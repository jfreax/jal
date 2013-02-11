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

#ifndef SPI_H
#define SPI_H

/** 
 *  @file 
 *  @code #include <spi.h> @endcode
 *  @ingroup spi
 * 
 *  @brief This is
 *         and more
 *         here
 *
 *  @note Based on 
 *  @author Jens Dieskau jens.dieskau@gmail.com http://jdsoft.de
 */
 

#include "defines.h"

#if defined(MCU_328P)
#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define SPI_MOSI DDB3
#define SPI_MISO DDB4
#define SPI_SCK  DDB5
#define SPI_CS   DDB2
#endif


/**
 * Initialize register for master spi communication
 */
void SPI_MasterInit(void);


/**
 * Shift full array to target device without receiving any byte
 * @param 8-bit data
 * @return 8-bit data from MISO
 */
uint8_t SPI_MasterTransmit(uint8_t cData);


/**
 * Read one full byte from slave
 * @return MISO byte
 */
uint8_t SPI_MasterReceive(void);


#endif // SPI_H
