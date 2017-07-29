/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_8463_H
#define KSZ_CFG_8463_H

#if defined(CONFIG_MICREL_KSZ8463_PTP)
/* Support 1588 PTP. */
#define CONFIG_1588_PTP
#define PTP_SPI
#endif

#if defined(CONFIG_MICREL_KSZ8463_STP)
/* Support STP. */
#define CONFIG_KSZ_STP
#endif

#ifdef CONFIG_KSZ_STP
#include <../net/bridge/br_private.h>
#endif


#include "ksz_common.h"

#include "ksz_req.h"

#include "ks846xReg.h"
#include "ksz8463.h"
#include "ksz_sw.h"

#endif

