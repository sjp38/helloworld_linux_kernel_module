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
	struct mm_struct *mm;
	struct rb_root *root;
	struct rb_node *nd;
	unsigned long prev_end;

	for_each_process(task) {
		prev_end = 0;
		pr_info("%s [%d]\n", task->comm, task->pid);
		mm = task->mm;
		if (!mm)
			continue;
		down_read(&mm->mmap_sem);

		root = &mm->mm_rb;
		for (nd = rb_first(root); nd; nd = rb_next(nd)) {
			struct vm_area_struct *vma;

			vma = rb_entry(nd, struct vm_area_struct, vm_rb);
			if (vma->vm_start > vma->vm_end) {
				pr_err("Start %lx > end %lx\n",
						vma->vm_start, vma->vm_end);
				break;
			}

			if (prev_end > vma->vm_start) {
				pr_err("Prev end %lx < start %lx\n",
						prev_end, vma->vm_start);
				break;
			}
			prev_end = vma->vm_end;
			vma = vma->vm_next;
		}
		up_read(&mm->mmap_sem);
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
