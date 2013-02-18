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

#include "devices/eeprom/93C66.h"
#include "devices/oled/ssd1306.h"


int __attribute__((OS_main, noreturn)) main(void)
{
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    init_printf(&uart_stdout);

    printf("Hello!\n");

    // Enable interrupt
    sei();

//     uart_puts("Data on adress 10\n");

    // EEPROM SPI test code //
    //////////////////////////
//     SPI_MasterInit();
//
//     uart_puts("int\n");
//
//     // Write data
//     //EEPROM_write_enable();
//     //EEPROM_write(10, 3);
//
//     // Read test data from eeprom with spi
//     int16_t data = EEPROM_read(10);
//     printf("Base 10: %i\n", data);
//
//     char intToStrBuffer[16];
//     itoa(data, intToStrBuffer, 2);
//     printf("Base 02: %s\n", intToStrBuffer);
//
    // TWI test code //
    ///////////////////
    uint8_t twi_ret; // = i2c_start(0x55+I2C_WRITE);
    twi_ret = TWI_init(100000);
    printf("TWI2 init: %i\n", twi_ret);
//
//     // SSD1306 test code //
//     ///////////////////////
//     SSD1306_SEND_COMMAND(0xae);
//     SSD1306_init();
//     SSD1306_clear_display();
//     SSD1306_set_position(2, 3);
//     SSD1306_send_string("Hallooooo!1234567890");

//     init_printf(&ssd1306_stdout);

//     printf("Finish");


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

            // TODO real command for reboot
#if defined(JAL_REBOOT_WATCHDOG)
            if ((char)c == '0') {
                cli(); //irq's off
                wdt_enable(WDTO_15MS); //wd on,15ms
                while (1); //loop
            }
#endif

        }
    }
}

