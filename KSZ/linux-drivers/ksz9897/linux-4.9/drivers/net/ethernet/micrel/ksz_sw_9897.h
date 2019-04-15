/**
 * Microchip KSZ9897 switch common header
 *
 * Copyright (c) 2015-2019 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2013-2015 Micrel, Inc.
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

#ifndef KSZ_SW_9897_H
#define KSZ_SW_9897_H


/* These definitions should be defined before this header file. */
#ifndef PRIO_QUEUES
#define PRIO_QUEUES			4
#endif
#define PRIO_QUEUES_M			(PRIO_QUEUES - 1)

#ifndef KS_PRIO_IN_REG
#define KS_PRIO_IN_REG			2
#endif

#ifndef TOTAL_PORT_NUM
#define TOTAL_PORT_NUM			7
#endif

#ifndef SWITCH_COUNTER_NUM
#define SWITCH_COUNTER_NUM		0x20
#endif

#ifndef SW_D
#error "SW_D and other data bus parameters need to be defined."
#endif

/* Host port can be any one of them. */
#define SWITCH_PORT_NUM			(TOTAL_PORT_NUM)


struct sw_dev_info {
	void *sw;
	unsigned int minor;
	u8 *write_buf;
	u8 *read_buf;
	size_t read_max;
	size_t read_len;
	size_t write_len;
	struct semaphore sem;
	struct mutex lock;
	wait_queue_head_t wait_msg;
	struct sw_dev_info *next;
};


struct ksz_vlan_table;

#define NUM_OF_VID			4094
#define NUM_OF_MSTI			8

#include "ksz_sw_api.h"
#ifdef CONFIG_KSZ_MSTP
#include "ksz_mstp.h"
#elif defined(CONFIG_KSZ_STP)
#include "ksz_stp.h"
#endif
#ifdef CONFIG_KSZ_IBA
#include "ksz_iba.h"
#endif
#ifdef CONFIG_1588_PTP
#include "ksz_ptp_9897.h"
#endif
#ifdef CONFIG_KSZ_MRP
#include "ksz_mrp.h"
#endif
#ifdef CONFIG_KSZ_DLR
#include "ksz_dlr.h"
#endif
#ifdef CONFIG_KSZ_HSR
#include "ksz_hsr.h"
#endif


#define LEARNED_MAC_TABLE_ENTRIES	1024
#define STATIC_MAC_TABLE_ENTRIES	16
#define RESERVED_MCAST_TABLE_ENTRIES	0x30
#define ACTUAL_MCAST_TABLE_ENTRIES	8
#define SWITCH_MAC_TABLE_ENTRIES	16
#define MULTI_MAC_TABLE_ENTRIES		80

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
	u8 addr[ETH_ALEN];
	u32 ports;
	u16 fid;
	u8 mstp;
	u8 prio;
	u8 src:1;
	u8 dst:1;
	u8 override:1;
	u8 use_fid:1;
	u8 valid:1;
	u8 dirty:1;
};

#define FWD_HOST_OVERRIDE		BIT(0)
#define FWD_HOST			BIT(1)
#define FWD_STP_DEV			BIT(2)
#define FWD_MAIN_DEV			BIT(3)
#define FWD_VLAN_DEV			BIT(4)
#define FWD_MCAST			BIT(5)
#define FWD_UCAST			BIT(6)
#define FWD_KNOWN			BIT(7)

struct ksz_alu_table {
	u16 index;
	u16 owner;
	u8 forward;
	u8 type;
	u8 valid:1;
};

#define VLAN_TABLE_ENTRIES		4096
#define VID_IN_DATA			32
#define FID_ENTRIES			128
#define FID_IN_DATA			32

/**
 * struct ksz_vlan_table - VLAN table data structure
 * @vid:	VID value.
 * @fid:	FID value.
 * @ports:	Port membership.
 * @untag:	Untag membership.
 * @mstp:	MSTP number.
 * @prio:	Priority
 * @fo:		Forward option.
 * @valid:	Valid setting indicating the entry is being used.
 */
struct ksz_vlan_table {
	u16 vid;
	u16 fid;
	u32 ports;
	u32 untag;
	u8 mstp;
	u8 prio;
	u8 option:1;
	u8 valid:1;
	u8 dirty:1;
};

#ifdef CONFIG_KSZ_HSR
/**
 * struct ksz_hsr_table - HSR table data structure
 * @dst:	Destination MAC address.
 * @src:	Source MAC address.
 * @age_cnt:	Age count.
 * @path_id:	Path ID.
 * @start_seq:	Starting sequence number.
 * @exp_seq:	Expected sequence number.
 * @seq_cnt:	Out of sequence number count.
 * @valid:	Valid setting indicating the entry is being used.
 * @dirty:	Flag indicating structure has been changed.
 */
struct ksz_hsr_table {
	u8 dst_mac[ETH_ALEN];
	u8 src_mac[ETH_ALEN];
	u8 age_cnt;
	u8 path_id;
	u16 start_seq[2];
	u16 exp_seq[2];
	u16 seq_cnt[2];
	u8 valid:1;
	u8 dirty:1;
};
#endif

#define PRIO_802_1P_ENTRIES		8

#define DIFFSERV_ENTRIES		64

#define ACL_TABLE_ENTRIES		16

struct ksz_acl_table {
	u16 first_rule;
	u16 ruleset;
	u8 mac[ETH_ALEN];
	u16 eth_type;
	u8 protocol;
	u8 ip4_addr[4];
	u8 ip4_mask[4];
	u32 seqnum;
	u16 max_port;
	u16 min_port;
	u8 prio;
	u8 vlan_prio;
	u16 ports;
	u16 cnt;
	u8 tcp_flag_mask;
	u8 tcp_flag;
#if 0
	u8 ip6_addr[16];
	u8 ip6_mask[16];
#endif
	u32 mode:2;
	u32 enable:2;
	u32 src:1;
	u32 equal:1;
	u32 port_mode:2;
	u32 tcp_flag_enable:1;
	u32 msec:1;
	u32 intr_mode:1;
	u32 prio_mode:2;
	u32 vlan_prio_replace:1;
	u32 map_mode:2;
	u32 changed:1;
	u32 action_changed:1;
	u32 ruleset_changed:1;
	u32 action_selected:1;

	u8 data[ACL_TABLE_LEN];
};

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
	u8 interval;
	u8 reserved[1];

	u64 counter[TOTAL_SWITCH_COUNTER_NUM];
	struct {
		unsigned long last;
		u64 last_cnt;
		u32 peak;
		unsigned long check;
		u64 prev_cnt;
		bool no_change;
	} rate[2];
	unsigned long last_drop;
	u64 drop;
	u64 first_drop;
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
 * @vid_member:	VLAN membership.
 * @index:	Net device pointer.
 * @stp_state:	Current Spanning Tree Protocol state.
 */
struct ksz_port_cfg {
	u16 vid;
	u16 member;
	u8 rate_ctrl[PRIO_QUEUES];
	u32 rx_packet[RX_PRIO_QUEUES];
	u32 rx_rate[RX_PRIO_QUEUES];
	u32 tx_packet[PRIO_QUEUES];
	u32 tx_rate[PRIO_QUEUES];
	u32 color_map[DIFFSERV_ENTRIES / 16];
	u32 tc_map[PRIO_802_1P_ENTRIES / 8];
	u32 untagged[VLAN_TABLE_ENTRIES / VID_IN_DATA];
	u8 p_index;
	u8 q_index;
	u8 port_prio;
	u8 rate_limit;
	int packet_based;
	u16 intr_mask;
	u16 vid_member;
	int index;
	int stp_state[NUM_OF_MSTI];

	struct ksz_acl_table acl_info[ACL_TABLE_ENTRIES];
	u16 acl_index;
	u16 acl_act_index;
	u16 acl_rule_index;

	u16 mmd_id;
	u16 mmd_reg;

	u32 enabled:1;
	u32 ptp_enabled:1;
	u32 asCapable:1;
	u32 asCapable_set:1;
	u32 avb_a:1;
	u32 avb_b:1;
	u32 restricted:1;
	u32 freeze:1;

	u16 phy_ctrl;
	u16 phy_adv;
	u16 phy_adv_g;
	u8 phy_intr;

	u8 mstp;

	u32 setup_time;
};

/**
 * struct ksz_sw_info - KSZ9897 switch information data structure
 * @mac_table:	MAC table entries information.
 * @alu_table:	ALU table entries information.
 * @multi_net:	Network multicast addresses used.
 * @multi_sys:	System multicast addresses used.
 * @port_cfg:	Port configuration information.
 * @rstp:	RSTP information.
 * @iba:	IBA information.
 * @dlr:	DLR information.
 * @hsr:	HSR information.
 * @hsr_entry:	HSR table entry information.
 * @mac_entry:	MAC table entry information.
 * @vlan_entry:	VLAN table entry information.
 * @diffserv:	DiffServ priority settings.  Possible values from 6-bit of ToS
 *		(bit7 ~ bit2) field.
 * @p_802_1p:	802.1P priority settings.  Possible values from 3-bit of 802.1p
 *		Tag priority field.
 * @br_addr:	Bridge address.  Used for STP.
 * @mac_addr:	Switch MAC address.
 * @broad_per:	Broadcast storm percentage.
 * @member:	Current port membership.  Used for STP.
 * @phy_addr:	PHY address used by first port.
 */
struct ksz_sw_info {
	struct ksz_mac_table mac_table[MULTI_MAC_TABLE_ENTRIES];
	struct ksz_alu_table alu_table[MULTI_MAC_TABLE_ENTRIES];
	int forward;
	int multi_net;
	int multi_sys;
	struct ksz_port_cfg port_cfg[TOTAL_PORT_NUM];
#ifdef CONFIG_KSZ_STP
	struct ksz_stp_info rstp;
#endif
#ifdef CONFIG_KSZ_IBA
	struct ksz_iba_info iba;
#endif
#ifdef CONFIG_KSZ_DLR
	struct ksz_dlr_info dlr;
#endif
#ifdef CONFIG_KSZ_HSR
	struct ksz_hsr_info hsr;
	struct ksz_hsr_table hsr_entry;
#endif
	struct ksz_mac_table mac_entry;
	struct ksz_vlan_table vlan_entry;

	SW_D diffserv[DIFFSERV_ENTRIES / KS_PRIO_IN_REG];
	SW_D p_802_1p[PRIO_802_1P_ENTRIES / KS_PRIO_IN_REG];

	u8 br_addr[ETH_ALEN];
	u8 mac_addr[ETH_ALEN];

	u8 vid2fid[VLAN_TABLE_ENTRIES];
	u8 fid2mstid[FID_ENTRIES];
	u32 vid[VLAN_TABLE_ENTRIES / VID_IN_DATA];
	u32 fid[FID_ENTRIES / FID_IN_DATA];
	u16 fid_cnt;

	u8 broad_per;
	u8 member[NUM_OF_MSTI];
	u8 phy_addr;
	u8 fid_updated;
};

struct ksz_sw;
struct ksz_port;

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
	uint tx_rate;
	u8 link_down;
};

enum {
	INTF_RGMII,
	INTF_SGMII,
	INTF_TX_PHY,
	INTF_T1_PHY,
};

#define TX_RATE_UNIT			10000

/**
 * struct ksz_port_info - Port information data structure
 * @interface:	PHY interface.
 * @state:	Connection status of the port.
 * @tx_rate:	Transmit rate divided by 10000 to get Mbit.
 * @duplex:	Duplex mode.
 * @flow_ctrl:	Flow control.
 * @link:	Link status.  Used to determine link.
 * @advertised:	Advertised auto-negotiation setting.  Used to determine link.
 * @partner:	Auto-negotiation partner setting.  Used to determine link.
 * @status:	LinkMD status values.
 * @length:	LinkMD length values.
 * @sqi:	Signal Quality Indicator.
 * @mac_addr:	MAC address of the port.
 * @phy_id:	PHY id used by the port.
 */
struct ksz_port_info {
	phy_interface_t interface;
	uint state;
	uint tx_rate;
	u8 duplex;
	u8 flow_ctrl;
	u8 link_down;
	u16 link;
	u32 advertised;
	u32 partner;
	u32 status[5];
	u32 length[5];
	u16 sqi;
	u8 mac_addr[ETH_ALEN];
	u8 own_flow_ctrl;
	u8 own_duplex;
	u16 own_speed;
	u8 phy_id;
	u32 report:1;
	u32 phy:1;
	u32 fiber:1;

	u8 phy_p;
	u8 log_p;
	u16 phy_m;
	u16 log_m;
	u8 intf;

	int (*get_link_speed)(struct ksz_sw *sw, uint p, bool force_link);
	void (*set_link_speed)(struct ksz_sw *sw, uint p, int speed,
			       int duplex, int flow_ctrl);
	void (*force_link_speed)(struct ksz_sw *sw, uint p, int speed,
				 int duplex, int flow_ctrl);
};

struct ksz_sw_reg_ops {
	void (*lock)(struct ksz_sw *sw);
	void (*unlock)(struct ksz_sw *sw);

	u8 (*r8)(struct ksz_sw *sw, unsigned reg);
	u16 (*r16)(struct ksz_sw *sw, unsigned reg);
	u32 (*r24)(struct ksz_sw *sw, unsigned reg);
	u32 (*r32)(struct ksz_sw *sw, unsigned reg);
	void (*w8)(struct ksz_sw *sw, unsigned reg, unsigned val);
	void (*w16)(struct ksz_sw *sw, unsigned reg, unsigned val);
	void (*w24)(struct ksz_sw *sw, unsigned reg, unsigned val);
	void (*w32)(struct ksz_sw *sw, unsigned reg, unsigned val);

	void (*r)(struct ksz_sw *sw, unsigned reg, void *buf, size_t cnt);
	void (*w)(struct ksz_sw *sw, unsigned reg, void *buf, size_t cnt);

	int (*get)(struct ksz_sw *sw, u32 reg, size_t count, char *buf);
	int (*set)(struct ksz_sw *sw, u32 reg, size_t count, char *buf);

	int (*r_dyn_mac_hw)(struct ksz_sw *sw, u16 addr, u8 *src_addr,
		u16 src_fid, struct ksz_mac_table *mac, u16 *entry);
	int (*w_dyn_mac_hw)(struct ksz_sw *sw, u16 addr, u8 *src_addr,
		u16 src_fid, struct ksz_mac_table *mac);
	int (*start_dyn_mac_hw)(struct ksz_sw *sw);
	int (*g_dyn_mac_hw)(struct ksz_sw *sw, struct ksz_mac_table *mac);
	u32 (*stop_dyn_mac_hw)(struct ksz_sw *sw);
	int (*r_sta_mac_hw)(struct ksz_sw *sw, u32 ctrl[], int num,
		struct ksz_mac_table *mac);
	int (*w_sta_mac_hw)(struct ksz_sw *sw, u32 ctrl[], int num,
		struct ksz_mac_table *mac);
	int (*r_vlan_hw)(struct ksz_sw *sw, u32 data[], int num);
	int (*w_vlan_hw)(struct ksz_sw *sw, u32 data[], int num);
	int (*r_mib_cnt_hw)(struct ksz_sw *sw, uint port, u32 addr[], int num,
			    u32 data[]);
	int (*r_acl_hw)(struct ksz_sw *sw, uint port, u16 addr, u8 data[]);
	int (*w_acl_hw)(struct ksz_sw *sw, uint port, u16 addr, u8 data[]);

#ifdef CONFIG_KSZ_HSR
	int (*r_hsr_hw)(struct ksz_sw *sw, u16 addr,
		struct ksz_hsr_table *hsr);
	int (*w_hsr_hw)(struct ksz_sw *sw, u16 addr,
		struct ksz_hsr_table *hsr);
	int (*start_hsr_hw)(struct ksz_sw *sw);
	int (*g_hsr_hw)(struct ksz_sw *sw, struct ksz_hsr_table *hsr);
	u32 (*stop_hsr_hw)(struct ksz_sw *sw);
#endif
};

struct ksz_sw_net_ops {
	void (*setup_special)(struct ksz_sw *sw, int *port_cnt,
		int *mib_port_cnt, int *dev_cnt);
	int (*setup_dev)(struct ksz_sw *sw, struct net_device *dev,
		char *dev_name, struct ksz_port *port, int i, uint port_cnt,
		uint mib_port_cnt);
	void (*leave_dev)(struct ksz_sw *sw);
	u8 (*get_state)(struct net_device *dev);
	void (*set_state)(struct net_device *dev, u8 state);
	struct ksz_port *(*get_priv_port)(struct net_device *dev);
	int (*get_ready)(struct net_device *dev);

	void (*start)(struct ksz_sw *sw, u8 *addr);
	int (*stop)(struct ksz_sw *sw, int complete);
	int (*open_dev)(struct ksz_sw *sw, struct net_device *dev, u8 *addr);
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
		u8 promiscuous, uint port);

	int (*get_mtu)(struct ksz_sw *sw);
	int (*get_tx_len)(struct ksz_sw *sw, struct sk_buff *skb, uint port,
		int *header);
	void (*add_tail_tag)(struct ksz_sw *sw, struct sk_buff *skb, uint dst);
	int (*get_tail_tag)(u8 *trailer, int *port);
	void (*add_vid)(struct ksz_sw *sw, u16 vid);
	void (*kill_vid)(struct ksz_sw *sw, u16 vid);
	struct sk_buff *(*check_tx)(struct ksz_sw *sw, struct net_device *dev,
		struct sk_buff *skb, struct ksz_port *priv);
	struct net_device *(*rx_dev)(struct ksz_sw *sw, u8 *data, u32 *len,
		int *tag, int *port);
	int (*match_pkt)(struct ksz_sw *sw, struct net_device **dev,
		void **priv, int (*get_promiscuous)(void *ptr),
		int (*get_multi)(void *ptr), struct sk_buff *skb,
		u8 h_promiscuous);
	struct net_device *(*parent_rx)(struct ksz_sw *sw,
		struct net_device *dev, struct sk_buff *skb, int *forward,
		struct net_device **parent_dev, struct sk_buff **parent_skb);
	int (*port_vlan_rx)(struct ksz_sw *sw, struct net_device *dev,
		struct net_device *parent_dev, struct sk_buff *skb,
		int forward, int tag, void *ptr,
		void (*rx_tstamp)(void *ptr, struct sk_buff *skb));
	int (*drop_icmp)(struct sk_buff *skb, int extra_skb);
	struct sk_buff *(*final_skb)(struct ksz_sw *sw, struct sk_buff *skb,
		struct net_device *dev, struct ksz_port *port);
	int (*drv_rx)(struct ksz_sw *sw, struct sk_buff *skb, uint port);
	void (*set_multi)(struct ksz_sw *sw, struct net_device *dev,
		struct ksz_port *priv);
};

struct ksz_sw_ops {
	void (*init)(struct ksz_sw *sw);
	void (*exit)(struct ksz_sw *sw);
	int (*dev_req)(struct ksz_sw *sw, int start, char *arg,
		struct sw_dev_info *info);

	uint (*get_phy_port)(struct ksz_sw *sw, uint n);
	uint (*get_log_port)(struct ksz_sw *sw, uint p);

	void (*chk_regs)(struct ksz_sw *sw, u32 addr, u8 *val, size_t txl);

	void (*acquire)(struct ksz_sw *sw);
	void (*release)(struct ksz_sw *sw);

	int (*chk)(struct ksz_sw *sw, u32 addr, SW_D bits);
	void (*cfg)(struct ksz_sw *sw, u32 addr, SW_D bits, bool set);

	int (*port_get_link_speed)(struct ksz_port *port);
	void (*port_set_link_speed)(struct ksz_port *port);
	void (*port_force_link_speed)(struct ksz_port *port);

	int (*port_r_cnt)(struct ksz_sw *sw, uint port);
	void (*get_mib_counters)(struct ksz_sw *sw, int first, int cnt,
		u64 *counter);

	ssize_t (*sysfs_read)(struct ksz_sw *sw, int proc_num,
		struct ksz_port *port, ssize_t len, char *buf);
	ssize_t (*sysfs_read_hw)(struct ksz_sw *sw, int proc_num, ssize_t len,
		char *buf);
	int (*sysfs_write)(struct ksz_sw *sw, int proc_num,
		struct ksz_port *port, int num, const char *buf);
	ssize_t (*sysfs_port_read)(struct ksz_sw *sw, int proc_num, uint port,
		ssize_t len, char *buf);
	ssize_t (*sysfs_port_read_hw)(struct ksz_sw *sw, int proc_num,
		uint port, ssize_t len, char *buf);
	int (*sysfs_port_write)(struct ksz_sw *sw, int proc_num, uint port,
		int num, const char *buf);
	ssize_t (*sysfs_mac_read)(struct ksz_sw *sw, int proc_num, ssize_t len,
		char *buf);
	int (*sysfs_mac_write)(struct ksz_sw *sw, int proc_num, int num,
		const char *buf);
	ssize_t (*sysfs_vlan_read)(struct ksz_sw *sw, int proc_num,
		ssize_t len, char *buf);
	int (*sysfs_vlan_write)(struct ksz_sw *sw, int proc_num, int num);

#ifdef CONFIG_KSZ_STP
	ssize_t (*sysfs_stp_read)(struct ksz_sw *sw, int proc_num, ssize_t len,
		char *buf);
	int (*sysfs_stp_write)(struct ksz_sw *sw, int proc_num, int num,
		const char *buf);
	ssize_t (*sysfs_stp_port_read)(struct ksz_sw *sw, int proc_num,
		uint port, ssize_t len, char *buf);
	int (*sysfs_stp_port_write)(struct ksz_sw *sw, int proc_num, uint port,
		int num, const char *buf);
#endif

#ifdef CONFIG_KSZ_MRP
	ssize_t (*sysfs_mrp_read)(struct ksz_sw *sw, int proc_num, ssize_t len,
		char *buf);
	int (*sysfs_mrp_write)(struct ksz_sw *sw, int proc_num, int num,
		const char *buf);
	ssize_t (*sysfs_mrp_port_read)(struct ksz_sw *sw, int proc_num,
		uint port, ssize_t len, char *buf);
	int (*sysfs_mrp_port_write)(struct ksz_sw *sw, int proc_num, uint port,
		int num, const char *buf);
#endif

#ifdef CONFIG_KSZ_HSR
	ssize_t (*sysfs_hsr_read)(struct ksz_sw *sw, int proc_num, ssize_t len,
		char *buf);
	int (*sysfs_hsr_write)(struct ksz_sw *sw, int proc_num, int num,
		const char *buf);
#endif

	ssize_t (*sysfs_acl_read)(struct ksz_sw *sw, int proc_num, uint port,
		ssize_t len, char *buf);
	int (*sysfs_acl_write)(struct ksz_sw *sw, int proc_num, uint port,
		int num, const char *buf);

	void (*cfg_mac)(struct ksz_sw *sw, u8 index, const u8 *dest, u32 ports,
		int override, int use_fid, u16 fid);
	void (*cfg_vlan)(struct ksz_sw *sw, u8 index, u16 vid, u16 fid,
		u32 ports);
	u8 (*alloc_mac)(struct ksz_sw *sw);
	void (*free_mac)(struct ksz_sw *sw, u8 index);
	u8 (*alloc_vlan)(struct ksz_sw *sw);
	void (*free_vlan)(struct ksz_sw *sw, u8 index);
	u16 (*alloc_fid)(struct ksz_sw *sw, u16 vid);
	void (*free_fid)(struct ksz_sw *sw, u16 fid);

	const u8 *(*get_br_id)(struct ksz_sw *sw);
	void (*from_backup)(struct ksz_sw *sw, uint p);
	void (*to_backup)(struct ksz_sw *sw, uint p);
	void (*from_designated)(struct ksz_sw *sw, uint p, bool alt);
	void (*to_designated)(struct ksz_sw *sw, uint p);
	void (*tc_detected)(struct ksz_sw *sw, uint p);
	int (*get_tcDetected)(struct ksz_sw *sw, uint p);

	int (*get_id)(struct ksz_sw *sw, u8 *id1, u8 *id2, char *name);
	void (*cfg_tail_tag)(struct ksz_sw *sw, bool enable);
	void (*cfg_each_port)(struct ksz_sw *sw, uint p, bool cpu);
	int (*port_to_phy_addr)(struct ksz_sw *sw, uint p);
	void (*set_port_addr)(struct ksz_sw *sw, uint p, u8 *addr);

	void (*cfg_src_filter)(struct ksz_sw *sw, bool set);
	void (*flush_table)(struct ksz_sw *sw, uint port);
	void (*fwd_unk_mcast)(struct ksz_sw *sw, bool set);
	void (*fwd_unk_ucast)(struct ksz_sw *sw);
	void (*fwd_unk_vid)(struct ksz_sw *sw);

	void (*port_freeze_mib)(struct ksz_sw *sw, uint port, bool freeze);
	void (*freeze_mib)(struct ksz_sw *sw, bool freeze);
};

struct ksz_sw_tx_tag {
	u32 timestamp;
	u16 ports;
};

struct ksz_sw_cached_regs {
	u32 ptp_unit_index;
	u16 ptp_clk_ctrl;
	u16 xmii[2];
};

struct ksz_dev_map {
	u16 cnt;
	u16 mask;
	u16 first;
	u16 phy_id;
	u16 vlan;
	uint proto;
};

struct phy_priv {
	struct ksz_port *port;
	enum phy_state state;
};

/* Switch features and bug fixes. */
#define STP_SUPPORT			(1 << 0)
#define VLAN_PORT			(1 << 1)
#define VLAN_PORT_REMOVE_TAG		(1 << 2)
#define VLAN_PORT_TAGGING		(1 << 3)
#define VLAN_PORT_START			200
#define SW_VLAN_DEV			(1 << 4)
#define MRP_SUPPORT			(1 << 5)

#define ACL_CORRUPT_BUG			(1 << 8)
#define NO_GLOBAL_RESET			(1 << 9)
#define PHY_INTR_BUG			(1 << 10)
#define IS_9893				(1 << 15)
#define SETUP_PHY			(1 << 16)
#define NEW_XMII			(1 << 17)
#define USE_FEWER_PORTS			(1 << 18)
#define GIGABIT_SUPPORT			(1 << 19)
#define IBA_SUPPORT			(1 << 20)
#define NEW_CAP				(1 << 21)
#define AVB_SUPPORT			(1 << 22)
#define REDUNDANCY_SUPPORT		(1 << 23)
#define DLR_HW				(1 << 24)
#define HSR_HW				(1 << 25)
#define HSR_REDBOX			(1 << 26)
#define DSA_SUPPORT			(1 << 28)
#define DIFF_MAC_ADDR			(1 << 29)
#define QW_HW				(1 << 30)
#define PTP_HW				(1 << 31)

/* Software overrides. */
#define PAUSE_FLOW_CTRL			(1 << 0)
#define FAST_AGING			(1 << 1)
#define MCAST_FILTER			(1 << 2)
#define HAVE_MORE_THAN_2_PORTS		(1 << 3)
#define DLR_FORWARD			(1 << 4)
#define UNK_MCAST_BLOCK			(1 << 5)

#define BAD_SPI				(1 << 15)
#define IBA_TEST			(1 << 16)
#define ACL_INTR_MONITOR		(1 << 17)
#define SYSFS_PHY_PORT			(1 << 18)

#define TAIL_PRP_0			(1 << 24)
#define TAIL_PRP_1			(1 << 25)

#define USE_802_1X_AUTH			(1 << 27)
#define VLAN_SET			(1 << 28)
#define PTP_TAG				(1 << 29)
#define TAG_REMOVE			(1 << 30)
#define TAIL_TAGGING			(1 << 31)

#define TAIL_TAG_SET_OVERRIDE		BIT(31)
#define TAIL_TAG_SET_QUEUE		BIT(30)

/**
 * struct ksz_sw - Virtual switch data structure
 * @dev:		Pointer to hardware device.
 * @phydev:		Pointer to PHY device interface.
 * @interface:		The R/G/MII interface used.
 * @msg_enable:		The message flags controlling driver output.
 * @hwlock:		Pointer to hardware lock.
 * @reglock:		Pointer to register lock.
 * @acllock:		ACL table lock.
 * @alulock:		ALU table lock.
 * @vlanlock:		VLAN table lock.
 * @hsrlock:		HSR table lock.
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
 * @phy_port_cnt:	Number of ports with actual PHY.
 * @port_cnt:		Number of ports to support.
 * @monitor_timer_info:	Timer information for monitoring ports.
 * @counter:		Pointer to OS dependent MIB counter information.
 * @link_read:		Workqueue for link monitoring.
 * @ops:		Switch function access.
 * @reg:		Switch register access.
 * @net_ops:		Network related switch function access.
 * @HOST_PORT:		A predefined value indicating the host port.
 * @HOST_MASK:		A predefined value indicating the host port mask.
 * @PORT_MASK:		A predefined value indicating the port mask.
 * @PORT_INTR_MASK:	A predefined value indicating the port interrupt mask.
 * @TAIL_TAG_LOOKUP:	A predefined value indicating tx tail tag lookup.
 * @TAIL_TAG_OVERRIDE:	A predefined value indicating tx tail tag override.
 * @live_ports:		Bitmap of ports with link enabled.
 * @on_ports:		Bitmap of ports with 802.1X enabled.
 * @rx_ports:		Bitmap of ports with receive enabled.
 * @tx_ports:		Bitmap of ports with transmit enabled.
 * @dev_count:		Number of network devices this switch supports.
 * @id:			Hardware ID.  Used for display only.
 * @vlan_id		Used for the VLAN port forwarding feature.
 * @vid:		Used for the VLAN port forwarding feature.
 * @revision:		Hardware revision number.
 * @features:		Switch features to enable.
 * @overrides:		Switch features to override.
 * @multi_dev:		Used to specify multiple devices mode.
 * @stp:		Used to enable STP.
 * @fast_aging:		Used to enable fast aging.
 */
struct ksz_sw {
	void *dev;
	phy_interface_t interface;
	u32 msg_enable;
	wait_queue_head_t queue;
	struct sk_buff_head txq;
	struct mutex *hwlock;
	struct mutex *reglock;
	struct mutex acllock;
	struct mutex alulock;
	struct mutex vlanlock;
	struct mutex hsrlock;
	struct mutex lock;
	int intr_cnt;
	int intr_using;

	struct ksz_sw_info *info;
	struct ksz_port_info port_info[SWITCH_PORT_NUM];
	struct net_device *main_dev;
	struct net_device *netdev[TOTAL_PORT_NUM];
	struct ksz_port *netport[TOTAL_PORT_NUM];
	struct phy_device phy_map[TOTAL_PORT_NUM + 1];
	struct phy_device *phy[TOTAL_PORT_NUM + 1];
	struct phy_priv phydata[TOTAL_PORT_NUM + 1];
	int dev_offset;
	int phy_offset;
	struct ksz_port_state port_state[TOTAL_PORT_NUM];
	struct ksz_port_mib port_mib[TOTAL_PORT_NUM];
	u8 mib_interval_start[4];
	unsigned long next_jiffies;
	int mib_cnt;
	int mib_port_cnt;
	int phy_port_cnt;
	int dsa_port_cnt;
	int port_cnt;
	struct ksz_timer_info *monitor_timer_info;
	struct ksz_counter_info *counter;
	struct delayed_work *link_read;

	const struct ksz_sw_ops *ops;
	const struct ksz_sw_reg_ops *reg;
	const struct ksz_sw_reg_ops *org_reg;
	const struct ksz_sw_reg_ops *cur;
	struct ksz_sw_net_ops *net_ops;
	struct delayed_work set_ops;
	struct work_struct set_addr;
	struct work_struct tx_fwd;

	int HOST_PORT;
	u16 HOST_MASK;
	u16 PORT_MASK;
	u16 PORT_INTR_MASK;
	u16 TAIL_TAG_LOOKUP;
	u16 TAIL_TAG_OVERRIDE;
	u16 TAIL_TAG_SHIFT;
	u32 intr_mask;
	u32 port_intr_mask;
	u32 phy_intr;
	u16 dev_ports;
	u16 live_ports;
	u16 on_ports;
	u16 open_ports;
	u16 rx_ports[NUM_OF_MSTI];
	u16 tx_ports[NUM_OF_MSTI];
	u8 ctrl_queue;
	u8 tx_pad[60];
	int mtu;
	int tx_start;
	int priv_port;
	struct ksz_sw_tx_tag tag;
	struct ksz_sw_cached_regs cached;

	int dev_major;
	u8 *msg_buf;
	struct sw_dev_info *dev_list[2];
	struct sw_dev_info *dev_info;
	uint notifications;
	char dev_name[20];

	int chip_id;
	int dev_count;
	int id;
	u32 vlan_id;
	u16 vid;
	u16 alu_index;
	u8 alu_type;
	u8 alu_dirty;
	u16 vlan_index;
	u16 hsr_index;
	u8 hsr_dirty;
	u8 vlan_dirty;
	u8 verbose;
	u8 running;

	int revision;
	uint features;
	uint overrides;

	struct napi_struct *napi;

	int multi_dev;
	int stp;
	int fast_aging;
	int sgmii_mode;
	struct ksz_dev_map eth_maps[SWITCH_PORT_NUM];
	int eth_cnt;

#ifdef CONFIG_KSZ_MRP
	struct delayed_work set_mrp;
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
	u16 speed;
	u8 force_link;
	u16 link_ports;
	u16 live_ports;

	struct ksz_port_info *linked;

	struct net_device *netdev;
	struct phy_device *phydev;
	struct ksz_sw *sw;
	struct work_struct link_update;
};

struct lan_attributes {
	int info;
	int version;
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
	int hsr_table;
	int aging;
	int fast_aging;
	int link_aging;
	int bcast_per;
	int mcast_storm;
	int tx_queue_based;
	int diffserv_map;
	int p_802_1p_map;
	int vlan;
	int null_vid;
	int drop_inv_vid;
	int macaddr;
	int mirror_mode;
	int igmp_snoop;
	int ipv6_mld_snoop;
	int ipv6_mld_option;
	int aggr_backoff;
	int no_exc_drop;
	int jumbo_packet;
	int legal_packet;
	int length_check;
	int back_pressure;
	int sw_flow_ctrl;
	int sw_half_duplex;
	int sw_10_mbit;
	int fair_flow_ctrl;
	int vlan_bound;
	int double_tag;
	int isp;
	int hsr;
	int hsr_redbox_id;
	int hsr_net_id;
	int mtu;
	int unk_ucast_fwd;
	int unk_ucast_ports;
	int unk_mcast_fwd;
	int unk_mcast_ports;
	int unk_vid_fwd;
	int unk_vid_ports;
	int pass_pause;
	int pme;
	int pme_polarity;

	int host_port;
	int ports;
	int dev_start;
	int vlan_start;
	int avb;
	int stp;
	int two_dev;
	int authen;

	int alu_fid;
	int alu_use_fid;
	int alu_override;
	int alu_valid;
	int alu_mstp;
	int alu_prio;
	int alu_src;
	int alu_dst;
	int alu_ports;
	int alu_addr;
	int alu_type;
	int alu_index;
	int alu_info;

	int vlan_valid;
	int vlan_ports;
	int vlan_untag;
	int vlan_fid;
	int vlan_mstp;
	int vlan_prio;
	int vlan_option;
	int vlan_index;
	int vlan_info;
	int vid2fid;
	int fid2mstid;

#ifdef CONFIG_KSZ_STP
	int stp_br_info;
	int stp_br_on;
	int stp_br_prio;
	int stp_br_fwd_delay;
	int stp_br_max_age;
	int stp_br_hello_time;
	int stp_br_tx_hold;
	int stp_version;
#ifdef CONFIG_KSZ_MSTP
	int stp_br_max_hops;
	int stp_msti;
	int stp_msti_vid;
	int stp_mstp_cfg;
	int stp_mstp_name;
#endif
#endif

#ifdef CONFIG_KSZ_MRP
#ifdef CONFIG_KSZ_MSRP
	int msrp_info;
	int msrpEnabled;
	int msrp_sr_a;
#endif
#endif

#ifdef CONFIG_KSZ_HSR
	int hsr_valid;
	int hsr_age_cnt;
	int hsr_path_id;
	int hsr_addr;
	int hsr_index;
	int hsr_info;
	int hsr_state;
#endif

	int no_color;
	int color_red;
	int color_yellow;
	int color_green;

	int vlan_filter_dynamic;
	int vlan_filter_static;
};

struct sw_attributes {
	int mib;
	int vid;
	int member;
	int bcast_storm;
	int diffserv;
	int p_802_1p;
	int prio_vlan;
	int prio_mac;
	int prio_acl;
	int prio_highest;
	int prio_or;
	int port_prio;
	int non_vid;
	int ingress;
	int drop_non_vlan;
	int drop_tagged;
	int replace_vid;
	int replace_prio;
	int mac_802_1x;
	int src_addr_filter;
	int vlan_lookup_0;
	int mstp;
	int rx;
	int tx;
	int learn;
	int power;
	int prio_queue;
	int rx_prio_rate;
	int tx_prio_rate;
	int limit;
	int limit_port_based;
	int limit_packet_based;
	int limit_flow_ctrl;
	int limit_cnt_ifg;
	int limit_cnt_pre;
	int rx_p0_rate;
	int rx_p1_rate;
	int rx_p2_rate;
	int rx_p3_rate;
	int rx_p4_rate;
	int rx_p5_rate;
	int rx_p6_rate;
	int rx_p7_rate;
	int tx_q0_rate;
	int tx_q1_rate;
	int tx_q2_rate;
	int tx_q3_rate;
	int color_map;
	int tc_map;
	int mirror_port;
	int mirror_rx;
	int mirror_tx;
	int back_pressure;
	int force_flow_ctrl;
	int pass_all;
	int tail_tag;

	int cust_vid;
	int sr_1_vid;
	int sr_2_vid;
	int sr_1_type;
	int sr_2_type;

	int pme_ctrl;
	int pme_status;

	int authen_mode;
	int acl;
	int acl_first_rule;
	int acl_ruleset;
	int acl_mode;
	int acl_enable;
	int acl_src;
	int acl_equal;
	int acl_addr;
	int acl_type;
	int acl_cnt;
	int acl_msec;
	int acl_intr_mode;
	int acl_ip_addr;
	int acl_ip_mask;
	int acl_protocol;
	int acl_seqnum;
	int acl_port_mode;
	int acl_max_port;
	int acl_min_port;
	int acl_tcp_flag_enable;
	int acl_tcp_flag;
	int acl_tcp_flag_mask;
	int acl_prio_mode;
	int acl_prio;
	int acl_vlan_prio_replace;
	int acl_vlan_prio;
	int acl_map_mode;
	int acl_ports;
	int acl_index;
	int acl_act_index;
	int acl_act;
	int acl_rule_index;
	int acl_info;
	int acl_table;

	int p_index;
	int q_index;
	int police_type;
	int non_dscp_color;
	int police_drop_all;
	int police_port_based;
	int color_mark;
	int color_remap;
	int drop_srp;
	int color_aware;
	int police;

	int q_cir;
	int q_pir;
	int q_cbs;
	int q_pbs;

	int wred_max;
	int wred_min;
	int wred_multiplier;
	int wred_avg_size;
	int wred_q_max;
	int wred_q_min;
	int wred_q_multiplier;
	int wred_q_avg_size;
	int wred_random_drop;
	int wred_drop_gyr;
	int wred_drop_yr;
	int wred_drop_r;
	int wred_drop_all;
	int wred_q_pmon;

	int q_scheduling;
	int q_shaping;
#ifdef MTI_PREEMPT_ENABLE
	int preempt;
#endif
	int q_tx_ratio;
	int q_credit_hi;
	int q_credit_lo;
	int q_credit_incr;
	int srp;

	int qm_drop;
	int qm_burst;
	int qm_resv_space;
	int qm_hi;
	int qm_lo;
	int qm_tx_used;
	int qm_tx_avail;
	int qm_tx_calc;

	int mmd_id;
	int mmd_reg;
	int mmd_val;

	int rx_flow_ctrl;
	int tx_flow_ctrl;

	int duplex;
	int speed;
	int mac_oper;
	int vlan_restricted;
	int vlan_untagged;

#ifdef CONFIG_KSZ_STP
	int stp_info;
	int stp_on;
	int stp_prio;
	int stp_admin_path_cost;
	int stp_path_cost;
	int stp_admin_edge;
	int stp_auto_edge;
	int stp_mcheck;
	int stp_admin_p2p;
	int stp_auto_isolate;
#endif

#ifdef CONFIG_KSZ_MRP
	int mmrpEnabled;
	int mmrp_mac;
	int mmrp_svc;
	int mmrp_reg;
	int mvrpEnabled;
	int mvrp_vid;
	int mvrp_reg;

#ifdef CONFIG_KSZ_MSRP
	int asCapable;
	int msrpEnabled;
	int q_delta;
	int q_admin_mbps;
	int q_admin_slope;
	int q_oper_slope;
	int q_alg;
	int sr_0_rx_prio;
	int sr_0_tx_prio;
	int sr_0_boundary;
	int sr_0_latency;
	int sr_1_rx_prio;
	int sr_1_tx_prio;
	int sr_1_boundary;
	int sr_1_latency;
#endif
#endif

	int linkmd;
	int sqi;
	int mac_loopback;
	int phy_loopback;
	int remote_loopback;
};

#endif
