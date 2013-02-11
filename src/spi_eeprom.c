#include <avr/io.h>
#include <util/delay.h>


#include "spi_eeprom.h"
#include "spi.h"

#define EEPROM_SELECT SPI_PORT |= (1 << SPI_CS)
#define EEPROM_DESELECT   SPI_PORT &= ~(1 << SPI_CS); _delay_us(1)


int16_t EEPROM_read(uint8_t adress)
{
    EEPROM_SELECT;

    /* Send start bit and OP Code */
    uint8_t startcode = (1 << 2) | (OP_READ);
    SPI_MasterTransmit(startcode);

    /* Send adress */
    uint8_t datastart = SPI_MasterTransmit(adress);

    /* Shift out "dummy bit" manually */
    SPCR &= ~(1 << SPE);
    SPI_PORT |= (1 << SPI_SCK);
    SPI_PORT &= ~(1 << SPI_SCK);
    SPCR |= (1 << SPE);

    /* Get data */
    //int16_t data = (SPI_MasterReceive() << 9) | (SPI_MasterReceive() << 1) | (SPI_MasterReceive() >> 7);
    int16_t data = (SPI_MasterReceive() << 8) | (SPI_MasterReceive());
    EEPROM_DESELECT;
    return data;
}


void EEPROM_write(uint8_t adress, int16_t data)
{
    EEPROM_SELECT;
    /* Send start bit and OP Code */
    uint8_t startcode = (1 << 2) | (OP_WRITE);
    SPI_MasterTransmit(startcode);

    /* Send adress */
    SPI_MasterTransmit(adress);

    /* Send data */
    uint8_t dataL = data;
    uint8_t dataH = (data >> 8);
    SPI_MasterTransmit(dataH);
    SPI_MasterTransmit(dataL);

    EEPROM_DESELECT;

    /* Wait T_WP=15ms (see datasheet) */
    _delay_ms(15 + 5);
}

void EEPROM_write_enable(void)
{
    EEPROM_SELECT;
    /* Send start bit and OP Code (00) */
    uint8_t startcode = (1 << 2);
    SPI_MasterTransmit(startcode);

    /* Send adress */
    SPI_MasterTransmit(3 << 6);

    EEPROM_DESELECT;
}
