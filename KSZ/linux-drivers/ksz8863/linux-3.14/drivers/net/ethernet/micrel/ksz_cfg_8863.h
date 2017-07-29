/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_8863_H
#define KSZ_CFG_8863_H

#if defined(CONFIG_MICREL_KSZ8863_STP)
/* Support STP. */
#define CONFIG_KSZ_STP
#endif

#ifdef CONFIG_KSZ_STP
#include <../net/bridge/br_private.h>
#endif


#include "ksz_common.h"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.h"

#include "ksz8863.h"
#include "ksz_sw.h"

#endif

