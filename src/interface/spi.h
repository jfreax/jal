#ifndef SPI_H
#define SPI_H

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
 * @param 8-Bit data
 */
uint8_t SPI_MasterTransmit(uint8_t cData);


/**
 * Read one full byte from slave
 * @return MISO byte
 */
uint8_t SPI_MasterReceive(void);


#endif
