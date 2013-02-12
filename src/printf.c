#include "printf.h"

void init_printf(void)
{
    stdout = &mystdout;
}

static int uart_putchar_stream(char c, FILE* stream)
{
    if (c == '\n') uart_putchar_stream('\r', stream);

    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;

    return 0;
}

