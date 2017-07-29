/**
 * Micrel KSZ8795 switch common sysfs code
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2011-2015 Micrel, Inc.
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


static char *sw_name[TOTAL_PORT_NUM] = {
	"sw0",
	"sw1",
	"sw2",
	"sw3",
	"sw4",
};

static ssize_t netlan_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct ksz_port *uninitialized_var(port);
	struct ksz_sw *sw;
	struct semaphore *proc_sem;
	ssize_t len = -EINVAL;
	int proc_num;

	get_private_data(d, &proc_sem, &sw, &port);
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	len = 0;
	proc_num = offset / sizeof(int);
	len = sw->ops->sysfs_read(sw, proc_num, port, len, buf);
	if (len)
		goto netlan_show_done;

	len = sw->ops->sysfs_mac_read(sw, proc_num, len, buf);
	if (len)
		goto netlan_show_done;

	len = sw->ops->sysfs_vlan_read(sw, proc_num, len, buf);
	if (len)
		goto netlan_show_done;

	/* Require hardware to be acquired first. */
	sw->ops->acquire(sw);
	len = sw->ops->sysfs_read_hw(sw, proc_num, len, buf);
	sw->ops->release(sw);

netlan_show_done:
	up(proc_sem);
	return len;
}

static ssize_t netlan_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct ksz_port *uninitialized_var(port);
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

	if (sw->ops->sysfs_mac_write(sw, proc_num, num, buf))
		goto netlan_store_done;

	if (sw->ops->sysfs_vlan_write(sw, proc_num, num))
		goto netlan_store_done;

	sw->ops->acquire(sw);
	sw->ops->sysfs_write(sw, proc_num, port, num, buf);
	sw->ops->release(sw);

netlan_store_done:
	up(proc_sem);
	return ret;
}

static ssize_t netsw_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct ksz_sw *sw;
	struct semaphore *proc_sem;
	ssize_t len = -EINVAL;
	int num;
	int port;

	if (attr->attr.name[1] != '_')
		return len;
	port = attr->attr.name[0] - '0';
	if (port >= TOTAL_PORT_NUM)
		return len;

	get_private_data(d, &proc_sem, &sw, NULL);
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	len = 0;
	num = offset / sizeof(int);
	len = sw->ops->sysfs_port_read(sw, num, port, len, buf);
	if (len)
		goto netsw_show_done;

	len = sw->ops->sysfs_acl_read(sw, num, port, len, buf);
	if (len)
		goto netsw_show_done;

	/* Require hardware to be acquired first. */
	sw->ops->acquire(sw);
	len = sw->ops->sysfs_port_read_hw(sw, num, port, len, buf);
	sw->ops->release(sw);

netsw_show_done:
	up(proc_sem);
	return len;
}

static ssize_t netsw_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct ksz_sw *sw;
	struct semaphore *proc_sem;
	ssize_t ret = -EINVAL;
	int num;
	int port;
	int proc_num;

	if (attr->attr.name[1] != '_')
		return ret;
	port = attr->attr.name[0] - '0';
	if (port >= TOTAL_PORT_NUM)
		return ret;
	num = get_num_val(buf);
	get_private_data(d, &proc_sem, &sw, NULL);
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;

	if (sw->ops->sysfs_acl_write(sw, proc_num, port, num, buf))
		goto netsw_store_done;

	sw->ops->acquire(sw);
	sw->ops->sysfs_port_write(sw, proc_num, port, num, buf);
	sw->ops->release(sw);

netsw_store_done:
	up(proc_sem);
	return ret;
}

#define LAN_ATTR(_name, _mode, _show, _store) \
struct device_attribute lan_attr_##_name = \
	__ATTR(_name, _mode, _show, _store)

/* generate a read-only attribute */
#define NETLAN_RD_ENTRY(name)						\
static ssize_t show_lan_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netlan_show(d, attr, buf,				\
		offsetof(struct lan_attributes, name));			\
}									\
static LAN_ATTR(name, S_IRUGO, show_lan_##name, NULL)

/* generate a write-able attribute */
#define NETLAN_WR_ENTRY(name)						\
static ssize_t show_lan_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netlan_show(d, attr, buf,				\
		offsetof(struct lan_attributes, name));			\
}									\
static ssize_t store_lan_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return netlan_store(d, attr, buf, count,			\
		offsetof(struct lan_attributes, name));			\
}									\
static LAN_ATTR(name, S_IRUGO | S_IWUSR, show_lan_##name, store_lan_##name)

#define SW_ATTR(_name, _mode, _show, _store) \
struct device_attribute sw_attr_##_name = \
	__ATTR(0_##_name, _mode, _show, _store)

/* generate a read-only attribute */
#define NETSW_RD_ENTRY(name)						\
static ssize_t show_sw_##name(struct device *d,				\
	struct device_attribute *attr, char *buf)			\
{									\
	return netsw_show(d, attr, buf,					\
		offsetof(struct sw_attributes, name));			\
}									\
static SW_ATTR(name, S_IRUGO, show_sw_##name, NULL)

/* generate a write-able attribute */
#define NETSW_WR_ENTRY(name)						\
static ssize_t show_sw_##name(struct device *d,				\
	struct device_attribute *attr, char *buf)			\
{									\
	return netsw_show(d, attr, buf,					\
		offsetof(struct sw_attributes, name));			\
}									\
static ssize_t store_sw_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return netsw_store(d, attr, buf, count,				\
		offsetof(struct sw_attributes, name));			\
}									\
static SW_ATTR(name, S_IRUGO | S_IWUSR, show_sw_##name, store_sw_##name)

NETLAN_WR_ENTRY(info);
NETLAN_WR_ENTRY(duplex);
NETLAN_WR_ENTRY(speed);
NETLAN_WR_ENTRY(force);
NETLAN_WR_ENTRY(flow_ctrl);
NETLAN_WR_ENTRY(mib);
NETLAN_WR_ENTRY(reg);
NETLAN_WR_ENTRY(vid);
NETLAN_WR_ENTRY(features);
NETLAN_WR_ENTRY(overrides);

NETLAN_WR_ENTRY(dynamic_table);
NETLAN_WR_ENTRY(static_table);
NETLAN_RD_ENTRY(vlan_table);
NETLAN_WR_ENTRY(aging);
NETLAN_WR_ENTRY(fast_aging);
NETLAN_WR_ENTRY(link_aging);
NETLAN_WR_ENTRY(bcast_per);
NETLAN_WR_ENTRY(mcast_storm);
NETLAN_WR_ENTRY(diffserv_map);
NETLAN_WR_ENTRY(p_802_1p_map);
NETLAN_WR_ENTRY(vlan);
NETLAN_WR_ENTRY(null_vid);
NETLAN_WR_ENTRY(macaddr);
NETLAN_WR_ENTRY(mirror_mode);
NETLAN_WR_ENTRY(tail_tag);
NETLAN_WR_ENTRY(igmp_snoop);
NETLAN_WR_ENTRY(ipv6_mld_snoop);
NETLAN_WR_ENTRY(ipv6_mld_option);
NETLAN_WR_ENTRY(aggr_backoff);
NETLAN_WR_ENTRY(no_exc_drop);
NETLAN_WR_ENTRY(huge_packet);
NETLAN_WR_ENTRY(legal_packet);
NETLAN_WR_ENTRY(length_check);
NETLAN_WR_ENTRY(back_pressure);
NETLAN_WR_ENTRY(sw_flow_ctrl);
NETLAN_WR_ENTRY(sw_half_duplex);
#ifdef SWITCH_10_MBIT
NETLAN_WR_ENTRY(sw_10_mbit);
#endif
NETLAN_WR_ENTRY(rx_flow_ctrl);
NETLAN_WR_ENTRY(tx_flow_ctrl);
NETLAN_WR_ENTRY(fair_flow_ctrl);
NETLAN_WR_ENTRY(vlan_bound);
NETLAN_WR_ENTRY(fw_unk_ucast_dest);
NETLAN_WR_ENTRY(fw_unk_ucast_ports);
NETLAN_WR_ENTRY(fw_unk_mcast_dest);
NETLAN_WR_ENTRY(fw_unk_mcast_ports);
NETLAN_WR_ENTRY(fw_inv_vid);
NETLAN_WR_ENTRY(fw_inv_vid_ports);
NETLAN_WR_ENTRY(fw_unk_ip_mcast_dest);
NETLAN_WR_ENTRY(fw_unk_ip_mcast_ports);
NETLAN_WR_ENTRY(self_filter);
NETLAN_WR_ENTRY(ins_tag);
NETLAN_WR_ENTRY(pme);
NETLAN_WR_ENTRY(pass_pause);
NETLAN_WR_ENTRY(hi_prio_queues);
NETLAN_RD_ENTRY(ports);
NETLAN_RD_ENTRY(dev_start);
NETLAN_RD_ENTRY(vlan_start);
NETLAN_RD_ENTRY(stp);

NETLAN_WR_ENTRY(mac_fid);
NETLAN_WR_ENTRY(mac_use_fid);
NETLAN_WR_ENTRY(mac_override);
NETLAN_WR_ENTRY(mac_valid);
NETLAN_WR_ENTRY(mac_ports);
NETLAN_WR_ENTRY(mac_addr);
NETLAN_WR_ENTRY(mac_index);
NETLAN_RD_ENTRY(mac_info);

NETLAN_WR_ENTRY(vlan_valid);
NETLAN_WR_ENTRY(vlan_ports);
NETLAN_WR_ENTRY(vlan_fid);
NETLAN_WR_ENTRY(vlan_index);
NETLAN_RD_ENTRY(vlan_info);

NETSW_WR_ENTRY(mib);
NETSW_WR_ENTRY(vid);
NETSW_WR_ENTRY(member);
NETSW_WR_ENTRY(bcast_storm);
NETSW_WR_ENTRY(rx);
NETSW_WR_ENTRY(tx);
NETSW_WR_ENTRY(learn);
NETSW_WR_ENTRY(mirror_port);
NETSW_WR_ENTRY(mirror_rx);
NETSW_WR_ENTRY(mirror_tx);
NETSW_WR_ENTRY(diffserv);
NETSW_WR_ENTRY(p_802_1p);
NETSW_WR_ENTRY(port_based);
NETSW_WR_ENTRY(non_vid);
NETSW_WR_ENTRY(drop_tagged);
NETSW_WR_ENTRY(ingress);
NETSW_WR_ENTRY(ins_tag);
NETSW_WR_ENTRY(rmv_tag);
NETSW_WR_ENTRY(ins_tag_0);
NETSW_WR_ENTRY(ins_tag_1);
NETSW_WR_ENTRY(ins_tag_2);
NETSW_WR_ENTRY(ins_tag_3);
NETSW_WR_ENTRY(ins_tag_4);
NETSW_WR_ENTRY(pass_all);
NETSW_WR_ENTRY(replace_prio);
NETSW_WR_ENTRY(prio_queue);
NETSW_WR_ENTRY(tx_q0_ctrl);
NETSW_WR_ENTRY(tx_q1_ctrl);
NETSW_WR_ENTRY(tx_q2_ctrl);
NETSW_WR_ENTRY(tx_q3_ctrl);
NETSW_WR_ENTRY(tx_q0_ratio);
NETSW_WR_ENTRY(tx_q1_ratio);
NETSW_WR_ENTRY(tx_q2_ratio);
NETSW_WR_ENTRY(tx_q3_ratio);
NETSW_WR_ENTRY(rx_prio_rate);
NETSW_WR_ENTRY(tx_prio_rate);
NETSW_WR_ENTRY(rx_limit);
NETSW_WR_ENTRY(rx_limit_port_based);
NETSW_WR_ENTRY(limit_packet_based);
NETSW_WR_ENTRY(rx_limit_flow_ctrl);
NETSW_WR_ENTRY(cnt_ifg);
NETSW_WR_ENTRY(cnt_pre);
NETSW_WR_ENTRY(rx_p0_rate);
NETSW_WR_ENTRY(rx_p1_rate);
NETSW_WR_ENTRY(rx_p2_rate);
NETSW_WR_ENTRY(rx_p3_rate);
NETSW_WR_ENTRY(tx_q0_rate);
NETSW_WR_ENTRY(tx_q1_rate);
NETSW_WR_ENTRY(tx_q2_rate);
NETSW_WR_ENTRY(tx_q3_rate);
NETSW_WR_ENTRY(back_pressure);
NETSW_WR_ENTRY(force_flow_ctrl);
NETSW_WR_ENTRY(fw_unk_ucast_dest);
NETSW_WR_ENTRY(fw_unk_mcast_dest);
NETSW_WR_ENTRY(fw_inv_vid);
NETSW_WR_ENTRY(fw_unk_ip_mcast_dest);
NETSW_WR_ENTRY(pme_ctrl);
NETSW_WR_ENTRY(pme_status);
NETSW_RD_ENTRY(duplex);
NETSW_RD_ENTRY(speed);
NETSW_WR_ENTRY(linkmd);

NETSW_WR_ENTRY(authen_mode);
NETSW_WR_ENTRY(acl);
NETSW_WR_ENTRY(acl_first_rule);
NETSW_WR_ENTRY(acl_ruleset);
NETSW_WR_ENTRY(acl_mode);
NETSW_WR_ENTRY(acl_enable);
NETSW_WR_ENTRY(acl_src);
NETSW_WR_ENTRY(acl_equal);
NETSW_WR_ENTRY(acl_addr);
NETSW_WR_ENTRY(acl_type);
NETSW_WR_ENTRY(acl_cnt);
NETSW_WR_ENTRY(acl_msec);
NETSW_WR_ENTRY(acl_intr_mode);
NETSW_WR_ENTRY(acl_ip_addr);
NETSW_WR_ENTRY(acl_ip_mask);
NETSW_WR_ENTRY(acl_protocol);
NETSW_WR_ENTRY(acl_seqnum);
NETSW_WR_ENTRY(acl_port_mode);
NETSW_WR_ENTRY(acl_max_port);
NETSW_WR_ENTRY(acl_min_port);
NETSW_WR_ENTRY(acl_tcp_flag_enable);
NETSW_WR_ENTRY(acl_tcp_flag);
NETSW_WR_ENTRY(acl_tcp_flag_mask);
NETSW_WR_ENTRY(acl_prio_mode);
NETSW_WR_ENTRY(acl_prio);
NETSW_WR_ENTRY(acl_vlan_prio_replace);
NETSW_WR_ENTRY(acl_vlan_prio);
NETSW_WR_ENTRY(acl_map_mode);
NETSW_WR_ENTRY(acl_ports);
NETSW_WR_ENTRY(acl_index);
NETSW_WR_ENTRY(acl_act_index);
NETSW_WR_ENTRY(acl_act);
NETSW_WR_ENTRY(acl_info);
NETSW_RD_ENTRY(acl_table);

static struct attribute *lan_attrs[] = {
	&lan_attr_info.attr,
#ifdef USE_SPEED_LINK
	&lan_attr_duplex.attr,
	&lan_attr_speed.attr,
	&lan_attr_force.attr,
	&lan_attr_flow_ctrl.attr,
#endif
#ifdef USE_MIB
	&lan_attr_mib.attr,
#endif
	&lan_attr_reg.attr,
	&lan_attr_vid.attr,
	&lan_attr_features.attr,
	&lan_attr_overrides.attr,

	&lan_attr_dynamic_table.attr,
	&lan_attr_static_table.attr,
	&lan_attr_vlan_table.attr,
	&lan_attr_aging.attr,
	&lan_attr_fast_aging.attr,
	&lan_attr_link_aging.attr,
	&lan_attr_bcast_per.attr,
	&lan_attr_mcast_storm.attr,
	&lan_attr_diffserv_map.attr,
	&lan_attr_p_802_1p_map.attr,
	&lan_attr_vlan.attr,
	&lan_attr_null_vid.attr,
	&lan_attr_macaddr.attr,
	&lan_attr_mirror_mode.attr,
	&lan_attr_tail_tag.attr,
	&lan_attr_igmp_snoop.attr,
	&lan_attr_ipv6_mld_snoop.attr,
	&lan_attr_ipv6_mld_option.attr,
	&lan_attr_aggr_backoff.attr,
	&lan_attr_no_exc_drop.attr,
	&lan_attr_huge_packet.attr,
	&lan_attr_legal_packet.attr,
	&lan_attr_length_check.attr,
	&lan_attr_back_pressure.attr,
	&lan_attr_sw_flow_ctrl.attr,
	&lan_attr_sw_half_duplex.attr,
#ifdef SWITCH_10_MBIT
	&lan_attr_sw_10_mbit.attr,
#endif
	&lan_attr_rx_flow_ctrl.attr,
	&lan_attr_tx_flow_ctrl.attr,
	&lan_attr_fair_flow_ctrl.attr,
	&lan_attr_vlan_bound.attr,
	&lan_attr_fw_unk_ucast_dest.attr,
	&lan_attr_fw_unk_ucast_ports.attr,
	&lan_attr_fw_unk_mcast_dest.attr,
	&lan_attr_fw_unk_mcast_ports.attr,
	&lan_attr_fw_inv_vid.attr,
	&lan_attr_fw_inv_vid_ports.attr,
	&lan_attr_fw_unk_ip_mcast_dest.attr,
	&lan_attr_fw_unk_ip_mcast_ports.attr,
	&lan_attr_self_filter.attr,
	&lan_attr_ins_tag.attr,
	&lan_attr_pme.attr,
	&lan_attr_pass_pause.attr,
	&lan_attr_hi_prio_queues.attr,
	&lan_attr_ports.attr,
	&lan_attr_dev_start.attr,
	&lan_attr_vlan_start.attr,
	&lan_attr_stp.attr,

	&lan_attr_mac_fid.attr,
	&lan_attr_mac_use_fid.attr,
	&lan_attr_mac_override.attr,
	&lan_attr_mac_valid.attr,
	&lan_attr_mac_ports.attr,
	&lan_attr_mac_addr.attr,
	&lan_attr_mac_index.attr,
	&lan_attr_mac_info.attr,

	&lan_attr_vlan_valid.attr,
	&lan_attr_vlan_ports.attr,
	&lan_attr_vlan_fid.attr,
	&lan_attr_vlan_index.attr,
	&lan_attr_vlan_info.attr,

	NULL
};

static struct attribute *sw_attrs[] = {
	&sw_attr_vid.attr,
	&sw_attr_member.attr,
	&sw_attr_bcast_storm.attr,
	&sw_attr_rx.attr,
	&sw_attr_tx.attr,
	&sw_attr_learn.attr,
	&sw_attr_mirror_port.attr,
	&sw_attr_mirror_rx.attr,
	&sw_attr_mirror_tx.attr,
	&sw_attr_diffserv.attr,
	&sw_attr_p_802_1p.attr,
	&sw_attr_port_based.attr,
	&sw_attr_non_vid.attr,
	&sw_attr_drop_tagged.attr,
	&sw_attr_ingress.attr,
	&sw_attr_ins_tag.attr,
	&sw_attr_rmv_tag.attr,
	&sw_attr_ins_tag_0.attr,
	&sw_attr_ins_tag_1.attr,
	&sw_attr_ins_tag_2.attr,
	&sw_attr_ins_tag_3.attr,
	&sw_attr_ins_tag_4.attr,
	&sw_attr_pass_all.attr,
	&sw_attr_replace_prio.attr,
	&sw_attr_prio_queue.attr,
	&sw_attr_tx_q0_ctrl.attr,
	&sw_attr_tx_q1_ctrl.attr,
	&sw_attr_tx_q2_ctrl.attr,
	&sw_attr_tx_q3_ctrl.attr,
	&sw_attr_tx_q0_ratio.attr,
	&sw_attr_tx_q1_ratio.attr,
	&sw_attr_tx_q2_ratio.attr,
	&sw_attr_tx_q3_ratio.attr,
	&sw_attr_rx_prio_rate.attr,
	&sw_attr_tx_prio_rate.attr,
	&sw_attr_rx_limit.attr,
	&sw_attr_rx_limit_port_based.attr,
	&sw_attr_limit_packet_based.attr,
	&sw_attr_rx_limit_flow_ctrl.attr,
	&sw_attr_cnt_ifg.attr,
	&sw_attr_cnt_pre.attr,
	&sw_attr_rx_p0_rate.attr,
	&sw_attr_rx_p1_rate.attr,
	&sw_attr_rx_p2_rate.attr,
	&sw_attr_rx_p3_rate.attr,
	&sw_attr_tx_q0_rate.attr,
	&sw_attr_tx_q1_rate.attr,
	&sw_attr_tx_q2_rate.attr,
	&sw_attr_tx_q3_rate.attr,
	&sw_attr_back_pressure.attr,
	&sw_attr_force_flow_ctrl.attr,
	&sw_attr_fw_unk_ucast_dest.attr,
	&sw_attr_fw_unk_mcast_dest.attr,
	&sw_attr_fw_inv_vid.attr,
	&sw_attr_fw_unk_ip_mcast_dest.attr,
	&sw_attr_mib.attr,
	&sw_attr_pme_ctrl.attr,
	&sw_attr_pme_status.attr,

	&sw_attr_authen_mode.attr,
	&sw_attr_acl.attr,
	&sw_attr_acl_first_rule.attr,
	&sw_attr_acl_ruleset.attr,
	&sw_attr_acl_mode.attr,
	&sw_attr_acl_enable.attr,
	&sw_attr_acl_src.attr,
	&sw_attr_acl_equal.attr,
	&sw_attr_acl_addr.attr,
	&sw_attr_acl_type.attr,
	&sw_attr_acl_cnt.attr,
	&sw_attr_acl_msec.attr,
	&sw_attr_acl_intr_mode.attr,
	&sw_attr_acl_ip_addr.attr,
	&sw_attr_acl_ip_mask.attr,
	&sw_attr_acl_protocol.attr,
	&sw_attr_acl_seqnum.attr,
	&sw_attr_acl_port_mode.attr,
	&sw_attr_acl_max_port.attr,
	&sw_attr_acl_min_port.attr,
	&sw_attr_acl_tcp_flag_enable.attr,
	&sw_attr_acl_tcp_flag.attr,
	&sw_attr_acl_tcp_flag_mask.attr,
	&sw_attr_acl_prio_mode.attr,
	&sw_attr_acl_prio.attr,
	&sw_attr_acl_vlan_prio_replace.attr,
	&sw_attr_acl_vlan_prio.attr,
	&sw_attr_acl_map_mode.attr,
	&sw_attr_acl_ports.attr,
	&sw_attr_acl_index.attr,
	&sw_attr_acl_act_index.attr,
	&sw_attr_acl_act.attr,
	&sw_attr_acl_info.attr,
	&sw_attr_acl_table.attr,

	&sw_attr_duplex.attr,
	&sw_attr_speed.attr,
	&sw_attr_linkmd.attr,

	NULL
};

static struct attribute_group lan_group = {
	.name  = "sw",
	.attrs  = lan_attrs,
};

static struct attribute_group sw_group = {
	.name  = "sw0",
	.attrs  = sw_attrs,
};

/* Kernel checking requires the attributes are in data segment. */
#define SW_ATTRS_SIZE		(sizeof(sw_attrs) / sizeof(void *) - 1)

#define MAX_SWITCHES		2

static struct ksz_dev_attr ksz_sw_dev_attrs[(
	SW_ATTRS_SIZE * TOTAL_PORT_NUM) * MAX_SWITCHES];
static struct ksz_dev_attr *ksz_sw_dev_attrs_ptr = ksz_sw_dev_attrs;

static void exit_sw_sysfs(struct ksz_sw *sw, struct ksz_sw_sysfs *info,
	struct device *dev)
{
	int i;
	int p = sw->mib_port_cnt - 1;

	if (sw->port_cnt < sw->mib_port_cnt)
		p--;
	for (i = 0; i < p; i++) {
		sw_group.name = sw_name[i];
		sw_group.attrs = info->port_attrs[i];
		sysfs_remove_group(&dev->kobj, &sw_group);
		kfree(info->port_attrs[i]);
		info->port_attrs[i] = NULL;
		info->ksz_port_attrs[i] = NULL;
	}
	i = sw->HOST_PORT;
	sw_group.name = sw_name[i];
	sw_group.attrs = info->port_attrs[i];
	sysfs_remove_group(&dev->kobj, &sw_group);
	kfree(info->port_attrs[i]);
	info->port_attrs[i] = NULL;
	info->ksz_port_attrs[i] = NULL;

	sysfs_remove_group(&dev->kobj, &lan_group);
}

static int init_sw_sysfs(struct ksz_sw *sw, struct ksz_sw_sysfs *info,
	struct device *dev)
{
	int err;
	int i;
	int p = sw->mib_port_cnt - 1;

	if (sw->port_cnt < sw->mib_port_cnt)
		p--;
	err = sysfs_create_group(&dev->kobj, &lan_group);
	if (err)
		return err;
	for (i = 0; i < p; i++) {
		err = alloc_dev_attr(sw_attrs,
			sizeof(sw_attrs) / sizeof(void *), i,
			&info->ksz_port_attrs[i],
			&info->port_attrs[i], NULL, &ksz_sw_dev_attrs_ptr);
		if (err)
			return err;
		sw_group.name = sw_name[i];
		sw_group.attrs = info->port_attrs[i];
		err = sysfs_create_group(&dev->kobj, &sw_group);
		if (err)
			return err;
	}
	i = sw->HOST_PORT;
	err = alloc_dev_attr(sw_attrs,
		sizeof(sw_attrs) / sizeof(void *), i,
		&info->ksz_port_attrs[i], &info->port_attrs[i],
		"0_duplex", &ksz_sw_dev_attrs_ptr);
	if (err)
		return err;
	sw_group.name = sw_name[i];
	sw_group.attrs = info->port_attrs[i];
	err = sysfs_create_group(&dev->kobj, &sw_group);
	if (err)
		return err;
	return err;
}

