#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

//LCD
#define P_ENABLE 1
#define P_REG_SELECT 2
#define P_READWRITE 4
#define S_ENABLE 0
#define S_REG_SELECT 1
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
uint8_t bitMask(uint8_t pos, uint8_t val);

int main(void)
{
	DDRD = 0xFF;//Set all PORT D pins to Output for LEDs
	DDRB = 0xFF;//Set all PORT B pins to Output for LCD
	uint8_t i = 0;
	i=0;
	init();
	while(1)
	{
	//	setParallel(i++);
		setLetter(letter[i]);
		i++;
		i = i>17?0:i;
		_delay_ms(100);
	}
}
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
	PORTB = 0;
	setParallel(1);//Clear Data;
	writeData();
	setParallel(2);//Return home, with DRam and Display
	writeData();
	//8: Display/Cursor Control
	//4: Display
	//2: Cursor
	//1: Curosr Blink
	setParallel(8 | 4 | 2 | 1);
	writeData(); 
	//32: Function Set,
	//16: 8Bit Data
	//8: 2Lines
	//4: 5x10 Dots
	setParallel(32 | 16 | 8 | 4 );
	writeData();
/* Works more or less
	//Set Display Control to defined Values
	PORTB = 0;//There should nothing active on PORT B on this time
	setParallel(32 | 16 | 8);//See Page 44	
	writeData();
	setParallel(8 | 4 | 2);
	writeData();
	setParallel(4 | 2 );
	writeData();
	PORTB |= P_REG_SELECT;	
	//Clear Display
	setParallel(1);
	writeData();
*/	
}
uint8_t bitMask(uint8_t pos, uint8_t val)
{
	uint8_t data = 0;
	uint8_t i;
	for(i = 0;i<8;i++)//8 Bit
		data |= (i == pos ? val : 1) << i;
	return data;
}
void writeData(void)
{
		PORTB |= P_ENABLE;//Enable Write to Display
		_delay_ms(100);
		PORTB &= 0xFE;//First disable
			
}
