// SPDX-License-Identifier: GPL-2.0

#define pr_fmt(fmt) "hello: " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_init(void)
{
	pr_info("Hello world\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("Goodbye world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("A Hello World Module");
