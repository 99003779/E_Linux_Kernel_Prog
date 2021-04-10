#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main()
{
	printf("1 : %d\n", syscall(399));
	printf("2 : %d\n", syscall(400, 1));
	printf("3 : %d\n", syscall(401, 2, 3));
	return 0;
}
