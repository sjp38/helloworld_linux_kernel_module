// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

struct data {
	int foo;
};

DEFINE_PER_CPU(struct data, pcpdat);

static int pcpu_init(void)
{
	int cpu;

	for_each_online_cpu(cpu) {
		pr_info("data for cpu %d: %d\n", cpu, per_cpu(pcpdat, cpu).foo);
		per_cpu(pcpdat, cpu).foo = cpu;
	}
	pr_info("sj: Hello world\n");
	return 0;
}

static void pcpu_exit(void)
{
	int cpu;

	for_each_online_cpu(cpu)
		pr_info("data for cpu %d: %d\n", cpu, per_cpu(pcpdat, cpu).foo);

	pr_info("sj: Goodbye world\n");
}

module_init(pcpu_init);
module_exit(pcpu_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("An example for pcpu variable");
