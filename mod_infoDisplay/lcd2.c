#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

//LCD
#define P_ENABLE 1
#define P_REG_SELECT 2
#define P_READWRITE 4
#define S_ENABLE 0
#define S_REG_SELECT 4
#define S_READWRITE 2
#define DATA_REG 1
#define FUNC_REG 0
#define DATA_READ 1
#define DATA_WRITE 0


//Shift Register
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

void setParallel(uint8_t data);
void setLetter(uint8_t data);
void init(void);
void writeData(void);
uint8_t letter[17];//16 TestLetter for LCD 

int main(void)
{
	DDRD = 0xFF;//Set all PORT D pins to Output for LEDs
	DDRB = 0xFF;//Set all PORT B pins to Output for LCD
	uint8_t i = 0;
	i=0;
	init();
	_delay_ms(100);
	while(1)
	{
		for(i=0;i<17;i++)
		{	setLetter(letter[i]);
		_delay_ms(200);
		}
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

void setLetter(uint8_t data)
{
	PORTB |= P_REG_SELECT; //Data reg is 1
	//Remove the enable
	setParallel(data);//Setting via Parallel Output
	writeData();
}
void init (void)
{
	uint8_t i = 0;
	//setting the letters
	letter[i++] = 'I';//0b01000001;
	letter[i++] = ' ';//0b01000010;
	letter[i++] = 'L';//0b01000011;
	letter[i++] = 'O';//0b01000100;
	letter[i++] = 'V';//0b01000101;
	letter[i++] = 'E';//0b01000110;
	letter[i++] = ' ';//0b01000111;
	letter[i++] = 'M';//0b01001000;
	letter[i++] = 'Y';//0b01001001;
	letter[i++] = ' ';//0b01001010;
	letter[i++] = 'W';//0b01001011;
	letter[i++] = 'I';//0b01001100;
	letter[i++] = 'N';//0b01001101;
	letter[i++] = 'N';//0b01001110;
	letter[i++] = 'I';//0b01001111;
	letter[i++] = 'E';//0b01010000;
	letter[i++] = ' ';
	//Init the Display
	_delay_ms(300);
	PORTB = 0;
	setParallel(48);
	writeData();
	_delay_ms(300);
	setParallel(48);
	writeData();
	_delay_ms(300);
	setParallel(48);
	writeData();
	_delay_ms(300);
	setParallel(60);
	writeData();
	_delay_ms(300);
	setParallel(8);
	writeData();
	_delay_ms(300);
	setParallel(0);
	writeData();
	_delay_ms(300);
	setParallel(12);
	writeData();
	_delay_ms(300);
	setParallel(15);
	writeData();
	_delay_ms(300);
	setParallel(2);
	writeData();
	_delay_ms(300);
}
void writeData(void)
{
		PORTB |= P_ENABLE;//Enable Write to Display
		_delay_ms(200);
		PORTB &= 0xFE;//First disable
			
}
