#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
void MPUgetData(int);
void printBin(int16_t);
/* Suche nach I2C-Adressen */
void scan_i2c_bus(int device)
{
	int port, res;
	/* Adressbereich 7 Bit */
	for (port = 0; port < 127; port++)
	{
		if (ioctl(device, I2C_SLAVE, port) < 0)
			perror("ioctl() I2C_SLAVE failed\n");
		else
		{
			/* kann gelesen werden? */
			res = i2c_smbus_read_byte(device);
			if (res >= 0)
				printf("i2c chip found at: %x, val = %d\n", port, res);
		}
	}
}

int main(void)
{
	int device;
	unsigned long funcs;

	/* Geraetedatei oeffnen */
	printf("Opening device...");
	if ((device = open("/dev/i2c-1", O_RDWR)) < 0)
	{
		perror("open() failed");
		exit (1);
	}
	printf(" OK\n");

	/* Abfragen, ob die I2C-Funktionen da sind */
	if (ioctl(device,I2C_FUNCS,&funcs) < 0)
	{
		perror("ioctl() I2C_FUNCS failed");
		exit (1);
	}

	/* Ergebnis untersuchen */
	if (funcs & I2C_FUNC_I2C)
		printf("I2C\n");
	if (funcs & (I2C_FUNC_SMBUS_BYTE))
		printf("I2C_FUNC_SMBUS_BYTE\n");

	/* und Bus abscannen */
	scan_i2c_bus(device);

	MPUgetData(device);	
	return 0;
}

void MPUgetData(int fd)
{
	printf("Cycle Data\n");
	int size = 16*16;	
	if(ioctl(fd,I2C_SLAVE, 0x68) < 0)
	{
		printf("Failed to select device\n");
	}
	int8_t count = 0;
	int8_t* data = (int8_t*) malloc(size*sizeof(int8_t));
	memset(data,0,sizeof(data));
	printf("Reading %d Bytes-->",size);
	uint8_t reg = 0x41;
	if(write(fd,&reg,1) != 1)
	{
		printf("Fehler\n");
		return;
	}
	else
		printf("kein Fehler\n");
	count = read(fd,data,6);
	printf("Read: %d Bytes\n",count);
	printf("Data: ");
	int tmp;
	for (int i = 0; i < 2;i++)
	{
		tmp = data[i]&0xFF;
		printf("%x ",tmp);
	}
	printf("\n");
	int high = data[0]&0xFF;
	int low = data[1]&0xFF;
	int16_t val = 0;
	printf("High = %d und low = %d\n",high,low);
	printBin(high);
	printBin(low);
	val = high;
	printBin(val);
	val = val<<8;
	printBin(val);
	val |= low;
	printBin(val);
	double d = val;
	printf("d=%6.3f\n",d);
	d /= 340;
	printf("d=%6.3f\n",d);
	d +=36.53;
	printf("d=%6.3f\n",d);
	
	free(data);
	printf("\n");
//	for(int16_t i = 0; i < 32;i++)
//	{
//		printBin(i);
//		printf("\n");
//	}
}
void printBin(int16_t data)
{
	printf("Data=%5d -> bin=",data);
	for(int i = 15; i >= 0;i--)
		if(data & (1<<i))
			printf("1");
		else
			printf("0");
	printf("\n");
}
