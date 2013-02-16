#ifndef PRINTF_H
#define PRINTF_H

#include <stdio.h>
#include <avr/io.h>


void init_printf(FILE* file);

int uart_putchar_stream(char c, FILE *stream);
int ssd1306_putchar_stream(char c, FILE *stream);


static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar_stream, NULL, _FDEV_SETUP_WRITE);
static FILE ssd1306_stdout = FDEV_SETUP_STREAM(ssd1306_putchar_stream, NULL, _FDEV_SETUP_WRITE);

#endif // PRINTF_H