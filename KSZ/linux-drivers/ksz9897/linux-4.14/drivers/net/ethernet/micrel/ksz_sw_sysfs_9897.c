/**
 * Microchip gigabit switch common sysfs code
 *
 * Copyright (c) 2015-2019 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2011-2014 Micrel, Inc.
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


#include "ksz_sysfs.h"


static char *sw_name[] = {
	"sw0",
	"sw1",
	"sw2",
	"sw3",
	"sw4",
	"sw5",
	"sw6",
	"sw7",
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

#ifdef CONFIG_KSZ_STP
	len = sw->ops->sysfs_stp_read(sw, proc_num, len, buf);
	if (len)
		goto netlan_show_done;
#endif

#ifdef CONFIG_KSZ_AVB
	len = sw->ops->sysfs_mrp_read(sw, proc_num, len, buf);
	if (len)
		goto netlan_show_done;
#endif

#ifdef CONFIG_KSZ_HSR
	len = sw->ops->sysfs_hsr_read(sw, proc_num, len, buf);
	if (len)
		goto netlan_show_done;
#endif

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

#ifdef CONFIG_KSZ_STP
	if (sw->ops->sysfs_stp_write(sw, proc_num, num, buf))
		goto netlan_store_done;
#endif

#ifdef CONFIG_KSZ_AVB
	if (sw->ops->sysfs_mrp_write(sw, proc_num, num, buf))
		goto netlan_store_done;
#endif

#ifdef CONFIG_KSZ_HSR
	if (sw->ops->sysfs_hsr_write(sw, proc_num, num, buf))
		goto netlan_store_done;
#endif

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
	int cnt;
	int num;
	uint port;

	if (attr->attr.name[1] != '_')
		return len;
	port = attr->attr.name[0] - '0';

	get_private_data(d, &proc_sem, &sw, NULL);
	cnt = TOTAL_PORT_NUM;
	if (sw->overrides & SYSFS_1_BASE)
		cnt++;
	if (port >= cnt)
		return len;
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

#ifdef CONFIG_KSZ_STP
	len = sw->ops->sysfs_stp_port_read(sw, num, port, len, buf);
	if (len)
		goto netsw_show_done;
#endif

#ifdef CONFIG_KSZ_AVB
	len = sw->ops->sysfs_mrp_port_read(sw, num, port, len, buf);
	if (len)
		goto netsw_show_done;
#endif

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
	int cnt;
	int num;
	uint port;
	int proc_num;

	if (attr->attr.name[1] != '_')
		return ret;
	port = attr->attr.name[0] - '0';
	num = get_num_val(buf);
	get_private_data(d, &proc_sem, &sw, NULL);
	cnt = TOTAL_PORT_NUM;
	if (sw->overrides & SYSFS_1_BASE)
		cnt++;
	if (port >= cnt)
		return ret;
	if (down_interruptible(proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;

	if (sw->ops->sysfs_acl_write(sw, proc_num, port, num, buf))
		goto netsw_store_done;

#ifdef CONFIG_KSZ_STP
	if (sw->ops->sysfs_stp_port_write(sw, proc_num, port, num, buf))
		goto netsw_store_done;
#endif

#ifdef CONFIG_KSZ_AVB
	if (sw->ops->sysfs_mrp_port_write(sw, proc_num, port, num, buf))
		goto netsw_store_done;
#endif

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
NETLAN_RD_ENTRY(version);
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
NETLAN_RD_ENTRY(hsr_table);
NETLAN_WR_ENTRY(aging);
NETLAN_WR_ENTRY(fast_aging);
NETLAN_WR_ENTRY(link_aging);
NETLAN_WR_ENTRY(bcast_per);
NETLAN_WR_ENTRY(mcast_storm);
NETLAN_WR_ENTRY(tx_queue_based);
NETLAN_WR_ENTRY(diffserv_map);
NETLAN_WR_ENTRY(p_802_1p_map);
NETLAN_WR_ENTRY(vlan);
NETLAN_WR_ENTRY(null_vid);
NETLAN_WR_ENTRY(drop_inv_vid);
NETLAN_WR_ENTRY(macaddr);
NETLAN_WR_ENTRY(mirror_mode);
NETLAN_WR_ENTRY(igmp_snoop);
NETLAN_WR_ENTRY(ipv6_mld_snoop);
NETLAN_WR_ENTRY(ipv6_mld_option);
NETLAN_WR_ENTRY(aggr_backoff);
NETLAN_WR_ENTRY(no_exc_drop);
NETLAN_WR_ENTRY(jumbo_packet);
NETLAN_WR_ENTRY(legal_packet);
NETLAN_WR_ENTRY(length_check);
NETLAN_WR_ENTRY(back_pressure);
NETLAN_WR_ENTRY(sw_flow_ctrl);
NETLAN_WR_ENTRY(sw_half_duplex);
#ifdef SWITCH_10_MBIT
NETLAN_WR_ENTRY(sw_10_mbit);
#endif
NETLAN_WR_ENTRY(fair_flow_ctrl);
NETLAN_WR_ENTRY(vlan_bound);
NETLAN_WR_ENTRY(double_tag);
NETLAN_WR_ENTRY(isp);
NETLAN_WR_ENTRY(hsr);
NETLAN_WR_ENTRY(hsr_redbox_id);
NETLAN_WR_ENTRY(hsr_net_id);
NETLAN_WR_ENTRY(mtu);
NETLAN_WR_ENTRY(unk_ucast_fwd);
NETLAN_WR_ENTRY(unk_ucast_ports);
NETLAN_WR_ENTRY(unk_mcast_fwd);
NETLAN_WR_ENTRY(unk_mcast_ports);
NETLAN_WR_ENTRY(unk_vid_fwd);
NETLAN_WR_ENTRY(unk_vid_ports);
NETLAN_WR_ENTRY(pass_pause);
NETLAN_WR_ENTRY(pme);
NETLAN_WR_ENTRY(pme_polarity);

NETLAN_RD_ENTRY(host_port);
NETLAN_RD_ENTRY(ports);
NETLAN_RD_ENTRY(dev_start);
NETLAN_RD_ENTRY(port_start);
NETLAN_RD_ENTRY(vlan_start);
NETLAN_RD_ENTRY(avb);
NETLAN_RD_ENTRY(stp);
NETLAN_RD_ENTRY(two_dev);
NETLAN_WR_ENTRY(authen);

NETLAN_WR_ENTRY(alu_fid);
NETLAN_WR_ENTRY(alu_use_fid);
NETLAN_WR_ENTRY(alu_override);
NETLAN_WR_ENTRY(alu_valid);
NETLAN_WR_ENTRY(alu_mstp);
NETLAN_WR_ENTRY(alu_prio);
NETLAN_WR_ENTRY(alu_src);
NETLAN_WR_ENTRY(alu_dst);
NETLAN_WR_ENTRY(alu_ports);
NETLAN_WR_ENTRY(alu_addr);
NETLAN_WR_ENTRY(alu_type);
NETLAN_WR_ENTRY(alu_index);
NETLAN_WR_ENTRY(alu_info);

NETLAN_WR_ENTRY(vlan_valid);
NETLAN_WR_ENTRY(vlan_ports);
NETLAN_WR_ENTRY(vlan_untag);
NETLAN_WR_ENTRY(vlan_fid);
NETLAN_WR_ENTRY(vlan_mstp);
NETLAN_WR_ENTRY(vlan_prio);
NETLAN_WR_ENTRY(vlan_option);
NETLAN_WR_ENTRY(vlan_index);
NETLAN_WR_ENTRY(vlan_info);
NETLAN_WR_ENTRY(vid2fid);
NETLAN_WR_ENTRY(fid2mstid);

#ifdef CONFIG_KSZ_STP
NETLAN_RD_ENTRY(stp_br_info);
NETLAN_WR_ENTRY(stp_br_on);
NETLAN_WR_ENTRY(stp_br_prio);
NETLAN_WR_ENTRY(stp_br_fwd_delay);
NETLAN_WR_ENTRY(stp_br_hello_time);
NETLAN_WR_ENTRY(stp_br_max_age);
NETLAN_WR_ENTRY(stp_br_tx_hold);
NETLAN_WR_ENTRY(stp_version);
#ifdef CONFIG_KSZ_MSTP
NETLAN_WR_ENTRY(stp_br_max_hops);
NETLAN_WR_ENTRY(stp_msti);
NETLAN_RD_ENTRY(stp_msti_vid);
NETLAN_RD_ENTRY(stp_mstp_cfg);
NETLAN_WR_ENTRY(stp_mstp_name);
#endif
#endif

#ifdef CONFIG_KSZ_MSRP
NETLAN_WR_ENTRY(msrp_info);
NETLAN_WR_ENTRY(msrpEnabled);
#endif

#ifdef CONFIG_KSZ_AVB
NETLAN_WR_ENTRY(msrp_sr_a);
#endif

#ifdef CONFIG_KSZ_HSR
NETLAN_WR_ENTRY(hsr_valid);
NETLAN_WR_ENTRY(hsr_age_cnt);
NETLAN_WR_ENTRY(hsr_path_id);
NETLAN_WR_ENTRY(hsr_addr);
NETLAN_WR_ENTRY(hsr_index);
NETLAN_WR_ENTRY(hsr_info);
NETLAN_RD_ENTRY(hsr_state);
#endif

NETLAN_WR_ENTRY(no_color);
NETLAN_WR_ENTRY(color_red);
NETLAN_WR_ENTRY(color_yellow);
NETLAN_WR_ENTRY(color_green);
NETLAN_WR_ENTRY(vlan_filter_dynamic);
NETLAN_WR_ENTRY(vlan_filter_static);

NETSW_WR_ENTRY(mib);
NETSW_WR_ENTRY(vid);
NETSW_WR_ENTRY(member);
NETSW_WR_ENTRY(bcast_storm);
NETSW_WR_ENTRY(mstp);
NETSW_WR_ENTRY(rx);
NETSW_WR_ENTRY(tx);
NETSW_WR_ENTRY(learn);
NETSW_WR_ENTRY(power);
NETSW_WR_ENTRY(mirror_port);
NETSW_WR_ENTRY(mirror_rx);
NETSW_WR_ENTRY(mirror_tx);
NETSW_WR_ENTRY(diffserv);
NETSW_WR_ENTRY(p_802_1p);
NETSW_WR_ENTRY(prio_vlan);
NETSW_WR_ENTRY(prio_mac);
NETSW_WR_ENTRY(prio_acl);
NETSW_WR_ENTRY(prio_highest);
NETSW_WR_ENTRY(prio_or);
NETSW_WR_ENTRY(port_prio);
NETSW_WR_ENTRY(non_vid);
NETSW_WR_ENTRY(drop_non_vlan);
NETSW_WR_ENTRY(drop_tagged);
NETSW_WR_ENTRY(ingress);
NETSW_WR_ENTRY(replace_vid);
NETSW_WR_ENTRY(replace_prio);
NETSW_WR_ENTRY(mac_802_1x);
NETSW_WR_ENTRY(src_addr_filter);
NETSW_WR_ENTRY(vlan_lookup_0);
NETSW_WR_ENTRY(prio_queue);
NETSW_WR_ENTRY(rx_prio_rate);
NETSW_WR_ENTRY(tx_prio_rate);
NETSW_WR_ENTRY(limit);
NETSW_WR_ENTRY(limit_port_based);
NETSW_WR_ENTRY(limit_packet_based);
NETSW_WR_ENTRY(limit_flow_ctrl);
NETSW_WR_ENTRY(limit_cnt_ifg);
NETSW_WR_ENTRY(limit_cnt_pre);
NETSW_WR_ENTRY(rx_p0_rate);
NETSW_WR_ENTRY(rx_p1_rate);
NETSW_WR_ENTRY(rx_p2_rate);
NETSW_WR_ENTRY(rx_p3_rate);
NETSW_WR_ENTRY(rx_p4_rate);
NETSW_WR_ENTRY(rx_p5_rate);
NETSW_WR_ENTRY(rx_p6_rate);
NETSW_WR_ENTRY(rx_p7_rate);
NETSW_WR_ENTRY(tx_q0_rate);
NETSW_WR_ENTRY(tx_q1_rate);
NETSW_WR_ENTRY(tx_q2_rate);
NETSW_WR_ENTRY(tx_q3_rate);
NETSW_WR_ENTRY(color_map);
NETSW_WR_ENTRY(tc_map);
NETSW_WR_ENTRY(back_pressure);
NETSW_WR_ENTRY(force_flow_ctrl);
NETSW_WR_ENTRY(pass_all);
NETSW_WR_ENTRY(tail_tag);

NETSW_WR_ENTRY(cust_vid);
NETSW_WR_ENTRY(sr_1_vid);
NETSW_WR_ENTRY(sr_2_vid);
NETSW_WR_ENTRY(sr_1_type);
NETSW_WR_ENTRY(sr_2_type);

NETSW_WR_ENTRY(pme_ctrl);
NETSW_WR_ENTRY(pme_status);

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
NETSW_WR_ENTRY(acl_rule_index);
NETSW_WR_ENTRY(acl_info);
NETSW_RD_ENTRY(acl_table);

NETSW_WR_ENTRY(p_index);
NETSW_WR_ENTRY(q_index);
NETSW_WR_ENTRY(police_type);
NETSW_WR_ENTRY(non_dscp_color);
NETSW_WR_ENTRY(police_drop_all);
NETSW_WR_ENTRY(police_port_based);
NETSW_WR_ENTRY(color_mark);
NETSW_WR_ENTRY(color_remap);
NETSW_WR_ENTRY(drop_srp);
NETSW_WR_ENTRY(color_aware);
NETSW_WR_ENTRY(police);
NETSW_WR_ENTRY(q_cir);
NETSW_WR_ENTRY(q_pir);
NETSW_WR_ENTRY(q_cbs);
NETSW_WR_ENTRY(q_pbs);
NETSW_WR_ENTRY(wred_max);
NETSW_WR_ENTRY(wred_min);
NETSW_WR_ENTRY(wred_multiplier);
NETSW_RD_ENTRY(wred_avg_size);
NETSW_WR_ENTRY(wred_q_max);
NETSW_WR_ENTRY(wred_q_min);
NETSW_WR_ENTRY(wred_q_multiplier);
NETSW_RD_ENTRY(wred_q_avg_size);
NETSW_WR_ENTRY(wred_random_drop);
NETSW_WR_ENTRY(wred_drop_gyr);
NETSW_WR_ENTRY(wred_drop_yr);
NETSW_WR_ENTRY(wred_drop_r);
NETSW_WR_ENTRY(wred_drop_all);
NETSW_RD_ENTRY(wred_q_pmon);

NETSW_WR_ENTRY(q_scheduling);
NETSW_WR_ENTRY(q_shaping);
#ifdef MTI_PREEMPT_ENABLE
NETSW_WR_ENTRY(preempt);
#endif
NETSW_WR_ENTRY(q_tx_ratio);
NETSW_WR_ENTRY(q_credit_hi);
NETSW_WR_ENTRY(q_credit_lo);
NETSW_WR_ENTRY(q_credit_incr);
NETSW_WR_ENTRY(srp);

NETSW_WR_ENTRY(qm_drop);
NETSW_WR_ENTRY(qm_burst);
NETSW_WR_ENTRY(qm_resv_space);
NETSW_WR_ENTRY(qm_hi);
NETSW_WR_ENTRY(qm_lo);
NETSW_RD_ENTRY(qm_tx_used);
NETSW_RD_ENTRY(qm_tx_avail);
NETSW_RD_ENTRY(qm_tx_calc);

NETSW_WR_ENTRY(mmd_id);
NETSW_WR_ENTRY(mmd_reg);
NETSW_WR_ENTRY(mmd_val);

NETSW_RD_ENTRY(rx_flow_ctrl);
NETSW_RD_ENTRY(tx_flow_ctrl);

NETSW_WR_ENTRY(duplex);
NETSW_WR_ENTRY(speed);
NETSW_WR_ENTRY(mac_oper);
NETSW_WR_ENTRY(vlan_restricted);
NETSW_WR_ENTRY(vlan_untagged);

#ifdef CONFIG_KSZ_STP
NETSW_RD_ENTRY(stp_info);
NETSW_WR_ENTRY(stp_on);
NETSW_WR_ENTRY(stp_prio);
NETSW_WR_ENTRY(stp_admin_path_cost);
NETSW_WR_ENTRY(stp_path_cost);
NETSW_WR_ENTRY(stp_admin_edge);
NETSW_WR_ENTRY(stp_auto_edge);
NETSW_WR_ENTRY(stp_mcheck);
NETSW_WR_ENTRY(stp_admin_p2p);
#ifdef CONFIG_KSZ_MSTP
NETSW_WR_ENTRY(stp_auto_isolate);
#endif
#endif

#ifdef CONFIG_KSZ_MRP
NETSW_WR_ENTRY(mmrpEnabled);
NETSW_WR_ENTRY(mmrp_mac);
NETSW_WR_ENTRY(mmrp_svc);
NETSW_WR_ENTRY(mmrp_reg);
NETSW_WR_ENTRY(mvrpEnabled);
NETSW_WR_ENTRY(mvrp_vid);
NETSW_WR_ENTRY(mvrp_reg);
#endif

#ifdef CONFIG_KSZ_MSRP
NETSW_WR_ENTRY(msrpEnabled);
#endif

#ifdef CONFIG_KSZ_AVB
NETSW_WR_ENTRY(asCapable);
NETSW_WR_ENTRY(q_delta);
NETSW_WR_ENTRY(q_admin_mbps);
NETSW_WR_ENTRY(q_admin_slope);
NETSW_RD_ENTRY(q_oper_slope);
NETSW_WR_ENTRY(q_alg);
NETSW_RD_ENTRY(sr_a_rx_prio);
NETSW_WR_ENTRY(sr_a_tx_prio);
NETSW_RD_ENTRY(sr_a_boundary);
NETSW_WR_ENTRY(sr_a_latency);
NETSW_RD_ENTRY(sr_b_rx_prio);
NETSW_WR_ENTRY(sr_b_tx_prio);
NETSW_RD_ENTRY(sr_b_boundary);
NETSW_WR_ENTRY(sr_b_latency);
NETSW_WR_ENTRY(max_frame_size);
NETSW_WR_ENTRY(max_int_frames);
NETSW_WR_ENTRY(class_prio);
#endif

NETSW_WR_ENTRY(linkmd);
NETSW_WR_ENTRY(sqi);
NETSW_WR_ENTRY(mac_loopback);
NETSW_WR_ENTRY(phy_loopback);
NETSW_WR_ENTRY(remote_loopback);

static struct attribute *lan_attrs[] = {
	&lan_attr_info.attr,
	&lan_attr_version.attr,
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
	&lan_attr_hsr_table.attr,
	&lan_attr_aging.attr,
	&lan_attr_fast_aging.attr,
	&lan_attr_link_aging.attr,
	&lan_attr_bcast_per.attr,
	&lan_attr_mcast_storm.attr,
	&lan_attr_tx_queue_based.attr,
	&lan_attr_diffserv_map.attr,
	&lan_attr_p_802_1p_map.attr,
	&lan_attr_vlan.attr,
	&lan_attr_null_vid.attr,
	&lan_attr_drop_inv_vid.attr,
	&lan_attr_macaddr.attr,
	&lan_attr_mirror_mode.attr,
	&lan_attr_igmp_snoop.attr,
	&lan_attr_ipv6_mld_snoop.attr,
	&lan_attr_ipv6_mld_option.attr,
	&lan_attr_aggr_backoff.attr,
	&lan_attr_no_exc_drop.attr,
	&lan_attr_jumbo_packet.attr,
	&lan_attr_legal_packet.attr,
	&lan_attr_length_check.attr,
	&lan_attr_back_pressure.attr,
	&lan_attr_sw_flow_ctrl.attr,
	&lan_attr_sw_half_duplex.attr,
#ifdef SWITCH_10_MBIT
	&lan_attr_sw_10_mbit.attr,
#endif
	&lan_attr_fair_flow_ctrl.attr,
	&lan_attr_vlan_bound.attr,
	&lan_attr_double_tag.attr,
	&lan_attr_isp.attr,
	&lan_attr_hsr.attr,
	&lan_attr_hsr_redbox_id.attr,
	&lan_attr_hsr_net_id.attr,
	&lan_attr_mtu.attr,
	&lan_attr_unk_ucast_fwd.attr,
	&lan_attr_unk_ucast_ports.attr,
	&lan_attr_unk_mcast_fwd.attr,
	&lan_attr_unk_mcast_ports.attr,
	&lan_attr_unk_vid_fwd.attr,
	&lan_attr_unk_vid_ports.attr,
	&lan_attr_pass_pause.attr,
	&lan_attr_pme.attr,
	&lan_attr_pme_polarity.attr,

	&lan_attr_host_port.attr,
	&lan_attr_ports.attr,
	&lan_attr_dev_start.attr,
	&lan_attr_port_start.attr,
	&lan_attr_vlan_start.attr,
	&lan_attr_avb.attr,
	&lan_attr_stp.attr,
	&lan_attr_two_dev.attr,
	&lan_attr_authen.attr,

	&lan_attr_alu_fid.attr,
	&lan_attr_alu_use_fid.attr,
	&lan_attr_alu_override.attr,
	&lan_attr_alu_valid.attr,
	&lan_attr_alu_mstp.attr,
	&lan_attr_alu_prio.attr,
	&lan_attr_alu_src.attr,
	&lan_attr_alu_dst.attr,
	&lan_attr_alu_ports.attr,
	&lan_attr_alu_addr.attr,
	&lan_attr_alu_type.attr,
	&lan_attr_alu_index.attr,
	&lan_attr_alu_info.attr,

	&lan_attr_vlan_valid.attr,
	&lan_attr_vlan_ports.attr,
	&lan_attr_vlan_untag.attr,
	&lan_attr_vlan_fid.attr,
	&lan_attr_vlan_mstp.attr,
	&lan_attr_vlan_prio.attr,
	&lan_attr_vlan_option.attr,
	&lan_attr_vlan_index.attr,
	&lan_attr_vlan_info.attr,
	&lan_attr_vid2fid.attr,
	&lan_attr_fid2mstid.attr,

#ifdef CONFIG_KSZ_STP
	&lan_attr_stp_br_info.attr,
	&lan_attr_stp_br_on.attr,
	&lan_attr_stp_br_prio.attr,
	&lan_attr_stp_br_fwd_delay.attr,
	&lan_attr_stp_br_hello_time.attr,
	&lan_attr_stp_br_max_age.attr,
	&lan_attr_stp_br_tx_hold.attr,
	&lan_attr_stp_version.attr,
#ifdef CONFIG_KSZ_MSTP
	&lan_attr_stp_br_max_hops.attr,
	&lan_attr_stp_msti.attr,
	&lan_attr_stp_msti_vid.attr,
	&lan_attr_stp_mstp_cfg.attr,
	&lan_attr_stp_mstp_name.attr,
#endif
#endif

#ifdef CONFIG_KSZ_MSRP
	&lan_attr_msrp_info.attr,
	&lan_attr_msrpEnabled.attr,
#endif

#ifdef CONFIG_KSZ_AVB
	&lan_attr_msrp_sr_a.attr,
#endif

#ifdef CONFIG_KSZ_HSR
	&lan_attr_hsr_valid.attr,
	&lan_attr_hsr_age_cnt.attr,
	&lan_attr_hsr_path_id.attr,
	&lan_attr_hsr_addr.attr,
	&lan_attr_hsr_index.attr,
	&lan_attr_hsr_info.attr,
	&lan_attr_hsr_state.attr,
#endif

	&lan_attr_no_color.attr,
	&lan_attr_color_red.attr,
	&lan_attr_color_yellow.attr,
	&lan_attr_color_green.attr,

	&lan_attr_vlan_filter_dynamic.attr,
	&lan_attr_vlan_filter_static.attr,

	NULL
};

static struct attribute *sw_attrs[] = {
	&sw_attr_mib.attr,

	&sw_attr_vid.attr,
	&sw_attr_member.attr,
	&sw_attr_bcast_storm.attr,
	&sw_attr_mstp.attr,
	&sw_attr_rx.attr,
	&sw_attr_tx.attr,
	&sw_attr_learn.attr,
	&sw_attr_power.attr,
	&sw_attr_mirror_port.attr,
	&sw_attr_mirror_rx.attr,
	&sw_attr_mirror_tx.attr,
	&sw_attr_diffserv.attr,
	&sw_attr_p_802_1p.attr,
	&sw_attr_prio_vlan.attr,
	&sw_attr_prio_mac.attr,
	&sw_attr_prio_acl.attr,
	&sw_attr_prio_highest.attr,
	&sw_attr_prio_or.attr,
	&sw_attr_port_prio.attr,
	&sw_attr_non_vid.attr,
	&sw_attr_drop_non_vlan.attr,
	&sw_attr_drop_tagged.attr,
	&sw_attr_ingress.attr,
	&sw_attr_replace_vid.attr,
	&sw_attr_replace_prio.attr,
	&sw_attr_mac_802_1x.attr,
	&sw_attr_src_addr_filter.attr,
	&sw_attr_vlan_lookup_0.attr,
	&sw_attr_prio_queue.attr,
	&sw_attr_rx_prio_rate.attr,
	&sw_attr_tx_prio_rate.attr,
	&sw_attr_limit.attr,
	&sw_attr_limit_port_based.attr,
	&sw_attr_limit_packet_based.attr,
	&sw_attr_limit_flow_ctrl.attr,
	&sw_attr_limit_cnt_ifg.attr,
	&sw_attr_limit_cnt_pre.attr,
	&sw_attr_rx_p0_rate.attr,
	&sw_attr_rx_p1_rate.attr,
	&sw_attr_rx_p2_rate.attr,
	&sw_attr_rx_p3_rate.attr,
	&sw_attr_rx_p4_rate.attr,
	&sw_attr_rx_p5_rate.attr,
	&sw_attr_rx_p6_rate.attr,
	&sw_attr_rx_p7_rate.attr,
	&sw_attr_tx_q0_rate.attr,
	&sw_attr_tx_q1_rate.attr,
	&sw_attr_tx_q2_rate.attr,
	&sw_attr_tx_q3_rate.attr,
	&sw_attr_color_map.attr,
	&sw_attr_tc_map.attr,
	&sw_attr_back_pressure.attr,
	&sw_attr_force_flow_ctrl.attr,
	&sw_attr_pass_all.attr,
	&sw_attr_tail_tag.attr,

	&sw_attr_cust_vid.attr,
	&sw_attr_sr_1_vid.attr,
	&sw_attr_sr_2_vid.attr,
	&sw_attr_sr_1_type.attr,
	&sw_attr_sr_2_type.attr,

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
	&sw_attr_acl_rule_index.attr,
	&sw_attr_acl_info.attr,
	&sw_attr_acl_table.attr,

	&sw_attr_p_index.attr,
	&sw_attr_q_index.attr,
	&sw_attr_police_type.attr,
	&sw_attr_non_dscp_color.attr,
	&sw_attr_police_drop_all.attr,
	&sw_attr_police_port_based.attr,
	&sw_attr_color_mark.attr,
	&sw_attr_color_remap.attr,
	&sw_attr_drop_srp.attr,
	&sw_attr_color_aware.attr,
	&sw_attr_police.attr,

	&sw_attr_q_cir.attr,
	&sw_attr_q_pir.attr,
	&sw_attr_q_cbs.attr,
	&sw_attr_q_pbs.attr,

	&sw_attr_wred_max.attr,
	&sw_attr_wred_min.attr,
	&sw_attr_wred_multiplier.attr,
	&sw_attr_wred_avg_size.attr,
	&sw_attr_wred_q_max.attr,
	&sw_attr_wred_q_min.attr,
	&sw_attr_wred_q_multiplier.attr,
	&sw_attr_wred_q_avg_size.attr,
	&sw_attr_wred_random_drop.attr,
	&sw_attr_wred_drop_gyr.attr,
	&sw_attr_wred_drop_yr.attr,
	&sw_attr_wred_drop_r.attr,
	&sw_attr_wred_drop_all.attr,
	&sw_attr_wred_q_pmon.attr,

	&sw_attr_q_scheduling.attr,
	&sw_attr_q_shaping.attr,
#ifdef MTI_PREEMPT_ENABLE
	&sw_attr_preempt.attr,
#endif
	&sw_attr_q_tx_ratio.attr,
	&sw_attr_q_credit_hi.attr,
	&sw_attr_q_credit_lo.attr,
	&sw_attr_q_credit_incr.attr,
	&sw_attr_srp.attr,

	&sw_attr_qm_drop.attr,
	&sw_attr_qm_burst.attr,
	&sw_attr_qm_resv_space.attr,
	&sw_attr_qm_hi.attr,
	&sw_attr_qm_lo.attr,
	&sw_attr_qm_tx_used.attr,
	&sw_attr_qm_tx_avail.attr,
	&sw_attr_qm_tx_calc.attr,

	&sw_attr_mmd_id.attr,
	&sw_attr_mmd_reg.attr,
	&sw_attr_mmd_val.attr,

	&sw_attr_rx_flow_ctrl.attr,
	&sw_attr_tx_flow_ctrl.attr,

	&sw_attr_duplex.attr,
	&sw_attr_speed.attr,
	&sw_attr_mac_oper.attr,
	&sw_attr_vlan_restricted.attr,
	&sw_attr_vlan_untagged.attr,

#ifdef CONFIG_KSZ_STP
	&sw_attr_stp_info.attr,
	&sw_attr_stp_on.attr,
	&sw_attr_stp_prio.attr,
	&sw_attr_stp_admin_path_cost.attr,
	&sw_attr_stp_path_cost.attr,
	&sw_attr_stp_admin_edge.attr,
	&sw_attr_stp_auto_edge.attr,
	&sw_attr_stp_mcheck.attr,
	&sw_attr_stp_admin_p2p.attr,
#ifdef CONFIG_KSZ_MSTP
	&sw_attr_stp_auto_isolate.attr,
#endif
#endif

#ifdef CONFIG_KSZ_MRP
	&sw_attr_mmrpEnabled.attr,
	&sw_attr_mmrp_mac.attr,
	&sw_attr_mmrp_svc.attr,
	&sw_attr_mmrp_reg.attr,
	&sw_attr_mvrpEnabled.attr,
	&sw_attr_mvrp_vid.attr,
	&sw_attr_mvrp_reg.attr,
#endif

#ifdef CONFIG_KSZ_MSRP
	&sw_attr_msrpEnabled.attr,
#endif

#ifdef CONFIG_KSZ_AVB
	&sw_attr_asCapable.attr,
	&sw_attr_q_delta.attr,
	&sw_attr_q_admin_mbps.attr,
	&sw_attr_q_admin_slope.attr,
	&sw_attr_q_oper_slope.attr,
	&sw_attr_q_alg.attr,
	&sw_attr_sr_a_rx_prio.attr,
	&sw_attr_sr_a_tx_prio.attr,
	&sw_attr_sr_a_boundary.attr,
	&sw_attr_sr_a_latency.attr,
	&sw_attr_sr_b_rx_prio.attr,
	&sw_attr_sr_b_tx_prio.attr,
	&sw_attr_sr_b_boundary.attr,
	&sw_attr_sr_b_latency.attr,
	&sw_attr_max_frame_size.attr,
	&sw_attr_max_int_frames.attr,
	&sw_attr_class_prio.attr,
#endif

	&sw_attr_linkmd.attr,
	&sw_attr_sqi.attr,
	&sw_attr_mac_loopback.attr,
	&sw_attr_phy_loopback.attr,
	&sw_attr_remote_loopback.attr,

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
	int j;
	uint n;

	if (sw->overrides & SYSFS_PHY_PORT)
		n = sw->port_cnt;
	else
		n = sw->mib_port_cnt + 1;
	j = 0;
	if (sw->overrides & SYSFS_1_BASE)
		j = 1;
	for (i = 0; i < n; i++) {
		sw_group.name = sw_name[i + j];
		sw_group.attrs = info->port_attrs[i];
		sysfs_remove_group(&dev->kobj, &sw_group);
		kfree(info->port_attrs[i]);
		info->port_attrs[i] = NULL;
		info->ksz_port_attrs[i] = NULL;
	}
	ksz_sw_dev_attrs_ptr = ksz_sw_dev_attrs;

	sysfs_remove_group(&dev->kobj, &lan_group);
}

static int init_sw_sysfs(struct ksz_sw *sw, struct ksz_sw_sysfs *info,
	struct device *dev)
{
	int err;
	int i;
	int j;
	uint n;
	uint p;
	char *file;

	err = sysfs_create_group(&dev->kobj, &lan_group);
	if (err)
		return err;
	if (sw->overrides & SYSFS_PHY_PORT)
		n = sw->port_cnt;
	else
		n = sw->mib_port_cnt + 1;
	j = 0;
	if (sw->overrides & SYSFS_1_BASE)
		j = 1;
	for (i = 0; i < n; i++) {
		p = i;
		if (!(sw->overrides & SYSFS_PHY_PORT))
			p = sw->ops->get_phy_port(sw, i + 1);
		file = NULL;
		if (p >= sw->phy_port_cnt || p == sw->HOST_PORT)
			file = "0_linkmd";
		err = alloc_dev_attr(sw_attrs,
			sizeof(sw_attrs) / sizeof(void *), i + j,
			&info->ksz_port_attrs[i], &info->port_attrs[i],
			file, &ksz_sw_dev_attrs_ptr);
		if (err)
			return err;
		sw_group.name = sw_name[i + j];
		sw_group.attrs = info->port_attrs[i];
		err = sysfs_create_group(&dev->kobj, &sw_group);
		if (err)
			return err;
	}
	return err;
}

