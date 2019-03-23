// SPDX-License-Identifier: GPL-2.0

#define pr_fmt(fmt) "list-example: " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

struct entry {
	unsigned int value;
	struct list_head list;
};

static struct entry *new_entry(unsigned int value)
{
	struct entry *ret;

	ret = kmalloc(sizeof(struct entry), GFP_KERNEL);
	if (ret == NULL)
		return ret;
	ret->value = value;
	INIT_LIST_HEAD(&ret->list);

	return ret;
}

static void pr_the_list(struct list_head *list)
{
	struct entry *e;
	char buffer[256] = {0,};

	list_for_each_entry(e, list, list)
		snprintf(buffer + strlen(buffer), 256, "%u->", e->value);
	snprintf(buffer + strlen(buffer), 256, "NULL");
	pr_info("%s\n", buffer);
}

static int __init list_example_init(void)
{
	static LIST_HEAD(the_list);
	struct entry *es[3];
	struct entry *e, *next;
	int i;

	for (i = 0; i < 3; i++) {
		e = new_entry(i);
		es[i] = e;
		list_add(&e->list, &the_list);
		pr_info("added %d entry\n", i);
		pr_the_list(&the_list);
	}

	list_for_each_entry_safe(e, next, &the_list, list) {
		pr_info("Deleted %u\n", e->value);
		list_del(&e->list);
		kfree(e);
		pr_the_list(&the_list);
	}

	return 0;
}

static void __exit list_example_exit(void)
{
	pr_info("Exit\n");
}

module_init(list_example_init);
module_exit(list_example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("A List Example Module");
