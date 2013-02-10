/*
 * KDevelop extras
 */
#if defined MCU_328p && !defined _AVR_IOM328P_H_
#include <avr/iom328p.h>
#endif

#if defined MCU_1280 && !defined _AVR_IOM1280_H_
#include <avr/iom1280.h>
#endif

/*
 * SPI
 */
#ifdef MCU_328p
#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define DD_MOSI  PORTB4
#define DD_SCK   PORTB5
#endif
