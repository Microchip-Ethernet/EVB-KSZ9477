/**
 * This file contains shared configurations between the network and switch
 * drivers.
 */


#ifndef KSZ_CFG_8463_H
#define KSZ_CFG_8463_H

#if defined(CONFIG_KSZ_PTP)
/* Support 1588 PTP. */
#define CONFIG_1588_PTP
#define PTP_SPI
#endif


#include "ksz_common.h"

#include "ksz_req.h"

#include "ks846xReg.h"
#include "ksz8463.h"
#include "ksz_sw.h"

#endif

