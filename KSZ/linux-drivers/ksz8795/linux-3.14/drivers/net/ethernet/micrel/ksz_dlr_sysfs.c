/**
 * Micrel DLR common sysfs code
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


static ssize_t dlr_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct ksz_sw *sw;
	struct semaphore *proc_sem;
	struct ksz_dlr_info *dlr;
	ssize_t len = -EINVAL;
	int proc_num;

	get_private_data(d, &proc_sem, &sw, NULL);
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	dlr = &sw->info->dlr;
	len = 0;
	proc_num = offset / sizeof(int);
	len = dlr->ops->sysfs_read(dlr, proc_num, len, buf);
	up(proc_sem);
	return len;
}

static ssize_t dlr_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct ksz_sw *sw;
	struct semaphore *proc_sem;
	struct ksz_dlr_info *dlr;
	ssize_t ret = -EINVAL;
	int num;
	int proc_num;

	num = get_num_val(buf);
	get_private_data(d, &proc_sem, &sw, NULL);
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	dlr = &sw->info->dlr;
	proc_num = offset / sizeof(int);
	ret = count;
	dlr->ops->sysfs_write(dlr, proc_num, num, buf);
	up(proc_sem);
	return ret;
}

#define DLR_ATTR(_name, _mode, _show, _store) \
struct device_attribute dlr_attr_##_name = \
	__ATTR(_name, _mode, _show, _store)

/* generate a read-only attribute */
#define DLR_RD_ENTRY(name)						\
static ssize_t show_dlr_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return dlr_show(d, attr, buf,					\
		offsetof(struct dlr_attributes, name));			\
}									\
static DLR_ATTR(name, S_IRUGO, show_dlr_##name, NULL)

/* generate a write-able attribute */
#define DLR_WR_ENTRY(name)						\
static ssize_t show_dlr_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return dlr_show(d, attr, buf,					\
		offsetof(struct dlr_attributes, name));			\
}									\
static ssize_t store_dlr_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return dlr_store(d, attr, buf, count,				\
		offsetof(struct dlr_attributes, name));			\
}									\
static DLR_ATTR(name, S_IRUGO | S_IWUSR, show_dlr_##name, store_dlr_##name)

DLR_RD_ENTRY(info);
DLR_WR_ENTRY(node);
DLR_WR_ENTRY(prec);
DLR_WR_ENTRY(interval);
DLR_WR_ENTRY(timeout);
DLR_WR_ENTRY(vid);
DLR_WR_ENTRY(state);
DLR_WR_ENTRY(port);
DLR_WR_ENTRY(test);
DLR_WR_ENTRY(req);
DLR_WR_ENTRY(resp);
DLR_WR_ENTRY(link);
DLR_WR_ENTRY(learn);
DLR_WR_ENTRY(fault);
DLR_WR_ENTRY(signon);
DLR_WR_ENTRY(clear_rapid);
DLR_WR_ENTRY(clear_partial);

DLR_RD_ENTRY(all);
DLR_RD_ENTRY(rev);
DLR_RD_ENTRY(topology);
DLR_RD_ENTRY(network);
DLR_RD_ENTRY(super);
DLR_WR_ENTRY(super_cfg);
DLR_WR_ENTRY(fault_cnt);
DLR_RD_ENTRY(last_active_1);
DLR_RD_ENTRY(last_active_2);
DLR_RD_ENTRY(part_cnt);
DLR_RD_ENTRY(part_list);
DLR_RD_ENTRY(active_super_addr);
DLR_RD_ENTRY(active_super_prec);
DLR_RD_ENTRY(cap);
DLR_WR_ENTRY(port_1);
DLR_WR_ENTRY(port_2);

static struct attribute *dlr_attrs[] = {
	&dlr_attr_info.attr,
	&dlr_attr_node.attr,
	&dlr_attr_prec.attr,
	&dlr_attr_interval.attr,
	&dlr_attr_timeout.attr,
	&dlr_attr_vid.attr,
	&dlr_attr_state.attr,
	&dlr_attr_port.attr,
	&dlr_attr_test.attr,
	&dlr_attr_req.attr,
	&dlr_attr_resp.attr,
	&dlr_attr_link.attr,
	&dlr_attr_learn.attr,
	&dlr_attr_fault.attr,
	&dlr_attr_signon.attr,
	&dlr_attr_clear_rapid.attr,
	&dlr_attr_clear_partial.attr,

	&dlr_attr_all.attr,
	&dlr_attr_rev.attr,
	&dlr_attr_topology.attr,
	&dlr_attr_network.attr,
	&dlr_attr_super.attr,
	&dlr_attr_super_cfg.attr,
	&dlr_attr_fault_cnt.attr,
	&dlr_attr_last_active_1.attr,
	&dlr_attr_last_active_2.attr,
	&dlr_attr_part_cnt.attr,
	&dlr_attr_part_list.attr,
	&dlr_attr_active_super_addr.attr,
	&dlr_attr_active_super_prec.attr,
	&dlr_attr_cap.attr,
	&dlr_attr_port_1.attr,
	&dlr_attr_port_2.attr,
	NULL
};

static struct attribute_group dlr_group = {
	.name  = "dlrfs",
	.attrs  = dlr_attrs,
};

static void exit_dlr_sysfs(struct device *dev)
{
	sysfs_remove_group(&dev->kobj, &dlr_group);
}

static int init_dlr_sysfs(struct device *dev)
{
	int err;

	err = sysfs_create_group(&dev->kobj, &dlr_group);
	if (err)
		return err;
	return err;
}

