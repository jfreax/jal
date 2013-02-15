#include <stdio.h>
#include <util/delay.h>

#include "io/twi.h"
#include "co-16_module_v1.0.h"


void CO_16_init(void)
{
    CO_16_SEND_COMMAND(0xae); // Display off
    CO_16_SEND_COMMAND(0x2e); // Deactivate scrolling
    CO_16_SEND_COMMAND(0xa4); // Set all pixels OFF
//   //delay(1000);
//   //i2c_OLED_send_cmd(0xa5);            //SET ALL pixels ON
//   delay(50);
    _delay_ms(50);
    CO_16_SEND_COMMAND(0x20); // Set Memory Addressing Mode
    CO_16_SEND_COMMAND(0x02); // Set Memory Addressing Mode to Page addressing mode (RESET)
// //  i2c_OLED_send_cmd(0xa0);      //colum address 0 mapped to SEG0 (POR)*** wires at bottom
    CO_16_SEND_COMMAND(0xa1); // Colum address 127 mapped to SEG0 (POR) (wires at top of board)
//  // i2c_OLED_send_cmd(0xC0);            // Scan from Right to Left (POR)         *** wires at bottom
    CO_16_SEND_COMMAND(0xC8); // Scan from Left to Right (wires at top)

    CO_16_SEND_COMMAND(0xa6); // Set White chars on black backround
//   //i2c_OLED_send_cmd(0xa7);            // Set BLACK chars on WHITE backround

    CO_16_SEND_COMMAND(0x81); // Setup CONTRAST CONTROL, following byte is the contrast Value
    CO_16_SEND_COMMAND(0xaf); // Contrast value between 1 ( == dull) to 256 ( == bright)
    _delay_ms(20);
    CO_16_SEND_COMMAND(0xaf); // Display on
    _delay_ms(20);
}


void CO_16_write_register(uint8_t address, uint8_t reg, uint8_t value)
{
    TWI_start(address, TWI_WRITE);
    TWI_write(reg);
    TWI_write(value);
    TWI_stop();
}


void CO_16_set_position(uint8_t row, uint8_t col)
{
    CO_16_SEND_COMMAND(0xb0 + row);                     // Set page address
    CO_16_SEND_COMMAND(0x00 + (8 * col & 0x0f));        // Set low col address
    CO_16_SEND_COMMAND(0x10 + ((8 * col >> 4) & 0x0f)); // Set high col address
}


void CO_16_clear_display(void)
{
    for (unsigned char k = 0; k < 8; k++) {
        CO_16_set_position(k, 0);
        for (unsigned char i = 0; i < 128; i++) {
            CO_16_SEND_BYTE(0x0); 
        }
    }
}
