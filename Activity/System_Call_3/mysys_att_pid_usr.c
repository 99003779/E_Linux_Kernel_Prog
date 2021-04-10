#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/syscall.h>
#include<stdlib.h>

int main()
{

	printf("the systemcall for process list pid and ppid is %ld \n", syscall(403));
	return 0;

}
