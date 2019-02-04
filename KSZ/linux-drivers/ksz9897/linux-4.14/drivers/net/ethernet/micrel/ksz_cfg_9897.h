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


#include "ksz_common.h"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.h"

#include "ksz9897.h"
#include "ksz_sw_9897.h"

#endif

