#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>

static char *kbuf;
static dev_t first;
static unsigned int count = 5;
static int my_major = 700,my_minor = 0;
static struct cdev *my_cdev;

#define MYDEV_NAME "Mychrdev"
#define KBUF_SIZE (size_t) ((10)*PAGE_SIZE)

//MODULE_LICENSE("Dual BSD/GPL");


static int mychrdev_open(struct inode *inode, struct file *file) //inode ???
{
	printk(KERN_INFO "Opening device %s: \n\n",MYDEV_NAME);
	return 0;
}

static int mychrdev_release(struct inode *inode, struct file *file) //inode ???
{
	printk(KERN_INFO "Opening device %s: \n\n",MYDEV_NAME);
	return 0;
}

static ssize_t mychrdev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes = lbuf - copy_to_user(buf, kbuf + *ppos, lbuf);
	*ppos += nbytes;

	printk(KERN_INFO "Read device %s nbytes = %d,ppos =%d: \n\n",MYDEV_NAME, nbytes, (int)*ppos);

	return nbytes;
}

static ssize_t mychrdrv_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
	*ppos += nbytes;

	printk(KERN_INFO "Write device %s nbytes = %d,ppos =%d: \n\n",MYDEV_NAME, nbytes, (int)*ppos);
	return nbytes;
}

static const struct file_operations mycdev_fops = {

	.owner = THIS_MODULE,
	.read = mychrdev_read,
	.write = mychrdrv_write,
	.release = mychrdev_release
};

static int __init init_chrdev(void)
{
	printk(KERN_ALERT " %s\n",__FUNCTION__);
	kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL); //GFP_KERNEL ???
	
	first = MKDEV(my_major, my_minor);	//MKDEV ???
	register_chrdev_region(first,count,MYDEV_NAME);	

	my_cdev = cdev_alloc();
	
	cdev_init(my_cdev, &mycdev_fops);
	cdev_add(my_cdev,first,count);	

	return 0;
}

static void __exit cleanup_chrdev(void)
{
printk(KERN_ALERT " %s\n",__FUNCTION__);
}
module_init(init_chrdev);
module_exit(cleanup_chrdev);