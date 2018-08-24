// SPDX-License-Identifier: GPL-2.0+

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static void consume_time(void)
{
	unsigned long i;
	volatile unsigned long sum;

	for (i = 0, sum = 0; i < 500000000; i++)
		sum += i;

	pr_info("sj: time killed for sum %lu\n", sum);
}

/*
 * Count cpu time of this kernel thread.
 *
 * NOTE: CONFIG_TICK_CPU_ACCOUNTING should be ON
 */
#include <linux/sched.h>

void count_cputime(void)
{
	pr_info("sj: Hello world\n");
	pr_info("sj: [before] utime %llu, stime %llu, gtime %llu\n",
			current->utime, current->stime, current->gtime);

	consume_time();

	pr_info("sj: [after] utime %llu, stime %llu, gtime %llu\n",
			current->utime, current->stime, current->gtime);
}

static int modinit(void)
{
	pr_info("sj: Hello world\n");
	count_cputime();
	return 0;
}

static void modexit(void)
{
	pr_info("sj: Goodbye world\n");
}

module_init(modinit);
module_exit(modexit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("CPU time read example module");
