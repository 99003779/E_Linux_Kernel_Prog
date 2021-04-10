#include<linux/syscalls.h>
#include<linux/kernel.h>
SYSCALL_DEFINE0(mytestcall)
{
	printk("This is my first system call\n");
	return 0;
}
