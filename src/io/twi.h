#include "defines.h"
#if !defined(TWI_H) && defined(JAL_USE_TWI)
#define TWI_H

/**
 * @file
 * @code #include <twi.h> @endcode
 * @ingroup twi
 *
 * @brief Two-Wire Interface
 *
 * TODO
 *
 * @author Jens Dieskau jens.dieskau@gmail.com http://jdsoft.de
 *
 */

#include "defines.h"
#include <avr/io.h>

#define TWI_READ    1
#define TWI_WRITE   0

// General TWI Master status codes
#define TWI_START                   0x08  // START has been transmitted  
#define TWI_REP_START               0x10  // Repeated START has been transmitted
#define TWI_ARB_LOST                0x38  // Arbitration lost

// Transmitter status codes
#define TWI_MTX_ADR_ACK             0x18  // SLA+W has been tramsmitted and ACK received
#define TWI_MTX_ADR_NACK            0x20  // SLA+W has been tramsmitted and NACK received 
#define TWI_MTX_DATA_ACK            0x28  // Data byte has been tramsmitted and ACK received
#define TWI_MTX_DATA_NACK           0x30  // Data byte has been tramsmitted and NACK received 

// Receiver status codes
#define TWI_MRX_ADR_ACK             0x40  // SLA+R has been tramsmitted and ACK received
#define TWI_MRX_ADR_NACK            0x48  // SLA+R has been tramsmitted and NACK received
#define TWI_MRX_DATA_ACK            0x50  // Data byte has been received and ACK tramsmitted
#define TWI_MRX_DATA_NACK           0x58  // Data byte has been received and NACK tramsmitted

// Pin configuration
#define SDA  PC4
#define SCL  PC5

// Configuration
#define INTERNAL_I2C_PULLUPS


/**
 * @brief Initialize 2-wire interface and set bitrate
 *
 * If bitrate is too high, then return 1
 *
 * @param bitrate TWI bitrate (Hz)
 * @return TRUE:    OK, TWI Master accessible\n
 *         FALSE:    Bitrate too high
 */
uint8_t TWI_init(uint32_t bitrate);


/**
 * @brief Start the TWI Master Interface
 *
 * @param adress Device adress
 * @param type Type of operation:\n
 *             TWI_READ: Read data from the slave\n
 *             TWI_WRITE: Write data to the slave
 * @return TRUE:    OK, TWI Master accessible\n
 *         FALSE:   Error in starting TWI Master
 */
uint8_t TWI_start(uint8_t address, uint8_t type);


/**
 * @brief Stop the TWI Master Interface
 */
void TWI_stop(void);


/**
 * @brief Write a byte to the slave device.
 *
 * @param byte Byte to be send
 * @return TRUE:    Byte sent
 *         FALSE:   Error in transmission
 */
uint8_t TWI_write(uint8_t byte);


/**
 * @brief Read a byte from the slave.
 *
 * If parameter ack is set then is this the last byte to read.
 * TWI_stop() gets called automaticall.y
 *
 * @param ack if set, then this is the last byte
 * @return Readed byte
 */
uint8_t TWI_read(uint8_t ack);


#endif // TWI_H
