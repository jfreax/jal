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

#ifndef SPI_EEPROM_H
#define SPI_EEPROM_H

/** 
 *  @file 
 *  @code #include <spi_eeprom.h> @endcode
 *  @ingroup eeprom
 * 
 *  @brief SPI control of a 93C66 EEPROM Modules
 * 
 *  These functions can be used to read, write and erase data from EEPROM through the built in SPI. 
 * 
 *  SPI must be initialized manually. Transmit and receive data is archived by using the spi functions from @link spi here@endlink.
 *
 *  @note Based on *FM93C66 4096-Bit Serial CMOS EEPROM (MICROWIRE (TM) Synchronous Bus)* Datasheet

 *  @author Jens Dieskau jens.dieskau@gmail.com http://jdsoft.de
 */
 
/**@{*/

#include "defines.h"

/*! \name Opcodes
 *  This is a 2-bit field and should immediately follow the start bit.
 *  These two bits (along with 2 MSB of address field) select a
 *  particular instruction to be executed.
 */

/*! \{ */
#define OP_READ   2
#define OP_WRITE  1
#define OP_EREASE 3
/*! \} */

/**
 * @brief EEPROM_read allows data to be read from a selected location
 *        in the memory array.
 * @param adress 8-bit adress location in memory
 * @return data 16-bit (signed) data from rom at position *adress*
 */
int16_t EEPROM_read(uint8_t adress);


/**
 * @brief This function allows write operation to a specified location in
 *        the memory with a specified data. 
 *        This instruction is valid only when device is write-enabled. Use EEPROM_write_enable().
 * @param adress 8-bit adress location in memory
 * @param data 16-bit (signed) data from rom at position *adress*
 */
void EEPROM_write(uint8_t adress, int16_t data);


/**
 * After powering up the device, it is in a *Write Disable (WDS)* state.
 * Therefore, before writing you have to send a *Write Enable (WEN)* instruction.
 *
 * Once *WEN* is executed, it remains enabled until a *WDS* instruction is transmitted (use EEPROM_write_disable)
 * or VCC is removed.
 */
void EEPROM_write_enable(void);


/**
 * This disables all write operations.
 * Executing this function after a write would protect you against data disturb due to spurious noise,
 * glitches and so on.
 */
void EEPROM_write_disable(void);


/**@}*/

#endif // SPI_EEPROM_H