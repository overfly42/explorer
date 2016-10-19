#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

//pi@flybot ~/explorer/mod_engine/src $ ls ../../mod_microcontroller/src/
//usiTwiSlave.c  usiTwiSlave.h  usiTwiSlave.o
#include "../../mod_microcontroller/src/usiTwiSlave.h"
int main(void)
{
   usiTwiSlaveInit(0b00010000);
   sei();//Enable interrupts

	DDRD = 0xFF;
	PORTD = 1;
	DDRA = 0xFF;
	int i;
	uint8_t PWM_val = 0;		// 8-bit PWM value
   uint8_t up_dn = 0;		// up down count flag
	uint8_t mask = 127;    
	uint8_t buf = 0;
    DDRB   |= (1 << PB2);                   // PWM output on PB2
    TCCR0A = (1 << COM0A1) | (1 << WGM00);  // phase correct PWM mode
    TCCR0B = (1 << CS01);   // clock source = CLK/8, start PWM
	while(1)
	{
		buf = rxbuffer[0];
		up_dn = buf & (1<<7);
		PWM_val = buf & mask;
		if(up_dn)
		{
			for(i=0;i<128;i++)
				if(i<PWM_val)
					PORTA = 1;
				else
					PORTA = 0;
		}
		else
		{
			for(i=0;i<128;i++)
				if(i<PWM_val)
					PORTA = 2;
				else
					PORTA = 0;
		}
	}	
while(1)
	{
//		if((PWM_val == 255) || (PWM_val == 0)) {
  //          up_dn ^= 0x01;      // toggle count direction flag
  //      }
        _delay_ms(5);
        //OCR0A  = PWM_val;       // write new PWM value
		OCR0A = rxbuffer[0];
   //     if (up_dn) {            // increment or decrement PWM value
   //         PWM_val++;
   //     }
   //     else {
   //         PWM_val--;
   //     }
	}

	while(1)
	{
		int on=rxbuffer[0];
		txbuffer[0] = on;
		for(i=0;i<20;i++)
		{
			if(i<on)PORTD = 2;
			else	  PORTD = 1;
			_delay_ms(1);
		}
//		int off = 255 - on;
//		PORTD += 2;
//		for(i = 0;i<on;i++)
//			_delay_ms(1);
//		PORTD += 2;
//		for(i = 0; i<off;i++)
//			_delay_ms(1);
	}
}
