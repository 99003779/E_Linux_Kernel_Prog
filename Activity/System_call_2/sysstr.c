#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/syscall.h>
#include<stdlib.h>

 
int main()
{
	char stri [256] ="abcdef";
	printf("the systemcall is %ld \n", syscall(402, stri));
	return 0;

}
