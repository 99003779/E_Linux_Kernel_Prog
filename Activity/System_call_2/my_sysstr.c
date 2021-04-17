#include<linux/syscalls.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/linkage.h>

 
SYSCALL_DEFINE1(mys, char*, stri)
{  
	int n;
	char buf[100];
 
	n=copy_from_user(buf,stri,100);
 
	if(n)
	{
		printk("abcdef");
		-EFAULT;
 	}
 	printk("my systemcall string is %s\n", buf);
 
 	return 0;
}
 
