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
# File Name           : AT91SAM9263.tcl
# Object              : AT91SAM9263 definitions
# Generated           : AT91 SW Application Group  09/12/2006 (17:51:15)
# 
# CVS Reference       : /AT91SAM9263.pl/0/dummy timestamp//
# CVS Reference       : /SYS_SAM9262.pl/1.4/Tue Jan 18 17:06:33 2005//
# CVS Reference       : /HMATRIX1_SAM9262.pl/1.10/Thu Oct 13 12:44:26 2005//
# CVS Reference       : /CCR_SAM9262.pl/1.4/Thu Dec 22 10:52:56 2005//
# CVS Reference       : /PMC_SAM9262.pl/1.4/Mon Mar 07 18:03:13 2005//
# CVS Reference       : /HSDRAMC1_6100A.pl/1.2/Mon Aug 09 10:52:25 2004//
# CVS Reference       : /HSMC3_6105A.pl/1.4/Tue Nov 16 09:16:23 2004//
# CVS Reference       : /AIC_6075B.pl/1.3/Fri May 20 14:21:42 2005//
# CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb 03 09:02:11 2005//
# CVS Reference       : /DBGU_6059D.pl/1.1/Mon Jan 31 13:54:41 2005//
# CVS Reference       : /PIO_6057A.pl/1.2/Thu Feb 03 10:29:42 2005//
# CVS Reference       : /RSTC_6098A.pl/1.3/Thu Nov 04 13:57:00 2004//
# CVS Reference       : /SHDWC_6122A.pl/1.3/Wed Oct 06 14:16:58 2004//
# CVS Reference       : /RTTC_6081A.pl/1.2/Thu Nov 04 13:57:22 2004//
# CVS Reference       : /PITC_6079A.pl/1.2/Thu Nov 04 13:56:22 2004//
# CVS Reference       : /WDTC_6080A.pl/1.3/Thu Nov 04 13:58:52 2004//
# CVS Reference       : /TC_6082A.pl/1.7/Wed Mar 09 16:31:51 2005//
# CVS Reference       : /MCI_6101E.pl/1.1/Fri Jun 03 13:20:23 2005//
# CVS Reference       : /TWI_6061A.pl/1.1/Tue Jul 13 06:38:23 2004//
# CVS Reference       : /US_6089C.pl/1.1/Mon Jan 31 13:56:02 2005//
# CVS Reference       : /SSC_6078B.pl/1.1/Wed Jul 13 15:25:46 2005//
# CVS Reference       : /SPI_6088D.pl/1.3/Fri May 20 14:23:02 2005//
# CVS Reference       : /AC97C_XXXX.pl/1.3/Tue Feb 22 17:08:27 2005//
# CVS Reference       : /CAN_6019B.pl/1.1/Mon Jan 31 13:54:30 2005//
# CVS Reference       : /PWM_6044D.pl/1.2/Tue May 10 12:39:09 2005//
# CVS Reference       : /LCDC_6063A.pl/1.3/Fri Dec 09 10:59:26 2005//
# CVS Reference       : /EMACB_6119A.pl/1.6/Wed Jul 13 15:25:00 2005//
# CVS Reference       : /DMA_XXXX.pl/1.6/Tue Jan 11 09:40:44 2005//
# CVS Reference       : /UDP_6ept.pl/1.1/Wed Aug 30 14:20:52 2006//
# CVS Reference       : /UHP_6127A.pl/1.1/Wed Feb 23 16:03:17 2005//
# CVS Reference       : /TBOX_XXXX.pl/1.15/Thu Jun 09 07:05:57 2005//
# CVS Reference       : /EBI_nadia2.pl/1.1/Wed Dec 29 11:28:03 2004//
# CVS Reference       : /HECC_6143A.pl/1.1/Wed Feb 09 17:16:57 2005//
# CVS Reference       : /ISI_xxxxx.pl/1.3/Thu Mar 03 11:11:48 2005//
# ----------------------------------------------------------------------------


# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR System Peripherals
# *****************************************************************************
# -------- GPBR : (SYS Offset: 0x1d60) GPBR General Purpose Register -------- 
set AT91C_GPBR_GPRV       [expr 0x0 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR External Bus Interface 0
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
#              SOFTWARE API DEFINITION  FOR External Bus Interface 1
# *****************************************************************************

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
# -------- CCFG_EBI0CSA : (CCFG Offset: 0x10) EBI0 Chip Select Assignement Register -------- 
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
# -------- CCFG_EBI1CSA : (CCFG Offset: 0x14) EBI1 Chip Select Assignement Register -------- 
set AT91C_EBI_CS1A        [expr 0x1 <<  1 ]
set 	AT91C_EBI_CS1A_SMC                  [expr 0x0 <<  1 ]
set 	AT91C_EBI_CS1A_SDRAMC               [expr 0x1 <<  1 ]
set AT91C_EBI_CS2A        [expr 0x1 <<  3 ]
set 	AT91C_EBI_CS2A_SMC                  [expr 0x0 <<  3 ]
set 	AT91C_EBI_CS2A_SM                   [expr 0x1 <<  3 ]
set AT91C_EBI_DBPUC       [expr 0x1 <<  8 ]

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
#              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
# *****************************************************************************
# -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- 
set AT91C_AIC_PRIOR       [expr 0x7 <<  0 ]
set 	AT91C_AIC_PRIOR_LOWEST               0x0
set 	AT91C_AIC_PRIOR_HIGHEST              0x7
set AT91C_AIC_SRCTYPE     [expr 0x3 <<  5 ]
set 	AT91C_AIC_SRCTYPE_EXT_LOW_LEVEL        [expr 0x0 <<  5 ]
set 	AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL       [expr 0x0 <<  5 ]
set 	AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE    [expr 0x1 <<  5 ]
set 	AT91C_AIC_SRCTYPE_EXT_NEGATIVE_EDGE    [expr 0x1 <<  5 ]
set 	AT91C_AIC_SRCTYPE_HIGH_LEVEL           [expr 0x2 <<  5 ]
set 	AT91C_AIC_SRCTYPE_POSITIVE_EDGE        [expr 0x3 <<  5 ]
# -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- 
set AT91C_AIC_NFIQ        [expr 0x1 <<  0 ]
set AT91C_AIC_NIRQ        [expr 0x1 <<  1 ]
# -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- 
set AT91C_AIC_DCR_PROT    [expr 0x1 <<  0 ]
set AT91C_AIC_DCR_GMSK    [expr 0x1 <<  1 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Parallel Input Output Controler
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Clock Generator Controler
# *****************************************************************************
# -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- 
set AT91C_CKGR_MOSCEN     [expr 0x1 <<  0 ]
set AT91C_CKGR_OSCBYPASS  [expr 0x1 <<  1 ]
set AT91C_CKGR_OSCOUNT    [expr 0xFF <<  8 ]
# -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLAR : (CKGR Offset: 0x8) PLL A Register -------- 
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
# -------- CKGR_PLLBR : (CKGR Offset: 0xc) PLL B Register -------- 
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
set 	AT91C_PMC_MDIV_3                    [expr 0x2 <<  8 ]
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
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]
# -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]
# -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]
# -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]

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
set AT91C_TWI_SWRST       [expr 0x1 <<  7 ]
# -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- 
set AT91C_TWI_IADRSZ      [expr 0x3 <<  8 ]
set 	AT91C_TWI_IADRSZ_NO                   [expr 0x0 <<  8 ]
set 	AT91C_TWI_IADRSZ_1_BYTE               [expr 0x1 <<  8 ]
set 	AT91C_TWI_IADRSZ_2_BYTE               [expr 0x2 <<  8 ]
set 	AT91C_TWI_IADRSZ_3_BYTE               [expr 0x3 <<  8 ]
set AT91C_TWI_MREAD       [expr 0x1 << 12 ]
set AT91C_TWI_DADR        [expr 0x7F << 16 ]
# -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- 
set AT91C_TWI_CLDIV       [expr 0xFF <<  0 ]
set AT91C_TWI_CHDIV       [expr 0xFF <<  8 ]
set AT91C_TWI_CKDIV       [expr 0x7 << 16 ]
# -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- 
set AT91C_TWI_TXCOMP      [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_UNRE        [expr 0x1 <<  7 ]
set AT91C_TWI_NACK        [expr 0x1 <<  8 ]
# -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- 
set AT91C_TWI_TXCOMP      [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_UNRE        [expr 0x1 <<  7 ]
set AT91C_TWI_NACK        [expr 0x1 <<  8 ]
# -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- 
set AT91C_TWI_TXCOMP      [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_UNRE        [expr 0x1 <<  7 ]
set AT91C_TWI_NACK        [expr 0x1 <<  8 ]
# -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- 
set AT91C_TWI_TXCOMP      [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_UNRE        [expr 0x1 <<  7 ]
set AT91C_TWI_NACK        [expr 0x1 <<  8 ]

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
set AT91C_US_MAX_ITER     [expr 0x1 << 24 ]
set AT91C_US_FILTER       [expr 0x1 << 28 ]
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
#              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface
# *****************************************************************************
# -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- 
set AT91C_CAN_MTIMEMARK   [expr 0xFFFF <<  0 ]
set AT91C_CAN_PRIOR       [expr 0xF << 16 ]
set AT91C_CAN_MOT         [expr 0x7 << 24 ]
set 	AT91C_CAN_MOT_DIS                  [expr 0x0 << 24 ]
set 	AT91C_CAN_MOT_RX                   [expr 0x1 << 24 ]
set 	AT91C_CAN_MOT_RXOVERWRITE          [expr 0x2 << 24 ]
set 	AT91C_CAN_MOT_TX                   [expr 0x3 << 24 ]
set 	AT91C_CAN_MOT_CONSUMER             [expr 0x4 << 24 ]
set 	AT91C_CAN_MOT_PRODUCER             [expr 0x5 << 24 ]
# -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- 
set AT91C_CAN_MIDvB       [expr 0x3FFFF <<  0 ]
set AT91C_CAN_MIDvA       [expr 0x7FF << 18 ]
set AT91C_CAN_MIDE        [expr 0x1 << 29 ]
# -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- 
set AT91C_CAN_MIDvB       [expr 0x3FFFF <<  0 ]
set AT91C_CAN_MIDvA       [expr 0x7FF << 18 ]
set AT91C_CAN_MIDE        [expr 0x1 << 29 ]
# -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- 
# -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- 
set AT91C_CAN_MTIMESTAMP  [expr 0xFFFF <<  0 ]
set AT91C_CAN_MDLC        [expr 0xF << 16 ]
set AT91C_CAN_MRTR        [expr 0x1 << 20 ]
set AT91C_CAN_MABT        [expr 0x1 << 22 ]
set AT91C_CAN_MRDY        [expr 0x1 << 23 ]
set AT91C_CAN_MMI         [expr 0x1 << 24 ]
# -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- 
# -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- 
# -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- 
set AT91C_CAN_MDLC        [expr 0xF << 16 ]
set AT91C_CAN_MRTR        [expr 0x1 << 20 ]
set AT91C_CAN_MACR        [expr 0x1 << 22 ]
set AT91C_CAN_MTCR        [expr 0x1 << 23 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Control Area Network Interface
# *****************************************************************************
# -------- CAN_MR : (CAN Offset: 0x0) CAN Mode Register -------- 
set AT91C_CAN_CANEN       [expr 0x1 <<  0 ]
set AT91C_CAN_LPM         [expr 0x1 <<  1 ]
set AT91C_CAN_ABM         [expr 0x1 <<  2 ]
set AT91C_CAN_OVL         [expr 0x1 <<  3 ]
set AT91C_CAN_TEOF        [expr 0x1 <<  4 ]
set AT91C_CAN_TTM         [expr 0x1 <<  5 ]
set AT91C_CAN_TIMFRZ      [expr 0x1 <<  6 ]
set AT91C_CAN_DRPT        [expr 0x1 <<  7 ]
# -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- 
set AT91C_CAN_MB0         [expr 0x1 <<  0 ]
set AT91C_CAN_MB1         [expr 0x1 <<  1 ]
set AT91C_CAN_MB2         [expr 0x1 <<  2 ]
set AT91C_CAN_MB3         [expr 0x1 <<  3 ]
set AT91C_CAN_MB4         [expr 0x1 <<  4 ]
set AT91C_CAN_MB5         [expr 0x1 <<  5 ]
set AT91C_CAN_MB6         [expr 0x1 <<  6 ]
set AT91C_CAN_MB7         [expr 0x1 <<  7 ]
set AT91C_CAN_MB8         [expr 0x1 <<  8 ]
set AT91C_CAN_MB9         [expr 0x1 <<  9 ]
set AT91C_CAN_MB10        [expr 0x1 << 10 ]
set AT91C_CAN_MB11        [expr 0x1 << 11 ]
set AT91C_CAN_MB12        [expr 0x1 << 12 ]
set AT91C_CAN_MB13        [expr 0x1 << 13 ]
set AT91C_CAN_MB14        [expr 0x1 << 14 ]
set AT91C_CAN_MB15        [expr 0x1 << 15 ]
set AT91C_CAN_ERRA        [expr 0x1 << 16 ]
set AT91C_CAN_WARN        [expr 0x1 << 17 ]
set AT91C_CAN_ERRP        [expr 0x1 << 18 ]
set AT91C_CAN_BOFF        [expr 0x1 << 19 ]
set AT91C_CAN_SLEEP       [expr 0x1 << 20 ]
set AT91C_CAN_WAKEUP      [expr 0x1 << 21 ]
set AT91C_CAN_TOVF        [expr 0x1 << 22 ]
set AT91C_CAN_TSTP        [expr 0x1 << 23 ]
set AT91C_CAN_CERR        [expr 0x1 << 24 ]
set AT91C_CAN_SERR        [expr 0x1 << 25 ]
set AT91C_CAN_AERR        [expr 0x1 << 26 ]
set AT91C_CAN_FERR        [expr 0x1 << 27 ]
set AT91C_CAN_BERR        [expr 0x1 << 28 ]
# -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- 
set AT91C_CAN_MB0         [expr 0x1 <<  0 ]
set AT91C_CAN_MB1         [expr 0x1 <<  1 ]
set AT91C_CAN_MB2         [expr 0x1 <<  2 ]
set AT91C_CAN_MB3         [expr 0x1 <<  3 ]
set AT91C_CAN_MB4         [expr 0x1 <<  4 ]
set AT91C_CAN_MB5         [expr 0x1 <<  5 ]
set AT91C_CAN_MB6         [expr 0x1 <<  6 ]
set AT91C_CAN_MB7         [expr 0x1 <<  7 ]
set AT91C_CAN_MB8         [expr 0x1 <<  8 ]
set AT91C_CAN_MB9         [expr 0x1 <<  9 ]
set AT91C_CAN_MB10        [expr 0x1 << 10 ]
set AT91C_CAN_MB11        [expr 0x1 << 11 ]
set AT91C_CAN_MB12        [expr 0x1 << 12 ]
set AT91C_CAN_MB13        [expr 0x1 << 13 ]
set AT91C_CAN_MB14        [expr 0x1 << 14 ]
set AT91C_CAN_MB15        [expr 0x1 << 15 ]
set AT91C_CAN_ERRA        [expr 0x1 << 16 ]
set AT91C_CAN_WARN        [expr 0x1 << 17 ]
set AT91C_CAN_ERRP        [expr 0x1 << 18 ]
set AT91C_CAN_BOFF        [expr 0x1 << 19 ]
set AT91C_CAN_SLEEP       [expr 0x1 << 20 ]
set AT91C_CAN_WAKEUP      [expr 0x1 << 21 ]
set AT91C_CAN_TOVF        [expr 0x1 << 22 ]
set AT91C_CAN_TSTP        [expr 0x1 << 23 ]
set AT91C_CAN_CERR        [expr 0x1 << 24 ]
set AT91C_CAN_SERR        [expr 0x1 << 25 ]
set AT91C_CAN_AERR        [expr 0x1 << 26 ]
set AT91C_CAN_FERR        [expr 0x1 << 27 ]
set AT91C_CAN_BERR        [expr 0x1 << 28 ]
# -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- 
set AT91C_CAN_MB0         [expr 0x1 <<  0 ]
set AT91C_CAN_MB1         [expr 0x1 <<  1 ]
set AT91C_CAN_MB2         [expr 0x1 <<  2 ]
set AT91C_CAN_MB3         [expr 0x1 <<  3 ]
set AT91C_CAN_MB4         [expr 0x1 <<  4 ]
set AT91C_CAN_MB5         [expr 0x1 <<  5 ]
set AT91C_CAN_MB6         [expr 0x1 <<  6 ]
set AT91C_CAN_MB7         [expr 0x1 <<  7 ]
set AT91C_CAN_MB8         [expr 0x1 <<  8 ]
set AT91C_CAN_MB9         [expr 0x1 <<  9 ]
set AT91C_CAN_MB10        [expr 0x1 << 10 ]
set AT91C_CAN_MB11        [expr 0x1 << 11 ]
set AT91C_CAN_MB12        [expr 0x1 << 12 ]
set AT91C_CAN_MB13        [expr 0x1 << 13 ]
set AT91C_CAN_MB14        [expr 0x1 << 14 ]
set AT91C_CAN_MB15        [expr 0x1 << 15 ]
set AT91C_CAN_ERRA        [expr 0x1 << 16 ]
set AT91C_CAN_WARN        [expr 0x1 << 17 ]
set AT91C_CAN_ERRP        [expr 0x1 << 18 ]
set AT91C_CAN_BOFF        [expr 0x1 << 19 ]
set AT91C_CAN_SLEEP       [expr 0x1 << 20 ]
set AT91C_CAN_WAKEUP      [expr 0x1 << 21 ]
set AT91C_CAN_TOVF        [expr 0x1 << 22 ]
set AT91C_CAN_TSTP        [expr 0x1 << 23 ]
set AT91C_CAN_CERR        [expr 0x1 << 24 ]
set AT91C_CAN_SERR        [expr 0x1 << 25 ]
set AT91C_CAN_AERR        [expr 0x1 << 26 ]
set AT91C_CAN_FERR        [expr 0x1 << 27 ]
set AT91C_CAN_BERR        [expr 0x1 << 28 ]
# -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- 
set AT91C_CAN_MB0         [expr 0x1 <<  0 ]
set AT91C_CAN_MB1         [expr 0x1 <<  1 ]
set AT91C_CAN_MB2         [expr 0x1 <<  2 ]
set AT91C_CAN_MB3         [expr 0x1 <<  3 ]
set AT91C_CAN_MB4         [expr 0x1 <<  4 ]
set AT91C_CAN_MB5         [expr 0x1 <<  5 ]
set AT91C_CAN_MB6         [expr 0x1 <<  6 ]
set AT91C_CAN_MB7         [expr 0x1 <<  7 ]
set AT91C_CAN_MB8         [expr 0x1 <<  8 ]
set AT91C_CAN_MB9         [expr 0x1 <<  9 ]
set AT91C_CAN_MB10        [expr 0x1 << 10 ]
set AT91C_CAN_MB11        [expr 0x1 << 11 ]
set AT91C_CAN_MB12        [expr 0x1 << 12 ]
set AT91C_CAN_MB13        [expr 0x1 << 13 ]
set AT91C_CAN_MB14        [expr 0x1 << 14 ]
set AT91C_CAN_MB15        [expr 0x1 << 15 ]
set AT91C_CAN_ERRA        [expr 0x1 << 16 ]
set AT91C_CAN_WARN        [expr 0x1 << 17 ]
set AT91C_CAN_ERRP        [expr 0x1 << 18 ]
set AT91C_CAN_BOFF        [expr 0x1 << 19 ]
set AT91C_CAN_SLEEP       [expr 0x1 << 20 ]
set AT91C_CAN_WAKEUP      [expr 0x1 << 21 ]
set AT91C_CAN_TOVF        [expr 0x1 << 22 ]
set AT91C_CAN_TSTP        [expr 0x1 << 23 ]
set AT91C_CAN_CERR        [expr 0x1 << 24 ]
set AT91C_CAN_SERR        [expr 0x1 << 25 ]
set AT91C_CAN_AERR        [expr 0x1 << 26 ]
set AT91C_CAN_FERR        [expr 0x1 << 27 ]
set AT91C_CAN_BERR        [expr 0x1 << 28 ]
set AT91C_CAN_RBSY        [expr 0x1 << 29 ]
set AT91C_CAN_TBSY        [expr 0x1 << 30 ]
set AT91C_CAN_OVLY        [expr 0x1 << 31 ]
# -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- 
set AT91C_CAN_PHASE2      [expr 0x7 <<  0 ]
set AT91C_CAN_PHASE1      [expr 0x7 <<  4 ]
set AT91C_CAN_PROPAG      [expr 0x7 <<  8 ]
set AT91C_CAN_SYNC        [expr 0x3 << 12 ]
set AT91C_CAN_BRP         [expr 0x7F << 16 ]
set AT91C_CAN_SMP         [expr 0x1 << 24 ]
# -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- 
set AT91C_CAN_TIMER       [expr 0xFFFF <<  0 ]
# -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- 
set AT91C_CAN_MTIMESTAMP  [expr 0xFFFF <<  0 ]
# -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- 
set AT91C_CAN_REC         [expr 0xFF <<  0 ]
set AT91C_CAN_TEC         [expr 0xFF << 16 ]
# -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- 
set AT91C_CAN_MB0         [expr 0x1 <<  0 ]
set AT91C_CAN_MB1         [expr 0x1 <<  1 ]
set AT91C_CAN_MB2         [expr 0x1 <<  2 ]
set AT91C_CAN_MB3         [expr 0x1 <<  3 ]
set AT91C_CAN_MB4         [expr 0x1 <<  4 ]
set AT91C_CAN_MB5         [expr 0x1 <<  5 ]
set AT91C_CAN_MB6         [expr 0x1 <<  6 ]
set AT91C_CAN_MB7         [expr 0x1 <<  7 ]
set AT91C_CAN_MB8         [expr 0x1 <<  8 ]
set AT91C_CAN_MB9         [expr 0x1 <<  9 ]
set AT91C_CAN_MB10        [expr 0x1 << 10 ]
set AT91C_CAN_MB11        [expr 0x1 << 11 ]
set AT91C_CAN_MB12        [expr 0x1 << 12 ]
set AT91C_CAN_MB13        [expr 0x1 << 13 ]
set AT91C_CAN_MB14        [expr 0x1 << 14 ]
set AT91C_CAN_MB15        [expr 0x1 << 15 ]
set AT91C_CAN_TIMRST      [expr 0x1 << 31 ]
# -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- 
set AT91C_CAN_MB0         [expr 0x1 <<  0 ]
set AT91C_CAN_MB1         [expr 0x1 <<  1 ]
set AT91C_CAN_MB2         [expr 0x1 <<  2 ]
set AT91C_CAN_MB3         [expr 0x1 <<  3 ]
set AT91C_CAN_MB4         [expr 0x1 <<  4 ]
set AT91C_CAN_MB5         [expr 0x1 <<  5 ]
set AT91C_CAN_MB6         [expr 0x1 <<  6 ]
set AT91C_CAN_MB7         [expr 0x1 <<  7 ]
set AT91C_CAN_MB8         [expr 0x1 <<  8 ]
set AT91C_CAN_MB9         [expr 0x1 <<  9 ]
set AT91C_CAN_MB10        [expr 0x1 << 10 ]
set AT91C_CAN_MB11        [expr 0x1 << 11 ]
set AT91C_CAN_MB12        [expr 0x1 << 12 ]
set AT91C_CAN_MB13        [expr 0x1 << 13 ]
set AT91C_CAN_MB14        [expr 0x1 << 14 ]
set AT91C_CAN_MB15        [expr 0x1 << 15 ]

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
#              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100
# *****************************************************************************
# -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- 
set AT91C_EMAC_LB         [expr 0x1 <<  0 ]
set AT91C_EMAC_LLB        [expr 0x1 <<  1 ]
set AT91C_EMAC_RE         [expr 0x1 <<  2 ]
set AT91C_EMAC_TE         [expr 0x1 <<  3 ]
set AT91C_EMAC_MPE        [expr 0x1 <<  4 ]
set AT91C_EMAC_CLRSTAT    [expr 0x1 <<  5 ]
set AT91C_EMAC_INCSTAT    [expr 0x1 <<  6 ]
set AT91C_EMAC_WESTAT     [expr 0x1 <<  7 ]
set AT91C_EMAC_BP         [expr 0x1 <<  8 ]
set AT91C_EMAC_TSTART     [expr 0x1 <<  9 ]
set AT91C_EMAC_THALT      [expr 0x1 << 10 ]
set AT91C_EMAC_TPFR       [expr 0x1 << 11 ]
set AT91C_EMAC_TZQ        [expr 0x1 << 12 ]
# -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- 
set AT91C_EMAC_SPD        [expr 0x1 <<  0 ]
set AT91C_EMAC_FD         [expr 0x1 <<  1 ]
set AT91C_EMAC_JFRAME     [expr 0x1 <<  3 ]
set AT91C_EMAC_CAF        [expr 0x1 <<  4 ]
set AT91C_EMAC_NBC        [expr 0x1 <<  5 ]
set AT91C_EMAC_MTI        [expr 0x1 <<  6 ]
set AT91C_EMAC_UNI        [expr 0x1 <<  7 ]
set AT91C_EMAC_BIG        [expr 0x1 <<  8 ]
set AT91C_EMAC_EAE        [expr 0x1 <<  9 ]
set AT91C_EMAC_CLK        [expr 0x3 << 10 ]
set 	AT91C_EMAC_CLK_HCLK_8               [expr 0x0 << 10 ]
set 	AT91C_EMAC_CLK_HCLK_16              [expr 0x1 << 10 ]
set 	AT91C_EMAC_CLK_HCLK_32              [expr 0x2 << 10 ]
set 	AT91C_EMAC_CLK_HCLK_64              [expr 0x3 << 10 ]
set AT91C_EMAC_RTY        [expr 0x1 << 12 ]
set AT91C_EMAC_PAE        [expr 0x1 << 13 ]
set AT91C_EMAC_RBOF       [expr 0x3 << 14 ]
set 	AT91C_EMAC_RBOF_OFFSET_0             [expr 0x0 << 14 ]
set 	AT91C_EMAC_RBOF_OFFSET_1             [expr 0x1 << 14 ]
set 	AT91C_EMAC_RBOF_OFFSET_2             [expr 0x2 << 14 ]
set 	AT91C_EMAC_RBOF_OFFSET_3             [expr 0x3 << 14 ]
set AT91C_EMAC_RLCE       [expr 0x1 << 16 ]
set AT91C_EMAC_DRFCS      [expr 0x1 << 17 ]
set AT91C_EMAC_EFRHD      [expr 0x1 << 18 ]
set AT91C_EMAC_IRXFCS     [expr 0x1 << 19 ]
# -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- 
set AT91C_EMAC_LINKR      [expr 0x1 <<  0 ]
set AT91C_EMAC_MDIO       [expr 0x1 <<  1 ]
set AT91C_EMAC_IDLE       [expr 0x1 <<  2 ]
# -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- 
set AT91C_EMAC_UBR        [expr 0x1 <<  0 ]
set AT91C_EMAC_COL        [expr 0x1 <<  1 ]
set AT91C_EMAC_RLES       [expr 0x1 <<  2 ]
set AT91C_EMAC_TGO        [expr 0x1 <<  3 ]
set AT91C_EMAC_BEX        [expr 0x1 <<  4 ]
set AT91C_EMAC_COMP       [expr 0x1 <<  5 ]
set AT91C_EMAC_UND        [expr 0x1 <<  6 ]
# -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- 
set AT91C_EMAC_BNA        [expr 0x1 <<  0 ]
set AT91C_EMAC_REC        [expr 0x1 <<  1 ]
set AT91C_EMAC_OVR        [expr 0x1 <<  2 ]
# -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- 
set AT91C_EMAC_MFD        [expr 0x1 <<  0 ]
set AT91C_EMAC_RCOMP      [expr 0x1 <<  1 ]
set AT91C_EMAC_RXUBR      [expr 0x1 <<  2 ]
set AT91C_EMAC_TXUBR      [expr 0x1 <<  3 ]
set AT91C_EMAC_TUNDR      [expr 0x1 <<  4 ]
set AT91C_EMAC_RLEX       [expr 0x1 <<  5 ]
set AT91C_EMAC_TXERR      [expr 0x1 <<  6 ]
set AT91C_EMAC_TCOMP      [expr 0x1 <<  7 ]
set AT91C_EMAC_LINK       [expr 0x1 <<  9 ]
set AT91C_EMAC_ROVR       [expr 0x1 << 10 ]
set AT91C_EMAC_HRESP      [expr 0x1 << 11 ]
set AT91C_EMAC_PFRE       [expr 0x1 << 12 ]
set AT91C_EMAC_PTZ        [expr 0x1 << 13 ]
# -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- 
set AT91C_EMAC_MFD        [expr 0x1 <<  0 ]
set AT91C_EMAC_RCOMP      [expr 0x1 <<  1 ]
set AT91C_EMAC_RXUBR      [expr 0x1 <<  2 ]
set AT91C_EMAC_TXUBR      [expr 0x1 <<  3 ]
set AT91C_EMAC_TUNDR      [expr 0x1 <<  4 ]
set AT91C_EMAC_RLEX       [expr 0x1 <<  5 ]
set AT91C_EMAC_TXERR      [expr 0x1 <<  6 ]
set AT91C_EMAC_TCOMP      [expr 0x1 <<  7 ]
set AT91C_EMAC_LINK       [expr 0x1 <<  9 ]
set AT91C_EMAC_ROVR       [expr 0x1 << 10 ]
set AT91C_EMAC_HRESP      [expr 0x1 << 11 ]
set AT91C_EMAC_PFRE       [expr 0x1 << 12 ]
set AT91C_EMAC_PTZ        [expr 0x1 << 13 ]
# -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- 
set AT91C_EMAC_MFD        [expr 0x1 <<  0 ]
set AT91C_EMAC_RCOMP      [expr 0x1 <<  1 ]
set AT91C_EMAC_RXUBR      [expr 0x1 <<  2 ]
set AT91C_EMAC_TXUBR      [expr 0x1 <<  3 ]
set AT91C_EMAC_TUNDR      [expr 0x1 <<  4 ]
set AT91C_EMAC_RLEX       [expr 0x1 <<  5 ]
set AT91C_EMAC_TXERR      [expr 0x1 <<  6 ]
set AT91C_EMAC_TCOMP      [expr 0x1 <<  7 ]
set AT91C_EMAC_LINK       [expr 0x1 <<  9 ]
set AT91C_EMAC_ROVR       [expr 0x1 << 10 ]
set AT91C_EMAC_HRESP      [expr 0x1 << 11 ]
set AT91C_EMAC_PFRE       [expr 0x1 << 12 ]
set AT91C_EMAC_PTZ        [expr 0x1 << 13 ]
# -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- 
set AT91C_EMAC_MFD        [expr 0x1 <<  0 ]
set AT91C_EMAC_RCOMP      [expr 0x1 <<  1 ]
set AT91C_EMAC_RXUBR      [expr 0x1 <<  2 ]
set AT91C_EMAC_TXUBR      [expr 0x1 <<  3 ]
set AT91C_EMAC_TUNDR      [expr 0x1 <<  4 ]
set AT91C_EMAC_RLEX       [expr 0x1 <<  5 ]
set AT91C_EMAC_TXERR      [expr 0x1 <<  6 ]
set AT91C_EMAC_TCOMP      [expr 0x1 <<  7 ]
set AT91C_EMAC_LINK       [expr 0x1 <<  9 ]
set AT91C_EMAC_ROVR       [expr 0x1 << 10 ]
set AT91C_EMAC_HRESP      [expr 0x1 << 11 ]
set AT91C_EMAC_PFRE       [expr 0x1 << 12 ]
set AT91C_EMAC_PTZ        [expr 0x1 << 13 ]
# -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- 
set AT91C_EMAC_DATA       [expr 0xFFFF <<  0 ]
set AT91C_EMAC_CODE       [expr 0x3 << 16 ]
set AT91C_EMAC_REGA       [expr 0x1F << 18 ]
set AT91C_EMAC_PHYA       [expr 0x1F << 23 ]
set AT91C_EMAC_RW         [expr 0x3 << 28 ]
set AT91C_EMAC_SOF        [expr 0x3 << 30 ]
# -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- 
set AT91C_EMAC_RMII       [expr 0x1 <<  0 ]
set AT91C_EMAC_CLKEN      [expr 0x1 <<  1 ]
# -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- 
set AT91C_EMAC_IP         [expr 0xFFFF <<  0 ]
set AT91C_EMAC_MAG        [expr 0x1 << 16 ]
set AT91C_EMAC_ARP        [expr 0x1 << 17 ]
set AT91C_EMAC_SA1        [expr 0x1 << 18 ]
set AT91C_EMAC_MTI        [expr 0x1 << 19 ]
# -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- 
set AT91C_EMAC_REVREF     [expr 0xFFFF <<  0 ]
set AT91C_EMAC_PARTREF    [expr 0xFFFF << 16 ]

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
#              SOFTWARE API DEFINITION  FOR DMA controller from Synopsys
# *****************************************************************************
# -------- DMA_SAR : (DMA Offset: 0x0)  -------- 
set AT91C_DMA_SADD        [expr 0x0 <<  0 ]
# -------- DMA_DAR : (DMA Offset: 0x8)  -------- 
set AT91C_DMA_DADD        [expr 0x0 <<  0 ]
# -------- DMA_LLP : (DMA Offset: 0x10)  -------- 
set AT91C_DMA_LOC         [expr 0x0 <<  0 ]
# -------- DMA_CTLl : (DMA Offset: 0x18)  -------- 
set AT91C_DMA_INT_EN      [expr 0x1 <<  0 ]
set AT91C_DMA_DST_TR_WIDTH [expr 0x7 <<  1 ]
set AT91C_DMA_SRC_TR_WIDTH [expr 0x7 <<  4 ]
set AT91C_DMA_DINC        [expr 0x3 <<  7 ]
set AT91C_DMA_SINC        [expr 0x3 <<  9 ]
set AT91C_DMA_DEST_MSIZE  [expr 0x7 << 11 ]
set AT91C_DMA_SRC_MSIZE   [expr 0x7 << 14 ]
set AT91C_DMA_S_GATH_EN   [expr 0x1 << 17 ]
set AT91C_DMA_D_SCAT_EN   [expr 0x1 << 18 ]
set AT91C_DMA_TT_FC       [expr 0x7 << 20 ]
set AT91C_DMA_DMS         [expr 0x3 << 23 ]
set AT91C_DMA_SMS         [expr 0x3 << 25 ]
set AT91C_DMA_LLP_D_EN    [expr 0x1 << 27 ]
set AT91C_DMA_LLP_S_EN    [expr 0x1 << 28 ]
# -------- DMA_CTLh : (DMA Offset: 0x1c)  -------- 
set AT91C_DMA_BLOCK_TS    [expr 0xFFF <<  0 ]
set AT91C_DMA_DONE        [expr 0x1 << 12 ]
# -------- DMA_CFGl : (DMA Offset: 0x40)  -------- 
set AT91C_DMA_CH_PRIOR    [expr 0x7 <<  5 ]
set AT91C_DMA_CH_SUSP     [expr 0x1 <<  8 ]
set AT91C_DMA_FIFO_EMPT   [expr 0x1 <<  9 ]
set AT91C_DMA_HS_SEL_DS   [expr 0x1 << 10 ]
set AT91C_DMA_HS_SEL_SR   [expr 0x1 << 11 ]
set AT91C_DMA_LOCK_CH_L   [expr 0x3 << 12 ]
set AT91C_DMA_LOCK_B_L    [expr 0x3 << 14 ]
set AT91C_DMA_LOCK_CH     [expr 0x1 << 16 ]
set AT91C_DMA_LOCK_B      [expr 0x1 << 17 ]
set AT91C_DMA_DS_HS_POL   [expr 0x1 << 18 ]
set AT91C_DMA_SR_HS_POL   [expr 0x1 << 19 ]
set AT91C_DMA_MAX_ABRST   [expr 0x3FF << 20 ]
set AT91C_DMA_RELOAD_SR   [expr 0x1 << 30 ]
set AT91C_DMA_RELOAD_DS   [expr 0x1 << 31 ]
# -------- DMA_CFGh : (DMA Offset: 0x44)  -------- 
set AT91C_DMA_FCMODE      [expr 0x1 <<  0 ]
set AT91C_DMA_FIFO_MODE   [expr 0x1 <<  1 ]
set AT91C_DMA_PROTCTL     [expr 0x7 <<  2 ]
set AT91C_DMA_DS_UPD_EN   [expr 0x1 <<  5 ]
set AT91C_DMA_SS_UPD_EN   [expr 0x1 <<  6 ]
set AT91C_DMA_SRC_PER     [expr 0xF <<  7 ]
set AT91C_DMA_DEST_PER    [expr 0xF << 11 ]
# -------- DMA_SGR : (DMA Offset: 0x48)  -------- 
set AT91C_DMA_SGI         [expr 0xFFFFF <<  0 ]
set AT91C_DMA_SGC         [expr 0xFFF << 20 ]
# -------- DMA_DSR : (DMA Offset: 0x50)  -------- 
set AT91C_DMA_DSI         [expr 0xFFFFF <<  0 ]
set AT91C_DMA_DSC         [expr 0xFFF << 20 ]
# -------- DMA_SAR : (DMA Offset: 0x58)  -------- 
set AT91C_DMA_SADD        [expr 0x0 <<  0 ]
# -------- DMA_DAR : (DMA Offset: 0x60)  -------- 
set AT91C_DMA_DADD        [expr 0x0 <<  0 ]
# -------- DMA_LLP : (DMA Offset: 0x68)  -------- 
set AT91C_DMA_LOC         [expr 0x0 <<  0 ]
# -------- DMA_CTLl : (DMA Offset: 0x70)  -------- 
set AT91C_DMA_INT_EN      [expr 0x1 <<  0 ]
set AT91C_DMA_DST_TR_WIDTH [expr 0x7 <<  1 ]
set AT91C_DMA_SRC_TR_WIDTH [expr 0x7 <<  4 ]
set AT91C_DMA_DINC        [expr 0x3 <<  7 ]
set AT91C_DMA_SINC        [expr 0x3 <<  9 ]
set AT91C_DMA_DEST_MSIZE  [expr 0x7 << 11 ]
set AT91C_DMA_SRC_MSIZE   [expr 0x7 << 14 ]
set AT91C_DMA_S_GATH_EN   [expr 0x1 << 17 ]
set AT91C_DMA_D_SCAT_EN   [expr 0x1 << 18 ]
set AT91C_DMA_TT_FC       [expr 0x7 << 20 ]
set AT91C_DMA_DMS         [expr 0x3 << 23 ]
set AT91C_DMA_SMS         [expr 0x3 << 25 ]
set AT91C_DMA_LLP_D_EN    [expr 0x1 << 27 ]
set AT91C_DMA_LLP_S_EN    [expr 0x1 << 28 ]
# -------- DMA_CTLh : (DMA Offset: 0x74)  -------- 
set AT91C_DMA_BLOCK_TS    [expr 0xFFF <<  0 ]
set AT91C_DMA_DONE        [expr 0x1 << 12 ]
# -------- DMA_CFGl : (DMA Offset: 0x98)  -------- 
set AT91C_DMA_CH_PRIOR    [expr 0x7 <<  5 ]
set AT91C_DMA_CH_SUSP     [expr 0x1 <<  8 ]
set AT91C_DMA_FIFO_EMPT   [expr 0x1 <<  9 ]
set AT91C_DMA_HS_SEL_DS   [expr 0x1 << 10 ]
set AT91C_DMA_HS_SEL_SR   [expr 0x1 << 11 ]
set AT91C_DMA_LOCK_CH_L   [expr 0x3 << 12 ]
set AT91C_DMA_LOCK_B_L    [expr 0x3 << 14 ]
set AT91C_DMA_LOCK_CH     [expr 0x1 << 16 ]
set AT91C_DMA_LOCK_B      [expr 0x1 << 17 ]
set AT91C_DMA_DS_HS_POL   [expr 0x1 << 18 ]
set AT91C_DMA_SR_HS_POL   [expr 0x1 << 19 ]
set AT91C_DMA_MAX_ABRST   [expr 0x3FF << 20 ]
set AT91C_DMA_RELOAD_SR   [expr 0x1 << 30 ]
set AT91C_DMA_RELOAD_DS   [expr 0x1 << 31 ]
# -------- DMA_CFGh : (DMA Offset: 0x9c)  -------- 
set AT91C_DMA_FCMODE      [expr 0x1 <<  0 ]
set AT91C_DMA_FIFO_MODE   [expr 0x1 <<  1 ]
set AT91C_DMA_PROTCTL     [expr 0x7 <<  2 ]
set AT91C_DMA_DS_UPD_EN   [expr 0x1 <<  5 ]
set AT91C_DMA_SS_UPD_EN   [expr 0x1 <<  6 ]
set AT91C_DMA_SRC_PER     [expr 0xF <<  7 ]
set AT91C_DMA_DEST_PER    [expr 0xF << 11 ]
# -------- DMA_SGR : (DMA Offset: 0xa0)  -------- 
set AT91C_DMA_SGI         [expr 0xFFFFF <<  0 ]
set AT91C_DMA_SGC         [expr 0xFFF << 20 ]
# -------- DMA_DSR : (DMA Offset: 0xa8)  -------- 
set AT91C_DMA_DSI         [expr 0xFFFFF <<  0 ]
set AT91C_DMA_DSC         [expr 0xFFF << 20 ]
# -------- DMA_RAWTFR : (DMA Offset: 0x2c0)  -------- 
set AT91C_DMA_RAW         [expr 0x7 <<  0 ]
# -------- DMA_RAWBLOCK : (DMA Offset: 0x2c8)  -------- 
set AT91C_DMA_RAW         [expr 0x7 <<  0 ]
# -------- DMA_RAWSRCTRAN : (DMA Offset: 0x2d0)  -------- 
set AT91C_DMA_RAW         [expr 0x7 <<  0 ]
# -------- DMA_RAWDSTTRAN : (DMA Offset: 0x2d8)  -------- 
set AT91C_DMA_RAW         [expr 0x7 <<  0 ]
# -------- DMA_RAWERR : (DMA Offset: 0x2e0)  -------- 
set AT91C_DMA_RAW         [expr 0x7 <<  0 ]
# -------- DMA_STATUSTFR : (DMA Offset: 0x2e8)  -------- 
set AT91C_DMA_STATUS      [expr 0x7 <<  0 ]
# -------- DMA_STATUSBLOCK : (DMA Offset: 0x2f0)  -------- 
set AT91C_DMA_STATUS      [expr 0x7 <<  0 ]
# -------- DMA_STATUSSRCTRAN : (DMA Offset: 0x2f8)  -------- 
set AT91C_DMA_STATUS      [expr 0x7 <<  0 ]
# -------- DMA_STATUSDSTTRAN : (DMA Offset: 0x300)  -------- 
set AT91C_DMA_STATUS      [expr 0x7 <<  0 ]
# -------- DMA_STATUSERR : (DMA Offset: 0x308)  -------- 
set AT91C_DMA_RAW         [expr 0x7 <<  0 ]
# -------- DMA_MASKTFR : (DMA Offset: 0x310)  -------- 
set AT91C_DMA_INT_MASK    [expr 0x7 <<  0 ]
set AT91C_DMA_INT_M_WE    [expr 0x7 <<  8 ]
# -------- DMA_MASKBLOCK : (DMA Offset: 0x318)  -------- 
set AT91C_DMA_INT_MASK    [expr 0x7 <<  0 ]
set AT91C_DMA_INT_M_WE    [expr 0x7 <<  8 ]
# -------- DMA_MASKSRCTRAN : (DMA Offset: 0x320)  -------- 
set AT91C_DMA_INT_MASK    [expr 0x7 <<  0 ]
set AT91C_DMA_INT_M_WE    [expr 0x7 <<  8 ]
# -------- DMA_MASKDSTTRAN : (DMA Offset: 0x328)  -------- 
set AT91C_DMA_INT_MASK    [expr 0x7 <<  0 ]
set AT91C_DMA_INT_M_WE    [expr 0x7 <<  8 ]
# -------- DMA_MASKERR : (DMA Offset: 0x330)  -------- 
set AT91C_DMA_INT_MASK    [expr 0x7 <<  0 ]
set AT91C_DMA_INT_M_WE    [expr 0x7 <<  8 ]
# -------- DMA_CLEARTFR : (DMA Offset: 0x338)  -------- 
set AT91C_DMA_CLEAR       [expr 0x7 <<  0 ]
# -------- DMA_CLEARBLOCK : (DMA Offset: 0x340)  -------- 
set AT91C_DMA_CLEAR       [expr 0x7 <<  0 ]
# -------- DMA_CLEARSRCTRAN : (DMA Offset: 0x348)  -------- 
set AT91C_DMA_CLEAR       [expr 0x7 <<  0 ]
# -------- DMA_CLEARDSTTRAN : (DMA Offset: 0x350)  -------- 
set AT91C_DMA_CLEAR       [expr 0x7 <<  0 ]
# -------- DMA_CLEARERR : (DMA Offset: 0x358)  -------- 
set AT91C_DMA_CLEAR       [expr 0x7 <<  0 ]
# -------- DMA_STATUSINT : (DMA Offset: 0x360)  -------- 
set AT91C_DMA_TFR         [expr 0x1 <<  0 ]
set AT91C_DMA_BLOCK       [expr 0x1 <<  1 ]
set AT91C_DMA_SRCT        [expr 0x1 <<  2 ]
set AT91C_DMA_DSTT        [expr 0x1 <<  3 ]
set AT91C_DMA_ERR         [expr 0x1 <<  4 ]
# -------- DMA_REQSRCREG : (DMA Offset: 0x368)  -------- 
set AT91C_DMA_SRC_REQ     [expr 0x7 <<  0 ]
set AT91C_DMA_REQ_WE      [expr 0x7 <<  8 ]
# -------- DMA_REQDSTREG : (DMA Offset: 0x370)  -------- 
set AT91C_DMA_DST_REQ     [expr 0x7 <<  0 ]
set AT91C_DMA_REQ_WE      [expr 0x7 <<  8 ]
# -------- DMA_SGLREQSRCREG : (DMA Offset: 0x378)  -------- 
set AT91C_DMA_S_SG_REQ    [expr 0x7 <<  0 ]
set AT91C_DMA_REQ_WE      [expr 0x7 <<  8 ]
# -------- DMA_SGLREQDSTREG : (DMA Offset: 0x380)  -------- 
set AT91C_DMA_D_SG_REQ    [expr 0x7 <<  0 ]
set AT91C_DMA_REQ_WE      [expr 0x7 <<  8 ]
# -------- DMA_LSTREQSRCREG : (DMA Offset: 0x388)  -------- 
set AT91C_DMA_LSTSRC      [expr 0x7 <<  0 ]
set AT91C_DMA_LSTSR_WE    [expr 0x7 <<  8 ]
# -------- DMA_LSTREQDSTREG : (DMA Offset: 0x390)  -------- 
set AT91C_DMA_LSTDST      [expr 0x7 <<  0 ]
set AT91C_DMA_LSTDS_WE    [expr 0x7 <<  8 ]
# -------- DMA_DMACFGREG : (DMA Offset: 0x398)  -------- 
set AT91C_DMA_DMA_EN      [expr 0x7 <<  0 ]
# -------- DMA_CHENREG : (DMA Offset: 0x3a0)  -------- 
set AT91C_DMA_CH_EN       [expr 0x7 <<  0 ]
set AT91C_DMA_CH_EN_WE    [expr 0x7 <<  8 ]
# -------- DMA_DMATESTREG : (DMA Offset: 0x3b0)  -------- 
set AT91C_DMA_TEST_SLV_IF [expr 0x1 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR USB Device Interface
# *****************************************************************************
# -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- 
set AT91C_UDP_FRM_NUM     [expr 0x7FF <<  0 ]
set AT91C_UDP_FRM_ERR     [expr 0x1 << 16 ]
set AT91C_UDP_FRM_OK      [expr 0x1 << 17 ]
# -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- 
set AT91C_UDP_FADDEN      [expr 0x1 <<  0 ]
set AT91C_UDP_CONFG       [expr 0x1 <<  1 ]
set AT91C_UDP_ESR         [expr 0x1 <<  2 ]
set AT91C_UDP_RSMINPR     [expr 0x1 <<  3 ]
set AT91C_UDP_RMWUPE      [expr 0x1 <<  4 ]
# -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- 
set AT91C_UDP_FADD        [expr 0xFF <<  0 ]
set AT91C_UDP_FEN         [expr 0x1 <<  8 ]
# -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_ENDBUSRES   [expr 0x1 << 12 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- 
set AT91C_UDP_EP0         [expr 0x1 <<  0 ]
set AT91C_UDP_EP1         [expr 0x1 <<  1 ]
set AT91C_UDP_EP2         [expr 0x1 <<  2 ]
set AT91C_UDP_EP3         [expr 0x1 <<  3 ]
set AT91C_UDP_EP4         [expr 0x1 <<  4 ]
set AT91C_UDP_EP5         [expr 0x1 <<  5 ]
# -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- 
set AT91C_UDP_TXCOMP      [expr 0x1 <<  0 ]
set AT91C_UDP_RX_DATA_BK0 [expr 0x1 <<  1 ]
set AT91C_UDP_RXSETUP     [expr 0x1 <<  2 ]
set AT91C_UDP_STALLSENT   [expr 0x1 <<  3 ]
set AT91C_UDP_ISOERROR    [expr 0x1 <<  3 ]
set AT91C_UDP_TXPKTRDY    [expr 0x1 <<  4 ]
set AT91C_UDP_FORCESTALL  [expr 0x1 <<  5 ]
set AT91C_UDP_RX_DATA_BK1 [expr 0x1 <<  6 ]
set AT91C_UDP_DIR         [expr 0x1 <<  7 ]
set AT91C_UDP_EPTYPE      [expr 0x7 <<  8 ]
set 	AT91C_UDP_EPTYPE_CTRL                 [expr 0x0 <<  8 ]
set 	AT91C_UDP_EPTYPE_ISO_OUT              [expr 0x1 <<  8 ]
set 	AT91C_UDP_EPTYPE_BULK_OUT             [expr 0x2 <<  8 ]
set 	AT91C_UDP_EPTYPE_INT_OUT              [expr 0x3 <<  8 ]
set 	AT91C_UDP_EPTYPE_ISO_IN               [expr 0x5 <<  8 ]
set 	AT91C_UDP_EPTYPE_BULK_IN              [expr 0x6 <<  8 ]
set 	AT91C_UDP_EPTYPE_INT_IN               [expr 0x7 <<  8 ]
set AT91C_UDP_DTGLE       [expr 0x1 << 11 ]
set AT91C_UDP_EPEDS       [expr 0x1 << 15 ]
set AT91C_UDP_RXBYTECNT   [expr 0x7FF << 16 ]
# -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- 
set AT91C_UDP_TXVDIS      [expr 0x1 <<  8 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR USB Host Interface
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Trickbox (external) / SIMULATION ONLY
# *****************************************************************************
# -------- TBOX_DMAEXTREQ : (TBOX Offset: 0x810)  -------- 
set AT91C_TBOX_DMAEXTREQ0 [expr 0x1 <<  0 ]
set AT91C_TBOX_DMAEXTREQ1 [expr 0x1 <<  1 ]
set AT91C_TBOX_DMAEXTREQ2 [expr 0x1 <<  2 ]
set AT91C_TBOX_DMAEXTREQ3 [expr 0x1 <<  3 ]

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
#              SOFTWARE API DEFINITION  FOR Image Sensor Interface
# *****************************************************************************
# -------- ISI_CR1 : (ISI Offset: 0x0) ISI Control Register 1 -------- 
set AT91C_ISI_RST         [expr 0x1 <<  0 ]
set AT91C_ISI_DISABLE     [expr 0x1 <<  1 ]
set AT91C_ISI_HSYNC_POL   [expr 0x1 <<  2 ]
set AT91C_ISI_HSYNC_POL   [expr 0x1 <<  3 ]
set AT91C_ISI_PIXCLK_POL  [expr 0x1 <<  4 ]
set AT91C_ISI_EMB_SYNC    [expr 0x1 <<  6 ]
set AT91C_ISI_CRC_SYNC    [expr 0x1 <<  7 ]
set AT91C_ISI_CRC_SYNC    [expr 0x7 <<  8 ]
set AT91C_ISI_FULL        [expr 0x1 << 12 ]
set AT91C_ISI_THMASK      [expr 0x3 << 13 ]
set 	AT91C_ISI_THMASK_4_8_16_BURST         [expr 0x0 << 13 ]
set 	AT91C_ISI_THMASK_8_16_BURST           [expr 0x1 << 13 ]
set 	AT91C_ISI_THMASK_16_BURST             [expr 0x2 << 13 ]
set AT91C_ISI_CODEC_ON    [expr 0x1 << 15 ]
set AT91C_ISI_SLD         [expr 0xFF << 16 ]
set AT91C_ISI_SFD         [expr 0xFF << 24 ]
# -------- ISI_CR2 : (ISI Offset: 0x4) ISI Control Register 2 -------- 
set AT91C_ISI_IM_VSIZE    [expr 0x7FF <<  0 ]
set AT91C_ISI_GS_MODE     [expr 0x1 << 11 ]
set AT91C_ISI_RGB_MODE    [expr 0x3 << 12 ]
set 	AT91C_ISI_RGB_MODE_RGB_888              [expr 0x0 << 12 ]
set 	AT91C_ISI_RGB_MODE_RGB_565              [expr 0x1 << 12 ]
set 	AT91C_ISI_RGB_MODE_RGB_555              [expr 0x2 << 12 ]
set AT91C_ISI_GRAYSCALE   [expr 0x1 << 13 ]
set AT91C_ISI_RGB_SWAP    [expr 0x1 << 14 ]
set AT91C_ISI_COL_SPACE   [expr 0x1 << 15 ]
set AT91C_ISI_IM_HSIZE    [expr 0x7FF << 16 ]
set AT91C_ISI_RGB_MODE    [expr 0x3 << 28 ]
set 	AT91C_ISI_RGB_MODE_YCC_DEF              [expr 0x0 << 28 ]
set 	AT91C_ISI_RGB_MODE_YCC_MOD1             [expr 0x1 << 28 ]
set 	AT91C_ISI_RGB_MODE_YCC_MOD2             [expr 0x2 << 28 ]
set 	AT91C_ISI_RGB_MODE_YCC_MOD3             [expr 0x3 << 28 ]
set AT91C_ISI_RGB_CFG     [expr 0x3 << 30 ]
set 	AT91C_ISI_RGB_CFG_RGB_DEF              [expr 0x0 << 30 ]
set 	AT91C_ISI_RGB_CFG_RGB_MOD1             [expr 0x1 << 30 ]
set 	AT91C_ISI_RGB_CFG_RGB_MOD2             [expr 0x2 << 30 ]
set 	AT91C_ISI_RGB_CFG_RGB_MOD3             [expr 0x3 << 30 ]
# -------- ISI_SR : (ISI Offset: 0x8) ISI Status Register -------- 
set AT91C_ISI_SOF         [expr 0x1 <<  0 ]
set AT91C_ISI_DIS         [expr 0x1 <<  1 ]
set AT91C_ISI_SOFTRST     [expr 0x1 <<  2 ]
set AT91C_ISI_CRC_ERR     [expr 0x1 <<  4 ]
set AT91C_ISI_FO_C_OVF    [expr 0x1 <<  5 ]
set AT91C_ISI_FO_P_OVF    [expr 0x1 <<  6 ]
set AT91C_ISI_FO_P_EMP    [expr 0x1 <<  7 ]
set AT91C_ISI_FO_C_EMP    [expr 0x1 <<  8 ]
set AT91C_ISI_FR_OVR      [expr 0x1 <<  9 ]
# -------- ISI_IER : (ISI Offset: 0xc) ISI Interrupt Enable Register -------- 
set AT91C_ISI_SOF         [expr 0x1 <<  0 ]
set AT91C_ISI_DIS         [expr 0x1 <<  1 ]
set AT91C_ISI_SOFTRST     [expr 0x1 <<  2 ]
set AT91C_ISI_CRC_ERR     [expr 0x1 <<  4 ]
set AT91C_ISI_FO_C_OVF    [expr 0x1 <<  5 ]
set AT91C_ISI_FO_P_OVF    [expr 0x1 <<  6 ]
set AT91C_ISI_FO_P_EMP    [expr 0x1 <<  7 ]
set AT91C_ISI_FO_C_EMP    [expr 0x1 <<  8 ]
set AT91C_ISI_FR_OVR      [expr 0x1 <<  9 ]
# -------- ISI_IDR : (ISI Offset: 0x10) ISI Interrupt Disable Register -------- 
set AT91C_ISI_SOF         [expr 0x1 <<  0 ]
set AT91C_ISI_DIS         [expr 0x1 <<  1 ]
set AT91C_ISI_SOFTRST     [expr 0x1 <<  2 ]
set AT91C_ISI_CRC_ERR     [expr 0x1 <<  4 ]
set AT91C_ISI_FO_C_OVF    [expr 0x1 <<  5 ]
set AT91C_ISI_FO_P_OVF    [expr 0x1 <<  6 ]
set AT91C_ISI_FO_P_EMP    [expr 0x1 <<  7 ]
set AT91C_ISI_FO_C_EMP    [expr 0x1 <<  8 ]
set AT91C_ISI_FR_OVR      [expr 0x1 <<  9 ]
# -------- ISI_IMR : (ISI Offset: 0x14) ISI Interrupt Mask Register -------- 
set AT91C_ISI_SOF         [expr 0x1 <<  0 ]
set AT91C_ISI_DIS         [expr 0x1 <<  1 ]
set AT91C_ISI_SOFTRST     [expr 0x1 <<  2 ]
set AT91C_ISI_CRC_ERR     [expr 0x1 <<  4 ]
set AT91C_ISI_FO_C_OVF    [expr 0x1 <<  5 ]
set AT91C_ISI_FO_P_OVF    [expr 0x1 <<  6 ]
set AT91C_ISI_FO_P_EMP    [expr 0x1 <<  7 ]
set AT91C_ISI_FO_C_EMP    [expr 0x1 <<  8 ]
set AT91C_ISI_FR_OVR      [expr 0x1 <<  9 ]
# -------- ISI_PSIZE : (ISI Offset: 0x20) ISI Preview Register -------- 
set AT91C_ISI_PREV_VSIZE  [expr 0x3FF <<  0 ]
set AT91C_ISI_PREV_HSIZE  [expr 0x3FF << 16 ]
# -------- ISI_Y2R_SET0 : (ISI Offset: 0x30) Color Space Conversion YCrCb to RGB Register -------- 
set AT91C_ISI_Y2R_C0      [expr 0xFF <<  0 ]
set AT91C_ISI_Y2R_C1      [expr 0xFF <<  8 ]
set AT91C_ISI_Y2R_C2      [expr 0xFF << 16 ]
set AT91C_ISI_Y2R_C3      [expr 0xFF << 24 ]
# -------- ISI_Y2R_SET1 : (ISI Offset: 0x34) ISI Color Space Conversion YCrCb to RGB set 1 Register -------- 
set AT91C_ISI_Y2R_C4      [expr 0x1FF <<  0 ]
set AT91C_ISI_Y2R_YOFF    [expr 0xFF << 12 ]
set AT91C_ISI_Y2R_CROFF   [expr 0xFF << 13 ]
set AT91C_ISI_Y2R_CBFF    [expr 0xFF << 14 ]
# -------- ISI_R2Y_SET0 : (ISI Offset: 0x38) Color Space Conversion RGB to YCrCb set 0 register -------- 
set AT91C_ISI_R2Y_C0      [expr 0x7F <<  0 ]
set AT91C_ISI_R2Y_C1      [expr 0x7F <<  1 ]
set AT91C_ISI_R2Y_C2      [expr 0x7F <<  3 ]
set AT91C_ISI_R2Y_ROFF    [expr 0x1 <<  4 ]
# -------- ISI_R2Y_SET1 : (ISI Offset: 0x3c) Color Space Conversion RGB to YCrCb set 1 register -------- 
set AT91C_ISI_R2Y_C3      [expr 0x7F <<  0 ]
set AT91C_ISI_R2Y_C4      [expr 0x7F <<  1 ]
set AT91C_ISI_R2Y_C5      [expr 0x7F <<  3 ]
set AT91C_ISI_R2Y_GOFF    [expr 0x1 <<  4 ]
# -------- ISI_R2Y_SET2 : (ISI Offset: 0x40) Color Space Conversion RGB to YCrCb set 2 register -------- 
set AT91C_ISI_R2Y_C6      [expr 0x7F <<  0 ]
set AT91C_ISI_R2Y_C7      [expr 0x7F <<  1 ]
set AT91C_ISI_R2Y_C8      [expr 0x7F <<  3 ]
set AT91C_ISI_R2Y_BOFF    [expr 0x1 <<  4 ]

# *****************************************************************************
#               REGISTER ADDRESS DEFINITION FOR AT91SAM9263
# *****************************************************************************
# ========== Register definition for SYS peripheral ========== 
set AT91C_SYS_ECC0  0xFFFFE000
set AT91C_SYS_GPBR  0xFFFFFD60
set AT91C_SYS_ECC1  0xFFFFE600
# ========== Register definition for EBI0 peripheral ========== 
set AT91C_EBI0_DUMMY 0xFFFFE200
# ========== Register definition for SDRAMC0 peripheral ========== 
set AT91C_SDRAMC0_ISR 0xFFFFE220
set AT91C_SDRAMC0_IDR 0xFFFFE218
set AT91C_SDRAMC0_LPR 0xFFFFE210
set AT91C_SDRAMC0_CR 0xFFFFE208
set AT91C_SDRAMC0_MR 0xFFFFE200
set AT91C_SDRAMC0_MDR 0xFFFFE224
set AT91C_SDRAMC0_IMR 0xFFFFE21C
set AT91C_SDRAMC0_IER 0xFFFFE214
set AT91C_SDRAMC0_HSR 0xFFFFE20C
set AT91C_SDRAMC0_TR 0xFFFFE204
# ========== Register definition for SMC0 peripheral ========== 
set AT91C_SMC0_SETUP7 0xFFFFE470
set AT91C_SMC0_CYCLE6 0xFFFFE468
set AT91C_SMC0_SETUP6 0xFFFFE460
set AT91C_SMC0_CYCLE5 0xFFFFE458
set AT91C_SMC0_SETUP5 0xFFFFE450
set AT91C_SMC0_SETUP2 0xFFFFE420
set AT91C_SMC0_CYCLE1 0xFFFFE418
set AT91C_SMC0_SETUP1 0xFFFFE410
set AT91C_SMC0_CYCLE0 0xFFFFE408
set AT91C_SMC0_SETUP0 0xFFFFE400
set AT91C_SMC0_CTRL7 0xFFFFE47C
set AT91C_SMC0_PULSE7 0xFFFFE474
set AT91C_SMC0_CTRL6 0xFFFFE46C
set AT91C_SMC0_PULSE6 0xFFFFE464
set AT91C_SMC0_PULSE3 0xFFFFE434
set AT91C_SMC0_CTRL2 0xFFFFE42C
set AT91C_SMC0_PULSE2 0xFFFFE424
set AT91C_SMC0_CTRL1 0xFFFFE41C
set AT91C_SMC0_PULSE1 0xFFFFE414
set AT91C_SMC0_CYCLE7 0xFFFFE478
set AT91C_SMC0_CYCLE2 0xFFFFE428
set AT91C_SMC0_SETUP3 0xFFFFE430
set AT91C_SMC0_CYCLE3 0xFFFFE438
set AT91C_SMC0_SETUP4 0xFFFFE440
set AT91C_SMC0_CTRL3 0xFFFFE43C
set AT91C_SMC0_PULSE4 0xFFFFE444
set AT91C_SMC0_CYCLE4 0xFFFFE448
set AT91C_SMC0_CTRL5 0xFFFFE45C
set AT91C_SMC0_PULSE5 0xFFFFE454
set AT91C_SMC0_CTRL4 0xFFFFE44C
set AT91C_SMC0_CTRL0 0xFFFFE40C
set AT91C_SMC0_PULSE0 0xFFFFE404
# ========== Register definition for EBI1 peripheral ========== 
set AT91C_EBI1_DUMMY 0xFFFFE800
# ========== Register definition for SDRAMC1 peripheral ========== 
set AT91C_SDRAMC1_MDR 0xFFFFE824
set AT91C_SDRAMC1_IMR 0xFFFFE81C
set AT91C_SDRAMC1_IER 0xFFFFE814
set AT91C_SDRAMC1_HSR 0xFFFFE80C
set AT91C_SDRAMC1_TR 0xFFFFE804
set AT91C_SDRAMC1_ISR 0xFFFFE820
set AT91C_SDRAMC1_IDR 0xFFFFE818
set AT91C_SDRAMC1_LPR 0xFFFFE810
set AT91C_SDRAMC1_CR 0xFFFFE808
set AT91C_SDRAMC1_MR 0xFFFFE800
# ========== Register definition for SMC1 peripheral ========== 
set AT91C_SMC1_SETUP2 0xFFFFEA20
set AT91C_SMC1_CTRL7 0xFFFFEA7C
set AT91C_SMC1_SETUP3 0xFFFFEA30
set AT91C_SMC1_PULSE4 0xFFFFEA44
set AT91C_SMC1_PULSE3 0xFFFFEA34
set AT91C_SMC1_CYCLE5 0xFFFFEA58
set AT91C_SMC1_CYCLE4 0xFFFFEA48
set AT91C_SMC1_SETUP1 0xFFFFEA10
set AT91C_SMC1_SETUP0 0xFFFFEA00
set AT91C_SMC1_CTRL6 0xFFFFEA6C
set AT91C_SMC1_CTRL5 0xFFFFEA5C
set AT91C_SMC1_PULSE1 0xFFFFEA14
set AT91C_SMC1_PULSE0 0xFFFFEA04
set AT91C_SMC1_SETUP7 0xFFFFEA70
set AT91C_SMC1_CYCLE1 0xFFFFEA18
set AT91C_SMC1_PULSE2 0xFFFFEA24
set AT91C_SMC1_CYCLE2 0xFFFFEA28
set AT91C_SMC1_CYCLE3 0xFFFFEA38
set AT91C_SMC1_CTRL3 0xFFFFEA3C
set AT91C_SMC1_CTRL2 0xFFFFEA2C
set AT91C_SMC1_CTRL4 0xFFFFEA4C
set AT91C_SMC1_SETUP4 0xFFFFEA40
set AT91C_SMC1_SETUP5 0xFFFFEA50
set AT91C_SMC1_SETUP6 0xFFFFEA60
set AT91C_SMC1_CYCLE0 0xFFFFEA08
set AT91C_SMC1_PULSE5 0xFFFFEA54
set AT91C_SMC1_PULSE6 0xFFFFEA64
set AT91C_SMC1_PULSE7 0xFFFFEA74
set AT91C_SMC1_CTRL0 0xFFFFEA0C
set AT91C_SMC1_CTRL1 0xFFFFEA1C
set AT91C_SMC1_CYCLE6 0xFFFFEA68
set AT91C_SMC1_CYCLE7 0xFFFFEA78
# ========== Register definition for MATRIX peripheral ========== 
set AT91C_MATRIX_MCFG6 0xFFFFEC18
set AT91C_MATRIX_MCFG7 0xFFFFEC1C
set AT91C_MATRIX_PRAS1 0xFFFFEC88
set AT91C_MATRIX_SCFG0 0xFFFFEC40
set AT91C_MATRIX_MCFG8 0xFFFFEC20
set AT91C_MATRIX_PRBS3 0xFFFFEC9C
set AT91C_MATRIX_PRBS1 0xFFFFEC8C
set AT91C_MATRIX_SCFG5 0xFFFFEC54
set AT91C_MATRIX_SCFG1 0xFFFFEC44
set AT91C_MATRIX_PRAS6 0xFFFFECB0
set AT91C_MATRIX_PRAS4 0xFFFFECA0
set AT91C_MATRIX_SCFG2 0xFFFFEC48
set AT91C_MATRIX_SCFG6 0xFFFFEC58
set AT91C_MATRIX_MCFG0 0xFFFFEC00
set AT91C_MATRIX_MCFG4 0xFFFFEC10
set AT91C_MATRIX_PRBS6 0xFFFFECB4
set AT91C_MATRIX_SCFG7 0xFFFFEC5C
set AT91C_MATRIX_MCFG5 0xFFFFEC14
set AT91C_MATRIX_PRAS0 0xFFFFEC80
set AT91C_MATRIX_PRAS2 0xFFFFEC90
set AT91C_MATRIX_PRBS0 0xFFFFEC84
set AT91C_MATRIX_PRBS2 0xFFFFEC94
set AT91C_MATRIX_PRBS4 0xFFFFECA4
set AT91C_MATRIX_SCFG3 0xFFFFEC4C
set AT91C_MATRIX_MCFG1 0xFFFFEC04
set AT91C_MATRIX_MRCR 0xFFFFED00
set AT91C_MATRIX_PRAS3 0xFFFFEC98
set AT91C_MATRIX_PRAS5 0xFFFFECA8
set AT91C_MATRIX_PRAS7 0xFFFFECB8
set AT91C_MATRIX_SCFG4 0xFFFFEC50
set AT91C_MATRIX_MCFG2 0xFFFFEC08
set AT91C_MATRIX_PRBS5 0xFFFFECAC
set AT91C_MATRIX_PRBS7 0xFFFFECBC
set AT91C_MATRIX_MCFG3 0xFFFFEC0C
# ========== Register definition for CCFG peripheral ========== 
set AT91C_CCFG_MATRIXVERSION 0xFFFFEDFC
set AT91C_CCFG_EBI1CSA 0xFFFFED24
set AT91C_CCFG_TCMR 0xFFFFED14
set AT91C_CCFG_EBI0CSA 0xFFFFED20
# ========== Register definition for PDC_DBGU peripheral ========== 
set AT91C_DBGU_PTCR 0xFFFFEF20
set AT91C_DBGU_TNPR 0xFFFFEF18
set AT91C_DBGU_RNPR 0xFFFFEF10
set AT91C_DBGU_TPR  0xFFFFEF08
set AT91C_DBGU_RPR  0xFFFFEF00
set AT91C_DBGU_PTSR 0xFFFFEF24
set AT91C_DBGU_TNCR 0xFFFFEF1C
set AT91C_DBGU_RNCR 0xFFFFEF14
set AT91C_DBGU_TCR  0xFFFFEF0C
set AT91C_DBGU_RCR  0xFFFFEF04
# ========== Register definition for DBGU peripheral ========== 
set AT91C_DBGU_MR   0xFFFFEE04
set AT91C_DBGU_FNTR 0xFFFFEE48
set AT91C_DBGU_CIDR 0xFFFFEE40
set AT91C_DBGU_BRGR 0xFFFFEE20
set AT91C_DBGU_RHR  0xFFFFEE18
set AT91C_DBGU_IMR  0xFFFFEE10
set AT91C_DBGU_IER  0xFFFFEE08
set AT91C_DBGU_CR   0xFFFFEE00
set AT91C_DBGU_EXID 0xFFFFEE44
set AT91C_DBGU_THR  0xFFFFEE1C
set AT91C_DBGU_CSR  0xFFFFEE14
set AT91C_DBGU_IDR  0xFFFFEE0C
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
# ========== Register definition for PIOA peripheral ========== 
set AT91C_PIOA_BSR  0xFFFFF274
set AT91C_PIOA_IDR  0xFFFFF244
set AT91C_PIOA_PDSR 0xFFFFF23C
set AT91C_PIOA_CODR 0xFFFFF234
set AT91C_PIOA_IFDR 0xFFFFF224
set AT91C_PIOA_OWSR 0xFFFFF2A8
set AT91C_PIOA_OWER 0xFFFFF2A0
set AT91C_PIOA_MDER 0xFFFFF250
set AT91C_PIOA_IMR  0xFFFFF248
set AT91C_PIOA_IER  0xFFFFF240
set AT91C_PIOA_ODSR 0xFFFFF238
set AT91C_PIOA_OWDR 0xFFFFF2A4
set AT91C_PIOA_ISR  0xFFFFF24C
set AT91C_PIOA_MDDR 0xFFFFF254
set AT91C_PIOA_MDSR 0xFFFFF258
set AT91C_PIOA_PER  0xFFFFF200
set AT91C_PIOA_PSR  0xFFFFF208
set AT91C_PIOA_PPUER 0xFFFFF264
set AT91C_PIOA_ODR  0xFFFFF214
set AT91C_PIOA_PDR  0xFFFFF204
set AT91C_PIOA_ABSR 0xFFFFF278
set AT91C_PIOA_ASR  0xFFFFF270
set AT91C_PIOA_PPUSR 0xFFFFF268
set AT91C_PIOA_PPUDR 0xFFFFF260
set AT91C_PIOA_SODR 0xFFFFF230
set AT91C_PIOA_IFSR 0xFFFFF228
set AT91C_PIOA_IFER 0xFFFFF220
set AT91C_PIOA_OSR  0xFFFFF218
set AT91C_PIOA_OER  0xFFFFF210
# ========== Register definition for PIOB peripheral ========== 
set AT91C_PIOB_IMR  0xFFFFF448
set AT91C_PIOB_IER  0xFFFFF440
set AT91C_PIOB_OWDR 0xFFFFF4A4
set AT91C_PIOB_ISR  0xFFFFF44C
set AT91C_PIOB_PPUDR 0xFFFFF460
set AT91C_PIOB_MDSR 0xFFFFF458
set AT91C_PIOB_MDER 0xFFFFF450
set AT91C_PIOB_PER  0xFFFFF400
set AT91C_PIOB_PSR  0xFFFFF408
set AT91C_PIOB_OER  0xFFFFF410
set AT91C_PIOB_BSR  0xFFFFF474
set AT91C_PIOB_PPUER 0xFFFFF464
set AT91C_PIOB_MDDR 0xFFFFF454
set AT91C_PIOB_PDR  0xFFFFF404
set AT91C_PIOB_ODR  0xFFFFF414
set AT91C_PIOB_IFDR 0xFFFFF424
set AT91C_PIOB_ABSR 0xFFFFF478
set AT91C_PIOB_ASR  0xFFFFF470
set AT91C_PIOB_PPUSR 0xFFFFF468
set AT91C_PIOB_ODSR 0xFFFFF438
set AT91C_PIOB_SODR 0xFFFFF430
set AT91C_PIOB_IFSR 0xFFFFF428
set AT91C_PIOB_IFER 0xFFFFF420
set AT91C_PIOB_OSR  0xFFFFF418
set AT91C_PIOB_IDR  0xFFFFF444
set AT91C_PIOB_PDSR 0xFFFFF43C
set AT91C_PIOB_CODR 0xFFFFF434
set AT91C_PIOB_OWSR 0xFFFFF4A8
set AT91C_PIOB_OWER 0xFFFFF4A0
# ========== Register definition for PIOC peripheral ========== 
set AT91C_PIOC_OWSR 0xFFFFF6A8
set AT91C_PIOC_PPUSR 0xFFFFF668
set AT91C_PIOC_PPUDR 0xFFFFF660
set AT91C_PIOC_MDSR 0xFFFFF658
set AT91C_PIOC_MDER 0xFFFFF650
set AT91C_PIOC_IMR  0xFFFFF648
set AT91C_PIOC_OSR  0xFFFFF618
set AT91C_PIOC_OER  0xFFFFF610
set AT91C_PIOC_PSR  0xFFFFF608
set AT91C_PIOC_PER  0xFFFFF600
set AT91C_PIOC_BSR  0xFFFFF674
set AT91C_PIOC_PPUER 0xFFFFF664
set AT91C_PIOC_IFDR 0xFFFFF624
set AT91C_PIOC_ODR  0xFFFFF614
set AT91C_PIOC_ABSR 0xFFFFF678
set AT91C_PIOC_ASR  0xFFFFF670
set AT91C_PIOC_IFER 0xFFFFF620
set AT91C_PIOC_IFSR 0xFFFFF628
set AT91C_PIOC_SODR 0xFFFFF630
set AT91C_PIOC_ODSR 0xFFFFF638
set AT91C_PIOC_CODR 0xFFFFF634
set AT91C_PIOC_PDSR 0xFFFFF63C
set AT91C_PIOC_OWER 0xFFFFF6A0
set AT91C_PIOC_IER  0xFFFFF640
set AT91C_PIOC_OWDR 0xFFFFF6A4
set AT91C_PIOC_MDDR 0xFFFFF654
set AT91C_PIOC_ISR  0xFFFFF64C
set AT91C_PIOC_IDR  0xFFFFF644
set AT91C_PIOC_PDR  0xFFFFF604
# ========== Register definition for PIOD peripheral ========== 
set AT91C_PIOD_IFDR 0xFFFFF824
set AT91C_PIOD_ODR  0xFFFFF814
set AT91C_PIOD_ABSR 0xFFFFF878
set AT91C_PIOD_SODR 0xFFFFF830
set AT91C_PIOD_IFSR 0xFFFFF828
set AT91C_PIOD_CODR 0xFFFFF834
set AT91C_PIOD_ODSR 0xFFFFF838
set AT91C_PIOD_IER  0xFFFFF840
set AT91C_PIOD_IMR  0xFFFFF848
set AT91C_PIOD_OWDR 0xFFFFF8A4
set AT91C_PIOD_MDDR 0xFFFFF854
set AT91C_PIOD_PDSR 0xFFFFF83C
set AT91C_PIOD_IDR  0xFFFFF844
set AT91C_PIOD_ISR  0xFFFFF84C
set AT91C_PIOD_PDR  0xFFFFF804
set AT91C_PIOD_OWSR 0xFFFFF8A8
set AT91C_PIOD_OWER 0xFFFFF8A0
set AT91C_PIOD_ASR  0xFFFFF870
set AT91C_PIOD_PPUSR 0xFFFFF868
set AT91C_PIOD_PPUDR 0xFFFFF860
set AT91C_PIOD_MDSR 0xFFFFF858
set AT91C_PIOD_MDER 0xFFFFF850
set AT91C_PIOD_IFER 0xFFFFF820
set AT91C_PIOD_OSR  0xFFFFF818
set AT91C_PIOD_OER  0xFFFFF810
set AT91C_PIOD_PSR  0xFFFFF808
set AT91C_PIOD_PER  0xFFFFF800
set AT91C_PIOD_BSR  0xFFFFF874
set AT91C_PIOD_PPUER 0xFFFFF864
# ========== Register definition for PIOE peripheral ========== 
set AT91C_PIOE_PDSR 0xFFFFFA3C
set AT91C_PIOE_CODR 0xFFFFFA34
set AT91C_PIOE_OWER 0xFFFFFAA0
set AT91C_PIOE_MDER 0xFFFFFA50
set AT91C_PIOE_IMR  0xFFFFFA48
set AT91C_PIOE_IER  0xFFFFFA40
set AT91C_PIOE_ODSR 0xFFFFFA38
set AT91C_PIOE_SODR 0xFFFFFA30
set AT91C_PIOE_PER  0xFFFFFA00
set AT91C_PIOE_OWDR 0xFFFFFAA4
set AT91C_PIOE_PPUER 0xFFFFFA64
set AT91C_PIOE_MDDR 0xFFFFFA54
set AT91C_PIOE_ISR  0xFFFFFA4C
set AT91C_PIOE_IDR  0xFFFFFA44
set AT91C_PIOE_PDR  0xFFFFFA04
set AT91C_PIOE_ODR  0xFFFFFA14
set AT91C_PIOE_OWSR 0xFFFFFAA8
set AT91C_PIOE_ABSR 0xFFFFFA78
set AT91C_PIOE_ASR  0xFFFFFA70
set AT91C_PIOE_PPUSR 0xFFFFFA68
set AT91C_PIOE_PPUDR 0xFFFFFA60
set AT91C_PIOE_MDSR 0xFFFFFA58
set AT91C_PIOE_PSR  0xFFFFFA08
set AT91C_PIOE_OER  0xFFFFFA10
set AT91C_PIOE_OSR  0xFFFFFA18
set AT91C_PIOE_IFER 0xFFFFFA20
set AT91C_PIOE_BSR  0xFFFFFA74
set AT91C_PIOE_IFDR 0xFFFFFA24
set AT91C_PIOE_IFSR 0xFFFFFA28
# ========== Register definition for CKGR peripheral ========== 
set AT91C_CKGR_PLLBR 0xFFFFFC2C
set AT91C_CKGR_MCFR 0xFFFFFC24
set AT91C_CKGR_PLLAR 0xFFFFFC28
set AT91C_CKGR_MOR  0xFFFFFC20
# ========== Register definition for PMC peripheral ========== 
set AT91C_PMC_SCSR  0xFFFFFC08
set AT91C_PMC_SCER  0xFFFFFC00
set AT91C_PMC_IMR   0xFFFFFC6C
set AT91C_PMC_IDR   0xFFFFFC64
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
# ========== Register definition for RSTC peripheral ========== 
set AT91C_RSTC_RSR  0xFFFFFD04
set AT91C_RSTC_RMR  0xFFFFFD08
set AT91C_RSTC_RCR  0xFFFFFD00
# ========== Register definition for SHDWC peripheral ========== 
set AT91C_SHDWC_SHMR 0xFFFFFD14
set AT91C_SHDWC_SHSR 0xFFFFFD18
set AT91C_SHDWC_SHCR 0xFFFFFD10
# ========== Register definition for RTTC0 peripheral ========== 
set AT91C_RTTC0_RTSR 0xFFFFFD2C
set AT91C_RTTC0_RTAR 0xFFFFFD24
set AT91C_RTTC0_RTVR 0xFFFFFD28
set AT91C_RTTC0_RTMR 0xFFFFFD20
# ========== Register definition for RTTC1 peripheral ========== 
set AT91C_RTTC1_RTSR 0xFFFFFD5C
set AT91C_RTTC1_RTAR 0xFFFFFD54
set AT91C_RTTC1_RTVR 0xFFFFFD58
set AT91C_RTTC1_RTMR 0xFFFFFD50
# ========== Register definition for PITC peripheral ========== 
set AT91C_PITC_PIIR 0xFFFFFD3C
set AT91C_PITC_PISR 0xFFFFFD34
set AT91C_PITC_PIVR 0xFFFFFD38
set AT91C_PITC_PIMR 0xFFFFFD30
# ========== Register definition for WDTC peripheral ========== 
set AT91C_WDTC_WDMR 0xFFFFFD44
set AT91C_WDTC_WDSR 0xFFFFFD48
set AT91C_WDTC_WDCR 0xFFFFFD40
# ========== Register definition for TC0 peripheral ========== 
set AT91C_TC0_IDR   0xFFF7C028
set AT91C_TC0_SR    0xFFF7C020
set AT91C_TC0_RB    0xFFF7C018
set AT91C_TC0_CV    0xFFF7C010
set AT91C_TC0_CCR   0xFFF7C000
set AT91C_TC0_IMR   0xFFF7C02C
set AT91C_TC0_IER   0xFFF7C024
set AT91C_TC0_RC    0xFFF7C01C
set AT91C_TC0_RA    0xFFF7C014
set AT91C_TC0_CMR   0xFFF7C004
# ========== Register definition for TC1 peripheral ========== 
set AT91C_TC1_IDR   0xFFF7C068
set AT91C_TC1_SR    0xFFF7C060
set AT91C_TC1_RB    0xFFF7C058
set AT91C_TC1_CV    0xFFF7C050
set AT91C_TC1_CCR   0xFFF7C040
set AT91C_TC1_IMR   0xFFF7C06C
set AT91C_TC1_IER   0xFFF7C064
set AT91C_TC1_RC    0xFFF7C05C
set AT91C_TC1_RA    0xFFF7C054
set AT91C_TC1_CMR   0xFFF7C044
# ========== Register definition for TC2 peripheral ========== 
set AT91C_TC2_IDR   0xFFF7C0A8
set AT91C_TC2_SR    0xFFF7C0A0
set AT91C_TC2_RB    0xFFF7C098
set AT91C_TC2_CV    0xFFF7C090
set AT91C_TC2_CCR   0xFFF7C080
set AT91C_TC2_IMR   0xFFF7C0AC
set AT91C_TC2_IER   0xFFF7C0A4
set AT91C_TC2_RC    0xFFF7C09C
set AT91C_TC2_RA    0xFFF7C094
set AT91C_TC2_CMR   0xFFF7C084
# ========== Register definition for TCB0 peripheral ========== 
set AT91C_TCB0_BCR  0xFFF7C0C0
set AT91C_TCB0_BMR  0xFFF7C0C4
# ========== Register definition for TCB1 peripheral ========== 
set AT91C_TCB1_BCR  0xFFF7C100
set AT91C_TCB1_BMR  0xFFF7C104
# ========== Register definition for TCB2 peripheral ========== 
set AT91C_TCB2_BMR  0xFFF7C144
set AT91C_TCB2_BCR  0xFFF7C140
# ========== Register definition for PDC_MCI0 peripheral ========== 
set AT91C_MCI0_TNCR 0xFFF8011C
set AT91C_MCI0_RNCR 0xFFF80114
set AT91C_MCI0_TCR  0xFFF8010C
set AT91C_MCI0_RCR  0xFFF80104
set AT91C_MCI0_PTCR 0xFFF80120
set AT91C_MCI0_TNPR 0xFFF80118
set AT91C_MCI0_RPR  0xFFF80100
set AT91C_MCI0_TPR  0xFFF80108
set AT91C_MCI0_RNPR 0xFFF80110
set AT91C_MCI0_PTSR 0xFFF80124
# ========== Register definition for MCI0 peripheral ========== 
set AT91C_MCI0_TDR  0xFFF80034
set AT91C_MCI0_CMDR 0xFFF80014
set AT91C_MCI0_IDR  0xFFF80048
set AT91C_MCI0_SR   0xFFF80040
set AT91C_MCI0_RDR  0xFFF80030
set AT91C_MCI0_VR   0xFFF800FC
set AT91C_MCI0_MR   0xFFF80004
set AT91C_MCI0_SDCR 0xFFF8000C
set AT91C_MCI0_IER  0xFFF80044
set AT91C_MCI0_IMR  0xFFF8004C
set AT91C_MCI0_CR   0xFFF80000
set AT91C_MCI0_DTOR 0xFFF80008
set AT91C_MCI0_ARGR 0xFFF80010
set AT91C_MCI0_BLKR 0xFFF80018
set AT91C_MCI0_RSPR 0xFFF80020
# ========== Register definition for PDC_MCI1 peripheral ========== 
set AT91C_MCI1_PTSR 0xFFF84124
set AT91C_MCI1_TNCR 0xFFF8411C
set AT91C_MCI1_RNCR 0xFFF84114
set AT91C_MCI1_TCR  0xFFF8410C
set AT91C_MCI1_RCR  0xFFF84104
set AT91C_MCI1_PTCR 0xFFF84120
set AT91C_MCI1_TNPR 0xFFF84118
set AT91C_MCI1_RNPR 0xFFF84110
set AT91C_MCI1_TPR  0xFFF84108
set AT91C_MCI1_RPR  0xFFF84100
# ========== Register definition for MCI1 peripheral ========== 
set AT91C_MCI1_CR   0xFFF84000
set AT91C_MCI1_VR   0xFFF840FC
set AT91C_MCI1_IMR  0xFFF8404C
set AT91C_MCI1_CMDR 0xFFF84014
set AT91C_MCI1_SDCR 0xFFF8400C
set AT91C_MCI1_MR   0xFFF84004
set AT91C_MCI1_RDR  0xFFF84030
set AT91C_MCI1_RSPR 0xFFF84020
set AT91C_MCI1_BLKR 0xFFF84018
set AT91C_MCI1_ARGR 0xFFF84010
set AT91C_MCI1_TDR  0xFFF84034
set AT91C_MCI1_IER  0xFFF84044
set AT91C_MCI1_DTOR 0xFFF84008
set AT91C_MCI1_SR   0xFFF84040
set AT91C_MCI1_IDR  0xFFF84048
# ========== Register definition for TWI peripheral ========== 
set AT91C_TWI_THR   0xFFF88034
set AT91C_TWI_IMR   0xFFF8802C
set AT91C_TWI_IER   0xFFF88024
set AT91C_TWI_IADR  0xFFF8800C
set AT91C_TWI_MMR   0xFFF88004
set AT91C_TWI_RHR   0xFFF88030
set AT91C_TWI_IDR   0xFFF88028
set AT91C_TWI_SR    0xFFF88020
set AT91C_TWI_CWGR  0xFFF88010
set AT91C_TWI_CR    0xFFF88000
# ========== Register definition for PDC_US0 peripheral ========== 
set AT91C_US0_PTSR  0xFFF8C124
set AT91C_US0_TNCR  0xFFF8C11C
set AT91C_US0_RNCR  0xFFF8C114
set AT91C_US0_TCR   0xFFF8C10C
set AT91C_US0_RCR   0xFFF8C104
set AT91C_US0_PTCR  0xFFF8C120
set AT91C_US0_TNPR  0xFFF8C118
set AT91C_US0_RNPR  0xFFF8C110
set AT91C_US0_TPR   0xFFF8C108
set AT91C_US0_RPR   0xFFF8C100
# ========== Register definition for US0 peripheral ========== 
set AT91C_US0_TTGR  0xFFF8C028
set AT91C_US0_BRGR  0xFFF8C020
set AT91C_US0_RHR   0xFFF8C018
set AT91C_US0_IMR   0xFFF8C010
set AT91C_US0_IER   0xFFF8C008
set AT91C_US0_RTOR  0xFFF8C024
set AT91C_US0_THR   0xFFF8C01C
set AT91C_US0_FIDI  0xFFF8C040
set AT91C_US0_CR    0xFFF8C000
set AT91C_US0_IF    0xFFF8C04C
set AT91C_US0_NER   0xFFF8C044
set AT91C_US0_MR    0xFFF8C004
set AT91C_US0_IDR   0xFFF8C00C
set AT91C_US0_CSR   0xFFF8C014
# ========== Register definition for PDC_US1 peripheral ========== 
set AT91C_US1_PTSR  0xFFF90124
set AT91C_US1_TNCR  0xFFF9011C
set AT91C_US1_RNCR  0xFFF90114
set AT91C_US1_TCR   0xFFF9010C
set AT91C_US1_RCR   0xFFF90104
set AT91C_US1_PTCR  0xFFF90120
set AT91C_US1_TNPR  0xFFF90118
set AT91C_US1_RNPR  0xFFF90110
set AT91C_US1_TPR   0xFFF90108
set AT91C_US1_RPR   0xFFF90100
# ========== Register definition for US1 peripheral ========== 
set AT91C_US1_IF    0xFFF9004C
set AT91C_US1_NER   0xFFF90044
set AT91C_US1_FIDI  0xFFF90040
set AT91C_US1_IMR   0xFFF90010
set AT91C_US1_IER   0xFFF90008
set AT91C_US1_CR    0xFFF90000
set AT91C_US1_MR    0xFFF90004
set AT91C_US1_IDR   0xFFF9000C
set AT91C_US1_CSR   0xFFF90014
set AT91C_US1_THR   0xFFF9001C
set AT91C_US1_RTOR  0xFFF90024
set AT91C_US1_RHR   0xFFF90018
set AT91C_US1_BRGR  0xFFF90020
set AT91C_US1_TTGR  0xFFF90028
# ========== Register definition for PDC_US2 peripheral ========== 
set AT91C_US2_PTCR  0xFFF94120
set AT91C_US2_TNPR  0xFFF94118
set AT91C_US2_RNPR  0xFFF94110
set AT91C_US2_TPR   0xFFF94108
set AT91C_US2_RPR   0xFFF94100
set AT91C_US2_PTSR  0xFFF94124
set AT91C_US2_TNCR  0xFFF9411C
set AT91C_US2_RNCR  0xFFF94114
set AT91C_US2_TCR   0xFFF9410C
set AT91C_US2_RCR   0xFFF94104
# ========== Register definition for US2 peripheral ========== 
set AT91C_US2_RTOR  0xFFF94024
set AT91C_US2_THR   0xFFF9401C
set AT91C_US2_CSR   0xFFF94014
set AT91C_US2_FIDI  0xFFF94040
set AT91C_US2_TTGR  0xFFF94028
set AT91C_US2_MR    0xFFF94004
set AT91C_US2_IDR   0xFFF9400C
set AT91C_US2_NER   0xFFF94044
set AT91C_US2_CR    0xFFF94000
set AT91C_US2_IER   0xFFF94008
set AT91C_US2_IMR   0xFFF94010
set AT91C_US2_RHR   0xFFF94018
set AT91C_US2_BRGR  0xFFF94020
set AT91C_US2_IF    0xFFF9404C
# ========== Register definition for PDC_SSC0 peripheral ========== 
set AT91C_SSC0_TCR  0xFFF9810C
set AT91C_SSC0_RCR  0xFFF98104
set AT91C_SSC0_PTCR 0xFFF98120
set AT91C_SSC0_TNPR 0xFFF98118
set AT91C_SSC0_RNPR 0xFFF98110
set AT91C_SSC0_TPR  0xFFF98108
set AT91C_SSC0_RPR  0xFFF98100
set AT91C_SSC0_PTSR 0xFFF98124
set AT91C_SSC0_RNCR 0xFFF98114
set AT91C_SSC0_TNCR 0xFFF9811C
# ========== Register definition for SSC0 peripheral ========== 
set AT91C_SSC0_IDR  0xFFF98048
set AT91C_SSC0_SR   0xFFF98040
set AT91C_SSC0_RSHR 0xFFF98030
set AT91C_SSC0_RHR  0xFFF98020
set AT91C_SSC0_TCMR 0xFFF98018
set AT91C_SSC0_RCMR 0xFFF98010
set AT91C_SSC0_CR   0xFFF98000
set AT91C_SSC0_IMR  0xFFF9804C
set AT91C_SSC0_IER  0xFFF98044
set AT91C_SSC0_TSHR 0xFFF98034
set AT91C_SSC0_THR  0xFFF98024
set AT91C_SSC0_TFMR 0xFFF9801C
set AT91C_SSC0_RFMR 0xFFF98014
set AT91C_SSC0_CMR  0xFFF98004
# ========== Register definition for PDC_SSC1 peripheral ========== 
set AT91C_SSC1_PTCR 0xFFF9C120
set AT91C_SSC1_TNPR 0xFFF9C118
set AT91C_SSC1_RNPR 0xFFF9C110
set AT91C_SSC1_TPR  0xFFF9C108
set AT91C_SSC1_RPR  0xFFF9C100
set AT91C_SSC1_PTSR 0xFFF9C124
set AT91C_SSC1_TNCR 0xFFF9C11C
set AT91C_SSC1_RNCR 0xFFF9C114
set AT91C_SSC1_TCR  0xFFF9C10C
set AT91C_SSC1_RCR  0xFFF9C104
# ========== Register definition for SSC1 peripheral ========== 
set AT91C_SSC1_IDR  0xFFF9C048
set AT91C_SSC1_SR   0xFFF9C040
set AT91C_SSC1_RSHR 0xFFF9C030
set AT91C_SSC1_RHR  0xFFF9C020
set AT91C_SSC1_TCMR 0xFFF9C018
set AT91C_SSC1_RCMR 0xFFF9C010
set AT91C_SSC1_CR   0xFFF9C000
set AT91C_SSC1_IMR  0xFFF9C04C
set AT91C_SSC1_IER  0xFFF9C044
set AT91C_SSC1_TSHR 0xFFF9C034
set AT91C_SSC1_THR  0xFFF9C024
set AT91C_SSC1_TFMR 0xFFF9C01C
set AT91C_SSC1_RFMR 0xFFF9C014
set AT91C_SSC1_CMR  0xFFF9C004
# ========== Register definition for PDC_AC97C peripheral ========== 
set AT91C_AC97C_PTSR 0xFFFA0124
set AT91C_AC97C_TNCR 0xFFFA011C
set AT91C_AC97C_RNCR 0xFFFA0114
set AT91C_AC97C_TCR 0xFFFA010C
set AT91C_AC97C_RCR 0xFFFA0104
set AT91C_AC97C_PTCR 0xFFFA0120
set AT91C_AC97C_TNPR 0xFFFA0118
set AT91C_AC97C_RNPR 0xFFFA0110
set AT91C_AC97C_TPR 0xFFFA0108
set AT91C_AC97C_RPR 0xFFFA0100
# ========== Register definition for AC97C peripheral ========== 
set AT91C_AC97C_VERSION 0xFFFA00FC
set AT91C_AC97C_IMR 0xFFFA005C
set AT91C_AC97C_IER 0xFFFA0054
set AT91C_AC97C_COMR 0xFFFA004C
set AT91C_AC97C_COTHR 0xFFFA0044
set AT91C_AC97C_OCA 0xFFFA0014
set AT91C_AC97C_IDR 0xFFFA0058
set AT91C_AC97C_CASR 0xFFFA0028
set AT91C_AC97C_CARHR 0xFFFA0020
set AT91C_AC97C_ICA 0xFFFA0010
set AT91C_AC97C_MR  0xFFFA0008
set AT91C_AC97C_CATHR 0xFFFA0024
set AT91C_AC97C_CAMR 0xFFFA002C
set AT91C_AC97C_CBTHR 0xFFFA0034
set AT91C_AC97C_CBMR 0xFFFA003C
set AT91C_AC97C_CBRHR 0xFFFA0030
set AT91C_AC97C_CBSR 0xFFFA0038
set AT91C_AC97C_CORHR 0xFFFA0040
set AT91C_AC97C_COSR 0xFFFA0048
set AT91C_AC97C_SR  0xFFFA0050
# ========== Register definition for PDC_SPI0 peripheral ========== 
set AT91C_SPI0_PTCR 0xFFFA4120
set AT91C_SPI0_TNPR 0xFFFA4118
set AT91C_SPI0_RNPR 0xFFFA4110
set AT91C_SPI0_TPR  0xFFFA4108
set AT91C_SPI0_RPR  0xFFFA4100
set AT91C_SPI0_PTSR 0xFFFA4124
set AT91C_SPI0_TNCR 0xFFFA411C
set AT91C_SPI0_RNCR 0xFFFA4114
set AT91C_SPI0_TCR  0xFFFA410C
set AT91C_SPI0_RCR  0xFFFA4104
# ========== Register definition for SPI0 peripheral ========== 
set AT91C_SPI0_SR   0xFFFA4010
set AT91C_SPI0_RDR  0xFFFA4008
set AT91C_SPI0_CR   0xFFFA4000
set AT91C_SPI0_MR   0xFFFA4004
set AT91C_SPI0_TDR  0xFFFA400C
set AT91C_SPI0_IER  0xFFFA4014
set AT91C_SPI0_IMR  0xFFFA401C
set AT91C_SPI0_CSR  0xFFFA4030
set AT91C_SPI0_IDR  0xFFFA4018
# ========== Register definition for PDC_SPI1 peripheral ========== 
set AT91C_SPI1_PTSR 0xFFFA8124
set AT91C_SPI1_TNCR 0xFFFA811C
set AT91C_SPI1_RNCR 0xFFFA8114
set AT91C_SPI1_TCR  0xFFFA810C
set AT91C_SPI1_RCR  0xFFFA8104
set AT91C_SPI1_PTCR 0xFFFA8120
set AT91C_SPI1_TNPR 0xFFFA8118
set AT91C_SPI1_RNPR 0xFFFA8110
set AT91C_SPI1_TPR  0xFFFA8108
set AT91C_SPI1_RPR  0xFFFA8100
# ========== Register definition for SPI1 peripheral ========== 
set AT91C_SPI1_CSR  0xFFFA8030
set AT91C_SPI1_IDR  0xFFFA8018
set AT91C_SPI1_SR   0xFFFA8010
set AT91C_SPI1_RDR  0xFFFA8008
set AT91C_SPI1_CR   0xFFFA8000
set AT91C_SPI1_IMR  0xFFFA801C
set AT91C_SPI1_IER  0xFFFA8014
set AT91C_SPI1_TDR  0xFFFA800C
set AT91C_SPI1_MR   0xFFFA8004
# ========== Register definition for CAN_MB0 peripheral ========== 
set AT91C_CAN_MB0_MDH 0xFFFAC218
set AT91C_CAN_MB0_MSR 0xFFFAC210
set AT91C_CAN_MB0_MID 0xFFFAC208
set AT91C_CAN_MB0_MMR 0xFFFAC200
set AT91C_CAN_MB0_MCR 0xFFFAC21C
set AT91C_CAN_MB0_MDL 0xFFFAC214
set AT91C_CAN_MB0_MFID 0xFFFAC20C
set AT91C_CAN_MB0_MAM 0xFFFAC204
# ========== Register definition for CAN_MB1 peripheral ========== 
set AT91C_CAN_MB1_MDH 0xFFFAC238
set AT91C_CAN_MB1_MSR 0xFFFAC230
set AT91C_CAN_MB1_MID 0xFFFAC228
set AT91C_CAN_MB1_MMR 0xFFFAC220
set AT91C_CAN_MB1_MCR 0xFFFAC23C
set AT91C_CAN_MB1_MDL 0xFFFAC234
set AT91C_CAN_MB1_MFID 0xFFFAC22C
set AT91C_CAN_MB1_MAM 0xFFFAC224
# ========== Register definition for CAN_MB2 peripheral ========== 
set AT91C_CAN_MB2_MDH 0xFFFAC258
set AT91C_CAN_MB2_MSR 0xFFFAC250
set AT91C_CAN_MB2_MID 0xFFFAC248
set AT91C_CAN_MB2_MMR 0xFFFAC240
set AT91C_CAN_MB2_MCR 0xFFFAC25C
set AT91C_CAN_MB2_MDL 0xFFFAC254
set AT91C_CAN_MB2_MFID 0xFFFAC24C
set AT91C_CAN_MB2_MAM 0xFFFAC244
# ========== Register definition for CAN_MB3 peripheral ========== 
set AT91C_CAN_MB3_MDH 0xFFFAC278
set AT91C_CAN_MB3_MSR 0xFFFAC270
set AT91C_CAN_MB3_MID 0xFFFAC268
set AT91C_CAN_MB3_MMR 0xFFFAC260
set AT91C_CAN_MB3_MCR 0xFFFAC27C
set AT91C_CAN_MB3_MDL 0xFFFAC274
set AT91C_CAN_MB3_MFID 0xFFFAC26C
set AT91C_CAN_MB3_MAM 0xFFFAC264
# ========== Register definition for CAN_MB4 peripheral ========== 
set AT91C_CAN_MB4_MID 0xFFFAC288
set AT91C_CAN_MB4_MMR 0xFFFAC280
set AT91C_CAN_MB4_MCR 0xFFFAC29C
set AT91C_CAN_MB4_MDL 0xFFFAC294
set AT91C_CAN_MB4_MFID 0xFFFAC28C
set AT91C_CAN_MB4_MAM 0xFFFAC284
set AT91C_CAN_MB4_MSR 0xFFFAC290
set AT91C_CAN_MB4_MDH 0xFFFAC298
# ========== Register definition for CAN_MB5 peripheral ========== 
set AT91C_CAN_MB5_MCR 0xFFFAC2BC
set AT91C_CAN_MB5_MDL 0xFFFAC2B4
set AT91C_CAN_MB5_MFID 0xFFFAC2AC
set AT91C_CAN_MB5_MAM 0xFFFAC2A4
set AT91C_CAN_MB5_MDH 0xFFFAC2B8
set AT91C_CAN_MB5_MSR 0xFFFAC2B0
set AT91C_CAN_MB5_MID 0xFFFAC2A8
set AT91C_CAN_MB5_MMR 0xFFFAC2A0
# ========== Register definition for CAN_MB6 peripheral ========== 
set AT91C_CAN_MB6_MCR 0xFFFAC2DC
set AT91C_CAN_MB6_MDL 0xFFFAC2D4
set AT91C_CAN_MB6_MFID 0xFFFAC2CC
set AT91C_CAN_MB6_MAM 0xFFFAC2C4
set AT91C_CAN_MB6_MDH 0xFFFAC2D8
set AT91C_CAN_MB6_MSR 0xFFFAC2D0
set AT91C_CAN_MB6_MID 0xFFFAC2C8
set AT91C_CAN_MB6_MMR 0xFFFAC2C0
# ========== Register definition for CAN_MB7 peripheral ========== 
set AT91C_CAN_MB7_MCR 0xFFFAC2FC
set AT91C_CAN_MB7_MDL 0xFFFAC2F4
set AT91C_CAN_MB7_MFID 0xFFFAC2EC
set AT91C_CAN_MB7_MAM 0xFFFAC2E4
set AT91C_CAN_MB7_MDH 0xFFFAC2F8
set AT91C_CAN_MB7_MSR 0xFFFAC2F0
set AT91C_CAN_MB7_MID 0xFFFAC2E8
set AT91C_CAN_MB7_MMR 0xFFFAC2E0
# ========== Register definition for CAN_MB8 peripheral ========== 
set AT91C_CAN_MB8_MCR 0xFFFAC31C
set AT91C_CAN_MB8_MDL 0xFFFAC314
set AT91C_CAN_MB8_MFID 0xFFFAC30C
set AT91C_CAN_MB8_MAM 0xFFFAC304
set AT91C_CAN_MB8_MMR 0xFFFAC300
set AT91C_CAN_MB8_MDH 0xFFFAC318
set AT91C_CAN_MB8_MSR 0xFFFAC310
set AT91C_CAN_MB8_MID 0xFFFAC308
# ========== Register definition for CAN_MB9 peripheral ========== 
set AT91C_CAN_MB9_MCR 0xFFFAC33C
set AT91C_CAN_MB9_MDL 0xFFFAC334
set AT91C_CAN_MB9_MFID 0xFFFAC32C
set AT91C_CAN_MB9_MAM 0xFFFAC324
set AT91C_CAN_MB9_MDH 0xFFFAC338
set AT91C_CAN_MB9_MSR 0xFFFAC330
set AT91C_CAN_MB9_MID 0xFFFAC328
set AT91C_CAN_MB9_MMR 0xFFFAC320
# ========== Register definition for CAN_MB10 peripheral ========== 
set AT91C_CAN_MB10_MCR 0xFFFAC35C
set AT91C_CAN_MB10_MDL 0xFFFAC354
set AT91C_CAN_MB10_MFID 0xFFFAC34C
set AT91C_CAN_MB10_MAM 0xFFFAC344
set AT91C_CAN_MB10_MDH 0xFFFAC358
set AT91C_CAN_MB10_MSR 0xFFFAC350
set AT91C_CAN_MB10_MID 0xFFFAC348
set AT91C_CAN_MB10_MMR 0xFFFAC340
# ========== Register definition for CAN_MB11 peripheral ========== 
set AT91C_CAN_MB11_MDH 0xFFFAC378
set AT91C_CAN_MB11_MSR 0xFFFAC370
set AT91C_CAN_MB11_MID 0xFFFAC368
set AT91C_CAN_MB11_MMR 0xFFFAC360
set AT91C_CAN_MB11_MCR 0xFFFAC37C
set AT91C_CAN_MB11_MDL 0xFFFAC374
set AT91C_CAN_MB11_MFID 0xFFFAC36C
set AT91C_CAN_MB11_MAM 0xFFFAC364
# ========== Register definition for CAN_MB12 peripheral ========== 
set AT91C_CAN_MB12_MDH 0xFFFAC398
set AT91C_CAN_MB12_MSR 0xFFFAC390
set AT91C_CAN_MB12_MID 0xFFFAC388
set AT91C_CAN_MB12_MMR 0xFFFAC380
set AT91C_CAN_MB12_MCR 0xFFFAC39C
set AT91C_CAN_MB12_MDL 0xFFFAC394
set AT91C_CAN_MB12_MFID 0xFFFAC38C
set AT91C_CAN_MB12_MAM 0xFFFAC384
# ========== Register definition for CAN_MB13 peripheral ========== 
set AT91C_CAN_MB13_MDH 0xFFFAC3B8
set AT91C_CAN_MB13_MSR 0xFFFAC3B0
set AT91C_CAN_MB13_MID 0xFFFAC3A8
set AT91C_CAN_MB13_MMR 0xFFFAC3A0
set AT91C_CAN_MB13_MCR 0xFFFAC3BC
set AT91C_CAN_MB13_MDL 0xFFFAC3B4
set AT91C_CAN_MB13_MFID 0xFFFAC3AC
set AT91C_CAN_MB13_MAM 0xFFFAC3A4
# ========== Register definition for CAN_MB14 peripheral ========== 
set AT91C_CAN_MB14_MDH 0xFFFAC3D8
set AT91C_CAN_MB14_MSR 0xFFFAC3D0
set AT91C_CAN_MB14_MID 0xFFFAC3C8
set AT91C_CAN_MB14_MMR 0xFFFAC3C0
set AT91C_CAN_MB14_MCR 0xFFFAC3DC
set AT91C_CAN_MB14_MDL 0xFFFAC3D4
set AT91C_CAN_MB14_MFID 0xFFFAC3CC
set AT91C_CAN_MB14_MAM 0xFFFAC3C4
# ========== Register definition for CAN_MB15 peripheral ========== 
set AT91C_CAN_MB15_MDH 0xFFFAC3F8
set AT91C_CAN_MB15_MSR 0xFFFAC3F0
set AT91C_CAN_MB15_MID 0xFFFAC3E8
set AT91C_CAN_MB15_MMR 0xFFFAC3E0
set AT91C_CAN_MB15_MCR 0xFFFAC3FC
set AT91C_CAN_MB15_MDL 0xFFFAC3F4
set AT91C_CAN_MB15_MFID 0xFFFAC3EC
set AT91C_CAN_MB15_MAM 0xFFFAC3E4
# ========== Register definition for CAN peripheral ========== 
set AT91C_CAN_TCR   0xFFFAC024
set AT91C_CAN_IDR   0xFFFAC008
set AT91C_CAN_MR    0xFFFAC000
set AT91C_CAN_VR    0xFFFAC0FC
set AT91C_CAN_IER   0xFFFAC004
set AT91C_CAN_IMR   0xFFFAC00C
set AT91C_CAN_BR    0xFFFAC014
set AT91C_CAN_TIMESTP 0xFFFAC01C
set AT91C_CAN_SR    0xFFFAC010
set AT91C_CAN_TIM   0xFFFAC018
set AT91C_CAN_ECR   0xFFFAC020
set AT91C_CAN_ACR   0xFFFAC028
# ========== Register definition for PWMC_CH0 peripheral ========== 
set AT91C_PWMC_CH0_Reserved 0xFFFB8214
set AT91C_PWMC_CH0_CCNTR 0xFFFB820C
set AT91C_PWMC_CH0_CDTYR 0xFFFB8204
set AT91C_PWMC_CH0_CUPDR 0xFFFB8210
set AT91C_PWMC_CH0_CPRDR 0xFFFB8208
set AT91C_PWMC_CH0_CMR 0xFFFB8200
# ========== Register definition for PWMC_CH1 peripheral ========== 
set AT91C_PWMC_CH1_Reserved 0xFFFB8234
set AT91C_PWMC_CH1_CCNTR 0xFFFB822C
set AT91C_PWMC_CH1_CDTYR 0xFFFB8224
set AT91C_PWMC_CH1_CUPDR 0xFFFB8230
set AT91C_PWMC_CH1_CPRDR 0xFFFB8228
set AT91C_PWMC_CH1_CMR 0xFFFB8220
# ========== Register definition for PWMC_CH2 peripheral ========== 
set AT91C_PWMC_CH2_Reserved 0xFFFB8254
set AT91C_PWMC_CH2_CCNTR 0xFFFB824C
set AT91C_PWMC_CH2_CDTYR 0xFFFB8244
set AT91C_PWMC_CH2_CUPDR 0xFFFB8250
set AT91C_PWMC_CH2_CPRDR 0xFFFB8248
set AT91C_PWMC_CH2_CMR 0xFFFB8240
# ========== Register definition for PWMC_CH3 peripheral ========== 
set AT91C_PWMC_CH3_CDTYR 0xFFFB8264
set AT91C_PWMC_CH3_CUPDR 0xFFFB8270
set AT91C_PWMC_CH3_CPRDR 0xFFFB8268
set AT91C_PWMC_CH3_CMR 0xFFFB8260
set AT91C_PWMC_CH3_Reserved 0xFFFB8274
set AT91C_PWMC_CH3_CCNTR 0xFFFB826C
# ========== Register definition for PWMC peripheral ========== 
set AT91C_PWMC_IMR  0xFFFB8018
set AT91C_PWMC_IER  0xFFFB8010
set AT91C_PWMC_MR   0xFFFB8000
set AT91C_PWMC_DIS  0xFFFB8008
set AT91C_PWMC_VR   0xFFFB80FC
set AT91C_PWMC_IDR  0xFFFB8014
set AT91C_PWMC_ISR  0xFFFB801C
set AT91C_PWMC_ENA  0xFFFB8004
set AT91C_PWMC_SR   0xFFFB800C
# ========== Register definition for MACB peripheral ========== 
set AT91C_MACB_RSR  0xFFFBC020
set AT91C_MACB_MAN  0xFFFBC034
set AT91C_MACB_ISR  0xFFFBC024
set AT91C_MACB_HRB  0xFFFBC090
set AT91C_MACB_MCF  0xFFFBC048
set AT91C_MACB_PTR  0xFFFBC038
set AT91C_MACB_IER  0xFFFBC028
set AT91C_MACB_SA2H 0xFFFBC0A4
set AT91C_MACB_HRT  0xFFFBC094
set AT91C_MACB_LCOL 0xFFFBC05C
set AT91C_MACB_FRO  0xFFFBC04C
set AT91C_MACB_PFR  0xFFFBC03C
set AT91C_MACB_NCFGR 0xFFFBC004
set AT91C_MACB_TID  0xFFFBC0B8
set AT91C_MACB_SA3L 0xFFFBC0A8
set AT91C_MACB_FCSE 0xFFFBC050
set AT91C_MACB_ECOL 0xFFFBC060
set AT91C_MACB_ROV  0xFFFBC070
set AT91C_MACB_NSR  0xFFFBC008
set AT91C_MACB_RBQP 0xFFFBC018
set AT91C_MACB_TPQ  0xFFFBC0BC
set AT91C_MACB_TUND 0xFFFBC064
set AT91C_MACB_RSE  0xFFFBC074
set AT91C_MACB_TBQP 0xFFFBC01C
set AT91C_MACB_ELE  0xFFFBC078
set AT91C_MACB_STE  0xFFFBC084
set AT91C_MACB_IDR  0xFFFBC02C
set AT91C_MACB_SA1L 0xFFFBC098
set AT91C_MACB_RLE  0xFFFBC088
set AT91C_MACB_IMR  0xFFFBC030
set AT91C_MACB_FTO  0xFFFBC040
set AT91C_MACB_SA3H 0xFFFBC0AC
set AT91C_MACB_SA1H 0xFFFBC09C
set AT91C_MACB_TPF  0xFFFBC08C
set AT91C_MACB_SCF  0xFFFBC044
set AT91C_MACB_ALE  0xFFFBC054
set AT91C_MACB_USRIO 0xFFFBC0C0
set AT91C_MACB_SA4L 0xFFFBC0B0
set AT91C_MACB_SA2L 0xFFFBC0A0
set AT91C_MACB_REV  0xFFFBC0FC
set AT91C_MACB_CSE  0xFFFBC068
set AT91C_MACB_DTF  0xFFFBC058
set AT91C_MACB_NCR  0xFFFBC000
set AT91C_MACB_WOL  0xFFFBC0C4
set AT91C_MACB_SA4H 0xFFFBC0B4
set AT91C_MACB_RRE  0xFFFBC06C
set AT91C_MACB_RJA  0xFFFBC07C
set AT91C_MACB_TSR  0xFFFBC014
set AT91C_MACB_USF  0xFFFBC080
# ========== Register definition for LCDC peripheral ========== 
set AT91C_LCDC_ITR  0x00700860
set AT91C_LCDC_TIM1 0x00700808
set AT91C_LCDC_BA1  0x00700000
set AT91C_LCDC_FIFO 0x00700814
set AT91C_LCDC_BA2  0x00700004
set AT91C_LCDC_FRMA2 0x00700014
set AT91C_LCDC_DP2_3 0x00700828
set AT91C_LCDC_MVAL 0x00700818
set AT91C_LCDC_FRMCFG 0x00700018
set AT91C_LCDC_LUT_ENTRY 0x00700C00
set AT91C_LCDC_PWRCON 0x0070083C
set AT91C_LCDC_DP5_7 0x0070082C
set AT91C_LCDC_DP1_2 0x0070081C
set AT91C_LCDC_IMR  0x00700850
set AT91C_LCDC_CTRSTCON 0x00700840
set AT91C_LCDC_DP3_4 0x00700830
set AT91C_LCDC_IRR  0x00700864
set AT91C_LCDC_ISR  0x00700854
set AT91C_LCDC_CTRSTVAL 0x00700844
set AT91C_LCDC_TIM2 0x0070080C
set AT91C_LCDC_ICR  0x00700858
set AT91C_LCDC_LCDFRCFG 0x00700810
set AT91C_LCDC_FRMP1 0x00700008
set AT91C_LCDC_DMACON 0x0070001C
set AT91C_LCDC_FRMP2 0x0070000C
set AT91C_LCDC_DP4_7 0x00700820
set AT91C_LCDC_DMA2DCFG 0x00700020
set AT91C_LCDC_FRMA1 0x00700010
set AT91C_LCDC_DP3_5 0x00700824
set AT91C_LCDC_DP4_5 0x00700834
set AT91C_LCDC_DP6_7 0x00700838
set AT91C_LCDC_IER  0x00700848
set AT91C_LCDC_LCDCON1 0x00700800
set AT91C_LCDC_GPR  0x0070085C
set AT91C_LCDC_IDR  0x0070084C
set AT91C_LCDC_LCDCON2 0x00700804
# ========== Register definition for DMA peripheral ========== 
set AT91C_DMA_CFG1h 0x0080009C
set AT91C_DMA_CFG0h 0x00800044
set AT91C_DMA_SGLREQSRCREG 0x00800378
set AT91C_DMA_SGR1  0x008000A0
set AT91C_DMA_SAR1  0x00800058
set AT91C_DMA_MASKBLOCK 0x00800318
set AT91C_DMA_RAWTFR 0x008002C0
set AT91C_DMA_LSTREQSRCREG 0x00800388
set AT91C_DMA_CLEARBLOCK 0x00800340
set AT91C_DMA_MASKERR 0x00800330
set AT91C_DMA_MASKSRCTRAN 0x00800320
set AT91C_DMA_STATUSTFR 0x008002E8
set AT91C_DMA_RAWDSTTRAN 0x008002D8
set AT91C_DMA_LLP1  0x00800068
set AT91C_DMA_SAR0  0x00800000
set AT91C_DMA_LLP0  0x00800010
set AT91C_DMA_SSTAT0 0x00800020
set AT91C_DMA_DMATESTREG 0x008003B0
set AT91C_DMA_CHENREG 0x008003A0
set AT91C_DMA_REQSRCREG 0x00800368
set AT91C_DMA_CLEARERR 0x00800358
set AT91C_DMA_CLEARSRCTRAN 0x00800348
set AT91C_DMA_MASKTFR 0x00800310
set AT91C_DMA_STATUSDSTTRAN 0x00800300
set AT91C_DMA_DSTATAR1 0x00800090
set AT91C_DMA_DSTAT1 0x00800080
set AT91C_DMA_SGR0  0x00800048
set AT91C_DMA_DSTATAR0 0x00800038
set AT91C_DMA_DSTAT0 0x00800028
set AT91C_DMA_REQDSTREG 0x00800370
set AT91C_DMA_DSR1  0x008000A8
set AT91C_DMA_DSR0  0x00800050
set AT91C_DMA_RAWBLOCK 0x008002C8
set AT91C_DMA_LSTREQDSTREG 0x00800390
set AT91C_DMA_SGLREQDSTREG 0x00800380
set AT91C_DMA_CLEARTFR 0x00800338
set AT91C_DMA_MASKDSTTRAN 0x00800328
set AT91C_DMA_CTL1l 0x00800070
set AT91C_DMA_DAR1  0x00800060
set AT91C_DMA_RAWSRCTRAN 0x008002D0
set AT91C_DMA_RAWERR 0x008002E0
set AT91C_DMA_STATUSBLOCK 0x008002F0
set AT91C_DMA_CTL0l 0x00800018
set AT91C_DMA_DAR0  0x00800008
set AT91C_DMA_CTL1h 0x00800074
set AT91C_DMA_CTL0h 0x0080001C
set AT91C_DMA_VERSIONID 0x008003B8
set AT91C_DMA_DMAIDREG 0x008003A8
set AT91C_DMA_DMACFGREG 0x00800398
set AT91C_DMA_STATUSINT 0x00800360
set AT91C_DMA_CLEARDSTTRAN 0x00800350
set AT91C_DMA_SSTAT1 0x00800078
set AT91C_DMA_SSTATAR1 0x00800088
set AT91C_DMA_CFG1l 0x00800098
set AT91C_DMA_STATUSSRCTRAN 0x008002F8
set AT91C_DMA_STATUSERR 0x00800308
set AT91C_DMA_SSTATAR0 0x00800030
set AT91C_DMA_CFG0l 0x00800040
# ========== Register definition for UDP peripheral ========== 
set AT91C_UDP_RSTEP 0xFFF78028
set AT91C_UDP_ICR   0xFFF78020
set AT91C_UDP_IMR   0xFFF78018
set AT91C_UDP_IER   0xFFF78010
set AT91C_UDP_FADDR 0xFFF78008
set AT91C_UDP_TXVC  0xFFF78074
set AT91C_UDP_ISR   0xFFF7801C
set AT91C_UDP_FDR   0xFFF78050
set AT91C_UDP_NUM   0xFFF78000
set AT91C_UDP_CSR   0xFFF78030
set AT91C_UDP_GLBSTATE 0xFFF78004
set AT91C_UDP_IDR   0xFFF78014
# ========== Register definition for UHP peripheral ========== 
set AT91C_UHP_HcBulkHeadED 0x00A00028
set AT91C_UHP_HcFmNumber 0x00A0003C
set AT91C_UHP_HcFmInterval 0x00A00034
set AT91C_UHP_HcBulkCurrentED 0x00A0002C
set AT91C_UHP_HcRhStatus 0x00A00050
set AT91C_UHP_HcRhDescriptorA 0x00A00048
set AT91C_UHP_HcPeriodicStart 0x00A00040
set AT91C_UHP_HcFmRemaining 0x00A00038
set AT91C_UHP_HcBulkDoneHead 0x00A00030
set AT91C_UHP_HcRevision 0x00A00000
set AT91C_UHP_HcRhPortStatus 0x00A00054
set AT91C_UHP_HcRhDescriptorB 0x00A0004C
set AT91C_UHP_HcLSThreshold 0x00A00044
set AT91C_UHP_HcControl 0x00A00004
set AT91C_UHP_HcInterruptStatus 0x00A0000C
set AT91C_UHP_HcInterruptDisable 0x00A00014
set AT91C_UHP_HcCommandStatus 0x00A00008
set AT91C_UHP_HcInterruptEnable 0x00A00010
set AT91C_UHP_HcHCCA 0x00A00018
set AT91C_UHP_HcControlHeadED 0x00A00020
set AT91C_UHP_HcPeriodCurrentED 0x00A0001C
set AT91C_UHP_HcControlCurrentED 0x00A00024
# ========== Register definition for TBOX peripheral ========== 
set AT91C_TBOX_GPSSIGQB 0x70000BB4
set AT91C_TBOX_PIOC 0x70000944
set AT91C_TBOX_PIOEENABLEFORCE 0x70000934
set AT91C_TBOX_PWM1 0x70000A08
set AT91C_TBOX_PIOD 0x70000948
set AT91C_TBOX_PIOAPUN 0x70000900
set AT91C_TBOX_STOPAPBSPY 0x70000A1C
set AT91C_TBOX_PWM2 0x70000A0C
set AT91C_TBOX_GPSACQDATA 0x70000B0C
set AT91C_TBOX_MAC  0x70000A10
set AT91C_TBOX_GPSDUMPRES 0x70000BC0
set AT91C_TBOX_GPSSYNCHRO 0x70000B00
set AT91C_TBOX_PIOEPUN 0x70000910
set AT91C_TBOX_GPSSIGIA 0x70000BA4
set AT91C_TBOX_PIOCENABLEFORCE 0x70000924
set AT91C_TBOX_PIOAENABLEFORCE 0x70000914
set AT91C_TBOX_GPSSIGQA 0x70000BA8
set AT91C_TBOX_PIOEFORCEVALUE 0x70000938
set AT91C_TBOX_PIOCFORCEVALUE 0x70000928
set AT91C_TBOX_PIOA 0x7000093C
set AT91C_TBOX_PIOE 0x7000094C
set AT91C_TBOX_AC97START 0x70000A00
set AT91C_TBOX_PWMSTART 0x70000A04
set AT91C_TBOX_USBDEV 0x70000A14
set AT91C_TBOX_GPSRAND 0x70000B04
set AT91C_TBOX_KBD  0x70000A18
set AT91C_TBOX_GPSACQSTATUS 0x70000B08
set AT91C_TBOX_PIOBPUN 0x70000904
set AT91C_TBOX_SHMCTRL 0x70000000
set AT91C_TBOX_PIOAFORCEVALUE 0x70000918
set AT91C_TBOX_PIOCPUN 0x70000908
set AT91C_TBOX_DMAEXTREQ 0x70000810
set AT91C_TBOX_PIODPUN 0x7000090C
set AT91C_TBOX_PIOBENABLEFORCE 0x7000091C
set AT91C_TBOX_PIODENABLEFORCE 0x7000092C
set AT91C_TBOX_GPSSIGIB 0x70000BB0
set AT91C_TBOX_GPSSIGFILE 0x70000BA0
set AT91C_TBOX_PIOBFORCEVALUE 0x70000920
set AT91C_TBOX_PIODFORCEVALUE 0x70000930
set AT91C_TBOX_PIOB 0x70000940
# ========== Register definition for HECC0 peripheral ========== 
set AT91C_HECC0_NPR 0xFFFFE010
set AT91C_HECC0_SR  0xFFFFE008
set AT91C_HECC0_CR  0xFFFFE000
set AT91C_HECC0_VR  0xFFFFE0FC
set AT91C_HECC0_PR  0xFFFFE00C
set AT91C_HECC0_MR  0xFFFFE004
# ========== Register definition for HECC1 peripheral ========== 
set AT91C_HECC1_PR  0xFFFFE60C
set AT91C_HECC1_MR  0xFFFFE604
set AT91C_HECC1_NPR 0xFFFFE610
set AT91C_HECC1_SR  0xFFFFE608
set AT91C_HECC1_CR  0xFFFFE600
set AT91C_HECC1_VR  0xFFFFE6FC
# ========== Register definition for HISI peripheral ========== 
set AT91C_HISI_IDR  0xFFFC4010
set AT91C_HISI_SR   0xFFFC4008
set AT91C_HISI_CR1  0xFFFC4000
set AT91C_HISI_CDBA 0xFFFC402C
set AT91C_HISI_PDECF 0xFFFC4024
set AT91C_HISI_IMR  0xFFFC4014
set AT91C_HISI_IER  0xFFFC400C
set AT91C_HISI_R2YSET2 0xFFFC4040
set AT91C_HISI_PSIZE 0xFFFC4020
set AT91C_HISI_PFBD 0xFFFC4028
set AT91C_HISI_Y2RSET0 0xFFFC4030
set AT91C_HISI_R2YSET0 0xFFFC4038
set AT91C_HISI_CR2  0xFFFC4004
set AT91C_HISI_Y2RSET1 0xFFFC4034
set AT91C_HISI_R2YSET1 0xFFFC403C

# *****************************************************************************
#               BASE ADDRESS DEFINITIONS FOR AT91SAM9263
# *****************************************************************************
set AT91C_BASE_SYS       0xFFFFE000
set AT91C_BASE_EBI0      0xFFFFE200
set AT91C_BASE_SDRAMC0   0xFFFFE200
set AT91C_BASE_SMC0      0xFFFFE400
set AT91C_BASE_EBI1      0xFFFFE800
set AT91C_BASE_SDRAMC1   0xFFFFE800
set AT91C_BASE_SMC1      0xFFFFEA00
set AT91C_BASE_MATRIX    0xFFFFEC00
set AT91C_BASE_CCFG      0xFFFFED10
set AT91C_BASE_PDC_DBGU  0xFFFFEF00
set AT91C_BASE_DBGU      0xFFFFEE00
set AT91C_BASE_AIC       0xFFFFF000
set AT91C_BASE_PIOA      0xFFFFF200
set AT91C_BASE_PIOB      0xFFFFF400
set AT91C_BASE_PIOC      0xFFFFF600
set AT91C_BASE_PIOD      0xFFFFF800
set AT91C_BASE_PIOE      0xFFFFFA00
set AT91C_BASE_CKGR      0xFFFFFC20
set AT91C_BASE_PMC       0xFFFFFC00
set AT91C_BASE_RSTC      0xFFFFFD00
set AT91C_BASE_SHDWC     0xFFFFFD10
set AT91C_BASE_RTTC0     0xFFFFFD20
set AT91C_BASE_RTTC1     0xFFFFFD50
set AT91C_BASE_PITC      0xFFFFFD30
set AT91C_BASE_WDTC      0xFFFFFD40
set AT91C_BASE_TC0       0xFFF7C000
set AT91C_BASE_TC1       0xFFF7C040
set AT91C_BASE_TC2       0xFFF7C080
set AT91C_BASE_TCB0      0xFFF7C000
set AT91C_BASE_TCB1      0xFFF7C040
set AT91C_BASE_TCB2      0xFFF7C080
set AT91C_BASE_PDC_MCI0  0xFFF80100
set AT91C_BASE_MCI0      0xFFF80000
set AT91C_BASE_PDC_MCI1  0xFFF84100
set AT91C_BASE_MCI1      0xFFF84000
set AT91C_BASE_TWI       0xFFF88000
set AT91C_BASE_PDC_US0   0xFFF8C100
set AT91C_BASE_US0       0xFFF8C000
set AT91C_BASE_PDC_US1   0xFFF90100
set AT91C_BASE_US1       0xFFF90000
set AT91C_BASE_PDC_US2   0xFFF94100
set AT91C_BASE_US2       0xFFF94000
set AT91C_BASE_PDC_SSC0  0xFFF98100
set AT91C_BASE_SSC0      0xFFF98000
set AT91C_BASE_PDC_SSC1  0xFFF9C100
set AT91C_BASE_SSC1      0xFFF9C000
set AT91C_BASE_PDC_AC97C 0xFFFA0100
set AT91C_BASE_AC97C     0xFFFA0000
set AT91C_BASE_PDC_SPI0  0xFFFA4100
set AT91C_BASE_SPI0      0xFFFA4000
set AT91C_BASE_PDC_SPI1  0xFFFA8100
set AT91C_BASE_SPI1      0xFFFA8000
set AT91C_BASE_CAN_MB0   0xFFFAC200
set AT91C_BASE_CAN_MB1   0xFFFAC220
set AT91C_BASE_CAN_MB2   0xFFFAC240
set AT91C_BASE_CAN_MB3   0xFFFAC260
set AT91C_BASE_CAN_MB4   0xFFFAC280
set AT91C_BASE_CAN_MB5   0xFFFAC2A0
set AT91C_BASE_CAN_MB6   0xFFFAC2C0
set AT91C_BASE_CAN_MB7   0xFFFAC2E0
set AT91C_BASE_CAN_MB8   0xFFFAC300
set AT91C_BASE_CAN_MB9   0xFFFAC320
set AT91C_BASE_CAN_MB10  0xFFFAC340
set AT91C_BASE_CAN_MB11  0xFFFAC360
set AT91C_BASE_CAN_MB12  0xFFFAC380
set AT91C_BASE_CAN_MB13  0xFFFAC3A0
set AT91C_BASE_CAN_MB14  0xFFFAC3C0
set AT91C_BASE_CAN_MB15  0xFFFAC3E0
set AT91C_BASE_CAN       0xFFFAC000
set AT91C_BASE_PWMC_CH0  0xFFFB8200
set AT91C_BASE_PWMC_CH1  0xFFFB8220
set AT91C_BASE_PWMC_CH2  0xFFFB8240
set AT91C_BASE_PWMC_CH3  0xFFFB8260
set AT91C_BASE_PWMC      0xFFFB8000
set AT91C_BASE_MACB      0xFFFBC000
set AT91C_BASE_LCDC      0x00700000
set AT91C_BASE_DMA       0x00800000
set AT91C_BASE_UDP       0xFFF78000
set AT91C_BASE_UHP       0x00A00000
set AT91C_BASE_TBOX      0x70000000
set AT91C_BASE_HECC0     0xFFFFE000
set AT91C_BASE_HECC1     0xFFFFE600
set AT91C_BASE_HISI      0xFFFC4000

# *****************************************************************************
#               PERIPHERAL ID DEFINITIONS FOR AT91SAM9263
# *****************************************************************************
set AT91C_ID_FIQ     0
set AT91C_ID_SYS     1
set AT91C_ID_PIOA    2
set AT91C_ID_PIOB    3
set AT91C_ID_PIOCDE  4
set AT91C_ID_US0     7
set AT91C_ID_US1     8
set AT91C_ID_US2     9
set AT91C_ID_MCI0   10
set AT91C_ID_MCI1   11
set AT91C_ID_CAN    12
set AT91C_ID_TWI    13
set AT91C_ID_SPI0   14
set AT91C_ID_SPI1   15
set AT91C_ID_SSC0   16
set AT91C_ID_SSC1   17
set AT91C_ID_AC97C  18
set AT91C_ID_TC012  19
set AT91C_ID_PWMC   20
set AT91C_ID_EMAC   21
set AT91C_ID_UDP    24
set AT91C_ID_HISI   25
set AT91C_ID_LCDC   26
set AT91C_ID_DMA    27
set AT91C_ID_UHP    29
set AT91C_ID_IRQ0   30
set AT91C_ID_IRQ1   31

# *****************************************************************************
#               PIO DEFINITIONS FOR AT91SAM9263
# *****************************************************************************
set AT91C_PIO_PA0        [expr 1 <<  0 ]
set AT91C_PA0_MCI0_DA0 $AT91C_PIO_PA0
set AT91C_PA0_SPI0_MISO $AT91C_PIO_PA0
set AT91C_PIO_PA1        [expr 1 <<  1 ]
set AT91C_PA1_MCI0_CDA $AT91C_PIO_PA1
set AT91C_PA1_SPI0_MOSI $AT91C_PIO_PA1
set AT91C_PIO_PA10       [expr 1 << 10 ]
set AT91C_PA10_MCI1_DA2 $AT91C_PIO_PA10
set AT91C_PIO_PA11       [expr 1 << 11 ]
set AT91C_PA11_MCI1_DA3 $AT91C_PIO_PA11
set AT91C_PIO_PA12       [expr 1 << 12 ]
set AT91C_PA12_MCI0_CK  $AT91C_PIO_PA12
set AT91C_PIO_PA13       [expr 1 << 13 ]
set AT91C_PA13_CANTX    $AT91C_PIO_PA13
set AT91C_PA13_PCK0     $AT91C_PIO_PA13
set AT91C_PIO_PA14       [expr 1 << 14 ]
set AT91C_PA14_CANRX    $AT91C_PIO_PA14
set AT91C_PA14_IRQ0     $AT91C_PIO_PA14
set AT91C_PIO_PA15       [expr 1 << 15 ]
set AT91C_PA15_TCLK2    $AT91C_PIO_PA15
set AT91C_PA15_IRQ1     $AT91C_PIO_PA15
set AT91C_PIO_PA16       [expr 1 << 16 ]
set AT91C_PA16_MCI0_CDB $AT91C_PIO_PA16
set AT91C_PA16_EBI1_D16 $AT91C_PIO_PA16
set AT91C_PIO_PA17       [expr 1 << 17 ]
set AT91C_PA17_MCI0_DB0 $AT91C_PIO_PA17
set AT91C_PA17_EBI1_D17 $AT91C_PIO_PA17
set AT91C_PIO_PA18       [expr 1 << 18 ]
set AT91C_PA18_MCI0_DB1 $AT91C_PIO_PA18
set AT91C_PA18_EBI1_D18 $AT91C_PIO_PA18
set AT91C_PIO_PA19       [expr 1 << 19 ]
set AT91C_PA19_MCI0_DB2 $AT91C_PIO_PA19
set AT91C_PA19_EBI1_D19 $AT91C_PIO_PA19
set AT91C_PIO_PA2        [expr 1 <<  2 ]
set AT91C_PA2_UNCONNECTED_PA2_A $AT91C_PIO_PA2
set AT91C_PA2_SPI0_SPCK $AT91C_PIO_PA2
set AT91C_PIO_PA20       [expr 1 << 20 ]
set AT91C_PA20_MCI0_DB3 $AT91C_PIO_PA20
set AT91C_PA20_EBI1_D20 $AT91C_PIO_PA20
set AT91C_PIO_PA21       [expr 1 << 21 ]
set AT91C_PA21_MCI1_CDB $AT91C_PIO_PA21
set AT91C_PA21_EBI1_D21 $AT91C_PIO_PA21
set AT91C_PIO_PA22       [expr 1 << 22 ]
set AT91C_PA22_MCI1_DB0 $AT91C_PIO_PA22
set AT91C_PA22_EBI1_D22 $AT91C_PIO_PA22
set AT91C_PIO_PA23       [expr 1 << 23 ]
set AT91C_PA23_MCI1_DB1 $AT91C_PIO_PA23
set AT91C_PA23_EBI1_D23 $AT91C_PIO_PA23
set AT91C_PIO_PA24       [expr 1 << 24 ]
set AT91C_PA24_MCI1_DB2 $AT91C_PIO_PA24
set AT91C_PA24_EBI1_D24 $AT91C_PIO_PA24
set AT91C_PIO_PA25       [expr 1 << 25 ]
set AT91C_PA25_MCI1_DB3 $AT91C_PIO_PA25
set AT91C_PA25_EBI1_D25 $AT91C_PIO_PA25
set AT91C_PIO_PA26       [expr 1 << 26 ]
set AT91C_PA26_TXD0     $AT91C_PIO_PA26
set AT91C_PA26_EBI1_D26 $AT91C_PIO_PA26
set AT91C_PIO_PA27       [expr 1 << 27 ]
set AT91C_PA27_RXD0     $AT91C_PIO_PA27
set AT91C_PA27_EBI1_D27 $AT91C_PIO_PA27
set AT91C_PIO_PA28       [expr 1 << 28 ]
set AT91C_PA28_RTS0     $AT91C_PIO_PA28
set AT91C_PA28_EBI1_D28 $AT91C_PIO_PA28
set AT91C_PIO_PA29       [expr 1 << 29 ]
set AT91C_PA29_CTS0     $AT91C_PIO_PA29
set AT91C_PA29_EBI1_D29 $AT91C_PIO_PA29
set AT91C_PIO_PA3        [expr 1 <<  3 ]
set AT91C_PA3_MCI0_DA1 $AT91C_PIO_PA3
set AT91C_PA3_SPI0_NPCS1 $AT91C_PIO_PA3
set AT91C_PIO_PA30       [expr 1 << 30 ]
set AT91C_PA30_SCK0     $AT91C_PIO_PA30
set AT91C_PA30_EBI1_D30 $AT91C_PIO_PA30
set AT91C_PIO_PA31       [expr 1 << 31 ]
set AT91C_PA31_DMARQ0   $AT91C_PIO_PA31
set AT91C_PA31_EBI1_D31 $AT91C_PIO_PA31
set AT91C_PIO_PA4        [expr 1 <<  4 ]
set AT91C_PA4_MCI0_DA2 $AT91C_PIO_PA4
set AT91C_PA4_SPI0_NPCS2A $AT91C_PIO_PA4
set AT91C_PIO_PA5        [expr 1 <<  5 ]
set AT91C_PA5_MCI0_DA3 $AT91C_PIO_PA5
set AT91C_PA5_SPI0_NPCS0 $AT91C_PIO_PA5
set AT91C_PIO_PA6        [expr 1 <<  6 ]
set AT91C_PA6_MCI1_CK  $AT91C_PIO_PA6
set AT91C_PA6_PCK2     $AT91C_PIO_PA6
set AT91C_PIO_PA7        [expr 1 <<  7 ]
set AT91C_PA7_MCI1_CDA $AT91C_PIO_PA7
set AT91C_PIO_PA8        [expr 1 <<  8 ]
set AT91C_PA8_MCI1_DA0 $AT91C_PIO_PA8
set AT91C_PIO_PA9        [expr 1 <<  9 ]
set AT91C_PA9_MCI1_DA1 $AT91C_PIO_PA9
set AT91C_PIO_PB0        [expr 1 <<  0 ]
set AT91C_PB0_AC97FS   $AT91C_PIO_PB0
set AT91C_PB0_TF0      $AT91C_PIO_PB0
set AT91C_PIO_PB1        [expr 1 <<  1 ]
set AT91C_PB1_AC97CK   $AT91C_PIO_PB1
set AT91C_PB1_TK0      $AT91C_PIO_PB1
set AT91C_PIO_PB10       [expr 1 << 10 ]
set AT91C_PB10_RK1      $AT91C_PIO_PB10
set AT91C_PB10_PCK1     $AT91C_PIO_PB10
set AT91C_PIO_PB11       [expr 1 << 11 ]
set AT91C_PB11_RF1      $AT91C_PIO_PB11
set AT91C_PB11_SPI0_NPCS3B $AT91C_PIO_PB11
set AT91C_PIO_PB12       [expr 1 << 12 ]
set AT91C_PB12_SPI1_MISO $AT91C_PIO_PB12
set AT91C_PIO_PB13       [expr 1 << 13 ]
set AT91C_PB13_SPI1_MOSI $AT91C_PIO_PB13
set AT91C_PIO_PB14       [expr 1 << 14 ]
set AT91C_PB14_SPI1_SPCK $AT91C_PIO_PB14
set AT91C_PIO_PB15       [expr 1 << 15 ]
set AT91C_PB15_SPI1_NPCS0 $AT91C_PIO_PB15
set AT91C_PIO_PB16       [expr 1 << 16 ]
set AT91C_PB16_SPI1_NPCS1 $AT91C_PIO_PB16
set AT91C_PB16_PCK1     $AT91C_PIO_PB16
set AT91C_PIO_PB17       [expr 1 << 17 ]
set AT91C_PB17_SPI1_NPCS2B $AT91C_PIO_PB17
set AT91C_PB17_TIOA2    $AT91C_PIO_PB17
set AT91C_PIO_PB18       [expr 1 << 18 ]
set AT91C_PB18_SPI1_NPCS3B $AT91C_PIO_PB18
set AT91C_PB18_TIOB2    $AT91C_PIO_PB18
set AT91C_PIO_PB19       [expr 1 << 19 ]
set AT91C_PIO_PB2        [expr 1 <<  2 ]
set AT91C_PB2_AC97TX   $AT91C_PIO_PB2
set AT91C_PB2_TD0      $AT91C_PIO_PB2
set AT91C_PIO_PB20       [expr 1 << 20 ]
set AT91C_PIO_PB21       [expr 1 << 21 ]
set AT91C_PIO_PB22       [expr 1 << 22 ]
set AT91C_PIO_PB23       [expr 1 << 23 ]
set AT91C_PIO_PB24       [expr 1 << 24 ]
set AT91C_PB24_UNCONNECTED_PB24_A $AT91C_PIO_PB24
set AT91C_PB24_DMARQ3   $AT91C_PIO_PB24
set AT91C_PIO_PB25       [expr 1 << 25 ]
set AT91C_PIO_PB26       [expr 1 << 26 ]
set AT91C_PIO_PB27       [expr 1 << 27 ]
set AT91C_PB27_UNCONNECTED_PB27_A $AT91C_PIO_PB27
set AT91C_PB27_PWM2     $AT91C_PIO_PB27
set AT91C_PIO_PB28       [expr 1 << 28 ]
set AT91C_PB28_UNCONNECTED_PB28_A $AT91C_PIO_PB28
set AT91C_PB28_TCLK0    $AT91C_PIO_PB28
set AT91C_PIO_PB29       [expr 1 << 29 ]
set AT91C_PB29_UNCONNECTED_PB29_A $AT91C_PIO_PB29
set AT91C_PB29_PWM3     $AT91C_PIO_PB29
set AT91C_PIO_PB3        [expr 1 <<  3 ]
set AT91C_PB3_AC97RX   $AT91C_PIO_PB3
set AT91C_PB3_RD0      $AT91C_PIO_PB3
set AT91C_PIO_PB30       [expr 1 << 30 ]
set AT91C_PIO_PB31       [expr 1 << 31 ]
set AT91C_PIO_PB4        [expr 1 <<  4 ]
set AT91C_PB4_TWD      $AT91C_PIO_PB4
set AT91C_PB4_RK0      $AT91C_PIO_PB4
set AT91C_PIO_PB5        [expr 1 <<  5 ]
set AT91C_PB5_TWCK     $AT91C_PIO_PB5
set AT91C_PB5_RF0      $AT91C_PIO_PB5
set AT91C_PIO_PB6        [expr 1 <<  6 ]
set AT91C_PB6_TF1      $AT91C_PIO_PB6
set AT91C_PB6_DMARQ1   $AT91C_PIO_PB6
set AT91C_PIO_PB7        [expr 1 <<  7 ]
set AT91C_PB7_TK1      $AT91C_PIO_PB7
set AT91C_PB7_PWM0     $AT91C_PIO_PB7
set AT91C_PIO_PB8        [expr 1 <<  8 ]
set AT91C_PB8_TD1      $AT91C_PIO_PB8
set AT91C_PB8_PWM1     $AT91C_PIO_PB8
set AT91C_PIO_PB9        [expr 1 <<  9 ]
set AT91C_PB9_RD1      $AT91C_PIO_PB9
set AT91C_PB9_LCDCC    $AT91C_PIO_PB9
set AT91C_PIO_PC0        [expr 1 <<  0 ]
set AT91C_PC0_LCDVSYNC $AT91C_PIO_PC0
set AT91C_PIO_PC1        [expr 1 <<  1 ]
set AT91C_PC1_LCDHSYNC $AT91C_PIO_PC1
set AT91C_PIO_PC10       [expr 1 << 10 ]
set AT91C_PC10_LCDD6    $AT91C_PIO_PC10
set AT91C_PC10_LCDD11B  $AT91C_PIO_PC10
set AT91C_PIO_PC11       [expr 1 << 11 ]
set AT91C_PC11_LCDD7    $AT91C_PIO_PC11
set AT91C_PC11_LCDD12B  $AT91C_PIO_PC11
set AT91C_PIO_PC12       [expr 1 << 12 ]
set AT91C_PC12_LCDD8    $AT91C_PIO_PC12
set AT91C_PC12_LCDD13B  $AT91C_PIO_PC12
set AT91C_PIO_PC13       [expr 1 << 13 ]
set AT91C_PC13_LCDD9    $AT91C_PIO_PC13
set AT91C_PC13_LCDD14B  $AT91C_PIO_PC13
set AT91C_PIO_PC14       [expr 1 << 14 ]
set AT91C_PC14_LCDD10   $AT91C_PIO_PC14
set AT91C_PC14_LCDD15B  $AT91C_PIO_PC14
set AT91C_PIO_PC15       [expr 1 << 15 ]
set AT91C_PC15_LCDD11   $AT91C_PIO_PC15
set AT91C_PC15_LCDD19B  $AT91C_PIO_PC15
set AT91C_PIO_PC16       [expr 1 << 16 ]
set AT91C_PC16_LCDD12   $AT91C_PIO_PC16
set AT91C_PC16_LCDD20B  $AT91C_PIO_PC16
set AT91C_PIO_PC17       [expr 1 << 17 ]
set AT91C_PC17_LCDD13   $AT91C_PIO_PC17
set AT91C_PC17_LCDD21B  $AT91C_PIO_PC17
set AT91C_PIO_PC18       [expr 1 << 18 ]
set AT91C_PC18_LCDD14   $AT91C_PIO_PC18
set AT91C_PC18_LCDD22B  $AT91C_PIO_PC18
set AT91C_PIO_PC19       [expr 1 << 19 ]
set AT91C_PC19_LCDD15   $AT91C_PIO_PC19
set AT91C_PC19_LCDD23B  $AT91C_PIO_PC19
set AT91C_PIO_PC2        [expr 1 <<  2 ]
set AT91C_PC2_LCDDOTCK $AT91C_PIO_PC2
set AT91C_PIO_PC20       [expr 1 << 20 ]
set AT91C_PC20_LCDD16   $AT91C_PIO_PC20
set AT91C_PC20_ETX2     $AT91C_PIO_PC20
set AT91C_PIO_PC21       [expr 1 << 21 ]
set AT91C_PC21_LCDD17   $AT91C_PIO_PC21
set AT91C_PC21_ETX3     $AT91C_PIO_PC21
set AT91C_PIO_PC22       [expr 1 << 22 ]
set AT91C_PC22_LCDD18   $AT91C_PIO_PC22
set AT91C_PC22_ERX2     $AT91C_PIO_PC22
set AT91C_PIO_PC23       [expr 1 << 23 ]
set AT91C_PC23_LCDD19   $AT91C_PIO_PC23
set AT91C_PC23_ERX3     $AT91C_PIO_PC23
set AT91C_PIO_PC24       [expr 1 << 24 ]
set AT91C_PC24_LCDD20   $AT91C_PIO_PC24
set AT91C_PC24_ETXER    $AT91C_PIO_PC24
set AT91C_PIO_PC25       [expr 1 << 25 ]
set AT91C_PC25_LCDD21   $AT91C_PIO_PC25
set AT91C_PC25_ERXDV    $AT91C_PIO_PC25
set AT91C_PIO_PC26       [expr 1 << 26 ]
set AT91C_PC26_LCDD22   $AT91C_PIO_PC26
set AT91C_PC26_ECOL     $AT91C_PIO_PC26
set AT91C_PIO_PC27       [expr 1 << 27 ]
set AT91C_PC27_LCDD23   $AT91C_PIO_PC27
set AT91C_PC27_ERXCK    $AT91C_PIO_PC27
set AT91C_PIO_PC28       [expr 1 << 28 ]
set AT91C_PC28_PWM0     $AT91C_PIO_PC28
set AT91C_PC28_TCLK1    $AT91C_PIO_PC28
set AT91C_PIO_PC29       [expr 1 << 29 ]
set AT91C_PC29_PCK0     $AT91C_PIO_PC29
set AT91C_PC29_PWM2     $AT91C_PIO_PC29
set AT91C_PIO_PC3        [expr 1 <<  3 ]
set AT91C_PC3_LCDEN    $AT91C_PIO_PC3
set AT91C_PC3_PWM1     $AT91C_PIO_PC3
set AT91C_PIO_PC30       [expr 1 << 30 ]
set AT91C_PC30_DRXD     $AT91C_PIO_PC30
set AT91C_PIO_PC31       [expr 1 << 31 ]
set AT91C_PC31_DTXD     $AT91C_PIO_PC31
set AT91C_PIO_PC4        [expr 1 <<  4 ]
set AT91C_PC4_LCDD0    $AT91C_PIO_PC4
set AT91C_PC4_LCDD3B   $AT91C_PIO_PC4
set AT91C_PIO_PC5        [expr 1 <<  5 ]
set AT91C_PC5_LCDD1    $AT91C_PIO_PC5
set AT91C_PC5_LCDD4B   $AT91C_PIO_PC5
set AT91C_PIO_PC6        [expr 1 <<  6 ]
set AT91C_PC6_LCDD2    $AT91C_PIO_PC6
set AT91C_PC6_LCDD5B   $AT91C_PIO_PC6
set AT91C_PIO_PC7        [expr 1 <<  7 ]
set AT91C_PC7_LCDD3    $AT91C_PIO_PC7
set AT91C_PC7_LCDD6B   $AT91C_PIO_PC7
set AT91C_PIO_PC8        [expr 1 <<  8 ]
set AT91C_PC8_LCDD4    $AT91C_PIO_PC8
set AT91C_PC8_LCDD7B   $AT91C_PIO_PC8
set AT91C_PIO_PC9        [expr 1 <<  9 ]
set AT91C_PC9_LCDD5    $AT91C_PIO_PC9
set AT91C_PC9_LCDD10B  $AT91C_PIO_PC9
set AT91C_PIO_PD0        [expr 1 <<  0 ]
set AT91C_PD0_TXD1     $AT91C_PIO_PD0
set AT91C_PD0_SPI0_NPCS2D $AT91C_PIO_PD0
set AT91C_PIO_PD1        [expr 1 <<  1 ]
set AT91C_PD1_RXD1     $AT91C_PIO_PD1
set AT91C_PD1_SPI0_NPCS3D $AT91C_PIO_PD1
set AT91C_PIO_PD10       [expr 1 << 10 ]
set AT91C_PD10_UNCONNECTED_PD10_A $AT91C_PIO_PD10
set AT91C_PD10_SCK1     $AT91C_PIO_PD10
set AT91C_PIO_PD11       [expr 1 << 11 ]
set AT91C_PD11_EBI0_NCS2 $AT91C_PIO_PD11
set AT91C_PD11_TSYNC    $AT91C_PIO_PD11
set AT91C_PIO_PD12       [expr 1 << 12 ]
set AT91C_PD12_EBI0_A23 $AT91C_PIO_PD12
set AT91C_PD12_TCLK     $AT91C_PIO_PD12
set AT91C_PIO_PD13       [expr 1 << 13 ]
set AT91C_PD13_EBI0_A24 $AT91C_PIO_PD13
set AT91C_PD13_TPS0     $AT91C_PIO_PD13
set AT91C_PIO_PD14       [expr 1 << 14 ]
set AT91C_PD14_EBI0_A25_CFNRW $AT91C_PIO_PD14
set AT91C_PD14_TPS1     $AT91C_PIO_PD14
set AT91C_PIO_PD15       [expr 1 << 15 ]
set AT91C_PD15_EBI0_NCS3_NANDCS $AT91C_PIO_PD15
set AT91C_PD15_TPS2     $AT91C_PIO_PD15
set AT91C_PIO_PD16       [expr 1 << 16 ]
set AT91C_PD16_EBI0_D16 $AT91C_PIO_PD16
set AT91C_PD16_TPK0     $AT91C_PIO_PD16
set AT91C_PIO_PD17       [expr 1 << 17 ]
set AT91C_PD17_EBI0_D17 $AT91C_PIO_PD17
set AT91C_PD17_TPK1     $AT91C_PIO_PD17
set AT91C_PIO_PD18       [expr 1 << 18 ]
set AT91C_PD18_EBI0_D18 $AT91C_PIO_PD18
set AT91C_PD18_TPK2     $AT91C_PIO_PD18
set AT91C_PIO_PD19       [expr 1 << 19 ]
set AT91C_PD19_EBI0_D19 $AT91C_PIO_PD19
set AT91C_PD19_TPK3     $AT91C_PIO_PD19
set AT91C_PIO_PD2        [expr 1 <<  2 ]
set AT91C_PD2_TXD2     $AT91C_PIO_PD2
set AT91C_PD2_SPI1_NPCS2D $AT91C_PIO_PD2
set AT91C_PIO_PD20       [expr 1 << 20 ]
set AT91C_PD20_EBI0_D20 $AT91C_PIO_PD20
set AT91C_PD20_TPK4     $AT91C_PIO_PD20
set AT91C_PIO_PD21       [expr 1 << 21 ]
set AT91C_PD21_EBI0_D21 $AT91C_PIO_PD21
set AT91C_PD21_TPK5     $AT91C_PIO_PD21
set AT91C_PIO_PD22       [expr 1 << 22 ]
set AT91C_PD22_EBI0_D22 $AT91C_PIO_PD22
set AT91C_PD22_TPK6     $AT91C_PIO_PD22
set AT91C_PIO_PD23       [expr 1 << 23 ]
set AT91C_PD23_EBI0_D23 $AT91C_PIO_PD23
set AT91C_PD23_TPK7     $AT91C_PIO_PD23
set AT91C_PIO_PD24       [expr 1 << 24 ]
set AT91C_PD24_EBI0_D24 $AT91C_PIO_PD24
set AT91C_PD24_TPK8     $AT91C_PIO_PD24
set AT91C_PIO_PD25       [expr 1 << 25 ]
set AT91C_PD25_EBI0_D25 $AT91C_PIO_PD25
set AT91C_PD25_TPK9     $AT91C_PIO_PD25
set AT91C_PIO_PD26       [expr 1 << 26 ]
set AT91C_PD26_EBI0_D26 $AT91C_PIO_PD26
set AT91C_PD26_TPK10    $AT91C_PIO_PD26
set AT91C_PIO_PD27       [expr 1 << 27 ]
set AT91C_PD27_EBI0_D27 $AT91C_PIO_PD27
set AT91C_PD27_TPK11    $AT91C_PIO_PD27
set AT91C_PIO_PD28       [expr 1 << 28 ]
set AT91C_PD28_EBI0_D28 $AT91C_PIO_PD28
set AT91C_PD28_TPK12    $AT91C_PIO_PD28
set AT91C_PIO_PD29       [expr 1 << 29 ]
set AT91C_PD29_EBI0_D29 $AT91C_PIO_PD29
set AT91C_PD29_TPK13    $AT91C_PIO_PD29
set AT91C_PIO_PD3        [expr 1 <<  3 ]
set AT91C_PD3_RXD2     $AT91C_PIO_PD3
set AT91C_PD3_SPI1_NPCS3D $AT91C_PIO_PD3
set AT91C_PIO_PD30       [expr 1 << 30 ]
set AT91C_PD30_EBI0_D30 $AT91C_PIO_PD30
set AT91C_PD30_TPK14    $AT91C_PIO_PD30
set AT91C_PIO_PD31       [expr 1 << 31 ]
set AT91C_PD31_EBI0_D31 $AT91C_PIO_PD31
set AT91C_PD31_TPK15    $AT91C_PIO_PD31
set AT91C_PIO_PD4        [expr 1 <<  4 ]
set AT91C_PD4_FIQ      $AT91C_PIO_PD4
set AT91C_PD4_DMARQ2   $AT91C_PIO_PD4
set AT91C_PIO_PD5        [expr 1 <<  5 ]
set AT91C_PD5_EBI0_NWAIT $AT91C_PIO_PD5
set AT91C_PD5_RTS2     $AT91C_PIO_PD5
set AT91C_PIO_PD6        [expr 1 <<  6 ]
set AT91C_PD6_EBI0_NCS4_CFCS0 $AT91C_PIO_PD6
set AT91C_PD6_CTS2     $AT91C_PIO_PD6
set AT91C_PIO_PD7        [expr 1 <<  7 ]
set AT91C_PD7_EBI0_NCS5_CFCS1 $AT91C_PIO_PD7
set AT91C_PD7_RTS1     $AT91C_PIO_PD7
set AT91C_PIO_PD8        [expr 1 <<  8 ]
set AT91C_PD8_EBI0_CFCE1 $AT91C_PIO_PD8
set AT91C_PD8_CTS1     $AT91C_PIO_PD8
set AT91C_PIO_PD9        [expr 1 <<  9 ]
set AT91C_PD9_EBI0_CFCE2 $AT91C_PIO_PD9
set AT91C_PD9_SCK2     $AT91C_PIO_PD9
set AT91C_PIO_PE0        [expr 1 <<  0 ]
set AT91C_PE0_ISI_D0   $AT91C_PIO_PE0
set AT91C_PIO_PE1        [expr 1 <<  1 ]
set AT91C_PE1_ISI_D1   $AT91C_PIO_PE1
set AT91C_PIO_PE10       [expr 1 << 10 ]
set AT91C_PE10_ISI_VSYNC $AT91C_PIO_PE10
set AT91C_PE10_PWM3     $AT91C_PIO_PE10
set AT91C_PIO_PE11       [expr 1 << 11 ]
set AT91C_PE11_ISI_MCK  $AT91C_PIO_PE11
set AT91C_PE11_PCK3     $AT91C_PIO_PE11
set AT91C_PIO_PE12       [expr 1 << 12 ]
set AT91C_PE12_KBDR0    $AT91C_PIO_PE12
set AT91C_PE12_ISI_D8   $AT91C_PIO_PE12
set AT91C_PIO_PE13       [expr 1 << 13 ]
set AT91C_PE13_KBDR1    $AT91C_PIO_PE13
set AT91C_PE13_ISI_D9   $AT91C_PIO_PE13
set AT91C_PIO_PE14       [expr 1 << 14 ]
set AT91C_PE14_KBDR2    $AT91C_PIO_PE14
set AT91C_PE14_ISI_D10  $AT91C_PIO_PE14
set AT91C_PIO_PE15       [expr 1 << 15 ]
set AT91C_PE15_KBDR3    $AT91C_PIO_PE15
set AT91C_PE15_ISI_D11  $AT91C_PIO_PE15
set AT91C_PIO_PE16       [expr 1 << 16 ]
set AT91C_PE16_KBDR4    $AT91C_PIO_PE16
set AT91C_PIO_PE17       [expr 1 << 17 ]
set AT91C_PE17_KBDC0    $AT91C_PIO_PE17
set AT91C_PIO_PE18       [expr 1 << 18 ]
set AT91C_PE18_KBDC1    $AT91C_PIO_PE18
set AT91C_PE18_TIOA0    $AT91C_PIO_PE18
set AT91C_PIO_PE19       [expr 1 << 19 ]
set AT91C_PE19_KBDC2    $AT91C_PIO_PE19
set AT91C_PE19_TIOB0    $AT91C_PIO_PE19
set AT91C_PIO_PE2        [expr 1 <<  2 ]
set AT91C_PE2_ISI_D2   $AT91C_PIO_PE2
set AT91C_PIO_PE20       [expr 1 << 20 ]
set AT91C_PE20_KBDC3    $AT91C_PIO_PE20
set AT91C_PE20_EBI1_NWAIT $AT91C_PIO_PE20
set AT91C_PIO_PE21       [expr 1 << 21 ]
set AT91C_PE21_ETXCK    $AT91C_PIO_PE21
set AT91C_PE21_EBI1_NANDWE $AT91C_PIO_PE21
set AT91C_PIO_PE22       [expr 1 << 22 ]
set AT91C_PE22_ECRS     $AT91C_PIO_PE22
set AT91C_PE22_EBI1_NCS2_NANDCS $AT91C_PIO_PE22
set AT91C_PIO_PE23       [expr 1 << 23 ]
set AT91C_PE23_ETX0     $AT91C_PIO_PE23
set AT91C_PE23_EBI1_NANDOE $AT91C_PIO_PE23
set AT91C_PIO_PE24       [expr 1 << 24 ]
set AT91C_PE24_ETX1     $AT91C_PIO_PE24
set AT91C_PE24_EBI1_NWR3_NBS3 $AT91C_PIO_PE24
set AT91C_PIO_PE25       [expr 1 << 25 ]
set AT91C_PE25_ERX0     $AT91C_PIO_PE25
set AT91C_PE25_EBI1_NCS1_SDCS $AT91C_PIO_PE25
set AT91C_PIO_PE26       [expr 1 << 26 ]
set AT91C_PE26_ERX1     $AT91C_PIO_PE26
set AT91C_PIO_PE27       [expr 1 << 27 ]
set AT91C_PE27_ERXER    $AT91C_PIO_PE27
set AT91C_PE27_EBI1_SDCKE $AT91C_PIO_PE27
set AT91C_PIO_PE28       [expr 1 << 28 ]
set AT91C_PE28_ETXEN    $AT91C_PIO_PE28
set AT91C_PE28_EBI1_RAS $AT91C_PIO_PE28
set AT91C_PIO_PE29       [expr 1 << 29 ]
set AT91C_PE29_EMDC     $AT91C_PIO_PE29
set AT91C_PE29_EBI1_CAS $AT91C_PIO_PE29
set AT91C_PIO_PE3        [expr 1 <<  3 ]
set AT91C_PE3_ISI_D3   $AT91C_PIO_PE3
set AT91C_PIO_PE30       [expr 1 << 30 ]
set AT91C_PE30_EMDIO    $AT91C_PIO_PE30
set AT91C_PE30_EBI1_SDWE $AT91C_PIO_PE30
set AT91C_PIO_PE31       [expr 1 << 31 ]
set AT91C_PE31_EF100    $AT91C_PIO_PE31
set AT91C_PE31_EBI1_SDA10 $AT91C_PIO_PE31
set AT91C_PIO_PE4        [expr 1 <<  4 ]
set AT91C_PE4_ISI_D4   $AT91C_PIO_PE4
set AT91C_PIO_PE5        [expr 1 <<  5 ]
set AT91C_PE5_ISI_D5   $AT91C_PIO_PE5
set AT91C_PIO_PE6        [expr 1 <<  6 ]
set AT91C_PE6_ISI_D6   $AT91C_PIO_PE6
set AT91C_PIO_PE7        [expr 1 <<  7 ]
set AT91C_PE7_ISI_D7   $AT91C_PIO_PE7
set AT91C_PIO_PE8        [expr 1 <<  8 ]
set AT91C_PE8_ISI_PCK  $AT91C_PIO_PE8
set AT91C_PE8_TIOA1    $AT91C_PIO_PE8
set AT91C_PIO_PE9        [expr 1 <<  9 ]
set AT91C_PE9_ISI_HSYNC $AT91C_PIO_PE9
set AT91C_PE9_TIOB1    $AT91C_PIO_PE9

# *****************************************************************************
#               MEMORY MAPPING DEFINITIONS FOR AT91SAM9263
# *****************************************************************************
set AT91C_ITCM 	 0x00100000
set AT91C_ITCM_SIZE	 0x00010000
set AT91C_DTCM 	 0x00200000
set AT91C_DTCM_SIZE	 0x00010000
set AT91C_IRAM 	 0x00300000
set AT91C_IRAM_SIZE	 0x00014000
set AT91C_IRAM_MIN	 0x00300000
set AT91C_IRAM_MIN_SIZE	 0x00004000
set AT91C_IROM 	 0x00400000
set AT91C_IROM_SIZE	 0x00020000
set AT91C_IRAM2	 0x00500000
set AT91C_IRAM2_SIZE	 0x00004000
set AT91C_EBI0_CS0	 0x10000000
set AT91C_EBI0_CS0_SIZE	 0x10000000
set AT91C_EBI0_CS1	 0x20000000
set AT91C_EBI0_CS1_SIZE	 0x10000000
set AT91C_EBI0_SDRAM	 0x20000000
set AT91C_EBI0_SDRAM_SIZE	 0x10000000
set AT91C_EBI0_SDRAM_16BIT	 0x20000000
set AT91C_EBI0_SDRAM_16BIT_SIZE	 0x02000000
set AT91C_EBI0_SDRAM_32BIT	 0x20000000
set AT91C_EBI0_SDRAM_32BIT_SIZE	 0x04000000
set AT91C_EBI0_CS2	 0x30000000
set AT91C_EBI0_CS2_SIZE	 0x10000000
set AT91C_EBI0_CS3	 0x40000000
set AT91C_EBI0_CS3_SIZE	 0x10000000
set AT91C_EBI0_SM	 0x40000000
set AT91C_EBI0_SM_SIZE	 0x10000000
set AT91C_EBI0_CS4	 0x50000000
set AT91C_EBI0_CS4_SIZE	 0x10000000
set AT91C_EBI0_CF0	 0x50000000
set AT91C_EBI0_CF0_SIZE	 0x10000000
set AT91C_EBI0_CS5	 0x60000000
set AT91C_EBI0_CS5_SIZE	 0x10000000
set AT91C_EBI0_CF1	 0x60000000
set AT91C_EBI0_CF1_SIZE	 0x10000000
set AT91C_EBI1_CS0	 0x70000000
set AT91C_EBI1_CS0_SIZE	 0x10000000
set AT91C_EBI1_CS1	 0x80000000
set AT91C_EBI1_CS1_SIZE	 0x10000000
set AT91C_EBI1_SDRAM_16BIT	 0x80000000
set AT91C_EBI1_SDRAM_16BIT_SIZE	 0x02000000
set AT91C_EBI1_SDRAM_32BIT	 0x80000000
set AT91C_EBI1_SDRAM_32BIT_SIZE	 0x04000000
set AT91C_EBI1_CS2	 0x90000000
set AT91C_EBI1_CS2_SIZE	 0x10000000
set AT91C_EBI1_SM	 0x90000000
set AT91C_EBI1_SM_SIZE	 0x10000000


# *****************************************************************************
#               ATTRIBUTES DEFINITIONS FOR AT91SAM9263
# *****************************************************************************
array set AT91SAM9263_att {
	PDC 	{ LP 	PDC_DBGU_att 	PDC_MCI0_att 	PDC_MCI1_att 	PDC_US0_att 	PDC_US1_att 	PDC_US2_att 	PDC_SSC0_att 	PDC_SSC1_att 	PDC_AC97C_att 	PDC_SPI0_att 	PDC_SPI1_att }
	EBI0 	{ LP 	EBI0_att }
	EBI1 	{ LP 	EBI1_att }
	SYS 	{ LP 	SYS_att }
	UHP 	{ LP 	UHP_att }
	EMAC 	{ LP 	MACB_att }
	SPI 	{ LP 	SPI0_att 	SPI1_att }
	DMA 	{ LP 	DMA_att }
	CCFG 	{ LP 	CCFG_att }
	ISI 	{ LP 	HISI_att }
	MATRIX 	{ LP 	MATRIX_att }
	RSTC 	{ LP 	RSTC_att }
	CKGR 	{ LP 	CKGR_att }
	TWI 	{ LP 	TWI_att }
	SDRAMC 	{ LP 	SDRAMC0_att 	SDRAMC1_att }
	USART 	{ LP 	US0_att 	US1_att 	US2_att }
	WDTC 	{ LP 	WDTC_att }
	SMC 	{ LP 	SMC0_att 	SMC1_att }
	ECC 	{ LP 	HECC0_att 	HECC1_att }
	AIC 	{ LP 	AIC_att }
	CAN 	{ LP 	CAN_att }
	DBGU 	{ LP 	DBGU_att }
	PWMC_CH 	{ LP 	PWMC_CH0_att 	PWMC_CH1_att 	PWMC_CH2_att 	PWMC_CH3_att }
	SHDWC 	{ LP 	SHDWC_att }
	SSC 	{ LP 	SSC0_att 	SSC1_att }
	TCB 	{ LP 	TCB0_att 	TCB1_att 	TCB2_att }
	PWMC 	{ LP 	PWMC_att }
	LCDC 	{ LP 	LCDC_att }
	PITC 	{ LP 	PITC_att }
	TC 	{ LP 	TC0_att 	TC1_att 	TC2_att }
	PMC 	{ LP 	PMC_att }
	TBOX 	{ LP 	TBOX_att }
	AC97C 	{ LP 	AC97C_att }
	CAN_MB 	{ LP 	CAN_MB0_att 	CAN_MB1_att 	CAN_MB2_att 	CAN_MB3_att 	CAN_MB4_att 	CAN_MB5_att 	CAN_MB6_att 	CAN_MB7_att 	CAN_MB8_att 	CAN_MB9_att 	CAN_MB10_att 	CAN_MB11_att 	CAN_MB12_att 	CAN_MB13_att 	CAN_MB14_att 	CAN_MB15_att }
	RTTC 	{ LP 	RTTC0_att 	RTTC1_att }
	PIO 	{ LP 	PIOA_att 	PIOB_att 	PIOC_att 	PIOD_att 	PIOE_att }
	MCI 	{ LP 	MCI0_att 	MCI1_att }
	UDP 	{ LP 	UDP_att }

}
# ========== Peripheral attributes for PDC peripheral ========== 
array set PDC_DBGU_att {
	PTCR 	{ R AT91C_DBGU_PTCR 	WO }
	TNPR 	{ R AT91C_DBGU_TNPR 	RW }
	RNPR 	{ R AT91C_DBGU_RNPR 	RW }
	TPR 	{ R AT91C_DBGU_TPR 	RW }
	RPR 	{ R AT91C_DBGU_RPR 	RW }
	PTSR 	{ R AT91C_DBGU_PTSR 	RO }
	TNCR 	{ R AT91C_DBGU_TNCR 	RW }
	RNCR 	{ R AT91C_DBGU_RNCR 	RW }
	TCR 	{ R AT91C_DBGU_TCR 	RW }
	RCR 	{ R AT91C_DBGU_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}
array set PDC_MCI0_att {
	TNCR 	{ R AT91C_MCI0_TNCR 	RW }
	RNCR 	{ R AT91C_MCI0_RNCR 	RW }
	TCR 	{ R AT91C_MCI0_TCR 	RW }
	RCR 	{ R AT91C_MCI0_RCR 	RW }
	PTCR 	{ R AT91C_MCI0_PTCR 	WO }
	TNPR 	{ R AT91C_MCI0_TNPR 	RW }
	RPR 	{ R AT91C_MCI0_RPR 	RW }
	TPR 	{ R AT91C_MCI0_TPR 	RW }
	RNPR 	{ R AT91C_MCI0_RNPR 	RW }
	PTSR 	{ R AT91C_MCI0_PTSR 	RO }
	listeReg 	{ TNCR RNCR TCR RCR PTCR TNPR RPR TPR RNPR PTSR  }

}
array set PDC_MCI1_att {
	PTSR 	{ R AT91C_MCI1_PTSR 	RO }
	TNCR 	{ R AT91C_MCI1_TNCR 	RW }
	RNCR 	{ R AT91C_MCI1_RNCR 	RW }
	TCR 	{ R AT91C_MCI1_TCR 	RW }
	RCR 	{ R AT91C_MCI1_RCR 	RW }
	PTCR 	{ R AT91C_MCI1_PTCR 	WO }
	TNPR 	{ R AT91C_MCI1_TNPR 	RW }
	RNPR 	{ R AT91C_MCI1_RNPR 	RW }
	TPR 	{ R AT91C_MCI1_TPR 	RW }
	RPR 	{ R AT91C_MCI1_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}
array set PDC_US0_att {
	PTSR 	{ R AT91C_US0_PTSR 	RO }
	TNCR 	{ R AT91C_US0_TNCR 	RW }
	RNCR 	{ R AT91C_US0_RNCR 	RW }
	TCR 	{ R AT91C_US0_TCR 	RW }
	RCR 	{ R AT91C_US0_RCR 	RW }
	PTCR 	{ R AT91C_US0_PTCR 	WO }
	TNPR 	{ R AT91C_US0_TNPR 	RW }
	RNPR 	{ R AT91C_US0_RNPR 	RW }
	TPR 	{ R AT91C_US0_TPR 	RW }
	RPR 	{ R AT91C_US0_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}
array set PDC_US1_att {
	PTSR 	{ R AT91C_US1_PTSR 	RO }
	TNCR 	{ R AT91C_US1_TNCR 	RW }
	RNCR 	{ R AT91C_US1_RNCR 	RW }
	TCR 	{ R AT91C_US1_TCR 	RW }
	RCR 	{ R AT91C_US1_RCR 	RW }
	PTCR 	{ R AT91C_US1_PTCR 	WO }
	TNPR 	{ R AT91C_US1_TNPR 	RW }
	RNPR 	{ R AT91C_US1_RNPR 	RW }
	TPR 	{ R AT91C_US1_TPR 	RW }
	RPR 	{ R AT91C_US1_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}
array set PDC_US2_att {
	PTCR 	{ R AT91C_US2_PTCR 	WO }
	TNPR 	{ R AT91C_US2_TNPR 	RW }
	RNPR 	{ R AT91C_US2_RNPR 	RW }
	TPR 	{ R AT91C_US2_TPR 	RW }
	RPR 	{ R AT91C_US2_RPR 	RW }
	PTSR 	{ R AT91C_US2_PTSR 	RO }
	TNCR 	{ R AT91C_US2_TNCR 	RW }
	RNCR 	{ R AT91C_US2_RNCR 	RW }
	TCR 	{ R AT91C_US2_TCR 	RW }
	RCR 	{ R AT91C_US2_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}
array set PDC_SSC0_att {
	TCR 	{ R AT91C_SSC0_TCR 	RW }
	RCR 	{ R AT91C_SSC0_RCR 	RW }
	PTCR 	{ R AT91C_SSC0_PTCR 	WO }
	TNPR 	{ R AT91C_SSC0_TNPR 	RW }
	RNPR 	{ R AT91C_SSC0_RNPR 	RW }
	TPR 	{ R AT91C_SSC0_TPR 	RW }
	RPR 	{ R AT91C_SSC0_RPR 	RW }
	PTSR 	{ R AT91C_SSC0_PTSR 	RO }
	RNCR 	{ R AT91C_SSC0_RNCR 	RW }
	TNCR 	{ R AT91C_SSC0_TNCR 	RW }
	listeReg 	{ TCR RCR PTCR TNPR RNPR TPR RPR PTSR RNCR TNCR  }

}
array set PDC_SSC1_att {
	PTCR 	{ R AT91C_SSC1_PTCR 	WO }
	TNPR 	{ R AT91C_SSC1_TNPR 	RW }
	RNPR 	{ R AT91C_SSC1_RNPR 	RW }
	TPR 	{ R AT91C_SSC1_TPR 	RW }
	RPR 	{ R AT91C_SSC1_RPR 	RW }
	PTSR 	{ R AT91C_SSC1_PTSR 	RO }
	TNCR 	{ R AT91C_SSC1_TNCR 	RW }
	RNCR 	{ R AT91C_SSC1_RNCR 	RW }
	TCR 	{ R AT91C_SSC1_TCR 	RW }
	RCR 	{ R AT91C_SSC1_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}
array set PDC_AC97C_att {
	PTSR 	{ R AT91C_AC97C_PTSR 	RO }
	TNCR 	{ R AT91C_AC97C_TNCR 	RW }
	RNCR 	{ R AT91C_AC97C_RNCR 	RW }
	TCR 	{ R AT91C_AC97C_TCR 	RW }
	RCR 	{ R AT91C_AC97C_RCR 	RW }
	PTCR 	{ R AT91C_AC97C_PTCR 	WO }
	TNPR 	{ R AT91C_AC97C_TNPR 	RW }
	RNPR 	{ R AT91C_AC97C_RNPR 	RW }
	TPR 	{ R AT91C_AC97C_TPR 	RW }
	RPR 	{ R AT91C_AC97C_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}
array set PDC_SPI0_att {
	PTCR 	{ R AT91C_SPI0_PTCR 	WO }
	TNPR 	{ R AT91C_SPI0_TNPR 	RW }
	RNPR 	{ R AT91C_SPI0_RNPR 	RW }
	TPR 	{ R AT91C_SPI0_TPR 	RW }
	RPR 	{ R AT91C_SPI0_RPR 	RW }
	PTSR 	{ R AT91C_SPI0_PTSR 	RO }
	TNCR 	{ R AT91C_SPI0_TNCR 	RW }
	RNCR 	{ R AT91C_SPI0_RNCR 	RW }
	TCR 	{ R AT91C_SPI0_TCR 	RW }
	RCR 	{ R AT91C_SPI0_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}
array set PDC_SPI1_att {
	PTSR 	{ R AT91C_SPI1_PTSR 	RO }
	TNCR 	{ R AT91C_SPI1_TNCR 	RW }
	RNCR 	{ R AT91C_SPI1_RNCR 	RW }
	TCR 	{ R AT91C_SPI1_TCR 	RW }
	RCR 	{ R AT91C_SPI1_RCR 	RW }
	PTCR 	{ R AT91C_SPI1_PTCR 	WO }
	TNPR 	{ R AT91C_SPI1_TNPR 	RW }
	RNPR 	{ R AT91C_SPI1_RNPR 	RW }
	TPR 	{ R AT91C_SPI1_TPR 	RW }
	RPR 	{ R AT91C_SPI1_RPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR RCR PTCR TNPR RNPR TPR RPR  }

}

# ========== Peripheral attributes for EBI0 peripheral ========== 
array set EBI0_att {
	DUMMY 	{ R AT91C_EBI0_DUMMY 	RW }
	listeReg 	{ DUMMY  }

}

# ========== Peripheral attributes for EBI1 peripheral ========== 
array set EBI1_att {
	DUMMY 	{ R AT91C_EBI1_DUMMY 	RW }
	listeReg 	{ DUMMY  }

}

# ========== Peripheral attributes for SYS peripheral ========== 
array set SYS_att {
	ECC0 	{ R AT91C_SYS_ECC0 	 }
	GPBR 	{ R AT91C_SYS_GPBR 	 20 }
	ECC1 	{ R AT91C_SYS_ECC1 	 }
	listeReg 	{ ECC0 GPBR ECC1  }

}

# ========== Peripheral attributes for UHP peripheral ========== 
array set UHP_att {
	HcBulkHeadED 	{ R AT91C_UHP_HcBulkHeadED 	RW }
	HcFmNumber 	{ R AT91C_UHP_HcFmNumber 	RW }
	HcFmInterval 	{ R AT91C_UHP_HcFmInterval 	RW }
	HcBulkCurrentED 	{ R AT91C_UHP_HcBulkCurrentED 	RW }
	HcRhStatus 	{ R AT91C_UHP_HcRhStatus 	RW }
	HcRhDescriptorA 	{ R AT91C_UHP_HcRhDescriptorA 	RW }
	HcPeriodicStart 	{ R AT91C_UHP_HcPeriodicStart 	RW }
	HcFmRemaining 	{ R AT91C_UHP_HcFmRemaining 	RW }
	HcBulkDoneHead 	{ R AT91C_UHP_HcBulkDoneHead 	RW }
	HcRevision 	{ R AT91C_UHP_HcRevision 	R }
	HcRhPortStatus 	{ R AT91C_UHP_HcRhPortStatus 	RW  2 }
	HcRhDescriptorB 	{ R AT91C_UHP_HcRhDescriptorB 	RW }
	HcLSThreshold 	{ R AT91C_UHP_HcLSThreshold 	RW }
	HcControl 	{ R AT91C_UHP_HcControl 	RW }
	HcInterruptStatus 	{ R AT91C_UHP_HcInterruptStatus 	RW }
	HcInterruptDisable 	{ R AT91C_UHP_HcInterruptDisable 	RW }
	HcCommandStatus 	{ R AT91C_UHP_HcCommandStatus 	RW }
	HcInterruptEnable 	{ R AT91C_UHP_HcInterruptEnable 	RW }
	HcHCCA 	{ R AT91C_UHP_HcHCCA 	RW }
	HcControlHeadED 	{ R AT91C_UHP_HcControlHeadED 	RW }
	HcPeriodCurrentED 	{ R AT91C_UHP_HcPeriodCurrentED 	RW }
	HcControlCurrentED 	{ R AT91C_UHP_HcControlCurrentED 	RW }
	listeReg 	{ HcBulkHeadED HcFmNumber HcFmInterval HcBulkCurrentED HcRhStatus HcRhDescriptorA HcPeriodicStart HcFmRemaining HcBulkDoneHead HcRevision HcRhPortStatus HcRhDescriptorB HcLSThreshold HcControl HcInterruptStatus HcInterruptDisable HcCommandStatus HcInterruptEnable HcHCCA HcControlHeadED HcPeriodCurrentED HcControlCurrentED  }

}

# ========== Peripheral attributes for EMAC peripheral ========== 
array set MACB_att {
	RSR 	{ R AT91C_MACB_RSR 	RW }
	MAN 	{ R AT91C_MACB_MAN 	RW }
	ISR 	{ R AT91C_MACB_ISR 	RW }
	HRB 	{ R AT91C_MACB_HRB 	RW }
	MCF 	{ R AT91C_MACB_MCF 	RW }
	PTR 	{ R AT91C_MACB_PTR 	RW }
	IER 	{ R AT91C_MACB_IER 	WO }
	SA2H 	{ R AT91C_MACB_SA2H 	RW }
	HRT 	{ R AT91C_MACB_HRT 	RW }
	LCOL 	{ R AT91C_MACB_LCOL 	RW }
	FRO 	{ R AT91C_MACB_FRO 	RW }
	PFR 	{ R AT91C_MACB_PFR 	RW }
	NCFGR 	{ R AT91C_MACB_NCFGR 	RW }
	TID 	{ R AT91C_MACB_TID 	RW }
	SA3L 	{ R AT91C_MACB_SA3L 	RW }
	FCSE 	{ R AT91C_MACB_FCSE 	RW }
	ECOL 	{ R AT91C_MACB_ECOL 	RW }
	ROV 	{ R AT91C_MACB_ROV 	RW }
	NSR 	{ R AT91C_MACB_NSR 	RO }
	RBQP 	{ R AT91C_MACB_RBQP 	RW }
	TPQ 	{ R AT91C_MACB_TPQ 	RW }
	TUND 	{ R AT91C_MACB_TUND 	RW }
	RSE 	{ R AT91C_MACB_RSE 	RW }
	TBQP 	{ R AT91C_MACB_TBQP 	RW }
	ELE 	{ R AT91C_MACB_ELE 	RW }
	STE 	{ R AT91C_MACB_STE 	RW }
	IDR 	{ R AT91C_MACB_IDR 	WO }
	SA1L 	{ R AT91C_MACB_SA1L 	RW }
	RLE 	{ R AT91C_MACB_RLE 	RW }
	IMR 	{ R AT91C_MACB_IMR 	RO }
	FTO 	{ R AT91C_MACB_FTO 	RW }
	SA3H 	{ R AT91C_MACB_SA3H 	RW }
	SA1H 	{ R AT91C_MACB_SA1H 	RW }
	TPF 	{ R AT91C_MACB_TPF 	RW }
	SCF 	{ R AT91C_MACB_SCF 	RW }
	ALE 	{ R AT91C_MACB_ALE 	RW }
	USRIO 	{ R AT91C_MACB_USRIO 	RW }
	SA4L 	{ R AT91C_MACB_SA4L 	RW }
	SA2L 	{ R AT91C_MACB_SA2L 	RW }
	REV 	{ R AT91C_MACB_REV 	RO }
	CSE 	{ R AT91C_MACB_CSE 	RW }
	DTF 	{ R AT91C_MACB_DTF 	RW }
	NCR 	{ R AT91C_MACB_NCR 	RW }
	WOL 	{ R AT91C_MACB_WOL 	RW }
	SA4H 	{ R AT91C_MACB_SA4H 	RW }
	RRE 	{ R AT91C_MACB_RRE 	RW }
	RJA 	{ R AT91C_MACB_RJA 	RW }
	TSR 	{ R AT91C_MACB_TSR 	RW }
	USF 	{ R AT91C_MACB_USF 	RW }
	listeReg 	{ RSR MAN ISR HRB MCF PTR IER SA2H HRT LCOL FRO PFR NCFGR TID SA3L FCSE ECOL ROV NSR RBQP TPQ TUND RSE TBQP ELE STE IDR SA1L RLE IMR FTO SA3H SA1H TPF SCF ALE USRIO SA4L SA2L REV CSE DTF NCR WOL SA4H RRE RJA TSR USF  }

}

# ========== Peripheral attributes for SPI peripheral ========== 
array set SPI0_att {
	SR 	{ R AT91C_SPI0_SR 	RO }
	RDR 	{ R AT91C_SPI0_RDR 	RO }
	CR 	{ R AT91C_SPI0_CR 	RO }
	MR 	{ R AT91C_SPI0_MR 	RW }
	TDR 	{ R AT91C_SPI0_TDR 	WO }
	IER 	{ R AT91C_SPI0_IER 	WO }
	IMR 	{ R AT91C_SPI0_IMR 	RO }
	CSR 	{ R AT91C_SPI0_CSR 	RW  4 }
	IDR 	{ R AT91C_SPI0_IDR 	WO }
	listeReg 	{ SR RDR CR MR TDR IER IMR CSR IDR  }

}
array set SPI1_att {
	CSR 	{ R AT91C_SPI1_CSR 	RW  4 }
	IDR 	{ R AT91C_SPI1_IDR 	WO }
	SR 	{ R AT91C_SPI1_SR 	RO }
	RDR 	{ R AT91C_SPI1_RDR 	RO }
	CR 	{ R AT91C_SPI1_CR 	RO }
	IMR 	{ R AT91C_SPI1_IMR 	RO }
	IER 	{ R AT91C_SPI1_IER 	WO }
	TDR 	{ R AT91C_SPI1_TDR 	WO }
	MR 	{ R AT91C_SPI1_MR 	RW }
	listeReg 	{ CSR IDR SR RDR CR IMR IER TDR MR  }

}

# ========== Peripheral attributes for DMA peripheral ========== 
array set DMA_att {
	CFG1h 	{ R AT91C_DMA_CFG1h 	RW }
	CFG0h 	{ R AT91C_DMA_CFG0h 	RW }
	SGLREQSRCREG 	{ R AT91C_DMA_SGLREQSRCREG 	RW }
	SGR1 	{ R AT91C_DMA_SGR1 	RW }
	SAR1 	{ R AT91C_DMA_SAR1 	RW }
	MASKBLOCK 	{ R AT91C_DMA_MASKBLOCK 	RW }
	RAWTFR 	{ R AT91C_DMA_RAWTFR 	RW }
	LSTREQSRCREG 	{ R AT91C_DMA_LSTREQSRCREG 	RW }
	CLEARBLOCK 	{ R AT91C_DMA_CLEARBLOCK 	RW }
	MASKERR 	{ R AT91C_DMA_MASKERR 	RW }
	MASKSRCTRAN 	{ R AT91C_DMA_MASKSRCTRAN 	RW }
	STATUSTFR 	{ R AT91C_DMA_STATUSTFR 	RW }
	RAWDSTTRAN 	{ R AT91C_DMA_RAWDSTTRAN 	RW }
	LLP1 	{ R AT91C_DMA_LLP1 	RW }
	SAR0 	{ R AT91C_DMA_SAR0 	RW }
	LLP0 	{ R AT91C_DMA_LLP0 	RW }
	SSTAT0 	{ R AT91C_DMA_SSTAT0 	RW }
	DMATESTREG 	{ R AT91C_DMA_DMATESTREG 	RW }
	CHENREG 	{ R AT91C_DMA_CHENREG 	RW }
	REQSRCREG 	{ R AT91C_DMA_REQSRCREG 	RW }
	CLEARERR 	{ R AT91C_DMA_CLEARERR 	RW }
	CLEARSRCTRAN 	{ R AT91C_DMA_CLEARSRCTRAN 	RW }
	MASKTFR 	{ R AT91C_DMA_MASKTFR 	RW }
	STATUSDSTTRAN 	{ R AT91C_DMA_STATUSDSTTRAN 	RW }
	DSTATAR1 	{ R AT91C_DMA_DSTATAR1 	RW }
	DSTAT1 	{ R AT91C_DMA_DSTAT1 	RW }
	SGR0 	{ R AT91C_DMA_SGR0 	RW }
	DSTATAR0 	{ R AT91C_DMA_DSTATAR0 	RW }
	DSTAT0 	{ R AT91C_DMA_DSTAT0 	RW }
	REQDSTREG 	{ R AT91C_DMA_REQDSTREG 	RW }
	DSR1 	{ R AT91C_DMA_DSR1 	RW }
	DSR0 	{ R AT91C_DMA_DSR0 	RW }
	RAWBLOCK 	{ R AT91C_DMA_RAWBLOCK 	RW }
	LSTREQDSTREG 	{ R AT91C_DMA_LSTREQDSTREG 	RW }
	SGLREQDSTREG 	{ R AT91C_DMA_SGLREQDSTREG 	RW }
	CLEARTFR 	{ R AT91C_DMA_CLEARTFR 	RW }
	MASKDSTTRAN 	{ R AT91C_DMA_MASKDSTTRAN 	RW }
	CTL1l 	{ R AT91C_DMA_CTL1l 	RW }
	DAR1 	{ R AT91C_DMA_DAR1 	RW }
	RAWSRCTRAN 	{ R AT91C_DMA_RAWSRCTRAN 	RW }
	RAWERR 	{ R AT91C_DMA_RAWERR 	RW }
	STATUSBLOCK 	{ R AT91C_DMA_STATUSBLOCK 	RW }
	CTL0l 	{ R AT91C_DMA_CTL0l 	RW }
	DAR0 	{ R AT91C_DMA_DAR0 	RW }
	CTL1h 	{ R AT91C_DMA_CTL1h 	RW }
	CTL0h 	{ R AT91C_DMA_CTL0h 	RW }
	VERSIONID 	{ R AT91C_DMA_VERSIONID 	RW }
	DMAIDREG 	{ R AT91C_DMA_DMAIDREG 	RW }
	DMACFGREG 	{ R AT91C_DMA_DMACFGREG 	RW }
	STATUSINT 	{ R AT91C_DMA_STATUSINT 	RW }
	CLEARDSTTRAN 	{ R AT91C_DMA_CLEARDSTTRAN 	RW }
	SSTAT1 	{ R AT91C_DMA_SSTAT1 	RW }
	SSTATAR1 	{ R AT91C_DMA_SSTATAR1 	RW }
	CFG1l 	{ R AT91C_DMA_CFG1l 	RW }
	STATUSSRCTRAN 	{ R AT91C_DMA_STATUSSRCTRAN 	RW }
	STATUSERR 	{ R AT91C_DMA_STATUSERR 	RW }
	SSTATAR0 	{ R AT91C_DMA_SSTATAR0 	RW }
	CFG0l 	{ R AT91C_DMA_CFG0l 	RW }
	listeReg 	{ CFG1h CFG0h SGLREQSRCREG SGR1 SAR1 MASKBLOCK RAWTFR LSTREQSRCREG CLEARBLOCK MASKERR MASKSRCTRAN STATUSTFR RAWDSTTRAN LLP1 SAR0 LLP0 SSTAT0 DMATESTREG CHENREG REQSRCREG CLEARERR CLEARSRCTRAN MASKTFR STATUSDSTTRAN DSTATAR1 DSTAT1 SGR0 DSTATAR0 DSTAT0 REQDSTREG DSR1 DSR0 RAWBLOCK LSTREQDSTREG SGLREQDSTREG CLEARTFR MASKDSTTRAN CTL1l DAR1 RAWSRCTRAN RAWERR STATUSBLOCK CTL0l DAR0 CTL1h CTL0h VERSIONID DMAIDREG DMACFGREG STATUSINT CLEARDSTTRAN SSTAT1 SSTATAR1 CFG1l STATUSSRCTRAN STATUSERR SSTATAR0 CFG0l  }

}

# ========== Peripheral attributes for CCFG peripheral ========== 
array set CCFG_att {
	MATRIXVERSION 	{ R AT91C_CCFG_MATRIXVERSION 	RO }
	EBI1CSA 	{ R AT91C_CCFG_EBI1CSA 	RW }
	TCMR 	{ R AT91C_CCFG_TCMR 	RW }
	EBI0CSA 	{ R AT91C_CCFG_EBI0CSA 	RW }
	listeReg 	{ MATRIXVERSION EBI1CSA TCMR EBI0CSA  }

}

# ========== Peripheral attributes for ISI peripheral ========== 
array set HISI_att {
	IDR 	{ R AT91C_HISI_IDR 	RW }
	SR 	{ R AT91C_HISI_SR 	RW }
	CR1 	{ R AT91C_HISI_CR1 	RW }
	CDBA 	{ R AT91C_HISI_CDBA 	WO }
	PDECF 	{ R AT91C_HISI_PDECF 	WO }
	IMR 	{ R AT91C_HISI_IMR 	RW }
	IER 	{ R AT91C_HISI_IER 	RW }
	R2YSET2 	{ R AT91C_HISI_R2YSET2 	RO }
	PSIZE 	{ R AT91C_HISI_PSIZE 	RO }
	PFBD 	{ R AT91C_HISI_PFBD 	WO }
	Y2RSET0 	{ R AT91C_HISI_Y2RSET0 	RO }
	R2YSET0 	{ R AT91C_HISI_R2YSET0 	RO }
	CR2 	{ R AT91C_HISI_CR2 	RW }
	Y2RSET1 	{ R AT91C_HISI_Y2RSET1 	RO }
	R2YSET1 	{ R AT91C_HISI_R2YSET1 	RO }
	listeReg 	{ IDR SR CR1 CDBA PDECF IMR IER R2YSET2 PSIZE PFBD Y2RSET0 R2YSET0 CR2 Y2RSET1 R2YSET1  }

}

# ========== Peripheral attributes for MATRIX peripheral ========== 
array set MATRIX_att {
	MCFG6 	{ R AT91C_MATRIX_MCFG6 	RW }
	MCFG7 	{ R AT91C_MATRIX_MCFG7 	RW }
	PRAS1 	{ R AT91C_MATRIX_PRAS1 	RW }
	SCFG0 	{ R AT91C_MATRIX_SCFG0 	RW }
	MCFG8 	{ R AT91C_MATRIX_MCFG8 	RW }
	PRBS3 	{ R AT91C_MATRIX_PRBS3 	RW }
	PRBS1 	{ R AT91C_MATRIX_PRBS1 	RW }
	SCFG5 	{ R AT91C_MATRIX_SCFG5 	RW }
	SCFG1 	{ R AT91C_MATRIX_SCFG1 	RW }
	PRAS6 	{ R AT91C_MATRIX_PRAS6 	RW }
	PRAS4 	{ R AT91C_MATRIX_PRAS4 	RW }
	SCFG2 	{ R AT91C_MATRIX_SCFG2 	RW }
	SCFG6 	{ R AT91C_MATRIX_SCFG6 	RW }
	MCFG0 	{ R AT91C_MATRIX_MCFG0 	RW }
	MCFG4 	{ R AT91C_MATRIX_MCFG4 	RW }
	PRBS6 	{ R AT91C_MATRIX_PRBS6 	RW }
	SCFG7 	{ R AT91C_MATRIX_SCFG7 	RW }
	MCFG5 	{ R AT91C_MATRIX_MCFG5 	RW }
	PRAS0 	{ R AT91C_MATRIX_PRAS0 	RW }
	PRAS2 	{ R AT91C_MATRIX_PRAS2 	RW }
	PRBS0 	{ R AT91C_MATRIX_PRBS0 	RW }
	PRBS2 	{ R AT91C_MATRIX_PRBS2 	RW }
	PRBS4 	{ R AT91C_MATRIX_PRBS4 	RW }
	SCFG3 	{ R AT91C_MATRIX_SCFG3 	RW }
	MCFG1 	{ R AT91C_MATRIX_MCFG1 	RW }
	MRCR 	{ R AT91C_MATRIX_MRCR 	RW }
	PRAS3 	{ R AT91C_MATRIX_PRAS3 	RW }
	PRAS5 	{ R AT91C_MATRIX_PRAS5 	RW }
	PRAS7 	{ R AT91C_MATRIX_PRAS7 	RW }
	SCFG4 	{ R AT91C_MATRIX_SCFG4 	RW }
	MCFG2 	{ R AT91C_MATRIX_MCFG2 	RW }
	PRBS5 	{ R AT91C_MATRIX_PRBS5 	RW }
	PRBS7 	{ R AT91C_MATRIX_PRBS7 	RW }
	MCFG3 	{ R AT91C_MATRIX_MCFG3 	RW }
	listeReg 	{ MCFG6 MCFG7 PRAS1 SCFG0 MCFG8 PRBS3 PRBS1 SCFG5 SCFG1 PRAS6 PRAS4 SCFG2 SCFG6 MCFG0 MCFG4 PRBS6 SCFG7 MCFG5 PRAS0 PRAS2 PRBS0 PRBS2 PRBS4 SCFG3 MCFG1 MRCR PRAS3 PRAS5 PRAS7 SCFG4 MCFG2 PRBS5 PRBS7 MCFG3  }

}

# ========== Peripheral attributes for RSTC peripheral ========== 
array set RSTC_att {
	RSR 	{ R AT91C_RSTC_RSR 	RO }
	RMR 	{ R AT91C_RSTC_RMR 	RW }
	RCR 	{ R AT91C_RSTC_RCR 	WO }
	listeReg 	{ RSR RMR RCR  }

}

# ========== Peripheral attributes for CKGR peripheral ========== 
array set CKGR_att {
	PLLBR 	{ R AT91C_CKGR_PLLBR 	RW }
	MCFR 	{ R AT91C_CKGR_MCFR 	RO }
	PLLAR 	{ R AT91C_CKGR_PLLAR 	RW }
	MOR 	{ R AT91C_CKGR_MOR 	RW }
	listeReg 	{ PLLBR MCFR PLLAR MOR  }

}

# ========== Peripheral attributes for TWI peripheral ========== 
array set TWI_att {
	THR 	{ R AT91C_TWI_THR 	WO }
	IMR 	{ R AT91C_TWI_IMR 	RO }
	IER 	{ R AT91C_TWI_IER 	WO }
	IADR 	{ R AT91C_TWI_IADR 	RW }
	MMR 	{ R AT91C_TWI_MMR 	RW }
	RHR 	{ R AT91C_TWI_RHR 	RO }
	IDR 	{ R AT91C_TWI_IDR 	WO }
	SR 	{ R AT91C_TWI_SR 	RO }
	CWGR 	{ R AT91C_TWI_CWGR 	RW }
	CR 	{ R AT91C_TWI_CR 	WO }
	listeReg 	{ THR IMR IER IADR MMR RHR IDR SR CWGR CR  }

}

# ========== Peripheral attributes for SDRAMC peripheral ========== 
array set SDRAMC0_att {
	ISR 	{ R AT91C_SDRAMC0_ISR 	RO }
	IDR 	{ R AT91C_SDRAMC0_IDR 	WO }
	LPR 	{ R AT91C_SDRAMC0_LPR 	RW }
	CR 	{ R AT91C_SDRAMC0_CR 	RW }
	MR 	{ R AT91C_SDRAMC0_MR 	RW }
	MDR 	{ R AT91C_SDRAMC0_MDR 	RO }
	IMR 	{ R AT91C_SDRAMC0_IMR 	RO }
	IER 	{ R AT91C_SDRAMC0_IER 	WO }
	HSR 	{ R AT91C_SDRAMC0_HSR 	RW }
	TR 	{ R AT91C_SDRAMC0_TR 	RW }
	listeReg 	{ ISR IDR LPR CR MR MDR IMR IER HSR TR  }

}
array set SDRAMC1_att {
	MDR 	{ R AT91C_SDRAMC1_MDR 	RO }
	IMR 	{ R AT91C_SDRAMC1_IMR 	RO }
	IER 	{ R AT91C_SDRAMC1_IER 	WO }
	HSR 	{ R AT91C_SDRAMC1_HSR 	RW }
	TR 	{ R AT91C_SDRAMC1_TR 	RW }
	ISR 	{ R AT91C_SDRAMC1_ISR 	RO }
	IDR 	{ R AT91C_SDRAMC1_IDR 	WO }
	LPR 	{ R AT91C_SDRAMC1_LPR 	RW }
	CR 	{ R AT91C_SDRAMC1_CR 	RW }
	MR 	{ R AT91C_SDRAMC1_MR 	RW }
	listeReg 	{ MDR IMR IER HSR TR ISR IDR LPR CR MR  }

}

# ========== Peripheral attributes for USART peripheral ========== 
array set US0_att {
	TTGR 	{ R AT91C_US0_TTGR 	RW }
	BRGR 	{ R AT91C_US0_BRGR 	RW }
	RHR 	{ R AT91C_US0_RHR 	RO }
	IMR 	{ R AT91C_US0_IMR 	RO }
	IER 	{ R AT91C_US0_IER 	WO }
	RTOR 	{ R AT91C_US0_RTOR 	RW }
	THR 	{ R AT91C_US0_THR 	WO }
	FIDI 	{ R AT91C_US0_FIDI 	RW }
	CR 	{ R AT91C_US0_CR 	WO }
	IF 	{ R AT91C_US0_IF 	RW }
	NER 	{ R AT91C_US0_NER 	RO }
	MR 	{ R AT91C_US0_MR 	RW }
	IDR 	{ R AT91C_US0_IDR 	WO }
	CSR 	{ R AT91C_US0_CSR 	RO }
	listeReg 	{ TTGR BRGR RHR IMR IER RTOR THR FIDI CR IF NER MR IDR CSR  }

}
array set US1_att {
	IF 	{ R AT91C_US1_IF 	RW }
	NER 	{ R AT91C_US1_NER 	RO }
	FIDI 	{ R AT91C_US1_FIDI 	RW }
	IMR 	{ R AT91C_US1_IMR 	RO }
	IER 	{ R AT91C_US1_IER 	WO }
	CR 	{ R AT91C_US1_CR 	WO }
	MR 	{ R AT91C_US1_MR 	RW }
	IDR 	{ R AT91C_US1_IDR 	WO }
	CSR 	{ R AT91C_US1_CSR 	RO }
	THR 	{ R AT91C_US1_THR 	WO }
	RTOR 	{ R AT91C_US1_RTOR 	RW }
	RHR 	{ R AT91C_US1_RHR 	RO }
	BRGR 	{ R AT91C_US1_BRGR 	RW }
	TTGR 	{ R AT91C_US1_TTGR 	RW }
	listeReg 	{ IF NER FIDI IMR IER CR MR IDR CSR THR RTOR RHR BRGR TTGR  }

}
array set US2_att {
	RTOR 	{ R AT91C_US2_RTOR 	RW }
	THR 	{ R AT91C_US2_THR 	WO }
	CSR 	{ R AT91C_US2_CSR 	RO }
	FIDI 	{ R AT91C_US2_FIDI 	RW }
	TTGR 	{ R AT91C_US2_TTGR 	RW }
	MR 	{ R AT91C_US2_MR 	RW }
	IDR 	{ R AT91C_US2_IDR 	WO }
	NER 	{ R AT91C_US2_NER 	RO }
	CR 	{ R AT91C_US2_CR 	WO }
	IER 	{ R AT91C_US2_IER 	WO }
	IMR 	{ R AT91C_US2_IMR 	RO }
	RHR 	{ R AT91C_US2_RHR 	RO }
	BRGR 	{ R AT91C_US2_BRGR 	RW }
	IF 	{ R AT91C_US2_IF 	RW }
	listeReg 	{ RTOR THR CSR FIDI TTGR MR IDR NER CR IER IMR RHR BRGR IF  }

}

# ========== Peripheral attributes for WDTC peripheral ========== 
array set WDTC_att {
	WDMR 	{ R AT91C_WDTC_WDMR 	RW }
	WDSR 	{ R AT91C_WDTC_WDSR 	RO }
	WDCR 	{ R AT91C_WDTC_WDCR 	WO }
	listeReg 	{ WDMR WDSR WDCR  }

}

# ========== Peripheral attributes for SMC peripheral ========== 
array set SMC0_att {
	SETUP7 	{ R AT91C_SMC0_SETUP7 	RW }
	CYCLE6 	{ R AT91C_SMC0_CYCLE6 	RW }
	SETUP6 	{ R AT91C_SMC0_SETUP6 	RW }
	CYCLE5 	{ R AT91C_SMC0_CYCLE5 	RW }
	SETUP5 	{ R AT91C_SMC0_SETUP5 	RW }
	SETUP2 	{ R AT91C_SMC0_SETUP2 	RW }
	CYCLE1 	{ R AT91C_SMC0_CYCLE1 	RW }
	SETUP1 	{ R AT91C_SMC0_SETUP1 	RW }
	CYCLE0 	{ R AT91C_SMC0_CYCLE0 	RW }
	SETUP0 	{ R AT91C_SMC0_SETUP0 	RW }
	CTRL7 	{ R AT91C_SMC0_CTRL7 	RW }
	PULSE7 	{ R AT91C_SMC0_PULSE7 	RW }
	CTRL6 	{ R AT91C_SMC0_CTRL6 	RW }
	PULSE6 	{ R AT91C_SMC0_PULSE6 	RW }
	PULSE3 	{ R AT91C_SMC0_PULSE3 	RW }
	CTRL2 	{ R AT91C_SMC0_CTRL2 	RW }
	PULSE2 	{ R AT91C_SMC0_PULSE2 	RW }
	CTRL1 	{ R AT91C_SMC0_CTRL1 	RW }
	PULSE1 	{ R AT91C_SMC0_PULSE1 	RW }
	CYCLE7 	{ R AT91C_SMC0_CYCLE7 	RW }
	CYCLE2 	{ R AT91C_SMC0_CYCLE2 	RW }
	SETUP3 	{ R AT91C_SMC0_SETUP3 	RW }
	CYCLE3 	{ R AT91C_SMC0_CYCLE3 	RW }
	SETUP4 	{ R AT91C_SMC0_SETUP4 	RW }
	CTRL3 	{ R AT91C_SMC0_CTRL3 	RW }
	PULSE4 	{ R AT91C_SMC0_PULSE4 	RW }
	CYCLE4 	{ R AT91C_SMC0_CYCLE4 	RW }
	CTRL5 	{ R AT91C_SMC0_CTRL5 	RW }
	PULSE5 	{ R AT91C_SMC0_PULSE5 	RW }
	CTRL4 	{ R AT91C_SMC0_CTRL4 	RW }
	CTRL0 	{ R AT91C_SMC0_CTRL0 	RW }
	PULSE0 	{ R AT91C_SMC0_PULSE0 	RW }
	listeReg 	{ SETUP7 CYCLE6 SETUP6 CYCLE5 SETUP5 SETUP2 CYCLE1 SETUP1 CYCLE0 SETUP0 CTRL7 PULSE7 CTRL6 PULSE6 PULSE3 CTRL2 PULSE2 CTRL1 PULSE1 CYCLE7 CYCLE2 SETUP3 CYCLE3 SETUP4 CTRL3 PULSE4 CYCLE4 CTRL5 PULSE5 CTRL4 CTRL0 PULSE0  }

}
array set SMC1_att {
	SETUP2 	{ R AT91C_SMC1_SETUP2 	RW }
	CTRL7 	{ R AT91C_SMC1_CTRL7 	RW }
	SETUP3 	{ R AT91C_SMC1_SETUP3 	RW }
	PULSE4 	{ R AT91C_SMC1_PULSE4 	RW }
	PULSE3 	{ R AT91C_SMC1_PULSE3 	RW }
	CYCLE5 	{ R AT91C_SMC1_CYCLE5 	RW }
	CYCLE4 	{ R AT91C_SMC1_CYCLE4 	RW }
	SETUP1 	{ R AT91C_SMC1_SETUP1 	RW }
	SETUP0 	{ R AT91C_SMC1_SETUP0 	RW }
	CTRL6 	{ R AT91C_SMC1_CTRL6 	RW }
	CTRL5 	{ R AT91C_SMC1_CTRL5 	RW }
	PULSE1 	{ R AT91C_SMC1_PULSE1 	RW }
	PULSE0 	{ R AT91C_SMC1_PULSE0 	RW }
	SETUP7 	{ R AT91C_SMC1_SETUP7 	RW }
	CYCLE1 	{ R AT91C_SMC1_CYCLE1 	RW }
	PULSE2 	{ R AT91C_SMC1_PULSE2 	RW }
	CYCLE2 	{ R AT91C_SMC1_CYCLE2 	RW }
	CYCLE3 	{ R AT91C_SMC1_CYCLE3 	RW }
	CTRL3 	{ R AT91C_SMC1_CTRL3 	RW }
	CTRL2 	{ R AT91C_SMC1_CTRL2 	RW }
	CTRL4 	{ R AT91C_SMC1_CTRL4 	RW }
	SETUP4 	{ R AT91C_SMC1_SETUP4 	RW }
	SETUP5 	{ R AT91C_SMC1_SETUP5 	RW }
	SETUP6 	{ R AT91C_SMC1_SETUP6 	RW }
	CYCLE0 	{ R AT91C_SMC1_CYCLE0 	RW }
	PULSE5 	{ R AT91C_SMC1_PULSE5 	RW }
	PULSE6 	{ R AT91C_SMC1_PULSE6 	RW }
	PULSE7 	{ R AT91C_SMC1_PULSE7 	RW }
	CTRL0 	{ R AT91C_SMC1_CTRL0 	RW }
	CTRL1 	{ R AT91C_SMC1_CTRL1 	RW }
	CYCLE6 	{ R AT91C_SMC1_CYCLE6 	RW }
	CYCLE7 	{ R AT91C_SMC1_CYCLE7 	RW }
	listeReg 	{ SETUP2 CTRL7 SETUP3 PULSE4 PULSE3 CYCLE5 CYCLE4 SETUP1 SETUP0 CTRL6 CTRL5 PULSE1 PULSE0 SETUP7 CYCLE1 PULSE2 CYCLE2 CYCLE3 CTRL3 CTRL2 CTRL4 SETUP4 SETUP5 SETUP6 CYCLE0 PULSE5 PULSE6 PULSE7 CTRL0 CTRL1 CYCLE6 CYCLE7  }

}

# ========== Peripheral attributes for ECC peripheral ========== 
array set HECC0_att {
	NPR 	{ R AT91C_HECC0_NPR 	RO }
	SR 	{ R AT91C_HECC0_SR 	RO }
	CR 	{ R AT91C_HECC0_CR 	WO }
	VR 	{ R AT91C_HECC0_VR 	RO }
	PR 	{ R AT91C_HECC0_PR 	RO }
	MR 	{ R AT91C_HECC0_MR 	RW }
	listeReg 	{ NPR SR CR VR PR MR  }

}
array set HECC1_att {
	PR 	{ R AT91C_HECC1_PR 	RO }
	MR 	{ R AT91C_HECC1_MR 	RW }
	NPR 	{ R AT91C_HECC1_NPR 	RO }
	SR 	{ R AT91C_HECC1_SR 	RO }
	CR 	{ R AT91C_HECC1_CR 	WO }
	VR 	{ R AT91C_HECC1_VR 	RO }
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

# ========== Peripheral attributes for CAN peripheral ========== 
array set CAN_att {
	TCR 	{ R AT91C_CAN_TCR 	WO }
	IDR 	{ R AT91C_CAN_IDR 	WO }
	MR 	{ R AT91C_CAN_MR 	RW }
	VR 	{ R AT91C_CAN_VR 	RO }
	IER 	{ R AT91C_CAN_IER 	WO }
	IMR 	{ R AT91C_CAN_IMR 	RO }
	BR 	{ R AT91C_CAN_BR 	RW }
	TIMESTP 	{ R AT91C_CAN_TIMESTP 	RO }
	SR 	{ R AT91C_CAN_SR 	RO }
	TIM 	{ R AT91C_CAN_TIM 	RO }
	ECR 	{ R AT91C_CAN_ECR 	RO }
	ACR 	{ R AT91C_CAN_ACR 	WO }
	listeReg 	{ TCR IDR MR VR IER IMR BR TIMESTP SR TIM ECR ACR  }

}

# ========== Peripheral attributes for DBGU peripheral ========== 
array set DBGU_att {
	MR 	{ R AT91C_DBGU_MR 	RW }
	FNTR 	{ R AT91C_DBGU_FNTR 	RW }
	CIDR 	{ R AT91C_DBGU_CIDR 	RO }
	BRGR 	{ R AT91C_DBGU_BRGR 	RW }
	RHR 	{ R AT91C_DBGU_RHR 	RO }
	IMR 	{ R AT91C_DBGU_IMR 	RO }
	IER 	{ R AT91C_DBGU_IER 	WO }
	CR 	{ R AT91C_DBGU_CR 	WO }
	EXID 	{ R AT91C_DBGU_EXID 	RO }
	THR 	{ R AT91C_DBGU_THR 	WO }
	CSR 	{ R AT91C_DBGU_CSR 	RO }
	IDR 	{ R AT91C_DBGU_IDR 	WO }
	listeReg 	{ MR FNTR CIDR BRGR RHR IMR IER CR EXID THR CSR IDR  }

}

# ========== Peripheral attributes for PWMC_CH peripheral ========== 
array set PWMC_CH0_att {
	Reserved 	{ R AT91C_PWMC_CH0_Reserved 	WO  3 }
	CCNTR 	{ R AT91C_PWMC_CH0_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH0_CDTYR 	RW }
	CUPDR 	{ R AT91C_PWMC_CH0_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH0_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH0_CMR 	RW }
	listeReg 	{ Reserved CCNTR CDTYR CUPDR CPRDR CMR  }

}
array set PWMC_CH1_att {
	Reserved 	{ R AT91C_PWMC_CH1_Reserved 	WO  3 }
	CCNTR 	{ R AT91C_PWMC_CH1_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH1_CDTYR 	RW }
	CUPDR 	{ R AT91C_PWMC_CH1_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH1_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH1_CMR 	RW }
	listeReg 	{ Reserved CCNTR CDTYR CUPDR CPRDR CMR  }

}
array set PWMC_CH2_att {
	Reserved 	{ R AT91C_PWMC_CH2_Reserved 	WO  3 }
	CCNTR 	{ R AT91C_PWMC_CH2_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH2_CDTYR 	RW }
	CUPDR 	{ R AT91C_PWMC_CH2_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH2_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH2_CMR 	RW }
	listeReg 	{ Reserved CCNTR CDTYR CUPDR CPRDR CMR  }

}
array set PWMC_CH3_att {
	CDTYR 	{ R AT91C_PWMC_CH3_CDTYR 	RW }
	CUPDR 	{ R AT91C_PWMC_CH3_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH3_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH3_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH3_Reserved 	WO  3 }
	CCNTR 	{ R AT91C_PWMC_CH3_CCNTR 	RO }
	listeReg 	{ CDTYR CUPDR CPRDR CMR Reserved CCNTR  }

}

# ========== Peripheral attributes for SHDWC peripheral ========== 
array set SHDWC_att {
	SHMR 	{ R AT91C_SHDWC_SHMR 	RW }
	SHSR 	{ R AT91C_SHDWC_SHSR 	RO }
	SHCR 	{ R AT91C_SHDWC_SHCR 	WO }
	listeReg 	{ SHMR SHSR SHCR  }

}

# ========== Peripheral attributes for SSC peripheral ========== 
array set SSC0_att {
	IDR 	{ R AT91C_SSC0_IDR 	WO }
	SR 	{ R AT91C_SSC0_SR 	RO }
	RSHR 	{ R AT91C_SSC0_RSHR 	RO }
	RHR 	{ R AT91C_SSC0_RHR 	RO }
	TCMR 	{ R AT91C_SSC0_TCMR 	RW }
	RCMR 	{ R AT91C_SSC0_RCMR 	RW }
	CR 	{ R AT91C_SSC0_CR 	WO }
	IMR 	{ R AT91C_SSC0_IMR 	RO }
	IER 	{ R AT91C_SSC0_IER 	WO }
	TSHR 	{ R AT91C_SSC0_TSHR 	RW }
	THR 	{ R AT91C_SSC0_THR 	WO }
	TFMR 	{ R AT91C_SSC0_TFMR 	RW }
	RFMR 	{ R AT91C_SSC0_RFMR 	RW }
	CMR 	{ R AT91C_SSC0_CMR 	RW }
	listeReg 	{ IDR SR RSHR RHR TCMR RCMR CR IMR IER TSHR THR TFMR RFMR CMR  }

}
array set SSC1_att {
	IDR 	{ R AT91C_SSC1_IDR 	WO }
	SR 	{ R AT91C_SSC1_SR 	RO }
	RSHR 	{ R AT91C_SSC1_RSHR 	RO }
	RHR 	{ R AT91C_SSC1_RHR 	RO }
	TCMR 	{ R AT91C_SSC1_TCMR 	RW }
	RCMR 	{ R AT91C_SSC1_RCMR 	RW }
	CR 	{ R AT91C_SSC1_CR 	WO }
	IMR 	{ R AT91C_SSC1_IMR 	RO }
	IER 	{ R AT91C_SSC1_IER 	WO }
	TSHR 	{ R AT91C_SSC1_TSHR 	RW }
	THR 	{ R AT91C_SSC1_THR 	WO }
	TFMR 	{ R AT91C_SSC1_TFMR 	RW }
	RFMR 	{ R AT91C_SSC1_RFMR 	RW }
	CMR 	{ R AT91C_SSC1_CMR 	RW }
	listeReg 	{ IDR SR RSHR RHR TCMR RCMR CR IMR IER TSHR THR TFMR RFMR CMR  }

}

# ========== Peripheral attributes for TCB peripheral ========== 
array set TCB0_att {
	BCR 	{ R AT91C_TCB0_BCR 	WO }
	BMR 	{ R AT91C_TCB0_BMR 	RW }
	listeReg 	{ BCR BMR  }

}
array set TCB1_att {
	BCR 	{ R AT91C_TCB1_BCR 	WO }
	BMR 	{ R AT91C_TCB1_BMR 	RW }
	listeReg 	{ BCR BMR  }

}
array set TCB2_att {
	BMR 	{ R AT91C_TCB2_BMR 	RW }
	BCR 	{ R AT91C_TCB2_BCR 	WO }
	listeReg 	{ BMR BCR  }

}

# ========== Peripheral attributes for PWMC peripheral ========== 
array set PWMC_att {
	IMR 	{ R AT91C_PWMC_IMR 	RO }
	IER 	{ R AT91C_PWMC_IER 	WO }
	MR 	{ R AT91C_PWMC_MR 	RW }
	DIS 	{ R AT91C_PWMC_DIS 	WO }
	VR 	{ R AT91C_PWMC_VR 	RO }
	IDR 	{ R AT91C_PWMC_IDR 	WO }
	ISR 	{ R AT91C_PWMC_ISR 	RO }
	ENA 	{ R AT91C_PWMC_ENA 	WO }
	SR 	{ R AT91C_PWMC_SR 	RO }
	listeReg 	{ IMR IER MR DIS VR IDR ISR ENA SR  }

}

# ========== Peripheral attributes for LCDC peripheral ========== 
array set LCDC_att {
	ITR 	{ R AT91C_LCDC_ITR 	WO }
	TIM1 	{ R AT91C_LCDC_TIM1 	RW }
	BA1 	{ R AT91C_LCDC_BA1 	RW }
	FIFO 	{ R AT91C_LCDC_FIFO 	RW }
	BA2 	{ R AT91C_LCDC_BA2 	RW }
	FRMA2 	{ R AT91C_LCDC_FRMA2 	RO }
	3 	{ R AT91C_LCDC_DP2_3 	RW }
	MVAL 	{ R AT91C_LCDC_MVAL 	RW }
	FRMCFG 	{ R AT91C_LCDC_FRMCFG 	RW }
	ENTRY 	{ R AT91C_LCDC_LUT_ENTRY 	RW 256 }
	PWRCON 	{ R AT91C_LCDC_PWRCON 	RW }
	7 	{ R AT91C_LCDC_DP5_7 	RW }
	2 	{ R AT91C_LCDC_DP1_2 	RW }
	IMR 	{ R AT91C_LCDC_IMR 	RO }
	CTRSTCON 	{ R AT91C_LCDC_CTRSTCON 	RW }
	4 	{ R AT91C_LCDC_DP3_4 	RW }
	IRR 	{ R AT91C_LCDC_IRR 	RW }
	ISR 	{ R AT91C_LCDC_ISR 	RO }
	CTRSTVAL 	{ R AT91C_LCDC_CTRSTVAL 	RW }
	TIM2 	{ R AT91C_LCDC_TIM2 	RW }
	ICR 	{ R AT91C_LCDC_ICR 	WO }
	LCDFRCFG 	{ R AT91C_LCDC_LCDFRCFG 	RW }
	FRMP1 	{ R AT91C_LCDC_FRMP1 	RO }
	DMACON 	{ R AT91C_LCDC_DMACON 	RW }
	FRMP2 	{ R AT91C_LCDC_FRMP2 	RO }
	7 	{ R AT91C_LCDC_DP4_7 	RW }
	DMA2DCFG 	{ R AT91C_LCDC_DMA2DCFG 	RW }
	FRMA1 	{ R AT91C_LCDC_FRMA1 	RO }
	5 	{ R AT91C_LCDC_DP3_5 	RW }
	5 	{ R AT91C_LCDC_DP4_5 	RW }
	7 	{ R AT91C_LCDC_DP6_7 	RW }
	IER 	{ R AT91C_LCDC_IER 	WO }
	LCDCON1 	{ R AT91C_LCDC_LCDCON1 	RW }
	GPR 	{ R AT91C_LCDC_GPR 	RW }
	IDR 	{ R AT91C_LCDC_IDR 	WO }
	LCDCON2 	{ R AT91C_LCDC_LCDCON2 	RW }
	listeReg 	{ ITR TIM1 BA1 FIFO BA2 FRMA2 3 MVAL FRMCFG ENTRY PWRCON 7 2 IMR CTRSTCON 4 IRR ISR CTRSTVAL TIM2 ICR LCDFRCFG FRMP1 DMACON FRMP2 7 DMA2DCFG FRMA1 5 5 7 IER LCDCON1 GPR IDR LCDCON2  }

}

# ========== Peripheral attributes for PITC peripheral ========== 
array set PITC_att {
	PIIR 	{ R AT91C_PITC_PIIR 	RO }
	PISR 	{ R AT91C_PITC_PISR 	RO }
	PIVR 	{ R AT91C_PITC_PIVR 	RO }
	PIMR 	{ R AT91C_PITC_PIMR 	RW }
	listeReg 	{ PIIR PISR PIVR PIMR  }

}

# ========== Peripheral attributes for TC peripheral ========== 
array set TC0_att {
	IDR 	{ R AT91C_TC0_IDR 	WO }
	SR 	{ R AT91C_TC0_SR 	RO }
	RB 	{ R AT91C_TC0_RB 	RW }
	CV 	{ R AT91C_TC0_CV 	RW }
	CCR 	{ R AT91C_TC0_CCR 	WO }
	IMR 	{ R AT91C_TC0_IMR 	RO }
	IER 	{ R AT91C_TC0_IER 	WO }
	RC 	{ R AT91C_TC0_RC 	RW }
	RA 	{ R AT91C_TC0_RA 	RW }
	CMR 	{ R AT91C_TC0_CMR 	RW }
	listeReg 	{ IDR SR RB CV CCR IMR IER RC RA CMR  }

}
array set TC1_att {
	IDR 	{ R AT91C_TC1_IDR 	WO }
	SR 	{ R AT91C_TC1_SR 	RO }
	RB 	{ R AT91C_TC1_RB 	RW }
	CV 	{ R AT91C_TC1_CV 	RW }
	CCR 	{ R AT91C_TC1_CCR 	WO }
	IMR 	{ R AT91C_TC1_IMR 	RO }
	IER 	{ R AT91C_TC1_IER 	WO }
	RC 	{ R AT91C_TC1_RC 	RW }
	RA 	{ R AT91C_TC1_RA 	RW }
	CMR 	{ R AT91C_TC1_CMR 	RW }
	listeReg 	{ IDR SR RB CV CCR IMR IER RC RA CMR  }

}
array set TC2_att {
	IDR 	{ R AT91C_TC2_IDR 	WO }
	SR 	{ R AT91C_TC2_SR 	RO }
	RB 	{ R AT91C_TC2_RB 	RW }
	CV 	{ R AT91C_TC2_CV 	RW }
	CCR 	{ R AT91C_TC2_CCR 	WO }
	IMR 	{ R AT91C_TC2_IMR 	RO }
	IER 	{ R AT91C_TC2_IER 	WO }
	RC 	{ R AT91C_TC2_RC 	RW }
	RA 	{ R AT91C_TC2_RA 	RW }
	CMR 	{ R AT91C_TC2_CMR 	RW }
	listeReg 	{ IDR SR RB CV CCR IMR IER RC RA CMR  }

}

# ========== Peripheral attributes for PMC peripheral ========== 
array set PMC_att {
	SCSR 	{ R AT91C_PMC_SCSR 	RO }
	SCER 	{ R AT91C_PMC_SCER 	WO }
	IMR 	{ R AT91C_PMC_IMR 	RO }
	IDR 	{ R AT91C_PMC_IDR 	WO }
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
	listeReg 	{ SCSR SCER IMR IDR PCDR SCDR SR IER MCKR PLLAR MOR PCER PCSR PLLBR MCFR PCKR  }

}

# ========== Peripheral attributes for TBOX peripheral ========== 
array set TBOX_att {
	GPSSIGQB 	{ R AT91C_TBOX_GPSSIGQB 	W }
	PIOC 	{ R AT91C_TBOX_PIOC 	R }
	PIOEENABLEFORCE 	{ R AT91C_TBOX_PIOEENABLEFORCE 	RW }
	PWM1 	{ R AT91C_TBOX_PWM1 	RW }
	PIOD 	{ R AT91C_TBOX_PIOD 	R }
	PIOAPUN 	{ R AT91C_TBOX_PIOAPUN 	RW }
	STOPAPBSPY 	{ R AT91C_TBOX_STOPAPBSPY 	RW }
	PWM2 	{ R AT91C_TBOX_PWM2 	RW }
	GPSACQDATA 	{ R AT91C_TBOX_GPSACQDATA 	R }
	MAC 	{ R AT91C_TBOX_MAC 	RW }
	GPSDUMPRES 	{ R AT91C_TBOX_GPSDUMPRES 	W }
	GPSSYNCHRO 	{ R AT91C_TBOX_GPSSYNCHRO 	W }
	PIOEPUN 	{ R AT91C_TBOX_PIOEPUN 	RW }
	GPSSIGIA 	{ R AT91C_TBOX_GPSSIGIA 	W }
	PIOCENABLEFORCE 	{ R AT91C_TBOX_PIOCENABLEFORCE 	RW }
	PIOAENABLEFORCE 	{ R AT91C_TBOX_PIOAENABLEFORCE 	RW }
	GPSSIGQA 	{ R AT91C_TBOX_GPSSIGQA 	W }
	PIOEFORCEVALUE 	{ R AT91C_TBOX_PIOEFORCEVALUE 	RW }
	PIOCFORCEVALUE 	{ R AT91C_TBOX_PIOCFORCEVALUE 	RW }
	PIOA 	{ R AT91C_TBOX_PIOA 	R }
	PIOE 	{ R AT91C_TBOX_PIOE 	R }
	AC97START 	{ R AT91C_TBOX_AC97START 	RW }
	PWMSTART 	{ R AT91C_TBOX_PWMSTART 	RW }
	USBDEV 	{ R AT91C_TBOX_USBDEV 	RW }
	GPSRAND 	{ R AT91C_TBOX_GPSRAND 	W }
	KBD 	{ R AT91C_TBOX_KBD 	RW }
	GPSACQSTATUS 	{ R AT91C_TBOX_GPSACQSTATUS 	R }
	PIOBPUN 	{ R AT91C_TBOX_PIOBPUN 	RW }
	SHMCTRL 	{ R AT91C_TBOX_SHMCTRL 	RW }
	PIOAFORCEVALUE 	{ R AT91C_TBOX_PIOAFORCEVALUE 	RW }
	PIOCPUN 	{ R AT91C_TBOX_PIOCPUN 	RW }
	DMAEXTREQ 	{ R AT91C_TBOX_DMAEXTREQ 	R }
	PIODPUN 	{ R AT91C_TBOX_PIODPUN 	RW }
	PIOBENABLEFORCE 	{ R AT91C_TBOX_PIOBENABLEFORCE 	RW }
	PIODENABLEFORCE 	{ R AT91C_TBOX_PIODENABLEFORCE 	RW }
	GPSSIGIB 	{ R AT91C_TBOX_GPSSIGIB 	W }
	GPSSIGFILE 	{ R AT91C_TBOX_GPSSIGFILE 	W }
	PIOBFORCEVALUE 	{ R AT91C_TBOX_PIOBFORCEVALUE 	RW }
	PIODFORCEVALUE 	{ R AT91C_TBOX_PIODFORCEVALUE 	RW }
	PIOB 	{ R AT91C_TBOX_PIOB 	R }
	listeReg 	{ GPSSIGQB PIOC PIOEENABLEFORCE PWM1 PIOD PIOAPUN STOPAPBSPY PWM2 GPSACQDATA MAC GPSDUMPRES GPSSYNCHRO PIOEPUN GPSSIGIA PIOCENABLEFORCE PIOAENABLEFORCE GPSSIGQA PIOEFORCEVALUE PIOCFORCEVALUE PIOA PIOE AC97START PWMSTART USBDEV GPSRAND KBD GPSACQSTATUS PIOBPUN SHMCTRL PIOAFORCEVALUE PIOCPUN DMAEXTREQ PIODPUN PIOBENABLEFORCE PIODENABLEFORCE GPSSIGIB GPSSIGFILE PIOBFORCEVALUE PIODFORCEVALUE PIOB  }

}

# ========== Peripheral attributes for AC97C peripheral ========== 
array set AC97C_att {
	VERSION 	{ R AT91C_AC97C_VERSION 	RO }
	IMR 	{ R AT91C_AC97C_IMR 	RO }
	IER 	{ R AT91C_AC97C_IER 	WO }
	COMR 	{ R AT91C_AC97C_COMR 	RW }
	COTHR 	{ R AT91C_AC97C_COTHR 	WO }
	OCA 	{ R AT91C_AC97C_OCA 	RW }
	IDR 	{ R AT91C_AC97C_IDR 	WO }
	CASR 	{ R AT91C_AC97C_CASR 	RO }
	CARHR 	{ R AT91C_AC97C_CARHR 	RO }
	ICA 	{ R AT91C_AC97C_ICA 	RW }
	MR 	{ R AT91C_AC97C_MR 	RW }
	CATHR 	{ R AT91C_AC97C_CATHR 	WO }
	CAMR 	{ R AT91C_AC97C_CAMR 	RW }
	CBTHR 	{ R AT91C_AC97C_CBTHR 	WO }
	CBMR 	{ R AT91C_AC97C_CBMR 	RW }
	CBRHR 	{ R AT91C_AC97C_CBRHR 	RO }
	CBSR 	{ R AT91C_AC97C_CBSR 	RO }
	CORHR 	{ R AT91C_AC97C_CORHR 	RO }
	COSR 	{ R AT91C_AC97C_COSR 	RO }
	SR 	{ R AT91C_AC97C_SR 	RO }
	listeReg 	{ VERSION IMR IER COMR COTHR OCA IDR CASR CARHR ICA MR CATHR CAMR CBTHR CBMR CBRHR CBSR CORHR COSR SR  }

}

# ========== Peripheral attributes for CAN_MB peripheral ========== 
array set CAN_MB0_att {
	MDH 	{ R AT91C_CAN_MB0_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB0_MSR 	RO }
	MID 	{ R AT91C_CAN_MB0_MID 	RW }
	MMR 	{ R AT91C_CAN_MB0_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB0_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB0_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB0_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB0_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN_MB1_att {
	MDH 	{ R AT91C_CAN_MB1_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB1_MSR 	RO }
	MID 	{ R AT91C_CAN_MB1_MID 	RW }
	MMR 	{ R AT91C_CAN_MB1_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB1_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB1_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB1_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB1_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN_MB2_att {
	MDH 	{ R AT91C_CAN_MB2_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB2_MSR 	RO }
	MID 	{ R AT91C_CAN_MB2_MID 	RW }
	MMR 	{ R AT91C_CAN_MB2_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB2_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB2_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB2_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB2_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN_MB3_att {
	MDH 	{ R AT91C_CAN_MB3_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB3_MSR 	RO }
	MID 	{ R AT91C_CAN_MB3_MID 	RW }
	MMR 	{ R AT91C_CAN_MB3_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB3_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB3_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB3_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB3_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN_MB4_att {
	MID 	{ R AT91C_CAN_MB4_MID 	RW }
	MMR 	{ R AT91C_CAN_MB4_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB4_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB4_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB4_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB4_MAM 	RW }
	MSR 	{ R AT91C_CAN_MB4_MSR 	RO }
	MDH 	{ R AT91C_CAN_MB4_MDH 	RW }
	listeReg 	{ MID MMR MCR MDL MFID MAM MSR MDH  }

}
array set CAN_MB5_att {
	MCR 	{ R AT91C_CAN_MB5_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB5_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB5_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB5_MAM 	RW }
	MDH 	{ R AT91C_CAN_MB5_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB5_MSR 	RO }
	MID 	{ R AT91C_CAN_MB5_MID 	RW }
	MMR 	{ R AT91C_CAN_MB5_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN_MB6_att {
	MCR 	{ R AT91C_CAN_MB6_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB6_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB6_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB6_MAM 	RW }
	MDH 	{ R AT91C_CAN_MB6_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB6_MSR 	RO }
	MID 	{ R AT91C_CAN_MB6_MID 	RW }
	MMR 	{ R AT91C_CAN_MB6_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN_MB7_att {
	MCR 	{ R AT91C_CAN_MB7_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB7_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB7_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB7_MAM 	RW }
	MDH 	{ R AT91C_CAN_MB7_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB7_MSR 	RO }
	MID 	{ R AT91C_CAN_MB7_MID 	RW }
	MMR 	{ R AT91C_CAN_MB7_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN_MB8_att {
	MCR 	{ R AT91C_CAN_MB8_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB8_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB8_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB8_MAM 	RW }
	MMR 	{ R AT91C_CAN_MB8_MMR 	RW }
	MDH 	{ R AT91C_CAN_MB8_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB8_MSR 	RO }
	MID 	{ R AT91C_CAN_MB8_MID 	RW }
	listeReg 	{ MCR MDL MFID MAM MMR MDH MSR MID  }

}
array set CAN_MB9_att {
	MCR 	{ R AT91C_CAN_MB9_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB9_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB9_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB9_MAM 	RW }
	MDH 	{ R AT91C_CAN_MB9_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB9_MSR 	RO }
	MID 	{ R AT91C_CAN_MB9_MID 	RW }
	MMR 	{ R AT91C_CAN_MB9_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN_MB10_att {
	MCR 	{ R AT91C_CAN_MB10_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB10_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB10_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB10_MAM 	RW }
	MDH 	{ R AT91C_CAN_MB10_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB10_MSR 	RO }
	MID 	{ R AT91C_CAN_MB10_MID 	RW }
	MMR 	{ R AT91C_CAN_MB10_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN_MB11_att {
	MDH 	{ R AT91C_CAN_MB11_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB11_MSR 	RO }
	MID 	{ R AT91C_CAN_MB11_MID 	RW }
	MMR 	{ R AT91C_CAN_MB11_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB11_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB11_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB11_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB11_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN_MB12_att {
	MDH 	{ R AT91C_CAN_MB12_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB12_MSR 	RO }
	MID 	{ R AT91C_CAN_MB12_MID 	RW }
	MMR 	{ R AT91C_CAN_MB12_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB12_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB12_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB12_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB12_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN_MB13_att {
	MDH 	{ R AT91C_CAN_MB13_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB13_MSR 	RO }
	MID 	{ R AT91C_CAN_MB13_MID 	RW }
	MMR 	{ R AT91C_CAN_MB13_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB13_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB13_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB13_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB13_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN_MB14_att {
	MDH 	{ R AT91C_CAN_MB14_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB14_MSR 	RO }
	MID 	{ R AT91C_CAN_MB14_MID 	RW }
	MMR 	{ R AT91C_CAN_MB14_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB14_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB14_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB14_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB14_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN_MB15_att {
	MDH 	{ R AT91C_CAN_MB15_MDH 	RW }
	MSR 	{ R AT91C_CAN_MB15_MSR 	RO }
	MID 	{ R AT91C_CAN_MB15_MID 	RW }
	MMR 	{ R AT91C_CAN_MB15_MMR 	RW }
	MCR 	{ R AT91C_CAN_MB15_MCR 	WO }
	MDL 	{ R AT91C_CAN_MB15_MDL 	RW }
	MFID 	{ R AT91C_CAN_MB15_MFID 	RO }
	MAM 	{ R AT91C_CAN_MB15_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}

# ========== Peripheral attributes for RTTC peripheral ========== 
array set RTTC0_att {
	RTSR 	{ R AT91C_RTTC0_RTSR 	RO }
	RTAR 	{ R AT91C_RTTC0_RTAR 	RW }
	RTVR 	{ R AT91C_RTTC0_RTVR 	RO }
	RTMR 	{ R AT91C_RTTC0_RTMR 	RW }
	listeReg 	{ RTSR RTAR RTVR RTMR  }

}
array set RTTC1_att {
	RTSR 	{ R AT91C_RTTC1_RTSR 	RO }
	RTAR 	{ R AT91C_RTTC1_RTAR 	RW }
	RTVR 	{ R AT91C_RTTC1_RTVR 	RO }
	RTMR 	{ R AT91C_RTTC1_RTMR 	RW }
	listeReg 	{ RTSR RTAR RTVR RTMR  }

}

# ========== Peripheral attributes for PIO peripheral ========== 
array set PIOA_att {
	BSR 	{ R AT91C_PIOA_BSR 	WO }
	IDR 	{ R AT91C_PIOA_IDR 	WO }
	PDSR 	{ R AT91C_PIOA_PDSR 	RO }
	CODR 	{ R AT91C_PIOA_CODR 	WO }
	IFDR 	{ R AT91C_PIOA_IFDR 	WO }
	OWSR 	{ R AT91C_PIOA_OWSR 	RO }
	OWER 	{ R AT91C_PIOA_OWER 	WO }
	MDER 	{ R AT91C_PIOA_MDER 	WO }
	IMR 	{ R AT91C_PIOA_IMR 	RO }
	IER 	{ R AT91C_PIOA_IER 	WO }
	ODSR 	{ R AT91C_PIOA_ODSR 	RO }
	OWDR 	{ R AT91C_PIOA_OWDR 	WO }
	ISR 	{ R AT91C_PIOA_ISR 	RO }
	MDDR 	{ R AT91C_PIOA_MDDR 	WO }
	MDSR 	{ R AT91C_PIOA_MDSR 	RO }
	PER 	{ R AT91C_PIOA_PER 	WO }
	PSR 	{ R AT91C_PIOA_PSR 	RO }
	PPUER 	{ R AT91C_PIOA_PPUER 	WO }
	ODR 	{ R AT91C_PIOA_ODR 	WO }
	PDR 	{ R AT91C_PIOA_PDR 	WO }
	ABSR 	{ R AT91C_PIOA_ABSR 	RO }
	ASR 	{ R AT91C_PIOA_ASR 	WO }
	PPUSR 	{ R AT91C_PIOA_PPUSR 	RO }
	PPUDR 	{ R AT91C_PIOA_PPUDR 	WO }
	SODR 	{ R AT91C_PIOA_SODR 	WO }
	IFSR 	{ R AT91C_PIOA_IFSR 	RO }
	IFER 	{ R AT91C_PIOA_IFER 	WO }
	OSR 	{ R AT91C_PIOA_OSR 	RO }
	OER 	{ R AT91C_PIOA_OER 	WO }
	listeReg 	{ BSR IDR PDSR CODR IFDR OWSR OWER MDER IMR IER ODSR OWDR ISR MDDR MDSR PER PSR PPUER ODR PDR ABSR ASR PPUSR PPUDR SODR IFSR IFER OSR OER  }

}
array set PIOB_att {
	IMR 	{ R AT91C_PIOB_IMR 	RO }
	IER 	{ R AT91C_PIOB_IER 	WO }
	OWDR 	{ R AT91C_PIOB_OWDR 	WO }
	ISR 	{ R AT91C_PIOB_ISR 	RO }
	PPUDR 	{ R AT91C_PIOB_PPUDR 	WO }
	MDSR 	{ R AT91C_PIOB_MDSR 	RO }
	MDER 	{ R AT91C_PIOB_MDER 	WO }
	PER 	{ R AT91C_PIOB_PER 	WO }
	PSR 	{ R AT91C_PIOB_PSR 	RO }
	OER 	{ R AT91C_PIOB_OER 	WO }
	BSR 	{ R AT91C_PIOB_BSR 	WO }
	PPUER 	{ R AT91C_PIOB_PPUER 	WO }
	MDDR 	{ R AT91C_PIOB_MDDR 	WO }
	PDR 	{ R AT91C_PIOB_PDR 	WO }
	ODR 	{ R AT91C_PIOB_ODR 	WO }
	IFDR 	{ R AT91C_PIOB_IFDR 	WO }
	ABSR 	{ R AT91C_PIOB_ABSR 	RO }
	ASR 	{ R AT91C_PIOB_ASR 	WO }
	PPUSR 	{ R AT91C_PIOB_PPUSR 	RO }
	ODSR 	{ R AT91C_PIOB_ODSR 	RO }
	SODR 	{ R AT91C_PIOB_SODR 	WO }
	IFSR 	{ R AT91C_PIOB_IFSR 	RO }
	IFER 	{ R AT91C_PIOB_IFER 	WO }
	OSR 	{ R AT91C_PIOB_OSR 	RO }
	IDR 	{ R AT91C_PIOB_IDR 	WO }
	PDSR 	{ R AT91C_PIOB_PDSR 	RO }
	CODR 	{ R AT91C_PIOB_CODR 	WO }
	OWSR 	{ R AT91C_PIOB_OWSR 	RO }
	OWER 	{ R AT91C_PIOB_OWER 	WO }
	listeReg 	{ IMR IER OWDR ISR PPUDR MDSR MDER PER PSR OER BSR PPUER MDDR PDR ODR IFDR ABSR ASR PPUSR ODSR SODR IFSR IFER OSR IDR PDSR CODR OWSR OWER  }

}
array set PIOC_att {
	OWSR 	{ R AT91C_PIOC_OWSR 	RO }
	PPUSR 	{ R AT91C_PIOC_PPUSR 	RO }
	PPUDR 	{ R AT91C_PIOC_PPUDR 	WO }
	MDSR 	{ R AT91C_PIOC_MDSR 	RO }
	MDER 	{ R AT91C_PIOC_MDER 	WO }
	IMR 	{ R AT91C_PIOC_IMR 	RO }
	OSR 	{ R AT91C_PIOC_OSR 	RO }
	OER 	{ R AT91C_PIOC_OER 	WO }
	PSR 	{ R AT91C_PIOC_PSR 	RO }
	PER 	{ R AT91C_PIOC_PER 	WO }
	BSR 	{ R AT91C_PIOC_BSR 	WO }
	PPUER 	{ R AT91C_PIOC_PPUER 	WO }
	IFDR 	{ R AT91C_PIOC_IFDR 	WO }
	ODR 	{ R AT91C_PIOC_ODR 	WO }
	ABSR 	{ R AT91C_PIOC_ABSR 	RO }
	ASR 	{ R AT91C_PIOC_ASR 	WO }
	IFER 	{ R AT91C_PIOC_IFER 	WO }
	IFSR 	{ R AT91C_PIOC_IFSR 	RO }
	SODR 	{ R AT91C_PIOC_SODR 	WO }
	ODSR 	{ R AT91C_PIOC_ODSR 	RO }
	CODR 	{ R AT91C_PIOC_CODR 	WO }
	PDSR 	{ R AT91C_PIOC_PDSR 	RO }
	OWER 	{ R AT91C_PIOC_OWER 	WO }
	IER 	{ R AT91C_PIOC_IER 	WO }
	OWDR 	{ R AT91C_PIOC_OWDR 	WO }
	MDDR 	{ R AT91C_PIOC_MDDR 	WO }
	ISR 	{ R AT91C_PIOC_ISR 	RO }
	IDR 	{ R AT91C_PIOC_IDR 	WO }
	PDR 	{ R AT91C_PIOC_PDR 	WO }
	listeReg 	{ OWSR PPUSR PPUDR MDSR MDER IMR OSR OER PSR PER BSR PPUER IFDR ODR ABSR ASR IFER IFSR SODR ODSR CODR PDSR OWER IER OWDR MDDR ISR IDR PDR  }

}
array set PIOD_att {
	IFDR 	{ R AT91C_PIOD_IFDR 	WO }
	ODR 	{ R AT91C_PIOD_ODR 	WO }
	ABSR 	{ R AT91C_PIOD_ABSR 	RO }
	SODR 	{ R AT91C_PIOD_SODR 	WO }
	IFSR 	{ R AT91C_PIOD_IFSR 	RO }
	CODR 	{ R AT91C_PIOD_CODR 	WO }
	ODSR 	{ R AT91C_PIOD_ODSR 	RO }
	IER 	{ R AT91C_PIOD_IER 	WO }
	IMR 	{ R AT91C_PIOD_IMR 	RO }
	OWDR 	{ R AT91C_PIOD_OWDR 	WO }
	MDDR 	{ R AT91C_PIOD_MDDR 	WO }
	PDSR 	{ R AT91C_PIOD_PDSR 	RO }
	IDR 	{ R AT91C_PIOD_IDR 	WO }
	ISR 	{ R AT91C_PIOD_ISR 	RO }
	PDR 	{ R AT91C_PIOD_PDR 	WO }
	OWSR 	{ R AT91C_PIOD_OWSR 	RO }
	OWER 	{ R AT91C_PIOD_OWER 	WO }
	ASR 	{ R AT91C_PIOD_ASR 	WO }
	PPUSR 	{ R AT91C_PIOD_PPUSR 	RO }
	PPUDR 	{ R AT91C_PIOD_PPUDR 	WO }
	MDSR 	{ R AT91C_PIOD_MDSR 	RO }
	MDER 	{ R AT91C_PIOD_MDER 	WO }
	IFER 	{ R AT91C_PIOD_IFER 	WO }
	OSR 	{ R AT91C_PIOD_OSR 	RO }
	OER 	{ R AT91C_PIOD_OER 	WO }
	PSR 	{ R AT91C_PIOD_PSR 	RO }
	PER 	{ R AT91C_PIOD_PER 	WO }
	BSR 	{ R AT91C_PIOD_BSR 	WO }
	PPUER 	{ R AT91C_PIOD_PPUER 	WO }
	listeReg 	{ IFDR ODR ABSR SODR IFSR CODR ODSR IER IMR OWDR MDDR PDSR IDR ISR PDR OWSR OWER ASR PPUSR PPUDR MDSR MDER IFER OSR OER PSR PER BSR PPUER  }

}
array set PIOE_att {
	PDSR 	{ R AT91C_PIOE_PDSR 	RO }
	CODR 	{ R AT91C_PIOE_CODR 	WO }
	OWER 	{ R AT91C_PIOE_OWER 	WO }
	MDER 	{ R AT91C_PIOE_MDER 	WO }
	IMR 	{ R AT91C_PIOE_IMR 	RO }
	IER 	{ R AT91C_PIOE_IER 	WO }
	ODSR 	{ R AT91C_PIOE_ODSR 	RO }
	SODR 	{ R AT91C_PIOE_SODR 	WO }
	PER 	{ R AT91C_PIOE_PER 	WO }
	OWDR 	{ R AT91C_PIOE_OWDR 	WO }
	PPUER 	{ R AT91C_PIOE_PPUER 	WO }
	MDDR 	{ R AT91C_PIOE_MDDR 	WO }
	ISR 	{ R AT91C_PIOE_ISR 	RO }
	IDR 	{ R AT91C_PIOE_IDR 	WO }
	PDR 	{ R AT91C_PIOE_PDR 	WO }
	ODR 	{ R AT91C_PIOE_ODR 	WO }
	OWSR 	{ R AT91C_PIOE_OWSR 	RO }
	ABSR 	{ R AT91C_PIOE_ABSR 	RO }
	ASR 	{ R AT91C_PIOE_ASR 	WO }
	PPUSR 	{ R AT91C_PIOE_PPUSR 	RO }
	PPUDR 	{ R AT91C_PIOE_PPUDR 	WO }
	MDSR 	{ R AT91C_PIOE_MDSR 	RO }
	PSR 	{ R AT91C_PIOE_PSR 	RO }
	OER 	{ R AT91C_PIOE_OER 	WO }
	OSR 	{ R AT91C_PIOE_OSR 	RO }
	IFER 	{ R AT91C_PIOE_IFER 	WO }
	BSR 	{ R AT91C_PIOE_BSR 	WO }
	IFDR 	{ R AT91C_PIOE_IFDR 	WO }
	IFSR 	{ R AT91C_PIOE_IFSR 	RO }
	listeReg 	{ PDSR CODR OWER MDER IMR IER ODSR SODR PER OWDR PPUER MDDR ISR IDR PDR ODR OWSR ABSR ASR PPUSR PPUDR MDSR PSR OER OSR IFER BSR IFDR IFSR  }

}

# ========== Peripheral attributes for MCI peripheral ========== 
array set MCI0_att {
	TDR 	{ R AT91C_MCI0_TDR 	RO }
	CMDR 	{ R AT91C_MCI0_CMDR 	WO }
	IDR 	{ R AT91C_MCI0_IDR 	WO }
	SR 	{ R AT91C_MCI0_SR 	RO }
	RDR 	{ R AT91C_MCI0_RDR 	RO }
	VR 	{ R AT91C_MCI0_VR 	RO }
	MR 	{ R AT91C_MCI0_MR 	RW }
	SDCR 	{ R AT91C_MCI0_SDCR 	RW }
	IER 	{ R AT91C_MCI0_IER 	WO }
	IMR 	{ R AT91C_MCI0_IMR 	RO }
	CR 	{ R AT91C_MCI0_CR 	WO }
	DTOR 	{ R AT91C_MCI0_DTOR 	RW }
	ARGR 	{ R AT91C_MCI0_ARGR 	RW }
	BLKR 	{ R AT91C_MCI0_BLKR 	RW }
	RSPR 	{ R AT91C_MCI0_RSPR 	RO  4 }
	listeReg 	{ TDR CMDR IDR SR RDR VR MR SDCR IER IMR CR DTOR ARGR BLKR RSPR  }

}
array set MCI1_att {
	CR 	{ R AT91C_MCI1_CR 	WO }
	VR 	{ R AT91C_MCI1_VR 	RO }
	IMR 	{ R AT91C_MCI1_IMR 	RO }
	CMDR 	{ R AT91C_MCI1_CMDR 	WO }
	SDCR 	{ R AT91C_MCI1_SDCR 	RW }
	MR 	{ R AT91C_MCI1_MR 	RW }
	RDR 	{ R AT91C_MCI1_RDR 	RO }
	RSPR 	{ R AT91C_MCI1_RSPR 	RO  4 }
	BLKR 	{ R AT91C_MCI1_BLKR 	RW }
	ARGR 	{ R AT91C_MCI1_ARGR 	RW }
	TDR 	{ R AT91C_MCI1_TDR 	RO }
	IER 	{ R AT91C_MCI1_IER 	WO }
	DTOR 	{ R AT91C_MCI1_DTOR 	RW }
	SR 	{ R AT91C_MCI1_SR 	RO }
	IDR 	{ R AT91C_MCI1_IDR 	WO }
	listeReg 	{ CR VR IMR CMDR SDCR MR RDR RSPR BLKR ARGR TDR IER DTOR SR IDR  }

}

# ========== Peripheral attributes for UDP peripheral ========== 
array set UDP_att {
	RSTEP 	{ R AT91C_UDP_RSTEP 	RO }
	ICR 	{ R AT91C_UDP_ICR 	RO }
	IMR 	{ R AT91C_UDP_IMR 	RO }
	IER 	{ R AT91C_UDP_IER 	WO }
	FADDR 	{ R AT91C_UDP_FADDR 	RW }
	TXVC 	{ R AT91C_UDP_TXVC 	RW }
	ISR 	{ R AT91C_UDP_ISR 	RO }
	FDR 	{ R AT91C_UDP_FDR 	RW  6 }
	NUM 	{ R AT91C_UDP_NUM 	RO }
	CSR 	{ R AT91C_UDP_CSR 	RW  6 }
	GLBSTATE 	{ R AT91C_UDP_GLBSTATE 	RW }
	IDR 	{ R AT91C_UDP_IDR 	WO }
	listeReg 	{ RSTEP ICR IMR IER FADDR TXVC ISR FDR NUM CSR GLBSTATE IDR  }

}

# ========== PIO information ========== 

array set def_PIOA_att {
 	PA0 	{  MCI0_DA0   SPI0_MISO  }
 	PA1 	{  MCI0_CDA   SPI0_MOSI  }
 	PA10 	{  MCI1_DA2  }
 	PA11 	{  MCI1_DA3  }
 	PA12 	{  MCI0_CK  }
 	PA13 	{  CANTX   PCK0  }
 	PA14 	{  CANRX   IRQ0  }
 	PA15 	{  TCLK2   IRQ1  }
 	PA16 	{  MCI0_CDB   EBI1_D16  }
 	PA17 	{  MCI0_DB0   EBI1_D17  }
 	PA18 	{  MCI0_DB1   EBI1_D18  }
 	PA19 	{  MCI0_DB2   EBI1_D19  }
 	PA2 	{  UNCONNECTED_PA2_A   SPI0_SPCK  }
 	PA20 	{  MCI0_DB3   EBI1_D20  }
 	PA21 	{  MCI1_CDB   EBI1_D21  }
 	PA22 	{  MCI1_DB0   EBI1_D22  }
 	PA23 	{  MCI1_DB1   EBI1_D23  }
 	PA24 	{  MCI1_DB2   EBI1_D24  }
 	PA25 	{  MCI1_DB3   EBI1_D25  }
 	PA26 	{  TXD0   EBI1_D26  }
 	PA27 	{  RXD0   EBI1_D27  }
 	PA28 	{  RTS0   EBI1_D28  }
 	PA29 	{  CTS0   EBI1_D29  }
 	PA3 	{  MCI0_DA1   SPI0_NPCS1  }
 	PA30 	{  SCK0   EBI1_D30  }
 	PA31 	{  DMARQ0   EBI1_D31  }
 	PA4 	{  MCI0_DA2   SPI0_NPCS2A  }
 	PA5 	{  MCI0_DA3   SPI0_NPCS0  }
 	PA6 	{  MCI1_CK   PCK2  }
 	PA7 	{  MCI1_CDA  }
 	PA8 	{  MCI1_DA0  }
 	PA9 	{  MCI1_DA1  }
 }

array set def_PIOB_att {
 	PB0 	{  AC97FS   TF0  }
 	PB1 	{  AC97CK   TK0  }
 	PB10 	{  RK1   PCK1  }
 	PB11 	{  RF1   SPI0_NPCS3B  }
 	PB12 	{  SPI1_MISO  }
 	PB13 	{  SPI1_MOSI  }
 	PB14 	{  SPI1_SPCK  }
 	PB15 	{  SPI1_NPCS0  }
 	PB16 	{  SPI1_NPCS1   PCK1  }
 	PB17 	{  SPI1_NPCS2B   TIOA2  }
 	PB18 	{  SPI1_NPCS3B   TIOB2  }
 	PB19 	{ }
 	PB2 	{  AC97TX   TD0  }
 	PB20 	{ }
 	PB21 	{ }
 	PB22 	{ }
 	PB23 	{ }
 	PB24 	{  UNCONNECTED_PB24_A   DMARQ3  }
 	PB25 	{ }
 	PB26 	{ }
 	PB27 	{  UNCONNECTED_PB27_A   PWM2  }
 	PB28 	{  UNCONNECTED_PB28_A   TCLK0  }
 	PB29 	{  UNCONNECTED_PB29_A   PWM3  }
 	PB3 	{  AC97RX   RD0  }
 	PB30 	{ }
 	PB31 	{ }
 	PB4 	{  TWD   RK0  }
 	PB5 	{  TWCK   RF0  }
 	PB6 	{  TF1   DMARQ1  }
 	PB7 	{  TK1   PWM0  }
 	PB8 	{  TD1   PWM1  }
 	PB9 	{  RD1   LCDCC  }
 }

array set def_PIOC_att {
 	PC0 	{  LCDVSYNC  }
 	PC1 	{  LCDHSYNC  }
 	PC10 	{  LCDD6   LCDD11B  }
 	PC11 	{  LCDD7   LCDD12B  }
 	PC12 	{  LCDD8   LCDD13B  }
 	PC13 	{  LCDD9   LCDD14B  }
 	PC14 	{  LCDD10   LCDD15B  }
 	PC15 	{  LCDD11   LCDD19B  }
 	PC16 	{  LCDD12   LCDD20B  }
 	PC17 	{  LCDD13   LCDD21B  }
 	PC18 	{  LCDD14   LCDD22B  }
 	PC19 	{  LCDD15   LCDD23B  }
 	PC2 	{  LCDDOTCK  }
 	PC20 	{  LCDD16   ETX2  }
 	PC21 	{  LCDD17   ETX3  }
 	PC22 	{  LCDD18   ERX2  }
 	PC23 	{  LCDD19   ERX3  }
 	PC24 	{  LCDD20   ETXER  }
 	PC25 	{  LCDD21   ERXDV  }
 	PC26 	{  LCDD22   ECOL  }
 	PC27 	{  LCDD23   ERXCK  }
 	PC28 	{  PWM0   TCLK1  }
 	PC29 	{  PCK0   PWM2  }
 	PC3 	{  LCDEN   PWM1  }
 	PC30 	{  DRXD  }
 	PC31 	{  DTXD  }
 	PC4 	{  LCDD0   LCDD3B  }
 	PC5 	{  LCDD1   LCDD4B  }
 	PC6 	{  LCDD2   LCDD5B  }
 	PC7 	{  LCDD3   LCDD6B  }
 	PC8 	{  LCDD4   LCDD7B  }
 	PC9 	{  LCDD5   LCDD10B  }
 }

array set def_PIOD_att {
 	PD0 	{  TXD1   SPI0_NPCS2D  }
 	PD1 	{  RXD1   SPI0_NPCS3D  }
 	PD10 	{  UNCONNECTED_PD10_A   SCK1  }
 	PD11 	{  EBI0_NCS2   TSYNC  }
 	PD12 	{  EBI0_A23   TCLK  }
 	PD13 	{  EBI0_A24   TPS0  }
 	PD14 	{  EBI0_A25_CFNRW   TPS1  }
 	PD15 	{  EBI0_NCS3_NANDCS   TPS2  }
 	PD16 	{  EBI0_D16   TPK0  }
 	PD17 	{  EBI0_D17   TPK1  }
 	PD18 	{  EBI0_D18   TPK2  }
 	PD19 	{  EBI0_D19   TPK3  }
 	PD2 	{  TXD2   SPI1_NPCS2D  }
 	PD20 	{  EBI0_D20   TPK4  }
 	PD21 	{  EBI0_D21   TPK5  }
 	PD22 	{  EBI0_D22   TPK6  }
 	PD23 	{  EBI0_D23   TPK7  }
 	PD24 	{  EBI0_D24   TPK8  }
 	PD25 	{  EBI0_D25   TPK9  }
 	PD26 	{  EBI0_D26   TPK10  }
 	PD27 	{  EBI0_D27   TPK11  }
 	PD28 	{  EBI0_D28   TPK12  }
 	PD29 	{  EBI0_D29   TPK13  }
 	PD3 	{  RXD2   SPI1_NPCS3D  }
 	PD30 	{  EBI0_D30   TPK14  }
 	PD31 	{  EBI0_D31   TPK15  }
 	PD4 	{  FIQ   DMARQ2  }
 	PD5 	{  EBI0_NWAIT   RTS2  }
 	PD6 	{  EBI0_NCS4_CFCS0   CTS2  }
 	PD7 	{  EBI0_NCS5_CFCS1   RTS1  }
 	PD8 	{  EBI0_CFCE1   CTS1  }
 	PD9 	{  EBI0_CFCE2   SCK2  }
 }

array set def_PIOE_att {
 	PE0 	{  ISI_D0  }
 	PE1 	{  ISI_D1  }
 	PE10 	{  ISI_VSYNC   PWM3  }
 	PE11 	{  ISI_MCK   PCK3  }
 	PE12 	{  KBDR0   ISI_D8  }
 	PE13 	{  KBDR1   ISI_D9  }
 	PE14 	{  KBDR2   ISI_D10  }
 	PE15 	{  KBDR3   ISI_D11  }
 	PE16 	{  KBDR4  }
 	PE17 	{  KBDC0  }
 	PE18 	{  KBDC1   TIOA0  }
 	PE19 	{  KBDC2   TIOB0  }
 	PE2 	{  ISI_D2  }
 	PE20 	{  KBDC3   EBI1_NWAIT  }
 	PE21 	{  ETXCK   EBI1_NANDWE  }
 	PE22 	{  ECRS   EBI1_NCS2_NANDCS  }
 	PE23 	{  ETX0   EBI1_NANDOE  }
 	PE24 	{  ETX1   EBI1_NWR3_NBS3  }
 	PE25 	{  ERX0   EBI1_NCS1_SDCS  }
 	PE26 	{  ERX1  }
 	PE27 	{  ERXER   EBI1_SDCKE  }
 	PE28 	{  ETXEN   EBI1_RAS  }
 	PE29 	{  EMDC   EBI1_CAS  }
 	PE3 	{  ISI_D3  }
 	PE30 	{  EMDIO   EBI1_SDWE  }
 	PE31 	{  EF100   EBI1_SDA10  }
 	PE4 	{  ISI_D4  }
 	PE5 	{  ISI_D5  }
 	PE6 	{  ISI_D6  }
 	PE7 	{  ISI_D7  }
 	PE8 	{  ISI_PCK   TIOA1  }
 	PE9 	{  ISI_HSYNC   TIOB1  }
 }
