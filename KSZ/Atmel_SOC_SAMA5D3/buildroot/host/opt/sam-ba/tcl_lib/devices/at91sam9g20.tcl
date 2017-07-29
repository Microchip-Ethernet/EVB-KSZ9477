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
# File Name           : AT91SAM9260A.tcl
# Object              : AT91SAM9260A definitions
# Generated           : AT91 SW Application Group  04/23/2007 (12:55:26)
# 
# CVS Reference       : /AT91SAM9260A.pl/1.2/Mon Apr 23 10:53:39 2007//
# CVS Reference       : /SYS_SAM9260.pl/1.2/Fri Sep 30 12:12:15 2005//
# CVS Reference       : /HMATRIX1_SAM9260.pl/1.7/Mon Apr 23 10:39:45 2007//
# CVS Reference       : /CCR_SAM9260.pl/1.2/Mon Apr 16 10:47:39 2007//
# CVS Reference       : /PMC_SAM9260.pl/1.2/Thu Oct 13 11:39:15 2005//
# CVS Reference       : /ADC_9260.pl/1.2/Thu Dec  7 13:57:57 2006//
# CVS Reference       : /HSDRAMC1_6100A.pl/1.2/Mon Aug  9 10:52:25 2004//
# CVS Reference       : /HSMC3_6105A.pl/1.4/Tue Nov 16 09:16:23 2004//
# CVS Reference       : /AIC_6075A.pl/1.1/Mon Jul 12 17:04:01 2004//
# CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb  3 09:02:11 2005//
# CVS Reference       : /DBGU_6059D.pl/1.1/Mon Jan 31 13:54:41 2005//
# CVS Reference       : /PIO_6057A.pl/1.2/Thu Feb  3 10:29:42 2005//
# CVS Reference       : /RSTC_6098A.pl/1.3/Thu Nov  4 13:57:00 2004//
# CVS Reference       : /SHDWC_6122A.pl/1.3/Wed Oct  6 14:16:58 2004//
# CVS Reference       : /RTTC_6081A.pl/1.2/Thu Nov  4 13:57:22 2004//
# CVS Reference       : /PITC_6079A.pl/1.2/Thu Nov  4 13:56:22 2004//
# CVS Reference       : /WDTC_6080A.pl/1.3/Thu Nov  4 13:58:52 2004//
# CVS Reference       : /TC_6082A.pl/1.7/Wed Mar  9 16:31:51 2005//
# CVS Reference       : /MCI_6101E.pl/1.1/Fri Jun  3 13:20:23 2005//
# CVS Reference       : /TWI_6061A.pl/1.2/Wed Oct 25 15:03:34 2006//
# CVS Reference       : /US_6089C.pl/1.1/Mon Jan 31 13:56:02 2005//
# CVS Reference       : /SSC_6078A.pl/1.1/Tue Jul 13 07:10:41 2004//
# CVS Reference       : /SPI_6088D.pl/1.3/Fri May 20 14:23:02 2005//
# CVS Reference       : /EMACB_6119A.pl/1.6/Wed Jul 13 15:25:00 2005//
# CVS Reference       : /UDP_6ept_puon.pl/1.1/Wed Aug 30 14:20:53 2006//
# CVS Reference       : /UHP_6127A.pl/1.1/Wed Feb 23 16:03:17 2005//
# CVS Reference       : /TBOX_XXXX.pl/1.15/Thu Jun  9 07:05:57 2005//
# CVS Reference       : /EBI_SAM9260.pl/1.1/Fri Sep 30 12:12:14 2005//
# CVS Reference       : /HECC_6143A.pl/1.1/Wed Feb  9 17:16:57 2005//
# CVS Reference       : /ISI_xxxxx.pl/1.3/Thu Mar  3 11:11:48 2005//
# ----------------------------------------------------------------------------


# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR System Peripherals
# *****************************************************************************
# -------- GPBR : (SYS Offset: 0x1350) GPBR General Purpose Register -------- 
# -------- GPBR : (SYS Offset: 0x1354) GPBR General Purpose Register -------- 
# -------- GPBR : (SYS Offset: 0x1358) GPBR General Purpose Register -------- 
# -------- GPBR : (SYS Offset: 0x135c) GPBR General Purpose Register -------- 

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR External Bus Interface
# *****************************************************************************

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
# -------- MATRIX_SCFG0 : (MATRIX Offset: 0x40) Slave Configuration Register 0 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR0 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_HPDC3                [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_LCDC                 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA                  [expr 0x4 << 18 ]
# -------- MATRIX_SCFG1 : (MATRIX Offset: 0x44) Slave Configuration Register 1 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR1 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_HPDC3                [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_LCDC                 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_DMA                  [expr 0x4 << 18 ]
# -------- MATRIX_SCFG2 : (MATRIX Offset: 0x48) Slave Configuration Register 2 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR2 [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926D              [expr 0x1 << 18 ]
# -------- MATRIX_SCFG3 : (MATRIX Offset: 0x4c) Slave Configuration Register 3 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR3 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_HPDC3                [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_LCDC                 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_DMA                  [expr 0x4 << 18 ]
# -------- MATRIX_SCFG4 : (MATRIX Offset: 0x50) Slave Configuration Register 4 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR4 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_HPDC3                [expr 0x2 << 18 ]
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
# -------- MATRIX_MRCR : (MATRIX Offset: 0x100) MRCR Register -------- 
set AT91C_MATRIX_RCA926I  [expr 0x1 <<  0 ]
set AT91C_MATRIX_RCA926D  [expr 0x1 <<  1 ]
# -------- MATRIX_EBI : (MATRIX Offset: 0x11c) EBI (Slave 3) Special Function Register -------- 
set AT91C_MATRIX_CS1A     [expr 0x1 <<  1 ]
set 	AT91C_MATRIX_CS1A_SMC                  [expr 0x0 <<  1 ]
set 	AT91C_MATRIX_CS1A_SDRAMC               [expr 0x1 <<  1 ]
set AT91C_MATRIX_CS3A     [expr 0x1 <<  3 ]
set 	AT91C_MATRIX_CS3A_SMC                  [expr 0x0 <<  3 ]
set 	AT91C_MATRIX_CS3A_SM                   [expr 0x1 <<  3 ]
set AT91C_MATRIX_CS4A     [expr 0x1 <<  4 ]
set 	AT91C_MATRIX_CS4A_SMC                  [expr 0x0 <<  4 ]
set 	AT91C_MATRIX_CS4A_CF                   [expr 0x1 <<  4 ]
set AT91C_MATRIX_CS5A     [expr 0x1 <<  5 ]
set 	AT91C_MATRIX_CS5A_SMC                  [expr 0x0 <<  5 ]
set 	AT91C_MATRIX_CS5A_CF                   [expr 0x1 <<  5 ]
set AT91C_MATRIX_DBPUC    [expr 0x1 <<  8 ]
# -------- MATRIX_TEAKCFG : (MATRIX Offset: 0x12c) Slave 7 Special Function Register -------- 
set AT91C_TEAK_PROGRAM_ACCESS [expr 0x1 <<  0 ]
set 	AT91C_TEAK_PROGRAM_ACCESS_DISABLED             0x0
set 	AT91C_TEAK_PROGRAM_ACCESS_ENABLED              0x1
set AT91C_TEAK_BOOT       [expr 0x1 <<  1 ]
set 	AT91C_TEAK_BOOT_DISABLED             [expr 0x0 <<  1 ]
set 	AT91C_TEAK_BOOT_ENABLED              [expr 0x1 <<  1 ]
set AT91C_TEAK_NRESET     [expr 0x1 <<  2 ]
set 	AT91C_TEAK_NRESET_ENABLED              [expr 0x0 <<  2 ]
set 	AT91C_TEAK_NRESET_DISABLED             [expr 0x1 <<  2 ]
set AT91C_TEAK_LVECTORP   [expr 0x3FFFF << 14 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Chip Configuration Registers
# *****************************************************************************
# -------- CCFG_EBICSA : (CCFG Offset: 0xc) EBI Chip Select Assignement Register -------- 
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
set AT91C_PMC_UHP         [expr 0x1 <<  6 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_HCK0        [expr 0x1 << 16 ]
set AT91C_PMC_HCK1        [expr 0x1 << 17 ]
# -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_UHP         [expr 0x1 <<  6 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_HCK0        [expr 0x1 << 16 ]
set AT91C_PMC_HCK1        [expr 0x1 << 17 ]
# -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_UHP         [expr 0x1 <<  6 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_HCK0        [expr 0x1 << 16 ]
set AT91C_PMC_HCK1        [expr 0x1 << 17 ]
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
# -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
# -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_OSCSEL      [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
# -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]

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
set AT91C_TC_CPCDIS       [expr 0x1 <<  7 ]
set AT91C_TC_LDBDIS       [expr 0x1 <<  7 ]
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
set AT91C_TC_EEVT         [expr 0x3 << 10 ]
set 	AT91C_TC_EEVT_TIOB                 [expr 0x0 << 10 ]
set 	AT91C_TC_EEVT_XC0                  [expr 0x1 << 10 ]
set 	AT91C_TC_EEVT_XC1                  [expr 0x2 << 10 ]
set 	AT91C_TC_EEVT_XC2                  [expr 0x3 << 10 ]
set AT91C_TC_ABETRG       [expr 0x1 << 10 ]
set AT91C_TC_ENETRG       [expr 0x1 << 12 ]
set AT91C_TC_WAVESEL      [expr 0x3 << 13 ]
set 	AT91C_TC_WAVESEL_UP                   [expr 0x0 << 13 ]
set 	AT91C_TC_WAVESEL_UPDOWN               [expr 0x1 << 13 ]
set 	AT91C_TC_WAVESEL_UP_AUTO              [expr 0x2 << 13 ]
set 	AT91C_TC_WAVESEL_UPDOWN_AUTO          [expr 0x3 << 13 ]
set AT91C_TC_CPCTRG       [expr 0x1 << 14 ]
set AT91C_TC_WAVE         [expr 0x1 << 15 ]
set AT91C_TC_WAVE         [expr 0x1 << 15 ]
set AT91C_TC_ACPA         [expr 0x3 << 16 ]
set 	AT91C_TC_ACPA_NONE                 [expr 0x0 << 16 ]
set 	AT91C_TC_ACPA_SET                  [expr 0x1 << 16 ]
set 	AT91C_TC_ACPA_CLEAR                [expr 0x2 << 16 ]
set 	AT91C_TC_ACPA_TOGGLE               [expr 0x3 << 16 ]
set AT91C_TC_LDRA         [expr 0x3 << 16 ]
set 	AT91C_TC_LDRA_NONE                 [expr 0x0 << 16 ]
set 	AT91C_TC_LDRA_RISING               [expr 0x1 << 16 ]
set 	AT91C_TC_LDRA_FALLING              [expr 0x2 << 16 ]
set 	AT91C_TC_LDRA_BOTH                 [expr 0x3 << 16 ]
set AT91C_TC_ACPC         [expr 0x3 << 18 ]
set 	AT91C_TC_ACPC_NONE                 [expr 0x0 << 18 ]
set 	AT91C_TC_ACPC_SET                  [expr 0x1 << 18 ]
set 	AT91C_TC_ACPC_CLEAR                [expr 0x2 << 18 ]
set 	AT91C_TC_ACPC_TOGGLE               [expr 0x3 << 18 ]
set AT91C_TC_LDRB         [expr 0x3 << 18 ]
set 	AT91C_TC_LDRB_NONE                 [expr 0x0 << 18 ]
set 	AT91C_TC_LDRB_RISING               [expr 0x1 << 18 ]
set 	AT91C_TC_LDRB_FALLING              [expr 0x2 << 18 ]
set 	AT91C_TC_LDRB_BOTH                 [expr 0x3 << 18 ]
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
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
# -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- 
set AT91C_TWI_TXCOMP      [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_UNRE        [expr 0x1 <<  7 ]
set AT91C_TWI_NACK        [expr 0x1 <<  8 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
# -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- 
set AT91C_TWI_TXCOMP      [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_UNRE        [expr 0x1 <<  7 ]
set AT91C_TWI_NACK        [expr 0x1 <<  8 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
# -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- 
set AT91C_TWI_TXCOMP      [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_UNRE        [expr 0x1 <<  7 ]
set AT91C_TWI_NACK        [expr 0x1 <<  8 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
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
set AT91C_SSC_TXSYN       [expr 0x1 << 10 ]
set AT91C_SSC_RXSYN       [expr 0x1 << 11 ]

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
#              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor
# *****************************************************************************
# -------- ADC_CR : (ADC Offset: 0x0) ADC Control Register -------- 
set AT91C_ADC_SWRST       [expr 0x1 <<  0 ]
set AT91C_ADC_START       [expr 0x1 <<  1 ]
# -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- 
set AT91C_ADC_TRGEN       [expr 0x1 <<  0 ]
set 	AT91C_ADC_TRGEN_DIS                  0x0
set 	AT91C_ADC_TRGEN_EN                   0x1
set AT91C_ADC_TRGSEL      [expr 0x7 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA0                [expr 0x0 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA1                [expr 0x1 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA2                [expr 0x2 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA3                [expr 0x3 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA4                [expr 0x4 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA5                [expr 0x5 <<  1 ]
set 	AT91C_ADC_TRGSEL_EXT                  [expr 0x6 <<  1 ]
set AT91C_ADC_LOWRES      [expr 0x1 <<  4 ]
set 	AT91C_ADC_LOWRES_10_BIT               [expr 0x0 <<  4 ]
set 	AT91C_ADC_LOWRES_8_BIT                [expr 0x1 <<  4 ]
set AT91C_ADC_SLEEP       [expr 0x1 <<  5 ]
set 	AT91C_ADC_SLEEP_NORMAL_MODE          [expr 0x0 <<  5 ]
set 	AT91C_ADC_SLEEP_MODE                 [expr 0x1 <<  5 ]
set AT91C_ADC_PRESCAL     [expr 0x3F <<  8 ]
set AT91C_ADC_STARTUP     [expr 0x1F << 16 ]
set AT91C_ADC_SHTIM       [expr 0xF << 24 ]
# -------- 	ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- 
set AT91C_ADC_CH0         [expr 0x1 <<  0 ]
set AT91C_ADC_CH1         [expr 0x1 <<  1 ]
set AT91C_ADC_CH2         [expr 0x1 <<  2 ]
set AT91C_ADC_CH3         [expr 0x1 <<  3 ]
# -------- 	ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- 
set AT91C_ADC_CH0         [expr 0x1 <<  0 ]
set AT91C_ADC_CH1         [expr 0x1 <<  1 ]
set AT91C_ADC_CH2         [expr 0x1 <<  2 ]
set AT91C_ADC_CH3         [expr 0x1 <<  3 ]
# -------- 	ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- 
set AT91C_ADC_CH0         [expr 0x1 <<  0 ]
set AT91C_ADC_CH1         [expr 0x1 <<  1 ]
set AT91C_ADC_CH2         [expr 0x1 <<  2 ]
set AT91C_ADC_CH3         [expr 0x1 <<  3 ]
# -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_OVRE0       [expr 0x1 <<  8 ]
set AT91C_ADC_OVRE1       [expr 0x1 <<  9 ]
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_DRDY        [expr 0x1 << 16 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 17 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 18 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 19 ]
# -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- 
set AT91C_ADC_LDATA       [expr 0x3FF <<  0 ]
# -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_OVRE0       [expr 0x1 <<  8 ]
set AT91C_ADC_OVRE1       [expr 0x1 <<  9 ]
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_DRDY        [expr 0x1 << 16 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 17 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 18 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 19 ]
# -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_OVRE0       [expr 0x1 <<  8 ]
set AT91C_ADC_OVRE1       [expr 0x1 <<  9 ]
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_DRDY        [expr 0x1 << 16 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 17 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 18 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 19 ]
# -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_OVRE0       [expr 0x1 <<  8 ]
set AT91C_ADC_OVRE1       [expr 0x1 <<  9 ]
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_DRDY        [expr 0x1 << 16 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 17 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 18 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 19 ]
# -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR1 : (ADC Offset: 0x34) ADC Channel Data Register 1 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR2 : (ADC Offset: 0x38) ADC Channel Data Register 2 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR3 : (ADC Offset: 0x3c) ADC Channel Data Register 3 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]

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
set AT91C_UDP_ISOERROR    [expr 0x1 <<  3 ]
set AT91C_UDP_STALLSENT   [expr 0x1 <<  3 ]
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
set AT91C_UDP_PUON        [expr 0x1 <<  9 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR USB Host Interface
# *****************************************************************************

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
#               REGISTER ADDRESS DEFINITION FOR AT91SAM9260A
# *****************************************************************************
# ========== Register definition for SYS peripheral ========== 
set AT91C_SYS_GPBR1 0xFFFFFFFF
set AT91C_SYS_GPBR2 0xFFFFFFFF
set AT91C_SYS_GPBR0 0xFFFFFFFF
set AT91C_SYS_GPBR3 0xFFFFFFFF
# ========== Register definition for EBI peripheral ========== 
set AT91C_EBI_DUMMY 0xFFFFEA00
# ========== Register definition for HECC peripheral ========== 
set AT91C_HECC_VR   0xFFFFE8FC
set AT91C_HECC_NPR  0xFFFFE810
set AT91C_HECC_SR   0xFFFFE808
set AT91C_HECC_PR   0xFFFFE80C
set AT91C_HECC_MR   0xFFFFE804
set AT91C_HECC_CR   0xFFFFE800
# ========== Register definition for SDRAMC peripheral ========== 
set AT91C_SDRAMC_MR 0xFFFFEA00
set AT91C_SDRAMC_IMR 0xFFFFEA1C
set AT91C_SDRAMC_LPR 0xFFFFEA10
set AT91C_SDRAMC_ISR 0xFFFFEA20
set AT91C_SDRAMC_IDR 0xFFFFEA18
set AT91C_SDRAMC_CR 0xFFFFEA08
set AT91C_SDRAMC_TR 0xFFFFEA04
set AT91C_SDRAMC_MDR 0xFFFFEA24
set AT91C_SDRAMC_HSR 0xFFFFEA0C
set AT91C_SDRAMC_IER 0xFFFFEA14
# ========== Register definition for SMC peripheral ========== 
set AT91C_SMC_CTRL1 0xFFFFEC1C
set AT91C_SMC_PULSE7 0xFFFFEC74
set AT91C_SMC_PULSE6 0xFFFFEC64
set AT91C_SMC_SETUP4 0xFFFFEC40
set AT91C_SMC_PULSE3 0xFFFFEC34
set AT91C_SMC_CYCLE5 0xFFFFEC58
set AT91C_SMC_CYCLE2 0xFFFFEC28
set AT91C_SMC_CTRL2 0xFFFFEC2C
set AT91C_SMC_CTRL0 0xFFFFEC0C
set AT91C_SMC_PULSE5 0xFFFFEC54
set AT91C_SMC_PULSE1 0xFFFFEC14
set AT91C_SMC_PULSE0 0xFFFFEC04
set AT91C_SMC_CYCLE7 0xFFFFEC78
set AT91C_SMC_CTRL4 0xFFFFEC4C
set AT91C_SMC_CTRL3 0xFFFFEC3C
set AT91C_SMC_SETUP7 0xFFFFEC70
set AT91C_SMC_CTRL7 0xFFFFEC7C
set AT91C_SMC_SETUP1 0xFFFFEC10
set AT91C_SMC_CYCLE0 0xFFFFEC08
set AT91C_SMC_CTRL5 0xFFFFEC5C
set AT91C_SMC_CYCLE1 0xFFFFEC18
set AT91C_SMC_CTRL6 0xFFFFEC6C
set AT91C_SMC_SETUP0 0xFFFFEC00
set AT91C_SMC_PULSE4 0xFFFFEC44
set AT91C_SMC_SETUP5 0xFFFFEC50
set AT91C_SMC_SETUP2 0xFFFFEC20
set AT91C_SMC_CYCLE3 0xFFFFEC38
set AT91C_SMC_CYCLE6 0xFFFFEC68
set AT91C_SMC_SETUP6 0xFFFFEC60
set AT91C_SMC_CYCLE4 0xFFFFEC48
set AT91C_SMC_PULSE2 0xFFFFEC24
set AT91C_SMC_SETUP3 0xFFFFEC30
# ========== Register definition for MATRIX peripheral ========== 
set AT91C_MATRIX_MCFG0 0xFFFFEE00
set AT91C_MATRIX_MCFG7 0xFFFFEE1C
set AT91C_MATRIX_SCFG1 0xFFFFEE44
set AT91C_MATRIX_MCFG4 0xFFFFEE10
set AT91C_MATRIX_VERSION 0xFFFFEFFC
set AT91C_MATRIX_MCFG2 0xFFFFEE08
set AT91C_MATRIX_PRBS4 0xFFFFEEA4
set AT91C_MATRIX_PRBS0 0xFFFFEE84
set AT91C_MATRIX_SCFG3 0xFFFFEE4C
set AT91C_MATRIX_MCFG6 0xFFFFEE18
set AT91C_MATRIX_EBI 0xFFFFEF1C
set AT91C_MATRIX_SCFG0 0xFFFFEE40
set AT91C_MATRIX_PRBS3 0xFFFFEE9C
set AT91C_MATRIX_PRAS3 0xFFFFEE98
set AT91C_MATRIX_PRAS0 0xFFFFEE80
set AT91C_MATRIX_MCFG3 0xFFFFEE0C
set AT91C_MATRIX_PRAS1 0xFFFFEE88
set AT91C_MATRIX_PRAS2 0xFFFFEE90
set AT91C_MATRIX_SCFG2 0xFFFFEE48
set AT91C_MATRIX_MCFG5 0xFFFFEE14
set AT91C_MATRIX_MCFG1 0xFFFFEE04
set AT91C_MATRIX_PRAS4 0xFFFFEEA0
set AT91C_MATRIX_MRCR 0xFFFFEF00
set AT91C_MATRIX_PRBS2 0xFFFFEE94
set AT91C_MATRIX_SCFG4 0xFFFFEE50
set AT91C_MATRIX_TEAKCFG 0xFFFFEF2C
set AT91C_MATRIX_PRBS1 0xFFFFEE8C
# ========== Register definition for CCFG peripheral ========== 
set AT91C_CCFG_MATRIXVERSION 0xFFFFEFFC
set AT91C_CCFG_EBICSA 0xFFFFEF1C
# ========== Register definition for PDC_DBGU peripheral ========== 
set AT91C_DBGU_TCR  0xFFFFF30C
set AT91C_DBGU_RNPR 0xFFFFF310
set AT91C_DBGU_TNPR 0xFFFFF318
set AT91C_DBGU_TPR  0xFFFFF308
set AT91C_DBGU_RPR  0xFFFFF300
set AT91C_DBGU_RCR  0xFFFFF304
set AT91C_DBGU_RNCR 0xFFFFF314
set AT91C_DBGU_PTCR 0xFFFFF320
set AT91C_DBGU_PTSR 0xFFFFF324
set AT91C_DBGU_TNCR 0xFFFFF31C
# ========== Register definition for DBGU peripheral ========== 
set AT91C_DBGU_EXID 0xFFFFF244
set AT91C_DBGU_BRGR 0xFFFFF220
set AT91C_DBGU_IDR  0xFFFFF20C
set AT91C_DBGU_CSR  0xFFFFF214
set AT91C_DBGU_CIDR 0xFFFFF240
set AT91C_DBGU_MR   0xFFFFF204
set AT91C_DBGU_IMR  0xFFFFF210
set AT91C_DBGU_CR   0xFFFFF200
set AT91C_DBGU_FNTR 0xFFFFF248
set AT91C_DBGU_THR  0xFFFFF21C
set AT91C_DBGU_RHR  0xFFFFF218
set AT91C_DBGU_IER  0xFFFFF208
# ========== Register definition for AIC peripheral ========== 
set AT91C_AIC_IVR   0xFFFFF100
set AT91C_AIC_SMR   0xFFFFF000
set AT91C_AIC_FVR   0xFFFFF104
set AT91C_AIC_DCR   0xFFFFF138
set AT91C_AIC_EOICR 0xFFFFF130
set AT91C_AIC_SVR   0xFFFFF080
set AT91C_AIC_FFSR  0xFFFFF148
set AT91C_AIC_ICCR  0xFFFFF128
set AT91C_AIC_ISR   0xFFFFF108
set AT91C_AIC_IMR   0xFFFFF110
set AT91C_AIC_IPR   0xFFFFF10C
set AT91C_AIC_FFER  0xFFFFF140
set AT91C_AIC_IECR  0xFFFFF120
set AT91C_AIC_ISCR  0xFFFFF12C
set AT91C_AIC_FFDR  0xFFFFF144
set AT91C_AIC_CISR  0xFFFFF114
set AT91C_AIC_IDCR  0xFFFFF124
set AT91C_AIC_SPU   0xFFFFF134
# ========== Register definition for PIOA peripheral ========== 
set AT91C_PIOA_ODR  0xFFFFF414
set AT91C_PIOA_SODR 0xFFFFF430
set AT91C_PIOA_ISR  0xFFFFF44C
set AT91C_PIOA_ABSR 0xFFFFF478
set AT91C_PIOA_IER  0xFFFFF440
set AT91C_PIOA_PPUDR 0xFFFFF460
set AT91C_PIOA_IMR  0xFFFFF448
set AT91C_PIOA_PER  0xFFFFF400
set AT91C_PIOA_IFDR 0xFFFFF424
set AT91C_PIOA_OWDR 0xFFFFF4A4
set AT91C_PIOA_MDSR 0xFFFFF458
set AT91C_PIOA_IDR  0xFFFFF444
set AT91C_PIOA_ODSR 0xFFFFF438
set AT91C_PIOA_PPUSR 0xFFFFF468
set AT91C_PIOA_OWSR 0xFFFFF4A8
set AT91C_PIOA_BSR  0xFFFFF474
set AT91C_PIOA_OWER 0xFFFFF4A0
set AT91C_PIOA_IFER 0xFFFFF420
set AT91C_PIOA_PDSR 0xFFFFF43C
set AT91C_PIOA_PPUER 0xFFFFF464
set AT91C_PIOA_OSR  0xFFFFF418
set AT91C_PIOA_ASR  0xFFFFF470
set AT91C_PIOA_MDDR 0xFFFFF454
set AT91C_PIOA_CODR 0xFFFFF434
set AT91C_PIOA_MDER 0xFFFFF450
set AT91C_PIOA_PDR  0xFFFFF404
set AT91C_PIOA_IFSR 0xFFFFF428
set AT91C_PIOA_OER  0xFFFFF410
set AT91C_PIOA_PSR  0xFFFFF408
# ========== Register definition for PIOB peripheral ========== 
set AT91C_PIOB_OWDR 0xFFFFF6A4
set AT91C_PIOB_MDER 0xFFFFF650
set AT91C_PIOB_PPUSR 0xFFFFF668
set AT91C_PIOB_IMR  0xFFFFF648
set AT91C_PIOB_ASR  0xFFFFF670
set AT91C_PIOB_PPUDR 0xFFFFF660
set AT91C_PIOB_PSR  0xFFFFF608
set AT91C_PIOB_IER  0xFFFFF640
set AT91C_PIOB_CODR 0xFFFFF634
set AT91C_PIOB_OWER 0xFFFFF6A0
set AT91C_PIOB_ABSR 0xFFFFF678
set AT91C_PIOB_IFDR 0xFFFFF624
set AT91C_PIOB_PDSR 0xFFFFF63C
set AT91C_PIOB_IDR  0xFFFFF644
set AT91C_PIOB_OWSR 0xFFFFF6A8
set AT91C_PIOB_PDR  0xFFFFF604
set AT91C_PIOB_ODR  0xFFFFF614
set AT91C_PIOB_IFSR 0xFFFFF628
set AT91C_PIOB_PPUER 0xFFFFF664
set AT91C_PIOB_SODR 0xFFFFF630
set AT91C_PIOB_ISR  0xFFFFF64C
set AT91C_PIOB_ODSR 0xFFFFF638
set AT91C_PIOB_OSR  0xFFFFF618
set AT91C_PIOB_MDSR 0xFFFFF658
set AT91C_PIOB_IFER 0xFFFFF620
set AT91C_PIOB_BSR  0xFFFFF674
set AT91C_PIOB_MDDR 0xFFFFF654
set AT91C_PIOB_OER  0xFFFFF610
set AT91C_PIOB_PER  0xFFFFF600
# ========== Register definition for PIOC peripheral ========== 
set AT91C_PIOC_OWDR 0xFFFFF8A4
set AT91C_PIOC_SODR 0xFFFFF830
set AT91C_PIOC_PPUER 0xFFFFF864
set AT91C_PIOC_CODR 0xFFFFF834
set AT91C_PIOC_PSR  0xFFFFF808
set AT91C_PIOC_PDR  0xFFFFF804
set AT91C_PIOC_ODR  0xFFFFF814
set AT91C_PIOC_PPUSR 0xFFFFF868
set AT91C_PIOC_ABSR 0xFFFFF878
set AT91C_PIOC_IFSR 0xFFFFF828
set AT91C_PIOC_OER  0xFFFFF810
set AT91C_PIOC_IMR  0xFFFFF848
set AT91C_PIOC_ASR  0xFFFFF870
set AT91C_PIOC_MDDR 0xFFFFF854
set AT91C_PIOC_OWSR 0xFFFFF8A8
set AT91C_PIOC_PER  0xFFFFF800
set AT91C_PIOC_IDR  0xFFFFF844
set AT91C_PIOC_MDER 0xFFFFF850
set AT91C_PIOC_PDSR 0xFFFFF83C
set AT91C_PIOC_MDSR 0xFFFFF858
set AT91C_PIOC_OWER 0xFFFFF8A0
set AT91C_PIOC_BSR  0xFFFFF874
set AT91C_PIOC_PPUDR 0xFFFFF860
set AT91C_PIOC_IFDR 0xFFFFF824
set AT91C_PIOC_IER  0xFFFFF840
set AT91C_PIOC_OSR  0xFFFFF818
set AT91C_PIOC_ODSR 0xFFFFF838
set AT91C_PIOC_ISR  0xFFFFF84C
set AT91C_PIOC_IFER 0xFFFFF820
# ========== Register definition for CKGR peripheral ========== 
set AT91C_CKGR_MOR  0xFFFFFC20
set AT91C_CKGR_PLLBR 0xFFFFFC2C
set AT91C_CKGR_MCFR 0xFFFFFC24
set AT91C_CKGR_PLLAR 0xFFFFFC28
# ========== Register definition for PMC peripheral ========== 
set AT91C_PMC_PCER  0xFFFFFC10
set AT91C_PMC_PCKR  0xFFFFFC40
set AT91C_PMC_MCKR  0xFFFFFC30
set AT91C_PMC_PLLAR 0xFFFFFC28
set AT91C_PMC_PCDR  0xFFFFFC14
set AT91C_PMC_SCSR  0xFFFFFC08
set AT91C_PMC_MCFR  0xFFFFFC24
set AT91C_PMC_IMR   0xFFFFFC6C
set AT91C_PMC_IER   0xFFFFFC60
set AT91C_PMC_MOR   0xFFFFFC20
set AT91C_PMC_IDR   0xFFFFFC64
set AT91C_PMC_PLLBR 0xFFFFFC2C
set AT91C_PMC_SCDR  0xFFFFFC04
set AT91C_PMC_PCSR  0xFFFFFC18
set AT91C_PMC_SCER  0xFFFFFC00
set AT91C_PMC_SR    0xFFFFFC68
# ========== Register definition for RSTC peripheral ========== 
set AT91C_RSTC_RCR  0xFFFFFD00
set AT91C_RSTC_RMR  0xFFFFFD08
set AT91C_RSTC_RSR  0xFFFFFD04
# ========== Register definition for SHDWC peripheral ========== 
set AT91C_SHDWC_SHSR 0xFFFFFD18
set AT91C_SHDWC_SHMR 0xFFFFFD14
set AT91C_SHDWC_SHCR 0xFFFFFD10
# ========== Register definition for RTTC peripheral ========== 
set AT91C_RTTC_RTSR 0xFFFFFD2C
set AT91C_RTTC_RTMR 0xFFFFFD20
set AT91C_RTTC_RTVR 0xFFFFFD28
set AT91C_RTTC_RTAR 0xFFFFFD24
# ========== Register definition for PITC peripheral ========== 
set AT91C_PITC_PIVR 0xFFFFFD38
set AT91C_PITC_PISR 0xFFFFFD34
set AT91C_PITC_PIIR 0xFFFFFD3C
set AT91C_PITC_PIMR 0xFFFFFD30
# ========== Register definition for WDTC peripheral ========== 
set AT91C_WDTC_WDCR 0xFFFFFD40
set AT91C_WDTC_WDSR 0xFFFFFD48
set AT91C_WDTC_WDMR 0xFFFFFD44
# ========== Register definition for TC0 peripheral ========== 
set AT91C_TC0_SR    0xFFFA0020
set AT91C_TC0_RC    0xFFFA001C
set AT91C_TC0_RB    0xFFFA0018
set AT91C_TC0_CCR   0xFFFA0000
set AT91C_TC0_CMR   0xFFFA0004
set AT91C_TC0_IER   0xFFFA0024
set AT91C_TC0_RA    0xFFFA0014
set AT91C_TC0_IDR   0xFFFA0028
set AT91C_TC0_CV    0xFFFA0010
set AT91C_TC0_IMR   0xFFFA002C
# ========== Register definition for TC1 peripheral ========== 
set AT91C_TC1_RB    0xFFFA0058
set AT91C_TC1_CCR   0xFFFA0040
set AT91C_TC1_IER   0xFFFA0064
set AT91C_TC1_IDR   0xFFFA0068
set AT91C_TC1_SR    0xFFFA0060
set AT91C_TC1_CMR   0xFFFA0044
set AT91C_TC1_RA    0xFFFA0054
set AT91C_TC1_RC    0xFFFA005C
set AT91C_TC1_IMR   0xFFFA006C
set AT91C_TC1_CV    0xFFFA0050
# ========== Register definition for TC2 peripheral ========== 
set AT91C_TC2_CMR   0xFFFA0084
set AT91C_TC2_CCR   0xFFFA0080
set AT91C_TC2_CV    0xFFFA0090
set AT91C_TC2_RA    0xFFFA0094
set AT91C_TC2_RB    0xFFFA0098
set AT91C_TC2_IDR   0xFFFA00A8
set AT91C_TC2_IMR   0xFFFA00AC
set AT91C_TC2_RC    0xFFFA009C
set AT91C_TC2_IER   0xFFFA00A4
set AT91C_TC2_SR    0xFFFA00A0
# ========== Register definition for TC3 peripheral ========== 
set AT91C_TC3_IER   0xFFFDC024
set AT91C_TC3_RB    0xFFFDC018
set AT91C_TC3_CMR   0xFFFDC004
set AT91C_TC3_RC    0xFFFDC01C
set AT91C_TC3_CCR   0xFFFDC000
set AT91C_TC3_SR    0xFFFDC020
set AT91C_TC3_CV    0xFFFDC010
set AT91C_TC3_RA    0xFFFDC014
set AT91C_TC3_IDR   0xFFFDC028
set AT91C_TC3_IMR   0xFFFDC02C
# ========== Register definition for TC4 peripheral ========== 
set AT91C_TC4_CMR   0xFFFDC044
set AT91C_TC4_RC    0xFFFDC05C
set AT91C_TC4_SR    0xFFFDC060
set AT91C_TC4_RB    0xFFFDC058
set AT91C_TC4_IER   0xFFFDC064
set AT91C_TC4_CV    0xFFFDC050
set AT91C_TC4_RA    0xFFFDC054
set AT91C_TC4_IDR   0xFFFDC068
set AT91C_TC4_IMR   0xFFFDC06C
set AT91C_TC4_CCR   0xFFFDC040
# ========== Register definition for TC5 peripheral ========== 
set AT91C_TC5_RB    0xFFFDC098
set AT91C_TC5_RA    0xFFFDC094
set AT91C_TC5_CV    0xFFFDC090
set AT91C_TC5_CCR   0xFFFDC080
set AT91C_TC5_SR    0xFFFDC0A0
set AT91C_TC5_IER   0xFFFDC0A4
set AT91C_TC5_IDR   0xFFFDC0A8
set AT91C_TC5_RC    0xFFFDC09C
set AT91C_TC5_IMR   0xFFFDC0AC
set AT91C_TC5_CMR   0xFFFDC084
# ========== Register definition for TCB0 peripheral ========== 
set AT91C_TCB0_BMR  0xFFFA00C4
set AT91C_TCB0_BCR  0xFFFA00C0
# ========== Register definition for TCB1 peripheral ========== 
set AT91C_TCB1_BCR  0xFFFDC0C0
set AT91C_TCB1_BMR  0xFFFDC0C4
# ========== Register definition for PDC_MCI peripheral ========== 
set AT91C_MCI_RNCR  0xFFFA8114
set AT91C_MCI_TCR   0xFFFA810C
set AT91C_MCI_RCR   0xFFFA8104
set AT91C_MCI_TNPR  0xFFFA8118
set AT91C_MCI_RNPR  0xFFFA8110
set AT91C_MCI_RPR   0xFFFA8100
set AT91C_MCI_TNCR  0xFFFA811C
set AT91C_MCI_TPR   0xFFFA8108
set AT91C_MCI_PTSR  0xFFFA8124
set AT91C_MCI_PTCR  0xFFFA8120
# ========== Register definition for MCI peripheral ========== 
set AT91C_MCI_RDR   0xFFFA8030
set AT91C_MCI_CMDR  0xFFFA8014
set AT91C_MCI_VR    0xFFFA80FC
set AT91C_MCI_IDR   0xFFFA8048
set AT91C_MCI_DTOR  0xFFFA8008
set AT91C_MCI_TDR   0xFFFA8034
set AT91C_MCI_IER   0xFFFA8044
set AT91C_MCI_BLKR  0xFFFA8018
set AT91C_MCI_MR    0xFFFA8004
set AT91C_MCI_IMR   0xFFFA804C
set AT91C_MCI_CR    0xFFFA8000
set AT91C_MCI_ARGR  0xFFFA8010
set AT91C_MCI_SDCR  0xFFFA800C
set AT91C_MCI_SR    0xFFFA8040
set AT91C_MCI_RSPR  0xFFFA8020
# ========== Register definition for PDC_TWI peripheral ========== 
set AT91C_TWI_PTSR  0xFFFAC124
set AT91C_TWI_RPR   0xFFFAC100
set AT91C_TWI_RNCR  0xFFFAC114
set AT91C_TWI_RCR   0xFFFAC104
set AT91C_TWI_PTCR  0xFFFAC120
set AT91C_TWI_TPR   0xFFFAC108
set AT91C_TWI_RNPR  0xFFFAC110
set AT91C_TWI_TNPR  0xFFFAC118
set AT91C_TWI_TCR   0xFFFAC10C
set AT91C_TWI_TNCR  0xFFFAC11C
# ========== Register definition for TWI peripheral ========== 
set AT91C_TWI_THR   0xFFFAC034
set AT91C_TWI_IDR   0xFFFAC028
set AT91C_TWI_CWGR  0xFFFAC010
set AT91C_TWI_IADR  0xFFFAC00C
set AT91C_TWI_RHR   0xFFFAC030
set AT91C_TWI_IER   0xFFFAC024
set AT91C_TWI_MMR   0xFFFAC004
set AT91C_TWI_SR    0xFFFAC020
set AT91C_TWI_CR    0xFFFAC000
set AT91C_TWI_IMR   0xFFFAC02C
# ========== Register definition for PDC_US0 peripheral ========== 
set AT91C_US0_TCR   0xFFFB010C
set AT91C_US0_PTCR  0xFFFB0120
set AT91C_US0_RNCR  0xFFFB0114
set AT91C_US0_PTSR  0xFFFB0124
set AT91C_US0_TNCR  0xFFFB011C
set AT91C_US0_RNPR  0xFFFB0110
set AT91C_US0_RCR   0xFFFB0104
set AT91C_US0_TPR   0xFFFB0108
set AT91C_US0_TNPR  0xFFFB0118
set AT91C_US0_RPR   0xFFFB0100
# ========== Register definition for US0 peripheral ========== 
set AT91C_US0_RHR   0xFFFB0018
set AT91C_US0_NER   0xFFFB0044
set AT91C_US0_IER   0xFFFB0008
set AT91C_US0_CR    0xFFFB0000
set AT91C_US0_THR   0xFFFB001C
set AT91C_US0_CSR   0xFFFB0014
set AT91C_US0_BRGR  0xFFFB0020
set AT91C_US0_RTOR  0xFFFB0024
set AT91C_US0_TTGR  0xFFFB0028
set AT91C_US0_IDR   0xFFFB000C
set AT91C_US0_MR    0xFFFB0004
set AT91C_US0_IF    0xFFFB004C
set AT91C_US0_FIDI  0xFFFB0040
set AT91C_US0_IMR   0xFFFB0010
# ========== Register definition for PDC_US1 peripheral ========== 
set AT91C_US1_PTCR  0xFFFB4120
set AT91C_US1_RCR   0xFFFB4104
set AT91C_US1_RPR   0xFFFB4100
set AT91C_US1_PTSR  0xFFFB4124
set AT91C_US1_TPR   0xFFFB4108
set AT91C_US1_TCR   0xFFFB410C
set AT91C_US1_RNPR  0xFFFB4110
set AT91C_US1_TNCR  0xFFFB411C
set AT91C_US1_RNCR  0xFFFB4114
set AT91C_US1_TNPR  0xFFFB4118
# ========== Register definition for US1 peripheral ========== 
set AT91C_US1_THR   0xFFFB401C
set AT91C_US1_TTGR  0xFFFB4028
set AT91C_US1_BRGR  0xFFFB4020
set AT91C_US1_IDR   0xFFFB400C
set AT91C_US1_MR    0xFFFB4004
set AT91C_US1_RTOR  0xFFFB4024
set AT91C_US1_CR    0xFFFB4000
set AT91C_US1_IMR   0xFFFB4010
set AT91C_US1_FIDI  0xFFFB4040
set AT91C_US1_RHR   0xFFFB4018
set AT91C_US1_IER   0xFFFB4008
set AT91C_US1_CSR   0xFFFB4014
set AT91C_US1_IF    0xFFFB404C
set AT91C_US1_NER   0xFFFB4044
# ========== Register definition for PDC_US2 peripheral ========== 
set AT91C_US2_TNCR  0xFFFB811C
set AT91C_US2_RNCR  0xFFFB8114
set AT91C_US2_TNPR  0xFFFB8118
set AT91C_US2_PTCR  0xFFFB8120
set AT91C_US2_TCR   0xFFFB810C
set AT91C_US2_RPR   0xFFFB8100
set AT91C_US2_TPR   0xFFFB8108
set AT91C_US2_RCR   0xFFFB8104
set AT91C_US2_PTSR  0xFFFB8124
set AT91C_US2_RNPR  0xFFFB8110
# ========== Register definition for US2 peripheral ========== 
set AT91C_US2_RTOR  0xFFFB8024
set AT91C_US2_CSR   0xFFFB8014
set AT91C_US2_CR    0xFFFB8000
set AT91C_US2_BRGR  0xFFFB8020
set AT91C_US2_NER   0xFFFB8044
set AT91C_US2_FIDI  0xFFFB8040
set AT91C_US2_TTGR  0xFFFB8028
set AT91C_US2_RHR   0xFFFB8018
set AT91C_US2_IDR   0xFFFB800C
set AT91C_US2_THR   0xFFFB801C
set AT91C_US2_MR    0xFFFB8004
set AT91C_US2_IMR   0xFFFB8010
set AT91C_US2_IF    0xFFFB804C
set AT91C_US2_IER   0xFFFB8008
# ========== Register definition for PDC_US3 peripheral ========== 
set AT91C_US3_RNPR  0xFFFD0110
set AT91C_US3_RNCR  0xFFFD0114
set AT91C_US3_PTSR  0xFFFD0124
set AT91C_US3_PTCR  0xFFFD0120
set AT91C_US3_TCR   0xFFFD010C
set AT91C_US3_TNPR  0xFFFD0118
set AT91C_US3_RCR   0xFFFD0104
set AT91C_US3_TPR   0xFFFD0108
set AT91C_US3_TNCR  0xFFFD011C
set AT91C_US3_RPR   0xFFFD0100
# ========== Register definition for US3 peripheral ========== 
set AT91C_US3_NER   0xFFFD0044
set AT91C_US3_RTOR  0xFFFD0024
set AT91C_US3_IDR   0xFFFD000C
set AT91C_US3_MR    0xFFFD0004
set AT91C_US3_FIDI  0xFFFD0040
set AT91C_US3_BRGR  0xFFFD0020
set AT91C_US3_THR   0xFFFD001C
set AT91C_US3_CR    0xFFFD0000
set AT91C_US3_IF    0xFFFD004C
set AT91C_US3_IER   0xFFFD0008
set AT91C_US3_TTGR  0xFFFD0028
set AT91C_US3_RHR   0xFFFD0018
set AT91C_US3_IMR   0xFFFD0010
set AT91C_US3_CSR   0xFFFD0014
# ========== Register definition for PDC_US4 peripheral ========== 
set AT91C_US4_TNCR  0xFFFD411C
set AT91C_US4_RPR   0xFFFD4100
set AT91C_US4_RNCR  0xFFFD4114
set AT91C_US4_TPR   0xFFFD4108
set AT91C_US4_PTCR  0xFFFD4120
set AT91C_US4_TCR   0xFFFD410C
set AT91C_US4_RCR   0xFFFD4104
set AT91C_US4_RNPR  0xFFFD4110
set AT91C_US4_TNPR  0xFFFD4118
set AT91C_US4_PTSR  0xFFFD4124
# ========== Register definition for US4 peripheral ========== 
set AT91C_US4_BRGR  0xFFFD4020
set AT91C_US4_THR   0xFFFD401C
set AT91C_US4_RTOR  0xFFFD4024
set AT91C_US4_IMR   0xFFFD4010
set AT91C_US4_NER   0xFFFD4044
set AT91C_US4_TTGR  0xFFFD4028
set AT91C_US4_FIDI  0xFFFD4040
set AT91C_US4_MR    0xFFFD4004
set AT91C_US4_IER   0xFFFD4008
set AT91C_US4_RHR   0xFFFD4018
set AT91C_US4_CR    0xFFFD4000
set AT91C_US4_IF    0xFFFD404C
set AT91C_US4_IDR   0xFFFD400C
set AT91C_US4_CSR   0xFFFD4014
# ========== Register definition for PDC_US5 peripheral ========== 
set AT91C_US5_PTSR  0xFFFD8124
set AT91C_US5_PTCR  0xFFFD8120
set AT91C_US5_TNPR  0xFFFD8118
set AT91C_US5_TNCR  0xFFFD811C
set AT91C_US5_RNPR  0xFFFD8110
set AT91C_US5_RNCR  0xFFFD8114
set AT91C_US5_RPR   0xFFFD8100
set AT91C_US5_TCR   0xFFFD810C
set AT91C_US5_TPR   0xFFFD8108
set AT91C_US5_RCR   0xFFFD8104
# ========== Register definition for US5 peripheral ========== 
set AT91C_US5_IF    0xFFFD804C
set AT91C_US5_RTOR  0xFFFD8024
set AT91C_US5_NER   0xFFFD8044
set AT91C_US5_IMR   0xFFFD8010
set AT91C_US5_RHR   0xFFFD8018
set AT91C_US5_CSR   0xFFFD8014
set AT91C_US5_MR    0xFFFD8004
set AT91C_US5_IDR   0xFFFD800C
set AT91C_US5_THR   0xFFFD801C
set AT91C_US5_FIDI  0xFFFD8040
set AT91C_US5_TTGR  0xFFFD8028
set AT91C_US5_BRGR  0xFFFD8020
set AT91C_US5_CR    0xFFFD8000
set AT91C_US5_IER   0xFFFD8008
# ========== Register definition for PDC_SSC0 peripheral ========== 
set AT91C_SSC0_TNPR 0xFFFBC118
set AT91C_SSC0_TCR  0xFFFBC10C
set AT91C_SSC0_RNCR 0xFFFBC114
set AT91C_SSC0_RPR  0xFFFBC100
set AT91C_SSC0_TPR  0xFFFBC108
set AT91C_SSC0_RCR  0xFFFBC104
set AT91C_SSC0_RNPR 0xFFFBC110
set AT91C_SSC0_PTCR 0xFFFBC120
set AT91C_SSC0_TNCR 0xFFFBC11C
set AT91C_SSC0_PTSR 0xFFFBC124
# ========== Register definition for SSC0 peripheral ========== 
set AT91C_SSC0_IMR  0xFFFBC04C
set AT91C_SSC0_RFMR 0xFFFBC014
set AT91C_SSC0_CR   0xFFFBC000
set AT91C_SSC0_TFMR 0xFFFBC01C
set AT91C_SSC0_CMR  0xFFFBC004
set AT91C_SSC0_IER  0xFFFBC044
set AT91C_SSC0_RHR  0xFFFBC020
set AT91C_SSC0_RCMR 0xFFFBC010
set AT91C_SSC0_SR   0xFFFBC040
set AT91C_SSC0_RSHR 0xFFFBC030
set AT91C_SSC0_THR  0xFFFBC024
set AT91C_SSC0_TCMR 0xFFFBC018
set AT91C_SSC0_IDR  0xFFFBC048
set AT91C_SSC0_TSHR 0xFFFBC034
# ========== Register definition for PDC_SPI0 peripheral ========== 
set AT91C_SPI0_PTCR 0xFFFC8120
set AT91C_SPI0_TCR  0xFFFC810C
set AT91C_SPI0_RPR  0xFFFC8100
set AT91C_SPI0_TPR  0xFFFC8108
set AT91C_SPI0_PTSR 0xFFFC8124
set AT91C_SPI0_RNCR 0xFFFC8114
set AT91C_SPI0_TNPR 0xFFFC8118
set AT91C_SPI0_RCR  0xFFFC8104
set AT91C_SPI0_RNPR 0xFFFC8110
set AT91C_SPI0_TNCR 0xFFFC811C
# ========== Register definition for SPI0 peripheral ========== 
set AT91C_SPI0_IDR  0xFFFC8018
set AT91C_SPI0_TDR  0xFFFC800C
set AT91C_SPI0_SR   0xFFFC8010
set AT91C_SPI0_CR   0xFFFC8000
set AT91C_SPI0_CSR  0xFFFC8030
set AT91C_SPI0_RDR  0xFFFC8008
set AT91C_SPI0_MR   0xFFFC8004
set AT91C_SPI0_IER  0xFFFC8014
set AT91C_SPI0_IMR  0xFFFC801C
# ========== Register definition for PDC_SPI1 peripheral ========== 
set AT91C_SPI1_PTCR 0xFFFCC120
set AT91C_SPI1_RNPR 0xFFFCC110
set AT91C_SPI1_RCR  0xFFFCC104
set AT91C_SPI1_TPR  0xFFFCC108
set AT91C_SPI1_PTSR 0xFFFCC124
set AT91C_SPI1_TNCR 0xFFFCC11C
set AT91C_SPI1_RPR  0xFFFCC100
set AT91C_SPI1_TCR  0xFFFCC10C
set AT91C_SPI1_RNCR 0xFFFCC114
set AT91C_SPI1_TNPR 0xFFFCC118
# ========== Register definition for SPI1 peripheral ========== 
set AT91C_SPI1_IER  0xFFFCC014
set AT91C_SPI1_RDR  0xFFFCC008
set AT91C_SPI1_SR   0xFFFCC010
set AT91C_SPI1_IMR  0xFFFCC01C
set AT91C_SPI1_TDR  0xFFFCC00C
set AT91C_SPI1_IDR  0xFFFCC018
set AT91C_SPI1_CSR  0xFFFCC030
set AT91C_SPI1_CR   0xFFFCC000
set AT91C_SPI1_MR   0xFFFCC004
# ========== Register definition for PDC_ADC peripheral ========== 
set AT91C_ADC_PTCR  0xFFFE0120
set AT91C_ADC_TPR   0xFFFE0108
set AT91C_ADC_TCR   0xFFFE010C
set AT91C_ADC_RCR   0xFFFE0104
set AT91C_ADC_PTSR  0xFFFE0124
set AT91C_ADC_RNPR  0xFFFE0110
set AT91C_ADC_RPR   0xFFFE0100
set AT91C_ADC_TNCR  0xFFFE011C
set AT91C_ADC_RNCR  0xFFFE0114
set AT91C_ADC_TNPR  0xFFFE0118
# ========== Register definition for ADC peripheral ========== 
set AT91C_ADC_CHDR  0xFFFE0014
set AT91C_ADC_CDR3  0xFFFE003C
set AT91C_ADC_CHER  0xFFFE0010
set AT91C_ADC_CHSR  0xFFFE0018
set AT91C_ADC_CR    0xFFFE0000
set AT91C_ADC_IMR   0xFFFE002C
set AT91C_ADC_MR    0xFFFE0004
set AT91C_ADC_CDR2  0xFFFE0038
set AT91C_ADC_SR    0xFFFE001C
set AT91C_ADC_LCDR  0xFFFE0020
set AT91C_ADC_IER   0xFFFE0024
set AT91C_ADC_CDR1  0xFFFE0034
set AT91C_ADC_IDR   0xFFFE0028
set AT91C_ADC_CDR0  0xFFFE0030
# ========== Register definition for EMACB peripheral ========== 
set AT91C_EMACB_USRIO 0xFFFC40C0
set AT91C_EMACB_RSE 0xFFFC4074
set AT91C_EMACB_SCF 0xFFFC4044
set AT91C_EMACB_STE 0xFFFC4084
set AT91C_EMACB_SA1H 0xFFFC409C
set AT91C_EMACB_ROV 0xFFFC4070
set AT91C_EMACB_TBQP 0xFFFC401C
set AT91C_EMACB_IMR 0xFFFC4030
set AT91C_EMACB_IER 0xFFFC4028
set AT91C_EMACB_REV 0xFFFC40FC
set AT91C_EMACB_SA3L 0xFFFC40A8
set AT91C_EMACB_ELE 0xFFFC4078
set AT91C_EMACB_HRT 0xFFFC4094
set AT91C_EMACB_SA2L 0xFFFC40A0
set AT91C_EMACB_RRE 0xFFFC406C
set AT91C_EMACB_FRO 0xFFFC404C
set AT91C_EMACB_TPQ 0xFFFC40BC
set AT91C_EMACB_ISR 0xFFFC4024
set AT91C_EMACB_TSR 0xFFFC4014
set AT91C_EMACB_RLE 0xFFFC4088
set AT91C_EMACB_USF 0xFFFC4080
set AT91C_EMACB_WOL 0xFFFC40C4
set AT91C_EMACB_TPF 0xFFFC408C
set AT91C_EMACB_PTR 0xFFFC4038
set AT91C_EMACB_TUND 0xFFFC4064
set AT91C_EMACB_MAN 0xFFFC4034
set AT91C_EMACB_RJA 0xFFFC407C
set AT91C_EMACB_SA4L 0xFFFC40B0
set AT91C_EMACB_CSE 0xFFFC4068
set AT91C_EMACB_HRB 0xFFFC4090
set AT91C_EMACB_ALE 0xFFFC4054
set AT91C_EMACB_SA1L 0xFFFC4098
set AT91C_EMACB_NCR 0xFFFC4000
set AT91C_EMACB_FTO 0xFFFC4040
set AT91C_EMACB_ECOL 0xFFFC4060
set AT91C_EMACB_DTF 0xFFFC4058
set AT91C_EMACB_SA4H 0xFFFC40B4
set AT91C_EMACB_FCSE 0xFFFC4050
set AT91C_EMACB_TID 0xFFFC40B8
set AT91C_EMACB_PFR 0xFFFC403C
set AT91C_EMACB_IDR 0xFFFC402C
set AT91C_EMACB_SA3H 0xFFFC40AC
set AT91C_EMACB_NSR 0xFFFC4008
set AT91C_EMACB_MCF 0xFFFC4048
set AT91C_EMACB_RBQP 0xFFFC4018
set AT91C_EMACB_RSR 0xFFFC4020
set AT91C_EMACB_SA2H 0xFFFC40A4
set AT91C_EMACB_NCFGR 0xFFFC4004
set AT91C_EMACB_LCOL 0xFFFC405C
# ========== Register definition for UDP peripheral ========== 
set AT91C_UDP_GLBSTATE 0xFFFA4004
set AT91C_UDP_FDR   0xFFFA4050
set AT91C_UDP_RSTEP 0xFFFA4028
set AT91C_UDP_FADDR 0xFFFA4008
set AT91C_UDP_NUM   0xFFFA4000
set AT91C_UDP_IDR   0xFFFA4014
set AT91C_UDP_IMR   0xFFFA4018
set AT91C_UDP_CSR   0xFFFA4030
set AT91C_UDP_IER   0xFFFA4010
set AT91C_UDP_ICR   0xFFFA4020
set AT91C_UDP_TXVC  0xFFFA4074
set AT91C_UDP_ISR   0xFFFA401C
# ========== Register definition for UHP peripheral ========== 
set AT91C_UHP_HcInterruptStatus 0x0050000C
set AT91C_UHP_HcCommandStatus 0x00500008
set AT91C_UHP_HcRhStatus 0x00500050
set AT91C_UHP_HcInterruptDisable 0x00500014
set AT91C_UHP_HcPeriodicStart 0x00500040
set AT91C_UHP_HcControlCurrentED 0x00500024
set AT91C_UHP_HcPeriodCurrentED 0x0050001C
set AT91C_UHP_HcBulkHeadED 0x00500028
set AT91C_UHP_HcRevision 0x00500000
set AT91C_UHP_HcBulkCurrentED 0x0050002C
set AT91C_UHP_HcRhDescriptorB 0x0050004C
set AT91C_UHP_HcControlHeadED 0x00500020
set AT91C_UHP_HcFmRemaining 0x00500038
set AT91C_UHP_HcHCCA 0x00500018
set AT91C_UHP_HcLSThreshold 0x00500044
set AT91C_UHP_HcRhPortStatus 0x00500054
set AT91C_UHP_HcInterruptEnable 0x00500010
set AT91C_UHP_HcFmNumber 0x0050003C
set AT91C_UHP_HcFmInterval 0x00500034
set AT91C_UHP_HcControl 0x00500004
set AT91C_UHP_HcBulkDoneHead 0x00500030
set AT91C_UHP_HcRhDescriptorA 0x00500048
# ========== Register definition for HECC peripheral ========== 
set AT91C_HECC_VR   0xFFFFE8FC
set AT91C_HECC_NPR  0xFFFFE810
set AT91C_HECC_SR   0xFFFFE808
set AT91C_HECC_PR   0xFFFFE80C
set AT91C_HECC_MR   0xFFFFE804
set AT91C_HECC_CR   0xFFFFE800
# ========== Register definition for HISI peripheral ========== 
set AT91C_HISI_PSIZE 0xFFFC0020
set AT91C_HISI_CR1  0xFFFC0000
set AT91C_HISI_R2YSET1 0xFFFC003C
set AT91C_HISI_CDBA 0xFFFC002C
set AT91C_HISI_IDR  0xFFFC0010
set AT91C_HISI_R2YSET2 0xFFFC0040
set AT91C_HISI_Y2RSET1 0xFFFC0034
set AT91C_HISI_PFBD 0xFFFC0028
set AT91C_HISI_CR2  0xFFFC0004
set AT91C_HISI_Y2RSET0 0xFFFC0030
set AT91C_HISI_PDECF 0xFFFC0024
set AT91C_HISI_IMR  0xFFFC0014
set AT91C_HISI_IER  0xFFFC000C
set AT91C_HISI_R2YSET0 0xFFFC0038
set AT91C_HISI_SR   0xFFFC0008

# *****************************************************************************
#               BASE ADDRESS DEFINITIONS FOR AT91SAM9260A
# *****************************************************************************
set AT91C_BASE_SYS       0xFFFFFD00
set AT91C_BASE_EBI       0xFFFFEA00
set AT91C_BASE_HECC      0xFFFFE800
set AT91C_BASE_SDRAMC    0xFFFFEA00
set AT91C_BASE_SMC       0xFFFFEC00
set AT91C_BASE_MATRIX    0xFFFFEE00
set AT91C_BASE_CCFG      0xFFFFEF10
set AT91C_BASE_PDC_DBGU  0xFFFFF300
set AT91C_BASE_DBGU      0xFFFFF200
set AT91C_BASE_AIC       0xFFFFF000
set AT91C_BASE_PIOA      0xFFFFF400
set AT91C_BASE_PIOB      0xFFFFF600
set AT91C_BASE_PIOC      0xFFFFF800
set AT91C_BASE_CKGR      0xFFFFFC20
set AT91C_BASE_PMC       0xFFFFFC00
set AT91C_BASE_RSTC      0xFFFFFD00
set AT91C_BASE_SHDWC     0xFFFFFD10
set AT91C_BASE_RTTC      0xFFFFFD20
set AT91C_BASE_PITC      0xFFFFFD30
set AT91C_BASE_WDTC      0xFFFFFD40
set AT91C_BASE_TC0       0xFFFA0000
set AT91C_BASE_TC1       0xFFFA0040
set AT91C_BASE_TC2       0xFFFA0080
set AT91C_BASE_TC3       0xFFFDC000
set AT91C_BASE_TC4       0xFFFDC040
set AT91C_BASE_TC5       0xFFFDC080
set AT91C_BASE_TCB0      0xFFFA0000
set AT91C_BASE_TCB1      0xFFFDC000
set AT91C_BASE_PDC_MCI   0xFFFA8100
set AT91C_BASE_MCI       0xFFFA8000
set AT91C_BASE_PDC_TWI   0xFFFAC100
set AT91C_BASE_TWI       0xFFFAC000
set AT91C_BASE_PDC_US0   0xFFFB0100
set AT91C_BASE_US0       0xFFFB0000
set AT91C_BASE_PDC_US1   0xFFFB4100
set AT91C_BASE_US1       0xFFFB4000
set AT91C_BASE_PDC_US2   0xFFFB8100
set AT91C_BASE_US2       0xFFFB8000
set AT91C_BASE_PDC_US3   0xFFFD0100
set AT91C_BASE_US3       0xFFFD0000
set AT91C_BASE_PDC_US4   0xFFFD4100
set AT91C_BASE_US4       0xFFFD4000
set AT91C_BASE_PDC_US5   0xFFFD8100
set AT91C_BASE_US5       0xFFFD8000
set AT91C_BASE_PDC_SSC0  0xFFFBC100
set AT91C_BASE_SSC0      0xFFFBC000
set AT91C_BASE_PDC_SPI0  0xFFFC8100
set AT91C_BASE_SPI0      0xFFFC8000
set AT91C_BASE_PDC_SPI1  0xFFFCC100
set AT91C_BASE_SPI1      0xFFFCC000
set AT91C_BASE_PDC_ADC   0xFFFE0100
set AT91C_BASE_ADC       0xFFFE0000
set AT91C_BASE_EMACB     0xFFFC4000
set AT91C_BASE_UDP       0xFFFA4000
set AT91C_BASE_UHP       0x00500000
set AT91C_BASE_HECC      0xFFFFE800
set AT91C_BASE_HISI      0xFFFC0000

# *****************************************************************************
#               PERIPHERAL ID DEFINITIONS FOR AT91SAM9260A
# *****************************************************************************
set AT91C_ID_FIQ     0
set AT91C_ID_SYS     1
set AT91C_ID_PIOA    2
set AT91C_ID_PIOB    3
set AT91C_ID_PIOC    4
set AT91C_ID_ADC     5
set AT91C_ID_US0     6
set AT91C_ID_US1     7
set AT91C_ID_US2     8
set AT91C_ID_MCI     9
set AT91C_ID_UDP    10
set AT91C_ID_TWI    11
set AT91C_ID_SPI0   12
set AT91C_ID_SPI1   13
set AT91C_ID_SSC0   14
set AT91C_ID_TC0    17
set AT91C_ID_TC1    18
set AT91C_ID_TC2    19
set AT91C_ID_UHP    20
set AT91C_ID_EMAC   21
set AT91C_ID_HISI   22
set AT91C_ID_US3    23
set AT91C_ID_US4    24
set AT91C_ID_US5    25
set AT91C_ID_TC3    26
set AT91C_ID_TC4    27
set AT91C_ID_TC5    28
set AT91C_ID_IRQ0   29
set AT91C_ID_IRQ1   30
set AT91C_ID_IRQ2   31

# *****************************************************************************
#               PIO DEFINITIONS FOR AT91SAM9260A
# *****************************************************************************
set AT91C_PIO_PA0        [expr 1 <<  0 ]
set AT91C_PA0_SPI0_MISO $AT91C_PIO_PA0
set AT91C_PA0_MCDB0    $AT91C_PIO_PA0
set AT91C_PIO_PA1        [expr 1 <<  1 ]
set AT91C_PA1_SPI0_MOSI $AT91C_PIO_PA1
set AT91C_PA1_MCCDB    $AT91C_PIO_PA1
set AT91C_PIO_PA10       [expr 1 << 10 ]
set AT91C_PA10_MCDA2    $AT91C_PIO_PA10
set AT91C_PA10_ETX2_0   $AT91C_PIO_PA10
set AT91C_PIO_PA11       [expr 1 << 11 ]
set AT91C_PA11_MCDA3    $AT91C_PIO_PA11
set AT91C_PA11_ETX3_0   $AT91C_PIO_PA11
set AT91C_PIO_PA12       [expr 1 << 12 ]
set AT91C_PA12_ETX0     $AT91C_PIO_PA12
set AT91C_PIO_PA13       [expr 1 << 13 ]
set AT91C_PA13_ETX1     $AT91C_PIO_PA13
set AT91C_PIO_PA14       [expr 1 << 14 ]
set AT91C_PA14_ERX0     $AT91C_PIO_PA14
set AT91C_PIO_PA15       [expr 1 << 15 ]
set AT91C_PA15_ERX1     $AT91C_PIO_PA15
set AT91C_PIO_PA16       [expr 1 << 16 ]
set AT91C_PA16_ETXEN    $AT91C_PIO_PA16
set AT91C_PIO_PA17       [expr 1 << 17 ]
set AT91C_PA17_ERXDV    $AT91C_PIO_PA17
set AT91C_PIO_PA18       [expr 1 << 18 ]
set AT91C_PA18_ERXER    $AT91C_PIO_PA18
set AT91C_PIO_PA19       [expr 1 << 19 ]
set AT91C_PA19_ETXCK    $AT91C_PIO_PA19
set AT91C_PIO_PA2        [expr 1 <<  2 ]
set AT91C_PA2_SPI0_SPCK $AT91C_PIO_PA2
set AT91C_PIO_PA20       [expr 1 << 20 ]
set AT91C_PA20_EMDC     $AT91C_PIO_PA20
set AT91C_PIO_PA21       [expr 1 << 21 ]
set AT91C_PA21_EMDIO    $AT91C_PIO_PA21
set AT91C_PIO_PA22       [expr 1 << 22 ]
set AT91C_PA22_ADTRG    $AT91C_PIO_PA22
set AT91C_PA22_ETXER    $AT91C_PIO_PA22
set AT91C_PIO_PA23       [expr 1 << 23 ]
set AT91C_PA23_TWD      $AT91C_PIO_PA23
set AT91C_PA23_ETX2_1   $AT91C_PIO_PA23
set AT91C_PIO_PA24       [expr 1 << 24 ]
set AT91C_PA24_TWCK     $AT91C_PIO_PA24
set AT91C_PA24_ETX3_1   $AT91C_PIO_PA24
set AT91C_PIO_PA25       [expr 1 << 25 ]
set AT91C_PA25_TCLK0    $AT91C_PIO_PA25
set AT91C_PA25_ERX2     $AT91C_PIO_PA25
set AT91C_PIO_PA26       [expr 1 << 26 ]
set AT91C_PA26_TIOA0    $AT91C_PIO_PA26
set AT91C_PA26_ERX3     $AT91C_PIO_PA26
set AT91C_PIO_PA27       [expr 1 << 27 ]
set AT91C_PA27_TIOA1    $AT91C_PIO_PA27
set AT91C_PA27_ERXCK    $AT91C_PIO_PA27
set AT91C_PIO_PA28       [expr 1 << 28 ]
set AT91C_PA28_TIOA2    $AT91C_PIO_PA28
set AT91C_PA28_ECRS     $AT91C_PIO_PA28
set AT91C_PIO_PA29       [expr 1 << 29 ]
set AT91C_PA29_SCK1     $AT91C_PIO_PA29
set AT91C_PA29_ECOL     $AT91C_PIO_PA29
set AT91C_PIO_PA3        [expr 1 <<  3 ]
set AT91C_PA3_SPI0_NPCS0 $AT91C_PIO_PA3
set AT91C_PA3_MCDB3    $AT91C_PIO_PA3
set AT91C_PIO_PA30       [expr 1 << 30 ]
set AT91C_PA30_SCK2     $AT91C_PIO_PA30
set AT91C_PA30_RXD4     $AT91C_PIO_PA30
set AT91C_PIO_PA31       [expr 1 << 31 ]
set AT91C_PA31_SCK0     $AT91C_PIO_PA31
set AT91C_PA31_TXD4     $AT91C_PIO_PA31
set AT91C_PIO_PA4        [expr 1 <<  4 ]
set AT91C_PA4_RTS2     $AT91C_PIO_PA4
set AT91C_PA4_MCDB2    $AT91C_PIO_PA4
set AT91C_PIO_PA5        [expr 1 <<  5 ]
set AT91C_PA5_CTS2     $AT91C_PIO_PA5
set AT91C_PA5_MCDB1    $AT91C_PIO_PA5
set AT91C_PIO_PA6        [expr 1 <<  6 ]
set AT91C_PA6_MCDA0    $AT91C_PIO_PA6
set AT91C_PIO_PA7        [expr 1 <<  7 ]
set AT91C_PA7_MCCDA    $AT91C_PIO_PA7
set AT91C_PIO_PA8        [expr 1 <<  8 ]
set AT91C_PA8_MCCK     $AT91C_PIO_PA8
set AT91C_PIO_PA9        [expr 1 <<  9 ]
set AT91C_PA9_MCDA1    $AT91C_PIO_PA9
set AT91C_PIO_PB0        [expr 1 <<  0 ]
set AT91C_PB0_SPI1_MISO $AT91C_PIO_PB0
set AT91C_PB0_TIOA3    $AT91C_PIO_PB0
set AT91C_PIO_PB1        [expr 1 <<  1 ]
set AT91C_PB1_SPI1_MOSI $AT91C_PIO_PB1
set AT91C_PB1_TIOB3    $AT91C_PIO_PB1
set AT91C_PIO_PB10       [expr 1 << 10 ]
set AT91C_PB10_TXD3     $AT91C_PIO_PB10
set AT91C_PB10_ISI_D8   $AT91C_PIO_PB10
set AT91C_PIO_PB11       [expr 1 << 11 ]
set AT91C_PB11_RXD3     $AT91C_PIO_PB11
set AT91C_PB11_ISI_D9   $AT91C_PIO_PB11
set AT91C_PIO_PB12       [expr 1 << 12 ]
set AT91C_PB12_TXD5     $AT91C_PIO_PB12
set AT91C_PB12_ISI_D10  $AT91C_PIO_PB12
set AT91C_PIO_PB13       [expr 1 << 13 ]
set AT91C_PB13_RXD5     $AT91C_PIO_PB13
set AT91C_PB13_ISI_D11  $AT91C_PIO_PB13
set AT91C_PIO_PB14       [expr 1 << 14 ]
set AT91C_PB14_DRXD     $AT91C_PIO_PB14
set AT91C_PIO_PB15       [expr 1 << 15 ]
set AT91C_PB15_DTXD     $AT91C_PIO_PB15
set AT91C_PIO_PB16       [expr 1 << 16 ]
set AT91C_PB16_TK0      $AT91C_PIO_PB16
set AT91C_PB16_TCLK3    $AT91C_PIO_PB16
set AT91C_PIO_PB17       [expr 1 << 17 ]
set AT91C_PB17_TF0      $AT91C_PIO_PB17
set AT91C_PB17_TCLK4    $AT91C_PIO_PB17
set AT91C_PIO_PB18       [expr 1 << 18 ]
set AT91C_PB18_TD0      $AT91C_PIO_PB18
set AT91C_PB18_TIOB4    $AT91C_PIO_PB18
set AT91C_PIO_PB19       [expr 1 << 19 ]
set AT91C_PB19_RD0      $AT91C_PIO_PB19
set AT91C_PB19_TIOB5    $AT91C_PIO_PB19
set AT91C_PIO_PB2        [expr 1 <<  2 ]
set AT91C_PB2_SPI1_SPCK $AT91C_PIO_PB2
set AT91C_PB2_TIOA4    $AT91C_PIO_PB2
set AT91C_PIO_PB20       [expr 1 << 20 ]
set AT91C_PB20_RK0      $AT91C_PIO_PB20
set AT91C_PB20_ISI_D0   $AT91C_PIO_PB20
set AT91C_PIO_PB21       [expr 1 << 21 ]
set AT91C_PB21_RF0      $AT91C_PIO_PB21
set AT91C_PB21_ISI_D1   $AT91C_PIO_PB21
set AT91C_PIO_PB22       [expr 1 << 22 ]
set AT91C_PB22_DSR0     $AT91C_PIO_PB22
set AT91C_PB22_ISI_D2   $AT91C_PIO_PB22
set AT91C_PIO_PB23       [expr 1 << 23 ]
set AT91C_PB23_DCD0     $AT91C_PIO_PB23
set AT91C_PB23_ISI_D3   $AT91C_PIO_PB23
set AT91C_PIO_PB24       [expr 1 << 24 ]
set AT91C_PB24_DTR0     $AT91C_PIO_PB24
set AT91C_PB24_ISI_D4   $AT91C_PIO_PB24
set AT91C_PIO_PB25       [expr 1 << 25 ]
set AT91C_PB25_RI0      $AT91C_PIO_PB25
set AT91C_PB25_ISI_D5   $AT91C_PIO_PB25
set AT91C_PIO_PB26       [expr 1 << 26 ]
set AT91C_PB26_RTS0     $AT91C_PIO_PB26
set AT91C_PB26_ISI_D6   $AT91C_PIO_PB26
set AT91C_PIO_PB27       [expr 1 << 27 ]
set AT91C_PB27_CTS0     $AT91C_PIO_PB27
set AT91C_PB27_ISI_D7   $AT91C_PIO_PB27
set AT91C_PIO_PB28       [expr 1 << 28 ]
set AT91C_PB28_RTS1     $AT91C_PIO_PB28
set AT91C_PB28_ISI_PCK  $AT91C_PIO_PB28
set AT91C_PIO_PB29       [expr 1 << 29 ]
set AT91C_PB29_CTS1     $AT91C_PIO_PB29
set AT91C_PB29_ISI_VSYNC $AT91C_PIO_PB29
set AT91C_PIO_PB3        [expr 1 <<  3 ]
set AT91C_PB3_SPI1_NPCS0 $AT91C_PIO_PB3
set AT91C_PB3_TIOA5    $AT91C_PIO_PB3
set AT91C_PIO_PB30       [expr 1 << 30 ]
set AT91C_PB30_PCK0_0   $AT91C_PIO_PB30
set AT91C_PB30_ISI_HSYNC $AT91C_PIO_PB30
set AT91C_PIO_PB31       [expr 1 << 31 ]
set AT91C_PB31_PCK1_0   $AT91C_PIO_PB31
set AT91C_PB31_ISI_MCK  $AT91C_PIO_PB31
set AT91C_PIO_PB4        [expr 1 <<  4 ]
set AT91C_PB4_TXD0     $AT91C_PIO_PB4
set AT91C_PIO_PB5        [expr 1 <<  5 ]
set AT91C_PB5_RXD0     $AT91C_PIO_PB5
set AT91C_PIO_PB6        [expr 1 <<  6 ]
set AT91C_PB6_TXD1     $AT91C_PIO_PB6
set AT91C_PB6_TCLK1    $AT91C_PIO_PB6
set AT91C_PIO_PB7        [expr 1 <<  7 ]
set AT91C_PB7_RXD1     $AT91C_PIO_PB7
set AT91C_PB7_TCLK2    $AT91C_PIO_PB7
set AT91C_PIO_PB8        [expr 1 <<  8 ]
set AT91C_PB8_TXD2     $AT91C_PIO_PB8
set AT91C_PIO_PB9        [expr 1 <<  9 ]
set AT91C_PB9_RXD2     $AT91C_PIO_PB9
set AT91C_PIO_PC0        [expr 1 <<  0 ]
set AT91C_PC0_AD0      $AT91C_PIO_PC0
set AT91C_PC0_SCK3     $AT91C_PIO_PC0
set AT91C_PIO_PC1        [expr 1 <<  1 ]
set AT91C_PC1_AD1      $AT91C_PIO_PC1
set AT91C_PC1_PCK0_1   $AT91C_PIO_PC1
set AT91C_PIO_PC10       [expr 1 << 10 ]
set AT91C_PC10_A25_CFRNW $AT91C_PIO_PC10
set AT91C_PC10_CTS3     $AT91C_PIO_PC10
set AT91C_PIO_PC11       [expr 1 << 11 ]
set AT91C_PC11_NCS2     $AT91C_PIO_PC11
set AT91C_PC11_SPI0_NPCS1 $AT91C_PIO_PC11
set AT91C_PIO_PC12       [expr 1 << 12 ]
set AT91C_PC12_IRQ0     $AT91C_PIO_PC12
set AT91C_PC12_NCS7     $AT91C_PIO_PC12
set AT91C_PIO_PC13       [expr 1 << 13 ]
set AT91C_PC13_FIQ      $AT91C_PIO_PC13
set AT91C_PC13_NCS6     $AT91C_PIO_PC13
set AT91C_PIO_PC14       [expr 1 << 14 ]
set AT91C_PC14_NCS3_NANDCS $AT91C_PIO_PC14
set AT91C_PC14_IRQ2     $AT91C_PIO_PC14
set AT91C_PIO_PC15       [expr 1 << 15 ]
set AT91C_PC15_NWAIT    $AT91C_PIO_PC15
set AT91C_PC15_IRQ1     $AT91C_PIO_PC15
set AT91C_PIO_PC16       [expr 1 << 16 ]
set AT91C_PC16_D16      $AT91C_PIO_PC16
set AT91C_PC16_SPI0_NPCS2 $AT91C_PIO_PC16
set AT91C_PIO_PC17       [expr 1 << 17 ]
set AT91C_PC17_D17      $AT91C_PIO_PC17
set AT91C_PC17_SPI0_NPCS3 $AT91C_PIO_PC17
set AT91C_PIO_PC18       [expr 1 << 18 ]
set AT91C_PC18_D18      $AT91C_PIO_PC18
set AT91C_PC18_SPI1_NPCS1_1 $AT91C_PIO_PC18
set AT91C_PIO_PC19       [expr 1 << 19 ]
set AT91C_PC19_D19      $AT91C_PIO_PC19
set AT91C_PC19_SPI1_NPCS2_1 $AT91C_PIO_PC19
set AT91C_PIO_PC2        [expr 1 <<  2 ]
set AT91C_PC2_AD2      $AT91C_PIO_PC2
set AT91C_PC2_PCK1_1   $AT91C_PIO_PC2
set AT91C_PIO_PC20       [expr 1 << 20 ]
set AT91C_PC20_D20      $AT91C_PIO_PC20
set AT91C_PC20_SPI1_NPCS3_1 $AT91C_PIO_PC20
set AT91C_PIO_PC21       [expr 1 << 21 ]
set AT91C_PC21_D21      $AT91C_PIO_PC21
set AT91C_PC21_EF100    $AT91C_PIO_PC21
set AT91C_PIO_PC22       [expr 1 << 22 ]
set AT91C_PC22_D22      $AT91C_PIO_PC22
set AT91C_PC22_TCLK5    $AT91C_PIO_PC22
set AT91C_PIO_PC23       [expr 1 << 23 ]
set AT91C_PC23_D23      $AT91C_PIO_PC23
set AT91C_PIO_PC24       [expr 1 << 24 ]
set AT91C_PC24_D24      $AT91C_PIO_PC24
set AT91C_PIO_PC25       [expr 1 << 25 ]
set AT91C_PC25_D25      $AT91C_PIO_PC25
set AT91C_PIO_PC26       [expr 1 << 26 ]
set AT91C_PC26_D26      $AT91C_PIO_PC26
set AT91C_PIO_PC27       [expr 1 << 27 ]
set AT91C_PC27_D27      $AT91C_PIO_PC27
set AT91C_PIO_PC28       [expr 1 << 28 ]
set AT91C_PC28_D28      $AT91C_PIO_PC28
set AT91C_PIO_PC29       [expr 1 << 29 ]
set AT91C_PC29_D29      $AT91C_PIO_PC29
set AT91C_PIO_PC3        [expr 1 <<  3 ]
set AT91C_PC3_AD3      $AT91C_PIO_PC3
set AT91C_PC3_SPI1_NPCS3_0 $AT91C_PIO_PC3
set AT91C_PIO_PC30       [expr 1 << 30 ]
set AT91C_PC30_D30      $AT91C_PIO_PC30
set AT91C_PIO_PC31       [expr 1 << 31 ]
set AT91C_PC31_D31      $AT91C_PIO_PC31
set AT91C_PIO_PC4        [expr 1 <<  4 ]
set AT91C_PC4_A23      $AT91C_PIO_PC4
set AT91C_PC4_SPI1_NPCS2_0 $AT91C_PIO_PC4
set AT91C_PIO_PC5        [expr 1 <<  5 ]
set AT91C_PC5_A24      $AT91C_PIO_PC5
set AT91C_PC5_SPI1_NPCS1_0 $AT91C_PIO_PC5
set AT91C_PIO_PC6        [expr 1 <<  6 ]
set AT91C_PC6_TIOB2    $AT91C_PIO_PC6
set AT91C_PC6_CFCE1    $AT91C_PIO_PC6
set AT91C_PIO_PC7        [expr 1 <<  7 ]
set AT91C_PC7_TIOB1    $AT91C_PIO_PC7
set AT91C_PC7_CFCE2    $AT91C_PIO_PC7
set AT91C_PIO_PC8        [expr 1 <<  8 ]
set AT91C_PC8_NCS4_CFCS0 $AT91C_PIO_PC8
set AT91C_PC8_RTS3     $AT91C_PIO_PC8
set AT91C_PIO_PC9        [expr 1 <<  9 ]
set AT91C_PC9_NCS5_CFCS1 $AT91C_PIO_PC9
set AT91C_PC9_TIOB0    $AT91C_PIO_PC9

# *****************************************************************************
#               MEMORY MAPPING DEFINITIONS FOR AT91SAM9260A
# *****************************************************************************
set AT91C_IROM 	 0x00100000
set AT91C_IROM_SIZE	 0x00008000
set AT91C_IRAM_1	 0x00200000
set AT91C_IRAM_1_SIZE	 0x00002000
set AT91C_IRAM_2	 0x00300000
set AT91C_IRAM_2_SIZE	 0x00002000
set AT91C_IRAM_MIN	 0x00300000
set AT91C_IRAM_MIN_SIZE	 0x00002000
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
set AT91C_EBI_CS6	 0x70000000
set AT91C_EBI_CS6_SIZE	 0x10000000
set AT91C_EBI_CS7	 0x80000000
set AT91C_EBI_CS7_SIZE	 0x10000000


# *****************************************************************************
#               ATTRIBUTES DEFINITIONS FOR AT91SAM9260A
# *****************************************************************************
array set AT91SAM9260A_att {
	DBGU 	{ LP 	DBGU_att }
	MCI 	{ LP 	MCI_att }
	PMC 	{ LP 	PMC_att }
	MATRIX 	{ LP 	MATRIX_att }
	SMC 	{ LP 	SMC_att }
	RSTC 	{ LP 	RSTC_att }
	CCFG 	{ LP 	CCFG_att }
	ISI 	{ LP 	HISI_att }
	EBI 	{ LP 	EBI_att }
	UHP 	{ LP 	UHP_att }
	SSC 	{ LP 	SSC0_att }
	WDTC 	{ LP 	WDTC_att }
	SDRAMC 	{ LP 	SDRAMC_att }
	SPI 	{ LP 	SPI0_att 	SPI1_att }
	USART 	{ LP 	US0_att 	US1_att 	US2_att 	US3_att 	US4_att 	US5_att }
	PITC 	{ LP 	PITC_att }
	SHDWC 	{ LP 	SHDWC_att }
	TCB 	{ LP 	TCB0_att 	TCB1_att }
	CKGR 	{ LP 	CKGR_att }
	AIC 	{ LP 	AIC_att }
	TWI 	{ LP 	TWI_att }
	ADC 	{ LP 	ADC_att }
	RTTC 	{ LP 	RTTC_att }
	UDP 	{ LP 	UDP_att }
	EMAC 	{ LP 	EMACB_att }
	TC 	{ LP 	TC0_att 	TC1_att 	TC2_att 	TC3_att 	TC4_att 	TC5_att }
	ECC 	{ LP 	HECC_att 	HECC_att }
	SYS 	{ LP 	SYS_att }
	PIO 	{ LP 	PIOA_att 	PIOB_att 	PIOC_att }
	PDC 	{ LP 	PDC_DBGU_att 	PDC_MCI_att 	PDC_TWI_att 	PDC_US0_att 	PDC_US1_att 	PDC_US2_att 	PDC_US3_att 	PDC_US4_att 	PDC_US5_att 	PDC_SSC0_att 	PDC_SPI0_att 	PDC_SPI1_att 	PDC_ADC_att }

}
# ========== Peripheral attributes for DBGU peripheral ========== 
array set DBGU_att {
	EXID 	{ R AT91C_DBGU_EXID 	RO }
	BRGR 	{ R AT91C_DBGU_BRGR 	RW }
	IDR 	{ R AT91C_DBGU_IDR 	WO }
	CSR 	{ R AT91C_DBGU_CSR 	RO }
	CIDR 	{ R AT91C_DBGU_CIDR 	RO }
	MR 	{ R AT91C_DBGU_MR 	RW }
	IMR 	{ R AT91C_DBGU_IMR 	RO }
	CR 	{ R AT91C_DBGU_CR 	WO }
	FNTR 	{ R AT91C_DBGU_FNTR 	RW }
	THR 	{ R AT91C_DBGU_THR 	WO }
	RHR 	{ R AT91C_DBGU_RHR 	RO }
	IER 	{ R AT91C_DBGU_IER 	WO }
	listeReg 	{ EXID BRGR IDR CSR CIDR MR IMR CR FNTR THR RHR IER  }

}

# ========== Peripheral attributes for MCI peripheral ========== 
array set MCI_att {
	RDR 	{ R AT91C_MCI_RDR 	RO }
	CMDR 	{ R AT91C_MCI_CMDR 	WO }
	VR 	{ R AT91C_MCI_VR 	RO }
	IDR 	{ R AT91C_MCI_IDR 	WO }
	DTOR 	{ R AT91C_MCI_DTOR 	RW }
	TDR 	{ R AT91C_MCI_TDR 	RO }
	IER 	{ R AT91C_MCI_IER 	WO }
	BLKR 	{ R AT91C_MCI_BLKR 	RW }
	MR 	{ R AT91C_MCI_MR 	RW }
	IMR 	{ R AT91C_MCI_IMR 	RO }
	CR 	{ R AT91C_MCI_CR 	WO }
	ARGR 	{ R AT91C_MCI_ARGR 	RW }
	SDCR 	{ R AT91C_MCI_SDCR 	RW }
	SR 	{ R AT91C_MCI_SR 	RO }
	RSPR 	{ R AT91C_MCI_RSPR 	RO  4 }
	listeReg 	{ RDR CMDR VR IDR DTOR TDR IER BLKR MR IMR CR ARGR SDCR SR RSPR  }

}

# ========== Peripheral attributes for PMC peripheral ========== 
array set PMC_att {
	PCER 	{ R AT91C_PMC_PCER 	WO }
	PCKR 	{ R AT91C_PMC_PCKR 	RW  8 }
	MCKR 	{ R AT91C_PMC_MCKR 	RW }
	PLLAR 	{ R AT91C_PMC_PLLAR 	RW }
	PCDR 	{ R AT91C_PMC_PCDR 	WO }
	SCSR 	{ R AT91C_PMC_SCSR 	RO }
	MCFR 	{ R AT91C_PMC_MCFR 	RO }
	IMR 	{ R AT91C_PMC_IMR 	RO }
	IER 	{ R AT91C_PMC_IER 	WO }
	MOR 	{ R AT91C_PMC_MOR 	RW }
	IDR 	{ R AT91C_PMC_IDR 	WO }
	PLLBR 	{ R AT91C_PMC_PLLBR 	RW }
	SCDR 	{ R AT91C_PMC_SCDR 	WO }
	PCSR 	{ R AT91C_PMC_PCSR 	RO }
	SCER 	{ R AT91C_PMC_SCER 	WO }
	SR 	{ R AT91C_PMC_SR 	RO }
	listeReg 	{ PCER PCKR MCKR PLLAR PCDR SCSR MCFR IMR IER MOR IDR PLLBR SCDR PCSR SCER SR  }

}

# ========== Peripheral attributes for MATRIX peripheral ========== 
array set MATRIX_att {
	MCFG0 	{ R AT91C_MATRIX_MCFG0 	WO }
	MCFG7 	{ R AT91C_MATRIX_MCFG7 	WO }
	SCFG1 	{ R AT91C_MATRIX_SCFG1 	RW }
	MCFG4 	{ R AT91C_MATRIX_MCFG4 	WO }
	VERSION 	{ R AT91C_MATRIX_VERSION 	RO }
	MCFG2 	{ R AT91C_MATRIX_MCFG2 	WO }
	PRBS4 	{ R AT91C_MATRIX_PRBS4 	RW }
	PRBS0 	{ R AT91C_MATRIX_PRBS0 	RW }
	SCFG3 	{ R AT91C_MATRIX_SCFG3 	RW }
	MCFG6 	{ R AT91C_MATRIX_MCFG6 	WO }
	EBI 	{ R AT91C_MATRIX_EBI 	RW }
	SCFG0 	{ R AT91C_MATRIX_SCFG0 	RW }
	PRBS3 	{ R AT91C_MATRIX_PRBS3 	RW }
	PRAS3 	{ R AT91C_MATRIX_PRAS3 	RW }
	PRAS0 	{ R AT91C_MATRIX_PRAS0 	RW }
	MCFG3 	{ R AT91C_MATRIX_MCFG3 	WO }
	PRAS1 	{ R AT91C_MATRIX_PRAS1 	RW }
	PRAS2 	{ R AT91C_MATRIX_PRAS2 	RW }
	SCFG2 	{ R AT91C_MATRIX_SCFG2 	RW }
	MCFG5 	{ R AT91C_MATRIX_MCFG5 	WO }
	MCFG1 	{ R AT91C_MATRIX_MCFG1 	WO }
	PRAS4 	{ R AT91C_MATRIX_PRAS4 	RW }
	MRCR 	{ R AT91C_MATRIX_MRCR 	RW }
	PRBS2 	{ R AT91C_MATRIX_PRBS2 	RW }
	SCFG4 	{ R AT91C_MATRIX_SCFG4 	RW }
	TEAKCFG 	{ R AT91C_MATRIX_TEAKCFG 	RW }
	PRBS1 	{ R AT91C_MATRIX_PRBS1 	RW }
	listeReg 	{ MCFG0 MCFG7 SCFG1 MCFG4 VERSION MCFG2 PRBS4 PRBS0 SCFG3 MCFG6 EBI SCFG0 PRBS3 PRAS3 PRAS0 MCFG3 PRAS1 PRAS2 SCFG2 MCFG5 MCFG1 PRAS4 MRCR PRBS2 SCFG4 TEAKCFG PRBS1  }

}

# ========== Peripheral attributes for SMC peripheral ========== 
array set SMC_att {
	CTRL1 	{ R AT91C_SMC_CTRL1 	RW }
	PULSE7 	{ R AT91C_SMC_PULSE7 	RW }
	PULSE6 	{ R AT91C_SMC_PULSE6 	RW }
	SETUP4 	{ R AT91C_SMC_SETUP4 	RW }
	PULSE3 	{ R AT91C_SMC_PULSE3 	RW }
	CYCLE5 	{ R AT91C_SMC_CYCLE5 	RW }
	CYCLE2 	{ R AT91C_SMC_CYCLE2 	RW }
	CTRL2 	{ R AT91C_SMC_CTRL2 	RW }
	CTRL0 	{ R AT91C_SMC_CTRL0 	RW }
	PULSE5 	{ R AT91C_SMC_PULSE5 	RW }
	PULSE1 	{ R AT91C_SMC_PULSE1 	RW }
	PULSE0 	{ R AT91C_SMC_PULSE0 	RW }
	CYCLE7 	{ R AT91C_SMC_CYCLE7 	RW }
	CTRL4 	{ R AT91C_SMC_CTRL4 	RW }
	CTRL3 	{ R AT91C_SMC_CTRL3 	RW }
	SETUP7 	{ R AT91C_SMC_SETUP7 	RW }
	CTRL7 	{ R AT91C_SMC_CTRL7 	RW }
	SETUP1 	{ R AT91C_SMC_SETUP1 	RW }
	CYCLE0 	{ R AT91C_SMC_CYCLE0 	RW }
	CTRL5 	{ R AT91C_SMC_CTRL5 	RW }
	CYCLE1 	{ R AT91C_SMC_CYCLE1 	RW }
	CTRL6 	{ R AT91C_SMC_CTRL6 	RW }
	SETUP0 	{ R AT91C_SMC_SETUP0 	RW }
	PULSE4 	{ R AT91C_SMC_PULSE4 	RW }
	SETUP5 	{ R AT91C_SMC_SETUP5 	RW }
	SETUP2 	{ R AT91C_SMC_SETUP2 	RW }
	CYCLE3 	{ R AT91C_SMC_CYCLE3 	RW }
	CYCLE6 	{ R AT91C_SMC_CYCLE6 	RW }
	SETUP6 	{ R AT91C_SMC_SETUP6 	RW }
	CYCLE4 	{ R AT91C_SMC_CYCLE4 	RW }
	PULSE2 	{ R AT91C_SMC_PULSE2 	RW }
	SETUP3 	{ R AT91C_SMC_SETUP3 	RW }
	listeReg 	{ CTRL1 PULSE7 PULSE6 SETUP4 PULSE3 CYCLE5 CYCLE2 CTRL2 CTRL0 PULSE5 PULSE1 PULSE0 CYCLE7 CTRL4 CTRL3 SETUP7 CTRL7 SETUP1 CYCLE0 CTRL5 CYCLE1 CTRL6 SETUP0 PULSE4 SETUP5 SETUP2 CYCLE3 CYCLE6 SETUP6 CYCLE4 PULSE2 SETUP3  }

}

# ========== Peripheral attributes for RSTC peripheral ========== 
array set RSTC_att {
	RCR 	{ R AT91C_RSTC_RCR 	WO }
	RMR 	{ R AT91C_RSTC_RMR 	RW }
	RSR 	{ R AT91C_RSTC_RSR 	RO }
	listeReg 	{ RCR RMR RSR  }

}

# ========== Peripheral attributes for CCFG peripheral ========== 
array set CCFG_att {
	MATRIXVERSION 	{ R AT91C_CCFG_MATRIXVERSION 	RO }
	EBICSA 	{ R AT91C_CCFG_EBICSA 	RW }
	listeReg 	{ MATRIXVERSION EBICSA  }

}

# ========== Peripheral attributes for ISI peripheral ========== 
array set HISI_att {
	PSIZE 	{ R AT91C_HISI_PSIZE 	RO }
	CR1 	{ R AT91C_HISI_CR1 	RW }
	R2YSET1 	{ R AT91C_HISI_R2YSET1 	RO }
	CDBA 	{ R AT91C_HISI_CDBA 	WO }
	IDR 	{ R AT91C_HISI_IDR 	RW }
	R2YSET2 	{ R AT91C_HISI_R2YSET2 	RO }
	Y2RSET1 	{ R AT91C_HISI_Y2RSET1 	RO }
	PFBD 	{ R AT91C_HISI_PFBD 	WO }
	CR2 	{ R AT91C_HISI_CR2 	RW }
	Y2RSET0 	{ R AT91C_HISI_Y2RSET0 	RO }
	PDECF 	{ R AT91C_HISI_PDECF 	WO }
	IMR 	{ R AT91C_HISI_IMR 	RW }
	IER 	{ R AT91C_HISI_IER 	RW }
	R2YSET0 	{ R AT91C_HISI_R2YSET0 	RO }
	SR 	{ R AT91C_HISI_SR 	RW }
	listeReg 	{ PSIZE CR1 R2YSET1 CDBA IDR R2YSET2 Y2RSET1 PFBD CR2 Y2RSET0 PDECF IMR IER R2YSET0 SR  }

}

# ========== Peripheral attributes for EBI peripheral ========== 
array set EBI_att {
	DUMMY 	{ R AT91C_EBI_DUMMY 	RW }
	listeReg 	{ DUMMY  }

}

# ========== Peripheral attributes for UHP peripheral ========== 
array set UHP_att {
	HcInterruptStatus 	{ R AT91C_UHP_HcInterruptStatus 	RW }
	HcCommandStatus 	{ R AT91C_UHP_HcCommandStatus 	RW }
	HcRhStatus 	{ R AT91C_UHP_HcRhStatus 	RW }
	HcInterruptDisable 	{ R AT91C_UHP_HcInterruptDisable 	RW }
	HcPeriodicStart 	{ R AT91C_UHP_HcPeriodicStart 	RW }
	HcControlCurrentED 	{ R AT91C_UHP_HcControlCurrentED 	RW }
	HcPeriodCurrentED 	{ R AT91C_UHP_HcPeriodCurrentED 	RW }
	HcBulkHeadED 	{ R AT91C_UHP_HcBulkHeadED 	RW }
	HcRevision 	{ R AT91C_UHP_HcRevision 	R }
	HcBulkCurrentED 	{ R AT91C_UHP_HcBulkCurrentED 	RW }
	HcRhDescriptorB 	{ R AT91C_UHP_HcRhDescriptorB 	RW }
	HcControlHeadED 	{ R AT91C_UHP_HcControlHeadED 	RW }
	HcFmRemaining 	{ R AT91C_UHP_HcFmRemaining 	RW }
	HcHCCA 	{ R AT91C_UHP_HcHCCA 	RW }
	HcLSThreshold 	{ R AT91C_UHP_HcLSThreshold 	RW }
	HcRhPortStatus 	{ R AT91C_UHP_HcRhPortStatus 	RW  2 }
	HcInterruptEnable 	{ R AT91C_UHP_HcInterruptEnable 	RW }
	HcFmNumber 	{ R AT91C_UHP_HcFmNumber 	RW }
	HcFmInterval 	{ R AT91C_UHP_HcFmInterval 	RW }
	HcControl 	{ R AT91C_UHP_HcControl 	RW }
	HcBulkDoneHead 	{ R AT91C_UHP_HcBulkDoneHead 	RW }
	HcRhDescriptorA 	{ R AT91C_UHP_HcRhDescriptorA 	RW }
	listeReg 	{ HcInterruptStatus HcCommandStatus HcRhStatus HcInterruptDisable HcPeriodicStart HcControlCurrentED HcPeriodCurrentED HcBulkHeadED HcRevision HcBulkCurrentED HcRhDescriptorB HcControlHeadED HcFmRemaining HcHCCA HcLSThreshold HcRhPortStatus HcInterruptEnable HcFmNumber HcFmInterval HcControl HcBulkDoneHead HcRhDescriptorA  }

}

# ========== Peripheral attributes for SSC peripheral ========== 
array set SSC0_att {
	IMR 	{ R AT91C_SSC0_IMR 	RO }
	RFMR 	{ R AT91C_SSC0_RFMR 	RW }
	CR 	{ R AT91C_SSC0_CR 	WO }
	TFMR 	{ R AT91C_SSC0_TFMR 	RW }
	CMR 	{ R AT91C_SSC0_CMR 	RW }
	IER 	{ R AT91C_SSC0_IER 	WO }
	RHR 	{ R AT91C_SSC0_RHR 	RO }
	RCMR 	{ R AT91C_SSC0_RCMR 	RW }
	SR 	{ R AT91C_SSC0_SR 	RO }
	RSHR 	{ R AT91C_SSC0_RSHR 	RO }
	THR 	{ R AT91C_SSC0_THR 	WO }
	TCMR 	{ R AT91C_SSC0_TCMR 	RW }
	IDR 	{ R AT91C_SSC0_IDR 	WO }
	TSHR 	{ R AT91C_SSC0_TSHR 	RW }
	listeReg 	{ IMR RFMR CR TFMR CMR IER RHR RCMR SR RSHR THR TCMR IDR TSHR  }

}

# ========== Peripheral attributes for WDTC peripheral ========== 
array set WDTC_att {
	WDCR 	{ R AT91C_WDTC_WDCR 	WO }
	WDSR 	{ R AT91C_WDTC_WDSR 	RO }
	WDMR 	{ R AT91C_WDTC_WDMR 	RW }
	listeReg 	{ WDCR WDSR WDMR  }

}

# ========== Peripheral attributes for SDRAMC peripheral ========== 
array set SDRAMC_att {
	MR 	{ R AT91C_SDRAMC_MR 	RW }
	IMR 	{ R AT91C_SDRAMC_IMR 	RO }
	LPR 	{ R AT91C_SDRAMC_LPR 	RW }
	ISR 	{ R AT91C_SDRAMC_ISR 	RO }
	IDR 	{ R AT91C_SDRAMC_IDR 	WO }
	CR 	{ R AT91C_SDRAMC_CR 	RW }
	TR 	{ R AT91C_SDRAMC_TR 	RW }
	MDR 	{ R AT91C_SDRAMC_MDR 	RO }
	HSR 	{ R AT91C_SDRAMC_HSR 	RW }
	IER 	{ R AT91C_SDRAMC_IER 	WO }
	listeReg 	{ MR IMR LPR ISR IDR CR TR MDR HSR IER  }

}

# ========== Peripheral attributes for SPI peripheral ========== 
array set SPI0_att {
	IDR 	{ R AT91C_SPI0_IDR 	WO }
	TDR 	{ R AT91C_SPI0_TDR 	WO }
	SR 	{ R AT91C_SPI0_SR 	RO }
	CR 	{ R AT91C_SPI0_CR 	RO }
	CSR 	{ R AT91C_SPI0_CSR 	RW  4 }
	RDR 	{ R AT91C_SPI0_RDR 	RO }
	MR 	{ R AT91C_SPI0_MR 	RW }
	IER 	{ R AT91C_SPI0_IER 	WO }
	IMR 	{ R AT91C_SPI0_IMR 	RO }
	listeReg 	{ IDR TDR SR CR CSR RDR MR IER IMR  }

}
array set SPI1_att {
	IER 	{ R AT91C_SPI1_IER 	WO }
	RDR 	{ R AT91C_SPI1_RDR 	RO }
	SR 	{ R AT91C_SPI1_SR 	RO }
	IMR 	{ R AT91C_SPI1_IMR 	RO }
	TDR 	{ R AT91C_SPI1_TDR 	WO }
	IDR 	{ R AT91C_SPI1_IDR 	WO }
	CSR 	{ R AT91C_SPI1_CSR 	RW  4 }
	CR 	{ R AT91C_SPI1_CR 	RO }
	MR 	{ R AT91C_SPI1_MR 	RW }
	listeReg 	{ IER RDR SR IMR TDR IDR CSR CR MR  }

}

# ========== Peripheral attributes for USART peripheral ========== 
array set US0_att {
	RHR 	{ R AT91C_US0_RHR 	RO }
	NER 	{ R AT91C_US0_NER 	RO }
	IER 	{ R AT91C_US0_IER 	WO }
	CR 	{ R AT91C_US0_CR 	WO }
	THR 	{ R AT91C_US0_THR 	WO }
	CSR 	{ R AT91C_US0_CSR 	RO }
	BRGR 	{ R AT91C_US0_BRGR 	RW }
	RTOR 	{ R AT91C_US0_RTOR 	RW }
	TTGR 	{ R AT91C_US0_TTGR 	RW }
	IDR 	{ R AT91C_US0_IDR 	WO }
	MR 	{ R AT91C_US0_MR 	RW }
	IF 	{ R AT91C_US0_IF 	RW }
	FIDI 	{ R AT91C_US0_FIDI 	RW }
	IMR 	{ R AT91C_US0_IMR 	RO }
	listeReg 	{ RHR NER IER CR THR CSR BRGR RTOR TTGR IDR MR IF FIDI IMR  }

}
array set US1_att {
	THR 	{ R AT91C_US1_THR 	WO }
	TTGR 	{ R AT91C_US1_TTGR 	RW }
	BRGR 	{ R AT91C_US1_BRGR 	RW }
	IDR 	{ R AT91C_US1_IDR 	WO }
	MR 	{ R AT91C_US1_MR 	RW }
	RTOR 	{ R AT91C_US1_RTOR 	RW }
	CR 	{ R AT91C_US1_CR 	WO }
	IMR 	{ R AT91C_US1_IMR 	RO }
	FIDI 	{ R AT91C_US1_FIDI 	RW }
	RHR 	{ R AT91C_US1_RHR 	RO }
	IER 	{ R AT91C_US1_IER 	WO }
	CSR 	{ R AT91C_US1_CSR 	RO }
	IF 	{ R AT91C_US1_IF 	RW }
	NER 	{ R AT91C_US1_NER 	RO }
	listeReg 	{ THR TTGR BRGR IDR MR RTOR CR IMR FIDI RHR IER CSR IF NER  }

}
array set US2_att {
	RTOR 	{ R AT91C_US2_RTOR 	RW }
	CSR 	{ R AT91C_US2_CSR 	RO }
	CR 	{ R AT91C_US2_CR 	WO }
	BRGR 	{ R AT91C_US2_BRGR 	RW }
	NER 	{ R AT91C_US2_NER 	RO }
	FIDI 	{ R AT91C_US2_FIDI 	RW }
	TTGR 	{ R AT91C_US2_TTGR 	RW }
	RHR 	{ R AT91C_US2_RHR 	RO }
	IDR 	{ R AT91C_US2_IDR 	WO }
	THR 	{ R AT91C_US2_THR 	WO }
	MR 	{ R AT91C_US2_MR 	RW }
	IMR 	{ R AT91C_US2_IMR 	RO }
	IF 	{ R AT91C_US2_IF 	RW }
	IER 	{ R AT91C_US2_IER 	WO }
	listeReg 	{ RTOR CSR CR BRGR NER FIDI TTGR RHR IDR THR MR IMR IF IER  }

}
array set US3_att {
	NER 	{ R AT91C_US3_NER 	RO }
	RTOR 	{ R AT91C_US3_RTOR 	RW }
	IDR 	{ R AT91C_US3_IDR 	WO }
	MR 	{ R AT91C_US3_MR 	RW }
	FIDI 	{ R AT91C_US3_FIDI 	RW }
	BRGR 	{ R AT91C_US3_BRGR 	RW }
	THR 	{ R AT91C_US3_THR 	WO }
	CR 	{ R AT91C_US3_CR 	WO }
	IF 	{ R AT91C_US3_IF 	RW }
	IER 	{ R AT91C_US3_IER 	WO }
	TTGR 	{ R AT91C_US3_TTGR 	RW }
	RHR 	{ R AT91C_US3_RHR 	RO }
	IMR 	{ R AT91C_US3_IMR 	RO }
	CSR 	{ R AT91C_US3_CSR 	RO }
	listeReg 	{ NER RTOR IDR MR FIDI BRGR THR CR IF IER TTGR RHR IMR CSR  }

}
array set US4_att {
	BRGR 	{ R AT91C_US4_BRGR 	RW }
	THR 	{ R AT91C_US4_THR 	WO }
	RTOR 	{ R AT91C_US4_RTOR 	RW }
	IMR 	{ R AT91C_US4_IMR 	RO }
	NER 	{ R AT91C_US4_NER 	RO }
	TTGR 	{ R AT91C_US4_TTGR 	RW }
	FIDI 	{ R AT91C_US4_FIDI 	RW }
	MR 	{ R AT91C_US4_MR 	RW }
	IER 	{ R AT91C_US4_IER 	WO }
	RHR 	{ R AT91C_US4_RHR 	RO }
	CR 	{ R AT91C_US4_CR 	WO }
	IF 	{ R AT91C_US4_IF 	RW }
	IDR 	{ R AT91C_US4_IDR 	WO }
	CSR 	{ R AT91C_US4_CSR 	RO }
	listeReg 	{ BRGR THR RTOR IMR NER TTGR FIDI MR IER RHR CR IF IDR CSR  }

}
array set US5_att {
	IF 	{ R AT91C_US5_IF 	RW }
	RTOR 	{ R AT91C_US5_RTOR 	RW }
	NER 	{ R AT91C_US5_NER 	RO }
	IMR 	{ R AT91C_US5_IMR 	RO }
	RHR 	{ R AT91C_US5_RHR 	RO }
	CSR 	{ R AT91C_US5_CSR 	RO }
	MR 	{ R AT91C_US5_MR 	RW }
	IDR 	{ R AT91C_US5_IDR 	WO }
	THR 	{ R AT91C_US5_THR 	WO }
	FIDI 	{ R AT91C_US5_FIDI 	RW }
	TTGR 	{ R AT91C_US5_TTGR 	RW }
	BRGR 	{ R AT91C_US5_BRGR 	RW }
	CR 	{ R AT91C_US5_CR 	WO }
	IER 	{ R AT91C_US5_IER 	WO }
	listeReg 	{ IF RTOR NER IMR RHR CSR MR IDR THR FIDI TTGR BRGR CR IER  }

}

# ========== Peripheral attributes for PITC peripheral ========== 
array set PITC_att {
	PIVR 	{ R AT91C_PITC_PIVR 	RO }
	PISR 	{ R AT91C_PITC_PISR 	RO }
	PIIR 	{ R AT91C_PITC_PIIR 	RO }
	PIMR 	{ R AT91C_PITC_PIMR 	RW }
	listeReg 	{ PIVR PISR PIIR PIMR  }

}

# ========== Peripheral attributes for SHDWC peripheral ========== 
array set SHDWC_att {
	SHSR 	{ R AT91C_SHDWC_SHSR 	RO }
	SHMR 	{ R AT91C_SHDWC_SHMR 	RW }
	SHCR 	{ R AT91C_SHDWC_SHCR 	WO }
	listeReg 	{ SHSR SHMR SHCR  }

}

# ========== Peripheral attributes for TCB peripheral ========== 
array set TCB0_att {
	BMR 	{ R AT91C_TCB0_BMR 	RW }
	BCR 	{ R AT91C_TCB0_BCR 	WO }
	listeReg 	{ BMR BCR  }

}
array set TCB1_att {
	BCR 	{ R AT91C_TCB1_BCR 	WO }
	BMR 	{ R AT91C_TCB1_BMR 	RW }
	listeReg 	{ BCR BMR  }

}

# ========== Peripheral attributes for CKGR peripheral ========== 
array set CKGR_att {
	MOR 	{ R AT91C_CKGR_MOR 	RW }
	PLLBR 	{ R AT91C_CKGR_PLLBR 	RW }
	MCFR 	{ R AT91C_CKGR_MCFR 	RO }
	PLLAR 	{ R AT91C_CKGR_PLLAR 	RW }
	listeReg 	{ MOR PLLBR MCFR PLLAR  }

}

# ========== Peripheral attributes for AIC peripheral ========== 
array set AIC_att {
	IVR 	{ R AT91C_AIC_IVR 	RO }
	SMR 	{ R AT91C_AIC_SMR 	RW 32 }
	FVR 	{ R AT91C_AIC_FVR 	RO }
	DCR 	{ R AT91C_AIC_DCR 	RW }
	EOICR 	{ R AT91C_AIC_EOICR 	WO }
	SVR 	{ R AT91C_AIC_SVR 	RW 32 }
	FFSR 	{ R AT91C_AIC_FFSR 	RO }
	ICCR 	{ R AT91C_AIC_ICCR 	WO }
	ISR 	{ R AT91C_AIC_ISR 	RO }
	IMR 	{ R AT91C_AIC_IMR 	RO }
	IPR 	{ R AT91C_AIC_IPR 	RO }
	FFER 	{ R AT91C_AIC_FFER 	WO }
	IECR 	{ R AT91C_AIC_IECR 	WO }
	ISCR 	{ R AT91C_AIC_ISCR 	WO }
	FFDR 	{ R AT91C_AIC_FFDR 	WO }
	CISR 	{ R AT91C_AIC_CISR 	RO }
	IDCR 	{ R AT91C_AIC_IDCR 	WO }
	SPU 	{ R AT91C_AIC_SPU 	RW }
	listeReg 	{ IVR SMR FVR DCR EOICR SVR FFSR ICCR ISR IMR IPR FFER IECR ISCR FFDR CISR IDCR SPU  }

}

# ========== Peripheral attributes for TWI peripheral ========== 
array set TWI_att {
	THR 	{ R AT91C_TWI_THR 	WO }
	IDR 	{ R AT91C_TWI_IDR 	WO }
	CWGR 	{ R AT91C_TWI_CWGR 	RW }
	IADR 	{ R AT91C_TWI_IADR 	RW }
	RHR 	{ R AT91C_TWI_RHR 	RO }
	IER 	{ R AT91C_TWI_IER 	WO }
	MMR 	{ R AT91C_TWI_MMR 	RW }
	SR 	{ R AT91C_TWI_SR 	RO }
	CR 	{ R AT91C_TWI_CR 	WO }
	IMR 	{ R AT91C_TWI_IMR 	RO }
	listeReg 	{ THR IDR CWGR IADR RHR IER MMR SR CR IMR  }

}

# ========== Peripheral attributes for ADC peripheral ========== 
array set ADC_att {
	CHDR 	{ R AT91C_ADC_CHDR 	WO }
	CDR3 	{ R AT91C_ADC_CDR3 	RO }
	CHER 	{ R AT91C_ADC_CHER 	WO }
	CHSR 	{ R AT91C_ADC_CHSR 	RO }
	CR 	{ R AT91C_ADC_CR 	WO }
	IMR 	{ R AT91C_ADC_IMR 	RO }
	MR 	{ R AT91C_ADC_MR 	RW }
	CDR2 	{ R AT91C_ADC_CDR2 	RO }
	SR 	{ R AT91C_ADC_SR 	RO }
	LCDR 	{ R AT91C_ADC_LCDR 	RO }
	IER 	{ R AT91C_ADC_IER 	WO }
	CDR1 	{ R AT91C_ADC_CDR1 	RO }
	IDR 	{ R AT91C_ADC_IDR 	WO }
	CDR0 	{ R AT91C_ADC_CDR0 	RO }
	listeReg 	{ CHDR CDR3 CHER CHSR CR IMR MR CDR2 SR LCDR IER CDR1 IDR CDR0  }

}

# ========== Peripheral attributes for RTTC peripheral ========== 
array set RTTC_att {
	RTSR 	{ R AT91C_RTTC_RTSR 	RO }
	RTMR 	{ R AT91C_RTTC_RTMR 	RW }
	RTVR 	{ R AT91C_RTTC_RTVR 	RO }
	RTAR 	{ R AT91C_RTTC_RTAR 	RW }
	listeReg 	{ RTSR RTMR RTVR RTAR  }

}

# ========== Peripheral attributes for UDP peripheral ========== 
array set UDP_att {
	GLBSTATE 	{ R AT91C_UDP_GLBSTATE 	RW }
	FDR 	{ R AT91C_UDP_FDR 	RW  6 }
	RSTEP 	{ R AT91C_UDP_RSTEP 	RO }
	FADDR 	{ R AT91C_UDP_FADDR 	RW }
	NUM 	{ R AT91C_UDP_NUM 	RO }
	IDR 	{ R AT91C_UDP_IDR 	WO }
	IMR 	{ R AT91C_UDP_IMR 	RO }
	CSR 	{ R AT91C_UDP_CSR 	RW  6 }
	IER 	{ R AT91C_UDP_IER 	WO }
	ICR 	{ R AT91C_UDP_ICR 	RO }
	TXVC 	{ R AT91C_UDP_TXVC 	RW }
	ISR 	{ R AT91C_UDP_ISR 	RO }
	listeReg 	{ GLBSTATE FDR RSTEP FADDR NUM IDR IMR CSR IER ICR TXVC ISR  }

}

# ========== Peripheral attributes for EMAC peripheral ========== 
array set EMACB_att {
	USRIO 	{ R AT91C_EMACB_USRIO 	RW }
	RSE 	{ R AT91C_EMACB_RSE 	RW }
	SCF 	{ R AT91C_EMACB_SCF 	RW }
	STE 	{ R AT91C_EMACB_STE 	RW }
	SA1H 	{ R AT91C_EMACB_SA1H 	RW }
	ROV 	{ R AT91C_EMACB_ROV 	RW }
	TBQP 	{ R AT91C_EMACB_TBQP 	RW }
	IMR 	{ R AT91C_EMACB_IMR 	RO }
	IER 	{ R AT91C_EMACB_IER 	WO }
	REV 	{ R AT91C_EMACB_REV 	RO }
	SA3L 	{ R AT91C_EMACB_SA3L 	RW }
	ELE 	{ R AT91C_EMACB_ELE 	RW }
	HRT 	{ R AT91C_EMACB_HRT 	RW }
	SA2L 	{ R AT91C_EMACB_SA2L 	RW }
	RRE 	{ R AT91C_EMACB_RRE 	RW }
	FRO 	{ R AT91C_EMACB_FRO 	RW }
	TPQ 	{ R AT91C_EMACB_TPQ 	RW }
	ISR 	{ R AT91C_EMACB_ISR 	RW }
	TSR 	{ R AT91C_EMACB_TSR 	RW }
	RLE 	{ R AT91C_EMACB_RLE 	RW }
	USF 	{ R AT91C_EMACB_USF 	RW }
	WOL 	{ R AT91C_EMACB_WOL 	RW }
	TPF 	{ R AT91C_EMACB_TPF 	RW }
	PTR 	{ R AT91C_EMACB_PTR 	RW }
	TUND 	{ R AT91C_EMACB_TUND 	RW }
	MAN 	{ R AT91C_EMACB_MAN 	RW }
	RJA 	{ R AT91C_EMACB_RJA 	RW }
	SA4L 	{ R AT91C_EMACB_SA4L 	RW }
	CSE 	{ R AT91C_EMACB_CSE 	RW }
	HRB 	{ R AT91C_EMACB_HRB 	RW }
	ALE 	{ R AT91C_EMACB_ALE 	RW }
	SA1L 	{ R AT91C_EMACB_SA1L 	RW }
	NCR 	{ R AT91C_EMACB_NCR 	RW }
	FTO 	{ R AT91C_EMACB_FTO 	RW }
	ECOL 	{ R AT91C_EMACB_ECOL 	RW }
	DTF 	{ R AT91C_EMACB_DTF 	RW }
	SA4H 	{ R AT91C_EMACB_SA4H 	RW }
	FCSE 	{ R AT91C_EMACB_FCSE 	RW }
	TID 	{ R AT91C_EMACB_TID 	RW }
	PFR 	{ R AT91C_EMACB_PFR 	RW }
	IDR 	{ R AT91C_EMACB_IDR 	WO }
	SA3H 	{ R AT91C_EMACB_SA3H 	RW }
	NSR 	{ R AT91C_EMACB_NSR 	RO }
	MCF 	{ R AT91C_EMACB_MCF 	RW }
	RBQP 	{ R AT91C_EMACB_RBQP 	RW }
	RSR 	{ R AT91C_EMACB_RSR 	RW }
	SA2H 	{ R AT91C_EMACB_SA2H 	RW }
	NCFGR 	{ R AT91C_EMACB_NCFGR 	RW }
	LCOL 	{ R AT91C_EMACB_LCOL 	RW }
	listeReg 	{ USRIO RSE SCF STE SA1H ROV TBQP IMR IER REV SA3L ELE HRT SA2L RRE FRO TPQ ISR TSR RLE USF WOL TPF PTR TUND MAN RJA SA4L CSE HRB ALE SA1L NCR FTO ECOL DTF SA4H FCSE TID PFR IDR SA3H NSR MCF RBQP RSR SA2H NCFGR LCOL  }

}

# ========== Peripheral attributes for TC peripheral ========== 
array set TC0_att {
	SR 	{ R AT91C_TC0_SR 	RO }
	RC 	{ R AT91C_TC0_RC 	RW }
	RB 	{ R AT91C_TC0_RB 	RW }
	CCR 	{ R AT91C_TC0_CCR 	WO }
	CMR 	{ R AT91C_TC0_CMR 	RW }
	IER 	{ R AT91C_TC0_IER 	WO }
	RA 	{ R AT91C_TC0_RA 	RW }
	IDR 	{ R AT91C_TC0_IDR 	WO }
	CV 	{ R AT91C_TC0_CV 	RW }
	IMR 	{ R AT91C_TC0_IMR 	RO }
	listeReg 	{ SR RC RB CCR CMR IER RA IDR CV IMR  }

}
array set TC1_att {
	RB 	{ R AT91C_TC1_RB 	RW }
	CCR 	{ R AT91C_TC1_CCR 	WO }
	IER 	{ R AT91C_TC1_IER 	WO }
	IDR 	{ R AT91C_TC1_IDR 	WO }
	SR 	{ R AT91C_TC1_SR 	RO }
	CMR 	{ R AT91C_TC1_CMR 	RW }
	RA 	{ R AT91C_TC1_RA 	RW }
	RC 	{ R AT91C_TC1_RC 	RW }
	IMR 	{ R AT91C_TC1_IMR 	RO }
	CV 	{ R AT91C_TC1_CV 	RW }
	listeReg 	{ RB CCR IER IDR SR CMR RA RC IMR CV  }

}
array set TC2_att {
	CMR 	{ R AT91C_TC2_CMR 	RW }
	CCR 	{ R AT91C_TC2_CCR 	WO }
	CV 	{ R AT91C_TC2_CV 	RW }
	RA 	{ R AT91C_TC2_RA 	RW }
	RB 	{ R AT91C_TC2_RB 	RW }
	IDR 	{ R AT91C_TC2_IDR 	WO }
	IMR 	{ R AT91C_TC2_IMR 	RO }
	RC 	{ R AT91C_TC2_RC 	RW }
	IER 	{ R AT91C_TC2_IER 	WO }
	SR 	{ R AT91C_TC2_SR 	RO }
	listeReg 	{ CMR CCR CV RA RB IDR IMR RC IER SR  }

}
array set TC3_att {
	IER 	{ R AT91C_TC3_IER 	WO }
	RB 	{ R AT91C_TC3_RB 	RW }
	CMR 	{ R AT91C_TC3_CMR 	RW }
	RC 	{ R AT91C_TC3_RC 	RW }
	CCR 	{ R AT91C_TC3_CCR 	WO }
	SR 	{ R AT91C_TC3_SR 	RO }
	CV 	{ R AT91C_TC3_CV 	RW }
	RA 	{ R AT91C_TC3_RA 	RW }
	IDR 	{ R AT91C_TC3_IDR 	WO }
	IMR 	{ R AT91C_TC3_IMR 	RO }
	listeReg 	{ IER RB CMR RC CCR SR CV RA IDR IMR  }

}
array set TC4_att {
	CMR 	{ R AT91C_TC4_CMR 	RW }
	RC 	{ R AT91C_TC4_RC 	RW }
	SR 	{ R AT91C_TC4_SR 	RO }
	RB 	{ R AT91C_TC4_RB 	RW }
	IER 	{ R AT91C_TC4_IER 	WO }
	CV 	{ R AT91C_TC4_CV 	RW }
	RA 	{ R AT91C_TC4_RA 	RW }
	IDR 	{ R AT91C_TC4_IDR 	WO }
	IMR 	{ R AT91C_TC4_IMR 	RO }
	CCR 	{ R AT91C_TC4_CCR 	WO }
	listeReg 	{ CMR RC SR RB IER CV RA IDR IMR CCR  }

}
array set TC5_att {
	RB 	{ R AT91C_TC5_RB 	RW }
	RA 	{ R AT91C_TC5_RA 	RW }
	CV 	{ R AT91C_TC5_CV 	RW }
	CCR 	{ R AT91C_TC5_CCR 	WO }
	SR 	{ R AT91C_TC5_SR 	RO }
	IER 	{ R AT91C_TC5_IER 	WO }
	IDR 	{ R AT91C_TC5_IDR 	WO }
	RC 	{ R AT91C_TC5_RC 	RW }
	IMR 	{ R AT91C_TC5_IMR 	RO }
	CMR 	{ R AT91C_TC5_CMR 	RW }
	listeReg 	{ RB RA CV CCR SR IER IDR RC IMR CMR  }

}

# ========== Peripheral attributes for ECC peripheral ========== 
array set HECC_att {
	VR 	{ R AT91C_HECC_VR 	RO }
	NPR 	{ R AT91C_HECC_NPR 	RO }
	SR 	{ R AT91C_HECC_SR 	RO }
	PR 	{ R AT91C_HECC_PR 	RO }
	MR 	{ R AT91C_HECC_MR 	RW }
	CR 	{ R AT91C_HECC_CR 	WO }
	listeReg 	{ VR NPR SR PR MR CR  }

}
array set HECC_att {
	VR 	{ R AT91C_HECC_VR 	RO }
	NPR 	{ R AT91C_HECC_NPR 	RO }
	SR 	{ R AT91C_HECC_SR 	RO }
	PR 	{ R AT91C_HECC_PR 	RO }
	MR 	{ R AT91C_HECC_MR 	RW }
	CR 	{ R AT91C_HECC_CR 	WO }
	listeReg 	{ VR NPR SR PR MR CR  }

}

# ========== Peripheral attributes for SYS peripheral ========== 
array set SYS_att {
	GPBR1 	{ R AT91C_SYS_GPBR1 	 }
	GPBR2 	{ R AT91C_SYS_GPBR2 	 }
	GPBR0 	{ R AT91C_SYS_GPBR0 	 }
	GPBR3 	{ R AT91C_SYS_GPBR3 	 }
	listeReg 	{ GPBR1 GPBR2 GPBR0 GPBR3  }

}

# ========== Peripheral attributes for PIO peripheral ========== 
array set PIOA_att {
	ODR 	{ R AT91C_PIOA_ODR 	WO }
	SODR 	{ R AT91C_PIOA_SODR 	WO }
	ISR 	{ R AT91C_PIOA_ISR 	RO }
	ABSR 	{ R AT91C_PIOA_ABSR 	RO }
	IER 	{ R AT91C_PIOA_IER 	WO }
	PPUDR 	{ R AT91C_PIOA_PPUDR 	WO }
	IMR 	{ R AT91C_PIOA_IMR 	RO }
	PER 	{ R AT91C_PIOA_PER 	WO }
	IFDR 	{ R AT91C_PIOA_IFDR 	WO }
	OWDR 	{ R AT91C_PIOA_OWDR 	WO }
	MDSR 	{ R AT91C_PIOA_MDSR 	RO }
	IDR 	{ R AT91C_PIOA_IDR 	WO }
	ODSR 	{ R AT91C_PIOA_ODSR 	RO }
	PPUSR 	{ R AT91C_PIOA_PPUSR 	RO }
	OWSR 	{ R AT91C_PIOA_OWSR 	RO }
	BSR 	{ R AT91C_PIOA_BSR 	WO }
	OWER 	{ R AT91C_PIOA_OWER 	WO }
	IFER 	{ R AT91C_PIOA_IFER 	WO }
	PDSR 	{ R AT91C_PIOA_PDSR 	RO }
	PPUER 	{ R AT91C_PIOA_PPUER 	WO }
	OSR 	{ R AT91C_PIOA_OSR 	RO }
	ASR 	{ R AT91C_PIOA_ASR 	WO }
	MDDR 	{ R AT91C_PIOA_MDDR 	WO }
	CODR 	{ R AT91C_PIOA_CODR 	WO }
	MDER 	{ R AT91C_PIOA_MDER 	WO }
	PDR 	{ R AT91C_PIOA_PDR 	WO }
	IFSR 	{ R AT91C_PIOA_IFSR 	RO }
	OER 	{ R AT91C_PIOA_OER 	WO }
	PSR 	{ R AT91C_PIOA_PSR 	RO }
	listeReg 	{ ODR SODR ISR ABSR IER PPUDR IMR PER IFDR OWDR MDSR IDR ODSR PPUSR OWSR BSR OWER IFER PDSR PPUER OSR ASR MDDR CODR MDER PDR IFSR OER PSR  }

}
array set PIOB_att {
	OWDR 	{ R AT91C_PIOB_OWDR 	WO }
	MDER 	{ R AT91C_PIOB_MDER 	WO }
	PPUSR 	{ R AT91C_PIOB_PPUSR 	RO }
	IMR 	{ R AT91C_PIOB_IMR 	RO }
	ASR 	{ R AT91C_PIOB_ASR 	WO }
	PPUDR 	{ R AT91C_PIOB_PPUDR 	WO }
	PSR 	{ R AT91C_PIOB_PSR 	RO }
	IER 	{ R AT91C_PIOB_IER 	WO }
	CODR 	{ R AT91C_PIOB_CODR 	WO }
	OWER 	{ R AT91C_PIOB_OWER 	WO }
	ABSR 	{ R AT91C_PIOB_ABSR 	RO }
	IFDR 	{ R AT91C_PIOB_IFDR 	WO }
	PDSR 	{ R AT91C_PIOB_PDSR 	RO }
	IDR 	{ R AT91C_PIOB_IDR 	WO }
	OWSR 	{ R AT91C_PIOB_OWSR 	RO }
	PDR 	{ R AT91C_PIOB_PDR 	WO }
	ODR 	{ R AT91C_PIOB_ODR 	WO }
	IFSR 	{ R AT91C_PIOB_IFSR 	RO }
	PPUER 	{ R AT91C_PIOB_PPUER 	WO }
	SODR 	{ R AT91C_PIOB_SODR 	WO }
	ISR 	{ R AT91C_PIOB_ISR 	RO }
	ODSR 	{ R AT91C_PIOB_ODSR 	RO }
	OSR 	{ R AT91C_PIOB_OSR 	RO }
	MDSR 	{ R AT91C_PIOB_MDSR 	RO }
	IFER 	{ R AT91C_PIOB_IFER 	WO }
	BSR 	{ R AT91C_PIOB_BSR 	WO }
	MDDR 	{ R AT91C_PIOB_MDDR 	WO }
	OER 	{ R AT91C_PIOB_OER 	WO }
	PER 	{ R AT91C_PIOB_PER 	WO }
	listeReg 	{ OWDR MDER PPUSR IMR ASR PPUDR PSR IER CODR OWER ABSR IFDR PDSR IDR OWSR PDR ODR IFSR PPUER SODR ISR ODSR OSR MDSR IFER BSR MDDR OER PER  }

}
array set PIOC_att {
	OWDR 	{ R AT91C_PIOC_OWDR 	WO }
	SODR 	{ R AT91C_PIOC_SODR 	WO }
	PPUER 	{ R AT91C_PIOC_PPUER 	WO }
	CODR 	{ R AT91C_PIOC_CODR 	WO }
	PSR 	{ R AT91C_PIOC_PSR 	RO }
	PDR 	{ R AT91C_PIOC_PDR 	WO }
	ODR 	{ R AT91C_PIOC_ODR 	WO }
	PPUSR 	{ R AT91C_PIOC_PPUSR 	RO }
	ABSR 	{ R AT91C_PIOC_ABSR 	RO }
	IFSR 	{ R AT91C_PIOC_IFSR 	RO }
	OER 	{ R AT91C_PIOC_OER 	WO }
	IMR 	{ R AT91C_PIOC_IMR 	RO }
	ASR 	{ R AT91C_PIOC_ASR 	WO }
	MDDR 	{ R AT91C_PIOC_MDDR 	WO }
	OWSR 	{ R AT91C_PIOC_OWSR 	RO }
	PER 	{ R AT91C_PIOC_PER 	WO }
	IDR 	{ R AT91C_PIOC_IDR 	WO }
	MDER 	{ R AT91C_PIOC_MDER 	WO }
	PDSR 	{ R AT91C_PIOC_PDSR 	RO }
	MDSR 	{ R AT91C_PIOC_MDSR 	RO }
	OWER 	{ R AT91C_PIOC_OWER 	WO }
	BSR 	{ R AT91C_PIOC_BSR 	WO }
	PPUDR 	{ R AT91C_PIOC_PPUDR 	WO }
	IFDR 	{ R AT91C_PIOC_IFDR 	WO }
	IER 	{ R AT91C_PIOC_IER 	WO }
	OSR 	{ R AT91C_PIOC_OSR 	RO }
	ODSR 	{ R AT91C_PIOC_ODSR 	RO }
	ISR 	{ R AT91C_PIOC_ISR 	RO }
	IFER 	{ R AT91C_PIOC_IFER 	WO }
	listeReg 	{ OWDR SODR PPUER CODR PSR PDR ODR PPUSR ABSR IFSR OER IMR ASR MDDR OWSR PER IDR MDER PDSR MDSR OWER BSR PPUDR IFDR IER OSR ODSR ISR IFER  }

}

# ========== Peripheral attributes for PDC peripheral ========== 
array set PDC_DBGU_att {
	TCR 	{ R AT91C_DBGU_TCR 	RW }
	RNPR 	{ R AT91C_DBGU_RNPR 	RW }
	TNPR 	{ R AT91C_DBGU_TNPR 	RW }
	TPR 	{ R AT91C_DBGU_TPR 	RW }
	RPR 	{ R AT91C_DBGU_RPR 	RW }
	RCR 	{ R AT91C_DBGU_RCR 	RW }
	RNCR 	{ R AT91C_DBGU_RNCR 	RW }
	PTCR 	{ R AT91C_DBGU_PTCR 	WO }
	PTSR 	{ R AT91C_DBGU_PTSR 	RO }
	TNCR 	{ R AT91C_DBGU_TNCR 	RW }
	listeReg 	{ TCR RNPR TNPR TPR RPR RCR RNCR PTCR PTSR TNCR  }

}
array set PDC_MCI_att {
	RNCR 	{ R AT91C_MCI_RNCR 	RW }
	TCR 	{ R AT91C_MCI_TCR 	RW }
	RCR 	{ R AT91C_MCI_RCR 	RW }
	TNPR 	{ R AT91C_MCI_TNPR 	RW }
	RNPR 	{ R AT91C_MCI_RNPR 	RW }
	RPR 	{ R AT91C_MCI_RPR 	RW }
	TNCR 	{ R AT91C_MCI_TNCR 	RW }
	TPR 	{ R AT91C_MCI_TPR 	RW }
	PTSR 	{ R AT91C_MCI_PTSR 	RO }
	PTCR 	{ R AT91C_MCI_PTCR 	WO }
	listeReg 	{ RNCR TCR RCR TNPR RNPR RPR TNCR TPR PTSR PTCR  }

}
array set PDC_TWI_att {
	PTSR 	{ R AT91C_TWI_PTSR 	RO }
	RPR 	{ R AT91C_TWI_RPR 	RW }
	RNCR 	{ R AT91C_TWI_RNCR 	RW }
	RCR 	{ R AT91C_TWI_RCR 	RW }
	PTCR 	{ R AT91C_TWI_PTCR 	WO }
	TPR 	{ R AT91C_TWI_TPR 	RW }
	RNPR 	{ R AT91C_TWI_RNPR 	RW }
	TNPR 	{ R AT91C_TWI_TNPR 	RW }
	TCR 	{ R AT91C_TWI_TCR 	RW }
	TNCR 	{ R AT91C_TWI_TNCR 	RW }
	listeReg 	{ PTSR RPR RNCR RCR PTCR TPR RNPR TNPR TCR TNCR  }

}
array set PDC_US0_att {
	TCR 	{ R AT91C_US0_TCR 	RW }
	PTCR 	{ R AT91C_US0_PTCR 	WO }
	RNCR 	{ R AT91C_US0_RNCR 	RW }
	PTSR 	{ R AT91C_US0_PTSR 	RO }
	TNCR 	{ R AT91C_US0_TNCR 	RW }
	RNPR 	{ R AT91C_US0_RNPR 	RW }
	RCR 	{ R AT91C_US0_RCR 	RW }
	TPR 	{ R AT91C_US0_TPR 	RW }
	TNPR 	{ R AT91C_US0_TNPR 	RW }
	RPR 	{ R AT91C_US0_RPR 	RW }
	listeReg 	{ TCR PTCR RNCR PTSR TNCR RNPR RCR TPR TNPR RPR  }

}
array set PDC_US1_att {
	PTCR 	{ R AT91C_US1_PTCR 	WO }
	RCR 	{ R AT91C_US1_RCR 	RW }
	RPR 	{ R AT91C_US1_RPR 	RW }
	PTSR 	{ R AT91C_US1_PTSR 	RO }
	TPR 	{ R AT91C_US1_TPR 	RW }
	TCR 	{ R AT91C_US1_TCR 	RW }
	RNPR 	{ R AT91C_US1_RNPR 	RW }
	TNCR 	{ R AT91C_US1_TNCR 	RW }
	RNCR 	{ R AT91C_US1_RNCR 	RW }
	TNPR 	{ R AT91C_US1_TNPR 	RW }
	listeReg 	{ PTCR RCR RPR PTSR TPR TCR RNPR TNCR RNCR TNPR  }

}
array set PDC_US2_att {
	TNCR 	{ R AT91C_US2_TNCR 	RW }
	RNCR 	{ R AT91C_US2_RNCR 	RW }
	TNPR 	{ R AT91C_US2_TNPR 	RW }
	PTCR 	{ R AT91C_US2_PTCR 	WO }
	TCR 	{ R AT91C_US2_TCR 	RW }
	RPR 	{ R AT91C_US2_RPR 	RW }
	TPR 	{ R AT91C_US2_TPR 	RW }
	RCR 	{ R AT91C_US2_RCR 	RW }
	PTSR 	{ R AT91C_US2_PTSR 	RO }
	RNPR 	{ R AT91C_US2_RNPR 	RW }
	listeReg 	{ TNCR RNCR TNPR PTCR TCR RPR TPR RCR PTSR RNPR  }

}
array set PDC_US3_att {
	RNPR 	{ R AT91C_US3_RNPR 	RW }
	RNCR 	{ R AT91C_US3_RNCR 	RW }
	PTSR 	{ R AT91C_US3_PTSR 	RO }
	PTCR 	{ R AT91C_US3_PTCR 	WO }
	TCR 	{ R AT91C_US3_TCR 	RW }
	TNPR 	{ R AT91C_US3_TNPR 	RW }
	RCR 	{ R AT91C_US3_RCR 	RW }
	TPR 	{ R AT91C_US3_TPR 	RW }
	TNCR 	{ R AT91C_US3_TNCR 	RW }
	RPR 	{ R AT91C_US3_RPR 	RW }
	listeReg 	{ RNPR RNCR PTSR PTCR TCR TNPR RCR TPR TNCR RPR  }

}
array set PDC_US4_att {
	TNCR 	{ R AT91C_US4_TNCR 	RW }
	RPR 	{ R AT91C_US4_RPR 	RW }
	RNCR 	{ R AT91C_US4_RNCR 	RW }
	TPR 	{ R AT91C_US4_TPR 	RW }
	PTCR 	{ R AT91C_US4_PTCR 	WO }
	TCR 	{ R AT91C_US4_TCR 	RW }
	RCR 	{ R AT91C_US4_RCR 	RW }
	RNPR 	{ R AT91C_US4_RNPR 	RW }
	TNPR 	{ R AT91C_US4_TNPR 	RW }
	PTSR 	{ R AT91C_US4_PTSR 	RO }
	listeReg 	{ TNCR RPR RNCR TPR PTCR TCR RCR RNPR TNPR PTSR  }

}
array set PDC_US5_att {
	PTSR 	{ R AT91C_US5_PTSR 	RO }
	PTCR 	{ R AT91C_US5_PTCR 	WO }
	TNPR 	{ R AT91C_US5_TNPR 	RW }
	TNCR 	{ R AT91C_US5_TNCR 	RW }
	RNPR 	{ R AT91C_US5_RNPR 	RW }
	RNCR 	{ R AT91C_US5_RNCR 	RW }
	RPR 	{ R AT91C_US5_RPR 	RW }
	TCR 	{ R AT91C_US5_TCR 	RW }
	TPR 	{ R AT91C_US5_TPR 	RW }
	RCR 	{ R AT91C_US5_RCR 	RW }
	listeReg 	{ PTSR PTCR TNPR TNCR RNPR RNCR RPR TCR TPR RCR  }

}
array set PDC_SSC0_att {
	TNPR 	{ R AT91C_SSC0_TNPR 	RW }
	TCR 	{ R AT91C_SSC0_TCR 	RW }
	RNCR 	{ R AT91C_SSC0_RNCR 	RW }
	RPR 	{ R AT91C_SSC0_RPR 	RW }
	TPR 	{ R AT91C_SSC0_TPR 	RW }
	RCR 	{ R AT91C_SSC0_RCR 	RW }
	RNPR 	{ R AT91C_SSC0_RNPR 	RW }
	PTCR 	{ R AT91C_SSC0_PTCR 	WO }
	TNCR 	{ R AT91C_SSC0_TNCR 	RW }
	PTSR 	{ R AT91C_SSC0_PTSR 	RO }
	listeReg 	{ TNPR TCR RNCR RPR TPR RCR RNPR PTCR TNCR PTSR  }

}
array set PDC_SPI0_att {
	PTCR 	{ R AT91C_SPI0_PTCR 	WO }
	TCR 	{ R AT91C_SPI0_TCR 	RW }
	RPR 	{ R AT91C_SPI0_RPR 	RW }
	TPR 	{ R AT91C_SPI0_TPR 	RW }
	PTSR 	{ R AT91C_SPI0_PTSR 	RO }
	RNCR 	{ R AT91C_SPI0_RNCR 	RW }
	TNPR 	{ R AT91C_SPI0_TNPR 	RW }
	RCR 	{ R AT91C_SPI0_RCR 	RW }
	RNPR 	{ R AT91C_SPI0_RNPR 	RW }
	TNCR 	{ R AT91C_SPI0_TNCR 	RW }
	listeReg 	{ PTCR TCR RPR TPR PTSR RNCR TNPR RCR RNPR TNCR  }

}
array set PDC_SPI1_att {
	PTCR 	{ R AT91C_SPI1_PTCR 	WO }
	RNPR 	{ R AT91C_SPI1_RNPR 	RW }
	RCR 	{ R AT91C_SPI1_RCR 	RW }
	TPR 	{ R AT91C_SPI1_TPR 	RW }
	PTSR 	{ R AT91C_SPI1_PTSR 	RO }
	TNCR 	{ R AT91C_SPI1_TNCR 	RW }
	RPR 	{ R AT91C_SPI1_RPR 	RW }
	TCR 	{ R AT91C_SPI1_TCR 	RW }
	RNCR 	{ R AT91C_SPI1_RNCR 	RW }
	TNPR 	{ R AT91C_SPI1_TNPR 	RW }
	listeReg 	{ PTCR RNPR RCR TPR PTSR TNCR RPR TCR RNCR TNPR  }

}
array set PDC_ADC_att {
	PTCR 	{ R AT91C_ADC_PTCR 	WO }
	TPR 	{ R AT91C_ADC_TPR 	RW }
	TCR 	{ R AT91C_ADC_TCR 	RW }
	RCR 	{ R AT91C_ADC_RCR 	RW }
	PTSR 	{ R AT91C_ADC_PTSR 	RO }
	RNPR 	{ R AT91C_ADC_RNPR 	RW }
	RPR 	{ R AT91C_ADC_RPR 	RW }
	TNCR 	{ R AT91C_ADC_TNCR 	RW }
	RNCR 	{ R AT91C_ADC_RNCR 	RW }
	TNPR 	{ R AT91C_ADC_TNPR 	RW }
	listeReg 	{ PTCR TPR TCR RCR PTSR RNPR RPR TNCR RNCR TNPR  }

}

# ========== PIO information ========== 

array set def_PIOA_att {
 	PA0 	{  SPI0_MISO   MCDB0  }
 	PA1 	{  SPI0_MOSI   MCCDB  }
 	PA10 	{  MCDA2   ETX2_0  }
 	PA11 	{  MCDA3   ETX3_0  }
 	PA12 	{  ETX0  }
 	PA13 	{  ETX1  }
 	PA14 	{  ERX0  }
 	PA15 	{  ERX1  }
 	PA16 	{  ETXEN  }
 	PA17 	{  ERXDV  }
 	PA18 	{  ERXER  }
 	PA19 	{  ETXCK  }
 	PA2 	{  SPI0_SPCK  }
 	PA20 	{  EMDC  }
 	PA21 	{  EMDIO  }
 	PA22 	{  ADTRG   ETXER  }
 	PA23 	{  TWD   ETX2_1  }
 	PA24 	{  TWCK   ETX3_1  }
 	PA25 	{  TCLK0   ERX2  }
 	PA26 	{  TIOA0   ERX3  }
 	PA27 	{  TIOA1   ERXCK  }
 	PA28 	{  TIOA2   ECRS  }
 	PA29 	{  SCK1   ECOL  }
 	PA3 	{  SPI0_NPCS0   MCDB3  }
 	PA30 	{  SCK2   RXD4  }
 	PA31 	{  SCK0   TXD4  }
 	PA4 	{  RTS2   MCDB2  }
 	PA5 	{  CTS2   MCDB1  }
 	PA6 	{  MCDA0  }
 	PA7 	{  MCCDA  }
 	PA8 	{  MCCK  }
 	PA9 	{  MCDA1  }
 }

array set def_PIOB_att {
 	PB0 	{  SPI1_MISO   TIOA3  }
 	PB1 	{  SPI1_MOSI   TIOB3  }
 	PB10 	{  TXD3   ISI_D8  }
 	PB11 	{  RXD3   ISI_D9  }
 	PB12 	{  TXD5   ISI_D10  }
 	PB13 	{  RXD5   ISI_D11  }
 	PB14 	{  DRXD  }
 	PB15 	{  DTXD  }
 	PB16 	{  TK0   TCLK3  }
 	PB17 	{  TF0   TCLK4  }
 	PB18 	{  TD0   TIOB4  }
 	PB19 	{  RD0   TIOB5  }
 	PB2 	{  SPI1_SPCK   TIOA4  }
 	PB20 	{  RK0   ISI_D0  }
 	PB21 	{  RF0   ISI_D1  }
 	PB22 	{  DSR0   ISI_D2  }
 	PB23 	{  DCD0   ISI_D3  }
 	PB24 	{  DTR0   ISI_D4  }
 	PB25 	{  RI0   ISI_D5  }
 	PB26 	{  RTS0   ISI_D6  }
 	PB27 	{  CTS0   ISI_D7  }
 	PB28 	{  RTS1   ISI_PCK  }
 	PB29 	{  CTS1   ISI_VSYNC  }
 	PB3 	{  SPI1_NPCS0   TIOA5  }
 	PB30 	{  PCK0_0   ISI_HSYNC  }
 	PB31 	{  PCK1_0   ISI_MCK  }
 	PB4 	{  TXD0  }
 	PB5 	{  RXD0  }
 	PB6 	{  TXD1   TCLK1  }
 	PB7 	{  RXD1   TCLK2  }
 	PB8 	{  TXD2  }
 	PB9 	{  RXD2  }
 }

array set def_PIOC_att {
 	PC0 	{  AD0   SCK3  }
 	PC1 	{  AD1   PCK0_1  }
 	PC10 	{  A25_CFRNW   CTS3  }
 	PC11 	{  NCS2   SPI0_NPCS1  }
 	PC12 	{  IRQ0   NCS7  }
 	PC13 	{  FIQ   NCS6  }
 	PC14 	{  NCS3_NANDCS   IRQ2  }
 	PC15 	{  NWAIT   IRQ1  }
 	PC16 	{  D16   SPI0_NPCS2  }
 	PC17 	{  D17   SPI0_NPCS3  }
 	PC18 	{  D18   SPI1_NPCS1_1  }
 	PC19 	{  D19   SPI1_NPCS2_1  }
 	PC2 	{  AD2   PCK1_1  }
 	PC20 	{  D20   SPI1_NPCS3_1  }
 	PC21 	{  D21   EF100  }
 	PC22 	{  D22   TCLK5  }
 	PC23 	{  D23  }
 	PC24 	{  D24  }
 	PC25 	{  D25  }
 	PC26 	{  D26  }
 	PC27 	{  D27  }
 	PC28 	{  D28  }
 	PC29 	{  D29  }
 	PC3 	{  AD3   SPI1_NPCS3_0  }
 	PC30 	{  D30  }
 	PC31 	{  D31  }
 	PC4 	{  A23   SPI1_NPCS2_0  }
 	PC5 	{  A24   SPI1_NPCS1_0  }
 	PC6 	{  TIOB2   CFCE1  }
 	PC7 	{  TIOB1   CFCE2  }
 	PC8 	{  NCS4_CFCS0   RTS3  }
 	PC9 	{  NCS5_CFCS1   TIOB0  }
 }
