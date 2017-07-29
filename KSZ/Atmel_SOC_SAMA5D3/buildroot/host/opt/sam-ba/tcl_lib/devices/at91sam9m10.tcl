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
# File Name           : AT91SAM9264.tcl
# Object              : AT91SAM9264 definitions
# Generated           : AT91 SW Application Group  04/28/2008 (18:15:14)
# 
# CVS Reference       : /AT91SAM9264.pl/1.47/Wed Jan  2 11:35:59 2008//
# CVS Reference       : /SYS_SAM9264.pl/1.2/Fri Oct  5 09:08:21 2007//
# CVS Reference       : /HMATRIX2_SAM9264.pl/1.5/Thu Aug  9 13:21:11 2007//
# CVS Reference       : /CCR_SAM9264.pl/1.6/Wed Feb 13 13:27:21 2008//
# CVS Reference       : /PMC_SAM9264.pl/1.9/Wed Jan  2 11:36:06 2008//
# CVS Reference       : /HDDRSDRC2_6304B.pl/1.1/Thu Oct 11 10:44:49 2007//
# CVS Reference       : /EBI_SAM9260.pl/1.1/Fri Sep 30 12:12:14 2005//
# CVS Reference       : /HSMC3_SAM9264.pl/1.1/Wed Oct 10 09:39:31 2007//
# CVS Reference       : /HECC_6143A.pl/1.1/Wed Feb  9 17:16:57 2005//
# CVS Reference       : /SFR_SAM9264.pl/1.4/Thu Jan 17 16:52:02 2008//
# CVS Reference       : /AIC_6075A.pl/1.1/Mon Jul 12 17:04:01 2004//
# CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb  3 09:02:11 2005//
# CVS Reference       : /DBGU_6059D.pl/1.1/Mon Jan 31 13:54:41 2005//
# CVS Reference       : /PIO_SAM9264.pl/1.1/Wed Oct 10 09:38:26 2007//
# CVS Reference       : /RSTC_6098A.pl/1.3/Thu Nov  4 13:57:00 2004//
# CVS Reference       : /SHDWC_6122A.pl/1.3/Wed Oct  6 14:16:58 2004//
# CVS Reference       : /RTTC_6081A.pl/1.2/Thu Nov  4 13:57:22 2004//
# CVS Reference       : /PITC_6079A.pl/1.2/Thu Nov  4 13:56:22 2004//
# CVS Reference       : /WDTC_6080A.pl/1.3/Thu Nov  4 13:58:52 2004//
# CVS Reference       : /TC_6082A.pl/1.7/Wed Mar  9 16:31:51 2005//
# CVS Reference       : /MCI_6101F.pl/1.1/Tue Sep 11 16:25:38 2007//
# CVS Reference       : /TWI_6061B.pl/1.2/Fri Aug  4 08:53:02 2006//
# CVS Reference       : /US_6089J.pl/1.2/Wed Oct 11 13:26:02 2006//
# CVS Reference       : /SSC_6078B.pl/1.2/Thu Apr 17 13:55:44 2008//
# CVS Reference       : /SPI_6088D.pl/1.3/Fri May 20 14:23:02 2005//
# CVS Reference       : /AC97C_XXXX.pl/1.3/Tue Feb 22 17:08:27 2005//
# CVS Reference       : /PWM_6044D.pl/1.2/Tue May 10 12:39:09 2005//
# CVS Reference       : /LCDC_6063A.pl/1.3/Fri Dec  9 10:59:26 2005//
# CVS Reference       : /HDMA_SAM9264.pl/1.2/Mon Sep 17 12:01:17 2007//
# CVS Reference       : /UDPHS_SAM9_7ept6dma4iso.pl/1.3/Mon Apr 28 13:59:55 2008//
# CVS Reference       : /TSC_SAM9264.pl/1.1/Fri Jul 13 10:30:41 2007//
# CVS Reference       : /RTC_1245D.pl/1.3/Fri Sep 17 14:01:31 2004//
# CVS Reference       : /EMACB_SAM9264.pl/1.1/Tue Sep 25 12:07:23 2007//
# CVS Reference       : /uhphs_ohci.pl/1.1/Fri Jun 22 14:20:34 2007//
# CVS Reference       : /uhphs_ehci.pl/1.3/Tue Jul 17 07:50:29 2007//
# CVS Reference       : /VDEC_7190.pl/1.2/Fri Aug 31 15:21:50 2007//
# CVS Reference       : /ISI_SAM9264.pl/1.1/Tue Aug 14 10:20:03 2007//
# CVS Reference       : /AES_6149B.pl/1.1/Fri Oct 14 13:30:02 2005//
# CVS Reference       : /DES3_6150A.pl/1.1/Mon Jan 17 13:30:33 2005//
# CVS Reference       : /SHA_6156B.pl/1.1/Fri Jun 22 13:26:18 2007//
# CVS Reference       : /TRNG_xxxxx.pl/1.1/Wed Jul 18 12:02:58 2007//
# ----------------------------------------------------------------------------


# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR SPECIAL FUNCTION REGISTER
# *****************************************************************************
# -------- SFR_EMA : (SFR Offset: 0x0) memory Extra Margin Adjustment control register -------- 
set AT91C_SFR_RAM_EMA     [expr 0x7 <<  0 ]
set 	AT91C_SFR_RAM_EMA_0                    0x0
set 	AT91C_SFR_RAM_EMA_1                    0x1
set 	AT91C_SFR_RAM_EMA_2                    0x2
set 	AT91C_SFR_RAM_EMA_3                    0x3
set 	AT91C_SFR_RAM_EMA_4                    0x4
set 	AT91C_SFR_RAM_EMA_5                    0x5
set 	AT91C_SFR_RAM_EMA_6                    0x6
set 	AT91C_SFR_RAM_EMA_7                    0x7
set AT91C_SFR_DPRAM_EMA   [expr 0x7 <<  4 ]
set 	AT91C_SFR_DPRAM_EMA_0                    [expr 0x0 <<  4 ]
set 	AT91C_SFR_DPRAM_EMA_1                    [expr 0x1 <<  4 ]
set 	AT91C_SFR_DPRAM_EMA_2                    [expr 0x2 <<  4 ]
set 	AT91C_SFR_DPRAM_EMA_3                    [expr 0x3 <<  4 ]
set 	AT91C_SFR_DPRAM_EMA_4                    [expr 0x4 <<  4 ]
set 	AT91C_SFR_DPRAM_EMA_5                    [expr 0x5 <<  4 ]
set 	AT91C_SFR_DPRAM_EMA_6                    [expr 0x6 <<  4 ]
set 	AT91C_SFR_DPRAM_EMA_7                    [expr 0x7 <<  4 ]
set AT91C_SFR_RF_EMA      [expr 0x7 <<  8 ]
set 	AT91C_SFR_RF_EMA_0                    [expr 0x0 <<  8 ]
set 	AT91C_SFR_RF_EMA_1                    [expr 0x1 <<  8 ]
set 	AT91C_SFR_RF_EMA_2                    [expr 0x2 <<  8 ]
set 	AT91C_SFR_RF_EMA_3                    [expr 0x3 <<  8 ]
set 	AT91C_SFR_RF_EMA_4                    [expr 0x4 <<  8 ]
set 	AT91C_SFR_RF_EMA_5                    [expr 0x5 <<  8 ]
set 	AT91C_SFR_RF_EMA_6                    [expr 0x6 <<  8 ]
set 	AT91C_SFR_RF_EMA_7                    [expr 0x7 <<  8 ]
set AT91C_SFR_DPRF_EMA    [expr 0x7 << 12 ]
set 	AT91C_SFR_DPRF_EMA_0                    [expr 0x0 << 12 ]
set 	AT91C_SFR_DPRF_EMA_1                    [expr 0x1 << 12 ]
set 	AT91C_SFR_DPRF_EMA_2                    [expr 0x2 << 12 ]
set 	AT91C_SFR_DPRF_EMA_3                    [expr 0x3 << 12 ]
set 	AT91C_SFR_DPRF_EMA_4                    [expr 0x4 << 12 ]
set 	AT91C_SFR_DPRF_EMA_5                    [expr 0x5 << 12 ]
set 	AT91C_SFR_DPRF_EMA_6                    [expr 0x6 << 12 ]
set 	AT91C_SFR_DPRF_EMA_7                    [expr 0x7 << 12 ]
set AT91C_SFR_ROM_EMA     [expr 0x7 << 16 ]
set 	AT91C_SFR_ROM_EMA_0                    [expr 0x0 << 16 ]
set 	AT91C_SFR_ROM_EMA_1                    [expr 0x1 << 16 ]
set 	AT91C_SFR_ROM_EMA_2                    [expr 0x2 << 16 ]
set 	AT91C_SFR_ROM_EMA_3                    [expr 0x3 << 16 ]
set 	AT91C_SFR_ROM_EMA_4                    [expr 0x4 << 16 ]
set 	AT91C_SFR_ROM_EMA_5                    [expr 0x5 << 16 ]
set 	AT91C_SFR_ROM_EMA_6                    [expr 0x6 << 16 ]
set 	AT91C_SFR_ROM_EMA_7                    [expr 0x7 << 16 ]
# -------- SFR_DDRCFG : (SFR Offset: 0x4) DDR2 SSTL18 control register -------- 
set AT91C_SFR_DDRCFG_SSTL [expr 0x1 <<  0 ]
set 	AT91C_SFR_DDRCFG_SSTL_NORMAL               0x0
set 	AT91C_SFR_DDRCFG_SSTL_COMPATIBLE           0x1
set AT91C_SFR_DDRCFG_CLKDELAY [expr 0x1 <<  8 ]
set 	AT91C_SFR_DDRCFG_CLKDELAY_HARD                 [expr 0x0 <<  8 ]
set 	AT91C_SFR_DDRCFG_CLKDELAY_SOFT                 [expr 0x1 <<  8 ]
# -------- SFR_DDRDELAY : (SFR Offset: 0x8) DDR2 controller clock delay -------- 
set AT91C_SFR_DDRDELAY_CLK [expr 0xFF <<  0 ]
set 	AT91C_SFR_DDRDELAY_CLK_0                    0x0
set 	AT91C_SFR_DDRDELAY_CLK_1                    0x1
set 	AT91C_SFR_DDRDELAY_CLK_2                    0x2
set 	AT91C_SFR_DDRDELAY_CLK_3                    0x3
set 	AT91C_SFR_DDRDELAY_CLK_4                    0x4
set 	AT91C_SFR_DDRDELAY_CLK_5                    0x5
set 	AT91C_SFR_DDRDELAY_CLK_6                    0x6
set 	AT91C_SFR_DDRDELAY_CLK_7                    0x7
set 	AT91C_SFR_DDRDELAY_CLK_8                    0x8
set 	AT91C_SFR_DDRDELAY_CLK_9                    0x9
set 	AT91C_SFR_DDRDELAY_CLK_10                   0xA
set 	AT91C_SFR_DDRDELAY_CLK_11                   0xB
set 	AT91C_SFR_DDRDELAY_CLK_12                   0xC
set 	AT91C_SFR_DDRDELAY_CLK_13                   0xD
set 	AT91C_SFR_DDRDELAY_CLK_14                   0xE
set 	AT91C_SFR_DDRDELAY_CLK_15                   0xF
set 	AT91C_SFR_DDRDELAY_CLK_16                   0x10
set AT91C_SFR_DDRDELAY_DQS0 [expr 0xFF <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_0                    [expr 0x0 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_1                    [expr 0x1 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_2                    [expr 0x2 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_3                    [expr 0x3 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_4                    [expr 0x4 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_5                    [expr 0x5 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_6                    [expr 0x6 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_7                    [expr 0x7 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_8                    [expr 0x8 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_9                    [expr 0x9 <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_10                   [expr 0xA <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_11                   [expr 0xB <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_12                   [expr 0xC <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_13                   [expr 0xD <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_14                   [expr 0xE <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_15                   [expr 0xF <<  8 ]
set 	AT91C_SFR_DDRDELAY_DQS0_16                   [expr 0x10 <<  8 ]
set AT91C_SFR_DDRDELAY_DQS1 [expr 0xFF << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_0                    [expr 0x0 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_1                    [expr 0x1 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_2                    [expr 0x2 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_3                    [expr 0x3 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_4                    [expr 0x4 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_5                    [expr 0x5 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_6                    [expr 0x6 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_7                    [expr 0x7 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_8                    [expr 0x8 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_9                    [expr 0x9 << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_10                   [expr 0xA << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_11                   [expr 0xB << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_12                   [expr 0xC << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_13                   [expr 0xD << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_14                   [expr 0xE << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_15                   [expr 0xF << 16 ]
set 	AT91C_SFR_DDRDELAY_DQS1_16                   [expr 0x10 << 16 ]
# -------- SFR_EBIDELAY : (SFR Offset: 0xc) EBI DDR controller clock delay -------- 
set AT91C_SFR_EBIDELAY_CLK [expr 0xFF <<  0 ]
set 	AT91C_SFR_EBIDELAY_CLK_0                    0x0
set 	AT91C_SFR_EBIDELAY_CLK_1                    0x1
set 	AT91C_SFR_EBIDELAY_CLK_2                    0x2
set 	AT91C_SFR_EBIDELAY_CLK_3                    0x3
set 	AT91C_SFR_EBIDELAY_CLK_4                    0x4
set 	AT91C_SFR_EBIDELAY_CLK_5                    0x5
set 	AT91C_SFR_EBIDELAY_CLK_6                    0x6
set 	AT91C_SFR_EBIDELAY_CLK_7                    0x7
set 	AT91C_SFR_EBIDELAY_CLK_8                    0x8
set 	AT91C_SFR_EBIDELAY_CLK_9                    0x9
set 	AT91C_SFR_EBIDELAY_CLK_10                   0xA
set 	AT91C_SFR_EBIDELAY_CLK_11                   0xB
set 	AT91C_SFR_EBIDELAY_CLK_12                   0xC
set 	AT91C_SFR_EBIDELAY_CLK_13                   0xD
set 	AT91C_SFR_EBIDELAY_CLK_14                   0xE
set 	AT91C_SFR_EBIDELAY_CLK_15                   0xF
set 	AT91C_SFR_EBIDELAY_CLK_16                   0x10
set AT91C_SFR_EBIDELAY_DQS0 [expr 0xFF <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_0                    [expr 0x0 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_1                    [expr 0x1 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_2                    [expr 0x2 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_3                    [expr 0x3 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_4                    [expr 0x4 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_5                    [expr 0x5 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_6                    [expr 0x6 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_7                    [expr 0x7 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_8                    [expr 0x8 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_9                    [expr 0x9 <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_10                   [expr 0xA <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_11                   [expr 0xB <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_12                   [expr 0xC <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_13                   [expr 0xD <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_14                   [expr 0xE <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_15                   [expr 0xF <<  8 ]
set 	AT91C_SFR_EBIDELAY_DQS0_16                   [expr 0x10 <<  8 ]
set AT91C_SFR_EBIDELAY_DQS1 [expr 0xFF << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_0                    [expr 0x0 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_1                    [expr 0x1 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_2                    [expr 0x2 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_3                    [expr 0x3 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_4                    [expr 0x4 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_5                    [expr 0x5 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_6                    [expr 0x6 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_7                    [expr 0x7 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_8                    [expr 0x8 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_9                    [expr 0x9 << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_10                   [expr 0xA << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_11                   [expr 0xB << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_12                   [expr 0xC << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_13                   [expr 0xD << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_14                   [expr 0xE << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_15                   [expr 0xF << 16 ]
set 	AT91C_SFR_EBIDELAY_DQS1_16                   [expr 0x10 << 16 ]
# -------- SFR_UTMICFG : (SFR Offset: 0x10) UTMI Software Reset -------- 
set AT91C_SFR_UTMICFG_PORT0 [expr 0x1 <<  0 ]
set AT91C_SFR_UTMICFG_PORT1 [expr 0x1 <<  1 ]
set AT91C_SFR_UTMICFG_OHCI_SUSP_INT_ENABLE [expr 0x1 <<  2 ]
# -------- SFR_OHCI_SUSP_INT : (SFR Offset: 0x14) OHCI suspend Interrupt status -------- 
set AT91C_SFR_OHCI_SUSP_INT_STATUS [expr 0x3 <<  0 ]
set 	AT91C_SFR_OHCI_SUSP_INT_STATUS_PORT0                0x1
set 	AT91C_SFR_OHCI_SUSP_INT_STATUS_PORT1                0x2

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR System Peripherals
# *****************************************************************************
# -------- SLCKSEL : (SYS Offset: 0x3d50) Slow Clock Selection Register -------- 
set AT91C_SLCKSEL_RCEN    [expr 0x1 <<  0 ]
set AT91C_SLCKSEL_OSC32EN [expr 0x1 <<  1 ]
set AT91C_SLCKSEL_OSC32BYP [expr 0x1 <<  2 ]
set AT91C_SLCKSEL_OSCSEL  [expr 0x1 <<  3 ]
# -------- GPBR : (SYS Offset: 0x3d60) GPBR General Purpose Register -------- 
set AT91C_GPBR_GPRV       [expr 0x0 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR External Bus Interface
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR DDR2/SDRAM Controller
# *****************************************************************************
# -------- HDDRSDRC2_MR : (HDDRSDRC2 Offset: 0x0) Mode Register -------- 
set AT91C_DDRC2_MODE      [expr 0x7 <<  0 ]
set 	AT91C_DDRC2_MODE_NORMAL_CMD           0x0
set 	AT91C_DDRC2_MODE_NOP_CMD              0x1
set 	AT91C_DDRC2_MODE_PRCGALL_CMD          0x2
set 	AT91C_DDRC2_MODE_LMR_CMD              0x3
set 	AT91C_DDRC2_MODE_RFSH_CMD             0x4
set 	AT91C_DDRC2_MODE_EXT_LMR_CMD          0x5
set 	AT91C_DDRC2_MODE_DEEP_CMD             0x6
set 	AT91C_DDRC2_MODE_Reserved             0x7
# -------- HDDRSDRC2_RTR : (HDDRSDRC2 Offset: 0x4) Refresh Timer Register -------- 
set AT91C_DDRC2_COUNT     [expr 0xFFF <<  0 ]
# -------- HDDRSDRC2_CR : (HDDRSDRC2 Offset: 0x8) Configuration Register -------- 
set AT91C_DDRC2_NC        [expr 0x3 <<  0 ]
set 	AT91C_DDRC2_NC_DDR9_SDR8            0x0
set 	AT91C_DDRC2_NC_DDR10_SDR9           0x1
set 	AT91C_DDRC2_NC_DDR11_SDR10          0x2
set 	AT91C_DDRC2_NC_DDR12_SDR11          0x3
set AT91C_DDRC2_NR        [expr 0x3 <<  2 ]
set 	AT91C_DDRC2_NR_11                   [expr 0x0 <<  2 ]
set 	AT91C_DDRC2_NR_12                   [expr 0x1 <<  2 ]
set 	AT91C_DDRC2_NR_13                   [expr 0x2 <<  2 ]
set 	AT91C_DDRC2_NR_14                   [expr 0x3 <<  2 ]
set AT91C_DDRC2_CAS       [expr 0x7 <<  4 ]
set 	AT91C_DDRC2_CAS_2                    [expr 0x2 <<  4 ]
set 	AT91C_DDRC2_CAS_3                    [expr 0x3 <<  4 ]
set 	AT91C_DDRC2_CAS_4                    [expr 0x4 <<  4 ]
set 	AT91C_DDRC2_CAS_2_5                  [expr 0x6 <<  4 ]
set AT91C_DDRC2_DLL       [expr 0x1 <<  7 ]
set 	AT91C_DDRC2_DLL_RESET_DISABLED       [expr 0x0 <<  7 ]
set 	AT91C_DDRC2_DLL_RESET_ENABLED        [expr 0x1 <<  7 ]
set AT91C_DDRC2_DIC_DS    [expr 0x1 <<  8 ]
set AT91C_DDRC2_OCD       [expr 0x7 << 12 ]
set 	AT91C_DDRC2_OCD_EXIT                 [expr 0x0 << 12 ]
set 	AT91C_DDRC2_OCD_DEFAULT              [expr 0x7 << 12 ]
set AT91C_DDRC2_DQMS      [expr 0x1 << 16 ]
set 	AT91C_DDRC2_DQMS_NOT_SHARED           [expr 0x0 << 16 ]
set 	AT91C_DDRC2_DQMS_SHARED               [expr 0x1 << 16 ]
set AT91C_DDRC2_ENRDM     [expr 0x1 << 17 ]
set 	AT91C_DDRC2_ENRDM_OFF                  [expr 0x0 << 17 ]
set 	AT91C_DDRC2_ENRDM_ON                   [expr 0x1 << 17 ]
# -------- HDDRSDRC2_T0PR : (HDDRSDRC2 Offset: 0xc) Timing0 Register -------- 
set AT91C_DDRC2_TRAS      [expr 0xF <<  0 ]
set 	AT91C_DDRC2_TRAS_0                    0x0
set 	AT91C_DDRC2_TRAS_1                    0x1
set 	AT91C_DDRC2_TRAS_2                    0x2
set 	AT91C_DDRC2_TRAS_3                    0x3
set 	AT91C_DDRC2_TRAS_4                    0x4
set 	AT91C_DDRC2_TRAS_5                    0x5
set 	AT91C_DDRC2_TRAS_6                    0x6
set 	AT91C_DDRC2_TRAS_7                    0x7
set 	AT91C_DDRC2_TRAS_8                    0x8
set 	AT91C_DDRC2_TRAS_9                    0x9
set 	AT91C_DDRC2_TRAS_10                   0xA
set 	AT91C_DDRC2_TRAS_11                   0xB
set 	AT91C_DDRC2_TRAS_12                   0xC
set 	AT91C_DDRC2_TRAS_13                   0xD
set 	AT91C_DDRC2_TRAS_14                   0xE
set 	AT91C_DDRC2_TRAS_15                   0xF
set AT91C_DDRC2_TRCD      [expr 0xF <<  4 ]
set 	AT91C_DDRC2_TRCD_0                    [expr 0x0 <<  4 ]
set 	AT91C_DDRC2_TRCD_1                    [expr 0x1 <<  4 ]
set 	AT91C_DDRC2_TRCD_2                    [expr 0x2 <<  4 ]
set 	AT91C_DDRC2_TRCD_3                    [expr 0x3 <<  4 ]
set 	AT91C_DDRC2_TRCD_4                    [expr 0x4 <<  4 ]
set 	AT91C_DDRC2_TRCD_5                    [expr 0x5 <<  4 ]
set 	AT91C_DDRC2_TRCD_6                    [expr 0x6 <<  4 ]
set 	AT91C_DDRC2_TRCD_7                    [expr 0x7 <<  4 ]
set 	AT91C_DDRC2_TRCD_8                    [expr 0x8 <<  4 ]
set 	AT91C_DDRC2_TRCD_9                    [expr 0x9 <<  4 ]
set 	AT91C_DDRC2_TRCD_10                   [expr 0xA <<  4 ]
set 	AT91C_DDRC2_TRCD_11                   [expr 0xB <<  4 ]
set 	AT91C_DDRC2_TRCD_12                   [expr 0xC <<  4 ]
set 	AT91C_DDRC2_TRCD_13                   [expr 0xD <<  4 ]
set 	AT91C_DDRC2_TRCD_14                   [expr 0xE <<  4 ]
set 	AT91C_DDRC2_TRCD_15                   [expr 0xF <<  4 ]
set AT91C_DDRC2_TWR       [expr 0xF <<  8 ]
set 	AT91C_DDRC2_TWR_0                    [expr 0x0 <<  8 ]
set 	AT91C_DDRC2_TWR_1                    [expr 0x1 <<  8 ]
set 	AT91C_DDRC2_TWR_2                    [expr 0x2 <<  8 ]
set 	AT91C_DDRC2_TWR_3                    [expr 0x3 <<  8 ]
set 	AT91C_DDRC2_TWR_4                    [expr 0x4 <<  8 ]
set 	AT91C_DDRC2_TWR_5                    [expr 0x5 <<  8 ]
set 	AT91C_DDRC2_TWR_6                    [expr 0x6 <<  8 ]
set 	AT91C_DDRC2_TWR_7                    [expr 0x7 <<  8 ]
set 	AT91C_DDRC2_TWR_8                    [expr 0x8 <<  8 ]
set 	AT91C_DDRC2_TWR_9                    [expr 0x9 <<  8 ]
set 	AT91C_DDRC2_TWR_10                   [expr 0xA <<  8 ]
set 	AT91C_DDRC2_TWR_11                   [expr 0xB <<  8 ]
set 	AT91C_DDRC2_TWR_12                   [expr 0xC <<  8 ]
set 	AT91C_DDRC2_TWR_13                   [expr 0xD <<  8 ]
set 	AT91C_DDRC2_TWR_14                   [expr 0xE <<  8 ]
set 	AT91C_DDRC2_TWR_15                   [expr 0xF <<  8 ]
set AT91C_DDRC2_TRC       [expr 0xF << 12 ]
set 	AT91C_DDRC2_TRC_0                    [expr 0x0 << 12 ]
set 	AT91C_DDRC2_TRC_1                    [expr 0x1 << 12 ]
set 	AT91C_DDRC2_TRC_2                    [expr 0x2 << 12 ]
set 	AT91C_DDRC2_TRC_3                    [expr 0x3 << 12 ]
set 	AT91C_DDRC2_TRC_4                    [expr 0x4 << 12 ]
set 	AT91C_DDRC2_TRC_5                    [expr 0x5 << 12 ]
set 	AT91C_DDRC2_TRC_6                    [expr 0x6 << 12 ]
set 	AT91C_DDRC2_TRC_7                    [expr 0x7 << 12 ]
set 	AT91C_DDRC2_TRC_8                    [expr 0x8 << 12 ]
set 	AT91C_DDRC2_TRC_9                    [expr 0x9 << 12 ]
set 	AT91C_DDRC2_TRC_10                   [expr 0xA << 12 ]
set 	AT91C_DDRC2_TRC_11                   [expr 0xB << 12 ]
set 	AT91C_DDRC2_TRC_12                   [expr 0xC << 12 ]
set 	AT91C_DDRC2_TRC_13                   [expr 0xD << 12 ]
set 	AT91C_DDRC2_TRC_14                   [expr 0xE << 12 ]
set 	AT91C_DDRC2_TRC_15                   [expr 0xF << 12 ]
set AT91C_DDRC2_TRP       [expr 0xF << 16 ]
set 	AT91C_DDRC2_TRP_0                    [expr 0x0 << 16 ]
set 	AT91C_DDRC2_TRP_1                    [expr 0x1 << 16 ]
set 	AT91C_DDRC2_TRP_2                    [expr 0x2 << 16 ]
set 	AT91C_DDRC2_TRP_3                    [expr 0x3 << 16 ]
set 	AT91C_DDRC2_TRP_4                    [expr 0x4 << 16 ]
set 	AT91C_DDRC2_TRP_5                    [expr 0x5 << 16 ]
set 	AT91C_DDRC2_TRP_6                    [expr 0x6 << 16 ]
set 	AT91C_DDRC2_TRP_7                    [expr 0x7 << 16 ]
set 	AT91C_DDRC2_TRP_8                    [expr 0x8 << 16 ]
set 	AT91C_DDRC2_TRP_9                    [expr 0x9 << 16 ]
set 	AT91C_DDRC2_TRP_10                   [expr 0xA << 16 ]
set 	AT91C_DDRC2_TRP_11                   [expr 0xB << 16 ]
set 	AT91C_DDRC2_TRP_12                   [expr 0xC << 16 ]
set 	AT91C_DDRC2_TRP_13                   [expr 0xD << 16 ]
set 	AT91C_DDRC2_TRP_14                   [expr 0xE << 16 ]
set 	AT91C_DDRC2_TRP_15                   [expr 0xF << 16 ]
set AT91C_DDRC2_TRRD      [expr 0xF << 20 ]
set 	AT91C_DDRC2_TRRD_0                    [expr 0x0 << 20 ]
set 	AT91C_DDRC2_TRRD_1                    [expr 0x1 << 20 ]
set 	AT91C_DDRC2_TRRD_2                    [expr 0x2 << 20 ]
set 	AT91C_DDRC2_TRRD_3                    [expr 0x3 << 20 ]
set 	AT91C_DDRC2_TRRD_4                    [expr 0x4 << 20 ]
set 	AT91C_DDRC2_TRRD_5                    [expr 0x5 << 20 ]
set 	AT91C_DDRC2_TRRD_6                    [expr 0x6 << 20 ]
set 	AT91C_DDRC2_TRRD_7                    [expr 0x7 << 20 ]
set 	AT91C_DDRC2_TRRD_8                    [expr 0x8 << 20 ]
set 	AT91C_DDRC2_TRRD_9                    [expr 0x9 << 20 ]
set 	AT91C_DDRC2_TRRD_10                   [expr 0xA << 20 ]
set 	AT91C_DDRC2_TRRD_11                   [expr 0xB << 20 ]
set 	AT91C_DDRC2_TRRD_12                   [expr 0xC << 20 ]
set 	AT91C_DDRC2_TRRD_13                   [expr 0xD << 20 ]
set 	AT91C_DDRC2_TRRD_14                   [expr 0xE << 20 ]
set 	AT91C_DDRC2_TRRD_15                   [expr 0xF << 20 ]
set AT91C_DDRC2_TWTR      [expr 0x1 << 24 ]
set 	AT91C_DDRC2_TWTR_0                    [expr 0x0 << 24 ]
set 	AT91C_DDRC2_TWTR_1                    [expr 0x1 << 24 ]
set AT91C_DDRC2_TMRD      [expr 0xF << 28 ]
set 	AT91C_DDRC2_TMRD_0                    [expr 0x0 << 28 ]
set 	AT91C_DDRC2_TMRD_1                    [expr 0x1 << 28 ]
set 	AT91C_DDRC2_TMRD_2                    [expr 0x2 << 28 ]
set 	AT91C_DDRC2_TMRD_3                    [expr 0x3 << 28 ]
set 	AT91C_DDRC2_TMRD_4                    [expr 0x4 << 28 ]
set 	AT91C_DDRC2_TMRD_5                    [expr 0x5 << 28 ]
set 	AT91C_DDRC2_TMRD_6                    [expr 0x6 << 28 ]
set 	AT91C_DDRC2_TMRD_7                    [expr 0x7 << 28 ]
set 	AT91C_DDRC2_TMRD_8                    [expr 0x8 << 28 ]
set 	AT91C_DDRC2_TMRD_9                    [expr 0x9 << 28 ]
set 	AT91C_DDRC2_TMRD_10                   [expr 0xA << 28 ]
set 	AT91C_DDRC2_TMRD_11                   [expr 0xB << 28 ]
set 	AT91C_DDRC2_TMRD_12                   [expr 0xC << 28 ]
set 	AT91C_DDRC2_TMRD_13                   [expr 0xD << 28 ]
set 	AT91C_DDRC2_TMRD_14                   [expr 0xE << 28 ]
set 	AT91C_DDRC2_TMRD_15                   [expr 0xF << 28 ]
# -------- HDDRSDRC2_T1PR : (HDDRSDRC2 Offset: 0x10) Timing1 Register -------- 
set AT91C_DDRC2_TRFC      [expr 0x1F <<  0 ]
set 	AT91C_DDRC2_TRFC_0                    0x0
set 	AT91C_DDRC2_TRFC_1                    0x1
set 	AT91C_DDRC2_TRFC_2                    0x2
set 	AT91C_DDRC2_TRFC_3                    0x3
set 	AT91C_DDRC2_TRFC_4                    0x4
set 	AT91C_DDRC2_TRFC_5                    0x5
set 	AT91C_DDRC2_TRFC_6                    0x6
set 	AT91C_DDRC2_TRFC_7                    0x7
set 	AT91C_DDRC2_TRFC_8                    0x8
set 	AT91C_DDRC2_TRFC_9                    0x9
set 	AT91C_DDRC2_TRFC_10                   0xA
set 	AT91C_DDRC2_TRFC_11                   0xB
set 	AT91C_DDRC2_TRFC_12                   0xC
set 	AT91C_DDRC2_TRFC_13                   0xD
set 	AT91C_DDRC2_TRFC_14                   0xE
set 	AT91C_DDRC2_TRFC_15                   0xF
set 	AT91C_DDRC2_TRFC_16                   0x10
set 	AT91C_DDRC2_TRFC_17                   0x11
set 	AT91C_DDRC2_TRFC_18                   0x12
set 	AT91C_DDRC2_TRFC_19                   0x13
set 	AT91C_DDRC2_TRFC_20                   0x14
set 	AT91C_DDRC2_TRFC_21                   0x15
set 	AT91C_DDRC2_TRFC_22                   0x16
set 	AT91C_DDRC2_TRFC_23                   0x17
set 	AT91C_DDRC2_TRFC_24                   0x18
set 	AT91C_DDRC2_TRFC_25                   0x19
set 	AT91C_DDRC2_TRFC_26                   0x1A
set 	AT91C_DDRC2_TRFC_27                   0x1B
set 	AT91C_DDRC2_TRFC_28                   0x1C
set 	AT91C_DDRC2_TRFC_29                   0x1D
set 	AT91C_DDRC2_TRFC_30                   0x1E
set 	AT91C_DDRC2_TRFC_31                   0x1F
set AT91C_DDRC2_TXSNR     [expr 0xFF <<  8 ]
set 	AT91C_DDRC2_TXSNR_0                    [expr 0x0 <<  8 ]
set 	AT91C_DDRC2_TXSNR_8                    [expr 0x8 <<  8 ]
set 	AT91C_DDRC2_TXSNR_16                   [expr 0x10 <<  8 ]
set 	AT91C_DDRC2_TXSNR_32                   [expr 0x20 <<  8 ]
set 	AT91C_DDRC2_TXSNR_48                   [expr 0x30 <<  8 ]
set 	AT91C_DDRC2_TXSNR_64                   [expr 0x40 <<  8 ]
set 	AT91C_DDRC2_TXSNR_80                   [expr 0x50 <<  8 ]
set 	AT91C_DDRC2_TXSNR_96                   [expr 0x60 <<  8 ]
set 	AT91C_DDRC2_TXSNR_112                  [expr 0x70 <<  8 ]
set 	AT91C_DDRC2_TXSNR_128                  [expr 0x80 <<  8 ]
set 	AT91C_DDRC2_TXSNR_144                  [expr 0x90 <<  8 ]
set 	AT91C_DDRC2_TXSNR_160                  [expr 0xA0 <<  8 ]
set 	AT91C_DDRC2_TXSNR_176                  [expr 0xB0 <<  8 ]
set 	AT91C_DDRC2_TXSNR_192                  [expr 0xC0 <<  8 ]
set 	AT91C_DDRC2_TXSNR_208                  [expr 0xD0 <<  8 ]
set 	AT91C_DDRC2_TXSNR_224                  [expr 0xE0 <<  8 ]
set 	AT91C_DDRC2_TXSNR_240                  [expr 0xF0 <<  8 ]
set 	AT91C_DDRC2_TXSNR_255                  [expr 0xFF <<  8 ]
set AT91C_DDRC2_TXSRD     [expr 0xFF << 16 ]
set 	AT91C_DDRC2_TXSRD_0                    [expr 0x0 << 16 ]
set 	AT91C_DDRC2_TXSRD_8                    [expr 0x8 << 16 ]
set 	AT91C_DDRC2_TXSRD_16                   [expr 0x10 << 16 ]
set 	AT91C_DDRC2_TXSRD_32                   [expr 0x20 << 16 ]
set 	AT91C_DDRC2_TXSRD_48                   [expr 0x30 << 16 ]
set 	AT91C_DDRC2_TXSRD_64                   [expr 0x40 << 16 ]
set 	AT91C_DDRC2_TXSRD_80                   [expr 0x50 << 16 ]
set 	AT91C_DDRC2_TXSRD_96                   [expr 0x60 << 16 ]
set 	AT91C_DDRC2_TXSRD_112                  [expr 0x70 << 16 ]
set 	AT91C_DDRC2_TXSRD_128                  [expr 0x80 << 16 ]
set 	AT91C_DDRC2_TXSRD_144                  [expr 0x90 << 16 ]
set 	AT91C_DDRC2_TXSRD_160                  [expr 0xA0 << 16 ]
set 	AT91C_DDRC2_TXSRD_176                  [expr 0xB0 << 16 ]
set 	AT91C_DDRC2_TXSRD_192                  [expr 0xC0 << 16 ]
set 	AT91C_DDRC2_TXSRD_208                  [expr 0xD0 << 16 ]
set 	AT91C_DDRC2_TXSRD_224                  [expr 0xE0 << 16 ]
set 	AT91C_DDRC2_TXSRD_240                  [expr 0xF0 << 16 ]
set 	AT91C_DDRC2_TXSRD_255                  [expr 0xFF << 16 ]
set AT91C_DDRC2_TXP       [expr 0xF << 24 ]
set 	AT91C_DDRC2_TXP_0                    [expr 0x0 << 24 ]
set 	AT91C_DDRC2_TXP_1                    [expr 0x1 << 24 ]
set 	AT91C_DDRC2_TXP_2                    [expr 0x2 << 24 ]
set 	AT91C_DDRC2_TXP_3                    [expr 0x3 << 24 ]
set 	AT91C_DDRC2_TXP_4                    [expr 0x4 << 24 ]
set 	AT91C_DDRC2_TXP_5                    [expr 0x5 << 24 ]
set 	AT91C_DDRC2_TXP_6                    [expr 0x6 << 24 ]
set 	AT91C_DDRC2_TXP_7                    [expr 0x7 << 24 ]
set 	AT91C_DDRC2_TXP_8                    [expr 0x8 << 24 ]
set 	AT91C_DDRC2_TXP_9                    [expr 0x9 << 24 ]
set 	AT91C_DDRC2_TXP_10                   [expr 0xA << 24 ]
set 	AT91C_DDRC2_TXP_11                   [expr 0xB << 24 ]
set 	AT91C_DDRC2_TXP_12                   [expr 0xC << 24 ]
set 	AT91C_DDRC2_TXP_13                   [expr 0xD << 24 ]
set 	AT91C_DDRC2_TXP_14                   [expr 0xE << 24 ]
set 	AT91C_DDRC2_TXP_15                   [expr 0xF << 24 ]
# -------- HDDRSDRC2_T2PR : (HDDRSDRC2 Offset: 0x14) Timing2 Register -------- 
set AT91C_DDRC2_TXARD     [expr 0xF <<  0 ]
set 	AT91C_DDRC2_TXARD_0                    0x0
set 	AT91C_DDRC2_TXARD_1                    0x1
set 	AT91C_DDRC2_TXARD_2                    0x2
set 	AT91C_DDRC2_TXARD_3                    0x3
set 	AT91C_DDRC2_TXARD_4                    0x4
set 	AT91C_DDRC2_TXARD_5                    0x5
set 	AT91C_DDRC2_TXARD_6                    0x6
set 	AT91C_DDRC2_TXARD_7                    0x7
set 	AT91C_DDRC2_TXARD_8                    0x8
set 	AT91C_DDRC2_TXARD_9                    0x9
set 	AT91C_DDRC2_TXARD_10                   0xA
set 	AT91C_DDRC2_TXARD_11                   0xB
set 	AT91C_DDRC2_TXARD_12                   0xC
set 	AT91C_DDRC2_TXARD_13                   0xD
set 	AT91C_DDRC2_TXARD_14                   0xE
set 	AT91C_DDRC2_TXARD_15                   0xF
set AT91C_DDRC2_TXARDS    [expr 0xF <<  8 ]
set 	AT91C_DDRC2_TXARDS_0                    [expr 0x0 <<  8 ]
set 	AT91C_DDRC2_TXARDS_1                    [expr 0x1 <<  8 ]
set 	AT91C_DDRC2_TXARDS_2                    [expr 0x2 <<  8 ]
set 	AT91C_DDRC2_TXARDS_3                    [expr 0x3 <<  8 ]
set 	AT91C_DDRC2_TXARDS_4                    [expr 0x4 <<  8 ]
set 	AT91C_DDRC2_TXARDS_5                    [expr 0x5 <<  8 ]
set 	AT91C_DDRC2_TXARDS_6                    [expr 0x6 <<  8 ]
set 	AT91C_DDRC2_TXARDS_7                    [expr 0x7 <<  8 ]
set 	AT91C_DDRC2_TXARDS_8                    [expr 0x8 <<  8 ]
set 	AT91C_DDRC2_TXARDS_9                    [expr 0x9 <<  8 ]
set 	AT91C_DDRC2_TXARDS_10                   [expr 0xA <<  8 ]
set 	AT91C_DDRC2_TXARDS_11                   [expr 0xB <<  8 ]
set 	AT91C_DDRC2_TXARDS_12                   [expr 0xC <<  8 ]
set 	AT91C_DDRC2_TXARDS_13                   [expr 0xD <<  8 ]
set 	AT91C_DDRC2_TXARDS_14                   [expr 0xE <<  8 ]
set 	AT91C_DDRC2_TXARDS_15                   [expr 0xF <<  8 ]
set AT91C_DDRC2_TRPA      [expr 0xF << 16 ]
set 	AT91C_DDRC2_TRPA_0                    [expr 0x0 << 16 ]
set 	AT91C_DDRC2_TRPA_1                    [expr 0x1 << 16 ]
set 	AT91C_DDRC2_TRPA_2                    [expr 0x2 << 16 ]
set 	AT91C_DDRC2_TRPA_3                    [expr 0x3 << 16 ]
set 	AT91C_DDRC2_TRPA_4                    [expr 0x4 << 16 ]
set 	AT91C_DDRC2_TRPA_5                    [expr 0x5 << 16 ]
set 	AT91C_DDRC2_TRPA_6                    [expr 0x6 << 16 ]
set 	AT91C_DDRC2_TRPA_7                    [expr 0x7 << 16 ]
set 	AT91C_DDRC2_TRPA_8                    [expr 0x8 << 16 ]
set 	AT91C_DDRC2_TRPA_9                    [expr 0x9 << 16 ]
set 	AT91C_DDRC2_TRPA_10                   [expr 0xA << 16 ]
set 	AT91C_DDRC2_TRPA_11                   [expr 0xB << 16 ]
set 	AT91C_DDRC2_TRPA_12                   [expr 0xC << 16 ]
set 	AT91C_DDRC2_TRPA_13                   [expr 0xD << 16 ]
set 	AT91C_DDRC2_TRPA_14                   [expr 0xE << 16 ]
set 	AT91C_DDRC2_TRPA_15                   [expr 0xF << 16 ]
set AT91C_DDRC2_TRTP      [expr 0xF << 24 ]
set 	AT91C_DDRC2_TRTP_0                    [expr 0x0 << 24 ]
set 	AT91C_DDRC2_TRTP_1                    [expr 0x1 << 24 ]
set 	AT91C_DDRC2_TRTP_2                    [expr 0x2 << 24 ]
set 	AT91C_DDRC2_TRTP_3                    [expr 0x3 << 24 ]
set 	AT91C_DDRC2_TRTP_4                    [expr 0x4 << 24 ]
set 	AT91C_DDRC2_TRTP_5                    [expr 0x5 << 24 ]
set 	AT91C_DDRC2_TRTP_6                    [expr 0x6 << 24 ]
set 	AT91C_DDRC2_TRTP_7                    [expr 0x7 << 24 ]
set 	AT91C_DDRC2_TRTP_8                    [expr 0x8 << 24 ]
set 	AT91C_DDRC2_TRTP_9                    [expr 0x9 << 24 ]
set 	AT91C_DDRC2_TRTP_10                   [expr 0xA << 24 ]
set 	AT91C_DDRC2_TRTP_11                   [expr 0xB << 24 ]
set 	AT91C_DDRC2_TRTP_12                   [expr 0xC << 24 ]
set 	AT91C_DDRC2_TRTP_13                   [expr 0xD << 24 ]
set 	AT91C_DDRC2_TRTP_14                   [expr 0xE << 24 ]
set 	AT91C_DDRC2_TRTP_15                   [expr 0xF << 24 ]
# -------- HDDRSDRC2_T3PR : (HDDRSDRC2 Offset: 0x18) Timing3 Register -------- 
set AT91C_DDRC2_TANPD     [expr 0xF <<  0 ]
set 	AT91C_DDRC2_TANPD_0                    0x0
set 	AT91C_DDRC2_TANPD_1                    0x1
set 	AT91C_DDRC2_TANPD_2                    0x2
set 	AT91C_DDRC2_TANPD_3                    0x3
set 	AT91C_DDRC2_TANPD_4                    0x4
set 	AT91C_DDRC2_TANPD_5                    0x5
set 	AT91C_DDRC2_TANPD_6                    0x6
set 	AT91C_DDRC2_TANPD_7                    0x7
set 	AT91C_DDRC2_TANPD_8                    0x8
set 	AT91C_DDRC2_TANPD_9                    0x9
set 	AT91C_DDRC2_TANPD_10                   0xA
set 	AT91C_DDRC2_TANPD_11                   0xB
set 	AT91C_DDRC2_TANPD_12                   0xC
set 	AT91C_DDRC2_TANPD_13                   0xD
set 	AT91C_DDRC2_TANPD_14                   0xE
set 	AT91C_DDRC2_TANPD_15                   0xF
set AT91C_DDRC2_TAXPD     [expr 0xF <<  4 ]
set 	AT91C_DDRC2_TAXPD_0                    [expr 0x0 <<  4 ]
set 	AT91C_DDRC2_TAXPD_1                    [expr 0x1 <<  4 ]
set 	AT91C_DDRC2_TAXPD_2                    [expr 0x2 <<  4 ]
set 	AT91C_DDRC2_TAXPD_3                    [expr 0x3 <<  4 ]
set 	AT91C_DDRC2_TAXPD_4                    [expr 0x4 <<  4 ]
set 	AT91C_DDRC2_TAXPD_5                    [expr 0x5 <<  4 ]
set 	AT91C_DDRC2_TAXPD_6                    [expr 0x6 <<  4 ]
set 	AT91C_DDRC2_TAXPD_7                    [expr 0x7 <<  4 ]
set 	AT91C_DDRC2_TAXPD_8                    [expr 0x8 <<  4 ]
set 	AT91C_DDRC2_TAXPD_9                    [expr 0x9 <<  4 ]
set 	AT91C_DDRC2_TAXPD_10                   [expr 0xA <<  4 ]
set 	AT91C_DDRC2_TAXPD_11                   [expr 0xB <<  4 ]
set 	AT91C_DDRC2_TAXPD_12                   [expr 0xC <<  4 ]
set 	AT91C_DDRC2_TAXPD_13                   [expr 0xD <<  4 ]
set 	AT91C_DDRC2_TAXPD_14                   [expr 0xE <<  4 ]
set 	AT91C_DDRC2_TAXPD_15                   [expr 0xF <<  4 ]
set AT91C_DDRC2_TAOFPD    [expr 0xF <<  8 ]
set 	AT91C_DDRC2_TAOFPD_0                    [expr 0x0 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_1                    [expr 0x1 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_2                    [expr 0x2 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_3                    [expr 0x3 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_4                    [expr 0x4 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_5                    [expr 0x5 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_6                    [expr 0x6 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_7                    [expr 0x7 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_8                    [expr 0x8 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_9                    [expr 0x9 <<  8 ]
set 	AT91C_DDRC2_TAOFPD_10                   [expr 0xA <<  8 ]
set 	AT91C_DDRC2_TAOFPD_11                   [expr 0xB <<  8 ]
set 	AT91C_DDRC2_TAOFPD_12                   [expr 0xC <<  8 ]
set 	AT91C_DDRC2_TAOFPD_13                   [expr 0xD <<  8 ]
set 	AT91C_DDRC2_TAOFPD_14                   [expr 0xE <<  8 ]
set 	AT91C_DDRC2_TAOFPD_15                   [expr 0xF <<  8 ]
set AT91C_DDRC2_TAOFD     [expr 0xF << 12 ]
set 	AT91C_DDRC2_TAOFD_0                    [expr 0x0 << 12 ]
set 	AT91C_DDRC2_TAOFD_1                    [expr 0x1 << 12 ]
set 	AT91C_DDRC2_TAOFD_2                    [expr 0x2 << 12 ]
set 	AT91C_DDRC2_TAOFD_3                    [expr 0x3 << 12 ]
set 	AT91C_DDRC2_TAOFD_4                    [expr 0x4 << 12 ]
set 	AT91C_DDRC2_TAOFD_5                    [expr 0x5 << 12 ]
set 	AT91C_DDRC2_TAOFD_6                    [expr 0x6 << 12 ]
set 	AT91C_DDRC2_TAOFD_7                    [expr 0x7 << 12 ]
set 	AT91C_DDRC2_TAOFD_8                    [expr 0x8 << 12 ]
set 	AT91C_DDRC2_TAOFD_9                    [expr 0x9 << 12 ]
set 	AT91C_DDRC2_TAOFD_10                   [expr 0xA << 12 ]
set 	AT91C_DDRC2_TAOFD_11                   [expr 0xB << 12 ]
set 	AT91C_DDRC2_TAOFD_12                   [expr 0xC << 12 ]
set 	AT91C_DDRC2_TAOFD_13                   [expr 0xD << 12 ]
set 	AT91C_DDRC2_TAOFD_14                   [expr 0xE << 12 ]
set 	AT91C_DDRC2_TAOFD_15                   [expr 0xF << 12 ]
set AT91C_DDRC2_TAONPD    [expr 0xF << 16 ]
set 	AT91C_DDRC2_TAONPD_0                    [expr 0x0 << 16 ]
set 	AT91C_DDRC2_TAONPD_1                    [expr 0x1 << 16 ]
set 	AT91C_DDRC2_TAONPD_2                    [expr 0x2 << 16 ]
set 	AT91C_DDRC2_TAONPD_3                    [expr 0x3 << 16 ]
set 	AT91C_DDRC2_TAONPD_4                    [expr 0x4 << 16 ]
set 	AT91C_DDRC2_TAONPD_5                    [expr 0x5 << 16 ]
set 	AT91C_DDRC2_TAONPD_6                    [expr 0x6 << 16 ]
set 	AT91C_DDRC2_TAONPD_7                    [expr 0x7 << 16 ]
set 	AT91C_DDRC2_TAONPD_8                    [expr 0x8 << 16 ]
set 	AT91C_DDRC2_TAONPD_9                    [expr 0x9 << 16 ]
set 	AT91C_DDRC2_TAONPD_10                   [expr 0xA << 16 ]
set 	AT91C_DDRC2_TAONPD_11                   [expr 0xB << 16 ]
set 	AT91C_DDRC2_TAONPD_12                   [expr 0xC << 16 ]
set 	AT91C_DDRC2_TAONPD_13                   [expr 0xD << 16 ]
set 	AT91C_DDRC2_TAONPD_14                   [expr 0xE << 16 ]
set 	AT91C_DDRC2_TAONPD_15                   [expr 0xF << 16 ]
# -------- HDDRSDRC2_LPR : (HDDRSDRC2 Offset: 0x1c)  -------- 
set AT91C_DDRC2_LPCB      [expr 0x3 <<  0 ]
set 	AT91C_DDRC2_LPCB_DISABLED             0x0
set 	AT91C_DDRC2_LPCB_SELFREFRESH          0x1
set 	AT91C_DDRC2_LPCB_POWERDOWN            0x2
set 	AT91C_DDRC2_LPCB_DEEP_PWD             0x3
set AT91C_DDRC2_CLK_FR    [expr 0x1 <<  2 ]
set 	AT91C_DDRC2_CLK_FR_DISABLED             [expr 0x0 <<  2 ]
set 	AT91C_DDRC2_CLK_FR_SELFREFRESH          [expr 0x1 <<  2 ]
set 	AT91C_DDRC2_CLK_FR_POWERDOWN            [expr 0x2 <<  2 ]
set 	AT91C_DDRC2_CLK_FR_DEEP_PWD             [expr 0x3 <<  2 ]
set AT91C_DDRC2_PASR      [expr 0x7 <<  4 ]
set AT91C_                [expr 0x0 <<  8 ]
set AT91C_DDRC2_DS        [expr 0x3 << 10 ]
set AT91C_DDRC2_TIMEOUT   [expr 0x3 << 12 ]
set 	AT91C_DDRC2_TIMEOUT_0                    [expr 0x0 << 12 ]
set 	AT91C_DDRC2_TIMEOUT_64                   [expr 0x1 << 12 ]
set 	AT91C_DDRC2_TIMEOUT_128                  [expr 0x2 << 12 ]
set 	AT91C_DDRC2_TIMEOUT_Reserved             [expr 0x3 << 12 ]
set AT91C_DDRC2_ADPE      [expr 0x1 << 16 ]
set 	AT91C_DDRC2_ADPE_FAST                 [expr 0x0 << 16 ]
set 	AT91C_DDRC2_ADPE_SLOW                 [expr 0x1 << 16 ]
# -------- HDDRSDRC2_MDR : (HDDRSDRC2 Offset: 0x20) Memory Device Register -------- 
set AT91C_DDRC2_MD        [expr 0x7 <<  0 ]
set 	AT91C_DDRC2_MD_SDR_SDRAM            0x0
set 	AT91C_DDRC2_MD_LP_SDR_SDRAM         0x1
set 	AT91C_DDRC2_MD_DDR_SDRAM            0x2
set 	AT91C_DDRC2_MD_LP_DDR_SDRAM         0x3
set 	AT91C_DDRC2_MD_DDR2_SDRAM           0x6
set AT91C_DDRC2_DBW       [expr 0x1 <<  4 ]
set 	AT91C_DDRC2_DBW_32_BITS              [expr 0x0 <<  4 ]
set 	AT91C_DDRC2_DBW_16_BITS              [expr 0x1 <<  4 ]
# -------- HDDRSDRC2_DLL : (HDDRSDRC2 Offset: 0x24) DLL Information Register -------- 
set AT91C_DDRC2_MDINC     [expr 0x1 <<  0 ]
set AT91C_DDRC2_MDDEC     [expr 0x1 <<  1 ]
set AT91C_DDRC2_MDOVF     [expr 0x1 <<  2 ]
set AT91C_DDRC2_SDCOVF    [expr 0x1 <<  3 ]
set AT91C_DDRC2_SDCUDF    [expr 0x1 <<  4 ]
set AT91C_DDRC2_SDERF     [expr 0x1 <<  5 ]
set AT91C_DDRC2_MDVAL     [expr 0xFF <<  8 ]
set AT91C_DDRC2_SDVAL     [expr 0xFF << 16 ]
set AT91C_DDRC2_SDCVAL    [expr 0xFF << 24 ]
# -------- HDDRSDRC2_HS : (HDDRSDRC2 Offset: 0x2c) High Speed Register -------- 
set AT91C_DDRC2_DA        [expr 0x1 <<  0 ]
set AT91C_DDRC2_NO_OPT    [expr 0x1 <<  1 ]
set AT91C_DDRC2_NO_ANT    [expr 0x1 <<  2 ]
set AT91C_DDRC2_RES_DQS   [expr 0x1 <<  3 ]
# -------- HDDRSDRC2_DELAY1 : (HDDRSDRC2 Offset: 0x30) Pad delay1 Register -------- 
set AT91C_DDRC2_DELAY     [expr 0xF <<  0 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  4 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  8 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 12 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 16 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 20 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 24 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 28 ]
# -------- HDDRSDRC2_DELAY2 : (HDDRSDRC2 Offset: 0x34) Pad delay2 Register -------- 
set AT91C_DDRC2_DELAY     [expr 0xF <<  0 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  4 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  8 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 12 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 16 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 20 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 24 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 28 ]
# -------- HDDRSDRC2_DELAY3 : (HDDRSDRC2 Offset: 0x38) Pad delay3 Register -------- 
set AT91C_DDRC2_DELAY     [expr 0xF <<  0 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  4 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  8 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 12 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 16 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 20 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 24 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 28 ]
# -------- HDDRSDRC2_DELAY4 : (HDDRSDRC2 Offset: 0x3c) Pad delay4 Register -------- 
set AT91C_DDRC2_DELAY     [expr 0xF <<  0 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  4 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  8 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 12 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 16 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 20 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 24 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 28 ]
# -------- HDDRSDRC2_DELAY5 : (HDDRSDRC2 Offset: 0x40) Pad delay5 Register -------- 
set AT91C_DDRC2_DELAY     [expr 0xF <<  0 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  4 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  8 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 12 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 16 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 20 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 24 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 28 ]
# -------- HDDRSDRC2_DELAY6 : (HDDRSDRC2 Offset: 0x44) Pad delay6 Register -------- 
set AT91C_DDRC2_DELAY     [expr 0xF <<  0 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  4 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  8 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 12 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 16 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 20 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 24 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 28 ]
# -------- HDDRSDRC2_DELAY7 : (HDDRSDRC2 Offset: 0x48) Pad delay7 Register -------- 
set AT91C_DDRC2_DELAY     [expr 0xF <<  0 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  4 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  8 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 12 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 16 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 20 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 24 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 28 ]
# -------- HDDRSDRC2_DELAY8 : (HDDRSDRC2 Offset: 0x4c) Pad delay8 Register -------- 
set AT91C_DDRC2_DELAY     [expr 0xF <<  0 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  4 ]
set AT91C_DDRC2_DELAY     [expr 0xF <<  8 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 12 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 16 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 20 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 24 ]
set AT91C_DDRC2_DELAY     [expr 0xF << 28 ]
# -------- HDDRSDRC2_WPCR : (HDDRSDRC2 Offset: 0xe4) Write Protect Control Register -------- 
set AT91C_DDRC2_WPEN      [expr 0x1 <<  0 ]
set AT91C_DDRC2_WPKEY     [expr 0xFFFFFF <<  8 ]
# -------- HDDRSDRC2_WPSR : (HDDRSDRC2 Offset: 0xe8) Write Protect Status Register -------- 
set AT91C_DDRC2_WPVS      [expr 0x1 <<  0 ]
set AT91C_DDRC2_WPSRC     [expr 0xFFFF <<  8 ]

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
# -------- MATRIX_MCFG0 : (MATRIX Offset: 0x0) Master Configuration Register ARM-I -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG1 : (MATRIX Offset: 0x4) Master Configuration Register ARM-D -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG2 : (MATRIX Offset: 0x8) Master Configuration Register PDC -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG3 : (MATRIX Offset: 0xc) Master Configuration Register USB Host OHCI -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG4 : (MATRIX Offset: 0x10) Master Configuration Register DMA0 -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG5 : (MATRIX Offset: 0x14) Master Configuration Register DMA1 -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG6 : (MATRIX Offset: 0x18) Master Configuration Register HISI -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG7 : (MATRIX Offset: 0x1c) Master Configuration Register LCD -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG8 : (MATRIX Offset: 0x20) Master Configuration Register EMAC -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG9 : (MATRIX Offset: 0x24) Master Configuration Register USB Device -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG10 : (MATRIX Offset: 0x28) Master Configuration Register USB Host EHCI -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_MCFG11 : (MATRIX Offset: 0x2c) Master Configuration Register Video Decoder -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
# -------- MATRIX_SCFG0 : (MATRIX Offset: 0x40) Slave Configuration Register 0 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR0 [expr 0xF << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_UHPHS_OHCI           [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA0                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA1                 [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_ISI                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_EMAC                 [expr 0x8 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_UDPHS                [expr 0x9 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR0_UHPHS_EHCI           [expr 0xA << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG1 : (MATRIX Offset: 0x44) Slave Configuration Register 1 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR1 [expr 0xF << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_ISI                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR1_UDPHS                [expr 0x9 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG2 : (MATRIX Offset: 0x48) Slave Configuration Register 2 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR2 [expr 0xF << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR2_VDEC                 [expr 0xB << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG3 : (MATRIX Offset: 0x4c) Slave Configuration Register 3 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR3 [expr 0xF << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR3_LCD                  [expr 0x7 << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG4 : (MATRIX Offset: 0x50) Slave Configuration Register 4 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR4 [expr 0xF << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_UHPHS_OHCI           [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_DMA0                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_DMA1                 [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_ISI                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_EMAC                 [expr 0x8 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_UDPHS                [expr 0x9 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR4_UHPHS_EHCI           [expr 0xA << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG5 : (MATRIX Offset: 0x54) Slave Configuration Register 5 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR5 [expr 0xF << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_UHPHS_OHCI           [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_DMA0                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_DMA1                 [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_ISI                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_EMAC                 [expr 0x8 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_UDPHS                [expr 0x9 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR5_UHPHS_EHCI           [expr 0xA << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG6 : (MATRIX Offset: 0x58) Slave Configuration Register 6 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR6 [expr 0xF << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_UHPHS_OHCI           [expr 0x3 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_DMA0                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_DMA1                 [expr 0x5 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_ISI                  [expr 0x6 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_LCD                  [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_EMAC                 [expr 0x8 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_UDPHS                [expr 0x9 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_UHPHS_EHCI           [expr 0xA << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR6_VDEC                 [expr 0xB << 18 ]
set AT91C_MATRIX_ARBT     [expr 0x3 << 24 ]
# -------- MATRIX_SCFG7 : (MATRIX Offset: 0x5c) Slave Configuration Register 7 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR7 [expr 0xF << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR7_ARM926I              [expr 0x0 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR7_ARM926D              [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR7_PDC                  [expr 0x2 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR7_DMA0                 [expr 0x4 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR7_DMA1                 [expr 0x5 << 18 ]
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
set AT91C_MATRIX_M9PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M10PR    [expr 0x3 <<  8 ]
set AT91C_MATRIX_M11PR    [expr 0x3 << 12 ]
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
set AT91C_MATRIX_M9PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M10PR    [expr 0x3 <<  8 ]
set AT91C_MATRIX_M11PR    [expr 0x3 << 12 ]
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
set AT91C_MATRIX_M9PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M10PR    [expr 0x3 <<  8 ]
set AT91C_MATRIX_M11PR    [expr 0x3 << 12 ]
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
set AT91C_MATRIX_M9PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M10PR    [expr 0x3 <<  8 ]
set AT91C_MATRIX_M11PR    [expr 0x3 << 12 ]
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
set AT91C_MATRIX_M9PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M10PR    [expr 0x3 <<  8 ]
set AT91C_MATRIX_M11PR    [expr 0x3 << 12 ]
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
set AT91C_MATRIX_M9PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M10PR    [expr 0x3 <<  8 ]
set AT91C_MATRIX_M11PR    [expr 0x3 << 12 ]
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
set AT91C_MATRIX_M9PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M10PR    [expr 0x3 <<  8 ]
set AT91C_MATRIX_M11PR    [expr 0x3 << 12 ]
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
set AT91C_MATRIX_M9PR     [expr 0x3 <<  4 ]
set AT91C_MATRIX_M10PR    [expr 0x3 <<  8 ]
set AT91C_MATRIX_M11PR    [expr 0x3 << 12 ]
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
# -------- MATRIX_WRPROTEN : (MATRIX Offset: 0x1e4) Write Protection Control Register -------- 
set AT91C_MATRIX_WRPROT   [expr 0x1 <<  0 ]
set 	AT91C_MATRIX_WRPROT_DISABLE              0x0
set 	AT91C_MATRIX_WRPROT_ENABLE               0x1
# -------- MATRIX_WRPROTST : (MATRIX Offset: 0x1e8) Write Protection Status Register -------- 
set AT91C_MATRIX_WRPROT_VIOLATION [expr 0x1 <<  0 ]
set 	AT91C_MATRIX_WRPROT_VIOLATION_UNDETECTED           0x0
set 	AT91C_MATRIX_WRPROT_VIOLATION_DETECTED             0x1
set AT91C_MATRIX_WRPROT_VIOLATION_OFFSET [expr 0x1FF <<  8 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AHB CCFG Interface
# *****************************************************************************
# -------- CCFG_TCMR : (CCFG Offset: 0x0) TCM Configuration -------- 
set AT91C_CCFG_ITCM_SIZE  [expr 0xF <<  0 ]
set 	AT91C_CCFG_ITCM_SIZE_0KB                  0x0
set 	AT91C_CCFG_ITCM_SIZE_32KB                 0x6
set AT91C_CCFG_DTCM_SIZE  [expr 0xF <<  4 ]
set 	AT91C_CCFG_DTCM_SIZE_0KB                  [expr 0x0 <<  4 ]
set 	AT91C_CCFG_DTCM_SIZE_32KB                 [expr 0x6 <<  4 ]
set 	AT91C_CCFG_DTCM_SIZE_64KB                 [expr 0x7 <<  4 ]
set AT91C_CCFG_WAIT_STATE_TCM [expr 0x1 << 11 ]
set 	AT91C_CCFG_WAIT_STATE_TCM_NO_WS                [expr 0x0 << 11 ]
set 	AT91C_CCFG_WAIT_STATE_TCM_ONE_WS               [expr 0x1 << 11 ]
# -------- CCFG_UDPHS : (CCFG Offset: 0x4) USB HS configuration -------- 
set AT91C_CCFG_DONT_USE_UTMI_LOCK [expr 0x1 <<  0 ]
set 	AT91C_CCFG_DONT_USE_UTMI_LOCK_DONT_USE_LOCK        0x0
# -------- CCFG_VIDEO : (CCFG Offset: 0x8) Video Mode configuration -------- 
set AT91C_VDEC_SEL        [expr 0x1 <<  0 ]
set 	AT91C_VDEC_SEL_OFF                  0x0
set 	AT91C_VDEC_SEL_ON                   0x1
# -------- CCFG_EBICSA : (CCFG Offset: 0x18) EBI Chip Select Assignement Register -------- 
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
set AT91C_EBI_DRV         [expr 0x1 << 17 ]
set AT91C_CCFG_DDR_DRV    [expr 0x1 << 18 ]

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
#              SOFTWARE API DEFINITION  FOR Power Management Controller V610
# *****************************************************************************
# -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
set AT91C_PMC_DDR         [expr 0x1 <<  2 ]
set AT91C_PMC_UHP         [expr 0x1 <<  6 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
# -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_DDR         [expr 0x1 <<  2 ]
set AT91C_PMC_UHP         [expr 0x1 <<  6 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
# -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_DDR         [expr 0x1 <<  2 ]
set AT91C_PMC_UHP         [expr 0x1 <<  6 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
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
set AT91C_CKGR_MULA       [expr 0xFF << 16 ]
set AT91C_CKGR_SRCA       [expr 0x1 << 29 ]
# -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x3 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLLA_CLK             0x2
set 	AT91C_PMC_CSS_UPLL_CLK             0x3
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
set 	AT91C_PMC_MDIV_3                    [expr 0x3 <<  8 ]
set AT91C_PMC_PLLADIV2    [expr 0x1 << 12 ]
set 	AT91C_PMC_PLLADIV2_1                    [expr 0x0 << 12 ]
set 	AT91C_PMC_PLLADIV2_2                    [expr 0x1 << 12 ]
# -------- PMC_USB : (PMC Offset: 0x38) USB Clock Register -------- 
set AT91C_PMC_USBS        [expr 0x1 <<  0 ]
set 	AT91C_PMC_USBS_USB_PLLA             0x0
set 	AT91C_PMC_USBS_USB_UPLL             0x1
set AT91C_PMC_USBDIV      [expr 0xF <<  8 ]
set 	AT91C_PMC_USBDIV_1                    [expr 0x0 <<  8 ]
set 	AT91C_PMC_USBDIV_2                    [expr 0x1 <<  8 ]
set 	AT91C_PMC_USBDIV_3                    [expr 0x2 <<  8 ]
set 	AT91C_PMC_USBDIV_4                    [expr 0x3 <<  8 ]
set 	AT91C_PMC_USBDIV_5                    [expr 0x4 <<  8 ]
set 	AT91C_PMC_USBDIV_6                    [expr 0x5 <<  8 ]
set 	AT91C_PMC_USBDIV_7                    [expr 0x6 <<  8 ]
set 	AT91C_PMC_USBDIV_8                    [expr 0x7 <<  8 ]
set 	AT91C_PMC_USBDIV_9                    [expr 0x8 <<  8 ]
set 	AT91C_PMC_USBDIV_10                   [expr 0x9 <<  8 ]
set 	AT91C_PMC_USBDIV_11                   [expr 0xA <<  8 ]
set 	AT91C_PMC_USBDIV_12                   [expr 0xB <<  8 ]
set 	AT91C_PMC_USBDIV_13                   [expr 0xC <<  8 ]
set 	AT91C_PMC_USBDIV_14                   [expr 0xD <<  8 ]
set 	AT91C_PMC_USBDIV_15                   [expr 0xE <<  8 ]
set 	AT91C_PMC_USBDIV_16                   [expr 0xF <<  8 ]
# -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock 0 Register -------- 
set AT91C_PMC_CSS         [expr 0x3 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLLA_CLK             0x2
set 	AT91C_PMC_CSS_UPLL_CLK             0x3
set AT91C_PMC_PRES        [expr 0x7 <<  2 ]
set 	AT91C_PMC_PRES_CLK                  [expr 0x0 <<  2 ]
set 	AT91C_PMC_PRES_CLK_2                [expr 0x1 <<  2 ]
set 	AT91C_PMC_PRES_CLK_4                [expr 0x2 <<  2 ]
set 	AT91C_PMC_PRES_CLK_8                [expr 0x3 <<  2 ]
set 	AT91C_PMC_PRES_CLK_16               [expr 0x4 <<  2 ]
set 	AT91C_PMC_PRES_CLK_32               [expr 0x5 <<  2 ]
set 	AT91C_PMC_PRES_CLK_64               [expr 0x6 <<  2 ]
set AT91C_PMC_SLCKMCK     [expr 0x1 <<  8 ]
set 	AT91C_PMC_SLCKMCK_SLCK                 [expr 0x0 <<  8 ]
set 	AT91C_PMC_SLCKMCK_MCK                  [expr 0x1 <<  8 ]
# -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
# -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
# -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
# -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
# -------- PMC_PLLICPR : (PMC Offset: 0x80) PLL Charge Pump Current Register -------- 
set AT91C_PMC_ICPPLLA     [expr 0xF <<  0 ]
set 	AT91C_PMC_ICPPLLA_0                    0x0
set 	AT91C_PMC_ICPPLLA_1                    0x1
set AT91C_PMC_REALLOCK    [expr 0x1 <<  7 ]
set AT91C_PMC_IPLLA       [expr 0xF <<  8 ]
set 	AT91C_PMC_IPLLA_0                    [expr 0x0 <<  8 ]
set 	AT91C_PMC_IPLLA_1                    [expr 0x1 <<  8 ]
# -------- PMC_FEATURES : (PMC Offset: 0xf8)   -------- 
set AT91C_PMC_CFGAHBCLK   [expr 0x1 <<  0 ]
set 	AT91C_PMC_CFGAHBCLK_0                    0x0
set 	AT91C_PMC_CFGAHBCLK_1                    0x1
set AT91C_PMC_HCLKEN      [expr 0x1 <<  1 ]
set 	AT91C_PMC_HCLKEN_0                    [expr 0x0 <<  1 ]
set 	AT91C_PMC_HCLKEN_1                    [expr 0x1 <<  1 ]
set AT91C_PMC_PERMCLK     [expr 0x1 <<  2 ]
set 	AT91C_PMC_PERMCLK_0                    [expr 0x0 <<  2 ]
set 	AT91C_PMC_PERMCLK_1                    [expr 0x1 <<  2 ]
set AT91C_PMC_CORE2       [expr 0x1 <<  3 ]
set 	AT91C_PMC_CORE2_0                    [expr 0x0 <<  3 ]
set 	AT91C_PMC_CORE2_1                    [expr 0x1 <<  3 ]
set AT91C_PMC_USBDEVCK    [expr 0x1 <<  4 ]
set 	AT91C_PMC_USBDEVCK_0                    [expr 0x0 <<  4 ]
set 	AT91C_PMC_USBDEVCK_1                    [expr 0x1 <<  4 ]
set AT91C_PMC_USBHOSTCK   [expr 0x1 <<  5 ]
set 	AT91C_PMC_USBHOSTCK_0                    [expr 0x0 <<  5 ]
set 	AT91C_PMC_USBHOSTCK_1                    [expr 0x1 <<  5 ]
set AT91C_PMC_USBOTGCK    [expr 0x1 <<  6 ]
set 	AT91C_PMC_USBOTGCK_0                    [expr 0x0 <<  6 ]
set 	AT91C_PMC_USBOTGCK_1                    [expr 0x1 <<  6 ]
set AT91C_PMC_UHSYNRST    [expr 0x1 <<  7 ]
set 	AT91C_PMC_UHSYNRST_0                    [expr 0x0 <<  7 ]
set 	AT91C_PMC_UHSYNRST_1                    [expr 0x1 <<  7 ]
set AT91C_PMC_UOSYNRST    [expr 0x1 <<  8 ]
set 	AT91C_PMC_UOSYNRST_0                    [expr 0x0 <<  8 ]
set 	AT91C_PMC_UOSYNRST_1                    [expr 0x1 <<  8 ]
set AT91C_PMC_PLLENPOL    [expr 0x1 <<  9 ]
set 	AT91C_PMC_PLLENPOL_0                    [expr 0x0 <<  9 ]
set 	AT91C_PMC_PLLENPOL_1                    [expr 0x1 <<  9 ]
set AT91C_PMC_BIASREG     [expr 0x1 << 10 ]
set 	AT91C_PMC_BIASREG_0                    [expr 0x0 << 10 ]
set 	AT91C_PMC_BIASREG_1                    [expr 0x1 << 10 ]
set AT91C_PMC_OUTPLL      [expr 0x1 << 11 ]
set 	AT91C_PMC_OUTPLL_0                    [expr 0x0 << 11 ]
set 	AT91C_PMC_OUTPLL_1                    [expr 0x1 << 11 ]
set AT91C_PMC_OUTCURR     [expr 0x1 << 12 ]
set 	AT91C_PMC_OUTCURR_0                    [expr 0x0 << 12 ]
set 	AT91C_PMC_OUTCURR_1                    [expr 0x1 << 12 ]
set AT91C_PMC_FWUP        [expr 0x1 << 13 ]
set 	AT91C_PMC_FWUP_0                    [expr 0x0 << 13 ]
set 	AT91C_PMC_FWUP_1                    [expr 0x1 << 13 ]
set AT91C_PMC_SELMAINCLK  [expr 0x1 << 14 ]
set 	AT91C_PMC_SELMAINCLK_0                    [expr 0x0 << 14 ]
set 	AT91C_PMC_SELMAINCLK_1                    [expr 0x1 << 14 ]
set AT91C_PMC_RSTCLKM     [expr 0x1 << 15 ]
set 	AT91C_PMC_RSTCLKM_0                    [expr 0x0 << 15 ]
set 	AT91C_PMC_RSTCLKM_1                    [expr 0x1 << 15 ]
set AT91C_PMC_NB_PERIPH_CLOCK [expr 0xFF << 16 ]
set AT91C_PMC_NB_PERIPH_CLOCK [expr 0xFF << 24 ]
# -------- PMC_VERSION : (PMC Offset: 0xfc)   -------- 
set AT91C_PMC_Version     [expr 0xFFFF <<  0 ]
set 	AT91C_PMC_Version_0                    0x0
set 	AT91C_PMC_Version_1                    0x1
set AT91C_PMC_MFN         [expr 0x7 << 16 ]
set 	AT91C_PMC_MFN_0                    [expr 0x0 << 16 ]
set 	AT91C_PMC_MFN_1                    [expr 0x1 << 16 ]

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
set AT91C_CKGR_MULA       [expr 0xFF << 16 ]
set AT91C_CKGR_SRCA       [expr 0x1 << 29 ]

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
set AT91C_SHDWC_RTTWKEN   [expr 0x1 << 16 ]
# -------- SHDWC_SHSR : (SHDWC Offset: 0x8) Shut Down Status Register -------- 
set AT91C_SHDWC_WAKEUP0   [expr 0x1 <<  0 ]
set AT91C_SHDWC_RTTWK     [expr 0x1 << 16 ]

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
set 	AT91C_MCI_MCIEN_0                    0x0
set 	AT91C_MCI_MCIEN_1                    0x1
set AT91C_MCI_MCIDIS      [expr 0x1 <<  1 ]
set 	AT91C_MCI_MCIDIS_0                    [expr 0x0 <<  1 ]
set 	AT91C_MCI_MCIDIS_1                    [expr 0x1 <<  1 ]
set AT91C_MCI_PWSEN       [expr 0x1 <<  2 ]
set 	AT91C_MCI_PWSEN_0                    [expr 0x0 <<  2 ]
set 	AT91C_MCI_PWSEN_1                    [expr 0x1 <<  2 ]
set AT91C_MCI_PWSDIS      [expr 0x1 <<  3 ]
set 	AT91C_MCI_PWSDIS_0                    [expr 0x0 <<  3 ]
set 	AT91C_MCI_PWSDIS_1                    [expr 0x1 <<  3 ]
set AT91C_MCI_IOWAITEN    [expr 0x1 <<  4 ]
set 	AT91C_MCI_IOWAITEN_0                    [expr 0x0 <<  4 ]
set 	AT91C_MCI_IOWAITEN_1                    [expr 0x1 <<  4 ]
set AT91C_MCI_IOWAITDIS   [expr 0x1 <<  5 ]
set 	AT91C_MCI_IOWAITDIS_0                    [expr 0x0 <<  5 ]
set 	AT91C_MCI_IOWAITDIS_1                    [expr 0x1 <<  5 ]
set AT91C_MCI_SWRST       [expr 0x1 <<  7 ]
set 	AT91C_MCI_SWRST_0                    [expr 0x0 <<  7 ]
set 	AT91C_MCI_SWRST_1                    [expr 0x1 <<  7 ]
# -------- MCI_MR : (MCI Offset: 0x4) MCI Mode Register -------- 
set AT91C_MCI_CLKDIV      [expr 0xFF <<  0 ]
set AT91C_MCI_PWSDIV      [expr 0x7 <<  8 ]
set AT91C_MCI_RDPROOF     [expr 0x1 << 11 ]
set 	AT91C_MCI_RDPROOF_DISABLE              [expr 0x0 << 11 ]
set 	AT91C_MCI_RDPROOF_ENABLE               [expr 0x1 << 11 ]
set AT91C_MCI_WRPROOF     [expr 0x1 << 12 ]
set 	AT91C_MCI_WRPROOF_DISABLE              [expr 0x0 << 12 ]
set 	AT91C_MCI_WRPROOF_ENABLE               [expr 0x1 << 12 ]
set AT91C_MCI_PDCFBYTE    [expr 0x1 << 13 ]
set 	AT91C_MCI_PDCFBYTE_DISABLE              [expr 0x0 << 13 ]
set 	AT91C_MCI_PDCFBYTE_ENABLE               [expr 0x1 << 13 ]
set AT91C_MCI_PDCPADV     [expr 0x1 << 14 ]
set AT91C_MCI_PDCMODE     [expr 0x1 << 15 ]
set 	AT91C_MCI_PDCMODE_DISABLE              [expr 0x0 << 15 ]
set 	AT91C_MCI_PDCMODE_ENABLE               [expr 0x1 << 15 ]
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
set 	AT91C_MCI_SCDSEL_SLOTA                0x0
set 	AT91C_MCI_SCDSEL_SLOTB                0x1
set 	AT91C_MCI_SCDSEL_SLOTC                0x2
set 	AT91C_MCI_SCDSEL_SLOTD                0x3
set AT91C_MCI_SCDBUS      [expr 0x1 <<  6 ]
set 	AT91C_MCI_SCDBUS_1BIT                 [expr 0x0 <<  6 ]
set 	AT91C_MCI_SCDBUS_4BITS                [expr 0x2 <<  6 ]
set 	AT91C_MCI_SCDBUS_8BITS                [expr 0x3 <<  6 ]
# -------- MCI_CMDR : (MCI Offset: 0x14) MCI Command Register -------- 
set AT91C_MCI_CMDNB       [expr 0x3F <<  0 ]
set AT91C_MCI_RSPTYP      [expr 0x3 <<  6 ]
set 	AT91C_MCI_RSPTYP_NO                   [expr 0x0 <<  6 ]
set 	AT91C_MCI_RSPTYP_48                   [expr 0x1 <<  6 ]
set 	AT91C_MCI_RSPTYP_136                  [expr 0x2 <<  6 ]
set 	AT91C_MCI_RSPTYP_R1B                  [expr 0x3 <<  6 ]
set AT91C_MCI_SPCMD       [expr 0x7 <<  8 ]
set 	AT91C_MCI_SPCMD_NONE                 [expr 0x0 <<  8 ]
set 	AT91C_MCI_SPCMD_INIT                 [expr 0x1 <<  8 ]
set 	AT91C_MCI_SPCMD_SYNC                 [expr 0x2 <<  8 ]
set 	AT91C_MCI_SPCMD_CE_ATA               [expr 0x3 <<  8 ]
set 	AT91C_MCI_SPCMD_IT_CMD               [expr 0x4 <<  8 ]
set 	AT91C_MCI_SPCMD_IT_REP               [expr 0x5 <<  8 ]
set AT91C_MCI_OPDCMD      [expr 0x1 << 11 ]
set 	AT91C_MCI_OPDCMD_PUSHPULL             [expr 0x0 << 11 ]
set 	AT91C_MCI_OPDCMD_OPENDRAIN            [expr 0x1 << 11 ]
set AT91C_MCI_MAXLAT      [expr 0x1 << 12 ]
set 	AT91C_MCI_MAXLAT_5                    [expr 0x0 << 12 ]
set 	AT91C_MCI_MAXLAT_64                   [expr 0x1 << 12 ]
set AT91C_MCI_TRCMD       [expr 0x3 << 16 ]
set 	AT91C_MCI_TRCMD_NO                   [expr 0x0 << 16 ]
set 	AT91C_MCI_TRCMD_START                [expr 0x1 << 16 ]
set 	AT91C_MCI_TRCMD_STOP                 [expr 0x2 << 16 ]
set AT91C_MCI_TRDIR       [expr 0x1 << 18 ]
set 	AT91C_MCI_TRDIR_WRITE                [expr 0x0 << 18 ]
set 	AT91C_MCI_TRDIR_READ                 [expr 0x1 << 18 ]
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
set AT91C_MCI_ATACS       [expr 0x1 << 26 ]
set 	AT91C_MCI_ATACS_NORMAL               [expr 0x0 << 26 ]
set 	AT91C_MCI_ATACS_COMPLETION           [expr 0x1 << 26 ]
# -------- MCI_BLKR : (MCI Offset: 0x18) MCI Block Register -------- 
set AT91C_MCI_BCNT        [expr 0xFFFF <<  0 ]
set AT91C_MCI_BLKLEN      [expr 0xFFFF << 16 ]
# -------- MCI_CSTOR : (MCI Offset: 0x1c) MCI Completion Signal Timeout Register -------- 
set AT91C_MCI_CSTOCYC     [expr 0xF <<  0 ]
set AT91C_MCI_CSTOMUL     [expr 0x7 <<  4 ]
set 	AT91C_MCI_CSTOMUL_1                    [expr 0x0 <<  4 ]
set 	AT91C_MCI_CSTOMUL_16                   [expr 0x1 <<  4 ]
set 	AT91C_MCI_CSTOMUL_128                  [expr 0x2 <<  4 ]
set 	AT91C_MCI_CSTOMUL_256                  [expr 0x3 <<  4 ]
set 	AT91C_MCI_CSTOMUL_1024                 [expr 0x4 <<  4 ]
set 	AT91C_MCI_CSTOMUL_4096                 [expr 0x5 <<  4 ]
set 	AT91C_MCI_CSTOMUL_65536                [expr 0x6 <<  4 ]
set 	AT91C_MCI_CSTOMUL_1048576              [expr 0x7 <<  4 ]
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
set AT91C_MCI_SDIOWAIT    [expr 0x1 << 12 ]
set AT91C_MCI_CSRCV       [expr 0x1 << 13 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_CSTOE       [expr 0x1 << 23 ]
set AT91C_MCI_BLKOVRE     [expr 0x1 << 24 ]
set AT91C_MCI_DMADONE     [expr 0x1 << 25 ]
set AT91C_MCI_FIFOEMPTY   [expr 0x1 << 26 ]
set AT91C_MCI_XFRDONE     [expr 0x1 << 27 ]
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
set AT91C_MCI_SDIOWAIT    [expr 0x1 << 12 ]
set AT91C_MCI_CSRCV       [expr 0x1 << 13 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_CSTOE       [expr 0x1 << 23 ]
set AT91C_MCI_BLKOVRE     [expr 0x1 << 24 ]
set AT91C_MCI_DMADONE     [expr 0x1 << 25 ]
set AT91C_MCI_FIFOEMPTY   [expr 0x1 << 26 ]
set AT91C_MCI_XFRDONE     [expr 0x1 << 27 ]
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
set AT91C_MCI_SDIOWAIT    [expr 0x1 << 12 ]
set AT91C_MCI_CSRCV       [expr 0x1 << 13 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_CSTOE       [expr 0x1 << 23 ]
set AT91C_MCI_BLKOVRE     [expr 0x1 << 24 ]
set AT91C_MCI_DMADONE     [expr 0x1 << 25 ]
set AT91C_MCI_FIFOEMPTY   [expr 0x1 << 26 ]
set AT91C_MCI_XFRDONE     [expr 0x1 << 27 ]
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
set AT91C_MCI_SDIOWAIT    [expr 0x1 << 12 ]
set AT91C_MCI_CSRCV       [expr 0x1 << 13 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_CSTOE       [expr 0x1 << 23 ]
set AT91C_MCI_BLKOVRE     [expr 0x1 << 24 ]
set AT91C_MCI_DMADONE     [expr 0x1 << 25 ]
set AT91C_MCI_FIFOEMPTY   [expr 0x1 << 26 ]
set AT91C_MCI_XFRDONE     [expr 0x1 << 27 ]
set AT91C_MCI_OVRE        [expr 0x1 << 30 ]
set AT91C_MCI_UNRE        [expr 0x1 << 31 ]
# -------- MCI_DMA : (MCI Offset: 0x50) MCI DMA Configuration Register -------- 
set AT91C_MCI_OFFSET      [expr 0x3 <<  0 ]
set AT91C_MCI_CHKSIZE     [expr 0x7 <<  4 ]
set 	AT91C_MCI_CHKSIZE_1                    [expr 0x0 <<  4 ]
set 	AT91C_MCI_CHKSIZE_4                    [expr 0x1 <<  4 ]
set 	AT91C_MCI_CHKSIZE_8                    [expr 0x2 <<  4 ]
set 	AT91C_MCI_CHKSIZE_16                   [expr 0x3 <<  4 ]
set 	AT91C_MCI_CHKSIZE_32                   [expr 0x4 <<  4 ]
set AT91C_MCI_DMAEN       [expr 0x1 <<  8 ]
set 	AT91C_MCI_DMAEN_DISABLE              [expr 0x0 <<  8 ]
set 	AT91C_MCI_DMAEN_ENABLE               [expr 0x1 <<  8 ]
# -------- MCI_CFG : (MCI Offset: 0x54) MCI Configuration Register -------- 
set AT91C_MCI_FIFOMODE    [expr 0x1 <<  0 ]
set 	AT91C_MCI_FIFOMODE_AMOUNTDATA           0x0
set 	AT91C_MCI_FIFOMODE_ONEDATA              0x1
set AT91C_MCI_FERRCTRL    [expr 0x1 <<  4 ]
set 	AT91C_MCI_FERRCTRL_RWCMD                [expr 0x0 <<  4 ]
set 	AT91C_MCI_FERRCTRL_READSR               [expr 0x1 <<  4 ]
set AT91C_MCI_HSMODE      [expr 0x1 <<  8 ]
set 	AT91C_MCI_HSMODE_DISABLE              [expr 0x0 <<  8 ]
set 	AT91C_MCI_HSMODE_ENABLE               [expr 0x1 <<  8 ]
set AT91C_MCI_LSYNC       [expr 0x1 << 12 ]
set 	AT91C_MCI_LSYNC_CURRENT              [expr 0x0 << 12 ]
set 	AT91C_MCI_LSYNC_INFINITE             [expr 0x1 << 12 ]
# -------- MCI_WPCR : (MCI Offset: 0xe4) Write Protection Control Register -------- 
set AT91C_MCI_WP_EN       [expr 0x1 <<  0 ]
set 	AT91C_MCI_WP_EN_DISABLE              0x0
set 	AT91C_MCI_WP_EN_ENABLE               0x1
set AT91C_MCI_WP_KEY      [expr 0xFFFFFF <<  8 ]
# -------- MCI_WPSR : (MCI Offset: 0xe8) Write Protection Status Register -------- 
set AT91C_MCI_WP_VS       [expr 0xF <<  0 ]
set 	AT91C_MCI_WP_VS_NO_VIOLATION         0x0
set 	AT91C_MCI_WP_VS_ON_WRITE             0x1
set 	AT91C_MCI_WP_VS_ON_RESET             0x2
set 	AT91C_MCI_WP_VS_ON_BOTH              0x3
set AT91C_MCI_WP_VSRC     [expr 0xF <<  8 ]
set 	AT91C_MCI_WP_VSRC_NO_VIOLATION         [expr 0x0 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_MR               [expr 0x1 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_DTOR             [expr 0x2 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_SDCR             [expr 0x3 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_CSTOR            [expr 0x4 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_DMA              [expr 0x5 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_CFG              [expr 0x6 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_DEL              [expr 0x7 <<  8 ]

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
#              SOFTWARE API DEFINITION  FOR TSADC
# *****************************************************************************
# -------- TSADC_CR : (TSADC Offset: 0x0) Control Register -------- 
set AT91C_TSADC_SWRST     [expr 0x1 <<  0 ]
set AT91C_TSADC_START     [expr 0x1 <<  1 ]
# -------- TSADC_MR : (TSADC Offset: 0x4) Mode Register -------- 
set AT91C_TSADC_TSAMOD    [expr 0x3 <<  0 ]
set 	AT91C_TSADC_TSAMOD_ADC_ONLY_MODE        0x0
set 	AT91C_TSADC_TSAMOD_TS_ONLY_MODE         0x1
set AT91C_TSADC_LOWRES    [expr 0x1 <<  4 ]
set AT91C_TSADC_SLEEP     [expr 0x1 <<  5 ]
set AT91C_TSADC_PENDET    [expr 0x1 <<  6 ]
set AT91C_TSADC_PRESCAL   [expr 0x3F <<  8 ]
set AT91C_TSADC_STARTUP   [expr 0x7F << 16 ]
set AT91C_TSADC_SHTIM     [expr 0xF << 24 ]
set AT91C_TSADC_PENDBC    [expr 0xF << 28 ]
# -------- TSADC_TRGR : (TSADC Offset: 0x8) Trigger Register -------- 
set AT91C_TSADC_TRGMOD    [expr 0x7 <<  0 ]
set 	AT91C_TSADC_TRGMOD_NO_TRIGGER           0x0
set 	AT91C_TSADC_TRGMOD_EXTERNAL_TRIGGER_RE  0x1
set 	AT91C_TSADC_TRGMOD_EXTERNAL_TRIGGER_FE  0x2
set 	AT91C_TSADC_TRGMOD_EXTERNAL_TRIGGER_AE  0x3
set 	AT91C_TSADC_TRGMOD_PENDET_TRIGGER       0x4
set 	AT91C_TSADC_TRGMOD_PERIODIC_TRIGGER     0x5
set 	AT91C_TSADC_TRGMOD_CONT_TRIGGER         0x6
set AT91C_TSADC_TRGPER    [expr 0xFFFF << 16 ]
# -------- TSADC_TSR : (TSADC Offset: 0xc) Touch Screen Register -------- 
set AT91C_TSADC_TSSHTIM   [expr 0xF << 24 ]
# -------- TSADC_CHER : (TSADC Offset: 0x10) Channel Enable Register -------- 
set AT91C_TSADC_CHENA0    [expr 0x1 <<  0 ]
set AT91C_TSADC_CHENA1    [expr 0x1 <<  1 ]
set AT91C_TSADC_CHENA2    [expr 0x1 <<  2 ]
set AT91C_TSADC_CHENA3    [expr 0x1 <<  3 ]
set AT91C_TSADC_CHENA4    [expr 0x1 <<  4 ]
set AT91C_TSADC_CHENA5    [expr 0x1 <<  5 ]
set AT91C_TSADC_CHENA6    [expr 0x1 <<  6 ]
set AT91C_TSADC_CHENA7    [expr 0x1 <<  7 ]
# -------- TSADC_CHDR : (TSADC Offset: 0x14) Channel Disable Register -------- 
set AT91C_TSADC_CHDIS0    [expr 0x1 <<  0 ]
set AT91C_TSADC_CHDIS1    [expr 0x1 <<  1 ]
set AT91C_TSADC_CHDIS2    [expr 0x1 <<  2 ]
set AT91C_TSADC_CHDIS3    [expr 0x1 <<  3 ]
set AT91C_TSADC_CHDIS4    [expr 0x1 <<  4 ]
set AT91C_TSADC_CHDIS5    [expr 0x1 <<  5 ]
set AT91C_TSADC_CHDIS6    [expr 0x1 <<  6 ]
set AT91C_TSADC_CHDIS7    [expr 0x1 <<  7 ]
# -------- TSADC_CHSR : (TSADC Offset: 0x18) Channel Status Register -------- 
set AT91C_TSADC_CHS0      [expr 0x1 <<  0 ]
set AT91C_TSADC_CHS1      [expr 0x1 <<  1 ]
set AT91C_TSADC_CHS2      [expr 0x1 <<  2 ]
set AT91C_TSADC_CHS3      [expr 0x1 <<  3 ]
set AT91C_TSADC_CHS4      [expr 0x1 <<  4 ]
set AT91C_TSADC_CHS5      [expr 0x1 <<  5 ]
set AT91C_TSADC_CHS6      [expr 0x1 <<  6 ]
set AT91C_TSADC_CHS7      [expr 0x1 <<  7 ]
# -------- TSADC_SR : (TSADC Offset: 0x1c) Status Register -------- 
set AT91C_TSADC_EOC0      [expr 0x1 <<  0 ]
set AT91C_TSADC_EOC1      [expr 0x1 <<  1 ]
set AT91C_TSADC_EOC2      [expr 0x1 <<  2 ]
set AT91C_TSADC_EOC3      [expr 0x1 <<  3 ]
set AT91C_TSADC_EOC4      [expr 0x1 <<  4 ]
set AT91C_TSADC_EOC5      [expr 0x1 <<  5 ]
set AT91C_TSADC_EOC6      [expr 0x1 <<  6 ]
set AT91C_TSADC_EOC7      [expr 0x1 <<  7 ]
set AT91C_TSADC_OVRE0     [expr 0x1 <<  8 ]
set AT91C_TSADC_OVRE1     [expr 0x1 <<  9 ]
set AT91C_TSADC_OVRE2     [expr 0x1 << 10 ]
set AT91C_TSADC_OVRE3     [expr 0x1 << 11 ]
set AT91C_TSADC_OVRE4     [expr 0x1 << 12 ]
set AT91C_TSADC_OVRE5     [expr 0x1 << 13 ]
set AT91C_TSADC_OVRE6     [expr 0x1 << 14 ]
set AT91C_TSADC_OVRE7     [expr 0x1 << 15 ]
set AT91C_TSADC_DRDY      [expr 0x1 << 16 ]
set AT91C_TSADC_GOVRE     [expr 0x1 << 17 ]
set AT91C_TSADC_ENDRX     [expr 0x1 << 18 ]
set AT91C_TSADC_RXBUFF    [expr 0x1 << 19 ]
set AT91C_TSADC_PENCNT    [expr 0x1 << 20 ]
set AT91C_TSADC_NOCNT     [expr 0x1 << 21 ]
# -------- TSADC_LCDR : (TSADC Offset: 0x20) Last Converted Data Register -------- 
set AT91C_TSADC_LDATA     [expr 0x3FF <<  0 ]
# -------- TSADC_IER : (TSADC Offset: 0x24) Interrupt Enable Register -------- 
set AT91C_TSADC_IENAEOC0  [expr 0x1 <<  0 ]
set AT91C_TSADC_IENAEOC1  [expr 0x1 <<  1 ]
set AT91C_TSADC_IENAEOC2  [expr 0x1 <<  2 ]
set AT91C_TSADC_IENAEOC3  [expr 0x1 <<  3 ]
set AT91C_TSADC_IENAEOC4  [expr 0x1 <<  4 ]
set AT91C_TSADC_IENAEOC5  [expr 0x1 <<  5 ]
set AT91C_TSADC_IENAEOC6  [expr 0x1 <<  6 ]
set AT91C_TSADC_IENAEOC7  [expr 0x1 <<  7 ]
set AT91C_TSADC_IENAOVRE0 [expr 0x1 <<  8 ]
set AT91C_TSADC_IENAOVRE1 [expr 0x1 <<  9 ]
set AT91C_TSADC_IENAOVRE2 [expr 0x1 << 10 ]
set AT91C_TSADC_IENAOVRE3 [expr 0x1 << 11 ]
set AT91C_TSADC_IENAOVRE4 [expr 0x1 << 12 ]
set AT91C_TSADC_IENAOVRE5 [expr 0x1 << 13 ]
set AT91C_TSADC_IENAOVRE6 [expr 0x1 << 14 ]
set AT91C_TSADC_IENAOVRE7 [expr 0x1 << 15 ]
set AT91C_TSADC_IENADRDY  [expr 0x1 << 16 ]
set AT91C_TSADC_IENAGOVRE [expr 0x1 << 17 ]
set AT91C_TSADC_IENAENDRX [expr 0x1 << 18 ]
set AT91C_TSADC_IENARXBUFF [expr 0x1 << 19 ]
set AT91C_TSADC_IENAPENCNT [expr 0x1 << 20 ]
set AT91C_TSADC_IENANOCNT [expr 0x1 << 21 ]
# -------- TSADC_IDR : (TSADC Offset: 0x28) Interrupt Disable Register -------- 
set AT91C_TSADC_IDISEOC0  [expr 0x1 <<  0 ]
set AT91C_TSADC_IDISEOC1  [expr 0x1 <<  1 ]
set AT91C_TSADC_IDISEOC2  [expr 0x1 <<  2 ]
set AT91C_TSADC_IDISEOC3  [expr 0x1 <<  3 ]
set AT91C_TSADC_IDISEOC4  [expr 0x1 <<  4 ]
set AT91C_TSADC_IDISEOC5  [expr 0x1 <<  5 ]
set AT91C_TSADC_IDISEOC6  [expr 0x1 <<  6 ]
set AT91C_TSADC_IDISEOC7  [expr 0x1 <<  7 ]
set AT91C_TSADC_IDISOVRE0 [expr 0x1 <<  8 ]
set AT91C_TSADC_IDISOVRE1 [expr 0x1 <<  9 ]
set AT91C_TSADC_IDISOVRE2 [expr 0x1 << 10 ]
set AT91C_TSADC_IDISOVRE3 [expr 0x1 << 11 ]
set AT91C_TSADC_IDISOVRE4 [expr 0x1 << 12 ]
set AT91C_TSADC_IDISOVRE5 [expr 0x1 << 13 ]
set AT91C_TSADC_IDISOVRE6 [expr 0x1 << 14 ]
set AT91C_TSADC_IDISOVRE7 [expr 0x1 << 15 ]
set AT91C_TSADC_IDISDRDY  [expr 0x1 << 16 ]
set AT91C_TSADC_IDISGOVRE [expr 0x1 << 17 ]
set AT91C_TSADC_IDISENDRX [expr 0x1 << 18 ]
set AT91C_TSADC_IDISRXBUFF [expr 0x1 << 19 ]
set AT91C_TSADC_IDISPENCNT [expr 0x1 << 20 ]
set AT91C_TSADC_IDISNOCNT [expr 0x1 << 21 ]
# -------- TSADC_IMR : (TSADC Offset: 0x2c) Interrupt Mask Register -------- 
set AT91C_TSADC_IMSKEOC0  [expr 0x1 <<  0 ]
set AT91C_TSADC_IMSKEOC1  [expr 0x1 <<  1 ]
set AT91C_TSADC_IMSKEOC2  [expr 0x1 <<  2 ]
set AT91C_TSADC_IMSKEOC3  [expr 0x1 <<  3 ]
set AT91C_TSADC_IMSKEOC4  [expr 0x1 <<  4 ]
set AT91C_TSADC_IMSKEOC5  [expr 0x1 <<  5 ]
set AT91C_TSADC_IMSKEOC6  [expr 0x1 <<  6 ]
set AT91C_TSADC_IMSKEOC7  [expr 0x1 <<  7 ]
set AT91C_TSADC_IMSKOVRE0 [expr 0x1 <<  8 ]
set AT91C_TSADC_IMSKOVRE1 [expr 0x1 <<  9 ]
set AT91C_TSADC_IMSKOVRE2 [expr 0x1 << 10 ]
set AT91C_TSADC_IMSKOVRE3 [expr 0x1 << 11 ]
set AT91C_TSADC_IMSKOVRE4 [expr 0x1 << 12 ]
set AT91C_TSADC_IMSKOVRE5 [expr 0x1 << 13 ]
set AT91C_TSADC_IMSKOVRE6 [expr 0x1 << 14 ]
set AT91C_TSADC_IMSKOVRE7 [expr 0x1 << 15 ]
set AT91C_TSADC_IMSKDRDY  [expr 0x1 << 16 ]
set AT91C_TSADC_IMSKGOVRE [expr 0x1 << 17 ]
set AT91C_TSADC_IMSKENDRX [expr 0x1 << 18 ]
set AT91C_TSADC_IMSKRXBUFF [expr 0x1 << 19 ]
set AT91C_TSADC_IMSKPENCNT [expr 0x1 << 20 ]
set AT91C_TSADC_IMSKNOCNT [expr 0x1 << 21 ]
# -------- TSADC_CDR0 : (TSADC Offset: 0x30) Channel 0 Data Register -------- 
set AT91C_TSADC_DATA0     [expr 0x3FF <<  0 ]
# -------- TSADC_CDR1 : (TSADC Offset: 0x34) Channel 1 Data Register -------- 
set AT91C_TSADC_DATA1     [expr 0x3FF <<  0 ]
# -------- TSADC_CDR2 : (TSADC Offset: 0x38) Channel 2 Data Register -------- 
set AT91C_TSADC_DATA2     [expr 0x3FF <<  0 ]
# -------- TSADC_CDR3 : (TSADC Offset: 0x3c) Channel 3 Data Register -------- 
set AT91C_TSADC_DATA3     [expr 0x3FF <<  0 ]
# -------- TSADC_CDR4 : (TSADC Offset: 0x40) Channel 4 Data Register -------- 
set AT91C_TSADC_DATA4     [expr 0x3FF <<  0 ]
# -------- TSADC_CDR5 : (TSADC Offset: 0x44) Channel 5 Data Register -------- 
set AT91C_TSADC_DATA5     [expr 0x3FF <<  0 ]
# -------- TSADC_CDR6 : (TSADC Offset: 0x48) Channel 6 Data Register -------- 
set AT91C_TSADC_DATA6     [expr 0x3FF <<  0 ]
# -------- TSADC_CDR7 : (TSADC Offset: 0x4c) Channel 7 Data Register -------- 
set AT91C_TSADC_DATA7     [expr 0x3FF <<  0 ]

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
set AT91C_UDPHS_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_UDPHS_TX_PK_RDY [expr 0x1 << 11 ]
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
set AT91C_UDPHS_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_UDPHS_TX_PK_RDY [expr 0x1 << 11 ]
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
set AT91C_UDPHS_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_UDPHS_TX_PK_RDY [expr 0x1 << 11 ]
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
set AT91C_UDPHS_KILL_BANK [expr 0x1 <<  9 ]
set AT91C_UDPHS_RX_BK_RDY [expr 0x1 <<  9 ]
set AT91C_UDPHS_TX_COMPLT [expr 0x1 << 10 ]
set AT91C_UDPHS_ERR_TRANS [expr 0x1 << 11 ]
set AT91C_UDPHS_TX_PK_RDY [expr 0x1 << 11 ]
set AT91C_UDPHS_RX_SETUP  [expr 0x1 << 12 ]
set AT91C_UDPHS_ERR_FL_ISO [expr 0x1 << 12 ]
set AT91C_UDPHS_STALL_SNT [expr 0x1 << 13 ]
set AT91C_UDPHS_ERR_CRISO [expr 0x1 << 13 ]
set AT91C_UDPHS_NAK_IN    [expr 0x1 << 14 ]
set AT91C_UDPHS_NAK_OUT   [expr 0x1 << 15 ]
set AT91C_UDPHS_CONTROL_DIR [expr 0x3 << 16 ]
set 	AT91C_UDPHS_CONTROL_DIR_00                   [expr 0x0 << 16 ]
set 	AT91C_UDPHS_CONTROL_DIR_01                   [expr 0x1 << 16 ]
set 	AT91C_UDPHS_CONTROL_DIR_10                   [expr 0x2 << 16 ]
set 	AT91C_UDPHS_CONTROL_DIR_11                   [expr 0x3 << 16 ]
set AT91C_UDPHS_CURRENT_BANK [expr 0x3 << 16 ]
set 	AT91C_UDPHS_CURRENT_BANK_00                   [expr 0x0 << 16 ]
set 	AT91C_UDPHS_CURRENT_BANK_01                   [expr 0x1 << 16 ]
set 	AT91C_UDPHS_CURRENT_BANK_10                   [expr 0x2 << 16 ]
set 	AT91C_UDPHS_CURRENT_BANK_11                   [expr 0x3 << 16 ]
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
set AT91C_UDPHS_DMA_INT_1 [expr 0x1 << 25 ]
set AT91C_UDPHS_DMA_INT_2 [expr 0x1 << 26 ]
set AT91C_UDPHS_DMA_INT_3 [expr 0x1 << 27 ]
set AT91C_UDPHS_DMA_INT_4 [expr 0x1 << 28 ]
set AT91C_UDPHS_DMA_INT_5 [expr 0x1 << 29 ]
set AT91C_UDPHS_DMA_INT_6 [expr 0x1 << 30 ]
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
set AT91C_UDPHS_DMA_INT_1 [expr 0x1 << 25 ]
set AT91C_UDPHS_DMA_INT_2 [expr 0x1 << 26 ]
set AT91C_UDPHS_DMA_INT_3 [expr 0x1 << 27 ]
set AT91C_UDPHS_DMA_INT_4 [expr 0x1 << 28 ]
set AT91C_UDPHS_DMA_INT_5 [expr 0x1 << 29 ]
set AT91C_UDPHS_DMA_INT_6 [expr 0x1 << 30 ]
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
set AT91C_UDPHS_ISO_EPT_5 [expr 0x1 << 21 ]
set AT91C_UDPHS_ISO_EPT_6 [expr 0x1 << 22 ]
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
set AT91C_HDMA_DSCR_IF    [expr 0x3 <<  0 ]
set 	AT91C_HDMA_DSCR_IF_0                    0x0
set 	AT91C_HDMA_DSCR_IF_1                    0x1
set 	AT91C_HDMA_DSCR_IF_2                    0x2
set 	AT91C_HDMA_DSCR_IF_3                    0x3
set AT91C_HDMA_DSCR       [expr 0x3FFFFFFF <<  2 ]
# -------- HDMA_CTRLA : (HDMA_CH Offset: 0xc)  -------- 
set AT91C_HDMA_BTSIZE     [expr 0xFFFF <<  0 ]
set AT91C_HDMA_SCSIZE     [expr 0x7 << 16 ]
set 	AT91C_HDMA_SCSIZE_1                    [expr 0x0 << 16 ]
set 	AT91C_HDMA_SCSIZE_4                    [expr 0x1 << 16 ]
set 	AT91C_HDMA_SCSIZE_8                    [expr 0x2 << 16 ]
set 	AT91C_HDMA_SCSIZE_16                   [expr 0x3 << 16 ]
set 	AT91C_HDMA_SCSIZE_32                   [expr 0x4 << 16 ]
set 	AT91C_HDMA_SCSIZE_64                   [expr 0x5 << 16 ]
set 	AT91C_HDMA_SCSIZE_128                  [expr 0x6 << 16 ]
set 	AT91C_HDMA_SCSIZE_256                  [expr 0x7 << 16 ]
set AT91C_HDMA_DCSIZE     [expr 0x7 << 20 ]
set 	AT91C_HDMA_DCSIZE_1                    [expr 0x0 << 20 ]
set 	AT91C_HDMA_DCSIZE_4                    [expr 0x1 << 20 ]
set 	AT91C_HDMA_DCSIZE_8                    [expr 0x2 << 20 ]
set 	AT91C_HDMA_DCSIZE_16                   [expr 0x3 << 20 ]
set 	AT91C_HDMA_DCSIZE_32                   [expr 0x4 << 20 ]
set 	AT91C_HDMA_DCSIZE_64                   [expr 0x5 << 20 ]
set 	AT91C_HDMA_DCSIZE_128                  [expr 0x6 << 20 ]
set 	AT91C_HDMA_DCSIZE_256                  [expr 0x7 << 20 ]
set AT91C_HDMA_SRC_WIDTH  [expr 0x3 << 24 ]
set 	AT91C_HDMA_SRC_WIDTH_BYTE                 [expr 0x0 << 24 ]
set 	AT91C_HDMA_SRC_WIDTH_HALFWORD             [expr 0x1 << 24 ]
set 	AT91C_HDMA_SRC_WIDTH_WORD                 [expr 0x2 << 24 ]
set 	AT91C_HDMA_SRC_WIDTH_WORD                 [expr 0x3 << 24 ]
set AT91C_HDMA_DST_WIDTH  [expr 0x3 << 28 ]
set 	AT91C_HDMA_DST_WIDTH_BYTE                 [expr 0x0 << 28 ]
set 	AT91C_HDMA_DST_WIDTH_HALFWORD             [expr 0x1 << 28 ]
set 	AT91C_HDMA_DST_WIDTH_WORD                 [expr 0x2 << 28 ]
set 	AT91C_HDMA_DST_WIDTH_WORD                 [expr 0x3 << 28 ]
set AT91C_HDMA_DONE       [expr 0x1 << 31 ]
# -------- HDMA_CTRLB : (HDMA_CH Offset: 0x10)  -------- 
set AT91C_HDMA_SIF        [expr 0x3 <<  0 ]
set 	AT91C_HDMA_SIF_0                    0x0
set 	AT91C_HDMA_SIF_1                    0x1
set 	AT91C_HDMA_SIF_2                    0x2
set 	AT91C_HDMA_SIF_3                    0x3
set AT91C_HDMA_DIF        [expr 0x3 <<  4 ]
set 	AT91C_HDMA_DIF_0                    [expr 0x0 <<  4 ]
set 	AT91C_HDMA_DIF_1                    [expr 0x1 <<  4 ]
set 	AT91C_HDMA_DIF_2                    [expr 0x2 <<  4 ]
set 	AT91C_HDMA_DIF_3                    [expr 0x3 <<  4 ]
set AT91C_HDMA_SRC_PIP    [expr 0x1 <<  8 ]
set 	AT91C_HDMA_SRC_PIP_DISABLE              [expr 0x0 <<  8 ]
set 	AT91C_HDMA_SRC_PIP_ENABLE               [expr 0x1 <<  8 ]
set AT91C_HDMA_DST_PIP    [expr 0x1 << 12 ]
set 	AT91C_HDMA_DST_PIP_DISABLE              [expr 0x0 << 12 ]
set 	AT91C_HDMA_DST_PIP_ENABLE               [expr 0x1 << 12 ]
set AT91C_HDMA_SRC_DSCR   [expr 0x1 << 16 ]
set 	AT91C_HDMA_SRC_DSCR_FETCH_FROM_MEM       [expr 0x0 << 16 ]
set 	AT91C_HDMA_SRC_DSCR_FETCH_DISABLE        [expr 0x1 << 16 ]
set AT91C_HDMA_DST_DSCR   [expr 0x1 << 20 ]
set 	AT91C_HDMA_DST_DSCR_FETCH_FROM_MEM       [expr 0x0 << 20 ]
set 	AT91C_HDMA_DST_DSCR_FETCH_DISABLE        [expr 0x1 << 20 ]
set AT91C_HDMA_FC         [expr 0x7 << 21 ]
set 	AT91C_HDMA_FC_MEM2MEM              [expr 0x0 << 21 ]
set 	AT91C_HDMA_FC_MEM2PER              [expr 0x1 << 21 ]
set 	AT91C_HDMA_FC_PER2MEM              [expr 0x2 << 21 ]
set 	AT91C_HDMA_FC_PER2PER              [expr 0x3 << 21 ]
set 	AT91C_HDMA_FC_PER2MEM_PER          [expr 0x4 << 21 ]
set 	AT91C_HDMA_FC_MEM2PER_PER          [expr 0x5 << 21 ]
set 	AT91C_HDMA_FC_PER2PER_PER          [expr 0x6 << 21 ]
set 	AT91C_HDMA_FC_PER2PER_PER          [expr 0x7 << 21 ]
set AT91C_HDMA_SRC_ADDRESS_MODE [expr 0x3 << 24 ]
set 	AT91C_HDMA_SRC_ADDRESS_MODE_INCR                 [expr 0x0 << 24 ]
set 	AT91C_HDMA_SRC_ADDRESS_MODE_DECR                 [expr 0x1 << 24 ]
set 	AT91C_HDMA_SRC_ADDRESS_MODE_FIXED                [expr 0x2 << 24 ]
set AT91C_HDMA_DST_ADDRESS_MODE [expr 0x3 << 28 ]
set 	AT91C_HDMA_DST_ADDRESS_MODE_INCR                 [expr 0x0 << 28 ]
set 	AT91C_HDMA_DST_ADDRESS_MODE_DECR                 [expr 0x1 << 28 ]
set 	AT91C_HDMA_DST_ADDRESS_MODE_FIXED                [expr 0x2 << 28 ]
set AT91C_HDMA_AUTO       [expr 0x1 << 31 ]
set 	AT91C_HDMA_AUTO_DISABLE              [expr 0x0 << 31 ]
set 	AT91C_HDMA_AUTO_ENABLE               [expr 0x1 << 31 ]
# -------- HDMA_CFG : (HDMA_CH Offset: 0x14)  -------- 
set AT91C_HDMA_SRC_PER    [expr 0xF <<  0 ]
set 	AT91C_HDMA_SRC_PER_0                    0x0
set 	AT91C_HDMA_SRC_PER_1                    0x1
set 	AT91C_HDMA_SRC_PER_2                    0x2
set 	AT91C_HDMA_SRC_PER_3                    0x3
set 	AT91C_HDMA_SRC_PER_4                    0x4
set 	AT91C_HDMA_SRC_PER_5                    0x5
set 	AT91C_HDMA_SRC_PER_6                    0x6
set 	AT91C_HDMA_SRC_PER_7                    0x7
set 	AT91C_HDMA_SRC_PER_8                    0x8
set 	AT91C_HDMA_SRC_PER_9                    0x9
set 	AT91C_HDMA_SRC_PER_10                   0xA
set 	AT91C_HDMA_SRC_PER_11                   0xB
set 	AT91C_HDMA_SRC_PER_12                   0xC
set 	AT91C_HDMA_SRC_PER_13                   0xD
set 	AT91C_HDMA_SRC_PER_14                   0xE
set 	AT91C_HDMA_SRC_PER_15                   0xF
set AT91C_HDMA_DST_PER    [expr 0xF <<  4 ]
set 	AT91C_HDMA_DST_PER_0                    [expr 0x0 <<  4 ]
set 	AT91C_HDMA_DST_PER_1                    [expr 0x1 <<  4 ]
set 	AT91C_HDMA_DST_PER_2                    [expr 0x2 <<  4 ]
set 	AT91C_HDMA_DST_PER_3                    [expr 0x3 <<  4 ]
set 	AT91C_HDMA_DST_PER_4                    [expr 0x4 <<  4 ]
set 	AT91C_HDMA_DST_PER_5                    [expr 0x5 <<  4 ]
set 	AT91C_HDMA_DST_PER_6                    [expr 0x6 <<  4 ]
set 	AT91C_HDMA_DST_PER_7                    [expr 0x7 <<  4 ]
set 	AT91C_HDMA_DST_PER_8                    [expr 0x8 <<  4 ]
set 	AT91C_HDMA_DST_PER_9                    [expr 0x9 <<  4 ]
set 	AT91C_HDMA_DST_PER_10                   [expr 0xA <<  4 ]
set 	AT91C_HDMA_DST_PER_11                   [expr 0xB <<  4 ]
set 	AT91C_HDMA_DST_PER_12                   [expr 0xC <<  4 ]
set 	AT91C_HDMA_DST_PER_13                   [expr 0xD <<  4 ]
set 	AT91C_HDMA_DST_PER_14                   [expr 0xE <<  4 ]
set 	AT91C_HDMA_DST_PER_15                   [expr 0xF <<  4 ]
set AT91C_HDMA_SRC_REP    [expr 0x1 <<  8 ]
set 	AT91C_HDMA_SRC_REP_CONTIGUOUS_ADDR      [expr 0x0 <<  8 ]
set 	AT91C_HDMA_SRC_REP_RELOAD_ADDR          [expr 0x1 <<  8 ]
set AT91C_HDMA_SRC_H2SEL  [expr 0x1 <<  9 ]
set 	AT91C_HDMA_SRC_H2SEL_SW                   [expr 0x0 <<  9 ]
set 	AT91C_HDMA_SRC_H2SEL_HW                   [expr 0x1 <<  9 ]
set AT91C_HDMA_DST_REP    [expr 0x1 << 12 ]
set 	AT91C_HDMA_DST_REP_CONTIGUOUS_ADDR      [expr 0x0 << 12 ]
set 	AT91C_HDMA_DST_REP_RELOAD_ADDR          [expr 0x1 << 12 ]
set AT91C_HDMA_DST_H2SEL  [expr 0x1 << 13 ]
set 	AT91C_HDMA_DST_H2SEL_SW                   [expr 0x0 << 13 ]
set 	AT91C_HDMA_DST_H2SEL_HW                   [expr 0x1 << 13 ]
set AT91C_HDMA_SOD        [expr 0x1 << 16 ]
set 	AT91C_HDMA_SOD_DISABLE              [expr 0x0 << 16 ]
set 	AT91C_HDMA_SOD_ENABLE               [expr 0x1 << 16 ]
set AT91C_HDMA_LOCK_IF    [expr 0x1 << 20 ]
set 	AT91C_HDMA_LOCK_IF_DISABLE              [expr 0x0 << 20 ]
set 	AT91C_HDMA_LOCK_IF_ENABLE               [expr 0x1 << 20 ]
set AT91C_HDMA_LOCK_B     [expr 0x1 << 21 ]
set 	AT91C_HDMA_LOCK_B_DISABLE              [expr 0x0 << 21 ]
set 	AT91C_HDMA_LOCK_B_ENABLE               [expr 0x1 << 21 ]
set AT91C_HDMA_LOCK_IF_L  [expr 0x1 << 22 ]
set 	AT91C_HDMA_LOCK_IF_L_CHUNK                [expr 0x0 << 22 ]
set 	AT91C_HDMA_LOCK_IF_L_BUFFER               [expr 0x1 << 22 ]
set AT91C_HDMA_AHB_PROT   [expr 0x7 << 24 ]
set AT91C_HDMA_FIFOCFG    [expr 0x3 << 28 ]
set 	AT91C_HDMA_FIFOCFG_LARGESTBURST         [expr 0x0 << 28 ]
set 	AT91C_HDMA_FIFOCFG_HALFFIFO             [expr 0x1 << 28 ]
set 	AT91C_HDMA_FIFOCFG_ENOUGHSPACE          [expr 0x2 << 28 ]
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
set AT91C_HDMA_IF0_BIGEND [expr 0x1 <<  0 ]
set 	AT91C_HDMA_IF0_BIGEND_IS_LITTLE_ENDIAN     0x0
set 	AT91C_HDMA_IF0_BIGEND_IS_BIG_ENDIAN        0x1
set AT91C_HDMA_IF1_BIGEND [expr 0x1 <<  1 ]
set 	AT91C_HDMA_IF1_BIGEND_IS_LITTLE_ENDIAN     [expr 0x0 <<  1 ]
set 	AT91C_HDMA_IF1_BIGEND_IS_BIG_ENDIAN        [expr 0x1 <<  1 ]
set AT91C_HDMA_IF2_BIGEND [expr 0x1 <<  2 ]
set 	AT91C_HDMA_IF2_BIGEND_IS_LITTLE_ENDIAN     [expr 0x0 <<  2 ]
set 	AT91C_HDMA_IF2_BIGEND_IS_BIG_ENDIAN        [expr 0x1 <<  2 ]
set AT91C_HDMA_IF3_BIGEND [expr 0x1 <<  3 ]
set 	AT91C_HDMA_IF3_BIGEND_IS_LITTLE_ENDIAN     [expr 0x0 <<  3 ]
set 	AT91C_HDMA_IF3_BIGEND_IS_BIG_ENDIAN        [expr 0x1 <<  3 ]
set AT91C_HDMA_ARB_CFG    [expr 0x1 <<  4 ]
set 	AT91C_HDMA_ARB_CFG_FIXED                [expr 0x0 <<  4 ]
set 	AT91C_HDMA_ARB_CFG_ROUND_ROBIN          [expr 0x1 <<  4 ]
# -------- HDMA_EN : (HDMA Offset: 0x4)  -------- 
set AT91C_HDMA_ENABLE     [expr 0x1 <<  0 ]
set 	AT91C_HDMA_ENABLE_DISABLE              0x0
set 	AT91C_HDMA_ENABLE_ENABLE               0x1
# -------- HDMA_SREQ : (HDMA Offset: 0x8)  -------- 
set AT91C_HDMA_SSREQ0     [expr 0x1 <<  0 ]
set 	AT91C_HDMA_SSREQ0_0                    0x0
set 	AT91C_HDMA_SSREQ0_1                    0x1
set AT91C_HDMA_DSREQ0     [expr 0x1 <<  1 ]
set 	AT91C_HDMA_DSREQ0_0                    [expr 0x0 <<  1 ]
set 	AT91C_HDMA_DSREQ0_1                    [expr 0x1 <<  1 ]
set AT91C_HDMA_SSREQ1     [expr 0x1 <<  2 ]
set 	AT91C_HDMA_SSREQ1_0                    [expr 0x0 <<  2 ]
set 	AT91C_HDMA_SSREQ1_1                    [expr 0x1 <<  2 ]
set AT91C_HDMA_DSREQ1     [expr 0x1 <<  3 ]
set 	AT91C_HDMA_DSREQ1_0                    [expr 0x0 <<  3 ]
set 	AT91C_HDMA_DSREQ1_1                    [expr 0x1 <<  3 ]
set AT91C_HDMA_SSREQ2     [expr 0x1 <<  4 ]
set 	AT91C_HDMA_SSREQ2_0                    [expr 0x0 <<  4 ]
set 	AT91C_HDMA_SSREQ2_1                    [expr 0x1 <<  4 ]
set AT91C_HDMA_DSREQ2     [expr 0x1 <<  5 ]
set 	AT91C_HDMA_DSREQ2_0                    [expr 0x0 <<  5 ]
set 	AT91C_HDMA_DSREQ2_1                    [expr 0x1 <<  5 ]
set AT91C_HDMA_SSREQ3     [expr 0x1 <<  6 ]
set 	AT91C_HDMA_SSREQ3_0                    [expr 0x0 <<  6 ]
set 	AT91C_HDMA_SSREQ3_1                    [expr 0x1 <<  6 ]
set AT91C_HDMA_DSREQ3     [expr 0x1 <<  7 ]
set 	AT91C_HDMA_DSREQ3_0                    [expr 0x0 <<  7 ]
set 	AT91C_HDMA_DSREQ3_1                    [expr 0x1 <<  7 ]
set AT91C_HDMA_SSREQ4     [expr 0x1 <<  8 ]
set 	AT91C_HDMA_SSREQ4_0                    [expr 0x0 <<  8 ]
set 	AT91C_HDMA_SSREQ4_1                    [expr 0x1 <<  8 ]
set AT91C_HDMA_DSREQ4     [expr 0x1 <<  9 ]
set 	AT91C_HDMA_DSREQ4_0                    [expr 0x0 <<  9 ]
set 	AT91C_HDMA_DSREQ4_1                    [expr 0x1 <<  9 ]
set AT91C_HDMA_SSREQ5     [expr 0x1 << 10 ]
set 	AT91C_HDMA_SSREQ5_0                    [expr 0x0 << 10 ]
set 	AT91C_HDMA_SSREQ5_1                    [expr 0x1 << 10 ]
set AT91C_HDMA_DSREQ6     [expr 0x1 << 11 ]
set 	AT91C_HDMA_DSREQ6_0                    [expr 0x0 << 11 ]
set 	AT91C_HDMA_DSREQ6_1                    [expr 0x1 << 11 ]
set AT91C_HDMA_SSREQ6     [expr 0x1 << 12 ]
set 	AT91C_HDMA_SSREQ6_0                    [expr 0x0 << 12 ]
set 	AT91C_HDMA_SSREQ6_1                    [expr 0x1 << 12 ]
set AT91C_HDMA_DSREQ6     [expr 0x1 << 13 ]
set 	AT91C_HDMA_DSREQ6_0                    [expr 0x0 << 13 ]
set 	AT91C_HDMA_DSREQ6_1                    [expr 0x1 << 13 ]
set AT91C_HDMA_SSREQ7     [expr 0x1 << 14 ]
set 	AT91C_HDMA_SSREQ7_0                    [expr 0x0 << 14 ]
set 	AT91C_HDMA_SSREQ7_1                    [expr 0x1 << 14 ]
set AT91C_HDMA_DSREQ7     [expr 0x1 << 15 ]
set 	AT91C_HDMA_DSREQ7_0                    [expr 0x0 << 15 ]
set 	AT91C_HDMA_DSREQ7_1                    [expr 0x1 << 15 ]
# -------- HDMA_CREQ : (HDMA Offset: 0xc)  -------- 
set AT91C_HDMA_SCREQ0     [expr 0x1 <<  0 ]
set 	AT91C_HDMA_SCREQ0_0                    0x0
set 	AT91C_HDMA_SCREQ0_1                    0x1
set AT91C_HDMA_DCREQ0     [expr 0x1 <<  1 ]
set 	AT91C_HDMA_DCREQ0_0                    [expr 0x0 <<  1 ]
set 	AT91C_HDMA_DCREQ0_1                    [expr 0x1 <<  1 ]
set AT91C_HDMA_SCREQ1     [expr 0x1 <<  2 ]
set 	AT91C_HDMA_SCREQ1_0                    [expr 0x0 <<  2 ]
set 	AT91C_HDMA_SCREQ1_1                    [expr 0x1 <<  2 ]
set AT91C_HDMA_DCREQ1     [expr 0x1 <<  3 ]
set 	AT91C_HDMA_DCREQ1_0                    [expr 0x0 <<  3 ]
set 	AT91C_HDMA_DCREQ1_1                    [expr 0x1 <<  3 ]
set AT91C_HDMA_SCREQ2     [expr 0x1 <<  4 ]
set 	AT91C_HDMA_SCREQ2_0                    [expr 0x0 <<  4 ]
set 	AT91C_HDMA_SCREQ2_1                    [expr 0x1 <<  4 ]
set AT91C_HDMA_DCREQ2     [expr 0x1 <<  5 ]
set 	AT91C_HDMA_DCREQ2_0                    [expr 0x0 <<  5 ]
set 	AT91C_HDMA_DCREQ2_1                    [expr 0x1 <<  5 ]
set AT91C_HDMA_SCREQ3     [expr 0x1 <<  6 ]
set 	AT91C_HDMA_SCREQ3_0                    [expr 0x0 <<  6 ]
set 	AT91C_HDMA_SCREQ3_1                    [expr 0x1 <<  6 ]
set AT91C_HDMA_DCREQ3     [expr 0x1 <<  7 ]
set 	AT91C_HDMA_DCREQ3_0                    [expr 0x0 <<  7 ]
set 	AT91C_HDMA_DCREQ3_1                    [expr 0x1 <<  7 ]
set AT91C_HDMA_SCREQ4     [expr 0x1 <<  8 ]
set 	AT91C_HDMA_SCREQ4_0                    [expr 0x0 <<  8 ]
set 	AT91C_HDMA_SCREQ4_1                    [expr 0x1 <<  8 ]
set AT91C_HDMA_DCREQ4     [expr 0x1 <<  9 ]
set 	AT91C_HDMA_DCREQ4_0                    [expr 0x0 <<  9 ]
set 	AT91C_HDMA_DCREQ4_1                    [expr 0x1 <<  9 ]
set AT91C_HDMA_SCREQ5     [expr 0x1 << 10 ]
set 	AT91C_HDMA_SCREQ5_0                    [expr 0x0 << 10 ]
set 	AT91C_HDMA_SCREQ5_1                    [expr 0x1 << 10 ]
set AT91C_HDMA_DCREQ6     [expr 0x1 << 11 ]
set 	AT91C_HDMA_DCREQ6_0                    [expr 0x0 << 11 ]
set 	AT91C_HDMA_DCREQ6_1                    [expr 0x1 << 11 ]
set AT91C_HDMA_SCREQ6     [expr 0x1 << 12 ]
set 	AT91C_HDMA_SCREQ6_0                    [expr 0x0 << 12 ]
set 	AT91C_HDMA_SCREQ6_1                    [expr 0x1 << 12 ]
set AT91C_HDMA_DCREQ6     [expr 0x1 << 13 ]
set 	AT91C_HDMA_DCREQ6_0                    [expr 0x0 << 13 ]
set 	AT91C_HDMA_DCREQ6_1                    [expr 0x1 << 13 ]
set AT91C_HDMA_SCREQ7     [expr 0x1 << 14 ]
set 	AT91C_HDMA_SCREQ7_0                    [expr 0x0 << 14 ]
set 	AT91C_HDMA_SCREQ7_1                    [expr 0x1 << 14 ]
set AT91C_HDMA_DCREQ7     [expr 0x1 << 15 ]
set 	AT91C_HDMA_DCREQ7_0                    [expr 0x0 << 15 ]
set 	AT91C_HDMA_DCREQ7_1                    [expr 0x1 << 15 ]
# -------- HDMA_LAST : (HDMA Offset: 0x10)  -------- 
set AT91C_HDMA_SLAST0     [expr 0x1 <<  0 ]
set 	AT91C_HDMA_SLAST0_0                    0x0
set 	AT91C_HDMA_SLAST0_1                    0x1
set AT91C_HDMA_DLAST0     [expr 0x1 <<  1 ]
set 	AT91C_HDMA_DLAST0_0                    [expr 0x0 <<  1 ]
set 	AT91C_HDMA_DLAST0_1                    [expr 0x1 <<  1 ]
set AT91C_HDMA_SLAST1     [expr 0x1 <<  2 ]
set 	AT91C_HDMA_SLAST1_0                    [expr 0x0 <<  2 ]
set 	AT91C_HDMA_SLAST1_1                    [expr 0x1 <<  2 ]
set AT91C_HDMA_DLAST1     [expr 0x1 <<  3 ]
set 	AT91C_HDMA_DLAST1_0                    [expr 0x0 <<  3 ]
set 	AT91C_HDMA_DLAST1_1                    [expr 0x1 <<  3 ]
set AT91C_HDMA_SLAST2     [expr 0x1 <<  4 ]
set 	AT91C_HDMA_SLAST2_0                    [expr 0x0 <<  4 ]
set 	AT91C_HDMA_SLAST2_1                    [expr 0x1 <<  4 ]
set AT91C_HDMA_DLAST2     [expr 0x1 <<  5 ]
set 	AT91C_HDMA_DLAST2_0                    [expr 0x0 <<  5 ]
set 	AT91C_HDMA_DLAST2_1                    [expr 0x1 <<  5 ]
set AT91C_HDMA_SLAST3     [expr 0x1 <<  6 ]
set 	AT91C_HDMA_SLAST3_0                    [expr 0x0 <<  6 ]
set 	AT91C_HDMA_SLAST3_1                    [expr 0x1 <<  6 ]
set AT91C_HDMA_DLAST3     [expr 0x1 <<  7 ]
set 	AT91C_HDMA_DLAST3_0                    [expr 0x0 <<  7 ]
set 	AT91C_HDMA_DLAST3_1                    [expr 0x1 <<  7 ]
set AT91C_HDMA_SLAST4     [expr 0x1 <<  8 ]
set 	AT91C_HDMA_SLAST4_0                    [expr 0x0 <<  8 ]
set 	AT91C_HDMA_SLAST4_1                    [expr 0x1 <<  8 ]
set AT91C_HDMA_DLAST4     [expr 0x1 <<  9 ]
set 	AT91C_HDMA_DLAST4_0                    [expr 0x0 <<  9 ]
set 	AT91C_HDMA_DLAST4_1                    [expr 0x1 <<  9 ]
set AT91C_HDMA_SLAST5     [expr 0x1 << 10 ]
set 	AT91C_HDMA_SLAST5_0                    [expr 0x0 << 10 ]
set 	AT91C_HDMA_SLAST5_1                    [expr 0x1 << 10 ]
set AT91C_HDMA_DLAST6     [expr 0x1 << 11 ]
set 	AT91C_HDMA_DLAST6_0                    [expr 0x0 << 11 ]
set 	AT91C_HDMA_DLAST6_1                    [expr 0x1 << 11 ]
set AT91C_HDMA_SLAST6     [expr 0x1 << 12 ]
set 	AT91C_HDMA_SLAST6_0                    [expr 0x0 << 12 ]
set 	AT91C_HDMA_SLAST6_1                    [expr 0x1 << 12 ]
set AT91C_HDMA_DLAST6     [expr 0x1 << 13 ]
set 	AT91C_HDMA_DLAST6_0                    [expr 0x0 << 13 ]
set 	AT91C_HDMA_DLAST6_1                    [expr 0x1 << 13 ]
set AT91C_HDMA_SLAST7     [expr 0x1 << 14 ]
set 	AT91C_HDMA_SLAST7_0                    [expr 0x0 << 14 ]
set 	AT91C_HDMA_SLAST7_1                    [expr 0x1 << 14 ]
set AT91C_HDMA_DLAST7     [expr 0x1 << 15 ]
set 	AT91C_HDMA_DLAST7_0                    [expr 0x0 << 15 ]
set 	AT91C_HDMA_DLAST7_1                    [expr 0x1 << 15 ]
# -------- HDMA_SYNC : (HDMA Offset: 0x14)  -------- 
set AT91C_SYNC_REQ        [expr 0xFFFF <<  0 ]
# -------- HDMA_EBCIER : (HDMA Offset: 0x18) Buffer Transfer Completed/Chained Buffer Transfer Completed/Access Error Interrupt Enable Register -------- 
set AT91C_HDMA_BTC0       [expr 0x1 <<  0 ]
set AT91C_HDMA_BTC1       [expr 0x1 <<  1 ]
set AT91C_HDMA_BTC2       [expr 0x1 <<  2 ]
set AT91C_HDMA_BTC3       [expr 0x1 <<  3 ]
set AT91C_HDMA_BTC4       [expr 0x1 <<  4 ]
set AT91C_HDMA_BTC5       [expr 0x1 <<  5 ]
set AT91C_HDMA_BTC6       [expr 0x1 <<  6 ]
set AT91C_HDMA_BTC7       [expr 0x1 <<  7 ]
set AT91C_HDMA_CBTC0      [expr 0x1 <<  8 ]
set AT91C_HDMA_CBTC1      [expr 0x1 <<  9 ]
set AT91C_HDMA_CBTC2      [expr 0x1 << 10 ]
set AT91C_HDMA_CBTC3      [expr 0x1 << 11 ]
set AT91C_HDMA_CBTC4      [expr 0x1 << 12 ]
set AT91C_HDMA_CBTC5      [expr 0x1 << 13 ]
set AT91C_HDMA_CBTC6      [expr 0x1 << 14 ]
set AT91C_HDMA_CBTC7      [expr 0x1 << 15 ]
set AT91C_HDMA_ERR0       [expr 0x1 << 16 ]
set AT91C_HDMA_ERR1       [expr 0x1 << 17 ]
set AT91C_HDMA_ERR2       [expr 0x1 << 18 ]
set AT91C_HDMA_ERR3       [expr 0x1 << 19 ]
set AT91C_HDMA_ERR4       [expr 0x1 << 20 ]
set AT91C_HDMA_ERR5       [expr 0x1 << 21 ]
set AT91C_HDMA_ERR6       [expr 0x1 << 22 ]
set AT91C_HDMA_ERR7       [expr 0x1 << 23 ]
# -------- HDMA_EBCIDR : (HDMA Offset: 0x1c)  -------- 
set AT91C_HDMA_BTC0       [expr 0x1 <<  0 ]
set AT91C_HDMA_BTC1       [expr 0x1 <<  1 ]
set AT91C_HDMA_BTC2       [expr 0x1 <<  2 ]
set AT91C_HDMA_BTC3       [expr 0x1 <<  3 ]
set AT91C_HDMA_BTC4       [expr 0x1 <<  4 ]
set AT91C_HDMA_BTC5       [expr 0x1 <<  5 ]
set AT91C_HDMA_BTC6       [expr 0x1 <<  6 ]
set AT91C_HDMA_BTC7       [expr 0x1 <<  7 ]
set AT91C_HDMA_CBTC0      [expr 0x1 <<  8 ]
set AT91C_HDMA_CBTC1      [expr 0x1 <<  9 ]
set AT91C_HDMA_CBTC2      [expr 0x1 << 10 ]
set AT91C_HDMA_CBTC3      [expr 0x1 << 11 ]
set AT91C_HDMA_CBTC4      [expr 0x1 << 12 ]
set AT91C_HDMA_CBTC5      [expr 0x1 << 13 ]
set AT91C_HDMA_CBTC6      [expr 0x1 << 14 ]
set AT91C_HDMA_CBTC7      [expr 0x1 << 15 ]
set AT91C_HDMA_ERR0       [expr 0x1 << 16 ]
set AT91C_HDMA_ERR1       [expr 0x1 << 17 ]
set AT91C_HDMA_ERR2       [expr 0x1 << 18 ]
set AT91C_HDMA_ERR3       [expr 0x1 << 19 ]
set AT91C_HDMA_ERR4       [expr 0x1 << 20 ]
set AT91C_HDMA_ERR5       [expr 0x1 << 21 ]
set AT91C_HDMA_ERR6       [expr 0x1 << 22 ]
set AT91C_HDMA_ERR7       [expr 0x1 << 23 ]
# -------- HDMA_EBCIMR : (HDMA Offset: 0x20)  -------- 
set AT91C_HDMA_BTC0       [expr 0x1 <<  0 ]
set AT91C_HDMA_BTC1       [expr 0x1 <<  1 ]
set AT91C_HDMA_BTC2       [expr 0x1 <<  2 ]
set AT91C_HDMA_BTC3       [expr 0x1 <<  3 ]
set AT91C_HDMA_BTC4       [expr 0x1 <<  4 ]
set AT91C_HDMA_BTC5       [expr 0x1 <<  5 ]
set AT91C_HDMA_BTC6       [expr 0x1 <<  6 ]
set AT91C_HDMA_BTC7       [expr 0x1 <<  7 ]
set AT91C_HDMA_CBTC0      [expr 0x1 <<  8 ]
set AT91C_HDMA_CBTC1      [expr 0x1 <<  9 ]
set AT91C_HDMA_CBTC2      [expr 0x1 << 10 ]
set AT91C_HDMA_CBTC3      [expr 0x1 << 11 ]
set AT91C_HDMA_CBTC4      [expr 0x1 << 12 ]
set AT91C_HDMA_CBTC5      [expr 0x1 << 13 ]
set AT91C_HDMA_CBTC6      [expr 0x1 << 14 ]
set AT91C_HDMA_CBTC7      [expr 0x1 << 15 ]
set AT91C_HDMA_ERR0       [expr 0x1 << 16 ]
set AT91C_HDMA_ERR1       [expr 0x1 << 17 ]
set AT91C_HDMA_ERR2       [expr 0x1 << 18 ]
set AT91C_HDMA_ERR3       [expr 0x1 << 19 ]
set AT91C_HDMA_ERR4       [expr 0x1 << 20 ]
set AT91C_HDMA_ERR5       [expr 0x1 << 21 ]
set AT91C_HDMA_ERR6       [expr 0x1 << 22 ]
set AT91C_HDMA_ERR7       [expr 0x1 << 23 ]
# -------- HDMA_EBCISR : (HDMA Offset: 0x24)  -------- 
set AT91C_HDMA_BTC0       [expr 0x1 <<  0 ]
set AT91C_HDMA_BTC1       [expr 0x1 <<  1 ]
set AT91C_HDMA_BTC2       [expr 0x1 <<  2 ]
set AT91C_HDMA_BTC3       [expr 0x1 <<  3 ]
set AT91C_HDMA_BTC4       [expr 0x1 <<  4 ]
set AT91C_HDMA_BTC5       [expr 0x1 <<  5 ]
set AT91C_HDMA_BTC6       [expr 0x1 <<  6 ]
set AT91C_HDMA_BTC7       [expr 0x1 <<  7 ]
set AT91C_HDMA_CBTC0      [expr 0x1 <<  8 ]
set AT91C_HDMA_CBTC1      [expr 0x1 <<  9 ]
set AT91C_HDMA_CBTC2      [expr 0x1 << 10 ]
set AT91C_HDMA_CBTC3      [expr 0x1 << 11 ]
set AT91C_HDMA_CBTC4      [expr 0x1 << 12 ]
set AT91C_HDMA_CBTC5      [expr 0x1 << 13 ]
set AT91C_HDMA_CBTC6      [expr 0x1 << 14 ]
set AT91C_HDMA_CBTC7      [expr 0x1 << 15 ]
set AT91C_HDMA_ERR0       [expr 0x1 << 16 ]
set AT91C_HDMA_ERR1       [expr 0x1 << 17 ]
set AT91C_HDMA_ERR2       [expr 0x1 << 18 ]
set AT91C_HDMA_ERR3       [expr 0x1 << 19 ]
set AT91C_HDMA_ERR4       [expr 0x1 << 20 ]
set AT91C_HDMA_ERR5       [expr 0x1 << 21 ]
set AT91C_HDMA_ERR6       [expr 0x1 << 22 ]
set AT91C_HDMA_ERR7       [expr 0x1 << 23 ]
# -------- HDMA_CHER : (HDMA Offset: 0x28)  -------- 
set AT91C_HDMA_ENA0       [expr 0x1 <<  0 ]
set 	AT91C_HDMA_ENA0_0                    0x0
set 	AT91C_HDMA_ENA0_1                    0x1
set AT91C_HDMA_ENA1       [expr 0x1 <<  1 ]
set 	AT91C_HDMA_ENA1_0                    [expr 0x0 <<  1 ]
set 	AT91C_HDMA_ENA1_1                    [expr 0x1 <<  1 ]
set AT91C_HDMA_ENA2       [expr 0x1 <<  2 ]
set 	AT91C_HDMA_ENA2_0                    [expr 0x0 <<  2 ]
set 	AT91C_HDMA_ENA2_1                    [expr 0x1 <<  2 ]
set AT91C_HDMA_ENA3       [expr 0x1 <<  3 ]
set 	AT91C_HDMA_ENA3_0                    [expr 0x0 <<  3 ]
set 	AT91C_HDMA_ENA3_1                    [expr 0x1 <<  3 ]
set AT91C_HDMA_ENA4       [expr 0x1 <<  4 ]
set 	AT91C_HDMA_ENA4_0                    [expr 0x0 <<  4 ]
set 	AT91C_HDMA_ENA4_1                    [expr 0x1 <<  4 ]
set AT91C_HDMA_ENA5       [expr 0x1 <<  5 ]
set 	AT91C_HDMA_ENA5_0                    [expr 0x0 <<  5 ]
set 	AT91C_HDMA_ENA5_1                    [expr 0x1 <<  5 ]
set AT91C_HDMA_ENA6       [expr 0x1 <<  6 ]
set 	AT91C_HDMA_ENA6_0                    [expr 0x0 <<  6 ]
set 	AT91C_HDMA_ENA6_1                    [expr 0x1 <<  6 ]
set AT91C_HDMA_ENA7       [expr 0x1 <<  7 ]
set 	AT91C_HDMA_ENA7_0                    [expr 0x0 <<  7 ]
set 	AT91C_HDMA_ENA7_1                    [expr 0x1 <<  7 ]
set AT91C_HDMA_SUSP0      [expr 0x1 <<  8 ]
set 	AT91C_HDMA_SUSP0_0                    [expr 0x0 <<  8 ]
set 	AT91C_HDMA_SUSP0_1                    [expr 0x1 <<  8 ]
set AT91C_HDMA_SUSP1      [expr 0x1 <<  9 ]
set 	AT91C_HDMA_SUSP1_0                    [expr 0x0 <<  9 ]
set 	AT91C_HDMA_SUSP1_1                    [expr 0x1 <<  9 ]
set AT91C_HDMA_SUSP2      [expr 0x1 << 10 ]
set 	AT91C_HDMA_SUSP2_0                    [expr 0x0 << 10 ]
set 	AT91C_HDMA_SUSP2_1                    [expr 0x1 << 10 ]
set AT91C_HDMA_SUSP3      [expr 0x1 << 11 ]
set 	AT91C_HDMA_SUSP3_0                    [expr 0x0 << 11 ]
set 	AT91C_HDMA_SUSP3_1                    [expr 0x1 << 11 ]
set AT91C_HDMA_SUSP4      [expr 0x1 << 12 ]
set 	AT91C_HDMA_SUSP4_0                    [expr 0x0 << 12 ]
set 	AT91C_HDMA_SUSP4_1                    [expr 0x1 << 12 ]
set AT91C_HDMA_SUSP5      [expr 0x1 << 13 ]
set 	AT91C_HDMA_SUSP5_0                    [expr 0x0 << 13 ]
set 	AT91C_HDMA_SUSP5_1                    [expr 0x1 << 13 ]
set AT91C_HDMA_SUSP6      [expr 0x1 << 14 ]
set 	AT91C_HDMA_SUSP6_0                    [expr 0x0 << 14 ]
set 	AT91C_HDMA_SUSP6_1                    [expr 0x1 << 14 ]
set AT91C_HDMA_SUSP7      [expr 0x1 << 15 ]
set 	AT91C_HDMA_SUSP7_0                    [expr 0x0 << 15 ]
set 	AT91C_HDMA_SUSP7_1                    [expr 0x1 << 15 ]
set AT91C_HDMA_KEEP0      [expr 0x1 << 24 ]
set 	AT91C_HDMA_KEEP0_0                    [expr 0x0 << 24 ]
set 	AT91C_HDMA_KEEP0_1                    [expr 0x1 << 24 ]
set AT91C_HDMA_KEEP1      [expr 0x1 << 25 ]
set 	AT91C_HDMA_KEEP1_0                    [expr 0x0 << 25 ]
set 	AT91C_HDMA_KEEP1_1                    [expr 0x1 << 25 ]
set AT91C_HDMA_KEEP2      [expr 0x1 << 26 ]
set 	AT91C_HDMA_KEEP2_0                    [expr 0x0 << 26 ]
set 	AT91C_HDMA_KEEP2_1                    [expr 0x1 << 26 ]
set AT91C_HDMA_KEEP3      [expr 0x1 << 27 ]
set 	AT91C_HDMA_KEEP3_0                    [expr 0x0 << 27 ]
set 	AT91C_HDMA_KEEP3_1                    [expr 0x1 << 27 ]
set AT91C_HDMA_KEEP4      [expr 0x1 << 28 ]
set 	AT91C_HDMA_KEEP4_0                    [expr 0x0 << 28 ]
set 	AT91C_HDMA_KEEP4_1                    [expr 0x1 << 28 ]
set AT91C_HDMA_KEEP5      [expr 0x1 << 29 ]
set 	AT91C_HDMA_KEEP5_0                    [expr 0x0 << 29 ]
set 	AT91C_HDMA_KEEP5_1                    [expr 0x1 << 29 ]
set AT91C_HDMA_KEEP6      [expr 0x1 << 30 ]
set 	AT91C_HDMA_KEEP6_0                    [expr 0x0 << 30 ]
set 	AT91C_HDMA_KEEP6_1                    [expr 0x1 << 30 ]
set AT91C_HDMA_KEEP7      [expr 0x1 << 31 ]
set 	AT91C_HDMA_KEEP7_0                    [expr 0x0 << 31 ]
set 	AT91C_HDMA_KEEP7_1                    [expr 0x1 << 31 ]
# -------- HDMA_CHDR : (HDMA Offset: 0x2c)  -------- 
set AT91C_HDMA_DIS0       [expr 0x1 <<  0 ]
set 	AT91C_HDMA_DIS0_0                    0x0
set 	AT91C_HDMA_DIS0_1                    0x1
set AT91C_HDMA_DIS1       [expr 0x1 <<  1 ]
set 	AT91C_HDMA_DIS1_0                    [expr 0x0 <<  1 ]
set 	AT91C_HDMA_DIS1_1                    [expr 0x1 <<  1 ]
set AT91C_HDMA_DIS2       [expr 0x1 <<  2 ]
set 	AT91C_HDMA_DIS2_0                    [expr 0x0 <<  2 ]
set 	AT91C_HDMA_DIS2_1                    [expr 0x1 <<  2 ]
set AT91C_HDMA_DIS3       [expr 0x1 <<  3 ]
set 	AT91C_HDMA_DIS3_0                    [expr 0x0 <<  3 ]
set 	AT91C_HDMA_DIS3_1                    [expr 0x1 <<  3 ]
set AT91C_HDMA_DIS4       [expr 0x1 <<  4 ]
set 	AT91C_HDMA_DIS4_0                    [expr 0x0 <<  4 ]
set 	AT91C_HDMA_DIS4_1                    [expr 0x1 <<  4 ]
set AT91C_HDMA_DIS5       [expr 0x1 <<  5 ]
set 	AT91C_HDMA_DIS5_0                    [expr 0x0 <<  5 ]
set 	AT91C_HDMA_DIS5_1                    [expr 0x1 <<  5 ]
set AT91C_HDMA_DIS6       [expr 0x1 <<  6 ]
set 	AT91C_HDMA_DIS6_0                    [expr 0x0 <<  6 ]
set 	AT91C_HDMA_DIS6_1                    [expr 0x1 <<  6 ]
set AT91C_HDMA_DIS7       [expr 0x1 <<  7 ]
set 	AT91C_HDMA_DIS7_0                    [expr 0x0 <<  7 ]
set 	AT91C_HDMA_DIS7_1                    [expr 0x1 <<  7 ]
set AT91C_HDMA_RES0       [expr 0x1 <<  8 ]
set 	AT91C_HDMA_RES0_0                    [expr 0x0 <<  8 ]
set 	AT91C_HDMA_RES0_1                    [expr 0x1 <<  8 ]
set AT91C_HDMA_RES1       [expr 0x1 <<  9 ]
set 	AT91C_HDMA_RES1_0                    [expr 0x0 <<  9 ]
set 	AT91C_HDMA_RES1_1                    [expr 0x1 <<  9 ]
set AT91C_HDMA_RES2       [expr 0x1 << 10 ]
set 	AT91C_HDMA_RES2_0                    [expr 0x0 << 10 ]
set 	AT91C_HDMA_RES2_1                    [expr 0x1 << 10 ]
set AT91C_HDMA_RES3       [expr 0x1 << 11 ]
set 	AT91C_HDMA_RES3_0                    [expr 0x0 << 11 ]
set 	AT91C_HDMA_RES3_1                    [expr 0x1 << 11 ]
set AT91C_HDMA_RES4       [expr 0x1 << 12 ]
set 	AT91C_HDMA_RES4_0                    [expr 0x0 << 12 ]
set 	AT91C_HDMA_RES4_1                    [expr 0x1 << 12 ]
set AT91C_HDMA_RES5       [expr 0x1 << 13 ]
set 	AT91C_HDMA_RES5_0                    [expr 0x0 << 13 ]
set 	AT91C_HDMA_RES5_1                    [expr 0x1 << 13 ]
set AT91C_HDMA_RES6       [expr 0x1 << 14 ]
set 	AT91C_HDMA_RES6_0                    [expr 0x0 << 14 ]
set 	AT91C_HDMA_RES6_1                    [expr 0x1 << 14 ]
set AT91C_HDMA_RES7       [expr 0x1 << 15 ]
set 	AT91C_HDMA_RES7_0                    [expr 0x0 << 15 ]
set 	AT91C_HDMA_RES7_1                    [expr 0x1 << 15 ]
# -------- HDMA_CHSR : (HDMA Offset: 0x30)  -------- 
set AT91C_HDMA_ENA0       [expr 0x1 <<  0 ]
set 	AT91C_HDMA_ENA0_0                    0x0
set 	AT91C_HDMA_ENA0_1                    0x1
set AT91C_HDMA_ENA1       [expr 0x1 <<  1 ]
set 	AT91C_HDMA_ENA1_0                    [expr 0x0 <<  1 ]
set 	AT91C_HDMA_ENA1_1                    [expr 0x1 <<  1 ]
set AT91C_HDMA_ENA2       [expr 0x1 <<  2 ]
set 	AT91C_HDMA_ENA2_0                    [expr 0x0 <<  2 ]
set 	AT91C_HDMA_ENA2_1                    [expr 0x1 <<  2 ]
set AT91C_HDMA_ENA3       [expr 0x1 <<  3 ]
set 	AT91C_HDMA_ENA3_0                    [expr 0x0 <<  3 ]
set 	AT91C_HDMA_ENA3_1                    [expr 0x1 <<  3 ]
set AT91C_HDMA_ENA4       [expr 0x1 <<  4 ]
set 	AT91C_HDMA_ENA4_0                    [expr 0x0 <<  4 ]
set 	AT91C_HDMA_ENA4_1                    [expr 0x1 <<  4 ]
set AT91C_HDMA_ENA5       [expr 0x1 <<  5 ]
set 	AT91C_HDMA_ENA5_0                    [expr 0x0 <<  5 ]
set 	AT91C_HDMA_ENA5_1                    [expr 0x1 <<  5 ]
set AT91C_HDMA_ENA6       [expr 0x1 <<  6 ]
set 	AT91C_HDMA_ENA6_0                    [expr 0x0 <<  6 ]
set 	AT91C_HDMA_ENA6_1                    [expr 0x1 <<  6 ]
set AT91C_HDMA_ENA7       [expr 0x1 <<  7 ]
set 	AT91C_HDMA_ENA7_0                    [expr 0x0 <<  7 ]
set 	AT91C_HDMA_ENA7_1                    [expr 0x1 <<  7 ]
set AT91C_HDMA_SUSP0      [expr 0x1 <<  8 ]
set 	AT91C_HDMA_SUSP0_0                    [expr 0x0 <<  8 ]
set 	AT91C_HDMA_SUSP0_1                    [expr 0x1 <<  8 ]
set AT91C_HDMA_SUSP1      [expr 0x1 <<  9 ]
set 	AT91C_HDMA_SUSP1_0                    [expr 0x0 <<  9 ]
set 	AT91C_HDMA_SUSP1_1                    [expr 0x1 <<  9 ]
set AT91C_HDMA_SUSP2      [expr 0x1 << 10 ]
set 	AT91C_HDMA_SUSP2_0                    [expr 0x0 << 10 ]
set 	AT91C_HDMA_SUSP2_1                    [expr 0x1 << 10 ]
set AT91C_HDMA_SUSP3      [expr 0x1 << 11 ]
set 	AT91C_HDMA_SUSP3_0                    [expr 0x0 << 11 ]
set 	AT91C_HDMA_SUSP3_1                    [expr 0x1 << 11 ]
set AT91C_HDMA_SUSP4      [expr 0x1 << 12 ]
set 	AT91C_HDMA_SUSP4_0                    [expr 0x0 << 12 ]
set 	AT91C_HDMA_SUSP4_1                    [expr 0x1 << 12 ]
set AT91C_HDMA_SUSP5      [expr 0x1 << 13 ]
set 	AT91C_HDMA_SUSP5_0                    [expr 0x0 << 13 ]
set 	AT91C_HDMA_SUSP5_1                    [expr 0x1 << 13 ]
set AT91C_HDMA_SUSP6      [expr 0x1 << 14 ]
set 	AT91C_HDMA_SUSP6_0                    [expr 0x0 << 14 ]
set 	AT91C_HDMA_SUSP6_1                    [expr 0x1 << 14 ]
set AT91C_HDMA_SUSP7      [expr 0x1 << 15 ]
set 	AT91C_HDMA_SUSP7_0                    [expr 0x0 << 15 ]
set 	AT91C_HDMA_SUSP7_1                    [expr 0x1 << 15 ]
set AT91C_HDMA_EMPT0      [expr 0x1 << 16 ]
set 	AT91C_HDMA_EMPT0_0                    [expr 0x0 << 16 ]
set 	AT91C_HDMA_EMPT0_1                    [expr 0x1 << 16 ]
set AT91C_HDMA_EMPT1      [expr 0x1 << 17 ]
set 	AT91C_HDMA_EMPT1_0                    [expr 0x0 << 17 ]
set 	AT91C_HDMA_EMPT1_1                    [expr 0x1 << 17 ]
set AT91C_HDMA_EMPT2      [expr 0x1 << 18 ]
set 	AT91C_HDMA_EMPT2_0                    [expr 0x0 << 18 ]
set 	AT91C_HDMA_EMPT2_1                    [expr 0x1 << 18 ]
set AT91C_HDMA_EMPT3      [expr 0x1 << 19 ]
set 	AT91C_HDMA_EMPT3_0                    [expr 0x0 << 19 ]
set 	AT91C_HDMA_EMPT3_1                    [expr 0x1 << 19 ]
set AT91C_HDMA_EMPT4      [expr 0x1 << 20 ]
set 	AT91C_HDMA_EMPT4_0                    [expr 0x0 << 20 ]
set 	AT91C_HDMA_EMPT4_1                    [expr 0x1 << 20 ]
set AT91C_HDMA_EMPT5      [expr 0x1 << 21 ]
set 	AT91C_HDMA_EMPT5_0                    [expr 0x0 << 21 ]
set 	AT91C_HDMA_EMPT5_1                    [expr 0x1 << 21 ]
set AT91C_HDMA_EMPT6      [expr 0x1 << 22 ]
set 	AT91C_HDMA_EMPT6_0                    [expr 0x0 << 22 ]
set 	AT91C_HDMA_EMPT6_1                    [expr 0x1 << 22 ]
set AT91C_HDMA_EMPT7      [expr 0x1 << 23 ]
set 	AT91C_HDMA_EMPT7_0                    [expr 0x0 << 23 ]
set 	AT91C_HDMA_EMPT7_1                    [expr 0x1 << 23 ]
set AT91C_HDMA_STAL0      [expr 0x1 << 24 ]
set 	AT91C_HDMA_STAL0_0                    [expr 0x0 << 24 ]
set 	AT91C_HDMA_STAL0_1                    [expr 0x1 << 24 ]
set AT91C_HDMA_STAL1      [expr 0x1 << 25 ]
set 	AT91C_HDMA_STAL1_0                    [expr 0x0 << 25 ]
set 	AT91C_HDMA_STAL1_1                    [expr 0x1 << 25 ]
set AT91C_HDMA_STAL2      [expr 0x1 << 26 ]
set 	AT91C_HDMA_STAL2_0                    [expr 0x0 << 26 ]
set 	AT91C_HDMA_STAL2_1                    [expr 0x1 << 26 ]
set AT91C_HDMA_STAL3      [expr 0x1 << 27 ]
set 	AT91C_HDMA_STAL3_0                    [expr 0x0 << 27 ]
set 	AT91C_HDMA_STAL3_1                    [expr 0x1 << 27 ]
set AT91C_HDMA_STAL4      [expr 0x1 << 28 ]
set 	AT91C_HDMA_STAL4_0                    [expr 0x0 << 28 ]
set 	AT91C_HDMA_STAL4_1                    [expr 0x1 << 28 ]
set AT91C_HDMA_STAL5      [expr 0x1 << 29 ]
set 	AT91C_HDMA_STAL5_0                    [expr 0x0 << 29 ]
set 	AT91C_HDMA_STAL5_1                    [expr 0x1 << 29 ]
set AT91C_HDMA_STAL6      [expr 0x1 << 30 ]
set 	AT91C_HDMA_STAL6_0                    [expr 0x0 << 30 ]
set 	AT91C_HDMA_STAL6_1                    [expr 0x1 << 30 ]
set AT91C_HDMA_STAL7      [expr 0x1 << 31 ]
set 	AT91C_HDMA_STAL7_0                    [expr 0x0 << 31 ]
set 	AT91C_HDMA_STAL7_1                    [expr 0x1 << 31 ]
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
set AT91C_EMAC_WOLEV      [expr 0x1 << 14 ]
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
set AT91C_                [expr 0x0 << 14 ]
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
set AT91C_                [expr 0x0 << 14 ]
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
set AT91C_                [expr 0x0 << 14 ]
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
#              SOFTWARE API DEFINITION  FOR Image Sensor Interface
# *****************************************************************************
# -------- ISI_CFG1 : (ISI Offset: 0x0) ISI Configuration Register 1 -------- 
set AT91C_ISI_HSYNC_POL   [expr 0x1 <<  2 ]
set 	AT91C_ISI_HSYNC_POL_ACTIVE_HIGH          [expr 0x0 <<  2 ]
set 	AT91C_ISI_HSYNC_POL_ACTIVE_LOW           [expr 0x1 <<  2 ]
set AT91C_ISI_HSYNC_POL   [expr 0x1 <<  3 ]
set 	AT91C_ISI_HSYNC_POL_ACTIVE_HIGH          [expr 0x0 <<  3 ]
set 	AT91C_ISI_HSYNC_POL_ACTIVE_LOW           [expr 0x1 <<  3 ]
set AT91C_ISI_PIXCLK_POL  [expr 0x1 <<  4 ]
set 	AT91C_ISI_PIXCLK_POL_RISING_EDGE          [expr 0x0 <<  4 ]
set 	AT91C_ISI_PIXCLK_POL_FALLING_EDGE         [expr 0x1 <<  4 ]
set AT91C_ISI_EMB_SYNC    [expr 0x1 <<  6 ]
set 	AT91C_ISI_EMB_SYNC_HSYNC_VSYNC          [expr 0x0 <<  6 ]
set 	AT91C_ISI_EMB_SYNC_SAV_EAV              [expr 0x1 <<  6 ]
set AT91C_ISI_CRC_SYNC    [expr 0x1 <<  7 ]
set 	AT91C_ISI_CRC_SYNC_CORRECTION_OFF       [expr 0x0 <<  7 ]
set 	AT91C_ISI_CRC_SYNC_CORRECTION_ON        [expr 0x1 <<  7 ]
set AT91C_ISI_FRATE       [expr 0x7 <<  8 ]
set AT91C_ISI_FULL        [expr 0x1 << 12 ]
set 	AT91C_ISI_FULL_MODE_DISABLE         [expr 0x0 << 12 ]
set 	AT91C_ISI_FULL_MODE_ENABLE          [expr 0x1 << 12 ]
set AT91C_ISI_THMASK      [expr 0x3 << 13 ]
set 	AT91C_ISI_THMASK_4_BURST              [expr 0x0 << 13 ]
set 	AT91C_ISI_THMASK_4_8_BURST            [expr 0x1 << 13 ]
set 	AT91C_ISI_THMASK_4_8_16_BURST         [expr 0x2 << 13 ]
set AT91C_ISI_SLD         [expr 0xFF << 16 ]
set AT91C_ISI_SFD         [expr 0xFF << 24 ]
# -------- ISI_CFG2 : (ISI Offset: 0x4) ISI Control Register 2 -------- 
set AT91C_ISI_IM_VSIZE    [expr 0x7FF <<  0 ]
set AT91C_ISI_GS_MODE     [expr 0x1 << 11 ]
set 	AT91C_ISI_GS_MODE_2_PIXELS             [expr 0x0 << 11 ]
set 	AT91C_ISI_GS_MODE_1_PIXEL              [expr 0x1 << 11 ]
set AT91C_ISI_RGB_MODE    [expr 0x1 << 12 ]
set 	AT91C_ISI_RGB_MODE_RGB_888              [expr 0x0 << 12 ]
set 	AT91C_ISI_RGB_MODE_RGB_565              [expr 0x1 << 12 ]
set AT91C_ISI_GRAYSCALE   [expr 0x1 << 13 ]
set 	AT91C_ISI_GRAYSCALE_DISABLE              [expr 0x0 << 13 ]
set 	AT91C_ISI_GRAYSCALE_ENABLE               [expr 0x1 << 13 ]
set AT91C_ISI_RGB_SWAP    [expr 0x1 << 14 ]
set 	AT91C_ISI_RGB_SWAP_DISABLE              [expr 0x0 << 14 ]
set 	AT91C_ISI_RGB_SWAP_ENABLE               [expr 0x1 << 14 ]
set AT91C_ISI_COL_SPACE   [expr 0x1 << 15 ]
set 	AT91C_ISI_COL_SPACE_YCBCR                [expr 0x0 << 15 ]
set 	AT91C_ISI_COL_SPACE_RGB                  [expr 0x1 << 15 ]
set AT91C_ISI_IM_HSIZE    [expr 0x7FF << 16 ]
set AT91C_ISI_YCC_SWAP    [expr 0x3 << 28 ]
set 	AT91C_ISI_YCC_SWAP_YCC_DEFAULT          [expr 0x0 << 28 ]
set 	AT91C_ISI_YCC_SWAP_YCC_MODE1            [expr 0x1 << 28 ]
set 	AT91C_ISI_YCC_SWAP_YCC_MODE2            [expr 0x2 << 28 ]
set 	AT91C_ISI_YCC_SWAP_YCC_MODE3            [expr 0x3 << 28 ]
set AT91C_ISI_RGB_CFG     [expr 0x3 << 30 ]
set 	AT91C_ISI_RGB_CFG_RGB_DEFAULT          [expr 0x0 << 30 ]
set 	AT91C_ISI_RGB_CFG_RGB_MODE1            [expr 0x1 << 30 ]
set 	AT91C_ISI_RGB_CFG_RGB_MODE2            [expr 0x2 << 30 ]
set 	AT91C_ISI_RGB_CFG_RGB_MODE3            [expr 0x3 << 30 ]
# -------- ISI_PSIZE : (ISI Offset: 0x8) ISI Preview Register -------- 
set AT91C_ISI_PREV_VSIZE  [expr 0x3FF <<  0 ]
set AT91C_ISI_PREV_HSIZE  [expr 0x3FF << 16 ]
# -------- ISI_Y2RSET0 : (ISI Offset: 0x10) Color Space Conversion YCrCb to RGB Register -------- 
set AT91C_ISI_Y2R_C0      [expr 0xFF <<  0 ]
set AT91C_ISI_Y2R_C1      [expr 0xFF <<  8 ]
set AT91C_ISI_Y2R_C2      [expr 0xFF << 16 ]
set AT91C_ISI_Y2R_C3      [expr 0xFF << 24 ]
# -------- ISI_Y2RSET1 : (ISI Offset: 0x14) ISI Color Space Conversion YCrCb to RGB set 1 Register -------- 
set AT91C_ISI_Y2R_C4      [expr 0x1FF <<  0 ]
set AT91C_ISI_Y2R_YOFF    [expr 0x1 << 12 ]
set 	AT91C_ISI_Y2R_YOFF_0                    [expr 0x0 << 12 ]
set 	AT91C_ISI_Y2R_YOFF_128                  [expr 0x1 << 12 ]
set AT91C_ISI_Y2R_CROFF   [expr 0x1 << 13 ]
set 	AT91C_ISI_Y2R_CROFF_0                    [expr 0x0 << 13 ]
set 	AT91C_ISI_Y2R_CROFF_16                   [expr 0x1 << 13 ]
set AT91C_ISI_Y2R_CBOFF   [expr 0x1 << 14 ]
set 	AT91C_ISI_Y2R_CBOFF_0                    [expr 0x0 << 14 ]
set 	AT91C_ISI_Y2R_CBOFF_16                   [expr 0x1 << 14 ]
# -------- ISI_R2YSET0 : (ISI Offset: 0x18) Color Space Conversion RGB to YCrCb set 0 register -------- 
set AT91C_ISI_R2Y_C0      [expr 0xFF <<  0 ]
set AT91C_ISI_R2Y_C1      [expr 0xFF <<  8 ]
set AT91C_ISI_R2Y_C2      [expr 0xFF << 16 ]
set AT91C_ISI_R2Y_ROFF    [expr 0x1 << 24 ]
set 	AT91C_ISI_R2Y_ROFF_0                    [expr 0x0 << 24 ]
set 	AT91C_ISI_R2Y_ROFF_16                   [expr 0x1 << 24 ]
# -------- ISI_R2YSET1 : (ISI Offset: 0x1c) Color Space Conversion RGB to YCrCb set 1 register -------- 
set AT91C_ISI_R2Y_C3      [expr 0xFF <<  0 ]
set AT91C_ISI_R2Y_C4      [expr 0xFF <<  8 ]
set AT91C_ISI_R2Y_C5      [expr 0xFF << 16 ]
set AT91C_ISI_R2Y_GOFF    [expr 0x1 << 24 ]
set 	AT91C_ISI_R2Y_GOFF_0                    [expr 0x0 << 24 ]
set 	AT91C_ISI_R2Y_GOFF_128                  [expr 0x1 << 24 ]
# -------- ISI_R2YSET2 : (ISI Offset: 0x20) Color Space Conversion RGB to YCrCb set 2 register -------- 
set AT91C_ISI_R2Y_C6      [expr 0xFF <<  0 ]
set AT91C_ISI_R2Y_C7      [expr 0xFF <<  8 ]
set AT91C_ISI_R2Y_C8      [expr 0xFF << 16 ]
set AT91C_ISI_R2Y_BOFF    [expr 0x1 << 24 ]
set 	AT91C_ISI_R2Y_BOFF_0                    [expr 0x0 << 24 ]
set 	AT91C_ISI_R2Y_BOFF_128                  [expr 0x1 << 24 ]
# -------- ISI_CTRL : (ISI Offset: 0x24) ISI Control Register -------- 
set AT91C_ISI_EN          [expr 0x1 <<  0 ]
set 	AT91C_ISI_EN_0                    0x0
set 	AT91C_ISI_EN_1                    0x1
set AT91C_ISI_DIS         [expr 0x1 <<  1 ]
set 	AT91C_ISI_DIS_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_DIS_1                    [expr 0x1 <<  1 ]
set AT91C_ISI_SRST        [expr 0x1 <<  2 ]
set 	AT91C_ISI_SRST_0                    [expr 0x0 <<  2 ]
set 	AT91C_ISI_SRST_1                    [expr 0x1 <<  2 ]
set AT91C_ISI_CDC         [expr 0x1 <<  8 ]
set 	AT91C_ISI_CDC_0                    [expr 0x0 <<  8 ]
set 	AT91C_ISI_CDC_1                    [expr 0x1 <<  8 ]
# -------- ISI_SR : (ISI Offset: 0x28) ISI Status Register -------- 
set AT91C_ISI_EN          [expr 0x1 <<  0 ]
set 	AT91C_ISI_EN_0                    0x0
set 	AT91C_ISI_EN_1                    0x1
set AT91C_ISI_DIS         [expr 0x1 <<  1 ]
set 	AT91C_ISI_DIS_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_DIS_1                    [expr 0x1 <<  1 ]
set AT91C_ISI_SRST        [expr 0x1 <<  2 ]
set 	AT91C_ISI_SRST_0                    [expr 0x0 <<  2 ]
set 	AT91C_ISI_SRST_1                    [expr 0x1 <<  2 ]
set AT91C_ISI_CDC         [expr 0x1 <<  3 ]
set 	AT91C_ISI_CDC_0                    [expr 0x0 <<  3 ]
set 	AT91C_ISI_CDC_1                    [expr 0x1 <<  3 ]
set AT91C_ISI_VSYNC       [expr 0x1 << 10 ]
set 	AT91C_ISI_VSYNC_0                    [expr 0x0 << 10 ]
set 	AT91C_ISI_VSYNC_1                    [expr 0x1 << 10 ]
set AT91C_ISI_PXFR_DONE   [expr 0x1 << 16 ]
set 	AT91C_ISI_PXFR_DONE_0                    [expr 0x0 << 16 ]
set 	AT91C_ISI_PXFR_DONE_1                    [expr 0x1 << 16 ]
set AT91C_ISI_CXFR_DONE   [expr 0x1 << 17 ]
set 	AT91C_ISI_CXFR_DONE_0                    [expr 0x0 << 17 ]
set 	AT91C_ISI_CXFR_DONE_1                    [expr 0x1 << 17 ]
set AT91C_ISI_SIP         [expr 0x1 << 19 ]
set 	AT91C_ISI_SIP_0                    [expr 0x0 << 19 ]
set 	AT91C_ISI_SIP_1                    [expr 0x1 << 19 ]
set AT91C_ISI_P_OVR       [expr 0x1 << 24 ]
set 	AT91C_ISI_P_OVR_0                    [expr 0x0 << 24 ]
set 	AT91C_ISI_P_OVR_1                    [expr 0x1 << 24 ]
set AT91C_ISI_C_OVR       [expr 0x1 << 25 ]
set 	AT91C_ISI_C_OVR_0                    [expr 0x0 << 25 ]
set 	AT91C_ISI_C_OVR_1                    [expr 0x1 << 25 ]
set AT91C_ISI_CRC_ERR     [expr 0x1 << 26 ]
set 	AT91C_ISI_CRC_ERR_0                    [expr 0x0 << 26 ]
set 	AT91C_ISI_CRC_ERR_1                    [expr 0x1 << 26 ]
set AT91C_ISI_FR_OVR      [expr 0x1 << 27 ]
set 	AT91C_ISI_FR_OVR_0                    [expr 0x0 << 27 ]
set 	AT91C_ISI_FR_OVR_1                    [expr 0x1 << 27 ]
# -------- ISI_IER : (ISI Offset: 0x2c) ISI Interrupt Enable Register -------- 
set AT91C_ISI_DIS         [expr 0x1 <<  1 ]
set 	AT91C_ISI_DIS_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_DIS_1                    [expr 0x1 <<  1 ]
set AT91C_ISI_SRST        [expr 0x1 <<  2 ]
set 	AT91C_ISI_SRST_0                    [expr 0x0 <<  2 ]
set 	AT91C_ISI_SRST_1                    [expr 0x1 <<  2 ]
set AT91C_ISI_VSYNC       [expr 0x1 << 10 ]
set 	AT91C_ISI_VSYNC_0                    [expr 0x0 << 10 ]
set 	AT91C_ISI_VSYNC_1                    [expr 0x1 << 10 ]
set AT91C_ISI_PXFR_DONE   [expr 0x1 << 16 ]
set 	AT91C_ISI_PXFR_DONE_0                    [expr 0x0 << 16 ]
set 	AT91C_ISI_PXFR_DONE_1                    [expr 0x1 << 16 ]
set AT91C_ISI_CXFR_DONE   [expr 0x1 << 17 ]
set 	AT91C_ISI_CXFR_DONE_0                    [expr 0x0 << 17 ]
set 	AT91C_ISI_CXFR_DONE_1                    [expr 0x1 << 17 ]
set AT91C_ISI_P_OVR       [expr 0x1 << 24 ]
set 	AT91C_ISI_P_OVR_0                    [expr 0x0 << 24 ]
set 	AT91C_ISI_P_OVR_1                    [expr 0x1 << 24 ]
set AT91C_ISI_C_OVR       [expr 0x1 << 25 ]
set 	AT91C_ISI_C_OVR_0                    [expr 0x0 << 25 ]
set 	AT91C_ISI_C_OVR_1                    [expr 0x1 << 25 ]
set AT91C_ISI_CRC_ERR     [expr 0x1 << 26 ]
set 	AT91C_ISI_CRC_ERR_0                    [expr 0x0 << 26 ]
set 	AT91C_ISI_CRC_ERR_1                    [expr 0x1 << 26 ]
set AT91C_ISI_FR_OVR      [expr 0x1 << 27 ]
set 	AT91C_ISI_FR_OVR_0                    [expr 0x0 << 27 ]
set 	AT91C_ISI_FR_OVR_1                    [expr 0x1 << 27 ]
# -------- ISI_IDR : (ISI Offset: 0x30) ISI Interrupt Disable Register -------- 
set AT91C_ISI_DIS         [expr 0x1 <<  1 ]
set 	AT91C_ISI_DIS_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_DIS_1                    [expr 0x1 <<  1 ]
set AT91C_ISI_SRST        [expr 0x1 <<  2 ]
set 	AT91C_ISI_SRST_0                    [expr 0x0 <<  2 ]
set 	AT91C_ISI_SRST_1                    [expr 0x1 <<  2 ]
set AT91C_ISI_VSYNC       [expr 0x1 << 10 ]
set 	AT91C_ISI_VSYNC_0                    [expr 0x0 << 10 ]
set 	AT91C_ISI_VSYNC_1                    [expr 0x1 << 10 ]
set AT91C_ISI_PXFR_DONE   [expr 0x1 << 16 ]
set 	AT91C_ISI_PXFR_DONE_0                    [expr 0x0 << 16 ]
set 	AT91C_ISI_PXFR_DONE_1                    [expr 0x1 << 16 ]
set AT91C_ISI_CXFR_DONE   [expr 0x1 << 17 ]
set 	AT91C_ISI_CXFR_DONE_0                    [expr 0x0 << 17 ]
set 	AT91C_ISI_CXFR_DONE_1                    [expr 0x1 << 17 ]
set AT91C_ISI_P_OVR       [expr 0x1 << 24 ]
set 	AT91C_ISI_P_OVR_0                    [expr 0x0 << 24 ]
set 	AT91C_ISI_P_OVR_1                    [expr 0x1 << 24 ]
set AT91C_ISI_C_OVR       [expr 0x1 << 25 ]
set 	AT91C_ISI_C_OVR_0                    [expr 0x0 << 25 ]
set 	AT91C_ISI_C_OVR_1                    [expr 0x1 << 25 ]
set AT91C_ISI_CRC_ERR     [expr 0x1 << 26 ]
set 	AT91C_ISI_CRC_ERR_0                    [expr 0x0 << 26 ]
set 	AT91C_ISI_CRC_ERR_1                    [expr 0x1 << 26 ]
set AT91C_ISI_FR_OVR      [expr 0x1 << 27 ]
set 	AT91C_ISI_FR_OVR_0                    [expr 0x0 << 27 ]
set 	AT91C_ISI_FR_OVR_1                    [expr 0x1 << 27 ]
# -------- ISI_IMR : (ISI Offset: 0x34) ISI Interrupt Mask Register -------- 
set AT91C_ISI_DIS         [expr 0x1 <<  1 ]
set 	AT91C_ISI_DIS_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_DIS_1                    [expr 0x1 <<  1 ]
set AT91C_ISI_SRST        [expr 0x1 <<  2 ]
set 	AT91C_ISI_SRST_0                    [expr 0x0 <<  2 ]
set 	AT91C_ISI_SRST_1                    [expr 0x1 <<  2 ]
set AT91C_ISI_VSYNC       [expr 0x1 << 10 ]
set 	AT91C_ISI_VSYNC_0                    [expr 0x0 << 10 ]
set 	AT91C_ISI_VSYNC_1                    [expr 0x1 << 10 ]
set AT91C_ISI_PXFR_DONE   [expr 0x1 << 16 ]
set 	AT91C_ISI_PXFR_DONE_0                    [expr 0x0 << 16 ]
set 	AT91C_ISI_PXFR_DONE_1                    [expr 0x1 << 16 ]
set AT91C_ISI_CXFR_DONE   [expr 0x1 << 17 ]
set 	AT91C_ISI_CXFR_DONE_0                    [expr 0x0 << 17 ]
set 	AT91C_ISI_CXFR_DONE_1                    [expr 0x1 << 17 ]
set AT91C_ISI_P_OVR       [expr 0x1 << 24 ]
set 	AT91C_ISI_P_OVR_0                    [expr 0x0 << 24 ]
set 	AT91C_ISI_P_OVR_1                    [expr 0x1 << 24 ]
set AT91C_ISI_C_OVR       [expr 0x1 << 25 ]
set 	AT91C_ISI_C_OVR_0                    [expr 0x0 << 25 ]
set 	AT91C_ISI_C_OVR_1                    [expr 0x1 << 25 ]
set AT91C_ISI_CRC_ERR     [expr 0x1 << 26 ]
set 	AT91C_ISI_CRC_ERR_0                    [expr 0x0 << 26 ]
set 	AT91C_ISI_CRC_ERR_1                    [expr 0x1 << 26 ]
set AT91C_ISI_FR_OVR      [expr 0x1 << 27 ]
set 	AT91C_ISI_FR_OVR_0                    [expr 0x0 << 27 ]
set 	AT91C_ISI_FR_OVR_1                    [expr 0x1 << 27 ]
# -------- ISI_DMACHER : (ISI Offset: 0x38) DMA Channel Enable Register -------- 
set AT91C_ISI_P_CH_EN     [expr 0x1 <<  0 ]
set 	AT91C_ISI_P_CH_EN_0                    0x0
set 	AT91C_ISI_P_CH_EN_1                    0x1
set AT91C_ISI_C_CH_EN     [expr 0x1 <<  1 ]
set 	AT91C_ISI_C_CH_EN_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_C_CH_EN_1                    [expr 0x1 <<  1 ]
# -------- ISI_DMACHDR : (ISI Offset: 0x3c) DMA Channel Enable Register -------- 
set AT91C_ISI_P_CH_DIS    [expr 0x1 <<  0 ]
set 	AT91C_ISI_P_CH_DIS_0                    0x0
set 	AT91C_ISI_P_CH_DIS_1                    0x1
set AT91C_ISI_C_CH_DIS    [expr 0x1 <<  1 ]
set 	AT91C_ISI_C_CH_DIS_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_C_CH_DIS_1                    [expr 0x1 <<  1 ]
# -------- ISI_DMACHSR : (ISI Offset: 0x40) DMA Channel Status Register -------- 
set AT91C_ISI_P_CH_S      [expr 0x1 <<  0 ]
set 	AT91C_ISI_P_CH_S_0                    0x0
set 	AT91C_ISI_P_CH_S_1                    0x1
set AT91C_ISI_C_CH_S      [expr 0x1 <<  1 ]
set 	AT91C_ISI_C_CH_S_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_C_CH_S_1                    [expr 0x1 <<  1 ]
# -------- ISI_DMAPCTRL : (ISI Offset: 0x48) DMA Preview Control Register -------- 
set AT91C_ISI_P_FETCH     [expr 0x1 <<  0 ]
set 	AT91C_ISI_P_FETCH_DISABLE              0x0
set 	AT91C_ISI_P_FETCH_ENABLE               0x1
set AT91C_ISI_P_DONE      [expr 0x1 <<  1 ]
set 	AT91C_ISI_P_DONE_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_P_DONE_1                    [expr 0x1 <<  1 ]
# -------- ISI_DMACCTRL : (ISI Offset: 0x54) DMA Codec Control Register -------- 
set AT91C_ISI_C_FETCH     [expr 0x1 <<  0 ]
set 	AT91C_ISI_C_FETCH_DISABLE              0x0
set 	AT91C_ISI_C_FETCH_ENABLE               0x1
set AT91C_ISI_C_DONE      [expr 0x1 <<  1 ]
set 	AT91C_ISI_C_DONE_0                    [expr 0x0 <<  1 ]
set 	AT91C_ISI_C_DONE_1                    [expr 0x1 <<  1 ]
# -------- ISI_WPCR : (ISI Offset: 0xe4) Write Protection Control Register -------- 
set AT91C_ISI_WP_EN       [expr 0x1 <<  0 ]
set 	AT91C_ISI_WP_EN_DISABLE              0x0
set 	AT91C_ISI_WP_EN_ENABLE               0x1
set AT91C_ISI_WP_KEY      [expr 0xFFFFFF <<  8 ]
# -------- ISI_WPSR : (ISI Offset: 0xe8) Write Protection Status Register -------- 
set AT91C_ISI_WP_VS       [expr 0xF <<  0 ]
set 	AT91C_ISI_WP_VS_NO_VIOLATION         0x0
set 	AT91C_ISI_WP_VS_ON_WRITE             0x1
set 	AT91C_ISI_WP_VS_ON_RESET             0x2
set 	AT91C_ISI_WP_VS_ON_BOTH              0x3
set AT91C_ISI_WP_VSRC     [expr 0xF <<  8 ]
set 	AT91C_ISI_WP_VSRC_NO_VIOLATION         [expr 0x0 <<  8 ]
set 	AT91C_ISI_WP_VSRC_ISI_CFG1             [expr 0x1 <<  8 ]
set 	AT91C_ISI_WP_VSRC_ISI_CFG2             [expr 0x2 <<  8 ]
set 	AT91C_ISI_WP_VSRC_ISI_PSIZE            [expr 0x3 <<  8 ]
set 	AT91C_ISI_WP_VSRC_ISI_PDECF            [expr 0x4 <<  8 ]
set 	AT91C_ISI_WP_VSRC_ISI_Y2RSET0          [expr 0x5 <<  8 ]
set 	AT91C_ISI_WP_VSRC_ISI_Y2RSET1          [expr 0x6 <<  8 ]
set 	AT91C_ISI_WP_VSRC_ISI_R2YSET0          [expr 0x7 <<  8 ]
set 	AT91C_ISI_WP_VSRC_ISI_R2YSET1          [expr 0x8 <<  8 ]
set 	AT91C_ISI_WP_VSRC_ISI_R2YSET2          [expr 0x9 <<  8 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR HANTRO VDEC 7190
# *****************************************************************************
# -------- VDEC_IDR : (VDEC Offset: 0x0) VDEC ID Register -------- 
set AT91C_VDEC_ID         [expr 0x0 <<  0 ]
# -------- VDEC_ISR : (VDEC Offset: 0x4) VDEC Interrupt Status Register -------- 
set AT91C_VDEC_DEC_E      [expr 0x1 <<  0 ]
set AT91C_VDEC_DEC_IRQ_DIS [expr 0x1 <<  4 ]
set AT91C_VDEC_DEC_IRQ    [expr 0x1 <<  8 ]
set AT91C_VDEC_DEC_RDY_INT [expr 0x1 << 12 ]
set AT91C_VDEC_DEC_BUS_INT [expr 0x1 << 13 ]
set AT91C_VDEC_DEC_BUFFER_INT [expr 0x1 << 14 ]
set AT91C_VDEC_DEC_ASO_INT [expr 0x1 << 15 ]
set AT91C_VDEC_DEC_ERROR_INT [expr 0x1 << 16 ]
set AT91C_VDEC_DEC_SLICE_INT [expr 0x1 << 17 ]
set AT91C_VDEC_DEC_TIMEOUT [expr 0x1 << 18 ]
# -------- VDEC_DCR : (VDEC Offset: 0x8) VDEC Device Configuration Register -------- 
set AT91C_VDEC_DEC_MAX_BURST [expr 0x1F <<  0 ]
set 	AT91C_VDEC_DEC_MAX_BURST_4                    0x4
set 	AT91C_VDEC_DEC_MAX_BURST_8                    0x8
set 	AT91C_VDEC_DEC_MAX_BURST_16                   0x10
set AT91C_VDEC_PRIORITY_MODE [expr 0x7 <<  5 ]
set 	AT91C_VDEC_PRIORITY_MODE_HW                   [expr 0x0 <<  5 ]
set 	AT91C_VDEC_PRIORITY_MODE_WRITE_FT             [expr 0x1 <<  5 ]
set 	AT91C_VDEC_PRIORITY_MODE_WRITE_PP             [expr 0x2 <<  5 ]
set 	AT91C_VDEC_PRIORITY_MODE_READ_FT              [expr 0x3 <<  5 ]
set 	AT91C_VDEC_PRIORITY_MODE_READ_PP              [expr 0x4 <<  5 ]
set AT91C_VDEC_DEC_OUT_ENDIAN [expr 0x1 <<  8 ]
set 	AT91C_VDEC_DEC_OUT_ENDIAN_BIG                  [expr 0x0 <<  8 ]
set 	AT91C_VDEC_DEC_OUT_ENDIAN_LIT                  [expr 0x1 <<  8 ]
set AT91C_VDEC_DEC_IN_ENDIAN [expr 0x1 <<  9 ]
set 	AT91C_VDEC_DEC_IN_ENDIAN_BIG                  [expr 0x0 <<  9 ]
set 	AT91C_VDEC_DEC_IN_ENDIAN_LIT                  [expr 0x1 <<  9 ]
set AT91C_VDEC_DEC_CLK_GATE_E [expr 0x1 << 10 ]
set AT91C_VDEC_DEC_LATENCY [expr 0x3F << 11 ]
set AT91C_VDEC_DEC_OUT_TILED_E [expr 0x1 << 17 ]
set AT91C_VDEC_DEC_DATA_DISC_E [expr 0x1 << 18 ]
set AT91C_VDEC_DEC_OUTSWAP32_E [expr 0x1 << 19 ]
set AT91C_VDEC_DEC_INSWAP32_E [expr 0x1 << 20 ]
set AT91C_VDEC_DEC_STRENDIAN_E [expr 0x1 << 21 ]
set 	AT91C_VDEC_DEC_STRENDIAN_E_BIG                  [expr 0x0 << 21 ]
set 	AT91C_VDEC_DEC_STRENDIAN_E_LIT                  [expr 0x1 << 21 ]
set AT91C_VDEC_DEC_STRSWAP32_E [expr 0x1 << 22 ]
set AT91C_VDEC_DEC_TIMEOUT_E [expr 0x1 << 23 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR USB Host Interface
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR USB Host Interface
# *****************************************************************************
# -------- VERSION : (UHPHS_EHCI Offset: 0x0)  -------- 
set AT91C_UHPHS_CAPLENGTH [expr 0xFF <<  0 ]
set AT91C_UHPHS_HCIVERSION [expr 0xFF << 16 ]

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
set AT91C_AES_KEYSIZE     [expr 0x3 << 10 ]
set 	AT91C_AES_KEYSIZE_128_BIT              [expr 0x0 << 10 ]
set 	AT91C_AES_KEYSIZE_192_BIT              [expr 0x1 << 10 ]
set 	AT91C_AES_KEYSIZE_256_BIT              [expr 0x2 << 10 ]
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
#              SOFTWARE API DEFINITION  FOR Secure Hash Algorithm
# *****************************************************************************
# -------- SHA_CR : (SHA Offset: 0x0) Control Register -------- 
set AT91C_SHA_START       [expr 0x1 <<  0 ]
set AT91C_SHA_FIRST       [expr 0x1 <<  4 ]
set AT91C_SHA_SWRST       [expr 0x1 <<  8 ]
# -------- SHA_MR : (SHA Offset: 0x4) Mode Register -------- 
set AT91C_SHA_SMOD        [expr 0x3 <<  0 ]
set 	AT91C_SHA_SMOD_MANUAL               0x0
set 	AT91C_SHA_SMOD_AUTO                 0x1
set 	AT91C_SHA_SMOD_PDC                  0x2
set AT91C_SHA_PROCDLY     [expr 0x1 <<  4 ]
set AT91C_SHA_ALGO        [expr 0x1 <<  8 ]
# -------- SHA_IER : (SHA Offset: 0x10) Interrupt Enable Register -------- 
set AT91C_SHA_DATRDY      [expr 0x1 <<  0 ]
set AT91C_SHA_ENDTX       [expr 0x1 <<  1 ]
set AT91C_SHA_TXBUFE      [expr 0x1 <<  2 ]
set AT91C_SHA_URAD        [expr 0x1 <<  8 ]
# -------- SHA_IDR : (SHA Offset: 0x14) Interrupt Disable Register -------- 
set AT91C_SHA_DATRDY      [expr 0x1 <<  0 ]
set AT91C_SHA_ENDTX       [expr 0x1 <<  1 ]
set AT91C_SHA_TXBUFE      [expr 0x1 <<  2 ]
set AT91C_SHA_URAD        [expr 0x1 <<  8 ]
# -------- SHA_IMR : (SHA Offset: 0x18) Interrupt Mask Register -------- 
set AT91C_SHA_DATRDY      [expr 0x1 <<  0 ]
set AT91C_SHA_ENDTX       [expr 0x1 <<  1 ]
set AT91C_SHA_TXBUFE      [expr 0x1 <<  2 ]
set AT91C_SHA_URAD        [expr 0x1 <<  8 ]
# -------- SHA_ISR : (SHA Offset: 0x1c) Interrupt Status Register -------- 
set AT91C_SHA_DATRDY      [expr 0x1 <<  0 ]
set AT91C_SHA_ENDTX       [expr 0x1 <<  1 ]
set AT91C_SHA_TXBUFE      [expr 0x1 <<  2 ]
set AT91C_SHA_URAD        [expr 0x1 <<  8 ]
set AT91C_SHA_URAT        [expr 0x7 << 12 ]
set 	AT91C_SHA_URAT_IN_DAT_WRITE_DATPROC [expr 0x0 << 12 ]
set 	AT91C_SHA_URAT_OUT_DAT_READ_DATPROC [expr 0x1 << 12 ]
set 	AT91C_SHA_URAT_MODEREG_WRITE_DATPROC [expr 0x2 << 12 ]
set 	AT91C_SHA_URAT_OUT_DAT_READ_SUBKEY  [expr 0x3 << 12 ]
set 	AT91C_SHA_URAT_MODEREG_WRITE_SUBKEY [expr 0x4 << 12 ]
set 	AT91C_SHA_URAT_WO_REG_READ          [expr 0x5 << 12 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR True Random Generator
# *****************************************************************************
# -------- TRNG_CR : (TRNG Offset: 0x0) Control Register -------- 
set AT91C_TRNG_ENABLE     [expr 0x1 <<  0 ]
# -------- TRNG_IER : (TRNG Offset: 0x10) Interrupt Enable Register -------- 
set AT91C_TRNG_DATRDY     [expr 0x1 <<  0 ]
# -------- TRNG_IDR : (TRNG Offset: 0x14) Interrupt Disable Register -------- 
set AT91C_TRNG_DATRDY     [expr 0x1 <<  0 ]
# -------- TRNG_IMR : (TRNG Offset: 0x18) Interrupt Mask Register -------- 
set AT91C_TRNG_DATRDY     [expr 0x1 <<  0 ]
# -------- TRNG_ISR : (TRNG Offset: 0x1c) Interrupt Status Register -------- 
set AT91C_TRNG_DATRDY     [expr 0x1 <<  0 ]

# *****************************************************************************
#               REGISTER ADDRESS DEFINITION FOR AT91SAM9264
# *****************************************************************************
# ========== Register definition for SFR peripheral ========== 
set AT91C_SFR_INT   0xFFF74014
set AT91C_SFR_DDRCFG 0xFFF74004
set AT91C_SFR_UTMICFG 0xFFF74010
set AT91C_SFR_EBIDELAY 0xFFF7400C
set AT91C_SFR_DDRDELAY 0xFFF74008
set AT91C_SFR_EMA   0xFFF74000
# ========== Register definition for SYS peripheral ========== 
set AT91C_SYS_SLCKSEL 0xFFFFFD50
set AT91C_SYS_GPBR  0xFFFFFD60
# ========== Register definition for EBI peripheral ========== 
set AT91C_EBI_DUMMY 0xFFFFE200
# ========== Register definition for DDR2CP1 peripheral ========== 
set AT91C_DDR2CP1_DELAY2 0xFFFFE434
set AT91C_DDR2CP1_T3PR 0xFFFFE418
set AT91C_DDR2CP1_RTR 0xFFFFE404
set AT91C_DDR2CP1_T0PR 0xFFFFE40C
set AT91C_DDR2CP1_WPSR 0xFFFFE4E8
set AT91C_DDR2CP1_DELAY8 0xFFFFE44C
set AT91C_DDR2CP1_LPR 0xFFFFE41C
set AT91C_DDR2CP1_VER 0xFFFFE428
set AT91C_DDR2CP1_DELAY7 0xFFFFE448
set AT91C_DDR2CP1_CR 0xFFFFE408
set AT91C_DDR2CP1_WPCR 0xFFFFE4E4
set AT91C_DDR2CP1_MR 0xFFFFE400
set AT91C_DDR2CP1_DELAY5 0xFFFFE440
set AT91C_DDR2CP1_T2PR 0xFFFFE414
set AT91C_DDR2CP1_HS 0xFFFFE42C
set AT91C_DDR2CP1_MDR 0xFFFFE420
set AT91C_DDR2CP1_DELAY4 0xFFFFE43C
set AT91C_DDR2CP1_DELAY1 0xFFFFE430
set AT91C_DDR2CP1_DELAY6 0xFFFFE444
set AT91C_DDR2CP1_DLL 0xFFFFE424
set AT91C_DDR2CP1_DELAY3 0xFFFFE438
set AT91C_DDR2CP1_VERSION 0xFFFFE4FC
set AT91C_DDR2CP1_T1PR 0xFFFFE410
# ========== Register definition for DDR2C peripheral ========== 
set AT91C_DDR2C_DELAY8 0xFFFFE64C
set AT91C_DDR2C_VER 0xFFFFE628
set AT91C_DDR2C_RTR 0xFFFFE604
set AT91C_DDR2C_T0PR 0xFFFFE60C
set AT91C_DDR2C_DELAY5 0xFFFFE640
set AT91C_DDR2C_LPR 0xFFFFE61C
set AT91C_DDR2C_HS  0xFFFFE62C
set AT91C_DDR2C_DELAY2 0xFFFFE634
set AT91C_DDR2C_T2PR 0xFFFFE614
set AT91C_DDR2C_DELAY1 0xFFFFE630
set AT91C_DDR2C_T1PR 0xFFFFE610
set AT91C_DDR2C_MDR 0xFFFFE620
set AT91C_DDR2C_DELAY6 0xFFFFE644
set AT91C_DDR2C_VERSION 0xFFFFE6FC
set AT91C_DDR2C_MR  0xFFFFE600
set AT91C_DDR2C_DLL 0xFFFFE624
set AT91C_DDR2C_DELAY4 0xFFFFE63C
set AT91C_DDR2C_WPCR 0xFFFFE6E4
set AT91C_DDR2C_CR  0xFFFFE608
set AT91C_DDR2C_DELAY3 0xFFFFE638
set AT91C_DDR2C_WPSR 0xFFFFE6E8
set AT91C_DDR2C_DELAY7 0xFFFFE648
set AT91C_DDR2C_T3PR 0xFFFFE618
# ========== Register definition for SMC peripheral ========== 
set AT91C_SMC_PULSE7 0xFFFFE874
set AT91C_SMC_DELAY1 0xFFFFE8C0
set AT91C_SMC_CYCLE2 0xFFFFE828
set AT91C_SMC_DELAY5 0xFFFFE8D0
set AT91C_SMC_DELAY6 0xFFFFE8D4
set AT91C_SMC_PULSE2 0xFFFFE824
set AT91C_SMC_SETUP6 0xFFFFE860
set AT91C_SMC_SETUP5 0xFFFFE850
set AT91C_SMC_CYCLE6 0xFFFFE868
set AT91C_SMC_PULSE6 0xFFFFE864
set AT91C_SMC_CTRL5 0xFFFFE85C
set AT91C_SMC_CTRL3 0xFFFFE83C
set AT91C_SMC_DELAY7 0xFFFFE8D8
set AT91C_SMC_DELAY3 0xFFFFE8C8
set AT91C_SMC_CYCLE0 0xFFFFE808
set AT91C_SMC_SETUP1 0xFFFFE810
set AT91C_SMC_PULSE5 0xFFFFE854
set AT91C_SMC_SETUP7 0xFFFFE870
set AT91C_SMC_CTRL4 0xFFFFE84C
set AT91C_SMC_DELAY2 0xFFFFE8C4
set AT91C_SMC_PULSE3 0xFFFFE834
set AT91C_SMC_CYCLE4 0xFFFFE848
set AT91C_SMC_CTRL1 0xFFFFE81C
set AT91C_SMC_SETUP3 0xFFFFE830
set AT91C_SMC_CTRL0 0xFFFFE80C
set AT91C_SMC_CYCLE7 0xFFFFE878
set AT91C_SMC_DELAY4 0xFFFFE8CC
set AT91C_SMC_CYCLE1 0xFFFFE818
set AT91C_SMC_SETUP2 0xFFFFE820
set AT91C_SMC_PULSE1 0xFFFFE814
set AT91C_SMC_DELAY8 0xFFFFE8DC
set AT91C_SMC_CTRL2 0xFFFFE82C
set AT91C_SMC_PULSE4 0xFFFFE844
set AT91C_SMC_SETUP4 0xFFFFE840
set AT91C_SMC_CYCLE3 0xFFFFE838
set AT91C_SMC_SETUP0 0xFFFFE800
set AT91C_SMC_CYCLE5 0xFFFFE858
set AT91C_SMC_PULSE0 0xFFFFE804
set AT91C_SMC_CTRL6 0xFFFFE86C
set AT91C_SMC_CTRL7 0xFFFFE87C
# ========== Register definition for MATRIX peripheral ========== 
set AT91C_MATRIX_SCFG1 0xFFFFEA44
set AT91C_MATRIX_MRCR 0xFFFFEB00
set AT91C_MATRIX_PRAS2 0xFFFFEA90
set AT91C_MATRIX_PRAS1 0xFFFFEA88
set AT91C_MATRIX_PRAS0 0xFFFFEA80
set AT91C_MATRIX_MCFG8 0xFFFFEA20
set AT91C_MATRIX_MCFG2 0xFFFFEA08
set AT91C_MATRIX_PRAS4 0xFFFFEAA0
set AT91C_MATRIX_MCFG3 0xFFFFEA0C
set AT91C_MATRIX_SCFG0 0xFFFFEA40
set AT91C_MATRIX_MCFG7 0xFFFFEA1C
set AT91C_MATRIX_PRAS6 0xFFFFEAB0
set AT91C_MATRIX_SCFG7 0xFFFFEA5C
set AT91C_MATRIX_PRAS7 0xFFFFEAB8
set AT91C_MATRIX_SCFG2 0xFFFFEA48
set AT91C_MATRIX_WRPROTST 0xFFFFEBE8
set AT91C_MATRIX_PRBS0 0xFFFFEA84
set AT91C_MATRIX_PRBS2 0xFFFFEA94
set AT91C_MATRIX_MCFG4 0xFFFFEA10
set AT91C_MATRIX_SCFG5 0xFFFFEA54
set AT91C_MATRIX_PRBS6 0xFFFFEAB4
set AT91C_MATRIX_MCFG1 0xFFFFEA04
set AT91C_MATRIX_SCFG6 0xFFFFEA58
set AT91C_MATRIX_SCFG4 0xFFFFEA50
set AT91C_MATRIX_PRBS1 0xFFFFEA8C
set AT91C_MATRIX_PRBS3 0xFFFFEA9C
set AT91C_MATRIX_WRPROTEN 0xFFFFEBE4
set AT91C_MATRIX_MCFG11 0xFFFFEA2C
set AT91C_MATRIX_MCFG0 0xFFFFEA00
set AT91C_MATRIX_PRAS5 0xFFFFEAA8
set AT91C_MATRIX_PRBS4 0xFFFFEAA4
set AT91C_MATRIX_MCFG6 0xFFFFEA18
set AT91C_MATRIX_PRBS5 0xFFFFEAAC
set AT91C_MATRIX_MCFG9 0xFFFFEA24
set AT91C_MATRIX_MCFG5 0xFFFFEA14
set AT91C_MATRIX_PRBS7 0xFFFFEABC
set AT91C_MATRIX_MCFG10 0xFFFFEA28
set AT91C_MATRIX_PRAS3 0xFFFFEA98
set AT91C_MATRIX_SCFG3 0xFFFFEA4C
# ========== Register definition for CCFG peripheral ========== 
set AT91C_CCFG_TCMR 0xFFFFEB10
set AT91C_CCFG_VIDEO 0xFFFFEB18
set AT91C_CCFG_MATRIXVERSION 0xFFFFEBFC
set AT91C_CCFG_UDPHS 0xFFFFEB14
set AT91C_CCFG_EBICSA 0xFFFFEB28
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
# ========== Register definition for PDC_DBGU peripheral ========== 
set AT91C_DBGU_PTCR 0xFFFFEF20
set AT91C_DBGU_RCR  0xFFFFEF04
set AT91C_DBGU_TCR  0xFFFFEF0C
set AT91C_DBGU_RNCR 0xFFFFEF14
set AT91C_DBGU_TNPR 0xFFFFEF18
set AT91C_DBGU_RNPR 0xFFFFEF10
set AT91C_DBGU_PTSR 0xFFFFEF24
set AT91C_DBGU_RPR  0xFFFFEF00
set AT91C_DBGU_TPR  0xFFFFEF08
set AT91C_DBGU_TNCR 0xFFFFEF1C
# ========== Register definition for DBGU peripheral ========== 
set AT91C_DBGU_BRGR 0xFFFFEE20
set AT91C_DBGU_CR   0xFFFFEE00
set AT91C_DBGU_THR  0xFFFFEE1C
set AT91C_DBGU_IDR  0xFFFFEE0C
set AT91C_DBGU_EXID 0xFFFFEE44
set AT91C_DBGU_IMR  0xFFFFEE10
set AT91C_DBGU_FNTR 0xFFFFEE48
set AT91C_DBGU_IER  0xFFFFEE08
set AT91C_DBGU_CSR  0xFFFFEE14
set AT91C_DBGU_MR   0xFFFFEE04
set AT91C_DBGU_RHR  0xFFFFEE18
set AT91C_DBGU_CIDR 0xFFFFEE40
# ========== Register definition for PIOA peripheral ========== 
set AT91C_PIOA_OWDR 0xFFFFF2A4
set AT91C_PIOA_DELAY3 0xFFFFF2C8
set AT91C_PIOA_ISR  0xFFFFF24C
set AT91C_PIOA_PDR  0xFFFFF204
set AT91C_PIOA_OSR  0xFFFFF218
set AT91C_PIOA_ABSR 0xFFFFF278
set AT91C_PIOA_DELAY2 0xFFFFF2C4
set AT91C_PIOA_PDSR 0xFFFFF23C
set AT91C_PIOA_BSR  0xFFFFF274
set AT91C_PIOA_DELAY1 0xFFFFF2C0
set AT91C_PIOA_PPUER 0xFFFFF264
set AT91C_PIOA_OER  0xFFFFF210
set AT91C_PIOA_PER  0xFFFFF200
set AT91C_PIOA_VERSION 0xFFFFF2FC
set AT91C_PIOA_PPUDR 0xFFFFF260
set AT91C_PIOA_ODSR 0xFFFFF238
set AT91C_PIOA_SLEWRATE1 0xFFFFF2B0
set AT91C_PIOA_MDDR 0xFFFFF254
set AT91C_PIOA_IFSR 0xFFFFF228
set AT91C_PIOA_CODR 0xFFFFF234
set AT91C_PIOA_ASR  0xFFFFF270
set AT91C_PIOA_OWSR 0xFFFFF2A8
set AT91C_PIOA_IMR  0xFFFFF248
set AT91C_PIOA_PPUSR 0xFFFFF268
set AT91C_PIOA_MDER 0xFFFFF250
set AT91C_PIOA_IFDR 0xFFFFF224
set AT91C_PIOA_SODR 0xFFFFF230
set AT91C_PIOA_OWER 0xFFFFF2A0
set AT91C_PIOA_IDR  0xFFFFF244
set AT91C_PIOA_IFER 0xFFFFF220
set AT91C_PIOA_IER  0xFFFFF240
set AT91C_PIOA_ODR  0xFFFFF214
set AT91C_PIOA_MDSR 0xFFFFF258
set AT91C_PIOA_DELAY4 0xFFFFF2CC
set AT91C_PIOA_PSR  0xFFFFF208
# ========== Register definition for PIOB peripheral ========== 
set AT91C_PIOB_ODR  0xFFFFF414
set AT91C_PIOB_DELAY4 0xFFFFF4CC
set AT91C_PIOB_SODR 0xFFFFF430
set AT91C_PIOB_ISR  0xFFFFF44C
set AT91C_PIOB_ABSR 0xFFFFF478
set AT91C_PIOB_IMR  0xFFFFF448
set AT91C_PIOB_MDSR 0xFFFFF458
set AT91C_PIOB_PPUSR 0xFFFFF468
set AT91C_PIOB_PDSR 0xFFFFF43C
set AT91C_PIOB_DELAY3 0xFFFFF4C8
set AT91C_PIOB_MDDR 0xFFFFF454
set AT91C_PIOB_CODR 0xFFFFF434
set AT91C_PIOB_MDER 0xFFFFF450
set AT91C_PIOB_PDR  0xFFFFF404
set AT91C_PIOB_IFSR 0xFFFFF428
set AT91C_PIOB_PSR  0xFFFFF408
set AT91C_PIOB_SLEWRATE1 0xFFFFF4B0
set AT91C_PIOB_IER  0xFFFFF440
set AT91C_PIOB_PPUDR 0xFFFFF460
set AT91C_PIOB_PER  0xFFFFF400
set AT91C_PIOB_IFDR 0xFFFFF424
set AT91C_PIOB_IDR  0xFFFFF444
set AT91C_PIOB_OWDR 0xFFFFF4A4
set AT91C_PIOB_ODSR 0xFFFFF438
set AT91C_PIOB_DELAY2 0xFFFFF4C4
set AT91C_PIOB_OWSR 0xFFFFF4A8
set AT91C_PIOB_BSR  0xFFFFF474
set AT91C_PIOB_IFER 0xFFFFF420
set AT91C_PIOB_OWER 0xFFFFF4A0
set AT91C_PIOB_PPUER 0xFFFFF464
set AT91C_PIOB_OSR  0xFFFFF418
set AT91C_PIOB_ASR  0xFFFFF470
set AT91C_PIOB_OER  0xFFFFF410
set AT91C_PIOB_VERSION 0xFFFFF4FC
set AT91C_PIOB_DELAY1 0xFFFFF4C0
# ========== Register definition for PIOC peripheral ========== 
set AT91C_PIOC_OWDR 0xFFFFF6A4
set AT91C_PIOC_IMR  0xFFFFF648
set AT91C_PIOC_ASR  0xFFFFF670
set AT91C_PIOC_PPUDR 0xFFFFF660
set AT91C_PIOC_CODR 0xFFFFF634
set AT91C_PIOC_OWER 0xFFFFF6A0
set AT91C_PIOC_ABSR 0xFFFFF678
set AT91C_PIOC_IFDR 0xFFFFF624
set AT91C_PIOC_VERSION 0xFFFFF6FC
set AT91C_PIOC_ODR  0xFFFFF614
set AT91C_PIOC_PPUER 0xFFFFF664
set AT91C_PIOC_SODR 0xFFFFF630
set AT91C_PIOC_ISR  0xFFFFF64C
set AT91C_PIOC_OSR  0xFFFFF618
set AT91C_PIOC_MDSR 0xFFFFF658
set AT91C_PIOC_IFER 0xFFFFF620
set AT91C_PIOC_DELAY2 0xFFFFF6C4
set AT91C_PIOC_MDER 0xFFFFF650
set AT91C_PIOC_PPUSR 0xFFFFF668
set AT91C_PIOC_PSR  0xFFFFF608
set AT91C_PIOC_DELAY4 0xFFFFF6CC
set AT91C_PIOC_DELAY3 0xFFFFF6C8
set AT91C_PIOC_IER  0xFFFFF640
set AT91C_PIOC_SLEWRATE1 0xFFFFF6B0
set AT91C_PIOC_IDR  0xFFFFF644
set AT91C_PIOC_PDSR 0xFFFFF63C
set AT91C_PIOC_DELAY1 0xFFFFF6C0
set AT91C_PIOC_PDR  0xFFFFF604
set AT91C_PIOC_OWSR 0xFFFFF6A8
set AT91C_PIOC_IFSR 0xFFFFF628
set AT91C_PIOC_ODSR 0xFFFFF638
set AT91C_PIOC_OER  0xFFFFF610
set AT91C_PIOC_MDDR 0xFFFFF654
set AT91C_PIOC_BSR  0xFFFFF674
set AT91C_PIOC_PER  0xFFFFF600
# ========== Register definition for PIOD peripheral ========== 
set AT91C_PIOD_DELAY1 0xFFFFF8C0
set AT91C_PIOD_OWDR 0xFFFFF8A4
set AT91C_PIOD_SODR 0xFFFFF830
set AT91C_PIOD_PPUER 0xFFFFF864
set AT91C_PIOD_CODR 0xFFFFF834
set AT91C_PIOD_DELAY4 0xFFFFF8CC
set AT91C_PIOD_PSR  0xFFFFF808
set AT91C_PIOD_PDR  0xFFFFF804
set AT91C_PIOD_ODR  0xFFFFF814
set AT91C_PIOD_PPUSR 0xFFFFF868
set AT91C_PIOD_IFSR 0xFFFFF828
set AT91C_PIOD_IMR  0xFFFFF848
set AT91C_PIOD_ASR  0xFFFFF870
set AT91C_PIOD_DELAY2 0xFFFFF8C4
set AT91C_PIOD_OWSR 0xFFFFF8A8
set AT91C_PIOD_PER  0xFFFFF800
set AT91C_PIOD_MDER 0xFFFFF850
set AT91C_PIOD_PDSR 0xFFFFF83C
set AT91C_PIOD_MDSR 0xFFFFF858
set AT91C_PIOD_OWER 0xFFFFF8A0
set AT91C_PIOD_BSR  0xFFFFF874
set AT91C_PIOD_IFDR 0xFFFFF824
set AT91C_PIOD_DELAY3 0xFFFFF8C8
set AT91C_PIOD_ABSR 0xFFFFF878
set AT91C_PIOD_OER  0xFFFFF810
set AT91C_PIOD_MDDR 0xFFFFF854
set AT91C_PIOD_IDR  0xFFFFF844
set AT91C_PIOD_IER  0xFFFFF840
set AT91C_PIOD_PPUDR 0xFFFFF860
set AT91C_PIOD_VERSION 0xFFFFF8FC
set AT91C_PIOD_ISR  0xFFFFF84C
set AT91C_PIOD_ODSR 0xFFFFF838
set AT91C_PIOD_OSR  0xFFFFF818
set AT91C_PIOD_IFER 0xFFFFF820
set AT91C_PIOD_SLEWRATE1 0xFFFFF8B0
# ========== Register definition for PIOE peripheral ========== 
set AT91C_PIOE_ODSR 0xFFFFFA38
set AT91C_PIOE_ABSR 0xFFFFFA78
set AT91C_PIOE_PSR  0xFFFFFA08
set AT91C_PIOE_PPUDR 0xFFFFFA60
set AT91C_PIOE_OER  0xFFFFFA10
set AT91C_PIOE_IFSR 0xFFFFFA28
set AT91C_PIOE_IFER 0xFFFFFA20
set AT91C_PIOE_DELAY3 0xFFFFFAC8
set AT91C_PIOE_ODR  0xFFFFFA14
set AT91C_PIOE_IDR  0xFFFFFA44
set AT91C_PIOE_DELAY1 0xFFFFFAC0
set AT91C_PIOE_OSR  0xFFFFFA18
set AT91C_PIOE_CODR 0xFFFFFA34
set AT91C_PIOE_VERSION 0xFFFFFAFC
set AT91C_PIOE_MDSR 0xFFFFFA58
set AT91C_PIOE_PDR  0xFFFFFA04
set AT91C_PIOE_IER  0xFFFFFA40
set AT91C_PIOE_OWSR 0xFFFFFAA8
set AT91C_PIOE_BSR  0xFFFFFA74
set AT91C_PIOE_SLEWRATE1 0xFFFFFAB0
set AT91C_PIOE_DELAY4 0xFFFFFACC
set AT91C_PIOE_PER  0xFFFFFA00
set AT91C_PIOE_OWDR 0xFFFFFAA4
set AT91C_PIOE_IFDR 0xFFFFFA24
set AT91C_PIOE_PPUSR 0xFFFFFA68
set AT91C_PIOE_PDSR 0xFFFFFA3C
set AT91C_PIOE_PPUER 0xFFFFFA64
set AT91C_PIOE_MDDR 0xFFFFFA54
set AT91C_PIOE_ISR  0xFFFFFA4C
set AT91C_PIOE_DELAY2 0xFFFFFAC4
set AT91C_PIOE_SODR 0xFFFFFA30
set AT91C_PIOE_ASR  0xFFFFFA70
set AT91C_PIOE_IMR  0xFFFFFA48
set AT91C_PIOE_OWER 0xFFFFFAA0
set AT91C_PIOE_MDER 0xFFFFFA50
# ========== Register definition for PMC peripheral ========== 
set AT91C_PMC_ADDRSIZE 0xFFFFFCEC
set AT91C_PMC_PCER  0xFFFFFC10
set AT91C_PMC_PCKR  0xFFFFFC40
set AT91C_PMC_MCKR  0xFFFFFC30
set AT91C_PMC_PLLAR 0xFFFFFC28
set AT91C_PMC_NAME2 0xFFFFFCF4
set AT91C_PMC_PCDR  0xFFFFFC14
set AT91C_PMC_SCSR  0xFFFFFC08
set AT91C_PMC_MCFR  0xFFFFFC24
set AT91C_PMC_FEATURES 0xFFFFFCF8
set AT91C_PMC_PLLICPR 0xFFFFFC80
set AT91C_PMC_IMR   0xFFFFFC6C
set AT91C_PMC_IER   0xFFFFFC60
set AT91C_PMC_UCKR  0xFFFFFC1C
set AT91C_PMC_USB   0xFFFFFC38
set AT91C_PMC_MOR   0xFFFFFC20
set AT91C_PMC_IDR   0xFFFFFC64
set AT91C_PMC_NAME1 0xFFFFFCF0
set AT91C_PMC_SCDR  0xFFFFFC04
set AT91C_PMC_PCSR  0xFFFFFC18
set AT91C_PMC_SCER  0xFFFFFC00
set AT91C_PMC_VERSION 0xFFFFFCFC
set AT91C_PMC_SR    0xFFFFFC68
# ========== Register definition for CKGR peripheral ========== 
set AT91C_CKGR_MOR  0xFFFFFC20
set AT91C_CKGR_MCFR 0xFFFFFC24
set AT91C_CKGR_PLLAR 0xFFFFFC28
set AT91C_CKGR_UCKR 0xFFFFFC1C
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
# ========== Register definition for RTC peripheral ========== 
set AT91C_RTC_IDR   0xFFFFFDD4
set AT91C_RTC_SR    0xFFFFFDC8
set AT91C_RTC_MR    0xFFFFFDB4
set AT91C_RTC_IER   0xFFFFFDD0
set AT91C_RTC_TIMALR 0xFFFFFDC0
set AT91C_RTC_CALALR 0xFFFFFDC4
set AT91C_RTC_CR    0xFFFFFDB0
set AT91C_RTC_TIMR  0xFFFFFDB8
set AT91C_RTC_CALR  0xFFFFFDBC
set AT91C_RTC_VER   0xFFFFFDDC
set AT91C_RTC_SCCR  0xFFFFFDCC
set AT91C_RTC_IMR   0xFFFFFDD8
# ========== Register definition for TC0 peripheral ========== 
set AT91C_TC0_IER   0xFFF7C024
set AT91C_TC0_IMR   0xFFF7C02C
set AT91C_TC0_CCR   0xFFF7C000
set AT91C_TC0_RB    0xFFF7C018
set AT91C_TC0_CV    0xFFF7C010
set AT91C_TC0_SR    0xFFF7C020
set AT91C_TC0_CMR   0xFFF7C004
set AT91C_TC0_RA    0xFFF7C014
set AT91C_TC0_RC    0xFFF7C01C
set AT91C_TC0_IDR   0xFFF7C028
# ========== Register definition for TC1 peripheral ========== 
set AT91C_TC1_IER   0xFFF7C064
set AT91C_TC1_SR    0xFFF7C060
set AT91C_TC1_RC    0xFFF7C05C
set AT91C_TC1_CV    0xFFF7C050
set AT91C_TC1_RA    0xFFF7C054
set AT91C_TC1_CMR   0xFFF7C044
set AT91C_TC1_IDR   0xFFF7C068
set AT91C_TC1_RB    0xFFF7C058
set AT91C_TC1_IMR   0xFFF7C06C
set AT91C_TC1_CCR   0xFFF7C040
# ========== Register definition for TC2 peripheral ========== 
set AT91C_TC2_SR    0xFFF7C0A0
set AT91C_TC2_IMR   0xFFF7C0AC
set AT91C_TC2_IER   0xFFF7C0A4
set AT91C_TC2_CV    0xFFF7C090
set AT91C_TC2_RB    0xFFF7C098
set AT91C_TC2_CCR   0xFFF7C080
set AT91C_TC2_CMR   0xFFF7C084
set AT91C_TC2_RA    0xFFF7C094
set AT91C_TC2_IDR   0xFFF7C0A8
set AT91C_TC2_RC    0xFFF7C09C
# ========== Register definition for TC3 peripheral ========== 
set AT91C_TC3_SR    0xFFFD4020
set AT91C_TC3_RC    0xFFFD401C
set AT91C_TC3_IER   0xFFFD4024
set AT91C_TC3_CV    0xFFFD4010
set AT91C_TC3_IDR   0xFFFD4028
set AT91C_TC3_IMR   0xFFFD402C
set AT91C_TC3_CMR   0xFFFD4004
set AT91C_TC3_RB    0xFFFD4018
set AT91C_TC3_CCR   0xFFFD4000
set AT91C_TC3_RA    0xFFFD4014
# ========== Register definition for TC4 peripheral ========== 
set AT91C_TC4_CV    0xFFFD4050
set AT91C_TC4_RA    0xFFFD4054
set AT91C_TC4_IDR   0xFFFD4068
set AT91C_TC4_SR    0xFFFD4060
set AT91C_TC4_CMR   0xFFFD4044
set AT91C_TC4_CCR   0xFFFD4040
set AT91C_TC4_RB    0xFFFD4058
set AT91C_TC4_RC    0xFFFD405C
set AT91C_TC4_IER   0xFFFD4064
set AT91C_TC4_IMR   0xFFFD406C
# ========== Register definition for TC5 peripheral ========== 
set AT91C_TC5_IER   0xFFFD40A4
set AT91C_TC5_IDR   0xFFFD40A8
set AT91C_TC5_RA    0xFFFD4094
set AT91C_TC5_RB    0xFFFD4098
set AT91C_TC5_CCR   0xFFFD4080
set AT91C_TC5_SR    0xFFFD40A0
set AT91C_TC5_CV    0xFFFD4090
set AT91C_TC5_RC    0xFFFD409C
set AT91C_TC5_IMR   0xFFFD40AC
set AT91C_TC5_CMR   0xFFFD4084
# ========== Register definition for TCB0 peripheral ========== 
set AT91C_TCB0_BCR  0xFFF7C0C0
set AT91C_TCB0_BMR  0xFFF7C0C4
# ========== Register definition for TCB1 peripheral ========== 
set AT91C_TCB1_BMR  0xFFFD40C4
set AT91C_TCB1_BCR  0xFFFD40C0
# ========== Register definition for MCI0 peripheral ========== 
set AT91C_MCI0_IMR  0xFFF8004C
set AT91C_MCI0_MR   0xFFF80004
set AT91C_MCI0_CR   0xFFF80000
set AT91C_MCI0_IER  0xFFF80044
set AT91C_MCI0_FIFO 0xFFF80200
set AT91C_MCI0_DTOR 0xFFF80008
set AT91C_MCI0_SDCR 0xFFF8000C
set AT91C_MCI0_BLKR 0xFFF80018
set AT91C_MCI0_VR   0xFFF800FC
set AT91C_MCI0_WPSR 0xFFF800E8
set AT91C_MCI0_CMDR 0xFFF80014
set AT91C_MCI0_CSTOR 0xFFF8001C
set AT91C_MCI0_DMA  0xFFF80050
set AT91C_MCI0_RDR  0xFFF80030
set AT91C_MCI0_SR   0xFFF80040
set AT91C_MCI0_TDR  0xFFF80034
set AT91C_MCI0_CFG  0xFFF80054
set AT91C_MCI0_ARGR 0xFFF80010
set AT91C_MCI0_RSPR 0xFFF80020
set AT91C_MCI0_WPCR 0xFFF800E4
set AT91C_MCI0_IDR  0xFFF80048
# ========== Register definition for MCI1 peripheral ========== 
set AT91C_MCI1_IDR  0xFFFD0048
set AT91C_MCI1_MR   0xFFFD0004
set AT91C_MCI1_SR   0xFFFD0040
set AT91C_MCI1_DTOR 0xFFFD0008
set AT91C_MCI1_WPCR 0xFFFD00E4
set AT91C_MCI1_ARGR 0xFFFD0010
set AT91C_MCI1_FIFO 0xFFFD0200
set AT91C_MCI1_IER  0xFFFD0044
set AT91C_MCI1_SDCR 0xFFFD000C
set AT91C_MCI1_CR   0xFFFD0000
set AT91C_MCI1_CSTOR 0xFFFD001C
set AT91C_MCI1_RSPR 0xFFFD0020
set AT91C_MCI1_IMR  0xFFFD004C
set AT91C_MCI1_DMA  0xFFFD0050
set AT91C_MCI1_BLKR 0xFFFD0018
set AT91C_MCI1_RDR  0xFFFD0030
set AT91C_MCI1_CFG  0xFFFD0054
set AT91C_MCI1_WPSR 0xFFFD00E8
set AT91C_MCI1_CMDR 0xFFFD0014
set AT91C_MCI1_TDR  0xFFFD0034
set AT91C_MCI1_VR   0xFFFD00FC
# ========== Register definition for TWI0 peripheral ========== 
set AT91C_TWI0_RHR  0xFFF84030
set AT91C_TWI0_IMR  0xFFF8402C
set AT91C_TWI0_SR   0xFFF84020
set AT91C_TWI0_IADR 0xFFF8400C
set AT91C_TWI0_IDR  0xFFF84028
set AT91C_TWI0_CWGR 0xFFF84010
set AT91C_TWI0_IER  0xFFF84024
set AT91C_TWI0_THR  0xFFF84034
set AT91C_TWI0_CR   0xFFF84000
set AT91C_TWI0_MMR  0xFFF84004
# ========== Register definition for TWI1 peripheral ========== 
set AT91C_TWI1_IDR  0xFFF88028
set AT91C_TWI1_RHR  0xFFF88030
set AT91C_TWI1_IMR  0xFFF8802C
set AT91C_TWI1_THR  0xFFF88034
set AT91C_TWI1_IER  0xFFF88024
set AT91C_TWI1_IADR 0xFFF8800C
set AT91C_TWI1_MMR  0xFFF88004
set AT91C_TWI1_CR   0xFFF88000
set AT91C_TWI1_SR   0xFFF88020
set AT91C_TWI1_CWGR 0xFFF88010
# ========== Register definition for PDC_US0 peripheral ========== 
set AT91C_US0_TNPR  0xFFF8C118
set AT91C_US0_PTSR  0xFFF8C124
set AT91C_US0_PTCR  0xFFF8C120
set AT91C_US0_RNCR  0xFFF8C114
set AT91C_US0_RCR   0xFFF8C104
set AT91C_US0_TNCR  0xFFF8C11C
set AT91C_US0_TCR   0xFFF8C10C
set AT91C_US0_RNPR  0xFFF8C110
set AT91C_US0_RPR   0xFFF8C100
set AT91C_US0_TPR   0xFFF8C108
# ========== Register definition for US0 peripheral ========== 
set AT91C_US0_RTOR  0xFFF8C024
set AT91C_US0_MAN   0xFFF8C050
set AT91C_US0_NER   0xFFF8C044
set AT91C_US0_THR   0xFFF8C01C
set AT91C_US0_MR    0xFFF8C004
set AT91C_US0_RHR   0xFFF8C018
set AT91C_US0_CSR   0xFFF8C014
set AT91C_US0_IMR   0xFFF8C010
set AT91C_US0_IDR   0xFFF8C00C
set AT91C_US0_FIDI  0xFFF8C040
set AT91C_US0_CR    0xFFF8C000
set AT91C_US0_IER   0xFFF8C008
set AT91C_US0_TTGR  0xFFF8C028
set AT91C_US0_BRGR  0xFFF8C020
set AT91C_US0_IF    0xFFF8C04C
# ========== Register definition for PDC_US1 peripheral ========== 
set AT91C_US1_PTCR  0xFFF90120
set AT91C_US1_TNCR  0xFFF9011C
set AT91C_US1_RCR   0xFFF90104
set AT91C_US1_RPR   0xFFF90100
set AT91C_US1_TPR   0xFFF90108
set AT91C_US1_TCR   0xFFF9010C
set AT91C_US1_RNPR  0xFFF90110
set AT91C_US1_TNPR  0xFFF90118
set AT91C_US1_RNCR  0xFFF90114
set AT91C_US1_PTSR  0xFFF90124
# ========== Register definition for US1 peripheral ========== 
set AT91C_US1_NER   0xFFF90044
set AT91C_US1_RHR   0xFFF90018
set AT91C_US1_RTOR  0xFFF90024
set AT91C_US1_IER   0xFFF90008
set AT91C_US1_IF    0xFFF9004C
set AT91C_US1_MAN   0xFFF90050
set AT91C_US1_CR    0xFFF90000
set AT91C_US1_IMR   0xFFF90010
set AT91C_US1_TTGR  0xFFF90028
set AT91C_US1_MR    0xFFF90004
set AT91C_US1_IDR   0xFFF9000C
set AT91C_US1_FIDI  0xFFF90040
set AT91C_US1_CSR   0xFFF90014
set AT91C_US1_THR   0xFFF9001C
set AT91C_US1_BRGR  0xFFF90020
# ========== Register definition for PDC_US2 peripheral ========== 
set AT91C_US2_RNCR  0xFFF94114
set AT91C_US2_PTCR  0xFFF94120
set AT91C_US2_TNPR  0xFFF94118
set AT91C_US2_TNCR  0xFFF9411C
set AT91C_US2_TPR   0xFFF94108
set AT91C_US2_RCR   0xFFF94104
set AT91C_US2_PTSR  0xFFF94124
set AT91C_US2_TCR   0xFFF9410C
set AT91C_US2_RPR   0xFFF94100
set AT91C_US2_RNPR  0xFFF94110
# ========== Register definition for US2 peripheral ========== 
set AT91C_US2_TTGR  0xFFF94028
set AT91C_US2_RHR   0xFFF94018
set AT91C_US2_IMR   0xFFF94010
set AT91C_US2_IER   0xFFF94008
set AT91C_US2_NER   0xFFF94044
set AT91C_US2_CR    0xFFF94000
set AT91C_US2_FIDI  0xFFF94040
set AT91C_US2_MR    0xFFF94004
set AT91C_US2_MAN   0xFFF94050
set AT91C_US2_IDR   0xFFF9400C
set AT91C_US2_THR   0xFFF9401C
set AT91C_US2_IF    0xFFF9404C
set AT91C_US2_BRGR  0xFFF94020
set AT91C_US2_CSR   0xFFF94014
set AT91C_US2_RTOR  0xFFF94024
# ========== Register definition for PDC_US3 peripheral ========== 
set AT91C_US3_PTSR  0xFFF98124
set AT91C_US3_TCR   0xFFF9810C
set AT91C_US3_RNPR  0xFFF98110
set AT91C_US3_RNCR  0xFFF98114
set AT91C_US3_TNPR  0xFFF98118
set AT91C_US3_RPR   0xFFF98100
set AT91C_US3_TPR   0xFFF98108
set AT91C_US3_RCR   0xFFF98104
set AT91C_US3_TNCR  0xFFF9811C
set AT91C_US3_PTCR  0xFFF98120
# ========== Register definition for US3 peripheral ========== 
set AT91C_US3_CSR   0xFFF98014
set AT91C_US3_BRGR  0xFFF98020
set AT91C_US3_TTGR  0xFFF98028
set AT91C_US3_IER   0xFFF98008
set AT91C_US3_RTOR  0xFFF98024
set AT91C_US3_MR    0xFFF98004
set AT91C_US3_IF    0xFFF9804C
set AT91C_US3_MAN   0xFFF98050
set AT91C_US3_NER   0xFFF98044
set AT91C_US3_FIDI  0xFFF98040
set AT91C_US3_CR    0xFFF98000
set AT91C_US3_IDR   0xFFF9800C
set AT91C_US3_IMR   0xFFF98010
set AT91C_US3_THR   0xFFF9801C
set AT91C_US3_RHR   0xFFF98018
# ========== Register definition for PDC_SSC0 peripheral ========== 
set AT91C_SSC0_TNPR 0xFFF9C118
set AT91C_SSC0_PTSR 0xFFF9C124
set AT91C_SSC0_TNCR 0xFFF9C11C
set AT91C_SSC0_RNCR 0xFFF9C114
set AT91C_SSC0_TPR  0xFFF9C108
set AT91C_SSC0_RCR  0xFFF9C104
set AT91C_SSC0_PTCR 0xFFF9C120
set AT91C_SSC0_RNPR 0xFFF9C110
set AT91C_SSC0_TCR  0xFFF9C10C
set AT91C_SSC0_RPR  0xFFF9C100
# ========== Register definition for SSC0 peripheral ========== 
set AT91C_SSC0_CMR  0xFFF9C004
set AT91C_SSC0_SR   0xFFF9C040
set AT91C_SSC0_TSHR 0xFFF9C034
set AT91C_SSC0_TCMR 0xFFF9C018
set AT91C_SSC0_IMR  0xFFF9C04C
set AT91C_SSC0_IDR  0xFFF9C048
set AT91C_SSC0_RCMR 0xFFF9C010
set AT91C_SSC0_IER  0xFFF9C044
set AT91C_SSC0_RSHR 0xFFF9C030
set AT91C_SSC0_CR   0xFFF9C000
set AT91C_SSC0_RHR  0xFFF9C020
set AT91C_SSC0_THR  0xFFF9C024
set AT91C_SSC0_RFMR 0xFFF9C014
set AT91C_SSC0_TFMR 0xFFF9C01C
# ========== Register definition for PDC_SSC1 peripheral ========== 
set AT91C_SSC1_RNPR 0xFFFA0110
set AT91C_SSC1_TCR  0xFFFA010C
set AT91C_SSC1_TNCR 0xFFFA011C
set AT91C_SSC1_RCR  0xFFFA0104
set AT91C_SSC1_RNCR 0xFFFA0114
set AT91C_SSC1_PTCR 0xFFFA0120
set AT91C_SSC1_TPR  0xFFFA0108
set AT91C_SSC1_RPR  0xFFFA0100
set AT91C_SSC1_PTSR 0xFFFA0124
set AT91C_SSC1_TNPR 0xFFFA0118
# ========== Register definition for SSC1 peripheral ========== 
set AT91C_SSC1_SR   0xFFFA0040
set AT91C_SSC1_RHR  0xFFFA0020
set AT91C_SSC1_TFMR 0xFFFA001C
set AT91C_SSC1_TCMR 0xFFFA0018
set AT91C_SSC1_CR   0xFFFA0000
set AT91C_SSC1_RSHR 0xFFFA0030
set AT91C_SSC1_CMR  0xFFFA0004
set AT91C_SSC1_IER  0xFFFA0044
set AT91C_SSC1_THR  0xFFFA0024
set AT91C_SSC1_IMR  0xFFFA004C
set AT91C_SSC1_TSHR 0xFFFA0034
set AT91C_SSC1_RFMR 0xFFFA0014
set AT91C_SSC1_IDR  0xFFFA0048
set AT91C_SSC1_RCMR 0xFFFA0010
# ========== Register definition for PWMC_CH0 peripheral ========== 
set AT91C_PWMC_CH0_CCNTR 0xFFFB820C
set AT91C_PWMC_CH0_CPRDR 0xFFFB8208
set AT91C_PWMC_CH0_CUPDR 0xFFFB8210
set AT91C_PWMC_CH0_CDTYR 0xFFFB8204
set AT91C_PWMC_CH0_CMR 0xFFFB8200
set AT91C_PWMC_CH0_Reserved 0xFFFB8214
# ========== Register definition for PWMC_CH1 peripheral ========== 
set AT91C_PWMC_CH1_CCNTR 0xFFFB822C
set AT91C_PWMC_CH1_CDTYR 0xFFFB8224
set AT91C_PWMC_CH1_CMR 0xFFFB8220
set AT91C_PWMC_CH1_CPRDR 0xFFFB8228
set AT91C_PWMC_CH1_Reserved 0xFFFB8234
set AT91C_PWMC_CH1_CUPDR 0xFFFB8230
# ========== Register definition for PWMC_CH2 peripheral ========== 
set AT91C_PWMC_CH2_CUPDR 0xFFFB8250
set AT91C_PWMC_CH2_CMR 0xFFFB8240
set AT91C_PWMC_CH2_Reserved 0xFFFB8254
set AT91C_PWMC_CH2_CPRDR 0xFFFB8248
set AT91C_PWMC_CH2_CDTYR 0xFFFB8244
set AT91C_PWMC_CH2_CCNTR 0xFFFB824C
# ========== Register definition for PWMC_CH3 peripheral ========== 
set AT91C_PWMC_CH3_CPRDR 0xFFFB8268
set AT91C_PWMC_CH3_Reserved 0xFFFB8274
set AT91C_PWMC_CH3_CUPDR 0xFFFB8270
set AT91C_PWMC_CH3_CDTYR 0xFFFB8264
set AT91C_PWMC_CH3_CCNTR 0xFFFB826C
set AT91C_PWMC_CH3_CMR 0xFFFB8260
# ========== Register definition for PWMC peripheral ========== 
set AT91C_PWMC_IDR  0xFFFB8014
set AT91C_PWMC_MR   0xFFFB8000
set AT91C_PWMC_VR   0xFFFB80FC
set AT91C_PWMC_IMR  0xFFFB8018
set AT91C_PWMC_SR   0xFFFB800C
set AT91C_PWMC_ISR  0xFFFB801C
set AT91C_PWMC_ENA  0xFFFB8004
set AT91C_PWMC_IER  0xFFFB8010
set AT91C_PWMC_DIS  0xFFFB8008
# ========== Register definition for PDC_SPI0 peripheral ========== 
set AT91C_SPI0_TPR  0xFFFA4108
set AT91C_SPI0_PTCR 0xFFFA4120
set AT91C_SPI0_RNPR 0xFFFA4110
set AT91C_SPI0_TNCR 0xFFFA411C
set AT91C_SPI0_TCR  0xFFFA410C
set AT91C_SPI0_RCR  0xFFFA4104
set AT91C_SPI0_RNCR 0xFFFA4114
set AT91C_SPI0_TNPR 0xFFFA4118
set AT91C_SPI0_RPR  0xFFFA4100
set AT91C_SPI0_PTSR 0xFFFA4124
# ========== Register definition for PDC_SPI1 peripheral ========== 
set AT91C_SPI1_RNCR 0xFFFA8114
set AT91C_SPI1_TCR  0xFFFA810C
set AT91C_SPI1_RCR  0xFFFA8104
set AT91C_SPI1_TNPR 0xFFFA8118
set AT91C_SPI1_RNPR 0xFFFA8110
set AT91C_SPI1_RPR  0xFFFA8100
set AT91C_SPI1_TNCR 0xFFFA811C
set AT91C_SPI1_TPR  0xFFFA8108
set AT91C_SPI1_PTSR 0xFFFA8124
set AT91C_SPI1_PTCR 0xFFFA8120
# ========== Register definition for SPI0 peripheral ========== 
set AT91C_SPI0_MR   0xFFFA4004
set AT91C_SPI0_RDR  0xFFFA4008
set AT91C_SPI0_CR   0xFFFA4000
set AT91C_SPI0_IER  0xFFFA4014
set AT91C_SPI0_TDR  0xFFFA400C
set AT91C_SPI0_IDR  0xFFFA4018
set AT91C_SPI0_CSR  0xFFFA4030
set AT91C_SPI0_SR   0xFFFA4010
set AT91C_SPI0_IMR  0xFFFA401C
# ========== Register definition for SPI1 peripheral ========== 
set AT91C_SPI1_CSR  0xFFFA8030
set AT91C_SPI1_IER  0xFFFA8014
set AT91C_SPI1_RDR  0xFFFA8008
set AT91C_SPI1_IDR  0xFFFA8018
set AT91C_SPI1_MR   0xFFFA8004
set AT91C_SPI1_CR   0xFFFA8000
set AT91C_SPI1_SR   0xFFFA8010
set AT91C_SPI1_TDR  0xFFFA800C
set AT91C_SPI1_IMR  0xFFFA801C
# ========== Register definition for PDC_TSADC peripheral ========== 
set AT91C_TSADC_TCR 0xFFFB010C
set AT91C_TSADC_PTCR 0xFFFB0120
set AT91C_TSADC_RNCR 0xFFFB0114
set AT91C_TSADC_PTSR 0xFFFB0124
set AT91C_TSADC_TNCR 0xFFFB011C
set AT91C_TSADC_RNPR 0xFFFB0110
set AT91C_TSADC_RCR 0xFFFB0104
set AT91C_TSADC_TPR 0xFFFB0108
set AT91C_TSADC_TNPR 0xFFFB0118
set AT91C_TSADC_RPR 0xFFFB0100
# ========== Register definition for TSADC peripheral ========== 
set AT91C_TSADC_CHSR 0xFFFB0018
set AT91C_TSADC_CDR5 0xFFFB0044
set AT91C_TSADC_CR  0xFFFB0000
set AT91C_TSADC_IMR 0xFFFB002C
set AT91C_TSADC_CHDR 0xFFFB0014
set AT91C_TSADC_LCDR 0xFFFB0020
set AT91C_TSADC_IER 0xFFFB0024
set AT91C_TSADC_TSR 0xFFFB000C
set AT91C_TSADC_CDR2 0xFFFB0038
set AT91C_TSADC_CDR4 0xFFFB0040
set AT91C_TSADC_CHER 0xFFFB0010
set AT91C_TSADC_TRGR 0xFFFB0008
set AT91C_TSADC_CDR3 0xFFFB003C
set AT91C_TSADC_SR  0xFFFB001C
set AT91C_TSADC_CDR0 0xFFFB0030
set AT91C_TSADC_CDR6 0xFFFB0048
set AT91C_TSADC_IDR 0xFFFB0028
set AT91C_TSADC_MR  0xFFFB0004
set AT91C_TSADC_CDR7 0xFFFB004C
set AT91C_TSADC_CDR1 0xFFFB0034
# ========== Register definition for UDPHS_EPTFIFO peripheral ========== 
set AT91C_UDPHS_EPTFIFO_READEPT3 0x00630000
set AT91C_UDPHS_EPTFIFO_READEPT5 0x00650000
set AT91C_UDPHS_EPTFIFO_READEPT1 0x00610000
set AT91C_UDPHS_EPTFIFO_READEPT0 0x00600000
set AT91C_UDPHS_EPTFIFO_READEPT6 0x00660000
set AT91C_UDPHS_EPTFIFO_READEPT2 0x00620000
set AT91C_UDPHS_EPTFIFO_READEPT4 0x00640000
# ========== Register definition for UDPHS_EPT_0 peripheral ========== 
set AT91C_UDPHS_EPT_0_EPTSTA 0xFFF7811C
set AT91C_UDPHS_EPT_0_EPTCTL 0xFFF7810C
set AT91C_UDPHS_EPT_0_EPTCTLDIS 0xFFF78108
set AT91C_UDPHS_EPT_0_EPTCFG 0xFFF78100
set AT91C_UDPHS_EPT_0_EPTCLRSTA 0xFFF78118
set AT91C_UDPHS_EPT_0_EPTSETSTA 0xFFF78114
set AT91C_UDPHS_EPT_0_EPTCTLENB 0xFFF78104
# ========== Register definition for UDPHS_EPT_1 peripheral ========== 
set AT91C_UDPHS_EPT_1_EPTCTLENB 0xFFF78124
set AT91C_UDPHS_EPT_1_EPTCFG 0xFFF78120
set AT91C_UDPHS_EPT_1_EPTCTL 0xFFF7812C
set AT91C_UDPHS_EPT_1_EPTSTA 0xFFF7813C
set AT91C_UDPHS_EPT_1_EPTCLRSTA 0xFFF78138
set AT91C_UDPHS_EPT_1_EPTSETSTA 0xFFF78134
set AT91C_UDPHS_EPT_1_EPTCTLDIS 0xFFF78128
# ========== Register definition for UDPHS_EPT_2 peripheral ========== 
set AT91C_UDPHS_EPT_2_EPTCLRSTA 0xFFF78158
set AT91C_UDPHS_EPT_2_EPTCTLDIS 0xFFF78148
set AT91C_UDPHS_EPT_2_EPTSTA 0xFFF7815C
set AT91C_UDPHS_EPT_2_EPTSETSTA 0xFFF78154
set AT91C_UDPHS_EPT_2_EPTCTL 0xFFF7814C
set AT91C_UDPHS_EPT_2_EPTCFG 0xFFF78140
set AT91C_UDPHS_EPT_2_EPTCTLENB 0xFFF78144
# ========== Register definition for UDPHS_EPT_3 peripheral ========== 
set AT91C_UDPHS_EPT_3_EPTCTL 0xFFF7816C
set AT91C_UDPHS_EPT_3_EPTCLRSTA 0xFFF78178
set AT91C_UDPHS_EPT_3_EPTCTLDIS 0xFFF78168
set AT91C_UDPHS_EPT_3_EPTSTA 0xFFF7817C
set AT91C_UDPHS_EPT_3_EPTSETSTA 0xFFF78174
set AT91C_UDPHS_EPT_3_EPTCTLENB 0xFFF78164
set AT91C_UDPHS_EPT_3_EPTCFG 0xFFF78160
# ========== Register definition for UDPHS_EPT_4 peripheral ========== 
set AT91C_UDPHS_EPT_4_EPTCLRSTA 0xFFF78198
set AT91C_UDPHS_EPT_4_EPTCTL 0xFFF7818C
set AT91C_UDPHS_EPT_4_EPTCTLENB 0xFFF78184
set AT91C_UDPHS_EPT_4_EPTSTA 0xFFF7819C
set AT91C_UDPHS_EPT_4_EPTSETSTA 0xFFF78194
set AT91C_UDPHS_EPT_4_EPTCFG 0xFFF78180
set AT91C_UDPHS_EPT_4_EPTCTLDIS 0xFFF78188
# ========== Register definition for UDPHS_EPT_5 peripheral ========== 
set AT91C_UDPHS_EPT_5_EPTSTA 0xFFF781BC
set AT91C_UDPHS_EPT_5_EPTCLRSTA 0xFFF781B8
set AT91C_UDPHS_EPT_5_EPTCTLENB 0xFFF781A4
set AT91C_UDPHS_EPT_5_EPTSETSTA 0xFFF781B4
set AT91C_UDPHS_EPT_5_EPTCTLDIS 0xFFF781A8
set AT91C_UDPHS_EPT_5_EPTCFG 0xFFF781A0
set AT91C_UDPHS_EPT_5_EPTCTL 0xFFF781AC
# ========== Register definition for UDPHS_EPT_6 peripheral ========== 
set AT91C_UDPHS_EPT_6_EPTCLRSTA 0xFFF781D8
set AT91C_UDPHS_EPT_6_EPTCTLENB 0xFFF781C4
set AT91C_UDPHS_EPT_6_EPTCTL 0xFFF781CC
set AT91C_UDPHS_EPT_6_EPTSETSTA 0xFFF781D4
set AT91C_UDPHS_EPT_6_EPTCTLDIS 0xFFF781C8
set AT91C_UDPHS_EPT_6_EPTSTA 0xFFF781DC
set AT91C_UDPHS_EPT_6_EPTCFG 0xFFF781C0
# ========== Register definition for UDPHS_DMA_1 peripheral ========== 
set AT91C_UDPHS_DMA_1_DMASTATUS 0xFFF7831C
set AT91C_UDPHS_DMA_1_DMANXTDSC 0xFFF78310
set AT91C_UDPHS_DMA_1_DMACONTROL 0xFFF78318
set AT91C_UDPHS_DMA_1_DMAADDRESS 0xFFF78314
# ========== Register definition for UDPHS_DMA_2 peripheral ========== 
set AT91C_UDPHS_DMA_2_DMACONTROL 0xFFF78328
set AT91C_UDPHS_DMA_2_DMASTATUS 0xFFF7832C
set AT91C_UDPHS_DMA_2_DMAADDRESS 0xFFF78324
set AT91C_UDPHS_DMA_2_DMANXTDSC 0xFFF78320
# ========== Register definition for UDPHS_DMA_3 peripheral ========== 
set AT91C_UDPHS_DMA_3_DMAADDRESS 0xFFF78334
set AT91C_UDPHS_DMA_3_DMANXTDSC 0xFFF78330
set AT91C_UDPHS_DMA_3_DMACONTROL 0xFFF78338
set AT91C_UDPHS_DMA_3_DMASTATUS 0xFFF7833C
# ========== Register definition for UDPHS_DMA_4 peripheral ========== 
set AT91C_UDPHS_DMA_4_DMANXTDSC 0xFFF78340
set AT91C_UDPHS_DMA_4_DMAADDRESS 0xFFF78344
set AT91C_UDPHS_DMA_4_DMACONTROL 0xFFF78348
set AT91C_UDPHS_DMA_4_DMASTATUS 0xFFF7834C
# ========== Register definition for UDPHS_DMA_5 peripheral ========== 
set AT91C_UDPHS_DMA_5_DMASTATUS 0xFFF7835C
set AT91C_UDPHS_DMA_5_DMACONTROL 0xFFF78358
set AT91C_UDPHS_DMA_5_DMANXTDSC 0xFFF78350
set AT91C_UDPHS_DMA_5_DMAADDRESS 0xFFF78354
# ========== Register definition for UDPHS_DMA_6 peripheral ========== 
set AT91C_UDPHS_DMA_6_DMANXTDSC 0xFFF78360
set AT91C_UDPHS_DMA_6_DMACONTROL 0xFFF78368
set AT91C_UDPHS_DMA_6_DMASTATUS 0xFFF7836C
set AT91C_UDPHS_DMA_6_DMAADDRESS 0xFFF78364
# ========== Register definition for UDPHS peripheral ========== 
set AT91C_UDPHS_IEN 0xFFF78010
set AT91C_UDPHS_TSTSOFCNT 0xFFF780D0
set AT91C_UDPHS_IPFEATURES 0xFFF780F8
set AT91C_UDPHS_TST 0xFFF780E0
set AT91C_UDPHS_FNUM 0xFFF78004
set AT91C_UDPHS_TSTCNTB 0xFFF780D8
set AT91C_UDPHS_RIPPADDRSIZE 0xFFF780EC
set AT91C_UDPHS_INTSTA 0xFFF78014
set AT91C_UDPHS_EPTRST 0xFFF7801C
set AT91C_UDPHS_TSTCNTA 0xFFF780D4
set AT91C_UDPHS_RIPNAME2 0xFFF780F4
set AT91C_UDPHS_RIPNAME1 0xFFF780F0
set AT91C_UDPHS_TSTMODREG 0xFFF780DC
set AT91C_UDPHS_CLRINT 0xFFF78018
set AT91C_UDPHS_IPVERSION 0xFFF780FC
set AT91C_UDPHS_CTRL 0xFFF78000
# ========== Register definition for PDC_AC97C peripheral ========== 
set AT91C_AC97C_PTSR 0xFFFAC124
set AT91C_AC97C_RPR 0xFFFAC100
set AT91C_AC97C_RNCR 0xFFFAC114
set AT91C_AC97C_RCR 0xFFFAC104
set AT91C_AC97C_PTCR 0xFFFAC120
set AT91C_AC97C_TPR 0xFFFAC108
set AT91C_AC97C_RNPR 0xFFFAC110
set AT91C_AC97C_TNPR 0xFFFAC118
set AT91C_AC97C_TCR 0xFFFAC10C
set AT91C_AC97C_TNCR 0xFFFAC11C
# ========== Register definition for AC97C peripheral ========== 
set AT91C_AC97C_IER 0xFFFAC054
set AT91C_AC97C_COTHR 0xFFFAC044
set AT91C_AC97C_IDR 0xFFFAC058
set AT91C_AC97C_ICA 0xFFFAC010
set AT91C_AC97C_CATHR 0xFFFAC024
set AT91C_AC97C_CBSR 0xFFFAC038
set AT91C_AC97C_CAMR 0xFFFAC02C
set AT91C_AC97C_SR  0xFFFAC050
set AT91C_AC97C_CBTHR 0xFFFAC034
set AT91C_AC97C_CASR 0xFFFAC028
set AT91C_AC97C_COSR 0xFFFAC048
set AT91C_AC97C_MR  0xFFFAC008
set AT91C_AC97C_OCA 0xFFFAC014
set AT91C_AC97C_CORHR 0xFFFAC040
set AT91C_AC97C_CBRHR 0xFFFAC030
set AT91C_AC97C_IMR 0xFFFAC05C
set AT91C_AC97C_COMR 0xFFFAC04C
set AT91C_AC97C_CARHR 0xFFFAC020
set AT91C_AC97C_VERSION 0xFFFAC0FC
set AT91C_AC97C_CBMR 0xFFFAC03C
# ========== Register definition for LCDC peripheral ========== 
set AT91C_LCDC_MVAL 0x00500818
set AT91C_LCDC_PWRCON 0x0050083C
set AT91C_LCDC_ISR  0x00500854
set AT91C_LCDC_FRMP1 0x00500008
set AT91C_LCDC_CTRSTVAL 0x00500844
set AT91C_LCDC_ICR  0x00500858
set AT91C_LCDC_TIM1 0x00500808
set AT91C_LCDC_DMACON 0x0050001C
set AT91C_LCDC_ITR  0x00500860
set AT91C_LCDC_IDR  0x0050084C
set AT91C_LCDC_DP4_7 0x00500820
set AT91C_LCDC_DP5_7 0x0050082C
set AT91C_LCDC_IRR  0x00500864
set AT91C_LCDC_DP3_4 0x00500830
set AT91C_LCDC_IMR  0x00500850
set AT91C_LCDC_LCDFRCFG 0x00500810
set AT91C_LCDC_CTRSTCON 0x00500840
set AT91C_LCDC_DP1_2 0x0050081C
set AT91C_LCDC_FRMP2 0x0050000C
set AT91C_LCDC_LCDCON1 0x00500800
set AT91C_LCDC_DP4_5 0x00500834
set AT91C_LCDC_FRMA2 0x00500014
set AT91C_LCDC_BA1  0x00500000
set AT91C_LCDC_DMA2DCFG 0x00500020
set AT91C_LCDC_LUT_ENTRY 0x00500C00
set AT91C_LCDC_DP6_7 0x00500838
set AT91C_LCDC_FRMCFG 0x00500018
set AT91C_LCDC_TIM2 0x0050080C
set AT91C_LCDC_DP3_5 0x00500824
set AT91C_LCDC_FRMA1 0x00500010
set AT91C_LCDC_IER  0x00500848
set AT91C_LCDC_DP2_3 0x00500828
set AT91C_LCDC_FIFO 0x00500814
set AT91C_LCDC_BA2  0x00500004
set AT91C_LCDC_LCDCON2 0x00500804
set AT91C_LCDC_GPR  0x0050085C
# ========== Register definition for LCDC_16B_TFT peripheral ========== 
set AT91C_TFT_MVAL  0x00500818
set AT91C_TFT_PWRCON 0x0050083C
set AT91C_TFT_ISR   0x00500854
set AT91C_TFT_FRMP1 0x00500008
set AT91C_TFT_CTRSTVAL 0x00500844
set AT91C_TFT_ICR   0x00500858
set AT91C_TFT_TIM1  0x00500808
set AT91C_TFT_DMACON 0x0050001C
set AT91C_TFT_ITR   0x00500860
set AT91C_TFT_IDR   0x0050084C
set AT91C_TFT_DP4_7 0x00500820
set AT91C_TFT_DP5_7 0x0050082C
set AT91C_TFT_IRR   0x00500864
set AT91C_TFT_DP3_4 0x00500830
set AT91C_TFT_IMR   0x00500850
set AT91C_TFT_LCDFRCFG 0x00500810
set AT91C_TFT_CTRSTCON 0x00500840
set AT91C_TFT_DP1_2 0x0050081C
set AT91C_TFT_FRMP2 0x0050000C
set AT91C_TFT_LCDCON1 0x00500800
set AT91C_TFT_DP4_5 0x00500834
set AT91C_TFT_FRMA2 0x00500014
set AT91C_TFT_BA1   0x00500000
set AT91C_TFT_DMA2DCFG 0x00500020
set AT91C_TFT_LUT_ENTRY 0x00500C00
set AT91C_TFT_DP6_7 0x00500838
set AT91C_TFT_FRMCFG 0x00500018
set AT91C_TFT_TIM2  0x0050080C
set AT91C_TFT_DP3_5 0x00500824
set AT91C_TFT_FRMA1 0x00500010
set AT91C_TFT_IER   0x00500848
set AT91C_TFT_DP2_3 0x00500828
set AT91C_TFT_FIFO  0x00500814
set AT91C_TFT_BA2   0x00500004
set AT91C_TFT_LCDCON2 0x00500804
set AT91C_TFT_GPR   0x0050085C
# ========== Register definition for HDMA_CH_0 peripheral ========== 
set AT91C_HDMA_CH_0_BDSCR 0xFFFFEC5C
set AT91C_HDMA_CH_0_DADDR 0xFFFFEC40
set AT91C_HDMA_CH_0_DPIP 0xFFFFEC58
set AT91C_HDMA_CH_0_DSCR 0xFFFFEC44
set AT91C_HDMA_CH_0_CFG 0xFFFFEC50
set AT91C_HDMA_CH_0_SPIP 0xFFFFEC54
set AT91C_HDMA_CH_0_CADDR 0xFFFFEC60
set AT91C_HDMA_CH_0_CTRLA 0xFFFFEC48
set AT91C_HDMA_CH_0_CTRLB 0xFFFFEC4C
set AT91C_HDMA_CH_0_SADDR 0xFFFFEC3C
# ========== Register definition for HDMA_CH_1 peripheral ========== 
set AT91C_HDMA_CH_1_CADDR 0xFFFFEC88
set AT91C_HDMA_CH_1_DPIP 0xFFFFEC80
set AT91C_HDMA_CH_1_CTRLB 0xFFFFEC74
set AT91C_HDMA_CH_1_SADDR 0xFFFFEC64
set AT91C_HDMA_CH_1_BDSCR 0xFFFFEC84
set AT91C_HDMA_CH_1_CFG 0xFFFFEC78
set AT91C_HDMA_CH_1_DSCR 0xFFFFEC6C
set AT91C_HDMA_CH_1_DADDR 0xFFFFEC68
set AT91C_HDMA_CH_1_CTRLA 0xFFFFEC70
set AT91C_HDMA_CH_1_SPIP 0xFFFFEC7C
# ========== Register definition for HDMA_CH_2 peripheral ========== 
set AT91C_HDMA_CH_2_SADDR 0xFFFFEC8C
set AT91C_HDMA_CH_2_BDSCR 0xFFFFECAC
set AT91C_HDMA_CH_2_DPIP 0xFFFFECA8
set AT91C_HDMA_CH_2_SPIP 0xFFFFECA4
set AT91C_HDMA_CH_2_DADDR 0xFFFFEC90
set AT91C_HDMA_CH_2_DSCR 0xFFFFEC94
set AT91C_HDMA_CH_2_CTRLA 0xFFFFEC98
set AT91C_HDMA_CH_2_CADDR 0xFFFFECB0
set AT91C_HDMA_CH_2_CFG 0xFFFFECA0
set AT91C_HDMA_CH_2_CTRLB 0xFFFFEC9C
# ========== Register definition for HDMA_CH_3 peripheral ========== 
set AT91C_HDMA_CH_3_SPIP 0xFFFFECCC
set AT91C_HDMA_CH_3_CTRLA 0xFFFFECC0
set AT91C_HDMA_CH_3_DPIP 0xFFFFECD0
set AT91C_HDMA_CH_3_CTRLB 0xFFFFECC4
set AT91C_HDMA_CH_3_BDSCR 0xFFFFECD4
set AT91C_HDMA_CH_3_DSCR 0xFFFFECBC
set AT91C_HDMA_CH_3_CADDR 0xFFFFECD8
set AT91C_HDMA_CH_3_CFG 0xFFFFECC8
set AT91C_HDMA_CH_3_DADDR 0xFFFFECB8
set AT91C_HDMA_CH_3_SADDR 0xFFFFECB4
# ========== Register definition for HDMA_CH_4 peripheral ========== 
set AT91C_HDMA_CH_4_CFG 0xFFFFECF0
set AT91C_HDMA_CH_4_BDSCR 0xFFFFECFC
set AT91C_HDMA_CH_4_CADDR 0xFFFFED00
set AT91C_HDMA_CH_4_DADDR 0xFFFFECE0
set AT91C_HDMA_CH_4_CTRLA 0xFFFFECE8
set AT91C_HDMA_CH_4_SADDR 0xFFFFECDC
set AT91C_HDMA_CH_4_CTRLB 0xFFFFECEC
set AT91C_HDMA_CH_4_DSCR 0xFFFFECE4
set AT91C_HDMA_CH_4_SPIP 0xFFFFECF4
set AT91C_HDMA_CH_4_DPIP 0xFFFFECF8
# ========== Register definition for HDMA_CH_5 peripheral ========== 
set AT91C_HDMA_CH_5_CTRLB 0xFFFFED14
set AT91C_HDMA_CH_5_DADDR 0xFFFFED08
set AT91C_HDMA_CH_5_SPIP 0xFFFFED1C
set AT91C_HDMA_CH_5_DSCR 0xFFFFED0C
set AT91C_HDMA_CH_5_DPIP 0xFFFFED20
set AT91C_HDMA_CH_5_CFG 0xFFFFED18
set AT91C_HDMA_CH_5_CADDR 0xFFFFED28
set AT91C_HDMA_CH_5_SADDR 0xFFFFED04
set AT91C_HDMA_CH_5_BDSCR 0xFFFFED24
set AT91C_HDMA_CH_5_CTRLA 0xFFFFED10
# ========== Register definition for HDMA_CH_6 peripheral ========== 
set AT91C_HDMA_CH_6_SADDR 0xFFFFED2C
set AT91C_HDMA_CH_6_BDSCR 0xFFFFED4C
set AT91C_HDMA_CH_6_CADDR 0xFFFFED50
set AT91C_HDMA_CH_6_SPIP 0xFFFFED44
set AT91C_HDMA_CH_6_CTRLB 0xFFFFED3C
set AT91C_HDMA_CH_6_DSCR 0xFFFFED34
set AT91C_HDMA_CH_6_CFG 0xFFFFED40
set AT91C_HDMA_CH_6_DPIP 0xFFFFED48
set AT91C_HDMA_CH_6_DADDR 0xFFFFED30
set AT91C_HDMA_CH_6_CTRLA 0xFFFFED38
# ========== Register definition for HDMA_CH_7 peripheral ========== 
set AT91C_HDMA_CH_7_CADDR 0xFFFFED78
set AT91C_HDMA_CH_7_CFG 0xFFFFED68
set AT91C_HDMA_CH_7_DADDR 0xFFFFED58
set AT91C_HDMA_CH_7_CTRLB 0xFFFFED64
set AT91C_HDMA_CH_7_DSCR 0xFFFFED5C
set AT91C_HDMA_CH_7_DPIP 0xFFFFED70
set AT91C_HDMA_CH_7_CTRLA 0xFFFFED60
set AT91C_HDMA_CH_7_BDSCR 0xFFFFED74
set AT91C_HDMA_CH_7_SPIP 0xFFFFED6C
set AT91C_HDMA_CH_7_SADDR 0xFFFFED54
# ========== Register definition for HDMA peripheral ========== 
set AT91C_HDMA_EBCIDR 0xFFFFEC1C
set AT91C_HDMA_LAST 0xFFFFEC10
set AT91C_HDMA_SREQ 0xFFFFEC08
set AT91C_HDMA_RSVD0 0xFFFFEC34
set AT91C_HDMA_EBCIER 0xFFFFEC18
set AT91C_HDMA_GCFG 0xFFFFEC00
set AT91C_HDMA_CHER 0xFFFFEC28
set AT91C_HDMA_RSVD1 0xFFFFEC38
set AT91C_HDMA_CHDR 0xFFFFEC2C
set AT91C_HDMA_EBCIMR 0xFFFFEC20
set AT91C_HDMA_CREQ 0xFFFFEC0C
set AT91C_HDMA_SYNC 0xFFFFEC14
set AT91C_HDMA_EN   0xFFFFEC04
set AT91C_HDMA_EBCISR 0xFFFFEC24
set AT91C_HDMA_CHSR 0xFFFFEC30
# ========== Register definition for HECC peripheral ========== 
set AT91C_HECC_VR   0xFFFFE2FC
set AT91C_HECC_SR   0xFFFFE208
set AT91C_HECC_CR   0xFFFFE200
set AT91C_HECC_NPR  0xFFFFE210
set AT91C_HECC_PR   0xFFFFE20C
set AT91C_HECC_MR   0xFFFFE204
# ========== Register definition for EMACB peripheral ========== 
set AT91C_EMACB_ALE 0xFFFBC054
set AT91C_EMACB_RRE 0xFFFBC06C
set AT91C_EMACB_SA4H 0xFFFBC0B4
set AT91C_EMACB_TPQ 0xFFFBC0BC
set AT91C_EMACB_RJA 0xFFFBC07C
set AT91C_EMACB_SA2H 0xFFFBC0A4
set AT91C_EMACB_TPF 0xFFFBC08C
set AT91C_EMACB_ROV 0xFFFBC070
set AT91C_EMACB_SA4L 0xFFFBC0B0
set AT91C_EMACB_MAN 0xFFFBC034
set AT91C_EMACB_TID 0xFFFBC0B8
set AT91C_EMACB_TBQP 0xFFFBC01C
set AT91C_EMACB_SA3L 0xFFFBC0A8
set AT91C_EMACB_DTF 0xFFFBC058
set AT91C_EMACB_PTR 0xFFFBC038
set AT91C_EMACB_CSE 0xFFFBC068
set AT91C_EMACB_ECOL 0xFFFBC060
set AT91C_EMACB_STE 0xFFFBC084
set AT91C_EMACB_MCF 0xFFFBC048
set AT91C_EMACB_IER 0xFFFBC028
set AT91C_EMACB_ELE 0xFFFBC078
set AT91C_EMACB_USRIO 0xFFFBC0C0
set AT91C_EMACB_PFR 0xFFFBC03C
set AT91C_EMACB_FCSE 0xFFFBC050
set AT91C_EMACB_SA1L 0xFFFBC098
set AT91C_EMACB_NCR 0xFFFBC000
set AT91C_EMACB_HRT 0xFFFBC094
set AT91C_EMACB_NCFGR 0xFFFBC004
set AT91C_EMACB_SCF 0xFFFBC044
set AT91C_EMACB_LCOL 0xFFFBC05C
set AT91C_EMACB_SA3H 0xFFFBC0AC
set AT91C_EMACB_HRB 0xFFFBC090
set AT91C_EMACB_ISR 0xFFFBC024
set AT91C_EMACB_IMR 0xFFFBC030
set AT91C_EMACB_WOL 0xFFFBC0C4
set AT91C_EMACB_USF 0xFFFBC080
set AT91C_EMACB_TSR 0xFFFBC014
set AT91C_EMACB_FRO 0xFFFBC04C
set AT91C_EMACB_IDR 0xFFFBC02C
set AT91C_EMACB_SA1H 0xFFFBC09C
set AT91C_EMACB_RLE 0xFFFBC088
set AT91C_EMACB_TUND 0xFFFBC064
set AT91C_EMACB_RSR 0xFFFBC020
set AT91C_EMACB_SA2L 0xFFFBC0A0
set AT91C_EMACB_FTO 0xFFFBC040
set AT91C_EMACB_RSE 0xFFFBC074
set AT91C_EMACB_NSR 0xFFFBC008
set AT91C_EMACB_RBQP 0xFFFBC018
set AT91C_EMACB_REV 0xFFFBC0FC
# ========== Register definition for ISI peripheral ========== 
set AT91C_ISI_DMACHDR 0xFFFB403C
set AT91C_ISI_IMR   0xFFFB4034
set AT91C_ISI_R2YSET1 0xFFFB401C
set AT91C_ISI_PDECF 0xFFFB400C
set AT91C_ISI_CFG2  0xFFFB4004
set AT91C_ISI_DMACCTRL 0xFFFB4054
set AT91C_ISI_CTRL  0xFFFB4024
set AT91C_ISI_Y2RSET0 0xFFFB4010
set AT91C_ISI_WPSR  0xFFFB40E8
set AT91C_ISI_DMACHER 0xFFFB4038
set AT91C_ISI_DMACHSR 0xFFFB4040
set AT91C_ISI_IDR   0xFFFB4030
set AT91C_ISI_VER   0xFFFB40FC
set AT91C_ISI_Y2RSET1 0xFFFB4014
set AT91C_ISI_R2YSET2 0xFFFB4020
set AT91C_ISI_SR    0xFFFB4028
set AT91C_ISI_DMACDSCR 0xFFFB4058
set AT91C_ISI_IER   0xFFFB402C
set AT91C_ISI_WPCR  0xFFFB40E4
set AT91C_ISI_DMACADDR 0xFFFB4050
set AT91C_ISI_CFG1  0xFFFB4000
set AT91C_ISI_R2YSET0 0xFFFB4018
set AT91C_ISI_PSIZE 0xFFFB4008
set AT91C_ISI_DMAPDSCR 0xFFFB404C
set AT91C_ISI_DMAPADDR 0xFFFB4044
set AT91C_ISI_DMAPCTRL 0xFFFB4048
# ========== Register definition for VDEC peripheral ========== 
set AT91C_VDEC_DCR  0x00900008
set AT91C_VDEC_IDR  0x00900000
set AT91C_VDEC_ISR  0x00900004
# ========== Register definition for UHPHS_OHCI peripheral ========== 
set AT91C_OHCI_HcRhPortStatus 0x00700054
set AT91C_OHCI_HcFmRemaining 0x00700038
set AT91C_OHCI_HcInterruptEnable 0x00700010
set AT91C_OHCI_HcControl 0x00700004
set AT91C_OHCI_HcPeriodicStart 0x00700040
set AT91C_OHCI_HcInterruptStatus 0x0070000C
set AT91C_OHCI_HcRhDescriptorB 0x0070004C
set AT91C_OHCI_HcInterruptDisable 0x00700014
set AT91C_OHCI_HcPeriodCurrentED 0x0070001C
set AT91C_OHCI_HcRhDescriptorA 0x00700048
set AT91C_OHCI_HcRhStatus 0x00700050
set AT91C_OHCI_HcBulkCurrentED 0x0070002C
set AT91C_OHCI_HcControlHeadED 0x00700020
set AT91C_OHCI_HcLSThreshold 0x00700044
set AT91C_OHCI_HcRevision 0x00700000
set AT91C_OHCI_HcBulkDoneHead 0x00700030
set AT91C_OHCI_HcFmNumber 0x0070003C
set AT91C_OHCI_HcFmInterval 0x00700034
set AT91C_OHCI_HcBulkHeadED 0x00700028
set AT91C_OHCI_HcHCCA 0x00700018
set AT91C_OHCI_HcCommandStatus 0x00700008
set AT91C_OHCI_HcControlCurrentED 0x00700024
# ========== Register definition for UHPHS_EHCI peripheral ========== 
set AT91C_EHCI_USBSTS 0x00800014
set AT91C_EHCI_INSNREG03 0x0080009C
set AT91C_EHCI_INSNREG00 0x00800090
set AT91C_EHCI_HCSPPORTROUTE 0x0080000C
set AT91C_EHCI_FRINDEX 0x0080001C
set AT91C_EHCI_CONFIGFLAG 0x00800050
set AT91C_EHCI_HCCPARAMS 0x00800008
set AT91C_EHCI_USBINTR 0x00800018
set AT91C_EHCI_PORTSC 0x00800054
set AT91C_EHCI_CTRLDSSEGMENT 0x00800020
set AT91C_EHCI_VERSION 0x00800000
set AT91C_EHCI_USBCMD 0x00800010
set AT91C_EHCI_INSNREG04 0x008000A0
set AT91C_EHCI_PERIODICLISTBASE 0x00800024
set AT91C_EHCI_INSNREG01 0x00800094
set AT91C_EHCI_HCSPARAMS 0x00800004
set AT91C_EHCI_INSNREG05 0x008000A4
set AT91C_EHCI_ASYNCLISTADDR 0x00800028
set AT91C_EHCI_INSNREG02 0x00800098
# ========== Register definition for AES peripheral ========== 
set AT91C_AES_IVxR  0xFFFC0060
set AT91C_AES_KEYWxR 0xFFFC0020
set AT91C_AES_CR    0xFFFC0000
set AT91C_AES_IER   0xFFFC0010
set AT91C_AES_IDATAxR 0xFFFC0040
set AT91C_AES_MR    0xFFFC0004
set AT91C_AES_IDR   0xFFFC0014
set AT91C_AES_IMR   0xFFFC0018
set AT91C_AES_ODATAxR 0xFFFC0050
set AT91C_AES_ISR   0xFFFC001C
set AT91C_AES_VR    0xFFFC00FC
# ========== Register definition for TDES peripheral ========== 
set AT91C_TDES_IDR  0xFFFC4014
set AT91C_TDES_ISR  0xFFFC401C
set AT91C_TDES_KEY2WxR 0xFFFC4028
set AT91C_TDES_KEY3WxR 0xFFFC4030
set AT91C_TDES_IMR  0xFFFC4018
set AT91C_TDES_KEY1WxR 0xFFFC4020
set AT91C_TDES_VR   0xFFFC40FC
set AT91C_TDES_IER  0xFFFC4010
set AT91C_TDES_IVxR 0xFFFC4060
set AT91C_TDES_IDATAxR 0xFFFC4040
set AT91C_TDES_CR   0xFFFC4000
set AT91C_TDES_MR   0xFFFC4004
set AT91C_TDES_ODATAxR 0xFFFC4050
# ========== Register definition for PDC_TDES peripheral ========== 
set AT91C_TDES_RNCR 0xFFFC4114
set AT91C_TDES_PTCR 0xFFFC4120
set AT91C_TDES_TCR  0xFFFC410C
set AT91C_TDES_PTSR 0xFFFC4124
set AT91C_TDES_TNPR 0xFFFC4118
set AT91C_TDES_RCR  0xFFFC4104
set AT91C_TDES_RNPR 0xFFFC4110
set AT91C_TDES_RPR  0xFFFC4100
set AT91C_TDES_TNCR 0xFFFC411C
set AT91C_TDES_TPR  0xFFFC4108
# ========== Register definition for SHA peripheral ========== 
set AT91C_SHA_IMR   0xFFFC8018
set AT91C_SHA_IER   0xFFFC8010
set AT91C_SHA_VR    0xFFFC80FC
set AT91C_SHA_CR    0xFFFC8000
set AT91C_SHA_MR    0xFFFC8004
set AT91C_SHA_IDR   0xFFFC8014
set AT91C_SHA_ISR   0xFFFC801C
set AT91C_SHA_IDATAxR 0xFFFC8040
set AT91C_SHA_ODATAxR 0xFFFC8080
# ========== Register definition for PDC_SHA peripheral ========== 
set AT91C_SHA_PTCR  0xFFFC8120
set AT91C_SHA_TCR   0xFFFC810C
set AT91C_SHA_RPR   0xFFFC8100
set AT91C_SHA_TPR   0xFFFC8108
set AT91C_SHA_PTSR  0xFFFC8124
set AT91C_SHA_RNCR  0xFFFC8114
set AT91C_SHA_TNPR  0xFFFC8118
set AT91C_SHA_RCR   0xFFFC8104
set AT91C_SHA_RNPR  0xFFFC8110
set AT91C_SHA_TNCR  0xFFFC811C
# ========== Register definition for TRNG peripheral ========== 
set AT91C_TRNG_IDR  0xFFFCC014
set AT91C_TRNG_IER  0xFFFCC010
set AT91C_TRNG_VERSION 0xFFFCC0FC
set AT91C_TRNG_ISR  0xFFFCC01C
set AT91C_TRNG_CR   0xFFFCC000
set AT91C_TRNG_ODATA 0xFFFCC050
set AT91C_TRNG_IMR  0xFFFCC018

# *****************************************************************************
#               BASE ADDRESS DEFINITIONS FOR AT91SAM9264
# *****************************************************************************
set AT91C_BASE_SFR       0xFFF74000
set AT91C_BASE_SYS       0xFFFFC000
set AT91C_BASE_EBI       0xFFFFE200
set AT91C_BASE_DDR2CP1   0xFFFFE400
set AT91C_BASE_DDR2C     0xFFFFE600
set AT91C_BASE_SMC       0xFFFFE800
set AT91C_BASE_MATRIX    0xFFFFEA00
set AT91C_BASE_CCFG      0xFFFFEB10
set AT91C_BASE_AIC       0xFFFFF000
set AT91C_BASE_PDC_DBGU  0xFFFFEF00
set AT91C_BASE_DBGU      0xFFFFEE00
set AT91C_BASE_PIOA      0xFFFFF200
set AT91C_BASE_PIOB      0xFFFFF400
set AT91C_BASE_PIOC      0xFFFFF600
set AT91C_BASE_PIOD      0xFFFFF800
set AT91C_BASE_PIOE      0xFFFFFA00
set AT91C_BASE_PMC       0xFFFFFC00
set AT91C_BASE_CKGR      0xFFFFFC1C
set AT91C_BASE_RSTC      0xFFFFFD00
set AT91C_BASE_SHDWC     0xFFFFFD10
set AT91C_BASE_RTTC      0xFFFFFD20
set AT91C_BASE_PITC      0xFFFFFD30
set AT91C_BASE_WDTC      0xFFFFFD40
set AT91C_BASE_RTC       0xFFFFFDB0
set AT91C_BASE_TC0       0xFFF7C000
set AT91C_BASE_TC1       0xFFF7C040
set AT91C_BASE_TC2       0xFFF7C080
set AT91C_BASE_TC3       0xFFFD4000
set AT91C_BASE_TC4       0xFFFD4040
set AT91C_BASE_TC5       0xFFFD4080
set AT91C_BASE_TCB0      0xFFF7C000
set AT91C_BASE_TCB1      0xFFFD4000
set AT91C_BASE_MCI0      0xFFF80000
set AT91C_BASE_MCI1      0xFFFD0000
set AT91C_BASE_TWI0      0xFFF84000
set AT91C_BASE_TWI1      0xFFF88000
set AT91C_BASE_PDC_US0   0xFFF8C100
set AT91C_BASE_US0       0xFFF8C000
set AT91C_BASE_PDC_US1   0xFFF90100
set AT91C_BASE_US1       0xFFF90000
set AT91C_BASE_PDC_US2   0xFFF94100
set AT91C_BASE_US2       0xFFF94000
set AT91C_BASE_PDC_US3   0xFFF98100
set AT91C_BASE_US3       0xFFF98000
set AT91C_BASE_PDC_SSC0  0xFFF9C100
set AT91C_BASE_SSC0      0xFFF9C000
set AT91C_BASE_PDC_SSC1  0xFFFA0100
set AT91C_BASE_SSC1      0xFFFA0000
set AT91C_BASE_PWMC_CH0  0xFFFB8200
set AT91C_BASE_PWMC_CH1  0xFFFB8220
set AT91C_BASE_PWMC_CH2  0xFFFB8240
set AT91C_BASE_PWMC_CH3  0xFFFB8260
set AT91C_BASE_PWMC      0xFFFB8000
set AT91C_BASE_PDC_SPI0  0xFFFA4100
set AT91C_BASE_PDC_SPI1  0xFFFA8100
set AT91C_BASE_SPI0      0xFFFA4000
set AT91C_BASE_SPI1      0xFFFA8000
set AT91C_BASE_PDC_TSADC 0xFFFB0100
set AT91C_BASE_TSADC     0xFFFB0000
set AT91C_BASE_UDPHS_EPTFIFO 0x00600000
set AT91C_BASE_UDPHS_EPT_0 0xFFF78100
set AT91C_BASE_UDPHS_EPT_1 0xFFF78120
set AT91C_BASE_UDPHS_EPT_2 0xFFF78140
set AT91C_BASE_UDPHS_EPT_3 0xFFF78160
set AT91C_BASE_UDPHS_EPT_4 0xFFF78180
set AT91C_BASE_UDPHS_EPT_5 0xFFF781A0
set AT91C_BASE_UDPHS_EPT_6 0xFFF781C0
set AT91C_BASE_UDPHS_DMA_1 0xFFF78310
set AT91C_BASE_UDPHS_DMA_2 0xFFF78320
set AT91C_BASE_UDPHS_DMA_3 0xFFF78330
set AT91C_BASE_UDPHS_DMA_4 0xFFF78340
set AT91C_BASE_UDPHS_DMA_5 0xFFF78350
set AT91C_BASE_UDPHS_DMA_6 0xFFF78360
set AT91C_BASE_UDPHS     0xFFF78000
set AT91C_BASE_PDC_AC97C 0xFFFAC100
set AT91C_BASE_AC97C     0xFFFAC000
set AT91C_BASE_LCDC      0x00500000
set AT91C_BASE_LCDC_16B_TFT 0x00500000
set AT91C_BASE_HDMA_CH_0 0xFFFFEC3C
set AT91C_BASE_HDMA_CH_1 0xFFFFEC64
set AT91C_BASE_HDMA_CH_2 0xFFFFEC8C
set AT91C_BASE_HDMA_CH_3 0xFFFFECB4
set AT91C_BASE_HDMA_CH_4 0xFFFFECDC
set AT91C_BASE_HDMA_CH_5 0xFFFFED04
set AT91C_BASE_HDMA_CH_6 0xFFFFED2C
set AT91C_BASE_HDMA_CH_7 0xFFFFED54
set AT91C_BASE_HDMA      0xFFFFEC00
set AT91C_BASE_HECC      0xFFFFE200
set AT91C_BASE_EMACB     0xFFFBC000
set AT91C_BASE_ISI       0xFFFB4000
set AT91C_BASE_VDEC      0x00900000
set AT91C_BASE_UHPHS_OHCI 0x00700000
set AT91C_BASE_UHPHS_EHCI 0x00800000
set AT91C_BASE_AES       0xFFFC0000
set AT91C_BASE_TDES      0xFFFC4000
set AT91C_BASE_PDC_TDES  0xFFFC4100
set AT91C_BASE_SHA       0xFFFC8000
set AT91C_BASE_PDC_SHA   0xFFFC8100
set AT91C_BASE_TRNG      0xFFFCC000

# *****************************************************************************
#               PERIPHERAL ID DEFINITIONS FOR AT91SAM9264
# *****************************************************************************
set AT91C_ID_FIQ     0
set AT91C_ID_SYS     1
set AT91C_ID_PIOA    2
set AT91C_ID_PIOB    3
set AT91C_ID_PIOC    4
set AT91C_ID_PIOD_E  5
set AT91C_ID_TRNG    6
set AT91C_ID_US0     7
set AT91C_ID_US1     8
set AT91C_ID_US2     9
set AT91C_ID_US3    10
set AT91C_ID_MCI0   11
set AT91C_ID_TWI0   12
set AT91C_ID_TWI1   13
set AT91C_ID_SPI0   14
set AT91C_ID_SPI1   15
set AT91C_ID_SSC0   16
set AT91C_ID_SSC1   17
set AT91C_ID_TC     18
set AT91C_ID_PWMC   19
set AT91C_ID_TSADC  20
set AT91C_ID_HDMA   21
set AT91C_ID_UHPHS  22
set AT91C_ID_LCDC   23
set AT91C_ID_AC97C  24
set AT91C_ID_EMAC   25
set AT91C_ID_ISI    26
set AT91C_ID_UDPHS  27
set AT91C_ID_TDES   28
set AT91C_ID_MCI1   29
set AT91C_ID_VDEC   30
set AT91C_ID_IRQ0   31

# *****************************************************************************
#               PIO DEFINITIONS FOR AT91SAM9264
# *****************************************************************************
set AT91C_PIO_PA0        [expr 1 <<  0 ]
set AT91C_PA0_MCI0_CK  $AT91C_PIO_PA0
set AT91C_PA0_TCLK3    $AT91C_PIO_PA0
set AT91C_PIO_PA1        [expr 1 <<  1 ]
set AT91C_PA1_MCI0_CDA $AT91C_PIO_PA1
set AT91C_PA1_TIOA3    $AT91C_PIO_PA1
set AT91C_PIO_PA10       [expr 1 << 10 ]
set AT91C_PA10_ETX0     $AT91C_PIO_PA10
set AT91C_PIO_PA11       [expr 1 << 11 ]
set AT91C_PA11_ETX1     $AT91C_PIO_PA11
set AT91C_PIO_PA12       [expr 1 << 12 ]
set AT91C_PA12_ERX0     $AT91C_PIO_PA12
set AT91C_PIO_PA13       [expr 1 << 13 ]
set AT91C_PA13_ERX1     $AT91C_PIO_PA13
set AT91C_PIO_PA14       [expr 1 << 14 ]
set AT91C_PA14_ETXEN    $AT91C_PIO_PA14
set AT91C_PIO_PA15       [expr 1 << 15 ]
set AT91C_PA15_ERXDV    $AT91C_PIO_PA15
set AT91C_PIO_PA16       [expr 1 << 16 ]
set AT91C_PA16_ERXER    $AT91C_PIO_PA16
set AT91C_PIO_PA17       [expr 1 << 17 ]
set AT91C_PA17_ETXCK_EREFCK $AT91C_PIO_PA17
set AT91C_PIO_PA18       [expr 1 << 18 ]
set AT91C_PA18_EMDC     $AT91C_PIO_PA18
set AT91C_PIO_PA19       [expr 1 << 19 ]
set AT91C_PA19_EMDIO    $AT91C_PIO_PA19
set AT91C_PIO_PA2        [expr 1 <<  2 ]
set AT91C_PA2_MCI0_DA0 $AT91C_PIO_PA2
set AT91C_PA2_TIOB3    $AT91C_PIO_PA2
set AT91C_PIO_PA20       [expr 1 << 20 ]
set AT91C_PA20_TWD0     $AT91C_PIO_PA20
set AT91C_PIO_PA21       [expr 1 << 21 ]
set AT91C_PA21_TWCK0    $AT91C_PIO_PA21
set AT91C_PIO_PA22       [expr 1 << 22 ]
set AT91C_PA22_MCI1_CDA $AT91C_PIO_PA22
set AT91C_PA22_SCK3     $AT91C_PIO_PA22
set AT91C_PIO_PA23       [expr 1 << 23 ]
set AT91C_PA23_MCI1_DA0 $AT91C_PIO_PA23
set AT91C_PA23_RTS3     $AT91C_PIO_PA23
set AT91C_PIO_PA24       [expr 1 << 24 ]
set AT91C_PA24_MCI1_DA1 $AT91C_PIO_PA24
set AT91C_PA24_CTS3     $AT91C_PIO_PA24
set AT91C_PIO_PA25       [expr 1 << 25 ]
set AT91C_PA25_MCI1_DA2 $AT91C_PIO_PA25
set AT91C_PA25_PWM3     $AT91C_PIO_PA25
set AT91C_PIO_PA26       [expr 1 << 26 ]
set AT91C_PA26_MCI1_DA3 $AT91C_PIO_PA26
set AT91C_PA26_TIOB2    $AT91C_PIO_PA26
set AT91C_PIO_PA27       [expr 1 << 27 ]
set AT91C_PA27_MCI1_DA4 $AT91C_PIO_PA27
set AT91C_PA27_ETXER    $AT91C_PIO_PA27
set AT91C_PIO_PA28       [expr 1 << 28 ]
set AT91C_PA28_MCI1_DA5 $AT91C_PIO_PA28
set AT91C_PA28_ERXCK    $AT91C_PIO_PA28
set AT91C_PIO_PA29       [expr 1 << 29 ]
set AT91C_PA29_MCI1_DA6 $AT91C_PIO_PA29
set AT91C_PA29_ECRS     $AT91C_PIO_PA29
set AT91C_PIO_PA3        [expr 1 <<  3 ]
set AT91C_PA3_MCI0_DA1 $AT91C_PIO_PA3
set AT91C_PA3_TCLK4    $AT91C_PIO_PA3
set AT91C_PIO_PA30       [expr 1 << 30 ]
set AT91C_PA30_MCI1_DA7 $AT91C_PIO_PA30
set AT91C_PA30_ECOL     $AT91C_PIO_PA30
set AT91C_PIO_PA31       [expr 1 << 31 ]
set AT91C_PA31_MCI1_CK  $AT91C_PIO_PA31
set AT91C_PA31_PCK0     $AT91C_PIO_PA31
set AT91C_PIO_PA4        [expr 1 <<  4 ]
set AT91C_PA4_MCI0_DA2 $AT91C_PIO_PA4
set AT91C_PA4_TIOA4    $AT91C_PIO_PA4
set AT91C_PIO_PA5        [expr 1 <<  5 ]
set AT91C_PA5_MCI0_DA3 $AT91C_PIO_PA5
set AT91C_PA5_TIOB4    $AT91C_PIO_PA5
set AT91C_PIO_PA6        [expr 1 <<  6 ]
set AT91C_PA6_MCI0_DA4 $AT91C_PIO_PA6
set AT91C_PA6_ETX2     $AT91C_PIO_PA6
set AT91C_PIO_PA7        [expr 1 <<  7 ]
set AT91C_PA7_MCI0_DA5 $AT91C_PIO_PA7
set AT91C_PA7_ETX3     $AT91C_PIO_PA7
set AT91C_PIO_PA8        [expr 1 <<  8 ]
set AT91C_PA8_MCI0_DA6 $AT91C_PIO_PA8
set AT91C_PA8_ERX2     $AT91C_PIO_PA8
set AT91C_PIO_PA9        [expr 1 <<  9 ]
set AT91C_PA9_MCI0_DA7 $AT91C_PIO_PA9
set AT91C_PA9_ERX3     $AT91C_PIO_PA9
set AT91C_PIO_PB0        [expr 1 <<  0 ]
set AT91C_PB0_SPI0_MISO $AT91C_PIO_PB0
set AT91C_PIO_PB1        [expr 1 <<  1 ]
set AT91C_PB1_SPI0_MOSI $AT91C_PIO_PB1
set AT91C_PIO_PB10       [expr 1 << 10 ]
set AT91C_PB10_TWD1     $AT91C_PIO_PB10
set AT91C_PB10_ISI_D10  $AT91C_PIO_PB10
set AT91C_PIO_PB11       [expr 1 << 11 ]
set AT91C_PB11_TWCK1    $AT91C_PIO_PB11
set AT91C_PB11_ISI_D11  $AT91C_PIO_PB11
set AT91C_PIO_PB12       [expr 1 << 12 ]
set AT91C_PB12_DRXD     $AT91C_PIO_PB12
set AT91C_PIO_PB13       [expr 1 << 13 ]
set AT91C_PB13_DTXD     $AT91C_PIO_PB13
set AT91C_PIO_PB14       [expr 1 << 14 ]
set AT91C_PB14_SPI1_MISO $AT91C_PIO_PB14
set AT91C_PIO_PB15       [expr 1 << 15 ]
set AT91C_PB15_SPI1_MOSI $AT91C_PIO_PB15
set AT91C_PB15_CTS0     $AT91C_PIO_PB15
set AT91C_PIO_PB16       [expr 1 << 16 ]
set AT91C_PB16_SPI1_SPCK $AT91C_PIO_PB16
set AT91C_PB16_SCK0     $AT91C_PIO_PB16
set AT91C_PIO_PB17       [expr 1 << 17 ]
set AT91C_PB17_SPI1_NPCS0 $AT91C_PIO_PB17
set AT91C_PB17_RTS0     $AT91C_PIO_PB17
set AT91C_PIO_PB18       [expr 1 << 18 ]
set AT91C_PB18_RXD0     $AT91C_PIO_PB18
set AT91C_PB18_SPI0_NPCS1 $AT91C_PIO_PB18
set AT91C_PIO_PB19       [expr 1 << 19 ]
set AT91C_PB19_TXD0     $AT91C_PIO_PB19
set AT91C_PB19_SPI0_NPCS2 $AT91C_PIO_PB19
set AT91C_PIO_PB2        [expr 1 <<  2 ]
set AT91C_PB2_SPI0_SPCK $AT91C_PIO_PB2
set AT91C_PIO_PB20       [expr 1 << 20 ]
set AT91C_PB20_ISI_D0   $AT91C_PIO_PB20
set AT91C_PIO_PB21       [expr 1 << 21 ]
set AT91C_PB21_ISI_D1   $AT91C_PIO_PB21
set AT91C_PIO_PB22       [expr 1 << 22 ]
set AT91C_PB22_ISI_D2   $AT91C_PIO_PB22
set AT91C_PIO_PB23       [expr 1 << 23 ]
set AT91C_PB23_ISI_D3   $AT91C_PIO_PB23
set AT91C_PIO_PB24       [expr 1 << 24 ]
set AT91C_PB24_ISI_D4   $AT91C_PIO_PB24
set AT91C_PIO_PB25       [expr 1 << 25 ]
set AT91C_PB25_ISI_D5   $AT91C_PIO_PB25
set AT91C_PIO_PB26       [expr 1 << 26 ]
set AT91C_PB26_ISI_D6   $AT91C_PIO_PB26
set AT91C_PIO_PB27       [expr 1 << 27 ]
set AT91C_PB27_ISI_D7   $AT91C_PIO_PB27
set AT91C_PIO_PB28       [expr 1 << 28 ]
set AT91C_PB28_ISI_PCK  $AT91C_PIO_PB28
set AT91C_PIO_PB29       [expr 1 << 29 ]
set AT91C_PB29_ISI_VSYNC $AT91C_PIO_PB29
set AT91C_PIO_PB3        [expr 1 <<  3 ]
set AT91C_PB3_SPI0_NPCS0 $AT91C_PIO_PB3
set AT91C_PIO_PB30       [expr 1 << 30 ]
set AT91C_PB30_ISI_HSYNC $AT91C_PIO_PB30
set AT91C_PIO_PB31       [expr 1 << 31 ]
set AT91C_PB31_         $AT91C_PIO_PB31
set AT91C_PB31_PCK1     $AT91C_PIO_PB31
set AT91C_PIO_PB4        [expr 1 <<  4 ]
set AT91C_PB4_TXD1     $AT91C_PIO_PB4
set AT91C_PIO_PB5        [expr 1 <<  5 ]
set AT91C_PB5_RXD1     $AT91C_PIO_PB5
set AT91C_PIO_PB6        [expr 1 <<  6 ]
set AT91C_PB6_TXD2     $AT91C_PIO_PB6
set AT91C_PIO_PB7        [expr 1 <<  7 ]
set AT91C_PB7_RXD2     $AT91C_PIO_PB7
set AT91C_PIO_PB8        [expr 1 <<  8 ]
set AT91C_PB8_TXD3     $AT91C_PIO_PB8
set AT91C_PB8_ISI_D8   $AT91C_PIO_PB8
set AT91C_PIO_PB9        [expr 1 <<  9 ]
set AT91C_PB9_RXD3     $AT91C_PIO_PB9
set AT91C_PB9_ISI_D9   $AT91C_PIO_PB9
set AT91C_PIO_PC0        [expr 1 <<  0 ]
set AT91C_PC0_DQM2     $AT91C_PIO_PC0
set AT91C_PIO_PC1        [expr 1 <<  1 ]
set AT91C_PC1_DQM3     $AT91C_PIO_PC1
set AT91C_PIO_PC10       [expr 1 << 10 ]
set AT91C_PC10_NCS4_CFCS0 $AT91C_PIO_PC10
set AT91C_PC10_TCLK2    $AT91C_PIO_PC10
set AT91C_PIO_PC11       [expr 1 << 11 ]
set AT91C_PC11_NCS5_CFCS1 $AT91C_PIO_PC11
set AT91C_PC11_CTS2     $AT91C_PIO_PC11
set AT91C_PIO_PC12       [expr 1 << 12 ]
set AT91C_PC12_A25_CFRNW $AT91C_PIO_PC12
set AT91C_PIO_PC13       [expr 1 << 13 ]
set AT91C_PC13_NCS2     $AT91C_PIO_PC13
set AT91C_PIO_PC14       [expr 1 << 14 ]
set AT91C_PC14_NCS3_NANDCS $AT91C_PIO_PC14
set AT91C_PIO_PC15       [expr 1 << 15 ]
set AT91C_PC15_NWAIT    $AT91C_PIO_PC15
set AT91C_PIO_PC16       [expr 1 << 16 ]
set AT91C_PC16_D16      $AT91C_PIO_PC16
set AT91C_PIO_PC17       [expr 1 << 17 ]
set AT91C_PC17_D17      $AT91C_PIO_PC17
set AT91C_PIO_PC18       [expr 1 << 18 ]
set AT91C_PC18_D18      $AT91C_PIO_PC18
set AT91C_PIO_PC19       [expr 1 << 19 ]
set AT91C_PC19_D19      $AT91C_PIO_PC19
set AT91C_PIO_PC2        [expr 1 <<  2 ]
set AT91C_PC2_A19      $AT91C_PIO_PC2
set AT91C_PIO_PC20       [expr 1 << 20 ]
set AT91C_PC20_D20      $AT91C_PIO_PC20
set AT91C_PIO_PC21       [expr 1 << 21 ]
set AT91C_PC21_D21      $AT91C_PIO_PC21
set AT91C_PIO_PC22       [expr 1 << 22 ]
set AT91C_PC22_D22      $AT91C_PIO_PC22
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
set AT91C_PC3_A20      $AT91C_PIO_PC3
set AT91C_PIO_PC30       [expr 1 << 30 ]
set AT91C_PC30_D30      $AT91C_PIO_PC30
set AT91C_PIO_PC31       [expr 1 << 31 ]
set AT91C_PC31_D31      $AT91C_PIO_PC31
set AT91C_PIO_PC4        [expr 1 <<  4 ]
set AT91C_PC4_A21_NANDALE $AT91C_PIO_PC4
set AT91C_PIO_PC5        [expr 1 <<  5 ]
set AT91C_PC5_A22_NANDCLE $AT91C_PIO_PC5
set AT91C_PIO_PC6        [expr 1 <<  6 ]
set AT91C_PC6_A23      $AT91C_PIO_PC6
set AT91C_PIO_PC7        [expr 1 <<  7 ]
set AT91C_PC7_A24      $AT91C_PIO_PC7
set AT91C_PIO_PC8        [expr 1 <<  8 ]
set AT91C_PC8_CFCE1    $AT91C_PIO_PC8
set AT91C_PIO_PC9        [expr 1 <<  9 ]
set AT91C_PC9_CFCE2    $AT91C_PIO_PC9
set AT91C_PC9_RTS2     $AT91C_PIO_PC9
set AT91C_PIO_PD0        [expr 1 <<  0 ]
set AT91C_PD0_TK0      $AT91C_PIO_PD0
set AT91C_PD0_PWM3     $AT91C_PIO_PD0
set AT91C_PIO_PD1        [expr 1 <<  1 ]
set AT91C_PD1_TF0      $AT91C_PIO_PD1
set AT91C_PIO_PD10       [expr 1 << 10 ]
set AT91C_PD10_TD1      $AT91C_PIO_PD10
set AT91C_PIO_PD11       [expr 1 << 11 ]
set AT91C_PD11_RD1      $AT91C_PIO_PD11
set AT91C_PIO_PD12       [expr 1 << 12 ]
set AT91C_PD12_TK1      $AT91C_PIO_PD12
set AT91C_PD12_PCK0     $AT91C_PIO_PD12
set AT91C_PIO_PD13       [expr 1 << 13 ]
set AT91C_PD13_RK1      $AT91C_PIO_PD13
set AT91C_PIO_PD14       [expr 1 << 14 ]
set AT91C_PD14_TF1      $AT91C_PIO_PD14
set AT91C_PIO_PD15       [expr 1 << 15 ]
set AT91C_PD15_RF1      $AT91C_PIO_PD15
set AT91C_PIO_PD16       [expr 1 << 16 ]
set AT91C_PD16_RTS1     $AT91C_PIO_PD16
set AT91C_PIO_PD17       [expr 1 << 17 ]
set AT91C_PD17_CTS1     $AT91C_PIO_PD17
set AT91C_PIO_PD18       [expr 1 << 18 ]
set AT91C_PD18_SPI1_NPCS2 $AT91C_PIO_PD18
set AT91C_PD18_IRQ      $AT91C_PIO_PD18
set AT91C_PIO_PD19       [expr 1 << 19 ]
set AT91C_PD19_SPI1_NPCS3 $AT91C_PIO_PD19
set AT91C_PD19_FIQ      $AT91C_PIO_PD19
set AT91C_PIO_PD2        [expr 1 <<  2 ]
set AT91C_PD2_TD0      $AT91C_PIO_PD2
set AT91C_PIO_PD20       [expr 1 << 20 ]
set AT91C_PD20_TIOA0    $AT91C_PIO_PD20
set AT91C_PIO_PD21       [expr 1 << 21 ]
set AT91C_PD21_TIOA1    $AT91C_PIO_PD21
set AT91C_PIO_PD22       [expr 1 << 22 ]
set AT91C_PD22_TIOA2    $AT91C_PIO_PD22
set AT91C_PIO_PD23       [expr 1 << 23 ]
set AT91C_PD23_TCLK0    $AT91C_PIO_PD23
set AT91C_PIO_PD24       [expr 1 << 24 ]
set AT91C_PD24_SPI0_NPCS1 $AT91C_PIO_PD24
set AT91C_PD24_PWM0     $AT91C_PIO_PD24
set AT91C_PIO_PD25       [expr 1 << 25 ]
set AT91C_PD25_SPI0_NPCS2 $AT91C_PIO_PD25
set AT91C_PD25_PWM1     $AT91C_PIO_PD25
set AT91C_PIO_PD26       [expr 1 << 26 ]
set AT91C_PD26_PCK0     $AT91C_PIO_PD26
set AT91C_PD26_PWM2     $AT91C_PIO_PD26
set AT91C_PIO_PD27       [expr 1 << 27 ]
set AT91C_PD27_PCK1     $AT91C_PIO_PD27
set AT91C_PD27_SPI0_NPCS3 $AT91C_PIO_PD27
set AT91C_PIO_PD28       [expr 1 << 28 ]
set AT91C_PD28_TSADTRG  $AT91C_PIO_PD28
set AT91C_PD28_SPI1_NPCS1 $AT91C_PIO_PD28
set AT91C_PIO_PD29       [expr 1 << 29 ]
set AT91C_PD29_TCLK1    $AT91C_PIO_PD29
set AT91C_PD29_SCK1     $AT91C_PIO_PD29
set AT91C_PIO_PD3        [expr 1 <<  3 ]
set AT91C_PD3_RD0      $AT91C_PIO_PD3
set AT91C_PIO_PD30       [expr 1 << 30 ]
set AT91C_PD30_TIOB0    $AT91C_PIO_PD30
set AT91C_PD30_SCK2     $AT91C_PIO_PD30
set AT91C_PIO_PD31       [expr 1 << 31 ]
set AT91C_PD31_TIOB1    $AT91C_PIO_PD31
set AT91C_PD31_PWM1     $AT91C_PIO_PD31
set AT91C_PIO_PD4        [expr 1 <<  4 ]
set AT91C_PD4_RK0      $AT91C_PIO_PD4
set AT91C_PIO_PD5        [expr 1 <<  5 ]
set AT91C_PD5_RF0      $AT91C_PIO_PD5
set AT91C_PIO_PD6        [expr 1 <<  6 ]
set AT91C_PD6_AC97RX   $AT91C_PIO_PD6
set AT91C_PIO_PD7        [expr 1 <<  7 ]
set AT91C_PD7_AC97TX   $AT91C_PIO_PD7
set AT91C_PD7_TIOA5    $AT91C_PIO_PD7
set AT91C_PIO_PD8        [expr 1 <<  8 ]
set AT91C_PD8_AC97FS   $AT91C_PIO_PD8
set AT91C_PD8_TIOB5    $AT91C_PIO_PD8
set AT91C_PIO_PD9        [expr 1 <<  9 ]
set AT91C_PD9_AC97CK   $AT91C_PIO_PD9
set AT91C_PD9_TCLK5    $AT91C_PIO_PD9
set AT91C_PIO_PE0        [expr 1 <<  0 ]
set AT91C_PE0_LCDPWR   $AT91C_PIO_PE0
set AT91C_PE0_PCK0     $AT91C_PIO_PE0
set AT91C_PIO_PE1        [expr 1 <<  1 ]
set AT91C_PE1_LCDMOD   $AT91C_PIO_PE1
set AT91C_PIO_PE10       [expr 1 << 10 ]
set AT91C_PE10_LCDD3    $AT91C_PIO_PE10
set AT91C_PE10_LCDD5    $AT91C_PIO_PE10
set AT91C_PIO_PE11       [expr 1 << 11 ]
set AT91C_PE11_LCDD4    $AT91C_PIO_PE11
set AT91C_PE11_LCDD6    $AT91C_PIO_PE11
set AT91C_PIO_PE12       [expr 1 << 12 ]
set AT91C_PE12_LCDD5    $AT91C_PIO_PE12
set AT91C_PE12_LCDD7    $AT91C_PIO_PE12
set AT91C_PIO_PE13       [expr 1 << 13 ]
set AT91C_PE13_LCDD6    $AT91C_PIO_PE13
set AT91C_PE13_LCDD10   $AT91C_PIO_PE13
set AT91C_PIO_PE14       [expr 1 << 14 ]
set AT91C_PE14_LCDD7    $AT91C_PIO_PE14
set AT91C_PE14_LCDD11   $AT91C_PIO_PE14
set AT91C_PIO_PE15       [expr 1 << 15 ]
set AT91C_PE15_LCDD8    $AT91C_PIO_PE15
set AT91C_PE15_LCDD12   $AT91C_PIO_PE15
set AT91C_PIO_PE16       [expr 1 << 16 ]
set AT91C_PE16_LCDD9    $AT91C_PIO_PE16
set AT91C_PE16_LCDD13   $AT91C_PIO_PE16
set AT91C_PIO_PE17       [expr 1 << 17 ]
set AT91C_PE17_LCDD10   $AT91C_PIO_PE17
set AT91C_PE17_LCDD14   $AT91C_PIO_PE17
set AT91C_PIO_PE18       [expr 1 << 18 ]
set AT91C_PE18_LCDD11   $AT91C_PIO_PE18
set AT91C_PE18_LCDD15   $AT91C_PIO_PE18
set AT91C_PIO_PE19       [expr 1 << 19 ]
set AT91C_PE19_LCDD12   $AT91C_PIO_PE19
set AT91C_PE19_LCDD18   $AT91C_PIO_PE19
set AT91C_PIO_PE2        [expr 1 <<  2 ]
set AT91C_PE2_LCDCC    $AT91C_PIO_PE2
set AT91C_PIO_PE20       [expr 1 << 20 ]
set AT91C_PE20_LCDD13   $AT91C_PIO_PE20
set AT91C_PE20_LCDD19   $AT91C_PIO_PE20
set AT91C_PIO_PE21       [expr 1 << 21 ]
set AT91C_PE21_LCDD14   $AT91C_PIO_PE21
set AT91C_PE21_LCDD20   $AT91C_PIO_PE21
set AT91C_PIO_PE22       [expr 1 << 22 ]
set AT91C_PE22_LCDD15   $AT91C_PIO_PE22
set AT91C_PE22_LCDD21   $AT91C_PIO_PE22
set AT91C_PIO_PE23       [expr 1 << 23 ]
set AT91C_PE23_LCDD16   $AT91C_PIO_PE23
set AT91C_PE23_LCDD22   $AT91C_PIO_PE23
set AT91C_PIO_PE24       [expr 1 << 24 ]
set AT91C_PE24_LCDD17   $AT91C_PIO_PE24
set AT91C_PE24_LCDD23   $AT91C_PIO_PE24
set AT91C_PIO_PE25       [expr 1 << 25 ]
set AT91C_PE25_LCDD18   $AT91C_PIO_PE25
set AT91C_PIO_PE26       [expr 1 << 26 ]
set AT91C_PE26_LCDD19   $AT91C_PIO_PE26
set AT91C_PIO_PE27       [expr 1 << 27 ]
set AT91C_PE27_LCDD20   $AT91C_PIO_PE27
set AT91C_PIO_PE28       [expr 1 << 28 ]
set AT91C_PE28_LCDD21   $AT91C_PIO_PE28
set AT91C_PIO_PE29       [expr 1 << 29 ]
set AT91C_PE29_LCDD22   $AT91C_PIO_PE29
set AT91C_PIO_PE3        [expr 1 <<  3 ]
set AT91C_PE3_LCDVSYNC $AT91C_PIO_PE3
set AT91C_PIO_PE30       [expr 1 << 30 ]
set AT91C_PE30_LCDD23   $AT91C_PIO_PE30
set AT91C_PIO_PE31       [expr 1 << 31 ]
set AT91C_PE31_PWM2     $AT91C_PIO_PE31
set AT91C_PE31_PCK1     $AT91C_PIO_PE31
set AT91C_PIO_PE4        [expr 1 <<  4 ]
set AT91C_PE4_LCDHSYNC $AT91C_PIO_PE4
set AT91C_PIO_PE5        [expr 1 <<  5 ]
set AT91C_PE5_LCDDOTCK $AT91C_PIO_PE5
set AT91C_PIO_PE6        [expr 1 <<  6 ]
set AT91C_PE6_LCDDEN   $AT91C_PIO_PE6
set AT91C_PIO_PE7        [expr 1 <<  7 ]
set AT91C_PE7_LCDD0    $AT91C_PIO_PE7
set AT91C_PE7_LCDD2    $AT91C_PIO_PE7
set AT91C_PIO_PE8        [expr 1 <<  8 ]
set AT91C_PE8_LCDD1    $AT91C_PIO_PE8
set AT91C_PE8_LCDD3    $AT91C_PIO_PE8
set AT91C_PIO_PE9        [expr 1 <<  9 ]
set AT91C_PE9_LCDD2    $AT91C_PIO_PE9
set AT91C_PE9_LCDD4    $AT91C_PIO_PE9

# *****************************************************************************
#               MEMORY MAPPING DEFINITIONS FOR AT91SAM9264
# *****************************************************************************
set AT91C_ITCM 	 0x00100000
set AT91C_ITCM_SIZE	 0x00008000
set AT91C_DTCM 	 0x00200000
set AT91C_DTCM_SIZE	 0x00010000
set AT91C_IRAM 	 0x00300000
set AT91C_IRAM_SIZE	 0x00010000
set AT91C_IRAM_MIN	 0x00300000
set AT91C_IRAM_MIN_SIZE	 0x00004000
set AT91C_IROM 	 0x00400000
set AT91C_IROM_SIZE	 0x00010000
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
set AT91C_DDR2 	 0x70000000
set AT91C_DDR2_SIZE	 0x10000000


# *****************************************************************************
#               ATTRIBUTES DEFINITIONS FOR AT91SAM9264
# *****************************************************************************
array set AT91SAM9264_att {
	HDMA_CH 	{ LP 	HDMA_CH_0_att 	HDMA_CH_1_att 	HDMA_CH_2_att 	HDMA_CH_3_att 	HDMA_CH_4_att 	HDMA_CH_5_att 	HDMA_CH_6_att 	HDMA_CH_7_att }
	LCDC 	{ LP 	LCDC_att 	LCDC_16B_TFT_att }
	SMC 	{ LP 	SMC_att }
	RSTC 	{ LP 	RSTC_att }
	SSC 	{ LP 	SSC0_att 	SSC1_att }
	WDTC 	{ LP 	WDTC_att }
	HDDRSDRC2 	{ LP 	DDR2CP1_att 	DDR2C_att }
	TRNG 	{ LP 	TRNG_att }
	VDEC 	{ LP 	VDEC_att }
	CKGR 	{ LP 	CKGR_att }
	AES 	{ LP 	AES_att }
	TWI 	{ LP 	TWI0_att 	TWI1_att }
	SHA 	{ LP 	SHA_att }
	TSADC 	{ LP 	TSADC_att }
	HDMA 	{ LP 	HDMA_att }
	RTTC 	{ LP 	RTTC_att }
	TDES 	{ LP 	TDES_att }
	RTC 	{ LP 	RTC_att }
	TC 	{ LP 	TC0_att 	TC1_att 	TC2_att 	TC3_att 	TC4_att 	TC5_att }
	SYS 	{ LP 	SYS_att }
	UHPHS_OHCI 	{ LP 	UHPHS_OHCI_att }
	UDPHS_DMA 	{ LP 	UDPHS_DMA_1_att 	UDPHS_DMA_2_att 	UDPHS_DMA_3_att 	UDPHS_DMA_4_att 	UDPHS_DMA_5_att 	UDPHS_DMA_6_att }
	UHPHS_EHCI 	{ LP 	UHPHS_EHCI_att }
	PIO 	{ LP 	PIOA_att 	PIOB_att 	PIOC_att 	PIOD_att 	PIOE_att }
	PWMC 	{ LP 	PWMC_att }
	SFR 	{ LP 	SFR_att }
	PDC 	{ LP 	PDC_DBGU_att 	PDC_US0_att 	PDC_US1_att 	PDC_US2_att 	PDC_US3_att 	PDC_SSC0_att 	PDC_SSC1_att 	PDC_SPI0_att 	PDC_SPI1_att 	PDC_TSADC_att 	PDC_AC97C_att 	PDC_TDES_att 	PDC_SHA_att }
	DBGU 	{ LP 	DBGU_att }
	MATRIX 	{ LP 	MATRIX_att }
	PMC 	{ LP 	PMC_att }
	MCI 	{ LP 	MCI0_att 	MCI1_att }
	CCFG 	{ LP 	CCFG_att }
	ISI 	{ LP 	ISI_att }
	EBI 	{ LP 	EBI_att }
	SHDWC 	{ LP 	SHDWC_att }
	PITC 	{ LP 	PITC_att }
	USART 	{ LP 	US0_att 	US1_att 	US2_att 	US3_att }
	SPI 	{ LP 	SPI0_att 	SPI1_att }
	TCB 	{ LP 	TCB0_att 	TCB1_att }
	AIC 	{ LP 	AIC_att }
	UDPHS_EPT 	{ LP 	UDPHS_EPT_0_att 	UDPHS_EPT_1_att 	UDPHS_EPT_2_att 	UDPHS_EPT_3_att 	UDPHS_EPT_4_att 	UDPHS_EPT_5_att 	UDPHS_EPT_6_att }
	AC97C 	{ LP 	AC97C_att }
	PWMC_CH 	{ LP 	PWMC_CH0_att 	PWMC_CH1_att 	PWMC_CH2_att 	PWMC_CH3_att }
	UDPHS_EPTFIFO 	{ LP 	UDPHS_EPTFIFO_att }
	EMAC 	{ LP 	EMACB_att }
	ECC 	{ LP 	HECC_att }
	UDPHS 	{ LP 	UDPHS_att }

}
# ========== Peripheral attributes for HDMA_CH peripheral ========== 
array set HDMA_CH_0_att {
	BDSCR 	{ R AT91C_HDMA_CH_0_BDSCR 	RW }
	DADDR 	{ R AT91C_HDMA_CH_0_DADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_0_DPIP 	RW }
	DSCR 	{ R AT91C_HDMA_CH_0_DSCR 	RW }
	CFG 	{ R AT91C_HDMA_CH_0_CFG 	RW }
	SPIP 	{ R AT91C_HDMA_CH_0_SPIP 	RW }
	CADDR 	{ R AT91C_HDMA_CH_0_CADDR 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_0_CTRLA 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_0_CTRLB 	RW }
	SADDR 	{ R AT91C_HDMA_CH_0_SADDR 	RW }
	listeReg 	{ BDSCR DADDR DPIP DSCR CFG SPIP CADDR CTRLA CTRLB SADDR  }

}
array set HDMA_CH_1_att {
	CADDR 	{ R AT91C_HDMA_CH_1_CADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_1_DPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_1_CTRLB 	RW }
	SADDR 	{ R AT91C_HDMA_CH_1_SADDR 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_1_BDSCR 	RW }
	CFG 	{ R AT91C_HDMA_CH_1_CFG 	RW }
	DSCR 	{ R AT91C_HDMA_CH_1_DSCR 	RW }
	DADDR 	{ R AT91C_HDMA_CH_1_DADDR 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_1_CTRLA 	RW }
	SPIP 	{ R AT91C_HDMA_CH_1_SPIP 	RW }
	listeReg 	{ CADDR DPIP CTRLB SADDR BDSCR CFG DSCR DADDR CTRLA SPIP  }

}
array set HDMA_CH_2_att {
	SADDR 	{ R AT91C_HDMA_CH_2_SADDR 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_2_BDSCR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_2_DPIP 	RW }
	SPIP 	{ R AT91C_HDMA_CH_2_SPIP 	RW }
	DADDR 	{ R AT91C_HDMA_CH_2_DADDR 	RW }
	DSCR 	{ R AT91C_HDMA_CH_2_DSCR 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_2_CTRLA 	RW }
	CADDR 	{ R AT91C_HDMA_CH_2_CADDR 	RW }
	CFG 	{ R AT91C_HDMA_CH_2_CFG 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_2_CTRLB 	RW }
	listeReg 	{ SADDR BDSCR DPIP SPIP DADDR DSCR CTRLA CADDR CFG CTRLB  }

}
array set HDMA_CH_3_att {
	SPIP 	{ R AT91C_HDMA_CH_3_SPIP 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_3_CTRLA 	RW }
	DPIP 	{ R AT91C_HDMA_CH_3_DPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_3_CTRLB 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_3_BDSCR 	RW }
	DSCR 	{ R AT91C_HDMA_CH_3_DSCR 	RW }
	CADDR 	{ R AT91C_HDMA_CH_3_CADDR 	RW }
	CFG 	{ R AT91C_HDMA_CH_3_CFG 	RW }
	DADDR 	{ R AT91C_HDMA_CH_3_DADDR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_3_SADDR 	RW }
	listeReg 	{ SPIP CTRLA DPIP CTRLB BDSCR DSCR CADDR CFG DADDR SADDR  }

}
array set HDMA_CH_4_att {
	CFG 	{ R AT91C_HDMA_CH_4_CFG 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_4_BDSCR 	RW }
	CADDR 	{ R AT91C_HDMA_CH_4_CADDR 	RW }
	DADDR 	{ R AT91C_HDMA_CH_4_DADDR 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_4_CTRLA 	RW }
	SADDR 	{ R AT91C_HDMA_CH_4_SADDR 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_4_CTRLB 	RW }
	DSCR 	{ R AT91C_HDMA_CH_4_DSCR 	RW }
	SPIP 	{ R AT91C_HDMA_CH_4_SPIP 	RW }
	DPIP 	{ R AT91C_HDMA_CH_4_DPIP 	RW }
	listeReg 	{ CFG BDSCR CADDR DADDR CTRLA SADDR CTRLB DSCR SPIP DPIP  }

}
array set HDMA_CH_5_att {
	CTRLB 	{ R AT91C_HDMA_CH_5_CTRLB 	RW }
	DADDR 	{ R AT91C_HDMA_CH_5_DADDR 	RW }
	SPIP 	{ R AT91C_HDMA_CH_5_SPIP 	RW }
	DSCR 	{ R AT91C_HDMA_CH_5_DSCR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_5_DPIP 	RW }
	CFG 	{ R AT91C_HDMA_CH_5_CFG 	RW }
	CADDR 	{ R AT91C_HDMA_CH_5_CADDR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_5_SADDR 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_5_BDSCR 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_5_CTRLA 	RW }
	listeReg 	{ CTRLB DADDR SPIP DSCR DPIP CFG CADDR SADDR BDSCR CTRLA  }

}
array set HDMA_CH_6_att {
	SADDR 	{ R AT91C_HDMA_CH_6_SADDR 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_6_BDSCR 	RW }
	CADDR 	{ R AT91C_HDMA_CH_6_CADDR 	RW }
	SPIP 	{ R AT91C_HDMA_CH_6_SPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_6_CTRLB 	RW }
	DSCR 	{ R AT91C_HDMA_CH_6_DSCR 	RW }
	CFG 	{ R AT91C_HDMA_CH_6_CFG 	RW }
	DPIP 	{ R AT91C_HDMA_CH_6_DPIP 	RW }
	DADDR 	{ R AT91C_HDMA_CH_6_DADDR 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_6_CTRLA 	RW }
	listeReg 	{ SADDR BDSCR CADDR SPIP CTRLB DSCR CFG DPIP DADDR CTRLA  }

}
array set HDMA_CH_7_att {
	CADDR 	{ R AT91C_HDMA_CH_7_CADDR 	RW }
	CFG 	{ R AT91C_HDMA_CH_7_CFG 	RW }
	DADDR 	{ R AT91C_HDMA_CH_7_DADDR 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_7_CTRLB 	RW }
	DSCR 	{ R AT91C_HDMA_CH_7_DSCR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_7_DPIP 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_7_CTRLA 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_7_BDSCR 	RW }
	SPIP 	{ R AT91C_HDMA_CH_7_SPIP 	RW }
	SADDR 	{ R AT91C_HDMA_CH_7_SADDR 	RW }
	listeReg 	{ CADDR CFG DADDR CTRLB DSCR DPIP CTRLA BDSCR SPIP SADDR  }

}

# ========== Peripheral attributes for LCDC peripheral ========== 
array set LCDC_att {
	MVAL 	{ R AT91C_LCDC_MVAL 	RW }
	PWRCON 	{ R AT91C_LCDC_PWRCON 	RW }
	ISR 	{ R AT91C_LCDC_ISR 	RO }
	FRMP1 	{ R AT91C_LCDC_FRMP1 	RO }
	CTRSTVAL 	{ R AT91C_LCDC_CTRSTVAL 	RW }
	ICR 	{ R AT91C_LCDC_ICR 	WO }
	TIM1 	{ R AT91C_LCDC_TIM1 	RW }
	DMACON 	{ R AT91C_LCDC_DMACON 	RW }
	ITR 	{ R AT91C_LCDC_ITR 	WO }
	IDR 	{ R AT91C_LCDC_IDR 	WO }
	7 	{ R AT91C_LCDC_DP4_7 	RW }
	7 	{ R AT91C_LCDC_DP5_7 	RW }
	IRR 	{ R AT91C_LCDC_IRR 	RW }
	4 	{ R AT91C_LCDC_DP3_4 	RW }
	IMR 	{ R AT91C_LCDC_IMR 	RO }
	LCDFRCFG 	{ R AT91C_LCDC_LCDFRCFG 	RW }
	CTRSTCON 	{ R AT91C_LCDC_CTRSTCON 	RW }
	2 	{ R AT91C_LCDC_DP1_2 	RW }
	FRMP2 	{ R AT91C_LCDC_FRMP2 	RO }
	LCDCON1 	{ R AT91C_LCDC_LCDCON1 	RW }
	5 	{ R AT91C_LCDC_DP4_5 	RW }
	FRMA2 	{ R AT91C_LCDC_FRMA2 	RO }
	BA1 	{ R AT91C_LCDC_BA1 	RW }
	DMA2DCFG 	{ R AT91C_LCDC_DMA2DCFG 	RW }
	ENTRY 	{ R AT91C_LCDC_LUT_ENTRY 	RW 256 }
	7 	{ R AT91C_LCDC_DP6_7 	RW }
	FRMCFG 	{ R AT91C_LCDC_FRMCFG 	RW }
	TIM2 	{ R AT91C_LCDC_TIM2 	RW }
	5 	{ R AT91C_LCDC_DP3_5 	RW }
	FRMA1 	{ R AT91C_LCDC_FRMA1 	RO }
	IER 	{ R AT91C_LCDC_IER 	WO }
	3 	{ R AT91C_LCDC_DP2_3 	RW }
	FIFO 	{ R AT91C_LCDC_FIFO 	RW }
	BA2 	{ R AT91C_LCDC_BA2 	RW }
	LCDCON2 	{ R AT91C_LCDC_LCDCON2 	RW }
	GPR 	{ R AT91C_LCDC_GPR 	RW }
	listeReg 	{ MVAL PWRCON ISR FRMP1 CTRSTVAL ICR TIM1 DMACON ITR IDR 7 7 IRR 4 IMR LCDFRCFG CTRSTCON 2 FRMP2 LCDCON1 5 FRMA2 BA1 DMA2DCFG ENTRY 7 FRMCFG TIM2 5 FRMA1 IER 3 FIFO BA2 LCDCON2 GPR  }

}
array set LCDC_16B_TFT_att {
	MVAL 	{ R AT91C_TFT_MVAL 	RW }
	PWRCON 	{ R AT91C_TFT_PWRCON 	RW }
	ISR 	{ R AT91C_TFT_ISR 	RO }
	FRMP1 	{ R AT91C_TFT_FRMP1 	RO }
	CTRSTVAL 	{ R AT91C_TFT_CTRSTVAL 	RW }
	ICR 	{ R AT91C_TFT_ICR 	WO }
	TIM1 	{ R AT91C_TFT_TIM1 	RW }
	DMACON 	{ R AT91C_TFT_DMACON 	RW }
	ITR 	{ R AT91C_TFT_ITR 	WO }
	IDR 	{ R AT91C_TFT_IDR 	WO }
	7 	{ R AT91C_TFT_DP4_7 	RW }
	7 	{ R AT91C_TFT_DP5_7 	RW }
	IRR 	{ R AT91C_TFT_IRR 	RW }
	4 	{ R AT91C_TFT_DP3_4 	RW }
	IMR 	{ R AT91C_TFT_IMR 	RO }
	LCDFRCFG 	{ R AT91C_TFT_LCDFRCFG 	RW }
	CTRSTCON 	{ R AT91C_TFT_CTRSTCON 	RW }
	2 	{ R AT91C_TFT_DP1_2 	RW }
	FRMP2 	{ R AT91C_TFT_FRMP2 	RO }
	LCDCON1 	{ R AT91C_TFT_LCDCON1 	RW }
	5 	{ R AT91C_TFT_DP4_5 	RW }
	FRMA2 	{ R AT91C_TFT_FRMA2 	RO }
	BA1 	{ R AT91C_TFT_BA1 	RW }
	DMA2DCFG 	{ R AT91C_TFT_DMA2DCFG 	RW }
	ENTRY 	{ R AT91C_TFT_LUT_ENTRY 	RW 256 }
	7 	{ R AT91C_TFT_DP6_7 	RW }
	FRMCFG 	{ R AT91C_TFT_FRMCFG 	RW }
	TIM2 	{ R AT91C_TFT_TIM2 	RW }
	5 	{ R AT91C_TFT_DP3_5 	RW }
	FRMA1 	{ R AT91C_TFT_FRMA1 	RO }
	IER 	{ R AT91C_TFT_IER 	WO }
	3 	{ R AT91C_TFT_DP2_3 	RW }
	FIFO 	{ R AT91C_TFT_FIFO 	RW }
	BA2 	{ R AT91C_TFT_BA2 	RW }
	LCDCON2 	{ R AT91C_TFT_LCDCON2 	RW }
	GPR 	{ R AT91C_TFT_GPR 	RW }
	listeReg 	{ MVAL PWRCON ISR FRMP1 CTRSTVAL ICR TIM1 DMACON ITR IDR 7 7 IRR 4 IMR LCDFRCFG CTRSTCON 2 FRMP2 LCDCON1 5 FRMA2 BA1 DMA2DCFG ENTRY 7 FRMCFG TIM2 5 FRMA1 IER 3 FIFO BA2 LCDCON2 GPR  }

}

# ========== Peripheral attributes for SMC peripheral ========== 
array set SMC_att {
	PULSE7 	{ R AT91C_SMC_PULSE7 	RW }
	DELAY1 	{ R AT91C_SMC_DELAY1 	WO }
	CYCLE2 	{ R AT91C_SMC_CYCLE2 	RW }
	DELAY5 	{ R AT91C_SMC_DELAY5 	WO }
	DELAY6 	{ R AT91C_SMC_DELAY6 	WO }
	PULSE2 	{ R AT91C_SMC_PULSE2 	RW }
	SETUP6 	{ R AT91C_SMC_SETUP6 	RW }
	SETUP5 	{ R AT91C_SMC_SETUP5 	RW }
	CYCLE6 	{ R AT91C_SMC_CYCLE6 	RW }
	PULSE6 	{ R AT91C_SMC_PULSE6 	RW }
	CTRL5 	{ R AT91C_SMC_CTRL5 	RW }
	CTRL3 	{ R AT91C_SMC_CTRL3 	RW }
	DELAY7 	{ R AT91C_SMC_DELAY7 	WO }
	DELAY3 	{ R AT91C_SMC_DELAY3 	WO }
	CYCLE0 	{ R AT91C_SMC_CYCLE0 	RW }
	SETUP1 	{ R AT91C_SMC_SETUP1 	RW }
	PULSE5 	{ R AT91C_SMC_PULSE5 	RW }
	SETUP7 	{ R AT91C_SMC_SETUP7 	RW }
	CTRL4 	{ R AT91C_SMC_CTRL4 	RW }
	DELAY2 	{ R AT91C_SMC_DELAY2 	WO }
	PULSE3 	{ R AT91C_SMC_PULSE3 	RW }
	CYCLE4 	{ R AT91C_SMC_CYCLE4 	RW }
	CTRL1 	{ R AT91C_SMC_CTRL1 	RW }
	SETUP3 	{ R AT91C_SMC_SETUP3 	RW }
	CTRL0 	{ R AT91C_SMC_CTRL0 	RW }
	CYCLE7 	{ R AT91C_SMC_CYCLE7 	RW }
	DELAY4 	{ R AT91C_SMC_DELAY4 	WO }
	CYCLE1 	{ R AT91C_SMC_CYCLE1 	RW }
	SETUP2 	{ R AT91C_SMC_SETUP2 	RW }
	PULSE1 	{ R AT91C_SMC_PULSE1 	RW }
	DELAY8 	{ R AT91C_SMC_DELAY8 	WO }
	CTRL2 	{ R AT91C_SMC_CTRL2 	RW }
	PULSE4 	{ R AT91C_SMC_PULSE4 	RW }
	SETUP4 	{ R AT91C_SMC_SETUP4 	RW }
	CYCLE3 	{ R AT91C_SMC_CYCLE3 	RW }
	SETUP0 	{ R AT91C_SMC_SETUP0 	RW }
	CYCLE5 	{ R AT91C_SMC_CYCLE5 	RW }
	PULSE0 	{ R AT91C_SMC_PULSE0 	RW }
	CTRL6 	{ R AT91C_SMC_CTRL6 	RW }
	CTRL7 	{ R AT91C_SMC_CTRL7 	RW }
	listeReg 	{ PULSE7 DELAY1 CYCLE2 DELAY5 DELAY6 PULSE2 SETUP6 SETUP5 CYCLE6 PULSE6 CTRL5 CTRL3 DELAY7 DELAY3 CYCLE0 SETUP1 PULSE5 SETUP7 CTRL4 DELAY2 PULSE3 CYCLE4 CTRL1 SETUP3 CTRL0 CYCLE7 DELAY4 CYCLE1 SETUP2 PULSE1 DELAY8 CTRL2 PULSE4 SETUP4 CYCLE3 SETUP0 CYCLE5 PULSE0 CTRL6 CTRL7  }

}

# ========== Peripheral attributes for RSTC peripheral ========== 
array set RSTC_att {
	RCR 	{ R AT91C_RSTC_RCR 	WO }
	RMR 	{ R AT91C_RSTC_RMR 	RW }
	RSR 	{ R AT91C_RSTC_RSR 	RO }
	listeReg 	{ RCR RMR RSR  }

}

# ========== Peripheral attributes for SSC peripheral ========== 
array set SSC0_att {
	CMR 	{ R AT91C_SSC0_CMR 	RW }
	SR 	{ R AT91C_SSC0_SR 	RO }
	TSHR 	{ R AT91C_SSC0_TSHR 	RW }
	TCMR 	{ R AT91C_SSC0_TCMR 	RW }
	IMR 	{ R AT91C_SSC0_IMR 	RO }
	IDR 	{ R AT91C_SSC0_IDR 	WO }
	RCMR 	{ R AT91C_SSC0_RCMR 	RW }
	IER 	{ R AT91C_SSC0_IER 	WO }
	RSHR 	{ R AT91C_SSC0_RSHR 	RO }
	CR 	{ R AT91C_SSC0_CR 	WO }
	RHR 	{ R AT91C_SSC0_RHR 	RO }
	THR 	{ R AT91C_SSC0_THR 	WO }
	RFMR 	{ R AT91C_SSC0_RFMR 	RW }
	TFMR 	{ R AT91C_SSC0_TFMR 	RW }
	listeReg 	{ CMR SR TSHR TCMR IMR IDR RCMR IER RSHR CR RHR THR RFMR TFMR  }

}
array set SSC1_att {
	SR 	{ R AT91C_SSC1_SR 	RO }
	RHR 	{ R AT91C_SSC1_RHR 	RO }
	TFMR 	{ R AT91C_SSC1_TFMR 	RW }
	TCMR 	{ R AT91C_SSC1_TCMR 	RW }
	CR 	{ R AT91C_SSC1_CR 	WO }
	RSHR 	{ R AT91C_SSC1_RSHR 	RO }
	CMR 	{ R AT91C_SSC1_CMR 	RW }
	IER 	{ R AT91C_SSC1_IER 	WO }
	THR 	{ R AT91C_SSC1_THR 	WO }
	IMR 	{ R AT91C_SSC1_IMR 	RO }
	TSHR 	{ R AT91C_SSC1_TSHR 	RW }
	RFMR 	{ R AT91C_SSC1_RFMR 	RW }
	IDR 	{ R AT91C_SSC1_IDR 	WO }
	RCMR 	{ R AT91C_SSC1_RCMR 	RW }
	listeReg 	{ SR RHR TFMR TCMR CR RSHR CMR IER THR IMR TSHR RFMR IDR RCMR  }

}

# ========== Peripheral attributes for WDTC peripheral ========== 
array set WDTC_att {
	WDCR 	{ R AT91C_WDTC_WDCR 	WO }
	WDSR 	{ R AT91C_WDTC_WDSR 	RO }
	WDMR 	{ R AT91C_WDTC_WDMR 	RW }
	listeReg 	{ WDCR WDSR WDMR  }

}

# ========== Peripheral attributes for HDDRSDRC2 peripheral ========== 
array set DDR2CP1_att {
	DELAY2 	{ R AT91C_DDR2CP1_DELAY2 	RW }
	T3PR 	{ R AT91C_DDR2CP1_T3PR 	RW }
	RTR 	{ R AT91C_DDR2CP1_RTR 	RW }
	T0PR 	{ R AT91C_DDR2CP1_T0PR 	RW }
	WPSR 	{ R AT91C_DDR2CP1_WPSR 	RO }
	DELAY8 	{ R AT91C_DDR2CP1_DELAY8 	RW }
	LPR 	{ R AT91C_DDR2CP1_LPR 	RW }
	VER 	{ R AT91C_DDR2CP1_VER 	RO }
	DELAY7 	{ R AT91C_DDR2CP1_DELAY7 	RW }
	CR 	{ R AT91C_DDR2CP1_CR 	RW }
	WPCR 	{ R AT91C_DDR2CP1_WPCR 	RW }
	MR 	{ R AT91C_DDR2CP1_MR 	RW }
	DELAY5 	{ R AT91C_DDR2CP1_DELAY5 	RW }
	T2PR 	{ R AT91C_DDR2CP1_T2PR 	RW }
	HS 	{ R AT91C_DDR2CP1_HS 	RW }
	MDR 	{ R AT91C_DDR2CP1_MDR 	RW }
	DELAY4 	{ R AT91C_DDR2CP1_DELAY4 	RW }
	DELAY1 	{ R AT91C_DDR2CP1_DELAY1 	RW }
	DELAY6 	{ R AT91C_DDR2CP1_DELAY6 	RW }
	DLL 	{ R AT91C_DDR2CP1_DLL 	RO }
	DELAY3 	{ R AT91C_DDR2CP1_DELAY3 	RW }
	VERSION 	{ R AT91C_DDR2CP1_VERSION 	RO }
	T1PR 	{ R AT91C_DDR2CP1_T1PR 	RW }
	listeReg 	{ DELAY2 T3PR RTR T0PR WPSR DELAY8 LPR VER DELAY7 CR WPCR MR DELAY5 T2PR HS MDR DELAY4 DELAY1 DELAY6 DLL DELAY3 VERSION T1PR  }

}
array set DDR2C_att {
	DELAY8 	{ R AT91C_DDR2C_DELAY8 	RW }
	VER 	{ R AT91C_DDR2C_VER 	RO }
	RTR 	{ R AT91C_DDR2C_RTR 	RW }
	T0PR 	{ R AT91C_DDR2C_T0PR 	RW }
	DELAY5 	{ R AT91C_DDR2C_DELAY5 	RW }
	LPR 	{ R AT91C_DDR2C_LPR 	RW }
	HS 	{ R AT91C_DDR2C_HS 	RW }
	DELAY2 	{ R AT91C_DDR2C_DELAY2 	RW }
	T2PR 	{ R AT91C_DDR2C_T2PR 	RW }
	DELAY1 	{ R AT91C_DDR2C_DELAY1 	RW }
	T1PR 	{ R AT91C_DDR2C_T1PR 	RW }
	MDR 	{ R AT91C_DDR2C_MDR 	RW }
	DELAY6 	{ R AT91C_DDR2C_DELAY6 	RW }
	VERSION 	{ R AT91C_DDR2C_VERSION 	RO }
	MR 	{ R AT91C_DDR2C_MR 	RW }
	DLL 	{ R AT91C_DDR2C_DLL 	RO }
	DELAY4 	{ R AT91C_DDR2C_DELAY4 	RW }
	WPCR 	{ R AT91C_DDR2C_WPCR 	RW }
	CR 	{ R AT91C_DDR2C_CR 	RW }
	DELAY3 	{ R AT91C_DDR2C_DELAY3 	RW }
	WPSR 	{ R AT91C_DDR2C_WPSR 	RO }
	DELAY7 	{ R AT91C_DDR2C_DELAY7 	RW }
	T3PR 	{ R AT91C_DDR2C_T3PR 	RW }
	listeReg 	{ DELAY8 VER RTR T0PR DELAY5 LPR HS DELAY2 T2PR DELAY1 T1PR MDR DELAY6 VERSION MR DLL DELAY4 WPCR CR DELAY3 WPSR DELAY7 T3PR  }

}

# ========== Peripheral attributes for TRNG peripheral ========== 
array set TRNG_att {
	IDR 	{ R AT91C_TRNG_IDR 	WO }
	IER 	{ R AT91C_TRNG_IER 	WO }
	VERSION 	{ R AT91C_TRNG_VERSION 	RO }
	ISR 	{ R AT91C_TRNG_ISR 	RO }
	CR 	{ R AT91C_TRNG_CR 	WO }
	ODATA 	{ R AT91C_TRNG_ODATA 	R0 }
	IMR 	{ R AT91C_TRNG_IMR 	RO }
	listeReg 	{ IDR IER VERSION ISR CR ODATA IMR  }

}

# ========== Peripheral attributes for VDEC peripheral ========== 
array set VDEC_att {
	DCR 	{ R AT91C_VDEC_DCR 	RW }
	IDR 	{ R AT91C_VDEC_IDR 	RO }
	ISR 	{ R AT91C_VDEC_ISR 	RW }
	listeReg 	{ DCR IDR ISR  }

}

# ========== Peripheral attributes for CKGR peripheral ========== 
array set CKGR_att {
	MOR 	{ R AT91C_CKGR_MOR 	RW }
	MCFR 	{ R AT91C_CKGR_MCFR 	RO }
	PLLAR 	{ R AT91C_CKGR_PLLAR 	RW }
	UCKR 	{ R AT91C_CKGR_UCKR 	RW }
	listeReg 	{ MOR MCFR PLLAR UCKR  }

}

# ========== Peripheral attributes for AES peripheral ========== 
array set AES_att {
	IVxR 	{ R AT91C_AES_IVxR 	W0  4 }
	KEYWxR 	{ R AT91C_AES_KEYWxR 	WO  8 }
	CR 	{ R AT91C_AES_CR 	WO }
	IER 	{ R AT91C_AES_IER 	WO }
	IDATAxR 	{ R AT91C_AES_IDATAxR 	WO  4 }
	MR 	{ R AT91C_AES_MR 	RW }
	IDR 	{ R AT91C_AES_IDR 	WO }
	IMR 	{ R AT91C_AES_IMR 	RO }
	ODATAxR 	{ R AT91C_AES_ODATAxR 	R0  4 }
	ISR 	{ R AT91C_AES_ISR 	RO }
	VR 	{ R AT91C_AES_VR 	RO }
	listeReg 	{ IVxR KEYWxR CR IER IDATAxR MR IDR IMR ODATAxR ISR VR  }

}

# ========== Peripheral attributes for TWI peripheral ========== 
array set TWI0_att {
	RHR 	{ R AT91C_TWI0_RHR 	RO }
	IMR 	{ R AT91C_TWI0_IMR 	RO }
	SR 	{ R AT91C_TWI0_SR 	RO }
	IADR 	{ R AT91C_TWI0_IADR 	RW }
	IDR 	{ R AT91C_TWI0_IDR 	WO }
	CWGR 	{ R AT91C_TWI0_CWGR 	RW }
	IER 	{ R AT91C_TWI0_IER 	WO }
	THR 	{ R AT91C_TWI0_THR 	WO }
	CR 	{ R AT91C_TWI0_CR 	WO }
	MMR 	{ R AT91C_TWI0_MMR 	RW }
	listeReg 	{ RHR IMR SR IADR IDR CWGR IER THR CR MMR  }

}
array set TWI1_att {
	IDR 	{ R AT91C_TWI1_IDR 	WO }
	RHR 	{ R AT91C_TWI1_RHR 	RO }
	IMR 	{ R AT91C_TWI1_IMR 	RO }
	THR 	{ R AT91C_TWI1_THR 	WO }
	IER 	{ R AT91C_TWI1_IER 	WO }
	IADR 	{ R AT91C_TWI1_IADR 	RW }
	MMR 	{ R AT91C_TWI1_MMR 	RW }
	CR 	{ R AT91C_TWI1_CR 	WO }
	SR 	{ R AT91C_TWI1_SR 	RO }
	CWGR 	{ R AT91C_TWI1_CWGR 	RW }
	listeReg 	{ IDR RHR IMR THR IER IADR MMR CR SR CWGR  }

}

# ========== Peripheral attributes for SHA peripheral ========== 
array set SHA_att {
	IMR 	{ R AT91C_SHA_IMR 	RO }
	IER 	{ R AT91C_SHA_IER 	WO }
	VR 	{ R AT91C_SHA_VR 	RO }
	CR 	{ R AT91C_SHA_CR 	WO }
	MR 	{ R AT91C_SHA_MR 	RW }
	IDR 	{ R AT91C_SHA_IDR 	WO }
	ISR 	{ R AT91C_SHA_ISR 	RO }
	IDATAxR 	{ R AT91C_SHA_IDATAxR 	WO 16 }
	ODATAxR 	{ R AT91C_SHA_ODATAxR 	R0  8 }
	listeReg 	{ IMR IER VR CR MR IDR ISR IDATAxR ODATAxR  }

}

# ========== Peripheral attributes for TSADC peripheral ========== 
array set TSADC_att {
	CHSR 	{ R AT91C_TSADC_CHSR 	RO }
	CDR5 	{ R AT91C_TSADC_CDR5 	RO }
	CR 	{ R AT91C_TSADC_CR 	WO }
	IMR 	{ R AT91C_TSADC_IMR 	RO }
	CHDR 	{ R AT91C_TSADC_CHDR 	WO }
	LCDR 	{ R AT91C_TSADC_LCDR 	RO }
	IER 	{ R AT91C_TSADC_IER 	WO }
	TSR 	{ R AT91C_TSADC_TSR 	RW }
	CDR2 	{ R AT91C_TSADC_CDR2 	RO }
	CDR4 	{ R AT91C_TSADC_CDR4 	RO }
	CHER 	{ R AT91C_TSADC_CHER 	WO }
	TRGR 	{ R AT91C_TSADC_TRGR 	RW }
	CDR3 	{ R AT91C_TSADC_CDR3 	RO }
	SR 	{ R AT91C_TSADC_SR 	RO }
	CDR0 	{ R AT91C_TSADC_CDR0 	RO }
	CDR6 	{ R AT91C_TSADC_CDR6 	RO }
	IDR 	{ R AT91C_TSADC_IDR 	WO }
	MR 	{ R AT91C_TSADC_MR 	RW }
	CDR7 	{ R AT91C_TSADC_CDR7 	RO }
	CDR1 	{ R AT91C_TSADC_CDR1 	RO }
	listeReg 	{ CHSR CDR5 CR IMR CHDR LCDR IER TSR CDR2 CDR4 CHER TRGR CDR3 SR CDR0 CDR6 IDR MR CDR7 CDR1  }

}

# ========== Peripheral attributes for HDMA peripheral ========== 
array set HDMA_att {
	EBCIDR 	{ R AT91C_HDMA_EBCIDR 	WO }
	LAST 	{ R AT91C_HDMA_LAST 	RW }
	SREQ 	{ R AT91C_HDMA_SREQ 	RW }
	RSVD0 	{ R AT91C_HDMA_RSVD0 	WO }
	EBCIER 	{ R AT91C_HDMA_EBCIER 	WO }
	GCFG 	{ R AT91C_HDMA_GCFG 	RW }
	CHER 	{ R AT91C_HDMA_CHER 	WO }
	RSVD1 	{ R AT91C_HDMA_RSVD1 	WO }
	CHDR 	{ R AT91C_HDMA_CHDR 	WO }
	EBCIMR 	{ R AT91C_HDMA_EBCIMR 	RO }
	CREQ 	{ R AT91C_HDMA_CREQ 	RW }
	SYNC 	{ R AT91C_HDMA_SYNC 	RW }
	EN 	{ R AT91C_HDMA_EN 	RW }
	EBCISR 	{ R AT91C_HDMA_EBCISR 	RO }
	CHSR 	{ R AT91C_HDMA_CHSR 	RO }
	listeReg 	{ EBCIDR LAST SREQ RSVD0 EBCIER GCFG CHER RSVD1 CHDR EBCIMR CREQ SYNC EN EBCISR CHSR  }

}

# ========== Peripheral attributes for RTTC peripheral ========== 
array set RTTC_att {
	RTSR 	{ R AT91C_RTTC_RTSR 	RO }
	RTMR 	{ R AT91C_RTTC_RTMR 	RW }
	RTVR 	{ R AT91C_RTTC_RTVR 	RO }
	RTAR 	{ R AT91C_RTTC_RTAR 	RW }
	listeReg 	{ RTSR RTMR RTVR RTAR  }

}

# ========== Peripheral attributes for TDES peripheral ========== 
array set TDES_att {
	IDR 	{ R AT91C_TDES_IDR 	WO }
	ISR 	{ R AT91C_TDES_ISR 	RO }
	KEY2WxR 	{ R AT91C_TDES_KEY2WxR 	WO  2 }
	KEY3WxR 	{ R AT91C_TDES_KEY3WxR 	WO  2 }
	IMR 	{ R AT91C_TDES_IMR 	RO }
	KEY1WxR 	{ R AT91C_TDES_KEY1WxR 	WO  2 }
	VR 	{ R AT91C_TDES_VR 	RO }
	IER 	{ R AT91C_TDES_IER 	WO }
	IVxR 	{ R AT91C_TDES_IVxR 	W0  2 }
	IDATAxR 	{ R AT91C_TDES_IDATAxR 	WO  2 }
	CR 	{ R AT91C_TDES_CR 	WO }
	MR 	{ R AT91C_TDES_MR 	RW }
	ODATAxR 	{ R AT91C_TDES_ODATAxR 	R0  2 }
	listeReg 	{ IDR ISR KEY2WxR KEY3WxR IMR KEY1WxR VR IER IVxR IDATAxR CR MR ODATAxR  }

}

# ========== Peripheral attributes for RTC peripheral ========== 
array set RTC_att {
	IDR 	{ R AT91C_RTC_IDR 	WO }
	SR 	{ R AT91C_RTC_SR 	RO }
	MR 	{ R AT91C_RTC_MR 	RW }
	IER 	{ R AT91C_RTC_IER 	WO }
	TIMALR 	{ R AT91C_RTC_TIMALR 	RW }
	CALALR 	{ R AT91C_RTC_CALALR 	RW }
	CR 	{ R AT91C_RTC_CR 	RW }
	TIMR 	{ R AT91C_RTC_TIMR 	RW }
	CALR 	{ R AT91C_RTC_CALR 	RW }
	VER 	{ R AT91C_RTC_VER 	RO }
	SCCR 	{ R AT91C_RTC_SCCR 	WO }
	IMR 	{ R AT91C_RTC_IMR 	RO }
	listeReg 	{ IDR SR MR IER TIMALR CALALR CR TIMR CALR VER SCCR IMR  }

}

# ========== Peripheral attributes for TC peripheral ========== 
array set TC0_att {
	IER 	{ R AT91C_TC0_IER 	WO }
	IMR 	{ R AT91C_TC0_IMR 	RO }
	CCR 	{ R AT91C_TC0_CCR 	WO }
	RB 	{ R AT91C_TC0_RB 	RW }
	CV 	{ R AT91C_TC0_CV 	RW }
	SR 	{ R AT91C_TC0_SR 	RO }
	CMR 	{ R AT91C_TC0_CMR 	RW }
	RA 	{ R AT91C_TC0_RA 	RW }
	RC 	{ R AT91C_TC0_RC 	RW }
	IDR 	{ R AT91C_TC0_IDR 	WO }
	listeReg 	{ IER IMR CCR RB CV SR CMR RA RC IDR  }

}
array set TC1_att {
	IER 	{ R AT91C_TC1_IER 	WO }
	SR 	{ R AT91C_TC1_SR 	RO }
	RC 	{ R AT91C_TC1_RC 	RW }
	CV 	{ R AT91C_TC1_CV 	RW }
	RA 	{ R AT91C_TC1_RA 	RW }
	CMR 	{ R AT91C_TC1_CMR 	RW }
	IDR 	{ R AT91C_TC1_IDR 	WO }
	RB 	{ R AT91C_TC1_RB 	RW }
	IMR 	{ R AT91C_TC1_IMR 	RO }
	CCR 	{ R AT91C_TC1_CCR 	WO }
	listeReg 	{ IER SR RC CV RA CMR IDR RB IMR CCR  }

}
array set TC2_att {
	SR 	{ R AT91C_TC2_SR 	RO }
	IMR 	{ R AT91C_TC2_IMR 	RO }
	IER 	{ R AT91C_TC2_IER 	WO }
	CV 	{ R AT91C_TC2_CV 	RW }
	RB 	{ R AT91C_TC2_RB 	RW }
	CCR 	{ R AT91C_TC2_CCR 	WO }
	CMR 	{ R AT91C_TC2_CMR 	RW }
	RA 	{ R AT91C_TC2_RA 	RW }
	IDR 	{ R AT91C_TC2_IDR 	WO }
	RC 	{ R AT91C_TC2_RC 	RW }
	listeReg 	{ SR IMR IER CV RB CCR CMR RA IDR RC  }

}
array set TC3_att {
	SR 	{ R AT91C_TC3_SR 	RO }
	RC 	{ R AT91C_TC3_RC 	RW }
	IER 	{ R AT91C_TC3_IER 	WO }
	CV 	{ R AT91C_TC3_CV 	RW }
	IDR 	{ R AT91C_TC3_IDR 	WO }
	IMR 	{ R AT91C_TC3_IMR 	RO }
	CMR 	{ R AT91C_TC3_CMR 	RW }
	RB 	{ R AT91C_TC3_RB 	RW }
	CCR 	{ R AT91C_TC3_CCR 	WO }
	RA 	{ R AT91C_TC3_RA 	RW }
	listeReg 	{ SR RC IER CV IDR IMR CMR RB CCR RA  }

}
array set TC4_att {
	CV 	{ R AT91C_TC4_CV 	RW }
	RA 	{ R AT91C_TC4_RA 	RW }
	IDR 	{ R AT91C_TC4_IDR 	WO }
	SR 	{ R AT91C_TC4_SR 	RO }
	CMR 	{ R AT91C_TC4_CMR 	RW }
	CCR 	{ R AT91C_TC4_CCR 	WO }
	RB 	{ R AT91C_TC4_RB 	RW }
	RC 	{ R AT91C_TC4_RC 	RW }
	IER 	{ R AT91C_TC4_IER 	WO }
	IMR 	{ R AT91C_TC4_IMR 	RO }
	listeReg 	{ CV RA IDR SR CMR CCR RB RC IER IMR  }

}
array set TC5_att {
	IER 	{ R AT91C_TC5_IER 	WO }
	IDR 	{ R AT91C_TC5_IDR 	WO }
	RA 	{ R AT91C_TC5_RA 	RW }
	RB 	{ R AT91C_TC5_RB 	RW }
	CCR 	{ R AT91C_TC5_CCR 	WO }
	SR 	{ R AT91C_TC5_SR 	RO }
	CV 	{ R AT91C_TC5_CV 	RW }
	RC 	{ R AT91C_TC5_RC 	RW }
	IMR 	{ R AT91C_TC5_IMR 	RO }
	CMR 	{ R AT91C_TC5_CMR 	RW }
	listeReg 	{ IER IDR RA RB CCR SR CV RC IMR CMR  }

}

# ========== Peripheral attributes for SYS peripheral ========== 
array set SYS_att {
	SLCKSEL 	{ R AT91C_SYS_SLCKSEL 	 }
	GPBR 	{ R AT91C_SYS_GPBR 	  4 }
	listeReg 	{ SLCKSEL GPBR  }

}

# ========== Peripheral attributes for UHPHS_OHCI peripheral ========== 
array set UHPHS_OHCI_att {
	HcRhPortStatus 	{ R AT91C_OHCI_HcRhPortStatus 	RW  2 }
	HcFmRemaining 	{ R AT91C_OHCI_HcFmRemaining 	RW }
	HcInterruptEnable 	{ R AT91C_OHCI_HcInterruptEnable 	RW }
	HcControl 	{ R AT91C_OHCI_HcControl 	RW }
	HcPeriodicStart 	{ R AT91C_OHCI_HcPeriodicStart 	RW }
	HcInterruptStatus 	{ R AT91C_OHCI_HcInterruptStatus 	RW }
	HcRhDescriptorB 	{ R AT91C_OHCI_HcRhDescriptorB 	RW }
	HcInterruptDisable 	{ R AT91C_OHCI_HcInterruptDisable 	RW }
	HcPeriodCurrentED 	{ R AT91C_OHCI_HcPeriodCurrentED 	RW }
	HcRhDescriptorA 	{ R AT91C_OHCI_HcRhDescriptorA 	RW }
	HcRhStatus 	{ R AT91C_OHCI_HcRhStatus 	RW }
	HcBulkCurrentED 	{ R AT91C_OHCI_HcBulkCurrentED 	RW }
	HcControlHeadED 	{ R AT91C_OHCI_HcControlHeadED 	RW }
	HcLSThreshold 	{ R AT91C_OHCI_HcLSThreshold 	RW }
	HcRevision 	{ R AT91C_OHCI_HcRevision 	R }
	HcBulkDoneHead 	{ R AT91C_OHCI_HcBulkDoneHead 	RW }
	HcFmNumber 	{ R AT91C_OHCI_HcFmNumber 	RW }
	HcFmInterval 	{ R AT91C_OHCI_HcFmInterval 	RW }
	HcBulkHeadED 	{ R AT91C_OHCI_HcBulkHeadED 	RW }
	HcHCCA 	{ R AT91C_OHCI_HcHCCA 	RW }
	HcCommandStatus 	{ R AT91C_OHCI_HcCommandStatus 	RW }
	HcControlCurrentED 	{ R AT91C_OHCI_HcControlCurrentED 	RW }
	listeReg 	{ HcRhPortStatus HcFmRemaining HcInterruptEnable HcControl HcPeriodicStart HcInterruptStatus HcRhDescriptorB HcInterruptDisable HcPeriodCurrentED HcRhDescriptorA HcRhStatus HcBulkCurrentED HcControlHeadED HcLSThreshold HcRevision HcBulkDoneHead HcFmNumber HcFmInterval HcBulkHeadED HcHCCA HcCommandStatus HcControlCurrentED  }

}

# ========== Peripheral attributes for UDPHS_DMA peripheral ========== 
array set UDPHS_DMA_1_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_1_DMASTATUS 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_1_DMANXTDSC 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_1_DMACONTROL 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_1_DMAADDRESS 	RW }
	listeReg 	{ DMASTATUS DMANXTDSC DMACONTROL DMAADDRESS  }

}
array set UDPHS_DMA_2_att {
	DMACONTROL 	{ R AT91C_UDPHS_DMA_2_DMACONTROL 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_2_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_2_DMAADDRESS 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_2_DMANXTDSC 	RW }
	listeReg 	{ DMACONTROL DMASTATUS DMAADDRESS DMANXTDSC  }

}
array set UDPHS_DMA_3_att {
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_3_DMAADDRESS 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_3_DMANXTDSC 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_3_DMACONTROL 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_3_DMASTATUS 	RW }
	listeReg 	{ DMAADDRESS DMANXTDSC DMACONTROL DMASTATUS  }

}
array set UDPHS_DMA_4_att {
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_4_DMANXTDSC 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_4_DMAADDRESS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_4_DMACONTROL 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_4_DMASTATUS 	RW }
	listeReg 	{ DMANXTDSC DMAADDRESS DMACONTROL DMASTATUS  }

}
array set UDPHS_DMA_5_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_5_DMASTATUS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_5_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_5_DMANXTDSC 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_5_DMAADDRESS 	RW }
	listeReg 	{ DMASTATUS DMACONTROL DMANXTDSC DMAADDRESS  }

}
array set UDPHS_DMA_6_att {
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_6_DMANXTDSC 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_6_DMACONTROL 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_6_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_6_DMAADDRESS 	RW }
	listeReg 	{ DMANXTDSC DMACONTROL DMASTATUS DMAADDRESS  }

}

# ========== Peripheral attributes for UHPHS_EHCI peripheral ========== 
array set UHPHS_EHCI_att {
	USBSTS 	{ R AT91C_EHCI_USBSTS 	RW }
	INSNREG03 	{ R AT91C_EHCI_INSNREG03 	RW }
	INSNREG00 	{ R AT91C_EHCI_INSNREG00 	RW }
	HCSPPORTROUTE 	{ R AT91C_EHCI_HCSPPORTROUTE 	R }
	FRINDEX 	{ R AT91C_EHCI_FRINDEX 	RW }
	CONFIGFLAG 	{ R AT91C_EHCI_CONFIGFLAG 	RW }
	HCCPARAMS 	{ R AT91C_EHCI_HCCPARAMS 	R }
	USBINTR 	{ R AT91C_EHCI_USBINTR 	RW }
	PORTSC 	{ R AT91C_EHCI_PORTSC 	RW  2 }
	CTRLDSSEGMENT 	{ R AT91C_EHCI_CTRLDSSEGMENT 	RW }
	VERSION 	{ R AT91C_EHCI_VERSION 	R }
	USBCMD 	{ R AT91C_EHCI_USBCMD 	RW }
	INSNREG04 	{ R AT91C_EHCI_INSNREG04 	RW }
	PERIODICLISTBASE 	{ R AT91C_EHCI_PERIODICLISTBASE 	RW }
	INSNREG01 	{ R AT91C_EHCI_INSNREG01 	RW }
	HCSPARAMS 	{ R AT91C_EHCI_HCSPARAMS 	R }
	INSNREG05 	{ R AT91C_EHCI_INSNREG05 	RW }
	ASYNCLISTADDR 	{ R AT91C_EHCI_ASYNCLISTADDR 	RW }
	INSNREG02 	{ R AT91C_EHCI_INSNREG02 	RW }
	listeReg 	{ USBSTS INSNREG03 INSNREG00 HCSPPORTROUTE FRINDEX CONFIGFLAG HCCPARAMS USBINTR PORTSC CTRLDSSEGMENT VERSION USBCMD INSNREG04 PERIODICLISTBASE INSNREG01 HCSPARAMS INSNREG05 ASYNCLISTADDR INSNREG02  }

}

# ========== Peripheral attributes for PIO peripheral ========== 
array set PIOA_att {
	OWDR 	{ R AT91C_PIOA_OWDR 	WO }
	DELAY3 	{ R AT91C_PIOA_DELAY3 	WO }
	ISR 	{ R AT91C_PIOA_ISR 	RO }
	PDR 	{ R AT91C_PIOA_PDR 	WO }
	OSR 	{ R AT91C_PIOA_OSR 	RO }
	ABSR 	{ R AT91C_PIOA_ABSR 	RO }
	DELAY2 	{ R AT91C_PIOA_DELAY2 	WO }
	PDSR 	{ R AT91C_PIOA_PDSR 	RO }
	BSR 	{ R AT91C_PIOA_BSR 	WO }
	DELAY1 	{ R AT91C_PIOA_DELAY1 	WO }
	PPUER 	{ R AT91C_PIOA_PPUER 	WO }
	OER 	{ R AT91C_PIOA_OER 	WO }
	PER 	{ R AT91C_PIOA_PER 	WO }
	VERSION 	{ R AT91C_PIOA_VERSION 	RO }
	PPUDR 	{ R AT91C_PIOA_PPUDR 	WO }
	ODSR 	{ R AT91C_PIOA_ODSR 	RO }
	SLEWRATE1 	{ R AT91C_PIOA_SLEWRATE1 	RW }
	MDDR 	{ R AT91C_PIOA_MDDR 	WO }
	IFSR 	{ R AT91C_PIOA_IFSR 	RO }
	CODR 	{ R AT91C_PIOA_CODR 	WO }
	ASR 	{ R AT91C_PIOA_ASR 	WO }
	OWSR 	{ R AT91C_PIOA_OWSR 	RO }
	IMR 	{ R AT91C_PIOA_IMR 	RO }
	PPUSR 	{ R AT91C_PIOA_PPUSR 	RO }
	MDER 	{ R AT91C_PIOA_MDER 	WO }
	IFDR 	{ R AT91C_PIOA_IFDR 	WO }
	SODR 	{ R AT91C_PIOA_SODR 	WO }
	OWER 	{ R AT91C_PIOA_OWER 	WO }
	IDR 	{ R AT91C_PIOA_IDR 	WO }
	IFER 	{ R AT91C_PIOA_IFER 	WO }
	IER 	{ R AT91C_PIOA_IER 	WO }
	ODR 	{ R AT91C_PIOA_ODR 	WO }
	MDSR 	{ R AT91C_PIOA_MDSR 	RO }
	DELAY4 	{ R AT91C_PIOA_DELAY4 	WO }
	PSR 	{ R AT91C_PIOA_PSR 	RO }
	listeReg 	{ OWDR DELAY3 ISR PDR OSR ABSR DELAY2 PDSR BSR DELAY1 PPUER OER PER VERSION PPUDR ODSR SLEWRATE1 MDDR IFSR CODR ASR OWSR IMR PPUSR MDER IFDR SODR OWER IDR IFER IER ODR MDSR DELAY4 PSR  }

}
array set PIOB_att {
	ODR 	{ R AT91C_PIOB_ODR 	WO }
	DELAY4 	{ R AT91C_PIOB_DELAY4 	WO }
	SODR 	{ R AT91C_PIOB_SODR 	WO }
	ISR 	{ R AT91C_PIOB_ISR 	RO }
	ABSR 	{ R AT91C_PIOB_ABSR 	RO }
	IMR 	{ R AT91C_PIOB_IMR 	RO }
	MDSR 	{ R AT91C_PIOB_MDSR 	RO }
	PPUSR 	{ R AT91C_PIOB_PPUSR 	RO }
	PDSR 	{ R AT91C_PIOB_PDSR 	RO }
	DELAY3 	{ R AT91C_PIOB_DELAY3 	WO }
	MDDR 	{ R AT91C_PIOB_MDDR 	WO }
	CODR 	{ R AT91C_PIOB_CODR 	WO }
	MDER 	{ R AT91C_PIOB_MDER 	WO }
	PDR 	{ R AT91C_PIOB_PDR 	WO }
	IFSR 	{ R AT91C_PIOB_IFSR 	RO }
	PSR 	{ R AT91C_PIOB_PSR 	RO }
	SLEWRATE1 	{ R AT91C_PIOB_SLEWRATE1 	RW }
	IER 	{ R AT91C_PIOB_IER 	WO }
	PPUDR 	{ R AT91C_PIOB_PPUDR 	WO }
	PER 	{ R AT91C_PIOB_PER 	WO }
	IFDR 	{ R AT91C_PIOB_IFDR 	WO }
	IDR 	{ R AT91C_PIOB_IDR 	WO }
	OWDR 	{ R AT91C_PIOB_OWDR 	WO }
	ODSR 	{ R AT91C_PIOB_ODSR 	RO }
	DELAY2 	{ R AT91C_PIOB_DELAY2 	WO }
	OWSR 	{ R AT91C_PIOB_OWSR 	RO }
	BSR 	{ R AT91C_PIOB_BSR 	WO }
	IFER 	{ R AT91C_PIOB_IFER 	WO }
	OWER 	{ R AT91C_PIOB_OWER 	WO }
	PPUER 	{ R AT91C_PIOB_PPUER 	WO }
	OSR 	{ R AT91C_PIOB_OSR 	RO }
	ASR 	{ R AT91C_PIOB_ASR 	WO }
	OER 	{ R AT91C_PIOB_OER 	WO }
	VERSION 	{ R AT91C_PIOB_VERSION 	RO }
	DELAY1 	{ R AT91C_PIOB_DELAY1 	WO }
	listeReg 	{ ODR DELAY4 SODR ISR ABSR IMR MDSR PPUSR PDSR DELAY3 MDDR CODR MDER PDR IFSR PSR SLEWRATE1 IER PPUDR PER IFDR IDR OWDR ODSR DELAY2 OWSR BSR IFER OWER PPUER OSR ASR OER VERSION DELAY1  }

}
array set PIOC_att {
	OWDR 	{ R AT91C_PIOC_OWDR 	WO }
	IMR 	{ R AT91C_PIOC_IMR 	RO }
	ASR 	{ R AT91C_PIOC_ASR 	WO }
	PPUDR 	{ R AT91C_PIOC_PPUDR 	WO }
	CODR 	{ R AT91C_PIOC_CODR 	WO }
	OWER 	{ R AT91C_PIOC_OWER 	WO }
	ABSR 	{ R AT91C_PIOC_ABSR 	RO }
	IFDR 	{ R AT91C_PIOC_IFDR 	WO }
	VERSION 	{ R AT91C_PIOC_VERSION 	RO }
	ODR 	{ R AT91C_PIOC_ODR 	WO }
	PPUER 	{ R AT91C_PIOC_PPUER 	WO }
	SODR 	{ R AT91C_PIOC_SODR 	WO }
	ISR 	{ R AT91C_PIOC_ISR 	RO }
	OSR 	{ R AT91C_PIOC_OSR 	RO }
	MDSR 	{ R AT91C_PIOC_MDSR 	RO }
	IFER 	{ R AT91C_PIOC_IFER 	WO }
	DELAY2 	{ R AT91C_PIOC_DELAY2 	WO }
	MDER 	{ R AT91C_PIOC_MDER 	WO }
	PPUSR 	{ R AT91C_PIOC_PPUSR 	RO }
	PSR 	{ R AT91C_PIOC_PSR 	RO }
	DELAY4 	{ R AT91C_PIOC_DELAY4 	WO }
	DELAY3 	{ R AT91C_PIOC_DELAY3 	WO }
	IER 	{ R AT91C_PIOC_IER 	WO }
	SLEWRATE1 	{ R AT91C_PIOC_SLEWRATE1 	RW }
	IDR 	{ R AT91C_PIOC_IDR 	WO }
	PDSR 	{ R AT91C_PIOC_PDSR 	RO }
	DELAY1 	{ R AT91C_PIOC_DELAY1 	WO }
	PDR 	{ R AT91C_PIOC_PDR 	WO }
	OWSR 	{ R AT91C_PIOC_OWSR 	RO }
	IFSR 	{ R AT91C_PIOC_IFSR 	RO }
	ODSR 	{ R AT91C_PIOC_ODSR 	RO }
	OER 	{ R AT91C_PIOC_OER 	WO }
	MDDR 	{ R AT91C_PIOC_MDDR 	WO }
	BSR 	{ R AT91C_PIOC_BSR 	WO }
	PER 	{ R AT91C_PIOC_PER 	WO }
	listeReg 	{ OWDR IMR ASR PPUDR CODR OWER ABSR IFDR VERSION ODR PPUER SODR ISR OSR MDSR IFER DELAY2 MDER PPUSR PSR DELAY4 DELAY3 IER SLEWRATE1 IDR PDSR DELAY1 PDR OWSR IFSR ODSR OER MDDR BSR PER  }

}
array set PIOD_att {
	DELAY1 	{ R AT91C_PIOD_DELAY1 	WO }
	OWDR 	{ R AT91C_PIOD_OWDR 	WO }
	SODR 	{ R AT91C_PIOD_SODR 	WO }
	PPUER 	{ R AT91C_PIOD_PPUER 	WO }
	CODR 	{ R AT91C_PIOD_CODR 	WO }
	DELAY4 	{ R AT91C_PIOD_DELAY4 	WO }
	PSR 	{ R AT91C_PIOD_PSR 	RO }
	PDR 	{ R AT91C_PIOD_PDR 	WO }
	ODR 	{ R AT91C_PIOD_ODR 	WO }
	PPUSR 	{ R AT91C_PIOD_PPUSR 	RO }
	IFSR 	{ R AT91C_PIOD_IFSR 	RO }
	IMR 	{ R AT91C_PIOD_IMR 	RO }
	ASR 	{ R AT91C_PIOD_ASR 	WO }
	DELAY2 	{ R AT91C_PIOD_DELAY2 	WO }
	OWSR 	{ R AT91C_PIOD_OWSR 	RO }
	PER 	{ R AT91C_PIOD_PER 	WO }
	MDER 	{ R AT91C_PIOD_MDER 	WO }
	PDSR 	{ R AT91C_PIOD_PDSR 	RO }
	MDSR 	{ R AT91C_PIOD_MDSR 	RO }
	OWER 	{ R AT91C_PIOD_OWER 	WO }
	BSR 	{ R AT91C_PIOD_BSR 	WO }
	IFDR 	{ R AT91C_PIOD_IFDR 	WO }
	DELAY3 	{ R AT91C_PIOD_DELAY3 	WO }
	ABSR 	{ R AT91C_PIOD_ABSR 	RO }
	OER 	{ R AT91C_PIOD_OER 	WO }
	MDDR 	{ R AT91C_PIOD_MDDR 	WO }
	IDR 	{ R AT91C_PIOD_IDR 	WO }
	IER 	{ R AT91C_PIOD_IER 	WO }
	PPUDR 	{ R AT91C_PIOD_PPUDR 	WO }
	VERSION 	{ R AT91C_PIOD_VERSION 	RO }
	ISR 	{ R AT91C_PIOD_ISR 	RO }
	ODSR 	{ R AT91C_PIOD_ODSR 	RO }
	OSR 	{ R AT91C_PIOD_OSR 	RO }
	IFER 	{ R AT91C_PIOD_IFER 	WO }
	SLEWRATE1 	{ R AT91C_PIOD_SLEWRATE1 	RW }
	listeReg 	{ DELAY1 OWDR SODR PPUER CODR DELAY4 PSR PDR ODR PPUSR IFSR IMR ASR DELAY2 OWSR PER MDER PDSR MDSR OWER BSR IFDR DELAY3 ABSR OER MDDR IDR IER PPUDR VERSION ISR ODSR OSR IFER SLEWRATE1  }

}
array set PIOE_att {
	ODSR 	{ R AT91C_PIOE_ODSR 	RO }
	ABSR 	{ R AT91C_PIOE_ABSR 	RO }
	PSR 	{ R AT91C_PIOE_PSR 	RO }
	PPUDR 	{ R AT91C_PIOE_PPUDR 	WO }
	OER 	{ R AT91C_PIOE_OER 	WO }
	IFSR 	{ R AT91C_PIOE_IFSR 	RO }
	IFER 	{ R AT91C_PIOE_IFER 	WO }
	DELAY3 	{ R AT91C_PIOE_DELAY3 	WO }
	ODR 	{ R AT91C_PIOE_ODR 	WO }
	IDR 	{ R AT91C_PIOE_IDR 	WO }
	DELAY1 	{ R AT91C_PIOE_DELAY1 	WO }
	OSR 	{ R AT91C_PIOE_OSR 	RO }
	CODR 	{ R AT91C_PIOE_CODR 	WO }
	VERSION 	{ R AT91C_PIOE_VERSION 	RO }
	MDSR 	{ R AT91C_PIOE_MDSR 	RO }
	PDR 	{ R AT91C_PIOE_PDR 	WO }
	IER 	{ R AT91C_PIOE_IER 	WO }
	OWSR 	{ R AT91C_PIOE_OWSR 	RO }
	BSR 	{ R AT91C_PIOE_BSR 	WO }
	SLEWRATE1 	{ R AT91C_PIOE_SLEWRATE1 	RW }
	DELAY4 	{ R AT91C_PIOE_DELAY4 	WO }
	PER 	{ R AT91C_PIOE_PER 	WO }
	OWDR 	{ R AT91C_PIOE_OWDR 	WO }
	IFDR 	{ R AT91C_PIOE_IFDR 	WO }
	PPUSR 	{ R AT91C_PIOE_PPUSR 	RO }
	PDSR 	{ R AT91C_PIOE_PDSR 	RO }
	PPUER 	{ R AT91C_PIOE_PPUER 	WO }
	MDDR 	{ R AT91C_PIOE_MDDR 	WO }
	ISR 	{ R AT91C_PIOE_ISR 	RO }
	DELAY2 	{ R AT91C_PIOE_DELAY2 	WO }
	SODR 	{ R AT91C_PIOE_SODR 	WO }
	ASR 	{ R AT91C_PIOE_ASR 	WO }
	IMR 	{ R AT91C_PIOE_IMR 	RO }
	OWER 	{ R AT91C_PIOE_OWER 	WO }
	MDER 	{ R AT91C_PIOE_MDER 	WO }
	listeReg 	{ ODSR ABSR PSR PPUDR OER IFSR IFER DELAY3 ODR IDR DELAY1 OSR CODR VERSION MDSR PDR IER OWSR BSR SLEWRATE1 DELAY4 PER OWDR IFDR PPUSR PDSR PPUER MDDR ISR DELAY2 SODR ASR IMR OWER MDER  }

}

# ========== Peripheral attributes for PWMC peripheral ========== 
array set PWMC_att {
	IDR 	{ R AT91C_PWMC_IDR 	WO }
	MR 	{ R AT91C_PWMC_MR 	RW }
	VR 	{ R AT91C_PWMC_VR 	RO }
	IMR 	{ R AT91C_PWMC_IMR 	RO }
	SR 	{ R AT91C_PWMC_SR 	RO }
	ISR 	{ R AT91C_PWMC_ISR 	RO }
	ENA 	{ R AT91C_PWMC_ENA 	WO }
	IER 	{ R AT91C_PWMC_IER 	WO }
	DIS 	{ R AT91C_PWMC_DIS 	WO }
	listeReg 	{ IDR MR VR IMR SR ISR ENA IER DIS  }

}

# ========== Peripheral attributes for SFR peripheral ========== 
array set SFR_att {
	INT 	{ R AT91C_SFR_INT 	RO }
	DDRCFG 	{ R AT91C_SFR_DDRCFG 	RW }
	UTMICFG 	{ R AT91C_SFR_UTMICFG 	RW }
	EBIDELAY 	{ R AT91C_SFR_EBIDELAY 	RW }
	DDRDELAY 	{ R AT91C_SFR_DDRDELAY 	RW }
	EMA 	{ R AT91C_SFR_EMA 	RW }
	listeReg 	{ INT DDRCFG UTMICFG EBIDELAY DDRDELAY EMA  }

}

# ========== Peripheral attributes for PDC peripheral ========== 
array set PDC_DBGU_att {
	PTCR 	{ R AT91C_DBGU_PTCR 	WO }
	RCR 	{ R AT91C_DBGU_RCR 	RW }
	TCR 	{ R AT91C_DBGU_TCR 	RW }
	RNCR 	{ R AT91C_DBGU_RNCR 	RW }
	TNPR 	{ R AT91C_DBGU_TNPR 	RW }
	RNPR 	{ R AT91C_DBGU_RNPR 	RW }
	PTSR 	{ R AT91C_DBGU_PTSR 	RO }
	RPR 	{ R AT91C_DBGU_RPR 	RW }
	TPR 	{ R AT91C_DBGU_TPR 	RW }
	TNCR 	{ R AT91C_DBGU_TNCR 	RW }
	listeReg 	{ PTCR RCR TCR RNCR TNPR RNPR PTSR RPR TPR TNCR  }

}
array set PDC_US0_att {
	TNPR 	{ R AT91C_US0_TNPR 	RW }
	PTSR 	{ R AT91C_US0_PTSR 	RO }
	PTCR 	{ R AT91C_US0_PTCR 	WO }
	RNCR 	{ R AT91C_US0_RNCR 	RW }
	RCR 	{ R AT91C_US0_RCR 	RW }
	TNCR 	{ R AT91C_US0_TNCR 	RW }
	TCR 	{ R AT91C_US0_TCR 	RW }
	RNPR 	{ R AT91C_US0_RNPR 	RW }
	RPR 	{ R AT91C_US0_RPR 	RW }
	TPR 	{ R AT91C_US0_TPR 	RW }
	listeReg 	{ TNPR PTSR PTCR RNCR RCR TNCR TCR RNPR RPR TPR  }

}
array set PDC_US1_att {
	PTCR 	{ R AT91C_US1_PTCR 	WO }
	TNCR 	{ R AT91C_US1_TNCR 	RW }
	RCR 	{ R AT91C_US1_RCR 	RW }
	RPR 	{ R AT91C_US1_RPR 	RW }
	TPR 	{ R AT91C_US1_TPR 	RW }
	TCR 	{ R AT91C_US1_TCR 	RW }
	RNPR 	{ R AT91C_US1_RNPR 	RW }
	TNPR 	{ R AT91C_US1_TNPR 	RW }
	RNCR 	{ R AT91C_US1_RNCR 	RW }
	PTSR 	{ R AT91C_US1_PTSR 	RO }
	listeReg 	{ PTCR TNCR RCR RPR TPR TCR RNPR TNPR RNCR PTSR  }

}
array set PDC_US2_att {
	RNCR 	{ R AT91C_US2_RNCR 	RW }
	PTCR 	{ R AT91C_US2_PTCR 	WO }
	TNPR 	{ R AT91C_US2_TNPR 	RW }
	TNCR 	{ R AT91C_US2_TNCR 	RW }
	TPR 	{ R AT91C_US2_TPR 	RW }
	RCR 	{ R AT91C_US2_RCR 	RW }
	PTSR 	{ R AT91C_US2_PTSR 	RO }
	TCR 	{ R AT91C_US2_TCR 	RW }
	RPR 	{ R AT91C_US2_RPR 	RW }
	RNPR 	{ R AT91C_US2_RNPR 	RW }
	listeReg 	{ RNCR PTCR TNPR TNCR TPR RCR PTSR TCR RPR RNPR  }

}
array set PDC_US3_att {
	PTSR 	{ R AT91C_US3_PTSR 	RO }
	TCR 	{ R AT91C_US3_TCR 	RW }
	RNPR 	{ R AT91C_US3_RNPR 	RW }
	RNCR 	{ R AT91C_US3_RNCR 	RW }
	TNPR 	{ R AT91C_US3_TNPR 	RW }
	RPR 	{ R AT91C_US3_RPR 	RW }
	TPR 	{ R AT91C_US3_TPR 	RW }
	RCR 	{ R AT91C_US3_RCR 	RW }
	TNCR 	{ R AT91C_US3_TNCR 	RW }
	PTCR 	{ R AT91C_US3_PTCR 	WO }
	listeReg 	{ PTSR TCR RNPR RNCR TNPR RPR TPR RCR TNCR PTCR  }

}
array set PDC_SSC0_att {
	TNPR 	{ R AT91C_SSC0_TNPR 	RW }
	PTSR 	{ R AT91C_SSC0_PTSR 	RO }
	TNCR 	{ R AT91C_SSC0_TNCR 	RW }
	RNCR 	{ R AT91C_SSC0_RNCR 	RW }
	TPR 	{ R AT91C_SSC0_TPR 	RW }
	RCR 	{ R AT91C_SSC0_RCR 	RW }
	PTCR 	{ R AT91C_SSC0_PTCR 	WO }
	RNPR 	{ R AT91C_SSC0_RNPR 	RW }
	TCR 	{ R AT91C_SSC0_TCR 	RW }
	RPR 	{ R AT91C_SSC0_RPR 	RW }
	listeReg 	{ TNPR PTSR TNCR RNCR TPR RCR PTCR RNPR TCR RPR  }

}
array set PDC_SSC1_att {
	RNPR 	{ R AT91C_SSC1_RNPR 	RW }
	TCR 	{ R AT91C_SSC1_TCR 	RW }
	TNCR 	{ R AT91C_SSC1_TNCR 	RW }
	RCR 	{ R AT91C_SSC1_RCR 	RW }
	RNCR 	{ R AT91C_SSC1_RNCR 	RW }
	PTCR 	{ R AT91C_SSC1_PTCR 	WO }
	TPR 	{ R AT91C_SSC1_TPR 	RW }
	RPR 	{ R AT91C_SSC1_RPR 	RW }
	PTSR 	{ R AT91C_SSC1_PTSR 	RO }
	TNPR 	{ R AT91C_SSC1_TNPR 	RW }
	listeReg 	{ RNPR TCR TNCR RCR RNCR PTCR TPR RPR PTSR TNPR  }

}
array set PDC_SPI0_att {
	TPR 	{ R AT91C_SPI0_TPR 	RW }
	PTCR 	{ R AT91C_SPI0_PTCR 	WO }
	RNPR 	{ R AT91C_SPI0_RNPR 	RW }
	TNCR 	{ R AT91C_SPI0_TNCR 	RW }
	TCR 	{ R AT91C_SPI0_TCR 	RW }
	RCR 	{ R AT91C_SPI0_RCR 	RW }
	RNCR 	{ R AT91C_SPI0_RNCR 	RW }
	TNPR 	{ R AT91C_SPI0_TNPR 	RW }
	RPR 	{ R AT91C_SPI0_RPR 	RW }
	PTSR 	{ R AT91C_SPI0_PTSR 	RO }
	listeReg 	{ TPR PTCR RNPR TNCR TCR RCR RNCR TNPR RPR PTSR  }

}
array set PDC_SPI1_att {
	RNCR 	{ R AT91C_SPI1_RNCR 	RW }
	TCR 	{ R AT91C_SPI1_TCR 	RW }
	RCR 	{ R AT91C_SPI1_RCR 	RW }
	TNPR 	{ R AT91C_SPI1_TNPR 	RW }
	RNPR 	{ R AT91C_SPI1_RNPR 	RW }
	RPR 	{ R AT91C_SPI1_RPR 	RW }
	TNCR 	{ R AT91C_SPI1_TNCR 	RW }
	TPR 	{ R AT91C_SPI1_TPR 	RW }
	PTSR 	{ R AT91C_SPI1_PTSR 	RO }
	PTCR 	{ R AT91C_SPI1_PTCR 	WO }
	listeReg 	{ RNCR TCR RCR TNPR RNPR RPR TNCR TPR PTSR PTCR  }

}
array set PDC_TSADC_att {
	TCR 	{ R AT91C_TSADC_TCR 	RW }
	PTCR 	{ R AT91C_TSADC_PTCR 	WO }
	RNCR 	{ R AT91C_TSADC_RNCR 	RW }
	PTSR 	{ R AT91C_TSADC_PTSR 	RO }
	TNCR 	{ R AT91C_TSADC_TNCR 	RW }
	RNPR 	{ R AT91C_TSADC_RNPR 	RW }
	RCR 	{ R AT91C_TSADC_RCR 	RW }
	TPR 	{ R AT91C_TSADC_TPR 	RW }
	TNPR 	{ R AT91C_TSADC_TNPR 	RW }
	RPR 	{ R AT91C_TSADC_RPR 	RW }
	listeReg 	{ TCR PTCR RNCR PTSR TNCR RNPR RCR TPR TNPR RPR  }

}
array set PDC_AC97C_att {
	PTSR 	{ R AT91C_AC97C_PTSR 	RO }
	RPR 	{ R AT91C_AC97C_RPR 	RW }
	RNCR 	{ R AT91C_AC97C_RNCR 	RW }
	RCR 	{ R AT91C_AC97C_RCR 	RW }
	PTCR 	{ R AT91C_AC97C_PTCR 	WO }
	TPR 	{ R AT91C_AC97C_TPR 	RW }
	RNPR 	{ R AT91C_AC97C_RNPR 	RW }
	TNPR 	{ R AT91C_AC97C_TNPR 	RW }
	TCR 	{ R AT91C_AC97C_TCR 	RW }
	TNCR 	{ R AT91C_AC97C_TNCR 	RW }
	listeReg 	{ PTSR RPR RNCR RCR PTCR TPR RNPR TNPR TCR TNCR  }

}
array set PDC_TDES_att {
	RNCR 	{ R AT91C_TDES_RNCR 	RW }
	PTCR 	{ R AT91C_TDES_PTCR 	WO }
	TCR 	{ R AT91C_TDES_TCR 	RW }
	PTSR 	{ R AT91C_TDES_PTSR 	RO }
	TNPR 	{ R AT91C_TDES_TNPR 	RW }
	RCR 	{ R AT91C_TDES_RCR 	RW }
	RNPR 	{ R AT91C_TDES_RNPR 	RW }
	RPR 	{ R AT91C_TDES_RPR 	RW }
	TNCR 	{ R AT91C_TDES_TNCR 	RW }
	TPR 	{ R AT91C_TDES_TPR 	RW }
	listeReg 	{ RNCR PTCR TCR PTSR TNPR RCR RNPR RPR TNCR TPR  }

}
array set PDC_SHA_att {
	PTCR 	{ R AT91C_SHA_PTCR 	WO }
	TCR 	{ R AT91C_SHA_TCR 	RW }
	RPR 	{ R AT91C_SHA_RPR 	RW }
	TPR 	{ R AT91C_SHA_TPR 	RW }
	PTSR 	{ R AT91C_SHA_PTSR 	RO }
	RNCR 	{ R AT91C_SHA_RNCR 	RW }
	TNPR 	{ R AT91C_SHA_TNPR 	RW }
	RCR 	{ R AT91C_SHA_RCR 	RW }
	RNPR 	{ R AT91C_SHA_RNPR 	RW }
	TNCR 	{ R AT91C_SHA_TNCR 	RW }
	listeReg 	{ PTCR TCR RPR TPR PTSR RNCR TNPR RCR RNPR TNCR  }

}

# ========== Peripheral attributes for DBGU peripheral ========== 
array set DBGU_att {
	BRGR 	{ R AT91C_DBGU_BRGR 	RW }
	CR 	{ R AT91C_DBGU_CR 	WO }
	THR 	{ R AT91C_DBGU_THR 	WO }
	IDR 	{ R AT91C_DBGU_IDR 	WO }
	EXID 	{ R AT91C_DBGU_EXID 	RO }
	IMR 	{ R AT91C_DBGU_IMR 	RO }
	FNTR 	{ R AT91C_DBGU_FNTR 	RW }
	IER 	{ R AT91C_DBGU_IER 	WO }
	CSR 	{ R AT91C_DBGU_CSR 	RO }
	MR 	{ R AT91C_DBGU_MR 	RW }
	RHR 	{ R AT91C_DBGU_RHR 	RO }
	CIDR 	{ R AT91C_DBGU_CIDR 	RO }
	listeReg 	{ BRGR CR THR IDR EXID IMR FNTR IER CSR MR RHR CIDR  }

}

# ========== Peripheral attributes for MATRIX peripheral ========== 
array set MATRIX_att {
	SCFG1 	{ R AT91C_MATRIX_SCFG1 	RW }
	MRCR 	{ R AT91C_MATRIX_MRCR 	RW }
	PRAS2 	{ R AT91C_MATRIX_PRAS2 	RW }
	PRAS1 	{ R AT91C_MATRIX_PRAS1 	RW }
	PRAS0 	{ R AT91C_MATRIX_PRAS0 	RW }
	MCFG8 	{ R AT91C_MATRIX_MCFG8 	RW }
	MCFG2 	{ R AT91C_MATRIX_MCFG2 	RW }
	PRAS4 	{ R AT91C_MATRIX_PRAS4 	RW }
	MCFG3 	{ R AT91C_MATRIX_MCFG3 	RW }
	SCFG0 	{ R AT91C_MATRIX_SCFG0 	RW }
	MCFG7 	{ R AT91C_MATRIX_MCFG7 	RW }
	PRAS6 	{ R AT91C_MATRIX_PRAS6 	RW }
	SCFG7 	{ R AT91C_MATRIX_SCFG7 	RW }
	PRAS7 	{ R AT91C_MATRIX_PRAS7 	RW }
	SCFG2 	{ R AT91C_MATRIX_SCFG2 	RW }
	WRPROTST 	{ R AT91C_MATRIX_WRPROTST 	RO }
	PRBS0 	{ R AT91C_MATRIX_PRBS0 	RW }
	PRBS2 	{ R AT91C_MATRIX_PRBS2 	RW }
	MCFG4 	{ R AT91C_MATRIX_MCFG4 	RW }
	SCFG5 	{ R AT91C_MATRIX_SCFG5 	RW }
	PRBS6 	{ R AT91C_MATRIX_PRBS6 	RW }
	MCFG1 	{ R AT91C_MATRIX_MCFG1 	RW }
	SCFG6 	{ R AT91C_MATRIX_SCFG6 	RW }
	SCFG4 	{ R AT91C_MATRIX_SCFG4 	RW }
	PRBS1 	{ R AT91C_MATRIX_PRBS1 	RW }
	PRBS3 	{ R AT91C_MATRIX_PRBS3 	RW }
	WRPROTEN 	{ R AT91C_MATRIX_WRPROTEN 	RW }
	MCFG11 	{ R AT91C_MATRIX_MCFG11 	RW }
	MCFG0 	{ R AT91C_MATRIX_MCFG0 	RW }
	PRAS5 	{ R AT91C_MATRIX_PRAS5 	RW }
	PRBS4 	{ R AT91C_MATRIX_PRBS4 	RW }
	MCFG6 	{ R AT91C_MATRIX_MCFG6 	RW }
	PRBS5 	{ R AT91C_MATRIX_PRBS5 	RW }
	MCFG9 	{ R AT91C_MATRIX_MCFG9 	RW }
	MCFG5 	{ R AT91C_MATRIX_MCFG5 	RW }
	PRBS7 	{ R AT91C_MATRIX_PRBS7 	RW }
	MCFG10 	{ R AT91C_MATRIX_MCFG10 	RW }
	PRAS3 	{ R AT91C_MATRIX_PRAS3 	RW }
	SCFG3 	{ R AT91C_MATRIX_SCFG3 	RW }
	listeReg 	{ SCFG1 MRCR PRAS2 PRAS1 PRAS0 MCFG8 MCFG2 PRAS4 MCFG3 SCFG0 MCFG7 PRAS6 SCFG7 PRAS7 SCFG2 WRPROTST PRBS0 PRBS2 MCFG4 SCFG5 PRBS6 MCFG1 SCFG6 SCFG4 PRBS1 PRBS3 WRPROTEN MCFG11 MCFG0 PRAS5 PRBS4 MCFG6 PRBS5 MCFG9 MCFG5 PRBS7 MCFG10 PRAS3 SCFG3  }

}

# ========== Peripheral attributes for PMC peripheral ========== 
array set PMC_att {
	ADDRSIZE 	{ R AT91C_PMC_ADDRSIZE 	RO }
	PCER 	{ R AT91C_PMC_PCER 	WO }
	PCKR 	{ R AT91C_PMC_PCKR 	RW  2 }
	MCKR 	{ R AT91C_PMC_MCKR 	RW }
	PLLAR 	{ R AT91C_PMC_PLLAR 	RW }
	NAME2 	{ R AT91C_PMC_NAME2 	RO }
	PCDR 	{ R AT91C_PMC_PCDR 	WO }
	SCSR 	{ R AT91C_PMC_SCSR 	RO }
	MCFR 	{ R AT91C_PMC_MCFR 	RO }
	FEATURES 	{ R AT91C_PMC_FEATURES 	RO }
	PLLICPR 	{ R AT91C_PMC_PLLICPR 	RW }
	IMR 	{ R AT91C_PMC_IMR 	RO }
	IER 	{ R AT91C_PMC_IER 	WO }
	UCKR 	{ R AT91C_PMC_UCKR 	RW }
	USB 	{ R AT91C_PMC_USB 	RW }
	MOR 	{ R AT91C_PMC_MOR 	RW }
	IDR 	{ R AT91C_PMC_IDR 	WO }
	NAME1 	{ R AT91C_PMC_NAME1 	RO }
	SCDR 	{ R AT91C_PMC_SCDR 	WO }
	PCSR 	{ R AT91C_PMC_PCSR 	RO }
	SCER 	{ R AT91C_PMC_SCER 	WO }
	VERSION 	{ R AT91C_PMC_VERSION 	RO }
	SR 	{ R AT91C_PMC_SR 	RO }
	listeReg 	{ ADDRSIZE PCER PCKR MCKR PLLAR NAME2 PCDR SCSR MCFR FEATURES PLLICPR IMR IER UCKR USB MOR IDR NAME1 SCDR PCSR SCER VERSION SR  }

}

# ========== Peripheral attributes for MCI peripheral ========== 
array set MCI0_att {
	IMR 	{ R AT91C_MCI0_IMR 	RO }
	MR 	{ R AT91C_MCI0_MR 	RW }
	CR 	{ R AT91C_MCI0_CR 	WO }
	IER 	{ R AT91C_MCI0_IER 	WO }
	FIFO 	{ R AT91C_MCI0_FIFO 	R0 }
	DTOR 	{ R AT91C_MCI0_DTOR 	RW }
	SDCR 	{ R AT91C_MCI0_SDCR 	RW }
	BLKR 	{ R AT91C_MCI0_BLKR 	RW }
	VR 	{ R AT91C_MCI0_VR 	RO }
	WPSR 	{ R AT91C_MCI0_WPSR 	R0 }
	CMDR 	{ R AT91C_MCI0_CMDR 	WO }
	CSTOR 	{ R AT91C_MCI0_CSTOR 	RW }
	DMA 	{ R AT91C_MCI0_DMA 	RW }
	RDR 	{ R AT91C_MCI0_RDR 	RO }
	SR 	{ R AT91C_MCI0_SR 	RO }
	TDR 	{ R AT91C_MCI0_TDR 	RO }
	CFG 	{ R AT91C_MCI0_CFG 	RW }
	ARGR 	{ R AT91C_MCI0_ARGR 	RW }
	RSPR 	{ R AT91C_MCI0_RSPR 	RO  4 }
	WPCR 	{ R AT91C_MCI0_WPCR 	RW }
	IDR 	{ R AT91C_MCI0_IDR 	WO }
	listeReg 	{ IMR MR CR IER FIFO DTOR SDCR BLKR VR WPSR CMDR CSTOR DMA RDR SR TDR CFG ARGR RSPR WPCR IDR  }

}
array set MCI1_att {
	IDR 	{ R AT91C_MCI1_IDR 	WO }
	MR 	{ R AT91C_MCI1_MR 	RW }
	SR 	{ R AT91C_MCI1_SR 	RO }
	DTOR 	{ R AT91C_MCI1_DTOR 	RW }
	WPCR 	{ R AT91C_MCI1_WPCR 	RW }
	ARGR 	{ R AT91C_MCI1_ARGR 	RW }
	FIFO 	{ R AT91C_MCI1_FIFO 	R0 }
	IER 	{ R AT91C_MCI1_IER 	WO }
	SDCR 	{ R AT91C_MCI1_SDCR 	RW }
	CR 	{ R AT91C_MCI1_CR 	WO }
	CSTOR 	{ R AT91C_MCI1_CSTOR 	RW }
	RSPR 	{ R AT91C_MCI1_RSPR 	RO  4 }
	IMR 	{ R AT91C_MCI1_IMR 	RO }
	DMA 	{ R AT91C_MCI1_DMA 	RW }
	BLKR 	{ R AT91C_MCI1_BLKR 	RW }
	RDR 	{ R AT91C_MCI1_RDR 	RO }
	CFG 	{ R AT91C_MCI1_CFG 	RW }
	WPSR 	{ R AT91C_MCI1_WPSR 	R0 }
	CMDR 	{ R AT91C_MCI1_CMDR 	WO }
	TDR 	{ R AT91C_MCI1_TDR 	RO }
	VR 	{ R AT91C_MCI1_VR 	RO }
	listeReg 	{ IDR MR SR DTOR WPCR ARGR FIFO IER SDCR CR CSTOR RSPR IMR DMA BLKR RDR CFG WPSR CMDR TDR VR  }

}

# ========== Peripheral attributes for CCFG peripheral ========== 
array set CCFG_att {
	TCMR 	{ R AT91C_CCFG_TCMR 	RW }
	VIDEO 	{ R AT91C_CCFG_VIDEO 	RW }
	MATRIXVERSION 	{ R AT91C_CCFG_MATRIXVERSION 	RO }
	UDPHS 	{ R AT91C_CCFG_UDPHS 	RW }
	EBICSA 	{ R AT91C_CCFG_EBICSA 	RW }
	listeReg 	{ TCMR VIDEO MATRIXVERSION UDPHS EBICSA  }

}

# ========== Peripheral attributes for ISI peripheral ========== 
array set ISI_att {
	DMACHDR 	{ R AT91C_ISI_DMACHDR 	WO }
	IMR 	{ R AT91C_ISI_IMR 	RO }
	R2YSET1 	{ R AT91C_ISI_R2YSET1 	RW }
	PDECF 	{ R AT91C_ISI_PDECF 	RW }
	CFG2 	{ R AT91C_ISI_CFG2 	RW }
	DMACCTRL 	{ R AT91C_ISI_DMACCTRL 	RW }
	CTRL 	{ R AT91C_ISI_CTRL 	WO }
	Y2RSET0 	{ R AT91C_ISI_Y2RSET0 	RW }
	WPSR 	{ R AT91C_ISI_WPSR 	RO }
	DMACHER 	{ R AT91C_ISI_DMACHER 	WO }
	DMACHSR 	{ R AT91C_ISI_DMACHSR 	RO }
	IDR 	{ R AT91C_ISI_IDR 	WO }
	VER 	{ R AT91C_ISI_VER 	RO }
	Y2RSET1 	{ R AT91C_ISI_Y2RSET1 	RW }
	R2YSET2 	{ R AT91C_ISI_R2YSET2 	RW }
	SR 	{ R AT91C_ISI_SR 	RO }
	DMACDSCR 	{ R AT91C_ISI_DMACDSCR 	RW }
	IER 	{ R AT91C_ISI_IER 	WO }
	WPCR 	{ R AT91C_ISI_WPCR 	RW }
	DMACADDR 	{ R AT91C_ISI_DMACADDR 	RW }
	CFG1 	{ R AT91C_ISI_CFG1 	RW }
	R2YSET0 	{ R AT91C_ISI_R2YSET0 	RW }
	PSIZE 	{ R AT91C_ISI_PSIZE 	RW }
	DMAPDSCR 	{ R AT91C_ISI_DMAPDSCR 	RW }
	DMAPADDR 	{ R AT91C_ISI_DMAPADDR 	RW }
	DMAPCTRL 	{ R AT91C_ISI_DMAPCTRL 	RW }
	listeReg 	{ DMACHDR IMR R2YSET1 PDECF CFG2 DMACCTRL CTRL Y2RSET0 WPSR DMACHER DMACHSR IDR VER Y2RSET1 R2YSET2 SR DMACDSCR IER WPCR DMACADDR CFG1 R2YSET0 PSIZE DMAPDSCR DMAPADDR DMAPCTRL  }

}

# ========== Peripheral attributes for EBI peripheral ========== 
array set EBI_att {
	DUMMY 	{ R AT91C_EBI_DUMMY 	RW }
	listeReg 	{ DUMMY  }

}

# ========== Peripheral attributes for SHDWC peripheral ========== 
array set SHDWC_att {
	SHSR 	{ R AT91C_SHDWC_SHSR 	RO }
	SHMR 	{ R AT91C_SHDWC_SHMR 	RW }
	SHCR 	{ R AT91C_SHDWC_SHCR 	WO }
	listeReg 	{ SHSR SHMR SHCR  }

}

# ========== Peripheral attributes for PITC peripheral ========== 
array set PITC_att {
	PIVR 	{ R AT91C_PITC_PIVR 	RO }
	PISR 	{ R AT91C_PITC_PISR 	RO }
	PIIR 	{ R AT91C_PITC_PIIR 	RO }
	PIMR 	{ R AT91C_PITC_PIMR 	RW }
	listeReg 	{ PIVR PISR PIIR PIMR  }

}

# ========== Peripheral attributes for USART peripheral ========== 
array set US0_att {
	RTOR 	{ R AT91C_US0_RTOR 	RW }
	MAN 	{ R AT91C_US0_MAN 	RW }
	NER 	{ R AT91C_US0_NER 	RO }
	THR 	{ R AT91C_US0_THR 	WO }
	MR 	{ R AT91C_US0_MR 	RW }
	RHR 	{ R AT91C_US0_RHR 	RO }
	CSR 	{ R AT91C_US0_CSR 	RO }
	IMR 	{ R AT91C_US0_IMR 	RO }
	IDR 	{ R AT91C_US0_IDR 	WO }
	FIDI 	{ R AT91C_US0_FIDI 	RW }
	CR 	{ R AT91C_US0_CR 	WO }
	IER 	{ R AT91C_US0_IER 	WO }
	TTGR 	{ R AT91C_US0_TTGR 	RW }
	BRGR 	{ R AT91C_US0_BRGR 	RW }
	IF 	{ R AT91C_US0_IF 	RW }
	listeReg 	{ RTOR MAN NER THR MR RHR CSR IMR IDR FIDI CR IER TTGR BRGR IF  }

}
array set US1_att {
	NER 	{ R AT91C_US1_NER 	RO }
	RHR 	{ R AT91C_US1_RHR 	RO }
	RTOR 	{ R AT91C_US1_RTOR 	RW }
	IER 	{ R AT91C_US1_IER 	WO }
	IF 	{ R AT91C_US1_IF 	RW }
	MAN 	{ R AT91C_US1_MAN 	RW }
	CR 	{ R AT91C_US1_CR 	WO }
	IMR 	{ R AT91C_US1_IMR 	RO }
	TTGR 	{ R AT91C_US1_TTGR 	RW }
	MR 	{ R AT91C_US1_MR 	RW }
	IDR 	{ R AT91C_US1_IDR 	WO }
	FIDI 	{ R AT91C_US1_FIDI 	RW }
	CSR 	{ R AT91C_US1_CSR 	RO }
	THR 	{ R AT91C_US1_THR 	WO }
	BRGR 	{ R AT91C_US1_BRGR 	RW }
	listeReg 	{ NER RHR RTOR IER IF MAN CR IMR TTGR MR IDR FIDI CSR THR BRGR  }

}
array set US2_att {
	TTGR 	{ R AT91C_US2_TTGR 	RW }
	RHR 	{ R AT91C_US2_RHR 	RO }
	IMR 	{ R AT91C_US2_IMR 	RO }
	IER 	{ R AT91C_US2_IER 	WO }
	NER 	{ R AT91C_US2_NER 	RO }
	CR 	{ R AT91C_US2_CR 	WO }
	FIDI 	{ R AT91C_US2_FIDI 	RW }
	MR 	{ R AT91C_US2_MR 	RW }
	MAN 	{ R AT91C_US2_MAN 	RW }
	IDR 	{ R AT91C_US2_IDR 	WO }
	THR 	{ R AT91C_US2_THR 	WO }
	IF 	{ R AT91C_US2_IF 	RW }
	BRGR 	{ R AT91C_US2_BRGR 	RW }
	CSR 	{ R AT91C_US2_CSR 	RO }
	RTOR 	{ R AT91C_US2_RTOR 	RW }
	listeReg 	{ TTGR RHR IMR IER NER CR FIDI MR MAN IDR THR IF BRGR CSR RTOR  }

}
array set US3_att {
	CSR 	{ R AT91C_US3_CSR 	RO }
	BRGR 	{ R AT91C_US3_BRGR 	RW }
	TTGR 	{ R AT91C_US3_TTGR 	RW }
	IER 	{ R AT91C_US3_IER 	WO }
	RTOR 	{ R AT91C_US3_RTOR 	RW }
	MR 	{ R AT91C_US3_MR 	RW }
	IF 	{ R AT91C_US3_IF 	RW }
	MAN 	{ R AT91C_US3_MAN 	RW }
	NER 	{ R AT91C_US3_NER 	RO }
	FIDI 	{ R AT91C_US3_FIDI 	RW }
	CR 	{ R AT91C_US3_CR 	WO }
	IDR 	{ R AT91C_US3_IDR 	WO }
	IMR 	{ R AT91C_US3_IMR 	RO }
	THR 	{ R AT91C_US3_THR 	WO }
	RHR 	{ R AT91C_US3_RHR 	RO }
	listeReg 	{ CSR BRGR TTGR IER RTOR MR IF MAN NER FIDI CR IDR IMR THR RHR  }

}

# ========== Peripheral attributes for SPI peripheral ========== 
array set SPI0_att {
	MR 	{ R AT91C_SPI0_MR 	RW }
	RDR 	{ R AT91C_SPI0_RDR 	RO }
	CR 	{ R AT91C_SPI0_CR 	RO }
	IER 	{ R AT91C_SPI0_IER 	WO }
	TDR 	{ R AT91C_SPI0_TDR 	WO }
	IDR 	{ R AT91C_SPI0_IDR 	WO }
	CSR 	{ R AT91C_SPI0_CSR 	RW  4 }
	SR 	{ R AT91C_SPI0_SR 	RO }
	IMR 	{ R AT91C_SPI0_IMR 	RO }
	listeReg 	{ MR RDR CR IER TDR IDR CSR SR IMR  }

}
array set SPI1_att {
	CSR 	{ R AT91C_SPI1_CSR 	RW  4 }
	IER 	{ R AT91C_SPI1_IER 	WO }
	RDR 	{ R AT91C_SPI1_RDR 	RO }
	IDR 	{ R AT91C_SPI1_IDR 	WO }
	MR 	{ R AT91C_SPI1_MR 	RW }
	CR 	{ R AT91C_SPI1_CR 	RO }
	SR 	{ R AT91C_SPI1_SR 	RO }
	TDR 	{ R AT91C_SPI1_TDR 	WO }
	IMR 	{ R AT91C_SPI1_IMR 	RO }
	listeReg 	{ CSR IER RDR IDR MR CR SR TDR IMR  }

}

# ========== Peripheral attributes for TCB peripheral ========== 
array set TCB0_att {
	BCR 	{ R AT91C_TCB0_BCR 	WO }
	BMR 	{ R AT91C_TCB0_BMR 	RW }
	listeReg 	{ BCR BMR  }

}
array set TCB1_att {
	BMR 	{ R AT91C_TCB1_BMR 	RW }
	BCR 	{ R AT91C_TCB1_BCR 	WO }
	listeReg 	{ BMR BCR  }

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

# ========== Peripheral attributes for UDPHS_EPT peripheral ========== 
array set UDPHS_EPT_0_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_0_EPTSTA 	RO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_0_EPTCTL 	RO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_0_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_0_EPTCFG 	RW }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_0_EPTCLRSTA 	WO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_0_EPTSETSTA 	WO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_0_EPTCTLENB 	WO }
	listeReg 	{ EPTSTA EPTCTL EPTCTLDIS EPTCFG EPTCLRSTA EPTSETSTA EPTCTLENB  }

}
array set UDPHS_EPT_1_att {
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_1_EPTCTLENB 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_1_EPTCFG 	RW }
	EPTCTL 	{ R AT91C_UDPHS_EPT_1_EPTCTL 	RO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_1_EPTSTA 	RO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_1_EPTCLRSTA 	WO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_1_EPTSETSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_1_EPTCTLDIS 	WO }
	listeReg 	{ EPTCTLENB EPTCFG EPTCTL EPTSTA EPTCLRSTA EPTSETSTA EPTCTLDIS  }

}
array set UDPHS_EPT_2_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_2_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_2_EPTCTLDIS 	WO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_2_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_2_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_2_EPTCTL 	RO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_2_EPTCFG 	RW }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_2_EPTCTLENB 	WO }
	listeReg 	{ EPTCLRSTA EPTCTLDIS EPTSTA EPTSETSTA EPTCTL EPTCFG EPTCTLENB  }

}
array set UDPHS_EPT_3_att {
	EPTCTL 	{ R AT91C_UDPHS_EPT_3_EPTCTL 	RO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_3_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_3_EPTCTLDIS 	WO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_3_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_3_EPTSETSTA 	WO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_3_EPTCTLENB 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_3_EPTCFG 	RW }
	listeReg 	{ EPTCTL EPTCLRSTA EPTCTLDIS EPTSTA EPTSETSTA EPTCTLENB EPTCFG  }

}
array set UDPHS_EPT_4_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_4_EPTCLRSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_4_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_4_EPTCTLENB 	WO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_4_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_4_EPTSETSTA 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_4_EPTCFG 	RW }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_4_EPTCTLDIS 	WO }
	listeReg 	{ EPTCLRSTA EPTCTL EPTCTLENB EPTSTA EPTSETSTA EPTCFG EPTCTLDIS  }

}
array set UDPHS_EPT_5_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_5_EPTSTA 	RO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_5_EPTCLRSTA 	WO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_5_EPTCTLENB 	WO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_5_EPTSETSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_5_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_5_EPTCFG 	RW }
	EPTCTL 	{ R AT91C_UDPHS_EPT_5_EPTCTL 	RO }
	listeReg 	{ EPTSTA EPTCLRSTA EPTCTLENB EPTSETSTA EPTCTLDIS EPTCFG EPTCTL  }

}
array set UDPHS_EPT_6_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_6_EPTCLRSTA 	WO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_6_EPTCTLENB 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_6_EPTCTL 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_6_EPTSETSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_6_EPTCTLDIS 	WO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_6_EPTSTA 	RO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_6_EPTCFG 	RW }
	listeReg 	{ EPTCLRSTA EPTCTLENB EPTCTL EPTSETSTA EPTCTLDIS EPTSTA EPTCFG  }

}

# ========== Peripheral attributes for AC97C peripheral ========== 
array set AC97C_att {
	IER 	{ R AT91C_AC97C_IER 	WO }
	COTHR 	{ R AT91C_AC97C_COTHR 	WO }
	IDR 	{ R AT91C_AC97C_IDR 	WO }
	ICA 	{ R AT91C_AC97C_ICA 	RW }
	CATHR 	{ R AT91C_AC97C_CATHR 	WO }
	CBSR 	{ R AT91C_AC97C_CBSR 	RO }
	CAMR 	{ R AT91C_AC97C_CAMR 	RW }
	SR 	{ R AT91C_AC97C_SR 	RO }
	CBTHR 	{ R AT91C_AC97C_CBTHR 	WO }
	CASR 	{ R AT91C_AC97C_CASR 	RO }
	COSR 	{ R AT91C_AC97C_COSR 	RO }
	MR 	{ R AT91C_AC97C_MR 	RW }
	OCA 	{ R AT91C_AC97C_OCA 	RW }
	CORHR 	{ R AT91C_AC97C_CORHR 	RO }
	CBRHR 	{ R AT91C_AC97C_CBRHR 	RO }
	IMR 	{ R AT91C_AC97C_IMR 	RO }
	COMR 	{ R AT91C_AC97C_COMR 	RW }
	CARHR 	{ R AT91C_AC97C_CARHR 	RO }
	VERSION 	{ R AT91C_AC97C_VERSION 	RO }
	CBMR 	{ R AT91C_AC97C_CBMR 	RW }
	listeReg 	{ IER COTHR IDR ICA CATHR CBSR CAMR SR CBTHR CASR COSR MR OCA CORHR CBRHR IMR COMR CARHR VERSION CBMR  }

}

# ========== Peripheral attributes for PWMC_CH peripheral ========== 
array set PWMC_CH0_att {
	CCNTR 	{ R AT91C_PWMC_CH0_CCNTR 	RO }
	CPRDR 	{ R AT91C_PWMC_CH0_CPRDR 	RW }
	CUPDR 	{ R AT91C_PWMC_CH0_CUPDR 	WO }
	CDTYR 	{ R AT91C_PWMC_CH0_CDTYR 	RW }
	CMR 	{ R AT91C_PWMC_CH0_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH0_Reserved 	WO  3 }
	listeReg 	{ CCNTR CPRDR CUPDR CDTYR CMR Reserved  }

}
array set PWMC_CH1_att {
	CCNTR 	{ R AT91C_PWMC_CH1_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH1_CDTYR 	RW }
	CMR 	{ R AT91C_PWMC_CH1_CMR 	RW }
	CPRDR 	{ R AT91C_PWMC_CH1_CPRDR 	RW }
	Reserved 	{ R AT91C_PWMC_CH1_Reserved 	WO  3 }
	CUPDR 	{ R AT91C_PWMC_CH1_CUPDR 	WO }
	listeReg 	{ CCNTR CDTYR CMR CPRDR Reserved CUPDR  }

}
array set PWMC_CH2_att {
	CUPDR 	{ R AT91C_PWMC_CH2_CUPDR 	WO }
	CMR 	{ R AT91C_PWMC_CH2_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH2_Reserved 	WO  3 }
	CPRDR 	{ R AT91C_PWMC_CH2_CPRDR 	RW }
	CDTYR 	{ R AT91C_PWMC_CH2_CDTYR 	RW }
	CCNTR 	{ R AT91C_PWMC_CH2_CCNTR 	RO }
	listeReg 	{ CUPDR CMR Reserved CPRDR CDTYR CCNTR  }

}
array set PWMC_CH3_att {
	CPRDR 	{ R AT91C_PWMC_CH3_CPRDR 	RW }
	Reserved 	{ R AT91C_PWMC_CH3_Reserved 	WO  3 }
	CUPDR 	{ R AT91C_PWMC_CH3_CUPDR 	WO }
	CDTYR 	{ R AT91C_PWMC_CH3_CDTYR 	RW }
	CCNTR 	{ R AT91C_PWMC_CH3_CCNTR 	RO }
	CMR 	{ R AT91C_PWMC_CH3_CMR 	RW }
	listeReg 	{ CPRDR Reserved CUPDR CDTYR CCNTR CMR  }

}

# ========== Peripheral attributes for UDPHS_EPTFIFO peripheral ========== 
array set UDPHS_EPTFIFO_att {
	READEPT3 	{ R AT91C_UDPHS_EPTFIFO_READEPT3 	RW 16384 }
	READEPT5 	{ R AT91C_UDPHS_EPTFIFO_READEPT5 	RW 16384 }
	READEPT1 	{ R AT91C_UDPHS_EPTFIFO_READEPT1 	RW 16384 }
	READEPT0 	{ R AT91C_UDPHS_EPTFIFO_READEPT0 	RW 16384 }
	READEPT6 	{ R AT91C_UDPHS_EPTFIFO_READEPT6 	RW 16384 }
	READEPT2 	{ R AT91C_UDPHS_EPTFIFO_READEPT2 	RW 16384 }
	READEPT4 	{ R AT91C_UDPHS_EPTFIFO_READEPT4 	RW 16384 }
	listeReg 	{ READEPT3 READEPT5 READEPT1 READEPT0 READEPT6 READEPT2 READEPT4  }

}

# ========== Peripheral attributes for EMAC peripheral ========== 
array set EMACB_att {
	ALE 	{ R AT91C_EMACB_ALE 	RW }
	RRE 	{ R AT91C_EMACB_RRE 	RW }
	SA4H 	{ R AT91C_EMACB_SA4H 	RW }
	TPQ 	{ R AT91C_EMACB_TPQ 	RW }
	RJA 	{ R AT91C_EMACB_RJA 	RW }
	SA2H 	{ R AT91C_EMACB_SA2H 	RW }
	TPF 	{ R AT91C_EMACB_TPF 	RW }
	ROV 	{ R AT91C_EMACB_ROV 	RW }
	SA4L 	{ R AT91C_EMACB_SA4L 	RW }
	MAN 	{ R AT91C_EMACB_MAN 	RW }
	TID 	{ R AT91C_EMACB_TID 	RW }
	TBQP 	{ R AT91C_EMACB_TBQP 	RW }
	SA3L 	{ R AT91C_EMACB_SA3L 	RW }
	DTF 	{ R AT91C_EMACB_DTF 	RW }
	PTR 	{ R AT91C_EMACB_PTR 	RW }
	CSE 	{ R AT91C_EMACB_CSE 	RW }
	ECOL 	{ R AT91C_EMACB_ECOL 	RW }
	STE 	{ R AT91C_EMACB_STE 	RW }
	MCF 	{ R AT91C_EMACB_MCF 	RW }
	IER 	{ R AT91C_EMACB_IER 	WO }
	ELE 	{ R AT91C_EMACB_ELE 	RW }
	USRIO 	{ R AT91C_EMACB_USRIO 	RW }
	PFR 	{ R AT91C_EMACB_PFR 	RW }
	FCSE 	{ R AT91C_EMACB_FCSE 	RW }
	SA1L 	{ R AT91C_EMACB_SA1L 	RW }
	NCR 	{ R AT91C_EMACB_NCR 	RW }
	HRT 	{ R AT91C_EMACB_HRT 	RW }
	NCFGR 	{ R AT91C_EMACB_NCFGR 	RW }
	SCF 	{ R AT91C_EMACB_SCF 	RW }
	LCOL 	{ R AT91C_EMACB_LCOL 	RW }
	SA3H 	{ R AT91C_EMACB_SA3H 	RW }
	HRB 	{ R AT91C_EMACB_HRB 	RW }
	ISR 	{ R AT91C_EMACB_ISR 	RW }
	IMR 	{ R AT91C_EMACB_IMR 	RO }
	WOL 	{ R AT91C_EMACB_WOL 	RW }
	USF 	{ R AT91C_EMACB_USF 	RW }
	TSR 	{ R AT91C_EMACB_TSR 	RW }
	FRO 	{ R AT91C_EMACB_FRO 	RW }
	IDR 	{ R AT91C_EMACB_IDR 	WO }
	SA1H 	{ R AT91C_EMACB_SA1H 	RW }
	RLE 	{ R AT91C_EMACB_RLE 	RW }
	TUND 	{ R AT91C_EMACB_TUND 	RW }
	RSR 	{ R AT91C_EMACB_RSR 	RW }
	SA2L 	{ R AT91C_EMACB_SA2L 	RW }
	FTO 	{ R AT91C_EMACB_FTO 	RW }
	RSE 	{ R AT91C_EMACB_RSE 	RW }
	NSR 	{ R AT91C_EMACB_NSR 	RO }
	RBQP 	{ R AT91C_EMACB_RBQP 	RW }
	REV 	{ R AT91C_EMACB_REV 	RO }
	listeReg 	{ ALE RRE SA4H TPQ RJA SA2H TPF ROV SA4L MAN TID TBQP SA3L DTF PTR CSE ECOL STE MCF IER ELE USRIO PFR FCSE SA1L NCR HRT NCFGR SCF LCOL SA3H HRB ISR IMR WOL USF TSR FRO IDR SA1H RLE TUND RSR SA2L FTO RSE NSR RBQP REV  }

}

# ========== Peripheral attributes for ECC peripheral ========== 
array set HECC_att {
	VR 	{ R AT91C_HECC_VR 	RO }
	SR 	{ R AT91C_HECC_SR 	RO }
	CR 	{ R AT91C_HECC_CR 	WO }
	NPR 	{ R AT91C_HECC_NPR 	RO }
	PR 	{ R AT91C_HECC_PR 	RO }
	MR 	{ R AT91C_HECC_MR 	RW }
	listeReg 	{ VR SR CR NPR PR MR  }

}

# ========== Peripheral attributes for UDPHS peripheral ========== 
array set UDPHS_att {
	IEN 	{ R AT91C_UDPHS_IEN 	RW }
	TSTSOFCNT 	{ R AT91C_UDPHS_TSTSOFCNT 	RW }
	IPFEATURES 	{ R AT91C_UDPHS_IPFEATURES 	RO }
	TST 	{ R AT91C_UDPHS_TST 	RW }
	FNUM 	{ R AT91C_UDPHS_FNUM 	RO }
	TSTCNTB 	{ R AT91C_UDPHS_TSTCNTB 	RW }
	RIPPADDRSIZE 	{ R AT91C_UDPHS_RIPPADDRSIZE 	RO }
	INTSTA 	{ R AT91C_UDPHS_INTSTA 	RO }
	EPTRST 	{ R AT91C_UDPHS_EPTRST 	WO }
	TSTCNTA 	{ R AT91C_UDPHS_TSTCNTA 	RW }
	RIPNAME2 	{ R AT91C_UDPHS_RIPNAME2 	RO }
	RIPNAME1 	{ R AT91C_UDPHS_RIPNAME1 	RO }
	TSTMODREG 	{ R AT91C_UDPHS_TSTMODREG 	RW }
	CLRINT 	{ R AT91C_UDPHS_CLRINT 	WO }
	IPVERSION 	{ R AT91C_UDPHS_IPVERSION 	RO }
	CTRL 	{ R AT91C_UDPHS_CTRL 	RW }
	listeReg 	{ IEN TSTSOFCNT IPFEATURES TST FNUM TSTCNTB RIPPADDRSIZE INTSTA EPTRST TSTCNTA RIPNAME2 RIPNAME1 TSTMODREG CLRINT IPVERSION CTRL  }

}

# ========== PIO information ========== 

array set def_PIOA_att {
 	PA0 	{  MCI0_CK   TCLK3  }
 	PA1 	{  MCI0_CDA   TIOA3  }
 	PA10 	{  ETX0  }
 	PA11 	{  ETX1  }
 	PA12 	{  ERX0  }
 	PA13 	{  ERX1  }
 	PA14 	{  ETXEN  }
 	PA15 	{  ERXDV  }
 	PA16 	{  ERXER  }
 	PA17 	{  ETXCK_EREFCK  }
 	PA18 	{  EMDC  }
 	PA19 	{  EMDIO  }
 	PA2 	{  MCI0_DA0   TIOB3  }
 	PA20 	{  TWD0  }
 	PA21 	{  TWCK0  }
 	PA22 	{  MCI1_CDA   SCK3  }
 	PA23 	{  MCI1_DA0   RTS3  }
 	PA24 	{  MCI1_DA1   CTS3  }
 	PA25 	{  MCI1_DA2   PWM3  }
 	PA26 	{  MCI1_DA3   TIOB2  }
 	PA27 	{  MCI1_DA4   ETXER  }
 	PA28 	{  MCI1_DA5   ERXCK  }
 	PA29 	{  MCI1_DA6   ECRS  }
 	PA3 	{  MCI0_DA1   TCLK4  }
 	PA30 	{  MCI1_DA7   ECOL  }
 	PA31 	{  MCI1_CK   PCK0  }
 	PA4 	{  MCI0_DA2   TIOA4  }
 	PA5 	{  MCI0_DA3   TIOB4  }
 	PA6 	{  MCI0_DA4   ETX2  }
 	PA7 	{  MCI0_DA5   ETX3  }
 	PA8 	{  MCI0_DA6   ERX2  }
 	PA9 	{  MCI0_DA7   ERX3  }
 }

array set def_PIOB_att {
 	PB0 	{  SPI0_MISO  }
 	PB1 	{  SPI0_MOSI  }
 	PB10 	{  TWD1   ISI_D10  }
 	PB11 	{  TWCK1   ISI_D11  }
 	PB12 	{  DRXD  }
 	PB13 	{  DTXD  }
 	PB14 	{  SPI1_MISO  }
 	PB15 	{  SPI1_MOSI   CTS0  }
 	PB16 	{  SPI1_SPCK   SCK0  }
 	PB17 	{  SPI1_NPCS0   RTS0  }
 	PB18 	{  RXD0   SPI0_NPCS1  }
 	PB19 	{  TXD0   SPI0_NPCS2  }
 	PB2 	{  SPI0_SPCK  }
 	PB20 	{  ISI_D0  }
 	PB21 	{  ISI_D1  }
 	PB22 	{  ISI_D2  }
 	PB23 	{  ISI_D3  }
 	PB24 	{  ISI_D4  }
 	PB25 	{  ISI_D5  }
 	PB26 	{  ISI_D6  }
 	PB27 	{  ISI_D7  }
 	PB28 	{  ISI_PCK  }
 	PB29 	{  ISI_VSYNC  }
 	PB3 	{  SPI0_NPCS0  }
 	PB30 	{  ISI_HSYNC  }
 	PB31 	{  XXXXXX   PCK1  }
 	PB4 	{  TXD1  }
 	PB5 	{  RXD1  }
 	PB6 	{  TXD2  }
 	PB7 	{  RXD2  }
 	PB8 	{  TXD3   ISI_D8  }
 	PB9 	{  RXD3   ISI_D9  }
 }

array set def_PIOC_att {
 	PC0 	{  DQM2  }
 	PC1 	{  DQM3  }
 	PC10 	{  NCS4_CFCS0   TCLK2  }
 	PC11 	{  NCS5_CFCS1   CTS2  }
 	PC12 	{  A25_CFRNW  }
 	PC13 	{  NCS2  }
 	PC14 	{  NCS3_NANDCS  }
 	PC15 	{  NWAIT  }
 	PC16 	{  D16  }
 	PC17 	{  D17  }
 	PC18 	{  D18  }
 	PC19 	{  D19  }
 	PC2 	{  A19  }
 	PC20 	{  D20  }
 	PC21 	{  D21  }
 	PC22 	{  D22  }
 	PC23 	{  D23  }
 	PC24 	{  D24  }
 	PC25 	{  D25  }
 	PC26 	{  D26  }
 	PC27 	{  D27  }
 	PC28 	{  D28  }
 	PC29 	{  D29  }
 	PC3 	{  A20  }
 	PC30 	{  D30  }
 	PC31 	{  D31  }
 	PC4 	{  A21_NANDALE  }
 	PC5 	{  A22_NANDCLE  }
 	PC6 	{  A23  }
 	PC7 	{  A24  }
 	PC8 	{  CFCE1  }
 	PC9 	{  CFCE2   RTS2  }
 }

array set def_PIOD_att {
 	PD0 	{  TK0   PWM3  }
 	PD1 	{  TF0  }
 	PD10 	{  TD1  }
 	PD11 	{  RD1  }
 	PD12 	{  TK1   PCK0  }
 	PD13 	{  RK1  }
 	PD14 	{  TF1  }
 	PD15 	{  RF1  }
 	PD16 	{  RTS1  }
 	PD17 	{  CTS1  }
 	PD18 	{  SPI1_NPCS2   IRQ  }
 	PD19 	{  SPI1_NPCS3   FIQ  }
 	PD2 	{  TD0  }
 	PD20 	{  TIOA0  }
 	PD21 	{  TIOA1  }
 	PD22 	{  TIOA2  }
 	PD23 	{  TCLK0  }
 	PD24 	{  SPI0_NPCS1   PWM0  }
 	PD25 	{  SPI0_NPCS2   PWM1  }
 	PD26 	{  PCK0   PWM2  }
 	PD27 	{  PCK1   SPI0_NPCS3  }
 	PD28 	{  TSADTRG   SPI1_NPCS1  }
 	PD29 	{  TCLK1   SCK1  }
 	PD3 	{  RD0  }
 	PD30 	{  TIOB0   SCK2  }
 	PD31 	{  TIOB1   PWM1  }
 	PD4 	{  RK0  }
 	PD5 	{  RF0  }
 	PD6 	{  AC97RX  }
 	PD7 	{  AC97TX   TIOA5  }
 	PD8 	{  AC97FS   TIOB5  }
 	PD9 	{  AC97CK   TCLK5  }
 }

array set def_PIOE_att {
 	PE0 	{  LCDPWR   PCK0  }
 	PE1 	{  LCDMOD  }
 	PE10 	{  LCDD3   LCDD5  }
 	PE11 	{  LCDD4   LCDD6  }
 	PE12 	{  LCDD5   LCDD7  }
 	PE13 	{  LCDD6   LCDD10  }
 	PE14 	{  LCDD7   LCDD11  }
 	PE15 	{  LCDD8   LCDD12  }
 	PE16 	{  LCDD9   LCDD13  }
 	PE17 	{  LCDD10   LCDD14  }
 	PE18 	{  LCDD11   LCDD15  }
 	PE19 	{  LCDD12   LCDD18  }
 	PE2 	{  LCDCC  }
 	PE20 	{  LCDD13   LCDD19  }
 	PE21 	{  LCDD14   LCDD20  }
 	PE22 	{  LCDD15   LCDD21  }
 	PE23 	{  LCDD16   LCDD22  }
 	PE24 	{  LCDD17   LCDD23  }
 	PE25 	{  LCDD18  }
 	PE26 	{  LCDD19  }
 	PE27 	{  LCDD20  }
 	PE28 	{  LCDD21  }
 	PE29 	{  LCDD22  }
 	PE3 	{  LCDVSYNC  }
 	PE30 	{  LCDD23  }
 	PE31 	{  PWM2   PCK1  }
 	PE4 	{  LCDHSYNC  }
 	PE5 	{  LCDDOTCK  }
 	PE6 	{  LCDDEN  }
 	PE7 	{  LCDD0   LCDD2  }
 	PE8 	{  LCDD1   LCDD3  }
 	PE9 	{  LCDD2   LCDD4  }
 }

# *****************************************************************************
#               IP PIN DEFINITIONS FOR AT91SAM9264
# *****************************************************************************

# table definition: portname direction is_a_pio is_open_drain

array set def_design_att {
  NAND {
    D[0] {d[0] inout 0 0}
    D[1] {d[1] inout 0 0}
    D[2] {d[2] inout 0 0}
    D[3] {d[3] inout 0 0}
    D[4] {d[4] inout 0 0}
    D[5] {d[5] inout 0 0}
    D[6] {d[6] inout 0 0}
    D[7] {d[7] inout 0 0}
    D[8] {d[8] inout 0 0}
    D[9] {d[9] inout 0 0}
    D[10] {d[10] inout 0 0}
    D[11] {d[11] inout 0 0}
    D[12] {d[12] inout 0 0}
    D[13] {d[13] inout 0 0}
    D[14] {d[14] inout 0 0}
    D[15] {d[15] inout 0 0}
    NANDCLE {a22_nandcle output 1 0}
    NANDALE {a21_nandale output 1 0}
    NANDWE {nandwe output 1 0}
    NANDOE {nandoe output 1 0}
    NANDCS {ncs3_nandcs output 1 0}
  }
  SDRAM {
    A[2] {a[2] output 0 0}
    A[3] {a[3] output 0 0}
    A[4] {a[4] output 0 0}
    A[5] {a[5] output 0 0}
    A[6] {a[6] output 0 0}
    A[7] {a[7] output 0 0}
    A[8] {a[8] output 0 0}
    A[9] {a[9] output 0 0}
    A[10] {a[10] output 0 0}
    A[11] {a[11] output 0 0}
    A[12] {a[12] output 0 0}
    A[13] {a[13] output 0 0}
    A[14] {a[14] output 0 0}
    SDA10 {sda10 output 0 0}
    BA0 {a[16] output 0 0}
    BA1 {a[17] output 0 0}
    SDCK {sdck output 0 0}
    SDCKE {sdcke output 0 0}
    SDCS {ncs1_sdcs output 0 0}
    RAS {ras output 0 0}
    CAS {cas output 0 0}
    SDWE {sdwe output 0 0}
    DQM0 {a[0] output 0 0}
    DQM1 {nwr1_nbs1_cfior output 0 0}
    DQM2 {a[1] output 0 0}
    DQM3 {nwr3_nbs3_cfiow output 0 0}
    D[0] {d[0] inout 0 0}
    D[1] {d[1] inout 0 0}
    D[2] {d[2] inout 0 0}
    D[3] {d[3] inout 0 0}
    D[4] {d[4] inout 0 0}
    D[5] {d[5] inout 0 0}
    D[6] {d[6] inout 0 0}
    D[7] {d[7] inout 0 0}
    D[8] {d[8] inout 0 0}
    D[9] {d[9] inout 0 0}
    D[10] {d[10] inout 0 0}
    D[11] {d[11] inout 0 0}
    D[12] {d[12] inout 0 0}
    D[13] {d[13] inout 0 0}
    D[14] {d[14] inout 0 0}
    D[15] {d[15] inout 0 0}
    D[16] {d[16] inout 1 0}
    D[17] {d[17] inout 1 0}
    D[18] {d[18] inout 1 0}
    D[19] {d[19] inout 1 0}
    D[20] {d[20] inout 1 0}
    D[21] {d[21] inout 1 0}
    D[22] {d[22] inout 1 0}
    D[23] {d[23] inout 1 0}
    D[24] {d[24] inout 1 0}
    D[25] {d[25] inout 1 0}
    D[26] {d[26] inout 1 0}
    D[27] {d[27] inout 1 0}
    D[28] {d[28] inout 1 0}
    D[29] {d[29] inout 1 0}
    D[30] {d[30] inout 1 0}
    D[31] {d[31] inout 1 0}
  }
  SRAM {
    A[0] {ebi_a[0] output 0 0}
    A[1] {ebi_a[1] output 0 0}
    A[2] {ebi_a[2] output 0 0}
    A[3] {ebi_a[3] output 0 0}
    A[4] {ebi_a[4] output 0 0}
    A[5] {ebi_a[5] output 0 0}
    A[6] {ebi_a[6] output 0 0}
    A[7] {ebi_a[7] output 0 0}
    A[8] {ebi_a[8] output 0 0}
    A[9] {ebi_a[9] output 0 0}
    A[10] {ebi_a[10] output 0 0}
    A[11] {ebi_a[11] output 0 0}
    A[12] {ebi_a[12] output 0 0}
    A[13] {ebi_a[13] output 0 0}
    A[14] {ebi_a[14] output 0 0}
    A[15] {ebi_a[15] output 0 0}
    A[16] {ebi_a[16] output 0 0}
    A[17] {ebi_a[17] output 0 0}
    A[18] {ebi_a[18] output 0 0}
    A[19] {a19 output 1 0}
    A[20] {a20 output 1 0}
    A[21] {a21_nandale output 1 0}
    A[22] {a22_nandcle output 1 0}
    A[23] {a23 output 1 0}
    A[24] {a24 output 1 0}
    A[25] {a25_cfrnw output 1 0}
    D[0] {ebi_d[0] inout 0 0}
    D[1] {ebi_d[1] inout 0 0}
    D[2] {ebi_d[2] inout 0 0}
    D[3] {ebi_d[3] inout 0 0}
    D[4] {ebi_d[4] inout 0 0}
    D[5] {ebi_d[5] inout 0 0}
    D[6] {ebi_d[6] inout 0 0}
    D[7] {ebi_d[7] inout 0 0}
    D[8] {ebi_d[8] inout 0 0}
    D[9] {ebi_d[9] inout 0 0}
    D[10] {ebi_d[10] inout 0 0}
    D[11] {ebi_d[11] inout 0 0}
    D[12] {ebi_d[12] inout 0 0}
    D[13] {ebi_d[13] inout 0 0}
    D[14] {ebi_d[14] inout 0 0}
    D[15] {ebi_d[15] inout 0 0}
    D[16] {d[16] inout 1 0}
    D[17] {d[17] inout 1 0}
    D[18] {d[18] inout 1 0}
    D[19] {d[19] inout 1 0}
    D[20] {d[20] inout 1 0}
    D[21] {d[21] inout 1 0}
    D[22] {d[22] inout 1 0}
    D[23] {d[23] inout 1 0}
    D[24] {d[24] inout 1 0}
    D[25] {d[25] inout 1 0}
    D[26] {d[26] inout 1 0}
    D[27] {d[27] inout 1 0}
    D[28] {d[28] inout 1 0}
    D[29] {d[29] inout 1 0}
    D[30] {d[30] inout 1 0}
    D[31] {d[31] inout 1 0}
    NCS0 {ebi_ncs0 output 0 0}
    NCS1 {ebi_ncs1_sdcs output 0 0}
    NCS2 {ncs2 output 1 0}
    NCS3 {ncs3_nandcs output 1 0}
    NCS4 {ncs4_cfcs0 output 1 0}
    NCS5 {ncs5_cfcs1 output 1 0}
    NWR0 {ebi_nwr0_nwe_cfwe output 0 0}
    NWR1 {ebi_nwr1_nbs1_cfior output 0 0}
    NWR2 {ebi_a[1] output 0 0}
    NWR3 {ebi_nwr3_nbs3_cfiow output 0 0}
    NRD {ebi_nrd_cfoe output 0 0}
    NWE {ebi_nwr0_nwe_cfwe output 0 0}
    NBS0 {ebi_a[0] output 0 0}
    NBS1 {ebi_nwr1_nbs1_cfior output 0 0}
    NBS2 {ebi_a[1] output 0 0}
    NBS3 {ebi_nwr3_nbs3_cfiow output 0 0}
  }
}
