#include <avr/io.h>
#include <util/delay.h>


#include "spi_eeprom.h"
#include "spi.h"

int16_t EEPROM_read(uint8_t adress)
{
    SPI_PORT &= ~(1 << SPI_CS);

    /* Send start bit and OP Code */
    uint8_t startcode = (1 << 3) | (OP_READ);
    startcode = SPI_MasterTransmit(startcode);

    _delay_ms(1);

    /* Send adress */
    SPI_MasterTransmit(adress);

    SPI_PORT |= (1 << SPI_CS);

    /* Get data */
    int16_t data = ((int16_t)SPI_MasterReceive << 8) | (int16_t)SPI_MasterReceive;
    return data;
}
