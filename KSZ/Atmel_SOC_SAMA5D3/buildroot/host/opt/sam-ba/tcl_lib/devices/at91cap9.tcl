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
# File Name           : AT91CAP9.tcl
# Object              : AT91CAP9 definitions
# Generated           : AT91 SW Application Group  06/19/2006 (10:23:47)
# 
# CVS Reference       : /AT91CAP9.pl/1.2/Wed Jun 14 07:56:31 2006//
# CVS Reference       : /SYS_AT91CAP9.pl/1.1/Wed Jun 14 07:58:41 2006//
# CVS Reference       : /HECC_6143A.pl/1.1/Wed Feb 09 17:16:57 2005//
# CVS Reference       : /HBCRAMC1_XXXX.pl/1.1/Wed Jun 14 07:59:13 2006//
# CVS Reference       : /HSDRAMC1_6100A.pl/1.2/Mon Aug 09 10:52:25 2004//
# CVS Reference       : /DDRSDRC_XXXX.pl/1.2/Wed Jun 14 08:01:13 2006//
# CVS Reference       : /HSMC3_6105A.pl/1.4/Tue Nov 16 09:16:23 2004//
# CVS Reference       : /HMATRIX1_CAP9.pl/1.2/Wed Jun 14 08:02:21 2006//
# CVS Reference       : /CCR_CAP9.pl/1.1/Wed Jun 14 08:02:21 2006//
# CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb 03 09:02:11 2005//
# CVS Reference       : /DBGU_6059D.pl/1.1/Mon Jan 31 13:54:41 2005//
# CVS Reference       : /AIC_6075A.pl/1.1/Mon Jul 12 17:04:01 2004//
# CVS Reference       : /PIO_6057A.pl/1.2/Thu Feb 03 10:29:42 2005//
# CVS Reference       : /PMC_CAP9.pl/1.1/Mon Jun 19 07:59:02 2006//
# CVS Reference       : /RSTC_6098A.pl/1.3/Thu Nov 04 13:57:00 2004//
# CVS Reference       : /SHDWC_6122A.pl/1.3/Wed Oct 06 14:16:58 2004//
# CVS Reference       : /RTTC_6081A.pl/1.2/Thu Nov 04 13:57:22 2004//
# CVS Reference       : /PITC_6079A.pl/1.2/Thu Nov 04 13:56:22 2004//
# CVS Reference       : /WDTC_6080A.pl/1.3/Thu Nov 04 13:58:52 2004//
# CVS Reference       : /UDP_6083C.pl/1.3/Tue May 02 13:57:06 2006//
# CVS Reference       : /UDPHS_SAM9265.pl/1.5/Mon Feb 13 12:45:54 2006//
# CVS Reference       : /TC_6082A.pl/1.7/Wed Mar 09 16:31:51 2005//
# CVS Reference       : /MCI_6101E.pl/1.1/Fri Jun 03 13:20:23 2005//
# CVS Reference       : /TWI_6061B.pl/1.1/Tue Sep 13 15:05:42 2005//
# CVS Reference       : /US_6089C.pl/1.1/Mon Jan 31 13:56:02 2005//
# CVS Reference       : /SSC_6078A.pl/1.1/Tue Jul 13 07:10:41 2004//
# CVS Reference       : /AC97C_XXXX.pl/1.3/Tue Feb 22 17:08:27 2005//
# CVS Reference       : /SPI_6088D.pl/1.3/Fri May 20 14:23:02 2005//
# CVS Reference       : /CAN_6019B.pl/1.1/Mon Jan 31 13:54:30 2005//
# CVS Reference       : /AES_6149A.pl/1.12/Wed Nov 02 14:17:53 2005//
# CVS Reference       : /DES3_6150A.pl/1.1/Mon Jan 17 13:30:33 2005//
# CVS Reference       : /PWM_6044D.pl/1.2/Tue May 10 12:39:09 2005//
# CVS Reference       : /EMACB_6119A.pl/1.6/Wed Jul 13 15:25:00 2005//
# CVS Reference       : /ADC_6051C.pl/1.1/Mon Jan 31 13:12:40 2005//
# CVS Reference       : /ISI_xxxxx.pl/1.3/Thu Mar 03 11:11:48 2005//
# CVS Reference       : /LCDC_6063A.pl/1.3/Fri Dec 09 10:59:26 2005//
# CVS Reference       : /HDMA_XXXX.pl/1.2/Mon Oct 17 12:24:05 2005//
# CVS Reference       : /UHP_6127A.pl/1.1/Wed Feb 23 16:03:17 2005//
# ----------------------------------------------------------------------------


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
#              SOFTWARE API DEFINITION  FOR Busr Cellular RAM Controller Interface
# *****************************************************************************
# -------- BCRAMC_CR : (BCRAMC Offset: 0x0) BCRAM Controller Configuration Register -------- 
set AT91C_BCRAMC_EN       [expr 0x1 <<  0 ]
set AT91C_BCRAMC_CAS      [expr 0x7 <<  4 ]
set 	AT91C_BCRAMC_CAS_2                    [expr 0x2 <<  4 ]
set 	AT91C_BCRAMC_CAS_3                    [expr 0x3 <<  4 ]
set 	AT91C_BCRAMC_CAS_4                    [expr 0x4 <<  4 ]
set 	AT91C_BCRAMC_CAS_5                    [expr 0x5 <<  4 ]
set 	AT91C_BCRAMC_CAS_6                    [expr 0x6 <<  4 ]
set AT91C_BCRAMC_DBW      [expr 0x1 <<  8 ]
set 	AT91C_BCRAMC_DBW_32_BITS              [expr 0x0 <<  8 ]
set 	AT91C_BCRAMC_DBW_16_BITS              [expr 0x1 <<  8 ]
set AT91C_BCRAM_NWIR      [expr 0x3 << 12 ]
set 	AT91C_BCRAM_NWIR_64                   [expr 0x0 << 12 ]
set 	AT91C_BCRAM_NWIR_128                  [expr 0x1 << 12 ]
set 	AT91C_BCRAM_NWIR_256                  [expr 0x2 << 12 ]
set 	AT91C_BCRAM_NWIR_512                  [expr 0x3 << 12 ]
set AT91C_BCRAM_ADMX      [expr 0x1 << 16 ]
set 	AT91C_BCRAM_ADMX_NO_MUX               [expr 0x0 << 16 ]
set 	AT91C_BCRAM_ADMX_MUX                  [expr 0x1 << 16 ]
set AT91C_BCRAM_DS        [expr 0x3 << 20 ]
set 	AT91C_BCRAM_DS_FULL_DRIVE           [expr 0x0 << 20 ]
set 	AT91C_BCRAM_DS_HALF_DRIVE           [expr 0x1 << 20 ]
set 	AT91C_BCRAM_DS_QUARTER_DRIVE        [expr 0x2 << 20 ]
set AT91C_BCRAM_VFLAT     [expr 0x1 << 24 ]
set 	AT91C_BCRAM_VFLAT_VARIABLE             [expr 0x0 << 24 ]
set 	AT91C_BCRAM_VFLAT_FIXED                [expr 0x1 << 24 ]
# -------- BCRAMC_TPR : (BCRAMC Offset: 0x4) BCRAMC Timing Parameter Register -------- 
set AT91C_BCRAMC_TCW      [expr 0xF <<  0 ]
set 	AT91C_BCRAMC_TCW_0                    0x0
set 	AT91C_BCRAMC_TCW_1                    0x1
set 	AT91C_BCRAMC_TCW_2                    0x2
set 	AT91C_BCRAMC_TCW_3                    0x3
set 	AT91C_BCRAMC_TCW_4                    0x4
set 	AT91C_BCRAMC_TCW_5                    0x5
set 	AT91C_BCRAMC_TCW_6                    0x6
set 	AT91C_BCRAMC_TCW_7                    0x7
set 	AT91C_BCRAMC_TCW_8                    0x8
set 	AT91C_BCRAMC_TCW_9                    0x9
set 	AT91C_BCRAMC_TCW_10                   0xA
set 	AT91C_BCRAMC_TCW_11                   0xB
set 	AT91C_BCRAMC_TCW_12                   0xC
set 	AT91C_BCRAMC_TCW_13                   0xD
set 	AT91C_BCRAMC_TCW_14                   0xE
set 	AT91C_BCRAMC_TCW_15                   0xF
set AT91C_BCRAMC_TCRES    [expr 0x3 <<  4 ]
set 	AT91C_BCRAMC_TCRES_0                    [expr 0x0 <<  4 ]
set 	AT91C_BCRAMC_TCRES_1                    [expr 0x1 <<  4 ]
set 	AT91C_BCRAMC_TCRES_2                    [expr 0x2 <<  4 ]
set 	AT91C_BCRAMC_TCRES_3                    [expr 0x3 <<  4 ]
set AT91C_BCRAMC_TCKA     [expr 0xF <<  8 ]
set 	AT91C_BCRAMC_TCKA_0                    [expr 0x0 <<  8 ]
set 	AT91C_BCRAMC_TCKA_1                    [expr 0x1 <<  8 ]
set 	AT91C_BCRAMC_TCKA_2                    [expr 0x2 <<  8 ]
set 	AT91C_BCRAMC_TCKA_3                    [expr 0x3 <<  8 ]
set 	AT91C_BCRAMC_TCKA_4                    [expr 0x4 <<  8 ]
set 	AT91C_BCRAMC_TCKA_5                    [expr 0x5 <<  8 ]
set 	AT91C_BCRAMC_TCKA_6                    [expr 0x6 <<  8 ]
set 	AT91C_BCRAMC_TCKA_7                    [expr 0x7 <<  8 ]
set 	AT91C_BCRAMC_TCKA_8                    [expr 0x8 <<  8 ]
set 	AT91C_BCRAMC_TCKA_9                    [expr 0x9 <<  8 ]
set 	AT91C_BCRAMC_TCKA_10                   [expr 0xA <<  8 ]
set 	AT91C_BCRAMC_TCKA_11                   [expr 0xB <<  8 ]
set 	AT91C_BCRAMC_TCKA_12                   [expr 0xC <<  8 ]
set 	AT91C_BCRAMC_TCKA_13                   [expr 0xD <<  8 ]
set 	AT91C_BCRAMC_TCKA_14                   [expr 0xE <<  8 ]
set 	AT91C_BCRAMC_TCKA_15                   [expr 0xF <<  8 ]
# -------- BCRAMC_HSR : (BCRAMC Offset: 0x8) BCRAM Controller High Speed Register -------- 
set AT91C_BCRAMC_DA       [expr 0x1 <<  0 ]
set 	AT91C_BCRAMC_DA_DISABLE              0x0
set 	AT91C_BCRAMC_DA_ENABLE               0x1
# -------- BCRAMC_LPR : (BCRAMC Offset: 0xc) BCRAM Controller Low-power Register -------- 
set AT91C_BCRAMC_PAR      [expr 0x7 <<  0 ]
set 	AT91C_BCRAMC_PAR_FULL                 0x0
set 	AT91C_BCRAMC_PAR_PARTIAL_BOTTOM_HALF  0x1
set 	AT91C_BCRAMC_PAR_PARTIAL_BOTTOM_QUARTER 0x2
set 	AT91C_BCRAMC_PAR_PARTIAL_BOTTOM_EIGTH 0x3
set 	AT91C_BCRAMC_PAR_NONE                 0x4
set 	AT91C_BCRAMC_PAR_PARTIAL_TOP_HALF     0x5
set 	AT91C_BCRAMC_PAR_PARTIAL_TOP_QUARTER  0x6
set 	AT91C_BCRAMC_PAR_PARTIAL_TOP_EIGTH    0x7
set AT91C_BCRAMC_TCR      [expr 0x3 <<  4 ]
set 	AT91C_BCRAMC_TCR_85C                  [expr 0x0 <<  4 ]
set 	AT91C_BCRAMC_TCR_INTERNAL_OR_70C      [expr 0x1 <<  4 ]
set 	AT91C_BCRAMC_TCR_45C                  [expr 0x2 <<  4 ]
set 	AT91C_BCRAMC_TCR_15C                  [expr 0x3 <<  4 ]
set AT91C_BCRAMC_LPCB     [expr 0x3 <<  8 ]
set 	AT91C_BCRAMC_LPCB_DISABLE              [expr 0x0 <<  8 ]
set 	AT91C_BCRAMC_LPCB_STANDBY              [expr 0x1 <<  8 ]
set 	AT91C_BCRAMC_LPCB_DEEP_POWER_DOWN      [expr 0x2 <<  8 ]
# -------- BCRAMC_MDR : (BCRAMC Offset: 0x10) BCRAM Controller Memory Device Register -------- 
set AT91C_BCRAMC_MD       [expr 0x3 <<  0 ]
set 	AT91C_BCRAMC_MD_BCRAM_V10            0x0
set 	AT91C_BCRAMC_MD_BCRAM_V15            0x1
set 	AT91C_BCRAMC_MD_BCRAM_V20            0x2

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
#              SOFTWARE API DEFINITION  FOR DDR/SDRAM Controller
# *****************************************************************************
# -------- SDDRC_MR : (SDDRC Offset: 0x0)  -------- 
set AT91C_MODE            [expr 0xF <<  0 ]
set 	AT91C_MODE_NORMAL_CMD           0x0
set 	AT91C_MODE_NOP_CMD              0x1
set 	AT91C_MODE_PRCGALL_CMD          0x2
set 	AT91C_MODE_LMR_CMD              0x3
set 	AT91C_MODE_RFSH_CMD             0x4
set 	AT91C_MODE_EXT_LMR_CMD          0x5
set 	AT91C_MODE_DEEP_CMD             0x6
# -------- SDDRC_RTR : (SDDRC Offset: 0x4)  -------- 
set AT91C_COUNT           [expr 0xFFF <<  0 ]
# -------- SDDRC_CR : (SDDRC Offset: 0x8)  -------- 
set AT91C_NC              [expr 0x3 <<  0 ]
set 	AT91C_NC_DDR9_SDR8            0x0
set 	AT91C_NC_DDR10_SDR9           0x1
set 	AT91C_NC_DDR11_SDR10          0x2
set 	AT91C_NC_DDR12_SDR11          0x3
set AT91C_NR              [expr 0x3 <<  2 ]
set 	AT91C_NR_11                   [expr 0x0 <<  2 ]
set 	AT91C_NR_12                   [expr 0x1 <<  2 ]
set 	AT91C_NR_13                   [expr 0x2 <<  2 ]
set 	AT91C_NR_14                   [expr 0x3 <<  2 ]
set AT91C_CAS             [expr 0x7 <<  4 ]
set 	AT91C_CAS_2                    [expr 0x2 <<  4 ]
set 	AT91C_CAS_3                    [expr 0x3 <<  4 ]
set AT91C_DLL             [expr 0x1 <<  7 ]
set 	AT91C_DLL_RESET_DISABLED       [expr 0x0 <<  7 ]
set 	AT91C_DLL_RESET_ENABLED        [expr 0x1 <<  7 ]
set AT91C_DIC_DS          [expr 0x1 <<  8 ]
# -------- SDDRC_T0PR : (SDDRC Offset: 0xc)  -------- 
set AT91C_TRAS            [expr 0xF <<  0 ]
set 	AT91C_TRAS_0                    0x0
set 	AT91C_TRAS_1                    0x1
set 	AT91C_TRAS_2                    0x2
set 	AT91C_TRAS_3                    0x3
set 	AT91C_TRAS_4                    0x4
set 	AT91C_TRAS_5                    0x5
set 	AT91C_TRAS_6                    0x6
set 	AT91C_TRAS_7                    0x7
set 	AT91C_TRAS_8                    0x8
set 	AT91C_TRAS_9                    0x9
set 	AT91C_TRAS_10                   0xA
set 	AT91C_TRAS_11                   0xB
set 	AT91C_TRAS_12                   0xC
set 	AT91C_TRAS_13                   0xD
set 	AT91C_TRAS_14                   0xE
set 	AT91C_TRAS_15                   0xF
set AT91C_TRCD            [expr 0xF <<  4 ]
set 	AT91C_TRCD_0                    [expr 0x0 <<  4 ]
set 	AT91C_TRCD_1                    [expr 0x1 <<  4 ]
set 	AT91C_TRCD_2                    [expr 0x2 <<  4 ]
set 	AT91C_TRCD_3                    [expr 0x3 <<  4 ]
set 	AT91C_TRCD_4                    [expr 0x4 <<  4 ]
set 	AT91C_TRCD_5                    [expr 0x5 <<  4 ]
set 	AT91C_TRCD_6                    [expr 0x6 <<  4 ]
set 	AT91C_TRCD_7                    [expr 0x7 <<  4 ]
set 	AT91C_TRCD_8                    [expr 0x8 <<  4 ]
set 	AT91C_TRCD_9                    [expr 0x9 <<  4 ]
set 	AT91C_TRCD_10                   [expr 0xA <<  4 ]
set 	AT91C_TRCD_11                   [expr 0xB <<  4 ]
set 	AT91C_TRCD_12                   [expr 0xC <<  4 ]
set 	AT91C_TRCD_13                   [expr 0xD <<  4 ]
set 	AT91C_TRCD_14                   [expr 0xE <<  4 ]
set 	AT91C_TRCD_15                   [expr 0xF <<  4 ]
set AT91C_TWR             [expr 0xF <<  8 ]
set 	AT91C_TWR_0                    [expr 0x0 <<  8 ]
set 	AT91C_TWR_1                    [expr 0x1 <<  8 ]
set 	AT91C_TWR_2                    [expr 0x2 <<  8 ]
set 	AT91C_TWR_3                    [expr 0x3 <<  8 ]
set 	AT91C_TWR_4                    [expr 0x4 <<  8 ]
set 	AT91C_TWR_5                    [expr 0x5 <<  8 ]
set 	AT91C_TWR_6                    [expr 0x6 <<  8 ]
set 	AT91C_TWR_7                    [expr 0x7 <<  8 ]
set 	AT91C_TWR_8                    [expr 0x8 <<  8 ]
set 	AT91C_TWR_9                    [expr 0x9 <<  8 ]
set 	AT91C_TWR_10                   [expr 0xA <<  8 ]
set 	AT91C_TWR_11                   [expr 0xB <<  8 ]
set 	AT91C_TWR_12                   [expr 0xC <<  8 ]
set 	AT91C_TWR_13                   [expr 0xD <<  8 ]
set 	AT91C_TWR_14                   [expr 0xE <<  8 ]
set 	AT91C_TWR_15                   [expr 0xF <<  8 ]
set AT91C_TRC             [expr 0xF << 12 ]
set 	AT91C_TRC_0                    [expr 0x0 << 12 ]
set 	AT91C_TRC_1                    [expr 0x1 << 12 ]
set 	AT91C_TRC_2                    [expr 0x2 << 12 ]
set 	AT91C_TRC_3                    [expr 0x3 << 12 ]
set 	AT91C_TRC_4                    [expr 0x4 << 12 ]
set 	AT91C_TRC_5                    [expr 0x5 << 12 ]
set 	AT91C_TRC_6                    [expr 0x6 << 12 ]
set 	AT91C_TRC_7                    [expr 0x7 << 12 ]
set 	AT91C_TRC_8                    [expr 0x8 << 12 ]
set 	AT91C_TRC_9                    [expr 0x9 << 12 ]
set 	AT91C_TRC_10                   [expr 0xA << 12 ]
set 	AT91C_TRC_11                   [expr 0xB << 12 ]
set 	AT91C_TRC_12                   [expr 0xC << 12 ]
set 	AT91C_TRC_13                   [expr 0xD << 12 ]
set 	AT91C_TRC_14                   [expr 0xE << 12 ]
set 	AT91C_TRC_15                   [expr 0xF << 12 ]
set AT91C_TRP             [expr 0xF << 16 ]
set 	AT91C_TRP_0                    [expr 0x0 << 16 ]
set 	AT91C_TRP_1                    [expr 0x1 << 16 ]
set 	AT91C_TRP_2                    [expr 0x2 << 16 ]
set 	AT91C_TRP_3                    [expr 0x3 << 16 ]
set 	AT91C_TRP_4                    [expr 0x4 << 16 ]
set 	AT91C_TRP_5                    [expr 0x5 << 16 ]
set 	AT91C_TRP_6                    [expr 0x6 << 16 ]
set 	AT91C_TRP_7                    [expr 0x7 << 16 ]
set 	AT91C_TRP_8                    [expr 0x8 << 16 ]
set 	AT91C_TRP_9                    [expr 0x9 << 16 ]
set 	AT91C_TRP_10                   [expr 0xA << 16 ]
set 	AT91C_TRP_11                   [expr 0xB << 16 ]
set 	AT91C_TRP_12                   [expr 0xC << 16 ]
set 	AT91C_TRP_13                   [expr 0xD << 16 ]
set 	AT91C_TRP_14                   [expr 0xE << 16 ]
set 	AT91C_TRP_15                   [expr 0xF << 16 ]
set AT91C_TRRD            [expr 0xF << 20 ]
set 	AT91C_TRRD_0                    [expr 0x0 << 20 ]
set 	AT91C_TRRD_1                    [expr 0x1 << 20 ]
set 	AT91C_TRRD_2                    [expr 0x2 << 20 ]
set 	AT91C_TRRD_3                    [expr 0x3 << 20 ]
set 	AT91C_TRRD_4                    [expr 0x4 << 20 ]
set 	AT91C_TRRD_5                    [expr 0x5 << 20 ]
set 	AT91C_TRRD_6                    [expr 0x6 << 20 ]
set 	AT91C_TRRD_7                    [expr 0x7 << 20 ]
set 	AT91C_TRRD_8                    [expr 0x8 << 20 ]
set 	AT91C_TRRD_9                    [expr 0x9 << 20 ]
set 	AT91C_TRRD_10                   [expr 0xA << 20 ]
set 	AT91C_TRRD_11                   [expr 0xB << 20 ]
set 	AT91C_TRRD_12                   [expr 0xC << 20 ]
set 	AT91C_TRRD_13                   [expr 0xD << 20 ]
set 	AT91C_TRRD_14                   [expr 0xE << 20 ]
set 	AT91C_TRRD_15                   [expr 0xF << 20 ]
set AT91C_TWTR            [expr 0x1 << 24 ]
set 	AT91C_TWTR_0                    [expr 0x0 << 24 ]
set 	AT91C_TWTR_1                    [expr 0x1 << 24 ]
set AT91C_TMRD            [expr 0xF << 28 ]
set 	AT91C_TMRD_0                    [expr 0x0 << 28 ]
set 	AT91C_TMRD_1                    [expr 0x1 << 28 ]
set 	AT91C_TMRD_2                    [expr 0x2 << 28 ]
set 	AT91C_TMRD_3                    [expr 0x3 << 28 ]
set 	AT91C_TMRD_4                    [expr 0x4 << 28 ]
set 	AT91C_TMRD_5                    [expr 0x5 << 28 ]
set 	AT91C_TMRD_6                    [expr 0x6 << 28 ]
set 	AT91C_TMRD_7                    [expr 0x7 << 28 ]
set 	AT91C_TMRD_8                    [expr 0x8 << 28 ]
set 	AT91C_TMRD_9                    [expr 0x9 << 28 ]
set 	AT91C_TMRD_10                   [expr 0xA << 28 ]
set 	AT91C_TMRD_11                   [expr 0xB << 28 ]
set 	AT91C_TMRD_12                   [expr 0xC << 28 ]
set 	AT91C_TMRD_13                   [expr 0xD << 28 ]
set 	AT91C_TMRD_14                   [expr 0xE << 28 ]
set 	AT91C_TMRD_15                   [expr 0xF << 28 ]
# -------- SDDRC_T1PR : (SDDRC Offset: 0x10)  -------- 
set AT91C_TRFC            [expr 0x1F <<  0 ]
set 	AT91C_TRFC_0                    0x0
set 	AT91C_TRFC_1                    0x1
set 	AT91C_TRFC_2                    0x2
set 	AT91C_TRFC_3                    0x3
set 	AT91C_TRFC_4                    0x4
set 	AT91C_TRFC_5                    0x5
set 	AT91C_TRFC_6                    0x6
set 	AT91C_TRFC_7                    0x7
set 	AT91C_TRFC_8                    0x8
set 	AT91C_TRFC_9                    0x9
set 	AT91C_TRFC_10                   0xA
set 	AT91C_TRFC_11                   0xB
set 	AT91C_TRFC_12                   0xC
set 	AT91C_TRFC_13                   0xD
set 	AT91C_TRFC_14                   0xE
set 	AT91C_TRFC_15                   0xF
set AT91C_TXSNR           [expr 0xFF <<  8 ]
set 	AT91C_TXSNR_0                    [expr 0x0 <<  8 ]
set 	AT91C_TXSNR_1                    [expr 0x1 <<  8 ]
set 	AT91C_TXSNR_2                    [expr 0x2 <<  8 ]
set 	AT91C_TXSNR_3                    [expr 0x3 <<  8 ]
set 	AT91C_TXSNR_4                    [expr 0x4 <<  8 ]
set 	AT91C_TXSNR_5                    [expr 0x5 <<  8 ]
set 	AT91C_TXSNR_6                    [expr 0x6 <<  8 ]
set 	AT91C_TXSNR_7                    [expr 0x7 <<  8 ]
set 	AT91C_TXSNR_8                    [expr 0x8 <<  8 ]
set 	AT91C_TXSNR_9                    [expr 0x9 <<  8 ]
set 	AT91C_TXSNR_10                   [expr 0xA <<  8 ]
set 	AT91C_TXSNR_11                   [expr 0xB <<  8 ]
set 	AT91C_TXSNR_12                   [expr 0xC <<  8 ]
set 	AT91C_TXSNR_13                   [expr 0xD <<  8 ]
set 	AT91C_TXSNR_14                   [expr 0xE <<  8 ]
set 	AT91C_TXSNR_15                   [expr 0xF <<  8 ]
set AT91C_TXSRD           [expr 0xFF << 16 ]
set 	AT91C_TXSRD_0                    [expr 0x0 << 16 ]
set 	AT91C_TXSRD_1                    [expr 0x1 << 16 ]
set 	AT91C_TXSRD_2                    [expr 0x2 << 16 ]
set 	AT91C_TXSRD_3                    [expr 0x3 << 16 ]
set 	AT91C_TXSRD_4                    [expr 0x4 << 16 ]
set 	AT91C_TXSRD_5                    [expr 0x5 << 16 ]
set 	AT91C_TXSRD_6                    [expr 0x6 << 16 ]
set 	AT91C_TXSRD_7                    [expr 0x7 << 16 ]
set 	AT91C_TXSRD_8                    [expr 0x8 << 16 ]
set 	AT91C_TXSRD_9                    [expr 0x9 << 16 ]
set 	AT91C_TXSRD_10                   [expr 0xA << 16 ]
set 	AT91C_TXSRD_11                   [expr 0xB << 16 ]
set 	AT91C_TXSRD_12                   [expr 0xC << 16 ]
set 	AT91C_TXSRD_13                   [expr 0xD << 16 ]
set 	AT91C_TXSRD_14                   [expr 0xE << 16 ]
set 	AT91C_TXSRD_15                   [expr 0xF << 16 ]
# -------- SDDRC_HS : (SDDRC Offset: 0x14)  -------- 
set AT91C_DA              [expr 0x1 <<  0 ]
set AT91C_OVL             [expr 0x1 <<  1 ]
# -------- SDDRC_LPR : (SDDRC Offset: 0x18)  -------- 
set AT91C_LPCB            [expr 0x3 <<  0 ]
set AT91C_PASR            [expr 0x7 <<  4 ]
set AT91C_LP_TRC          [expr 0x3 <<  8 ]
set AT91C_DS              [expr 0x3 << 10 ]
set AT91C_TIMEOUT         [expr 0x3 << 12 ]
# -------- SDDRC_MDR : (SDDRC Offset: 0x1c)  -------- 
set AT91C_MD              [expr 0x3 <<  0 ]
set 	AT91C_MD_SDR_SDRAM            0x0
set 	AT91C_MD_LP_SDR_SDRAM         0x1
set 	AT91C_MD_DDR_SDRAM            0x2
set 	AT91C_MD_LP_DDR_SDRAM         0x3
set AT91C_B16MODE         [expr 0x1 <<  4 ]
set 	AT91C_B16MODE_32_BITS              [expr 0x0 <<  4 ]
set 	AT91C_B16MODE_16_BITS              [expr 0x1 <<  4 ]

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
#              SOFTWARE API DEFINITION  FOR Slave Priority Registers
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AHB Matrix Interface
# *****************************************************************************
# -------- MATRIX_MCFG : (MATRIX Offset: 0x0) Master Configuration Register rom -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_SCFG : (MATRIX Offset: 0x40) Slave Configuration Register -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_LCDC                 [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_2DGC                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_ISI                  [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_DMA                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_EMAC                 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_USB                  [expr 0x8 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
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
set AT91C_MATRIX_RCB9     [expr 0x1 <<  9 ]
set AT91C_MATRIX_RCB10    [expr 0x1 << 10 ]
set AT91C_MATRIX_RCB11    [expr 0x1 << 11 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AHB CCFG Interface
# *****************************************************************************
# -------- CCFG_UDPHS : (CCFG Offset: 0x8) UDPHS Configuration -------- 
set AT91C_CCFG_UDPHS_UDP_SELECT [expr 0x1 << 31 ]
set 	AT91C_CCFG_UDPHS_UDP_SELECT_UDPHS                [expr 0x0 << 31 ]
set 	AT91C_CCFG_UDPHS_UDP_SELECT_UDP                  [expr 0x1 << 31 ]
# -------- CCFG_EBICSA : (CCFG Offset: 0x10) EBI Chip Select Assignement Register -------- 
set AT91C_EBI_CS1A        [expr 0x1 <<  1 ]
set 	AT91C_EBI_CS1A_SMC                  [expr 0x0 <<  1 ]
set 	AT91C_EBI_CS1A_BCRAMC               [expr 0x1 <<  1 ]
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
set AT91C_EBI_DDRPUC      [expr 0x1 <<  9 ]
set AT91C_EBI_SUP         [expr 0x1 << 16 ]
set 	AT91C_EBI_SUP_1V8                  [expr 0x0 << 16 ]
set 	AT91C_EBI_SUP_3V3                  [expr 0x1 << 16 ]
set AT91C_EBI_LP          [expr 0x1 << 17 ]
set 	AT91C_EBI_LP_LOW_DRIVE            [expr 0x0 << 17 ]
set 	AT91C_EBI_LP_STD_DRIVE            [expr 0x1 << 17 ]
set AT91C_CCFG_DDR_SDR_SELECT [expr 0x1 << 31 ]
set 	AT91C_CCFG_DDR_SDR_SELECT_DDR                  [expr 0x0 << 31 ]
set 	AT91C_CCFG_DDR_SDR_SELECT_SDR                  [expr 0x1 << 31 ]
# -------- CCFG_BRIDGE : (CCFG Offset: 0x24) BRIDGE Configuration -------- 
set AT91C_CCFG_AES_TDES_SELECT [expr 0x1 << 31 ]
set 	AT91C_CCFG_AES_TDES_SELECT_AES                  [expr 0x0 << 31 ]
set 	AT91C_CCFG_AES_TDES_SELECT_TDES                 [expr 0x1 << 31 ]

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
#              SOFTWARE API DEFINITION  FOR UDPHS Enpoint FIFO data register
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR UDPHS Endpoint struct
# *****************************************************************************
# -------- UDPHS_EPTCFG : (UDPHS_EPT Offset: 0x0) UDPHS Endpoint Config Register -------- 
set AT91C_EPT_SIZE        [expr 0x1 <<  0 ]
set 	AT91C_EPT_SIZE_8                    0x0
set 	AT91C_EPT_SIZE_16                   0x1
set 	AT91C_EPT_SIZE_32                   0x2
set 	AT91C_EPT_SIZE_64                   0x3
set 	AT91C_EPT_SIZE_128                  0x4
set 	AT91C_EPT_SIZE_256                  0x5
set 	AT91C_EPT_SIZE_512                  0x6
set 	AT91C_EPT_SIZE_1024                 0x7
set AT91C_EPT_DIR         [expr 0x1 <<  3 ]
set 	AT91C_EPT_DIR_OUT                  [expr 0x0 <<  3 ]
set 	AT91C_EPT_DIR_IN                   [expr 0x1 <<  3 ]
set AT91C_EPT_TYPE        [expr 0x1 <<  4 ]
set 	AT91C_EPT_TYPE_CTL_EPT              [expr 0x0 <<  4 ]
set 	AT91C_EPT_TYPE_ISO_EPT              [expr 0x1 <<  4 ]
set 	AT91C_EPT_TYPE_BUL_EPT              [expr 0x2 <<  4 ]
set 	AT91C_EPT_TYPE_INT_EPT              [expr 0x3 <<  4 ]
set AT91C_BK_NUMBER       [expr 0x1 <<  6 ]
set 	AT91C_BK_NUMBER_0                    [expr 0x0 <<  6 ]
set 	AT91C_BK_NUMBER_1                    [expr 0x1 <<  6 ]
set 	AT91C_BK_NUMBER_2                    [expr 0x2 <<  6 ]
set 	AT91C_BK_NUMBER_3                    [expr 0x3 <<  6 ]
set AT91C_NB_TRANS        [expr 0x1 <<  8 ]
set AT91C_EPT_MAPD        [expr 0x1 << 31 ]
# -------- UDPHS_EPTCTLENB : (UDPHS_EPT Offset: 0x4) UDPHS Endpoint Control Enable Register -------- 
set AT91C_EPT_ENABL       [expr 0x1 <<  0 ]
set AT91C_AUTO_VALID      [expr 0x1 <<  1 ]
set AT91C_INTDIS_DMA      [expr 0x1 <<  3 ]
set AT91C_NYET_DIS        [expr 0x1 <<  4 ]
set AT91C_DATAX_RX        [expr 0x1 <<  6 ]
set AT91C_MDATA_RX        [expr 0x1 <<  7 ]
set AT91C_ERR_OVFLW       [expr 0x1 <<  8 ]
set AT91C_RX_BK_RDY       [expr 0x1 <<  9 ]
set AT91C_TX_COMPLT       [expr 0x1 << 10 ]
set AT91C_TX_PK_RDY_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_RX_SETUP_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_STALL_SNT_ERR_CRISO [expr 0x1 << 13 ]
set AT91C_NAK_IN          [expr 0x1 << 14 ]
set AT91C_NAK_OUT         [expr 0x1 << 15 ]
set AT91C_BUSY_BANK       [expr 0x1 << 18 ]
set AT91C_SHRT_PCKT       [expr 0x1 << 31 ]
# -------- UDPHS_EPTCTLDIS : (UDPHS_EPT Offset: 0x8) UDPHS Endpoint Control Disable Register -------- 
set AT91C_EPT_DISABL      [expr 0x1 <<  0 ]
set AT91C_AUTO_VALID      [expr 0x1 <<  1 ]
set AT91C_INTDIS_DMA      [expr 0x1 <<  3 ]
set AT91C_NYET_DIS        [expr 0x1 <<  4 ]
set AT91C_DATAX_RX        [expr 0x1 <<  6 ]
set AT91C_MDATA_RX        [expr 0x1 <<  7 ]
set AT91C_ERR_OVFLW       [expr 0x1 <<  8 ]
set AT91C_RX_BK_RDY       [expr 0x1 <<  9 ]
set AT91C_TX_COMPLT       [expr 0x1 << 10 ]
set AT91C_TX_PK_RDY_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_RX_SETUP_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_STALL_SNT_ERR_CRISO [expr 0x1 << 13 ]
set AT91C_NAK_IN          [expr 0x1 << 14 ]
set AT91C_NAK_OUT         [expr 0x1 << 15 ]
set AT91C_BUSY_BANK       [expr 0x1 << 18 ]
set AT91C_SHRT_PCKT       [expr 0x1 << 31 ]
# -------- UDPHS_EPTCTL : (UDPHS_EPT Offset: 0xc) UDPHS Endpoint Control Register -------- 
set AT91C_EPT_ENABL       [expr 0x1 <<  0 ]
set AT91C_AUTO_VALID      [expr 0x1 <<  1 ]
set AT91C_INTDIS_DMA      [expr 0x1 <<  3 ]
set AT91C_NYET_DIS        [expr 0x1 <<  4 ]
set AT91C_DATAX_RX        [expr 0x1 <<  6 ]
set AT91C_MDATA_RX        [expr 0x1 <<  7 ]
set AT91C_ERR_OVFLW       [expr 0x1 <<  8 ]
set AT91C_RX_BK_RDY       [expr 0x1 <<  9 ]
set AT91C_TX_COMPLT       [expr 0x1 << 10 ]
set AT91C_TX_PK_RDY_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_RX_SETUP_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_STALL_SNT_ERR_CRISO [expr 0x1 << 13 ]
set AT91C_NAK_IN          [expr 0x1 << 14 ]
set AT91C_NAK_OUT         [expr 0x1 << 15 ]
set AT91C_BUSY_BANK       [expr 0x1 << 18 ]
set AT91C_SHRT_PCKT       [expr 0x1 << 31 ]
# -------- UDPHS_EPTSETSTA : (UDPHS_EPT Offset: 0x14) UDPHS Endpoint Set Status Register -------- 
set AT91C_FRCESTALL       [expr 0x1 <<  5 ]
set AT91C_KILL_BANK       [expr 0x1 <<  9 ]
set AT91C_TX_PK_RDY       [expr 0x1 << 11 ]
# -------- UDPHS_EPTCLRSTA : (UDPHS_EPT Offset: 0x18) UDPHS Endpoint Clear Status Register -------- 
set AT91C_FRCESTALL       [expr 0x1 <<  5 ]
set AT91C_TOGGLESQ        [expr 0x1 <<  6 ]
set AT91C_RX_BK_RDY       [expr 0x1 <<  9 ]
set AT91C_TX_COMPLT       [expr 0x1 << 10 ]
set AT91C_RX_SETUP_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_STALL_SNT       [expr 0x1 << 13 ]
set AT91C_NAK_IN          [expr 0x1 << 14 ]
set AT91C_NAK_OUT         [expr 0x1 << 15 ]
# -------- UDPHS_EPTSTA : (UDPHS_EPT Offset: 0x1c) UDPHS Endpoint Status Register -------- 
set AT91C_FRCESTALL       [expr 0x1 <<  5 ]
set AT91C_TOGGLESQ_STA    [expr 0x3 <<  6 ]
set 	AT91C_TOGGLESQ_STA_00                   [expr 0x0 <<  6 ]
set 	AT91C_TOGGLESQ_STA_01                   [expr 0x1 <<  6 ]
set 	AT91C_TOGGLESQ_STA_10                   [expr 0x2 <<  6 ]
set 	AT91C_TOGGLESQ_STA_11                   [expr 0x3 <<  6 ]
set AT91C_ERR_OVFLW       [expr 0x1 <<  8 ]
set AT91C_RX_BK_RDY_KILL_BANK [expr 0x1 <<  9 ]
set AT91C_TX_COMPLT       [expr 0x1 << 10 ]
set AT91C_TX_PK_RDY_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_RX_SETUP_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_STALL_SNT_ERR_CRISO [expr 0x1 << 13 ]
set AT91C_NAK_IN          [expr 0x1 << 14 ]
set AT91C_NAK_OUT         [expr 0x1 << 15 ]
set AT91C_CURRENT_BANK_CONTROL_DIR [expr 0x3 << 16 ]
set 	AT91C_CURRENT_BANK_CONTROL_DIR_00                   [expr 0x0 << 16 ]
set 	AT91C_CURRENT_BANK_CONTROL_DIR_01                   [expr 0x1 << 16 ]
set 	AT91C_CURRENT_BANK_CONTROL_DIR_10                   [expr 0x2 << 16 ]
set 	AT91C_CURRENT_BANK_CONTROL_DIR_11                   [expr 0x3 << 16 ]
set AT91C_BUSY_BANK_STA   [expr 0x3 << 18 ]
set 	AT91C_BUSY_BANK_STA_00                   [expr 0x0 << 18 ]
set 	AT91C_BUSY_BANK_STA_01                   [expr 0x1 << 18 ]
set 	AT91C_BUSY_BANK_STA_10                   [expr 0x2 << 18 ]
set 	AT91C_BUSY_BANK_STA_11                   [expr 0x3 << 18 ]
set AT91C_BYTE_COUNT      [expr 0x7FF << 20 ]
set AT91C_SHRT_PCKT       [expr 0x1 << 31 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR UDPHS DMA struct
# *****************************************************************************
# -------- UDPHS_DMANXTDSC : (UDPHS_DMA Offset: 0x0) UDPHS DMA Next Descriptor Address Register -------- 
set AT91C_NXT_DSC_ADD     [expr 0xFFFFFFF <<  4 ]
# -------- UDPHS_DMAADDRESS : (UDPHS_DMA Offset: 0x4) UDPHS DMA Channel Address Register -------- 
set AT91C_BUFF_ADD        [expr 0x0 <<  0 ]
# -------- UDPHS_DMACONTROL : (UDPHS_DMA Offset: 0x8) UDPHS DMA Channel Control Register -------- 
set AT91C_CHANN_ENB       [expr 0x1 <<  0 ]
set AT91C_LDNXT_DSC       [expr 0x1 <<  1 ]
set AT91C_END_TR_EN       [expr 0x1 <<  2 ]
set AT91C_END_B_EN        [expr 0x1 <<  3 ]
set AT91C_END_TR_IT       [expr 0x1 <<  4 ]
set AT91C_END_BUFFIT      [expr 0x1 <<  5 ]
set AT91C_DESC_LD_IT      [expr 0x1 <<  6 ]
set AT91C_BURST_LCK       [expr 0x1 <<  7 ]
set AT91C_BUFF_LENGTH     [expr 0xFFFF << 16 ]
# -------- UDPHS_DMASTATUS : (UDPHS_DMA Offset: 0xc) UDPHS DMA Channelx Status Register -------- 
set AT91C_CHANN_ENB       [expr 0x1 <<  0 ]
set AT91C_CHANN_ACT       [expr 0x1 <<  1 ]
set AT91C_END_TR_ST       [expr 0x1 <<  4 ]
set AT91C_END_BF_ST       [expr 0x1 <<  5 ]
set AT91C_DESC_LDST       [expr 0x1 <<  6 ]
set AT91C_BUFF_COUNT      [expr 0xFFFF << 16 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR UDPHS High Speed Device Interface
# *****************************************************************************
# -------- UDPHS_CTRL : (UDPHS Offset: 0x0) UDPHS Control Register -------- 
set AT91C_DEV_ADDR        [expr 0x7F <<  0 ]
set AT91C_FADDR_EN        [expr 0x1 <<  7 ]
set AT91C_EN_UDPHS        [expr 0x1 <<  8 ]
set AT91C_DETACH          [expr 0x1 <<  9 ]
set AT91C_REWAKEUP        [expr 0x1 << 10 ]
set AT91C_PULLD_DIS       [expr 0x1 << 11 ]
# -------- UDPHS_FNUM : (UDPHS Offset: 0x4) UDPHS Frame Number Register -------- 
set AT91C_MICRO_FRAME_NUM [expr 0x7 <<  0 ]
set AT91C_FRAME_NUMBER    [expr 0x7FF <<  3 ]
set AT91C_FNUM_ERR        [expr 0x1 << 31 ]
# -------- UDPHS_IEN : (UDPHS Offset: 0x10) UDPHS Interrupt Enable Register -------- 
set AT91C_DET_SUSPD       [expr 0x1 <<  1 ]
set AT91C_MICRO_SOF       [expr 0x1 <<  2 ]
set AT91C_IEN_SOF         [expr 0x1 <<  3 ]
set AT91C_ENDRESET        [expr 0x1 <<  4 ]
set AT91C_WAKE_UP         [expr 0x1 <<  5 ]
set AT91C_ENDOFRSM        [expr 0x1 <<  6 ]
set AT91C_UPSTR_RES       [expr 0x1 <<  7 ]
set AT91C_EPT_INT_0       [expr 0x1 <<  8 ]
set AT91C_EPT_INT_1       [expr 0x1 <<  9 ]
set AT91C_EPT_INT_2       [expr 0x1 << 10 ]
set AT91C_EPT_INT_3       [expr 0x1 << 11 ]
set AT91C_EPT_INT_4       [expr 0x1 << 12 ]
set AT91C_EPT_INT_5       [expr 0x1 << 13 ]
set AT91C_EPT_INT_6       [expr 0x1 << 14 ]
set AT91C_EPT_INT_7       [expr 0x1 << 15 ]
set AT91C_EPT_INT_8       [expr 0x1 << 16 ]
set AT91C_EPT_INT_9       [expr 0x1 << 17 ]
set AT91C_EPT_INT_10      [expr 0x1 << 18 ]
set AT91C_EPT_INT_11      [expr 0x1 << 19 ]
set AT91C_EPT_INT_12      [expr 0x1 << 20 ]
set AT91C_EPT_INT_13      [expr 0x1 << 21 ]
set AT91C_EPT_INT_14      [expr 0x1 << 22 ]
set AT91C_EPT_INT_15      [expr 0x1 << 23 ]
set AT91C_DMA_INT_1       [expr 0x1 << 25 ]
set AT91C_DMA_INT_2       [expr 0x1 << 26 ]
set AT91C_DMA_INT_3       [expr 0x1 << 27 ]
set AT91C_DMA_INT_4       [expr 0x1 << 28 ]
set AT91C_DMA_INT_5       [expr 0x1 << 29 ]
set AT91C_DMA_INT_6       [expr 0x1 << 30 ]
set AT91C_DMA_INT_7       [expr 0x1 << 31 ]
# -------- UDPHS_INTSTA : (UDPHS Offset: 0x14) UDPHS Interrupt Status Register -------- 
set AT91C_SPEED           [expr 0x1 <<  0 ]
set AT91C_DET_SUSPD       [expr 0x1 <<  1 ]
set AT91C_MICRO_SOF       [expr 0x1 <<  2 ]
set AT91C_IEN_SOF         [expr 0x1 <<  3 ]
set AT91C_ENDRESET        [expr 0x1 <<  4 ]
set AT91C_WAKE_UP         [expr 0x1 <<  5 ]
set AT91C_ENDOFRSM        [expr 0x1 <<  6 ]
set AT91C_UPSTR_RES       [expr 0x1 <<  7 ]
set AT91C_EPT_INT_0       [expr 0x1 <<  8 ]
set AT91C_EPT_INT_1       [expr 0x1 <<  9 ]
set AT91C_EPT_INT_2       [expr 0x1 << 10 ]
set AT91C_EPT_INT_3       [expr 0x1 << 11 ]
set AT91C_EPT_INT_4       [expr 0x1 << 12 ]
set AT91C_EPT_INT_5       [expr 0x1 << 13 ]
set AT91C_EPT_INT_6       [expr 0x1 << 14 ]
set AT91C_EPT_INT_7       [expr 0x1 << 15 ]
set AT91C_EPT_INT_8       [expr 0x1 << 16 ]
set AT91C_EPT_INT_9       [expr 0x1 << 17 ]
set AT91C_EPT_INT_10      [expr 0x1 << 18 ]
set AT91C_EPT_INT_11      [expr 0x1 << 19 ]
set AT91C_EPT_INT_12      [expr 0x1 << 20 ]
set AT91C_EPT_INT_13      [expr 0x1 << 21 ]
set AT91C_EPT_INT_14      [expr 0x1 << 22 ]
set AT91C_EPT_INT_15      [expr 0x1 << 23 ]
set AT91C_DMA_INT_1       [expr 0x1 << 25 ]
set AT91C_DMA_INT_2       [expr 0x1 << 26 ]
set AT91C_DMA_INT_3       [expr 0x1 << 27 ]
set AT91C_DMA_INT_4       [expr 0x1 << 28 ]
set AT91C_DMA_INT_5       [expr 0x1 << 29 ]
set AT91C_DMA_INT_6       [expr 0x1 << 30 ]
set AT91C_DMA_INT_7       [expr 0x1 << 31 ]
# -------- UDPHS_CLRINT : (UDPHS Offset: 0x18) UDPHS Clear Interrupt Register -------- 
set AT91C_DET_SUSPD       [expr 0x1 <<  1 ]
set AT91C_MICRO_SOF       [expr 0x1 <<  2 ]
set AT91C_IEN_SOF         [expr 0x1 <<  3 ]
set AT91C_ENDRESET        [expr 0x1 <<  4 ]
set AT91C_WAKE_UP         [expr 0x1 <<  5 ]
set AT91C_ENDOFRSM        [expr 0x1 <<  6 ]
set AT91C_UPSTR_RES       [expr 0x1 <<  7 ]
# -------- UDPHS_EPTRST : (UDPHS Offset: 0x1c) UDPHS Endpoints Reset Register -------- 
set AT91C_RST_EPT_0       [expr 0x1 <<  0 ]
set AT91C_RST_EPT_1       [expr 0x1 <<  1 ]
set AT91C_RST_EPT_2       [expr 0x1 <<  2 ]
set AT91C_RST_EPT_3       [expr 0x1 <<  3 ]
set AT91C_RST_EPT_4       [expr 0x1 <<  4 ]
set AT91C_RST_EPT_5       [expr 0x1 <<  5 ]
set AT91C_RST_EPT_6       [expr 0x1 <<  6 ]
set AT91C_RST_EPT_7       [expr 0x1 <<  7 ]
set AT91C_RST_EPT_8       [expr 0x1 <<  8 ]
set AT91C_RST_EPT_9       [expr 0x1 <<  9 ]
set AT91C_RST_EPT_10      [expr 0x1 << 10 ]
set AT91C_RST_EPT_11      [expr 0x1 << 11 ]
set AT91C_RST_EPT_12      [expr 0x1 << 12 ]
set AT91C_RST_EPT_13      [expr 0x1 << 13 ]
set AT91C_RST_EPT_14      [expr 0x1 << 14 ]
set AT91C_RST_EPT_15      [expr 0x1 << 15 ]
# -------- UDPHS_TSTSOFCNT : (UDPHS Offset: 0xd0) UDPHS Test SOF Counter Register -------- 
set AT91C_SOFCNTMAX       [expr 0x3 <<  0 ]
set AT91C_SOFCTLOAD       [expr 0x1 <<  7 ]
# -------- UDPHS_TSTCNTA : (UDPHS Offset: 0xd4) UDPHS Test A Counter Register -------- 
set AT91C_CNTAMAX         [expr 0x7FFF <<  0 ]
set AT91C_CNTALOAD        [expr 0x1 << 15 ]
# -------- UDPHS_TSTCNTB : (UDPHS Offset: 0xd8) UDPHS Test B Counter Register -------- 
set AT91C_CNTBMAX         [expr 0x7FFF <<  0 ]
set AT91C_CNTBLOAD        [expr 0x1 << 15 ]
# -------- UDPHS_TSTMODREG : (UDPHS Offset: 0xdc) UDPHS Test Mode Register -------- 
set AT91C_TSTMODE         [expr 0x1F <<  1 ]
# -------- UDPHS_TST : (UDPHS Offset: 0xe0) UDPHS Test Register -------- 
set AT91C_SPEED_CFG       [expr 0x3 <<  0 ]
set 	AT91C_SPEED_CFG_NM                   0x0
set 	AT91C_SPEED_CFG_RS                   0x1
set 	AT91C_SPEED_CFG_HS                   0x2
set 	AT91C_SPEED_CFG_FS                   0x3
set AT91C_TST_J           [expr 0x1 <<  2 ]
set AT91C_TST_K           [expr 0x1 <<  3 ]
set AT91C_TST_PKT         [expr 0x1 <<  4 ]
set AT91C_OPMODE2         [expr 0x1 <<  5 ]
# -------- UDPHS_IPPADDRSIZE : (UDPHS Offset: 0xec) UDPHS PADDRSIZE Register -------- 
set AT91C_IPPADDRSIZE     [expr 0x0 <<  0 ]
# -------- UDPHS_IPNAME1 : (UDPHS Offset: 0xf0) UDPHS Name Register -------- 
set AT91C_IPNAME1         [expr 0x0 <<  0 ]
# -------- UDPHS_IPNAME2 : (UDPHS Offset: 0xf4) UDPHS Name Register -------- 
set AT91C_IPNAME2         [expr 0x0 <<  0 ]
# -------- UDPHS_IPFEATURES : (UDPHS Offset: 0xf8) UDPHS Features Register -------- 
set AT91C_EPT_NBR_MAX     [expr 0xF <<  0 ]
set AT91C_DMA_CHANNEL_NBR [expr 0x7 <<  4 ]
set AT91C_DMA_B_SIZ       [expr 0x1 <<  7 ]
set AT91C_DMA_FIFO_WORD_DEPTH [expr 0xF <<  8 ]
set AT91C_FIFO_MAX_SIZE   [expr 0x7 << 12 ]
set AT91C_BW_DPRAM        [expr 0x1 << 15 ]
set AT91C_DATAB16_8       [expr 0x1 << 16 ]
set AT91C_ISO_EPT_1       [expr 0x1 << 17 ]
set AT91C_ISO_EPT_2       [expr 0x1 << 18 ]
set AT91C_ISO_EPT_3       [expr 0x1 << 19 ]
set AT91C_ISO_EPT_4       [expr 0x1 << 20 ]
set AT91C_ISO_EPT_5       [expr 0x1 << 21 ]
set AT91C_ISO_EPT_6       [expr 0x1 << 22 ]
set AT91C_ISO_EPT_7       [expr 0x1 << 23 ]
set AT91C_ISO_EPT_8       [expr 0x1 << 24 ]
set AT91C_ISO_EPT_9       [expr 0x1 << 25 ]
set AT91C_ISO_EPT_10      [expr 0x1 << 26 ]
set AT91C_ISO_EPT_11      [expr 0x1 << 27 ]
set AT91C_ISO_EPT_12      [expr 0x1 << 28 ]
set AT91C_ISO_EPT_13      [expr 0x1 << 29 ]
set AT91C_ISO_EPT_14      [expr 0x1 << 30 ]
set AT91C_ISO_EPT_15      [expr 0x1 << 31 ]
# -------- UDPHS_IPVERSION : (UDPHS Offset: 0xfc) UDPHS Version Register -------- 
set AT91C_VERSION_NUM     [expr 0xFFFF <<  0 ]
set AT91C_METAL_FIX_NUM   [expr 0x7 << 16 ]

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
#              SOFTWARE API DEFINITION  FOR Advanced  Encryption Standard
# *****************************************************************************
# -------- AES_CR : (AES Offset: 0x0) Control Register -------- 
set AT91C_AES_START       [expr 0x1 <<  0 ]
set AT91C_AES_SWRST       [expr 0x1 <<  8 ]
set AT91C_AES_LOADSEED    [expr 0x1 << 16 ]
# -------- AES_MR : (AES Offset: 0x4) Mode Register -------- 
set AT91C_AES_CIPHER      [expr 0x1 <<  0 ]
set AT91C_AES_PROCDLY     [expr 0xF <<  4 ]
set AT91C_AES_SMOD        [expr 0x3 <<  8 ]
set 	AT91C_AES_SMOD_MANUAL               [expr 0x0 <<  8 ]
set 	AT91C_AES_SMOD_AUTO                 [expr 0x1 <<  8 ]
set 	AT91C_AES_SMOD_PDC                  [expr 0x2 <<  8 ]
set AT91C_AES_OPMOD       [expr 0x7 << 12 ]
set 	AT91C_AES_OPMOD_ECB                  [expr 0x0 << 12 ]
set 	AT91C_AES_OPMOD_CBC                  [expr 0x1 << 12 ]
set 	AT91C_AES_OPMOD_OFB                  [expr 0x2 << 12 ]
set 	AT91C_AES_OPMOD_CFB                  [expr 0x3 << 12 ]
set 	AT91C_AES_OPMOD_CTR                  [expr 0x4 << 12 ]
set AT91C_AES_LOD         [expr 0x1 << 15 ]
set AT91C_AES_CFBS        [expr 0x7 << 16 ]
set 	AT91C_AES_CFBS_128_BIT              [expr 0x0 << 16 ]
set 	AT91C_AES_CFBS_64_BIT               [expr 0x1 << 16 ]
set 	AT91C_AES_CFBS_32_BIT               [expr 0x2 << 16 ]
set 	AT91C_AES_CFBS_16_BIT               [expr 0x3 << 16 ]
set 	AT91C_AES_CFBS_8_BIT                [expr 0x4 << 16 ]
set AT91C_AES_CKEY        [expr 0xF << 20 ]
set AT91C_AES_CTYPE       [expr 0x1F << 24 ]
set 	AT91C_AES_CTYPE_TYPE1_EN             [expr 0x1 << 24 ]
set 	AT91C_AES_CTYPE_TYPE2_EN             [expr 0x2 << 24 ]
set 	AT91C_AES_CTYPE_TYPE3_EN             [expr 0x4 << 24 ]
set 	AT91C_AES_CTYPE_TYPE4_EN             [expr 0x8 << 24 ]
set 	AT91C_AES_CTYPE_TYPE5_EN             [expr 0x10 << 24 ]
# -------- AES_IER : (AES Offset: 0x10) Interrupt Enable Register -------- 
set AT91C_AES_DATRDY      [expr 0x1 <<  0 ]
set AT91C_AES_ENDRX       [expr 0x1 <<  1 ]
set AT91C_AES_ENDTX       [expr 0x1 <<  2 ]
set AT91C_AES_RXBUFF      [expr 0x1 <<  3 ]
set AT91C_AES_TXBUFE      [expr 0x1 <<  4 ]
set AT91C_AES_URAD        [expr 0x1 <<  8 ]
# -------- AES_IDR : (AES Offset: 0x14) Interrupt Disable Register -------- 
set AT91C_AES_DATRDY      [expr 0x1 <<  0 ]
set AT91C_AES_ENDRX       [expr 0x1 <<  1 ]
set AT91C_AES_ENDTX       [expr 0x1 <<  2 ]
set AT91C_AES_RXBUFF      [expr 0x1 <<  3 ]
set AT91C_AES_TXBUFE      [expr 0x1 <<  4 ]
set AT91C_AES_URAD        [expr 0x1 <<  8 ]
# -------- AES_IMR : (AES Offset: 0x18) Interrupt Mask Register -------- 
set AT91C_AES_DATRDY      [expr 0x1 <<  0 ]
set AT91C_AES_ENDRX       [expr 0x1 <<  1 ]
set AT91C_AES_ENDTX       [expr 0x1 <<  2 ]
set AT91C_AES_RXBUFF      [expr 0x1 <<  3 ]
set AT91C_AES_TXBUFE      [expr 0x1 <<  4 ]
set AT91C_AES_URAD        [expr 0x1 <<  8 ]
# -------- AES_ISR : (AES Offset: 0x1c) Interrupt Status Register -------- 
set AT91C_AES_DATRDY      [expr 0x1 <<  0 ]
set AT91C_AES_ENDRX       [expr 0x1 <<  1 ]
set AT91C_AES_ENDTX       [expr 0x1 <<  2 ]
set AT91C_AES_RXBUFF      [expr 0x1 <<  3 ]
set AT91C_AES_TXBUFE      [expr 0x1 <<  4 ]
set AT91C_AES_URAD        [expr 0x1 <<  8 ]
set AT91C_AES_URAT        [expr 0x7 << 12 ]
set 	AT91C_AES_URAT_IN_DAT_WRITE_DATPROC [expr 0x0 << 12 ]
set 	AT91C_AES_URAT_OUT_DAT_READ_DATPROC [expr 0x1 << 12 ]
set 	AT91C_AES_URAT_MODEREG_WRITE_DATPROC [expr 0x2 << 12 ]
set 	AT91C_AES_URAT_OUT_DAT_READ_SUBKEY  [expr 0x3 << 12 ]
set 	AT91C_AES_URAT_MODEREG_WRITE_SUBKEY [expr 0x4 << 12 ]
set 	AT91C_AES_URAT_WO_REG_READ          [expr 0x5 << 12 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Triple Data Encryption Standard
# *****************************************************************************
# -------- TDES_CR : (TDES Offset: 0x0) Control Register -------- 
set AT91C_TDES_START      [expr 0x1 <<  0 ]
set AT91C_TDES_SWRST      [expr 0x1 <<  8 ]
# -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- 
set AT91C_TDES_CIPHER     [expr 0x1 <<  0 ]
set AT91C_TDES_TDESMOD    [expr 0x1 <<  1 ]
set AT91C_TDES_KEYMOD     [expr 0x1 <<  4 ]
set AT91C_TDES_SMOD       [expr 0x3 <<  8 ]
set 	AT91C_TDES_SMOD_MANUAL               [expr 0x0 <<  8 ]
set 	AT91C_TDES_SMOD_AUTO                 [expr 0x1 <<  8 ]
set 	AT91C_TDES_SMOD_PDC                  [expr 0x2 <<  8 ]
set AT91C_TDES_OPMOD      [expr 0x3 << 12 ]
set 	AT91C_TDES_OPMOD_ECB                  [expr 0x0 << 12 ]
set 	AT91C_TDES_OPMOD_CBC                  [expr 0x1 << 12 ]
set 	AT91C_TDES_OPMOD_OFB                  [expr 0x2 << 12 ]
set 	AT91C_TDES_OPMOD_CFB                  [expr 0x3 << 12 ]
set AT91C_TDES_LOD        [expr 0x1 << 15 ]
set AT91C_TDES_CFBS       [expr 0x3 << 16 ]
set 	AT91C_TDES_CFBS_64_BIT               [expr 0x0 << 16 ]
set 	AT91C_TDES_CFBS_32_BIT               [expr 0x1 << 16 ]
set 	AT91C_TDES_CFBS_16_BIT               [expr 0x2 << 16 ]
set 	AT91C_TDES_CFBS_8_BIT                [expr 0x3 << 16 ]
# -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- 
set AT91C_TDES_DATRDY     [expr 0x1 <<  0 ]
set AT91C_TDES_ENDRX      [expr 0x1 <<  1 ]
set AT91C_TDES_ENDTX      [expr 0x1 <<  2 ]
set AT91C_TDES_RXBUFF     [expr 0x1 <<  3 ]
set AT91C_TDES_TXBUFE     [expr 0x1 <<  4 ]
set AT91C_TDES_URAD       [expr 0x1 <<  8 ]
# -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- 
set AT91C_TDES_DATRDY     [expr 0x1 <<  0 ]
set AT91C_TDES_ENDRX      [expr 0x1 <<  1 ]
set AT91C_TDES_ENDTX      [expr 0x1 <<  2 ]
set AT91C_TDES_RXBUFF     [expr 0x1 <<  3 ]
set AT91C_TDES_TXBUFE     [expr 0x1 <<  4 ]
set AT91C_TDES_URAD       [expr 0x1 <<  8 ]
# -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- 
set AT91C_TDES_DATRDY     [expr 0x1 <<  0 ]
set AT91C_TDES_ENDRX      [expr 0x1 <<  1 ]
set AT91C_TDES_ENDTX      [expr 0x1 <<  2 ]
set AT91C_TDES_RXBUFF     [expr 0x1 <<  3 ]
set AT91C_TDES_TXBUFE     [expr 0x1 <<  4 ]
set AT91C_TDES_URAD       [expr 0x1 <<  8 ]
# -------- TDES_ISR : (TDES Offset: 0x1c) Interrupt Status Register -------- 
set AT91C_TDES_DATRDY     [expr 0x1 <<  0 ]
set AT91C_TDES_ENDRX      [expr 0x1 <<  1 ]
set AT91C_TDES_ENDTX      [expr 0x1 <<  2 ]
set AT91C_TDES_RXBUFF     [expr 0x1 <<  3 ]
set AT91C_TDES_TXBUFE     [expr 0x1 <<  4 ]
set AT91C_TDES_URAD       [expr 0x1 <<  8 ]
set AT91C_TDES_URAT       [expr 0x3 << 12 ]
set 	AT91C_TDES_URAT_IN_DAT_WRITE_DATPROC [expr 0x0 << 12 ]
set 	AT91C_TDES_URAT_OUT_DAT_READ_DATPROC [expr 0x1 << 12 ]
set 	AT91C_TDES_URAT_MODEREG_WRITE_DATPROC [expr 0x2 << 12 ]
set 	AT91C_TDES_URAT_WO_REG_READ          [expr 0x3 << 12 ]

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
set AT91C_ADC_CH4         [expr 0x1 <<  4 ]
set AT91C_ADC_CH5         [expr 0x1 <<  5 ]
set AT91C_ADC_CH6         [expr 0x1 <<  6 ]
set AT91C_ADC_CH7         [expr 0x1 <<  7 ]
# -------- 	ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- 
set AT91C_ADC_CH0         [expr 0x1 <<  0 ]
set AT91C_ADC_CH1         [expr 0x1 <<  1 ]
set AT91C_ADC_CH2         [expr 0x1 <<  2 ]
set AT91C_ADC_CH3         [expr 0x1 <<  3 ]
set AT91C_ADC_CH4         [expr 0x1 <<  4 ]
set AT91C_ADC_CH5         [expr 0x1 <<  5 ]
set AT91C_ADC_CH6         [expr 0x1 <<  6 ]
set AT91C_ADC_CH7         [expr 0x1 <<  7 ]
# -------- 	ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- 
set AT91C_ADC_CH0         [expr 0x1 <<  0 ]
set AT91C_ADC_CH1         [expr 0x1 <<  1 ]
set AT91C_ADC_CH2         [expr 0x1 <<  2 ]
set AT91C_ADC_CH3         [expr 0x1 <<  3 ]
set AT91C_ADC_CH4         [expr 0x1 <<  4 ]
set AT91C_ADC_CH5         [expr 0x1 <<  5 ]
set AT91C_ADC_CH6         [expr 0x1 <<  6 ]
set AT91C_ADC_CH7         [expr 0x1 <<  7 ]
# -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_EOC4        [expr 0x1 <<  4 ]
set AT91C_ADC_EOC5        [expr 0x1 <<  5 ]
set AT91C_ADC_EOC6        [expr 0x1 <<  6 ]
set AT91C_ADC_EOC7        [expr 0x1 <<  7 ]
set AT91C_ADC_OVRE0       [expr 0x1 <<  8 ]
set AT91C_ADC_OVRE1       [expr 0x1 <<  9 ]
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_OVRE4       [expr 0x1 << 12 ]
set AT91C_ADC_OVRE5       [expr 0x1 << 13 ]
set AT91C_ADC_OVRE6       [expr 0x1 << 14 ]
set AT91C_ADC_OVRE7       [expr 0x1 << 15 ]
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
set AT91C_ADC_EOC4        [expr 0x1 <<  4 ]
set AT91C_ADC_EOC5        [expr 0x1 <<  5 ]
set AT91C_ADC_EOC6        [expr 0x1 <<  6 ]
set AT91C_ADC_EOC7        [expr 0x1 <<  7 ]
set AT91C_ADC_OVRE0       [expr 0x1 <<  8 ]
set AT91C_ADC_OVRE1       [expr 0x1 <<  9 ]
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_OVRE4       [expr 0x1 << 12 ]
set AT91C_ADC_OVRE5       [expr 0x1 << 13 ]
set AT91C_ADC_OVRE6       [expr 0x1 << 14 ]
set AT91C_ADC_OVRE7       [expr 0x1 << 15 ]
set AT91C_ADC_DRDY        [expr 0x1 << 16 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 17 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 18 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 19 ]
# -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_EOC4        [expr 0x1 <<  4 ]
set AT91C_ADC_EOC5        [expr 0x1 <<  5 ]
set AT91C_ADC_EOC6        [expr 0x1 <<  6 ]
set AT91C_ADC_EOC7        [expr 0x1 <<  7 ]
set AT91C_ADC_OVRE0       [expr 0x1 <<  8 ]
set AT91C_ADC_OVRE1       [expr 0x1 <<  9 ]
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_OVRE4       [expr 0x1 << 12 ]
set AT91C_ADC_OVRE5       [expr 0x1 << 13 ]
set AT91C_ADC_OVRE6       [expr 0x1 << 14 ]
set AT91C_ADC_OVRE7       [expr 0x1 << 15 ]
set AT91C_ADC_DRDY        [expr 0x1 << 16 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 17 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 18 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 19 ]
# -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_EOC4        [expr 0x1 <<  4 ]
set AT91C_ADC_EOC5        [expr 0x1 <<  5 ]
set AT91C_ADC_EOC6        [expr 0x1 <<  6 ]
set AT91C_ADC_EOC7        [expr 0x1 <<  7 ]
set AT91C_ADC_OVRE0       [expr 0x1 <<  8 ]
set AT91C_ADC_OVRE1       [expr 0x1 <<  9 ]
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_OVRE4       [expr 0x1 << 12 ]
set AT91C_ADC_OVRE5       [expr 0x1 << 13 ]
set AT91C_ADC_OVRE6       [expr 0x1 << 14 ]
set AT91C_ADC_OVRE7       [expr 0x1 << 15 ]
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
# -------- ADC_CDR4 : (ADC Offset: 0x40) ADC Channel Data Register 4 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR5 : (ADC Offset: 0x44) ADC Channel Data Register 5 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR6 : (ADC Offset: 0x48) ADC Channel Data Register 6 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR7 : (ADC Offset: 0x4c) ADC Channel Data Register 7 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]

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

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR System Peripherals
# *****************************************************************************
# -------- GPBR : (SYS Offset: 0x1b50) GPBR General Purpose Register -------- 
set AT91C_GPBR_GPRV       [expr 0x0 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR USB Host Interface
# *****************************************************************************

# *****************************************************************************
#               REGISTER ADDRESS DEFINITION FOR AT91CAP9
# *****************************************************************************
# ========== Register definition for HECC peripheral ========== 
set AT91C_HECC_NPR  0xFFFFE210
set AT91C_HECC_SR   0xFFFFE208
set AT91C_HECC_CR   0xFFFFE200
set AT91C_HECC_VR   0xFFFFE2FC
set AT91C_HECC_PR   0xFFFFE20C
set AT91C_HECC_MR   0xFFFFE204
# ========== Register definition for BCRAMC peripheral ========== 
set AT91C_BCRAMC_MDR 0xFFFFE410
set AT91C_BCRAMC_HSR 0xFFFFE408
set AT91C_BCRAMC_CR 0xFFFFE400
set AT91C_BCRAMC_VR 0xFFFFE4FC
set AT91C_BCRAMC_IPNR2 0xFFFFE4F4
set AT91C_BCRAMC_PADDSR 0xFFFFE4EC
set AT91C_BCRAMC_LPR 0xFFFFE40C
set AT91C_BCRAMC_TPR 0xFFFFE404
set AT91C_BCRAMC_IPFR 0xFFFFE4F8
set AT91C_BCRAMC_IPNR1 0xFFFFE4F0
# ========== Register definition for SDRAMC peripheral ========== 
set AT91C_SDRAMC_MDR 0xFFFFE624
set AT91C_SDRAMC_IMR 0xFFFFE61C
set AT91C_SDRAMC_IER 0xFFFFE614
set AT91C_SDRAMC_HSR 0xFFFFE60C
set AT91C_SDRAMC_TR 0xFFFFE604
set AT91C_SDRAMC_ISR 0xFFFFE620
set AT91C_SDRAMC_IDR 0xFFFFE618
set AT91C_SDRAMC_LPR 0xFFFFE610
set AT91C_SDRAMC_CR 0xFFFFE608
set AT91C_SDRAMC_MR 0xFFFFE600
# ========== Register definition for SDDRC peripheral ========== 
set AT91C_SDDRC_HS  0xFFFFE614
set AT91C_SDDRC_T0PR 0xFFFFE60C
set AT91C_SDDRC_RTR 0xFFFFE604
set AT91C_SDDRC_LPR 0xFFFFE618
set AT91C_SDDRC_T1PR 0xFFFFE610
set AT91C_SDDRC_CR  0xFFFFE608
set AT91C_SDDRC_MDR 0xFFFFE61C
set AT91C_SDDRC_MR  0xFFFFE600
set AT91C_SDDRC_VERSION 0xFFFFE6FC
# ========== Register definition for SMC peripheral ========== 
set AT91C_SMC_PULSE4 0xFFFFE844
set AT91C_SMC_CTRL3 0xFFFFE83C
set AT91C_SMC_PULSE3 0xFFFFE834
set AT91C_SMC_CYCLE5 0xFFFFE858
set AT91C_SMC_SETUP5 0xFFFFE850
set AT91C_SMC_CYCLE4 0xFFFFE848
set AT91C_SMC_SETUP4 0xFFFFE840
set AT91C_SMC_CYCLE3 0xFFFFE838
set AT91C_SMC_CYCLE0 0xFFFFE808
set AT91C_SMC_SETUP0 0xFFFFE800
set AT91C_SMC_CTRL6 0xFFFFE86C
set AT91C_SMC_PULSE6 0xFFFFE864
set AT91C_SMC_CTRL5 0xFFFFE85C
set AT91C_SMC_PULSE5 0xFFFFE854
set AT91C_SMC_CTRL4 0xFFFFE84C
set AT91C_SMC_PULSE0 0xFFFFE804
set AT91C_SMC_CTRL0 0xFFFFE80C
set AT91C_SMC_PULSE1 0xFFFFE814
set AT91C_SMC_CTRL1 0xFFFFE81C
set AT91C_SMC_CYCLE7 0xFFFFE878
set AT91C_SMC_SETUP7 0xFFFFE870
set AT91C_SMC_CYCLE6 0xFFFFE868
set AT91C_SMC_SETUP6 0xFFFFE860
set AT91C_SMC_SETUP1 0xFFFFE810
set AT91C_SMC_CYCLE1 0xFFFFE818
set AT91C_SMC_SETUP2 0xFFFFE820
set AT91C_SMC_CYCLE2 0xFFFFE828
set AT91C_SMC_CTRL7 0xFFFFE87C
set AT91C_SMC_PULSE7 0xFFFFE874
set AT91C_SMC_PULSE2 0xFFFFE824
set AT91C_SMC_CTRL2 0xFFFFE82C
set AT91C_SMC_SETUP3 0xFFFFE830
# ========== Register definition for MATRIX_PRS peripheral ========== 
set AT91C_MATRIX_PRS_PRBS 0xFFFFEA84
set AT91C_MATRIX_PRS_PRAS 0xFFFFEA80
# ========== Register definition for MATRIX peripheral ========== 
set AT91C_MATRIX_MCFG 0xFFFFEA00
set AT91C_MATRIX_MRCR 0xFFFFEB00
set AT91C_MATRIX_SCFG 0xFFFFEA40
# ========== Register definition for CCFG peripheral ========== 
set AT91C_CCFG_BRIDGE 0xFFFFEB34
set AT91C_CCFG_MPBS2 0xFFFFEB2C
set AT91C_CCFG_MPBS1 0xFFFFEB1C
set AT91C_CCFG_MPBS0 0xFFFFEB14
set AT91C_CCFG_MATRIXVERSION 0xFFFFEBFC
set AT91C_CCFG_MPBS3 0xFFFFEB30
set AT91C_CCFG_EBICSA 0xFFFFEB20
set AT91C_CCFG_UDPHS 0xFFFFEB18
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
# ========== Register definition for CKGR peripheral ========== 
set AT91C_CKGR_PLLBR 0xFFFFFC2C
set AT91C_CKGR_MCFR 0xFFFFFC24
set AT91C_CKGR_UCKR 0xFFFFFC1C
set AT91C_CKGR_PLLAR 0xFFFFFC28
set AT91C_CKGR_MOR  0xFFFFFC20
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
set AT91C_UDPHS_EPT_0_EPTCTLENB 0xFFF78104
set AT91C_UDPHS_EPT_0_EPTSTA 0xFFF7811C
set AT91C_UDPHS_EPT_0_EPTSETSTA 0xFFF78114
set AT91C_UDPHS_EPT_0_EPTCTL 0xFFF7810C
set AT91C_UDPHS_EPT_0_EPTCLRSTA 0xFFF78118
set AT91C_UDPHS_EPT_0_EPTCTLDIS 0xFFF78108
set AT91C_UDPHS_EPT_0_EPTCFG 0xFFF78100
# ========== Register definition for UDPHS_EPT_1 peripheral ========== 
set AT91C_UDPHS_EPT_1_EPTSTA 0xFFF7813C
set AT91C_UDPHS_EPT_1_EPTSETSTA 0xFFF78134
set AT91C_UDPHS_EPT_1_EPTCTL 0xFFF7812C
set AT91C_UDPHS_EPT_1_EPTCTLENB 0xFFF78124
set AT91C_UDPHS_EPT_1_EPTCLRSTA 0xFFF78138
set AT91C_UDPHS_EPT_1_EPTCTLDIS 0xFFF78128
set AT91C_UDPHS_EPT_1_EPTCFG 0xFFF78120
# ========== Register definition for UDPHS_EPT_2 peripheral ========== 
set AT91C_UDPHS_EPT_2_EPTSTA 0xFFF7815C
set AT91C_UDPHS_EPT_2_EPTSETSTA 0xFFF78154
set AT91C_UDPHS_EPT_2_EPTCTL 0xFFF7814C
set AT91C_UDPHS_EPT_2_EPTCTLENB 0xFFF78144
set AT91C_UDPHS_EPT_2_EPTCLRSTA 0xFFF78158
set AT91C_UDPHS_EPT_2_EPTCTLDIS 0xFFF78148
set AT91C_UDPHS_EPT_2_EPTCFG 0xFFF78140
# ========== Register definition for UDPHS_EPT_3 peripheral ========== 
set AT91C_UDPHS_EPT_3_EPTSTA 0xFFF7817C
set AT91C_UDPHS_EPT_3_EPTSETSTA 0xFFF78174
set AT91C_UDPHS_EPT_3_EPTCTL 0xFFF7816C
set AT91C_UDPHS_EPT_3_EPTCTLENB 0xFFF78164
set AT91C_UDPHS_EPT_3_EPTCTLDIS 0xFFF78168
set AT91C_UDPHS_EPT_3_EPTCLRSTA 0xFFF78178
set AT91C_UDPHS_EPT_3_EPTCFG 0xFFF78160
# ========== Register definition for UDPHS_EPT_4 peripheral ========== 
set AT91C_UDPHS_EPT_4_EPTSTA 0xFFF7819C
set AT91C_UDPHS_EPT_4_EPTSETSTA 0xFFF78194
set AT91C_UDPHS_EPT_4_EPTCTL 0xFFF7818C
set AT91C_UDPHS_EPT_4_EPTCTLENB 0xFFF78184
set AT91C_UDPHS_EPT_4_EPTCLRSTA 0xFFF78198
set AT91C_UDPHS_EPT_4_EPTCTLDIS 0xFFF78188
set AT91C_UDPHS_EPT_4_EPTCFG 0xFFF78180
# ========== Register definition for UDPHS_EPT_5 peripheral ========== 
set AT91C_UDPHS_EPT_5_EPTSTA 0xFFF781BC
set AT91C_UDPHS_EPT_5_EPTSETSTA 0xFFF781B4
set AT91C_UDPHS_EPT_5_EPTCTL 0xFFF781AC
set AT91C_UDPHS_EPT_5_EPTCTLENB 0xFFF781A4
set AT91C_UDPHS_EPT_5_EPTCLRSTA 0xFFF781B8
set AT91C_UDPHS_EPT_5_EPTCTLDIS 0xFFF781A8
set AT91C_UDPHS_EPT_5_EPTCFG 0xFFF781A0
# ========== Register definition for UDPHS_EPT_6 peripheral ========== 
set AT91C_UDPHS_EPT_6_EPTSTA 0xFFF781DC
set AT91C_UDPHS_EPT_6_EPTSETSTA 0xFFF781D4
set AT91C_UDPHS_EPT_6_EPTCTLENB 0xFFF781C4
set AT91C_UDPHS_EPT_6_EPTCLRSTA 0xFFF781D8
set AT91C_UDPHS_EPT_6_EPTCTLDIS 0xFFF781C8
set AT91C_UDPHS_EPT_6_EPTCFG 0xFFF781C0
set AT91C_UDPHS_EPT_6_EPTCTL 0xFFF781CC
# ========== Register definition for UDPHS_EPT_7 peripheral ========== 
set AT91C_UDPHS_EPT_7_EPTSTA 0xFFF781FC
set AT91C_UDPHS_EPT_7_EPTSETSTA 0xFFF781F4
set AT91C_UDPHS_EPT_7_EPTCTL 0xFFF781EC
set AT91C_UDPHS_EPT_7_EPTCTLENB 0xFFF781E4
set AT91C_UDPHS_EPT_7_EPTCLRSTA 0xFFF781F8
set AT91C_UDPHS_EPT_7_EPTCTLDIS 0xFFF781E8
set AT91C_UDPHS_EPT_7_EPTCFG 0xFFF781E0
# ========== Register definition for UDPHS_EPT_8 peripheral ========== 
set AT91C_UDPHS_EPT_8_EPTSTA 0xFFF7821C
set AT91C_UDPHS_EPT_8_EPTSETSTA 0xFFF78214
set AT91C_UDPHS_EPT_8_EPTCTL 0xFFF7820C
set AT91C_UDPHS_EPT_8_EPTCTLENB 0xFFF78204
set AT91C_UDPHS_EPT_8_EPTCLRSTA 0xFFF78218
set AT91C_UDPHS_EPT_8_EPTCTLDIS 0xFFF78208
set AT91C_UDPHS_EPT_8_EPTCFG 0xFFF78200
# ========== Register definition for UDPHS_EPT_9 peripheral ========== 
set AT91C_UDPHS_EPT_9_EPTCTL 0xFFF7822C
set AT91C_UDPHS_EPT_9_EPTCTLENB 0xFFF78224
set AT91C_UDPHS_EPT_9_EPTCLRSTA 0xFFF78238
set AT91C_UDPHS_EPT_9_EPTCTLDIS 0xFFF78228
set AT91C_UDPHS_EPT_9_EPTCFG 0xFFF78220
set AT91C_UDPHS_EPT_9_EPTSTA 0xFFF7823C
set AT91C_UDPHS_EPT_9_EPTSETSTA 0xFFF78234
# ========== Register definition for UDPHS_EPT_10 peripheral ========== 
set AT91C_UDPHS_EPT_10_EPTCLRSTA 0xFFF78258
set AT91C_UDPHS_EPT_10_EPTCTLDIS 0xFFF78248
set AT91C_UDPHS_EPT_10_EPTCFG 0xFFF78240
set AT91C_UDPHS_EPT_10_EPTSTA 0xFFF7825C
set AT91C_UDPHS_EPT_10_EPTSETSTA 0xFFF78254
set AT91C_UDPHS_EPT_10_EPTCTL 0xFFF7824C
set AT91C_UDPHS_EPT_10_EPTCTLENB 0xFFF78244
# ========== Register definition for UDPHS_EPT_11 peripheral ========== 
set AT91C_UDPHS_EPT_11_EPTCLRSTA 0xFFF78278
set AT91C_UDPHS_EPT_11_EPTCTLDIS 0xFFF78268
set AT91C_UDPHS_EPT_11_EPTCFG 0xFFF78260
set AT91C_UDPHS_EPT_11_EPTSTA 0xFFF7827C
set AT91C_UDPHS_EPT_11_EPTSETSTA 0xFFF78274
set AT91C_UDPHS_EPT_11_EPTCTL 0xFFF7826C
set AT91C_UDPHS_EPT_11_EPTCTLENB 0xFFF78264
# ========== Register definition for UDPHS_EPT_12 peripheral ========== 
set AT91C_UDPHS_EPT_12_EPTCLRSTA 0xFFF78298
set AT91C_UDPHS_EPT_12_EPTCTLDIS 0xFFF78288
set AT91C_UDPHS_EPT_12_EPTCFG 0xFFF78280
set AT91C_UDPHS_EPT_12_EPTSTA 0xFFF7829C
set AT91C_UDPHS_EPT_12_EPTSETSTA 0xFFF78294
set AT91C_UDPHS_EPT_12_EPTCTL 0xFFF7828C
set AT91C_UDPHS_EPT_12_EPTCTLENB 0xFFF78284
# ========== Register definition for UDPHS_EPT_13 peripheral ========== 
set AT91C_UDPHS_EPT_13_EPTCLRSTA 0xFFF782B8
set AT91C_UDPHS_EPT_13_EPTCTLDIS 0xFFF782A8
set AT91C_UDPHS_EPT_13_EPTCFG 0xFFF782A0
set AT91C_UDPHS_EPT_13_EPTSTA 0xFFF782BC
set AT91C_UDPHS_EPT_13_EPTSETSTA 0xFFF782B4
set AT91C_UDPHS_EPT_13_EPTCTL 0xFFF782AC
set AT91C_UDPHS_EPT_13_EPTCTLENB 0xFFF782A4
# ========== Register definition for UDPHS_EPT_14 peripheral ========== 
set AT91C_UDPHS_EPT_14_EPTCLRSTA 0xFFF782D8
set AT91C_UDPHS_EPT_14_EPTCTLDIS 0xFFF782C8
set AT91C_UDPHS_EPT_14_EPTCFG 0xFFF782C0
set AT91C_UDPHS_EPT_14_EPTSTA 0xFFF782DC
set AT91C_UDPHS_EPT_14_EPTSETSTA 0xFFF782D4
set AT91C_UDPHS_EPT_14_EPTCTL 0xFFF782CC
set AT91C_UDPHS_EPT_14_EPTCTLENB 0xFFF782C4
# ========== Register definition for UDPHS_EPT_15 peripheral ========== 
set AT91C_UDPHS_EPT_15_EPTSTA 0xFFF782FC
set AT91C_UDPHS_EPT_15_EPTCTLDIS 0xFFF782E8
set AT91C_UDPHS_EPT_15_EPTCFG 0xFFF782E0
set AT91C_UDPHS_EPT_15_EPTCLRSTA 0xFFF782F8
set AT91C_UDPHS_EPT_15_EPTSETSTA 0xFFF782F4
set AT91C_UDPHS_EPT_15_EPTCTL 0xFFF782EC
set AT91C_UDPHS_EPT_15_EPTCTLENB 0xFFF782E4
# ========== Register definition for UDPHS_DMA_1 peripheral ========== 
set AT91C_UDPHS_DMA_1_DMASTATUS 0xFFF7831C
set AT91C_UDPHS_DMA_1_DMAADDRESS 0xFFF78314
set AT91C_UDPHS_DMA_1_DMACONTROL 0xFFF78318
set AT91C_UDPHS_DMA_1_DMANXTDSC 0xFFF78310
# ========== Register definition for UDPHS_DMA_2 peripheral ========== 
set AT91C_UDPHS_DMA_2_DMASTATUS 0xFFF7832C
set AT91C_UDPHS_DMA_2_DMAADDRESS 0xFFF78324
set AT91C_UDPHS_DMA_2_DMANXTDSC 0xFFF78320
set AT91C_UDPHS_DMA_2_DMACONTROL 0xFFF78328
# ========== Register definition for UDPHS_DMA_3 peripheral ========== 
set AT91C_UDPHS_DMA_3_DMAADDRESS 0xFFF78334
set AT91C_UDPHS_DMA_3_DMASTATUS 0xFFF7833C
set AT91C_UDPHS_DMA_3_DMACONTROL 0xFFF78338
set AT91C_UDPHS_DMA_3_DMANXTDSC 0xFFF78330
# ========== Register definition for UDPHS_DMA_4 peripheral ========== 
set AT91C_UDPHS_DMA_4_DMASTATUS 0xFFF7834C
set AT91C_UDPHS_DMA_4_DMAADDRESS 0xFFF78344
set AT91C_UDPHS_DMA_4_DMACONTROL 0xFFF78348
set AT91C_UDPHS_DMA_4_DMANXTDSC 0xFFF78340
# ========== Register definition for UDPHS_DMA_5 peripheral ========== 
set AT91C_UDPHS_DMA_5_DMASTATUS 0xFFF7835C
set AT91C_UDPHS_DMA_5_DMAADDRESS 0xFFF78354
set AT91C_UDPHS_DMA_5_DMACONTROL 0xFFF78358
set AT91C_UDPHS_DMA_5_DMANXTDSC 0xFFF78350
# ========== Register definition for UDPHS_DMA_6 peripheral ========== 
set AT91C_UDPHS_DMA_6_DMASTATUS 0xFFF7836C
set AT91C_UDPHS_DMA_6_DMAADDRESS 0xFFF78364
set AT91C_UDPHS_DMA_6_DMACONTROL 0xFFF78368
set AT91C_UDPHS_DMA_6_DMANXTDSC 0xFFF78360
# ========== Register definition for UDPHS_DMA_7 peripheral ========== 
set AT91C_UDPHS_DMA_7_DMASTATUS 0xFFF7837C
set AT91C_UDPHS_DMA_7_DMAADDRESS 0xFFF78374
set AT91C_UDPHS_DMA_7_DMANXTDSC 0xFFF78370
set AT91C_UDPHS_DMA_7_DMACONTROL 0xFFF78378
# ========== Register definition for UDPHS peripheral ========== 
set AT91C_UDPHS_CLRINT 0xFFF78018
set AT91C_UDPHS_IEN 0xFFF78010
set AT91C_UDPHS_TSTMODREG 0xFFF780DC
set AT91C_UDPHS_TSTCNTA 0xFFF780D4
set AT91C_UDPHS_EPTRST 0xFFF7801C
set AT91C_UDPHS_IPNAME1 0xFFF780F0
set AT91C_UDPHS_TST 0xFFF780E0
set AT91C_UDPHS_TSTCNTB 0xFFF780D8
set AT91C_UDPHS_TSTSOFCNT 0xFFF780D0
set AT91C_UDPHS_CTRL 0xFFF78000
set AT91C_UDPHS_IPVERSION 0xFFF780FC
set AT91C_UDPHS_IPNAME2 0xFFF780F4
set AT91C_UDPHS_IPPADDRSIZE 0xFFF780EC
set AT91C_UDPHS_FNUM 0xFFF78004
set AT91C_UDPHS_INTSTA 0xFFF78014
set AT91C_UDPHS_IPFEATURES 0xFFF780F8
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
# ========== Register definition for PDC_TWI peripheral ========== 
set AT91C_TWI_PTCR  0xFFF88120
set AT91C_TWI_TNPR  0xFFF88118
set AT91C_TWI_RNPR  0xFFF88110
set AT91C_TWI_TPR   0xFFF88108
set AT91C_TWI_RPR   0xFFF88100
set AT91C_TWI_PTSR  0xFFF88124
set AT91C_TWI_TNCR  0xFFF8811C
set AT91C_TWI_RNCR  0xFFF88114
set AT91C_TWI_TCR   0xFFF8810C
set AT91C_TWI_RCR   0xFFF88104
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
set AT91C_TWI_SMR   0xFFF88008
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
# ========== Register definition for PDC_AES peripheral ========== 
set AT91C_AES_TNCR  0xFFFB011C
set AT91C_AES_RNCR  0xFFFB0114
set AT91C_AES_TCR   0xFFFB010C
set AT91C_AES_RCR   0xFFFB0104
set AT91C_AES_PTCR  0xFFFB0120
set AT91C_AES_TNPR  0xFFFB0118
set AT91C_AES_RNPR  0xFFFB0110
set AT91C_AES_PTSR  0xFFFB0124
set AT91C_AES_RPR   0xFFFB0100
set AT91C_AES_TPR   0xFFFB0108
# ========== Register definition for AES peripheral ========== 
set AT91C_AES_VR    0xFFFB00FC
set AT91C_AES_ISR   0xFFFB001C
set AT91C_AES_IDR   0xFFFB0014
set AT91C_AES_IDATAxR 0xFFFB0040
set AT91C_AES_KEYWxR 0xFFFB0020
set AT91C_AES_MR    0xFFFB0004
set AT91C_AES_IVxR  0xFFFB0060
set AT91C_AES_CR    0xFFFB0000
set AT91C_AES_IER   0xFFFB0010
set AT91C_AES_IMR   0xFFFB0018
set AT91C_AES_ODATAxR 0xFFFB0050
# ========== Register definition for PDC_TDES peripheral ========== 
set AT91C_TDES_TNCR 0xFFFB011C
set AT91C_TDES_RNCR 0xFFFB0114
set AT91C_TDES_TCR  0xFFFB010C
set AT91C_TDES_RCR  0xFFFB0104
set AT91C_TDES_PTCR 0xFFFB0120
set AT91C_TDES_TNPR 0xFFFB0118
set AT91C_TDES_RNPR 0xFFFB0110
set AT91C_TDES_PTSR 0xFFFB0124
set AT91C_TDES_RPR  0xFFFB0100
set AT91C_TDES_TPR  0xFFFB0108
# ========== Register definition for TDES peripheral ========== 
set AT91C_TDES_VR   0xFFFB00FC
set AT91C_TDES_ISR  0xFFFB001C
set AT91C_TDES_IDR  0xFFFB0014
set AT91C_TDES_IDATAxR 0xFFFB0040
set AT91C_TDES_KEY3WxR 0xFFFB0030
set AT91C_TDES_KEY2WxR 0xFFFB0028
set AT91C_TDES_KEY1WxR 0xFFFB0020
set AT91C_TDES_MR   0xFFFB0004
set AT91C_TDES_IVxR 0xFFFB0060
set AT91C_TDES_CR   0xFFFB0000
set AT91C_TDES_IER  0xFFFB0010
set AT91C_TDES_IMR  0xFFFB0018
set AT91C_TDES_ODATAxR 0xFFFB0050
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
# ========== Register definition for PDC_ADC peripheral ========== 
set AT91C_ADC_PTCR  0xFFFC0120
set AT91C_ADC_TNPR  0xFFFC0118
set AT91C_ADC_RNPR  0xFFFC0110
set AT91C_ADC_TPR   0xFFFC0108
set AT91C_ADC_RPR   0xFFFC0100
set AT91C_ADC_PTSR  0xFFFC0124
set AT91C_ADC_TNCR  0xFFFC011C
set AT91C_ADC_RNCR  0xFFFC0114
set AT91C_ADC_TCR   0xFFFC010C
set AT91C_ADC_RCR   0xFFFC0104
# ========== Register definition for ADC peripheral ========== 
set AT91C_ADC_CDR0  0xFFFC0030
set AT91C_ADC_CDR5  0xFFFC0044
set AT91C_ADC_CDR3  0xFFFC003C
set AT91C_ADC_CDR1  0xFFFC0034
set AT91C_ADC_CDR6  0xFFFC0048
set AT91C_ADC_CDR4  0xFFFC0040
set AT91C_ADC_CDR2  0xFFFC0038
set AT91C_ADC_CR    0xFFFC0000
set AT91C_ADC_CDR7  0xFFFC004C
set AT91C_ADC_MR    0xFFFC0004
set AT91C_ADC_CHDR  0xFFFC0014
set AT91C_ADC_SR    0xFFFC001C
set AT91C_ADC_CHER  0xFFFC0010
set AT91C_ADC_CHSR  0xFFFC0018
set AT91C_ADC_LCDR  0xFFFC0020
set AT91C_ADC_IDR   0xFFFC0028
set AT91C_ADC_IER   0xFFFC0024
set AT91C_ADC_IMR   0xFFFC002C
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
# ========== Register definition for HDMA_CH_0 peripheral ========== 
set AT91C_HDMA_CH_0_DPIP 0xFFFFEC58
set AT91C_HDMA_CH_0_CFG 0xFFFFEC50
set AT91C_HDMA_CH_0_CTRLA 0xFFFFEC48
set AT91C_HDMA_CH_0_DADDR 0xFFFFEC40
set AT91C_HDMA_CH_0_SPIP 0xFFFFEC54
set AT91C_HDMA_CH_0_CTRLB 0xFFFFEC4C
set AT91C_HDMA_CH_0_DSCR 0xFFFFEC44
set AT91C_HDMA_CH_0_SADDR 0xFFFFEC3C
# ========== Register definition for HDMA_CH_1 peripheral ========== 
set AT91C_HDMA_CH_1_DADDR 0xFFFFEC68
set AT91C_HDMA_CH_1_SPIP 0xFFFFEC7C
set AT91C_HDMA_CH_1_CTRLB 0xFFFFEC74
set AT91C_HDMA_CH_1_DSCR 0xFFFFEC6C
set AT91C_HDMA_CH_1_SADDR 0xFFFFEC64
set AT91C_HDMA_CH_1_DPIP 0xFFFFEC80
set AT91C_HDMA_CH_1_CTRLA 0xFFFFEC70
set AT91C_HDMA_CH_1_CFG 0xFFFFEC78
# ========== Register definition for HDMA_CH_2 peripheral ========== 
set AT91C_HDMA_CH_2_SPIP 0xFFFFECA4
set AT91C_HDMA_CH_2_CTRLB 0xFFFFEC9C
set AT91C_HDMA_CH_2_DSCR 0xFFFFEC94
set AT91C_HDMA_CH_2_SADDR 0xFFFFEC8C
set AT91C_HDMA_CH_2_DPIP 0xFFFFECA8
set AT91C_HDMA_CH_2_CFG 0xFFFFECA0
set AT91C_HDMA_CH_2_CTRLA 0xFFFFEC98
set AT91C_HDMA_CH_2_DADDR 0xFFFFEC90
# ========== Register definition for HDMA_CH_3 peripheral ========== 
set AT91C_HDMA_CH_3_SPIP 0xFFFFECCC
set AT91C_HDMA_CH_3_CTRLB 0xFFFFECC4
set AT91C_HDMA_CH_3_DSCR 0xFFFFECBC
set AT91C_HDMA_CH_3_SADDR 0xFFFFECB4
set AT91C_HDMA_CH_3_DPIP 0xFFFFECD0
set AT91C_HDMA_CH_3_CFG 0xFFFFECC8
set AT91C_HDMA_CH_3_CTRLA 0xFFFFECC0
set AT91C_HDMA_CH_3_DADDR 0xFFFFECB8
# ========== Register definition for HDMA peripheral ========== 
set AT91C_HDMA_EBCIER 0xFFFFEC18
set AT91C_HDMA_LAST 0xFFFFEC10
set AT91C_HDMA_SREQ 0xFFFFEC08
set AT91C_HDMA_GCFG 0xFFFFEC00
set AT91C_HDMA_CHDR 0xFFFFEC2C
set AT91C_HDMA_EBCISR 0xFFFFEC24
set AT91C_HDMA_EBCIDR 0xFFFFEC1C
set AT91C_HDMA_SYNC 0xFFFFEC14
set AT91C_HDMA_BREQ 0xFFFFEC0C
set AT91C_HDMA_CHSR 0xFFFFEC30
set AT91C_HDMA_CHER 0xFFFFEC28
set AT91C_HDMA_EBCIMR 0xFFFFEC20
set AT91C_HDMA_EN   0xFFFFEC04
# ========== Register definition for SYS peripheral ========== 
set AT91C_SYS_GPBR  0xFFFFFD50
# ========== Register definition for UHP peripheral ========== 
set AT91C_UHP_HcLSThreshold 0x00700044
set AT91C_UHP_HcRhStatus 0x00700050
set AT91C_UHP_HcRhDescriptorA 0x00700048
set AT91C_UHP_HcRevision 0x00700000
set AT91C_UHP_HcCommandStatus 0x00700008
set AT91C_UHP_HcRhPortStatus 0x00700054
set AT91C_UHP_HcRhDescriptorB 0x0070004C
set AT91C_UHP_HcControl 0x00700004
set AT91C_UHP_HcInterruptStatus 0x0070000C
set AT91C_UHP_HcInterruptDisable 0x00700014
set AT91C_UHP_HcPeriodCurrentED 0x0070001C
set AT91C_UHP_HcInterruptEnable 0x00700010
set AT91C_UHP_HcHCCA 0x00700018
set AT91C_UHP_HcControlHeadED 0x00700020
set AT91C_UHP_HcBulkHeadED 0x00700028
set AT91C_UHP_HcBulkDoneHead 0x00700030
set AT91C_UHP_HcControlCurrentED 0x00700024
set AT91C_UHP_HcBulkCurrentED 0x0070002C
set AT91C_UHP_HcFmInterval 0x00700034
set AT91C_UHP_HcFmNumber 0x0070003C
set AT91C_UHP_HcPeriodicStart 0x00700040
set AT91C_UHP_HcFmRemaining 0x00700038

# *****************************************************************************
#               BASE ADDRESS DEFINITIONS FOR AT91CAP9
# *****************************************************************************
set AT91C_BASE_HECC      0xFFFFE200
set AT91C_BASE_BCRAMC    0xFFFFE400
set AT91C_BASE_SDRAMC    0xFFFFE600
set AT91C_BASE_SDDRC     0xFFFFE600
set AT91C_BASE_SMC       0xFFFFE800
set AT91C_BASE_MATRIX_PRS 0xFFFFEA80
set AT91C_BASE_MATRIX    0xFFFFEA00
set AT91C_BASE_CCFG      0xFFFFEB10
set AT91C_BASE_PDC_DBGU  0xFFFFEF00
set AT91C_BASE_DBGU      0xFFFFEE00
set AT91C_BASE_AIC       0xFFFFF000
set AT91C_BASE_PIOA      0xFFFFF200
set AT91C_BASE_PIOB      0xFFFFF400
set AT91C_BASE_PIOC      0xFFFFF600
set AT91C_BASE_PIOD      0xFFFFF800
set AT91C_BASE_CKGR      0xFFFFFC1C
set AT91C_BASE_PMC       0xFFFFFC00
set AT91C_BASE_RSTC      0xFFFFFD00
set AT91C_BASE_SHDWC     0xFFFFFD10
set AT91C_BASE_RTTC      0xFFFFFD20
set AT91C_BASE_PITC      0xFFFFFD30
set AT91C_BASE_WDTC      0xFFFFFD40
set AT91C_BASE_UDP       0xFFF78000
set AT91C_BASE_UDPHS_EPTFIFO 0x00600000
set AT91C_BASE_UDPHS_EPT_0 0xFFF78100
set AT91C_BASE_UDPHS_EPT_1 0xFFF78120
set AT91C_BASE_UDPHS_EPT_2 0xFFF78140
set AT91C_BASE_UDPHS_EPT_3 0xFFF78160
set AT91C_BASE_UDPHS_EPT_4 0xFFF78180
set AT91C_BASE_UDPHS_EPT_5 0xFFF781A0
set AT91C_BASE_UDPHS_EPT_6 0xFFF781C0
set AT91C_BASE_UDPHS_EPT_7 0xFFF781E0
set AT91C_BASE_UDPHS_EPT_8 0xFFF78200
set AT91C_BASE_UDPHS_EPT_9 0xFFF78220
set AT91C_BASE_UDPHS_EPT_10 0xFFF78240
set AT91C_BASE_UDPHS_EPT_11 0xFFF78260
set AT91C_BASE_UDPHS_EPT_12 0xFFF78280
set AT91C_BASE_UDPHS_EPT_13 0xFFF782A0
set AT91C_BASE_UDPHS_EPT_14 0xFFF782C0
set AT91C_BASE_UDPHS_EPT_15 0xFFF782E0
set AT91C_BASE_UDPHS_DMA_1 0xFFF78310
set AT91C_BASE_UDPHS_DMA_2 0xFFF78320
set AT91C_BASE_UDPHS_DMA_3 0xFFF78330
set AT91C_BASE_UDPHS_DMA_4 0xFFF78340
set AT91C_BASE_UDPHS_DMA_5 0xFFF78350
set AT91C_BASE_UDPHS_DMA_6 0xFFF78360
set AT91C_BASE_UDPHS_DMA_7 0xFFF78370
set AT91C_BASE_UDPHS     0xFFF78000
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
set AT91C_BASE_PDC_TWI   0xFFF88100
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
set AT91C_BASE_PDC_AES   0xFFFB0100
set AT91C_BASE_AES       0xFFFB0000
set AT91C_BASE_PDC_TDES  0xFFFB0100
set AT91C_BASE_TDES      0xFFFB0000
set AT91C_BASE_PWMC_CH0  0xFFFB8200
set AT91C_BASE_PWMC_CH1  0xFFFB8220
set AT91C_BASE_PWMC_CH2  0xFFFB8240
set AT91C_BASE_PWMC_CH3  0xFFFB8260
set AT91C_BASE_PWMC      0xFFFB8000
set AT91C_BASE_MACB      0xFFFBC000
set AT91C_BASE_PDC_ADC   0xFFFC0100
set AT91C_BASE_ADC       0xFFFC0000
set AT91C_BASE_HISI      0xFFFC4000
set AT91C_BASE_LCDC      0x00500000
set AT91C_BASE_HDMA_CH_0 0xFFFFEC3C
set AT91C_BASE_HDMA_CH_1 0xFFFFEC64
set AT91C_BASE_HDMA_CH_2 0xFFFFEC8C
set AT91C_BASE_HDMA_CH_3 0xFFFFECB4
set AT91C_BASE_HDMA      0xFFFFEC00
set AT91C_BASE_SYS       0xFFFFE200
set AT91C_BASE_UHP       0x00700000

# *****************************************************************************
#               PERIPHERAL ID DEFINITIONS FOR AT91CAP9
# *****************************************************************************
set AT91C_ID_FIQ     0
set AT91C_ID_SYS     1
set AT91C_ID_PIOABCDE  2
set AT91C_ID_MPB0    3
set AT91C_ID_MPB1    4
set AT91C_ID_MPB2    5
set AT91C_ID_MPB3    6
set AT91C_ID_MPB4    7
set AT91C_ID_US0     8
set AT91C_ID_US1     9
set AT91C_ID_US2    10
set AT91C_ID_MCI0   11
set AT91C_ID_MCI1   12
set AT91C_ID_CAN    13
set AT91C_ID_TWI    14
set AT91C_ID_SPI0   15
set AT91C_ID_SPI1   16
set AT91C_ID_SSC0   17
set AT91C_ID_SSC1   18
set AT91C_ID_AC97C  19
set AT91C_ID_TC012  20
set AT91C_ID_PWMC   21
set AT91C_ID_EMAC   22
set AT91C_ID_AESTDES 23
set AT91C_ID_ADC    24
set AT91C_ID_HISI   25
set AT91C_ID_LCDC   26
set AT91C_ID_HDMA   27
set AT91C_ID_UDPHS  28
set AT91C_ID_UHP    29
set AT91C_ID_IRQ0   30
set AT91C_ID_IRQ1   31

# *****************************************************************************
#               PIO DEFINITIONS FOR AT91CAP9
# *****************************************************************************
set AT91C_PIO_PA0        [expr 1 <<  0 ]
set AT91C_PA0_MCI0_DA0 $AT91C_PIO_PA0
set AT91C_PA0_SPI0_MISO $AT91C_PIO_PA0
set AT91C_PIO_PA1        [expr 1 <<  1 ]
set AT91C_PA1_MCI0_CDA $AT91C_PIO_PA1
set AT91C_PA1_SPI0_MOSI $AT91C_PIO_PA1
set AT91C_PIO_PA10       [expr 1 << 10 ]
set AT91C_PA10_IRQ0     $AT91C_PIO_PA10
set AT91C_PA10_PWM1     $AT91C_PIO_PA10
set AT91C_PIO_PA11       [expr 1 << 11 ]
set AT91C_PA11_DMARQ0   $AT91C_PIO_PA11
set AT91C_PA11_PWM3     $AT91C_PIO_PA11
set AT91C_PIO_PA12       [expr 1 << 12 ]
set AT91C_PA12_CANTX    $AT91C_PIO_PA12
set AT91C_PA12_PCK0     $AT91C_PIO_PA12
set AT91C_PIO_PA13       [expr 1 << 13 ]
set AT91C_PA13_CANRX    $AT91C_PIO_PA13
set AT91C_PIO_PA14       [expr 1 << 14 ]
set AT91C_PA14_TCLK2    $AT91C_PIO_PA14
set AT91C_PA14_IRQ1     $AT91C_PIO_PA14
set AT91C_PIO_PA15       [expr 1 << 15 ]
set AT91C_PA15_DMARQ3   $AT91C_PIO_PA15
set AT91C_PA15_PCK2     $AT91C_PIO_PA15
set AT91C_PIO_PA16       [expr 1 << 16 ]
set AT91C_PA16_MCI1_CK  $AT91C_PIO_PA16
set AT91C_PA16_ISI_D0   $AT91C_PIO_PA16
set AT91C_PIO_PA17       [expr 1 << 17 ]
set AT91C_PA17_MCI1_CDA $AT91C_PIO_PA17
set AT91C_PA17_ISI_D1   $AT91C_PIO_PA17
set AT91C_PIO_PA18       [expr 1 << 18 ]
set AT91C_PA18_MCI1_DA0 $AT91C_PIO_PA18
set AT91C_PA18_ISI_D2   $AT91C_PIO_PA18
set AT91C_PIO_PA19       [expr 1 << 19 ]
set AT91C_PA19_MCI1_DA1 $AT91C_PIO_PA19
set AT91C_PA19_ISI_D3   $AT91C_PIO_PA19
set AT91C_PIO_PA2        [expr 1 <<  2 ]
set AT91C_PA2_MCI0_CK  $AT91C_PIO_PA2
set AT91C_PA2_SPI0_SPCK $AT91C_PIO_PA2
set AT91C_PIO_PA20       [expr 1 << 20 ]
set AT91C_PA20_MCI1_DA2 $AT91C_PIO_PA20
set AT91C_PA20_ISI_D4   $AT91C_PIO_PA20
set AT91C_PIO_PA21       [expr 1 << 21 ]
set AT91C_PA21_MCI1_DA3 $AT91C_PIO_PA21
set AT91C_PA21_ISI_D5   $AT91C_PIO_PA21
set AT91C_PIO_PA22       [expr 1 << 22 ]
set AT91C_PA22_TXD0     $AT91C_PIO_PA22
set AT91C_PA22_ISI_D6   $AT91C_PIO_PA22
set AT91C_PIO_PA23       [expr 1 << 23 ]
set AT91C_PA23_RXD0     $AT91C_PIO_PA23
set AT91C_PA23_ISI_D7   $AT91C_PIO_PA23
set AT91C_PIO_PA24       [expr 1 << 24 ]
set AT91C_PA24_RTS0     $AT91C_PIO_PA24
set AT91C_PA24_ISI_PCK  $AT91C_PIO_PA24
set AT91C_PIO_PA25       [expr 1 << 25 ]
set AT91C_PA25_CTS0     $AT91C_PIO_PA25
set AT91C_PA25_ISI_HSYNC $AT91C_PIO_PA25
set AT91C_PIO_PA26       [expr 1 << 26 ]
set AT91C_PA26_SCK0     $AT91C_PIO_PA26
set AT91C_PA26_ISI_VSYNC $AT91C_PIO_PA26
set AT91C_PIO_PA27       [expr 1 << 27 ]
set AT91C_PA27_PCK1     $AT91C_PIO_PA27
set AT91C_PA27_ISI_MCK  $AT91C_PIO_PA27
set AT91C_PIO_PA28       [expr 1 << 28 ]
set AT91C_PA28_SPI0_NPCS3A $AT91C_PIO_PA28
set AT91C_PA28_ISI_D8   $AT91C_PIO_PA28
set AT91C_PIO_PA29       [expr 1 << 29 ]
set AT91C_PA29_TIOA0    $AT91C_PIO_PA29
set AT91C_PA29_ISI_D9   $AT91C_PIO_PA29
set AT91C_PIO_PA3        [expr 1 <<  3 ]
set AT91C_PA3_MCI0_DA1 $AT91C_PIO_PA3
set AT91C_PA3_SPI0_NPCS1 $AT91C_PIO_PA3
set AT91C_PIO_PA30       [expr 1 << 30 ]
set AT91C_PA30_TIOB0    $AT91C_PIO_PA30
set AT91C_PA30_ISI_D10  $AT91C_PIO_PA30
set AT91C_PIO_PA31       [expr 1 << 31 ]
set AT91C_PA31_DMARQ1   $AT91C_PIO_PA31
set AT91C_PA31_ISI_D11  $AT91C_PIO_PA31
set AT91C_PIO_PA4        [expr 1 <<  4 ]
set AT91C_PA4_MCI0_DA2 $AT91C_PIO_PA4
set AT91C_PA4_SPI0_NPCS2A $AT91C_PIO_PA4
set AT91C_PIO_PA5        [expr 1 <<  5 ]
set AT91C_PA5_MCI0_DA3 $AT91C_PIO_PA5
set AT91C_PA5_SPI0_NPCS0 $AT91C_PIO_PA5
set AT91C_PIO_PA6        [expr 1 <<  6 ]
set AT91C_PA6_AC97FS   $AT91C_PIO_PA6
set AT91C_PIO_PA7        [expr 1 <<  7 ]
set AT91C_PA7_AC97CK   $AT91C_PIO_PA7
set AT91C_PIO_PA8        [expr 1 <<  8 ]
set AT91C_PA8_AC97TX   $AT91C_PIO_PA8
set AT91C_PIO_PA9        [expr 1 <<  9 ]
set AT91C_PA9_AC97RX   $AT91C_PIO_PA9
set AT91C_PIO_PB0        [expr 1 <<  0 ]
set AT91C_PB0_TF0      $AT91C_PIO_PB0
set AT91C_PIO_PB1        [expr 1 <<  1 ]
set AT91C_PB1_TK0      $AT91C_PIO_PB1
set AT91C_PIO_PB10       [expr 1 << 10 ]
set AT91C_PB10_RK1      $AT91C_PIO_PB10
set AT91C_PB10_PCK1     $AT91C_PIO_PB10
set AT91C_PIO_PB11       [expr 1 << 11 ]
set AT91C_PB11_RF1      $AT91C_PIO_PB11
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
set AT91C_PIO_PB17       [expr 1 << 17 ]
set AT91C_PB17_SPI1_NPCS2B $AT91C_PIO_PB17
set AT91C_PB17_AD0      $AT91C_PIO_PB17
set AT91C_PIO_PB18       [expr 1 << 18 ]
set AT91C_PB18_SPI1_NPCS3B $AT91C_PIO_PB18
set AT91C_PB18_AD1      $AT91C_PIO_PB18
set AT91C_PIO_PB19       [expr 1 << 19 ]
set AT91C_PB19_PWM0     $AT91C_PIO_PB19
set AT91C_PB19_AD2      $AT91C_PIO_PB19
set AT91C_PIO_PB2        [expr 1 <<  2 ]
set AT91C_PB2_TD0      $AT91C_PIO_PB2
set AT91C_PIO_PB20       [expr 1 << 20 ]
set AT91C_PB20_PWM1     $AT91C_PIO_PB20
set AT91C_PB20_AD3      $AT91C_PIO_PB20
set AT91C_PIO_PB21       [expr 1 << 21 ]
set AT91C_PB21_E_TXCK   $AT91C_PIO_PB21
set AT91C_PB21_TIOA2    $AT91C_PIO_PB21
set AT91C_PIO_PB22       [expr 1 << 22 ]
set AT91C_PB22_E_RXDV   $AT91C_PIO_PB22
set AT91C_PB22_TIOB2    $AT91C_PIO_PB22
set AT91C_PIO_PB23       [expr 1 << 23 ]
set AT91C_PB23_E_TX0    $AT91C_PIO_PB23
set AT91C_PB23_PCK3     $AT91C_PIO_PB23
set AT91C_PIO_PB24       [expr 1 << 24 ]
set AT91C_PB24_E_TX1    $AT91C_PIO_PB24
set AT91C_PIO_PB25       [expr 1 << 25 ]
set AT91C_PB25_E_RX0    $AT91C_PIO_PB25
set AT91C_PIO_PB26       [expr 1 << 26 ]
set AT91C_PB26_E_RX1    $AT91C_PIO_PB26
set AT91C_PIO_PB27       [expr 1 << 27 ]
set AT91C_PB27_E_RXER   $AT91C_PIO_PB27
set AT91C_PIO_PB28       [expr 1 << 28 ]
set AT91C_PB28_E_TXEN   $AT91C_PIO_PB28
set AT91C_PB28_TCLK0    $AT91C_PIO_PB28
set AT91C_PIO_PB29       [expr 1 << 29 ]
set AT91C_PB29_E_MDC    $AT91C_PIO_PB29
set AT91C_PB29_PWM3     $AT91C_PIO_PB29
set AT91C_PIO_PB3        [expr 1 <<  3 ]
set AT91C_PB3_RD0      $AT91C_PIO_PB3
set AT91C_PIO_PB30       [expr 1 << 30 ]
set AT91C_PB30_E_MDIO   $AT91C_PIO_PB30
set AT91C_PIO_PB31       [expr 1 << 31 ]
set AT91C_PB31_ADTRIG   $AT91C_PIO_PB31
set AT91C_PB31_E_F100   $AT91C_PIO_PB31
set AT91C_PIO_PB4        [expr 1 <<  4 ]
set AT91C_PB4_RK0      $AT91C_PIO_PB4
set AT91C_PB4_TWD      $AT91C_PIO_PB4
set AT91C_PIO_PB5        [expr 1 <<  5 ]
set AT91C_PB5_RF0      $AT91C_PIO_PB5
set AT91C_PB5_TWCK     $AT91C_PIO_PB5
set AT91C_PIO_PB6        [expr 1 <<  6 ]
set AT91C_PB6_TF1      $AT91C_PIO_PB6
set AT91C_PB6_TIOA1    $AT91C_PIO_PB6
set AT91C_PIO_PB7        [expr 1 <<  7 ]
set AT91C_PB7_TK1      $AT91C_PIO_PB7
set AT91C_PB7_TIOB1    $AT91C_PIO_PB7
set AT91C_PIO_PB8        [expr 1 <<  8 ]
set AT91C_PB8_TD1      $AT91C_PIO_PB8
set AT91C_PB8_PWM2     $AT91C_PIO_PB8
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
set AT91C_PC20_E_TX2    $AT91C_PIO_PC20
set AT91C_PIO_PC21       [expr 1 << 21 ]
set AT91C_PC21_LCDD17   $AT91C_PIO_PC21
set AT91C_PC21_E_TX3    $AT91C_PIO_PC21
set AT91C_PIO_PC22       [expr 1 << 22 ]
set AT91C_PC22_LCDD18   $AT91C_PIO_PC22
set AT91C_PC22_E_RX2    $AT91C_PIO_PC22
set AT91C_PIO_PC23       [expr 1 << 23 ]
set AT91C_PC23_LCDD19   $AT91C_PIO_PC23
set AT91C_PC23_E_RX3    $AT91C_PIO_PC23
set AT91C_PIO_PC24       [expr 1 << 24 ]
set AT91C_PC24_LCDD20   $AT91C_PIO_PC24
set AT91C_PC24_E_TXER   $AT91C_PIO_PC24
set AT91C_PIO_PC25       [expr 1 << 25 ]
set AT91C_PC25_LCDD21   $AT91C_PIO_PC25
set AT91C_PC25_E_CRS    $AT91C_PIO_PC25
set AT91C_PIO_PC26       [expr 1 << 26 ]
set AT91C_PC26_LCDD22   $AT91C_PIO_PC26
set AT91C_PC26_E_COL    $AT91C_PIO_PC26
set AT91C_PIO_PC27       [expr 1 << 27 ]
set AT91C_PC27_LCDD23   $AT91C_PIO_PC27
set AT91C_PC27_E_RXCK   $AT91C_PIO_PC27
set AT91C_PIO_PC28       [expr 1 << 28 ]
set AT91C_PC28_PWM0     $AT91C_PIO_PC28
set AT91C_PC28_TCLK1    $AT91C_PIO_PC28
set AT91C_PIO_PC29       [expr 1 << 29 ]
set AT91C_PC29_PCK0     $AT91C_PIO_PC29
set AT91C_PC29_PWM2     $AT91C_PIO_PC29
set AT91C_PIO_PC3        [expr 1 <<  3 ]
set AT91C_PC3_LCDDEN   $AT91C_PIO_PC3
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
set AT91C_PD10_EBI_CFCE2 $AT91C_PIO_PD10
set AT91C_PD10_SCK1     $AT91C_PIO_PD10
set AT91C_PIO_PD11       [expr 1 << 11 ]
set AT91C_PD11_EBI_NCS2 $AT91C_PIO_PD11
set AT91C_PIO_PD12       [expr 1 << 12 ]
set AT91C_PD12_EBI_A23  $AT91C_PIO_PD12
set AT91C_PIO_PD13       [expr 1 << 13 ]
set AT91C_PD13_EBI_A24  $AT91C_PIO_PD13
set AT91C_PIO_PD14       [expr 1 << 14 ]
set AT91C_PD14_EBI_A25_CFRNW $AT91C_PIO_PD14
set AT91C_PIO_PD15       [expr 1 << 15 ]
set AT91C_PD15_EBI_NCS3_NANDCS $AT91C_PIO_PD15
set AT91C_PIO_PD16       [expr 1 << 16 ]
set AT91C_PD16_EBI_D16  $AT91C_PIO_PD16
set AT91C_PIO_PD17       [expr 1 << 17 ]
set AT91C_PD17_EBI_D17  $AT91C_PIO_PD17
set AT91C_PIO_PD18       [expr 1 << 18 ]
set AT91C_PD18_EBI_D18  $AT91C_PIO_PD18
set AT91C_PIO_PD19       [expr 1 << 19 ]
set AT91C_PD19_EBI_D19  $AT91C_PIO_PD19
set AT91C_PIO_PD2        [expr 1 <<  2 ]
set AT91C_PD2_TXD2     $AT91C_PIO_PD2
set AT91C_PD2_SPI1_NPCS2D $AT91C_PIO_PD2
set AT91C_PIO_PD20       [expr 1 << 20 ]
set AT91C_PD20_EBI_D20  $AT91C_PIO_PD20
set AT91C_PIO_PD21       [expr 1 << 21 ]
set AT91C_PD21_EBI_D21  $AT91C_PIO_PD21
set AT91C_PIO_PD22       [expr 1 << 22 ]
set AT91C_PD22_EBI_D22  $AT91C_PIO_PD22
set AT91C_PIO_PD23       [expr 1 << 23 ]
set AT91C_PD23_EBI_D23  $AT91C_PIO_PD23
set AT91C_PIO_PD24       [expr 1 << 24 ]
set AT91C_PD24_EBI_D24  $AT91C_PIO_PD24
set AT91C_PIO_PD25       [expr 1 << 25 ]
set AT91C_PD25_EBI_D25  $AT91C_PIO_PD25
set AT91C_PIO_PD26       [expr 1 << 26 ]
set AT91C_PD26_EBI_D26  $AT91C_PIO_PD26
set AT91C_PIO_PD27       [expr 1 << 27 ]
set AT91C_PD27_EBI_D27  $AT91C_PIO_PD27
set AT91C_PIO_PD28       [expr 1 << 28 ]
set AT91C_PD28_EBI_D28  $AT91C_PIO_PD28
set AT91C_PIO_PD29       [expr 1 << 29 ]
set AT91C_PD29_EBI_D29  $AT91C_PIO_PD29
set AT91C_PIO_PD3        [expr 1 <<  3 ]
set AT91C_PD3_RXD2     $AT91C_PIO_PD3
set AT91C_PD3_SPI1_NPCS3D $AT91C_PIO_PD3
set AT91C_PIO_PD30       [expr 1 << 30 ]
set AT91C_PD30_EBI_D30  $AT91C_PIO_PD30
set AT91C_PIO_PD31       [expr 1 << 31 ]
set AT91C_PD31_EBI_D31  $AT91C_PIO_PD31
set AT91C_PIO_PD4        [expr 1 <<  4 ]
set AT91C_PD4_FIQ      $AT91C_PIO_PD4
set AT91C_PIO_PD5        [expr 1 <<  5 ]
set AT91C_PD5_DMARQ2   $AT91C_PIO_PD5
set AT91C_PD5_RTS2     $AT91C_PIO_PD5
set AT91C_PIO_PD6        [expr 1 <<  6 ]
set AT91C_PD6_EBI_NWAIT $AT91C_PIO_PD6
set AT91C_PD6_CTS2     $AT91C_PIO_PD6
set AT91C_PIO_PD7        [expr 1 <<  7 ]
set AT91C_PD7_EBI_NCS4_CFCS0 $AT91C_PIO_PD7
set AT91C_PD7_RTS1     $AT91C_PIO_PD7
set AT91C_PIO_PD8        [expr 1 <<  8 ]
set AT91C_PD8_EBI_NCS5_CFCS1 $AT91C_PIO_PD8
set AT91C_PD8_CTS1     $AT91C_PIO_PD8
set AT91C_PIO_PD9        [expr 1 <<  9 ]
set AT91C_PD9_EBI_CFCE1 $AT91C_PIO_PD9
set AT91C_PD9_SCK2     $AT91C_PIO_PD9

# *****************************************************************************
#               MEMORY MAPPING DEFINITIONS FOR AT91CAP9
# *****************************************************************************
set AT91C_IRAM 	 0x00100000
set AT91C_IRAM_SIZE	 0x00004000
set AT91C_IRAM_MIN	 0x00100000
set AT91C_IRAM_MIN_SIZE	 0x00004000
set AT91C_DPR  	 0x00200000
set AT91C_DPR_SIZE	 0x00004000
set AT91C_IROM 	 0x00400000
set AT91C_IROM_SIZE	 0x00008000
set AT91C_EBI_CS0	 0x10000000
set AT91C_EBI_CS0_SIZE	 0x10000000
set AT91C_EBI_CS1	 0x20000000
set AT91C_EBI_CS1_SIZE	 0x10000000
set AT91C_EBI_BCRAM	 0x20000000
set AT91C_EBI_BCRAM_SIZE	 0x10000000
set AT91C_EBI_BCRAM_16BIT	 0x20000000
set AT91C_EBI_BCRAM_16BIT_SIZE	 0x02000000
set AT91C_EBI_BCRAM_32BIT	 0x20000000
set AT91C_EBI_BCRAM_32BIT_SIZE	 0x04000000
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
set AT91C_EBI_SDRAM	 0x70000000
set AT91C_EBI_SDRAM_SIZE	 0x10000000
set AT91C_EBI_SDRAM_16BIT	 0x70000000
set AT91C_EBI_SDRAM_16BIT_SIZE	 0x02000000
set AT91C_EBI_SDRAM_32BIT	 0x70000000
set AT91C_EBI_SDRAM_32BIT_SIZE	 0x04000000


# *****************************************************************************
#               ATTRIBUTES DEFINITIONS FOR AT91CAP9
# *****************************************************************************
array set AT91CAP9_att {
	PDC 	{ LP 	PDC_DBGU_att 	PDC_MCI0_att 	PDC_MCI1_att 	PDC_TWI_att 	PDC_US0_att 	PDC_US1_att 	PDC_US2_att 	PDC_SSC0_att 	PDC_SSC1_att 	PDC_AC97C_att 	PDC_SPI0_att 	PDC_SPI1_att 	PDC_AES_att 	PDC_TDES_att 	PDC_ADC_att }
	SYS 	{ LP 	SYS_att }
	UHP 	{ LP 	UHP_att }
	EMAC 	{ LP 	MACB_att }
	SPI 	{ LP 	SPI0_att 	SPI1_att }
	HDMA_CH 	{ LP 	HDMA_CH_0_att 	HDMA_CH_1_att 	HDMA_CH_2_att 	HDMA_CH_3_att }
	BCRAMC 	{ LP 	BCRAMC_att }
	CCFG 	{ LP 	CCFG_att }
	ISI 	{ LP 	HISI_att }
	UDPHS_EPT 	{ LP 	UDPHS_EPT_0_att 	UDPHS_EPT_1_att 	UDPHS_EPT_2_att 	UDPHS_EPT_3_att 	UDPHS_EPT_4_att 	UDPHS_EPT_5_att 	UDPHS_EPT_6_att 	UDPHS_EPT_7_att 	UDPHS_EPT_8_att 	UDPHS_EPT_9_att 	UDPHS_EPT_10_att 	UDPHS_EPT_11_att 	UDPHS_EPT_12_att 	UDPHS_EPT_13_att 	UDPHS_EPT_14_att 	UDPHS_EPT_15_att }
	MATRIX 	{ LP 	MATRIX_att }
	MATRIX_PRS 	{ LP 	MATRIX_PRS_att }
	RSTC 	{ LP 	RSTC_att }
	CKGR 	{ LP 	CKGR_att }
	UDPHS 	{ LP 	UDPHS_att }
	TWI 	{ LP 	TWI_att }
	SDRAMC 	{ LP 	SDRAMC_att }
	USART 	{ LP 	US0_att 	US1_att 	US2_att }
	WDTC 	{ LP 	WDTC_att }
	SMC 	{ LP 	SMC_att }
	ECC 	{ LP 	HECC_att }
	AIC 	{ LP 	AIC_att }
	CAN 	{ LP 	CAN_att }
	TDES 	{ LP 	TDES_att }
	DBGU 	{ LP 	DBGU_att }
	PWMC_CH 	{ LP 	PWMC_CH0_att 	PWMC_CH1_att 	PWMC_CH2_att 	PWMC_CH3_att }
	AES 	{ LP 	AES_att }
	SHDWC 	{ LP 	SHDWC_att }
	SSC 	{ LP 	SSC0_att 	SSC1_att }
	TCB 	{ LP 	TCB0_att 	TCB1_att 	TCB2_att }
	PWMC 	{ LP 	PWMC_att }
	LCDC 	{ LP 	LCDC_att }
	SDDRC 	{ LP 	SDDRC_att }
	HDMA 	{ LP 	HDMA_att }
	PITC 	{ LP 	PITC_att }
	TC 	{ LP 	TC0_att 	TC1_att 	TC2_att }
	ADC 	{ LP 	ADC_att }
	PMC 	{ LP 	PMC_att }
	UDPHS_DMA 	{ LP 	UDPHS_DMA_1_att 	UDPHS_DMA_2_att 	UDPHS_DMA_3_att 	UDPHS_DMA_4_att 	UDPHS_DMA_5_att 	UDPHS_DMA_6_att 	UDPHS_DMA_7_att }
	AC97C 	{ LP 	AC97C_att }
	CAN_MB 	{ LP 	CAN_MB0_att 	CAN_MB1_att 	CAN_MB2_att 	CAN_MB3_att 	CAN_MB4_att 	CAN_MB5_att 	CAN_MB6_att 	CAN_MB7_att 	CAN_MB8_att 	CAN_MB9_att 	CAN_MB10_att 	CAN_MB11_att 	CAN_MB12_att 	CAN_MB13_att 	CAN_MB14_att 	CAN_MB15_att }
	PIO 	{ LP 	PIOA_att 	PIOB_att 	PIOC_att 	PIOD_att }
	RTTC 	{ LP 	RTTC_att }
	UDPHS_EPTFIFO 	{ LP 	UDPHS_EPTFIFO_att }
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
array set PDC_TWI_att {
	PTCR 	{ R AT91C_TWI_PTCR 	WO }
	TNPR 	{ R AT91C_TWI_TNPR 	RW }
	RNPR 	{ R AT91C_TWI_RNPR 	RW }
	TPR 	{ R AT91C_TWI_TPR 	RW }
	RPR 	{ R AT91C_TWI_RPR 	RW }
	PTSR 	{ R AT91C_TWI_PTSR 	RO }
	TNCR 	{ R AT91C_TWI_TNCR 	RW }
	RNCR 	{ R AT91C_TWI_RNCR 	RW }
	TCR 	{ R AT91C_TWI_TCR 	RW }
	RCR 	{ R AT91C_TWI_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

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
array set PDC_AES_att {
	TNCR 	{ R AT91C_AES_TNCR 	RW }
	RNCR 	{ R AT91C_AES_RNCR 	RW }
	TCR 	{ R AT91C_AES_TCR 	RW }
	RCR 	{ R AT91C_AES_RCR 	RW }
	PTCR 	{ R AT91C_AES_PTCR 	WO }
	TNPR 	{ R AT91C_AES_TNPR 	RW }
	RNPR 	{ R AT91C_AES_RNPR 	RW }
	PTSR 	{ R AT91C_AES_PTSR 	RO }
	RPR 	{ R AT91C_AES_RPR 	RW }
	TPR 	{ R AT91C_AES_TPR 	RW }
	listeReg 	{ TNCR RNCR TCR RCR PTCR TNPR RNPR PTSR RPR TPR  }

}
array set PDC_TDES_att {
	TNCR 	{ R AT91C_TDES_TNCR 	RW }
	RNCR 	{ R AT91C_TDES_RNCR 	RW }
	TCR 	{ R AT91C_TDES_TCR 	RW }
	RCR 	{ R AT91C_TDES_RCR 	RW }
	PTCR 	{ R AT91C_TDES_PTCR 	WO }
	TNPR 	{ R AT91C_TDES_TNPR 	RW }
	RNPR 	{ R AT91C_TDES_RNPR 	RW }
	PTSR 	{ R AT91C_TDES_PTSR 	RO }
	RPR 	{ R AT91C_TDES_RPR 	RW }
	TPR 	{ R AT91C_TDES_TPR 	RW }
	listeReg 	{ TNCR RNCR TCR RCR PTCR TNPR RNPR PTSR RPR TPR  }

}
array set PDC_ADC_att {
	PTCR 	{ R AT91C_ADC_PTCR 	WO }
	TNPR 	{ R AT91C_ADC_TNPR 	RW }
	RNPR 	{ R AT91C_ADC_RNPR 	RW }
	TPR 	{ R AT91C_ADC_TPR 	RW }
	RPR 	{ R AT91C_ADC_RPR 	RW }
	PTSR 	{ R AT91C_ADC_PTSR 	RO }
	TNCR 	{ R AT91C_ADC_TNCR 	RW }
	RNCR 	{ R AT91C_ADC_RNCR 	RW }
	TCR 	{ R AT91C_ADC_TCR 	RW }
	RCR 	{ R AT91C_ADC_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}

# ========== Peripheral attributes for SYS peripheral ========== 
array set SYS_att {
	GPBR 	{ R AT91C_SYS_GPBR 	  4 }
	listeReg 	{ GPBR  }

}

# ========== Peripheral attributes for UHP peripheral ========== 
array set UHP_att {
	HcLSThreshold 	{ R AT91C_UHP_HcLSThreshold 	RW }
	HcRhStatus 	{ R AT91C_UHP_HcRhStatus 	RW }
	HcRhDescriptorA 	{ R AT91C_UHP_HcRhDescriptorA 	RW }
	HcRevision 	{ R AT91C_UHP_HcRevision 	R }
	HcCommandStatus 	{ R AT91C_UHP_HcCommandStatus 	RW }
	HcRhPortStatus 	{ R AT91C_UHP_HcRhPortStatus 	RW  2 }
	HcRhDescriptorB 	{ R AT91C_UHP_HcRhDescriptorB 	RW }
	HcControl 	{ R AT91C_UHP_HcControl 	RW }
	HcInterruptStatus 	{ R AT91C_UHP_HcInterruptStatus 	RW }
	HcInterruptDisable 	{ R AT91C_UHP_HcInterruptDisable 	RW }
	HcPeriodCurrentED 	{ R AT91C_UHP_HcPeriodCurrentED 	RW }
	HcInterruptEnable 	{ R AT91C_UHP_HcInterruptEnable 	RW }
	HcHCCA 	{ R AT91C_UHP_HcHCCA 	RW }
	HcControlHeadED 	{ R AT91C_UHP_HcControlHeadED 	RW }
	HcBulkHeadED 	{ R AT91C_UHP_HcBulkHeadED 	RW }
	HcBulkDoneHead 	{ R AT91C_UHP_HcBulkDoneHead 	RW }
	HcControlCurrentED 	{ R AT91C_UHP_HcControlCurrentED 	RW }
	HcBulkCurrentED 	{ R AT91C_UHP_HcBulkCurrentED 	RW }
	HcFmInterval 	{ R AT91C_UHP_HcFmInterval 	RW }
	HcFmNumber 	{ R AT91C_UHP_HcFmNumber 	RW }
	HcPeriodicStart 	{ R AT91C_UHP_HcPeriodicStart 	RW }
	HcFmRemaining 	{ R AT91C_UHP_HcFmRemaining 	RW }
	listeReg 	{ HcLSThreshold HcRhStatus HcRhDescriptorA HcRevision HcCommandStatus HcRhPortStatus HcRhDescriptorB HcControl HcInterruptStatus HcInterruptDisable HcPeriodCurrentED HcInterruptEnable HcHCCA HcControlHeadED HcBulkHeadED HcBulkDoneHead HcControlCurrentED HcBulkCurrentED HcFmInterval HcFmNumber HcPeriodicStart HcFmRemaining  }

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

# ========== Peripheral attributes for HDMA_CH peripheral ========== 
array set HDMA_CH_0_att {
	DPIP 	{ R AT91C_HDMA_CH_0_DPIP 	RW }
	CFG 	{ R AT91C_HDMA_CH_0_CFG 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_0_CTRLA 	RW }
	DADDR 	{ R AT91C_HDMA_CH_0_DADDR 	RW }
	SPIP 	{ R AT91C_HDMA_CH_0_SPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_0_CTRLB 	RW }
	DSCR 	{ R AT91C_HDMA_CH_0_DSCR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_0_SADDR 	RW }
	listeReg 	{ DPIP CFG CTRLA DADDR SPIP CTRLB DSCR SADDR  }

}
array set HDMA_CH_1_att {
	DADDR 	{ R AT91C_HDMA_CH_1_DADDR 	RW }
	SPIP 	{ R AT91C_HDMA_CH_1_SPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_1_CTRLB 	RW }
	DSCR 	{ R AT91C_HDMA_CH_1_DSCR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_1_SADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_1_DPIP 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_1_CTRLA 	RW }
	CFG 	{ R AT91C_HDMA_CH_1_CFG 	RW }
	listeReg 	{ DADDR SPIP CTRLB DSCR SADDR DPIP CTRLA CFG  }

}
array set HDMA_CH_2_att {
	SPIP 	{ R AT91C_HDMA_CH_2_SPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_2_CTRLB 	RW }
	DSCR 	{ R AT91C_HDMA_CH_2_DSCR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_2_SADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_2_DPIP 	RW }
	CFG 	{ R AT91C_HDMA_CH_2_CFG 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_2_CTRLA 	RW }
	DADDR 	{ R AT91C_HDMA_CH_2_DADDR 	RW }
	listeReg 	{ SPIP CTRLB DSCR SADDR DPIP CFG CTRLA DADDR  }

}
array set HDMA_CH_3_att {
	SPIP 	{ R AT91C_HDMA_CH_3_SPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_3_CTRLB 	RW }
	DSCR 	{ R AT91C_HDMA_CH_3_DSCR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_3_SADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_3_DPIP 	RW }
	CFG 	{ R AT91C_HDMA_CH_3_CFG 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_3_CTRLA 	RW }
	DADDR 	{ R AT91C_HDMA_CH_3_DADDR 	RW }
	listeReg 	{ SPIP CTRLB DSCR SADDR DPIP CFG CTRLA DADDR  }

}

# ========== Peripheral attributes for BCRAMC peripheral ========== 
array set BCRAMC_att {
	MDR 	{ R AT91C_BCRAMC_MDR 	RO }
	HSR 	{ R AT91C_BCRAMC_HSR 	RW }
	CR 	{ R AT91C_BCRAMC_CR 	RW }
	VR 	{ R AT91C_BCRAMC_VR 	RO }
	IPNR2 	{ R AT91C_BCRAMC_IPNR2 	RO }
	PADDSR 	{ R AT91C_BCRAMC_PADDSR 	RO }
	LPR 	{ R AT91C_BCRAMC_LPR 	RW }
	TPR 	{ R AT91C_BCRAMC_TPR 	RW }
	IPFR 	{ R AT91C_BCRAMC_IPFR 	RO }
	IPNR1 	{ R AT91C_BCRAMC_IPNR1 	RO }
	listeReg 	{ MDR HSR CR VR IPNR2 PADDSR LPR TPR IPFR IPNR1  }

}

# ========== Peripheral attributes for CCFG peripheral ========== 
array set CCFG_att {
	BRIDGE 	{ R AT91C_CCFG_BRIDGE 	RW }
	MPBS2 	{ R AT91C_CCFG_MPBS2 	RW }
	MPBS1 	{ R AT91C_CCFG_MPBS1 	RW }
	MPBS0 	{ R AT91C_CCFG_MPBS0 	RW }
	MATRIXVERSION 	{ R AT91C_CCFG_MATRIXVERSION 	RO }
	MPBS3 	{ R AT91C_CCFG_MPBS3 	RW }
	EBICSA 	{ R AT91C_CCFG_EBICSA 	RW }
	UDPHS 	{ R AT91C_CCFG_UDPHS 	RW }
	listeReg 	{ BRIDGE MPBS2 MPBS1 MPBS0 MATRIXVERSION MPBS3 EBICSA UDPHS  }

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

# ========== Peripheral attributes for UDPHS_EPT peripheral ========== 
array set UDPHS_EPT_0_att {
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_0_EPTCTLENB 	WO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_0_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_0_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_0_EPTCTL 	RO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_0_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_0_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_0_EPTCFG 	RW }
	listeReg 	{ EPTCTLENB EPTSTA EPTSETSTA EPTCTL EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_1_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_1_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_1_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_1_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_1_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_1_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_1_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_1_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_2_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_2_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_2_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_2_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_2_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_2_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_2_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_2_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_3_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_3_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_3_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_3_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_3_EPTCTLENB 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_3_EPTCTLDIS 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_3_EPTCLRSTA 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_3_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCTLDIS EPTCLRSTA EPTCFG  }

}
array set UDPHS_EPT_4_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_4_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_4_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_4_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_4_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_4_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_4_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_4_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_5_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_5_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_5_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_5_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_5_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_5_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_5_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_5_EPTCFG 	RW }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG  }

}
array set UDPHS_EPT_6_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_6_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_6_EPTSETSTA 	WO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_6_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_6_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_6_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_6_EPTCFG 	RW }
	EPTCTL 	{ R AT91C_UDPHS_EPT_6_EPTCTL 	RO }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG EPTCTL  }

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
	EPTCTL 	{ R AT91C_UDPHS_EPT_9_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_9_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_9_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_9_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_9_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_9_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_9_EPTSETSTA 	WO }
	listeReg 	{ EPTCTL EPTCTLENB EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA  }

}
array set UDPHS_EPT_10_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_10_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_10_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_10_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_10_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_10_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_10_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_10_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_11_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_11_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_11_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_11_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_11_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_11_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_11_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_11_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_12_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_12_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_12_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_12_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_12_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_12_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_12_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_12_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_13_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_13_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_13_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_13_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_13_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_13_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_13_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_13_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_14_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_14_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_14_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_14_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_14_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_14_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_14_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_14_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTCFG EPTSTA EPTSETSTA EPTCTL EPTCTLENB  }

}
array set UDPHS_EPT_15_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_15_EPTSTA 	RO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_15_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_15_EPTCFG 	RW }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_15_EPTCLRSTA 	WO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_15_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_15_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_15_EPTCTLENB 	WO }
	listeReg 	{ EPTSTA EPTCTLDIS EPTCFG EPTCLRSTA EPTSETSTA EPTCTL EPTCTLENB  }

}

# ========== Peripheral attributes for MATRIX peripheral ========== 
array set MATRIX_att {
	MCFG 	{ R AT91C_MATRIX_MCFG 	RW 12 }
	MRCR 	{ R AT91C_MATRIX_MRCR 	RW }
	SCFG 	{ R AT91C_MATRIX_SCFG 	RW  9 }
	listeReg 	{ MCFG MRCR SCFG  }

}

# ========== Peripheral attributes for MATRIX_PRS peripheral ========== 
array set MATRIX_PRS_att {
	PRBS 	{ R AT91C_MATRIX_PRS_PRBS 	RW }
	PRAS 	{ R AT91C_MATRIX_PRS_PRAS 	RW }
	listeReg 	{ PRBS PRAS  }

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
	UCKR 	{ R AT91C_CKGR_UCKR 	RW }
	PLLAR 	{ R AT91C_CKGR_PLLAR 	RW }
	MOR 	{ R AT91C_CKGR_MOR 	RW }
	listeReg 	{ PLLBR MCFR UCKR PLLAR MOR  }

}

# ========== Peripheral attributes for UDPHS peripheral ========== 
array set UDPHS_att {
	CLRINT 	{ R AT91C_UDPHS_CLRINT 	WO }
	IEN 	{ R AT91C_UDPHS_IEN 	RW }
	TSTMODREG 	{ R AT91C_UDPHS_TSTMODREG 	RW }
	TSTCNTA 	{ R AT91C_UDPHS_TSTCNTA 	RW }
	EPTRST 	{ R AT91C_UDPHS_EPTRST 	WO }
	IPNAME1 	{ R AT91C_UDPHS_IPNAME1 	RO }
	TST 	{ R AT91C_UDPHS_TST 	RW }
	TSTCNTB 	{ R AT91C_UDPHS_TSTCNTB 	RW }
	TSTSOFCNT 	{ R AT91C_UDPHS_TSTSOFCNT 	RW }
	CTRL 	{ R AT91C_UDPHS_CTRL 	RW }
	IPVERSION 	{ R AT91C_UDPHS_IPVERSION 	RO }
	IPNAME2 	{ R AT91C_UDPHS_IPNAME2 	RO }
	IPPADDRSIZE 	{ R AT91C_UDPHS_IPPADDRSIZE 	RO }
	FNUM 	{ R AT91C_UDPHS_FNUM 	RO }
	INTSTA 	{ R AT91C_UDPHS_INTSTA 	RO }
	IPFEATURES 	{ R AT91C_UDPHS_IPFEATURES 	RO }
	listeReg 	{ CLRINT IEN TSTMODREG TSTCNTA EPTRST IPNAME1 TST TSTCNTB TSTSOFCNT CTRL IPVERSION IPNAME2 IPPADDRSIZE FNUM INTSTA IPFEATURES  }

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
	SMR 	{ R AT91C_TWI_SMR 	RW }
	CR 	{ R AT91C_TWI_CR 	WO }
	listeReg 	{ THR IMR IER IADR MMR RHR IDR SR CWGR SMR CR  }

}

# ========== Peripheral attributes for SDRAMC peripheral ========== 
array set SDRAMC_att {
	MDR 	{ R AT91C_SDRAMC_MDR 	RO }
	IMR 	{ R AT91C_SDRAMC_IMR 	RO }
	IER 	{ R AT91C_SDRAMC_IER 	WO }
	HSR 	{ R AT91C_SDRAMC_HSR 	RW }
	TR 	{ R AT91C_SDRAMC_TR 	RW }
	ISR 	{ R AT91C_SDRAMC_ISR 	RO }
	IDR 	{ R AT91C_SDRAMC_IDR 	WO }
	LPR 	{ R AT91C_SDRAMC_LPR 	RW }
	CR 	{ R AT91C_SDRAMC_CR 	RW }
	MR 	{ R AT91C_SDRAMC_MR 	RW }
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
array set SMC_att {
	PULSE4 	{ R AT91C_SMC_PULSE4 	RW }
	CTRL3 	{ R AT91C_SMC_CTRL3 	RW }
	PULSE3 	{ R AT91C_SMC_PULSE3 	RW }
	CYCLE5 	{ R AT91C_SMC_CYCLE5 	RW }
	SETUP5 	{ R AT91C_SMC_SETUP5 	RW }
	CYCLE4 	{ R AT91C_SMC_CYCLE4 	RW }
	SETUP4 	{ R AT91C_SMC_SETUP4 	RW }
	CYCLE3 	{ R AT91C_SMC_CYCLE3 	RW }
	CYCLE0 	{ R AT91C_SMC_CYCLE0 	RW }
	SETUP0 	{ R AT91C_SMC_SETUP0 	RW }
	CTRL6 	{ R AT91C_SMC_CTRL6 	RW }
	PULSE6 	{ R AT91C_SMC_PULSE6 	RW }
	CTRL5 	{ R AT91C_SMC_CTRL5 	RW }
	PULSE5 	{ R AT91C_SMC_PULSE5 	RW }
	CTRL4 	{ R AT91C_SMC_CTRL4 	RW }
	PULSE0 	{ R AT91C_SMC_PULSE0 	RW }
	CTRL0 	{ R AT91C_SMC_CTRL0 	RW }
	PULSE1 	{ R AT91C_SMC_PULSE1 	RW }
	CTRL1 	{ R AT91C_SMC_CTRL1 	RW }
	CYCLE7 	{ R AT91C_SMC_CYCLE7 	RW }
	SETUP7 	{ R AT91C_SMC_SETUP7 	RW }
	CYCLE6 	{ R AT91C_SMC_CYCLE6 	RW }
	SETUP6 	{ R AT91C_SMC_SETUP6 	RW }
	SETUP1 	{ R AT91C_SMC_SETUP1 	RW }
	CYCLE1 	{ R AT91C_SMC_CYCLE1 	RW }
	SETUP2 	{ R AT91C_SMC_SETUP2 	RW }
	CYCLE2 	{ R AT91C_SMC_CYCLE2 	RW }
	CTRL7 	{ R AT91C_SMC_CTRL7 	RW }
	PULSE7 	{ R AT91C_SMC_PULSE7 	RW }
	PULSE2 	{ R AT91C_SMC_PULSE2 	RW }
	CTRL2 	{ R AT91C_SMC_CTRL2 	RW }
	SETUP3 	{ R AT91C_SMC_SETUP3 	RW }
	listeReg 	{ PULSE4 CTRL3 PULSE3 CYCLE5 SETUP5 CYCLE4 SETUP4 CYCLE3 CYCLE0 SETUP0 CTRL6 PULSE6 CTRL5 PULSE5 CTRL4 PULSE0 CTRL0 PULSE1 CTRL1 CYCLE7 SETUP7 CYCLE6 SETUP6 SETUP1 CYCLE1 SETUP2 CYCLE2 CTRL7 PULSE7 PULSE2 CTRL2 SETUP3  }

}

# ========== Peripheral attributes for ECC peripheral ========== 
array set HECC_att {
	NPR 	{ R AT91C_HECC_NPR 	RO }
	SR 	{ R AT91C_HECC_SR 	RO }
	CR 	{ R AT91C_HECC_CR 	WO }
	VR 	{ R AT91C_HECC_VR 	RO }
	PR 	{ R AT91C_HECC_PR 	RO }
	MR 	{ R AT91C_HECC_MR 	RW }
	listeReg 	{ NPR SR CR VR PR MR  }

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

# ========== Peripheral attributes for TDES peripheral ========== 
array set TDES_att {
	VR 	{ R AT91C_TDES_VR 	RO }
	ISR 	{ R AT91C_TDES_ISR 	RO }
	IDR 	{ R AT91C_TDES_IDR 	WO }
	IDATAxR 	{ R AT91C_TDES_IDATAxR 	WO  2 }
	KEY3WxR 	{ R AT91C_TDES_KEY3WxR 	WO  2 }
	KEY2WxR 	{ R AT91C_TDES_KEY2WxR 	WO  2 }
	KEY1WxR 	{ R AT91C_TDES_KEY1WxR 	WO  2 }
	MR 	{ R AT91C_TDES_MR 	RW }
	IVxR 	{ R AT91C_TDES_IVxR 	W0  2 }
	CR 	{ R AT91C_TDES_CR 	WO }
	IER 	{ R AT91C_TDES_IER 	WO }
	IMR 	{ R AT91C_TDES_IMR 	RO }
	ODATAxR 	{ R AT91C_TDES_ODATAxR 	R0  2 }
	listeReg 	{ VR ISR IDR IDATAxR KEY3WxR KEY2WxR KEY1WxR MR IVxR CR IER IMR ODATAxR  }

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

# ========== Peripheral attributes for AES peripheral ========== 
array set AES_att {
	VR 	{ R AT91C_AES_VR 	RO }
	ISR 	{ R AT91C_AES_ISR 	RO }
	IDR 	{ R AT91C_AES_IDR 	WO }
	IDATAxR 	{ R AT91C_AES_IDATAxR 	WO  4 }
	KEYWxR 	{ R AT91C_AES_KEYWxR 	WO  4 }
	MR 	{ R AT91C_AES_MR 	RW }
	IVxR 	{ R AT91C_AES_IVxR 	W0  4 }
	CR 	{ R AT91C_AES_CR 	WO }
	IER 	{ R AT91C_AES_IER 	WO }
	IMR 	{ R AT91C_AES_IMR 	RO }
	ODATAxR 	{ R AT91C_AES_ODATAxR 	R0  4 }
	listeReg 	{ VR ISR IDR IDATAxR KEYWxR MR IVxR CR IER IMR ODATAxR  }

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

# ========== Peripheral attributes for SDDRC peripheral ========== 
array set SDDRC_att {
	HS 	{ R AT91C_SDDRC_HS 	RW }
	T0PR 	{ R AT91C_SDDRC_T0PR 	RW }
	RTR 	{ R AT91C_SDDRC_RTR 	RW }
	LPR 	{ R AT91C_SDDRC_LPR 	RW }
	T1PR 	{ R AT91C_SDDRC_T1PR 	RW }
	CR 	{ R AT91C_SDDRC_CR 	RW }
	MDR 	{ R AT91C_SDDRC_MDR 	RW }
	MR 	{ R AT91C_SDDRC_MR 	RW }
	VERSION 	{ R AT91C_SDDRC_VERSION 	RO }
	listeReg 	{ HS T0PR RTR LPR T1PR CR MDR MR VERSION  }

}

# ========== Peripheral attributes for HDMA peripheral ========== 
array set HDMA_att {
	EBCIER 	{ R AT91C_HDMA_EBCIER 	WO }
	LAST 	{ R AT91C_HDMA_LAST 	RW }
	SREQ 	{ R AT91C_HDMA_SREQ 	RW }
	GCFG 	{ R AT91C_HDMA_GCFG 	RW }
	CHDR 	{ R AT91C_HDMA_CHDR 	WO }
	EBCISR 	{ R AT91C_HDMA_EBCISR 	RO }
	EBCIDR 	{ R AT91C_HDMA_EBCIDR 	WO }
	SYNC 	{ R AT91C_HDMA_SYNC 	RW }
	BREQ 	{ R AT91C_HDMA_BREQ 	RW }
	CHSR 	{ R AT91C_HDMA_CHSR 	RO }
	CHER 	{ R AT91C_HDMA_CHER 	WO }
	EBCIMR 	{ R AT91C_HDMA_EBCIMR 	RO }
	EN 	{ R AT91C_HDMA_EN 	RW }
	listeReg 	{ EBCIER LAST SREQ GCFG CHDR EBCISR EBCIDR SYNC BREQ CHSR CHER EBCIMR EN  }

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

# ========== Peripheral attributes for ADC peripheral ========== 
array set ADC_att {
	CDR0 	{ R AT91C_ADC_CDR0 	RO }
	CDR5 	{ R AT91C_ADC_CDR5 	RO }
	CDR3 	{ R AT91C_ADC_CDR3 	RO }
	CDR1 	{ R AT91C_ADC_CDR1 	RO }
	CDR6 	{ R AT91C_ADC_CDR6 	RO }
	CDR4 	{ R AT91C_ADC_CDR4 	RO }
	CDR2 	{ R AT91C_ADC_CDR2 	RO }
	CR 	{ R AT91C_ADC_CR 	WO }
	CDR7 	{ R AT91C_ADC_CDR7 	RO }
	MR 	{ R AT91C_ADC_MR 	RW }
	CHDR 	{ R AT91C_ADC_CHDR 	WO }
	SR 	{ R AT91C_ADC_SR 	RO }
	CHER 	{ R AT91C_ADC_CHER 	WO }
	CHSR 	{ R AT91C_ADC_CHSR 	RO }
	LCDR 	{ R AT91C_ADC_LCDR 	RO }
	IDR 	{ R AT91C_ADC_IDR 	WO }
	IER 	{ R AT91C_ADC_IER 	WO }
	IMR 	{ R AT91C_ADC_IMR 	RO }
	listeReg 	{ CDR0 CDR5 CDR3 CDR1 CDR6 CDR4 CDR2 CR CDR7 MR CHDR SR CHER CHSR LCDR IDR IER IMR  }

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
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_2_DMANXTDSC 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_2_DMACONTROL 	RW }
	listeReg 	{ DMASTATUS DMAADDRESS DMANXTDSC DMACONTROL  }

}
array set UDPHS_DMA_3_att {
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_3_DMAADDRESS 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_3_DMASTATUS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_3_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_3_DMANXTDSC 	RW }
	listeReg 	{ DMAADDRESS DMASTATUS DMACONTROL DMANXTDSC  }

}
array set UDPHS_DMA_4_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_4_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_4_DMAADDRESS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_4_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_4_DMANXTDSC 	RW }
	listeReg 	{ DMASTATUS DMAADDRESS DMACONTROL DMANXTDSC  }

}
array set UDPHS_DMA_5_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_5_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_5_DMAADDRESS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_5_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_5_DMANXTDSC 	RW }
	listeReg 	{ DMASTATUS DMAADDRESS DMACONTROL DMANXTDSC  }

}
array set UDPHS_DMA_6_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_6_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_6_DMAADDRESS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_6_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_6_DMANXTDSC 	RW }
	listeReg 	{ DMASTATUS DMAADDRESS DMACONTROL DMANXTDSC  }

}
array set UDPHS_DMA_7_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_7_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_7_DMAADDRESS 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_7_DMANXTDSC 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_7_DMACONTROL 	RW }
	listeReg 	{ DMASTATUS DMAADDRESS DMANXTDSC DMACONTROL  }

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

# ========== Peripheral attributes for RTTC peripheral ========== 
array set RTTC_att {
	RTSR 	{ R AT91C_RTTC_RTSR 	RO }
	RTAR 	{ R AT91C_RTTC_RTAR 	RW }
	RTVR 	{ R AT91C_RTTC_RTVR 	RO }
	RTMR 	{ R AT91C_RTTC_RTMR 	RW }
	listeReg 	{ RTSR RTAR RTVR RTMR  }

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
 	PA10 	{  IRQ0   PWM1  }
 	PA11 	{  DMARQ0   PWM3  }
 	PA12 	{  CANTX   PCK0  }
 	PA13 	{  CANRX  }
 	PA14 	{  TCLK2   IRQ1  }
 	PA15 	{  DMARQ3   PCK2  }
 	PA16 	{  MCI1_CK   ISI_D0  }
 	PA17 	{  MCI1_CDA   ISI_D1  }
 	PA18 	{  MCI1_DA0   ISI_D2  }
 	PA19 	{  MCI1_DA1   ISI_D3  }
 	PA2 	{  MCI0_CK   SPI0_SPCK  }
 	PA20 	{  MCI1_DA2   ISI_D4  }
 	PA21 	{  MCI1_DA3   ISI_D5  }
 	PA22 	{  TXD0   ISI_D6  }
 	PA23 	{  RXD0   ISI_D7  }
 	PA24 	{  RTS0   ISI_PCK  }
 	PA25 	{  CTS0   ISI_HSYNC  }
 	PA26 	{  SCK0   ISI_VSYNC  }
 	PA27 	{  PCK1   ISI_MCK  }
 	PA28 	{  SPI0_NPCS3A   ISI_D8  }
 	PA29 	{  TIOA0   ISI_D9  }
 	PA3 	{  MCI0_DA1   SPI0_NPCS1  }
 	PA30 	{  TIOB0   ISI_D10  }
 	PA31 	{  DMARQ1   ISI_D11  }
 	PA4 	{  MCI0_DA2   SPI0_NPCS2A  }
 	PA5 	{  MCI0_DA3   SPI0_NPCS0  }
 	PA6 	{  AC97FS  }
 	PA7 	{  AC97CK  }
 	PA8 	{  AC97TX  }
 	PA9 	{  AC97RX  }
 }

array set def_PIOB_att {
 	PB0 	{  TF0  }
 	PB1 	{  TK0  }
 	PB10 	{  RK1   PCK1  }
 	PB11 	{  RF1  }
 	PB12 	{  SPI1_MISO  }
 	PB13 	{  SPI1_MOSI  }
 	PB14 	{  SPI1_SPCK  }
 	PB15 	{  SPI1_NPCS0  }
 	PB16 	{  SPI1_NPCS1  }
 	PB17 	{  SPI1_NPCS2B   AD0  }
 	PB18 	{  SPI1_NPCS3B   AD1  }
 	PB19 	{  PWM0   AD2  }
 	PB2 	{  TD0  }
 	PB20 	{  PWM1   AD3  }
 	PB21 	{  E_TXCK   TIOA2  }
 	PB22 	{  E_RXDV   TIOB2  }
 	PB23 	{  E_TX0   PCK3  }
 	PB24 	{  E_TX1  }
 	PB25 	{  E_RX0  }
 	PB26 	{  E_RX1  }
 	PB27 	{  E_RXER  }
 	PB28 	{  E_TXEN   TCLK0  }
 	PB29 	{  E_MDC   PWM3  }
 	PB3 	{  RD0  }
 	PB30 	{  E_MDIO  }
 	PB31 	{  ADTRIG   E_F100  }
 	PB4 	{  RK0   TWD  }
 	PB5 	{  RF0   TWCK  }
 	PB6 	{  TF1   TIOA1  }
 	PB7 	{  TK1   TIOB1  }
 	PB8 	{  TD1   PWM2  }
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
 	PC20 	{  LCDD16   E_TX2  }
 	PC21 	{  LCDD17   E_TX3  }
 	PC22 	{  LCDD18   E_RX2  }
 	PC23 	{  LCDD19   E_RX3  }
 	PC24 	{  LCDD20   E_TXER  }
 	PC25 	{  LCDD21   E_CRS  }
 	PC26 	{  LCDD22   E_COL  }
 	PC27 	{  LCDD23   E_RXCK  }
 	PC28 	{  PWM0   TCLK1  }
 	PC29 	{  PCK0   PWM2  }
 	PC3 	{  LCDDEN   PWM1  }
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
 	PD10 	{  EBI_CFCE2   SCK1  }
 	PD11 	{  EBI_NCS2  }
 	PD12 	{  EBI_A23  }
 	PD13 	{  EBI_A24  }
 	PD14 	{  EBI_A25_CFRNW  }
 	PD15 	{  EBI_NCS3_NANDCS  }
 	PD16 	{  EBI_D16  }
 	PD17 	{  EBI_D17  }
 	PD18 	{  EBI_D18  }
 	PD19 	{  EBI_D19  }
 	PD2 	{  TXD2   SPI1_NPCS2D  }
 	PD20 	{  EBI_D20  }
 	PD21 	{  EBI_D21  }
 	PD22 	{  EBI_D22  }
 	PD23 	{  EBI_D23  }
 	PD24 	{  EBI_D24  }
 	PD25 	{  EBI_D25  }
 	PD26 	{  EBI_D26  }
 	PD27 	{  EBI_D27  }
 	PD28 	{  EBI_D28  }
 	PD29 	{  EBI_D29  }
 	PD3 	{  RXD2   SPI1_NPCS3D  }
 	PD30 	{  EBI_D30  }
 	PD31 	{  EBI_D31  }
 	PD4 	{  FIQ  }
 	PD5 	{  DMARQ2   RTS2  }
 	PD6 	{  EBI_NWAIT   CTS2  }
 	PD7 	{  EBI_NCS4_CFCS0   RTS1  }
 	PD8 	{  EBI_NCS5_CFCS1   CTS1  }
 	PD9 	{  EBI_CFCE1   SCK2  }
 }
