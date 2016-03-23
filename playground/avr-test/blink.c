#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>


int main(void)
{
	DDRA = 0xFF;
	PORTB = 0xFF;
	uint8_t i = 0;
	while(1)
	{
		PORTA = i++;
		_delay_ms(100);
	}
}
