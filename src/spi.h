#ifndef SPI_H
#define SPI_H


/**
 * Initialize register for master spi communication
 */
void SPI_MasterInit(void);

/**
 * Shift full array to target device without receiving any byte
 * @param 8-Bit data
 */
void SPI_MasterTransmit(uint8_t cData);

#endif
