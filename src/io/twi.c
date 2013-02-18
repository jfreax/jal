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


uint8_t TWI_write(uint8_t address, uint8_t byte, uint8_t ack)
{
    if (TWI_start(address, TWI_WRITE))
        return 1;

    // Send data to the previously addressed device
    TWDR = byte;
    TWCR = (1 << TWINT) | (1 << TWEN);

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


// bool TWI_write_bit(uint8_t regAddr, uint8_t bitNum, uint8_t data)
// {
//     uint8_t b;
//     readByte(devAddr, regAddr, &b);
//     b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
//     //printf("i2c - writeBit - b: %X\n", b);
//     return writeByte(devAddr, regAddr, b);
// }


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

