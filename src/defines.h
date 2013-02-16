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

#ifndef DEFINES_H
#define DEFINES_H

/**
 * General
 */
#ifndef F_CPU
#define F_CPU 16000000L
#endif // F_CPU

/**
 * Enable features.
 * Comment out unused features
 */
#define JAL_USE_UART
#define JAL_USE_TWI
#define JAL_USE_SPI
#define JAL_USE_PRINTF

#define JAL_INCLUDE_FONT

/**
 * Enable hardware device driver.
 * Comment out unused drivers.
 */
#define JAL_USE_EEPROM_93C66
#define JAL_USE_SSD1306



/**
 * UART specific
 */
#ifndef UART_BAUD_RATE
#define UART_BAUD_RATE 57600
#endif // UART_BAUD_RATE


/**
 * KDevelop extras
 */
#ifdef IN_IDE_PARSER

#define MCU_328P

#if defined(MCU_328P) && !defined (_AVR_IOM328P_H_)
#include <avr/iom328p.h>
#endif

#if defined (MCU_1280) && !defined (_AVR_IOM1280_H_)
#include <avr/iom1280.h>
#endif

#endif


#endif // DEFINES_H
