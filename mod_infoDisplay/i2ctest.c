#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include "i2ctest.h"
#include "../mod_microcontroller/src/usiTwiSlave.h"

uint8_t redVal;

int main(void)
{
	init();
	while(1)
	{
		redVal++;
		writeData();
		_delay_ms(200);
	}
}
void setParallel(uint8_t data)
{
	//PD0 --> SHCP
	//PD1 --> STCP
	//PD2 --> OE
	//PD3 --> MR 
	//PD4 --> DS
	uint8_t i = 0;
	for(i = 0; i < 8; i++)
	{
		PORTD = INPUT_PREPAIR;
		PORTD = INPUT_PREPAIR | (((data>>i)&1)<<4);
		PORTD |= INPUT_WRITE; 
	}
	PORTD = SET_OUTPUT_1;//prepair
		_delay_ms(200);
	PORTD = SET_OUTPUT_2;//Raising Edge
}

void init (void)
{
	//Setting the Ports
	DDRD = 0xFF;//Set all PORT D pins to Output for LEDs
	DDRB = 0xFF;//Set all PORT B pins to Output for LCD
	//initialize variables
	redVal = 0;
	//i2c config
	usiTwiSlaveInit(0b00010000);
	sei();//Enable interrupts
}
void writeData(void)
{
	setParallel(redVal);
}
