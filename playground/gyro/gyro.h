#ifndef GYRO_H
	#define GYRO_H
	#define I2C_ADDRESS 0x68
	#define PWR_MGMT_1 0x6B
	double readTemp(int);//file descriptor
	double readAccX(int);//file descriptor
	double readAccY(int);//file descriptor
	double readAccZ(int);//file descriptor
	int initMPU();//returns file descriptor
#endif /*GYRO_H*/
