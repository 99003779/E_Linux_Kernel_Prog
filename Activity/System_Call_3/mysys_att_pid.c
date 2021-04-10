#include<linux/syscalls.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/linkage.h>
#include<linux/unistd.h>

 
SYSCALL_DEFINE0(mysl)
{  

	struct task_struct *proces;
 
    	for_each_process(proces) 
    	{
 
    		printk( "Process: %s\n PID_Number: %ld\n Process State: %ld\n Priority: %ld\n RT_Priority:%ld\n Static Priority: %ld\n Normal 			Priority: %ld\n",proces->comm,(long)task_pid_nr(proces),(long)proces->state,(long)proces->prio,(long)proces->rt_priority,(long)proces->static_prio,(long)proces->normal_prio);
  
  
   		if(proces->parent) 
      		printk("Parent process is: %s,PID_Number is: %ld",proces->parent->comm, (long)task_pid_nr(proces->parent));
 
	}
 	return 0;
}
