// SPDX-License-Identifier: GPL-2.0

#define pr_fmt(fmt) "fileio: " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init fileio_init(void)
{
	pr_info("init\n");
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
