#define pr_fmt(fmt) "misc_dev_example: " fmt

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>

static char *magicword = "xxxxxxxxxxxx";
static const size_t len_magicword = 12;

/*
 * When the character device node is read from, your assigned id is returned to
 * the caller.
 */
static ssize_t mde_read(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	if (*ppos >= len_magicword)
		return 0;

	if (*ppos + count > len_magicword)
		count = len_magicword - *ppos;

	if (copy_to_user(buf, magicword + *ppos, count))
		return -EINVAL;
	*ppos += count;

	return count;
}

/*
 * When the character device node is written to, the data sent to the kernel
 * needs to be checked.  If it matches your assigned id, then return a correct
 * write return value.  If the value does not match your assigned id, return
 * the "invalid value" error value.
 */
static ssize_t mde_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	char input[256];

	if (*ppos >= len_magicword)
		return 0;

	if (*ppos + count > len_magicword)
		count = len_magicword - *ppos;

	copy_from_user(input, buf, count);
	if (strncmp(magicword + *ppos, input, count))
		return -EINVAL;
	*ppos += count;
	return count;
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
