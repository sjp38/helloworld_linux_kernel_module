#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static void kill_time(void)
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

	kill_time();

	pr_info("sj: [after] utime %llu, stime %llu, gtime %llu\n",
			current->utime, current->stime, current->gtime);
}

/*
 * Use kthread to run a task on an isolated CPU
 */
#include <linux/kthread.h>

struct completion foo_completion;

int foo(void *info)
{

	kill_time();
	pr_info("sj: %s ran on cpu %d\n", __func__, smp_processor_id());
	complete(&foo_completion);

	return 0;
}

int run_kthread_on_cpu(void)
{
	struct task_struct *t;

	t = kthread_create(foo, NULL, "foo");
	kthread_bind(t, 42);
	if (!t)
		return -EINVAL;
	init_completion(&foo_completion);
	wake_up_process(t);
	wait_for_completion(&foo_completion);

	return 0;
}

static int hello_init(void)
{
	pr_info("sj: Hello world\n");
	return 0;
}

static void hello_exit(void)
{
	pr_info("sj: Goodbye world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("A Hello World Module");
