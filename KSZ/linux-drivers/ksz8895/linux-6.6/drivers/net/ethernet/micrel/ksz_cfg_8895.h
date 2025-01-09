/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_8895_H
#define KSZ_CFG_8895_H

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

#if defined(CONFIG_SOC_SAM9X7)
/* Switch interrupt does not work properly in SAM9X75 when starting early. */
#define CONFIG_DELAY_REQUEST_INTR
#endif


#include "ksz_common.h"

#include "ksz_req.h"

#include "ksz8895.h"
#include "ksz_sw_8895.h"

#endif

