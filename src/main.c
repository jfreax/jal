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
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include <util/delay.h>

#include "defines.h"
#include "printf.h"

#include "io/uart.h"
#include "io/spi.h"

#include <compat/twi.h>

#include "io/twi.h"

#include "devices/eeprom/spi_eeprom.h"
#include "devices/oled/co-16_module_v1.0.h"



int __attribute__((OS_main, noreturn)) main(void)
{
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    init_printf();

    // Enable interrupt
    sei();
    uart_puts("Data on adress 10\n");

    // EEPROM SPI test code //
    //////////////////////////
    SPI_MasterInit();

    // Write data
    //EEPROM_write_enable();
    //EEPROM_write(10, 3);

    // Read test data from eeprom with spi
    int16_t data = EEPROM_read(10);
    printf("Base 10: %i\n", data);

    char intToStrBuffer[16];
    itoa(data, intToStrBuffer, 2);
    printf("Base 02: %s\n", intToStrBuffer);

    // I2C test code //
    // DDRC |= (1 << 4);
    //DDRC |= (1 << 5);

    //cli ();
    //_delay_ms(100);

    uint8_t twi_ret; // = i2c_start(0x55+I2C_WRITE);
    twi_ret = TWI_init(50000);
    printf("TWI2 init: %i\n", twi_ret);

    CO_16_init();
    CO_16_clear_display();
    CO_16_set_position(2, 3);

    for (uint8_t i = 0; i < 200; i++) {
        CO_16_SEND_BYTE(i);
    }

//      TWI_start(0x1E, TWI_WRITE);
//      TWI_write(0x80);
//      TWI_stop();

    printf("Finish");
//
//     TWI_start(0x55, TWI_READ);
//     TWI_write(0xa7);
//     TWI_stop();



    // UART test code //
    ////////////////////

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

            if ((char)c == '0') {
                cli(); //irq's off
                wdt_enable(WDTO_15MS); //wd on,15ms
                while (1); //loop
            }
        }
    }
}

