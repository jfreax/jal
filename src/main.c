#ifndef F_CPU
#define F_CPU 16000000L
#endif

#define MCU_328p 1
#define UART_BAUD_RATE 57600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "defines.h"
#include "uart.h"


int __attribute__((naked))
main(void)
{
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enable interrupt
    sei();
    uart_puts("String stored in SRAM\n");

    uint16_t c;
    while (1) {
        c = uart_getc();
        if (c ^ UART_NO_DATA) {
            /* check for Frame or Overrun error */
            if (c & UART_FRAME_ERROR) {
                /* Framing Error detected, i.e no stop bit detected */
                uart_puts("UART Frame Error: ");
            }
            if (c & UART_OVERRUN_ERROR) {
                uart_puts("UART Overrun Error: ");
            }
            if (c & UART_BUFFER_OVERFLOW) {
                uart_puts("Buffer overflow error: ");
            }
            /* send received character back */
            uart_putc((unsigned char)c);
        }
    }
}

void SPI_MasterInit(void)
{
    /* Set MOSI and SCK output, all others input */
    SPI_DDR = (1 << DD_MOSI) | (1 << DD_SCK);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

