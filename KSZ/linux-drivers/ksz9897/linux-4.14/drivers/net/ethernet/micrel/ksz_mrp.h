/**
 * Microchip MRP driver header
 *
 * Copyright (c) 2015-2019 Microchp Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2014-2015 Micrel, Inc.
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


#ifndef KSZ_MRP_H
#define KSZ_MRP_H

#include "ksz_mrp_api.h"

#if 0
#define DBG_MRP
#endif
#if 0
#define DBG_MRP_APP
#endif
#if 0
#define DBG_MRP_REG
#endif
#if 0
#define DBG_MRP_RX
#endif
#if 0
#define DBG_MRP_TX
#endif
#if 0
#define MRP_BASIC
#endif
#ifdef CONFIG_KSZ_MRP
#include "mrp.h"
#endif


struct mrp_node {
	void *data;
	struct mrp_node *next;
};

struct mrp_node_anchor {
	struct mrp_node anchor;
	struct mrp_node *last;
	int cnt;
};

#ifdef CONFIG_KSZ_MSRP
struct SRP_bridge_base {
	uint msrpEnabledStatus:1;
	uint msrpTalkerPruning:1;
	uint msrpMaxFanInPorts;
	uint msrpLatencyMaxFrameSize;
};

struct SRP_bridge_port {
	uint msrpPortEnabledStatus:1;
	uint Failed_Registrations;
	u8 Last_PDU_Origin[ETH_ALEN];
	u16 SR_PVID;
};

struct SRP_reserv;

struct SRP_stream {
	u8 id[8];
	u8 dest[ETH_ALEN];
	u16 vlan_id;
	u16 MaxFrameSize;
	u16 MaxIntervalFrames;
	u8 reserved:4;
	u8 rank:1;
	u8 priority:3;
	u32 latency;
	u32 bandwidth;

	u8 in_port;
	struct SRP_reserv *t_reserv;

	struct SRP_stream *id_prev;
	struct SRP_stream *id_next;
	struct SRP_stream *dest_prev;
	struct SRP_stream *dest_next;
} __packed;

enum {
	SRP_TALKER,
	SRP_LISTENER,
};

#define SRP_ASKING_FAILED_SCALE		(1 << SRP_ASKING_FAILED)
#define SRP_READY_SCALE			(1 << SRP_READY)
#define SRP_READY_FAILED_SCALE		(1 << SRP_READY_FAILED)

struct SRP_reserv {
	u8 id[8];
	u8 direction;
	u8 declaration;
	u32 latency;
	u8 bridge_id[8];
	u8 rx_code;
	u8 code;
	u32 code_bits;
	u16 tx_ports;

	uint dropped_frames;
	u64 streamAge;
	unsigned long ticks;

	struct SRP_stream *stream;
	struct SRP_reserv *pair;

	struct SRP_reserv *next;
	struct SRP_reserv *prev;
};
#endif

#ifdef CONFIG_KSZ_AVB
struct SRP_bandwidth_availability_parameter {
	u8 traffic_class;
	int deltaBandwidth;
	u32 adminIdleSlope;
	u32 operIdleSlope;
};

struct SRP_latency_parameter {
	u8 traffic_class;
	u32 portTcMaxLatency;
};

struct SRP_priority_regeneration_override {
	u8 received_priority;
	u8 regenerated_priority;
	int SRPdomainBoundaryPort;
};

struct SRP_transmission_selection_algorithm {
	u8 traffic_class;
	int algorithm;
};

struct mrp_traffic_info {
	u32 bandwidth_delta;
	u32 bandwidth_max;
	u32 bandwidth_left;
	u32 bandwidth_used;
	u32 bandwidth_set;
	u32 *bandwidth_avail;
	u32 *bandwidth_other;
	u32 max_frame_size;
	u8 queue;

#ifdef CONFIG_KSZ_MSRP
	struct mrp_node_anchor active;
	struct mrp_node_anchor passive;
#endif
};
#endif

struct mrp_report {
	void *attrib;
	u8 action;
	u8 type;
	u8 port;
	struct mrp_report *next;
};

#define SRP_PORT_AVAIL			(mrp->mask)
#define SRP_PORT_OTHER			(mrp->other)
#define SRP_PORT_SET			(1 << 11)
#define SRP_PORT_DROP			(1 << 12)
#define SRP_PORT_IGNORE			(1 << 13)
#define SRP_PORT_BLACKLIST		(1 << 14)
#define SRP_PORT_READY			(1 << 15)

struct mrp_mac_info {
	u16 fid;
	u8 addr[ETH_ALEN];
	u16 ports;
	u16 set_ports;
	u16 mrp_ports;
	u16 srp_ports;
	u16 rx_ports;
	u16 tx_ports;
	u8 index;
	unsigned long ticks;
};

struct mrp_vlan_info {
	u16 vid;
	u16 fid;
	u8 addr[ETH_ALEN];
	u16 ports;
	u16 set_ports;
	u16 rx_ports;
	u16 tx_ports;
	u8 index;
};

struct srp_stream_info {
	struct SRP_reserv *reserv;
	u8 *id;
	u64 age;
	u8 rank;
	u8 mark:1;
};

#ifdef CONFIG_KSZ_AVB
struct mrp_port_info {
	u32 bandwidth_max;
	u32 bandwidth_left;
	u32 bandwidth_used;
	u32 speed;
	u32 max_frame_size;
	u32 max_interval_frames;
	u64 age;
	u32 link:1;
	u32 duplex:1;
	u8 index;
	u16 credit[PRIO_QUEUES];
	int deltaBandwidth;
	struct mrp_traffic_info traffic[2];

	struct SRP_bandwidth_availability_parameter bandwidth[PRIO_QUEUES];
	struct SRP_latency_parameter latency[2];
	struct SRP_priority_regeneration_override priority[SR_CLASS_NUM];
	struct SRP_transmission_selection_algorithm algorithm[PRIO_QUEUES];

#ifdef CONFIG_KSZ_MSRP
	struct SRP_bridge_port status;

	struct SRP_reserv declared;
	struct SRP_reserv registered;
#endif
};
#endif

struct mrp_info;

struct mrp_work {
	struct work_struct work;
	struct completion done;
	struct mrp_info *mrp;
	struct sk_buff *skb;
	int cmd;
	int subcmd;
	int option;
	int output;
	int result;
	int used;
	int index;
	union {
		struct mrp_cfg_options cfg;
		u8 data[8];
	} param;
	struct mrp_work *prev;
};

#define MRP_WORK_NUM			(1 << 4)
#define MRP_WORK_LAST			(MRP_WORK_NUM - 1)

struct mrp_access {
	struct work_struct work;
	int index;
	int head;
	int tail;
	struct mrp_work works[MRP_WORK_NUM];
};

struct mrp_ops {
	void (*init)(struct mrp_info *mrp);
	void (*exit)(struct mrp_info *mrp);
	int (*dev_req)(struct mrp_info *mrp, char *arg);

	void (*from_backup)(struct mrp_info *mrp, uint p);
	void (*to_backup)(struct mrp_info *mrp, uint p);
	void (*from_designated)(struct mrp_info *mrp, uint p, bool alt);
	void (*to_designated)(struct mrp_info *mrp, uint p);
	void (*tc_detected)(struct mrp_info *mrp, uint p);

	void (*chk_talker)(struct mrp_info *mrp, u8 port);

	void (*setup_vlan)(struct mrp_info *mrp, u16 vid,
			   struct ksz_vlan_table *vlan);
};

struct mrp_info {
	void *parent;
	struct mutex lock;
	struct mrp_access hw_access;
	struct workqueue_struct *access;
	struct sk_buff_head rxq;
	struct sk_buff_head txq;
	struct sk_buff_head macq;
	struct sk_buff_head vlanq;
	int macq_sched;
	int vlanq_sched;
	struct work_struct cfg_mac;
	struct work_struct cfg_vlan;
	struct work_struct rx_proc;
	u8 version;
	u8 ports;
	u8 started;
	u32 mask;
	u32 other;
	u32 rx_ports;
	u32 tx_ports;
	u32 mmrp_rx_ports;
	u32 mmrp_tx_ports;
	u32 mvrp_rx_ports;
	u32 mvrp_tx_ports;
	uint no_report;
	int listeners;

	const struct mrp_ops *ops;

#ifdef CONFIG_KSZ_AVB
	const u8 *id;
	u8 tc[8];
	u8 prio[SR_CLASS_NUM];
	u8 queue[SR_CLASS_NUM];
	u32 max_interference_size;
	u16 mcast_ports;
	int mcast_port_cnt;

	struct mrp_port_info port_info[TOTAL_PORT_NUM];

	struct SRP_domain_class domain[2];

#ifdef CONFIG_KSZ_MSRP
	struct SRP_bridge_base status;

	struct SRP_stream stream_by_id;
	struct SRP_stream stream_by_dest;

	struct mrp_node_anchor mac_down;
	struct mrp_node_anchor mac_up;
	struct mrp_node_anchor vlan_down;
	struct mrp_node_anchor vlan_up;
#endif
#endif

#ifdef CONFIG_KSZ_MRP
	struct mrp_node_anchor mac_list;
	struct mrp_node_anchor vlan_list;

	struct mrp_report *report_head;
	struct mrp_report *report_tail;

	struct mrp_port mrp_ports[TOTAL_PORT_NUM];
	int mac_tx[TOTAL_PORT_NUM];
	int vlan_tx[TOTAL_PORT_NUM];
	int srp_tx[TOTAL_PORT_NUM];
	u8 cvlan_addr[ETH_ALEN];
	u8 svlan_addr[ETH_ALEN];
#endif
};

#endif
