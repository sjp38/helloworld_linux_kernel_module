// SPDX-License-Identifier: GPL-2.0

#define pr_fmt(fmt) "pr_vma: " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/sched/signal.h>

static void pr_vmas(void)
{
	struct task_struct *task;
	struct vm_area_struct *vma;
	struct mm_struct *mm;

	for_each_process(task) {
		pr_info("%s [%d]\n", task->comm, task->pid);
		mm = task->mm;
		if (!mm)
			continue;
		down_read(&mm->mmap_sem);
		vma = mm->mmap;

		while (vma) {
			pr_info("%012lx-%012lx", vma->vm_start, vma->vm_end);
			vma = vma->vm_next;
		}
		up_read(&mm->mmap_sem);
		pr_info("\n");
	}
}

static int __init pr_vma_init(void)
{
	pr_info("init\n");
	pr_vmas();
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
