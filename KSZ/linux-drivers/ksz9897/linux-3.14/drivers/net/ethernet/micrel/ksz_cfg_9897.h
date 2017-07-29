/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_9897_H
#define KSZ_CFG_9897_H

#if defined(CONFIG_MICREL_KSZ9897_PTP)
/* Support 1588 PTP. */
#define CONFIG_1588_PTP
#define PTP_SPI
#endif

#if defined(CONFIG_MICREL_KSZ9897_STP)
/* Support STP. */
#define CONFIG_KSZ_STP
#endif

#ifdef CONFIG_KSZ_STP
#include <../net/bridge/br_private.h>
#endif


#if 1
/* Support IBA. */
#define KSZ_IBA
#endif

#if 1
/* Support MRP. */
#define KSZ_MRP
#endif

#if 1
/* Support DLR. */
#define KSZ_DLR
#endif


#include "ksz_common.h"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.h"

#include "ksz9897.h"
#include "ksz_sw_9897.h"

#endif

