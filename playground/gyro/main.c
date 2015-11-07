#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
int main(void)
{
	printf("Starting to open I2C Gyro\n");
	int fd;
	if((fd=open(expander.I2CBus, O_RDWR)) < 0)
	{
		perror("Failt to open i2c bus\n");
		exit(1);
	}
	if(ioctl(fd,I2C_SLAVE, expander.adress) < 0 )
	{
		perror("Failed to acquire bus access and/or talk to slave\n");
	}

}
