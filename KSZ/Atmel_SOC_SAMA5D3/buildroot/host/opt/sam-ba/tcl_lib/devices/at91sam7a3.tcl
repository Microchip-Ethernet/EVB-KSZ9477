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
# File Name           : AT91SAM7A3.tcl
# Object              : AT91SAM7A3 definitions
# Generated           : AT91 SW Application Group  01/16/2006 (16:35:50)
# 
# CVS Reference       : /AT91SAM7A3.pl/1.29/Fri Nov 18 12:43:45 2005//
# CVS Reference       : /SYS_SAM7A3.pl/1.7/Thu Feb  3 17:18:25 2005//
# CVS Reference       : /MC_SAM7A3.pl/1.3/Fri Sep 23 08:43:52 2005//
# CVS Reference       : /PMC_SAM7A3.pl/1.2/Tue Feb  8 13:58:44 2005//
# CVS Reference       : /RSTC_SAM7A3.pl/1.2/Wed Jul 13 14:57:29 2005//
# CVS Reference       : /SHDWC_SAM7A3.pl/1.1/Thu Feb  3 16:25:23 2005//
# CVS Reference       : /UDP_SAM7A3.pl/1.1/Tue May 10 09:41:20 2005//
# CVS Reference       : /PWM_SAM7A3.pl/1.1/Tue May 10 12:00:26 2005//
# CVS Reference       : /AIC_6075B.pl/1.3/Fri May 20 14:01:30 2005//
# CVS Reference       : /PIO_6057A.pl/1.2/Thu Feb  3 10:18:28 2005//
# CVS Reference       : /RTTC_6081A.pl/1.2/Tue Nov  9 14:43:58 2004//
# CVS Reference       : /PITC_6079A.pl/1.2/Tue Nov  9 14:43:56 2004//
# CVS Reference       : /WDTC_6080A.pl/1.3/Tue Nov  9 14:44:00 2004//
# CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb  3 08:48:54 2005//
# CVS Reference       : /DBGU_6059D.pl/1.1/Mon Jan 31 13:15:32 2005//
# CVS Reference       : /SPI_6088D.pl/1.3/Fri May 20 14:08:59 2005//
# CVS Reference       : /US_6089C.pl/1.1/Mon Jul 12 18:23:26 2004//
# CVS Reference       : /SSC_6078A.pl/1.1/Tue Jul 13 07:45:40 2004//
# CVS Reference       : /TWI_6061A.pl/1.1/Tue Jul 13 07:38:06 2004//
# CVS Reference       : /TC_6082A.pl/1.7/Fri Mar 11 12:52:17 2005//
# CVS Reference       : /CAN_6019B.pl/1.1/Tue Mar  8 12:42:22 2005//
# CVS Reference       : /MCI_6101A.pl/1.1/Tue May 18 13:48:46 2004//
# CVS Reference       : /ADC_6051C.pl/1.1/Fri Oct 17 09:12:38 2003//
# CVS Reference       : /AES_6149A.pl/1.12/Wed Nov  2 14:15:23 2005//
# CVS Reference       : /DES3_6150A.pl/1.1/Mon Jan 17 08:34:31 2005//
# ----------------------------------------------------------------------------


# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR System Peripherals
# *****************************************************************************
# -------- GPBR : (SYS Offset: 0xd50) GPBR General Purpose Register -------- 
# -------- GPBR : (SYS Offset: 0xd54) GPBR General Purpose Register -------- 

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
#              SOFTWARE API DEFINITION  FOR Clock Generator Controler
# *****************************************************************************
# -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- 
set AT91C_CKGR_MOSCEN     [expr 0x1 <<  0 ]
set AT91C_CKGR_OSCBYPASS  [expr 0x1 <<  1 ]
set AT91C_CKGR_OSCOUNT    [expr 0xFF <<  8 ]
# -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- 
set AT91C_CKGR_DIV        [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIV_0                    0x0
set 	AT91C_CKGR_DIV_BYPASS               0x1
set AT91C_CKGR_PLLCOUNT   [expr 0x3F <<  8 ]
set AT91C_CKGR_OUT        [expr 0x3 << 14 ]
set 	AT91C_CKGR_OUT_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_OUT_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_OUT_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_OUT_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MUL        [expr 0x7FF << 16 ]
set AT91C_CKGR_USBDIV     [expr 0x3 << 28 ]
set 	AT91C_CKGR_USBDIV_0                    [expr 0x0 << 28 ]
set 	AT91C_CKGR_USBDIV_1                    [expr 0x1 << 28 ]
set 	AT91C_CKGR_USBDIV_2                    [expr 0x2 << 28 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Power Management Controler
# *****************************************************************************
# -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
set AT91C_PMC_PCK3        [expr 0x1 << 11 ]
# -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
set AT91C_PMC_PCK3        [expr 0x1 << 11 ]
# -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
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
# -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- 
set AT91C_CKGR_DIV        [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIV_0                    0x0
set 	AT91C_CKGR_DIV_BYPASS               0x1
set AT91C_CKGR_PLLCOUNT   [expr 0x3F <<  8 ]
set AT91C_CKGR_OUT        [expr 0x3 << 14 ]
set 	AT91C_CKGR_OUT_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_OUT_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_OUT_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_OUT_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MUL        [expr 0x7FF << 16 ]
set AT91C_CKGR_USBDIV     [expr 0x3 << 28 ]
set 	AT91C_CKGR_USBDIV_0                    [expr 0x0 << 28 ]
set 	AT91C_CKGR_USBDIV_1                    [expr 0x1 << 28 ]
set 	AT91C_CKGR_USBDIV_2                    [expr 0x2 << 28 ]
# -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x3 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLL_CLK              0x3
set AT91C_PMC_PRES        [expr 0x7 <<  2 ]
set 	AT91C_PMC_PRES_CLK                  [expr 0x0 <<  2 ]
set 	AT91C_PMC_PRES_CLK_2                [expr 0x1 <<  2 ]
set 	AT91C_PMC_PRES_CLK_4                [expr 0x2 <<  2 ]
set 	AT91C_PMC_PRES_CLK_8                [expr 0x3 <<  2 ]
set 	AT91C_PMC_PRES_CLK_16               [expr 0x4 <<  2 ]
set 	AT91C_PMC_PRES_CLK_32               [expr 0x5 <<  2 ]
set 	AT91C_PMC_PRES_CLK_64               [expr 0x6 <<  2 ]
# -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x3 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLL_CLK              0x3
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
set AT91C_PMC_LOCK        [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]
# -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCK        [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]
# -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCK        [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
set AT91C_PMC_PCK3RDY     [expr 0x1 << 11 ]
# -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 
set AT91C_PMC_MOSCS       [expr 0x1 <<  0 ]
set AT91C_PMC_LOCK        [expr 0x1 <<  2 ]
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
# -------- SHDWC_SHSR : (SHDWC Offset: 0x8) Shut Down Status Register -------- 
set AT91C_SHDWC_WAKEUP0   [expr 0x1 <<  0 ]
set AT91C_SHDWC_WAKEUP1   [expr 0x1 <<  1 ]
set AT91C_SHDWC_FWKUP     [expr 0x1 <<  2 ]
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
#              SOFTWARE API DEFINITION  FOR Memory Controller Interface
# *****************************************************************************
# -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- 
set AT91C_MC_RCB          [expr 0x1 <<  0 ]
# -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- 
set AT91C_MC_UNDADD       [expr 0x1 <<  0 ]
set AT91C_MC_MISADD       [expr 0x1 <<  1 ]
set AT91C_MC_MPU          [expr 0x1 <<  2 ]
set AT91C_MC_ABTSZ        [expr 0x3 <<  8 ]
set 	AT91C_MC_ABTSZ_BYTE                 [expr 0x0 <<  8 ]
set 	AT91C_MC_ABTSZ_HWORD                [expr 0x1 <<  8 ]
set 	AT91C_MC_ABTSZ_WORD                 [expr 0x2 <<  8 ]
set AT91C_MC_ABTTYP       [expr 0x3 << 10 ]
set 	AT91C_MC_ABTTYP_DATAR                [expr 0x0 << 10 ]
set 	AT91C_MC_ABTTYP_DATAW                [expr 0x1 << 10 ]
set 	AT91C_MC_ABTTYP_FETCH                [expr 0x2 << 10 ]
set AT91C_MC_MST0         [expr 0x1 << 16 ]
set AT91C_MC_MST1         [expr 0x1 << 17 ]
set AT91C_MC_SVMST0       [expr 0x1 << 24 ]
set AT91C_MC_SVMST1       [expr 0x1 << 25 ]
# -------- MC_PUIA : (MC Offset: 0x10) MC Protection Unit Area -------- 
set AT91C_MC_PROT         [expr 0x3 <<  0 ]
set 	AT91C_MC_PROT_PNAUNA               0x0
set 	AT91C_MC_PROT_PRWUNA               0x1
set 	AT91C_MC_PROT_PRWURO               0x2
set 	AT91C_MC_PROT_PRWURW               0x3
set AT91C_MC_SIZE         [expr 0xF <<  4 ]
set 	AT91C_MC_SIZE_1KB                  [expr 0x0 <<  4 ]
set 	AT91C_MC_SIZE_2KB                  [expr 0x1 <<  4 ]
set 	AT91C_MC_SIZE_4KB                  [expr 0x2 <<  4 ]
set 	AT91C_MC_SIZE_8KB                  [expr 0x3 <<  4 ]
set 	AT91C_MC_SIZE_16KB                 [expr 0x4 <<  4 ]
set 	AT91C_MC_SIZE_32KB                 [expr 0x5 <<  4 ]
set 	AT91C_MC_SIZE_64KB                 [expr 0x6 <<  4 ]
set 	AT91C_MC_SIZE_128KB                [expr 0x7 <<  4 ]
set 	AT91C_MC_SIZE_256KB                [expr 0x8 <<  4 ]
set 	AT91C_MC_SIZE_512KB                [expr 0x9 <<  4 ]
set 	AT91C_MC_SIZE_1MB                  [expr 0xA <<  4 ]
set 	AT91C_MC_SIZE_2MB                  [expr 0xB <<  4 ]
set 	AT91C_MC_SIZE_4MB                  [expr 0xC <<  4 ]
set 	AT91C_MC_SIZE_8MB                  [expr 0xD <<  4 ]
set 	AT91C_MC_SIZE_16MB                 [expr 0xE <<  4 ]
set 	AT91C_MC_SIZE_64MB                 [expr 0xF <<  4 ]
set AT91C_MC_BA           [expr 0x3FFFF << 10 ]
# -------- MC_PUP : (MC Offset: 0x50) MC Protection Unit Peripheral -------- 
set AT91C_MC_PROT         [expr 0x3 <<  0 ]
set 	AT91C_MC_PROT_PNAUNA               0x0
set 	AT91C_MC_PROT_PRWUNA               0x1
set 	AT91C_MC_PROT_PRWURO               0x2
set 	AT91C_MC_PROT_PRWURW               0x3
# -------- MC_PUER : (MC Offset: 0x54) MC Protection Unit Area -------- 
set AT91C_MC_PUEB         [expr 0x1 <<  0 ]
# -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- 
set AT91C_MC_EOP          [expr 0x1 <<  0 ]
set AT91C_MC_EOL          [expr 0x1 <<  1 ]
set AT91C_MC_LOCKE        [expr 0x1 <<  2 ]
set AT91C_MC_PROGE        [expr 0x1 <<  3 ]
set AT91C_MC_NEBP         [expr 0x1 <<  7 ]
set AT91C_MC_FWS          [expr 0x3 <<  8 ]
set 	AT91C_MC_FWS_0FWS                 [expr 0x0 <<  8 ]
set 	AT91C_MC_FWS_1FWS                 [expr 0x1 <<  8 ]
set 	AT91C_MC_FWS_2FWS                 [expr 0x2 <<  8 ]
set 	AT91C_MC_FWS_3FWS                 [expr 0x3 <<  8 ]
set AT91C_MC_FMCN         [expr 0xFF << 16 ]
# -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- 
set AT91C_MC_FCMD         [expr 0xF <<  0 ]
set 	AT91C_MC_FCMD_START_PROG           0x1
set 	AT91C_MC_FCMD_LOCK                 0x2
set 	AT91C_MC_FCMD_PROG_AND_LOCK        0x3
set 	AT91C_MC_FCMD_UNLOCK               0x4
set 	AT91C_MC_FCMD_ERASE_ALL            0x8
set AT91C_MC_PAGEN        [expr 0x3FF <<  8 ]
set AT91C_MC_KEY          [expr 0xFF << 24 ]
# -------- MC_FSR : (MC Offset: 0x68) MC Flash Status Register -------- 
set AT91C_MC_EOP          [expr 0x1 <<  0 ]
set AT91C_MC_EOL          [expr 0x1 <<  1 ]
set AT91C_MC_LOCKE        [expr 0x1 <<  2 ]
set AT91C_MC_PROGE        [expr 0x1 <<  3 ]
set AT91C_MC_LOCKS0       [expr 0x1 << 16 ]
set AT91C_MC_LOCKS1       [expr 0x1 << 17 ]
set AT91C_MC_LOCKS2       [expr 0x1 << 18 ]
set AT91C_MC_LOCKS3       [expr 0x1 << 19 ]
set AT91C_MC_LOCKS4       [expr 0x1 << 20 ]
set AT91C_MC_LOCKS5       [expr 0x1 << 21 ]
set AT91C_MC_LOCKS6       [expr 0x1 << 22 ]
set AT91C_MC_LOCKS7       [expr 0x1 << 23 ]
set AT91C_MC_LOCKS8       [expr 0x1 << 24 ]
set AT91C_MC_LOCKS9       [expr 0x1 << 25 ]
set AT91C_MC_LOCKS10      [expr 0x1 << 26 ]
set AT91C_MC_LOCKS11      [expr 0x1 << 27 ]
set AT91C_MC_LOCKS12      [expr 0x1 << 28 ]
set AT91C_MC_LOCKS13      [expr 0x1 << 29 ]
set AT91C_MC_LOCKS14      [expr 0x1 << 30 ]
set AT91C_MC_LOCKS15      [expr 0x1 << 31 ]

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
set AT91C_MCI_PDCPADV     [expr 0x1 << 14 ]
set AT91C_MCI_PDCMODE     [expr 0x1 << 15 ]
set AT91C_MCI_BLKLEN      [expr 0xFFF << 18 ]
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
set AT91C_MCI_SCDSEL      [expr 0xF <<  0 ]
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
set AT91C_MCI_TRTYP       [expr 0x3 << 19 ]
set 	AT91C_MCI_TRTYP_BLOCK                [expr 0x0 << 19 ]
set 	AT91C_MCI_TRTYP_MULTIPLE             [expr 0x1 << 19 ]
set 	AT91C_MCI_TRTYP_STREAM               [expr 0x2 << 19 ]
# -------- MCI_SR : (MCI Offset: 0x40) MCI Status Register -------- 
set AT91C_MCI_CMDRDY      [expr 0x1 <<  0 ]
set AT91C_MCI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_MCI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_MCI_BLKE        [expr 0x1 <<  3 ]
set AT91C_MCI_DTIP        [expr 0x1 <<  4 ]
set AT91C_MCI_NOTBUSY     [expr 0x1 <<  5 ]
set AT91C_MCI_ENDRX       [expr 0x1 <<  6 ]
set AT91C_MCI_ENDTX       [expr 0x1 <<  7 ]
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
#               REGISTER ADDRESS DEFINITION FOR AT91SAM7A3
# *****************************************************************************
# ========== Register definition for SYS peripheral ========== 
set AT91C_SYS_GPBR1 0xFFFFFD54
set AT91C_SYS_GPBR0 0xFFFFFD50
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
# ========== Register definition for CKGR peripheral ========== 
set AT91C_CKGR_PLLR 0xFFFFFC2C
set AT91C_CKGR_MCFR 0xFFFFFC24
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
set AT91C_PMC_MOR   0xFFFFFC20
set AT91C_PMC_PCER  0xFFFFFC10
set AT91C_PMC_PCSR  0xFFFFFC18
set AT91C_PMC_PLLR  0xFFFFFC2C
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
# ========== Register definition for MC peripheral ========== 
set AT91C_MC_FCR    0xFFFFFF64
set AT91C_MC_PUER   0xFFFFFF54
set AT91C_MC_ASR    0xFFFFFF04
set AT91C_MC_FSR    0xFFFFFF68
set AT91C_MC_FMR    0xFFFFFF60
set AT91C_MC_PUP    0xFFFFFF50
set AT91C_MC_PUIA   0xFFFFFF10
set AT91C_MC_AASR   0xFFFFFF08
set AT91C_MC_RCR    0xFFFFFF00
# ========== Register definition for CAN0_MB0 peripheral ========== 
set AT91C_CAN0_MB0_MDH 0xFFF80218
set AT91C_CAN0_MB0_MSR 0xFFF80210
set AT91C_CAN0_MB0_MID 0xFFF80208
set AT91C_CAN0_MB0_MMR 0xFFF80200
set AT91C_CAN0_MB0_MCR 0xFFF8021C
set AT91C_CAN0_MB0_MDL 0xFFF80214
set AT91C_CAN0_MB0_MFID 0xFFF8020C
set AT91C_CAN0_MB0_MAM 0xFFF80204
# ========== Register definition for CAN0_MB1 peripheral ========== 
set AT91C_CAN0_MB1_MDH 0xFFF80238
set AT91C_CAN0_MB1_MSR 0xFFF80230
set AT91C_CAN0_MB1_MID 0xFFF80228
set AT91C_CAN0_MB1_MMR 0xFFF80220
set AT91C_CAN0_MB1_MCR 0xFFF8023C
set AT91C_CAN0_MB1_MDL 0xFFF80234
set AT91C_CAN0_MB1_MFID 0xFFF8022C
set AT91C_CAN0_MB1_MAM 0xFFF80224
# ========== Register definition for CAN0_MB2 peripheral ========== 
set AT91C_CAN0_MB2_MDH 0xFFF80258
set AT91C_CAN0_MB2_MSR 0xFFF80250
set AT91C_CAN0_MB2_MID 0xFFF80248
set AT91C_CAN0_MB2_MMR 0xFFF80240
set AT91C_CAN0_MB2_MCR 0xFFF8025C
set AT91C_CAN0_MB2_MDL 0xFFF80254
set AT91C_CAN0_MB2_MFID 0xFFF8024C
set AT91C_CAN0_MB2_MAM 0xFFF80244
# ========== Register definition for CAN0_MB3 peripheral ========== 
set AT91C_CAN0_MB3_MDH 0xFFF80278
set AT91C_CAN0_MB3_MSR 0xFFF80270
set AT91C_CAN0_MB3_MID 0xFFF80268
set AT91C_CAN0_MB3_MMR 0xFFF80260
set AT91C_CAN0_MB3_MCR 0xFFF8027C
set AT91C_CAN0_MB3_MDL 0xFFF80274
set AT91C_CAN0_MB3_MFID 0xFFF8026C
set AT91C_CAN0_MB3_MAM 0xFFF80264
# ========== Register definition for CAN0_MB4 peripheral ========== 
set AT91C_CAN0_MB4_MDH 0xFFF80298
set AT91C_CAN0_MB4_MSR 0xFFF80290
set AT91C_CAN0_MB4_MID 0xFFF80288
set AT91C_CAN0_MB4_MMR 0xFFF80280
set AT91C_CAN0_MB4_MCR 0xFFF8029C
set AT91C_CAN0_MB4_MDL 0xFFF80294
set AT91C_CAN0_MB4_MFID 0xFFF8028C
set AT91C_CAN0_MB4_MAM 0xFFF80284
# ========== Register definition for CAN0_MB5 peripheral ========== 
set AT91C_CAN0_MB5_MSR 0xFFF802B0
set AT91C_CAN0_MB5_MID 0xFFF802A8
set AT91C_CAN0_MB5_MMR 0xFFF802A0
set AT91C_CAN0_MB5_MCR 0xFFF802BC
set AT91C_CAN0_MB5_MDL 0xFFF802B4
set AT91C_CAN0_MB5_MFID 0xFFF802AC
set AT91C_CAN0_MB5_MAM 0xFFF802A4
set AT91C_CAN0_MB5_MDH 0xFFF802B8
# ========== Register definition for CAN0_MB6 peripheral ========== 
set AT91C_CAN0_MB6_MCR 0xFFF802DC
set AT91C_CAN0_MB6_MDL 0xFFF802D4
set AT91C_CAN0_MB6_MFID 0xFFF802CC
set AT91C_CAN0_MB6_MAM 0xFFF802C4
set AT91C_CAN0_MB6_MDH 0xFFF802D8
set AT91C_CAN0_MB6_MSR 0xFFF802D0
set AT91C_CAN0_MB6_MID 0xFFF802C8
set AT91C_CAN0_MB6_MMR 0xFFF802C0
# ========== Register definition for CAN0_MB7 peripheral ========== 
set AT91C_CAN0_MB7_MCR 0xFFF802FC
set AT91C_CAN0_MB7_MDL 0xFFF802F4
set AT91C_CAN0_MB7_MFID 0xFFF802EC
set AT91C_CAN0_MB7_MAM 0xFFF802E4
set AT91C_CAN0_MB7_MDH 0xFFF802F8
set AT91C_CAN0_MB7_MSR 0xFFF802F0
set AT91C_CAN0_MB7_MID 0xFFF802E8
set AT91C_CAN0_MB7_MMR 0xFFF802E0
# ========== Register definition for CAN0_MB8 peripheral ========== 
set AT91C_CAN0_MB8_MCR 0xFFF8031C
set AT91C_CAN0_MB8_MDL 0xFFF80314
set AT91C_CAN0_MB8_MFID 0xFFF8030C
set AT91C_CAN0_MB8_MAM 0xFFF80304
set AT91C_CAN0_MB8_MDH 0xFFF80318
set AT91C_CAN0_MB8_MMR 0xFFF80300
set AT91C_CAN0_MB8_MID 0xFFF80308
set AT91C_CAN0_MB8_MSR 0xFFF80310
# ========== Register definition for CAN0_MB9 peripheral ========== 
set AT91C_CAN0_MB9_MCR 0xFFF8033C
set AT91C_CAN0_MB9_MDL 0xFFF80334
set AT91C_CAN0_MB9_MFID 0xFFF8032C
set AT91C_CAN0_MB9_MAM 0xFFF80324
set AT91C_CAN0_MB9_MDH 0xFFF80338
set AT91C_CAN0_MB9_MSR 0xFFF80330
set AT91C_CAN0_MB9_MID 0xFFF80328
set AT91C_CAN0_MB9_MMR 0xFFF80320
# ========== Register definition for CAN0_MB10 peripheral ========== 
set AT91C_CAN0_MB10_MCR 0xFFF8035C
set AT91C_CAN0_MB10_MDL 0xFFF80354
set AT91C_CAN0_MB10_MFID 0xFFF8034C
set AT91C_CAN0_MB10_MAM 0xFFF80344
set AT91C_CAN0_MB10_MDH 0xFFF80358
set AT91C_CAN0_MB10_MSR 0xFFF80350
set AT91C_CAN0_MB10_MID 0xFFF80348
set AT91C_CAN0_MB10_MMR 0xFFF80340
# ========== Register definition for CAN0_MB11 peripheral ========== 
set AT91C_CAN0_MB11_MCR 0xFFF8037C
set AT91C_CAN0_MB11_MDL 0xFFF80374
set AT91C_CAN0_MB11_MFID 0xFFF8036C
set AT91C_CAN0_MB11_MAM 0xFFF80364
set AT91C_CAN0_MB11_MDH 0xFFF80378
set AT91C_CAN0_MB11_MSR 0xFFF80370
set AT91C_CAN0_MB11_MMR 0xFFF80360
set AT91C_CAN0_MB11_MID 0xFFF80368
# ========== Register definition for CAN0_MB12 peripheral ========== 
set AT91C_CAN0_MB12_MCR 0xFFF8039C
set AT91C_CAN0_MB12_MDL 0xFFF80394
set AT91C_CAN0_MB12_MFID 0xFFF8038C
set AT91C_CAN0_MB12_MAM 0xFFF80384
set AT91C_CAN0_MB12_MDH 0xFFF80398
set AT91C_CAN0_MB12_MSR 0xFFF80390
set AT91C_CAN0_MB12_MID 0xFFF80388
set AT91C_CAN0_MB12_MMR 0xFFF80380
# ========== Register definition for CAN0_MB13 peripheral ========== 
set AT91C_CAN0_MB13_MCR 0xFFF803BC
set AT91C_CAN0_MB13_MDL 0xFFF803B4
set AT91C_CAN0_MB13_MFID 0xFFF803AC
set AT91C_CAN0_MB13_MAM 0xFFF803A4
set AT91C_CAN0_MB13_MDH 0xFFF803B8
set AT91C_CAN0_MB13_MSR 0xFFF803B0
set AT91C_CAN0_MB13_MID 0xFFF803A8
set AT91C_CAN0_MB13_MMR 0xFFF803A0
# ========== Register definition for CAN0_MB14 peripheral ========== 
set AT91C_CAN0_MB14_MCR 0xFFF803DC
set AT91C_CAN0_MB14_MDL 0xFFF803D4
set AT91C_CAN0_MB14_MFID 0xFFF803CC
set AT91C_CAN0_MB14_MAM 0xFFF803C4
set AT91C_CAN0_MB14_MDH 0xFFF803D8
set AT91C_CAN0_MB14_MSR 0xFFF803D0
set AT91C_CAN0_MB14_MID 0xFFF803C8
set AT91C_CAN0_MB14_MMR 0xFFF803C0
# ========== Register definition for CAN0_MB15 peripheral ========== 
set AT91C_CAN0_MB15_MMR 0xFFF803E0
set AT91C_CAN0_MB15_MDH 0xFFF803F8
set AT91C_CAN0_MB15_MSR 0xFFF803F0
set AT91C_CAN0_MB15_MID 0xFFF803E8
set AT91C_CAN0_MB15_MCR 0xFFF803FC
set AT91C_CAN0_MB15_MDL 0xFFF803F4
set AT91C_CAN0_MB15_MFID 0xFFF803EC
set AT91C_CAN0_MB15_MAM 0xFFF803E4
# ========== Register definition for CAN0 peripheral ========== 
set AT91C_CAN0_TCR  0xFFF80024
set AT91C_CAN0_TIMESTP 0xFFF8001C
set AT91C_CAN0_BR   0xFFF80014
set AT91C_CAN0_ACR  0xFFF80028
set AT91C_CAN0_VR   0xFFF800FC
set AT91C_CAN0_IER  0xFFF80004
set AT91C_CAN0_IMR  0xFFF8000C
set AT91C_CAN0_MR   0xFFF80000
set AT91C_CAN0_IDR  0xFFF80008
set AT91C_CAN0_SR   0xFFF80010
set AT91C_CAN0_TIM  0xFFF80018
set AT91C_CAN0_ECR  0xFFF80020
# ========== Register definition for CAN1_MB0 peripheral ========== 
set AT91C_CAN1_MB0_MDH 0xFFF84218
set AT91C_CAN1_MB0_MSR 0xFFF84210
set AT91C_CAN1_MB0_MID 0xFFF84208
set AT91C_CAN1_MB0_MMR 0xFFF84200
set AT91C_CAN1_MB0_MCR 0xFFF8421C
set AT91C_CAN1_MB0_MDL 0xFFF84214
set AT91C_CAN1_MB0_MFID 0xFFF8420C
set AT91C_CAN1_MB0_MAM 0xFFF84204
# ========== Register definition for CAN1_MB1 peripheral ========== 
set AT91C_CAN1_MB1_MDH 0xFFF84238
set AT91C_CAN1_MB1_MSR 0xFFF84230
set AT91C_CAN1_MB1_MID 0xFFF84228
set AT91C_CAN1_MB1_MMR 0xFFF84220
set AT91C_CAN1_MB1_MCR 0xFFF8423C
set AT91C_CAN1_MB1_MDL 0xFFF84234
set AT91C_CAN1_MB1_MFID 0xFFF8422C
set AT91C_CAN1_MB1_MAM 0xFFF84224
# ========== Register definition for CAN1_MB2 peripheral ========== 
set AT91C_CAN1_MB2_MDH 0xFFF84258
set AT91C_CAN1_MB2_MSR 0xFFF84250
set AT91C_CAN1_MB2_MID 0xFFF84248
set AT91C_CAN1_MB2_MMR 0xFFF84240
set AT91C_CAN1_MB2_MCR 0xFFF8425C
set AT91C_CAN1_MB2_MDL 0xFFF84254
set AT91C_CAN1_MB2_MFID 0xFFF8424C
set AT91C_CAN1_MB2_MAM 0xFFF84244
# ========== Register definition for CAN1_MB3 peripheral ========== 
set AT91C_CAN1_MB3_MCR 0xFFF8427C
set AT91C_CAN1_MB3_MFID 0xFFF8426C
set AT91C_CAN1_MB3_MAM 0xFFF84264
set AT91C_CAN1_MB3_MMR 0xFFF84260
set AT91C_CAN1_MB3_MDH 0xFFF84278
set AT91C_CAN1_MB3_MSR 0xFFF84270
set AT91C_CAN1_MB3_MID 0xFFF84268
set AT91C_CAN1_MB3_MDL 0xFFF84274
# ========== Register definition for CAN1_MB4 peripheral ========== 
set AT91C_CAN1_MB4_MCR 0xFFF8429C
set AT91C_CAN1_MB4_MDL 0xFFF84294
set AT91C_CAN1_MB4_MFID 0xFFF8428C
set AT91C_CAN1_MB4_MAM 0xFFF84284
set AT91C_CAN1_MB4_MDH 0xFFF84298
set AT91C_CAN1_MB4_MSR 0xFFF84290
set AT91C_CAN1_MB4_MID 0xFFF84288
set AT91C_CAN1_MB4_MMR 0xFFF84280
# ========== Register definition for CAN1_MB5 peripheral ========== 
set AT91C_CAN1_MB5_MCR 0xFFF842BC
set AT91C_CAN1_MB5_MDL 0xFFF842B4
set AT91C_CAN1_MB5_MFID 0xFFF842AC
set AT91C_CAN1_MB5_MAM 0xFFF842A4
set AT91C_CAN1_MB5_MDH 0xFFF842B8
set AT91C_CAN1_MB5_MSR 0xFFF842B0
set AT91C_CAN1_MB5_MID 0xFFF842A8
set AT91C_CAN1_MB5_MMR 0xFFF842A0
# ========== Register definition for CAN1_MB6 peripheral ========== 
set AT91C_CAN1_MB6_MDH 0xFFF842D8
set AT91C_CAN1_MB6_MSR 0xFFF842D0
set AT91C_CAN1_MB6_MID 0xFFF842C8
set AT91C_CAN1_MB6_MMR 0xFFF842C0
set AT91C_CAN1_MB6_MAM 0xFFF842C4
set AT91C_CAN1_MB6_MCR 0xFFF842DC
set AT91C_CAN1_MB6_MDL 0xFFF842D4
set AT91C_CAN1_MB6_MFID 0xFFF842CC
# ========== Register definition for CAN1_MB7 peripheral ========== 
set AT91C_CAN1_MB7_MDH 0xFFF842F8
set AT91C_CAN1_MB7_MSR 0xFFF842F0
set AT91C_CAN1_MB7_MID 0xFFF842E8
set AT91C_CAN1_MB7_MMR 0xFFF842E0
set AT91C_CAN1_MB7_MCR 0xFFF842FC
set AT91C_CAN1_MB7_MDL 0xFFF842F4
set AT91C_CAN1_MB7_MFID 0xFFF842EC
set AT91C_CAN1_MB7_MAM 0xFFF842E4
# ========== Register definition for CAN1_MB8 peripheral ========== 
set AT91C_CAN1_MB8_MDH 0xFFF84318
set AT91C_CAN1_MB8_MSR 0xFFF84310
set AT91C_CAN1_MB8_MID 0xFFF84308
set AT91C_CAN1_MB8_MMR 0xFFF84300
set AT91C_CAN1_MB8_MCR 0xFFF8431C
set AT91C_CAN1_MB8_MDL 0xFFF84314
set AT91C_CAN1_MB8_MFID 0xFFF8430C
set AT91C_CAN1_MB8_MAM 0xFFF84304
# ========== Register definition for CAN1_MB9 peripheral ========== 
set AT91C_CAN1_MB9_MID 0xFFF84328
set AT91C_CAN1_MB9_MDH 0xFFF84338
set AT91C_CAN1_MB9_MSR 0xFFF84330
set AT91C_CAN1_MB9_MMR 0xFFF84320
set AT91C_CAN1_MB9_MCR 0xFFF8433C
set AT91C_CAN1_MB9_MDL 0xFFF84334
set AT91C_CAN1_MB9_MFID 0xFFF8432C
set AT91C_CAN1_MB9_MAM 0xFFF84324
# ========== Register definition for CAN1_MB10 peripheral ========== 
set AT91C_CAN1_MB10_MDH 0xFFF84358
set AT91C_CAN1_MB10_MSR 0xFFF84350
set AT91C_CAN1_MB10_MID 0xFFF84348
set AT91C_CAN1_MB10_MMR 0xFFF84340
set AT91C_CAN1_MB10_MCR 0xFFF8435C
set AT91C_CAN1_MB10_MDL 0xFFF84354
set AT91C_CAN1_MB10_MFID 0xFFF8434C
set AT91C_CAN1_MB10_MAM 0xFFF84344
# ========== Register definition for CAN1_MB11 peripheral ========== 
set AT91C_CAN1_MB11_MDH 0xFFF84378
set AT91C_CAN1_MB11_MSR 0xFFF84370
set AT91C_CAN1_MB11_MID 0xFFF84368
set AT91C_CAN1_MB11_MMR 0xFFF84360
set AT91C_CAN1_MB11_MCR 0xFFF8437C
set AT91C_CAN1_MB11_MDL 0xFFF84374
set AT91C_CAN1_MB11_MFID 0xFFF8436C
set AT91C_CAN1_MB11_MAM 0xFFF84364
# ========== Register definition for CAN1_MB12 peripheral ========== 
set AT91C_CAN1_MB12_MDH 0xFFF84398
set AT91C_CAN1_MB12_MSR 0xFFF84390
set AT91C_CAN1_MB12_MID 0xFFF84388
set AT91C_CAN1_MB12_MMR 0xFFF84380
set AT91C_CAN1_MB12_MCR 0xFFF8439C
set AT91C_CAN1_MB12_MDL 0xFFF84394
set AT91C_CAN1_MB12_MFID 0xFFF8438C
set AT91C_CAN1_MB12_MAM 0xFFF84384
# ========== Register definition for CAN1_MB13 peripheral ========== 
set AT91C_CAN1_MB13_MDH 0xFFF843B8
set AT91C_CAN1_MB13_MSR 0xFFF843B0
set AT91C_CAN1_MB13_MID 0xFFF843A8
set AT91C_CAN1_MB13_MMR 0xFFF843A0
set AT91C_CAN1_MB13_MCR 0xFFF843BC
set AT91C_CAN1_MB13_MDL 0xFFF843B4
set AT91C_CAN1_MB13_MFID 0xFFF843AC
set AT91C_CAN1_MB13_MAM 0xFFF843A4
# ========== Register definition for CAN1_MB14 peripheral ========== 
set AT91C_CAN1_MB14_MDH 0xFFF843D8
set AT91C_CAN1_MB14_MSR 0xFFF843D0
set AT91C_CAN1_MB14_MID 0xFFF843C8
set AT91C_CAN1_MB14_MMR 0xFFF843C0
set AT91C_CAN1_MB14_MCR 0xFFF843DC
set AT91C_CAN1_MB14_MDL 0xFFF843D4
set AT91C_CAN1_MB14_MFID 0xFFF843CC
set AT91C_CAN1_MB14_MAM 0xFFF843C4
# ========== Register definition for CAN1_MB15 peripheral ========== 
set AT91C_CAN1_MB15_MDH 0xFFF843F8
set AT91C_CAN1_MB15_MSR 0xFFF843F0
set AT91C_CAN1_MB15_MID 0xFFF843E8
set AT91C_CAN1_MB15_MMR 0xFFF843E0
set AT91C_CAN1_MB15_MCR 0xFFF843FC
set AT91C_CAN1_MB15_MDL 0xFFF843F4
set AT91C_CAN1_MB15_MFID 0xFFF843EC
set AT91C_CAN1_MB15_MAM 0xFFF843E4
# ========== Register definition for CAN1 peripheral ========== 
set AT91C_CAN1_MR   0xFFF84000
set AT91C_CAN1_VR   0xFFF840FC
set AT91C_CAN1_TIMESTP 0xFFF8401C
set AT91C_CAN1_BR   0xFFF84014
set AT91C_CAN1_IMR  0xFFF8400C
set AT91C_CAN1_IER  0xFFF84004
set AT91C_CAN1_ACR  0xFFF84028
set AT91C_CAN1_ECR  0xFFF84020
set AT91C_CAN1_TIM  0xFFF84018
set AT91C_CAN1_SR   0xFFF84010
set AT91C_CAN1_TCR  0xFFF84024
set AT91C_CAN1_IDR  0xFFF84008
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
# ========== Register definition for TC3 peripheral ========== 
set AT91C_TC3_IMR   0xFFFA402C
set AT91C_TC3_CV    0xFFFA4010
set AT91C_TC3_CCR   0xFFFA4000
set AT91C_TC3_IER   0xFFFA4024
set AT91C_TC3_CMR   0xFFFA4004
set AT91C_TC3_RA    0xFFFA4014
set AT91C_TC3_RC    0xFFFA401C
set AT91C_TC3_IDR   0xFFFA4028
set AT91C_TC3_RB    0xFFFA4018
set AT91C_TC3_SR    0xFFFA4020
# ========== Register definition for TC4 peripheral ========== 
set AT91C_TC4_IMR   0xFFFA406C
set AT91C_TC4_IER   0xFFFA4064
set AT91C_TC4_RC    0xFFFA405C
set AT91C_TC4_RA    0xFFFA4054
set AT91C_TC4_CMR   0xFFFA4044
set AT91C_TC4_IDR   0xFFFA4068
set AT91C_TC4_SR    0xFFFA4060
set AT91C_TC4_RB    0xFFFA4058
set AT91C_TC4_CV    0xFFFA4050
set AT91C_TC4_CCR   0xFFFA4040
# ========== Register definition for TC5 peripheral ========== 
set AT91C_TC5_CMR   0xFFFA4084
set AT91C_TC5_IDR   0xFFFA40A8
set AT91C_TC5_SR    0xFFFA40A0
set AT91C_TC5_RB    0xFFFA4098
set AT91C_TC5_CV    0xFFFA4090
set AT91C_TC5_CCR   0xFFFA4080
set AT91C_TC5_IMR   0xFFFA40AC
set AT91C_TC5_IER   0xFFFA40A4
set AT91C_TC5_RC    0xFFFA409C
set AT91C_TC5_RA    0xFFFA4094
# ========== Register definition for TCB1 peripheral ========== 
set AT91C_TCB1_BCR  0xFFFA40C0
set AT91C_TCB1_BMR  0xFFFA40C4
# ========== Register definition for TC6 peripheral ========== 
set AT91C_TC6_IDR   0xFFFA8028
set AT91C_TC6_SR    0xFFFA8020
set AT91C_TC6_RB    0xFFFA8018
set AT91C_TC6_CV    0xFFFA8010
set AT91C_TC6_CCR   0xFFFA8000
set AT91C_TC6_IMR   0xFFFA802C
set AT91C_TC6_IER   0xFFFA8024
set AT91C_TC6_RC    0xFFFA801C
set AT91C_TC6_RA    0xFFFA8014
set AT91C_TC6_CMR   0xFFFA8004
# ========== Register definition for TC7 peripheral ========== 
set AT91C_TC7_IDR   0xFFFA8068
set AT91C_TC7_SR    0xFFFA8060
set AT91C_TC7_RB    0xFFFA8058
set AT91C_TC7_CV    0xFFFA8050
set AT91C_TC7_CCR   0xFFFA8040
set AT91C_TC7_IMR   0xFFFA806C
set AT91C_TC7_IER   0xFFFA8064
set AT91C_TC7_RC    0xFFFA805C
set AT91C_TC7_RA    0xFFFA8054
set AT91C_TC7_CMR   0xFFFA8044
# ========== Register definition for TC8 peripheral ========== 
set AT91C_TC8_CV    0xFFFA8090
set AT91C_TC8_CCR   0xFFFA8080
set AT91C_TC8_IMR   0xFFFA80AC
set AT91C_TC8_IER   0xFFFA80A4
set AT91C_TC8_RC    0xFFFA809C
set AT91C_TC8_RA    0xFFFA8094
set AT91C_TC8_CMR   0xFFFA8084
set AT91C_TC8_IDR   0xFFFA80A8
set AT91C_TC8_SR    0xFFFA80A0
set AT91C_TC8_RB    0xFFFA8098
# ========== Register definition for TCB2 peripheral ========== 
set AT91C_TCB2_BMR  0xFFFA80C4
set AT91C_TCB2_BCR  0xFFFA80C0
# ========== Register definition for PDC_MCI peripheral ========== 
set AT91C_MCI_RCR   0xFFFAC104
set AT91C_MCI_PTCR  0xFFFAC120
set AT91C_MCI_TNPR  0xFFFAC118
set AT91C_MCI_RNPR  0xFFFAC110
set AT91C_MCI_TPR   0xFFFAC108
set AT91C_MCI_RPR   0xFFFAC100
set AT91C_MCI_PTSR  0xFFFAC124
set AT91C_MCI_TNCR  0xFFFAC11C
set AT91C_MCI_RNCR  0xFFFAC114
set AT91C_MCI_TCR   0xFFFAC10C
# ========== Register definition for MCI peripheral ========== 
set AT91C_MCI_IER   0xFFFAC044
set AT91C_MCI_TDR   0xFFFAC034
set AT91C_MCI_IDR   0xFFFAC048
set AT91C_MCI_SR    0xFFFAC040
set AT91C_MCI_DTOR  0xFFFAC008
set AT91C_MCI_CR    0xFFFAC000
set AT91C_MCI_IMR   0xFFFAC04C
set AT91C_MCI_MR    0xFFFAC004
set AT91C_MCI_SDCR  0xFFFAC00C
set AT91C_MCI_CMDR  0xFFFAC014
set AT91C_MCI_ARGR  0xFFFAC010
set AT91C_MCI_RSPR  0xFFFAC020
set AT91C_MCI_RDR   0xFFFAC030
# ========== Register definition for UDP peripheral ========== 
set AT91C_UDP_TXVC  0xFFFB0074
set AT91C_UDP_ISR   0xFFFB001C
set AT91C_UDP_IDR   0xFFFB0014
set AT91C_UDP_CSR   0xFFFB0030
set AT91C_UDP_RSTEP 0xFFFB0028
set AT91C_UDP_ICR   0xFFFB0020
set AT91C_UDP_GLBSTATE 0xFFFB0004
set AT91C_UDP_NUM   0xFFFB0000
set AT91C_UDP_FADDR 0xFFFB0008
set AT91C_UDP_IER   0xFFFB0010
set AT91C_UDP_IMR   0xFFFB0018
set AT91C_UDP_FDR   0xFFFB0050
# ========== Register definition for TWI peripheral ========== 
set AT91C_TWI_RHR   0xFFFB8030
set AT91C_TWI_IDR   0xFFFB8028
set AT91C_TWI_SR    0xFFFB8020
set AT91C_TWI_CWGR  0xFFFB8010
set AT91C_TWI_CR    0xFFFB8000
set AT91C_TWI_THR   0xFFFB8034
set AT91C_TWI_IMR   0xFFFB802C
set AT91C_TWI_IER   0xFFFB8024
set AT91C_TWI_IADR  0xFFFB800C
set AT91C_TWI_MMR   0xFFFB8004
# ========== Register definition for PDC_US0 peripheral ========== 
set AT91C_US0_PTCR  0xFFFC0120
set AT91C_US0_TNPR  0xFFFC0118
set AT91C_US0_RNPR  0xFFFC0110
set AT91C_US0_TPR   0xFFFC0108
set AT91C_US0_RPR   0xFFFC0100
set AT91C_US0_PTSR  0xFFFC0124
set AT91C_US0_TNCR  0xFFFC011C
set AT91C_US0_RNCR  0xFFFC0114
set AT91C_US0_TCR   0xFFFC010C
set AT91C_US0_RCR   0xFFFC0104
# ========== Register definition for US0 peripheral ========== 
set AT91C_US0_TTGR  0xFFFC0028
set AT91C_US0_BRGR  0xFFFC0020
set AT91C_US0_RHR   0xFFFC0018
set AT91C_US0_IMR   0xFFFC0010
set AT91C_US0_NER   0xFFFC0044
set AT91C_US0_RTOR  0xFFFC0024
set AT91C_US0_FIDI  0xFFFC0040
set AT91C_US0_CR    0xFFFC0000
set AT91C_US0_IER   0xFFFC0008
set AT91C_US0_IF    0xFFFC004C
set AT91C_US0_MR    0xFFFC0004
set AT91C_US0_IDR   0xFFFC000C
set AT91C_US0_CSR   0xFFFC0014
set AT91C_US0_THR   0xFFFC001C
# ========== Register definition for PDC_US1 peripheral ========== 
set AT91C_US1_PTSR  0xFFFC4124
set AT91C_US1_TNCR  0xFFFC411C
set AT91C_US1_RNCR  0xFFFC4114
set AT91C_US1_TCR   0xFFFC410C
set AT91C_US1_RCR   0xFFFC4104
set AT91C_US1_PTCR  0xFFFC4120
set AT91C_US1_TNPR  0xFFFC4118
set AT91C_US1_RNPR  0xFFFC4110
set AT91C_US1_TPR   0xFFFC4108
set AT91C_US1_RPR   0xFFFC4100
# ========== Register definition for US1 peripheral ========== 
set AT91C_US1_RHR   0xFFFC4018
set AT91C_US1_IMR   0xFFFC4010
set AT91C_US1_IER   0xFFFC4008
set AT91C_US1_CR    0xFFFC4000
set AT91C_US1_RTOR  0xFFFC4024
set AT91C_US1_THR   0xFFFC401C
set AT91C_US1_CSR   0xFFFC4014
set AT91C_US1_IDR   0xFFFC400C
set AT91C_US1_FIDI  0xFFFC4040
set AT91C_US1_BRGR  0xFFFC4020
set AT91C_US1_TTGR  0xFFFC4028
set AT91C_US1_IF    0xFFFC404C
set AT91C_US1_NER   0xFFFC4044
set AT91C_US1_MR    0xFFFC4004
# ========== Register definition for PDC_US2 peripheral ========== 
set AT91C_US2_PTSR  0xFFFC8124
set AT91C_US2_TNCR  0xFFFC811C
set AT91C_US2_RNCR  0xFFFC8114
set AT91C_US2_TCR   0xFFFC810C
set AT91C_US2_PTCR  0xFFFC8120
set AT91C_US2_RCR   0xFFFC8104
set AT91C_US2_TNPR  0xFFFC8118
set AT91C_US2_RPR   0xFFFC8100
set AT91C_US2_TPR   0xFFFC8108
set AT91C_US2_RNPR  0xFFFC8110
# ========== Register definition for US2 peripheral ========== 
set AT91C_US2_FIDI  0xFFFC8040
set AT91C_US2_TTGR  0xFFFC8028
set AT91C_US2_BRGR  0xFFFC8020
set AT91C_US2_RHR   0xFFFC8018
set AT91C_US2_IMR   0xFFFC8010
set AT91C_US2_IER   0xFFFC8008
set AT91C_US2_CR    0xFFFC8000
set AT91C_US2_IF    0xFFFC804C
set AT91C_US2_NER   0xFFFC8044
set AT91C_US2_RTOR  0xFFFC8024
set AT91C_US2_THR   0xFFFC801C
set AT91C_US2_CSR   0xFFFC8014
set AT91C_US2_IDR   0xFFFC800C
set AT91C_US2_MR    0xFFFC8004
# ========== Register definition for PWMC_CH0 peripheral ========== 
set AT91C_PWMC_CH0_CUPDR 0xFFFCC210
set AT91C_PWMC_CH0_CPRDR 0xFFFCC208
set AT91C_PWMC_CH0_CMR 0xFFFCC200
set AT91C_PWMC_CH0_Reserved 0xFFFCC214
set AT91C_PWMC_CH0_CCNTR 0xFFFCC20C
set AT91C_PWMC_CH0_CDTYR 0xFFFCC204
# ========== Register definition for PWMC_CH1 peripheral ========== 
set AT91C_PWMC_CH1_CUPDR 0xFFFCC230
set AT91C_PWMC_CH1_CPRDR 0xFFFCC228
set AT91C_PWMC_CH1_CMR 0xFFFCC220
set AT91C_PWMC_CH1_Reserved 0xFFFCC234
set AT91C_PWMC_CH1_CCNTR 0xFFFCC22C
set AT91C_PWMC_CH1_CDTYR 0xFFFCC224
# ========== Register definition for PWMC_CH2 peripheral ========== 
set AT91C_PWMC_CH2_CUPDR 0xFFFCC250
set AT91C_PWMC_CH2_CPRDR 0xFFFCC248
set AT91C_PWMC_CH2_CMR 0xFFFCC240
set AT91C_PWMC_CH2_Reserved 0xFFFCC254
set AT91C_PWMC_CH2_CCNTR 0xFFFCC24C
set AT91C_PWMC_CH2_CDTYR 0xFFFCC244
# ========== Register definition for PWMC_CH3 peripheral ========== 
set AT91C_PWMC_CH3_CUPDR 0xFFFCC270
set AT91C_PWMC_CH3_CPRDR 0xFFFCC268
set AT91C_PWMC_CH3_CMR 0xFFFCC260
set AT91C_PWMC_CH3_Reserved 0xFFFCC274
set AT91C_PWMC_CH3_CCNTR 0xFFFCC26C
set AT91C_PWMC_CH3_CDTYR 0xFFFCC264
# ========== Register definition for PWMC_CH4 peripheral ========== 
set AT91C_PWMC_CH4_CUPDR 0xFFFCC290
set AT91C_PWMC_CH4_CPRDR 0xFFFCC288
set AT91C_PWMC_CH4_CMR 0xFFFCC280
set AT91C_PWMC_CH4_Reserved 0xFFFCC294
set AT91C_PWMC_CH4_CCNTR 0xFFFCC28C
set AT91C_PWMC_CH4_CDTYR 0xFFFCC284
# ========== Register definition for PWMC_CH5 peripheral ========== 
set AT91C_PWMC_CH5_CUPDR 0xFFFCC2B0
set AT91C_PWMC_CH5_CPRDR 0xFFFCC2A8
set AT91C_PWMC_CH5_CMR 0xFFFCC2A0
set AT91C_PWMC_CH5_Reserved 0xFFFCC2B4
set AT91C_PWMC_CH5_CCNTR 0xFFFCC2AC
set AT91C_PWMC_CH5_CDTYR 0xFFFCC2A4
# ========== Register definition for PWMC_CH6 peripheral ========== 
set AT91C_PWMC_CH6_Reserved 0xFFFCC2D4
set AT91C_PWMC_CH6_CCNTR 0xFFFCC2CC
set AT91C_PWMC_CH6_CDTYR 0xFFFCC2C4
set AT91C_PWMC_CH6_CUPDR 0xFFFCC2D0
set AT91C_PWMC_CH6_CPRDR 0xFFFCC2C8
set AT91C_PWMC_CH6_CMR 0xFFFCC2C0
# ========== Register definition for PWMC_CH7 peripheral ========== 
set AT91C_PWMC_CH7_Reserved 0xFFFCC2F4
set AT91C_PWMC_CH7_CCNTR 0xFFFCC2EC
set AT91C_PWMC_CH7_CDTYR 0xFFFCC2E4
set AT91C_PWMC_CH7_CUPDR 0xFFFCC2F0
set AT91C_PWMC_CH7_CPRDR 0xFFFCC2E8
set AT91C_PWMC_CH7_CMR 0xFFFCC2E0
# ========== Register definition for PWMC peripheral ========== 
set AT91C_PWMC_VR   0xFFFCC0FC
set AT91C_PWMC_ISR  0xFFFCC01C
set AT91C_PWMC_IDR  0xFFFCC014
set AT91C_PWMC_SR   0xFFFCC00C
set AT91C_PWMC_ENA  0xFFFCC004
set AT91C_PWMC_IMR  0xFFFCC018
set AT91C_PWMC_MR   0xFFFCC000
set AT91C_PWMC_DIS  0xFFFCC008
set AT91C_PWMC_IER  0xFFFCC010
# ========== Register definition for PDC_SSC0 peripheral ========== 
set AT91C_SSC0_PTCR 0xFFFD0120
set AT91C_SSC0_TNPR 0xFFFD0118
set AT91C_SSC0_RNPR 0xFFFD0110
set AT91C_SSC0_TPR  0xFFFD0108
set AT91C_SSC0_RPR  0xFFFD0100
set AT91C_SSC0_PTSR 0xFFFD0124
set AT91C_SSC0_TNCR 0xFFFD011C
set AT91C_SSC0_RNCR 0xFFFD0114
set AT91C_SSC0_TCR  0xFFFD010C
set AT91C_SSC0_RCR  0xFFFD0104
# ========== Register definition for SSC0 peripheral ========== 
set AT91C_SSC0_IMR  0xFFFD004C
set AT91C_SSC0_IER  0xFFFD0044
set AT91C_SSC0_TSHR 0xFFFD0034
set AT91C_SSC0_THR  0xFFFD0024
set AT91C_SSC0_TFMR 0xFFFD001C
set AT91C_SSC0_RFMR 0xFFFD0014
set AT91C_SSC0_CMR  0xFFFD0004
set AT91C_SSC0_IDR  0xFFFD0048
set AT91C_SSC0_SR   0xFFFD0040
set AT91C_SSC0_RSHR 0xFFFD0030
set AT91C_SSC0_RHR  0xFFFD0020
set AT91C_SSC0_TCMR 0xFFFD0018
set AT91C_SSC0_RCMR 0xFFFD0010
set AT91C_SSC0_CR   0xFFFD0000
# ========== Register definition for PDC_SSC1 peripheral ========== 
set AT91C_SSC1_PTCR 0xFFFD4120
set AT91C_SSC1_TNPR 0xFFFD4118
set AT91C_SSC1_RNPR 0xFFFD4110
set AT91C_SSC1_TPR  0xFFFD4108
set AT91C_SSC1_RPR  0xFFFD4100
set AT91C_SSC1_PTSR 0xFFFD4124
set AT91C_SSC1_TNCR 0xFFFD411C
set AT91C_SSC1_RNCR 0xFFFD4114
set AT91C_SSC1_TCR  0xFFFD410C
set AT91C_SSC1_RCR  0xFFFD4104
# ========== Register definition for SSC1 peripheral ========== 
set AT91C_SSC1_RFMR 0xFFFD4014
set AT91C_SSC1_CMR  0xFFFD4004
set AT91C_SSC1_IDR  0xFFFD4048
set AT91C_SSC1_SR   0xFFFD4040
set AT91C_SSC1_RSHR 0xFFFD4030
set AT91C_SSC1_RHR  0xFFFD4020
set AT91C_SSC1_TCMR 0xFFFD4018
set AT91C_SSC1_RCMR 0xFFFD4010
set AT91C_SSC1_CR   0xFFFD4000
set AT91C_SSC1_IMR  0xFFFD404C
set AT91C_SSC1_IER  0xFFFD4044
set AT91C_SSC1_TSHR 0xFFFD4034
set AT91C_SSC1_THR  0xFFFD4024
set AT91C_SSC1_TFMR 0xFFFD401C
# ========== Register definition for PDC_ADC0 peripheral ========== 
set AT91C_ADC0_PTCR 0xFFFD8120
set AT91C_ADC0_TNPR 0xFFFD8118
set AT91C_ADC0_RNPR 0xFFFD8110
set AT91C_ADC0_TPR  0xFFFD8108
set AT91C_ADC0_RPR  0xFFFD8100
set AT91C_ADC0_PTSR 0xFFFD8124
set AT91C_ADC0_TNCR 0xFFFD811C
set AT91C_ADC0_RNCR 0xFFFD8114
set AT91C_ADC0_TCR  0xFFFD810C
set AT91C_ADC0_RCR  0xFFFD8104
# ========== Register definition for ADC0 peripheral ========== 
set AT91C_ADC0_IMR  0xFFFD802C
set AT91C_ADC0_CDR4 0xFFFD8040
set AT91C_ADC0_CDR2 0xFFFD8038
set AT91C_ADC0_CDR0 0xFFFD8030
set AT91C_ADC0_CDR7 0xFFFD804C
set AT91C_ADC0_CDR1 0xFFFD8034
set AT91C_ADC0_CDR3 0xFFFD803C
set AT91C_ADC0_CDR5 0xFFFD8044
set AT91C_ADC0_MR   0xFFFD8004
set AT91C_ADC0_CDR6 0xFFFD8048
set AT91C_ADC0_CR   0xFFFD8000
set AT91C_ADC0_CHER 0xFFFD8010
set AT91C_ADC0_CHSR 0xFFFD8018
set AT91C_ADC0_IER  0xFFFD8024
set AT91C_ADC0_SR   0xFFFD801C
set AT91C_ADC0_CHDR 0xFFFD8014
set AT91C_ADC0_IDR  0xFFFD8028
set AT91C_ADC0_LCDR 0xFFFD8020
# ========== Register definition for PDC_ADC1 peripheral ========== 
set AT91C_ADC1_RPR  0xFFFDC100
set AT91C_ADC1_RCR  0xFFFDC104
set AT91C_ADC1_PTSR 0xFFFDC124
set AT91C_ADC1_TNCR 0xFFFDC11C
set AT91C_ADC1_RNCR 0xFFFDC114
set AT91C_ADC1_TCR  0xFFFDC10C
set AT91C_ADC1_PTCR 0xFFFDC120
set AT91C_ADC1_TNPR 0xFFFDC118
set AT91C_ADC1_RNPR 0xFFFDC110
set AT91C_ADC1_TPR  0xFFFDC108
# ========== Register definition for ADC1 peripheral ========== 
set AT91C_ADC1_CDR1 0xFFFDC034
set AT91C_ADC1_IMR  0xFFFDC02C
set AT91C_ADC1_IER  0xFFFDC024
set AT91C_ADC1_SR   0xFFFDC01C
set AT91C_ADC1_CDR2 0xFFFDC038
set AT91C_ADC1_CDR0 0xFFFDC030
set AT91C_ADC1_CDR3 0xFFFDC03C
set AT91C_ADC1_CDR6 0xFFFDC048
set AT91C_ADC1_CDR4 0xFFFDC040
set AT91C_ADC1_CR   0xFFFDC000
set AT91C_ADC1_CDR7 0xFFFDC04C
set AT91C_ADC1_CDR5 0xFFFDC044
set AT91C_ADC1_CHDR 0xFFFDC014
set AT91C_ADC1_MR   0xFFFDC004
set AT91C_ADC1_IDR  0xFFFDC028
set AT91C_ADC1_LCDR 0xFFFDC020
set AT91C_ADC1_CHSR 0xFFFDC018
set AT91C_ADC1_CHER 0xFFFDC010
# ========== Register definition for PDC_SPI0 peripheral ========== 
set AT91C_SPI0_PTCR 0xFFFE0120
set AT91C_SPI0_TNPR 0xFFFE0118
set AT91C_SPI0_RNPR 0xFFFE0110
set AT91C_SPI0_TPR  0xFFFE0108
set AT91C_SPI0_RPR  0xFFFE0100
set AT91C_SPI0_PTSR 0xFFFE0124
set AT91C_SPI0_TNCR 0xFFFE011C
set AT91C_SPI0_RNCR 0xFFFE0114
set AT91C_SPI0_TCR  0xFFFE010C
set AT91C_SPI0_RCR  0xFFFE0104
# ========== Register definition for SPI0 peripheral ========== 
set AT91C_SPI0_CSR  0xFFFE0030
set AT91C_SPI0_IDR  0xFFFE0018
set AT91C_SPI0_SR   0xFFFE0010
set AT91C_SPI0_RDR  0xFFFE0008
set AT91C_SPI0_CR   0xFFFE0000
set AT91C_SPI0_IMR  0xFFFE001C
set AT91C_SPI0_IER  0xFFFE0014
set AT91C_SPI0_TDR  0xFFFE000C
set AT91C_SPI0_MR   0xFFFE0004
# ========== Register definition for PDC_SPI1 peripheral ========== 
set AT91C_SPI1_RNPR 0xFFFE4110
set AT91C_SPI1_TPR  0xFFFE4108
set AT91C_SPI1_RPR  0xFFFE4100
set AT91C_SPI1_PTSR 0xFFFE4124
set AT91C_SPI1_RCR  0xFFFE4104
set AT91C_SPI1_TCR  0xFFFE410C
set AT91C_SPI1_RNCR 0xFFFE4114
set AT91C_SPI1_TNCR 0xFFFE411C
set AT91C_SPI1_TNPR 0xFFFE4118
set AT91C_SPI1_PTCR 0xFFFE4120
# ========== Register definition for SPI1 peripheral ========== 
set AT91C_SPI1_CSR  0xFFFE4030
set AT91C_SPI1_IDR  0xFFFE4018
set AT91C_SPI1_SR   0xFFFE4010
set AT91C_SPI1_RDR  0xFFFE4008
set AT91C_SPI1_CR   0xFFFE4000
set AT91C_SPI1_IMR  0xFFFE401C
set AT91C_SPI1_IER  0xFFFE4014
set AT91C_SPI1_TDR  0xFFFE400C
set AT91C_SPI1_MR   0xFFFE4004

# *****************************************************************************
#               BASE ADDRESS DEFINITIONS FOR AT91SAM7A3
# *****************************************************************************
set AT91C_BASE_SYS       0xFFFFF000
set AT91C_BASE_AIC       0xFFFFF000
set AT91C_BASE_PDC_DBGU  0xFFFFF300
set AT91C_BASE_DBGU      0xFFFFF200
set AT91C_BASE_PIOA      0xFFFFF400
set AT91C_BASE_PIOB      0xFFFFF600
set AT91C_BASE_CKGR      0xFFFFFC20
set AT91C_BASE_PMC       0xFFFFFC00
set AT91C_BASE_RSTC      0xFFFFFD00
set AT91C_BASE_SHDWC     0xFFFFFD10
set AT91C_BASE_RTTC      0xFFFFFD20
set AT91C_BASE_PITC      0xFFFFFD30
set AT91C_BASE_WDTC      0xFFFFFD40
set AT91C_BASE_MC        0xFFFFFF00
set AT91C_BASE_CAN0_MB0  0xFFF80200
set AT91C_BASE_CAN0_MB1  0xFFF80220
set AT91C_BASE_CAN0_MB2  0xFFF80240
set AT91C_BASE_CAN0_MB3  0xFFF80260
set AT91C_BASE_CAN0_MB4  0xFFF80280
set AT91C_BASE_CAN0_MB5  0xFFF802A0
set AT91C_BASE_CAN0_MB6  0xFFF802C0
set AT91C_BASE_CAN0_MB7  0xFFF802E0
set AT91C_BASE_CAN0_MB8  0xFFF80300
set AT91C_BASE_CAN0_MB9  0xFFF80320
set AT91C_BASE_CAN0_MB10 0xFFF80340
set AT91C_BASE_CAN0_MB11 0xFFF80360
set AT91C_BASE_CAN0_MB12 0xFFF80380
set AT91C_BASE_CAN0_MB13 0xFFF803A0
set AT91C_BASE_CAN0_MB14 0xFFF803C0
set AT91C_BASE_CAN0_MB15 0xFFF803E0
set AT91C_BASE_CAN0      0xFFF80000
set AT91C_BASE_CAN1_MB0  0xFFF84200
set AT91C_BASE_CAN1_MB1  0xFFF84220
set AT91C_BASE_CAN1_MB2  0xFFF84240
set AT91C_BASE_CAN1_MB3  0xFFF84260
set AT91C_BASE_CAN1_MB4  0xFFF84280
set AT91C_BASE_CAN1_MB5  0xFFF842A0
set AT91C_BASE_CAN1_MB6  0xFFF842C0
set AT91C_BASE_CAN1_MB7  0xFFF842E0
set AT91C_BASE_CAN1_MB8  0xFFF84300
set AT91C_BASE_CAN1_MB9  0xFFF84320
set AT91C_BASE_CAN1_MB10 0xFFF84340
set AT91C_BASE_CAN1_MB11 0xFFF84360
set AT91C_BASE_CAN1_MB12 0xFFF84380
set AT91C_BASE_CAN1_MB13 0xFFF843A0
set AT91C_BASE_CAN1_MB14 0xFFF843C0
set AT91C_BASE_CAN1_MB15 0xFFF843E0
set AT91C_BASE_CAN1      0xFFF84000
set AT91C_BASE_TC0       0xFFFA0000
set AT91C_BASE_TC1       0xFFFA0040
set AT91C_BASE_TC2       0xFFFA0080
set AT91C_BASE_TCB0      0xFFFA0000
set AT91C_BASE_TC3       0xFFFA4000
set AT91C_BASE_TC4       0xFFFA4040
set AT91C_BASE_TC5       0xFFFA4080
set AT91C_BASE_TCB1      0xFFFA4000
set AT91C_BASE_TC6       0xFFFA8000
set AT91C_BASE_TC7       0xFFFA8040
set AT91C_BASE_TC8       0xFFFA8080
set AT91C_BASE_TCB2      0xFFFA8000
set AT91C_BASE_PDC_MCI   0xFFFAC100
set AT91C_BASE_MCI       0xFFFAC000
set AT91C_BASE_UDP       0xFFFB0000
set AT91C_BASE_TWI       0xFFFB8000
set AT91C_BASE_PDC_US0   0xFFFC0100
set AT91C_BASE_US0       0xFFFC0000
set AT91C_BASE_PDC_US1   0xFFFC4100
set AT91C_BASE_US1       0xFFFC4000
set AT91C_BASE_PDC_US2   0xFFFC8100
set AT91C_BASE_US2       0xFFFC8000
set AT91C_BASE_PWMC_CH0  0xFFFCC200
set AT91C_BASE_PWMC_CH1  0xFFFCC220
set AT91C_BASE_PWMC_CH2  0xFFFCC240
set AT91C_BASE_PWMC_CH3  0xFFFCC260
set AT91C_BASE_PWMC_CH4  0xFFFCC280
set AT91C_BASE_PWMC_CH5  0xFFFCC2A0
set AT91C_BASE_PWMC_CH6  0xFFFCC2C0
set AT91C_BASE_PWMC_CH7  0xFFFCC2E0
set AT91C_BASE_PWMC      0xFFFCC000
set AT91C_BASE_PDC_SSC0  0xFFFD0100
set AT91C_BASE_SSC0      0xFFFD0000
set AT91C_BASE_PDC_SSC1  0xFFFD4100
set AT91C_BASE_SSC1      0xFFFD4000
set AT91C_BASE_PDC_ADC0  0xFFFD8100
set AT91C_BASE_ADC0      0xFFFD8000
set AT91C_BASE_PDC_ADC1  0xFFFDC100
set AT91C_BASE_ADC1      0xFFFDC000
set AT91C_BASE_PDC_SPI0  0xFFFE0100
set AT91C_BASE_SPI0      0xFFFE0000
set AT91C_BASE_PDC_SPI1  0xFFFE4100
set AT91C_BASE_SPI1      0xFFFE4000

# *****************************************************************************
#               PERIPHERAL ID DEFINITIONS FOR AT91SAM7A3
# *****************************************************************************
set AT91C_ID_FIQ     0
set AT91C_ID_SYS     1
set AT91C_ID_PIOA    2
set AT91C_ID_PIOB    3
set AT91C_ID_CAN0    4
set AT91C_ID_CAN1    5
set AT91C_ID_US0     6
set AT91C_ID_US1     7
set AT91C_ID_US2     8
set AT91C_ID_MCI     9
set AT91C_ID_TWI    10
set AT91C_ID_SPI0   11
set AT91C_ID_SPI1   12
set AT91C_ID_SSC0   13
set AT91C_ID_SSC1   14
set AT91C_ID_TC0    15
set AT91C_ID_TC1    16
set AT91C_ID_TC2    17
set AT91C_ID_TC3    18
set AT91C_ID_TC4    19
set AT91C_ID_TC5    20
set AT91C_ID_TC6    21
set AT91C_ID_TC7    22
set AT91C_ID_TC8    23
set AT91C_ID_ADC0   24
set AT91C_ID_ADC1   25
set AT91C_ID_PWMC   26
set AT91C_ID_UDP    27
set AT91C_ID_IRQ0   28
set AT91C_ID_IRQ1   29
set AT91C_ID_IRQ2   30
set AT91C_ID_IRQ3   31

# *****************************************************************************
#               PIO DEFINITIONS FOR AT91SAM7A3
# *****************************************************************************
set AT91C_PIO_PA0        [expr 1 <<  0 ]
set AT91C_PA0_TWD      $AT91C_PIO_PA0
set AT91C_PA0_ADTRG0   $AT91C_PIO_PA0
set AT91C_PIO_PA1        [expr 1 <<  1 ]
set AT91C_PA1_TWCK     $AT91C_PIO_PA1
set AT91C_PA1_ADTRG1   $AT91C_PIO_PA1
set AT91C_PIO_PA10       [expr 1 << 10 ]
set AT91C_PA10_TXD2     $AT91C_PIO_PA10
set AT91C_PA10_SPI1_SPCK $AT91C_PIO_PA10
set AT91C_PIO_PA11       [expr 1 << 11 ]
set AT91C_PA11_SPI0_NPCS0 $AT91C_PIO_PA11
set AT91C_PIO_PA12       [expr 1 << 12 ]
set AT91C_PA12_SPI0_NPCS1 $AT91C_PIO_PA12
set AT91C_PA12_MCDA1    $AT91C_PIO_PA12
set AT91C_PIO_PA13       [expr 1 << 13 ]
set AT91C_PA13_SPI0_NPCS2 $AT91C_PIO_PA13
set AT91C_PA13_MCDA2    $AT91C_PIO_PA13
set AT91C_PIO_PA14       [expr 1 << 14 ]
set AT91C_PA14_SPI0_NPCS3 $AT91C_PIO_PA14
set AT91C_PA14_MCDA3    $AT91C_PIO_PA14
set AT91C_PIO_PA15       [expr 1 << 15 ]
set AT91C_PA15_SPI0_MISO $AT91C_PIO_PA15
set AT91C_PA15_MCDA0    $AT91C_PIO_PA15
set AT91C_PIO_PA16       [expr 1 << 16 ]
set AT91C_PA16_SPI0_MOSI $AT91C_PIO_PA16
set AT91C_PA16_MCCDA    $AT91C_PIO_PA16
set AT91C_PIO_PA17       [expr 1 << 17 ]
set AT91C_PA17_SPI0_SPCK $AT91C_PIO_PA17
set AT91C_PA17_MCCK     $AT91C_PIO_PA17
set AT91C_PIO_PA18       [expr 1 << 18 ]
set AT91C_PA18_PWM0     $AT91C_PIO_PA18
set AT91C_PA18_PCK0     $AT91C_PIO_PA18
set AT91C_PIO_PA19       [expr 1 << 19 ]
set AT91C_PA19_PWM1     $AT91C_PIO_PA19
set AT91C_PA19_PCK1     $AT91C_PIO_PA19
set AT91C_PIO_PA2        [expr 1 <<  2 ]
set AT91C_PA2_RXD0     $AT91C_PIO_PA2
set AT91C_PIO_PA20       [expr 1 << 20 ]
set AT91C_PA20_PWM2     $AT91C_PIO_PA20
set AT91C_PA20_PCK2     $AT91C_PIO_PA20
set AT91C_PIO_PA21       [expr 1 << 21 ]
set AT91C_PA21_PWM3     $AT91C_PIO_PA21
set AT91C_PA21_PCK3     $AT91C_PIO_PA21
set AT91C_PIO_PA22       [expr 1 << 22 ]
set AT91C_PA22_PWM4     $AT91C_PIO_PA22
set AT91C_PA22_IRQ0     $AT91C_PIO_PA22
set AT91C_PIO_PA23       [expr 1 << 23 ]
set AT91C_PA23_PWM5     $AT91C_PIO_PA23
set AT91C_PA23_IRQ1     $AT91C_PIO_PA23
set AT91C_PIO_PA24       [expr 1 << 24 ]
set AT91C_PA24_PWM6     $AT91C_PIO_PA24
set AT91C_PA24_TCLK4    $AT91C_PIO_PA24
set AT91C_PIO_PA25       [expr 1 << 25 ]
set AT91C_PA25_PWM7     $AT91C_PIO_PA25
set AT91C_PA25_TCLK5    $AT91C_PIO_PA25
set AT91C_PIO_PA26       [expr 1 << 26 ]
set AT91C_PA26_CANRX0   $AT91C_PIO_PA26
set AT91C_PIO_PA27       [expr 1 << 27 ]
set AT91C_PA27_CANTX0   $AT91C_PIO_PA27
set AT91C_PIO_PA28       [expr 1 << 28 ]
set AT91C_PA28_CANRX1   $AT91C_PIO_PA28
set AT91C_PA28_TCLK3    $AT91C_PIO_PA28
set AT91C_PIO_PA29       [expr 1 << 29 ]
set AT91C_PA29_CANTX1   $AT91C_PIO_PA29
set AT91C_PA29_TCLK6    $AT91C_PIO_PA29
set AT91C_PIO_PA3        [expr 1 <<  3 ]
set AT91C_PA3_TXD0     $AT91C_PIO_PA3
set AT91C_PIO_PA30       [expr 1 << 30 ]
set AT91C_PA30_DRXD     $AT91C_PIO_PA30
set AT91C_PA30_TCLK7    $AT91C_PIO_PA30
set AT91C_PIO_PA31       [expr 1 << 31 ]
set AT91C_PA31_DTXD     $AT91C_PIO_PA31
set AT91C_PA31_TCLK8    $AT91C_PIO_PA31
set AT91C_PIO_PA4        [expr 1 <<  4 ]
set AT91C_PA4_SCK0     $AT91C_PIO_PA4
set AT91C_PA4_SPI1_NPCS0 $AT91C_PIO_PA4
set AT91C_PIO_PA5        [expr 1 <<  5 ]
set AT91C_PA5_RTS0     $AT91C_PIO_PA5
set AT91C_PA5_SPI1_NPCS1 $AT91C_PIO_PA5
set AT91C_PIO_PA6        [expr 1 <<  6 ]
set AT91C_PA6_CTS0     $AT91C_PIO_PA6
set AT91C_PA6_SPI1_NPCS2 $AT91C_PIO_PA6
set AT91C_PIO_PA7        [expr 1 <<  7 ]
set AT91C_PA7_RXD1     $AT91C_PIO_PA7
set AT91C_PA7_SPI1_NPCS3 $AT91C_PIO_PA7
set AT91C_PIO_PA8        [expr 1 <<  8 ]
set AT91C_PA8_TXD1     $AT91C_PIO_PA8
set AT91C_PA8_SPI1_MISO $AT91C_PIO_PA8
set AT91C_PIO_PA9        [expr 1 <<  9 ]
set AT91C_PA9_RXD2     $AT91C_PIO_PA9
set AT91C_PA9_SPI1_MOSI $AT91C_PIO_PA9
set AT91C_PIO_PB0        [expr 1 <<  0 ]
set AT91C_PB0_IRQ2     $AT91C_PIO_PB0
set AT91C_PB0_PWM5     $AT91C_PIO_PB0
set AT91C_PIO_PB1        [expr 1 <<  1 ]
set AT91C_PB1_IRQ3     $AT91C_PIO_PB1
set AT91C_PB1_PWM6     $AT91C_PIO_PB1
set AT91C_PIO_PB10       [expr 1 << 10 ]
set AT91C_PB10_TCLK1    $AT91C_PIO_PB10
set AT91C_PB10_RK1      $AT91C_PIO_PB10
set AT91C_PIO_PB11       [expr 1 << 11 ]
set AT91C_PB11_TCLK2    $AT91C_PIO_PB11
set AT91C_PB11_RF1      $AT91C_PIO_PB11
set AT91C_PIO_PB12       [expr 1 << 12 ]
set AT91C_PB12_TIOA0    $AT91C_PIO_PB12
set AT91C_PB12_TD1      $AT91C_PIO_PB12
set AT91C_PIO_PB13       [expr 1 << 13 ]
set AT91C_PB13_TIOB0    $AT91C_PIO_PB13
set AT91C_PB13_RD1      $AT91C_PIO_PB13
set AT91C_PIO_PB14       [expr 1 << 14 ]
set AT91C_PB14_TIOA1    $AT91C_PIO_PB14
set AT91C_PB14_PWM0     $AT91C_PIO_PB14
set AT91C_PIO_PB15       [expr 1 << 15 ]
set AT91C_PB15_TIOB1    $AT91C_PIO_PB15
set AT91C_PB15_PWM1     $AT91C_PIO_PB15
set AT91C_PIO_PB16       [expr 1 << 16 ]
set AT91C_PB16_TIOA2    $AT91C_PIO_PB16
set AT91C_PB16_PWM2     $AT91C_PIO_PB16
set AT91C_PIO_PB17       [expr 1 << 17 ]
set AT91C_PB17_TIOB2    $AT91C_PIO_PB17
set AT91C_PB17_PWM3     $AT91C_PIO_PB17
set AT91C_PIO_PB18       [expr 1 << 18 ]
set AT91C_PB18_TIOA3    $AT91C_PIO_PB18
set AT91C_PB18_PWM4     $AT91C_PIO_PB18
set AT91C_PIO_PB19       [expr 1 << 19 ]
set AT91C_PB19_TIOB3    $AT91C_PIO_PB19
set AT91C_PB19_SPI1_NPCS1 $AT91C_PIO_PB19
set AT91C_PIO_PB2        [expr 1 <<  2 ]
set AT91C_PB2_TF0      $AT91C_PIO_PB2
set AT91C_PB2_PWM7     $AT91C_PIO_PB2
set AT91C_PIO_PB20       [expr 1 << 20 ]
set AT91C_PB20_TIOA4    $AT91C_PIO_PB20
set AT91C_PB20_SPI1_NPCS2 $AT91C_PIO_PB20
set AT91C_PIO_PB21       [expr 1 << 21 ]
set AT91C_PB21_TIOB4    $AT91C_PIO_PB21
set AT91C_PB21_SPI1_NPCS3 $AT91C_PIO_PB21
set AT91C_PIO_PB22       [expr 1 << 22 ]
set AT91C_PB22_TIOA5    $AT91C_PIO_PB22
set AT91C_PIO_PB23       [expr 1 << 23 ]
set AT91C_PB23_TIOB5    $AT91C_PIO_PB23
set AT91C_PIO_PB24       [expr 1 << 24 ]
set AT91C_PB24_TIOA6    $AT91C_PIO_PB24
set AT91C_PB24_RTS1     $AT91C_PIO_PB24
set AT91C_PIO_PB25       [expr 1 << 25 ]
set AT91C_PB25_TIOB6    $AT91C_PIO_PB25
set AT91C_PB25_CTS1     $AT91C_PIO_PB25
set AT91C_PIO_PB26       [expr 1 << 26 ]
set AT91C_PB26_TIOA7    $AT91C_PIO_PB26
set AT91C_PB26_SCK1     $AT91C_PIO_PB26
set AT91C_PIO_PB27       [expr 1 << 27 ]
set AT91C_PB27_TIOB7    $AT91C_PIO_PB27
set AT91C_PB27_RTS2     $AT91C_PIO_PB27
set AT91C_PIO_PB28       [expr 1 << 28 ]
set AT91C_PB28_TIOA8    $AT91C_PIO_PB28
set AT91C_PB28_CTS2     $AT91C_PIO_PB28
set AT91C_PIO_PB29       [expr 1 << 29 ]
set AT91C_PB29_TIOB8    $AT91C_PIO_PB29
set AT91C_PB29_SCK2     $AT91C_PIO_PB29
set AT91C_PIO_PB3        [expr 1 <<  3 ]
set AT91C_PB3_TK0      $AT91C_PIO_PB3
set AT91C_PB3_PCK0     $AT91C_PIO_PB3
set AT91C_PIO_PB4        [expr 1 <<  4 ]
set AT91C_PB4_TD0      $AT91C_PIO_PB4
set AT91C_PB4_PCK1     $AT91C_PIO_PB4
set AT91C_PIO_PB5        [expr 1 <<  5 ]
set AT91C_PB5_RD0      $AT91C_PIO_PB5
set AT91C_PB5_PCK2     $AT91C_PIO_PB5
set AT91C_PIO_PB6        [expr 1 <<  6 ]
set AT91C_PB6_RK0      $AT91C_PIO_PB6
set AT91C_PB6_PCK3     $AT91C_PIO_PB6
set AT91C_PIO_PB7        [expr 1 <<  7 ]
set AT91C_PB7_RF0      $AT91C_PIO_PB7
set AT91C_PB7_CANTX1   $AT91C_PIO_PB7
set AT91C_PIO_PB8        [expr 1 <<  8 ]
set AT91C_PB8_FIQ      $AT91C_PIO_PB8
set AT91C_PB8_TF1      $AT91C_PIO_PB8
set AT91C_PIO_PB9        [expr 1 <<  9 ]
set AT91C_PB9_TCLK0    $AT91C_PIO_PB9
set AT91C_PB9_TK1      $AT91C_PIO_PB9

# *****************************************************************************
#               MEMORY MAPPING DEFINITIONS FOR AT91SAM7A3
# *****************************************************************************
set AT91C_ISRAM	 0x00200000
set AT91C_ISRAM_SIZE	 0x00008000
set AT91C_IFLASH	 0x00100000
set AT91C_IFLASH_SIZE	 0x00040000


# *****************************************************************************
#               ATTRIBUTES DEFINITIONS FOR AT91SAM7A3
# *****************************************************************************
array set AT91SAM7A3_att {
	MC 	{ LP 	MC_att }
	PDC 	{ LP 	PDC_DBGU_att 	PDC_MCI_att 	PDC_US0_att 	PDC_US1_att 	PDC_US2_att 	PDC_SSC0_att 	PDC_SSC1_att 	PDC_ADC0_att 	PDC_ADC1_att 	PDC_SPI0_att 	PDC_SPI1_att }
	DBGU 	{ LP 	DBGU_att }
	PWMC_CH 	{ LP 	PWMC_CH0_att 	PWMC_CH1_att 	PWMC_CH2_att 	PWMC_CH3_att 	PWMC_CH4_att 	PWMC_CH5_att 	PWMC_CH6_att 	PWMC_CH7_att }
	SYS 	{ LP 	SYS_att }
	SHDWC 	{ LP 	SHDWC_att }
	SPI 	{ LP 	SPI0_att 	SPI1_att }
	SSC 	{ LP 	SSC0_att 	SSC1_att }
	TCB 	{ LP 	TCB0_att 	TCB1_att 	TCB2_att }
	PWMC 	{ LP 	PWMC_att }
	TC 	{ LP 	TC0_att 	TC1_att 	TC2_att 	TC3_att 	TC4_att 	TC5_att 	TC6_att 	TC7_att 	TC8_att }
	PITC 	{ LP 	PITC_att }
	ADC 	{ LP 	ADC0_att 	ADC1_att }
	PMC 	{ LP 	PMC_att }
	RSTC 	{ LP 	RSTC_att }
	CKGR 	{ LP 	CKGR_att }
	CAN_MB 	{ LP 	CAN0_MB0_att 	CAN0_MB1_att 	CAN0_MB2_att 	CAN0_MB3_att 	CAN0_MB4_att 	CAN0_MB5_att 	CAN0_MB6_att 	CAN0_MB7_att 	CAN0_MB8_att 	CAN0_MB9_att 	CAN0_MB10_att 	CAN0_MB11_att 	CAN0_MB12_att 	CAN0_MB13_att 	CAN0_MB14_att 	CAN0_MB15_att 	CAN1_MB0_att 	CAN1_MB1_att 	CAN1_MB2_att 	CAN1_MB3_att 	CAN1_MB4_att 	CAN1_MB5_att 	CAN1_MB6_att 	CAN1_MB7_att 	CAN1_MB8_att 	CAN1_MB9_att 	CAN1_MB10_att 	CAN1_MB11_att 	CAN1_MB12_att 	CAN1_MB13_att 	CAN1_MB14_att 	CAN1_MB15_att }
	PIO 	{ LP 	PIOA_att 	PIOB_att }
	RTTC 	{ LP 	RTTC_att }
	TWI 	{ LP 	TWI_att }
	USART 	{ LP 	US0_att 	US1_att 	US2_att }
	MCI 	{ LP 	MCI_att }
	WDTC 	{ LP 	WDTC_att }
	UDP 	{ LP 	UDP_att }
	AIC 	{ LP 	AIC_att }
	CAN 	{ LP 	CAN0_att 	CAN1_att }

}
# ========== Peripheral attributes for MC peripheral ========== 
array set MC_att {
	FCR 	{ R AT91C_MC_FCR 	WO }
	PUER 	{ R AT91C_MC_PUER 	RW }
	ASR 	{ R AT91C_MC_ASR 	RO }
	FSR 	{ R AT91C_MC_FSR 	RO }
	FMR 	{ R AT91C_MC_FMR 	RW }
	PUP 	{ R AT91C_MC_PUP 	RW }
	PUIA 	{ R AT91C_MC_PUIA 	RW }
	AASR 	{ R AT91C_MC_AASR 	RO }
	RCR 	{ R AT91C_MC_RCR 	WO }
	listeReg 	{ FCR PUER ASR FSR FMR PUP PUIA AASR RCR  }

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
	RCR 	{ R AT91C_MCI_RCR 	RW }
	PTCR 	{ R AT91C_MCI_PTCR 	WO }
	TNPR 	{ R AT91C_MCI_TNPR 	RW }
	RNPR 	{ R AT91C_MCI_RNPR 	RW }
	TPR 	{ R AT91C_MCI_TPR 	RW }
	RPR 	{ R AT91C_MCI_RPR 	RW }
	PTSR 	{ R AT91C_MCI_PTSR 	RO }
	TNCR 	{ R AT91C_MCI_TNCR 	RW }
	RNCR 	{ R AT91C_MCI_RNCR 	RW }
	TCR 	{ R AT91C_MCI_TCR 	RW }
	listeReg 	{ RCR PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR  }

}
array set PDC_US0_att {
	PTCR 	{ R AT91C_US0_PTCR 	WO }
	TNPR 	{ R AT91C_US0_TNPR 	RW }
	RNPR 	{ R AT91C_US0_RNPR 	RW }
	TPR 	{ R AT91C_US0_TPR 	RW }
	RPR 	{ R AT91C_US0_RPR 	RW }
	PTSR 	{ R AT91C_US0_PTSR 	RO }
	TNCR 	{ R AT91C_US0_TNCR 	RW }
	RNCR 	{ R AT91C_US0_RNCR 	RW }
	TCR 	{ R AT91C_US0_TCR 	RW }
	RCR 	{ R AT91C_US0_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

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
	PTSR 	{ R AT91C_US2_PTSR 	RO }
	TNCR 	{ R AT91C_US2_TNCR 	RW }
	RNCR 	{ R AT91C_US2_RNCR 	RW }
	TCR 	{ R AT91C_US2_TCR 	RW }
	PTCR 	{ R AT91C_US2_PTCR 	WO }
	RCR 	{ R AT91C_US2_RCR 	RW }
	TNPR 	{ R AT91C_US2_TNPR 	RW }
	RPR 	{ R AT91C_US2_RPR 	RW }
	TPR 	{ R AT91C_US2_TPR 	RW }
	RNPR 	{ R AT91C_US2_RNPR 	RW }
	listeReg 	{ PTSR TNCR RNCR TCR PTCR RCR TNPR RPR TPR RNPR  }

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
array set PDC_ADC0_att {
	PTCR 	{ R AT91C_ADC0_PTCR 	WO }
	TNPR 	{ R AT91C_ADC0_TNPR 	RW }
	RNPR 	{ R AT91C_ADC0_RNPR 	RW }
	TPR 	{ R AT91C_ADC0_TPR 	RW }
	RPR 	{ R AT91C_ADC0_RPR 	RW }
	PTSR 	{ R AT91C_ADC0_PTSR 	RO }
	TNCR 	{ R AT91C_ADC0_TNCR 	RW }
	RNCR 	{ R AT91C_ADC0_RNCR 	RW }
	TCR 	{ R AT91C_ADC0_TCR 	RW }
	RCR 	{ R AT91C_ADC0_RCR 	RW }
	listeReg 	{ PTCR TNPR RNPR TPR RPR PTSR TNCR RNCR TCR RCR  }

}
array set PDC_ADC1_att {
	RPR 	{ R AT91C_ADC1_RPR 	RW }
	RCR 	{ R AT91C_ADC1_RCR 	RW }
	PTSR 	{ R AT91C_ADC1_PTSR 	RO }
	TNCR 	{ R AT91C_ADC1_TNCR 	RW }
	RNCR 	{ R AT91C_ADC1_RNCR 	RW }
	TCR 	{ R AT91C_ADC1_TCR 	RW }
	PTCR 	{ R AT91C_ADC1_PTCR 	WO }
	TNPR 	{ R AT91C_ADC1_TNPR 	RW }
	RNPR 	{ R AT91C_ADC1_RNPR 	RW }
	TPR 	{ R AT91C_ADC1_TPR 	RW }
	listeReg 	{ RPR RCR PTSR TNCR RNCR TCR PTCR TNPR RNPR TPR  }

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
	RNPR 	{ R AT91C_SPI1_RNPR 	RW }
	TPR 	{ R AT91C_SPI1_TPR 	RW }
	RPR 	{ R AT91C_SPI1_RPR 	RW }
	PTSR 	{ R AT91C_SPI1_PTSR 	RO }
	RCR 	{ R AT91C_SPI1_RCR 	RW }
	TCR 	{ R AT91C_SPI1_TCR 	RW }
	RNCR 	{ R AT91C_SPI1_RNCR 	RW }
	TNCR 	{ R AT91C_SPI1_TNCR 	RW }
	TNPR 	{ R AT91C_SPI1_TNPR 	RW }
	PTCR 	{ R AT91C_SPI1_PTCR 	WO }
	listeReg 	{ RNPR TPR RPR PTSR RCR TCR RNCR TNCR TNPR PTCR  }

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

# ========== Peripheral attributes for PWMC_CH peripheral ========== 
array set PWMC_CH0_att {
	CUPDR 	{ R AT91C_PWMC_CH0_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH0_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH0_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH0_Reserved 	WO }
	CCNTR 	{ R AT91C_PWMC_CH0_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH0_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}
array set PWMC_CH1_att {
	CUPDR 	{ R AT91C_PWMC_CH1_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH1_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH1_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH1_Reserved 	WO }
	CCNTR 	{ R AT91C_PWMC_CH1_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH1_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}
array set PWMC_CH2_att {
	CUPDR 	{ R AT91C_PWMC_CH2_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH2_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH2_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH2_Reserved 	WO }
	CCNTR 	{ R AT91C_PWMC_CH2_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH2_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}
array set PWMC_CH3_att {
	CUPDR 	{ R AT91C_PWMC_CH3_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH3_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH3_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH3_Reserved 	WO }
	CCNTR 	{ R AT91C_PWMC_CH3_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH3_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}
array set PWMC_CH4_att {
	CUPDR 	{ R AT91C_PWMC_CH4_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH4_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH4_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH4_Reserved 	WO }
	CCNTR 	{ R AT91C_PWMC_CH4_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH4_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}
array set PWMC_CH5_att {
	CUPDR 	{ R AT91C_PWMC_CH5_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH5_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH5_CMR 	RW }
	Reserved 	{ R AT91C_PWMC_CH5_Reserved 	WO }
	CCNTR 	{ R AT91C_PWMC_CH5_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH5_CDTYR 	RW }
	listeReg 	{ CUPDR CPRDR CMR Reserved CCNTR CDTYR  }

}
array set PWMC_CH6_att {
	Reserved 	{ R AT91C_PWMC_CH6_Reserved 	WO }
	CCNTR 	{ R AT91C_PWMC_CH6_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH6_CDTYR 	RW }
	CUPDR 	{ R AT91C_PWMC_CH6_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH6_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH6_CMR 	RW }
	listeReg 	{ Reserved CCNTR CDTYR CUPDR CPRDR CMR  }

}
array set PWMC_CH7_att {
	Reserved 	{ R AT91C_PWMC_CH7_Reserved 	WO }
	CCNTR 	{ R AT91C_PWMC_CH7_CCNTR 	RO }
	CDTYR 	{ R AT91C_PWMC_CH7_CDTYR 	RW }
	CUPDR 	{ R AT91C_PWMC_CH7_CUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH7_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH7_CMR 	RW }
	listeReg 	{ Reserved CCNTR CDTYR CUPDR CPRDR CMR  }

}

# ========== Peripheral attributes for SYS peripheral ========== 
array set SYS_att {
	GPBR1 	{ R AT91C_SYS_GPBR1 	 }
	GPBR0 	{ R AT91C_SYS_GPBR0 	 }
	listeReg 	{ GPBR1 GPBR0  }

}

# ========== Peripheral attributes for SHDWC peripheral ========== 
array set SHDWC_att {
	SHMR 	{ R AT91C_SHDWC_SHMR 	RW }
	SHSR 	{ R AT91C_SHDWC_SHSR 	RO }
	SHCR 	{ R AT91C_SHDWC_SHCR 	WO }
	listeReg 	{ SHMR SHSR SHCR  }

}

# ========== Peripheral attributes for SPI peripheral ========== 
array set SPI0_att {
	CSR 	{ R AT91C_SPI0_CSR 	RW }
	IDR 	{ R AT91C_SPI0_IDR 	WO }
	SR 	{ R AT91C_SPI0_SR 	RO }
	RDR 	{ R AT91C_SPI0_RDR 	RO }
	CR 	{ R AT91C_SPI0_CR 	RO }
	IMR 	{ R AT91C_SPI0_IMR 	RO }
	IER 	{ R AT91C_SPI0_IER 	WO }
	TDR 	{ R AT91C_SPI0_TDR 	WO }
	MR 	{ R AT91C_SPI0_MR 	RW }
	listeReg 	{ CSR IDR SR RDR CR IMR IER TDR MR  }

}
array set SPI1_att {
	CSR 	{ R AT91C_SPI1_CSR 	RW }
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

# ========== Peripheral attributes for SSC peripheral ========== 
array set SSC0_att {
	IMR 	{ R AT91C_SSC0_IMR 	RO }
	IER 	{ R AT91C_SSC0_IER 	WO }
	TSHR 	{ R AT91C_SSC0_TSHR 	RW }
	THR 	{ R AT91C_SSC0_THR 	WO }
	TFMR 	{ R AT91C_SSC0_TFMR 	RW }
	RFMR 	{ R AT91C_SSC0_RFMR 	RW }
	CMR 	{ R AT91C_SSC0_CMR 	RW }
	IDR 	{ R AT91C_SSC0_IDR 	WO }
	SR 	{ R AT91C_SSC0_SR 	RO }
	RSHR 	{ R AT91C_SSC0_RSHR 	RO }
	RHR 	{ R AT91C_SSC0_RHR 	RO }
	TCMR 	{ R AT91C_SSC0_TCMR 	RW }
	RCMR 	{ R AT91C_SSC0_RCMR 	RW }
	CR 	{ R AT91C_SSC0_CR 	WO }
	listeReg 	{ IMR IER TSHR THR TFMR RFMR CMR IDR SR RSHR RHR TCMR RCMR CR  }

}
array set SSC1_att {
	RFMR 	{ R AT91C_SSC1_RFMR 	RW }
	CMR 	{ R AT91C_SSC1_CMR 	RW }
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
	listeReg 	{ RFMR CMR IDR SR RSHR RHR TCMR RCMR CR IMR IER TSHR THR TFMR  }

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
array set TCB2_att {
	BMR 	{ R AT91C_TCB2_BMR 	RW }
	BCR 	{ R AT91C_TCB2_BCR 	WO }
	listeReg 	{ BMR BCR  }

}

# ========== Peripheral attributes for PWMC peripheral ========== 
array set PWMC_att {
	VR 	{ R AT91C_PWMC_VR 	RO }
	ISR 	{ R AT91C_PWMC_ISR 	RO }
	IDR 	{ R AT91C_PWMC_IDR 	WO }
	SR 	{ R AT91C_PWMC_SR 	RO }
	ENA 	{ R AT91C_PWMC_ENA 	WO }
	IMR 	{ R AT91C_PWMC_IMR 	RO }
	MR 	{ R AT91C_PWMC_MR 	RW }
	DIS 	{ R AT91C_PWMC_DIS 	WO }
	IER 	{ R AT91C_PWMC_IER 	WO }
	listeReg 	{ VR ISR IDR SR ENA IMR MR DIS IER  }

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
array set TC3_att {
	IMR 	{ R AT91C_TC3_IMR 	RO }
	CV 	{ R AT91C_TC3_CV 	RW }
	CCR 	{ R AT91C_TC3_CCR 	WO }
	IER 	{ R AT91C_TC3_IER 	WO }
	CMR 	{ R AT91C_TC3_CMR 	RW }
	RA 	{ R AT91C_TC3_RA 	RW }
	RC 	{ R AT91C_TC3_RC 	RW }
	IDR 	{ R AT91C_TC3_IDR 	WO }
	RB 	{ R AT91C_TC3_RB 	RW }
	SR 	{ R AT91C_TC3_SR 	RO }
	listeReg 	{ IMR CV CCR IER CMR RA RC IDR RB SR  }

}
array set TC4_att {
	IMR 	{ R AT91C_TC4_IMR 	RO }
	IER 	{ R AT91C_TC4_IER 	WO }
	RC 	{ R AT91C_TC4_RC 	RW }
	RA 	{ R AT91C_TC4_RA 	RW }
	CMR 	{ R AT91C_TC4_CMR 	RW }
	IDR 	{ R AT91C_TC4_IDR 	WO }
	SR 	{ R AT91C_TC4_SR 	RO }
	RB 	{ R AT91C_TC4_RB 	RW }
	CV 	{ R AT91C_TC4_CV 	RW }
	CCR 	{ R AT91C_TC4_CCR 	WO }
	listeReg 	{ IMR IER RC RA CMR IDR SR RB CV CCR  }

}
array set TC5_att {
	CMR 	{ R AT91C_TC5_CMR 	RW }
	IDR 	{ R AT91C_TC5_IDR 	WO }
	SR 	{ R AT91C_TC5_SR 	RO }
	RB 	{ R AT91C_TC5_RB 	RW }
	CV 	{ R AT91C_TC5_CV 	RW }
	CCR 	{ R AT91C_TC5_CCR 	WO }
	IMR 	{ R AT91C_TC5_IMR 	RO }
	IER 	{ R AT91C_TC5_IER 	WO }
	RC 	{ R AT91C_TC5_RC 	RW }
	RA 	{ R AT91C_TC5_RA 	RW }
	listeReg 	{ CMR IDR SR RB CV CCR IMR IER RC RA  }

}
array set TC6_att {
	IDR 	{ R AT91C_TC6_IDR 	WO }
	SR 	{ R AT91C_TC6_SR 	RO }
	RB 	{ R AT91C_TC6_RB 	RW }
	CV 	{ R AT91C_TC6_CV 	RW }
	CCR 	{ R AT91C_TC6_CCR 	WO }
	IMR 	{ R AT91C_TC6_IMR 	RO }
	IER 	{ R AT91C_TC6_IER 	WO }
	RC 	{ R AT91C_TC6_RC 	RW }
	RA 	{ R AT91C_TC6_RA 	RW }
	CMR 	{ R AT91C_TC6_CMR 	RW }
	listeReg 	{ IDR SR RB CV CCR IMR IER RC RA CMR  }

}
array set TC7_att {
	IDR 	{ R AT91C_TC7_IDR 	WO }
	SR 	{ R AT91C_TC7_SR 	RO }
	RB 	{ R AT91C_TC7_RB 	RW }
	CV 	{ R AT91C_TC7_CV 	RW }
	CCR 	{ R AT91C_TC7_CCR 	WO }
	IMR 	{ R AT91C_TC7_IMR 	RO }
	IER 	{ R AT91C_TC7_IER 	WO }
	RC 	{ R AT91C_TC7_RC 	RW }
	RA 	{ R AT91C_TC7_RA 	RW }
	CMR 	{ R AT91C_TC7_CMR 	RW }
	listeReg 	{ IDR SR RB CV CCR IMR IER RC RA CMR  }

}
array set TC8_att {
	CV 	{ R AT91C_TC8_CV 	RW }
	CCR 	{ R AT91C_TC8_CCR 	WO }
	IMR 	{ R AT91C_TC8_IMR 	RO }
	IER 	{ R AT91C_TC8_IER 	WO }
	RC 	{ R AT91C_TC8_RC 	RW }
	RA 	{ R AT91C_TC8_RA 	RW }
	CMR 	{ R AT91C_TC8_CMR 	RW }
	IDR 	{ R AT91C_TC8_IDR 	WO }
	SR 	{ R AT91C_TC8_SR 	RO }
	RB 	{ R AT91C_TC8_RB 	RW }
	listeReg 	{ CV CCR IMR IER RC RA CMR IDR SR RB  }

}

# ========== Peripheral attributes for PITC peripheral ========== 
array set PITC_att {
	PIIR 	{ R AT91C_PITC_PIIR 	RO }
	PISR 	{ R AT91C_PITC_PISR 	RO }
	PIVR 	{ R AT91C_PITC_PIVR 	RO }
	PIMR 	{ R AT91C_PITC_PIMR 	RW }
	listeReg 	{ PIIR PISR PIVR PIMR  }

}

# ========== Peripheral attributes for ADC peripheral ========== 
array set ADC0_att {
	IMR 	{ R AT91C_ADC0_IMR 	RO }
	CDR4 	{ R AT91C_ADC0_CDR4 	RO }
	CDR2 	{ R AT91C_ADC0_CDR2 	RO }
	CDR0 	{ R AT91C_ADC0_CDR0 	RO }
	CDR7 	{ R AT91C_ADC0_CDR7 	RO }
	CDR1 	{ R AT91C_ADC0_CDR1 	RO }
	CDR3 	{ R AT91C_ADC0_CDR3 	RO }
	CDR5 	{ R AT91C_ADC0_CDR5 	RO }
	MR 	{ R AT91C_ADC0_MR 	RW }
	CDR6 	{ R AT91C_ADC0_CDR6 	RO }
	CR 	{ R AT91C_ADC0_CR 	WO }
	CHER 	{ R AT91C_ADC0_CHER 	WO }
	CHSR 	{ R AT91C_ADC0_CHSR 	RO }
	IER 	{ R AT91C_ADC0_IER 	WO }
	SR 	{ R AT91C_ADC0_SR 	RO }
	CHDR 	{ R AT91C_ADC0_CHDR 	WO }
	IDR 	{ R AT91C_ADC0_IDR 	WO }
	LCDR 	{ R AT91C_ADC0_LCDR 	RO }
	listeReg 	{ IMR CDR4 CDR2 CDR0 CDR7 CDR1 CDR3 CDR5 MR CDR6 CR CHER CHSR IER SR CHDR IDR LCDR  }

}
array set ADC1_att {
	CDR1 	{ R AT91C_ADC1_CDR1 	RO }
	IMR 	{ R AT91C_ADC1_IMR 	RO }
	IER 	{ R AT91C_ADC1_IER 	WO }
	SR 	{ R AT91C_ADC1_SR 	RO }
	CDR2 	{ R AT91C_ADC1_CDR2 	RO }
	CDR0 	{ R AT91C_ADC1_CDR0 	RO }
	CDR3 	{ R AT91C_ADC1_CDR3 	RO }
	CDR6 	{ R AT91C_ADC1_CDR6 	RO }
	CDR4 	{ R AT91C_ADC1_CDR4 	RO }
	CR 	{ R AT91C_ADC1_CR 	WO }
	CDR7 	{ R AT91C_ADC1_CDR7 	RO }
	CDR5 	{ R AT91C_ADC1_CDR5 	RO }
	CHDR 	{ R AT91C_ADC1_CHDR 	WO }
	MR 	{ R AT91C_ADC1_MR 	RW }
	IDR 	{ R AT91C_ADC1_IDR 	WO }
	LCDR 	{ R AT91C_ADC1_LCDR 	RO }
	CHSR 	{ R AT91C_ADC1_CHSR 	RO }
	CHER 	{ R AT91C_ADC1_CHER 	WO }
	listeReg 	{ CDR1 IMR IER SR CDR2 CDR0 CDR3 CDR6 CDR4 CR CDR7 CDR5 CHDR MR IDR LCDR CHSR CHER  }

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
	MOR 	{ R AT91C_PMC_MOR 	RW }
	PCER 	{ R AT91C_PMC_PCER 	WO }
	PCSR 	{ R AT91C_PMC_PCSR 	RO }
	PLLR 	{ R AT91C_PMC_PLLR 	RW }
	MCFR 	{ R AT91C_PMC_MCFR 	RO }
	PCKR 	{ R AT91C_PMC_PCKR 	RW }
	listeReg 	{ SCSR SCER IMR IDR PCDR SCDR SR IER MCKR MOR PCER PCSR PLLR MCFR PCKR  }

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
	PLLR 	{ R AT91C_CKGR_PLLR 	RW }
	MCFR 	{ R AT91C_CKGR_MCFR 	RO }
	MOR 	{ R AT91C_CKGR_MOR 	RW }
	listeReg 	{ PLLR MCFR MOR  }

}

# ========== Peripheral attributes for CAN_MB peripheral ========== 
array set CAN0_MB0_att {
	MDH 	{ R AT91C_CAN0_MB0_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB0_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB0_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB0_MMR 	RW }
	MCR 	{ R AT91C_CAN0_MB0_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB0_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB0_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB0_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN0_MB1_att {
	MDH 	{ R AT91C_CAN0_MB1_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB1_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB1_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB1_MMR 	RW }
	MCR 	{ R AT91C_CAN0_MB1_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB1_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB1_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB1_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN0_MB2_att {
	MDH 	{ R AT91C_CAN0_MB2_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB2_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB2_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB2_MMR 	RW }
	MCR 	{ R AT91C_CAN0_MB2_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB2_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB2_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB2_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN0_MB3_att {
	MDH 	{ R AT91C_CAN0_MB3_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB3_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB3_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB3_MMR 	RW }
	MCR 	{ R AT91C_CAN0_MB3_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB3_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB3_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB3_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN0_MB4_att {
	MDH 	{ R AT91C_CAN0_MB4_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB4_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB4_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB4_MMR 	RW }
	MCR 	{ R AT91C_CAN0_MB4_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB4_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB4_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB4_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN0_MB5_att {
	MSR 	{ R AT91C_CAN0_MB5_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB5_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB5_MMR 	RW }
	MCR 	{ R AT91C_CAN0_MB5_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB5_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB5_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB5_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB5_MDH 	RW }
	listeReg 	{ MSR MID MMR MCR MDL MFID MAM MDH  }

}
array set CAN0_MB6_att {
	MCR 	{ R AT91C_CAN0_MB6_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB6_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB6_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB6_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB6_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB6_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB6_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB6_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN0_MB7_att {
	MCR 	{ R AT91C_CAN0_MB7_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB7_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB7_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB7_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB7_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB7_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB7_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB7_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN0_MB8_att {
	MCR 	{ R AT91C_CAN0_MB8_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB8_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB8_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB8_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB8_MDH 	RW }
	MMR 	{ R AT91C_CAN0_MB8_MMR 	RW }
	MID 	{ R AT91C_CAN0_MB8_MID 	RW }
	MSR 	{ R AT91C_CAN0_MB8_MSR 	RO }
	listeReg 	{ MCR MDL MFID MAM MDH MMR MID MSR  }

}
array set CAN0_MB9_att {
	MCR 	{ R AT91C_CAN0_MB9_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB9_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB9_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB9_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB9_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB9_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB9_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB9_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN0_MB10_att {
	MCR 	{ R AT91C_CAN0_MB10_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB10_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB10_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB10_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB10_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB10_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB10_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB10_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN0_MB11_att {
	MCR 	{ R AT91C_CAN0_MB11_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB11_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB11_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB11_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB11_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB11_MSR 	RO }
	MMR 	{ R AT91C_CAN0_MB11_MMR 	RW }
	MID 	{ R AT91C_CAN0_MB11_MID 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MMR MID  }

}
array set CAN0_MB12_att {
	MCR 	{ R AT91C_CAN0_MB12_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB12_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB12_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB12_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB12_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB12_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB12_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB12_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN0_MB13_att {
	MCR 	{ R AT91C_CAN0_MB13_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB13_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB13_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB13_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB13_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB13_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB13_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB13_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN0_MB14_att {
	MCR 	{ R AT91C_CAN0_MB14_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB14_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB14_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB14_MAM 	RW }
	MDH 	{ R AT91C_CAN0_MB14_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB14_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB14_MID 	RW }
	MMR 	{ R AT91C_CAN0_MB14_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN0_MB15_att {
	MMR 	{ R AT91C_CAN0_MB15_MMR 	RW }
	MDH 	{ R AT91C_CAN0_MB15_MDH 	RW }
	MSR 	{ R AT91C_CAN0_MB15_MSR 	RO }
	MID 	{ R AT91C_CAN0_MB15_MID 	RW }
	MCR 	{ R AT91C_CAN0_MB15_MCR 	WO }
	MDL 	{ R AT91C_CAN0_MB15_MDL 	RW }
	MFID 	{ R AT91C_CAN0_MB15_MFID 	RO }
	MAM 	{ R AT91C_CAN0_MB15_MAM 	RW }
	listeReg 	{ MMR MDH MSR MID MCR MDL MFID MAM  }

}
array set CAN1_MB0_att {
	MDH 	{ R AT91C_CAN1_MB0_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB0_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB0_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB0_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB0_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB0_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB0_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB0_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB1_att {
	MDH 	{ R AT91C_CAN1_MB1_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB1_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB1_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB1_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB1_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB1_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB1_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB1_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB2_att {
	MDH 	{ R AT91C_CAN1_MB2_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB2_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB2_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB2_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB2_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB2_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB2_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB2_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB3_att {
	MCR 	{ R AT91C_CAN1_MB3_MCR 	WO }
	MFID 	{ R AT91C_CAN1_MB3_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB3_MAM 	RW }
	MMR 	{ R AT91C_CAN1_MB3_MMR 	RW }
	MDH 	{ R AT91C_CAN1_MB3_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB3_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB3_MID 	RW }
	MDL 	{ R AT91C_CAN1_MB3_MDL 	RW }
	listeReg 	{ MCR MFID MAM MMR MDH MSR MID MDL  }

}
array set CAN1_MB4_att {
	MCR 	{ R AT91C_CAN1_MB4_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB4_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB4_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB4_MAM 	RW }
	MDH 	{ R AT91C_CAN1_MB4_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB4_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB4_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB4_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN1_MB5_att {
	MCR 	{ R AT91C_CAN1_MB5_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB5_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB5_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB5_MAM 	RW }
	MDH 	{ R AT91C_CAN1_MB5_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB5_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB5_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB5_MMR 	RW }
	listeReg 	{ MCR MDL MFID MAM MDH MSR MID MMR  }

}
array set CAN1_MB6_att {
	MDH 	{ R AT91C_CAN1_MB6_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB6_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB6_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB6_MMR 	RW }
	MAM 	{ R AT91C_CAN1_MB6_MAM 	RW }
	MCR 	{ R AT91C_CAN1_MB6_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB6_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB6_MFID 	RO }
	listeReg 	{ MDH MSR MID MMR MAM MCR MDL MFID  }

}
array set CAN1_MB7_att {
	MDH 	{ R AT91C_CAN1_MB7_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB7_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB7_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB7_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB7_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB7_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB7_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB7_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB8_att {
	MDH 	{ R AT91C_CAN1_MB8_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB8_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB8_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB8_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB8_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB8_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB8_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB8_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB9_att {
	MID 	{ R AT91C_CAN1_MB9_MID 	RW }
	MDH 	{ R AT91C_CAN1_MB9_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB9_MSR 	RO }
	MMR 	{ R AT91C_CAN1_MB9_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB9_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB9_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB9_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB9_MAM 	RW }
	listeReg 	{ MID MDH MSR MMR MCR MDL MFID MAM  }

}
array set CAN1_MB10_att {
	MDH 	{ R AT91C_CAN1_MB10_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB10_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB10_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB10_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB10_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB10_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB10_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB10_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB11_att {
	MDH 	{ R AT91C_CAN1_MB11_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB11_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB11_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB11_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB11_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB11_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB11_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB11_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB12_att {
	MDH 	{ R AT91C_CAN1_MB12_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB12_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB12_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB12_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB12_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB12_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB12_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB12_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB13_att {
	MDH 	{ R AT91C_CAN1_MB13_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB13_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB13_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB13_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB13_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB13_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB13_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB13_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB14_att {
	MDH 	{ R AT91C_CAN1_MB14_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB14_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB14_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB14_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB14_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB14_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB14_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB14_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

}
array set CAN1_MB15_att {
	MDH 	{ R AT91C_CAN1_MB15_MDH 	RW }
	MSR 	{ R AT91C_CAN1_MB15_MSR 	RO }
	MID 	{ R AT91C_CAN1_MB15_MID 	RW }
	MMR 	{ R AT91C_CAN1_MB15_MMR 	RW }
	MCR 	{ R AT91C_CAN1_MB15_MCR 	WO }
	MDL 	{ R AT91C_CAN1_MB15_MDL 	RW }
	MFID 	{ R AT91C_CAN1_MB15_MFID 	RO }
	MAM 	{ R AT91C_CAN1_MB15_MAM 	RW }
	listeReg 	{ MDH MSR MID MMR MCR MDL MFID MAM  }

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

# ========== Peripheral attributes for RTTC peripheral ========== 
array set RTTC_att {
	RTSR 	{ R AT91C_RTTC_RTSR 	RO }
	RTAR 	{ R AT91C_RTTC_RTAR 	RW }
	RTVR 	{ R AT91C_RTTC_RTVR 	RO }
	RTMR 	{ R AT91C_RTTC_RTMR 	RW }
	listeReg 	{ RTSR RTAR RTVR RTMR  }

}

# ========== Peripheral attributes for TWI peripheral ========== 
array set TWI_att {
	RHR 	{ R AT91C_TWI_RHR 	RO }
	IDR 	{ R AT91C_TWI_IDR 	WO }
	SR 	{ R AT91C_TWI_SR 	RO }
	CWGR 	{ R AT91C_TWI_CWGR 	RW }
	CR 	{ R AT91C_TWI_CR 	WO }
	THR 	{ R AT91C_TWI_THR 	WO }
	IMR 	{ R AT91C_TWI_IMR 	RO }
	IER 	{ R AT91C_TWI_IER 	WO }
	IADR 	{ R AT91C_TWI_IADR 	RW }
	MMR 	{ R AT91C_TWI_MMR 	RW }
	listeReg 	{ RHR IDR SR CWGR CR THR IMR IER IADR MMR  }

}

# ========== Peripheral attributes for USART peripheral ========== 
array set US0_att {
	TTGR 	{ R AT91C_US0_TTGR 	RW }
	BRGR 	{ R AT91C_US0_BRGR 	RW }
	RHR 	{ R AT91C_US0_RHR 	RO }
	IMR 	{ R AT91C_US0_IMR 	RO }
	NER 	{ R AT91C_US0_NER 	RO }
	RTOR 	{ R AT91C_US0_RTOR 	RW }
	FIDI 	{ R AT91C_US0_FIDI 	RW }
	CR 	{ R AT91C_US0_CR 	WO }
	IER 	{ R AT91C_US0_IER 	WO }
	IF 	{ R AT91C_US0_IF 	RW }
	MR 	{ R AT91C_US0_MR 	RW }
	IDR 	{ R AT91C_US0_IDR 	WO }
	CSR 	{ R AT91C_US0_CSR 	RO }
	THR 	{ R AT91C_US0_THR 	WO }
	listeReg 	{ TTGR BRGR RHR IMR NER RTOR FIDI CR IER IF MR IDR CSR THR  }

}
array set US1_att {
	RHR 	{ R AT91C_US1_RHR 	RO }
	IMR 	{ R AT91C_US1_IMR 	RO }
	IER 	{ R AT91C_US1_IER 	WO }
	CR 	{ R AT91C_US1_CR 	WO }
	RTOR 	{ R AT91C_US1_RTOR 	RW }
	THR 	{ R AT91C_US1_THR 	WO }
	CSR 	{ R AT91C_US1_CSR 	RO }
	IDR 	{ R AT91C_US1_IDR 	WO }
	FIDI 	{ R AT91C_US1_FIDI 	RW }
	BRGR 	{ R AT91C_US1_BRGR 	RW }
	TTGR 	{ R AT91C_US1_TTGR 	RW }
	IF 	{ R AT91C_US1_IF 	RW }
	NER 	{ R AT91C_US1_NER 	RO }
	MR 	{ R AT91C_US1_MR 	RW }
	listeReg 	{ RHR IMR IER CR RTOR THR CSR IDR FIDI BRGR TTGR IF NER MR  }

}
array set US2_att {
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
	listeReg 	{ FIDI TTGR BRGR RHR IMR IER CR IF NER RTOR THR CSR IDR MR  }

}

# ========== Peripheral attributes for MCI peripheral ========== 
array set MCI_att {
	IER 	{ R AT91C_MCI_IER 	WO }
	TDR 	{ R AT91C_MCI_TDR 	RO }
	IDR 	{ R AT91C_MCI_IDR 	WO }
	SR 	{ R AT91C_MCI_SR 	RO }
	DTOR 	{ R AT91C_MCI_DTOR 	RW }
	CR 	{ R AT91C_MCI_CR 	WO }
	IMR 	{ R AT91C_MCI_IMR 	RO }
	MR 	{ R AT91C_MCI_MR 	RW }
	SDCR 	{ R AT91C_MCI_SDCR 	RW }
	CMDR 	{ R AT91C_MCI_CMDR 	WO }
	ARGR 	{ R AT91C_MCI_ARGR 	RW }
	RSPR 	{ R AT91C_MCI_RSPR 	RO }
	RDR 	{ R AT91C_MCI_RDR 	RO }
	listeReg 	{ IER TDR IDR SR DTOR CR IMR MR SDCR CMDR ARGR RSPR RDR  }

}

# ========== Peripheral attributes for WDTC peripheral ========== 
array set WDTC_att {
	WDMR 	{ R AT91C_WDTC_WDMR 	RW }
	WDSR 	{ R AT91C_WDTC_WDSR 	RO }
	WDCR 	{ R AT91C_WDTC_WDCR 	WO }
	listeReg 	{ WDMR WDSR WDCR  }

}

# ========== Peripheral attributes for UDP peripheral ========== 
array set UDP_att {
	TXVC 	{ R AT91C_UDP_TXVC 	RW }
	ISR 	{ R AT91C_UDP_ISR 	RO }
	IDR 	{ R AT91C_UDP_IDR 	WO }
	CSR 	{ R AT91C_UDP_CSR 	RW }
	RSTEP 	{ R AT91C_UDP_RSTEP 	RO }
	ICR 	{ R AT91C_UDP_ICR 	RO }
	GLBSTATE 	{ R AT91C_UDP_GLBSTATE 	RW }
	NUM 	{ R AT91C_UDP_NUM 	RO }
	FADDR 	{ R AT91C_UDP_FADDR 	RW }
	IER 	{ R AT91C_UDP_IER 	WO }
	IMR 	{ R AT91C_UDP_IMR 	RO }
	FDR 	{ R AT91C_UDP_FDR 	RW }
	listeReg 	{ TXVC ISR IDR CSR RSTEP ICR GLBSTATE NUM FADDR IER IMR FDR  }

}

# ========== Peripheral attributes for AIC peripheral ========== 
array set AIC_att {
	ICCR 	{ R AT91C_AIC_ICCR 	WO }
	IECR 	{ R AT91C_AIC_IECR 	WO }
	SMR 	{ R AT91C_AIC_SMR 	RW }
	ISCR 	{ R AT91C_AIC_ISCR 	WO }
	EOICR 	{ R AT91C_AIC_EOICR 	WO }
	DCR 	{ R AT91C_AIC_DCR 	RW }
	FFER 	{ R AT91C_AIC_FFER 	WO }
	SVR 	{ R AT91C_AIC_SVR 	RW }
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
array set CAN0_att {
	TCR 	{ R AT91C_CAN0_TCR 	WO }
	TIMESTP 	{ R AT91C_CAN0_TIMESTP 	RO }
	BR 	{ R AT91C_CAN0_BR 	RW }
	ACR 	{ R AT91C_CAN0_ACR 	WO }
	VR 	{ R AT91C_CAN0_VR 	RO }
	IER 	{ R AT91C_CAN0_IER 	WO }
	IMR 	{ R AT91C_CAN0_IMR 	RO }
	MR 	{ R AT91C_CAN0_MR 	RW }
	IDR 	{ R AT91C_CAN0_IDR 	WO }
	SR 	{ R AT91C_CAN0_SR 	RO }
	TIM 	{ R AT91C_CAN0_TIM 	RO }
	ECR 	{ R AT91C_CAN0_ECR 	RO }
	listeReg 	{ TCR TIMESTP BR ACR VR IER IMR MR IDR SR TIM ECR  }

}
array set CAN1_att {
	MR 	{ R AT91C_CAN1_MR 	RW }
	VR 	{ R AT91C_CAN1_VR 	RO }
	TIMESTP 	{ R AT91C_CAN1_TIMESTP 	RO }
	BR 	{ R AT91C_CAN1_BR 	RW }
	IMR 	{ R AT91C_CAN1_IMR 	RO }
	IER 	{ R AT91C_CAN1_IER 	WO }
	ACR 	{ R AT91C_CAN1_ACR 	WO }
	ECR 	{ R AT91C_CAN1_ECR 	RO }
	TIM 	{ R AT91C_CAN1_TIM 	RO }
	SR 	{ R AT91C_CAN1_SR 	RO }
	TCR 	{ R AT91C_CAN1_TCR 	WO }
	IDR 	{ R AT91C_CAN1_IDR 	WO }
	listeReg 	{ MR VR TIMESTP BR IMR IER ACR ECR TIM SR TCR IDR  }

}

# ========== PIO information ========== 

array set def_PIOA_att {
 	PA0 	{  TWD   ADTRG0  }
 	PA1 	{  TWCK   ADTRG1  }
 	PA10 	{  TXD2   SPI1_SPCK  }
 	PA11 	{  SPI0_NPCS0  }
 	PA12 	{  SPI0_NPCS1   MCDA1  }
 	PA13 	{  SPI0_NPCS2   MCDA2  }
 	PA14 	{  SPI0_NPCS3   MCDA3  }
 	PA15 	{  SPI0_MISO   MCDA0  }
 	PA16 	{  SPI0_MOSI   MCCDA  }
 	PA17 	{  SPI0_SPCK   MCCK  }
 	PA18 	{  PWM0   PCK0  }
 	PA19 	{  PWM1   PCK1  }
 	PA2 	{  RXD0  }
 	PA20 	{  PWM2   PCK2  }
 	PA21 	{  PWM3   PCK3  }
 	PA22 	{  PWM4   IRQ0  }
 	PA23 	{  PWM5   IRQ1  }
 	PA24 	{  PWM6   TCLK4  }
 	PA25 	{  PWM7   TCLK5  }
 	PA26 	{  CANRX0  }
 	PA27 	{  CANTX0  }
 	PA28 	{  CANRX1   TCLK3  }
 	PA29 	{  CANTX1   TCLK6  }
 	PA3 	{  TXD0  }
 	PA30 	{  DRXD   TCLK7  }
 	PA31 	{  DTXD   TCLK8  }
 	PA4 	{  SCK0   SPI1_NPCS0  }
 	PA5 	{  RTS0   SPI1_NPCS1  }
 	PA6 	{  CTS0   SPI1_NPCS2  }
 	PA7 	{  RXD1   SPI1_NPCS3  }
 	PA8 	{  TXD1   SPI1_MISO  }
 	PA9 	{  RXD2   SPI1_MOSI  }
 }

array set def_PIOB_att {
 	PB0 	{  IRQ2   PWM5  }
 	PB1 	{  IRQ3   PWM6  }
 	PB10 	{  TCLK1   RK1  }
 	PB11 	{  TCLK2   RF1  }
 	PB12 	{  TIOA0   TD1  }
 	PB13 	{  TIOB0   RD1  }
 	PB14 	{  TIOA1   PWM0  }
 	PB15 	{  TIOB1   PWM1  }
 	PB16 	{  TIOA2   PWM2  }
 	PB17 	{  TIOB2   PWM3  }
 	PB18 	{  TIOA3   PWM4  }
 	PB19 	{  TIOB3   SPI1_NPCS1  }
 	PB2 	{  TF0   PWM7  }
 	PB20 	{  TIOA4   SPI1_NPCS2  }
 	PB21 	{  TIOB4   SPI1_NPCS3  }
 	PB22 	{  TIOA5  }
 	PB23 	{  TIOB5  }
 	PB24 	{  TIOA6   RTS1  }
 	PB25 	{  TIOB6   CTS1  }
 	PB26 	{  TIOA7   SCK1  }
 	PB27 	{  TIOB7   RTS2  }
 	PB28 	{  TIOA8   CTS2  }
 	PB29 	{  TIOB8   SCK2  }
 	PB3 	{  TK0   PCK0  }
 	PB4 	{  TD0   PCK1  }
 	PB5 	{  RD0   PCK2  }
 	PB6 	{  RK0   PCK3  }
 	PB7 	{  RF0   CANTX1  }
 	PB8 	{  FIQ   TF1  }
 	PB9 	{  TCLK0   TK1  }
 }
