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
#endif

#define MCU_328P 1

/**
 * KDevelop extras
 */
#if defined(MCU_328P) && !defined (_AVR_IOM328P_H_)
#include <avr/iom328p.h>
#endif

#if defined (MCU_1280) && !defined (_AVR_IOM1280_H_)
#include <avr/iom1280.h>
#endif

/**
 * UART
 */
#define UART_BAUD_RATE 57600



#endif