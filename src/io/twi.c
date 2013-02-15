#include "twi.h"
#include <stdio.h>



uint8_t TWI_init(uint32_t bitrate)
{
#ifdef INTERNAL_I2C_PULLUPS
    PORTC |= (1 << SDA) | (1 << SCL);
#else
    PORTC &= ~(1 << SDA) & ~(1 << SCL);
#endif

    TWSR = 0;
    TWBR = ((F_CPU / bitrate) - 16) / 2;
    if (TWBR < 11)
        return 0;

    return 1;
}


uint8_t TWI_start(uint8_t address, uint8_t type)
{
    uint8_t twst;

    // Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // Wait until transmission completed
    while (!(TWCR & (1 << TWINT)));

    // Check value of TWI Status Register. Mask prescaler bits.
    twst = TWSR & 0xF8;
    if ((twst != TWI_START) && (twst != TWI_REP_START)) return 1;

    // Send device address
    TWDR = (address << 1) + type;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait until transmission completed and ACK/NACK has been received
    while (!(TWCR & (1 << TWINT)));

    // Check value of TWI Status Register. Mask prescaler bits.
    twst = TWSR & 0xF8;
    if ((twst != TWI_MTX_ADR_ACK) && (twst != TWI_MRX_ADR_ACK)) return 0;

    return 1;
}


void TWI_stop(void)
{
    // Send stop condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

    // Wait until stop condition is executed and bus released
    while (TWCR & (1 << TWINT));
}


uint8_t TWI_write(uint8_t byte)
{
    // Send data to the previously addressed device
    TWDR = byte;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait until transmission completed
    while (!(TWCR & (1 << TWINT)));

    // Check value of TWI Status Register. Mask prescaler bits
    uint8_t twst = TWSR & 0xF8;
    if (twst != TWI_MTX_DATA_ACK) return 0;

    return 1;
}


uint8_t TWI_read(uint8_t ack)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack ? (1 << TWEA) : 0);

    // Wait until transmission completed
    while (!(TWCR & (1 << TWINT)));

    uint8_t data = TWDR;
    if (!ack) {
        TWI_stop();
    }

    return data;
}


