/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_8895_H
#define KSZ_CFG_8895_H

#if defined(CONFIG_MICREL_KSZ8895_STP)
/* Support STP. */
#define CONFIG_KSZ_STP
#endif

#ifdef CONFIG_KSZ_STP
#include <../net/bridge/br_private.h>
#endif


#include "ksz_common.h"

#include "ksz8895.h"
#include "ksz_sw_8895.h"

#endif

