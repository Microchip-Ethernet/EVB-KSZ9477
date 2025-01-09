/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_8463_H
#define KSZ_CFG_8463_H

#if defined(CONFIG_KSZ_PTP)
/* Support 1588 PTP. */
#define CONFIG_1588_PTP
#define PTP_SPI
#endif

#ifdef CONFIG_KSZ_MRP
/* MRP code not implemented yet. */
#undef CONFIG_KSZ_MRP
#undef CONFIG_KSZ_MMRP
#undef CONFIG_KSZ_MVRP
#undef CONFIG_KSZ_MSRP
#endif
/* Can be defined if KSZ9897 driver is included also. */
#undef CONFIG_KSZ_DLR
#undef CONFIG_KSZ_HSR

/* KSZ8463 and KSZ8863 use same ksz_sw.c code. */
#undef CONFIG_HAVE_KSZ8863

#if defined(CONFIG_SOC_SAM9X7)
/* Switch interrupt does not work properly in SAM9X75 when starting early. */
#define CONFIG_DELAY_REQUEST_INTR
#endif


#include "ksz_common.h"

#include "ksz_req.h"

#include "ksz846x.h"
#include "ksz8463.h"
#include "ksz_sw.h"

#endif

