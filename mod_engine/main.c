#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	PORTD = 1;
	while(1)
	{
		PORTD += 2;
		_delay_ms(1000);
	}
}
