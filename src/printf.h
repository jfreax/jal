#ifndef PRINTF_H
#define PRINTF_H

#include <stdio.h>
#include <avr/io.h>


void init_printf(void);
static int uart_putchar_stream(char c, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar_stream, NULL, _FDEV_SETUP_WRITE);

#endif // PRINTF_H