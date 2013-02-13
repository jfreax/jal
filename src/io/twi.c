#include "twi.h"
#include <stdio.h>

/**
 * @brief Initialize 2-wire interface and set bitrate
 *
 * If bitrate is too high, then return 1
 *
 * @param bitrate TWI bitrate (Hz)
 * @return 1 - Ok
 *         0 - Bitrate too high
 */
uint8_t TWI_init(uint32_t bitrate)
{
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

    printf("1 - %i\n", TWCR);

    // Wait until transmission completed
    while (!(TWCR & (1 << TWINT)));

    printf("2\n");


    // Check value of TWI Status Register. Mask prescaler bits.
    twst = TWSR & 0xF8;
    if ((twst != TWI_START) && (twst != TWI_REP_START)) return 1;
    
        printf("3\n");


    // Send device address
    TWDR = (address << 1) + type;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Wait until transmission completed and ACK/NACK has been received
    while (!(TWCR & (1 << TWINT)));
    
        printf("4\n");


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
