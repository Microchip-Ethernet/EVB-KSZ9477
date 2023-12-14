/**
 * Microchip HSR driver header
 *
 * Copyright (c) 2016-2023 Microchip Technology Inc.
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


#ifndef KSZ_HSR_H
#define KSZ_HSR_H

#ifdef CONFIG_KSZ_USE_NEW_HSR
#define USE_NEW_HSR
#endif

#ifdef USE_NEW_HSR
#include "hsr_main_6_1.h"
#else
#include "hsr_main.h"
#endif
#include "ksz_hsr_api.h"


#ifdef USE_NEW_HSR

#ifdef CONFIG_KSZ_SWITCH
struct hsr_dev_info {
	struct net_device *dev;
	u8 member;
};
#endif

struct hsr_node {
	struct list_head	mac_list;
	/* Protect R/W access to seq_out */
	spinlock_t		seq_out_lock;
	unsigned char		macaddress_A[ETH_ALEN];
	unsigned char		macaddress_B[ETH_ALEN];
	/* Local slave through which AddrB frames are received from this node */
	enum hsr_port_type	addr_B_port;
	unsigned long		time_in[HSR_PT_PORTS];
	bool			time_in_stale[HSR_PT_PORTS];
	unsigned long		time_out[HSR_PT_PORTS];
	/* if the node is a SAN */
	bool			san_a;
	bool			san_b;
	u16			seq_out[HSR_PT_PORTS];
	bool			removed;
	struct rcu_head		rcu_head;
#ifdef CONFIG_KSZ_SWITCH
	bool			is_same_addr;
	int			slave;
#endif
};
#endif

struct hsr_frame_info {
	struct sk_buff *skb_std;
	struct sk_buff *skb_hsr;
	struct sk_buff *skb_prp;
	struct hsr_port *port_rcv;
	struct hsr_node *node_src;
	u16 sequence_nr;
#ifdef CONFIG_KSZ_SWITCH
	struct sk_buff *skb_out;
	struct hsr_node *node_dst;
	u8 out;
	u8 skb_cnt;
#ifndef USE_NEW_HSR
	u16 *proto;
	struct hsr_tag *hsr_tag;
#endif
	bool fwd_hsr;
	bool is_hsr_dest;
	bool is_hsr_exclusive;
	bool is_redbox_dest;
	bool is_redbox_exclusive;
#endif
	bool is_supervision;
	bool is_vlan;
	bool is_local_dest;
	bool is_local_exclusive;
	bool is_from_san;
};


struct ksz_hsr_info;

struct hsr_ops {
	void (*change_addr)(struct ksz_hsr_info *info, struct net_device *dev);
	void (*link_change)(struct ksz_hsr_info *info, int link1, int link2);
	void (*check_announce)(struct ksz_hsr_info *info);
	u8 (*get_redbox_id)(struct ksz_hsr_info *info);
	void (*set_redbox_id)(struct ksz_hsr_info *info, u8 id);
	u8 (*get_net_id)(struct ksz_hsr_info *info);
	void (*set_net_id)(struct ksz_hsr_info *info, u8 id);

	int (*dev_req)(struct ksz_hsr_info *hsr, char *arg, void *info);

};


struct ksz_hsr_info {
	u16 vid;
	u8 src_addr[ETH_ALEN];

	void *sw_dev;
	struct net_device *dev;
	struct net_device *redbox;
	struct hsr_priv hsr;
#ifdef USE_NEW_HSR
	struct hsr_port *hsr_ports[HSR_PT_PORTS];
#else
	struct hsr_port hsr_ports[HSR_PT_PORTS];
#endif
	struct hsr_node *center;

	u8 master_sup_frame[80];
	u8 slave_sup_frame[80];
	u8 *tx_frame;
	struct hsr_sup_tag *hsr_stag;
	struct hsr_sup_tag *master_hsr_stag;
	struct hsr_sup_tag *slave_hsr_stag;
	struct hsr_frame_info frame;
	int master_len;
	int slave_len;
	int len;
	int state;
	u8 ports[2];
	u8 fwd_cnt;
	u8 hsr_index;
	u8 redbox_index;
	u32 cap;
	u16 member;
	u16 part_cnt;
	struct sk_buff_head txq;
	struct work_struct tx_proc;
	struct delayed_work chk_ring;
	u16 redbox_vlan;
	u16 seq_num;
	u16 check:1;
	u16 ring:1;
	u16 p1_down:1;
	u16 p2_down:1;
	u16 p1_lost:1;
	u16 p2_lost:1;
	u16 fwd_lane_a:1;
	u16 fwd_lane_b:1;
	u16 use_lane_b:1;
	u16 redbox_fwd:1;
	u16 redbox_up:1;
	u16 hsr_up:1;

	uint notifications;

	uint overrides;

	const struct hsr_ops *ops;
};

#endif
