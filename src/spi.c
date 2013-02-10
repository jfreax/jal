#include <avr/io.h>
#include "defines.h"

void SPI_MasterInit(void)
{
    /* Set MOSI and SCK output, all others input */
    SPI_DDR = (1 << DD_MOSI) | (1 << DD_SCK);

    SPCR = ((1 << SPE) |            // SPI Enable
            (0 << SPIE) |           // SPI Interupt Enable
            (0 << DORD) |           // Data Order (0:MSB first / 1:LSB first)
            (1 << MSTR) |           // Master(1)/Slave(0) select
            (0 << SPR1) | (1 << SPR0) | // SPI Clock Rate; fck/16; See table 18-5
            (0 << CPOL) |           // Clock Polarity (0:SCK low / 1:SCK hi when idle)
            (0 << CPHA));           // Clock Phase (0:leading / 1:trailing edge sampling)

    SPSR = (1 << SPI2X);            // Double Clock Rate
}


void SPI_MasterTransmit(uint8_t cData)
{
    /* Start transmission */
    SPDR = cData;

    /* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)));
}
