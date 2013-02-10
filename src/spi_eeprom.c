#include <avr/io.h>

#include "spi_eeprom.h"
#include "spi.h"

uint16_t EEPROM_read(uint8_t adress)
{
  // Send start bit and OP Code
  uint8_t startcode = (1 << 3) | (OP_READ);
  SPI_MasterTransmit(startcode);
  
  // Send adress
  SPI_MasterTransmit(adress);
  
  // Get data
  uint16_t data = ((uint16_t)SPI_MasterReceive << 8) | (uint16_t)SPI_MasterReceive;
  return data;
}