#include "defines.h"
#if defined(JAL_USE_TWI)

#include <avr/io.h>
#include <stdio.h>

#include <util/delay.h>

#include "twi.h"


uint8_t TWI_init(uint32_t bitrate)
{
#ifdef INTERNAL_I2C_PULLUPS
    TWI_PORT |= (1 << SDA) | (1 << SCL);
#else
    TWI_PORT &= ~(1 << SDA) & ~(1 << SCL);
#endif

    TWSR = 0;
    TWBR = ((F_CPU / bitrate) - 16) / 2;
    if (TWBR < 11)
        return 1;

    return 0;
}


uint8_t TWI_start(uint8_t address, uint8_t type)
{
    uint8_t twst;

    // Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // Wait until transmission completed
    if (waitForTransmission())
        return 1;

    // Check value of TWI Status Register. Mask prescaler bits.
    twst = TWSR & 0xF8;
    if ((twst != TWI_START) && (twst != TWI_REP_START)) return 0;

    // Send device address
    TWDR = (address << 1) + type;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait until transmission completed and ACK/NACK has been received
    if (waitForTransmission())
        return 2;

    // Check value of TWI Status Register. Mask prescaler bits.
    twst = TWSR & 0xF8;
    if ((twst != TWI_MTX_ADR_ACK) && (twst != TWI_MRX_ADR_ACK)) return 1;

    return 0;
}


uint8_t TWI_stop(void)
{
    // Send stop condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

    // Wait until stop condition is executed and bus released
    if (waitForTransmission())
        return 1;

    return 0;
}


uint8_t TWI_read(uint8_t address, uint8_t* data, uint8_t ack)
{
    if (TWI_start(address, TWI_READ))
        return 1;

    TWCR = (1 << TWINT) | (1 << TWEN) | (ack ? (1 << TWEA) : 0);

    // Wait until transmission completed
    if (waitForTransmission())
        return 2;

    *data = TWDR;
    if (!ack) {
        TWI_stop();
    }

    return 0;
}


uint8_t TWI_read_register(uint8_t address, uint8_t register_address, uint8_t* data, uint8_t ack)
{
    // Say that we want to read old register from slave
    TWI_write(address, register_address, 0);

    // Read what slaves say to us
    if (TWI_start(address, TWI_READ))
        return 1;

    TWCR = (1 << TWINT) | (1 << TWEN) | (ack ? (1 << TWEA) : 0);

    // Wait until transmission completed
    if (waitForTransmission())
        return 2;

    *data = TWDR;
    if (!ack) {
        TWI_stop();
    }

    return 0;
}


uint8_t TWI_read_registers(uint8_t address, uint8_t register_address, uint8_t length, uint8_t* data, uint8_t ack)
{
    for (uint8_t i = 0; i < length; i++) {
        if (TWI_read_register(address, register_address + i, &data[i], 0))
            return 1;
    }
    if( ack )
      TWI_stop();

    return 0;
}



uint8_t TWI_write(uint8_t address, uint8_t data, uint8_t ack)
{
    if (TWI_start(address, TWI_WRITE))
        return 1;

    // Send data to the previously addressed device
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack ? (1 << TWEA) : 0);

    // Wait until transmission completed
    if (waitForTransmission())
        return 2;

    // Check value of TWI Status Register. Mask prescaler bits
    uint8_t twst = TWSR & 0xF8;
    if (twst != TWI_MTX_DATA_ACK) return 3;

    if (!ack) {
        TWI_stop();
    }

    return 0;
}


uint8_t TWI_write_register(uint8_t address, uint8_t register_address, uint8_t data, uint8_t ack)
{
    if (TWI_write(address, register_address, 0))
        return 1;

    return TWI_write(address, data, ack);
}


uint8_t TWI_change_bit(uint8_t address, uint8_t register_address, uint8_t bit_number, uint8_t data, uint8_t ack)
{
    uint8_t register_data;
    if (TWI_read_register(address, register_address, &register_data, 0))
        return 1;

    register_data = data ? (register_data | (1 << bit_number)) : (register_data & ~(1 << bit_number));

    return TWI_write_register(address, register_address, register_data, ack);
}


uint8_t TWI_change_bits(uint8_t address, uint8_t register_address, uint8_t start_bit, uint8_t length, uint8_t data, uint8_t ack)
{
    uint8_t register_data;
    if (TWI_read_register(address, register_address, &register_data, 0))
        return 1;

    unsigned char mask = ((1 << length) - 1) << (start_bit - length + 1);
    data <<= (start_bit - length + 1); // shift data into correct position
    data &= mask;
    register_data &= ~(mask);
    register_data |= data;

    return TWI_write_register(address, register_address, register_data, ack);
}


uint8_t waitForTransmission(void)
{
    uint8_t num = 255;
    while (!(TWCR & (1 << TWINT))) {
        _delay_us(2);
        if (!(num--)) {
            return 1;
        }
    }
    return 0;
}

#endif // JAL_USE_TWI

