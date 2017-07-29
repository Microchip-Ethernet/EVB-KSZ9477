/**
 * Micrel switch common header
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2010-2015 Micrel, Inc.
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

#ifndef KSZ_SW_H
#define KSZ_SW_H


/* These definitions should be defined before this header file. */
#ifndef PRIO_QUEUES
#define PRIO_QUEUES			4
#endif

#ifndef KS_PRIO_IN_REG
#define KS_PRIO_IN_REG			4
#endif

#ifndef SWITCH_PORT_NUM
#define SWITCH_PORT_NUM			2
#endif

#ifndef SWITCH_COUNTER_NUM
#define SWITCH_COUNTER_NUM		0x20
#endif
#ifndef TOTAL_SWITCH_COUNTER_NUM
#define TOTAL_SWITCH_COUNTER_NUM	(SWITCH_COUNTER_NUM + 2)
#endif

#ifndef SW_D
#error "SW_D and other data bus parameters need to be defined."
#endif

#define TOTAL_PORT_NUM			(SWITCH_PORT_NUM + 1)

#ifdef CONFIG_1588_PTP
#include "ksz_ptp.h"
#endif
#ifdef CONFIG_MRP
#include "ksz_mrp.h"
#endif
#ifdef KSZ_DLR
#include "ksz_dlr.h"
#endif


#define KS_PRIO_M			SWITCH_802_1P_MAP_MASK
#define KS_PRIO_S			SWITCH_802_1P_MAP_SHIFT

#define LEARNED_MAC_TABLE_ENTRIES	1024
#define STATIC_MAC_TABLE_ENTRIES	8
#define SWITCH_MAC_TABLE_ENTRIES	16
#define MULTI_MAC_TABLE_ENTRIES		40

#define RX_TABLE_ENTRIES		128
#define TX_TABLE_ENTRIES		8

#define BLOCKED_RX_ENTRIES		8

struct ksz_frame_table {
	u32 crc;
	int cnt;
	int port;
	unsigned long expired;
};

struct ksz_rx_table {
	struct ksz_frame_table table[RX_TABLE_ENTRIES];
	int cnt;
};

struct ksz_tx_table {
	struct ksz_frame_table table[TX_TABLE_ENTRIES];
	int cnt;
};

/**
 * struct ksz_mac_table - Static MAC table data structure
 * @mac_addr:	MAC address to filter.
 * @vid:	VID value.
 * @fid:	FID value.
 * @ports:	Port membership.
 * @override:	Override setting.
 * @use_fid:	FID use setting.
 * @valid:	Valid setting indicating the entry is being used.
 */
struct ksz_mac_table {
	u8 mac_addr[ETH_ALEN];
	u16 vid;
	u8 fid;
	u8 ports;
	u8 override:1;
	u8 use_fid:1;
	u8 valid:1;
};

#define FWD_HOST_OVERRIDE		(1 << 0)
#define FWD_HOST			(1 << 1)
#define FWD_STP_DEV			(1 << 2)
#define FWD_MAIN_DEV			(1 << 3)
#define FWD_VLAN_DEV			(1 << 4)

struct ksz_alu_table {
	u8 owner;
	u8 forward;
	u8 valid:1;
};

#define VLAN_TABLE_ENTRIES		16

/**
 * struct ksz_vlan_table - VLAN table data structure
 * @vid:	VID value.
 * @fid:	FID value.
 * @member:	Port membership.
 * @valid:	Valid setting indicating the entry is being used.
 */
struct ksz_vlan_table {
	u16 vid;
	u8 fid;
	u8 member;
	u8 valid:1;
};

#define PRIO_802_1P_ENTRIES		8

#define DIFFSERV_ENTRIES		64

/**
 * struct ksz_port_mib - Port MIB data structure
 * @cnt_ptr:	Current pointer to MIB counter index.
 * @mib_start:	The starting counter index.  Some ports do not start at 0.
 * @counter:	64-bit MIB counter value.
 * @dropped:	Temporary buffer to remember last read packet dropped values.
 * @read_cnt:	Used to signal when to read the MIB counter.
 * @read_max:	Used to indicate how often to read the MIB counter.
 *
 * MIB counters needs to be read periodically so that counters do not get
 * overflowed and give incorrect values.  A right balance is needed to
 * satisfy this condition and not waste too much CPU time.
 */
struct ksz_port_mib {
	u8 cnt_ptr;
	u8 mib_start;
	u8 reserved[2];

	u64 counter[TOTAL_SWITCH_COUNTER_NUM];
	u32 dropped[2];
	u8 read_cnt[SWITCH_COUNTER_NUM];
	u8 read_max[SWITCH_COUNTER_NUM];
};

enum {
	STP_STATE_DISABLED = 0,
	STP_STATE_LISTENING,
	STP_STATE_LEARNING,
	STP_STATE_FORWARDING,
	STP_STATE_BLOCKED,
	STP_STATE_SIMPLE
};

/**
 * struct ksz_port_cfg - Port configuration data structure
 * @vid:	VID value.
 * @member:	Port membership.
 * @port_prio:	Port priority.
 * @rate_ctrl:	Priority rate control.
 * @rx_rate:	Receive priority rate.
 * @tx_rate:	Transmit priority rate.
 * @rate_limit: Priority rate limit value.
 * @stp_state:	Current Spanning Tree Protocol state.
 */
struct ksz_port_cfg {
	u16 vid;
	u8 member;
	u8 port_prio;
	u8 rate_ctrl[PRIO_QUEUES];
	u32 rx_rate[PRIO_QUEUES];
	u32 tx_rate[PRIO_QUEUES];
	u8 rate_limit;
	int stp_state;
};

/**
 * struct ksz_sw_info - KSZ8463 switch information data structure
 * @mac_table:	MAC table entries information.
 * @multi_net:	Network multicast addresses used.
 * @multi_sys:	System multicast addresses used.
 * @blocked_rx:	Blocked receive addresses.
 * @blocked_rx_cnt: Blocked receive addresses count.
 * @vlan_table:	VLAN table entries information.
 * @port_cfg:	Port configuration information.
 * @rx_table:	Receive frame information.
 * @tx_table:	Transmit frame information.
 * @diffserv:	DiffServ priority settings.  Possible values from 6-bit of ToS
 *		(bit7 ~ bit2) field.
 * @p_802_1p:	802.1P priority settings.  Possible values from 3-bit of 802.1p
 *		Tag priority field.
 * @br_addr:	Bridge address.  Used for STP.
 * @mac_addr:	Switch MAC address.
 * @broad_per:	Broadcast storm percentage.
 * @member:	Current port membership.  Used for STP.
 * @stp:	STP port membership.  Used for STP.
 * @stp_down:	STP port down membership.  Used for STP.
 * @phy_addr:	PHY address used by first port.
 */
struct ksz_sw_info {
	struct ksz_mac_table mac_table[MULTI_MAC_TABLE_ENTRIES];
	struct ksz_alu_table alu_table[MULTI_MAC_TABLE_ENTRIES];
	u32 mac_table_used;
	int multi_net;
	int multi_sys;
	u8 blocked_rx[BLOCKED_RX_ENTRIES][ETH_ALEN];
	int blocked_rx_cnt;
	struct ksz_vlan_table vlan_table[VLAN_TABLE_ENTRIES];
	u32 vlan_table_used;
	struct ksz_port_cfg port_cfg[TOTAL_PORT_NUM];
	struct ksz_rx_table rx_table;
	struct ksz_tx_table tx_table;
#ifdef KSZ_DLR
	struct ksz_dlr_info dlr;
#endif

	SW_D diffserv[DIFFSERV_ENTRIES / KS_PRIO_IN_REG];
	SW_D p_802_1p[PRIO_802_1P_ENTRIES / KS_PRIO_IN_REG];

	u8 br_addr[ETH_ALEN];
	u8 mac_addr[ETH_ALEN];

	u8 broad_per;
	u8 member;
	u8 stp;
	u8 stp_down;
	u8 fwd_ports;
	u8 phy_addr;
};

/**
 * struct ksz_port_state - Port state information data structure
 * @state:	Connection status of the port.
 * @link_down:	Indication the link has just gone down.
 *
 * It is pointless to read MIB counters when the port is disconnected.  The
 * @state provides the connection status so that MIB counters are read only
 * when the port is connected.  The @link_down indicates the port is just
 * disconnected so that all MIB counters are read one last time to update the
 * information.
 */
struct ksz_port_state {
	uint state;
	u8 link_down;
};

#define TX_RATE_UNIT			10000

/**
 * struct ksz_port_info - Port information data structure
 * @state:	Connection status of the port.
 * @tx_rate:	Transmit rate divided by 10000 to get Mbit.
 * @duplex:	Duplex mode.
 * @flow_ctrl:	Flow control.
 * @advertised:	Advertised auto-negotiation setting.  Used to determine link.
 * @partner:	Auto-negotiation partner setting.  Used to determine link.
 * @fiber:	Using fiber instead of copper.
 * @port_id:	Port index to access actual hardware register.
 * @status:	LinkMD status values.
 * @length:	LinkMD length values.
 * @mac_addr:	MAC address of the port.
 */
struct ksz_port_info {
	uint state;
	uint tx_rate;
	u8 duplex;
	u8 flow_ctrl;
	u8 advertised;
	u8 partner;
	u8 fiber;
	u8 port_id;
	u32 status[3];
	u32 length[3];
	u8 mac_addr[ETH_ALEN];
};

struct ksz_sw;
struct ksz_port;

struct ksz_sw_reg_ops {
	u8 (*r8)(struct ksz_sw *sw, unsigned reg);
	u16 (*r16)(struct ksz_sw *sw, unsigned reg);
	u32 (*r32)(struct ksz_sw *sw, unsigned reg);
	void (*w8)(struct ksz_sw *sw, unsigned reg, unsigned val);
	void (*w16)(struct ksz_sw *sw, unsigned reg, unsigned val);
	void (*w32)(struct ksz_sw *sw, unsigned reg, unsigned val);

	int (*get)(struct ksz_sw *sw, u32 reg, size_t count, char *buf);
	int (*set)(struct ksz_sw *sw, u32 reg, size_t count, char *buf);
};

struct ksz_sw_net_ops {
	void (*setup_special)(struct ksz_sw *sw, int *port_cnt,
		int *mib_port_cnt, int *dev_cnt);
	void (*setup_dev)(struct ksz_sw *sw, struct net_device *dev,
		char *dev_name, struct ksz_port *port, int i, int port_cnt,
		int mib_port_cnt);
	u8 (*get_state)(struct net_device *dev);
	void (*set_state)(struct net_device *dev, u8 state);
	struct ksz_port *(*get_priv_port)(struct net_device *dev);

	void (*start)(struct ksz_sw *sw, u8 *addr);
	int (*stop)(struct ksz_sw *sw, int complete);
	void (*open_dev)(struct ksz_sw *sw, struct net_device *dev, u8 *addr);
	void (*open_port)(struct ksz_sw *sw, struct net_device *dev,
		struct ksz_port *port, u8 *state);
	void (*close_port)(struct ksz_sw *sw, struct net_device *dev,
		struct ksz_port *port);
	void (*open)(struct ksz_sw *sw);
	void (*close)(struct ksz_sw *sw);

	void (*netdev_start_queue)(struct ksz_sw *sw, struct net_device *dev);
	void (*netdev_stop_queue)(struct ksz_sw *sw, struct net_device *dev);
	void (*netdev_wake_queue)(struct ksz_sw *sw, struct net_device *dev);
	void (*netdev_open_port)(struct ksz_sw *sw, struct net_device *dev);

	u8 (*set_mac_addr)(struct ksz_sw *sw, struct net_device *dev,
		u8 promiscuous, int port);

	int (*get_tx_len)(struct ksz_sw *sw, struct sk_buff *skb);
	void (*add_tail_tag)(struct ksz_sw *sw, struct sk_buff *skb, int ports);
	int (*get_tail_tag)(u8 *trailer, int *port);
	struct sk_buff *(*check_tx)(struct ksz_sw *sw, struct net_device *dev,
		struct sk_buff *skb, struct ksz_port *priv);
	struct net_device *(*rx_dev)(struct ksz_sw *sw, u8 *data, u32 *len,
		int *tag, int *port);
	int (*match_pkt)(struct ksz_sw *sw, struct net_device **dev,
		void **priv, int (*get_promiscuous)(void *ptr),
		int (*match_multi)(void *ptr, u8 *data),
		struct sk_buff *skb, u8 h_promiscuous);
	struct net_device *(*parent_rx)(struct ksz_sw *sw,
		struct net_device *dev, struct sk_buff *skb, int forward,
		struct net_device **parent_dev, struct sk_buff **parent_skb);
	int (*port_vlan_rx)(struct ksz_sw *sw, struct net_device *dev,
		struct net_device *parent_dev, struct sk_buff *skb,
		int forward, int tag, void *ptr,
		void (*rx_tstamp)(void *ptr, struct sk_buff *skb));
	int (*drop_icmp)(struct sk_buff *skb, int extra_skb);
	struct sk_buff *(*final_skb)(struct ksz_sw *sw, struct sk_buff *skb,
		struct net_device *dev, struct ksz_port *port);
	int (*drv_rx)(struct ksz_sw *sw, struct sk_buff *skb, int port);

#ifdef CONFIG_KSZ_STP
	u8 (*get_port_state)(struct net_device *dev,
		struct net_device **br_dev);

	void (*set_multi)(struct ksz_sw *sw, struct net_device *dev,
		struct ksz_port *priv);
	int (*stp_rx)(struct ksz_sw *sw, struct net_device *dev,
		struct sk_buff *skb, int port, int *forward);
	int (*blocked_rx)(struct ksz_sw *sw, u8 *data);
	void (*monitor_ports)(struct ksz_sw *sw);
#endif
};

struct ksz_sw_ops {
	void (*acquire)(struct ksz_sw *sw);
	void (*release)(struct ksz_sw *sw);

	int (*chk)(struct ksz_sw *sw, u32 addr, SW_D bits);
	void (*cfg)(struct ksz_sw *sw, u32 addr, SW_D bits, int set);

	int (*port_get_link_speed)(struct ksz_port *port);
	void (*port_set_link_speed)(struct ksz_port *port);
	void (*port_force_link_speed)(struct ksz_port *port);

	int (*port_r_cnt)(struct ksz_sw *sw, int port);
	void (*get_mib_counters)(struct ksz_sw *sw, int first, int cnt,
		u64 *counter);

	ssize_t (*sysfs_read)(struct ksz_sw *sw, int proc_num,
		struct ksz_port *port, ssize_t len, char *buf);
	ssize_t (*sysfs_read_hw)(struct ksz_sw *sw, int proc_num, ssize_t len,
		char *buf);
	int (*sysfs_write)(struct ksz_sw *sw, int proc_num,
		struct ksz_port *port, int num, const char *buf);
	ssize_t (*sysfs_port_read)(struct ksz_sw *sw, int proc_num, int port,
		ssize_t len, char *buf);
	ssize_t (*sysfs_port_read_hw)(struct ksz_sw *sw, int proc_num,
		int port, ssize_t len, char *buf);
	int (*sysfs_port_write)(struct ksz_sw *sw, int proc_num, int port,
		int num, const char *buf);
	ssize_t (*sysfs_mac_read)(struct ksz_sw *sw, int proc_num, int index,
		ssize_t len, char *buf);
	int (*sysfs_mac_write)(struct ksz_sw *sw, int proc_num, int index,
		int num, const char *buf);
	ssize_t (*sysfs_vlan_read)(struct ksz_sw *sw, int proc_num, int index,
		ssize_t len, char *buf);
	int (*sysfs_vlan_write)(struct ksz_sw *sw, int proc_num, int index,
		int num);

	void (*cfg_mac)(struct ksz_sw *sw, u8 index, u8 *dest, u32 ports,
		int override, int use_fid, u16 fid);
	void (*cfg_vlan)(struct ksz_sw *sw, u8 index, u16 vid, u16 fid,
		u32 ports);
	u8 (*alloc_mac)(struct ksz_sw *sw);
	void (*free_mac)(struct ksz_sw *sw, u8 index);
	u8 (*alloc_vlan)(struct ksz_sw *sw);
	void (*free_vlan)(struct ksz_sw *sw, u8 index);

	int (*get_id)(struct ksz_sw *sw, u8 *id1, u8 *id2);
	void (*cfg_tail_tag)(struct ksz_sw *sw, int enable);
	void (*cfg_each_port)(struct ksz_sw *sw, int p, int cpu);
	int (*port_to_phy_addr)(struct ksz_sw *sw, int p);
	void (*set_port_addr)(struct ksz_sw *sw, int p, u8 *addr);

	void (*cfg_src_filter)(struct ksz_sw *sw, int set);
	void (*flush_table)(struct ksz_sw *sw, int port);
};

struct ksz_sw_cached_regs {
	u16 ptp_clk_ctrl;
};

/* Switch features and bug fixes. */
#define STP_SUPPORT			(1 << 0)
#define VLAN_PORT			(1 << 1)
#define VLAN_PORT_REMOVE_TAG		(1 << 2)
#define VLAN_PORT_TAGGING		(1 << 3)
#define VLAN_PORT_START			200
#define MRP_SUPPORT			(1 << 4)

#define DSA_SUPPORT			(1 << 28)
#define DIFF_MAC_ADDR			(1 << 30)
#ifdef CONFIG_1588_PTP
#define PTP_HW				(1 << 31)
#endif

/* Software overrides. */
#define PAUSE_FLOW_CTRL			(1 << 0)
#define FAST_AGING			(1 << 1)

#define TAIL_PRP_0			(1 << 24)
#define TAIL_PRP_1			(1 << 25)

#define TAG_REMOVE			(1 << 30)
#define TAIL_TAGGING			(1 << 31)

/**
 * struct ksz_sw - Virtual switch data structure
 * @dev:		Pointer to hardware device.
 * @phydev:		Pointer to PHY device interface.
 * @interface:		The R/G/MII interface used.
 * @msg_enable:		The message flags controlling driver output.
 * @hwlock:		Pointer to hardware lock.
 * @reglock:		Pointer to register lock.
 * @lock		Software lock to switch structure.
 * @locked:		locked status.
 * @info:		Pointer to switch information structure.
 * @port_info:		Port information.
 * @netdev:		Pointer to OS dependent network devices.
 * @phy:		Pointer to OS dependent PHY devices.
 * @dev_offset:		Indication of a switch associated network device.
 * @phy_offset:		Indication of a port associated PHY device.
 * @port_state:		Port state information.
 * @port_mib:		Port MIB information.
 * @mib_cnt:		Number of MIB counters this switch has.
 * @mib_port_cnt:	Number of ports with MIB counters.
 * @port_cnt:		Number of ports to support.
 * @monitor_timer_info:	Timer information for monitoring ports.
 * @counter:		Pointer to OS dependent MIB counter information.
 * @link_read:		Workqueue for link monitoring.
 * @stp_monitor:	Workqueue for STP monitoring.
 * @ops:		Switch function access.
 * @reg:		Switch register access.
 * @net_ops:		Network related switch function access.
 * @HOST_PORT:		A predefined value indicating the host port.
 * @HOST_MASK:		A predefined value indicating the host port mask.
 * @PORT_MASK:		A predefined value indicating the port mask.
 * @rx_ports:		Bitmap of ports with receive enabled.
 * @tx_ports:		Bitmap of ports with transmit enabled.
 * @dev_count:		Number of network devices this switch supports.
 * @id:			Hardware ID.  Used for display only.
 * @vlan_id		Used for the VLAN port forwarding feature.
 * @vid:		Used for the VLAN port forwarding feature.
 * @features:		Switch features to enable.
 * @overrides:		Switch features to override.
 * @multi_dev:		Used to specify multiple devices mode.
 * @stp:		Used to enable STP.
 * @fast_aging:		Used to enable fast aging.
 */
struct ksz_sw {
	void *dev;
	void *phydev;
	phy_interface_t interface;
	u32 msg_enable;
	wait_queue_head_t queue;
	struct mutex *hwlock;
	struct mutex *reglock;
	struct mutex lock;
	int intr_using;

	struct ksz_sw_info *info;
	struct ksz_port_info port_info[SWITCH_PORT_NUM];
	struct net_device *main_dev;
	struct net_device *netdev[TOTAL_PORT_NUM];
	struct phy_device *phy[TOTAL_PORT_NUM + 1];
	int dev_offset;
	int phy_offset;
	struct ksz_port_state port_state[TOTAL_PORT_NUM];
	struct ksz_port_mib port_mib[TOTAL_PORT_NUM];
	int mib_cnt;
	int mib_port_cnt;
	int port_cnt;
	struct ksz_timer_info *monitor_timer_info;
	struct ksz_counter_info *counter;
	struct delayed_work *link_read;
	struct delayed_work *stp_monitor;

	const struct ksz_sw_ops *ops;
	const struct ksz_sw_reg_ops *reg;
	struct ksz_sw_net_ops *net_ops;

	int HOST_PORT;
	u16 HOST_MASK;
	u16 PORT_MASK;
	u16 rx_ports;
	u16 tx_ports;
	u8 tx_pad[60];
	int tx_start;
	struct ksz_sw_cached_regs cached;

	int dev_count;
	int id;
	u32 vlan_id;
	u16 vid;

	uint features;
	uint overrides;

	int multi_dev;
	int stp;
	int fast_aging;

#ifdef CONFIG_MRP
	struct mrp_info mrp;
#endif

#ifdef CONFIG_1588_PTP
	/* PTP structure size can be variable. */
	struct ptp_info ptp_hw;
#endif
};

struct ksz_sw_sysfs {
	struct ksz_dev_attr *ksz_port_attrs[TOTAL_PORT_NUM];
	struct attribute **port_attrs[TOTAL_PORT_NUM];
	struct ksz_dev_attr *ksz_mac_attrs[SWITCH_MAC_TABLE_ENTRIES];
	struct attribute **mac_attrs[SWITCH_MAC_TABLE_ENTRIES];
	struct ksz_dev_attr *ksz_vlan_attrs[VLAN_TABLE_ENTRIES];
	struct attribute **vlan_attrs[VLAN_TABLE_ENTRIES];
};

/**
 * struct ksz_port - Virtual port data structure
 * @first_port:		Index of first port this port supports.
 * @mib_port_cnt:	Number of ports with MIB counters.
 * @port_cnt:		Number of ports this port supports.
 * @flow_ctrl:		Flow control setting.  PHY_NO_FLOW_CTRL for no flow
 *			control, and PHY_FLOW_CTRL for flow control.
 *			PHY_TX_ONLY and PHY_RX_ONLY are not supported for 100
 *			Mbit PHY.
 * @duplex:		Duplex mode setting.  1 for half duplex, 2 for full
 *			duplex, and 0 for auto, which normally results in full
 *			duplex.
 * @speed:		Speed setting.  10 for 10 Mbit, 100 for 100 Mbit, and
 *			0 for auto, which normally results in 100 Mbit.
 * @force_link:		Force link setting.  0 for auto-negotiation, and 1 for
 *			force.
 * @linked:		Pointer to port information linked to this port.
 * @sw:			Pointer to virtual switch structure.
 */
struct ksz_port {
	int first_port;
	int mib_port_cnt;
	int port_cnt;

	u8 flow_ctrl;
	u8 duplex;
	u8 speed;
	u8 force_link;

	struct ksz_port_info *linked;

	struct ksz_sw *sw;
	struct work_struct link_update;
};

struct lan_attributes {
	int info;
	int duplex;
	int speed;
	int force;
	int flow_ctrl;
	int features;
	int overrides;
	int mib;
	int reg;
	int vid;
	int dynamic_table;
	int static_table;
	int vlan_table;
	int aging;
	int fast_aging;
	int link_aging;
	int bcast_per;
	int mcast_storm;
	int diffserv_map;
	int p_802_1p_map;
	int vlan;
	int null_vid;
	int macaddr;
	int mirror_mode;
	int tail_tag;
	int igmp_snoop;
	int ipv6_mld_snoop;
	int ipv6_mld_option;
	int aggr_backoff;
	int no_exc_drop;
	int buf_reserve;
	int huge_packet;
	int legal_packet;
	int length_check;
	int back_pressure;
	int sw_flow_ctrl;
	int sw_half_duplex;
	int sw_10_mbit;
	int rx_flow_ctrl;
	int tx_flow_ctrl;
	int fair_flow_ctrl;
	int vlan_bound;
	int fw_unk_dest;
	int ins_tag_0_1;
	int ins_tag_0_2;
	int ins_tag_1_0;
	int ins_tag_1_2;
	int ins_tag_2_0;
	int ins_tag_2_1;
	int pass_all;
	int pass_pause;
	int phy_addr;
	int ports;
	int dev_start;
	int vlan_start;
	int stp;
};

struct sw_attributes {
	int mib;
	int vid;
	int member;
	int bcast_storm;
	int diffserv;
	int p_802_1p;
	int port_based;
	int non_vid;
	int ingress;
	int ins_tag;
	int rmv_tag;
	int double_tag;
	int drop_tagged;
	int replace_prio;
	int rx;
	int tx;
	int learn;
	int prio_queue;
	int tx_p0_ctrl;
	int tx_p1_ctrl;
	int tx_p2_ctrl;
	int tx_p3_ctrl;
	int tx_p0_ratio;
	int tx_p1_ratio;
	int tx_p2_ratio;
	int tx_p3_ratio;
	int prio_rate;
	int rx_limit;
	int cnt_ifg;
	int cnt_pre;
	int rx_p0_rate;
	int rx_p1_rate;
	int rx_p2_rate;
	int rx_p3_rate;
	int tx_p0_rate;
	int tx_p1_rate;
	int tx_p2_rate;
	int tx_p3_rate;
	int mirror_port;
	int mirror_rx;
	int mirror_tx;
	int back_pressure;
	int force_flow_ctrl;
	int fw_unk_dest;
	int fw_inv_vid;

	int duplex;
	int speed;
	int linkmd;
	int macaddr;
	int src_filter_0;
	int src_filter_1;
};

struct static_mac_attributes {
	int fid;
	int use_fid;
	int override;
	int valid;
	int ports;
	int addr;
};

struct vlan_attributes {
	int valid;
	int member;
	int fid;
	int vid;
};

static int alloc_dev_attr(struct attribute **attrs, size_t attr_size, int item,
	struct ksz_dev_attr **ksz_attrs, struct attribute ***item_attrs,
	char *item_name, struct ksz_dev_attr **attrs_ptr)
{
	struct attribute **attr_ptr;
	struct device_attribute *dev_attr;
	struct ksz_dev_attr *new_attr;

	*item_attrs = kmalloc(attr_size * sizeof(void *), GFP_KERNEL);
	if (!*item_attrs)
		return -ENOMEM;

	attr_size--;
	attr_size *= sizeof(struct ksz_dev_attr);
	*ksz_attrs = *attrs_ptr;
	*attrs_ptr += attr_size / sizeof(struct ksz_dev_attr);

	new_attr = *ksz_attrs;
	attr_ptr = *item_attrs;
	while (*attrs != NULL) {
		if (item_name && !strcmp((*attrs)->name, item_name))
			break;
		dev_attr = container_of(*attrs, struct device_attribute, attr);
		memcpy(new_attr, dev_attr, sizeof(struct device_attribute));
		strncpy(new_attr->dev_name, (*attrs)->name, DEV_NAME_SIZE);
		if (10 <= item && item <= 15)
			new_attr->dev_name[0] = item - 10 + 'a';
		else
			new_attr->dev_name[0] = item + '0';
		new_attr->dev_attr.attr.name = new_attr->dev_name;
		*attr_ptr = &new_attr->dev_attr.attr;
		new_attr++;
		attr_ptr++;
		attrs++;
	}
	*attr_ptr = NULL;
	return 0;
}

#endif
