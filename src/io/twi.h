#ifndef TWI_H
#define TWI_H

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

// Configuration
#define INTERNAL_I2C_PULLUPS

uint8_t TWI_init(uint32_t bitrate);

uint8_t TWI_start(uint8_t address, uint8_t type);
void TWI_stop(void);

uint8_t TWI_write(uint8_t byte);

#endif // TWI_H
