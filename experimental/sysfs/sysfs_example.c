// SPDX-License-Identifier: GPL-2.0
/*
 * NOTE: The code is mainly stalled from samples/kobject/kobject-example.c in
 * the Linux source tree.
 */
#define pr_fmt(fmt) "sysfs-exmaple: " fmt

#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>

static int foo;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
		char *buf)
{
	return sprintf(buf, "%d\n", foo);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	int ret;

	ret = kstrtoint(buf, 10, &foo);
	if (ret < 0)
		return ret;

	return count;
}

static struct kobj_attribute foo_attribute =
	__ATTR(foo, 0664, foo_show, foo_store);

static struct attribute *attrs[] = {
	&foo_attribute.attr,
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

static struct kobject *example_kobj;

static int sysfs_example_init(void)
{
	int ret;

	example_kobj = kobject_create_and_add("sysfs_example", NULL);
	if (!example_kobj)
		return -ENOMEM;

	ret = sysfs_create_group(example_kobj, &attr_group);
	if (ret)
		kobject_put(example_kobj);

	pr_info("/sys/sysfs_example/foo has created\n");
	return ret;
}

static void sysfs_example_exit(void)
{
	kobject_put(example_kobj);
	pr_info("/sys/sysfs_example/ has removed\n");
}

module_init(sysfs_example_init);
module_exit(sysfs_example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SeongJae Park");
MODULE_DESCRIPTION("An example for pcpu variable");
