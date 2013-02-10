#ifndef SPI_EEPROM_H
#define SPI_EEPROM_H

#include "defines.h"

#define OP_READ   2
#define OP_WRITE  1
#define OP_EREASE 3

int16_t EEPROM_read(uint8_t adress);

#endif