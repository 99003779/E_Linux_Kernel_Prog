#include <linux/delay.h>
#include <linux/init.h>
#include<linux/slab.h>
#include<linux/semaphore.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include<linux/list.h>


struct thrd 
{
	int x;
	int y;
	int z;
	struct list_head entry;
};
LIST_HEAD(mylist);
int N = 5;
int count = 0;
void printdata(void) 
{
	struct list_head* pcur;
	struct sample *ps;
	list_for_each(pcur,&mylist) 
	{
		ps=list_entry(pcur, struct thrd,entry); //container_of
		printk("%d\n %d\n",ps->x,ps->y);
	}
}

 
static struct task_struct *task1;
static struct task_struct *task2;
static struct task_struct *task3;

int val=100;
const int max=10;

static DEFINE_SEMAPHORE(s1);
static DEFINE_SEMAPHORE(s2);
static DEFINE_SEMAPHORE(s3);

static int thread_one(void *pargs)
{

	int i;
	printk("Welcome to Thread A");
	down_interruptible(&s3);
	down_interruptible(&s2);
	printdata();

	up(&s3);
	up(&s2);

	do_exit(0);
	return 0;
}


static int thread_two(void *pargs)
{
	struct thrd *ps;
	int i;
	printk("Welcome to thread B");
	down_interruptible(&s1);
	for(i=1;i<=N;i++)
	{
		ps=kmalloc(sizeof(struct thrd), GFP_KERNEL);
		ps->x=i*100;
		ps->y=i*100+10;
		list_add_tail(&ps->entry, &mylist);


		if(kthread_should_stop())
		break;
	}
	up(&s1);
	up(&s2);
	do_exit(0);
	return 0;

}

static int thread_three(void *pargs)
{
	struct thrd *ps;
	int i;
	printk("Welcome to Thread C");
	down_interruptible(&s2);
	down_interruptible(&s1);
	for(i=1;i<=N;i++)
	{
		ps=kmalloc(sizeof(struct thrd), GFP_KERNEL);
		ps->x=i*100;
		ps->y=i*100+10;
		list_add_tail(&ps->entry, &mylist);
		if(kthread_should_stop())
		break;
	}
	up(&s1);
	up(&s2);
	up(&s3);
	do_exit(0);
	return 0;

}

static int __init thread_init(void)
{
	sema_init(&s1,1);
	sema_init(&s2,0);
	sema_init(&s3,0);
	task1=kthread_run(thread_one, NULL, "thread_A");
	//kthread_create + wake_up_process
	task2=kthread_run(thread_two, NULL, "thread_B");
	task3=kthread_run(thread_three, NULL, "thread_C");
	return 0;

}

static void __exit thread_exit(void)
{
	struct list_head *pcur,*pbak;
	struct sample *ps;
	printk("EXIT");
	list_for_each_safe(pcur,pbak, &mylist)
	{
		ps=list_entry(pcur,struct sample, entry); //container_of
		kfree(ps);
	}
	printdata();
	printk("EMPTY");
}

module_init(thread_init);
module_exit(thread_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neha");
MODULE_DESCRIPTION("3 Threads to list");