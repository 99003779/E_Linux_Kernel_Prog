#include <linux/syscalls.h>
#include <linux/kernel.h>

SYSCALL_DEFINE0(my_syscall_0)
{
	printk("my_syscall_0\n");
	return 0;
}

SYSCALL_DEFINE1(my_syscall_1, int, a)
{
	printk("my_syscall_1 : %d\n", a);
	return 0;
}

SYSCALL_DEFINE2(my_syscall_2, int, a, int, b)
{
	printk("my_syscall_1 : %d, %d\n", a, b);
	return b;
}
