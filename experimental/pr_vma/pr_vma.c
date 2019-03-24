// SPDX-License-Identifier: GPL-2.0

#define pr_fmt(fmt) "pr_vma: " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

static int __init pr_vma_init(void)
{
	pr_info("init\n");
	return 0;
}

static void __exit pr_vma_exit(void)
{
	pr_info("exit\n");
}

module_init(pr_vma_init);
module_exit(pr_vma_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("A VMA Printer Module");
