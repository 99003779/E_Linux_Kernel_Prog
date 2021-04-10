#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/errno.h>
#include <linux/unistd.h>
#include <linux/delay.h>



static struct task_struct *task1;
static struct task_struct *task2;
int val = 100;
const int max = 20;

static int thread_one(void *pargs)
{
	int i=0;
	for(i=1; i<=max; i++)
	{
		printk("Thread A--%d\n", i++);
		if(kthread_should_stop())
			break;
		msleep(1000);
	}
	do_exit(0);
	return 0;
}

static int thread_two(void *pargs)
{
	int i=0;
	for(i=1; i<=max; i++)
	{
		printk("Thread B--%d\n", i++);
		if(kthread_should_stop())
			break;
		msleep(2000);
	}
	do_exit(0);
	return 0;
}


static int __init tdemo_init(void)
{	
    task1 = kthread_run(thread_one, NULL, "Thread_A");
    //thread create+wakeup process
    task2 = kthread_run(thread_two, NULL, "Thread_B");
    
    return 0;
}
   
    
    
static void __exit tdemo_exit(void) 
{	
	if(task1)
		kthread_stop(task1);
	
	if(task2)
		kthread_stop(task2);
}

module_init(tdemo_init);
module_exit(tdemo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("Parameter demo Module");
