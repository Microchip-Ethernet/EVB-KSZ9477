/**
 * Micrel MRP driver API header
 *
 * Copyright (c) 2015 Microchip Technology Inc.
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


#ifndef KSZ_MRP_API_H
#define KSZ_MRP_API_H

#ifndef ETH_ALEN
#define ETH_ALEN			6
#endif


enum {
	DEV_IOC_MRP_REPORT = DEV_IOC_LAST,
};

enum {
	DEV_MRP_ATTRIBUTE,
};

struct MRP_mac {
	u8 addr[ETH_ALEN];
} __packed;

struct MRP_vlan {
	u16 id;
} __packed;

enum {
	SRP_IGNORED,
	SRP_ASKING_FAILED,
	SRP_READY,
	SRP_READY_FAILED,
	SRP_ADVERTISE,
	SRP_FAILED,
};

struct SRP_listener {
	u8 id[8];
	u8 substate;
} __packed;

struct SRP_talker {
	u8 id[8];
	u8 dest[ETH_ALEN];
	u16 vlan_id;
	u16 MaxFrameSize;
	u16 MaxIntervalFrames;
	u8 priority:3;
	u8 rank:1;
	u8 reserved:4;
	u32 AccumulatedLatency;
	u8 bridge_id[8];
	u8 FailureCode;
} __packed;

enum {
	RFC_NO_ERROR,
	RFC_NO_BANDWIDTH,
	RFC_NO_RESOURCES,
	RFC_NO_BANDWIDTH_FOR_TRAFFIC_CLASS,
	RFC_STREAM_ID_USED,
	RFC_DEST_ADDR_USED,
	RFC_PREEMPTED_BY_RANK,
	RFC_LATENCY_CHANGED,
	RFC_PORT_IS_NOT_AVB,
	RFC_USE_DIFF_DEST_ADDR,
	RFC_OUT_OF_MSRP_RESOURCE,
	RFC_OUT_OF_MMRP_RESOURCE,
	RFC_CANNOT_STORE_DEST_ADDR,
	RFC_PRIORITY_IS_NOT_SR_CLASS,
	RFC_MAXFRAMESIZE_TOO_LARGE,
	RFC_MAXFANINPORTS_LIMIT_REACHED,
	RFC_FIRSTVALUE_CHANGED,
	RFC_VLAN_BLOCKED,
	RFC_VLAN_TAGGING_DISABLED,
	RFC_SR_CLASS_PRIORITY_MISMATCHED,
};

enum {
	SR_CLASS_UNDEFINED,
	SR_CLASS_A,
	SR_CLASS_B,
};

#define SR_CLASS_A_ID	6
#define SR_CLASS_B_ID	5

struct SRP_domain_class {
	u8 id;
	u8 priority;
	u16 vlan_id;
} __packed;

union mrp_data {
	struct MRP_mac mac;
	struct MRP_vlan vlan;
	struct SRP_talker talker;
	struct SRP_listener listener;
	struct SRP_domain_class domain;
} __packed;

enum {
	MRP_ACTION_RX,
	MRP_ACTION_TX,
	MRP_ACTION_LV,
	MRP_ACTION_ON,
	MRP_ACTION_OFF,

	MRP_ACTION_DBG,
};

enum {
	MRP_TYPE_UNKNOWN,
	MRP_TYPE_MAC,
	MRP_TYPE_VLAN,
	MRP_TYPE_TALKER,
	MRP_TYPE_LISTENER,
	MRP_TYPE_DOMAIN,
};

struct mrp_cfg_options {
	u8 action;
	u8 type;
	u8 port;
	u8 reserved;
	union mrp_data data;
} __packed;

#define SIZEOF_MRP_mac	\
	(sizeof(struct MRP_mac) + sizeof(u8) * 4)

#define SIZEOF_MRP_vlan	\
	(sizeof(struct MRP_vlan) + sizeof(u8) * 4)

#define SIZEOF_SRP_talker	\
	(sizeof(struct SRP_talker) + sizeof(u8) * 4)

#define SIZEOF_SRP_listener	\
	(sizeof(struct SRP_listener) + sizeof(u8) * 4)

#define SIZEOF_SRP_domain_class	\
	(sizeof(struct SRP_domain_class) + sizeof(u8) * 4)


int set_mac_lv(void *fd,
	int port, struct MRP_mac *mac);
int set_mac_rx(void *fd,
	int port, struct MRP_mac *mac);
int set_vlan_lv(void *fd,
	int port, struct MRP_vlan *vlan);
int set_vlan_rx(void *fd,
	int port, struct MRP_vlan *vlan);
int set_domain_lv(void *fd,
	int port, struct SRP_domain_class *domain);
int set_domain_rx(void *fd,
	int port, struct SRP_domain_class *domain);
int set_listener_lv(void *fd,
	int port, struct SRP_listener *listener);
int set_listener_rx(void *fd,
	int port, struct SRP_listener *listener);
int set_talker_lv(void *fd,
	int port, struct SRP_talker *talker);
int set_talker_rx(void *fd,
	int port, struct SRP_talker *talker);
int get_attribute(void *fd,
	int *port, int *type, int *action, void *buf, size_t size);

#endif
