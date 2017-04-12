#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <asm/uaccess.h>

#define DEVICEN "charDevice"
#define CLASSN "charClass"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SP");
MODULE_DESCRIPTION("Character linux device driver");


static int mnum;
static struct class *charcls=NULL;
static struct device *chardev=NULL;
static int ucont=0;
static char mbuff[255]={0};
static int sizeofmsg;

static int char_open(struct inode *inode , struct file *filep);
static ssize_t char_read(struct file *filep , char *buff , size_t count , loff_t *offp );
static ssize_t char_write(struct file *filep , const char *buff , size_t count , loff_t *offp );
static int char_release(struct inode *inode , struct file *filep); 

/* C99 way of assigning to elements of a structure,
 */
static struct file_operations fops={  
	                                  .owner=THIS_MODULE,
	                                  .open=char_open,
	                                  .read=char_read,
	                                  .write=char_write,
	                                  .release=char_release
								  };

static int __init my_init(void)
{
	mnum=register_chrdev(0 , DEVICEN , &fops);

	if(mnum < 0)
	{
		printk(KERN_ALERT "Character driver is not register");
		printk(KERN_ALERT "Errorneous major number %d" , mnum);
		return -1;
	}
	printk(KERN_ALERT "Character driver is register using major number: %d", mnum );

	charcls=class_create(THIS_MODULE , CLASSN);

	if(IS_ERR(charcls) )
	{
		unregister_chrdev(mnum , DEVICEN);
		printk(KERN_ALERT "Failed to Register device class");
		return PTR_ERR(charcls);
	}
	printk(KERN_INFO "Device Class register succefully");

	chardev=device_create(charcls , NULL , MKDEV(mnum , 0) , NULL , DEVICEN);

	if(IS_ERR(chardev) )
	{
		class_destroy(charcls);
		unregister_chrdev(mnum , DEVICEN);
		printk(KERN_ALERT "Failed to create device class");
		return PTR_ERR(chardev);
	}
	printk(KERN_INFO "Device Class created succefully");

	return 0;
}
static void __exit my_exit(void)
{
	device_destroy(charcls , MKDEV(mnum, 0 ));
	class_unregister(charcls);
	class_destroy(charcls);
	unregister_chrdev(mnum , DEVICEN);

	printk(KERN_ALERT "Driver unregister succefully \n");
}
static int char_open(struct inode *inode , struct file *filep)
{
	ucont++;
	printk(KERN_INFO "Device open %d times", ucont);

	return 0;
}
static int char_release(struct inode *inode , struct file *filep)
{
	ucont--;
	printk(KERN_INFO "Device succefully closed");
	return 0;
}

static ssize_t char_read(struct file *filep , char *buff , size_t count , loff_t *offp )
{
	int err;

	err=copy_to_user(buff , mbuff , sizeofmsg);

	if(err >= 0)
	{
		printk(KERN_INFO "Device sent %d character to the user\n", sizeofmsg);
		return (sizeofmsg=0);
	}
	else
	{
		printk(KERN_ALERT " Failed to sent %d charcter to the user \n",sizeofmsg);
		return -EFAULT;
	}

}
static ssize_t char_write(struct file *filep , const char *buff , size_t count , loff_t *offp )
{
	sprintf(mbuff , "%s(%ld letters)" , buff , count);
	sizeofmsg= strlen(mbuff);
	printk(KERN_INFO " Recived %ld charcter from the user\n", count);

	return count;
}

module_init(my_init);
module_exit(my_exit);