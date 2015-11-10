#include <unistd.h> //sleep
#include <stdint.h> //uint16_t etc.
#include <stdio.h> //printf
#include <wiringPiI2C.h>
#include <stdlib.h> //exit
#include <math.h>

#include "gyro.h"

int main (void)
{
	int fd =	initMPU();
	for(int i = 0; i < 10;i++)
	{
		double x = readAccX(fd);
		double y = readAccY(fd);
		double z = readAccZ(fd);
		double all = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
		printf("temperature is: %6.3f°C\t x=%6.3f y=%6.3f z=%6.3f all=%6.3f\n",readTemp(fd),x,y,z,all);
		sleep(1);
	}
	return 0;
}
int initMPU()
{
	int fd =  wiringPiI2CSetup(I2C_ADDRESS);
	if(fd < 0)
	{
		printf("Error while init, could not connect to device\n");
		exit(-1);
	}
	uint8_t data = 128;//reset device
	int result = wiringPiI2CWriteReg8(fd,PWR_MGMT_1,data);
	if(result < 0)
	{
		printf("Error while init, could not reset device\n");
		exit(-1);
	}
	data = 0;//Always on, Temp enabled
	result = wiringPiI2CWriteReg8(fd,PWR_MGMT_1,data);
	if(result < 0)
	{
		printf("Error while init, could not start  device\n");
		exit(-1);
	}
	printf("Sleeping 1 second to star mesurement...");
	fflush(stdout);
	sleep(1);
	printf("...continuing\n");
	return fd;
}
double readTemp(int dev)
{
	uint8_t high = wiringPiI2CReadReg8(dev,0x41);
	uint8_t low  = wiringPiI2CReadReg8(dev,0x42);
	int16_t data = (high << 8) | low;
	double d = data;
	d /= 340;
	d +=36.53;	
	return d;
}
double readAccX(int dev)
{
	uint8_t high = wiringPiI2CReadReg8(dev,0x3B);
	uint8_t low  = wiringPiI2CReadReg8(dev,0x3C);
	int16_t data = (high << 8) | low;
	data = ~data;
	data += 1;
	double accPerBit = 9.81/16384;
	return accPerBit*data;
}
double readAccY(int dev)
{
	uint8_t high = wiringPiI2CReadReg8(dev,0x3D);
	uint8_t low  = wiringPiI2CReadReg8(dev,0x3E);
	int16_t data = (high << 8) | low;
	data = ~data;
	data += 1;
	double accPerBit = 9.81/16384;
	return accPerBit*data;
}
double readAccZ(int dev)
{
	uint8_t high = wiringPiI2CReadReg8(dev,0x3F);
	uint8_t low  = wiringPiI2CReadReg8(dev,0x40);
	int16_t data = (high << 8) | low;
	data = ~data;
	data += 1;
	double accPerBit = 9.81/16384;
	return accPerBit*data;
}
