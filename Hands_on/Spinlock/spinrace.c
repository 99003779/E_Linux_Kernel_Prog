#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/time.h>
#include <linux/unistd.h>
#include <linux/sched/signal.h>

static struct task_struct *task1;
static struct task_struct *task2;

int maxcount=50;
static int val = 100;
module_param(maxcount, int, S_IRUGO);

static DEFINE_SPINLOCK(s1);
static DEFINE_SPINLOCK(s2);


static int thread_one(void *pargs)
{
	int i = 0;
	spin_lock(&s1);
	spin_lock(&s2);
	
	for(i=1; i <= maxcount; i++)
	{	
		val++;
		printk("Thread A %d",i);
		msleep(1000);
	}
	spin_unlock(&s1);
	spin_unlock(&s2);
	printk("stopping thread A\n");
	do_exit(0);
	return 0;
}

static int thread_two(void *pargs) 
{
	int i = 0; 
	for(i=1; i<=maxcount; i++)
	{	
		val--;
		printk("Thread B %d\n",i);
		msleep(500);
		//val--
		//if(kthread_should_stop())
		//break;
	}
	printk("stopping thread B\n");
	do_exit(0);
	return 0;
}

static int __init demo_init(void)
{
	spin_lock_init(&s2);
	task1 = kthread_run(thread_one, NULL, "thread_A");
	task2 = kthread_run(thread_two, NULL, "thread_B");
	printk("SPINLOCK sample--welcome\n");
	return 0;
}
static void __exit demo_exit(void)
{	
	/*if(task1)
      	kthread_stop(task1);
 	if(task2)
      	kthread_stop(task2);*/
	printk("Thread Demo, Leaving, val=%d\n",val);
	
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("NEHA");
MODULE_DESCRIPTION("Spinlock module");
