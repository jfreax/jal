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

#ifndef SPI_EEPROM_H
#define SPI_EEPROM_H

/** 
 *  @file
 *  @code #include <spi_eeprom.h> @endcode
 *  @ingroup eeprom
 * 
 *  @brief This is
 *         and more
 *         here
 *
 *  @note Based on 
 *  @author Jens Dieskau jens.dieskau@gmail.com http://jdsoft.de
 */
 
/**@{*/

#include "defines.h"

#define OP_READ   2
#define OP_WRITE  1
#define OP_EREASE 3


/**
 * lala
 */
int16_t EEPROM_read(uint8_t adress);
void EEPROM_write(uint8_t adress, int16_t data);

void EEPROM_write_enable(void);



/**@}*/

#endif // SPI_EEPROM_H