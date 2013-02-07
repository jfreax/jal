#include <avr/io.h>
#include <util/delay.h>         

int main(void)
{
   DDRC  |= (1<<PC5);
 
   while(1) {
	PORTC |=(1<<PC5);
	_delay_ms(1000);
	PORTC &=~(1<<PC5);
	_delay_ms(1000);
   }           
}
