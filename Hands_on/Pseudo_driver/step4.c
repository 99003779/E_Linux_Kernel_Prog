#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define MAX_SIZE 1024

struct cdev cdev;
struct device *pdev;
struct class *pclass;

int ndevices=1;
int i=0;
dev_t pdevid;
unsigned char *pbuffer;
int rd_offset=0;
int wr_offset=0;
int buflen=0;
int ret=0;


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
    
    //Read method:
    if(buflen==0)
    {
    	printk("buffer is empty\n");
    	return 0;
    }
    rcount = size;
    if(rcount > buflen)
    	rcount = buflen;      //min of buflen, size
    	
    ret = copy_to_user(buf, pbuffer + rd_offset,rcount);
    
    if(ret)
    {
    	printk("copy to user failed\n");
    	return -EFAULT;
    }
    
    
    rd_offset += rcount;
    buflen -= rcount;
    
    return rcount;
}


ssize_t pseudo_write(struct file * file, const char __user * buf , size_t size, loff_t * off)
{
	int wcount=0;
    
    //write method:
    if(wr_offset >= MAX_SIZE)
    {
    	printk("buffer is full\n");
    	return -ENOSPC;
    }
    wcount = size;
    if(wcount > MAX_SIZE - wr_offset)
    	wcount = MAX_SIZE - wr_offset;       ///min
    ret=copy_from_user(pbuffer + wr_offset,buf, wcount);
    
    if(ret)
    {
    printk("copy from user failed\n");
    return -EFAULT;
    }
    wr_offset += wcount;
    buflen += wcount;
    
    return wcount;
}

struct file_operations fops = {
    .open = pseudo_open,
    .release = pseudo_close,
    .write = pseudo_write,
    .read = pseudo_read
};

 
static int __init psuedo_init(void)
{	
    int ret;
    int i=0;
    pclass = class_create(THIS_MODULE, "pseudo_class");
    ret=alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");
    pdev = device_create(pclass, NULL, pdevid, NULL, "psample%d", i);
    pbuffer = kmalloc(MAX_SIZE, GFP_KERNEL);
    if(ret) 
    {
        printk("Pseudo: Failed to register driver\n");
        return -EINVAL;
    }
    

    
    cdev_init(&cdev, &fops);
    kobject_set_name(&cdev.kobj,"pdevice%d",i);
    ret = cdev_add(&cdev, pdevid, 1);
    
    printk("Successfully registered,major=%d, minor=%d\n",MAJOR(pdevid), MINOR(pdevid));
    printk("Pseudo Driver Sample..welcome\n");
    
    printk("count is %d",rd_offset);
    
    return 0;
}
static void __exit psuedo_exit(void) 
{
    
    unregister_chrdev_region(pdevid, ndevices);
    printk("Pseudo Driver Sample..Bye\n");
    cdev_del(&cdev);
    device_destroy(pclass, pdevid);
    class_destroy(pclass);
    kfree(pbuffer);
}

module_init(psuedo_init);
module_exit(psuedo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("Parameter demo Module");
