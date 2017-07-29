/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_8795_H
#define KSZ_CFG_8795_H

#if defined(CONFIG_MICREL_KSZ8795_STP)
/* Support STP. */
#define CONFIG_KSZ_STP
#endif

#ifdef CONFIG_KSZ_STP
#include <../net/bridge/br_private.h>
#endif


#if 0
/* Support DLR. */
#define KSZ_DLR
#endif


#include "ksz_common.h"

#include "ksz8795.h"
#include "ksz_sw_8795.h"

#endif

