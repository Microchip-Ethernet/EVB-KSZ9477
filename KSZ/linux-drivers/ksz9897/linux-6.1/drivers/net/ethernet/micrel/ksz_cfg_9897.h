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
#elif defined(CONFIG_SOC_SAM9X7)
/* Switch interrupt does not work properly in SAM9X75 when starting early. */
#define CONFIG_DELAY_REQUEST_INTR
#endif


#include "ksz_common.h"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.h"

#include "ksz9897.h"
#include "ksz_sw_9897.h"

#endif

