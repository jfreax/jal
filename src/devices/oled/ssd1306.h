#ifndef SSD1306_MODULE_V1_0
#define SSD1306_MODULE_V1_0

/**
 * @file
 * @code #include <co-16_module_v1.0.h> @endcode
 * @ingroup oled
 *
 * @brief Driver for CO-16 OLED Module Board V1.0
 * 
 * A breakout module for a 128X64 Monochrome OLED Display with a SSD1306 controller.
 * It only uses the TWI (I2C) interface.
 *
 * @author Jens Dieskau jens.dieskau@gmail.com http://jdsoft.de
 *
 */

#define SSD1306_MODULE_V1_0_ADRESS 0x3c

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A


#define SSD1306_SEND_COMMAND(CMD)  SSD1306_write_register(SSD1306_MODULE_V1_0_ADRESS, 0x80, CMD)
#define SSD1306_SEND_BYTE(BYTE)  SSD1306_write_register(SSD1306_MODULE_V1_0_ADRESS, 0x40, BYTE)


void SSD1306_init(void);
void SSD1306_write_register(uint8_t address, uint8_t reg, uint8_t value);

void SSD1306_set_position(uint8_t row, uint8_t col);
void SSD1306_clear_display(void);

void SSD1306_send_char(uint8_t character);
void SSD1306_send_string(uint8_t* string);

void SSD1306_set_contrast(uint8_t contrast);
void SSD1306_scrollright(uint8_t start, uint8_t stop);


#endif // SSD1306_MODULE_V1_0
