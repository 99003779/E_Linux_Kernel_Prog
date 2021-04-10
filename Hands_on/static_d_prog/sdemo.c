//sdemo.c – ref code for static module
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
int svar=100;
void sayHello(void);
static int __init sdemo_init(void)
{
	int i;
	for(i=1;i<=4;i++)
	printk("sdemo, i=%d\n",xvar);
	return 0;
}
static void __exit sdemi _exit(void) 
{
	printk("Bye,Leaving the world\n");
}
EXPORT_SYMBOL_GPL(svar);
EXPORT_SYMBOL_GPL(sayHello);
