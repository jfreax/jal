/*
 * KDevelop extras
 */
#if defined(MCU_328p) && !defined (_AVR_IOM328P_H_)
#include <avr/iom328p.h>
#endif

#if defined (MCU_1280) && !defined (_AVR_IOM1280_H_)
#include <avr/iom1280.h>
#endif

/*
 * SPI
 */
#if defined(MCU_328p)
#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define DD_MOSI  DDB3
#define DD_SCK   DDB5
#endif
