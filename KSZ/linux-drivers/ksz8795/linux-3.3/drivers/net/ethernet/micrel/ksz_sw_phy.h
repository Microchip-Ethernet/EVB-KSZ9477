/**
 * Micrel switch PHY common header
 *
 * Copyright (c) 2015 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2012-2015 Micrel, Inc.
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


#ifndef KSZ_PHY_H
#define KSZ_PHY_H

#define ADDR_SHIFT			14
#define ADDR_8				1
#define ADDR_16				2
#define ADDR_24				3
#define ADDR_32				4

#define BANK_SHIFT			12

#define PHY_REG(addr, reg)		\
	(((addr) << ADDR_SHIFT) | (reg))

#define PHY_BANK_REG(addr, bank, reg)	\
	(((addr) << ADDR_SHIFT) | ((bank) << BANK_SHIFT) | (reg))

/* Use PHY access if no direct access. */
#ifndef SW_R8
#define SW_R8(s, r)	phy_read(s->phydev, PHY_REG(ADDR_8, r))
#define SW_W8(s, r, v)	phy_write(s->phydev, PHY_REG(ADDR_8, r), v)
#define SW_R16(s, r)	phy_read(s->phydev, PHY_REG(ADDR_16, r))
#define SW_W16(s, r, v)	phy_write(s->phydev, PHY_REG(ADDR_16, r), v)
#define SW_R32(s, r)	phy_read(s->phydev, PHY_REG(ADDR_32, r))
#define SW_W32(s, r, v) \
	do { \
		phy_write(s->phydev, PHY_REG(ADDR_32, (r) + 2), (v) >> 16); \
		phy_write(s->phydev, PHY_REG(ADDR_32, r), v); \
	} while (0)
#define SW_LOCK(s)				\
	do {					\
		mutex_lock(s->hwlock);		\
	} while (0)
#define SW_UNLOCK(s)				\
	do {					\
		mutex_unlock(s->hwlock);	\
	} while (0)
#endif

struct phy_priv {
	int ptp_irq;
	int ptp_using;
	struct ksz_port port;
};

#endif
