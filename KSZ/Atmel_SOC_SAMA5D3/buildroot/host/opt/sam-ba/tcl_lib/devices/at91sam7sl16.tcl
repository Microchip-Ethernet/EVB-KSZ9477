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
# File Name           : AT91SAM7SL16.tcl
# Object              : AT91SAM7SL16 definitions
# Generated           : AT91 SW Application Group  01/14/2009 (09:01:10)
# # ----------------------------------------------------------------------------


# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR System Peripherals
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
# *****************************************************************************
# -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- 
set AT91C_AIC_PRIOR       [expr 0x7 <<  0 ]
set 	AT91C_AIC_PRIOR_LOWEST               0x0
set 	AT91C_AIC_PRIOR_HIGHEST              0x7
set AT91C_AIC_SRCTYPE     [expr 0x3 <<  5 ]
set 	AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL       [expr 0x0 <<  5 ]
set 	AT91C_AIC_SRCTYPE_EXT_LOW_LEVEL        [expr 0x0 <<  5 ]
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
set AT91C_CKGR_MAINCKON   [expr 0x1 <<  0 ]
set AT91C_CKGR_FKEY       [expr 0xFF << 16 ]
set AT91C_CKGR_MCKSEL     [expr 0x1 << 24 ]
# -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLR : (CKGR Offset: 0x8) PLL A Register -------- 
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

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Power Management Controler
# *****************************************************************************
# -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
# -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
# -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
# -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
set AT91C_CKGR_MAINCKON   [expr 0x1 <<  0 ]
set AT91C_CKGR_FKEY       [expr 0xFF << 16 ]
set AT91C_CKGR_MCKSEL     [expr 0x1 << 24 ]
# -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLR : (PMC Offset: 0x28) PLL A Register -------- 
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
# -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x3 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLL_CLK              0x2
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
set 	AT91C_PMC_CSS_PLL_CLK              0x2
set AT91C_PMC_PRES        [expr 0x7 <<  2 ]
set 	AT91C_PMC_PRES_CLK                  [expr 0x0 <<  2 ]
set 	AT91C_PMC_PRES_CLK_2                [expr 0x1 <<  2 ]
set 	AT91C_PMC_PRES_CLK_4                [expr 0x2 <<  2 ]
set 	AT91C_PMC_PRES_CLK_8                [expr 0x3 <<  2 ]
set 	AT91C_PMC_PRES_CLK_16               [expr 0x4 <<  2 ]
set 	AT91C_PMC_PRES_CLK_32               [expr 0x5 <<  2 ]
set 	AT91C_PMC_PRES_CLK_64               [expr 0x6 <<  2 ]
# -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
set AT91C_PMC_MAINSELS    [expr 0x1 <<  0 ]
set AT91C_PMC_LOCK        [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
# -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
set AT91C_PMC_MAINSELS    [expr 0x1 <<  0 ]
set AT91C_PMC_LOCK        [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
# -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
set AT91C_PMC_MAINSELS    [expr 0x1 <<  0 ]
set AT91C_PMC_LOCK        [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]
# -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 
set AT91C_PMC_MAINSELS    [expr 0x1 <<  0 ]
set AT91C_PMC_LOCK        [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_PCK0RDY     [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1RDY     [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2RDY     [expr 0x1 << 10 ]

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
set AT91C_RSTC_BODSTS     [expr 0x1 <<  1 ]
set AT91C_RSTC_RSTTYP     [expr 0x7 <<  8 ]
set 	AT91C_RSTC_RSTTYP_POWERUP              [expr 0x0 <<  8 ]
set 	AT91C_RSTC_RSTTYP_WAKEUP               [expr 0x1 <<  8 ]
set 	AT91C_RSTC_RSTTYP_WATCHDOG             [expr 0x2 <<  8 ]
set 	AT91C_RSTC_RSTTYP_SOFTWARE             [expr 0x3 <<  8 ]
set 	AT91C_RSTC_RSTTYP_USER                 [expr 0x4 <<  8 ]
set 	AT91C_RSTC_RSTTYP_BROWNOUT             [expr 0x5 <<  8 ]
set AT91C_RSTC_NRSTL      [expr 0x1 << 16 ]
set AT91C_RSTC_SRCMP      [expr 0x1 << 17 ]
# -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- 
set AT91C_RSTC_URSTEN     [expr 0x1 <<  0 ]
set AT91C_RSTC_URSTIEN    [expr 0x1 <<  4 ]
set AT91C_RSTC_ERSTL      [expr 0xF <<  8 ]
set AT91C_RSTC_BODIEN     [expr 0x1 << 16 ]
set AT91C_RSTC_KEY        [expr 0xFF << 24 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Supply Controller Interface
# *****************************************************************************
# -------- SUPC_CR : (SUPC Offset: 0x0) Control Register -------- 
set AT91C_SUPC_SHDW       [expr 0x1 <<  0 ]
set AT91C_SUPC_SHDWEOF    [expr 0x1 <<  1 ]
set AT91C_SUPC_VROFF      [expr 0x1 <<  2 ]
set AT91C_SUPC_XTALSEL    [expr 0x1 <<  3 ]
set AT91C_SUPC_KEY        [expr 0xFF << 24 ]
# -------- SUPC_BOMR : (SUPC Offset: 0x4) Brown Out Mode Register -------- 
set AT91C_SUPC_BODTH      [expr 0xF <<  0 ]
set AT91C_SUPC_BODSMPL    [expr 0x7 <<  8 ]
set 	AT91C_SUPC_BODSMPL_DISABLED             [expr 0x0 <<  8 ]
set 	AT91C_SUPC_BODSMPL_CONTINUOUS           [expr 0x1 <<  8 ]
set 	AT91C_SUPC_BODSMPL_32_SLCK              [expr 0x2 <<  8 ]
set 	AT91C_SUPC_BODSMPL_256_SLCK             [expr 0x3 <<  8 ]
set 	AT91C_SUPC_BODSMPL_2048_SLCK            [expr 0x4 <<  8 ]
set AT91C_SUPC_BODRSTEN   [expr 0x1 << 12 ]
# -------- SUPC_MR : (SUPC Offset: 0x8) Supply Controller Mode Register -------- 
set AT91C_SUPC_LCDOUT     [expr 0xF <<  0 ]
set AT91C_SUPC_LCDMODE    [expr 0x3 <<  4 ]
set 	AT91C_SUPC_LCDMODE_OFF                  [expr 0x0 <<  4 ]
set 	AT91C_SUPC_LCDMODE_OFF_AFTER_EOF        [expr 0x1 <<  4 ]
set 	AT91C_SUPC_LCDMODE_EXTERNAL             [expr 0x2 <<  4 ]
set 	AT91C_SUPC_LCDMODE_INTERNAL             [expr 0x3 <<  4 ]
set AT91C_SUPC_VRDEEP     [expr 0x1 <<  8 ]
set AT91C_SUPC_VRVDD      [expr 0x7 <<  9 ]
set AT91C_SUPC_VRRSTEN    [expr 0x1 << 12 ]
set AT91C_SUPC_SRAMON     [expr 0x1 << 17 ]
set AT91C_SUPC_RTCON      [expr 0x1 << 18 ]
set AT91C_SUPC_FLASHON    [expr 0x1 << 19 ]
set AT91C_SUPC_BYPASS     [expr 0x1 << 20 ]
set AT91C_SUPC_MKEY       [expr 0xFF << 24 ]
# -------- SUPC_WUMR : (SUPC Offset: 0xc) Wake Up Mode Register -------- 
set AT91C_SUPC_FWUPEN     [expr 0x1 <<  0 ]
set AT91C_SUPC_BODEN      [expr 0x1 <<  1 ]
set AT91C_SUPC_RTTEN      [expr 0x1 <<  2 ]
set AT91C_SUPC_RTCEN      [expr 0x1 <<  3 ]
set AT91C_SUPC_FWUPDBC    [expr 0x7 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_IMMEDIATE            [expr 0x0 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_3_SLCK               [expr 0x1 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_32_SLCK              [expr 0x2 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_512_SLCK             [expr 0x3 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_4096_SLCK            [expr 0x4 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_32768_SLCK           [expr 0x5 <<  8 ]
set AT91C_SUPC_WKUPDBC    [expr 0x7 << 12 ]
set 	AT91C_SUPC_WKUPDBC_IMMEDIATE            [expr 0x0 << 12 ]
set 	AT91C_SUPC_WKUPDBC_3_SLCK               [expr 0x1 << 12 ]
set 	AT91C_SUPC_WKUPDBC_32_SLCK              [expr 0x2 << 12 ]
set 	AT91C_SUPC_WKUPDBC_512_SLCK             [expr 0x3 << 12 ]
set 	AT91C_SUPC_WKUPDBC_4096_SLCK            [expr 0x4 << 12 ]
set 	AT91C_SUPC_WKUPDBC_32768_SLCK           [expr 0x5 << 12 ]
# -------- SUPC_WUIR : (SUPC Offset: 0x10) Wake Up Inputs Register -------- 
set AT91C_SUPC_WKUPEN0    [expr 0x1 <<  0 ]
set AT91C_SUPC_WKUPEN1    [expr 0x1 <<  1 ]
set AT91C_SUPC_WKUPEN2    [expr 0x1 <<  2 ]
set AT91C_SUPC_WKUPEN3    [expr 0x1 <<  3 ]
set AT91C_SUPC_WKUPEN4    [expr 0x1 <<  4 ]
set AT91C_SUPC_WKUPEN5    [expr 0x1 <<  5 ]
set AT91C_SUPC_WKUPEN6    [expr 0x1 <<  6 ]
set AT91C_SUPC_WKUPEN7    [expr 0x1 <<  7 ]
set AT91C_SUPC_WKUPEN8    [expr 0x1 <<  8 ]
set AT91C_SUPC_WKUPEN9    [expr 0x1 <<  9 ]
set AT91C_SUPC_WKUPEN10   [expr 0x1 << 10 ]
set AT91C_SUPC_WKUPEN11   [expr 0x1 << 11 ]
set AT91C_SUPC_WKUPEN12   [expr 0x1 << 12 ]
set AT91C_SUPC_WKUPEN13   [expr 0x1 << 13 ]
set AT91C_SUPC_WKUPEN14   [expr 0x1 << 14 ]
set AT91C_SUPC_WKUPEN15   [expr 0x1 << 15 ]
set AT91C_SUPC_WKUPT0     [expr 0x1 << 16 ]
set AT91C_SUPC_WKUPT1     [expr 0x1 << 17 ]
set AT91C_SUPC_WKUPT2     [expr 0x1 << 18 ]
set AT91C_SUPC_WKUPT3     [expr 0x1 << 19 ]
set AT91C_SUPC_WKUPT4     [expr 0x1 << 20 ]
set AT91C_SUPC_WKUPT5     [expr 0x1 << 21 ]
set AT91C_SUPC_WKUPT6     [expr 0x1 << 22 ]
set AT91C_SUPC_WKUPT7     [expr 0x1 << 23 ]
set AT91C_SUPC_WKUPT8     [expr 0x1 << 24 ]
set AT91C_SUPC_WKUPT9     [expr 0x1 << 25 ]
set AT91C_SUPC_WKUPT10    [expr 0x1 << 26 ]
set AT91C_SUPC_WKUPT11    [expr 0x1 << 27 ]
set AT91C_SUPC_WKUPT12    [expr 0x1 << 28 ]
set AT91C_SUPC_WKUPT13    [expr 0x1 << 29 ]
set AT91C_SUPC_WKUPT14    [expr 0x1 << 30 ]
set AT91C_SUPC_WKUPT15    [expr 0x1 << 31 ]
# -------- SUPC_SR : (SUPC Offset: 0x14) Status Register -------- 
set AT91C_SUPC_FWUPS      [expr 0x1 <<  0 ]
set AT91C_SUPC_WKUPS      [expr 0x1 <<  1 ]
set AT91C_SUPC_BODWS      [expr 0x1 <<  2 ]
set AT91C_SUPC_VRRSTS     [expr 0x1 <<  3 ]
set AT91C_SUPC_BODRSTS    [expr 0x1 <<  4 ]
set AT91C_SUPC_BODS       [expr 0x1 <<  5 ]
set AT91C_SUPC_BROWNOUT   [expr 0x1 <<  6 ]
set AT91C_SUPC_OSCSEL     [expr 0x1 <<  7 ]
set AT91C_SUPC_LCDS       [expr 0x1 <<  8 ]
set AT91C_SUPC_GPBRS      [expr 0x1 <<  9 ]
set AT91C_SUPC_RTS        [expr 0x1 << 10 ]
set AT91C_SUPC_FLASHS     [expr 0x1 << 11 ]
set AT91C_SUPC_WKUPIS0    [expr 0x1 << 16 ]
set AT91C_SUPC_WKUPIS1    [expr 0x1 << 17 ]
set AT91C_SUPC_WKUPIS2    [expr 0x1 << 18 ]
set AT91C_SUPC_WKUPIS3    [expr 0x1 << 19 ]
set AT91C_SUPC_WKUPIS4    [expr 0x1 << 20 ]
set AT91C_SUPC_WKUPIS5    [expr 0x1 << 21 ]
set AT91C_SUPC_WKUPIS6    [expr 0x1 << 22 ]
set AT91C_SUPC_WKUPIS7    [expr 0x1 << 23 ]
set AT91C_SUPC_WKUPIS8    [expr 0x1 << 24 ]
set AT91C_SUPC_WKUPIS9    [expr 0x1 << 25 ]
set AT91C_SUPC_WKUPIS10   [expr 0x1 << 26 ]
set AT91C_SUPC_WKUPIS11   [expr 0x1 << 27 ]
set AT91C_SUPC_WKUPIS12   [expr 0x1 << 28 ]
set AT91C_SUPC_WKUPIS13   [expr 0x1 << 29 ]
set AT91C_SUPC_WKUPIS14   [expr 0x1 << 30 ]
set AT91C_SUPC_WKUPIS15   [expr 0x1 << 31 ]
# -------- SUPC_FWUTR : (SUPC Offset: 0x18) Flash Wake Up Timer Register -------- 
set AT91C_SUPC_FWUT       [expr 0x3FF <<  0 ]

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
#              SOFTWARE API DEFINITION  FOR Memory Controller Interface
# *****************************************************************************
# -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- 
set AT91C_MC_RCB          [expr 0x1 <<  0 ]
# -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- 
set AT91C_MC_UNDADD       [expr 0x1 <<  0 ]
set AT91C_MC_MISADD       [expr 0x1 <<  1 ]
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
# -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- 
set AT91C_MC_FRDY         [expr 0x1 <<  0 ]
set AT91C_MC_FWS          [expr 0xF <<  8 ]
set 	AT91C_MC_FWS_0FWS                 [expr 0x0 <<  8 ]
set 	AT91C_MC_FWS_1FWS                 [expr 0x1 <<  8 ]
set 	AT91C_MC_FWS_2FWS                 [expr 0x2 <<  8 ]
set 	AT91C_MC_FWS_3FWS                 [expr 0x3 <<  8 ]
# -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- 
set AT91C_MC_FCMD         [expr 0xFF <<  0 ]
set 	AT91C_MC_FCMD_GETD                 0x0
set 	AT91C_MC_FCMD_WP                   0x1
set 	AT91C_MC_FCMD_WPL                  0x2
set 	AT91C_MC_FCMD_EWP                  0x3
set 	AT91C_MC_FCMD_EWPL                 0x4
set 	AT91C_MC_FCMD_EA                   0x5
set 	AT91C_MC_FCMD_EPL                  0x6
set 	AT91C_MC_FCMD_EPA                  0x7
set 	AT91C_MC_FCMD_SLB                  0x8
set 	AT91C_MC_FCMD_CLB                  0x9
set 	AT91C_MC_FCMD_GLB                  0xA
set 	AT91C_MC_FCMD_SFB                  0xB
set 	AT91C_MC_FCMD_CFB                  0xC
set 	AT91C_MC_FCMD_GFB                  0xD
set AT91C_MC_FARG         [expr 0xFFFF <<  8 ]
set AT91C_MC_KEY          [expr 0xFF << 24 ]
# -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- 
set AT91C_MC_FRDY_S       [expr 0x1 <<  0 ]
set AT91C_MC_FCMDE        [expr 0x1 <<  1 ]
set AT91C_MC_LOCKE        [expr 0x1 <<  2 ]

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
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
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
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
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
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
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
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
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
# -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
# -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
# -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
# -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
# -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
# -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]

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
#               REGISTER ADDRESS DEFINITION FOR AT91SAM7SL16
# *****************************************************************************
# ========== Register definition for SYS peripheral ========== 
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
# ========== Register definition for CKGR peripheral ========== 
set AT91C_CKGR_MOR  0xFFFFFC20
set AT91C_CKGR_MCFR 0xFFFFFC24
set AT91C_CKGR_PLLR 0xFFFFFC28
# ========== Register definition for PMC peripheral ========== 
set AT91C_PMC_PCER  0xFFFFFC10
set AT91C_PMC_PCKR  0xFFFFFC40
set AT91C_PMC_MCKR  0xFFFFFC30
set AT91C_PMC_PLLR  0xFFFFFC28
set AT91C_PMC_PCDR  0xFFFFFC14
set AT91C_PMC_SCSR  0xFFFFFC08
set AT91C_PMC_MCFR  0xFFFFFC24
set AT91C_PMC_IMR   0xFFFFFC6C
set AT91C_PMC_IER   0xFFFFFC60
set AT91C_PMC_MOR   0xFFFFFC20
set AT91C_PMC_IDR   0xFFFFFC64
set AT91C_PMC_SCDR  0xFFFFFC04
set AT91C_PMC_PCSR  0xFFFFFC18
set AT91C_PMC_FSMR  0xFFFFFC70
set AT91C_PMC_SCER  0xFFFFFC00
set AT91C_PMC_SR    0xFFFFFC68
# ========== Register definition for RSTC peripheral ========== 
set AT91C_RSTC_RCR  0xFFFFFD00
set AT91C_RSTC_RMR  0xFFFFFD08
set AT91C_RSTC_RSR  0xFFFFFD04
# ========== Register definition for SUPC peripheral ========== 
set AT91C_SUPC_WUIR 0xFFFFFD20
set AT91C_SUPC_MR   0xFFFFFD18
set AT91C_SUPC_FWUTR 0xFFFFFD28
set AT91C_SUPC_BOMR 0xFFFFFD14
set AT91C_SUPC_SR   0xFFFFFD24
set AT91C_SUPC_CR   0xFFFFFD10
set AT91C_SUPC_WUMR 0xFFFFFD1C
# ========== Register definition for RTTC peripheral ========== 
set AT91C_RTTC_RTVR 0xFFFFFD38
set AT91C_RTTC_RTAR 0xFFFFFD34
set AT91C_RTTC_RTSR 0xFFFFFD3C
set AT91C_RTTC_RTMR 0xFFFFFD30
# ========== Register definition for PITC peripheral ========== 
set AT91C_PITC_PIMR 0xFFFFFD40
set AT91C_PITC_PIVR 0xFFFFFD48
set AT91C_PITC_PISR 0xFFFFFD44
set AT91C_PITC_PIIR 0xFFFFFD4C
# ========== Register definition for WDTC peripheral ========== 
set AT91C_WDTC_WDMR 0xFFFFFD54
set AT91C_WDTC_WDSR 0xFFFFFD58
set AT91C_WDTC_WDCR 0xFFFFFD50
# ========== Register definition for RTC peripheral ========== 
set AT91C_RTC_IMR   0xFFFFFD88
set AT91C_RTC_TIMALR 0xFFFFFD70
set AT91C_RTC_IDR   0xFFFFFD84
set AT91C_RTC_MR    0xFFFFFD64
set AT91C_RTC_SR    0xFFFFFD78
set AT91C_RTC_VER   0xFFFFFD8C
set AT91C_RTC_TIMR  0xFFFFFD68
set AT91C_RTC_CALALR 0xFFFFFD74
set AT91C_RTC_IER   0xFFFFFD80
set AT91C_RTC_SCCR  0xFFFFFD7C
set AT91C_RTC_CR    0xFFFFFD60
set AT91C_RTC_CALR  0xFFFFFD6C
# ========== Register definition for MC peripheral ========== 
set AT91C_MC_ASR    0xFFFFFF04
set AT91C_MC_RCR    0xFFFFFF00
set AT91C_MC_FCR    0xFFFFFF64
set AT91C_MC_AASR   0xFFFFFF08
set AT91C_MC_FSR    0xFFFFFF68
set AT91C_MC_FRR    0xFFFFFF6C
set AT91C_MC_FMR    0xFFFFFF60
# ========== Register definition for PDC_SPI peripheral ========== 
set AT91C_SPI_PTCR  0xFFFE0120
set AT91C_SPI_TPR   0xFFFE0108
set AT91C_SPI_TCR   0xFFFE010C
set AT91C_SPI_RCR   0xFFFE0104
set AT91C_SPI_PTSR  0xFFFE0124
set AT91C_SPI_RNPR  0xFFFE0110
set AT91C_SPI_RPR   0xFFFE0100
set AT91C_SPI_TNCR  0xFFFE011C
set AT91C_SPI_RNCR  0xFFFE0114
set AT91C_SPI_TNPR  0xFFFE0118
# ========== Register definition for SPI peripheral ========== 
set AT91C_SPI_IER   0xFFFE0014
set AT91C_SPI_SR    0xFFFE0010
set AT91C_SPI_IDR   0xFFFE0018
set AT91C_SPI_CR    0xFFFE0000
set AT91C_SPI_MR    0xFFFE0004
set AT91C_SPI_IMR   0xFFFE001C
set AT91C_SPI_TDR   0xFFFE000C
set AT91C_SPI_RDR   0xFFFE0008
set AT91C_SPI_CSR   0xFFFE0030
# ========== Register definition for PDC_US1 peripheral ========== 
set AT91C_US1_RNCR  0xFFFC4114
set AT91C_US1_PTCR  0xFFFC4120
set AT91C_US1_TCR   0xFFFC410C
set AT91C_US1_PTSR  0xFFFC4124
set AT91C_US1_TNPR  0xFFFC4118
set AT91C_US1_RCR   0xFFFC4104
set AT91C_US1_RNPR  0xFFFC4110
set AT91C_US1_RPR   0xFFFC4100
set AT91C_US1_TNCR  0xFFFC411C
set AT91C_US1_TPR   0xFFFC4108
# ========== Register definition for US1 peripheral ========== 
set AT91C_US1_IF    0xFFFC404C
set AT91C_US1_NER   0xFFFC4044
set AT91C_US1_RTOR  0xFFFC4024
set AT91C_US1_CSR   0xFFFC4014
set AT91C_US1_IDR   0xFFFC400C
set AT91C_US1_IER   0xFFFC4008
set AT91C_US1_THR   0xFFFC401C
set AT91C_US1_TTGR  0xFFFC4028
set AT91C_US1_RHR   0xFFFC4018
set AT91C_US1_BRGR  0xFFFC4020
set AT91C_US1_IMR   0xFFFC4010
set AT91C_US1_FIDI  0xFFFC4040
set AT91C_US1_CR    0xFFFC4000
set AT91C_US1_MR    0xFFFC4004
# ========== Register definition for PDC_US0 peripheral ========== 
set AT91C_US0_TNPR  0xFFFC0118
set AT91C_US0_RNPR  0xFFFC0110
set AT91C_US0_TCR   0xFFFC010C
set AT91C_US0_PTCR  0xFFFC0120
set AT91C_US0_PTSR  0xFFFC0124
set AT91C_US0_TNCR  0xFFFC011C
set AT91C_US0_TPR   0xFFFC0108
set AT91C_US0_RCR   0xFFFC0104
set AT91C_US0_RPR   0xFFFC0100
set AT91C_US0_RNCR  0xFFFC0114
# ========== Register definition for US0 peripheral ========== 
set AT91C_US0_BRGR  0xFFFC0020
set AT91C_US0_NER   0xFFFC0044
set AT91C_US0_CR    0xFFFC0000
set AT91C_US0_IMR   0xFFFC0010
set AT91C_US0_FIDI  0xFFFC0040
set AT91C_US0_TTGR  0xFFFC0028
set AT91C_US0_MR    0xFFFC0004
set AT91C_US0_RTOR  0xFFFC0024
set AT91C_US0_CSR   0xFFFC0014
set AT91C_US0_RHR   0xFFFC0018
set AT91C_US0_IDR   0xFFFC000C
set AT91C_US0_THR   0xFFFC001C
set AT91C_US0_IF    0xFFFC004C
set AT91C_US0_IER   0xFFFC0008
# ========== Register definition for PDC_TWI0 peripheral ========== 
set AT91C_TWI0_TNCR 0xFFFB811C
set AT91C_TWI0_RNCR 0xFFFB8114
set AT91C_TWI0_TNPR 0xFFFB8118
set AT91C_TWI0_PTCR 0xFFFB8120
set AT91C_TWI0_TCR  0xFFFB810C
set AT91C_TWI0_RPR  0xFFFB8100
set AT91C_TWI0_TPR  0xFFFB8108
set AT91C_TWI0_RCR  0xFFFB8104
set AT91C_TWI0_PTSR 0xFFFB8124
set AT91C_TWI0_RNPR 0xFFFB8110
# ========== Register definition for TWI0 peripheral ========== 
set AT91C_TWI0_CR   0xFFFB8000
set AT91C_TWI0_VER  0xFFFB80FC
set AT91C_TWI0_SR   0xFFFB8020
set AT91C_TWI0_FEATURES 0xFFFB80F8
set AT91C_TWI0_IMR  0xFFFB802C
set AT91C_TWI0_THR  0xFFFB8034
set AT91C_TWI0_IDR  0xFFFB8028
set AT91C_TWI0_IADR 0xFFFB800C
set AT91C_TWI0_IPNAME1 0xFFFB80F0
set AT91C_TWI0_SMR  0xFFFB8008
set AT91C_TWI0_IER  0xFFFB8024
set AT91C_TWI0_ADDRSIZE 0xFFFB80EC
set AT91C_TWI0_RHR  0xFFFB8030
set AT91C_TWI0_CWGR 0xFFFB8010
set AT91C_TWI0_MMR  0xFFFB8004
set AT91C_TWI0_IPNAME2 0xFFFB80F4
# ========== Register definition for PDC_TWI1 peripheral ========== 
set AT91C_TWI1_TNPR 0xFFFBC118
set AT91C_TWI1_TCR  0xFFFBC10C
set AT91C_TWI1_RNCR 0xFFFBC114
set AT91C_TWI1_RPR  0xFFFBC100
set AT91C_TWI1_TPR  0xFFFBC108
set AT91C_TWI1_RCR  0xFFFBC104
set AT91C_TWI1_RNPR 0xFFFBC110
set AT91C_TWI1_PTCR 0xFFFBC120
set AT91C_TWI1_TNCR 0xFFFBC11C
set AT91C_TWI1_PTSR 0xFFFBC124
# ========== Register definition for TWI1 peripheral ========== 
set AT91C_TWI1_IDR  0xFFFBC028
set AT91C_TWI1_CR   0xFFFBC000
set AT91C_TWI1_MMR  0xFFFBC004
set AT91C_TWI1_FEATURES 0xFFFBC0F8
set AT91C_TWI1_RHR  0xFFFBC030
set AT91C_TWI1_IER  0xFFFBC024
set AT91C_TWI1_ADDRSIZE 0xFFFBC0EC
set AT91C_TWI1_THR  0xFFFBC034
set AT91C_TWI1_IMR  0xFFFBC02C
set AT91C_TWI1_IADR 0xFFFBC00C
set AT91C_TWI1_SR   0xFFFBC020
set AT91C_TWI1_IPNAME1 0xFFFBC0F0
set AT91C_TWI1_IPNAME2 0xFFFBC0F4
set AT91C_TWI1_CWGR 0xFFFBC010
set AT91C_TWI1_SMR  0xFFFBC008
set AT91C_TWI1_VER  0xFFFBC0FC
# ========== Register definition for PWMC_CH3 peripheral ========== 
set AT91C_CH3_CUPDR 0xFFFCC270
set AT91C_CH3_Reserved 0xFFFCC274
set AT91C_CH3_CPRDR 0xFFFCC268
set AT91C_CH3_CDTYR 0xFFFCC264
set AT91C_CH3_CCNTR 0xFFFCC26C
set AT91C_CH3_CMR   0xFFFCC260
# ========== Register definition for PWMC_CH2 peripheral ========== 
set AT91C_CH2_Reserved 0xFFFCC254
set AT91C_CH2_CMR   0xFFFCC240
set AT91C_CH2_CCNTR 0xFFFCC24C
set AT91C_CH2_CPRDR 0xFFFCC248
set AT91C_CH2_CUPDR 0xFFFCC250
set AT91C_CH2_CDTYR 0xFFFCC244
# ========== Register definition for PWMC_CH1 peripheral ========== 
set AT91C_CH1_Reserved 0xFFFCC234
set AT91C_CH1_CUPDR 0xFFFCC230
set AT91C_CH1_CPRDR 0xFFFCC228
set AT91C_CH1_CCNTR 0xFFFCC22C
set AT91C_CH1_CDTYR 0xFFFCC224
set AT91C_CH1_CMR   0xFFFCC220
# ========== Register definition for PWMC_CH0 peripheral ========== 
set AT91C_CH0_Reserved 0xFFFCC214
set AT91C_CH0_CPRDR 0xFFFCC208
set AT91C_CH0_CDTYR 0xFFFCC204
set AT91C_CH0_CMR   0xFFFCC200
set AT91C_CH0_CUPDR 0xFFFCC210
set AT91C_CH0_CCNTR 0xFFFCC20C
# ========== Register definition for PWMC peripheral ========== 
set AT91C_PWMC_IDR  0xFFFCC014
set AT91C_PWMC_DIS  0xFFFCC008
set AT91C_PWMC_IER  0xFFFCC010
set AT91C_PWMC_VR   0xFFFCC0FC
set AT91C_PWMC_ISR  0xFFFCC01C
set AT91C_PWMC_SR   0xFFFCC00C
set AT91C_PWMC_IMR  0xFFFCC018
set AT91C_PWMC_MR   0xFFFCC000
set AT91C_PWMC_ENA  0xFFFCC004
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
# ========== Register definition for TCB peripheral ========== 
set AT91C_TCB_ADDRSIZE 0xFFFA00EC
set AT91C_TCB_BMR   0xFFFA00C4
set AT91C_TCB_VER   0xFFFA00FC
set AT91C_TCB_FEATURES 0xFFFA00F8
set AT91C_TCB_IPNAME1 0xFFFA00F0
set AT91C_TCB_BCR   0xFFFA00C0
set AT91C_TCB_IPNAME2 0xFFFA00F4
# ========== Register definition for PDC_ADC peripheral ========== 
set AT91C_ADC_PTSR  0xFFFD8124
set AT91C_ADC_PTCR  0xFFFD8120
set AT91C_ADC_TNPR  0xFFFD8118
set AT91C_ADC_TNCR  0xFFFD811C
set AT91C_ADC_RNPR  0xFFFD8110
set AT91C_ADC_RNCR  0xFFFD8114
set AT91C_ADC_RPR   0xFFFD8100
set AT91C_ADC_TCR   0xFFFD810C
set AT91C_ADC_TPR   0xFFFD8108
set AT91C_ADC_RCR   0xFFFD8104
# ========== Register definition for ADC peripheral ========== 
set AT91C_ADC_CDR2  0xFFFD8038
set AT91C_ADC_CDR3  0xFFFD803C
set AT91C_ADC_CDR0  0xFFFD8030
set AT91C_ADC_CDR5  0xFFFD8044
set AT91C_ADC_CHDR  0xFFFD8014
set AT91C_ADC_SR    0xFFFD801C
set AT91C_ADC_CDR4  0xFFFD8040
set AT91C_ADC_CDR1  0xFFFD8034
set AT91C_ADC_LCDR  0xFFFD8020
set AT91C_ADC_IDR   0xFFFD8028
set AT91C_ADC_CR    0xFFFD8000
set AT91C_ADC_CDR7  0xFFFD804C
set AT91C_ADC_CDR6  0xFFFD8048
set AT91C_ADC_IER   0xFFFD8024
set AT91C_ADC_CHER  0xFFFD8010
set AT91C_ADC_CHSR  0xFFFD8018
set AT91C_ADC_MR    0xFFFD8004
set AT91C_ADC_IMR   0xFFFD802C
# ========== Register definition for PDC_SSC peripheral ========== 
set AT91C_SSC_TNCR  0xFFFD411C
set AT91C_SSC_RPR   0xFFFD4100
set AT91C_SSC_RNCR  0xFFFD4114
set AT91C_SSC_TPR   0xFFFD4108
set AT91C_SSC_PTCR  0xFFFD4120
set AT91C_SSC_TCR   0xFFFD410C
set AT91C_SSC_RCR   0xFFFD4104
set AT91C_SSC_RNPR  0xFFFD4110
set AT91C_SSC_TNPR  0xFFFD4118
set AT91C_SSC_PTSR  0xFFFD4124
# ========== Register definition for SSC peripheral ========== 
set AT91C_SSC_IPNAME2 0xFFFD40F4
set AT91C_SSC_RHR   0xFFFD4020
set AT91C_SSC_IDR   0xFFFD4048
set AT91C_SSC_THR   0xFFFD4024
set AT91C_SSC_RCMR  0xFFFD4010
set AT91C_SSC_IER   0xFFFD4044
set AT91C_SSC_CMR   0xFFFD4004
set AT91C_SSC_TCMR  0xFFFD4018
set AT91C_SSC_ADDRSIZE 0xFFFD40EC
set AT91C_SSC_TFMR  0xFFFD401C
set AT91C_SSC_RSHR  0xFFFD4030
set AT91C_SSC_TSHR  0xFFFD4034
set AT91C_SSC_FEATURES 0xFFFD40F8
set AT91C_SSC_SR    0xFFFD4040
set AT91C_SSC_IPNAME1 0xFFFD40F0
set AT91C_SSC_VER   0xFFFD40FC
set AT91C_SSC_CR    0xFFFD4000
set AT91C_SSC_IMR   0xFFFD404C
set AT91C_SSC_RFMR  0xFFFD4014

# *****************************************************************************
#               BASE ADDRESS DEFINITIONS FOR AT91SAM7SL16
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
set AT91C_BASE_SUPC      0xFFFFFD10
set AT91C_BASE_RTTC      0xFFFFFD30
set AT91C_BASE_PITC      0xFFFFFD40
set AT91C_BASE_WDTC      0xFFFFFD50
set AT91C_BASE_RTC       0xFFFFFD60
set AT91C_BASE_MC        0xFFFFFF00
set AT91C_BASE_PDC_SPI   0xFFFE0100
set AT91C_BASE_SPI       0xFFFE0000
set AT91C_BASE_PDC_US1   0xFFFC4100
set AT91C_BASE_US1       0xFFFC4000
set AT91C_BASE_PDC_US0   0xFFFC0100
set AT91C_BASE_US0       0xFFFC0000
set AT91C_BASE_PDC_TWI0  0xFFFB8100
set AT91C_BASE_TWI0      0xFFFB8000
set AT91C_BASE_PDC_TWI1  0xFFFBC100
set AT91C_BASE_TWI1      0xFFFBC000
set AT91C_BASE_PWMC_CH3  0xFFFCC260
set AT91C_BASE_PWMC_CH2  0xFFFCC240
set AT91C_BASE_PWMC_CH1  0xFFFCC220
set AT91C_BASE_PWMC_CH0  0xFFFCC200
set AT91C_BASE_PWMC      0xFFFCC000
set AT91C_BASE_TC0       0xFFFA0000
set AT91C_BASE_TC1       0xFFFA0040
set AT91C_BASE_TC2       0xFFFA0080
set AT91C_BASE_TCB       0xFFFA0000
set AT91C_BASE_PDC_ADC   0xFFFD8100
set AT91C_BASE_ADC       0xFFFD8000
set AT91C_BASE_PDC_SSC   0xFFFD4100
set AT91C_BASE_SSC       0xFFFD4000

# *****************************************************************************
#               PERIPHERAL ID DEFINITIONS FOR AT91SAM7SL16
# *****************************************************************************
set AT91C_ID_FIQ     0
set AT91C_ID_SYS     1
set AT91C_ID_PIOA    2
set AT91C_ID_PIOB    3
set AT91C_ID_4_Reserved  4
set AT91C_ID_SPI     5
set AT91C_ID_US0     6
set AT91C_ID_US1     7
set AT91C_ID_TWI0    8
set AT91C_ID_TWI1    9
set AT91C_ID_PWMC   10
set AT91C_ID_11_Reserved 11
set AT91C_ID_TC0    12
set AT91C_ID_TC1    13
set AT91C_ID_TC2    14
set AT91C_ID_ADC    15
set AT91C_ID_SSC    16
set AT91C_ID_17_Reserved 17
set AT91C_ID_18_Reserved 18
set AT91C_ID_19_Reserved 19
set AT91C_ID_20_Reserved 20
set AT91C_ID_21_Reserved 21
set AT91C_ID_22_Reserved 22
set AT91C_ID_23_Reserved 23
set AT91C_ID_24_Reserved 24
set AT91C_ID_25_Reserved 25
set AT91C_ID_26_Reserved 26
set AT91C_ID_27_Reserved 27
set AT91C_ID_28_Reserved 28
set AT91C_ID_29_Reserved 29
set AT91C_ID_IRQ0   30
set AT91C_ID_IRQ1   31

# *****************************************************************************
#               PIO DEFINITIONS FOR AT91SAM7SL16
# *****************************************************************************
set AT91C_PIO_PA0        [expr 1 <<  0 ]
set AT91C_PA0_DRXD     $AT91C_PIO_PA0
set AT91C_PA0_FIQ      $AT91C_PIO_PA0
set AT91C_PIO_PA1        [expr 1 <<  1 ]
set AT91C_PA1_DTXD     $AT91C_PIO_PA1
set AT91C_PA1_TCLK0    $AT91C_PIO_PA1
set AT91C_PIO_PA10       [expr 1 << 10 ]
set AT91C_PA10_TWD0     $AT91C_PIO_PA10
set AT91C_PA10_IRQ0     $AT91C_PIO_PA10
set AT91C_PIO_PA11       [expr 1 << 11 ]
set AT91C_PA11_TWCK0    $AT91C_PIO_PA11
set AT91C_PA11_PCK0     $AT91C_PIO_PA11
set AT91C_PIO_PA12       [expr 1 << 12 ]
set AT91C_PA12_TD       $AT91C_PIO_PA12
set AT91C_PA12_PWM0     $AT91C_PIO_PA12
set AT91C_PIO_PA13       [expr 1 << 13 ]
set AT91C_PA13_RD       $AT91C_PIO_PA13
set AT91C_PA13_PWM1     $AT91C_PIO_PA13
set AT91C_PIO_PA14       [expr 1 << 14 ]
set AT91C_PA14_TK       $AT91C_PIO_PA14
set AT91C_PA14_PCK2     $AT91C_PIO_PA14
set AT91C_PIO_PA15       [expr 1 << 15 ]
set AT91C_PA15_TF       $AT91C_PIO_PA15
set AT91C_PA15_TIOA0    $AT91C_PIO_PA15
set AT91C_PIO_PA16       [expr 1 << 16 ]
set AT91C_PA16_RK       $AT91C_PIO_PA16
set AT91C_PA16_NPCS2    $AT91C_PIO_PA16
set AT91C_PIO_PA17       [expr 1 << 17 ]
set AT91C_PA17_RF       $AT91C_PIO_PA17
set AT91C_PA17_NPCS3    $AT91C_PIO_PA17
set AT91C_PIO_PA18       [expr 1 << 18 ]
set AT91C_PA18_TWD1     $AT91C_PIO_PA18
set AT91C_PA18_CTS0     $AT91C_PIO_PA18
set AT91C_PIO_PA19       [expr 1 << 19 ]
set AT91C_PA19_TWCK1    $AT91C_PIO_PA19
set AT91C_PA19_RTS0     $AT91C_PIO_PA19
set AT91C_PIO_PA2        [expr 1 <<  2 ]
set AT91C_PA2_TXD0     $AT91C_PIO_PA2
set AT91C_PA2_PWM0     $AT91C_PIO_PA2
set AT91C_PIO_PA20       [expr 1 << 20 ]
set AT91C_PA20_NPCS1    $AT91C_PIO_PA20
set AT91C_PA20_PCK1     $AT91C_PIO_PA20
set AT91C_PIO_PA21       [expr 1 << 21 ]
set AT91C_PA21_SCK1     $AT91C_PIO_PA21
set AT91C_PA21_TIOB0    $AT91C_PIO_PA21
set AT91C_PIO_PA22       [expr 1 << 22 ]
set AT91C_PA22_RTS1     $AT91C_PIO_PA22
set AT91C_PA22_PWM2     $AT91C_PIO_PA22
set AT91C_PIO_PA23       [expr 1 << 23 ]
set AT91C_PA23_CTS1     $AT91C_PIO_PA23
set AT91C_PA23_ADTRG    $AT91C_PIO_PA23
set AT91C_PIO_PA24       [expr 1 << 24 ]
set AT91C_PA24_TIOB1    $AT91C_PIO_PA24
set AT91C_PA24_PWM3     $AT91C_PIO_PA24
set AT91C_PIO_PA25       [expr 1 << 25 ]
set AT91C_PA25_TIOA1    $AT91C_PIO_PA25
set AT91C_PA25_PWM2     $AT91C_PIO_PA25
set AT91C_PIO_PA26       [expr 1 << 26 ]
set AT91C_PA26_TCLK1    $AT91C_PIO_PA26
set AT91C_PA26_IRQ1     $AT91C_PIO_PA26
set AT91C_PIO_PA27       [expr 1 << 27 ]
set AT91C_PA27_TIOB2    $AT91C_PIO_PA27
set AT91C_PA27_NPCS2    $AT91C_PIO_PA27
set AT91C_PIO_PA28       [expr 1 << 28 ]
set AT91C_PA28_TIOA2    $AT91C_PIO_PA28
set AT91C_PA28_PCK2     $AT91C_PIO_PA28
set AT91C_PIO_PA29       [expr 1 << 29 ]
set AT91C_PA29_TCLK2    $AT91C_PIO_PA29
set AT91C_PA29_PCK1     $AT91C_PIO_PA29
set AT91C_PIO_PA3        [expr 1 <<  3 ]
set AT91C_PA3_RXD0     $AT91C_PIO_PA3
set AT91C_PA3_PWM1     $AT91C_PIO_PA3
set AT91C_PIO_PA30       [expr 1 << 30 ]
set AT91C_PA30_PWM2     $AT91C_PIO_PA30
set AT91C_PA30_NPCS1    $AT91C_PIO_PA30
set AT91C_PIO_PA31       [expr 1 << 31 ]
set AT91C_PA31_PWM3     $AT91C_PIO_PA31
set AT91C_PA31_NPCS2    $AT91C_PIO_PA31
set AT91C_PIO_PA4        [expr 1 <<  4 ]
set AT91C_PA4_TXD1     $AT91C_PIO_PA4
set AT91C_PA4_SCK0     $AT91C_PIO_PA4
set AT91C_PIO_PA5        [expr 1 <<  5 ]
set AT91C_PA5_RXD1     $AT91C_PIO_PA5
set AT91C_PA5_PWM3     $AT91C_PIO_PA5
set AT91C_PIO_PA6        [expr 1 <<  6 ]
set AT91C_PA6_MISO     $AT91C_PIO_PA6
set AT91C_PA6_PWM2     $AT91C_PIO_PA6
set AT91C_PIO_PA7        [expr 1 <<  7 ]
set AT91C_PA7_MOSI     $AT91C_PIO_PA7
set AT91C_PA7_PCK0     $AT91C_PIO_PA7
set AT91C_PIO_PA8        [expr 1 <<  8 ]
set AT91C_PA8_SPCK     $AT91C_PIO_PA8
set AT91C_PA8_PCK0     $AT91C_PIO_PA8
set AT91C_PIO_PA9        [expr 1 <<  9 ]
set AT91C_PA9_NPCS0    $AT91C_PIO_PA9
set AT91C_PA9_PWM2     $AT91C_PIO_PA9
set AT91C_PIO_PB0        [expr 1 <<  0 ]
set AT91C_PIO_PB1        [expr 1 <<  1 ]
set AT91C_PIO_PB2        [expr 1 <<  2 ]
set AT91C_PIO_PB3        [expr 1 <<  3 ]

# *****************************************************************************
#               MEMORY MAPPING DEFINITIONS FOR AT91SAM7SL16
# *****************************************************************************
set AT91C_ISRAM	 0x00200000
set AT91C_ISRAM_SIZE	 0x00001000
set AT91C_IFLASH	 0x00100000
set AT91C_IFLASH_SIZE	 0x00004000


# *****************************************************************************
#               ATTRIBUTES DEFINITIONS FOR AT91SAM7SL16
# *****************************************************************************
array set AT91SAM7SL16_att {
	DBGU 	{ LP 	DBGU_att }
	PMC 	{ LP 	PMC_att }
	RSTC 	{ LP 	RSTC_att }
	SSC 	{ LP 	SSC_att }
	WDTC 	{ LP 	WDTC_att }
	USART 	{ LP 	US1_att 	US0_att }
	SPI 	{ LP 	SPI_att }
	PITC 	{ LP 	PITC_att }
	TCB 	{ LP 	TCB_att }
	CKGR 	{ LP 	CKGR_att }
	AIC 	{ LP 	AIC_att }
	SUPC 	{ LP 	SUPC_att }
	TWI 	{ LP 	TWI0_att 	TWI1_att }
	ADC 	{ LP 	ADC_att }
	PWMC_CH 	{ LP 	PWMC_CH3_att 	PWMC_CH2_att 	PWMC_CH1_att 	PWMC_CH0_att }
	RTTC 	{ LP 	RTTC_att }
	RTC 	{ LP 	RTC_att }
	TC 	{ LP 	TC0_att 	TC1_att 	TC2_att }
	SYS 	{ LP 	SYS_att }
	MC 	{ LP 	MC_att }
	PIO 	{ LP 	PIOA_att 	PIOB_att }
	PWMC 	{ LP 	PWMC_att }
	PDC 	{ LP 	PDC_DBGU_att 	PDC_SPI_att 	PDC_US1_att 	PDC_US0_att 	PDC_TWI0_att 	PDC_TWI1_att 	PDC_ADC_att 	PDC_SSC_att }

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

# ========== Peripheral attributes for PMC peripheral ========== 
array set PMC_att {
	PCER 	{ R AT91C_PMC_PCER 	WO }
	PCKR 	{ R AT91C_PMC_PCKR 	RW  3 }
	MCKR 	{ R AT91C_PMC_MCKR 	RW }
	PLLR 	{ R AT91C_PMC_PLLR 	RW }
	PCDR 	{ R AT91C_PMC_PCDR 	WO }
	SCSR 	{ R AT91C_PMC_SCSR 	RO }
	MCFR 	{ R AT91C_PMC_MCFR 	RO }
	IMR 	{ R AT91C_PMC_IMR 	RO }
	IER 	{ R AT91C_PMC_IER 	WO }
	MOR 	{ R AT91C_PMC_MOR 	RW }
	IDR 	{ R AT91C_PMC_IDR 	WO }
	SCDR 	{ R AT91C_PMC_SCDR 	WO }
	PCSR 	{ R AT91C_PMC_PCSR 	RO }
	FSMR 	{ R AT91C_PMC_FSMR 	RW }
	SCER 	{ R AT91C_PMC_SCER 	WO }
	SR 	{ R AT91C_PMC_SR 	RO }
	listeReg 	{ PCER PCKR MCKR PLLR PCDR SCSR MCFR IMR IER MOR IDR SCDR PCSR FSMR SCER SR  }

}

# ========== Peripheral attributes for RSTC peripheral ========== 
array set RSTC_att {
	RCR 	{ R AT91C_RSTC_RCR 	WO }
	RMR 	{ R AT91C_RSTC_RMR 	RW }
	RSR 	{ R AT91C_RSTC_RSR 	RO }
	listeReg 	{ RCR RMR RSR  }

}

# ========== Peripheral attributes for SSC peripheral ========== 
array set SSC_att {
	IPNAME2 	{ R AT91C_SSC_IPNAME2 	RW }
	RHR 	{ R AT91C_SSC_RHR 	RO }
	IDR 	{ R AT91C_SSC_IDR 	WO }
	THR 	{ R AT91C_SSC_THR 	WO }
	RCMR 	{ R AT91C_SSC_RCMR 	RW }
	IER 	{ R AT91C_SSC_IER 	WO }
	CMR 	{ R AT91C_SSC_CMR 	RW }
	TCMR 	{ R AT91C_SSC_TCMR 	RW }
	ADDRSIZE 	{ R AT91C_SSC_ADDRSIZE 	RW }
	TFMR 	{ R AT91C_SSC_TFMR 	RW }
	RSHR 	{ R AT91C_SSC_RSHR 	RO }
	TSHR 	{ R AT91C_SSC_TSHR 	RW }
	FEATURES 	{ R AT91C_SSC_FEATURES 	RW }
	SR 	{ R AT91C_SSC_SR 	RO }
	IPNAME1 	{ R AT91C_SSC_IPNAME1 	RW }
	VER 	{ R AT91C_SSC_VER 	RO }
	CR 	{ R AT91C_SSC_CR 	WO }
	IMR 	{ R AT91C_SSC_IMR 	RO }
	RFMR 	{ R AT91C_SSC_RFMR 	RW }
	listeReg 	{ IPNAME2 RHR IDR THR RCMR IER CMR TCMR ADDRSIZE TFMR RSHR TSHR FEATURES SR IPNAME1 VER CR IMR RFMR  }

}

# ========== Peripheral attributes for WDTC peripheral ========== 
array set WDTC_att {
	WDMR 	{ R AT91C_WDTC_WDMR 	RW }
	WDSR 	{ R AT91C_WDTC_WDSR 	RO }
	WDCR 	{ R AT91C_WDTC_WDCR 	WO }
	listeReg 	{ WDMR WDSR WDCR  }

}

# ========== Peripheral attributes for USART peripheral ========== 
array set US1_att {
	IF 	{ R AT91C_US1_IF 	RW }
	NER 	{ R AT91C_US1_NER 	RO }
	RTOR 	{ R AT91C_US1_RTOR 	RW }
	CSR 	{ R AT91C_US1_CSR 	RO }
	IDR 	{ R AT91C_US1_IDR 	WO }
	IER 	{ R AT91C_US1_IER 	WO }
	THR 	{ R AT91C_US1_THR 	WO }
	TTGR 	{ R AT91C_US1_TTGR 	RW }
	RHR 	{ R AT91C_US1_RHR 	RO }
	BRGR 	{ R AT91C_US1_BRGR 	RW }
	IMR 	{ R AT91C_US1_IMR 	RO }
	FIDI 	{ R AT91C_US1_FIDI 	RW }
	CR 	{ R AT91C_US1_CR 	WO }
	MR 	{ R AT91C_US1_MR 	RW }
	listeReg 	{ IF NER RTOR CSR IDR IER THR TTGR RHR BRGR IMR FIDI CR MR  }

}
array set US0_att {
	BRGR 	{ R AT91C_US0_BRGR 	RW }
	NER 	{ R AT91C_US0_NER 	RO }
	CR 	{ R AT91C_US0_CR 	WO }
	IMR 	{ R AT91C_US0_IMR 	RO }
	FIDI 	{ R AT91C_US0_FIDI 	RW }
	TTGR 	{ R AT91C_US0_TTGR 	RW }
	MR 	{ R AT91C_US0_MR 	RW }
	RTOR 	{ R AT91C_US0_RTOR 	RW }
	CSR 	{ R AT91C_US0_CSR 	RO }
	RHR 	{ R AT91C_US0_RHR 	RO }
	IDR 	{ R AT91C_US0_IDR 	WO }
	THR 	{ R AT91C_US0_THR 	WO }
	IF 	{ R AT91C_US0_IF 	RW }
	IER 	{ R AT91C_US0_IER 	WO }
	listeReg 	{ BRGR NER CR IMR FIDI TTGR MR RTOR CSR RHR IDR THR IF IER  }

}

# ========== Peripheral attributes for SPI peripheral ========== 
array set SPI_att {
	IER 	{ R AT91C_SPI_IER 	WO }
	SR 	{ R AT91C_SPI_SR 	RO }
	IDR 	{ R AT91C_SPI_IDR 	WO }
	CR 	{ R AT91C_SPI_CR 	RO }
	MR 	{ R AT91C_SPI_MR 	RW }
	IMR 	{ R AT91C_SPI_IMR 	RO }
	TDR 	{ R AT91C_SPI_TDR 	WO }
	RDR 	{ R AT91C_SPI_RDR 	RO }
	CSR 	{ R AT91C_SPI_CSR 	RW  4 }
	listeReg 	{ IER SR IDR CR MR IMR TDR RDR CSR  }

}

# ========== Peripheral attributes for PITC peripheral ========== 
array set PITC_att {
	PIMR 	{ R AT91C_PITC_PIMR 	RW }
	PIVR 	{ R AT91C_PITC_PIVR 	RO }
	PISR 	{ R AT91C_PITC_PISR 	RO }
	PIIR 	{ R AT91C_PITC_PIIR 	RO }
	listeReg 	{ PIMR PIVR PISR PIIR  }

}

# ========== Peripheral attributes for TCB peripheral ========== 
array set TCB_att {
	ADDRSIZE 	{ R AT91C_TCB_ADDRSIZE 	RW }
	BMR 	{ R AT91C_TCB_BMR 	RW }
	VER 	{ R AT91C_TCB_VER 	RO }
	FEATURES 	{ R AT91C_TCB_FEATURES 	RW }
	IPNAME1 	{ R AT91C_TCB_IPNAME1 	RW }
	BCR 	{ R AT91C_TCB_BCR 	WO }
	IPNAME2 	{ R AT91C_TCB_IPNAME2 	RW }
	listeReg 	{ ADDRSIZE BMR VER FEATURES IPNAME1 BCR IPNAME2  }

}

# ========== Peripheral attributes for CKGR peripheral ========== 
array set CKGR_att {
	MOR 	{ R AT91C_CKGR_MOR 	RW }
	MCFR 	{ R AT91C_CKGR_MCFR 	RO }
	PLLR 	{ R AT91C_CKGR_PLLR 	RW }
	listeReg 	{ MOR MCFR PLLR  }

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

# ========== Peripheral attributes for SUPC peripheral ========== 
array set SUPC_att {
	WUIR 	{ R AT91C_SUPC_WUIR 	RW }
	MR 	{ R AT91C_SUPC_MR 	RW }
	FWUTR 	{ R AT91C_SUPC_FWUTR 	RW }
	BOMR 	{ R AT91C_SUPC_BOMR 	RW }
	SR 	{ R AT91C_SUPC_SR 	RO }
	CR 	{ R AT91C_SUPC_CR 	WO }
	WUMR 	{ R AT91C_SUPC_WUMR 	RW }
	listeReg 	{ WUIR MR FWUTR BOMR SR CR WUMR  }

}

# ========== Peripheral attributes for TWI peripheral ========== 
array set TWI0_att {
	CR 	{ R AT91C_TWI0_CR 	WO }
	VER 	{ R AT91C_TWI0_VER 	WO }
	SR 	{ R AT91C_TWI0_SR 	RO }
	FEATURES 	{ R AT91C_TWI0_FEATURES 	RW }
	IMR 	{ R AT91C_TWI0_IMR 	RO }
	THR 	{ R AT91C_TWI0_THR 	WO }
	IDR 	{ R AT91C_TWI0_IDR 	WO }
	IADR 	{ R AT91C_TWI0_IADR 	RW }
	IPNAME1 	{ R AT91C_TWI0_IPNAME1 	RW }
	SMR 	{ R AT91C_TWI0_SMR 	RW }
	IER 	{ R AT91C_TWI0_IER 	WO }
	ADDRSIZE 	{ R AT91C_TWI0_ADDRSIZE 	RW }
	RHR 	{ R AT91C_TWI0_RHR 	RO }
	CWGR 	{ R AT91C_TWI0_CWGR 	RW }
	MMR 	{ R AT91C_TWI0_MMR 	RW }
	IPNAME2 	{ R AT91C_TWI0_IPNAME2 	RW }
	listeReg 	{ CR VER SR FEATURES IMR THR IDR IADR IPNAME1 SMR IER ADDRSIZE RHR CWGR MMR IPNAME2  }

}
array set TWI1_att {
	IDR 	{ R AT91C_TWI1_IDR 	WO }
	CR 	{ R AT91C_TWI1_CR 	WO }
	MMR 	{ R AT91C_TWI1_MMR 	RW }
	FEATURES 	{ R AT91C_TWI1_FEATURES 	RW }
	RHR 	{ R AT91C_TWI1_RHR 	RO }
	IER 	{ R AT91C_TWI1_IER 	WO }
	ADDRSIZE 	{ R AT91C_TWI1_ADDRSIZE 	RW }
	THR 	{ R AT91C_TWI1_THR 	WO }
	IMR 	{ R AT91C_TWI1_IMR 	RO }
	IADR 	{ R AT91C_TWI1_IADR 	RW }
	SR 	{ R AT91C_TWI1_SR 	RO }
	IPNAME1 	{ R AT91C_TWI1_IPNAME1 	RW }
	IPNAME2 	{ R AT91C_TWI1_IPNAME2 	RW }
	CWGR 	{ R AT91C_TWI1_CWGR 	RW }
	SMR 	{ R AT91C_TWI1_SMR 	RW }
	VER 	{ R AT91C_TWI1_VER 	WO }
	listeReg 	{ IDR CR MMR FEATURES RHR IER ADDRSIZE THR IMR IADR SR IPNAME1 IPNAME2 CWGR SMR VER  }

}

# ========== Peripheral attributes for ADC peripheral ========== 
array set ADC_att {
	CDR2 	{ R AT91C_ADC_CDR2 	RO }
	CDR3 	{ R AT91C_ADC_CDR3 	RO }
	CDR0 	{ R AT91C_ADC_CDR0 	RO }
	CDR5 	{ R AT91C_ADC_CDR5 	RO }
	CHDR 	{ R AT91C_ADC_CHDR 	WO }
	SR 	{ R AT91C_ADC_SR 	RO }
	CDR4 	{ R AT91C_ADC_CDR4 	RO }
	CDR1 	{ R AT91C_ADC_CDR1 	RO }
	LCDR 	{ R AT91C_ADC_LCDR 	RO }
	IDR 	{ R AT91C_ADC_IDR 	WO }
	CR 	{ R AT91C_ADC_CR 	WO }
	CDR7 	{ R AT91C_ADC_CDR7 	RO }
	CDR6 	{ R AT91C_ADC_CDR6 	RO }
	IER 	{ R AT91C_ADC_IER 	WO }
	CHER 	{ R AT91C_ADC_CHER 	WO }
	CHSR 	{ R AT91C_ADC_CHSR 	RO }
	MR 	{ R AT91C_ADC_MR 	RW }
	IMR 	{ R AT91C_ADC_IMR 	RO }
	listeReg 	{ CDR2 CDR3 CDR0 CDR5 CHDR SR CDR4 CDR1 LCDR IDR CR CDR7 CDR6 IER CHER CHSR MR IMR  }

}

# ========== Peripheral attributes for PWMC_CH peripheral ========== 
array set PWMC_CH3_att {
	CUPDR 	{ R AT91C_CH3_CUPDR 	WO }
	Reserved 	{ R AT91C_CH3_Reserved 	WO  3 }
	CPRDR 	{ R AT91C_CH3_CPRDR 	RW }
	CDTYR 	{ R AT91C_CH3_CDTYR 	RW }
	CCNTR 	{ R AT91C_CH3_CCNTR 	RO }
	CMR 	{ R AT91C_CH3_CMR 	RW }
	listeReg 	{ CUPDR Reserved CPRDR CDTYR CCNTR CMR  }

}
array set PWMC_CH2_att {
	Reserved 	{ R AT91C_CH2_Reserved 	WO  3 }
	CMR 	{ R AT91C_CH2_CMR 	RW }
	CCNTR 	{ R AT91C_CH2_CCNTR 	RO }
	CPRDR 	{ R AT91C_CH2_CPRDR 	RW }
	CUPDR 	{ R AT91C_CH2_CUPDR 	WO }
	CDTYR 	{ R AT91C_CH2_CDTYR 	RW }
	listeReg 	{ Reserved CMR CCNTR CPRDR CUPDR CDTYR  }

}
array set PWMC_CH1_att {
	Reserved 	{ R AT91C_CH1_Reserved 	WO  3 }
	CUPDR 	{ R AT91C_CH1_CUPDR 	WO }
	CPRDR 	{ R AT91C_CH1_CPRDR 	RW }
	CCNTR 	{ R AT91C_CH1_CCNTR 	RO }
	CDTYR 	{ R AT91C_CH1_CDTYR 	RW }
	CMR 	{ R AT91C_CH1_CMR 	RW }
	listeReg 	{ Reserved CUPDR CPRDR CCNTR CDTYR CMR  }

}
array set PWMC_CH0_att {
	Reserved 	{ R AT91C_CH0_Reserved 	WO  3 }
	CPRDR 	{ R AT91C_CH0_CPRDR 	RW }
	CDTYR 	{ R AT91C_CH0_CDTYR 	RW }
	CMR 	{ R AT91C_CH0_CMR 	RW }
	CUPDR 	{ R AT91C_CH0_CUPDR 	WO }
	CCNTR 	{ R AT91C_CH0_CCNTR 	RO }
	listeReg 	{ Reserved CPRDR CDTYR CMR CUPDR CCNTR  }

}

# ========== Peripheral attributes for RTTC peripheral ========== 
array set RTTC_att {
	RTVR 	{ R AT91C_RTTC_RTVR 	RO }
	RTAR 	{ R AT91C_RTTC_RTAR 	RW }
	RTSR 	{ R AT91C_RTTC_RTSR 	RO }
	RTMR 	{ R AT91C_RTTC_RTMR 	RW }
	listeReg 	{ RTVR RTAR RTSR RTMR  }

}

# ========== Peripheral attributes for RTC peripheral ========== 
array set RTC_att {
	IMR 	{ R AT91C_RTC_IMR 	RO }
	TIMALR 	{ R AT91C_RTC_TIMALR 	RW }
	IDR 	{ R AT91C_RTC_IDR 	WO }
	MR 	{ R AT91C_RTC_MR 	RW }
	SR 	{ R AT91C_RTC_SR 	RO }
	VER 	{ R AT91C_RTC_VER 	RO }
	TIMR 	{ R AT91C_RTC_TIMR 	RW }
	CALALR 	{ R AT91C_RTC_CALALR 	RW }
	IER 	{ R AT91C_RTC_IER 	WO }
	SCCR 	{ R AT91C_RTC_SCCR 	WO }
	CR 	{ R AT91C_RTC_CR 	RW }
	CALR 	{ R AT91C_RTC_CALR 	RW }
	listeReg 	{ IMR TIMALR IDR MR SR VER TIMR CALALR IER SCCR CR CALR  }

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

# ========== Peripheral attributes for SYS peripheral ========== 
array set SYS_att {
	listeReg 	{  }

}

# ========== Peripheral attributes for MC peripheral ========== 
array set MC_att {
	ASR 	{ R AT91C_MC_ASR 	RO }
	RCR 	{ R AT91C_MC_RCR 	WO }
	FCR 	{ R AT91C_MC_FCR 	WO }
	AASR 	{ R AT91C_MC_AASR 	RO }
	FSR 	{ R AT91C_MC_FSR 	RO }
	FRR 	{ R AT91C_MC_FRR 	RO }
	FMR 	{ R AT91C_MC_FMR 	RW }
	listeReg 	{ ASR RCR FCR AASR FSR FRR FMR  }

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

# ========== Peripheral attributes for PWMC peripheral ========== 
array set PWMC_att {
	IDR 	{ R AT91C_PWMC_IDR 	WO }
	DIS 	{ R AT91C_PWMC_DIS 	WO }
	IER 	{ R AT91C_PWMC_IER 	WO }
	VR 	{ R AT91C_PWMC_VR 	RO }
	ISR 	{ R AT91C_PWMC_ISR 	RO }
	SR 	{ R AT91C_PWMC_SR 	RO }
	IMR 	{ R AT91C_PWMC_IMR 	RO }
	MR 	{ R AT91C_PWMC_MR 	RW }
	ENA 	{ R AT91C_PWMC_ENA 	WO }
	listeReg 	{ IDR DIS IER VR ISR SR IMR MR ENA  }

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
array set PDC_SPI_att {
	PTCR 	{ R AT91C_SPI_PTCR 	WO }
	TPR 	{ R AT91C_SPI_TPR 	RW }
	TCR 	{ R AT91C_SPI_TCR 	RW }
	RCR 	{ R AT91C_SPI_RCR 	RW }
	PTSR 	{ R AT91C_SPI_PTSR 	RO }
	RNPR 	{ R AT91C_SPI_RNPR 	RW }
	RPR 	{ R AT91C_SPI_RPR 	RW }
	TNCR 	{ R AT91C_SPI_TNCR 	RW }
	RNCR 	{ R AT91C_SPI_RNCR 	RW }
	TNPR 	{ R AT91C_SPI_TNPR 	RW }
	listeReg 	{ PTCR TPR TCR RCR PTSR RNPR RPR TNCR RNCR TNPR  }

}
array set PDC_US1_att {
	RNCR 	{ R AT91C_US1_RNCR 	RW }
	PTCR 	{ R AT91C_US1_PTCR 	WO }
	TCR 	{ R AT91C_US1_TCR 	RW }
	PTSR 	{ R AT91C_US1_PTSR 	RO }
	TNPR 	{ R AT91C_US1_TNPR 	RW }
	RCR 	{ R AT91C_US1_RCR 	RW }
	RNPR 	{ R AT91C_US1_RNPR 	RW }
	RPR 	{ R AT91C_US1_RPR 	RW }
	TNCR 	{ R AT91C_US1_TNCR 	RW }
	TPR 	{ R AT91C_US1_TPR 	RW }
	listeReg 	{ RNCR PTCR TCR PTSR TNPR RCR RNPR RPR TNCR TPR  }

}
array set PDC_US0_att {
	TNPR 	{ R AT91C_US0_TNPR 	RW }
	RNPR 	{ R AT91C_US0_RNPR 	RW }
	TCR 	{ R AT91C_US0_TCR 	RW }
	PTCR 	{ R AT91C_US0_PTCR 	WO }
	PTSR 	{ R AT91C_US0_PTSR 	RO }
	TNCR 	{ R AT91C_US0_TNCR 	RW }
	TPR 	{ R AT91C_US0_TPR 	RW }
	RCR 	{ R AT91C_US0_RCR 	RW }
	RPR 	{ R AT91C_US0_RPR 	RW }
	RNCR 	{ R AT91C_US0_RNCR 	RW }
	listeReg 	{ TNPR RNPR TCR PTCR PTSR TNCR TPR RCR RPR RNCR  }

}
array set PDC_TWI0_att {
	TNCR 	{ R AT91C_TWI0_TNCR 	RW }
	RNCR 	{ R AT91C_TWI0_RNCR 	RW }
	TNPR 	{ R AT91C_TWI0_TNPR 	RW }
	PTCR 	{ R AT91C_TWI0_PTCR 	WO }
	TCR 	{ R AT91C_TWI0_TCR 	RW }
	RPR 	{ R AT91C_TWI0_RPR 	RW }
	TPR 	{ R AT91C_TWI0_TPR 	RW }
	RCR 	{ R AT91C_TWI0_RCR 	RW }
	PTSR 	{ R AT91C_TWI0_PTSR 	RO }
	RNPR 	{ R AT91C_TWI0_RNPR 	RW }
	listeReg 	{ TNCR RNCR TNPR PTCR TCR RPR TPR RCR PTSR RNPR  }

}
array set PDC_TWI1_att {
	TNPR 	{ R AT91C_TWI1_TNPR 	RW }
	TCR 	{ R AT91C_TWI1_TCR 	RW }
	RNCR 	{ R AT91C_TWI1_RNCR 	RW }
	RPR 	{ R AT91C_TWI1_RPR 	RW }
	TPR 	{ R AT91C_TWI1_TPR 	RW }
	RCR 	{ R AT91C_TWI1_RCR 	RW }
	RNPR 	{ R AT91C_TWI1_RNPR 	RW }
	PTCR 	{ R AT91C_TWI1_PTCR 	WO }
	TNCR 	{ R AT91C_TWI1_TNCR 	RW }
	PTSR 	{ R AT91C_TWI1_PTSR 	RO }
	listeReg 	{ TNPR TCR RNCR RPR TPR RCR RNPR PTCR TNCR PTSR  }

}
array set PDC_ADC_att {
	PTSR 	{ R AT91C_ADC_PTSR 	RO }
	PTCR 	{ R AT91C_ADC_PTCR 	WO }
	TNPR 	{ R AT91C_ADC_TNPR 	RW }
	TNCR 	{ R AT91C_ADC_TNCR 	RW }
	RNPR 	{ R AT91C_ADC_RNPR 	RW }
	RNCR 	{ R AT91C_ADC_RNCR 	RW }
	RPR 	{ R AT91C_ADC_RPR 	RW }
	TCR 	{ R AT91C_ADC_TCR 	RW }
	TPR 	{ R AT91C_ADC_TPR 	RW }
	RCR 	{ R AT91C_ADC_RCR 	RW }
	listeReg 	{ PTSR PTCR TNPR TNCR RNPR RNCR RPR TCR TPR RCR  }

}
array set PDC_SSC_att {
	TNCR 	{ R AT91C_SSC_TNCR 	RW }
	RPR 	{ R AT91C_SSC_RPR 	RW }
	RNCR 	{ R AT91C_SSC_RNCR 	RW }
	TPR 	{ R AT91C_SSC_TPR 	RW }
	PTCR 	{ R AT91C_SSC_PTCR 	WO }
	TCR 	{ R AT91C_SSC_TCR 	RW }
	RCR 	{ R AT91C_SSC_RCR 	RW }
	RNPR 	{ R AT91C_SSC_RNPR 	RW }
	TNPR 	{ R AT91C_SSC_TNPR 	RW }
	PTSR 	{ R AT91C_SSC_PTSR 	RO }
	listeReg 	{ TNCR RPR RNCR TPR PTCR TCR RCR RNPR TNPR PTSR  }

}

# ========== PIO information ========== 

array set def_PIOA_att {
 	PA0 	{  DRXD   FIQ  }
 	PA1 	{  DTXD   TCLK0  }
 	PA10 	{  TWD0   IRQ0  }
 	PA11 	{  TWCK0   PCK0  }
 	PA12 	{  TD   PWM0  }
 	PA13 	{  RD   PWM1  }
 	PA14 	{  TK   PCK2  }
 	PA15 	{  TF   TIOA0  }
 	PA16 	{  RK   NPCS2  }
 	PA17 	{  RF   NPCS3  }
 	PA18 	{  TWD1   CTS0  }
 	PA19 	{  TWCK1   RTS0  }
 	PA2 	{  TXD0   PWM0  }
 	PA20 	{  NPCS1   PCK1  }
 	PA21 	{  SCK1   TIOB0  }
 	PA22 	{  RTS1   PWM2  }
 	PA23 	{  CTS1   ADTRG  }
 	PA24 	{  TIOB1   PWM3  }
 	PA25 	{  TIOA1   PWM2  }
 	PA26 	{  TCLK1   IRQ1  }
 	PA27 	{  TIOB2   NPCS2  }
 	PA28 	{  TIOA2   PCK2  }
 	PA29 	{  TCLK2   PCK1  }
 	PA3 	{  RXD0   PWM1  }
 	PA30 	{  PWM2   NPCS1  }
 	PA31 	{  PWM3   NPCS2  }
 	PA4 	{  TXD1   SCK0  }
 	PA5 	{  RXD1   PWM3  }
 	PA6 	{  MISO   PWM2  }
 	PA7 	{  MOSI   PCK0  }
 	PA8 	{  SPCK   PCK0  }
 	PA9 	{  NPCS0   PWM2  }
 }

array set def_PIOB_att {
 	PB0 	{ }
 	PB1 	{ }
 	PB2 	{ }
 	PB3 	{ }
 }
