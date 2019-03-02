#define pr_fmt(fmt) "misc_dev_example: " fmt

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>

static ssize_t mde_read(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	return -EINVAL;
}

static ssize_t mde_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	return -EINVAL;
}

static struct file_operations mde_dev_ops = {
	.owner = THIS_MODULE,
	.read = mde_read,
	.write = mde_write,
};

static struct miscdevice mde_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "a_misc_dev",
	.fops = &mde_dev_ops,
};

static int misc_dev_example_init(void)
{
	int ret;

	ret = misc_register(&mde_dev);
 	pr_info("Registered\n");
 	return 0;
}

static void misc_dev_example_exit(void)
{
	misc_deregister(&mde_dev);
 	pr_info("Unregistered\n");
}

module_init(misc_dev_example_init);
module_exit(misc_dev_example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("An example for misc device usage");
