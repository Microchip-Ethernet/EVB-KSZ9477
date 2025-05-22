#include "ksz_web.h"


static ssize_t netweb_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct ksz_port *port;
	struct ksz_sw *sw;
	struct semaphore *proc_sem;
	ssize_t len = -EINVAL;
	int proc_num;

	get_private_data(d, &proc_sem, &sw, &port);
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	len = 0;
	proc_num = offset / sizeof(int);
	len = sw->ops->sysfs_web_read(sw, proc_num, port, len, buf);

	up(proc_sem);
	return len;
}

static ssize_t netweb_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct ksz_port *port;
	struct ksz_sw *sw;
	struct semaphore *proc_sem;
	ssize_t ret = -EINVAL;
	int num;
	int proc_num;

	num = get_num_val(buf);
	get_private_data(d, &proc_sem, &sw, &port);
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;

	sw->ops->sysfs_web_write(sw, proc_num, port, num, buf);

	up(proc_sem);
	return ret;
}

#define WEB_ATTR(_name, _mode, _show, _store) \
struct device_attribute web_attr_##_name = \
	__ATTR(_name, _mode, _show, _store)

/* generate a read-only attribute */
#define NETWEB_RD_ENTRY(name)						\
static ssize_t show_web_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netweb_show(d, attr, buf,				\
		offsetof(struct web_attributes, name));			\
}									\
static WEB_ATTR(name, S_IRUGO, show_web_##name, NULL)

/* generate a write-able attribute */
#define NETWEB_WR_ENTRY(name)						\
static ssize_t show_web_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netweb_show(d, attr, buf,				\
		offsetof(struct web_attributes, name));			\
}									\
static ssize_t store_web_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return netweb_store(d, attr, buf, count,			\
		offsetof(struct web_attributes, name));			\
}									\
static WEB_ATTR(name, S_IRUGO | S_IWUSR, show_web_##name, store_web_##name)

NETWEB_RD_ENTRY(dev_info);
NETWEB_RD_ENTRY(tgt_info);
NETWEB_WR_ENTRY(dynamic_table);
NETWEB_WR_ENTRY(static_table);
NETWEB_WR_ENTRY(static_cfg);
NETWEB_WR_ENTRY(vlan_table);
NETWEB_WR_ENTRY(vlan);
NETWEB_WR_ENTRY(jumbo_packet);
NETWEB_WR_ENTRY(mtu);
NETWEB_WR_ENTRY(port_status);
NETWEB_WR_ENTRY(pvid);


static struct attribute *web_attrs[] = {
	&web_attr_dev_info.attr,
	&web_attr_tgt_info.attr,
	&web_attr_dynamic_table.attr,
	&web_attr_static_table.attr,
	&web_attr_static_cfg.attr,
	&web_attr_vlan_table.attr,
	&web_attr_vlan.attr,
	&web_attr_jumbo_packet.attr,
	&web_attr_mtu.attr,
	&web_attr_port_status.attr,
	&web_attr_pvid.attr,

	NULL
};

