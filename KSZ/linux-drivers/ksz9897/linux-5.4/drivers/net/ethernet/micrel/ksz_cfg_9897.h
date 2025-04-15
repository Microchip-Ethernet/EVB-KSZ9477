/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_9897_H
#define KSZ_CFG_9897_H

#if defined(CONFIG_KSZ_PTP)
/* Support 1588 PTP. */
#define CONFIG_1588_PTP
#endif

#if defined(CONFIG_IBA_KSZ9897)
#define CONFIG_KSZ_IBA_ONLY
#endif

#ifdef CONFIG_KSZ_DLR
/* Have ACL to handle beacon timeout. */
#define CONFIG_HAVE_ACL_HW

/* Have DLR to transmit beacons. */
#define CONFIG_HAVE_DLR_HW
#endif

#ifdef CONFIG_KSZ_HSR
#define CONFIG_HAVE_HSR_HW
#define CONFIG_KSZ_HSR_REDBOX
#endif


#include "ksz_common.h"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.h"

#include "ksz9897.h"
#include "ksz_sw_9897.h"

#endif

