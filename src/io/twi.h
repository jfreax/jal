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
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__) \
 || defined(__AVR_ATmega3250__) || defined(__AVR_ATmega3290__) ||defined(__AVR_ATmega6450__) || defined(__AVR_ATmega6490__)
#define TWI_PORT PORTC
#define SDA  PC4
#define SCL  PC5

#elif defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__) || defined(__AVR_ATmega1280__)  || defined(__AVR_ATmega1281__) || defined(__AVR_ATmega640__)
#define TWI_PORT PORTD
#define SDA  PD1
#define SCL  PD0

#else // general pins (may be wrong)
#define TWI_PORT PORTC
#define SDA  PC4
#define SCL  PC5
#endif

// Configuration
#define INTERNAL_I2C_PULLUPS


/**
 * @brief Initialize 2-wire interface and set bitrate
 *
 * If bitrate is too high, then return 1
 *
 * @param bitrate TWI bitrate (Hz)
 *
 * @return 0:    No error
 */
uint8_t TWI_init(uint32_t bitrate);


/**
 * @brief Start the TWI Master Interface
 *
 * Should not be called directly.
 *
 * @param adress Device adress
 * @param type Type of operation:\n
 *             TWI_READ: Read data from the slave\n
 *             TWI_WRITE: Write data to the slave
 *
 * @return 0:    No error
 */
uint8_t TWI_start(uint8_t address, uint8_t type);


/**
 * @brief Stop the TWI Master Interface
 *
 * Should not be called directly.
 *
 * @return 0: No error
 */
uint8_t TWI_stop(void);


/**
 * @brief Read a byte from the slave.
 *
 * If parameter ack is set then is this the last byte to read.
 * TWI_stop() gets called automaticall.y
 *
 * @param adress Device adress
 * @param data Readed byte
 * @param ack if set, then this is the last byte
 *
 * @return 0:    Byte sent
 *         else: Error in transmission
 */
uint8_t TWI_read(uint8_t address, uint8_t* data, uint8_t ack);


/**
 * @brief Read byte from slave from a certain register
 *
 * Its shorthand for TWI_write(..., register_address, ...) and then TWI_read(..., register_address, ...)
 *
 * @param adress Device adress
 * @param register_address Register adress
 * @param data Byte to be send
 * @param ack if set, then this is the last byte
 *
 * @return 0:    Byte sent
 *         else: Error in transmission
 */
uint8_t TWI_read_register(uint8_t address, uint8_t register_address, uint8_t* data, uint8_t ack);


/**
 * @brief Write a byte to the slave device.
 *
 * @param adress Device adress
 * @param data Byte to be send
 * @param ack if set, then this is the last byte
 *
 * @return 0:    Byte sent
 *         else: Error in transmission
 */
uint8_t TWI_write(uint8_t address, uint8_t data, uint8_t ack);


/**
 * @brief Write a byte into a certain register on slave device.
 * 
 * Shorthand for TWI_write(..., register_address, ...) and then TWI_write(..., data, ...)
 *
 * @param adress Device adress
 * @param register_address Register adress
 * @param data Byte to be send
 * @param ack if set, then this is the last byte
 *
 * @return 0:    Byte sent
 *         else: Error in transmission
 */
uint8_t TWI_write_register(uint8_t address, uint8_t register_address, uint8_t data, uint8_t ack);


/**
 * @brief Change one single bit in an 8-bit device register
 *
 * @param adress Device adress
 * @param register_address Register adress
 * @param bit_number Which bit to change (0-7)
 * @param data Byte to be send
 * @param ack if set, then this is the last byte
 *
 * @return 0: Bit set
 */
uint8_t TWI_change_bit(uint8_t address, uint8_t register_address, uint8_t bit_number, uint8_t data, uint8_t ack);


/**
 * @brief Change many bits all at once in an 8-bit device register
 *
 * @param adress Device adress
 * @param register_address Register adress
 * @param start_bit Start bit
 * @param length How many bits to change (0-7)
 * @param data Byte to be send
 * @param ack if set, then this is the last byte
 *
 * @return 0: Bit set
 */
uint8_t TWI_change_bits(uint8_t address, uint8_t register_address, uint8_t start_bit, uint8_t length, uint8_t data, uint8_t ack);


/**
 * @brief Wait until data successful transmitted
 *
 * Waits 255 times (in a while loop) until given up
 * and rise an error.
 *
 * Should not be called directly.
 *
 * @return 0: No error
 */
uint8_t waitForTransmission(void);


#endif // TWI_H
