#include <avr/io.h>
#include "spi.h"

void SPI_MasterInit(void)
{
    /* Set MOSI, SCK and CS as output, all others input */
    SPI_DDR = (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_CS);
    SPI_DDR &= ~(1<<SPI_MISO);

    SPCR = ((1 << SPE) |            // SPI Enable
            (0 << SPIE) |           // SPI Interupt Enable
            (0 << DORD) |           // Data Order; MSB first(0) / LSB first(1)
            (1 << MSTR) |           // Master(1)/Slave(0) select
            (0 << SPR1) | (1 << SPR0) | // SPI Clock Rate; See table 18-5
            (0 << CPOL) |           // Clock Polarity SCK low(0) / SCK hi when idle(1)
            (0 << CPHA));           // Clock Phase; leading(0) / trailing edge(1) sampling

    SPSR = (1 << SPI2X);            // Double Clock Rate
}


uint8_t SPI_MasterTransmit(uint8_t cData)
{
    /* Activate the CS pin */
    //SPI_PORT &= ~(1 << SPI_CS);

    /* Start transmission */
    SPDR = cData;

    /* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)));
    
    /* Deactivate the CS pin */
    //SPI_PORT |= (1<<SPI_CS);
    
    return SPDR;
}


uint8_t SPI_MasterReceive(void)
{
    /* Wait for reception complete */
    while (!(SPSR & (1 << SPIF)));

    /* Return Data Register */
    return SPDR;
}
