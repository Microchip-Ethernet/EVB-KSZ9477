/*
 * Copyright (C) 2015 Microchip Technology
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mii.h>
#include <linux/ethtool.h>
#include <linux/phy.h>
#include <linux//delay.h>
#include <linux/microchipphy.h>

#define DRIVER_AUTHOR	"WOOJUNG HUH <woojung.huh@microchip.com>"
#define DRIVER_DESC	"Microchip LAN88XX PHY driver"

struct lan88xx_priv {
	int	chip_id;
	int	chip_rev;
	__u32	wolopts;
};

struct lan87xx_priv {
	int	chip_id;
	int	chip_rev;
};

struct access_ereg_val {
	u8  mode;
	u8  bank;
	u8  offset;
	u16 val;
	u16 mask;
};

static int access_ereg(struct phy_device *phydev, u8 mode, u8 bank,
		       u8 offset, u16 val)
{
	u16 ereg = 0;
	int rc = 0;

	if (mode > 1 || bank > 7)
		return -EINVAL;

	if (bank == PHYACC_ATTR_BANK_SMI) {
		if (mode == PHYACC_ATTR_MODE_WRITE)
			rc = phy_write(phydev, offset, val);
		else
			rc = phy_read(phydev, offset);
		return rc;
	}

	if (mode == PHYACC_ATTR_MODE_WRITE) {
		ereg = LAN87XX_MASK_WRITE_CONTROL;
		rc = phy_write(phydev, LAN87XX_EXT_REG_WR_DATA, val);
		if (rc < 0)
			return rc;
	} else {
		ereg = LAN87XX_MASK_READ_CONTROL;
	}

	ereg |= (bank << 8) | offset;

	rc = phy_write(phydev, LAN87XX_EXT_REG_CTL, ereg);
	if (rc < 0)
		return rc;

	if (mode == PHYACC_ATTR_MODE_READ)
		rc = phy_read(phydev, LAN87XX_EXT_REG_RD_DATA);

	return rc;
}

static int access_ereg_modify_changed(struct phy_device *phydev,
				      u8 bank, u8 offset, u16 val, u16 mask)
{
	int new = 0, rc = 0;

	if (bank > 7)
		return -EINVAL;

	rc = access_ereg(phydev, PHYACC_ATTR_MODE_READ, bank, offset, val);
	if (rc < 0)
		return rc;

	new = val | (rc & (mask ^ 0xFFFF));
	rc = access_ereg(phydev, PHYACC_ATTR_MODE_WRITE, bank, offset, new);

	return rc;
}

static int lan87xx_phy_init(struct phy_device *phydev)
{
	static const struct access_ereg_val init[] = {
		/* TX Amplitude = 5 */
		{PHYACC_ATTR_MODE_MODIFY, PHYACC_ATTR_BANK_AFE, 0x0B,
		 0x000A, 0x001E},
		/* Clear SMI interrupts */
		{PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_SMI, 0x18,
		 0, 0},
		/* Clear MISC interrupts */
		{PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_MISC, 0x08,
		 0, 0},
		/* Turn on TC10 Ring Oscillator (ROSC) */
		{PHYACC_ATTR_MODE_MODIFY, PHYACC_ATTR_BANK_MISC, 0x20,
		 0x0020, 0x0020},
		/* WUR Detect Length to 1.2uS, LPC Detect Length to 1.09uS */
		{PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_PCS, 0x20,
		 0x283C, 0},
		/* Wake_In Debounce Length to 39uS, Wake_Out Length to 79uS */
		{PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_MISC, 0x21,
		 0x274F, 0},
		/* Enable Auto Wake Forward to Wake_Out, ROSC on, Sleep,
		 * and Wake_In to wake PHY
		 */
		{PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_MISC, 0x20,
		 0x80A7, 0},
		/* Enable WUP Auto Fwd, Enable Wake on MDI, Wakeup Debouncer
		 * to 128 uS
		 */
		{PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_MISC, 0x24,
		 0xF110, 0},
		/* Enable HW Init */
		{PHYACC_ATTR_MODE_MODIFY, PHYACC_ATTR_BANK_SMI, 0x1A,
		 0x0100, 0x0100},
	};
	int rc, i;

	/* Start manual initialization procedures in Managed Mode */
	rc = access_ereg_modify_changed(phydev, PHYACC_ATTR_BANK_SMI,
					0x1a, 0x0000, 0x0100);
	if (rc < 0)
		return rc;

	/* Soft Reset the SMI block */
	rc = access_ereg_modify_changed(phydev, PHYACC_ATTR_BANK_SMI,
					0x00, 0x8000, 0x8000);
	if (rc < 0)
		return rc;

	/* Wait for the self-clearing bit to be cleared */
	usleep_range(1000, 2000);
	rc = access_ereg(phydev, PHYACC_ATTR_MODE_READ,
			 PHYACC_ATTR_BANK_SMI, 0x00, 0);
	if (rc < 0)
		return rc;
	if ((rc & 0x8000) != 0)
		return -ETIMEDOUT;

	/* PHY Initialization */
	for (i = 0; i < ARRAY_SIZE(init); i++) {
		if (init[i].mode == PHYACC_ATTR_MODE_MODIFY) {
			rc = access_ereg_modify_changed(phydev, init[i].bank,
							init[i].offset,
							init[i].val,
							init[i].mask);
		} else {
			rc = access_ereg(phydev, init[i].mode, init[i].bank,
					 init[i].offset, init[i].val);
		}
		if (rc < 0)
			return rc;
	}

	return 0;
}

static int lan88xx_phy_config_intr(struct phy_device *phydev)
{
	int rc;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED) {
		/* unmask all source and clear them before enable */
		rc = phy_write(phydev, LAN88XX_INT_MASK, 0x7FFF);
		rc = phy_read(phydev, LAN88XX_INT_STS);
		rc = phy_write(phydev, LAN88XX_INT_MASK,
			       LAN88XX_INT_MASK_MDINTPIN_EN_ |
			       LAN88XX_INT_MASK_LINK_CHANGE_);
	} else {
		rc = phy_write(phydev, LAN88XX_INT_MASK, 0);
	}

	return rc < 0 ? rc : 0;
}

static int lan88xx_phy_ack_interrupt(struct phy_device *phydev)
{
	int rc = phy_read(phydev, LAN88XX_INT_STS);

	return rc < 0 ? rc : 0;
}

static int lan88xx_suspend(struct phy_device *phydev)
{
	struct lan88xx_priv *priv = phydev->priv;

	/* do not power down PHY when WOL is enabled */
	if (!priv->wolopts)
		genphy_suspend(phydev);

	return 0;
}

static int lan88xx_probe(struct phy_device *phydev)
{
	struct device *dev = &phydev->mdio.dev;
	struct lan88xx_priv *priv;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->wolopts = 0;

	/* these values can be used to identify internal PHY */
	priv->chip_id = phy_read_mmd_indirect(phydev, LAN88XX_MMD3_CHIP_ID, 3);
	priv->chip_rev = phy_read_mmd_indirect(phydev, LAN88XX_MMD3_CHIP_REV,
					       3);

	phydev->priv = priv;

	return 0;
}

static void lan88xx_remove(struct phy_device *phydev)
{
	struct device *dev = &phydev->mdio.dev;
	struct lan88xx_priv *priv = phydev->priv;

	if (priv)
		devm_kfree(dev, priv);
}

static int lan88xx_set_wol(struct phy_device *phydev,
			   struct ethtool_wolinfo *wol)
{
	struct lan88xx_priv *priv = phydev->priv;

	priv->wolopts = wol->wolopts;

	return 0;
}

static int lan87xx_probe(struct phy_device *phydev)
{
	struct device *dev = &phydev->mdio.dev;
	struct lan87xx_priv *priv;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	/* these values can be used to identify internal PHY */
	priv->chip_id = phy_read(phydev, LAN87XX_PHY_ID1);
	priv->chip_rev = phy_read(phydev, LAN87XX_PHY_ID2);

	phydev->priv = priv;

	return 0;
}

static void lan87xx_remove(struct phy_device *phydev)
{
	struct device *dev = &phydev->mdio.dev;
	struct lan87xx_priv *priv = phydev->priv;

	if (priv)
		devm_kfree(dev, priv);
}

static int lan87xx_phy_config_intr(struct phy_device *phydev)
{
	int rc = 0;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED) {
		/* unmask all source and clear them before enable */
		rc = phy_write(phydev, LAN87XX_INTERRUPT_MASK, 0x7FFF);
		rc = phy_read(phydev, LAN87XX_INTERRUPT_SOURCE);
		rc = phy_write(phydev, LAN87XX_INTERRUPT_MASK,
			       LAN87XX_MASK_LINK_UP | LAN87XX_MASK_LINK_DOWN);
	} else {
		rc = phy_write(phydev, LAN87XX_INTERRUPT_MASK, 0);
	}

	return rc < 0 ? rc : 0;
}

static int lan87xx_phy_ack_interrupt(struct phy_device *phydev)
{
	int rc = phy_read(phydev, LAN87XX_INTERRUPT_SOURCE);

	return rc < 0 ? rc : 0;
}

static int lan87xx_phy_config_aneg(struct phy_device *phydev)
{
	/* Fixed speed, let the phy state machine check the link */
	phy_trigger_machine(phydev, 0);
	return 0;
}

static int lan87xx_phy_aneg_done(struct phy_device *phydev)
{
	/* Fixed speed */
	return 1;
}

static int lan87xx_config_init(struct phy_device *phydev)
{
	int rc = 0;

	/* init the PHY */
	rc = lan87xx_phy_init(phydev);
	if (rc < 0)
		return rc;

	/* enable rgmii delays */
	if ((phydev->interface == PHY_INTERFACE_MODE_RGMII) ||
	    (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID) ||
	    (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID) ||
	    (phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID)) {

		/* read the CTRL_1 reg in MISC bank */
		rc = phy_write(phydev, LAN87XX_EXT_REG_CTL,
			       LAN87XX_MASK_READ_CONTROL | LAN87XX_MISC | LAN87XX_CTRL_1);
		rc = phy_read(phydev, LAN87XX_EXT_REG_RD_DATA);
		
		if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID) {
			rc |= (LAN87XX_MASK_RGMII_TXC_DLY_EN |
			       LAN87XX_MASK_RGMII_RXC_DLY_EN);
		}
		else if (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID) {
			rc &= ~LAN87XX_MASK_RGMII_TXC_DLY_EN;
			rc |= LAN87XX_MASK_RGMII_RXC_DLY_EN;
		}
		else if (phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID) {
			rc &= ~LAN87XX_MASK_RGMII_RXC_DLY_EN;
			rc |= LAN87XX_MASK_RGMII_TXC_DLY_EN;
		}
		else {
			rc &= ~(LAN87XX_MASK_RGMII_TXC_DLY_EN |
				LAN87XX_MASK_RGMII_RXC_DLY_EN);
		}
		/* write back to the CTRL_1 reg in MISC bank */
		rc = phy_write(phydev, LAN87XX_EXT_REG_WR_DATA, rc);
		rc = phy_write(phydev, LAN87XX_EXT_REG_CTL,
			       LAN87XX_MASK_WRITE_CONTROL | LAN87XX_MISC | LAN87XX_CTRL_1 );
	}

	/* Always in forced mode. */
	phydev->autoneg = 0;
	phydev->speed = SPEED_100;
	phydev->duplex = DUPLEX_FULL;
	
	rc = genphy_read_status(phydev);

	return rc < 0 ? rc : 0;
}

static struct phy_driver microchip_phy_driver[] = {
{
	.phy_id		= 0x0007c130,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Microchip LAN88xx",

	.features	= (PHY_GBIT_FEATURES |
			   SUPPORTED_Pause | SUPPORTED_Asym_Pause),
	.flags		= PHY_HAS_INTERRUPT | PHY_HAS_MAGICANEG,

	.probe		= lan88xx_probe,
	.remove		= lan88xx_remove,

	.config_init	= genphy_config_init,
	.config_aneg	= genphy_config_aneg,
	.read_status	= genphy_read_status,

	.ack_interrupt	= lan88xx_phy_ack_interrupt,
	.config_intr	= lan88xx_phy_config_intr,

	.suspend	= lan88xx_suspend,
	.resume		= genphy_resume,
	.set_wol	= lan88xx_set_wol,
},
{
	.phy_id		= 0x0007c150,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Microchip LAN87xx",

	.features	= SUPPORTED_100baseT_Full,
	.flags		= PHY_HAS_INTERRUPT | PHY_HAS_MAGICANEG,

	.probe		= lan87xx_probe,
	.remove		= lan87xx_remove,

	.config_init	= lan87xx_config_init,
	.config_aneg	= lan87xx_phy_config_aneg,
	.aneg_done	= lan87xx_phy_aneg_done,
	.read_status	= genphy_read_status,

	.ack_interrupt	= lan87xx_phy_ack_interrupt,
	.config_intr	= lan87xx_phy_config_intr,

	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
}
};

module_phy_driver(microchip_phy_driver);

static struct mdio_device_id __maybe_unused microchip_tbl[] = {
	{ 0x0007c130, 0xfffffff0 },
	{ 0x0007c150, 0xfffffff0 },
	{ }
};

MODULE_DEVICE_TABLE(mdio, microchip_tbl);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
