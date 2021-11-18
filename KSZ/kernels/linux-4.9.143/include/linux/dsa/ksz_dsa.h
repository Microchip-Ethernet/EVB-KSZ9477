/* SPDX-License-Identifier: GPL-2.0
 *
 * Microchip KSZ series switch common definitions
 *
 * Copyright (C) 2017-2021 Microchip Technology Inc.
 */

#include <linux/phy.h>
#include <linux/regmap.h>

struct ksz_device;

struct ksz_tag_ops {
	int (*get_len)(struct ksz_device *dev);
	int (*get_tag)(struct ksz_device *dev, u8 *tag, int *port);
	void (*set_tag)(struct ksz_device *dev, void *ptr, u8 *addr, int p);
};

struct vlan_table {
	u32 table[3];
};

struct ksz_port_mib {
	struct mutex cnt_mutex;		/* structure access */
	u8 cnt_ptr;
	u64 *counters;
};

struct ksz_port {
	u16 member;
	u16 vid_member;
	u8 intr_mask;
	u8 link_val;
	int stp_state;
	struct phy_device phydev;
	struct phy_device *actual_phydev;

	u32 on:1;			/* port is not disabled by hardware */
	u32 phy:1;			/* port has a PHY */
	u32 fiber:1;			/* port is fiber */
	u32 sgmii:1;			/* port is SGMII */
	u32 force:1;
	u32 link_just_down:1;		/* link just goes down */
	u32 freeze:1;			/* MIB counter freeze is enabled */

	struct ksz_port_mib mib;
};

struct ksz_device {
	struct dsa_switch *ds;
	struct ksz_platform_data *pdata;
	const char *name;
	struct regmap *regmap[3];

	struct mutex stats_mutex;	/* status access */
	struct mutex alu_mutex;		/* ALU access */
	struct mutex vlan_mutex;	/* vlan access */
	const struct ksz_io_ops *ops;
	const struct ksz_dev_ops *dev_ops;
	const struct ksz_tag_ops *tag_ops;

	struct device *dev;
	int irq;

	void *priv;

	/* chip specific data */
	u32 chip_id;
	int num_vlans;
	int num_alus;
	int num_statics;
	int cpu_port;			/* port connected to CPU */
	int cpu_ports;			/* port bitmap can be cpu port */
	int phy_port_cnt;
	int port_cnt;
	int reg_mib_cnt;
	int mib_cnt;
	int mib_port_cnt;
	int last_port;			/* ports after that not used */
	phy_interface_t interface;
	u32 regs_size;

	struct vlan_table *vlan_cache;

	u8 *txbuf;

	struct ksz_port *ports;
	struct timer_list mib_read_timer;
	struct work_struct mib_read;
	unsigned long mib_read_interval;
	struct timer_list sgmii_timer;
	struct work_struct sgmii_check;
	u16 br_member;
	u16 member;
	u16 live_ports;
	u16 on_ports;			/* ports enabled by DSA */
	u16 rx_ports;
	u16 tx_ports;
	u16 vid_ports;
	u16 vlan_ports;
	u16 mirror_rx;
	u16 mirror_tx;
	u32 features;			/* chip specific features */
	u32 overrides;			/* chip functions set by user */
	u16 host_mask;
	u16 port_mask;
	u32 vlan_up:1;
	u8 sgmii_mode;
};

