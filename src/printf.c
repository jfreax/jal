#include "defines.h"
#if defined(JAL_USE_PRINTF)

#include "printf.h"
#include "devices/oled/ssd1306.h"

void init_printf(FILE* file)
{
    stdout = file;
}

int uart_putchar_stream(char c, FILE* stream)
{
    if (c == '\n') uart_putchar_stream('\r', stream);

    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;

    return 0;
}


#if defined(JAL_USE_SSD1306)
int ssd1306_putchar_stream(char c, FILE* stream)
{
    // TODO if (c == '\n')
    
    SSD1306_send_char(c);
  
    return 0;
}
#endif // JAL_USE_SSD1306

#endif // JAL_USE_PRINTF
