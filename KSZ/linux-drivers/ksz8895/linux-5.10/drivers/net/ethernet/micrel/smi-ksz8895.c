/**
 * Microchip KSZ8895 SMI driver
 *
 * Copyright (c) 2018-2023 Microchip Technology Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if 0
#define DEBUG
#define DBG
#define DEBUG_MSG
#if 0
#define DBG_LINK
#endif
#endif

#include <linux/debugfs.h>
#include <linux/seq_file.h>

#include "ksz_cfg_8895.h"
#include "ksz_spi_net.h"

#define USE_SHOW_HELP
#include "ksz_common.c"
#include "ksz_req.c"

#define SW_DRV_RELDATE			"Mar 25, 2023"
#define SW_DRV_VERSION			"1.2.3"

/* -------------------------------------------------------------------------- */

#define MIB_READ_INTERVAL		(HZ / 2)

static void smi_addr(unsigned reg, int *phyid, int *regnum)
{
	int phy_hi;

	*regnum = reg & 0x1f;
	*phyid = (reg & 0xe0) >> 5;
	phy_hi = (*phyid >> 1) << 3;
	*phyid &= 1;
	*phyid |= 6;
	*phyid |= phy_hi;
}

static u8 mdio_r8(struct sw_priv *priv, unsigned reg)
{
	struct smi_hw_priv *smi = priv->hw_dev;
	int phyid;
	int regnum;
	int ret;

	smi_addr(reg, &phyid, &regnum);
	ret = smi->read(smi->bus, phyid, regnum);
	return (u8)ret;
}

static void mdio_w8(struct sw_priv *priv, unsigned reg, unsigned val)
{
	struct smi_hw_priv *smi = priv->hw_dev;
	int phyid;
	int regnum;
	int ret;

	smi_addr(reg, &phyid, &regnum);
	ret = smi->write(smi->bus, phyid, regnum, val & 0xff);
}

static uint mdio_r_c(struct sw_priv *priv, unsigned reg, int cnt)
{
	int i;
	int ret;
	uint val;

	val = 0;
	for (i = 0; i < cnt; i++) {
		ret = mdio_r8(priv, reg++);
		val <<= 8;
		val |= ret;
	}
	return val;
}

static void mdio_w_c(struct sw_priv *priv, unsigned reg, unsigned val, int cnt)
{
	int i;

	for (i = 0; i < cnt; i++) {
		mdio_w8(priv, reg++, val);
		val >>= 8;
	}
}

static u16 mdio_r16(struct sw_priv *priv, unsigned reg)
{
	uint val;

	val = mdio_r_c(priv, reg, 2);
	return (u16)val;
}

static u32 mdio_r32(struct sw_priv *priv, unsigned reg)
{
	uint val;

	val = mdio_r_c(priv, reg, 4);
	return (u32)val;
}

static void mdio_w16(struct sw_priv *priv, unsigned reg, unsigned val)
{
	val = cpu_to_be16(val);
	mdio_w_c(priv, reg, val, 2);
}

static void mdio_w32(struct sw_priv *priv, unsigned reg, unsigned val)
{
	val = cpu_to_be32(val);
	mdio_w_c(priv, reg, val, 4);
}

static int mdio_r(struct sw_priv *priv, u32 reg, void *buf, unsigned len)
{
	int i;
	int ret;
	u8 *data = (u8 *)buf;

	for (i = 0; i < len; i++) {
		ret = mdio_r8(priv, reg++);
		data[i] = ret & 0xff;
	}
	return 0;
}

static int mdio_w(struct sw_priv *priv, u32 reg, void *buf, unsigned len)
{
	int i;
	u8 *data = (u8 *)buf;

	for (i = 0; i < len; i++) {
		mdio_w8(priv, reg++, data[i]);
	}
	return 0;
}

static u8 smi_r8(struct ksz_sw *sw, unsigned reg)
{
	return mdio_r8(sw->dev, reg);
}

static u16 smi_r16(struct ksz_sw *sw, unsigned reg)
{
	return mdio_r16(sw->dev, reg);
}

static u32 smi_r32(struct ksz_sw *sw, unsigned reg)
{
	return mdio_r32(sw->dev, reg);
}

static void smi_w8(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	mdio_w8(sw->dev, reg, val);
}

static void smi_w16(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	mdio_w16(sw->dev, reg, val);
}

static void smi_w32(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	mdio_w32(sw->dev, reg, val);
}

static void smi_r(struct ksz_sw *sw, unsigned reg, void *buf, size_t cnt)
{
	mdio_r(sw->dev, reg, buf, cnt);
}

static void smi_w(struct ksz_sw *sw, unsigned reg, void *buf, size_t cnt)
{
	mdio_w(sw->dev, reg, buf, cnt);
}

#include "ksz_sw_8895.c"

static struct ksz_sw_reg_ops smi_reg_ops = {
	.r8			= smi_r8,
	.r16			= smi_r16,
	.r32			= smi_r32,
	.w8			= smi_w8,
	.w16			= smi_w16,
	.w32			= smi_w32,

	.r			= smi_r,
	.w			= smi_w,

	.get			= sw_reg_get,
	.set			= sw_reg_set,
};

/* -------------------------------------------------------------------------- */

static int smi_probe(struct platform_device **pdev, struct mii_bus *bus,
		     int irq,
		     int (*read)(struct mii_bus *b, int id, int reg),
		     int (*write)(struct mii_bus *b, int id, int reg, u16 val))
{
	struct smi_hw_priv *smi;
	struct sw_priv *priv = NULL;
	int ret = -ENOMEM;

	*pdev = platform_device_register_data(NULL, "smi", sw_device_present,
					      NULL, 0);
	if (IS_ERR(*pdev))
		return PTR_ERR(*pdev);

#ifdef DEBUG_MSG
	if (init_dbg())
		goto probe_err;
#endif

	priv = kzalloc(sizeof(struct sw_priv), GFP_KERNEL);
	if (!priv)
		goto probe_err;

	priv->hw_dev = kzalloc(sizeof(struct smi_hw_priv), GFP_KERNEL);
	if (!priv->hw_dev)
		goto probe_err;

	smi = priv->hw_dev;

	smi->bus = bus;
	smi->read = read;
	smi->write = write;

	priv->dev = &(*pdev)->dev;
	priv->of_dev = &(*pdev)->dev;

	priv->sw.reg = &smi_reg_ops;

	priv->irq = irq;

	ret = ksz_probe(priv);

	/* It will be deleted when probing fails. */
	priv = NULL;
	if (!ret)
		return 0;

probe_err:
	if (priv) {
		if (priv->hw_dev)
			kfree(priv->hw_dev);
		kfree(priv);
	}
	if (*pdev)
		platform_device_unregister(*pdev);

#ifdef DEBUG_MSG
	exit_dbg();
#endif
	return ret;
}

static int smi_remove(struct platform_device *pdev)
{
	struct sw_priv *priv = platform_get_drvdata(pdev);
	int ret;

	ret = ksz_remove(priv);
	platform_device_unregister(pdev);

#ifdef DEBUG_MSG
	exit_dbg();
#endif
	return ret;
}

