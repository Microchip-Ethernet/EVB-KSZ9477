# ----------------------------------------------------------------------------
#          ATMEL Microcontroller Software Support  -  ROUSSET  -
# ----------------------------------------------------------------------------
#  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
#  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
#  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------
# File Name           : AT91SAM3UE256.tcl
# Object              : AT91SAM3UE256 definitions
# Generated           : AT91 SW Application Group  02/17/2009 (15:51:20)
# 
# CVS Reference       : /AT91SAM3UE256.pl/1.31/Thu Feb  5 07:57:17 2009//
# CVS Reference       : /SYS_SAM3UE256.pl/1.4/Mon Sep 15 16:37:06 2008//
# CVS Reference       : /HMATRIX2_SAM3UE256.pl/1.2/Mon Sep 15 12:44:31 2008//
# CVS Reference       : /PMC_SAM3UE256.pl/1.7/Mon Sep 15 16:53:38 2008//
# CVS Reference       : /EBI_SAM9260.pl/1.1/Fri Sep 30 12:12:14 2005//
# CVS Reference       : /EFC2_SAM3UE256.pl/1.2/Fri Apr  4 14:40:51 2008//
# CVS Reference       : /HSDRAMC1_6100A.pl/1.2/Mon Aug  9 10:52:25 2004//
# CVS Reference       : /HSMC4_xxxx.pl/1.9/Mon Sep 15 12:48:03 2008//
# CVS Reference       : /HECC_6143A.pl/1.1/Wed Feb  9 17:16:57 2005//
# CVS Reference       : /CORTEX_M3_NVIC.pl/1.7/Thu Feb  5 07:57:20 2009//
# CVS Reference       : /CORTEX_M3_MPU.pl/1.3/Mon Sep 15 12:43:55 2008//
# CVS Reference       : /CORTEX_M3.pl/1.1/Mon Sep 15 15:22:06 2008//
# CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb  3 09:02:11 2005//
# CVS Reference       : /DBGU_SAM3UE256.pl/1.2/Tue Sep 16 06:00:35 2008//
# CVS Reference       : /PIO3_xxxx.pl/1.4/Thu Feb  5 07:57:25 2009//
# CVS Reference       : /RSTC_6098A.pl/1.4/Mon Sep 15 12:47:42 2008//
# CVS Reference       : /SHDWC_6122A.pl/1.3/Wed Oct  6 14:16:58 2004//
# CVS Reference       : /SUPC_SAM3UE256.pl/1.2/Tue May 27 08:20:16 2008//
# CVS Reference       : /RTTC_6081A.pl/1.2/Thu Nov  4 13:57:22 2004//
# CVS Reference       : /PITC_6079A.pl/1.2/Thu Nov  4 13:56:22 2004//
# CVS Reference       : /WDTC_6080A.pl/1.3/Thu Nov  4 13:58:52 2004//
# CVS Reference       : /TC_6082A.pl/1.8/Mon Sep 15 12:49:16 2008//
# CVS Reference       : /MCI_6101F.pl/1.3/Thu Feb  5 07:57:24 2009//
# CVS Reference       : /TWI_6061B.pl/1.3/Mon Sep 15 12:49:32 2008//
# CVS Reference       : /US_6089J.pl/1.3/Mon Sep 15 12:50:23 2008//
# CVS Reference       : /SSC_6078B.pl/1.3/Mon Sep 15 12:48:42 2008//
# CVS Reference       : /SPI2.pl/1.3/Mon Sep 15 12:48:25 2008//
# CVS Reference       : /PWM_6343B_V400.pl/1.3/Mon Sep 15 12:47:22 2008//
# CVS Reference       : /HDMA_SAM3UE256.pl/1.3/Mon Sep 15 12:44:11 2008//
# CVS Reference       : /UDPHS_SAM9_7ept6dma4iso.pl/1.4/Wed Jun 11 09:13:52 2008//
# CVS Reference       : /ADC_SAM3UE.pl/1.3/Mon Sep 15 12:43:39 2008//
# CVS Reference       : /RTC_1245D.pl/1.3/Fri Sep 17 14:01:31 2004//
# ----------------------------------------------------------------------------


# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR System Peripherals
# *****************************************************************************
# -------- GPBR : (SYS Offset: 0x1290) GPBR General Purpose Register -------- 
set AT91C_GPBR_GPRV       [expr 0x0 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR HSMC4 Chip Select interface
# *****************************************************************************
# -------- HSMC4_SETUP : (HSMC4_CS Offset: 0x0) HSMC4 SETUP -------- 
set AT91C_HSMC4_NWE_SETUP [expr 0x3F <<  0 ]
set AT91C_HSMC4_NCS_WR_SETUP [expr 0x3F <<  8 ]
set AT91C_HSMC4_NRD_SETUP [expr 0x3F << 16 ]
set AT91C_HSMC4_NCS_RD_SETUP [expr 0x3F << 24 ]
# -------- HSMC4_PULSE : (HSMC4_CS Offset: 0x4) HSMC4 PULSE -------- 
set AT91C_HSMC4_NWE_PULSE [expr 0x3F <<  0 ]
set AT91C_HSMC4_NCS_WR_PULSE [expr 0x3F <<  8 ]
set AT91C_HSMC4_NRD_PULSE [expr 0x3F << 16 ]
set AT91C_HSMC4_NCS_RD_PULSE [expr 0x3F << 24 ]
# -------- HSMC4_CYCLE : (HSMC4_CS Offset: 0x8) HSMC4 CYCLE -------- 
set AT91C_HSMC4_NWE_CYCLE [expr 0x1FF <<  0 ]
set AT91C_HSMC4_NRD_CYCLE [expr 0x1FF << 16 ]
# -------- HSMC4_TIMINGS : (HSMC4_CS Offset: 0xc) HSMC4 TIMINGS -------- 
set AT91C_HSMC4_TCLR      [expr 0xF <<  0 ]
set AT91C_HSMC4_TADL      [expr 0xF <<  4 ]
set AT91C_HSMC4_TAR       [expr 0xF <<  8 ]
set AT91C_HSMC4_OCMSEN    [expr 0x1 << 12 ]
set AT91C_HSMC4_TRR       [expr 0xF << 16 ]
set AT91C_HSMC4_TWB       [expr 0xF << 24 ]
set AT91C_HSMC4_RBNSEL    [expr 0x7 << 28 ]
set AT91C_HSMC4_NFSEL     [expr 0x1 << 31 ]
# -------- HSMC4_MODE : (HSMC4_CS Offset: 0x10) HSMC4 MODE -------- 
set AT91C_HSMC4_READ_MODE [expr 0x1 <<  0 ]
set AT91C_HSMC4_WRITE_MODE [expr 0x1 <<  1 ]
set AT91C_HSMC4_EXNW_MODE [expr 0x3 <<  4 ]
set 	AT91C_HSMC4_EXNW_MODE_NWAIT_DISABLE        [expr 0x0 <<  4 ]
set 	AT91C_HSMC4_EXNW_MODE_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  4 ]
set 	AT91C_HSMC4_EXNW_MODE_NWAIT_ENABLE_READY   [expr 0x3 <<  4 ]
set AT91C_HSMC4_BAT       [expr 0x1 <<  8 ]
set 	AT91C_HSMC4_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_HSMC4_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_HSMC4_DBW       [expr 0x3 << 12 ]
set 	AT91C_HSMC4_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_HSMC4_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_HSMC4_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_HSMC4_TDF_CYCLES [expr 0xF << 16 ]
set AT91C_HSMC4_TDF_MODE  [expr 0x1 << 20 ]
set AT91C_HSMC4_PMEN      [expr 0x1 << 24 ]
set AT91C_HSMC4_PS        [expr 0x3 << 28 ]
set 	AT91C_HSMC4_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_HSMC4_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_HSMC4_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_HSMC4_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AHB Static Memory Controller 4 Interface
# *****************************************************************************
# -------- HSMC4_CFG : (HSMC4 Offset: 0x0) Configuration Register -------- 
set AT91C_HSMC4_PAGESIZE  [expr 0x3 <<  0 ]
set 	AT91C_HSMC4_PAGESIZE_528_Bytes            0x0
set 	AT91C_HSMC4_PAGESIZE_1056_Bytes           0x1
set 	AT91C_HSMC4_PAGESIZE_2112_Bytes           0x2
set 	AT91C_HSMC4_PAGESIZE_4224_Bytes           0x3
set AT91C_HSMC4_WSPARE    [expr 0x1 <<  8 ]
set AT91C_HSMC4_RSPARE    [expr 0x1 <<  9 ]
set AT91C_HSMC4_EDGECTRL  [expr 0x1 << 12 ]
set AT91C_HSMC4_RBEDGE    [expr 0x1 << 13 ]
set AT91C_HSMC4_DTOCYC    [expr 0xF << 16 ]
set AT91C_HSMC4_DTOMUL    [expr 0x7 << 20 ]
set 	AT91C_HSMC4_DTOMUL_1                    [expr 0x0 << 20 ]
set 	AT91C_HSMC4_DTOMUL_16                   [expr 0x1 << 20 ]
set 	AT91C_HSMC4_DTOMUL_128                  [expr 0x2 << 20 ]
set 	AT91C_HSMC4_DTOMUL_256                  [expr 0x3 << 20 ]
set 	AT91C_HSMC4_DTOMUL_1024                 [expr 0x4 << 20 ]
set 	AT91C_HSMC4_DTOMUL_4096                 [expr 0x5 << 20 ]
set 	AT91C_HSMC4_DTOMUL_65536                [expr 0x6 << 20 ]
set 	AT91C_HSMC4_DTOMUL_1048576              [expr 0x7 << 20 ]
# -------- HSMC4_CTRL : (HSMC4 Offset: 0x4) Control Register -------- 
set AT91C_HSMC4_NFCEN     [expr 0x1 <<  0 ]
set AT91C_HSMC4_NFCDIS    [expr 0x1 <<  1 ]
set AT91C_HSMC4_HOSTEN    [expr 0x1 <<  8 ]
set AT91C_HSMC4_HOSTWR    [expr 0x1 << 11 ]
set AT91C_HSMC4_HOSTCSID  [expr 0x7 << 12 ]
set 	AT91C_HSMC4_HOSTCSID_0                    [expr 0x0 << 12 ]
set 	AT91C_HSMC4_HOSTCSID_1                    [expr 0x1 << 12 ]
set 	AT91C_HSMC4_HOSTCSID_2                    [expr 0x2 << 12 ]
set 	AT91C_HSMC4_HOSTCSID_3                    [expr 0x3 << 12 ]
set 	AT91C_HSMC4_HOSTCSID_4                    [expr 0x4 << 12 ]
set 	AT91C_HSMC4_HOSTCSID_5                    [expr 0x5 << 12 ]
set 	AT91C_HSMC4_HOSTCSID_6                    [expr 0x6 << 12 ]
set 	AT91C_HSMC4_HOSTCSID_7                    [expr 0x7 << 12 ]
set AT91C_HSMC4_VALID     [expr 0x1 << 15 ]
# -------- HSMC4_SR : (HSMC4 Offset: 0x8) HSMC4 Status Register -------- 
set AT91C_HSMC4_NFCSTS    [expr 0x1 <<  0 ]
set AT91C_HSMC4_RBRISE    [expr 0x1 <<  4 ]
set AT91C_HSMC4_RBFALL    [expr 0x1 <<  5 ]
set AT91C_HSMC4_HOSTBUSY  [expr 0x1 <<  8 ]
set AT91C_HSMC4_HOSTW     [expr 0x1 << 11 ]
set AT91C_HSMC4_HOSTCS    [expr 0x7 << 12 ]
set 	AT91C_HSMC4_HOSTCS_0                    [expr 0x0 << 12 ]
set 	AT91C_HSMC4_HOSTCS_1                    [expr 0x1 << 12 ]
set 	AT91C_HSMC4_HOSTCS_2                    [expr 0x2 << 12 ]
set 	AT91C_HSMC4_HOSTCS_3                    [expr 0x3 << 12 ]
set 	AT91C_HSMC4_HOSTCS_4                    [expr 0x4 << 12 ]
set 	AT91C_HSMC4_HOSTCS_5                    [expr 0x5 << 12 ]
set 	AT91C_HSMC4_HOSTCS_6                    [expr 0x6 << 12 ]
set 	AT91C_HSMC4_HOSTCS_7                    [expr 0x7 << 12 ]
set AT91C_HSMC4_XFRDONE   [expr 0x1 << 16 ]
set AT91C_HSMC4_CMDDONE   [expr 0x1 << 17 ]
set AT91C_HSMC4_ECCRDY    [expr 0x1 << 18 ]
set AT91C_HSMC4_DTOE      [expr 0x1 << 20 ]
set AT91C_HSMC4_UNDEF     [expr 0x1 << 21 ]
set AT91C_HSMC4_AWB       [expr 0x1 << 22 ]
set AT91C_HSMC4_HASE      [expr 0x1 << 23 ]
set AT91C_HSMC4_RBEDGE0   [expr 0x1 << 24 ]
set AT91C_HSMC4_RBEDGE1   [expr 0x1 << 25 ]
set AT91C_HSMC4_RBEDGE2   [expr 0x1 << 26 ]
set AT91C_HSMC4_RBEDGE3   [expr 0x1 << 27 ]
set AT91C_HSMC4_RBEDGE4   [expr 0x1 << 28 ]
set AT91C_HSMC4_RBEDGE5   [expr 0x1 << 29 ]
set AT91C_HSMC4_RBEDGE6   [expr 0x1 << 30 ]
set AT91C_HSMC4_RBEDGE7   [expr 0x1 << 31 ]
# -------- HSMC4_IER : (HSMC4 Offset: 0xc) HSMC4 Interrupt Enable Register -------- 
set AT91C_HSMC4_NFCSTS    [expr 0x1 <<  0 ]
set AT91C_HSMC4_RBRISE    [expr 0x1 <<  4 ]
set AT91C_HSMC4_RBFALL    [expr 0x1 <<  5 ]
set AT91C_HSMC4_HOSTBUSY  [expr 0x1 <<  8 ]
set AT91C_HSMC4_HOSTW     [expr 0x1 << 11 ]
set AT91C_HSMC4_HOSTCS    [expr 0x7 << 12 ]
set 	AT91C_HSMC4_HOSTCS_0                    [expr 0x0 << 12 ]
set 	AT91C_HSMC4_HOSTCS_1                    [expr 0x1 << 12 ]
set 	AT91C_HSMC4_HOSTCS_2                    [expr 0x2 << 12 ]
set 	AT91C_HSMC4_HOSTCS_3                    [expr 0x3 << 12 ]
set 	AT91C_HSMC4_HOSTCS_4                    [expr 0x4 << 12 ]
set 	AT91C_HSMC4_HOSTCS_5                    [expr 0x5 << 12 ]
set 	AT91C_HSMC4_HOSTCS_6                    [expr 0x6 << 12 ]
set 	AT91C_HSMC4_HOSTCS_7                    [expr 0x7 << 12 ]
set AT91C_HSMC4_XFRDONE   [expr 0x1 << 16 ]
set AT91C_HSMC4_CMDDONE   [expr 0x1 << 17 ]
set AT91C_HSMC4_ECCRDY    [expr 0x1 << 18 ]
set AT91C_HSMC4_DTOE      [expr 0x1 << 20 ]
set AT91C_HSMC4_UNDEF     [expr 0x1 << 21 ]
set AT91C_HSMC4_AWB       [expr 0x1 << 22 ]
set AT91C_HSMC4_HASE      [expr 0x1 << 23 ]
set AT91C_HSMC4_RBEDGE0   [expr 0x1 << 24 ]
set AT91C_HSMC4_RBEDGE1   [expr 0x1 << 25 ]
set AT91C_HSMC4_RBEDGE2   [expr 0x1 << 26 ]
set AT91C_HSMC4_RBEDGE3   [expr 0x1 << 27 ]
set AT91C_HSMC4_RBEDGE4   [expr 0x1 << 28 ]
set AT91C_HSMC4_RBEDGE5   [expr 0x1 << 29 ]
set AT91C_HSMC4_RBEDGE6   [expr 0x1 << 30 ]
set AT91C_HSMC4_RBEDGE7   [expr 0x1 << 31 ]
# -------- HSMC4_IDR : (HSMC4 Offset: 0x10) HSMC4 Interrupt Disable Register -------- 
set AT91C_HSMC4_NFCSTS    [expr 0x1 <<  0 ]
set AT91C_HSMC4_RBRISE    [expr 0x1 <<  4 ]
set AT91C_HSMC4_RBFALL    [expr 0x1 <<  5 ]
set AT91C_HSMC4_HOSTBUSY  [expr 0x1 <<  8 ]
set AT91C_HSMC4_HOSTW     [expr 0x1 << 11 ]
set AT91C_HSMC4_HOSTCS    [expr 0x7 << 12 ]
set 	AT91C_HSMC4_HOSTCS_0                    [expr 0x0 << 12 ]
set 	AT91C_HSMC4_HOSTCS_1                    [expr 0x1 << 12 ]
set 	AT91C_HSMC4_HOSTCS_2                    [expr 0x2 << 12 ]
set 	AT91C_HSMC4_HOSTCS_3                    [expr 0x3 << 12 ]
set 	AT91C_HSMC4_HOSTCS_4                    [expr 0x4 << 12 ]
set 	AT91C_HSMC4_HOSTCS_5                    [expr 0x5 << 12 ]
set 	AT91C_HSMC4_HOSTCS_6                    [expr 0x6 << 12 ]
set 	AT91C_HSMC4_HOSTCS_7                    [expr 0x7 << 12 ]
set AT91C_HSMC4_XFRDONE   [expr 0x1 << 16 ]
set AT91C_HSMC4_CMDDONE   [expr 0x1 << 17 ]
set AT91C_HSMC4_ECCRDY    [expr 0x1 << 18 ]
set AT91C_HSMC4_DTOE      [expr 0x1 << 20 ]
set AT91C_HSMC4_UNDEF     [expr 0x1 << 21 ]
set AT91C_HSMC4_AWB       [expr 0x1 << 22 ]
set AT91C_HSMC4_HASE      [expr 0x1 << 23 ]
set AT91C_HSMC4_RBEDGE0   [expr 0x1 << 24 ]
set AT91C_HSMC4_RBEDGE1   [expr 0x1 << 25 ]
set AT91C_HSMC4_RBEDGE2   [expr 0x1 << 26 ]
set AT91C_HSMC4_RBEDGE3   [expr 0x1 << 27 ]
set AT91C_HSMC4_RBEDGE4   [expr 0x1 << 28 ]
set AT91C_HSMC4_RBEDGE5   [expr 0x1 << 29 ]
set AT91C_HSMC4_RBEDGE6   [expr 0x1 << 30 ]
set AT91C_HSMC4_RBEDGE7   [expr 0x1 << 31 ]
# -------- HSMC4_IMR : (HSMC4 Offset: 0x14) HSMC4 Interrupt Mask Register -------- 
set AT91C_HSMC4_NFCSTS    [expr 0x1 <<  0 ]
set AT91C_HSMC4_RBRISE    [expr 0x1 <<  4 ]
set AT91C_HSMC4_RBFALL    [expr 0x1 <<  5 ]
set AT91C_HSMC4_HOSTBUSY  [expr 0x1 <<  8 ]
set AT91C_HSMC4_HOSTW     [expr 0x1 << 11 ]
set AT91C_HSMC4_HOSTCS    [expr 0x7 << 12 ]
set 	AT91C_HSMC4_HOSTCS_0                    [expr 0x0 << 12 ]
set 	AT91C_HSMC4_HOSTCS_1                    [expr 0x1 << 12 ]
set 	AT91C_HSMC4_HOSTCS_2                    [expr 0x2 << 12 ]
set 	AT91C_HSMC4_HOSTCS_3                    [expr 0x3 << 12 ]
set 	AT91C_HSMC4_HOSTCS_4                    [expr 0x4 << 12 ]
set 	AT91C_HSMC4_HOSTCS_5                    [expr 0x5 << 12 ]
set 	AT91C_HSMC4_HOSTCS_6                    [expr 0x6 << 12 ]
set 	AT91C_HSMC4_HOSTCS_7                    [expr 0x7 << 12 ]
set AT91C_HSMC4_XFRDONE   [expr 0x1 << 16 ]
set AT91C_HSMC4_CMDDONE   [expr 0x1 << 17 ]
set AT91C_HSMC4_ECCRDY    [expr 0x1 << 18 ]
set AT91C_HSMC4_DTOE      [expr 0x1 << 20 ]
set AT91C_HSMC4_UNDEF     [expr 0x1 << 21 ]
set AT91C_HSMC4_AWB       [expr 0x1 << 22 ]
set AT91C_HSMC4_HASE      [expr 0x1 << 23 ]
set AT91C_HSMC4_RBEDGE0   [expr 0x1 << 24 ]
set AT91C_HSMC4_RBEDGE1   [expr 0x1 << 25 ]
set AT91C_HSMC4_RBEDGE2   [expr 0x1 << 26 ]
set AT91C_HSMC4_RBEDGE3   [expr 0x1 << 27 ]
set AT91C_HSMC4_RBEDGE4   [expr 0x1 << 28 ]
set AT91C_HSMC4_RBEDGE5   [expr 0x1 << 29 ]
set AT91C_HSMC4_RBEDGE6   [expr 0x1 << 30 ]
set AT91C_HSMC4_RBEDGE7   [expr 0x1 << 31 ]
# -------- HSMC4_ADDR : (HSMC4 Offset: 0x18) Address Cycle Zero Register -------- 
set AT91C_HSMC4_ADDRCYCLE0 [expr 0xFF <<  0 ]
# -------- HSMC4_BANK : (HSMC4 Offset: 0x1c) Bank Register -------- 
set AT91C_BANK            [expr 0x7 <<  0 ]
set 	AT91C_BANK_0                    0x0
set 	AT91C_BANK_1                    0x1
set 	AT91C_BANK_2                    0x2
set 	AT91C_BANK_3                    0x3
set 	AT91C_BANK_4                    0x4
set 	AT91C_BANK_5                    0x5
set 	AT91C_BANK_6                    0x6
set 	AT91C_BANK_7                    0x7
# -------- HSMC4_ECCCR : (HSMC4 Offset: 0x20) ECC Control Register -------- 
set AT91C_HSMC4_ECCRESET  [expr 0x1 <<  0 ]
# -------- HSMC4_ECCCMD : (HSMC4 Offset: 0x24) ECC mode register -------- 
set AT91C_ECC_PAGE_SIZE   [expr 0x3 <<  0 ]
set AT91C_ECC_TYPCORRECT  [expr 0x3 <<  4 ]
set 	AT91C_ECC_TYPCORRECT_ONE_PER_PAGE         [expr 0x0 <<  4 ]
set 	AT91C_ECC_TYPCORRECT_ONE_EVERY_256_BYTES  [expr 0x1 <<  4 ]
set 	AT91C_ECC_TYPCORRECT_ONE_EVERY_512_BYTES  [expr 0x2 <<  4 ]
# -------- HSMC4_ECCSR1 : (HSMC4 Offset: 0x28) ECC Status Register 1 -------- 
set AT91C_HSMC4_ECC_RECERR0 [expr 0x1 <<  0 ]
set AT91C_HSMC4_ECC_ECCERR0 [expr 0x1 <<  1 ]
set AT91C_HSMC4_ECC_MULERR0 [expr 0x1 <<  2 ]
set AT91C_HSMC4_ECC_RECERR1 [expr 0x1 <<  4 ]
set AT91C_HSMC4_ECC_ECCERR1 [expr 0x1 <<  5 ]
set AT91C_HSMC4_ECC_MULERR1 [expr 0x1 <<  6 ]
set AT91C_HSMC4_ECC_RECERR2 [expr 0x1 <<  8 ]
set AT91C_HSMC4_ECC_ECCERR2 [expr 0x1 <<  9 ]
set AT91C_HSMC4_ECC_MULERR2 [expr 0x1 << 10 ]
set AT91C_HSMC4_ECC_RECERR3 [expr 0x1 << 12 ]
set AT91C_HSMC4_ECC_ECCERR3 [expr 0x1 << 13 ]
set AT91C_HSMC4_ECC_MULERR3 [expr 0x1 << 14 ]
set AT91C_HSMC4_ECC_RECERR4 [expr 0x1 << 16 ]
set AT91C_HSMC4_ECC_ECCERR4 [expr 0x1 << 17 ]
set AT91C_HSMC4_ECC_MULERR4 [expr 0x1 << 18 ]
set AT91C_HSMC4_ECC_RECERR5 [expr 0x1 << 20 ]
set AT91C_HSMC4_ECC_ECCERR5 [expr 0x1 << 21 ]
set AT91C_HSMC4_ECC_MULERR5 [expr 0x1 << 22 ]
set AT91C_HSMC4_ECC_RECERR6 [expr 0x1 << 24 ]
set AT91C_HSMC4_ECC_ECCERR6 [expr 0x1 << 25 ]
set AT91C_HSMC4_ECC_MULERR6 [expr 0x1 << 26 ]
set AT91C_HSMC4_ECC_RECERR7 [expr 0x1 << 28 ]
set AT91C_HSMC4_ECC_ECCERR7 [expr 0x1 << 29 ]
set AT91C_HSMC4_ECC_MULERR7 [expr 0x1 << 30 ]
# -------- HSMC4_ECCPR0 : (HSMC4 Offset: 0x2c) HSMC4 ECC parity Register 0 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR1 : (HSMC4 Offset: 0x30) HSMC4 ECC parity Register 1 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCSR2 : (HSMC4 Offset: 0x34) ECC Status Register 2 -------- 
set AT91C_HSMC4_ECC_RECERR8 [expr 0x1 <<  0 ]
set AT91C_HSMC4_ECC_ECCERR8 [expr 0x1 <<  1 ]
set AT91C_HSMC4_ECC_MULERR8 [expr 0x1 <<  2 ]
set AT91C_HSMC4_ECC_RECERR9 [expr 0x1 <<  4 ]
set AT91C_HSMC4_ECC_ECCERR9 [expr 0x1 <<  5 ]
set AT91C_HSMC4_ECC_MULERR9 [expr 0x1 <<  6 ]
set AT91C_HSMC4_ECC_RECERR10 [expr 0x1 <<  8 ]
set AT91C_HSMC4_ECC_ECCERR10 [expr 0x1 <<  9 ]
set AT91C_HSMC4_ECC_MULERR10 [expr 0x1 << 10 ]
set AT91C_HSMC4_ECC_RECERR11 [expr 0x1 << 12 ]
set AT91C_HSMC4_ECC_ECCERR11 [expr 0x1 << 13 ]
set AT91C_HSMC4_ECC_MULERR11 [expr 0x1 << 14 ]
set AT91C_HSMC4_ECC_RECERR12 [expr 0x1 << 16 ]
set AT91C_HSMC4_ECC_ECCERR12 [expr 0x1 << 17 ]
set AT91C_HSMC4_ECC_MULERR12 [expr 0x1 << 18 ]
set AT91C_HSMC4_ECC_RECERR13 [expr 0x1 << 20 ]
set AT91C_HSMC4_ECC_ECCERR13 [expr 0x1 << 21 ]
set AT91C_HSMC4_ECC_MULERR13 [expr 0x1 << 22 ]
set AT91C_HSMC4_ECC_RECERR14 [expr 0x1 << 24 ]
set AT91C_HSMC4_ECC_ECCERR14 [expr 0x1 << 25 ]
set AT91C_HSMC4_ECC_MULERR14 [expr 0x1 << 26 ]
set AT91C_HSMC4_ECC_RECERR15 [expr 0x1 << 28 ]
set AT91C_HSMC4_ECC_ECCERR15 [expr 0x1 << 29 ]
set AT91C_HSMC4_ECC_MULERR15 [expr 0x1 << 30 ]
# -------- HSMC4_ECCPR2 : (HSMC4 Offset: 0x38) HSMC4 ECC parity Register 2 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR3 : (HSMC4 Offset: 0x3c) HSMC4 ECC parity Register 3 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR4 : (HSMC4 Offset: 0x40) HSMC4 ECC parity Register 4 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR5 : (HSMC4 Offset: 0x44) HSMC4 ECC parity Register 5 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR6 : (HSMC4 Offset: 0x48) HSMC4 ECC parity Register 6 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR7 : (HSMC4 Offset: 0x4c) HSMC4 ECC parity Register 7 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR8 : (HSMC4 Offset: 0x50) HSMC4 ECC parity Register 8 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR9 : (HSMC4 Offset: 0x54) HSMC4 ECC parity Register 9 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR10 : (HSMC4 Offset: 0x58) HSMC4 ECC parity Register 10 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR11 : (HSMC4 Offset: 0x5c) HSMC4 ECC parity Register 11 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR12 : (HSMC4 Offset: 0x60) HSMC4 ECC parity Register 12 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR13 : (HSMC4 Offset: 0x64) HSMC4 ECC parity Register 13 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR14 : (HSMC4 Offset: 0x68) HSMC4 ECC parity Register 14 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_ECCPR15 : (HSMC4 Offset: 0x6c) HSMC4 ECC parity Register 15 -------- 
set AT91C_HSMC4_ECC_BITADDR [expr 0x7 <<  0 ]
set AT91C_HSMC4_ECC_WORDADDR [expr 0xFF <<  3 ]
set AT91C_HSMC4_ECC_NPARITY [expr 0x7FF << 12 ]
# -------- HSMC4_OCMS : (HSMC4 Offset: 0x110) HSMC4 OCMS Register -------- 
set AT91C_HSMC4_OCMS_SRSE [expr 0x1 <<  0 ]
set AT91C_HSMC4_OCMS_SMSE [expr 0x1 <<  1 ]
# -------- HSMC4_KEY1 : (HSMC4 Offset: 0x114) HSMC4 OCMS KEY1 Register -------- 
set AT91C_HSMC4_OCMS_KEY1 [expr 0x0 <<  0 ]
# -------- HSMC4_OCMS_KEY2 : (HSMC4 Offset: 0x118) HSMC4 OCMS KEY2 Register -------- 
set AT91C_HSMC4_OCMS_KEY2 [expr 0x0 <<  0 ]
# -------- HSMC4_WPCR : (HSMC4 Offset: 0x1e4) HSMC4 Witre Protection Control Register -------- 
set AT91C_HSMC4_WP_EN     [expr 0x1 <<  0 ]
set AT91C_HSMC4_WP_KEY    [expr 0xFFFFFF <<  8 ]
# -------- HSMC4_WPSR : (HSMC4 Offset: 0x1e8) HSMC4 WPSR Register -------- 
set AT91C_HSMC4_WP_VS     [expr 0xF <<  0 ]
set 	AT91C_HSMC4_WP_VS_WP_VS0               0x0
set 	AT91C_HSMC4_WP_VS_WP_VS1               0x1
set 	AT91C_HSMC4_WP_VS_WP_VS2               0x2
set 	AT91C_HSMC4_WP_VS_WP_VS3               0x3
set AT91C_                [expr 0x0 <<  8 ]
# -------- HSMC4_VER : (HSMC4 Offset: 0x1fc) HSMC4 VERSION Register -------- 
set AT91C_                [expr 0x0 <<  0 ]
set AT91C_                [expr 0x0 << 16 ]
# -------- HSMC4_DUMMY : (HSMC4 Offset: 0x200) HSMC4 DUMMY REGISTER -------- 
set AT91C_HSMC4_CMD1      [expr 0xFF <<  2 ]
set AT91C_HSMC4_CMD2      [expr 0xFF << 10 ]
set AT91C_HSMC4_VCMD2     [expr 0x1 << 18 ]
set AT91C_HSMC4_ACYCLE    [expr 0x7 << 19 ]
set 	AT91C_HSMC4_ACYCLE_HSMC4_ACYCLE_NONE    [expr 0x0 << 19 ]
set 	AT91C_HSMC4_ACYCLE_HSMC4_ACYCLE_ONE     [expr 0x1 << 19 ]
set 	AT91C_HSMC4_ACYCLE_HSMC4_ACYCLE_TWO     [expr 0x2 << 19 ]
set 	AT91C_HSMC4_ACYCLE_HSMC4_ACYCLE_THREE   [expr 0x3 << 19 ]
set 	AT91C_HSMC4_ACYCLE_HSMC4_ACYCLE_FOUR    [expr 0x4 << 19 ]
set 	AT91C_HSMC4_ACYCLE_HSMC4_ACYCLE_FIVE    [expr 0x5 << 19 ]
set AT91C_HSMC4_CSID      [expr 0x7 << 22 ]
set 	AT91C_HSMC4_CSID_0                    [expr 0x0 << 22 ]
set 	AT91C_HSMC4_CSID_1                    [expr 0x1 << 22 ]
set 	AT91C_HSMC4_CSID_2                    [expr 0x2 << 22 ]
set 	AT91C_HSMC4_CSID_3                    [expr 0x3 << 22 ]
set 	AT91C_HSMC4_CSID_4                    [expr 0x4 << 22 ]
set 	AT91C_HSMC4_CSID_5                    [expr 0x5 << 22 ]
set 	AT91C_HSMC4_CSID_6                    [expr 0x6 << 22 ]
set 	AT91C_HSMC4_CSID_7                    [expr 0x7 << 22 ]
set AT91C_HSMC4_HOST_EN   [expr 0x1 << 25 ]
set AT91C_HSMC4_HOST_WR   [expr 0x1 << 26 ]
set AT91C_HSMC4_HOSTCMD   [expr 0x1 << 27 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AHB Matrix2 Interface
# *****************************************************************************
# -------- MATRIX_MCFG0 : (HMATRIX2 Offset: 0x0) Master Configuration Register ARM bus I and D -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG1 : (HMATRIX2 Offset: 0x4) Master Configuration Register ARM bus S -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG2 : (HMATRIX2 Offset: 0x8) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG3 : (HMATRIX2 Offset: 0xc) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG4 : (HMATRIX2 Offset: 0x10) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG5 : (HMATRIX2 Offset: 0x14) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG6 : (HMATRIX2 Offset: 0x18) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG7 : (HMATRIX2 Offset: 0x1c) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_SCFG0 : (HMATRIX2 Offset: 0x40) Slave Configuration Register 0 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG0 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG0_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG1 : (HMATRIX2 Offset: 0x44) Slave Configuration Register 1 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG1 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG1_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG2 : (HMATRIX2 Offset: 0x48) Slave Configuration Register 2 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG2 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG2_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG3 : (HMATRIX2 Offset: 0x4c) Slave Configuration Register 3 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG3 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG3_ARMC                 [expr 0x0 << 18 ]
# -------- MATRIX_SCFG4 : (HMATRIX2 Offset: 0x50) Slave Configuration Register 4 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG4 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG4_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG5 : (HMATRIX2 Offset: 0x54) Slave Configuration Register 5 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG5 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG5_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG6 : (HMATRIX2 Offset: 0x58) Slave Configuration Register 6 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG6 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG6_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG7 : (HMATRIX2 Offset: 0x5c) Slave Configuration Register 7 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG7 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG7_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG8 : (HMATRIX2 Offset: 0x60) Slave Configuration Register 8 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG8 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG8_ARMS                 [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG8_HDMA                 [expr 0x4 << 18 ]
# -------- HMATRIX2_VER : (HMATRIX2 Offset: 0x1fc)  VERSION  Register -------- 
set AT91C_HMATRIX2_VER    [expr 0xF <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR NESTED vector Interrupt Controller
# *****************************************************************************
# -------- NVIC_ICTR : (NVIC Offset: 0x4) Interrupt Controller Type Register -------- 
set AT91C_NVIC_INTLINESNUM [expr 0xF <<  0 ]
set 	AT91C_NVIC_INTLINESNUM_32                   0x0
set 	AT91C_NVIC_INTLINESNUM_64                   0x1
set 	AT91C_NVIC_INTLINESNUM_96                   0x2
set 	AT91C_NVIC_INTLINESNUM_128                  0x3
set 	AT91C_NVIC_INTLINESNUM_160                  0x4
set 	AT91C_NVIC_INTLINESNUM_192                  0x5
set 	AT91C_NVIC_INTLINESNUM_224                  0x6
set 	AT91C_NVIC_INTLINESNUM_256                  0x7
set 	AT91C_NVIC_INTLINESNUM_288                  0x8
set 	AT91C_NVIC_INTLINESNUM_320                  0x9
set 	AT91C_NVIC_INTLINESNUM_352                  0xA
set 	AT91C_NVIC_INTLINESNUM_384                  0xB
set 	AT91C_NVIC_INTLINESNUM_416                  0xC
set 	AT91C_NVIC_INTLINESNUM_448                  0xD
set 	AT91C_NVIC_INTLINESNUM_480                  0xE
set 	AT91C_NVIC_INTLINESNUM_496                  0xF
# -------- NVIC_STICKCSR : (NVIC Offset: 0x10) SysTick Control and Status Register -------- 
set AT91C_NVIC_STICKENABLE [expr 0x1 <<  0 ]
set AT91C_NVIC_STICKINT   [expr 0x1 <<  1 ]
set AT91C_NVIC_STICKCLKSOURCE [expr 0x1 <<  2 ]
set AT91C_NVIC_STICKCOUNTFLAG [expr 0x1 << 16 ]
# -------- NVIC_STICKRVR : (NVIC Offset: 0x14) SysTick Reload Value Register -------- 
set AT91C_NVIC_STICKRELOAD [expr 0xFFFFFF <<  0 ]
# -------- NVIC_STICKCVR : (NVIC Offset: 0x18) SysTick Current Value Register -------- 
set AT91C_NVIC_STICKCURRENT [expr 0x7FFFFFFF <<  0 ]
# -------- NVIC_STICKCALVR : (NVIC Offset: 0x1c) SysTick Calibration Value Register -------- 
set AT91C_NVIC_STICKTENMS [expr 0xFFFFFF <<  0 ]
set AT91C_NVIC_STICKSKEW  [expr 0x1 << 30 ]
set AT91C_NVIC_STICKNOREF [expr 0x1 << 31 ]
# -------- NVIC_IPR : (NVIC Offset: 0x400) Interrupt Priority Registers -------- 
set AT91C_NVIC_PRI_N      [expr 0xFF <<  0 ]
set AT91C_NVIC_PRI_N1     [expr 0xFF <<  8 ]
set AT91C_NVIC_PRI_N2     [expr 0xFF << 16 ]
set AT91C_NVIC_PRI_N3     [expr 0xFF << 24 ]
# -------- NVIC_CPUID : (NVIC Offset: 0xd00) CPU ID Base Register -------- 
set AT91C_NVIC_REVISION   [expr 0xF <<  0 ]
set AT91C_NVIC_PARTNO     [expr 0xFFF <<  4 ]
set AT91C_NVIC_CONSTANT   [expr 0xF << 16 ]
set AT91C_NVIC_VARIANT    [expr 0xF << 20 ]
set AT91C_NVIC_IMPLEMENTER [expr 0xFF << 24 ]
# -------- NVIC_ICSR : (NVIC Offset: 0xd04) Interrupt Control State Register -------- 
set AT91C_NVIC_VECTACTIVE [expr 0x1FF <<  0 ]
set AT91C_NVIC_RETTOBASE  [expr 0x1 << 11 ]
set AT91C_NVIC_VECTPENDING [expr 0x1FF << 12 ]
set AT91C_NVIC_ISRPENDING [expr 0x1 << 22 ]
set AT91C_NVIC_ISRPREEMPT [expr 0x1 << 23 ]
set AT91C_NVIC_PENDSTCLR  [expr 0x1 << 25 ]
set AT91C_NVIC_PENDSTSET  [expr 0x1 << 26 ]
set AT91C_NVIC_PENDSVCLR  [expr 0x1 << 27 ]
set AT91C_NVIC_PENDSVSET  [expr 0x1 << 28 ]
set AT91C_NVIC_NMIPENDSET [expr 0x1 << 31 ]
# -------- NVIC_VTOFFR : (NVIC Offset: 0xd08) Vector Table Offset Register -------- 
set AT91C_NVIC_TBLOFF     [expr 0x3FFFFF <<  7 ]
set AT91C_NVIC_TBLBASE    [expr 0x1 << 29 ]
set 	AT91C_NVIC_TBLBASE_CODE                 [expr 0x0 << 29 ]
set 	AT91C_NVIC_TBLBASE_RAM                  [expr 0x1 << 29 ]
# -------- NVIC_AIRCR : (NVIC Offset: 0xd0c) Application Interrupt and Reset Control Register -------- 
set AT91C_NVIC_VECTRESET  [expr 0x1 <<  0 ]
set AT91C_NVIC_VECTCLRACTIVE [expr 0x1 <<  1 ]
set AT91C_NVIC_SYSRESETREQ [expr 0x1 <<  2 ]
set AT91C_NVIC_PRIGROUP   [expr 0x7 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_0                    [expr 0x0 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_1                    [expr 0x1 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_2                    [expr 0x2 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_3                    [expr 0x3 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_4                    [expr 0x4 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_5                    [expr 0x5 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_6                    [expr 0x6 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_7                    [expr 0x7 <<  8 ]
set AT91C_NVIC_ENDIANESS  [expr 0x1 << 15 ]
set AT91C_NVIC_VECTKEY    [expr 0xFFFF << 16 ]
# -------- NVIC_SCR : (NVIC Offset: 0xd10) System Control Register -------- 
set AT91C_NVIC_SLEEPONEXIT [expr 0x1 <<  1 ]
set AT91C_NVIC_SLEEPDEEP  [expr 0x1 <<  2 ]
set AT91C_NVIC_SEVONPEND  [expr 0x1 <<  4 ]
# -------- NVIC_CCR : (NVIC Offset: 0xd14) Configuration Control Register -------- 
set AT91C_NVIC_NONEBASETHRDENA [expr 0x1 <<  0 ]
set AT91C_NVIC_USERSETMPEND [expr 0x1 <<  1 ]
set AT91C_NVIC_UNALIGN_TRP [expr 0x1 <<  3 ]
set AT91C_NVIC_DIV_0_TRP  [expr 0x1 <<  4 ]
set AT91C_NVIC_BFHFNMIGN  [expr 0x1 <<  8 ]
set AT91C_NVIC_STKALIGN   [expr 0x1 <<  9 ]
# -------- NVIC_HAND4PR : (NVIC Offset: 0xd18) System Handlers 4-7 Priority Register -------- 
set AT91C_NVIC_PRI_4      [expr 0xFF <<  0 ]
set AT91C_NVIC_PRI_5      [expr 0xFF <<  8 ]
set AT91C_NVIC_PRI_6      [expr 0xFF << 16 ]
set AT91C_NVIC_PRI_7      [expr 0xFF << 24 ]
# -------- NVIC_HAND8PR : (NVIC Offset: 0xd1c) System Handlers 8-11 Priority Register -------- 
set AT91C_NVIC_PRI_8      [expr 0xFF <<  0 ]
set AT91C_NVIC_PRI_9      [expr 0xFF <<  8 ]
set AT91C_NVIC_PRI_10     [expr 0xFF << 16 ]
set AT91C_NVIC_PRI_11     [expr 0xFF << 24 ]
# -------- NVIC_HAND12PR : (NVIC Offset: 0xd20) System Handlers 12-15 Priority Register -------- 
set AT91C_NVIC_PRI_12     [expr 0xFF <<  0 ]
set AT91C_NVIC_PRI_13     [expr 0xFF <<  8 ]
set AT91C_NVIC_PRI_14     [expr 0xFF << 16 ]
set AT91C_NVIC_PRI_15     [expr 0xFF << 24 ]
# -------- NVIC_HANDCSR : (NVIC Offset: 0xd24) System Handler Control and State Register -------- 
set AT91C_NVIC_MEMFAULTACT [expr 0x1 <<  0 ]
set AT91C_NVIC_BUSFAULTACT [expr 0x1 <<  1 ]
set AT91C_NVIC_USGFAULTACT [expr 0x1 <<  3 ]
set AT91C_NVIC_SVCALLACT  [expr 0x1 <<  7 ]
set AT91C_NVIC_MONITORACT [expr 0x1 <<  8 ]
set AT91C_NVIC_PENDSVACT  [expr 0x1 << 10 ]
set AT91C_NVIC_SYSTICKACT [expr 0x1 << 11 ]
set AT91C_NVIC_USGFAULTPENDED [expr 0x1 << 12 ]
set AT91C_NVIC_MEMFAULTPENDED [expr 0x1 << 13 ]
set AT91C_NVIC_BUSFAULTPENDED [expr 0x1 << 14 ]
set AT91C_NVIC_SVCALLPENDED [expr 0x1 << 15 ]
set AT91C_NVIC_MEMFAULTENA [expr 0x1 << 16 ]
set AT91C_NVIC_BUSFAULTENA [expr 0x1 << 17 ]
set AT91C_NVIC_USGFAULTENA [expr 0x1 << 18 ]
# -------- NVIC_CFSR : (NVIC Offset: 0xd28) Configurable Fault Status Registers -------- 
set AT91C_NVIC_MEMMANAGE  [expr 0xFF <<  0 ]
set AT91C_NVIC_BUSFAULT   [expr 0xFF <<  8 ]
set AT91C_NVIC_USAGEFAULT [expr 0xFF << 16 ]
# -------- NVIC_BFAR : (NVIC Offset: 0xd38) Bus Fault Address Register -------- 
set AT91C_NVIC_IBUSERR    [expr 0x1 <<  0 ]
set AT91C_NVIC_PRECISERR  [expr 0x1 <<  1 ]
set AT91C_NVIC_IMPRECISERR [expr 0x1 <<  2 ]
set AT91C_NVIC_UNSTKERR   [expr 0x1 <<  3 ]
set AT91C_NVIC_STKERR     [expr 0x1 <<  4 ]
set AT91C_NVIC_BFARVALID  [expr 0x1 <<  7 ]
# -------- NVIC_PFR0 : (NVIC Offset: 0xd40) Processor Feature register0 (ID_PFR0) -------- 
set AT91C_NVIC_ID_PFR0_0  [expr 0xF <<  0 ]
set AT91C_NVIC_ID_PRF0_1  [expr 0xF <<  4 ]
# -------- NVIC_PFR1 : (NVIC Offset: 0xd44) Processor Feature register1 (ID_PFR1) -------- 
set AT91C_NVIC_ID_PRF1_MODEL [expr 0xF <<  8 ]
# -------- NVIC_DFR0 : (NVIC Offset: 0xd48) Debug Feature register0 (ID_DFR0) -------- 
set AT91C_NVIC_ID_DFR0_MODEL [expr 0xF << 20 ]
# -------- NVIC_MMFR0 : (NVIC Offset: 0xd50) Memory Model Feature register0 (ID_MMFR0) -------- 
set AT91C_NVIC_ID_MMFR0_PMSA [expr 0xF <<  4 ]
set AT91C_NVIC_ID_MMFR0_CACHE [expr 0xF <<  8 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR NESTED vector Interrupt Controller
# *****************************************************************************
# -------- MPU_TYPE : (MPU Offset: 0x0)  -------- 
set AT91C_MPU_SEPARATE    [expr 0x1 <<  0 ]
set AT91C_MPU_DREGION     [expr 0xFF <<  8 ]
set AT91C_MPU_IREGION     [expr 0xFF << 16 ]
# -------- MPU_CTRL : (MPU Offset: 0x4)  -------- 
set AT91C_MPU_ENABLE      [expr 0x1 <<  0 ]
set AT91C_MPU_HFNMIENA    [expr 0x1 <<  1 ]
set AT91C_MPU_PRIVDEFENA  [expr 0x1 <<  2 ]
# -------- MPU_REG_NB : (MPU Offset: 0x8)  -------- 
set AT91C_MPU_REGION      [expr 0xFF <<  0 ]
# -------- MPU_REG_BASE_ADDR : (MPU Offset: 0xc)  -------- 
set AT91C_MPU_REG         [expr 0xF <<  0 ]
set AT91C_MPU_VALID       [expr 0x1 <<  4 ]
set AT91C_MPU_ADDR        [expr 0x3FFFFFF <<  5 ]
# -------- MPU_ATTR_SIZE : (MPU Offset: 0x10)  -------- 
set AT91C_MPU_ENA         [expr 0x1 <<  0 ]
set AT91C_MPU_SIZE        [expr 0xF <<  1 ]
set AT91C_MPU_SRD         [expr 0xFF <<  8 ]
set AT91C_MPU_B           [expr 0x1 << 16 ]
set AT91C_MPU_C           [expr 0x1 << 17 ]
set AT91C_MPU_S           [expr 0x1 << 18 ]
set AT91C_MPU_TEX         [expr 0x7 << 19 ]
set AT91C_MPU_AP          [expr 0x7 << 24 ]
set AT91C_MPU_XN          [expr 0x7 << 28 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR CORTEX_M3 Registers
# *****************************************************************************
# -------- CM3_CPUID : (CM3 Offset: 0x0)  -------- 
# -------- CM3_AIRCR : (CM3 Offset: 0xc)  -------- 
set AT91C_CM3_SYSRESETREQ [expr 0x1 <<  2 ]
# -------- CM3_SCR : (CM3 Offset: 0x10)  -------- 
set AT91C_CM3_SLEEPONEXIT [expr 0x1 <<  1 ]
set AT91C_CM3_SLEEPDEEP   [expr 0x1 <<  2 ]
set AT91C_CM3_SEVONPEND   [expr 0x1 <<  4 ]
# -------- CM3_SHCSR : (CM3 Offset: 0x24)  -------- 
set AT91C_CM3_SYSTICKACT  [expr 0x1 << 11 ]

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
# -------- CKGR_UCKR : (PMC Offset: 0x1c) UTMI Clock Configuration Register -------- 
set AT91C_CKGR_UPLLEN     [expr 0x1 << 16 ]
set 	AT91C_CKGR_UPLLEN_DISABLED             [expr 0x0 << 16 ]
set 	AT91C_CKGR_UPLLEN_ENABLED              [expr 0x1 << 16 ]
set AT91C_CKGR_UPLLCOUNT  [expr 0xF << 20 ]
set AT91C_CKGR_BIASEN     [expr 0x1 << 24 ]
set 	AT91C_CKGR_BIASEN_DISABLED             [expr 0x0 << 24 ]
set 	AT91C_CKGR_BIASEN_ENABLED              [expr 0x1 << 24 ]
set AT91C_CKGR_BIASCOUNT  [expr 0xF << 28 ]
# -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
set AT91C_CKGR_MOSCXTEN   [expr 0x1 <<  0 ]
set AT91C_CKGR_MOSCXTBY   [expr 0x1 <<  1 ]
set AT91C_CKGR_WAITMODE   [expr 0x1 <<  2 ]
set AT91C_CKGR_MOSCRCEN   [expr 0x1 <<  3 ]
set AT91C_CKGR_MOSCRCF    [expr 0x7 <<  4 ]
set AT91C_CKGR_MOSCXTST   [expr 0xFF <<  8 ]
set AT91C_CKGR_KEY        [expr 0xFF << 16 ]
set AT91C_CKGR_MOSCSEL    [expr 0x1 << 24 ]
set AT91C_CKGR_CFDEN      [expr 0x1 << 25 ]
# -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLAR : (PMC Offset: 0x28) PLL A Register -------- 
set AT91C_CKGR_DIVA       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVA_0                    0x0
set 	AT91C_CKGR_DIVA_BYPASS               0x1
set AT91C_CKGR_PLLACOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_STMODE     [expr 0x3 << 14 ]
set 	AT91C_CKGR_STMODE_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_STMODE_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_STMODE_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_STMODE_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULA       [expr 0x7FF << 16 ]
set AT91C_CKGR_SRC        [expr 0x1 << 29 ]
# -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x7 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLLA_CLK             0x2
set 	AT91C_PMC_CSS_UPLL_CLK             0x3
set 	AT91C_PMC_CSS_SYS_CLK              0x4
set AT91C_PMC_PRES        [expr 0x7 <<  4 ]
set 	AT91C_PMC_PRES_CLK                  [expr 0x0 <<  4 ]
set 	AT91C_PMC_PRES_CLK_2                [expr 0x1 <<  4 ]
set 	AT91C_PMC_PRES_CLK_4                [expr 0x2 <<  4 ]
set 	AT91C_PMC_PRES_CLK_8                [expr 0x3 <<  4 ]
set 	AT91C_PMC_PRES_CLK_16               [expr 0x4 <<  4 ]
set 	AT91C_PMC_PRES_CLK_32               [expr 0x5 <<  4 ]
set 	AT91C_PMC_PRES_CLK_64               [expr 0x6 <<  4 ]
set 	AT91C_PMC_PRES_CLK_6                [expr 0x7 <<  4 ]
# -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x7 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLLA_CLK             0x2
set 	AT91C_PMC_CSS_UPLL_CLK             0x3
set 	AT91C_PMC_CSS_SYS_CLK              0x4
set AT91C_PMC_PRES        [expr 0x7 <<  4 ]
set 	AT91C_PMC_PRES_CLK                  [expr 0x0 <<  4 ]
set 	AT91C_PMC_PRES_CLK_2                [expr 0x1 <<  4 ]
set 	AT91C_PMC_PRES_CLK_4                [expr 0x2 <<  4 ]
set 	AT91C_PMC_PRES_CLK_8                [expr 0x3 <<  4 ]
set 	AT91C_PMC_PRES_CLK_16               [expr 0x4 <<  4 ]
set 	AT91C_PMC_PRES_CLK_32               [expr 0x5 <<  4 ]
set 	AT91C_PMC_PRES_CLK_64               [expr 0x6 <<  4 ]
set 	AT91C_PMC_PRES_CLK_6                [expr 0x7 <<  4 ]
# -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
set AT91C_PMC_MOSCXTS     [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCKRDY0     [expr 0x1 <<  8 ]
set AT91C_PMC_PCKRDY1     [expr 0x1 <<  9 ]
set AT91C_PMC_PCKRDY2     [expr 0x1 << 10 ]
set AT91C_PMC_MOSCSELS    [expr 0x1 << 16 ]
set AT91C_PMC_MOSCRCS     [expr 0x1 << 17 ]
set AT91C_PMC_CFDEV       [expr 0x1 << 18 ]
# -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
set AT91C_PMC_MOSCXTS     [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCKRDY0     [expr 0x1 <<  8 ]
set AT91C_PMC_PCKRDY1     [expr 0x1 <<  9 ]
set AT91C_PMC_PCKRDY2     [expr 0x1 << 10 ]
set AT91C_PMC_MOSCSELS    [expr 0x1 << 16 ]
set AT91C_PMC_MOSCRCS     [expr 0x1 << 17 ]
set AT91C_PMC_CFDEV       [expr 0x1 << 18 ]
# -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
set AT91C_PMC_MOSCXTS     [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_OSCSELS     [expr 0x1 <<  7 ]
set AT91C_PMC_PCKRDY0     [expr 0x1 <<  8 ]
set AT91C_PMC_PCKRDY1     [expr 0x1 <<  9 ]
set AT91C_PMC_PCKRDY2     [expr 0x1 << 10 ]
set AT91C_PMC_MOSCSELS    [expr 0x1 << 16 ]
set AT91C_PMC_MOSCRCS     [expr 0x1 << 17 ]
set AT91C_PMC_CFDEV       [expr 0x1 << 18 ]
set AT91C_PMC_CFDS        [expr 0x1 << 19 ]
set AT91C_PMC_FOS         [expr 0x1 << 20 ]
# -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 
set AT91C_PMC_MOSCXTS     [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCKRDY0     [expr 0x1 <<  8 ]
set AT91C_PMC_PCKRDY1     [expr 0x1 <<  9 ]
set AT91C_PMC_PCKRDY2     [expr 0x1 << 10 ]
set AT91C_PMC_MOSCSELS    [expr 0x1 << 16 ]
set AT91C_PMC_MOSCRCS     [expr 0x1 << 17 ]
set AT91C_PMC_CFDEV       [expr 0x1 << 18 ]
# -------- PMC_FSMR : (PMC Offset: 0x70) Fast Startup Mode Register -------- 
set AT91C_PMC_FSTT        [expr 0xFFFF <<  0 ]
set AT91C_PMC_RTTAL       [expr 0x1 << 16 ]
set AT91C_PMC_RTCAL       [expr 0x1 << 17 ]
set AT91C_PMC_USBAL       [expr 0x1 << 18 ]
set AT91C_PMC_LPM         [expr 0x1 << 20 ]
# -------- PMC_FSPR : (PMC Offset: 0x74) Fast Startup Polarity Register -------- 
set AT91C_PMC_FSTP        [expr 0xFFFF <<  0 ]
# -------- PMC_FOCR : (PMC Offset: 0x78) Fault Output Clear Register -------- 
set AT91C_PMC_FOCLR       [expr 0x1 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Clock Generator Controler
# *****************************************************************************
# -------- CKGR_UCKR : (CKGR Offset: 0x0) UTMI Clock Configuration Register -------- 
set AT91C_CKGR_UPLLEN     [expr 0x1 << 16 ]
set 	AT91C_CKGR_UPLLEN_DISABLED             [expr 0x0 << 16 ]
set 	AT91C_CKGR_UPLLEN_ENABLED              [expr 0x1 << 16 ]
set AT91C_CKGR_UPLLCOUNT  [expr 0xF << 20 ]
set AT91C_CKGR_BIASEN     [expr 0x1 << 24 ]
set 	AT91C_CKGR_BIASEN_DISABLED             [expr 0x0 << 24 ]
set 	AT91C_CKGR_BIASEN_ENABLED              [expr 0x1 << 24 ]
set AT91C_CKGR_BIASCOUNT  [expr 0xF << 28 ]
# -------- CKGR_MOR : (CKGR Offset: 0x4) Main Oscillator Register -------- 
set AT91C_CKGR_MOSCXTEN   [expr 0x1 <<  0 ]
set AT91C_CKGR_MOSCXTBY   [expr 0x1 <<  1 ]
set AT91C_CKGR_WAITMODE   [expr 0x1 <<  2 ]
set AT91C_CKGR_MOSCRCEN   [expr 0x1 <<  3 ]
set AT91C_CKGR_MOSCRCF    [expr 0x7 <<  4 ]
set AT91C_CKGR_MOSCXTST   [expr 0xFF <<  8 ]
set AT91C_CKGR_KEY        [expr 0xFF << 16 ]
set AT91C_CKGR_MOSCSEL    [expr 0x1 << 24 ]
set AT91C_CKGR_CFDEN      [expr 0x1 << 25 ]
# -------- CKGR_MCFR : (CKGR Offset: 0x8) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLAR : (CKGR Offset: 0xc) PLL A Register -------- 
set AT91C_CKGR_DIVA       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVA_0                    0x0
set 	AT91C_CKGR_DIVA_BYPASS               0x1
set AT91C_CKGR_PLLACOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_STMODE     [expr 0x3 << 14 ]
set 	AT91C_CKGR_STMODE_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_STMODE_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_STMODE_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_STMODE_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULA       [expr 0x7FF << 16 ]
set AT91C_CKGR_SRC        [expr 0x1 << 29 ]

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
set AT91C_SUPC_GPBRON     [expr 0x1 << 16 ]
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
set AT91C_SUPC_FWUPIS     [expr 0x1 << 12 ]
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
set 	AT91C_ADC_TRGSEL_EXT                  [expr 0x0 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA0                [expr 0x1 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA1                [expr 0x2 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA2                [expr 0x3 <<  1 ]
set 	AT91C_ADC_TRGSEL_PWM0_TRIG            [expr 0x4 <<  1 ]
set 	AT91C_ADC_TRGSEL_PWM1_TRIG            [expr 0x5 <<  1 ]
set 	AT91C_ADC_TRGSEL_RESERVED             [expr 0x6 <<  1 ]
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
# -------- ADC_VER : (ADC Offset: 0xfc) ADC VER -------- 
set AT91C_ADC_VER         [expr 0xF <<  0 ]

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
#              SOFTWARE API DEFINITION  FOR Embedded Flash Controller 2.0
# *****************************************************************************
# -------- EFC_FMR : (EFC Offset: 0x0) EFC Flash Mode Register -------- 
set AT91C_EFC_FRDY        [expr 0x1 <<  0 ]
set AT91C_EFC_FWS         [expr 0xF <<  8 ]
set 	AT91C_EFC_FWS_0WS                  [expr 0x0 <<  8 ]
set 	AT91C_EFC_FWS_1WS                  [expr 0x1 <<  8 ]
set 	AT91C_EFC_FWS_2WS                  [expr 0x2 <<  8 ]
set 	AT91C_EFC_FWS_3WS                  [expr 0x3 <<  8 ]
# -------- EFC_FCR : (EFC Offset: 0x4) EFC Flash Command Register -------- 
set AT91C_EFC_FCMD        [expr 0xFF <<  0 ]
set 	AT91C_EFC_FCMD_GETD                 0x0
set 	AT91C_EFC_FCMD_WP                   0x1
set 	AT91C_EFC_FCMD_WPL                  0x2
set 	AT91C_EFC_FCMD_EWP                  0x3
set 	AT91C_EFC_FCMD_EWPL                 0x4
set 	AT91C_EFC_FCMD_EA                   0x5
set 	AT91C_EFC_FCMD_EPL                  0x6
set 	AT91C_EFC_FCMD_EPA                  0x7
set 	AT91C_EFC_FCMD_SLB                  0x8
set 	AT91C_EFC_FCMD_CLB                  0x9
set 	AT91C_EFC_FCMD_GLB                  0xA
set 	AT91C_EFC_FCMD_SFB                  0xB
set 	AT91C_EFC_FCMD_CFB                  0xC
set 	AT91C_EFC_FCMD_GFB                  0xD
set AT91C_EFC_FARG        [expr 0xFFFF <<  8 ]
set AT91C_EFC_FKEY        [expr 0xFF << 24 ]
# -------- EFC_FSR : (EFC Offset: 0x8) EFC Flash Status Register -------- 
set AT91C_EFC_FRDY_S      [expr 0x1 <<  0 ]
set AT91C_EFC_FCMDE       [expr 0x1 <<  1 ]
set AT91C_EFC_LOCKE       [expr 0x1 <<  2 ]
# -------- EFC_FRR : (EFC Offset: 0xc) EFC Flash Result Register -------- 
set AT91C_EFC_FVALUE      [expr 0x0 <<  0 ]

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
set AT91C_MCI_SCDBUS      [expr 0x3 <<  6 ]
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
# -------- MCI_VER : (MCI Offset: 0xfc)  VERSION  Register -------- 
set AT91C_MCI_VER         [expr 0xF <<  0 ]

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
#              SOFTWARE API DEFINITION  FOR Usart
# *****************************************************************************
# -------- US_CR : (USART Offset: 0x0)  Control Register -------- 
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
# -------- US_MR : (USART Offset: 0x4)  Mode Register -------- 
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
# -------- US_IER : (USART Offset: 0x8)  Interrupt Enable Register -------- 
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
# -------- US_IDR : (USART Offset: 0xc)  Interrupt Disable Register -------- 
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
# -------- US_IMR : (USART Offset: 0x10)  Interrupt Mask Register -------- 
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
# -------- US_CSR : (USART Offset: 0x14)  Channel Status Register -------- 
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
set 	AT91C_PWMC_CPRE_MCK_DIV_2            0x1
set 	AT91C_PWMC_CPRE_MCK_DIV_4            0x2
set 	AT91C_PWMC_CPRE_MCK_DIV_8            0x3
set 	AT91C_PWMC_CPRE_MCK_DIV_16           0x4
set 	AT91C_PWMC_CPRE_MCK_DIV_32           0x5
set 	AT91C_PWMC_CPRE_MCK_DIV_64           0x6
set 	AT91C_PWMC_CPRE_MCK_DIV_128          0x7
set 	AT91C_PWMC_CPRE_MCK_DIV_256          0x8
set 	AT91C_PWMC_CPRE_MCK_DIV_512          0x9
set 	AT91C_PWMC_CPRE_MCK_DIV_1024         0xA
set 	AT91C_PWMC_CPRE_MCKA                 0xB
set 	AT91C_PWMC_CPRE_MCKB                 0xC
set AT91C_PWMC_CALG       [expr 0x1 <<  8 ]
set AT91C_PWMC_CPOL       [expr 0x1 <<  9 ]
set AT91C_PWMC_CES        [expr 0x1 << 10 ]
set AT91C_PWMC_DTE        [expr 0x1 << 16 ]
set AT91C_PWMC_DTHI       [expr 0x1 << 17 ]
set AT91C_PWMC_DTLI       [expr 0x1 << 18 ]
# -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- 
set AT91C_PWMC_CDTY       [expr 0xFFFFFF <<  0 ]
# -------- PWMC_CDTYUPDR : (PWMC_CH Offset: 0x8) PWMC Channel Duty Cycle Update Register -------- 
set AT91C_PWMC_CDTYUPD    [expr 0xFFFFFF <<  0 ]
# -------- PWMC_CPRDR : (PWMC_CH Offset: 0xc) PWMC Channel Period Register -------- 
set AT91C_PWMC_CPRD       [expr 0xFFFFFF <<  0 ]
# -------- PWMC_CPRDUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Period Update Register -------- 
set AT91C_PWMC_CPRDUPD    [expr 0xFFFFFF <<  0 ]
# -------- PWMC_CCNTR : (PWMC_CH Offset: 0x14) PWMC Channel Counter Register -------- 
set AT91C_PWMC_CCNT       [expr 0xFFFFFF <<  0 ]
# -------- PWMC_DTR : (PWMC_CH Offset: 0x18) Channel Dead Time Value Register -------- 
set AT91C_PWMC_DTL        [expr 0xFFFF <<  0 ]
set AT91C_PWMC_DTH        [expr 0xFFFF << 16 ]
# -------- PWMC_DTUPDR : (PWMC_CH Offset: 0x1c) Channel Dead Time Value Register -------- 
set AT91C_PWMC_DTLUPD     [expr 0xFFFF <<  0 ]
set AT91C_PWMC_DTHUPD     [expr 0xFFFF << 16 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface
# *****************************************************************************
# -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- 
set AT91C_PWMC_DIVA       [expr 0xFF <<  0 ]
set AT91C_PWMC_PREA       [expr 0xF <<  8 ]
set 	AT91C_PWMC_PREA_MCK                  [expr 0x0 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_2            [expr 0x1 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_4            [expr 0x2 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_8            [expr 0x3 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_16           [expr 0x4 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_32           [expr 0x5 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_64           [expr 0x6 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_128          [expr 0x7 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_256          [expr 0x8 <<  8 ]
set AT91C_PWMC_DIVB       [expr 0xFF << 16 ]
set AT91C_PWMC_PREB       [expr 0xF << 24 ]
set 	AT91C_PWMC_PREB_MCK                  [expr 0x0 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_2            [expr 0x1 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_4            [expr 0x2 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_8            [expr 0x3 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_16           [expr 0x4 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_32           [expr 0x5 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_64           [expr 0x6 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_128          [expr 0x7 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_256          [expr 0x8 << 24 ]
set AT91C_PWMC_CLKSEL     [expr 0x1 << 31 ]
# -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
# -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
# -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
# -------- PWMC_IER1 : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
set AT91C_PWMC_FCHID0     [expr 0x1 << 16 ]
set AT91C_PWMC_FCHID1     [expr 0x1 << 17 ]
set AT91C_PWMC_FCHID2     [expr 0x1 << 18 ]
set AT91C_PWMC_FCHID3     [expr 0x1 << 19 ]
set AT91C_PWMC_FCHID4     [expr 0x1 << 20 ]
set AT91C_PWMC_FCHID5     [expr 0x1 << 21 ]
set AT91C_PWMC_FCHID6     [expr 0x1 << 22 ]
set AT91C_PWMC_FCHID7     [expr 0x1 << 23 ]
set AT91C_PWMC_FCHID8     [expr 0x1 << 24 ]
set AT91C_PWMC_FCHID9     [expr 0x1 << 25 ]
set AT91C_PWMC_FCHID10    [expr 0x1 << 26 ]
set AT91C_PWMC_FCHID11    [expr 0x1 << 27 ]
set AT91C_PWMC_FCHID12    [expr 0x1 << 28 ]
set AT91C_PWMC_FCHID13    [expr 0x1 << 29 ]
set AT91C_PWMC_FCHID14    [expr 0x1 << 30 ]
set AT91C_PWMC_FCHID15    [expr 0x1 << 31 ]
# -------- PWMC_IDR1 : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
set AT91C_PWMC_FCHID0     [expr 0x1 << 16 ]
set AT91C_PWMC_FCHID1     [expr 0x1 << 17 ]
set AT91C_PWMC_FCHID2     [expr 0x1 << 18 ]
set AT91C_PWMC_FCHID3     [expr 0x1 << 19 ]
set AT91C_PWMC_FCHID4     [expr 0x1 << 20 ]
set AT91C_PWMC_FCHID5     [expr 0x1 << 21 ]
set AT91C_PWMC_FCHID6     [expr 0x1 << 22 ]
set AT91C_PWMC_FCHID7     [expr 0x1 << 23 ]
set AT91C_PWMC_FCHID8     [expr 0x1 << 24 ]
set AT91C_PWMC_FCHID9     [expr 0x1 << 25 ]
set AT91C_PWMC_FCHID10    [expr 0x1 << 26 ]
set AT91C_PWMC_FCHID11    [expr 0x1 << 27 ]
set AT91C_PWMC_FCHID12    [expr 0x1 << 28 ]
set AT91C_PWMC_FCHID13    [expr 0x1 << 29 ]
set AT91C_PWMC_FCHID14    [expr 0x1 << 30 ]
set AT91C_PWMC_FCHID15    [expr 0x1 << 31 ]
# -------- PWMC_IMR1 : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
set AT91C_PWMC_FCHID0     [expr 0x1 << 16 ]
set AT91C_PWMC_FCHID1     [expr 0x1 << 17 ]
set AT91C_PWMC_FCHID2     [expr 0x1 << 18 ]
set AT91C_PWMC_FCHID3     [expr 0x1 << 19 ]
set AT91C_PWMC_FCHID4     [expr 0x1 << 20 ]
set AT91C_PWMC_FCHID5     [expr 0x1 << 21 ]
set AT91C_PWMC_FCHID6     [expr 0x1 << 22 ]
set AT91C_PWMC_FCHID7     [expr 0x1 << 23 ]
set AT91C_PWMC_FCHID8     [expr 0x1 << 24 ]
set AT91C_PWMC_FCHID9     [expr 0x1 << 25 ]
set AT91C_PWMC_FCHID10    [expr 0x1 << 26 ]
set AT91C_PWMC_FCHID11    [expr 0x1 << 27 ]
set AT91C_PWMC_FCHID12    [expr 0x1 << 28 ]
set AT91C_PWMC_FCHID13    [expr 0x1 << 29 ]
set AT91C_PWMC_FCHID14    [expr 0x1 << 30 ]
set AT91C_PWMC_FCHID15    [expr 0x1 << 31 ]
# -------- PWMC_ISR1 : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
set AT91C_PWMC_FCHID0     [expr 0x1 << 16 ]
set AT91C_PWMC_FCHID1     [expr 0x1 << 17 ]
set AT91C_PWMC_FCHID2     [expr 0x1 << 18 ]
set AT91C_PWMC_FCHID3     [expr 0x1 << 19 ]
set AT91C_PWMC_FCHID4     [expr 0x1 << 20 ]
set AT91C_PWMC_FCHID5     [expr 0x1 << 21 ]
set AT91C_PWMC_FCHID6     [expr 0x1 << 22 ]
set AT91C_PWMC_FCHID7     [expr 0x1 << 23 ]
set AT91C_PWMC_FCHID8     [expr 0x1 << 24 ]
set AT91C_PWMC_FCHID9     [expr 0x1 << 25 ]
set AT91C_PWMC_FCHID10    [expr 0x1 << 26 ]
set AT91C_PWMC_FCHID11    [expr 0x1 << 27 ]
set AT91C_PWMC_FCHID12    [expr 0x1 << 28 ]
set AT91C_PWMC_FCHID13    [expr 0x1 << 29 ]
set AT91C_PWMC_FCHID14    [expr 0x1 << 30 ]
set AT91C_PWMC_FCHID15    [expr 0x1 << 31 ]
# -------- PWMC_SYNC : (PWMC Offset: 0x20) PWMC Synchronous Channels Register -------- 
set AT91C_PWMC_SYNC0      [expr 0x1 <<  0 ]
set AT91C_PWMC_SYNC1      [expr 0x1 <<  1 ]
set AT91C_PWMC_SYNC2      [expr 0x1 <<  2 ]
set AT91C_PWMC_SYNC3      [expr 0x1 <<  3 ]
set AT91C_PWMC_SYNC4      [expr 0x1 <<  4 ]
set AT91C_PWMC_SYNC5      [expr 0x1 <<  5 ]
set AT91C_PWMC_SYNC6      [expr 0x1 <<  6 ]
set AT91C_PWMC_SYNC7      [expr 0x1 <<  7 ]
set AT91C_PWMC_SYNC8      [expr 0x1 <<  8 ]
set AT91C_PWMC_SYNC9      [expr 0x1 <<  9 ]
set AT91C_PWMC_SYNC10     [expr 0x1 << 10 ]
set AT91C_PWMC_SYNC11     [expr 0x1 << 11 ]
set AT91C_PWMC_SYNC12     [expr 0x1 << 12 ]
set AT91C_PWMC_SYNC13     [expr 0x1 << 13 ]
set AT91C_PWMC_SYNC14     [expr 0x1 << 14 ]
set AT91C_PWMC_SYNC15     [expr 0x1 << 15 ]
set AT91C_PWMC_UPDM       [expr 0x3 << 16 ]
set 	AT91C_PWMC_UPDM_MODE0                [expr 0x0 << 16 ]
set 	AT91C_PWMC_UPDM_MODE1                [expr 0x1 << 16 ]
set 	AT91C_PWMC_UPDM_MODE2                [expr 0x2 << 16 ]
# -------- PWMC_UPCR : (PWMC Offset: 0x28) PWMC Update Control Register -------- 
set AT91C_PWMC_UPDULOCK   [expr 0x1 <<  0 ]
# -------- PWMC_SCUP : (PWMC Offset: 0x2c) PWM Update Period Register -------- 
set AT91C_PWMC_UPR        [expr 0xF <<  0 ]
set AT91C_PWMC_UPRCNT     [expr 0xF <<  4 ]
# -------- PWMC_SCUPUPD : (PWMC Offset: 0x30) PWM Update Period Update Register -------- 
set AT91C_PWMC_UPVUPDAL   [expr 0xF <<  0 ]
# -------- PWMC_IER2 : (PWMC Offset: 0x34) PWMC Interrupt Enable Register -------- 
set AT91C_PWMC_WRDY       [expr 0x1 <<  0 ]
set AT91C_PWMC_ENDTX      [expr 0x1 <<  1 ]
set AT91C_PWMC_TXBUFE     [expr 0x1 <<  2 ]
set AT91C_PWMC_UNRE       [expr 0x1 <<  3 ]
# -------- PWMC_IDR2 : (PWMC Offset: 0x38) PWMC Interrupt Disable Register -------- 
set AT91C_PWMC_WRDY       [expr 0x1 <<  0 ]
set AT91C_PWMC_ENDTX      [expr 0x1 <<  1 ]
set AT91C_PWMC_TXBUFE     [expr 0x1 <<  2 ]
set AT91C_PWMC_UNRE       [expr 0x1 <<  3 ]
# -------- PWMC_IMR2 : (PWMC Offset: 0x3c) PWMC Interrupt Mask Register -------- 
set AT91C_PWMC_WRDY       [expr 0x1 <<  0 ]
set AT91C_PWMC_ENDTX      [expr 0x1 <<  1 ]
set AT91C_PWMC_TXBUFE     [expr 0x1 <<  2 ]
set AT91C_PWMC_UNRE       [expr 0x1 <<  3 ]
# -------- PWMC_ISR2 : (PWMC Offset: 0x40) PWMC Interrupt Status Register -------- 
set AT91C_PWMC_WRDY       [expr 0x1 <<  0 ]
set AT91C_PWMC_ENDTX      [expr 0x1 <<  1 ]
set AT91C_PWMC_TXBUFE     [expr 0x1 <<  2 ]
set AT91C_PWMC_UNRE       [expr 0x1 <<  3 ]
set AT91C_PWMC_CMPM0      [expr 0x1 <<  8 ]
set AT91C_PWMC_CMPM1      [expr 0x1 <<  9 ]
set AT91C_PWMC_CMPM2      [expr 0x1 << 10 ]
set AT91C_PWMC_CMPM3      [expr 0x1 << 11 ]
set AT91C_PWMC_CMPM4      [expr 0x1 << 12 ]
set AT91C_PWMC_CMPM5      [expr 0x1 << 13 ]
set AT91C_PWMC_CMPM6      [expr 0x1 << 14 ]
set AT91C_PWMC_CMPM7      [expr 0x1 << 15 ]
set AT91C_PWMC_CMPU0      [expr 0x1 << 16 ]
set AT91C_PWMC_CMPU1      [expr 0x1 << 17 ]
set AT91C_PWMC_CMPU2      [expr 0x1 << 18 ]
set AT91C_PWMC_CMPU3      [expr 0x1 << 19 ]
set AT91C_PWMC_CMPU4      [expr 0x1 << 20 ]
set AT91C_PWMC_CMPU5      [expr 0x1 << 21 ]
set AT91C_PWMC_CMPU6      [expr 0x1 << 22 ]
set AT91C_PWMC_CMPU7      [expr 0x1 << 23 ]
# -------- PWMC_OOV : (PWMC Offset: 0x44) PWM Output Override Value Register -------- 
set AT91C_PWMC_OOVH0      [expr 0x1 <<  0 ]
set AT91C_PWMC_OOVH1      [expr 0x1 <<  1 ]
set AT91C_PWMC_OOVH2      [expr 0x1 <<  2 ]
set AT91C_PWMC_OOVH3      [expr 0x1 <<  3 ]
set AT91C_PWMC_OOVH4      [expr 0x1 <<  4 ]
set AT91C_PWMC_OOVH5      [expr 0x1 <<  5 ]
set AT91C_PWMC_OOVH6      [expr 0x1 <<  6 ]
set AT91C_PWMC_OOVH7      [expr 0x1 <<  7 ]
set AT91C_PWMC_OOVH8      [expr 0x1 <<  8 ]
set AT91C_PWMC_OOVH9      [expr 0x1 <<  9 ]
set AT91C_PWMC_OOVH10     [expr 0x1 << 10 ]
set AT91C_PWMC_OOVH11     [expr 0x1 << 11 ]
set AT91C_PWMC_OOVH12     [expr 0x1 << 12 ]
set AT91C_PWMC_OOVH13     [expr 0x1 << 13 ]
set AT91C_PWMC_OOVH14     [expr 0x1 << 14 ]
set AT91C_PWMC_OOVH15     [expr 0x1 << 15 ]
set AT91C_PWMC_OOVL0      [expr 0x1 << 16 ]
set AT91C_PWMC_OOVL1      [expr 0x1 << 17 ]
set AT91C_PWMC_OOVL2      [expr 0x1 << 18 ]
set AT91C_PWMC_OOVL3      [expr 0x1 << 19 ]
set AT91C_PWMC_OOVL4      [expr 0x1 << 20 ]
set AT91C_PWMC_OOVL5      [expr 0x1 << 21 ]
set AT91C_PWMC_OOVL6      [expr 0x1 << 22 ]
set AT91C_PWMC_OOVL7      [expr 0x1 << 23 ]
set AT91C_PWMC_OOVL8      [expr 0x1 << 24 ]
set AT91C_PWMC_OOVL9      [expr 0x1 << 25 ]
set AT91C_PWMC_OOVL10     [expr 0x1 << 26 ]
set AT91C_PWMC_OOVL11     [expr 0x1 << 27 ]
set AT91C_PWMC_OOVL12     [expr 0x1 << 28 ]
set AT91C_PWMC_OOVL13     [expr 0x1 << 29 ]
set AT91C_PWMC_OOVL14     [expr 0x1 << 30 ]
set AT91C_PWMC_OOVL15     [expr 0x1 << 31 ]
# -------- PWMC_OS : (PWMC Offset: 0x48) PWM Output Selection Register -------- 
set AT91C_PWMC_OSH0       [expr 0x1 <<  0 ]
set AT91C_PWMC_OSH1       [expr 0x1 <<  1 ]
set AT91C_PWMC_OSH2       [expr 0x1 <<  2 ]
set AT91C_PWMC_OSH3       [expr 0x1 <<  3 ]
set AT91C_PWMC_OSH4       [expr 0x1 <<  4 ]
set AT91C_PWMC_OSH5       [expr 0x1 <<  5 ]
set AT91C_PWMC_OSH6       [expr 0x1 <<  6 ]
set AT91C_PWMC_OSH7       [expr 0x1 <<  7 ]
set AT91C_PWMC_OSH8       [expr 0x1 <<  8 ]
set AT91C_PWMC_OSH9       [expr 0x1 <<  9 ]
set AT91C_PWMC_OSH10      [expr 0x1 << 10 ]
set AT91C_PWMC_OSH11      [expr 0x1 << 11 ]
set AT91C_PWMC_OSH12      [expr 0x1 << 12 ]
set AT91C_PWMC_OSH13      [expr 0x1 << 13 ]
set AT91C_PWMC_OSH14      [expr 0x1 << 14 ]
set AT91C_PWMC_OSH15      [expr 0x1 << 15 ]
set AT91C_PWMC_OSL0       [expr 0x1 << 16 ]
set AT91C_PWMC_OSL1       [expr 0x1 << 17 ]
set AT91C_PWMC_OSL2       [expr 0x1 << 18 ]
set AT91C_PWMC_OSL3       [expr 0x1 << 19 ]
set AT91C_PWMC_OSL4       [expr 0x1 << 20 ]
set AT91C_PWMC_OSL5       [expr 0x1 << 21 ]
set AT91C_PWMC_OSL6       [expr 0x1 << 22 ]
set AT91C_PWMC_OSL7       [expr 0x1 << 23 ]
set AT91C_PWMC_OSL8       [expr 0x1 << 24 ]
set AT91C_PWMC_OSL9       [expr 0x1 << 25 ]
set AT91C_PWMC_OSL10      [expr 0x1 << 26 ]
set AT91C_PWMC_OSL11      [expr 0x1 << 27 ]
set AT91C_PWMC_OSL12      [expr 0x1 << 28 ]
set AT91C_PWMC_OSL13      [expr 0x1 << 29 ]
set AT91C_PWMC_OSL14      [expr 0x1 << 30 ]
set AT91C_PWMC_OSL15      [expr 0x1 << 31 ]
# -------- PWMC_OSS : (PWMC Offset: 0x4c) PWM Output Selection Set Register -------- 
set AT91C_PWMC_OSSH0      [expr 0x1 <<  0 ]
set AT91C_PWMC_OSSH1      [expr 0x1 <<  1 ]
set AT91C_PWMC_OSSH2      [expr 0x1 <<  2 ]
set AT91C_PWMC_OSSH3      [expr 0x1 <<  3 ]
set AT91C_PWMC_OSSH4      [expr 0x1 <<  4 ]
set AT91C_PWMC_OSSH5      [expr 0x1 <<  5 ]
set AT91C_PWMC_OSSH6      [expr 0x1 <<  6 ]
set AT91C_PWMC_OSSH7      [expr 0x1 <<  7 ]
set AT91C_PWMC_OSSH8      [expr 0x1 <<  8 ]
set AT91C_PWMC_OSSH9      [expr 0x1 <<  9 ]
set AT91C_PWMC_OSSH10     [expr 0x1 << 10 ]
set AT91C_PWMC_OSSH11     [expr 0x1 << 11 ]
set AT91C_PWMC_OSSH12     [expr 0x1 << 12 ]
set AT91C_PWMC_OSSH13     [expr 0x1 << 13 ]
set AT91C_PWMC_OSSH14     [expr 0x1 << 14 ]
set AT91C_PWMC_OSSH15     [expr 0x1 << 15 ]
set AT91C_PWMC_OSSL0      [expr 0x1 << 16 ]
set AT91C_PWMC_OSSL1      [expr 0x1 << 17 ]
set AT91C_PWMC_OSSL2      [expr 0x1 << 18 ]
set AT91C_PWMC_OSSL3      [expr 0x1 << 19 ]
set AT91C_PWMC_OSSL4      [expr 0x1 << 20 ]
set AT91C_PWMC_OSSL5      [expr 0x1 << 21 ]
set AT91C_PWMC_OSSL6      [expr 0x1 << 22 ]
set AT91C_PWMC_OSSL7      [expr 0x1 << 23 ]
set AT91C_PWMC_OSSL8      [expr 0x1 << 24 ]
set AT91C_PWMC_OSSL9      [expr 0x1 << 25 ]
set AT91C_PWMC_OSSL10     [expr 0x1 << 26 ]
set AT91C_PWMC_OSSL11     [expr 0x1 << 27 ]
set AT91C_PWMC_OSSL12     [expr 0x1 << 28 ]
set AT91C_PWMC_OSSL13     [expr 0x1 << 29 ]
set AT91C_PWMC_OSSL14     [expr 0x1 << 30 ]
set AT91C_PWMC_OSSL15     [expr 0x1 << 31 ]
# -------- PWMC_OSC : (PWMC Offset: 0x50) PWM Output Selection Clear Register -------- 
set AT91C_PWMC_OSCH0      [expr 0x1 <<  0 ]
set AT91C_PWMC_OSCH1      [expr 0x1 <<  1 ]
set AT91C_PWMC_OSCH2      [expr 0x1 <<  2 ]
set AT91C_PWMC_OSCH3      [expr 0x1 <<  3 ]
set AT91C_PWMC_OSCH4      [expr 0x1 <<  4 ]
set AT91C_PWMC_OSCH5      [expr 0x1 <<  5 ]
set AT91C_PWMC_OSCH6      [expr 0x1 <<  6 ]
set AT91C_PWMC_OSCH7      [expr 0x1 <<  7 ]
set AT91C_PWMC_OSCH8      [expr 0x1 <<  8 ]
set AT91C_PWMC_OSCH9      [expr 0x1 <<  9 ]
set AT91C_PWMC_OSCH10     [expr 0x1 << 10 ]
set AT91C_PWMC_OSCH11     [expr 0x1 << 11 ]
set AT91C_PWMC_OSCH12     [expr 0x1 << 12 ]
set AT91C_PWMC_OSCH13     [expr 0x1 << 13 ]
set AT91C_PWMC_OSCH14     [expr 0x1 << 14 ]
set AT91C_PWMC_OSCH15     [expr 0x1 << 15 ]
set AT91C_PWMC_OSCL0      [expr 0x1 << 16 ]
set AT91C_PWMC_OSCL1      [expr 0x1 << 17 ]
set AT91C_PWMC_OSCL2      [expr 0x1 << 18 ]
set AT91C_PWMC_OSCL3      [expr 0x1 << 19 ]
set AT91C_PWMC_OSCL4      [expr 0x1 << 20 ]
set AT91C_PWMC_OSCL5      [expr 0x1 << 21 ]
set AT91C_PWMC_OSCL6      [expr 0x1 << 22 ]
set AT91C_PWMC_OSCL7      [expr 0x1 << 23 ]
set AT91C_PWMC_OSCL8      [expr 0x1 << 24 ]
set AT91C_PWMC_OSCL9      [expr 0x1 << 25 ]
set AT91C_PWMC_OSCL10     [expr 0x1 << 26 ]
set AT91C_PWMC_OSCL11     [expr 0x1 << 27 ]
set AT91C_PWMC_OSCL12     [expr 0x1 << 28 ]
set AT91C_PWMC_OSCL13     [expr 0x1 << 29 ]
set AT91C_PWMC_OSCL14     [expr 0x1 << 30 ]
set AT91C_PWMC_OSCL15     [expr 0x1 << 31 ]
# -------- PWMC_OSSUPD : (PWMC Offset: 0x54) Output Selection Set for PWMH / PWML output of the channel x -------- 
set AT91C_PWMC_OSSUPDH0   [expr 0x1 <<  0 ]
set AT91C_PWMC_OSSUPDH1   [expr 0x1 <<  1 ]
set AT91C_PWMC_OSSUPDH2   [expr 0x1 <<  2 ]
set AT91C_PWMC_OSSUPDH3   [expr 0x1 <<  3 ]
set AT91C_PWMC_OSSUPDH4   [expr 0x1 <<  4 ]
set AT91C_PWMC_OSSUPDH5   [expr 0x1 <<  5 ]
set AT91C_PWMC_OSSUPDH6   [expr 0x1 <<  6 ]
set AT91C_PWMC_OSSUPDH7   [expr 0x1 <<  7 ]
set AT91C_PWMC_OSSUPDH8   [expr 0x1 <<  8 ]
set AT91C_PWMC_OSSUPDH9   [expr 0x1 <<  9 ]
set AT91C_PWMC_OSSUPDH10  [expr 0x1 << 10 ]
set AT91C_PWMC_OSSUPDH11  [expr 0x1 << 11 ]
set AT91C_PWMC_OSSUPDH12  [expr 0x1 << 12 ]
set AT91C_PWMC_OSSUPDH13  [expr 0x1 << 13 ]
set AT91C_PWMC_OSSUPDH14  [expr 0x1 << 14 ]
set AT91C_PWMC_OSSUPDH15  [expr 0x1 << 15 ]
set AT91C_PWMC_OSSUPDL0   [expr 0x1 << 16 ]
set AT91C_PWMC_OSSUPDL1   [expr 0x1 << 17 ]
set AT91C_PWMC_OSSUPDL2   [expr 0x1 << 18 ]
set AT91C_PWMC_OSSUPDL3   [expr 0x1 << 19 ]
set AT91C_PWMC_OSSUPDL4   [expr 0x1 << 20 ]
set AT91C_PWMC_OSSUPDL5   [expr 0x1 << 21 ]
set AT91C_PWMC_OSSUPDL6   [expr 0x1 << 22 ]
set AT91C_PWMC_OSSUPDL7   [expr 0x1 << 23 ]
set AT91C_PWMC_OSSUPDL8   [expr 0x1 << 24 ]
set AT91C_PWMC_OSSUPDL9   [expr 0x1 << 25 ]
set AT91C_PWMC_OSSUPDL10  [expr 0x1 << 26 ]
set AT91C_PWMC_OSSUPDL11  [expr 0x1 << 27 ]
set AT91C_PWMC_OSSUPDL12  [expr 0x1 << 28 ]
set AT91C_PWMC_OSSUPDL13  [expr 0x1 << 29 ]
set AT91C_PWMC_OSSUPDL14  [expr 0x1 << 30 ]
set AT91C_PWMC_OSSUPDL15  [expr 0x1 << 31 ]
# -------- PWMC_OSCUPD : (PWMC Offset: 0x58) Output Selection Clear for PWMH / PWML output of the channel x -------- 
set AT91C_PWMC_OSCUPDH0   [expr 0x1 <<  0 ]
set AT91C_PWMC_OSCUPDH1   [expr 0x1 <<  1 ]
set AT91C_PWMC_OSCUPDH2   [expr 0x1 <<  2 ]
set AT91C_PWMC_OSCUPDH3   [expr 0x1 <<  3 ]
set AT91C_PWMC_OSCUPDH4   [expr 0x1 <<  4 ]
set AT91C_PWMC_OSCUPDH5   [expr 0x1 <<  5 ]
set AT91C_PWMC_OSCUPDH6   [expr 0x1 <<  6 ]
set AT91C_PWMC_OSCUPDH7   [expr 0x1 <<  7 ]
set AT91C_PWMC_OSCUPDH8   [expr 0x1 <<  8 ]
set AT91C_PWMC_OSCUPDH9   [expr 0x1 <<  9 ]
set AT91C_PWMC_OSCUPDH10  [expr 0x1 << 10 ]
set AT91C_PWMC_OSCUPDH11  [expr 0x1 << 11 ]
set AT91C_PWMC_OSCUPDH12  [expr 0x1 << 12 ]
set AT91C_PWMC_OSCUPDH13  [expr 0x1 << 13 ]
set AT91C_PWMC_OSCUPDH14  [expr 0x1 << 14 ]
set AT91C_PWMC_OSCUPDH15  [expr 0x1 << 15 ]
set AT91C_PWMC_OSCUPDL0   [expr 0x1 << 16 ]
set AT91C_PWMC_OSCUPDL1   [expr 0x1 << 17 ]
set AT91C_PWMC_OSCUPDL2   [expr 0x1 << 18 ]
set AT91C_PWMC_OSCUPDL3   [expr 0x1 << 19 ]
set AT91C_PWMC_OSCUPDL4   [expr 0x1 << 20 ]
set AT91C_PWMC_OSCUPDL5   [expr 0x1 << 21 ]
set AT91C_PWMC_OSCUPDL6   [expr 0x1 << 22 ]
set AT91C_PWMC_OSCUPDL7   [expr 0x1 << 23 ]
set AT91C_PWMC_OSCUPDL8   [expr 0x1 << 24 ]
set AT91C_PWMC_OSCUPDL9   [expr 0x1 << 25 ]
set AT91C_PWMC_OSCUPDL10  [expr 0x1 << 26 ]
set AT91C_PWMC_OSCUPDL11  [expr 0x1 << 27 ]
set AT91C_PWMC_OSCUPDL12  [expr 0x1 << 28 ]
set AT91C_PWMC_OSCUPDL13  [expr 0x1 << 29 ]
set AT91C_PWMC_OSCUPDL14  [expr 0x1 << 30 ]
set AT91C_PWMC_OSCUPDL15  [expr 0x1 << 31 ]
# -------- PWMC_FMR : (PWMC Offset: 0x5c) PWM Fault Mode Register -------- 
set AT91C_PWMC_FPOL0      [expr 0x1 <<  0 ]
set AT91C_PWMC_FPOL1      [expr 0x1 <<  1 ]
set AT91C_PWMC_FPOL2      [expr 0x1 <<  2 ]
set AT91C_PWMC_FPOL3      [expr 0x1 <<  3 ]
set AT91C_PWMC_FPOL4      [expr 0x1 <<  4 ]
set AT91C_PWMC_FPOL5      [expr 0x1 <<  5 ]
set AT91C_PWMC_FPOL6      [expr 0x1 <<  6 ]
set AT91C_PWMC_FPOL7      [expr 0x1 <<  7 ]
set AT91C_PWMC_FMOD0      [expr 0x1 <<  8 ]
set AT91C_PWMC_FMOD1      [expr 0x1 <<  9 ]
set AT91C_PWMC_FMOD2      [expr 0x1 << 10 ]
set AT91C_PWMC_FMOD3      [expr 0x1 << 11 ]
set AT91C_PWMC_FMOD4      [expr 0x1 << 12 ]
set AT91C_PWMC_FMOD5      [expr 0x1 << 13 ]
set AT91C_PWMC_FMOD6      [expr 0x1 << 14 ]
set AT91C_PWMC_FMOD7      [expr 0x1 << 15 ]
set AT91C_PWMC_FFIL00     [expr 0x1 << 16 ]
set AT91C_PWMC_FFIL01     [expr 0x1 << 17 ]
set AT91C_PWMC_FFIL02     [expr 0x1 << 18 ]
set AT91C_PWMC_FFIL03     [expr 0x1 << 19 ]
set AT91C_PWMC_FFIL04     [expr 0x1 << 20 ]
set AT91C_PWMC_FFIL05     [expr 0x1 << 21 ]
set AT91C_PWMC_FFIL06     [expr 0x1 << 22 ]
set AT91C_PWMC_FFIL07     [expr 0x1 << 23 ]
# -------- PWMC_FSR : (PWMC Offset: 0x60) Fault Input x Value -------- 
set AT91C_PWMC_FIV0       [expr 0x1 <<  0 ]
set AT91C_PWMC_FIV1       [expr 0x1 <<  1 ]
set AT91C_PWMC_FIV2       [expr 0x1 <<  2 ]
set AT91C_PWMC_FIV3       [expr 0x1 <<  3 ]
set AT91C_PWMC_FIV4       [expr 0x1 <<  4 ]
set AT91C_PWMC_FIV5       [expr 0x1 <<  5 ]
set AT91C_PWMC_FIV6       [expr 0x1 <<  6 ]
set AT91C_PWMC_FIV7       [expr 0x1 <<  7 ]
set AT91C_PWMC_FS0        [expr 0x1 <<  8 ]
set AT91C_PWMC_FS1        [expr 0x1 <<  9 ]
set AT91C_PWMC_FS2        [expr 0x1 << 10 ]
set AT91C_PWMC_FS3        [expr 0x1 << 11 ]
set AT91C_PWMC_FS4        [expr 0x1 << 12 ]
set AT91C_PWMC_FS5        [expr 0x1 << 13 ]
set AT91C_PWMC_FS6        [expr 0x1 << 14 ]
set AT91C_PWMC_FS7        [expr 0x1 << 15 ]
# -------- PWMC_FCR : (PWMC Offset: 0x64) Fault y Clear -------- 
set AT91C_PWMC_FCLR0      [expr 0x1 <<  0 ]
set AT91C_PWMC_FCLR1      [expr 0x1 <<  1 ]
set AT91C_PWMC_FCLR2      [expr 0x1 <<  2 ]
set AT91C_PWMC_FCLR3      [expr 0x1 <<  3 ]
set AT91C_PWMC_FCLR4      [expr 0x1 <<  4 ]
set AT91C_PWMC_FCLR5      [expr 0x1 <<  5 ]
set AT91C_PWMC_FCLR6      [expr 0x1 <<  6 ]
set AT91C_PWMC_FCLR7      [expr 0x1 <<  7 ]
# -------- PWMC_FPV : (PWMC Offset: 0x68) PWM Fault Protection Value -------- 
set AT91C_PWMC_FPVH0      [expr 0x1 <<  0 ]
set AT91C_PWMC_FPVH1      [expr 0x1 <<  1 ]
set AT91C_PWMC_FPVH2      [expr 0x1 <<  2 ]
set AT91C_PWMC_FPVH3      [expr 0x1 <<  3 ]
set AT91C_PWMC_FPVH4      [expr 0x1 <<  4 ]
set AT91C_PWMC_FPVH5      [expr 0x1 <<  5 ]
set AT91C_PWMC_FPVH6      [expr 0x1 <<  6 ]
set AT91C_PWMC_FPVH7      [expr 0x1 <<  7 ]
set AT91C_PWMC_FPVL0      [expr 0x1 << 16 ]
set AT91C_PWMC_FPVL1      [expr 0x1 << 17 ]
set AT91C_PWMC_FPVL2      [expr 0x1 << 18 ]
set AT91C_PWMC_FPVL3      [expr 0x1 << 19 ]
set AT91C_PWMC_FPVL4      [expr 0x1 << 20 ]
set AT91C_PWMC_FPVL5      [expr 0x1 << 21 ]
set AT91C_PWMC_FPVL6      [expr 0x1 << 22 ]
set AT91C_PWMC_FPVL7      [expr 0x1 << 23 ]
# -------- PWMC_FPER1 : (PWMC Offset: 0x6c) PWM Fault Protection Enable Register 1 -------- 
set AT91C_PWMC_FPE0       [expr 0xFF <<  0 ]
set AT91C_PWMC_FPE1       [expr 0xFF <<  8 ]
set AT91C_PWMC_FPE2       [expr 0xFF << 16 ]
set AT91C_PWMC_FPE3       [expr 0xFF << 24 ]
# -------- PWMC_FPER2 : (PWMC Offset: 0x70) PWM Fault Protection Enable Register 2 -------- 
set AT91C_PWMC_FPE4       [expr 0xFF <<  0 ]
set AT91C_PWMC_FPE5       [expr 0xFF <<  8 ]
set AT91C_PWMC_FPE6       [expr 0xFF << 16 ]
set AT91C_PWMC_FPE7       [expr 0xFF << 24 ]
# -------- PWMC_FPER3 : (PWMC Offset: 0x74) PWM Fault Protection Enable Register 3 -------- 
set AT91C_PWMC_FPE8       [expr 0xFF <<  0 ]
set AT91C_PWMC_FPE9       [expr 0xFF <<  8 ]
set AT91C_PWMC_FPE10      [expr 0xFF << 16 ]
set AT91C_PWMC_FPE11      [expr 0xFF << 24 ]
# -------- PWMC_FPER4 : (PWMC Offset: 0x78) PWM Fault Protection Enable Register 4 -------- 
set AT91C_PWMC_FPE12      [expr 0xFF <<  0 ]
set AT91C_PWMC_FPE13      [expr 0xFF <<  8 ]
set AT91C_PWMC_FPE14      [expr 0xFF << 16 ]
set AT91C_PWMC_FPE15      [expr 0xFF << 24 ]
# -------- PWMC_EL0MR : (PWMC Offset: 0x7c) PWM Event Line 0 Mode Register -------- 
set AT91C_PWMC_L0CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L0CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L0CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L0CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L0CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L0CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L0CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L0CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL1MR : (PWMC Offset: 0x80) PWM Event Line 1 Mode Register -------- 
set AT91C_PWMC_L1CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L1CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L1CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L1CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L1CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L1CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L1CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L1CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL2MR : (PWMC Offset: 0x84) PWM Event line 2 Mode Register -------- 
set AT91C_PWMC_L2CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L2CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L2CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L2CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L2CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L2CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L2CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L2CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL3MR : (PWMC Offset: 0x88) PWM Event line 3 Mode Register -------- 
set AT91C_PWMC_L3CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L3CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L3CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L3CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L3CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L3CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L3CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L3CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL4MR : (PWMC Offset: 0x8c) PWM Event line 4 Mode Register -------- 
set AT91C_PWMC_L4CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L4CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L4CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L4CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L4CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L4CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L4CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L4CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL5MR : (PWMC Offset: 0x90) PWM Event line 5 Mode Register -------- 
set AT91C_PWMC_L5CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L5CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L5CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L5CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L5CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L5CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L5CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L5CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL6MR : (PWMC Offset: 0x94) PWM Event line 6 Mode Register -------- 
set AT91C_PWMC_L6CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L6CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L6CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L6CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L6CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L6CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L6CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L6CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL7MR : (PWMC Offset: 0x98) PWM Event line 7 Mode Register -------- 
set AT91C_PWMC_L7CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L7CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L7CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L7CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L7CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L7CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L7CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L7CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_WPCR : (PWMC Offset: 0xe4) PWM Write Protection Control Register -------- 
set AT91C_PWMC_WPCMD      [expr 0x3 <<  0 ]
set AT91C_PWMC_WPRG0      [expr 0x1 <<  2 ]
set AT91C_PWMC_WPRG1      [expr 0x1 <<  3 ]
set AT91C_PWMC_WPRG2      [expr 0x1 <<  4 ]
set AT91C_PWMC_WPRG3      [expr 0x1 <<  5 ]
set AT91C_PWMC_WPRG4      [expr 0x1 <<  6 ]
set AT91C_PWMC_WPRG5      [expr 0x1 <<  7 ]
set AT91C_PWMC_WPKEY      [expr 0xFFFFFF <<  8 ]
# -------- PWMC_WPVS : (PWMC Offset: 0xe8) Write Protection Status Register -------- 
set AT91C_PWMC_WPSWS0     [expr 0x1 <<  0 ]
set AT91C_PWMC_WPSWS1     [expr 0x1 <<  1 ]
set AT91C_PWMC_WPSWS2     [expr 0x1 <<  2 ]
set AT91C_PWMC_WPSWS3     [expr 0x1 <<  3 ]
set AT91C_PWMC_WPSWS4     [expr 0x1 <<  4 ]
set AT91C_PWMC_WPSWS5     [expr 0x1 <<  5 ]
set AT91C_PWMC_WPVS       [expr 0x1 <<  7 ]
set AT91C_PWMC_WPHWS0     [expr 0x1 <<  8 ]
set AT91C_PWMC_WPHWS1     [expr 0x1 <<  9 ]
set AT91C_PWMC_WPHWS2     [expr 0x1 << 10 ]
set AT91C_PWMC_WPHWS3     [expr 0x1 << 11 ]
set AT91C_PWMC_WPHWS4     [expr 0x1 << 12 ]
set AT91C_PWMC_WPHWS5     [expr 0x1 << 13 ]
set AT91C_PWMC_WPVSRC     [expr 0xFFFF << 16 ]
# -------- PWMC_CMP0V : (PWMC Offset: 0x130) PWM Comparison Value 0 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP0VUPD : (PWMC Offset: 0x134) PWM Comparison Value 0 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP0M : (PWMC Offset: 0x138) PWM Comparison 0 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP0MUPD : (PWMC Offset: 0x13c) PWM Comparison 0 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP1V : (PWMC Offset: 0x140) PWM Comparison Value 1 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP1VUPD : (PWMC Offset: 0x144) PWM Comparison Value 1 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP1M : (PWMC Offset: 0x148) PWM Comparison 1 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP1MUPD : (PWMC Offset: 0x14c) PWM Comparison 1 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP2V : (PWMC Offset: 0x150) PWM Comparison Value 2 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP2VUPD : (PWMC Offset: 0x154) PWM Comparison Value 2 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP2M : (PWMC Offset: 0x158) PWM Comparison 2 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP2MUPD : (PWMC Offset: 0x15c) PWM Comparison 2 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP3V : (PWMC Offset: 0x160) PWM Comparison Value 3 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP3VUPD : (PWMC Offset: 0x164) PWM Comparison Value 3 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP3M : (PWMC Offset: 0x168) PWM Comparison 3 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP3MUPD : (PWMC Offset: 0x16c) PWM Comparison 3 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP4V : (PWMC Offset: 0x170) PWM Comparison Value 4 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP4VUPD : (PWMC Offset: 0x174) PWM Comparison Value 4 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP4M : (PWMC Offset: 0x178) PWM Comparison 4 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP4MUPD : (PWMC Offset: 0x17c) PWM Comparison 4 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP5V : (PWMC Offset: 0x180) PWM Comparison Value 5 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP5VUPD : (PWMC Offset: 0x184) PWM Comparison Value 5 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP5M : (PWMC Offset: 0x188) PWM Comparison 5 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP5MUPD : (PWMC Offset: 0x18c) PWM Comparison 5 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP6V : (PWMC Offset: 0x190) PWM Comparison Value 6 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP6VUPD : (PWMC Offset: 0x194) PWM Comparison Value 6 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP6M : (PWMC Offset: 0x198) PWM Comparison 6 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP6MUPD : (PWMC Offset: 0x19c) PWM Comparison 6 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP7V : (PWMC Offset: 0x1a0) PWM Comparison Value 7 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP7VUPD : (PWMC Offset: 0x1a4) PWM Comparison Value 7 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP7M : (PWMC Offset: 0x1a8) PWM Comparison 7 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP7MUPD : (PWMC Offset: 0x1ac) PWM Comparison 7 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]

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
set AT91C_SPI_CSAAT       [expr 0x1 <<  2 ]
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
# -------- HDMA_VER : (HDMA Offset: 0x1fc)  -------- 

# *****************************************************************************
#               REGISTER ADDRESS DEFINITION FOR AT91SAM3UE256
# *****************************************************************************
# ========== Register definition for SYS peripheral ========== 
set AT91C_SYS_GPBR  0x400E1290
# ========== Register definition for HSMC4_CS0 peripheral ========== 
set AT91C_CS0_MODE  0x400E0080
set AT91C_CS0_PULSE 0x400E0074
set AT91C_CS0_CYCLE 0x400E0078
set AT91C_CS0_TIMINGS 0x400E007C
set AT91C_CS0_SETUP 0x400E0070
# ========== Register definition for HSMC4_CS1 peripheral ========== 
set AT91C_CS1_CYCLE 0x400E008C
set AT91C_CS1_PULSE 0x400E0088
set AT91C_CS1_MODE  0x400E0094
set AT91C_CS1_SETUP 0x400E0084
set AT91C_CS1_TIMINGS 0x400E0090
# ========== Register definition for HSMC4_CS2 peripheral ========== 
set AT91C_CS2_PULSE 0x400E009C
set AT91C_CS2_TIMINGS 0x400E00A4
set AT91C_CS2_CYCLE 0x400E00A0
set AT91C_CS2_MODE  0x400E00A8
set AT91C_CS2_SETUP 0x400E0098
# ========== Register definition for HSMC4_CS3 peripheral ========== 
set AT91C_CS3_MODE  0x400E00BC
set AT91C_CS3_TIMINGS 0x400E00B8
set AT91C_CS3_SETUP 0x400E00AC
set AT91C_CS3_CYCLE 0x400E00B4
set AT91C_CS3_PULSE 0x400E00B0
# ========== Register definition for HSMC4_NFC peripheral ========== 
set AT91C_NFC_MODE  0x400E010C
set AT91C_NFC_CYCLE 0x400E0104
set AT91C_NFC_PULSE 0x400E0100
set AT91C_NFC_SETUP 0x400E00FC
set AT91C_NFC_TIMINGS 0x400E0108
# ========== Register definition for HSMC4 peripheral ========== 
set AT91C_HSMC4_IPNAME1 0x400E01F0
set AT91C_HSMC4_ECCPR6 0x400E0048
set AT91C_HSMC4_ADDRSIZE 0x400E01EC
set AT91C_HSMC4_ECCPR11 0x400E005C
set AT91C_HSMC4_SR  0x400E0008
set AT91C_HSMC4_IMR 0x400E0014
set AT91C_HSMC4_WPSR 0x400E01E8
set AT91C_HSMC4_BANK 0x400E001C
set AT91C_HSMC4_ECCPR8 0x400E0050
set AT91C_HSMC4_WPCR 0x400E01E4
set AT91C_HSMC4_ECCPR2 0x400E0038
set AT91C_HSMC4_ECCPR1 0x400E0030
set AT91C_HSMC4_ECCSR2 0x400E0034
set AT91C_HSMC4_OCMS 0x400E0110
set AT91C_HSMC4_ECCPR9 0x400E0054
set AT91C_HSMC4_DUMMY 0x400E0200
set AT91C_HSMC4_ECCPR5 0x400E0044
set AT91C_HSMC4_ECCCR 0x400E0020
set AT91C_HSMC4_KEY2 0x400E0118
set AT91C_HSMC4_IER 0x400E000C
set AT91C_HSMC4_ECCSR1 0x400E0028
set AT91C_HSMC4_IDR 0x400E0010
set AT91C_HSMC4_ECCPR0 0x400E002C
set AT91C_HSMC4_FEATURES 0x400E01F8
set AT91C_HSMC4_ECCPR7 0x400E004C
set AT91C_HSMC4_ECCPR12 0x400E0060
set AT91C_HSMC4_ECCPR10 0x400E0058
set AT91C_HSMC4_KEY1 0x400E0114
set AT91C_HSMC4_VER 0x400E01FC
set AT91C_HSMC4_Eccpr15 0x400E006C
set AT91C_HSMC4_ECCPR4 0x400E0040
set AT91C_HSMC4_IPNAME2 0x400E01F4
set AT91C_HSMC4_ECCCMD 0x400E0024
set AT91C_HSMC4_ADDR 0x400E0018
set AT91C_HSMC4_ECCPR3 0x400E003C
set AT91C_HSMC4_CFG 0x400E0000
set AT91C_HSMC4_CTRL 0x400E0004
set AT91C_HSMC4_ECCPR13 0x400E0064
set AT91C_HSMC4_ECCPR14 0x400E0068
# ========== Register definition for MATRIX peripheral ========== 
set AT91C_MATRIX_SCFG6 0x400E0258
set AT91C_MATRIX_SCFG8 0x400E0260
set AT91C_MATRIX_MCFG2 0x400E0208
set AT91C_MATRIX_MCFG7 0x400E021C
set AT91C_MATRIX_SCFG3 0x400E024C
set AT91C_MATRIX_SCFG0 0x400E0240
set AT91C_MATRIX_IPNAME2 0x400E03F4
set AT91C_MATRIX_ADDRSIZE 0x400E03EC
set AT91C_MATRIX_MCFG5 0x400E0214
set AT91C_MATRIX_MCFG3 0x400E020C
set AT91C_MATRIX_SCFG4 0x400E0250
set AT91C_MATRIX_MCFG1 0x400E0204
set AT91C_MATRIX_SCFG1 0x400E0244
set AT91C_MATRIX_SCFG7 0x400E025C
set AT91C_MATRIX_VER 0x400E03FC
set AT91C_MATRIX_SCFG2 0x400E0248
set AT91C_MATRIX_IPNAME1 0x400E03F0
set AT91C_MATRIX_MCFG4 0x400E0210
set AT91C_MATRIX_FEATURES 0x400E03F8
set AT91C_MATRIX_MCFG6 0x400E0218
set AT91C_MATRIX_SCFG5 0x400E0254
set AT91C_MATRIX_MCFG0 0x400E0200
# ========== Register definition for NVIC peripheral ========== 
set AT91C_NVIC_MMAR 0xE000ED34
set AT91C_NVIC_STIR 0xE000EF00
set AT91C_NVIC_MMFR2 0xE000ED58
set AT91C_NVIC_CPUID 0xE000ED00
set AT91C_NVIC_DFSR 0xE000ED30
set AT91C_NVIC_HAND4PR 0xE000ED18
set AT91C_NVIC_HFSR 0xE000ED2C
set AT91C_NVIC_PID6 0xE000EFD8
set AT91C_NVIC_PFR0 0xE000ED40
set AT91C_NVIC_VTOFFR 0xE000ED08
set AT91C_NVIC_ISPR 0xE000E200
set AT91C_NVIC_PID0 0xE000EFE0
set AT91C_NVIC_PID7 0xE000EFDC
set AT91C_NVIC_STICKRVR 0xE000E014
set AT91C_NVIC_PID2 0xE000EFE8
set AT91C_NVIC_ISAR0 0xE000ED60
set AT91C_NVIC_SCR  0xE000ED10
set AT91C_NVIC_PID4 0xE000EFD0
set AT91C_NVIC_ISAR2 0xE000ED68
set AT91C_NVIC_ISER 0xE000E100
set AT91C_NVIC_IPR  0xE000E400
set AT91C_NVIC_AIRCR 0xE000ED0C
set AT91C_NVIC_CID2 0xE000EFF8
set AT91C_NVIC_ICPR 0xE000E280
set AT91C_NVIC_CID3 0xE000EFFC
set AT91C_NVIC_CFSR 0xE000ED28
set AT91C_NVIC_AFR0 0xE000ED4C
set AT91C_NVIC_ICSR 0xE000ED04
set AT91C_NVIC_CCR  0xE000ED14
set AT91C_NVIC_CID0 0xE000EFF0
set AT91C_NVIC_ISAR1 0xE000ED64
set AT91C_NVIC_STICKCVR 0xE000E018
set AT91C_NVIC_STICKCSR 0xE000E010
set AT91C_NVIC_CID1 0xE000EFF4
set AT91C_NVIC_DFR0 0xE000ED48
set AT91C_NVIC_MMFR3 0xE000ED5C
set AT91C_NVIC_MMFR0 0xE000ED50
set AT91C_NVIC_STICKCALVR 0xE000E01C
set AT91C_NVIC_PID1 0xE000EFE4
set AT91C_NVIC_HAND12PR 0xE000ED20
set AT91C_NVIC_MMFR1 0xE000ED54
set AT91C_NVIC_AFSR 0xE000ED3C
set AT91C_NVIC_HANDCSR 0xE000ED24
set AT91C_NVIC_ISAR4 0xE000ED70
set AT91C_NVIC_ABR  0xE000E300
set AT91C_NVIC_PFR1 0xE000ED44
set AT91C_NVIC_PID5 0xE000EFD4
set AT91C_NVIC_ICTR 0xE000E004
set AT91C_NVIC_ICER 0xE000E180
set AT91C_NVIC_PID3 0xE000EFEC
set AT91C_NVIC_ISAR3 0xE000ED6C
set AT91C_NVIC_HAND8PR 0xE000ED1C
set AT91C_NVIC_BFAR 0xE000ED38
# ========== Register definition for MPU peripheral ========== 
set AT91C_MPU_REG_BASE_ADDR3 0xE000EDB4
set AT91C_MPU_REG_NB 0xE000ED98
set AT91C_MPU_ATTR_SIZE1 0xE000EDA8
set AT91C_MPU_REG_BASE_ADDR1 0xE000EDA4
set AT91C_MPU_ATTR_SIZE3 0xE000EDB8
set AT91C_MPU_CTRL  0xE000ED94
set AT91C_MPU_ATTR_SIZE2 0xE000EDB0
set AT91C_MPU_REG_BASE_ADDR 0xE000ED9C
set AT91C_MPU_REG_BASE_ADDR2 0xE000EDAC
set AT91C_MPU_ATTR_SIZE 0xE000EDA0
set AT91C_MPU_TYPE  0xE000ED90
# ========== Register definition for CM3 peripheral ========== 
set AT91C_CM3_SHCSR 0xE000ED24
set AT91C_CM3_CCR   0xE000ED14
set AT91C_CM3_ICSR  0xE000ED04
set AT91C_CM3_CPUID 0xE000ED00
set AT91C_CM3_SCR   0xE000ED10
set AT91C_CM3_AIRCR 0xE000ED0C
set AT91C_CM3_SHPR  0xE000ED18
set AT91C_CM3_VTOR  0xE000ED08
# ========== Register definition for PDC_DBGU peripheral ========== 
set AT91C_DBGU_TPR  0x400E0708
set AT91C_DBGU_PTCR 0x400E0720
set AT91C_DBGU_TNCR 0x400E071C
set AT91C_DBGU_PTSR 0x400E0724
set AT91C_DBGU_RNCR 0x400E0714
set AT91C_DBGU_RPR  0x400E0700
set AT91C_DBGU_TCR  0x400E070C
set AT91C_DBGU_RNPR 0x400E0710
set AT91C_DBGU_TNPR 0x400E0718
set AT91C_DBGU_RCR  0x400E0704
# ========== Register definition for DBGU peripheral ========== 
set AT91C_DBGU_CR   0x400E0600
set AT91C_DBGU_IDR  0x400E060C
set AT91C_DBGU_CIDR 0x400E0740
set AT91C_DBGU_IPNAME2 0x400E06F4
set AT91C_DBGU_FEATURES 0x400E06F8
set AT91C_DBGU_FNTR 0x400E0648
set AT91C_DBGU_RHR  0x400E0618
set AT91C_DBGU_THR  0x400E061C
set AT91C_DBGU_ADDRSIZE 0x400E06EC
set AT91C_DBGU_MR   0x400E0604
set AT91C_DBGU_IER  0x400E0608
set AT91C_DBGU_BRGR 0x400E0620
set AT91C_DBGU_CSR  0x400E0614
set AT91C_DBGU_VER  0x400E06FC
set AT91C_DBGU_IMR  0x400E0610
set AT91C_DBGU_IPNAME1 0x400E06F0
set AT91C_DBGU_EXID 0x400E0744
# ========== Register definition for PIOA peripheral ========== 
set AT91C_PIOA_PDR  0x400E0C04
set AT91C_PIOA_ABSR 0x400E0C78
set AT91C_PIOA_IFSR 0x400E0C28
set AT91C_PIOA_ODR  0x400E0C14
set AT91C_PIOA_PER  0x400E0C00
set AT91C_PIOA_FEATURES 0x400E0CF8
set AT91C_PIOA_VER  0x400E0CFC
set AT91C_PIOA_OWSR 0x400E0CA8
set AT91C_PIOA_IMR  0x400E0C48
set AT91C_PIOA_OWDR 0x400E0CA4
set AT91C_PIOA_MDSR 0x400E0C58
set AT91C_PIOA_IFDR 0x400E0C24
set AT91C_PIOA_CODR 0x400E0C34
set AT91C_PIOA_ISR  0x400E0C4C
set AT91C_PIOA_PPUDR 0x400E0C60
set AT91C_PIOA_IPNAME2 0x400E0CF4
set AT91C_PIOA_MDDR 0x400E0C54
set AT91C_PIOA_PSR  0x400E0C08
set AT91C_PIOA_PDSR 0x400E0C3C
set AT91C_PIOA_PPUSR 0x400E0C68
set AT91C_PIOA_OER  0x400E0C10
set AT91C_PIOA_OSR  0x400E0C18
set AT91C_PIOA_IER  0x400E0C40
set AT91C_PIOA_PPUER 0x400E0C64
set AT91C_PIOA_ABMR 0x400E0C70
set AT91C_PIOA_ADDRSIZE 0x400E0CEC
set AT91C_PIOA_MDER 0x400E0C50
set AT91C_PIOA_IFER 0x400E0C20
set AT91C_PIOA_IPNAME1 0x400E0CF0
set AT91C_PIOA_IDR  0x400E0C44
set AT91C_PIOA_OWER 0x400E0CA0
set AT91C_PIOA_ODSR 0x400E0C38
set AT91C_PIOA_SODR 0x400E0C30
# ========== Register definition for PIOB peripheral ========== 
set AT91C_PIOB_OWSR 0x400E0EA8
set AT91C_PIOB_PSR  0x400E0E08
set AT91C_PIOB_MDER 0x400E0E50
set AT91C_PIOB_IPNAME1 0x400E0EF0
set AT91C_PIOB_FEATURES 0x400E0EF8
set AT91C_PIOB_ODR  0x400E0E14
set AT91C_PIOB_IDR  0x400E0E44
set AT91C_PIOB_PDR  0x400E0E04
set AT91C_PIOB_PDSR 0x400E0E3C
set AT91C_PIOB_PPUDR 0x400E0E60
set AT91C_PIOB_OWDR 0x400E0EA4
set AT91C_PIOB_ADDRSIZE 0x400E0EEC
set AT91C_PIOB_IFER 0x400E0E20
set AT91C_PIOB_ABMR 0x400E0E70
set AT91C_PIOB_VER  0x400E0EFC
set AT91C_PIOB_PER  0x400E0E00
set AT91C_PIOB_IMR  0x400E0E48
set AT91C_PIOB_PPUSR 0x400E0E68
set AT91C_PIOB_ODSR 0x400E0E38
set AT91C_PIOB_IFDR 0x400E0E24
set AT91C_PIOB_SODR 0x400E0E30
set AT91C_PIOB_IER  0x400E0E40
set AT91C_PIOB_MDSR 0x400E0E58
set AT91C_PIOB_ISR  0x400E0E4C
set AT91C_PIOB_IFSR 0x400E0E28
set AT91C_PIOB_PPUER 0x400E0E64
set AT91C_PIOB_OWER 0x400E0EA0
set AT91C_PIOB_IPNAME2 0x400E0EF4
set AT91C_PIOB_MDDR 0x400E0E54
set AT91C_PIOB_CODR 0x400E0E34
set AT91C_PIOB_OER  0x400E0E10
set AT91C_PIOB_OSR  0x400E0E18
set AT91C_PIOB_ABSR 0x400E0E78
# ========== Register definition for PIOC peripheral ========== 
set AT91C_PIOC_MDDR 0x400E1054
set AT91C_PIOC_ABSR 0x400E1078
set AT91C_PIOC_ABMR 0x400E1070
set AT91C_PIOC_ODSR 0x400E1038
set AT91C_PIOC_OSR  0x400E1018
set AT91C_PIOC_IFER 0x400E1020
set AT91C_PIOC_MDSR 0x400E1058
set AT91C_PIOC_IFDR 0x400E1024
set AT91C_PIOC_MDER 0x400E1050
set AT91C_PIOC_IER  0x400E1040
set AT91C_PIOC_OWDR 0x400E10A4
set AT91C_PIOC_IFSR 0x400E1028
set AT91C_PIOC_ISR  0x400E104C
set AT91C_PIOC_PPUDR 0x400E1060
set AT91C_PIOC_PDSR 0x400E103C
set AT91C_PIOC_IPNAME2 0x400E10F4
set AT91C_PIOC_PPUER 0x400E1064
set AT91C_PIOC_OER  0x400E1010
set AT91C_PIOC_CODR 0x400E1034
set AT91C_PIOC_OWER 0x400E10A0
set AT91C_PIOC_VER  0x400E10FC
set AT91C_PIOC_IMR  0x400E1048
set AT91C_PIOC_PPUSR 0x400E1068
set AT91C_PIOC_ADDRSIZE 0x400E10EC
set AT91C_PIOC_IPNAME1 0x400E10F0
set AT91C_PIOC_IDR  0x400E1044
set AT91C_PIOC_SODR 0x400E1030
set AT91C_PIOC_PSR  0x400E1008
set AT91C_PIOC_ODR  0x400E1014
set AT91C_PIOC_OWSR 0x400E10A8
set AT91C_PIOC_FEATURES 0x400E10F8
set AT91C_PIOC_PDR  0x400E1004
set AT91C_PIOC_PER  0x400E1000
# ========== Register definition for PMC peripheral ========== 
set AT91C_PMC_PLLAR 0x400E0428
set AT91C_PMC_UCKR  0x400E041C
set AT91C_PMC_FSMR  0x400E0470
set AT91C_PMC_MCKR  0x400E0430
set AT91C_PMC_SCER  0x400E0400
set AT91C_PMC_PCSR  0x400E0418
set AT91C_PMC_MCFR  0x400E0424
set AT91C_PMC_FOCR  0x400E0478
set AT91C_PMC_FSPR  0x400E0474
set AT91C_PMC_SCSR  0x400E0408
set AT91C_PMC_IDR   0x400E0464
set AT91C_PMC_VER   0x400E04FC
set AT91C_PMC_IMR   0x400E046C
set AT91C_PMC_IPNAME2 0x400E04F4
set AT91C_PMC_SCDR  0x400E0404
set AT91C_PMC_PCKR  0x400E0440
set AT91C_PMC_ADDRSIZE 0x400E04EC
set AT91C_PMC_PCDR  0x400E0414
set AT91C_PMC_MOR   0x400E0420
set AT91C_PMC_SR    0x400E0468
set AT91C_PMC_IER   0x400E0460
set AT91C_PMC_IPNAME1 0x400E04F0
set AT91C_PMC_PCER  0x400E0410
set AT91C_PMC_FEATURES 0x400E04F8
# ========== Register definition for CKGR peripheral ========== 
set AT91C_CKGR_PLLAR 0x400E0428
set AT91C_CKGR_UCKR 0x400E041C
set AT91C_CKGR_MOR  0x400E0420
set AT91C_CKGR_MCFR 0x400E0424
# ========== Register definition for RSTC peripheral ========== 
set AT91C_RSTC_VER  0x400E12FC
set AT91C_RSTC_RCR  0x400E1200
set AT91C_RSTC_RMR  0x400E1208
set AT91C_RSTC_RSR  0x400E1204
# ========== Register definition for SUPC peripheral ========== 
set AT91C_SUPC_WUIR 0x400E1220
set AT91C_SUPC_CR   0x400E1210
set AT91C_SUPC_MR   0x400E1218
set AT91C_SUPC_FWUTR 0x400E1228
set AT91C_SUPC_SR   0x400E1224
set AT91C_SUPC_WUMR 0x400E121C
set AT91C_SUPC_BOMR 0x400E1214
# ========== Register definition for RTTC peripheral ========== 
set AT91C_RTTC_RTVR 0x400E1238
set AT91C_RTTC_RTAR 0x400E1234
set AT91C_RTTC_RTMR 0x400E1230
set AT91C_RTTC_RTSR 0x400E123C
# ========== Register definition for WDTC peripheral ========== 
set AT91C_WDTC_WDSR 0x400E1258
set AT91C_WDTC_WDMR 0x400E1254
set AT91C_WDTC_WDCR 0x400E1250
# ========== Register definition for RTC peripheral ========== 
set AT91C_RTC_IMR   0x400E1288
set AT91C_RTC_SCCR  0x400E127C
set AT91C_RTC_CALR  0x400E126C
set AT91C_RTC_MR    0x400E1264
set AT91C_RTC_TIMR  0x400E1268
set AT91C_RTC_CALALR 0x400E1274
set AT91C_RTC_VER   0x400E128C
set AT91C_RTC_CR    0x400E1260
set AT91C_RTC_IDR   0x400E1284
set AT91C_RTC_TIMALR 0x400E1270
set AT91C_RTC_IER   0x400E1280
set AT91C_RTC_SR    0x400E1278
# ========== Register definition for ADC0 peripheral ========== 
set AT91C_ADC0_CDR4 0x400A8040
set AT91C_ADC0_CDR2 0x400A8038
set AT91C_ADC0_CHER 0x400A8010
set AT91C_ADC0_SR   0x400A801C
set AT91C_ADC0_IPNAME1 0x400A80F0
set AT91C_ADC0_IER  0x400A8024
set AT91C_ADC0_CR   0x400A8000
set AT91C_ADC0_CDR6 0x400A8048
set AT91C_ADC0_CHDR 0x400A8014
set AT91C_ADC0_CDR3 0x400A803C
set AT91C_ADC0_IDR  0x400A8028
set AT91C_ADC0_VER  0x400A80FC
set AT91C_ADC0_CDR7 0x400A804C
set AT91C_ADC0_CHSR 0x400A8018
set AT91C_ADC0_CDR5 0x400A8044
set AT91C_ADC0_IPNAME2 0x400A80F4
set AT91C_ADC0_MR   0x400A8004
set AT91C_ADC0_FEATURES 0x400A80F8
set AT91C_ADC0_CDR0 0x400A8030
set AT91C_ADC0_LCDR 0x400A8020
set AT91C_ADC0_IMR  0x400A802C
set AT91C_ADC0_ADDRSIZE 0x400A80EC
set AT91C_ADC0_CDR1 0x400A8034
# ========== Register definition for ADC1 peripheral ========== 
set AT91C_ADC1_IPNAME2 0x400AC0F4
set AT91C_ADC1_ADDRSIZE 0x400AC0EC
set AT91C_ADC1_IDR  0x400AC028
set AT91C_ADC1_CHSR 0x400AC018
set AT91C_ADC1_FEATURES 0x400AC0F8
set AT91C_ADC1_CDR0 0x400AC030
set AT91C_ADC1_LCDR 0x400AC020
set AT91C_ADC1_CDR3 0x400AC03C
set AT91C_ADC1_CDR7 0x400AC04C
set AT91C_ADC1_SR   0x400AC01C
set AT91C_ADC1_CDR5 0x400AC044
set AT91C_ADC1_IPNAME1 0x400AC0F0
set AT91C_ADC1_CDR6 0x400AC048
set AT91C_ADC1_MR   0x400AC004
set AT91C_ADC1_CDR1 0x400AC034
set AT91C_ADC1_CDR2 0x400AC038
set AT91C_ADC1_CDR4 0x400AC040
set AT91C_ADC1_CHER 0x400AC010
set AT91C_ADC1_VER  0x400AC0FC
set AT91C_ADC1_CHDR 0x400AC014
set AT91C_ADC1_CR   0x400AC000
set AT91C_ADC1_IMR  0x400AC02C
set AT91C_ADC1_IER  0x400AC024
# ========== Register definition for TC0 peripheral ========== 
set AT91C_TC0_IER   0x40080024
set AT91C_TC0_CV    0x40080010
set AT91C_TC0_RA    0x40080014
set AT91C_TC0_RB    0x40080018
set AT91C_TC0_IDR   0x40080028
set AT91C_TC0_SR    0x40080020
set AT91C_TC0_IMR   0x4008002C
set AT91C_TC0_CMR   0x40080004
set AT91C_TC0_RC    0x4008001C
set AT91C_TC0_CCR   0x40080000
# ========== Register definition for TC1 peripheral ========== 
set AT91C_TC1_SR    0x40080060
set AT91C_TC1_RA    0x40080054
set AT91C_TC1_IER   0x40080064
set AT91C_TC1_RB    0x40080058
set AT91C_TC1_IDR   0x40080068
set AT91C_TC1_CCR   0x40080040
set AT91C_TC1_IMR   0x4008006C
set AT91C_TC1_RC    0x4008005C
set AT91C_TC1_CMR   0x40080044
set AT91C_TC1_CV    0x40080050
# ========== Register definition for TC2 peripheral ========== 
set AT91C_TC2_RA    0x40080094
set AT91C_TC2_RB    0x40080098
set AT91C_TC2_CMR   0x40080084
set AT91C_TC2_SR    0x400800A0
set AT91C_TC2_CCR   0x40080080
set AT91C_TC2_IMR   0x400800AC
set AT91C_TC2_CV    0x40080090
set AT91C_TC2_RC    0x4008009C
set AT91C_TC2_IER   0x400800A4
set AT91C_TC2_IDR   0x400800A8
# ========== Register definition for TCB0 peripheral ========== 
set AT91C_TCB0_BCR  0x400800C0
set AT91C_TCB0_IPNAME2 0x400800F4
set AT91C_TCB0_IPNAME1 0x400800F0
set AT91C_TCB0_ADDRSIZE 0x400800EC
set AT91C_TCB0_FEATURES 0x400800F8
set AT91C_TCB0_BMR  0x400800C4
set AT91C_TCB0_VER  0x400800FC
# ========== Register definition for TCB1 peripheral ========== 
set AT91C_TCB1_BCR  0x40080100
set AT91C_TCB1_VER  0x4008013C
set AT91C_TCB1_FEATURES 0x40080138
set AT91C_TCB1_IPNAME2 0x40080134
set AT91C_TCB1_BMR  0x40080104
set AT91C_TCB1_ADDRSIZE 0x4008012C
set AT91C_TCB1_IPNAME1 0x40080130
# ========== Register definition for TCB2 peripheral ========== 
set AT91C_TCB2_FEATURES 0x40080178
set AT91C_TCB2_VER  0x4008017C
set AT91C_TCB2_ADDRSIZE 0x4008016C
set AT91C_TCB2_IPNAME1 0x40080170
set AT91C_TCB2_IPNAME2 0x40080174
set AT91C_TCB2_BMR  0x40080144
set AT91C_TCB2_BCR  0x40080140
# ========== Register definition for EFC0 peripheral ========== 
set AT91C_EFC0_FCR  0x400E0804
set AT91C_EFC0_FRR  0x400E080C
set AT91C_EFC0_FMR  0x400E0800
set AT91C_EFC0_FSR  0x400E0808
set AT91C_EFC0_FVR  0x400E0814
# ========== Register definition for EFC1 peripheral ========== 
set AT91C_EFC1_FMR  0x400E0A00
set AT91C_EFC1_FVR  0x400E0A14
set AT91C_EFC1_FSR  0x400E0A08
set AT91C_EFC1_FCR  0x400E0A04
set AT91C_EFC1_FRR  0x400E0A0C
# ========== Register definition for MCI0 peripheral ========== 
set AT91C_MCI0_DMA  0x40000050
set AT91C_MCI0_SDCR 0x4000000C
set AT91C_MCI0_IPNAME1 0x400000F0
set AT91C_MCI0_CSTOR 0x4000001C
set AT91C_MCI0_RDR  0x40000030
set AT91C_MCI0_CMDR 0x40000014
set AT91C_MCI0_IDR  0x40000048
set AT91C_MCI0_ADDRSIZE 0x400000EC
set AT91C_MCI0_WPCR 0x400000E4
set AT91C_MCI0_RSPR 0x40000020
set AT91C_MCI0_IPNAME2 0x400000F4
set AT91C_MCI0_CR   0x40000000
set AT91C_MCI0_IMR  0x4000004C
set AT91C_MCI0_WPSR 0x400000E8
set AT91C_MCI0_DTOR 0x40000008
set AT91C_MCI0_MR   0x40000004
set AT91C_MCI0_SR   0x40000040
set AT91C_MCI0_IER  0x40000044
set AT91C_MCI0_VER  0x400000FC
set AT91C_MCI0_FEATURES 0x400000F8
set AT91C_MCI0_BLKR 0x40000018
set AT91C_MCI0_ARGR 0x40000010
set AT91C_MCI0_FIFO 0x40000200
set AT91C_MCI0_TDR  0x40000034
set AT91C_MCI0_CFG  0x40000054
# ========== Register definition for PDC_TWI0 peripheral ========== 
set AT91C_TWI0_TNCR 0x4008411C
set AT91C_TWI0_PTCR 0x40084120
set AT91C_TWI0_PTSR 0x40084124
set AT91C_TWI0_RCR  0x40084104
set AT91C_TWI0_TNPR 0x40084118
set AT91C_TWI0_RNPR 0x40084110
set AT91C_TWI0_RPR  0x40084100
set AT91C_TWI0_RNCR 0x40084114
set AT91C_TWI0_TPR  0x40084108
set AT91C_TWI0_TCR  0x4008410C
# ========== Register definition for PDC_TWI1 peripheral ========== 
set AT91C_TWI1_TNCR 0x4008811C
set AT91C_TWI1_PTCR 0x40088120
set AT91C_TWI1_RNCR 0x40088114
set AT91C_TWI1_RCR  0x40088104
set AT91C_TWI1_RPR  0x40088100
set AT91C_TWI1_TNPR 0x40088118
set AT91C_TWI1_RNPR 0x40088110
set AT91C_TWI1_TCR  0x4008810C
set AT91C_TWI1_TPR  0x40088108
set AT91C_TWI1_PTSR 0x40088124
# ========== Register definition for TWI0 peripheral ========== 
set AT91C_TWI0_FEATURES 0x400840F8
set AT91C_TWI0_IPNAME1 0x400840F0
set AT91C_TWI0_SMR  0x40084008
set AT91C_TWI0_MMR  0x40084004
set AT91C_TWI0_SR   0x40084020
set AT91C_TWI0_IPNAME2 0x400840F4
set AT91C_TWI0_CR   0x40084000
set AT91C_TWI0_IER  0x40084024
set AT91C_TWI0_RHR  0x40084030
set AT91C_TWI0_ADDRSIZE 0x400840EC
set AT91C_TWI0_THR  0x40084034
set AT91C_TWI0_VER  0x400840FC
set AT91C_TWI0_IADR 0x4008400C
set AT91C_TWI0_IMR  0x4008402C
set AT91C_TWI0_CWGR 0x40084010
set AT91C_TWI0_IDR  0x40084028
# ========== Register definition for TWI1 peripheral ========== 
set AT91C_TWI1_VER  0x400880FC
set AT91C_TWI1_IDR  0x40088028
set AT91C_TWI1_IPNAME2 0x400880F4
set AT91C_TWI1_CWGR 0x40088010
set AT91C_TWI1_CR   0x40088000
set AT91C_TWI1_ADDRSIZE 0x400880EC
set AT91C_TWI1_IADR 0x4008800C
set AT91C_TWI1_IER  0x40088024
set AT91C_TWI1_SMR  0x40088008
set AT91C_TWI1_RHR  0x40088030
set AT91C_TWI1_FEATURES 0x400880F8
set AT91C_TWI1_IMR  0x4008802C
set AT91C_TWI1_SR   0x40088020
set AT91C_TWI1_THR  0x40088034
set AT91C_TWI1_MMR  0x40088004
set AT91C_TWI1_IPNAME1 0x400880F0
# ========== Register definition for PDC_US0 peripheral ========== 
set AT91C_US0_RNCR  0x40090114
set AT91C_US0_TNPR  0x40090118
set AT91C_US0_TPR   0x40090108
set AT91C_US0_RCR   0x40090104
set AT91C_US0_RNPR  0x40090110
set AT91C_US0_TNCR  0x4009011C
set AT91C_US0_PTSR  0x40090124
set AT91C_US0_RPR   0x40090100
set AT91C_US0_PTCR  0x40090120
set AT91C_US0_TCR   0x4009010C
# ========== Register definition for US0 peripheral ========== 
set AT91C_US0_NER   0x40090044
set AT91C_US0_RHR   0x40090018
set AT91C_US0_IPNAME1 0x400900F0
set AT91C_US0_MR    0x40090004
set AT91C_US0_RTOR  0x40090024
set AT91C_US0_IF    0x4009004C
set AT91C_US0_ADDRSIZE 0x400900EC
set AT91C_US0_IDR   0x4009000C
set AT91C_US0_IMR   0x40090010
set AT91C_US0_IER   0x40090008
set AT91C_US0_TTGR  0x40090028
set AT91C_US0_IPNAME2 0x400900F4
set AT91C_US0_FIDI  0x40090040
set AT91C_US0_CR    0x40090000
set AT91C_US0_BRGR  0x40090020
set AT91C_US0_MAN   0x40090050
set AT91C_US0_VER   0x400900FC
set AT91C_US0_FEATURES 0x400900F8
set AT91C_US0_CSR   0x40090014
set AT91C_US0_THR   0x4009001C
# ========== Register definition for PDC_US1 peripheral ========== 
set AT91C_US1_TNPR  0x40094118
set AT91C_US1_TPR   0x40094108
set AT91C_US1_RNCR  0x40094114
set AT91C_US1_TNCR  0x4009411C
set AT91C_US1_RNPR  0x40094110
set AT91C_US1_TCR   0x4009410C
set AT91C_US1_PTSR  0x40094124
set AT91C_US1_RCR   0x40094104
set AT91C_US1_RPR   0x40094100
set AT91C_US1_PTCR  0x40094120
# ========== Register definition for US1 peripheral ========== 
set AT91C_US1_IMR   0x40094010
set AT91C_US1_RTOR  0x40094024
set AT91C_US1_RHR   0x40094018
set AT91C_US1_IPNAME1 0x400940F0
set AT91C_US1_VER   0x400940FC
set AT91C_US1_MR    0x40094004
set AT91C_US1_FEATURES 0x400940F8
set AT91C_US1_NER   0x40094044
set AT91C_US1_IPNAME2 0x400940F4
set AT91C_US1_CR    0x40094000
set AT91C_US1_BRGR  0x40094020
set AT91C_US1_IF    0x4009404C
set AT91C_US1_IER   0x40094008
set AT91C_US1_TTGR  0x40094028
set AT91C_US1_FIDI  0x40094040
set AT91C_US1_MAN   0x40094050
set AT91C_US1_ADDRSIZE 0x400940EC
set AT91C_US1_CSR   0x40094014
set AT91C_US1_THR   0x4009401C
set AT91C_US1_IDR   0x4009400C
# ========== Register definition for PDC_US2 peripheral ========== 
set AT91C_US2_RPR   0x40098100
set AT91C_US2_TPR   0x40098108
set AT91C_US2_TCR   0x4009810C
set AT91C_US2_PTSR  0x40098124
set AT91C_US2_PTCR  0x40098120
set AT91C_US2_RNPR  0x40098110
set AT91C_US2_TNCR  0x4009811C
set AT91C_US2_RNCR  0x40098114
set AT91C_US2_TNPR  0x40098118
set AT91C_US2_RCR   0x40098104
# ========== Register definition for US2 peripheral ========== 
set AT91C_US2_MAN   0x40098050
set AT91C_US2_ADDRSIZE 0x400980EC
set AT91C_US2_MR    0x40098004
set AT91C_US2_IPNAME1 0x400980F0
set AT91C_US2_IF    0x4009804C
set AT91C_US2_BRGR  0x40098020
set AT91C_US2_FIDI  0x40098040
set AT91C_US2_IER   0x40098008
set AT91C_US2_RTOR  0x40098024
set AT91C_US2_CR    0x40098000
set AT91C_US2_THR   0x4009801C
set AT91C_US2_CSR   0x40098014
set AT91C_US2_VER   0x400980FC
set AT91C_US2_FEATURES 0x400980F8
set AT91C_US2_IDR   0x4009800C
set AT91C_US2_TTGR  0x40098028
set AT91C_US2_IPNAME2 0x400980F4
set AT91C_US2_RHR   0x40098018
set AT91C_US2_NER   0x40098044
set AT91C_US2_IMR   0x40098010
# ========== Register definition for PDC_US3 peripheral ========== 
set AT91C_US3_TPR   0x4009C108
set AT91C_US3_PTCR  0x4009C120
set AT91C_US3_TCR   0x4009C10C
set AT91C_US3_RCR   0x4009C104
set AT91C_US3_RNCR  0x4009C114
set AT91C_US3_RNPR  0x4009C110
set AT91C_US3_RPR   0x4009C100
set AT91C_US3_PTSR  0x4009C124
set AT91C_US3_TNCR  0x4009C11C
set AT91C_US3_TNPR  0x4009C118
# ========== Register definition for US3 peripheral ========== 
set AT91C_US3_MAN   0x4009C050
set AT91C_US3_CSR   0x4009C014
set AT91C_US3_BRGR  0x4009C020
set AT91C_US3_IPNAME2 0x4009C0F4
set AT91C_US3_RTOR  0x4009C024
set AT91C_US3_ADDRSIZE 0x4009C0EC
set AT91C_US3_CR    0x4009C000
set AT91C_US3_IF    0x4009C04C
set AT91C_US3_FEATURES 0x4009C0F8
set AT91C_US3_VER   0x4009C0FC
set AT91C_US3_RHR   0x4009C018
set AT91C_US3_TTGR  0x4009C028
set AT91C_US3_NER   0x4009C044
set AT91C_US3_IMR   0x4009C010
set AT91C_US3_THR   0x4009C01C
set AT91C_US3_IDR   0x4009C00C
set AT91C_US3_MR    0x4009C004
set AT91C_US3_IER   0x4009C008
set AT91C_US3_FIDI  0x4009C040
set AT91C_US3_IPNAME1 0x4009C0F0
# ========== Register definition for PDC_SSC0 peripheral ========== 
set AT91C_SSC0_RNCR 0x40004114
set AT91C_SSC0_TPR  0x40004108
set AT91C_SSC0_TCR  0x4000410C
set AT91C_SSC0_PTCR 0x40004120
set AT91C_SSC0_TNPR 0x40004118
set AT91C_SSC0_RPR  0x40004100
set AT91C_SSC0_TNCR 0x4000411C
set AT91C_SSC0_RNPR 0x40004110
set AT91C_SSC0_RCR  0x40004104
set AT91C_SSC0_PTSR 0x40004124
# ========== Register definition for SSC0 peripheral ========== 
set AT91C_SSC0_FEATURES 0x400040F8
set AT91C_SSC0_IPNAME1 0x400040F0
set AT91C_SSC0_CR   0x40004000
set AT91C_SSC0_ADDRSIZE 0x400040EC
set AT91C_SSC0_RHR  0x40004020
set AT91C_SSC0_VER  0x400040FC
set AT91C_SSC0_TSHR 0x40004034
set AT91C_SSC0_RFMR 0x40004014
set AT91C_SSC0_IDR  0x40004048
set AT91C_SSC0_TFMR 0x4000401C
set AT91C_SSC0_RSHR 0x40004030
set AT91C_SSC0_TCMR 0x40004018
set AT91C_SSC0_RCMR 0x40004010
set AT91C_SSC0_SR   0x40004040
set AT91C_SSC0_IPNAME2 0x400040F4
set AT91C_SSC0_THR  0x40004024
set AT91C_SSC0_CMR  0x40004004
set AT91C_SSC0_IER  0x40004044
set AT91C_SSC0_IMR  0x4000404C
# ========== Register definition for PDC_PWMC peripheral ========== 
set AT91C_PWMC_TNCR 0x4008C11C
set AT91C_PWMC_TPR  0x4008C108
set AT91C_PWMC_RPR  0x4008C100
set AT91C_PWMC_TCR  0x4008C10C
set AT91C_PWMC_PTSR 0x4008C124
set AT91C_PWMC_RNPR 0x4008C110
set AT91C_PWMC_RCR  0x4008C104
set AT91C_PWMC_RNCR 0x4008C114
set AT91C_PWMC_PTCR 0x4008C120
set AT91C_PWMC_TNPR 0x4008C118
# ========== Register definition for PWMC_CH0 peripheral ========== 
set AT91C_PWMC_CH0_DTR 0x4008C218
set AT91C_PWMC_CH0_CMR 0x4008C200
set AT91C_PWMC_CH0_CCNTR 0x4008C214
set AT91C_PWMC_CH0_CPRDR 0x4008C20C
set AT91C_PWMC_CH0_DTUPDR 0x4008C21C
set AT91C_PWMC_CH0_CPRDUPDR 0x4008C210
set AT91C_PWMC_CH0_CDTYUPDR 0x4008C208
set AT91C_PWMC_CH0_CDTYR 0x4008C204
# ========== Register definition for PWMC_CH1 peripheral ========== 
set AT91C_PWMC_CH1_CCNTR 0x4008C234
set AT91C_PWMC_CH1_DTR 0x4008C238
set AT91C_PWMC_CH1_CDTYUPDR 0x4008C228
set AT91C_PWMC_CH1_DTUPDR 0x4008C23C
set AT91C_PWMC_CH1_CDTYR 0x4008C224
set AT91C_PWMC_CH1_CPRDR 0x4008C22C
set AT91C_PWMC_CH1_CPRDUPDR 0x4008C230
set AT91C_PWMC_CH1_CMR 0x4008C220
# ========== Register definition for PWMC_CH2 peripheral ========== 
set AT91C_PWMC_CH2_CDTYR 0x4008C244
set AT91C_PWMC_CH2_DTUPDR 0x4008C25C
set AT91C_PWMC_CH2_CCNTR 0x4008C254
set AT91C_PWMC_CH2_CMR 0x4008C240
set AT91C_PWMC_CH2_CPRDR 0x4008C24C
set AT91C_PWMC_CH2_CPRDUPDR 0x4008C250
set AT91C_PWMC_CH2_CDTYUPDR 0x4008C248
set AT91C_PWMC_CH2_DTR 0x4008C258
# ========== Register definition for PWMC_CH3 peripheral ========== 
set AT91C_PWMC_CH3_CPRDUPDR 0x4008C270
set AT91C_PWMC_CH3_DTR 0x4008C278
set AT91C_PWMC_CH3_CDTYR 0x4008C264
set AT91C_PWMC_CH3_DTUPDR 0x4008C27C
set AT91C_PWMC_CH3_CDTYUPDR 0x4008C268
set AT91C_PWMC_CH3_CCNTR 0x4008C274
set AT91C_PWMC_CH3_CMR 0x4008C260
set AT91C_PWMC_CH3_CPRDR 0x4008C26C
# ========== Register definition for PWMC peripheral ========== 
set AT91C_PWMC_CMP6MUPD 0x4008C19C
set AT91C_PWMC_ISR1 0x4008C01C
set AT91C_PWMC_CMP5V 0x4008C180
set AT91C_PWMC_CMP4MUPD 0x4008C17C
set AT91C_PWMC_FMR  0x4008C05C
set AT91C_PWMC_CMP6V 0x4008C190
set AT91C_PWMC_EL4MR 0x4008C08C
set AT91C_PWMC_UPCR 0x4008C028
set AT91C_PWMC_CMP1VUPD 0x4008C144
set AT91C_PWMC_CMP0M 0x4008C138
set AT91C_PWMC_CMP5VUPD 0x4008C184
set AT91C_PWMC_FPER3 0x4008C074
set AT91C_PWMC_OSCUPD 0x4008C058
set AT91C_PWMC_FPER1 0x4008C06C
set AT91C_PWMC_SCUPUPD 0x4008C030
set AT91C_PWMC_DIS  0x4008C008
set AT91C_PWMC_IER1 0x4008C010
set AT91C_PWMC_IMR2 0x4008C03C
set AT91C_PWMC_CMP0V 0x4008C130
set AT91C_PWMC_SR   0x4008C00C
set AT91C_PWMC_CMP4M 0x4008C178
set AT91C_PWMC_CMP3M 0x4008C168
set AT91C_PWMC_IER2 0x4008C034
set AT91C_PWMC_CMP3VUPD 0x4008C164
set AT91C_PWMC_CMP2M 0x4008C158
set AT91C_PWMC_IDR2 0x4008C038
set AT91C_PWMC_EL2MR 0x4008C084
set AT91C_PWMC_CMP7V 0x4008C1A0
set AT91C_PWMC_CMP1M 0x4008C148
set AT91C_PWMC_CMP0VUPD 0x4008C134
set AT91C_PWMC_WPSR 0x4008C0E8
set AT91C_PWMC_CMP6VUPD 0x4008C194
set AT91C_PWMC_CMP1MUPD 0x4008C14C
set AT91C_PWMC_CMP1V 0x4008C140
set AT91C_PWMC_FCR  0x4008C064
set AT91C_PWMC_VER  0x4008C0FC
set AT91C_PWMC_EL1MR 0x4008C080
set AT91C_PWMC_EL6MR 0x4008C094
set AT91C_PWMC_ISR2 0x4008C040
set AT91C_PWMC_CMP4VUPD 0x4008C174
set AT91C_PWMC_CMP5MUPD 0x4008C18C
set AT91C_PWMC_OS   0x4008C048
set AT91C_PWMC_FPV  0x4008C068
set AT91C_PWMC_FPER2 0x4008C070
set AT91C_PWMC_EL7MR 0x4008C098
set AT91C_PWMC_OSSUPD 0x4008C054
set AT91C_PWMC_FEATURES 0x4008C0F8
set AT91C_PWMC_CMP2V 0x4008C150
set AT91C_PWMC_FSR  0x4008C060
set AT91C_PWMC_ADDRSIZE 0x4008C0EC
set AT91C_PWMC_OSC  0x4008C050
set AT91C_PWMC_SCUP 0x4008C02C
set AT91C_PWMC_CMP7MUPD 0x4008C1AC
set AT91C_PWMC_CMP2VUPD 0x4008C154
set AT91C_PWMC_FPER4 0x4008C078
set AT91C_PWMC_IMR1 0x4008C018
set AT91C_PWMC_EL3MR 0x4008C088
set AT91C_PWMC_CMP3V 0x4008C160
set AT91C_PWMC_IPNAME1 0x4008C0F0
set AT91C_PWMC_OSS  0x4008C04C
set AT91C_PWMC_CMP0MUPD 0x4008C13C
set AT91C_PWMC_CMP2MUPD 0x4008C15C
set AT91C_PWMC_CMP4V 0x4008C170
set AT91C_PWMC_ENA  0x4008C004
set AT91C_PWMC_CMP3MUPD 0x4008C16C
set AT91C_PWMC_EL0MR 0x4008C07C
set AT91C_PWMC_OOV  0x4008C044
set AT91C_PWMC_WPCR 0x4008C0E4
set AT91C_PWMC_CMP7M 0x4008C1A8
set AT91C_PWMC_CMP6M 0x4008C198
set AT91C_PWMC_CMP5M 0x4008C188
set AT91C_PWMC_IPNAME2 0x4008C0F4
set AT91C_PWMC_CMP7VUPD 0x4008C1A4
set AT91C_PWMC_SYNC 0x4008C020
set AT91C_PWMC_MR   0x4008C000
set AT91C_PWMC_IDR1 0x4008C014
set AT91C_PWMC_EL5MR 0x4008C090
# ========== Register definition for SPI0 peripheral ========== 
set AT91C_SPI0_ADDRSIZE 0x400080EC
set AT91C_SPI0_RDR  0x40008008
set AT91C_SPI0_FEATURES 0x400080F8
set AT91C_SPI0_CR   0x40008000
set AT91C_SPI0_IPNAME1 0x400080F0
set AT91C_SPI0_VER  0x400080FC
set AT91C_SPI0_IDR  0x40008018
set AT91C_SPI0_TDR  0x4000800C
set AT91C_SPI0_MR   0x40008004
set AT91C_SPI0_IER  0x40008014
set AT91C_SPI0_IMR  0x4000801C
set AT91C_SPI0_IPNAME2 0x400080F4
set AT91C_SPI0_CSR  0x40008030
set AT91C_SPI0_SR   0x40008010
# ========== Register definition for UDPHS_EPTFIFO peripheral ========== 
set AT91C_UDPHS_EPTFIFO_READEPT6 0x201E0000
set AT91C_UDPHS_EPTFIFO_READEPT2 0x201A0000
set AT91C_UDPHS_EPTFIFO_READEPT1 0x20190000
set AT91C_UDPHS_EPTFIFO_READEPT0 0x20180000
set AT91C_UDPHS_EPTFIFO_READEPT5 0x201D0000
set AT91C_UDPHS_EPTFIFO_READEPT4 0x201C0000
set AT91C_UDPHS_EPTFIFO_READEPT3 0x201B0000
# ========== Register definition for UDPHS_EPT_0 peripheral ========== 
set AT91C_UDPHS_EPT_0_EPTCTL 0x400A410C
set AT91C_UDPHS_EPT_0_EPTSTA 0x400A411C
set AT91C_UDPHS_EPT_0_EPTCLRSTA 0x400A4118
set AT91C_UDPHS_EPT_0_EPTCTLDIS 0x400A4108
set AT91C_UDPHS_EPT_0_EPTCFG 0x400A4100
set AT91C_UDPHS_EPT_0_EPTSETSTA 0x400A4114
set AT91C_UDPHS_EPT_0_EPTCTLENB 0x400A4104
# ========== Register definition for UDPHS_EPT_1 peripheral ========== 
set AT91C_UDPHS_EPT_1_EPTSTA 0x400A413C
set AT91C_UDPHS_EPT_1_EPTSETSTA 0x400A4134
set AT91C_UDPHS_EPT_1_EPTCTL 0x400A412C
set AT91C_UDPHS_EPT_1_EPTCFG 0x400A4120
set AT91C_UDPHS_EPT_1_EPTCTLDIS 0x400A4128
set AT91C_UDPHS_EPT_1_EPTCLRSTA 0x400A4138
set AT91C_UDPHS_EPT_1_EPTCTLENB 0x400A4124
# ========== Register definition for UDPHS_EPT_2 peripheral ========== 
set AT91C_UDPHS_EPT_2_EPTCTLENB 0x400A4144
set AT91C_UDPHS_EPT_2_EPTCLRSTA 0x400A4158
set AT91C_UDPHS_EPT_2_EPTCFG 0x400A4140
set AT91C_UDPHS_EPT_2_EPTCTL 0x400A414C
set AT91C_UDPHS_EPT_2_EPTSETSTA 0x400A4154
set AT91C_UDPHS_EPT_2_EPTSTA 0x400A415C
set AT91C_UDPHS_EPT_2_EPTCTLDIS 0x400A4148
# ========== Register definition for UDPHS_EPT_3 peripheral ========== 
set AT91C_UDPHS_EPT_3_EPTCTLDIS 0x400A4168
set AT91C_UDPHS_EPT_3_EPTCTLENB 0x400A4164
set AT91C_UDPHS_EPT_3_EPTSETSTA 0x400A4174
set AT91C_UDPHS_EPT_3_EPTCLRSTA 0x400A4178
set AT91C_UDPHS_EPT_3_EPTCFG 0x400A4160
set AT91C_UDPHS_EPT_3_EPTSTA 0x400A417C
set AT91C_UDPHS_EPT_3_EPTCTL 0x400A416C
# ========== Register definition for UDPHS_EPT_4 peripheral ========== 
set AT91C_UDPHS_EPT_4_EPTSETSTA 0x400A4194
set AT91C_UDPHS_EPT_4_EPTCTLDIS 0x400A4188
set AT91C_UDPHS_EPT_4_EPTCTL 0x400A418C
set AT91C_UDPHS_EPT_4_EPTCFG 0x400A4180
set AT91C_UDPHS_EPT_4_EPTCTLENB 0x400A4184
set AT91C_UDPHS_EPT_4_EPTSTA 0x400A419C
set AT91C_UDPHS_EPT_4_EPTCLRSTA 0x400A4198
# ========== Register definition for UDPHS_EPT_5 peripheral ========== 
set AT91C_UDPHS_EPT_5_EPTCFG 0x400A41A0
set AT91C_UDPHS_EPT_5_EPTCTL 0x400A41AC
set AT91C_UDPHS_EPT_5_EPTCTLENB 0x400A41A4
set AT91C_UDPHS_EPT_5_EPTSTA 0x400A41BC
set AT91C_UDPHS_EPT_5_EPTSETSTA 0x400A41B4
set AT91C_UDPHS_EPT_5_EPTCTLDIS 0x400A41A8
set AT91C_UDPHS_EPT_5_EPTCLRSTA 0x400A41B8
# ========== Register definition for UDPHS_EPT_6 peripheral ========== 
set AT91C_UDPHS_EPT_6_EPTCLRSTA 0x400A41D8
set AT91C_UDPHS_EPT_6_EPTCTL 0x400A41CC
set AT91C_UDPHS_EPT_6_EPTCFG 0x400A41C0
set AT91C_UDPHS_EPT_6_EPTCTLDIS 0x400A41C8
set AT91C_UDPHS_EPT_6_EPTSTA 0x400A41DC
set AT91C_UDPHS_EPT_6_EPTCTLENB 0x400A41C4
set AT91C_UDPHS_EPT_6_EPTSETSTA 0x400A41D4
# ========== Register definition for UDPHS_DMA_1 peripheral ========== 
set AT91C_UDPHS_DMA_1_DMASTATUS 0x400A431C
set AT91C_UDPHS_DMA_1_DMACONTROL 0x400A4318
set AT91C_UDPHS_DMA_1_DMANXTDSC 0x400A4310
set AT91C_UDPHS_DMA_1_DMAADDRESS 0x400A4314
# ========== Register definition for UDPHS_DMA_2 peripheral ========== 
set AT91C_UDPHS_DMA_2_DMASTATUS 0x400A432C
set AT91C_UDPHS_DMA_2_DMANXTDSC 0x400A4320
set AT91C_UDPHS_DMA_2_DMACONTROL 0x400A4328
set AT91C_UDPHS_DMA_2_DMAADDRESS 0x400A4324
# ========== Register definition for UDPHS_DMA_3 peripheral ========== 
set AT91C_UDPHS_DMA_3_DMACONTROL 0x400A4338
set AT91C_UDPHS_DMA_3_DMANXTDSC 0x400A4330
set AT91C_UDPHS_DMA_3_DMASTATUS 0x400A433C
set AT91C_UDPHS_DMA_3_DMAADDRESS 0x400A4334
# ========== Register definition for UDPHS_DMA_4 peripheral ========== 
set AT91C_UDPHS_DMA_4_DMAADDRESS 0x400A4344
set AT91C_UDPHS_DMA_4_DMANXTDSC 0x400A4340
set AT91C_UDPHS_DMA_4_DMASTATUS 0x400A434C
set AT91C_UDPHS_DMA_4_DMACONTROL 0x400A4348
# ========== Register definition for UDPHS_DMA_5 peripheral ========== 
set AT91C_UDPHS_DMA_5_DMACONTROL 0x400A4358
set AT91C_UDPHS_DMA_5_DMAADDRESS 0x400A4354
set AT91C_UDPHS_DMA_5_DMANXTDSC 0x400A4350
set AT91C_UDPHS_DMA_5_DMASTATUS 0x400A435C
# ========== Register definition for UDPHS_DMA_6 peripheral ========== 
set AT91C_UDPHS_DMA_6_DMASTATUS 0x400A436C
set AT91C_UDPHS_DMA_6_DMACONTROL 0x400A4368
set AT91C_UDPHS_DMA_6_DMANXTDSC 0x400A4360
set AT91C_UDPHS_DMA_6_DMAADDRESS 0x400A4364
# ========== Register definition for UDPHS peripheral ========== 
set AT91C_UDPHS_EPTRST 0x400A401C
set AT91C_UDPHS_IEN 0x400A4010
set AT91C_UDPHS_TSTCNTB 0x400A40D8
set AT91C_UDPHS_RIPNAME2 0x400A40F4
set AT91C_UDPHS_RIPPADDRSIZE 0x400A40EC
set AT91C_UDPHS_TSTMODREG 0x400A40DC
set AT91C_UDPHS_TST 0x400A40E0
set AT91C_UDPHS_TSTSOFCNT 0x400A40D0
set AT91C_UDPHS_FNUM 0x400A4004
set AT91C_UDPHS_TSTCNTA 0x400A40D4
set AT91C_UDPHS_INTSTA 0x400A4014
set AT91C_UDPHS_IPFEATURES 0x400A40F8
set AT91C_UDPHS_CLRINT 0x400A4018
set AT91C_UDPHS_RIPNAME1 0x400A40F0
set AT91C_UDPHS_CTRL 0x400A4000
set AT91C_UDPHS_IPVERSION 0x400A40FC
# ========== Register definition for HDMA_CH_0 peripheral ========== 
set AT91C_HDMA_CH_0_CADDR 0x400B0060
set AT91C_HDMA_CH_0_DADDR 0x400B0040
set AT91C_HDMA_CH_0_BDSCR 0x400B005C
set AT91C_HDMA_CH_0_CFG 0x400B0050
set AT91C_HDMA_CH_0_CTRLB 0x400B004C
set AT91C_HDMA_CH_0_CTRLA 0x400B0048
set AT91C_HDMA_CH_0_DSCR 0x400B0044
set AT91C_HDMA_CH_0_SADDR 0x400B003C
set AT91C_HDMA_CH_0_DPIP 0x400B0058
set AT91C_HDMA_CH_0_SPIP 0x400B0054
# ========== Register definition for HDMA_CH_1 peripheral ========== 
set AT91C_HDMA_CH_1_DSCR 0x400B006C
set AT91C_HDMA_CH_1_BDSCR 0x400B0084
set AT91C_HDMA_CH_1_CTRLB 0x400B0074
set AT91C_HDMA_CH_1_SPIP 0x400B007C
set AT91C_HDMA_CH_1_SADDR 0x400B0064
set AT91C_HDMA_CH_1_DPIP 0x400B0080
set AT91C_HDMA_CH_1_CFG 0x400B0078
set AT91C_HDMA_CH_1_DADDR 0x400B0068
set AT91C_HDMA_CH_1_CADDR 0x400B0088
set AT91C_HDMA_CH_1_CTRLA 0x400B0070
# ========== Register definition for HDMA_CH_2 peripheral ========== 
set AT91C_HDMA_CH_2_BDSCR 0x400B00AC
set AT91C_HDMA_CH_2_CTRLB 0x400B009C
set AT91C_HDMA_CH_2_CADDR 0x400B00B0
set AT91C_HDMA_CH_2_CFG 0x400B00A0
set AT91C_HDMA_CH_2_CTRLA 0x400B0098
set AT91C_HDMA_CH_2_SADDR 0x400B008C
set AT91C_HDMA_CH_2_DPIP 0x400B00A8
set AT91C_HDMA_CH_2_DADDR 0x400B0090
set AT91C_HDMA_CH_2_SPIP 0x400B00A4
set AT91C_HDMA_CH_2_DSCR 0x400B0094
# ========== Register definition for HDMA_CH_3 peripheral ========== 
set AT91C_HDMA_CH_3_DSCR 0x400B00BC
set AT91C_HDMA_CH_3_SADDR 0x400B00B4
set AT91C_HDMA_CH_3_BDSCR 0x400B00D4
set AT91C_HDMA_CH_3_CTRLA 0x400B00C0
set AT91C_HDMA_CH_3_DPIP 0x400B00D0
set AT91C_HDMA_CH_3_CTRLB 0x400B00C4
set AT91C_HDMA_CH_3_SPIP 0x400B00CC
set AT91C_HDMA_CH_3_CFG 0x400B00C8
set AT91C_HDMA_CH_3_CADDR 0x400B00D8
set AT91C_HDMA_CH_3_DADDR 0x400B00B8
# ========== Register definition for HDMA peripheral ========== 
set AT91C_HDMA_SYNC 0x400B0014
set AT91C_HDMA_VER  0x400B01FC
set AT91C_HDMA_RSVD0 0x400B0034
set AT91C_HDMA_CHSR 0x400B0030
set AT91C_HDMA_IPNAME2 0x400B01F4
set AT91C_HDMA_EBCIMR 0x400B0020
set AT91C_HDMA_CHDR 0x400B002C
set AT91C_HDMA_EN   0x400B0004
set AT91C_HDMA_GCFG 0x400B0000
set AT91C_HDMA_IPNAME1 0x400B01F0
set AT91C_HDMA_LAST 0x400B0010
set AT91C_HDMA_FEATURES 0x400B01F8
set AT91C_HDMA_CREQ 0x400B000C
set AT91C_HDMA_EBCIER 0x400B0018
set AT91C_HDMA_CHER 0x400B0028
set AT91C_HDMA_ADDRSIZE 0x400B01EC
set AT91C_HDMA_EBCISR 0x400B0024
set AT91C_HDMA_SREQ 0x400B0008
set AT91C_HDMA_EBCIDR 0x400B001C
set AT91C_HDMA_RSVD1 0x400B0038

# *****************************************************************************
#               BASE ADDRESS DEFINITIONS FOR AT91SAM3UE256
# *****************************************************************************
set AT91C_BASE_SYS       0x400E0000
set AT91C_BASE_HSMC4_CS0 0x400E0070
set AT91C_BASE_HSMC4_CS1 0x400E0084
set AT91C_BASE_HSMC4_CS2 0x400E0098
set AT91C_BASE_HSMC4_CS3 0x400E00AC
set AT91C_BASE_HSMC4_NFC 0x400E00FC
set AT91C_BASE_HSMC4     0x400E0000
set AT91C_BASE_MATRIX    0x400E0200
set AT91C_BASE_NVIC      0xE000E000
set AT91C_BASE_MPU       0xE000ED90
set AT91C_BASE_CM3       0xE000ED00
set AT91C_BASE_PDC_DBGU  0x400E0700
set AT91C_BASE_DBGU      0x400E0600
set AT91C_BASE_PIOA      0x400E0C00
set AT91C_BASE_PIOB      0x400E0E00
set AT91C_BASE_PIOC      0x400E1000
set AT91C_BASE_PMC       0x400E0400
set AT91C_BASE_CKGR      0x400E041C
set AT91C_BASE_RSTC      0x400E1200
set AT91C_BASE_SUPC      0x400E1210
set AT91C_BASE_RTTC      0x400E1230
set AT91C_BASE_WDTC      0x400E1250
set AT91C_BASE_RTC       0x400E1260
set AT91C_BASE_ADC0      0x400A8000
set AT91C_BASE_ADC1      0x400AC000
set AT91C_BASE_TC0       0x40080000
set AT91C_BASE_TC1       0x40080040
set AT91C_BASE_TC2       0x40080080
set AT91C_BASE_TCB0      0x40080000
set AT91C_BASE_TCB1      0x40080040
set AT91C_BASE_TCB2      0x40080080
set AT91C_BASE_EFC0      0x400E0800
set AT91C_BASE_EFC1      0x400E0A00
set AT91C_BASE_MCI0      0x40000000
set AT91C_BASE_PDC_TWI0  0x40084100
set AT91C_BASE_PDC_TWI1  0x40088100
set AT91C_BASE_TWI0      0x40084000
set AT91C_BASE_TWI1      0x40088000
set AT91C_BASE_PDC_US0   0x40090100
set AT91C_BASE_US0       0x40090000
set AT91C_BASE_PDC_US1   0x40094100
set AT91C_BASE_US1       0x40094000
set AT91C_BASE_PDC_US2   0x40098100
set AT91C_BASE_US2       0x40098000
set AT91C_BASE_PDC_US3   0x4009C100
set AT91C_BASE_US3       0x4009C000
set AT91C_BASE_PDC_SSC0  0x40004100
set AT91C_BASE_SSC0      0x40004000
set AT91C_BASE_PDC_PWMC  0x4008C100
set AT91C_BASE_PWMC_CH0  0x4008C200
set AT91C_BASE_PWMC_CH1  0x4008C220
set AT91C_BASE_PWMC_CH2  0x4008C240
set AT91C_BASE_PWMC_CH3  0x4008C260
set AT91C_BASE_PWMC      0x4008C000
set AT91C_BASE_SPI0      0x40008000
set AT91C_BASE_UDPHS_EPTFIFO 0x20180000
set AT91C_BASE_UDPHS_EPT_0 0x400A4100
set AT91C_BASE_UDPHS_EPT_1 0x400A4120
set AT91C_BASE_UDPHS_EPT_2 0x400A4140
set AT91C_BASE_UDPHS_EPT_3 0x400A4160
set AT91C_BASE_UDPHS_EPT_4 0x400A4180
set AT91C_BASE_UDPHS_EPT_5 0x400A41A0
set AT91C_BASE_UDPHS_EPT_6 0x400A41C0
set AT91C_BASE_UDPHS_DMA_1 0x400A4310
set AT91C_BASE_UDPHS_DMA_2 0x400A4320
set AT91C_BASE_UDPHS_DMA_3 0x400A4330
set AT91C_BASE_UDPHS_DMA_4 0x400A4340
set AT91C_BASE_UDPHS_DMA_5 0x400A4350
set AT91C_BASE_UDPHS_DMA_6 0x400A4360
set AT91C_BASE_UDPHS     0x400A4000
set AT91C_BASE_HDMA_CH_0 0x400B003C
set AT91C_BASE_HDMA_CH_1 0x400B0064
set AT91C_BASE_HDMA_CH_2 0x400B008C
set AT91C_BASE_HDMA_CH_3 0x400B00B4
set AT91C_BASE_HDMA      0x400B0000

# *****************************************************************************
#               PERIPHERAL ID DEFINITIONS FOR AT91SAM3UE256
# *****************************************************************************
set AT91C_ID_SUPC    0
set AT91C_ID_RSTC    1
set AT91C_ID_RTC     2
set AT91C_ID_RTT     3
set AT91C_ID_WDG     4
set AT91C_ID_PMC     5
set AT91C_ID_EFC0    6
set AT91C_ID_EFC1    7
set AT91C_ID_DBGU    8
set AT91C_ID_HSMC4   9
set AT91C_ID_PIOA   10
set AT91C_ID_PIOB   11
set AT91C_ID_PIOC   12
set AT91C_ID_US0    13
set AT91C_ID_US1    14
set AT91C_ID_US2    15
set AT91C_ID_US3    16
set AT91C_ID_MCI0   17
set AT91C_ID_TWI0   18
set AT91C_ID_TWI1   19
set AT91C_ID_SPI0   20
set AT91C_ID_SSC0   21
set AT91C_ID_TC0    22
set AT91C_ID_TC1    23
set AT91C_ID_TC2    24
set AT91C_ID_PWMC   25
set AT91C_ID_ADCC0  26
set AT91C_ID_ADCC1  27
set AT91C_ID_HDMA   28
set AT91C_ID_UDPHS  29

# *****************************************************************************
#               PIO DEFINITIONS FOR AT91SAM3UE256
# *****************************************************************************
set AT91C_PIO_PA0        [expr 1 <<  0 ]
set AT91C_PA0_TIOB0    $AT91C_PIO_PA0
set AT91C_PA0_SPI0_NPCS1 $AT91C_PIO_PA0
set AT91C_PIO_PA1        [expr 1 <<  1 ]
set AT91C_PA1_TIOA0    $AT91C_PIO_PA1
set AT91C_PA1_SPI0_NPCS2 $AT91C_PIO_PA1
set AT91C_PIO_PA10       [expr 1 << 10 ]
set AT91C_PA10_TWCK0    $AT91C_PIO_PA10
set AT91C_PA10_PWML3    $AT91C_PIO_PA10
set AT91C_PIO_PA11       [expr 1 << 11 ]
set AT91C_PA11_DRXD     $AT91C_PIO_PA11
set AT91C_PIO_PA12       [expr 1 << 12 ]
set AT91C_PA12_DTXD     $AT91C_PIO_PA12
set AT91C_PIO_PA13       [expr 1 << 13 ]
set AT91C_PA13_SPI0_MISO $AT91C_PIO_PA13
set AT91C_PIO_PA14       [expr 1 << 14 ]
set AT91C_PA14_SPI0_MOSI $AT91C_PIO_PA14
set AT91C_PIO_PA15       [expr 1 << 15 ]
set AT91C_PA15_SPI0_SPCK $AT91C_PIO_PA15
set AT91C_PA15_PWMH2    $AT91C_PIO_PA15
set AT91C_PIO_PA16       [expr 1 << 16 ]
set AT91C_PA16_SPI0_NPCS0 $AT91C_PIO_PA16
set AT91C_PA16_NCS1     $AT91C_PIO_PA16
set AT91C_PIO_PA17       [expr 1 << 17 ]
set AT91C_PA17_SCK0     $AT91C_PIO_PA17
set AT91C_PA17_ADTRG0   $AT91C_PIO_PA17
set AT91C_PIO_PA18       [expr 1 << 18 ]
set AT91C_PA18_TXD0     $AT91C_PIO_PA18
set AT91C_PIO_PA19       [expr 1 << 19 ]
set AT91C_PA19_RXD0     $AT91C_PIO_PA19
set AT91C_PA19_SPI0_NPCS3 $AT91C_PIO_PA19
set AT91C_PIO_PA2        [expr 1 <<  2 ]
set AT91C_PA2_TCLK0    $AT91C_PIO_PA2
set AT91C_PA2_ADTRG1   $AT91C_PIO_PA2
set AT91C_PIO_PA20       [expr 1 << 20 ]
set AT91C_PA20_TXD1     $AT91C_PIO_PA20
set AT91C_PA20_PWMH3    $AT91C_PIO_PA20
set AT91C_PIO_PA21       [expr 1 << 21 ]
set AT91C_PA21_RXD1     $AT91C_PIO_PA21
set AT91C_PA21_PCK0     $AT91C_PIO_PA21
set AT91C_PIO_PA22       [expr 1 << 22 ]
set AT91C_PA22_TXD2     $AT91C_PIO_PA22
set AT91C_PA22_RTS1     $AT91C_PIO_PA22
set AT91C_PIO_PA23       [expr 1 << 23 ]
set AT91C_PA23_RXD2     $AT91C_PIO_PA23
set AT91C_PA23_CTS1     $AT91C_PIO_PA23
set AT91C_PIO_PA24       [expr 1 << 24 ]
set AT91C_PA24_TWD1     $AT91C_PIO_PA24
set AT91C_PA24_SCK1     $AT91C_PIO_PA24
set AT91C_PIO_PA25       [expr 1 << 25 ]
set AT91C_PA25_TWCK1    $AT91C_PIO_PA25
set AT91C_PA25_SCK2     $AT91C_PIO_PA25
set AT91C_PIO_PA26       [expr 1 << 26 ]
set AT91C_PA26_TD0      $AT91C_PIO_PA26
set AT91C_PA26_TCLK2    $AT91C_PIO_PA26
set AT91C_PIO_PA27       [expr 1 << 27 ]
set AT91C_PA27_RD0      $AT91C_PIO_PA27
set AT91C_PA27_PCK0     $AT91C_PIO_PA27
set AT91C_PIO_PA28       [expr 1 << 28 ]
set AT91C_PA28_TK0      $AT91C_PIO_PA28
set AT91C_PA28_PWMH0    $AT91C_PIO_PA28
set AT91C_PIO_PA29       [expr 1 << 29 ]
set AT91C_PA29_RK0      $AT91C_PIO_PA29
set AT91C_PA29_PWMH1    $AT91C_PIO_PA29
set AT91C_PIO_PA3        [expr 1 <<  3 ]
set AT91C_PA3_MCI0_CK  $AT91C_PIO_PA3
set AT91C_PA3_PCK1     $AT91C_PIO_PA3
set AT91C_PIO_PA30       [expr 1 << 30 ]
set AT91C_PA30_TF0      $AT91C_PIO_PA30
set AT91C_PA30_TIOA2    $AT91C_PIO_PA30
set AT91C_PIO_PA31       [expr 1 << 31 ]
set AT91C_PA31_RF0      $AT91C_PIO_PA31
set AT91C_PA31_TIOB2    $AT91C_PIO_PA31
set AT91C_PIO_PA4        [expr 1 <<  4 ]
set AT91C_PA4_MCI0_CDA $AT91C_PIO_PA4
set AT91C_PA4_PWMH0    $AT91C_PIO_PA4
set AT91C_PIO_PA5        [expr 1 <<  5 ]
set AT91C_PA5_MCI0_DA0 $AT91C_PIO_PA5
set AT91C_PA5_PWMH1    $AT91C_PIO_PA5
set AT91C_PIO_PA6        [expr 1 <<  6 ]
set AT91C_PA6_MCI0_DA1 $AT91C_PIO_PA6
set AT91C_PA6_PWMH2    $AT91C_PIO_PA6
set AT91C_PIO_PA7        [expr 1 <<  7 ]
set AT91C_PA7_MCI0_DA2 $AT91C_PIO_PA7
set AT91C_PA7_PWML0    $AT91C_PIO_PA7
set AT91C_PIO_PA8        [expr 1 <<  8 ]
set AT91C_PA8_MCI0_DA3 $AT91C_PIO_PA8
set AT91C_PA8_PWML1    $AT91C_PIO_PA8
set AT91C_PIO_PA9        [expr 1 <<  9 ]
set AT91C_PA9_TWD0     $AT91C_PIO_PA9
set AT91C_PA9_PWML2    $AT91C_PIO_PA9
set AT91C_PIO_PB0        [expr 1 <<  0 ]
set AT91C_PB0_PWMH0    $AT91C_PIO_PB0
set AT91C_PB0_A2       $AT91C_PIO_PB0
set AT91C_PIO_PB1        [expr 1 <<  1 ]
set AT91C_PB1_PWMH1    $AT91C_PIO_PB1
set AT91C_PB1_A3       $AT91C_PIO_PB1
set AT91C_PIO_PB10       [expr 1 << 10 ]
set AT91C_PB10_D1       $AT91C_PIO_PB10
set AT91C_PB10_DSR0     $AT91C_PIO_PB10
set AT91C_PIO_PB11       [expr 1 << 11 ]
set AT91C_PB11_D2       $AT91C_PIO_PB11
set AT91C_PB11_DCD0     $AT91C_PIO_PB11
set AT91C_PIO_PB12       [expr 1 << 12 ]
set AT91C_PB12_D3       $AT91C_PIO_PB12
set AT91C_PB12_RI0      $AT91C_PIO_PB12
set AT91C_PIO_PB13       [expr 1 << 13 ]
set AT91C_PB13_D4       $AT91C_PIO_PB13
set AT91C_PB13_PWMH0    $AT91C_PIO_PB13
set AT91C_PIO_PB14       [expr 1 << 14 ]
set AT91C_PB14_D5       $AT91C_PIO_PB14
set AT91C_PB14_PWMH1    $AT91C_PIO_PB14
set AT91C_PIO_PB15       [expr 1 << 15 ]
set AT91C_PB15_D6       $AT91C_PIO_PB15
set AT91C_PB15_PWMH2    $AT91C_PIO_PB15
set AT91C_PIO_PB16       [expr 1 << 16 ]
set AT91C_PB16_D7       $AT91C_PIO_PB16
set AT91C_PB16_PWMH3    $AT91C_PIO_PB16
set AT91C_PIO_PB17       [expr 1 << 17 ]
set AT91C_PB17_NANDOE   $AT91C_PIO_PB17
set AT91C_PB17_PWML0    $AT91C_PIO_PB17
set AT91C_PIO_PB18       [expr 1 << 18 ]
set AT91C_PB18_NANDWE   $AT91C_PIO_PB18
set AT91C_PB18_PWML1    $AT91C_PIO_PB18
set AT91C_PIO_PB19       [expr 1 << 19 ]
set AT91C_PB19_NRD      $AT91C_PIO_PB19
set AT91C_PB19_PWML2    $AT91C_PIO_PB19
set AT91C_PIO_PB2        [expr 1 <<  2 ]
set AT91C_PB2_PWMH2    $AT91C_PIO_PB2
set AT91C_PB2_A4       $AT91C_PIO_PB2
set AT91C_PIO_PB20       [expr 1 << 20 ]
set AT91C_PB20_NCS0     $AT91C_PIO_PB20
set AT91C_PB20_PWML3    $AT91C_PIO_PB20
set AT91C_PIO_PB21       [expr 1 << 21 ]
set AT91C_PB21_A21_NANDALE $AT91C_PIO_PB21
set AT91C_PB21_RTS2     $AT91C_PIO_PB21
set AT91C_PIO_PB22       [expr 1 << 22 ]
set AT91C_PB22_A22_NANDCLE $AT91C_PIO_PB22
set AT91C_PB22_CTS2     $AT91C_PIO_PB22
set AT91C_PIO_PB23       [expr 1 << 23 ]
set AT91C_PB23_NWR0_NWE $AT91C_PIO_PB23
set AT91C_PB23_PCK2     $AT91C_PIO_PB23
set AT91C_PIO_PB24       [expr 1 << 24 ]
set AT91C_PB24_NANDRDY  $AT91C_PIO_PB24
set AT91C_PB24_PCK1     $AT91C_PIO_PB24
set AT91C_PIO_PB25       [expr 1 << 25 ]
set AT91C_PB25_D8       $AT91C_PIO_PB25
set AT91C_PB25_PWML0    $AT91C_PIO_PB25
set AT91C_PIO_PB26       [expr 1 << 26 ]
set AT91C_PB26_D9       $AT91C_PIO_PB26
set AT91C_PB26_PWML1    $AT91C_PIO_PB26
set AT91C_PIO_PB27       [expr 1 << 27 ]
set AT91C_PB27_D10      $AT91C_PIO_PB27
set AT91C_PB27_PWML2    $AT91C_PIO_PB27
set AT91C_PIO_PB28       [expr 1 << 28 ]
set AT91C_PB28_D11      $AT91C_PIO_PB28
set AT91C_PB28_PWML3    $AT91C_PIO_PB28
set AT91C_PIO_PB29       [expr 1 << 29 ]
set AT91C_PB29_D12      $AT91C_PIO_PB29
set AT91C_PIO_PB3        [expr 1 <<  3 ]
set AT91C_PB3_PWMH3    $AT91C_PIO_PB3
set AT91C_PB3_A5       $AT91C_PIO_PB3
set AT91C_PIO_PB30       [expr 1 << 30 ]
set AT91C_PB30_D13      $AT91C_PIO_PB30
set AT91C_PIO_PB31       [expr 1 << 31 ]
set AT91C_PB31_D14      $AT91C_PIO_PB31
set AT91C_PIO_PB4        [expr 1 <<  4 ]
set AT91C_PB4_TCLK1    $AT91C_PIO_PB4
set AT91C_PB4_A6       $AT91C_PIO_PB4
set AT91C_PIO_PB5        [expr 1 <<  5 ]
set AT91C_PB5_TIOA1    $AT91C_PIO_PB5
set AT91C_PB5_A7       $AT91C_PIO_PB5
set AT91C_PIO_PB6        [expr 1 <<  6 ]
set AT91C_PB6_TIOB1    $AT91C_PIO_PB6
set AT91C_PB6_D15      $AT91C_PIO_PB6
set AT91C_PIO_PB7        [expr 1 <<  7 ]
set AT91C_PB7_RTS0     $AT91C_PIO_PB7
set AT91C_PB7_A0_NBS0  $AT91C_PIO_PB7
set AT91C_PIO_PB8        [expr 1 <<  8 ]
set AT91C_PB8_CTS0     $AT91C_PIO_PB8
set AT91C_PB8_A1       $AT91C_PIO_PB8
set AT91C_PIO_PB9        [expr 1 <<  9 ]
set AT91C_PB9_D0       $AT91C_PIO_PB9
set AT91C_PB9_DTR0     $AT91C_PIO_PB9
set AT91C_PIO_PC0        [expr 1 <<  0 ]
set AT91C_PC0_A2       $AT91C_PIO_PC0
set AT91C_PIO_PC1        [expr 1 <<  1 ]
set AT91C_PC1_A3       $AT91C_PIO_PC1
set AT91C_PIO_PC10       [expr 1 << 10 ]
set AT91C_PC10_A12      $AT91C_PIO_PC10
set AT91C_PC10_CTS3     $AT91C_PIO_PC10
set AT91C_PIO_PC11       [expr 1 << 11 ]
set AT91C_PC11_A13      $AT91C_PIO_PC11
set AT91C_PC11_RTS3     $AT91C_PIO_PC11
set AT91C_PIO_PC12       [expr 1 << 12 ]
set AT91C_PC12_NCS1     $AT91C_PIO_PC12
set AT91C_PC12_TXD3     $AT91C_PIO_PC12
set AT91C_PIO_PC13       [expr 1 << 13 ]
set AT91C_PC13_A2       $AT91C_PIO_PC13
set AT91C_PC13_RXD3     $AT91C_PIO_PC13
set AT91C_PIO_PC14       [expr 1 << 14 ]
set AT91C_PC14_A3       $AT91C_PIO_PC14
set AT91C_PC14_SPI0_NPCS2 $AT91C_PIO_PC14
set AT91C_PIO_PC15       [expr 1 << 15 ]
set AT91C_PC15_NWR1_NBS1 $AT91C_PIO_PC15
set AT91C_PIO_PC16       [expr 1 << 16 ]
set AT91C_PC16_NCS2     $AT91C_PIO_PC16
set AT91C_PC16_PWML3    $AT91C_PIO_PC16
set AT91C_PIO_PC17       [expr 1 << 17 ]
set AT91C_PC17_NCS3     $AT91C_PIO_PC17
set AT91C_PC17_A24      $AT91C_PIO_PC17
set AT91C_PIO_PC18       [expr 1 << 18 ]
set AT91C_PC18_NWAIT    $AT91C_PIO_PC18
set AT91C_PIO_PC19       [expr 1 << 19 ]
set AT91C_PC19_SCK3     $AT91C_PIO_PC19
set AT91C_PC19_NPCS1    $AT91C_PIO_PC19
set AT91C_PIO_PC2        [expr 1 <<  2 ]
set AT91C_PC2_A4       $AT91C_PIO_PC2
set AT91C_PIO_PC20       [expr 1 << 20 ]
set AT91C_PC20_A14      $AT91C_PIO_PC20
set AT91C_PIO_PC21       [expr 1 << 21 ]
set AT91C_PC21_A15      $AT91C_PIO_PC21
set AT91C_PIO_PC22       [expr 1 << 22 ]
set AT91C_PC22_A16      $AT91C_PIO_PC22
set AT91C_PIO_PC23       [expr 1 << 23 ]
set AT91C_PC23_A17      $AT91C_PIO_PC23
set AT91C_PIO_PC24       [expr 1 << 24 ]
set AT91C_PC24_A18      $AT91C_PIO_PC24
set AT91C_PC24_PWMH0    $AT91C_PIO_PC24
set AT91C_PIO_PC25       [expr 1 << 25 ]
set AT91C_PC25_A19      $AT91C_PIO_PC25
set AT91C_PC25_PWMH1    $AT91C_PIO_PC25
set AT91C_PIO_PC26       [expr 1 << 26 ]
set AT91C_PC26_A20      $AT91C_PIO_PC26
set AT91C_PC26_PWMH2    $AT91C_PIO_PC26
set AT91C_PIO_PC27       [expr 1 << 27 ]
set AT91C_PC27_A23      $AT91C_PIO_PC27
set AT91C_PC27_PWMH3    $AT91C_PIO_PC27
set AT91C_PIO_PC28       [expr 1 << 28 ]
set AT91C_PC28_A24      $AT91C_PIO_PC28
set AT91C_PC28_MCI0_DA4 $AT91C_PIO_PC28
set AT91C_PIO_PC29       [expr 1 << 29 ]
set AT91C_PC29_PWML0    $AT91C_PIO_PC29
set AT91C_PC29_MCI0_DA5 $AT91C_PIO_PC29
set AT91C_PIO_PC3        [expr 1 <<  3 ]
set AT91C_PC3_A5       $AT91C_PIO_PC3
set AT91C_PC3_SPI0_NPCS1 $AT91C_PIO_PC3
set AT91C_PIO_PC30       [expr 1 << 30 ]
set AT91C_PC30_PWML1    $AT91C_PIO_PC30
set AT91C_PC30_MCI0_DA6 $AT91C_PIO_PC30
set AT91C_PIO_PC31       [expr 1 << 31 ]
set AT91C_PC31_PWML2    $AT91C_PIO_PC31
set AT91C_PC31_MCI0_DA7 $AT91C_PIO_PC31
set AT91C_PIO_PC4        [expr 1 <<  4 ]
set AT91C_PC4_A6       $AT91C_PIO_PC4
set AT91C_PC4_SPI0_NPCS2 $AT91C_PIO_PC4
set AT91C_PIO_PC5        [expr 1 <<  5 ]
set AT91C_PC5_A7       $AT91C_PIO_PC5
set AT91C_PC5_SPI0_NPCS3 $AT91C_PIO_PC5
set AT91C_PIO_PC6        [expr 1 <<  6 ]
set AT91C_PC6_A8       $AT91C_PIO_PC6
set AT91C_PC6_PWML0    $AT91C_PIO_PC6
set AT91C_PIO_PC7        [expr 1 <<  7 ]
set AT91C_PC7_A9       $AT91C_PIO_PC7
set AT91C_PC7_PWML1    $AT91C_PIO_PC7
set AT91C_PIO_PC8        [expr 1 <<  8 ]
set AT91C_PC8_A10      $AT91C_PIO_PC8
set AT91C_PC8_PWML2    $AT91C_PIO_PC8
set AT91C_PIO_PC9        [expr 1 <<  9 ]
set AT91C_PC9_A11      $AT91C_PIO_PC9
set AT91C_PC9_PWML3    $AT91C_PIO_PC9

# *****************************************************************************
#               MEMORY MAPPING DEFINITIONS FOR AT91SAM3UE256
# *****************************************************************************
set AT91C_ITCM 	 0x00100000
set AT91C_ITCM_SIZE	 0x00010000
set AT91C_DTCM 	 0x00200000
set AT91C_DTCM_SIZE	 0x00010000
set AT91C_IRAM 	 0x20000000
set AT91C_IRAM_SIZE	 0x00010000
set AT91C_IRAM_MIN	 0x00300000
set AT91C_IRAM_MIN_SIZE	 0x00004000
set AT91C_IROM 	 0x00180000
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
#               ATTRIBUTES DEFINITIONS FOR AT91SAM3UE256
# *****************************************************************************
array set AT91SAM3UE256_att {
	HDMA_CH 	{ LP 	HDMA_CH_0_att 	HDMA_CH_1_att 	HDMA_CH_2_att 	HDMA_CH_3_att }
	RSTC 	{ LP 	RSTC_att }
	EFC 	{ LP 	EFC0_att 	EFC1_att }
	SSC 	{ LP 	SSC0_att }
	WDTC 	{ LP 	WDTC_att }
	CKGR 	{ LP 	CKGR_att }
	TWI 	{ LP 	TWI0_att 	TWI1_att }
	HDMA 	{ LP 	HDMA_att }
	HMATRIX2 	{ LP 	MATRIX_att }
	HSMC4 	{ LP 	HSMC4_att }
	RTTC 	{ LP 	RTTC_att }
	RTC 	{ LP 	RTC_att }
	TC 	{ LP 	TC0_att 	TC1_att 	TC2_att }
	SYS 	{ LP 	SYS_att }
	UDPHS_DMA 	{ LP 	UDPHS_DMA_1_att 	UDPHS_DMA_2_att 	UDPHS_DMA_3_att 	UDPHS_DMA_4_att 	UDPHS_DMA_5_att 	UDPHS_DMA_6_att }
	PIO 	{ LP 	PIOA_att 	PIOB_att 	PIOC_att }
	PWMC 	{ LP 	PWMC_att }
	PDC 	{ LP 	PDC_DBGU_att 	PDC_TWI0_att 	PDC_TWI1_att 	PDC_US0_att 	PDC_US1_att 	PDC_US2_att 	PDC_US3_att 	PDC_SSC0_att 	PDC_PWMC_att }
	HSMC4_CS 	{ LP 	HSMC4_CS0_att 	HSMC4_CS1_att 	HSMC4_CS2_att 	HSMC4_CS3_att 	HSMC4_NFC_att }
	DBGU 	{ LP 	DBGU_att }
	PMC 	{ LP 	PMC_att }
	MCI 	{ LP 	MCI0_att }
	NVIC 	{ LP 	NVIC_att }
	USART 	{ LP 	US0_att 	US1_att 	US2_att 	US3_att }
	SPI 	{ LP 	SPI0_att }
	TCB 	{ LP 	TCB0_att 	TCB1_att 	TCB2_att }
	UDPHS_EPT 	{ LP 	UDPHS_EPT_0_att 	UDPHS_EPT_1_att 	UDPHS_EPT_2_att 	UDPHS_EPT_3_att 	UDPHS_EPT_4_att 	UDPHS_EPT_5_att 	UDPHS_EPT_6_att }
	SUPC 	{ LP 	SUPC_att }
	CM3 	{ LP 	CM3_att }
	MPU 	{ LP 	MPU_att }
	ADC 	{ LP 	ADC0_att 	ADC1_att }
	PWMC_CH 	{ LP 	PWMC_CH0_att 	PWMC_CH1_att 	PWMC_CH2_att 	PWMC_CH3_att }
	UDPHS_EPTFIFO 	{ LP 	UDPHS_EPTFIFO_att }
	UDPHS 	{ LP 	UDPHS_att }

}
# ========== Peripheral attributes for HDMA_CH peripheral ========== 
array set HDMA_CH_0_att {
	CADDR 	{ R AT91C_HDMA_CH_0_CADDR 	RW }
	DADDR 	{ R AT91C_HDMA_CH_0_DADDR 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_0_BDSCR 	RW }
	CFG 	{ R AT91C_HDMA_CH_0_CFG 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_0_CTRLB 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_0_CTRLA 	RW }
	DSCR 	{ R AT91C_HDMA_CH_0_DSCR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_0_SADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_0_DPIP 	RW }
	SPIP 	{ R AT91C_HDMA_CH_0_SPIP 	RW }
	listeReg 	{ CADDR DADDR BDSCR CFG CTRLB CTRLA DSCR SADDR DPIP SPIP  }

}
array set HDMA_CH_1_att {
	DSCR 	{ R AT91C_HDMA_CH_1_DSCR 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_1_BDSCR 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_1_CTRLB 	RW }
	SPIP 	{ R AT91C_HDMA_CH_1_SPIP 	RW }
	SADDR 	{ R AT91C_HDMA_CH_1_SADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_1_DPIP 	RW }
	CFG 	{ R AT91C_HDMA_CH_1_CFG 	RW }
	DADDR 	{ R AT91C_HDMA_CH_1_DADDR 	RW }
	CADDR 	{ R AT91C_HDMA_CH_1_CADDR 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_1_CTRLA 	RW }
	listeReg 	{ DSCR BDSCR CTRLB SPIP SADDR DPIP CFG DADDR CADDR CTRLA  }

}
array set HDMA_CH_2_att {
	BDSCR 	{ R AT91C_HDMA_CH_2_BDSCR 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_2_CTRLB 	RW }
	CADDR 	{ R AT91C_HDMA_CH_2_CADDR 	RW }
	CFG 	{ R AT91C_HDMA_CH_2_CFG 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_2_CTRLA 	RW }
	SADDR 	{ R AT91C_HDMA_CH_2_SADDR 	RW }
	DPIP 	{ R AT91C_HDMA_CH_2_DPIP 	RW }
	DADDR 	{ R AT91C_HDMA_CH_2_DADDR 	RW }
	SPIP 	{ R AT91C_HDMA_CH_2_SPIP 	RW }
	DSCR 	{ R AT91C_HDMA_CH_2_DSCR 	RW }
	listeReg 	{ BDSCR CTRLB CADDR CFG CTRLA SADDR DPIP DADDR SPIP DSCR  }

}
array set HDMA_CH_3_att {
	DSCR 	{ R AT91C_HDMA_CH_3_DSCR 	RW }
	SADDR 	{ R AT91C_HDMA_CH_3_SADDR 	RW }
	BDSCR 	{ R AT91C_HDMA_CH_3_BDSCR 	RW }
	CTRLA 	{ R AT91C_HDMA_CH_3_CTRLA 	RW }
	DPIP 	{ R AT91C_HDMA_CH_3_DPIP 	RW }
	CTRLB 	{ R AT91C_HDMA_CH_3_CTRLB 	RW }
	SPIP 	{ R AT91C_HDMA_CH_3_SPIP 	RW }
	CFG 	{ R AT91C_HDMA_CH_3_CFG 	RW }
	CADDR 	{ R AT91C_HDMA_CH_3_CADDR 	RW }
	DADDR 	{ R AT91C_HDMA_CH_3_DADDR 	RW }
	listeReg 	{ DSCR SADDR BDSCR CTRLA DPIP CTRLB SPIP CFG CADDR DADDR  }

}

# ========== Peripheral attributes for RSTC peripheral ========== 
array set RSTC_att {
	VER 	{ R AT91C_RSTC_VER 	RW }
	RCR 	{ R AT91C_RSTC_RCR 	WO }
	RMR 	{ R AT91C_RSTC_RMR 	RW }
	RSR 	{ R AT91C_RSTC_RSR 	RO }
	listeReg 	{ VER RCR RMR RSR  }

}

# ========== Peripheral attributes for EFC peripheral ========== 
array set EFC0_att {
	FCR 	{ R AT91C_EFC0_FCR 	WO }
	FRR 	{ R AT91C_EFC0_FRR 	RO }
	FMR 	{ R AT91C_EFC0_FMR 	RW }
	FSR 	{ R AT91C_EFC0_FSR 	RO }
	FVR 	{ R AT91C_EFC0_FVR 	RO }
	listeReg 	{ FCR FRR FMR FSR FVR  }

}
array set EFC1_att {
	FMR 	{ R AT91C_EFC1_FMR 	RW }
	FVR 	{ R AT91C_EFC1_FVR 	RO }
	FSR 	{ R AT91C_EFC1_FSR 	RO }
	FCR 	{ R AT91C_EFC1_FCR 	WO }
	FRR 	{ R AT91C_EFC1_FRR 	RO }
	listeReg 	{ FMR FVR FSR FCR FRR  }

}

# ========== Peripheral attributes for SSC peripheral ========== 
array set SSC0_att {
	FEATURES 	{ R AT91C_SSC0_FEATURES 	RW }
	IPNAME1 	{ R AT91C_SSC0_IPNAME1 	RW }
	CR 	{ R AT91C_SSC0_CR 	WO }
	ADDRSIZE 	{ R AT91C_SSC0_ADDRSIZE 	RW }
	RHR 	{ R AT91C_SSC0_RHR 	RO }
	VER 	{ R AT91C_SSC0_VER 	RO }
	TSHR 	{ R AT91C_SSC0_TSHR 	RW }
	RFMR 	{ R AT91C_SSC0_RFMR 	RW }
	IDR 	{ R AT91C_SSC0_IDR 	WO }
	TFMR 	{ R AT91C_SSC0_TFMR 	RW }
	RSHR 	{ R AT91C_SSC0_RSHR 	RO }
	TCMR 	{ R AT91C_SSC0_TCMR 	RW }
	RCMR 	{ R AT91C_SSC0_RCMR 	RW }
	SR 	{ R AT91C_SSC0_SR 	RO }
	IPNAME2 	{ R AT91C_SSC0_IPNAME2 	RW }
	THR 	{ R AT91C_SSC0_THR 	WO }
	CMR 	{ R AT91C_SSC0_CMR 	RW }
	IER 	{ R AT91C_SSC0_IER 	WO }
	IMR 	{ R AT91C_SSC0_IMR 	RO }
	listeReg 	{ FEATURES IPNAME1 CR ADDRSIZE RHR VER TSHR RFMR IDR TFMR RSHR TCMR RCMR SR IPNAME2 THR CMR IER IMR  }

}

# ========== Peripheral attributes for WDTC peripheral ========== 
array set WDTC_att {
	WDSR 	{ R AT91C_WDTC_WDSR 	RO }
	WDMR 	{ R AT91C_WDTC_WDMR 	RW }
	WDCR 	{ R AT91C_WDTC_WDCR 	WO }
	listeReg 	{ WDSR WDMR WDCR  }

}

# ========== Peripheral attributes for CKGR peripheral ========== 
array set CKGR_att {
	PLLAR 	{ R AT91C_CKGR_PLLAR 	RW }
	UCKR 	{ R AT91C_CKGR_UCKR 	RW }
	MOR 	{ R AT91C_CKGR_MOR 	RW }
	MCFR 	{ R AT91C_CKGR_MCFR 	RO }
	listeReg 	{ PLLAR UCKR MOR MCFR  }

}

# ========== Peripheral attributes for TWI peripheral ========== 
array set TWI0_att {
	FEATURES 	{ R AT91C_TWI0_FEATURES 	RW }
	IPNAME1 	{ R AT91C_TWI0_IPNAME1 	RW }
	SMR 	{ R AT91C_TWI0_SMR 	RW }
	MMR 	{ R AT91C_TWI0_MMR 	RW }
	SR 	{ R AT91C_TWI0_SR 	RO }
	IPNAME2 	{ R AT91C_TWI0_IPNAME2 	RW }
	CR 	{ R AT91C_TWI0_CR 	WO }
	IER 	{ R AT91C_TWI0_IER 	WO }
	RHR 	{ R AT91C_TWI0_RHR 	RO }
	ADDRSIZE 	{ R AT91C_TWI0_ADDRSIZE 	RW }
	THR 	{ R AT91C_TWI0_THR 	WO }
	VER 	{ R AT91C_TWI0_VER 	WO }
	IADR 	{ R AT91C_TWI0_IADR 	RW }
	IMR 	{ R AT91C_TWI0_IMR 	RO }
	CWGR 	{ R AT91C_TWI0_CWGR 	RW }
	IDR 	{ R AT91C_TWI0_IDR 	WO }
	listeReg 	{ FEATURES IPNAME1 SMR MMR SR IPNAME2 CR IER RHR ADDRSIZE THR VER IADR IMR CWGR IDR  }

}
array set TWI1_att {
	VER 	{ R AT91C_TWI1_VER 	WO }
	IDR 	{ R AT91C_TWI1_IDR 	WO }
	IPNAME2 	{ R AT91C_TWI1_IPNAME2 	RW }
	CWGR 	{ R AT91C_TWI1_CWGR 	RW }
	CR 	{ R AT91C_TWI1_CR 	WO }
	ADDRSIZE 	{ R AT91C_TWI1_ADDRSIZE 	RW }
	IADR 	{ R AT91C_TWI1_IADR 	RW }
	IER 	{ R AT91C_TWI1_IER 	WO }
	SMR 	{ R AT91C_TWI1_SMR 	RW }
	RHR 	{ R AT91C_TWI1_RHR 	RO }
	FEATURES 	{ R AT91C_TWI1_FEATURES 	RW }
	IMR 	{ R AT91C_TWI1_IMR 	RO }
	SR 	{ R AT91C_TWI1_SR 	RO }
	THR 	{ R AT91C_TWI1_THR 	WO }
	MMR 	{ R AT91C_TWI1_MMR 	RW }
	IPNAME1 	{ R AT91C_TWI1_IPNAME1 	RW }
	listeReg 	{ VER IDR IPNAME2 CWGR CR ADDRSIZE IADR IER SMR RHR FEATURES IMR SR THR MMR IPNAME1  }

}

# ========== Peripheral attributes for HDMA peripheral ========== 
array set HDMA_att {
	SYNC 	{ R AT91C_HDMA_SYNC 	RW }
	VER 	{ R AT91C_HDMA_VER 	 }
	RSVD0 	{ R AT91C_HDMA_RSVD0 	WO }
	CHSR 	{ R AT91C_HDMA_CHSR 	RO }
	IPNAME2 	{ R AT91C_HDMA_IPNAME2 	RW }
	EBCIMR 	{ R AT91C_HDMA_EBCIMR 	RO }
	CHDR 	{ R AT91C_HDMA_CHDR 	WO }
	EN 	{ R AT91C_HDMA_EN 	RW }
	GCFG 	{ R AT91C_HDMA_GCFG 	RW }
	IPNAME1 	{ R AT91C_HDMA_IPNAME1 	RW }
	LAST 	{ R AT91C_HDMA_LAST 	RW }
	FEATURES 	{ R AT91C_HDMA_FEATURES 	RW }
	CREQ 	{ R AT91C_HDMA_CREQ 	RW }
	EBCIER 	{ R AT91C_HDMA_EBCIER 	WO }
	CHER 	{ R AT91C_HDMA_CHER 	WO }
	ADDRSIZE 	{ R AT91C_HDMA_ADDRSIZE 	RW }
	EBCISR 	{ R AT91C_HDMA_EBCISR 	RO }
	SREQ 	{ R AT91C_HDMA_SREQ 	RW }
	EBCIDR 	{ R AT91C_HDMA_EBCIDR 	WO }
	RSVD1 	{ R AT91C_HDMA_RSVD1 	WO }
	listeReg 	{ SYNC VER RSVD0 CHSR IPNAME2 EBCIMR CHDR EN GCFG IPNAME1 LAST FEATURES CREQ EBCIER CHER ADDRSIZE EBCISR SREQ EBCIDR RSVD1  }

}

# ========== Peripheral attributes for HMATRIX2 peripheral ========== 
array set MATRIX_att {
	SCFG6 	{ R AT91C_MATRIX_SCFG6 	RW }
	SCFG8 	{ R AT91C_MATRIX_SCFG8 	RW }
	MCFG2 	{ R AT91C_MATRIX_MCFG2 	RW }
	MCFG7 	{ R AT91C_MATRIX_MCFG7 	RW }
	SCFG3 	{ R AT91C_MATRIX_SCFG3 	RW }
	SCFG0 	{ R AT91C_MATRIX_SCFG0 	RW }
	IPNAME2 	{ R AT91C_MATRIX_IPNAME2 	RW }
	ADDRSIZE 	{ R AT91C_MATRIX_ADDRSIZE 	RW }
	MCFG5 	{ R AT91C_MATRIX_MCFG5 	RW }
	MCFG3 	{ R AT91C_MATRIX_MCFG3 	RW }
	SCFG4 	{ R AT91C_MATRIX_SCFG4 	RW }
	MCFG1 	{ R AT91C_MATRIX_MCFG1 	RW }
	SCFG1 	{ R AT91C_MATRIX_SCFG1 	RW }
	SCFG7 	{ R AT91C_MATRIX_SCFG7 	RW }
	VER 	{ R AT91C_MATRIX_VER 	RW }
	SCFG2 	{ R AT91C_MATRIX_SCFG2 	RW }
	IPNAME1 	{ R AT91C_MATRIX_IPNAME1 	RW }
	MCFG4 	{ R AT91C_MATRIX_MCFG4 	RW }
	FEATURES 	{ R AT91C_MATRIX_FEATURES 	RW }
	MCFG6 	{ R AT91C_MATRIX_MCFG6 	RW }
	SCFG5 	{ R AT91C_MATRIX_SCFG5 	RW }
	MCFG0 	{ R AT91C_MATRIX_MCFG0 	RW }
	listeReg 	{ SCFG6 SCFG8 MCFG2 MCFG7 SCFG3 SCFG0 IPNAME2 ADDRSIZE MCFG5 MCFG3 SCFG4 MCFG1 SCFG1 SCFG7 VER SCFG2 IPNAME1 MCFG4 FEATURES MCFG6 SCFG5 MCFG0  }

}

# ========== Peripheral attributes for HSMC4 peripheral ========== 
array set HSMC4_att {
	IPNAME1 	{ R AT91C_HSMC4_IPNAME1 	RO }
	ECCPR6 	{ R AT91C_HSMC4_ECCPR6 	RO }
	ADDRSIZE 	{ R AT91C_HSMC4_ADDRSIZE 	RO }
	ECCPR11 	{ R AT91C_HSMC4_ECCPR11 	RO }
	SR 	{ R AT91C_HSMC4_SR 	RO }
	IMR 	{ R AT91C_HSMC4_IMR 	RO }
	WPSR 	{ R AT91C_HSMC4_WPSR 	RO }
	BANK 	{ R AT91C_HSMC4_BANK 	RW }
	ECCPR8 	{ R AT91C_HSMC4_ECCPR8 	RO }
	WPCR 	{ R AT91C_HSMC4_WPCR 	W }
	ECCPR2 	{ R AT91C_HSMC4_ECCPR2 	RO }
	ECCPR1 	{ R AT91C_HSMC4_ECCPR1 	RO }
	ECCSR2 	{ R AT91C_HSMC4_ECCSR2 	RO }
	OCMS 	{ R AT91C_HSMC4_OCMS 	RW }
	ECCPR9 	{ R AT91C_HSMC4_ECCPR9 	RO }
	DUMMY 	{ R AT91C_HSMC4_DUMMY 	RW }
	ECCPR5 	{ R AT91C_HSMC4_ECCPR5 	RO }
	ECCCR 	{ R AT91C_HSMC4_ECCCR 	WO }
	KEY2 	{ R AT91C_HSMC4_KEY2 	WO }
	IER 	{ R AT91C_HSMC4_IER 	WO }
	ECCSR1 	{ R AT91C_HSMC4_ECCSR1 	RO }
	IDR 	{ R AT91C_HSMC4_IDR 	WO }
	ECCPR0 	{ R AT91C_HSMC4_ECCPR0 	RO }
	FEATURES 	{ R AT91C_HSMC4_FEATURES 	RO }
	ECCPR7 	{ R AT91C_HSMC4_ECCPR7 	RO }
	ECCPR12 	{ R AT91C_HSMC4_ECCPR12 	RO }
	ECCPR10 	{ R AT91C_HSMC4_ECCPR10 	RO }
	KEY1 	{ R AT91C_HSMC4_KEY1 	WO }
	VER 	{ R AT91C_HSMC4_VER 	RO }
	Eccpr15 	{ R AT91C_HSMC4_Eccpr15 	RO }
	ECCPR4 	{ R AT91C_HSMC4_ECCPR4 	RO }
	IPNAME2 	{ R AT91C_HSMC4_IPNAME2 	RO }
	ECCCMD 	{ R AT91C_HSMC4_ECCCMD 	RW }
	ADDR 	{ R AT91C_HSMC4_ADDR 	RW }
	ECCPR3 	{ R AT91C_HSMC4_ECCPR3 	RO }
	CFG 	{ R AT91C_HSMC4_CFG 	RW }
	CTRL 	{ R AT91C_HSMC4_CTRL 	WO }
	ECCPR13 	{ R AT91C_HSMC4_ECCPR13 	RO }
	ECCPR14 	{ R AT91C_HSMC4_ECCPR14 	RO }
	listeReg 	{ IPNAME1 ECCPR6 ADDRSIZE ECCPR11 SR IMR WPSR BANK ECCPR8 WPCR ECCPR2 ECCPR1 ECCSR2 OCMS ECCPR9 DUMMY ECCPR5 ECCCR KEY2 IER ECCSR1 IDR ECCPR0 FEATURES ECCPR7 ECCPR12 ECCPR10 KEY1 VER Eccpr15 ECCPR4 IPNAME2 ECCCMD ADDR ECCPR3 CFG CTRL ECCPR13 ECCPR14  }

}

# ========== Peripheral attributes for RTTC peripheral ========== 
array set RTTC_att {
	RTVR 	{ R AT91C_RTTC_RTVR 	RO }
	RTAR 	{ R AT91C_RTTC_RTAR 	RW }
	RTMR 	{ R AT91C_RTTC_RTMR 	RW }
	RTSR 	{ R AT91C_RTTC_RTSR 	RO }
	listeReg 	{ RTVR RTAR RTMR RTSR  }

}

# ========== Peripheral attributes for RTC peripheral ========== 
array set RTC_att {
	IMR 	{ R AT91C_RTC_IMR 	RO }
	SCCR 	{ R AT91C_RTC_SCCR 	WO }
	CALR 	{ R AT91C_RTC_CALR 	RW }
	MR 	{ R AT91C_RTC_MR 	RW }
	TIMR 	{ R AT91C_RTC_TIMR 	RW }
	CALALR 	{ R AT91C_RTC_CALALR 	RW }
	VER 	{ R AT91C_RTC_VER 	RO }
	CR 	{ R AT91C_RTC_CR 	RW }
	IDR 	{ R AT91C_RTC_IDR 	WO }
	TIMALR 	{ R AT91C_RTC_TIMALR 	RW }
	IER 	{ R AT91C_RTC_IER 	WO }
	SR 	{ R AT91C_RTC_SR 	RO }
	listeReg 	{ IMR SCCR CALR MR TIMR CALALR VER CR IDR TIMALR IER SR  }

}

# ========== Peripheral attributes for TC peripheral ========== 
array set TC0_att {
	IER 	{ R AT91C_TC0_IER 	WO }
	CV 	{ R AT91C_TC0_CV 	RW }
	RA 	{ R AT91C_TC0_RA 	RW }
	RB 	{ R AT91C_TC0_RB 	RW }
	IDR 	{ R AT91C_TC0_IDR 	WO }
	SR 	{ R AT91C_TC0_SR 	RO }
	IMR 	{ R AT91C_TC0_IMR 	RO }
	CMR 	{ R AT91C_TC0_CMR 	RW }
	RC 	{ R AT91C_TC0_RC 	RW }
	CCR 	{ R AT91C_TC0_CCR 	WO }
	listeReg 	{ IER CV RA RB IDR SR IMR CMR RC CCR  }

}
array set TC1_att {
	SR 	{ R AT91C_TC1_SR 	RO }
	RA 	{ R AT91C_TC1_RA 	RW }
	IER 	{ R AT91C_TC1_IER 	WO }
	RB 	{ R AT91C_TC1_RB 	RW }
	IDR 	{ R AT91C_TC1_IDR 	WO }
	CCR 	{ R AT91C_TC1_CCR 	WO }
	IMR 	{ R AT91C_TC1_IMR 	RO }
	RC 	{ R AT91C_TC1_RC 	RW }
	CMR 	{ R AT91C_TC1_CMR 	RW }
	CV 	{ R AT91C_TC1_CV 	RW }
	listeReg 	{ SR RA IER RB IDR CCR IMR RC CMR CV  }

}
array set TC2_att {
	RA 	{ R AT91C_TC2_RA 	RW }
	RB 	{ R AT91C_TC2_RB 	RW }
	CMR 	{ R AT91C_TC2_CMR 	RW }
	SR 	{ R AT91C_TC2_SR 	RO }
	CCR 	{ R AT91C_TC2_CCR 	WO }
	IMR 	{ R AT91C_TC2_IMR 	RO }
	CV 	{ R AT91C_TC2_CV 	RW }
	RC 	{ R AT91C_TC2_RC 	RW }
	IER 	{ R AT91C_TC2_IER 	WO }
	IDR 	{ R AT91C_TC2_IDR 	WO }
	listeReg 	{ RA RB CMR SR CCR IMR CV RC IER IDR  }

}

# ========== Peripheral attributes for SYS peripheral ========== 
array set SYS_att {
	GPBR 	{ R AT91C_SYS_GPBR 	  8 }
	listeReg 	{ GPBR  }

}

# ========== Peripheral attributes for UDPHS_DMA peripheral ========== 
array set UDPHS_DMA_1_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_1_DMASTATUS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_1_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_1_DMANXTDSC 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_1_DMAADDRESS 	RW }
	listeReg 	{ DMASTATUS DMACONTROL DMANXTDSC DMAADDRESS  }

}
array set UDPHS_DMA_2_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_2_DMASTATUS 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_2_DMANXTDSC 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_2_DMACONTROL 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_2_DMAADDRESS 	RW }
	listeReg 	{ DMASTATUS DMANXTDSC DMACONTROL DMAADDRESS  }

}
array set UDPHS_DMA_3_att {
	DMACONTROL 	{ R AT91C_UDPHS_DMA_3_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_3_DMANXTDSC 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_3_DMASTATUS 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_3_DMAADDRESS 	RW }
	listeReg 	{ DMACONTROL DMANXTDSC DMASTATUS DMAADDRESS  }

}
array set UDPHS_DMA_4_att {
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_4_DMAADDRESS 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_4_DMANXTDSC 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_4_DMASTATUS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_4_DMACONTROL 	RW }
	listeReg 	{ DMAADDRESS DMANXTDSC DMASTATUS DMACONTROL  }

}
array set UDPHS_DMA_5_att {
	DMACONTROL 	{ R AT91C_UDPHS_DMA_5_DMACONTROL 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_5_DMAADDRESS 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_5_DMANXTDSC 	RW }
	DMASTATUS 	{ R AT91C_UDPHS_DMA_5_DMASTATUS 	RW }
	listeReg 	{ DMACONTROL DMAADDRESS DMANXTDSC DMASTATUS  }

}
array set UDPHS_DMA_6_att {
	DMASTATUS 	{ R AT91C_UDPHS_DMA_6_DMASTATUS 	RW }
	DMACONTROL 	{ R AT91C_UDPHS_DMA_6_DMACONTROL 	RW }
	DMANXTDSC 	{ R AT91C_UDPHS_DMA_6_DMANXTDSC 	RW }
	DMAADDRESS 	{ R AT91C_UDPHS_DMA_6_DMAADDRESS 	RW }
	listeReg 	{ DMASTATUS DMACONTROL DMANXTDSC DMAADDRESS  }

}

# ========== Peripheral attributes for PIO peripheral ========== 
array set PIOA_att {
	PDR 	{ R AT91C_PIOA_PDR 	WO }
	ABSR 	{ R AT91C_PIOA_ABSR 	RO }
	IFSR 	{ R AT91C_PIOA_IFSR 	RO }
	ODR 	{ R AT91C_PIOA_ODR 	WO }
	PER 	{ R AT91C_PIOA_PER 	WO }
	FEATURES 	{ R AT91C_PIOA_FEATURES 	RW }
	VER 	{ R AT91C_PIOA_VER 	RW }
	OWSR 	{ R AT91C_PIOA_OWSR 	RO }
	IMR 	{ R AT91C_PIOA_IMR 	RO }
	OWDR 	{ R AT91C_PIOA_OWDR 	WO }
	MDSR 	{ R AT91C_PIOA_MDSR 	RO }
	IFDR 	{ R AT91C_PIOA_IFDR 	WO }
	CODR 	{ R AT91C_PIOA_CODR 	WO }
	ISR 	{ R AT91C_PIOA_ISR 	RO }
	PPUDR 	{ R AT91C_PIOA_PPUDR 	WO }
	IPNAME2 	{ R AT91C_PIOA_IPNAME2 	RW }
	MDDR 	{ R AT91C_PIOA_MDDR 	WO }
	PSR 	{ R AT91C_PIOA_PSR 	RO }
	PDSR 	{ R AT91C_PIOA_PDSR 	RO }
	PPUSR 	{ R AT91C_PIOA_PPUSR 	RO }
	OER 	{ R AT91C_PIOA_OER 	WO }
	OSR 	{ R AT91C_PIOA_OSR 	RO }
	IER 	{ R AT91C_PIOA_IER 	WO }
	PPUER 	{ R AT91C_PIOA_PPUER 	WO }
	ABMR 	{ R AT91C_PIOA_ABMR 	WO }
	ADDRSIZE 	{ R AT91C_PIOA_ADDRSIZE 	RW }
	MDER 	{ R AT91C_PIOA_MDER 	WO }
	IFER 	{ R AT91C_PIOA_IFER 	WO }
	IPNAME1 	{ R AT91C_PIOA_IPNAME1 	RW }
	IDR 	{ R AT91C_PIOA_IDR 	WO }
	OWER 	{ R AT91C_PIOA_OWER 	WO }
	ODSR 	{ R AT91C_PIOA_ODSR 	RO }
	SODR 	{ R AT91C_PIOA_SODR 	WO }
	listeReg 	{ PDR ABSR IFSR ODR PER FEATURES VER OWSR IMR OWDR MDSR IFDR CODR ISR PPUDR IPNAME2 MDDR PSR PDSR PPUSR OER OSR IER PPUER ABMR ADDRSIZE MDER IFER IPNAME1 IDR OWER ODSR SODR  }

}
array set PIOB_att {
	OWSR 	{ R AT91C_PIOB_OWSR 	RO }
	PSR 	{ R AT91C_PIOB_PSR 	RO }
	MDER 	{ R AT91C_PIOB_MDER 	WO }
	IPNAME1 	{ R AT91C_PIOB_IPNAME1 	RW }
	FEATURES 	{ R AT91C_PIOB_FEATURES 	RW }
	ODR 	{ R AT91C_PIOB_ODR 	WO }
	IDR 	{ R AT91C_PIOB_IDR 	WO }
	PDR 	{ R AT91C_PIOB_PDR 	WO }
	PDSR 	{ R AT91C_PIOB_PDSR 	RO }
	PPUDR 	{ R AT91C_PIOB_PPUDR 	WO }
	OWDR 	{ R AT91C_PIOB_OWDR 	WO }
	ADDRSIZE 	{ R AT91C_PIOB_ADDRSIZE 	RW }
	IFER 	{ R AT91C_PIOB_IFER 	WO }
	ABMR 	{ R AT91C_PIOB_ABMR 	WO }
	VER 	{ R AT91C_PIOB_VER 	RW }
	PER 	{ R AT91C_PIOB_PER 	WO }
	IMR 	{ R AT91C_PIOB_IMR 	RO }
	PPUSR 	{ R AT91C_PIOB_PPUSR 	RO }
	ODSR 	{ R AT91C_PIOB_ODSR 	RO }
	IFDR 	{ R AT91C_PIOB_IFDR 	WO }
	SODR 	{ R AT91C_PIOB_SODR 	WO }
	IER 	{ R AT91C_PIOB_IER 	WO }
	MDSR 	{ R AT91C_PIOB_MDSR 	RO }
	ISR 	{ R AT91C_PIOB_ISR 	RO }
	IFSR 	{ R AT91C_PIOB_IFSR 	RO }
	PPUER 	{ R AT91C_PIOB_PPUER 	WO }
	OWER 	{ R AT91C_PIOB_OWER 	WO }
	IPNAME2 	{ R AT91C_PIOB_IPNAME2 	RW }
	MDDR 	{ R AT91C_PIOB_MDDR 	WO }
	CODR 	{ R AT91C_PIOB_CODR 	WO }
	OER 	{ R AT91C_PIOB_OER 	WO }
	OSR 	{ R AT91C_PIOB_OSR 	RO }
	ABSR 	{ R AT91C_PIOB_ABSR 	RO }
	listeReg 	{ OWSR PSR MDER IPNAME1 FEATURES ODR IDR PDR PDSR PPUDR OWDR ADDRSIZE IFER ABMR VER PER IMR PPUSR ODSR IFDR SODR IER MDSR ISR IFSR PPUER OWER IPNAME2 MDDR CODR OER OSR ABSR  }

}
array set PIOC_att {
	MDDR 	{ R AT91C_PIOC_MDDR 	WO }
	ABSR 	{ R AT91C_PIOC_ABSR 	RO }
	ABMR 	{ R AT91C_PIOC_ABMR 	WO }
	ODSR 	{ R AT91C_PIOC_ODSR 	RO }
	OSR 	{ R AT91C_PIOC_OSR 	RO }
	IFER 	{ R AT91C_PIOC_IFER 	WO }
	MDSR 	{ R AT91C_PIOC_MDSR 	RO }
	IFDR 	{ R AT91C_PIOC_IFDR 	WO }
	MDER 	{ R AT91C_PIOC_MDER 	WO }
	IER 	{ R AT91C_PIOC_IER 	WO }
	OWDR 	{ R AT91C_PIOC_OWDR 	WO }
	IFSR 	{ R AT91C_PIOC_IFSR 	RO }
	ISR 	{ R AT91C_PIOC_ISR 	RO }
	PPUDR 	{ R AT91C_PIOC_PPUDR 	WO }
	PDSR 	{ R AT91C_PIOC_PDSR 	RO }
	IPNAME2 	{ R AT91C_PIOC_IPNAME2 	RW }
	PPUER 	{ R AT91C_PIOC_PPUER 	WO }
	OER 	{ R AT91C_PIOC_OER 	WO }
	CODR 	{ R AT91C_PIOC_CODR 	WO }
	OWER 	{ R AT91C_PIOC_OWER 	WO }
	VER 	{ R AT91C_PIOC_VER 	RW }
	IMR 	{ R AT91C_PIOC_IMR 	RO }
	PPUSR 	{ R AT91C_PIOC_PPUSR 	RO }
	ADDRSIZE 	{ R AT91C_PIOC_ADDRSIZE 	RW }
	IPNAME1 	{ R AT91C_PIOC_IPNAME1 	RW }
	IDR 	{ R AT91C_PIOC_IDR 	WO }
	SODR 	{ R AT91C_PIOC_SODR 	WO }
	PSR 	{ R AT91C_PIOC_PSR 	RO }
	ODR 	{ R AT91C_PIOC_ODR 	WO }
	OWSR 	{ R AT91C_PIOC_OWSR 	RO }
	FEATURES 	{ R AT91C_PIOC_FEATURES 	RW }
	PDR 	{ R AT91C_PIOC_PDR 	WO }
	PER 	{ R AT91C_PIOC_PER 	WO }
	listeReg 	{ MDDR ABSR ABMR ODSR OSR IFER MDSR IFDR MDER IER OWDR IFSR ISR PPUDR PDSR IPNAME2 PPUER OER CODR OWER VER IMR PPUSR ADDRSIZE IPNAME1 IDR SODR PSR ODR OWSR FEATURES PDR PER  }

}

# ========== Peripheral attributes for PWMC peripheral ========== 
array set PWMC_att {
	CMP6MUPD 	{ R AT91C_PWMC_CMP6MUPD 	WO }
	ISR1 	{ R AT91C_PWMC_ISR1 	RO }
	CMP5V 	{ R AT91C_PWMC_CMP5V 	RW }
	CMP4MUPD 	{ R AT91C_PWMC_CMP4MUPD 	WO }
	FMR 	{ R AT91C_PWMC_FMR 	RW }
	CMP6V 	{ R AT91C_PWMC_CMP6V 	RW }
	EL4MR 	{ R AT91C_PWMC_EL4MR 	RW }
	UPCR 	{ R AT91C_PWMC_UPCR 	RW }
	CMP1VUPD 	{ R AT91C_PWMC_CMP1VUPD 	WO }
	CMP0M 	{ R AT91C_PWMC_CMP0M 	RW }
	CMP5VUPD 	{ R AT91C_PWMC_CMP5VUPD 	WO }
	FPER3 	{ R AT91C_PWMC_FPER3 	RW }
	OSCUPD 	{ R AT91C_PWMC_OSCUPD 	WO }
	FPER1 	{ R AT91C_PWMC_FPER1 	RW }
	SCUPUPD 	{ R AT91C_PWMC_SCUPUPD 	WO }
	DIS 	{ R AT91C_PWMC_DIS 	WO }
	IER1 	{ R AT91C_PWMC_IER1 	WO }
	IMR2 	{ R AT91C_PWMC_IMR2 	RO }
	CMP0V 	{ R AT91C_PWMC_CMP0V 	RW }
	SR 	{ R AT91C_PWMC_SR 	RO }
	CMP4M 	{ R AT91C_PWMC_CMP4M 	RW }
	CMP3M 	{ R AT91C_PWMC_CMP3M 	RW }
	IER2 	{ R AT91C_PWMC_IER2 	WO }
	CMP3VUPD 	{ R AT91C_PWMC_CMP3VUPD 	WO }
	CMP2M 	{ R AT91C_PWMC_CMP2M 	RW }
	IDR2 	{ R AT91C_PWMC_IDR2 	WO }
	EL2MR 	{ R AT91C_PWMC_EL2MR 	RW }
	CMP7V 	{ R AT91C_PWMC_CMP7V 	RW }
	CMP1M 	{ R AT91C_PWMC_CMP1M 	RW }
	CMP0VUPD 	{ R AT91C_PWMC_CMP0VUPD 	WO }
	WPSR 	{ R AT91C_PWMC_WPSR 	RO }
	CMP6VUPD 	{ R AT91C_PWMC_CMP6VUPD 	WO }
	CMP1MUPD 	{ R AT91C_PWMC_CMP1MUPD 	WO }
	CMP1V 	{ R AT91C_PWMC_CMP1V 	RW }
	FCR 	{ R AT91C_PWMC_FCR 	WO }
	VER 	{ R AT91C_PWMC_VER 	RO }
	EL1MR 	{ R AT91C_PWMC_EL1MR 	RW }
	EL6MR 	{ R AT91C_PWMC_EL6MR 	RW }
	ISR2 	{ R AT91C_PWMC_ISR2 	RO }
	CMP4VUPD 	{ R AT91C_PWMC_CMP4VUPD 	WO }
	CMP5MUPD 	{ R AT91C_PWMC_CMP5MUPD 	WO }
	OS 	{ R AT91C_PWMC_OS 	RW }
	FPV 	{ R AT91C_PWMC_FPV 	RW }
	FPER2 	{ R AT91C_PWMC_FPER2 	RW }
	EL7MR 	{ R AT91C_PWMC_EL7MR 	RW }
	OSSUPD 	{ R AT91C_PWMC_OSSUPD 	WO }
	FEATURES 	{ R AT91C_PWMC_FEATURES 	RW }
	CMP2V 	{ R AT91C_PWMC_CMP2V 	RW }
	FSR 	{ R AT91C_PWMC_FSR 	RO }
	ADDRSIZE 	{ R AT91C_PWMC_ADDRSIZE 	RW }
	OSC 	{ R AT91C_PWMC_OSC 	WO }
	SCUP 	{ R AT91C_PWMC_SCUP 	RW }
	CMP7MUPD 	{ R AT91C_PWMC_CMP7MUPD 	WO }
	CMP2VUPD 	{ R AT91C_PWMC_CMP2VUPD 	WO }
	FPER4 	{ R AT91C_PWMC_FPER4 	RW }
	IMR1 	{ R AT91C_PWMC_IMR1 	RO }
	EL3MR 	{ R AT91C_PWMC_EL3MR 	RW }
	CMP3V 	{ R AT91C_PWMC_CMP3V 	RW }
	IPNAME1 	{ R AT91C_PWMC_IPNAME1 	RW }
	OSS 	{ R AT91C_PWMC_OSS 	WO }
	CMP0MUPD 	{ R AT91C_PWMC_CMP0MUPD 	WO }
	CMP2MUPD 	{ R AT91C_PWMC_CMP2MUPD 	WO }
	CMP4V 	{ R AT91C_PWMC_CMP4V 	RW }
	ENA 	{ R AT91C_PWMC_ENA 	WO }
	CMP3MUPD 	{ R AT91C_PWMC_CMP3MUPD 	WO }
	EL0MR 	{ R AT91C_PWMC_EL0MR 	RW }
	OOV 	{ R AT91C_PWMC_OOV 	RW }
	WPCR 	{ R AT91C_PWMC_WPCR 	RW }
	CMP7M 	{ R AT91C_PWMC_CMP7M 	RW }
	CMP6M 	{ R AT91C_PWMC_CMP6M 	RW }
	CMP5M 	{ R AT91C_PWMC_CMP5M 	RW }
	IPNAME2 	{ R AT91C_PWMC_IPNAME2 	RW }
	CMP7VUPD 	{ R AT91C_PWMC_CMP7VUPD 	WO }
	SYNC 	{ R AT91C_PWMC_SYNC 	RW }
	MR 	{ R AT91C_PWMC_MR 	RW }
	IDR1 	{ R AT91C_PWMC_IDR1 	WO }
	EL5MR 	{ R AT91C_PWMC_EL5MR 	RW }
	listeReg 	{ CMP6MUPD ISR1 CMP5V CMP4MUPD FMR CMP6V EL4MR UPCR CMP1VUPD CMP0M CMP5VUPD FPER3 OSCUPD FPER1 SCUPUPD DIS IER1 IMR2 CMP0V SR CMP4M CMP3M IER2 CMP3VUPD CMP2M IDR2 EL2MR CMP7V CMP1M CMP0VUPD WPSR CMP6VUPD CMP1MUPD CMP1V FCR VER EL1MR EL6MR ISR2 CMP4VUPD CMP5MUPD OS FPV FPER2 EL7MR OSSUPD FEATURES CMP2V FSR ADDRSIZE OSC SCUP CMP7MUPD CMP2VUPD FPER4 IMR1 EL3MR CMP3V IPNAME1 OSS CMP0MUPD CMP2MUPD CMP4V ENA CMP3MUPD EL0MR OOV WPCR CMP7M CMP6M CMP5M IPNAME2 CMP7VUPD SYNC MR IDR1 EL5MR  }

}

# ========== Peripheral attributes for PDC peripheral ========== 
array set PDC_DBGU_att {
	TPR 	{ R AT91C_DBGU_TPR 	RW }
	PTCR 	{ R AT91C_DBGU_PTCR 	WO }
	TNCR 	{ R AT91C_DBGU_TNCR 	RW }
	PTSR 	{ R AT91C_DBGU_PTSR 	RO }
	RNCR 	{ R AT91C_DBGU_RNCR 	RW }
	RPR 	{ R AT91C_DBGU_RPR 	RW }
	TCR 	{ R AT91C_DBGU_TCR 	RW }
	RNPR 	{ R AT91C_DBGU_RNPR 	RW }
	TNPR 	{ R AT91C_DBGU_TNPR 	RW }
	RCR 	{ R AT91C_DBGU_RCR 	RW }
	listeReg 	{ TPR PTCR TNCR PTSR RNCR RPR TCR RNPR TNPR RCR  }

}
array set PDC_TWI0_att {
	TNCR 	{ R AT91C_TWI0_TNCR 	RW }
	PTCR 	{ R AT91C_TWI0_PTCR 	WO }
	PTSR 	{ R AT91C_TWI0_PTSR 	RO }
	RCR 	{ R AT91C_TWI0_RCR 	RW }
	TNPR 	{ R AT91C_TWI0_TNPR 	RW }
	RNPR 	{ R AT91C_TWI0_RNPR 	RW }
	RPR 	{ R AT91C_TWI0_RPR 	RW }
	RNCR 	{ R AT91C_TWI0_RNCR 	RW }
	TPR 	{ R AT91C_TWI0_TPR 	RW }
	TCR 	{ R AT91C_TWI0_TCR 	RW }
	listeReg 	{ TNCR PTCR PTSR RCR TNPR RNPR RPR RNCR TPR TCR  }

}
array set PDC_TWI1_att {
	TNCR 	{ R AT91C_TWI1_TNCR 	RW }
	PTCR 	{ R AT91C_TWI1_PTCR 	WO }
	RNCR 	{ R AT91C_TWI1_RNCR 	RW }
	RCR 	{ R AT91C_TWI1_RCR 	RW }
	RPR 	{ R AT91C_TWI1_RPR 	RW }
	TNPR 	{ R AT91C_TWI1_TNPR 	RW }
	RNPR 	{ R AT91C_TWI1_RNPR 	RW }
	TCR 	{ R AT91C_TWI1_TCR 	RW }
	TPR 	{ R AT91C_TWI1_TPR 	RW }
	PTSR 	{ R AT91C_TWI1_PTSR 	RO }
	listeReg 	{ TNCR PTCR RNCR RCR RPR TNPR RNPR TCR TPR PTSR  }

}
array set PDC_US0_att {
	RNCR 	{ R AT91C_US0_RNCR 	RW }
	TNPR 	{ R AT91C_US0_TNPR 	RW }
	TPR 	{ R AT91C_US0_TPR 	RW }
	RCR 	{ R AT91C_US0_RCR 	RW }
	RNPR 	{ R AT91C_US0_RNPR 	RW }
	TNCR 	{ R AT91C_US0_TNCR 	RW }
	PTSR 	{ R AT91C_US0_PTSR 	RO }
	RPR 	{ R AT91C_US0_RPR 	RW }
	PTCR 	{ R AT91C_US0_PTCR 	WO }
	TCR 	{ R AT91C_US0_TCR 	RW }
	listeReg 	{ RNCR TNPR TPR RCR RNPR TNCR PTSR RPR PTCR TCR  }

}
array set PDC_US1_att {
	TNPR 	{ R AT91C_US1_TNPR 	RW }
	TPR 	{ R AT91C_US1_TPR 	RW }
	RNCR 	{ R AT91C_US1_RNCR 	RW }
	TNCR 	{ R AT91C_US1_TNCR 	RW }
	RNPR 	{ R AT91C_US1_RNPR 	RW }
	TCR 	{ R AT91C_US1_TCR 	RW }
	PTSR 	{ R AT91C_US1_PTSR 	RO }
	RCR 	{ R AT91C_US1_RCR 	RW }
	RPR 	{ R AT91C_US1_RPR 	RW }
	PTCR 	{ R AT91C_US1_PTCR 	WO }
	listeReg 	{ TNPR TPR RNCR TNCR RNPR TCR PTSR RCR RPR PTCR  }

}
array set PDC_US2_att {
	RPR 	{ R AT91C_US2_RPR 	RW }
	TPR 	{ R AT91C_US2_TPR 	RW }
	TCR 	{ R AT91C_US2_TCR 	RW }
	PTSR 	{ R AT91C_US2_PTSR 	RO }
	PTCR 	{ R AT91C_US2_PTCR 	WO }
	RNPR 	{ R AT91C_US2_RNPR 	RW }
	TNCR 	{ R AT91C_US2_TNCR 	RW }
	RNCR 	{ R AT91C_US2_RNCR 	RW }
	TNPR 	{ R AT91C_US2_TNPR 	RW }
	RCR 	{ R AT91C_US2_RCR 	RW }
	listeReg 	{ RPR TPR TCR PTSR PTCR RNPR TNCR RNCR TNPR RCR  }

}
array set PDC_US3_att {
	TPR 	{ R AT91C_US3_TPR 	RW }
	PTCR 	{ R AT91C_US3_PTCR 	WO }
	TCR 	{ R AT91C_US3_TCR 	RW }
	RCR 	{ R AT91C_US3_RCR 	RW }
	RNCR 	{ R AT91C_US3_RNCR 	RW }
	RNPR 	{ R AT91C_US3_RNPR 	RW }
	RPR 	{ R AT91C_US3_RPR 	RW }
	PTSR 	{ R AT91C_US3_PTSR 	RO }
	TNCR 	{ R AT91C_US3_TNCR 	RW }
	TNPR 	{ R AT91C_US3_TNPR 	RW }
	listeReg 	{ TPR PTCR TCR RCR RNCR RNPR RPR PTSR TNCR TNPR  }

}
array set PDC_SSC0_att {
	RNCR 	{ R AT91C_SSC0_RNCR 	RW }
	TPR 	{ R AT91C_SSC0_TPR 	RW }
	TCR 	{ R AT91C_SSC0_TCR 	RW }
	PTCR 	{ R AT91C_SSC0_PTCR 	WO }
	TNPR 	{ R AT91C_SSC0_TNPR 	RW }
	RPR 	{ R AT91C_SSC0_RPR 	RW }
	TNCR 	{ R AT91C_SSC0_TNCR 	RW }
	RNPR 	{ R AT91C_SSC0_RNPR 	RW }
	RCR 	{ R AT91C_SSC0_RCR 	RW }
	PTSR 	{ R AT91C_SSC0_PTSR 	RO }
	listeReg 	{ RNCR TPR TCR PTCR TNPR RPR TNCR RNPR RCR PTSR  }

}
array set PDC_PWMC_att {
	TNCR 	{ R AT91C_PWMC_TNCR 	RW }
	TPR 	{ R AT91C_PWMC_TPR 	RW }
	RPR 	{ R AT91C_PWMC_RPR 	RW }
	TCR 	{ R AT91C_PWMC_TCR 	RW }
	PTSR 	{ R AT91C_PWMC_PTSR 	RO }
	RNPR 	{ R AT91C_PWMC_RNPR 	RW }
	RCR 	{ R AT91C_PWMC_RCR 	RW }
	RNCR 	{ R AT91C_PWMC_RNCR 	RW }
	PTCR 	{ R AT91C_PWMC_PTCR 	WO }
	TNPR 	{ R AT91C_PWMC_TNPR 	RW }
	listeReg 	{ TNCR TPR RPR TCR PTSR RNPR RCR RNCR PTCR TNPR  }

}

# ========== Peripheral attributes for HSMC4_CS peripheral ========== 
array set HSMC4_CS0_att {
	MODE 	{ R AT91C_CS0_MODE 	RW }
	PULSE 	{ R AT91C_CS0_PULSE 	RW }
	CYCLE 	{ R AT91C_CS0_CYCLE 	RW }
	TIMINGS 	{ R AT91C_CS0_TIMINGS 	RW }
	SETUP 	{ R AT91C_CS0_SETUP 	RW }
	listeReg 	{ MODE PULSE CYCLE TIMINGS SETUP  }

}
array set HSMC4_CS1_att {
	CYCLE 	{ R AT91C_CS1_CYCLE 	RW }
	PULSE 	{ R AT91C_CS1_PULSE 	RW }
	MODE 	{ R AT91C_CS1_MODE 	RW }
	SETUP 	{ R AT91C_CS1_SETUP 	RW }
	TIMINGS 	{ R AT91C_CS1_TIMINGS 	RW }
	listeReg 	{ CYCLE PULSE MODE SETUP TIMINGS  }

}
array set HSMC4_CS2_att {
	PULSE 	{ R AT91C_CS2_PULSE 	RW }
	TIMINGS 	{ R AT91C_CS2_TIMINGS 	RW }
	CYCLE 	{ R AT91C_CS2_CYCLE 	RW }
	MODE 	{ R AT91C_CS2_MODE 	RW }
	SETUP 	{ R AT91C_CS2_SETUP 	RW }
	listeReg 	{ PULSE TIMINGS CYCLE MODE SETUP  }

}
array set HSMC4_CS3_att {
	MODE 	{ R AT91C_CS3_MODE 	RW }
	TIMINGS 	{ R AT91C_CS3_TIMINGS 	RW }
	SETUP 	{ R AT91C_CS3_SETUP 	RW }
	CYCLE 	{ R AT91C_CS3_CYCLE 	RW }
	PULSE 	{ R AT91C_CS3_PULSE 	RW }
	listeReg 	{ MODE TIMINGS SETUP CYCLE PULSE  }

}
array set HSMC4_NFC_att {
	MODE 	{ R AT91C_NFC_MODE 	RW }
	CYCLE 	{ R AT91C_NFC_CYCLE 	RW }
	PULSE 	{ R AT91C_NFC_PULSE 	RW }
	SETUP 	{ R AT91C_NFC_SETUP 	RW }
	TIMINGS 	{ R AT91C_NFC_TIMINGS 	RW }
	listeReg 	{ MODE CYCLE PULSE SETUP TIMINGS  }

}

# ========== Peripheral attributes for DBGU peripheral ========== 
array set DBGU_att {
	CR 	{ R AT91C_DBGU_CR 	WO }
	IDR 	{ R AT91C_DBGU_IDR 	WO }
	CIDR 	{ R AT91C_DBGU_CIDR 	RO }
	IPNAME2 	{ R AT91C_DBGU_IPNAME2 	RW }
	FEATURES 	{ R AT91C_DBGU_FEATURES 	RW }
	FNTR 	{ R AT91C_DBGU_FNTR 	RW }
	RHR 	{ R AT91C_DBGU_RHR 	RO }
	THR 	{ R AT91C_DBGU_THR 	WO }
	ADDRSIZE 	{ R AT91C_DBGU_ADDRSIZE 	RW }
	MR 	{ R AT91C_DBGU_MR 	RW }
	IER 	{ R AT91C_DBGU_IER 	WO }
	BRGR 	{ R AT91C_DBGU_BRGR 	RW }
	CSR 	{ R AT91C_DBGU_CSR 	RO }
	VER 	{ R AT91C_DBGU_VER 	RW }
	IMR 	{ R AT91C_DBGU_IMR 	RO }
	IPNAME1 	{ R AT91C_DBGU_IPNAME1 	RW }
	EXID 	{ R AT91C_DBGU_EXID 	RO }
	listeReg 	{ CR IDR CIDR IPNAME2 FEATURES FNTR RHR THR ADDRSIZE MR IER BRGR CSR VER IMR IPNAME1 EXID  }

}

# ========== Peripheral attributes for PMC peripheral ========== 
array set PMC_att {
	PLLAR 	{ R AT91C_PMC_PLLAR 	RW }
	UCKR 	{ R AT91C_PMC_UCKR 	RW }
	FSMR 	{ R AT91C_PMC_FSMR 	RW }
	MCKR 	{ R AT91C_PMC_MCKR 	RW }
	SCER 	{ R AT91C_PMC_SCER 	WO }
	PCSR 	{ R AT91C_PMC_PCSR 	RO }
	MCFR 	{ R AT91C_PMC_MCFR 	RO }
	FOCR 	{ R AT91C_PMC_FOCR 	WO }
	FSPR 	{ R AT91C_PMC_FSPR 	RW }
	SCSR 	{ R AT91C_PMC_SCSR 	RO }
	IDR 	{ R AT91C_PMC_IDR 	WO }
	VER 	{ R AT91C_PMC_VER 	RO }
	IMR 	{ R AT91C_PMC_IMR 	RO }
	IPNAME2 	{ R AT91C_PMC_IPNAME2 	RW }
	SCDR 	{ R AT91C_PMC_SCDR 	WO }
	PCKR 	{ R AT91C_PMC_PCKR 	RW  8 }
	ADDRSIZE 	{ R AT91C_PMC_ADDRSIZE 	RW }
	PCDR 	{ R AT91C_PMC_PCDR 	WO }
	MOR 	{ R AT91C_PMC_MOR 	RW }
	SR 	{ R AT91C_PMC_SR 	RO }
	IER 	{ R AT91C_PMC_IER 	WO }
	IPNAME1 	{ R AT91C_PMC_IPNAME1 	RW }
	PCER 	{ R AT91C_PMC_PCER 	WO }
	FEATURES 	{ R AT91C_PMC_FEATURES 	RW }
	listeReg 	{ PLLAR UCKR FSMR MCKR SCER PCSR MCFR FOCR FSPR SCSR IDR VER IMR IPNAME2 SCDR PCKR ADDRSIZE PCDR MOR SR IER IPNAME1 PCER FEATURES  }

}

# ========== Peripheral attributes for MCI peripheral ========== 
array set MCI0_att {
	DMA 	{ R AT91C_MCI0_DMA 	RW }
	SDCR 	{ R AT91C_MCI0_SDCR 	RW }
	IPNAME1 	{ R AT91C_MCI0_IPNAME1 	RW }
	CSTOR 	{ R AT91C_MCI0_CSTOR 	RW }
	RDR 	{ R AT91C_MCI0_RDR 	RO }
	CMDR 	{ R AT91C_MCI0_CMDR 	WO }
	IDR 	{ R AT91C_MCI0_IDR 	WO }
	ADDRSIZE 	{ R AT91C_MCI0_ADDRSIZE 	RW }
	WPCR 	{ R AT91C_MCI0_WPCR 	RW }
	RSPR 	{ R AT91C_MCI0_RSPR 	RO  4 }
	IPNAME2 	{ R AT91C_MCI0_IPNAME2 	RW }
	CR 	{ R AT91C_MCI0_CR 	WO }
	IMR 	{ R AT91C_MCI0_IMR 	RO }
	WPSR 	{ R AT91C_MCI0_WPSR 	R0 }
	DTOR 	{ R AT91C_MCI0_DTOR 	RW }
	MR 	{ R AT91C_MCI0_MR 	RW }
	SR 	{ R AT91C_MCI0_SR 	RO }
	IER 	{ R AT91C_MCI0_IER 	WO }
	VER 	{ R AT91C_MCI0_VER 	RW }
	FEATURES 	{ R AT91C_MCI0_FEATURES 	RW }
	BLKR 	{ R AT91C_MCI0_BLKR 	RW }
	ARGR 	{ R AT91C_MCI0_ARGR 	RW }
	FIFO 	{ R AT91C_MCI0_FIFO 	R0 }
	TDR 	{ R AT91C_MCI0_TDR 	RO }
	CFG 	{ R AT91C_MCI0_CFG 	RW }
	listeReg 	{ DMA SDCR IPNAME1 CSTOR RDR CMDR IDR ADDRSIZE WPCR RSPR IPNAME2 CR IMR WPSR DTOR MR SR IER VER FEATURES BLKR ARGR FIFO TDR CFG  }

}

# ========== Peripheral attributes for NVIC peripheral ========== 
array set NVIC_att {
	MMAR 	{ R AT91C_NVIC_MMAR 	RO }
	STIR 	{ R AT91C_NVIC_STIR 	RO }
	MMFR2 	{ R AT91C_NVIC_MMFR2 	RO }
	CPUID 	{ R AT91C_NVIC_CPUID 	RO }
	DFSR 	{ R AT91C_NVIC_DFSR 	RO }
	HAND4PR 	{ R AT91C_NVIC_HAND4PR 	RO }
	HFSR 	{ R AT91C_NVIC_HFSR 	RO }
	PID6 	{ R AT91C_NVIC_PID6 	RO }
	PFR0 	{ R AT91C_NVIC_PFR0 	RO }
	VTOFFR 	{ R AT91C_NVIC_VTOFFR 	RO }
	ISPR 	{ R AT91C_NVIC_ISPR 	RO  8 }
	PID0 	{ R AT91C_NVIC_PID0 	RO }
	PID7 	{ R AT91C_NVIC_PID7 	RO }
	STICKRVR 	{ R AT91C_NVIC_STICKRVR 	RW }
	PID2 	{ R AT91C_NVIC_PID2 	RO }
	ISAR0 	{ R AT91C_NVIC_ISAR0 	RO }
	SCR 	{ R AT91C_NVIC_SCR 	RO }
	PID4 	{ R AT91C_NVIC_PID4 	RO }
	ISAR2 	{ R AT91C_NVIC_ISAR2 	RO }
	ISER 	{ R AT91C_NVIC_ISER 	RW  8 }
	IPR 	{ R AT91C_NVIC_IPR 	RO 60 }
	AIRCR 	{ R AT91C_NVIC_AIRCR 	RO }
	CID2 	{ R AT91C_NVIC_CID2 	RO }
	ICPR 	{ R AT91C_NVIC_ICPR 	RO  8 }
	CID3 	{ R AT91C_NVIC_CID3 	RO }
	CFSR 	{ R AT91C_NVIC_CFSR 	RO }
	AFR0 	{ R AT91C_NVIC_AFR0 	RO }
	ICSR 	{ R AT91C_NVIC_ICSR 	RO }
	CCR 	{ R AT91C_NVIC_CCR 	RO }
	CID0 	{ R AT91C_NVIC_CID0 	RO }
	ISAR1 	{ R AT91C_NVIC_ISAR1 	RO }
	STICKCVR 	{ R AT91C_NVIC_STICKCVR 	RW }
	STICKCSR 	{ R AT91C_NVIC_STICKCSR 	RW }
	CID1 	{ R AT91C_NVIC_CID1 	RO }
	DFR0 	{ R AT91C_NVIC_DFR0 	RO }
	MMFR3 	{ R AT91C_NVIC_MMFR3 	RO }
	MMFR0 	{ R AT91C_NVIC_MMFR0 	RO }
	STICKCALVR 	{ R AT91C_NVIC_STICKCALVR 	RO }
	PID1 	{ R AT91C_NVIC_PID1 	RO }
	HAND12PR 	{ R AT91C_NVIC_HAND12PR 	RO }
	MMFR1 	{ R AT91C_NVIC_MMFR1 	RO }
	AFSR 	{ R AT91C_NVIC_AFSR 	RO }
	HANDCSR 	{ R AT91C_NVIC_HANDCSR 	RO }
	ISAR4 	{ R AT91C_NVIC_ISAR4 	RO }
	ABR 	{ R AT91C_NVIC_ABR 	RO  8 }
	PFR1 	{ R AT91C_NVIC_PFR1 	RO }
	PID5 	{ R AT91C_NVIC_PID5 	RO }
	ICTR 	{ R AT91C_NVIC_ICTR 	RO }
	ICER 	{ R AT91C_NVIC_ICER 	RW  8 }
	PID3 	{ R AT91C_NVIC_PID3 	RO }
	ISAR3 	{ R AT91C_NVIC_ISAR3 	RO }
	HAND8PR 	{ R AT91C_NVIC_HAND8PR 	RO }
	BFAR 	{ R AT91C_NVIC_BFAR 	RO }
	listeReg 	{ MMAR STIR MMFR2 CPUID DFSR HAND4PR HFSR PID6 PFR0 VTOFFR ISPR PID0 PID7 STICKRVR PID2 ISAR0 SCR PID4 ISAR2 ISER IPR AIRCR CID2 ICPR CID3 CFSR AFR0 ICSR CCR CID0 ISAR1 STICKCVR STICKCSR CID1 DFR0 MMFR3 MMFR0 STICKCALVR PID1 HAND12PR MMFR1 AFSR HANDCSR ISAR4 ABR PFR1 PID5 ICTR ICER PID3 ISAR3 HAND8PR BFAR  }

}

# ========== Peripheral attributes for USART peripheral ========== 
array set US0_att {
	NER 	{ R AT91C_US0_NER 	RO }
	RHR 	{ R AT91C_US0_RHR 	RO }
	IPNAME1 	{ R AT91C_US0_IPNAME1 	RW }
	MR 	{ R AT91C_US0_MR 	RW }
	RTOR 	{ R AT91C_US0_RTOR 	RW }
	IF 	{ R AT91C_US0_IF 	RW }
	ADDRSIZE 	{ R AT91C_US0_ADDRSIZE 	RW }
	IDR 	{ R AT91C_US0_IDR 	WO }
	IMR 	{ R AT91C_US0_IMR 	RO }
	IER 	{ R AT91C_US0_IER 	WO }
	TTGR 	{ R AT91C_US0_TTGR 	RW }
	IPNAME2 	{ R AT91C_US0_IPNAME2 	RW }
	FIDI 	{ R AT91C_US0_FIDI 	RW }
	CR 	{ R AT91C_US0_CR 	WO }
	BRGR 	{ R AT91C_US0_BRGR 	RW }
	MAN 	{ R AT91C_US0_MAN 	RW }
	VER 	{ R AT91C_US0_VER 	RW }
	FEATURES 	{ R AT91C_US0_FEATURES 	RW }
	CSR 	{ R AT91C_US0_CSR 	RO }
	THR 	{ R AT91C_US0_THR 	WO }
	listeReg 	{ NER RHR IPNAME1 MR RTOR IF ADDRSIZE IDR IMR IER TTGR IPNAME2 FIDI CR BRGR MAN VER FEATURES CSR THR  }

}
array set US1_att {
	IMR 	{ R AT91C_US1_IMR 	RO }
	RTOR 	{ R AT91C_US1_RTOR 	RW }
	RHR 	{ R AT91C_US1_RHR 	RO }
	IPNAME1 	{ R AT91C_US1_IPNAME1 	RW }
	VER 	{ R AT91C_US1_VER 	RW }
	MR 	{ R AT91C_US1_MR 	RW }
	FEATURES 	{ R AT91C_US1_FEATURES 	RW }
	NER 	{ R AT91C_US1_NER 	RO }
	IPNAME2 	{ R AT91C_US1_IPNAME2 	RW }
	CR 	{ R AT91C_US1_CR 	WO }
	BRGR 	{ R AT91C_US1_BRGR 	RW }
	IF 	{ R AT91C_US1_IF 	RW }
	IER 	{ R AT91C_US1_IER 	WO }
	TTGR 	{ R AT91C_US1_TTGR 	RW }
	FIDI 	{ R AT91C_US1_FIDI 	RW }
	MAN 	{ R AT91C_US1_MAN 	RW }
	ADDRSIZE 	{ R AT91C_US1_ADDRSIZE 	RW }
	CSR 	{ R AT91C_US1_CSR 	RO }
	THR 	{ R AT91C_US1_THR 	WO }
	IDR 	{ R AT91C_US1_IDR 	WO }
	listeReg 	{ IMR RTOR RHR IPNAME1 VER MR FEATURES NER IPNAME2 CR BRGR IF IER TTGR FIDI MAN ADDRSIZE CSR THR IDR  }

}
array set US2_att {
	MAN 	{ R AT91C_US2_MAN 	RW }
	ADDRSIZE 	{ R AT91C_US2_ADDRSIZE 	RW }
	MR 	{ R AT91C_US2_MR 	RW }
	IPNAME1 	{ R AT91C_US2_IPNAME1 	RW }
	IF 	{ R AT91C_US2_IF 	RW }
	BRGR 	{ R AT91C_US2_BRGR 	RW }
	FIDI 	{ R AT91C_US2_FIDI 	RW }
	IER 	{ R AT91C_US2_IER 	WO }
	RTOR 	{ R AT91C_US2_RTOR 	RW }
	CR 	{ R AT91C_US2_CR 	WO }
	THR 	{ R AT91C_US2_THR 	WO }
	CSR 	{ R AT91C_US2_CSR 	RO }
	VER 	{ R AT91C_US2_VER 	RW }
	FEATURES 	{ R AT91C_US2_FEATURES 	RW }
	IDR 	{ R AT91C_US2_IDR 	WO }
	TTGR 	{ R AT91C_US2_TTGR 	RW }
	IPNAME2 	{ R AT91C_US2_IPNAME2 	RW }
	RHR 	{ R AT91C_US2_RHR 	RO }
	NER 	{ R AT91C_US2_NER 	RO }
	IMR 	{ R AT91C_US2_IMR 	RO }
	listeReg 	{ MAN ADDRSIZE MR IPNAME1 IF BRGR FIDI IER RTOR CR THR CSR VER FEATURES IDR TTGR IPNAME2 RHR NER IMR  }

}
array set US3_att {
	MAN 	{ R AT91C_US3_MAN 	RW }
	CSR 	{ R AT91C_US3_CSR 	RO }
	BRGR 	{ R AT91C_US3_BRGR 	RW }
	IPNAME2 	{ R AT91C_US3_IPNAME2 	RW }
	RTOR 	{ R AT91C_US3_RTOR 	RW }
	ADDRSIZE 	{ R AT91C_US3_ADDRSIZE 	RW }
	CR 	{ R AT91C_US3_CR 	WO }
	IF 	{ R AT91C_US3_IF 	RW }
	FEATURES 	{ R AT91C_US3_FEATURES 	RW }
	VER 	{ R AT91C_US3_VER 	RW }
	RHR 	{ R AT91C_US3_RHR 	RO }
	TTGR 	{ R AT91C_US3_TTGR 	RW }
	NER 	{ R AT91C_US3_NER 	RO }
	IMR 	{ R AT91C_US3_IMR 	RO }
	THR 	{ R AT91C_US3_THR 	WO }
	IDR 	{ R AT91C_US3_IDR 	WO }
	MR 	{ R AT91C_US3_MR 	RW }
	IER 	{ R AT91C_US3_IER 	WO }
	FIDI 	{ R AT91C_US3_FIDI 	RW }
	IPNAME1 	{ R AT91C_US3_IPNAME1 	RW }
	listeReg 	{ MAN CSR BRGR IPNAME2 RTOR ADDRSIZE CR IF FEATURES VER RHR TTGR NER IMR THR IDR MR IER FIDI IPNAME1  }

}

# ========== Peripheral attributes for SPI peripheral ========== 
array set SPI0_att {
	ADDRSIZE 	{ R AT91C_SPI0_ADDRSIZE 	RW }
	RDR 	{ R AT91C_SPI0_RDR 	RO }
	FEATURES 	{ R AT91C_SPI0_FEATURES 	RW }
	CR 	{ R AT91C_SPI0_CR 	RO }
	IPNAME1 	{ R AT91C_SPI0_IPNAME1 	RW }
	VER 	{ R AT91C_SPI0_VER 	RW }
	IDR 	{ R AT91C_SPI0_IDR 	WO }
	TDR 	{ R AT91C_SPI0_TDR 	WO }
	MR 	{ R AT91C_SPI0_MR 	RW }
	IER 	{ R AT91C_SPI0_IER 	WO }
	IMR 	{ R AT91C_SPI0_IMR 	RO }
	IPNAME2 	{ R AT91C_SPI0_IPNAME2 	RW }
	CSR 	{ R AT91C_SPI0_CSR 	RW  4 }
	SR 	{ R AT91C_SPI0_SR 	RO }
	listeReg 	{ ADDRSIZE RDR FEATURES CR IPNAME1 VER IDR TDR MR IER IMR IPNAME2 CSR SR  }

}

# ========== Peripheral attributes for TCB peripheral ========== 
array set TCB0_att {
	BCR 	{ R AT91C_TCB0_BCR 	WO }
	IPNAME2 	{ R AT91C_TCB0_IPNAME2 	RW }
	IPNAME1 	{ R AT91C_TCB0_IPNAME1 	RW }
	ADDRSIZE 	{ R AT91C_TCB0_ADDRSIZE 	RW }
	FEATURES 	{ R AT91C_TCB0_FEATURES 	RW }
	BMR 	{ R AT91C_TCB0_BMR 	RW }
	VER 	{ R AT91C_TCB0_VER 	RO }
	listeReg 	{ BCR IPNAME2 IPNAME1 ADDRSIZE FEATURES BMR VER  }

}
array set TCB1_att {
	BCR 	{ R AT91C_TCB1_BCR 	WO }
	VER 	{ R AT91C_TCB1_VER 	RO }
	FEATURES 	{ R AT91C_TCB1_FEATURES 	RW }
	IPNAME2 	{ R AT91C_TCB1_IPNAME2 	RW }
	BMR 	{ R AT91C_TCB1_BMR 	RW }
	ADDRSIZE 	{ R AT91C_TCB1_ADDRSIZE 	RW }
	IPNAME1 	{ R AT91C_TCB1_IPNAME1 	RW }
	listeReg 	{ BCR VER FEATURES IPNAME2 BMR ADDRSIZE IPNAME1  }

}
array set TCB2_att {
	FEATURES 	{ R AT91C_TCB2_FEATURES 	RW }
	VER 	{ R AT91C_TCB2_VER 	RO }
	ADDRSIZE 	{ R AT91C_TCB2_ADDRSIZE 	RW }
	IPNAME1 	{ R AT91C_TCB2_IPNAME1 	RW }
	IPNAME2 	{ R AT91C_TCB2_IPNAME2 	RW }
	BMR 	{ R AT91C_TCB2_BMR 	RW }
	BCR 	{ R AT91C_TCB2_BCR 	WO }
	listeReg 	{ FEATURES VER ADDRSIZE IPNAME1 IPNAME2 BMR BCR  }

}

# ========== Peripheral attributes for UDPHS_EPT peripheral ========== 
array set UDPHS_EPT_0_att {
	EPTCTL 	{ R AT91C_UDPHS_EPT_0_EPTCTL 	RO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_0_EPTSTA 	RO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_0_EPTCLRSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_0_EPTCTLDIS 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_0_EPTCFG 	RW }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_0_EPTSETSTA 	WO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_0_EPTCTLENB 	WO }
	listeReg 	{ EPTCTL EPTSTA EPTCLRSTA EPTCTLDIS EPTCFG EPTSETSTA EPTCTLENB  }

}
array set UDPHS_EPT_1_att {
	EPTSTA 	{ R AT91C_UDPHS_EPT_1_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_1_EPTSETSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_1_EPTCTL 	RO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_1_EPTCFG 	RW }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_1_EPTCTLDIS 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_1_EPTCLRSTA 	WO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_1_EPTCTLENB 	WO }
	listeReg 	{ EPTSTA EPTSETSTA EPTCTL EPTCFG EPTCTLDIS EPTCLRSTA EPTCTLENB  }

}
array set UDPHS_EPT_2_att {
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_2_EPTCTLENB 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_2_EPTCLRSTA 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_2_EPTCFG 	RW }
	EPTCTL 	{ R AT91C_UDPHS_EPT_2_EPTCTL 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_2_EPTSETSTA 	WO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_2_EPTSTA 	RO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_2_EPTCTLDIS 	WO }
	listeReg 	{ EPTCTLENB EPTCLRSTA EPTCFG EPTCTL EPTSETSTA EPTSTA EPTCTLDIS  }

}
array set UDPHS_EPT_3_att {
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_3_EPTCTLDIS 	WO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_3_EPTCTLENB 	WO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_3_EPTSETSTA 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_3_EPTCLRSTA 	WO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_3_EPTCFG 	RW }
	EPTSTA 	{ R AT91C_UDPHS_EPT_3_EPTSTA 	RO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_3_EPTCTL 	RO }
	listeReg 	{ EPTCTLDIS EPTCTLENB EPTSETSTA EPTCLRSTA EPTCFG EPTSTA EPTCTL  }

}
array set UDPHS_EPT_4_att {
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_4_EPTSETSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_4_EPTCTLDIS 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_4_EPTCTL 	RO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_4_EPTCFG 	RW }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_4_EPTCTLENB 	WO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_4_EPTSTA 	RO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_4_EPTCLRSTA 	WO }
	listeReg 	{ EPTSETSTA EPTCTLDIS EPTCTL EPTCFG EPTCTLENB EPTSTA EPTCLRSTA  }

}
array set UDPHS_EPT_5_att {
	EPTCFG 	{ R AT91C_UDPHS_EPT_5_EPTCFG 	RW }
	EPTCTL 	{ R AT91C_UDPHS_EPT_5_EPTCTL 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_5_EPTCTLENB 	WO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_5_EPTSTA 	RO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_5_EPTSETSTA 	WO }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_5_EPTCTLDIS 	WO }
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_5_EPTCLRSTA 	WO }
	listeReg 	{ EPTCFG EPTCTL EPTCTLENB EPTSTA EPTSETSTA EPTCTLDIS EPTCLRSTA  }

}
array set UDPHS_EPT_6_att {
	EPTCLRSTA 	{ R AT91C_UDPHS_EPT_6_EPTCLRSTA 	WO }
	EPTCTL 	{ R AT91C_UDPHS_EPT_6_EPTCTL 	RO }
	EPTCFG 	{ R AT91C_UDPHS_EPT_6_EPTCFG 	RW }
	EPTCTLDIS 	{ R AT91C_UDPHS_EPT_6_EPTCTLDIS 	WO }
	EPTSTA 	{ R AT91C_UDPHS_EPT_6_EPTSTA 	RO }
	EPTCTLENB 	{ R AT91C_UDPHS_EPT_6_EPTCTLENB 	WO }
	EPTSETSTA 	{ R AT91C_UDPHS_EPT_6_EPTSETSTA 	WO }
	listeReg 	{ EPTCLRSTA EPTCTL EPTCFG EPTCTLDIS EPTSTA EPTCTLENB EPTSETSTA  }

}

# ========== Peripheral attributes for SUPC peripheral ========== 
array set SUPC_att {
	WUIR 	{ R AT91C_SUPC_WUIR 	RW }
	CR 	{ R AT91C_SUPC_CR 	WO }
	MR 	{ R AT91C_SUPC_MR 	RW }
	FWUTR 	{ R AT91C_SUPC_FWUTR 	RW }
	SR 	{ R AT91C_SUPC_SR 	RO }
	WUMR 	{ R AT91C_SUPC_WUMR 	RW }
	BOMR 	{ R AT91C_SUPC_BOMR 	RW }
	listeReg 	{ WUIR CR MR FWUTR SR WUMR BOMR  }

}

# ========== Peripheral attributes for CM3 peripheral ========== 
array set CM3_att {
	SHCSR 	{ R AT91C_CM3_SHCSR 	RW }
	CCR 	{ R AT91C_CM3_CCR 	RW }
	ICSR 	{ R AT91C_CM3_ICSR 	RW }
	CPUID 	{ R AT91C_CM3_CPUID 	RO }
	SCR 	{ R AT91C_CM3_SCR 	RW }
	AIRCR 	{ R AT91C_CM3_AIRCR 	RW }
	SHPR 	{ R AT91C_CM3_SHPR 	RW  3 }
	VTOR 	{ R AT91C_CM3_VTOR 	RW }
	listeReg 	{ SHCSR CCR ICSR CPUID SCR AIRCR SHPR VTOR  }

}

# ========== Peripheral attributes for MPU peripheral ========== 
array set MPU_att {
	ADDR3 	{ R AT91C_MPU_REG_BASE_ADDR3 	RW }
	NB 	{ R AT91C_MPU_REG_NB 	RW }
	SIZE1 	{ R AT91C_MPU_ATTR_SIZE1 	RW }
	ADDR1 	{ R AT91C_MPU_REG_BASE_ADDR1 	RW }
	SIZE3 	{ R AT91C_MPU_ATTR_SIZE3 	RW }
	CTRL 	{ R AT91C_MPU_CTRL 	RW }
	SIZE2 	{ R AT91C_MPU_ATTR_SIZE2 	RW }
	ADDR 	{ R AT91C_MPU_REG_BASE_ADDR 	RW }
	ADDR2 	{ R AT91C_MPU_REG_BASE_ADDR2 	RW }
	SIZE 	{ R AT91C_MPU_ATTR_SIZE 	RW }
	TYPE 	{ R AT91C_MPU_TYPE 	RO }
	listeReg 	{ ADDR3 NB SIZE1 ADDR1 SIZE3 CTRL SIZE2 ADDR ADDR2 SIZE TYPE  }

}

# ========== Peripheral attributes for ADC peripheral ========== 
array set ADC0_att {
	CDR4 	{ R AT91C_ADC0_CDR4 	RO }
	CDR2 	{ R AT91C_ADC0_CDR2 	RO }
	CHER 	{ R AT91C_ADC0_CHER 	WO }
	SR 	{ R AT91C_ADC0_SR 	RO }
	IPNAME1 	{ R AT91C_ADC0_IPNAME1 	RW }
	IER 	{ R AT91C_ADC0_IER 	WO }
	CR 	{ R AT91C_ADC0_CR 	WO }
	CDR6 	{ R AT91C_ADC0_CDR6 	RO }
	CHDR 	{ R AT91C_ADC0_CHDR 	WO }
	CDR3 	{ R AT91C_ADC0_CDR3 	RO }
	IDR 	{ R AT91C_ADC0_IDR 	WO }
	VER 	{ R AT91C_ADC0_VER 	RO }
	CDR7 	{ R AT91C_ADC0_CDR7 	RO }
	CHSR 	{ R AT91C_ADC0_CHSR 	RO }
	CDR5 	{ R AT91C_ADC0_CDR5 	RO }
	IPNAME2 	{ R AT91C_ADC0_IPNAME2 	RW }
	MR 	{ R AT91C_ADC0_MR 	RW }
	FEATURES 	{ R AT91C_ADC0_FEATURES 	RW }
	CDR0 	{ R AT91C_ADC0_CDR0 	RO }
	LCDR 	{ R AT91C_ADC0_LCDR 	RO }
	IMR 	{ R AT91C_ADC0_IMR 	RO }
	ADDRSIZE 	{ R AT91C_ADC0_ADDRSIZE 	RW }
	CDR1 	{ R AT91C_ADC0_CDR1 	RO }
	listeReg 	{ CDR4 CDR2 CHER SR IPNAME1 IER CR CDR6 CHDR CDR3 IDR VER CDR7 CHSR CDR5 IPNAME2 MR FEATURES CDR0 LCDR IMR ADDRSIZE CDR1  }

}
array set ADC1_att {
	IPNAME2 	{ R AT91C_ADC1_IPNAME2 	RW }
	ADDRSIZE 	{ R AT91C_ADC1_ADDRSIZE 	RW }
	IDR 	{ R AT91C_ADC1_IDR 	WO }
	CHSR 	{ R AT91C_ADC1_CHSR 	RO }
	FEATURES 	{ R AT91C_ADC1_FEATURES 	RW }
	CDR0 	{ R AT91C_ADC1_CDR0 	RO }
	LCDR 	{ R AT91C_ADC1_LCDR 	RO }
	CDR3 	{ R AT91C_ADC1_CDR3 	RO }
	CDR7 	{ R AT91C_ADC1_CDR7 	RO }
	SR 	{ R AT91C_ADC1_SR 	RO }
	CDR5 	{ R AT91C_ADC1_CDR5 	RO }
	IPNAME1 	{ R AT91C_ADC1_IPNAME1 	RW }
	CDR6 	{ R AT91C_ADC1_CDR6 	RO }
	MR 	{ R AT91C_ADC1_MR 	RW }
	CDR1 	{ R AT91C_ADC1_CDR1 	RO }
	CDR2 	{ R AT91C_ADC1_CDR2 	RO }
	CDR4 	{ R AT91C_ADC1_CDR4 	RO }
	CHER 	{ R AT91C_ADC1_CHER 	WO }
	VER 	{ R AT91C_ADC1_VER 	RO }
	CHDR 	{ R AT91C_ADC1_CHDR 	WO }
	CR 	{ R AT91C_ADC1_CR 	WO }
	IMR 	{ R AT91C_ADC1_IMR 	RO }
	IER 	{ R AT91C_ADC1_IER 	WO }
	listeReg 	{ IPNAME2 ADDRSIZE IDR CHSR FEATURES CDR0 LCDR CDR3 CDR7 SR CDR5 IPNAME1 CDR6 MR CDR1 CDR2 CDR4 CHER VER CHDR CR IMR IER  }

}

# ========== Peripheral attributes for PWMC_CH peripheral ========== 
array set PWMC_CH0_att {
	DTR 	{ R AT91C_PWMC_CH0_DTR 	RW }
	CMR 	{ R AT91C_PWMC_CH0_CMR 	RW }
	CCNTR 	{ R AT91C_PWMC_CH0_CCNTR 	RO }
	CPRDR 	{ R AT91C_PWMC_CH0_CPRDR 	RW }
	DTUPDR 	{ R AT91C_PWMC_CH0_DTUPDR 	WO }
	CPRDUPDR 	{ R AT91C_PWMC_CH0_CPRDUPDR 	WO }
	CDTYUPDR 	{ R AT91C_PWMC_CH0_CDTYUPDR 	WO }
	CDTYR 	{ R AT91C_PWMC_CH0_CDTYR 	RW }
	listeReg 	{ DTR CMR CCNTR CPRDR DTUPDR CPRDUPDR CDTYUPDR CDTYR  }

}
array set PWMC_CH1_att {
	CCNTR 	{ R AT91C_PWMC_CH1_CCNTR 	RO }
	DTR 	{ R AT91C_PWMC_CH1_DTR 	RW }
	CDTYUPDR 	{ R AT91C_PWMC_CH1_CDTYUPDR 	WO }
	DTUPDR 	{ R AT91C_PWMC_CH1_DTUPDR 	WO }
	CDTYR 	{ R AT91C_PWMC_CH1_CDTYR 	RW }
	CPRDR 	{ R AT91C_PWMC_CH1_CPRDR 	RW }
	CPRDUPDR 	{ R AT91C_PWMC_CH1_CPRDUPDR 	WO }
	CMR 	{ R AT91C_PWMC_CH1_CMR 	RW }
	listeReg 	{ CCNTR DTR CDTYUPDR DTUPDR CDTYR CPRDR CPRDUPDR CMR  }

}
array set PWMC_CH2_att {
	CDTYR 	{ R AT91C_PWMC_CH2_CDTYR 	RW }
	DTUPDR 	{ R AT91C_PWMC_CH2_DTUPDR 	WO }
	CCNTR 	{ R AT91C_PWMC_CH2_CCNTR 	RO }
	CMR 	{ R AT91C_PWMC_CH2_CMR 	RW }
	CPRDR 	{ R AT91C_PWMC_CH2_CPRDR 	RW }
	CPRDUPDR 	{ R AT91C_PWMC_CH2_CPRDUPDR 	WO }
	CDTYUPDR 	{ R AT91C_PWMC_CH2_CDTYUPDR 	WO }
	DTR 	{ R AT91C_PWMC_CH2_DTR 	RW }
	listeReg 	{ CDTYR DTUPDR CCNTR CMR CPRDR CPRDUPDR CDTYUPDR DTR  }

}
array set PWMC_CH3_att {
	CPRDUPDR 	{ R AT91C_PWMC_CH3_CPRDUPDR 	WO }
	DTR 	{ R AT91C_PWMC_CH3_DTR 	RW }
	CDTYR 	{ R AT91C_PWMC_CH3_CDTYR 	RW }
	DTUPDR 	{ R AT91C_PWMC_CH3_DTUPDR 	WO }
	CDTYUPDR 	{ R AT91C_PWMC_CH3_CDTYUPDR 	WO }
	CCNTR 	{ R AT91C_PWMC_CH3_CCNTR 	RO }
	CMR 	{ R AT91C_PWMC_CH3_CMR 	RW }
	CPRDR 	{ R AT91C_PWMC_CH3_CPRDR 	RW }
	listeReg 	{ CPRDUPDR DTR CDTYR DTUPDR CDTYUPDR CCNTR CMR CPRDR  }

}

# ========== Peripheral attributes for UDPHS_EPTFIFO peripheral ========== 
array set UDPHS_EPTFIFO_att {
	READEPT6 	{ R AT91C_UDPHS_EPTFIFO_READEPT6 	RW 16384 }
	READEPT2 	{ R AT91C_UDPHS_EPTFIFO_READEPT2 	RW 16384 }
	READEPT1 	{ R AT91C_UDPHS_EPTFIFO_READEPT1 	RW 16384 }
	READEPT0 	{ R AT91C_UDPHS_EPTFIFO_READEPT0 	RW 16384 }
	READEPT5 	{ R AT91C_UDPHS_EPTFIFO_READEPT5 	RW 16384 }
	READEPT4 	{ R AT91C_UDPHS_EPTFIFO_READEPT4 	RW 16384 }
	READEPT3 	{ R AT91C_UDPHS_EPTFIFO_READEPT3 	RW 16384 }
	listeReg 	{ READEPT6 READEPT2 READEPT1 READEPT0 READEPT5 READEPT4 READEPT3  }

}

# ========== Peripheral attributes for UDPHS peripheral ========== 
array set UDPHS_att {
	EPTRST 	{ R AT91C_UDPHS_EPTRST 	WO }
	IEN 	{ R AT91C_UDPHS_IEN 	RW }
	TSTCNTB 	{ R AT91C_UDPHS_TSTCNTB 	RW }
	RIPNAME2 	{ R AT91C_UDPHS_RIPNAME2 	RO }
	RIPPADDRSIZE 	{ R AT91C_UDPHS_RIPPADDRSIZE 	RO }
	TSTMODREG 	{ R AT91C_UDPHS_TSTMODREG 	RW }
	TST 	{ R AT91C_UDPHS_TST 	RW }
	TSTSOFCNT 	{ R AT91C_UDPHS_TSTSOFCNT 	RW }
	FNUM 	{ R AT91C_UDPHS_FNUM 	RO }
	TSTCNTA 	{ R AT91C_UDPHS_TSTCNTA 	RW }
	INTSTA 	{ R AT91C_UDPHS_INTSTA 	RO }
	IPFEATURES 	{ R AT91C_UDPHS_IPFEATURES 	RO }
	CLRINT 	{ R AT91C_UDPHS_CLRINT 	WO }
	RIPNAME1 	{ R AT91C_UDPHS_RIPNAME1 	RO }
	CTRL 	{ R AT91C_UDPHS_CTRL 	RW }
	IPVERSION 	{ R AT91C_UDPHS_IPVERSION 	RO }
	listeReg 	{ EPTRST IEN TSTCNTB RIPNAME2 RIPPADDRSIZE TSTMODREG TST TSTSOFCNT FNUM TSTCNTA INTSTA IPFEATURES CLRINT RIPNAME1 CTRL IPVERSION  }

}

# ========== PIO information ========== 

array set def_PIOA_att {
 	PA0 	{  TIOB0   SPI0_NPCS1  }
 	PA1 	{  TIOA0   SPI0_NPCS2  }
 	PA10 	{  TWCK0   PWML3  }
 	PA11 	{  DRXD  }
 	PA12 	{  DTXD  }
 	PA13 	{  SPI0_MISO  }
 	PA14 	{  SPI0_MOSI  }
 	PA15 	{  SPI0_SPCK   PWMH2  }
 	PA16 	{  SPI0_NPCS0   NCS1  }
 	PA17 	{  SCK0   ADTRG0  }
 	PA18 	{  TXD0  }
 	PA19 	{  RXD0   SPI0_NPCS3  }
 	PA2 	{  TCLK0   ADTRG1  }
 	PA20 	{  TXD1   PWMH3  }
 	PA21 	{  RXD1   PCK0  }
 	PA22 	{  TXD2   RTS1  }
 	PA23 	{  RXD2   CTS1  }
 	PA24 	{  TWD1   SCK1  }
 	PA25 	{  TWCK1   SCK2  }
 	PA26 	{  TD0   TCLK2  }
 	PA27 	{  RD0   PCK0  }
 	PA28 	{  TK0   PWMH0  }
 	PA29 	{  RK0   PWMH1  }
 	PA3 	{  MCI0_CK   PCK1  }
 	PA30 	{  TF0   TIOA2  }
 	PA31 	{  RF0   TIOB2  }
 	PA4 	{  MCI0_CDA   PWMH0  }
 	PA5 	{  MCI0_DA0   PWMH1  }
 	PA6 	{  MCI0_DA1   PWMH2  }
 	PA7 	{  MCI0_DA2   PWML0  }
 	PA8 	{  MCI0_DA3   PWML1  }
 	PA9 	{  TWD0   PWML2  }
 }

array set def_PIOB_att {
 	PB0 	{  PWMH0   A2  }
 	PB1 	{  PWMH1   A3  }
 	PB10 	{  D1   DSR0  }
 	PB11 	{  D2   DCD0  }
 	PB12 	{  D3   RI0  }
 	PB13 	{  D4   PWMH0  }
 	PB14 	{  D5   PWMH1  }
 	PB15 	{  D6   PWMH2  }
 	PB16 	{  D7   PWMH3  }
 	PB17 	{  NANDOE   PWML0  }
 	PB18 	{  NANDWE   PWML1  }
 	PB19 	{  NRD   PWML2  }
 	PB2 	{  PWMH2   A4  }
 	PB20 	{  NCS0   PWML3  }
 	PB21 	{  A21_NANDALE   RTS2  }
 	PB22 	{  A22_NANDCLE   CTS2  }
 	PB23 	{  NWR0_NWE   PCK2  }
 	PB24 	{  NANDRDY   PCK1  }
 	PB25 	{  D8   PWML0  }
 	PB26 	{  D9   PWML1  }
 	PB27 	{  D10   PWML2  }
 	PB28 	{  D11   PWML3  }
 	PB29 	{  D12  }
 	PB3 	{  PWMH3   A5  }
 	PB30 	{  D13  }
 	PB31 	{  D14  }
 	PB4 	{  TCLK1   A6  }
 	PB5 	{  TIOA1   A7  }
 	PB6 	{  TIOB1   D15  }
 	PB7 	{  RTS0   A0_NBS0  }
 	PB8 	{  CTS0   A1  }
 	PB9 	{  D0   DTR0  }
 }

array set def_PIOC_att {
 	PC0 	{  A2  }
 	PC1 	{  A3  }
 	PC10 	{  A12   CTS3  }
 	PC11 	{  A13   RTS3  }
 	PC12 	{  NCS1   TXD3  }
 	PC13 	{  A2   RXD3  }
 	PC14 	{  A3   SPI0_NPCS2  }
 	PC15 	{  NWR1_NBS1  }
 	PC16 	{  NCS2   PWML3  }
 	PC17 	{  NCS3   A24  }
 	PC18 	{  NWAIT  }
 	PC19 	{  SCK3   NPCS1  }
 	PC2 	{  A4  }
 	PC20 	{  A14  }
 	PC21 	{  A15  }
 	PC22 	{  A16  }
 	PC23 	{  A17  }
 	PC24 	{  A18   PWMH0  }
 	PC25 	{  A19   PWMH1  }
 	PC26 	{  A20   PWMH2  }
 	PC27 	{  A23   PWMH3  }
 	PC28 	{  A24   MCI0_DA4  }
 	PC29 	{  PWML0   MCI0_DA5  }
 	PC3 	{  A5   SPI0_NPCS1  }
 	PC30 	{  PWML1   MCI0_DA6  }
 	PC31 	{  PWML2   MCI0_DA7  }
 	PC4 	{  A6   SPI0_NPCS2  }
 	PC5 	{  A7   SPI0_NPCS3  }
 	PC6 	{  A8   PWML0  }
 	PC7 	{  A9   PWML1  }
 	PC8 	{  A10   PWML2  }
 	PC9 	{  A11   PWML3  }
 }

# *****************************************************************************
#               IP PIN DEFINITIONS FOR AT91SAM3UE256
# *****************************************************************************

# table definition: portname direction is_a_pio is_open_drain

array set def_design_att {
  MCI0 {
    CK {mci0_ck output 1 0}
    CDA {mci0_cda output 1 0}
    DA0 {mci0_da0 inout 1 0}
    DA1 {mci0_da1 inout 1 0}
    DA2 {mci0_da2 inout 1 0}
    DA3 {mci0_da3 inout 1 0}
    DA4 {mci0_da4 inout 1 0}
    DA5 {mci0_da5 inout 1 0}
    DA6 {mci0_da6 inout 1 0}
    DA7 {mci0_da7 inout 1 0}
  }
  NAND0 {
    D0 {d0 inout 1 0}
    D1 {d1 inout 1 0}
    D2 {d2 inout 1 0}
    D3 {d3 inout 1 0}
    D4 {d4 inout 1 0}
    D5 {d5 inout 1 0}
    D6 {d6 inout 1 0}
    D7 {d7 inout 1 0}
    D8 {d8 inout 1 0}
    D9 {d9 inout 1 0}
    D10 {d10 inout 1 0}
    D11 {d11 inout 1 0}
    D12 {d12 inout 1 0}
    D13 {d13 inout 1 0}
    D14 {d14 inout 1 0}
    D15 {d15 inout 1 0}
    NANDCLE {a22_nandcle output 1 0}
    NANDALE {a21_nandale output 1 0}
    NANDWE {nandwe output 1 0}
    NANDOE {nandoe output 1 0}
    NCS0 {ncs0 output 1 0}
    NCS1 {ncs1 output 1 0}
    NCS2 {ncs2 output 1 0}
    NCS3 {ncs3 output 1 0}
  }
  SPI0 {
    SPI0_NPCS0 {spi0_npcs0 inout 1 0}
    SPI0_NPCS1 {spi0_npcs1 output 1 0}
    SPI0_NPCS2 {spi0_npcs2 output 1 0}
    SPI0_NPCS3 {spi0_npcs3 output 1 0}
    SPI0_MOSI {spi0_mosi inout 1 0}
    SPI0_MISO {spi0_miso inout 1 0}
    SPI0_SPCK {spi0_spck inout 1 0}
  }
  SRAM0 {
    A0 {a0_nbs0 output 1 0}
    A1 {a1 output 1 0}
    A2 {a2 output 1 0}
    A3 {a3 output 1 0}
    A4 {a4 output 1 0}
    A5 {a5 output 1 0}
    A6 {a6 output 1 0}
    A7 {a7 output 1 0}
    A8 {a8 output 1 0}
    A9 {a9 output 1 0}
    A10 {a10 output 1 0}
    A11 {a11 output 1 0}
    A12 {a12 output 1 0}
    A13 {a13 output 1 0}
    A14 {a14 output 1 0}
    A15 {a15 output 1 0}
    A16 {a16 output 1 0}
    A17 {a17 output 1 0}
    A18 {a18 output 1 0}
    A19 {a19 output 1 0}
    A20 {a20 output 1 0}
    A21 {a21_nandale output 1 0}
    A22 {a22_nandcle output 1 0}
    A23 {a23 output 1 0}
    A24 {a24 output 1 0}
    D0 {d0 inout 1 0}
    D1 {d1 inout 1 0}
    D2 {d2 inout 1 0}
    D3 {d3 inout 1 0}
    D4 {d4 inout 1 0}
    D5 {d5 inout 1 0}
    D6 {d6 inout 1 0}
    D7 {d7 inout 1 0}
    D8 {d8 inout 1 0}
    D9 {d9 inout 1 0}
    D10 {d10 inout 1 0}
    D11 {d11 inout 1 0}
    D12 {d12 inout 1 0}
    D13 {d13 inout 1 0}
    D14 {d14 inout 1 0}
    D15 {d15 inout 1 0}
    NRD {nrd output 1 0}
    NCS0 {ncs0 output 1 0}
    NCS1 {ncs1 output 1 0}
    NCS2 {ncs2 output 1 0}
    NCS3 {ncs3 output 1 0}
    NWR0 {nwr0_nwe output 1 0}
    NWR1 {nwr1_nbs1 output 1 0}
    NBS0 {a0_nbs0 output 1 0}
    NBS1 {nwr1_nbs1 output 1 0}
  }
  SSC0 {
    TK {tk0 inout 1 0}
    TD {td0 output 1 0}
    TF {tf0 inout 1 0}
    RK {rk0 inout 1 0}
    RD {rd0 input 1 0}
    RF {rf0 inout 1 0}
  }
}
