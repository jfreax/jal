#include <avr/io.h>
#include "defines.h"

void SPI_MasterInit(void)
{
    /* Set MOSI and SCK output, all others input */
    SPI_DDR = (1 << DD_MOSI) | (1 << DD_SCK);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)));
}
