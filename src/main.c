#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <avr/iom1280.h> // Special for kdevelop

#include "uart.h"

#ifndef F_CPU
#define F_CPU 16000000L
#endif

#define UART_BAUD_RATE 9600


int main(void)
{
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enable interrupt
    sei();
    uart_puts("String stored in SRAM\n");

    DDRB  |= (1<<PC7);

    uint16_t c;
    while(1) {
        c = uart_getc();
        if ( c & UART_NO_DATA ) {
        } else {
            /* check for Frame or Overrun error */
            if ( c & UART_FRAME_ERROR ) {
                /* Framing Error detected, i.e no stop bit detected */
                uart_puts("UART Frame Error: ");
            }
            if ( c & UART_OVERRUN_ERROR ) {
                uart_puts("UART Overrun Error: ");
            }
            if ( c & UART_BUFFER_OVERFLOW ) {
                uart_puts("Buffer overflow error: ");
            }
            /* send received character back */
            uart_putc( (unsigned char)c );
        }


        //PORTB |= (1<<PC7);
        //uart_puts("a");
        //_delay_ms(1000);
        //PORTB &= ~(1<<PC7);
        //uart_puts("b");
        //_delay_ms(1000);
    }
}
