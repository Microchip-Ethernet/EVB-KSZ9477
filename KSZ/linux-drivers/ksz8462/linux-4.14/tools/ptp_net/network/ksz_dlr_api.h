/**
 * Microchip DLR driver API header
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


#ifndef KSZ_DLR_API_H
#define KSZ_DLR_API_H

#ifndef ETH_ALEN
#define ETH_ALEN				6
#endif


enum {
	DEV_INFO_DLR_LINK = DEV_INFO_LAST,
	DEV_INFO_DLR_CFG,
};

#define DLR_INFO_LINK_LOST			(1 << 0)
#define DLR_INFO_CFG_CHANGE			(1 << 1)


#define STATUS_INVALID_ATTRIB_VALUE		0x09
#define STATUS_OBJECT_STATE_CONFLICT		0x0C
#define STATUS_REPLY_DATA_TOO_LARGE		0x11

#define SVC_GET_ATTRIBUTES_ALL			0x01
#define SVC_GET_ATTRIBUTE_SINGLE		0x0E
#define SVC_SET_ATTRIBUTE_SINGLE		0x10
#define SVC_GET_MEMBER				0x18


#define CIP_CLASS_ATTRIBUTES			0
#define CIP_INSTANCE_ATTRIBUTES			1


#define CLASS_DLR_OBJECT			0x47


#define CIP_SVC_S				24
#define CIP_CLASS_S				16
#define CIP_ATTR_S				8


#define DLR_GET_REVISION			1

#define DLR_REVISION				3


#define DLR_GET_NETWORK_TOPOLOGY		1
#define DLR_GET_NETWORK_STATUS			2
#define DLR_GET_RING_SUPERVISOR_STATUS		3
#define DLR_SET_RING_SUPERVISOR_CONFIG		4
#define DLR_SET_RING_FAULT_COUNT		5
#define DLR_GET_LAST_ACTIVE_NODE_ON_PORT_1	6
#define DLR_GET_LAST_ACTIVE_NODE_ON_PORT_2	7
#define DLR_GET_RING_PARTICIPANTS_COUNT		8
#define DLR_GET_RING_PARTICIPANTS_LIST		9
#define DLR_GET_ACTIVE_SUPERVISOR_ADDRESS	10
#define DLR_GET_ACTIVE_SUPERVISOR_PRECEDENCE	11
#define DLR_GET_CAPABILITY_FLAGS		12
#define DLR_SET_REDUNDANT_GATEWAY_CONFIG	13
#define DLR_GET_REDUNDANT_GATEWAY_STATUS	14
#define DLR_GET_ACTIVE_GATEWAY_ADDRESS		15
#define DLR_GET_ACTIVE_GATEWAY_PRECEDENCE	16
#define DLR_SET_IP_ADDRESS			17

#define SVC_DLR_VERIFY_FAULT_LOCATION		0x4B
#define SVC_DLR_CLEAR_RAPID_FAULTS		0x4C
#define SVC_DLR_RESTART_SIGN_ON			0x4D
#define SVC_DLR_CLEAR_GATEWAY_PARTIAL_FAULT	0x4E


#define DLR_TOPOLOGY_LINEAR			0
#define DLR_TOPOLOGY_RING			1

#define DLR_NET_NORMAL				0
#define DLR_NET_RING_FAULT			1
#define DLR_NET_UNEXPECTED_LOOP_DETECTED	2
#define DLR_NET_PARTIAL_FAULT			3
#define DLR_NET_RAPID_FAULT			4

#define DLR_STAT_BACKUP_SUPERVISOR		0
#define DLR_STAT_ACTIVE_SUPERVISOR		1
#define DLR_STAT_RING_NODE			2
#define DLR_STAT_NO_SUPERVISOR			3
#define DLR_STAT_NODE_NOT_SUPPORTED		4

#define DLR_CAP_ANNOUNCE_BASED			(1 << 0)
#define DLR_CAP_BEACON_BASED			(1 << 1)
#define DLR_CAP_SUPERVISOR_CAPABLE		(1 << 5)
#define DLR_CAP_GATEWAY_CAPABLE			(1 << 6)
#define DLR_CAP_FLUSH_TABLE_CAPABLE		(1 << 7)

#define DLR_STAT_NON_GATEWAY			0
#define DLR_STAT_BACKUP_GATEWAY			1
#define DLR_STAT_ACTIVE_GATEWAY			2
#define DLR_STAT_GATEWAY_FAULT_TO_UPLINK	3
#define DLR_STAT_GATEWAY_NOT_SUPPORTED		4
#define DLR_STAT_GATEWAY_FAULT_TO_NETWORK	5


struct ksz_dlr_active_node {
	u32 ip_addr;
	u8 addr[ETH_ALEN];
} __packed;

struct ksz_dlr_super_cfg {
	u8 enable;
	u8 prec;
	u32 beacon_interval;
	u32 beacon_timeout;
	u16 vid;
}  __packed;

struct ksz_dlr_gateway_cfg {
	u8 enable;
	u8 prec;
	u32 advertise_interval;
	u32 advertise_timeout;
	u8 learning_enable;
}  __packed;

struct ksz_dlr_non_super_capable_1 {
	u8 net_topology;
	u8 net_status;
} __packed;

struct ksz_dlr_super_capable_1 {
	u8 net_topology;
	u8 net_status;
	u8 super_status;
	struct ksz_dlr_super_cfg super_cfg;
	u16 fault_cnt;
	struct ksz_dlr_active_node last_active[2];
	u16 participants_cnt;
	struct ksz_dlr_active_node active_super_addr;
	u8 active_super_prec;
} __packed;

struct ksz_dlr_non_super_capable_2 {
	u8 net_topology;
	u8 net_status;
	struct ksz_dlr_active_node active_super_addr;
	u32 cap;
} __packed;

struct ksz_dlr_super_capable_2 {
	u8 net_topology;
	u8 net_status;
	u8 super_status;
	struct ksz_dlr_super_cfg super_cfg;
	u16 fault_cnt;
	struct ksz_dlr_active_node last_active[2];
	u16 participants_cnt;
	struct ksz_dlr_active_node active_super_addr;
	u8 active_super_prec;
	u32 cap;
} __packed;

struct ksz_dlr_gateway_capable {
	u8 net_topology;
	u8 net_status;
	u8 super_status;
	struct ksz_dlr_super_cfg super_cfg;
	u16 fault_cnt;
	struct ksz_dlr_active_node last_active[2];
	u16 participants_cnt;
	struct ksz_dlr_active_node active_super_addr;
	u8 active_super_prec;
	u32 cap;
	struct ksz_dlr_gateway_cfg gateway_cfg;
	u8 gateway_status;
	struct ksz_dlr_active_node active_gateway_addr;
	u8 active_gateway_prec;
} __packed;

union dlr_data {
	struct ksz_dlr_gateway_capable gateway;
	struct ksz_dlr_super_capable_2 super;
	struct ksz_dlr_non_super_capable_2 non_super;
	struct ksz_dlr_super_cfg super_cfg;
	struct ksz_dlr_gateway_cfg gateway_cfg;
	struct ksz_dlr_active_node active;
	u32 dword;
	u16 word;
	u8 byte;
} __packed;

#endif
