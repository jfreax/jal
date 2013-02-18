#include "defines.h"
#if defined(JAL_USE_SSD1306)

#include <avr/io.h>
#include <util/delay.h>

#include "io/twi.h"
#include "ssd1306.h"

#include "data/font.h"


void SSD1306_init(void)
{
    SSD1306_SEND_COMMAND(0xae); // Display off
    SSD1306_SEND_COMMAND(0x2e); // Deactivate scrolling
    SSD1306_SEND_COMMAND(0xa4); // Set all pixels OFF
//     SSD1306_SEND_COMMAND(0xa5); // Set all pixels ON

    SSD1306_SEND_COMMAND(0xd3); // Set display offset
    SSD1306_SEND_COMMAND(0x00); //   no offset

    SSD1306_SEND_COMMAND(0x40); // line #0

    SSD1306_SEND_COMMAND(0x21); // set column address range
    SSD1306_SEND_COMMAND(0x00); // first column
    SSD1306_SEND_COMMAND(0x7f); // last column

    SSD1306_SEND_COMMAND(0xda); // Set com pins hardware configuration
    SSD1306_SEND_COMMAND(0x12);

    SSD1306_SEND_COMMAND(0xd5); // Set display clock divide ratio/oscillator frequency
    SSD1306_SEND_COMMAND(0x80); // Set divide ratio
    SSD1306_SEND_COMMAND(0xd9); // Set pre-charge period
    SSD1306_SEND_COMMAND(0xf1);

    SSD1306_SEND_COMMAND(0x8d); // Set Charge Pump enable/disable
    SSD1306_SEND_COMMAND(0x14); //   0x10 = disable; 0x14 = enable

    SSD1306_SEND_COMMAND(0xdb); // Set vcomh
    SSD1306_SEND_COMMAND(0x40);

    SSD1306_SEND_COMMAND(0x3f);//--1/64 duty

    SSD1306_SEND_COMMAND(0x20); // Set Memory Addressing Mode
    SSD1306_SEND_COMMAND(0x00); // Set Memory Addressing Mode to Page addressing mode (RESET)

    SSD1306_SEND_COMMAND(0xa1); // Colum address 127 mapped to SEG0 (POR) (wires at top of board)
    SSD1306_SEND_COMMAND(0xC8); // Scan from Left to Right (wires at top)

    SSD1306_SEND_COMMAND(0xa6); // Set White chars on black backround
//     SSD1306_SEND_COMMAND(0xa7); // Set BLACK chars on WHITE backround

    SSD1306_SEND_COMMAND(0xa8); // Set MUX ratio
    SSD1306_SEND_COMMAND(0x3f); // Set MUX ratio

    SSD1306_SEND_COMMAND(0x81); // Setup CONTRAST CONTROL, following byte is the contrast Value
    SSD1306_SEND_COMMAND(0xaf); // Contrast value between 1 ( == dull) to 256 ( == bright)

    _delay_ms(20);
    SSD1306_SEND_COMMAND(0xaf); // Display on
}


void SSD1306_write_register(uint8_t address, uint8_t reg, uint8_t value)
{
    TWI_write(address, reg, 0);
    TWI_write(address, value, 1);
}


void SSD1306_set_position(uint8_t row, uint8_t col)
{
    SSD1306_SEND_COMMAND(0xb0 + row);                     // Set page address
    SSD1306_SEND_COMMAND(0x00 + (8 * col & 0x0f));        // Set low col address
    SSD1306_SEND_COMMAND(0x10 + ((8 * col >> 4) & 0x0f)); // Set high col address
}


void SSD1306_clear_display(void)
{
    for (uint8_t k = 0; k < 8; k++) {
        SSD1306_set_position(k, 0);
        for (uint8_t i = 0; i < 128; i++) {
            SSD1306_SEND_BYTE(0x0);
        }
    }
}


void SSD1306_send_char(uint8_t character)
{
    for (uint8_t i = 0; i < 8; i++) {
        SSD1306_SEND_BYTE(simpleFont[character - 0x20][i]);
    }

}


void SSD1306_send_string(uint8_t* string)
{
    while (*string) {
        for (uint8_t i = 0; i < 8; i++) {
            SSD1306_SEND_BYTE(simpleFont[*string - 0x20][i]);
        }
        (*string)++;
    }
}


void SSD1306_set_contrast(uint8_t contrast)
{
    SSD1306_SEND_COMMAND(0x81); // Setup CONTRAST CONTROL, following byte is the contrast Value
    SSD1306_SEND_COMMAND(contrast); // Contrast value between 1 ( == dull) to 256 ( == bright)
}


void SSD1306_scrollright(uint8_t start, uint8_t stop)
{
    SSD1306_SEND_COMMAND(SSD1306_RIGHT_HORIZONTAL_SCROLL);
    SSD1306_SEND_COMMAND(0X00);
    SSD1306_SEND_COMMAND(start);
    SSD1306_SEND_COMMAND(0X00);
    SSD1306_SEND_COMMAND(stop);
    SSD1306_SEND_COMMAND(0X01);
    SSD1306_SEND_COMMAND(0XFF);
    SSD1306_SEND_COMMAND(SSD1306_ACTIVATE_SCROLL);
}


#endif // JAL_USE_SSD1306

