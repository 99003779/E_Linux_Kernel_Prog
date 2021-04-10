#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/kfifo.h>

unsigned char *pbuffer;
int ndevices=1;


int i=0;
unsigned char *pbuffer;
int rd_offset=0;
int wr_offset=0;
int buflen=0;
int ret=0;

dev_t pdevid;

struct kfifo myfifo;
struct cdev cdev;
struct device *pdev;
struct class *pclass;

#define MAX_SIZE 1024

#define IOC_MAGIC 'p'
#define MY_IOCTL_LEN _IO(IOC_MAGIC, 1)
#define MY_IOCTL_AVAIL _IO(IOC_MAGIC, 2)
#define MY_IOCTL_RESET _IO(IOC_MAGIC, 3)


int pseudo_open(struct inode* inode , struct file* file)
{
    printk("Pseudo--open method\n");
    return 0;
}
int pseudo_close(struct inode* inode , struct file* file)
{
    printk("Pseudo--release method\n");
    return 0;
}
ssize_t pseudo_read(struct file * file, char __user * buf , size_t size, loff_t * off)
{
    int rcount;
char *tbuf;

    if(kfifo_is_empty(&myfifo))
    {
    	printk("Buffer is empty\n");
    	return 0;
    }
    rcount = size; 
    if(rcount > kfifo_len(&myfifo))
    	rcount = kfifo_len(&myfifo);
    	
    tbuf = kmalloc(rcount, GFP_KERNEL);
    kfifo_out(&myfifo, tbuf, rcount);
    
    ret = copy_to_user(buf, tbuf, rcount);
    
    kfree(tbuf);
    return rcount;
}


ssize_t pseudo_write(struct file * file, const char __user * buf , size_t size, loff_t * off)
{	
   unsigned int ret;
   char *tbuf;
    if (kfifo_is_full(&myfifo))
    {
    	printk("buffer is full\n");
    	return -ENOSPC;
    }
    int wcount = size;
    if (wcount > kfifo_avail(&myfifo)){
    	wcount = kfifo_avail(&myfifo);      //min
    	}
       tbuf=kmalloc(wcount, GFP_KERNEL);
    
    ret=copy_from_user(tbuf, buf, wcount);
    
    kfifo_in(&myfifo, tbuf, wcount);
    kfree(tbuf);
    return wcount;
}

static long pseudo_ioctl(struct file *file, unsigned int cmd, unsigned long arg) 
{
  printk("Pseudo--ioctl method\n");
  switch (cmd) 
  {
  	case MY_IOCTL_LEN:
    		printk("ioctl--kfifo length is %d\n", kfifo_len(&myfifo));
    		break;
  	case MY_IOCTL_AVAIL:
    		printk("ioctl--kfifo avail is %d\n", kfifo_avail(&myfifo));
    		break;
  	case MY_IOCTL_RESET:
    		printk("ioctl--kfifo got reset\n");
    		kfifo_reset(&myfifo);
    		break;
  }
  return 0;
}


struct file_operations fops = {
		.open = pseudo_open,
		.release = pseudo_close,                
		.write = pseudo_write,
		.read = pseudo_read,
		.unlocked_ioctl = pseudo_ioctl
};

static int __init psuedo_init(void)
{	
    int ret;
    int i=0;
    pclass = class_create(THIS_MODULE, "pseudo_class");
    ret=alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");
    pbuffer = kmalloc(MAX_SIZE, GFP_KERNEL);
    kfifo_init(&myfifo,pbuffer, MAX_SIZE);
    cdev_init(&cdev, &fops);
    kobject_set_name(&cdev.kobj,"pdevice%d",i);
    ret = cdev_add(&cdev, pdevid, 1);
    pdev = device_create(pclass, NULL, pdevid, NULL, "psample%d", i);
    
    if (ret) 
    {
    	printk("Pseudo: Failed to register driver\n");
    	return -EINVAL;
    }
    
    
    
    printk("Successfully registered,major=%d, minor=%d\n",MAJOR(pdevid), MINOR(pdevid));
    printk("Pseudo Driver Sample..welcome\n");
    
    printk("count is %d",rd_offset);
    
    return 0;
}





static void __exit psuedo_exit(void) 
{
    
    unregister_chrdev_region(pdevid, ndevices);
    cdev_del(&cdev);
    device_destroy(pclass, pdevid);
    class_destroy(pclass);
    kfree(pbuffer);
    printk("Pseudo Driver Sample..Bye\n");
   
    //kfifo_free(kfifo);
}

module_init(psuedo_init);
module_exit(psuedo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("Parameter demo Module");








