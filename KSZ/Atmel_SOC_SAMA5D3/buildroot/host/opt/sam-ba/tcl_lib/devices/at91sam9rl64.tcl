#  ----------------------------------------------------------------------------
#          ATMEL Microcontroller Software Support
#  ----------------------------------------------------------------------------
#  Copyright (c) 2009, Atmel Corporation
#
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of source code must retain the above copyright notice,
#  this list of conditions and the disclaimer below.
#
#  Atmel's name may not be used to endorse or promote products derived from
#  this software without specific prior written permission.
#
#  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
#  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
#  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#  ----------------------------------------------------------------------------
# File Name           : AT91SAM9RL64.tcl
# Object              : AT91SAM9RL64 definitions
# Generated           : AT91 SW Application Group  11/13/2006 (17:21:51)
# 
# CVS Reference       : /AT91SAM9RL64.pl/1.19/Mon Nov 13 16:21:11 2006//
# CVS Reference       : /SYS_SAM9RL64.pl/1.2/Mon Nov 13 16:23:12 2006//
# CVS Reference       : /HMATRIX1_SAM9RL64.pl/1.1/Wed Sep 13 15:29:30 2006//
# CVS Reference       : /CCR_SAM9RL64.pl/1.1/Wed Sep 13 15:29:30 2006//
# CVS Reference       : /PMC_CAP9.pl/1.2/Thu Oct 26 11:26:44 2006//
# CVS Reference       : /EBI_SAM9260.pl/1.1/Fri Sep 30 11:12:14 2005//
# CVS Reference       : /HSDRAMC1_6100A.pl/1.2/Mon Aug 09 09:52:25 2004//
# CVS Reference       : /HSMC3_6105A.pl/1.4/Tue Nov 16 08:16:23 2004//
# CVS Reference       : /HECC_6143A.pl/1.1/Wed Feb 09 16:16:57 2005//
# CVS Reference       : /AIC_6075A.pl/1.1/Mon Jul 12 16:04:01 2004//
# CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb 03 08:02:11 2005//
# CVS Reference       : /DBGU_6059D.pl/1.1/Mon Jan 31 12:54:41 2005//
# CVS Reference       : /PIO_6057A.pl/1.2/Thu Feb 03 09:29:42 2005//
# CVS Reference       : /RSTC_6098A.pl/1.3/Thu Nov 04 12:57:00 2004//
# CVS Reference       : /SHDWC_6122A.pl/1.3/Wed Oct 06 13:16:58 2004//
# CVS Reference       : /RTTC_6081A.pl/1.2/Thu Nov 04 12:57:22 2004//
# CVS Reference       : /PITC_6079A.pl/1.2/Thu Nov 04 12:56:22 2004//
# CVS Reference       : /WDTC_6080A.pl/1.3/Thu Nov 04 12:58:52 2004//
# CVS Reference       : /TC_6082A.pl/1.7/Wed Mar 09 15:31:51 2005//
# CVS Reference       : /MCI_6101E.pl/1.1/Fri Jun 03 12:20:23 2005//
# CVS Reference       : /TWI_6061B.pl/1.2/Tue Sep 12 12:35:28 2006//
# CVS Reference       : /US_6089J.pl/1.2/Wed Oct 11 12:26:02 2006//
# CVS Reference       : /SSC_6078B.pl/1.1/Wed Jul 13 14:25:46 2005//
# CVS Reference       : /SPI_6088D.pl/1.3/Fri May 20 13:23:02 2005//
# CVS Reference       : /AC97C_XXXX.pl/1.3/Tue Feb 22 16:08:27 2005//
# CVS Reference       : /PWM_6044D.pl/1.2/Tue May 10 11:39:09 2005//
# CVS Reference       : /LCDC_6063A.pl/1.3/Fri Dec 09 09:59:26 2005//
# CVS Reference       : /HDMA_SAM9RL64.pl/1.2/Wed Sep 06 15:25:21 2006//
# CVS Reference       : /UDPHS_SAM9265.pl/1.8/Tue Sep 12 12:35:29 2006//
# CVS Reference       : /TSC_XXXX.pl/1.1/Wed Oct 11 13:03:27 2006//
# CVS Reference       : /RTC_1245D.pl/1.3/Fri Sep 17 13:01:31 2004//
# ----------------------------------------------------------------------------


# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR System Peripherals
# *****************************************************************************
# -------- GPBR : (SYS Offset: 0x3d50) GPBR General Purpose Register -------- 
set AT91C_GPBR_GPRV       [expr 0x0 <<  0 ]
# -------- SLCKSEL : (SYS Offset: 0x3d60) Slow Clock Selection Register -------- 
set AT91C_SLCKSEL_RCEN    [expr 0x1 <<  0 ]
set AT91C_SLCKSEL_OSC32EN [expr 0x1 <<  1 ]
set AT91C_SLCKSEL_OSC32BYP [expr 0x1 <<  2 ]
set AT91C_SLCKSEL_OSCSEL  [expr 0x1 <<  3 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR External Bus Interface
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR SDRAM Controller Interface
# *****************************************************************************
# -------- SDRAMC_MR : (SDRAMC Offset: 0x0) SDRAM Controller Mode Register -------- 
set AT91C_SDRAMC_MODE     [expr 0xF <<  0 ]
set 	AT91C_SDRAMC_MODE_NORMAL_CMD           0x0
set 	AT91C_SDRAMC_MODE_NOP_CMD              0x1
set 	AT91C_SDRAMC_MODE_PRCGALL_CMD          0x2
set 	AT91C_SDRAMC_MODE_LMR_CMD              0x3
set 	AT91C_SDRAMC_MODE_RFSH_CMD             0x4
set 	AT91C_SDRAMC_MODE_EXT_LMR_CMD          0x5
set 	AT91C_SDRAMC_MODE_DEEP_CMD             0x6
# -------- SDRAMC_TR : (SDRAMC Offset: 0x4) SDRAMC Refresh Timer Register -------- 
set AT91C_SDRAMC_COUNT    [expr 0xFFF <<  0 ]
# -------- SDRAMC_CR : (SDRAMC Offset: 0x8) SDRAM Configuration Register -------- 
set AT91C_SDRAMC_NC       [expr 0x3 <<  0 ]
set 	AT91C_SDRAMC_NC_8                    0x0
set 	AT91C_SDRAMC_NC_9                    0x1
set 	AT91C_SDRAMC_NC_10                   0x2
set 	AT91C_SDRAMC_NC_11                   0x3
set AT91C_SDRAMC_NR       [expr 0x3 <<  2 ]
set 	AT91C_SDRAMC_NR_11                   [expr 0x0 <<  2 ]
set 	AT91C_SDRAMC_NR_12                   [expr 0x1 <<  2 ]
set 	AT91C_SDRAMC_NR_13                   [expr 0x2 <<  2 ]
set AT91C_SDRAMC_NB       [expr 0x1 <<  4 ]
set 	AT91C_SDRAMC_NB_2_BANKS              [expr 0x0 <<  4 ]
set 	AT91C_SDRAMC_NB_4_BANKS              [expr 0x1 <<  4 ]
set AT91C_SDRAMC_CAS      [expr 0x3 <<  5 ]
set 	AT91C_SDRAMC_CAS_2                    [expr 0x2 <<  5 ]
set 	AT91C_SDRAMC_CAS_3                    [expr 0x3 <<  5 ]
set AT91C_SDRAMC_DBW      [expr 0x1 <<  7 ]
set 	AT91C_SDRAMC_DBW_32_BITS              [expr 0x0 <<  7 ]
set 	AT91C_SDRAMC_DBW_16_BITS              [expr 0x1 <<  7 ]
set AT91C_SDRAMC_TWR      [expr 0xF <<  8 ]
set 	AT91C_SDRAMC_TWR_0                    [expr 0x0 <<  8 ]
set 	AT91C_SDRAMC_TWR_1                    [expr 0x1 <<  8 ]
set 	AT91C_SDRAMC_TWR_2                    [expr 0x2 <<  8 ]
set 	AT91C_SDRAMC_TWR_3                    [expr 0x3 <<  8 ]
set 	AT91C_SDRAMC_TWR_4                    [expr 0x4 <<  8 ]
set 	AT91C_SDRAMC_TWR_5                    [expr 0x5 <<  8 ]
set 	AT91C_SDRAMC_TWR_6                    [expr 0x6 <<  8 ]
set 	AT91C_SDRAMC_TWR_7                    [expr 0x7 <<  8 ]
set 	AT91C_SDRAMC_TWR_8                    [expr 0x8 <<  8 ]
set 	AT91C_SDRAMC_TWR_9                    [expr 0x9 <<  8 ]
set 	AT91C_SDRAMC_TWR_10                   [expr 0xA <<  8 ]
set 	AT91C_SDRAMC_TWR_11                   [expr 0xB <<  8 ]
set 	AT91C_SDRAMC_TWR_12                   [expr 0xC <<  8 ]
set 	AT91C_SDRAMC_TWR_13                   [expr 0xD <<  8 ]
set 	AT91C_SDRAMC_TWR_14                   [expr 0xE <<  8 ]
set 	AT91C_SDRAMC_TWR_15                   [expr 0xF <<  8 ]
set AT91C_SDRAMC_TRC      [expr 0xF << 12 ]
set 	AT91C_SDRAMC_TRC_0                    [expr 0x0 << 12 ]
set 	AT91C_SDRAMC_TRC_1                    [expr 0x1 << 12 ]
set 	AT91C_SDRAMC_TRC_2                    [expr 0x2 << 12 ]
set 	AT91C_SDRAMC_TRC_3                    [expr 0x3 << 12 ]
set 	AT91C_SDRAMC_TRC_4                    [expr 0x4 << 12 ]
set 	AT91C_SDRAMC_TRC_5                    [expr 0x5 << 12 ]
set 	AT91C_SDRAMC_TRC_6                    [expr 0x6 << 12 ]
set 	AT91C_SDRAMC_TRC_7                    [expr 0x7 << 12 ]
set 	AT91C_SDRAMC_TRC_8                    [expr 0x8 << 12 ]
set 	AT91C_SDRAMC_TRC_9                    [expr 0x9 << 12 ]
set 	AT91C_SDRAMC_TRC_10                   [expr 0xA << 12 ]
set 	AT91C_SDRAMC_TRC_11                   [expr 0xB << 12 ]
set 	AT91C_SDRAMC_TRC_12                   [expr 0xC << 12 ]
set 	AT91C_SDRAMC_TRC_13                   [expr 0xD << 12 ]
set 	AT91C_SDRAMC_TRC_14                   [expr 0xE << 12 ]
set 	AT91C_SDRAMC_TRC_15                   [expr 0xF << 12 ]
set AT91C_SDRAMC_TRP      [expr 0xF << 16 ]
set 	AT91C_SDRAMC_TRP_0                    [expr 0x0 << 16 ]
set 	AT91C_SDRAMC_TRP_1                    [expr 0x1 << 16 ]
set 	AT91C_SDRAMC_TRP_2                    [expr 0x2 << 16 ]
set 	AT91C_SDRAMC_TRP_3                    [expr 0x3 << 16 ]
set 	AT91C_SDRAMC_TRP_4                    [expr 0x4 << 16 ]
set 	AT91C_SDRAMC_TRP_5                    [expr 0x5 << 16 ]
set 	AT91C_SDRAMC_TRP_6                    [expr 0x6 << 16 ]
set 	AT91C_SDRAMC_TRP_7                    [expr 0x7 << 16 ]
set 	AT91C_SDRAMC_TRP_8                    [expr 0x8 << 16 ]
set 	AT91C_SDRAMC_TRP_9                    [expr 0x9 << 16 ]
set 	AT91C_SDRAMC_TRP_10                   [expr 0xA << 16 ]
set 	AT91C_SDRAMC_TRP_11                   [expr 0xB << 16 ]
set 	AT91C_SDRAMC_TRP_12                   [expr 0xC << 16 ]
set 	AT91C_SDRAMC_TRP_13                   [expr 0xD << 16 ]
set 	AT91C_SDRAMC_TRP_14                   [expr 0xE << 16 ]
set 	AT91C_SDRAMC_TRP_15                   [expr 0xF << 16 ]
set AT91C_SDRAMC_TRCD     [expr 0xF << 20 ]
set 	AT91C_SDRAMC_TRCD_0                    [expr 0x0 << 20 ]
set 	AT91C_SDRAMC_TRCD_1                    [expr 0x1 << 20 ]
set 	AT91C_SDRAMC_TRCD_2                    [expr 0x2 << 20 ]
set 	AT91C_SDRAMC_TRCD_3                    [expr 0x3 << 20 ]
set 	AT91C_SDRAMC_TRCD_4                    [expr 0x4 << 20 ]
set 	AT91C_SDRAMC_TRCD_5                    [expr 0x5 << 20 ]
set 	AT91C_SDRAMC_TRCD_6                    [expr 0x6 << 20 ]
set 	AT91C_SDRAMC_TRCD_7                    [expr 0x7 << 20 ]
set 	AT91C_SDRAMC_TRCD_8                    [expr 0x8 << 20 ]
set 	AT91C_SDRAMC_TRCD_9                    [expr 0x9 << 20 ]
set 	AT91C_SDRAMC_TRCD_10                   [expr 0xA << 20 ]
set 	AT91C_SDRAMC_TRCD_11                   [expr 0xB << 20 ]
set 	AT91C_SDRAMC_TRCD_12                   [expr 0xC << 20 ]
set 	AT91C_SDRAMC_TRCD_13                   [expr 0xD << 20 ]
set 	AT91C_SDRAMC_TRCD_14                   [expr 0xE << 20 ]
set 	AT91C_SDRAMC_TRCD_15                   [expr 0xF << 20 ]
set AT91C_SDRAMC_TRAS     [expr 0xF << 24 ]
set 	AT91C_SDRAMC_TRAS_0                    [expr 0x0 << 24 ]
set 	AT91C_SDRAMC_TRAS_1                    [expr 0x1 << 24 ]
set 	AT91C_SDRAMC_TRAS_2                    [expr 0x2 << 24 ]
set 	AT91C_SDRAMC_TRAS_3                    [expr 0x3 << 24 ]
set 	AT91C_SDRAMC_TRAS_4                    [expr 0x4 << 24 ]
set 	AT91C_SDRAMC_TRAS_5                    [expr 0x5 << 24 ]
set 	AT91C_SDRAMC_TRAS_6                    [expr 0x6 << 24 ]
set 	AT91C_SDRAMC_TRAS_7                    [expr 0x7 << 24 ]
set 	AT91C_SDRAMC_TRAS_8                    [expr 0x8 << 24 ]
set 	AT91C_SDRAMC_TRAS_9                    [expr 0x9 << 24 ]
set 	AT91C_SDRAMC_TRAS_10                   [expr 0xA << 24 ]
set 	AT91C_SDRAMC_TRAS_11                   [expr 0xB << 24 ]
set 	AT91C_SDRAMC_TRAS_12                   [expr 0xC << 24 ]
set 	AT91C_SDRAMC_TRAS_13                   [expr 0xD << 24 ]
set 	AT91C_SDRAMC_TRAS_14                   [expr 0xE << 24 ]
set 	AT91C_SDRAMC_TRAS_15                   [expr 0xF << 24 ]
set AT91C_SDRAMC_TXSR     [expr 0xF << 28 ]
set 	AT91C_SDRAMC_TXSR_0                    [expr 0x0 << 28 ]
set 	AT91C_SDRAMC_TXSR_1                    [expr 0x1 << 28 ]
set 	AT91C_SDRAMC_TXSR_2                    [expr 0x2 << 28 ]
set 	AT91C_SDRAMC_TXSR_3                    [expr 0x3 << 28 ]
set 	AT91C_SDRAMC_TXSR_4                    [expr 0x4 << 28 ]
set 	AT91C_SDRAMC_TXSR_5                    [expr 0x5 << 28 ]
set 	AT91C_SDRAMC_TXSR_6                    [expr 0x6 << 28 ]
set 	AT91C_SDRAMC_TXSR_7                    [expr 0x7 << 28 ]
set 	AT91C_SDRAMC_TXSR_8                    [expr 0x8 << 28 ]
set 	AT91C_SDRAMC_TXSR_9                    [expr 0x9 << 28 ]
set 	AT91C_SDRAMC_TXSR_10                   [expr 0xA << 28 ]
set 	AT91C_SDRAMC_TXSR_11                   [expr 0xB << 28 ]
set 	AT91C_SDRAMC_TXSR_12                   [expr 0xC << 28 ]
set 	AT91C_SDRAMC_TXSR_13                   [expr 0xD << 28 ]
set 	AT91C_SDRAMC_TXSR_14                   [expr 0xE << 28 ]
set 	AT91C_SDRAMC_TXSR_15                   [expr 0xF << 28 ]
# -------- SDRAMC_HSR : (SDRAMC Offset: 0xc) SDRAM Controller High Speed Register -------- 
set AT91C_SDRAMC_DA       [expr 0x1 <<  0 ]
set 	AT91C_SDRAMC_DA_DISABLE              0x0
set 	AT91C_SDRAMC_DA_ENABLE               0x1
# -------- SDRAMC_LPR : (SDRAMC Offset: 0x10) SDRAM Controller Low-power Register -------- 
set AT91C_SDRAMC_LPCB     [expr 0x3 <<  0 ]
set 	AT91C_SDRAMC_LPCB_DISABLE              0x0
set 	AT91C_SDRAMC_LPCB_SELF_REFRESH         0x1
set 	AT91C_SDRAMC_LPCB_POWER_DOWN           0x2
set 	AT91C_SDRAMC_LPCB_DEEP_POWER_DOWN      0x3
set AT91C_SDRAMC_PASR     [expr 0x7 <<  4 ]
set AT91C_SDRAMC_TCSR     [expr 0x3 <<  8 ]
set AT91C_SDRAMC_DS       [expr 0x3 << 10 ]
set AT91C_SDRAMC_TIMEOUT  [expr 0x3 << 12 ]
set 	AT91C_SDRAMC_TIMEOUT_0_CLK_CYCLES         [expr 0x0 << 12 ]
set 	AT91C_SDRAMC_TIMEOUT_64_CLK_CYCLES        [expr 0x1 << 12 ]
set 	AT91C_SDRAMC_TIMEOUT_128_CLK_CYCLES       [expr 0x2 << 12 ]
# -------- SDRAMC_IER : (SDRAMC Offset: 0x14) SDRAM Controller Interrupt Enable Register -------- 
set AT91C_SDRAMC_RES      [expr 0x1 <<  0 ]
# -------- SDRAMC_IDR : (SDRAMC Offset: 0x18) SDRAM Controller Interrupt Disable Register -------- 
set AT91C_SDRAMC_RES      [expr 0x1 <<  0 ]
# -------- SDRAMC_IMR : (SDRAMC Offset: 0x1c) SDRAM Controller Interrupt Mask Register -------- 
set AT91C_SDRAMC_RES      [expr 0x1 <<  0 ]
# -------- SDRAMC_ISR : (SDRAMC Offset: 0x20) SDRAM Controller Interrupt Status Register -------- 
set AT91C_SDRAMC_RES      [expr 0x1 <<  0 ]
# -------- SDRAMC_MDR : (SDRAMC Offset: 0x24) SDRAM Controller Memory Device Register -------- 
set AT91C_SDRAMC_MD       [expr 0x3 <<  0 ]
set 	AT91C_SDRAMC_MD_SDRAM                0x0
set 	AT91C_SDRAMC_MD_LOW_POWER_SDRAM      0x1

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Static Memory Controller Interface
# *****************************************************************************
# -------- SMC_SETUP : (SMC Offset: 0x0) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x4) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x8) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0xc) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x10) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x14) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x18) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x1c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x20) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x24) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x28) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x2c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x30) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x34) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x38) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x3c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x40) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x44) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x48) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x4c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x50) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x54) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x58) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x5c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x60) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x64) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x68) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x6c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x70) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x74) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x78) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x7c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AHB Matrix Interface
# *****************************************************************************
# -------- MATRIX_MCFG0 : (MATRIX Offset: 0x0) Master Configuration Register rom -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG1 : (MATRIX Offset: 0x4) Master Configuration Register htcm -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG2 : (MATRIX Offset: 0x8) Master Configuration Register gps_tcm -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG3 : (MATRIX Offset: 0xc) Master Configuration Register hperiphs -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG4 : (MATRIX Offset: 0x10) Master Configuration Register ebi0 -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG5 : (MATRIX Offset: 0x14) Master Configuration Register ebi1 -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG6 : (MATRIX Offset: 0x18) Master Configuration Register bridge -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG7 : (MATRIX Offset: 0x1c) Master Configuration Register gps -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG8 : (MATRIX Offset: 0x20) Master Configuration Register gps -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_SCFG0 : (MATRIX Offset: 0x40) Slave Configuration Register 0 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR0 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_LCDC                 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_2DGC                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_ISI                  [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_EMAC                 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_USB                  [expr 0x8 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG1 : (MATRIX Offset: 0x44) Slave Configuration Register 1 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR1 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_LCDC                 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_2DGC                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_ISI                  [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_DMA                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_EMAC                 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_USB                  [expr 0x8 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG2 : (MATRIX Offset: 0x48) Slave Configuration Register 2 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR2 [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR2_DMA                  [expr 0x6 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG3 : (MATRIX Offset: 0x4c) Slave Configuration Register 3 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR3 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_LCDC                 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_2DGC                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_ISI                  [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_DMA                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_EMAC                 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_USB                  [expr 0x8 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG4 : (MATRIX Offset: 0x50) Slave Configuration Register 4 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR4 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_DMA                  [expr 0x6 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG5 : (MATRIX Offset: 0x54) Slave Configuration Register 5 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR5 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_LCDC                 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_2DGC                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_ISI                  [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_DMA                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_EMAC                 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_USB                  [expr 0x8 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG6 : (MATRIX Offset: 0x58) Slave Configuration Register 6 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR6 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_LCDC                 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_2DGC                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_ISI                  [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_DMA                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_EMAC                 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_USB                  [expr 0x8 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG7 : (MATRIX Offset: 0x5c) Slave Configuration Register 7 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR7 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR7_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR7_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR7_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR7_DMA                  [expr 0x6 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_PRAS0 : (MATRIX Offset: 0x80) PRAS0 Register -------- 
set AT91C_MATRIX_M0PR     [expr 0x3 <<  0 ]
set AT91C_MATRIX_M1PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M2PR     [expr 0x3 <<  8 ]
set AT91C_MATRIX_M3PR     [expr 0x3 << 12 ]
set AT91C_MATRIX_M4PR     [expr 0x3 << 16 ]
set AT91C_MATRIX_M5PR     [expr 0x3 << 20 ]
set AT91C_MATRIX_M6PR     [expr 0x3 << 24 ]
set AT91C_MATRIX_M7PR     [expr 0x3 << 28 ]
# -------- MATRIX_PRBS0 : (MATRIX Offset: 0x84) PRBS0 Register -------- 
set AT91C_MATRIX_M8PR     [expr 0x3 <<  0 ]
# -------- MATRIX_PRAS1 : (MATRIX Offset: 0x88) PRAS1 Register -------- 
set AT91C_MATRIX_M0PR     [expr 0x3 <<  0 ]
set AT91C_MATRIX_M1PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M2PR     [expr 0x3 <<  8 ]
set AT91C_MATRIX_M3PR     [expr 0x3 << 12 ]
set AT91C_MATRIX_M4PR     [expr 0x3 << 16 ]
set AT91C_MATRIX_M5PR     [expr 0x3 << 20 ]
set AT91C_MATRIX_M6PR     [expr 0x3 << 24 ]
set AT91C_MATRIX_M7PR     [expr 0x3 << 28 ]
# -------- MATRIX_PRBS1 : (MATRIX Offset: 0x8c) PRBS1 Register -------- 
set AT91C_MATRIX_M8PR     [expr 0x3 <<  0 ]
# -------- MATRIX_PRAS2 : (MATRIX Offset: 0x90) PRAS2 Register -------- 
set AT91C_MATRIX_M0PR     [expr 0x3 <<  0 ]
set AT91C_MATRIX_M1PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M2PR     [expr 0x3 <<  8 ]
set AT91C_MATRIX_M3PR     [expr 0x3 << 12 ]
set AT91C_MATRIX_M4PR     [expr 0x3 << 16 ]
set AT91C_MATRIX_M5PR     [expr 0x3 << 20 ]
set AT91C_MATRIX_M6PR     [expr 0x3 << 24 ]
set AT91C_MATRIX_M7PR     [expr 0x3 << 28 ]
# -------- MATRIX_PRBS2 : (MATRIX Offset: 0x94) PRBS2 Register -------- 
set AT91C_MATRIX_M8PR     [expr 0x3 <<  0 ]
# -------- MATRIX_PRAS3 : (MATRIX Offset: 0x98) PRAS3 Register -------- 
set AT91C_MATRIX_M0PR     [expr 0x3 <<  0 ]
set AT91C_MATRIX_M1PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M2PR     [expr 0x3 <<  8 ]
set AT91C_MATRIX_M3PR     [expr 0x3 << 12 ]
set AT91C_MATRIX_M4PR     [expr 0x3 << 16 ]
set AT91C_MATRIX_M5PR     [expr 0x3 << 20 ]
set AT91C_MATRIX_M6PR     [expr 0x3 << 24 ]
set AT91C_MATRIX_M7PR     [expr 0x3 << 28 ]
# -------- MATRIX_PRBS3 : (MATRIX Offset: 0x9c) PRBS3 Register -------- 
set AT91C_MATRIX_M8PR     [expr 0x3 <<  0 ]
# -------- MATRIX_PRAS4 : (MATRIX Offset: 0xa0) PRAS4 Register -------- 
set AT91C_MATRIX_M0PR     [expr 0x3 <<  0 ]
set AT91C_MATRIX_M1PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M2PR     [expr 0x3 <<  8 ]
set AT91C_MATRIX_M3PR     [expr 0x3 << 12 ]
set AT91C_MATRIX_M4PR     [expr 0x3 << 16 ]
set AT91C_MATRIX_M5PR     [expr 0x3 << 20 ]
set AT91C_MATRIX_M6PR     [expr 0x3 << 24 ]
set AT91C_MATRIX_M7PR     [expr 0x3 << 28 ]
# -------- MATRIX_PRBS4 : (MATRIX Offset: 0xa4) PRBS4 Register -------- 
set AT91C_MATRIX_M8PR     [expr 0x3 <<  0 ]
# -------- MATRIX_PRAS5 : (MATRIX Offset: 0xa8) PRAS5 Register -------- 
set AT91C_MATRIX_M0PR     [expr 0x3 <<  0 ]
set AT91C_MATRIX_M1PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M2PR     [expr 0x3 <<  8 ]
set AT91C_MATRIX_M3PR     [expr 0x3 << 12 ]
set AT91C_MATRIX_M4PR     [expr 0x3 << 16 ]
set AT91C_MATRIX_M5PR     [expr 0x3 << 20 ]
set AT91C_MATRIX_M6PR     [expr 0x3 << 24 ]
set AT91C_MATRIX_M7PR     [expr 0x3 << 28 ]
# -------- MATRIX_PRBS5 : (MATRIX Offset: 0xac) PRBS5 Register -------- 
set AT91C_MATRIX_M8PR     [expr 0x3 <<  0 ]
# -------- MATRIX_PRAS6 : (MATRIX Offset: 0xb0) PRAS6 Register -------- 
set AT91C_MATRIX_M0PR     [expr 0x3 <<  0 ]
set AT91C_MATRIX_M1PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M2PR     [expr 0x3 <<  8 ]
set AT91C_MATRIX_M3PR     [expr 0x3 << 12 ]
set AT91C_MATRIX_M4PR     [expr 0x3 << 16 ]
set AT91C_MATRIX_M5PR     [expr 0x3 << 20 ]
set AT91C_MATRIX_M6PR     [expr 0x3 << 24 ]
set AT91C_MATRIX_M7PR     [expr 0x3 << 28 ]
# -------- MATRIX_PRBS6 : (MATRIX Offset: 0xb4) PRBS6 Register -------- 
set AT91C_MATRIX_M8PR     [expr 0x3 <<  0 ]
# -------- MATRIX_PRAS7 : (MATRIX Offset: 0xb8) PRAS7 Register -------- 
set AT91C_MATRIX_M0PR     [expr 0x3 <<  0 ]
set AT91C_MATRIX_M1PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M2PR     [expr 0x3 <<  8 ]
set AT91C_MATRIX_M3PR     [expr 0x3 << 12 ]
set AT91C_MATRIX_M4PR     [expr 0x3 << 16 ]
set AT91C_MATRIX_M5PR     [expr 0x3 << 20 ]
set AT91C_MATRIX_M6PR     [expr 0x3 << 24 ]
set AT91C_MATRIX_M7PR     [expr 0x3 << 28 ]
# -------- MATRIX_PRBS7 : (MATRIX Offset: 0xbc) PRBS7 Register -------- 
set AT91C_MATRIX_M8PR     [expr 0x3 <<  0 ]
# -------- MATRIX_MRCR : (MATRIX Offset: 0x100) MRCR Register -------- 
set AT91C_MATRIX_RCA926I  [expr 0x1 <<  0 ]
set AT91C_MATRIX_RCA926D  [expr 0x1 <<  1 ]
set AT91C_MATRIX_RCB2     [expr 0x1 <<  2 ]
set AT91C_MATRIX_RCB3     [expr 0x1 <<  3 ]
set AT91C_MATRIX_RCB4     [expr 0x1 <<  4 ]
set AT91C_MATRIX_RCB5     [expr 0x1 <<  5 ]
set AT91C_MATRIX_RCB6     [expr 0x1 <<  6 ]
set AT91C_MATRIX_RCB7     [expr 0x1 <<  7 ]
set AT91C_MATRIX_RCB8     [expr 0x1 <<  8 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AHB CCFG Interface
# *****************************************************************************
# -------- CCFG_TCMR : (CCFG Offset: 0x4) TCM Configuration -------- 
set AT91C_CCFG_ITCM_SIZE  [expr 0xF <<  0 ]
set 	AT91C_CCFG_ITCM_SIZE_0KB                  0x0
set 	AT91C_CCFG_ITCM_SIZE_16KB                 0x5
set 	AT91C_CCFG_ITCM_SIZE_32KB                 0x6
set AT91C_CCFG_DTCM_SIZE  [expr 0xF <<  4 ]
set 	AT91C_CCFG_DTCM_SIZE_0KB                  [expr 0x0 <<  4 ]
set 	AT91C_CCFG_DTCM_SIZE_16KB                 [expr 0x5 <<  4 ]
set 	AT91C_CCFG_DTCM_SIZE_32KB                 [expr 0x6 <<  4 ]
set AT91C_CCFG_RM         [expr 0xF <<  8 ]
# -------- CCFG_UDPHS : (CCFG Offset: 0xc) USB Device HS configuration -------- 
set AT91C_CCFG_DONT_USE_UTMI_LOCK [expr 0x1 <<  0 ]
set 	AT91C_CCFG_DONT_USE_UTMI_LOCK_DONT_USE_LOCK        0x0
# -------- CCFG_EBICSA : (CCFG Offset: 0x10) EBI Chip Select Assignement Register -------- 
set AT91C_EBI_CS1A        [expr 0x1 <<  1 ]
set 	AT91C_EBI_CS1A_SMC                  [expr 0x0 <<  1 ]
set 	AT91C_EBI_CS1A_SDRAMC               [expr 0x1 <<  1 ]
set AT91C_EBI_CS3A        [expr 0x1 <<  3 ]
set 	AT91C_EBI_CS3A_SMC                  [expr 0x0 <<  3 ]
set 	AT91C_EBI_CS3A_SM                   [expr 0x1 <<  3 ]
set AT91C_EBI_CS4A        [expr 0x1 <<  4 ]
set 	AT91C_EBI_CS4A_SMC                  [expr 0x0 <<  4 ]
set 	AT91C_EBI_CS4A_CF                   [expr 0x1 <<  4 ]
set AT91C_EBI_CS5A        [expr 0x1 <<  5 ]
set 	AT91C_EBI_CS5A_SMC                  [expr 0x0 <<  5 ]
set 	AT91C_EBI_CS5A_CF                   [expr 0x1 <<  5 ]
set AT91C_EBI_DBPUC       [expr 0x1 <<  8 ]
set AT91C_EBI_SUPPLY      [expr 0x1 << 16 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
# *****************************************************************************
# -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- 
set AT91C_AIC_PRIOR       [expr 0x7 <<  0 ]
set 	AT91C_AIC_PRIOR_LOWEST               0x0
set 	AT91C_AIC_PRIOR_HIGHEST              0x7
set AT91C_AIC_SRCTYPE     [expr 0x3 <<  5 ]
set 	AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE  [expr 0x0 <<  5 ]
set 	AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED   [expr 0x1 <<  5 ]
set 	AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL       [expr 0x2 <<  5 ]
set 	AT91C_AIC_SRCTYPE_EXT_POSITIVE_EDGE    [expr 0x3 <<  5 ]
# -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- 
set AT91C_AIC_NFIQ        [expr 0x1 <<  0 ]
set AT91C_AIC_NIRQ        [expr 0x1 <<  1 ]
# -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- 
set AT91C_AIC_DCR_PROT    [expr 0x1 <<  0 ]
set AT91C_AIC_DCR_GMSK    [expr 0x1 <<  1 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller
# *****************************************************************************
# -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- 
set AT91C_PDC_RXTEN       [expr 0x1 <<  0 ]
set AT91C_PDC_RXTDIS      [expr 0x1 <<  1 ]
set AT91C_PDC_TXTEN       [expr 0x1 <<  8 ]
set AT91C_PDC_TXTDIS      [expr 0x1 <<  9 ]
# -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- 
set AT91C_PDC_RXTEN       [expr 0x1 <<  0 ]
set AT91C_PDC_TXTEN       [expr 0x1 <<  8 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Debug Unit
# *****************************************************************************
# -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- 
set AT91C_US_RSTRX        [expr 0x1 <<  2 ]
set AT91C_US_RSTTX        [expr 0x1 <<  3 ]
set AT91C_US_RXEN         [expr 0x1 <<  4 ]
set AT91C_US_RXDIS        [expr 0x1 <<  5 ]
set AT91C_US_TXEN         [expr 0x1 <<  6 ]
set AT91C_US_TXDIS        [expr 0x1 <<  7 ]
set AT91C_US_RSTSTA       [expr 0x1 <<  8 ]
# -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- 
set AT91C_US_PAR          [expr 0x7 <<  9 ]
set 	AT91C_US_PAR_EVEN                 [expr 0x0 <<  9 ]
set 	AT91C_US_PAR_ODD                  [expr 0x1 <<  9 ]
set 	AT91C_US_PAR_SPACE                [expr 0x2 <<  9 ]
set 	AT91C_US_PAR_MARK                 [expr 0x3 <<  9 ]
set 	AT91C_US_PAR_NONE                 [expr 0x4 <<  9 ]
set 	AT91C_US_PAR_MULTI_DROP           [expr 0x6 <<  9 ]
set AT91C_US_CHMODE       [expr 0x3 << 14 ]
set 	AT91C_US_CHMODE_NORMAL               [expr 0x0 << 14 ]
set 	AT91C_US_CHMODE_AUTO                 [expr 0x1 << 14 ]
set 	AT91C_US_CHMODE_LOCAL                [expr 0x2 << 14 ]
set 	AT91C_US_CHMODE_REMOTE               [expr 0x3 << 14 ]
# -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_COMM_TX      [expr 0x1 << 30 ]
set AT91C_US_COMM_RX      [expr 0x1 << 31 ]
# -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_COMM_TX      [expr 0x1 << 30 ]
set AT91C_US_COMM_RX      [expr 0x1 << 31 ]
# -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_COMM_TX      [expr 0x1 << 30 ]
set AT91C_US_COMM_RX      [expr 0x1 << 31 ]
# -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_COMM_TX      [expr 0x1 << 30 ]
set AT91C_US_COMM_RX      [expr 0x1 << 31 ]
# -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- 
set AT91C_US_FORCE_NTRST  [expr 0x1 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Parallel Input Output Controler
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Power Management Controler
# *****************************************************************************
# -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_OTG         [expr 0x1 <<  5 ]
set AT91C_PMC_UHP         [expr 0x1 <<  6 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
set AT91C_PMC_PCK3        [expr 0x1 << 11 ]
# -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_OTG         [expr 0x1 <<  5 ]
set AT91C_PMC_UHP         [expr 0x1 <<  6 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
set AT91C_PMC_PCK3        [expr 0x1 << 11 ]
# -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_OTG         [expr 0x1 <<  5 ]
set AT91C_PMC_UHP         [expr 0x1 <<  6 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
set AT91C_PMC_PCK3        [expr 0x1 << 11 ]
# -------- CKGR_UCKR : (PMC Offset: 0x1c) UTMI Clock Configuration Register -------- 
set AT91C_CKGR_UPLLEN     [expr 0x1 << 16 ]
set 	AT91C_CKGR_UPLLEN_DISABLED             [expr 0x0 << 16 ]
set 	AT91C_CKGR_UPLLEN_ENABLED              [expr 0x1 << 16 ]
set AT91C_CKGR_PLLCOUNT   [expr 0xF << 20 ]
set AT91C_CKGR_BIASEN     [expr 0x1 << 24 ]
set 	AT91C_CKGR_BIASEN_DISABLED             [expr 0x0 << 24 ]
set 	AT91C_CKGR_BIASEN_ENABLED              [expr 0x1 << 24 ]
set AT91C_CKGR_BIASCOUNT  [expr 0xF << 28 ]
# -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
set AT91C_CKGR_MOSCEN     [expr 0x1 <<  0 ]
set AT91C_CKGR_OSCBYPASS  [expr 0x1 <<  1 ]
set AT91C_CKGR_OSCOUNT    [expr 0xFF <<  8 ]
# -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLAR : (PMC Offset: 0x28) PLL A Register -------- 
set AT91C_CKGR_DIVA       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVA_0                    0x0
set 	AT91C_CKGR_DIVA_BYPASS               0x1
set AT91C_CKGR_PLLACOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_OUTA       [expr 0x3 << 14 ]
set 	AT91C_CKGR_OUTA_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_OUTA_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_OUTA_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_OUTA_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULA       [expr 0x7FF << 16 ]
set AT91C_CKGR_SRCA       [expr 0x1 << 29 ]
# -------- CKGR_PLLBR : (PMC Offset: 0x2c) PLL B Register -------- 
set AT91C_CKGR_DIVB       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVB_0                    0x0
set 	AT91C_CKGR_DIVB_BYPASS               0x1
set AT91C_CKGR_PLLBCOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_OUTB       [expr 0x3 << 14 ]
set 	AT91C_CKGR_OUTB_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_OUTB_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_OUTB_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_OUTB_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULB       [expr 0x7FF << 16 ]
set AT91C_CKGR_USBDIV     [expr 0x3 << 28 ]
set 	AT91C_CKGR_USBDIV_0                    [expr 0x0 << 28 ]
set 	AT91C_CKGR_USBDIV_1                    [expr 0x1 << 28 ]
set 	AT91C_CKGR_USBDIV_2                    [expr 0x2 << 28 ]
# -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x3 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLLA_CLK             0x2
set 	AT91C_PMC_CSS_PLLB_CLK             0x3
set AT91C_PMC_PRES        [expr 0x7 <<  2 ]
set 	AT91C_PMC_PRES_CLK                  [expr 0x0 <<  2 ]
set 	AT91C_PMC_PRES_CLK_2                [expr 0x1 <<  2 ]
set 	AT91C_PMC_PRES_CLK_4                [expr 0x2 <<  2 ]
set 	AT91C_PMC_PRES_CLK_8                [expr 0x3 <<  2 ]
set 	AT91C_PMC_PRES_CLK_16               [expr 0x4 <<  2 ]
set 	AT91C_PMC_PRES_CLK_32               [expr 0x5 <<  2 ]
set 	AT91C_PMC_PRES_CLK_64               [expr 0x6 <<  2 ]
set AT91C_PMC_MDIV        [expr 0x3 <<  8 ]
set 	AT91C_PMC_MDIV_1                    [expr 0x0 <<  8 ]
set 	AT91C_PMC_MDIV_2                    [expr 0x1 <<  8 ]
set 	AT91C_PMC_MDIV_4                    [expr 0x2 <<  8 ]
# -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x3 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLLA_CLK             0x2
set 	AT91C_PMC_CSS_PLLB_CLK             0x3
set AT91C_PMC_PRES        [expr 0x7 <<  2 ]
set 	AT91C_PMC_PRES_CLK                  [expr 0x0 <<  2 ]
set 	AT91C_PMC_PRES_CLK_2                [expr 0x1 <<  2 ]
set 	AT91C_PMC_PRES_CLK_4                [expr 0x2 <<  2 ]
set 	AT91C_PMC_PRES_CLK_8                [expr 0x3 <<  2 ]
set 	AT91C_PMC_PRES_CLK_16               [expr 0x4 <<  2 ]
set 	AT91C_PMC_PRES_CLK_32               [expr 0x5 <<  2 ]
set 	AT91C_PMC_PRES_CLK_64               [expr 0x6 <<  2 ]
# -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]
# -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]
# -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]
# -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Clock Generator Controler
# *****************************************************************************
# -------- CKGR_UCKR : (CKGR Offset: 0x0) UTMI Clock Configuration Register -------- 
set AT91C_CKGR_UPLLEN     [expr 0x1 << 16 ]
set 	AT91C_CKGR_UPLLEN_DISABLED             [expr 0x0 << 16 ]
set 	AT91C_CKGR_UPLLEN_ENABLED              [expr 0x1 << 16 ]
set AT91C_CKGR_PLLCOUNT   [expr 0xF << 20 ]
set AT91C_CKGR_BIASEN     [expr 0x1 << 24 ]
set 	AT91C_CKGR_BIASEN_DISABLED             [expr 0x0 << 24 ]
set 	AT91C_CKGR_BIASEN_ENABLED              [expr 0x1 << 24 ]
set AT91C_CKGR_BIASCOUNT  [expr 0xF << 28 ]
# -------- CKGR_MOR : (CKGR Offset: 0x4) Main Oscillator Register -------- 
set AT91C_CKGR_MOSCEN     [expr 0x1 <<  0 ]
set AT91C_CKGR_OSCBYPASS  [expr 0x1 <<  1 ]
set AT91C_CKGR_OSCOUNT    [expr 0xFF <<  8 ]
# -------- CKGR_MCFR : (CKGR Offset: 0x8) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLAR : (CKGR Offset: 0xc) PLL A Register -------- 
set AT91C_CKGR_DIVA       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVA_0                    0x0
set 	AT91C_CKGR_DIVA_BYPASS               0x1
set AT91C_CKGR_PLLACOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_OUTA       [expr 0x3 << 14 ]
set 	AT91C_CKGR_OUTA_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_OUTA_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_OUTA_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_OUTA_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULA       [expr 0x7FF << 16 ]
set AT91C_CKGR_SRCA       [expr 0x1 << 29 ]
# -------- CKGR_PLLBR : (CKGR Offset: 0x10) PLL B Register -------- 
set AT91C_CKGR_DIVB       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVB_0                    0x0
set 	AT91C_CKGR_DIVB_BYPASS               0x1
set AT91C_CKGR_PLLBCOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_OUTB       [expr 0x3 << 14 ]
set 	AT91C_CKGR_OUTB_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_OUTB_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_OUTB_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_OUTB_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULB       [expr 0x7FF << 16 ]
set AT91C_CKGR_USBDIV     [expr 0x3 << 28 ]
set 	AT91C_CKGR_USBDIV_0                    [expr 0x0 << 28 ]
set 	AT91C_CKGR_USBDIV_1                    [expr 0x1 << 28 ]
set 	AT91C_CKGR_USBDIV_2                    [expr 0x2 << 28 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Reset Controller Interface
# *****************************************************************************
# -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- 
set AT91C_RSTC_PROCRST    [expr 0x1 <<  0 ]
set AT91C_RSTC_ICERST     [expr 0x1 <<  1 ]
set AT91C_RSTC_PERRST     [expr 0x1 <<  2 ]
set AT91C_RSTC_EXTRST     [expr 0x1 <<  3 ]
set AT91C_RSTC_KEY        [expr 0xFF << 24 ]
# -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- 
set AT91C_RSTC_URSTS      [expr 0x1 <<  0 ]
set AT91C_RSTC_RSTTYP     [expr 0x7 <<  8 ]
set 	AT91C_RSTC_RSTTYP_GENERAL              [expr 0x0 <<  8 ]
set 	AT91C_RSTC_RSTTYP_WAKEUP               [expr 0x1 <<  8 ]
set 	AT91C_RSTC_RSTTYP_WATCHDOG             [expr 0x2 <<  8 ]
set 	AT91C_RSTC_RSTTYP_SOFTWARE             [expr 0x3 <<  8 ]
set 	AT91C_RSTC_RSTTYP_USER                 [expr 0x4 <<  8 ]
set AT91C_RSTC_NRSTL      [expr 0x1 << 16 ]
set AT91C_RSTC_SRCMP      [expr 0x1 << 17 ]
# -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- 
set AT91C_RSTC_URSTEN     [expr 0x1 <<  0 ]
set AT91C_RSTC_URSTIEN    [expr 0x1 <<  4 ]
set AT91C_RSTC_ERSTL      [expr 0xF <<  8 ]
set AT91C_RSTC_KEY        [expr 0xFF << 24 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Shut Down Controller Interface
# *****************************************************************************
# -------- SHDWC_SHCR : (SHDWC Offset: 0x0) Shut Down Control Register -------- 
set AT91C_SHDWC_SHDW      [expr 0x1 <<  0 ]
set AT91C_SHDWC_KEY       [expr 0xFF << 24 ]
# -------- SHDWC_SHMR : (SHDWC Offset: 0x4) Shut Down Mode Register -------- 
set AT91C_SHDWC_WKMODE0   [expr 0x3 <<  0 ]
set 	AT91C_SHDWC_WKMODE0_NONE                 0x0
set 	AT91C_SHDWC_WKMODE0_HIGH                 0x1
set 	AT91C_SHDWC_WKMODE0_LOW                  0x2
set 	AT91C_SHDWC_WKMODE0_ANYLEVEL             0x3
set AT91C_SHDWC_CPTWK0    [expr 0xF <<  4 ]
set AT91C_SHDWC_WKMODE1   [expr 0x3 <<  8 ]
set 	AT91C_SHDWC_WKMODE1_NONE                 [expr 0x0 <<  8 ]
set 	AT91C_SHDWC_WKMODE1_HIGH                 [expr 0x1 <<  8 ]
set 	AT91C_SHDWC_WKMODE1_LOW                  [expr 0x2 <<  8 ]
set 	AT91C_SHDWC_WKMODE1_ANYLEVEL             [expr 0x3 <<  8 ]
set AT91C_SHDWC_CPTWK1    [expr 0xF << 12 ]
set AT91C_SHDWC_RTTWKEN   [expr 0x1 << 16 ]
set AT91C_SHDWC_RTCWKEN   [expr 0x1 << 17 ]
# -------- SHDWC_SHSR : (SHDWC Offset: 0x8) Shut Down Status Register -------- 
set AT91C_SHDWC_WAKEUP0   [expr 0x1 <<  0 ]
set AT91C_SHDWC_WAKEUP1   [expr 0x1 <<  1 ]
set AT91C_SHDWC_FWKUP     [expr 0x1 <<  2 ]
set AT91C_SHDWC_RTTWK     [expr 0x1 << 16 ]
set AT91C_SHDWC_RTCWK     [expr 0x1 << 17 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface
# *****************************************************************************
# -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- 
set AT91C_RTTC_RTPRES     [expr 0xFFFF <<  0 ]
set AT91C_RTTC_ALMIEN     [expr 0x1 << 16 ]
set AT91C_RTTC_RTTINCIEN  [expr 0x1 << 17 ]
set AT91C_RTTC_RTTRST     [expr 0x1 << 18 ]
# -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- 
set AT91C_RTTC_ALMV       [expr 0x0 <<  0 ]
# -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- 
set AT91C_RTTC_CRTV       [expr 0x0 <<  0 ]
# -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- 
set AT91C_RTTC_ALMS       [expr 0x1 <<  0 ]
set AT91C_RTTC_RTTINC     [expr 0x1 <<  1 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface
# *****************************************************************************
# -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- 
set AT91C_PITC_PIV        [expr 0xFFFFF <<  0 ]
set AT91C_PITC_PITEN      [expr 0x1 << 24 ]
set AT91C_PITC_PITIEN     [expr 0x1 << 25 ]
# -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- 
set AT91C_PITC_PITS       [expr 0x1 <<  0 ]
# -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- 
set AT91C_PITC_CPIV       [expr 0xFFFFF <<  0 ]
set AT91C_PITC_PICNT      [expr 0xFFF << 20 ]
# -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- 
set AT91C_PITC_CPIV       [expr 0xFFFFF <<  0 ]
set AT91C_PITC_PICNT      [expr 0xFFF << 20 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface
# *****************************************************************************
# -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- 
set AT91C_WDTC_WDRSTT     [expr 0x1 <<  0 ]
set AT91C_WDTC_KEY        [expr 0xFF << 24 ]
# -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- 
set AT91C_WDTC_WDV        [expr 0xFFF <<  0 ]
set AT91C_WDTC_WDFIEN     [expr 0x1 << 12 ]
set AT91C_WDTC_WDRSTEN    [expr 0x1 << 13 ]
set AT91C_WDTC_WDRPROC    [expr 0x1 << 14 ]
set AT91C_WDTC_WDDIS      [expr 0x1 << 15 ]
set AT91C_WDTC_WDD        [expr 0xFFF << 16 ]
set AT91C_WDTC_WDDBGHLT   [expr 0x1 << 28 ]
set AT91C_WDTC_WDIDLEHLT  [expr 0x1 << 29 ]
# -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- 
set AT91C_WDTC_WDUNF      [expr 0x1 <<  0 ]
set AT91C_WDTC_WDERR      [expr 0x1 <<  1 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Real-time Clock Alarm and Parallel Load Interface
# *****************************************************************************
# -------- RTC_CR : (RTC Offset: 0x0) RTC Control Register -------- 
set AT91C_RTC_UPDTIM      [expr 0x1 <<  0 ]
set AT91C_RTC_UPDCAL      [expr 0x1 <<  1 ]
set AT91C_RTC_TIMEVSEL    [expr 0x3 <<  8 ]
set 	AT91C_RTC_TIMEVSEL_MINUTE               [expr 0x0 <<  8 ]
set 	AT91C_RTC_TIMEVSEL_HOUR                 [expr 0x1 <<  8 ]
set 	AT91C_RTC_TIMEVSEL_DAY24                [expr 0x2 <<  8 ]
set 	AT91C_RTC_TIMEVSEL_DAY12                [expr 0x3 <<  8 ]
set AT91C_RTC_CALEVSEL    [expr 0x3 << 16 ]
set 	AT91C_RTC_CALEVSEL_WEEK                 [expr 0x0 << 16 ]
set 	AT91C_RTC_CALEVSEL_MONTH                [expr 0x1 << 16 ]
set 	AT91C_RTC_CALEVSEL_YEAR                 [expr 0x2 << 16 ]
# -------- RTC_MR : (RTC Offset: 0x4) RTC Mode Register -------- 
set AT91C_RTC_HRMOD       [expr 0x1 <<  0 ]
# -------- RTC_TIMR : (RTC Offset: 0x8) RTC Time Register -------- 
set AT91C_RTC_SEC         [expr 0x7F <<  0 ]
set AT91C_RTC_MIN         [expr 0x7F <<  8 ]
set AT91C_RTC_HOUR        [expr 0x3F << 16 ]
set AT91C_RTC_AMPM        [expr 0x1 << 22 ]
# -------- RTC_CALR : (RTC Offset: 0xc) RTC Calendar Register -------- 
set AT91C_RTC_CENT        [expr 0x3F <<  0 ]
set AT91C_RTC_YEAR        [expr 0xFF <<  8 ]
set AT91C_RTC_MONTH       [expr 0x1F << 16 ]
set AT91C_RTC_DAY         [expr 0x7 << 21 ]
set AT91C_RTC_DATE        [expr 0x3F << 24 ]
# -------- RTC_TIMALR : (RTC Offset: 0x10) RTC Time Alarm Register -------- 
set AT91C_RTC_SEC         [expr 0x7F <<  0 ]
set AT91C_RTC_SECEN       [expr 0x1 <<  7 ]
set AT91C_RTC_MIN         [expr 0x7F <<  8 ]
set AT91C_RTC_MINEN       [expr 0x1 << 15 ]
set AT91C_RTC_HOUR        [expr 0x3F << 16 ]
set AT91C_RTC_AMPM        [expr 0x1 << 22 ]
set AT91C_RTC_HOUREN      [expr 0x1 << 23 ]
# -------- RTC_CALALR : (RTC Offset: 0x14) RTC Calendar Alarm Register -------- 
set AT91C_RTC_MONTH       [expr 0x1F << 16 ]
set AT91C_RTC_MONTHEN     [expr 0x1 << 23 ]
set AT91C_RTC_DATE        [expr 0x3F << 24 ]
set AT91C_RTC_DATEEN      [expr 0x1 << 31 ]
# -------- RTC_SR : (RTC Offset: 0x18) RTC Status Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_SCCR : (RTC Offset: 0x1c) RTC Status Clear Command Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_IER : (RTC Offset: 0x20) RTC Interrupt Enable Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_IDR : (RTC Offset: 0x24) RTC Interrupt Disable Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_IMR : (RTC Offset: 0x28) RTC Interrupt Mask Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_VER : (RTC Offset: 0x2c) RTC Valid Entry Register -------- 
set AT91C_RTC_NVTIM       [expr 0x1 <<  0 ]
set AT91C_RTC_NVCAL       [expr 0x1 <<  1 ]
set AT91C_RTC_NVTIMALR    [expr 0x1 <<  2 ]
set AT91C_RTC_NVCALALR    [expr 0x1 <<  3 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface
# *****************************************************************************
# -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- 
set AT91C_TC_CLKEN        [expr 0x1 <<  0 ]
set AT91C_TC_CLKDIS       [expr 0x1 <<  1 ]
set AT91C_TC_SWTRG        [expr 0x1 <<  2 ]
# -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- 
set AT91C_TC_CLKS         [expr 0x7 <<  0 ]
set 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     0x0
set 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     0x1
set 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     0x2
set 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     0x3
set 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     0x4
set 	AT91C_TC_CLKS_XC0                  0x5
set 	AT91C_TC_CLKS_XC1                  0x6
set 	AT91C_TC_CLKS_XC2                  0x7
set AT91C_TC_CLKS         [expr 0x7 <<  0 ]
set 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     0x0
set 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     0x1
set 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     0x2
set 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     0x3
set 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     0x4
set 	AT91C_TC_CLKS_XC0                  0x5
set 	AT91C_TC_CLKS_XC1                  0x6
set 	AT91C_TC_CLKS_XC2                  0x7
set AT91C_TC_CLKI         [expr 0x1 <<  3 ]
set AT91C_TC_CLKI         [expr 0x1 <<  3 ]
set AT91C_TC_BURST        [expr 0x3 <<  4 ]
set 	AT91C_TC_BURST_NONE                 [expr 0x0 <<  4 ]
set 	AT91C_TC_BURST_XC0                  [expr 0x1 <<  4 ]
set 	AT91C_TC_BURST_XC1                  [expr 0x2 <<  4 ]
set 	AT91C_TC_BURST_XC2                  [expr 0x3 <<  4 ]
set AT91C_TC_BURST        [expr 0x3 <<  4 ]
set 	AT91C_TC_BURST_NONE                 [expr 0x0 <<  4 ]
set 	AT91C_TC_BURST_XC0                  [expr 0x1 <<  4 ]
set 	AT91C_TC_BURST_XC1                  [expr 0x2 <<  4 ]
set 	AT91C_TC_BURST_XC2                  [expr 0x3 <<  4 ]
set AT91C_TC_CPCSTOP      [expr 0x1 <<  6 ]
set AT91C_TC_LDBSTOP      [expr 0x1 <<  6 ]
set AT91C_TC_LDBDIS       [expr 0x1 <<  7 ]
set AT91C_TC_CPCDIS       [expr 0x1 <<  7 ]
set AT91C_TC_ETRGEDG      [expr 0x3 <<  8 ]
set 	AT91C_TC_ETRGEDG_NONE                 [expr 0x0 <<  8 ]
set 	AT91C_TC_ETRGEDG_RISING               [expr 0x1 <<  8 ]
set 	AT91C_TC_ETRGEDG_FALLING              [expr 0x2 <<  8 ]
set 	AT91C_TC_ETRGEDG_BOTH                 [expr 0x3 <<  8 ]
set AT91C_TC_EEVTEDG      [expr 0x3 <<  8 ]
set 	AT91C_TC_EEVTEDG_NONE                 [expr 0x0 <<  8 ]
set 	AT91C_TC_EEVTEDG_RISING               [expr 0x1 <<  8 ]
set 	AT91C_TC_EEVTEDG_FALLING              [expr 0x2 <<  8 ]
set 	AT91C_TC_EEVTEDG_BOTH                 [expr 0x3 <<  8 ]
set AT91C_TC_ABETRG       [expr 0x1 << 10 ]
set AT91C_TC_EEVT         [expr 0x3 << 10 ]
set 	AT91C_TC_EEVT_TIOB                 [expr 0x0 << 10 ]
set 	AT91C_TC_EEVT_XC0                  [expr 0x1 << 10 ]
set 	AT91C_TC_EEVT_XC1                  [expr 0x2 << 10 ]
set 	AT91C_TC_EEVT_XC2                  [expr 0x3 << 10 ]
set AT91C_TC_ENETRG       [expr 0x1 << 12 ]
set AT91C_TC_WAVESEL      [expr 0x3 << 13 ]
set 	AT91C_TC_WAVESEL_UP                   [expr 0x0 << 13 ]
set 	AT91C_TC_WAVESEL_UPDOWN               [expr 0x1 << 13 ]
set 	AT91C_TC_WAVESEL_UP_AUTO              [expr 0x2 << 13 ]
set 	AT91C_TC_WAVESEL_UPDOWN_AUTO          [expr 0x3 << 13 ]
set AT91C_TC_CPCTRG       [expr 0x1 << 14 ]
set AT91C_TC_WAVE         [expr 0x1 << 15 ]
set AT91C_TC_WAVE         [expr 0x1 << 15 ]
set AT91C_TC_LDRA         [expr 0x3 << 16 ]
set 	AT91C_TC_LDRA_NONE                 [expr 0x0 << 16 ]
set 	AT91C_TC_LDRA_RISING               [expr 0x1 << 16 ]
set 	AT91C_TC_LDRA_FALLING              [expr 0x2 << 16 ]
set 	AT91C_TC_LDRA_BOTH                 [expr 0x3 << 16 ]
set AT91C_TC_ACPA         [expr 0x3 << 16 ]
set 	AT91C_TC_ACPA_NONE                 [expr 0x0 << 16 ]
set 	AT91C_TC_ACPA_SET                  [expr 0x1 << 16 ]
set 	AT91C_TC_ACPA_CLEAR                [expr 0x2 << 16 ]
set 	AT91C_TC_ACPA_TOGGLE               [expr 0x3 << 16 ]
set AT91C_TC_LDRB         [expr 0x3 << 18 ]
set 	AT91C_TC_LDRB_NONE                 [expr 0x0 << 18 ]
set 	AT91C_TC_LDRB_RISING               [expr 0x1 << 18 ]
set 	AT91C_TC_LDRB_FALLING              [expr 0x2 << 18 ]
set 	AT91C_TC_LDRB_BOTH                 [expr 0x3 << 18 ]
set AT91C_TC_ACPC         [expr 0x3 << 18 ]
set 	AT91C_TC_ACPC_NONE                 [expr 0x0 << 18 ]
set 	AT91C_TC_ACPC_SET                  [expr 0x1 << 18 ]
set 	AT91C_TC_ACPC_CLEAR                [expr 0x2 << 18 ]
set 	AT91C_TC_ACPC_TOGGLE               [expr 0x3 << 18 ]
set AT91C_TC_AEEVT        [expr 0x3 << 20 ]
set 	AT91C_TC_AEEVT_NONE                 [expr 0x0 << 20 ]
set 	AT91C_TC_AEEVT_SET                  [expr 0x1 << 20 ]
set 	AT91C_TC_AEEVT_CLEAR                [expr 0x2 << 20 ]
set 	AT91C_TC_AEEVT_TOGGLE               [expr 0x3 << 20 ]
set AT91C_TC_ASWTRG       [expr 0x3 << 22 ]
set 	AT91C_TC_ASWTRG_NONE                 [expr 0x0 << 22 ]
set 	AT91C_TC_ASWTRG_SET                  [expr 0x1 << 22 ]
set 	AT91C_TC_ASWTRG_CLEAR                [expr 0x2 << 22 ]
set 	AT91C_TC_ASWTRG_TOGGLE               [expr 0x3 << 22 ]
set AT91C_TC_BCPB         [expr 0x3 << 24 ]
set 	AT91C_TC_BCPB_NONE                 [expr 0x0 << 24 ]
set 	AT91C_TC_BCPB_SET                  [expr 0x1 << 24 ]
set 	AT91C_TC_BCPB_CLEAR                [expr 0x2 << 24 ]
set 	AT91C_TC_BCPB_TOGGLE               [expr 0x3 << 24 ]
set AT91C_TC_BCPC         [expr 0x3 << 26 ]
set 	AT91C_TC_BCPC_NONE                 [expr 0x0 << 26 ]
set 	AT91C_TC_BCPC_SET                  [expr 0x1 << 26 ]
set 	AT91C_TC_BCPC_CLEAR                [expr 0x2 << 26 ]
set 	AT91C_TC_BCPC_TOGGLE               [expr 0x3 << 26 ]
set AT91C_TC_BEEVT        [expr 0x3 << 28 ]
set 	AT91C_TC_BEEVT_NONE                 [expr 0x0 << 28 ]
set 	AT91C_TC_BEEVT_SET                  [expr 0x1 << 28 ]
set 	AT91C_TC_BEEVT_CLEAR                [expr 0x2 << 28 ]
set 	AT91C_TC_BEEVT_TOGGLE               [expr 0x3 << 28 ]
set AT91C_TC_BSWTRG       [expr 0x3 << 30 ]
set 	AT91C_TC_BSWTRG_NONE                 [expr 0x0 << 30 ]
set 	AT91C_TC_BSWTRG_SET                  [expr 0x1 << 30 ]
set 	AT91C_TC_BSWTRG_CLEAR                [expr 0x2 << 30 ]
set 	AT91C_TC_BSWTRG_TOGGLE               [expr 0x3 << 30 ]
# -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- 
set AT91C_TC_COVFS        [expr 0x1 <<  0 ]
set AT91C_TC_LOVRS        [expr 0x1 <<  1 ]
set AT91C_TC_CPAS         [expr 0x1 <<  2 ]
set AT91C_TC_CPBS         [expr 0x1 <<  3 ]
set AT91C_TC_CPCS         [expr 0x1 <<  4 ]
set AT91C_TC_LDRAS        [expr 0x1 <<  5 ]
set AT91C_TC_LDRBS        [expr 0x1 <<  6 ]
set AT91C_TC_ETRGS        [expr 0x1 <<  7 ]
set AT91C_TC_CLKSTA       [expr 0x1 << 16 ]
set AT91C_TC_MTIOA        [expr 0x1 << 17 ]
set AT91C_TC_MTIOB        [expr 0x1 << 18 ]
# -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- 
set AT91C_TC_COVFS        [expr 0x1 <<  0 ]
set AT91C_TC_LOVRS        [expr 0x1 <<  1 ]
set AT91C_TC_CPAS         [expr 0x1 <<  2 ]
set AT91C_TC_CPBS         [expr 0x1 <<  3 ]
set AT91C_TC_CPCS         [expr 0x1 <<  4 ]
set AT91C_TC_LDRAS        [expr 0x1 <<  5 ]
set AT91C_TC_LDRBS        [expr 0x1 <<  6 ]
set AT91C_TC_ETRGS        [expr 0x1 <<  7 ]
# -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- 
set AT91C_TC_COVFS        [expr 0x1 <<  0 ]
set AT91C_TC_LOVRS        [expr 0x1 <<  1 ]
set AT91C_TC_CPAS         [expr 0x1 <<  2 ]
set AT91C_TC_CPBS         [expr 0x1 <<  3 ]
set AT91C_TC_CPCS         [expr 0x1 <<  4 ]
set AT91C_TC_LDRAS        [expr 0x1 <<  5 ]
set AT91C_TC_LDRBS        [expr 0x1 <<  6 ]
set AT91C_TC_ETRGS        [expr 0x1 <<  7 ]
# -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- 
set AT91C_TC_COVFS        [expr 0x1 <<  0 ]
set AT91C_TC_LOVRS        [expr 0x1 <<  1 ]
set AT91C_TC_CPAS         [expr 0x1 <<  2 ]
set AT91C_TC_CPBS         [expr 0x1 <<  3 ]
set AT91C_TC_CPCS         [expr 0x1 <<  4 ]
set AT91C_TC_LDRAS        [expr 0x1 <<  5 ]
set AT91C_TC_LDRBS        [expr 0x1 <<  6 ]
set AT91C_TC_ETRGS        [expr 0x1 <<  7 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Timer Counter Interface
# *****************************************************************************
# -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- 
set AT91C_TCB_SYNC        [expr 0x1 <<  0 ]
# -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- 
set AT91C_TCB_TC0XC0S     [expr 0x3 <<  0 ]
set 	AT91C_TCB_TC0XC0S_TCLK0                0x0
set 	AT91C_TCB_TC0XC0S_NONE                 0x1
set 	AT91C_TCB_TC0XC0S_TIOA1                0x2
set 	AT91C_TCB_TC0XC0S_TIOA2                0x3
set AT91C_TCB_TC1XC1S     [expr 0x3 <<  2 ]
set 	AT91C_TCB_TC1XC1S_TCLK1                [expr 0x0 <<  2 ]
set 	AT91C_TCB_TC1XC1S_NONE                 [expr 0x1 <<  2 ]
set 	AT91C_TCB_TC1XC1S_TIOA0                [expr 0x2 <<  2 ]
set 	AT91C_TCB_TC1XC1S_TIOA2                [expr 0x3 <<  2 ]
set AT91C_TCB_TC2XC2S     [expr 0x3 <<  4 ]
set 	AT91C_TCB_TC2XC2S_TCLK2                [expr 0x0 <<  4 ]
set 	AT91C_TCB_TC2XC2S_NONE                 [expr 0x1 <<  4 ]
set 	AT91C_TCB_TC2XC2S_TIOA0                [expr 0x2 <<  4 ]
set 	AT91C_TCB_TC2XC2S_TIOA1                [expr 0x3 <<  4 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Multimedia Card Interface
# *****************************************************************************
# -------- MCI_CR : (MCI Offset: 0x0) MCI Control Register -------- 
set AT91C_MCI_MCIEN       [expr 0x1 <<  0 ]
set AT91C_MCI_MCIDIS      [expr 0x1 <<  1 ]
set AT91C_MCI_PWSEN       [expr 0x1 <<  2 ]
set AT91C_MCI_PWSDIS      [expr 0x1 <<  3 ]
set AT91C_MCI_SWRST       [expr 0x1 <<  7 ]
# -------- MCI_MR : (MCI Offset: 0x4) MCI Mode Register -------- 
set AT91C_MCI_CLKDIV      [expr 0xFF <<  0 ]
set AT91C_MCI_PWSDIV      [expr 0x7 <<  8 ]
set AT91C_MCI_RDPROOF     [expr 0x1 << 11 ]
set AT91C_MCI_WRPROOF     [expr 0x1 << 12 ]
set AT91C_MCI_PDCFBYTE    [expr 0x1 << 13 ]
set AT91C_MCI_PDCPADV     [expr 0x1 << 14 ]
set AT91C_MCI_PDCMODE     [expr 0x1 << 15 ]
set AT91C_MCI_BLKLEN      [expr 0xFFFF << 16 ]
# -------- MCI_DTOR : (MCI Offset: 0x8) MCI Data Timeout Register -------- 
set AT91C_MCI_DTOCYC      [expr 0xF <<  0 ]
set AT91C_MCI_DTOMUL      [expr 0x7 <<  4 ]
set 	AT91C_MCI_DTOMUL_1                    [expr 0x0 <<  4 ]
set 	AT91C_MCI_DTOMUL_16                   [expr 0x1 <<  4 ]
set 	AT91C_MCI_DTOMUL_128                  [expr 0x2 <<  4 ]
set 	AT91C_MCI_DTOMUL_256                  [expr 0x3 <<  4 ]
set 	AT91C_MCI_DTOMUL_1024                 [expr 0x4 <<  4 ]
set 	AT91C_MCI_DTOMUL_4096                 [expr 0x5 <<  4 ]
set 	AT91C_MCI_DTOMUL_65536                [expr 0x6 <<  4 ]
set 	AT91C_MCI_DTOMUL_1048576              [expr 0x7 <<  4 ]
# -------- MCI_SDCR : (MCI Offset: 0xc) MCI SD Card Register -------- 
set AT91C_MCI_SCDSEL      [expr 0x3 <<  0 ]
set AT91C_MCI_SCDBUS      [expr 0x1 <<  7 ]
# -------- MCI_CMDR : (MCI Offset: 0x14) MCI Command Register -------- 
set AT91C_MCI_CMDNB       [expr 0x3F <<  0 ]
set AT91C_MCI_RSPTYP      [expr 0x3 <<  6 ]
set 	AT91C_MCI_RSPTYP_NO                   [expr 0x0 <<  6 ]
set 	AT91C_MCI_RSPTYP_48                   [expr 0x1 <<  6 ]
set 	AT91C_MCI_RSPTYP_136                  [expr 0x2 <<  6 ]
set AT91C_MCI_SPCMD       [expr 0x7 <<  8 ]
set 	AT91C_MCI_SPCMD_NONE                 [expr 0x0 <<  8 ]
set 	AT91C_MCI_SPCMD_INIT                 [expr 0x1 <<  8 ]
set 	AT91C_MCI_SPCMD_SYNC                 [expr 0x2 <<  8 ]
set 	AT91C_MCI_SPCMD_IT_CMD               [expr 0x4 <<  8 ]
set 	AT91C_MCI_SPCMD_IT_REP               [expr 0x5 <<  8 ]
set AT91C_MCI_OPDCMD      [expr 0x1 << 11 ]
set AT91C_MCI_MAXLAT      [expr 0x1 << 12 ]
set AT91C_MCI_TRCMD       [expr 0x3 << 16 ]
set 	AT91C_MCI_TRCMD_NO                   [expr 0x0 << 16 ]
set 	AT91C_MCI_TRCMD_START                [expr 0x1 << 16 ]
set 	AT91C_MCI_TRCMD_STOP                 [expr 0x2 << 16 ]
set AT91C_MCI_TRDIR       [expr 0x1 << 18 ]
set AT91C_MCI_TRTYP       [expr 0x7 << 19 ]
set 	AT91C_MCI_TRTYP_BLOCK                [expr 0x0 << 19 ]
set 	AT91C_MCI_TRTYP_MULTIPLE             [expr 0x1 << 19 ]
set 	AT91C_MCI_TRTYP_STREAM               [expr 0x2 << 19 ]
set 	AT91C_MCI_TRTYP_SDIO_BYTE            [expr 0x4 << 19 ]
set 	AT91C_MCI_TRTYP_SDIO_BLOCK           [expr 0x5 << 19 ]
set AT91C_MCI_IOSPCMD     [expr 0x3 << 24 ]
set 	AT91C_MCI_IOSPCMD_NONE                 [expr 0x0 << 24 ]
set 	AT91C_MCI_IOSPCMD_SUSPEND              [expr 0x1 << 24 ]
set 	AT91C_MCI_IOSPCMD_RESUME               [expr 0x2 << 24 ]
# -------- MCI_BLKR : (MCI Offset: 0x18) MCI Block Register -------- 
set AT91C_MCI_BCNT        [expr 0xFFFF <<  0 ]
set AT91C_MCI_BLKLEN      [expr 0xFFFF << 16 ]
# -------- MCI_SR : (MCI Offset: 0x40) MCI Status Register -------- 
set AT91C_MCI_CMDRDY      [expr 0x1 <<  0 ]
set AT91C_MCI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_MCI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_MCI_BLKE        [expr 0x1 <<  3 ]
set AT91C_MCI_DTIP        [expr 0x1 <<  4 ]
set AT91C_MCI_NOTBUSY     [expr 0x1 <<  5 ]
set AT91C_MCI_ENDRX       [expr 0x1 <<  6 ]
set AT91C_MCI_ENDTX       [expr 0x1 <<  7 ]
set AT91C_MCI_SDIOIRQA    [expr 0x1 <<  8 ]
set AT91C_MCI_SDIOIRQB    [expr 0x1 <<  9 ]
set AT91C_MCI_SDIOIRQC    [expr 0x1 << 10 ]
set AT91C_MCI_SDIOIRQD    [expr 0x1 << 11 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_OVRE        [expr 0x1 << 30 ]
set AT91C_MCI_UNRE        [expr 0x1 << 31 ]
# -------- MCI_IER : (MCI Offset: 0x44) MCI Interrupt Enable Register -------- 
set AT91C_MCI_CMDRDY      [expr 0x1 <<  0 ]
set AT91C_MCI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_MCI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_MCI_BLKE        [expr 0x1 <<  3 ]
set AT91C_MCI_DTIP        [expr 0x1 <<  4 ]
set AT91C_MCI_NOTBUSY     [expr 0x1 <<  5 ]
set AT91C_MCI_ENDRX       [expr 0x1 <<  6 ]
set AT91C_MCI_ENDTX       [expr 0x1 <<  7 ]
set AT91C_MCI_SDIOIRQA    [expr 0x1 <<  8 ]
set AT91C_MCI_SDIOIRQB    [expr 0x1 <<  9 ]
set AT91C_MCI_SDIOIRQC    [expr 0x1 << 10 ]
set AT91C_MCI_SDIOIRQD    [expr 0x1 << 11 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_OVRE        [expr 0x1 << 30 ]
set AT91C_MCI_UNRE        [expr 0x1 << 31 ]
# -------- MCI_IDR : (MCI Offset: 0x48) MCI Interrupt Disable Register -------- 
set AT91C_MCI_CMDRDY      [expr 0x1 <<  0 ]
set AT91C_MCI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_MCI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_MCI_BLKE        [expr 0x1 <<  3 ]
set AT91C_MCI_DTIP        [expr 0x1 <<  4 ]
set AT91C_MCI_NOTBUSY     [expr 0x1 <<  5 ]
set AT91C_MCI_ENDRX       [expr 0x1 <<  6 ]
set AT91C_MCI_ENDTX       [expr 0x1 <<  7 ]
set AT91C_MCI_SDIOIRQA    [expr 0x1 <<  8 ]
set AT91C_MCI_SDIOIRQB    [expr 0x1 <<  9 ]
set AT91C_MCI_SDIOIRQC    [expr 0x1 << 10 ]
set AT91C_MCI_SDIOIRQD    [expr 0x1 << 11 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_OVRE        [expr 0x1 << 30 ]
set AT91C_MCI_UNRE        [expr 0x1 << 31 ]
# -------- MCI_IMR : (MCI Offset: 0x4c) MCI Interrupt Mask Register -------- 
set AT91C_MCI_CMDRDY      [expr 0x1 <<  0 ]
set AT91C_MCI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_MCI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_MCI_BLKE        [expr 0x1 <<  3 ]
set AT91C_MCI_DTIP        [expr 0x1 <<  4 ]
set AT91C_MCI_NOTBUSY     [expr 0x1 <<  5 ]
set AT91C_MCI_ENDRX       [expr 0x1 <<  6 ]
set AT91C_MCI_ENDTX       [expr 0x1 <<  7 ]
set AT91C_MCI_SDIOIRQA    [expr 0x1 <<  8 ]
set AT91C_MCI_SDIOIRQB    [expr 0x1 <<  9 ]
set AT91C_MCI_SDIOIRQC    [expr 0x1 << 10 ]
set AT91C_MCI_SDIOIRQD    [expr 0x1 << 11 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_OVRE        [expr 0x1 << 30 ]
set AT91C_MCI_UNRE        [expr 0x1 << 31 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Two-wire Interface
# *****************************************************************************
# -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- 
set AT91C_TWI_START       [expr 0x1 <<  0 ]
set AT91C_TWI_STOP        [expr 0x1 <<  1 ]
set AT91C_TWI_MSEN        [expr 0x1 <<  2 ]
set AT91C_TWI_MSDIS       [expr 0x1 <<  3 ]
set AT91C_TWI_SVEN        [expr 0x1 <<  4 ]
set AT91C_TWI_SVDIS       [expr 0x1 <<  5 ]
set AT91C_TWI_SWRST       [expr 0x1 <<  7 ]
# -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- 
set AT91C_TWI_IADRSZ      [expr 0x3 <<  8 ]
set 	AT91C_TWI_IADRSZ_NO                   [expr 0x0 <<  8 ]
set 	AT91C_TWI_IADRSZ_1_BYTE               [expr 0x1 <<  8 ]
set 	AT91C_TWI_IADRSZ_2_BYTE               [expr 0x2 <<  8 ]
set 	AT91C_TWI_IADRSZ_3_BYTE               [expr 0x3 <<  8 ]
set AT91C_TWI_MREAD       [expr 0x1 << 12 ]
set AT91C_TWI_DADR        [expr 0x7F << 16 ]
# -------- TWI_SMR : (TWI Offset: 0x8) TWI Slave Mode Register -------- 
set AT91C_TWI_SADR        [expr 0x7F << 16 ]
# -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- 
set AT91C_TWI_CLDIV       [expr 0xFF <<  0 ]
set AT91C_TWI_CHDIV       [expr 0xFF <<  8 ]
set AT91C_TWI_CKDIV       [expr 0x7 << 16 ]
# -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- 
set AT91C_TWI_TXCOMP_SLAVE [expr 0x1 <<  0 ]
set AT91C_TWI_TXCOMP_MASTER [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY_MASTER [expr 0x1 <<  2 ]
set AT91C_TWI_TXRDY_SLAVE [expr 0x1 <<  2 ]
set AT91C_TWI_SVREAD      [expr 0x1 <<  3 ]
set AT91C_TWI_SVACC       [expr 0x1 <<  4 ]
set AT91C_TWI_GACC        [expr 0x1 <<  5 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_ARBLST_MULTI_MASTER [expr 0x1 <<  9 ]
set AT91C_TWI_SCLWS       [expr 0x1 << 10 ]
set AT91C_TWI_EOSACC      [expr 0x1 << 11 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
# -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- 
set AT91C_TWI_TXCOMP_SLAVE [expr 0x1 <<  0 ]
set AT91C_TWI_TXCOMP_MASTER [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY_MASTER [expr 0x1 <<  2 ]
set AT91C_TWI_TXRDY_SLAVE [expr 0x1 <<  2 ]
set AT91C_TWI_SVREAD      [expr 0x1 <<  3 ]
set AT91C_TWI_SVACC       [expr 0x1 <<  4 ]
set AT91C_TWI_GACC        [expr 0x1 <<  5 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_ARBLST_MULTI_MASTER [expr 0x1 <<  9 ]
set AT91C_TWI_SCLWS       [expr 0x1 << 10 ]
set AT91C_TWI_EOSACC      [expr 0x1 << 11 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
# -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- 
set AT91C_TWI_TXCOMP_SLAVE [expr 0x1 <<  0 ]
set AT91C_TWI_TXCOMP_MASTER [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY_MASTER [expr 0x1 <<  2 ]
set AT91C_TWI_TXRDY_SLAVE [expr 0x1 <<  2 ]
set AT91C_TWI_SVREAD      [expr 0x1 <<  3 ]
set AT91C_TWI_SVACC       [expr 0x1 <<  4 ]
set AT91C_TWI_GACC        [expr 0x1 <<  5 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_ARBLST_MULTI_MASTER [expr 0x1 <<  9 ]
set AT91C_TWI_SCLWS       [expr 0x1 << 10 ]
set AT91C_TWI_EOSACC      [expr 0x1 << 11 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
# -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- 
set AT91C_TWI_TXCOMP_SLAVE [expr 0x1 <<  0 ]
set AT91C_TWI_TXCOMP_MASTER [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY_MASTER [expr 0x1 <<  2 ]
set AT91C_TWI_TXRDY_SLAVE [expr 0x1 <<  2 ]
set AT91C_TWI_SVREAD      [expr 0x1 <<  3 ]
set AT91C_TWI_SVACC       [expr 0x1 <<  4 ]
set AT91C_TWI_GACC        [expr 0x1 <<  5 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_ARBLST_MULTI_MASTER [expr 0x1 <<  9 ]
set AT91C_TWI_SCLWS       [expr 0x1 << 10 ]
set AT91C_TWI_EOSACC      [expr 0x1 << 11 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Usart
# *****************************************************************************
# -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- 
set AT91C_US_RSTRX        [expr 0x1 <<  2 ]
set AT91C_US_RSTTX        [expr 0x1 <<  3 ]
set AT91C_US_RXEN         [expr 0x1 <<  4 ]
set AT91C_US_RXDIS        [expr 0x1 <<  5 ]
set AT91C_US_TXEN         [expr 0x1 <<  6 ]
set AT91C_US_TXDIS        [expr 0x1 <<  7 ]
set AT91C_US_RSTSTA       [expr 0x1 <<  8 ]
set AT91C_US_STTBRK       [expr 0x1 <<  9 ]
set AT91C_US_STPBRK       [expr 0x1 << 10 ]
set AT91C_US_STTTO        [expr 0x1 << 11 ]
set AT91C_US_SENDA        [expr 0x1 << 12 ]
set AT91C_US_RSTIT        [expr 0x1 << 13 ]
set AT91C_US_RSTNACK      [expr 0x1 << 14 ]
set AT91C_US_RETTO        [expr 0x1 << 15 ]
set AT91C_US_DTREN        [expr 0x1 << 16 ]
set AT91C_US_DTRDIS       [expr 0x1 << 17 ]
set AT91C_US_RTSEN        [expr 0x1 << 18 ]
set AT91C_US_RTSDIS       [expr 0x1 << 19 ]
# -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- 
set AT91C_US_USMODE       [expr 0xF <<  0 ]
set 	AT91C_US_USMODE_NORMAL               0x0
set 	AT91C_US_USMODE_RS485                0x1
set 	AT91C_US_USMODE_HWHSH                0x2
set 	AT91C_US_USMODE_MODEM                0x3
set 	AT91C_US_USMODE_ISO7816_0            0x4
set 	AT91C_US_USMODE_ISO7816_1            0x6
set 	AT91C_US_USMODE_IRDA                 0x8
set 	AT91C_US_USMODE_SWHSH                0xC
set AT91C_US_CLKS         [expr 0x3 <<  4 ]
set 	AT91C_US_CLKS_CLOCK                [expr 0x0 <<  4 ]
set 	AT91C_US_CLKS_FDIV1                [expr 0x1 <<  4 ]
set 	AT91C_US_CLKS_SLOW                 [expr 0x2 <<  4 ]
set 	AT91C_US_CLKS_EXT                  [expr 0x3 <<  4 ]
set AT91C_US_CHRL         [expr 0x3 <<  6 ]
set 	AT91C_US_CHRL_5_BITS               [expr 0x0 <<  6 ]
set 	AT91C_US_CHRL_6_BITS               [expr 0x1 <<  6 ]
set 	AT91C_US_CHRL_7_BITS               [expr 0x2 <<  6 ]
set 	AT91C_US_CHRL_8_BITS               [expr 0x3 <<  6 ]
set AT91C_US_SYNC         [expr 0x1 <<  8 ]
set AT91C_US_PAR          [expr 0x7 <<  9 ]
set 	AT91C_US_PAR_EVEN                 [expr 0x0 <<  9 ]
set 	AT91C_US_PAR_ODD                  [expr 0x1 <<  9 ]
set 	AT91C_US_PAR_SPACE                [expr 0x2 <<  9 ]
set 	AT91C_US_PAR_MARK                 [expr 0x3 <<  9 ]
set 	AT91C_US_PAR_NONE                 [expr 0x4 <<  9 ]
set 	AT91C_US_PAR_MULTI_DROP           [expr 0x6 <<  9 ]
set AT91C_US_NBSTOP       [expr 0x3 << 12 ]
set 	AT91C_US_NBSTOP_1_BIT                [expr 0x0 << 12 ]
set 	AT91C_US_NBSTOP_15_BIT               [expr 0x1 << 12 ]
set 	AT91C_US_NBSTOP_2_BIT                [expr 0x2 << 12 ]
set AT91C_US_CHMODE       [expr 0x3 << 14 ]
set 	AT91C_US_CHMODE_NORMAL               [expr 0x0 << 14 ]
set 	AT91C_US_CHMODE_AUTO                 [expr 0x1 << 14 ]
set 	AT91C_US_CHMODE_LOCAL                [expr 0x2 << 14 ]
set 	AT91C_US_CHMODE_REMOTE               [expr 0x3 << 14 ]
set AT91C_US_MSBF         [expr 0x1 << 16 ]
set AT91C_US_MODE9        [expr 0x1 << 17 ]
set AT91C_US_CKLO         [expr 0x1 << 18 ]
set AT91C_US_OVER         [expr 0x1 << 19 ]
set AT91C_US_INACK        [expr 0x1 << 20 ]
set AT91C_US_DSNACK       [expr 0x1 << 21 ]
set AT91C_US_VAR_SYNC     [expr 0x1 << 22 ]
set AT91C_US_MAX_ITER     [expr 0x1 << 24 ]
set AT91C_US_FILTER       [expr 0x1 << 28 ]
set AT91C_US_MANMODE      [expr 0x1 << 29 ]
set AT91C_US_MODSYNC      [expr 0x1 << 30 ]
set AT91C_US_ONEBIT       [expr 0x1 << 31 ]
# -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_RXBRK        [expr 0x1 <<  2 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TIMEOUT      [expr 0x1 <<  8 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_ITERATION    [expr 0x1 << 10 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_NACK         [expr 0x1 << 13 ]
set AT91C_US_RIIC         [expr 0x1 << 16 ]
set AT91C_US_DSRIC        [expr 0x1 << 17 ]
set AT91C_US_DCDIC        [expr 0x1 << 18 ]
set AT91C_US_CTSIC        [expr 0x1 << 19 ]
set AT91C_US_MANE         [expr 0x1 << 20 ]
# -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_RXBRK        [expr 0x1 <<  2 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TIMEOUT      [expr 0x1 <<  8 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_ITERATION    [expr 0x1 << 10 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_NACK         [expr 0x1 << 13 ]
set AT91C_US_RIIC         [expr 0x1 << 16 ]
set AT91C_US_DSRIC        [expr 0x1 << 17 ]
set AT91C_US_DCDIC        [expr 0x1 << 18 ]
set AT91C_US_CTSIC        [expr 0x1 << 19 ]
set AT91C_US_MANE         [expr 0x1 << 20 ]
# -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_RXBRK        [expr 0x1 <<  2 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TIMEOUT      [expr 0x1 <<  8 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_ITERATION    [expr 0x1 << 10 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_NACK         [expr 0x1 << 13 ]
set AT91C_US_RIIC         [expr 0x1 << 16 ]
set AT91C_US_DSRIC        [expr 0x1 << 17 ]
set AT91C_US_DCDIC        [expr 0x1 << 18 ]
set AT91C_US_CTSIC        [expr 0x1 << 19 ]
set AT91C_US_MANE         [expr 0x1 << 20 ]
# -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_RXBRK        [expr 0x1 <<  2 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TIMEOUT      [expr 0x1 <<  8 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_ITERATION    [expr 0x1 << 10 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_NACK         [expr 0x1 << 13 ]
set AT91C_US_RIIC         [expr 0x1 << 16 ]
set AT91C_US_DSRIC        [expr 0x1 << 17 ]
set AT91C_US_DCDIC        [expr 0x1 << 18 ]
set AT91C_US_CTSIC        [expr 0x1 << 19 ]
set AT91C_US_RI           [expr 0x1 << 20 ]
set AT91C_US_DSR          [expr 0x1 << 21 ]
set AT91C_US_DCD          [expr 0x1 << 22 ]
set AT91C_US_CTS          [expr 0x1 << 23 ]
set AT91C_US_MANERR       [expr 0x1 << 24 ]
# -------- US_MAN : (USART Offset: 0x50) Manchester Encoder Decoder Register -------- 
set AT91C_US_TX_PL        [expr 0xF <<  0 ]
set AT91C_US_TX_PP        [expr 0x3 <<  8 ]
set 	AT91C_US_TX_PP_ALL_ONE              [expr 0x0 <<  8 ]
set 	AT91C_US_TX_PP_ALL_ZERO             [expr 0x1 <<  8 ]
set 	AT91C_US_TX_PP_ZERO_ONE             [expr 0x2 <<  8 ]
set 	AT91C_US_TX_PP_ONE_ZERO             [expr 0x3 <<  8 ]
set AT91C_US_TX_MPOL      [expr 0x1 << 12 ]
set AT91C_US_RX_PL        [expr 0xF << 16 ]
set AT91C_US_RX_PP        [expr 0x3 << 24 ]
set 	AT91C_US_RX_PP_ALL_ONE              [expr 0x0 << 24 ]
set 	AT91C_US_RX_PP_ALL_ZERO             [expr 0x1 << 24 ]
set 	AT91C_US_RX_PP_ZERO_ONE             [expr 0x2 << 24 ]
set 	AT91C_US_RX_PP_ONE_ZERO             [expr 0x3 << 24 ]
set AT91C_US_RX_MPOL      [expr 0x1 << 28 ]
set AT91C_US_DRIFT        [expr 0x1 << 30 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface
# *****************************************************************************
# -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- 
set AT91C_SSC_RXEN        [expr 0x1 <<  0 ]
set AT91C_SSC_RXDIS       [expr 0x1 <<  1 ]
set AT91C_SSC_TXEN        [expr 0x1 <<  8 ]
set AT91C_SSC_TXDIS       [expr 0x1 <<  9 ]
set AT91C_SSC_SWRST       [expr 0x1 << 15 ]
# -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- 
set AT91C_SSC_CKS         [expr 0x3 <<  0 ]
set 	AT91C_SSC_CKS_DIV                  0x0
set 	AT91C_SSC_CKS_TK                   0x1
set 	AT91C_SSC_CKS_RK                   0x2
set AT91C_SSC_CKO         [expr 0x7 <<  2 ]
set 	AT91C_SSC_CKO_NONE                 [expr 0x0 <<  2 ]
set 	AT91C_SSC_CKO_CONTINOUS            [expr 0x1 <<  2 ]
set 	AT91C_SSC_CKO_DATA_TX              [expr 0x2 <<  2 ]
set AT91C_SSC_CKI         [expr 0x1 <<  5 ]
set AT91C_SSC_CKG         [expr 0x3 <<  6 ]
set 	AT91C_SSC_CKG_NONE                 [expr 0x0 <<  6 ]
set 	AT91C_SSC_CKG_LOW                  [expr 0x1 <<  6 ]
set 	AT91C_SSC_CKG_HIGH                 [expr 0x2 <<  6 ]
set AT91C_SSC_START       [expr 0xF <<  8 ]
set 	AT91C_SSC_START_CONTINOUS            [expr 0x0 <<  8 ]
set 	AT91C_SSC_START_TX                   [expr 0x1 <<  8 ]
set 	AT91C_SSC_START_LOW_RF               [expr 0x2 <<  8 ]
set 	AT91C_SSC_START_HIGH_RF              [expr 0x3 <<  8 ]
set 	AT91C_SSC_START_FALL_RF              [expr 0x4 <<  8 ]
set 	AT91C_SSC_START_RISE_RF              [expr 0x5 <<  8 ]
set 	AT91C_SSC_START_LEVEL_RF             [expr 0x6 <<  8 ]
set 	AT91C_SSC_START_EDGE_RF              [expr 0x7 <<  8 ]
set 	AT91C_SSC_START_0                    [expr 0x8 <<  8 ]
set AT91C_SSC_STOP        [expr 0x1 << 12 ]
set AT91C_SSC_STTDLY      [expr 0xFF << 16 ]
set AT91C_SSC_PERIOD      [expr 0xFF << 24 ]
# -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- 
set AT91C_SSC_DATLEN      [expr 0x1F <<  0 ]
set AT91C_SSC_LOOP        [expr 0x1 <<  5 ]
set AT91C_SSC_MSBF        [expr 0x1 <<  7 ]
set AT91C_SSC_DATNB       [expr 0xF <<  8 ]
set AT91C_SSC_FSLEN       [expr 0xF << 16 ]
set AT91C_SSC_FSOS        [expr 0x7 << 20 ]
set 	AT91C_SSC_FSOS_NONE                 [expr 0x0 << 20 ]
set 	AT91C_SSC_FSOS_NEGATIVE             [expr 0x1 << 20 ]
set 	AT91C_SSC_FSOS_POSITIVE             [expr 0x2 << 20 ]
set 	AT91C_SSC_FSOS_LOW                  [expr 0x3 << 20 ]
set 	AT91C_SSC_FSOS_HIGH                 [expr 0x4 << 20 ]
set 	AT91C_SSC_FSOS_TOGGLE               [expr 0x5 << 20 ]
set AT91C_SSC_FSEDGE      [expr 0x1 << 24 ]
# -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- 
set AT91C_SSC_CKS         [expr 0x3 <<  0 ]
set 	AT91C_SSC_CKS_DIV                  0x0
set 	AT91C_SSC_CKS_TK                   0x1
set 	AT91C_SSC_CKS_RK                   0x2
set AT91C_SSC_CKO         [expr 0x7 <<  2 ]
set 	AT91C_SSC_CKO_NONE                 [expr 0x0 <<  2 ]
set 	AT91C_SSC_CKO_CONTINOUS            [expr 0x1 <<  2 ]
set 	AT91C_SSC_CKO_DATA_TX              [expr 0x2 <<  2 ]
set AT91C_SSC_CKI         [expr 0x1 <<  5 ]
set AT91C_SSC_CKG         [expr 0x3 <<  6 ]
set 	AT91C_SSC_CKG_NONE                 [expr 0x0 <<  6 ]
set 	AT91C_SSC_CKG_LOW                  [expr 0x1 <<  6 ]
set 	AT91C_SSC_CKG_HIGH                 [expr 0x2 <<  6 ]
set AT91C_SSC_START       [expr 0xF <<  8 ]
set 	AT91C_SSC_START_CONTINOUS            [expr 0x0 <<  8 ]
set 	AT91C_SSC_START_TX                   [expr 0x1 <<  8 ]
set 	AT91C_SSC_START_LOW_RF               [expr 0x2 <<  8 ]
set 	AT91C_SSC_START_HIGH_RF              [expr 0x3 <<  8 ]
set 	AT91C_SSC_START_FALL_RF              [expr 0x4 <<  8 ]
set 	AT91C_SSC_START_RISE_RF              [expr 0x5 <<  8 ]
set 	AT91C_SSC_START_LEVEL_RF             [expr 0x6 <<  8 ]
set 	AT91C_SSC_START_EDGE_RF              [expr 0x7 <<  8 ]
set 	AT91C_SSC_START_0                    [expr 0x8 <<  8 ]
set AT91C_SSC_STTDLY      [expr 0xFF << 16 ]
set AT91C_SSC_PERIOD      [expr 0xFF << 24 ]
# -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- 
set AT91C_SSC_DATLEN      [expr 0x1F <<  0 ]
set AT91C_SSC_DATDEF      [expr 0x1 <<  5 ]
set AT91C_SSC_MSBF        [expr 0x1 <<  7 ]
set AT91C_SSC_DATNB       [expr 0xF <<  8 ]
set AT91C_SSC_FSLEN       [expr 0xF << 16 ]
set AT91C_SSC_FSOS        [expr 0x7 << 20 ]
set 	AT91C_SSC_FSOS_NONE                 [expr 0x0 << 20 ]
set 	AT91C_SSC_FSOS_NEGATIVE             [expr 0x1 << 20 ]
set 	AT91C_SSC_FSOS_POSITIVE             [expr 0x2 << 20 ]
set 	AT91C_SSC_FSOS_LOW                  [expr 0x3 << 20 ]
set 	AT91C_SSC_FSOS_HIGH                 [expr 0x4 << 20 ]
set 	AT91C_SSC_FSOS_TOGGLE               [expr 0x5 << 20 ]
set AT91C_SSC_FSDEN       [expr 0x1 << 23 ]
set AT91C_SSC_FSEDGE      [expr 0x1 << 24 ]
# -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- 
set AT91C_SSC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_SSC_TXEMPTY     [expr 0x1 <<  1 ]
set AT91C_SSC_ENDTX       [expr 0x1 <<  2 ]
set AT91C_SSC_TXBUFE      [expr 0x1 <<  3 ]
set AT91C_SSC_RXRDY       [expr 0x1 <<  4 ]
set AT91C_SSC_OVRUN       [expr 0x1 <<  5 ]
set AT91C_SSC_ENDRX       [expr 0x1 <<  6 ]
set AT91C_SSC_RXBUFF      [expr 0x1 <<  7 ]
set AT91C_SSC_CP0         [expr 0x1 <<  8 ]
set AT91C_SSC_CP1         [expr 0x1 <<  9 ]
set AT91C_SSC_TXSYN       [expr 0x1 << 10 ]
set AT91C_SSC_RXSYN       [expr 0x1 << 11 ]
set AT91C_SSC_TXENA       [expr 0x1 << 16 ]
set AT91C_SSC_RXENA       [expr 0x1 << 17 ]
# -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- 
set AT91C_SSC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_SSC_TXEMPTY     [expr 0x1 <<  1 ]
set AT91C_SSC_ENDTX       [expr 0x1 <<  2 ]
set AT91C_SSC_TXBUFE      [expr 0x1 <<  3 ]
set AT91C_SSC_RXRDY       [expr 0x1 <<  4 ]
set AT91C_SSC_OVRUN       [expr 0x1 <<  5 ]
set AT91C_SSC_ENDRX       [expr 0x1 <<  6 ]
set AT91C_SSC_RXBUFF      [expr 0x1 <<  7 ]
set AT91C_SSC_CP0         [expr 0x1 <<  8 ]
set AT91C_SSC_CP1         [expr 0x1 <<  9 ]
set AT91C_SSC_TXSYN       [expr 0x1 << 10 ]
set AT91C_SSC_RXSYN       [expr 0x1 << 11 ]
# -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- 
set AT91C_SSC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_SSC_TXEMPTY     [expr 0x1 <<  1 ]
set AT91C_SSC_ENDTX       [expr 0x1 <<  2 ]
set AT91C_SSC_TXBUFE      [expr 0x1 <<  3 ]
set AT91C_SSC_RXRDY       [expr 0x1 <<  4 ]
set AT91C_SSC_OVRUN       [expr 0x1 <<  5 ]
set AT91C_SSC_ENDRX       [expr 0x1 <<  6 ]
set AT91C_SSC_RXBUFF      [expr 0x1 <<  7 ]
set AT91C_SSC_CP0         [expr 0x1 <<  8 ]
set AT91C_SSC_CP1         [expr 0x1 <<  9 ]
set AT91C_SSC_TXSYN       [expr 0x1 << 10 ]
set AT91C_SSC_RXSYN       [expr 0x1 << 11 ]
# -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- 
set AT91C_SSC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_SSC_TXEMPTY     [expr 0x1 <<  1 ]
set AT91C_SSC_ENDTX       [expr 0x1 <<  2 ]
set AT91C_SSC_TXBUFE      [expr 0x1 <<  3 ]
set AT91C_SSC_RXRDY       [expr 0x1 <<  4 ]
set AT91C_SSC_OVRUN       [expr 0x1 <<  5 ]
set AT91C_SSC_ENDRX       [expr 0x1 <<  6 ]
set AT91C_SSC_RXBUFF      [expr 0x1 <<  7 ]
set AT91C_SSC_CP0         [expr 0x1 <<  8 ]
set AT91C_SSC_CP1         [expr 0x1 <<  9 ]
set AT91C_SSC_TXSYN       [expr 0x1 << 10 ]
set AT91C_SSC_RXSYN       [expr 0x1 << 11 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR PWMC Channel Interface
# *****************************************************************************
# -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- 
set AT91C_PWMC_CPRE       [expr 0xF <<  0 ]
set 	AT91C_PWMC_CPRE_MCK                  0x0
set 	AT91C_PWMC_CPRE_MCK/2                0x1
set 	AT91C_PWMC_CPRE_MCK/4                0x2
set 	AT91C_PWMC_CPRE_MCK/8                0x3
set 	AT91C_PWMC_CPRE_MCK/16               0x4
set 	AT91C_PWMC_CPRE_MCK/32               0x5
set 	AT91C_PWMC_CPRE_MCK/64               0x6
set 	AT91C_PWMC_CPRE_MCK/128              0x7
set 	AT91C_PWMC_CPRE_MCK/256              0x8
set 	AT91C_PWMC_CPRE_MCK/512              0x9
set 	AT91C_PWMC_CPRE_MCK/1024             0xA
set 	AT91C_PWMC_CPRE_MCKA                 0xB
set 	AT91C_PWMC_CPRE_MCKB                 0xC
set AT91C_PWMC_CALG       [expr 0x1 <<  8 ]
set AT91C_PWMC_CPOL       [expr 0x1 <<  9 ]
set AT91C_PWMC_CPD        [expr 0x1 << 10 ]
# -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- 
set AT91C_PWMC_CDTY       [expr 0x0 <<  0 ]
# -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- 
set AT91C_PWMC_CPRD       [expr 0x0 <<  0 ]
# -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- 
set AT91C_PWMC_CCNT       [expr 0x0 <<  0 ]
# -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- 
set AT91C_PWMC_CUPD       [expr 0x0 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface
# *****************************************************************************
# -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- 
set AT91C_PWMC_DIVA       [expr 0xFF <<  0 ]
set AT91C_PWMC_PREA       [expr 0xF <<  8 ]
set 	AT91C_PWMC_PREA_MCK                  [expr 0x0 <<  8 ]
set 	AT91C_PWMC_PREA_MCK/2                [expr 0x1 <<  8 ]
set 	AT91C_PWMC_PREA_MCK/4                [expr 0x2 <<  8 ]
set 	AT91C_PWMC_PREA_MCK/8                [expr 0x3 <<  8 ]
set 	AT91C_PWMC_PREA_MCK/16               [expr 0x4 <<  8 ]
set 	AT91C_PWMC_PREA_MCK/32               [expr 0x5 <<  8 ]
set 	AT91C_PWMC_PREA_MCK/64               [expr 0x6 <<  8 ]
set 	AT91C_PWMC_PREA_MCK/128              [expr 0x7 <<  8 ]
set 	AT91C_PWMC_PREA_MCK/256              [expr 0x8 <<  8 ]
set AT91C_PWMC_DIVB       [expr 0xFF << 16 ]
set AT91C_PWMC_PREB       [expr 0xF << 24 ]
set 	AT91C_PWMC_PREB_MCK                  [expr 0x0 << 24 ]
set 	AT91C_PWMC_PREB_MCK/2                [expr 0x1 << 24 ]
set 	AT91C_PWMC_PREB_MCK/4                [expr 0x2 << 24 ]
set 	AT91C_PWMC_PREB_MCK/8                [expr 0x3 << 24 ]
set 	AT91C_PWMC_PREB_MCK/16               [expr 0x4 << 24 ]
set 	AT91C_PWMC_PREB_MCK/32               [expr 0x5 << 24 ]
set 	AT91C_PWMC_PREB_MCK/64               [expr 0x6 << 24 ]
set 	AT91C_PWMC_PREB_MCK/128              [expr 0x7 << 24 ]
set 	AT91C_PWMC_PREB_MCK/256              [expr 0x8 << 24 ]
# -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
# -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
# -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
# -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
# -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
# -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
# -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Serial Parallel Interface
# *****************************************************************************
# -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- 
set AT91C_SPI_SPIEN       [expr 0x1 <<  0 ]
set AT91C_SPI_SPIDIS      [expr 0x1 <<  1 ]
set AT91C_SPI_SWRST       [expr 0x1 <<  7 ]
set AT91C_SPI_LASTXFER    [expr 0x1 << 24 ]
# -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- 
set AT91C_SPI_MSTR        [expr 0x1 <<  0 ]
set AT91C_SPI_PS          [expr 0x1 <<  1 ]
set 	AT91C_SPI_PS_FIXED                [expr 0x0 <<  1 ]
set 	AT91C_SPI_PS_VARIABLE             [expr 0x1 <<  1 ]
set AT91C_SPI_PCSDEC      [expr 0x1 <<  2 ]
set AT91C_SPI_FDIV        [expr 0x1 <<  3 ]
set AT91C_SPI_MODFDIS     [expr 0x1 <<  4 ]
set AT91C_SPI_LLB         [expr 0x1 <<  7 ]
set AT91C_SPI_PCS         [expr 0xF << 16 ]
set AT91C_SPI_DLYBCS      [expr 0xFF << 24 ]
# -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- 
set AT91C_SPI_RD          [expr 0xFFFF <<  0 ]
set AT91C_SPI_RPCS        [expr 0xF << 16 ]
# -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- 
set AT91C_SPI_TD          [expr 0xFFFF <<  0 ]
set AT91C_SPI_TPCS        [expr 0xF << 16 ]
set AT91C_SPI_LASTXFER    [expr 0x1 << 24 ]
# -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- 
set AT91C_SPI_RDRF        [expr 0x1 <<  0 ]
set AT91C_SPI_TDRE        [expr 0x1 <<  1 ]
set AT91C_SPI_MODF        [expr 0x1 <<  2 ]
set AT91C_SPI_OVRES       [expr 0x1 <<  3 ]
set AT91C_SPI_ENDRX       [expr 0x1 <<  4 ]
set AT91C_SPI_ENDTX       [expr 0x1 <<  5 ]
set AT91C_SPI_RXBUFF      [expr 0x1 <<  6 ]
set AT91C_SPI_TXBUFE      [expr 0x1 <<  7 ]
set AT91C_SPI_NSSR        [expr 0x1 <<  8 ]
set AT91C_SPI_TXEMPTY     [expr 0x1 <<  9 ]
set AT91C_SPI_SPIENS      [expr 0x1 << 16 ]
# -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- 
set AT91C_SPI_RDRF        [expr 0x1 <<  0 ]
set AT91C_SPI_TDRE        [expr 0x1 <<  1 ]
set AT91C_SPI_MODF        [expr 0x1 <<  2 ]
set AT91C_SPI_OVRES       [expr 0x1 <<  3 ]
set AT91C_SPI_ENDRX       [expr 0x1 <<  4 ]
set AT91C_SPI_ENDTX       [expr 0x1 <<  5 ]
set AT91C_SPI_RXBUFF      [expr 0x1 <<  6 ]
set AT91C_SPI_TXBUFE      [expr 0x1 <<  7 ]
set AT91C_SPI_NSSR        [expr 0x1 <<  8 ]
set AT91C_SPI_TXEMPTY     [expr 0x1 <<  9 ]
# -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- 
set AT91C_SPI_RDRF        [expr 0x1 <<  0 ]
set AT91C_SPI_TDRE        [expr 0x1 <<  1 ]
set AT91C_SPI_MODF        [expr 0x1 <<  2 ]
set AT91C_SPI_OVRES       [expr 0x1 <<  3 ]
set AT91C_SPI_ENDRX       [expr 0x1 <<  4 ]
set AT91C_SPI_ENDTX       [expr 0x1 <<  5 ]
set AT91C_SPI_RXBUFF      [expr 0x1 <<  6 ]
set AT91C_SPI_TXBUFE      [expr 0x1 <<  7 ]
set AT91C_SPI_NSSR        [expr 0x1 <<  8 ]
set AT91C_SPI_TXEMPTY     [expr 0x1 <<  9 ]
# -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- 
set AT91C_SPI_RDRF        [expr 0x1 <<  0 ]
set AT91C_SPI_TDRE        [expr 0x1 <<  1 ]
set AT91C_SPI_MODF        [expr 0x1 <<  2 ]
set AT91C_SPI_OVRES       [expr 0x1 <<  3 ]
set AT91C_SPI_ENDRX       [expr 0x1 <<  4 ]
set AT91C_SPI_ENDTX       [expr 0x1 <<  5 ]
set AT91C_SPI_RXBUFF      [expr 0x1 <<  6 ]
set AT91C_SPI_TXBUFE      [expr 0x1 <<  7 ]
set AT91C_SPI_NSSR        [expr 0x1 <<  8 ]
set AT91C_SPI_TXEMPTY     [expr 0x1 <<  9 ]
# -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- 
set AT91C_SPI_CPOL        [expr 0x1 <<  0 ]
set AT91C_SPI_NCPHA       [expr 0x1 <<  1 ]
set AT91C_SPI_CSAAT       [expr 0x1 <<  3 ]
set AT91C_SPI_BITS        [expr 0xF <<  4 ]
set 	AT91C_SPI_BITS_8                    [expr 0x0 <<  4 ]
set 	AT91C_SPI_BITS_9                    [expr 0x1 <<  4 ]
set 	AT91C_SPI_BITS_10                   [expr 0x2 <<  4 ]
set 	AT91C_SPI_BITS_11                   [expr 0x3 <<  4 ]
set 	AT91C_SPI_BITS_12                   [expr 0x4 <<  4 ]
set 	AT91C_SPI_BITS_13                   [expr 0x5 <<  4 ]
set 	AT91C_SPI_BITS_14                   [expr 0x6 <<  4 ]
set 	AT91C_SPI_BITS_15                   [expr 0x7 <<  4 ]
set 	AT91C_SPI_BITS_16                   [expr 0x8 <<  4 ]
set AT91C_SPI_SCBR        [expr 0xFF <<  8 ]
set AT91C_SPI_DLYBS       [expr 0xFF << 16 ]
set AT91C_SPI_DLYBCT      [expr 0xFF << 24 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR 
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR UDPHS Enpoint FIFO data register
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR UDPHS Endpoint struct
# *****************************************************************************
# -------- UDPHS_EPTCFG : (UDPHS_EPT Offset: 0x0) UDPHS Endpoint Config Register -------- 
set AT91C_UDPHS_EPT_SIZE  [expr 0x7 <<  0 ]
set 	AT91C_UDPHS_EPT_SIZE_8                    0x0
set 	AT91C_UDPHS_EPT_SIZE_16                   0x1
set 	AT91C_UDPHS_EPT_SIZE_32                   0x2
set 	AT91C_UDPHS_EPT_SIZE_64                   0x3
set 	AT91C_UDPHS_EPT_SIZE_128                  0x4
set 	AT91C_UDPHS_EPT_SIZE_256                  0x5
set 	AT91C_UDPHS_EPT_SIZE_512                  0x6
set 	AT91C_UDPHS_EPT_SIZE_1024                 0x7
set AT91C_UDPHS_EPT_DIR   [expr 0x1 <<  3 ]
set 	AT91C_UDPHS_EPT_DIR_OUT                  [expr 0x0 <<  3 ]
set 	AT91C_UDPHS_EPT_DIR_IN                   [expr 0x1 <<  3 ]
set AT91C_UDPHS_EPT_TYPE  [expr 0x3 <<  4 ]
set 	AT91C_UDPHS_EPT_TYPE_CTL_EPT              [expr 0x0 <<  4 ]
set 	AT91C_UDPHS_EPT_TYPE_ISO_EPT              [expr 0x1 <<  4 ]
set 	AT91C_UDPHS_EPT_TYPE_BUL_EPT              [expr 0x2 <<  4 ]
set 	AT91C_UDPHS_EPT_TYPE_INT_EPT              [expr 0x3 <<  4 ]
set AT91C_UDPHS_BK_NUMBER [expr 0x3 <<  6 ]
set 	AT91C_UDPHS_BK_NUMBER_0                    [expr 0x0 <<  6 ]
set 	AT91C_UDPHS_BK_NUMBER_1                    [expr 0x1 <<  6 ]
set 	AT91C_UDPHS_BK_NUMBER_2                    [expr 0x2 <<  6 ]
set 	AT91C_UDPHS_BK_NUMBER_3                    [expr 0x3 <<  6 ]
set AT91C_UDPHS_NB_TRANS  [expr 0x3 <<  8 ]
set AT91C_UDPHS_EPT_MAPD  [expr 0x1 << 31 ]
# -------- UDPHS_EPTCTLENB : (UDPHS_EPT Offset: 0x4) UDPHS Endpoint Control Enable Register -------- 
set AT91C_UDPHS_EPT_ENABL [expr 0x1 <<  0 ]
set AT91C_UDPHS_AUTO_VALID [expr 0x1 <<  1 ]
set AT91C_UDPHS_INTDIS_DMA [expr 0x1 <<  3 ]
set AT91C_UDPHS_NYET_DIS  [expr 0x1 <<  4 ]
set AT91C_UDPHS_DATAX_RX  [expr 0x1 <<  6 ]
set AT91C_UDPHS_MDATA_RX  [expr 0x1 <<  7 ]
set AT91C_UDPHS_ERR_OVFLW [expr 0x1 <<  8 ]
set AT91C_UDPHS_RX_BK_RDY [expr 0x1 <<  9 ]
set AT91C_UDPHS_TX_COMPLT [expr 0x1 << 10 ]
set AT91C_UDPHS_TX_PK_RDY [expr 0x1 << 11 ]
set AT91C_UDPHS_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_UDPHS_RX_SETUP  [expr 0x1 << 12 ]
set AT91C_UDPHS_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_UDPHS_STALL_SNT [expr 0x1 << 13 ]
set AT91C_UDPHS_ERR_CRISO [expr 0x1 << 13 ]
set AT91C_UDPHS_NAK_IN    [expr 0x1 << 14 ]
set AT91C_UDPHS_NAK_OUT   [expr 0x1 << 15 ]
set AT91C_UDPHS_BUSY_BANK [expr 0x1 << 18 ]
set AT91C_UDPHS_SHRT_PCKT [expr 0x1 << 31 ]
# -------- UDPHS_EPTCTLDIS : (UDPHS_EPT Offset: 0x8) UDPHS Endpoint Control Disable Register -------- 
set AT91C_UDPHS_EPT_DISABL [expr 0x1 <<  0 ]
set AT91C_UDPHS_AUTO_VALID [expr 0x1 <<  1 ]
set AT91C_UDPHS_INTDIS_DMA [expr 0x1 <<  3 ]
set AT91C_UDPHS_NYET_DIS  [expr 0x1 <<  4 ]
set AT91C_UDPHS_DATAX_RX  [expr 0x1 <<  6 ]
set AT91C_UDPHS_MDATA_RX  [expr 0x1 <<  7 ]
set AT91C_UDPHS_ERR_OVFLW [expr 0x1 <<  8 ]
set AT91C_UDPHS_RX_BK_RDY [expr 0x1 <<  9 ]
set AT91C_UDPHS_TX_COMPLT [expr 0x1 << 10 ]
set AT91C_UDPHS_TX_PK_RDY [expr 0x1 << 11 ]
set AT91C_UDPHS_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_UDPHS_RX_SETUP  [expr 0x1 << 12 ]
set AT91C_UDPHS_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_UDPHS_STALL_SNT [expr 0x1 << 13 ]
set AT91C_UDPHS_ERR_CRISO [expr 0x1 << 13 ]
set AT91C_UDPHS_NAK_IN    [expr 0x1 << 14 ]
set AT91C_UDPHS_NAK_OUT   [expr 0x1 << 15 ]
set AT91C_UDPHS_BUSY_BANK [expr 0x1 << 18 ]
set AT91C_UDPHS_SHRT_PCKT [expr 0x1 << 31 ]
# -------- UDPHS_EPTCTL : (UDPHS_EPT Offset: 0xc) UDPHS Endpoint Control Register -------- 
set AT91C_UDPHS_EPT_ENABL [expr 0x1 <<  0 ]
set AT91C_UDPHS_AUTO_VALID [expr 0x1 <<  1 ]
set AT91C_UDPHS_INTDIS_DMA [expr 0x1 <<  3 ]
set AT91C_UDPHS_NYET_DIS  [expr 0x1 <<  4 ]
set AT91C_UDPHS_DATAX_RX  [expr 0x1 <<  6 ]
set AT91C_UDPHS_MDATA_RX  [expr 0x1 <<  7 ]
set AT91C_UDPHS_ERR_OVFLW [expr 0x1 <<  8 ]
set AT91C_UDPHS_RX_BK_RDY [expr 0x1 <<  9 ]
set AT91C_UDPHS_TX_COMPLT [expr 0x1 << 10 ]
set AT91C_UDPHS_TX_PK_RDY [expr 0x1 << 11 ]
set AT91C_UDPHS_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_UDPHS_RX_SETUP  [expr 0x1 << 12 ]
set AT91C_UDPHS_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_UDPHS_STALL_SNT [expr 0x1 << 13 ]
set AT91C_UDPHS_ERR_CRISO [expr 0x1 << 13 ]
set AT91C_UDPHS_NAK_IN    [expr 0x1 << 14 ]
set AT91C_UDPHS_NAK_OUT   [expr 0x1 << 15 ]
set AT91C_UDPHS_BUSY_BANK [expr 0x1 << 18 ]
set AT91C_UDPHS_SHRT_PCKT [expr 0x1 << 31 ]
# -------- UDPHS_EPTSETSTA : (UDPHS_EPT Offset: 0x14) UDPHS Endpoint Set Status Register -------- 
set AT91C_UDPHS_FRCESTALL [expr 0x1 <<  5 ]
set AT91C_UDPHS_KILL_BANK [expr 0x1 <<  9 ]
set AT91C_UDPHS_TX_PK_RDY [expr 0x1 << 11 ]
# -------- UDPHS_EPTCLRSTA : (UDPHS_EPT Offset: 0x18) UDPHS Endpoint Clear Status Register -------- 
set AT91C_UDPHS_FRCESTALL [expr 0x1 <<  5 ]
set AT91C_UDPHS_TOGGLESQ  [expr 0x1 <<  6 ]
set AT91C_UDPHS_RX_BK_RDY [expr 0x1 <<  9 ]
set AT91C_UDPHS_TX_COMPLT [expr 0x1 << 10 ]
set AT91C_UDPHS_RX_SETUP  [expr 0x1 << 12 ]
set AT91C_UDPHS_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_UDPHS_STALL_SNT [expr 0x1 << 13 ]
set AT91C_UDPHS_NAK_IN    [expr 0x1 << 14 ]
set AT91C_UDPHS_NAK_OUT   [expr 0x1 << 15 ]
# -------- UDPHS_EPTSTA : (UDPHS_EPT Offset: 0x1c) UDPHS Endpoint Status Register -------- 
set AT91C_UDPHS_FRCESTALL [expr 0x1 <<  5 ]
set AT91C_UDPHS_TOGGLESQ_STA [expr 0x3 <<  6 ]
set 	AT91C_UDPHS_TOGGLESQ_STA_00                   [expr 0x0 <<  6 ]
set 	AT91C_UDPHS_TOGGLESQ_STA_01                   [expr 0x1 <<  6 ]
set 	AT91C_UDPHS_TOGGLESQ_STA_10                   [expr 0x2 <<  6 ]
set 	AT91C_UDPHS_TOGGLESQ_STA_11                   [expr 0x3 <<  6 ]
set AT91C_UDPHS_ERR_OVFLW [expr 0x1 <<  8 ]
set AT91C_UDPHS_RX_BK_RDY [expr 0x1 <<  9 ]
set AT91C_UDPHS_KILL_BANK [expr 0x1 <<  9 ]
set AT91C_UDPHS_TX_COMPLT [expr 0x1 << 10 ]
set AT91C_UDPHS_TX_PK_RDY [expr 0x1 << 11 ]
set AT91C_UDPHS_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_UDPHS_RX_SETUP  [expr 0x1 << 12 ]
set AT91C_UDPHS_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_UDPHS_STALL_SNT [expr 0x1 << 13 ]
set AT91C_UDPHS_ERR_CRISO [expr 0x1 << 13 ]
set AT91C_UDPHS_NAK_IN    [expr 0x1 << 14 ]
set AT91C_UDPHS_NAK_OUT   [expr 0x1 << 15 ]
set AT91C_UDPHS_CURRENT_BANK [expr 0x3 << 16 ]
set 	AT91C_UDPHS_CURRENT_BANK_00                   [expr 0x0 << 16 ]
set 	AT91C_UDPHS_CURRENT_BANK_01                   [expr 0x1 << 16 ]
set 	AT91C_UDPHS_CURRENT_BANK_10                   [expr 0x2 << 16 ]
set 	AT91C_UDPHS_CURRENT_BANK_11                   [expr 0x3 << 16 ]
set AT91C_UDPHS_CONTROL_DIR [expr 0x3 << 16 ]
set 	AT91C_UDPHS_CONTROL_DIR_00                   [expr 0x0 << 16 ]
set 	AT91C_UDPHS_CONTROL_DIR_01                   [expr 0x1 << 16 ]
set 	AT91C_UDPHS_CONTROL_DIR_10                   [expr 0x2 << 16 ]
set 	AT91C_UDPHS_CONTROL_DIR_11                   [expr 0x3 << 16 ]
set AT91C_UDPHS_BUSY_BANK_STA [expr 0x3 << 18 ]
set 	AT91C_UDPHS_BUSY_BANK_STA_00                   [expr 0x0 << 18 ]
set 	AT91C_UDPHS_BUSY_BANK_STA_01                   [expr 0x1 << 18 ]
set 	AT91C_UDPHS_BUSY_BANK_STA_10                   [expr 0x2 << 18 ]
set 	AT91C_UDPHS_BUSY_BANK_STA_11                   [expr 0x3 << 18 ]
set AT91C_UDPHS_BYTE_COUNT [expr 0x7FF << 20 ]
set AT91C_UDPHS_SHRT_PCKT [expr 0x1 << 31 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR UDPHS DMA struct
# *****************************************************************************
# -------- UDPHS_DMANXTDSC : (UDPHS_DMA Offset: 0x0) UDPHS DMA Next Descriptor Address Register -------- 
set AT91C_UDPHS_NXT_DSC_ADD [expr 0xFFFFFFF <<  4 ]
# -------- UDPHS_DMAADDRESS : (UDPHS_DMA Offset: 0x4) UDPHS DMA Channel Address Register -------- 
set AT91C_UDPHS_BUFF_ADD  [expr 0x0 <<  0 ]
# -------- UDPHS_DMACONTROL : (UDPHS_DMA Offset: 0x8) UDPHS DMA Channel Control Register -------- 
set AT91C_UDPHS_CHANN_ENB [expr 0x1 <<  0 ]
set AT91C_UDPHS_LDNXT_DSC [expr 0x1 <<  1 ]
set AT91C_UDPHS_END_TR_EN [expr 0x1 <<  2 ]
set AT91C_UDPHS_END_B_EN  [expr 0x1 <<  3 ]
set AT91C_UDPHS_END_TR_IT [expr 0x1 <<  4 ]
set AT91C_UDPHS_END_BUFFIT [expr 0x1 <<  5 ]
set AT91C_UDPHS_DESC_LD_IT [expr 0x1 <<  6 ]
set AT91C_UDPHS_BURST_LCK [expr 0x1 <<  7 ]
set AT91C_UDPHS_BUFF_LENGTH [expr 0xFFFF << 16 ]
# -------- UDPHS_DMASTATUS : (UDPHS_DMA Offset: 0xc) UDPHS DMA Channelx Status Register -------- 
set AT91C_UDPHS_CHANN_ENB [expr 0x1 <<  0 ]
set AT91C_UDPHS_CHANN_ACT [expr 0x1 <<  1 ]
set AT91C_UDPHS_END_TR_ST [expr 0x1 <<  4 ]
set AT91C_UDPHS_END_BF_ST [expr 0x1 <<  5 ]
set AT91C_UDPHS_DESC_LDST [expr 0x1 <<  6 ]
set AT91C_UDPHS_BUFF_COUNT [expr 0xFFFF << 16 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR UDPHS High Speed Device Interface
# *****************************************************************************
# -------- UDPHS_CTRL : (UDPHS Offset: 0x0) UDPHS Control Register -------- 
set AT91C_UDPHS_DEV_ADDR  [expr 0x7F <<  0 ]
set AT91C_UDPHS_FADDR_EN  [expr 0x1 <<  7 ]
set AT91C_UDPHS_EN_UDPHS  [expr 0x1 <<  8 ]
set AT91C_UDPHS_DETACH    [expr 0x1 <<  9 ]
set AT91C_UDPHS_REWAKEUP  [expr 0x1 << 10 ]
set AT91C_UDPHS_PULLD_DIS [expr 0x1 << 11 ]
# -------- UDPHS_FNUM : (UDPHS Offset: 0x4) UDPHS Frame Number Register -------- 
set AT91C_UDPHS_MICRO_FRAME_NUM [expr 0x7 <<  0 ]
set AT91C_UDPHS_FRAME_NUMBER [expr 0x7FF <<  3 ]
set AT91C_UDPHS_FNUM_ERR  [expr 0x1 << 31 ]
# -------- UDPHS_IEN : (UDPHS Offset: 0x10) UDPHS Interrupt Enable Register -------- 
set AT91C_UDPHS_DET_SUSPD [expr 0x1 <<  1 ]
set AT91C_UDPHS_MICRO_SOF [expr 0x1 <<  2 ]
set AT91C_UDPHS_IEN_SOF   [expr 0x1 <<  3 ]
set AT91C_UDPHS_ENDRESET  [expr 0x1 <<  4 ]
set AT91C_UDPHS_WAKE_UP   [expr 0x1 <<  5 ]
set AT91C_UDPHS_ENDOFRSM  [expr 0x1 <<  6 ]
set AT91C_UDPHS_UPSTR_RES [expr 0x1 <<  7 ]
set AT91C_UDPHS_EPT_INT_0 [expr 0x1 <<  8 ]
set AT91C_UDPHS_EPT_INT_1 [expr 0x1 <<  9 ]
set AT91C_UDPHS_EPT_INT_2 [expr 0x1 << 10 ]
set AT91C_UDPHS_EPT_INT_3 [expr 0x1 << 11 ]
set AT91C_UDPHS_EPT_INT_4 [expr 0x1 << 12 ]
set AT91C_UDPHS_EPT_INT_5 [expr 0x1 << 13 ]
set AT91C_UDPHS_EPT_INT_6 [expr 0x1 << 14 ]
set AT91C_UDPHS_EPT_INT_7 [expr 0x1 << 15 ]
set AT91C_UDPHS_EPT_INT_8 [expr 0x1 << 16 ]
set AT91C_UDPHS_EPT_INT_9 [expr 0x1 << 17 ]
set AT91C_UDPHS_EPT_INT_10 [expr 0x1 << 18 ]
set AT91C_UDPHS_EPT_INT_11 [expr 0x1 << 19 ]
set AT91C_UDPHS_EPT_INT_12 [expr 0x1 << 20 ]
set AT91C_UDPHS_EPT_INT_13 [expr 0x1 << 21 ]
set AT91C_UDPHS_EPT_INT_14 [expr 0x1 << 22 ]
set AT91C_UDPHS_EPT_INT_15 [expr 0x1 << 23 ]
set AT91C_UDPHS_DMA_INT_1 [expr 0x1 << 25 ]
set AT91C_UDPHS_DMA_INT_2 [expr 0x1 << 26 ]
set AT91C_UDPHS_DMA_INT_3 [expr 0x1 << 27 ]
set AT91C_UDPHS_DMA_INT_4 [expr 0x1 << 28 ]
set AT91C_UDPHS_DMA_INT_5 [expr 0x1 << 29 ]
set AT91C_UDPHS_DMA_INT_6 [expr 0x1 << 30 ]
set AT91C_UDPHS_DMA_INT_7 [expr 0x1 << 31 ]
# -------- UDPHS_INTSTA : (UDPHS Offset: 0x14) UDPHS Interrupt Status Register -------- 
set AT91C_UDPHS_SPEED     [expr 0x1 <<  0 ]
set AT91C_UDPHS_DET_SUSPD [expr 0x1 <<  1 ]
set AT91C_UDPHS_MICRO_SOF [expr 0x1 <<  2 ]
set AT91C_UDPHS_IEN_SOF   [expr 0x1 <<  3 ]
set AT91C_UDPHS_ENDRESET  [expr 0x1 <<  4 ]
set AT91C_UDPHS_WAKE_UP   [expr 0x1 <<  5 ]
set AT91C_UDPHS_ENDOFRSM  [expr 0x1 <<  6 ]
set AT91C_UDPHS_UPSTR_RES [expr 0x1 <<  7 ]
set AT91C_UDPHS_EPT_INT_0 [expr 0x1 <<  8 ]
set AT91C_UDPHS_EPT_INT_1 [expr 0x1 <<  9 ]
set AT91C_UDPHS_EPT_INT_2 [expr 0x1 << 10 ]
set AT91C_UDPHS_EPT_INT_3 [expr 0x1 << 11 ]
set AT91C_UDPHS_EPT_INT_4 [expr 0x1 << 12 ]
set AT91C_UDPHS_EPT_INT_5 [expr 0x1 << 13 ]
set AT91C_UDPHS_EPT_INT_6 [expr 0x1 << 14 ]
set AT91C_UDPHS_EPT_INT_7 [expr 0x1 << 15 ]
set AT91C_UDPHS_EPT_INT_8 [expr 0x1 << 16 ]
set AT91C_UDPHS_EPT_INT_9 [expr 0x1 << 17 ]
set AT91C_UDPHS_EPT_INT_10 [expr 0x1 << 18 ]
set AT91C_UDPHS_EPT_INT_11 [expr 0x1 << 19 ]
set AT91C_UDPHS_EPT_INT_12 [expr 0x1 << 20 ]
set AT91C_UDPHS_EPT_INT_13 [expr 0x1 << 21 ]
set AT91C_UDPHS_EPT_INT_14 [expr 0x1 << 22 ]
set AT91C_UDPHS_EPT_INT_15 [expr 0x1 << 23 ]
set AT91C_UDPHS_DMA_INT_1 [expr 0x1 << 25 ]
set AT91C_UDPHS_DMA_INT_2 [expr 0x1 << 26 ]
set AT91C_UDPHS_DMA_INT_3 [expr 0x1 << 27 ]
set AT91C_UDPHS_DMA_INT_4 [expr 0x1 << 28 ]
set AT91C_UDPHS_DMA_INT_5 [expr 0x1 << 29 ]
set AT91C_UDPHS_DMA_INT_6 [expr 0x1 << 30 ]
set AT91C_UDPHS_DMA_INT_7 [expr 0x1 << 31 ]
# -------- UDPHS_CLRINT : (UDPHS Offset: 0x18) UDPHS Clear Interrupt Register -------- 
set AT91C_UDPHS_DET_SUSPD [expr 0x1 <<  1 ]
set AT91C_UDPHS_MICRO_SOF [expr 0x1 <<  2 ]
set AT91C_UDPHS_IEN_SOF   [expr 0x1 <<  3 ]
set AT91C_UDPHS_ENDRESET  [expr 0x1 <<  4 ]
set AT91C_UDPHS_WAKE_UP   [expr 0x1 <<  5 ]
set AT91C_UDPHS_ENDOFRSM  [expr 0x1 <<  6 ]
set AT91C_UDPHS_UPSTR_RES [expr 0x1 <<  7 ]
# -------- UDPHS_EPTRST : (UDPHS Offset: 0x1c) UDPHS Endpoints Reset Register -------- 
set AT91C_UDPHS_RST_EPT_0 [expr 0x1 <<  0 ]
set AT91C_UDPHS_RST_EPT_1 [expr 0x1 <<  1 ]
set AT91C_UDPHS_RST_EPT_2 [expr 0x1 <<  2 ]
set AT91C_UDPHS_RST_EPT_3 [expr 0x1 <<  3 ]
set AT91C_UDPHS_RST_EPT_4 [expr 0x1 <<  4 ]
set AT91C_UDPHS_RST_EPT_5 [expr 0x1 <<  5 ]
set AT91C_UDPHS_RST_EPT_6 [expr 0x1 <<  6 ]
set AT91C_UDPHS_RST_EPT_7 [expr 0x1 <<  7 ]
set AT91C_UDPHS_RST_EPT_8 [expr 0x1 <<  8 ]
set AT91C_UDPHS_RST_EPT_9 [expr 0x1 <<  9 ]
set AT91C_UDPHS_RST_EPT_10 [expr 0x1 << 10 ]
set AT91C_UDPHS_RST_EPT_11 [expr 0x1 << 11 ]
set AT91C_UDPHS_RST_EPT_12 [expr 0x1 << 12 ]
set AT91C_UDPHS_RST_EPT_13 [expr 0x1 << 13 ]
set AT91C_UDPHS_RST_EPT_14 [expr 0x1 << 14 ]
set AT91C_UDPHS_RST_EPT_15 [expr 0x1 << 15 ]
# -------- UDPHS_TSTSOFCNT : (UDPHS Offset: 0xd0) UDPHS Test SOF Counter Register -------- 
set AT91C_UDPHS_SOFCNTMAX [expr 0x3 <<  0 ]
set AT91C_UDPHS_SOFCTLOAD [expr 0x1 <<  7 ]
# -------- UDPHS_TSTCNTA : (UDPHS Offset: 0xd4) UDPHS Test A Counter Register -------- 
set AT91C_UDPHS_CNTAMAX   [expr 0x7FFF <<  0 ]
set AT91C_UDPHS_CNTALOAD  [expr 0x1 << 15 ]
# -------- UDPHS_TSTCNTB : (UDPHS Offset: 0xd8) UDPHS Test B Counter Register -------- 
set AT91C_UDPHS_CNTBMAX   [expr 0x7FFF <<  0 ]
set AT91C_UDPHS_CNTBLOAD  [expr 0x1 << 15 ]
# -------- UDPHS_TSTMODREG : (UDPHS Offset: 0xdc) UDPHS Test Mode Register -------- 
set AT91C_UDPHS_TSTMODE   [expr 0x1F <<  1 ]
# -------- UDPHS_TST : (UDPHS Offset: 0xe0) UDPHS Test Register -------- 
set AT91C_UDPHS_SPEED_CFG [expr 0x3 <<  0 ]
set 	AT91C_UDPHS_SPEED_CFG_NM                   0x0
set 	AT91C_UDPHS_SPEED_CFG_RS                   0x1
set 	AT91C_UDPHS_SPEED_CFG_HS                   0x2
set 	AT91C_UDPHS_SPEED_CFG_FS                   0x3
set AT91C_UDPHS_TST_J     [expr 0x1 <<  2 ]
set AT91C_UDPHS_TST_K     [expr 0x1 <<  3 ]
set AT91C_UDPHS_TST_PKT   [expr 0x1 <<  4 ]
set AT91C_UDPHS_OPMODE2   [expr 0x1 <<  5 ]
# -------- UDPHS_RIPPADDRSIZE : (UDPHS Offset: 0xec) UDPHS PADDRSIZE Register -------- 
set AT91C_UDPHS_IPPADDRSIZE [expr 0x0 <<  0 ]
# -------- UDPHS_RIPNAME1 : (UDPHS Offset: 0xf0) UDPHS Name Register -------- 
set AT91C_UDPHS_IPNAME1   [expr 0x0 <<  0 ]
# -------- UDPHS_RIPNAME2 : (UDPHS Offset: 0xf4) UDPHS Name Register -------- 
set AT91C_UDPHS_IPNAME2   [expr 0x0 <<  0 ]
# -------- UDPHS_IPFEATURES : (UDPHS Offset: 0xf8) UDPHS Features Register -------- 
set AT91C_UDPHS_EPT_NBR_MAX [expr 0xF <<  0 ]
set AT91C_UDPHS_DMA_CHANNEL_NBR [expr 0x7 <<  4 ]
set AT91C_UDPHS_DMA_B_SIZ [expr 0x1 <<  7 ]
set AT91C_UDPHS_DMA_FIFO_WORD_DEPTH [expr 0xF <<  8 ]
set AT91C_UDPHS_FIFO_MAX_SIZE [expr 0x7 << 12 ]
set AT91C_UDPHS_BW_DPRAM  [expr 0x1 << 15 ]
set AT91C_UDPHS_DATAB16_8 [expr 0x1 << 16 ]
set AT91C_UDPHS_ISO_EPT_1 [expr 0x1 << 17 ]
set AT91C_UDPHS_ISO_EPT_2 [expr 0x1 << 18 ]
set AT91C_UDPHS_ISO_EPT_3 [expr 0x1 << 19 ]
set AT91C_UDPHS_ISO_EPT_4 [expr 0x1 << 20 ]
set AT91C_UDPHS_ISO_EPT_5 [expr 0x1 << 21 ]
set AT91C_UDPHS_ISO_EPT_6 [expr 0x1 << 22 ]
set AT91C_UDPHS_ISO_EPT_7 [expr 0x1 << 23 ]
set AT91C_UDPHS_ISO_EPT_8 [expr 0x1 << 24 ]
set AT91C_UDPHS_ISO_EPT_9 [expr 0x1 << 25 ]
set AT91C_UDPHS_ISO_EPT_10 [expr 0x1 << 26 ]
set AT91C_UDPHS_ISO_EPT_11 [expr 0x1 << 27 ]
set AT91C_UDPHS_ISO_EPT_12 [expr 0x1 << 28 ]
set AT91C_UDPHS_ISO_EPT_13 [expr 0x1 << 29 ]
set AT91C_UDPHS_ISO_EPT_14 [expr 0x1 << 30 ]
set AT91C_UDPHS_ISO_EPT_15 [expr 0x1 << 31 ]
# -------- UDPHS_IPVERSION : (UDPHS Offset: 0xfc) UDPHS Version Register -------- 
set AT91C_UDPHS_VERSION_NUM [expr 0xFFFF <<  0 ]
set AT91C_UDPHS_METAL_FIX_NUM [expr 0x7 << 16 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AC97 Controller Interface
# *****************************************************************************
# -------- AC97C_MR : (AC97C Offset: 0x8) AC97C Mode Register -------- 
set AT91C_AC97C_ENA       [expr 0x1 <<  0 ]
set AT91C_AC97C_WRST      [expr 0x1 <<  1 ]
set AT91C_AC97C_VRA       [expr 0x1 <<  2 ]
# -------- AC97C_ICA : (AC97C Offset: 0x10) AC97C Input Channel Assignement Register -------- 
set AT91C_AC97C_CHID3     [expr 0x7 <<  0 ]
set 	AT91C_AC97C_CHID3_NONE                 0x0
set 	AT91C_AC97C_CHID3_CA                   0x1
set 	AT91C_AC97C_CHID3_CB                   0x2
set 	AT91C_AC97C_CHID3_CC                   0x3
set AT91C_AC97C_CHID4     [expr 0x7 <<  3 ]
set 	AT91C_AC97C_CHID4_NONE                 [expr 0x0 <<  3 ]
set 	AT91C_AC97C_CHID4_CA                   [expr 0x1 <<  3 ]
set 	AT91C_AC97C_CHID4_CB                   [expr 0x2 <<  3 ]
set 	AT91C_AC97C_CHID4_CC                   [expr 0x3 <<  3 ]
set AT91C_AC97C_CHID5     [expr 0x7 <<  6 ]
set 	AT91C_AC97C_CHID5_NONE                 [expr 0x0 <<  6 ]
set 	AT91C_AC97C_CHID5_CA                   [expr 0x1 <<  6 ]
set 	AT91C_AC97C_CHID5_CB                   [expr 0x2 <<  6 ]
set 	AT91C_AC97C_CHID5_CC                   [expr 0x3 <<  6 ]
set AT91C_AC97C_CHID6     [expr 0x7 <<  9 ]
set 	AT91C_AC97C_CHID6_NONE                 [expr 0x0 <<  9 ]
set 	AT91C_AC97C_CHID6_CA                   [expr 0x1 <<  9 ]
set 	AT91C_AC97C_CHID6_CB                   [expr 0x2 <<  9 ]
set 	AT91C_AC97C_CHID6_CC                   [expr 0x3 <<  9 ]
set AT91C_AC97C_CHID7     [expr 0x7 << 12 ]
set 	AT91C_AC97C_CHID7_NONE                 [expr 0x0 << 12 ]
set 	AT91C_AC97C_CHID7_CA                   [expr 0x1 << 12 ]
set 	AT91C_AC97C_CHID7_CB                   [expr 0x2 << 12 ]
set 	AT91C_AC97C_CHID7_CC                   [expr 0x3 << 12 ]
set AT91C_AC97C_CHID8     [expr 0x7 << 15 ]
set 	AT91C_AC97C_CHID8_NONE                 [expr 0x0 << 15 ]
set 	AT91C_AC97C_CHID8_CA                   [expr 0x1 << 15 ]
set 	AT91C_AC97C_CHID8_CB                   [expr 0x2 << 15 ]
set 	AT91C_AC97C_CHID8_CC                   [expr 0x3 << 15 ]
set AT91C_AC97C_CHID9     [expr 0x7 << 18 ]
set 	AT91C_AC97C_CHID9_NONE                 [expr 0x0 << 18 ]
set 	AT91C_AC97C_CHID9_CA                   [expr 0x1 << 18 ]
set 	AT91C_AC97C_CHID9_CB                   [expr 0x2 << 18 ]
set 	AT91C_AC97C_CHID9_CC                   [expr 0x3 << 18 ]
set AT91C_AC97C_CHID10    [expr 0x7 << 21 ]
set 	AT91C_AC97C_CHID10_NONE                 [expr 0x0 << 21 ]
set 	AT91C_AC97C_CHID10_CA                   [expr 0x1 << 21 ]
set 	AT91C_AC97C_CHID10_CB                   [expr 0x2 << 21 ]
set 	AT91C_AC97C_CHID10_CC                   [expr 0x3 << 21 ]
set AT91C_AC97C_CHID11    [expr 0x7 << 24 ]
set 	AT91C_AC97C_CHID11_NONE                 [expr 0x0 << 24 ]
set 	AT91C_AC97C_CHID11_CA                   [expr 0x1 << 24 ]
set 	AT91C_AC97C_CHID11_CB                   [expr 0x2 << 24 ]
set 	AT91C_AC97C_CHID11_CC                   [expr 0x3 << 24 ]
set AT91C_AC97C_CHID12    [expr 0x7 << 27 ]
set 	AT91C_AC97C_CHID12_NONE                 [expr 0x0 << 27 ]
set 	AT91C_AC97C_CHID12_CA                   [expr 0x1 << 27 ]
set 	AT91C_AC97C_CHID12_CB                   [expr 0x2 << 27 ]
set 	AT91C_AC97C_CHID12_CC                   [expr 0x3 << 27 ]
# -------- AC97C_OCA : (AC97C Offset: 0x14) AC97C Output Channel Assignement Register -------- 
set AT91C_AC97C_CHID3     [expr 0x7 <<  0 ]
set 	AT91C_AC97C_CHID3_NONE                 0x0
set 	AT91C_AC97C_CHID3_CA                   0x1
set 	AT91C_AC97C_CHID3_CB                   0x2
set 	AT91C_AC97C_CHID3_CC                   0x3
set AT91C_AC97C_CHID4     [expr 0x7 <<  3 ]
set 	AT91C_AC97C_CHID4_NONE                 [expr 0x0 <<  3 ]
set 	AT91C_AC97C_CHID4_CA                   [expr 0x1 <<  3 ]
set 	AT91C_AC97C_CHID4_CB                   [expr 0x2 <<  3 ]
set 	AT91C_AC97C_CHID4_CC                   [expr 0x3 <<  3 ]
set AT91C_AC97C_CHID5     [expr 0x7 <<  6 ]
set 	AT91C_AC97C_CHID5_NONE                 [expr 0x0 <<  6 ]
set 	AT91C_AC97C_CHID5_CA                   [expr 0x1 <<  6 ]
set 	AT91C_AC97C_CHID5_CB                   [expr 0x2 <<  6 ]
set 	AT91C_AC97C_CHID5_CC                   [expr 0x3 <<  6 ]
set AT91C_AC97C_CHID6     [expr 0x7 <<  9 ]
set 	AT91C_AC97C_CHID6_NONE                 [expr 0x0 <<  9 ]
set 	AT91C_AC97C_CHID6_CA                   [expr 0x1 <<  9 ]
set 	AT91C_AC97C_CHID6_CB                   [expr 0x2 <<  9 ]
set 	AT91C_AC97C_CHID6_CC                   [expr 0x3 <<  9 ]
set AT91C_AC97C_CHID7     [expr 0x7 << 12 ]
set 	AT91C_AC97C_CHID7_NONE                 [expr 0x0 << 12 ]
set 	AT91C_AC97C_CHID7_CA                   [expr 0x1 << 12 ]
set 	AT91C_AC97C_CHID7_CB                   [expr 0x2 << 12 ]
set 	AT91C_AC97C_CHID7_CC                   [expr 0x3 << 12 ]
set AT91C_AC97C_CHID8     [expr 0x7 << 15 ]
set 	AT91C_AC97C_CHID8_NONE                 [expr 0x0 << 15 ]
set 	AT91C_AC97C_CHID8_CA                   [expr 0x1 << 15 ]
set 	AT91C_AC97C_CHID8_CB                   [expr 0x2 << 15 ]
set 	AT91C_AC97C_CHID8_CC                   [expr 0x3 << 15 ]
set AT91C_AC97C_CHID9     [expr 0x7 << 18 ]
set 	AT91C_AC97C_CHID9_NONE                 [expr 0x0 << 18 ]
set 	AT91C_AC97C_CHID9_CA                   [expr 0x1 << 18 ]
set 	AT91C_AC97C_CHID9_CB                   [expr 0x2 << 18 ]
set 	AT91C_AC97C_CHID9_CC                   [expr 0x3 << 18 ]
set AT91C_AC97C_CHID10    [expr 0x7 << 21 ]
set 	AT91C_AC97C_CHID10_NONE                 [expr 0x0 << 21 ]
set 	AT91C_AC97C_CHID10_CA                   [expr 0x1 << 21 ]
set 	AT91C_AC97C_CHID10_CB                   [expr 0x2 << 21 ]
set 	AT91C_AC97C_CHID10_CC                   [expr 0x3 << 21 ]
set AT91C_AC97C_CHID11    [expr 0x7 << 24 ]
set 	AT91C_AC97C_CHID11_NONE                 [expr 0x0 << 24 ]
set 	AT91C_AC97C_CHID11_CA                   [expr 0x1 << 24 ]
set 	AT91C_AC97C_CHID11_CB                   [expr 0x2 << 24 ]
set 	AT91C_AC97C_CHID11_CC                   [expr 0x3 << 24 ]
set AT91C_AC97C_CHID12    [expr 0x7 << 27 ]
set 	AT91C_AC97C_CHID12_NONE                 [expr 0x0 << 27 ]
set 	AT91C_AC97C_CHID12_CA                   [expr 0x1 << 27 ]
set 	AT91C_AC97C_CHID12_CB                   [expr 0x2 << 27 ]
set 	AT91C_AC97C_CHID12_CC                   [expr 0x3 << 27 ]
# -------- AC97C_CARHR : (AC97C Offset: 0x20) AC97C Channel A Receive Holding Register -------- 
set AT91C_AC97C_RDATA     [expr 0xFFFFF <<  0 ]
# -------- AC97C_CATHR : (AC97C Offset: 0x24) AC97C Channel A Transmit Holding Register -------- 
set AT91C_AC97C_TDATA     [expr 0xFFFFF <<  0 ]
# -------- AC97C_CASR : (AC97C Offset: 0x28) AC97C Channel A Status Register -------- 
set AT91C_AC97C_TXRDY     [expr 0x1 <<  0 ]
set AT91C_AC97C_TXEMPTY   [expr 0x1 <<  1 ]
set AT91C_AC97C_UNRUN     [expr 0x1 <<  2 ]
set AT91C_AC97C_RXRDY     [expr 0x1 <<  4 ]
set AT91C_AC97C_OVRUN     [expr 0x1 <<  5 ]
set AT91C_AC97C_ENDTX     [expr 0x1 << 10 ]
set AT91C_AC97C_TXBUFE    [expr 0x1 << 11 ]
set AT91C_AC97C_ENDRX     [expr 0x1 << 14 ]
set AT91C_AC97C_RXBUFF    [expr 0x1 << 15 ]
# -------- AC97C_CAMR : (AC97C Offset: 0x2c) AC97C Channel A Mode Register -------- 
set AT91C_AC97C_TXRDY     [expr 0x1 <<  0 ]
set AT91C_AC97C_TXEMPTY   [expr 0x1 <<  1 ]
set AT91C_AC97C_UNRUN     [expr 0x1 <<  2 ]
set AT91C_AC97C_RXRDY     [expr 0x1 <<  4 ]
set AT91C_AC97C_OVRUN     [expr 0x1 <<  5 ]
set AT91C_AC97C_ENDTX     [expr 0x1 << 10 ]
set AT91C_AC97C_TXBUFE    [expr 0x1 << 11 ]
set AT91C_AC97C_ENDRX     [expr 0x1 << 14 ]
set AT91C_AC97C_RXBUFF    [expr 0x1 << 15 ]
set AT91C_AC97C_SIZE      [expr 0x3 << 16 ]
set 	AT91C_AC97C_SIZE_20_BITS              [expr 0x0 << 16 ]
set 	AT91C_AC97C_SIZE_18_BITS              [expr 0x1 << 16 ]
set 	AT91C_AC97C_SIZE_16_BITS              [expr 0x2 << 16 ]
set 	AT91C_AC97C_SIZE_10_BITS              [expr 0x3 << 16 ]
set AT91C_AC97C_CEM       [expr 0x1 << 18 ]
set AT91C_AC97C_CEN       [expr 0x1 << 21 ]
set AT91C_AC97C_PDCEN     [expr 0x1 << 22 ]
# -------- AC97C_CBRHR : (AC97C Offset: 0x30) AC97C Channel B Receive Holding Register -------- 
set AT91C_AC97C_RDATA     [expr 0xFFFFF <<  0 ]
# -------- AC97C_CBTHR : (AC97C Offset: 0x34) AC97C Channel B Transmit Holding Register -------- 
set AT91C_AC97C_TDATA     [expr 0xFFFFF <<  0 ]
# -------- AC97C_CBSR : (AC97C Offset: 0x38) AC97C Channel B Status Register -------- 
set AT91C_AC97C_TXRDY     [expr 0x1 <<  0 ]
set AT91C_AC97C_TXEMPTY   [expr 0x1 <<  1 ]
set AT91C_AC97C_UNRUN     [expr 0x1 <<  2 ]
set AT91C_AC97C_RXRDY     [expr 0x1 <<  4 ]
set AT91C_AC97C_OVRUN     [expr 0x1 <<  5 ]
# -------- AC97C_CBMR : (AC97C Offset: 0x3c) AC97C Channel B Mode Register -------- 
set AT91C_AC97C_TXRDY     [expr 0x1 <<  0 ]
set AT91C_AC97C_TXEMPTY   [expr 0x1 <<  1 ]
set AT91C_AC97C_UNRUN     [expr 0x1 <<  2 ]
set AT91C_AC97C_RXRDY     [expr 0x1 <<  4 ]
set AT91C_AC97C_OVRUN     [expr 0x1 <<  5 ]
set AT91C_AC97C_SIZE      [expr 0x3 << 16 ]
set 	AT91C_AC97C_SIZE_20_BITS              [expr 0x0 << 16 ]
set 	AT91C_AC97C_SIZE_18_BITS              [expr 0x1 << 16 ]
set 	AT91C_AC97C_SIZE_16_BITS              [expr 0x2 << 16 ]
set 	AT91C_AC97C_SIZE_10_BITS              [expr 0x3 << 16 ]
set AT91C_AC97C_CEM       [expr 0x1 << 18 ]
set AT91C_AC97C_CEN       [expr 0x1 << 21 ]
# -------- AC97C_CORHR : (AC97C Offset: 0x40) AC97C Codec Channel Receive Holding Register -------- 
set AT91C_AC97C_SDATA     [expr 0xFFFF <<  0 ]
# -------- AC97C_COTHR : (AC97C Offset: 0x44) AC97C Codec Channel Transmit Holding Register -------- 
set AT91C_AC97C_CDATA     [expr 0xFFFF <<  0 ]
set AT91C_AC97C_CADDR     [expr 0x7F << 16 ]
set AT91C_AC97C_READ      [expr 0x1 << 23 ]
# -------- AC97C_COSR : (AC97C Offset: 0x48) AC97C CODEC Status Register -------- 
set AT91C_AC97C_TXRDY     [expr 0x1 <<  0 ]
set AT91C_AC97C_TXEMPTY   [expr 0x1 <<  1 ]
set AT91C_AC97C_UNRUN     [expr 0x1 <<  2 ]
set AT91C_AC97C_RXRDY     [expr 0x1 <<  4 ]
# -------- AC97C_COMR : (AC97C Offset: 0x4c) AC97C CODEC Mode Register -------- 
set AT91C_AC97C_TXRDY     [expr 0x1 <<  0 ]
set AT91C_AC97C_TXEMPTY   [expr 0x1 <<  1 ]
set AT91C_AC97C_UNRUN     [expr 0x1 <<  2 ]
set AT91C_AC97C_RXRDY     [expr 0x1 <<  4 ]
# -------- AC97C_SR : (AC97C Offset: 0x50) AC97C Status Register -------- 
set AT91C_AC97C_SOF       [expr 0x1 <<  0 ]
set AT91C_AC97C_WKUP      [expr 0x1 <<  1 ]
set AT91C_AC97C_COEVT     [expr 0x1 <<  2 ]
set AT91C_AC97C_CAEVT     [expr 0x1 <<  3 ]
set AT91C_AC97C_CBEVT     [expr 0x1 <<  4 ]
# -------- AC97C_IER : (AC97C Offset: 0x54) AC97C Interrupt Enable Register -------- 
set AT91C_AC97C_SOF       [expr 0x1 <<  0 ]
set AT91C_AC97C_WKUP      [expr 0x1 <<  1 ]
set AT91C_AC97C_COEVT     [expr 0x1 <<  2 ]
set AT91C_AC97C_CAEVT     [expr 0x1 <<  3 ]
set AT91C_AC97C_CBEVT     [expr 0x1 <<  4 ]
# -------- AC97C_IDR : (AC97C Offset: 0x58) AC97C Interrupt Disable Register -------- 
set AT91C_AC97C_SOF       [expr 0x1 <<  0 ]
set AT91C_AC97C_WKUP      [expr 0x1 <<  1 ]
set AT91C_AC97C_COEVT     [expr 0x1 <<  2 ]
set AT91C_AC97C_CAEVT     [expr 0x1 <<  3 ]
set AT91C_AC97C_CBEVT     [expr 0x1 <<  4 ]
# -------- AC97C_IMR : (AC97C Offset: 0x5c) AC97C Interrupt Mask Register -------- 
set AT91C_AC97C_SOF       [expr 0x1 <<  0 ]
set AT91C_AC97C_WKUP      [expr 0x1 <<  1 ]
set AT91C_AC97C_COEVT     [expr 0x1 <<  2 ]
set AT91C_AC97C_CAEVT     [expr 0x1 <<  3 ]
set AT91C_AC97C_CBEVT     [expr 0x1 <<  4 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR LCD Controller
# *****************************************************************************
# -------- LCDC_FRMP1 : (LCDC Offset: 0x8) DMA Frame Pointer 1 Register -------- 
set AT91C_LCDC_FRMPT1     [expr 0x3FFFFF <<  0 ]
# -------- LCDC_FRMP2 : (LCDC Offset: 0xc) DMA Frame Pointer 2 Register -------- 
set AT91C_LCDC_FRMPT2     [expr 0x1FFFFF <<  0 ]
# -------- LCDC_FRMCFG : (LCDC Offset: 0x18) DMA Frame Config Register -------- 
set AT91C_LCDC_FRSIZE     [expr 0x3FFFFF <<  0 ]
set AT91C_LCDC_BLENGTH    [expr 0xF << 24 ]
# -------- LCDC_DMACON : (LCDC Offset: 0x1c) DMA Control Register -------- 
set AT91C_LCDC_DMAEN      [expr 0x1 <<  0 ]
set AT91C_LCDC_DMARST     [expr 0x1 <<  1 ]
set AT91C_LCDC_DMABUSY    [expr 0x1 <<  2 ]
set AT91C_LCDC_DMAUPDT    [expr 0x1 <<  3 ]
set AT91C_LCDC_DMA2DEN    [expr 0x1 <<  4 ]
# -------- LCDC_DMA2DCFG : (LCDC Offset: 0x20) DMA 2D addressing configuration Register -------- 
set AT91C_LCDC_ADDRINC    [expr 0xFFFF <<  0 ]
set AT91C_LCDC_PIXELOFF   [expr 0x1F << 24 ]
# -------- LCDC_LCDCON1 : (LCDC Offset: 0x800) LCD Control 1 Register -------- 
set AT91C_LCDC_BYPASS     [expr 0x1 <<  0 ]
set AT91C_LCDC_CLKVAL     [expr 0x1FF << 12 ]
set AT91C_LCDC_LINCNT     [expr 0x7FF << 21 ]
# -------- LCDC_LCDCON2 : (LCDC Offset: 0x804) LCD Control 2 Register -------- 
set AT91C_LCDC_DISTYPE    [expr 0x3 <<  0 ]
set 	AT91C_LCDC_DISTYPE_STNMONO              0x0
set 	AT91C_LCDC_DISTYPE_STNCOLOR             0x1
set 	AT91C_LCDC_DISTYPE_TFT                  0x2
set AT91C_LCDC_SCANMOD    [expr 0x1 <<  2 ]
set 	AT91C_LCDC_SCANMOD_SINGLESCAN           [expr 0x0 <<  2 ]
set 	AT91C_LCDC_SCANMOD_DUALSCAN             [expr 0x1 <<  2 ]
set AT91C_LCDC_IFWIDTH    [expr 0x3 <<  3 ]
set 	AT91C_LCDC_IFWIDTH_FOURBITSWIDTH        [expr 0x0 <<  3 ]
set 	AT91C_LCDC_IFWIDTH_EIGTHBITSWIDTH       [expr 0x1 <<  3 ]
set 	AT91C_LCDC_IFWIDTH_SIXTEENBITSWIDTH     [expr 0x2 <<  3 ]
set AT91C_LCDC_PIXELSIZE  [expr 0x7 <<  5 ]
set 	AT91C_LCDC_PIXELSIZE_ONEBITSPERPIXEL      [expr 0x0 <<  5 ]
set 	AT91C_LCDC_PIXELSIZE_TWOBITSPERPIXEL      [expr 0x1 <<  5 ]
set 	AT91C_LCDC_PIXELSIZE_FOURBITSPERPIXEL     [expr 0x2 <<  5 ]
set 	AT91C_LCDC_PIXELSIZE_EIGTHBITSPERPIXEL    [expr 0x3 <<  5 ]
set 	AT91C_LCDC_PIXELSIZE_SIXTEENBITSPERPIXEL  [expr 0x4 <<  5 ]
set 	AT91C_LCDC_PIXELSIZE_TWENTYFOURBITSPERPIXEL [expr 0x5 <<  5 ]
set AT91C_LCDC_INVVD      [expr 0x1 <<  8 ]
set 	AT91C_LCDC_INVVD_NORMALPOL            [expr 0x0 <<  8 ]
set 	AT91C_LCDC_INVVD_INVERTEDPOL          [expr 0x1 <<  8 ]
set AT91C_LCDC_INVFRAME   [expr 0x1 <<  9 ]
set 	AT91C_LCDC_INVFRAME_NORMALPOL            [expr 0x0 <<  9 ]
set 	AT91C_LCDC_INVFRAME_INVERTEDPOL          [expr 0x1 <<  9 ]
set AT91C_LCDC_INVLINE    [expr 0x1 << 10 ]
set 	AT91C_LCDC_INVLINE_NORMALPOL            [expr 0x0 << 10 ]
set 	AT91C_LCDC_INVLINE_INVERTEDPOL          [expr 0x1 << 10 ]
set AT91C_LCDC_INVCLK     [expr 0x1 << 11 ]
set 	AT91C_LCDC_INVCLK_NORMALPOL            [expr 0x0 << 11 ]
set 	AT91C_LCDC_INVCLK_INVERTEDPOL          [expr 0x1 << 11 ]
set AT91C_LCDC_INVDVAL    [expr 0x1 << 12 ]
set 	AT91C_LCDC_INVDVAL_NORMALPOL            [expr 0x0 << 12 ]
set 	AT91C_LCDC_INVDVAL_INVERTEDPOL          [expr 0x1 << 12 ]
set AT91C_LCDC_CLKMOD     [expr 0x1 << 15 ]
set 	AT91C_LCDC_CLKMOD_ACTIVEONLYDISP       [expr 0x0 << 15 ]
set 	AT91C_LCDC_CLKMOD_ALWAYSACTIVE         [expr 0x1 << 15 ]
set AT91C_LCDC_MEMOR      [expr 0x1 << 31 ]
set 	AT91C_LCDC_MEMOR_BIGIND               [expr 0x0 << 31 ]
set 	AT91C_LCDC_MEMOR_LITTLEIND            [expr 0x1 << 31 ]
# -------- LCDC_TIM1 : (LCDC Offset: 0x808) LCDC Timing Config 1 Register -------- 
set AT91C_LCDC_VFP        [expr 0xFF <<  0 ]
set AT91C_LCDC_VBP        [expr 0xFF <<  8 ]
set AT91C_LCDC_VPW        [expr 0x3F << 16 ]
set AT91C_LCDC_VHDLY      [expr 0xF << 24 ]
# -------- LCDC_TIM2 : (LCDC Offset: 0x80c) LCDC Timing Config 2 Register -------- 
set AT91C_LCDC_HBP        [expr 0xFF <<  0 ]
set AT91C_LCDC_HPW        [expr 0x3F <<  8 ]
set AT91C_LCDC_HFP        [expr 0x3FF << 22 ]
# -------- LCDC_LCDFRCFG : (LCDC Offset: 0x810) LCD Frame Config Register -------- 
set AT91C_LCDC_LINEVAL    [expr 0x7FF <<  0 ]
set AT91C_LCDC_HOZVAL     [expr 0x7FF << 21 ]
# -------- LCDC_FIFO : (LCDC Offset: 0x814) LCD FIFO Register -------- 
set AT91C_LCDC_FIFOTH     [expr 0xFFFF <<  0 ]
# -------- LCDC_MVAL : (LCDC Offset: 0x818) LCD Mode Toggle Rate Value Register -------- 
set AT91C_LCDC_MVALUE     [expr 0xFF <<  0 ]
set AT91C_LCDC_MMODE      [expr 0x1 << 31 ]
set 	AT91C_LCDC_MMODE_EACHFRAME            [expr 0x0 << 31 ]
set 	AT91C_LCDC_MMODE_MVALDEFINED          [expr 0x1 << 31 ]
# -------- LCDC_DP1_2 : (LCDC Offset: 0x81c) Dithering Pattern 1/2 -------- 
set AT91C_LCDC_DP1_2_FIELD [expr 0xFF <<  0 ]
# -------- LCDC_DP4_7 : (LCDC Offset: 0x820) Dithering Pattern 4/7 -------- 
set AT91C_LCDC_DP4_7_FIELD [expr 0xFFFFFFF <<  0 ]
# -------- LCDC_DP3_5 : (LCDC Offset: 0x824) Dithering Pattern 3/5 -------- 
set AT91C_LCDC_DP3_5_FIELD [expr 0xFFFFF <<  0 ]
# -------- LCDC_DP2_3 : (LCDC Offset: 0x828) Dithering Pattern 2/3 -------- 
set AT91C_LCDC_DP2_3_FIELD [expr 0xFFF <<  0 ]
# -------- LCDC_DP5_7 : (LCDC Offset: 0x82c) Dithering Pattern 5/7 -------- 
set AT91C_LCDC_DP5_7_FIELD [expr 0xFFFFFFF <<  0 ]
# -------- LCDC_DP3_4 : (LCDC Offset: 0x830) Dithering Pattern 3/4 -------- 
set AT91C_LCDC_DP3_4_FIELD [expr 0xFFFF <<  0 ]
# -------- LCDC_DP4_5 : (LCDC Offset: 0x834) Dithering Pattern 4/5 -------- 
set AT91C_LCDC_DP4_5_FIELD [expr 0xFFFFF <<  0 ]
# -------- LCDC_DP6_7 : (LCDC Offset: 0x838) Dithering Pattern 6/7 -------- 
set AT91C_LCDC_DP6_7_FIELD [expr 0xFFFFFFF <<  0 ]
# -------- LCDC_PWRCON : (LCDC Offset: 0x83c) LCDC Power Control Register -------- 
set AT91C_LCDC_PWR        [expr 0x1 <<  0 ]
set AT91C_LCDC_GUARDT     [expr 0x7F <<  1 ]
set AT91C_LCDC_BUSY       [expr 0x1 << 31 ]
set 	AT91C_LCDC_BUSY_LCDNOTBUSY           [expr 0x0 << 31 ]
set 	AT91C_LCDC_BUSY_LCDBUSY              [expr 0x1 << 31 ]
# -------- LCDC_CTRSTCON : (LCDC Offset: 0x840) LCDC Contrast Control Register -------- 
set AT91C_LCDC_PS         [expr 0x3 <<  0 ]
set 	AT91C_LCDC_PS_NOTDIVIDED           0x0
set 	AT91C_LCDC_PS_DIVIDEDBYTWO         0x1
set 	AT91C_LCDC_PS_DIVIDEDBYFOUR        0x2
set 	AT91C_LCDC_PS_DIVIDEDBYEIGHT       0x3
set AT91C_LCDC_POL        [expr 0x1 <<  2 ]
set 	AT91C_LCDC_POL_NEGATIVEPULSE        [expr 0x0 <<  2 ]
set 	AT91C_LCDC_POL_POSITIVEPULSE        [expr 0x1 <<  2 ]
set AT91C_LCDC_ENA        [expr 0x1 <<  3 ]
set 	AT91C_LCDC_ENA_PWMGEMDISABLED       [expr 0x0 <<  3 ]
set 	AT91C_LCDC_ENA_PWMGEMENABLED        [expr 0x1 <<  3 ]
# -------- LCDC_CTRSTVAL : (LCDC Offset: 0x844) Contrast Value Register -------- 
set AT91C_LCDC_CVAL       [expr 0xFF <<  0 ]
# -------- LCDC_IER : (LCDC Offset: 0x848) LCDC Interrupt Enable Register -------- 
set AT91C_LCDC_LNI        [expr 0x1 <<  0 ]
set AT91C_LCDC_LSTLNI     [expr 0x1 <<  1 ]
set AT91C_LCDC_EOFI       [expr 0x1 <<  2 ]
set AT91C_LCDC_UFLWI      [expr 0x1 <<  4 ]
set AT91C_LCDC_OWRI       [expr 0x1 <<  5 ]
set AT91C_LCDC_MERI       [expr 0x1 <<  6 ]
# -------- LCDC_IDR : (LCDC Offset: 0x84c) LCDC Interrupt Disable Register -------- 
set AT91C_LCDC_LNI        [expr 0x1 <<  0 ]
set AT91C_LCDC_LSTLNI     [expr 0x1 <<  1 ]
set AT91C_LCDC_EOFI       [expr 0x1 <<  2 ]
set AT91C_LCDC_UFLWI      [expr 0x1 <<  4 ]
set AT91C_LCDC_OWRI       [expr 0x1 <<  5 ]
set AT91C_LCDC_MERI       [expr 0x1 <<  6 ]
# -------- LCDC_IMR : (LCDC Offset: 0x850) LCDC Interrupt Mask Register -------- 
set AT91C_LCDC_LNI        [expr 0x1 <<  0 ]
set AT91C_LCDC_LSTLNI     [expr 0x1 <<  1 ]
set AT91C_LCDC_EOFI       [expr 0x1 <<  2 ]
set AT91C_LCDC_UFLWI      [expr 0x1 <<  4 ]
set AT91C_LCDC_OWRI       [expr 0x1 <<  5 ]
set AT91C_LCDC_MERI       [expr 0x1 <<  6 ]
# -------- LCDC_ISR : (LCDC Offset: 0x854) LCDC Interrupt Status Register -------- 
set AT91C_LCDC_LNI        [expr 0x1 <<  0 ]
set AT91C_LCDC_LSTLNI     [expr 0x1 <<  1 ]
set AT91C_LCDC_EOFI       [expr 0x1 <<  2 ]
set AT91C_LCDC_UFLWI      [expr 0x1 <<  4 ]
set AT91C_LCDC_OWRI       [expr 0x1 <<  5 ]
set AT91C_LCDC_MERI       [expr 0x1 <<  6 ]
# -------- LCDC_ICR : (LCDC Offset: 0x858) LCDC Interrupt Clear Register -------- 
set AT91C_LCDC_LNI        [expr 0x1 <<  0 ]
set AT91C_LCDC_LSTLNI     [expr 0x1 <<  1 ]
set AT91C_LCDC_EOFI       [expr 0x1 <<  2 ]
set AT91C_LCDC_UFLWI      [expr 0x1 <<  4 ]
set AT91C_LCDC_OWRI       [expr 0x1 <<  5 ]
set AT91C_LCDC_MERI       [expr 0x1 <<  6 ]
# -------- LCDC_GPR : (LCDC Offset: 0x85c) LCDC General Purpose Register -------- 
set AT91C_LCDC_GPRBUS     [expr 0xFF <<  0 ]
# -------- LCDC_ITR : (LCDC Offset: 0x860) Interrupts Test Register -------- 
set AT91C_LCDC_LNI        [expr 0x1 <<  0 ]
set AT91C_LCDC_LSTLNI     [expr 0x1 <<  1 ]
set AT91C_LCDC_EOFI       [expr 0x1 <<  2 ]
set AT91C_LCDC_UFLWI      [expr 0x1 <<  4 ]
set AT91C_LCDC_OWRI       [expr 0x1 <<  5 ]
set AT91C_LCDC_MERI       [expr 0x1 <<  6 ]
# -------- LCDC_IRR : (LCDC Offset: 0x864) Interrupts Raw Status Register -------- 
set AT91C_LCDC_LNI        [expr 0x1 <<  0 ]
set AT91C_LCDC_LSTLNI     [expr 0x1 <<  1 ]
set AT91C_LCDC_EOFI       [expr 0x1 <<  2 ]
set AT91C_LCDC_UFLWI      [expr 0x1 <<  4 ]
set AT91C_LCDC_OWRI       [expr 0x1 <<  5 ]
set AT91C_LCDC_MERI       [expr 0x1 <<  6 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR HDMA Channel structure
# *****************************************************************************
# -------- HDMA_SADDR : (HDMA_CH Offset: 0x0)  -------- 
set AT91C_SADDR           [expr 0x0 <<  0 ]
# -------- HDMA_DADDR : (HDMA_CH Offset: 0x4)  -------- 
set AT91C_DADDR           [expr 0x0 <<  0 ]
# -------- HDMA_DSCR : (HDMA_CH Offset: 0x8)  -------- 
set AT91C_DSCR_IF         [expr 0x3 <<  0 ]
set AT91C_DSCR            [expr 0x3FFFFFFF <<  2 ]
# -------- HDMA_CTRLA : (HDMA_CH Offset: 0xc)  -------- 
set AT91C_BTSIZE          [expr 0xFFF <<  0 ]
set AT91C_FC              [expr 0x7 << 12 ]
set AT91C_AUTO            [expr 0x1 << 15 ]
set AT91C_SCSIZE          [expr 0x7 << 16 ]
set AT91C_DCSIZE          [expr 0x7 << 20 ]
set AT91C_SRC_WIDTH       [expr 0x3 << 24 ]
set AT91C_DST_WIDTH       [expr 0x3 << 28 ]
# -------- HDMA_CTRLB : (HDMA_CH Offset: 0x10)  -------- 
set AT91C_SIF             [expr 0x3 <<  0 ]
set AT91C_DIF             [expr 0x3 <<  4 ]
set AT91C_SRC_PIP         [expr 0x1 <<  8 ]
set AT91C_DST_PIP         [expr 0x1 << 12 ]
set AT91C_SRC_DSCR        [expr 0x1 << 16 ]
set AT91C_DST_DSCR        [expr 0x1 << 20 ]
set AT91C_SRC_INCR        [expr 0x3 << 24 ]
set AT91C_DST_INCR        [expr 0x3 << 28 ]
# -------- HDMA_CFG : (HDMA_CH Offset: 0x14)  -------- 
set AT91C_SRC_PER         [expr 0xF <<  0 ]
set AT91C_DST_PER         [expr 0xF <<  4 ]
set AT91C_SRC_REP         [expr 0x1 <<  8 ]
set AT91C_SRC_H2SEL       [expr 0x1 <<  9 ]
set AT91C_DST_REP         [expr 0x1 << 12 ]
set AT91C_DST_H2SEL       [expr 0x1 << 13 ]
set AT91C_LOCK_IF         [expr 0x1 << 20 ]
set AT91C_LOCK_B          [expr 0x1 << 21 ]
set AT91C_LOCK_IF_L       [expr 0x1 << 22 ]
set AT91C_AHB_PROT        [expr 0x7 << 24 ]
# -------- HDMA_SPIP : (HDMA_CH Offset: 0x18)  -------- 
set AT91C_SPIP_HOLE       [expr 0xFFFF <<  0 ]
set AT91C_SPIP_BOUNDARY   [expr 0x3FF << 16 ]
# -------- HDMA_DPIP : (HDMA_CH Offset: 0x1c)  -------- 
set AT91C_DPIP_HOLE       [expr 0xFFFF <<  0 ]
set AT91C_DPIP_BOUNDARY   [expr 0x3FF << 16 ]
# -------- HDMA_BDSCR : (HDMA_CH Offset: 0x20)  -------- 
# -------- HDMA_CADDR : (HDMA_CH Offset: 0x24)  -------- 

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR HDMA controller
# *****************************************************************************
# -------- HDMA_GCFG : (HDMA Offset: 0x0)  -------- 
set AT91C_IF0_BIGEND      [expr 0x1 <<  0 ]
set AT91C_IF1_BIGEND      [expr 0x1 <<  1 ]
set AT91C_IF2_BIGEND      [expr 0x1 <<  2 ]
set AT91C_IF3_BIGEND      [expr 0x1 <<  3 ]
set AT91C_ARB_CFG         [expr 0x1 <<  4 ]
# -------- HDMA_EN : (HDMA Offset: 0x4)  -------- 
set AT91C_HDMA_ENABLE     [expr 0x1 <<  0 ]
# -------- HDMA_SREQ : (HDMA Offset: 0x8)  -------- 
set AT91C_SOFT_SREQ       [expr 0xFFFF <<  0 ]
# -------- HDMA_BREQ : (HDMA Offset: 0xc)  -------- 
set AT91C_SOFT_BREQ       [expr 0xFFFF <<  0 ]
# -------- HDMA_LAST : (HDMA Offset: 0x10)  -------- 
set AT91C_SOFT_LAST       [expr 0xFFFF <<  0 ]
# -------- HDMA_SYNC : (HDMA Offset: 0x14)  -------- 
set AT91C_SYNC_REQ        [expr 0xFFFF <<  0 ]
# -------- HDMA_EBCIER : (HDMA Offset: 0x18)  -------- 
set AT91C_BTC             [expr 0xFF <<  0 ]
set AT91C_CBTC            [expr 0xFF <<  8 ]
set AT91C_ERR             [expr 0xFF << 16 ]
# -------- HDMA_EBCIDR : (HDMA Offset: 0x1c)  -------- 
set AT91C_BTC             [expr 0xFF <<  0 ]
set AT91C_CBTC            [expr 0xFF <<  8 ]
set AT91C_ERR             [expr 0xFF << 16 ]
# -------- HDMA_EBCIMR : (HDMA Offset: 0x20)  -------- 
set AT91C_BTC             [expr 0xFF <<  0 ]
set AT91C_CBTC            [expr 0xFF <<  8 ]
set AT91C_ERR             [expr 0xFF << 16 ]
# -------- HDMA_EBCISR : (HDMA Offset: 0x24)  -------- 
set AT91C_BTC             [expr 0xFF <<  0 ]
set AT91C_CBTC            [expr 0xFF <<  8 ]
set AT91C_ERR             [expr 0xFF << 16 ]
# -------- HDMA_CHER : (HDMA Offset: 0x28)  -------- 
set AT91C_ENABLE          [expr 0xFF <<  0 ]
set AT91C_SUSPEND         [expr 0xFF <<  8 ]
set AT91C_KEEPON          [expr 0xFF << 24 ]
# -------- HDMA_CHDR : (HDMA Offset: 0x2c)  -------- 
set AT91C_ENABLE          [expr 0xFF <<  0 ]
set AT91C_RESUME          [expr 0xFF <<  8 ]
# -------- HDMA_CHSR : (HDMA Offset: 0x30)  -------- 
set AT91C_ENABLE          [expr 0xFF <<  0 ]
set AT91C_SUSPEND         [expr 0xFF <<  8 ]
set AT91C_STALLED         [expr 0xFF << 14 ]
set AT91C_EMPTY           [expr 0xFF << 16 ]
# -------- HDMA_RSVD : (HDMA Offset: 0x34)  -------- 
# -------- HDMA_RSVD : (HDMA Offset: 0x38)  -------- 

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Error Correction Code controller
# *****************************************************************************
# -------- ECC_CR : (ECC Offset: 0x0) ECC reset register -------- 
set AT91C_ECC_RST         [expr 0x1 <<  0 ]
# -------- ECC_MR : (ECC Offset: 0x4) ECC page size register -------- 
set AT91C_ECC_PAGE_SIZE   [expr 0x3 <<  0 ]
# -------- ECC_SR : (ECC Offset: 0x8) ECC status register -------- 
set AT91C_ECC_RECERR      [expr 0x1 <<  0 ]
set AT91C_ECC_ECCERR      [expr 0x1 <<  1 ]
set AT91C_ECC_MULERR      [expr 0x1 <<  2 ]
# -------- ECC_PR : (ECC Offset: 0xc) ECC parity register -------- 
set AT91C_ECC_BITADDR     [expr 0xF <<  0 ]
set AT91C_ECC_WORDADDR    [expr 0xFFF <<  4 ]
# -------- ECC_NPR : (ECC Offset: 0x10) ECC N parity register -------- 
set AT91C_ECC_NPARITY     [expr 0xFFFF <<  0 ]
# -------- ECC_VR : (ECC Offset: 0xfc) ECC version register -------- 
set AT91C_ECC_VR          [expr 0xF <<  0 ]

# *****************************************************************************
#               REGISTER ADDRESS DEFINITION FOR AT91SAM9RL64
# *****************************************************************************
# ========== Register definition for SYS peripheral ========== 
set AT91C_SYS_SLCKSEL 0xFFFFFD60
set AT91C_SYS_GPBR  0xFFFFFD50
# ========== Register definition for EBI peripheral ========== 
set AT91C_EBI_DUMMY 0xFFFFE800
# ========== Register definition for SDRAMC peripheral ========== 
set AT91C_SDRAMC_ISR 0xFFFFEA20
set AT91C_SDRAMC_IDR 0xFFFFEA18
set AT91C_SDRAMC_MR 0xFFFFEA00
set AT91C_SDRAMC_CR 0xFFFFEA08
set AT91C_SDRAMC_LPR 0xFFFFEA10
set AT91C_SDRAMC_MDR 0xFFFFEA24
set AT91C_SDRAMC_TR 0xFFFFEA04
set AT91C_SDRAMC_HSR 0xFFFFEA0C
set AT91C_SDRAMC_IER 0xFFFFEA14
set AT91C_SDRAMC_IMR 0xFFFFEA1C
# ========== Register definition for SMC peripheral ========== 
set AT91C_SMC_CYCLE1 0xFFFFEC18
set AT91C_SMC_CTRL7 0xFFFFEC7C
set AT91C_SMC_CTRL2 0xFFFFEC2C
set AT91C_SMC_PULSE2 0xFFFFEC24
set AT91C_SMC_CTRL1 0xFFFFEC1C
set AT91C_SMC_SETUP4 0xFFFFEC40
set AT91C_SMC_CYCLE3 0xFFFFEC38
set AT91C_SMC_SETUP3 0xFFFFEC30
set AT91C_SMC_CYCLE2 0xFFFFEC28
set AT91C_SMC_SETUP2 0xFFFFEC20
set AT91C_SMC_PULSE5 0xFFFFEC54
set AT91C_SMC_CTRL4 0xFFFFEC4C
set AT91C_SMC_PULSE4 0xFFFFEC44
set AT91C_SMC_CTRL3 0xFFFFEC3C
set AT91C_SMC_PULSE3 0xFFFFEC34
set AT91C_SMC_PULSE0 0xFFFFEC04
set AT91C_SMC_CYCLE4 0xFFFFEC48
set AT91C_SMC_SETUP5 0xFFFFEC50
set AT91C_SMC_CYCLE5 0xFFFFEC58
set AT91C_SMC_SETUP6 0xFFFFEC60
set AT91C_SMC_CYCLE6 0xFFFFEC68
set AT91C_SMC_SETUP0 0xFFFFEC00
set AT91C_SMC_CYCLE0 0xFFFFEC08
set AT91C_SMC_SETUP1 0xFFFFEC10
set AT91C_SMC_CTRL5 0xFFFFEC5C
set AT91C_SMC_PULSE6 0xFFFFEC64
set AT91C_SMC_CTRL6 0xFFFFEC6C
set AT91C_SMC_PULSE7 0xFFFFEC74
set AT91C_SMC_CTRL0 0xFFFFEC0C
set AT91C_SMC_PULSE1 0xFFFFEC14
set AT91C_SMC_SETUP7 0xFFFFEC70
set AT91C_SMC_CYCLE7 0xFFFFEC78
# ========== Register definition for MATRIX peripheral ========== 
set AT91C_MATRIX_MCFG1 0xFFFFEE04
set AT91C_MATRIX_MRCR 0xFFFFEF00
set AT91C_MATRIX_PRAS7 0xFFFFEEB8
set AT91C_MATRIX_PRAS5 0xFFFFEEA8
set AT91C_MATRIX_SCFG4 0xFFFFEE50
set AT91C_MATRIX_MCFG2 0xFFFFEE08
set AT91C_MATRIX_PRBS7 0xFFFFEEBC
set AT91C_MATRIX_MCFG6 0xFFFFEE18
set AT91C_MATRIX_PRBS0 0xFFFFEE84
set AT91C_MATRIX_MCFG7 0xFFFFEE1C
set AT91C_MATRIX_PRAS3 0xFFFFEE98
set AT91C_MATRIX_PRAS1 0xFFFFEE88
set AT91C_MATRIX_SCFG0 0xFFFFEE40
set AT91C_MATRIX_PRBS5 0xFFFFEEAC
set AT91C_MATRIX_PRBS3 0xFFFFEE9C
set AT91C_MATRIX_PRBS1 0xFFFFEE8C
set AT91C_MATRIX_SCFG5 0xFFFFEE54
set AT91C_MATRIX_SCFG1 0xFFFFEE44
set AT91C_MATRIX_PRAS4 0xFFFFEEA0
set AT91C_MATRIX_PRAS6 0xFFFFEEB0
set AT91C_MATRIX_SCFG6 0xFFFFEE58
set AT91C_MATRIX_MCFG0 0xFFFFEE00
set AT91C_MATRIX_PRBS6 0xFFFFEEB4
set AT91C_MATRIX_MCFG3 0xFFFFEE0C
set AT91C_MATRIX_MCFG8 0xFFFFEE20
set AT91C_MATRIX_MCFG4 0xFFFFEE10
set AT91C_MATRIX_MCFG5 0xFFFFEE14
set AT91C_MATRIX_PRAS0 0xFFFFEE80
set AT91C_MATRIX_PRAS2 0xFFFFEE90
set AT91C_MATRIX_SCFG2 0xFFFFEE48
set AT91C_MATRIX_PRBS2 0xFFFFEE94
set AT91C_MATRIX_PRBS4 0xFFFFEEA4
set AT91C_MATRIX_SCFG3 0xFFFFEE4C
set AT91C_MATRIX_SCFG7 0xFFFFEE5C
# ========== Register definition for CCFG peripheral ========== 
set AT91C_CCFG_MATRIXVERSION 0xFFFFEFFC
set AT91C_CCFG_EBICSA 0xFFFFEF20
set AT91C_CCFG_UDPHS 0xFFFFEF1C
set AT91C_CCFG_TCMR 0xFFFFEF14
# ========== Register definition for AIC peripheral ========== 
set AT91C_AIC_ICCR  0xFFFFF128
set AT91C_AIC_IECR  0xFFFFF120
set AT91C_AIC_SMR   0xFFFFF000
set AT91C_AIC_ISCR  0xFFFFF12C
set AT91C_AIC_EOICR 0xFFFFF130
set AT91C_AIC_DCR   0xFFFFF138
set AT91C_AIC_FFER  0xFFFFF140
set AT91C_AIC_SVR   0xFFFFF080
set AT91C_AIC_SPU   0xFFFFF134
set AT91C_AIC_FFDR  0xFFFFF144
set AT91C_AIC_FVR   0xFFFFF104
set AT91C_AIC_FFSR  0xFFFFF148
set AT91C_AIC_IMR   0xFFFFF110
set AT91C_AIC_ISR   0xFFFFF108
set AT91C_AIC_IVR   0xFFFFF100
set AT91C_AIC_IDCR  0xFFFFF124
set AT91C_AIC_CISR  0xFFFFF114
set AT91C_AIC_IPR   0xFFFFF10C
# ========== Register definition for PDC_DBGU peripheral ========== 
set AT91C_DBGU_TNCR 0xFFFFF31C
set AT91C_DBGU_RNCR 0xFFFFF314
set AT91C_DBGU_PTCR 0xFFFFF320
set AT91C_DBGU_PTSR 0xFFFFF324
set AT91C_DBGU_RCR  0xFFFFF304
set AT91C_DBGU_TCR  0xFFFFF30C
set AT91C_DBGU_RPR  0xFFFFF300
set AT91C_DBGU_TPR  0xFFFFF308
set AT91C_DBGU_RNPR 0xFFFFF310
set AT91C_DBGU_TNPR 0xFFFFF318
# ========== Register definition for DBGU peripheral ========== 
set AT91C_DBGU_EXID 0xFFFFF244
set AT91C_DBGU_THR  0xFFFFF21C
set AT91C_DBGU_CSR  0xFFFFF214
set AT91C_DBGU_IDR  0xFFFFF20C
set AT91C_DBGU_MR   0xFFFFF204
set AT91C_DBGU_FNTR 0xFFFFF248
set AT91C_DBGU_CIDR 0xFFFFF240
set AT91C_DBGU_BRGR 0xFFFFF220
set AT91C_DBGU_RHR  0xFFFFF218
set AT91C_DBGU_IMR  0xFFFFF210
set AT91C_DBGU_IER  0xFFFFF208
set AT91C_DBGU_CR   0xFFFFF200
# ========== Register definition for PIOA peripheral ========== 
set AT91C_PIOA_IMR  0xFFFFF448
set AT91C_PIOA_IER  0xFFFFF440
set AT91C_PIOA_OWDR 0xFFFFF4A4
set AT91C_PIOA_ISR  0xFFFFF44C
set AT91C_PIOA_PPUDR 0xFFFFF460
set AT91C_PIOA_MDSR 0xFFFFF458
set AT91C_PIOA_MDER 0xFFFFF450
set AT91C_PIOA_PER  0xFFFFF400
set AT91C_PIOA_PSR  0xFFFFF408
set AT91C_PIOA_OER  0xFFFFF410
set AT91C_PIOA_BSR  0xFFFFF474
set AT91C_PIOA_PPUER 0xFFFFF464
set AT91C_PIOA_MDDR 0xFFFFF454
set AT91C_PIOA_PDR  0xFFFFF404
set AT91C_PIOA_ODR  0xFFFFF414
set AT91C_PIOA_IFDR 0xFFFFF424
set AT91C_PIOA_ABSR 0xFFFFF478
set AT91C_PIOA_ASR  0xFFFFF470
set AT91C_PIOA_PPUSR 0xFFFFF468
set AT91C_PIOA_ODSR 0xFFFFF438
set AT91C_PIOA_SODR 0xFFFFF430
set AT91C_PIOA_IFSR 0xFFFFF428
set AT91C_PIOA_IFER 0xFFFFF420
set AT91C_PIOA_OSR  0xFFFFF418
set AT91C_PIOA_IDR  0xFFFFF444
set AT91C_PIOA_PDSR 0xFFFFF43C
set AT91C_PIOA_CODR 0xFFFFF434
set AT91C_PIOA_OWSR 0xFFFFF4A8
set AT91C_PIOA_OWER 0xFFFFF4A0
# ========== Register definition for PIOB peripheral ========== 
set AT91C_PIOB_OWSR 0xFFFFF6A8
set AT91C_PIOB_PPUSR 0xFFFFF668
set AT91C_PIOB_PPUDR 0xFFFFF660
set AT91C_PIOB_MDSR 0xFFFFF658
set AT91C_PIOB_MDER 0xFFFFF650
set AT91C_PIOB_IMR  0xFFFFF648
set AT91C_PIOB_OSR  0xFFFFF618
set AT91C_PIOB_OER  0xFFFFF610
set AT91C_PIOB_PSR  0xFFFFF608
set AT91C_PIOB_PER  0xFFFFF600
set AT91C_PIOB_BSR  0xFFFFF674
set AT91C_PIOB_PPUER 0xFFFFF664
set AT91C_PIOB_IFDR 0xFFFFF624
set AT91C_PIOB_ODR  0xFFFFF614
set AT91C_PIOB_ABSR 0xFFFFF678
set AT91C_PIOB_ASR  0xFFFFF670
set AT91C_PIOB_IFER 0xFFFFF620
set AT91C_PIOB_IFSR 0xFFFFF628
set AT91C_PIOB_SODR 0xFFFFF630
set AT91C_PIOB_ODSR 0xFFFFF638
set AT91C_PIOB_CODR 0xFFFFF634
set AT91C_PIOB_PDSR 0xFFFFF63C
set AT91C_PIOB_OWER 0xFFFFF6A0
set AT91C_PIOB_IER  0xFFFFF640
set AT91C_PIOB_OWDR 0xFFFFF6A4
set AT91C_PIOB_MDDR 0xFFFFF654
set AT91C_PIOB_ISR  0xFFFFF64C
set AT91C_PIOB_IDR  0xFFFFF644
set AT91C_PIOB_PDR  0xFFFFF604
# ========== Register definition for PIOC peripheral ========== 
set AT91C_PIOC_IFDR 0xFFFFF824
set AT91C_PIOC_ODR  0xFFFFF814
set AT91C_PIOC_ABSR 0xFFFFF878
set AT91C_PIOC_SODR 0xFFFFF830
set AT91C_PIOC_IFSR 0xFFFFF828
set AT91C_PIOC_CODR 0xFFFFF834
set AT91C_PIOC_ODSR 0xFFFFF838
set AT91C_PIOC_IER  0xFFFFF840
set AT91C_PIOC_IMR  0xFFFFF848
set AT91C_PIOC_OWDR 0xFFFFF8A4
set AT91C_PIOC_MDDR 0xFFFFF854
set AT91C_PIOC_PDSR 0xFFFFF83C
set AT91C_PIOC_IDR  0xFFFFF844
set AT91C_PIOC_ISR  0xFFFFF84C
set AT91C_PIOC_PDR  0xFFFFF804
set AT91C_PIOC_OWSR 0xFFFFF8A8
set AT91C_PIOC_OWER 0xFFFFF8A0
set AT91C_PIOC_ASR  0xFFFFF870
set AT91C_PIOC_PPUSR 0xFFFFF868
set AT91C_PIOC_PPUDR 0xFFFFF860
set AT91C_PIOC_MDSR 0xFFFFF858
set AT91C_PIOC_MDER 0xFFFFF850
set AT91C_PIOC_IFER 0xFFFFF820
set AT91C_PIOC_OSR  0xFFFFF818
set AT91C_PIOC_OER  0xFFFFF810
set AT91C_PIOC_PSR  0xFFFFF808
set AT91C_PIOC_PER  0xFFFFF800
set AT91C_PIOC_BSR  0xFFFFF874
set AT91C_PIOC_PPUER 0xFFFFF864
# ========== Register definition for PIOD peripheral ========== 
set AT91C_PIOD_PDSR 0xFFFFFA3C
set AT91C_PIOD_CODR 0xFFFFFA34
set AT91C_PIOD_OWER 0xFFFFFAA0
set AT91C_PIOD_MDER 0xFFFFFA50
set AT91C_PIOD_IMR  0xFFFFFA48
set AT91C_PIOD_IER  0xFFFFFA40
set AT91C_PIOD_ODSR 0xFFFFFA38
set AT91C_PIOD_SODR 0xFFFFFA30
set AT91C_PIOD_PER  0xFFFFFA00
set AT91C_PIOD_OWDR 0xFFFFFAA4
set AT91C_PIOD_PPUER 0xFFFFFA64
set AT91C_PIOD_MDDR 0xFFFFFA54
set AT91C_PIOD_ISR  0xFFFFFA4C
set AT91C_PIOD_IDR  0xFFFFFA44
set AT91C_PIOD_PDR  0xFFFFFA04
set AT91C_PIOD_ODR  0xFFFFFA14
set AT91C_PIOD_OWSR 0xFFFFFAA8
set AT91C_PIOD_ABSR 0xFFFFFA78
set AT91C_PIOD_ASR  0xFFFFFA70
set AT91C_PIOD_PPUSR 0xFFFFFA68
set AT91C_PIOD_PPUDR 0xFFFFFA60
set AT91C_PIOD_MDSR 0xFFFFFA58
set AT91C_PIOD_PSR  0xFFFFFA08
set AT91C_PIOD_OER  0xFFFFFA10
set AT91C_PIOD_OSR  0xFFFFFA18
set AT91C_PIOD_IFER 0xFFFFFA20
set AT91C_PIOD_BSR  0xFFFFFA74
set AT91C_PIOD_IFDR 0xFFFFFA24
set AT91C_PIOD_IFSR 0xFFFFFA28
# ========== Register definition for PMC peripheral ========== 
set AT91C_PMC_SCSR  0xFFFFFC08
set AT91C_PMC_SCER  0xFFFFFC00
set AT91C_PMC_IMR   0xFFFFFC6C
set AT91C_PMC_IDR   0xFFFFFC64
set AT91C_PMC_UCKR  0xFFFFFC1C
set AT91C_PMC_PCDR  0xFFFFFC14
set AT91C_PMC_SCDR  0xFFFFFC04
set AT91C_PMC_SR    0xFFFFFC68
set AT91C_PMC_IER   0xFFFFFC60
set AT91C_PMC_MCKR  0xFFFFFC30
set AT91C_PMC_PLLAR 0xFFFFFC28
set AT91C_PMC_MOR   0xFFFFFC20
set AT91C_PMC_PCER  0xFFFFFC10
set AT91C_PMC_PCSR  0xFFFFFC18
set AT91C_PMC_PLLBR 0xFFFFFC2C
set AT91C_PMC_MCFR  0xFFFFFC24
set AT91C_PMC_PCKR  0xFFFFFC40
# ========== Register definition for CKGR peripheral ========== 
set AT91C_CKGR_PLLBR 0xFFFFFC2C
set AT91C_CKGR_MCFR 0xFFFFFC24
set AT91C_CKGR_UCKR 0xFFFFFC1C
set AT91C_CKGR_PLLAR 0xFFFFFC28
set AT91C_CKGR_MOR  0xFFFFFC20
# ========== Register definition for RSTC peripheral ========== 
set AT91C_RSTC_RSR  0xFFFFFD04
set AT91C_RSTC_RMR  0xFFFFFD08
set AT91C_RSTC_RCR  0xFFFFFD00
# ========== Register definition for SHDWC peripheral ========== 
set AT91C_SHDWC_SHMR 0xFFFFFD14
set AT91C_SHDWC_SHSR 0xFFFFFD18
set AT91C_SHDWC_SHCR 0xFFFFFD10
# ========== Register definition for RTTC peripheral ========== 
set AT91C_RTTC_RTSR 0xFFFFFD2C
set AT91C_RTTC_RTAR 0xFFFFFD24
set AT91C_RTTC_RTVR 0xFFFFFD28
set AT91C_RTTC_RTMR 0xFFFFFD20
# ========== Register definition for PITC peripheral ========== 
set AT91C_PITC_PIIR 0xFFFFFD3C
set AT91C_PITC_PISR 0xFFFFFD34
set AT91C_PITC_PIVR 0xFFFFFD38
set AT91C_PITC_PIMR 0xFFFFFD30
# ========== Register definition for WDTC peripheral ========== 
set AT91C_WDTC_WDMR 0xFFFFFD44
set AT91C_WDTC_WDSR 0xFFFFFD48
set AT91C_WDTC_WDCR 0xFFFFFD40
# ========== Register definition for RTC peripheral ========== 
set AT91C_RTC_IMR   0xFFFFFE28
set AT91C_RTC_IER   0xFFFFFE20
set AT91C_RTC_SR    0xFFFFFE18
set AT91C_RTC_TIMALR 0xFFFFFE10
set AT91C_RTC_TIMR  0xFFFFFE08
set AT91C_RTC_CR    0xFFFFFE00
set AT91C_RTC_VER   0xFFFFFE2C
set AT91C_RTC_IDR   0xFFFFFE24
set AT91C_RTC_SCCR  0xFFFFFE1C
set AT91C_RTC_CALALR 0xFFFFFE14
set AT91C_RTC_CALR  0xFFFFFE0C
set AT91C_RTC_MR    0xFFFFFE04
# ========== Register definition for TC0 peripheral ========== 
set AT91C_TC0_IMR   0xFFFA002C
set AT91C_TC0_IER   0xFFFA0024
set AT91C_TC0_RC    0xFFFA001C
set AT91C_TC0_RA    0xFFFA0014
set AT91C_TC0_CMR   0xFFFA0004
set AT91C_TC0_IDR   0xFFFA0028
set AT91C_TC0_SR    0xFFFA0020
set AT91C_TC0_RB    0xFFFA0018
set AT91C_TC0_CV    0xFFFA0010
set AT91C_TC0_CCR   0xFFFA0000
# ========== Register definition for TC1 peripheral ========== 
set AT91C_TC1_IMR   0xFFFA006C
set AT91C_TC1_IER   0xFFFA0064
set AT91C_TC1_RC    0xFFFA005C
set AT91C_TC1_RA    0xFFFA0054
set AT91C_TC1_CMR   0xFFFA0044
set AT91C_TC1_IDR   0xFFFA0068
set AT91C_TC1_SR    0xFFFA0060
set AT91C_TC1_RB    0xFFFA0058
set AT91C_TC1_CV    0xFFFA0050
set AT91C_TC1_CCR   0xFFFA0040
# ========== Register definition for TC2 peripheral ========== 
set AT91C_TC2_IMR   0xFFFA00AC
set AT91C_TC2_IER   0xFFFA00A4
set AT91C_TC2_RC    0xFFFA009C
set AT91C_TC2_RA    0xFFFA0094
set AT91C_TC2_CMR   0xFFFA0084
set AT91C_TC2_IDR   0xFFFA00A8
set AT91C_TC2_SR    0xFFFA00A0
set AT91C_TC2_RB    0xFFFA0098
set AT91C_TC2_CV    0xFFFA0090
set AT91C_TC2_CCR   0xFFFA0080
# ========== Register definition for TCB0 peripheral ========== 
set AT91C_TCB0_BMR  0xFFFA00C4
set AT91C_TCB0_BCR  0xFFFA00C0
# ========== Register definition for TCB1 peripheral ========== 
set AT91C_TCB1_BMR  0xFFFA0104
set AT91C_TCB1_BCR  0xFFFA0100
# ========== Register definition for TCB2 peripheral ========== 
set AT91C_TCB2_BCR  0xFFFA0140
set AT91C_TCB2_BMR  0xFFFA0144
# ========== Register definition for PDC_MCI peripheral ========== 
set AT91C_MCI_PTCR  0xFFFA4120
set AT91C_MCI_TNPR  0xFFFA4118
set AT91C_MCI_RNPR  0xFFFA4110
set AT91C_MCI_TPR   0xFFFA4108
set AT91C_MCI_RPR   0xFFFA4100
set AT91C_MCI_PTSR  0xFFFA4124
set AT91C_MCI_TNCR  0xFFFA411C
set AT91C_MCI_RNCR  0xFFFA4114
set AT91C_MCI_TCR   0xFFFA410C
set AT91C_MCI_RCR   0xFFFA4104
# ========== Register definition for MCI peripheral ========== 
set AT91C_MCI_IMR   0xFFFA404C
set AT91C_MCI_IER   0xFFFA4044
set AT91C_MCI_TDR   0xFFFA4034
set AT91C_MCI_IDR   0xFFFA4048
set AT91C_MCI_SR    0xFFFA4040
set AT91C_MCI_ARGR  0xFFFA4010
set AT91C_MCI_DTOR  0xFFFA4008
set AT91C_MCI_CR    0xFFFA4000
set AT91C_MCI_VR    0xFFFA40FC
set AT91C_MCI_MR    0xFFFA4004
set AT91C_MCI_SDCR  0xFFFA400C
set AT91C_MCI_CMDR  0xFFFA4014
set AT91C_MCI_RDR   0xFFFA4030
set AT91C_MCI_BLKR  0xFFFA4018
set AT91C_MCI_RSPR  0xFFFA4020
# ========== Register definition for PDC_TWI0 peripheral ========== 
set AT91C_TWI0_PTSR 0xFFFA8124
set AT91C_TWI0_TNCR 0xFFFA811C
set AT91C_TWI0_RNCR 0xFFFA8114
set AT91C_TWI0_TCR  0xFFFA810C
set AT91C_TWI0_RCR  0xFFFA8104
set AT91C_TWI0_PTCR 0xFFFA8120
set AT91C_TWI0_TNPR 0xFFFA8118
set AT91C_TWI0_RNPR 0xFFFA8110
set AT91C_TWI0_TPR  0xFFFA8108
set AT91C_TWI0_RPR  0xFFFA8100
# ========== Register definition for TWI0 peripheral ========== 
set AT91C_TWI0_SR   0xFFFA8020
set AT91C_TWI0_CWGR 0xFFFA8010
set AT91C_TWI0_SMR  0xFFFA8008
set AT91C_TWI0_CR   0xFFFA8000
set AT91C_TWI0_THR  0xFFFA8034
set AT91C_TWI0_IMR  0xFFFA802C
set AT91C_TWI0_IER  0xFFFA8024
set AT91C_TWI0_IDR  0xFFFA8028
set AT91C_TWI0_RHR  0xFFFA8030
set AT91C_TWI0_MMR  0xFFFA8004
set AT91C_TWI0_IADR 0xFFFA800C
# ========== Register definition for TWI1 peripheral ========== 
set AT91C_TWI1_THR  0xFFFAC034
set AT91C_TWI1_IMR  0xFFFAC02C
set AT91C_TWI1_IER  0xFFFAC024
set AT91C_TWI1_IADR 0xFFFAC00C
set AT91C_TWI1_MMR  0xFFFAC004
set AT91C_TWI1_RHR  0xFFFAC030
set AT91C_TWI1_IDR  0xFFFAC028
set AT91C_TWI1_SR   0xFFFAC020
set AT91C_TWI1_CWGR 0xFFFAC010
set AT91C_TWI1_SMR  0xFFFAC008
set AT91C_TWI1_CR   0xFFFAC000
# ========== Register definition for PDC_US0 peripheral ========== 
set AT91C_US0_TNCR  0xFFFB011C
set AT91C_US0_RNCR  0xFFFB0114
set AT91C_US0_TCR   0xFFFB010C
set AT91C_US0_RCR   0xFFFB0104
set AT91C_US0_PTCR  0xFFFB0120
set AT91C_US0_TNPR  0xFFFB0118
set AT91C_US0_RNPR  0xFFFB0110
set AT91C_US0_PTSR  0xFFFB0124
set AT91C_US0_RPR   0xFFFB0100
set AT91C_US0_TPR   0xFFFB0108
# ========== Register definition for US0 peripheral ========== 
set AT91C_US0_IF    0xFFFB004C
set AT91C_US0_NER   0xFFFB0044
set AT91C_US0_RTOR  0xFFFB0024
set AT91C_US0_THR   0xFFFB001C
set AT91C_US0_CSR   0xFFFB0014
set AT91C_US0_IDR   0xFFFB000C
set AT91C_US0_MR    0xFFFB0004
set AT91C_US0_MAN   0xFFFB0050
set AT91C_US0_FIDI  0xFFFB0040
set AT91C_US0_TTGR  0xFFFB0028
set AT91C_US0_BRGR  0xFFFB0020
set AT91C_US0_RHR   0xFFFB0018
set AT91C_US0_IMR   0xFFFB0010
set AT91C_US0_IER   0xFFFB0008
set AT91C_US0_CR    0xFFFB0000
# ========== Register definition for PDC_US1 peripheral ========== 
set AT91C_US1_PTCR  0xFFFB4120
set AT91C_US1_TNPR  0xFFFB4118
set AT91C_US1_RNPR  0xFFFB4110
set AT91C_US1_TPR   0xFFFB4108
set AT91C_US1_RPR   0xFFFB4100
set AT91C_US1_PTSR  0xFFFB4124
set AT91C_US1_TNCR  0xFFFB411C
set AT91C_US1_RNCR  0xFFFB4114
set AT91C_US1_TCR   0xFFFB410C
set AT91C_US1_RCR   0xFFFB4104
# ========== Register definition for US1 peripheral ========== 
set AT91C_US1_MAN   0xFFFB4050
set AT91C_US1_FIDI  0xFFFB4040
set AT91C_US1_TTGR  0xFFFB4028
set AT91C_US1_BRGR  0xFFFB4020
set AT91C_US1_RHR   0xFFFB4018
set AT91C_US1_IMR   0xFFFB4010
set AT91C_US1_IER   0xFFFB4008
set AT91C_US1_CR    0xFFFB4000
set AT91C_US1_IF    0xFFFB404C
set AT91C_US1_NER   0xFFFB4044
set AT91C_US1_RTOR  0xFFFB4024
set AT91C_US1_THR   0xFFFB401C
set AT91C_US1_CSR   0xFFFB4014
set AT91C_US1_IDR   0xFFFB400C
set AT91C_US1_MR    0xFFFB4004
# ========== Register definition for PDC_US2 peripheral ========== 
set AT91C_US2_PTSR  0xFFFB8124
set AT91C_US2_TNCR  0xFFFB811C
set AT91C_US2_RNCR  0xFFFB8114
set AT91C_US2_TCR   0xFFFB810C
set AT91C_US2_RCR   0xFFFB8104
set AT91C_US2_PTCR  0xFFFB8120
set AT91C_US2_TNPR  0xFFFB8118
set AT91C_US2_RNPR  0xFFFB8110
set AT91C_US2_TPR   0xFFFB8108
set AT91C_US2_RPR   0xFFFB8100
# ========== Register definition for US2 peripheral ========== 
set AT91C_US2_MAN   0xFFFB8050
set AT91C_US2_FIDI  0xFFFB8040
set AT91C_US2_TTGR  0xFFFB8028
set AT91C_US2_BRGR  0xFFFB8020
set AT91C_US2_RHR   0xFFFB8018
set AT91C_US2_IMR   0xFFFB8010
set AT91C_US2_IER   0xFFFB8008
set AT91C_US2_CR    0xFFFB8000
set AT91C_US2_IF    0xFFFB804C
set AT91C_US2_NER   0xFFFB8044
set AT91C_US2_RTOR  0xFFFB8024
set AT91C_US2_THR   0xFFFB801C
set AT91C_US2_CSR   0xFFFB8014
set AT91C_US2_IDR   0xFFFB800C
set AT91C_US2_MR    0xFFFB8004
# ========== Register definition for PDC_US3 peripheral ========== 
set AT91C_US3_PTSR  0xFFFBC124
set AT91C_US3_TNCR  0xFFFBC11C
set AT91C_US3_RNCR  0xFFFBC114
set AT91C_US3_TCR   0xFFFBC10C
set AT91C_US3_RCR   0xFFFBC104
set AT91C_US3_PTCR  0xFFFBC120
set AT91C_US3_TNPR  0xFFFBC118
set AT91C_US3_RNPR  0xFFFBC110
set AT91C_US3_TPR   0xFFFBC108
set AT91C_US3_RPR   0xFFFBC100
# ========== Register definition for US3 peripheral ========== 
set AT91C_US3_MAN   0xFFFBC050
set AT91C_US3_BRGR  0xFFFBC020
set AT91C_US3_RHR   0xFFFBC018
set AT91C_US3_IMR   0xFFFBC010
set AT91C_US3_IER   0xFFFBC008
set AT91C_US3_CR    0xFFFBC000
set AT91C_US3_RTOR  0xFFFBC024
set AT91C_US3_THR   0xFFFBC01C
set AT91C_US3_CSR   0xFFFBC014
set AT91C_US3_FIDI  0xFFFBC040
set AT91C_US3_TTGR  0xFFFBC028
set AT91C_US3_IF    0xFFFBC04C
set AT91C_US3_NER   0xFFFBC044
set AT91C_US3_MR    0xFFFBC004
set AT91C_US3_IDR   0xFFFBC00C
# ========== Register definition for PDC_SSC0 peripheral ========== 
set AT91C_SSC0_PTCR 0xFFFC0120
set AT91C_SSC0_TNPR 0xFFFC0118
set AT91C_SSC0_RNPR 0xFFFC0110
set AT91C_SSC0_TPR  0xFFFC0108
set AT91C_SSC0_RPR  0xFFFC0100
set AT91C_SSC0_PTSR 0xFFFC0124
set AT91C_SSC0_TNCR 0xFFFC011C
set AT91C_SSC0_RNCR 0xFFFC0114
set AT91C_SSC0_TCR  0xFFFC010C
set AT91C_SSC0_RCR  0xFFFC0104
# ========== Register definition for SSC0 peripheral ========== 
set AT91C_SSC0_RSHR 0xFFFC0030
set AT91C_SSC0_RHR  0xFFFC0020
set AT91C_SSC0_TCMR 0xFFFC0018
set AT91C_SSC0_RCMR 0xFFFC0010
set AT91C_SSC0_IER  0xFFFC0044
set AT91C_SSC0_TSHR 0xFFFC0034
set AT91C_SSC0_THR  0xFFFC0024
set AT91C_SSC0_IDR  0xFFFC0048
set AT91C_SSC0_SR   0xFFFC0040
set AT91C_SSC0_CR   0xFFFC0000
set AT91C_SSC0_IMR  0xFFFC004C
set AT91C_SSC0_CMR  0xFFFC0004
set AT91C_SSC0_RFMR 0xFFFC0014
set AT91C_SSC0_TFMR 0xFFFC001C
# ========== Register definition for PDC_SSC1 peripheral ========== 
set AT91C_SSC1_PTSR 0xFFFC4124
set AT91C_SSC1_TNCR 0xFFFC411C
set AT91C_SSC1_RNCR 0xFFFC4114
set AT91C_SSC1_TCR  0xFFFC410C
set AT91C_SSC1_RCR  0xFFFC4104
set AT91C_SSC1_PTCR 0xFFFC4120
set AT91C_SSC1_TNPR 0xFFFC4118
set AT91C_SSC1_RNPR 0xFFFC4110
set AT91C_SSC1_TPR  0xFFFC4108
set AT91C_SSC1_RPR  0xFFFC4100
# ========== Register definition for SSC1 peripheral ========== 
set AT91C_SSC1_IDR  0xFFFC4048
set AT91C_SSC1_TCMR 0xFFFC4018
set AT91C_SSC1_RCMR 0xFFFC4010
set AT91C_SSC1_CR   0xFFFC4000
set AT91C_SSC1_THR  0xFFFC4024
set AT91C_SSC1_TFMR 0xFFFC401C
set AT91C_SSC1_RFMR 0xFFFC4014
set AT91C_SSC1_SR   0xFFFC4040
set AT91C_SSC1_RHR  0xFFFC4020
set AT91C_SSC1_RSHR 0xFFFC4030
set AT91C_SSC1_IMR  0xFFFC404C
set AT91C_SSC1_IER  0xFFFC4044
set AT91C_SSC1_CMR  0xFFFC4004
set AT91C_SSC1_TSHR 0xFFFC4034
# ========== Register definition for PWMC_CH0 peripheral ========== 
set AT91C_PWMC_CH0_CUPDR 0xFFFC8210
set AT91C_PWMC_CH0_CPRDR 0xFFFC8208
set AT91C_PWMC_CH0_CMR 0xFFFC8200
set AT91C_PWMC_CH0_Reserved 0xFFFC8214
set AT91C_PWMC_CH0_CCNTR 0xFFFC820C
set AT91C_PWMC_CH0_CDTYR 0xFFFC8204
# ========== Register definition for PWMC_CH1 peripheral ========== 
set AT91C_PWMC_CH1_CUPDR 0xFFFC8230
set AT91C_PWMC_CH1_CPRDR 0xFFFC8228
set AT91C_PWMC_CH1_CMR 0xFFFC8220
set AT91C_PWMC_CH1_Reserved 0xFFFC8234
set AT91C_PWMC_CH1_CCNTR 0xFFFC822C
set AT91C_PWMC_CH1_CDTYR 0xFFFC8224
# ========== Register definition for PWMC_CH2 peripheral ========== 
set AT91C_PWMC_CH2_CUPDR 0xFFFC8250
set AT91C_PWMC_CH2_CPRDR 0xFFFC8248
set AT91C_PWMC_CH2_CMR 0xFFFC8240
set AT91C_PWMC_CH2_Reserved 0xFFFC8254
set AT91C_PWMC_CH2_CCNTR 0xFFFC824C
set AT91C_PWMC_CH2_CDTYR 0xFFFC8244
# ========== Register definition for PWMC_CH3 peripheral ========== 
set AT91C_PWMC_CH3_CUPDR 0xFFFC8270
set AT91C_PWMC_CH3_CPRDR 0xFFFC8268
set AT91C_PWMC_CH3_CMR 0xFFFC8260
set AT91C_PWMC_CH3_Reserved 0xFFFC8274
set AT91C_PWMC_CH3_CCNTR 0xFFFC826C
set AT91C_PWMC_CH3_CDTYR 0xFFFC8264
# ========== Register definition for PWMC peripheral ========== 
set AT91C_PWMC_VR   0xFFFC80FC
set AT91C_PWMC_IMR  0xFFFC8018
set AT91C_PWMC_IER  0xFFFC8010
set AT91C_PWMC_DIS  0xFFFC8008
set AT91C_PWMC_MR   0xFFFC8000
set AT91C_PWMC_ISR  0xFFFC801C
set AT91C_PWMC_IDR  0xFFFC8014
set AT91C_PWMC_SR   0xFFFC800C
set AT91C_PWMC_ENA  0xFFFC8004
# ========== Register definition for PDC_SPI peripheral ========== 
set AT91C_SPI_PTSR  0xFFFCC124
set AT91C_SPI_TNCR  0xFFFCC11C
set AT91C_SPI_RNCR  0xFFFCC114
set AT91C_SPI_TCR   0xFFFCC10C
set AT91C_SPI_RCR   0xFFFCC104
set AT91C_SPI_PTCR  0xFFFCC120
set AT91C_SPI_TNPR  0xFFFCC118
set AT91C_SPI_RNPR  0xFFFCC110
set AT91C_SPI_TPR   0xFFFCC108
set AT91C_SPI_RPR   0xFFFCC100
# ========== Register definition for SPI peripheral ========== 
set AT91C_SPI_IMR   0xFFFCC01C
set AT91C_SPI_IER   0xFFFCC014
set AT91C_SPI_TDR   0xFFFCC00C
set AT91C_SPI_MR    0xFFFCC004
set AT91C_SPI_CSR   0xFFFCC030
set AT91C_SPI_IDR   0xFFFCC018
set AT91C_SPI_SR    0xFFFCC010
set AT91C_SPI_RDR   0xFFFCC008
set AT91C_SPI_CR    0xFFFCC000
# ========== Register definition for PDC_TSC peripheral ========== 
set AT91C_TSC_PTCR  0xFFFD0120
set AT91C_TSC_TNPR  0xFFFD0118
set AT91C_TSC_RNPR  0xFFFD0110
set AT91C_TSC_TPR   0xFFFD0108
set AT91C_TSC_RPR   0xFFFD0100
set AT91C_TSC_PTSR  0xFFFD0124
set AT91C_TSC_TNCR  0xFFFD011C
set AT91C_TSC_RNCR  0xFFFD0114
set AT91C_TSC_TCR   0xFFFD010C
set AT91C_TSC_RCR   0xFFFD0104
# ========== Register definition for TSC peripheral ========== 
# ========== Register definition for UDPHS_EPTFIFO peripheral ========== 
set AT91C_UDPHS_EPTFIFO_READEPT5 0x00650000
set AT91C_UDPHS_EPTFIFO_READEPT4 0x00640000
set AT91C_UDPHS_EPTFIFO_READEPT2 0x00620000
set AT91C_UDPHS_EPTFIFO_READEPTC 0x006C0000
set AT91C_UDPHS_EPTFIFO_READEPT6 0x00660000
set AT91C_UDPHS_EPTFIFO_READEPT3 0x00630000
set AT91C_UDPHS_EPTFIFO_READEPTD 0x006D0000
set AT91C_UDPHS_EPTFIFO_READEPTB 0x006B0000
set AT91C_UDPHS_EPTFIFO_READEPT7 0x00670000
set AT91C_UDPHS_EPTFIFO_READEPT0 0x00600000
set AT91C_UDPHS_EPTFIFO_READEPTF 0x006F0000
set AT91C_UDPHS_EPTFIFO_READEPTE 0x006E0000
set AT91C_UDPHS_EPTFIFO_READEPTA 0x006A0000
set AT91C_UDPHS_EPTFIFO_READEPT9 0x00690000
set AT91C_UDPHS_EPTFIFO_READEPT8 0x00680000
set AT91C_UDPHS_EPTFIFO_READEPT1 0x00610000
# ========== Register definition for UDPHS_EPT_0 peripheral ========== 
set AT91C_UDPHS_EPT_0_EPTCLRSTA 0xFFFD4118
set AT91C_UDPHS_EPT_0_EPTCTLDIS 0xFFFD4108
set AT91C_UDPHS_EPT_0_EPTCFG 0xFFFD4100
set AT91C_UDPHS_EPT_0_EPTSTA 0xFFFD411C
set AT91C_UDPHS_EPT_0_EPTSETSTA 0xFFFD4114
set AT91C_UDPHS_EPT_0_EPTCTL 0xFFFD410C
set AT91C_UDPHS_EPT_0_EPTCTLENB 0xFFFD4104
# ========== Register definition for UDPHS_EPT_1 peripheral ========== 
set AT91C_UDPHS_EPT_1_EPTCLRSTA 0xFFFD4138
set AT91C_UDPHS_EPT_1_EPTCTLDIS 0xFFFD4128
set AT91C_UDPHS_EPT_1_EPTCFG 0xFFFD4120
set AT91C_UDPHS_EPT_1_EPTSTA 0xFFFD413C
set AT91C_UDPHS_EPT_1_EPTSETSTA 0xFFFD4134
set AT91C_UDPHS_EPT_1_EPTCTL 0xFFFD412C
set AT91C_UDPHS_EPT_1_EPTCTLENB 0xFFFD4124
# ========== Register definition for UDPHS_EPT_2 peripheral ========== 
set AT91C_UDPHS_EPT_2_EPTCLRSTA 0xFFFD4158
set AT91C_UDPHS_EPT_2_EPTCTLDIS 0xFFFD4148
set AT91C_UDPHS_EPT_2_EPTCFG 0xFFFD4140
set AT91C_UDPHS_EPT_2_EPTSTA 0xFFFD415C
set AT91C_UDPHS_EPT_2_EPTSETSTA 0xFFFD4154
set AT91C_UDPHS_EPT_2_EPTCTL 0xFFFD414C
set AT91C_UDPHS_EPT_2_EPTCTLENB 0xFFFD4144
# ========== Register definition for UDPHS_EPT_3 peripheral ========== 
set AT91C_UDPHS_EPT_3_EPTCLRSTA 0xFFFD4178
set AT91C_UDPHS_EPT_3_EPTCTLDIS 0xFFFD4168
set AT91C_UDPHS_EPT_3_EPTCFG 0xFFFD4160
set AT91C_UDPHS_EPT_3_EPTSTA 0xFFFD417C
set AT91C_UDPHS_EPT_3_EPTSETSTA 0xFFFD4174
set AT91C_UDPHS_EPT_3_EPTCTL 0xFFFD416C
set AT91C_UDPHS_EPT_3_EPTCTLENB 0xFFFD4164
# ========== Register definition for UDPHS_EPT_4 peripheral ========== 
set AT91C_UDPHS_EPT_4_EPTCLRSTA 0xFFFD4198
set AT91C_UDPHS_EPT_4_EPTCTLDIS 0xFFFD4188
set AT91C_UDPHS_EPT_4_EPTCFG 0xFFFD4180
set AT91C_UDPHS_EPT_4_EPTSTA 0xFFFD419C
set AT91C_UDPHS_EPT_4_EPTSETSTA 0xFFFD4194
set AT91C_UDPHS_EPT_4_EPTCTL 0xFFFD418C
set AT91C_UDPHS_EPT_4_EPTCTLENB 0xFFFD4184
# ========== Register definition for UDPHS_EPT_5 peripheral ========== 
set AT91C_UDPHS_EPT_5_EPTCTLDIS 0xFFFD41A8
set AT91C_UDPHS_EPT_5_EPTCFG 0xFFFD41A0
set AT91C_UDPHS_EPT_5_EPTSTA 0xFFFD41BC
set AT91C_UDPHS_EPT_5_EPTSETSTA 0xFFFD41B4
set AT91C_UDPHS_EPT_5_EPTCTL 0xFFFD41AC
set AT91C_UDPHS_EPT_5_EPTCTLENB 0xFFFD41A4
set AT91C_UDPHS_EPT_5_EPTCLRSTA 0xFFFD41B8
# ========== Register definition for UDPHS_EPT_6 peripheral ========== 
set AT91C_UDPHS_EPT_6_EPTSTA 0xFFFD41DC
set AT91C_UDPHS_EPT_6_EPTSETSTA 0xFFFD41D4
set AT91C_UDPHS_EPT_6_EPTCTL 0xFFFD41CC
set AT91C_UDPHS_EPT_6_EPTCTLENB 0xFFFD41C4
set AT91C_UDPHS_EPT_6_EPTCLRSTA 0xFFFD41D8
set AT91C_UDPHS_EPT_6_EPTCTLDIS 0xFFFD41C8
set AT91C_UDPHS_EPT_6_EPTCFG 0xFFFD41C0
# ========== Register definition for UDPHS_EPT_7 peripheral ========== 
set AT91C_UDPHS_EPT_7_EPTSTA 0xFFFD41FC
set AT91C_UDPHS_EPT_7_EPTSETSTA 0xFFFD41F4
set AT91C_UDPHS_EPT_7_EPTCTL 0xFFFD41EC
set AT91C_UDPHS_EPT_7_EPTCTLENB 0xFFFD41E4
set AT91C_UDPHS_EPT_7_EPTCLRSTA 0xFFFD41F8
set AT91C_UDPHS_EPT_7_EPTCTLDIS 0xFFFD41E8
set AT91C_UDPHS_EPT_7_EPTCFG 0xFFFD41E0
# ========== Register definition for UDPHS_EPT_8 peripheral ========== 
set AT91C_UDPHS_EPT_8_EPTSTA 0xFFFD421C
set AT91C_UDPHS_EPT_8_EPTSETSTA 0xFFFD4214
set AT91C_UDPHS_EPT_8_EPTCTL 0xFFFD420C
set AT91C_UDPHS_EPT_8_EPTCTLENB 0xFFFD4204
set AT91C_UDPHS_EPT_8_EPTCLRSTA 0xFFFD4218
set AT91C_UDPHS_EPT_8_EPTCTLDIS 0xFFFD4208
set AT91C_UDPHS_EPT_8_EPTCFG 0xFFFD4200
# ========== Register definition for UDPHS_EPT_9 peripheral ========== 
set AT91C_UDPHS_EPT_9_EPTSTA 0xFFFD423C
set AT91C_UDPHS_EPT_9_EPTSETSTA 0xFFFD4234
set AT91C_UDPHS_EPT_9_EPTCTL 0xFFFD422C
set AT91C_UDPHS_EPT_9_EPTCTLENB 0xFFFD4224
set AT91C_UDPHS_EPT_9_EPTCLRSTA 0xFFFD4238
set AT91C_UDPHS_EPT_9_EPTCTLDIS 0xFFFD4228
set AT91C_UDPHS_EPT_9_EPTCFG 0xFFFD4220
# ========== Register definition for UDPHS_EPT_10 peripheral ========== 
set AT91C_UDPHS_EPT_10_EPTSTA 0xFFFD425C
set AT91C_UDPHS_EPT_10_EPTSETSTA 0xFFFD4254
set AT91C_UDPHS_EPT_10_EPTCTL 0xFFFD424C
set AT91C_UDPHS_EPT_10_EPTCTLENB 0xFFFD4244
set AT91C_UDPHS_EPT_10_EPTCLRSTA 0xFFFD4258
set AT91C_UDPHS_EPT_10_EPTCTLDIS 0xFFFD4248
set AT91C_UDPHS_EPT_10_EPTCFG 0xFFFD4240
# ========== Register definition for UDPHS_EPT_11 peripheral ========== 
set AT91C_UDPHS_EPT_11_EPTSTA 0xFFFD427C
set AT91C_UDPHS_EPT_11_EPTSETSTA 0xFFFD4274
set AT91C_UDPHS_EPT_11_EPTCTL 0xFFFD426C
set AT91C_UDPHS_EPT_11_EPTCTLENB 0xFFFD4264
set AT91C_UDPHS_EPT_11_EPTCLRSTA 0xFFFD4278
set AT91C_UDPHS_EPT_11_EPTCTLDIS 0xFFFD4268
set AT91C_UDPHS_EPT_11_EPTCFG 0xFFFD4260
# ========== Register definition for UDPHS_EPT_12 peripheral ========== 
set AT91C_UDPHS_EPT_12_EPTSTA 0xFFFD429C
set AT91C_UDPHS_EPT_12_EPTSETSTA 0xFFFD4294
set AT91C_UDPHS_EPT_12_EPTCTL 0xFFFD428C
set AT91C_UDPHS_EPT_12_EPTCTLENB 0xFFFD4284
set AT91C_UDPHS_EPT_12_EPTCLRSTA 0xFFFD4298
set AT91C_UDPHS_EPT_12_EPTCTLDIS 0xFFFD4288
set AT91C_UDPHS_EPT_12_EPTCFG 0xFFFD4280
# ========== Register definition for UDPHS_EPT_13 peripheral ========== 
set AT91C_UDPHS_EPT_13_EPTSTA 0xFFFD42BC
set AT91C_UDPHS_EPT_13_EPTSETSTA 0xFFFD42B4
set AT91C_UDPHS_EPT_13_EPTCTL 0xFFFD42AC
set AT91C_UDPHS_EPT_13_EPTCTLENB 0xFFFD42A4
set AT91C_UDPHS_EPT_13_EPTCLRSTA 0xFFFD42B8
set AT91C_UDPHS_EPT_13_EPTCTLDIS 0xFFFD42A8
set AT91C_UDPHS_EPT_13_EPTCFG 0xFFFD42A0
# ========== Register definition for UDPHS_EPT_14 peripheral ========== 
set AT91C_UDPHS_EPT_14_EPTSTA 0xFFFD42DC
set AT91C_UDPHS_EPT_14_EPTSETSTA 0xFFFD42D4
set AT91C_UDPHS_EPT_14_EPTCTLENB 0xFFFD42C4
set AT91C_UDPHS_EPT_14_EPTCTL 0xFFFD42CC
set AT91C_UDPHS_EPT_14_EPTCLRSTA 0xFFFD42D8
set AT91C_UDPHS_EPT_14_EPTCTLDIS 0xFFFD42C8
set AT91C_UDPHS_EPT_14_EPTCFG 0xFFFD42C0
# ========== Register definition for UDPHS_EPT_15 peripheral ========== 
set AT91C_UDPHS_EPT_15_EPTSTA 0xFFFD42FC
set AT91C_UDPHS_EPT_15_EPTSETSTA 0xFFFD42F4
set AT91C_UDPHS_EPT_15_EPTCTL 0xFFFD42EC
set AT91C_UDPHS_EPT_15_EPTCTLENB 0xFFFD42E4
set AT91C_UDPHS_EPT_15_EPTCLRSTA 0xFFFD42F8
set AT91C_UDPHS_EPT_15_EPTCTLDIS 0xFFFD42E8
set AT91C_UDPHS_EPT_15_EPTCFG 0xFFFD42E0
# ========== Register definition for UDPHS_DMA_1 peripheral ========== 
set AT91C_UDPHS_DMA_1_DMASTATUS 0xFFFD431C
set AT91C_UDPHS_DMA_1_DMAADDRESS 0xFFFD4314
set AT91C_UDPHS_DMA_1_DMACONTROL 0xFFFD4318
set AT91C_UDPHS_DMA_1_DMANXTDSC 0xFFFD4310
# ========== Register definition for UDPHS_DMA_2 peripheral ========== 
set AT91C_UDPHS_DMA_2_DMASTATUS 0xFFFD432C
set AT91C_UDPHS_DMA_2_DMAADDRESS 0xFFFD4324
set AT91C_UDPHS_DMA_2_DMACONTROL 0xFFFD4328
set AT91C_UDPHS_DMA_2_DMANXTDSC 0xFFFD4320
# ========== Register definition for UDPHS_DMA_3 peripheral ========== 
set AT91C_UDPHS_DMA_3_DMAADDRESS 0xFFFD4334
set AT91C_UDPHS_DMA_3_DMACONTROL 0xFFFD4338
set AT91C_UDPHS_DMA_3_DMANXTDSC 0xFFFD4330
set AT91C_UDPHS_DMA_3_DMASTATUS 0xFFFD433C
# ========== Register definition for UDPHS_DMA_4 peripheral ========== 
set AT91C_UDPHS_DMA_4_DMACONTROL 0xFFFD4348
set AT91C_UDPHS_DMA_4_DMANXTDSC 0xFFFD4340
set AT91C_UDPHS_DMA_4_DMASTATUS 0xFFFD434C
set AT91C_UDPHS_DMA_4_DMAADDRESS 0xFFFD4344
# ========== Register definition for UDPHS_DMA_5 peripheral ========== 
set AT91C_UDPHS_DMA_5_DMACONTROL 0xFFFD4358
set AT91C_UDPHS_DMA_5_DMANXTDSC 0xFFFD4350
set AT91C_UDPHS_DMA_5_DMASTATUS 0xFFFD435C
set AT91C_UDPHS_DMA_5_DMAADDRESS 0xFFFD4354
# ========== Register definition for UDPHS_DMA_6 peripheral ========== 
set AT91C_UDPHS_DMA_6_DMACONTROL 0xFFFD4368
set AT91C_UDPHS_DMA_6_DMANXTDSC 0xFFFD4360
set AT91C_UDPHS_DMA_6_DMASTATUS 0xFFFD436C
set AT91C_UDPHS_DMA_6_DMAADDRESS 0xFFFD4364
# ========== Register definition for UDPHS_DMA_7 peripheral ========== 
set AT91C_UDPHS_DMA_7_DMACONTROL 0xFFFD4378
set AT91C_UDPHS_DMA_7_DMANXTDSC 0xFFFD4370
set AT91C_UDPHS_DMA_7_DMASTATUS 0xFFFD437C
set AT91C_UDPHS_DMA_7_DMAADDRESS 0xFFFD4374
# ========== Register definition for UDPHS peripheral ========== 
set AT91C_UDPHS_INTSTA 0xFFFD4014
set AT91C_UDPHS_FNUM 0xFFFD4004
set AT91C_UDPHS_TSTSOFCNT 0xFFFD40D0
set AT91C_UDPHS_CLRINT 0xFFFD4018
set AT91C_UDPHS_IEN 0xFFFD4010
set AT91C_UDPHS_TSTMODREG 0xFFFD40DC
set AT91C_UDPHS_TSTCNTA 0xFFFD40D4
set AT91C_UDPHS_IPFEATURES 0xFFFD40F8
set AT91C_UDPHS_RIPNAME1 0xFFFD40F0
set AT91C_UDPHS_TST 0xFFFD40E0
set AT91C_UDPHS_TSTCNTB 0xFFFD40D8
set AT91C_UDPHS_CTRL 0xFFFD4000
set AT91C_UDPHS_IPVERSION 0xFFFD40FC
set AT91C_UDPHS_RIPNAME2 0xFFFD40F4
set AT91C_UDPHS_RIPPADDRSIZE 0xFFFD40EC
set AT91C_UDPHS_EPTRST 0xFFFD401C
# ========== Register definition for PDC_AC97C peripheral ========== 
set AT91C_AC97C_PTCR 0xFFFD8120
set AT91C_AC97C_TNPR 0xFFFD8118
set AT91C_AC97C_RNPR 0xFFFD8110
set AT91C_AC97C_TPR 0xFFFD8108
set AT91C_AC97C_RPR 0xFFFD8100
set AT91C_AC97C_PTSR 0xFFFD8124
set AT91C_AC97C_TNCR 0xFFFD811C
set AT91C_AC97C_RNCR 0xFFFD8114
set AT91C_AC97C_TCR 0xFFFD810C
set AT91C_AC97C_RCR 0xFFFD8104
# ========== Register definition for AC97C peripheral ========== 
set AT91C_AC97C_CAMR 0xFFFD802C
set AT91C_AC97C_CORHR 0xFFFD8040
set AT91C_AC97C_CBSR 0xFFFD8038
set AT91C_AC97C_CBRHR 0xFFFD8030
set AT91C_AC97C_CBTHR 0xFFFD8034
set AT91C_AC97C_CBMR 0xFFFD803C
set AT91C_AC97C_COTHR 0xFFFD8044
set AT91C_AC97C_COMR 0xFFFD804C
set AT91C_AC97C_IER 0xFFFD8054
set AT91C_AC97C_COSR 0xFFFD8048
set AT91C_AC97C_SR  0xFFFD8050
set AT91C_AC97C_IDR 0xFFFD8058
set AT91C_AC97C_MR  0xFFFD8008
set AT91C_AC97C_ICA 0xFFFD8010
set AT91C_AC97C_VERSION 0xFFFD80FC
set AT91C_AC97C_IMR 0xFFFD805C
set AT91C_AC97C_CATHR 0xFFFD8024
set AT91C_AC97C_OCA 0xFFFD8014
set AT91C_AC97C_CASR 0xFFFD8028
set AT91C_AC97C_CARHR 0xFFFD8020
# ========== Register definition for LCDC peripheral ========== 
set AT91C_LCDC_LUT_ENTRY 0x00500C00
set AT91C_LCDC_CTRSTVAL 0x00500844
set AT91C_LCDC_PWRCON 0x0050083C
set AT91C_LCDC_DP4_5 0x00500834
set AT91C_LCDC_DP5_7 0x0050082C
set AT91C_LCDC_DP3_5 0x00500824
set AT91C_LCDC_DP1_2 0x0050081C
set AT91C_LCDC_FIFO 0x00500814
set AT91C_LCDC_TIM2 0x0050080C
set AT91C_LCDC_LCDCON2 0x00500804
set AT91C_LCDC_DMACON 0x0050001C
set AT91C_LCDC_FRMA2 0x00500014
set AT91C_LCDC_ITR  0x00500860
set AT91C_LCDC_ICR  0x00500858
set AT91C_LCDC_IMR  0x00500850
set AT91C_LCDC_IER  0x00500848
set AT91C_LCDC_FRMP2 0x0050000C
set AT91C_LCDC_BA2  0x00500004
set AT91C_LCDC_CTRSTCON 0x00500840
set AT91C_LCDC_DP6_7 0x00500838
set AT91C_LCDC_DP3_4 0x00500830
set AT91C_LCDC_DP2_3 0x00500828
set AT91C_LCDC_DP4_7 0x00500820
set AT91C_LCDC_MVAL 0x00500818
set AT91C_LCDC_LCDFRCFG 0x00500810
set AT91C_LCDC_TIM1 0x00500808
set AT91C_LCDC_LCDCON1 0x00500800
set AT91C_LCDC_DMA2DCFG 0x00500020
set AT91C_LCDC_FRMCFG 0x00500018
set AT91C_LCDC_IRR  0x00500864
set AT91C_LCDC_GPR  0x0050085C
set AT91C_LCDC_ISR  0x00500854
set AT91C_LCDC_IDR  0x0050084C
set AT91C_LCDC_FRMA1 0x00500010
set AT91C_LCDC_FRMP1 0x00500008
set AT91C_LCDC_BA1  0x00500000
# ========== Register definition for LCDC_16B_TFT peripheral ========== 
set AT91C_TFT_LUT_ENTRY 0x00500C00
set AT91C_TFT_CTRSTVAL 0x00500844
set AT91C_TFT_PWRCON 0x0050083C
set AT91C_TFT_DP4_5 0x00500834
set AT91C_TFT_DP5_7 0x0050082C
set AT91C_TFT_DP3_5 0x00500824
set AT91C_TFT_DP1_2 0x0050081C
set AT91C_TFT_FIFO  0x00500814
set AT91C_TFT_TIM2  0x0050080C
set AT91C_TFT_LCDCON2 0x00500804
set AT91C_TFT_DMACON 0x0050001C
set AT91C_TFT_FRMA2 0x00500014
set AT91C_TFT_ITR   0x00500860
set AT91C_TFT_ICR   0x00500858
set AT91C_TFT_IMR   0x00500850
set AT91C_TFT_IER   0x00500848
set AT91C_TFT_FRMP2 0x0050000C
set AT91C_TFT_BA2   0x00500004
set AT91C_TFT_CTRSTCON 0x00500840
set AT91C_TFT_DP6_7 0x00500838
set AT91C_TFT_DP3_4 0x00500830
set AT91C_TFT_DP2_3 0x00500828
set AT91C_TFT_DP4_7 0x00500820
set AT91C_TFT_MVAL  0x00500818
set AT91C_TFT_LCDFRCFG 0x00500810
set AT91C_TFT_TIM1  0x00500808
set AT91C_TFT_LCDCON1 0x00500800
set AT91C_TFT_DMA2DCFG 0x00500020
set AT91C_TFT_FRMCFG 0x00500018
set AT91C_TFT_IRR   0x00500864
set AT91C_TFT_GPR   0x0050085C
set AT91C_TFT_ISR   0x00500854
set AT91C_TFT_IDR   0x0050084C
set AT91C_TFT_FRMA1 0x00500010
set AT91C_TFT_FRMP1 0x00500008
set AT91C_TFT_BA1   0x00500000
# ========== Register definition for HDMA_CH_0 peripheral ========== 
set AT91C_HDMA_CH_0_CADDR 0xFFFFE660
set AT91C_HDMA_CH_0_DPIP 0xFFFFE658
set AT91C_HDMA_CH_0_CFG 0xFFFFE650
set AT91C_HDMA_CH_0_CTRLA 0xFFFFE648
set AT91C_HDMA_CH_0_DADDR 0xFFFFE640
set AT91C_HDMA_CH_0_BDSCR 0xFFFFE65C
set AT91C_HDMA_CH_0_SPIP 0xFFFFE654
set AT91C_HDMA_CH_0_CTRLB 0xFFFFE64C
set AT91C_HDMA_CH_0_DSCR 0xFFFFE644
set AT91C_HDMA_CH_0_SADDR 0xFFFFE63C
# ========== Register definition for HDMA_CH_1 peripheral ========== 
set AT91C_HDMA_CH_1_CADDR 0xFFFFE688
set AT91C_HDMA_CH_1_DPIP 0xFFFFE680
set AT91C_HDMA_CH_1_CFG 0xFFFFE678
set AT91C_HDMA_CH_1_CTRLA 0xFFFFE670
set AT91C_HDMA_CH_1_DADDR 0xFFFFE668
set AT91C_HDMA_CH_1_BDSCR 0xFFFFE684
set AT91C_HDMA_CH_1_SPIP 0xFFFFE67C
set AT91C_HDMA_CH_1_CTRLB 0xFFFFE674
set AT91C_HDMA_CH_1_DSCR 0xFFFFE66C
set AT91C_HDMA_CH_1_SADDR 0xFFFFE664
# ========== Register definition for HDMA peripheral ========== 
set AT91C_HDMA_RSVD0 0xFFFFE634
set AT91C_HDMA_CHDR 0xFFFFE62C
set AT91C_HDMA_EBCISR 0xFFFFE624
set AT91C_HDMA_EBCIDR 0xFFFFE61C
set AT91C_HDMA_SYNC 0xFFFFE614
set AT91C_HDMA_BREQ 0xFFFFE60C
set AT91C_HDMA_EN   0xFFFFE604
set AT91C_HDMA_RSVD1 0xFFFFE638
set AT91C_HDMA_CHSR 0xFFFFE630
set AT91C_HDMA_CHER 0xFFFFE628
set AT91C_HDMA_EBCIMR 0xFFFFE620
set AT91C_HDMA_EBCIER 0xFFFFE618
set AT91C_HDMA_LAST 0xFFFFE610
set AT91C_HDMA_SREQ 0xFFFFE608
set AT91C_HDMA_GCFG 0xFFFFE600
# ========== Register definition for HECC peripheral ========== 
set AT91C_HECC_PR   0xFFFFE80C
set AT91C_HECC_MR   0xFFFFE804
set AT91C_HECC_NPR  0xFFFFE810
set AT91C_HECC_SR   0xFFFFE808
set AT91C_HECC_CR   0xFFFFE800
set AT91C_HECC_VR   0xFFFFE8FC

# *****************************************************************************
#               BASE ADDRESS DEFINITIONS FOR AT91SAM9RL64
# *****************************************************************************
set AT91C_BASE_SYS       0xFFFFC000
set AT91C_BASE_EBI       0xFFFFE800
set AT91C_BASE_SDRAMC    0xFFFFEA00
set AT91C_BASE_SMC       0xFFFFEC00
set AT91C_BASE_MATRIX    0xFFFFEE00
set AT91C_BASE_CCFG      0xFFFFEF10
set AT91C_BASE_AIC       0xFFFFF000
set AT91C_BASE_PDC_DBGU  0xFFFFF300
set AT91C_BASE_DBGU      0xFFFFF200
set AT91C_BASE_PIOA      0xFFFFF400
set AT91C_BASE_PIOB      0xFFFFF600
set AT91C_BASE_PIOC      0xFFFFF800
set AT91C_BASE_PIOD      0xFFFFFA00
set AT91C_BASE_PMC       0xFFFFFC00
set AT91C_BASE_CKGR      0xFFFFFC1C
set AT91C_BASE_RSTC      0xFFFFFD00
set AT91C_BASE_SHDWC     0xFFFFFD10
set AT91C_BASE_RTTC      0xFFFFFD20
set AT91C_BASE_PITC      0xFFFFFD30
set AT91C_BASE_WDTC      0xFFFFFD40
set AT91C_BASE_RTC       0xFFFFFE00
set AT91C_BASE_TC0       0xFFFA0000
set AT91C_BASE_TC1       0xFFFA0040
set AT91C_BASE_TC2       0xFFFA0080
set AT91C_BASE_TCB0      0xFFFA0000
set AT91C_BASE_TCB1      0xFFFA0040
set AT91C_BASE_TCB2      0xFFFA0080
set AT91C_BASE_PDC_MCI   0xFFFA4100
set AT91C_BASE_MCI       0xFFFA4000
set AT91C_BASE_PDC_TWI0  0xFFFA8100
set AT91C_BASE_TWI0      0xFFFA8000
set AT91C_BASE_TWI1      0xFFFAC000
set AT91C_BASE_PDC_US0   0xFFFB0100
set AT91C_BASE_US0       0xFFFB0000
set AT91C_BASE_PDC_US1   0xFFFB4100
set AT91C_BASE_US1       0xFFFB4000
set AT91C_BASE_PDC_US2   0xFFFB8100
set AT91C_BASE_US2       0xFFFB8000
set AT91C_BASE_PDC_US3   0xFFFBC100
set AT91C_BASE_US3       0xFFFBC000
set AT91C_BASE_PDC_SSC0  0xFFFC0100
set AT91C_BASE_SSC0      0xFFFC0000
set AT91C_BASE_PDC_SSC1  0xFFFC4100
set AT91C_BASE_SSC1      0xFFFC4000
set AT91C_BASE_PWMC_CH0  0xFFFC8200
set AT91C_BASE_PWMC_CH1  0xFFFC8220
set AT91C_BASE_PWMC_CH2  0xFFFC8240
set AT91C_BASE_PWMC_CH3  0xFFFC8260
set AT91C_BASE_PWMC      0xFFFC8000
set AT91C_BASE_PDC_SPI   0xFFFCC100
set AT91C_BASE_SPI       0xFFFCC000
set AT91C_BASE_PDC_TSC   0xFFFD0100
set AT91C_BASE_TSC       0xFFFD0000
set AT91C_BASE_UDPHS_EPTFIFO 0x00600000
set AT91C_BASE_UDPHS_EPT_0 0xFFFD4100
set AT91C_BASE_UDPHS_EPT_1 0xFFFD4120
set AT91C_BASE_UDPHS_EPT_2 0xFFFD4140
set AT91C_BASE_UDPHS_EPT_3 0xFFFD4160
set AT91C_BASE_UDPHS_EPT_4 0xFFFD4180
set AT91C_BASE_UDPHS_EPT_5 0xFFFD41A0
set AT91C_BASE_UDPHS_EPT_6 0xFFFD41C0
set AT91C_BASE_UDPHS_EPT_7 0xFFFD41E0
set AT91C_BASE_UDPHS_EPT_8 0xFFFD4200
set AT91C_BASE_UDPHS_EPT_9 0xFFFD4220
set AT91C_BASE_UDPHS_EPT_10 0xFFFD4240
set AT91C_BASE_UDPHS_EPT_11 0xFFFD4260
set AT91C_BASE_UDPHS_EPT_12 0xFFFD4280
set AT91C_BASE_UDPHS_EPT_13 0xFFFD42A0
set AT91C_BASE_UDPHS_EPT_14 0xFFFD42C0
set AT91C_BASE_UDPHS_EPT_15 0xFFFD42E0
set AT91C_BASE_UDPHS_DMA_1 0xFFFD4310
set AT91C_BASE_UDPHS_DMA_2 0xFFFD4320
set AT91C_BASE_UDPHS_DMA_3 0xFFFD4330
set AT91C_BASE_UDPHS_DMA_4 0xFFFD4340
set AT91C_BASE_UDPHS_DMA_5 0xFFFD4350
set AT91C_BASE_UDPHS_DMA_6 0xFFFD4360
set AT91C_BASE_UDPHS_DMA_7 0xFFFD4370
set AT91C_BASE_UDPHS     0xFFFD4000
set AT91C_BASE_PDC_AC97C 0xFFFD8100
set AT91C_BASE_AC97C     0xFFFD8000
set AT91C_BASE_LCDC      0x00500000
set AT91C_BASE_LCDC_16B_TFT 0x00500000
set AT91C_BASE_HDMA_CH_0 0xFFFFE63C
set AT91C_BASE_HDMA_CH_1 0xFFFFE664
set AT91C_BASE_HDMA      0xFFFFE600
set AT91C_BASE_HECC      0xFFFFE800

# *****************************************************************************
#               PERIPHERAL ID DEFINITIONS FOR AT91SAM9RL64
# *****************************************************************************
set AT91C_ID_FIQ     0
set AT91C_ID_SYS     1
set AT91C_ID_PIOA    2
set AT91C_ID_PIOB    3
set AT91C_ID_PIOC    4
set AT91C_ID_PIOD    5
set AT91C_ID_US0     6
set AT91C_ID_US1     7
set AT91C_ID_US2     8
set AT91C_ID_US3     9
set AT91C_ID_MCI    10
set AT91C_ID_TWI0   11
set AT91C_ID_TWI1   12
set AT91C_ID_SPI    13
set AT91C_ID_SSC0   14
set AT91C_ID_SSC1   15
set AT91C_ID_TC0    16
set AT91C_ID_TC1    17
set AT91C_ID_TC2    18
set AT91C_ID_PWMC   19
set AT91C_ID_TSC    20
set AT91C_ID_HDMA   21
set AT91C_ID_UDPHS  22
set AT91C_ID_LCDC   23
set AT91C_ID_AC97C  24
set AT91C_ID_IRQ0   31

# *****************************************************************************
#               PIO DEFINITIONS FOR AT91SAM9RL64
# *****************************************************************************
set AT91C_PIO_PA0        [expr 1 <<  0 ]
set AT91C_PA0_MC_DA0   $AT91C_PIO_PA0
set AT91C_PIO_PA1        [expr 1 <<  1 ]
set AT91C_PA1_MC_CDA   $AT91C_PIO_PA1
set AT91C_PIO_PA10       [expr 1 << 10 ]
set AT91C_PA10_CTS0     $AT91C_PIO_PA10
set AT91C_PA10_RK0      $AT91C_PIO_PA10
set AT91C_PIO_PA11       [expr 1 << 11 ]
set AT91C_PA11_TXD1     $AT91C_PIO_PA11
set AT91C_PIO_PA12       [expr 1 << 12 ]
set AT91C_PA12_RXD1     $AT91C_PIO_PA12
set AT91C_PIO_PA13       [expr 1 << 13 ]
set AT91C_PA13_TXD2     $AT91C_PIO_PA13
set AT91C_PA13_TD1      $AT91C_PIO_PA13
set AT91C_PIO_PA14       [expr 1 << 14 ]
set AT91C_PA14_RXD2     $AT91C_PIO_PA14
set AT91C_PA14_RD1      $AT91C_PIO_PA14
set AT91C_PIO_PA15       [expr 1 << 15 ]
set AT91C_PA15_TD0      $AT91C_PIO_PA15
set AT91C_PIO_PA16       [expr 1 << 16 ]
set AT91C_PA16_RD0      $AT91C_PIO_PA16
set AT91C_PIO_PA17       [expr 1 << 17 ]
set AT91C_PA17_AD0      $AT91C_PIO_PA17
set AT91C_PIO_PA18       [expr 1 << 18 ]
set AT91C_PA18_AD1      $AT91C_PIO_PA18
set AT91C_PA18_RTS1     $AT91C_PIO_PA18
set AT91C_PIO_PA19       [expr 1 << 19 ]
set AT91C_PA19_AD2      $AT91C_PIO_PA19
set AT91C_PA19_CTS1     $AT91C_PIO_PA19
set AT91C_PIO_PA2        [expr 1 <<  2 ]
set AT91C_PA2_MC_CK    $AT91C_PIO_PA2
set AT91C_PIO_PA20       [expr 1 << 20 ]
set AT91C_PA20_AD3      $AT91C_PIO_PA20
set AT91C_PA20_SCK3     $AT91C_PIO_PA20
set AT91C_PIO_PA21       [expr 1 << 21 ]
set AT91C_PA21_DRXD     $AT91C_PIO_PA21
set AT91C_PIO_PA22       [expr 1 << 22 ]
set AT91C_PA22_DTXD     $AT91C_PIO_PA22
set AT91C_PA22_RF0      $AT91C_PIO_PA22
set AT91C_PIO_PA23       [expr 1 << 23 ]
set AT91C_PA23_TWD0     $AT91C_PIO_PA23
set AT91C_PIO_PA24       [expr 1 << 24 ]
set AT91C_PA24_TWCK0    $AT91C_PIO_PA24
set AT91C_PIO_PA25       [expr 1 << 25 ]
set AT91C_PA25_MISO     $AT91C_PIO_PA25
set AT91C_PIO_PA26       [expr 1 << 26 ]
set AT91C_PA26_MOSI     $AT91C_PIO_PA26
set AT91C_PIO_PA27       [expr 1 << 27 ]
set AT91C_PA27_SPCK     $AT91C_PIO_PA27
set AT91C_PIO_PA28       [expr 1 << 28 ]
set AT91C_PA28_NPCS0    $AT91C_PIO_PA28
set AT91C_PIO_PA29       [expr 1 << 29 ]
set AT91C_PA29_RTS2     $AT91C_PIO_PA29
set AT91C_PA29_TF1      $AT91C_PIO_PA29
set AT91C_PIO_PA3        [expr 1 <<  3 ]
set AT91C_PA3_MC_DA1   $AT91C_PIO_PA3
set AT91C_PA3_TCLK0    $AT91C_PIO_PA3
set AT91C_PIO_PA30       [expr 1 << 30 ]
set AT91C_PA30_CTS2     $AT91C_PIO_PA30
set AT91C_PA30_TK1      $AT91C_PIO_PA30
set AT91C_PIO_PA31       [expr 1 << 31 ]
set AT91C_PA31_NWAIT    $AT91C_PIO_PA31
set AT91C_PA31_IRQ      $AT91C_PIO_PA31
set AT91C_PIO_PA4        [expr 1 <<  4 ]
set AT91C_PA4_MC_DA2   $AT91C_PIO_PA4
set AT91C_PA4_TIOA0    $AT91C_PIO_PA4
set AT91C_PIO_PA5        [expr 1 <<  5 ]
set AT91C_PA5_MC_DA3   $AT91C_PIO_PA5
set AT91C_PA5_TIOB0    $AT91C_PIO_PA5
set AT91C_PIO_PA6        [expr 1 <<  6 ]
set AT91C_PA6_TXD0     $AT91C_PIO_PA6
set AT91C_PIO_PA7        [expr 1 <<  7 ]
set AT91C_PA7_RXD0     $AT91C_PIO_PA7
set AT91C_PIO_PA8        [expr 1 <<  8 ]
set AT91C_PA8_SCK0     $AT91C_PIO_PA8
set AT91C_PA8_RF1      $AT91C_PIO_PA8
set AT91C_PIO_PA9        [expr 1 <<  9 ]
set AT91C_PA9_RTS0     $AT91C_PIO_PA9
set AT91C_PA9_RK1      $AT91C_PIO_PA9
set AT91C_PIO_PB0        [expr 1 <<  0 ]
set AT91C_PB0_TXD3     $AT91C_PIO_PB0
set AT91C_PIO_PB1        [expr 1 <<  1 ]
set AT91C_PB1_RXD3     $AT91C_PIO_PB1
set AT91C_PIO_PB10       [expr 1 << 10 ]
set AT91C_PB10_A25_CFRNW $AT91C_PIO_PB10
set AT91C_PB10_FIQ      $AT91C_PIO_PB10
set AT91C_PIO_PB11       [expr 1 << 11 ]
set AT91C_PB11_A18      $AT91C_PIO_PB11
set AT91C_PIO_PB12       [expr 1 << 12 ]
set AT91C_PB12_A19      $AT91C_PIO_PB12
set AT91C_PIO_PB13       [expr 1 << 13 ]
set AT91C_PB13_A20      $AT91C_PIO_PB13
set AT91C_PIO_PB14       [expr 1 << 14 ]
set AT91C_PB14_A23      $AT91C_PIO_PB14
set AT91C_PB14_PCK0     $AT91C_PIO_PB14
set AT91C_PIO_PB15       [expr 1 << 15 ]
set AT91C_PB15_A24      $AT91C_PIO_PB15
set AT91C_PB15_ADTRG    $AT91C_PIO_PB15
set AT91C_PIO_PB16       [expr 1 << 16 ]
set AT91C_PB16_D16      $AT91C_PIO_PB16
set AT91C_PIO_PB17       [expr 1 << 17 ]
set AT91C_PB17_D17      $AT91C_PIO_PB17
set AT91C_PIO_PB18       [expr 1 << 18 ]
set AT91C_PB18_D18      $AT91C_PIO_PB18
set AT91C_PIO_PB19       [expr 1 << 19 ]
set AT91C_PB19_D19      $AT91C_PIO_PB19
set AT91C_PIO_PB2        [expr 1 <<  2 ]
set AT91C_PB2_A21_NANDALE $AT91C_PIO_PB2
set AT91C_PIO_PB20       [expr 1 << 20 ]
set AT91C_PB20_D20      $AT91C_PIO_PB20
set AT91C_PIO_PB21       [expr 1 << 21 ]
set AT91C_PB21_D21      $AT91C_PIO_PB21
set AT91C_PIO_PB22       [expr 1 << 22 ]
set AT91C_PB22_D22      $AT91C_PIO_PB22
set AT91C_PIO_PB23       [expr 1 << 23 ]
set AT91C_PB23_D23      $AT91C_PIO_PB23
set AT91C_PIO_PB24       [expr 1 << 24 ]
set AT91C_PB24_D24      $AT91C_PIO_PB24
set AT91C_PIO_PB25       [expr 1 << 25 ]
set AT91C_PB25_D25      $AT91C_PIO_PB25
set AT91C_PIO_PB26       [expr 1 << 26 ]
set AT91C_PB26_D26      $AT91C_PIO_PB26
set AT91C_PIO_PB27       [expr 1 << 27 ]
set AT91C_PB27_D27      $AT91C_PIO_PB27
set AT91C_PIO_PB28       [expr 1 << 28 ]
set AT91C_PB28_D28      $AT91C_PIO_PB28
set AT91C_PIO_PB29       [expr 1 << 29 ]
set AT91C_PB29_D29      $AT91C_PIO_PB29
set AT91C_PIO_PB3        [expr 1 <<  3 ]
set AT91C_PB3_A22_NANDCLE $AT91C_PIO_PB3
set AT91C_PIO_PB30       [expr 1 << 30 ]
set AT91C_PB30_D30      $AT91C_PIO_PB30
set AT91C_PIO_PB31       [expr 1 << 31 ]
set AT91C_PB31_D31      $AT91C_PIO_PB31
set AT91C_PIO_PB4        [expr 1 <<  4 ]
set AT91C_PB4_NANDOE   $AT91C_PIO_PB4
set AT91C_PIO_PB5        [expr 1 <<  5 ]
set AT91C_PB5_NANDWE   $AT91C_PIO_PB5
set AT91C_PIO_PB6        [expr 1 <<  6 ]
set AT91C_PB6_NCS3_NANDCS $AT91C_PIO_PB6
set AT91C_PIO_PB7        [expr 1 <<  7 ]
set AT91C_PB7_NCS4_CFCS0 $AT91C_PIO_PB7
set AT91C_PB7_NPCS1    $AT91C_PIO_PB7
set AT91C_PIO_PB8        [expr 1 <<  8 ]
set AT91C_PB8_CFE1     $AT91C_PIO_PB8
set AT91C_PB8_PWM0     $AT91C_PIO_PB8
set AT91C_PIO_PB9        [expr 1 <<  9 ]
set AT91C_PB9_CFE2     $AT91C_PIO_PB9
set AT91C_PB9_PWM1     $AT91C_PIO_PB9
set AT91C_PIO_PC0        [expr 1 <<  0 ]
set AT91C_PC0_TF0      $AT91C_PIO_PC0
set AT91C_PIO_PC1        [expr 1 <<  1 ]
set AT91C_PC1_TK0      $AT91C_PIO_PC1
set AT91C_PC1_LCDPWR   $AT91C_PIO_PC1
set AT91C_PIO_PC10       [expr 1 << 10 ]
set AT91C_PC10_LCDD2    $AT91C_PIO_PC10
set AT91C_PC10_LCDD4    $AT91C_PIO_PC10
set AT91C_PIO_PC11       [expr 1 << 11 ]
set AT91C_PC11_LCDD3    $AT91C_PIO_PC11
set AT91C_PC11_LCDD5    $AT91C_PIO_PC11
set AT91C_PIO_PC12       [expr 1 << 12 ]
set AT91C_PC12_LCDD4    $AT91C_PIO_PC12
set AT91C_PC12_LCDD6    $AT91C_PIO_PC12
set AT91C_PIO_PC13       [expr 1 << 13 ]
set AT91C_PC13_LCDD5    $AT91C_PIO_PC13
set AT91C_PC13_LCDD7    $AT91C_PIO_PC13
set AT91C_PIO_PC14       [expr 1 << 14 ]
set AT91C_PC14_LCDD6    $AT91C_PIO_PC14
set AT91C_PC14_LCDD10   $AT91C_PIO_PC14
set AT91C_PIO_PC15       [expr 1 << 15 ]
set AT91C_PC15_LCDD7    $AT91C_PIO_PC15
set AT91C_PC15_LCDD11   $AT91C_PIO_PC15
set AT91C_PIO_PC16       [expr 1 << 16 ]
set AT91C_PC16_LCDD8    $AT91C_PIO_PC16
set AT91C_PC16_LCDD12   $AT91C_PIO_PC16
set AT91C_PIO_PC17       [expr 1 << 17 ]
set AT91C_PC17_LCDD9    $AT91C_PIO_PC17
set AT91C_PC17_LCDD13   $AT91C_PIO_PC17
set AT91C_PIO_PC18       [expr 1 << 18 ]
set AT91C_PC18_LCDD10   $AT91C_PIO_PC18
set AT91C_PC18_LCDD14   $AT91C_PIO_PC18
set AT91C_PIO_PC19       [expr 1 << 19 ]
set AT91C_PC19_LCDD11   $AT91C_PIO_PC19
set AT91C_PC19_LCDD15   $AT91C_PIO_PC19
set AT91C_PIO_PC2        [expr 1 <<  2 ]
set AT91C_PC2_LCDMOD   $AT91C_PIO_PC2
set AT91C_PC2_PWM0     $AT91C_PIO_PC2
set AT91C_PIO_PC20       [expr 1 << 20 ]
set AT91C_PC20_LCDD12   $AT91C_PIO_PC20
set AT91C_PC20_LCDD18   $AT91C_PIO_PC20
set AT91C_PIO_PC21       [expr 1 << 21 ]
set AT91C_PC21_LCDD13   $AT91C_PIO_PC21
set AT91C_PC21_LCDD19   $AT91C_PIO_PC21
set AT91C_PIO_PC22       [expr 1 << 22 ]
set AT91C_PC22_LCDD14   $AT91C_PIO_PC22
set AT91C_PC22_LCDD20   $AT91C_PIO_PC22
set AT91C_PIO_PC23       [expr 1 << 23 ]
set AT91C_PC23_LCDD15   $AT91C_PIO_PC23
set AT91C_PC23_LCDD21   $AT91C_PIO_PC23
set AT91C_PIO_PC24       [expr 1 << 24 ]
set AT91C_PC24_LCDD16   $AT91C_PIO_PC24
set AT91C_PC24_LCDD22   $AT91C_PIO_PC24
set AT91C_PIO_PC25       [expr 1 << 25 ]
set AT91C_PC25_LCDD17   $AT91C_PIO_PC25
set AT91C_PC25_LCDD23   $AT91C_PIO_PC25
set AT91C_PIO_PC26       [expr 1 << 26 ]
set AT91C_PC26_LCDD18   $AT91C_PIO_PC26
set AT91C_PIO_PC27       [expr 1 << 27 ]
set AT91C_PC27_LCDD19   $AT91C_PIO_PC27
set AT91C_PIO_PC28       [expr 1 << 28 ]
set AT91C_PC28_LCDD20   $AT91C_PIO_PC28
set AT91C_PIO_PC29       [expr 1 << 29 ]
set AT91C_PC29_LCDD21   $AT91C_PIO_PC29
set AT91C_PC29_TIOA1    $AT91C_PIO_PC29
set AT91C_PIO_PC3        [expr 1 <<  3 ]
set AT91C_PC3_LCDCC    $AT91C_PIO_PC3
set AT91C_PC3_PWM1     $AT91C_PIO_PC3
set AT91C_PIO_PC30       [expr 1 << 30 ]
set AT91C_PC30_LCDD22   $AT91C_PIO_PC30
set AT91C_PC30_TIOB1    $AT91C_PIO_PC30
set AT91C_PIO_PC31       [expr 1 << 31 ]
set AT91C_PC31_LCDD23   $AT91C_PIO_PC31
set AT91C_PC31_TCLK1    $AT91C_PIO_PC31
set AT91C_PIO_PC4        [expr 1 <<  4 ]
set AT91C_PC4_LCDVSYNC $AT91C_PIO_PC4
set AT91C_PIO_PC5        [expr 1 <<  5 ]
set AT91C_PC5_LCDHSYNC $AT91C_PIO_PC5
set AT91C_PIO_PC6        [expr 1 <<  6 ]
set AT91C_PC6_LCDDOTCK $AT91C_PIO_PC6
set AT91C_PIO_PC7        [expr 1 <<  7 ]
set AT91C_PC7_LCDDEN   $AT91C_PIO_PC7
set AT91C_PIO_PC8        [expr 1 <<  8 ]
set AT91C_PC8_LCDD0    $AT91C_PIO_PC8
set AT91C_PC8_LCDD2    $AT91C_PIO_PC8
set AT91C_PIO_PC9        [expr 1 <<  9 ]
set AT91C_PC9_LCDD1    $AT91C_PIO_PC9
set AT91C_PC9_LCDD3    $AT91C_PIO_PC9
set AT91C_PIO_PD0        [expr 1 <<  0 ]
set AT91C_PD0_NCS2     $AT91C_PIO_PD0
set AT91C_PIO_PD1        [expr 1 <<  1 ]
set AT91C_PD1_AC97_FS  $AT91C_PIO_PD1
set AT91C_PIO_PD10       [expr 1 << 10 ]
set AT91C_PD10_TWD1     $AT91C_PIO_PD10
set AT91C_PD10_TIOA2    $AT91C_PIO_PD10
set AT91C_PIO_PD11       [expr 1 << 11 ]
set AT91C_PD11_TWCK1    $AT91C_PIO_PD11
set AT91C_PD11_TIOB2    $AT91C_PIO_PD11
set AT91C_PIO_PD12       [expr 1 << 12 ]
set AT91C_PD12_PWM2     $AT91C_PIO_PD12
set AT91C_PD12_PCK1     $AT91C_PIO_PD12
set AT91C_PIO_PD13       [expr 1 << 13 ]
set AT91C_PD13_NCS5_CFCS1 $AT91C_PIO_PD13
set AT91C_PD13_NPCS3    $AT91C_PIO_PD13
set AT91C_PIO_PD14       [expr 1 << 14 ]
set AT91C_PD14_DSR0     $AT91C_PIO_PD14
set AT91C_PD14_PWM0     $AT91C_PIO_PD14
set AT91C_PIO_PD15       [expr 1 << 15 ]
set AT91C_PD15_DTR0     $AT91C_PIO_PD15
set AT91C_PD15_PWM1     $AT91C_PIO_PD15
set AT91C_PIO_PD16       [expr 1 << 16 ]
set AT91C_PD16_DCD0     $AT91C_PIO_PD16
set AT91C_PD16_PWM2     $AT91C_PIO_PD16
set AT91C_PIO_PD17       [expr 1 << 17 ]
set AT91C_PD17_RI0      $AT91C_PIO_PD17
set AT91C_PIO_PD18       [expr 1 << 18 ]
set AT91C_PD18_PWM3     $AT91C_PIO_PD18
set AT91C_PIO_PD19       [expr 1 << 19 ]
set AT91C_PD19_PCK0     $AT91C_PIO_PD19
set AT91C_PIO_PD2        [expr 1 <<  2 ]
set AT91C_PD2_AC97_CK  $AT91C_PIO_PD2
set AT91C_PD2_SCK1     $AT91C_PIO_PD2
set AT91C_PIO_PD20       [expr 1 << 20 ]
set AT91C_PD20_PCK1     $AT91C_PIO_PD20
set AT91C_PIO_PD21       [expr 1 << 21 ]
set AT91C_PD21_TCLK2    $AT91C_PIO_PD21
set AT91C_PIO_PD3        [expr 1 <<  3 ]
set AT91C_PD3_AC97_TX  $AT91C_PIO_PD3
set AT91C_PD3_CTS3     $AT91C_PIO_PD3
set AT91C_PIO_PD4        [expr 1 <<  4 ]
set AT91C_PD4_AC97_RX  $AT91C_PIO_PD4
set AT91C_PD4_RTS3     $AT91C_PIO_PD4
set AT91C_PIO_PD5        [expr 1 <<  5 ]
set AT91C_PD5_DTXD     $AT91C_PIO_PD5
set AT91C_PD5_PWM2     $AT91C_PIO_PD5
set AT91C_PIO_PD6        [expr 1 <<  6 ]
set AT91C_PD6_AD4      $AT91C_PIO_PD6
set AT91C_PIO_PD7        [expr 1 <<  7 ]
set AT91C_PD7_AD5      $AT91C_PIO_PD7
set AT91C_PIO_PD8        [expr 1 <<  8 ]
set AT91C_PD8_NPCS2    $AT91C_PIO_PD8
set AT91C_PD8_PWM3     $AT91C_PIO_PD8
set AT91C_PIO_PD9        [expr 1 <<  9 ]
set AT91C_PD9_SCK2     $AT91C_PIO_PD9
set AT91C_PD9_NPCS3    $AT91C_PIO_PD9

# *****************************************************************************
#               MEMORY MAPPING DEFINITIONS FOR AT91SAM9RL64
# *****************************************************************************
set AT91C_ITCM 	 0x00100000
set AT91C_ITCM_SIZE	 0x00010000
set AT91C_DTCM 	 0x00200000
set AT91C_DTCM_SIZE	 0x00010000
set AT91C_IRAM 	 0x00300000
set AT91C_IRAM_SIZE	 0x00010000
set AT91C_IRAM_MIN	 0x00300000
set AT91C_IRAM_MIN_SIZE	 0x00004000
set AT91C_IROM 	 0x00400000
set AT91C_IROM_SIZE	 0x00008000
set AT91C_EBI_CS0	 0x10000000
set AT91C_EBI_CS0_SIZE	 0x10000000
set AT91C_EBI_CS1	 0x20000000
set AT91C_EBI_CS1_SIZE	 0x10000000
set AT91C_EBI_SDRAM	 0x20000000
set AT91C_EBI_SDRAM_SIZE	 0x10000000
set AT91C_EBI_SDRAM_16BIT	 0x20000000
set AT91C_EBI_SDRAM_16BIT_SIZE	 0x02000000
set AT91C_EBI_SDRAM_32BIT	 0x20000000
set AT91C_EBI_SDRAM_32BIT_SIZE	 0x04000000
set AT91C_EBI_CS2	 0x30000000
set AT91C_EBI_CS2_SIZE	 0x10000000
set AT91C_EBI_CS3	 0x40000000
set AT91C_EBI_CS3_SIZE	 0x10000000
set AT91C_EBI_SM	 0x40000000
set AT91C_EBI_SM_SIZE	 0x10000000
set AT91C_EBI_CS4	 0x50000000
set AT91C_EBI_CS4_SIZE	 0x10000000
set AT91C_EBI_CF0	 0x50000000
set AT91C_EBI_CF0_SIZE	 0x10000000
set AT91C_EBI_CS5	 0x60000000
set AT91C_EBI_CS5_SIZE	 0x10000000
set AT91C_EBI_CF1	 0x60000000
set AT91C_EBI_CF1_SIZE	 0x10000000


# *****************************************************************************
#               ATTRIBUTES DEFINITIONS FOR AT91SAM9RL64
# *****************************************************************************
array set AT91SAM9RL64_att {
	PDC 	{ LP 	PDC_DBGU_att 	PDC_MCI_att 	PDC_TWI0_att 	PDC_US0_att 	PDC_US1_att 	PDC_US2_att 	PDC_US3_att 	PDC_SSC0_att 	PDC_SSC1_att 	PDC_SPI_att 	PDC_TSC_att 	PDC_AC97C_att }
	DBGU 	{ LP 	DBGU_att }
	EBI 	{ LP 	EBI_att }
	PWMC_CH 	{ LP 	PWMC_CH0_att 	PWMC_CH1_att 	PWMC_CH2_att 	PWMC_CH3_att }
	SYS 	{ LP 	SYS_att }
	SHDWC 	{ LP 	SHDWC_att }
	RTC 	{ LP 	RTC_att }
	SPI 	{ LP 	SPI_att }
	SSC 	{ LP 	SSC0_att 	SSC1_att }
	TCB 	{ LP 	TCB0_att 	TCB1_att 	TCB2_att }
	PWMC 	{ LP 	PWMC_att }
	LCDC 	{ LP 	LCDC_att 	LCDC_16B_TFT_att }
	TSC 	{ LP 	TSC_att }
	HDMA 	{ LP 	HDMA_att }
	TC 	{ LP 	TC0_att 	TC1_att 	TC2_att }
	PITC 	{ LP 	PITC_att }
	HDMA_CH 	{ LP 	HDMA_CH_0_att 	HDMA_CH_1_att }
	CCFG 	{ LP 	CCFG_att }
	UDPHS_EPT 	{ LP 	UDPHS_EPT_0_att 	UDPHS_EPT_1_att 	UDPHS_EPT_2_att 	UDPHS_EPT_3_att 	UDPHS_EPT_4_att 	UDPHS_EPT_5_att 	UDPHS_EPT_6_att 	UDPHS_EPT_7_att 	UDPHS_EPT_8_att 	UDPHS_EPT_9_att 	UDPHS_EPT_10_att 	UDPHS_EPT_11_att 	UDPHS_EPT_12_att 	UDPHS_EPT_13_att 	UDPHS_EPT_14_att 	UDPHS_EPT_15_att }
	MATRIX 	{ LP 	MATRIX_att }
	UDPHS_DMA 	{ LP 	UDPHS_DMA_1_att 	UDPHS_DMA_2_att 	UDPHS_DMA_3_att 	UDPHS_DMA_4_att 	UDPHS_DMA_5_att 	UDPHS_DMA_6_att 	UDPHS_DMA_7_att }
	PMC 	{ LP 	PMC_att }
	RSTC 	{ LP 	RSTC_att }
	AC97C 	{ LP 	AC97C_att }
	CKGR 	{ LP 	CKGR_att }
	UDPHS 	{ LP 	UDPHS_att }
	UDPHS_EPTFIFO 	{ LP 	UDPHS_EPTFIFO_att }
	PIO 	{ LP 	PIOA_att 	PIOB_att 	PIOC_att 	PIOD_att }
	RTTC 	{ LP 	RTTC_att }
	TWI 	{ LP 	TWI0_att 	TWI1_att }
	SDRAMC 	{ LP 	SDRAMC_att }
	USART 	{ LP 	US0_att 	US1_att 	US2_att 	US3_att }
	MCI 	{ LP 	MCI_att }
	WDTC 	{ LP 	WDTC_att }
	SMC 	{ LP 	SMC_att }
	ECC 	{ LP 	HECC_att }
	AIC 	{ LP 	AIC_att }

}
# ========== Peripheral attributes for PDC peripheral ========== 
array set PDC_DBGU_att {
	TNCR 	{ R AT91C_DBGU_TNCR 	RW }
	RNCR 	{ R AT91C_DBGU_RNCR 	RW }
	PTCR 	{ R AT91C_DBGU_PTCR 	WO }
	PTSR 	{ R AT91C_DBGU_PTSR 	RO }
	RCR 	{ R AT91C_DBGU_RCR 	RW }
	TCR 	{ R AT91C_DBGU_TCR 	RW }
	RPR 	{ R AT91C_DBGU_RPR 	RW }
	TPR 	{ R AT91C_DBGU_TPR 	RW }
	RNPR 	{ R AT91C_DBGU_RNPR 	RW }
	TNPR 	{ R AT91C_DBGU_TNPR 	RW }
	listeReg 	{ TNCR RNCR PTCR PTSR RCR TCR RPR TPR RNPR TNPR  }

}
array set PDC_MCI_att {
	PTCR 	{ R AT91C_MCI_PTCR 	WO }
	TNPR 	{ R AT91C_MCI_TNPR 	RW }
	RNPR 	{ R AT91C_MCI_RNPR 	RW }
	TPR 	{ R AT91C_MCI_TPR 	RW }
	RPR 	{ R AT91C_MCI_RPR 	RW }
	PTSR 	{ R AT91C_MCI_PTSR 	RO }
	TNCR 	{ R AT91C_MCI_TNCR 	RW }
	RNCR 	{ R AT91C_MCI_RNCR 	RW }
	TCR 	{ R AT91C_MCI_TCR 	RW }
	RCR 	{ R AT91C_MCI_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}
array set PDC_TWI0_att {
	PTSR 	{ R AT91C_TWI0_PTSR 	RO }
	TNCR 	{ R AT91C_TWI0_TNCR 	RW }
	RNCR 	{ R AT91C_TWI0_RNCR 	RW }
	TCR 	{ R AT91C_TWI0_TCR 	RW }
	RCR 	{ R AT91C_TWI0_RCR 	RW }
	PTCR 	{ R AT91C_TWI0_PTCR 	WO }
	TNPR 	{ R AT91C_TWI0_TNPR 	RW }
	RNPR 	{ R AT91C_TWI0_RNPR 	RW }
	TPR 	{ R AT91C_TWI0_TPR 	RW }
	RPR 	{ R AT91C_TWI0_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}
array set PDC_US0_att {
	TNCR 	{ R AT91C_US0_TNCR 	RW }
	RNCR 	{ R AT91C_US0_RNCR 	RW }
	TCR 	{ R AT91C_US0_TCR 	RW }
	RCR 	{ R AT91C_US0_RCR 	RW }
	PTCR 	{ R AT91C_US0_PTCR 	WO }
	TNPR 	{ R AT91C_US0_TNPR 	RW }
	RNPR 	{ R AT91C_US0_RNPR 	RW }
	PTSR 	{ R AT91C_US0_PTSR 	RO }
	RPR 	{ R AT91C_US0_RPR 	RW }
	TPR 	{ R AT91C_US0_TPR 	RW }
	listeReg 	{ TNCR RNCR TCR RCR PTCR TNPR RNPR PTSR RPR TPR  }

}
array set PDC_US1_att {
	PTCR 	{ R AT91C_US1_PTCR 	WO }
	TNPR 	{ R AT91C_US1_TNPR 	RW }
	RNPR 	{ R AT91C_US1_RNPR 	RW }
	TPR 	{ R AT91C_US1_TPR 	RW }
	RPR 	{ R AT91C_US1_RPR 	RW }
	PTSR 	{ R AT91C_US1_PTSR 	RO }
	TNCR 	{ R AT91C_US1_TNCR 	RW }
	RNCR 	{ R AT91C_US1_RNCR 	RW }
	TCR 	{ R AT91C_US1_TCR 	RW }
	RCR 	{ R AT91C_US1_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}
array set PDC_US2_att {
	PTSR 	{ R AT91C_US2_PTSR 	RO }
	TNCR 	{ R AT91C_US2_TNCR 	RW }
	RNCR 	{ R AT91C_US2_RNCR 	RW }
	TCR 	{ R AT91C_US2_TCR 	RW }
	RCR 	{ R AT91C_US2_RCR 	RW }
	PTCR 	{ R AT91C_US2_PTCR 	WO }
	TNPR 	{ R AT91C_US2_TNPR 	RW }
	RNPR 	{ R AT91C_US2_RNPR 	RW }
	TPR 	{ R AT91C_US2_TPR 	RW }
	RPR 	{ R AT91C_US2_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}
array set PDC_US3_att {
	PTSR 	{ R AT91C_US3_PTSR 	RO }
	TNCR 	{ R AT91C_US3_TNCR 	RW }
	RNCR 	{ R AT91C_US3_RNCR 	RW }
	TCR 	{ R AT91C_US3_TCR 	RW }
	RCR 	{ R AT91C_US3_RCR 	RW }
	PTCR 	{ R AT91C_US3_PTCR 	WO }
	TNPR 	{ R AT91C_US3_TNPR 	RW }
	RNPR 	{ R AT91C_US3_RNPR 	RW }
	TPR 	{ R AT91C_US3_TPR 	RW }
	RPR 	{ R AT91C_US3_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}
array set PDC_SSC0_att {
	PTCR 	{ R AT91C_SSC0_PTCR 	WO }
	TNPR 	{ R AT91C_SSC0_TNPR 	RW }
	RNPR 	{ R AT91C_SSC0_RNPR 	RW }
	TPR 	{ R AT91C_SSC0_TPR 	RW }
	RPR 	{ R AT91C_SSC0_RPR 	RW }
	PTSR 	{ R AT91C_SSC0_PTSR 	RO }
	TNCR 	{ R AT91C_SSC0_TNCR 	RW }
	RNCR 	{ R AT91C_SSC0_RNCR 	RW }
	TCR 	{ R AT91C_SSC0_TCR 	RW }
	RCR 	{ R AT91C_SSC0_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}
array set PDC_SSC1_att {
	PTSR 	{ R AT91C_SSC1_PTSR 	RO }
	TNCR 	{ R AT91C_SSC1_TNCR 	RW }
	RNCR 	{ R AT91C_SSC1_RNCR 	RW }
	TCR 	{ R AT91C_SSC1_TCR 	RW }
	RCR 	{ R AT91C_SSC1_RCR 	RW }
	PTCR 	{ R AT91C_SSC1_PTCR 	WO }
	TNPR 	{ R AT91C_SSC1_TNPR 	RW }
	RNPR 	{ R AT91C_SSC1_RNPR 	RW }
	TPR 	{ R AT91C_SSC1_TPR 	RW }
	RPR 	{ R AT91C_SSC1_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}
array set PDC_SPI_att {
	PTSR 	{ R AT91C_SPI_PTSR 	RO }
	TNCR 	{ R AT91C_SPI_TNCR 	RW }
	RNCR 	{ R AT91C_SPI_RNCR 	RW }
	TCR 	{ R AT91C_SPI_TCR 	RW }
	RCR 	{ R AT91C_SPI_RCR 	RW }
	PTCR 	{ R AT91C_SPI_PTCR 	WO }
	TNPR 	{ R AT91C_SPI_TNPR 	RW }
	RNPR 	{ R AT91C_SPI_RNPR 	RW }
	TPR 	{ R AT91C_SPI_TPR 	RW }
	RPR 	{ R AT91C_SPI_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}
array set PDC_TSC_att {
	PTCR 	{ R AT91C_TSC_PTCR 	WO }
	TNPR 	{ R AT91C_TSC_TNPR 	RW }
	RNPR 	{ R AT91C_TSC_RNPR 	RW }
	TPR 	{ R AT91C_TSC_TPR 	RW }
	RPR 	{ R AT91C_TSC_RPR 	RW }
	PTSR 	{ R AT91C_TSC_PTSR 	RO }
	TNCR 	{ R AT91C_TSC_TNCR 	RW }
	RNCR 	{ R AT91C_TSC_RNCR 	RW }
	TCR 	{ R AT91C_TSC_TCR 	RW }
	RCR 	{ R AT91C_TSC_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}
array set PDC_AC97C_att {
	PTCR 	{ R AT91C_AC97C_PTCR 	WO }
	TNPR 	{ R AT91C_AC97C_TNPR 	RW }
	RNPR 	{ R AT91C_AC97C_RNPR 	RW }
	TPR 	{ R AT91C_AC97C_TPR 	RW }
	RPR 	{ R AT91C_AC97C_RPR 	RW }
	PTSR 	{ R AT91C_AC97C_PTSR 	RO }
	TNCR 	{ R AT91C_AC97C_TNCR 	RW }
	RNCR 	{ R AT91C_AC97C_RNCR 	RW }
	TCR 	{ R AT91C_AC97C_TCR 	RW }
	RCR 	{ R AT91C_AC97C_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}

# ========== Peripheral attributes for DBGU peripheral ========== 
array set DBGU_att {
	EXID 	{ R AT91C_DBGU_EXID 	RO }
	THR 	{ R AT91C_DBGU_THR 	WO }
	CSR 	{ R AT91C_DBGU_CSR 	RO }
	IDR 	{ R AT91C_DBGU_IDR 	WO }
	MR 	{ R AT91C_DBGU_MR 	RW }
	FNTR 	{ R AT91C_DBGU_FNTR 	RW }
	CIDR 	{ R AT91C_DBGU_CIDR 	RO }
	BRGR 	{ R AT91C_DBGU_BRGR 	RW }
	RHR 	{ R AT91C_DBGU_RHR 	RO }
	IMR 	{ R AT91C_DBGU_IMR 	RO }
	IER 	{ R AT91C_DBGU_IER 	WO }
	CR 	{ R AT91C_DBGU_CR 	WO }
	listeReg 	{ EXID THR CSR IDR MR FNTR CIDR BRGR RHR IMR IER CR  }

}

# ========== Peripheral attributes for EBI peripheral ========== 
array set EBI_att {
	DUMMY 	{ R AT91C_EBI_DUMMY 	RW }
	listeReg 	{ DUMMY  }

}

# ========== Peripheral attributes for PWMC_CH peripheral ========== 
array set PWMC_CH0_att {
	CUPDR 	{ R AT91C_PWMC_CH0_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH0_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH0_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH0_Reserved 	WO  3 }
	CCNTR 	{ R AT91C_PWMC_CH0_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH0_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}
array set PWMC_CH1_att {
	CUPDR 	{ R AT91C_PWMC_CH1_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH1_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH1_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH1_Reserved 	WO  3 }
	CCNTR 	{ R AT91C_PWMC_CH1_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH1_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}
array set PWMC_CH2_att {
	CUPDR 	{ R AT91C_PWMC_CH2_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH2_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH2_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH2_Reserved 	WO  3 }
	CCNTR 	{ R AT91C_PWMC_CH2_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH2_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}
array set PWMC_CH3_att {
	CUPDR 	{ R AT91C_PWMC_CH3_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH3_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH3_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH3_Reserved 	WO  3 }
	CCNTR 	{ R AT91C_PWMC_CH3_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH3_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}

# ========== Peripheral attributes for SYS peripheral ========== 
array set SYS_att {
	SLCKSEL 	{ R AT91C_SYS_SLCKSEL 	 }
	GPBR 	{ R AT91C_SYS_GPBR 	  4 }
	listeReg 	{ SLCKSEL GPBR  }

}

# ========== Peripheral attributes for SHDWC peripheral ========== 
array set SHDWC_att {
	SHMR 	{ R AT91C_SHDWC_SHMR 	RW }
	SHSR 	{ R AT91C_SHDWC_SHSR 	RO }
	SHCR 	{ R AT91C_SHDWC_SHCR 	WO }
	listeReg 	{ SHMR SHSR SHCR  }

}

# ========== Peripheral attributes for RTC peripheral ========== 
array set RTC_att {
	IMR 	{ R AT91C_RTC_IMR 	RO }
	IER 	{ R AT91C_RTC_IER 	WO }
	SR 	{ R AT91C_RTC_SR 	RO }
	TIMALR 	{ R AT91C_RTC_TIMALR 	RW }
	TIMR 	{ R AT91C_RTC_TIMR 	RW }
	CR 	{ R AT91C_RTC_CR 	RW }
	VER 	{ R AT91C_RTC_VER 	RO }
	IDR 	{ R AT91C_RTC_IDR 	WO }
	SCCR 	{ R AT91C_RTC_SCCR 	WO }
	CALALR 	{ R AT91C_RTC_CALALR 	RW }
	CALR 	{ R AT91C_RTC_CALR 	RW }
	MR 	{ R AT91C_RTC_MR 	RW }
	listeReg 	{ IMR IER SR TIMALR TIMR CR VER IDR SCCR CALALR CALR MR  }

}

# ========== Peripheral attributes for SPI peripheral ========== 
array set SPI_att {
	IMR 	{ R AT91C_SPI_IMR 	RO }
	IER 	{ R AT91C_SPI_IER 	WO }
	TDR 	{ R AT91C_SPI_TDR 	WO }
	MR 	{ R AT91C_SPI_MR 	RW }
	CSR 	{ R AT91C_SPI_CSR 	RW  4 }
	IDR 	{ R AT91C_SPI_IDR 	WO }
	SR 	{ R AT91C_SPI_SR 	RO }
	RDR 	{ R AT91C_SPI_RDR 	RO }
	CR 	{ R AT91C_SPI_CR 	RO }
	listeReg 	{ IMR IER TDR MR CSR IDR SR RDR CR  }

}

# ========== Peripheral attributes for SSC peripheral ========== 
array set SSC0_att {
	RSHR 	{ R AT91C_SSC0_RSHR 	RO }
	RHR 	{ R AT91C_SSC0_RHR 	RO }
	TCMR 	{ R AT91C_SSC0_TCMR 	RW }
	RCMR 	{ R AT91C_SSC0_RCMR 	RW }
	IER 	{ R AT91C_SSC0_IER 	WO }
	TSHR 	{ R AT91C_SSC0_TSHR 	RW }
	THR 	{ R AT91C_SSC0_THR 	WO }
	IDR 	{ R AT91C_SSC0_IDR 	WO }
	SR 	{ R AT91C_SSC0_SR 	RO }
	CR 	{ R AT91C_SSC0_CR 	WO }
	IMR 	{ R AT91C_SSC0_IMR 	RO }
	CMR 	{ R AT91C_SSC0_CMR 	RW }
	RFMR 	{ R AT91C_SSC0_RFMR 	RW }
	TFMR 	{ R AT91C_SSC0_TFMR 	RW }
	listeReg 	{ RSHR RHR TCMR RCMR IER TSHR THR IDR SR CR IMR CMR RFMR TFMR  }

}
array set SSC1_att {
	IDR 	{ R AT91C_SSC1_IDR 	WO }
	TCMR 	{ R AT91C_SSC1_TCMR 	RW }
	RCMR 	{ R AT91C_SSC1_RCMR 	RW }
	CR 	{ R AT91C_SSC1_CR 	WO }
	THR 	{ R AT91C_SSC1_THR 	WO }
	TFMR 	{ R AT91C_SSC1_TFMR 	RW }
	RFMR 	{ R AT91C_SSC1_RFMR 	RW }
	SR 	{ R AT91C_SSC1_SR 	RO }
	RHR 	{ R AT91C_SSC1_RHR 	RO }
	RSHR 	{ R AT91C_SSC1_RSHR 	RO }
	IMR 	{ R AT91C_SSC1_IMR 	RO }
	IER 	{ R AT91C_SSC1_IER 	WO }
	CMR 	{ R AT91C_SSC1_CMR 	RW }
	TSHR 	{ R AT91C_SSC1_TSHR 	RW }
	listeReg 	{ IDR TCMR RCMR CR THR TFMR RFMR SR RHR RSHR IMR IER CMR TSHR  }

}

# ========== Peripheral attributes for TCB peripheral ========== 
array set TCB0_att {
	BMR 	{ R AT91C_TCB0_BMR 	RW }
	BCR 	{ R AT91C_TCB0_BCR 	WO }
	listeReg 	{ BMR BCR  }

}
array set TCB1_att {
	BMR 	{ R AT91C_TCB1_BMR 	RW }
	BCR 	{ R AT91C_TCB1_BCR 	WO }
	listeReg 	{ BMR BCR  }

}
array set TCB2_att {
	BCR 	{ R AT91C_TCB2_BCR 	WO }
	BMR 	{ R AT91C_TCB2_BMR 	RW }
	listeReg 	{ BCR BMR  }

}

# ========== Peripheral attributes for PWMC peripheral ========== 
array set PWMC_att {
	VR 	{ R AT91C_PWMC_VR 	RO }
	IMR 	{ R AT91C_PWMC_IMR 	RO }
	IER 	{ R AT91C_PWMC_IER 	WO }
	DIS 	{ R AT91C_PWMC_DIS 	WO }
	MR 	{ R AT91C_PWMC_MR 	RW }
	ISR 	{ R AT91C_PWMC_ISR 	RO }
	IDR 	{ R AT91C_PWMC_IDR 	WO }
	SR 	{ R AT91C_PWMC_SR 	RO }
	ENA 	{ R AT91C_PWMC_ENA 	WO }
	listeReg 	{ VR IMR IER DIS MR ISR IDR SR ENA  }

}

# ========== Peripheral attributes for LCDC peripheral ========== 
array set LCDC_att {
	ENTRY 	{ R AT91C_LCDC_LUT_ENTRY 	RW 256 }
	CTRSTVAL 	{ R AT91C_LCDC_CTRSTVAL 	RW }
	PWRCON 	{ R AT91C_LCDC_PWRCON 	RW }
	5 	{ R AT91C_LCDC_DP4_5 	RW }
	7 	{ R AT91C_LCDC_DP5_7 	RW }
	5 	{ R AT91C_LCDC_DP3_5 	RW }
	2 	{ R AT91C_LCDC_DP1_2 	RW }
	FIFO 	{ R AT91C_LCDC_FIFO 	RW }
	TIM2 	{ R AT91C_LCDC_TIM2 	RW }
	LCDCON2 	{ R AT91C_LCDC_LCDCON2 	RW }
	DMACON 	{ R AT91C_LCDC_DMACON 	RW }
	FRMA2 	{ R AT91C_LCDC_FRMA2 	RO }
	ITR 	{ R AT91C_LCDC_ITR 	WO }
	ICR 	{ R AT91C_LCDC_ICR 	WO }
	IMR 	{ R AT91C_LCDC_IMR 	RO }
	IER 	{ R AT91C_LCDC_IER 	WO }
	FRMP2 	{ R AT91C_LCDC_FRMP2 	RO }
	BA2 	{ R AT91C_LCDC_BA2 	RW }
	CTRSTCON 	{ R AT91C_LCDC_CTRSTCON 	RW }
	7 	{ R AT91C_LCDC_DP6_7 	RW }
	4 	{ R AT91C_LCDC_DP3_4 	RW }
	3 	{ R AT91C_LCDC_DP2_3 	RW }
	7 	{ R AT91C_LCDC_DP4_7 	RW }
	MVAL 	{ R AT91C_LCDC_MVAL 	RW }
	LCDFRCFG 	{ R AT91C_LCDC_LCDFRCFG 	RW }
	TIM1 	{ R AT91C_LCDC_TIM1 	RW }
	LCDCON1 	{ R AT91C_LCDC_LCDCON1 	RW }
	DMA2DCFG 	{ R AT91C_LCDC_DMA2DCFG 	RW }
	FRMCFG 	{ R AT91C_LCDC_FRMCFG 	RW }
	IRR 	{ R AT91C_LCDC_IRR 	RW }
	GPR 	{ R AT91C_LCDC_GPR 	RW }
	ISR 	{ R AT91C_LCDC_ISR 	RO }
	IDR 	{ R AT91C_LCDC_IDR 	WO }
	FRMA1 	{ R AT91C_LCDC_FRMA1 	RO }
	FRMP1 	{ R AT91C_LCDC_FRMP1 	RO }
	BA1 	{ R AT91C_LCDC_BA1 	RW }
	listeReg 	{ ENTRY CTRSTVAL PWRCON 5 7 5 2 FIFO TIM2 LCDCON2 DMACON FRMA2 ITR ICR IMR IER FRMP2 BA2 CTRSTCON 7 4 3 7 MVAL LCDFRCFG TIM1 LCDCON1 DMA2DCFG FRMCFG IRR GPR ISR IDR FRMA1 FRMP1 BA1  }

}
array set LCDC_16B_TFT_att {
	ENTRY 	{ R AT91C_TFT_LUT_ENTRY 	RW 256 }
	CTRSTVAL 	{ R AT91C_TFT_CTRSTVAL 	RW }
	PWRCON 	{ R AT91C_TFT_PWRCON 	RW }
	5 	{ R AT91C_TFT_DP4_5 	RW }
	7 	{ R AT91C_TFT_DP5_7 	RW }
	5 	{ R AT91C_TFT_DP3_5 	RW }
	2 	{ R AT91C_TFT_DP1_2 	RW }
	FIFO 	{ R AT91C_TFT_FIFO 	RW }
	TIM2 	{ R AT91C_TFT_TIM2 	RW }
	LCDCON2 	{ R AT91C_TFT_LCDCON2 	RW }
	DMACON 	{ R AT91C_TFT_DMACON 	RW }
	FRMA2 	{ R AT91C_TFT_FRMA2 	RO }
	ITR 	{ R AT91C_TFT_ITR 	WO }
	ICR 	{ R AT91C_TFT_ICR 	WO }
	IMR 	{ R AT91C_TFT_IMR 	RO }
	IER 	{ R AT91C_TFT_IER 	WO }
	FRMP2 	{ R AT91C_TFT_FRMP2 	RO }
	BA2 	{ R AT91C_TFT_BA2 	RW }
	CTRSTCON 	{ R AT91C_TFT_CTRSTCON 	RW }
	7 	{ R AT91C_TFT_DP6_7 	RW }
	4 	{ R AT91C_TFT_DP3_4 	RW }
	3 	{ R AT91C_TFT_DP2_3 	RW }
	7 	{ R AT91C_TFT_DP4_7 	RW }
	MVAL 	{ R AT91C_TFT_MVAL 	RW }
	LCDFRCFG 	{ R AT91C_TFT_LCDFRCFG 	RW }
	TIM1 	{ R AT91C_TFT_TIM1 	RW }
	LCDCON1 	{ R AT91C_TFT_LCDCON1 	RW }
	DMA2DCFG 	{ R AT91C_TFT_DMA2DCFG 	RW }
	FRMCFG 	{ R AT91C_TFT_FRMCFG 	RW }
	IRR 	{ R AT91C_TFT_IRR 	RW }
	GPR 	{ R AT91C_TFT_GPR 	RW }
	ISR 	{ R AT91C_TFT_ISR 	RO }
	IDR 	{ R AT91C_TFT_IDR 	WO }
	FRMA1 	{ R AT91C_TFT_FRMA1 	RO }
	FRMP1 	{ R AT91C_TFT_FRMP1 	RO }
	BA1 	{ R AT91C_TFT_BA1 	RW }
	listeReg 	{ ENTRY CTRSTVAL PWRCON 5 7 5 2 FIFO TIM2 LCDCON2 DMACON FRMA2 ITR ICR IMR IER FRMP2 BA2 CTRSTCON 7 4 3 7 MVAL LCDFRCFG TIM1 LCDCON1 DMA2DCFG FRMCFG IRR GPR ISR IDR FRMA1 FRMP1 BA1  }

}

# ========== Peripheral attributes for TSC peripheral ========== 
array set TSC_att {
	listeReg 	{  }

}

# ========== Peripheral attributes for HDMA peripheral ========== 
array set HDMA_att {
	RSVD0 	{ R AT91C_HDMA_RSVD0 	WO }
	CHDR 	{ R AT91C_HDMA_CHDR 	WO }
	EBCISR 	{ R AT91C_HDMA_EBCISR 	RO }
	EBCIDR 	{ R AT91C_HDMA_EBCIDR 	WO }
	SYNC 	{ R AT91C_HDMA_SYNC 	RW }
	BREQ 	{ R AT91C_HDMA_BREQ 	RW }
	EN 	{ R AT91C_HDMA_EN 	RW }
	RSVD1 	{ R AT91C_HDMA_RSVD1 	WO }
	CHSR 	{ R AT91C_HDMA_CHSR 	RO }
	CHER 	{ R AT91C_HDMA_CHER 	WO }
	EBCIMR 	{ R AT91C_HDMA_EBCIMR 	RO }
	EBCIER 	{ R AT91C_HDMA_EBCIER 	WO }
	LAST 	{ R AT91C_HDMA_LAST 	RW }
	SREQ 	{ R AT91C_HDMA_SREQ 	RW }
	GCFG 	{ R AT91C_HDMA_GCFG 	RW }
	listeReg 	{ RSVD0 CHDR EBCISR EBCIDR SYNC BREQ EN RSVD1 CHSR CHER EBCIMR EBCIER LAST SREQ GCFG  }

}

# ========== Peripheral attributes for TC peripheral ========== 
array set TC0_att {
	IMR 	{ R AT91C_TC0_IMR 	RO }
	IER 	{ R AT91C_TC0_IER 	WO }
	RC 	{ R AT91C_TC0_RC 	RW }
	RA 	{ R AT91C_TC0_RA 	RW }
	CMR 	{ R AT91C_TC0_CMR 	RW }
	IDR 	{ R AT91C_TC0_IDR 	WO }
	SR 	{ R AT91C_TC0_SR 	RO }
	RB 	{ R AT91C_TC0_RB 	RW }
	CV 	{ R AT91C_TC0_CV 	RW }
	CCR 	{ R AT91C_TC0_CCR 	WO }
	listeReg 	{ IMR IER RC RA CMR IDR SR RB CV CCR  }

}
array set TC1_att {
	IMR 	{ R AT91C_TC1_IMR 	RO }
	IER 	{ R AT91C_TC1_IER 	WO }
	RC 	{ R AT91C_TC1_RC 	RW }
	RA 	{ R AT91C_TC1_RA 	RW }
	CMR 	{ R AT91C_TC1_CMR 	RW }
	IDR 	{ R AT91C_TC1_IDR 	WO }
	SR 	{ R AT91C_TC1_SR 	RO }
	RB 	{ R AT91C_TC1_RB 	RW }
	CV 	{ R AT91C_TC1_CV 	RW }
	CCR 	{ R AT91C_TC1_CCR 	WO }
	listeReg 	{ IMR IER RC RA CMR IDR SR RB CV CCR  }

}
array set TC2_att {
	IMR 	{ R AT91C_TC2_IMR 	RO }
	IER 	{ R AT91C_TC2_IER 	WO }
	RC 	{ R AT91C_TC2_RC 	RW }
	RA 	{ R AT91C_TC2_RA 	RW }
	CMR 	{ R AT91C_TC2_CMR 	RW }
	IDR 	{ R AT91C_TC2_IDR 	WO }
	SR 	{ R AT91C_TC2_SR 	RO }
	RB 	{ R AT91C_TC2_RB 	RW }
	CV 	{ R AT91C_TC2_CV 	RW }
	CCR 	{ R AT91C_TC2_CCR 	WO }
	listeReg 	{ IMR IER RC RA CMR IDR SR RB CV CCR  }

}

# ========== Peripheral attributes for PITC peripheral ========== 
array set PITC_att {
	PIIR 	{ R AT91C_PITC_PIIR 	RO }
	PISR 	{ R AT91C_PITC_PISR 	RO }
	PIVR 	{ R AT91C_PITC_PIVR 	RO }
	PIMR 	{ R AT91C_PITC_PIMR 	RW }
	listeReg 	{ PIIR PISR PIVR PIMR  }

}

# ========== Peripheral attributes for HDMA_CH peripheral ========== 
array set HDMA_CH_0_att {
	CADDR 	{ R AT91C_HDMA_CH_0_CADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_0_DPIP 	RW }
	CFG 	{ R AT91C_HDMA_CH_0_CFG 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_0_CTRLA 	RW }
	DADDR 	{ R AT91C_HDMA_CH_0_DADDR 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_0_BDSCR 	RW }
	SPIP 	{ R AT91C_HDMA_CH_0_SPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_0_CTRLB 	RW }
	DSCR 	{ R AT91C_HDMA_CH_0_DSCR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_0_SADDR 	RW }
	listeReg 	{ CADDR DPIP CFG CTRLA DADDR BDSCR SPIP CTRLB DSCR SADDR  }

}
array set HDMA_CH_1_att {
	CADDR 	{ R AT91C_HDMA_CH_1_CADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_1_DPIP 	RW }
	CFG 	{ R AT91C_HDMA_CH_1_CFG 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_1_CTRLA 	RW }
	DADDR 	{ R AT91C_HDMA_CH_1_DADDR 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_1_BDSCR 	RW }
	SPIP 	{ R AT91C_HDMA_CH_1_SPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_1_CTRLB 	RW }
	DSCR 	{ R AT91C_HDMA_CH_1_DSCR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_1_SADDR 	RW }
	listeReg 	{ CADDR DPIP CFG CTRLA DADDR BDSCR SPIP CTRLB DSCR SADDR  }

}

# ========== Peripheral attributes for CCFG peripheral ========== 
array set CCFG_att {
	MATRIXVERSION 	{ R AT91C_CCFG_MATRIXVERSION 	RO }
	EBICSA 	{ R AT91C_CCFG_EBICSA 	RW }
	UDPHS 	{ R AT91C_CCFG_UDPHS 	RW }
	TCMR 	{ R AT91C_CCFG_TCMR 	RW }
	listeReg 	{ MATRIXVERSION EBICSA UDPHS TCMR  }

}

# ========== Peripheral attributes for UDPHS_EPT peripheral ========== 
array set UDPHS_EPT_0_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_0_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_0_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_0_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_0_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_0_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_0_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_0_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_1_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_1_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_1_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_1_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_1_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_1_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_1_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_1_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_2_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_2_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_2_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_2_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_2_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_2_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_2_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_2_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_3_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_3_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_3_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_3_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_3_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_3_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_3_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_3_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_4_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_4_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_4_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_4_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_4_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_4_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_4_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_4_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_5_att {
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_5_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_5_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_5_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_5_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_5_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_5_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_5_EPTCLRSTA 	WO }
	listeReg 	{ EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA  }

}
array set UDPHS_EPT_6_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_6_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_6_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_6_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_6_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_6_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_6_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_6_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_7_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_7_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_7_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_7_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_7_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_7_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_7_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_7_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_8_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_8_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_8_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_8_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_8_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_8_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_8_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_8_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_9_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_9_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_9_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_9_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_9_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_9_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_9_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_9_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_10_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_10_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_10_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_10_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_10_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_10_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_10_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_10_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_11_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_11_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_11_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_11_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_11_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_11_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_11_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_11_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_12_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_12_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_12_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_12_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_12_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_12_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_12_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_12_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_13_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_13_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_13_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_13_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_13_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_13_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_13_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_13_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_14_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_14_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_14_EPTSETSTA 	WO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_14_EPTCTLENB 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_14_EPTCTL 	RO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_14_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_14_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_14_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTLENB EPTCTL EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_15_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_15_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_15_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_15_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_15_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_15_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_15_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_15_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}

# ========== Peripheral attributes for MATRIX peripheral ========== 
array set MATRIX_att {
	MCFG1 	{ R AT91C_MATRIX_MCFG1 	RW }
	MRCR 	{ R AT91C_MATRIX_MRCR 	RW }
	PRAS7 	{ R AT91C_MATRIX_PRAS7 	RW }
	PRAS5 	{ R AT91C_MATRIX_PRAS5 	RW }
	SCFG4 	{ R AT91C_MATRIX_SCFG4 	RW }
	MCFG2 	{ R AT91C_MATRIX_MCFG2 	RW }
	PRBS7 	{ R AT91C_MATRIX_PRBS7 	RW }
	MCFG6 	{ R AT91C_MATRIX_MCFG6 	RW }
	PRBS0 	{ R AT91C_MATRIX_PRBS0 	RW }
	MCFG7 	{ R AT91C_MATRIX_MCFG7 	RW }
	PRAS3 	{ R AT91C_MATRIX_PRAS3 	RW }
	PRAS1 	{ R AT91C_MATRIX_PRAS1 	RW }
	SCFG0 	{ R AT91C_MATRIX_SCFG0 	RW }
	PRBS5 	{ R AT91C_MATRIX_PRBS5 	RW }
	PRBS3 	{ R AT91C_MATRIX_PRBS3 	RW }
	PRBS1 	{ R AT91C_MATRIX_PRBS1 	RW }
	SCFG5 	{ R AT91C_MATRIX_SCFG5 	RW }
	SCFG1 	{ R AT91C_MATRIX_SCFG1 	RW }
	PRAS4 	{ R AT91C_MATRIX_PRAS4 	RW }
	PRAS6 	{ R AT91C_MATRIX_PRAS6 	RW }
	SCFG6 	{ R AT91C_MATRIX_SCFG6 	RW }
	MCFG0 	{ R AT91C_MATRIX_MCFG0 	RW }
	PRBS6 	{ R AT91C_MATRIX_PRBS6 	RW }
	MCFG3 	{ R AT91C_MATRIX_MCFG3 	RW }
	MCFG8 	{ R AT91C_MATRIX_MCFG8 	RW }
	MCFG4 	{ R AT91C_MATRIX_MCFG4 	RW }
	MCFG5 	{ R AT91C_MATRIX_MCFG5 	RW }
	PRAS0 	{ R AT91C_MATRIX_PRAS0 	RW }
	PRAS2 	{ R AT91C_MATRIX_PRAS2 	RW }
	SCFG2 	{ R AT91C_MATRIX_SCFG2 	RW }
	PRBS2 	{ R AT91C_MATRIX_PRBS2 	RW }
	PRBS4 	{ R AT91C_MATRIX_PRBS4 	RW }
	SCFG3 	{ R AT91C_MATRIX_SCFG3 	RW }
	SCFG7 	{ R AT91C_MATRIX_SCFG7 	RW }
	listeReg 	{ MCFG1 MRCR PRAS7 PRAS5 SCFG4 MCFG2 PRBS7 MCFG6 PRBS0 MCFG7 PRAS3 PRAS1 SCFG0 PRBS5 PRBS3 PRBS1 SCFG5 SCFG1 PRAS4 PRAS6 SCFG6 MCFG0 PRBS6 MCFG3 MCFG8 MCFG4 MCFG5 PRAS0 PRAS2 SCFG2 PRBS2 PRBS4 SCFG3 SCFG7  }

}

# ========== Peripheral attributes for UDPHS_DMA peripheral ========== 
array set UDPHS_DMA_1_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_1_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_1_DMAADDRESS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_1_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_1_DMANXTDSC 	RW }
	listeReg 	{ DMASTATUS DMAADDRESS DMACONTROL DMANXTDSC  }

}
array set UDPHS_DMA_2_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_2_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_2_DMAADDRESS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_2_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_2_DMANXTDSC 	RW }
	listeReg 	{ DMASTATUS DMAADDRESS DMACONTROL DMANXTDSC  }

}
array set UDPHS_DMA_3_att {
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_3_DMAADDRESS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_3_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_3_DMANXTDSC 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_3_DMASTATUS 	RW }
	listeReg 	{ DMAADDRESS DMACONTROL DMANXTDSC DMASTATUS  }

}
array set UDPHS_DMA_4_att {
	DMACONTROL 	{ R AT91C_UDPHS_DMA_4_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_4_DMANXTDSC 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_4_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_4_DMAADDRESS 	RW }
	listeReg 	{ DMACONTROL DMANXTDSC DMASTATUS DMAADDRESS  }

}
array set UDPHS_DMA_5_att {
	DMACONTROL 	{ R AT91C_UDPHS_DMA_5_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_5_DMANXTDSC 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_5_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_5_DMAADDRESS 	RW }
	listeReg 	{ DMACONTROL DMANXTDSC DMASTATUS DMAADDRESS  }

}
array set UDPHS_DMA_6_att {
	DMACONTROL 	{ R AT91C_UDPHS_DMA_6_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_6_DMANXTDSC 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_6_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_6_DMAADDRESS 	RW }
	listeReg 	{ DMACONTROL DMANXTDSC DMASTATUS DMAADDRESS  }

}
array set UDPHS_DMA_7_att {
	DMACONTROL 	{ R AT91C_UDPHS_DMA_7_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_7_DMANXTDSC 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_7_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_7_DMAADDRESS 	RW }
	listeReg 	{ DMACONTROL DMANXTDSC DMASTATUS DMAADDRESS  }

}

# ========== Peripheral attributes for PMC peripheral ========== 
array set PMC_att {
	SCSR 	{ R AT91C_PMC_SCSR 	RO }
	SCER 	{ R AT91C_PMC_SCER 	WO }
	IMR 	{ R AT91C_PMC_IMR 	RO }
	IDR 	{ R AT91C_PMC_IDR 	WO }
	UCKR 	{ R AT91C_PMC_UCKR 	RW }
	PCDR 	{ R AT91C_PMC_PCDR 	WO }
	SCDR 	{ R AT91C_PMC_SCDR 	WO }
	SR 	{ R AT91C_PMC_SR 	RO }
	IER 	{ R AT91C_PMC_IER 	WO }
	MCKR 	{ R AT91C_PMC_MCKR 	RW }
	PLLAR 	{ R AT91C_PMC_PLLAR 	RW }
	MOR 	{ R AT91C_PMC_MOR 	RW }
	PCER 	{ R AT91C_PMC_PCER 	WO }
	PCSR 	{ R AT91C_PMC_PCSR 	RO }
	PLLBR 	{ R AT91C_PMC_PLLBR 	RW }
	MCFR 	{ R AT91C_PMC_MCFR 	RO }
	PCKR 	{ R AT91C_PMC_PCKR 	RW  8 }
	listeReg 	{ SCSR SCER IMR IDR UCKR PCDR SCDR SR IER MCKR PLLAR MOR PCER PCSR PLLBR MCFR PCKR  }

}

# ========== Peripheral attributes for RSTC peripheral ========== 
array set RSTC_att {
	RSR 	{ R AT91C_RSTC_RSR 	RO }
	RMR 	{ R AT91C_RSTC_RMR 	RW }
	RCR 	{ R AT91C_RSTC_RCR 	WO }
	listeReg 	{ RSR RMR RCR  }

}

# ========== Peripheral attributes for AC97C peripheral ========== 
array set AC97C_att {
	CAMR 	{ R AT91C_AC97C_CAMR 	RW }
	CORHR 	{ R AT91C_AC97C_CORHR 	RO }
	CBSR 	{ R AT91C_AC97C_CBSR 	RO }
	CBRHR 	{ R AT91C_AC97C_CBRHR 	RO }
	CBTHR 	{ R AT91C_AC97C_CBTHR 	WO }
	CBMR 	{ R AT91C_AC97C_CBMR 	RW }
	COTHR 	{ R AT91C_AC97C_COTHR 	WO }
	COMR 	{ R AT91C_AC97C_COMR 	RW }
	IER 	{ R AT91C_AC97C_IER 	WO }
	COSR 	{ R AT91C_AC97C_COSR 	RO }
	SR 	{ R AT91C_AC97C_SR 	RO }
	IDR 	{ R AT91C_AC97C_IDR 	WO }
	MR 	{ R AT91C_AC97C_MR 	RW }
	ICA 	{ R AT91C_AC97C_ICA 	RW }
	VERSION 	{ R AT91C_AC97C_VERSION 	RO }
	IMR 	{ R AT91C_AC97C_IMR 	RO }
	CATHR 	{ R AT91C_AC97C_CATHR 	WO }
	OCA 	{ R AT91C_AC97C_OCA 	RW }
	CASR 	{ R AT91C_AC97C_CASR 	RO }
	CARHR 	{ R AT91C_AC97C_CARHR 	RO }
	listeReg 	{ CAMR CORHR CBSR CBRHR CBTHR CBMR COTHR COMR IER COSR SR IDR MR ICA VERSION IMR CATHR OCA CASR CARHR  }

}

# ========== Peripheral attributes for CKGR peripheral ========== 
array set CKGR_att {
	PLLBR 	{ R AT91C_CKGR_PLLBR 	RW }
	MCFR 	{ R AT91C_CKGR_MCFR 	RO }
	UCKR 	{ R AT91C_CKGR_UCKR 	RW }
	PLLAR 	{ R AT91C_CKGR_PLLAR 	RW }
	MOR 	{ R AT91C_CKGR_MOR 	RW }
	listeReg 	{ PLLBR MCFR UCKR PLLAR MOR  }

}

# ========== Peripheral attributes for UDPHS peripheral ========== 
array set UDPHS_att {
	INTSTA 	{ R AT91C_UDPHS_INTSTA 	RO }
	FNUM 	{ R AT91C_UDPHS_FNUM 	RO }
	TSTSOFCNT 	{ R AT91C_UDPHS_TSTSOFCNT 	RW }
	CLRINT 	{ R AT91C_UDPHS_CLRINT 	WO }
	IEN 	{ R AT91C_UDPHS_IEN 	RW }
	TSTMODREG 	{ R AT91C_UDPHS_TSTMODREG 	RW }
	TSTCNTA 	{ R AT91C_UDPHS_TSTCNTA 	RW }
	IPFEATURES 	{ R AT91C_UDPHS_IPFEATURES 	RO }
	RIPNAME1 	{ R AT91C_UDPHS_RIPNAME1 	RO }
	TST 	{ R AT91C_UDPHS_TST 	RW }
	TSTCNTB 	{ R AT91C_UDPHS_TSTCNTB 	RW }
	CTRL 	{ R AT91C_UDPHS_CTRL 	RW }
	IPVERSION 	{ R AT91C_UDPHS_IPVERSION 	RO }
	RIPNAME2 	{ R AT91C_UDPHS_RIPNAME2 	RO }
	RIPPADDRSIZE 	{ R AT91C_UDPHS_RIPPADDRSIZE 	RO }
	EPTRST 	{ R AT91C_UDPHS_EPTRST 	WO }
	listeReg 	{ INTSTA FNUM TSTSOFCNT CLRINT IEN TSTMODREG TSTCNTA IPFEATURES RIPNAME1 TST TSTCNTB CTRL IPVERSION RIPNAME2 RIPPADDRSIZE EPTRST  }

}

# ========== Peripheral attributes for UDPHS_EPTFIFO peripheral ========== 
array set UDPHS_EPTFIFO_att {
	READEPT5 	{ R AT91C_UDPHS_EPTFIFO_READEPT5 	RW 16384 }
	READEPT4 	{ R AT91C_UDPHS_EPTFIFO_READEPT4 	RW 16384 }
	READEPT2 	{ R AT91C_UDPHS_EPTFIFO_READEPT2 	RW 16384 }
	READEPTC 	{ R AT91C_UDPHS_EPTFIFO_READEPTC 	RW 16384 }
	READEPT6 	{ R AT91C_UDPHS_EPTFIFO_READEPT6 	RW 16384 }
	READEPT3 	{ R AT91C_UDPHS_EPTFIFO_READEPT3 	RW 16384 }
	READEPTD 	{ R AT91C_UDPHS_EPTFIFO_READEPTD 	RW 16384 }
	READEPTB 	{ R AT91C_UDPHS_EPTFIFO_READEPTB 	RW 16384 }
	READEPT7 	{ R AT91C_UDPHS_EPTFIFO_READEPT7 	RW 16384 }
	READEPT0 	{ R AT91C_UDPHS_EPTFIFO_READEPT0 	RW 16384 }
	READEPTF 	{ R AT91C_UDPHS_EPTFIFO_READEPTF 	RW 16384 }
	READEPTE 	{ R AT91C_UDPHS_EPTFIFO_READEPTE 	RW 16384 }
	READEPTA 	{ R AT91C_UDPHS_EPTFIFO_READEPTA 	RW 16384 }
	READEPT9 	{ R AT91C_UDPHS_EPTFIFO_READEPT9 	RW 16384 }
	READEPT8 	{ R AT91C_UDPHS_EPTFIFO_READEPT8 	RW 16384 }
	READEPT1 	{ R AT91C_UDPHS_EPTFIFO_READEPT1 	RW 16384 }
	listeReg 	{ READEPT5 READEPT4 READEPT2 READEPTC READEPT6 READEPT3 READEPTD READEPTB READEPT7 READEPT0 READEPTF READEPTE READEPTA READEPT9 READEPT8 READEPT1  }

}

# ========== Peripheral attributes for PIO peripheral ========== 
array set PIOA_att {
	IMR 	{ R AT91C_PIOA_IMR 	RO }
	IER 	{ R AT91C_PIOA_IER 	WO }
	OWDR 	{ R AT91C_PIOA_OWDR 	WO }
	ISR 	{ R AT91C_PIOA_ISR 	RO }
	PPUDR 	{ R AT91C_PIOA_PPUDR 	WO }
	MDSR 	{ R AT91C_PIOA_MDSR 	RO }
	MDER 	{ R AT91C_PIOA_MDER 	WO }
	PER 	{ R AT91C_PIOA_PER 	WO }
	PSR 	{ R AT91C_PIOA_PSR 	RO }
	OER 	{ R AT91C_PIOA_OER 	WO }
	BSR 	{ R AT91C_PIOA_BSR 	WO }
	PPUER 	{ R AT91C_PIOA_PPUER 	WO }
	MDDR 	{ R AT91C_PIOA_MDDR 	WO }
	PDR 	{ R AT91C_PIOA_PDR 	WO }
	ODR 	{ R AT91C_PIOA_ODR 	WO }
	IFDR 	{ R AT91C_PIOA_IFDR 	WO }
	ABSR 	{ R AT91C_PIOA_ABSR 	RO }
	ASR 	{ R AT91C_PIOA_ASR 	WO }
	PPUSR 	{ R AT91C_PIOA_PPUSR 	RO }
	ODSR 	{ R AT91C_PIOA_ODSR 	RO }
	SODR 	{ R AT91C_PIOA_SODR 	WO }
	IFSR 	{ R AT91C_PIOA_IFSR 	RO }
	IFER 	{ R AT91C_PIOA_IFER 	WO }
	OSR 	{ R AT91C_PIOA_OSR 	RO }
	IDR 	{ R AT91C_PIOA_IDR 	WO }
	PDSR 	{ R AT91C_PIOA_PDSR 	RO }
	CODR 	{ R AT91C_PIOA_CODR 	WO }
	OWSR 	{ R AT91C_PIOA_OWSR 	RO }
	OWER 	{ R AT91C_PIOA_OWER 	WO }
	listeReg 	{ IMR IER OWDR ISR PPUDR MDSR MDER PER PSR OER BSR PPUER MDDR PDR ODR IFDR ABSR ASR PPUSR ODSR SODR IFSR IFER OSR IDR PDSR CODR OWSR OWER  }

}
array set PIOB_att {
	OWSR 	{ R AT91C_PIOB_OWSR 	RO }
	PPUSR 	{ R AT91C_PIOB_PPUSR 	RO }
	PPUDR 	{ R AT91C_PIOB_PPUDR 	WO }
	MDSR 	{ R AT91C_PIOB_MDSR 	RO }
	MDER 	{ R AT91C_PIOB_MDER 	WO }
	IMR 	{ R AT91C_PIOB_IMR 	RO }
	OSR 	{ R AT91C_PIOB_OSR 	RO }
	OER 	{ R AT91C_PIOB_OER 	WO }
	PSR 	{ R AT91C_PIOB_PSR 	RO }
	PER 	{ R AT91C_PIOB_PER 	WO }
	BSR 	{ R AT91C_PIOB_BSR 	WO }
	PPUER 	{ R AT91C_PIOB_PPUER 	WO }
	IFDR 	{ R AT91C_PIOB_IFDR 	WO }
	ODR 	{ R AT91C_PIOB_ODR 	WO }
	ABSR 	{ R AT91C_PIOB_ABSR 	RO }
	ASR 	{ R AT91C_PIOB_ASR 	WO }
	IFER 	{ R AT91C_PIOB_IFER 	WO }
	IFSR 	{ R AT91C_PIOB_IFSR 	RO }
	SODR 	{ R AT91C_PIOB_SODR 	WO }
	ODSR 	{ R AT91C_PIOB_ODSR 	RO }
	CODR 	{ R AT91C_PIOB_CODR 	WO }
	PDSR 	{ R AT91C_PIOB_PDSR 	RO }
	OWER 	{ R AT91C_PIOB_OWER 	WO }
	IER 	{ R AT91C_PIOB_IER 	WO }
	OWDR 	{ R AT91C_PIOB_OWDR 	WO }
	MDDR 	{ R AT91C_PIOB_MDDR 	WO }
	ISR 	{ R AT91C_PIOB_ISR 	RO }
	IDR 	{ R AT91C_PIOB_IDR 	WO }
	PDR 	{ R AT91C_PIOB_PDR 	WO }
	listeReg 	{ OWSR PPUSR PPUDR MDSR MDER IMR OSR OER PSR PER BSR PPUER IFDR ODR ABSR ASR IFER IFSR SODR ODSR CODR PDSR OWER IER OWDR MDDR ISR IDR PDR  }

}
array set PIOC_att {
	IFDR 	{ R AT91C_PIOC_IFDR 	WO }
	ODR 	{ R AT91C_PIOC_ODR 	WO }
	ABSR 	{ R AT91C_PIOC_ABSR 	RO }
	SODR 	{ R AT91C_PIOC_SODR 	WO }
	IFSR 	{ R AT91C_PIOC_IFSR 	RO }
	CODR 	{ R AT91C_PIOC_CODR 	WO }
	ODSR 	{ R AT91C_PIOC_ODSR 	RO }
	IER 	{ R AT91C_PIOC_IER 	WO }
	IMR 	{ R AT91C_PIOC_IMR 	RO }
	OWDR 	{ R AT91C_PIOC_OWDR 	WO }
	MDDR 	{ R AT91C_PIOC_MDDR 	WO }
	PDSR 	{ R AT91C_PIOC_PDSR 	RO }
	IDR 	{ R AT91C_PIOC_IDR 	WO }
	ISR 	{ R AT91C_PIOC_ISR 	RO }
	PDR 	{ R AT91C_PIOC_PDR 	WO }
	OWSR 	{ R AT91C_PIOC_OWSR 	RO }
	OWER 	{ R AT91C_PIOC_OWER 	WO }
	ASR 	{ R AT91C_PIOC_ASR 	WO }
	PPUSR 	{ R AT91C_PIOC_PPUSR 	RO }
	PPUDR 	{ R AT91C_PIOC_PPUDR 	WO }
	MDSR 	{ R AT91C_PIOC_MDSR 	RO }
	MDER 	{ R AT91C_PIOC_MDER 	WO }
	IFER 	{ R AT91C_PIOC_IFER 	WO }
	OSR 	{ R AT91C_PIOC_OSR 	RO }
	OER 	{ R AT91C_PIOC_OER 	WO }
	PSR 	{ R AT91C_PIOC_PSR 	RO }
	PER 	{ R AT91C_PIOC_PER 	WO }
	BSR 	{ R AT91C_PIOC_BSR 	WO }
	PPUER 	{ R AT91C_PIOC_PPUER 	WO }
	listeReg 	{ IFDR ODR ABSR SODR IFSR CODR ODSR IER IMR OWDR MDDR PDSR IDR ISR PDR OWSR OWER ASR PPUSR PPUDR MDSR MDER IFER OSR OER PSR PER BSR PPUER  }

}
array set PIOD_att {
	PDSR 	{ R AT91C_PIOD_PDSR 	RO }
	CODR 	{ R AT91C_PIOD_CODR 	WO }
	OWER 	{ R AT91C_PIOD_OWER 	WO }
	MDER 	{ R AT91C_PIOD_MDER 	WO }
	IMR 	{ R AT91C_PIOD_IMR 	RO }
	IER 	{ R AT91C_PIOD_IER 	WO }
	ODSR 	{ R AT91C_PIOD_ODSR 	RO }
	SODR 	{ R AT91C_PIOD_SODR 	WO }
	PER 	{ R AT91C_PIOD_PER 	WO }
	OWDR 	{ R AT91C_PIOD_OWDR 	WO }
	PPUER 	{ R AT91C_PIOD_PPUER 	WO }
	MDDR 	{ R AT91C_PIOD_MDDR 	WO }
	ISR 	{ R AT91C_PIOD_ISR 	RO }
	IDR 	{ R AT91C_PIOD_IDR 	WO }
	PDR 	{ R AT91C_PIOD_PDR 	WO }
	ODR 	{ R AT91C_PIOD_ODR 	WO }
	OWSR 	{ R AT91C_PIOD_OWSR 	RO }
	ABSR 	{ R AT91C_PIOD_ABSR 	RO }
	ASR 	{ R AT91C_PIOD_ASR 	WO }
	PPUSR 	{ R AT91C_PIOD_PPUSR 	RO }
	PPUDR 	{ R AT91C_PIOD_PPUDR 	WO }
	MDSR 	{ R AT91C_PIOD_MDSR 	RO }
	PSR 	{ R AT91C_PIOD_PSR 	RO }
	OER 	{ R AT91C_PIOD_OER 	WO }
	OSR 	{ R AT91C_PIOD_OSR 	RO }
	IFER 	{ R AT91C_PIOD_IFER 	WO }
	BSR 	{ R AT91C_PIOD_BSR 	WO }
	IFDR 	{ R AT91C_PIOD_IFDR 	WO }
	IFSR 	{ R AT91C_PIOD_IFSR 	RO }
	listeReg 	{ PDSR CODR OWER MDER IMR IER ODSR SODR PER OWDR PPUER MDDR ISR IDR PDR ODR OWSR ABSR ASR PPUSR PPUDR MDSR PSR OER OSR IFER BSR IFDR IFSR  }

}

# ========== Peripheral attributes for RTTC peripheral ========== 
array set RTTC_att {
	RTSR 	{ R AT91C_RTTC_RTSR 	RO }
	RTAR 	{ R AT91C_RTTC_RTAR 	RW }
	RTVR 	{ R AT91C_RTTC_RTVR 	RO }
	RTMR 	{ R AT91C_RTTC_RTMR 	RW }
	listeReg 	{ RTSR RTAR RTVR RTMR  }

}

# ========== Peripheral attributes for TWI peripheral ========== 
array set TWI0_att {
	SR 	{ R AT91C_TWI0_SR 	RO }
	CWGR 	{ R AT91C_TWI0_CWGR 	RW }
	SMR 	{ R AT91C_TWI0_SMR 	RW }
	CR 	{ R AT91C_TWI0_CR 	WO }
	THR 	{ R AT91C_TWI0_THR 	WO }
	IMR 	{ R AT91C_TWI0_IMR 	RO }
	IER 	{ R AT91C_TWI0_IER 	WO }
	IDR 	{ R AT91C_TWI0_IDR 	WO }
	RHR 	{ R AT91C_TWI0_RHR 	RO }
	MMR 	{ R AT91C_TWI0_MMR 	RW }
	IADR 	{ R AT91C_TWI0_IADR 	RW }
	listeReg 	{ SR CWGR SMR CR THR IMR IER IDR RHR MMR IADR  }

}
array set TWI1_att {
	THR 	{ R AT91C_TWI1_THR 	WO }
	IMR 	{ R AT91C_TWI1_IMR 	RO }
	IER 	{ R AT91C_TWI1_IER 	WO }
	IADR 	{ R AT91C_TWI1_IADR 	RW }
	MMR 	{ R AT91C_TWI1_MMR 	RW }
	RHR 	{ R AT91C_TWI1_RHR 	RO }
	IDR 	{ R AT91C_TWI1_IDR 	WO }
	SR 	{ R AT91C_TWI1_SR 	RO }
	CWGR 	{ R AT91C_TWI1_CWGR 	RW }
	SMR 	{ R AT91C_TWI1_SMR 	RW }
	CR 	{ R AT91C_TWI1_CR 	WO }
	listeReg 	{ THR IMR IER IADR MMR RHR IDR SR CWGR SMR CR  }

}

# ========== Peripheral attributes for SDRAMC peripheral ========== 
array set SDRAMC_att {
	ISR 	{ R AT91C_SDRAMC_ISR 	RO }
	IDR 	{ R AT91C_SDRAMC_IDR 	WO }
	MR 	{ R AT91C_SDRAMC_MR 	RW }
	CR 	{ R AT91C_SDRAMC_CR 	RW }
	LPR 	{ R AT91C_SDRAMC_LPR 	RW }
	MDR 	{ R AT91C_SDRAMC_MDR 	RO }
	TR 	{ R AT91C_SDRAMC_TR 	RW }
	HSR 	{ R AT91C_SDRAMC_HSR 	RW }
	IER 	{ R AT91C_SDRAMC_IER 	WO }
	IMR 	{ R AT91C_SDRAMC_IMR 	RO }
	listeReg 	{ ISR IDR MR CR LPR MDR TR HSR IER IMR  }

}

# ========== Peripheral attributes for USART peripheral ========== 
array set US0_att {
	IF 	{ R AT91C_US0_IF 	RW }
	NER 	{ R AT91C_US0_NER 	RO }
	RTOR 	{ R AT91C_US0_RTOR 	RW }
	THR 	{ R AT91C_US0_THR 	WO }
	CSR 	{ R AT91C_US0_CSR 	RO }
	IDR 	{ R AT91C_US0_IDR 	WO }
	MR 	{ R AT91C_US0_MR 	RW }
	MAN 	{ R AT91C_US0_MAN 	RW }
	FIDI 	{ R AT91C_US0_FIDI 	RW }
	TTGR 	{ R AT91C_US0_TTGR 	RW }
	BRGR 	{ R AT91C_US0_BRGR 	RW }
	RHR 	{ R AT91C_US0_RHR 	RO }
	IMR 	{ R AT91C_US0_IMR 	RO }
	IER 	{ R AT91C_US0_IER 	WO }
	CR 	{ R AT91C_US0_CR 	WO }
	listeReg 	{ IF NER RTOR THR CSR IDR MR MAN FIDI TTGR BRGR RHR IMR IER CR  }

}
array set US1_att {
	MAN 	{ R AT91C_US1_MAN 	RW }
	FIDI 	{ R AT91C_US1_FIDI 	RW }
	TTGR 	{ R AT91C_US1_TTGR 	RW }
	BRGR 	{ R AT91C_US1_BRGR 	RW }
	RHR 	{ R AT91C_US1_RHR 	RO }
	IMR 	{ R AT91C_US1_IMR 	RO }
	IER 	{ R AT91C_US1_IER 	WO }
	CR 	{ R AT91C_US1_CR 	WO }
	IF 	{ R AT91C_US1_IF 	RW }
	NER 	{ R AT91C_US1_NER 	RO }
	RTOR 	{ R AT91C_US1_RTOR 	RW }
	THR 	{ R AT91C_US1_THR 	WO }
	CSR 	{ R AT91C_US1_CSR 	RO }
	IDR 	{ R AT91C_US1_IDR 	WO }
	MR 	{ R AT91C_US1_MR 	RW }
	listeReg 	{ MAN FIDI TTGR BRGR RHR IMR IER CR IF NER RTOR THR CSR IDR MR  }

}
array set US2_att {
	MAN 	{ R AT91C_US2_MAN 	RW }
	FIDI 	{ R AT91C_US2_FIDI 	RW }
	TTGR 	{ R AT91C_US2_TTGR 	RW }
	BRGR 	{ R AT91C_US2_BRGR 	RW }
	RHR 	{ R AT91C_US2_RHR 	RO }
	IMR 	{ R AT91C_US2_IMR 	RO }
	IER 	{ R AT91C_US2_IER 	WO }
	CR 	{ R AT91C_US2_CR 	WO }
	IF 	{ R AT91C_US2_IF 	RW }
	NER 	{ R AT91C_US2_NER 	RO }
	RTOR 	{ R AT91C_US2_RTOR 	RW }
	THR 	{ R AT91C_US2_THR 	WO }
	CSR 	{ R AT91C_US2_CSR 	RO }
	IDR 	{ R AT91C_US2_IDR 	WO }
	MR 	{ R AT91C_US2_MR 	RW }
	listeReg 	{ MAN FIDI TTGR BRGR RHR IMR IER CR IF NER RTOR THR CSR IDR MR  }

}
array set US3_att {
	MAN 	{ R AT91C_US3_MAN 	RW }
	BRGR 	{ R AT91C_US3_BRGR 	RW }
	RHR 	{ R AT91C_US3_RHR 	RO }
	IMR 	{ R AT91C_US3_IMR 	RO }
	IER 	{ R AT91C_US3_IER 	WO }
	CR 	{ R AT91C_US3_CR 	WO }
	RTOR 	{ R AT91C_US3_RTOR 	RW }
	THR 	{ R AT91C_US3_THR 	WO }
	CSR 	{ R AT91C_US3_CSR 	RO }
	FIDI 	{ R AT91C_US3_FIDI 	RW }
	TTGR 	{ R AT91C_US3_TTGR 	RW }
	IF 	{ R AT91C_US3_IF 	RW }
	NER 	{ R AT91C_US3_NER 	RO }
	MR 	{ R AT91C_US3_MR 	RW }
	IDR 	{ R AT91C_US3_IDR 	WO }
	listeReg 	{ MAN BRGR RHR IMR IER CR RTOR THR CSR FIDI TTGR IF NER MR IDR  }

}

# ========== Peripheral attributes for MCI peripheral ========== 
array set MCI_att {
	IMR 	{ R AT91C_MCI_IMR 	RO }
	IER 	{ R AT91C_MCI_IER 	WO }
	TDR 	{ R AT91C_MCI_TDR 	RO }
	IDR 	{ R AT91C_MCI_IDR 	WO }
	SR 	{ R AT91C_MCI_SR 	RO }
	ARGR 	{ R AT91C_MCI_ARGR 	RW }
	DTOR 	{ R AT91C_MCI_DTOR 	RW }
	CR 	{ R AT91C_MCI_CR 	WO }
	VR 	{ R AT91C_MCI_VR 	RO }
	MR 	{ R AT91C_MCI_MR 	RW }
	SDCR 	{ R AT91C_MCI_SDCR 	RW }
	CMDR 	{ R AT91C_MCI_CMDR 	WO }
	RDR 	{ R AT91C_MCI_RDR 	RO }
	BLKR 	{ R AT91C_MCI_BLKR 	RW }
	RSPR 	{ R AT91C_MCI_RSPR 	RO  4 }
	listeReg 	{ IMR IER TDR IDR SR ARGR DTOR CR VR MR SDCR CMDR RDR BLKR RSPR  }

}

# ========== Peripheral attributes for WDTC peripheral ========== 
array set WDTC_att {
	WDMR 	{ R AT91C_WDTC_WDMR 	RW }
	WDSR 	{ R AT91C_WDTC_WDSR 	RO }
	WDCR 	{ R AT91C_WDTC_WDCR 	WO }
	listeReg 	{ WDMR WDSR WDCR  }

}

# ========== Peripheral attributes for SMC peripheral ========== 
array set SMC_att {
	CYCLE1 	{ R AT91C_SMC_CYCLE1 	RW }
	CTRL7 	{ R AT91C_SMC_CTRL7 	RW }
	CTRL2 	{ R AT91C_SMC_CTRL2 	RW }
	PULSE2 	{ R AT91C_SMC_PULSE2 	RW }
	CTRL1 	{ R AT91C_SMC_CTRL1 	RW }
	SETUP4 	{ R AT91C_SMC_SETUP4 	RW }
	CYCLE3 	{ R AT91C_SMC_CYCLE3 	RW }
	SETUP3 	{ R AT91C_SMC_SETUP3 	RW }
	CYCLE2 	{ R AT91C_SMC_CYCLE2 	RW }
	SETUP2 	{ R AT91C_SMC_SETUP2 	RW }
	PULSE5 	{ R AT91C_SMC_PULSE5 	RW }
	CTRL4 	{ R AT91C_SMC_CTRL4 	RW }
	PULSE4 	{ R AT91C_SMC_PULSE4 	RW }
	CTRL3 	{ R AT91C_SMC_CTRL3 	RW }
	PULSE3 	{ R AT91C_SMC_PULSE3 	RW }
	PULSE0 	{ R AT91C_SMC_PULSE0 	RW }
	CYCLE4 	{ R AT91C_SMC_CYCLE4 	RW }
	SETUP5 	{ R AT91C_SMC_SETUP5 	RW }
	CYCLE5 	{ R AT91C_SMC_CYCLE5 	RW }
	SETUP6 	{ R AT91C_SMC_SETUP6 	RW }
	CYCLE6 	{ R AT91C_SMC_CYCLE6 	RW }
	SETUP0 	{ R AT91C_SMC_SETUP0 	RW }
	CYCLE0 	{ R AT91C_SMC_CYCLE0 	RW }
	SETUP1 	{ R AT91C_SMC_SETUP1 	RW }
	CTRL5 	{ R AT91C_SMC_CTRL5 	RW }
	PULSE6 	{ R AT91C_SMC_PULSE6 	RW }
	CTRL6 	{ R AT91C_SMC_CTRL6 	RW }
	PULSE7 	{ R AT91C_SMC_PULSE7 	RW }
	CTRL0 	{ R AT91C_SMC_CTRL0 	RW }
	PULSE1 	{ R AT91C_SMC_PULSE1 	RW }
	SETUP7 	{ R AT91C_SMC_SETUP7 	RW }
	CYCLE7 	{ R AT91C_SMC_CYCLE7 	RW }
	listeReg 	{ CYCLE1 CTRL7 CTRL2 PULSE2 CTRL1 SETUP4 CYCLE3 SETUP3 CYCLE2 SETUP2 PULSE5 CTRL4 PULSE4 CTRL3 PULSE3 PULSE0 CYCLE4 SETUP5 CYCLE5 SETUP6 CYCLE6 SETUP0 CYCLE0 SETUP1 CTRL5 PULSE6 CTRL6 PULSE7 CTRL0 PULSE1 SETUP7 CYCLE7  }

}

# ========== Peripheral attributes for ECC peripheral ========== 
array set HECC_att {
	PR 	{ R AT91C_HECC_PR 	RO }
	MR 	{ R AT91C_HECC_MR 	RW }
	NPR 	{ R AT91C_HECC_NPR 	RO }
	SR 	{ R AT91C_HECC_SR 	RO }
	CR 	{ R AT91C_HECC_CR 	WO }
	VR 	{ R AT91C_HECC_VR 	RO }
	listeReg 	{ PR MR NPR SR CR VR  }

}

# ========== Peripheral attributes for AIC peripheral ========== 
array set AIC_att {
	ICCR 	{ R AT91C_AIC_ICCR 	WO }
	IECR 	{ R AT91C_AIC_IECR 	WO }
	SMR 	{ R AT91C_AIC_SMR 	RW 32 }
	ISCR 	{ R AT91C_AIC_ISCR 	WO }
	EOICR 	{ R AT91C_AIC_EOICR 	WO }
	DCR 	{ R AT91C_AIC_DCR 	RW }
	FFER 	{ R AT91C_AIC_FFER 	WO }
	SVR 	{ R AT91C_AIC_SVR 	RW 32 }
	SPU 	{ R AT91C_AIC_SPU 	RW }
	FFDR 	{ R AT91C_AIC_FFDR 	WO }
	FVR 	{ R AT91C_AIC_FVR 	RO }
	FFSR 	{ R AT91C_AIC_FFSR 	RO }
	IMR 	{ R AT91C_AIC_IMR 	RO }
	ISR 	{ R AT91C_AIC_ISR 	RO }
	IVR 	{ R AT91C_AIC_IVR 	RO }
	IDCR 	{ R AT91C_AIC_IDCR 	WO }
	CISR 	{ R AT91C_AIC_CISR 	RO }
	IPR 	{ R AT91C_AIC_IPR 	RO }
	listeReg 	{ ICCR IECR SMR ISCR EOICR DCR FFER SVR SPU FFDR FVR FFSR IMR ISR IVR IDCR CISR IPR  }

}

# ========== PIO information ========== 

array set def_PIOA_att {
 	PA0 	{  MC_DA0  }
 	PA1 	{  MC_CDA  }
 	PA10 	{  CTS0   RK0  }
 	PA11 	{  TXD1  }
 	PA12 	{  RXD1  }
 	PA13 	{  TXD2   TD1  }
 	PA14 	{  RXD2   RD1  }
 	PA15 	{  TD0  }
 	PA16 	{  RD0  }
 	PA17 	{  AD0  }
 	PA18 	{  AD1   RTS1  }
 	PA19 	{  AD2   CTS1  }
 	PA2 	{  MC_CK  }
 	PA20 	{  AD3   SCK3  }
 	PA21 	{  DRXD  }
 	PA22 	{  DTXD   RF0  }
 	PA23 	{  TWD0  }
 	PA24 	{  TWCK0  }
 	PA25 	{  MISO  }
 	PA26 	{  MOSI  }
 	PA27 	{  SPCK  }
 	PA28 	{  NPCS0  }
 	PA29 	{  RTS2   TF1  }
 	PA3 	{  MC_DA1   TCLK0  }
 	PA30 	{  CTS2   TK1  }
 	PA31 	{  NWAIT   IRQ  }
 	PA4 	{  MC_DA2   TIOA0  }
 	PA5 	{  MC_DA3   TIOB0  }
 	PA6 	{  TXD0  }
 	PA7 	{  RXD0  }
 	PA8 	{  SCK0   RF1  }
 	PA9 	{  RTS0   RK1  }
 }

array set def_PIOB_att {
 	PB0 	{  TXD3  }
 	PB1 	{  RXD3  }
 	PB10 	{  A25_CFRNW   FIQ  }
 	PB11 	{  A18  }
 	PB12 	{  A19  }
 	PB13 	{  A20  }
 	PB14 	{  A23   PCK0  }
 	PB15 	{  A24   ADTRG  }
 	PB16 	{  D16  }
 	PB17 	{  D17  }
 	PB18 	{  D18  }
 	PB19 	{  D19  }
 	PB2 	{  A21_NANDALE  }
 	PB20 	{  D20  }
 	PB21 	{  D21  }
 	PB22 	{  D22  }
 	PB23 	{  D23  }
 	PB24 	{  D24  }
 	PB25 	{  D25  }
 	PB26 	{  D26  }
 	PB27 	{  D27  }
 	PB28 	{  D28  }
 	PB29 	{  D29  }
 	PB3 	{  A22_NANDCLE  }
 	PB30 	{  D30  }
 	PB31 	{  D31  }
 	PB4 	{  NANDOE  }
 	PB5 	{  NANDWE  }
 	PB6 	{  NCS3_NANDCS  }
 	PB7 	{  NCS4_CFCS0   NPCS1  }
 	PB8 	{  CFE1   PWM0  }
 	PB9 	{  CFE2   PWM1  }
 }

array set def_PIOC_att {
 	PC0 	{  TF0  }
 	PC1 	{  TK0   LCDPWR  }
 	PC10 	{  LCDD2   LCDD4  }
 	PC11 	{  LCDD3   LCDD5  }
 	PC12 	{  LCDD4   LCDD6  }
 	PC13 	{  LCDD5   LCDD7  }
 	PC14 	{  LCDD6   LCDD10  }
 	PC15 	{  LCDD7   LCDD11  }
 	PC16 	{  LCDD8   LCDD12  }
 	PC17 	{  LCDD9   LCDD13  }
 	PC18 	{  LCDD10   LCDD14  }
 	PC19 	{  LCDD11   LCDD15  }
 	PC2 	{  LCDMOD   PWM0  }
 	PC20 	{  LCDD12   LCDD18  }
 	PC21 	{  LCDD13   LCDD19  }
 	PC22 	{  LCDD14   LCDD20  }
 	PC23 	{  LCDD15   LCDD21  }
 	PC24 	{  LCDD16   LCDD22  }
 	PC25 	{  LCDD17   LCDD23  }
 	PC26 	{  LCDD18  }
 	PC27 	{  LCDD19  }
 	PC28 	{  LCDD20  }
 	PC29 	{  LCDD21   TIOA1  }
 	PC3 	{  LCDCC   PWM1  }
 	PC30 	{  LCDD22   TIOB1  }
 	PC31 	{  LCDD23   TCLK1  }
 	PC4 	{  LCDVSYNC  }
 	PC5 	{  LCDHSYNC  }
 	PC6 	{  LCDDOTCK  }
 	PC7 	{  LCDDEN  }
 	PC8 	{  LCDD0   LCDD2  }
 	PC9 	{  LCDD1   LCDD3  }
 }

array set def_PIOD_att {
 	PD0 	{  NCS2  }
 	PD1 	{  AC97_FS  }
 	PD10 	{  TWD1   TIOA2  }
 	PD11 	{  TWCK1   TIOB2  }
 	PD12 	{  PWM2   PCK1  }
 	PD13 	{  NCS5_CFCS1   NPCS3  }
 	PD14 	{  DSR0   PWM0  }
 	PD15 	{  DTR0   PWM1  }
 	PD16 	{  DCD0   PWM2  }
 	PD17 	{  RI0  }
 	PD18 	{  PWM3  }
 	PD19 	{  PCK0  }
 	PD2 	{  AC97_CK   SCK1  }
 	PD20 	{  PCK1  }
 	PD21 	{  TCLK2  }
 	PD3 	{  AC97_TX   CTS3  }
 	PD4 	{  AC97_RX   RTS3  }
 	PD5 	{  DTXD   PWM2  }
 	PD6 	{  AD4  }
 	PD7 	{  AD5  }
 	PD8 	{  NPCS2   PWM3  }
 	PD9 	{  SCK2   NPCS3  }
 }
