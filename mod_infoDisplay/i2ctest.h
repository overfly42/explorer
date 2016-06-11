#include <avr/io.h>
#ifndef buffer_size_
	#define buffer_size 5 
#endif

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
void init(void);
void writeData(void);

