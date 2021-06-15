/* SPDX-License-Identifier: GPL-2.0
 * Microchip switch driver common header
 *
 * Copyright (C) 2017-2021 Microchip Technology Inc.
 */

#ifndef __KSZ_COMMON_H
#define __KSZ_COMMON_H

void ksz_update_port_member(struct ksz_device *dev, int port);
void ksz_init_mib_timer(struct ksz_device *dev);

/* Common DSA access functions */

int ksz_phy_read16(struct dsa_switch *ds, int addr, int reg);
int ksz_phy_write16(struct dsa_switch *ds, int addr, int reg, u16 val);
void ksz_adjust_link(struct dsa_switch *ds, int port,
		     struct phy_device *phydev);
int ksz_sset_count(struct dsa_switch *ds, int port, int sset);
void ksz_get_ethtool_stats(struct dsa_switch *ds, int port, uint64_t *buf);
int ksz_port_bridge_join(struct dsa_switch *ds, int port,
			 struct net_device *br);
void ksz_port_bridge_leave(struct dsa_switch *ds, int port,
			   struct net_device *br);
void ksz_port_fast_age(struct dsa_switch *ds, int port);
int ksz_port_vlan_prepare(struct dsa_switch *ds, int port,
			  const struct switchdev_obj_port_vlan *vlan);
int ksz_port_fdb_dump(struct dsa_switch *ds, int port,
		      dsa_fdb_dump_cb_t *cb, void *data);
int ksz_port_mdb_prepare(struct dsa_switch *ds, int port,
			 const struct switchdev_obj_port_mdb *mdb);
void ksz_port_mdb_add(struct dsa_switch *ds, int port,
		      const struct switchdev_obj_port_mdb *mdb);
int ksz_port_mdb_del(struct dsa_switch *ds, int port,
		     const struct switchdev_obj_port_mdb *mdb);
int ksz_enable_port(struct dsa_switch *ds, int port, struct phy_device *phy);
void ksz_disable_port(struct dsa_switch *ds, int port, struct phy_device *phy);

ssize_t ksz_registers_read(struct file *filp, struct kobject *kobj,
			   struct bin_attribute *bin_attr, char *buf,
			   loff_t off, size_t count);
ssize_t ksz_registers_write(struct file *filp, struct kobject *kobj,
			    struct bin_attribute *bin_attr, char *buf,
			    loff_t off, size_t count);

/* Common register access functions */

/* Switch may require register transformation. */
#ifndef KSZ_BYTE_REG
#define KSZ_BYTE_REG(reg)
#endif
#ifndef KSZ_WORD_REG
#define KSZ_WORD_REG(reg)
#endif
#ifndef KSZ_DWORD_REG
#define KSZ_DWORD_REG(reg)
#endif

static inline int ksz_read8(struct ksz_device *dev, u32 reg, u8 *val)
{
	int ret;

	KSZ_BYTE_REG(reg);
	ret = regmap_raw_read(dev->regmap[0], reg, val, 1);

	return ret;
}

static inline int ksz_read16(struct ksz_device *dev, u32 reg, u16 *val)
{
	int ret;

	KSZ_WORD_REG(reg);
	ret = regmap_raw_read(dev->regmap[0], reg, val, 2);
	if (!ret)
		*val = be16_to_cpu(*val);

	return ret;
}

static inline int ksz_read24(struct ksz_device *dev, u32 reg, u32 *val)
{
	int ret;

	ret = regmap_raw_read(dev->regmap[0], reg, val, 3);
	if (!ret) {
		*val = be32_to_cpu(*val);
		/* convert to 24bit */
		*val >>= 8;
	}

	return ret;
}

static inline int ksz_read32(struct ksz_device *dev, u32 reg, u32 *val)
{
	int ret;

	KSZ_DWORD_REG(reg);
	ret = regmap_raw_read(dev->regmap[0], reg, val, 4);
	if (!ret)
		*val = be32_to_cpu(*val);

	return ret;
}

static inline int ksz_write8(struct ksz_device *dev, u32 reg, u8 value)
{
	KSZ_BYTE_REG(reg);
	return regmap_raw_write(dev->regmap[0], reg, &value, 1);
}

static inline int ksz_write16(struct ksz_device *dev, u32 reg, u16 value)
{
	KSZ_WORD_REG(reg);
	value = cpu_to_be16(value);
	return regmap_raw_write(dev->regmap[0], reg, &value, 2);
}

static inline int ksz_write24(struct ksz_device *dev, u32 reg, u32 value)
{
	/* make it to big endian 24bit from MSB */
	value <<= 8;
	value = cpu_to_be32(value);
	return regmap_raw_write(dev->regmap[0], reg, &value, 3);
}

static inline int ksz_write32(struct ksz_device *dev, u32 reg, u32 value)
{
	KSZ_DWORD_REG(reg);
	value = cpu_to_be32(value);
	return regmap_raw_write(dev->regmap[0], reg, &value, 4);
}

static inline int ksz_get(struct ksz_device *dev, u32 reg, void *data,
			  size_t len)
{
	return regmap_raw_read(dev->regmap[0], reg, data, len);
}

static inline int ksz_set(struct ksz_device *dev, u32 reg, void *data,
			  size_t len)
{
	return regmap_raw_write(dev->regmap[0], reg, data, len);
}

static inline void ksz_pread8(struct ksz_device *dev, int port, int offset,
			      u8 *data)
{
	ksz_read8(dev, PORT_CTRL_ADDR(port, offset), data);
}

static inline void ksz_pread16(struct ksz_device *dev, int port, int offset,
			       u16 *data)
{
	ksz_read16(dev, PORT_CTRL_ADDR(port, offset), data);
}

static inline void ksz_pread32(struct ksz_device *dev, int port, int offset,
			       u32 *data)
{
	ksz_read32(dev, PORT_CTRL_ADDR(port, offset), data);
}

static inline void ksz_pwrite8(struct ksz_device *dev, int port, int offset,
			       u8 data)
{
	ksz_write8(dev, PORT_CTRL_ADDR(port, offset), data);
}

static inline void ksz_pwrite16(struct ksz_device *dev, int port, int offset,
				u16 data)
{
	ksz_write16(dev, PORT_CTRL_ADDR(port, offset), data);
}

static inline void ksz_pwrite32(struct ksz_device *dev, int port, int offset,
				u32 data)
{
	ksz_write32(dev, PORT_CTRL_ADDR(port, offset), data);
}

static inline void ksz_cfg(struct ksz_device *dev, u32 addr, u8 bits, bool set)
{
	regmap_update_bits(dev->regmap[0], addr, bits, set ? bits : 0);
}

static inline void ksz_port_cfg(struct ksz_device *dev, int port, int offset,
				u8 bits, bool set)
{
	regmap_update_bits(dev->regmap[0], PORT_CTRL_ADDR(port, offset), bits,
			   set ? bits : 0);
}

static inline void ksz_cfg16(struct ksz_device *dev, u32 addr, u16 bits,
			     bool set)
{
	regmap_update_bits(dev->regmap[1], addr, bits, set ? bits : 0);
}

static inline void ksz_port_cfg16(struct ksz_device *dev, int port, int offset,
				  u16 bits, bool set)
{
	regmap_update_bits(dev->regmap[1], PORT_CTRL_ADDR(port, offset), bits,
			   set ? bits : 0);
}
#endif
