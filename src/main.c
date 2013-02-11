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

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "defines.h"
#include "uart.h"
#include "io/spi.h"
#include "devices/eeprom/spi_eeprom.h"

/**
 * Test
 */
int __attribute__((naked)) main(void)
{
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enable interrupt
    sei();
    uart_puts("Data on adress 10\n");


    // EEPROM SPI test code
    SPI_MasterInit();

    // Write data
    EEPROM_write_enable();
    EEPROM_write(10, 3);

    // Read test data from eeprom with spi
    int16_t data = EEPROM_read(10);

    char intToStrBuffer[16];
    itoa(data, intToStrBuffer, 10);
    uart_puts(intToStrBuffer);
    uart_puts("_10\n");
    itoa(data, intToStrBuffer, 2);
    uart_puts(intToStrBuffer);
    uart_puts("_2\n");



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

