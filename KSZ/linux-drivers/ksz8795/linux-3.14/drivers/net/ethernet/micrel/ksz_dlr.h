/**
 * Micrel DLR driver header
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


#ifndef KSZ_DLR_H
#define KSZ_DLR_H

#include "ksz_dlr_api.h"


#define DLR_TAG_TYPE			0x80E1

#define DLR_RING_SUBTYPE		2

#define DLR_BEACON			0x1
#define DLR_NEIGH_CHK_REQ		0x2
#define DLR_NEIGH_CHK_RESP		0x3
#define DLR_LINK_STATUS			0x4
#define DLR_LOCATE_FAULT		0x5
#define DLR_ANNOUNCE			0x6
#define DLR_SIGN_ON			0x7
#define DLR_ADVERTISE			0x8
#define DLR_FLUSH_TABLES		0x9
#define DLR_LEARNING_UPDATE		0xA

#define DLR_PORT_NONE			0
#define DLR_PORT_1			1
#define DLR_PORT_2			2

#define RING_NORMAL_STATE		1
#define RING_FAULT_STATE		2

#define DLR_GW_ACTIVE_LISTEN_STATE	1
#define DLR_GW_ACTIVE_NORMAL_STATE	2
#define DLR_GW_FAULT_STATE		3


struct ksz_dlr_hdr {
	u8 ring_subtype;
	u8 ring_protocol_version;
	u8 frame_type;
	u8 src_port;
	u32 ip_addr;
	u32 seqid;
} __packed;

struct ksz_dlr_advertise {
	u8 state;
	u8 precedence;
	u32 interval;
	u32 timeout;
	u8 learning_update_enable;
} __packed;

struct ksz_dlr_announce {
	u8 ring_state;
} __packed;

struct ksz_dlr_beacon {
	u8 ring_state;
	u8 precedence;
	u32 interval;
	u32 timeout;
	u8 reserved[20];
} __packed;

struct ksz_dlr_flush_tables {
	u8 learning_update_enable;
} __packed;

struct ksz_dlr_status {
	u8 port1_active:1;
	u8 port2_active:1;
	u8 reserved:5;
	u8 neighbor:1;
} __packed;

struct ksz_dlr_node {
	u8 addr[ETH_ALEN];
	u32 ip_addr;
} __packed;

struct ksz_dlr_signon {
	u16 num;
	struct ksz_dlr_node node[1];
} __packed;

struct ksz_dlr_neigh_chk_resp {
	u8 src_port;
} __packed;

struct ksz_dlr_frame {
	struct ksz_dlr_hdr hdr;
	union {
		struct ksz_dlr_advertise advertise;
		struct ksz_dlr_announce announce;
		struct ksz_dlr_beacon beacon;
		struct ksz_dlr_flush_tables flush;
		struct ksz_dlr_status status;
		struct ksz_dlr_neigh_chk_resp neigh_chk_resp;
		struct ksz_dlr_signon signon;
		u8 reserved[30];
	} data;
} __packed;

struct ksz_dlr_tx_frame {
	struct vlan_ethhdr vlan;
	struct ksz_dlr_frame body;
} __packed;

struct ksz_dlr_update_frame {
	struct ethhdr eth;
	struct ksz_dlr_hdr hdr;
	u8 reserved[34];
} __packed;

struct ksz_dlr_rx_frame {
	struct vlan_ethhdr *vlan;
	struct ksz_dlr_frame *body;
};

#define DLR_SUPERVISOR_NUM	10

struct ksz_dlr_super_info {
	u8 prec_addr[ETH_ALEN + 1];
	u32 crc;
	int port;
	u32 timeout[2];
	u32 cnt;
	u32 last_cnt;
	u32 sent:1;
};

struct ksz_dlr_info;

struct dlr_work {
	struct sk_buff *skb;
	int cmd;
	int subcmd;
	int option;
	int used;
	int index;
	struct dlr_work *prev;
};

#define DLR_WORK_NUM			(1 << 4)
#define DLR_WORK_LAST			(DLR_WORK_NUM - 1)

struct dlr_work_info {
	struct work_struct work;
	int head;
	int tail;
int ready;
	struct dlr_work works[DLR_WORK_NUM];
};

struct dlr_ops {
	void (*change_addr)(struct ksz_dlr_info *dlr, u8 *addr);
	void (*link_change)(struct ksz_dlr_info *dlr, int link1, int link2);
	void (*timeout)(struct ksz_dlr_info *dir, int port);

	int (*dev_req)(struct ksz_dlr_info *dlr, char *arg);

	ssize_t (*sysfs_read)(struct ksz_dlr_info *dlr, int proc_num,
		ssize_t len, char *buf);
	void (*sysfs_write)(struct ksz_dlr_info *dlr, int proc_num, int num,
		const char *buf);

};

struct ksz_dlr_node_info {
	struct ksz_dlr_node signon;
	u32 p1_down:1;
	u32 p2_down:1;
	u32 p1_lost:1;
	u32 p2_lost:1;
};

struct ksz_dlr_beacon_info {
	u32 timer:1;
	u32 rcv_once:1;
	u32 timeout_start:1;
	u32 timeout_stop:1;
	u32 interval;
	u32 timeout;
	struct ksz_dlr_beacon last;
};

#define DLR_BEACON_LEAK_HACK		(1 << 0)
#define DLR_TEST_SEQ			(1 << 30)
#define DLR_TEST			(1 << 31)

struct ksz_dlr_info {
	u32 p1_down:1;
	u32 p2_down:1;
	u32 p1_lost:1;
	u32 p2_lost:1;
	u32 p1_rcvd:1;
	u32 p2_rcvd:1;
	u32 p1_set:1;
	u32 p2_set:1;
	u32 p1_timeout:1;
	u32 p2_timeout:1;
	u32 one_down:1;
	u32 both_down:1;
	u32 one_rcvd:1;
	u32 both_rcvd:1;
	u32 one_timeout:1;
	u32 both_timeout:1;
	u32 new_supervisor:1;
	u32 ann_rcvd:1;
	u32 ann_timeout:1;
	u32 ann_delay:1;
	u32 signon_delay:1;
	u32 signon_start:1;
	u32 new_val:1;
	u32 neigh_chk:1;
	u32 state_change:1;
	u32 wait_done:1;
	u32 reset:1;
	u32 reset_fault:1;
	u32 start:1;
	u32 chk_hw:1;

	struct ksz_dlr_gateway_capable attrib;

	u32 beacon_interval;
	u32 beacon_timeout;
	u32 ip_addr;
	u16 vid;
	u8 src_addr[ETH_ALEN];
	u8 next_node;
	u8 node;
	u8 port;
	u8 precedence;
	u8 ring_state;
	u8 drop_beacon;
	u8 skip_beacon;
	u8 LastBcnRcvPort;
	struct ksz_dlr_beacon_info beacon_info[2];
	u32 interval;

	void *sw_dev;
	struct net_device *dev;
	struct ksz_timer_info announce_timer_info;
	struct ksz_timer_info announce_timeout_timer_info;
	struct ksz_timer_info neigh_chk_timer_info;
	struct ksz_timer_info signon_timer_info;
	struct delayed_work announce_tx;
	struct delayed_work beacon_tx;
	u32 beacon_timeout_ports;
	struct work_struct beacon_rx_timeout;
	struct dlr_work_info work_info;

	struct ksz_dlr_tx_frame frame;
	struct ksz_dlr_update_frame update_frame;
	u8 signon_frame[2000];
	u8 signon_addr[ETH_ALEN];
	struct ksz_dlr_node_info nodes[500];
	u8 *tx_frame;
	int signon_port;
	int len;
	int cur_state;
	int state;
	int rx_port;
	int tx_port;
	int active_port;
	u32 seqid;
	u32 seqid_announce;
	u32 seqid_beacon;
	u32 seqid_signon;
	u32 seqid_chk[2];
	u32 seqid_first[2];
	u32 seqid_last[2];
	u32 seqid_rcv[2];
	u8 port_chk[2];
	u8 port_rcv[2];
	u32 seqid_accept[2];
	u8 ports[2];
	u16 member;

	struct ksz_dlr_super_info supers[DLR_SUPERVISOR_NUM];
	struct ksz_dlr_super_info *rogue_super;

	int seqid_cnt;
	int signon_space;
	u8 ignore_req;
	u8 req_cnt[2];
	u8 link_break;

	uint overrides;

	const struct dlr_ops *ops;
};

struct dlr_attributes {
	int info;
	int node;
	int prec;
	int interval;
	int timeout;
	int vid;
	int state;
	int port;

	int test;
	int req;
	int resp;
	int link;
	int learn;
	int fault;
	int signon;
	int clear_rapid;
	int clear_partial;

	int all;
	int rev;
	int topology;
	int network;
	int super;
	int super_cfg;
	int fault_cnt;
	int last_active_1;
	int last_active_2;
	int part_cnt;
	int part_list;
	int active_super_addr;
	int active_super_prec;
	int cap;
	int port_1;
	int port_2;
};

#endif
