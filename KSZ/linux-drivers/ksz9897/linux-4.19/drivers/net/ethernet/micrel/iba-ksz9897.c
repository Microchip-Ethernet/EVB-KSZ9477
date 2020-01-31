/**
 * Microchip KSZ9897 IBA driver
 *
 * Copyright (c) 2015-2020 Microchip Technology Inc.
 * Copyright (c) 2013-2015 Micrel, Inc.
 *
 * Copyright 2009 Simtec Electronics
 *	http://www.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
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
#define DEBUG_PHY
#define DBG_LINK
#endif
#endif

/* -------------------------------------------------------------------------- */

#include <linux/net_tstamp.h>

#define MAX_REQUEST_SIZE		80

#include "ksz_cfg_9897.h"


#if 1
#define NO_EEE
#endif


#ifdef CONFIG_KSZ_DLR
/* Have ACL to handle beacon timeout. */
#define CONFIG_HAVE_ACL_HW

/* Have DLR to transmit beacons. */
#define CONFIG_HAVE_DLR_HW
#endif

#ifdef CONFIG_KSZ_HSR
#define CONFIG_HAVE_HSR_HW
#endif

#if 0
#define USE_MII_PHY
#endif
#if 0
#define USE_RGMII_PHY
#endif
#if 0
#define USE_MII_MODE
#endif
#if 0
#define USE_GMII_MODE
#endif
#if 0
#define USE_RMII_MODE
#endif
#if 0
#define USE_RGMII_MODE
#endif
#if 0
#define USE_GMII_100_MODE
#endif
#if 0
#define USE_10_MBIT_MODE
#ifndef USE_GMII_100_MODE
#define USE_GMII_100_MODE
#endif
#endif
#if 0
#define USE_HALF_DUPLEX
#endif


#define KS9897MLI_DEV0			"ksz9897"

#define SW_DRV_RELDATE			"Jan 30, 2020"
#define SW_DRV_VERSION			"1.2.3"

/* -------------------------------------------------------------------------- */

#include "ksz_spi_net.h"

#define USE_SHOW_HELP
#include "ksz_common.c"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.c"

/* -------------------------------------------------------------------------- */

#define MIB_READ_INTERVAL		(HZ / 2)

#include "ksz_sw_9897.c"

