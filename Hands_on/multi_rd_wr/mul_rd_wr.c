#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd, nbytes;

	fd=open("/dev/psample0", O_RDWR);
	if(fd<0) 
	{
		perror("open");
	}
	char str[50]="Hello This is Neha";
	nbytes=write(fd,str,7);
	if(nbytes<0) 
	{
		perror("write");
	}
	char wbuf[32];
	int maxlen=32;
	memset(str, '$', 12);
	nbytes=write(fd, wbuf, maxlen);
	memset(str, '&', 12);
	nbytes=write(fd, wbuf, maxlen);
	char rbuf[32];
	//int maxlen=10;
	while(1)
	{
		nbytes=read(fd,rbuf,maxlen);
		if(nbytes<0) 
		{
			perror("write");
		}
		if (nbytes==0)
			break;
		write(1,wbuf,maxlen);
	}
	//write(1,wbuf,maxlen); //(or) buf[nbytes]='\0'; 
	close(fd);
	return 0;
}
