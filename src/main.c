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

    while(1) {
        uart_puts("a");
        PORTB |= (1<<PC7);
        //_delay_ms(1000);
        //PORTB &= ~(1<<PC7);
        //_delay_ms(1000);
    }
}
