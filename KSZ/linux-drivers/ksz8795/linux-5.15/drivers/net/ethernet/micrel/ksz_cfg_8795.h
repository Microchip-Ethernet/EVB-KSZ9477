/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_8795_H
#define KSZ_CFG_8795_H

#ifdef CONFIG_KSZ_MRP
/* MRP code not implemented yet. */
#undef CONFIG_KSZ_MRP
#undef CONFIG_KSZ_MMRP
#undef CONFIG_KSZ_MVRP
#undef CONFIG_KSZ_MSRP
#endif
/* Can be defined if KSZ9897 driver is included also. */
#undef CONFIG_KSZ_HSR

#ifdef CONFIG_KSZ_DLR
#define MAX_REQUEST_SIZE	80
#endif


#include "ksz_common.h"

#include "ksz_req.h"

#include "ksz8795.h"
#include "ksz_sw_8795.h"

#endif

