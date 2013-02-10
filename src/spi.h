#ifndef SPI_H
#define SPI_H

#include "defines.h"

#if defined(MCU_328P)
#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define DD_MOSI  DDB3
#define DD_SCK   DDB5
#endif


/**
 * Initialize register for master spi communication
 */
void SPI_MasterInit(void);

/**
 * Shift full array to target device without receiving any byte
 * @param 8-Bit data
 */
void SPI_MasterTransmit(uint8_t cData);


/**
 * Read one full byte from slave
 * @return MISO byte
 */
uint8_t SPI_MasterReceive(void);


#endif
