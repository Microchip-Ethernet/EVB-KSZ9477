/**
 * Microchip KSZ8462 Register Definitions.
 *
 * Copyright (C) 2015 Microchip Technology Inc.
 * Copyright (C) 2010-2015 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *
  ----------------------------------------------------------------------------

  Author  Date      Version  Description
  PCD     03/23/10  0.0.1    Register definition for KS8461/2.
  ----------------------------------------------------------------------------
 */

#ifndef __KS846XREG_h
#define __KS846XREG_h

#include "ks886xReg.h"

/*
 * Trigger Output Registers
 * (Bank 1, Offset 0x200 - 0x398)
 */

#define MAX_GPIO                    12   /* GPIO from 0 ~ 11 */
#define MAX_TRIG_UNIT               12   /* Trigger unit from 0 ~ 11 */
#define MAX_TIMESTAMP_UNIT          12   /* Timestamp unit from 0 ~ 11 */
#define MAX_TIMESTAMP_EVENT_UNIT    8    /* Timestamp event unit from 0 ~ 7 */


#define TRIG_ERROR                 0x200       /* TRIG_ERROR */
#define TRIG_ACTIVE                0x202       /* TRIG_ACTIVE */
#define TRIG_DONE                  0x204       /* TRIG_DONE */
#define TRIG_EN                    0x206       /* TRIG_EN */
#define   TRIG_UNIT_11               (1 << 11)
#define   TRIG_UNIT_10               (1 << 10)
#define   TRIG_UNIT_9                (1 << 9)
#define   TRIG_UNIT_8                (1 << 8)
#define   TRIG_UNIT_7                (1 << 7)
#define   TRIG_UNIT_6                (1 << 6)
#define   TRIG_UNIT_5                (1 << 5)
#define   TRIG_UNIT_4                (1 << 4)
#define   TRIG_UNIT_3                (1 << 3)
#define   TRIG_UNIT_2                (1 << 2)
#define   TRIG_UNIT_1                (1 << 1)
#define   TRIG_UNIT_0                (1 << 0)

#define TRIG_RESET                 0x208       /* TRIG_SR */

#define TRIG_PPS_WS                0x20A       /* TRIG_PPS_WS */
/* +/- 1ns offset from the internal clock transition */
#define   TRIG_ADJUST_1NS            (1 << 11)
/* Trig PULSE_WIDTH multiple mask (only apply to last Trig Unit */
#define   TRIG_PPS_WS_MASK           (0x00FF)


/* TRAG0 */
#define TRIG0_TARGET_NANOSEC_L     0x220       /* TRIG_TARGET_NS */
#define TRIG0_TARGET_NANOSEC_H     0x222       /* TRIG_TARGET_NS */
#define TRIG0_TARGET_SEC_L         0x224       /* TRIG_TARGET_S */
#define TRIG0_TARGET_SEC_H         0x226       /* TRIG_TARGET_S */
#define TRIG0_CONF_1               0x228       /* TRIG_CFG_1 */
/* Enable Trig out cascade mode */
#define   TRIG_CASCADE_EN            (1 << 15)
/* Last unit of Trig out cascade mode */
#define   TRIG_CASCADE_TAIL          (1 << 14)
/* Trig immediate */
#define   TRIG_NOW                   (1 << 9)
/* Enable reporting on TRIG_DONE */
#define   TRIG_NOTIFY                (1 << 8)
/* Select +/- 1ns offset from clock */
#define   TRIG_CLK_OPT               (1 << 7)
/* Cascade unit link to previous unit */
#define   TRIG_CASCADE_UPS_MASK      (0x3c00)

/* negative edge trigger pattern */
#define   TRIG_NEG_EDGE              0
/* positive edge trigger pattern */
#define   TRIG_POS_EDGE              1
/* negative pulse trigger pattern */
#define   TRIG_NEG_PULSE             2
/* positive pulse trigger pattern */
#define   TRIG_POS_PULSE             3
/* negative period trigger pattern */
#define   TRIG_NEG_PERIOD            4
/* positive period trigger pattern */
#define   TRIG_POS_PERIOD            5
/* register value output trigger pattern */
#define   TRIG_REG_OUTPUT            6


#define TRIG0_PULSE_WIDTH          0x22A       /* TRIG_CFG_2 */
#define TRIG0_CYCLE_WIDTH_L        0x22C       /* TRIG_CFG_3 */
#define TRIG0_CYCLE_WIDTH_H        0x22E       /* TRIG_CFG_4 */
#define TRIG0_PER_OCCUR            0x230       /* TRIG_CFG_5 */
#define TRIG0_BIT_PATTERN          0x232       /* TRIG_CFG_6 */
#define TRIG0_ITERATE_TIME_L       0x234       /* TRIG_CFG_7 */
#define TRIG0_ITERATE_TIME_H       0x236       /* TRIG_CFG_8 */

/* TRAG0(N=0) to TRIG11(N=11) */
#define TRIGn_TARGET_NANOSEC_L(N)  (TRIG0_TARGET_NANOSEC_L + (N * 0x20))
#define TRIGn_TARGET_NANOSEC_H(N)  (TRIG0_TARGET_NANOSEC_H + (N * 0x20))
#define TRIGn_TARGET_SEC_L(N)      (TRIG0_TARGET_SEC_L + (N * 0x20))
#define TRIGn_TARGET_SEC_H(N)      (TRIG0_TARGET_SEC_H + (N * 0x20))
#define TRIGn_CONF_1(N)            (TRIG0_CONF_1 + (N * 0x20))
#define TRIGn_PULSE_WIDTH(N)       (TRIG0_PULSE_WIDTH + (N * 0x20))
#define TRIGn_CYCLE_WIDTH_L(N)     (TRIG0_CYCLE_WIDTH_L + (N * 0x20))
#define TRIGn_CYCLE_WIDTH_H(N)     (TRIG0_CYCLE_WIDTH_H + (N * 0x20))
#define TRIGn_PER_OCCUR(N)         (TRIG0_PER_OCCUR + (N * 0x20))
#define TRIGn_BIT_PATTERN(N)       (TRIG0_BIT_PATTERN + (N * 0x20))
#define TRIGn_ITERATE_TIME_L(N)    (TRIG0_ITERATE_TIME_L + (N * 0x20))
#define TRIGn_ITERATE_TIME_H(N)    (TRIG0_ITERATE_TIME_H + (N * 0x20))


/*
 * Time Stamping Event Registers
 * (Bank 2, Offset 0x400 - 0x5FA)
 */

#define TS_STATUS                  0x400       /* TS_RDY */
/* Port2 egress timestamp for xDelay available */
#define   TS_PORT2_OUT_XDELAY        (1 << 15)
/* Port2 egress timestamp for SYNC available */
#define   TS_PORT2_OUT_SYNC          (1 << 14)
/* Port1 egress timestamp for xDelay available */
#define   TS_PORT1_OUT_XDELAY        (1 << 13)
/* Port1 egress timestamp for SYNC available */
#define   TS_PORT1_OUT_SYNC          (1 << 12)
/* Timestamp is ready for read mask */
#define   TS_RDY_MASK                (0x0FFF)

#define TS_ENABLE                  0x402       /* TS_EN */
#define   TS_UNIT_11                 (1 << 11)
#define   TS_UNIT_10                 (1 << 10)
#define   TS_UNIT_9                  (1 << 9)
#define   TS_UNIT_8                  (1 << 8)
#define   TS_UNIT_7                  (1 << 7)
#define   TS_UNIT_6                  (1 << 6)
#define   TS_UNIT_5                  (1 << 5)
#define   TS_UNIT_4                  (1 << 4)
#define   TS_UNIT_3                  (1 << 3)
#define   TS_UNIT_2                  (1 << 2)
#define   TS_UNIT_1                  (1 << 1)
#define   TS_UNIT_0                  (1 << 0)

#define TS_RESET                   0x404       /* TS_SR */

/* TS0 */
#define TS0_EVENT_STATUS           0x420       /* TS_STS */
/* TS detected events overflow */
#define   TS_EVENT_OVERFLOW          (1 << 0)
/* TS has detected number of events */
#define   TS_NO_EVENT_DET_MASK       (0x001E)

#define TS0_CONF                   0x422       /* TS_CFG */
/* TS on whose GPIO mask */
#define   TS_GPIO_MASK               (0x0F00)
/* Enable TS raising edge detection */
#define   TS_DETECT_RISE             (1 << 7)
/* Enable TS falling edge detection */
#define   TS_DETECT_FALL             (1 << 6)
/* Last unit of TS cascade mode */
#define   TS_CASCADE_TAIL            (1 << 5)
/* Enable TS cascade mode */
#define   TS_CASCADE_EN              (1 << 0)
/* Cascade unit link to previous unit */
#define   TS_CASCADE_UPS_MASK        (0x001E)

/* TS0-0 Event Timestamp */
#define TS0_0_EVENT_NANOSEC_L      0x424       /* TS_SMPL_NS */
#define TS0_0_EVENT_NANOSEC_H      0x426       /* TS_SMPL_NS */
/* Cascade unit link to previous unit */
#define   TS_DETECT_FALLING          (1 << 30)
/* 30bits of nanoseconds */
#define   TS_ENEVT_NANOSEC_MASK      (0x3FFFFFFF)

#define TS0_0_EVENT_SEC_L          0x428       /* TS_SMPL_S */
#define TS0_0_EVENT_SEC_H          0x42A       /* TS_SMPL_S */
#define TS0_0_EVENT_SUB_NANOSEC    0x42C       /* TS_SUB    */
/* 3bits of sub nanoseconds (0 ~ 4) * 8ns */
#define   TS_ENEVT_SUB_NANOSEC_MASK  (0x0007)

/* TS0-1 Event Timestamp */
#define TS0_1_EVENT_NANOSEC_L      0x434
#define TS0_1_EVENT_NANOSEC_H      0x436
#define TS0_1_EVENT_SEC_L          0x438
#define TS0_1_EVENT_SEC_H          0x43A
#define TS0_1_EVENT_SUB_NANOSEC    0x43C

/* TS0(N=0) to TS11(N=11) */
#define TSn_EVENT_STATUS(N)        (TS0_EVENT_STATUS + (N * 0x20))
#define TSn_CONF(N)                (TS0_CONF + (N * 0x20))

/* TS0-0(N=0) to TS11-0(N=11) Event Timestamp */
#define TSn_0_EVENT_NANOSEC_L(N)   (TS0_0_EVENT_NANOSEC_L + (N * 0x20))
#define TSn_0_EVENT_NANOSEC_H(N)   (TS0_0_EVENT_NANOSEC_H + (N * 0x20))
#define TSn_0_EVENT_SEC_L(N)       (TS0_0_EVENT_SEC_L + (N * 0x20))
#define TSn_0_EVENT_SEC_H(N)       (TS0_0_EVENT_SEC_H + (N * 0x20))
#define TSn_0_EVENT_SUB_NANOSEC(N) (TS0_0_EVENT_SUB_NANOSEC + (N * 0x20))


/*
 * PTP Clock Registers
 * (Bank 3, Offset 0x600 - 0x690)
 */

#define PTP_CLK_CTRL               0x600       /* PTP_CLK_CTL */
/* Enable adjust RTC from PTP delta clock */
#define   PTP_STEP_TIME              (1 << 6)
/* 1 add PTP delta clock to RTC; 0: subtract */
#define   PTP_STEP_DIR               (1 << 5)
/* Read from RTC */
#define   PTP_READ_RTC               (1 << 4)
/* Load RTC to STC */
#define   PTP_LOAD_TIME              (1 << 3)
/* Enable continuous RTC adjustment */
#define   PTP_CLK_ADJ_ENABLE         (1 << 2)
/* Enable PTP clock */
#define   PTP_CLK_ENABLE             (1 << 1)
/* Reset PTP clock */
#define   PTP_CLK_RESET              (1 << 0)

#define PTP_CLK_CONF               0x602       /* CLK_CFG */

#define PTP_RTC_NANOSEC_L          0x604       /* PTP_RTC_NSL */
#define PTP_RTC_NANOSEC_H          0x606       /* PTP_RTC_NSH */

#define PTP_RTC_SEC_L              0x608       /* PTP_RTC_SL */
#define PTP_RTC_SEC_H              0x60A       /* PTP_RTC_SH */

#define PTP_RTC_SUB_NANOSEC        0x60C       /* PTP_RTC_PHASE */
/* 3bits of sub nanoseconds (0 ~ 4) * 8ns */
#define   PTP_RTC_SUB_NANOSEC_MASK   0x0007

#define PTP_SUBNANOSEC_RATE_L      0x610       /* PTP_SNC_RATEL */
#define PTP_SUBNANOSEC_RATE_H      0x612       /* PTP_SNC_RATEH */
/* 1: Adjust PTP clock by add 4ns; 0:subtract */
#define   PTP_RATE_DIR               (1 << 15)
/* enable temporary adjustment PTP clock */
#define   PTP_TMP_RATE_ENABLE        (1 << 14)


#define PTP_RATE_DURATION_L        0x614       /* PTP_DURL */
#define PTP_RATE_DURATION_H        0x616       /* PTP_DURH */

#define PTP_MSG_CONF1              0x620       /* PTP_MSG_CONF_1 */
/* all the PTP pkts are forward to Port3 */
#define   PTP_FORWARD_TO_PORT3       (1 << 7)
/* Enable PTP function */
#define   PTP_ENABLE                 (1 << 6)
/* Enable detection of Ethernet PTP msg */
#define   PTP_ETH_ENABLE             (1 << 5)
/* Enable detection of ipv4/UDP PTP msg */
#define   PTP_IPV4_UDP_ENABLE        (1 << 4)
/* Enable detection of ipv6/UDP PTP msg */
#define   PTP_IPV6_UDP_ENABLE        (1 << 3)
/* 1: P2P TC; 0: E2E TC */
#define   PTP_TC_P2P                 (1 << 2)
/* 1: master OC; 0: slave OC */
#define   PTP_MASTER                 (1 << 1)
/* 1-step synchronizarion */
#define   PTP_1STEP                  (1 << 0)

#define PTP_MSG_CONF2              0x622       /* PTP_MSG_CONF_2 */
#define   PTP_UNICAST_ENABLE         (1 << 12)
#define   PTP_ALTERNATE_MASTER       (1 << 11)
#define   PTP_ALL_HIGH_PRIORITY      (1 << 10)
/* Enable PTP SYNC assciation check */
#define   PTP_SYNC_CHECK             (1 << 9)
/* Enable PTP delay_req/delay_resp assciation check */
#define   PTP_DELAY_CHECK            (1 << 8)
/* Enable PTP Pdelay_req/Pdelay_resp assciation check */
#define   PTP_PDELAY_CHECK           (1 << 7)
/* drop PTP SYNC/delay_req before BMC is selectedi */
#define   PTP_DROP_SYNC_DELAY_REQ    (1 << 5)
/* Enavle checing PTP domain field before forward to port3 */
#define   PTP_DOMAIN_CHECK           (1 << 4)
/* Enable re-calculate PTP UDP checksum; 0: UDP checksum field is 0 */
#define   PTP_UDP_CHECKSUM           (1 << 2)
/* port1 is connected to master port */
#define   PTP_PORT1_MASTER           (1 << 1)
/* port2 is connected to master port */
#define   PTP_PORT2_MASTER           (1 << 0)

#define PTP_DOMAIN_VERSION         0x624       /* PTP_DOMAIN_VERSION */
/* PTP version number mask */
#define   PTP_VERSION_MASK           (0xFF00)
/* PTP domain vlaue mask */
#define   PTP_DOMAIN_MASK            (0x00FF)

/* PTP_PORT1_RX_LATENCY */
#define PTP_PORT1_RX_MAC2PHY_DELAY     0x640
/* PTP_PORT1_TX_LATENCY */
#define PTP_PORT1_TX_MAC2PHY_DELAY     0x642
/* PTP_PORT1_ASYMMETRY_CORRECTION */
#define PTP_PORT1_ASYM_DELAY           0x644
/* PTP_PORT1_LINK_DELAY */
#define PTP_PORT1_LINK_DELAY           0x646

#define PTP_PORT1_XDELAY_TIMESTAMP_L   0x648
#define PTP_PORT1_XDELAY_TIMESTAMP_H   0x64A

#define PTP_PORT1_SYNC_TIMESTAMP_L     0x64C
#define PTP_PORT1_SYNC_TIMESTAMP_H     0x64E

#define PTP_PORT1_PDRESP_TIMESTAMP_L   0x650
#define PTP_PORT1_PDRESP_TIMESTAMP_H   0x652

#define PTP_PORT2_RX_MAC2PHY_DELAY     (PTP_PORT1_RX_MAC2PHY_DELAY + 0x20)
#define PTP_PORT2_TX_MAC2PHY_DELAY     (PTP_PORT1_TX_MAC2PHY_DELAY + 0x20)
#define PTP_PORT2_ASYM_DELAY           (PTP_PORT1_ASYM_DELAY + 0x20)
#define PTP_PORT2_LINK_DELAY           (PTP_PORT1_LINK_DELAY + 0x20)

#define PTP_PORT2_XDELAY_TIMESTAMP_L   (PTP_PORT1_XDELAY_TIMESTAMP_L + 0x20)
#define PTP_PORT2_XDELAY_TIMESTAMP_H   (PTP_PORT1_XDELAY_TIMESTAMP_H + 0x20)

#define PTP_PORT2_SYNC_TIMESTAMP_L     (PTP_PORT1_SYNC_TIMESTAMP_L + 0x20)
#define PTP_PORT2_SYNC_TIMESTAMP_H     (PTP_PORT1_SYNC_TIMESTAMP_H + 0x20)

#define PTP_PORT2_PDRESP_TIMESTAMP_L   (PTP_PORT1_PDRESP_TIMESTAMP_L + 0x20)
#define PTP_PORT2_PDRESP_TIMESTAMP_H   (PTP_PORT1_PDRESP_TIMESTAMP_H + 0x20)

#define PTP_PORT_INTERVAL(port)		((port) * 0x20)

#define GPIO_MONITOR               0x680
#define GPIO_ENABLE                0x682
/* 0:enable GPIO0 as trigger output; 1:enable GPIO0 as TS input */
#define   GPIO0_DISABLE              (1 << 0)
/* GPIO Output and Monitor mask */
#define   GPIO_MASK                  (0x007F)

#define TRIG_INT_STATUS            0x688       /* TRIG_INTERRUPT_STS */
#define TRIG_INT_ENABLE            0x68A       /* TRIG_INTERRUPT_IE */

#define TS_INT_STATUS              0x68C       /* TS_INTERRUPT_STS */
#define TS_INT_ENABLE              0x68E       /* TS_INTERRUPT_IE */
/* Enable port2 egress xDelay TS interrupt */
#define   TS_PORT2_INT_XDELAY        (1 << 15)
/* Enable port2 egress SYNC TS interrupt */
#define   TS_PORT2_INT_SYNC          (1 << 14)
/* Enable port1 egress xDelay TS interrupt */
#define   TS_PORT1_INT_XDELAY        (1 << 13)
/* Enable port1 egress SYNC TS interrupt */
#define   TS_PORT1_INT_SYNC          (1 << 12)

#define REG_DSP_CTRL_6			0x734
#define COPPER_RECEIVE_ADJUSTMENT	(1 << 13)

#define REG_ANA_CTRL_1			0x748
#define LDO_OFF				(1 << 7)

#define REG_ANA_CTRL_3			0x74C

#endif

/* END */
