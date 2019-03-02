// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/topology.h>

static int cpu_topology_init(void)
{
	int cpu, node;
	char cpus[nr_cpu_ids + 1];

	pr_info("Module is working on cpu %d/%d, node %d/%d\n",
			smp_processor_id(), nr_cpu_ids, numa_node_id(),
			nr_node_ids);

	for_each_node_with_cpus(node) {
		pr_info("node %d has %d cpus\n", node, nr_cpus_node(node));
		for_each_present_cpu(cpu)
			cpus[cpu] = cpu_to_node(cpu) == node ? 'o' : ' ';
		cpus[cpu + 1] = '\0';
		pr_info("mask: [%s]\n", cpus);
	}

	return 0;
}

static void cpu_topology_exit(void)
{
	return;
}

module_init(cpu_topology_init);
module_exit(cpu_topology_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("An example for cpu topology");
