#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

#define BUFFERL 256

static char receive[BUFFERL];

int main()
{
	int ret,fd;
	char stringTosend[BUFFERL];

	printf("Strating device testing code\n");
	fd=open("/dev/charDevice",O_RDWR);

	if(fd < 0)
	{
		perror("Failed to open device\n");
		return errno;
	}

	printf("Type in short string to send the kernel module : \n");
	gets(stringTosend);
	ret=write(fd, stringTosend , strlen( stringTosend) );

	if( ret < 0)
	{
		perror("Filed to write the message to the device");
		return errno;
	}

	printf("press ENTER read back from the device\n");
	getchar();

	printf("Reading from the device..\n");
	ret=read(fd , receive , BUFFERL);

	if(ret < 0)
	{
		perror("Failed to read from the message from the device \n");
		return errno;
	}

	printf("The recieve message is : %s \n",receive);	

	printf("End of program \n");
	close(fd);
	return 0;
}