#include "defines.h"
#if !defined(PRINTF_H) && defined(JAL_USE_PRINTF)
#define PRINTF_H

#include <stdio.h>
#include <avr/io.h>


void init_printf(FILE* file);

int uart_putchar_stream(char c, FILE *stream);
static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar_stream, NULL, _FDEV_SETUP_WRITE);

#if defined(JAL_USE_SSD1306)
int ssd1306_putchar_stream(char c, FILE *stream);
static FILE ssd1306_stdout = FDEV_SETUP_STREAM(ssd1306_putchar_stream, NULL, _FDEV_SETUP_WRITE);
#endif // JAL_USE_SSD1306


#endif // PRINTF_H