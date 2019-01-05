/**
 * Microchip HSR driver header
 *
 * Copyright (c) 2016 Microchip Technology Inc.
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

#include "hsr_main.h"
#include "ksz_hsr_api.h"


struct hsr_frame_info {
	struct sk_buff *skb_std;
	struct sk_buff *skb_hsr;
	struct hsr_port *port_rcv;
	struct hsr_node *node_src;
	u16 sequence_nr;
	u16 *proto;
	struct hsr_tag *hsr_tag;
	bool is_supervision;
	bool is_vlan;
	bool is_local_dest;
	bool is_local_exclusive;
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
	struct hsr_port hsr_ports[HSR_PT_PORTS];
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
	u32 cap;
	u16 member;
	u16 part_cnt;
	struct delayed_work chk_ring;
	u16 seq_num;
	u16 check:1;
	u16 ring:1;
	u16 p1_down:1;
	u16 p2_down:1;
	u16 p1_lost:1;
	u16 p2_lost:1;

	struct sw_dev_info *dev_info;
	uint notifications;

	uint overrides;

	const struct hsr_ops *ops;
};

#endif
