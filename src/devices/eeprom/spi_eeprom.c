/*
    Copyright (C) 2013  Jens Dieskau <jens.dieskau@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include <avr/io.h>
#include <util/delay.h>


#include "spi_eeprom.h"
#include "interface/spi.h"

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

    /* Unlike writing, reading is on the trailing clock edge */
    SPCR |= (1 << CPHA);

    /* Get data */
    int16_t data = (SPI_MasterReceive() << 8) | (SPI_MasterReceive());

    /* set back to leading edge */
    SPCR &= ~(1 << CPHA);

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
    _delay_ms(15);
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

