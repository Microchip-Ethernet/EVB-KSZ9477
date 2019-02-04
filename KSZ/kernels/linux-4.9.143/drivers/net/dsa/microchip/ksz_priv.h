/* SPDX-License-Identifier: GPL-2.0
 *
 * Microchip KSZ series switch common definitions
 *
 * Copyright (C) 2017-2019 Microchip Technology Inc.
 */

#ifndef __KSZ_PRIV_H
#define __KSZ_PRIV_H

#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/phy.h>
#include <linux/etherdevice.h>
#include <net/dsa.h>
#include <linux/dsa/ksz_dsa.h>

struct alu_struct {
	/* entry 1 */
	u8	is_static:1;
	u8	is_src_filter:1;
	u8	is_dst_filter:1;
	u8	prio_age:3;
	u32	_reserv_0_1:23;
	u8	mstp:3;
	/* entry 2 */
	u8	is_override:1;
	u8	is_use_fid:1;
	u32	_reserv_1_1:23;
	u8	port_forward:7;
	/* entry 3 & 4*/
	u32	_reserv_2_1:9;
	u8	fid:7;
	u8	mac[ETH_ALEN];
};

struct ksz_dev_ops {
	void (*cfg_port_member)(struct ksz_device *dev, int port, u8 member);
	void (*flush_dyn_mac_table)(struct ksz_device *dev, int port);
	void (*phy_setup)(struct ksz_device *dev, int port,
			  struct phy_device *phy);
	void (*port_setup)(struct ksz_device *dev, int port, bool cpu_port);
	void (*r_phy)(struct ksz_device *dev, u16 phy, u16 reg, u16 *val);
	void (*w_phy)(struct ksz_device *dev, u16 phy, u16 reg, u16 val);
	int (*r_dyn_mac_table)(struct ksz_device *dev, u16 addr, u8 *mac_addr,
			       u8 *fid, u8 *src_port, u8 *timestamp,
			       u16 *entries);
	int (*r_sta_mac_table)(struct ksz_device *dev, u16 addr,
			       struct alu_struct *alu);
	void (*w_sta_mac_table)(struct ksz_device *dev, u16 addr,
				struct alu_struct *alu);
	void (*r_mib_cnt)(struct ksz_device *dev, int port, u16 addr,
			  u64 *cnt);
	void (*r_mib_pkt)(struct ksz_device *dev, int port, u16 addr,
			  u64 *dropped, u64 *cnt);
	void (*freeze_mib)(struct ksz_device *dev, int port, bool freeze);
	void (*port_init_cnt)(struct ksz_device *dev, int port);
	int (*get)(struct ksz_device *dev, u32 reg, void *data, size_t len);
	int (*set)(struct ksz_device *dev, u32 reg, void *data, size_t len);
	int (*shutdown)(struct ksz_device *dev);
	int (*detect)(struct ksz_device *dev);
	int (*init)(struct ksz_device *dev);
	void (*exit)(struct ksz_device *dev);
};

struct ksz_device *ksz_switch_alloc(struct device *base);
int ksz_switch_register(struct ksz_device *dev,
			const struct ksz_dev_ops *ops,
			const struct ksz_tag_ops *tag_ops);
void ksz_switch_remove(struct ksz_device *dev);

int ksz8795_switch_register(struct ksz_device *dev);
int ksz8895_switch_register(struct ksz_device *dev);
int ksz8463_switch_register(struct ksz_device *dev);
int ksz8863_switch_register(struct ksz_device *dev);
int ksz9477_switch_register(struct ksz_device *dev);

#endif
