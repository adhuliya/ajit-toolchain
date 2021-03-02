//Simple char device driver
///A simple character driver taht reverses a string written into it
//
// References:
//1: 	http://www.thegeekstuff.com/2013/07/write-linux-kernel-module/
//2: 	https://appusajeev.wordpress.com/2011/06/18/writing-a-linux-character-device-driver/



#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/fs.h>		//defines the file_operations structure
#include <linux/uaccess.h>
#include <linux/string.h> 	//for using string utilities


//every driver module has this metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neha Karanjkar");
MODULE_DESCRIPTION("A character driver that reverses a string written to it");


//callback functions that the driver must pass
//to the kernel when registering itself
static int     dev_open   (struct inode *, struct file *);
static int     dev_release(struct inode *, struct file *);
static ssize_t dev_read   (struct file * ,      char *, size_t, loff_t *);
static ssize_t dev_write  (struct file * ,const char *, size_t, loff_t *);


//Whoa!....what kind of C syntax is this?
//it seems to compile without any complaints by gcc!
static struct file_operations fops = 
{
	.read = dev_read,
	.open = dev_open,
	.write = dev_write,
	.release = dev_release,
};
//Okay...turns out, this is a special syntax (C99 standard)
//for setting arguments in a device driver. It is supported by
//most compilers including gcc. The fields that are not 
//explicitly set, are assigned NULL by gcc.



// Some buffers area for our character device:
static char  	buffer[100] ={0};
static short	readPos=0;
static int	times=0;
//variable to store major number
static int 	major_number=0;

int init_module(void)
{
	//lets register our deice driver
	int t = register_chrdev(89, "stringReverser", &fops);
	//passing major_num =0 makes kernel choose an appropriate
	//major_num and return it.
	// If a negative num is returned, it means error.
	if(t<0) 
	{
		printk(KERN_ALERT "stringReverser: Device Registration failed\n");
		return t;
	}
	else
	{
		printk(KERN_ALERT "stringReverser: Device Registration successful\n");
		major_number = 89;
		return 0;
	}
	return 0;
}

void cleanup_module(void)
{
	unregister_chrdev(major_number, "stringReverser");
	printk(KERN_ALERT "stringReverser: Cleaning Up\n");
}

static int     dev_open   (struct inode * i, struct file * filep)
{
	times++;
	printk(KERN_ALERT "stringReverser : Device opened %d times\n",times);
	return 0;

}

static int     dev_release(struct inode * i, struct file * filep)
{
	printk(KERN_ALERT "stringReverser : Device closed\n");
	return 0;
}
static ssize_t dev_read   (struct file *filep , char *buff, size_t len, loff_t *off)
{
	short count=0;
	printk(KERN_ALERT "stringReverser : Device read\n");
	while(len && (buffer[readPos]!=0))
	{
		put_user(buffer[readPos], buff++); //copy byte from kernel to user space
		count++;
		len--;
		readPos++;
	}
	return count; //return number of bytes copied
}

static ssize_t dev_write  (struct file *filep ,const char *buff, size_t len, loff_t *off)
{
	short ind = len-1;
	short count=0;
	printk(KERN_ALERT "stringReverser : dev_write() called with string = %s\n",buff);
	memset(buffer,0,100);
	readPos=0;
	while(len>0)
	{
		buffer[count++]=buff[ind--];
		len--;
		
	}
	return count;
}
module_init(init_module);
module_exit(cleanup_module);



