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