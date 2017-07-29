/**
 * Micrel PTP common sysfs code
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2012-2013 Micrel, Inc.
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


static ssize_t ptp_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct ksz_sw *sw;
	struct semaphore *proc_sem;
	struct ptp_info *ptp;
	ssize_t len = -EINVAL;
	int proc_num;

	get_private_data(d, &proc_sem, &sw, NULL);
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	ptp = &sw->ptp_hw;
	len = 0;
	proc_num = offset / sizeof(int);
	len = ptp->ops->sysfs_read(ptp, proc_num, len, buf);
	up(proc_sem);
	return len;
}

static ssize_t ptp_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct ksz_sw *sw;
	struct semaphore *proc_sem;
	struct ptp_info *ptp;
	ssize_t ret = -EINVAL;
	int num;
	int proc_num;

	num = get_num_val(buf);
	get_private_data(d, &proc_sem, &sw, NULL);
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	ptp = &sw->ptp_hw;
	proc_num = offset / sizeof(int);
	ret = count;
	ptp->ops->acquire(ptp);
	ptp->ops->sysfs_write(ptp, proc_num, num, buf);
	ptp->ops->release(ptp);
	up(proc_sem);
	return ret;
}

#define PTP_ATTR(_name, _mode, _show, _store) \
struct device_attribute ptp_attr_##_name = \
	__ATTR(_name, _mode, _show, _store)

/* generate a read-only attribute */
#define PTP_RD_ENTRY(name)						\
static ssize_t show_ptp_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return ptp_show(d, attr, buf,					\
		offsetof(struct ptp_attributes, name));			\
}									\
static PTP_ATTR(name, S_IRUGO, show_ptp_##name, NULL)

/* generate a write-able attribute */
#define PTP_WR_ENTRY(name)						\
static ssize_t show_ptp_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return ptp_show(d, attr, buf,					\
		offsetof(struct ptp_attributes, name));			\
}									\
static ssize_t store_ptp_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return ptp_store(d, attr, buf, count,				\
		offsetof(struct ptp_attributes, name));			\
}									\
static PTP_ATTR(name, S_IRUGO | S_IWUSR, show_ptp_##name, store_ptp_##name)

PTP_WR_ENTRY(features);
PTP_WR_ENTRY(overrides);
PTP_WR_ENTRY(vid);

static struct attribute *ptp_attrs[] = {
	&ptp_attr_features.attr,
	&ptp_attr_overrides.attr,
	&ptp_attr_vid.attr,
	NULL
};

static struct attribute_group ptp_group = {
	.name  = "ptpfs",
	.attrs  = ptp_attrs,
};

static void exit_ptp_sysfs(struct ksz_ptp_sysfs *info, struct device *dev)
{
	sysfs_remove_group(&dev->kobj, &ptp_group);
}

static int init_ptp_sysfs(struct ksz_ptp_sysfs *info, struct device *dev)
{
	int err;

	err = sysfs_create_group(&dev->kobj, &ptp_group);
	if (err)
		return err;
	return err;
}

