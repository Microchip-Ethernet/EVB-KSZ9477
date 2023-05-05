/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_8863_H
#define KSZ_CFG_8863_H

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
#undef CONFIG_HAVE_KSZ8463

#include "ksz_common.h"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.h"

#include "ksz8863.h"
#include "ksz_sw.h"

#endif

