#include <avr/io.h>
#include <util/delay.h>

#include <avr/iom1280.h> // only for kdevelop

int main(void)
{
    DDRB  |= (1<<PC7);

    while(1) {
        PORTB |=(1<<PC7);
        _delay_ms(1000);
        PORTB &=~(1<<PC7);
        _delay_ms(1000);
    }
}
