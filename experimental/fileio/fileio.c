// SPDX-License-Identifier: GPL-2.0

#define pr_fmt(fmt) "fileio: " fmt

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static void fileio_example(void)
{
	struct file *f;
	char buffer[256];
	ssize_t sz;
	loff_t pos;

	f = filp_open("/hello_lkm_test", O_CREAT | O_RDWR, 0600);
	if (IS_ERR(f)) {
		pr_err("Failed to open file\n");
		return;
	}

	sz = kernel_read(f, buffer, 256, &pos);
	if (sz == 0)
		pr_info("nothing read\n");
	else
		pr_info("read %s\n", buffer);

	memcpy(buffer, "hello fileio\n", 256);
	sz = kernel_write(f, buffer, strnlen(buffer, 256), &pos);
	if (sz != strnlen(buffer, 256))
		pr_info("failed to write the string\n");
	else
		pr_info("written the string %s\n", buffer);

	filp_close(f, NULL);
}

static int __init fileio_init(void)
{
	pr_info("init\n");
	fileio_example();
	return 0;
}

static void __exit fileio_exit(void)
{
	pr_info("exit\n");
}

module_init(fileio_init);
module_exit(fileio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("A File I/O Example");
