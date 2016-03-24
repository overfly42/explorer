#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

void setParallel(uint8_t data);

int main(void)
{
	DDRA = 0xFF;
	PORTB = 0xFF;
	DDRD = 0xFF;//Set all PORT D pins to Output
	uint8_t i = 0;
	while(1)
	{
		PORTA = i++;
		setParallel(i);
		_delay_ms(100);
	}
}
#define SHCP 	1
#define STCP 	2
#define OE 		4
#define MR 		8
#define DS		16

#define EMPTY_SHIFT_1 0
#define EMPTY_SHIFT_2 STCP
#define SET_OUTPUT_1 MR
#define SET_OUTPUT_2 (MR | STCP)
#define INPUT_PREPAIR MR
#define INPUT_WRITE (MR | SHCP)
void setParallel(uint8_t data)
{
	//PD0 --> SHCP
	//PD1 --> STCP
	//PD2 --> OE
	//PD3 --> MR 
	//PD4 --> DS
//	PORTD = EMPTY_SHIFT_1;//Prepair
//		_delay_ms(100);
//	PORTD = EMPTY_SHIFT_2;//Rising edge
	uint8_t i = 0;
	for(i = 0; i < 8; i++)
	{
//		_delay_ms(100);
		PORTD = INPUT_PREPAIR;
//		_delay_ms(100);
		PORTD = INPUT_PREPAIR | (((data>>i)&1)<<4);
//		_delay_ms(100);
		PORTD |= INPUT_WRITE; 
	}
	PORTD = SET_OUTPUT_1;//prepair
		_delay_ms(100);
	PORTD = SET_OUTPUT_2;//Raising Edge
}
