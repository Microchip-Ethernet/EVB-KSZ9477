/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2014, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _SAMA5D4_
#define _SAMA5D4_

/** \addtogroup SAMA5D4_definitions SAMA5D4 definitions
  This file defines all structures and symbols for SAMA5D4:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

#ifdef __cplusplus
 extern "C" {
#endif 

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#include <stdint.h>
#ifdef __cplusplus
  #define __I  volatile       /**< Defines 'read-only'  permissions */
#else
  #define __I  volatile const /**< Defines 'read-only'  permissions */
#endif
#define   __O  volatile       /**< Defines 'write-only' permissions */
#define   __IO volatile       /**< Defines 'read/write' permissions */
#endif

typedef enum IRQn
{
  FIQ_IRQn             =  0, /**<  0 SAMA5D4 FIQ Interrupt ID (FIQ) */
  SYS_IRQn             =  1, /**<  1 SAMA5D4 System Controller Interrupt (SYS) */
  ARM_IRQn             =  2, /**<  2 SAMA5D4 Performance Monitor Unit (ARM) */
  PIT_IRQn             =  3, /**<  3 SAMA5D4 Periodic Interval Timer Interrupt (PIT) */
  WDT_IRQn             =  4, /**<  4 SAMA5D4 Watchdog timer Interrupt (WDT) */
  PIOD_IRQn            =  5, /**<  5 SAMA5D4 Parallel I/O Controller D (PIOD) */
  USART0_IRQn          =  6, /**<  6 SAMA5D4 USART 0 (USART0) */
  USART1_IRQn          =  7, /**<  7 SAMA5D4 USART 1 (USART1) */
  XDMAC0_IRQn          =  8, /**<  8 SAMA5D4 DMA Controller 0 (XDMAC0) */
  ICM_IRQn             =  9, /**<  9 SAMA5D4 Integritry Check Monitor (ICM) */
  AES_IRQn             = 12, /**< 12 SAMA5D4 Advanced Encryption Standard (AES) */
  AESB_IRQn            = 13, /**< 13 SAMA5D4 AES bridge (AESB) */
  TDES_IRQn            = 14, /**< 14 SAMA5D4 Triple Data Encryption Standard (TDES) */
  SHA_IRQn             = 15, /**< 15 SAMA5D4 SHA Signature (SHA) */
  MPDDRC_IRQn          = 16, /**< 16 SAMA5D4 MPDDR controller (MPDDRC) */
  MATRIX1_IRQn         = 17, /**< 17 SAMA5D4 H32MX, 32-bit AHB Matrix (MATRIX1) */
  MATRIX0_IRQn         = 18, /**< 18 SAMA5D4 H64MX, 64-bit AHB Matrix (MATRIX0) */
  VDEC_IRQn            = 19, /**< 19 SAMA5D4 Video Decoder (VDEC) */
  HSMC_IRQn            = 22, /**< 22 SAMA5D4 Multi-bit ECC Interrupt (HSMC) */
  PIOA_IRQn            = 23, /**< 23 SAMA5D4 Parallel I/O Controller A (PIOA) */
  PIOB_IRQn            = 24, /**< 24 SAMA5D4 Parallel I/O Controller B (PIOB) */
  PIOC_IRQn            = 25, /**< 25 SAMA5D4 Parallel I/O Controller C (PIOC) */
  PIOE_IRQn            = 26, /**< 26 SAMA5D4 Parallel I/O Controller E (PIOE) */
  UART0_IRQn           = 27, /**< 27 SAMA5D4 UART 0 (UART0) */
  UART1_IRQn           = 28, /**< 28 SAMA5D4 UART 1 (UART1) */
  USART2_IRQn          = 29, /**< 29 SAMA5D4 USART 2 (USART2) */
  USART3_IRQn          = 30, /**< 30 SAMA5D4 USART 3 (USART3) */
  USART4_IRQn          = 31, /**< 31 SAMA5D4 USART 4 (USART4) */
  TWI0_IRQn            = 32, /**< 32 SAMA5D4 Two-Wire Interface 0 (TWI0) */
  TWI1_IRQn            = 33, /**< 33 SAMA5D4 Two-Wire Interface 1 (TWI1) */
  TWI2_IRQn            = 34, /**< 34 SAMA5D4 Two-Wire Interface 2 (TWI2) */
  HSMCI0_IRQn          = 35, /**< 35 SAMA5D4 High Speed Multimedia Card Interface 0 (HSMCI0) */
  HSMCI1_IRQn          = 36, /**< 36 SAMA5D4 High Speed Multimedia Card Interface 1 (HSMCI1) */
  SPI0_IRQn            = 37, /**< 37 SAMA5D4 Serial Peripheral Interface 0 (SPI0) */
  SPI1_IRQn            = 38, /**< 38 SAMA5D4 Serial Peripheral Interface 1 (SPI1) */
  SPI2_IRQn            = 39, /**< 39 SAMA5D4 Serial Peripheral Interface 2 (SPI2) */
  TC0_IRQn             = 40, /**< 40 SAMA5D4 Timer Counter 0 (ch. 0, 1, 2) (TC0) */
  TC1_IRQn             = 41, /**< 41 SAMA5D4 Timer Counter 1 (ch. 3, 4, 5) (TC1) */
  TC2_IRQn             = 42, /**< 42 SAMA5D4 Timer Counter 2 (ch. 6, 7, 8) (TC2) */
  PWM_IRQn             = 43, /**< 43 SAMA5D4 Pulse Width Modulation Controller (PWM) */
  ADC_IRQn             = 44, /**< 44 SAMA5D4 Touch Screen ADC Controller (ADC) */
  DBGU_IRQn            = 45, /**< 45 SAMA5D4 Debug Unit Interrupt (DBGU) */
  UHPHS_IRQn           = 46, /**< 46 SAMA5D4 USB Host High Speed (UHPHS) */
  UDPHS_IRQn           = 47, /**< 47 SAMA5D4 USB Device High Speed (UDPHS) */
  SSC0_IRQn            = 48, /**< 48 SAMA5D4 Synchronous Serial Controller 0 (SSC0) */
  SSC1_IRQn            = 49, /**< 49 SAMA5D4 Synchronous Serial Controller 1 (SSC1) */
  XDMAC1_IRQn          = 50, /**< 50 SAMA5D4 DMA Controller 1 (XDMAC1) */
  LCDC_IRQn            = 51, /**< 51 SAMA5D4 LCD Controller (LCDC) */
  ISI_IRQn             = 52, /**< 52 SAMA5D4 Camera Interface (ISI) */
  TRNG_IRQn            = 53, /**< 53 SAMA5D4 True Random Number Generator (TRNG) */
  GMAC0_IRQn           = 54, /**< 54 SAMA5D4 Ethernet MAC 0 (GMAC0) */
  GMAC1_IRQn           = 55, /**< 55 SAMA5D4 Ethernet MAC 1 (GMAC1) */
  IRQ_IRQn             = 56, /**< 56 SAMA5D4 IRQ Interrupt ID (IRQ) */
  SFC_IRQn             = 57, /**< 57 SAMA5D4 Fuse Controller (SFC) */
  SMD_IRQn             = 61, /**< 61 SAMA5D4 SMD Soft Modem (SMD) */
  TWI3_IRQn            = 62, /**< 62 SAMA5D4 Two-Wire Interface 3 (TWI3) */
  CATB_IRQn            = 63, /**< 63 SAMA5D4 Capacitive Touch Controller (CATB) */
  SFR_IRQn             = 64, /**< 64 SAMA5D4 Special Function Register  (SFR) */
  AIC_IRQn             = 65, /**< 65 SAMA5D4 Advanced Interrupt Controller  (AIC) */
  SAIC_IRQn            = 66, /**< 66 SAMA5D4 Secured Advanced Interrupt Controller  (SAIC) */
  L2CC_IRQn            = 67, /**< 67 SAMA5D4 L2 Cache Controller  (L2CC) */

  PERIPH_COUNT_IRQn    = 68  /**< Number of peripheral IDs */
} IRQn_Type;

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAMA5D4 */
/* ************************************************************************** */
/** \addtogroup SAMA5D4_api Peripheral Software API */
/*@{*/


/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR AXI Matrix */
/* ============================================================================= */
/** \addtogroup SAMA5D4_AXIMX AXI Matrix */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Aximx hardware registers */
typedef struct {
  __O uint32_t AXIMX_REMAP; /**< \brief (Aximx Offset: 0x00) Remap Register */
} Aximx;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- AXIMX_REMAP : (AXIMX Offset: 0x00) Remap Register -------- */
#define AXIMX_REMAP_REMAP0 (0x1u << 0) /**< \brief (AXIMX_REMAP) Remap State 0 */
#define AXIMX_REMAP_REMAP1 (0x1u << 1) /**< \brief (AXIMX_REMAP) Remap State 1 */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Debug Unit */
/* ============================================================================= */
/** \addtogroup SAMA5D4_DBGU Debug Unit */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Dbgu hardware registers */
typedef struct {
  __O  uint32_t DBGU_CR;      /**< \brief (Dbgu Offset: 0x0000) Control Register */
  __IO uint32_t DBGU_MR;      /**< \brief (Dbgu Offset: 0x0004) Mode Register */
  __O  uint32_t DBGU_IER;     /**< \brief (Dbgu Offset: 0x0008) Interrupt Enable Register */
  __O  uint32_t DBGU_IDR;     /**< \brief (Dbgu Offset: 0x000C) Interrupt Disable Register */
  __I  uint32_t DBGU_IMR;     /**< \brief (Dbgu Offset: 0x0010) Interrupt Mask Register */
  __I  uint32_t DBGU_SR;      /**< \brief (Dbgu Offset: 0x0014) Status Register */
  __I  uint32_t DBGU_RHR;     /**< \brief (Dbgu Offset: 0x0018) Receive Holding Register */
  __O  uint32_t DBGU_THR;     /**< \brief (Dbgu Offset: 0x001C) Transmit Holding Register */
  __IO uint32_t DBGU_BRGR;    /**< \brief (Dbgu Offset: 0x0020) Baud Rate Generator Register */
  __I  uint32_t Reserved1[7];
  __I  uint32_t DBGU_CIDR;    /**< \brief (Dbgu Offset: 0x0040) Chip ID Register */
  __I  uint32_t DBGU_EXID;    /**< \brief (Dbgu Offset: 0x0044) Chip ID Extension Register */
  __IO uint32_t DBGU_FNR;     /**< \brief (Dbgu Offset: 0x0048) Force NTRST Register */
} Dbgu;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- DBGU_CR : (DBGU Offset: 0x0000) Control Register -------- */
#define DBGU_CR_RSTRX (0x1u << 2) /**< \brief (DBGU_CR) Reset Receiver */
#define DBGU_CR_RSTTX (0x1u << 3) /**< \brief (DBGU_CR) Reset Transmitter */
#define DBGU_CR_RXEN (0x1u << 4) /**< \brief (DBGU_CR) Receiver Enable */
#define DBGU_CR_RXDIS (0x1u << 5) /**< \brief (DBGU_CR) Receiver Disable */
#define DBGU_CR_TXEN (0x1u << 6) /**< \brief (DBGU_CR) Transmitter Enable */
#define DBGU_CR_TXDIS (0x1u << 7) /**< \brief (DBGU_CR) Transmitter Disable */
#define DBGU_CR_RSTSTA (0x1u << 8) /**< \brief (DBGU_CR) Reset Status Bits */
/* -------- DBGU_MR : (DBGU Offset: 0x0004) Mode Register -------- */
#define DBGU_MR_PAR_Pos 9
#define DBGU_MR_PAR_Msk (0x7u << DBGU_MR_PAR_Pos) /**< \brief (DBGU_MR) Parity Type */
#define   DBGU_MR_PAR_EVEN (0x0u << 9) /**< \brief (DBGU_MR) Even Parity */
#define   DBGU_MR_PAR_ODD (0x1u << 9) /**< \brief (DBGU_MR) Odd Parity */
#define   DBGU_MR_PAR_SPACE (0x2u << 9) /**< \brief (DBGU_MR) Space: Parity forced to 0 */
#define   DBGU_MR_PAR_MARK (0x3u << 9) /**< \brief (DBGU_MR) Mark: Parity forced to 1 */
#define   DBGU_MR_PAR_NONE (0x4u << 9) /**< \brief (DBGU_MR) No Parity */
#define DBGU_MR_CHMODE_Pos 14
#define DBGU_MR_CHMODE_Msk (0x3u << DBGU_MR_CHMODE_Pos) /**< \brief (DBGU_MR) Channel Mode */
#define   DBGU_MR_CHMODE_NORM (0x0u << 14) /**< \brief (DBGU_MR) Normal Mode */
#define   DBGU_MR_CHMODE_AUTO (0x1u << 14) /**< \brief (DBGU_MR) Automatic Echo */
#define   DBGU_MR_CHMODE_LOCLOOP (0x2u << 14) /**< \brief (DBGU_MR) Local Loopback */
#define   DBGU_MR_CHMODE_REMLOOP (0x3u << 14) /**< \brief (DBGU_MR) Remote Loopback */
/* -------- DBGU_IER : (DBGU Offset: 0x0008) Interrupt Enable Register -------- */
#define DBGU_IER_RXRDY (0x1u << 0) /**< \brief (DBGU_IER) Enable RXRDY Interrupt */
#define DBGU_IER_TXRDY (0x1u << 1) /**< \brief (DBGU_IER) Enable TXRDY Interrupt */
#define DBGU_IER_OVRE (0x1u << 5) /**< \brief (DBGU_IER) Enable Overrun Error Interrupt */
#define DBGU_IER_FRAME (0x1u << 6) /**< \brief (DBGU_IER) Enable Framing Error Interrupt */
#define DBGU_IER_PARE (0x1u << 7) /**< \brief (DBGU_IER) Enable Parity Error Interrupt */
#define DBGU_IER_TXEMPTY (0x1u << 9) /**< \brief (DBGU_IER) Enable TXEMPTY Interrupt */
#define DBGU_IER_COMMTX (0x1u << 30) /**< \brief (DBGU_IER) Enable COMMTX (from ARM) Interrupt */
#define DBGU_IER_COMMRX (0x1u << 31) /**< \brief (DBGU_IER) Enable COMMRX (from ARM) Interrupt */
/* -------- DBGU_IDR : (DBGU Offset: 0x000C) Interrupt Disable Register -------- */
#define DBGU_IDR_RXRDY (0x1u << 0) /**< \brief (DBGU_IDR) Disable RXRDY Interrupt */
#define DBGU_IDR_TXRDY (0x1u << 1) /**< \brief (DBGU_IDR) Disable TXRDY Interrupt */
#define DBGU_IDR_OVRE (0x1u << 5) /**< \brief (DBGU_IDR) Disable Overrun Error Interrupt */
#define DBGU_IDR_FRAME (0x1u << 6) /**< \brief (DBGU_IDR) Disable Framing Error Interrupt */
#define DBGU_IDR_PARE (0x1u << 7) /**< \brief (DBGU_IDR) Disable Parity Error Interrupt */
#define DBGU_IDR_TXEMPTY (0x1u << 9) /**< \brief (DBGU_IDR) Disable TXEMPTY Interrupt */
#define DBGU_IDR_COMMTX (0x1u << 30) /**< \brief (DBGU_IDR) Disable COMMTX (from ARM) Interrupt */
#define DBGU_IDR_COMMRX (0x1u << 31) /**< \brief (DBGU_IDR) Disable COMMRX (from ARM) Interrupt */
/* -------- DBGU_IMR : (DBGU Offset: 0x0010) Interrupt Mask Register -------- */
#define DBGU_IMR_RXRDY (0x1u << 0) /**< \brief (DBGU_IMR) Mask RXRDY Interrupt */
#define DBGU_IMR_TXRDY (0x1u << 1) /**< \brief (DBGU_IMR) Disable TXRDY Interrupt */
#define DBGU_IMR_OVRE (0x1u << 5) /**< \brief (DBGU_IMR) Mask Overrun Error Interrupt */
#define DBGU_IMR_FRAME (0x1u << 6) /**< \brief (DBGU_IMR) Mask Framing Error Interrupt */
#define DBGU_IMR_PARE (0x1u << 7) /**< \brief (DBGU_IMR) Mask Parity Error Interrupt */
#define DBGU_IMR_TXEMPTY (0x1u << 9) /**< \brief (DBGU_IMR) Mask TXEMPTY Interrupt */
#define DBGU_IMR_COMMTX (0x1u << 30) /**< \brief (DBGU_IMR) Mask COMMTX Interrupt */
#define DBGU_IMR_COMMRX (0x1u << 31) /**< \brief (DBGU_IMR) Mask COMMRX Interrupt */
/* -------- DBGU_SR : (DBGU Offset: 0x0014) Status Register -------- */
#define DBGU_SR_RXRDY (0x1u << 0) /**< \brief (DBGU_SR) Receiver Ready */
#define DBGU_SR_TXRDY (0x1u << 1) /**< \brief (DBGU_SR) Transmitter Ready */
#define DBGU_SR_OVRE (0x1u << 5) /**< \brief (DBGU_SR) Overrun Error */
#define DBGU_SR_FRAME (0x1u << 6) /**< \brief (DBGU_SR) Framing Error */
#define DBGU_SR_PARE (0x1u << 7) /**< \brief (DBGU_SR) Parity Error */
#define DBGU_SR_TXEMPTY (0x1u << 9) /**< \brief (DBGU_SR) Transmitter Empty */
#define DBGU_SR_COMMTX (0x1u << 30) /**< \brief (DBGU_SR) Debug Communication Channel Write Status */
#define DBGU_SR_COMMRX (0x1u << 31) /**< \brief (DBGU_SR) Debug Communication Channel Read Status */
/* -------- DBGU_RHR : (DBGU Offset: 0x0018) Receive Holding Register -------- */
#define DBGU_RHR_RXCHR_Pos 0
#define DBGU_RHR_RXCHR_Msk (0xffu << DBGU_RHR_RXCHR_Pos) /**< \brief (DBGU_RHR) Received Character */
/* -------- DBGU_THR : (DBGU Offset: 0x001C) Transmit Holding Register -------- */
#define DBGU_THR_TXCHR_Pos 0
#define DBGU_THR_TXCHR_Msk (0xffu << DBGU_THR_TXCHR_Pos) /**< \brief (DBGU_THR) Character to be Transmitted */
#define DBGU_THR_TXCHR(value) ((DBGU_THR_TXCHR_Msk & ((value) << DBGU_THR_TXCHR_Pos)))
/* -------- DBGU_BRGR : (DBGU Offset: 0x0020) Baud Rate Generator Register -------- */
#define DBGU_BRGR_CD_Pos 0
#define DBGU_BRGR_CD_Msk (0xffffu << DBGU_BRGR_CD_Pos) /**< \brief (DBGU_BRGR) Clock Divisor */
#define   DBGU_BRGR_CD_DISABLED (0x0u << 0) /**< \brief (DBGU_BRGR) DBGU Disabled */
#define   DBGU_BRGR_CD_MCK (0x1u << 0) /**< \brief (DBGU_BRGR) MCK */
/* -------- DBGU_CIDR : (DBGU Offset: 0x0040) Chip ID Register -------- */
#define DBGU_CIDR_VERSION_Pos 0
#define DBGU_CIDR_VERSION_Msk (0x1fu << DBGU_CIDR_VERSION_Pos) /**< \brief (DBGU_CIDR) Version of the Device */
#define DBGU_CIDR_EPROC_Pos 5
#define DBGU_CIDR_EPROC_Msk (0x7u << DBGU_CIDR_EPROC_Pos) /**< \brief (DBGU_CIDR) Embedded Processor */
#define   DBGU_CIDR_EPROC_ARM946ES (0x1u << 5) /**< \brief (DBGU_CIDR) ARM946ES */
#define   DBGU_CIDR_EPROC_ARM7TDMI (0x2u << 5) /**< \brief (DBGU_CIDR) ARM7TDMI */
#define   DBGU_CIDR_EPROC_CM3 (0x3u << 5) /**< \brief (DBGU_CIDR) Cortex-M3 */
#define   DBGU_CIDR_EPROC_ARM920T (0x4u << 5) /**< \brief (DBGU_CIDR) ARM920T */
#define   DBGU_CIDR_EPROC_ARM926EJS (0x5u << 5) /**< \brief (DBGU_CIDR) ARM926EJS */
#define DBGU_CIDR_NVPSIZ_Pos 8
#define DBGU_CIDR_NVPSIZ_Msk (0xfu << DBGU_CIDR_NVPSIZ_Pos) /**< \brief (DBGU_CIDR) Nonvolatile Program Memory Size */
#define   DBGU_CIDR_NVPSIZ_NONE (0x0u << 8) /**< \brief (DBGU_CIDR) None */
#define   DBGU_CIDR_NVPSIZ_8K (0x1u << 8) /**< \brief (DBGU_CIDR) 8 Kbytes */
#define   DBGU_CIDR_NVPSIZ_16K (0x2u << 8) /**< \brief (DBGU_CIDR) 16 Kbytes */
#define   DBGU_CIDR_NVPSIZ_32K (0x3u << 8) /**< \brief (DBGU_CIDR) 32 Kbytes */
#define   DBGU_CIDR_NVPSIZ_64K (0x5u << 8) /**< \brief (DBGU_CIDR) 64 Kbytes */
#define   DBGU_CIDR_NVPSIZ_128K (0x7u << 8) /**< \brief (DBGU_CIDR) 128 Kbytes */
#define   DBGU_CIDR_NVPSIZ_256K (0x9u << 8) /**< \brief (DBGU_CIDR) 256 Kbytes */
#define   DBGU_CIDR_NVPSIZ_512K (0xAu << 8) /**< \brief (DBGU_CIDR) 512 Kbytes */
#define   DBGU_CIDR_NVPSIZ_1024K (0xCu << 8) /**< \brief (DBGU_CIDR) 1024 Kbytes */
#define   DBGU_CIDR_NVPSIZ_2048K (0xEu << 8) /**< \brief (DBGU_CIDR) 2048 Kbytes */
#define DBGU_CIDR_NVPSIZ2_Pos 12
#define DBGU_CIDR_NVPSIZ2_Msk (0xfu << DBGU_CIDR_NVPSIZ2_Pos) /**< \brief (DBGU_CIDR) Second Nonvolatile Program Memory Size */
#define   DBGU_CIDR_NVPSIZ2_NONE (0x0u << 12) /**< \brief (DBGU_CIDR) None */
#define   DBGU_CIDR_NVPSIZ2_8K (0x1u << 12) /**< \brief (DBGU_CIDR) 8 Kbytes */
#define   DBGU_CIDR_NVPSIZ2_16K (0x2u << 12) /**< \brief (DBGU_CIDR) 16 Kbytes */
#define   DBGU_CIDR_NVPSIZ2_32K (0x3u << 12) /**< \brief (DBGU_CIDR) 32 Kbytes */
#define   DBGU_CIDR_NVPSIZ2_64K (0x5u << 12) /**< \brief (DBGU_CIDR) 64 Kbytes */
#define   DBGU_CIDR_NVPSIZ2_128K (0x7u << 12) /**< \brief (DBGU_CIDR) 128 Kbytes */
#define   DBGU_CIDR_NVPSIZ2_256K (0x9u << 12) /**< \brief (DBGU_CIDR) 256 Kbytes */
#define   DBGU_CIDR_NVPSIZ2_512K (0xAu << 12) /**< \brief (DBGU_CIDR) 512 Kbytes */
#define   DBGU_CIDR_NVPSIZ2_1024K (0xCu << 12) /**< \brief (DBGU_CIDR) 1024 Kbytes */
#define   DBGU_CIDR_NVPSIZ2_2048K (0xEu << 12) /**< \brief (DBGU_CIDR) 2048 Kbytes */
#define DBGU_CIDR_SRAMSIZ_Pos 16
#define DBGU_CIDR_SRAMSIZ_Msk (0xfu << DBGU_CIDR_SRAMSIZ_Pos) /**< \brief (DBGU_CIDR) Internal SRAM Size */
#define   DBGU_CIDR_SRAMSIZ_1K (0x1u << 16) /**< \brief (DBGU_CIDR) 1 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_2K (0x2u << 16) /**< \brief (DBGU_CIDR) 2 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_6K (0x3u << 16) /**< \brief (DBGU_CIDR) 6 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_112K (0x4u << 16) /**< \brief (DBGU_CIDR) 112 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_4K (0x5u << 16) /**< \brief (DBGU_CIDR) 4 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_80K (0x6u << 16) /**< \brief (DBGU_CIDR) 80 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_160K (0x7u << 16) /**< \brief (DBGU_CIDR) 160 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_8K (0x8u << 16) /**< \brief (DBGU_CIDR) 8 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_16K (0x9u << 16) /**< \brief (DBGU_CIDR) 16 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_32K (0xAu << 16) /**< \brief (DBGU_CIDR) 32 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_64K (0xBu << 16) /**< \brief (DBGU_CIDR) 64 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_128K (0xCu << 16) /**< \brief (DBGU_CIDR) 128 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_256K (0xDu << 16) /**< \brief (DBGU_CIDR) 256 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_96K (0xEu << 16) /**< \brief (DBGU_CIDR) 96 Kbytes */
#define   DBGU_CIDR_SRAMSIZ_512K (0xFu << 16) /**< \brief (DBGU_CIDR) 512 Kbytes */
#define DBGU_CIDR_ARCH_Pos 20
#define DBGU_CIDR_ARCH_Msk (0xffu << DBGU_CIDR_ARCH_Pos) /**< \brief (DBGU_CIDR) Architecture Identifier */
#define   DBGU_CIDR_ARCH_AT91SAM9xx (0x19u << 20) /**< \brief (DBGU_CIDR) AT91SAM9xx Series */
#define   DBGU_CIDR_ARCH_AT91SAM9XExx (0x29u << 20) /**< \brief (DBGU_CIDR) AT91SAM9XExx Series */
#define   DBGU_CIDR_ARCH_AT91x34 (0x34u << 20) /**< \brief (DBGU_CIDR) AT91x34 Series */
#define   DBGU_CIDR_ARCH_CAP7 (0x37u << 20) /**< \brief (DBGU_CIDR) CAP7 Series */
#define   DBGU_CIDR_ARCH_CAP9 (0x39u << 20) /**< \brief (DBGU_CIDR) CAP9 Series */
#define   DBGU_CIDR_ARCH_CAP11 (0x3Bu << 20) /**< \brief (DBGU_CIDR) CAP11 Series */
#define   DBGU_CIDR_ARCH_AT91x40 (0x40u << 20) /**< \brief (DBGU_CIDR) AT91x40 Series */
#define   DBGU_CIDR_ARCH_AT91x42 (0x42u << 20) /**< \brief (DBGU_CIDR) AT91x42 Series */
#define   DBGU_CIDR_ARCH_AT91x55 (0x55u << 20) /**< \brief (DBGU_CIDR) AT91x55 Series */
#define   DBGU_CIDR_ARCH_AT91SAM7Axx (0x60u << 20) /**< \brief (DBGU_CIDR) AT91SAM7Axx Series */
#define   DBGU_CIDR_ARCH_AT91SAM7AQxx (0x61u << 20) /**< \brief (DBGU_CIDR) AT91SAM7AQxx Series */
#define   DBGU_CIDR_ARCH_AT91x63 (0x63u << 20) /**< \brief (DBGU_CIDR) AT91x63 Series */
#define   DBGU_CIDR_ARCH_AT91SAM7Sxx (0x70u << 20) /**< \brief (DBGU_CIDR) AT91SAM7Sxx Series */
#define   DBGU_CIDR_ARCH_AT91SAM7XCxx (0x71u << 20) /**< \brief (DBGU_CIDR) AT91SAM7XCxx Series */
#define   DBGU_CIDR_ARCH_AT91SAM7SExx (0x72u << 20) /**< \brief (DBGU_CIDR) AT91SAM7SExx Series */
#define   DBGU_CIDR_ARCH_AT91SAM7Lxx (0x73u << 20) /**< \brief (DBGU_CIDR) AT91SAM7Lxx Series */
#define   DBGU_CIDR_ARCH_AT91SAM7Xxx (0x75u << 20) /**< \brief (DBGU_CIDR) AT91SAM7Xxx Series */
#define   DBGU_CIDR_ARCH_AT91SAM7SLxx (0x76u << 20) /**< \brief (DBGU_CIDR) AT91SAM7SLxx Series */
#define   DBGU_CIDR_ARCH_ATSAM3UxC (0x80u << 20) /**< \brief (DBGU_CIDR) ATSAM3UxC Series (100-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3UxE (0x81u << 20) /**< \brief (DBGU_CIDR) ATSAM3UxE Series (144-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3AxC (0x83u << 20) /**< \brief (DBGU_CIDR) ATSAM3AxC Series (100-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3XxC (0x84u << 20) /**< \brief (DBGU_CIDR) ATSAM3XxC Series (100-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3XxE (0x85u << 20) /**< \brief (DBGU_CIDR) ATSAM3XxE Series (144-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3XxG (0x86u << 20) /**< \brief (DBGU_CIDR) ATSAM3XxG Series (208/217-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3SxA (0x88u << 20) /**< \brief (DBGU_CIDR) ATSAM3SxA Series (48-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3SxB (0x89u << 20) /**< \brief (DBGU_CIDR) ATSAM3SxB Series (64-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3SxC (0x8Au << 20) /**< \brief (DBGU_CIDR) ATSAM3SxC Series (100-pin version) */
#define   DBGU_CIDR_ARCH_AT91x92 (0x92u << 20) /**< \brief (DBGU_CIDR) AT91x92 Series */
#define   DBGU_CIDR_ARCH_ATSAM3NxA (0x93u << 20) /**< \brief (DBGU_CIDR) ATSAM3NxA Series (48-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3NxB (0x94u << 20) /**< \brief (DBGU_CIDR) ATSAM3NxB Series (64-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3NxC (0x95u << 20) /**< \brief (DBGU_CIDR) ATSAM3NxC Series (100-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3SDxA (0x98u << 20) /**< \brief (DBGU_CIDR) ATSAM3SDxA Series (48-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3SDxB (0x99u << 20) /**< \brief (DBGU_CIDR) ATSAM3SDxB Series (64-pin version) */
#define   DBGU_CIDR_ARCH_ATSAM3SDxC (0x9Au << 20) /**< \brief (DBGU_CIDR) ATSAM3SDxC Series (100-pin version) */
#define   DBGU_CIDR_ARCH_AT75Cxx (0xF0u << 20) /**< \brief (DBGU_CIDR) AT75Cxx Series */
#define DBGU_CIDR_NVPTYP_Pos 28
#define DBGU_CIDR_NVPTYP_Msk (0x7u << DBGU_CIDR_NVPTYP_Pos) /**< \brief (DBGU_CIDR) Nonvolatile Program Memory Type */
#define   DBGU_CIDR_NVPTYP_ROM (0x0u << 28) /**< \brief (DBGU_CIDR) ROM */
#define   DBGU_CIDR_NVPTYP_ROMLESS (0x1u << 28) /**< \brief (DBGU_CIDR) ROMless or on-chip Flash */
#define   DBGU_CIDR_NVPTYP_FLASH (0x2u << 28) /**< \brief (DBGU_CIDR) Embedded Flash Memory */
#define   DBGU_CIDR_NVPTYP_ROM_FLASH (0x3u << 28) /**< \brief (DBGU_CIDR) ROM and Embedded Flash MemoryNVPSIZ is ROM size      NVPSIZ2 is Flash size */
#define   DBGU_CIDR_NVPTYP_SRAM (0x4u << 28) /**< \brief (DBGU_CIDR) SRAM emulating ROM */
#define DBGU_CIDR_EXT (0x1u << 31) /**< \brief (DBGU_CIDR) Extension Flag */
/* -------- DBGU_EXID : (DBGU Offset: 0x0044) Chip ID Extension Register -------- */
#define DBGU_EXID_EXID_Pos 0
#define DBGU_EXID_EXID_Msk (0xffffffffu << DBGU_EXID_EXID_Pos) /**< \brief (DBGU_EXID) Chip ID Extension */
/* -------- DBGU_FNR : (DBGU Offset: 0x0048) Force NTRST Register -------- */
#define DBGU_FNR_FNTRST (0x1u << 0) /**< \brief (DBGU_FNR) Force NTRST */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Static Memory Controller */
/* ============================================================================= */
/** \addtogroup SAMA5D4_HSMC Static Memory Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief HsmcCs_number hardware registers */
typedef struct {
  __IO uint32_t HSMC_SETUP;   /**< \brief (HsmcCs_number Offset: 0x0) HSMC Setup Register */
  __IO uint32_t HSMC_PULSE;   /**< \brief (HsmcCs_number Offset: 0x4) HSMC Pulse Register */
  __IO uint32_t HSMC_CYCLE;   /**< \brief (HsmcCs_number Offset: 0x8) HSMC Cycle Register */
  __IO uint32_t HSMC_TIMINGS; /**< \brief (HsmcCs_number Offset: 0xC) HSMC Timings Register */
  __IO uint32_t HSMC_MODE;    /**< \brief (HsmcCs_number Offset: 0x10) HSMC Mode Register */
} HsmcCs_number;
/** \brief HsmcPmecc hardware registers */
typedef struct {
  __I uint32_t HSMC_PMECC[11]; /**< \brief (HsmcPmecc Offset: 0x0) PMECC Redundancy x Register */
  __I uint32_t Reserved1[5];
} HsmcPmecc;
/** \brief HsmcRem hardware registers */
typedef struct {
  __I uint32_t HSMC_REM[12]; /**< \brief (HsmcRem Offset: 0x0) PMECC Remainder x Register */
  __I uint32_t Reserved2[4];
} HsmcRem;
/** \brief Hsmc hardware registers */
#define HSMCPMECC_NUMBER 8
#define HSMCREM_NUMBER 8
#define HSMCCS_NUMBER_NUMBER 4
typedef struct {
  __IO uint32_t      HSMC_CFG;                             /**< \brief (Hsmc Offset: 0x000) HSMC NFC Configuration Register */
  __O  uint32_t      HSMC_CTRL;                            /**< \brief (Hsmc Offset: 0x004) HSMC NFC Control Register */
  __I  uint32_t      HSMC_SR;                              /**< \brief (Hsmc Offset: 0x008) HSMC NFC Status Register */
  __O  uint32_t      HSMC_IER;                             /**< \brief (Hsmc Offset: 0x00C) HSMC NFC Interrupt Enable Register */
  __O  uint32_t      HSMC_IDR;                             /**< \brief (Hsmc Offset: 0x010) HSMC NFC Interrupt Disable Register */
  __I  uint32_t      HSMC_IMR;                             /**< \brief (Hsmc Offset: 0x014) HSMC NFC Interrupt Mask Register */
  __IO uint32_t      HSMC_ADDR;                            /**< \brief (Hsmc Offset: 0x018) HSMC NFC Address Cycle Zero Register */
  __IO uint32_t      HSMC_BANK;                            /**< \brief (Hsmc Offset: 0x01C) HSMC Bank Address Register */
  __O  uint32_t      HSMC_ECC_CTRL;                        /**< \brief (Hsmc Offset: 0x020) HSMC ECC Control Register */
  __IO uint32_t      HSMC_ECC_MD;                          /**< \brief (Hsmc Offset: 0x024) HSMC ECC Mode Register */
  __I  uint32_t      HSMC_ECC_SR1;                         /**< \brief (Hsmc Offset: 0x028) HSMC ECC Status 1 Register */
  __I  uint32_t      HSMC_ECC_PR0;                         /**< \brief (Hsmc Offset: 0x02C) HSMC ECC Parity 0 Register */
  __I  uint32_t      HSMC_ECC_PR1;                         /**< \brief (Hsmc Offset: 0x030) HSMC ECC parity 1 Register */
  __I  uint32_t      HSMC_ECC_SR2;                         /**< \brief (Hsmc Offset: 0x034) HSMC ECC status 2 Register */
  __I  uint32_t      HSMC_ECC_PR2;                         /**< \brief (Hsmc Offset: 0x038) HSMC ECC parity 2 Register */
  __I  uint32_t      HSMC_ECC_PR3;                         /**< \brief (Hsmc Offset: 0x03C) HSMC ECC parity 3 Register */
  __I  uint32_t      HSMC_ECC_PR4;                         /**< \brief (Hsmc Offset: 0x040) HSMC ECC parity 4 Register */
  __I  uint32_t      HSMC_ECC_PR5;                         /**< \brief (Hsmc Offset: 0x044) HSMC ECC parity 5 Register */
  __I  uint32_t      HSMC_ECC_PR6;                         /**< \brief (Hsmc Offset: 0x048) HSMC ECC parity 6 Register */
  __I  uint32_t      HSMC_ECC_PR7;                         /**< \brief (Hsmc Offset: 0x04C) HSMC ECC parity 7 Register */
  __I  uint32_t      HSMC_ECC_PR8;                         /**< \brief (Hsmc Offset: 0x050) HSMC ECC parity 8 Register */
  __I  uint32_t      HSMC_ECC_PR9;                         /**< \brief (Hsmc Offset: 0x054) HSMC ECC parity 9 Register */
  __I  uint32_t      HSMC_ECC_PR10;                        /**< \brief (Hsmc Offset: 0x058) HSMC ECC parity 10 Register */
  __I  uint32_t      HSMC_ECC_PR11;                        /**< \brief (Hsmc Offset: 0x05C) HSMC ECC parity 11 Register */
  __I  uint32_t      HSMC_ECC_PR12;                        /**< \brief (Hsmc Offset: 0x060) HSMC ECC parity 12 Register */
  __I  uint32_t      HSMC_ECC_PR13;                        /**< \brief (Hsmc Offset: 0x064) HSMC ECC parity 13 Register */
  __I  uint32_t      HSMC_ECC_PR14;                        /**< \brief (Hsmc Offset: 0x068) HSMC ECC parity 14 Register */
  __I  uint32_t      HSMC_ECC_PR15;                        /**< \brief (Hsmc Offset: 0x06C) HSMC ECC parity 15 Register */
  __IO uint32_t      HSMC_PMECCFG;                         /**< \brief (Hsmc Offset: 0x70) PMECC Configuration Register */
  __IO uint32_t      HSMC_PMECCSAREA;                      /**< \brief (Hsmc Offset: 0x74) PMECC Spare Area Size Register */
  __IO uint32_t      HSMC_PMECCSADDR;                      /**< \brief (Hsmc Offset: 0x78) PMECC Start Address Register */
  __IO uint32_t      HSMC_PMECCEADDR;                      /**< \brief (Hsmc Offset: 0x7C) PMECC End Address Register */
  __I  uint32_t      Reserved1[1];
  __O  uint32_t      HSMC_PMECCTRL;                        /**< \brief (Hsmc Offset: 0x84) PMECC Control Register */
  __I  uint32_t      HSMC_PMECCSR;                         /**< \brief (Hsmc Offset: 0x88) PMECC Status Register */
  __O  uint32_t      HSMC_PMECCIER;                        /**< \brief (Hsmc Offset: 0x8C) PMECC Interrupt Enable register */
  __O  uint32_t      HSMC_PMECCIDR;                        /**< \brief (Hsmc Offset: 0x90) PMECC Interrupt Disable Register */
  __I  uint32_t      HSMC_PMECCIMR;                        /**< \brief (Hsmc Offset: 0x94) PMECC Interrupt Mask Register */
  __I  uint32_t      HSMC_PMECCISR;                        /**< \brief (Hsmc Offset: 0x98) PMECC Interrupt Status Register */
  __I  uint32_t      Reserved2[5];
       HsmcPmecc     HSMC_PMECC[HSMCPMECC_NUMBER];         /**< \brief (Hsmc Offset: 0xB0) sec_num = 0 .. 7 */
       HsmcRem       HSMC_REM[HSMCREM_NUMBER];             /**< \brief (Hsmc Offset: 0x2B0) sec_num = 0 .. 7 */
  __I  uint32_t      Reserved3[20];
  __IO uint32_t      HSMC_ELCFG;                           /**< \brief (Hsmc Offset: 0x500) PMECC Error Location Configuration Register */
  __I  uint32_t      HSMC_ELPRIM;                          /**< \brief (Hsmc Offset: 0x504) PMECC Error Location Primitive Register */
  __O  uint32_t      HSMC_ELEN;                            /**< \brief (Hsmc Offset: 0x508) PMECC Error Location Enable Register */
  __O  uint32_t      HSMC_ELDIS;                           /**< \brief (Hsmc Offset: 0x50C) PMECC Error Location Disable Register */
  __I  uint32_t      HSMC_ELSR;                            /**< \brief (Hsmc Offset: 0x510) PMECC Error Location Status Register */
  __O  uint32_t      HSMC_ELIER;                           /**< \brief (Hsmc Offset: 0x514) PMECC Error Location Interrupt Enable register */
  __O  uint32_t      HSMC_ELIDR;                           /**< \brief (Hsmc Offset: 0x518) PMECC Error Location Interrupt Disable Register */
  __I  uint32_t      HSMC_ELIMR;                           /**< \brief (Hsmc Offset: 0x51C) PMECC Error Location Interrupt Mask Register */
  __I  uint32_t      HSMC_ELISR;                           /**< \brief (Hsmc Offset: 0x520) PMECC Error Location Interrupt Status Register */
  __I  uint32_t      Reserved4[1];
  __IO uint32_t      HSMC_SIGMA0;                          /**< \brief (Hsmc Offset: 0x528) PMECC Error Location SIGMA 0 Register */
  __IO uint32_t      HSMC_SIGMA1;                          /**< \brief (Hsmc Offset: 0x52C) PMECC Error Location SIGMA 1 Register */
  __IO uint32_t      HSMC_SIGMA2;                          /**< \brief (Hsmc Offset: 0x530) PMECC Error Location SIGMA 2 Register */
  __IO uint32_t      HSMC_SIGMA3;                          /**< \brief (Hsmc Offset: 0x534) PMECC Error Location SIGMA 3 Register */
  __IO uint32_t      HSMC_SIGMA4;                          /**< \brief (Hsmc Offset: 0x538) PMECC Error Location SIGMA 4 Register */
  __IO uint32_t      HSMC_SIGMA5;                          /**< \brief (Hsmc Offset: 0x53C) PMECC Error Location SIGMA 5 Register */
  __IO uint32_t      HSMC_SIGMA6;                          /**< \brief (Hsmc Offset: 0x540) PMECC Error Location SIGMA 6 Register */
  __IO uint32_t      HSMC_SIGMA7;                          /**< \brief (Hsmc Offset: 0x544) PMECC Error Location SIGMA 7 Register */
  __IO uint32_t      HSMC_SIGMA8;                          /**< \brief (Hsmc Offset: 0x548) PMECC Error Location SIGMA 8 Register */
  __IO uint32_t      HSMC_SIGMA9;                          /**< \brief (Hsmc Offset: 0x54C) PMECC Error Location SIGMA 9 Register */
  __IO uint32_t      HSMC_SIGMA10;                         /**< \brief (Hsmc Offset: 0x550) PMECC Error Location SIGMA 10 Register */
  __IO uint32_t      HSMC_SIGMA11;                         /**< \brief (Hsmc Offset: 0x554) PMECC Error Location SIGMA 11 Register */
  __IO uint32_t      HSMC_SIGMA12;                         /**< \brief (Hsmc Offset: 0x558) PMECC Error Location SIGMA 12 Register */
  __IO uint32_t      HSMC_SIGMA13;                         /**< \brief (Hsmc Offset: 0x55C) PMECC Error Location SIGMA 13 Register */
  __IO uint32_t      HSMC_SIGMA14;                         /**< \brief (Hsmc Offset: 0x560) PMECC Error Location SIGMA 14 Register */
  __IO uint32_t      HSMC_SIGMA15;                         /**< \brief (Hsmc Offset: 0x564) PMECC Error Location SIGMA 15 Register */
  __IO uint32_t      HSMC_SIGMA16;                         /**< \brief (Hsmc Offset: 0x568) PMECC Error Location SIGMA 16 Register */
  __IO uint32_t      HSMC_SIGMA17;                         /**< \brief (Hsmc Offset: 0x56C) PMECC Error Location SIGMA 17 Register */
  __IO uint32_t      HSMC_SIGMA18;                         /**< \brief (Hsmc Offset: 0x570) PMECC Error Location SIGMA 18 Register */
  __IO uint32_t      HSMC_SIGMA19;                         /**< \brief (Hsmc Offset: 0x574) PMECC Error Location SIGMA 19 Register */
  __IO uint32_t      HSMC_SIGMA20;                         /**< \brief (Hsmc Offset: 0x578) PMECC Error Location SIGMA 20 Register */
  __IO uint32_t      HSMC_SIGMA21;                         /**< \brief (Hsmc Offset: 0x57C) PMECC Error Location SIGMA 21 Register */
  __IO uint32_t      HSMC_SIGMA22;                         /**< \brief (Hsmc Offset: 0x580) PMECC Error Location SIGMA 22 Register */
  __IO uint32_t      HSMC_SIGMA23;                         /**< \brief (Hsmc Offset: 0x584) PMECC Error Location SIGMA 23 Register */
  __IO uint32_t      HSMC_SIGMA24;                         /**< \brief (Hsmc Offset: 0x588) PMECC Error Location SIGMA 24 Register */
  __I  uint32_t      HSMC_ERRLOC[24];                      /**< \brief (Hsmc Offset: 0x58C) PMECC Error Location 0 Register */
  __I  uint32_t      Reserved5[5];
       HsmcCs_number HSMC_CS_NUMBER[HSMCCS_NUMBER_NUMBER]; /**< \brief (Hsmc Offset: 0x600) CS_number = 0 .. 3 */
  __I  uint32_t      Reserved6[20];
  __IO uint32_t      HSMC_OCMS;                            /**< \brief (Hsmc Offset: 0x6A0) HSMC OCMS Register */
  __O  uint32_t      HSMC_KEY1;                            /**< \brief (Hsmc Offset: 0x6A4) HSMC OCMS KEY1 Register */
  __O  uint32_t      HSMC_KEY2;                            /**< \brief (Hsmc Offset: 0x6A8) HSMC OCMS KEY2 Register */
  __I  uint32_t      Reserved7[14];
  __O  uint32_t      HSMC_WPCR;                            /**< \brief (Hsmc Offset: 0x6E4) HSMC Write Protection Control Register */
  __I  uint32_t      HSMC_WPSR;                            /**< \brief (Hsmc Offset: 0x6E8) HSMC Write Protection Status Register */
} Hsmc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- HSMC_CFG : (HSMC Offset: 0x000) HSMC NFC Configuration Register -------- */
#define HSMC_CFG_PAGESIZE_Pos 0
#define HSMC_CFG_PAGESIZE_Msk (0x7u << HSMC_CFG_PAGESIZE_Pos) /**< \brief (HSMC_CFG)  */
#define   HSMC_CFG_PAGESIZE_PS512 (0x0u << 0) /**< \brief (HSMC_CFG) Main area 512 Bytes */
#define   HSMC_CFG_PAGESIZE_PS1024 (0x1u << 0) /**< \brief (HSMC_CFG) Main area 1024 Bytes */
#define   HSMC_CFG_PAGESIZE_PS2048 (0x2u << 0) /**< \brief (HSMC_CFG) Main area 2048 Bytes */
#define   HSMC_CFG_PAGESIZE_PS4096 (0x3u << 0) /**< \brief (HSMC_CFG) Main area 4096 Bytes */
#define   HSMC_CFG_PAGESIZE_PS8192 (0x4u << 0) /**< \brief (HSMC_CFG) Main area 8192 Bytes */
#define HSMC_CFG_WSPARE (0x1u << 8) /**< \brief (HSMC_CFG) Write Spare Area */
#define HSMC_CFG_RSPARE (0x1u << 9) /**< \brief (HSMC_CFG) Read Spare Area */
#define HSMC_CFG_EDGECTRL (0x1u << 12) /**< \brief (HSMC_CFG) Rising/Falling Edge Detection Control */
#define HSMC_CFG_RBEDGE (0x1u << 13) /**< \brief (HSMC_CFG) Ready/Busy Signal Edge Detection */
#define HSMC_CFG_DTOCYC_Pos 16
#define HSMC_CFG_DTOCYC_Msk (0xfu << HSMC_CFG_DTOCYC_Pos) /**< \brief (HSMC_CFG) Data Timeout Cycle Number */
#define HSMC_CFG_DTOCYC(value) ((HSMC_CFG_DTOCYC_Msk & ((value) << HSMC_CFG_DTOCYC_Pos)))
#define HSMC_CFG_DTOMUL_Pos 20
#define HSMC_CFG_DTOMUL_Msk (0x7u << HSMC_CFG_DTOMUL_Pos) /**< \brief (HSMC_CFG) Data Timeout Multiplier */
#define   HSMC_CFG_DTOMUL_X1 (0x0u << 20) /**< \brief (HSMC_CFG) DTOCYC */
#define   HSMC_CFG_DTOMUL_X16 (0x1u << 20) /**< \brief (HSMC_CFG) DTOCYC x 16 */
#define   HSMC_CFG_DTOMUL_X128 (0x2u << 20) /**< \brief (HSMC_CFG) DTOCYC x 128 */
#define   HSMC_CFG_DTOMUL_X256 (0x3u << 20) /**< \brief (HSMC_CFG) DTOCYC x 256 */
#define   HSMC_CFG_DTOMUL_X1024 (0x4u << 20) /**< \brief (HSMC_CFG) DTOCYC x 1024 */
#define   HSMC_CFG_DTOMUL_X4096 (0x5u << 20) /**< \brief (HSMC_CFG) DTOCYC x 4096 */
#define   HSMC_CFG_DTOMUL_X65536 (0x6u << 20) /**< \brief (HSMC_CFG) DTOCYC x 65536 */
#define   HSMC_CFG_DTOMUL_X1048576 (0x7u << 20) /**< \brief (HSMC_CFG) DTOCYC x 1048576 */
#define HSMC_CFG_NFCSPARESIZE_Pos 24
#define HSMC_CFG_NFCSPARESIZE_Msk (0x7fu << HSMC_CFG_NFCSPARESIZE_Pos) /**< \brief (HSMC_CFG) NAND Flash Spare Area Size Retrieved by the Host Controller */
#define HSMC_CFG_NFCSPARESIZE(value) ((HSMC_CFG_NFCSPARESIZE_Msk & ((value) << HSMC_CFG_NFCSPARESIZE_Pos)))
/* -------- HSMC_CTRL : (HSMC Offset: 0x004) HSMC NFC Control Register -------- */
#define HSMC_CTRL_NFCEN (0x1u << 0) /**< \brief (HSMC_CTRL) NAND Flash Controller Enable */
#define HSMC_CTRL_NFCDIS (0x1u << 1) /**< \brief (HSMC_CTRL) NAND Flash Controller Disable */
/* -------- HSMC_SR : (HSMC Offset: 0x008) HSMC NFC Status Register -------- */
#define HSMC_SR_SMCSTS (0x1u << 0) /**< \brief (HSMC_SR) NAND Flash Controller Status (this field cannot be reset) */
#define HSMC_SR_RB_RISE (0x1u << 4) /**< \brief (HSMC_SR) Selected Ready Busy Rising Edge Detected */
#define HSMC_SR_RB_FALL (0x1u << 5) /**< \brief (HSMC_SR) Selected Ready Busy Falling Edge Detected */
#define HSMC_SR_NFCBUSY (0x1u << 8) /**< \brief (HSMC_SR) NFC Busy (this field cannot be reset) */
#define HSMC_SR_NFCWR (0x1u << 11) /**< \brief (HSMC_SR) NFC Write/Read Operation (this field cannot be reset) */
#define HSMC_SR_NFCSID_Pos 12
#define HSMC_SR_NFCSID_Msk (0x7u << HSMC_SR_NFCSID_Pos) /**< \brief (HSMC_SR) NFC Chip Select ID (this field cannot be reset) */
#define HSMC_SR_XFRDONE (0x1u << 16) /**< \brief (HSMC_SR) NFC Data Transfer Terminated */
#define HSMC_SR_CMDDONE (0x1u << 17) /**< \brief (HSMC_SR) Command Done */
#define HSMC_SR_ECCRDY (0x1u << 18) /**< \brief (HSMC_SR) Hamming ECC Ready */
#define HSMC_SR_DTOE (0x1u << 20) /**< \brief (HSMC_SR) Data Timeout Error */
#define HSMC_SR_UNDEF (0x1u << 21) /**< \brief (HSMC_SR) Undefined Area Error */
#define HSMC_SR_AWB (0x1u << 22) /**< \brief (HSMC_SR) Accessing While Busy */
#define HSMC_SR_NFCASE (0x1u << 23) /**< \brief (HSMC_SR) NFC Access Size Error */
#define HSMC_SR_RB_EDGE3 (0x1u << 27) /**< \brief (HSMC_SR) Ready/Busy Line 3 Edge Detected */
/* -------- HSMC_IER : (HSMC Offset: 0x00C) HSMC NFC Interrupt Enable Register -------- */
#define HSMC_IER_RB_RISE (0x1u << 4) /**< \brief (HSMC_IER) Ready Busy Rising Edge Detection Interrupt Enable */
#define HSMC_IER_RB_FALL (0x1u << 5) /**< \brief (HSMC_IER) Ready Busy Falling Edge Detection Interrupt Enable */
#define HSMC_IER_XFRDONE (0x1u << 16) /**< \brief (HSMC_IER) Transfer Done Interrupt Enable */
#define HSMC_IER_CMDDONE (0x1u << 17) /**< \brief (HSMC_IER) Command Done Interrupt Enable */
#define HSMC_IER_DTOE (0x1u << 20) /**< \brief (HSMC_IER) Data Timeout Error Interrupt Enable */
#define HSMC_IER_UNDEF (0x1u << 21) /**< \brief (HSMC_IER) Undefined Area Access Interrupt Enable */
#define HSMC_IER_AWB (0x1u << 22) /**< \brief (HSMC_IER) Accessing While Busy Interrupt Enable */
#define HSMC_IER_NFCASE (0x1u << 23) /**< \brief (HSMC_IER) NFC Access Size Error Interrupt Enable */
#define HSMC_IER_RB_EDGE3 (0x1u << 27) /**< \brief (HSMC_IER) Ready/Busy Line 3 Interrupt Enable */
/* -------- HSMC_IDR : (HSMC Offset: 0x010) HSMC NFC Interrupt Disable Register -------- */
#define HSMC_IDR_RB_RISE (0x1u << 4) /**< \brief (HSMC_IDR) Ready Busy Rising Edge Detection Interrupt Disable */
#define HSMC_IDR_RB_FALL (0x1u << 5) /**< \brief (HSMC_IDR) Ready Busy Falling Edge Detection Interrupt Disable */
#define HSMC_IDR_XFRDONE (0x1u << 16) /**< \brief (HSMC_IDR) Transfer Done Interrupt Disable */
#define HSMC_IDR_CMDDONE (0x1u << 17) /**< \brief (HSMC_IDR) Command Done Interrupt Disable */
#define HSMC_IDR_DTOE (0x1u << 20) /**< \brief (HSMC_IDR) Data Timeout Error Interrupt Disable */
#define HSMC_IDR_UNDEF (0x1u << 21) /**< \brief (HSMC_IDR) Undefined Area Access Interrupt Disable */
#define HSMC_IDR_AWB (0x1u << 22) /**< \brief (HSMC_IDR) Accessing While Busy Interrupt Disable */
#define HSMC_IDR_NFCASE (0x1u << 23) /**< \brief (HSMC_IDR) NFC Access Size Error Interrupt Disable */
#define HSMC_IDR_RB_EDGE3 (0x1u << 27) /**< \brief (HSMC_IDR) Ready/Busy Line 3 Interrupt Disable */
/* -------- HSMC_IMR : (HSMC Offset: 0x014) HSMC NFC Interrupt Mask Register -------- */
#define HSMC_IMR_RB_RISE (0x1u << 4) /**< \brief (HSMC_IMR) Ready Busy Rising Edge Detection Interrupt Mask */
#define HSMC_IMR_RB_FALL (0x1u << 5) /**< \brief (HSMC_IMR) Ready Busy Falling Edge Detection Interrupt Mask */
#define HSMC_IMR_XFRDONE (0x1u << 16) /**< \brief (HSMC_IMR) Transfer Done Interrupt Mask */
#define HSMC_IMR_CMDDONE (0x1u << 17) /**< \brief (HSMC_IMR) Command Done Interrupt Mask */
#define HSMC_IMR_DTOE (0x1u << 20) /**< \brief (HSMC_IMR) Data Timeout Error Interrupt Mask */
#define HSMC_IMR_UNDEF (0x1u << 21) /**< \brief (HSMC_IMR) Undefined Area Access Interrupt Mask5 */
#define HSMC_IMR_AWB (0x1u << 22) /**< \brief (HSMC_IMR) Accessing While Busy Interrupt Mask */
#define HSMC_IMR_NFCASE (0x1u << 23) /**< \brief (HSMC_IMR) NFC Access Size Error Interrupt Mask */
#define HSMC_IMR_RB_EDGE3 (0x1u << 27) /**< \brief (HSMC_IMR) Ready/Busy Line 3 Interrupt Mask */
/* -------- HSMC_ADDR : (HSMC Offset: 0x018) HSMC NFC Address Cycle Zero Register -------- */
#define HSMC_ADDR_ADDR_CYCLE0_Pos 0
#define HSMC_ADDR_ADDR_CYCLE0_Msk (0xffu << HSMC_ADDR_ADDR_CYCLE0_Pos) /**< \brief (HSMC_ADDR) NAND Flash Array Address Cycle 0 */
#define HSMC_ADDR_ADDR_CYCLE0(value) ((HSMC_ADDR_ADDR_CYCLE0_Msk & ((value) << HSMC_ADDR_ADDR_CYCLE0_Pos)))
/* -------- HSMC_BANK : (HSMC Offset: 0x01C) HSMC Bank Address Register -------- */
#define HSMC_BANK_BANK (0x1u << 0) /**< \brief (HSMC_BANK) Bank Identifier */
/* -------- HSMC_ECC_CTRL : (HSMC Offset: 0x020) HSMC ECC Control Register -------- */
#define HSMC_ECC_CTRL_RST (0x1u << 0) /**< \brief (HSMC_ECC_CTRL) Reset ECC */
#define HSMC_ECC_CTRL_SWRST (0x1u << 1) /**< \brief (HSMC_ECC_CTRL) Software Reset */
/* -------- HSMC_ECC_MD : (HSMC Offset: 0x024) HSMC ECC Mode Register -------- */
#define HSMC_ECC_MD_ECC_PAGESIZE_Pos 0
#define HSMC_ECC_MD_ECC_PAGESIZE_Msk (0x3u << HSMC_ECC_MD_ECC_PAGESIZE_Pos) /**< \brief (HSMC_ECC_MD) ECC Page Size */
#define   HSMC_ECC_MD_ECC_PAGESIZE_PS512 (0x0u << 0) /**< \brief (HSMC_ECC_MD) Main area 512 Words */
#define   HSMC_ECC_MD_ECC_PAGESIZE_PS1024 (0x1u << 0) /**< \brief (HSMC_ECC_MD) Main area 1024 Words */
#define   HSMC_ECC_MD_ECC_PAGESIZE_PS2048 (0x2u << 0) /**< \brief (HSMC_ECC_MD) Main area 2048 Words */
#define   HSMC_ECC_MD_ECC_PAGESIZE_PS4096 (0x3u << 0) /**< \brief (HSMC_ECC_MD) Main area 4096 Words */
#define HSMC_ECC_MD_TYPCORREC_Pos 4
#define HSMC_ECC_MD_TYPCORREC_Msk (0x3u << HSMC_ECC_MD_TYPCORREC_Pos) /**< \brief (HSMC_ECC_MD) Type of Correction */
#define   HSMC_ECC_MD_TYPCORREC_CPAGE (0x0u << 4) /**< \brief (HSMC_ECC_MD) 1 bit correction for a page of 512/1024/2048/4096 Bytes  (for 8 or 16-bit NAND Flash) */
#define   HSMC_ECC_MD_TYPCORREC_C256B (0x1u << 4) /**< \brief (HSMC_ECC_MD) 1 bit correction for 256 Bytes of data for a page of 512/2048/4096 bytes (for 8-bit NAND Flash only) */
#define   HSMC_ECC_MD_TYPCORREC_C512B (0x2u << 4) /**< \brief (HSMC_ECC_MD) 1 bit correction for 512 Bytes of data for a page of 512/2048/4096 bytes (for 8-bit NAND Flash only) */
#define HSMC_ECC_MD_HAMMING (0x1u << 8) /**< \brief (HSMC_ECC_MD) Hamming Error Correcting Code Selected */
/* -------- HSMC_ECC_SR1 : (HSMC Offset: 0x028) HSMC ECC Status 1 Register -------- */
#define HSMC_ECC_SR1_RECERR0 (0x1u << 0) /**< \brief (HSMC_ECC_SR1) Recoverable Error */
#define HSMC_ECC_SR1_ECCERR0 (0x1u << 1) /**< \brief (HSMC_ECC_SR1) ECC Error */
#define HSMC_ECC_SR1_MULERR0 (0x1u << 2) /**< \brief (HSMC_ECC_SR1) Multiple Error */
#define HSMC_ECC_SR1_RECERR1 (0x1u << 4) /**< \brief (HSMC_ECC_SR1) Recoverable Error in the page between the 256th and the 511th Bytes or the 512nd and the 1023rd Bytes */
#define HSMC_ECC_SR1_ECCERR1 (0x1u << 5) /**< \brief (HSMC_ECC_SR1) ECC Error in the page between the 256th and the 511th Bytes or between the 512nd and the 1023rd Bytes */
#define HSMC_ECC_SR1_MULERR1 (0x1u << 6) /**< \brief (HSMC_ECC_SR1) Multiple Error in the page between the 256th and the 511th Bytes or between the 512nd and the 1023rd Bytes */
#define HSMC_ECC_SR1_RECERR2 (0x1u << 8) /**< \brief (HSMC_ECC_SR1) Recoverable Error in the page between the 512nd and the 767th Bytes or between the 1024th and the 1535th Bytes */
#define HSMC_ECC_SR1_ECCERR2 (0x1u << 9) /**< \brief (HSMC_ECC_SR1) ECC Error in the page between the 512nd and the 767th Bytes or between the 1024th and the 1535th Bytes */
#define HSMC_ECC_SR1_MULERR2 (0x1u << 10) /**< \brief (HSMC_ECC_SR1) Multiple Error in the page between the 512nd and the 767th Bytes or between the 1024th and the 1535th Bytes */
#define HSMC_ECC_SR1_RECERR3 (0x1u << 12) /**< \brief (HSMC_ECC_SR1) Recoverable Error in the page between the 768th and the 1023rd Bytes or between the 1536th and the 2047th Bytes */
#define HSMC_ECC_SR1_ECCERR3 (0x1u << 13) /**< \brief (HSMC_ECC_SR1) ECC Error in the page between the 768th and the 1023rd Bytes or between the 1536th and the 2047th Bytes */
#define HSMC_ECC_SR1_MULERR3 (0x1u << 14) /**< \brief (HSMC_ECC_SR1) Multiple Error in the page between the 768th and the 1023rd Bytes or between the 1536th and the 2047th Bytes */
#define HSMC_ECC_SR1_RECERR4 (0x1u << 16) /**< \brief (HSMC_ECC_SR1) Recoverable Error in the page between the 1024th and the 1279th Bytes or between the 2048th and the 2559th Bytes */
#define HSMC_ECC_SR1_ECCERR4 (0x1u << 17) /**< \brief (HSMC_ECC_SR1) ECC Error in the page between the 1024th and the 1279th Bytes or between the 2048th and the 2559th Bytes */
#define HSMC_ECC_SR1_MULERR4 (0x1u << 18) /**< \brief (HSMC_ECC_SR1) Multiple Error in the page between the 1024th and the 1279th Bytes or between the 2048th and the 2559th Bytes */
#define HSMC_ECC_SR1_RECERR5 (0x1u << 20) /**< \brief (HSMC_ECC_SR1) Recoverable Error in the page between the 1280th and the 1535th Bytes or between the 2560th and the 3071st Bytes */
#define HSMC_ECC_SR1_ECCERR5 (0x1u << 21) /**< \brief (HSMC_ECC_SR1) ECC Error in the page between the 1280th and the 1535th Bytes or between the 2560th and the 3071st Bytes */
#define HSMC_ECC_SR1_MULERR5 (0x1u << 22) /**< \brief (HSMC_ECC_SR1) Multiple Error in the page between the 1280th and the 1535th Bytes or between the 2560th and the 3071st Bytes */
#define HSMC_ECC_SR1_RECERR6 (0x1u << 24) /**< \brief (HSMC_ECC_SR1) Recoverable Error in the page between the 1536th and the 1791st Bytes or between the 3072nd and the 3583rd Bytes */
#define HSMC_ECC_SR1_ECCERR6 (0x1u << 25) /**< \brief (HSMC_ECC_SR1) ECC Error in the page between the 1536th and the 1791st Bytes or between the 3072nd and the 3583rd Bytes */
#define HSMC_ECC_SR1_MULERR6 (0x1u << 26) /**< \brief (HSMC_ECC_SR1) Multiple Error in the page between the 1536th and the 1791st Bytes or between the 3072nd and the 3583rd Bytes */
#define HSMC_ECC_SR1_RECERR7 (0x1u << 28) /**< \brief (HSMC_ECC_SR1) Recoverable Error in the page between the 1792nd and the 2047th Bytes or between the 3584th and the 4095th Bytes */
#define HSMC_ECC_SR1_ECCERR7 (0x1u << 29) /**< \brief (HSMC_ECC_SR1) ECC Error in the page between the 1792nd and the 2047th Bytes or between the 3584th and the 4095th Bytes */
#define HSMC_ECC_SR1_MULERR7 (0x1u << 30) /**< \brief (HSMC_ECC_SR1) Multiple Error in the page between the 1792nd and the 2047th Bytes or between the 3584th and the 4095th Bytes */
/* -------- HSMC_ECC_PR0 : (HSMC Offset: 0x02C) HSMC ECC Parity 0 Register -------- */
#define HSMC_ECC_PR0_BITADDR_Pos 0
#define HSMC_ECC_PR0_BITADDR_Msk (0xfu << HSMC_ECC_PR0_BITADDR_Pos) /**< \brief (HSMC_ECC_PR0) Bit Address */
#define HSMC_ECC_PR0_WORDADDR_Pos 4
#define HSMC_ECC_PR0_WORDADDR_Msk (0xfffu << HSMC_ECC_PR0_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR0) Word Address */
#define HSMC_ECC_PR0_BITADDR_W9BIT_Pos 0
#define HSMC_ECC_PR0_BITADDR_W9BIT_Msk (0x7u << HSMC_ECC_PR0_BITADDR_W9BIT_Pos) /**< \brief (HSMC_ECC_PR0) Corrupted Bit Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR0_WORDADDR_W9BIT_Pos 3
#define HSMC_ECC_PR0_WORDADDR_W9BIT_Msk (0x1ffu << HSMC_ECC_PR0_WORDADDR_W9BIT_Pos) /**< \brief (HSMC_ECC_PR0) Corrupted Word Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR0_NPARITY_Pos 12
#define HSMC_ECC_PR0_NPARITY_Msk (0xfffu << HSMC_ECC_PR0_NPARITY_Pos) /**< \brief (HSMC_ECC_PR0) Parity N */
#define HSMC_ECC_PR0_BITADDR_W8BIT_Pos 0
#define HSMC_ECC_PR0_BITADDR_W8BIT_Msk (0x7u << HSMC_ECC_PR0_BITADDR_W8BIT_Pos) /**< \brief (HSMC_ECC_PR0) Corrupted Bit Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR0_WORDADDR_W8BIT_Pos 3
#define HSMC_ECC_PR0_WORDADDR_W8BIT_Msk (0xffu << HSMC_ECC_PR0_WORDADDR_W8BIT_Pos) /**< \brief (HSMC_ECC_PR0) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR0_NPARITY_W8BIT_Pos 12
#define HSMC_ECC_PR0_NPARITY_W8BIT_Msk (0x7ffu << HSMC_ECC_PR0_NPARITY_W8BIT_Pos) /**< \brief (HSMC_ECC_PR0) Parity N */
/* -------- HSMC_ECC_PR1 : (HSMC Offset: 0x030) HSMC ECC parity 1 Register -------- */
#define HSMC_ECC_PR1_NPARITY_Pos 0
#define HSMC_ECC_PR1_NPARITY_Msk (0xffffu << HSMC_ECC_PR1_NPARITY_Pos) /**< \brief (HSMC_ECC_PR1) Parity N */
#define HSMC_ECC_PR1_BITADDR_Pos 0
#define HSMC_ECC_PR1_BITADDR_Msk (0x7u << HSMC_ECC_PR1_BITADDR_Pos) /**< \brief (HSMC_ECC_PR1) Corrupted Bit Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR1_WORDADDR_Pos 3
#define HSMC_ECC_PR1_WORDADDR_Msk (0x1ffu << HSMC_ECC_PR1_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR1) Corrupted Word Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR1_NPARITY_W9BIT_Pos 12
#define HSMC_ECC_PR1_NPARITY_W9BIT_Msk (0xfffu << HSMC_ECC_PR1_NPARITY_W9BIT_Pos) /**< \brief (HSMC_ECC_PR1) Parity N */
#define HSMC_ECC_PR1_WORDADDR_W8BIT_Pos 3
#define HSMC_ECC_PR1_WORDADDR_W8BIT_Msk (0xffu << HSMC_ECC_PR1_WORDADDR_W8BIT_Pos) /**< \brief (HSMC_ECC_PR1) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR1_NPARITY_W8BIT_Pos 12
#define HSMC_ECC_PR1_NPARITY_W8BIT_Msk (0x7ffu << HSMC_ECC_PR1_NPARITY_W8BIT_Pos) /**< \brief (HSMC_ECC_PR1) Parity N */
/* -------- HSMC_ECC_SR2 : (HSMC Offset: 0x034) HSMC ECC status 2 Register -------- */
#define HSMC_ECC_SR2_RECERR8 (0x1u << 0) /**< \brief (HSMC_ECC_SR2) Recoverable Error in the page between the 2048th and the 2303rd Bytes */
#define HSMC_ECC_SR2_ECCERR8 (0x1u << 1) /**< \brief (HSMC_ECC_SR2) ECC Error in the page between the 2048th and the 2303rd Bytes */
#define HSMC_ECC_SR2_MULERR8 (0x1u << 2) /**< \brief (HSMC_ECC_SR2) Multiple Error in the page between the 2048th and the 2303rd Bytes */
#define HSMC_ECC_SR2_RECERR9 (0x1u << 4) /**< \brief (HSMC_ECC_SR2) Recoverable Error in the page between the 2304th and the 2559th Bytes */
#define HSMC_ECC_SR2_ECCERR9 (0x1u << 5) /**< \brief (HSMC_ECC_SR2) ECC Error in the page between the 2304th and the 2559th Bytes */
#define HSMC_ECC_SR2_MULERR9 (0x1u << 6) /**< \brief (HSMC_ECC_SR2) Multiple Error in the page between the 2304th and the 2559th Bytes */
#define HSMC_ECC_SR2_RECERR10 (0x1u << 8) /**< \brief (HSMC_ECC_SR2) Recoverable Error in the page between the 2560th and the 2815th Bytes */
#define HSMC_ECC_SR2_ECCERR10 (0x1u << 9) /**< \brief (HSMC_ECC_SR2) ECC Error in the page between the 2560th and the 2815th Bytes */
#define HSMC_ECC_SR2_MULERR10 (0x1u << 10) /**< \brief (HSMC_ECC_SR2) Multiple Error in the page between the 2560th and the 2815th Bytes */
#define HSMC_ECC_SR2_RECERR11 (0x1u << 12) /**< \brief (HSMC_ECC_SR2) Recoverable Error in the page between the 2816th and the 3071st Bytes */
#define HSMC_ECC_SR2_ECCERR11 (0x1u << 13) /**< \brief (HSMC_ECC_SR2) ECC Error in the page between the 2816th and the 3071st Bytes */
#define HSMC_ECC_SR2_MULERR11 (0x1u << 14) /**< \brief (HSMC_ECC_SR2) Multiple Error in the page between the 2816th and the 3071st Bytes */
#define HSMC_ECC_SR2_RECERR12 (0x1u << 16) /**< \brief (HSMC_ECC_SR2) Recoverable Error in the page between the 3072nd and the 3327th Bytes */
#define HSMC_ECC_SR2_ECCERR12 (0x1u << 17) /**< \brief (HSMC_ECC_SR2) ECC Error in the page between the 3072nd and the 3327th Bytes */
#define HSMC_ECC_SR2_MULERR12 (0x1u << 18) /**< \brief (HSMC_ECC_SR2) Multiple Error in the page between the 3072nd and the 3327th Bytes */
#define HSMC_ECC_SR2_RECERR13 (0x1u << 20) /**< \brief (HSMC_ECC_SR2) Recoverable Error in the page between the 3328th and the 3583rd Bytes */
#define HSMC_ECC_SR2_ECCERR13 (0x1u << 21) /**< \brief (HSMC_ECC_SR2) ECC Error in the page between the 3328th and the 3583rd Bytes */
#define HSMC_ECC_SR2_MULERR13 (0x1u << 22) /**< \brief (HSMC_ECC_SR2) Multiple Error in the page between the 3328th and the 3583rd Bytes */
#define HSMC_ECC_SR2_RECERR14 (0x1u << 24) /**< \brief (HSMC_ECC_SR2) Recoverable Error in the page between the 3584th and the 3839th Bytes */
#define HSMC_ECC_SR2_ECCERR14 (0x1u << 25) /**< \brief (HSMC_ECC_SR2) ECC Error in the page between the 3584th and the 3839th Bytes */
#define HSMC_ECC_SR2_MULERR14 (0x1u << 26) /**< \brief (HSMC_ECC_SR2) Multiple Error in the page between the 3584th and the 3839th Bytes */
#define HSMC_ECC_SR2_RECERR15 (0x1u << 28) /**< \brief (HSMC_ECC_SR2) Recoverable Error in the page between the 3840th and the 4095th Bytes */
#define HSMC_ECC_SR2_ECCERR15 (0x1u << 29) /**< \brief (HSMC_ECC_SR2) ECC Error in the page between the 3840th and the 4095th Bytes */
#define HSMC_ECC_SR2_MULERR15 (0x1u << 30) /**< \brief (HSMC_ECC_SR2) Multiple Error in the page between the 3840th and the 4095th Bytes */
/* -------- HSMC_ECC_PR2 : (HSMC Offset: 0x038) HSMC ECC parity 2 Register -------- */
#define HSMC_ECC_PR2_BITADDR_Pos 0
#define HSMC_ECC_PR2_BITADDR_Msk (0x7u << HSMC_ECC_PR2_BITADDR_Pos) /**< \brief (HSMC_ECC_PR2) Corrupted Bit Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR2_WORDADDR_Pos 3
#define HSMC_ECC_PR2_WORDADDR_Msk (0x1ffu << HSMC_ECC_PR2_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR2) Corrupted Word Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR2_NPARITY_Pos 12
#define HSMC_ECC_PR2_NPARITY_Msk (0xfffu << HSMC_ECC_PR2_NPARITY_Pos) /**< \brief (HSMC_ECC_PR2) Parity N */
#define HSMC_ECC_PR2_WORDADDR_W8BIT_Pos 3
#define HSMC_ECC_PR2_WORDADDR_W8BIT_Msk (0xffu << HSMC_ECC_PR2_WORDADDR_W8BIT_Pos) /**< \brief (HSMC_ECC_PR2) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR2_NPARITY_W8BIT_Pos 12
#define HSMC_ECC_PR2_NPARITY_W8BIT_Msk (0x7ffu << HSMC_ECC_PR2_NPARITY_W8BIT_Pos) /**< \brief (HSMC_ECC_PR2) Parity N */
/* -------- HSMC_ECC_PR3 : (HSMC Offset: 0x03C) HSMC ECC parity 3 Register -------- */
#define HSMC_ECC_PR3_BITADDR_Pos 0
#define HSMC_ECC_PR3_BITADDR_Msk (0x7u << HSMC_ECC_PR3_BITADDR_Pos) /**< \brief (HSMC_ECC_PR3) Corrupted Bit Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR3_WORDADDR_Pos 3
#define HSMC_ECC_PR3_WORDADDR_Msk (0x1ffu << HSMC_ECC_PR3_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR3) Corrupted Word Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR3_NPARITY_Pos 12
#define HSMC_ECC_PR3_NPARITY_Msk (0xfffu << HSMC_ECC_PR3_NPARITY_Pos) /**< \brief (HSMC_ECC_PR3) Parity N */
#define HSMC_ECC_PR3_WORDADDR_W8BIT_Pos 3
#define HSMC_ECC_PR3_WORDADDR_W8BIT_Msk (0xffu << HSMC_ECC_PR3_WORDADDR_W8BIT_Pos) /**< \brief (HSMC_ECC_PR3) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR3_NPARITY_W8BIT_Pos 12
#define HSMC_ECC_PR3_NPARITY_W8BIT_Msk (0x7ffu << HSMC_ECC_PR3_NPARITY_W8BIT_Pos) /**< \brief (HSMC_ECC_PR3) Parity N */
/* -------- HSMC_ECC_PR4 : (HSMC Offset: 0x040) HSMC ECC parity 4 Register -------- */
#define HSMC_ECC_PR4_BITADDR_Pos 0
#define HSMC_ECC_PR4_BITADDR_Msk (0x7u << HSMC_ECC_PR4_BITADDR_Pos) /**< \brief (HSMC_ECC_PR4) Corrupted Bit Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR4_WORDADDR_Pos 3
#define HSMC_ECC_PR4_WORDADDR_Msk (0x1ffu << HSMC_ECC_PR4_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR4) Corrupted Word Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR4_NPARITY_Pos 12
#define HSMC_ECC_PR4_NPARITY_Msk (0xfffu << HSMC_ECC_PR4_NPARITY_Pos) /**< \brief (HSMC_ECC_PR4) Parity N */
#define HSMC_ECC_PR4_WORDADDR_W8BIT_Pos 3
#define HSMC_ECC_PR4_WORDADDR_W8BIT_Msk (0xffu << HSMC_ECC_PR4_WORDADDR_W8BIT_Pos) /**< \brief (HSMC_ECC_PR4) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR4_NPARITY_W8BIT_Pos 12
#define HSMC_ECC_PR4_NPARITY_W8BIT_Msk (0x7ffu << HSMC_ECC_PR4_NPARITY_W8BIT_Pos) /**< \brief (HSMC_ECC_PR4) Parity N */
/* -------- HSMC_ECC_PR5 : (HSMC Offset: 0x044) HSMC ECC parity 5 Register -------- */
#define HSMC_ECC_PR5_BITADDR_Pos 0
#define HSMC_ECC_PR5_BITADDR_Msk (0x7u << HSMC_ECC_PR5_BITADDR_Pos) /**< \brief (HSMC_ECC_PR5) Corrupted Bit Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR5_WORDADDR_Pos 3
#define HSMC_ECC_PR5_WORDADDR_Msk (0x1ffu << HSMC_ECC_PR5_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR5) Corrupted Word Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR5_NPARITY_Pos 12
#define HSMC_ECC_PR5_NPARITY_Msk (0xfffu << HSMC_ECC_PR5_NPARITY_Pos) /**< \brief (HSMC_ECC_PR5) Parity N */
#define HSMC_ECC_PR5_WORDADDR_W8BIT_Pos 3
#define HSMC_ECC_PR5_WORDADDR_W8BIT_Msk (0xffu << HSMC_ECC_PR5_WORDADDR_W8BIT_Pos) /**< \brief (HSMC_ECC_PR5) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR5_NPARITY_W8BIT_Pos 12
#define HSMC_ECC_PR5_NPARITY_W8BIT_Msk (0x7ffu << HSMC_ECC_PR5_NPARITY_W8BIT_Pos) /**< \brief (HSMC_ECC_PR5) Parity N */
/* -------- HSMC_ECC_PR6 : (HSMC Offset: 0x048) HSMC ECC parity 6 Register -------- */
#define HSMC_ECC_PR6_BITADDR_Pos 0
#define HSMC_ECC_PR6_BITADDR_Msk (0x7u << HSMC_ECC_PR6_BITADDR_Pos) /**< \brief (HSMC_ECC_PR6) Corrupted Bit Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR6_WORDADDR_Pos 3
#define HSMC_ECC_PR6_WORDADDR_Msk (0x1ffu << HSMC_ECC_PR6_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR6) Corrupted Word Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR6_NPARITY_Pos 12
#define HSMC_ECC_PR6_NPARITY_Msk (0xfffu << HSMC_ECC_PR6_NPARITY_Pos) /**< \brief (HSMC_ECC_PR6) Parity N */
#define HSMC_ECC_PR6_WORDADDR_W8BIT_Pos 3
#define HSMC_ECC_PR6_WORDADDR_W8BIT_Msk (0xffu << HSMC_ECC_PR6_WORDADDR_W8BIT_Pos) /**< \brief (HSMC_ECC_PR6) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR6_NPARITY_W8BIT_Pos 12
#define HSMC_ECC_PR6_NPARITY_W8BIT_Msk (0x7ffu << HSMC_ECC_PR6_NPARITY_W8BIT_Pos) /**< \brief (HSMC_ECC_PR6) Parity N */
/* -------- HSMC_ECC_PR7 : (HSMC Offset: 0x04C) HSMC ECC parity 7 Register -------- */
#define HSMC_ECC_PR7_BITADDR_Pos 0
#define HSMC_ECC_PR7_BITADDR_Msk (0x7u << HSMC_ECC_PR7_BITADDR_Pos) /**< \brief (HSMC_ECC_PR7) Corrupted Bit Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR7_WORDADDR_Pos 3
#define HSMC_ECC_PR7_WORDADDR_Msk (0x1ffu << HSMC_ECC_PR7_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR7) Corrupted Word Address in the Page between (i x 512) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR7_NPARITY_Pos 12
#define HSMC_ECC_PR7_NPARITY_Msk (0xfffu << HSMC_ECC_PR7_NPARITY_Pos) /**< \brief (HSMC_ECC_PR7) Parity N */
#define HSMC_ECC_PR7_WORDADDR_W8BIT_Pos 3
#define HSMC_ECC_PR7_WORDADDR_W8BIT_Msk (0xffu << HSMC_ECC_PR7_WORDADDR_W8BIT_Pos) /**< \brief (HSMC_ECC_PR7) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR7_NPARITY_W8BIT_Pos 12
#define HSMC_ECC_PR7_NPARITY_W8BIT_Msk (0x7ffu << HSMC_ECC_PR7_NPARITY_W8BIT_Pos) /**< \brief (HSMC_ECC_PR7) Parity N */
/* -------- HSMC_ECC_PR8 : (HSMC Offset: 0x050) HSMC ECC parity 8 Register -------- */
#define HSMC_ECC_PR8_BITADDR_Pos 0
#define HSMC_ECC_PR8_BITADDR_Msk (0x7u << HSMC_ECC_PR8_BITADDR_Pos) /**< \brief (HSMC_ECC_PR8) Corrupted Bit Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR8_WORDADDR_Pos 3
#define HSMC_ECC_PR8_WORDADDR_Msk (0xffu << HSMC_ECC_PR8_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR8) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR8_NPARITY_Pos 12
#define HSMC_ECC_PR8_NPARITY_Msk (0x7ffu << HSMC_ECC_PR8_NPARITY_Pos) /**< \brief (HSMC_ECC_PR8) Parity N */
/* -------- HSMC_ECC_PR9 : (HSMC Offset: 0x054) HSMC ECC parity 9 Register -------- */
#define HSMC_ECC_PR9_BITADDR_Pos 0
#define HSMC_ECC_PR9_BITADDR_Msk (0x7u << HSMC_ECC_PR9_BITADDR_Pos) /**< \brief (HSMC_ECC_PR9) Corrupted Bit Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR9_WORDADDR_Pos 3
#define HSMC_ECC_PR9_WORDADDR_Msk (0xffu << HSMC_ECC_PR9_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR9) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR9_NPARITY_Pos 12
#define HSMC_ECC_PR9_NPARITY_Msk (0x7ffu << HSMC_ECC_PR9_NPARITY_Pos) /**< \brief (HSMC_ECC_PR9) Parity N */
/* -------- HSMC_ECC_PR10 : (HSMC Offset: 0x058) HSMC ECC parity 10 Register -------- */
#define HSMC_ECC_PR10_BITADDR_Pos 0
#define HSMC_ECC_PR10_BITADDR_Msk (0x7u << HSMC_ECC_PR10_BITADDR_Pos) /**< \brief (HSMC_ECC_PR10) Corrupted Bit Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR10_WORDADDR_Pos 3
#define HSMC_ECC_PR10_WORDADDR_Msk (0xffu << HSMC_ECC_PR10_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR10) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR10_NPARITY_Pos 12
#define HSMC_ECC_PR10_NPARITY_Msk (0x7ffu << HSMC_ECC_PR10_NPARITY_Pos) /**< \brief (HSMC_ECC_PR10) Parity N */
/* -------- HSMC_ECC_PR11 : (HSMC Offset: 0x05C) HSMC ECC parity 11 Register -------- */
#define HSMC_ECC_PR11_BITADDR_Pos 0
#define HSMC_ECC_PR11_BITADDR_Msk (0x7u << HSMC_ECC_PR11_BITADDR_Pos) /**< \brief (HSMC_ECC_PR11) Corrupted Bit Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR11_WORDADDR_Pos 3
#define HSMC_ECC_PR11_WORDADDR_Msk (0xffu << HSMC_ECC_PR11_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR11) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR11_NPARITY_Pos 12
#define HSMC_ECC_PR11_NPARITY_Msk (0x7ffu << HSMC_ECC_PR11_NPARITY_Pos) /**< \brief (HSMC_ECC_PR11) Parity N */
/* -------- HSMC_ECC_PR12 : (HSMC Offset: 0x060) HSMC ECC parity 12 Register -------- */
#define HSMC_ECC_PR12_BITADDR_Pos 0
#define HSMC_ECC_PR12_BITADDR_Msk (0x7u << HSMC_ECC_PR12_BITADDR_Pos) /**< \brief (HSMC_ECC_PR12) Corrupted Bit Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR12_WORDADDR_Pos 3
#define HSMC_ECC_PR12_WORDADDR_Msk (0xffu << HSMC_ECC_PR12_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR12) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR12_NPARITY_Pos 12
#define HSMC_ECC_PR12_NPARITY_Msk (0x7ffu << HSMC_ECC_PR12_NPARITY_Pos) /**< \brief (HSMC_ECC_PR12) Parity N */
/* -------- HSMC_ECC_PR13 : (HSMC Offset: 0x064) HSMC ECC parity 13 Register -------- */
#define HSMC_ECC_PR13_BITADDR_Pos 0
#define HSMC_ECC_PR13_BITADDR_Msk (0x7u << HSMC_ECC_PR13_BITADDR_Pos) /**< \brief (HSMC_ECC_PR13) Corrupted Bit Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR13_WORDADDR_Pos 3
#define HSMC_ECC_PR13_WORDADDR_Msk (0xffu << HSMC_ECC_PR13_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR13) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR13_NPARITY_Pos 12
#define HSMC_ECC_PR13_NPARITY_Msk (0x7ffu << HSMC_ECC_PR13_NPARITY_Pos) /**< \brief (HSMC_ECC_PR13) Parity N */
/* -------- HSMC_ECC_PR14 : (HSMC Offset: 0x068) HSMC ECC parity 14 Register -------- */
#define HSMC_ECC_PR14_BITADDR_Pos 0
#define HSMC_ECC_PR14_BITADDR_Msk (0x7u << HSMC_ECC_PR14_BITADDR_Pos) /**< \brief (HSMC_ECC_PR14) Corrupted Bit Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR14_WORDADDR_Pos 3
#define HSMC_ECC_PR14_WORDADDR_Msk (0xffu << HSMC_ECC_PR14_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR14) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR14_NPARITY_Pos 12
#define HSMC_ECC_PR14_NPARITY_Msk (0x7ffu << HSMC_ECC_PR14_NPARITY_Pos) /**< \brief (HSMC_ECC_PR14) Parity N */
/* -------- HSMC_ECC_PR15 : (HSMC Offset: 0x06C) HSMC ECC parity 15 Register -------- */
#define HSMC_ECC_PR15_BITADDR_Pos 0
#define HSMC_ECC_PR15_BITADDR_Msk (0x7u << HSMC_ECC_PR15_BITADDR_Pos) /**< \brief (HSMC_ECC_PR15) Corrupted Bit Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR15_WORDADDR_Pos 3
#define HSMC_ECC_PR15_WORDADDR_Msk (0xffu << HSMC_ECC_PR15_WORDADDR_Pos) /**< \brief (HSMC_ECC_PR15) Corrupted Word Address in the Page between (i x 256) and ((i + 1) x 512) - 1) Bytes */
#define HSMC_ECC_PR15_NPARITY_Pos 12
#define HSMC_ECC_PR15_NPARITY_Msk (0x7ffu << HSMC_ECC_PR15_NPARITY_Pos) /**< \brief (HSMC_ECC_PR15) Parity N */
/* -------- HSMC_PMECCFG : (HSMC Offset: 0x70) PMECC Configuration Register -------- */
#define HSMC_PMECCFG_BCH_ERR_Pos 0
#define HSMC_PMECCFG_BCH_ERR_Msk (0x7u << HSMC_PMECCFG_BCH_ERR_Pos) /**< \brief (HSMC_PMECCFG) Error Correcting Capability */
#define   HSMC_PMECCFG_BCH_ERR_BCH_ERR2 (0x0u << 0) /**< \brief (HSMC_PMECCFG) 2 errors */
#define   HSMC_PMECCFG_BCH_ERR_BCH_ERR4 (0x1u << 0) /**< \brief (HSMC_PMECCFG) 4 errors */
#define   HSMC_PMECCFG_BCH_ERR_BCH_ERR8 (0x2u << 0) /**< \brief (HSMC_PMECCFG) 8 errors */
#define   HSMC_PMECCFG_BCH_ERR_BCH_ERR12 (0x3u << 0) /**< \brief (HSMC_PMECCFG) 12 errors */
#define   HSMC_PMECCFG_BCH_ERR_BCH_ERR24 (0x4u << 0) /**< \brief (HSMC_PMECCFG) 24 errors */
#define HSMC_PMECCFG_SECTORSZ (0x1u << 4) /**< \brief (HSMC_PMECCFG) Sector Size */
#define HSMC_PMECCFG_PAGESIZE_Pos 8
#define HSMC_PMECCFG_PAGESIZE_Msk (0x3u << HSMC_PMECCFG_PAGESIZE_Pos) /**< \brief (HSMC_PMECCFG) Number of Sectors in the Page */
#define   HSMC_PMECCFG_PAGESIZE_PAGESIZE_1SEC (0x0u << 8) /**< \brief (HSMC_PMECCFG) 1 sector for main area (512 or 1024 Bytes) */
#define   HSMC_PMECCFG_PAGESIZE_PAGESIZE_2SEC (0x1u << 8) /**< \brief (HSMC_PMECCFG) 2 sectors for main area (1024 or 2048 Bytes) */
#define   HSMC_PMECCFG_PAGESIZE_PAGESIZE_4SEC (0x2u << 8) /**< \brief (HSMC_PMECCFG) 4 sectors for main area (2048 or 4096 Bytes) */
#define   HSMC_PMECCFG_PAGESIZE_PAGESIZE_8SEC (0x3u << 8) /**< \brief (HSMC_PMECCFG) 8 sectors for main area (4096 or 8192 Bytes) */
#define HSMC_PMECCFG_NANDWR (0x1u << 12) /**< \brief (HSMC_PMECCFG) NAND Write Access */
#define HSMC_PMECCFG_SPAREEN (0x1u << 16) /**< \brief (HSMC_PMECCFG) Spare Enable */
#define HSMC_PMECCFG_AUTO (0x1u << 20) /**< \brief (HSMC_PMECCFG) Automatic Mode Enable */
/* -------- HSMC_PMECCSAREA : (HSMC Offset: 0x74) PMECC Spare Area Size Register -------- */
#define HSMC_PMECCSAREA_SPARESIZE_Pos 0
#define HSMC_PMECCSAREA_SPARESIZE_Msk (0x1ffu << HSMC_PMECCSAREA_SPARESIZE_Pos) /**< \brief (HSMC_PMECCSAREA) Spare Area Size */
#define HSMC_PMECCSAREA_SPARESIZE(value) ((HSMC_PMECCSAREA_SPARESIZE_Msk & ((value) << HSMC_PMECCSAREA_SPARESIZE_Pos)))
/* -------- HSMC_PMECCSADDR : (HSMC Offset: 0x78) PMECC Start Address Register -------- */
#define HSMC_PMECCSADDR_STARTADDR_Pos 0
#define HSMC_PMECCSADDR_STARTADDR_Msk (0x1ffu << HSMC_PMECCSADDR_STARTADDR_Pos) /**< \brief (HSMC_PMECCSADDR) ECC Area Start Address */
#define HSMC_PMECCSADDR_STARTADDR(value) ((HSMC_PMECCSADDR_STARTADDR_Msk & ((value) << HSMC_PMECCSADDR_STARTADDR_Pos)))
/* -------- HSMC_PMECCEADDR : (HSMC Offset: 0x7C) PMECC End Address Register -------- */
#define HSMC_PMECCEADDR_ENDADDR_Pos 0
#define HSMC_PMECCEADDR_ENDADDR_Msk (0x1ffu << HSMC_PMECCEADDR_ENDADDR_Pos) /**< \brief (HSMC_PMECCEADDR) ECC Area End Address */
#define HSMC_PMECCEADDR_ENDADDR(value) ((HSMC_PMECCEADDR_ENDADDR_Msk & ((value) << HSMC_PMECCEADDR_ENDADDR_Pos)))
/* -------- HSMC_PMECCTRL : (HSMC Offset: 0x84) PMECC Control Register -------- */
#define HSMC_PMECCTRL_RST (0x1u << 0) /**< \brief (HSMC_PMECCTRL) Reset the PMECC Module */
#define HSMC_PMECCTRL_DATA (0x1u << 1) /**< \brief (HSMC_PMECCTRL) Start a Data Phase */
#define HSMC_PMECCTRL_USER (0x1u << 2) /**< \brief (HSMC_PMECCTRL) Start a User Mode Phase */
#define HSMC_PMECCTRL_ENABLE (0x1u << 4) /**< \brief (HSMC_PMECCTRL) PMECC Enable */
#define HSMC_PMECCTRL_DISABLE (0x1u << 5) /**< \brief (HSMC_PMECCTRL) PMECC Enable */
/* -------- HSMC_PMECCSR : (HSMC Offset: 0x88) PMECC Status Register -------- */
#define HSMC_PMECCSR_BUSY (0x1u << 0) /**< \brief (HSMC_PMECCSR) The kernel of the PMECC is busy */
#define HSMC_PMECCSR_ENABLE (0x1u << 4) /**< \brief (HSMC_PMECCSR) PMECC Enable bit */
/* -------- HSMC_PMECCIER : (HSMC Offset: 0x8C) PMECC Interrupt Enable register -------- */
#define HSMC_PMECCIER_ERRIE (0x1u << 0) /**< \brief (HSMC_PMECCIER) Error Interrupt Enable */
/* -------- HSMC_PMECCIDR : (HSMC Offset: 0x90) PMECC Interrupt Disable Register -------- */
#define HSMC_PMECCIDR_ERRID (0x1u << 0) /**< \brief (HSMC_PMECCIDR) Error Interrupt Disable */
/* -------- HSMC_PMECCIMR : (HSMC Offset: 0x94) PMECC Interrupt Mask Register -------- */
#define HSMC_PMECCIMR_ERRIM (0x1u << 0) /**< \brief (HSMC_PMECCIMR) Error Interrupt Mask */
/* -------- HSMC_PMECCISR : (HSMC Offset: 0x98) PMECC Interrupt Status Register -------- */
#define HSMC_PMECCISR_ERRIS_Pos 0
#define HSMC_PMECCISR_ERRIS_Msk (0xffu << HSMC_PMECCISR_ERRIS_Pos) /**< \brief (HSMC_PMECCISR) Error Interrupt Status Register */
/* -------- HSMC_PMECC[11] : (HSMC Offset: N/A) PMECC Redundancy x Register -------- */
#define HSMC_PMECC_ECC_Pos 0
#define HSMC_PMECC_ECC_Msk (0xffffffffu << HSMC_PMECC_ECC_Pos) /**< \brief (HSMC_PMECC[11]) BCH Redundancy */
/* -------- HSMC_REM[12] : (HSMC Offset: N/A) PMECC Remainder x Register -------- */
#define HSMC_REM_REM2NP1_Pos 0
#define HSMC_REM_REM2NP1_Msk (0x3fffu << HSMC_REM_REM2NP1_Pos) /**< \brief (HSMC_REM[12]) BCH Remainder 2 * N + 1 */
#define HSMC_REM_REM2NP3_Pos 16
#define HSMC_REM_REM2NP3_Msk (0x3fffu << HSMC_REM_REM2NP3_Pos) /**< \brief (HSMC_REM[12]) BCH Remainder 2 * N + 3 */
/* -------- HSMC_ELCFG : (HSMC Offset: 0x500) PMECC Error Location Configuration Register -------- */
#define HSMC_ELCFG_SECTORSZ (0x1u << 0) /**< \brief (HSMC_ELCFG) Sector Size */
#define HSMC_ELCFG_ERRNUM_Pos 16
#define HSMC_ELCFG_ERRNUM_Msk (0x1fu << HSMC_ELCFG_ERRNUM_Pos) /**< \brief (HSMC_ELCFG) Number of Errors */
#define HSMC_ELCFG_ERRNUM(value) ((HSMC_ELCFG_ERRNUM_Msk & ((value) << HSMC_ELCFG_ERRNUM_Pos)))
/* -------- HSMC_ELPRIM : (HSMC Offset: 0x504) PMECC Error Location Primitive Register -------- */
#define HSMC_ELPRIM_PRIMITIV_Pos 0
#define HSMC_ELPRIM_PRIMITIV_Msk (0xffffu << HSMC_ELPRIM_PRIMITIV_Pos) /**< \brief (HSMC_ELPRIM) Primitive Polynomial */
/* -------- HSMC_ELEN : (HSMC Offset: 0x508) PMECC Error Location Enable Register -------- */
#define HSMC_ELEN_ENINIT_Pos 0
#define HSMC_ELEN_ENINIT_Msk (0x3fffu << HSMC_ELEN_ENINIT_Pos) /**< \brief (HSMC_ELEN) Error Location Enable */
#define HSMC_ELEN_ENINIT(value) ((HSMC_ELEN_ENINIT_Msk & ((value) << HSMC_ELEN_ENINIT_Pos)))
/* -------- HSMC_ELDIS : (HSMC Offset: 0x50C) PMECC Error Location Disable Register -------- */
#define HSMC_ELDIS_DIS (0x1u << 0) /**< \brief (HSMC_ELDIS) Disable Error Location Engine */
/* -------- HSMC_ELSR : (HSMC Offset: 0x510) PMECC Error Location Status Register -------- */
#define HSMC_ELSR_BUSY (0x1u << 0) /**< \brief (HSMC_ELSR) Error Location Engine Busy */
/* -------- HSMC_ELIER : (HSMC Offset: 0x514) PMECC Error Location Interrupt Enable register -------- */
#define HSMC_ELIER_DONE (0x1u << 0) /**< \brief (HSMC_ELIER) Computation Terminated Interrupt Enable */
/* -------- HSMC_ELIDR : (HSMC Offset: 0x518) PMECC Error Location Interrupt Disable Register -------- */
#define HSMC_ELIDR_DONE (0x1u << 0) /**< \brief (HSMC_ELIDR) Computation Terminated Interrupt Disable */
/* -------- HSMC_ELIMR : (HSMC Offset: 0x51C) PMECC Error Location Interrupt Mask Register -------- */
#define HSMC_ELIMR_DONE (0x1u << 0) /**< \brief (HSMC_ELIMR) Computation Terminated Interrupt Mask */
/* -------- HSMC_ELISR : (HSMC Offset: 0x520) PMECC Error Location Interrupt Status Register -------- */
#define HSMC_ELISR_DONE (0x1u << 0) /**< \brief (HSMC_ELISR) Computation Terminated Interrupt Status */
#define HSMC_ELISR_ERR_CNT_Pos 8
#define HSMC_ELISR_ERR_CNT_Msk (0x1fu << HSMC_ELISR_ERR_CNT_Pos) /**< \brief (HSMC_ELISR) Error Counter value */
/* -------- HSMC_SIGMA0 : (HSMC Offset: 0x528) PMECC Error Location SIGMA 0 Register -------- */
#define HSMC_SIGMA0_SIGMA0_Pos 0
#define HSMC_SIGMA0_SIGMA0_Msk (0x3fffu << HSMC_SIGMA0_SIGMA0_Pos) /**< \brief (HSMC_SIGMA0) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA0_SIGMA0(value) ((HSMC_SIGMA0_SIGMA0_Msk & ((value) << HSMC_SIGMA0_SIGMA0_Pos)))
/* -------- HSMC_SIGMA1 : (HSMC Offset: 0x52C) PMECC Error Location SIGMA 1 Register -------- */
#define HSMC_SIGMA1_SIGMA1_Pos 0
#define HSMC_SIGMA1_SIGMA1_Msk (0x3fffu << HSMC_SIGMA1_SIGMA1_Pos) /**< \brief (HSMC_SIGMA1) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA1_SIGMA1(value) ((HSMC_SIGMA1_SIGMA1_Msk & ((value) << HSMC_SIGMA1_SIGMA1_Pos)))
/* -------- HSMC_SIGMA2 : (HSMC Offset: 0x530) PMECC Error Location SIGMA 2 Register -------- */
#define HSMC_SIGMA2_SIGMA2_Pos 0
#define HSMC_SIGMA2_SIGMA2_Msk (0x3fffu << HSMC_SIGMA2_SIGMA2_Pos) /**< \brief (HSMC_SIGMA2) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA2_SIGMA2(value) ((HSMC_SIGMA2_SIGMA2_Msk & ((value) << HSMC_SIGMA2_SIGMA2_Pos)))
/* -------- HSMC_SIGMA3 : (HSMC Offset: 0x534) PMECC Error Location SIGMA 3 Register -------- */
#define HSMC_SIGMA3_SIGMA3_Pos 0
#define HSMC_SIGMA3_SIGMA3_Msk (0x3fffu << HSMC_SIGMA3_SIGMA3_Pos) /**< \brief (HSMC_SIGMA3) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA3_SIGMA3(value) ((HSMC_SIGMA3_SIGMA3_Msk & ((value) << HSMC_SIGMA3_SIGMA3_Pos)))
/* -------- HSMC_SIGMA4 : (HSMC Offset: 0x538) PMECC Error Location SIGMA 4 Register -------- */
#define HSMC_SIGMA4_SIGMA4_Pos 0
#define HSMC_SIGMA4_SIGMA4_Msk (0x3fffu << HSMC_SIGMA4_SIGMA4_Pos) /**< \brief (HSMC_SIGMA4) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA4_SIGMA4(value) ((HSMC_SIGMA4_SIGMA4_Msk & ((value) << HSMC_SIGMA4_SIGMA4_Pos)))
/* -------- HSMC_SIGMA5 : (HSMC Offset: 0x53C) PMECC Error Location SIGMA 5 Register -------- */
#define HSMC_SIGMA5_SIGMA5_Pos 0
#define HSMC_SIGMA5_SIGMA5_Msk (0x3fffu << HSMC_SIGMA5_SIGMA5_Pos) /**< \brief (HSMC_SIGMA5) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA5_SIGMA5(value) ((HSMC_SIGMA5_SIGMA5_Msk & ((value) << HSMC_SIGMA5_SIGMA5_Pos)))
/* -------- HSMC_SIGMA6 : (HSMC Offset: 0x540) PMECC Error Location SIGMA 6 Register -------- */
#define HSMC_SIGMA6_SIGMA6_Pos 0
#define HSMC_SIGMA6_SIGMA6_Msk (0x3fffu << HSMC_SIGMA6_SIGMA6_Pos) /**< \brief (HSMC_SIGMA6) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA6_SIGMA6(value) ((HSMC_SIGMA6_SIGMA6_Msk & ((value) << HSMC_SIGMA6_SIGMA6_Pos)))
/* -------- HSMC_SIGMA7 : (HSMC Offset: 0x544) PMECC Error Location SIGMA 7 Register -------- */
#define HSMC_SIGMA7_SIGMA7_Pos 0
#define HSMC_SIGMA7_SIGMA7_Msk (0x3fffu << HSMC_SIGMA7_SIGMA7_Pos) /**< \brief (HSMC_SIGMA7) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA7_SIGMA7(value) ((HSMC_SIGMA7_SIGMA7_Msk & ((value) << HSMC_SIGMA7_SIGMA7_Pos)))
/* -------- HSMC_SIGMA8 : (HSMC Offset: 0x548) PMECC Error Location SIGMA 8 Register -------- */
#define HSMC_SIGMA8_SIGMA8_Pos 0
#define HSMC_SIGMA8_SIGMA8_Msk (0x3fffu << HSMC_SIGMA8_SIGMA8_Pos) /**< \brief (HSMC_SIGMA8) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA8_SIGMA8(value) ((HSMC_SIGMA8_SIGMA8_Msk & ((value) << HSMC_SIGMA8_SIGMA8_Pos)))
/* -------- HSMC_SIGMA9 : (HSMC Offset: 0x54C) PMECC Error Location SIGMA 9 Register -------- */
#define HSMC_SIGMA9_SIGMA9_Pos 0
#define HSMC_SIGMA9_SIGMA9_Msk (0x3fffu << HSMC_SIGMA9_SIGMA9_Pos) /**< \brief (HSMC_SIGMA9) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA9_SIGMA9(value) ((HSMC_SIGMA9_SIGMA9_Msk & ((value) << HSMC_SIGMA9_SIGMA9_Pos)))
/* -------- HSMC_SIGMA10 : (HSMC Offset: 0x550) PMECC Error Location SIGMA 10 Register -------- */
#define HSMC_SIGMA10_SIGMA10_Pos 0
#define HSMC_SIGMA10_SIGMA10_Msk (0x3fffu << HSMC_SIGMA10_SIGMA10_Pos) /**< \brief (HSMC_SIGMA10) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA10_SIGMA10(value) ((HSMC_SIGMA10_SIGMA10_Msk & ((value) << HSMC_SIGMA10_SIGMA10_Pos)))
/* -------- HSMC_SIGMA11 : (HSMC Offset: 0x554) PMECC Error Location SIGMA 11 Register -------- */
#define HSMC_SIGMA11_SIGMA11_Pos 0
#define HSMC_SIGMA11_SIGMA11_Msk (0x3fffu << HSMC_SIGMA11_SIGMA11_Pos) /**< \brief (HSMC_SIGMA11) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA11_SIGMA11(value) ((HSMC_SIGMA11_SIGMA11_Msk & ((value) << HSMC_SIGMA11_SIGMA11_Pos)))
/* -------- HSMC_SIGMA12 : (HSMC Offset: 0x558) PMECC Error Location SIGMA 12 Register -------- */
#define HSMC_SIGMA12_SIGMA12_Pos 0
#define HSMC_SIGMA12_SIGMA12_Msk (0x3fffu << HSMC_SIGMA12_SIGMA12_Pos) /**< \brief (HSMC_SIGMA12) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA12_SIGMA12(value) ((HSMC_SIGMA12_SIGMA12_Msk & ((value) << HSMC_SIGMA12_SIGMA12_Pos)))
/* -------- HSMC_SIGMA13 : (HSMC Offset: 0x55C) PMECC Error Location SIGMA 13 Register -------- */
#define HSMC_SIGMA13_SIGMA13_Pos 0
#define HSMC_SIGMA13_SIGMA13_Msk (0x3fffu << HSMC_SIGMA13_SIGMA13_Pos) /**< \brief (HSMC_SIGMA13) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA13_SIGMA13(value) ((HSMC_SIGMA13_SIGMA13_Msk & ((value) << HSMC_SIGMA13_SIGMA13_Pos)))
/* -------- HSMC_SIGMA14 : (HSMC Offset: 0x560) PMECC Error Location SIGMA 14 Register -------- */
#define HSMC_SIGMA14_SIGMA14_Pos 0
#define HSMC_SIGMA14_SIGMA14_Msk (0x3fffu << HSMC_SIGMA14_SIGMA14_Pos) /**< \brief (HSMC_SIGMA14) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA14_SIGMA14(value) ((HSMC_SIGMA14_SIGMA14_Msk & ((value) << HSMC_SIGMA14_SIGMA14_Pos)))
/* -------- HSMC_SIGMA15 : (HSMC Offset: 0x564) PMECC Error Location SIGMA 15 Register -------- */
#define HSMC_SIGMA15_SIGMA15_Pos 0
#define HSMC_SIGMA15_SIGMA15_Msk (0x3fffu << HSMC_SIGMA15_SIGMA15_Pos) /**< \brief (HSMC_SIGMA15) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA15_SIGMA15(value) ((HSMC_SIGMA15_SIGMA15_Msk & ((value) << HSMC_SIGMA15_SIGMA15_Pos)))
/* -------- HSMC_SIGMA16 : (HSMC Offset: 0x568) PMECC Error Location SIGMA 16 Register -------- */
#define HSMC_SIGMA16_SIGMA16_Pos 0
#define HSMC_SIGMA16_SIGMA16_Msk (0x3fffu << HSMC_SIGMA16_SIGMA16_Pos) /**< \brief (HSMC_SIGMA16) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA16_SIGMA16(value) ((HSMC_SIGMA16_SIGMA16_Msk & ((value) << HSMC_SIGMA16_SIGMA16_Pos)))
/* -------- HSMC_SIGMA17 : (HSMC Offset: 0x56C) PMECC Error Location SIGMA 17 Register -------- */
#define HSMC_SIGMA17_SIGMA17_Pos 0
#define HSMC_SIGMA17_SIGMA17_Msk (0x3fffu << HSMC_SIGMA17_SIGMA17_Pos) /**< \brief (HSMC_SIGMA17) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA17_SIGMA17(value) ((HSMC_SIGMA17_SIGMA17_Msk & ((value) << HSMC_SIGMA17_SIGMA17_Pos)))
/* -------- HSMC_SIGMA18 : (HSMC Offset: 0x570) PMECC Error Location SIGMA 18 Register -------- */
#define HSMC_SIGMA18_SIGMA18_Pos 0
#define HSMC_SIGMA18_SIGMA18_Msk (0x3fffu << HSMC_SIGMA18_SIGMA18_Pos) /**< \brief (HSMC_SIGMA18) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA18_SIGMA18(value) ((HSMC_SIGMA18_SIGMA18_Msk & ((value) << HSMC_SIGMA18_SIGMA18_Pos)))
/* -------- HSMC_SIGMA19 : (HSMC Offset: 0x574) PMECC Error Location SIGMA 19 Register -------- */
#define HSMC_SIGMA19_SIGMA19_Pos 0
#define HSMC_SIGMA19_SIGMA19_Msk (0x3fffu << HSMC_SIGMA19_SIGMA19_Pos) /**< \brief (HSMC_SIGMA19) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA19_SIGMA19(value) ((HSMC_SIGMA19_SIGMA19_Msk & ((value) << HSMC_SIGMA19_SIGMA19_Pos)))
/* -------- HSMC_SIGMA20 : (HSMC Offset: 0x578) PMECC Error Location SIGMA 20 Register -------- */
#define HSMC_SIGMA20_SIGMA20_Pos 0
#define HSMC_SIGMA20_SIGMA20_Msk (0x3fffu << HSMC_SIGMA20_SIGMA20_Pos) /**< \brief (HSMC_SIGMA20) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA20_SIGMA20(value) ((HSMC_SIGMA20_SIGMA20_Msk & ((value) << HSMC_SIGMA20_SIGMA20_Pos)))
/* -------- HSMC_SIGMA21 : (HSMC Offset: 0x57C) PMECC Error Location SIGMA 21 Register -------- */
#define HSMC_SIGMA21_SIGMA21_Pos 0
#define HSMC_SIGMA21_SIGMA21_Msk (0x3fffu << HSMC_SIGMA21_SIGMA21_Pos) /**< \brief (HSMC_SIGMA21) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA21_SIGMA21(value) ((HSMC_SIGMA21_SIGMA21_Msk & ((value) << HSMC_SIGMA21_SIGMA21_Pos)))
/* -------- HSMC_SIGMA22 : (HSMC Offset: 0x580) PMECC Error Location SIGMA 22 Register -------- */
#define HSMC_SIGMA22_SIGMA22_Pos 0
#define HSMC_SIGMA22_SIGMA22_Msk (0x3fffu << HSMC_SIGMA22_SIGMA22_Pos) /**< \brief (HSMC_SIGMA22) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA22_SIGMA22(value) ((HSMC_SIGMA22_SIGMA22_Msk & ((value) << HSMC_SIGMA22_SIGMA22_Pos)))
/* -------- HSMC_SIGMA23 : (HSMC Offset: 0x584) PMECC Error Location SIGMA 23 Register -------- */
#define HSMC_SIGMA23_SIGMA23_Pos 0
#define HSMC_SIGMA23_SIGMA23_Msk (0x3fffu << HSMC_SIGMA23_SIGMA23_Pos) /**< \brief (HSMC_SIGMA23) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA23_SIGMA23(value) ((HSMC_SIGMA23_SIGMA23_Msk & ((value) << HSMC_SIGMA23_SIGMA23_Pos)))
/* -------- HSMC_SIGMA24 : (HSMC Offset: 0x588) PMECC Error Location SIGMA 24 Register -------- */
#define HSMC_SIGMA24_SIGMA24_Pos 0
#define HSMC_SIGMA24_SIGMA24_Msk (0x3fffu << HSMC_SIGMA24_SIGMA24_Pos) /**< \brief (HSMC_SIGMA24) Coefficient of degree x in the SIGMA polynomial. */
#define HSMC_SIGMA24_SIGMA24(value) ((HSMC_SIGMA24_SIGMA24_Msk & ((value) << HSMC_SIGMA24_SIGMA24_Pos)))
/* -------- HSMC_ERRLOC[24] : (HSMC Offset: 0x58C) PMECC Error Location 0 Register -------- */
#define HSMC_ERRLOC_ERRLOCN_Pos 0
#define HSMC_ERRLOC_ERRLOCN_Msk (0x3fffu << HSMC_ERRLOC_ERRLOCN_Pos) /**< \brief (HSMC_ERRLOC[24]) Error Position within the Set {sector area, spare area} */
/* -------- HSMC_SETUP : (HSMC Offset: N/A) HSMC Setup Register -------- */
#define HSMC_SETUP_NWE_SETUP_Pos 0
#define HSMC_SETUP_NWE_SETUP_Msk (0x3fu << HSMC_SETUP_NWE_SETUP_Pos) /**< \brief (HSMC_SETUP) NWE Setup Length */
#define HSMC_SETUP_NWE_SETUP(value) ((HSMC_SETUP_NWE_SETUP_Msk & ((value) << HSMC_SETUP_NWE_SETUP_Pos)))
#define HSMC_SETUP_NCS_WR_SETUP_Pos 8
#define HSMC_SETUP_NCS_WR_SETUP_Msk (0x3fu << HSMC_SETUP_NCS_WR_SETUP_Pos) /**< \brief (HSMC_SETUP) NCS Setup Length in Write Access */
#define HSMC_SETUP_NCS_WR_SETUP(value) ((HSMC_SETUP_NCS_WR_SETUP_Msk & ((value) << HSMC_SETUP_NCS_WR_SETUP_Pos)))
#define HSMC_SETUP_NRD_SETUP_Pos 16
#define HSMC_SETUP_NRD_SETUP_Msk (0x3fu << HSMC_SETUP_NRD_SETUP_Pos) /**< \brief (HSMC_SETUP) NRD Setup Length */
#define HSMC_SETUP_NRD_SETUP(value) ((HSMC_SETUP_NRD_SETUP_Msk & ((value) << HSMC_SETUP_NRD_SETUP_Pos)))
#define HSMC_SETUP_NCS_RD_SETUP_Pos 24
#define HSMC_SETUP_NCS_RD_SETUP_Msk (0x3fu << HSMC_SETUP_NCS_RD_SETUP_Pos) /**< \brief (HSMC_SETUP) NCS Setup Length in Read Access */
#define HSMC_SETUP_NCS_RD_SETUP(value) ((HSMC_SETUP_NCS_RD_SETUP_Msk & ((value) << HSMC_SETUP_NCS_RD_SETUP_Pos)))
/* -------- HSMC_PULSE : (HSMC Offset: N/A) HSMC Pulse Register -------- */
#define HSMC_PULSE_NWE_PULSE_Pos 0
#define HSMC_PULSE_NWE_PULSE_Msk (0x3fu << HSMC_PULSE_NWE_PULSE_Pos) /**< \brief (HSMC_PULSE) NWE Pulse Length */
#define HSMC_PULSE_NWE_PULSE(value) ((HSMC_PULSE_NWE_PULSE_Msk & ((value) << HSMC_PULSE_NWE_PULSE_Pos)))
#define HSMC_PULSE_NCS_WR_PULSE_Pos 8
#define HSMC_PULSE_NCS_WR_PULSE_Msk (0x3fu << HSMC_PULSE_NCS_WR_PULSE_Pos) /**< \brief (HSMC_PULSE) NCS Pulse Length in WRITE Access */
#define HSMC_PULSE_NCS_WR_PULSE(value) ((HSMC_PULSE_NCS_WR_PULSE_Msk & ((value) << HSMC_PULSE_NCS_WR_PULSE_Pos)))
#define HSMC_PULSE_NRD_PULSE_Pos 16
#define HSMC_PULSE_NRD_PULSE_Msk (0x3fu << HSMC_PULSE_NRD_PULSE_Pos) /**< \brief (HSMC_PULSE) NRD Pulse Length */
#define HSMC_PULSE_NRD_PULSE(value) ((HSMC_PULSE_NRD_PULSE_Msk & ((value) << HSMC_PULSE_NRD_PULSE_Pos)))
#define HSMC_PULSE_NCS_RD_PULSE_Pos 24
#define HSMC_PULSE_NCS_RD_PULSE_Msk (0x3fu << HSMC_PULSE_NCS_RD_PULSE_Pos) /**< \brief (HSMC_PULSE) NCS Pulse Length in READ Access */
#define HSMC_PULSE_NCS_RD_PULSE(value) ((HSMC_PULSE_NCS_RD_PULSE_Msk & ((value) << HSMC_PULSE_NCS_RD_PULSE_Pos)))
/* -------- HSMC_CYCLE : (HSMC Offset: N/A) HSMC Cycle Register -------- */
#define HSMC_CYCLE_NWE_CYCLE_Pos 0
#define HSMC_CYCLE_NWE_CYCLE_Msk (0x1ffu << HSMC_CYCLE_NWE_CYCLE_Pos) /**< \brief (HSMC_CYCLE) Total Write Cycle Length */
#define HSMC_CYCLE_NWE_CYCLE(value) ((HSMC_CYCLE_NWE_CYCLE_Msk & ((value) << HSMC_CYCLE_NWE_CYCLE_Pos)))
#define HSMC_CYCLE_NRD_CYCLE_Pos 16
#define HSMC_CYCLE_NRD_CYCLE_Msk (0x1ffu << HSMC_CYCLE_NRD_CYCLE_Pos) /**< \brief (HSMC_CYCLE) Total Read Cycle Length */
#define HSMC_CYCLE_NRD_CYCLE(value) ((HSMC_CYCLE_NRD_CYCLE_Msk & ((value) << HSMC_CYCLE_NRD_CYCLE_Pos)))
/* -------- HSMC_TIMINGS : (HSMC Offset: N/A) HSMC Timings Register -------- */
#define HSMC_TIMINGS_TCLR_Pos 0
#define HSMC_TIMINGS_TCLR_Msk (0xfu << HSMC_TIMINGS_TCLR_Pos) /**< \brief (HSMC_TIMINGS) CLE to REN Low Delay */
#define HSMC_TIMINGS_TCLR(value) ((HSMC_TIMINGS_TCLR_Msk & ((value) << HSMC_TIMINGS_TCLR_Pos)))
#define HSMC_TIMINGS_TADL_Pos 4
#define HSMC_TIMINGS_TADL_Msk (0xfu << HSMC_TIMINGS_TADL_Pos) /**< \brief (HSMC_TIMINGS) ALE to Data Start */
#define HSMC_TIMINGS_TADL(value) ((HSMC_TIMINGS_TADL_Msk & ((value) << HSMC_TIMINGS_TADL_Pos)))
#define HSMC_TIMINGS_TAR_Pos 8
#define HSMC_TIMINGS_TAR_Msk (0xfu << HSMC_TIMINGS_TAR_Pos) /**< \brief (HSMC_TIMINGS) ALE to REN Low Delay */
#define HSMC_TIMINGS_TAR(value) ((HSMC_TIMINGS_TAR_Msk & ((value) << HSMC_TIMINGS_TAR_Pos)))
#define HSMC_TIMINGS_OCMS (0x1u << 12) /**< \brief (HSMC_TIMINGS) Off Chip Memory Scrambling Enable */
#define HSMC_TIMINGS_TRR_Pos 16
#define HSMC_TIMINGS_TRR_Msk (0xfu << HSMC_TIMINGS_TRR_Pos) /**< \brief (HSMC_TIMINGS) Ready to REN Low Delay */
#define HSMC_TIMINGS_TRR(value) ((HSMC_TIMINGS_TRR_Msk & ((value) << HSMC_TIMINGS_TRR_Pos)))
#define HSMC_TIMINGS_TWB_Pos 24
#define HSMC_TIMINGS_TWB_Msk (0xfu << HSMC_TIMINGS_TWB_Pos) /**< \brief (HSMC_TIMINGS) WEN High to REN to Busy */
#define HSMC_TIMINGS_TWB(value) ((HSMC_TIMINGS_TWB_Msk & ((value) << HSMC_TIMINGS_TWB_Pos)))
#define HSMC_TIMINGS_RBNSEL_Pos 28
#define HSMC_TIMINGS_RBNSEL_Msk (0x7u << HSMC_TIMINGS_RBNSEL_Pos) /**< \brief (HSMC_TIMINGS) Ready/Busy Line Selection */
#define HSMC_TIMINGS_RBNSEL(value) ((HSMC_TIMINGS_RBNSEL_Msk & ((value) << HSMC_TIMINGS_RBNSEL_Pos)))
#define HSMC_TIMINGS_NFSEL (0x1u << 31) /**< \brief (HSMC_TIMINGS) NAND Flash Selection */
/* -------- HSMC_MODE : (HSMC Offset: N/A) HSMC Mode Register -------- */
#define HSMC_MODE_READ_MODE (0x1u << 0) /**< \brief (HSMC_MODE)  */
#define   HSMC_MODE_READ_MODE_NCS_CTRL (0x0u << 0) /**< \brief (HSMC_MODE) The Read operation is controlled by the NCS signal. */
#define   HSMC_MODE_READ_MODE_NRD_CTRL (0x1u << 0) /**< \brief (HSMC_MODE) The Read operation is controlled by the NRD signal. */
#define HSMC_MODE_WRITE_MODE (0x1u << 1) /**< \brief (HSMC_MODE)  */
#define   HSMC_MODE_WRITE_MODE_NCS_CTRL (0x0u << 1) /**< \brief (HSMC_MODE) The Write operation is controller by the NCS signal. */
#define   HSMC_MODE_WRITE_MODE_NWE_CTRL (0x1u << 1) /**< \brief (HSMC_MODE) The Write operation is controlled by the NWE signal. */
#define HSMC_MODE_EXNW_MODE_Pos 4
#define HSMC_MODE_EXNW_MODE_Msk (0x3u << HSMC_MODE_EXNW_MODE_Pos) /**< \brief (HSMC_MODE) NWAIT Mode */
#define   HSMC_MODE_EXNW_MODE_DISABLED (0x0u << 4) /**< \brief (HSMC_MODE) Disabled */
#define   HSMC_MODE_EXNW_MODE_FROZEN (0x2u << 4) /**< \brief (HSMC_MODE) Frozen Mode */
#define   HSMC_MODE_EXNW_MODE_READY (0x3u << 4) /**< \brief (HSMC_MODE) Ready Mode */
#define HSMC_MODE_BAT (0x1u << 8) /**< \brief (HSMC_MODE) Byte Access Type */
#define HSMC_MODE_DBW (0x1u << 12) /**< \brief (HSMC_MODE) Data Bus Width */
#define   HSMC_MODE_DBW_BIT_8 (0x0u << 12) /**< \brief (HSMC_MODE) 8-bit bus */
#define   HSMC_MODE_DBW_BIT_16 (0x1u << 12) /**< \brief (HSMC_MODE) 16-bit bus */
#define HSMC_MODE_TDF_CYCLES_Pos 16
#define HSMC_MODE_TDF_CYCLES_Msk (0xfu << HSMC_MODE_TDF_CYCLES_Pos) /**< \brief (HSMC_MODE) Data Float Time */
#define HSMC_MODE_TDF_CYCLES(value) ((HSMC_MODE_TDF_CYCLES_Msk & ((value) << HSMC_MODE_TDF_CYCLES_Pos)))
#define HSMC_MODE_TDF_MODE (0x1u << 20) /**< \brief (HSMC_MODE) TDF Optimization */
/* -------- HSMC_OCMS : (HSMC Offset: 0x6A0) HSMC OCMS Register -------- */
#define HSMC_OCMS_SMSE (0x1u << 0) /**< \brief (HSMC_OCMS) Static Memory Controller Scrambling Enable */
#define HSMC_OCMS_SRSE (0x1u << 1) /**< \brief (HSMC_OCMS) SRAM Scrambling Enable */
/* -------- HSMC_KEY1 : (HSMC Offset: 0x6A4) HSMC OCMS KEY1 Register -------- */
#define HSMC_KEY1_KEY1_Pos 0
#define HSMC_KEY1_KEY1_Msk (0xffffffffu << HSMC_KEY1_KEY1_Pos) /**< \brief (HSMC_KEY1) Off Chip Memory Scrambling (OCMS) Key Part 1 */
#define HSMC_KEY1_KEY1(value) ((HSMC_KEY1_KEY1_Msk & ((value) << HSMC_KEY1_KEY1_Pos)))
/* -------- HSMC_KEY2 : (HSMC Offset: 0x6A8) HSMC OCMS KEY2 Register -------- */
#define HSMC_KEY2_KEY2_Pos 0
#define HSMC_KEY2_KEY2_Msk (0xffffffffu << HSMC_KEY2_KEY2_Pos) /**< \brief (HSMC_KEY2) Off Chip Memory Scrambling (OCMS) Key Part 2 */
#define HSMC_KEY2_KEY2(value) ((HSMC_KEY2_KEY2_Msk & ((value) << HSMC_KEY2_KEY2_Pos)))
/* -------- HSMC_WPCR : (HSMC Offset: 0x6E4) HSMC Write Protection Control Register -------- */
#define HSMC_WPCR_WP_EN (0x1u << 0) /**< \brief (HSMC_WPCR) Write Protection Enable */
#define HSMC_WPCR_WP_KEY_Pos 8
#define HSMC_WPCR_WP_KEY_Msk (0xffffffu << HSMC_WPCR_WP_KEY_Pos) /**< \brief (HSMC_WPCR) Write Protection KEY password */
#define HSMC_WPCR_WP_KEY(value) ((HSMC_WPCR_WP_KEY_Msk & ((value) << HSMC_WPCR_WP_KEY_Pos)))
/* -------- HSMC_WPSR : (HSMC Offset: 0x6E8) HSMC Write Protection Status Register -------- */
#define HSMC_WPSR_WP_VS_Pos 0
#define HSMC_WPSR_WP_VS_Msk (0xfu << HSMC_WPSR_WP_VS_Pos) /**< \brief (HSMC_WPSR) Write Protection Violation Status */
#define HSMC_WPSR_WP_VSRC_Pos 8
#define HSMC_WPSR_WP_VSRC_Msk (0xffffu << HSMC_WPSR_WP_VSRC_Pos) /**< \brief (HSMC_WPSR) Write Protection Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR High Speed MultiMedia Card Interface */
/* ============================================================================= */
/** \addtogroup SAMA5D4_HSMCI High Speed MultiMedia Card Interface */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Hsmci hardware registers */
typedef struct {
  __O  uint32_t HSMCI_CR;        /**< \brief (Hsmci Offset: 0x00) Control Register */
  __IO uint32_t HSMCI_MR;        /**< \brief (Hsmci Offset: 0x04) Mode Register */
  __IO uint32_t HSMCI_DTOR;      /**< \brief (Hsmci Offset: 0x08) Data Timeout Register */
  __IO uint32_t HSMCI_SDCR;      /**< \brief (Hsmci Offset: 0x0C) SD/SDIO Card Register */
  __IO uint32_t HSMCI_ARGR;      /**< \brief (Hsmci Offset: 0x10) Argument Register */
  __O  uint32_t HSMCI_CMDR;      /**< \brief (Hsmci Offset: 0x14) Command Register */
  __IO uint32_t HSMCI_BLKR;      /**< \brief (Hsmci Offset: 0x18) Block Register */
  __IO uint32_t HSMCI_CSTOR;     /**< \brief (Hsmci Offset: 0x1C) Completion Signal Timeout Register */
  __I  uint32_t HSMCI_RSPR[4];   /**< \brief (Hsmci Offset: 0x20) Response Register */
  __I  uint32_t HSMCI_RDR;       /**< \brief (Hsmci Offset: 0x30) Receive Data Register */
  __O  uint32_t HSMCI_TDR;       /**< \brief (Hsmci Offset: 0x34) Transmit Data Register */
  __I  uint32_t Reserved1[2];
  __I  uint32_t HSMCI_SR;        /**< \brief (Hsmci Offset: 0x40) Status Register */
  __O  uint32_t HSMCI_IER;       /**< \brief (Hsmci Offset: 0x44) Interrupt Enable Register */
  __O  uint32_t HSMCI_IDR;       /**< \brief (Hsmci Offset: 0x48) Interrupt Disable Register */
  __I  uint32_t HSMCI_IMR;       /**< \brief (Hsmci Offset: 0x4C) Interrupt Mask Register */
  __IO uint32_t HSMCI_DMA;       /**< \brief (Hsmci Offset: 0x50) DMA Configuration Register */
  __IO uint32_t HSMCI_CFG;       /**< \brief (Hsmci Offset: 0x54) Configuration Register */
  __I  uint32_t Reserved2[35];
  __IO uint32_t HSMCI_WPMR;      /**< \brief (Hsmci Offset: 0xE4) Write Protection Mode Register */
  __I  uint32_t HSMCI_WPSR;      /**< \brief (Hsmci Offset: 0xE8) Write Protection Status Register */
  __I  uint32_t Reserved3[69];
  __IO uint32_t HSMCI_FIFO[256]; /**< \brief (Hsmci Offset: 0x200) FIFO Memory Aperture0 */
} Hsmci;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- HSMCI_CR : (HSMCI Offset: 0x00) Control Register -------- */
#define HSMCI_CR_MCIEN (0x1u << 0) /**< \brief (HSMCI_CR) Multi-Media Interface Enable */
#define HSMCI_CR_MCIDIS (0x1u << 1) /**< \brief (HSMCI_CR) Multi-Media Interface Disable */
#define HSMCI_CR_PWSEN (0x1u << 2) /**< \brief (HSMCI_CR) Power Save Mode Enable */
#define HSMCI_CR_PWSDIS (0x1u << 3) /**< \brief (HSMCI_CR) Power Save Mode Disable */
#define HSMCI_CR_SWRST (0x1u << 7) /**< \brief (HSMCI_CR) Software Reset */
/* -------- HSMCI_MR : (HSMCI Offset: 0x04) Mode Register -------- */
#define HSMCI_MR_CLKDIV_Pos 0
#define HSMCI_MR_CLKDIV_Msk (0xffu << HSMCI_MR_CLKDIV_Pos) /**< \brief (HSMCI_MR) Clock Divider */
#define HSMCI_MR_CLKDIV(value) ((HSMCI_MR_CLKDIV_Msk & ((value) << HSMCI_MR_CLKDIV_Pos)))
#define HSMCI_MR_PWSDIV_Pos 8
#define HSMCI_MR_PWSDIV_Msk (0x7u << HSMCI_MR_PWSDIV_Pos) /**< \brief (HSMCI_MR) Power Saving Divider */
#define HSMCI_MR_PWSDIV(value) ((HSMCI_MR_PWSDIV_Msk & ((value) << HSMCI_MR_PWSDIV_Pos)))
#define HSMCI_MR_RDPROOF (0x1u << 11) /**< \brief (HSMCI_MR) Read Proof Enable */
#define HSMCI_MR_WRPROOF (0x1u << 12) /**< \brief (HSMCI_MR) Write Proof Enable */
#define HSMCI_MR_FBYTE (0x1u << 13) /**< \brief (HSMCI_MR) Force Byte Transfer */
#define HSMCI_MR_PADV (0x1u << 14) /**< \brief (HSMCI_MR) Padding Value */
#define HSMCI_MR_CLKODD (0x1u << 16) /**< \brief (HSMCI_MR) Clock divider is odd */
/* -------- HSMCI_DTOR : (HSMCI Offset: 0x08) Data Timeout Register -------- */
#define HSMCI_DTOR_DTOCYC_Pos 0
#define HSMCI_DTOR_DTOCYC_Msk (0xfu << HSMCI_DTOR_DTOCYC_Pos) /**< \brief (HSMCI_DTOR) Data Timeout Cycle Number */
#define HSMCI_DTOR_DTOCYC(value) ((HSMCI_DTOR_DTOCYC_Msk & ((value) << HSMCI_DTOR_DTOCYC_Pos)))
#define HSMCI_DTOR_DTOMUL_Pos 4
#define HSMCI_DTOR_DTOMUL_Msk (0x7u << HSMCI_DTOR_DTOMUL_Pos) /**< \brief (HSMCI_DTOR) Data Timeout Multiplier */
#define   HSMCI_DTOR_DTOMUL_1 (0x0u << 4) /**< \brief (HSMCI_DTOR) DTOCYC */
#define   HSMCI_DTOR_DTOMUL_16 (0x1u << 4) /**< \brief (HSMCI_DTOR) DTOCYC x 16 */
#define   HSMCI_DTOR_DTOMUL_128 (0x2u << 4) /**< \brief (HSMCI_DTOR) DTOCYC x 128 */
#define   HSMCI_DTOR_DTOMUL_256 (0x3u << 4) /**< \brief (HSMCI_DTOR) DTOCYC x 256 */
#define   HSMCI_DTOR_DTOMUL_1024 (0x4u << 4) /**< \brief (HSMCI_DTOR) DTOCYC x 1024 */
#define   HSMCI_DTOR_DTOMUL_4096 (0x5u << 4) /**< \brief (HSMCI_DTOR) DTOCYC x 4096 */
#define   HSMCI_DTOR_DTOMUL_65536 (0x6u << 4) /**< \brief (HSMCI_DTOR) DTOCYC x 65536 */
#define   HSMCI_DTOR_DTOMUL_1048576 (0x7u << 4) /**< \brief (HSMCI_DTOR) DTOCYC x 1048576 */
/* -------- HSMCI_SDCR : (HSMCI Offset: 0x0C) SD/SDIO Card Register -------- */
#define HSMCI_SDCR_SDCSEL_Pos 0
#define HSMCI_SDCR_SDCSEL_Msk (0x3u << HSMCI_SDCR_SDCSEL_Pos) /**< \brief (HSMCI_SDCR) SDCard/SDIO Slot */
#define   HSMCI_SDCR_SDCSEL_SLOTA (0x0u << 0) /**< \brief (HSMCI_SDCR) Slot A is selected. */
#define   HSMCI_SDCR_SDCSEL_SLOTB (0x1u << 0) /**< \brief (HSMCI_SDCR) Slot B is selected. */
#define HSMCI_SDCR_SDCBUS_Pos 6
#define HSMCI_SDCR_SDCBUS_Msk (0x3u << HSMCI_SDCR_SDCBUS_Pos) /**< \brief (HSMCI_SDCR) SDCard/SDIO Bus Width */
#define   HSMCI_SDCR_SDCBUS_1 (0x0u << 6) /**< \brief (HSMCI_SDCR) 1 bit */
#define   HSMCI_SDCR_SDCBUS_4 (0x2u << 6) /**< \brief (HSMCI_SDCR) 4 bit */
#define   HSMCI_SDCR_SDCBUS_8 (0x3u << 6) /**< \brief (HSMCI_SDCR) 8 bit */
/* -------- HSMCI_ARGR : (HSMCI Offset: 0x10) Argument Register -------- */
#define HSMCI_ARGR_ARG_Pos 0
#define HSMCI_ARGR_ARG_Msk (0xffffffffu << HSMCI_ARGR_ARG_Pos) /**< \brief (HSMCI_ARGR) Command Argument */
#define HSMCI_ARGR_ARG(value) ((HSMCI_ARGR_ARG_Msk & ((value) << HSMCI_ARGR_ARG_Pos)))
/* -------- HSMCI_CMDR : (HSMCI Offset: 0x14) Command Register -------- */
#define HSMCI_CMDR_CMDNB_Pos 0
#define HSMCI_CMDR_CMDNB_Msk (0x3fu << HSMCI_CMDR_CMDNB_Pos) /**< \brief (HSMCI_CMDR) Command Number */
#define HSMCI_CMDR_CMDNB(value) ((HSMCI_CMDR_CMDNB_Msk & ((value) << HSMCI_CMDR_CMDNB_Pos)))
#define HSMCI_CMDR_RSPTYP_Pos 6
#define HSMCI_CMDR_RSPTYP_Msk (0x3u << HSMCI_CMDR_RSPTYP_Pos) /**< \brief (HSMCI_CMDR) Response Type */
#define   HSMCI_CMDR_RSPTYP_NORESP (0x0u << 6) /**< \brief (HSMCI_CMDR) No response. */
#define   HSMCI_CMDR_RSPTYP_48_BIT (0x1u << 6) /**< \brief (HSMCI_CMDR) 48-bit response. */
#define   HSMCI_CMDR_RSPTYP_136_BIT (0x2u << 6) /**< \brief (HSMCI_CMDR) 136-bit response. */
#define   HSMCI_CMDR_RSPTYP_R1B (0x3u << 6) /**< \brief (HSMCI_CMDR) R1b response type */
#define HSMCI_CMDR_SPCMD_Pos 8
#define HSMCI_CMDR_SPCMD_Msk (0x7u << HSMCI_CMDR_SPCMD_Pos) /**< \brief (HSMCI_CMDR) Special Command */
#define   HSMCI_CMDR_SPCMD_STD (0x0u << 8) /**< \brief (HSMCI_CMDR) Not a special CMD. */
#define   HSMCI_CMDR_SPCMD_INIT (0x1u << 8) /**< \brief (HSMCI_CMDR) Initialization CMD: 74 clock cycles for initialization sequence. */
#define   HSMCI_CMDR_SPCMD_SYNC (0x2u << 8) /**< \brief (HSMCI_CMDR) Synchronized CMD: Wait for the end of the current data block transfer before sending the pending command. */
#define   HSMCI_CMDR_SPCMD_CE_ATA (0x3u << 8) /**< \brief (HSMCI_CMDR) CE-ATA Completion Signal disable Command. The host cancels the ability for the device to return a command completion signal on the command line. */
#define   HSMCI_CMDR_SPCMD_IT_CMD (0x4u << 8) /**< \brief (HSMCI_CMDR) Interrupt command: Corresponds to the Interrupt Mode (CMD40). */
#define   HSMCI_CMDR_SPCMD_IT_RESP (0x5u << 8) /**< \brief (HSMCI_CMDR) Interrupt response: Corresponds to the Interrupt Mode (CMD40). */
#define   HSMCI_CMDR_SPCMD_BOR (0x6u << 8) /**< \brief (HSMCI_CMDR) Boot Operation Request. Start a boot operation mode, the host processor can read boot data from the MMC device directly. */
#define   HSMCI_CMDR_SPCMD_EBO (0x7u << 8) /**< \brief (HSMCI_CMDR) End Boot Operation. This command allows the host processor to terminate the boot operation mode. */
#define HSMCI_CMDR_OPDCMD (0x1u << 11) /**< \brief (HSMCI_CMDR) Open Drain Command */
#define   HSMCI_CMDR_OPDCMD_PUSHPULL (0x0u << 11) /**< \brief (HSMCI_CMDR) Push pull command. */
#define   HSMCI_CMDR_OPDCMD_OPENDRAIN (0x1u << 11) /**< \brief (HSMCI_CMDR) Open drain command. */
#define HSMCI_CMDR_MAXLAT (0x1u << 12) /**< \brief (HSMCI_CMDR) Max Latency for Command to Response */
#define   HSMCI_CMDR_MAXLAT_5 (0x0u << 12) /**< \brief (HSMCI_CMDR) 5-cycle max latency. */
#define   HSMCI_CMDR_MAXLAT_64 (0x1u << 12) /**< \brief (HSMCI_CMDR) 64-cycle max latency. */
#define HSMCI_CMDR_TRCMD_Pos 16
#define HSMCI_CMDR_TRCMD_Msk (0x3u << HSMCI_CMDR_TRCMD_Pos) /**< \brief (HSMCI_CMDR) Transfer Command */
#define   HSMCI_CMDR_TRCMD_NO_DATA (0x0u << 16) /**< \brief (HSMCI_CMDR) No data transfer */
#define   HSMCI_CMDR_TRCMD_START_DATA (0x1u << 16) /**< \brief (HSMCI_CMDR) Start data transfer */
#define   HSMCI_CMDR_TRCMD_STOP_DATA (0x2u << 16) /**< \brief (HSMCI_CMDR) Stop data transfer */
#define HSMCI_CMDR_TRDIR (0x1u << 18) /**< \brief (HSMCI_CMDR) Transfer Direction */
#define   HSMCI_CMDR_TRDIR_WRITE (0x0u << 18) /**< \brief (HSMCI_CMDR) Write. */
#define   HSMCI_CMDR_TRDIR_READ (0x1u << 18) /**< \brief (HSMCI_CMDR) Read. */
#define HSMCI_CMDR_TRTYP_Pos 19
#define HSMCI_CMDR_TRTYP_Msk (0x7u << HSMCI_CMDR_TRTYP_Pos) /**< \brief (HSMCI_CMDR) Transfer Type */
#define   HSMCI_CMDR_TRTYP_SINGLE (0x0u << 19) /**< \brief (HSMCI_CMDR) MMC/SD Card Single Block */
#define   HSMCI_CMDR_TRTYP_MULTIPLE (0x1u << 19) /**< \brief (HSMCI_CMDR) MMC/SD Card Multiple Block */
#define   HSMCI_CMDR_TRTYP_STREAM (0x2u << 19) /**< \brief (HSMCI_CMDR) MMC Stream */
#define   HSMCI_CMDR_TRTYP_BYTE (0x4u << 19) /**< \brief (HSMCI_CMDR) SDIO Byte */
#define   HSMCI_CMDR_TRTYP_BLOCK (0x5u << 19) /**< \brief (HSMCI_CMDR) SDIO Block */
#define HSMCI_CMDR_IOSPCMD_Pos 24
#define HSMCI_CMDR_IOSPCMD_Msk (0x3u << HSMCI_CMDR_IOSPCMD_Pos) /**< \brief (HSMCI_CMDR) SDIO Special Command */
#define   HSMCI_CMDR_IOSPCMD_STD (0x0u << 24) /**< \brief (HSMCI_CMDR) Not an SDIO Special Command */
#define   HSMCI_CMDR_IOSPCMD_SUSPEND (0x1u << 24) /**< \brief (HSMCI_CMDR) SDIO Suspend Command */
#define   HSMCI_CMDR_IOSPCMD_RESUME (0x2u << 24) /**< \brief (HSMCI_CMDR) SDIO Resume Command */
#define HSMCI_CMDR_ATACS (0x1u << 26) /**< \brief (HSMCI_CMDR) ATA with Command Completion Signal */
#define   HSMCI_CMDR_ATACS_NORMAL (0x0u << 26) /**< \brief (HSMCI_CMDR) Normal operation mode. */
#define   HSMCI_CMDR_ATACS_COMPLETION (0x1u << 26) /**< \brief (HSMCI_CMDR) This bit indicates that a completion signal is expected within a programmed amount of time (HSMCI_CSTOR). */
#define HSMCI_CMDR_BOOT_ACK (0x1u << 27) /**< \brief (HSMCI_CMDR) Boot Operation Acknowledge. */
/* -------- HSMCI_BLKR : (HSMCI Offset: 0x18) Block Register -------- */
#define HSMCI_BLKR_BCNT_Pos 0
#define HSMCI_BLKR_BCNT_Msk (0xffffu << HSMCI_BLKR_BCNT_Pos) /**< \brief (HSMCI_BLKR) MMC/SDIO Block Count - SDIO Byte Count */
#define HSMCI_BLKR_BCNT(value) ((HSMCI_BLKR_BCNT_Msk & ((value) << HSMCI_BLKR_BCNT_Pos)))
#define HSMCI_BLKR_BLKLEN_Pos 16
#define HSMCI_BLKR_BLKLEN_Msk (0xffffu << HSMCI_BLKR_BLKLEN_Pos) /**< \brief (HSMCI_BLKR) Data Block Length */
#define HSMCI_BLKR_BLKLEN(value) ((HSMCI_BLKR_BLKLEN_Msk & ((value) << HSMCI_BLKR_BLKLEN_Pos)))
/* -------- HSMCI_CSTOR : (HSMCI Offset: 0x1C) Completion Signal Timeout Register -------- */
#define HSMCI_CSTOR_CSTOCYC_Pos 0
#define HSMCI_CSTOR_CSTOCYC_Msk (0xfu << HSMCI_CSTOR_CSTOCYC_Pos) /**< \brief (HSMCI_CSTOR) Completion Signal Timeout Cycle Number */
#define HSMCI_CSTOR_CSTOCYC(value) ((HSMCI_CSTOR_CSTOCYC_Msk & ((value) << HSMCI_CSTOR_CSTOCYC_Pos)))
#define HSMCI_CSTOR_CSTOMUL_Pos 4
#define HSMCI_CSTOR_CSTOMUL_Msk (0x7u << HSMCI_CSTOR_CSTOMUL_Pos) /**< \brief (HSMCI_CSTOR) Completion Signal Timeout Multiplier */
#define   HSMCI_CSTOR_CSTOMUL_1 (0x0u << 4) /**< \brief (HSMCI_CSTOR) CSTOCYC x 1 */
#define   HSMCI_CSTOR_CSTOMUL_16 (0x1u << 4) /**< \brief (HSMCI_CSTOR) CSTOCYC x 16 */
#define   HSMCI_CSTOR_CSTOMUL_128 (0x2u << 4) /**< \brief (HSMCI_CSTOR) CSTOCYC x 128 */
#define   HSMCI_CSTOR_CSTOMUL_256 (0x3u << 4) /**< \brief (HSMCI_CSTOR) CSTOCYC x 256 */
#define   HSMCI_CSTOR_CSTOMUL_1024 (0x4u << 4) /**< \brief (HSMCI_CSTOR) CSTOCYC x 1024 */
#define   HSMCI_CSTOR_CSTOMUL_4096 (0x5u << 4) /**< \brief (HSMCI_CSTOR) CSTOCYC x 4096 */
#define   HSMCI_CSTOR_CSTOMUL_65536 (0x6u << 4) /**< \brief (HSMCI_CSTOR) CSTOCYC x 65536 */
#define   HSMCI_CSTOR_CSTOMUL_1048576 (0x7u << 4) /**< \brief (HSMCI_CSTOR) CSTOCYC x 1048576 */
/* -------- HSMCI_RSPR[4] : (HSMCI Offset: 0x20) Response Register -------- */
#define HSMCI_RSPR_RSP_Pos 0
#define HSMCI_RSPR_RSP_Msk (0xffffffffu << HSMCI_RSPR_RSP_Pos) /**< \brief (HSMCI_RSPR[4]) Response */
/* -------- HSMCI_RDR : (HSMCI Offset: 0x30) Receive Data Register -------- */
#define HSMCI_RDR_DATA_Pos 0
#define HSMCI_RDR_DATA_Msk (0xffffffffu << HSMCI_RDR_DATA_Pos) /**< \brief (HSMCI_RDR) Data to Read */
/* -------- HSMCI_TDR : (HSMCI Offset: 0x34) Transmit Data Register -------- */
#define HSMCI_TDR_DATA_Pos 0
#define HSMCI_TDR_DATA_Msk (0xffffffffu << HSMCI_TDR_DATA_Pos) /**< \brief (HSMCI_TDR) Data to Write */
#define HSMCI_TDR_DATA(value) ((HSMCI_TDR_DATA_Msk & ((value) << HSMCI_TDR_DATA_Pos)))
/* -------- HSMCI_SR : (HSMCI Offset: 0x40) Status Register -------- */
#define HSMCI_SR_CMDRDY (0x1u << 0) /**< \brief (HSMCI_SR) Command Ready */
#define HSMCI_SR_RXRDY (0x1u << 1) /**< \brief (HSMCI_SR) Receiver Ready */
#define HSMCI_SR_TXRDY (0x1u << 2) /**< \brief (HSMCI_SR) Transmit Ready */
#define HSMCI_SR_BLKE (0x1u << 3) /**< \brief (HSMCI_SR) Data Block Ended */
#define HSMCI_SR_DTIP (0x1u << 4) /**< \brief (HSMCI_SR) Data Transfer in Progress */
#define HSMCI_SR_NOTBUSY (0x1u << 5) /**< \brief (HSMCI_SR) HSMCI Not Busy */
#define HSMCI_SR_SDIOIRQA (0x1u << 8) /**< \brief (HSMCI_SR) SDIO Interrupt for Slot A */
#define HSMCI_SR_SDIOIRQB (0x1u << 9) /**< \brief (HSMCI_SR) SDIO Interrupt for Slot B */
#define HSMCI_SR_SDIOWAIT (0x1u << 12) /**< \brief (HSMCI_SR) SDIO Read Wait Operation Status */
#define HSMCI_SR_CSRCV (0x1u << 13) /**< \brief (HSMCI_SR) CE-ATA Completion Signal Received */
#define HSMCI_SR_RINDE (0x1u << 16) /**< \brief (HSMCI_SR) Response Index Error */
#define HSMCI_SR_RDIRE (0x1u << 17) /**< \brief (HSMCI_SR) Response Direction Error */
#define HSMCI_SR_RCRCE (0x1u << 18) /**< \brief (HSMCI_SR) Response CRC Error */
#define HSMCI_SR_RENDE (0x1u << 19) /**< \brief (HSMCI_SR) Response End Bit Error */
#define HSMCI_SR_RTOE (0x1u << 20) /**< \brief (HSMCI_SR) Response Time-out Error */
#define HSMCI_SR_DCRCE (0x1u << 21) /**< \brief (HSMCI_SR) Data CRC Error */
#define HSMCI_SR_DTOE (0x1u << 22) /**< \brief (HSMCI_SR) Data Time-out Error */
#define HSMCI_SR_CSTOE (0x1u << 23) /**< \brief (HSMCI_SR) Completion Signal Time-out Error */
#define HSMCI_SR_BLKOVRE (0x1u << 24) /**< \brief (HSMCI_SR) DMA Block Overrun Error */
#define HSMCI_SR_FIFOEMPTY (0x1u << 26) /**< \brief (HSMCI_SR) FIFO empty flag */
#define HSMCI_SR_XFRDONE (0x1u << 27) /**< \brief (HSMCI_SR) Transfer Done flag */
#define HSMCI_SR_ACKRCV (0x1u << 28) /**< \brief (HSMCI_SR) Boot Operation Acknowledge Received */
#define HSMCI_SR_ACKRCVE (0x1u << 29) /**< \brief (HSMCI_SR) Boot Operation Acknowledge Error */
#define HSMCI_SR_OVRE (0x1u << 30) /**< \brief (HSMCI_SR) Overrun */
#define HSMCI_SR_UNRE (0x1u << 31) /**< \brief (HSMCI_SR) Underrun */
/* -------- HSMCI_IER : (HSMCI Offset: 0x44) Interrupt Enable Register -------- */
#define HSMCI_IER_CMDRDY (0x1u << 0) /**< \brief (HSMCI_IER) Command Ready Interrupt Enable */
#define HSMCI_IER_RXRDY (0x1u << 1) /**< \brief (HSMCI_IER) Receiver Ready Interrupt Enable */
#define HSMCI_IER_TXRDY (0x1u << 2) /**< \brief (HSMCI_IER) Transmit Ready Interrupt Enable */
#define HSMCI_IER_BLKE (0x1u << 3) /**< \brief (HSMCI_IER) Data Block Ended Interrupt Enable */
#define HSMCI_IER_DTIP (0x1u << 4) /**< \brief (HSMCI_IER) Data Transfer in Progress Interrupt Enable */
#define HSMCI_IER_NOTBUSY (0x1u << 5) /**< \brief (HSMCI_IER) Data Not Busy Interrupt Enable */
#define HSMCI_IER_SDIOIRQA (0x1u << 8) /**< \brief (HSMCI_IER) SDIO Interrupt for Slot A Interrupt Enable */
#define HSMCI_IER_SDIOIRQB (0x1u << 9) /**< \brief (HSMCI_IER) SDIO Interrupt for Slot B Interrupt Enable */
#define HSMCI_IER_SDIOWAIT (0x1u << 12) /**< \brief (HSMCI_IER) SDIO Read Wait Operation Status Interrupt Enable */
#define HSMCI_IER_CSRCV (0x1u << 13) /**< \brief (HSMCI_IER) Completion Signal Received Interrupt Enable */
#define HSMCI_IER_RINDE (0x1u << 16) /**< \brief (HSMCI_IER) Response Index Error Interrupt Enable */
#define HSMCI_IER_RDIRE (0x1u << 17) /**< \brief (HSMCI_IER) Response Direction Error Interrupt Enable */
#define HSMCI_IER_RCRCE (0x1u << 18) /**< \brief (HSMCI_IER) Response CRC Error Interrupt Enable */
#define HSMCI_IER_RENDE (0x1u << 19) /**< \brief (HSMCI_IER) Response End Bit Error Interrupt Enable */
#define HSMCI_IER_RTOE (0x1u << 20) /**< \brief (HSMCI_IER) Response Time-out Error Interrupt Enable */
#define HSMCI_IER_DCRCE (0x1u << 21) /**< \brief (HSMCI_IER) Data CRC Error Interrupt Enable */
#define HSMCI_IER_DTOE (0x1u << 22) /**< \brief (HSMCI_IER) Data Time-out Error Interrupt Enable */
#define HSMCI_IER_CSTOE (0x1u << 23) /**< \brief (HSMCI_IER) Completion Signal Timeout Error Interrupt Enable */
#define HSMCI_IER_BLKOVRE (0x1u << 24) /**< \brief (HSMCI_IER) DMA Block Overrun Error Interrupt Enable */
#define HSMCI_IER_FIFOEMPTY (0x1u << 26) /**< \brief (HSMCI_IER) FIFO empty Interrupt enable */
#define HSMCI_IER_XFRDONE (0x1u << 27) /**< \brief (HSMCI_IER) Transfer Done Interrupt enable */
#define HSMCI_IER_ACKRCV (0x1u << 28) /**< \brief (HSMCI_IER) Boot Acknowledge Interrupt Enable */
#define HSMCI_IER_ACKRCVE (0x1u << 29) /**< \brief (HSMCI_IER) Boot Acknowledge Error Interrupt Enable */
#define HSMCI_IER_OVRE (0x1u << 30) /**< \brief (HSMCI_IER) Overrun Interrupt Enable */
#define HSMCI_IER_UNRE (0x1u << 31) /**< \brief (HSMCI_IER) Underrun Interrupt Enable */
/* -------- HSMCI_IDR : (HSMCI Offset: 0x48) Interrupt Disable Register -------- */
#define HSMCI_IDR_CMDRDY (0x1u << 0) /**< \brief (HSMCI_IDR) Command Ready Interrupt Disable */
#define HSMCI_IDR_RXRDY (0x1u << 1) /**< \brief (HSMCI_IDR) Receiver Ready Interrupt Disable */
#define HSMCI_IDR_TXRDY (0x1u << 2) /**< \brief (HSMCI_IDR) Transmit Ready Interrupt Disable */
#define HSMCI_IDR_BLKE (0x1u << 3) /**< \brief (HSMCI_IDR) Data Block Ended Interrupt Disable */
#define HSMCI_IDR_DTIP (0x1u << 4) /**< \brief (HSMCI_IDR) Data Transfer in Progress Interrupt Disable */
#define HSMCI_IDR_NOTBUSY (0x1u << 5) /**< \brief (HSMCI_IDR) Data Not Busy Interrupt Disable */
#define HSMCI_IDR_SDIOIRQA (0x1u << 8) /**< \brief (HSMCI_IDR) SDIO Interrupt for Slot A Interrupt Disable */
#define HSMCI_IDR_SDIOIRQB (0x1u << 9) /**< \brief (HSMCI_IDR) SDIO Interrupt for Slot B Interrupt Disable */
#define HSMCI_IDR_SDIOWAIT (0x1u << 12) /**< \brief (HSMCI_IDR) SDIO Read Wait Operation Status Interrupt Disable */
#define HSMCI_IDR_CSRCV (0x1u << 13) /**< \brief (HSMCI_IDR) Completion Signal received interrupt Disable */
#define HSMCI_IDR_RINDE (0x1u << 16) /**< \brief (HSMCI_IDR) Response Index Error Interrupt Disable */
#define HSMCI_IDR_RDIRE (0x1u << 17) /**< \brief (HSMCI_IDR) Response Direction Error Interrupt Disable */
#define HSMCI_IDR_RCRCE (0x1u << 18) /**< \brief (HSMCI_IDR) Response CRC Error Interrupt Disable */
#define HSMCI_IDR_RENDE (0x1u << 19) /**< \brief (HSMCI_IDR) Response End Bit Error Interrupt Disable */
#define HSMCI_IDR_RTOE (0x1u << 20) /**< \brief (HSMCI_IDR) Response Time-out Error Interrupt Disable */
#define HSMCI_IDR_DCRCE (0x1u << 21) /**< \brief (HSMCI_IDR) Data CRC Error Interrupt Disable */
#define HSMCI_IDR_DTOE (0x1u << 22) /**< \brief (HSMCI_IDR) Data Time-out Error Interrupt Disable */
#define HSMCI_IDR_CSTOE (0x1u << 23) /**< \brief (HSMCI_IDR) Completion Signal Time out Error Interrupt Disable */
#define HSMCI_IDR_BLKOVRE (0x1u << 24) /**< \brief (HSMCI_IDR) DMA Block Overrun Error Interrupt Disable */
#define HSMCI_IDR_FIFOEMPTY (0x1u << 26) /**< \brief (HSMCI_IDR) FIFO empty Interrupt Disable */
#define HSMCI_IDR_XFRDONE (0x1u << 27) /**< \brief (HSMCI_IDR) Transfer Done Interrupt Disable */
#define HSMCI_IDR_ACKRCV (0x1u << 28) /**< \brief (HSMCI_IDR) Boot Acknowledge Interrupt Disable */
#define HSMCI_IDR_ACKRCVE (0x1u << 29) /**< \brief (HSMCI_IDR) Boot Acknowledge Error Interrupt Disable */
#define HSMCI_IDR_OVRE (0x1u << 30) /**< \brief (HSMCI_IDR) Overrun Interrupt Disable */
#define HSMCI_IDR_UNRE (0x1u << 31) /**< \brief (HSMCI_IDR) Underrun Interrupt Disable */
/* -------- HSMCI_IMR : (HSMCI Offset: 0x4C) Interrupt Mask Register -------- */
#define HSMCI_IMR_CMDRDY (0x1u << 0) /**< \brief (HSMCI_IMR) Command Ready Interrupt Mask */
#define HSMCI_IMR_RXRDY (0x1u << 1) /**< \brief (HSMCI_IMR) Receiver Ready Interrupt Mask */
#define HSMCI_IMR_TXRDY (0x1u << 2) /**< \brief (HSMCI_IMR) Transmit Ready Interrupt Mask */
#define HSMCI_IMR_BLKE (0x1u << 3) /**< \brief (HSMCI_IMR) Data Block Ended Interrupt Mask */
#define HSMCI_IMR_DTIP (0x1u << 4) /**< \brief (HSMCI_IMR) Data Transfer in Progress Interrupt Mask */
#define HSMCI_IMR_NOTBUSY (0x1u << 5) /**< \brief (HSMCI_IMR) Data Not Busy Interrupt Mask */
#define HSMCI_IMR_SDIOIRQA (0x1u << 8) /**< \brief (HSMCI_IMR) SDIO Interrupt for Slot A Interrupt Mask */
#define HSMCI_IMR_SDIOIRQB (0x1u << 9) /**< \brief (HSMCI_IMR) SDIO Interrupt for Slot B Interrupt Mask */
#define HSMCI_IMR_SDIOWAIT (0x1u << 12) /**< \brief (HSMCI_IMR) SDIO Read Wait Operation Status Interrupt Mask */
#define HSMCI_IMR_CSRCV (0x1u << 13) /**< \brief (HSMCI_IMR) Completion Signal Received Interrupt Mask */
#define HSMCI_IMR_RINDE (0x1u << 16) /**< \brief (HSMCI_IMR) Response Index Error Interrupt Mask */
#define HSMCI_IMR_RDIRE (0x1u << 17) /**< \brief (HSMCI_IMR) Response Direction Error Interrupt Mask */
#define HSMCI_IMR_RCRCE (0x1u << 18) /**< \brief (HSMCI_IMR) Response CRC Error Interrupt Mask */
#define HSMCI_IMR_RENDE (0x1u << 19) /**< \brief (HSMCI_IMR) Response End Bit Error Interrupt Mask */
#define HSMCI_IMR_RTOE (0x1u << 20) /**< \brief (HSMCI_IMR) Response Time-out Error Interrupt Mask */
#define HSMCI_IMR_DCRCE (0x1u << 21) /**< \brief (HSMCI_IMR) Data CRC Error Interrupt Mask */
#define HSMCI_IMR_DTOE (0x1u << 22) /**< \brief (HSMCI_IMR) Data Time-out Error Interrupt Mask */
#define HSMCI_IMR_CSTOE (0x1u << 23) /**< \brief (HSMCI_IMR) Completion Signal Time-out Error Interrupt Mask */
#define HSMCI_IMR_BLKOVRE (0x1u << 24) /**< \brief (HSMCI_IMR) DMA Block Overrun Error Interrupt Mask */
#define HSMCI_IMR_FIFOEMPTY (0x1u << 26) /**< \brief (HSMCI_IMR) FIFO Empty Interrupt Mask */
#define HSMCI_IMR_XFRDONE (0x1u << 27) /**< \brief (HSMCI_IMR) Transfer Done Interrupt Mask */
#define HSMCI_IMR_ACKRCV (0x1u << 28) /**< \brief (HSMCI_IMR) Boot Operation Acknowledge Received Interrupt Mask */
#define HSMCI_IMR_ACKRCVE (0x1u << 29) /**< \brief (HSMCI_IMR) Boot Operation Acknowledge Error Interrupt Mask */
#define HSMCI_IMR_OVRE (0x1u << 30) /**< \brief (HSMCI_IMR) Overrun Interrupt Mask */
#define HSMCI_IMR_UNRE (0x1u << 31) /**< \brief (HSMCI_IMR) Underrun Interrupt Mask */
/* -------- HSMCI_DMA : (HSMCI Offset: 0x50) DMA Configuration Register -------- */
#define HSMCI_DMA_CHKSIZE_Pos 4
#define HSMCI_DMA_CHKSIZE_Msk (0x7u << HSMCI_DMA_CHKSIZE_Pos) /**< \brief (HSMCI_DMA) DMA Channel Read and Write Chunk Size */
#define HSMCI_DMA_CHKSIZE(value) ((HSMCI_DMA_CHKSIZE_Msk & ((value) << HSMCI_DMA_CHKSIZE_Pos)))
#define HSMCI_DMA_DMAEN (0x1u << 8) /**< \brief (HSMCI_DMA) DMA Hardware Handshaking Enable */
/* -------- HSMCI_CFG : (HSMCI Offset: 0x54) Configuration Register -------- */
#define HSMCI_CFG_FIFOMODE (0x1u << 0) /**< \brief (HSMCI_CFG) HSMCI Internal FIFO control mode */
#define HSMCI_CFG_FERRCTRL (0x1u << 4) /**< \brief (HSMCI_CFG) Flow Error flag reset control mode */
#define HSMCI_CFG_HSMODE (0x1u << 8) /**< \brief (HSMCI_CFG) High Speed Mode */
#define HSMCI_CFG_LSYNC (0x1u << 12) /**< \brief (HSMCI_CFG) Synchronize on the last block */
/* -------- HSMCI_WPMR : (HSMCI Offset: 0xE4) Write Protection Mode Register -------- */
#define HSMCI_WPMR_WP_EN (0x1u << 0) /**< \brief (HSMCI_WPMR) Write Protection Enable */
#define HSMCI_WPMR_WP_KEY_Pos 8
#define HSMCI_WPMR_WP_KEY_Msk (0xffffffu << HSMCI_WPMR_WP_KEY_Pos) /**< \brief (HSMCI_WPMR) Write Protection Key password */
#define HSMCI_WPMR_WP_KEY(value) ((HSMCI_WPMR_WP_KEY_Msk & ((value) << HSMCI_WPMR_WP_KEY_Pos)))
/* -------- HSMCI_WPSR : (HSMCI Offset: 0xE8) Write Protection Status Register -------- */
#define HSMCI_WPSR_WP_VS_Pos 0
#define HSMCI_WPSR_WP_VS_Msk (0xfu << HSMCI_WPSR_WP_VS_Pos) /**< \brief (HSMCI_WPSR) Write Protection Violation Status */
#define   HSMCI_WPSR_WP_VS_NONE (0x0u << 0) /**< \brief (HSMCI_WPSR) No Write Protection Violation occurred since the last read of this register (WP_SR) */
#define   HSMCI_WPSR_WP_VS_WRITE (0x1u << 0) /**< \brief (HSMCI_WPSR) Write Protection detected unauthorized attempt to write a control register had occurred (since the last read.) */
#define   HSMCI_WPSR_WP_VS_RESET (0x2u << 0) /**< \brief (HSMCI_WPSR) Software reset had been performed while Write Protection was enabled (since the last read). */
#define   HSMCI_WPSR_WP_VS_BOTH (0x3u << 0) /**< \brief (HSMCI_WPSR) Both Write Protection violation and software reset with Write Protection enabled have occurred since the last read. */
#define HSMCI_WPSR_WP_VSRC_Pos 8
#define HSMCI_WPSR_WP_VSRC_Msk (0xffffu << HSMCI_WPSR_WP_VSRC_Pos) /**< \brief (HSMCI_WPSR) Write Protection Violation SouRCe */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR AHB Bus Matrix */
/* ============================================================================= */
/** \addtogroup SAMA5D4_MATRIX AHB Bus Matrix */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief MatrixPr hardware registers */
typedef struct {
  __IO uint32_t MATRIX_PRAS; /**< \brief (MatrixPr Offset: 0x0) Priority Register A for Slave 0 */
  __IO uint32_t MATRIX_PRBS; /**< \brief (MatrixPr Offset: 0x4) Priority Register B for Slave 0 */
} MatrixPr;
/** \brief Matrix hardware registers */
#define MATRIXPR_NUMBER 13
typedef struct {
  __IO uint32_t MATRIX_MCFG[10];            /**< \brief (Matrix Offset: 0x0000) Master Configuration Register */
  __I  uint32_t Reserved1[6];
  __IO uint32_t MATRIX_SCFG[13];            /**< \brief (Matrix Offset: 0x0040) Slave Configuration Register */
  __I  uint32_t Reserved2[3];
       MatrixPr MATRIX_PR[MATRIXPR_NUMBER]; /**< \brief (Matrix Offset: 0x0080) 0 .. 12 */
  __I  uint32_t Reserved3[26];
  __O  uint32_t MATRIX_MEIER;               /**< \brief (Matrix Offset: 0x0150) Master Error Interrupt Enable Register */
  __O  uint32_t MATRIX_MEIDR;               /**< \brief (Matrix Offset: 0x0154) Master Error Interrupt Disable Register */
  __I  uint32_t MATRIX_MEIMR;               /**< \brief (Matrix Offset: 0x0158) Master Error Interrupt Mask Register */
  __I  uint32_t MATRIX_MESR;                /**< \brief (Matrix Offset: 0x015C) Master Error Status Register */
  __I  uint32_t MATRIX_MEAR[10];            /**< \brief (Matrix Offset: 0x0160) Master 0 Error Address Register */
  __I  uint32_t Reserved4[23];
  __IO uint32_t MATRIX_WPMR;                /**< \brief (Matrix Offset: 0x01E4) Write Protect Mode Register */
  __I  uint32_t MATRIX_WPSR;                /**< \brief (Matrix Offset: 0x01E8) Write Protect Status Register */
  __I  uint32_t Reserved5[5];
  __IO uint32_t MATRIX_SSR[13];             /**< \brief (Matrix Offset: 0x0200) Security Slave 0 Register */
  __I  uint32_t Reserved6[3];
  __IO uint32_t MATRIX_SASSR[13];           /**< \brief (Matrix Offset: 0x0240) Security Areas Split Slave 0 Register */
  __I  uint32_t Reserved7[3];
  __IO uint32_t MATRIX_SRTSR[13];           /**< \brief (Matrix Offset: 0x0280) Security Region Top Slave 0 Register */
  __I  uint32_t Reserved8[3];
  __IO uint32_t MATRIX_SPSELR[3];           /**< \brief (Matrix Offset: 0x02C0) Security Peripheral Select 1 Register */
} Matrix;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- MATRIX_MCFG[10] : (MATRIX Offset: 0x0000) Master Configuration Register -------- */
#define MATRIX_MCFG_ULBT_Pos 0
#define MATRIX_MCFG_ULBT_Msk (0x7u << MATRIX_MCFG_ULBT_Pos) /**< \brief (MATRIX_MCFG[10]) Undefined Length Burst Type */
#define MATRIX_MCFG_ULBT(value) ((MATRIX_MCFG_ULBT_Msk & ((value) << MATRIX_MCFG_ULBT_Pos)))
/* -------- MATRIX_SCFG[13] : (MATRIX Offset: 0x0040) Slave Configuration Register -------- */
#define MATRIX_SCFG_SLOT_CYCLE_Pos 0
#define MATRIX_SCFG_SLOT_CYCLE_Msk (0x1ffu << MATRIX_SCFG_SLOT_CYCLE_Pos) /**< \brief (MATRIX_SCFG[13]) Maximum Bus Grant Duration for Masters */
#define MATRIX_SCFG_SLOT_CYCLE(value) ((MATRIX_SCFG_SLOT_CYCLE_Msk & ((value) << MATRIX_SCFG_SLOT_CYCLE_Pos)))
#define MATRIX_SCFG_DEFMSTR_TYPE_Pos 16
#define MATRIX_SCFG_DEFMSTR_TYPE_Msk (0x3u << MATRIX_SCFG_DEFMSTR_TYPE_Pos) /**< \brief (MATRIX_SCFG[13]) Default Master Type */
#define MATRIX_SCFG_DEFMSTR_TYPE(value) ((MATRIX_SCFG_DEFMSTR_TYPE_Msk & ((value) << MATRIX_SCFG_DEFMSTR_TYPE_Pos)))
#define MATRIX_SCFG_FIXED_DEFMSTR_Pos 18
#define MATRIX_SCFG_FIXED_DEFMSTR_Msk (0xfu << MATRIX_SCFG_FIXED_DEFMSTR_Pos) /**< \brief (MATRIX_SCFG[13]) Fixed Default Master */
#define MATRIX_SCFG_FIXED_DEFMSTR(value) ((MATRIX_SCFG_FIXED_DEFMSTR_Msk & ((value) << MATRIX_SCFG_FIXED_DEFMSTR_Pos)))
/* -------- MATRIX_PRAS : (MATRIX Offset: N/A) Priority Register A for Slave 0 -------- */
#define MATRIX_PRAS_M0PR_Pos 0
#define MATRIX_PRAS_M0PR_Msk (0x3u << MATRIX_PRAS_M0PR_Pos) /**< \brief (MATRIX_PRAS) Master 0 Priority */
#define MATRIX_PRAS_M0PR(value) ((MATRIX_PRAS_M0PR_Msk & ((value) << MATRIX_PRAS_M0PR_Pos)))
#define MATRIX_PRAS_LQOSEN0 (0x1u << 2) /**< \brief (MATRIX_PRAS) Latency Quality of Service Enable for Master 0 */
#define MATRIX_PRAS_M1PR_Pos 4
#define MATRIX_PRAS_M1PR_Msk (0x3u << MATRIX_PRAS_M1PR_Pos) /**< \brief (MATRIX_PRAS) Master 1 Priority */
#define MATRIX_PRAS_M1PR(value) ((MATRIX_PRAS_M1PR_Msk & ((value) << MATRIX_PRAS_M1PR_Pos)))
#define MATRIX_PRAS_LQOSEN1 (0x1u << 6) /**< \brief (MATRIX_PRAS) Latency Quality of Service Enable for Master 1 */
#define MATRIX_PRAS_M2PR_Pos 8
#define MATRIX_PRAS_M2PR_Msk (0x3u << MATRIX_PRAS_M2PR_Pos) /**< \brief (MATRIX_PRAS) Master 2 Priority */
#define MATRIX_PRAS_M2PR(value) ((MATRIX_PRAS_M2PR_Msk & ((value) << MATRIX_PRAS_M2PR_Pos)))
#define MATRIX_PRAS_LQOSEN2 (0x1u << 10) /**< \brief (MATRIX_PRAS) Latency Quality of Service Enable for Master 2 */
#define MATRIX_PRAS_M3PR_Pos 12
#define MATRIX_PRAS_M3PR_Msk (0x3u << MATRIX_PRAS_M3PR_Pos) /**< \brief (MATRIX_PRAS) Master 3 Priority */
#define MATRIX_PRAS_M3PR(value) ((MATRIX_PRAS_M3PR_Msk & ((value) << MATRIX_PRAS_M3PR_Pos)))
#define MATRIX_PRAS_LQOSEN3 (0x1u << 14) /**< \brief (MATRIX_PRAS) Latency Quality of Service Enable for Master 3 */
#define MATRIX_PRAS_M4PR_Pos 16
#define MATRIX_PRAS_M4PR_Msk (0x3u << MATRIX_PRAS_M4PR_Pos) /**< \brief (MATRIX_PRAS) Master 4 Priority */
#define MATRIX_PRAS_M4PR(value) ((MATRIX_PRAS_M4PR_Msk & ((value) << MATRIX_PRAS_M4PR_Pos)))
#define MATRIX_PRAS_LQOSEN4 (0x1u << 18) /**< \brief (MATRIX_PRAS) Latency Quality of Service Enable for Master 4 */
#define MATRIX_PRAS_M5PR_Pos 20
#define MATRIX_PRAS_M5PR_Msk (0x3u << MATRIX_PRAS_M5PR_Pos) /**< \brief (MATRIX_PRAS) Master 5 Priority */
#define MATRIX_PRAS_M5PR(value) ((MATRIX_PRAS_M5PR_Msk & ((value) << MATRIX_PRAS_M5PR_Pos)))
#define MATRIX_PRAS_LQOSEN5 (0x1u << 22) /**< \brief (MATRIX_PRAS) Latency Quality of Service Enable for Master 5 */
#define MATRIX_PRAS_M6PR_Pos 24
#define MATRIX_PRAS_M6PR_Msk (0x3u << MATRIX_PRAS_M6PR_Pos) /**< \brief (MATRIX_PRAS) Master 6 Priority */
#define MATRIX_PRAS_M6PR(value) ((MATRIX_PRAS_M6PR_Msk & ((value) << MATRIX_PRAS_M6PR_Pos)))
#define MATRIX_PRAS_LQOSEN6 (0x1u << 26) /**< \brief (MATRIX_PRAS) Latency Quality of Service Enable for Master 6 */
#define MATRIX_PRAS_M7PR_Pos 28
#define MATRIX_PRAS_M7PR_Msk (0x3u << MATRIX_PRAS_M7PR_Pos) /**< \brief (MATRIX_PRAS) Master 7 Priority */
#define MATRIX_PRAS_M7PR(value) ((MATRIX_PRAS_M7PR_Msk & ((value) << MATRIX_PRAS_M7PR_Pos)))
#define MATRIX_PRAS_LQOSEN7 (0x1u << 30) /**< \brief (MATRIX_PRAS) Latency Quality of Service Enable for Master 7 */
/* -------- MATRIX_PRBS : (MATRIX Offset: N/A) Priority Register B for Slave 0 -------- */
#define MATRIX_PRBS_M8PR_Pos 0
#define MATRIX_PRBS_M8PR_Msk (0x3u << MATRIX_PRBS_M8PR_Pos) /**< \brief (MATRIX_PRBS) Master 8 Priority */
#define MATRIX_PRBS_M8PR(value) ((MATRIX_PRBS_M8PR_Msk & ((value) << MATRIX_PRBS_M8PR_Pos)))
#define MATRIX_PRBS_LQOSEN8 (0x1u << 2) /**< \brief (MATRIX_PRBS) Latency Quality of Service Enable for Master 8 */
#define MATRIX_PRBS_M9PR_Pos 4
#define MATRIX_PRBS_M9PR_Msk (0x3u << MATRIX_PRBS_M9PR_Pos) /**< \brief (MATRIX_PRBS) Master 9 Priority */
#define MATRIX_PRBS_M9PR(value) ((MATRIX_PRBS_M9PR_Msk & ((value) << MATRIX_PRBS_M9PR_Pos)))
#define MATRIX_PRBS_LQOSEN9 (0x1u << 6) /**< \brief (MATRIX_PRBS) Latency Quality of Service Enable for Master 9 */
/* -------- MATRIX_MEIER : (MATRIX Offset: 0x0150) Master Error Interrupt Enable Register -------- */
#define MATRIX_MEIER_MERR0 (0x1u << 0) /**< \brief (MATRIX_MEIER) Master 0 Access Error */
#define MATRIX_MEIER_MERR1 (0x1u << 1) /**< \brief (MATRIX_MEIER) Master 1 Access Error */
#define MATRIX_MEIER_MERR2 (0x1u << 2) /**< \brief (MATRIX_MEIER) Master 2 Access Error */
#define MATRIX_MEIER_MERR3 (0x1u << 3) /**< \brief (MATRIX_MEIER) Master 3 Access Error */
#define MATRIX_MEIER_MERR4 (0x1u << 4) /**< \brief (MATRIX_MEIER) Master 4 Access Error */
#define MATRIX_MEIER_MERR5 (0x1u << 5) /**< \brief (MATRIX_MEIER) Master 5 Access Error */
#define MATRIX_MEIER_MERR6 (0x1u << 6) /**< \brief (MATRIX_MEIER) Master 6 Access Error */
#define MATRIX_MEIER_MERR7 (0x1u << 7) /**< \brief (MATRIX_MEIER) Master 7 Access Error */
#define MATRIX_MEIER_MERR8 (0x1u << 8) /**< \brief (MATRIX_MEIER) Master 8 Access Error */
#define MATRIX_MEIER_MERR9 (0x1u << 9) /**< \brief (MATRIX_MEIER) Master 9 Access Error */
/* -------- MATRIX_MEIDR : (MATRIX Offset: 0x0154) Master Error Interrupt Disable Register -------- */
#define MATRIX_MEIDR_MERR0 (0x1u << 0) /**< \brief (MATRIX_MEIDR) Master 0 Access Error */
#define MATRIX_MEIDR_MERR1 (0x1u << 1) /**< \brief (MATRIX_MEIDR) Master 1 Access Error */
#define MATRIX_MEIDR_MERR2 (0x1u << 2) /**< \brief (MATRIX_MEIDR) Master 2 Access Error */
#define MATRIX_MEIDR_MERR3 (0x1u << 3) /**< \brief (MATRIX_MEIDR) Master 3 Access Error */
#define MATRIX_MEIDR_MERR4 (0x1u << 4) /**< \brief (MATRIX_MEIDR) Master 4 Access Error */
#define MATRIX_MEIDR_MERR5 (0x1u << 5) /**< \brief (MATRIX_MEIDR) Master 5 Access Error */
#define MATRIX_MEIDR_MERR6 (0x1u << 6) /**< \brief (MATRIX_MEIDR) Master 6 Access Error */
#define MATRIX_MEIDR_MERR7 (0x1u << 7) /**< \brief (MATRIX_MEIDR) Master 7 Access Error */
#define MATRIX_MEIDR_MERR8 (0x1u << 8) /**< \brief (MATRIX_MEIDR) Master 8 Access Error */
#define MATRIX_MEIDR_MERR9 (0x1u << 9) /**< \brief (MATRIX_MEIDR) Master 9 Access Error */
/* -------- MATRIX_MEIMR : (MATRIX Offset: 0x0158) Master Error Interrupt Mask Register -------- */
#define MATRIX_MEIMR_MERR0 (0x1u << 0) /**< \brief (MATRIX_MEIMR) Master 0 Access Error */
#define MATRIX_MEIMR_MERR1 (0x1u << 1) /**< \brief (MATRIX_MEIMR) Master 1 Access Error */
#define MATRIX_MEIMR_MERR2 (0x1u << 2) /**< \brief (MATRIX_MEIMR) Master 2 Access Error */
#define MATRIX_MEIMR_MERR3 (0x1u << 3) /**< \brief (MATRIX_MEIMR) Master 3 Access Error */
#define MATRIX_MEIMR_MERR4 (0x1u << 4) /**< \brief (MATRIX_MEIMR) Master 4 Access Error */
#define MATRIX_MEIMR_MERR5 (0x1u << 5) /**< \brief (MATRIX_MEIMR) Master 5 Access Error */
#define MATRIX_MEIMR_MERR6 (0x1u << 6) /**< \brief (MATRIX_MEIMR) Master 6 Access Error */
#define MATRIX_MEIMR_MERR7 (0x1u << 7) /**< \brief (MATRIX_MEIMR) Master 7 Access Error */
#define MATRIX_MEIMR_MERR8 (0x1u << 8) /**< \brief (MATRIX_MEIMR) Master 8 Access Error */
#define MATRIX_MEIMR_MERR9 (0x1u << 9) /**< \brief (MATRIX_MEIMR) Master 9 Access Error */
/* -------- MATRIX_MESR : (MATRIX Offset: 0x015C) Master Error Status Register -------- */
#define MATRIX_MESR_MERR0 (0x1u << 0) /**< \brief (MATRIX_MESR) Master 0 Access Error */
#define MATRIX_MESR_MERR1 (0x1u << 1) /**< \brief (MATRIX_MESR) Master 1 Access Error */
#define MATRIX_MESR_MERR2 (0x1u << 2) /**< \brief (MATRIX_MESR) Master 2 Access Error */
#define MATRIX_MESR_MERR3 (0x1u << 3) /**< \brief (MATRIX_MESR) Master 3 Access Error */
#define MATRIX_MESR_MERR4 (0x1u << 4) /**< \brief (MATRIX_MESR) Master 4 Access Error */
#define MATRIX_MESR_MERR5 (0x1u << 5) /**< \brief (MATRIX_MESR) Master 5 Access Error */
#define MATRIX_MESR_MERR6 (0x1u << 6) /**< \brief (MATRIX_MESR) Master 6 Access Error */
#define MATRIX_MESR_MERR7 (0x1u << 7) /**< \brief (MATRIX_MESR) Master 7 Access Error */
#define MATRIX_MESR_MERR8 (0x1u << 8) /**< \brief (MATRIX_MESR) Master 8 Access Error */
#define MATRIX_MESR_MERR9 (0x1u << 9) /**< \brief (MATRIX_MESR) Master 9 Access Error */
/* -------- MATRIX_MEAR[10] : (MATRIX Offset: 0x0160) Master 0 Error Address Register -------- */
#define MATRIX_MEAR_ERRADD_Pos 0
#define MATRIX_MEAR_ERRADD_Msk (0xffffffffu << MATRIX_MEAR_ERRADD_Pos) /**< \brief (MATRIX_MEAR[10]) Master Error Address */
/* -------- MATRIX_WPMR : (MATRIX Offset: 0x01E4) Write Protect Mode Register -------- */
#define MATRIX_WPMR_WPEN (0x1u << 0) /**< \brief (MATRIX_WPMR) Write Protect Enable */
#define MATRIX_WPMR_WPKEY_Pos 8
#define MATRIX_WPMR_WPKEY_Msk (0xffffffu << MATRIX_WPMR_WPKEY_Pos) /**< \brief (MATRIX_WPMR) Write Protect KEY (Write-only) */
#define MATRIX_WPMR_WPKEY(value) ((MATRIX_WPMR_WPKEY_Msk & ((value) << MATRIX_WPMR_WPKEY_Pos)))
/* -------- MATRIX_WPSR : (MATRIX Offset: 0x01E8) Write Protect Status Register -------- */
#define MATRIX_WPSR_WPVS (0x1u << 0) /**< \brief (MATRIX_WPSR) Write Protect Violation Status */
#define MATRIX_WPSR_WPVSRC_Pos 8
#define MATRIX_WPSR_WPVSRC_Msk (0xffffu << MATRIX_WPSR_WPVSRC_Pos) /**< \brief (MATRIX_WPSR) Write Protect Violation Source */
/* -------- MATRIX_SSR[13] : (MATRIX Offset: 0x0200) Security Slave 0 Register -------- */
#define MATRIX_SSR_LANSECH0 (0x1u << 0) /**< \brief (MATRIX_SSR[13]) Low Area Not Secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH1 (0x1u << 1) /**< \brief (MATRIX_SSR[13]) Low Area Not Secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH2 (0x1u << 2) /**< \brief (MATRIX_SSR[13]) Low Area Not Secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH3 (0x1u << 3) /**< \brief (MATRIX_SSR[13]) Low Area Not Secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH4 (0x1u << 4) /**< \brief (MATRIX_SSR[13]) Low Area Not Secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH5 (0x1u << 5) /**< \brief (MATRIX_SSR[13]) Low Area Not Secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH6 (0x1u << 6) /**< \brief (MATRIX_SSR[13]) Low Area Not Secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH7 (0x1u << 7) /**< \brief (MATRIX_SSR[13]) Low Area Not Secured in HSELx Security Region */
#define MATRIX_SSR_RDNSECH0 (0x1u << 8) /**< \brief (MATRIX_SSR[13]) Read Not Secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH1 (0x1u << 9) /**< \brief (MATRIX_SSR[13]) Read Not Secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH2 (0x1u << 10) /**< \brief (MATRIX_SSR[13]) Read Not Secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH3 (0x1u << 11) /**< \brief (MATRIX_SSR[13]) Read Not Secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH4 (0x1u << 12) /**< \brief (MATRIX_SSR[13]) Read Not Secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH5 (0x1u << 13) /**< \brief (MATRIX_SSR[13]) Read Not Secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH6 (0x1u << 14) /**< \brief (MATRIX_SSR[13]) Read Not Secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH7 (0x1u << 15) /**< \brief (MATRIX_SSR[13]) Read Not Secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH0 (0x1u << 16) /**< \brief (MATRIX_SSR[13]) Write Not Secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH1 (0x1u << 17) /**< \brief (MATRIX_SSR[13]) Write Not Secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH2 (0x1u << 18) /**< \brief (MATRIX_SSR[13]) Write Not Secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH3 (0x1u << 19) /**< \brief (MATRIX_SSR[13]) Write Not Secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH4 (0x1u << 20) /**< \brief (MATRIX_SSR[13]) Write Not Secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH5 (0x1u << 21) /**< \brief (MATRIX_SSR[13]) Write Not Secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH6 (0x1u << 22) /**< \brief (MATRIX_SSR[13]) Write Not Secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH7 (0x1u << 23) /**< \brief (MATRIX_SSR[13]) Write Not Secured for HSELx Security Region */
/* -------- MATRIX_SASSR[13] : (MATRIX Offset: 0x0240) Security Areas Split Slave 0 Register -------- */
#define MATRIX_SASSR_SASPLIT0_Pos 0
#define MATRIX_SASSR_SASPLIT0_Msk (0xfu << MATRIX_SASSR_SASPLIT0_Pos) /**< \brief (MATRIX_SASSR[13]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT0(value) ((MATRIX_SASSR_SASPLIT0_Msk & ((value) << MATRIX_SASSR_SASPLIT0_Pos)))
#define MATRIX_SASSR_SASPLIT1_Pos 4
#define MATRIX_SASSR_SASPLIT1_Msk (0xfu << MATRIX_SASSR_SASPLIT1_Pos) /**< \brief (MATRIX_SASSR[13]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT1(value) ((MATRIX_SASSR_SASPLIT1_Msk & ((value) << MATRIX_SASSR_SASPLIT1_Pos)))
#define MATRIX_SASSR_SASPLIT2_Pos 8
#define MATRIX_SASSR_SASPLIT2_Msk (0xfu << MATRIX_SASSR_SASPLIT2_Pos) /**< \brief (MATRIX_SASSR[13]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT2(value) ((MATRIX_SASSR_SASPLIT2_Msk & ((value) << MATRIX_SASSR_SASPLIT2_Pos)))
#define MATRIX_SASSR_SASPLIT3_Pos 12
#define MATRIX_SASSR_SASPLIT3_Msk (0xfu << MATRIX_SASSR_SASPLIT3_Pos) /**< \brief (MATRIX_SASSR[13]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT3(value) ((MATRIX_SASSR_SASPLIT3_Msk & ((value) << MATRIX_SASSR_SASPLIT3_Pos)))
#define MATRIX_SASSR_SASPLIT4_Pos 16
#define MATRIX_SASSR_SASPLIT4_Msk (0xfu << MATRIX_SASSR_SASPLIT4_Pos) /**< \brief (MATRIX_SASSR[13]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT4(value) ((MATRIX_SASSR_SASPLIT4_Msk & ((value) << MATRIX_SASSR_SASPLIT4_Pos)))
#define MATRIX_SASSR_SASPLIT5_Pos 20
#define MATRIX_SASSR_SASPLIT5_Msk (0xfu << MATRIX_SASSR_SASPLIT5_Pos) /**< \brief (MATRIX_SASSR[13]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT5(value) ((MATRIX_SASSR_SASPLIT5_Msk & ((value) << MATRIX_SASSR_SASPLIT5_Pos)))
#define MATRIX_SASSR_SASPLIT6_Pos 24
#define MATRIX_SASSR_SASPLIT6_Msk (0xfu << MATRIX_SASSR_SASPLIT6_Pos) /**< \brief (MATRIX_SASSR[13]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT6(value) ((MATRIX_SASSR_SASPLIT6_Msk & ((value) << MATRIX_SASSR_SASPLIT6_Pos)))
#define MATRIX_SASSR_SASPLIT7_Pos 28
#define MATRIX_SASSR_SASPLIT7_Msk (0xfu << MATRIX_SASSR_SASPLIT7_Pos) /**< \brief (MATRIX_SASSR[13]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT7(value) ((MATRIX_SASSR_SASPLIT7_Msk & ((value) << MATRIX_SASSR_SASPLIT7_Pos)))
/* -------- MATRIX_SRTSR[13] : (MATRIX Offset: 0x0280) Security Region Top Slave 0 Register -------- */
#define MATRIX_SRTSR_SRTOP0_Pos 0
#define MATRIX_SRTSR_SRTOP0_Msk (0xfu << MATRIX_SRTSR_SRTOP0_Pos) /**< \brief (MATRIX_SRTSR[13]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP0(value) ((MATRIX_SRTSR_SRTOP0_Msk & ((value) << MATRIX_SRTSR_SRTOP0_Pos)))
#define MATRIX_SRTSR_SRTOP1_Pos 4
#define MATRIX_SRTSR_SRTOP1_Msk (0xfu << MATRIX_SRTSR_SRTOP1_Pos) /**< \brief (MATRIX_SRTSR[13]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP1(value) ((MATRIX_SRTSR_SRTOP1_Msk & ((value) << MATRIX_SRTSR_SRTOP1_Pos)))
#define MATRIX_SRTSR_SRTOP2_Pos 8
#define MATRIX_SRTSR_SRTOP2_Msk (0xfu << MATRIX_SRTSR_SRTOP2_Pos) /**< \brief (MATRIX_SRTSR[13]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP2(value) ((MATRIX_SRTSR_SRTOP2_Msk & ((value) << MATRIX_SRTSR_SRTOP2_Pos)))
#define MATRIX_SRTSR_SRTOP3_Pos 12
#define MATRIX_SRTSR_SRTOP3_Msk (0xfu << MATRIX_SRTSR_SRTOP3_Pos) /**< \brief (MATRIX_SRTSR[13]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP3(value) ((MATRIX_SRTSR_SRTOP3_Msk & ((value) << MATRIX_SRTSR_SRTOP3_Pos)))
#define MATRIX_SRTSR_SRTOP4_Pos 16
#define MATRIX_SRTSR_SRTOP4_Msk (0xfu << MATRIX_SRTSR_SRTOP4_Pos) /**< \brief (MATRIX_SRTSR[13]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP4(value) ((MATRIX_SRTSR_SRTOP4_Msk & ((value) << MATRIX_SRTSR_SRTOP4_Pos)))
#define MATRIX_SRTSR_SRTOP5_Pos 20
#define MATRIX_SRTSR_SRTOP5_Msk (0xfu << MATRIX_SRTSR_SRTOP5_Pos) /**< \brief (MATRIX_SRTSR[13]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP5(value) ((MATRIX_SRTSR_SRTOP5_Msk & ((value) << MATRIX_SRTSR_SRTOP5_Pos)))
#define MATRIX_SRTSR_SRTOP6_Pos 24
#define MATRIX_SRTSR_SRTOP6_Msk (0xfu << MATRIX_SRTSR_SRTOP6_Pos) /**< \brief (MATRIX_SRTSR[13]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP6(value) ((MATRIX_SRTSR_SRTOP6_Msk & ((value) << MATRIX_SRTSR_SRTOP6_Pos)))
#define MATRIX_SRTSR_SRTOP7_Pos 28
#define MATRIX_SRTSR_SRTOP7_Msk (0xfu << MATRIX_SRTSR_SRTOP7_Pos) /**< \brief (MATRIX_SRTSR[13]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP7(value) ((MATRIX_SRTSR_SRTOP7_Msk & ((value) << MATRIX_SRTSR_SRTOP7_Pos)))
/* -------- MATRIX_SPSELR[3] : (MATRIX Offset: 0x02C0) Security Peripheral Select 1 Register -------- */
#define MATRIX_SPSELR_NSECP0 (0x1u << 0) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP1 (0x1u << 1) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP2 (0x1u << 2) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP3 (0x1u << 3) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP4 (0x1u << 4) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP5 (0x1u << 5) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP6 (0x1u << 6) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP7 (0x1u << 7) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP8 (0x1u << 8) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP9 (0x1u << 9) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP10 (0x1u << 10) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP11 (0x1u << 11) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP12 (0x1u << 12) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP13 (0x1u << 13) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP14 (0x1u << 14) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP15 (0x1u << 15) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP16 (0x1u << 16) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP17 (0x1u << 17) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP18 (0x1u << 18) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP19 (0x1u << 19) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP20 (0x1u << 20) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP21 (0x1u << 21) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP22 (0x1u << 22) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP23 (0x1u << 23) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP24 (0x1u << 24) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP25 (0x1u << 25) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP26 (0x1u << 26) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP27 (0x1u << 27) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP28 (0x1u << 28) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP29 (0x1u << 29) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP30 (0x1u << 30) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */
#define MATRIX_SPSELR_NSECP31 (0x1u << 31) /**< \brief (MATRIX_SPSELR[3]) Not Secured PSELy Peripheral */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR AHB Multi-port DDR-SDRAM Controller */
/* ============================================================================= */
/** \addtogroup SAMA5D4_MPDDRC AHB Multi-port DDR-SDRAM Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Mpddrc hardware registers */
typedef struct {
  __IO uint32_t MPDDRC_MR;             /**< \brief (Mpddrc Offset: 0x00) MPDDRC Mode Register */
  __IO uint32_t MPDDRC_RTR;            /**< \brief (Mpddrc Offset: 0x04) MPDDRC Refresh Timer Register */
  __IO uint32_t MPDDRC_CR;             /**< \brief (Mpddrc Offset: 0x08) MPDDRC Configuration Register */
  __IO uint32_t MPDDRC_TPR0;           /**< \brief (Mpddrc Offset: 0x0C) MPDDRC Timing Parameter 0 Register */
  __IO uint32_t MPDDRC_TPR1;           /**< \brief (Mpddrc Offset: 0x10) MPDDRC Timing Parameter 1 Register */
  __IO uint32_t MPDDRC_TPR2;           /**< \brief (Mpddrc Offset: 0x14) MPDDRC Timing Parameter 2 Register */
  __I  uint32_t Reserved1[1];
  __IO uint32_t MPDDRC_LPR;            /**< \brief (Mpddrc Offset: 0x1C) MPDDRC Low-power Register */
  __IO uint32_t MPDDRC_MD;             /**< \brief (Mpddrc Offset: 0x20) MPDDRC Memory Device Register */
  __I  uint32_t Reserved2[1];
  __IO uint32_t MPDDRC_LPDDR2_LPR;     /**< \brief (Mpddrc Offset: 0x28) MPDDRC LPDDR2 Low-power Register */
  __IO uint32_t MPDDRC_LPDDR2_CAL_MR4; /**< \brief (Mpddrc Offset: 0x2C) MPDDRC LPDDR2 Calibration and MR4 Register */
  __IO uint32_t MPDDRC_LPDDR2_TIM_CAL; /**< \brief (Mpddrc Offset: 0x30) MPDDRC LPDDR2 Timing Calibration Register */
  __IO uint32_t MPDDRC_IO_CALIBR;      /**< \brief (Mpddrc Offset: 0x34) MPDDRC IO Calibration */
  __IO uint32_t MPDDRC_OCMS;           /**< \brief (Mpddrc Offset: 0x38) MPDDRC OCMS Register */
  __O  uint32_t MPDDRC_OCMS_KEY1;      /**< \brief (Mpddrc Offset: 0x3C) MPDDRC OCMS KEY1 Register */
  __O  uint32_t MPDDRC_OCMS_KEY2;      /**< \brief (Mpddrc Offset: 0x40) MPDDRC OCMS KEY2 Register */
  __IO uint32_t MPDDRC_CONF_ARBITER;   /**< \brief (Mpddrc Offset: 0x44) MPDDRC Configuration Arbiter */
  __IO uint32_t MPDDRC_TIMEOUT;        /**< \brief (Mpddrc Offset: 0x48) MPDDRC Time-out Port 0/1/2/3 */
  __IO uint32_t MPDDRC_REQ_PORT_0123;  /**< \brief (Mpddrc Offset: 0x4C) MPDDRC Time-out Request Port 0/1/2/3 */
  __IO uint32_t MPDDRC_REQ_PORT_4567;  /**< \brief (Mpddrc Offset: 0x50) MPDDRC Time-out Request Port 4/5/6/7 */
  __I  uint32_t MPDDRC_BDW_PORT_0123;  /**< \brief (Mpddrc Offset: 0x54) MPDDRC Bandwidth Port 0/1/2/3 */
  __I  uint32_t MPDDRC_BDW_PORT_4567;  /**< \brief (Mpddrc Offset: 0x58) MPDDRC Bandwidth Port 4/5/6/7 */
  __IO uint32_t MPDDRC_RD_DATA_PATH;   /**< \brief (Mpddrc Offset: 0x5C) MPDDRC_READ_DATA_PATH */
  __IO uint32_t MPDDRC_SAW[4];         /**< \brief (Mpddrc Offset: 0x60) MPDDRC Smart Adaptation Wrapper 0 Register */
  __I  uint32_t Reserved3[29];
  __IO uint32_t MPDDRC_WPMR;           /**< \brief (Mpddrc Offset: 0xE4) MPDDRC Write Protect Control Register */
  __I  uint32_t MPDDRC_WPSR;           /**< \brief (Mpddrc Offset: 0xE8) MPDDRC Write Protect Status Register */
  __I  uint32_t Reserved4[5];
  __IO uint32_t MPDDRC_DLL_OS;         /**< \brief (Mpddrc Offset: 0x100) MPDDRC DLL Offset Selection Register */
  __IO uint32_t MPDDRC_DLL_MO;         /**< \brief (Mpddrc Offset: 0x104) MPDDRC DLL MASTER Offset Register */
  __IO uint32_t MPDDRC_DLL_SO0;        /**< \brief (Mpddrc Offset: 0x108) MPDDRC DLL SLAVE Offset 0 Register */
  __IO uint32_t MPDDRC_DLL_SO1;        /**< \brief (Mpddrc Offset: 0x10C) MPDDRC DLL SLAVE Offset 1 Register */
  __IO uint32_t MPDDRC_DLL_WRO;        /**< \brief (Mpddrc Offset: 0x110) MPDDRC DLL CLKWR Offset Register */
  __IO uint32_t MPDDRC_DLL_ADO;        /**< \brief (Mpddrc Offset: 0x114) MPDDRC DLL CLKAD Offset Register */
  __I  uint32_t MPDDRC_DLL_SM[4];      /**< \brief (Mpddrc Offset: 0x118) MPDDRC DLL Status MASTER0 Register */
  __I  uint32_t MPDDRC_DLL_SSL[8];     /**< \brief (Mpddrc Offset: 0x128) MPDDRC DLL Status SLAVE0 Register */
  __I  uint32_t MPDDRC_DLL_SWR[4];     /**< \brief (Mpddrc Offset: 0x148) MPDDRC DLL Status CLKWR0 Register */
  __I  uint32_t MPDDRC_DLL_SAD;        /**< \brief (Mpddrc Offset: 0x158) MPDDRC DLL Status CLKAD Register */
} Mpddrc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- MPDDRC_MR : (MPDDRC Offset: 0x00) MPDDRC Mode Register -------- */
#define MPDDRC_MR_MODE_Pos 0
#define MPDDRC_MR_MODE_Msk (0x7u << MPDDRC_MR_MODE_Pos) /**< \brief (MPDDRC_MR) MPDDRC Command Mode */
#define   MPDDRC_MR_MODE_NORMAL_CMD (0x0u << 0) /**< \brief (MPDDRC_MR) Normal Mode. Any access to the MPDDRC is decoded normally. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_NOP_CMD (0x1u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues a NOP command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_PRCGALL_CMD (0x2u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues the All Banks Precharge command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the SDRAM. */
#define   MPDDRC_MR_MODE_LMR_CMD (0x3u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues a Load Mode Register command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_RFSH_CMD (0x4u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an Auto-Refresh command when the DDR-SDRAM device is accessed regardless of the cycle. Previously, an "All Banks Precharge" command must be issued. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_EXT_LMR_CMD (0x5u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an Extended Load Mode Register command when the SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. The write in the DDR-SDRAM must be done in the appropriate bank. */
#define   MPDDRC_MR_MODE_DEEP_CMD (0x6u << 0) /**< \brief (MPDDRC_MR) Deep power mode: Access to deep power-down mode */
#define   MPDDRC_MR_MODE_LPDDR2_CMD (0x7u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an LPDDR2 Mode Register command when the Low-power DDR2-SDRAM device is accessed regardless of the cycle. To activate this mode, the Mode Register command must be followed by a write to the Low-power DDR2-SDRAM. */
#define MPDDRC_MR_MRS_Pos 8
#define MPDDRC_MR_MRS_Msk (0xffu << MPDDRC_MR_MRS_Pos) /**< \brief (MPDDRC_MR) Mode Register Select LPDDR2 */
#define MPDDRC_MR_MRS(value) ((MPDDRC_MR_MRS_Msk & ((value) << MPDDRC_MR_MRS_Pos)))
/* -------- MPDDRC_RTR : (MPDDRC Offset: 0x04) MPDDRC Refresh Timer Register -------- */
#define MPDDRC_RTR_COUNT_Pos 0
#define MPDDRC_RTR_COUNT_Msk (0xfffu << MPDDRC_RTR_COUNT_Pos) /**< \brief (MPDDRC_RTR) MPDDRC Refresh Timer Count */
#define MPDDRC_RTR_COUNT(value) ((MPDDRC_RTR_COUNT_Msk & ((value) << MPDDRC_RTR_COUNT_Pos)))
#define MPDDRC_RTR_ADJ_REF (0x1u << 16) /**< \brief (MPDDRC_RTR) Adjust Refresh Rate */
#define MPDDRC_RTR_REF_PB (0x1u << 17) /**< \brief (MPDDRC_RTR) Refresh Per Bank */
#define MPDDRC_RTR_MR4_VALUE_Pos 20
#define MPDDRC_RTR_MR4_VALUE_Msk (0x7u << MPDDRC_RTR_MR4_VALUE_Pos) /**< \brief (MPDDRC_RTR) Content of MR4 Register */
#define MPDDRC_RTR_MR4_VALUE(value) ((MPDDRC_RTR_MR4_VALUE_Msk & ((value) << MPDDRC_RTR_MR4_VALUE_Pos)))
/* -------- MPDDRC_CR : (MPDDRC Offset: 0x08) MPDDRC Configuration Register -------- */
#define MPDDRC_CR_NC_Pos 0
#define MPDDRC_CR_NC_Msk (0x3u << MPDDRC_CR_NC_Pos) /**< \brief (MPDDRC_CR) Number of Column Bits */
#define   MPDDRC_CR_NC_9_COL_BITS (0x0u << 0) /**< \brief (MPDDRC_CR) 9 bit to define the column number, up to 512 column */
#define   MPDDRC_CR_NC_10_COL_BITS (0x1u << 0) /**< \brief (MPDDRC_CR) 10 bit to define the column number, up to 1024 columns */
#define   MPDDRC_CR_NC_11_COL_BITS (0x2u << 0) /**< \brief (MPDDRC_CR) 11 bit to define the column number, up to 2048 columns */
#define   MPDDRC_CR_NC_12_COL_BITS (0x3u << 0) /**< \brief (MPDDRC_CR) 12 bit to define the column number, up to 4096 columns */
#define MPDDRC_CR_NR_Pos 2
#define MPDDRC_CR_NR_Msk (0x3u << MPDDRC_CR_NR_Pos) /**< \brief (MPDDRC_CR) Number of Row Bits */
#define   MPDDRC_CR_NR_11_ROW_BITS (0x0u << 2) /**< \brief (MPDDRC_CR) 11 bit to define the row number, up to 2048 rows */
#define   MPDDRC_CR_NR_12_ROW_BITS (0x1u << 2) /**< \brief (MPDDRC_CR) 12 bit to define the row number, up to 4096 rows */
#define   MPDDRC_CR_NR_13_ROW_BITS (0x2u << 2) /**< \brief (MPDDRC_CR) 13 bit to define the row number, up to 8192 rows */
#define   MPDDRC_CR_NR_14_ROW_BITS (0x3u << 2) /**< \brief (MPDDRC_CR) 14 bit to define the row number, up to 16384 rows */
#define MPDDRC_CR_CAS_Pos 4
#define MPDDRC_CR_CAS_Msk (0x7u << MPDDRC_CR_CAS_Pos) /**< \brief (MPDDRC_CR) CAS Latency */
#define   MPDDRC_CR_CAS_DDR_CAS2 (0x2u << 4) /**< \brief (MPDDRC_CR) LPDDR1 CAS Latency 2 */
#define   MPDDRC_CR_CAS_DDR_CAS3 (0x3u << 4) /**< \brief (MPDDRC_CR) DDR2/LPDDR2/LPDDR1 CAS Latency 3 */
#define   MPDDRC_CR_CAS_DDR_CAS4 (0x4u << 4) /**< \brief (MPDDRC_CR) DDR2/LPDDR2 CAS Latency 4 */
#define   MPDDRC_CR_CAS_DDR_CAS5 (0x5u << 4) /**< \brief (MPDDRC_CR) DDR2/LPDDR2 CAS Latency 5 */
#define   MPDDRC_CR_CAS_DDR_CAS6 (0x6u << 4) /**< \brief (MPDDRC_CR) DDR2 CAS Latency 6 */
#define MPDDRC_CR_DLL (0x1u << 7) /**< \brief (MPDDRC_CR) Reset DLL */
#define   MPDDRC_CR_DLL_RESET_DISABLED (0x0u << 7) /**< \brief (MPDDRC_CR) Disable DLL reset. */
#define   MPDDRC_CR_DLL_RESET_ENABLED (0x1u << 7) /**< \brief (MPDDRC_CR) Enable DLL reset. */
#define MPDDRC_CR_DIC_DS (0x1u << 8) /**< \brief (MPDDRC_CR) Output Driver Impedance Control (Drive Strength) */
#define   MPDDRC_CR_DIC_DS_DDR2_NORMALSTRENGTH (0x0u << 8) /**< \brief (MPDDRC_CR) Normal driver strength */
#define   MPDDRC_CR_DIC_DS_DDR2_WEAKSTRENGTH (0x1u << 8) /**< \brief (MPDDRC_CR) Weak driver strength */
#define MPDDRC_CR_DIS_DLL (0x1u << 9) /**< \brief (MPDDRC_CR) DISABLE DLL */
#define MPDDRC_CR_ZQ_Pos 10
#define MPDDRC_CR_ZQ_Msk (0x3u << MPDDRC_CR_ZQ_Pos) /**< \brief (MPDDRC_CR) ZQ Calibration */
#define   MPDDRC_CR_ZQ_INIT (0x0u << 10) /**< \brief (MPDDRC_CR) Calibration command after initialization */
#define   MPDDRC_CR_ZQ_LONG (0x1u << 10) /**< \brief (MPDDRC_CR) Long calibration */
#define   MPDDRC_CR_ZQ_SHORT (0x2u << 10) /**< \brief (MPDDRC_CR) Short calibration */
#define   MPDDRC_CR_ZQ_RESET (0x3u << 10) /**< \brief (MPDDRC_CR) ZQ Reset */
#define MPDDRC_CR_OCD_Pos 12
#define MPDDRC_CR_OCD_Msk (0x7u << MPDDRC_CR_OCD_Pos) /**< \brief (MPDDRC_CR) Off-chip Driver */
#define   MPDDRC_CR_OCD_DDR2_EXITCALIB (0x0u << 12) /**< \brief (MPDDRC_CR) Exit from OCD calibration mode and maintain settings */
#define   MPDDRC_CR_OCD_DDR2_DEFAULT_CALIB (0x7u << 12) /**< \brief (MPDDRC_CR) OCD calibration default */
#define MPDDRC_CR_DQMS (0x1u << 16) /**< \brief (MPDDRC_CR) Mask Data is Shared */
#define   MPDDRC_CR_DQMS_NOT_SHARED (0x0u << 16) /**< \brief (MPDDRC_CR) DQM is not shared with another controller. */
#define   MPDDRC_CR_DQMS_SHARED (0x1u << 16) /**< \brief (MPDDRC_CR) DQM is shared with another controller. */
#define MPDDRC_CR_ENRDM (0x1u << 17) /**< \brief (MPDDRC_CR) Enable Read Measure */
#define   MPDDRC_CR_ENRDM_OFF (0x0u << 17) /**< \brief (MPDDRC_CR) DQS/DDR_DATA phase error correction is disabled. */
#define   MPDDRC_CR_ENRDM_ON (0x1u << 17) /**< \brief (MPDDRC_CR) DQS/DDR_DATA phase error correction is enabled. */
#define MPDDRC_CR_LC_LPDDR1 (0x1u << 19) /**< \brief (MPDDRC_CR) Low-cost Low-power DDR1. */
#define   MPDDRC_CR_LC_LPDDR1_NOT_2_BANKS (0x0u << 19) /**< \brief (MPDDRC_CR) Any type of memory devices except of low cost, low density Low Power DDR1. */
#define   MPDDRC_CR_LC_LPDDR1_2_BANKS_LPDDR1 (0x1u << 19) /**< \brief (MPDDRC_CR) Low-cost and low-density Low-power DDR1. These devices have a density of 32 Mbits and are organized as 2 internal banks. To use this feature, the user has to define the type of memory and the data bus width (see "MPDDRC Memory Device Register" on page 69).The 16-bit memory device is organized as 2 banks, 9 columns and 11 rows. The 32-bit memory device is organized as 2 banks, 8 columns and 11 rows.It is impossible to use two 16-bit memory devices (2x32 Mbits) for creating one 32-bit memory device (64 Mbits). In this case, it is recommended to use one 32-bit memory device which embeds 4 internal banks. */
#define MPDDRC_CR_NB (0x1u << 20) /**< \brief (MPDDRC_CR) Number of Banks */
#define   MPDDRC_CR_NB_4_BANKS (0x0u << 20) /**< \brief (MPDDRC_CR) 4 banks memory devices. */
#define   MPDDRC_CR_NB_8_BANKS (0x1u << 20) /**< \brief (MPDDRC_CR) 8 banks. Only possible when using the DDR2-SDRAM and Low-power DDR2-SDRAM devices. */
#define MPDDRC_CR_NDQS (0x1u << 21) /**< \brief (MPDDRC_CR) Not DQS */
#define   MPDDRC_CR_NDQS_ENABLED (0x0u << 21) /**< \brief (MPDDRC_CR) Not DQS is enabled. */
#define   MPDDRC_CR_NDQS_DISABLED (0x1u << 21) /**< \brief (MPDDRC_CR) Not DQS is disabled. */
#define MPDDRC_CR_DECOD (0x1u << 22) /**< \brief (MPDDRC_CR) Type of Decoding */
#define   MPDDRC_CR_DECOD_SEQUENTIAL (0x0u << 22) /**< \brief (MPDDRC_CR) Method for address mapping where banks alternate at each last DDR-SDRAM page of the current bank. */
#define   MPDDRC_CR_DECOD_INTERLEAVED (0x1u << 22) /**< \brief (MPDDRC_CR) Method for address mapping where banks alternate at each SDRAM end page of the current bank. */
#define MPDDRC_CR_UNAL (0x1u << 23) /**< \brief (MPDDRC_CR) Support Unaligned Access */
#define   MPDDRC_CR_UNAL_UNSUPPORTED (0x0u << 23) /**< \brief (MPDDRC_CR) Unaligned access is not supported. */
#define   MPDDRC_CR_UNAL_SUPPORTED (0x1u << 23) /**< \brief (MPDDRC_CR) Unaligned access is supported. */
/* -------- MPDDRC_TPR0 : (MPDDRC Offset: 0x0C) MPDDRC Timing Parameter 0 Register -------- */
#define MPDDRC_TPR0_TRAS_Pos 0
#define MPDDRC_TPR0_TRAS_Msk (0xfu << MPDDRC_TPR0_TRAS_Pos) /**< \brief (MPDDRC_TPR0) Active to Precharge Delay */
#define MPDDRC_TPR0_TRAS(value) ((MPDDRC_TPR0_TRAS_Msk & ((value) << MPDDRC_TPR0_TRAS_Pos)))
#define MPDDRC_TPR0_TRCD_Pos 4
#define MPDDRC_TPR0_TRCD_Msk (0xfu << MPDDRC_TPR0_TRCD_Pos) /**< \brief (MPDDRC_TPR0) Row to Column Delay */
#define MPDDRC_TPR0_TRCD(value) ((MPDDRC_TPR0_TRCD_Msk & ((value) << MPDDRC_TPR0_TRCD_Pos)))
#define MPDDRC_TPR0_TWR_Pos 8
#define MPDDRC_TPR0_TWR_Msk (0xfu << MPDDRC_TPR0_TWR_Pos) /**< \brief (MPDDRC_TPR0) Write Recovery Delay */
#define MPDDRC_TPR0_TWR(value) ((MPDDRC_TPR0_TWR_Msk & ((value) << MPDDRC_TPR0_TWR_Pos)))
#define MPDDRC_TPR0_TRC_Pos 12
#define MPDDRC_TPR0_TRC_Msk (0xfu << MPDDRC_TPR0_TRC_Pos) /**< \brief (MPDDRC_TPR0) Row Cycle Delay */
#define MPDDRC_TPR0_TRC(value) ((MPDDRC_TPR0_TRC_Msk & ((value) << MPDDRC_TPR0_TRC_Pos)))
#define MPDDRC_TPR0_TRP_Pos 16
#define MPDDRC_TPR0_TRP_Msk (0xfu << MPDDRC_TPR0_TRP_Pos) /**< \brief (MPDDRC_TPR0) Row Precharge Delay */
#define MPDDRC_TPR0_TRP(value) ((MPDDRC_TPR0_TRP_Msk & ((value) << MPDDRC_TPR0_TRP_Pos)))
#define MPDDRC_TPR0_TRRD_Pos 20
#define MPDDRC_TPR0_TRRD_Msk (0xfu << MPDDRC_TPR0_TRRD_Pos) /**< \brief (MPDDRC_TPR0) Active BankA to Active BankB */
#define MPDDRC_TPR0_TRRD(value) ((MPDDRC_TPR0_TRRD_Msk & ((value) << MPDDRC_TPR0_TRRD_Pos)))
#define MPDDRC_TPR0_TWTR_Pos 24
#define MPDDRC_TPR0_TWTR_Msk (0xfu << MPDDRC_TPR0_TWTR_Pos) /**< \brief (MPDDRC_TPR0) Internal Write to Read Delay */
#define MPDDRC_TPR0_TWTR(value) ((MPDDRC_TPR0_TWTR_Msk & ((value) << MPDDRC_TPR0_TWTR_Pos)))
#define MPDDRC_TPR0_TMRD_Pos 28
#define MPDDRC_TPR0_TMRD_Msk (0xfu << MPDDRC_TPR0_TMRD_Pos) /**< \brief (MPDDRC_TPR0) Load Mode Register Command to Activate or Refresh Command */
#define MPDDRC_TPR0_TMRD(value) ((MPDDRC_TPR0_TMRD_Msk & ((value) << MPDDRC_TPR0_TMRD_Pos)))
/* -------- MPDDRC_TPR1 : (MPDDRC Offset: 0x10) MPDDRC Timing Parameter 1 Register -------- */
#define MPDDRC_TPR1_TRFC_Pos 0
#define MPDDRC_TPR1_TRFC_Msk (0x7fu << MPDDRC_TPR1_TRFC_Pos) /**< \brief (MPDDRC_TPR1) Row Cycle Delay */
#define MPDDRC_TPR1_TRFC(value) ((MPDDRC_TPR1_TRFC_Msk & ((value) << MPDDRC_TPR1_TRFC_Pos)))
#define MPDDRC_TPR1_TXSNR_Pos 8
#define MPDDRC_TPR1_TXSNR_Msk (0xffu << MPDDRC_TPR1_TXSNR_Pos) /**< \brief (MPDDRC_TPR1) Exit Self-refresh Delay to Non Read Command */
#define MPDDRC_TPR1_TXSNR(value) ((MPDDRC_TPR1_TXSNR_Msk & ((value) << MPDDRC_TPR1_TXSNR_Pos)))
#define MPDDRC_TPR1_TXSRD_Pos 16
#define MPDDRC_TPR1_TXSRD_Msk (0xffu << MPDDRC_TPR1_TXSRD_Pos) /**< \brief (MPDDRC_TPR1) Exit Self-refresh Delay to Read Command */
#define MPDDRC_TPR1_TXSRD(value) ((MPDDRC_TPR1_TXSRD_Msk & ((value) << MPDDRC_TPR1_TXSRD_Pos)))
#define MPDDRC_TPR1_TXP_Pos 24
#define MPDDRC_TPR1_TXP_Msk (0xfu << MPDDRC_TPR1_TXP_Pos) /**< \brief (MPDDRC_TPR1) Exit Power-down Delay to First Command */
#define MPDDRC_TPR1_TXP(value) ((MPDDRC_TPR1_TXP_Msk & ((value) << MPDDRC_TPR1_TXP_Pos)))
/* -------- MPDDRC_TPR2 : (MPDDRC Offset: 0x14) MPDDRC Timing Parameter 2 Register -------- */
#define MPDDRC_TPR2_TXARD_Pos 0
#define MPDDRC_TPR2_TXARD_Msk (0xfu << MPDDRC_TPR2_TXARD_Pos) /**< \brief (MPDDRC_TPR2) Exit Active Power Down Delay to Read Command in Mode "Fast Exit" */
#define MPDDRC_TPR2_TXARD(value) ((MPDDRC_TPR2_TXARD_Msk & ((value) << MPDDRC_TPR2_TXARD_Pos)))
#define MPDDRC_TPR2_TXARDS_Pos 4
#define MPDDRC_TPR2_TXARDS_Msk (0xfu << MPDDRC_TPR2_TXARDS_Pos) /**< \brief (MPDDRC_TPR2) Exit Active Power Down Delay to Read Command in Mode "Slow Exit" */
#define MPDDRC_TPR2_TXARDS(value) ((MPDDRC_TPR2_TXARDS_Msk & ((value) << MPDDRC_TPR2_TXARDS_Pos)))
#define MPDDRC_TPR2_TRPA_Pos 8
#define MPDDRC_TPR2_TRPA_Msk (0xfu << MPDDRC_TPR2_TRPA_Pos) /**< \brief (MPDDRC_TPR2) Row Precharge All Delay */
#define MPDDRC_TPR2_TRPA(value) ((MPDDRC_TPR2_TRPA_Msk & ((value) << MPDDRC_TPR2_TRPA_Pos)))
#define MPDDRC_TPR2_TRTP_Pos 12
#define MPDDRC_TPR2_TRTP_Msk (0x7u << MPDDRC_TPR2_TRTP_Pos) /**< \brief (MPDDRC_TPR2) Read to Precharge */
#define MPDDRC_TPR2_TRTP(value) ((MPDDRC_TPR2_TRTP_Msk & ((value) << MPDDRC_TPR2_TRTP_Pos)))
#define MPDDRC_TPR2_TFAW_Pos 16
#define MPDDRC_TPR2_TFAW_Msk (0xfu << MPDDRC_TPR2_TFAW_Pos) /**< \brief (MPDDRC_TPR2) Four Active Windows */
#define MPDDRC_TPR2_TFAW(value) ((MPDDRC_TPR2_TFAW_Msk & ((value) << MPDDRC_TPR2_TFAW_Pos)))
/* -------- MPDDRC_LPR : (MPDDRC Offset: 0x1C) MPDDRC Low-power Register -------- */
#define MPDDRC_LPR_LPCB_Pos 0
#define MPDDRC_LPR_LPCB_Msk (0x3u << MPDDRC_LPR_LPCB_Pos) /**< \brief (MPDDRC_LPR) Low-power Command Bit */
#define   MPDDRC_LPR_LPCB_NOLOWPOWER (0x0u << 0) /**< \brief (MPDDRC_LPR) Low-power feature is inhibited. No power-down, self-refresh and deep-power modes are issued to the DDR-SDRAM device. */
#define   MPDDRC_LPR_LPCB_SELFREFRESH (0x1u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a self-refresh command to the DDR-SDRAM device, the clock(s) is/are deactivated and the CKE signal is set low. The DDR-SDRAM device leaves the self-refresh mode when accessed and reenters it after the access. */
#define   MPDDRC_LPR_LPCB_POWERDOWN (0x2u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a Power-down command to the DDR-SDRAM device after each access, the CKE signal is set low. The DDR-SDRAM device leaves the power-down mode when accessed and reenters it after the access. */
#define   MPDDRC_LPR_LPCB_DEEPPOWERDOWN (0x3u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a Deep Power-down command to the Low-power DDR-SDRAM device. */
#define MPDDRC_LPR_CLK_FR (0x1u << 2) /**< \brief (MPDDRC_LPR) Clock Frozen Command Bit */
#define   MPDDRC_LPR_CLK_FR_DISABLED (0x0u << 2) /**< \brief (MPDDRC_LPR) Clock(s) is/are not frozen. */
#define   MPDDRC_LPR_CLK_FR_ENABLED (0x1u << 2) /**< \brief (MPDDRC_LPR) Clock(s) is/are frozen. */
#define MPDDRC_LPR_LPDDR2_PWOFF (0x1u << 3) /**< \brief (MPDDRC_LPR) LPDDR2 Power Off Bit */
#define   MPDDRC_LPR_LPDDR2_PWOFF_DISABLED (0x0u << 3) /**< \brief (MPDDRC_LPR) No power off sequence applied to LPDDR2. */
#define   MPDDRC_LPR_LPDDR2_PWOFF_ENABLED (0x1u << 3) /**< \brief (MPDDRC_LPR) A power off sequence is applied to the LPDDR2 device. CKE is forced low. */
#define MPDDRC_LPR_PASR_Pos 4
#define MPDDRC_LPR_PASR_Msk (0x7u << MPDDRC_LPR_PASR_Pos) /**< \brief (MPDDRC_LPR) Partial Array Self-refresh */
#define MPDDRC_LPR_PASR(value) ((MPDDRC_LPR_PASR_Msk & ((value) << MPDDRC_LPR_PASR_Pos)))
#define MPDDRC_LPR_DS_Pos 8
#define MPDDRC_LPR_DS_Msk (0x7u << MPDDRC_LPR_DS_Pos) /**< \brief (MPDDRC_LPR) Drive Strength */
#define MPDDRC_LPR_DS(value) ((MPDDRC_LPR_DS_Msk & ((value) << MPDDRC_LPR_DS_Pos)))
#define MPDDRC_LPR_TIMEOUT_Pos 12
#define MPDDRC_LPR_TIMEOUT_Msk (0x3u << MPDDRC_LPR_TIMEOUT_Pos) /**< \brief (MPDDRC_LPR) Time Between Last Transfer and Low Power Mode */
#define   MPDDRC_LPR_TIMEOUT_NONE (0x0u << 12) /**< \brief (MPDDRC_LPR) SDRAM low-power mode is activated immediately after the end of the last transfer. */
#define   MPDDRC_LPR_TIMEOUT_DELAY_64_CLK (0x1u << 12) /**< \brief (MPDDRC_LPR) SDRAM low-power mode is activated 64 clock cycles after the end of the last transfer. */
#define   MPDDRC_LPR_TIMEOUT_DELAY_128_CLK (0x2u << 12) /**< \brief (MPDDRC_LPR) SDRAM low-power mode is activated 128 clock cycles after the end of the last transfer. */
#define MPDDRC_LPR_APDE (0x1u << 16) /**< \brief (MPDDRC_LPR) Active Power Down Exit Time */
#define   MPDDRC_LPR_APDE_DDR2_FAST_EXIT (0x0u << 16) /**< \brief (MPDDRC_LPR) Fast Exit from Power Down. The DDR2-SDRAM devices only. */
#define   MPDDRC_LPR_APDE_DDR2_SLOW_EXIT (0x1u << 16) /**< \brief (MPDDRC_LPR) Slow Exit from Power Down. The DDR2-SDRAM devices only. */
#define MPDDRC_LPR_UPD_MR_Pos 20
#define MPDDRC_LPR_UPD_MR_Msk (0x3u << MPDDRC_LPR_UPD_MR_Pos) /**< \brief (MPDDRC_LPR) Update Load Mode Register and Extended Mode Register */
#define   MPDDRC_LPR_UPD_MR_NO_UPDATE (0x0u << 20) /**< \brief (MPDDRC_LPR) Update of Load Mode and Extended Mode registers is disabled. */
#define   MPDDRC_LPR_UPD_MR_UPDATE_SHAREDBUS (0x1u << 20) /**< \brief (MPDDRC_LPR) DDRSDRC shares an external bus. Automatic update is done during a refresh command and a pending read or write access in the SDRAM device. */
#define   MPDDRC_LPR_UPD_MR_UPDATE_NOSHAREDBUS (0x2u << 20) /**< \brief (MPDDRC_LPR) DDRSDRC does not share an external bus. Automatic update is done before entering in self-refresh mode. */
/* -------- MPDDRC_MD : (MPDDRC Offset: 0x20) MPDDRC Memory Device Register -------- */
#define MPDDRC_MD_MD_Pos 0
#define MPDDRC_MD_MD_Msk (0x7u << MPDDRC_MD_MD_Pos) /**< \brief (MPDDRC_MD) Memory Device */
#define   MPDDRC_MD_MD_DDR_SDRAM (0x2u << 0) /**< \brief (MPDDRC_MD) DDR1-SDRAM */
#define   MPDDRC_MD_MD_LPDDR_SDRAM (0x3u << 0) /**< \brief (MPDDRC_MD) Low-power DDR1-SDRAM */
#define   MPDDRC_MD_MD_DDR2_SDRAM (0x6u << 0) /**< \brief (MPDDRC_MD) DDR2-SDRAM */
#define   MPDDRC_MD_MD_LPDDR2_SDRAM (0x7u << 0) /**< \brief (MPDDRC_MD) Low-Power DDR2-SDRAM */
#define MPDDRC_MD_DBW (0x1u << 4) /**< \brief (MPDDRC_MD) Data Bus Width */
#define   MPDDRC_MD_DBW_DBW_32_BITS (0x0u << 4) /**< \brief (MPDDRC_MD) Data bus width is 32 bits. */
#define   MPDDRC_MD_DBW_DBW_16_BITS (0x1u << 4) /**< \brief (MPDDRC_MD) Data bus width is 16 bits. */
/* -------- MPDDRC_LPDDR2_LPR : (MPDDRC Offset: 0x28) MPDDRC LPDDR2 Low-power Register -------- */
#define MPDDRC_LPDDR2_LPR_BK_MASK_PASR_Pos 0
#define MPDDRC_LPDDR2_LPR_BK_MASK_PASR_Msk (0xffu << MPDDRC_LPDDR2_LPR_BK_MASK_PASR_Pos) /**< \brief (MPDDRC_LPDDR2_LPR) Bank Mask Bit/PASR */
#define MPDDRC_LPDDR2_LPR_BK_MASK_PASR(value) ((MPDDRC_LPDDR2_LPR_BK_MASK_PASR_Msk & ((value) << MPDDRC_LPDDR2_LPR_BK_MASK_PASR_Pos)))
#define MPDDRC_LPDDR2_LPR_SEG_MASK_Pos 8
#define MPDDRC_LPDDR2_LPR_SEG_MASK_Msk (0xffffu << MPDDRC_LPDDR2_LPR_SEG_MASK_Pos) /**< \brief (MPDDRC_LPDDR2_LPR) Segment Mask Bit */
#define MPDDRC_LPDDR2_LPR_SEG_MASK(value) ((MPDDRC_LPDDR2_LPR_SEG_MASK_Msk & ((value) << MPDDRC_LPDDR2_LPR_SEG_MASK_Pos)))
#define MPDDRC_LPDDR2_LPR_DS_Pos 24
#define MPDDRC_LPDDR2_LPR_DS_Msk (0xfu << MPDDRC_LPDDR2_LPR_DS_Pos) /**< \brief (MPDDRC_LPDDR2_LPR) Drive strength */
#define MPDDRC_LPDDR2_LPR_DS(value) ((MPDDRC_LPDDR2_LPR_DS_Msk & ((value) << MPDDRC_LPDDR2_LPR_DS_Pos)))
/* -------- MPDDRC_LPDDR2_CAL_MR4 : (MPDDRC Offset: 0x2C) MPDDRC LPDDR2 Calibration and MR4 Register -------- */
#define MPDDRC_LPDDR2_CAL_MR4_COUNT_CAL_Pos 0
#define MPDDRC_LPDDR2_CAL_MR4_COUNT_CAL_Msk (0xffffu << MPDDRC_LPDDR2_CAL_MR4_COUNT_CAL_Pos) /**< \brief (MPDDRC_LPDDR2_CAL_MR4) LPDDR2 Calibration Timer Count */
#define MPDDRC_LPDDR2_CAL_MR4_COUNT_CAL(value) ((MPDDRC_LPDDR2_CAL_MR4_COUNT_CAL_Msk & ((value) << MPDDRC_LPDDR2_CAL_MR4_COUNT_CAL_Pos)))
#define MPDDRC_LPDDR2_CAL_MR4_MR4_READ_Pos 16
#define MPDDRC_LPDDR2_CAL_MR4_MR4_READ_Msk (0xffffu << MPDDRC_LPDDR2_CAL_MR4_MR4_READ_Pos) /**< \brief (MPDDRC_LPDDR2_CAL_MR4) Mode Register 4 Read Interval */
#define MPDDRC_LPDDR2_CAL_MR4_MR4_READ(value) ((MPDDRC_LPDDR2_CAL_MR4_MR4_READ_Msk & ((value) << MPDDRC_LPDDR2_CAL_MR4_MR4_READ_Pos)))
/* -------- MPDDRC_LPDDR2_TIM_CAL : (MPDDRC Offset: 0x30) MPDDRC LPDDR2 Timing Calibration Register -------- */
#define MPDDRC_LPDDR2_TIM_CAL_ZQCS_Pos 0
#define MPDDRC_LPDDR2_TIM_CAL_ZQCS_Msk (0xffu << MPDDRC_LPDDR2_TIM_CAL_ZQCS_Pos) /**< \brief (MPDDRC_LPDDR2_TIM_CAL) ZQ Calibration Short */
#define MPDDRC_LPDDR2_TIM_CAL_ZQCS(value) ((MPDDRC_LPDDR2_TIM_CAL_ZQCS_Msk & ((value) << MPDDRC_LPDDR2_TIM_CAL_ZQCS_Pos)))
/* -------- MPDDRC_IO_CALIBR : (MPDDRC Offset: 0x34) MPDDRC IO Calibration -------- */
#define MPDDRC_IO_CALIBR_RDIV_Pos 0
#define MPDDRC_IO_CALIBR_RDIV_Msk (0x7u << MPDDRC_IO_CALIBR_RDIV_Pos) /**< \brief (MPDDRC_IO_CALIBR) Resistor Divider, Output Driver Impedance */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_34 (0x1u << 0) /**< \brief (MPDDRC_IO_CALIBR) LPDDR2 RZQ = 34,3 Ohms, DDR2/LPDDR1: Not applicable */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_40_RZQ_33_3 (0x2u << 0) /**< \brief (MPDDRC_IO_CALIBR) LPDDR2:RZQ = 40 Ohms, DDR2/LPDDR1: RZQ = 33,3 Ohms */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_48_RZQ_40 (0x3u << 0) /**< \brief (MPDDRC_IO_CALIBR) LPDDR2:RZQ =48 Ohms, DDR2/LPDDR1: RZQ =40 Ohms */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_60_RZQ_50 (0x4u << 0) /**< \brief (MPDDRC_IO_CALIBR) LPDDR2:RZQ =60 Ohms, DDR2/LPDDR1: RZQ =50 Ohms */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_80_RZQ_66_7 (0x6u << 0) /**< \brief (MPDDRC_IO_CALIBR) LPDDR2: RZQ = 80 Ohms, DDR2/LPDDR1: RZQ = 66,7 Ohms */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_120_RZQ_100 (0x7u << 0) /**< \brief (MPDDRC_IO_CALIBR) LPDDR2:RZQ = 120 Ohms, DDR2/LPDDR1: RZQ = 100 Ohms */
#define MPDDRC_IO_CALIBR_EN_CALIB (0x1u << 4) /**< \brief (MPDDRC_IO_CALIBR) Enable of the Calibration */
#define   MPDDRC_IO_CALIBR_EN_CALIB_DISABLE_CALIBRATION (0x0u << 4) /**< \brief (MPDDRC_IO_CALIBR) Calibration is disabled. */
#define   MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION (0x1u << 4) /**< \brief (MPDDRC_IO_CALIBR) Calibration is enabled. */
#define MPDDRC_IO_CALIBR_TZQIO_Pos 8
#define MPDDRC_IO_CALIBR_TZQIO_Msk (0x7u << MPDDRC_IO_CALIBR_TZQIO_Pos) /**< \brief (MPDDRC_IO_CALIBR) IO Calibration */
#define MPDDRC_IO_CALIBR_TZQIO(value) ((MPDDRC_IO_CALIBR_TZQIO_Msk & ((value) << MPDDRC_IO_CALIBR_TZQIO_Pos)))
#define MPDDRC_IO_CALIBR_CALCODEP_Pos 16
#define MPDDRC_IO_CALIBR_CALCODEP_Msk (0xfu << MPDDRC_IO_CALIBR_CALCODEP_Pos) /**< \brief (MPDDRC_IO_CALIBR) Number of Transistor P */
#define MPDDRC_IO_CALIBR_CALCODEP(value) ((MPDDRC_IO_CALIBR_CALCODEP_Msk & ((value) << MPDDRC_IO_CALIBR_CALCODEP_Pos)))
#define MPDDRC_IO_CALIBR_CALCODEN_Pos 20
#define MPDDRC_IO_CALIBR_CALCODEN_Msk (0xfu << MPDDRC_IO_CALIBR_CALCODEN_Pos) /**< \brief (MPDDRC_IO_CALIBR) Number of Transistor N */
#define MPDDRC_IO_CALIBR_CALCODEN(value) ((MPDDRC_IO_CALIBR_CALCODEN_Msk & ((value) << MPDDRC_IO_CALIBR_CALCODEN_Pos)))
/* -------- MPDDRC_OCMS : (MPDDRC Offset: 0x38) MPDDRC OCMS Register -------- */
#define MPDDRC_OCMS_SCR_EN (0x1u << 0) /**< \brief (MPDDRC_OCMS) Scrambling Enable */
/* -------- MPDDRC_OCMS_KEY1 : (MPDDRC Offset: 0x3C) MPDDRC OCMS KEY1 Register -------- */
#define MPDDRC_OCMS_KEY1_KEY1_Pos 0
#define MPDDRC_OCMS_KEY1_KEY1_Msk (0xffffffffu << MPDDRC_OCMS_KEY1_KEY1_Pos) /**< \brief (MPDDRC_OCMS_KEY1) Off-chip Memory Scrambling (OCMS) Key Part 1 */
#define MPDDRC_OCMS_KEY1_KEY1(value) ((MPDDRC_OCMS_KEY1_KEY1_Msk & ((value) << MPDDRC_OCMS_KEY1_KEY1_Pos)))
/* -------- MPDDRC_OCMS_KEY2 : (MPDDRC Offset: 0x40) MPDDRC OCMS KEY2 Register -------- */
#define MPDDRC_OCMS_KEY2_KEY2_Pos 0
#define MPDDRC_OCMS_KEY2_KEY2_Msk (0xffffffffu << MPDDRC_OCMS_KEY2_KEY2_Pos) /**< \brief (MPDDRC_OCMS_KEY2) Off-chip Memory Scrambling (OCMS) Key Part 2 */
#define MPDDRC_OCMS_KEY2_KEY2(value) ((MPDDRC_OCMS_KEY2_KEY2_Msk & ((value) << MPDDRC_OCMS_KEY2_KEY2_Pos)))
/* -------- MPDDRC_CONF_ARBITER : (MPDDRC Offset: 0x44) MPDDRC Configuration Arbiter -------- */
#define MPDDRC_CONF_ARBITER_ARB_Pos 0
#define MPDDRC_CONF_ARBITER_ARB_Msk (0x3u << MPDDRC_CONF_ARBITER_ARB_Pos) /**< \brief (MPDDRC_CONF_ARBITER) Type of Arbitration */
#define   MPDDRC_CONF_ARBITER_ARB_ROUND (0x0u << 0) /**< \brief (MPDDRC_CONF_ARBITER) Round Robin */
#define   MPDDRC_CONF_ARBITER_ARB_NB_REQUEST (0x1u << 0) /**< \brief (MPDDRC_CONF_ARBITER) Request Policy */
#define   MPDDRC_CONF_ARBITER_ARB_BANDWIDTH (0x2u << 0) /**< \brief (MPDDRC_CONF_ARBITER) Bandwidth Policy */
#define MPDDRC_CONF_ARBITER_BDW_BURST (0x1u << 2) /**< \brief (MPDDRC_CONF_ARBITER) Bandwidth is Reached or Bandwidth and Current Burst Access is Ended */
#define MPDDRC_CONF_ARBITER_BDW_MAX_CUR (0x1u << 3) /**< \brief (MPDDRC_CONF_ARBITER) Bandwidth Max or Current */
#define MPDDRC_CONF_ARBITER_RQ_WD_P0 (0x1u << 8) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P1 (0x1u << 9) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P2 (0x1u << 10) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P3 (0x1u << 11) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P4 (0x1u << 12) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P5 (0x1u << 13) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P6 (0x1u << 14) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P7 (0x1u << 15) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from port X */
#define MPDDRC_CONF_ARBITER_MA_PR_P0 (0x1u << 16) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P1 (0x1u << 17) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P2 (0x1u << 18) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P3 (0x1u << 19) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P4 (0x1u << 20) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P5 (0x1u << 21) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P6 (0x1u << 22) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P7 (0x1u << 23) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
/* -------- MPDDRC_TIMEOUT : (MPDDRC Offset: 0x48) MPDDRC Time-out Port 0/1/2/3 -------- */
#define MPDDRC_TIMEOUT_TIMEOUT_P0_Pos 0
#define MPDDRC_TIMEOUT_TIMEOUT_P0_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P0_Pos) /**< \brief (MPDDRC_TIMEOUT) Time-out for Ports 0, 1, 2, 3, 4, 5, 6 and 7 */
#define MPDDRC_TIMEOUT_TIMEOUT_P0(value) ((MPDDRC_TIMEOUT_TIMEOUT_P0_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P0_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P1_Pos 4
#define MPDDRC_TIMEOUT_TIMEOUT_P1_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P1_Pos) /**< \brief (MPDDRC_TIMEOUT) Time-out for Ports 0, 1, 2, 3, 4, 5, 6 and 7 */
#define MPDDRC_TIMEOUT_TIMEOUT_P1(value) ((MPDDRC_TIMEOUT_TIMEOUT_P1_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P1_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P2_Pos 8
#define MPDDRC_TIMEOUT_TIMEOUT_P2_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P2_Pos) /**< \brief (MPDDRC_TIMEOUT) Time-out for Ports 0, 1, 2, 3, 4, 5, 6 and 7 */
#define MPDDRC_TIMEOUT_TIMEOUT_P2(value) ((MPDDRC_TIMEOUT_TIMEOUT_P2_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P2_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P3_Pos 12
#define MPDDRC_TIMEOUT_TIMEOUT_P3_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P3_Pos) /**< \brief (MPDDRC_TIMEOUT) Time-out for Ports 0, 1, 2, 3, 4, 5, 6 and 7 */
#define MPDDRC_TIMEOUT_TIMEOUT_P3(value) ((MPDDRC_TIMEOUT_TIMEOUT_P3_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P3_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P4_Pos 16
#define MPDDRC_TIMEOUT_TIMEOUT_P4_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P4_Pos) /**< \brief (MPDDRC_TIMEOUT) Time-out for Ports 0, 1, 2, 3, 4, 5, 6 and 7 */
#define MPDDRC_TIMEOUT_TIMEOUT_P4(value) ((MPDDRC_TIMEOUT_TIMEOUT_P4_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P4_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P5_Pos 20
#define MPDDRC_TIMEOUT_TIMEOUT_P5_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P5_Pos) /**< \brief (MPDDRC_TIMEOUT) Time-out for Ports 0, 1, 2, 3, 4, 5, 6 and 7 */
#define MPDDRC_TIMEOUT_TIMEOUT_P5(value) ((MPDDRC_TIMEOUT_TIMEOUT_P5_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P5_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P6_Pos 24
#define MPDDRC_TIMEOUT_TIMEOUT_P6_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P6_Pos) /**< \brief (MPDDRC_TIMEOUT) Time-out for Ports 0, 1, 2, 3, 4, 5, 6 and 7 */
#define MPDDRC_TIMEOUT_TIMEOUT_P6(value) ((MPDDRC_TIMEOUT_TIMEOUT_P6_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P6_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P7_Pos 28
#define MPDDRC_TIMEOUT_TIMEOUT_P7_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P7_Pos) /**< \brief (MPDDRC_TIMEOUT) Time-out for Ports 0, 1, 2, 3, 4, 5, 6 and 7 */
#define MPDDRC_TIMEOUT_TIMEOUT_P7(value) ((MPDDRC_TIMEOUT_TIMEOUT_P7_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P7_Pos)))
/* -------- MPDDRC_REQ_PORT_0123 : (MPDDRC Offset: 0x4C) MPDDRC Time-out Request Port 0/1/2/3 -------- */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Pos 0
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Msk (0xffu << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Pos) /**< \brief (MPDDRC_REQ_PORT_0123) Number of Requests, Number of Words or Bandwidth Allocation from Port 0-1-2-3 */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0(value) ((MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Msk & ((value) << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Pos)))
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Pos 8
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Msk (0xffu << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Pos) /**< \brief (MPDDRC_REQ_PORT_0123) Number of Requests, Number of Words or Bandwidth Allocation from Port 0-1-2-3 */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1(value) ((MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Msk & ((value) << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Pos)))
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Pos 16
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Msk (0xffu << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Pos) /**< \brief (MPDDRC_REQ_PORT_0123) Number of Requests, Number of Words or Bandwidth Allocation from Port 0-1-2-3 */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2(value) ((MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Msk & ((value) << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Pos)))
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Pos 24
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Msk (0xffu << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Pos) /**< \brief (MPDDRC_REQ_PORT_0123) Number of Requests, Number of Words or Bandwidth Allocation from Port 0-1-2-3 */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3(value) ((MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Msk & ((value) << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Pos)))
/* -------- MPDDRC_REQ_PORT_4567 : (MPDDRC Offset: 0x50) MPDDRC Time-out Request Port 4/5/6/7 -------- */
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P4_Pos 0
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P4_Msk (0xffu << MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P4_Pos) /**< \brief (MPDDRC_REQ_PORT_4567) Number of Requests, Number of Words or Bandwidth allocation from port 4-5-6-7 */
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P4(value) ((MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P4_Msk & ((value) << MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P4_Pos)))
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P5_Pos 8
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P5_Msk (0xffu << MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P5_Pos) /**< \brief (MPDDRC_REQ_PORT_4567) Number of Requests, Number of Words or Bandwidth allocation from port 4-5-6-7 */
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P5(value) ((MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P5_Msk & ((value) << MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P5_Pos)))
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P6_Pos 16
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P6_Msk (0xffu << MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P6_Pos) /**< \brief (MPDDRC_REQ_PORT_4567) Number of Requests, Number of Words or Bandwidth allocation from port 4-5-6-7 */
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P6(value) ((MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P6_Msk & ((value) << MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P6_Pos)))
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P7_Pos 24
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P7_Msk (0xffu << MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P7_Pos) /**< \brief (MPDDRC_REQ_PORT_4567) Number of Requests, Number of Words or Bandwidth allocation from port 4-5-6-7 */
#define MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P7(value) ((MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P7_Msk & ((value) << MPDDRC_REQ_PORT_4567_NRQ_NWD_BDW_P7_Pos)))
/* -------- MPDDRC_BDW_PORT_0123 : (MPDDRC Offset: 0x54) MPDDRC Bandwidth Port 0/1/2/3 -------- */
#define MPDDRC_BDW_PORT_0123_BDW_P0_Pos 0
#define MPDDRC_BDW_PORT_0123_BDW_P0_Msk (0x7fu << MPDDRC_BDW_PORT_0123_BDW_P0_Pos) /**< \brief (MPDDRC_BDW_PORT_0123) Current/Maximum Bandwidth from Port 0-1-2-3 */
#define MPDDRC_BDW_PORT_0123_BDW_P1_Pos 8
#define MPDDRC_BDW_PORT_0123_BDW_P1_Msk (0x7fu << MPDDRC_BDW_PORT_0123_BDW_P1_Pos) /**< \brief (MPDDRC_BDW_PORT_0123) Current/Maximum Bandwidth from Port 0-1-2-3 */
#define MPDDRC_BDW_PORT_0123_BDW_P2_Pos 16
#define MPDDRC_BDW_PORT_0123_BDW_P2_Msk (0x7fu << MPDDRC_BDW_PORT_0123_BDW_P2_Pos) /**< \brief (MPDDRC_BDW_PORT_0123) Current/Maximum Bandwidth from Port 0-1-2-3 */
#define MPDDRC_BDW_PORT_0123_BDW_P3_Pos 24
#define MPDDRC_BDW_PORT_0123_BDW_P3_Msk (0x7fu << MPDDRC_BDW_PORT_0123_BDW_P3_Pos) /**< \brief (MPDDRC_BDW_PORT_0123) Current/Maximum Bandwidth from Port 0-1-2-3 */
/* -------- MPDDRC_BDW_PORT_4567 : (MPDDRC Offset: 0x58) MPDDRC Bandwidth Port 4/5/6/7 -------- */
#define MPDDRC_BDW_PORT_4567_BDW_P4_Pos 0
#define MPDDRC_BDW_PORT_4567_BDW_P4_Msk (0x7fu << MPDDRC_BDW_PORT_4567_BDW_P4_Pos) /**< \brief (MPDDRC_BDW_PORT_4567) Current/Maximum Bandwidth from Port 4-5-6-7 */
#define MPDDRC_BDW_PORT_4567_BDW_P5_Pos 8
#define MPDDRC_BDW_PORT_4567_BDW_P5_Msk (0x7fu << MPDDRC_BDW_PORT_4567_BDW_P5_Pos) /**< \brief (MPDDRC_BDW_PORT_4567) Current/Maximum Bandwidth from Port 4-5-6-7 */
#define MPDDRC_BDW_PORT_4567_BDW_P6_Pos 16
#define MPDDRC_BDW_PORT_4567_BDW_P6_Msk (0x7fu << MPDDRC_BDW_PORT_4567_BDW_P6_Pos) /**< \brief (MPDDRC_BDW_PORT_4567) Current/Maximum Bandwidth from Port 4-5-6-7 */
#define MPDDRC_BDW_PORT_4567_BDW_P7_Pos 24
#define MPDDRC_BDW_PORT_4567_BDW_P7_Msk (0x7fu << MPDDRC_BDW_PORT_4567_BDW_P7_Pos) /**< \brief (MPDDRC_BDW_PORT_4567) Current/Maximum Bandwidth from Port 4-5-6-7 */
/* -------- MPDDRC_RD_DATA_PATH : (MPDDRC Offset: 0x5C) MPDDRC_READ_DATA_PATH -------- */
#define MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_Pos 0
#define MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_Msk (0x3u << MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_Pos) /**< \brief (MPDDRC_RD_DATA_PATH) Shift Sampling Point of Data */
#define   MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_NO_SHIFT (0x0u << 0) /**< \brief (MPDDRC_RD_DATA_PATH) Initial sampling point. */
#define   MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE (0x1u << 0) /**< \brief (MPDDRC_RD_DATA_PATH) Sampling point is shifted of one cycle. */
#define   MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_TWO_CYCLES (0x2u << 0) /**< \brief (MPDDRC_RD_DATA_PATH) Sampling point is shifted of two cycles. */
#define   MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_THREE_CYCLES (0x3u << 0) /**< \brief (MPDDRC_RD_DATA_PATH) Sampling point is shifted of three cycles, unique for LPDDR2.Not applicable for the DDR2 and LPDDR1devices. */
/* -------- MPDDRC_SAW[4] : (MPDDRC Offset: 0x60) MPDDRC Smart Adaptation Wrapper 0 Register -------- */
#define MPDDRC_SAW_FLUSH_MAX_Pos 0
#define MPDDRC_SAW_FLUSH_MAX_Msk (0xffu << MPDDRC_SAW_FLUSH_MAX_Pos) /**< \brief (MPDDRC_SAW[4]) Clears FIFO Content */
#define MPDDRC_SAW_FLUSH_MAX(value) ((MPDDRC_SAW_FLUSH_MAX_Msk & ((value) << MPDDRC_SAW_FLUSH_MAX_Pos)))
#define MPDDRC_SAW_INCR_THRESH_Pos 8
#define MPDDRC_SAW_INCR_THRESH_Msk (0x3fu << MPDDRC_SAW_INCR_THRESH_Pos) /**< \brief (MPDDRC_SAW[4]) Incremental Threshold */
#define   MPDDRC_SAW_INCR_THRESH_1_WORD (0x1u << 8) /**< \brief (MPDDRC_SAW[4]) 1 word/dword max */
#define   MPDDRC_SAW_INCR_THRESH_2_WORDS (0x2u << 8) /**< \brief (MPDDRC_SAW[4]) 2 word/dword max */
#define   MPDDRC_SAW_INCR_THRESH_4_WORDS (0x4u << 8) /**< \brief (MPDDRC_SAW[4]) 4 word/dword max */
#define   MPDDRC_SAW_INCR_THRESH_8_WORDS (0x8u << 8) /**< \brief (MPDDRC_SAW[4]) 8 word/dword max */
#define   MPDDRC_SAW_INCR_THRESH_16_WORDS (0x10u << 8) /**< \brief (MPDDRC_SAW[4]) 16 word/dword max */
#define   MPDDRC_SAW_INCR_THRESH_32_WORDS (0x20u << 8) /**< \brief (MPDDRC_SAW[4]) 32 word/dword max */
#define MPDDRC_SAW_PFCH_THRESH_Pos 16
#define MPDDRC_SAW_PFCH_THRESH_Msk (0x3fu << MPDDRC_SAW_PFCH_THRESH_Pos) /**< \brief (MPDDRC_SAW[4]) Prefetch Threshold */
#define   MPDDRC_SAW_PFCH_THRESH_2_WORDS (0x2u << 16) /**< \brief (MPDDRC_SAW[4]) 2 word/dword max */
#define   MPDDRC_SAW_PFCH_THRESH_4_WORDS (0x4u << 16) /**< \brief (MPDDRC_SAW[4]) 4 word/dword max */
#define   MPDDRC_SAW_PFCH_THRESH_8_WORDS (0x8u << 16) /**< \brief (MPDDRC_SAW[4]) 8 word/dword max */
/* -------- MPDDRC_WPMR : (MPDDRC Offset: 0xE4) MPDDRC Write Protect Control Register -------- */
#define MPDDRC_WPMR_WPEN (0x1u << 0) /**< \brief (MPDDRC_WPMR) Write Protection Enable */
#define MPDDRC_WPMR_WPKEY_Pos 8
#define MPDDRC_WPMR_WPKEY_Msk (0xffffffu << MPDDRC_WPMR_WPKEY_Pos) /**< \brief (MPDDRC_WPMR) Write Protection KEY */
#define   MPDDRC_WPMR_WPKEY_PASSWD (0x444452u << 8) /**< \brief (MPDDRC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */
/* -------- MPDDRC_WPSR : (MPDDRC Offset: 0xE8) MPDDRC Write Protect Status Register -------- */
#define MPDDRC_WPSR_WPVS (0x1u << 0) /**< \brief (MPDDRC_WPSR) Write Protection Enable */
#define MPDDRC_WPSR_WPVSRC_Pos 8
#define MPDDRC_WPSR_WPVSRC_Msk (0xffffu << MPDDRC_WPSR_WPVSRC_Pos) /**< \brief (MPDDRC_WPSR) Write Protection Violation Source */
/* -------- MPDDRC_DLL_OS : (MPDDRC Offset: 0x100) MPDDRC DLL Offset Selection Register -------- */
#define MPDDRC_DLL_OS_SELOFF (0x1u << 0) /**< \brief (MPDDRC_DLL_OS) Offset Selection */
/* -------- MPDDRC_DLL_MO : (MPDDRC Offset: 0x104) MPDDRC DLL MASTER Offset Register -------- */
#define MPDDRC_DLL_MO_M0OFF_Pos 0
#define MPDDRC_DLL_MO_M0OFF_Msk (0xffu << MPDDRC_DLL_MO_M0OFF_Pos) /**< \brief (MPDDRC_DLL_MO) Master 0 Delay Line Offset */
#define MPDDRC_DLL_MO_M0OFF(value) ((MPDDRC_DLL_MO_M0OFF_Msk & ((value) << MPDDRC_DLL_MO_M0OFF_Pos)))
/* -------- MPDDRC_DLL_SO0 : (MPDDRC Offset: 0x108) MPDDRC DLL SLAVE Offset 0 Register -------- */
#define MPDDRC_DLL_SO0_S0OFF_Pos 0
#define MPDDRC_DLL_SO0_S0OFF_Msk (0xffu << MPDDRC_DLL_SO0_S0OFF_Pos) /**< \brief (MPDDRC_DLL_SO0) SLAVEx Delay Line Offset */
#define MPDDRC_DLL_SO0_S0OFF(value) ((MPDDRC_DLL_SO0_S0OFF_Msk & ((value) << MPDDRC_DLL_SO0_S0OFF_Pos)))
#define MPDDRC_DLL_SO0_S1OFF_Pos 8
#define MPDDRC_DLL_SO0_S1OFF_Msk (0xffu << MPDDRC_DLL_SO0_S1OFF_Pos) /**< \brief (MPDDRC_DLL_SO0) SLAVEx Delay Line Offset */
#define MPDDRC_DLL_SO0_S1OFF(value) ((MPDDRC_DLL_SO0_S1OFF_Msk & ((value) << MPDDRC_DLL_SO0_S1OFF_Pos)))
#define MPDDRC_DLL_SO0_S2OFF_Pos 16
#define MPDDRC_DLL_SO0_S2OFF_Msk (0xffu << MPDDRC_DLL_SO0_S2OFF_Pos) /**< \brief (MPDDRC_DLL_SO0) SLAVEx Delay Line Offset */
#define MPDDRC_DLL_SO0_S2OFF(value) ((MPDDRC_DLL_SO0_S2OFF_Msk & ((value) << MPDDRC_DLL_SO0_S2OFF_Pos)))
#define MPDDRC_DLL_SO0_S3OFF_Pos 24
#define MPDDRC_DLL_SO0_S3OFF_Msk (0xffu << MPDDRC_DLL_SO0_S3OFF_Pos) /**< \brief (MPDDRC_DLL_SO0) SLAVEx Delay Line Offset */
#define MPDDRC_DLL_SO0_S3OFF(value) ((MPDDRC_DLL_SO0_S3OFF_Msk & ((value) << MPDDRC_DLL_SO0_S3OFF_Pos)))
/* -------- MPDDRC_DLL_SO1 : (MPDDRC Offset: 0x10C) MPDDRC DLL SLAVE Offset 1 Register -------- */
#define MPDDRC_DLL_SO1_S4OFF_Pos 0
#define MPDDRC_DLL_SO1_S4OFF_Msk (0xffu << MPDDRC_DLL_SO1_S4OFF_Pos) /**< \brief (MPDDRC_DLL_SO1) SLAVEx Delay Line Offset */
#define MPDDRC_DLL_SO1_S4OFF(value) ((MPDDRC_DLL_SO1_S4OFF_Msk & ((value) << MPDDRC_DLL_SO1_S4OFF_Pos)))
#define MPDDRC_DLL_SO1_S5OFF_Pos 8
#define MPDDRC_DLL_SO1_S5OFF_Msk (0xffu << MPDDRC_DLL_SO1_S5OFF_Pos) /**< \brief (MPDDRC_DLL_SO1) SLAVEx Delay Line Offset */
#define MPDDRC_DLL_SO1_S5OFF(value) ((MPDDRC_DLL_SO1_S5OFF_Msk & ((value) << MPDDRC_DLL_SO1_S5OFF_Pos)))
#define MPDDRC_DLL_SO1_S6OFF_Pos 16
#define MPDDRC_DLL_SO1_S6OFF_Msk (0xffu << MPDDRC_DLL_SO1_S6OFF_Pos) /**< \brief (MPDDRC_DLL_SO1) SLAVEx Delay Line Offset */
#define MPDDRC_DLL_SO1_S6OFF(value) ((MPDDRC_DLL_SO1_S6OFF_Msk & ((value) << MPDDRC_DLL_SO1_S6OFF_Pos)))
#define MPDDRC_DLL_SO1_S7OFF_Pos 24
#define MPDDRC_DLL_SO1_S7OFF_Msk (0xffu << MPDDRC_DLL_SO1_S7OFF_Pos) /**< \brief (MPDDRC_DLL_SO1) SLAVEx Delay Line Offset */
#define MPDDRC_DLL_SO1_S7OFF(value) ((MPDDRC_DLL_SO1_S7OFF_Msk & ((value) << MPDDRC_DLL_SO1_S7OFF_Pos)))
/* -------- MPDDRC_DLL_WRO : (MPDDRC Offset: 0x110) MPDDRC DLL CLKWR Offset Register -------- */
#define MPDDRC_DLL_WRO_WR0OFF_Pos 0
#define MPDDRC_DLL_WRO_WR0OFF_Msk (0xffu << MPDDRC_DLL_WRO_WR0OFF_Pos) /**< \brief (MPDDRC_DLL_WRO) CLKWRx Delay Line Offset */
#define MPDDRC_DLL_WRO_WR0OFF(value) ((MPDDRC_DLL_WRO_WR0OFF_Msk & ((value) << MPDDRC_DLL_WRO_WR0OFF_Pos)))
#define MPDDRC_DLL_WRO_WR1OFF_Pos 8
#define MPDDRC_DLL_WRO_WR1OFF_Msk (0xffu << MPDDRC_DLL_WRO_WR1OFF_Pos) /**< \brief (MPDDRC_DLL_WRO) CLKWRx Delay Line Offset */
#define MPDDRC_DLL_WRO_WR1OFF(value) ((MPDDRC_DLL_WRO_WR1OFF_Msk & ((value) << MPDDRC_DLL_WRO_WR1OFF_Pos)))
#define MPDDRC_DLL_WRO_WR2OFF_Pos 16
#define MPDDRC_DLL_WRO_WR2OFF_Msk (0xffu << MPDDRC_DLL_WRO_WR2OFF_Pos) /**< \brief (MPDDRC_DLL_WRO) CLKWRx Delay Line Offset */
#define MPDDRC_DLL_WRO_WR2OFF(value) ((MPDDRC_DLL_WRO_WR2OFF_Msk & ((value) << MPDDRC_DLL_WRO_WR2OFF_Pos)))
#define MPDDRC_DLL_WRO_WR3OFF_Pos 24
#define MPDDRC_DLL_WRO_WR3OFF_Msk (0xffu << MPDDRC_DLL_WRO_WR3OFF_Pos) /**< \brief (MPDDRC_DLL_WRO) CLKWRx Delay Line Offset */
#define MPDDRC_DLL_WRO_WR3OFF(value) ((MPDDRC_DLL_WRO_WR3OFF_Msk & ((value) << MPDDRC_DLL_WRO_WR3OFF_Pos)))
/* -------- MPDDRC_DLL_ADO : (MPDDRC Offset: 0x114) MPDDRC DLL CLKAD Offset Register -------- */
#define MPDDRC_DLL_ADO_ADOFF_Pos 0
#define MPDDRC_DLL_ADO_ADOFF_Msk (0xffu << MPDDRC_DLL_ADO_ADOFF_Pos) /**< \brief (MPDDRC_DLL_ADO) CLKAD Delay Line Offset */
#define MPDDRC_DLL_ADO_ADOFF(value) ((MPDDRC_DLL_ADO_ADOFF_Msk & ((value) << MPDDRC_DLL_ADO_ADOFF_Pos)))
/* -------- MPDDRC_DLL_SM[4] : (MPDDRC Offset: 0x118) MPDDRC DLL Status MASTER0 Register -------- */
#define MPDDRC_DLL_SM_MDINC (0x1u << 0) /**< \brief (MPDDRC_DLL_SM[4]) MASTERx Delay Increment */
#define MPDDRC_DLL_SM_MDDEC (0x1u << 1) /**< \brief (MPDDRC_DLL_SM[4]) MASTERx Delay Decrement */
#define MPDDRC_DLL_SM_MDOVF (0x1u << 2) /**< \brief (MPDDRC_DLL_SM[4]) MASTERx Delay Overflow Flag */
#define MPDDRC_DLL_SM_MDLVAL_Pos 8
#define MPDDRC_DLL_SM_MDLVAL_Msk (0xffu << MPDDRC_DLL_SM_MDLVAL_Pos) /**< \brief (MPDDRC_DLL_SM[4]) MASTERx Delay Lock Value */
#define MPDDRC_DLL_SM_MDCNT_Pos 20
#define MPDDRC_DLL_SM_MDCNT_Msk (0xffu << MPDDRC_DLL_SM_MDCNT_Pos) /**< \brief (MPDDRC_DLL_SM[4]) MASTERx Delay Counter Value */
/* -------- MPDDRC_DLL_SSL[8] : (MPDDRC Offset: 0x128) MPDDRC DLL Status SLAVE0 Register -------- */
#define MPDDRC_DLL_SSL_SDCOVF (0x1u << 0) /**< \brief (MPDDRC_DLL_SSL[8]) SLAVEx Delay Correction Overflow Flag */
#define MPDDRC_DLL_SSL_SDCUDF (0x1u << 1) /**< \brief (MPDDRC_DLL_SSL[8]) SLAVEx Delay Correction Underflow Flag */
#define MPDDRC_DLL_SSL_SDERF (0x1u << 2) /**< \brief (MPDDRC_DLL_SSL[8]) SLAVEx Delay Correction Error Flag */
#define MPDDRC_DLL_SSL_SDCNT_Pos 8
#define MPDDRC_DLL_SSL_SDCNT_Msk (0xffu << MPDDRC_DLL_SSL_SDCNT_Pos) /**< \brief (MPDDRC_DLL_SSL[8]) SLAVEx Delay Counter Value */
#define MPDDRC_DLL_SSL_SDCVAL_Pos 20
#define MPDDRC_DLL_SSL_SDCVAL_Msk (0xffu << MPDDRC_DLL_SSL_SDCVAL_Pos) /**< \brief (MPDDRC_DLL_SSL[8]) SLAVEx Delay Correction Value */
/* -------- MPDDRC_DLL_SWR[4] : (MPDDRC Offset: 0x148) MPDDRC DLL Status CLKWR0 Register -------- */
#define MPDDRC_DLL_SWR_WRDCNT_Pos 0
#define MPDDRC_DLL_SWR_WRDCNT_Msk (0xffu << MPDDRC_DLL_SWR_WRDCNT_Pos) /**< \brief (MPDDRC_DLL_SWR[4]) CLKWRx Delay Counter Value */
/* -------- MPDDRC_DLL_SAD : (MPDDRC Offset: 0x158) MPDDRC DLL Status CLKAD Register -------- */
#define MPDDRC_DLL_SAD_ADDCNT_Pos 0
#define MPDDRC_DLL_SAD_ADDCNT_Msk (0xffu << MPDDRC_DLL_SAD_ADDCNT_Pos) /**< \brief (MPDDRC_DLL_SAD) CLKAD Delay Counter Value */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Parallel Input/Output Controller */
/* ============================================================================= */
/** \addtogroup SAMA5D4_PIO Parallel Input/Output Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Pio hardware registers */
typedef struct {
  __O  uint32_t PIO_PER;       /**< \brief (Pio Offset: 0x0000) PIO Enable Register */
  __O  uint32_t PIO_PDR;       /**< \brief (Pio Offset: 0x0004) PIO Disable Register */
  __I  uint32_t PIO_PSR;       /**< \brief (Pio Offset: 0x0008) PIO Status Register */
  __IO uint32_t PIO_ISLR;      /**< \brief (Pio Offset: 0x000C) PIO Interrupt Security Level Register */
  __O  uint32_t PIO_OER;       /**< \brief (Pio Offset: 0x0010) Output Enable Register */
  __O  uint32_t PIO_ODR;       /**< \brief (Pio Offset: 0x0014) Output Disable Register */
  __I  uint32_t PIO_OSR;       /**< \brief (Pio Offset: 0x0018) Output Status Register */
  __I  uint32_t Reserved1[1];
  __O  uint32_t PIO_IFER;      /**< \brief (Pio Offset: 0x0020) Glitch Input Filter Enable Register */
  __O  uint32_t PIO_IFDR;      /**< \brief (Pio Offset: 0x0024) Glitch Input Filter Disable Register */
  __I  uint32_t PIO_IFSR;      /**< \brief (Pio Offset: 0x0028) Glitch Input Filter Status Register */
  __I  uint32_t Reserved2[1];
  __O  uint32_t PIO_SODR;      /**< \brief (Pio Offset: 0x0030) Set Output Data Register */
  __O  uint32_t PIO_CODR;      /**< \brief (Pio Offset: 0x0034) Clear Output Data Register */
  __IO uint32_t PIO_ODSR;      /**< \brief (Pio Offset: 0x0038) Output Data Status Register */
  __I  uint32_t PIO_PDSR;      /**< \brief (Pio Offset: 0x003C) Pin Data Status Register */
  __O  uint32_t PIO_IER;       /**< \brief (Pio Offset: 0x0040) Interrupt Enable Register */
  __O  uint32_t PIO_IDR;       /**< \brief (Pio Offset: 0x0044) Interrupt Disable Register */
  __I  uint32_t PIO_IMR;       /**< \brief (Pio Offset: 0x0048) Interrupt Mask Register */
  __I  uint32_t PIO_ISR;       /**< \brief (Pio Offset: 0x004C) Interrupt Status Register */
  __O  uint32_t PIO_MDER;      /**< \brief (Pio Offset: 0x0050) Multi-driver Enable Register */
  __O  uint32_t PIO_MDDR;      /**< \brief (Pio Offset: 0x0054) Multi-driver Disable Register */
  __I  uint32_t PIO_MDSR;      /**< \brief (Pio Offset: 0x0058) Multi-driver Status Register */
  __I  uint32_t Reserved3[1];
  __O  uint32_t PIO_PUDR;      /**< \brief (Pio Offset: 0x0060) Pull-up Disable Register */
  __O  uint32_t PIO_PUER;      /**< \brief (Pio Offset: 0x0064) Pull-up Enable Register */
  __I  uint32_t PIO_PUSR;      /**< \brief (Pio Offset: 0x0068) Pad Pull-up Status Register */
  __I  uint32_t Reserved4[1];
  __IO uint32_t PIO_ABCDSR[2]; /**< \brief (Pio Offset: 0x0070) Peripheral Select Register */
  __I  uint32_t Reserved5[2];
  __O  uint32_t PIO_IFSCDR;    /**< \brief (Pio Offset: 0x0080) Input Filter Slow Clock Disable Register */
  __O  uint32_t PIO_IFSCER;    /**< \brief (Pio Offset: 0x0084) Input Filter Slow Clock Enable Register */
  __I  uint32_t PIO_IFSCSR;    /**< \brief (Pio Offset: 0x0088) Input Filter Slow Clock Status Register */
  __IO uint32_t PIO_SCDR;      /**< \brief (Pio Offset: 0x008C) Slow Clock Divider Debouncing Register */
  __O  uint32_t PIO_PPDDR;     /**< \brief (Pio Offset: 0x0090) Pad Pull-down Disable Register */
  __O  uint32_t PIO_PPDER;     /**< \brief (Pio Offset: 0x0094) Pad Pull-down Enable Register */
  __I  uint32_t PIO_PPDSR;     /**< \brief (Pio Offset: 0x0098) Pad Pull-down Status Register */
  __I  uint32_t Reserved6[1];
  __O  uint32_t PIO_OWER;      /**< \brief (Pio Offset: 0x00A0) Output Write Enable */
  __O  uint32_t PIO_OWDR;      /**< \brief (Pio Offset: 0x00A4) Output Write Disable */
  __I  uint32_t PIO_OWSR;      /**< \brief (Pio Offset: 0x00A8) Output Write Status Register */
  __I  uint32_t Reserved7[1];
  __O  uint32_t PIO_AIMER;     /**< \brief (Pio Offset: 0x00B0) Additional Interrupt Modes Enable Register */
  __O  uint32_t PIO_AIMDR;     /**< \brief (Pio Offset: 0x00B4) Additional Interrupt Modes Disables Register */
  __I  uint32_t PIO_AIMMR;     /**< \brief (Pio Offset: 0x00B8) Additional Interrupt Modes Mask Register */
  __I  uint32_t Reserved8[1];
  __O  uint32_t PIO_ESR;       /**< \brief (Pio Offset: 0x00C0) Edge Select Register */
  __O  uint32_t PIO_LSR;       /**< \brief (Pio Offset: 0x00C4) Level Select Register */
  __I  uint32_t PIO_ELSR;      /**< \brief (Pio Offset: 0x00C8) Edge/Level Status Register */
  __I  uint32_t Reserved9[1];
  __O  uint32_t PIO_FELLSR;    /**< \brief (Pio Offset: 0x00D0) Falling Edge/Low Level Select Register */
  __O  uint32_t PIO_REHLSR;    /**< \brief (Pio Offset: 0x00D4) Rising Edge/ High Level Select Register */
  __I  uint32_t PIO_FRLHSR;    /**< \brief (Pio Offset: 0x00D8) Fall/Rise - Low/High Status Register */
  __I  uint32_t Reserved10[2];
  __IO uint32_t PIO_WPMR;      /**< \brief (Pio Offset: 0x00E4) Write Protect Mode Register */
  __I  uint32_t PIO_WPSR;      /**< \brief (Pio Offset: 0x00E8) Write Protect Status Register */
  __I  uint32_t Reserved11[5];
  __IO uint32_t PIO_SCHMITT;   /**< \brief (Pio Offset: 0x0100) Schmitt Trigger Register */
  __I  uint32_t Reserved12[5];
  __IO uint32_t PIO_DRIVER1;   /**< \brief (Pio Offset: 0x0118) I/O Drive Register 1 */
  __IO uint32_t PIO_DRIVER2;   /**< \brief (Pio Offset: 0x011C) I/O Drive Register 2 */
} Pio;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- PIO_PER : (PIO Offset: 0x0000) PIO Enable Register -------- */
#define PIO_PER_P0 (0x1u << 0) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P1 (0x1u << 1) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P2 (0x1u << 2) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P3 (0x1u << 3) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P4 (0x1u << 4) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P5 (0x1u << 5) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P6 (0x1u << 6) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P7 (0x1u << 7) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P8 (0x1u << 8) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P9 (0x1u << 9) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P10 (0x1u << 10) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P11 (0x1u << 11) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P12 (0x1u << 12) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P13 (0x1u << 13) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P14 (0x1u << 14) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P15 (0x1u << 15) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P16 (0x1u << 16) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P17 (0x1u << 17) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P18 (0x1u << 18) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P19 (0x1u << 19) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P20 (0x1u << 20) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P21 (0x1u << 21) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P22 (0x1u << 22) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P23 (0x1u << 23) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P24 (0x1u << 24) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P25 (0x1u << 25) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P26 (0x1u << 26) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P27 (0x1u << 27) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P28 (0x1u << 28) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P29 (0x1u << 29) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P30 (0x1u << 30) /**< \brief (PIO_PER) PIO Enable */
#define PIO_PER_P31 (0x1u << 31) /**< \brief (PIO_PER) PIO Enable */
/* -------- PIO_PDR : (PIO Offset: 0x0004) PIO Disable Register -------- */
#define PIO_PDR_P0 (0x1u << 0) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P1 (0x1u << 1) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P2 (0x1u << 2) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P3 (0x1u << 3) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P4 (0x1u << 4) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P5 (0x1u << 5) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P6 (0x1u << 6) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P7 (0x1u << 7) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P8 (0x1u << 8) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P9 (0x1u << 9) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P10 (0x1u << 10) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P11 (0x1u << 11) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P12 (0x1u << 12) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P13 (0x1u << 13) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P14 (0x1u << 14) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P15 (0x1u << 15) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P16 (0x1u << 16) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P17 (0x1u << 17) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P18 (0x1u << 18) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P19 (0x1u << 19) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P20 (0x1u << 20) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P21 (0x1u << 21) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P22 (0x1u << 22) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P23 (0x1u << 23) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P24 (0x1u << 24) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P25 (0x1u << 25) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P26 (0x1u << 26) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P27 (0x1u << 27) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P28 (0x1u << 28) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P29 (0x1u << 29) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P30 (0x1u << 30) /**< \brief (PIO_PDR) PIO Disable */
#define PIO_PDR_P31 (0x1u << 31) /**< \brief (PIO_PDR) PIO Disable */
/* -------- PIO_PSR : (PIO Offset: 0x0008) PIO Status Register -------- */
#define PIO_PSR_P0 (0x1u << 0) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P1 (0x1u << 1) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P2 (0x1u << 2) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P3 (0x1u << 3) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P4 (0x1u << 4) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P5 (0x1u << 5) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P6 (0x1u << 6) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P7 (0x1u << 7) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P8 (0x1u << 8) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P9 (0x1u << 9) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P10 (0x1u << 10) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P11 (0x1u << 11) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P12 (0x1u << 12) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P13 (0x1u << 13) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P14 (0x1u << 14) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P15 (0x1u << 15) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P16 (0x1u << 16) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P17 (0x1u << 17) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P18 (0x1u << 18) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P19 (0x1u << 19) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P20 (0x1u << 20) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P21 (0x1u << 21) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P22 (0x1u << 22) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P23 (0x1u << 23) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P24 (0x1u << 24) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P25 (0x1u << 25) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P26 (0x1u << 26) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P27 (0x1u << 27) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P28 (0x1u << 28) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P29 (0x1u << 29) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P30 (0x1u << 30) /**< \brief (PIO_PSR) PIO Status */
#define PIO_PSR_P31 (0x1u << 31) /**< \brief (PIO_PSR) PIO Status */
/* -------- PIO_ISLR : (PIO Offset: 0x000C) PIO Interrupt Security Level Register -------- */
#define PIO_ISLR_P0 (0x1u << 0) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P1 (0x1u << 1) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P2 (0x1u << 2) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P3 (0x1u << 3) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P4 (0x1u << 4) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P5 (0x1u << 5) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P6 (0x1u << 6) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P7 (0x1u << 7) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P8 (0x1u << 8) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P9 (0x1u << 9) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P10 (0x1u << 10) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P11 (0x1u << 11) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P12 (0x1u << 12) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P13 (0x1u << 13) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P14 (0x1u << 14) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P15 (0x1u << 15) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P16 (0x1u << 16) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P17 (0x1u << 17) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P18 (0x1u << 18) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P19 (0x1u << 19) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P20 (0x1u << 20) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P21 (0x1u << 21) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P22 (0x1u << 22) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P23 (0x1u << 23) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P24 (0x1u << 24) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P25 (0x1u << 25) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P26 (0x1u << 26) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P27 (0x1u << 27) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P28 (0x1u << 28) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P29 (0x1u << 29) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P30 (0x1u << 30) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
#define PIO_ISLR_P31 (0x1u << 31) /**< \brief (PIO_ISLR) PIO Interrupt Security Level */
/* -------- PIO_OER : (PIO Offset: 0x0010) Output Enable Register -------- */
#define PIO_OER_P0 (0x1u << 0) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P1 (0x1u << 1) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P2 (0x1u << 2) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P3 (0x1u << 3) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P4 (0x1u << 4) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P5 (0x1u << 5) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P6 (0x1u << 6) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P7 (0x1u << 7) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P8 (0x1u << 8) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P9 (0x1u << 9) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P10 (0x1u << 10) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P11 (0x1u << 11) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P12 (0x1u << 12) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P13 (0x1u << 13) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P14 (0x1u << 14) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P15 (0x1u << 15) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P16 (0x1u << 16) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P17 (0x1u << 17) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P18 (0x1u << 18) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P19 (0x1u << 19) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P20 (0x1u << 20) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P21 (0x1u << 21) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P22 (0x1u << 22) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P23 (0x1u << 23) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P24 (0x1u << 24) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P25 (0x1u << 25) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P26 (0x1u << 26) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P27 (0x1u << 27) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P28 (0x1u << 28) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P29 (0x1u << 29) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P30 (0x1u << 30) /**< \brief (PIO_OER) Output Enable */
#define PIO_OER_P31 (0x1u << 31) /**< \brief (PIO_OER) Output Enable */
/* -------- PIO_ODR : (PIO Offset: 0x0014) Output Disable Register -------- */
#define PIO_ODR_P0 (0x1u << 0) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P1 (0x1u << 1) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P2 (0x1u << 2) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P3 (0x1u << 3) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P4 (0x1u << 4) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P5 (0x1u << 5) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P6 (0x1u << 6) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P7 (0x1u << 7) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P8 (0x1u << 8) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P9 (0x1u << 9) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P10 (0x1u << 10) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P11 (0x1u << 11) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P12 (0x1u << 12) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P13 (0x1u << 13) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P14 (0x1u << 14) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P15 (0x1u << 15) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P16 (0x1u << 16) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P17 (0x1u << 17) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P18 (0x1u << 18) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P19 (0x1u << 19) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P20 (0x1u << 20) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P21 (0x1u << 21) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P22 (0x1u << 22) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P23 (0x1u << 23) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P24 (0x1u << 24) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P25 (0x1u << 25) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P26 (0x1u << 26) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P27 (0x1u << 27) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P28 (0x1u << 28) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P29 (0x1u << 29) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P30 (0x1u << 30) /**< \brief (PIO_ODR) Output Disable */
#define PIO_ODR_P31 (0x1u << 31) /**< \brief (PIO_ODR) Output Disable */
/* -------- PIO_OSR : (PIO Offset: 0x0018) Output Status Register -------- */
#define PIO_OSR_P0 (0x1u << 0) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P1 (0x1u << 1) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P2 (0x1u << 2) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P3 (0x1u << 3) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P4 (0x1u << 4) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P5 (0x1u << 5) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P6 (0x1u << 6) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P7 (0x1u << 7) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P8 (0x1u << 8) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P9 (0x1u << 9) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P10 (0x1u << 10) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P11 (0x1u << 11) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P12 (0x1u << 12) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P13 (0x1u << 13) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P14 (0x1u << 14) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P15 (0x1u << 15) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P16 (0x1u << 16) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P17 (0x1u << 17) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P18 (0x1u << 18) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P19 (0x1u << 19) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P20 (0x1u << 20) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P21 (0x1u << 21) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P22 (0x1u << 22) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P23 (0x1u << 23) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P24 (0x1u << 24) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P25 (0x1u << 25) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P26 (0x1u << 26) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P27 (0x1u << 27) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P28 (0x1u << 28) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P29 (0x1u << 29) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P30 (0x1u << 30) /**< \brief (PIO_OSR) Output Status */
#define PIO_OSR_P31 (0x1u << 31) /**< \brief (PIO_OSR) Output Status */
/* -------- PIO_IFER : (PIO Offset: 0x0020) Glitch Input Filter Enable Register -------- */
#define PIO_IFER_P0 (0x1u << 0) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P1 (0x1u << 1) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P2 (0x1u << 2) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P3 (0x1u << 3) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P4 (0x1u << 4) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P5 (0x1u << 5) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P6 (0x1u << 6) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P7 (0x1u << 7) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P8 (0x1u << 8) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P9 (0x1u << 9) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P10 (0x1u << 10) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P11 (0x1u << 11) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P12 (0x1u << 12) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P13 (0x1u << 13) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P14 (0x1u << 14) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P15 (0x1u << 15) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P16 (0x1u << 16) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P17 (0x1u << 17) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P18 (0x1u << 18) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P19 (0x1u << 19) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P20 (0x1u << 20) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P21 (0x1u << 21) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P22 (0x1u << 22) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P23 (0x1u << 23) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P24 (0x1u << 24) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P25 (0x1u << 25) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P26 (0x1u << 26) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P27 (0x1u << 27) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P28 (0x1u << 28) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P29 (0x1u << 29) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P30 (0x1u << 30) /**< \brief (PIO_IFER) Input Filter Enable */
#define PIO_IFER_P31 (0x1u << 31) /**< \brief (PIO_IFER) Input Filter Enable */
/* -------- PIO_IFDR : (PIO Offset: 0x0024) Glitch Input Filter Disable Register -------- */
#define PIO_IFDR_P0 (0x1u << 0) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P1 (0x1u << 1) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P2 (0x1u << 2) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P3 (0x1u << 3) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P4 (0x1u << 4) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P5 (0x1u << 5) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P6 (0x1u << 6) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P7 (0x1u << 7) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P8 (0x1u << 8) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P9 (0x1u << 9) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P10 (0x1u << 10) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P11 (0x1u << 11) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P12 (0x1u << 12) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P13 (0x1u << 13) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P14 (0x1u << 14) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P15 (0x1u << 15) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P16 (0x1u << 16) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P17 (0x1u << 17) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P18 (0x1u << 18) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P19 (0x1u << 19) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P20 (0x1u << 20) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P21 (0x1u << 21) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P22 (0x1u << 22) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P23 (0x1u << 23) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P24 (0x1u << 24) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P25 (0x1u << 25) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P26 (0x1u << 26) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P27 (0x1u << 27) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P28 (0x1u << 28) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P29 (0x1u << 29) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P30 (0x1u << 30) /**< \brief (PIO_IFDR) Input Filter Disable */
#define PIO_IFDR_P31 (0x1u << 31) /**< \brief (PIO_IFDR) Input Filter Disable */
/* -------- PIO_IFSR : (PIO Offset: 0x0028) Glitch Input Filter Status Register -------- */
#define PIO_IFSR_P0 (0x1u << 0) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P1 (0x1u << 1) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P2 (0x1u << 2) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P3 (0x1u << 3) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P4 (0x1u << 4) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P5 (0x1u << 5) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P6 (0x1u << 6) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P7 (0x1u << 7) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P8 (0x1u << 8) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P9 (0x1u << 9) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P10 (0x1u << 10) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P11 (0x1u << 11) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P12 (0x1u << 12) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P13 (0x1u << 13) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P14 (0x1u << 14) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P15 (0x1u << 15) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P16 (0x1u << 16) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P17 (0x1u << 17) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P18 (0x1u << 18) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P19 (0x1u << 19) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P20 (0x1u << 20) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P21 (0x1u << 21) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P22 (0x1u << 22) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P23 (0x1u << 23) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P24 (0x1u << 24) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P25 (0x1u << 25) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P26 (0x1u << 26) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P27 (0x1u << 27) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P28 (0x1u << 28) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P29 (0x1u << 29) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P30 (0x1u << 30) /**< \brief (PIO_IFSR) Input Filer Status */
#define PIO_IFSR_P31 (0x1u << 31) /**< \brief (PIO_IFSR) Input Filer Status */
/* -------- PIO_SODR : (PIO Offset: 0x0030) Set Output Data Register -------- */
#define PIO_SODR_P0 (0x1u << 0) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P1 (0x1u << 1) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P2 (0x1u << 2) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P3 (0x1u << 3) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P4 (0x1u << 4) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P5 (0x1u << 5) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P6 (0x1u << 6) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P7 (0x1u << 7) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P8 (0x1u << 8) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P9 (0x1u << 9) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P10 (0x1u << 10) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P11 (0x1u << 11) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P12 (0x1u << 12) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P13 (0x1u << 13) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P14 (0x1u << 14) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P15 (0x1u << 15) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P16 (0x1u << 16) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P17 (0x1u << 17) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P18 (0x1u << 18) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P19 (0x1u << 19) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P20 (0x1u << 20) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P21 (0x1u << 21) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P22 (0x1u << 22) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P23 (0x1u << 23) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P24 (0x1u << 24) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P25 (0x1u << 25) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P26 (0x1u << 26) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P27 (0x1u << 27) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P28 (0x1u << 28) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P29 (0x1u << 29) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P30 (0x1u << 30) /**< \brief (PIO_SODR) Set Output Data */
#define PIO_SODR_P31 (0x1u << 31) /**< \brief (PIO_SODR) Set Output Data */
/* -------- PIO_CODR : (PIO Offset: 0x0034) Clear Output Data Register -------- */
#define PIO_CODR_P0 (0x1u << 0) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P1 (0x1u << 1) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P2 (0x1u << 2) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P3 (0x1u << 3) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P4 (0x1u << 4) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P5 (0x1u << 5) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P6 (0x1u << 6) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P7 (0x1u << 7) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P8 (0x1u << 8) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P9 (0x1u << 9) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P10 (0x1u << 10) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P11 (0x1u << 11) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P12 (0x1u << 12) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P13 (0x1u << 13) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P14 (0x1u << 14) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P15 (0x1u << 15) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P16 (0x1u << 16) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P17 (0x1u << 17) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P18 (0x1u << 18) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P19 (0x1u << 19) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P20 (0x1u << 20) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P21 (0x1u << 21) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P22 (0x1u << 22) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P23 (0x1u << 23) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P24 (0x1u << 24) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P25 (0x1u << 25) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P26 (0x1u << 26) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P27 (0x1u << 27) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P28 (0x1u << 28) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P29 (0x1u << 29) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P30 (0x1u << 30) /**< \brief (PIO_CODR) Clear Output Data */
#define PIO_CODR_P31 (0x1u << 31) /**< \brief (PIO_CODR) Clear Output Data */
/* -------- PIO_ODSR : (PIO Offset: 0x0038) Output Data Status Register -------- */
#define PIO_ODSR_P0 (0x1u << 0) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P1 (0x1u << 1) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P2 (0x1u << 2) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P3 (0x1u << 3) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P4 (0x1u << 4) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P5 (0x1u << 5) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P6 (0x1u << 6) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P7 (0x1u << 7) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P8 (0x1u << 8) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P9 (0x1u << 9) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P10 (0x1u << 10) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P11 (0x1u << 11) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P12 (0x1u << 12) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P13 (0x1u << 13) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P14 (0x1u << 14) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P15 (0x1u << 15) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P16 (0x1u << 16) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P17 (0x1u << 17) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P18 (0x1u << 18) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P19 (0x1u << 19) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P20 (0x1u << 20) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P21 (0x1u << 21) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P22 (0x1u << 22) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P23 (0x1u << 23) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P24 (0x1u << 24) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P25 (0x1u << 25) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P26 (0x1u << 26) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P27 (0x1u << 27) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P28 (0x1u << 28) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P29 (0x1u << 29) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P30 (0x1u << 30) /**< \brief (PIO_ODSR) Output Data Status */
#define PIO_ODSR_P31 (0x1u << 31) /**< \brief (PIO_ODSR) Output Data Status */
/* -------- PIO_PDSR : (PIO Offset: 0x003C) Pin Data Status Register -------- */
#define PIO_PDSR_P0 (0x1u << 0) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P1 (0x1u << 1) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P2 (0x1u << 2) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P3 (0x1u << 3) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P4 (0x1u << 4) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P5 (0x1u << 5) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P6 (0x1u << 6) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P7 (0x1u << 7) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P8 (0x1u << 8) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P9 (0x1u << 9) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P10 (0x1u << 10) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P11 (0x1u << 11) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P12 (0x1u << 12) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P13 (0x1u << 13) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P14 (0x1u << 14) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P15 (0x1u << 15) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P16 (0x1u << 16) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P17 (0x1u << 17) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P18 (0x1u << 18) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P19 (0x1u << 19) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P20 (0x1u << 20) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P21 (0x1u << 21) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P22 (0x1u << 22) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P23 (0x1u << 23) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P24 (0x1u << 24) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P25 (0x1u << 25) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P26 (0x1u << 26) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P27 (0x1u << 27) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P28 (0x1u << 28) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P29 (0x1u << 29) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P30 (0x1u << 30) /**< \brief (PIO_PDSR) Output Data Status */
#define PIO_PDSR_P31 (0x1u << 31) /**< \brief (PIO_PDSR) Output Data Status */
/* -------- PIO_IER : (PIO Offset: 0x0040) Interrupt Enable Register -------- */
#define PIO_IER_P0 (0x1u << 0) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P1 (0x1u << 1) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P2 (0x1u << 2) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P3 (0x1u << 3) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P4 (0x1u << 4) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P5 (0x1u << 5) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P6 (0x1u << 6) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P7 (0x1u << 7) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P8 (0x1u << 8) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P9 (0x1u << 9) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P10 (0x1u << 10) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P11 (0x1u << 11) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P12 (0x1u << 12) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P13 (0x1u << 13) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P14 (0x1u << 14) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P15 (0x1u << 15) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P16 (0x1u << 16) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P17 (0x1u << 17) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P18 (0x1u << 18) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P19 (0x1u << 19) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P20 (0x1u << 20) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P21 (0x1u << 21) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P22 (0x1u << 22) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P23 (0x1u << 23) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P24 (0x1u << 24) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P25 (0x1u << 25) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P26 (0x1u << 26) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P27 (0x1u << 27) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P28 (0x1u << 28) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P29 (0x1u << 29) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P30 (0x1u << 30) /**< \brief (PIO_IER) Input Change Interrupt Enable */
#define PIO_IER_P31 (0x1u << 31) /**< \brief (PIO_IER) Input Change Interrupt Enable */
/* -------- PIO_IDR : (PIO Offset: 0x0044) Interrupt Disable Register -------- */
#define PIO_IDR_P0 (0x1u << 0) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P1 (0x1u << 1) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P2 (0x1u << 2) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P3 (0x1u << 3) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P4 (0x1u << 4) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P5 (0x1u << 5) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P6 (0x1u << 6) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P7 (0x1u << 7) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P8 (0x1u << 8) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P9 (0x1u << 9) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P10 (0x1u << 10) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P11 (0x1u << 11) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P12 (0x1u << 12) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P13 (0x1u << 13) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P14 (0x1u << 14) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P15 (0x1u << 15) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P16 (0x1u << 16) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P17 (0x1u << 17) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P18 (0x1u << 18) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P19 (0x1u << 19) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P20 (0x1u << 20) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P21 (0x1u << 21) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P22 (0x1u << 22) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P23 (0x1u << 23) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P24 (0x1u << 24) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P25 (0x1u << 25) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P26 (0x1u << 26) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P27 (0x1u << 27) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P28 (0x1u << 28) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P29 (0x1u << 29) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P30 (0x1u << 30) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
#define PIO_IDR_P31 (0x1u << 31) /**< \brief (PIO_IDR) Input Change Interrupt Disable */
/* -------- PIO_IMR : (PIO Offset: 0x0048) Interrupt Mask Register -------- */
#define PIO_IMR_P0 (0x1u << 0) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P1 (0x1u << 1) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P2 (0x1u << 2) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P3 (0x1u << 3) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P4 (0x1u << 4) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P5 (0x1u << 5) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P6 (0x1u << 6) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P7 (0x1u << 7) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P8 (0x1u << 8) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P9 (0x1u << 9) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P10 (0x1u << 10) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P11 (0x1u << 11) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P12 (0x1u << 12) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P13 (0x1u << 13) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P14 (0x1u << 14) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P15 (0x1u << 15) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P16 (0x1u << 16) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P17 (0x1u << 17) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P18 (0x1u << 18) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P19 (0x1u << 19) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P20 (0x1u << 20) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P21 (0x1u << 21) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P22 (0x1u << 22) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P23 (0x1u << 23) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P24 (0x1u << 24) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P25 (0x1u << 25) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P26 (0x1u << 26) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P27 (0x1u << 27) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P28 (0x1u << 28) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P29 (0x1u << 29) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P30 (0x1u << 30) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
#define PIO_IMR_P31 (0x1u << 31) /**< \brief (PIO_IMR) Input Change Interrupt Mask */
/* -------- PIO_ISR : (PIO Offset: 0x004C) Interrupt Status Register -------- */
#define PIO_ISR_P0 (0x1u << 0) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P1 (0x1u << 1) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P2 (0x1u << 2) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P3 (0x1u << 3) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P4 (0x1u << 4) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P5 (0x1u << 5) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P6 (0x1u << 6) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P7 (0x1u << 7) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P8 (0x1u << 8) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P9 (0x1u << 9) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P10 (0x1u << 10) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P11 (0x1u << 11) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P12 (0x1u << 12) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P13 (0x1u << 13) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P14 (0x1u << 14) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P15 (0x1u << 15) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P16 (0x1u << 16) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P17 (0x1u << 17) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P18 (0x1u << 18) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P19 (0x1u << 19) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P20 (0x1u << 20) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P21 (0x1u << 21) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P22 (0x1u << 22) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P23 (0x1u << 23) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P24 (0x1u << 24) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P25 (0x1u << 25) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P26 (0x1u << 26) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P27 (0x1u << 27) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P28 (0x1u << 28) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P29 (0x1u << 29) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P30 (0x1u << 30) /**< \brief (PIO_ISR) Input Change Interrupt Status */
#define PIO_ISR_P31 (0x1u << 31) /**< \brief (PIO_ISR) Input Change Interrupt Status */
/* -------- PIO_MDER : (PIO Offset: 0x0050) Multi-driver Enable Register -------- */
#define PIO_MDER_P0 (0x1u << 0) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P1 (0x1u << 1) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P2 (0x1u << 2) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P3 (0x1u << 3) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P4 (0x1u << 4) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P5 (0x1u << 5) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P6 (0x1u << 6) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P7 (0x1u << 7) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P8 (0x1u << 8) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P9 (0x1u << 9) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P10 (0x1u << 10) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P11 (0x1u << 11) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P12 (0x1u << 12) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P13 (0x1u << 13) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P14 (0x1u << 14) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P15 (0x1u << 15) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P16 (0x1u << 16) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P17 (0x1u << 17) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P18 (0x1u << 18) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P19 (0x1u << 19) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P20 (0x1u << 20) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P21 (0x1u << 21) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P22 (0x1u << 22) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P23 (0x1u << 23) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P24 (0x1u << 24) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P25 (0x1u << 25) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P26 (0x1u << 26) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P27 (0x1u << 27) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P28 (0x1u << 28) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P29 (0x1u << 29) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P30 (0x1u << 30) /**< \brief (PIO_MDER) Multi Drive Enable */
#define PIO_MDER_P31 (0x1u << 31) /**< \brief (PIO_MDER) Multi Drive Enable */
/* -------- PIO_MDDR : (PIO Offset: 0x0054) Multi-driver Disable Register -------- */
#define PIO_MDDR_P0 (0x1u << 0) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P1 (0x1u << 1) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P2 (0x1u << 2) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P3 (0x1u << 3) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P4 (0x1u << 4) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P5 (0x1u << 5) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P6 (0x1u << 6) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P7 (0x1u << 7) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P8 (0x1u << 8) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P9 (0x1u << 9) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P10 (0x1u << 10) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P11 (0x1u << 11) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P12 (0x1u << 12) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P13 (0x1u << 13) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P14 (0x1u << 14) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P15 (0x1u << 15) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P16 (0x1u << 16) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P17 (0x1u << 17) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P18 (0x1u << 18) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P19 (0x1u << 19) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P20 (0x1u << 20) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P21 (0x1u << 21) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P22 (0x1u << 22) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P23 (0x1u << 23) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P24 (0x1u << 24) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P25 (0x1u << 25) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P26 (0x1u << 26) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P27 (0x1u << 27) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P28 (0x1u << 28) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P29 (0x1u << 29) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P30 (0x1u << 30) /**< \brief (PIO_MDDR) Multi Drive Disable. */
#define PIO_MDDR_P31 (0x1u << 31) /**< \brief (PIO_MDDR) Multi Drive Disable. */
/* -------- PIO_MDSR : (PIO Offset: 0x0058) Multi-driver Status Register -------- */
#define PIO_MDSR_P0 (0x1u << 0) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P1 (0x1u << 1) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P2 (0x1u << 2) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P3 (0x1u << 3) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P4 (0x1u << 4) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P5 (0x1u << 5) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P6 (0x1u << 6) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P7 (0x1u << 7) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P8 (0x1u << 8) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P9 (0x1u << 9) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P10 (0x1u << 10) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P11 (0x1u << 11) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P12 (0x1u << 12) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P13 (0x1u << 13) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P14 (0x1u << 14) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P15 (0x1u << 15) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P16 (0x1u << 16) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P17 (0x1u << 17) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P18 (0x1u << 18) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P19 (0x1u << 19) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P20 (0x1u << 20) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P21 (0x1u << 21) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P22 (0x1u << 22) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P23 (0x1u << 23) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P24 (0x1u << 24) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P25 (0x1u << 25) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P26 (0x1u << 26) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P27 (0x1u << 27) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P28 (0x1u << 28) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P29 (0x1u << 29) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P30 (0x1u << 30) /**< \brief (PIO_MDSR) Multi Drive Status. */
#define PIO_MDSR_P31 (0x1u << 31) /**< \brief (PIO_MDSR) Multi Drive Status. */
/* -------- PIO_PUDR : (PIO Offset: 0x0060) Pull-up Disable Register -------- */
#define PIO_PUDR_P0 (0x1u << 0) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P1 (0x1u << 1) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P2 (0x1u << 2) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P3 (0x1u << 3) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P4 (0x1u << 4) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P5 (0x1u << 5) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P6 (0x1u << 6) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P7 (0x1u << 7) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P8 (0x1u << 8) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P9 (0x1u << 9) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P10 (0x1u << 10) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P11 (0x1u << 11) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P12 (0x1u << 12) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P13 (0x1u << 13) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P14 (0x1u << 14) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P15 (0x1u << 15) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P16 (0x1u << 16) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P17 (0x1u << 17) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P18 (0x1u << 18) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P19 (0x1u << 19) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P20 (0x1u << 20) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P21 (0x1u << 21) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P22 (0x1u << 22) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P23 (0x1u << 23) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P24 (0x1u << 24) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P25 (0x1u << 25) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P26 (0x1u << 26) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P27 (0x1u << 27) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P28 (0x1u << 28) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P29 (0x1u << 29) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P30 (0x1u << 30) /**< \brief (PIO_PUDR) Pull Up Disable. */
#define PIO_PUDR_P31 (0x1u << 31) /**< \brief (PIO_PUDR) Pull Up Disable. */
/* -------- PIO_PUER : (PIO Offset: 0x0064) Pull-up Enable Register -------- */
#define PIO_PUER_P0 (0x1u << 0) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P1 (0x1u << 1) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P2 (0x1u << 2) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P3 (0x1u << 3) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P4 (0x1u << 4) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P5 (0x1u << 5) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P6 (0x1u << 6) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P7 (0x1u << 7) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P8 (0x1u << 8) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P9 (0x1u << 9) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P10 (0x1u << 10) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P11 (0x1u << 11) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P12 (0x1u << 12) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P13 (0x1u << 13) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P14 (0x1u << 14) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P15 (0x1u << 15) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P16 (0x1u << 16) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P17 (0x1u << 17) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P18 (0x1u << 18) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P19 (0x1u << 19) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P20 (0x1u << 20) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P21 (0x1u << 21) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P22 (0x1u << 22) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P23 (0x1u << 23) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P24 (0x1u << 24) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P25 (0x1u << 25) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P26 (0x1u << 26) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P27 (0x1u << 27) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P28 (0x1u << 28) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P29 (0x1u << 29) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P30 (0x1u << 30) /**< \brief (PIO_PUER) Pull Up Enable. */
#define PIO_PUER_P31 (0x1u << 31) /**< \brief (PIO_PUER) Pull Up Enable. */
/* -------- PIO_PUSR : (PIO Offset: 0x0068) Pad Pull-up Status Register -------- */
#define PIO_PUSR_P0 (0x1u << 0) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P1 (0x1u << 1) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P2 (0x1u << 2) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P3 (0x1u << 3) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P4 (0x1u << 4) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P5 (0x1u << 5) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P6 (0x1u << 6) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P7 (0x1u << 7) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P8 (0x1u << 8) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P9 (0x1u << 9) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P10 (0x1u << 10) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P11 (0x1u << 11) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P12 (0x1u << 12) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P13 (0x1u << 13) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P14 (0x1u << 14) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P15 (0x1u << 15) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P16 (0x1u << 16) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P17 (0x1u << 17) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P18 (0x1u << 18) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P19 (0x1u << 19) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P20 (0x1u << 20) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P21 (0x1u << 21) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P22 (0x1u << 22) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P23 (0x1u << 23) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P24 (0x1u << 24) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P25 (0x1u << 25) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P26 (0x1u << 26) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P27 (0x1u << 27) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P28 (0x1u << 28) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P29 (0x1u << 29) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P30 (0x1u << 30) /**< \brief (PIO_PUSR) Pull Up Status. */
#define PIO_PUSR_P31 (0x1u << 31) /**< \brief (PIO_PUSR) Pull Up Status. */
/* -------- PIO_ABCDSR[2] : (PIO Offset: 0x0070) Peripheral Select Register -------- */
#define PIO_ABCDSR_P0 (0x1u << 0) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P1 (0x1u << 1) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P2 (0x1u << 2) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P3 (0x1u << 3) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P4 (0x1u << 4) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P5 (0x1u << 5) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P6 (0x1u << 6) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P7 (0x1u << 7) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P8 (0x1u << 8) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P9 (0x1u << 9) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P10 (0x1u << 10) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P11 (0x1u << 11) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P12 (0x1u << 12) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P13 (0x1u << 13) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P14 (0x1u << 14) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P15 (0x1u << 15) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P16 (0x1u << 16) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P17 (0x1u << 17) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P18 (0x1u << 18) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P19 (0x1u << 19) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P20 (0x1u << 20) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P21 (0x1u << 21) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P22 (0x1u << 22) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P23 (0x1u << 23) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P24 (0x1u << 24) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P25 (0x1u << 25) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P26 (0x1u << 26) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P27 (0x1u << 27) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P28 (0x1u << 28) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P29 (0x1u << 29) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P30 (0x1u << 30) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
#define PIO_ABCDSR_P31 (0x1u << 31) /**< \brief (PIO_ABCDSR[2]) Peripheral Select. */
/* -------- PIO_IFSCDR : (PIO Offset: 0x0080) Input Filter Slow Clock Disable Register -------- */
#define PIO_IFSCDR_P0 (0x1u << 0) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P1 (0x1u << 1) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P2 (0x1u << 2) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P3 (0x1u << 3) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P4 (0x1u << 4) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P5 (0x1u << 5) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P6 (0x1u << 6) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P7 (0x1u << 7) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P8 (0x1u << 8) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P9 (0x1u << 9) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P10 (0x1u << 10) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P11 (0x1u << 11) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P12 (0x1u << 12) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P13 (0x1u << 13) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P14 (0x1u << 14) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P15 (0x1u << 15) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P16 (0x1u << 16) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P17 (0x1u << 17) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P18 (0x1u << 18) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P19 (0x1u << 19) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P20 (0x1u << 20) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P21 (0x1u << 21) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P22 (0x1u << 22) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P23 (0x1u << 23) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P24 (0x1u << 24) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P25 (0x1u << 25) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P26 (0x1u << 26) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P27 (0x1u << 27) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P28 (0x1u << 28) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P29 (0x1u << 29) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P30 (0x1u << 30) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
#define PIO_IFSCDR_P31 (0x1u << 31) /**< \brief (PIO_IFSCDR) PIO Clock Glitch Filtering Select. */
/* -------- PIO_IFSCER : (PIO Offset: 0x0084) Input Filter Slow Clock Enable Register -------- */
#define PIO_IFSCER_P0 (0x1u << 0) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P1 (0x1u << 1) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P2 (0x1u << 2) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P3 (0x1u << 3) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P4 (0x1u << 4) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P5 (0x1u << 5) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P6 (0x1u << 6) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P7 (0x1u << 7) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P8 (0x1u << 8) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P9 (0x1u << 9) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P10 (0x1u << 10) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P11 (0x1u << 11) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P12 (0x1u << 12) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P13 (0x1u << 13) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P14 (0x1u << 14) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P15 (0x1u << 15) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P16 (0x1u << 16) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P17 (0x1u << 17) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P18 (0x1u << 18) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P19 (0x1u << 19) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P20 (0x1u << 20) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P21 (0x1u << 21) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P22 (0x1u << 22) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P23 (0x1u << 23) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P24 (0x1u << 24) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P25 (0x1u << 25) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P26 (0x1u << 26) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P27 (0x1u << 27) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P28 (0x1u << 28) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P29 (0x1u << 29) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P30 (0x1u << 30) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
#define PIO_IFSCER_P31 (0x1u << 31) /**< \brief (PIO_IFSCER) Debouncing Filtering Select. */
/* -------- PIO_IFSCSR : (PIO Offset: 0x0088) Input Filter Slow Clock Status Register -------- */
#define PIO_IFSCSR_P0 (0x1u << 0) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P1 (0x1u << 1) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P2 (0x1u << 2) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P3 (0x1u << 3) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P4 (0x1u << 4) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P5 (0x1u << 5) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P6 (0x1u << 6) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P7 (0x1u << 7) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P8 (0x1u << 8) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P9 (0x1u << 9) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P10 (0x1u << 10) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P11 (0x1u << 11) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P12 (0x1u << 12) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P13 (0x1u << 13) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P14 (0x1u << 14) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P15 (0x1u << 15) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P16 (0x1u << 16) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P17 (0x1u << 17) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P18 (0x1u << 18) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P19 (0x1u << 19) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P20 (0x1u << 20) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P21 (0x1u << 21) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P22 (0x1u << 22) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P23 (0x1u << 23) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P24 (0x1u << 24) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P25 (0x1u << 25) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P26 (0x1u << 26) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P27 (0x1u << 27) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P28 (0x1u << 28) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P29 (0x1u << 29) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P30 (0x1u << 30) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
#define PIO_IFSCSR_P31 (0x1u << 31) /**< \brief (PIO_IFSCSR) Glitch or Debouncing Filter Selection Status */
/* -------- PIO_SCDR : (PIO Offset: 0x008C) Slow Clock Divider Debouncing Register -------- */
#define PIO_SCDR_DIV_Pos 0
#define PIO_SCDR_DIV_Msk (0x3fffu << PIO_SCDR_DIV_Pos) /**< \brief (PIO_SCDR) Slow Clock Divider Selection for Debouncing */
#define PIO_SCDR_DIV(value) ((PIO_SCDR_DIV_Msk & ((value) << PIO_SCDR_DIV_Pos)))
/* -------- PIO_PPDDR : (PIO Offset: 0x0090) Pad Pull-down Disable Register -------- */
#define PIO_PPDDR_P0 (0x1u << 0) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P1 (0x1u << 1) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P2 (0x1u << 2) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P3 (0x1u << 3) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P4 (0x1u << 4) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P5 (0x1u << 5) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P6 (0x1u << 6) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P7 (0x1u << 7) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P8 (0x1u << 8) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P9 (0x1u << 9) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P10 (0x1u << 10) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P11 (0x1u << 11) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P12 (0x1u << 12) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P13 (0x1u << 13) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P14 (0x1u << 14) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P15 (0x1u << 15) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P16 (0x1u << 16) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P17 (0x1u << 17) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P18 (0x1u << 18) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P19 (0x1u << 19) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P20 (0x1u << 20) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P21 (0x1u << 21) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P22 (0x1u << 22) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P23 (0x1u << 23) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P24 (0x1u << 24) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P25 (0x1u << 25) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P26 (0x1u << 26) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P27 (0x1u << 27) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P28 (0x1u << 28) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P29 (0x1u << 29) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P30 (0x1u << 30) /**< \brief (PIO_PPDDR) Pull Down Disable */
#define PIO_PPDDR_P31 (0x1u << 31) /**< \brief (PIO_PPDDR) Pull Down Disable */
/* -------- PIO_PPDER : (PIO Offset: 0x0094) Pad Pull-down Enable Register -------- */
#define PIO_PPDER_P0 (0x1u << 0) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P1 (0x1u << 1) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P2 (0x1u << 2) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P3 (0x1u << 3) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P4 (0x1u << 4) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P5 (0x1u << 5) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P6 (0x1u << 6) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P7 (0x1u << 7) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P8 (0x1u << 8) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P9 (0x1u << 9) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P10 (0x1u << 10) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P11 (0x1u << 11) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P12 (0x1u << 12) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P13 (0x1u << 13) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P14 (0x1u << 14) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P15 (0x1u << 15) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P16 (0x1u << 16) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P17 (0x1u << 17) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P18 (0x1u << 18) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P19 (0x1u << 19) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P20 (0x1u << 20) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P21 (0x1u << 21) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P22 (0x1u << 22) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P23 (0x1u << 23) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P24 (0x1u << 24) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P25 (0x1u << 25) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P26 (0x1u << 26) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P27 (0x1u << 27) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P28 (0x1u << 28) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P29 (0x1u << 29) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P30 (0x1u << 30) /**< \brief (PIO_PPDER) Pull Down Enable */
#define PIO_PPDER_P31 (0x1u << 31) /**< \brief (PIO_PPDER) Pull Down Enable */
/* -------- PIO_PPDSR : (PIO Offset: 0x0098) Pad Pull-down Status Register -------- */
#define PIO_PPDSR_P0 (0x1u << 0) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P1 (0x1u << 1) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P2 (0x1u << 2) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P3 (0x1u << 3) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P4 (0x1u << 4) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P5 (0x1u << 5) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P6 (0x1u << 6) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P7 (0x1u << 7) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P8 (0x1u << 8) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P9 (0x1u << 9) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P10 (0x1u << 10) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P11 (0x1u << 11) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P12 (0x1u << 12) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P13 (0x1u << 13) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P14 (0x1u << 14) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P15 (0x1u << 15) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P16 (0x1u << 16) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P17 (0x1u << 17) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P18 (0x1u << 18) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P19 (0x1u << 19) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P20 (0x1u << 20) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P21 (0x1u << 21) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P22 (0x1u << 22) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P23 (0x1u << 23) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P24 (0x1u << 24) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P25 (0x1u << 25) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P26 (0x1u << 26) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P27 (0x1u << 27) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P28 (0x1u << 28) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P29 (0x1u << 29) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P30 (0x1u << 30) /**< \brief (PIO_PPDSR) Pull Down Status */
#define PIO_PPDSR_P31 (0x1u << 31) /**< \brief (PIO_PPDSR) Pull Down Status */
/* -------- PIO_OWER : (PIO Offset: 0x00A0) Output Write Enable -------- */
#define PIO_OWER_P0 (0x1u << 0) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P1 (0x1u << 1) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P2 (0x1u << 2) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P3 (0x1u << 3) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P4 (0x1u << 4) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P5 (0x1u << 5) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P6 (0x1u << 6) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P7 (0x1u << 7) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P8 (0x1u << 8) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P9 (0x1u << 9) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P10 (0x1u << 10) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P11 (0x1u << 11) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P12 (0x1u << 12) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P13 (0x1u << 13) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P14 (0x1u << 14) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P15 (0x1u << 15) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P16 (0x1u << 16) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P17 (0x1u << 17) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P18 (0x1u << 18) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P19 (0x1u << 19) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P20 (0x1u << 20) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P21 (0x1u << 21) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P22 (0x1u << 22) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P23 (0x1u << 23) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P24 (0x1u << 24) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P25 (0x1u << 25) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P26 (0x1u << 26) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P27 (0x1u << 27) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P28 (0x1u << 28) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P29 (0x1u << 29) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P30 (0x1u << 30) /**< \brief (PIO_OWER) Output Write Enable */
#define PIO_OWER_P31 (0x1u << 31) /**< \brief (PIO_OWER) Output Write Enable */
/* -------- PIO_OWDR : (PIO Offset: 0x00A4) Output Write Disable -------- */
#define PIO_OWDR_P0 (0x1u << 0) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P1 (0x1u << 1) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P2 (0x1u << 2) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P3 (0x1u << 3) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P4 (0x1u << 4) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P5 (0x1u << 5) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P6 (0x1u << 6) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P7 (0x1u << 7) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P8 (0x1u << 8) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P9 (0x1u << 9) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P10 (0x1u << 10) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P11 (0x1u << 11) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P12 (0x1u << 12) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P13 (0x1u << 13) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P14 (0x1u << 14) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P15 (0x1u << 15) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P16 (0x1u << 16) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P17 (0x1u << 17) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P18 (0x1u << 18) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P19 (0x1u << 19) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P20 (0x1u << 20) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P21 (0x1u << 21) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P22 (0x1u << 22) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P23 (0x1u << 23) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P24 (0x1u << 24) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P25 (0x1u << 25) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P26 (0x1u << 26) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P27 (0x1u << 27) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P28 (0x1u << 28) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P29 (0x1u << 29) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P30 (0x1u << 30) /**< \brief (PIO_OWDR) Output Write Disable */
#define PIO_OWDR_P31 (0x1u << 31) /**< \brief (PIO_OWDR) Output Write Disable */
/* -------- PIO_OWSR : (PIO Offset: 0x00A8) Output Write Status Register -------- */
#define PIO_OWSR_P0 (0x1u << 0) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P1 (0x1u << 1) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P2 (0x1u << 2) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P3 (0x1u << 3) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P4 (0x1u << 4) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P5 (0x1u << 5) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P6 (0x1u << 6) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P7 (0x1u << 7) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P8 (0x1u << 8) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P9 (0x1u << 9) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P10 (0x1u << 10) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P11 (0x1u << 11) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P12 (0x1u << 12) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P13 (0x1u << 13) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P14 (0x1u << 14) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P15 (0x1u << 15) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P16 (0x1u << 16) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P17 (0x1u << 17) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P18 (0x1u << 18) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P19 (0x1u << 19) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P20 (0x1u << 20) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P21 (0x1u << 21) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P22 (0x1u << 22) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P23 (0x1u << 23) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P24 (0x1u << 24) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P25 (0x1u << 25) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P26 (0x1u << 26) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P27 (0x1u << 27) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P28 (0x1u << 28) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P29 (0x1u << 29) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P30 (0x1u << 30) /**< \brief (PIO_OWSR) Output Write Status */
#define PIO_OWSR_P31 (0x1u << 31) /**< \brief (PIO_OWSR) Output Write Status */
/* -------- PIO_AIMER : (PIO Offset: 0x00B0) Additional Interrupt Modes Enable Register -------- */
#define PIO_AIMER_P0 (0x1u << 0) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P1 (0x1u << 1) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P2 (0x1u << 2) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P3 (0x1u << 3) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P4 (0x1u << 4) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P5 (0x1u << 5) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P6 (0x1u << 6) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P7 (0x1u << 7) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P8 (0x1u << 8) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P9 (0x1u << 9) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P10 (0x1u << 10) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P11 (0x1u << 11) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P12 (0x1u << 12) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P13 (0x1u << 13) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P14 (0x1u << 14) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P15 (0x1u << 15) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P16 (0x1u << 16) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P17 (0x1u << 17) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P18 (0x1u << 18) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P19 (0x1u << 19) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P20 (0x1u << 20) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P21 (0x1u << 21) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P22 (0x1u << 22) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P23 (0x1u << 23) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P24 (0x1u << 24) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P25 (0x1u << 25) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P26 (0x1u << 26) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P27 (0x1u << 27) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P28 (0x1u << 28) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P29 (0x1u << 29) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P30 (0x1u << 30) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
#define PIO_AIMER_P31 (0x1u << 31) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable */
/* -------- PIO_AIMDR : (PIO Offset: 0x00B4) Additional Interrupt Modes Disables Register -------- */
#define PIO_AIMDR_P0 (0x1u << 0) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P1 (0x1u << 1) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P2 (0x1u << 2) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P3 (0x1u << 3) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P4 (0x1u << 4) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P5 (0x1u << 5) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P6 (0x1u << 6) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P7 (0x1u << 7) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P8 (0x1u << 8) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P9 (0x1u << 9) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P10 (0x1u << 10) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P11 (0x1u << 11) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P12 (0x1u << 12) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P13 (0x1u << 13) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P14 (0x1u << 14) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P15 (0x1u << 15) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P16 (0x1u << 16) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P17 (0x1u << 17) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P18 (0x1u << 18) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P19 (0x1u << 19) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P20 (0x1u << 20) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P21 (0x1u << 21) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P22 (0x1u << 22) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P23 (0x1u << 23) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P24 (0x1u << 24) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P25 (0x1u << 25) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P26 (0x1u << 26) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P27 (0x1u << 27) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P28 (0x1u << 28) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P29 (0x1u << 29) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P30 (0x1u << 30) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
#define PIO_AIMDR_P31 (0x1u << 31) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable */
/* -------- PIO_AIMMR : (PIO Offset: 0x00B8) Additional Interrupt Modes Mask Register -------- */
#define PIO_AIMMR_P0 (0x1u << 0) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P1 (0x1u << 1) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P2 (0x1u << 2) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P3 (0x1u << 3) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P4 (0x1u << 4) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P5 (0x1u << 5) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P6 (0x1u << 6) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P7 (0x1u << 7) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P8 (0x1u << 8) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P9 (0x1u << 9) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P10 (0x1u << 10) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P11 (0x1u << 11) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P12 (0x1u << 12) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P13 (0x1u << 13) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P14 (0x1u << 14) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P15 (0x1u << 15) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P16 (0x1u << 16) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P17 (0x1u << 17) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P18 (0x1u << 18) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P19 (0x1u << 19) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P20 (0x1u << 20) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P21 (0x1u << 21) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P22 (0x1u << 22) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P23 (0x1u << 23) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P24 (0x1u << 24) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P25 (0x1u << 25) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P26 (0x1u << 26) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P27 (0x1u << 27) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P28 (0x1u << 28) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P29 (0x1u << 29) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P30 (0x1u << 30) /**< \brief (PIO_AIMMR) Peripheral CD Status */
#define PIO_AIMMR_P31 (0x1u << 31) /**< \brief (PIO_AIMMR) Peripheral CD Status */
/* -------- PIO_ESR : (PIO Offset: 0x00C0) Edge Select Register -------- */
#define PIO_ESR_P0 (0x1u << 0) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P1 (0x1u << 1) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P2 (0x1u << 2) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P3 (0x1u << 3) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P4 (0x1u << 4) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P5 (0x1u << 5) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P6 (0x1u << 6) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P7 (0x1u << 7) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P8 (0x1u << 8) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P9 (0x1u << 9) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P10 (0x1u << 10) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P11 (0x1u << 11) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P12 (0x1u << 12) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P13 (0x1u << 13) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P14 (0x1u << 14) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P15 (0x1u << 15) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P16 (0x1u << 16) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P17 (0x1u << 17) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P18 (0x1u << 18) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P19 (0x1u << 19) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P20 (0x1u << 20) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P21 (0x1u << 21) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P22 (0x1u << 22) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P23 (0x1u << 23) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P24 (0x1u << 24) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P25 (0x1u << 25) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P26 (0x1u << 26) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P27 (0x1u << 27) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P28 (0x1u << 28) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P29 (0x1u << 29) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P30 (0x1u << 30) /**< \brief (PIO_ESR) Edge Interrupt Selection */
#define PIO_ESR_P31 (0x1u << 31) /**< \brief (PIO_ESR) Edge Interrupt Selection */
/* -------- PIO_LSR : (PIO Offset: 0x00C4) Level Select Register -------- */
#define PIO_LSR_P0 (0x1u << 0) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P1 (0x1u << 1) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P2 (0x1u << 2) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P3 (0x1u << 3) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P4 (0x1u << 4) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P5 (0x1u << 5) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P6 (0x1u << 6) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P7 (0x1u << 7) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P8 (0x1u << 8) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P9 (0x1u << 9) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P10 (0x1u << 10) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P11 (0x1u << 11) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P12 (0x1u << 12) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P13 (0x1u << 13) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P14 (0x1u << 14) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P15 (0x1u << 15) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P16 (0x1u << 16) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P17 (0x1u << 17) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P18 (0x1u << 18) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P19 (0x1u << 19) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P20 (0x1u << 20) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P21 (0x1u << 21) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P22 (0x1u << 22) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P23 (0x1u << 23) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P24 (0x1u << 24) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P25 (0x1u << 25) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P26 (0x1u << 26) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P27 (0x1u << 27) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P28 (0x1u << 28) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P29 (0x1u << 29) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P30 (0x1u << 30) /**< \brief (PIO_LSR) Level Interrupt Selection */
#define PIO_LSR_P31 (0x1u << 31) /**< \brief (PIO_LSR) Level Interrupt Selection */
/* -------- PIO_ELSR : (PIO Offset: 0x00C8) Edge/Level Status Register -------- */
#define PIO_ELSR_P0 (0x1u << 0) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P1 (0x1u << 1) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P2 (0x1u << 2) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P3 (0x1u << 3) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P4 (0x1u << 4) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P5 (0x1u << 5) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P6 (0x1u << 6) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P7 (0x1u << 7) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P8 (0x1u << 8) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P9 (0x1u << 9) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P10 (0x1u << 10) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P11 (0x1u << 11) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P12 (0x1u << 12) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P13 (0x1u << 13) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P14 (0x1u << 14) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P15 (0x1u << 15) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P16 (0x1u << 16) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P17 (0x1u << 17) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P18 (0x1u << 18) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P19 (0x1u << 19) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P20 (0x1u << 20) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P21 (0x1u << 21) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P22 (0x1u << 22) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P23 (0x1u << 23) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P24 (0x1u << 24) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P25 (0x1u << 25) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P26 (0x1u << 26) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P27 (0x1u << 27) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P28 (0x1u << 28) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P29 (0x1u << 29) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P30 (0x1u << 30) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
#define PIO_ELSR_P31 (0x1u << 31) /**< \brief (PIO_ELSR) Edge/Level Interrupt Source Selection */
/* -------- PIO_FELLSR : (PIO Offset: 0x00D0) Falling Edge/Low Level Select Register -------- */
#define PIO_FELLSR_P0 (0x1u << 0) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P1 (0x1u << 1) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P2 (0x1u << 2) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P3 (0x1u << 3) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P4 (0x1u << 4) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P5 (0x1u << 5) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P6 (0x1u << 6) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P7 (0x1u << 7) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P8 (0x1u << 8) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P9 (0x1u << 9) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P10 (0x1u << 10) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P11 (0x1u << 11) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P12 (0x1u << 12) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P13 (0x1u << 13) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P14 (0x1u << 14) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P15 (0x1u << 15) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P16 (0x1u << 16) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P17 (0x1u << 17) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P18 (0x1u << 18) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P19 (0x1u << 19) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P20 (0x1u << 20) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P21 (0x1u << 21) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P22 (0x1u << 22) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P23 (0x1u << 23) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P24 (0x1u << 24) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P25 (0x1u << 25) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P26 (0x1u << 26) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P27 (0x1u << 27) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P28 (0x1u << 28) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P29 (0x1u << 29) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P30 (0x1u << 30) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
#define PIO_FELLSR_P31 (0x1u << 31) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection */
/* -------- PIO_REHLSR : (PIO Offset: 0x00D4) Rising Edge/ High Level Select Register -------- */
#define PIO_REHLSR_P0 (0x1u << 0) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P1 (0x1u << 1) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P2 (0x1u << 2) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P3 (0x1u << 3) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P4 (0x1u << 4) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P5 (0x1u << 5) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P6 (0x1u << 6) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P7 (0x1u << 7) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P8 (0x1u << 8) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P9 (0x1u << 9) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P10 (0x1u << 10) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P11 (0x1u << 11) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P12 (0x1u << 12) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P13 (0x1u << 13) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P14 (0x1u << 14) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P15 (0x1u << 15) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P16 (0x1u << 16) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P17 (0x1u << 17) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P18 (0x1u << 18) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P19 (0x1u << 19) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P20 (0x1u << 20) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P21 (0x1u << 21) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P22 (0x1u << 22) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P23 (0x1u << 23) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P24 (0x1u << 24) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P25 (0x1u << 25) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P26 (0x1u << 26) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P27 (0x1u << 27) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P28 (0x1u << 28) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P29 (0x1u << 29) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P30 (0x1u << 30) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
#define PIO_REHLSR_P31 (0x1u << 31) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection */
/* -------- PIO_FRLHSR : (PIO Offset: 0x00D8) Fall/Rise - Low/High Status Register -------- */
#define PIO_FRLHSR_P0 (0x1u << 0) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P1 (0x1u << 1) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P2 (0x1u << 2) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P3 (0x1u << 3) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P4 (0x1u << 4) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P5 (0x1u << 5) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P6 (0x1u << 6) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P7 (0x1u << 7) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P8 (0x1u << 8) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P9 (0x1u << 9) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P10 (0x1u << 10) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P11 (0x1u << 11) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P12 (0x1u << 12) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P13 (0x1u << 13) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P14 (0x1u << 14) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P15 (0x1u << 15) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P16 (0x1u << 16) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P17 (0x1u << 17) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P18 (0x1u << 18) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P19 (0x1u << 19) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P20 (0x1u << 20) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P21 (0x1u << 21) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P22 (0x1u << 22) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P23 (0x1u << 23) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P24 (0x1u << 24) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P25 (0x1u << 25) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P26 (0x1u << 26) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P27 (0x1u << 27) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P28 (0x1u << 28) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P29 (0x1u << 29) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P30 (0x1u << 30) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
#define PIO_FRLHSR_P31 (0x1u << 31) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection */
/* -------- PIO_WPMR : (PIO Offset: 0x00E4) Write Protect Mode Register -------- */
#define PIO_WPMR_WPEN (0x1u << 0) /**< \brief (PIO_WPMR) Write Protect Enable */
#define PIO_WPMR_WPKEY_Pos 8
#define PIO_WPMR_WPKEY_Msk (0xffffffu << PIO_WPMR_WPKEY_Pos) /**< \brief (PIO_WPMR) Write Protect KEY. */
#define   PIO_WPMR_WPKEY_PASSWD (0x50494Fu << 8) /**< \brief (PIO_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */
/* -------- PIO_WPSR : (PIO Offset: 0x00E8) Write Protect Status Register -------- */
#define PIO_WPSR_WPVS (0x1u << 0) /**< \brief (PIO_WPSR) Write Protect Violation Status */
#define PIO_WPSR_WPVSRC_Pos 8
#define PIO_WPSR_WPVSRC_Msk (0xffffu << PIO_WPSR_WPVSRC_Pos) /**< \brief (PIO_WPSR) Write Protect Violation Source */
/* -------- PIO_SCHMITT : (PIO Offset: 0x0100) Schmitt Trigger Register -------- */
#define PIO_SCHMITT_SCHMITT0 (0x1u << 0) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT1 (0x1u << 1) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT2 (0x1u << 2) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT3 (0x1u << 3) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT4 (0x1u << 4) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT5 (0x1u << 5) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT6 (0x1u << 6) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT7 (0x1u << 7) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT8 (0x1u << 8) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT9 (0x1u << 9) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT10 (0x1u << 10) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT11 (0x1u << 11) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT12 (0x1u << 12) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT13 (0x1u << 13) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT14 (0x1u << 14) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT15 (0x1u << 15) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT16 (0x1u << 16) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT17 (0x1u << 17) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT18 (0x1u << 18) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT19 (0x1u << 19) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT20 (0x1u << 20) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT21 (0x1u << 21) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT22 (0x1u << 22) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT23 (0x1u << 23) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT24 (0x1u << 24) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT25 (0x1u << 25) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT26 (0x1u << 26) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT27 (0x1u << 27) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT28 (0x1u << 28) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT29 (0x1u << 29) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT30 (0x1u << 30) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
#define PIO_SCHMITT_SCHMITT31 (0x1u << 31) /**< \brief (PIO_SCHMITT) Schmitt Trigger Control */
/* -------- PIO_DRIVER1 : (PIO Offset: 0x0118) I/O Drive Register 1 -------- */
#define PIO_DRIVER1_LINE0_Pos 0
#define PIO_DRIVER1_LINE0_Msk (0x3u << PIO_DRIVER1_LINE0_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 0 */
#define   PIO_DRIVER1_LINE0_LO_DRIVE (0x0u << 0) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE0_ME_DRIVE (0x2u << 0) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE0_HI_DRIVE (0x3u << 0) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE1_Pos 2
#define PIO_DRIVER1_LINE1_Msk (0x3u << PIO_DRIVER1_LINE1_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 1 */
#define   PIO_DRIVER1_LINE1_LO_DRIVE (0x0u << 2) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE1_ME_DRIVE (0x2u << 2) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE1_HI_DRIVE (0x3u << 2) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE2_Pos 4
#define PIO_DRIVER1_LINE2_Msk (0x3u << PIO_DRIVER1_LINE2_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 2 */
#define   PIO_DRIVER1_LINE2_LO_DRIVE (0x0u << 4) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE2_ME_DRIVE (0x2u << 4) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE2_HI_DRIVE (0x3u << 4) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE3_Pos 6
#define PIO_DRIVER1_LINE3_Msk (0x3u << PIO_DRIVER1_LINE3_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 3 */
#define   PIO_DRIVER1_LINE3_LO_DRIVE (0x0u << 6) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE3_ME_DRIVE (0x2u << 6) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE3_HI_DRIVE (0x3u << 6) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE4_Pos 8
#define PIO_DRIVER1_LINE4_Msk (0x3u << PIO_DRIVER1_LINE4_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 4 */
#define   PIO_DRIVER1_LINE4_LO_DRIVE (0x0u << 8) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE4_ME_DRIVE (0x2u << 8) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE4_HI_DRIVE (0x3u << 8) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE5_Pos 10
#define PIO_DRIVER1_LINE5_Msk (0x3u << PIO_DRIVER1_LINE5_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 5 */
#define   PIO_DRIVER1_LINE5_LO_DRIVE (0x0u << 10) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE5_ME_DRIVE (0x2u << 10) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE5_HI_DRIVE (0x3u << 10) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE6_Pos 12
#define PIO_DRIVER1_LINE6_Msk (0x3u << PIO_DRIVER1_LINE6_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 6 */
#define   PIO_DRIVER1_LINE6_LO_DRIVE (0x0u << 12) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE6_ME_DRIVE (0x2u << 12) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE6_HI_DRIVE (0x3u << 12) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE7_Pos 14
#define PIO_DRIVER1_LINE7_Msk (0x3u << PIO_DRIVER1_LINE7_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 7 */
#define   PIO_DRIVER1_LINE7_LO_DRIVE (0x0u << 14) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE7_ME_DRIVE (0x2u << 14) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE7_HI_DRIVE (0x3u << 14) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE8_Pos 16
#define PIO_DRIVER1_LINE8_Msk (0x3u << PIO_DRIVER1_LINE8_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 8 */
#define   PIO_DRIVER1_LINE8_LO_DRIVE (0x0u << 16) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE8_ME_DRIVE (0x2u << 16) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE8_HI_DRIVE (0x3u << 16) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE9_Pos 18
#define PIO_DRIVER1_LINE9_Msk (0x3u << PIO_DRIVER1_LINE9_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 9 */
#define   PIO_DRIVER1_LINE9_LO_DRIVE (0x0u << 18) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE9_ME_DRIVE (0x2u << 18) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE9_HI_DRIVE (0x3u << 18) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE10_Pos 20
#define PIO_DRIVER1_LINE10_Msk (0x3u << PIO_DRIVER1_LINE10_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 10 */
#define   PIO_DRIVER1_LINE10_LO_DRIVE (0x0u << 20) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE10_ME_DRIVE (0x2u << 20) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE10_HI_DRIVE (0x3u << 20) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE11_Pos 22
#define PIO_DRIVER1_LINE11_Msk (0x3u << PIO_DRIVER1_LINE11_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 11 */
#define   PIO_DRIVER1_LINE11_LO_DRIVE (0x0u << 22) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE11_ME_DRIVE (0x2u << 22) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE11_HI_DRIVE (0x3u << 22) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE12_Pos 24
#define PIO_DRIVER1_LINE12_Msk (0x3u << PIO_DRIVER1_LINE12_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 12 */
#define   PIO_DRIVER1_LINE12_LO_DRIVE (0x0u << 24) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE12_ME_DRIVE (0x2u << 24) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE12_HI_DRIVE (0x3u << 24) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE13_Pos 26
#define PIO_DRIVER1_LINE13_Msk (0x3u << PIO_DRIVER1_LINE13_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 13 */
#define   PIO_DRIVER1_LINE13_LO_DRIVE (0x0u << 26) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE13_ME_DRIVE (0x2u << 26) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE13_HI_DRIVE (0x3u << 26) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE14_Pos 28
#define PIO_DRIVER1_LINE14_Msk (0x3u << PIO_DRIVER1_LINE14_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 14 */
#define   PIO_DRIVER1_LINE14_LO_DRIVE (0x0u << 28) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE14_ME_DRIVE (0x2u << 28) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE14_HI_DRIVE (0x3u << 28) /**< \brief (PIO_DRIVER1) High drive */
#define PIO_DRIVER1_LINE15_Pos 30
#define PIO_DRIVER1_LINE15_Msk (0x3u << PIO_DRIVER1_LINE15_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO Line 15 */
#define   PIO_DRIVER1_LINE15_LO_DRIVE (0x0u << 30) /**< \brief (PIO_DRIVER1) Low drive */
#define   PIO_DRIVER1_LINE15_ME_DRIVE (0x2u << 30) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE15_HI_DRIVE (0x3u << 30) /**< \brief (PIO_DRIVER1) High drive */
/* -------- PIO_DRIVER2 : (PIO Offset: 0x011C) I/O Drive Register 2 -------- */
#define PIO_DRIVER2_LINE16_Pos 0
#define PIO_DRIVER2_LINE16_Msk (0x3u << PIO_DRIVER2_LINE16_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 16 */
#define   PIO_DRIVER2_LINE16_LO_DRIVE (0x0u << 0) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE16_ME_DRIVE (0x2u << 0) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE16_HI_DRIVE (0x3u << 0) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE17_Pos 2
#define PIO_DRIVER2_LINE17_Msk (0x3u << PIO_DRIVER2_LINE17_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 17 */
#define   PIO_DRIVER2_LINE17_LO_DRIVE (0x0u << 2) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE17_ME_DRIVE (0x2u << 2) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE17_HI_DRIVE (0x3u << 2) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE18_Pos 4
#define PIO_DRIVER2_LINE18_Msk (0x3u << PIO_DRIVER2_LINE18_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 18 */
#define   PIO_DRIVER2_LINE18_LO_DRIVE (0x0u << 4) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE18_ME_DRIVE (0x2u << 4) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE18_HI_DRIVE (0x3u << 4) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE19_Pos 6
#define PIO_DRIVER2_LINE19_Msk (0x3u << PIO_DRIVER2_LINE19_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 19 */
#define   PIO_DRIVER2_LINE19_LO_DRIVE (0x0u << 6) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE19_ME_DRIVE (0x2u << 6) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE19_HI_DRIVE (0x3u << 6) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE20_Pos 8
#define PIO_DRIVER2_LINE20_Msk (0x3u << PIO_DRIVER2_LINE20_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 20 */
#define   PIO_DRIVER2_LINE20_LO_DRIVE (0x0u << 8) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE20_ME_DRIVE (0x2u << 8) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE20_HI_DRIVE (0x3u << 8) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE21_Pos 10
#define PIO_DRIVER2_LINE21_Msk (0x3u << PIO_DRIVER2_LINE21_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 21 */
#define   PIO_DRIVER2_LINE21_LO_DRIVE (0x0u << 10) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE21_ME_DRIVE (0x2u << 10) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE21_HI_DRIVE (0x3u << 10) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE22_Pos 12
#define PIO_DRIVER2_LINE22_Msk (0x3u << PIO_DRIVER2_LINE22_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 22 */
#define   PIO_DRIVER2_LINE22_LO_DRIVE (0x0u << 12) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE22_ME_DRIVE (0x2u << 12) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE22_HI_DRIVE (0x3u << 12) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE23_Pos 14
#define PIO_DRIVER2_LINE23_Msk (0x3u << PIO_DRIVER2_LINE23_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 23 */
#define   PIO_DRIVER2_LINE23_LO_DRIVE (0x0u << 14) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE23_ME_DRIVE (0x2u << 14) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE23_HI_DRIVE (0x3u << 14) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE24_Pos 16
#define PIO_DRIVER2_LINE24_Msk (0x3u << PIO_DRIVER2_LINE24_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 24 */
#define   PIO_DRIVER2_LINE24_LO_DRIVE (0x0u << 16) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE24_ME_DRIVE (0x2u << 16) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE24_HI_DRIVE (0x3u << 16) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE25_Pos 18
#define PIO_DRIVER2_LINE25_Msk (0x3u << PIO_DRIVER2_LINE25_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 25 */
#define   PIO_DRIVER2_LINE25_LO_DRIVE (0x0u << 18) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE25_ME_DRIVE (0x2u << 18) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE25_HI_DRIVE (0x3u << 18) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE26_Pos 20
#define PIO_DRIVER2_LINE26_Msk (0x3u << PIO_DRIVER2_LINE26_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 26 */
#define   PIO_DRIVER2_LINE26_LO_DRIVE (0x0u << 20) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE26_ME_DRIVE (0x2u << 20) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE26_HI_DRIVE (0x3u << 20) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE27_Pos 22
#define PIO_DRIVER2_LINE27_Msk (0x3u << PIO_DRIVER2_LINE27_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 27 */
#define   PIO_DRIVER2_LINE27_LO_DRIVE (0x0u << 22) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE27_ME_DRIVE (0x2u << 22) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE27_HI_DRIVE (0x3u << 22) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE28_Pos 24
#define PIO_DRIVER2_LINE28_Msk (0x3u << PIO_DRIVER2_LINE28_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 28 */
#define   PIO_DRIVER2_LINE28_LO_DRIVE (0x0u << 24) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE28_ME_DRIVE (0x2u << 24) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE28_HI_DRIVE (0x3u << 24) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE29_Pos 26
#define PIO_DRIVER2_LINE29_Msk (0x3u << PIO_DRIVER2_LINE29_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 29 */
#define   PIO_DRIVER2_LINE29_LO_DRIVE (0x0u << 26) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE29_ME_DRIVE (0x2u << 26) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE29_HI_DRIVE (0x3u << 26) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE30_Pos 28
#define PIO_DRIVER2_LINE30_Msk (0x3u << PIO_DRIVER2_LINE30_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 30 */
#define   PIO_DRIVER2_LINE30_LO_DRIVE (0x0u << 28) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE30_ME_DRIVE (0x2u << 28) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE30_HI_DRIVE (0x3u << 28) /**< \brief (PIO_DRIVER2) High drive */
#define PIO_DRIVER2_LINE31_Pos 30
#define PIO_DRIVER2_LINE31_Msk (0x3u << PIO_DRIVER2_LINE31_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 31 */
#define   PIO_DRIVER2_LINE31_LO_DRIVE (0x0u << 30) /**< \brief (PIO_DRIVER2) Low drive */
#define   PIO_DRIVER2_LINE31_ME_DRIVE (0x2u << 30) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE31_HI_DRIVE (0x3u << 30) /**< \brief (PIO_DRIVER2) High drive */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Periodic Interval Timer */
/* ============================================================================= */
/** \addtogroup SAMA5D4_PIT Periodic Interval Timer */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Pit hardware registers */
typedef struct {
  __IO uint32_t PIT_MR;   /**< \brief (Pit Offset: 0x00) Mode Register */
  __I  uint32_t PIT_SR;   /**< \brief (Pit Offset: 0x04) Status Register */
  __I  uint32_t PIT_PIVR; /**< \brief (Pit Offset: 0x08) Periodic Interval Value Register */
  __I  uint32_t PIT_PIIR; /**< \brief (Pit Offset: 0x0C) Periodic Interval Image Register */
} Pit;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- PIT_MR : (PIT Offset: 0x00) Mode Register -------- */
#define PIT_MR_PIV_Pos 0
#define PIT_MR_PIV_Msk (0xfffffu << PIT_MR_PIV_Pos) /**< \brief (PIT_MR) Periodic Interval Value */
#define PIT_MR_PIV(value) ((PIT_MR_PIV_Msk & ((value) << PIT_MR_PIV_Pos)))
#define PIT_MR_PITEN (0x1u << 24) /**< \brief (PIT_MR) Period Interval Timer Enabled */
#define PIT_MR_PITIEN (0x1u << 25) /**< \brief (PIT_MR) Periodic Interval Timer Interrupt Enable */
/* -------- PIT_SR : (PIT Offset: 0x04) Status Register -------- */
#define PIT_SR_PITS (0x1u << 0) /**< \brief (PIT_SR) Periodic Interval Timer Status */
/* -------- PIT_PIVR : (PIT Offset: 0x08) Periodic Interval Value Register -------- */
#define PIT_PIVR_CPIV_Pos 0
#define PIT_PIVR_CPIV_Msk (0xfffffu << PIT_PIVR_CPIV_Pos) /**< \brief (PIT_PIVR) Current Periodic Interval Value */
#define PIT_PIVR_PICNT_Pos 20
#define PIT_PIVR_PICNT_Msk (0xfffu << PIT_PIVR_PICNT_Pos) /**< \brief (PIT_PIVR) Periodic Interval Counter */
/* -------- PIT_PIIR : (PIT Offset: 0x0C) Periodic Interval Image Register -------- */
#define PIT_PIIR_CPIV_Pos 0
#define PIT_PIIR_CPIV_Msk (0xfffffu << PIT_PIIR_CPIV_Pos) /**< \brief (PIT_PIIR) Current Periodic Interval Value */
#define PIT_PIIR_PICNT_Pos 20
#define PIT_PIIR_PICNT_Msk (0xfffu << PIT_PIIR_PICNT_Pos) /**< \brief (PIT_PIIR) Periodic Interval Counter */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Power Management Controller */
/* ============================================================================= */
/** \addtogroup SAMA5D4_PMC Power Management Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Pmc hardware registers */
typedef struct {
  __O  uint32_t PMC_SCER;      /**< \brief (Pmc Offset: 0x0000) System Clock Enable Register */
  __O  uint32_t PMC_SCDR;      /**< \brief (Pmc Offset: 0x0004) System Clock Disable Register */
  __I  uint32_t PMC_SCSR;      /**< \brief (Pmc Offset: 0x0008) System Clock Status Register */
  __I  uint32_t Reserved1[1];
  __O  uint32_t PMC_PCER0;     /**< \brief (Pmc Offset: 0x0010) Peripheral Clock Enable Register 0 */
  __O  uint32_t PMC_PCDR0;     /**< \brief (Pmc Offset: 0x0014) Peripheral Clock Disable Register 0 */
  __I  uint32_t PMC_PCSR0;     /**< \brief (Pmc Offset: 0x0018) Peripheral Clock Status Register 0 */
  __IO uint32_t CKGR_UCKR;     /**< \brief (Pmc Offset: 0x001C) UTMI Clock Register */
  __IO uint32_t CKGR_MOR;      /**< \brief (Pmc Offset: 0x0020) Main Oscillator Register */
  __I  uint32_t CKGR_MCFR;     /**< \brief (Pmc Offset: 0x0024) Main Clock Frequency Register */
  __IO uint32_t CKGR_PLLAR;    /**< \brief (Pmc Offset: 0x0028) PLLA Register */
  __I  uint32_t Reserved2[1];
  __IO uint32_t PMC_MCKR;      /**< \brief (Pmc Offset: 0x0030) Master Clock Register */
  __I  uint32_t Reserved3[1];
  __IO uint32_t PMC_USB;       /**< \brief (Pmc Offset: 0x0038) USB Clock Register */
  __IO uint32_t PMC_SMD;       /**< \brief (Pmc Offset: 0x003C) Soft Modem Clock Register */
  __IO uint32_t PMC_PCK[3];    /**< \brief (Pmc Offset: 0x0040) Programmable Clock 0 Register */
  __I  uint32_t Reserved4[5];
  __O  uint32_t PMC_IER;       /**< \brief (Pmc Offset: 0x0060) Interrupt Enable Register */
  __O  uint32_t PMC_IDR;       /**< \brief (Pmc Offset: 0x0064) Interrupt Disable Register */
  __I  uint32_t PMC_SR;        /**< \brief (Pmc Offset: 0x0068) Status Register */
  __I  uint32_t PMC_IMR;       /**< \brief (Pmc Offset: 0x006C) Interrupt Mask Register */
  __I  uint32_t Reserved5[2];
  __O  uint32_t PMC_FOCR;      /**< \brief (Pmc Offset: 0x0078) Fault Output Clear Register */
  __I  uint32_t Reserved6[1];
  __O  uint32_t PMC_PLLICPR;   /**< \brief (Pmc Offset: 0x0080) PLL Charge Pump Current Register */
  __I  uint32_t Reserved7[24];
  __IO uint32_t PMC_WPMR;      /**< \brief (Pmc Offset: 0x00E4) Write Protect Mode Register */
  __I  uint32_t PMC_WPSR;      /**< \brief (Pmc Offset: 0x00E8) Write Protect Status Register */
  __I  uint32_t Reserved8[5];
  __O  uint32_t PMC_PCER1;     /**< \brief (Pmc Offset: 0x0100) Peripheral Clock Enable Register 1 */
  __O  uint32_t PMC_PCDR1;     /**< \brief (Pmc Offset: 0x0104) Peripheral Clock Disable Register 1 */
  __I  uint32_t PMC_PCSR1;     /**< \brief (Pmc Offset: 0x0108) Peripheral Clock Status Register 1 */
  __IO uint32_t PMC_PCR;       /**< \brief (Pmc Offset: 0x010C) Peripheral Control Register */
} Pmc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- PMC_SCER : (PMC Offset: 0x0000) System Clock Enable Register -------- */
#define PMC_SCER_DDRCK (0x1u << 2) /**< \brief (PMC_SCER) DDR Clock Enable */
#define PMC_SCER_LCDCK (0x1u << 3) /**< \brief (PMC_SCER) LCD2x Clock Enable */
#define PMC_SCER_SMDCK (0x1u << 4) /**< \brief (PMC_SCER) SMD Clock Enable */
#define PMC_SCER_UHP (0x1u << 6) /**< \brief (PMC_SCER) USB Host OHCI Clocks Enable */
#define PMC_SCER_UDP (0x1u << 7) /**< \brief (PMC_SCER) USB Device Clock Enable */
#define PMC_SCER_PCK0 (0x1u << 8) /**< \brief (PMC_SCER) Programmable Clock 0 Output Enable */
#define PMC_SCER_PCK1 (0x1u << 9) /**< \brief (PMC_SCER) Programmable Clock 1 Output Enable */
#define PMC_SCER_PCK2 (0x1u << 10) /**< \brief (PMC_SCER) Programmable Clock 2 Output Enable */
/* -------- PMC_SCDR : (PMC Offset: 0x0004) System Clock Disable Register -------- */
#define PMC_SCDR_PCK (0x1u << 0) /**< \brief (PMC_SCDR) Processor Clock Disable */
#define PMC_SCDR_DDRCK (0x1u << 2) /**< \brief (PMC_SCDR) DDR Clock Disable */
#define PMC_SCDR_LCDCK (0x1u << 3) /**< \brief (PMC_SCDR) LCD2x Clock Disable */
#define PMC_SCDR_SMDCK (0x1u << 4) /**< \brief (PMC_SCDR) SMD Clock Disable */
#define PMC_SCDR_UHP (0x1u << 6) /**< \brief (PMC_SCDR) USB Host OHCI Clock Disable */
#define PMC_SCDR_UDP (0x1u << 7) /**< \brief (PMC_SCDR) USB Device Clock Enable */
#define PMC_SCDR_PCK0 (0x1u << 8) /**< \brief (PMC_SCDR) Programmable Clock 0 Output Disable */
#define PMC_SCDR_PCK1 (0x1u << 9) /**< \brief (PMC_SCDR) Programmable Clock 1 Output Disable */
#define PMC_SCDR_PCK2 (0x1u << 10) /**< \brief (PMC_SCDR) Programmable Clock 2 Output Disable */
/* -------- PMC_SCSR : (PMC Offset: 0x0008) System Clock Status Register -------- */
#define PMC_SCSR_PCK (0x1u << 0) /**< \brief (PMC_SCSR) Processor Clock Status */
#define PMC_SCSR_DDRCK (0x1u << 2) /**< \brief (PMC_SCSR) DDR Clock Status */
#define PMC_SCSR_LCDCK (0x1u << 3) /**< \brief (PMC_SCSR) LCD2x Clock Status */
#define PMC_SCSR_SMDCK (0x1u << 4) /**< \brief (PMC_SCSR) SMD Clock Status */
#define PMC_SCSR_UHP (0x1u << 6) /**< \brief (PMC_SCSR) USB Host Port Clock Status */
#define PMC_SCSR_UDP (0x1u << 7) /**< \brief (PMC_SCSR) USB Device Port Clock Status */
#define PMC_SCSR_PCK0 (0x1u << 8) /**< \brief (PMC_SCSR) Programmable Clock 0 Output Status */
#define PMC_SCSR_PCK1 (0x1u << 9) /**< \brief (PMC_SCSR) Programmable Clock 1 Output Status */
#define PMC_SCSR_PCK2 (0x1u << 10) /**< \brief (PMC_SCSR) Programmable Clock 2 Output Status */
/* -------- PMC_PCER0 : (PMC Offset: 0x0010) Peripheral Clock Enable Register 0 -------- */
#define PMC_PCER0_PID2 (0x1u << 2) /**< \brief (PMC_PCER0) Peripheral Clock 2 Enable */
#define PMC_PCER0_PID3 (0x1u << 3) /**< \brief (PMC_PCER0) Peripheral Clock 3 Enable */
#define PMC_PCER0_PID4 (0x1u << 4) /**< \brief (PMC_PCER0) Peripheral Clock 4 Enable */
#define PMC_PCER0_PID5 (0x1u << 5) /**< \brief (PMC_PCER0) Peripheral Clock 5 Enable */
#define PMC_PCER0_PID6 (0x1u << 6) /**< \brief (PMC_PCER0) Peripheral Clock 6 Enable */
#define PMC_PCER0_PID7 (0x1u << 7) /**< \brief (PMC_PCER0) Peripheral Clock 7 Enable */
#define PMC_PCER0_PID8 (0x1u << 8) /**< \brief (PMC_PCER0) Peripheral Clock 8 Enable */
#define PMC_PCER0_PID9 (0x1u << 9) /**< \brief (PMC_PCER0) Peripheral Clock 9 Enable */
#define PMC_PCER0_PID10 (0x1u << 10) /**< \brief (PMC_PCER0) Peripheral Clock 10 Enable */
#define PMC_PCER0_PID11 (0x1u << 11) /**< \brief (PMC_PCER0) Peripheral Clock 11 Enable */
#define PMC_PCER0_PID12 (0x1u << 12) /**< \brief (PMC_PCER0) Peripheral Clock 12 Enable */
#define PMC_PCER0_PID13 (0x1u << 13) /**< \brief (PMC_PCER0) Peripheral Clock 13 Enable */
#define PMC_PCER0_PID14 (0x1u << 14) /**< \brief (PMC_PCER0) Peripheral Clock 14 Enable */
#define PMC_PCER0_PID15 (0x1u << 15) /**< \brief (PMC_PCER0) Peripheral Clock 15 Enable */
#define PMC_PCER0_PID16 (0x1u << 16) /**< \brief (PMC_PCER0) Peripheral Clock 16 Enable */
#define PMC_PCER0_PID17 (0x1u << 17) /**< \brief (PMC_PCER0) Peripheral Clock 17 Enable */
#define PMC_PCER0_PID18 (0x1u << 18) /**< \brief (PMC_PCER0) Peripheral Clock 18 Enable */
#define PMC_PCER0_PID19 (0x1u << 19) /**< \brief (PMC_PCER0) Peripheral Clock 19 Enable */
#define PMC_PCER0_PID20 (0x1u << 20) /**< \brief (PMC_PCER0) Peripheral Clock 20 Enable */
#define PMC_PCER0_PID21 (0x1u << 21) /**< \brief (PMC_PCER0) Peripheral Clock 21 Enable */
#define PMC_PCER0_PID22 (0x1u << 22) /**< \brief (PMC_PCER0) Peripheral Clock 22 Enable */
#define PMC_PCER0_PID23 (0x1u << 23) /**< \brief (PMC_PCER0) Peripheral Clock 23 Enable */
#define PMC_PCER0_PID24 (0x1u << 24) /**< \brief (PMC_PCER0) Peripheral Clock 24 Enable */
#define PMC_PCER0_PID25 (0x1u << 25) /**< \brief (PMC_PCER0) Peripheral Clock 25 Enable */
#define PMC_PCER0_PID26 (0x1u << 26) /**< \brief (PMC_PCER0) Peripheral Clock 26 Enable */
#define PMC_PCER0_PID27 (0x1u << 27) /**< \brief (PMC_PCER0) Peripheral Clock 27 Enable */
#define PMC_PCER0_PID28 (0x1u << 28) /**< \brief (PMC_PCER0) Peripheral Clock 28 Enable */
#define PMC_PCER0_PID29 (0x1u << 29) /**< \brief (PMC_PCER0) Peripheral Clock 29 Enable */
#define PMC_PCER0_PID30 (0x1u << 30) /**< \brief (PMC_PCER0) Peripheral Clock 30 Enable */
#define PMC_PCER0_PID31 (0x1u << 31) /**< \brief (PMC_PCER0) Peripheral Clock 31 Enable */
/* -------- PMC_PCDR0 : (PMC Offset: 0x0014) Peripheral Clock Disable Register 0 -------- */
#define PMC_PCDR0_PID2 (0x1u << 2) /**< \brief (PMC_PCDR0) Peripheral Clock 2 Disable */
#define PMC_PCDR0_PID3 (0x1u << 3) /**< \brief (PMC_PCDR0) Peripheral Clock 3 Disable */
#define PMC_PCDR0_PID4 (0x1u << 4) /**< \brief (PMC_PCDR0) Peripheral Clock 4 Disable */
#define PMC_PCDR0_PID5 (0x1u << 5) /**< \brief (PMC_PCDR0) Peripheral Clock 5 Disable */
#define PMC_PCDR0_PID6 (0x1u << 6) /**< \brief (PMC_PCDR0) Peripheral Clock 6 Disable */
#define PMC_PCDR0_PID7 (0x1u << 7) /**< \brief (PMC_PCDR0) Peripheral Clock 7 Disable */
#define PMC_PCDR0_PID8 (0x1u << 8) /**< \brief (PMC_PCDR0) Peripheral Clock 8 Disable */
#define PMC_PCDR0_PID9 (0x1u << 9) /**< \brief (PMC_PCDR0) Peripheral Clock 9 Disable */
#define PMC_PCDR0_PID10 (0x1u << 10) /**< \brief (PMC_PCDR0) Peripheral Clock 10 Disable */
#define PMC_PCDR0_PID11 (0x1u << 11) /**< \brief (PMC_PCDR0) Peripheral Clock 11 Disable */
#define PMC_PCDR0_PID12 (0x1u << 12) /**< \brief (PMC_PCDR0) Peripheral Clock 12 Disable */
#define PMC_PCDR0_PID13 (0x1u << 13) /**< \brief (PMC_PCDR0) Peripheral Clock 13 Disable */
#define PMC_PCDR0_PID14 (0x1u << 14) /**< \brief (PMC_PCDR0) Peripheral Clock 14 Disable */
#define PMC_PCDR0_PID15 (0x1u << 15) /**< \brief (PMC_PCDR0) Peripheral Clock 15 Disable */
#define PMC_PCDR0_PID16 (0x1u << 16) /**< \brief (PMC_PCDR0) Peripheral Clock 16 Disable */
#define PMC_PCDR0_PID17 (0x1u << 17) /**< \brief (PMC_PCDR0) Peripheral Clock 17 Disable */
#define PMC_PCDR0_PID18 (0x1u << 18) /**< \brief (PMC_PCDR0) Peripheral Clock 18 Disable */
#define PMC_PCDR0_PID19 (0x1u << 19) /**< \brief (PMC_PCDR0) Peripheral Clock 19 Disable */
#define PMC_PCDR0_PID20 (0x1u << 20) /**< \brief (PMC_PCDR0) Peripheral Clock 20 Disable */
#define PMC_PCDR0_PID21 (0x1u << 21) /**< \brief (PMC_PCDR0) Peripheral Clock 21 Disable */
#define PMC_PCDR0_PID22 (0x1u << 22) /**< \brief (PMC_PCDR0) Peripheral Clock 22 Disable */
#define PMC_PCDR0_PID23 (0x1u << 23) /**< \brief (PMC_PCDR0) Peripheral Clock 23 Disable */
#define PMC_PCDR0_PID24 (0x1u << 24) /**< \brief (PMC_PCDR0) Peripheral Clock 24 Disable */
#define PMC_PCDR0_PID25 (0x1u << 25) /**< \brief (PMC_PCDR0) Peripheral Clock 25 Disable */
#define PMC_PCDR0_PID26 (0x1u << 26) /**< \brief (PMC_PCDR0) Peripheral Clock 26 Disable */
#define PMC_PCDR0_PID27 (0x1u << 27) /**< \brief (PMC_PCDR0) Peripheral Clock 27 Disable */
#define PMC_PCDR0_PID28 (0x1u << 28) /**< \brief (PMC_PCDR0) Peripheral Clock 28 Disable */
#define PMC_PCDR0_PID29 (0x1u << 29) /**< \brief (PMC_PCDR0) Peripheral Clock 29 Disable */
#define PMC_PCDR0_PID30 (0x1u << 30) /**< \brief (PMC_PCDR0) Peripheral Clock 30 Disable */
#define PMC_PCDR0_PID31 (0x1u << 31) /**< \brief (PMC_PCDR0) Peripheral Clock 31 Disable */
/* -------- PMC_PCSR0 : (PMC Offset: 0x0018) Peripheral Clock Status Register 0 -------- */
#define PMC_PCSR0_PID2 (0x1u << 2) /**< \brief (PMC_PCSR0) Peripheral Clock 2 Status */
#define PMC_PCSR0_PID3 (0x1u << 3) /**< \brief (PMC_PCSR0) Peripheral Clock 3 Status */
#define PMC_PCSR0_PID4 (0x1u << 4) /**< \brief (PMC_PCSR0) Peripheral Clock 4 Status */
#define PMC_PCSR0_PID5 (0x1u << 5) /**< \brief (PMC_PCSR0) Peripheral Clock 5 Status */
#define PMC_PCSR0_PID6 (0x1u << 6) /**< \brief (PMC_PCSR0) Peripheral Clock 6 Status */
#define PMC_PCSR0_PID7 (0x1u << 7) /**< \brief (PMC_PCSR0) Peripheral Clock 7 Status */
#define PMC_PCSR0_PID8 (0x1u << 8) /**< \brief (PMC_PCSR0) Peripheral Clock 8 Status */
#define PMC_PCSR0_PID9 (0x1u << 9) /**< \brief (PMC_PCSR0) Peripheral Clock 9 Status */
#define PMC_PCSR0_PID10 (0x1u << 10) /**< \brief (PMC_PCSR0) Peripheral Clock 10 Status */
#define PMC_PCSR0_PID11 (0x1u << 11) /**< \brief (PMC_PCSR0) Peripheral Clock 11 Status */
#define PMC_PCSR0_PID12 (0x1u << 12) /**< \brief (PMC_PCSR0) Peripheral Clock 12 Status */
#define PMC_PCSR0_PID13 (0x1u << 13) /**< \brief (PMC_PCSR0) Peripheral Clock 13 Status */
#define PMC_PCSR0_PID14 (0x1u << 14) /**< \brief (PMC_PCSR0) Peripheral Clock 14 Status */
#define PMC_PCSR0_PID15 (0x1u << 15) /**< \brief (PMC_PCSR0) Peripheral Clock 15 Status */
#define PMC_PCSR0_PID16 (0x1u << 16) /**< \brief (PMC_PCSR0) Peripheral Clock 16 Status */
#define PMC_PCSR0_PID17 (0x1u << 17) /**< \brief (PMC_PCSR0) Peripheral Clock 17 Status */
#define PMC_PCSR0_PID18 (0x1u << 18) /**< \brief (PMC_PCSR0) Peripheral Clock 18 Status */
#define PMC_PCSR0_PID19 (0x1u << 19) /**< \brief (PMC_PCSR0) Peripheral Clock 19 Status */
#define PMC_PCSR0_PID20 (0x1u << 20) /**< \brief (PMC_PCSR0) Peripheral Clock 20 Status */
#define PMC_PCSR0_PID21 (0x1u << 21) /**< \brief (PMC_PCSR0) Peripheral Clock 21 Status */
#define PMC_PCSR0_PID22 (0x1u << 22) /**< \brief (PMC_PCSR0) Peripheral Clock 22 Status */
#define PMC_PCSR0_PID23 (0x1u << 23) /**< \brief (PMC_PCSR0) Peripheral Clock 23 Status */
#define PMC_PCSR0_PID24 (0x1u << 24) /**< \brief (PMC_PCSR0) Peripheral Clock 24 Status */
#define PMC_PCSR0_PID25 (0x1u << 25) /**< \brief (PMC_PCSR0) Peripheral Clock 25 Status */
#define PMC_PCSR0_PID26 (0x1u << 26) /**< \brief (PMC_PCSR0) Peripheral Clock 26 Status */
#define PMC_PCSR0_PID27 (0x1u << 27) /**< \brief (PMC_PCSR0) Peripheral Clock 27 Status */
#define PMC_PCSR0_PID28 (0x1u << 28) /**< \brief (PMC_PCSR0) Peripheral Clock 28 Status */
#define PMC_PCSR0_PID29 (0x1u << 29) /**< \brief (PMC_PCSR0) Peripheral Clock 29 Status */
#define PMC_PCSR0_PID30 (0x1u << 30) /**< \brief (PMC_PCSR0) Peripheral Clock 30 Status */
#define PMC_PCSR0_PID31 (0x1u << 31) /**< \brief (PMC_PCSR0) Peripheral Clock 31 Status */
/* -------- CKGR_UCKR : (PMC Offset: 0x001C) UTMI Clock Register -------- */
#define CKGR_UCKR_UPLLEN (0x1u << 16) /**< \brief (CKGR_UCKR) UTMI PLL Enable */
#define CKGR_UCKR_UPLLCOUNT_Pos 20
#define CKGR_UCKR_UPLLCOUNT_Msk (0xfu << CKGR_UCKR_UPLLCOUNT_Pos) /**< \brief (CKGR_UCKR) UTMI PLL Start-up Time */
#define CKGR_UCKR_UPLLCOUNT(value) ((CKGR_UCKR_UPLLCOUNT_Msk & ((value) << CKGR_UCKR_UPLLCOUNT_Pos)))
#define CKGR_UCKR_BIASEN (0x1u << 24) /**< \brief (CKGR_UCKR) UTMI BIAS Enable */
#define CKGR_UCKR_BIASCOUNT_Pos 28
#define CKGR_UCKR_BIASCOUNT_Msk (0xfu << CKGR_UCKR_BIASCOUNT_Pos) /**< \brief (CKGR_UCKR) UTMI BIAS Start-up Time */
#define CKGR_UCKR_BIASCOUNT(value) ((CKGR_UCKR_BIASCOUNT_Msk & ((value) << CKGR_UCKR_BIASCOUNT_Pos)))
/* -------- CKGR_MOR : (PMC Offset: 0x0020) Main Oscillator Register -------- */
#define CKGR_MOR_MOSCXTEN (0x1u << 0) /**< \brief (CKGR_MOR) Main Crystal Oscillator Enable */
#define CKGR_MOR_MOSCXTBY (0x1u << 1) /**< \brief (CKGR_MOR) Main Crystal Oscillator Bypass */
#define CKGR_MOR_MOSCXTST_Pos 8
#define CKGR_MOR_MOSCXTST_Msk (0xffu << CKGR_MOR_MOSCXTST_Pos) /**< \brief (CKGR_MOR) Main Crystal Oscillator Startup Time */
#define CKGR_MOR_MOSCXTST(value) ((CKGR_MOR_MOSCXTST_Msk & ((value) << CKGR_MOR_MOSCXTST_Pos)))
#define CKGR_MOR_KEY_Pos 16
#define CKGR_MOR_KEY_Msk (0xffu << CKGR_MOR_KEY_Pos) /**< \brief (CKGR_MOR) Password */
#define   CKGR_MOR_KEY_PASSWD (0x37u << 16) /**< \brief (CKGR_MOR) Writing any other value in this field aborts the write operation. */
#define CKGR_MOR_MOSCSEL (0x1u << 24) /**< \brief (CKGR_MOR) Main Oscillator Selection */
#define CKGR_MOR_CFDEN (0x1u << 25) /**< \brief (CKGR_MOR) Clock Failure Detector Enable */
/* -------- CKGR_MCFR : (PMC Offset: 0x0024) Main Clock Frequency Register -------- */
#define CKGR_MCFR_MAINF_Pos 0
#define CKGR_MCFR_MAINF_Msk (0xffffu << CKGR_MCFR_MAINF_Pos) /**< \brief (CKGR_MCFR) Main Clock Frequency */
#define CKGR_MCFR_MAINFRDY (0x1u << 16) /**< \brief (CKGR_MCFR) Main Clock Ready */
/* -------- CKGR_PLLAR : (PMC Offset: 0x0028) PLLA Register -------- */
#define CKGR_PLLAR_PLLACOUNT_Pos 8
#define CKGR_PLLAR_PLLACOUNT_Msk (0x3fu << CKGR_PLLAR_PLLACOUNT_Pos) /**< \brief (CKGR_PLLAR) PLLA Counter */
#define CKGR_PLLAR_PLLACOUNT(value) ((CKGR_PLLAR_PLLACOUNT_Msk & ((value) << CKGR_PLLAR_PLLACOUNT_Pos)))
#define CKGR_PLLAR_OUTA_Pos 14
#define CKGR_PLLAR_OUTA_Msk (0xfu << CKGR_PLLAR_OUTA_Pos) /**< \brief (CKGR_PLLAR) PLLA Clock Frequency Range */
#define CKGR_PLLAR_OUTA(value) ((CKGR_PLLAR_OUTA_Msk & ((value) << CKGR_PLLAR_OUTA_Pos)))
#define CKGR_PLLAR_MULA_Pos 18
#define CKGR_PLLAR_MULA_Msk (0x7fu << CKGR_PLLAR_MULA_Pos) /**< \brief (CKGR_PLLAR) PLLA Multiplier */
#define CKGR_PLLAR_MULA(value) ((CKGR_PLLAR_MULA_Msk & ((value) << CKGR_PLLAR_MULA_Pos)))
#define CKGR_PLLAR_ONE (0x1u << 29) /**< \brief (CKGR_PLLAR) Must Be Set to 1 */
/* -------- PMC_MCKR : (PMC Offset: 0x0030) Master Clock Register -------- */
#define PMC_MCKR_CSS_Pos 0
#define PMC_MCKR_CSS_Msk (0x3u << PMC_MCKR_CSS_Pos) /**< \brief (PMC_MCKR) Master/Processor Clock Source Selection */
#define   PMC_MCKR_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_MCKR) Slow Clock is selected */
#define   PMC_MCKR_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_MCKR) Main Clock is selected */
#define   PMC_MCKR_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_MCKR) PLLACK is selected */
#define   PMC_MCKR_CSS_UPLL_CLK (0x3u << 0) /**< \brief (PMC_MCKR) UPLL Clock is selected */
#define PMC_MCKR_PRES_Pos 4
#define PMC_MCKR_PRES_Msk (0x7u << PMC_MCKR_PRES_Pos) /**< \brief (PMC_MCKR) Master/Processor Clock Prescaler */
#define   PMC_MCKR_PRES_CLOCK (0x0u << 4) /**< \brief (PMC_MCKR) Selected clock */
#define   PMC_MCKR_PRES_CLOCK_DIV2 (0x1u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 2 */
#define   PMC_MCKR_PRES_CLOCK_DIV4 (0x2u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 4 */
#define   PMC_MCKR_PRES_CLOCK_DIV8 (0x3u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 8 */
#define   PMC_MCKR_PRES_CLOCK_DIV16 (0x4u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 16 */
#define   PMC_MCKR_PRES_CLOCK_DIV32 (0x5u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 32 */
#define   PMC_MCKR_PRES_CLOCK_DIV64 (0x6u << 4) /**< \brief (PMC_MCKR) Selected clock divided by 64 */
#define PMC_MCKR_MDIV_Pos 8
#define PMC_MCKR_MDIV_Msk (0x3u << PMC_MCKR_MDIV_Pos) /**< \brief (PMC_MCKR) Master Clock Division */
#define   PMC_MCKR_MDIV_EQ_PCK (0x0u << 8) /**< \brief (PMC_MCKR) Master Clock is Prescaler Output Clock divided by 1.Warning: SysClk DDR and DDRCK are not available. */
#define   PMC_MCKR_MDIV_PCK_DIV2 (0x1u << 8) /**< \brief (PMC_MCKR) Master Clock is Prescaler Output Clock divided by 2.SysClk DDR is equal to 2 x MCK. DDRCK is equal to MCK. */
#define   PMC_MCKR_MDIV_PCK_DIV4 (0x2u << 8) /**< \brief (PMC_MCKR) Master Clock is Prescaler Output Clock divided by 4.SysClk DDR is equal to 2 x MCK. DDRCK is equal to MCK. */
#define   PMC_MCKR_MDIV_PCK_DIV3 (0x3u << 8) /**< \brief (PMC_MCKR) Master Clock is Prescaler Output Clock divided by 3.SysClk DDR is equal to 2 x MCK. DDRCK is equal to MCK. */
#define PMC_MCKR_PLLADIV2 (0x1u << 12) /**< \brief (PMC_MCKR) PLLA Divisor by 2 */
#define PMC_MCKR_H32MXDIV (0x1u << 24) /**< \brief (PMC_MCKR) AHB 32-bit Matrix Divisor */
#define   PMC_MCKR_H32MXDIV_H32MXDIV1 (0x0u << 24) /**< \brief (PMC_MCKR) The AHB 32-bit Matrix frequency is equal to the AHB 64-bit Matrix frequency. It is possible only if the AHB 64-bit Matrix frequency is not exceeding 90 MHz. */
#define   PMC_MCKR_H32MXDIV_H32MXDIV2 (0x1u << 24) /**< \brief (PMC_MCKR) The AHB 32-bit Matrix frequency is equal to the AHB 64-bit Matrix frequency divided by 2. */
/* -------- PMC_USB : (PMC Offset: 0x0038) USB Clock Register -------- */
#define PMC_USB_USBS (0x1u << 0) /**< \brief (PMC_USB) USB OHCI Input clock selection */
#define PMC_USB_USBDIV_Pos 8
#define PMC_USB_USBDIV_Msk (0xfu << PMC_USB_USBDIV_Pos) /**< \brief (PMC_USB) Divider for USB OHCI Clock. */
#define PMC_USB_USBDIV(value) ((PMC_USB_USBDIV_Msk & ((value) << PMC_USB_USBDIV_Pos)))
/* -------- PMC_SMD : (PMC Offset: 0x003C) Soft Modem Clock Register -------- */
#define PMC_SMD_SMDS (0x1u << 0) /**< \brief (PMC_SMD) SMD input clock selection */
#define PMC_SMD_SMDDIV_Pos 8
#define PMC_SMD_SMDDIV_Msk (0x1fu << PMC_SMD_SMDDIV_Pos) /**< \brief (PMC_SMD) Divider for SMD Clock. */
#define PMC_SMD_SMDDIV(value) ((PMC_SMD_SMDDIV_Msk & ((value) << PMC_SMD_SMDDIV_Pos)))
/* -------- PMC_PCK[3] : (PMC Offset: 0x0040) Programmable Clock 0 Register -------- */
#define PMC_PCK_CSS_Pos 0
#define PMC_PCK_CSS_Msk (0x7u << PMC_PCK_CSS_Pos) /**< \brief (PMC_PCK[3]) Master Clock Source Selection */
#define   PMC_PCK_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_PCK[3]) Slow Clock is selected */
#define   PMC_PCK_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_PCK[3]) Main Clock is selected */
#define   PMC_PCK_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_PCK[3]) PLLACK is selected */
#define   PMC_PCK_CSS_UPLL_CLK (0x3u << 0) /**< \brief (PMC_PCK[3]) UPLL Clock is selected */
#define   PMC_PCK_CSS_MCK_CLK (0x4u << 0) /**< \brief (PMC_PCK[3]) Master Clock is selected */
#define PMC_PCK_PRES_Pos 4
#define PMC_PCK_PRES_Msk (0x7u << PMC_PCK_PRES_Pos) /**< \brief (PMC_PCK[3]) Programmable Clock Prescaler */
#define   PMC_PCK_PRES_CLOCK (0x0u << 4) /**< \brief (PMC_PCK[3]) Selected clock */
#define   PMC_PCK_PRES_CLOCK_DIV2 (0x1u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 2 */
#define   PMC_PCK_PRES_CLOCK_DIV4 (0x2u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 4 */
#define   PMC_PCK_PRES_CLOCK_DIV8 (0x3u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 8 */
#define   PMC_PCK_PRES_CLOCK_DIV16 (0x4u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 16 */
#define   PMC_PCK_PRES_CLOCK_DIV32 (0x5u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 32 */
#define   PMC_PCK_PRES_CLOCK_DIV64 (0x6u << 4) /**< \brief (PMC_PCK[3]) Selected clock divided by 64 */
/* -------- PMC_IER : (PMC Offset: 0x0060) Interrupt Enable Register -------- */
#define PMC_IER_MOSCXTS (0x1u << 0) /**< \brief (PMC_IER) Main Crystal Oscillator Status Interrupt Enable */
#define PMC_IER_LOCKA (0x1u << 1) /**< \brief (PMC_IER) PLLA Lock Interrupt Enable */
#define PMC_IER_MCKRDY (0x1u << 3) /**< \brief (PMC_IER) Master Clock Ready Interrupt Enable */
#define PMC_IER_LOCKU (0x1u << 6) /**< \brief (PMC_IER) UTMI PLL Lock Interrupt Enable */
#define PMC_IER_PCKRDY0 (0x1u << 8) /**< \brief (PMC_IER) Programmable Clock Ready 0 Interrupt Enable */
#define PMC_IER_PCKRDY1 (0x1u << 9) /**< \brief (PMC_IER) Programmable Clock Ready 1 Interrupt Enable */
#define PMC_IER_PCKRDY2 (0x1u << 10) /**< \brief (PMC_IER) Programmable Clock Ready 2 Interrupt Enable */
#define PMC_IER_MOSCSELS (0x1u << 16) /**< \brief (PMC_IER) Main Oscillator Selection Status Interrupt Enable */
#define PMC_IER_MOSCRCS (0x1u << 17) /**< \brief (PMC_IER) Main On-Chip RC Status Interrupt Enable */
#define PMC_IER_CFDEV (0x1u << 18) /**< \brief (PMC_IER) Clock Failure Detector Event Interrupt Enable */
/* -------- PMC_IDR : (PMC Offset: 0x0064) Interrupt Disable Register -------- */
#define PMC_IDR_MOSCXTS (0x1u << 0) /**< \brief (PMC_IDR) Main Crystal Oscillator Status Interrupt Disable */
#define PMC_IDR_LOCKA (0x1u << 1) /**< \brief (PMC_IDR) PLLA Lock Interrupt Disable */
#define PMC_IDR_MCKRDY (0x1u << 3) /**< \brief (PMC_IDR) Master Clock Ready Interrupt Disable */
#define PMC_IDR_LOCKU (0x1u << 6) /**< \brief (PMC_IDR) UTMI PLL Lock Interrupt Enable */
#define PMC_IDR_PCKRDY0 (0x1u << 8) /**< \brief (PMC_IDR) Programmable Clock Ready 0 Interrupt Disable */
#define PMC_IDR_PCKRDY1 (0x1u << 9) /**< \brief (PMC_IDR) Programmable Clock Ready 1 Interrupt Disable */
#define PMC_IDR_PCKRDY2 (0x1u << 10) /**< \brief (PMC_IDR) Programmable Clock Ready 2 Interrupt Disable */
#define PMC_IDR_MOSCSELS (0x1u << 16) /**< \brief (PMC_IDR) Main Oscillator Selection Status Interrupt Disable */
#define PMC_IDR_MOSCRCS (0x1u << 17) /**< \brief (PMC_IDR) Main On-Chip RC Status Interrupt Disable */
#define PMC_IDR_CFDEV (0x1u << 18) /**< \brief (PMC_IDR) Clock Failure Detector Event Interrupt Disable */
/* -------- PMC_SR : (PMC Offset: 0x0068) Status Register -------- */
#define PMC_SR_MOSCXTS (0x1u << 0) /**< \brief (PMC_SR) Main XTAL Oscillator Status */
#define PMC_SR_LOCKA (0x1u << 1) /**< \brief (PMC_SR) PLLA Lock Status */
#define PMC_SR_MCKRDY (0x1u << 3) /**< \brief (PMC_SR) Master Clock Status */
#define PMC_SR_LOCKU (0x1u << 6) /**< \brief (PMC_SR) UPLL Clock Status */
#define PMC_SR_OSCSELS (0x1u << 7) /**< \brief (PMC_SR) Slow Clock Oscillator Selection */
#define PMC_SR_PCKRDY0 (0x1u << 8) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY1 (0x1u << 9) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_PCKRDY2 (0x1u << 10) /**< \brief (PMC_SR) Programmable Clock Ready Status */
#define PMC_SR_MOSCSELS (0x1u << 16) /**< \brief (PMC_SR) Main Oscillator Selection Status */
#define PMC_SR_MOSCRCS (0x1u << 17) /**< \brief (PMC_SR) Main On-Chip RC Oscillator Status */
#define PMC_SR_CFDEV (0x1u << 18) /**< \brief (PMC_SR) Clock Failure Detector Event */
#define PMC_SR_CFDS (0x1u << 19) /**< \brief (PMC_SR) Clock Failure Detector Status */
#define PMC_SR_FOS (0x1u << 20) /**< \brief (PMC_SR) Clock Failure Detector Fault Output Status */
/* -------- PMC_IMR : (PMC Offset: 0x006C) Interrupt Mask Register -------- */
#define PMC_IMR_MOSCXTS (0x1u << 0) /**< \brief (PMC_IMR) Main Crystal Oscillator Status Interrupt Mask */
#define PMC_IMR_LOCKA (0x1u << 1) /**< \brief (PMC_IMR) PLLA Lock Interrupt Mask */
#define PMC_IMR_MCKRDY (0x1u << 3) /**< \brief (PMC_IMR) Master Clock Ready Interrupt Mask */
#define PMC_IMR_PCKRDY0 (0x1u << 8) /**< \brief (PMC_IMR) Programmable Clock Ready 0 Interrupt Mask */
#define PMC_IMR_PCKRDY1 (0x1u << 9) /**< \brief (PMC_IMR) Programmable Clock Ready 1 Interrupt Mask */
#define PMC_IMR_PCKRDY2 (0x1u << 10) /**< \brief (PMC_IMR) Programmable Clock Ready 2 Interrupt Mask */
#define PMC_IMR_MOSCSELS (0x1u << 16) /**< \brief (PMC_IMR) Main Oscillator Selection Status Interrupt Mask */
#define PMC_IMR_MOSCRCS (0x1u << 17) /**< \brief (PMC_IMR) Main On-Chip RC Status Interrupt Mask */
#define PMC_IMR_CFDEV (0x1u << 18) /**< \brief (PMC_IMR) Clock Failure Detector Event Interrupt Mask */
/* -------- PMC_FOCR : (PMC Offset: 0x0078) Fault Output Clear Register -------- */
#define PMC_FOCR_FOCLR (0x1u << 0) /**< \brief (PMC_FOCR) Fault Output Clear */
/* -------- PMC_PLLICPR : (PMC Offset: 0x0080) PLL Charge Pump Current Register -------- */
#define PMC_PLLICPR_ICP_PLLA_Pos 0
#define PMC_PLLICPR_ICP_PLLA_Msk (0x3u << PMC_PLLICPR_ICP_PLLA_Pos) /**< \brief (PMC_PLLICPR) Charge Pump Current PLLA */
#define PMC_PLLICPR_ICP_PLLA(value) ((PMC_PLLICPR_ICP_PLLA_Msk & ((value) << PMC_PLLICPR_ICP_PLLA_Pos)))
#define PMC_PLLICPR_IPLL_PLLA_Pos 8
#define PMC_PLLICPR_IPLL_PLLA_Msk (0x7u << PMC_PLLICPR_IPLL_PLLA_Pos) /**< \brief (PMC_PLLICPR) Engineering Configuration PLLA */
#define PMC_PLLICPR_IPLL_PLLA(value) ((PMC_PLLICPR_IPLL_PLLA_Msk & ((value) << PMC_PLLICPR_IPLL_PLLA_Pos)))
#define PMC_PLLICPR_ICP_PLLU_Pos 16
#define PMC_PLLICPR_ICP_PLLU_Msk (0x3u << PMC_PLLICPR_ICP_PLLU_Pos) /**< \brief (PMC_PLLICPR) Charge Pump Current PLL UTMI */
#define PMC_PLLICPR_ICP_PLLU(value) ((PMC_PLLICPR_ICP_PLLU_Msk & ((value) << PMC_PLLICPR_ICP_PLLU_Pos)))
#define PMC_PLLICPR_IVCO_PLLU_Pos 24
#define PMC_PLLICPR_IVCO_PLLU_Msk (0x3u << PMC_PLLICPR_IVCO_PLLU_Pos) /**< \brief (PMC_PLLICPR) Voltage Control Output Current PLL UTMI */
#define PMC_PLLICPR_IVCO_PLLU(value) ((PMC_PLLICPR_IVCO_PLLU_Msk & ((value) << PMC_PLLICPR_IVCO_PLLU_Pos)))
/* -------- PMC_WPMR : (PMC Offset: 0x00E4) Write Protect Mode Register -------- */
#define PMC_WPMR_WPEN (0x1u << 0) /**< \brief (PMC_WPMR) Write Protect Enable */
#define PMC_WPMR_WPKEY_Pos 8
#define PMC_WPMR_WPKEY_Msk (0xffffffu << PMC_WPMR_WPKEY_Pos) /**< \brief (PMC_WPMR) Write Protect KEY */
#define   PMC_WPMR_WPKEY_PASSWD (0x504D43u << 8) /**< \brief (PMC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */
/* -------- PMC_WPSR : (PMC Offset: 0x00E8) Write Protect Status Register -------- */
#define PMC_WPSR_WPVS (0x1u << 0) /**< \brief (PMC_WPSR) Write Protect Violation Status */
#define PMC_WPSR_WPVSRC_Pos 8
#define PMC_WPSR_WPVSRC_Msk (0xffffu << PMC_WPSR_WPVSRC_Pos) /**< \brief (PMC_WPSR) Write Protect Violation Source */
/* -------- PMC_PCER1 : (PMC Offset: 0x0100) Peripheral Clock Enable Register 1 -------- */
#define PMC_PCER1_PID32 (0x1u << 0) /**< \brief (PMC_PCER1) Peripheral Clock 32 Enable */
#define PMC_PCER1_PID33 (0x1u << 1) /**< \brief (PMC_PCER1) Peripheral Clock 33 Enable */
#define PMC_PCER1_PID34 (0x1u << 2) /**< \brief (PMC_PCER1) Peripheral Clock 34 Enable */
#define PMC_PCER1_PID35 (0x1u << 3) /**< \brief (PMC_PCER1) Peripheral Clock 35 Enable */
#define PMC_PCER1_PID36 (0x1u << 4) /**< \brief (PMC_PCER1) Peripheral Clock 36 Enable */
#define PMC_PCER1_PID37 (0x1u << 5) /**< \brief (PMC_PCER1) Peripheral Clock 37 Enable */
#define PMC_PCER1_PID38 (0x1u << 6) /**< \brief (PMC_PCER1) Peripheral Clock 38 Enable */
#define PMC_PCER1_PID39 (0x1u << 7) /**< \brief (PMC_PCER1) Peripheral Clock 39 Enable */
#define PMC_PCER1_PID40 (0x1u << 8) /**< \brief (PMC_PCER1) Peripheral Clock 40 Enable */
#define PMC_PCER1_PID41 (0x1u << 9) /**< \brief (PMC_PCER1) Peripheral Clock 41 Enable */
#define PMC_PCER1_PID42 (0x1u << 10) /**< \brief (PMC_PCER1) Peripheral Clock 42 Enable */
#define PMC_PCER1_PID43 (0x1u << 11) /**< \brief (PMC_PCER1) Peripheral Clock 43 Enable */
#define PMC_PCER1_PID44 (0x1u << 12) /**< \brief (PMC_PCER1) Peripheral Clock 44 Enable */
#define PMC_PCER1_PID45 (0x1u << 13) /**< \brief (PMC_PCER1) Peripheral Clock 45 Enable */
#define PMC_PCER1_PID46 (0x1u << 14) /**< \brief (PMC_PCER1) Peripheral Clock 46 Enable */
#define PMC_PCER1_PID47 (0x1u << 15) /**< \brief (PMC_PCER1) Peripheral Clock 47 Enable */
#define PMC_PCER1_PID48 (0x1u << 16) /**< \brief (PMC_PCER1) Peripheral Clock 48 Enable */
#define PMC_PCER1_PID49 (0x1u << 17) /**< \brief (PMC_PCER1) Peripheral Clock 49 Enable */
#define PMC_PCER1_PID50 (0x1u << 18) /**< \brief (PMC_PCER1) Peripheral Clock 50 Enable */
#define PMC_PCER1_PID51 (0x1u << 19) /**< \brief (PMC_PCER1) Peripheral Clock 51 Enable */
#define PMC_PCER1_PID52 (0x1u << 20) /**< \brief (PMC_PCER1) Peripheral Clock 52 Enable */
#define PMC_PCER1_PID53 (0x1u << 21) /**< \brief (PMC_PCER1) Peripheral Clock 53 Enable */
#define PMC_PCER1_PID54 (0x1u << 22) /**< \brief (PMC_PCER1) Peripheral Clock 54 Enable */
#define PMC_PCER1_PID55 (0x1u << 23) /**< \brief (PMC_PCER1) Peripheral Clock 55 Enable */
#define PMC_PCER1_PID56 (0x1u << 24) /**< \brief (PMC_PCER1) Peripheral Clock 56 Enable */
#define PMC_PCER1_PID57 (0x1u << 25) /**< \brief (PMC_PCER1) Peripheral Clock 57 Enable */
#define PMC_PCER1_PID58 (0x1u << 26) /**< \brief (PMC_PCER1) Peripheral Clock 58 Enable */
#define PMC_PCER1_PID59 (0x1u << 27) /**< \brief (PMC_PCER1) Peripheral Clock 59 Enable */
#define PMC_PCER1_PID60 (0x1u << 28) /**< \brief (PMC_PCER1) Peripheral Clock 60 Enable */
#define PMC_PCER1_PID61 (0x1u << 29) /**< \brief (PMC_PCER1) Peripheral Clock 61 Enable */
#define PMC_PCER1_PID62 (0x1u << 30) /**< \brief (PMC_PCER1) Peripheral Clock 62 Enable */
#define PMC_PCER1_PID63 (0x1u << 31) /**< \brief (PMC_PCER1) Peripheral Clock 63 Enable */
/* -------- PMC_PCDR1 : (PMC Offset: 0x0104) Peripheral Clock Disable Register 1 -------- */
#define PMC_PCDR1_PID32 (0x1u << 0) /**< \brief (PMC_PCDR1) Peripheral Clock 32 Disable */
#define PMC_PCDR1_PID33 (0x1u << 1) /**< \brief (PMC_PCDR1) Peripheral Clock 33 Disable */
#define PMC_PCDR1_PID34 (0x1u << 2) /**< \brief (PMC_PCDR1) Peripheral Clock 34 Disable */
#define PMC_PCDR1_PID35 (0x1u << 3) /**< \brief (PMC_PCDR1) Peripheral Clock 35 Disable */
#define PMC_PCDR1_PID36 (0x1u << 4) /**< \brief (PMC_PCDR1) Peripheral Clock 36 Disable */
#define PMC_PCDR1_PID37 (0x1u << 5) /**< \brief (PMC_PCDR1) Peripheral Clock 37 Disable */
#define PMC_PCDR1_PID38 (0x1u << 6) /**< \brief (PMC_PCDR1) Peripheral Clock 38 Disable */
#define PMC_PCDR1_PID39 (0x1u << 7) /**< \brief (PMC_PCDR1) Peripheral Clock 39 Disable */
#define PMC_PCDR1_PID40 (0x1u << 8) /**< \brief (PMC_PCDR1) Peripheral Clock 40 Disable */
#define PMC_PCDR1_PID41 (0x1u << 9) /**< \brief (PMC_PCDR1) Peripheral Clock 41 Disable */
#define PMC_PCDR1_PID42 (0x1u << 10) /**< \brief (PMC_PCDR1) Peripheral Clock 42 Disable */
#define PMC_PCDR1_PID43 (0x1u << 11) /**< \brief (PMC_PCDR1) Peripheral Clock 43 Disable */
#define PMC_PCDR1_PID44 (0x1u << 12) /**< \brief (PMC_PCDR1) Peripheral Clock 44 Disable */
#define PMC_PCDR1_PID45 (0x1u << 13) /**< \brief (PMC_PCDR1) Peripheral Clock 45 Disable */
#define PMC_PCDR1_PID46 (0x1u << 14) /**< \brief (PMC_PCDR1) Peripheral Clock 46 Disable */
#define PMC_PCDR1_PID47 (0x1u << 15) /**< \brief (PMC_PCDR1) Peripheral Clock 47 Disable */
#define PMC_PCDR1_PID48 (0x1u << 16) /**< \brief (PMC_PCDR1) Peripheral Clock 48 Disable */
#define PMC_PCDR1_PID49 (0x1u << 17) /**< \brief (PMC_PCDR1) Peripheral Clock 49 Disable */
#define PMC_PCDR1_PID50 (0x1u << 18) /**< \brief (PMC_PCDR1) Peripheral Clock 50 Disable */
#define PMC_PCDR1_PID51 (0x1u << 19) /**< \brief (PMC_PCDR1) Peripheral Clock 51 Disable */
#define PMC_PCDR1_PID52 (0x1u << 20) /**< \brief (PMC_PCDR1) Peripheral Clock 52 Disable */
#define PMC_PCDR1_PID53 (0x1u << 21) /**< \brief (PMC_PCDR1) Peripheral Clock 53 Disable */
#define PMC_PCDR1_PID54 (0x1u << 22) /**< \brief (PMC_PCDR1) Peripheral Clock 54 Disable */
#define PMC_PCDR1_PID55 (0x1u << 23) /**< \brief (PMC_PCDR1) Peripheral Clock 55 Disable */
#define PMC_PCDR1_PID56 (0x1u << 24) /**< \brief (PMC_PCDR1) Peripheral Clock 56 Disable */
#define PMC_PCDR1_PID57 (0x1u << 25) /**< \brief (PMC_PCDR1) Peripheral Clock 57 Disable */
#define PMC_PCDR1_PID58 (0x1u << 26) /**< \brief (PMC_PCDR1) Peripheral Clock 58 Disable */
#define PMC_PCDR1_PID59 (0x1u << 27) /**< \brief (PMC_PCDR1) Peripheral Clock 59 Disable */
#define PMC_PCDR1_PID60 (0x1u << 28) /**< \brief (PMC_PCDR1) Peripheral Clock 60 Disable */
#define PMC_PCDR1_PID61 (0x1u << 29) /**< \brief (PMC_PCDR1) Peripheral Clock 61 Disable */
#define PMC_PCDR1_PID62 (0x1u << 30) /**< \brief (PMC_PCDR1) Peripheral Clock 62 Disable */
#define PMC_PCDR1_PID63 (0x1u << 31) /**< \brief (PMC_PCDR1) Peripheral Clock 63 Disable */
/* -------- PMC_PCSR1 : (PMC Offset: 0x0108) Peripheral Clock Status Register 1 -------- */
#define PMC_PCSR1_PID32 (0x1u << 0) /**< \brief (PMC_PCSR1) Peripheral Clock 32 Status */
#define PMC_PCSR1_PID33 (0x1u << 1) /**< \brief (PMC_PCSR1) Peripheral Clock 33 Status */
#define PMC_PCSR1_PID34 (0x1u << 2) /**< \brief (PMC_PCSR1) Peripheral Clock 34 Status */
#define PMC_PCSR1_PID35 (0x1u << 3) /**< \brief (PMC_PCSR1) Peripheral Clock 35 Status */
#define PMC_PCSR1_PID36 (0x1u << 4) /**< \brief (PMC_PCSR1) Peripheral Clock 36 Status */
#define PMC_PCSR1_PID37 (0x1u << 5) /**< \brief (PMC_PCSR1) Peripheral Clock 37 Status */
#define PMC_PCSR1_PID38 (0x1u << 6) /**< \brief (PMC_PCSR1) Peripheral Clock 38 Status */
#define PMC_PCSR1_PID39 (0x1u << 7) /**< \brief (PMC_PCSR1) Peripheral Clock 39 Status */
#define PMC_PCSR1_PID40 (0x1u << 8) /**< \brief (PMC_PCSR1) Peripheral Clock 40 Status */
#define PMC_PCSR1_PID41 (0x1u << 9) /**< \brief (PMC_PCSR1) Peripheral Clock 41 Status */
#define PMC_PCSR1_PID42 (0x1u << 10) /**< \brief (PMC_PCSR1) Peripheral Clock 42 Status */
#define PMC_PCSR1_PID43 (0x1u << 11) /**< \brief (PMC_PCSR1) Peripheral Clock 43 Status */
#define PMC_PCSR1_PID44 (0x1u << 12) /**< \brief (PMC_PCSR1) Peripheral Clock 44 Status */
#define PMC_PCSR1_PID45 (0x1u << 13) /**< \brief (PMC_PCSR1) Peripheral Clock 45 Status */
#define PMC_PCSR1_PID46 (0x1u << 14) /**< \brief (PMC_PCSR1) Peripheral Clock 46 Status */
#define PMC_PCSR1_PID47 (0x1u << 15) /**< \brief (PMC_PCSR1) Peripheral Clock 47 Status */
#define PMC_PCSR1_PID48 (0x1u << 16) /**< \brief (PMC_PCSR1) Peripheral Clock 48 Status */
#define PMC_PCSR1_PID49 (0x1u << 17) /**< \brief (PMC_PCSR1) Peripheral Clock 49 Status */
#define PMC_PCSR1_PID50 (0x1u << 18) /**< \brief (PMC_PCSR1) Peripheral Clock 50 Status */
#define PMC_PCSR1_PID51 (0x1u << 19) /**< \brief (PMC_PCSR1) Peripheral Clock 51 Status */
#define PMC_PCSR1_PID52 (0x1u << 20) /**< \brief (PMC_PCSR1) Peripheral Clock 52 Status */
#define PMC_PCSR1_PID53 (0x1u << 21) /**< \brief (PMC_PCSR1) Peripheral Clock 53 Status */
#define PMC_PCSR1_PID54 (0x1u << 22) /**< \brief (PMC_PCSR1) Peripheral Clock 54 Status */
#define PMC_PCSR1_PID55 (0x1u << 23) /**< \brief (PMC_PCSR1) Peripheral Clock 55 Status */
#define PMC_PCSR1_PID56 (0x1u << 24) /**< \brief (PMC_PCSR1) Peripheral Clock 56 Status */
#define PMC_PCSR1_PID57 (0x1u << 25) /**< \brief (PMC_PCSR1) Peripheral Clock 57 Status */
#define PMC_PCSR1_PID58 (0x1u << 26) /**< \brief (PMC_PCSR1) Peripheral Clock 58 Status */
#define PMC_PCSR1_PID59 (0x1u << 27) /**< \brief (PMC_PCSR1) Peripheral Clock 59 Status */
#define PMC_PCSR1_PID60 (0x1u << 28) /**< \brief (PMC_PCSR1) Peripheral Clock 60 Status */
#define PMC_PCSR1_PID61 (0x1u << 29) /**< \brief (PMC_PCSR1) Peripheral Clock 61 Status */
#define PMC_PCSR1_PID62 (0x1u << 30) /**< \brief (PMC_PCSR1) Peripheral Clock 62 Status */
#define PMC_PCSR1_PID63 (0x1u << 31) /**< \brief (PMC_PCSR1) Peripheral Clock 63 Status */
/* -------- PMC_PCR : (PMC Offset: 0x010C) Peripheral Control Register -------- */
#define PMC_PCR_PID_Pos 0
#define PMC_PCR_PID_Msk (0x3fu << PMC_PCR_PID_Pos) /**< \brief (PMC_PCR) Peripheral ID */
#define PMC_PCR_PID(value) ((PMC_PCR_PID_Msk & ((value) << PMC_PCR_PID_Pos)))
#define PMC_PCR_CMD (0x1u << 12) /**< \brief (PMC_PCR) Command */
#define PMC_PCR_DIV_Pos 16
#define PMC_PCR_DIV_Msk (0x3u << PMC_PCR_DIV_Pos) /**< \brief (PMC_PCR) Divisor value */
#define   PMC_PCR_DIV_PERIPH_DIV_MCK (0x0u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK */
#define   PMC_PCR_DIV_PERIPH_DIV2_MCK (0x1u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK/2 */
#define   PMC_PCR_DIV_PERIPH_DIV4_MCK (0x2u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK/4 */
#define   PMC_PCR_DIV_PERIPH_DIV8_MCK (0x3u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK/8 */
#define PMC_PCR_EN (0x1u << 28) /**< \brief (PMC_PCR) Enable */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Reset Controller */
/* ============================================================================= */
/** \addtogroup SAMA5D4_RSTC Reset Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Rstc hardware registers */
typedef struct {
  __O  uint32_t RSTC_CR; /**< \brief (Rstc Offset: 0x00) Control Register */
  __I  uint32_t RSTC_SR; /**< \brief (Rstc Offset: 0x04) Status Register */
  __IO uint32_t RSTC_MR; /**< \brief (Rstc Offset: 0x08) Mode Register */
} Rstc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- RSTC_CR : (RSTC Offset: 0x00) Control Register -------- */
#define RSTC_CR_PROCRST (0x1u << 0) /**< \brief (RSTC_CR) Processor Reset */
#define RSTC_CR_PERRST (0x1u << 2) /**< \brief (RSTC_CR) Peripheral Reset */
#define RSTC_CR_EXTRST (0x1u << 3) /**< \brief (RSTC_CR) External Reset */
#define RSTC_CR_KEY_Pos 24
#define RSTC_CR_KEY_Msk (0xffu << RSTC_CR_KEY_Pos) /**< \brief (RSTC_CR) Password */
#define RSTC_CR_KEY(value) ((RSTC_CR_KEY_Msk & ((value) << RSTC_CR_KEY_Pos)))
/* -------- RSTC_SR : (RSTC Offset: 0x04) Status Register -------- */
#define RSTC_SR_URSTS (0x1u << 0) /**< \brief (RSTC_SR) User Reset Status */
#define RSTC_SR_RSTTYP_Pos 8
#define RSTC_SR_RSTTYP_Msk (0x7u << RSTC_SR_RSTTYP_Pos) /**< \brief (RSTC_SR) Reset Type */
#define RSTC_SR_NRSTL (0x1u << 16) /**< \brief (RSTC_SR) NRST Pin Level */
#define RSTC_SR_SRCMP (0x1u << 17) /**< \brief (RSTC_SR) Software Reset Command in Progress */
/* -------- RSTC_MR : (RSTC Offset: 0x08) Mode Register -------- */
#define RSTC_MR_URSTEN (0x1u << 0) /**< \brief (RSTC_MR) User Reset Enable */
#define RSTC_MR_URSTIEN (0x1u << 4) /**< \brief (RSTC_MR) User Reset Interrupt Enable */
#define RSTC_MR_ERSTL_Pos 8
#define RSTC_MR_ERSTL_Msk (0xfu << RSTC_MR_ERSTL_Pos) /**< \brief (RSTC_MR) External Reset Length */
#define RSTC_MR_ERSTL(value) ((RSTC_MR_ERSTL_Msk & ((value) << RSTC_MR_ERSTL_Pos)))
#define RSTC_MR_KEY_Pos 24
#define RSTC_MR_KEY_Msk (0xffu << RSTC_MR_KEY_Pos) /**< \brief (RSTC_MR) Password */
#define RSTC_MR_KEY(value) ((RSTC_MR_KEY_Msk & ((value) << RSTC_MR_KEY_Pos)))

/*@}*/


/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Slow Clock Controller */
/* ============================================================================= */
/** \addtogroup SAMA5D4_SCKC Slow Clock Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Sckc hardware registers */
typedef struct {
  __IO uint32_t SCKC_CR; /**< \brief (Sckc Offset: 0x0) Slow Clock Configuration Register */
} Sckc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SCKC_CR : (SCKC Offset: 0x0) Slow Clock Configuration Register -------- */
#define SCKC_CR_OSCSEL (0x1u << 3) /**< \brief (SCKC_CR) Slow Clock Selector */
#define   SCKC_CR_OSCSEL_RC (0x0u << 3) /**< \brief (SCKC_CR) Slow clock is internal 32 kHz RC oscillator. */
#define   SCKC_CR_OSCSEL_XTAL (0x1u << 3) /**< \brief (SCKC_CR) Slow clock is 32768 Hz oscillator. */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Secure Fuse Controller */
/* ============================================================================= */
/** \addtogroup SAMA5D4_SFC Secure Fuse Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Sfc hardware registers */
typedef struct {
  __O  uint32_t SFC_KR;       /**< \brief (Sfc Offset: 0x00) SFC Key Register */
  __IO uint32_t SFC_MR;       /**< \brief (Sfc Offset: 0X04) SFC Mode Register */
  __I  uint32_t Reserved1[2];
  __IO uint32_t SFC_IER;      /**< \brief (Sfc Offset: 0x10) SFC Interrupt Enable Register */
  __IO uint32_t SFC_IDR;      /**< \brief (Sfc Offset: 0x14) SFC Interrupt Disable Register */
  __I  uint32_t SFC_IMR;      /**< \brief (Sfc Offset: 0x18) SFC Interrupt Mask Register */
  __I  uint32_t SFC_SR;       /**< \brief (Sfc Offset: 0x1C) SFC Status Register */
  __IO uint32_t SFC_DR[24];   /**< \brief (Sfc Offset: 0x20) SFC Data Register */
} Sfc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SFC_KR : (SFC Offset: 0x00) SFC Key Register -------- */
#define SFC_KR_KEY_Pos 0
#define SFC_KR_KEY_Msk (0xffu << SFC_KR_KEY_Pos) /**< \brief (SFC_KR) Key Code */
#define SFC_KR_KEY(value) ((SFC_KR_KEY_Msk & ((value) << SFC_KR_KEY_Pos)))
/* -------- SFC_MR : (SFC Offset: 0X04) SFC Mode Register -------- */
#define SFC_MR_MSK (0x1u << 0) /**< \brief (SFC_MR) Mask Data Registers */
/* -------- SFC_IER : (SFC Offset: 0x10) SFC Interrupt Enable Register -------- */
#define SFC_IER_PGMC (0x1u << 0) /**< \brief (SFC_IER) Programming Sequence Completed Interrupt Enable */
#define SFC_IER_APLE (0x1u << 16) /**< \brief (SFC_IER) ATMEL Programming Lock Error Interrupt Enable */
#define SFC_IER_ACE (0x1u << 17) /**< \brief (SFC_IER) ATMEL Check Error Interrupt Enable */
/* -------- SFC_IDR : (SFC Offset: 0x14) SFC Interrupt Disable Register -------- */
#define SFC_IDR_PGMC (0x1u << 0) /**< \brief (SFC_IDR) Programming Sequence Completed Interrupt Disable */
#define SFC_IDR_APLE (0x1u << 16) /**< \brief (SFC_IDR) ATMEL Programming Lock Error Interrupt Disable */
#define SFC_IDR_ACE (0x1u << 17) /**< \brief (SFC_IDR) ATMEL Check Error Interrupt Disable */
/* -------- SFC_IMR : (SFC Offset: 0x18) SFC Interrupt Mask Register -------- */
#define SFC_IMR_PGMC (0x1u << 0) /**< \brief (SFC_IMR) Programming Sequence Completed Interrupt Mask */
#define SFC_IMR_APLE (0x1u << 16) /**< \brief (SFC_IMR) ATMEL Programming Lock Error Interrupt Mask */
#define SFC_IMR_ACE (0x1u << 17) /**< \brief (SFC_IMR) ATMEL Check Error Interrupt Mask */
/* -------- SFC_SR : (SFC Offset: 0x1C) SFC Status Register -------- */
#define SFC_SR_PGMC (0x1u << 0) /**< \brief (SFC_SR) Programming Sequence Completed */
#define SFC_SR_APLE (0x1u << 16) /**< \brief (SFC_SR) ATMEL Programming Lock Error */
#define SFC_SR_ACE (0x1u << 17) /**< \brief (SFC_SR) ATMEL Check Error */
/* -------- SFC_DR[24] : (SFC Offset: 0x20) SFC Data Register -------- */
#define SFC_DR_DATA_Pos 0
#define SFC_DR_DATA_Msk (0xffffffffu << SFC_DR_DATA_Pos) /**< \brief (SFC_DR[24]) Fuse Data */
#define SFC_DR_DATA(value) ((SFC_DR_DATA_Msk & ((value) << SFC_DR_DATA_Pos)))

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Special Function Registers */
/* ============================================================================= */
/** \addtogroup SAMA5D4_SFR Special Function Registers */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Sfr hardware registers */
typedef struct {
  __I  uint32_t Reserved1[4];
  __IO uint32_t SFR_OHCIICR;  /**< \brief (Sfr Offset: 0x10) OHCI Interrupt Configuration Register */
  __I  uint32_t SFR_OHCIISR;  /**< \brief (Sfr Offset: 0x14) OHCI Interrupt Status Register */
  __I  uint32_t Reserved2[4];
  __IO uint32_t SFR_SECURE;   /**< \brief (Sfr Offset: 0x28) Security Configuration Register */
  __I  uint32_t Reserved3[5];
  __IO uint32_t SFR_EBICFG;   /**< \brief (Sfr Offset: 0x40) EBI Configuration Register */
  __I  uint32_t Reserved4[2];
  __I  uint32_t SFR_SN0;      /**< \brief (Sfr Offset: 0x4C) Serial Number 0 Register */
  __I  uint32_t SFR_SN1;      /**< \brief (Sfr Offset: 0x50) Seriel Number 1 Register */
} Sfr;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SFR_OHCIICR : (SFR Offset: 0x10) OHCI Interrupt Configuration Register -------- */
#define SFR_OHCIICR_RES0 (0x1u << 0) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_RES1 (0x1u << 1) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_RES2 (0x1u << 2) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_ARIE (0x1u << 4) /**< \brief (SFR_OHCIICR) OHCI Asynchronous Resume Interrupt Enable */
#define SFR_OHCIICR_APPSTART (0x1u << 5) /**< \brief (SFR_OHCIICR) Reserved */
#define SFR_OHCIICR_UDPPUDIS (0x1u << 23) /**< \brief (SFR_OHCIICR) USB DEVICE PULL-UP DISABLE */
/* -------- SFR_OHCIISR : (SFR Offset: 0x14) OHCI Interrupt Status Register -------- */
#define SFR_OHCIISR_RIS0 (0x1u << 0) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 0 */
#define SFR_OHCIISR_RIS1 (0x1u << 1) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 1 */
#define SFR_OHCIISR_RIS2 (0x1u << 2) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 2 */
/* -------- SFR_SECURE : (SFR Offset: 0x28) Security Configuration Register -------- */
#define SFR_SECURE_ROM (0x1u << 0) /**< \brief (SFR_SECURE) Disable Access to ROM Code */
#define SFR_SECURE_FUSE (0x1u << 8) /**< \brief (SFR_SECURE) Disable Access to Fuse Controller */
/* -------- SFR_EBICFG : (SFR Offset: 0x40) EBI Configuration Register -------- */
#define SFR_EBICFG_DRIVE0_Pos 0
#define SFR_EBICFG_DRIVE0_Msk (0x3u << SFR_EBICFG_DRIVE0_Pos) /**< \brief (SFR_EBICFG) EBI Pins Drive Level */
#define   SFR_EBICFG_DRIVE0_LOW (0x0u << 0) /**< \brief (SFR_EBICFG) Low drive level */
#define   SFR_EBICFG_DRIVE0_MEDIUM (0x2u << 0) /**< \brief (SFR_EBICFG) Medium drive level */
#define   SFR_EBICFG_DRIVE0_HIGH (0x3u << 0) /**< \brief (SFR_EBICFG) High drive level */
#define SFR_EBICFG_PULL0_Pos 2
#define SFR_EBICFG_PULL0_Msk (0x3u << SFR_EBICFG_PULL0_Pos) /**< \brief (SFR_EBICFG) EBI Pins Pull Value */
#define   SFR_EBICFG_PULL0_UP (0x0u << 2) /**< \brief (SFR_EBICFG) Pull-up */
#define   SFR_EBICFG_PULL0_NONE (0x1u << 2) /**< \brief (SFR_EBICFG) No Pull */
#define   SFR_EBICFG_PULL0_DOWN (0x3u << 2) /**< \brief (SFR_EBICFG) Pull-down */
#define SFR_EBICFG_SCH0 (0x1u << 4) /**< \brief (SFR_EBICFG) EBI Pins Schmitt Trigger */
#define SFR_EBICFG_DRIVE1_Pos 8
#define SFR_EBICFG_DRIVE1_Msk (0x3u << SFR_EBICFG_DRIVE1_Pos) /**< \brief (SFR_EBICFG) EBI Pins Drive Level */
#define   SFR_EBICFG_DRIVE1_LOW (0x0u << 8) /**< \brief (SFR_EBICFG) Low drive level */
#define   SFR_EBICFG_DRIVE1_MEDIUM (0x2u << 8) /**< \brief (SFR_EBICFG) Medium drive level */
#define   SFR_EBICFG_DRIVE1_HIGH (0x3u << 8) /**< \brief (SFR_EBICFG) High drive level */
#define SFR_EBICFG_PULL1_Pos 10
#define SFR_EBICFG_PULL1_Msk (0x3u << SFR_EBICFG_PULL1_Pos) /**< \brief (SFR_EBICFG) EBI Pins Pull Value */
#define   SFR_EBICFG_PULL1_UP (0x0u << 10) /**< \brief (SFR_EBICFG) Pull-up */
#define   SFR_EBICFG_PULL1_NONE (0x1u << 10) /**< \brief (SFR_EBICFG) No Pull */
#define   SFR_EBICFG_PULL1_DOWN (0x3u << 10) /**< \brief (SFR_EBICFG) Pull-down */
#define SFR_EBICFG_SCH1 (0x1u << 12) /**< \brief (SFR_EBICFG) EBI Pins Schmitt Trigger */
#define SFR_EBICFG_BMS (0x1u << 16) /**< \brief (SFR_EBICFG) BMS Sampled Value (Read Only) */
#define   SFR_EBICFG_BMS_ROM (0x0u << 16) /**< \brief (SFR_EBICFG) Boot on ROM. */
#define   SFR_EBICFG_BMS_EBI (0x1u << 16) /**< \brief (SFR_EBICFG) Boot on EBI. */
/* -------- SFR_SN0 : (SFR Offset: 0x4C) Serial Number 0 Register -------- */
#define SFR_SN0_SN0_Pos 0
#define SFR_SN0_SN0_Msk (0xffffffffu << SFR_SN0_SN0_Pos) /**< \brief (SFR_SN0) Serial Number 0 */
/* -------- SFR_SN1 : (SFR Offset: 0x50) Seriel Number 1 Register -------- */
#define SFR_SN1_SN1_Pos 0
#define SFR_SN1_SN1_Msk (0xffffffu << SFR_SN1_SN1_Pos) /**< \brief (SFR_SN1) Serial Number 1 */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Serial Peripheral Interface */
/* ============================================================================= */
/** \addtogroup SAMA5D4_SPI Serial Peripheral Interface */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Spi hardware registers */
typedef struct {
  __O  uint32_t SPI_CR;        /**< \brief (Spi Offset: 0x00) Control Register */
  __IO uint32_t SPI_MR;        /**< \brief (Spi Offset: 0x04) Mode Register */
  __I  uint32_t SPI_RDR;       /**< \brief (Spi Offset: 0x08) Receive Data Register */
  __O  uint32_t SPI_TDR;       /**< \brief (Spi Offset: 0x0C) Transmit Data Register */
  __I  uint32_t SPI_SR;        /**< \brief (Spi Offset: 0x10) Status Register */
  __O  uint32_t SPI_IER;       /**< \brief (Spi Offset: 0x14) Interrupt Enable Register */
  __O  uint32_t SPI_IDR;       /**< \brief (Spi Offset: 0x18) Interrupt Disable Register */
  __I  uint32_t SPI_IMR;       /**< \brief (Spi Offset: 0x1C) Interrupt Mask Register */
  __I  uint32_t Reserved1[4];
  __IO uint32_t SPI_CSR[4];    /**< \brief (Spi Offset: 0x30) Chip Select Register */
  __I  uint32_t Reserved2[41];
  __IO uint32_t SPI_WPMR;      /**< \brief (Spi Offset: 0xE4) Write Protection Control Register */
  __I  uint32_t SPI_WPSR;      /**< \brief (Spi Offset: 0xE8) Write Protection Status Register */
} Spi;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SPI_CR : (SPI Offset: 0x00) Control Register -------- */
#define SPI_CR_SPIEN (0x1u << 0) /**< \brief (SPI_CR) SPI Enable */
#define SPI_CR_SPIDIS (0x1u << 1) /**< \brief (SPI_CR) SPI Disable */
#define SPI_CR_SWRST (0x1u << 7) /**< \brief (SPI_CR) SPI Software Reset */
#define SPI_CR_LASTXFER (0x1u << 24) /**< \brief (SPI_CR) Last Transfer */
/* -------- SPI_MR : (SPI Offset: 0x04) Mode Register -------- */
#define SPI_MR_MSTR (0x1u << 0) /**< \brief (SPI_MR) Master/Slave Mode */
#define SPI_MR_PS (0x1u << 1) /**< \brief (SPI_MR) Peripheral Select */
#define SPI_MR_PCSDEC (0x1u << 2) /**< \brief (SPI_MR) Chip Select Decode */
#define SPI_MR_MODFDIS (0x1u << 4) /**< \brief (SPI_MR) Mode Fault Detection */
#define SPI_MR_WDRBT (0x1u << 5) /**< \brief (SPI_MR) Wait Data Read Before Transfer */
#define SPI_MR_LLB (0x1u << 7) /**< \brief (SPI_MR) Local Loopback Enable */
#define SPI_MR_PCS_Pos 16
#define SPI_MR_PCS_Msk (0xfu << SPI_MR_PCS_Pos) /**< \brief (SPI_MR) Peripheral Chip Select */
#define SPI_MR_PCS(value) ((SPI_MR_PCS_Msk & ((value) << SPI_MR_PCS_Pos)))
#define SPI_MR_DLYBCS_Pos 24
#define SPI_MR_DLYBCS_Msk (0xffu << SPI_MR_DLYBCS_Pos) /**< \brief (SPI_MR) Delay Between Chip Selects */
#define SPI_MR_DLYBCS(value) ((SPI_MR_DLYBCS_Msk & ((value) << SPI_MR_DLYBCS_Pos)))
/* -------- SPI_RDR : (SPI Offset: 0x08) Receive Data Register -------- */
#define SPI_RDR_RD_Pos 0
#define SPI_RDR_RD_Msk (0xffffu << SPI_RDR_RD_Pos) /**< \brief (SPI_RDR) Receive Data */
#define SPI_RDR_PCS_Pos 16
#define SPI_RDR_PCS_Msk (0xfu << SPI_RDR_PCS_Pos) /**< \brief (SPI_RDR) Peripheral Chip Select */
/* -------- SPI_TDR : (SPI Offset: 0x0C) Transmit Data Register -------- */
#define SPI_TDR_TD_Pos 0
#define SPI_TDR_TD_Msk (0xffffu << SPI_TDR_TD_Pos) /**< \brief (SPI_TDR) Transmit Data */
#define SPI_TDR_TD(value) ((SPI_TDR_TD_Msk & ((value) << SPI_TDR_TD_Pos)))
#define SPI_TDR_PCS_Pos 16
#define SPI_TDR_PCS_Msk (0xfu << SPI_TDR_PCS_Pos) /**< \brief (SPI_TDR) Peripheral Chip Select */
#define SPI_TDR_PCS(value) ((SPI_TDR_PCS_Msk & ((value) << SPI_TDR_PCS_Pos)))
#define SPI_TDR_LASTXFER (0x1u << 24) /**< \brief (SPI_TDR) Last Transfer */
/* -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- */
#define SPI_SR_RDRF (0x1u << 0) /**< \brief (SPI_SR) Receive Data Register Full */
#define SPI_SR_TDRE (0x1u << 1) /**< \brief (SPI_SR) Transmit Data Register Empty */
#define SPI_SR_MODF (0x1u << 2) /**< \brief (SPI_SR) Mode Fault Error */
#define SPI_SR_OVRES (0x1u << 3) /**< \brief (SPI_SR) Overrun Error Status */
#define SPI_SR_NSSR (0x1u << 8) /**< \brief (SPI_SR) NSS Rising */
#define SPI_SR_TXEMPTY (0x1u << 9) /**< \brief (SPI_SR) Transmission Registers Empty */
#define SPI_SR_UNDES (0x1u << 10) /**< \brief (SPI_SR) Underrun Error Status (Slave Mode Only) */
#define SPI_SR_SPIENS (0x1u << 16) /**< \brief (SPI_SR) SPI Enable Status */
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
#define SPI_IER_RDRF (0x1u << 0) /**< \brief (SPI_IER) Receive Data Register Full Interrupt Enable */
#define SPI_IER_TDRE (0x1u << 1) /**< \brief (SPI_IER) SPI Transmit Data Register Empty Interrupt Enable */
#define SPI_IER_MODF (0x1u << 2) /**< \brief (SPI_IER) Mode Fault Error Interrupt Enable */
#define SPI_IER_OVRES (0x1u << 3) /**< \brief (SPI_IER) Overrun Error Interrupt Enable */
#define SPI_IER_NSSR (0x1u << 8) /**< \brief (SPI_IER) NSS Rising Interrupt Enable */
#define SPI_IER_TXEMPTY (0x1u << 9) /**< \brief (SPI_IER) Transmission Registers Empty Enable */
#define SPI_IER_UNDES (0x1u << 10) /**< \brief (SPI_IER) Underrun Error Interrupt Enable */
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
#define SPI_IDR_RDRF (0x1u << 0) /**< \brief (SPI_IDR) Receive Data Register Full Interrupt Disable */
#define SPI_IDR_TDRE (0x1u << 1) /**< \brief (SPI_IDR) SPI Transmit Data Register Empty Interrupt Disable */
#define SPI_IDR_MODF (0x1u << 2) /**< \brief (SPI_IDR) Mode Fault Error Interrupt Disable */
#define SPI_IDR_OVRES (0x1u << 3) /**< \brief (SPI_IDR) Overrun Error Interrupt Disable */
#define SPI_IDR_NSSR (0x1u << 8) /**< \brief (SPI_IDR) NSS Rising Interrupt Disable */
#define SPI_IDR_TXEMPTY (0x1u << 9) /**< \brief (SPI_IDR) Transmission Registers Empty Disable */
#define SPI_IDR_UNDES (0x1u << 10) /**< \brief (SPI_IDR) Underrun Error Interrupt Disable */
/* -------- SPI_IMR : (SPI Offset: 0x1C) Interrupt Mask Register -------- */
#define SPI_IMR_RDRF (0x1u << 0) /**< \brief (SPI_IMR) Receive Data Register Full Interrupt Mask */
#define SPI_IMR_TDRE (0x1u << 1) /**< \brief (SPI_IMR) SPI Transmit Data Register Empty Interrupt Mask */
#define SPI_IMR_MODF (0x1u << 2) /**< \brief (SPI_IMR) Mode Fault Error Interrupt Mask */
#define SPI_IMR_OVRES (0x1u << 3) /**< \brief (SPI_IMR) Overrun Error Interrupt Mask */
#define SPI_IMR_NSSR (0x1u << 8) /**< \brief (SPI_IMR) NSS Rising Interrupt Mask */
#define SPI_IMR_TXEMPTY (0x1u << 9) /**< \brief (SPI_IMR) Transmission Registers Empty Mask */
#define SPI_IMR_UNDES (0x1u << 10) /**< \brief (SPI_IMR) Underrun Error Interrupt Mask */
/* -------- SPI_CSR[4] : (SPI Offset: 0x30) Chip Select Register -------- */
#define SPI_CSR_CPOL (0x1u << 0) /**< \brief (SPI_CSR[4]) Clock Polarity */
#define SPI_CSR_NCPHA (0x1u << 1) /**< \brief (SPI_CSR[4]) Clock Phase */
#define SPI_CSR_CSNAAT (0x1u << 2) /**< \brief (SPI_CSR[4]) Chip Select Not Active After Transfer (Ignored if CSAAT = 1) */
#define SPI_CSR_CSAAT (0x1u << 3) /**< \brief (SPI_CSR[4]) Chip Select Active After Transfer */
#define SPI_CSR_BITS_Pos 4
#define SPI_CSR_BITS_Msk (0xfu << SPI_CSR_BITS_Pos) /**< \brief (SPI_CSR[4]) Bits Per Transfer */
#define   SPI_CSR_BITS_8_BIT (0x0u << 4) /**< \brief (SPI_CSR[4]) 8 bits for transfer */
#define   SPI_CSR_BITS_9_BIT (0x1u << 4) /**< \brief (SPI_CSR[4]) 9 bits for transfer */
#define   SPI_CSR_BITS_10_BIT (0x2u << 4) /**< \brief (SPI_CSR[4]) 10 bits for transfer */
#define   SPI_CSR_BITS_11_BIT (0x3u << 4) /**< \brief (SPI_CSR[4]) 11 bits for transfer */
#define   SPI_CSR_BITS_12_BIT (0x4u << 4) /**< \brief (SPI_CSR[4]) 12 bits for transfer */
#define   SPI_CSR_BITS_13_BIT (0x5u << 4) /**< \brief (SPI_CSR[4]) 13 bits for transfer */
#define   SPI_CSR_BITS_14_BIT (0x6u << 4) /**< \brief (SPI_CSR[4]) 14 bits for transfer */
#define   SPI_CSR_BITS_15_BIT (0x7u << 4) /**< \brief (SPI_CSR[4]) 15 bits for transfer */
#define   SPI_CSR_BITS_16_BIT (0x8u << 4) /**< \brief (SPI_CSR[4]) 16 bits for transfer */
#define SPI_CSR_SCBR_Pos 8
#define SPI_CSR_SCBR_Msk (0xffu << SPI_CSR_SCBR_Pos) /**< \brief (SPI_CSR[4]) Serial Clock Baud Rate */
#define SPI_CSR_SCBR(value) ((SPI_CSR_SCBR_Msk & ((value) << SPI_CSR_SCBR_Pos)))
#define SPI_CSR_DLYBS_Pos 16
#define SPI_CSR_DLYBS_Msk (0xffu << SPI_CSR_DLYBS_Pos) /**< \brief (SPI_CSR[4]) Delay Before SPCK */
#define SPI_CSR_DLYBS(value) ((SPI_CSR_DLYBS_Msk & ((value) << SPI_CSR_DLYBS_Pos)))
#define SPI_CSR_DLYBCT_Pos 24
#define SPI_CSR_DLYBCT_Msk (0xffu << SPI_CSR_DLYBCT_Pos) /**< \brief (SPI_CSR[4]) Delay Between Consecutive Transfers */
#define SPI_CSR_DLYBCT(value) ((SPI_CSR_DLYBCT_Msk & ((value) << SPI_CSR_DLYBCT_Pos)))
/* -------- SPI_WPMR : (SPI Offset: 0xE4) Write Protection Control Register -------- */
#define SPI_WPMR_WPEN (0x1u << 0) /**< \brief (SPI_WPMR) Write Protect Enable */
#define SPI_WPMR_WPKEY_Pos 8
#define SPI_WPMR_WPKEY_Msk (0xffffffu << SPI_WPMR_WPKEY_Pos) /**< \brief (SPI_WPMR) Write Protect Key */
#define   SPI_WPMR_WPKEY_PASSWD (0x535049u << 8) /**< \brief (SPI_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */
/* -------- SPI_WPSR : (SPI Offset: 0xE8) Write Protection Status Register -------- */
#define SPI_WPSR_WPVS (0x1u << 0) /**< \brief (SPI_WPSR) Write Protection Violation Status */
#define SPI_WPSR_WPVSRC_Pos 8
#define SPI_WPSR_WPVSRC_Msk (0xffu << SPI_WPSR_WPVSRC_Pos) /**< \brief (SPI_WPSR) Write Protection Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Timer Counter */
/* ============================================================================= */
/** \addtogroup SAMA5D4_TC Timer Counter */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief TcChannel hardware registers */
typedef struct {
  __O  uint32_t TC_CCR;       /**< \brief (TcChannel Offset: 0x0) Channel Control Register */
  __IO uint32_t TC_CMR;       /**< \brief (TcChannel Offset: 0x4) Channel Mode Register */
  __IO uint32_t TC_SMMR;      /**< \brief (TcChannel Offset: 0x8) Stepper Motor Mode Register */
  __I  uint32_t TC_RAB;       /**< \brief (TcChannel Offset: 0xC) Register AB */
  __I  uint32_t TC_CV;        /**< \brief (TcChannel Offset: 0x10) Counter Value */
  __IO uint32_t TC_RA;        /**< \brief (TcChannel Offset: 0x14) Register A */
  __IO uint32_t TC_RB;        /**< \brief (TcChannel Offset: 0x18) Register B */
  __IO uint32_t TC_RC;        /**< \brief (TcChannel Offset: 0x1C) Register C */
  __I  uint32_t TC_SR;        /**< \brief (TcChannel Offset: 0x20) Status Register */
  __O  uint32_t TC_IER;       /**< \brief (TcChannel Offset: 0x24) Interrupt Enable Register */
  __O  uint32_t TC_IDR;       /**< \brief (TcChannel Offset: 0x28) Interrupt Disable Register */
  __I  uint32_t TC_IMR;       /**< \brief (TcChannel Offset: 0x2C) Interrupt Mask Register */
  __IO uint32_t TC_EMR;       /**< \brief (TcChannel Offset: 0x30) Extended Mode Register */
  __I  uint32_t Reserved1[3];
} TcChannel;
/** \brief Tc hardware registers */
#define TCCHANNEL_NUMBER 3
typedef struct {
       TcChannel TC_CHANNEL[TCCHANNEL_NUMBER]; /**< \brief (Tc Offset: 0x0) channel = 0 .. 2 */
  __O  uint32_t  TC_BCR;                       /**< \brief (Tc Offset: 0xC0) Block Control Register */
  __IO uint32_t  TC_BMR;                       /**< \brief (Tc Offset: 0xC4) Block Mode Register */
  __O  uint32_t  TC_QIER;                      /**< \brief (Tc Offset: 0xC8) QDEC Interrupt Enable Register */
  __O  uint32_t  TC_QIDR;                      /**< \brief (Tc Offset: 0xCC) QDEC Interrupt Disable Register */
  __I  uint32_t  TC_QIMR;                      /**< \brief (Tc Offset: 0xD0) QDEC Interrupt Mask Register */
  __I  uint32_t  TC_QISR;                      /**< \brief (Tc Offset: 0xD4) QDEC Interrupt Status Register */
  __IO uint32_t  TC_FMR;                       /**< \brief (Tc Offset: 0xD8) Fault Mode Register */
  __I  uint32_t  Reserved1[2];
  __IO uint32_t  TC_WPMR;                      /**< \brief (Tc Offset: 0xE4) Write Protect Mode Register */
} Tc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- TC_CCR : (TC Offset: N/A) Channel Control Register -------- */
#define TC_CCR_CLKEN (0x1u << 0) /**< \brief (TC_CCR) Counter Clock Enable Command */
#define TC_CCR_CLKDIS (0x1u << 1) /**< \brief (TC_CCR) Counter Clock Disable Command */
#define TC_CCR_SWTRG (0x1u << 2) /**< \brief (TC_CCR) Software Trigger Command */
/* -------- TC_CMR : (TC Offset: N/A) Channel Mode Register -------- */
#define TC_CMR_TCCLKS_Pos 0
#define TC_CMR_TCCLKS_Msk (0x7u << TC_CMR_TCCLKS_Pos) /**< \brief (TC_CMR) Clock Selection */
#define   TC_CMR_TCCLKS_TIMER_CLOCK1 (0x0u << 0) /**< \brief (TC_CMR) Clock selected: TCLK1 */
#define   TC_CMR_TCCLKS_TIMER_CLOCK2 (0x1u << 0) /**< \brief (TC_CMR) Clock selected: TCLK2 */
#define   TC_CMR_TCCLKS_TIMER_CLOCK3 (0x2u << 0) /**< \brief (TC_CMR) Clock selected: TCLK3 */
#define   TC_CMR_TCCLKS_TIMER_CLOCK4 (0x3u << 0) /**< \brief (TC_CMR) Clock selected: TCLK4 */
#define   TC_CMR_TCCLKS_TIMER_CLOCK5 (0x4u << 0) /**< \brief (TC_CMR) Clock selected: TCLK5 */
#define   TC_CMR_TCCLKS_XC0 (0x5u << 0) /**< \brief (TC_CMR) Clock selected: XC0 */
#define   TC_CMR_TCCLKS_XC1 (0x6u << 0) /**< \brief (TC_CMR) Clock selected: XC1 */
#define   TC_CMR_TCCLKS_XC2 (0x7u << 0) /**< \brief (TC_CMR) Clock selected: XC2 */
#define TC_CMR_CLKI (0x1u << 3) /**< \brief (TC_CMR) Clock Invert */
#define TC_CMR_BURST_Pos 4
#define TC_CMR_BURST_Msk (0x3u << TC_CMR_BURST_Pos) /**< \brief (TC_CMR) Burst Signal Selection */
#define   TC_CMR_BURST_NONE (0x0u << 4) /**< \brief (TC_CMR) The clock is not gated by an external signal. */
#define   TC_CMR_BURST_XC0 (0x1u << 4) /**< \brief (TC_CMR) XC0 is ANDed with the selected clock. */
#define   TC_CMR_BURST_XC1 (0x2u << 4) /**< \brief (TC_CMR) XC1 is ANDed with the selected clock. */
#define   TC_CMR_BURST_XC2 (0x3u << 4) /**< \brief (TC_CMR) XC2 is ANDed with the selected clock. */
#define TC_CMR_LDBSTOP (0x1u << 6) /**< \brief (TC_CMR) Counter Clock Stopped with RB Loading */
#define TC_CMR_LDBDIS (0x1u << 7) /**< \brief (TC_CMR) Counter Clock Disable with RB Loading */
#define TC_CMR_ETRGEDG_Pos 8
#define TC_CMR_ETRGEDG_Msk (0x3u << TC_CMR_ETRGEDG_Pos) /**< \brief (TC_CMR) External Trigger Edge Selection */
#define   TC_CMR_ETRGEDG_NONE (0x0u << 8) /**< \brief (TC_CMR) The clock is not gated by an external signal. */
#define   TC_CMR_ETRGEDG_RISING (0x1u << 8) /**< \brief (TC_CMR) Rising edge */
#define   TC_CMR_ETRGEDG_FALLING (0x2u << 8) /**< \brief (TC_CMR) Falling edge */
#define   TC_CMR_ETRGEDG_EDGE (0x3u << 8) /**< \brief (TC_CMR) Each edge */
#define TC_CMR_ABETRG (0x1u << 10) /**< \brief (TC_CMR) TIOA or TIOB External Trigger Selection */
#define TC_CMR_CPCTRG (0x1u << 14) /**< \brief (TC_CMR) RC Compare Trigger Enable */
#define TC_CMR_WAVE (0x1u << 15) /**< \brief (TC_CMR) Waveform Mode */
#define TC_CMR_LDRA_Pos 16
#define TC_CMR_LDRA_Msk (0x3u << TC_CMR_LDRA_Pos) /**< \brief (TC_CMR) RA Loading Edge Selection */
#define   TC_CMR_LDRA_NONE (0x0u << 16) /**< \brief (TC_CMR) None */
#define   TC_CMR_LDRA_RISING (0x1u << 16) /**< \brief (TC_CMR) Rising edge of TIOA */
#define   TC_CMR_LDRA_FALLING (0x2u << 16) /**< \brief (TC_CMR) Falling edge of TIOA */
#define   TC_CMR_LDRA_EDGE (0x3u << 16) /**< \brief (TC_CMR) Each edge of TIOA */
#define TC_CMR_LDRB_Pos 18
#define TC_CMR_LDRB_Msk (0x3u << TC_CMR_LDRB_Pos) /**< \brief (TC_CMR) RB Loading Edge Selection */
#define   TC_CMR_LDRB_NONE (0x0u << 18) /**< \brief (TC_CMR) None */
#define   TC_CMR_LDRB_RISING (0x1u << 18) /**< \brief (TC_CMR) Rising edge of TIOA */
#define   TC_CMR_LDRB_FALLING (0x2u << 18) /**< \brief (TC_CMR) Falling edge of TIOA */
#define   TC_CMR_LDRB_EDGE (0x3u << 18) /**< \brief (TC_CMR) Each edge of TIOA */
#define TC_CMR_SBSMPLR_Pos 20
#define TC_CMR_SBSMPLR_Msk (0x7u << TC_CMR_SBSMPLR_Pos) /**< \brief (TC_CMR) Loading Edge Subsampling Ratio */
#define   TC_CMR_SBSMPLR_ONE (0x0u << 20) /**< \brief (TC_CMR) Load a Capture Register each selected edge */
#define   TC_CMR_SBSMPLR_HALF (0x1u << 20) /**< \brief (TC_CMR) Load a Capture Register every 2 selected edges */
#define   TC_CMR_SBSMPLR_FOURTH (0x2u << 20) /**< \brief (TC_CMR) Load a Capture Register every 4 selected edges */
#define   TC_CMR_SBSMPLR_EIGHTH (0x3u << 20) /**< \brief (TC_CMR) Load a Capture Register every 8 selected edges */
#define   TC_CMR_SBSMPLR_SIXTEENTH (0x4u << 20) /**< \brief (TC_CMR) Load a Capture Register every 16 selected edges */
#define TC_CMR_CPCSTOP (0x1u << 6) /**< \brief (TC_CMR) Counter Clock Stopped with RC Compare */
#define TC_CMR_CPCDIS (0x1u << 7) /**< \brief (TC_CMR) Counter Clock Disable with RC Compare */
#define TC_CMR_EEVTEDG_Pos 8
#define TC_CMR_EEVTEDG_Msk (0x3u << TC_CMR_EEVTEDG_Pos) /**< \brief (TC_CMR) External Event Edge Selection */
#define   TC_CMR_EEVTEDG_NONE (0x0u << 8) /**< \brief (TC_CMR) None */
#define   TC_CMR_EEVTEDG_RISING (0x1u << 8) /**< \brief (TC_CMR) Rising edge */
#define   TC_CMR_EEVTEDG_FALLING (0x2u << 8) /**< \brief (TC_CMR) Falling edge */
#define   TC_CMR_EEVTEDG_EDGE (0x3u << 8) /**< \brief (TC_CMR) Each edge */
#define TC_CMR_EEVT_Pos 10
#define TC_CMR_EEVT_Msk (0x3u << TC_CMR_EEVT_Pos) /**< \brief (TC_CMR) External Event Selection */
#define   TC_CMR_EEVT_TIOB (0x0u << 10) /**< \brief (TC_CMR) TIOB */
#define   TC_CMR_EEVT_XC0 (0x1u << 10) /**< \brief (TC_CMR) XC0 */
#define   TC_CMR_EEVT_XC1 (0x2u << 10) /**< \brief (TC_CMR) XC1 */
#define   TC_CMR_EEVT_XC2 (0x3u << 10) /**< \brief (TC_CMR) XC2 */
#define TC_CMR_ENETRG (0x1u << 12) /**< \brief (TC_CMR) External Event Trigger Enable */
#define TC_CMR_WAVSEL_Pos 13
#define TC_CMR_WAVSEL_Msk (0x3u << TC_CMR_WAVSEL_Pos) /**< \brief (TC_CMR) Waveform Selection */
#define   TC_CMR_WAVSEL_UP (0x0u << 13) /**< \brief (TC_CMR) UP mode without automatic trigger on RC Compare */
#define   TC_CMR_WAVSEL_UPDOWN (0x1u << 13) /**< \brief (TC_CMR) UPDOWN mode without automatic trigger on RC Compare */
#define   TC_CMR_WAVSEL_UP_RC (0x2u << 13) /**< \brief (TC_CMR) UP mode with automatic trigger on RC Compare */
#define   TC_CMR_WAVSEL_UPDOWN_RC (0x3u << 13) /**< \brief (TC_CMR) UPDOWN mode with automatic trigger on RC Compare */
#define TC_CMR_ACPA_Pos 16
#define TC_CMR_ACPA_Msk (0x3u << TC_CMR_ACPA_Pos) /**< \brief (TC_CMR) RA Compare Effect on TIOA */
#define   TC_CMR_ACPA_NONE (0x0u << 16) /**< \brief (TC_CMR) None */
#define   TC_CMR_ACPA_SET (0x1u << 16) /**< \brief (TC_CMR) Set */
#define   TC_CMR_ACPA_CLEAR (0x2u << 16) /**< \brief (TC_CMR) Clear */
#define   TC_CMR_ACPA_TOGGLE (0x3u << 16) /**< \brief (TC_CMR) Toggle */
#define TC_CMR_ACPC_Pos 18
#define TC_CMR_ACPC_Msk (0x3u << TC_CMR_ACPC_Pos) /**< \brief (TC_CMR) RC Compare Effect on TIOA */
#define   TC_CMR_ACPC_NONE (0x0u << 18) /**< \brief (TC_CMR) None */
#define   TC_CMR_ACPC_SET (0x1u << 18) /**< \brief (TC_CMR) Set */
#define   TC_CMR_ACPC_CLEAR (0x2u << 18) /**< \brief (TC_CMR) Clear */
#define   TC_CMR_ACPC_TOGGLE (0x3u << 18) /**< \brief (TC_CMR) Toggle */
#define TC_CMR_AEEVT_Pos 20
#define TC_CMR_AEEVT_Msk (0x3u << TC_CMR_AEEVT_Pos) /**< \brief (TC_CMR) External Event Effect on TIOA */
#define   TC_CMR_AEEVT_NONE (0x0u << 20) /**< \brief (TC_CMR) None */
#define   TC_CMR_AEEVT_SET (0x1u << 20) /**< \brief (TC_CMR) Set */
#define   TC_CMR_AEEVT_CLEAR (0x2u << 20) /**< \brief (TC_CMR) Clear */
#define   TC_CMR_AEEVT_TOGGLE (0x3u << 20) /**< \brief (TC_CMR) Toggle */
#define TC_CMR_ASWTRG_Pos 22
#define TC_CMR_ASWTRG_Msk (0x3u << TC_CMR_ASWTRG_Pos) /**< \brief (TC_CMR) Software Trigger Effect on TIOA */
#define   TC_CMR_ASWTRG_NONE (0x0u << 22) /**< \brief (TC_CMR) None */
#define   TC_CMR_ASWTRG_SET (0x1u << 22) /**< \brief (TC_CMR) Set */
#define   TC_CMR_ASWTRG_CLEAR (0x2u << 22) /**< \brief (TC_CMR) Clear */
#define   TC_CMR_ASWTRG_TOGGLE (0x3u << 22) /**< \brief (TC_CMR) Toggle */
#define TC_CMR_BCPB_Pos 24
#define TC_CMR_BCPB_Msk (0x3u << TC_CMR_BCPB_Pos) /**< \brief (TC_CMR) RB Compare Effect on TIOB */
#define   TC_CMR_BCPB_NONE (0x0u << 24) /**< \brief (TC_CMR) None */
#define   TC_CMR_BCPB_SET (0x1u << 24) /**< \brief (TC_CMR) Set */
#define   TC_CMR_BCPB_CLEAR (0x2u << 24) /**< \brief (TC_CMR) Clear */
#define   TC_CMR_BCPB_TOGGLE (0x3u << 24) /**< \brief (TC_CMR) Toggle */
#define TC_CMR_BCPC_Pos 26
#define TC_CMR_BCPC_Msk (0x3u << TC_CMR_BCPC_Pos) /**< \brief (TC_CMR) RC Compare Effect on TIOB */
#define   TC_CMR_BCPC_NONE (0x0u << 26) /**< \brief (TC_CMR) None */
#define   TC_CMR_BCPC_SET (0x1u << 26) /**< \brief (TC_CMR) Set */
#define   TC_CMR_BCPC_CLEAR (0x2u << 26) /**< \brief (TC_CMR) Clear */
#define   TC_CMR_BCPC_TOGGLE (0x3u << 26) /**< \brief (TC_CMR) Toggle */
#define TC_CMR_BEEVT_Pos 28
#define TC_CMR_BEEVT_Msk (0x3u << TC_CMR_BEEVT_Pos) /**< \brief (TC_CMR) External Event Effect on TIOB */
#define   TC_CMR_BEEVT_NONE (0x0u << 28) /**< \brief (TC_CMR) None */
#define   TC_CMR_BEEVT_SET (0x1u << 28) /**< \brief (TC_CMR) Set */
#define   TC_CMR_BEEVT_CLEAR (0x2u << 28) /**< \brief (TC_CMR) Clear */
#define   TC_CMR_BEEVT_TOGGLE (0x3u << 28) /**< \brief (TC_CMR) Toggle */
#define TC_CMR_BSWTRG_Pos 30
#define TC_CMR_BSWTRG_Msk (0x3u << TC_CMR_BSWTRG_Pos) /**< \brief (TC_CMR) Software Trigger Effect on TIOB */
#define   TC_CMR_BSWTRG_NONE (0x0u << 30) /**< \brief (TC_CMR) None */
#define   TC_CMR_BSWTRG_SET (0x1u << 30) /**< \brief (TC_CMR) Set */
#define   TC_CMR_BSWTRG_CLEAR (0x2u << 30) /**< \brief (TC_CMR) Clear */
#define   TC_CMR_BSWTRG_TOGGLE (0x3u << 30) /**< \brief (TC_CMR) Toggle */
/* -------- TC_SMMR : (TC Offset: N/A) Stepper Motor Mode Register -------- */
#define TC_SMMR_GCEN (0x1u << 0) /**< \brief (TC_SMMR) Gray Count Enable */
#define TC_SMMR_DOWN (0x1u << 1) /**< \brief (TC_SMMR) DOWN Count */
/* -------- TC_RAB : (TC Offset: N/A) Register AB -------- */
#define TC_RAB_RAB_Pos 0
#define TC_RAB_RAB_Msk (0xffffffffu << TC_RAB_RAB_Pos) /**< \brief (TC_RAB) Register A or Register B */
/* -------- TC_CV : (TC Offset: N/A) Counter Value -------- */
#define TC_CV_CV_Pos 0
#define TC_CV_CV_Msk (0xffffffffu << TC_CV_CV_Pos) /**< \brief (TC_CV) Counter Value */
/* -------- TC_RA : (TC Offset: N/A) Register A -------- */
#define TC_RA_RA_Pos 0
#define TC_RA_RA_Msk (0xffffffffu << TC_RA_RA_Pos) /**< \brief (TC_RA) Register A */
#define TC_RA_RA(value) ((TC_RA_RA_Msk & ((value) << TC_RA_RA_Pos)))
/* -------- TC_RB : (TC Offset: N/A) Register B -------- */
#define TC_RB_RB_Pos 0
#define TC_RB_RB_Msk (0xffffffffu << TC_RB_RB_Pos) /**< \brief (TC_RB) Register B */
#define TC_RB_RB(value) ((TC_RB_RB_Msk & ((value) << TC_RB_RB_Pos)))
/* -------- TC_RC : (TC Offset: N/A) Register C -------- */
#define TC_RC_RC_Pos 0
#define TC_RC_RC_Msk (0xffffffffu << TC_RC_RC_Pos) /**< \brief (TC_RC) Register C */
#define TC_RC_RC(value) ((TC_RC_RC_Msk & ((value) << TC_RC_RC_Pos)))
/* -------- TC_SR : (TC Offset: N/A) Status Register -------- */
#define TC_SR_COVFS (0x1u << 0) /**< \brief (TC_SR) Counter Overflow Status */
#define TC_SR_LOVRS (0x1u << 1) /**< \brief (TC_SR) Load Overrun Status */
#define TC_SR_CPAS (0x1u << 2) /**< \brief (TC_SR) RA Compare Status */
#define TC_SR_CPBS (0x1u << 3) /**< \brief (TC_SR) RB Compare Status */
#define TC_SR_CPCS (0x1u << 4) /**< \brief (TC_SR) RC Compare Status */
#define TC_SR_LDRAS (0x1u << 5) /**< \brief (TC_SR) RA Loading Status */
#define TC_SR_LDRBS (0x1u << 6) /**< \brief (TC_SR) RB Loading Status */
#define TC_SR_ETRGS (0x1u << 7) /**< \brief (TC_SR) External Trigger Status */
#define TC_SR_CLKSTA (0x1u << 16) /**< \brief (TC_SR) Clock Enabling Status */
#define TC_SR_MTIOA (0x1u << 17) /**< \brief (TC_SR) TIOA Mirror */
#define TC_SR_MTIOB (0x1u << 18) /**< \brief (TC_SR) TIOB Mirror */
/* -------- TC_IER : (TC Offset: N/A) Interrupt Enable Register -------- */
#define TC_IER_COVFS (0x1u << 0) /**< \brief (TC_IER) Counter Overflow */
#define TC_IER_LOVRS (0x1u << 1) /**< \brief (TC_IER) Load Overrun */
#define TC_IER_CPAS (0x1u << 2) /**< \brief (TC_IER) RA Compare */
#define TC_IER_CPBS (0x1u << 3) /**< \brief (TC_IER) RB Compare */
#define TC_IER_CPCS (0x1u << 4) /**< \brief (TC_IER) RC Compare */
#define TC_IER_LDRAS (0x1u << 5) /**< \brief (TC_IER) RA Loading */
#define TC_IER_LDRBS (0x1u << 6) /**< \brief (TC_IER) RB Loading */
#define TC_IER_ETRGS (0x1u << 7) /**< \brief (TC_IER) External Trigger */
/* -------- TC_IDR : (TC Offset: N/A) Interrupt Disable Register -------- */
#define TC_IDR_COVFS (0x1u << 0) /**< \brief (TC_IDR) Counter Overflow */
#define TC_IDR_LOVRS (0x1u << 1) /**< \brief (TC_IDR) Load Overrun */
#define TC_IDR_CPAS (0x1u << 2) /**< \brief (TC_IDR) RA Compare */
#define TC_IDR_CPBS (0x1u << 3) /**< \brief (TC_IDR) RB Compare */
#define TC_IDR_CPCS (0x1u << 4) /**< \brief (TC_IDR) RC Compare */
#define TC_IDR_LDRAS (0x1u << 5) /**< \brief (TC_IDR) RA Loading */
#define TC_IDR_LDRBS (0x1u << 6) /**< \brief (TC_IDR) RB Loading */
#define TC_IDR_ETRGS (0x1u << 7) /**< \brief (TC_IDR) External Trigger */
/* -------- TC_IMR : (TC Offset: N/A) Interrupt Mask Register -------- */
#define TC_IMR_COVFS (0x1u << 0) /**< \brief (TC_IMR) Counter Overflow */
#define TC_IMR_LOVRS (0x1u << 1) /**< \brief (TC_IMR) Load Overrun */
#define TC_IMR_CPAS (0x1u << 2) /**< \brief (TC_IMR) RA Compare */
#define TC_IMR_CPBS (0x1u << 3) /**< \brief (TC_IMR) RB Compare */
#define TC_IMR_CPCS (0x1u << 4) /**< \brief (TC_IMR) RC Compare */
#define TC_IMR_LDRAS (0x1u << 5) /**< \brief (TC_IMR) RA Loading */
#define TC_IMR_LDRBS (0x1u << 6) /**< \brief (TC_IMR) RB Loading */
#define TC_IMR_ETRGS (0x1u << 7) /**< \brief (TC_IMR) External Trigger */
/* -------- TC_EMR : (TC Offset: N/A) Extended Mode Register -------- */
#define TC_EMR_TRIGSRCA_Pos 0
#define TC_EMR_TRIGSRCA_Msk (0x3u << TC_EMR_TRIGSRCA_Pos) /**< \brief (TC_EMR) TRIGger SouRCe for input A */
#define   TC_EMR_TRIGSRCA_EXTERNAL_TIOAx (0x0u << 0) /**< \brief (TC_EMR) the trigger/capture input A is driven by external pin TIOAx */
#define   TC_EMR_TRIGSRCA_PWMx (0x1u << 0) /**< \brief (TC_EMR) the trigger/capture input A is driven internally by PWMx */
#define TC_EMR_TRIGSRCB_Pos 4
#define TC_EMR_TRIGSRCB_Msk (0x3u << TC_EMR_TRIGSRCB_Pos) /**< \brief (TC_EMR) TRIGger SouRCe for input B */
#define   TC_EMR_TRIGSRCB_EXTERNAL_TIOBx (0x0u << 4) /**< \brief (TC_EMR) the trigger/capture input B is driven by external pin TIOBx */
#define   TC_EMR_TRIGSRCB_PWMx (0x1u << 4) /**< \brief (TC_EMR) the trigger/capture input B is driven internally by PWMx */
#define TC_EMR_NODIVCLK (0x1u << 8) /**< \brief (TC_EMR) NO DIVided CLocK */
/* -------- TC_BCR : (TC Offset: 0xC0) Block Control Register -------- */
#define TC_BCR_SYNC (0x1u << 0) /**< \brief (TC_BCR) Synchro Command */
/* -------- TC_BMR : (TC Offset: 0xC4) Block Mode Register -------- */
#define TC_BMR_TC0XC0S_Pos 0
#define TC_BMR_TC0XC0S_Msk (0x3u << TC_BMR_TC0XC0S_Pos) /**< \brief (TC_BMR) External Clock Signal 0 Selection */
#define   TC_BMR_TC0XC0S_TCLK0 (0x0u << 0) /**< \brief (TC_BMR) Signal connected to XC0: TCLK0 */
#define   TC_BMR_TC0XC0S_TIOA1 (0x2u << 0) /**< \brief (TC_BMR) Signal connected to XC0: TIOA1 */
#define   TC_BMR_TC0XC0S_TIOA2 (0x3u << 0) /**< \brief (TC_BMR) Signal connected to XC0: TIOA2 */
#define TC_BMR_TC1XC1S_Pos 2
#define TC_BMR_TC1XC1S_Msk (0x3u << TC_BMR_TC1XC1S_Pos) /**< \brief (TC_BMR) External Clock Signal 1 Selection */
#define   TC_BMR_TC1XC1S_TCLK1 (0x0u << 2) /**< \brief (TC_BMR) Signal connected to XC1: TCLK1 */
#define   TC_BMR_TC1XC1S_TIOA0 (0x2u << 2) /**< \brief (TC_BMR) Signal connected to XC1: TIOA0 */
#define   TC_BMR_TC1XC1S_TIOA2 (0x3u << 2) /**< \brief (TC_BMR) Signal connected to XC1: TIOA2 */
#define TC_BMR_TC2XC2S_Pos 4
#define TC_BMR_TC2XC2S_Msk (0x3u << TC_BMR_TC2XC2S_Pos) /**< \brief (TC_BMR) External Clock Signal 2 Selection */
#define   TC_BMR_TC2XC2S_TCLK2 (0x0u << 4) /**< \brief (TC_BMR) Signal connected to XC2: TCLK2 */
#define   TC_BMR_TC2XC2S_TIOA1 (0x2u << 4) /**< \brief (TC_BMR) Signal connected to XC2: TIOA1 */
#define   TC_BMR_TC2XC2S_TIOA2 (0x3u << 4) /**< \brief (TC_BMR) Signal connected to XC2: TIOA2 */
#define TC_BMR_QDEN (0x1u << 8) /**< \brief (TC_BMR) Quadrature Decoder ENabled */
#define TC_BMR_POSEN (0x1u << 9) /**< \brief (TC_BMR) POSition ENabled */
#define TC_BMR_SPEEDEN (0x1u << 10) /**< \brief (TC_BMR) SPEED ENabled */
#define TC_BMR_QDTRANS (0x1u << 11) /**< \brief (TC_BMR) Quadrature Decoding TRANSparent */
#define TC_BMR_EDGPHA (0x1u << 12) /**< \brief (TC_BMR) EDGe on PHA count mode */
#define TC_BMR_INVA (0x1u << 13) /**< \brief (TC_BMR) INVerted phA */
#define TC_BMR_INVB (0x1u << 14) /**< \brief (TC_BMR) INVerted phB */
#define TC_BMR_INVIDX (0x1u << 15) /**< \brief (TC_BMR) INVerted InDeX */
#define TC_BMR_SWAP (0x1u << 16) /**< \brief (TC_BMR) SWAP PHA and PHB */
#define TC_BMR_IDXPHB (0x1u << 17) /**< \brief (TC_BMR) InDeX pin is PHB pin */
#define TC_BMR_FILTER (0x1u << 19) /**< \brief (TC_BMR)  */
#define TC_BMR_MAXFILT_Pos 20
#define TC_BMR_MAXFILT_Msk (0x3fu << TC_BMR_MAXFILT_Pos) /**< \brief (TC_BMR) MAXimum FILTer */
#define TC_BMR_MAXFILT(value) ((TC_BMR_MAXFILT_Msk & ((value) << TC_BMR_MAXFILT_Pos)))
/* -------- TC_QIER : (TC Offset: 0xC8) QDEC Interrupt Enable Register -------- */
#define TC_QIER_IDX (0x1u << 0) /**< \brief (TC_QIER) InDeX */
#define TC_QIER_DIRCHG (0x1u << 1) /**< \brief (TC_QIER) DIRection CHanGe */
#define TC_QIER_QERR (0x1u << 2) /**< \brief (TC_QIER) Quadrature ERRor */
/* -------- TC_QIDR : (TC Offset: 0xCC) QDEC Interrupt Disable Register -------- */
#define TC_QIDR_IDX (0x1u << 0) /**< \brief (TC_QIDR) InDeX */
#define TC_QIDR_DIRCHG (0x1u << 1) /**< \brief (TC_QIDR) DIRection CHanGe */
#define TC_QIDR_QERR (0x1u << 2) /**< \brief (TC_QIDR) Quadrature ERRor */
/* -------- TC_QIMR : (TC Offset: 0xD0) QDEC Interrupt Mask Register -------- */
#define TC_QIMR_IDX (0x1u << 0) /**< \brief (TC_QIMR) InDeX */
#define TC_QIMR_DIRCHG (0x1u << 1) /**< \brief (TC_QIMR) DIRection CHanGe */
#define TC_QIMR_QERR (0x1u << 2) /**< \brief (TC_QIMR) Quadrature ERRor */
/* -------- TC_QISR : (TC Offset: 0xD4) QDEC Interrupt Status Register -------- */
#define TC_QISR_IDX (0x1u << 0) /**< \brief (TC_QISR) InDeX */
#define TC_QISR_DIRCHG (0x1u << 1) /**< \brief (TC_QISR) DIRection CHanGe */
#define TC_QISR_QERR (0x1u << 2) /**< \brief (TC_QISR) Quadrature ERRor */
#define TC_QISR_DIR (0x1u << 8) /**< \brief (TC_QISR) DIRection */
/* -------- TC_FMR : (TC Offset: 0xD8) Fault Mode Register -------- */
#define TC_FMR_ENCF0 (0x1u << 0) /**< \brief (TC_FMR) ENable Compare Fault Channel 0 */
#define TC_FMR_ENCF1 (0x1u << 1) /**< \brief (TC_FMR) ENable Compare Fault Channel 1 */
/* -------- TC_WPMR : (TC Offset: 0xE4) Write Protect Mode Register -------- */
#define TC_WPMR_WPEN (0x1u << 0) /**< \brief (TC_WPMR) Write Protect Enable */
#define TC_WPMR_WPKEY_Pos 8
#define TC_WPMR_WPKEY_Msk (0xffffffu << TC_WPMR_WPKEY_Pos) /**< \brief (TC_WPMR) Write Protect KEY */
#define   TC_WPMR_WPKEY_PASSWD (0x54494Du << 8) /**< \brief (TC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Two-wire Interface */
/* ============================================================================= */
/** \addtogroup SAMA5D4_TWI Two-wire Interface */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Twi hardware registers */
typedef struct {
  __O  uint32_t TWI_CR;        /**< \brief (Twi Offset: 0x00) Control Register */
  __IO uint32_t TWI_MMR;       /**< \brief (Twi Offset: 0x04) Master Mode Register */
  __IO uint32_t TWI_SMR;       /**< \brief (Twi Offset: 0x08) Slave Mode Register */
  __IO uint32_t TWI_IADR;      /**< \brief (Twi Offset: 0x0C) Internal Address Register */
  __IO uint32_t TWI_CWGR;      /**< \brief (Twi Offset: 0x10) Clock Waveform Generator Register */
  __I  uint32_t Reserved1[3];
  __I  uint32_t TWI_SR;        /**< \brief (Twi Offset: 0x20) Status Register */
  __O  uint32_t TWI_IER;       /**< \brief (Twi Offset: 0x24) Interrupt Enable Register */
  __O  uint32_t TWI_IDR;       /**< \brief (Twi Offset: 0x28) Interrupt Disable Register */
  __I  uint32_t TWI_IMR;       /**< \brief (Twi Offset: 0x2C) Interrupt Mask Register */
  __I  uint32_t TWI_RHR;       /**< \brief (Twi Offset: 0x30) Receive Holding Register */
  __O  uint32_t TWI_THR;       /**< \brief (Twi Offset: 0x34) Transmit Holding Register */
  __I  uint32_t Reserved2[43];
  __IO uint32_t TWI_WPMR;      /**< \brief (Twi Offset: 0xE4) Protection Mode Register */
  __I  uint32_t TWI_WPSR;      /**< \brief (Twi Offset: 0xE8) Protection Status Register */
} Twi;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- TWI_CR : (TWI Offset: 0x00) Control Register -------- */
#define TWI_CR_START (0x1u << 0) /**< \brief (TWI_CR) Send a START Condition */
#define TWI_CR_STOP (0x1u << 1) /**< \brief (TWI_CR) Send a STOP Condition */
#define TWI_CR_MSEN (0x1u << 2) /**< \brief (TWI_CR) TWI Master Mode Enabled */
#define TWI_CR_MSDIS (0x1u << 3) /**< \brief (TWI_CR) TWI Master Mode Disabled */
#define TWI_CR_SVEN (0x1u << 4) /**< \brief (TWI_CR) TWI Slave Mode Enabled */
#define TWI_CR_SVDIS (0x1u << 5) /**< \brief (TWI_CR) TWI Slave Mode Disabled */
#define TWI_CR_SWRST (0x1u << 7) /**< \brief (TWI_CR) Software Reset */
/* -------- TWI_MMR : (TWI Offset: 0x04) Master Mode Register -------- */
#define TWI_MMR_IADRSZ_Pos 8
#define TWI_MMR_IADRSZ_Msk (0x3u << TWI_MMR_IADRSZ_Pos) /**< \brief (TWI_MMR) Internal Device Address Size */
#define   TWI_MMR_IADRSZ_NONE (0x0u << 8) /**< \brief (TWI_MMR) No internal device address */
#define   TWI_MMR_IADRSZ_1_BYTE (0x1u << 8) /**< \brief (TWI_MMR) One-byte internal device address */
#define   TWI_MMR_IADRSZ_2_BYTE (0x2u << 8) /**< \brief (TWI_MMR) Two-byte internal device address */
#define   TWI_MMR_IADRSZ_3_BYTE (0x3u << 8) /**< \brief (TWI_MMR) Three-byte internal device address */
#define TWI_MMR_MREAD (0x1u << 12) /**< \brief (TWI_MMR) Master Read Direction */
#define TWI_MMR_DADR_Pos 16
#define TWI_MMR_DADR_Msk (0x7fu << TWI_MMR_DADR_Pos) /**< \brief (TWI_MMR) Device Address */
#define TWI_MMR_DADR(value) ((TWI_MMR_DADR_Msk & ((value) << TWI_MMR_DADR_Pos)))
/* -------- TWI_SMR : (TWI Offset: 0x08) Slave Mode Register -------- */
#define TWI_SMR_SADR_Pos 16
#define TWI_SMR_SADR_Msk (0x7fu << TWI_SMR_SADR_Pos) /**< \brief (TWI_SMR) Slave Address */
#define TWI_SMR_SADR(value) ((TWI_SMR_SADR_Msk & ((value) << TWI_SMR_SADR_Pos)))
/* -------- TWI_IADR : (TWI Offset: 0x0C) Internal Address Register -------- */
#define TWI_IADR_IADR_Pos 0
#define TWI_IADR_IADR_Msk (0xffffffu << TWI_IADR_IADR_Pos) /**< \brief (TWI_IADR) Internal Address */
#define TWI_IADR_IADR(value) ((TWI_IADR_IADR_Msk & ((value) << TWI_IADR_IADR_Pos)))
/* -------- TWI_CWGR : (TWI Offset: 0x10) Clock Waveform Generator Register -------- */
#define TWI_CWGR_CLDIV_Pos 0
#define TWI_CWGR_CLDIV_Msk (0xffu << TWI_CWGR_CLDIV_Pos) /**< \brief (TWI_CWGR) Clock Low Divider */
#define TWI_CWGR_CLDIV(value) ((TWI_CWGR_CLDIV_Msk & ((value) << TWI_CWGR_CLDIV_Pos)))
#define TWI_CWGR_CHDIV_Pos 8
#define TWI_CWGR_CHDIV_Msk (0xffu << TWI_CWGR_CHDIV_Pos) /**< \brief (TWI_CWGR) Clock High Divider */
#define TWI_CWGR_CHDIV(value) ((TWI_CWGR_CHDIV_Msk & ((value) << TWI_CWGR_CHDIV_Pos)))
#define TWI_CWGR_CKDIV_Pos 16
#define TWI_CWGR_CKDIV_Msk (0x7u << TWI_CWGR_CKDIV_Pos) /**< \brief (TWI_CWGR) Clock Divider */
#define TWI_CWGR_CKDIV(value) ((TWI_CWGR_CKDIV_Msk & ((value) << TWI_CWGR_CKDIV_Pos)))
#define TWI_CWGR_HOLD_Pos 24
#define TWI_CWGR_HOLD_Msk (0x1fu << TWI_CWGR_HOLD_Pos) /**< \brief (TWI_CWGR) TWD Hold Time versus TWCK falling */
#define TWI_CWGR_HOLD(value) ((TWI_CWGR_HOLD_Msk & ((value) << TWI_CWGR_HOLD_Pos)))
/* -------- TWI_SR : (TWI Offset: 0x20) Status Register -------- */
#define TWI_SR_TXCOMP (0x1u << 0) /**< \brief (TWI_SR) Transmission Completed (automatically set / reset) */
#define TWI_SR_RXRDY (0x1u << 1) /**< \brief (TWI_SR) Receive Holding Register Ready (automatically set / reset) */
#define TWI_SR_TXRDY (0x1u << 2) /**< \brief (TWI_SR) Transmit Holding Register Ready (automatically set / reset) */
#define TWI_SR_SVREAD (0x1u << 3) /**< \brief (TWI_SR) Slave Read (automatically set / reset) */
#define TWI_SR_SVACC (0x1u << 4) /**< \brief (TWI_SR) Slave Access (automatically set / reset) */
#define TWI_SR_GACC (0x1u << 5) /**< \brief (TWI_SR) General Call Access (clear on read) */
#define TWI_SR_OVRE (0x1u << 6) /**< \brief (TWI_SR) Overrun Error (clear on read) */
#define TWI_SR_NACK (0x1u << 8) /**< \brief (TWI_SR) Not Acknowledged (clear on read) */
#define TWI_SR_ARBLST (0x1u << 9) /**< \brief (TWI_SR) Arbitration Lost (clear on read) */
#define TWI_SR_SCLWS (0x1u << 10) /**< \brief (TWI_SR) Clock Wait State (automatically set / reset) */
#define TWI_SR_EOSACC (0x1u << 11) /**< \brief (TWI_SR) End Of Slave Access (clear on read) */
/* -------- TWI_IER : (TWI Offset: 0x24) Interrupt Enable Register -------- */
#define TWI_IER_TXCOMP (0x1u << 0) /**< \brief (TWI_IER) Transmission Completed Interrupt Enable */
#define TWI_IER_RXRDY (0x1u << 1) /**< \brief (TWI_IER) Receive Holding Register Ready Interrupt Enable */
#define TWI_IER_TXRDY (0x1u << 2) /**< \brief (TWI_IER) Transmit Holding Register Ready Interrupt Enable */
#define TWI_IER_SVACC (0x1u << 4) /**< \brief (TWI_IER) Slave Access Interrupt Enable */
#define TWI_IER_GACC (0x1u << 5) /**< \brief (TWI_IER) General Call Access Interrupt Enable */
#define TWI_IER_OVRE (0x1u << 6) /**< \brief (TWI_IER) Overrun Error Interrupt Enable */
#define TWI_IER_NACK (0x1u << 8) /**< \brief (TWI_IER) Not Acknowledge Interrupt Enable */
#define TWI_IER_ARBLST (0x1u << 9) /**< \brief (TWI_IER) Arbitration Lost Interrupt Enable */
#define TWI_IER_SCL_WS (0x1u << 10) /**< \brief (TWI_IER) Clock Wait State Interrupt Enable */
#define TWI_IER_EOSACC (0x1u << 11) /**< \brief (TWI_IER) End Of Slave Access Interrupt Enable */
/* -------- TWI_IDR : (TWI Offset: 0x28) Interrupt Disable Register -------- */
#define TWI_IDR_TXCOMP (0x1u << 0) /**< \brief (TWI_IDR) Transmission Completed Interrupt Disable */
#define TWI_IDR_RXRDY (0x1u << 1) /**< \brief (TWI_IDR) Receive Holding Register Ready Interrupt Disable */
#define TWI_IDR_TXRDY (0x1u << 2) /**< \brief (TWI_IDR) Transmit Holding Register Ready Interrupt Disable */
#define TWI_IDR_SVACC (0x1u << 4) /**< \brief (TWI_IDR) Slave Access Interrupt Disable */
#define TWI_IDR_GACC (0x1u << 5) /**< \brief (TWI_IDR) General Call Access Interrupt Disable */
#define TWI_IDR_OVRE (0x1u << 6) /**< \brief (TWI_IDR) Overrun Error Interrupt Disable */
#define TWI_IDR_NACK (0x1u << 8) /**< \brief (TWI_IDR) Not Acknowledge Interrupt Disable */
#define TWI_IDR_ARBLST (0x1u << 9) /**< \brief (TWI_IDR) Arbitration Lost Interrupt Disable */
#define TWI_IDR_SCL_WS (0x1u << 10) /**< \brief (TWI_IDR) Clock Wait State Interrupt Disable */
#define TWI_IDR_EOSACC (0x1u << 11) /**< \brief (TWI_IDR) End Of Slave Access Interrupt Disable */
/* -------- TWI_IMR : (TWI Offset: 0x2C) Interrupt Mask Register -------- */
#define TWI_IMR_TXCOMP (0x1u << 0) /**< \brief (TWI_IMR) Transmission Completed Interrupt Mask */
#define TWI_IMR_RXRDY (0x1u << 1) /**< \brief (TWI_IMR) Receive Holding Register Ready Interrupt Mask */
#define TWI_IMR_TXRDY (0x1u << 2) /**< \brief (TWI_IMR) Transmit Holding Register Ready Interrupt Mask */
#define TWI_IMR_SVACC (0x1u << 4) /**< \brief (TWI_IMR) Slave Access Interrupt Mask */
#define TWI_IMR_GACC (0x1u << 5) /**< \brief (TWI_IMR) General Call Access Interrupt Mask */
#define TWI_IMR_OVRE (0x1u << 6) /**< \brief (TWI_IMR) Overrun Error Interrupt Mask */
#define TWI_IMR_NACK (0x1u << 8) /**< \brief (TWI_IMR) Not Acknowledge Interrupt Mask */
#define TWI_IMR_ARBLST (0x1u << 9) /**< \brief (TWI_IMR) Arbitration Lost Interrupt Mask */
#define TWI_IMR_SCL_WS (0x1u << 10) /**< \brief (TWI_IMR) Clock Wait State Interrupt Mask */
#define TWI_IMR_EOSACC (0x1u << 11) /**< \brief (TWI_IMR) End Of Slave Access Interrupt Mask */
/* -------- TWI_RHR : (TWI Offset: 0x30) Receive Holding Register -------- */
#define TWI_RHR_RXDATA_Pos 0
#define TWI_RHR_RXDATA_Msk (0xffu << TWI_RHR_RXDATA_Pos) /**< \brief (TWI_RHR) Master or Slave Receive Holding Data */
/* -------- TWI_THR : (TWI Offset: 0x34) Transmit Holding Register -------- */
#define TWI_THR_TXDATA_Pos 0
#define TWI_THR_TXDATA_Msk (0xffu << TWI_THR_TXDATA_Pos) /**< \brief (TWI_THR) Master or Slave Transmit Holding Data */
#define TWI_THR_TXDATA(value) ((TWI_THR_TXDATA_Msk & ((value) << TWI_THR_TXDATA_Pos)))
/* -------- TWI_WPMR : (TWI Offset: 0xE4) Protection Mode Register -------- */
#define TWI_WPMR_WPEN (0x1u << 0) /**< \brief (TWI_WPMR) Write Protect Enable */
#define TWI_WPMR_WPKEY_Pos 8
#define TWI_WPMR_WPKEY_Msk (0xffffffu << TWI_WPMR_WPKEY_Pos) /**< \brief (TWI_WPMR) Write Protect Key */
#define   TWI_WPMR_WPKEY_PASSWD (0x545749u << 8) /**< \brief (TWI_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0 */
/* -------- TWI_WPSR : (TWI Offset: 0xE8) Protection Status Register -------- */
#define TWI_WPSR_WPVS (0x1u << 0) /**< \brief (TWI_WPSR) Write Protect Violation Status */
#define TWI_WPSR_WPVSRC_Pos 8
#define TWI_WPSR_WPVSRC_Msk (0xffffffu << TWI_WPSR_WPVSRC_Pos) /**< \brief (TWI_WPSR) Write Protect Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Universal Asynchronous Receiver Transmitter */
/* ============================================================================= */
/** \addtogroup SAMA5D4_UART Universal Asynchronous Receiver Transmitter */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Uart hardware registers */
typedef struct {
  __O  uint32_t UART_CR;   /**< \brief (Uart Offset: 0x0000) Control Register */
  __IO uint32_t UART_MR;   /**< \brief (Uart Offset: 0x0004) Mode Register */
  __O  uint32_t UART_IER;  /**< \brief (Uart Offset: 0x0008) Interrupt Enable Register */
  __O  uint32_t UART_IDR;  /**< \brief (Uart Offset: 0x000C) Interrupt Disable Register */
  __I  uint32_t UART_IMR;  /**< \brief (Uart Offset: 0x0010) Interrupt Mask Register */
  __I  uint32_t UART_SR;   /**< \brief (Uart Offset: 0x0014) Status Register */
  __I  uint32_t UART_RHR;  /**< \brief (Uart Offset: 0x0018) Receive Holding Register */
  __O  uint32_t UART_THR;  /**< \brief (Uart Offset: 0x001C) Transmit Holding Register */
  __IO uint32_t UART_BRGR; /**< \brief (Uart Offset: 0x0020) Baud Rate Generator Register */
} Uart;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- UART_CR : (UART Offset: 0x0000) Control Register -------- */
#define UART_CR_RSTRX (0x1u << 2) /**< \brief (UART_CR) Reset Receiver */
#define UART_CR_RSTTX (0x1u << 3) /**< \brief (UART_CR) Reset Transmitter */
#define UART_CR_RXEN (0x1u << 4) /**< \brief (UART_CR) Receiver Enable */
#define UART_CR_RXDIS (0x1u << 5) /**< \brief (UART_CR) Receiver Disable */
#define UART_CR_TXEN (0x1u << 6) /**< \brief (UART_CR) Transmitter Enable */
#define UART_CR_TXDIS (0x1u << 7) /**< \brief (UART_CR) Transmitter Disable */
#define UART_CR_RSTSTA (0x1u << 8) /**< \brief (UART_CR) Reset Status Bits */
/* -------- UART_MR : (UART Offset: 0x0004) Mode Register -------- */
#define UART_MR_PAR_Pos 9
#define UART_MR_PAR_Msk (0x7u << UART_MR_PAR_Pos) /**< \brief (UART_MR) Parity Type */
#define   UART_MR_PAR_EVEN (0x0u << 9) /**< \brief (UART_MR) Even Parity */
#define   UART_MR_PAR_ODD (0x1u << 9) /**< \brief (UART_MR) Odd Parity */
#define   UART_MR_PAR_SPACE (0x2u << 9) /**< \brief (UART_MR) Space: parity forced to 0 */
#define   UART_MR_PAR_MARK (0x3u << 9) /**< \brief (UART_MR) Mark: parity forced to 1 */
#define   UART_MR_PAR_NO (0x4u << 9) /**< \brief (UART_MR) No Parity */
#define UART_MR_CHMODE_Pos 14
#define UART_MR_CHMODE_Msk (0x3u << UART_MR_CHMODE_Pos) /**< \brief (UART_MR) Channel Mode */
#define   UART_MR_CHMODE_NORMAL (0x0u << 14) /**< \brief (UART_MR) Normal Mode */
#define   UART_MR_CHMODE_AUTOMATIC (0x1u << 14) /**< \brief (UART_MR) Automatic Echo */
#define   UART_MR_CHMODE_LOCAL_LOOPBACK (0x2u << 14) /**< \brief (UART_MR) Local Loopback */
#define   UART_MR_CHMODE_REMOTE_LOOPBACK (0x3u << 14) /**< \brief (UART_MR) Remote Loopback */
/* -------- UART_IER : (UART Offset: 0x0008) Interrupt Enable Register -------- */
#define UART_IER_RXRDY (0x1u << 0) /**< \brief (UART_IER) Enable RXRDY Interrupt */
#define UART_IER_TXRDY (0x1u << 1) /**< \brief (UART_IER) Enable TXRDY Interrupt */
#define UART_IER_OVRE (0x1u << 5) /**< \brief (UART_IER) Enable Overrun Error Interrupt */
#define UART_IER_FRAME (0x1u << 6) /**< \brief (UART_IER) Enable Framing Error Interrupt */
#define UART_IER_PARE (0x1u << 7) /**< \brief (UART_IER) Enable Parity Error Interrupt */
#define UART_IER_TXEMPTY (0x1u << 9) /**< \brief (UART_IER) Enable TXEMPTY Interrupt */
/* -------- UART_IDR : (UART Offset: 0x000C) Interrupt Disable Register -------- */
#define UART_IDR_RXRDY (0x1u << 0) /**< \brief (UART_IDR) Disable RXRDY Interrupt */
#define UART_IDR_TXRDY (0x1u << 1) /**< \brief (UART_IDR) Disable TXRDY Interrupt */
#define UART_IDR_OVRE (0x1u << 5) /**< \brief (UART_IDR) Disable Overrun Error Interrupt */
#define UART_IDR_FRAME (0x1u << 6) /**< \brief (UART_IDR) Disable Framing Error Interrupt */
#define UART_IDR_PARE (0x1u << 7) /**< \brief (UART_IDR) Disable Parity Error Interrupt */
#define UART_IDR_TXEMPTY (0x1u << 9) /**< \brief (UART_IDR) Disable TXEMPTY Interrupt */
/* -------- UART_IMR : (UART Offset: 0x0010) Interrupt Mask Register -------- */
#define UART_IMR_RXRDY (0x1u << 0) /**< \brief (UART_IMR) Mask RXRDY Interrupt */
#define UART_IMR_TXRDY (0x1u << 1) /**< \brief (UART_IMR) Disable TXRDY Interrupt */
#define UART_IMR_OVRE (0x1u << 5) /**< \brief (UART_IMR) Mask Overrun Error Interrupt */
#define UART_IMR_FRAME (0x1u << 6) /**< \brief (UART_IMR) Mask Framing Error Interrupt */
#define UART_IMR_PARE (0x1u << 7) /**< \brief (UART_IMR) Mask Parity Error Interrupt */
#define UART_IMR_TXEMPTY (0x1u << 9) /**< \brief (UART_IMR) Mask TXEMPTY Interrupt */
/* -------- UART_SR : (UART Offset: 0x0014) Status Register -------- */
#define UART_SR_RXRDY (0x1u << 0) /**< \brief (UART_SR) Receiver Ready */
#define UART_SR_TXRDY (0x1u << 1) /**< \brief (UART_SR) Transmitter Ready */
#define UART_SR_OVRE (0x1u << 5) /**< \brief (UART_SR) Overrun Error */
#define UART_SR_FRAME (0x1u << 6) /**< \brief (UART_SR) Framing Error */
#define UART_SR_PARE (0x1u << 7) /**< \brief (UART_SR) Parity Error */
#define UART_SR_TXEMPTY (0x1u << 9) /**< \brief (UART_SR) Transmitter Empty */
/* -------- UART_RHR : (UART Offset: 0x0018) Receive Holding Register -------- */
#define UART_RHR_RXCHR_Pos 0
#define UART_RHR_RXCHR_Msk (0xffu << UART_RHR_RXCHR_Pos) /**< \brief (UART_RHR) Received Character */
/* -------- UART_THR : (UART Offset: 0x001C) Transmit Holding Register -------- */
#define UART_THR_TXCHR_Pos 0
#define UART_THR_TXCHR_Msk (0xffu << UART_THR_TXCHR_Pos) /**< \brief (UART_THR) Character to be Transmitted */
#define UART_THR_TXCHR(value) ((UART_THR_TXCHR_Msk & ((value) << UART_THR_TXCHR_Pos)))
/* -------- UART_BRGR : (UART Offset: 0x0020) Baud Rate Generator Register -------- */
#define UART_BRGR_CD_Pos 0
#define UART_BRGR_CD_Msk (0xffffu << UART_BRGR_CD_Pos) /**< \brief (UART_BRGR) Clock Divisor */
#define UART_BRGR_CD(value) ((UART_BRGR_CD_Msk & ((value) << UART_BRGR_CD_Pos)))

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Universal Synchronous Asynchronous Receiver Transmitter */
/* ============================================================================= */
/** \addtogroup SAMA5D4_USART Universal Synchronous Asynchronous Receiver Transmitter */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Usart hardware registers */
typedef struct {
  __O  uint32_t US_CR;         /**< \brief (Usart Offset: 0x0000) Control Register */
  __IO uint32_t US_MR;         /**< \brief (Usart Offset: 0x0004) Mode Register */
  __O  uint32_t US_IER;        /**< \brief (Usart Offset: 0x0008) Interrupt Enable Register */
  __O  uint32_t US_IDR;        /**< \brief (Usart Offset: 0x000C) Interrupt Disable Register */
  __I  uint32_t US_IMR;        /**< \brief (Usart Offset: 0x0010) Interrupt Mask Register */
  __I  uint32_t US_CSR;        /**< \brief (Usart Offset: 0x0014) Channel Status Register */
  __I  uint32_t US_RHR;        /**< \brief (Usart Offset: 0x0018) Receiver Holding Register */
  __O  uint32_t US_THR;        /**< \brief (Usart Offset: 0x001C) Transmitter Holding Register */
  __IO uint32_t US_BRGR;       /**< \brief (Usart Offset: 0x0020) Baud Rate Generator Register */
  __IO uint32_t US_RTOR;       /**< \brief (Usart Offset: 0x0024) Receiver Time-out Register */
  __IO uint32_t US_TTGR;       /**< \brief (Usart Offset: 0x0028) Transmitter Timeguard Register */
  __I  uint32_t Reserved1[5];
  __IO uint32_t US_FIDI;       /**< \brief (Usart Offset: 0x0040) FI DI Ratio Register */
  __I  uint32_t US_NER;        /**< \brief (Usart Offset: 0x0044) Number of Errors Register */
  __I  uint32_t Reserved2[1];
  __IO uint32_t US_IF;         /**< \brief (Usart Offset: 0x004C) IrDA Filter Register */
  __IO uint32_t US_MAN;        /**< \brief (Usart Offset: 0x0050) Manchester Encoder Decoder Register */
  __I  uint32_t Reserved3[36];
  __IO uint32_t US_WPMR;       /**< \brief (Usart Offset: 0x00E4) Write Protect Mode Register */
  __I  uint32_t US_WPSR;       /**< \brief (Usart Offset: 0x00E8) Write Protect Status Register */
} Usart;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- US_CR : (USART Offset: 0x0000) Control Register -------- */
#define US_CR_RSTRX (0x1u << 2) /**< \brief (US_CR) Reset Receiver */
#define US_CR_RSTTX (0x1u << 3) /**< \brief (US_CR) Reset Transmitter */
#define US_CR_RXEN (0x1u << 4) /**< \brief (US_CR) Receiver Enable */
#define US_CR_RXDIS (0x1u << 5) /**< \brief (US_CR) Receiver Disable */
#define US_CR_TXEN (0x1u << 6) /**< \brief (US_CR) Transmitter Enable */
#define US_CR_TXDIS (0x1u << 7) /**< \brief (US_CR) Transmitter Disable */
#define US_CR_RSTSTA (0x1u << 8) /**< \brief (US_CR) Reset Status Bits */
#define US_CR_STTBRK (0x1u << 9) /**< \brief (US_CR) Start Break */
#define US_CR_STPBRK (0x1u << 10) /**< \brief (US_CR) Stop Break */
#define US_CR_STTTO (0x1u << 11) /**< \brief (US_CR) Start Time-out */
#define US_CR_SENDA (0x1u << 12) /**< \brief (US_CR) Send Address */
#define US_CR_RSTIT (0x1u << 13) /**< \brief (US_CR) Reset Iterations */
#define US_CR_RSTNACK (0x1u << 14) /**< \brief (US_CR) Reset Non Acknowledge */
#define US_CR_RETTO (0x1u << 15) /**< \brief (US_CR) Rearm Time-out */
#define US_CR_RTSEN (0x1u << 18) /**< \brief (US_CR) Request to Send Enable */
#define US_CR_RTSDIS (0x1u << 19) /**< \brief (US_CR) Request to Send Disable */
#define US_CR_FCS (0x1u << 18) /**< \brief (US_CR) Force SPI Chip Select */
#define US_CR_RCS (0x1u << 19) /**< \brief (US_CR) Release SPI Chip Select */
/* -------- US_MR : (USART Offset: 0x0004) Mode Register -------- */
#define US_MR_USART_MODE_Pos 0
#define US_MR_USART_MODE_Msk (0xfu << US_MR_USART_MODE_Pos) /**< \brief (US_MR) USART Mode of Operation */
#define   US_MR_USART_MODE_NORMAL (0x0u << 0) /**< \brief (US_MR) Normal mode */
#define   US_MR_USART_MODE_RS485 (0x1u << 0) /**< \brief (US_MR) RS485 */
#define   US_MR_USART_MODE_HW_HANDSHAKING (0x2u << 0) /**< \brief (US_MR) Hardware Handshaking */
#define   US_MR_USART_MODE_IS07816_T_0 (0x4u << 0) /**< \brief (US_MR) IS07816 Protocol: T = 0 */
#define   US_MR_USART_MODE_IS07816_T_1 (0x6u << 0) /**< \brief (US_MR) IS07816 Protocol: T = 1 */
#define   US_MR_USART_MODE_IRDA (0x8u << 0) /**< \brief (US_MR) IrDA */
#define   US_MR_USART_MODE_SPI_MASTER (0xEu << 0) /**< \brief (US_MR) SPI Master */
#define   US_MR_USART_MODE_SPI_SLAVE (0xFu << 0) /**< \brief (US_MR) SPI Slave */
#define US_MR_USCLKS_Pos 4
#define US_MR_USCLKS_Msk (0x3u << US_MR_USCLKS_Pos) /**< \brief (US_MR) Clock Selection */
#define   US_MR_USCLKS_MCK (0x0u << 4) /**< \brief (US_MR) Master Clock MCK is selected */
#define   US_MR_USCLKS_DIV (0x1u << 4) /**< \brief (US_MR) Internal Clock Divided MCK/DIV (DIV=(DIV=8)) is selected */
#define   US_MR_USCLKS_SCK (0x3u << 4) /**< \brief (US_MR) Serial Clock SLK is selected */
#define US_MR_CHRL_Pos 6
#define US_MR_CHRL_Msk (0x3u << US_MR_CHRL_Pos) /**< \brief (US_MR) Character Length. */
#define   US_MR_CHRL_5_BIT (0x0u << 6) /**< \brief (US_MR) Character length is 5 bits */
#define   US_MR_CHRL_6_BIT (0x1u << 6) /**< \brief (US_MR) Character length is 6 bits */
#define   US_MR_CHRL_7_BIT (0x2u << 6) /**< \brief (US_MR) Character length is 7 bits */
#define   US_MR_CHRL_8_BIT (0x3u << 6) /**< \brief (US_MR) Character length is 8 bits */
#define US_MR_SYNC (0x1u << 8) /**< \brief (US_MR) Synchronous Mode Select */
#define US_MR_PAR_Pos 9
#define US_MR_PAR_Msk (0x7u << US_MR_PAR_Pos) /**< \brief (US_MR) Parity Type */
#define   US_MR_PAR_EVEN (0x0u << 9) /**< \brief (US_MR) Even parity */
#define   US_MR_PAR_ODD (0x1u << 9) /**< \brief (US_MR) Odd parity */
#define   US_MR_PAR_SPACE (0x2u << 9) /**< \brief (US_MR) Parity forced to 0 (Space) */
#define   US_MR_PAR_MARK (0x3u << 9) /**< \brief (US_MR) Parity forced to 1 (Mark) */
#define   US_MR_PAR_NO (0x4u << 9) /**< \brief (US_MR) No parity */
#define   US_MR_PAR_MULTIDROP (0x6u << 9) /**< \brief (US_MR) Multidrop mode */
#define US_MR_NBSTOP_Pos 12
#define US_MR_NBSTOP_Msk (0x3u << US_MR_NBSTOP_Pos) /**< \brief (US_MR) Number of Stop Bits */
#define   US_MR_NBSTOP_1_BIT (0x0u << 12) /**< \brief (US_MR) 1 stop bit */
#define   US_MR_NBSTOP_1_5_BIT (0x1u << 12) /**< \brief (US_MR) 1.5 stop bit (SYNC = 0) or reserved (SYNC = 1) */
#define   US_MR_NBSTOP_2_BIT (0x2u << 12) /**< \brief (US_MR) 2 stop bits */
#define US_MR_CHMODE_Pos 14
#define US_MR_CHMODE_Msk (0x3u << US_MR_CHMODE_Pos) /**< \brief (US_MR) Channel Mode */
#define   US_MR_CHMODE_NORMAL (0x0u << 14) /**< \brief (US_MR) Normal Mode */
#define   US_MR_CHMODE_AUTOMATIC (0x1u << 14) /**< \brief (US_MR) Automatic Echo. Receiver input is connected to the TXD pin. */
#define   US_MR_CHMODE_LOCAL_LOOPBACK (0x2u << 14) /**< \brief (US_MR) Local Loopback. Transmitter output is connected to the Receiver Input. */
#define   US_MR_CHMODE_REMOTE_LOOPBACK (0x3u << 14) /**< \brief (US_MR) Remote Loopback. RXD pin is internally connected to the TXD pin. */
#define US_MR_MSBF (0x1u << 16) /**< \brief (US_MR) Bit Order */
#define US_MR_MODE9 (0x1u << 17) /**< \brief (US_MR) 9-bit Character Length */
#define US_MR_CLKO (0x1u << 18) /**< \brief (US_MR) Clock Output Select */
#define US_MR_OVER (0x1u << 19) /**< \brief (US_MR) Oversampling Mode */
#define US_MR_INACK (0x1u << 20) /**< \brief (US_MR) Inhibit Non Acknowledge */
#define US_MR_DSNACK (0x1u << 21) /**< \brief (US_MR) Disable Successive NACK */
#define US_MR_VAR_SYNC (0x1u << 22) /**< \brief (US_MR) Variable Synchronization of Command/Data Sync Start Frame Delimiter */
#define US_MR_INVDATA (0x1u << 23) /**< \brief (US_MR) Inverted Data */
#define US_MR_MAX_ITERATION_Pos 24
#define US_MR_MAX_ITERATION_Msk (0x7u << US_MR_MAX_ITERATION_Pos) /**< \brief (US_MR) Maximum Number of Automatic Iteration */
#define US_MR_MAX_ITERATION(value) ((US_MR_MAX_ITERATION_Msk & ((value) << US_MR_MAX_ITERATION_Pos)))
#define US_MR_FILTER (0x1u << 28) /**< \brief (US_MR) Infrared Receive Line Filter */
#define US_MR_MAN (0x1u << 29) /**< \brief (US_MR) Manchester Encoder/Decoder Enable */
#define US_MR_MODSYNC (0x1u << 30) /**< \brief (US_MR) Manchester Synchronization Mode */
#define US_MR_ONEBIT (0x1u << 31) /**< \brief (US_MR) Start Frame Delimiter Selector */
#define US_MR_CPHA (0x1u << 8) /**< \brief (US_MR) SPI Clock Phase */
#define US_MR_CPOL (0x1u << 16) /**< \brief (US_MR) SPI Clock Polarity */
#define US_MR_WRDBT (0x1u << 20) /**< \brief (US_MR) Wait Read Data Before Transfer */
/* -------- US_IER : (USART Offset: 0x0008) Interrupt Enable Register -------- */
#define US_IER_RXRDY (0x1u << 0) /**< \brief (US_IER) RXRDY Interrupt Enable */
#define US_IER_TXRDY (0x1u << 1) /**< \brief (US_IER) TXRDY Interrupt Enable */
#define US_IER_RXBRK (0x1u << 2) /**< \brief (US_IER) Receiver Break Interrupt Enable */
#define US_IER_OVRE (0x1u << 5) /**< \brief (US_IER) Overrun Error Interrupt Enable */
#define US_IER_FRAME (0x1u << 6) /**< \brief (US_IER) Framing Error Interrupt Enable */
#define US_IER_PARE (0x1u << 7) /**< \brief (US_IER) Parity Error Interrupt Enable */
#define US_IER_TIMEOUT (0x1u << 8) /**< \brief (US_IER) Time-out Interrupt Enable */
#define US_IER_TXEMPTY (0x1u << 9) /**< \brief (US_IER) TXEMPTY Interrupt Enable */
#define US_IER_ITER (0x1u << 10) /**< \brief (US_IER) Max number of Repetitions Reached Interrupt Enable */
#define US_IER_NACK (0x1u << 13) /**< \brief (US_IER) Non AcknowledgeInterrupt Enable */
#define US_IER_CTSIC (0x1u << 19) /**< \brief (US_IER) Clear to Send Input Change Interrupt Enable */
#define US_IER_MANE (0x1u << 24) /**< \brief (US_IER) Manchester Error Interrupt Enable */
#define US_IER_UNRE (0x1u << 10) /**< \brief (US_IER) SPI Underrun Error Interrupt Enable */
/* -------- US_IDR : (USART Offset: 0x000C) Interrupt Disable Register -------- */
#define US_IDR_RXRDY (0x1u << 0) /**< \brief (US_IDR) RXRDY Interrupt Disable */
#define US_IDR_TXRDY (0x1u << 1) /**< \brief (US_IDR) TXRDY Interrupt Disable */
#define US_IDR_RXBRK (0x1u << 2) /**< \brief (US_IDR) Receiver Break Interrupt Disable */
#define US_IDR_OVRE (0x1u << 5) /**< \brief (US_IDR) Overrun Error Interrupt Enable */
#define US_IDR_FRAME (0x1u << 6) /**< \brief (US_IDR) Framing Error Interrupt Disable */
#define US_IDR_PARE (0x1u << 7) /**< \brief (US_IDR) Parity Error Interrupt Disable */
#define US_IDR_TIMEOUT (0x1u << 8) /**< \brief (US_IDR) Time-out Interrupt Disable */
#define US_IDR_TXEMPTY (0x1u << 9) /**< \brief (US_IDR) TXEMPTY Interrupt Disable */
#define US_IDR_ITER (0x1u << 10) /**< \brief (US_IDR) Max Number of Repetitions Reached Interrupt Disable */
#define US_IDR_NACK (0x1u << 13) /**< \brief (US_IDR) Non AcknowledgeInterrupt Disable */
#define US_IDR_CTSIC (0x1u << 19) /**< \brief (US_IDR) Clear to Send Input Change Interrupt Disable */
#define US_IDR_MANE (0x1u << 24) /**< \brief (US_IDR) Manchester Error Interrupt Disable */
#define US_IDR_UNRE (0x1u << 10) /**< \brief (US_IDR) SPI Underrun Error Interrupt Disable */
/* -------- US_IMR : (USART Offset: 0x0010) Interrupt Mask Register -------- */
#define US_IMR_RXRDY (0x1u << 0) /**< \brief (US_IMR) RXRDY Interrupt Mask */
#define US_IMR_TXRDY (0x1u << 1) /**< \brief (US_IMR) TXRDY Interrupt Mask */
#define US_IMR_RXBRK (0x1u << 2) /**< \brief (US_IMR) Receiver Break Interrupt Mask */
#define US_IMR_OVRE (0x1u << 5) /**< \brief (US_IMR) Overrun Error Interrupt Mask */
#define US_IMR_FRAME (0x1u << 6) /**< \brief (US_IMR) Framing Error Interrupt Mask */
#define US_IMR_PARE (0x1u << 7) /**< \brief (US_IMR) Parity Error Interrupt Mask */
#define US_IMR_TIMEOUT (0x1u << 8) /**< \brief (US_IMR) Time-out Interrupt Mask */
#define US_IMR_TXEMPTY (0x1u << 9) /**< \brief (US_IMR) TXEMPTY Interrupt Mask */
#define US_IMR_ITER (0x1u << 10) /**< \brief (US_IMR) Max Number of Repetitions Reached Interrupt Mask */
#define US_IMR_NACK (0x1u << 13) /**< \brief (US_IMR) Non AcknowledgeInterrupt Mask */
#define US_IMR_CTSIC (0x1u << 19) /**< \brief (US_IMR) Clear to Send Input Change Interrupt Mask */
#define US_IMR_MANE (0x1u << 24) /**< \brief (US_IMR) Manchester Error Interrupt Mask */
#define US_IMR_UNRE (0x1u << 10) /**< \brief (US_IMR) SPI Underrun Error Interrupt Mask */
/* -------- US_CSR : (USART Offset: 0x0014) Channel Status Register -------- */
#define US_CSR_RXRDY (0x1u << 0) /**< \brief (US_CSR) Receiver Ready */
#define US_CSR_TXRDY (0x1u << 1) /**< \brief (US_CSR) Transmitter Ready */
#define US_CSR_RXBRK (0x1u << 2) /**< \brief (US_CSR) Break Received/End of Break */
#define US_CSR_OVRE (0x1u << 5) /**< \brief (US_CSR) Overrun Error */
#define US_CSR_FRAME (0x1u << 6) /**< \brief (US_CSR) Framing Error */
#define US_CSR_PARE (0x1u << 7) /**< \brief (US_CSR) Parity Error */
#define US_CSR_TIMEOUT (0x1u << 8) /**< \brief (US_CSR) Receiver Time-out */
#define US_CSR_TXEMPTY (0x1u << 9) /**< \brief (US_CSR) Transmitter Empty */
#define US_CSR_ITER (0x1u << 10) /**< \brief (US_CSR) Max Number of Repetitions Reached */
#define US_CSR_NACK (0x1u << 13) /**< \brief (US_CSR) Non AcknowledgeInterrupt */
#define US_CSR_CTSIC (0x1u << 19) /**< \brief (US_CSR) Clear to Send Input Change Flag */
#define US_CSR_CTS (0x1u << 23) /**< \brief (US_CSR) Image of CTS Input */
#define US_CSR_MANERR (0x1u << 24) /**< \brief (US_CSR) Manchester Error */
#define US_CSR_UNRE (0x1u << 10) /**< \brief (US_CSR) Underrun Error */
/* -------- US_RHR : (USART Offset: 0x0018) Receiver Holding Register -------- */
#define US_RHR_RXCHR_Pos 0
#define US_RHR_RXCHR_Msk (0x1ffu << US_RHR_RXCHR_Pos) /**< \brief (US_RHR) Received Character */
#define US_RHR_RXSYNH (0x1u << 15) /**< \brief (US_RHR) Received Sync */
/* -------- US_THR : (USART Offset: 0x001C) Transmitter Holding Register -------- */
#define US_THR_TXCHR_Pos 0
#define US_THR_TXCHR_Msk (0x1ffu << US_THR_TXCHR_Pos) /**< \brief (US_THR) Character to be Transmitted */
#define US_THR_TXCHR(value) ((US_THR_TXCHR_Msk & ((value) << US_THR_TXCHR_Pos)))
#define US_THR_TXSYNH (0x1u << 15) /**< \brief (US_THR) Sync Field to be Transmitted */
/* -------- US_BRGR : (USART Offset: 0x0020) Baud Rate Generator Register -------- */
#define US_BRGR_CD_Pos 0
#define US_BRGR_CD_Msk (0xffffu << US_BRGR_CD_Pos) /**< \brief (US_BRGR) Clock Divider */
#define US_BRGR_CD(value) ((US_BRGR_CD_Msk & ((value) << US_BRGR_CD_Pos)))
#define US_BRGR_FP_Pos 16
#define US_BRGR_FP_Msk (0x7u << US_BRGR_FP_Pos) /**< \brief (US_BRGR) Fractional Part */
#define US_BRGR_FP(value) ((US_BRGR_FP_Msk & ((value) << US_BRGR_FP_Pos)))
/* -------- US_RTOR : (USART Offset: 0x0024) Receiver Time-out Register -------- */
#define US_RTOR_TO_Pos 0
#define US_RTOR_TO_Msk (0xffffu << US_RTOR_TO_Pos) /**< \brief (US_RTOR) Time-out Value */
#define US_RTOR_TO(value) ((US_RTOR_TO_Msk & ((value) << US_RTOR_TO_Pos)))
/* -------- US_TTGR : (USART Offset: 0x0028) Transmitter Timeguard Register -------- */
#define US_TTGR_TG_Pos 0
#define US_TTGR_TG_Msk (0xffu << US_TTGR_TG_Pos) /**< \brief (US_TTGR) Timeguard Value */
#define US_TTGR_TG(value) ((US_TTGR_TG_Msk & ((value) << US_TTGR_TG_Pos)))
/* -------- US_FIDI : (USART Offset: 0x0040) FI DI Ratio Register -------- */
#define US_FIDI_FI_DI_RATIO_Pos 0
#define US_FIDI_FI_DI_RATIO_Msk (0xffffu << US_FIDI_FI_DI_RATIO_Pos) /**< \brief (US_FIDI) FI Over DI Ratio Value */
#define US_FIDI_FI_DI_RATIO(value) ((US_FIDI_FI_DI_RATIO_Msk & ((value) << US_FIDI_FI_DI_RATIO_Pos)))
/* -------- US_NER : (USART Offset: 0x0044) Number of Errors Register -------- */
#define US_NER_NB_ERRORS_Pos 0
#define US_NER_NB_ERRORS_Msk (0xffu << US_NER_NB_ERRORS_Pos) /**< \brief (US_NER) Number of Errors */
/* -------- US_IF : (USART Offset: 0x004C) IrDA Filter Register -------- */
#define US_IF_IRDA_FILTER_Pos 0
#define US_IF_IRDA_FILTER_Msk (0xffu << US_IF_IRDA_FILTER_Pos) /**< \brief (US_IF) IrDA Filter */
#define US_IF_IRDA_FILTER(value) ((US_IF_IRDA_FILTER_Msk & ((value) << US_IF_IRDA_FILTER_Pos)))
/* -------- US_MAN : (USART Offset: 0x0050) Manchester Encoder Decoder Register -------- */
#define US_MAN_TX_PL_Pos 0
#define US_MAN_TX_PL_Msk (0xfu << US_MAN_TX_PL_Pos) /**< \brief (US_MAN) Transmitter Preamble Length */
#define US_MAN_TX_PL(value) ((US_MAN_TX_PL_Msk & ((value) << US_MAN_TX_PL_Pos)))
#define US_MAN_TX_PP_Pos 8
#define US_MAN_TX_PP_Msk (0x3u << US_MAN_TX_PP_Pos) /**< \brief (US_MAN) Transmitter Preamble Pattern */
#define   US_MAN_TX_PP_ALL_ONE (0x0u << 8) /**< \brief (US_MAN) The preamble is composed of '1's */
#define   US_MAN_TX_PP_ALL_ZERO (0x1u << 8) /**< \brief (US_MAN) The preamble is composed of '0's */
#define   US_MAN_TX_PP_ZERO_ONE (0x2u << 8) /**< \brief (US_MAN) The preamble is composed of '01's */
#define   US_MAN_TX_PP_ONE_ZERO (0x3u << 8) /**< \brief (US_MAN) The preamble is composed of '10's */
#define US_MAN_TX_MPOL (0x1u << 12) /**< \brief (US_MAN) Transmitter Manchester Polarity */
#define US_MAN_RX_PL_Pos 16
#define US_MAN_RX_PL_Msk (0xfu << US_MAN_RX_PL_Pos) /**< \brief (US_MAN) Receiver Preamble Length */
#define US_MAN_RX_PL(value) ((US_MAN_RX_PL_Msk & ((value) << US_MAN_RX_PL_Pos)))
#define US_MAN_RX_PP_Pos 24
#define US_MAN_RX_PP_Msk (0x3u << US_MAN_RX_PP_Pos) /**< \brief (US_MAN) Receiver Preamble Pattern detected */
#define   US_MAN_RX_PP_ALL_ONE (0x0u << 24) /**< \brief (US_MAN) The preamble is composed of '1's */
#define   US_MAN_RX_PP_ALL_ZERO (0x1u << 24) /**< \brief (US_MAN) The preamble is composed of '0's */
#define   US_MAN_RX_PP_ZERO_ONE (0x2u << 24) /**< \brief (US_MAN) The preamble is composed of '01's */
#define   US_MAN_RX_PP_ONE_ZERO (0x3u << 24) /**< \brief (US_MAN) The preamble is composed of '10's */
#define US_MAN_RX_MPOL (0x1u << 28) /**< \brief (US_MAN) Receiver Manchester Polarity */
#define US_MAN_ONE (0x1u << 29) /**< \brief (US_MAN) Must Be Set to 1 */
#define US_MAN_DRIFT (0x1u << 30) /**< \brief (US_MAN) Drift Compensation */
/* -------- US_WPMR : (USART Offset: 0x00E4) Write Protect Mode Register -------- */
#define US_WPMR_WPEN (0x1u << 0) /**< \brief (US_WPMR) Write Protect Enable */
#define US_WPMR_WPKEY_Pos 8
#define US_WPMR_WPKEY_Msk (0xffffffu << US_WPMR_WPKEY_Pos) /**< \brief (US_WPMR) Write Protect KEY. */
#define   US_WPMR_WPKEY_PASSWD (0x555341u << 8) /**< \brief (US_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */
/* -------- US_WPSR : (USART Offset: 0x00E8) Write Protect Status Register -------- */
#define US_WPSR_WPVS (0x1u << 0) /**< \brief (US_WPSR) Write Protect Violation Status */
#define US_WPSR_WPVSRC_Pos 8
#define US_WPSR_WPVSRC_Msk (0xffffu << US_WPSR_WPVSRC_Pos) /**< \brief (US_WPSR) Write Protect Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Watchdog Timer */
/* ============================================================================= */
/** \addtogroup SAMA5D4_WDT Watchdog Timer */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Wdt hardware registers */
typedef struct {
  __O  uint32_t WDT_CR; /**< \brief (Wdt Offset: 0x00) Control Register */
  __IO uint32_t WDT_MR; /**< \brief (Wdt Offset: 0x04) Mode Register */
  __I  uint32_t WDT_SR; /**< \brief (Wdt Offset: 0x08) Status Register */
} Wdt;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- WDT_CR : (WDT Offset: 0x00) Control Register -------- */
#define WDT_CR_WDRSTT (0x1u << 0) /**< \brief (WDT_CR) Watchdog Restart */
#define WDT_CR_LOCKMR (0x1u << 4) /**< \brief (WDT_CR) Locks Mode Register Write Access */
#define WDT_CR_KEY_Pos 24
#define WDT_CR_KEY_Msk (0xffu << WDT_CR_KEY_Pos) /**< \brief (WDT_CR) Password. */
#define   WDT_CR_KEY_PASSWD (0xA5u << 24) /**< \brief (WDT_CR) Writing any other value in this field aborts the write operation. */
/* -------- WDT_MR : (WDT Offset: 0x04) Mode Register -------- */
#define WDT_MR_WDV_Pos 0
#define WDT_MR_WDV_Msk (0xfffu << WDT_MR_WDV_Pos) /**< \brief (WDT_MR) Watchdog Counter Value */
#define WDT_MR_WDV(value) ((WDT_MR_WDV_Msk & ((value) << WDT_MR_WDV_Pos)))
#define WDT_MR_WDFIEN (0x1u << 12) /**< \brief (WDT_MR) Watchdog Fault Interrupt Enable */
#define WDT_MR_WDRSTEN (0x1u << 13) /**< \brief (WDT_MR) Watchdog Reset Enable */
#define WDT_MR_WDRPROC (0x1u << 14) /**< \brief (WDT_MR) Watchdog Reset Processor */
#define WDT_MR_WDDIS (0x1u << 15) /**< \brief (WDT_MR) Watchdog Disable */
#define WDT_MR_WDD_Pos 16
#define WDT_MR_WDD_Msk (0xfffu << WDT_MR_WDD_Pos) /**< \brief (WDT_MR) Watchdog Delta Value */
#define WDT_MR_WDD(value) ((WDT_MR_WDD_Msk & ((value) << WDT_MR_WDD_Pos)))
#define WDT_MR_WDDBGHLT (0x1u << 28) /**< \brief (WDT_MR) Watchdog Debug Halt */
#define WDT_MR_WDIDLEHLT (0x1u << 29) /**< \brief (WDT_MR) Watchdog Idle Halt */
/* -------- WDT_SR : (WDT Offset: 0x08) Status Register -------- */
#define WDT_SR_WDUNF (0x1u << 0) /**< \brief (WDT_SR) Watchdog Underflow */
#define WDT_SR_WDERR (0x1u << 1) /**< \brief (WDT_SR) Watchdog Error */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Extensible DMA Controller */
/* ============================================================================= */
/** \addtogroup SAMA5D4_XDMAC Extensible DMA Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief XdmacChid hardware registers */
typedef struct {
  __O  uint32_t XDMAC_CIE;     /**< \brief (XdmacChid Offset: 0x0) Channel Interrupt Enable Register */
  __O  uint32_t XDMAC_CID;     /**< \brief (XdmacChid Offset: 0x4) Channel Interrupt Disable Register */
  __O  uint32_t XDMAC_CIM;     /**< \brief (XdmacChid Offset: 0x8) Channel Interrupt Mask Register */
  __I  uint32_t XDMAC_CIS;     /**< \brief (XdmacChid Offset: 0xC) Channel Interrupt Status Register */
  __IO uint32_t XDMAC_CSA;     /**< \brief (XdmacChid Offset: 0x10) Channel Source Address Register */
  __IO uint32_t XDMAC_CDA;     /**< \brief (XdmacChid Offset: 0x14) Channel Destination Address Register */
  __IO uint32_t XDMAC_CNDA;    /**< \brief (XdmacChid Offset: 0x18) Channel Next Descriptor Address Register */
  __IO uint32_t XDMAC_CNDC;    /**< \brief (XdmacChid Offset: 0x1C) Channel Next Descriptor Control Register */
  __IO uint32_t XDMAC_CUBC;    /**< \brief (XdmacChid Offset: 0x20) Channel Microblock Control Register */
  __IO uint32_t XDMAC_CBC;     /**< \brief (XdmacChid Offset: 0x24) Channel Block Control Register */
  __IO uint32_t XDMAC_CC;      /**< \brief (XdmacChid Offset: 0x28) Channel Configuration Register */
  __IO uint32_t XDMAC_CDS_MSP; /**< \brief (XdmacChid Offset: 0x2C) Channel Data Stride Memory Set Pattern */
  __IO uint32_t XDMAC_CSUS;    /**< \brief (XdmacChid Offset: 0x30) Channel Source Microblock Stride */
  __IO uint32_t XDMAC_CDUS;    /**< \brief (XdmacChid Offset: 0x34) Channel Destination Microblock Stride */
  __I  uint32_t Reserved1[2];
} XdmacChid;
/** \brief Xdmac hardware registers */
#define XDMACCHID_NUMBER 16
typedef struct {
  __IO uint32_t  XDMAC_GTYPE;                  /**< \brief (Xdmac Offset: 0x00) Global Type register */
  __I  uint32_t  XDMAC_GCFG;                   /**< \brief (Xdmac Offset: 0x04) Global Configuration Register */
  __IO uint32_t  XDMAC_GWAC;                   /**< \brief (Xdmac Offset: 0x08) Global Weighted Arbiter Configuration Register */
  __O  uint32_t  XDMAC_GIE;                    /**< \brief (Xdmac Offset: 0x0C) Global Interrupt Enable Register */
  __O  uint32_t  XDMAC_GID;                    /**< \brief (Xdmac Offset: 0x10) Global Interrupt Disable Register */
  __I  uint32_t  XDMAC_GIM;                    /**< \brief (Xdmac Offset: 0x14) Global Interrupt Mask Register */
  __I  uint32_t  XDMAC_GIS;                    /**< \brief (Xdmac Offset: 0x18) Global Interrupt Status Register */
  __O  uint32_t  XDMAC_GE;                     /**< \brief (Xdmac Offset: 0x1C) Global Channel Enable Register */
  __O  uint32_t  XDMAC_GD;                     /**< \brief (Xdmac Offset: 0x20) Global Channel Disable Register */
  __I  uint32_t  XDMAC_GS;                     /**< \brief (Xdmac Offset: 0x24) Global Channel Status Register */
  __IO uint32_t  XDMAC_GRS;                    /**< \brief (Xdmac Offset: 0x28) Global Channel Read Suspend Register */
  __IO uint32_t  XDMAC_GWS;                    /**< \brief (Xdmac Offset: 0x2C) Global Channel Write Suspend Register */
  __O  uint32_t  XDMAC_GRWS;                   /**< \brief (Xdmac Offset: 0x30) Global Channel Read Write Suspend Register */
  __O  uint32_t  XDMAC_GRWR;                   /**< \brief (Xdmac Offset: 0x34) Global Channel Read Write Resume Register */
  __O  uint32_t  XDMAC_GSWR;                   /**< \brief (Xdmac Offset: 0x38) Global Channel Software Request Register */
  __I  uint32_t  XDMAC_GSWS;                   /**< \brief (Xdmac Offset: 0x3C) Global Channel Software Request Status Register */
  __O  uint32_t  XDMAC_GSWF;                   /**< \brief (Xdmac Offset: 0x40) Global Channel Software Flush Request Register */
  __I  uint32_t  Reserved1[3];
       XdmacChid XDMAC_CHID[XDMACCHID_NUMBER]; /**< \brief (Xdmac Offset: 0x50) chid = 0 .. 15 */
} Xdmac;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- XDMAC_GTYPE : (XDMAC Offset: 0x00) Global Type register -------- */
#define XDMAC_GTYPE_NB_CH_Pos 0
#define XDMAC_GTYPE_NB_CH_Msk (0x1fu << XDMAC_GTYPE_NB_CH_Pos) /**< \brief (XDMAC_GTYPE) Number of Channels Minus One */
#define XDMAC_GTYPE_NB_CH(value) ((XDMAC_GTYPE_NB_CH_Msk & ((value) << XDMAC_GTYPE_NB_CH_Pos)))
#define XDMAC_GTYPE_FIFO_SZ_Pos 5
#define XDMAC_GTYPE_FIFO_SZ_Msk (0x7ffu << XDMAC_GTYPE_FIFO_SZ_Pos) /**< \brief (XDMAC_GTYPE) Number of Bytes */
#define XDMAC_GTYPE_FIFO_SZ(value) ((XDMAC_GTYPE_FIFO_SZ_Msk & ((value) << XDMAC_GTYPE_FIFO_SZ_Pos)))
#define XDMAC_GTYPE_NB_REQ_Pos 16
#define XDMAC_GTYPE_NB_REQ_Msk (0x7fu << XDMAC_GTYPE_NB_REQ_Pos) /**< \brief (XDMAC_GTYPE) Number of Peripheral Requests Minus One */
#define XDMAC_GTYPE_NB_REQ(value) ((XDMAC_GTYPE_NB_REQ_Msk & ((value) << XDMAC_GTYPE_NB_REQ_Pos)))
/* -------- XDMAC_GCFG : (XDMAC Offset: 0x04) Global Configuration Register -------- */
#define XDMAC_GCFG_CGDISREG (0x1u << 0) /**< \brief (XDMAC_GCFG) Configuration Registers Clock Gating Disable */
#define XDMAC_GCFG_CGDISPIPE (0x1u << 1) /**< \brief (XDMAC_GCFG) Pipeline Clock Gating Disable */
#define XDMAC_GCFG_CGDISFIFO (0x1u << 2) /**< \brief (XDMAC_GCFG) FIFO Clock Gating Disable */
#define XDMAC_GCFG_CGDISIF (0x1u << 3) /**< \brief (XDMAC_GCFG) Bus Interface Clock Gating Disable */
#define XDMAC_GCFG_BXKBEN (0x1u << 8) /**< \brief (XDMAC_GCFG) Boundary X Kilo byte Enable */
/* -------- XDMAC_GWAC : (XDMAC Offset: 0x08) Global Weighted Arbiter Configuration Register -------- */
#define XDMAC_GWAC_PW0_Pos 0
#define XDMAC_GWAC_PW0_Msk (0xfu << XDMAC_GWAC_PW0_Pos) /**< \brief (XDMAC_GWAC) Pool Weight 0 */
#define XDMAC_GWAC_PW0(value) ((XDMAC_GWAC_PW0_Msk & ((value) << XDMAC_GWAC_PW0_Pos)))
#define XDMAC_GWAC_PW1_Pos 4
#define XDMAC_GWAC_PW1_Msk (0xfu << XDMAC_GWAC_PW1_Pos) /**< \brief (XDMAC_GWAC) Pool Weight 1 */
#define XDMAC_GWAC_PW1(value) ((XDMAC_GWAC_PW1_Msk & ((value) << XDMAC_GWAC_PW1_Pos)))
#define XDMAC_GWAC_PW2_Pos 8
#define XDMAC_GWAC_PW2_Msk (0xfu << XDMAC_GWAC_PW2_Pos) /**< \brief (XDMAC_GWAC) Pool Weight 2 */
#define XDMAC_GWAC_PW2(value) ((XDMAC_GWAC_PW2_Msk & ((value) << XDMAC_GWAC_PW2_Pos)))
#define XDMAC_GWAC_PW3_Pos 12
#define XDMAC_GWAC_PW3_Msk (0xfu << XDMAC_GWAC_PW3_Pos) /**< \brief (XDMAC_GWAC) Pool Weight 3 */
#define XDMAC_GWAC_PW3(value) ((XDMAC_GWAC_PW3_Msk & ((value) << XDMAC_GWAC_PW3_Pos)))
/* -------- XDMAC_GIE : (XDMAC Offset: 0x0C) Global Interrupt Enable Register -------- */
#define XDMAC_GIE_IE0 (0x1u << 0) /**< \brief (XDMAC_GIE) XDMAC Channel 0 Interrupt Enable Bit */
#define XDMAC_GIE_IE1 (0x1u << 1) /**< \brief (XDMAC_GIE) XDMAC Channel 1 Interrupt Enable Bit */
#define XDMAC_GIE_IE2 (0x1u << 2) /**< \brief (XDMAC_GIE) XDMAC Channel 2 Interrupt Enable Bit */
#define XDMAC_GIE_IE3 (0x1u << 3) /**< \brief (XDMAC_GIE) XDMAC Channel 3 Interrupt Enable Bit */
#define XDMAC_GIE_IE4 (0x1u << 4) /**< \brief (XDMAC_GIE) XDMAC Channel 4 Interrupt Enable Bit */
#define XDMAC_GIE_IE5 (0x1u << 5) /**< \brief (XDMAC_GIE) XDMAC Channel 5 Interrupt Enable Bit */
#define XDMAC_GIE_IE6 (0x1u << 6) /**< \brief (XDMAC_GIE) XDMAC Channel 6 Interrupt Enable Bit */
#define XDMAC_GIE_IE7 (0x1u << 7) /**< \brief (XDMAC_GIE) XDMAC Channel 7 Interrupt Enable Bit */
#define XDMAC_GIE_IE8 (0x1u << 8) /**< \brief (XDMAC_GIE) XDMAC Channel 8 Interrupt Enable Bit */
#define XDMAC_GIE_IE9 (0x1u << 9) /**< \brief (XDMAC_GIE) XDMAC Channel 9 Interrupt Enable Bit */
#define XDMAC_GIE_IE10 (0x1u << 10) /**< \brief (XDMAC_GIE) XDMAC Channel 10 Interrupt Enable Bit */
#define XDMAC_GIE_IE11 (0x1u << 11) /**< \brief (XDMAC_GIE) XDMAC Channel 11 Interrupt Enable Bit */
#define XDMAC_GIE_IE12 (0x1u << 12) /**< \brief (XDMAC_GIE) XDMAC Channel 12 Interrupt Enable Bit */
#define XDMAC_GIE_IE13 (0x1u << 13) /**< \brief (XDMAC_GIE) XDMAC Channel 13 Interrupt Enable Bit */
#define XDMAC_GIE_IE14 (0x1u << 14) /**< \brief (XDMAC_GIE) XDMAC Channel 14 Interrupt Enable Bit */
#define XDMAC_GIE_IE15 (0x1u << 15) /**< \brief (XDMAC_GIE) XDMAC Channel 15 Interrupt Enable Bit */
/* -------- XDMAC_GID : (XDMAC Offset: 0x10) Global Interrupt Disable Register -------- */
#define XDMAC_GID_ID0 (0x1u << 0) /**< \brief (XDMAC_GID) XDMAC Channel 0 Interrupt Disable Bit */
#define XDMAC_GID_ID1 (0x1u << 1) /**< \brief (XDMAC_GID) XDMAC Channel 1 Interrupt Disable Bit */
#define XDMAC_GID_ID2 (0x1u << 2) /**< \brief (XDMAC_GID) XDMAC Channel 2 Interrupt Disable Bit */
#define XDMAC_GID_ID3 (0x1u << 3) /**< \brief (XDMAC_GID) XDMAC Channel 3 Interrupt Disable Bit */
#define XDMAC_GID_ID4 (0x1u << 4) /**< \brief (XDMAC_GID) XDMAC Channel 4 Interrupt Disable Bit */
#define XDMAC_GID_ID5 (0x1u << 5) /**< \brief (XDMAC_GID) XDMAC Channel 5 Interrupt Disable Bit */
#define XDMAC_GID_ID6 (0x1u << 6) /**< \brief (XDMAC_GID) XDMAC Channel 6 Interrupt Disable Bit */
#define XDMAC_GID_ID7 (0x1u << 7) /**< \brief (XDMAC_GID) XDMAC Channel 7 Interrupt Disable Bit */
#define XDMAC_GID_ID8 (0x1u << 8) /**< \brief (XDMAC_GID) XDMAC Channel 8 Interrupt Disable Bit */
#define XDMAC_GID_ID9 (0x1u << 9) /**< \brief (XDMAC_GID) XDMAC Channel 9 Interrupt Disable Bit */
#define XDMAC_GID_ID10 (0x1u << 10) /**< \brief (XDMAC_GID) XDMAC Channel 10 Interrupt Disable Bit */
#define XDMAC_GID_ID11 (0x1u << 11) /**< \brief (XDMAC_GID) XDMAC Channel 11 Interrupt Disable Bit */
#define XDMAC_GID_ID12 (0x1u << 12) /**< \brief (XDMAC_GID) XDMAC Channel 12 Interrupt Disable Bit */
#define XDMAC_GID_ID13 (0x1u << 13) /**< \brief (XDMAC_GID) XDMAC Channel 13 Interrupt Disable Bit */
#define XDMAC_GID_ID14 (0x1u << 14) /**< \brief (XDMAC_GID) XDMAC Channel 14 Interrupt Disable Bit */
#define XDMAC_GID_ID15 (0x1u << 15) /**< \brief (XDMAC_GID) XDMAC Channel 15 Interrupt Disable Bit */
/* -------- XDMAC_GIM : (XDMAC Offset: 0x14) Global Interrupt Mask Register -------- */
#define XDMAC_GIM_IM0 (0x1u << 0) /**< \brief (XDMAC_GIM) XDMAC Channel 0 Interrupt Mask Bit */
#define XDMAC_GIM_IM1 (0x1u << 1) /**< \brief (XDMAC_GIM) XDMAC Channel 1 Interrupt Mask Bit */
#define XDMAC_GIM_IM2 (0x1u << 2) /**< \brief (XDMAC_GIM) XDMAC Channel 2 Interrupt Mask Bit */
#define XDMAC_GIM_IM3 (0x1u << 3) /**< \brief (XDMAC_GIM) XDMAC Channel 3 Interrupt Mask Bit */
#define XDMAC_GIM_IM4 (0x1u << 4) /**< \brief (XDMAC_GIM) XDMAC Channel 4 Interrupt Mask Bit */
#define XDMAC_GIM_IM5 (0x1u << 5) /**< \brief (XDMAC_GIM) XDMAC Channel 5 Interrupt Mask Bit */
#define XDMAC_GIM_IM6 (0x1u << 6) /**< \brief (XDMAC_GIM) XDMAC Channel 6 Interrupt Mask Bit */
#define XDMAC_GIM_IM7 (0x1u << 7) /**< \brief (XDMAC_GIM) XDMAC Channel 7 Interrupt Mask Bit */
#define XDMAC_GIM_IM8 (0x1u << 8) /**< \brief (XDMAC_GIM) XDMAC Channel 8 Interrupt Mask Bit */
#define XDMAC_GIM_IM9 (0x1u << 9) /**< \brief (XDMAC_GIM) XDMAC Channel 9 Interrupt Mask Bit */
#define XDMAC_GIM_IM10 (0x1u << 10) /**< \brief (XDMAC_GIM) XDMAC Channel 10 Interrupt Mask Bit */
#define XDMAC_GIM_IM11 (0x1u << 11) /**< \brief (XDMAC_GIM) XDMAC Channel 11 Interrupt Mask Bit */
#define XDMAC_GIM_IM12 (0x1u << 12) /**< \brief (XDMAC_GIM) XDMAC Channel 12 Interrupt Mask Bit */
#define XDMAC_GIM_IM13 (0x1u << 13) /**< \brief (XDMAC_GIM) XDMAC Channel 13 Interrupt Mask Bit */
#define XDMAC_GIM_IM14 (0x1u << 14) /**< \brief (XDMAC_GIM) XDMAC Channel 14 Interrupt Mask Bit */
#define XDMAC_GIM_IM15 (0x1u << 15) /**< \brief (XDMAC_GIM) XDMAC Channel 15 Interrupt Mask Bit */
/* -------- XDMAC_GIS : (XDMAC Offset: 0x18) Global Interrupt Status Register -------- */
#define XDMAC_GIS_IS0 (0x1u << 0) /**< \brief (XDMAC_GIS) XDMAC Channel 0 Interrupt Status Bit */
#define XDMAC_GIS_IS1 (0x1u << 1) /**< \brief (XDMAC_GIS) XDMAC Channel 1 Interrupt Status Bit */
#define XDMAC_GIS_IS2 (0x1u << 2) /**< \brief (XDMAC_GIS) XDMAC Channel 2 Interrupt Status Bit */
#define XDMAC_GIS_IS3 (0x1u << 3) /**< \brief (XDMAC_GIS) XDMAC Channel 3 Interrupt Status Bit */
#define XDMAC_GIS_IS4 (0x1u << 4) /**< \brief (XDMAC_GIS) XDMAC Channel 4 Interrupt Status Bit */
#define XDMAC_GIS_IS5 (0x1u << 5) /**< \brief (XDMAC_GIS) XDMAC Channel 5 Interrupt Status Bit */
#define XDMAC_GIS_IS6 (0x1u << 6) /**< \brief (XDMAC_GIS) XDMAC Channel 6 Interrupt Status Bit */
#define XDMAC_GIS_IS7 (0x1u << 7) /**< \brief (XDMAC_GIS) XDMAC Channel 7 Interrupt Status Bit */
#define XDMAC_GIS_IS8 (0x1u << 8) /**< \brief (XDMAC_GIS) XDMAC Channel 8 Interrupt Status Bit */
#define XDMAC_GIS_IS9 (0x1u << 9) /**< \brief (XDMAC_GIS) XDMAC Channel 9 Interrupt Status Bit */
#define XDMAC_GIS_IS10 (0x1u << 10) /**< \brief (XDMAC_GIS) XDMAC Channel 10 Interrupt Status Bit */
#define XDMAC_GIS_IS11 (0x1u << 11) /**< \brief (XDMAC_GIS) XDMAC Channel 11 Interrupt Status Bit */
#define XDMAC_GIS_IS12 (0x1u << 12) /**< \brief (XDMAC_GIS) XDMAC Channel 12 Interrupt Status Bit */
#define XDMAC_GIS_IS13 (0x1u << 13) /**< \brief (XDMAC_GIS) XDMAC Channel 13 Interrupt Status Bit */
#define XDMAC_GIS_IS14 (0x1u << 14) /**< \brief (XDMAC_GIS) XDMAC Channel 14 Interrupt Status Bit */
#define XDMAC_GIS_IS15 (0x1u << 15) /**< \brief (XDMAC_GIS) XDMAC Channel 15 Interrupt Status Bit */
/* -------- XDMAC_GE : (XDMAC Offset: 0x1C) Global Channel Enable Register -------- */
#define XDMAC_GE_EN0 (0x1u << 0) /**< \brief (XDMAC_GE) XDMAC Channel 0 Enable Bit */
#define XDMAC_GE_EN1 (0x1u << 1) /**< \brief (XDMAC_GE) XDMAC Channel 1 Enable Bit */
#define XDMAC_GE_EN2 (0x1u << 2) /**< \brief (XDMAC_GE) XDMAC Channel 2 Enable Bit */
#define XDMAC_GE_EN3 (0x1u << 3) /**< \brief (XDMAC_GE) XDMAC Channel 3 Enable Bit */
#define XDMAC_GE_EN4 (0x1u << 4) /**< \brief (XDMAC_GE) XDMAC Channel 4 Enable Bit */
#define XDMAC_GE_EN5 (0x1u << 5) /**< \brief (XDMAC_GE) XDMAC Channel 5 Enable Bit */
#define XDMAC_GE_EN6 (0x1u << 6) /**< \brief (XDMAC_GE) XDMAC Channel 6 Enable Bit */
#define XDMAC_GE_EN7 (0x1u << 7) /**< \brief (XDMAC_GE) XDMAC Channel 7 Enable Bit */
#define XDMAC_GE_EN8 (0x1u << 8) /**< \brief (XDMAC_GE) XDMAC Channel 8 Enable Bit */
#define XDMAC_GE_EN9 (0x1u << 9) /**< \brief (XDMAC_GE) XDMAC Channel 9 Enable Bit */
#define XDMAC_GE_EN10 (0x1u << 10) /**< \brief (XDMAC_GE) XDMAC Channel 10 Enable Bit */
#define XDMAC_GE_EN11 (0x1u << 11) /**< \brief (XDMAC_GE) XDMAC Channel 11 Enable Bit */
#define XDMAC_GE_EN12 (0x1u << 12) /**< \brief (XDMAC_GE) XDMAC Channel 12 Enable Bit */
#define XDMAC_GE_EN13 (0x1u << 13) /**< \brief (XDMAC_GE) XDMAC Channel 13 Enable Bit */
#define XDMAC_GE_EN14 (0x1u << 14) /**< \brief (XDMAC_GE) XDMAC Channel 14 Enable Bit */
#define XDMAC_GE_EN15 (0x1u << 15) /**< \brief (XDMAC_GE) XDMAC Channel 15 Enable Bit */
/* -------- XDMAC_GD : (XDMAC Offset: 0x20) Global Channel Disable Register -------- */
#define XDMAC_GD_DI0 (0x1u << 0) /**< \brief (XDMAC_GD) XDMAC Channel 0 Disable Bit */
#define XDMAC_GD_DI1 (0x1u << 1) /**< \brief (XDMAC_GD) XDMAC Channel 1 Disable Bit */
#define XDMAC_GD_DI2 (0x1u << 2) /**< \brief (XDMAC_GD) XDMAC Channel 2 Disable Bit */
#define XDMAC_GD_DI3 (0x1u << 3) /**< \brief (XDMAC_GD) XDMAC Channel 3 Disable Bit */
#define XDMAC_GD_DI4 (0x1u << 4) /**< \brief (XDMAC_GD) XDMAC Channel 4 Disable Bit */
#define XDMAC_GD_DI5 (0x1u << 5) /**< \brief (XDMAC_GD) XDMAC Channel 5 Disable Bit */
#define XDMAC_GD_DI6 (0x1u << 6) /**< \brief (XDMAC_GD) XDMAC Channel 6 Disable Bit */
#define XDMAC_GD_DI7 (0x1u << 7) /**< \brief (XDMAC_GD) XDMAC Channel 7 Disable Bit */
#define XDMAC_GD_DI8 (0x1u << 8) /**< \brief (XDMAC_GD) XDMAC Channel 8 Disable Bit */
#define XDMAC_GD_DI9 (0x1u << 9) /**< \brief (XDMAC_GD) XDMAC Channel 9 Disable Bit */
#define XDMAC_GD_DI10 (0x1u << 10) /**< \brief (XDMAC_GD) XDMAC Channel 10 Disable Bit */
#define XDMAC_GD_DI11 (0x1u << 11) /**< \brief (XDMAC_GD) XDMAC Channel 11 Disable Bit */
#define XDMAC_GD_DI12 (0x1u << 12) /**< \brief (XDMAC_GD) XDMAC Channel 12 Disable Bit */
#define XDMAC_GD_DI13 (0x1u << 13) /**< \brief (XDMAC_GD) XDMAC Channel 13 Disable Bit */
#define XDMAC_GD_DI14 (0x1u << 14) /**< \brief (XDMAC_GD) XDMAC Channel 14 Disable Bit */
#define XDMAC_GD_DI15 (0x1u << 15) /**< \brief (XDMAC_GD) XDMAC Channel 15 Disable Bit */
/* -------- XDMAC_GS : (XDMAC Offset: 0x24) Global Channel Status Register -------- */
#define XDMAC_GS_ST0 (0x1u << 0) /**< \brief (XDMAC_GS) XDMAC Channel 0 Status Bit */
#define XDMAC_GS_ST1 (0x1u << 1) /**< \brief (XDMAC_GS) XDMAC Channel 1 Status Bit */
#define XDMAC_GS_ST2 (0x1u << 2) /**< \brief (XDMAC_GS) XDMAC Channel 2 Status Bit */
#define XDMAC_GS_ST3 (0x1u << 3) /**< \brief (XDMAC_GS) XDMAC Channel 3 Status Bit */
#define XDMAC_GS_ST4 (0x1u << 4) /**< \brief (XDMAC_GS) XDMAC Channel 4 Status Bit */
#define XDMAC_GS_ST5 (0x1u << 5) /**< \brief (XDMAC_GS) XDMAC Channel 5 Status Bit */
#define XDMAC_GS_ST6 (0x1u << 6) /**< \brief (XDMAC_GS) XDMAC Channel 6 Status Bit */
#define XDMAC_GS_ST7 (0x1u << 7) /**< \brief (XDMAC_GS) XDMAC Channel 7 Status Bit */
#define XDMAC_GS_ST8 (0x1u << 8) /**< \brief (XDMAC_GS) XDMAC Channel 8 Status Bit */
#define XDMAC_GS_ST9 (0x1u << 9) /**< \brief (XDMAC_GS) XDMAC Channel 9 Status Bit */
#define XDMAC_GS_ST10 (0x1u << 10) /**< \brief (XDMAC_GS) XDMAC Channel 10 Status Bit */
#define XDMAC_GS_ST11 (0x1u << 11) /**< \brief (XDMAC_GS) XDMAC Channel 11 Status Bit */
#define XDMAC_GS_ST12 (0x1u << 12) /**< \brief (XDMAC_GS) XDMAC Channel 12 Status Bit */
#define XDMAC_GS_ST13 (0x1u << 13) /**< \brief (XDMAC_GS) XDMAC Channel 13 Status Bit */
#define XDMAC_GS_ST14 (0x1u << 14) /**< \brief (XDMAC_GS) XDMAC Channel 14 Status Bit */
#define XDMAC_GS_ST15 (0x1u << 15) /**< \brief (XDMAC_GS) XDMAC Channel 15 Status Bit */
/* -------- XDMAC_GRS : (XDMAC Offset: 0x28) Global Channel Read Suspend Register -------- */
#define XDMAC_GRS_RS0 (0x1u << 0) /**< \brief (XDMAC_GRS) XDMAC Channel 0 Read Suspend Bit */
#define XDMAC_GRS_RS1 (0x1u << 1) /**< \brief (XDMAC_GRS) XDMAC Channel 1 Read Suspend Bit */
#define XDMAC_GRS_RS2 (0x1u << 2) /**< \brief (XDMAC_GRS) XDMAC Channel 2 Read Suspend Bit */
#define XDMAC_GRS_RS3 (0x1u << 3) /**< \brief (XDMAC_GRS) XDMAC Channel 3 Read Suspend Bit */
#define XDMAC_GRS_RS4 (0x1u << 4) /**< \brief (XDMAC_GRS) XDMAC Channel 4 Read Suspend Bit */
#define XDMAC_GRS_RS5 (0x1u << 5) /**< \brief (XDMAC_GRS) XDMAC Channel 5 Read Suspend Bit */
#define XDMAC_GRS_RS6 (0x1u << 6) /**< \brief (XDMAC_GRS) XDMAC Channel 6 Read Suspend Bit */
#define XDMAC_GRS_RS7 (0x1u << 7) /**< \brief (XDMAC_GRS) XDMAC Channel 7 Read Suspend Bit */
#define XDMAC_GRS_RS8 (0x1u << 8) /**< \brief (XDMAC_GRS) XDMAC Channel 8 Read Suspend Bit */
#define XDMAC_GRS_RS9 (0x1u << 9) /**< \brief (XDMAC_GRS) XDMAC Channel 9 Read Suspend Bit */
#define XDMAC_GRS_RS10 (0x1u << 10) /**< \brief (XDMAC_GRS) XDMAC Channel 10 Read Suspend Bit */
#define XDMAC_GRS_RS11 (0x1u << 11) /**< \brief (XDMAC_GRS) XDMAC Channel 11 Read Suspend Bit */
#define XDMAC_GRS_RS12 (0x1u << 12) /**< \brief (XDMAC_GRS) XDMAC Channel 12 Read Suspend Bit */
#define XDMAC_GRS_RS13 (0x1u << 13) /**< \brief (XDMAC_GRS) XDMAC Channel 13 Read Suspend Bit */
#define XDMAC_GRS_RS14 (0x1u << 14) /**< \brief (XDMAC_GRS) XDMAC Channel 14 Read Suspend Bit */
#define XDMAC_GRS_RS15 (0x1u << 15) /**< \brief (XDMAC_GRS) XDMAC Channel 15 Read Suspend Bit */
/* -------- XDMAC_GWS : (XDMAC Offset: 0x2C) Global Channel Write Suspend Register -------- */
#define XDMAC_GWS_WS0 (0x1u << 0) /**< \brief (XDMAC_GWS) XDMAC Channel 0 Write Suspend Bit */
#define XDMAC_GWS_WS1 (0x1u << 1) /**< \brief (XDMAC_GWS) XDMAC Channel 1 Write Suspend Bit */
#define XDMAC_GWS_WS2 (0x1u << 2) /**< \brief (XDMAC_GWS) XDMAC Channel 2 Write Suspend Bit */
#define XDMAC_GWS_WS3 (0x1u << 3) /**< \brief (XDMAC_GWS) XDMAC Channel 3 Write Suspend Bit */
#define XDMAC_GWS_WS4 (0x1u << 4) /**< \brief (XDMAC_GWS) XDMAC Channel 4 Write Suspend Bit */
#define XDMAC_GWS_WS5 (0x1u << 5) /**< \brief (XDMAC_GWS) XDMAC Channel 5 Write Suspend Bit */
#define XDMAC_GWS_WS6 (0x1u << 6) /**< \brief (XDMAC_GWS) XDMAC Channel 6 Write Suspend Bit */
#define XDMAC_GWS_WS7 (0x1u << 7) /**< \brief (XDMAC_GWS) XDMAC Channel 7 Write Suspend Bit */
#define XDMAC_GWS_WS8 (0x1u << 8) /**< \brief (XDMAC_GWS) XDMAC Channel 8 Write Suspend Bit */
#define XDMAC_GWS_WS9 (0x1u << 9) /**< \brief (XDMAC_GWS) XDMAC Channel 9 Write Suspend Bit */
#define XDMAC_GWS_WS10 (0x1u << 10) /**< \brief (XDMAC_GWS) XDMAC Channel 10 Write Suspend Bit */
#define XDMAC_GWS_WS11 (0x1u << 11) /**< \brief (XDMAC_GWS) XDMAC Channel 11 Write Suspend Bit */
#define XDMAC_GWS_WS12 (0x1u << 12) /**< \brief (XDMAC_GWS) XDMAC Channel 12 Write Suspend Bit */
#define XDMAC_GWS_WS13 (0x1u << 13) /**< \brief (XDMAC_GWS) XDMAC Channel 13 Write Suspend Bit */
#define XDMAC_GWS_WS14 (0x1u << 14) /**< \brief (XDMAC_GWS) XDMAC Channel 14 Write Suspend Bit */
#define XDMAC_GWS_WS15 (0x1u << 15) /**< \brief (XDMAC_GWS) XDMAC Channel 15 Write Suspend Bit */
/* -------- XDMAC_GRWS : (XDMAC Offset: 0x30) Global Channel Read Write Suspend Register -------- */
#define XDMAC_GRWS_RWS0 (0x1u << 0) /**< \brief (XDMAC_GRWS) XDMAC Channel 0 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS1 (0x1u << 1) /**< \brief (XDMAC_GRWS) XDMAC Channel 1 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS2 (0x1u << 2) /**< \brief (XDMAC_GRWS) XDMAC Channel 2 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS3 (0x1u << 3) /**< \brief (XDMAC_GRWS) XDMAC Channel 3 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS4 (0x1u << 4) /**< \brief (XDMAC_GRWS) XDMAC Channel 4 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS5 (0x1u << 5) /**< \brief (XDMAC_GRWS) XDMAC Channel 5 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS6 (0x1u << 6) /**< \brief (XDMAC_GRWS) XDMAC Channel 6 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS7 (0x1u << 7) /**< \brief (XDMAC_GRWS) XDMAC Channel 7 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS8 (0x1u << 8) /**< \brief (XDMAC_GRWS) XDMAC Channel 8 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS9 (0x1u << 9) /**< \brief (XDMAC_GRWS) XDMAC Channel 9 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS10 (0x1u << 10) /**< \brief (XDMAC_GRWS) XDMAC Channel 10 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS11 (0x1u << 11) /**< \brief (XDMAC_GRWS) XDMAC Channel 11 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS12 (0x1u << 12) /**< \brief (XDMAC_GRWS) XDMAC Channel 12 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS13 (0x1u << 13) /**< \brief (XDMAC_GRWS) XDMAC Channel 13 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS14 (0x1u << 14) /**< \brief (XDMAC_GRWS) XDMAC Channel 14 Read Write Suspend Bit */
#define XDMAC_GRWS_RWS15 (0x1u << 15) /**< \brief (XDMAC_GRWS) XDMAC Channel 15 Read Write Suspend Bit */
/* -------- XDMAC_GRWR : (XDMAC Offset: 0x34) Global Channel Read Write Resume Register -------- */
#define XDMAC_GRWR_RWR0 (0x1u << 0) /**< \brief (XDMAC_GRWR) XDMAC Channel 0 Read Write Resume Bit */
#define XDMAC_GRWR_RWR1 (0x1u << 1) /**< \brief (XDMAC_GRWR) XDMAC Channel 1 Read Write Resume Bit */
#define XDMAC_GRWR_RWR2 (0x1u << 2) /**< \brief (XDMAC_GRWR) XDMAC Channel 2 Read Write Resume Bit */
#define XDMAC_GRWR_RWR3 (0x1u << 3) /**< \brief (XDMAC_GRWR) XDMAC Channel 3 Read Write Resume Bit */
#define XDMAC_GRWR_RWR4 (0x1u << 4) /**< \brief (XDMAC_GRWR) XDMAC Channel 4 Read Write Resume Bit */
#define XDMAC_GRWR_RWR5 (0x1u << 5) /**< \brief (XDMAC_GRWR) XDMAC Channel 5 Read Write Resume Bit */
#define XDMAC_GRWR_RWR6 (0x1u << 6) /**< \brief (XDMAC_GRWR) XDMAC Channel 6 Read Write Resume Bit */
#define XDMAC_GRWR_RWR7 (0x1u << 7) /**< \brief (XDMAC_GRWR) XDMAC Channel 7 Read Write Resume Bit */
#define XDMAC_GRWR_RWR8 (0x1u << 8) /**< \brief (XDMAC_GRWR) XDMAC Channel 8 Read Write Resume Bit */
#define XDMAC_GRWR_RWR9 (0x1u << 9) /**< \brief (XDMAC_GRWR) XDMAC Channel 9 Read Write Resume Bit */
#define XDMAC_GRWR_RWR10 (0x1u << 10) /**< \brief (XDMAC_GRWR) XDMAC Channel 10 Read Write Resume Bit */
#define XDMAC_GRWR_RWR11 (0x1u << 11) /**< \brief (XDMAC_GRWR) XDMAC Channel 11 Read Write Resume Bit */
#define XDMAC_GRWR_RWR12 (0x1u << 12) /**< \brief (XDMAC_GRWR) XDMAC Channel 12 Read Write Resume Bit */
#define XDMAC_GRWR_RWR13 (0x1u << 13) /**< \brief (XDMAC_GRWR) XDMAC Channel 13 Read Write Resume Bit */
#define XDMAC_GRWR_RWR14 (0x1u << 14) /**< \brief (XDMAC_GRWR) XDMAC Channel 14 Read Write Resume Bit */
#define XDMAC_GRWR_RWR15 (0x1u << 15) /**< \brief (XDMAC_GRWR) XDMAC Channel 15 Read Write Resume Bit */
/* -------- XDMAC_GSWR : (XDMAC Offset: 0x38) Global Channel Software Request Register -------- */
#define XDMAC_GSWR_SWREQ0 (0x1u << 0) /**< \brief (XDMAC_GSWR) XDMAC Channel 0 Software Request Bit */
#define XDMAC_GSWR_SWREQ1 (0x1u << 1) /**< \brief (XDMAC_GSWR) XDMAC Channel 1 Software Request Bit */
#define XDMAC_GSWR_SWREQ2 (0x1u << 2) /**< \brief (XDMAC_GSWR) XDMAC Channel 2 Software Request Bit */
#define XDMAC_GSWR_SWREQ3 (0x1u << 3) /**< \brief (XDMAC_GSWR) XDMAC Channel 3 Software Request Bit */
#define XDMAC_GSWR_SWREQ4 (0x1u << 4) /**< \brief (XDMAC_GSWR) XDMAC Channel 4 Software Request Bit */
#define XDMAC_GSWR_SWREQ5 (0x1u << 5) /**< \brief (XDMAC_GSWR) XDMAC Channel 5 Software Request Bit */
#define XDMAC_GSWR_SWREQ6 (0x1u << 6) /**< \brief (XDMAC_GSWR) XDMAC Channel 6 Software Request Bit */
#define XDMAC_GSWR_SWREQ7 (0x1u << 7) /**< \brief (XDMAC_GSWR) XDMAC Channel 7 Software Request Bit */
#define XDMAC_GSWR_SWREQ8 (0x1u << 8) /**< \brief (XDMAC_GSWR) XDMAC Channel 8 Software Request Bit */
#define XDMAC_GSWR_SWREQ9 (0x1u << 9) /**< \brief (XDMAC_GSWR) XDMAC Channel 9 Software Request Bit */
#define XDMAC_GSWR_SWREQ10 (0x1u << 10) /**< \brief (XDMAC_GSWR) XDMAC Channel 10 Software Request Bit */
#define XDMAC_GSWR_SWREQ11 (0x1u << 11) /**< \brief (XDMAC_GSWR) XDMAC Channel 11 Software Request Bit */
#define XDMAC_GSWR_SWREQ12 (0x1u << 12) /**< \brief (XDMAC_GSWR) XDMAC Channel 12 Software Request Bit */
#define XDMAC_GSWR_SWREQ13 (0x1u << 13) /**< \brief (XDMAC_GSWR) XDMAC Channel 13 Software Request Bit */
#define XDMAC_GSWR_SWREQ14 (0x1u << 14) /**< \brief (XDMAC_GSWR) XDMAC Channel 14 Software Request Bit */
#define XDMAC_GSWR_SWREQ15 (0x1u << 15) /**< \brief (XDMAC_GSWR) XDMAC Channel 15 Software Request Bit */
/* -------- XDMAC_GSWS : (XDMAC Offset: 0x3C) Global Channel Software Request Status Register -------- */
#define XDMAC_GSWS_SWRS0 (0x1u << 0) /**< \brief (XDMAC_GSWS) XDMAC Channel 0 Software Request Status Bit */
#define XDMAC_GSWS_SWRS1 (0x1u << 1) /**< \brief (XDMAC_GSWS) XDMAC Channel 1 Software Request Status Bit */
#define XDMAC_GSWS_SWRS2 (0x1u << 2) /**< \brief (XDMAC_GSWS) XDMAC Channel 2 Software Request Status Bit */
#define XDMAC_GSWS_SWRS3 (0x1u << 3) /**< \brief (XDMAC_GSWS) XDMAC Channel 3 Software Request Status Bit */
#define XDMAC_GSWS_SWRS4 (0x1u << 4) /**< \brief (XDMAC_GSWS) XDMAC Channel 4 Software Request Status Bit */
#define XDMAC_GSWS_SWRS5 (0x1u << 5) /**< \brief (XDMAC_GSWS) XDMAC Channel 5 Software Request Status Bit */
#define XDMAC_GSWS_SWRS6 (0x1u << 6) /**< \brief (XDMAC_GSWS) XDMAC Channel 6 Software Request Status Bit */
#define XDMAC_GSWS_SWRS7 (0x1u << 7) /**< \brief (XDMAC_GSWS) XDMAC Channel 7 Software Request Status Bit */
#define XDMAC_GSWS_SWRS8 (0x1u << 8) /**< \brief (XDMAC_GSWS) XDMAC Channel 8 Software Request Status Bit */
#define XDMAC_GSWS_SWRS9 (0x1u << 9) /**< \brief (XDMAC_GSWS) XDMAC Channel 9 Software Request Status Bit */
#define XDMAC_GSWS_SWRS10 (0x1u << 10) /**< \brief (XDMAC_GSWS) XDMAC Channel 10 Software Request Status Bit */
#define XDMAC_GSWS_SWRS11 (0x1u << 11) /**< \brief (XDMAC_GSWS) XDMAC Channel 11 Software Request Status Bit */
#define XDMAC_GSWS_SWRS12 (0x1u << 12) /**< \brief (XDMAC_GSWS) XDMAC Channel 12 Software Request Status Bit */
#define XDMAC_GSWS_SWRS13 (0x1u << 13) /**< \brief (XDMAC_GSWS) XDMAC Channel 13 Software Request Status Bit */
#define XDMAC_GSWS_SWRS14 (0x1u << 14) /**< \brief (XDMAC_GSWS) XDMAC Channel 14 Software Request Status Bit */
#define XDMAC_GSWS_SWRS15 (0x1u << 15) /**< \brief (XDMAC_GSWS) XDMAC Channel 15 Software Request Status Bit */
/* -------- XDMAC_GSWF : (XDMAC Offset: 0x40) Global Channel Software Flush Request Register -------- */
#define XDMAC_GSWF_SWF0 (0x1u << 0) /**< \brief (XDMAC_GSWF) XDMAC Channel 0 Software Flush Request Bit */
#define XDMAC_GSWF_SWF1 (0x1u << 1) /**< \brief (XDMAC_GSWF) XDMAC Channel 1 Software Flush Request Bit */
#define XDMAC_GSWF_SWF2 (0x1u << 2) /**< \brief (XDMAC_GSWF) XDMAC Channel 2 Software Flush Request Bit */
#define XDMAC_GSWF_SWF3 (0x1u << 3) /**< \brief (XDMAC_GSWF) XDMAC Channel 3 Software Flush Request Bit */
#define XDMAC_GSWF_SWF4 (0x1u << 4) /**< \brief (XDMAC_GSWF) XDMAC Channel 4 Software Flush Request Bit */
#define XDMAC_GSWF_SWF5 (0x1u << 5) /**< \brief (XDMAC_GSWF) XDMAC Channel 5 Software Flush Request Bit */
#define XDMAC_GSWF_SWF6 (0x1u << 6) /**< \brief (XDMAC_GSWF) XDMAC Channel 6 Software Flush Request Bit */
#define XDMAC_GSWF_SWF7 (0x1u << 7) /**< \brief (XDMAC_GSWF) XDMAC Channel 7 Software Flush Request Bit */
#define XDMAC_GSWF_SWF8 (0x1u << 8) /**< \brief (XDMAC_GSWF) XDMAC Channel 8 Software Flush Request Bit */
#define XDMAC_GSWF_SWF9 (0x1u << 9) /**< \brief (XDMAC_GSWF) XDMAC Channel 9 Software Flush Request Bit */
#define XDMAC_GSWF_SWF10 (0x1u << 10) /**< \brief (XDMAC_GSWF) XDMAC Channel 10 Software Flush Request Bit */
#define XDMAC_GSWF_SWF11 (0x1u << 11) /**< \brief (XDMAC_GSWF) XDMAC Channel 11 Software Flush Request Bit */
#define XDMAC_GSWF_SWF12 (0x1u << 12) /**< \brief (XDMAC_GSWF) XDMAC Channel 12 Software Flush Request Bit */
#define XDMAC_GSWF_SWF13 (0x1u << 13) /**< \brief (XDMAC_GSWF) XDMAC Channel 13 Software Flush Request Bit */
#define XDMAC_GSWF_SWF14 (0x1u << 14) /**< \brief (XDMAC_GSWF) XDMAC Channel 14 Software Flush Request Bit */
#define XDMAC_GSWF_SWF15 (0x1u << 15) /**< \brief (XDMAC_GSWF) XDMAC Channel 15 Software Flush Request Bit */
/* -------- XDMAC_CIE : (XDMAC Offset: N/A) Channel Interrupt Enable Register -------- */
#define XDMAC_CIE_BIE (0x1u << 0) /**< \brief (XDMAC_CIE) End of Block Interrupt Enable Bit */
#define XDMAC_CIE_LIE (0x1u << 1) /**< \brief (XDMAC_CIE) End of Linked List Interrupt Enable Bit */
#define XDMAC_CIE_DIE (0x1u << 2) /**< \brief (XDMAC_CIE) End of Disable Interrupt Enable Bit */
#define XDMAC_CIE_FIE (0x1u << 3) /**< \brief (XDMAC_CIE) End of Flush Interrupt Enable Bit */
#define XDMAC_CIE_RBIE (0x1u << 4) /**< \brief (XDMAC_CIE) Read Bus Error Interrupt Enable Bit */
#define XDMAC_CIE_WBIE (0x1u << 5) /**< \brief (XDMAC_CIE) Write Bus Error Interrupt Enable Bit */
#define XDMAC_CIE_ROIE (0x1u << 6) /**< \brief (XDMAC_CIE) Request Overflow Error Interrupt Enable Bit */
/* -------- XDMAC_CID : (XDMAC Offset: N/A) Channel Interrupt Disable Register -------- */
#define XDMAC_CID_BID (0x1u << 0) /**< \brief (XDMAC_CID) End of Block Interrupt Disable Bit */
#define XDMAC_CID_LID (0x1u << 1) /**< \brief (XDMAC_CID) End of Linked List Interrupt Disable Bit */
#define XDMAC_CID_DID (0x1u << 2) /**< \brief (XDMAC_CID) End of Disable Interrupt Disable Bit */
#define XDMAC_CID_FID (0x1u << 3) /**< \brief (XDMAC_CID) End of Flush Interrupt Disable Bit */
#define XDMAC_CID_RBEID (0x1u << 4) /**< \brief (XDMAC_CID) Read Bus Error Interrupt Disable Bit */
#define XDMAC_CID_WBEID (0x1u << 5) /**< \brief (XDMAC_CID) Write Bus Error Interrupt Disable Bit */
#define XDMAC_CID_ROID (0x1u << 6) /**< \brief (XDMAC_CID) Request Overflow Error Interrupt Disable Bit */
/* -------- XDMAC_CIM : (XDMAC Offset: N/A) Channel Interrupt Mask Register -------- */
#define XDMAC_CIM_BIM (0x1u << 0) /**< \brief (XDMAC_CIM) End of Block Interrupt Mask Bit */
#define XDMAC_CIM_LIM (0x1u << 1) /**< \brief (XDMAC_CIM) End of Linked List Interrupt Mask Bit */
#define XDMAC_CIM_DIM (0x1u << 2) /**< \brief (XDMAC_CIM) End of Disable Interrupt Mask bit */
#define XDMAC_CIM_FIM (0x1u << 3) /**< \brief (XDMAC_CIM) End of Flush Interrupt Mask Bit */
#define XDMAC_CIM_RBEIM (0x1u << 4) /**< \brief (XDMAC_CIM) Read Bus Error Interrupt Mask Bit */
#define XDMAC_CIM_WBEIM (0x1u << 5) /**< \brief (XDMAC_CIM) Write Bus Error Interrupt Mask Bit */
#define XDMAC_CIM_ROIM (0x1u << 6) /**< \brief (XDMAC_CIM) Request Overflow Error Interrupt Mask Bit */
/* -------- XDMAC_CIS : (XDMAC Offset: N/A) Channel Interrupt Status Register -------- */
#define XDMAC_CIS_BIS (0x1u << 0) /**< \brief (XDMAC_CIS) End of Block Interrupt Status Bit */
#define XDMAC_CIS_LIS (0x1u << 1) /**< \brief (XDMAC_CIS) End of Linked List Interrupt Status Bit */
#define XDMAC_CIS_DIS (0x1u << 2) /**< \brief (XDMAC_CIS) End of Disable Interrupt Status Bit */
#define XDMAC_CIS_FIS (0x1u << 3) /**< \brief (XDMAC_CIS) End of Flush Interrupt Status Bit */
#define XDMAC_CIS_RBEIS (0x1u << 4) /**< \brief (XDMAC_CIS) Read Bus Error Interrupt Status Bit */
#define XDMAC_CIS_WBEIS (0x1u << 5) /**< \brief (XDMAC_CIS) Write Bus Error Interrupt Status Bit */
#define XDMAC_CIS_ROIS (0x1u << 6) /**< \brief (XDMAC_CIS) Request Overflow Error Interrupt Status Bit */
/* -------- XDMAC_CSA : (XDMAC Offset: N/A) Channel Source Address Register -------- */
#define XDMAC_CSA_SA_Pos 0
#define XDMAC_CSA_SA_Msk (0xffffffffu << XDMAC_CSA_SA_Pos) /**< \brief (XDMAC_CSA) Channel x Source Address */
#define XDMAC_CSA_SA(value) ((XDMAC_CSA_SA_Msk & ((value) << XDMAC_CSA_SA_Pos)))
/* -------- XDMAC_CDA : (XDMAC Offset: N/A) Channel Destination Address Register -------- */
#define XDMAC_CDA_DA_Pos 0
#define XDMAC_CDA_DA_Msk (0xffffffffu << XDMAC_CDA_DA_Pos) /**< \brief (XDMAC_CDA) Channel x Destination Address */
#define XDMAC_CDA_DA(value) ((XDMAC_CDA_DA_Msk & ((value) << XDMAC_CDA_DA_Pos)))
/* -------- XDMAC_CNDA : (XDMAC Offset: N/A) Channel Next Descriptor Address Register -------- */
#define XDMAC_CNDA_NDAIF (0x1u << 0) /**< \brief (XDMAC_CNDA) Channel x Next Descriptor Interface */
#define XDMAC_CNDA_NDA_Pos 2
#define XDMAC_CNDA_NDA_Msk (0x3fffffffu << XDMAC_CNDA_NDA_Pos) /**< \brief (XDMAC_CNDA) Channel x Next Descriptor Address */
#define XDMAC_CNDA_NDA(value) ((XDMAC_CNDA_NDA_Msk & ((value) << XDMAC_CNDA_NDA_Pos)))
/* -------- XDMAC_CNDC : (XDMAC Offset: N/A) Channel Next Descriptor Control Register -------- */
#define XDMAC_CNDC_NDE (0x1u << 0) /**< \brief (XDMAC_CNDC) Channel x Next Descriptor Enable */
#define   XDMAC_CNDC_NDE_DSCR_FETCH_DIS (0x0u << 0) /**< \brief (XDMAC_CNDC) Descriptor fetch is disabled */
#define   XDMAC_CNDC_NDE_DSCR_FETCH_EN (0x1u << 0) /**< \brief (XDMAC_CNDC) Descriptor fetch is enabled */
#define XDMAC_CNDC_NDSUP (0x1u << 1) /**< \brief (XDMAC_CNDC) Channel x Next Descriptor Source Update */
#define   XDMAC_CNDC_NDSUP_SRC_PARAMS_UNCHANGED (0x0u << 1) /**< \brief (XDMAC_CNDC) Source parameters remain unchanged. */
#define   XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED (0x1u << 1) /**< \brief (XDMAC_CNDC) Source parameters are updated when the descriptor is retrieved. */
#define XDMAC_CNDC_NDDUP (0x1u << 2) /**< \brief (XDMAC_CNDC) Channel x Next Descriptor Destination Update */
#define   XDMAC_CNDC_NDDUP_DST_PARAMS_UNCHANGED (0x0u << 2) /**< \brief (XDMAC_CNDC) Destination parameters remain unchanged. */
#define   XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED (0x1u << 2) /**< \brief (XDMAC_CNDC) Destination parameters are updated when the descriptor is retrieved. */
#define XDMAC_CNDC_NDVIEW_Pos 3
#define XDMAC_CNDC_NDVIEW_Msk (0x3u << XDMAC_CNDC_NDVIEW_Pos) /**< \brief (XDMAC_CNDC) Channel x Next Descriptor View */
#define   XDMAC_CNDC_NDVIEW_NDV0 (0x0u << 3) /**< \brief (XDMAC_CNDC) Next Descriptor View 0 */
#define   XDMAC_CNDC_NDVIEW_NDV1 (0x1u << 3) /**< \brief (XDMAC_CNDC) Next Descriptor View 1 */
#define   XDMAC_CNDC_NDVIEW_NDV2 (0x2u << 3) /**< \brief (XDMAC_CNDC) Next Descriptor View 2 */
#define   XDMAC_CNDC_NDVIEW_NDV3 (0x3u << 3) /**< \brief (XDMAC_CNDC) Next Descriptor View 3 */
/* -------- XDMAC_CUBC : (XDMAC Offset: N/A) Channel Microblock Control Register -------- */
#define XDMAC_CUBC_UBLEN_Pos 0
#define XDMAC_CUBC_UBLEN_Msk (0xffffffu << XDMAC_CUBC_UBLEN_Pos) /**< \brief (XDMAC_CUBC) Channel x Microblock Length */
#define XDMAC_CUBC_UBLEN(value) ((XDMAC_CUBC_UBLEN_Msk & ((value) << XDMAC_CUBC_UBLEN_Pos)))
/* -------- XDMAC_CBC : (XDMAC Offset: N/A) Channel Block Control Register -------- */
#define XDMAC_CBC_BLEN_Pos 0
#define XDMAC_CBC_BLEN_Msk (0xfffu << XDMAC_CBC_BLEN_Pos) /**< \brief (XDMAC_CBC) Channel x Block Length */
#define XDMAC_CBC_BLEN(value) ((XDMAC_CBC_BLEN_Msk & ((value) << XDMAC_CBC_BLEN_Pos)))
/* -------- XDMAC_CC : (XDMAC Offset: N/A) Channel Configuration Register -------- */
#define XDMAC_CC_TYPE (0x1u << 0) /**< \brief (XDMAC_CC) Channel x Transfer Type */
#define   XDMAC_CC_TYPE_MEM_TRAN (0x0u << 0) /**< \brief (XDMAC_CC) Self triggered mode (Memory to Memory Transfer). */
#define   XDMAC_CC_TYPE_PER_TRAN (0x1u << 0) /**< \brief (XDMAC_CC) Synchronized mode (Peripheral to Memory or Memory to Peripheral Transfer). */
#define XDMAC_CC_MBSIZE_Pos 1
#define XDMAC_CC_MBSIZE_Msk (0x3u << XDMAC_CC_MBSIZE_Pos) /**< \brief (XDMAC_CC) Channel x Memory Burst Size */
#define   XDMAC_CC_MBSIZE_SINGLE (0x0u << 1) /**< \brief (XDMAC_CC) The memory burst size is set to one. */
#define   XDMAC_CC_MBSIZE_FOUR (0x1u << 1) /**< \brief (XDMAC_CC) The memory burst size is set to four. */
#define   XDMAC_CC_MBSIZE_EIGHT (0x2u << 1) /**< \brief (XDMAC_CC) The memory burst size is set to eight. */
#define   XDMAC_CC_MBSIZE_SIXTEEN (0x3u << 1) /**< \brief (XDMAC_CC) The memory burst size is set to sixteen. */
#define XDMAC_CC_DSYNC (0x1u << 4) /**< \brief (XDMAC_CC) Channel x Synchronization */
#define   XDMAC_CC_DSYNC_PER2MEM (0x0u << 4) /**< \brief (XDMAC_CC) Peripheral to Memory transfer */
#define   XDMAC_CC_DSYNC_MEM2PER (0x1u << 4) /**< \brief (XDMAC_CC) Memory to Peripheral transfer */
#define XDMAC_CC_PROT (0x1u << 5) /**< \brief (XDMAC_CC) Channel x Protection */
#define   XDMAC_CC_PROT_SEC (0x0u << 5) /**< \brief (XDMAC_CC) Channel is secured */
#define   XDMAC_CC_PROT_UNSEC (0x1u << 5) /**< \brief (XDMAC_CC) Channel is unsecured */
#define XDMAC_CC_SWREQ (0x1u << 6) /**< \brief (XDMAC_CC) Channel x Software Request Trigger */
#define   XDMAC_CC_SWREQ_HWR_CONNECTED (0x0u << 6) /**< \brief (XDMAC_CC) Hardware request line is connected to the peripheral request line. */
#define   XDMAC_CC_SWREQ_SWR_CONNECTED (0x1u << 6) /**< \brief (XDMAC_CC) Software request is connected to the peripheral request line. */
#define XDMAC_CC_MEMSET (0x1u << 7) /**< \brief (XDMAC_CC) Channel x Fill Block of memory */
#define   XDMAC_CC_MEMSET_NORMAL_MODE (0x0u << 7) /**< \brief (XDMAC_CC) Memset is not activated */
#define   XDMAC_CC_MEMSET_HW_MODE (0x1u << 7) /**< \brief (XDMAC_CC) Sets the block of memory pointed by DA field to the specified value. This operation is performed on 8, 16 or 32 bits basis. */
#define XDMAC_CC_CSIZE_Pos 8
#define XDMAC_CC_CSIZE_Msk (0x7u << XDMAC_CC_CSIZE_Pos) /**< \brief (XDMAC_CC) Channel x Chunk Size */
#define   XDMAC_CC_CSIZE_CHK_1 (0x0u << 8) /**< \brief (XDMAC_CC) 1 data transferred */
#define   XDMAC_CC_CSIZE_CHK_2 (0x1u << 8) /**< \brief (XDMAC_CC) 2 data transferred */
#define   XDMAC_CC_CSIZE_CHK_4 (0x2u << 8) /**< \brief (XDMAC_CC) 4 data transferred */
#define   XDMAC_CC_CSIZE_CHK_8 (0x3u << 8) /**< \brief (XDMAC_CC) 8 data transferred */
#define   XDMAC_CC_CSIZE_CHK_16 (0x4u << 8) /**< \brief (XDMAC_CC) 16 data transferred */
#define XDMAC_CC_DWIDTH_Pos 11
#define XDMAC_CC_DWIDTH_Msk (0x3u << XDMAC_CC_DWIDTH_Pos) /**< \brief (XDMAC_CC) Channel x Data Width */
#define   XDMAC_CC_DWIDTH_BYTE (0x0u << 11) /**< \brief (XDMAC_CC) The data size is set to 8 bits */
#define   XDMAC_CC_DWIDTH_HALFWORD (0x1u << 11) /**< \brief (XDMAC_CC) The data size is set to 16 bits */
#define   XDMAC_CC_DWIDTH_WORD (0x2u << 11) /**< \brief (XDMAC_CC) The data size is set to 32 bits */
#define   XDMAC_CC_DWIDTH_DWORD (0x3u << 11) /**< \brief (XDMAC_CC) The data size is set to 64bits */
#define XDMAC_CC_SIF (0x1u << 13) /**< \brief (XDMAC_CC) Channel x Source Interface Identifier */
#define   XDMAC_CC_SIF_AHB_IF0 (0x0u << 13) /**< \brief (XDMAC_CC) The data is read through the system bus interface 0 */
#define   XDMAC_CC_SIF_AHB_IF1 (0x1u << 13) /**< \brief (XDMAC_CC) The data is read through the system bus interface 1 */
#define XDMAC_CC_DIF (0x1u << 14) /**< \brief (XDMAC_CC) Channel x Destination Interface Identifier */
#define   XDMAC_CC_DIF_AHB_IF0 (0x0u << 14) /**< \brief (XDMAC_CC) The data is written through the system bus interface 0 */
#define   XDMAC_CC_DIF_AHB_IF1 (0x1u << 14) /**< \brief (XDMAC_CC) The data is written though the system bus interface 1 */
#define XDMAC_CC_SAM_Pos 16
#define XDMAC_CC_SAM_Msk (0x3u << XDMAC_CC_SAM_Pos) /**< \brief (XDMAC_CC) Channel x Source Addressing Mode */
#define   XDMAC_CC_SAM_FIXED_AM (0x0u << 16) /**< \brief (XDMAC_CC) The address remains unchanged. */
#define   XDMAC_CC_SAM_INCREMENTED_AM (0x1u << 16) /**< \brief (XDMAC_CC) The addressing mode is incremented (the increment size is set to the data size). */
#define   XDMAC_CC_SAM_UBS_AM (0x2u << 16) /**< \brief (XDMAC_CC) The microblock stride is added at the microblock boundary. */
#define   XDMAC_CC_SAM_UBS_DS_AM (0x3u << 16) /**< \brief (XDMAC_CC) The microblock stride is added at the microblock boundary, the data stride is added at the data boundary. */
#define XDMAC_CC_DAM_Pos 18
#define XDMAC_CC_DAM_Msk (0x3u << XDMAC_CC_DAM_Pos) /**< \brief (XDMAC_CC) Channel x Destination Addressing Mode */
#define   XDMAC_CC_DAM_FIXED_AM (0x0u << 18) /**< \brief (XDMAC_CC) The address remains unchanged. */
#define   XDMAC_CC_DAM_INCREMENTED_AM (0x1u << 18) /**< \brief (XDMAC_CC) The addressing mode is incremented (the increment size is set to the data size). */
#define   XDMAC_CC_DAM_UBS_AM (0x2u << 18) /**< \brief (XDMAC_CC) The microblock stride is added at the microblock boundary. */
#define   XDMAC_CC_DAM_UBS_DS_AM (0x3u << 18) /**< \brief (XDMAC_CC) The microblock stride is added at the microblock boundary, the data stride is added at the data boundary. */
#define XDMAC_CC_INITD (0x1u << 21) /**< \brief (XDMAC_CC) Channel Initialization Terminated (this bit is read only) */
#define   XDMAC_CC_INITD_TERMINATED (0x0u << 21) /**< \brief (XDMAC_CC) Channel initialization is in progress. */
#define   XDMAC_CC_INITD_IN_PROGRESS (0x1u << 21) /**< \brief (XDMAC_CC) Channel initialization is completed. */
#define XDMAC_CC_RDIP (0x1u << 22) /**< \brief (XDMAC_CC) Read in Progress (this bit is read only) */
#define   XDMAC_CC_RDIP_DONE (0x0u << 22) /**< \brief (XDMAC_CC) No Active read transaction on the bus. */
#define   XDMAC_CC_RDIP_IN_PROGRESS (0x1u << 22) /**< \brief (XDMAC_CC) A read transaction is in progress. */
#define XDMAC_CC_WRIP (0x1u << 23) /**< \brief (XDMAC_CC) Write in Progress (this bit is read only) */
#define   XDMAC_CC_WRIP_DONE (0x0u << 23) /**< \brief (XDMAC_CC) No Active write transaction on the bus. */
#define   XDMAC_CC_WRIP_IN_PROGRESS (0x1u << 23) /**< \brief (XDMAC_CC) A Write transaction is in progress. */
#define XDMAC_CC_PERID_Pos 24
#define XDMAC_CC_PERID_Msk (0x7fu << XDMAC_CC_PERID_Pos) /**< \brief (XDMAC_CC) Channel x Peripheral Identifier */
#define XDMAC_CC_PERID(value) ((XDMAC_CC_PERID_Msk & ((value) << XDMAC_CC_PERID_Pos)))
/* -------- XDMAC_CDS_MSP : (XDMAC Offset: N/A) Channel Data Stride Memory Set Pattern -------- */
#define XDMAC_CDS_MSP_SDS_MSP_Pos 0
#define XDMAC_CDS_MSP_SDS_MSP_Msk (0xffffu << XDMAC_CDS_MSP_SDS_MSP_Pos) /**< \brief (XDMAC_CDS_MSP) Channel x Source Data stride or Memory Set Pattern */
#define XDMAC_CDS_MSP_SDS_MSP(value) ((XDMAC_CDS_MSP_SDS_MSP_Msk & ((value) << XDMAC_CDS_MSP_SDS_MSP_Pos)))
#define XDMAC_CDS_MSP_DDS_MSP_Pos 16
#define XDMAC_CDS_MSP_DDS_MSP_Msk (0xffffu << XDMAC_CDS_MSP_DDS_MSP_Pos) /**< \brief (XDMAC_CDS_MSP) Channel x Destination Data Stride or Memory Set Pattern */
#define XDMAC_CDS_MSP_DDS_MSP(value) ((XDMAC_CDS_MSP_DDS_MSP_Msk & ((value) << XDMAC_CDS_MSP_DDS_MSP_Pos)))
/* -------- XDMAC_CSUS : (XDMAC Offset: N/A) Channel Source Microblock Stride -------- */
#define XDMAC_CSUS_SUBS_Pos 0
#define XDMAC_CSUS_SUBS_Msk (0xffffffu << XDMAC_CSUS_SUBS_Pos) /**< \brief (XDMAC_CSUS) Channel x Source Microblock Stride */
#define XDMAC_CSUS_SUBS(value) ((XDMAC_CSUS_SUBS_Msk & ((value) << XDMAC_CSUS_SUBS_Pos)))
/* -------- XDMAC_CDUS : (XDMAC Offset: N/A) Channel Destination Microblock Stride -------- */
#define XDMAC_CDUS_DUBS_Pos 0
#define XDMAC_CDUS_DUBS_Msk (0xffffffu << XDMAC_CDUS_DUBS_Pos) /**< \brief (XDMAC_CDUS) Channel x Destination Microblock Stride */
#define XDMAC_CDUS_DUBS(value) ((XDMAC_CDUS_DUBS_Msk & ((value) << XDMAC_CDUS_DUBS_Pos)))

/*@}*/

/*@}*/

/* ************************************************************************** */
/*   REGISTER ACCESS DEFINITIONS FOR SAMA5D4 */
/* ************************************************************************** */
/** \addtogroup SAMA5D4_reg Registers Access Definitions */
/*@{*/

/* ========== Register definition for AXIMX peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_AXIMX_REMAP                 (0x00700000U) /**< \brief (AXIMX) Remap Register */
#else
  #define REG_AXIMX_REMAP (*(__O uint32_t*)0x00700000U) /**< \brief (AXIMX) Remap Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for SMD peripheral ========== */

/* ========== Register definition for XDMAC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_XDMAC1_GTYPE                      (0xF0004000U) /**< \brief (XDMAC1) Global Type register */
  #define REG_XDMAC1_GCFG                       (0xF0004004U) /**< \brief (XDMAC1) Global Configuration Register */
  #define REG_XDMAC1_GWAC                       (0xF0004008U) /**< \brief (XDMAC1) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC1_GIE                        (0xF000400CU) /**< \brief (XDMAC1) Global Interrupt Enable Register */
  #define REG_XDMAC1_GID                        (0xF0004010U) /**< \brief (XDMAC1) Global Interrupt Disable Register */
  #define REG_XDMAC1_GIM                        (0xF0004014U) /**< \brief (XDMAC1) Global Interrupt Mask Register */
  #define REG_XDMAC1_GIS                        (0xF0004018U) /**< \brief (XDMAC1) Global Interrupt Status Register */
  #define REG_XDMAC1_GE                         (0xF000401CU) /**< \brief (XDMAC1) Global Channel Enable Register */
  #define REG_XDMAC1_GD                         (0xF0004020U) /**< \brief (XDMAC1) Global Channel Disable Register */
  #define REG_XDMAC1_GS                         (0xF0004024U) /**< \brief (XDMAC1) Global Channel Status Register */
  #define REG_XDMAC1_GRS                        (0xF0004028U) /**< \brief (XDMAC1) Global Channel Read Suspend Register */
  #define REG_XDMAC1_GWS                        (0xF000402CU) /**< \brief (XDMAC1) Global Channel Write Suspend Register */
  #define REG_XDMAC1_GRWS                       (0xF0004030U) /**< \brief (XDMAC1) Global Channel Read Write Suspend Register */
  #define REG_XDMAC1_GRWR                       (0xF0004034U) /**< \brief (XDMAC1) Global Channel Read Write Resume Register */
  #define REG_XDMAC1_GSWR                       (0xF0004038U) /**< \brief (XDMAC1) Global Channel Software Request Register */
  #define REG_XDMAC1_GSWS                       (0xF000403CU) /**< \brief (XDMAC1) Global Channel Software Request Status Register */
  #define REG_XDMAC1_GSWF                       (0xF0004040U) /**< \brief (XDMAC1) Global Channel Software Flush Request Register */
  #define REG_XDMAC1_CIE0                       (0xF0004050U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC1_CID0                       (0xF0004054U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC1_CIM0                       (0xF0004058U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC1_CIS0                       (0xF000405CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC1_CSA0                       (0xF0004060U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC1_CDA0                       (0xF0004064U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC1_CNDA0                      (0xF0004068U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC1_CNDC0                      (0xF000406CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC1_CUBC0                      (0xF0004070U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC1_CBC0                       (0xF0004074U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC1_CC0                        (0xF0004078U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC1_CDS_MSP0                   (0xF000407CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC1_CSUS0                      (0xF0004080U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC1_CDUS0                      (0xF0004084U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC1_CIE1                       (0xF0004090U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC1_CID1                       (0xF0004094U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC1_CIM1                       (0xF0004098U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC1_CIS1                       (0xF000409CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC1_CSA1                       (0xF00040A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC1_CDA1                       (0xF00040A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC1_CNDA1                      (0xF00040A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC1_CNDC1                      (0xF00040ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC1_CUBC1                      (0xF00040B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC1_CBC1                       (0xF00040B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC1_CC1                        (0xF00040B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC1_CDS_MSP1                   (0xF00040BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC1_CSUS1                      (0xF00040C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC1_CDUS1                      (0xF00040C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC1_CIE2                       (0xF00040D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC1_CID2                       (0xF00040D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC1_CIM2                       (0xF00040D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC1_CIS2                       (0xF00040DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC1_CSA2                       (0xF00040E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC1_CDA2                       (0xF00040E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC1_CNDA2                      (0xF00040E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC1_CNDC2                      (0xF00040ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC1_CUBC2                      (0xF00040F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC1_CBC2                       (0xF00040F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC1_CC2                        (0xF00040F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC1_CDS_MSP2                   (0xF00040FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC1_CSUS2                      (0xF0004100U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC1_CDUS2                      (0xF0004104U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC1_CIE3                       (0xF0004110U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC1_CID3                       (0xF0004114U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC1_CIM3                       (0xF0004118U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC1_CIS3                       (0xF000411CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC1_CSA3                       (0xF0004120U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC1_CDA3                       (0xF0004124U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC1_CNDA3                      (0xF0004128U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC1_CNDC3                      (0xF000412CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC1_CUBC3                      (0xF0004130U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC1_CBC3                       (0xF0004134U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC1_CC3                        (0xF0004138U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC1_CDS_MSP3                   (0xF000413CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC1_CSUS3                      (0xF0004140U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC1_CDUS3                      (0xF0004144U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC1_CIE4                       (0xF0004150U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC1_CID4                       (0xF0004154U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC1_CIM4                       (0xF0004158U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC1_CIS4                       (0xF000415CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC1_CSA4                       (0xF0004160U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC1_CDA4                       (0xF0004164U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC1_CNDA4                      (0xF0004168U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC1_CNDC4                      (0xF000416CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC1_CUBC4                      (0xF0004170U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC1_CBC4                       (0xF0004174U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC1_CC4                        (0xF0004178U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC1_CDS_MSP4                   (0xF000417CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC1_CSUS4                      (0xF0004180U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC1_CDUS4                      (0xF0004184U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC1_CIE5                       (0xF0004190U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC1_CID5                       (0xF0004194U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC1_CIM5                       (0xF0004198U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC1_CIS5                       (0xF000419CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC1_CSA5                       (0xF00041A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC1_CDA5                       (0xF00041A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC1_CNDA5                      (0xF00041A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC1_CNDC5                      (0xF00041ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC1_CUBC5                      (0xF00041B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC1_CBC5                       (0xF00041B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC1_CC5                        (0xF00041B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC1_CDS_MSP5                   (0xF00041BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC1_CSUS5                      (0xF00041C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC1_CDUS5                      (0xF00041C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC1_CIE6                       (0xF00041D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC1_CID6                       (0xF00041D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC1_CIM6                       (0xF00041D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC1_CIS6                       (0xF00041DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC1_CSA6                       (0xF00041E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC1_CDA6                       (0xF00041E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC1_CNDA6                      (0xF00041E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC1_CNDC6                      (0xF00041ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC1_CUBC6                      (0xF00041F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC1_CBC6                       (0xF00041F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC1_CC6                        (0xF00041F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC1_CDS_MSP6                   (0xF00041FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC1_CSUS6                      (0xF0004200U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC1_CDUS6                      (0xF0004204U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC1_CIE7                       (0xF0004210U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC1_CID7                       (0xF0004214U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC1_CIM7                       (0xF0004218U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC1_CIS7                       (0xF000421CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC1_CSA7                       (0xF0004220U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC1_CDA7                       (0xF0004224U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC1_CNDA7                      (0xF0004228U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC1_CNDC7                      (0xF000422CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC1_CUBC7                      (0xF0004230U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC1_CBC7                       (0xF0004234U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC1_CC7                        (0xF0004238U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC1_CDS_MSP7                   (0xF000423CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC1_CSUS7                      (0xF0004240U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC1_CDUS7                      (0xF0004244U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC1_CIE8                       (0xF0004250U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC1_CID8                       (0xF0004254U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC1_CIM8                       (0xF0004258U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC1_CIS8                       (0xF000425CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC1_CSA8                       (0xF0004260U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC1_CDA8                       (0xF0004264U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC1_CNDA8                      (0xF0004268U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC1_CNDC8                      (0xF000426CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC1_CUBC8                      (0xF0004270U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC1_CBC8                       (0xF0004274U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC1_CC8                        (0xF0004278U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC1_CDS_MSP8                   (0xF000427CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC1_CSUS8                      (0xF0004280U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC1_CDUS8                      (0xF0004284U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC1_CIE9                       (0xF0004290U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC1_CID9                       (0xF0004294U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC1_CIM9                       (0xF0004298U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC1_CIS9                       (0xF000429CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC1_CSA9                       (0xF00042A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC1_CDA9                       (0xF00042A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC1_CNDA9                      (0xF00042A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC1_CNDC9                      (0xF00042ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC1_CUBC9                      (0xF00042B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC1_CBC9                       (0xF00042B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC1_CC9                        (0xF00042B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC1_CDS_MSP9                   (0xF00042BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC1_CSUS9                      (0xF00042C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC1_CDUS9                      (0xF00042C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC1_CIE10                      (0xF00042D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC1_CID10                      (0xF00042D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC1_CIM10                      (0xF00042D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC1_CIS10                      (0xF00042DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC1_CSA10                      (0xF00042E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC1_CDA10                      (0xF00042E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC1_CNDA10                     (0xF00042E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC1_CNDC10                     (0xF00042ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC1_CUBC10                     (0xF00042F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC1_CBC10                      (0xF00042F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC1_CC10                       (0xF00042F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC1_CDS_MSP10                  (0xF00042FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC1_CSUS10                     (0xF0004300U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC1_CDUS10                     (0xF0004304U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC1_CIE11                      (0xF0004310U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC1_CID11                      (0xF0004314U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC1_CIM11                      (0xF0004318U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC1_CIS11                      (0xF000431CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC1_CSA11                      (0xF0004320U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC1_CDA11                      (0xF0004324U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC1_CNDA11                     (0xF0004328U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC1_CNDC11                     (0xF000432CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC1_CUBC11                     (0xF0004330U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC1_CBC11                      (0xF0004334U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC1_CC11                       (0xF0004338U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC1_CDS_MSP11                  (0xF000433CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC1_CSUS11                     (0xF0004340U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC1_CDUS11                     (0xF0004344U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC1_CIE12                      (0xF0004350U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC1_CID12                      (0xF0004354U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC1_CIM12                      (0xF0004358U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC1_CIS12                      (0xF000435CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC1_CSA12                      (0xF0004360U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC1_CDA12                      (0xF0004364U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC1_CNDA12                     (0xF0004368U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC1_CNDC12                     (0xF000436CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC1_CUBC12                     (0xF0004370U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC1_CBC12                      (0xF0004374U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC1_CC12                       (0xF0004378U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC1_CDS_MSP12                  (0xF000437CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC1_CSUS12                     (0xF0004380U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC1_CDUS12                     (0xF0004384U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC1_CIE13                      (0xF0004390U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC1_CID13                      (0xF0004394U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC1_CIM13                      (0xF0004398U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC1_CIS13                      (0xF000439CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC1_CSA13                      (0xF00043A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC1_CDA13                      (0xF00043A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC1_CNDA13                     (0xF00043A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC1_CNDC13                     (0xF00043ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC1_CUBC13                     (0xF00043B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC1_CBC13                      (0xF00043B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC1_CC13                       (0xF00043B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC1_CDS_MSP13                  (0xF00043BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC1_CSUS13                     (0xF00043C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC1_CDUS13                     (0xF00043C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC1_CIE14                      (0xF00043D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC1_CID14                      (0xF00043D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC1_CIM14                      (0xF00043D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC1_CIS14                      (0xF00043DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC1_CSA14                      (0xF00043E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC1_CDA14                      (0xF00043E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC1_CNDA14                     (0xF00043E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC1_CNDC14                     (0xF00043ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC1_CUBC14                     (0xF00043F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC1_CBC14                      (0xF00043F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC1_CC14                       (0xF00043F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC1_CDS_MSP14                  (0xF00043FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC1_CSUS14                     (0xF0004400U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC1_CDUS14                     (0xF0004404U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC1_CIE15                      (0xF0004410U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC1_CID15                      (0xF0004414U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC1_CIM15                      (0xF0004418U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC1_CIS15                      (0xF000441CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC1_CSA15                      (0xF0004420U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC1_CDA15                      (0xF0004424U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC1_CNDA15                     (0xF0004428U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC1_CNDC15                     (0xF000442CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC1_CUBC15                     (0xF0004430U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC1_CBC15                      (0xF0004434U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC1_CC15                       (0xF0004438U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC1_CDS_MSP15                  (0xF000443CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC1_CSUS15                     (0xF0004440U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC1_CDUS15                     (0xF0004444U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 15) */
#else
  #define REG_XDMAC1_GTYPE     (*(__IO uint32_t*)0xF0004000U) /**< \brief (XDMAC1) Global Type register */
  #define REG_XDMAC1_GCFG      (*(__I  uint32_t*)0xF0004004U) /**< \brief (XDMAC1) Global Configuration Register */
  #define REG_XDMAC1_GWAC      (*(__IO uint32_t*)0xF0004008U) /**< \brief (XDMAC1) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC1_GIE       (*(__O  uint32_t*)0xF000400CU) /**< \brief (XDMAC1) Global Interrupt Enable Register */
  #define REG_XDMAC1_GID       (*(__O  uint32_t*)0xF0004010U) /**< \brief (XDMAC1) Global Interrupt Disable Register */
  #define REG_XDMAC1_GIM       (*(__I  uint32_t*)0xF0004014U) /**< \brief (XDMAC1) Global Interrupt Mask Register */
  #define REG_XDMAC1_GIS       (*(__I  uint32_t*)0xF0004018U) /**< \brief (XDMAC1) Global Interrupt Status Register */
  #define REG_XDMAC1_GE        (*(__O  uint32_t*)0xF000401CU) /**< \brief (XDMAC1) Global Channel Enable Register */
  #define REG_XDMAC1_GD        (*(__O  uint32_t*)0xF0004020U) /**< \brief (XDMAC1) Global Channel Disable Register */
  #define REG_XDMAC1_GS        (*(__I  uint32_t*)0xF0004024U) /**< \brief (XDMAC1) Global Channel Status Register */
  #define REG_XDMAC1_GRS       (*(__IO uint32_t*)0xF0004028U) /**< \brief (XDMAC1) Global Channel Read Suspend Register */
  #define REG_XDMAC1_GWS       (*(__IO uint32_t*)0xF000402CU) /**< \brief (XDMAC1) Global Channel Write Suspend Register */
  #define REG_XDMAC1_GRWS      (*(__O  uint32_t*)0xF0004030U) /**< \brief (XDMAC1) Global Channel Read Write Suspend Register */
  #define REG_XDMAC1_GRWR      (*(__O  uint32_t*)0xF0004034U) /**< \brief (XDMAC1) Global Channel Read Write Resume Register */
  #define REG_XDMAC1_GSWR      (*(__O  uint32_t*)0xF0004038U) /**< \brief (XDMAC1) Global Channel Software Request Register */
  #define REG_XDMAC1_GSWS      (*(__I  uint32_t*)0xF000403CU) /**< \brief (XDMAC1) Global Channel Software Request Status Register */
  #define REG_XDMAC1_GSWF      (*(__O  uint32_t*)0xF0004040U) /**< \brief (XDMAC1) Global Channel Software Flush Request Register */
  #define REG_XDMAC1_CIE0      (*(__O  uint32_t*)0xF0004050U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC1_CID0      (*(__O  uint32_t*)0xF0004054U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC1_CIM0      (*(__O  uint32_t*)0xF0004058U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC1_CIS0      (*(__I  uint32_t*)0xF000405CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC1_CSA0      (*(__IO uint32_t*)0xF0004060U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC1_CDA0      (*(__IO uint32_t*)0xF0004064U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC1_CNDA0     (*(__IO uint32_t*)0xF0004068U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC1_CNDC0     (*(__IO uint32_t*)0xF000406CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC1_CUBC0     (*(__IO uint32_t*)0xF0004070U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC1_CBC0      (*(__IO uint32_t*)0xF0004074U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC1_CC0       (*(__IO uint32_t*)0xF0004078U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC1_CDS_MSP0  (*(__IO uint32_t*)0xF000407CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC1_CSUS0     (*(__IO uint32_t*)0xF0004080U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC1_CDUS0     (*(__IO uint32_t*)0xF0004084U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC1_CIE1      (*(__O  uint32_t*)0xF0004090U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC1_CID1      (*(__O  uint32_t*)0xF0004094U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC1_CIM1      (*(__O  uint32_t*)0xF0004098U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC1_CIS1      (*(__I  uint32_t*)0xF000409CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC1_CSA1      (*(__IO uint32_t*)0xF00040A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC1_CDA1      (*(__IO uint32_t*)0xF00040A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC1_CNDA1     (*(__IO uint32_t*)0xF00040A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC1_CNDC1     (*(__IO uint32_t*)0xF00040ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC1_CUBC1     (*(__IO uint32_t*)0xF00040B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC1_CBC1      (*(__IO uint32_t*)0xF00040B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC1_CC1       (*(__IO uint32_t*)0xF00040B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC1_CDS_MSP1  (*(__IO uint32_t*)0xF00040BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC1_CSUS1     (*(__IO uint32_t*)0xF00040C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC1_CDUS1     (*(__IO uint32_t*)0xF00040C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC1_CIE2      (*(__O  uint32_t*)0xF00040D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC1_CID2      (*(__O  uint32_t*)0xF00040D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC1_CIM2      (*(__O  uint32_t*)0xF00040D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC1_CIS2      (*(__I  uint32_t*)0xF00040DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC1_CSA2      (*(__IO uint32_t*)0xF00040E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC1_CDA2      (*(__IO uint32_t*)0xF00040E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC1_CNDA2     (*(__IO uint32_t*)0xF00040E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC1_CNDC2     (*(__IO uint32_t*)0xF00040ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC1_CUBC2     (*(__IO uint32_t*)0xF00040F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC1_CBC2      (*(__IO uint32_t*)0xF00040F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC1_CC2       (*(__IO uint32_t*)0xF00040F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC1_CDS_MSP2  (*(__IO uint32_t*)0xF00040FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC1_CSUS2     (*(__IO uint32_t*)0xF0004100U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC1_CDUS2     (*(__IO uint32_t*)0xF0004104U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC1_CIE3      (*(__O  uint32_t*)0xF0004110U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC1_CID3      (*(__O  uint32_t*)0xF0004114U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC1_CIM3      (*(__O  uint32_t*)0xF0004118U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC1_CIS3      (*(__I  uint32_t*)0xF000411CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC1_CSA3      (*(__IO uint32_t*)0xF0004120U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC1_CDA3      (*(__IO uint32_t*)0xF0004124U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC1_CNDA3     (*(__IO uint32_t*)0xF0004128U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC1_CNDC3     (*(__IO uint32_t*)0xF000412CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC1_CUBC3     (*(__IO uint32_t*)0xF0004130U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC1_CBC3      (*(__IO uint32_t*)0xF0004134U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC1_CC3       (*(__IO uint32_t*)0xF0004138U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC1_CDS_MSP3  (*(__IO uint32_t*)0xF000413CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC1_CSUS3     (*(__IO uint32_t*)0xF0004140U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC1_CDUS3     (*(__IO uint32_t*)0xF0004144U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC1_CIE4      (*(__O  uint32_t*)0xF0004150U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC1_CID4      (*(__O  uint32_t*)0xF0004154U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC1_CIM4      (*(__O  uint32_t*)0xF0004158U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC1_CIS4      (*(__I  uint32_t*)0xF000415CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC1_CSA4      (*(__IO uint32_t*)0xF0004160U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC1_CDA4      (*(__IO uint32_t*)0xF0004164U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC1_CNDA4     (*(__IO uint32_t*)0xF0004168U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC1_CNDC4     (*(__IO uint32_t*)0xF000416CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC1_CUBC4     (*(__IO uint32_t*)0xF0004170U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC1_CBC4      (*(__IO uint32_t*)0xF0004174U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC1_CC4       (*(__IO uint32_t*)0xF0004178U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC1_CDS_MSP4  (*(__IO uint32_t*)0xF000417CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC1_CSUS4     (*(__IO uint32_t*)0xF0004180U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC1_CDUS4     (*(__IO uint32_t*)0xF0004184U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC1_CIE5      (*(__O  uint32_t*)0xF0004190U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC1_CID5      (*(__O  uint32_t*)0xF0004194U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC1_CIM5      (*(__O  uint32_t*)0xF0004198U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC1_CIS5      (*(__I  uint32_t*)0xF000419CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC1_CSA5      (*(__IO uint32_t*)0xF00041A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC1_CDA5      (*(__IO uint32_t*)0xF00041A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC1_CNDA5     (*(__IO uint32_t*)0xF00041A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC1_CNDC5     (*(__IO uint32_t*)0xF00041ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC1_CUBC5     (*(__IO uint32_t*)0xF00041B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC1_CBC5      (*(__IO uint32_t*)0xF00041B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC1_CC5       (*(__IO uint32_t*)0xF00041B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC1_CDS_MSP5  (*(__IO uint32_t*)0xF00041BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC1_CSUS5     (*(__IO uint32_t*)0xF00041C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC1_CDUS5     (*(__IO uint32_t*)0xF00041C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC1_CIE6      (*(__O  uint32_t*)0xF00041D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC1_CID6      (*(__O  uint32_t*)0xF00041D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC1_CIM6      (*(__O  uint32_t*)0xF00041D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC1_CIS6      (*(__I  uint32_t*)0xF00041DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC1_CSA6      (*(__IO uint32_t*)0xF00041E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC1_CDA6      (*(__IO uint32_t*)0xF00041E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC1_CNDA6     (*(__IO uint32_t*)0xF00041E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC1_CNDC6     (*(__IO uint32_t*)0xF00041ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC1_CUBC6     (*(__IO uint32_t*)0xF00041F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC1_CBC6      (*(__IO uint32_t*)0xF00041F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC1_CC6       (*(__IO uint32_t*)0xF00041F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC1_CDS_MSP6  (*(__IO uint32_t*)0xF00041FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC1_CSUS6     (*(__IO uint32_t*)0xF0004200U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC1_CDUS6     (*(__IO uint32_t*)0xF0004204U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC1_CIE7      (*(__O  uint32_t*)0xF0004210U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC1_CID7      (*(__O  uint32_t*)0xF0004214U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC1_CIM7      (*(__O  uint32_t*)0xF0004218U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC1_CIS7      (*(__I  uint32_t*)0xF000421CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC1_CSA7      (*(__IO uint32_t*)0xF0004220U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC1_CDA7      (*(__IO uint32_t*)0xF0004224U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC1_CNDA7     (*(__IO uint32_t*)0xF0004228U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC1_CNDC7     (*(__IO uint32_t*)0xF000422CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC1_CUBC7     (*(__IO uint32_t*)0xF0004230U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC1_CBC7      (*(__IO uint32_t*)0xF0004234U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC1_CC7       (*(__IO uint32_t*)0xF0004238U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC1_CDS_MSP7  (*(__IO uint32_t*)0xF000423CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC1_CSUS7     (*(__IO uint32_t*)0xF0004240U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC1_CDUS7     (*(__IO uint32_t*)0xF0004244U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC1_CIE8      (*(__O  uint32_t*)0xF0004250U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC1_CID8      (*(__O  uint32_t*)0xF0004254U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC1_CIM8      (*(__O  uint32_t*)0xF0004258U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC1_CIS8      (*(__I  uint32_t*)0xF000425CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC1_CSA8      (*(__IO uint32_t*)0xF0004260U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC1_CDA8      (*(__IO uint32_t*)0xF0004264U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC1_CNDA8     (*(__IO uint32_t*)0xF0004268U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC1_CNDC8     (*(__IO uint32_t*)0xF000426CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC1_CUBC8     (*(__IO uint32_t*)0xF0004270U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC1_CBC8      (*(__IO uint32_t*)0xF0004274U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC1_CC8       (*(__IO uint32_t*)0xF0004278U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC1_CDS_MSP8  (*(__IO uint32_t*)0xF000427CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC1_CSUS8     (*(__IO uint32_t*)0xF0004280U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC1_CDUS8     (*(__IO uint32_t*)0xF0004284U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC1_CIE9      (*(__O  uint32_t*)0xF0004290U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC1_CID9      (*(__O  uint32_t*)0xF0004294U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC1_CIM9      (*(__O  uint32_t*)0xF0004298U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC1_CIS9      (*(__I  uint32_t*)0xF000429CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC1_CSA9      (*(__IO uint32_t*)0xF00042A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC1_CDA9      (*(__IO uint32_t*)0xF00042A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC1_CNDA9     (*(__IO uint32_t*)0xF00042A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC1_CNDC9     (*(__IO uint32_t*)0xF00042ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC1_CUBC9     (*(__IO uint32_t*)0xF00042B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC1_CBC9      (*(__IO uint32_t*)0xF00042B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC1_CC9       (*(__IO uint32_t*)0xF00042B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC1_CDS_MSP9  (*(__IO uint32_t*)0xF00042BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC1_CSUS9     (*(__IO uint32_t*)0xF00042C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC1_CDUS9     (*(__IO uint32_t*)0xF00042C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC1_CIE10     (*(__O  uint32_t*)0xF00042D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC1_CID10     (*(__O  uint32_t*)0xF00042D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC1_CIM10     (*(__O  uint32_t*)0xF00042D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC1_CIS10     (*(__I  uint32_t*)0xF00042DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC1_CSA10     (*(__IO uint32_t*)0xF00042E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC1_CDA10     (*(__IO uint32_t*)0xF00042E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC1_CNDA10    (*(__IO uint32_t*)0xF00042E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC1_CNDC10    (*(__IO uint32_t*)0xF00042ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC1_CUBC10    (*(__IO uint32_t*)0xF00042F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC1_CBC10     (*(__IO uint32_t*)0xF00042F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC1_CC10      (*(__IO uint32_t*)0xF00042F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC1_CDS_MSP10 (*(__IO uint32_t*)0xF00042FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC1_CSUS10    (*(__IO uint32_t*)0xF0004300U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC1_CDUS10    (*(__IO uint32_t*)0xF0004304U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC1_CIE11     (*(__O  uint32_t*)0xF0004310U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC1_CID11     (*(__O  uint32_t*)0xF0004314U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC1_CIM11     (*(__O  uint32_t*)0xF0004318U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC1_CIS11     (*(__I  uint32_t*)0xF000431CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC1_CSA11     (*(__IO uint32_t*)0xF0004320U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC1_CDA11     (*(__IO uint32_t*)0xF0004324U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC1_CNDA11    (*(__IO uint32_t*)0xF0004328U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC1_CNDC11    (*(__IO uint32_t*)0xF000432CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC1_CUBC11    (*(__IO uint32_t*)0xF0004330U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC1_CBC11     (*(__IO uint32_t*)0xF0004334U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC1_CC11      (*(__IO uint32_t*)0xF0004338U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC1_CDS_MSP11 (*(__IO uint32_t*)0xF000433CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC1_CSUS11    (*(__IO uint32_t*)0xF0004340U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC1_CDUS11    (*(__IO uint32_t*)0xF0004344U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC1_CIE12     (*(__O  uint32_t*)0xF0004350U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC1_CID12     (*(__O  uint32_t*)0xF0004354U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC1_CIM12     (*(__O  uint32_t*)0xF0004358U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC1_CIS12     (*(__I  uint32_t*)0xF000435CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC1_CSA12     (*(__IO uint32_t*)0xF0004360U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC1_CDA12     (*(__IO uint32_t*)0xF0004364U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC1_CNDA12    (*(__IO uint32_t*)0xF0004368U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC1_CNDC12    (*(__IO uint32_t*)0xF000436CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC1_CUBC12    (*(__IO uint32_t*)0xF0004370U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC1_CBC12     (*(__IO uint32_t*)0xF0004374U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC1_CC12      (*(__IO uint32_t*)0xF0004378U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC1_CDS_MSP12 (*(__IO uint32_t*)0xF000437CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC1_CSUS12    (*(__IO uint32_t*)0xF0004380U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC1_CDUS12    (*(__IO uint32_t*)0xF0004384U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC1_CIE13     (*(__O  uint32_t*)0xF0004390U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC1_CID13     (*(__O  uint32_t*)0xF0004394U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC1_CIM13     (*(__O  uint32_t*)0xF0004398U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC1_CIS13     (*(__I  uint32_t*)0xF000439CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC1_CSA13     (*(__IO uint32_t*)0xF00043A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC1_CDA13     (*(__IO uint32_t*)0xF00043A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC1_CNDA13    (*(__IO uint32_t*)0xF00043A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC1_CNDC13    (*(__IO uint32_t*)0xF00043ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC1_CUBC13    (*(__IO uint32_t*)0xF00043B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC1_CBC13     (*(__IO uint32_t*)0xF00043B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC1_CC13      (*(__IO uint32_t*)0xF00043B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC1_CDS_MSP13 (*(__IO uint32_t*)0xF00043BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC1_CSUS13    (*(__IO uint32_t*)0xF00043C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC1_CDUS13    (*(__IO uint32_t*)0xF00043C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC1_CIE14     (*(__O  uint32_t*)0xF00043D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC1_CID14     (*(__O  uint32_t*)0xF00043D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC1_CIM14     (*(__O  uint32_t*)0xF00043D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC1_CIS14     (*(__I  uint32_t*)0xF00043DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC1_CSA14     (*(__IO uint32_t*)0xF00043E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC1_CDA14     (*(__IO uint32_t*)0xF00043E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC1_CNDA14    (*(__IO uint32_t*)0xF00043E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC1_CNDC14    (*(__IO uint32_t*)0xF00043ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC1_CUBC14    (*(__IO uint32_t*)0xF00043F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC1_CBC14     (*(__IO uint32_t*)0xF00043F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC1_CC14      (*(__IO uint32_t*)0xF00043F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC1_CDS_MSP14 (*(__IO uint32_t*)0xF00043FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC1_CSUS14    (*(__IO uint32_t*)0xF0004400U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC1_CDUS14    (*(__IO uint32_t*)0xF0004404U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC1_CIE15     (*(__O  uint32_t*)0xF0004410U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC1_CID15     (*(__O  uint32_t*)0xF0004414U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC1_CIM15     (*(__O  uint32_t*)0xF0004418U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC1_CIS15     (*(__I  uint32_t*)0xF000441CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC1_CSA15     (*(__IO uint32_t*)0xF0004420U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC1_CDA15     (*(__IO uint32_t*)0xF0004424U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC1_CNDA15    (*(__IO uint32_t*)0xF0004428U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC1_CNDC15    (*(__IO uint32_t*)0xF000442CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC1_CUBC15    (*(__IO uint32_t*)0xF0004430U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC1_CBC15     (*(__IO uint32_t*)0xF0004434U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC1_CC15      (*(__IO uint32_t*)0xF0004438U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC1_CDS_MSP15 (*(__IO uint32_t*)0xF000443CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC1_CSUS15    (*(__IO uint32_t*)0xF0004440U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC1_CDUS15    (*(__IO uint32_t*)0xF0004444U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 15) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Register definition for MPDDRC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_MPDDRC_MR                              (0xF0010000U) /**< \brief (MPDDRC) MPDDRC Mode Register */
  #define REG_MPDDRC_RTR                             (0xF0010004U) /**< \brief (MPDDRC) MPDDRC Refresh Timer Register */
  #define REG_MPDDRC_CR                              (0xF0010008U) /**< \brief (MPDDRC) MPDDRC Configuration Register */
  #define REG_MPDDRC_TPR0                            (0xF001000CU) /**< \brief (MPDDRC) MPDDRC Timing Parameter 0 Register */
  #define REG_MPDDRC_TPR1                            (0xF0010010U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 1 Register */
  #define REG_MPDDRC_TPR2                            (0xF0010014U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 2 Register */
  #define REG_MPDDRC_LPR                             (0xF001001CU) /**< \brief (MPDDRC) MPDDRC Low-power Register */
  #define REG_MPDDRC_MD                              (0xF0010020U) /**< \brief (MPDDRC) MPDDRC Memory Device Register */
  #define REG_MPDDRC_LPDDR2_LPR                      (0xF0010028U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Low-power Register */
  #define REG_MPDDRC_LPDDR2_CAL_MR4                  (0xF001002CU) /**< \brief (MPDDRC) MPDDRC LPDDR2 Calibration and MR4 Register */
  #define REG_MPDDRC_LPDDR2_TIM_CAL                  (0xF0010030U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Timing Calibration Register */
  #define REG_MPDDRC_IO_CALIBR                       (0xF0010034U) /**< \brief (MPDDRC) MPDDRC IO Calibration */
  #define REG_MPDDRC_OCMS                            (0xF0010038U) /**< \brief (MPDDRC) MPDDRC OCMS Register */
  #define REG_MPDDRC_OCMS_KEY1                       (0xF001003CU) /**< \brief (MPDDRC) MPDDRC OCMS KEY1 Register */
  #define REG_MPDDRC_OCMS_KEY2                       (0xF0010040U) /**< \brief (MPDDRC) MPDDRC OCMS KEY2 Register */
  #define REG_MPDDRC_CONF_ARBITER                    (0xF0010044U) /**< \brief (MPDDRC) MPDDRC Configuration Arbiter */
  #define REG_MPDDRC_TIMEOUT                         (0xF0010048U) /**< \brief (MPDDRC) MPDDRC Time-out Port 0/1/2/3 */
  #define REG_MPDDRC_REQ_PORT_0123                   (0xF001004CU) /**< \brief (MPDDRC) MPDDRC Time-out Request Port 0/1/2/3 */
  #define REG_MPDDRC_REQ_PORT_4567                   (0xF0010050U) /**< \brief (MPDDRC) MPDDRC Time-out Request Port 4/5/6/7 */
  #define REG_MPDDRC_BDW_PORT_0123                   (0xF0010054U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 0/1/2/3 */
  #define REG_MPDDRC_BDW_PORT_4567                   (0xF0010058U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 4/5/6/7 */
  #define REG_MPDDRC_RD_DATA_PATH                    (0xF001005CU) /**< \brief (MPDDRC) MPDDRC_READ_DATA_PATH */
  #define REG_MPDDRC_SAW                             (0xF0010060U) /**< \brief (MPDDRC) MPDDRC Smart Adaptation Wrapper 0 Register */
  #define REG_MPDDRC_WPMR                            (0xF00100E4U) /**< \brief (MPDDRC) MPDDRC Write Protect Control Register */
  #define REG_MPDDRC_WPSR                            (0xF00100E8U) /**< \brief (MPDDRC) MPDDRC Write Protect Status Register */
  #define REG_MPDDRC_DLL_OS                          (0xF0010100U) /**< \brief (MPDDRC) MPDDRC DLL Offset Selection Register */
  #define REG_MPDDRC_DLL_MO                          (0xF0010104U) /**< \brief (MPDDRC) MPDDRC DLL MASTER Offset Register */
  #define REG_MPDDRC_DLL_SO0                         (0xF0010108U) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 0 Register */
  #define REG_MPDDRC_DLL_SO1                         (0xF001010CU) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 1 Register */
  #define REG_MPDDRC_DLL_WRO                         (0xF0010110U) /**< \brief (MPDDRC) MPDDRC DLL CLKWR Offset Register */
  #define REG_MPDDRC_DLL_ADO                         (0xF0010114U) /**< \brief (MPDDRC) MPDDRC DLL CLKAD Offset Register */
  #define REG_MPDDRC_DLL_SM                          (0xF0010118U) /**< \brief (MPDDRC) MPDDRC DLL Status MASTER0 Register */
  #define REG_MPDDRC_DLL_SSL                         (0xF0010128U) /**< \brief (MPDDRC) MPDDRC DLL Status SLAVE0 Register */
  #define REG_MPDDRC_DLL_SWR                         (0xF0010148U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKWR0 Register */
  #define REG_MPDDRC_DLL_SAD                         (0xF0010158U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKAD Register */
#else
  #define REG_MPDDRC_MR             (*(__IO uint32_t*)0xF0010000U) /**< \brief (MPDDRC) MPDDRC Mode Register */
  #define REG_MPDDRC_RTR            (*(__IO uint32_t*)0xF0010004U) /**< \brief (MPDDRC) MPDDRC Refresh Timer Register */
  #define REG_MPDDRC_CR             (*(__IO uint32_t*)0xF0010008U) /**< \brief (MPDDRC) MPDDRC Configuration Register */
  #define REG_MPDDRC_TPR0           (*(__IO uint32_t*)0xF001000CU) /**< \brief (MPDDRC) MPDDRC Timing Parameter 0 Register */
  #define REG_MPDDRC_TPR1           (*(__IO uint32_t*)0xF0010010U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 1 Register */
  #define REG_MPDDRC_TPR2           (*(__IO uint32_t*)0xF0010014U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 2 Register */
  #define REG_MPDDRC_LPR            (*(__IO uint32_t*)0xF001001CU) /**< \brief (MPDDRC) MPDDRC Low-power Register */
  #define REG_MPDDRC_MD             (*(__IO uint32_t*)0xF0010020U) /**< \brief (MPDDRC) MPDDRC Memory Device Register */
  #define REG_MPDDRC_LPDDR2_LPR     (*(__IO uint32_t*)0xF0010028U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Low-power Register */
  #define REG_MPDDRC_LPDDR2_CAL_MR4 (*(__IO uint32_t*)0xF001002CU) /**< \brief (MPDDRC) MPDDRC LPDDR2 Calibration and MR4 Register */
  #define REG_MPDDRC_LPDDR2_TIM_CAL (*(__IO uint32_t*)0xF0010030U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Timing Calibration Register */
  #define REG_MPDDRC_IO_CALIBR      (*(__IO uint32_t*)0xF0010034U) /**< \brief (MPDDRC) MPDDRC IO Calibration */
  #define REG_MPDDRC_OCMS           (*(__IO uint32_t*)0xF0010038U) /**< \brief (MPDDRC) MPDDRC OCMS Register */
  #define REG_MPDDRC_OCMS_KEY1      (*(__O  uint32_t*)0xF001003CU) /**< \brief (MPDDRC) MPDDRC OCMS KEY1 Register */
  #define REG_MPDDRC_OCMS_KEY2      (*(__O  uint32_t*)0xF0010040U) /**< \brief (MPDDRC) MPDDRC OCMS KEY2 Register */
  #define REG_MPDDRC_CONF_ARBITER   (*(__IO uint32_t*)0xF0010044U) /**< \brief (MPDDRC) MPDDRC Configuration Arbiter */
  #define REG_MPDDRC_TIMEOUT        (*(__IO uint32_t*)0xF0010048U) /**< \brief (MPDDRC) MPDDRC Time-out Port 0/1/2/3 */
  #define REG_MPDDRC_REQ_PORT_0123  (*(__IO uint32_t*)0xF001004CU) /**< \brief (MPDDRC) MPDDRC Time-out Request Port 0/1/2/3 */
  #define REG_MPDDRC_REQ_PORT_4567  (*(__IO uint32_t*)0xF0010050U) /**< \brief (MPDDRC) MPDDRC Time-out Request Port 4/5/6/7 */
  #define REG_MPDDRC_BDW_PORT_0123  (*(__I  uint32_t*)0xF0010054U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 0/1/2/3 */
  #define REG_MPDDRC_BDW_PORT_4567  (*(__I  uint32_t*)0xF0010058U) /**< \brief (MPDDRC) MPDDRC Bandwidth Port 4/5/6/7 */
  #define REG_MPDDRC_RD_DATA_PATH   (*(__IO uint32_t*)0xF001005CU) /**< \brief (MPDDRC) MPDDRC_READ_DATA_PATH */
  #define REG_MPDDRC_SAW            (*(__IO uint32_t*)0xF0010060U) /**< \brief (MPDDRC) MPDDRC Smart Adaptation Wrapper 0 Register */
  #define REG_MPDDRC_WPMR           (*(__IO uint32_t*)0xF00100E4U) /**< \brief (MPDDRC) MPDDRC Write Protect Control Register */
  #define REG_MPDDRC_WPSR           (*(__I  uint32_t*)0xF00100E8U) /**< \brief (MPDDRC) MPDDRC Write Protect Status Register */
  #define REG_MPDDRC_DLL_OS         (*(__IO uint32_t*)0xF0010100U) /**< \brief (MPDDRC) MPDDRC DLL Offset Selection Register */
  #define REG_MPDDRC_DLL_MO         (*(__IO uint32_t*)0xF0010104U) /**< \brief (MPDDRC) MPDDRC DLL MASTER Offset Register */
  #define REG_MPDDRC_DLL_SO0        (*(__IO uint32_t*)0xF0010108U) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 0 Register */
  #define REG_MPDDRC_DLL_SO1        (*(__IO uint32_t*)0xF001010CU) /**< \brief (MPDDRC) MPDDRC DLL SLAVE Offset 1 Register */
  #define REG_MPDDRC_DLL_WRO        (*(__IO uint32_t*)0xF0010110U) /**< \brief (MPDDRC) MPDDRC DLL CLKWR Offset Register */
  #define REG_MPDDRC_DLL_ADO        (*(__IO uint32_t*)0xF0010114U) /**< \brief (MPDDRC) MPDDRC DLL CLKAD Offset Register */
  #define REG_MPDDRC_DLL_SM         (*(__I  uint32_t*)0xF0010118U) /**< \brief (MPDDRC) MPDDRC DLL Status MASTER0 Register */
  #define REG_MPDDRC_DLL_SSL        (*(__I  uint32_t*)0xF0010128U) /**< \brief (MPDDRC) MPDDRC DLL Status SLAVE0 Register */
  #define REG_MPDDRC_DLL_SWR        (*(__I  uint32_t*)0xF0010148U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKWR0 Register */
  #define REG_MPDDRC_DLL_SAD        (*(__I  uint32_t*)0xF0010158U) /**< \brief (MPDDRC) MPDDRC DLL Status CLKAD Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for XDMAC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_XDMAC0_GTYPE                      (0xF0014000U) /**< \brief (XDMAC0) Global Type register */
  #define REG_XDMAC0_GCFG                       (0xF0014004U) /**< \brief (XDMAC0) Global Configuration Register */
  #define REG_XDMAC0_GWAC                       (0xF0014008U) /**< \brief (XDMAC0) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC0_GIE                        (0xF001400CU) /**< \brief (XDMAC0) Global Interrupt Enable Register */
  #define REG_XDMAC0_GID                        (0xF0014010U) /**< \brief (XDMAC0) Global Interrupt Disable Register */
  #define REG_XDMAC0_GIM                        (0xF0014014U) /**< \brief (XDMAC0) Global Interrupt Mask Register */
  #define REG_XDMAC0_GIS                        (0xF0014018U) /**< \brief (XDMAC0) Global Interrupt Status Register */
  #define REG_XDMAC0_GE                         (0xF001401CU) /**< \brief (XDMAC0) Global Channel Enable Register */
  #define REG_XDMAC0_GD                         (0xF0014020U) /**< \brief (XDMAC0) Global Channel Disable Register */
  #define REG_XDMAC0_GS                         (0xF0014024U) /**< \brief (XDMAC0) Global Channel Status Register */
  #define REG_XDMAC0_GRS                        (0xF0014028U) /**< \brief (XDMAC0) Global Channel Read Suspend Register */
  #define REG_XDMAC0_GWS                        (0xF001402CU) /**< \brief (XDMAC0) Global Channel Write Suspend Register */
  #define REG_XDMAC0_GRWS                       (0xF0014030U) /**< \brief (XDMAC0) Global Channel Read Write Suspend Register */
  #define REG_XDMAC0_GRWR                       (0xF0014034U) /**< \brief (XDMAC0) Global Channel Read Write Resume Register */
  #define REG_XDMAC0_GSWR                       (0xF0014038U) /**< \brief (XDMAC0) Global Channel Software Request Register */
  #define REG_XDMAC0_GSWS                       (0xF001403CU) /**< \brief (XDMAC0) Global Channel Software Request Status Register */
  #define REG_XDMAC0_GSWF                       (0xF0014040U) /**< \brief (XDMAC0) Global Channel Software Flush Request Register */
  #define REG_XDMAC0_CIE0                       (0xF0014050U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC0_CID0                       (0xF0014054U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC0_CIM0                       (0xF0014058U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC0_CIS0                       (0xF001405CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC0_CSA0                       (0xF0014060U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC0_CDA0                       (0xF0014064U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC0_CNDA0                      (0xF0014068U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC0_CNDC0                      (0xF001406CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC0_CUBC0                      (0xF0014070U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC0_CBC0                       (0xF0014074U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC0_CC0                        (0xF0014078U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC0_CDS_MSP0                   (0xF001407CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC0_CSUS0                      (0xF0014080U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC0_CDUS0                      (0xF0014084U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC0_CIE1                       (0xF0014090U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC0_CID1                       (0xF0014094U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC0_CIM1                       (0xF0014098U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC0_CIS1                       (0xF001409CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC0_CSA1                       (0xF00140A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC0_CDA1                       (0xF00140A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC0_CNDA1                      (0xF00140A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC0_CNDC1                      (0xF00140ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC0_CUBC1                      (0xF00140B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC0_CBC1                       (0xF00140B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC0_CC1                        (0xF00140B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC0_CDS_MSP1                   (0xF00140BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC0_CSUS1                      (0xF00140C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC0_CDUS1                      (0xF00140C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC0_CIE2                       (0xF00140D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC0_CID2                       (0xF00140D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC0_CIM2                       (0xF00140D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC0_CIS2                       (0xF00140DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC0_CSA2                       (0xF00140E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC0_CDA2                       (0xF00140E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC0_CNDA2                      (0xF00140E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC0_CNDC2                      (0xF00140ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC0_CUBC2                      (0xF00140F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC0_CBC2                       (0xF00140F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC0_CC2                        (0xF00140F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC0_CDS_MSP2                   (0xF00140FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC0_CSUS2                      (0xF0014100U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC0_CDUS2                      (0xF0014104U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC0_CIE3                       (0xF0014110U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC0_CID3                       (0xF0014114U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC0_CIM3                       (0xF0014118U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC0_CIS3                       (0xF001411CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC0_CSA3                       (0xF0014120U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC0_CDA3                       (0xF0014124U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC0_CNDA3                      (0xF0014128U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC0_CNDC3                      (0xF001412CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC0_CUBC3                      (0xF0014130U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC0_CBC3                       (0xF0014134U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC0_CC3                        (0xF0014138U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC0_CDS_MSP3                   (0xF001413CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC0_CSUS3                      (0xF0014140U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC0_CDUS3                      (0xF0014144U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC0_CIE4                       (0xF0014150U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC0_CID4                       (0xF0014154U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC0_CIM4                       (0xF0014158U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC0_CIS4                       (0xF001415CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC0_CSA4                       (0xF0014160U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC0_CDA4                       (0xF0014164U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC0_CNDA4                      (0xF0014168U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC0_CNDC4                      (0xF001416CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC0_CUBC4                      (0xF0014170U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC0_CBC4                       (0xF0014174U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC0_CC4                        (0xF0014178U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC0_CDS_MSP4                   (0xF001417CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC0_CSUS4                      (0xF0014180U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC0_CDUS4                      (0xF0014184U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC0_CIE5                       (0xF0014190U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC0_CID5                       (0xF0014194U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC0_CIM5                       (0xF0014198U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC0_CIS5                       (0xF001419CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC0_CSA5                       (0xF00141A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC0_CDA5                       (0xF00141A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC0_CNDA5                      (0xF00141A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC0_CNDC5                      (0xF00141ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC0_CUBC5                      (0xF00141B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC0_CBC5                       (0xF00141B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC0_CC5                        (0xF00141B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC0_CDS_MSP5                   (0xF00141BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC0_CSUS5                      (0xF00141C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC0_CDUS5                      (0xF00141C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC0_CIE6                       (0xF00141D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC0_CID6                       (0xF00141D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC0_CIM6                       (0xF00141D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC0_CIS6                       (0xF00141DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC0_CSA6                       (0xF00141E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC0_CDA6                       (0xF00141E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC0_CNDA6                      (0xF00141E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC0_CNDC6                      (0xF00141ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC0_CUBC6                      (0xF00141F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC0_CBC6                       (0xF00141F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC0_CC6                        (0xF00141F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC0_CDS_MSP6                   (0xF00141FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC0_CSUS6                      (0xF0014200U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC0_CDUS6                      (0xF0014204U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC0_CIE7                       (0xF0014210U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC0_CID7                       (0xF0014214U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC0_CIM7                       (0xF0014218U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC0_CIS7                       (0xF001421CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC0_CSA7                       (0xF0014220U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC0_CDA7                       (0xF0014224U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC0_CNDA7                      (0xF0014228U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC0_CNDC7                      (0xF001422CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC0_CUBC7                      (0xF0014230U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC0_CBC7                       (0xF0014234U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC0_CC7                        (0xF0014238U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC0_CDS_MSP7                   (0xF001423CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC0_CSUS7                      (0xF0014240U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC0_CDUS7                      (0xF0014244U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC0_CIE8                       (0xF0014250U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC0_CID8                       (0xF0014254U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC0_CIM8                       (0xF0014258U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC0_CIS8                       (0xF001425CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC0_CSA8                       (0xF0014260U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC0_CDA8                       (0xF0014264U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC0_CNDA8                      (0xF0014268U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC0_CNDC8                      (0xF001426CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC0_CUBC8                      (0xF0014270U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC0_CBC8                       (0xF0014274U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC0_CC8                        (0xF0014278U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC0_CDS_MSP8                   (0xF001427CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC0_CSUS8                      (0xF0014280U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC0_CDUS8                      (0xF0014284U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC0_CIE9                       (0xF0014290U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC0_CID9                       (0xF0014294U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC0_CIM9                       (0xF0014298U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC0_CIS9                       (0xF001429CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC0_CSA9                       (0xF00142A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC0_CDA9                       (0xF00142A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC0_CNDA9                      (0xF00142A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC0_CNDC9                      (0xF00142ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC0_CUBC9                      (0xF00142B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC0_CBC9                       (0xF00142B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC0_CC9                        (0xF00142B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC0_CDS_MSP9                   (0xF00142BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC0_CSUS9                      (0xF00142C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC0_CDUS9                      (0xF00142C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC0_CIE10                      (0xF00142D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC0_CID10                      (0xF00142D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC0_CIM10                      (0xF00142D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC0_CIS10                      (0xF00142DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC0_CSA10                      (0xF00142E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC0_CDA10                      (0xF00142E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC0_CNDA10                     (0xF00142E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC0_CNDC10                     (0xF00142ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC0_CUBC10                     (0xF00142F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC0_CBC10                      (0xF00142F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC0_CC10                       (0xF00142F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC0_CDS_MSP10                  (0xF00142FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC0_CSUS10                     (0xF0014300U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC0_CDUS10                     (0xF0014304U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC0_CIE11                      (0xF0014310U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC0_CID11                      (0xF0014314U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC0_CIM11                      (0xF0014318U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC0_CIS11                      (0xF001431CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC0_CSA11                      (0xF0014320U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC0_CDA11                      (0xF0014324U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC0_CNDA11                     (0xF0014328U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC0_CNDC11                     (0xF001432CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC0_CUBC11                     (0xF0014330U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC0_CBC11                      (0xF0014334U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC0_CC11                       (0xF0014338U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC0_CDS_MSP11                  (0xF001433CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC0_CSUS11                     (0xF0014340U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC0_CDUS11                     (0xF0014344U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC0_CIE12                      (0xF0014350U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC0_CID12                      (0xF0014354U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC0_CIM12                      (0xF0014358U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC0_CIS12                      (0xF001435CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC0_CSA12                      (0xF0014360U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC0_CDA12                      (0xF0014364U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC0_CNDA12                     (0xF0014368U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC0_CNDC12                     (0xF001436CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC0_CUBC12                     (0xF0014370U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC0_CBC12                      (0xF0014374U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC0_CC12                       (0xF0014378U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC0_CDS_MSP12                  (0xF001437CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC0_CSUS12                     (0xF0014380U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC0_CDUS12                     (0xF0014384U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC0_CIE13                      (0xF0014390U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC0_CID13                      (0xF0014394U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC0_CIM13                      (0xF0014398U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC0_CIS13                      (0xF001439CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC0_CSA13                      (0xF00143A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC0_CDA13                      (0xF00143A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC0_CNDA13                     (0xF00143A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC0_CNDC13                     (0xF00143ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC0_CUBC13                     (0xF00143B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC0_CBC13                      (0xF00143B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC0_CC13                       (0xF00143B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC0_CDS_MSP13                  (0xF00143BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC0_CSUS13                     (0xF00143C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC0_CDUS13                     (0xF00143C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC0_CIE14                      (0xF00143D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC0_CID14                      (0xF00143D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC0_CIM14                      (0xF00143D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC0_CIS14                      (0xF00143DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC0_CSA14                      (0xF00143E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC0_CDA14                      (0xF00143E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC0_CNDA14                     (0xF00143E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC0_CNDC14                     (0xF00143ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC0_CUBC14                     (0xF00143F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC0_CBC14                      (0xF00143F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC0_CC14                       (0xF00143F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC0_CDS_MSP14                  (0xF00143FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC0_CSUS14                     (0xF0014400U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC0_CDUS14                     (0xF0014404U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC0_CIE15                      (0xF0014410U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC0_CID15                      (0xF0014414U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC0_CIM15                      (0xF0014418U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC0_CIS15                      (0xF001441CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC0_CSA15                      (0xF0014420U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC0_CDA15                      (0xF0014424U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC0_CNDA15                     (0xF0014428U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC0_CNDC15                     (0xF001442CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC0_CUBC15                     (0xF0014430U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC0_CBC15                      (0xF0014434U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC0_CC15                       (0xF0014438U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC0_CDS_MSP15                  (0xF001443CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC0_CSUS15                     (0xF0014440U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC0_CDUS15                     (0xF0014444U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 15) */
#else
  #define REG_XDMAC0_GTYPE     (*(__IO uint32_t*)0xF0014000U) /**< \brief (XDMAC0) Global Type register */
  #define REG_XDMAC0_GCFG      (*(__I  uint32_t*)0xF0014004U) /**< \brief (XDMAC0) Global Configuration Register */
  #define REG_XDMAC0_GWAC      (*(__IO uint32_t*)0xF0014008U) /**< \brief (XDMAC0) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC0_GIE       (*(__O  uint32_t*)0xF001400CU) /**< \brief (XDMAC0) Global Interrupt Enable Register */
  #define REG_XDMAC0_GID       (*(__O  uint32_t*)0xF0014010U) /**< \brief (XDMAC0) Global Interrupt Disable Register */
  #define REG_XDMAC0_GIM       (*(__I  uint32_t*)0xF0014014U) /**< \brief (XDMAC0) Global Interrupt Mask Register */
  #define REG_XDMAC0_GIS       (*(__I  uint32_t*)0xF0014018U) /**< \brief (XDMAC0) Global Interrupt Status Register */
  #define REG_XDMAC0_GE        (*(__O  uint32_t*)0xF001401CU) /**< \brief (XDMAC0) Global Channel Enable Register */
  #define REG_XDMAC0_GD        (*(__O  uint32_t*)0xF0014020U) /**< \brief (XDMAC0) Global Channel Disable Register */
  #define REG_XDMAC0_GS        (*(__I  uint32_t*)0xF0014024U) /**< \brief (XDMAC0) Global Channel Status Register */
  #define REG_XDMAC0_GRS       (*(__IO uint32_t*)0xF0014028U) /**< \brief (XDMAC0) Global Channel Read Suspend Register */
  #define REG_XDMAC0_GWS       (*(__IO uint32_t*)0xF001402CU) /**< \brief (XDMAC0) Global Channel Write Suspend Register */
  #define REG_XDMAC0_GRWS      (*(__O  uint32_t*)0xF0014030U) /**< \brief (XDMAC0) Global Channel Read Write Suspend Register */
  #define REG_XDMAC0_GRWR      (*(__O  uint32_t*)0xF0014034U) /**< \brief (XDMAC0) Global Channel Read Write Resume Register */
  #define REG_XDMAC0_GSWR      (*(__O  uint32_t*)0xF0014038U) /**< \brief (XDMAC0) Global Channel Software Request Register */
  #define REG_XDMAC0_GSWS      (*(__I  uint32_t*)0xF001403CU) /**< \brief (XDMAC0) Global Channel Software Request Status Register */
  #define REG_XDMAC0_GSWF      (*(__O  uint32_t*)0xF0014040U) /**< \brief (XDMAC0) Global Channel Software Flush Request Register */
  #define REG_XDMAC0_CIE0      (*(__O  uint32_t*)0xF0014050U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC0_CID0      (*(__O  uint32_t*)0xF0014054U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC0_CIM0      (*(__O  uint32_t*)0xF0014058U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC0_CIS0      (*(__I  uint32_t*)0xF001405CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC0_CSA0      (*(__IO uint32_t*)0xF0014060U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC0_CDA0      (*(__IO uint32_t*)0xF0014064U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC0_CNDA0     (*(__IO uint32_t*)0xF0014068U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC0_CNDC0     (*(__IO uint32_t*)0xF001406CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC0_CUBC0     (*(__IO uint32_t*)0xF0014070U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC0_CBC0      (*(__IO uint32_t*)0xF0014074U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC0_CC0       (*(__IO uint32_t*)0xF0014078U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC0_CDS_MSP0  (*(__IO uint32_t*)0xF001407CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC0_CSUS0     (*(__IO uint32_t*)0xF0014080U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC0_CDUS0     (*(__IO uint32_t*)0xF0014084U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC0_CIE1      (*(__O  uint32_t*)0xF0014090U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC0_CID1      (*(__O  uint32_t*)0xF0014094U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC0_CIM1      (*(__O  uint32_t*)0xF0014098U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC0_CIS1      (*(__I  uint32_t*)0xF001409CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC0_CSA1      (*(__IO uint32_t*)0xF00140A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC0_CDA1      (*(__IO uint32_t*)0xF00140A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC0_CNDA1     (*(__IO uint32_t*)0xF00140A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC0_CNDC1     (*(__IO uint32_t*)0xF00140ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC0_CUBC1     (*(__IO uint32_t*)0xF00140B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC0_CBC1      (*(__IO uint32_t*)0xF00140B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC0_CC1       (*(__IO uint32_t*)0xF00140B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC0_CDS_MSP1  (*(__IO uint32_t*)0xF00140BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC0_CSUS1     (*(__IO uint32_t*)0xF00140C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC0_CDUS1     (*(__IO uint32_t*)0xF00140C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC0_CIE2      (*(__O  uint32_t*)0xF00140D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC0_CID2      (*(__O  uint32_t*)0xF00140D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC0_CIM2      (*(__O  uint32_t*)0xF00140D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC0_CIS2      (*(__I  uint32_t*)0xF00140DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC0_CSA2      (*(__IO uint32_t*)0xF00140E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC0_CDA2      (*(__IO uint32_t*)0xF00140E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC0_CNDA2     (*(__IO uint32_t*)0xF00140E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC0_CNDC2     (*(__IO uint32_t*)0xF00140ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC0_CUBC2     (*(__IO uint32_t*)0xF00140F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC0_CBC2      (*(__IO uint32_t*)0xF00140F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC0_CC2       (*(__IO uint32_t*)0xF00140F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC0_CDS_MSP2  (*(__IO uint32_t*)0xF00140FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC0_CSUS2     (*(__IO uint32_t*)0xF0014100U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC0_CDUS2     (*(__IO uint32_t*)0xF0014104U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC0_CIE3      (*(__O  uint32_t*)0xF0014110U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC0_CID3      (*(__O  uint32_t*)0xF0014114U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC0_CIM3      (*(__O  uint32_t*)0xF0014118U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC0_CIS3      (*(__I  uint32_t*)0xF001411CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC0_CSA3      (*(__IO uint32_t*)0xF0014120U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC0_CDA3      (*(__IO uint32_t*)0xF0014124U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC0_CNDA3     (*(__IO uint32_t*)0xF0014128U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC0_CNDC3     (*(__IO uint32_t*)0xF001412CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC0_CUBC3     (*(__IO uint32_t*)0xF0014130U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC0_CBC3      (*(__IO uint32_t*)0xF0014134U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC0_CC3       (*(__IO uint32_t*)0xF0014138U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC0_CDS_MSP3  (*(__IO uint32_t*)0xF001413CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC0_CSUS3     (*(__IO uint32_t*)0xF0014140U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC0_CDUS3     (*(__IO uint32_t*)0xF0014144U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC0_CIE4      (*(__O  uint32_t*)0xF0014150U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC0_CID4      (*(__O  uint32_t*)0xF0014154U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC0_CIM4      (*(__O  uint32_t*)0xF0014158U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC0_CIS4      (*(__I  uint32_t*)0xF001415CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC0_CSA4      (*(__IO uint32_t*)0xF0014160U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC0_CDA4      (*(__IO uint32_t*)0xF0014164U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC0_CNDA4     (*(__IO uint32_t*)0xF0014168U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC0_CNDC4     (*(__IO uint32_t*)0xF001416CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC0_CUBC4     (*(__IO uint32_t*)0xF0014170U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC0_CBC4      (*(__IO uint32_t*)0xF0014174U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC0_CC4       (*(__IO uint32_t*)0xF0014178U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC0_CDS_MSP4  (*(__IO uint32_t*)0xF001417CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC0_CSUS4     (*(__IO uint32_t*)0xF0014180U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC0_CDUS4     (*(__IO uint32_t*)0xF0014184U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC0_CIE5      (*(__O  uint32_t*)0xF0014190U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC0_CID5      (*(__O  uint32_t*)0xF0014194U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC0_CIM5      (*(__O  uint32_t*)0xF0014198U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC0_CIS5      (*(__I  uint32_t*)0xF001419CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC0_CSA5      (*(__IO uint32_t*)0xF00141A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC0_CDA5      (*(__IO uint32_t*)0xF00141A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC0_CNDA5     (*(__IO uint32_t*)0xF00141A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC0_CNDC5     (*(__IO uint32_t*)0xF00141ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC0_CUBC5     (*(__IO uint32_t*)0xF00141B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC0_CBC5      (*(__IO uint32_t*)0xF00141B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC0_CC5       (*(__IO uint32_t*)0xF00141B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC0_CDS_MSP5  (*(__IO uint32_t*)0xF00141BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC0_CSUS5     (*(__IO uint32_t*)0xF00141C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC0_CDUS5     (*(__IO uint32_t*)0xF00141C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC0_CIE6      (*(__O  uint32_t*)0xF00141D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC0_CID6      (*(__O  uint32_t*)0xF00141D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC0_CIM6      (*(__O  uint32_t*)0xF00141D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC0_CIS6      (*(__I  uint32_t*)0xF00141DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC0_CSA6      (*(__IO uint32_t*)0xF00141E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC0_CDA6      (*(__IO uint32_t*)0xF00141E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC0_CNDA6     (*(__IO uint32_t*)0xF00141E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC0_CNDC6     (*(__IO uint32_t*)0xF00141ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC0_CUBC6     (*(__IO uint32_t*)0xF00141F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC0_CBC6      (*(__IO uint32_t*)0xF00141F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC0_CC6       (*(__IO uint32_t*)0xF00141F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC0_CDS_MSP6  (*(__IO uint32_t*)0xF00141FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC0_CSUS6     (*(__IO uint32_t*)0xF0014200U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC0_CDUS6     (*(__IO uint32_t*)0xF0014204U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC0_CIE7      (*(__O  uint32_t*)0xF0014210U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC0_CID7      (*(__O  uint32_t*)0xF0014214U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC0_CIM7      (*(__O  uint32_t*)0xF0014218U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC0_CIS7      (*(__I  uint32_t*)0xF001421CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC0_CSA7      (*(__IO uint32_t*)0xF0014220U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC0_CDA7      (*(__IO uint32_t*)0xF0014224U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC0_CNDA7     (*(__IO uint32_t*)0xF0014228U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC0_CNDC7     (*(__IO uint32_t*)0xF001422CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC0_CUBC7     (*(__IO uint32_t*)0xF0014230U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC0_CBC7      (*(__IO uint32_t*)0xF0014234U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC0_CC7       (*(__IO uint32_t*)0xF0014238U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC0_CDS_MSP7  (*(__IO uint32_t*)0xF001423CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC0_CSUS7     (*(__IO uint32_t*)0xF0014240U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC0_CDUS7     (*(__IO uint32_t*)0xF0014244U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC0_CIE8      (*(__O  uint32_t*)0xF0014250U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC0_CID8      (*(__O  uint32_t*)0xF0014254U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC0_CIM8      (*(__O  uint32_t*)0xF0014258U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC0_CIS8      (*(__I  uint32_t*)0xF001425CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC0_CSA8      (*(__IO uint32_t*)0xF0014260U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC0_CDA8      (*(__IO uint32_t*)0xF0014264U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC0_CNDA8     (*(__IO uint32_t*)0xF0014268U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC0_CNDC8     (*(__IO uint32_t*)0xF001426CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC0_CUBC8     (*(__IO uint32_t*)0xF0014270U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC0_CBC8      (*(__IO uint32_t*)0xF0014274U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC0_CC8       (*(__IO uint32_t*)0xF0014278U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC0_CDS_MSP8  (*(__IO uint32_t*)0xF001427CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC0_CSUS8     (*(__IO uint32_t*)0xF0014280U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC0_CDUS8     (*(__IO uint32_t*)0xF0014284U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC0_CIE9      (*(__O  uint32_t*)0xF0014290U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC0_CID9      (*(__O  uint32_t*)0xF0014294U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC0_CIM9      (*(__O  uint32_t*)0xF0014298U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC0_CIS9      (*(__I  uint32_t*)0xF001429CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC0_CSA9      (*(__IO uint32_t*)0xF00142A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC0_CDA9      (*(__IO uint32_t*)0xF00142A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC0_CNDA9     (*(__IO uint32_t*)0xF00142A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC0_CNDC9     (*(__IO uint32_t*)0xF00142ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC0_CUBC9     (*(__IO uint32_t*)0xF00142B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC0_CBC9      (*(__IO uint32_t*)0xF00142B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC0_CC9       (*(__IO uint32_t*)0xF00142B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC0_CDS_MSP9  (*(__IO uint32_t*)0xF00142BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC0_CSUS9     (*(__IO uint32_t*)0xF00142C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC0_CDUS9     (*(__IO uint32_t*)0xF00142C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC0_CIE10     (*(__O  uint32_t*)0xF00142D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC0_CID10     (*(__O  uint32_t*)0xF00142D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC0_CIM10     (*(__O  uint32_t*)0xF00142D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC0_CIS10     (*(__I  uint32_t*)0xF00142DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC0_CSA10     (*(__IO uint32_t*)0xF00142E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC0_CDA10     (*(__IO uint32_t*)0xF00142E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC0_CNDA10    (*(__IO uint32_t*)0xF00142E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC0_CNDC10    (*(__IO uint32_t*)0xF00142ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC0_CUBC10    (*(__IO uint32_t*)0xF00142F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC0_CBC10     (*(__IO uint32_t*)0xF00142F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC0_CC10      (*(__IO uint32_t*)0xF00142F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC0_CDS_MSP10 (*(__IO uint32_t*)0xF00142FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC0_CSUS10    (*(__IO uint32_t*)0xF0014300U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC0_CDUS10    (*(__IO uint32_t*)0xF0014304U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC0_CIE11     (*(__O  uint32_t*)0xF0014310U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC0_CID11     (*(__O  uint32_t*)0xF0014314U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC0_CIM11     (*(__O  uint32_t*)0xF0014318U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC0_CIS11     (*(__I  uint32_t*)0xF001431CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC0_CSA11     (*(__IO uint32_t*)0xF0014320U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC0_CDA11     (*(__IO uint32_t*)0xF0014324U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC0_CNDA11    (*(__IO uint32_t*)0xF0014328U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC0_CNDC11    (*(__IO uint32_t*)0xF001432CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC0_CUBC11    (*(__IO uint32_t*)0xF0014330U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC0_CBC11     (*(__IO uint32_t*)0xF0014334U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC0_CC11      (*(__IO uint32_t*)0xF0014338U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC0_CDS_MSP11 (*(__IO uint32_t*)0xF001433CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC0_CSUS11    (*(__IO uint32_t*)0xF0014340U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC0_CDUS11    (*(__IO uint32_t*)0xF0014344U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC0_CIE12     (*(__O  uint32_t*)0xF0014350U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC0_CID12     (*(__O  uint32_t*)0xF0014354U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC0_CIM12     (*(__O  uint32_t*)0xF0014358U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC0_CIS12     (*(__I  uint32_t*)0xF001435CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC0_CSA12     (*(__IO uint32_t*)0xF0014360U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC0_CDA12     (*(__IO uint32_t*)0xF0014364U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC0_CNDA12    (*(__IO uint32_t*)0xF0014368U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC0_CNDC12    (*(__IO uint32_t*)0xF001436CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC0_CUBC12    (*(__IO uint32_t*)0xF0014370U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC0_CBC12     (*(__IO uint32_t*)0xF0014374U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC0_CC12      (*(__IO uint32_t*)0xF0014378U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC0_CDS_MSP12 (*(__IO uint32_t*)0xF001437CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC0_CSUS12    (*(__IO uint32_t*)0xF0014380U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC0_CDUS12    (*(__IO uint32_t*)0xF0014384U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC0_CIE13     (*(__O  uint32_t*)0xF0014390U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC0_CID13     (*(__O  uint32_t*)0xF0014394U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC0_CIM13     (*(__O  uint32_t*)0xF0014398U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC0_CIS13     (*(__I  uint32_t*)0xF001439CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC0_CSA13     (*(__IO uint32_t*)0xF00143A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC0_CDA13     (*(__IO uint32_t*)0xF00143A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC0_CNDA13    (*(__IO uint32_t*)0xF00143A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC0_CNDC13    (*(__IO uint32_t*)0xF00143ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC0_CUBC13    (*(__IO uint32_t*)0xF00143B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC0_CBC13     (*(__IO uint32_t*)0xF00143B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC0_CC13      (*(__IO uint32_t*)0xF00143B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC0_CDS_MSP13 (*(__IO uint32_t*)0xF00143BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC0_CSUS13    (*(__IO uint32_t*)0xF00143C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC0_CDUS13    (*(__IO uint32_t*)0xF00143C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC0_CIE14     (*(__O  uint32_t*)0xF00143D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC0_CID14     (*(__O  uint32_t*)0xF00143D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC0_CIM14     (*(__O  uint32_t*)0xF00143D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC0_CIS14     (*(__I  uint32_t*)0xF00143DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC0_CSA14     (*(__IO uint32_t*)0xF00143E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC0_CDA14     (*(__IO uint32_t*)0xF00143E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC0_CNDA14    (*(__IO uint32_t*)0xF00143E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC0_CNDC14    (*(__IO uint32_t*)0xF00143ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC0_CUBC14    (*(__IO uint32_t*)0xF00143F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC0_CBC14     (*(__IO uint32_t*)0xF00143F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC0_CC14      (*(__IO uint32_t*)0xF00143F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC0_CDS_MSP14 (*(__IO uint32_t*)0xF00143FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC0_CSUS14    (*(__IO uint32_t*)0xF0014400U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC0_CDUS14    (*(__IO uint32_t*)0xF0014404U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC0_CIE15     (*(__O  uint32_t*)0xF0014410U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC0_CID15     (*(__O  uint32_t*)0xF0014414U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC0_CIM15     (*(__O  uint32_t*)0xF0014418U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC0_CIS15     (*(__I  uint32_t*)0xF001441CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC0_CSA15     (*(__IO uint32_t*)0xF0014420U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC0_CDA15     (*(__IO uint32_t*)0xF0014424U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC0_CNDA15    (*(__IO uint32_t*)0xF0014428U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC0_CNDC15    (*(__IO uint32_t*)0xF001442CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC0_CUBC15    (*(__IO uint32_t*)0xF0014430U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC0_CBC15     (*(__IO uint32_t*)0xF0014434U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC0_CC15      (*(__IO uint32_t*)0xF0014438U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC0_CDS_MSP15 (*(__IO uint32_t*)0xF001443CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC0_CSUS15    (*(__IO uint32_t*)0xF0014440U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC0_CDUS15    (*(__IO uint32_t*)0xF0014444U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 15) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for PMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PMC_SCER                     (0xF0018000U) /**< \brief (PMC) System Clock Enable Register */
  #define REG_PMC_SCDR                     (0xF0018004U) /**< \brief (PMC) System Clock Disable Register */
  #define REG_PMC_SCSR                     (0xF0018008U) /**< \brief (PMC) System Clock Status Register */
  #define REG_PMC_PCER0                    (0xF0018010U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
  #define REG_PMC_PCDR0                    (0xF0018014U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */
  #define REG_PMC_PCSR0                    (0xF0018018U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
  #define REG_CKGR_UCKR                    (0xF001801CU) /**< \brief (PMC) UTMI Clock Register */
  #define REG_CKGR_MOR                     (0xF0018020U) /**< \brief (PMC) Main Oscillator Register */
  #define REG_CKGR_MCFR                    (0xF0018024U) /**< \brief (PMC) Main Clock Frequency Register */
  #define REG_CKGR_PLLAR                   (0xF0018028U) /**< \brief (PMC) PLLA Register */
  #define REG_PMC_MCKR                     (0xF0018030U) /**< \brief (PMC) Master Clock Register */
  #define REG_PMC_USB                      (0xF0018038U) /**< \brief (PMC) USB Clock Register */
  #define REG_PMC_SMD                      (0xF001803CU) /**< \brief (PMC) Soft Modem Clock Register */
  #define REG_PMC_PCK                      (0xF0018040U) /**< \brief (PMC) Programmable Clock 0 Register */
  #define REG_PMC_IER                      (0xF0018060U) /**< \brief (PMC) Interrupt Enable Register */
  #define REG_PMC_IDR                      (0xF0018064U) /**< \brief (PMC) Interrupt Disable Register */
  #define REG_PMC_SR                       (0xF0018068U) /**< \brief (PMC) Status Register */
  #define REG_PMC_IMR                      (0xF001806CU) /**< \brief (PMC) Interrupt Mask Register */
  #define REG_PMC_FOCR                     (0xF0018078U) /**< \brief (PMC) Fault Output Clear Register */
  #define REG_PMC_PLLICPR                  (0xF0018080U) /**< \brief (PMC) PLL Charge Pump Current Register */
  #define REG_PMC_WPMR                     (0xF00180E4U) /**< \brief (PMC) Write Protect Mode Register */
  #define REG_PMC_WPSR                     (0xF00180E8U) /**< \brief (PMC) Write Protect Status Register */
  #define REG_PMC_PCER1                    (0xF0018100U) /**< \brief (PMC) Peripheral Clock Enable Register 1 */
  #define REG_PMC_PCDR1                    (0xF0018104U) /**< \brief (PMC) Peripheral Clock Disable Register 1 */
  #define REG_PMC_PCSR1                    (0xF0018108U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
  #define REG_PMC_PCR                      (0xF001810CU) /**< \brief (PMC) Peripheral Control Register */
#else
  #define REG_PMC_SCER    (*(__O  uint32_t*)0xF0018000U) /**< \brief (PMC) System Clock Enable Register */
  #define REG_PMC_SCDR    (*(__O  uint32_t*)0xF0018004U) /**< \brief (PMC) System Clock Disable Register */
  #define REG_PMC_SCSR    (*(__I  uint32_t*)0xF0018008U) /**< \brief (PMC) System Clock Status Register */
  #define REG_PMC_PCER0   (*(__O  uint32_t*)0xF0018010U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
  #define REG_PMC_PCDR0   (*(__O  uint32_t*)0xF0018014U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */
  #define REG_PMC_PCSR0   (*(__I  uint32_t*)0xF0018018U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
  #define REG_CKGR_UCKR   (*(__IO uint32_t*)0xF001801CU) /**< \brief (PMC) UTMI Clock Register */
  #define REG_CKGR_MOR    (*(__IO uint32_t*)0xF0018020U) /**< \brief (PMC) Main Oscillator Register */
  #define REG_CKGR_MCFR   (*(__I  uint32_t*)0xF0018024U) /**< \brief (PMC) Main Clock Frequency Register */
  #define REG_CKGR_PLLAR  (*(__IO uint32_t*)0xF0018028U) /**< \brief (PMC) PLLA Register */
  #define REG_PMC_MCKR    (*(__IO uint32_t*)0xF0018030U) /**< \brief (PMC) Master Clock Register */
  #define REG_PMC_USB     (*(__IO uint32_t*)0xF0018038U) /**< \brief (PMC) USB Clock Register */
  #define REG_PMC_SMD     (*(__IO uint32_t*)0xF001803CU) /**< \brief (PMC) Soft Modem Clock Register */
  #define REG_PMC_PCK     (*(__IO uint32_t*)0xF0018040U) /**< \brief (PMC) Programmable Clock 0 Register */
  #define REG_PMC_IER     (*(__O  uint32_t*)0xF0018060U) /**< \brief (PMC) Interrupt Enable Register */
  #define REG_PMC_IDR     (*(__O  uint32_t*)0xF0018064U) /**< \brief (PMC) Interrupt Disable Register */
  #define REG_PMC_SR      (*(__I  uint32_t*)0xF0018068U) /**< \brief (PMC) Status Register */
  #define REG_PMC_IMR     (*(__I  uint32_t*)0xF001806CU) /**< \brief (PMC) Interrupt Mask Register */
  #define REG_PMC_FOCR    (*(__O  uint32_t*)0xF0018078U) /**< \brief (PMC) Fault Output Clear Register */
  #define REG_PMC_PLLICPR (*(__O  uint32_t*)0xF0018080U) /**< \brief (PMC) PLL Charge Pump Current Register */
  #define REG_PMC_WPMR    (*(__IO uint32_t*)0xF00180E4U) /**< \brief (PMC) Write Protect Mode Register */
  #define REG_PMC_WPSR    (*(__I  uint32_t*)0xF00180E8U) /**< \brief (PMC) Write Protect Status Register */
  #define REG_PMC_PCER1   (*(__O  uint32_t*)0xF0018100U) /**< \brief (PMC) Peripheral Clock Enable Register 1 */
  #define REG_PMC_PCDR1   (*(__O  uint32_t*)0xF0018104U) /**< \brief (PMC) Peripheral Clock Disable Register 1 */
  #define REG_PMC_PCSR1   (*(__I  uint32_t*)0xF0018108U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
  #define REG_PMC_PCR     (*(__IO uint32_t*)0xF001810CU) /**< \brief (PMC) Peripheral Control Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for MATRIX0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_MATRIX0_MCFG                    (0xF001C000U) /**< \brief (MATRIX0) Master Configuration Register */
  #define REG_MATRIX0_SCFG                    (0xF001C040U) /**< \brief (MATRIX0) Slave Configuration Register */
  #define REG_MATRIX0_PRAS0                   (0xF001C080U) /**< \brief (MATRIX0) Priority Register A for Slave 0 */
  #define REG_MATRIX0_PRBS0                   (0xF001C084U) /**< \brief (MATRIX0) Priority Register B for Slave 0 */
  #define REG_MATRIX0_PRAS1                   (0xF001C088U) /**< \brief (MATRIX0) Priority Register A for Slave 1 */
  #define REG_MATRIX0_PRBS1                   (0xF001C08CU) /**< \brief (MATRIX0) Priority Register B for Slave 1 */
  #define REG_MATRIX0_PRAS2                   (0xF001C090U) /**< \brief (MATRIX0) Priority Register A for Slave 2 */
  #define REG_MATRIX0_PRBS2                   (0xF001C094U) /**< \brief (MATRIX0) Priority Register B for Slave 2 */
  #define REG_MATRIX0_PRAS3                   (0xF001C098U) /**< \brief (MATRIX0) Priority Register A for Slave 3 */
  #define REG_MATRIX0_PRBS3                   (0xF001C09CU) /**< \brief (MATRIX0) Priority Register B for Slave 3 */
  #define REG_MATRIX0_PRAS4                   (0xF001C0A0U) /**< \brief (MATRIX0) Priority Register A for Slave 4 */
  #define REG_MATRIX0_PRBS4                   (0xF001C0A4U) /**< \brief (MATRIX0) Priority Register B for Slave 4 */
  #define REG_MATRIX0_PRAS5                   (0xF001C0A8U) /**< \brief (MATRIX0) Priority Register A for Slave 5 */
  #define REG_MATRIX0_PRBS5                   (0xF001C0ACU) /**< \brief (MATRIX0) Priority Register B for Slave 5 */
  #define REG_MATRIX0_PRAS6                   (0xF001C0B0U) /**< \brief (MATRIX0) Priority Register A for Slave 6 */
  #define REG_MATRIX0_PRBS6                   (0xF001C0B4U) /**< \brief (MATRIX0) Priority Register B for Slave 6 */
  #define REG_MATRIX0_PRAS7                   (0xF001C0B8U) /**< \brief (MATRIX0) Priority Register A for Slave 7 */
  #define REG_MATRIX0_PRBS7                   (0xF001C0BCU) /**< \brief (MATRIX0) Priority Register B for Slave 7 */
  #define REG_MATRIX0_PRAS8                   (0xF001C0C0U) /**< \brief (MATRIX0) Priority Register A for Slave 8 */
  #define REG_MATRIX0_PRBS8                   (0xF001C0C4U) /**< \brief (MATRIX0) Priority Register B for Slave 8 */
  #define REG_MATRIX0_PRAS9                   (0xF001C0C8U) /**< \brief (MATRIX0) Priority Register A for Slave 9 */
  #define REG_MATRIX0_PRBS9                   (0xF001C0CCU) /**< \brief (MATRIX0) Priority Register B for Slave 9 */
  #define REG_MATRIX0_PRAS10                  (0xF001C0D0U) /**< \brief (MATRIX0) Priority Register A for Slave 10 */
  #define REG_MATRIX0_PRBS10                  (0xF001C0D4U) /**< \brief (MATRIX0) Priority Register B for Slave 10 */
  #define REG_MATRIX0_PRAS11                  (0xF001C0D8U) /**< \brief (MATRIX0) Priority Register A for Slave 11 */
  #define REG_MATRIX0_PRBS11                  (0xF001C0DCU) /**< \brief (MATRIX0) Priority Register B for Slave 11 */
  #define REG_MATRIX0_PRAS12                  (0xF001C0E0U) /**< \brief (MATRIX0) Priority Register A for Slave 12 */
  #define REG_MATRIX0_PRBS12                  (0xF001C0E4U) /**< \brief (MATRIX0) Priority Register B for Slave 12 */
  #define REG_MATRIX0_MEIER                   (0xF001C150U) /**< \brief (MATRIX0) Master Error Interrupt Enable Register */
  #define REG_MATRIX0_MEIDR                   (0xF001C154U) /**< \brief (MATRIX0) Master Error Interrupt Disable Register */
  #define REG_MATRIX0_MEIMR                   (0xF001C158U) /**< \brief (MATRIX0) Master Error Interrupt Mask Register */
  #define REG_MATRIX0_MESR                    (0xF001C15CU) /**< \brief (MATRIX0) Master Error Status Register */
  #define REG_MATRIX0_MEAR                    (0xF001C160U) /**< \brief (MATRIX0) Master 0 Error Address Register */
  #define REG_MATRIX0_WPMR                    (0xF001C1E4U) /**< \brief (MATRIX0) Write Protect Mode Register */
  #define REG_MATRIX0_WPSR                    (0xF001C1E8U) /**< \brief (MATRIX0) Write Protect Status Register */
  #define REG_MATRIX0_SSR                     (0xF001C200U) /**< \brief (MATRIX0) Security Slave 0 Register */
  #define REG_MATRIX0_SASSR                   (0xF001C240U) /**< \brief (MATRIX0) Security Areas Split Slave 0 Register */
  #define REG_MATRIX0_SRTSR                   (0xF001C280U) /**< \brief (MATRIX0) Security Region Top Slave 0 Register */
  #define REG_MATRIX0_SPSELR                  (0xF001C2C0U) /**< \brief (MATRIX0) Security Peripheral Select 1 Register */
#else
  #define REG_MATRIX0_MCFG   (*(__IO uint32_t*)0xF001C000U) /**< \brief (MATRIX0) Master Configuration Register */
  #define REG_MATRIX0_SCFG   (*(__IO uint32_t*)0xF001C040U) /**< \brief (MATRIX0) Slave Configuration Register */
  #define REG_MATRIX0_PRAS0  (*(__IO uint32_t*)0xF001C080U) /**< \brief (MATRIX0) Priority Register A for Slave 0 */
  #define REG_MATRIX0_PRBS0  (*(__IO uint32_t*)0xF001C084U) /**< \brief (MATRIX0) Priority Register B for Slave 0 */
  #define REG_MATRIX0_PRAS1  (*(__IO uint32_t*)0xF001C088U) /**< \brief (MATRIX0) Priority Register A for Slave 1 */
  #define REG_MATRIX0_PRBS1  (*(__IO uint32_t*)0xF001C08CU) /**< \brief (MATRIX0) Priority Register B for Slave 1 */
  #define REG_MATRIX0_PRAS2  (*(__IO uint32_t*)0xF001C090U) /**< \brief (MATRIX0) Priority Register A for Slave 2 */
  #define REG_MATRIX0_PRBS2  (*(__IO uint32_t*)0xF001C094U) /**< \brief (MATRIX0) Priority Register B for Slave 2 */
  #define REG_MATRIX0_PRAS3  (*(__IO uint32_t*)0xF001C098U) /**< \brief (MATRIX0) Priority Register A for Slave 3 */
  #define REG_MATRIX0_PRBS3  (*(__IO uint32_t*)0xF001C09CU) /**< \brief (MATRIX0) Priority Register B for Slave 3 */
  #define REG_MATRIX0_PRAS4  (*(__IO uint32_t*)0xF001C0A0U) /**< \brief (MATRIX0) Priority Register A for Slave 4 */
  #define REG_MATRIX0_PRBS4  (*(__IO uint32_t*)0xF001C0A4U) /**< \brief (MATRIX0) Priority Register B for Slave 4 */
  #define REG_MATRIX0_PRAS5  (*(__IO uint32_t*)0xF001C0A8U) /**< \brief (MATRIX0) Priority Register A for Slave 5 */
  #define REG_MATRIX0_PRBS5  (*(__IO uint32_t*)0xF001C0ACU) /**< \brief (MATRIX0) Priority Register B for Slave 5 */
  #define REG_MATRIX0_PRAS6  (*(__IO uint32_t*)0xF001C0B0U) /**< \brief (MATRIX0) Priority Register A for Slave 6 */
  #define REG_MATRIX0_PRBS6  (*(__IO uint32_t*)0xF001C0B4U) /**< \brief (MATRIX0) Priority Register B for Slave 6 */
  #define REG_MATRIX0_PRAS7  (*(__IO uint32_t*)0xF001C0B8U) /**< \brief (MATRIX0) Priority Register A for Slave 7 */
  #define REG_MATRIX0_PRBS7  (*(__IO uint32_t*)0xF001C0BCU) /**< \brief (MATRIX0) Priority Register B for Slave 7 */
  #define REG_MATRIX0_PRAS8  (*(__IO uint32_t*)0xF001C0C0U) /**< \brief (MATRIX0) Priority Register A for Slave 8 */
  #define REG_MATRIX0_PRBS8  (*(__IO uint32_t*)0xF001C0C4U) /**< \brief (MATRIX0) Priority Register B for Slave 8 */
  #define REG_MATRIX0_PRAS9  (*(__IO uint32_t*)0xF001C0C8U) /**< \brief (MATRIX0) Priority Register A for Slave 9 */
  #define REG_MATRIX0_PRBS9  (*(__IO uint32_t*)0xF001C0CCU) /**< \brief (MATRIX0) Priority Register B for Slave 9 */
  #define REG_MATRIX0_PRAS10 (*(__IO uint32_t*)0xF001C0D0U) /**< \brief (MATRIX0) Priority Register A for Slave 10 */
  #define REG_MATRIX0_PRBS10 (*(__IO uint32_t*)0xF001C0D4U) /**< \brief (MATRIX0) Priority Register B for Slave 10 */
  #define REG_MATRIX0_PRAS11 (*(__IO uint32_t*)0xF001C0D8U) /**< \brief (MATRIX0) Priority Register A for Slave 11 */
  #define REG_MATRIX0_PRBS11 (*(__IO uint32_t*)0xF001C0DCU) /**< \brief (MATRIX0) Priority Register B for Slave 11 */
  #define REG_MATRIX0_PRAS12 (*(__IO uint32_t*)0xF001C0E0U) /**< \brief (MATRIX0) Priority Register A for Slave 12 */
  #define REG_MATRIX0_PRBS12 (*(__IO uint32_t*)0xF001C0E4U) /**< \brief (MATRIX0) Priority Register B for Slave 12 */
  #define REG_MATRIX0_MEIER  (*(__O  uint32_t*)0xF001C150U) /**< \brief (MATRIX0) Master Error Interrupt Enable Register */
  #define REG_MATRIX0_MEIDR  (*(__O  uint32_t*)0xF001C154U) /**< \brief (MATRIX0) Master Error Interrupt Disable Register */
  #define REG_MATRIX0_MEIMR  (*(__I  uint32_t*)0xF001C158U) /**< \brief (MATRIX0) Master Error Interrupt Mask Register */
  #define REG_MATRIX0_MESR   (*(__I  uint32_t*)0xF001C15CU) /**< \brief (MATRIX0) Master Error Status Register */
  #define REG_MATRIX0_MEAR   (*(__I  uint32_t*)0xF001C160U) /**< \brief (MATRIX0) Master 0 Error Address Register */
  #define REG_MATRIX0_WPMR   (*(__IO uint32_t*)0xF001C1E4U) /**< \brief (MATRIX0) Write Protect Mode Register */
  #define REG_MATRIX0_WPSR   (*(__I  uint32_t*)0xF001C1E8U) /**< \brief (MATRIX0) Write Protect Status Register */
  #define REG_MATRIX0_SSR    (*(__IO uint32_t*)0xF001C200U) /**< \brief (MATRIX0) Security Slave 0 Register */
  #define REG_MATRIX0_SASSR  (*(__IO uint32_t*)0xF001C240U) /**< \brief (MATRIX0) Security Areas Split Slave 0 Register */
  #define REG_MATRIX0_SRTSR  (*(__IO uint32_t*)0xF001C280U) /**< \brief (MATRIX0) Security Region Top Slave 0 Register */
  #define REG_MATRIX0_SPSELR (*(__IO uint32_t*)0xF001C2C0U) /**< \brief (MATRIX0) Security Peripheral Select 1 Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for HSMCI0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_HSMCI0_CR                     (0xF8000000U) /**< \brief (HSMCI0) Control Register */
  #define REG_HSMCI0_MR                     (0xF8000004U) /**< \brief (HSMCI0) Mode Register */
  #define REG_HSMCI0_DTOR                   (0xF8000008U) /**< \brief (HSMCI0) Data Timeout Register */
  #define REG_HSMCI0_SDCR                   (0xF800000CU) /**< \brief (HSMCI0) SD/SDIO Card Register */
  #define REG_HSMCI0_ARGR                   (0xF8000010U) /**< \brief (HSMCI0) Argument Register */
  #define REG_HSMCI0_CMDR                   (0xF8000014U) /**< \brief (HSMCI0) Command Register */
  #define REG_HSMCI0_BLKR                   (0xF8000018U) /**< \brief (HSMCI0) Block Register */
  #define REG_HSMCI0_CSTOR                  (0xF800001CU) /**< \brief (HSMCI0) Completion Signal Timeout Register */
  #define REG_HSMCI0_RSPR                   (0xF8000020U) /**< \brief (HSMCI0) Response Register */
  #define REG_HSMCI0_RDR                    (0xF8000030U) /**< \brief (HSMCI0) Receive Data Register */
  #define REG_HSMCI0_TDR                    (0xF8000034U) /**< \brief (HSMCI0) Transmit Data Register */
  #define REG_HSMCI0_SR                     (0xF8000040U) /**< \brief (HSMCI0) Status Register */
  #define REG_HSMCI0_IER                    (0xF8000044U) /**< \brief (HSMCI0) Interrupt Enable Register */
  #define REG_HSMCI0_IDR                    (0xF8000048U) /**< \brief (HSMCI0) Interrupt Disable Register */
  #define REG_HSMCI0_IMR                    (0xF800004CU) /**< \brief (HSMCI0) Interrupt Mask Register */
  #define REG_HSMCI0_DMA                    (0xF8000050U) /**< \brief (HSMCI0) DMA Configuration Register */
  #define REG_HSMCI0_CFG                    (0xF8000054U) /**< \brief (HSMCI0) Configuration Register */
  #define REG_HSMCI0_WPMR                   (0xF80000E4U) /**< \brief (HSMCI0) Write Protection Mode Register */
  #define REG_HSMCI0_WPSR                   (0xF80000E8U) /**< \brief (HSMCI0) Write Protection Status Register */
  #define REG_HSMCI0_FIFO                   (0xF8000200U) /**< \brief (HSMCI0) FIFO Memory Aperture0 */
#else
  #define REG_HSMCI0_CR    (*(__O  uint32_t*)0xF8000000U) /**< \brief (HSMCI0) Control Register */
  #define REG_HSMCI0_MR    (*(__IO uint32_t*)0xF8000004U) /**< \brief (HSMCI0) Mode Register */
  #define REG_HSMCI0_DTOR  (*(__IO uint32_t*)0xF8000008U) /**< \brief (HSMCI0) Data Timeout Register */
  #define REG_HSMCI0_SDCR  (*(__IO uint32_t*)0xF800000CU) /**< \brief (HSMCI0) SD/SDIO Card Register */
  #define REG_HSMCI0_ARGR  (*(__IO uint32_t*)0xF8000010U) /**< \brief (HSMCI0) Argument Register */
  #define REG_HSMCI0_CMDR  (*(__O  uint32_t*)0xF8000014U) /**< \brief (HSMCI0) Command Register */
  #define REG_HSMCI0_BLKR  (*(__IO uint32_t*)0xF8000018U) /**< \brief (HSMCI0) Block Register */
  #define REG_HSMCI0_CSTOR (*(__IO uint32_t*)0xF800001CU) /**< \brief (HSMCI0) Completion Signal Timeout Register */
  #define REG_HSMCI0_RSPR  (*(__I  uint32_t*)0xF8000020U) /**< \brief (HSMCI0) Response Register */
  #define REG_HSMCI0_RDR   (*(__I  uint32_t*)0xF8000030U) /**< \brief (HSMCI0) Receive Data Register */
  #define REG_HSMCI0_TDR   (*(__O  uint32_t*)0xF8000034U) /**< \brief (HSMCI0) Transmit Data Register */
  #define REG_HSMCI0_SR    (*(__I  uint32_t*)0xF8000040U) /**< \brief (HSMCI0) Status Register */
  #define REG_HSMCI0_IER   (*(__O  uint32_t*)0xF8000044U) /**< \brief (HSMCI0) Interrupt Enable Register */
  #define REG_HSMCI0_IDR   (*(__O  uint32_t*)0xF8000048U) /**< \brief (HSMCI0) Interrupt Disable Register */
  #define REG_HSMCI0_IMR   (*(__I  uint32_t*)0xF800004CU) /**< \brief (HSMCI0) Interrupt Mask Register */
  #define REG_HSMCI0_DMA   (*(__IO uint32_t*)0xF8000050U) /**< \brief (HSMCI0) DMA Configuration Register */
  #define REG_HSMCI0_CFG   (*(__IO uint32_t*)0xF8000054U) /**< \brief (HSMCI0) Configuration Register */
  #define REG_HSMCI0_WPMR  (*(__IO uint32_t*)0xF80000E4U) /**< \brief (HSMCI0) Write Protection Mode Register */
  #define REG_HSMCI0_WPSR  (*(__I  uint32_t*)0xF80000E8U) /**< \brief (HSMCI0) Write Protection Status Register */
  #define REG_HSMCI0_FIFO  (*(__IO uint32_t*)0xF8000200U) /**< \brief (HSMCI0) FIFO Memory Aperture0 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for UART0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_UART0_CR                    (0xF8004000U) /**< \brief (UART0) Control Register */
  #define REG_UART0_MR                    (0xF8004004U) /**< \brief (UART0) Mode Register */
  #define REG_UART0_IER                   (0xF8004008U) /**< \brief (UART0) Interrupt Enable Register */
  #define REG_UART0_IDR                   (0xF800400CU) /**< \brief (UART0) Interrupt Disable Register */
  #define REG_UART0_IMR                   (0xF8004010U) /**< \brief (UART0) Interrupt Mask Register */
  #define REG_UART0_SR                    (0xF8004014U) /**< \brief (UART0) Status Register */
  #define REG_UART0_RHR                   (0xF8004018U) /**< \brief (UART0) Receive Holding Register */
  #define REG_UART0_THR                   (0xF800401CU) /**< \brief (UART0) Transmit Holding Register */
  #define REG_UART0_BRGR                  (0xF8004020U) /**< \brief (UART0) Baud Rate Generator Register */
#else
  #define REG_UART0_CR   (*(__O  uint32_t*)0xF8004000U) /**< \brief (UART0) Control Register */
  #define REG_UART0_MR   (*(__IO uint32_t*)0xF8004004U) /**< \brief (UART0) Mode Register */
  #define REG_UART0_IER  (*(__O  uint32_t*)0xF8004008U) /**< \brief (UART0) Interrupt Enable Register */
  #define REG_UART0_IDR  (*(__O  uint32_t*)0xF800400CU) /**< \brief (UART0) Interrupt Disable Register */
  #define REG_UART0_IMR  (*(__I  uint32_t*)0xF8004010U) /**< \brief (UART0) Interrupt Mask Register */
  #define REG_UART0_SR   (*(__I  uint32_t*)0xF8004014U) /**< \brief (UART0) Status Register */
  #define REG_UART0_RHR  (*(__I  uint32_t*)0xF8004018U) /**< \brief (UART0) Receive Holding Register */
  #define REG_UART0_THR  (*(__O  uint32_t*)0xF800401CU) /**< \brief (UART0) Transmit Holding Register */
  #define REG_UART0_BRGR (*(__IO uint32_t*)0xF8004020U) /**< \brief (UART0) Baud Rate Generator Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for SPI0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SPI0_CR                    (0xF8010000U) /**< \brief (SPI0) Control Register */
  #define REG_SPI0_MR                    (0xF8010004U) /**< \brief (SPI0) Mode Register */
  #define REG_SPI0_RDR                   (0xF8010008U) /**< \brief (SPI0) Receive Data Register */
  #define REG_SPI0_TDR                   (0xF801000CU) /**< \brief (SPI0) Transmit Data Register */
  #define REG_SPI0_SR                    (0xF8010010U) /**< \brief (SPI0) Status Register */
  #define REG_SPI0_IER                   (0xF8010014U) /**< \brief (SPI0) Interrupt Enable Register */
  #define REG_SPI0_IDR                   (0xF8010018U) /**< \brief (SPI0) Interrupt Disable Register */
  #define REG_SPI0_IMR                   (0xF801001CU) /**< \brief (SPI0) Interrupt Mask Register */
  #define REG_SPI0_CSR                   (0xF8010030U) /**< \brief (SPI0) Chip Select Register */
  #define REG_SPI0_WPMR                  (0xF80100E4U) /**< \brief (SPI0) Write Protection Control Register */
  #define REG_SPI0_WPSR                  (0xF80100E8U) /**< \brief (SPI0) Write Protection Status Register */
#else
  #define REG_SPI0_CR   (*(__O  uint32_t*)0xF8010000U) /**< \brief (SPI0) Control Register */
  #define REG_SPI0_MR   (*(__IO uint32_t*)0xF8010004U) /**< \brief (SPI0) Mode Register */
  #define REG_SPI0_RDR  (*(__I  uint32_t*)0xF8010008U) /**< \brief (SPI0) Receive Data Register */
  #define REG_SPI0_TDR  (*(__O  uint32_t*)0xF801000CU) /**< \brief (SPI0) Transmit Data Register */
  #define REG_SPI0_SR   (*(__I  uint32_t*)0xF8010010U) /**< \brief (SPI0) Status Register */
  #define REG_SPI0_IER  (*(__O  uint32_t*)0xF8010014U) /**< \brief (SPI0) Interrupt Enable Register */
  #define REG_SPI0_IDR  (*(__O  uint32_t*)0xF8010018U) /**< \brief (SPI0) Interrupt Disable Register */
  #define REG_SPI0_IMR  (*(__I  uint32_t*)0xF801001CU) /**< \brief (SPI0) Interrupt Mask Register */
  #define REG_SPI0_CSR  (*(__IO uint32_t*)0xF8010030U) /**< \brief (SPI0) Chip Select Register */
  #define REG_SPI0_WPMR (*(__IO uint32_t*)0xF80100E4U) /**< \brief (SPI0) Write Protection Control Register */
  #define REG_SPI0_WPSR (*(__I  uint32_t*)0xF80100E8U) /**< \brief (SPI0) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for TWI0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_TWI0_CR                    (0xF8014000U) /**< \brief (TWI0) Control Register */
  #define REG_TWI0_MMR                   (0xF8014004U) /**< \brief (TWI0) Master Mode Register */
  #define REG_TWI0_SMR                   (0xF8014008U) /**< \brief (TWI0) Slave Mode Register */
  #define REG_TWI0_IADR                  (0xF801400CU) /**< \brief (TWI0) Internal Address Register */
  #define REG_TWI0_CWGR                  (0xF8014010U) /**< \brief (TWI0) Clock Waveform Generator Register */
  #define REG_TWI0_SR                    (0xF8014020U) /**< \brief (TWI0) Status Register */
  #define REG_TWI0_IER                   (0xF8014024U) /**< \brief (TWI0) Interrupt Enable Register */
  #define REG_TWI0_IDR                   (0xF8014028U) /**< \brief (TWI0) Interrupt Disable Register */
  #define REG_TWI0_IMR                   (0xF801402CU) /**< \brief (TWI0) Interrupt Mask Register */
  #define REG_TWI0_RHR                   (0xF8014030U) /**< \brief (TWI0) Receive Holding Register */
  #define REG_TWI0_THR                   (0xF8014034U) /**< \brief (TWI0) Transmit Holding Register */
  #define REG_TWI0_WPMR                  (0xF80140E4U) /**< \brief (TWI0) Protection Mode Register */
  #define REG_TWI0_WPSR                  (0xF80140E8U) /**< \brief (TWI0) Protection Status Register */
#else
  #define REG_TWI0_CR   (*(__O  uint32_t*)0xF8014000U) /**< \brief (TWI0) Control Register */
  #define REG_TWI0_MMR  (*(__IO uint32_t*)0xF8014004U) /**< \brief (TWI0) Master Mode Register */
  #define REG_TWI0_SMR  (*(__IO uint32_t*)0xF8014008U) /**< \brief (TWI0) Slave Mode Register */
  #define REG_TWI0_IADR (*(__IO uint32_t*)0xF801400CU) /**< \brief (TWI0) Internal Address Register */
  #define REG_TWI0_CWGR (*(__IO uint32_t*)0xF8014010U) /**< \brief (TWI0) Clock Waveform Generator Register */
  #define REG_TWI0_SR   (*(__I  uint32_t*)0xF8014020U) /**< \brief (TWI0) Status Register */
  #define REG_TWI0_IER  (*(__O  uint32_t*)0xF8014024U) /**< \brief (TWI0) Interrupt Enable Register */
  #define REG_TWI0_IDR  (*(__O  uint32_t*)0xF8014028U) /**< \brief (TWI0) Interrupt Disable Register */
  #define REG_TWI0_IMR  (*(__I  uint32_t*)0xF801402CU) /**< \brief (TWI0) Interrupt Mask Register */
  #define REG_TWI0_RHR  (*(__I  uint32_t*)0xF8014030U) /**< \brief (TWI0) Receive Holding Register */
  #define REG_TWI0_THR  (*(__O  uint32_t*)0xF8014034U) /**< \brief (TWI0) Transmit Holding Register */
  #define REG_TWI0_WPMR (*(__IO uint32_t*)0xF80140E4U) /**< \brief (TWI0) Protection Mode Register */
  #define REG_TWI0_WPSR (*(__I  uint32_t*)0xF80140E8U) /**< \brief (TWI0) Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for TWI1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_TWI1_CR                    (0xF8018000U) /**< \brief (TWI1) Control Register */
  #define REG_TWI1_MMR                   (0xF8018004U) /**< \brief (TWI1) Master Mode Register */
  #define REG_TWI1_SMR                   (0xF8018008U) /**< \brief (TWI1) Slave Mode Register */
  #define REG_TWI1_IADR                  (0xF801800CU) /**< \brief (TWI1) Internal Address Register */
  #define REG_TWI1_CWGR                  (0xF8018010U) /**< \brief (TWI1) Clock Waveform Generator Register */
  #define REG_TWI1_SR                    (0xF8018020U) /**< \brief (TWI1) Status Register */
  #define REG_TWI1_IER                   (0xF8018024U) /**< \brief (TWI1) Interrupt Enable Register */
  #define REG_TWI1_IDR                   (0xF8018028U) /**< \brief (TWI1) Interrupt Disable Register */
  #define REG_TWI1_IMR                   (0xF801802CU) /**< \brief (TWI1) Interrupt Mask Register */
  #define REG_TWI1_RHR                   (0xF8018030U) /**< \brief (TWI1) Receive Holding Register */
  #define REG_TWI1_THR                   (0xF8018034U) /**< \brief (TWI1) Transmit Holding Register */
  #define REG_TWI1_WPMR                  (0xF80180E4U) /**< \brief (TWI1) Protection Mode Register */
  #define REG_TWI1_WPSR                  (0xF80180E8U) /**< \brief (TWI1) Protection Status Register */
#else
  #define REG_TWI1_CR   (*(__O  uint32_t*)0xF8018000U) /**< \brief (TWI1) Control Register */
  #define REG_TWI1_MMR  (*(__IO uint32_t*)0xF8018004U) /**< \brief (TWI1) Master Mode Register */
  #define REG_TWI1_SMR  (*(__IO uint32_t*)0xF8018008U) /**< \brief (TWI1) Slave Mode Register */
  #define REG_TWI1_IADR (*(__IO uint32_t*)0xF801800CU) /**< \brief (TWI1) Internal Address Register */
  #define REG_TWI1_CWGR (*(__IO uint32_t*)0xF8018010U) /**< \brief (TWI1) Clock Waveform Generator Register */
  #define REG_TWI1_SR   (*(__I  uint32_t*)0xF8018020U) /**< \brief (TWI1) Status Register */
  #define REG_TWI1_IER  (*(__O  uint32_t*)0xF8018024U) /**< \brief (TWI1) Interrupt Enable Register */
  #define REG_TWI1_IDR  (*(__O  uint32_t*)0xF8018028U) /**< \brief (TWI1) Interrupt Disable Register */
  #define REG_TWI1_IMR  (*(__I  uint32_t*)0xF801802CU) /**< \brief (TWI1) Interrupt Mask Register */
  #define REG_TWI1_RHR  (*(__I  uint32_t*)0xF8018030U) /**< \brief (TWI1) Receive Holding Register */
  #define REG_TWI1_THR  (*(__O  uint32_t*)0xF8018034U) /**< \brief (TWI1) Transmit Holding Register */
  #define REG_TWI1_WPMR (*(__IO uint32_t*)0xF80180E4U) /**< \brief (TWI1) Protection Mode Register */
  #define REG_TWI1_WPSR (*(__I  uint32_t*)0xF80180E8U) /**< \brief (TWI1) Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for TWI2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_TWI2_CR                    (0xF8024000U) /**< \brief (TWI2) Control Register */
  #define REG_TWI2_MMR                   (0xF8024004U) /**< \brief (TWI2) Master Mode Register */
  #define REG_TWI2_SMR                   (0xF8024008U) /**< \brief (TWI2) Slave Mode Register */
  #define REG_TWI2_IADR                  (0xF802400CU) /**< \brief (TWI2) Internal Address Register */
  #define REG_TWI2_CWGR                  (0xF8024010U) /**< \brief (TWI2) Clock Waveform Generator Register */
  #define REG_TWI2_SR                    (0xF8024020U) /**< \brief (TWI2) Status Register */
  #define REG_TWI2_IER                   (0xF8024024U) /**< \brief (TWI2) Interrupt Enable Register */
  #define REG_TWI2_IDR                   (0xF8024028U) /**< \brief (TWI2) Interrupt Disable Register */
  #define REG_TWI2_IMR                   (0xF802402CU) /**< \brief (TWI2) Interrupt Mask Register */
  #define REG_TWI2_RHR                   (0xF8024030U) /**< \brief (TWI2) Receive Holding Register */
  #define REG_TWI2_THR                   (0xF8024034U) /**< \brief (TWI2) Transmit Holding Register */
  #define REG_TWI2_WPMR                  (0xF80240E4U) /**< \brief (TWI2) Protection Mode Register */
  #define REG_TWI2_WPSR                  (0xF80240E8U) /**< \brief (TWI2) Protection Status Register */
#else
  #define REG_TWI2_CR   (*(__O  uint32_t*)0xF8024000U) /**< \brief (TWI2) Control Register */
  #define REG_TWI2_MMR  (*(__IO uint32_t*)0xF8024004U) /**< \brief (TWI2) Master Mode Register */
  #define REG_TWI2_SMR  (*(__IO uint32_t*)0xF8024008U) /**< \brief (TWI2) Slave Mode Register */
  #define REG_TWI2_IADR (*(__IO uint32_t*)0xF802400CU) /**< \brief (TWI2) Internal Address Register */
  #define REG_TWI2_CWGR (*(__IO uint32_t*)0xF8024010U) /**< \brief (TWI2) Clock Waveform Generator Register */
  #define REG_TWI2_SR   (*(__I  uint32_t*)0xF8024020U) /**< \brief (TWI2) Status Register */
  #define REG_TWI2_IER  (*(__O  uint32_t*)0xF8024024U) /**< \brief (TWI2) Interrupt Enable Register */
  #define REG_TWI2_IDR  (*(__O  uint32_t*)0xF8024028U) /**< \brief (TWI2) Interrupt Disable Register */
  #define REG_TWI2_IMR  (*(__I  uint32_t*)0xF802402CU) /**< \brief (TWI2) Interrupt Mask Register */
  #define REG_TWI2_RHR  (*(__I  uint32_t*)0xF8024030U) /**< \brief (TWI2) Receive Holding Register */
  #define REG_TWI2_THR  (*(__O  uint32_t*)0xF8024034U) /**< \brief (TWI2) Transmit Holding Register */
  #define REG_TWI2_WPMR (*(__IO uint32_t*)0xF80240E4U) /**< \brief (TWI2) Protection Mode Register */
  #define REG_TWI2_WPSR (*(__I  uint32_t*)0xF80240E8U) /**< \brief (TWI2) Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for SFR peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SFR_OHCIICR                  (0xF8028010U) /**< \brief (SFR) OHCI Interrupt Configuration Register */
  #define REG_SFR_OHCIISR                  (0xF8028014U) /**< \brief (SFR) OHCI Interrupt Status Register */
  #define REG_SFR_SECURE                   (0xF8028028U) /**< \brief (SFR) Security Configuration Register */
  #define REG_SFR_EBICFG                   (0xF8028040U) /**< \brief (SFR) EBI Configuration Register */
  #define REG_SFR_SN0                      (0xF802804CU) /**< \brief (SFR) Serial Number 0 Register */
  #define REG_SFR_SN1                      (0xF8028050U) /**< \brief (SFR) Seriel Number 1 Register */
#else
  #define REG_SFR_OHCIICR (*(__IO uint32_t*)0xF8028010U) /**< \brief (SFR) OHCI Interrupt Configuration Register */
  #define REG_SFR_OHCIISR (*(__I  uint32_t*)0xF8028014U) /**< \brief (SFR) OHCI Interrupt Status Register */
  #define REG_SFR_SECURE  (*(__IO uint32_t*)0xF8028028U) /**< \brief (SFR) Security Configuration Register */
  #define REG_SFR_EBICFG  (*(__IO uint32_t*)0xF8028040U) /**< \brief (SFR) EBI Configuration Register */
  #define REG_SFR_SN0     (*(__I  uint32_t*)0xF802804CU) /**< \brief (SFR) Serial Number 0 Register */
  #define REG_SFR_SN1     (*(__I  uint32_t*)0xF8028050U) /**< \brief (SFR) Seriel Number 1 Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for USART0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_USART0_CR                    (0xF802C000U) /**< \brief (USART0) Control Register */
  #define REG_USART0_MR                    (0xF802C004U) /**< \brief (USART0) Mode Register */
  #define REG_USART0_IER                   (0xF802C008U) /**< \brief (USART0) Interrupt Enable Register */
  #define REG_USART0_IDR                   (0xF802C00CU) /**< \brief (USART0) Interrupt Disable Register */
  #define REG_USART0_IMR                   (0xF802C010U) /**< \brief (USART0) Interrupt Mask Register */
  #define REG_USART0_CSR                   (0xF802C014U) /**< \brief (USART0) Channel Status Register */
  #define REG_USART0_RHR                   (0xF802C018U) /**< \brief (USART0) Receiver Holding Register */
  #define REG_USART0_THR                   (0xF802C01CU) /**< \brief (USART0) Transmitter Holding Register */
  #define REG_USART0_BRGR                  (0xF802C020U) /**< \brief (USART0) Baud Rate Generator Register */
  #define REG_USART0_RTOR                  (0xF802C024U) /**< \brief (USART0) Receiver Time-out Register */
  #define REG_USART0_TTGR                  (0xF802C028U) /**< \brief (USART0) Transmitter Timeguard Register */
  #define REG_USART0_FIDI                  (0xF802C040U) /**< \brief (USART0) FI DI Ratio Register */
  #define REG_USART0_NER                   (0xF802C044U) /**< \brief (USART0) Number of Errors Register */
  #define REG_USART0_IF                    (0xF802C04CU) /**< \brief (USART0) IrDA Filter Register */
  #define REG_USART0_MAN                   (0xF802C050U) /**< \brief (USART0) Manchester Encoder Decoder Register */
  #define REG_USART0_WPMR                  (0xF802C0E4U) /**< \brief (USART0) Write Protect Mode Register */
  #define REG_USART0_WPSR                  (0xF802C0E8U) /**< \brief (USART0) Write Protect Status Register */
#else
  #define REG_USART0_CR   (*(__O  uint32_t*)0xF802C000U) /**< \brief (USART0) Control Register */
  #define REG_USART0_MR   (*(__IO uint32_t*)0xF802C004U) /**< \brief (USART0) Mode Register */
  #define REG_USART0_IER  (*(__O  uint32_t*)0xF802C008U) /**< \brief (USART0) Interrupt Enable Register */
  #define REG_USART0_IDR  (*(__O  uint32_t*)0xF802C00CU) /**< \brief (USART0) Interrupt Disable Register */
  #define REG_USART0_IMR  (*(__I  uint32_t*)0xF802C010U) /**< \brief (USART0) Interrupt Mask Register */
  #define REG_USART0_CSR  (*(__I  uint32_t*)0xF802C014U) /**< \brief (USART0) Channel Status Register */
  #define REG_USART0_RHR  (*(__I  uint32_t*)0xF802C018U) /**< \brief (USART0) Receiver Holding Register */
  #define REG_USART0_THR  (*(__O  uint32_t*)0xF802C01CU) /**< \brief (USART0) Transmitter Holding Register */
  #define REG_USART0_BRGR (*(__IO uint32_t*)0xF802C020U) /**< \brief (USART0) Baud Rate Generator Register */
  #define REG_USART0_RTOR (*(__IO uint32_t*)0xF802C024U) /**< \brief (USART0) Receiver Time-out Register */
  #define REG_USART0_TTGR (*(__IO uint32_t*)0xF802C028U) /**< \brief (USART0) Transmitter Timeguard Register */
  #define REG_USART0_FIDI (*(__IO uint32_t*)0xF802C040U) /**< \brief (USART0) FI DI Ratio Register */
  #define REG_USART0_NER  (*(__I  uint32_t*)0xF802C044U) /**< \brief (USART0) Number of Errors Register */
  #define REG_USART0_IF   (*(__IO uint32_t*)0xF802C04CU) /**< \brief (USART0) IrDA Filter Register */
  #define REG_USART0_MAN  (*(__IO uint32_t*)0xF802C050U) /**< \brief (USART0) Manchester Encoder Decoder Register */
  #define REG_USART0_WPMR (*(__IO uint32_t*)0xF802C0E4U) /**< \brief (USART0) Write Protect Mode Register */
  #define REG_USART0_WPSR (*(__I  uint32_t*)0xF802C0E8U) /**< \brief (USART0) Write Protect Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for USART1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_USART1_CR                    (0xF8030000U) /**< \brief (USART1) Control Register */
  #define REG_USART1_MR                    (0xF8030004U) /**< \brief (USART1) Mode Register */
  #define REG_USART1_IER                   (0xF8030008U) /**< \brief (USART1) Interrupt Enable Register */
  #define REG_USART1_IDR                   (0xF803000CU) /**< \brief (USART1) Interrupt Disable Register */
  #define REG_USART1_IMR                   (0xF8030010U) /**< \brief (USART1) Interrupt Mask Register */
  #define REG_USART1_CSR                   (0xF8030014U) /**< \brief (USART1) Channel Status Register */
  #define REG_USART1_RHR                   (0xF8030018U) /**< \brief (USART1) Receiver Holding Register */
  #define REG_USART1_THR                   (0xF803001CU) /**< \brief (USART1) Transmitter Holding Register */
  #define REG_USART1_BRGR                  (0xF8030020U) /**< \brief (USART1) Baud Rate Generator Register */
  #define REG_USART1_RTOR                  (0xF8030024U) /**< \brief (USART1) Receiver Time-out Register */
  #define REG_USART1_TTGR                  (0xF8030028U) /**< \brief (USART1) Transmitter Timeguard Register */
  #define REG_USART1_FIDI                  (0xF8030040U) /**< \brief (USART1) FI DI Ratio Register */
  #define REG_USART1_NER                   (0xF8030044U) /**< \brief (USART1) Number of Errors Register */
  #define REG_USART1_IF                    (0xF803004CU) /**< \brief (USART1) IrDA Filter Register */
  #define REG_USART1_MAN                   (0xF8030050U) /**< \brief (USART1) Manchester Encoder Decoder Register */
  #define REG_USART1_WPMR                  (0xF80300E4U) /**< \brief (USART1) Write Protect Mode Register */
  #define REG_USART1_WPSR                  (0xF80300E8U) /**< \brief (USART1) Write Protect Status Register */
#else
  #define REG_USART1_CR   (*(__O  uint32_t*)0xF8030000U) /**< \brief (USART1) Control Register */
  #define REG_USART1_MR   (*(__IO uint32_t*)0xF8030004U) /**< \brief (USART1) Mode Register */
  #define REG_USART1_IER  (*(__O  uint32_t*)0xF8030008U) /**< \brief (USART1) Interrupt Enable Register */
  #define REG_USART1_IDR  (*(__O  uint32_t*)0xF803000CU) /**< \brief (USART1) Interrupt Disable Register */
  #define REG_USART1_IMR  (*(__I  uint32_t*)0xF8030010U) /**< \brief (USART1) Interrupt Mask Register */
  #define REG_USART1_CSR  (*(__I  uint32_t*)0xF8030014U) /**< \brief (USART1) Channel Status Register */
  #define REG_USART1_RHR  (*(__I  uint32_t*)0xF8030018U) /**< \brief (USART1) Receiver Holding Register */
  #define REG_USART1_THR  (*(__O  uint32_t*)0xF803001CU) /**< \brief (USART1) Transmitter Holding Register */
  #define REG_USART1_BRGR (*(__IO uint32_t*)0xF8030020U) /**< \brief (USART1) Baud Rate Generator Register */
  #define REG_USART1_RTOR (*(__IO uint32_t*)0xF8030024U) /**< \brief (USART1) Receiver Time-out Register */
  #define REG_USART1_TTGR (*(__IO uint32_t*)0xF8030028U) /**< \brief (USART1) Transmitter Timeguard Register */
  #define REG_USART1_FIDI (*(__IO uint32_t*)0xF8030040U) /**< \brief (USART1) FI DI Ratio Register */
  #define REG_USART1_NER  (*(__I  uint32_t*)0xF8030044U) /**< \brief (USART1) Number of Errors Register */
  #define REG_USART1_IF   (*(__IO uint32_t*)0xF803004CU) /**< \brief (USART1) IrDA Filter Register */
  #define REG_USART1_MAN  (*(__IO uint32_t*)0xF8030050U) /**< \brief (USART1) Manchester Encoder Decoder Register */
  #define REG_USART1_WPMR (*(__IO uint32_t*)0xF80300E4U) /**< \brief (USART1) Write Protect Mode Register */
  #define REG_USART1_WPSR (*(__I  uint32_t*)0xF80300E8U) /**< \brief (USART1) Write Protect Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for HSMCI1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_HSMCI1_CR                     (0xFC000000U) /**< \brief (HSMCI1) Control Register */
  #define REG_HSMCI1_MR                     (0xFC000004U) /**< \brief (HSMCI1) Mode Register */
  #define REG_HSMCI1_DTOR                   (0xFC000008U) /**< \brief (HSMCI1) Data Timeout Register */
  #define REG_HSMCI1_SDCR                   (0xFC00000CU) /**< \brief (HSMCI1) SD/SDIO Card Register */
  #define REG_HSMCI1_ARGR                   (0xFC000010U) /**< \brief (HSMCI1) Argument Register */
  #define REG_HSMCI1_CMDR                   (0xFC000014U) /**< \brief (HSMCI1) Command Register */
  #define REG_HSMCI1_BLKR                   (0xFC000018U) /**< \brief (HSMCI1) Block Register */
  #define REG_HSMCI1_CSTOR                  (0xFC00001CU) /**< \brief (HSMCI1) Completion Signal Timeout Register */
  #define REG_HSMCI1_RSPR                   (0xFC000020U) /**< \brief (HSMCI1) Response Register */
  #define REG_HSMCI1_RDR                    (0xFC000030U) /**< \brief (HSMCI1) Receive Data Register */
  #define REG_HSMCI1_TDR                    (0xFC000034U) /**< \brief (HSMCI1) Transmit Data Register */
  #define REG_HSMCI1_SR                     (0xFC000040U) /**< \brief (HSMCI1) Status Register */
  #define REG_HSMCI1_IER                    (0xFC000044U) /**< \brief (HSMCI1) Interrupt Enable Register */
  #define REG_HSMCI1_IDR                    (0xFC000048U) /**< \brief (HSMCI1) Interrupt Disable Register */
  #define REG_HSMCI1_IMR                    (0xFC00004CU) /**< \brief (HSMCI1) Interrupt Mask Register */
  #define REG_HSMCI1_DMA                    (0xFC000050U) /**< \brief (HSMCI1) DMA Configuration Register */
  #define REG_HSMCI1_CFG                    (0xFC000054U) /**< \brief (HSMCI1) Configuration Register */
  #define REG_HSMCI1_WPMR                   (0xFC0000E4U) /**< \brief (HSMCI1) Write Protection Mode Register */
  #define REG_HSMCI1_WPSR                   (0xFC0000E8U) /**< \brief (HSMCI1) Write Protection Status Register */
  #define REG_HSMCI1_FIFO                   (0xFC000200U) /**< \brief (HSMCI1) FIFO Memory Aperture0 */
#else
  #define REG_HSMCI1_CR    (*(__O  uint32_t*)0xFC000000U) /**< \brief (HSMCI1) Control Register */
  #define REG_HSMCI1_MR    (*(__IO uint32_t*)0xFC000004U) /**< \brief (HSMCI1) Mode Register */
  #define REG_HSMCI1_DTOR  (*(__IO uint32_t*)0xFC000008U) /**< \brief (HSMCI1) Data Timeout Register */
  #define REG_HSMCI1_SDCR  (*(__IO uint32_t*)0xFC00000CU) /**< \brief (HSMCI1) SD/SDIO Card Register */
  #define REG_HSMCI1_ARGR  (*(__IO uint32_t*)0xFC000010U) /**< \brief (HSMCI1) Argument Register */
  #define REG_HSMCI1_CMDR  (*(__O  uint32_t*)0xFC000014U) /**< \brief (HSMCI1) Command Register */
  #define REG_HSMCI1_BLKR  (*(__IO uint32_t*)0xFC000018U) /**< \brief (HSMCI1) Block Register */
  #define REG_HSMCI1_CSTOR (*(__IO uint32_t*)0xFC00001CU) /**< \brief (HSMCI1) Completion Signal Timeout Register */
  #define REG_HSMCI1_RSPR  (*(__I  uint32_t*)0xFC000020U) /**< \brief (HSMCI1) Response Register */
  #define REG_HSMCI1_RDR   (*(__I  uint32_t*)0xFC000030U) /**< \brief (HSMCI1) Receive Data Register */
  #define REG_HSMCI1_TDR   (*(__O  uint32_t*)0xFC000034U) /**< \brief (HSMCI1) Transmit Data Register */
  #define REG_HSMCI1_SR    (*(__I  uint32_t*)0xFC000040U) /**< \brief (HSMCI1) Status Register */
  #define REG_HSMCI1_IER   (*(__O  uint32_t*)0xFC000044U) /**< \brief (HSMCI1) Interrupt Enable Register */
  #define REG_HSMCI1_IDR   (*(__O  uint32_t*)0xFC000048U) /**< \brief (HSMCI1) Interrupt Disable Register */
  #define REG_HSMCI1_IMR   (*(__I  uint32_t*)0xFC00004CU) /**< \brief (HSMCI1) Interrupt Mask Register */
  #define REG_HSMCI1_DMA   (*(__IO uint32_t*)0xFC000050U) /**< \brief (HSMCI1) DMA Configuration Register */
  #define REG_HSMCI1_CFG   (*(__IO uint32_t*)0xFC000054U) /**< \brief (HSMCI1) Configuration Register */
  #define REG_HSMCI1_WPMR  (*(__IO uint32_t*)0xFC0000E4U) /**< \brief (HSMCI1) Write Protection Mode Register */
  #define REG_HSMCI1_WPSR  (*(__I  uint32_t*)0xFC0000E8U) /**< \brief (HSMCI1) Write Protection Status Register */
  #define REG_HSMCI1_FIFO  (*(__IO uint32_t*)0xFC000200U) /**< \brief (HSMCI1) FIFO Memory Aperture0 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for UART1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_UART1_CR                    (0xFC004000U) /**< \brief (UART1) Control Register */
  #define REG_UART1_MR                    (0xFC004004U) /**< \brief (UART1) Mode Register */
  #define REG_UART1_IER                   (0xFC004008U) /**< \brief (UART1) Interrupt Enable Register */
  #define REG_UART1_IDR                   (0xFC00400CU) /**< \brief (UART1) Interrupt Disable Register */
  #define REG_UART1_IMR                   (0xFC004010U) /**< \brief (UART1) Interrupt Mask Register */
  #define REG_UART1_SR                    (0xFC004014U) /**< \brief (UART1) Status Register */
  #define REG_UART1_RHR                   (0xFC004018U) /**< \brief (UART1) Receive Holding Register */
  #define REG_UART1_THR                   (0xFC00401CU) /**< \brief (UART1) Transmit Holding Register */
  #define REG_UART1_BRGR                  (0xFC004020U) /**< \brief (UART1) Baud Rate Generator Register */
#else
  #define REG_UART1_CR   (*(__O  uint32_t*)0xFC004000U) /**< \brief (UART1) Control Register */
  #define REG_UART1_MR   (*(__IO uint32_t*)0xFC004004U) /**< \brief (UART1) Mode Register */
  #define REG_UART1_IER  (*(__O  uint32_t*)0xFC004008U) /**< \brief (UART1) Interrupt Enable Register */
  #define REG_UART1_IDR  (*(__O  uint32_t*)0xFC00400CU) /**< \brief (UART1) Interrupt Disable Register */
  #define REG_UART1_IMR  (*(__I  uint32_t*)0xFC004010U) /**< \brief (UART1) Interrupt Mask Register */
  #define REG_UART1_SR   (*(__I  uint32_t*)0xFC004014U) /**< \brief (UART1) Status Register */
  #define REG_UART1_RHR  (*(__I  uint32_t*)0xFC004018U) /**< \brief (UART1) Receive Holding Register */
  #define REG_UART1_THR  (*(__O  uint32_t*)0xFC00401CU) /**< \brief (UART1) Transmit Holding Register */
  #define REG_UART1_BRGR (*(__IO uint32_t*)0xFC004020U) /**< \brief (UART1) Baud Rate Generator Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for USART2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_USART2_CR                    (0xFC008000U) /**< \brief (USART2) Control Register */
  #define REG_USART2_MR                    (0xFC008004U) /**< \brief (USART2) Mode Register */
  #define REG_USART2_IER                   (0xFC008008U) /**< \brief (USART2) Interrupt Enable Register */
  #define REG_USART2_IDR                   (0xFC00800CU) /**< \brief (USART2) Interrupt Disable Register */
  #define REG_USART2_IMR                   (0xFC008010U) /**< \brief (USART2) Interrupt Mask Register */
  #define REG_USART2_CSR                   (0xFC008014U) /**< \brief (USART2) Channel Status Register */
  #define REG_USART2_RHR                   (0xFC008018U) /**< \brief (USART2) Receiver Holding Register */
  #define REG_USART2_THR                   (0xFC00801CU) /**< \brief (USART2) Transmitter Holding Register */
  #define REG_USART2_BRGR                  (0xFC008020U) /**< \brief (USART2) Baud Rate Generator Register */
  #define REG_USART2_RTOR                  (0xFC008024U) /**< \brief (USART2) Receiver Time-out Register */
  #define REG_USART2_TTGR                  (0xFC008028U) /**< \brief (USART2) Transmitter Timeguard Register */
  #define REG_USART2_FIDI                  (0xFC008040U) /**< \brief (USART2) FI DI Ratio Register */
  #define REG_USART2_NER                   (0xFC008044U) /**< \brief (USART2) Number of Errors Register */
  #define REG_USART2_IF                    (0xFC00804CU) /**< \brief (USART2) IrDA Filter Register */
  #define REG_USART2_MAN                   (0xFC008050U) /**< \brief (USART2) Manchester Encoder Decoder Register */
  #define REG_USART2_WPMR                  (0xFC0080E4U) /**< \brief (USART2) Write Protect Mode Register */
  #define REG_USART2_WPSR                  (0xFC0080E8U) /**< \brief (USART2) Write Protect Status Register */
#else
  #define REG_USART2_CR   (*(__O  uint32_t*)0xFC008000U) /**< \brief (USART2) Control Register */
  #define REG_USART2_MR   (*(__IO uint32_t*)0xFC008004U) /**< \brief (USART2) Mode Register */
  #define REG_USART2_IER  (*(__O  uint32_t*)0xFC008008U) /**< \brief (USART2) Interrupt Enable Register */
  #define REG_USART2_IDR  (*(__O  uint32_t*)0xFC00800CU) /**< \brief (USART2) Interrupt Disable Register */
  #define REG_USART2_IMR  (*(__I  uint32_t*)0xFC008010U) /**< \brief (USART2) Interrupt Mask Register */
  #define REG_USART2_CSR  (*(__I  uint32_t*)0xFC008014U) /**< \brief (USART2) Channel Status Register */
  #define REG_USART2_RHR  (*(__I  uint32_t*)0xFC008018U) /**< \brief (USART2) Receiver Holding Register */
  #define REG_USART2_THR  (*(__O  uint32_t*)0xFC00801CU) /**< \brief (USART2) Transmitter Holding Register */
  #define REG_USART2_BRGR (*(__IO uint32_t*)0xFC008020U) /**< \brief (USART2) Baud Rate Generator Register */
  #define REG_USART2_RTOR (*(__IO uint32_t*)0xFC008024U) /**< \brief (USART2) Receiver Time-out Register */
  #define REG_USART2_TTGR (*(__IO uint32_t*)0xFC008028U) /**< \brief (USART2) Transmitter Timeguard Register */
  #define REG_USART2_FIDI (*(__IO uint32_t*)0xFC008040U) /**< \brief (USART2) FI DI Ratio Register */
  #define REG_USART2_NER  (*(__I  uint32_t*)0xFC008044U) /**< \brief (USART2) Number of Errors Register */
  #define REG_USART2_IF   (*(__IO uint32_t*)0xFC00804CU) /**< \brief (USART2) IrDA Filter Register */
  #define REG_USART2_MAN  (*(__IO uint32_t*)0xFC008050U) /**< \brief (USART2) Manchester Encoder Decoder Register */
  #define REG_USART2_WPMR (*(__IO uint32_t*)0xFC0080E4U) /**< \brief (USART2) Write Protect Mode Register */
  #define REG_USART2_WPSR (*(__I  uint32_t*)0xFC0080E8U) /**< \brief (USART2) Write Protect Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for USART3 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_USART3_CR                    (0xFC00C000U) /**< \brief (USART3) Control Register */
  #define REG_USART3_MR                    (0xFC00C004U) /**< \brief (USART3) Mode Register */
  #define REG_USART3_IER                   (0xFC00C008U) /**< \brief (USART3) Interrupt Enable Register */
  #define REG_USART3_IDR                   (0xFC00C00CU) /**< \brief (USART3) Interrupt Disable Register */
  #define REG_USART3_IMR                   (0xFC00C010U) /**< \brief (USART3) Interrupt Mask Register */
  #define REG_USART3_CSR                   (0xFC00C014U) /**< \brief (USART3) Channel Status Register */
  #define REG_USART3_RHR                   (0xFC00C018U) /**< \brief (USART3) Receiver Holding Register */
  #define REG_USART3_THR                   (0xFC00C01CU) /**< \brief (USART3) Transmitter Holding Register */
  #define REG_USART3_BRGR                  (0xFC00C020U) /**< \brief (USART3) Baud Rate Generator Register */
  #define REG_USART3_RTOR                  (0xFC00C024U) /**< \brief (USART3) Receiver Time-out Register */
  #define REG_USART3_TTGR                  (0xFC00C028U) /**< \brief (USART3) Transmitter Timeguard Register */
  #define REG_USART3_FIDI                  (0xFC00C040U) /**< \brief (USART3) FI DI Ratio Register */
  #define REG_USART3_NER                   (0xFC00C044U) /**< \brief (USART3) Number of Errors Register */
  #define REG_USART3_IF                    (0xFC00C04CU) /**< \brief (USART3) IrDA Filter Register */
  #define REG_USART3_MAN                   (0xFC00C050U) /**< \brief (USART3) Manchester Encoder Decoder Register */
  #define REG_USART3_WPMR                  (0xFC00C0E4U) /**< \brief (USART3) Write Protect Mode Register */
  #define REG_USART3_WPSR                  (0xFC00C0E8U) /**< \brief (USART3) Write Protect Status Register */
#else
  #define REG_USART3_CR   (*(__O  uint32_t*)0xFC00C000U) /**< \brief (USART3) Control Register */
  #define REG_USART3_MR   (*(__IO uint32_t*)0xFC00C004U) /**< \brief (USART3) Mode Register */
  #define REG_USART3_IER  (*(__O  uint32_t*)0xFC00C008U) /**< \brief (USART3) Interrupt Enable Register */
  #define REG_USART3_IDR  (*(__O  uint32_t*)0xFC00C00CU) /**< \brief (USART3) Interrupt Disable Register */
  #define REG_USART3_IMR  (*(__I  uint32_t*)0xFC00C010U) /**< \brief (USART3) Interrupt Mask Register */
  #define REG_USART3_CSR  (*(__I  uint32_t*)0xFC00C014U) /**< \brief (USART3) Channel Status Register */
  #define REG_USART3_RHR  (*(__I  uint32_t*)0xFC00C018U) /**< \brief (USART3) Receiver Holding Register */
  #define REG_USART3_THR  (*(__O  uint32_t*)0xFC00C01CU) /**< \brief (USART3) Transmitter Holding Register */
  #define REG_USART3_BRGR (*(__IO uint32_t*)0xFC00C020U) /**< \brief (USART3) Baud Rate Generator Register */
  #define REG_USART3_RTOR (*(__IO uint32_t*)0xFC00C024U) /**< \brief (USART3) Receiver Time-out Register */
  #define REG_USART3_TTGR (*(__IO uint32_t*)0xFC00C028U) /**< \brief (USART3) Transmitter Timeguard Register */
  #define REG_USART3_FIDI (*(__IO uint32_t*)0xFC00C040U) /**< \brief (USART3) FI DI Ratio Register */
  #define REG_USART3_NER  (*(__I  uint32_t*)0xFC00C044U) /**< \brief (USART3) Number of Errors Register */
  #define REG_USART3_IF   (*(__IO uint32_t*)0xFC00C04CU) /**< \brief (USART3) IrDA Filter Register */
  #define REG_USART3_MAN  (*(__IO uint32_t*)0xFC00C050U) /**< \brief (USART3) Manchester Encoder Decoder Register */
  #define REG_USART3_WPMR (*(__IO uint32_t*)0xFC00C0E4U) /**< \brief (USART3) Write Protect Mode Register */
  #define REG_USART3_WPSR (*(__I  uint32_t*)0xFC00C0E8U) /**< \brief (USART3) Write Protect Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for USART4 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_USART4_CR                    (0xFC010000U) /**< \brief (USART4) Control Register */
  #define REG_USART4_MR                    (0xFC010004U) /**< \brief (USART4) Mode Register */
  #define REG_USART4_IER                   (0xFC010008U) /**< \brief (USART4) Interrupt Enable Register */
  #define REG_USART4_IDR                   (0xFC01000CU) /**< \brief (USART4) Interrupt Disable Register */
  #define REG_USART4_IMR                   (0xFC010010U) /**< \brief (USART4) Interrupt Mask Register */
  #define REG_USART4_CSR                   (0xFC010014U) /**< \brief (USART4) Channel Status Register */
  #define REG_USART4_RHR                   (0xFC010018U) /**< \brief (USART4) Receiver Holding Register */
  #define REG_USART4_THR                   (0xFC01001CU) /**< \brief (USART4) Transmitter Holding Register */
  #define REG_USART4_BRGR                  (0xFC010020U) /**< \brief (USART4) Baud Rate Generator Register */
  #define REG_USART4_RTOR                  (0xFC010024U) /**< \brief (USART4) Receiver Time-out Register */
  #define REG_USART4_TTGR                  (0xFC010028U) /**< \brief (USART4) Transmitter Timeguard Register */
  #define REG_USART4_FIDI                  (0xFC010040U) /**< \brief (USART4) FI DI Ratio Register */
  #define REG_USART4_NER                   (0xFC010044U) /**< \brief (USART4) Number of Errors Register */
  #define REG_USART4_IF                    (0xFC01004CU) /**< \brief (USART4) IrDA Filter Register */
  #define REG_USART4_MAN                   (0xFC010050U) /**< \brief (USART4) Manchester Encoder Decoder Register */
  #define REG_USART4_WPMR                  (0xFC0100E4U) /**< \brief (USART4) Write Protect Mode Register */
  #define REG_USART4_WPSR                  (0xFC0100E8U) /**< \brief (USART4) Write Protect Status Register */
#else
  #define REG_USART4_CR   (*(__O  uint32_t*)0xFC010000U) /**< \brief (USART4) Control Register */
  #define REG_USART4_MR   (*(__IO uint32_t*)0xFC010004U) /**< \brief (USART4) Mode Register */
  #define REG_USART4_IER  (*(__O  uint32_t*)0xFC010008U) /**< \brief (USART4) Interrupt Enable Register */
  #define REG_USART4_IDR  (*(__O  uint32_t*)0xFC01000CU) /**< \brief (USART4) Interrupt Disable Register */
  #define REG_USART4_IMR  (*(__I  uint32_t*)0xFC010010U) /**< \brief (USART4) Interrupt Mask Register */
  #define REG_USART4_CSR  (*(__I  uint32_t*)0xFC010014U) /**< \brief (USART4) Channel Status Register */
  #define REG_USART4_RHR  (*(__I  uint32_t*)0xFC010018U) /**< \brief (USART4) Receiver Holding Register */
  #define REG_USART4_THR  (*(__O  uint32_t*)0xFC01001CU) /**< \brief (USART4) Transmitter Holding Register */
  #define REG_USART4_BRGR (*(__IO uint32_t*)0xFC010020U) /**< \brief (USART4) Baud Rate Generator Register */
  #define REG_USART4_RTOR (*(__IO uint32_t*)0xFC010024U) /**< \brief (USART4) Receiver Time-out Register */
  #define REG_USART4_TTGR (*(__IO uint32_t*)0xFC010028U) /**< \brief (USART4) Transmitter Timeguard Register */
  #define REG_USART4_FIDI (*(__IO uint32_t*)0xFC010040U) /**< \brief (USART4) FI DI Ratio Register */
  #define REG_USART4_NER  (*(__I  uint32_t*)0xFC010044U) /**< \brief (USART4) Number of Errors Register */
  #define REG_USART4_IF   (*(__IO uint32_t*)0xFC01004CU) /**< \brief (USART4) IrDA Filter Register */
  #define REG_USART4_MAN  (*(__IO uint32_t*)0xFC010050U) /**< \brief (USART4) Manchester Encoder Decoder Register */
  #define REG_USART4_WPMR (*(__IO uint32_t*)0xFC0100E4U) /**< \brief (USART4) Write Protect Mode Register */
  #define REG_USART4_WPSR (*(__I  uint32_t*)0xFC0100E8U) /**< \brief (USART4) Write Protect Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Register definition for SPI1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SPI1_CR                    (0xFC018000U) /**< \brief (SPI1) Control Register */
  #define REG_SPI1_MR                    (0xFC018004U) /**< \brief (SPI1) Mode Register */
  #define REG_SPI1_RDR                   (0xFC018008U) /**< \brief (SPI1) Receive Data Register */
  #define REG_SPI1_TDR                   (0xFC01800CU) /**< \brief (SPI1) Transmit Data Register */
  #define REG_SPI1_SR                    (0xFC018010U) /**< \brief (SPI1) Status Register */
  #define REG_SPI1_IER                   (0xFC018014U) /**< \brief (SPI1) Interrupt Enable Register */
  #define REG_SPI1_IDR                   (0xFC018018U) /**< \brief (SPI1) Interrupt Disable Register */
  #define REG_SPI1_IMR                   (0xFC01801CU) /**< \brief (SPI1) Interrupt Mask Register */
  #define REG_SPI1_CSR                   (0xFC018030U) /**< \brief (SPI1) Chip Select Register */
  #define REG_SPI1_WPMR                  (0xFC0180E4U) /**< \brief (SPI1) Write Protection Control Register */
  #define REG_SPI1_WPSR                  (0xFC0180E8U) /**< \brief (SPI1) Write Protection Status Register */
#else
  #define REG_SPI1_CR   (*(__O  uint32_t*)0xFC018000U) /**< \brief (SPI1) Control Register */
  #define REG_SPI1_MR   (*(__IO uint32_t*)0xFC018004U) /**< \brief (SPI1) Mode Register */
  #define REG_SPI1_RDR  (*(__I  uint32_t*)0xFC018008U) /**< \brief (SPI1) Receive Data Register */
  #define REG_SPI1_TDR  (*(__O  uint32_t*)0xFC01800CU) /**< \brief (SPI1) Transmit Data Register */
  #define REG_SPI1_SR   (*(__I  uint32_t*)0xFC018010U) /**< \brief (SPI1) Status Register */
  #define REG_SPI1_IER  (*(__O  uint32_t*)0xFC018014U) /**< \brief (SPI1) Interrupt Enable Register */
  #define REG_SPI1_IDR  (*(__O  uint32_t*)0xFC018018U) /**< \brief (SPI1) Interrupt Disable Register */
  #define REG_SPI1_IMR  (*(__I  uint32_t*)0xFC01801CU) /**< \brief (SPI1) Interrupt Mask Register */
  #define REG_SPI1_CSR  (*(__IO uint32_t*)0xFC018030U) /**< \brief (SPI1) Chip Select Register */
  #define REG_SPI1_WPMR (*(__IO uint32_t*)0xFC0180E4U) /**< \brief (SPI1) Write Protection Control Register */
  #define REG_SPI1_WPSR (*(__I  uint32_t*)0xFC0180E8U) /**< \brief (SPI1) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for SPI2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SPI2_CR                    (0xFC01C000U) /**< \brief (SPI2) Control Register */
  #define REG_SPI2_MR                    (0xFC01C004U) /**< \brief (SPI2) Mode Register */
  #define REG_SPI2_RDR                   (0xFC01C008U) /**< \brief (SPI2) Receive Data Register */
  #define REG_SPI2_TDR                   (0xFC01C00CU) /**< \brief (SPI2) Transmit Data Register */
  #define REG_SPI2_SR                    (0xFC01C010U) /**< \brief (SPI2) Status Register */
  #define REG_SPI2_IER                   (0xFC01C014U) /**< \brief (SPI2) Interrupt Enable Register */
  #define REG_SPI2_IDR                   (0xFC01C018U) /**< \brief (SPI2) Interrupt Disable Register */
  #define REG_SPI2_IMR                   (0xFC01C01CU) /**< \brief (SPI2) Interrupt Mask Register */
  #define REG_SPI2_CSR                   (0xFC01C030U) /**< \brief (SPI2) Chip Select Register */
  #define REG_SPI2_WPMR                  (0xFC01C0E4U) /**< \brief (SPI2) Write Protection Control Register */
  #define REG_SPI2_WPSR                  (0xFC01C0E8U) /**< \brief (SPI2) Write Protection Status Register */
#else
  #define REG_SPI2_CR   (*(__O  uint32_t*)0xFC01C000U) /**< \brief (SPI2) Control Register */
  #define REG_SPI2_MR   (*(__IO uint32_t*)0xFC01C004U) /**< \brief (SPI2) Mode Register */
  #define REG_SPI2_RDR  (*(__I  uint32_t*)0xFC01C008U) /**< \brief (SPI2) Receive Data Register */
  #define REG_SPI2_TDR  (*(__O  uint32_t*)0xFC01C00CU) /**< \brief (SPI2) Transmit Data Register */
  #define REG_SPI2_SR   (*(__I  uint32_t*)0xFC01C010U) /**< \brief (SPI2) Status Register */
  #define REG_SPI2_IER  (*(__O  uint32_t*)0xFC01C014U) /**< \brief (SPI2) Interrupt Enable Register */
  #define REG_SPI2_IDR  (*(__O  uint32_t*)0xFC01C018U) /**< \brief (SPI2) Interrupt Disable Register */
  #define REG_SPI2_IMR  (*(__I  uint32_t*)0xFC01C01CU) /**< \brief (SPI2) Interrupt Mask Register */
  #define REG_SPI2_CSR  (*(__IO uint32_t*)0xFC01C030U) /**< \brief (SPI2) Chip Select Register */
  #define REG_SPI2_WPMR (*(__IO uint32_t*)0xFC01C0E4U) /**< \brief (SPI2) Write Protection Control Register */
  #define REG_SPI2_WPSR (*(__I  uint32_t*)0xFC01C0E8U) /**< \brief (SPI2) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Register definition for TWI3 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_TWI3_CR                    (0xFC038000U) /**< \brief (TWI3) Control Register */
  #define REG_TWI3_MMR                   (0xFC038004U) /**< \brief (TWI3) Master Mode Register */
  #define REG_TWI3_SMR                   (0xFC038008U) /**< \brief (TWI3) Slave Mode Register */
  #define REG_TWI3_IADR                  (0xFC03800CU) /**< \brief (TWI3) Internal Address Register */
  #define REG_TWI3_CWGR                  (0xFC038010U) /**< \brief (TWI3) Clock Waveform Generator Register */
  #define REG_TWI3_SR                    (0xFC038020U) /**< \brief (TWI3) Status Register */
  #define REG_TWI3_IER                   (0xFC038024U) /**< \brief (TWI3) Interrupt Enable Register */
  #define REG_TWI3_IDR                   (0xFC038028U) /**< \brief (TWI3) Interrupt Disable Register */
  #define REG_TWI3_IMR                   (0xFC03802CU) /**< \brief (TWI3) Interrupt Mask Register */
  #define REG_TWI3_RHR                   (0xFC038030U) /**< \brief (TWI3) Receive Holding Register */
  #define REG_TWI3_THR                   (0xFC038034U) /**< \brief (TWI3) Transmit Holding Register */
  #define REG_TWI3_WPMR                  (0xFC0380E4U) /**< \brief (TWI3) Protection Mode Register */
  #define REG_TWI3_WPSR                  (0xFC0380E8U) /**< \brief (TWI3) Protection Status Register */
#else
  #define REG_TWI3_CR   (*(__O  uint32_t*)0xFC038000U) /**< \brief (TWI3) Control Register */
  #define REG_TWI3_MMR  (*(__IO uint32_t*)0xFC038004U) /**< \brief (TWI3) Master Mode Register */
  #define REG_TWI3_SMR  (*(__IO uint32_t*)0xFC038008U) /**< \brief (TWI3) Slave Mode Register */
  #define REG_TWI3_IADR (*(__IO uint32_t*)0xFC03800CU) /**< \brief (TWI3) Internal Address Register */
  #define REG_TWI3_CWGR (*(__IO uint32_t*)0xFC038010U) /**< \brief (TWI3) Clock Waveform Generator Register */
  #define REG_TWI3_SR   (*(__I  uint32_t*)0xFC038020U) /**< \brief (TWI3) Status Register */
  #define REG_TWI3_IER  (*(__O  uint32_t*)0xFC038024U) /**< \brief (TWI3) Interrupt Enable Register */
  #define REG_TWI3_IDR  (*(__O  uint32_t*)0xFC038028U) /**< \brief (TWI3) Interrupt Disable Register */
  #define REG_TWI3_IMR  (*(__I  uint32_t*)0xFC03802CU) /**< \brief (TWI3) Interrupt Mask Register */
  #define REG_TWI3_RHR  (*(__I  uint32_t*)0xFC038030U) /**< \brief (TWI3) Receive Holding Register */
  #define REG_TWI3_THR  (*(__O  uint32_t*)0xFC038034U) /**< \brief (TWI3) Transmit Holding Register */
  #define REG_TWI3_WPMR (*(__IO uint32_t*)0xFC0380E4U) /**< \brief (TWI3) Protection Mode Register */
  #define REG_TWI3_WPSR (*(__I  uint32_t*)0xFC0380E8U) /**< \brief (TWI3) Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for MATRIX1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_MATRIX1_MCFG                    (0xFC054000U) /**< \brief (MATRIX1) Master Configuration Register */
  #define REG_MATRIX1_SCFG                    (0xFC054040U) /**< \brief (MATRIX1) Slave Configuration Register */
  #define REG_MATRIX1_PRAS0                   (0xFC054080U) /**< \brief (MATRIX1) Priority Register A for Slave 0 */
  #define REG_MATRIX1_PRBS0                   (0xFC054084U) /**< \brief (MATRIX1) Priority Register B for Slave 0 */
  #define REG_MATRIX1_PRAS1                   (0xFC054088U) /**< \brief (MATRIX1) Priority Register A for Slave 1 */
  #define REG_MATRIX1_PRBS1                   (0xFC05408CU) /**< \brief (MATRIX1) Priority Register B for Slave 1 */
  #define REG_MATRIX1_PRAS2                   (0xFC054090U) /**< \brief (MATRIX1) Priority Register A for Slave 2 */
  #define REG_MATRIX1_PRBS2                   (0xFC054094U) /**< \brief (MATRIX1) Priority Register B for Slave 2 */
  #define REG_MATRIX1_PRAS3                   (0xFC054098U) /**< \brief (MATRIX1) Priority Register A for Slave 3 */
  #define REG_MATRIX1_PRBS3                   (0xFC05409CU) /**< \brief (MATRIX1) Priority Register B for Slave 3 */
  #define REG_MATRIX1_PRAS4                   (0xFC0540A0U) /**< \brief (MATRIX1) Priority Register A for Slave 4 */
  #define REG_MATRIX1_PRBS4                   (0xFC0540A4U) /**< \brief (MATRIX1) Priority Register B for Slave 4 */
  #define REG_MATRIX1_PRAS5                   (0xFC0540A8U) /**< \brief (MATRIX1) Priority Register A for Slave 5 */
  #define REG_MATRIX1_PRBS5                   (0xFC0540ACU) /**< \brief (MATRIX1) Priority Register B for Slave 5 */
  #define REG_MATRIX1_PRAS6                   (0xFC0540B0U) /**< \brief (MATRIX1) Priority Register A for Slave 6 */
  #define REG_MATRIX1_PRBS6                   (0xFC0540B4U) /**< \brief (MATRIX1) Priority Register B for Slave 6 */
  #define REG_MATRIX1_PRAS7                   (0xFC0540B8U) /**< \brief (MATRIX1) Priority Register A for Slave 7 */
  #define REG_MATRIX1_PRBS7                   (0xFC0540BCU) /**< \brief (MATRIX1) Priority Register B for Slave 7 */
  #define REG_MATRIX1_PRAS8                   (0xFC0540C0U) /**< \brief (MATRIX1) Priority Register A for Slave 8 */
  #define REG_MATRIX1_PRBS8                   (0xFC0540C4U) /**< \brief (MATRIX1) Priority Register B for Slave 8 */
  #define REG_MATRIX1_PRAS9                   (0xFC0540C8U) /**< \brief (MATRIX1) Priority Register A for Slave 9 */
  #define REG_MATRIX1_PRBS9                   (0xFC0540CCU) /**< \brief (MATRIX1) Priority Register B for Slave 9 */
  #define REG_MATRIX1_PRAS10                  (0xFC0540D0U) /**< \brief (MATRIX1) Priority Register A for Slave 10 */
  #define REG_MATRIX1_PRBS10                  (0xFC0540D4U) /**< \brief (MATRIX1) Priority Register B for Slave 10 */
  #define REG_MATRIX1_PRAS11                  (0xFC0540D8U) /**< \brief (MATRIX1) Priority Register A for Slave 11 */
  #define REG_MATRIX1_PRBS11                  (0xFC0540DCU) /**< \brief (MATRIX1) Priority Register B for Slave 11 */
  #define REG_MATRIX1_PRAS12                  (0xFC0540E0U) /**< \brief (MATRIX1) Priority Register A for Slave 12 */
  #define REG_MATRIX1_PRBS12                  (0xFC0540E4U) /**< \brief (MATRIX1) Priority Register B for Slave 12 */
  #define REG_MATRIX1_MEIER                   (0xFC054150U) /**< \brief (MATRIX1) Master Error Interrupt Enable Register */
  #define REG_MATRIX1_MEIDR                   (0xFC054154U) /**< \brief (MATRIX1) Master Error Interrupt Disable Register */
  #define REG_MATRIX1_MEIMR                   (0xFC054158U) /**< \brief (MATRIX1) Master Error Interrupt Mask Register */
  #define REG_MATRIX1_MESR                    (0xFC05415CU) /**< \brief (MATRIX1) Master Error Status Register */
  #define REG_MATRIX1_MEAR                    (0xFC054160U) /**< \brief (MATRIX1) Master 0 Error Address Register */
  #define REG_MATRIX1_WPMR                    (0xFC0541E4U) /**< \brief (MATRIX1) Write Protect Mode Register */
  #define REG_MATRIX1_WPSR                    (0xFC0541E8U) /**< \brief (MATRIX1) Write Protect Status Register */
  #define REG_MATRIX1_SSR                     (0xFC054200U) /**< \brief (MATRIX1) Security Slave 0 Register */
  #define REG_MATRIX1_SASSR                   (0xFC054240U) /**< \brief (MATRIX1) Security Areas Split Slave 0 Register */
  #define REG_MATRIX1_SRTSR                   (0xFC054280U) /**< \brief (MATRIX1) Security Region Top Slave 0 Register */
  #define REG_MATRIX1_SPSELR                  (0xFC0542C0U) /**< \brief (MATRIX1) Security Peripheral Select 1 Register */
#else
  #define REG_MATRIX1_MCFG   (*(__IO uint32_t*)0xFC054000U) /**< \brief (MATRIX1) Master Configuration Register */
  #define REG_MATRIX1_SCFG   (*(__IO uint32_t*)0xFC054040U) /**< \brief (MATRIX1) Slave Configuration Register */
  #define REG_MATRIX1_PRAS0  (*(__IO uint32_t*)0xFC054080U) /**< \brief (MATRIX1) Priority Register A for Slave 0 */
  #define REG_MATRIX1_PRBS0  (*(__IO uint32_t*)0xFC054084U) /**< \brief (MATRIX1) Priority Register B for Slave 0 */
  #define REG_MATRIX1_PRAS1  (*(__IO uint32_t*)0xFC054088U) /**< \brief (MATRIX1) Priority Register A for Slave 1 */
  #define REG_MATRIX1_PRBS1  (*(__IO uint32_t*)0xFC05408CU) /**< \brief (MATRIX1) Priority Register B for Slave 1 */
  #define REG_MATRIX1_PRAS2  (*(__IO uint32_t*)0xFC054090U) /**< \brief (MATRIX1) Priority Register A for Slave 2 */
  #define REG_MATRIX1_PRBS2  (*(__IO uint32_t*)0xFC054094U) /**< \brief (MATRIX1) Priority Register B for Slave 2 */
  #define REG_MATRIX1_PRAS3  (*(__IO uint32_t*)0xFC054098U) /**< \brief (MATRIX1) Priority Register A for Slave 3 */
  #define REG_MATRIX1_PRBS3  (*(__IO uint32_t*)0xFC05409CU) /**< \brief (MATRIX1) Priority Register B for Slave 3 */
  #define REG_MATRIX1_PRAS4  (*(__IO uint32_t*)0xFC0540A0U) /**< \brief (MATRIX1) Priority Register A for Slave 4 */
  #define REG_MATRIX1_PRBS4  (*(__IO uint32_t*)0xFC0540A4U) /**< \brief (MATRIX1) Priority Register B for Slave 4 */
  #define REG_MATRIX1_PRAS5  (*(__IO uint32_t*)0xFC0540A8U) /**< \brief (MATRIX1) Priority Register A for Slave 5 */
  #define REG_MATRIX1_PRBS5  (*(__IO uint32_t*)0xFC0540ACU) /**< \brief (MATRIX1) Priority Register B for Slave 5 */
  #define REG_MATRIX1_PRAS6  (*(__IO uint32_t*)0xFC0540B0U) /**< \brief (MATRIX1) Priority Register A for Slave 6 */
  #define REG_MATRIX1_PRBS6  (*(__IO uint32_t*)0xFC0540B4U) /**< \brief (MATRIX1) Priority Register B for Slave 6 */
  #define REG_MATRIX1_PRAS7  (*(__IO uint32_t*)0xFC0540B8U) /**< \brief (MATRIX1) Priority Register A for Slave 7 */
  #define REG_MATRIX1_PRBS7  (*(__IO uint32_t*)0xFC0540BCU) /**< \brief (MATRIX1) Priority Register B for Slave 7 */
  #define REG_MATRIX1_PRAS8  (*(__IO uint32_t*)0xFC0540C0U) /**< \brief (MATRIX1) Priority Register A for Slave 8 */
  #define REG_MATRIX1_PRBS8  (*(__IO uint32_t*)0xFC0540C4U) /**< \brief (MATRIX1) Priority Register B for Slave 8 */
  #define REG_MATRIX1_PRAS9  (*(__IO uint32_t*)0xFC0540C8U) /**< \brief (MATRIX1) Priority Register A for Slave 9 */
  #define REG_MATRIX1_PRBS9  (*(__IO uint32_t*)0xFC0540CCU) /**< \brief (MATRIX1) Priority Register B for Slave 9 */
  #define REG_MATRIX1_PRAS10 (*(__IO uint32_t*)0xFC0540D0U) /**< \brief (MATRIX1) Priority Register A for Slave 10 */
  #define REG_MATRIX1_PRBS10 (*(__IO uint32_t*)0xFC0540D4U) /**< \brief (MATRIX1) Priority Register B for Slave 10 */
  #define REG_MATRIX1_PRAS11 (*(__IO uint32_t*)0xFC0540D8U) /**< \brief (MATRIX1) Priority Register A for Slave 11 */
  #define REG_MATRIX1_PRBS11 (*(__IO uint32_t*)0xFC0540DCU) /**< \brief (MATRIX1) Priority Register B for Slave 11 */
  #define REG_MATRIX1_PRAS12 (*(__IO uint32_t*)0xFC0540E0U) /**< \brief (MATRIX1) Priority Register A for Slave 12 */
  #define REG_MATRIX1_PRBS12 (*(__IO uint32_t*)0xFC0540E4U) /**< \brief (MATRIX1) Priority Register B for Slave 12 */
  #define REG_MATRIX1_MEIER  (*(__O  uint32_t*)0xFC054150U) /**< \brief (MATRIX1) Master Error Interrupt Enable Register */
  #define REG_MATRIX1_MEIDR  (*(__O  uint32_t*)0xFC054154U) /**< \brief (MATRIX1) Master Error Interrupt Disable Register */
  #define REG_MATRIX1_MEIMR  (*(__I  uint32_t*)0xFC054158U) /**< \brief (MATRIX1) Master Error Interrupt Mask Register */
  #define REG_MATRIX1_MESR   (*(__I  uint32_t*)0xFC05415CU) /**< \brief (MATRIX1) Master Error Status Register */
  #define REG_MATRIX1_MEAR   (*(__I  uint32_t*)0xFC054160U) /**< \brief (MATRIX1) Master 0 Error Address Register */
  #define REG_MATRIX1_WPMR   (*(__IO uint32_t*)0xFC0541E4U) /**< \brief (MATRIX1) Write Protect Mode Register */
  #define REG_MATRIX1_WPSR   (*(__I  uint32_t*)0xFC0541E8U) /**< \brief (MATRIX1) Write Protect Status Register */
  #define REG_MATRIX1_SSR    (*(__IO uint32_t*)0xFC054200U) /**< \brief (MATRIX1) Security Slave 0 Register */
  #define REG_MATRIX1_SASSR  (*(__IO uint32_t*)0xFC054240U) /**< \brief (MATRIX1) Security Areas Split Slave 0 Register */
  #define REG_MATRIX1_SRTSR  (*(__IO uint32_t*)0xFC054280U) /**< \brief (MATRIX1) Security Region Top Slave 0 Register */
  #define REG_MATRIX1_SPSELR (*(__IO uint32_t*)0xFC0542C0U) /**< \brief (MATRIX1) Security Peripheral Select 1 Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for HSMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_HSMC_CFG                         (0xFC05C000U) /**< \brief (HSMC) HSMC NFC Configuration Register */
  #define REG_HSMC_CTRL                        (0xFC05C004U) /**< \brief (HSMC) HSMC NFC Control Register */
  #define REG_HSMC_SR                          (0xFC05C008U) /**< \brief (HSMC) HSMC NFC Status Register */
  #define REG_HSMC_IER                         (0xFC05C00CU) /**< \brief (HSMC) HSMC NFC Interrupt Enable Register */
  #define REG_HSMC_IDR                         (0xFC05C010U) /**< \brief (HSMC) HSMC NFC Interrupt Disable Register */
  #define REG_HSMC_IMR                         (0xFC05C014U) /**< \brief (HSMC) HSMC NFC Interrupt Mask Register */
  #define REG_HSMC_ADDR                        (0xFC05C018U) /**< \brief (HSMC) HSMC NFC Address Cycle Zero Register */
  #define REG_HSMC_BANK                        (0xFC05C01CU) /**< \brief (HSMC) HSMC Bank Address Register */
  #define REG_HSMC_ECC_CTRL                    (0xFC05C020U) /**< \brief (HSMC) HSMC ECC Control Register */
  #define REG_HSMC_ECC_MD                      (0xFC05C024U) /**< \brief (HSMC) HSMC ECC Mode Register */
  #define REG_HSMC_ECC_SR1                     (0xFC05C028U) /**< \brief (HSMC) HSMC ECC Status 1 Register */
  #define REG_HSMC_ECC_PR0                     (0xFC05C02CU) /**< \brief (HSMC) HSMC ECC Parity 0 Register */
  #define REG_HSMC_ECC_PR1                     (0xFC05C030U) /**< \brief (HSMC) HSMC ECC parity 1 Register */
  #define REG_HSMC_ECC_SR2                     (0xFC05C034U) /**< \brief (HSMC) HSMC ECC status 2 Register */
  #define REG_HSMC_ECC_PR2                     (0xFC05C038U) /**< \brief (HSMC) HSMC ECC parity 2 Register */
  #define REG_HSMC_ECC_PR3                     (0xFC05C03CU) /**< \brief (HSMC) HSMC ECC parity 3 Register */
  #define REG_HSMC_ECC_PR4                     (0xFC05C040U) /**< \brief (HSMC) HSMC ECC parity 4 Register */
  #define REG_HSMC_ECC_PR5                     (0xFC05C044U) /**< \brief (HSMC) HSMC ECC parity 5 Register */
  #define REG_HSMC_ECC_PR6                     (0xFC05C048U) /**< \brief (HSMC) HSMC ECC parity 6 Register */
  #define REG_HSMC_ECC_PR7                     (0xFC05C04CU) /**< \brief (HSMC) HSMC ECC parity 7 Register */
  #define REG_HSMC_ECC_PR8                     (0xFC05C050U) /**< \brief (HSMC) HSMC ECC parity 8 Register */
  #define REG_HSMC_ECC_PR9                     (0xFC05C054U) /**< \brief (HSMC) HSMC ECC parity 9 Register */
  #define REG_HSMC_ECC_PR10                    (0xFC05C058U) /**< \brief (HSMC) HSMC ECC parity 10 Register */
  #define REG_HSMC_ECC_PR11                    (0xFC05C05CU) /**< \brief (HSMC) HSMC ECC parity 11 Register */
  #define REG_HSMC_ECC_PR12                    (0xFC05C060U) /**< \brief (HSMC) HSMC ECC parity 12 Register */
  #define REG_HSMC_ECC_PR13                    (0xFC05C064U) /**< \brief (HSMC) HSMC ECC parity 13 Register */
  #define REG_HSMC_ECC_PR14                    (0xFC05C068U) /**< \brief (HSMC) HSMC ECC parity 14 Register */
  #define REG_HSMC_ECC_PR15                    (0xFC05C06CU) /**< \brief (HSMC) HSMC ECC parity 15 Register */
  #define REG_HSMC_PMECCFG                     (0xFC05C070U) /**< \brief (HSMC) PMECC Configuration Register */
  #define REG_HSMC_PMECCSAREA                  (0xFC05C074U) /**< \brief (HSMC) PMECC Spare Area Size Register */
  #define REG_HSMC_PMECCSADDR                  (0xFC05C078U) /**< \brief (HSMC) PMECC Start Address Register */
  #define REG_HSMC_PMECCEADDR                  (0xFC05C07CU) /**< \brief (HSMC) PMECC End Address Register */
  #define REG_HSMC_PMECCTRL                    (0xFC05C084U) /**< \brief (HSMC) PMECC Control Register */
  #define REG_HSMC_PMECCSR                     (0xFC05C088U) /**< \brief (HSMC) PMECC Status Register */
  #define REG_HSMC_PMECCIER                    (0xFC05C08CU) /**< \brief (HSMC) PMECC Interrupt Enable register */
  #define REG_HSMC_PMECCIDR                    (0xFC05C090U) /**< \brief (HSMC) PMECC Interrupt Disable Register */
  #define REG_HSMC_PMECCIMR                    (0xFC05C094U) /**< \brief (HSMC) PMECC Interrupt Mask Register */
  #define REG_HSMC_PMECCISR                    (0xFC05C098U) /**< \brief (HSMC) PMECC Interrupt Status Register */
  #define REG_HSMC_PMECC0_0                    (0xFC05C0B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 0) */
  #define REG_HSMC_PMECC1_0                    (0xFC05C0B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 0) */
  #define REG_HSMC_PMECC2_0                    (0xFC05C0B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 0) */
  #define REG_HSMC_PMECC3_0                    (0xFC05C0BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 0) */
  #define REG_HSMC_PMECC4_0                    (0xFC05C0C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 0) */
  #define REG_HSMC_PMECC5_0                    (0xFC05C0C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 0) */
  #define REG_HSMC_PMECC6_0                    (0xFC05C0C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 0) */
  #define REG_HSMC_PMECC7_0                    (0xFC05C0CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 0) */
  #define REG_HSMC_PMECC8_0                    (0xFC05C0D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 0) */
  #define REG_HSMC_PMECC9_0                    (0xFC05C0D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 0) */
  #define REG_HSMC_PMECC10_0                   (0xFC05C0D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 0) */
  #define REG_HSMC_PMECC0_1                    (0xFC05C0F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 1) */
  #define REG_HSMC_PMECC1_1                    (0xFC05C0F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 1) */
  #define REG_HSMC_PMECC2_1                    (0xFC05C0F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 1) */
  #define REG_HSMC_PMECC3_1                    (0xFC05C0FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 1) */
  #define REG_HSMC_PMECC4_1                    (0xFC05C100U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 1) */
  #define REG_HSMC_PMECC5_1                    (0xFC05C104U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 1) */
  #define REG_HSMC_PMECC6_1                    (0xFC05C108U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 1) */
  #define REG_HSMC_PMECC7_1                    (0xFC05C10CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 1) */
  #define REG_HSMC_PMECC8_1                    (0xFC05C110U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 1) */
  #define REG_HSMC_PMECC9_1                    (0xFC05C114U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 1) */
  #define REG_HSMC_PMECC10_1                   (0xFC05C118U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 1) */
  #define REG_HSMC_PMECC0_2                    (0xFC05C130U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 2) */
  #define REG_HSMC_PMECC1_2                    (0xFC05C134U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 2) */
  #define REG_HSMC_PMECC2_2                    (0xFC05C138U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 2) */
  #define REG_HSMC_PMECC3_2                    (0xFC05C13CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 2) */
  #define REG_HSMC_PMECC4_2                    (0xFC05C140U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 2) */
  #define REG_HSMC_PMECC5_2                    (0xFC05C144U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 2) */
  #define REG_HSMC_PMECC6_2                    (0xFC05C148U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 2) */
  #define REG_HSMC_PMECC7_2                    (0xFC05C14CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 2) */
  #define REG_HSMC_PMECC8_2                    (0xFC05C150U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 2) */
  #define REG_HSMC_PMECC9_2                    (0xFC05C154U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 2) */
  #define REG_HSMC_PMECC10_2                   (0xFC05C158U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 2) */
  #define REG_HSMC_PMECC0_3                    (0xFC05C170U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 3) */
  #define REG_HSMC_PMECC1_3                    (0xFC05C174U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 3) */
  #define REG_HSMC_PMECC2_3                    (0xFC05C178U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 3) */
  #define REG_HSMC_PMECC3_3                    (0xFC05C17CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 3) */
  #define REG_HSMC_PMECC4_3                    (0xFC05C180U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 3) */
  #define REG_HSMC_PMECC5_3                    (0xFC05C184U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 3) */
  #define REG_HSMC_PMECC6_3                    (0xFC05C188U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 3) */
  #define REG_HSMC_PMECC7_3                    (0xFC05C18CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 3) */
  #define REG_HSMC_PMECC8_3                    (0xFC05C190U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 3) */
  #define REG_HSMC_PMECC9_3                    (0xFC05C194U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 3) */
  #define REG_HSMC_PMECC10_3                   (0xFC05C198U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 3) */
  #define REG_HSMC_PMECC0_4                    (0xFC05C1B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 4) */
  #define REG_HSMC_PMECC1_4                    (0xFC05C1B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 4) */
  #define REG_HSMC_PMECC2_4                    (0xFC05C1B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 4) */
  #define REG_HSMC_PMECC3_4                    (0xFC05C1BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 4) */
  #define REG_HSMC_PMECC4_4                    (0xFC05C1C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 4) */
  #define REG_HSMC_PMECC5_4                    (0xFC05C1C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 4) */
  #define REG_HSMC_PMECC6_4                    (0xFC05C1C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 4) */
  #define REG_HSMC_PMECC7_4                    (0xFC05C1CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 4) */
  #define REG_HSMC_PMECC8_4                    (0xFC05C1D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 4) */
  #define REG_HSMC_PMECC9_4                    (0xFC05C1D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 4) */
  #define REG_HSMC_PMECC10_4                   (0xFC05C1D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 4) */
  #define REG_HSMC_PMECC0_5                    (0xFC05C1F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 5) */
  #define REG_HSMC_PMECC1_5                    (0xFC05C1F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 5) */
  #define REG_HSMC_PMECC2_5                    (0xFC05C1F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 5) */
  #define REG_HSMC_PMECC3_5                    (0xFC05C1FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 5) */
  #define REG_HSMC_PMECC4_5                    (0xFC05C200U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 5) */
  #define REG_HSMC_PMECC5_5                    (0xFC05C204U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 5) */
  #define REG_HSMC_PMECC6_5                    (0xFC05C208U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 5) */
  #define REG_HSMC_PMECC7_5                    (0xFC05C20CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 5) */
  #define REG_HSMC_PMECC8_5                    (0xFC05C210U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 5) */
  #define REG_HSMC_PMECC9_5                    (0xFC05C214U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 5) */
  #define REG_HSMC_PMECC10_5                   (0xFC05C218U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 5) */
  #define REG_HSMC_PMECC0_6                    (0xFC05C230U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 6) */
  #define REG_HSMC_PMECC1_6                    (0xFC05C234U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 6) */
  #define REG_HSMC_PMECC2_6                    (0xFC05C238U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 6) */
  #define REG_HSMC_PMECC3_6                    (0xFC05C23CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 6) */
  #define REG_HSMC_PMECC4_6                    (0xFC05C240U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 6) */
  #define REG_HSMC_PMECC5_6                    (0xFC05C244U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 6) */
  #define REG_HSMC_PMECC6_6                    (0xFC05C248U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 6) */
  #define REG_HSMC_PMECC7_6                    (0xFC05C24CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 6) */
  #define REG_HSMC_PMECC8_6                    (0xFC05C250U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 6) */
  #define REG_HSMC_PMECC9_6                    (0xFC05C254U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 6) */
  #define REG_HSMC_PMECC10_6                   (0xFC05C258U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 6) */
  #define REG_HSMC_PMECC0_7                    (0xFC05C270U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 7) */
  #define REG_HSMC_PMECC1_7                    (0xFC05C274U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 7) */
  #define REG_HSMC_PMECC2_7                    (0xFC05C278U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 7) */
  #define REG_HSMC_PMECC3_7                    (0xFC05C27CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 7) */
  #define REG_HSMC_PMECC4_7                    (0xFC05C280U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 7) */
  #define REG_HSMC_PMECC5_7                    (0xFC05C284U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 7) */
  #define REG_HSMC_PMECC6_7                    (0xFC05C288U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 7) */
  #define REG_HSMC_PMECC7_7                    (0xFC05C28CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 7) */
  #define REG_HSMC_PMECC8_7                    (0xFC05C290U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 7) */
  #define REG_HSMC_PMECC9_7                    (0xFC05C294U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 7) */
  #define REG_HSMC_PMECC10_7                   (0xFC05C298U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 7) */
  #define REG_HSMC_REM0_0                      (0xFC05C2B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 0) */
  #define REG_HSMC_REM1_0                      (0xFC05C2B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 0) */
  #define REG_HSMC_REM2_0                      (0xFC05C2B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 0) */
  #define REG_HSMC_REM3_0                      (0xFC05C2BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 0) */
  #define REG_HSMC_REM4_0                      (0xFC05C2C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 0) */
  #define REG_HSMC_REM5_0                      (0xFC05C2C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 0) */
  #define REG_HSMC_REM6_0                      (0xFC05C2C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 0) */
  #define REG_HSMC_REM7_0                      (0xFC05C2CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 0) */
  #define REG_HSMC_REM8_0                      (0xFC05C2D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 0) */
  #define REG_HSMC_REM9_0                      (0xFC05C2D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 0) */
  #define REG_HSMC_REM10_0                     (0xFC05C2D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 0) */
  #define REG_HSMC_REM11_0                     (0xFC05C2DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 0) */
  #define REG_HSMC_REM0_1                      (0xFC05C2F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 1) */
  #define REG_HSMC_REM1_1                      (0xFC05C2F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 1) */
  #define REG_HSMC_REM2_1                      (0xFC05C2F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 1) */
  #define REG_HSMC_REM3_1                      (0xFC05C2FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 1) */
  #define REG_HSMC_REM4_1                      (0xFC05C300U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 1) */
  #define REG_HSMC_REM5_1                      (0xFC05C304U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 1) */
  #define REG_HSMC_REM6_1                      (0xFC05C308U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 1) */
  #define REG_HSMC_REM7_1                      (0xFC05C30CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 1) */
  #define REG_HSMC_REM8_1                      (0xFC05C310U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 1) */
  #define REG_HSMC_REM9_1                      (0xFC05C314U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 1) */
  #define REG_HSMC_REM10_1                     (0xFC05C318U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 1) */
  #define REG_HSMC_REM11_1                     (0xFC05C31CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 1) */
  #define REG_HSMC_REM0_2                      (0xFC05C330U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 2) */
  #define REG_HSMC_REM1_2                      (0xFC05C334U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 2) */
  #define REG_HSMC_REM2_2                      (0xFC05C338U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 2) */
  #define REG_HSMC_REM3_2                      (0xFC05C33CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 2) */
  #define REG_HSMC_REM4_2                      (0xFC05C340U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 2) */
  #define REG_HSMC_REM5_2                      (0xFC05C344U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 2) */
  #define REG_HSMC_REM6_2                      (0xFC05C348U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 2) */
  #define REG_HSMC_REM7_2                      (0xFC05C34CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 2) */
  #define REG_HSMC_REM8_2                      (0xFC05C350U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 2) */
  #define REG_HSMC_REM9_2                      (0xFC05C354U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 2) */
  #define REG_HSMC_REM10_2                     (0xFC05C358U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 2) */
  #define REG_HSMC_REM11_2                     (0xFC05C35CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 2) */
  #define REG_HSMC_REM0_3                      (0xFC05C370U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 3) */
  #define REG_HSMC_REM1_3                      (0xFC05C374U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 3) */
  #define REG_HSMC_REM2_3                      (0xFC05C378U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 3) */
  #define REG_HSMC_REM3_3                      (0xFC05C37CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 3) */
  #define REG_HSMC_REM4_3                      (0xFC05C380U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 3) */
  #define REG_HSMC_REM5_3                      (0xFC05C384U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 3) */
  #define REG_HSMC_REM6_3                      (0xFC05C388U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 3) */
  #define REG_HSMC_REM7_3                      (0xFC05C38CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 3) */
  #define REG_HSMC_REM8_3                      (0xFC05C390U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 3) */
  #define REG_HSMC_REM9_3                      (0xFC05C394U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 3) */
  #define REG_HSMC_REM10_3                     (0xFC05C398U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 3) */
  #define REG_HSMC_REM11_3                     (0xFC05C39CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 3) */
  #define REG_HSMC_REM0_4                      (0xFC05C3B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 4) */
  #define REG_HSMC_REM1_4                      (0xFC05C3B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 4) */
  #define REG_HSMC_REM2_4                      (0xFC05C3B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 4) */
  #define REG_HSMC_REM3_4                      (0xFC05C3BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 4) */
  #define REG_HSMC_REM4_4                      (0xFC05C3C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 4) */
  #define REG_HSMC_REM5_4                      (0xFC05C3C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 4) */
  #define REG_HSMC_REM6_4                      (0xFC05C3C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 4) */
  #define REG_HSMC_REM7_4                      (0xFC05C3CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 4) */
  #define REG_HSMC_REM8_4                      (0xFC05C3D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 4) */
  #define REG_HSMC_REM9_4                      (0xFC05C3D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 4) */
  #define REG_HSMC_REM10_4                     (0xFC05C3D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 4) */
  #define REG_HSMC_REM11_4                     (0xFC05C3DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 4) */
  #define REG_HSMC_REM0_5                      (0xFC05C3F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 5) */
  #define REG_HSMC_REM1_5                      (0xFC05C3F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 5) */
  #define REG_HSMC_REM2_5                      (0xFC05C3F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 5) */
  #define REG_HSMC_REM3_5                      (0xFC05C3FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 5) */
  #define REG_HSMC_REM4_5                      (0xFC05C400U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 5) */
  #define REG_HSMC_REM5_5                      (0xFC05C404U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 5) */
  #define REG_HSMC_REM6_5                      (0xFC05C408U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 5) */
  #define REG_HSMC_REM7_5                      (0xFC05C40CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 5) */
  #define REG_HSMC_REM8_5                      (0xFC05C410U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 5) */
  #define REG_HSMC_REM9_5                      (0xFC05C414U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 5) */
  #define REG_HSMC_REM10_5                     (0xFC05C418U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 5) */
  #define REG_HSMC_REM11_5                     (0xFC05C41CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 5) */
  #define REG_HSMC_REM0_6                      (0xFC05C430U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 6) */
  #define REG_HSMC_REM1_6                      (0xFC05C434U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 6) */
  #define REG_HSMC_REM2_6                      (0xFC05C438U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 6) */
  #define REG_HSMC_REM3_6                      (0xFC05C43CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 6) */
  #define REG_HSMC_REM4_6                      (0xFC05C440U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 6) */
  #define REG_HSMC_REM5_6                      (0xFC05C444U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 6) */
  #define REG_HSMC_REM6_6                      (0xFC05C448U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 6) */
  #define REG_HSMC_REM7_6                      (0xFC05C44CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 6) */
  #define REG_HSMC_REM8_6                      (0xFC05C450U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 6) */
  #define REG_HSMC_REM9_6                      (0xFC05C454U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 6) */
  #define REG_HSMC_REM10_6                     (0xFC05C458U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 6) */
  #define REG_HSMC_REM11_6                     (0xFC05C45CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 6) */
  #define REG_HSMC_REM0_7                      (0xFC05C470U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 7) */
  #define REG_HSMC_REM1_7                      (0xFC05C474U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 7) */
  #define REG_HSMC_REM2_7                      (0xFC05C478U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 7) */
  #define REG_HSMC_REM3_7                      (0xFC05C47CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 7) */
  #define REG_HSMC_REM4_7                      (0xFC05C480U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 7) */
  #define REG_HSMC_REM5_7                      (0xFC05C484U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 7) */
  #define REG_HSMC_REM6_7                      (0xFC05C488U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 7) */
  #define REG_HSMC_REM7_7                      (0xFC05C48CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 7) */
  #define REG_HSMC_REM8_7                      (0xFC05C490U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 7) */
  #define REG_HSMC_REM9_7                      (0xFC05C494U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 7) */
  #define REG_HSMC_REM10_7                     (0xFC05C498U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 7) */
  #define REG_HSMC_REM11_7                     (0xFC05C49CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 7) */
  #define REG_HSMC_ELCFG                       (0xFC05C500U) /**< \brief (HSMC) PMECC Error Location Configuration Register */
  #define REG_HSMC_ELPRIM                      (0xFC05C504U) /**< \brief (HSMC) PMECC Error Location Primitive Register */
  #define REG_HSMC_ELEN                        (0xFC05C508U) /**< \brief (HSMC) PMECC Error Location Enable Register */
  #define REG_HSMC_ELDIS                       (0xFC05C50CU) /**< \brief (HSMC) PMECC Error Location Disable Register */
  #define REG_HSMC_ELSR                        (0xFC05C510U) /**< \brief (HSMC) PMECC Error Location Status Register */
  #define REG_HSMC_ELIER                       (0xFC05C514U) /**< \brief (HSMC) PMECC Error Location Interrupt Enable register */
  #define REG_HSMC_ELIDR                       (0xFC05C518U) /**< \brief (HSMC) PMECC Error Location Interrupt Disable Register */
  #define REG_HSMC_ELIMR                       (0xFC05C51CU) /**< \brief (HSMC) PMECC Error Location Interrupt Mask Register */
  #define REG_HSMC_ELISR                       (0xFC05C520U) /**< \brief (HSMC) PMECC Error Location Interrupt Status Register */
  #define REG_HSMC_SIGMA0                      (0xFC05C528U) /**< \brief (HSMC) PMECC Error Location SIGMA 0 Register */
  #define REG_HSMC_SIGMA1                      (0xFC05C52CU) /**< \brief (HSMC) PMECC Error Location SIGMA 1 Register */
  #define REG_HSMC_SIGMA2                      (0xFC05C530U) /**< \brief (HSMC) PMECC Error Location SIGMA 2 Register */
  #define REG_HSMC_SIGMA3                      (0xFC05C534U) /**< \brief (HSMC) PMECC Error Location SIGMA 3 Register */
  #define REG_HSMC_SIGMA4                      (0xFC05C538U) /**< \brief (HSMC) PMECC Error Location SIGMA 4 Register */
  #define REG_HSMC_SIGMA5                      (0xFC05C53CU) /**< \brief (HSMC) PMECC Error Location SIGMA 5 Register */
  #define REG_HSMC_SIGMA6                      (0xFC05C540U) /**< \brief (HSMC) PMECC Error Location SIGMA 6 Register */
  #define REG_HSMC_SIGMA7                      (0xFC05C544U) /**< \brief (HSMC) PMECC Error Location SIGMA 7 Register */
  #define REG_HSMC_SIGMA8                      (0xFC05C548U) /**< \brief (HSMC) PMECC Error Location SIGMA 8 Register */
  #define REG_HSMC_SIGMA9                      (0xFC05C54CU) /**< \brief (HSMC) PMECC Error Location SIGMA 9 Register */
  #define REG_HSMC_SIGMA10                     (0xFC05C550U) /**< \brief (HSMC) PMECC Error Location SIGMA 10 Register */
  #define REG_HSMC_SIGMA11                     (0xFC05C554U) /**< \brief (HSMC) PMECC Error Location SIGMA 11 Register */
  #define REG_HSMC_SIGMA12                     (0xFC05C558U) /**< \brief (HSMC) PMECC Error Location SIGMA 12 Register */
  #define REG_HSMC_SIGMA13                     (0xFC05C55CU) /**< \brief (HSMC) PMECC Error Location SIGMA 13 Register */
  #define REG_HSMC_SIGMA14                     (0xFC05C560U) /**< \brief (HSMC) PMECC Error Location SIGMA 14 Register */
  #define REG_HSMC_SIGMA15                     (0xFC05C564U) /**< \brief (HSMC) PMECC Error Location SIGMA 15 Register */
  #define REG_HSMC_SIGMA16                     (0xFC05C568U) /**< \brief (HSMC) PMECC Error Location SIGMA 16 Register */
  #define REG_HSMC_SIGMA17                     (0xFC05C56CU) /**< \brief (HSMC) PMECC Error Location SIGMA 17 Register */
  #define REG_HSMC_SIGMA18                     (0xFC05C570U) /**< \brief (HSMC) PMECC Error Location SIGMA 18 Register */
  #define REG_HSMC_SIGMA19                     (0xFC05C574U) /**< \brief (HSMC) PMECC Error Location SIGMA 19 Register */
  #define REG_HSMC_SIGMA20                     (0xFC05C578U) /**< \brief (HSMC) PMECC Error Location SIGMA 20 Register */
  #define REG_HSMC_SIGMA21                     (0xFC05C57CU) /**< \brief (HSMC) PMECC Error Location SIGMA 21 Register */
  #define REG_HSMC_SIGMA22                     (0xFC05C580U) /**< \brief (HSMC) PMECC Error Location SIGMA 22 Register */
  #define REG_HSMC_SIGMA23                     (0xFC05C584U) /**< \brief (HSMC) PMECC Error Location SIGMA 23 Register */
  #define REG_HSMC_SIGMA24                     (0xFC05C588U) /**< \brief (HSMC) PMECC Error Location SIGMA 24 Register */
  #define REG_HSMC_ERRLOC                      (0xFC05C58CU) /**< \brief (HSMC) PMECC Error Location 0 Register */
  #define REG_HSMC_SETUP0                      (0xFC05C600U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 0) */
  #define REG_HSMC_PULSE0                      (0xFC05C604U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 0) */
  #define REG_HSMC_CYCLE0                      (0xFC05C608U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 0) */
  #define REG_HSMC_TIMINGS0                    (0xFC05C60CU) /**< \brief (HSMC) HSMC Timings Register (CS_number = 0) */
  #define REG_HSMC_MODE0                       (0xFC05C610U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 0) */
  #define REG_HSMC_SETUP1                      (0xFC05C614U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 1) */
  #define REG_HSMC_PULSE1                      (0xFC05C618U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 1) */
  #define REG_HSMC_CYCLE1                      (0xFC05C61CU) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 1) */
  #define REG_HSMC_TIMINGS1                    (0xFC05C620U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 1) */
  #define REG_HSMC_MODE1                       (0xFC05C624U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 1) */
  #define REG_HSMC_SETUP2                      (0xFC05C628U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 2) */
  #define REG_HSMC_PULSE2                      (0xFC05C62CU) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 2) */
  #define REG_HSMC_CYCLE2                      (0xFC05C630U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 2) */
  #define REG_HSMC_TIMINGS2                    (0xFC05C634U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 2) */
  #define REG_HSMC_MODE2                       (0xFC05C638U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 2) */
  #define REG_HSMC_SETUP3                      (0xFC05C63CU) /**< \brief (HSMC) HSMC Setup Register (CS_number = 3) */
  #define REG_HSMC_PULSE3                      (0xFC05C640U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 3) */
  #define REG_HSMC_CYCLE3                      (0xFC05C644U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 3) */
  #define REG_HSMC_TIMINGS3                    (0xFC05C648U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 3) */
  #define REG_HSMC_MODE3                       (0xFC05C64CU) /**< \brief (HSMC) HSMC Mode Register (CS_number = 3) */
  #define REG_HSMC_OCMS                        (0xFC05C6A0U) /**< \brief (HSMC) HSMC OCMS Register */
  #define REG_HSMC_KEY1                        (0xFC05C6A4U) /**< \brief (HSMC) HSMC OCMS KEY1 Register */
  #define REG_HSMC_KEY2                        (0xFC05C6A8U) /**< \brief (HSMC) HSMC OCMS KEY2 Register */
  #define REG_HSMC_WPCR                        (0xFC05C6E4U) /**< \brief (HSMC) HSMC Write Protection Control Register */
  #define REG_HSMC_WPSR                        (0xFC05C6E8U) /**< \brief (HSMC) HSMC Write Protection Status Register */
#else
  #define REG_HSMC_CFG        (*(__IO uint32_t*)0xFC05C000U) /**< \brief (HSMC) HSMC NFC Configuration Register */
  #define REG_HSMC_CTRL       (*(__O  uint32_t*)0xFC05C004U) /**< \brief (HSMC) HSMC NFC Control Register */
  #define REG_HSMC_SR         (*(__I  uint32_t*)0xFC05C008U) /**< \brief (HSMC) HSMC NFC Status Register */
  #define REG_HSMC_IER        (*(__O  uint32_t*)0xFC05C00CU) /**< \brief (HSMC) HSMC NFC Interrupt Enable Register */
  #define REG_HSMC_IDR        (*(__O  uint32_t*)0xFC05C010U) /**< \brief (HSMC) HSMC NFC Interrupt Disable Register */
  #define REG_HSMC_IMR        (*(__I  uint32_t*)0xFC05C014U) /**< \brief (HSMC) HSMC NFC Interrupt Mask Register */
  #define REG_HSMC_ADDR       (*(__IO uint32_t*)0xFC05C018U) /**< \brief (HSMC) HSMC NFC Address Cycle Zero Register */
  #define REG_HSMC_BANK       (*(__IO uint32_t*)0xFC05C01CU) /**< \brief (HSMC) HSMC Bank Address Register */
  #define REG_HSMC_ECC_CTRL   (*(__O  uint32_t*)0xFC05C020U) /**< \brief (HSMC) HSMC ECC Control Register */
  #define REG_HSMC_ECC_MD     (*(__IO uint32_t*)0xFC05C024U) /**< \brief (HSMC) HSMC ECC Mode Register */
  #define REG_HSMC_ECC_SR1    (*(__I  uint32_t*)0xFC05C028U) /**< \brief (HSMC) HSMC ECC Status 1 Register */
  #define REG_HSMC_ECC_PR0    (*(__I  uint32_t*)0xFC05C02CU) /**< \brief (HSMC) HSMC ECC Parity 0 Register */
  #define REG_HSMC_ECC_PR1    (*(__I  uint32_t*)0xFC05C030U) /**< \brief (HSMC) HSMC ECC parity 1 Register */
  #define REG_HSMC_ECC_SR2    (*(__I  uint32_t*)0xFC05C034U) /**< \brief (HSMC) HSMC ECC status 2 Register */
  #define REG_HSMC_ECC_PR2    (*(__I  uint32_t*)0xFC05C038U) /**< \brief (HSMC) HSMC ECC parity 2 Register */
  #define REG_HSMC_ECC_PR3    (*(__I  uint32_t*)0xFC05C03CU) /**< \brief (HSMC) HSMC ECC parity 3 Register */
  #define REG_HSMC_ECC_PR4    (*(__I  uint32_t*)0xFC05C040U) /**< \brief (HSMC) HSMC ECC parity 4 Register */
  #define REG_HSMC_ECC_PR5    (*(__I  uint32_t*)0xFC05C044U) /**< \brief (HSMC) HSMC ECC parity 5 Register */
  #define REG_HSMC_ECC_PR6    (*(__I  uint32_t*)0xFC05C048U) /**< \brief (HSMC) HSMC ECC parity 6 Register */
  #define REG_HSMC_ECC_PR7    (*(__I  uint32_t*)0xFC05C04CU) /**< \brief (HSMC) HSMC ECC parity 7 Register */
  #define REG_HSMC_ECC_PR8    (*(__I  uint32_t*)0xFC05C050U) /**< \brief (HSMC) HSMC ECC parity 8 Register */
  #define REG_HSMC_ECC_PR9    (*(__I  uint32_t*)0xFC05C054U) /**< \brief (HSMC) HSMC ECC parity 9 Register */
  #define REG_HSMC_ECC_PR10   (*(__I  uint32_t*)0xFC05C058U) /**< \brief (HSMC) HSMC ECC parity 10 Register */
  #define REG_HSMC_ECC_PR11   (*(__I  uint32_t*)0xFC05C05CU) /**< \brief (HSMC) HSMC ECC parity 11 Register */
  #define REG_HSMC_ECC_PR12   (*(__I  uint32_t*)0xFC05C060U) /**< \brief (HSMC) HSMC ECC parity 12 Register */
  #define REG_HSMC_ECC_PR13   (*(__I  uint32_t*)0xFC05C064U) /**< \brief (HSMC) HSMC ECC parity 13 Register */
  #define REG_HSMC_ECC_PR14   (*(__I  uint32_t*)0xFC05C068U) /**< \brief (HSMC) HSMC ECC parity 14 Register */
  #define REG_HSMC_ECC_PR15   (*(__I  uint32_t*)0xFC05C06CU) /**< \brief (HSMC) HSMC ECC parity 15 Register */
  #define REG_HSMC_PMECCFG    (*(__IO uint32_t*)0xFC05C070U) /**< \brief (HSMC) PMECC Configuration Register */
  #define REG_HSMC_PMECCSAREA (*(__IO uint32_t*)0xFC05C074U) /**< \brief (HSMC) PMECC Spare Area Size Register */
  #define REG_HSMC_PMECCSADDR (*(__IO uint32_t*)0xFC05C078U) /**< \brief (HSMC) PMECC Start Address Register */
  #define REG_HSMC_PMECCEADDR (*(__IO uint32_t*)0xFC05C07CU) /**< \brief (HSMC) PMECC End Address Register */
  #define REG_HSMC_PMECCTRL   (*(__O  uint32_t*)0xFC05C084U) /**< \brief (HSMC) PMECC Control Register */
  #define REG_HSMC_PMECCSR    (*(__I  uint32_t*)0xFC05C088U) /**< \brief (HSMC) PMECC Status Register */
  #define REG_HSMC_PMECCIER   (*(__O  uint32_t*)0xFC05C08CU) /**< \brief (HSMC) PMECC Interrupt Enable register */
  #define REG_HSMC_PMECCIDR   (*(__O  uint32_t*)0xFC05C090U) /**< \brief (HSMC) PMECC Interrupt Disable Register */
  #define REG_HSMC_PMECCIMR   (*(__I  uint32_t*)0xFC05C094U) /**< \brief (HSMC) PMECC Interrupt Mask Register */
  #define REG_HSMC_PMECCISR   (*(__I  uint32_t*)0xFC05C098U) /**< \brief (HSMC) PMECC Interrupt Status Register */
  #define REG_HSMC_PMECC0_0   (*(__I  uint32_t*)0xFC05C0B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 0) */
  #define REG_HSMC_PMECC1_0   (*(__I  uint32_t*)0xFC05C0B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 0) */
  #define REG_HSMC_PMECC2_0   (*(__I  uint32_t*)0xFC05C0B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 0) */
  #define REG_HSMC_PMECC3_0   (*(__I  uint32_t*)0xFC05C0BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 0) */
  #define REG_HSMC_PMECC4_0   (*(__I  uint32_t*)0xFC05C0C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 0) */
  #define REG_HSMC_PMECC5_0   (*(__I  uint32_t*)0xFC05C0C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 0) */
  #define REG_HSMC_PMECC6_0   (*(__I  uint32_t*)0xFC05C0C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 0) */
  #define REG_HSMC_PMECC7_0   (*(__I  uint32_t*)0xFC05C0CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 0) */
  #define REG_HSMC_PMECC8_0   (*(__I  uint32_t*)0xFC05C0D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 0) */
  #define REG_HSMC_PMECC9_0   (*(__I  uint32_t*)0xFC05C0D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 0) */
  #define REG_HSMC_PMECC10_0  (*(__I  uint32_t*)0xFC05C0D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 0) */
  #define REG_HSMC_PMECC0_1   (*(__I  uint32_t*)0xFC05C0F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 1) */
  #define REG_HSMC_PMECC1_1   (*(__I  uint32_t*)0xFC05C0F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 1) */
  #define REG_HSMC_PMECC2_1   (*(__I  uint32_t*)0xFC05C0F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 1) */
  #define REG_HSMC_PMECC3_1   (*(__I  uint32_t*)0xFC05C0FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 1) */
  #define REG_HSMC_PMECC4_1   (*(__I  uint32_t*)0xFC05C100U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 1) */
  #define REG_HSMC_PMECC5_1   (*(__I  uint32_t*)0xFC05C104U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 1) */
  #define REG_HSMC_PMECC6_1   (*(__I  uint32_t*)0xFC05C108U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 1) */
  #define REG_HSMC_PMECC7_1   (*(__I  uint32_t*)0xFC05C10CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 1) */
  #define REG_HSMC_PMECC8_1   (*(__I  uint32_t*)0xFC05C110U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 1) */
  #define REG_HSMC_PMECC9_1   (*(__I  uint32_t*)0xFC05C114U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 1) */
  #define REG_HSMC_PMECC10_1  (*(__I  uint32_t*)0xFC05C118U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 1) */
  #define REG_HSMC_PMECC0_2   (*(__I  uint32_t*)0xFC05C130U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 2) */
  #define REG_HSMC_PMECC1_2   (*(__I  uint32_t*)0xFC05C134U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 2) */
  #define REG_HSMC_PMECC2_2   (*(__I  uint32_t*)0xFC05C138U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 2) */
  #define REG_HSMC_PMECC3_2   (*(__I  uint32_t*)0xFC05C13CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 2) */
  #define REG_HSMC_PMECC4_2   (*(__I  uint32_t*)0xFC05C140U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 2) */
  #define REG_HSMC_PMECC5_2   (*(__I  uint32_t*)0xFC05C144U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 2) */
  #define REG_HSMC_PMECC6_2   (*(__I  uint32_t*)0xFC05C148U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 2) */
  #define REG_HSMC_PMECC7_2   (*(__I  uint32_t*)0xFC05C14CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 2) */
  #define REG_HSMC_PMECC8_2   (*(__I  uint32_t*)0xFC05C150U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 2) */
  #define REG_HSMC_PMECC9_2   (*(__I  uint32_t*)0xFC05C154U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 2) */
  #define REG_HSMC_PMECC10_2  (*(__I  uint32_t*)0xFC05C158U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 2) */
  #define REG_HSMC_PMECC0_3   (*(__I  uint32_t*)0xFC05C170U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 3) */
  #define REG_HSMC_PMECC1_3   (*(__I  uint32_t*)0xFC05C174U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 3) */
  #define REG_HSMC_PMECC2_3   (*(__I  uint32_t*)0xFC05C178U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 3) */
  #define REG_HSMC_PMECC3_3   (*(__I  uint32_t*)0xFC05C17CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 3) */
  #define REG_HSMC_PMECC4_3   (*(__I  uint32_t*)0xFC05C180U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 3) */
  #define REG_HSMC_PMECC5_3   (*(__I  uint32_t*)0xFC05C184U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 3) */
  #define REG_HSMC_PMECC6_3   (*(__I  uint32_t*)0xFC05C188U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 3) */
  #define REG_HSMC_PMECC7_3   (*(__I  uint32_t*)0xFC05C18CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 3) */
  #define REG_HSMC_PMECC8_3   (*(__I  uint32_t*)0xFC05C190U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 3) */
  #define REG_HSMC_PMECC9_3   (*(__I  uint32_t*)0xFC05C194U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 3) */
  #define REG_HSMC_PMECC10_3  (*(__I  uint32_t*)0xFC05C198U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 3) */
  #define REG_HSMC_PMECC0_4   (*(__I  uint32_t*)0xFC05C1B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 4) */
  #define REG_HSMC_PMECC1_4   (*(__I  uint32_t*)0xFC05C1B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 4) */
  #define REG_HSMC_PMECC2_4   (*(__I  uint32_t*)0xFC05C1B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 4) */
  #define REG_HSMC_PMECC3_4   (*(__I  uint32_t*)0xFC05C1BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 4) */
  #define REG_HSMC_PMECC4_4   (*(__I  uint32_t*)0xFC05C1C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 4) */
  #define REG_HSMC_PMECC5_4   (*(__I  uint32_t*)0xFC05C1C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 4) */
  #define REG_HSMC_PMECC6_4   (*(__I  uint32_t*)0xFC05C1C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 4) */
  #define REG_HSMC_PMECC7_4   (*(__I  uint32_t*)0xFC05C1CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 4) */
  #define REG_HSMC_PMECC8_4   (*(__I  uint32_t*)0xFC05C1D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 4) */
  #define REG_HSMC_PMECC9_4   (*(__I  uint32_t*)0xFC05C1D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 4) */
  #define REG_HSMC_PMECC10_4  (*(__I  uint32_t*)0xFC05C1D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 4) */
  #define REG_HSMC_PMECC0_5   (*(__I  uint32_t*)0xFC05C1F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 5) */
  #define REG_HSMC_PMECC1_5   (*(__I  uint32_t*)0xFC05C1F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 5) */
  #define REG_HSMC_PMECC2_5   (*(__I  uint32_t*)0xFC05C1F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 5) */
  #define REG_HSMC_PMECC3_5   (*(__I  uint32_t*)0xFC05C1FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 5) */
  #define REG_HSMC_PMECC4_5   (*(__I  uint32_t*)0xFC05C200U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 5) */
  #define REG_HSMC_PMECC5_5   (*(__I  uint32_t*)0xFC05C204U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 5) */
  #define REG_HSMC_PMECC6_5   (*(__I  uint32_t*)0xFC05C208U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 5) */
  #define REG_HSMC_PMECC7_5   (*(__I  uint32_t*)0xFC05C20CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 5) */
  #define REG_HSMC_PMECC8_5   (*(__I  uint32_t*)0xFC05C210U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 5) */
  #define REG_HSMC_PMECC9_5   (*(__I  uint32_t*)0xFC05C214U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 5) */
  #define REG_HSMC_PMECC10_5  (*(__I  uint32_t*)0xFC05C218U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 5) */
  #define REG_HSMC_PMECC0_6   (*(__I  uint32_t*)0xFC05C230U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 6) */
  #define REG_HSMC_PMECC1_6   (*(__I  uint32_t*)0xFC05C234U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 6) */
  #define REG_HSMC_PMECC2_6   (*(__I  uint32_t*)0xFC05C238U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 6) */
  #define REG_HSMC_PMECC3_6   (*(__I  uint32_t*)0xFC05C23CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 6) */
  #define REG_HSMC_PMECC4_6   (*(__I  uint32_t*)0xFC05C240U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 6) */
  #define REG_HSMC_PMECC5_6   (*(__I  uint32_t*)0xFC05C244U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 6) */
  #define REG_HSMC_PMECC6_6   (*(__I  uint32_t*)0xFC05C248U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 6) */
  #define REG_HSMC_PMECC7_6   (*(__I  uint32_t*)0xFC05C24CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 6) */
  #define REG_HSMC_PMECC8_6   (*(__I  uint32_t*)0xFC05C250U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 6) */
  #define REG_HSMC_PMECC9_6   (*(__I  uint32_t*)0xFC05C254U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 6) */
  #define REG_HSMC_PMECC10_6  (*(__I  uint32_t*)0xFC05C258U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 6) */
  #define REG_HSMC_PMECC0_7   (*(__I  uint32_t*)0xFC05C270U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 7) */
  #define REG_HSMC_PMECC1_7   (*(__I  uint32_t*)0xFC05C274U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 7) */
  #define REG_HSMC_PMECC2_7   (*(__I  uint32_t*)0xFC05C278U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 7) */
  #define REG_HSMC_PMECC3_7   (*(__I  uint32_t*)0xFC05C27CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 7) */
  #define REG_HSMC_PMECC4_7   (*(__I  uint32_t*)0xFC05C280U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 7) */
  #define REG_HSMC_PMECC5_7   (*(__I  uint32_t*)0xFC05C284U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 7) */
  #define REG_HSMC_PMECC6_7   (*(__I  uint32_t*)0xFC05C288U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 7) */
  #define REG_HSMC_PMECC7_7   (*(__I  uint32_t*)0xFC05C28CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 7) */
  #define REG_HSMC_PMECC8_7   (*(__I  uint32_t*)0xFC05C290U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 7) */
  #define REG_HSMC_PMECC9_7   (*(__I  uint32_t*)0xFC05C294U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 7) */
  #define REG_HSMC_PMECC10_7  (*(__I  uint32_t*)0xFC05C298U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 7) */
  #define REG_HSMC_REM0_0     (*(__I  uint32_t*)0xFC05C2B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 0) */
  #define REG_HSMC_REM1_0     (*(__I  uint32_t*)0xFC05C2B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 0) */
  #define REG_HSMC_REM2_0     (*(__I  uint32_t*)0xFC05C2B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 0) */
  #define REG_HSMC_REM3_0     (*(__I  uint32_t*)0xFC05C2BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 0) */
  #define REG_HSMC_REM4_0     (*(__I  uint32_t*)0xFC05C2C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 0) */
  #define REG_HSMC_REM5_0     (*(__I  uint32_t*)0xFC05C2C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 0) */
  #define REG_HSMC_REM6_0     (*(__I  uint32_t*)0xFC05C2C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 0) */
  #define REG_HSMC_REM7_0     (*(__I  uint32_t*)0xFC05C2CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 0) */
  #define REG_HSMC_REM8_0     (*(__I  uint32_t*)0xFC05C2D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 0) */
  #define REG_HSMC_REM9_0     (*(__I  uint32_t*)0xFC05C2D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 0) */
  #define REG_HSMC_REM10_0    (*(__I  uint32_t*)0xFC05C2D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 0) */
  #define REG_HSMC_REM11_0    (*(__I  uint32_t*)0xFC05C2DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 0) */
  #define REG_HSMC_REM0_1     (*(__I  uint32_t*)0xFC05C2F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 1) */
  #define REG_HSMC_REM1_1     (*(__I  uint32_t*)0xFC05C2F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 1) */
  #define REG_HSMC_REM2_1     (*(__I  uint32_t*)0xFC05C2F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 1) */
  #define REG_HSMC_REM3_1     (*(__I  uint32_t*)0xFC05C2FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 1) */
  #define REG_HSMC_REM4_1     (*(__I  uint32_t*)0xFC05C300U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 1) */
  #define REG_HSMC_REM5_1     (*(__I  uint32_t*)0xFC05C304U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 1) */
  #define REG_HSMC_REM6_1     (*(__I  uint32_t*)0xFC05C308U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 1) */
  #define REG_HSMC_REM7_1     (*(__I  uint32_t*)0xFC05C30CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 1) */
  #define REG_HSMC_REM8_1     (*(__I  uint32_t*)0xFC05C310U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 1) */
  #define REG_HSMC_REM9_1     (*(__I  uint32_t*)0xFC05C314U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 1) */
  #define REG_HSMC_REM10_1    (*(__I  uint32_t*)0xFC05C318U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 1) */
  #define REG_HSMC_REM11_1    (*(__I  uint32_t*)0xFC05C31CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 1) */
  #define REG_HSMC_REM0_2     (*(__I  uint32_t*)0xFC05C330U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 2) */
  #define REG_HSMC_REM1_2     (*(__I  uint32_t*)0xFC05C334U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 2) */
  #define REG_HSMC_REM2_2     (*(__I  uint32_t*)0xFC05C338U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 2) */
  #define REG_HSMC_REM3_2     (*(__I  uint32_t*)0xFC05C33CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 2) */
  #define REG_HSMC_REM4_2     (*(__I  uint32_t*)0xFC05C340U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 2) */
  #define REG_HSMC_REM5_2     (*(__I  uint32_t*)0xFC05C344U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 2) */
  #define REG_HSMC_REM6_2     (*(__I  uint32_t*)0xFC05C348U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 2) */
  #define REG_HSMC_REM7_2     (*(__I  uint32_t*)0xFC05C34CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 2) */
  #define REG_HSMC_REM8_2     (*(__I  uint32_t*)0xFC05C350U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 2) */
  #define REG_HSMC_REM9_2     (*(__I  uint32_t*)0xFC05C354U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 2) */
  #define REG_HSMC_REM10_2    (*(__I  uint32_t*)0xFC05C358U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 2) */
  #define REG_HSMC_REM11_2    (*(__I  uint32_t*)0xFC05C35CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 2) */
  #define REG_HSMC_REM0_3     (*(__I  uint32_t*)0xFC05C370U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 3) */
  #define REG_HSMC_REM1_3     (*(__I  uint32_t*)0xFC05C374U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 3) */
  #define REG_HSMC_REM2_3     (*(__I  uint32_t*)0xFC05C378U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 3) */
  #define REG_HSMC_REM3_3     (*(__I  uint32_t*)0xFC05C37CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 3) */
  #define REG_HSMC_REM4_3     (*(__I  uint32_t*)0xFC05C380U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 3) */
  #define REG_HSMC_REM5_3     (*(__I  uint32_t*)0xFC05C384U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 3) */
  #define REG_HSMC_REM6_3     (*(__I  uint32_t*)0xFC05C388U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 3) */
  #define REG_HSMC_REM7_3     (*(__I  uint32_t*)0xFC05C38CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 3) */
  #define REG_HSMC_REM8_3     (*(__I  uint32_t*)0xFC05C390U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 3) */
  #define REG_HSMC_REM9_3     (*(__I  uint32_t*)0xFC05C394U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 3) */
  #define REG_HSMC_REM10_3    (*(__I  uint32_t*)0xFC05C398U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 3) */
  #define REG_HSMC_REM11_3    (*(__I  uint32_t*)0xFC05C39CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 3) */
  #define REG_HSMC_REM0_4     (*(__I  uint32_t*)0xFC05C3B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 4) */
  #define REG_HSMC_REM1_4     (*(__I  uint32_t*)0xFC05C3B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 4) */
  #define REG_HSMC_REM2_4     (*(__I  uint32_t*)0xFC05C3B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 4) */
  #define REG_HSMC_REM3_4     (*(__I  uint32_t*)0xFC05C3BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 4) */
  #define REG_HSMC_REM4_4     (*(__I  uint32_t*)0xFC05C3C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 4) */
  #define REG_HSMC_REM5_4     (*(__I  uint32_t*)0xFC05C3C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 4) */
  #define REG_HSMC_REM6_4     (*(__I  uint32_t*)0xFC05C3C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 4) */
  #define REG_HSMC_REM7_4     (*(__I  uint32_t*)0xFC05C3CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 4) */
  #define REG_HSMC_REM8_4     (*(__I  uint32_t*)0xFC05C3D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 4) */
  #define REG_HSMC_REM9_4     (*(__I  uint32_t*)0xFC05C3D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 4) */
  #define REG_HSMC_REM10_4    (*(__I  uint32_t*)0xFC05C3D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 4) */
  #define REG_HSMC_REM11_4    (*(__I  uint32_t*)0xFC05C3DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 4) */
  #define REG_HSMC_REM0_5     (*(__I  uint32_t*)0xFC05C3F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 5) */
  #define REG_HSMC_REM1_5     (*(__I  uint32_t*)0xFC05C3F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 5) */
  #define REG_HSMC_REM2_5     (*(__I  uint32_t*)0xFC05C3F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 5) */
  #define REG_HSMC_REM3_5     (*(__I  uint32_t*)0xFC05C3FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 5) */
  #define REG_HSMC_REM4_5     (*(__I  uint32_t*)0xFC05C400U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 5) */
  #define REG_HSMC_REM5_5     (*(__I  uint32_t*)0xFC05C404U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 5) */
  #define REG_HSMC_REM6_5     (*(__I  uint32_t*)0xFC05C408U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 5) */
  #define REG_HSMC_REM7_5     (*(__I  uint32_t*)0xFC05C40CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 5) */
  #define REG_HSMC_REM8_5     (*(__I  uint32_t*)0xFC05C410U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 5) */
  #define REG_HSMC_REM9_5     (*(__I  uint32_t*)0xFC05C414U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 5) */
  #define REG_HSMC_REM10_5    (*(__I  uint32_t*)0xFC05C418U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 5) */
  #define REG_HSMC_REM11_5    (*(__I  uint32_t*)0xFC05C41CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 5) */
  #define REG_HSMC_REM0_6     (*(__I  uint32_t*)0xFC05C430U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 6) */
  #define REG_HSMC_REM1_6     (*(__I  uint32_t*)0xFC05C434U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 6) */
  #define REG_HSMC_REM2_6     (*(__I  uint32_t*)0xFC05C438U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 6) */
  #define REG_HSMC_REM3_6     (*(__I  uint32_t*)0xFC05C43CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 6) */
  #define REG_HSMC_REM4_6     (*(__I  uint32_t*)0xFC05C440U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 6) */
  #define REG_HSMC_REM5_6     (*(__I  uint32_t*)0xFC05C444U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 6) */
  #define REG_HSMC_REM6_6     (*(__I  uint32_t*)0xFC05C448U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 6) */
  #define REG_HSMC_REM7_6     (*(__I  uint32_t*)0xFC05C44CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 6) */
  #define REG_HSMC_REM8_6     (*(__I  uint32_t*)0xFC05C450U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 6) */
  #define REG_HSMC_REM9_6     (*(__I  uint32_t*)0xFC05C454U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 6) */
  #define REG_HSMC_REM10_6    (*(__I  uint32_t*)0xFC05C458U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 6) */
  #define REG_HSMC_REM11_6    (*(__I  uint32_t*)0xFC05C45CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 6) */
  #define REG_HSMC_REM0_7     (*(__I  uint32_t*)0xFC05C470U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 7) */
  #define REG_HSMC_REM1_7     (*(__I  uint32_t*)0xFC05C474U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 7) */
  #define REG_HSMC_REM2_7     (*(__I  uint32_t*)0xFC05C478U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 7) */
  #define REG_HSMC_REM3_7     (*(__I  uint32_t*)0xFC05C47CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 7) */
  #define REG_HSMC_REM4_7     (*(__I  uint32_t*)0xFC05C480U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 7) */
  #define REG_HSMC_REM5_7     (*(__I  uint32_t*)0xFC05C484U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 7) */
  #define REG_HSMC_REM6_7     (*(__I  uint32_t*)0xFC05C488U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 7) */
  #define REG_HSMC_REM7_7     (*(__I  uint32_t*)0xFC05C48CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 7) */
  #define REG_HSMC_REM8_7     (*(__I  uint32_t*)0xFC05C490U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 7) */
  #define REG_HSMC_REM9_7     (*(__I  uint32_t*)0xFC05C494U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 7) */
  #define REG_HSMC_REM10_7    (*(__I  uint32_t*)0xFC05C498U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 7) */
  #define REG_HSMC_REM11_7    (*(__I  uint32_t*)0xFC05C49CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 7) */
  #define REG_HSMC_ELCFG      (*(__IO uint32_t*)0xFC05C500U) /**< \brief (HSMC) PMECC Error Location Configuration Register */
  #define REG_HSMC_ELPRIM     (*(__I  uint32_t*)0xFC05C504U) /**< \brief (HSMC) PMECC Error Location Primitive Register */
  #define REG_HSMC_ELEN       (*(__O  uint32_t*)0xFC05C508U) /**< \brief (HSMC) PMECC Error Location Enable Register */
  #define REG_HSMC_ELDIS      (*(__O  uint32_t*)0xFC05C50CU) /**< \brief (HSMC) PMECC Error Location Disable Register */
  #define REG_HSMC_ELSR       (*(__I  uint32_t*)0xFC05C510U) /**< \brief (HSMC) PMECC Error Location Status Register */
  #define REG_HSMC_ELIER      (*(__O  uint32_t*)0xFC05C514U) /**< \brief (HSMC) PMECC Error Location Interrupt Enable register */
  #define REG_HSMC_ELIDR      (*(__O  uint32_t*)0xFC05C518U) /**< \brief (HSMC) PMECC Error Location Interrupt Disable Register */
  #define REG_HSMC_ELIMR      (*(__I  uint32_t*)0xFC05C51CU) /**< \brief (HSMC) PMECC Error Location Interrupt Mask Register */
  #define REG_HSMC_ELISR      (*(__I  uint32_t*)0xFC05C520U) /**< \brief (HSMC) PMECC Error Location Interrupt Status Register */
  #define REG_HSMC_SIGMA0     (*(__IO uint32_t*)0xFC05C528U) /**< \brief (HSMC) PMECC Error Location SIGMA 0 Register */
  #define REG_HSMC_SIGMA1     (*(__IO uint32_t*)0xFC05C52CU) /**< \brief (HSMC) PMECC Error Location SIGMA 1 Register */
  #define REG_HSMC_SIGMA2     (*(__IO uint32_t*)0xFC05C530U) /**< \brief (HSMC) PMECC Error Location SIGMA 2 Register */
  #define REG_HSMC_SIGMA3     (*(__IO uint32_t*)0xFC05C534U) /**< \brief (HSMC) PMECC Error Location SIGMA 3 Register */
  #define REG_HSMC_SIGMA4     (*(__IO uint32_t*)0xFC05C538U) /**< \brief (HSMC) PMECC Error Location SIGMA 4 Register */
  #define REG_HSMC_SIGMA5     (*(__IO uint32_t*)0xFC05C53CU) /**< \brief (HSMC) PMECC Error Location SIGMA 5 Register */
  #define REG_HSMC_SIGMA6     (*(__IO uint32_t*)0xFC05C540U) /**< \brief (HSMC) PMECC Error Location SIGMA 6 Register */
  #define REG_HSMC_SIGMA7     (*(__IO uint32_t*)0xFC05C544U) /**< \brief (HSMC) PMECC Error Location SIGMA 7 Register */
  #define REG_HSMC_SIGMA8     (*(__IO uint32_t*)0xFC05C548U) /**< \brief (HSMC) PMECC Error Location SIGMA 8 Register */
  #define REG_HSMC_SIGMA9     (*(__IO uint32_t*)0xFC05C54CU) /**< \brief (HSMC) PMECC Error Location SIGMA 9 Register */
  #define REG_HSMC_SIGMA10    (*(__IO uint32_t*)0xFC05C550U) /**< \brief (HSMC) PMECC Error Location SIGMA 10 Register */
  #define REG_HSMC_SIGMA11    (*(__IO uint32_t*)0xFC05C554U) /**< \brief (HSMC) PMECC Error Location SIGMA 11 Register */
  #define REG_HSMC_SIGMA12    (*(__IO uint32_t*)0xFC05C558U) /**< \brief (HSMC) PMECC Error Location SIGMA 12 Register */
  #define REG_HSMC_SIGMA13    (*(__IO uint32_t*)0xFC05C55CU) /**< \brief (HSMC) PMECC Error Location SIGMA 13 Register */
  #define REG_HSMC_SIGMA14    (*(__IO uint32_t*)0xFC05C560U) /**< \brief (HSMC) PMECC Error Location SIGMA 14 Register */
  #define REG_HSMC_SIGMA15    (*(__IO uint32_t*)0xFC05C564U) /**< \brief (HSMC) PMECC Error Location SIGMA 15 Register */
  #define REG_HSMC_SIGMA16    (*(__IO uint32_t*)0xFC05C568U) /**< \brief (HSMC) PMECC Error Location SIGMA 16 Register */
  #define REG_HSMC_SIGMA17    (*(__IO uint32_t*)0xFC05C56CU) /**< \brief (HSMC) PMECC Error Location SIGMA 17 Register */
  #define REG_HSMC_SIGMA18    (*(__IO uint32_t*)0xFC05C570U) /**< \brief (HSMC) PMECC Error Location SIGMA 18 Register */
  #define REG_HSMC_SIGMA19    (*(__IO uint32_t*)0xFC05C574U) /**< \brief (HSMC) PMECC Error Location SIGMA 19 Register */
  #define REG_HSMC_SIGMA20    (*(__IO uint32_t*)0xFC05C578U) /**< \brief (HSMC) PMECC Error Location SIGMA 20 Register */
  #define REG_HSMC_SIGMA21    (*(__IO uint32_t*)0xFC05C57CU) /**< \brief (HSMC) PMECC Error Location SIGMA 21 Register */
  #define REG_HSMC_SIGMA22    (*(__IO uint32_t*)0xFC05C580U) /**< \brief (HSMC) PMECC Error Location SIGMA 22 Register */
  #define REG_HSMC_SIGMA23    (*(__IO uint32_t*)0xFC05C584U) /**< \brief (HSMC) PMECC Error Location SIGMA 23 Register */
  #define REG_HSMC_SIGMA24    (*(__IO uint32_t*)0xFC05C588U) /**< \brief (HSMC) PMECC Error Location SIGMA 24 Register */
  #define REG_HSMC_ERRLOC     (*(__I  uint32_t*)0xFC05C58CU) /**< \brief (HSMC) PMECC Error Location 0 Register */
  #define REG_HSMC_SETUP0     (*(__IO uint32_t*)0xFC05C600U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 0) */
  #define REG_HSMC_PULSE0     (*(__IO uint32_t*)0xFC05C604U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 0) */
  #define REG_HSMC_CYCLE0     (*(__IO uint32_t*)0xFC05C608U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 0) */
  #define REG_HSMC_TIMINGS0   (*(__IO uint32_t*)0xFC05C60CU) /**< \brief (HSMC) HSMC Timings Register (CS_number = 0) */
  #define REG_HSMC_MODE0      (*(__IO uint32_t*)0xFC05C610U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 0) */
  #define REG_HSMC_SETUP1     (*(__IO uint32_t*)0xFC05C614U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 1) */
  #define REG_HSMC_PULSE1     (*(__IO uint32_t*)0xFC05C618U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 1) */
  #define REG_HSMC_CYCLE1     (*(__IO uint32_t*)0xFC05C61CU) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 1) */
  #define REG_HSMC_TIMINGS1   (*(__IO uint32_t*)0xFC05C620U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 1) */
  #define REG_HSMC_MODE1      (*(__IO uint32_t*)0xFC05C624U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 1) */
  #define REG_HSMC_SETUP2     (*(__IO uint32_t*)0xFC05C628U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 2) */
  #define REG_HSMC_PULSE2     (*(__IO uint32_t*)0xFC05C62CU) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 2) */
  #define REG_HSMC_CYCLE2     (*(__IO uint32_t*)0xFC05C630U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 2) */
  #define REG_HSMC_TIMINGS2   (*(__IO uint32_t*)0xFC05C634U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 2) */
  #define REG_HSMC_MODE2      (*(__IO uint32_t*)0xFC05C638U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 2) */
  #define REG_HSMC_SETUP3     (*(__IO uint32_t*)0xFC05C63CU) /**< \brief (HSMC) HSMC Setup Register (CS_number = 3) */
  #define REG_HSMC_PULSE3     (*(__IO uint32_t*)0xFC05C640U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 3) */
  #define REG_HSMC_CYCLE3     (*(__IO uint32_t*)0xFC05C644U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 3) */
  #define REG_HSMC_TIMINGS3   (*(__IO uint32_t*)0xFC05C648U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 3) */
  #define REG_HSMC_MODE3      (*(__IO uint32_t*)0xFC05C64CU) /**< \brief (HSMC) HSMC Mode Register (CS_number = 3) */
  #define REG_HSMC_OCMS       (*(__IO uint32_t*)0xFC05C6A0U) /**< \brief (HSMC) HSMC OCMS Register */
  #define REG_HSMC_KEY1       (*(__O  uint32_t*)0xFC05C6A4U) /**< \brief (HSMC) HSMC OCMS KEY1 Register */
  #define REG_HSMC_KEY2       (*(__O  uint32_t*)0xFC05C6A8U) /**< \brief (HSMC) HSMC OCMS KEY2 Register */
  #define REG_HSMC_WPCR       (*(__O  uint32_t*)0xFC05C6E4U) /**< \brief (HSMC) HSMC Write Protection Control Register */
  #define REG_HSMC_WPSR       (*(__I  uint32_t*)0xFC05C6E8U) /**< \brief (HSMC) HSMC Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for SFC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SFC_KR                   (0xFC060000U) /**< \brief (SFC) SFC Key Register */
  #define REG_SFC_MR                   (0xFC060004U) /**< \brief (SFC) SFC Mode Register */
  #define REG_SFC_IER                  (0xFC060010U) /**< \brief (SFC) SFC Interrupt Enable Register */
  #define REG_SFC_IDR                  (0xFC060014U) /**< \brief (SFC) SFC Interrupt Disable Register */
  #define REG_SFC_IMR                  (0xFC060018U) /**< \brief (SFC) SFC Interrupt Mask Register */
  #define REG_SFC_SR                   (0xFC06001CU) /**< \brief (SFC) SFC Status Register */
  #define REG_SFC_DR                   (0xFC060020U) /**< \brief (SFC) SFC Data Register */
#else
  #define REG_SFC_KR  (*(__O  uint32_t*)0xFC060000U) /**< \brief (SFC) SFC Key Register */
  #define REG_SFC_MR  (*(__IO uint32_t*)0xFC060004U) /**< \brief (SFC) SFC Mode Register */
  #define REG_SFC_IER (*(__IO uint32_t*)0xFC060010U) /**< \brief (SFC) SFC Interrupt Enable Register */
  #define REG_SFC_IDR (*(__IO uint32_t*)0xFC060014U) /**< \brief (SFC) SFC Interrupt Disable Register */
  #define REG_SFC_IMR (*(__I  uint32_t*)0xFC060018U) /**< \brief (SFC) SFC Interrupt Mask Register */
  #define REG_SFC_SR  (*(__I  uint32_t*)0xFC06001CU) /**< \brief (SFC) SFC Status Register */
  #define REG_SFC_DR  (*(__IO uint32_t*)0xFC060020U) /**< \brief (SFC) SFC Data Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for PIOD peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOD_PER                      (0xFC068000U) /**< \brief (PIOD) PIO Enable Register */
  #define REG_PIOD_PDR                      (0xFC068004U) /**< \brief (PIOD) PIO Disable Register */
  #define REG_PIOD_PSR                      (0xFC068008U) /**< \brief (PIOD) PIO Status Register */
  #define REG_PIOD_ISLR                     (0xFC06800CU) /**< \brief (PIOD) PIO Interrupt Security Level Register */
  #define REG_PIOD_OER                      (0xFC068010U) /**< \brief (PIOD) Output Enable Register */
  #define REG_PIOD_ODR                      (0xFC068014U) /**< \brief (PIOD) Output Disable Register */
  #define REG_PIOD_OSR                      (0xFC068018U) /**< \brief (PIOD) Output Status Register */
  #define REG_PIOD_IFER                     (0xFC068020U) /**< \brief (PIOD) Glitch Input Filter Enable Register */
  #define REG_PIOD_IFDR                     (0xFC068024U) /**< \brief (PIOD) Glitch Input Filter Disable Register */
  #define REG_PIOD_IFSR                     (0xFC068028U) /**< \brief (PIOD) Glitch Input Filter Status Register */
  #define REG_PIOD_SODR                     (0xFC068030U) /**< \brief (PIOD) Set Output Data Register */
  #define REG_PIOD_CODR                     (0xFC068034U) /**< \brief (PIOD) Clear Output Data Register */
  #define REG_PIOD_ODSR                     (0xFC068038U) /**< \brief (PIOD) Output Data Status Register */
  #define REG_PIOD_PDSR                     (0xFC06803CU) /**< \brief (PIOD) Pin Data Status Register */
  #define REG_PIOD_IER                      (0xFC068040U) /**< \brief (PIOD) Interrupt Enable Register */
  #define REG_PIOD_IDR                      (0xFC068044U) /**< \brief (PIOD) Interrupt Disable Register */
  #define REG_PIOD_IMR                      (0xFC068048U) /**< \brief (PIOD) Interrupt Mask Register */
  #define REG_PIOD_ISR                      (0xFC06804CU) /**< \brief (PIOD) Interrupt Status Register */
  #define REG_PIOD_MDER                     (0xFC068050U) /**< \brief (PIOD) Multi-driver Enable Register */
  #define REG_PIOD_MDDR                     (0xFC068054U) /**< \brief (PIOD) Multi-driver Disable Register */
  #define REG_PIOD_MDSR                     (0xFC068058U) /**< \brief (PIOD) Multi-driver Status Register */
  #define REG_PIOD_PUDR                     (0xFC068060U) /**< \brief (PIOD) Pull-up Disable Register */
  #define REG_PIOD_PUER                     (0xFC068064U) /**< \brief (PIOD) Pull-up Enable Register */
  #define REG_PIOD_PUSR                     (0xFC068068U) /**< \brief (PIOD) Pad Pull-up Status Register */
  #define REG_PIOD_ABCDSR                   (0xFC068070U) /**< \brief (PIOD) Peripheral Select Register */
  #define REG_PIOD_IFSCDR                   (0xFC068080U) /**< \brief (PIOD) Input Filter Slow Clock Disable Register */
  #define REG_PIOD_IFSCER                   (0xFC068084U) /**< \brief (PIOD) Input Filter Slow Clock Enable Register */
  #define REG_PIOD_IFSCSR                   (0xFC068088U) /**< \brief (PIOD) Input Filter Slow Clock Status Register */
  #define REG_PIOD_SCDR                     (0xFC06808CU) /**< \brief (PIOD) Slow Clock Divider Debouncing Register */
  #define REG_PIOD_PPDDR                    (0xFC068090U) /**< \brief (PIOD) Pad Pull-down Disable Register */
  #define REG_PIOD_PPDER                    (0xFC068094U) /**< \brief (PIOD) Pad Pull-down Enable Register */
  #define REG_PIOD_PPDSR                    (0xFC068098U) /**< \brief (PIOD) Pad Pull-down Status Register */
  #define REG_PIOD_OWER                     (0xFC0680A0U) /**< \brief (PIOD) Output Write Enable */
  #define REG_PIOD_OWDR                     (0xFC0680A4U) /**< \brief (PIOD) Output Write Disable */
  #define REG_PIOD_OWSR                     (0xFC0680A8U) /**< \brief (PIOD) Output Write Status Register */
  #define REG_PIOD_AIMER                    (0xFC0680B0U) /**< \brief (PIOD) Additional Interrupt Modes Enable Register */
  #define REG_PIOD_AIMDR                    (0xFC0680B4U) /**< \brief (PIOD) Additional Interrupt Modes Disables Register */
  #define REG_PIOD_AIMMR                    (0xFC0680B8U) /**< \brief (PIOD) Additional Interrupt Modes Mask Register */
  #define REG_PIOD_ESR                      (0xFC0680C0U) /**< \brief (PIOD) Edge Select Register */
  #define REG_PIOD_LSR                      (0xFC0680C4U) /**< \brief (PIOD) Level Select Register */
  #define REG_PIOD_ELSR                     (0xFC0680C8U) /**< \brief (PIOD) Edge/Level Status Register */
  #define REG_PIOD_FELLSR                   (0xFC0680D0U) /**< \brief (PIOD) Falling Edge/Low Level Select Register */
  #define REG_PIOD_REHLSR                   (0xFC0680D4U) /**< \brief (PIOD) Rising Edge/ High Level Select Register */
  #define REG_PIOD_FRLHSR                   (0xFC0680D8U) /**< \brief (PIOD) Fall/Rise - Low/High Status Register */
  #define REG_PIOD_WPMR                     (0xFC0680E4U) /**< \brief (PIOD) Write Protect Mode Register */
  #define REG_PIOD_WPSR                     (0xFC0680E8U) /**< \brief (PIOD) Write Protect Status Register */
  #define REG_PIOD_SCHMITT                  (0xFC068100U) /**< \brief (PIOD) Schmitt Trigger Register */
  #define REG_PIOD_DRIVER1                  (0xFC068118U) /**< \brief (PIOD) I/O Drive Register 1 */
  #define REG_PIOD_DRIVER2                  (0xFC06811CU) /**< \brief (PIOD) I/O Drive Register 2 */
#else
  #define REG_PIOD_PER     (*(__O  uint32_t*)0xFC068000U) /**< \brief (PIOD) PIO Enable Register */
  #define REG_PIOD_PDR     (*(__O  uint32_t*)0xFC068004U) /**< \brief (PIOD) PIO Disable Register */
  #define REG_PIOD_PSR     (*(__I  uint32_t*)0xFC068008U) /**< \brief (PIOD) PIO Status Register */
  #define REG_PIOD_ISLR    (*(__IO uint32_t*)0xFC06800CU) /**< \brief (PIOD) PIO Interrupt Security Level Register */
  #define REG_PIOD_OER     (*(__O  uint32_t*)0xFC068010U) /**< \brief (PIOD) Output Enable Register */
  #define REG_PIOD_ODR     (*(__O  uint32_t*)0xFC068014U) /**< \brief (PIOD) Output Disable Register */
  #define REG_PIOD_OSR     (*(__I  uint32_t*)0xFC068018U) /**< \brief (PIOD) Output Status Register */
  #define REG_PIOD_IFER    (*(__O  uint32_t*)0xFC068020U) /**< \brief (PIOD) Glitch Input Filter Enable Register */
  #define REG_PIOD_IFDR    (*(__O  uint32_t*)0xFC068024U) /**< \brief (PIOD) Glitch Input Filter Disable Register */
  #define REG_PIOD_IFSR    (*(__I  uint32_t*)0xFC068028U) /**< \brief (PIOD) Glitch Input Filter Status Register */
  #define REG_PIOD_SODR    (*(__O  uint32_t*)0xFC068030U) /**< \brief (PIOD) Set Output Data Register */
  #define REG_PIOD_CODR    (*(__O  uint32_t*)0xFC068034U) /**< \brief (PIOD) Clear Output Data Register */
  #define REG_PIOD_ODSR    (*(__IO uint32_t*)0xFC068038U) /**< \brief (PIOD) Output Data Status Register */
  #define REG_PIOD_PDSR    (*(__I  uint32_t*)0xFC06803CU) /**< \brief (PIOD) Pin Data Status Register */
  #define REG_PIOD_IER     (*(__O  uint32_t*)0xFC068040U) /**< \brief (PIOD) Interrupt Enable Register */
  #define REG_PIOD_IDR     (*(__O  uint32_t*)0xFC068044U) /**< \brief (PIOD) Interrupt Disable Register */
  #define REG_PIOD_IMR     (*(__I  uint32_t*)0xFC068048U) /**< \brief (PIOD) Interrupt Mask Register */
  #define REG_PIOD_ISR     (*(__I  uint32_t*)0xFC06804CU) /**< \brief (PIOD) Interrupt Status Register */
  #define REG_PIOD_MDER    (*(__O  uint32_t*)0xFC068050U) /**< \brief (PIOD) Multi-driver Enable Register */
  #define REG_PIOD_MDDR    (*(__O  uint32_t*)0xFC068054U) /**< \brief (PIOD) Multi-driver Disable Register */
  #define REG_PIOD_MDSR    (*(__I  uint32_t*)0xFC068058U) /**< \brief (PIOD) Multi-driver Status Register */
  #define REG_PIOD_PUDR    (*(__O  uint32_t*)0xFC068060U) /**< \brief (PIOD) Pull-up Disable Register */
  #define REG_PIOD_PUER    (*(__O  uint32_t*)0xFC068064U) /**< \brief (PIOD) Pull-up Enable Register */
  #define REG_PIOD_PUSR    (*(__I  uint32_t*)0xFC068068U) /**< \brief (PIOD) Pad Pull-up Status Register */
  #define REG_PIOD_ABCDSR  (*(__IO uint32_t*)0xFC068070U) /**< \brief (PIOD) Peripheral Select Register */
  #define REG_PIOD_IFSCDR  (*(__O  uint32_t*)0xFC068080U) /**< \brief (PIOD) Input Filter Slow Clock Disable Register */
  #define REG_PIOD_IFSCER  (*(__O  uint32_t*)0xFC068084U) /**< \brief (PIOD) Input Filter Slow Clock Enable Register */
  #define REG_PIOD_IFSCSR  (*(__I  uint32_t*)0xFC068088U) /**< \brief (PIOD) Input Filter Slow Clock Status Register */
  #define REG_PIOD_SCDR    (*(__IO uint32_t*)0xFC06808CU) /**< \brief (PIOD) Slow Clock Divider Debouncing Register */
  #define REG_PIOD_PPDDR   (*(__O  uint32_t*)0xFC068090U) /**< \brief (PIOD) Pad Pull-down Disable Register */
  #define REG_PIOD_PPDER   (*(__O  uint32_t*)0xFC068094U) /**< \brief (PIOD) Pad Pull-down Enable Register */
  #define REG_PIOD_PPDSR   (*(__I  uint32_t*)0xFC068098U) /**< \brief (PIOD) Pad Pull-down Status Register */
  #define REG_PIOD_OWER    (*(__O  uint32_t*)0xFC0680A0U) /**< \brief (PIOD) Output Write Enable */
  #define REG_PIOD_OWDR    (*(__O  uint32_t*)0xFC0680A4U) /**< \brief (PIOD) Output Write Disable */
  #define REG_PIOD_OWSR    (*(__I  uint32_t*)0xFC0680A8U) /**< \brief (PIOD) Output Write Status Register */
  #define REG_PIOD_AIMER   (*(__O  uint32_t*)0xFC0680B0U) /**< \brief (PIOD) Additional Interrupt Modes Enable Register */
  #define REG_PIOD_AIMDR   (*(__O  uint32_t*)0xFC0680B4U) /**< \brief (PIOD) Additional Interrupt Modes Disables Register */
  #define REG_PIOD_AIMMR   (*(__I  uint32_t*)0xFC0680B8U) /**< \brief (PIOD) Additional Interrupt Modes Mask Register */
  #define REG_PIOD_ESR     (*(__O  uint32_t*)0xFC0680C0U) /**< \brief (PIOD) Edge Select Register */
  #define REG_PIOD_LSR     (*(__O  uint32_t*)0xFC0680C4U) /**< \brief (PIOD) Level Select Register */
  #define REG_PIOD_ELSR    (*(__I  uint32_t*)0xFC0680C8U) /**< \brief (PIOD) Edge/Level Status Register */
  #define REG_PIOD_FELLSR  (*(__O  uint32_t*)0xFC0680D0U) /**< \brief (PIOD) Falling Edge/Low Level Select Register */
  #define REG_PIOD_REHLSR  (*(__O  uint32_t*)0xFC0680D4U) /**< \brief (PIOD) Rising Edge/ High Level Select Register */
  #define REG_PIOD_FRLHSR  (*(__I  uint32_t*)0xFC0680D8U) /**< \brief (PIOD) Fall/Rise - Low/High Status Register */
  #define REG_PIOD_WPMR    (*(__IO uint32_t*)0xFC0680E4U) /**< \brief (PIOD) Write Protect Mode Register */
  #define REG_PIOD_WPSR    (*(__I  uint32_t*)0xFC0680E8U) /**< \brief (PIOD) Write Protect Status Register */
  #define REG_PIOD_SCHMITT (*(__IO uint32_t*)0xFC068100U) /**< \brief (PIOD) Schmitt Trigger Register */
  #define REG_PIOD_DRIVER1 (*(__IO uint32_t*)0xFC068118U) /**< \brief (PIOD) I/O Drive Register 1 */
  #define REG_PIOD_DRIVER2 (*(__IO uint32_t*)0xFC06811CU) /**< \brief (PIOD) I/O Drive Register 2 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Register definition for RSTC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_RSTC_CR                  (0xFC068600U) /**< \brief (RSTC) Control Register */
  #define REG_RSTC_SR                  (0xFC068604U) /**< \brief (RSTC) Status Register */
  #define REG_RSTC_MR                  (0xFC068608U) /**< \brief (RSTC) Mode Register */
#else
  #define REG_RSTC_CR (*(__O  uint32_t*)0xFC068600U) /**< \brief (RSTC) Control Register */
  #define REG_RSTC_SR (*(__I  uint32_t*)0xFC068604U) /**< \brief (RSTC) Status Register */
  #define REG_RSTC_MR (*(__IO uint32_t*)0xFC068608U) /**< \brief (RSTC) Mode Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for SHDWC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SHDWC_CR                  (0xFC068610U) /**< \brief (SHDWC) Shutdown Control Register */
  #define REG_SHDWC_MR                  (0xFC068614U) /**< \brief (SHDWC) Shutdown Mode Register */
  #define REG_SHDWC_SR                  (0xFC068618U) /**< \brief (SHDWC) Shutdown Status Register */
#else
  #define REG_SHDWC_CR (*(__O  uint32_t*)0xFC068610U) /**< \brief (SHDWC) Shutdown Control Register */
  #define REG_SHDWC_MR (*(__IO uint32_t*)0xFC068614U) /**< \brief (SHDWC) Shutdown Mode Register */
  #define REG_SHDWC_SR (*(__I  uint32_t*)0xFC068618U) /**< \brief (SHDWC) Shutdown Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for PIT peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIT_MR                    (0xFC068630U) /**< \brief (PIT) Mode Register */
  #define REG_PIT_SR                    (0xFC068634U) /**< \brief (PIT) Status Register */
  #define REG_PIT_PIVR                  (0xFC068638U) /**< \brief (PIT) Periodic Interval Value Register */
  #define REG_PIT_PIIR                  (0xFC06863CU) /**< \brief (PIT) Periodic Interval Image Register */
#else
  #define REG_PIT_MR   (*(__IO uint32_t*)0xFC068630U) /**< \brief (PIT) Mode Register */
  #define REG_PIT_SR   (*(__I  uint32_t*)0xFC068634U) /**< \brief (PIT) Status Register */
  #define REG_PIT_PIVR (*(__I  uint32_t*)0xFC068638U) /**< \brief (PIT) Periodic Interval Value Register */
  #define REG_PIT_PIIR (*(__I  uint32_t*)0xFC06863CU) /**< \brief (PIT) Periodic Interval Image Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for WDT peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_WDT_CR                  (0xFC068640U) /**< \brief (WDT) Control Register */
  #define REG_WDT_MR                  (0xFC068644U) /**< \brief (WDT) Mode Register */
  #define REG_WDT_SR                  (0xFC068648U) /**< \brief (WDT) Status Register */
#else
  #define REG_WDT_CR (*(__O  uint32_t*)0xFC068640U) /**< \brief (WDT) Control Register */
  #define REG_WDT_MR (*(__IO uint32_t*)0xFC068644U) /**< \brief (WDT) Mode Register */
  #define REG_WDT_SR (*(__I  uint32_t*)0xFC068648U) /**< \brief (WDT) Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for SCKC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SCKC_CR                  (0xFC068650U) /**< \brief (SCKC) Slow Clock Configuration Register */
#else
  #define REG_SCKC_CR (*(__IO uint32_t*)0xFC068650U) /**< \brief (SCKC) Slow Clock Configuration Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Register definition for DBGU peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_DBGU_CR                    (0xFC069000U) /**< \brief (DBGU) Control Register */
  #define REG_DBGU_MR                    (0xFC069004U) /**< \brief (DBGU) Mode Register */
  #define REG_DBGU_IER                   (0xFC069008U) /**< \brief (DBGU) Interrupt Enable Register */
  #define REG_DBGU_IDR                   (0xFC06900CU) /**< \brief (DBGU) Interrupt Disable Register */
  #define REG_DBGU_IMR                   (0xFC069010U) /**< \brief (DBGU) Interrupt Mask Register */
  #define REG_DBGU_SR                    (0xFC069014U) /**< \brief (DBGU) Status Register */
  #define REG_DBGU_RHR                   (0xFC069018U) /**< \brief (DBGU) Receive Holding Register */
  #define REG_DBGU_THR                   (0xFC06901CU) /**< \brief (DBGU) Transmit Holding Register */
  #define REG_DBGU_BRGR                  (0xFC069020U) /**< \brief (DBGU) Baud Rate Generator Register */
  #define REG_DBGU_CIDR                  (0xFC069040U) /**< \brief (DBGU) Chip ID Register */
  #define REG_DBGU_EXID                  (0xFC069044U) /**< \brief (DBGU) Chip ID Extension Register */
  #define REG_DBGU_FNR                   (0xFC069048U) /**< \brief (DBGU) Force NTRST Register */
#else
  #define REG_DBGU_CR   (*(__O  uint32_t*)0xFC069000U) /**< \brief (DBGU) Control Register */
  #define REG_DBGU_MR   (*(__IO uint32_t*)0xFC069004U) /**< \brief (DBGU) Mode Register */
  #define REG_DBGU_IER  (*(__O  uint32_t*)0xFC069008U) /**< \brief (DBGU) Interrupt Enable Register */
  #define REG_DBGU_IDR  (*(__O  uint32_t*)0xFC06900CU) /**< \brief (DBGU) Interrupt Disable Register */
  #define REG_DBGU_IMR  (*(__I  uint32_t*)0xFC069010U) /**< \brief (DBGU) Interrupt Mask Register */
  #define REG_DBGU_SR   (*(__I  uint32_t*)0xFC069014U) /**< \brief (DBGU) Status Register */
  #define REG_DBGU_RHR  (*(__I  uint32_t*)0xFC069018U) /**< \brief (DBGU) Receive Holding Register */
  #define REG_DBGU_THR  (*(__O  uint32_t*)0xFC06901CU) /**< \brief (DBGU) Transmit Holding Register */
  #define REG_DBGU_BRGR (*(__IO uint32_t*)0xFC069020U) /**< \brief (DBGU) Baud Rate Generator Register */
  #define REG_DBGU_CIDR (*(__I  uint32_t*)0xFC069040U) /**< \brief (DBGU) Chip ID Register */
  #define REG_DBGU_EXID (*(__I  uint32_t*)0xFC069044U) /**< \brief (DBGU) Chip ID Extension Register */
  #define REG_DBGU_FNR  (*(__IO uint32_t*)0xFC069048U) /**< \brief (DBGU) Force NTRST Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for PIOA peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOA_PER                      (0xFC06A000U) /**< \brief (PIOA) PIO Enable Register */
  #define REG_PIOA_PDR                      (0xFC06A004U) /**< \brief (PIOA) PIO Disable Register */
  #define REG_PIOA_PSR                      (0xFC06A008U) /**< \brief (PIOA) PIO Status Register */
  #define REG_PIOA_ISLR                     (0xFC06A00CU) /**< \brief (PIOA) PIO Interrupt Security Level Register */
  #define REG_PIOA_OER                      (0xFC06A010U) /**< \brief (PIOA) Output Enable Register */
  #define REG_PIOA_ODR                      (0xFC06A014U) /**< \brief (PIOA) Output Disable Register */
  #define REG_PIOA_OSR                      (0xFC06A018U) /**< \brief (PIOA) Output Status Register */
  #define REG_PIOA_IFER                     (0xFC06A020U) /**< \brief (PIOA) Glitch Input Filter Enable Register */
  #define REG_PIOA_IFDR                     (0xFC06A024U) /**< \brief (PIOA) Glitch Input Filter Disable Register */
  #define REG_PIOA_IFSR                     (0xFC06A028U) /**< \brief (PIOA) Glitch Input Filter Status Register */
  #define REG_PIOA_SODR                     (0xFC06A030U) /**< \brief (PIOA) Set Output Data Register */
  #define REG_PIOA_CODR                     (0xFC06A034U) /**< \brief (PIOA) Clear Output Data Register */
  #define REG_PIOA_ODSR                     (0xFC06A038U) /**< \brief (PIOA) Output Data Status Register */
  #define REG_PIOA_PDSR                     (0xFC06A03CU) /**< \brief (PIOA) Pin Data Status Register */
  #define REG_PIOA_IER                      (0xFC06A040U) /**< \brief (PIOA) Interrupt Enable Register */
  #define REG_PIOA_IDR                      (0xFC06A044U) /**< \brief (PIOA) Interrupt Disable Register */
  #define REG_PIOA_IMR                      (0xFC06A048U) /**< \brief (PIOA) Interrupt Mask Register */
  #define REG_PIOA_ISR                      (0xFC06A04CU) /**< \brief (PIOA) Interrupt Status Register */
  #define REG_PIOA_MDER                     (0xFC06A050U) /**< \brief (PIOA) Multi-driver Enable Register */
  #define REG_PIOA_MDDR                     (0xFC06A054U) /**< \brief (PIOA) Multi-driver Disable Register */
  #define REG_PIOA_MDSR                     (0xFC06A058U) /**< \brief (PIOA) Multi-driver Status Register */
  #define REG_PIOA_PUDR                     (0xFC06A060U) /**< \brief (PIOA) Pull-up Disable Register */
  #define REG_PIOA_PUER                     (0xFC06A064U) /**< \brief (PIOA) Pull-up Enable Register */
  #define REG_PIOA_PUSR                     (0xFC06A068U) /**< \brief (PIOA) Pad Pull-up Status Register */
  #define REG_PIOA_ABCDSR                   (0xFC06A070U) /**< \brief (PIOA) Peripheral Select Register */
  #define REG_PIOA_IFSCDR                   (0xFC06A080U) /**< \brief (PIOA) Input Filter Slow Clock Disable Register */
  #define REG_PIOA_IFSCER                   (0xFC06A084U) /**< \brief (PIOA) Input Filter Slow Clock Enable Register */
  #define REG_PIOA_IFSCSR                   (0xFC06A088U) /**< \brief (PIOA) Input Filter Slow Clock Status Register */
  #define REG_PIOA_SCDR                     (0xFC06A08CU) /**< \brief (PIOA) Slow Clock Divider Debouncing Register */
  #define REG_PIOA_PPDDR                    (0xFC06A090U) /**< \brief (PIOA) Pad Pull-down Disable Register */
  #define REG_PIOA_PPDER                    (0xFC06A094U) /**< \brief (PIOA) Pad Pull-down Enable Register */
  #define REG_PIOA_PPDSR                    (0xFC06A098U) /**< \brief (PIOA) Pad Pull-down Status Register */
  #define REG_PIOA_OWER                     (0xFC06A0A0U) /**< \brief (PIOA) Output Write Enable */
  #define REG_PIOA_OWDR                     (0xFC06A0A4U) /**< \brief (PIOA) Output Write Disable */
  #define REG_PIOA_OWSR                     (0xFC06A0A8U) /**< \brief (PIOA) Output Write Status Register */
  #define REG_PIOA_AIMER                    (0xFC06A0B0U) /**< \brief (PIOA) Additional Interrupt Modes Enable Register */
  #define REG_PIOA_AIMDR                    (0xFC06A0B4U) /**< \brief (PIOA) Additional Interrupt Modes Disables Register */
  #define REG_PIOA_AIMMR                    (0xFC06A0B8U) /**< \brief (PIOA) Additional Interrupt Modes Mask Register */
  #define REG_PIOA_ESR                      (0xFC06A0C0U) /**< \brief (PIOA) Edge Select Register */
  #define REG_PIOA_LSR                      (0xFC06A0C4U) /**< \brief (PIOA) Level Select Register */
  #define REG_PIOA_ELSR                     (0xFC06A0C8U) /**< \brief (PIOA) Edge/Level Status Register */
  #define REG_PIOA_FELLSR                   (0xFC06A0D0U) /**< \brief (PIOA) Falling Edge/Low Level Select Register */
  #define REG_PIOA_REHLSR                   (0xFC06A0D4U) /**< \brief (PIOA) Rising Edge/ High Level Select Register */
  #define REG_PIOA_FRLHSR                   (0xFC06A0D8U) /**< \brief (PIOA) Fall/Rise - Low/High Status Register */
  #define REG_PIOA_WPMR                     (0xFC06A0E4U) /**< \brief (PIOA) Write Protect Mode Register */
  #define REG_PIOA_WPSR                     (0xFC06A0E8U) /**< \brief (PIOA) Write Protect Status Register */
  #define REG_PIOA_SCHMITT                  (0xFC06A100U) /**< \brief (PIOA) Schmitt Trigger Register */
  #define REG_PIOA_DRIVER1                  (0xFC06A118U) /**< \brief (PIOA) I/O Drive Register 1 */
  #define REG_PIOA_DRIVER2                  (0xFC06A11CU) /**< \brief (PIOA) I/O Drive Register 2 */
#else
  #define REG_PIOA_PER     (*(__O  uint32_t*)0xFC06A000U) /**< \brief (PIOA) PIO Enable Register */
  #define REG_PIOA_PDR     (*(__O  uint32_t*)0xFC06A004U) /**< \brief (PIOA) PIO Disable Register */
  #define REG_PIOA_PSR     (*(__I  uint32_t*)0xFC06A008U) /**< \brief (PIOA) PIO Status Register */
  #define REG_PIOA_ISLR    (*(__IO uint32_t*)0xFC06A00CU) /**< \brief (PIOA) PIO Interrupt Security Level Register */
  #define REG_PIOA_OER     (*(__O  uint32_t*)0xFC06A010U) /**< \brief (PIOA) Output Enable Register */
  #define REG_PIOA_ODR     (*(__O  uint32_t*)0xFC06A014U) /**< \brief (PIOA) Output Disable Register */
  #define REG_PIOA_OSR     (*(__I  uint32_t*)0xFC06A018U) /**< \brief (PIOA) Output Status Register */
  #define REG_PIOA_IFER    (*(__O  uint32_t*)0xFC06A020U) /**< \brief (PIOA) Glitch Input Filter Enable Register */
  #define REG_PIOA_IFDR    (*(__O  uint32_t*)0xFC06A024U) /**< \brief (PIOA) Glitch Input Filter Disable Register */
  #define REG_PIOA_IFSR    (*(__I  uint32_t*)0xFC06A028U) /**< \brief (PIOA) Glitch Input Filter Status Register */
  #define REG_PIOA_SODR    (*(__O  uint32_t*)0xFC06A030U) /**< \brief (PIOA) Set Output Data Register */
  #define REG_PIOA_CODR    (*(__O  uint32_t*)0xFC06A034U) /**< \brief (PIOA) Clear Output Data Register */
  #define REG_PIOA_ODSR    (*(__IO uint32_t*)0xFC06A038U) /**< \brief (PIOA) Output Data Status Register */
  #define REG_PIOA_PDSR    (*(__I  uint32_t*)0xFC06A03CU) /**< \brief (PIOA) Pin Data Status Register */
  #define REG_PIOA_IER     (*(__O  uint32_t*)0xFC06A040U) /**< \brief (PIOA) Interrupt Enable Register */
  #define REG_PIOA_IDR     (*(__O  uint32_t*)0xFC06A044U) /**< \brief (PIOA) Interrupt Disable Register */
  #define REG_PIOA_IMR     (*(__I  uint32_t*)0xFC06A048U) /**< \brief (PIOA) Interrupt Mask Register */
  #define REG_PIOA_ISR     (*(__I  uint32_t*)0xFC06A04CU) /**< \brief (PIOA) Interrupt Status Register */
  #define REG_PIOA_MDER    (*(__O  uint32_t*)0xFC06A050U) /**< \brief (PIOA) Multi-driver Enable Register */
  #define REG_PIOA_MDDR    (*(__O  uint32_t*)0xFC06A054U) /**< \brief (PIOA) Multi-driver Disable Register */
  #define REG_PIOA_MDSR    (*(__I  uint32_t*)0xFC06A058U) /**< \brief (PIOA) Multi-driver Status Register */
  #define REG_PIOA_PUDR    (*(__O  uint32_t*)0xFC06A060U) /**< \brief (PIOA) Pull-up Disable Register */
  #define REG_PIOA_PUER    (*(__O  uint32_t*)0xFC06A064U) /**< \brief (PIOA) Pull-up Enable Register */
  #define REG_PIOA_PUSR    (*(__I  uint32_t*)0xFC06A068U) /**< \brief (PIOA) Pad Pull-up Status Register */
  #define REG_PIOA_ABCDSR  (*(__IO uint32_t*)0xFC06A070U) /**< \brief (PIOA) Peripheral Select Register */
  #define REG_PIOA_IFSCDR  (*(__O  uint32_t*)0xFC06A080U) /**< \brief (PIOA) Input Filter Slow Clock Disable Register */
  #define REG_PIOA_IFSCER  (*(__O  uint32_t*)0xFC06A084U) /**< \brief (PIOA) Input Filter Slow Clock Enable Register */
  #define REG_PIOA_IFSCSR  (*(__I  uint32_t*)0xFC06A088U) /**< \brief (PIOA) Input Filter Slow Clock Status Register */
  #define REG_PIOA_SCDR    (*(__IO uint32_t*)0xFC06A08CU) /**< \brief (PIOA) Slow Clock Divider Debouncing Register */
  #define REG_PIOA_PPDDR   (*(__O  uint32_t*)0xFC06A090U) /**< \brief (PIOA) Pad Pull-down Disable Register */
  #define REG_PIOA_PPDER   (*(__O  uint32_t*)0xFC06A094U) /**< \brief (PIOA) Pad Pull-down Enable Register */
  #define REG_PIOA_PPDSR   (*(__I  uint32_t*)0xFC06A098U) /**< \brief (PIOA) Pad Pull-down Status Register */
  #define REG_PIOA_OWER    (*(__O  uint32_t*)0xFC06A0A0U) /**< \brief (PIOA) Output Write Enable */
  #define REG_PIOA_OWDR    (*(__O  uint32_t*)0xFC06A0A4U) /**< \brief (PIOA) Output Write Disable */
  #define REG_PIOA_OWSR    (*(__I  uint32_t*)0xFC06A0A8U) /**< \brief (PIOA) Output Write Status Register */
  #define REG_PIOA_AIMER   (*(__O  uint32_t*)0xFC06A0B0U) /**< \brief (PIOA) Additional Interrupt Modes Enable Register */
  #define REG_PIOA_AIMDR   (*(__O  uint32_t*)0xFC06A0B4U) /**< \brief (PIOA) Additional Interrupt Modes Disables Register */
  #define REG_PIOA_AIMMR   (*(__I  uint32_t*)0xFC06A0B8U) /**< \brief (PIOA) Additional Interrupt Modes Mask Register */
  #define REG_PIOA_ESR     (*(__O  uint32_t*)0xFC06A0C0U) /**< \brief (PIOA) Edge Select Register */
  #define REG_PIOA_LSR     (*(__O  uint32_t*)0xFC06A0C4U) /**< \brief (PIOA) Level Select Register */
  #define REG_PIOA_ELSR    (*(__I  uint32_t*)0xFC06A0C8U) /**< \brief (PIOA) Edge/Level Status Register */
  #define REG_PIOA_FELLSR  (*(__O  uint32_t*)0xFC06A0D0U) /**< \brief (PIOA) Falling Edge/Low Level Select Register */
  #define REG_PIOA_REHLSR  (*(__O  uint32_t*)0xFC06A0D4U) /**< \brief (PIOA) Rising Edge/ High Level Select Register */
  #define REG_PIOA_FRLHSR  (*(__I  uint32_t*)0xFC06A0D8U) /**< \brief (PIOA) Fall/Rise - Low/High Status Register */
  #define REG_PIOA_WPMR    (*(__IO uint32_t*)0xFC06A0E4U) /**< \brief (PIOA) Write Protect Mode Register */
  #define REG_PIOA_WPSR    (*(__I  uint32_t*)0xFC06A0E8U) /**< \brief (PIOA) Write Protect Status Register */
  #define REG_PIOA_SCHMITT (*(__IO uint32_t*)0xFC06A100U) /**< \brief (PIOA) Schmitt Trigger Register */
  #define REG_PIOA_DRIVER1 (*(__IO uint32_t*)0xFC06A118U) /**< \brief (PIOA) I/O Drive Register 1 */
  #define REG_PIOA_DRIVER2 (*(__IO uint32_t*)0xFC06A11CU) /**< \brief (PIOA) I/O Drive Register 2 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for PIOB peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOB_PER                      (0xFC06B000U) /**< \brief (PIOB) PIO Enable Register */
  #define REG_PIOB_PDR                      (0xFC06B004U) /**< \brief (PIOB) PIO Disable Register */
  #define REG_PIOB_PSR                      (0xFC06B008U) /**< \brief (PIOB) PIO Status Register */
  #define REG_PIOB_ISLR                     (0xFC06B00CU) /**< \brief (PIOB) PIO Interrupt Security Level Register */
  #define REG_PIOB_OER                      (0xFC06B010U) /**< \brief (PIOB) Output Enable Register */
  #define REG_PIOB_ODR                      (0xFC06B014U) /**< \brief (PIOB) Output Disable Register */
  #define REG_PIOB_OSR                      (0xFC06B018U) /**< \brief (PIOB) Output Status Register */
  #define REG_PIOB_IFER                     (0xFC06B020U) /**< \brief (PIOB) Glitch Input Filter Enable Register */
  #define REG_PIOB_IFDR                     (0xFC06B024U) /**< \brief (PIOB) Glitch Input Filter Disable Register */
  #define REG_PIOB_IFSR                     (0xFC06B028U) /**< \brief (PIOB) Glitch Input Filter Status Register */
  #define REG_PIOB_SODR                     (0xFC06B030U) /**< \brief (PIOB) Set Output Data Register */
  #define REG_PIOB_CODR                     (0xFC06B034U) /**< \brief (PIOB) Clear Output Data Register */
  #define REG_PIOB_ODSR                     (0xFC06B038U) /**< \brief (PIOB) Output Data Status Register */
  #define REG_PIOB_PDSR                     (0xFC06B03CU) /**< \brief (PIOB) Pin Data Status Register */
  #define REG_PIOB_IER                      (0xFC06B040U) /**< \brief (PIOB) Interrupt Enable Register */
  #define REG_PIOB_IDR                      (0xFC06B044U) /**< \brief (PIOB) Interrupt Disable Register */
  #define REG_PIOB_IMR                      (0xFC06B048U) /**< \brief (PIOB) Interrupt Mask Register */
  #define REG_PIOB_ISR                      (0xFC06B04CU) /**< \brief (PIOB) Interrupt Status Register */
  #define REG_PIOB_MDER                     (0xFC06B050U) /**< \brief (PIOB) Multi-driver Enable Register */
  #define REG_PIOB_MDDR                     (0xFC06B054U) /**< \brief (PIOB) Multi-driver Disable Register */
  #define REG_PIOB_MDSR                     (0xFC06B058U) /**< \brief (PIOB) Multi-driver Status Register */
  #define REG_PIOB_PUDR                     (0xFC06B060U) /**< \brief (PIOB) Pull-up Disable Register */
  #define REG_PIOB_PUER                     (0xFC06B064U) /**< \brief (PIOB) Pull-up Enable Register */
  #define REG_PIOB_PUSR                     (0xFC06B068U) /**< \brief (PIOB) Pad Pull-up Status Register */
  #define REG_PIOB_ABCDSR                   (0xFC06B070U) /**< \brief (PIOB) Peripheral Select Register */
  #define REG_PIOB_IFSCDR                   (0xFC06B080U) /**< \brief (PIOB) Input Filter Slow Clock Disable Register */
  #define REG_PIOB_IFSCER                   (0xFC06B084U) /**< \brief (PIOB) Input Filter Slow Clock Enable Register */
  #define REG_PIOB_IFSCSR                   (0xFC06B088U) /**< \brief (PIOB) Input Filter Slow Clock Status Register */
  #define REG_PIOB_SCDR                     (0xFC06B08CU) /**< \brief (PIOB) Slow Clock Divider Debouncing Register */
  #define REG_PIOB_PPDDR                    (0xFC06B090U) /**< \brief (PIOB) Pad Pull-down Disable Register */
  #define REG_PIOB_PPDER                    (0xFC06B094U) /**< \brief (PIOB) Pad Pull-down Enable Register */
  #define REG_PIOB_PPDSR                    (0xFC06B098U) /**< \brief (PIOB) Pad Pull-down Status Register */
  #define REG_PIOB_OWER                     (0xFC06B0A0U) /**< \brief (PIOB) Output Write Enable */
  #define REG_PIOB_OWDR                     (0xFC06B0A4U) /**< \brief (PIOB) Output Write Disable */
  #define REG_PIOB_OWSR                     (0xFC06B0A8U) /**< \brief (PIOB) Output Write Status Register */
  #define REG_PIOB_AIMER                    (0xFC06B0B0U) /**< \brief (PIOB) Additional Interrupt Modes Enable Register */
  #define REG_PIOB_AIMDR                    (0xFC06B0B4U) /**< \brief (PIOB) Additional Interrupt Modes Disables Register */
  #define REG_PIOB_AIMMR                    (0xFC06B0B8U) /**< \brief (PIOB) Additional Interrupt Modes Mask Register */
  #define REG_PIOB_ESR                      (0xFC06B0C0U) /**< \brief (PIOB) Edge Select Register */
  #define REG_PIOB_LSR                      (0xFC06B0C4U) /**< \brief (PIOB) Level Select Register */
  #define REG_PIOB_ELSR                     (0xFC06B0C8U) /**< \brief (PIOB) Edge/Level Status Register */
  #define REG_PIOB_FELLSR                   (0xFC06B0D0U) /**< \brief (PIOB) Falling Edge/Low Level Select Register */
  #define REG_PIOB_REHLSR                   (0xFC06B0D4U) /**< \brief (PIOB) Rising Edge/ High Level Select Register */
  #define REG_PIOB_FRLHSR                   (0xFC06B0D8U) /**< \brief (PIOB) Fall/Rise - Low/High Status Register */
  #define REG_PIOB_WPMR                     (0xFC06B0E4U) /**< \brief (PIOB) Write Protect Mode Register */
  #define REG_PIOB_WPSR                     (0xFC06B0E8U) /**< \brief (PIOB) Write Protect Status Register */
  #define REG_PIOB_SCHMITT                  (0xFC06B100U) /**< \brief (PIOB) Schmitt Trigger Register */
  #define REG_PIOB_DRIVER1                  (0xFC06B118U) /**< \brief (PIOB) I/O Drive Register 1 */
  #define REG_PIOB_DRIVER2                  (0xFC06B11CU) /**< \brief (PIOB) I/O Drive Register 2 */
#else
  #define REG_PIOB_PER     (*(__O  uint32_t*)0xFC06B000U) /**< \brief (PIOB) PIO Enable Register */
  #define REG_PIOB_PDR     (*(__O  uint32_t*)0xFC06B004U) /**< \brief (PIOB) PIO Disable Register */
  #define REG_PIOB_PSR     (*(__I  uint32_t*)0xFC06B008U) /**< \brief (PIOB) PIO Status Register */
  #define REG_PIOB_ISLR    (*(__IO uint32_t*)0xFC06B00CU) /**< \brief (PIOB) PIO Interrupt Security Level Register */
  #define REG_PIOB_OER     (*(__O  uint32_t*)0xFC06B010U) /**< \brief (PIOB) Output Enable Register */
  #define REG_PIOB_ODR     (*(__O  uint32_t*)0xFC06B014U) /**< \brief (PIOB) Output Disable Register */
  #define REG_PIOB_OSR     (*(__I  uint32_t*)0xFC06B018U) /**< \brief (PIOB) Output Status Register */
  #define REG_PIOB_IFER    (*(__O  uint32_t*)0xFC06B020U) /**< \brief (PIOB) Glitch Input Filter Enable Register */
  #define REG_PIOB_IFDR    (*(__O  uint32_t*)0xFC06B024U) /**< \brief (PIOB) Glitch Input Filter Disable Register */
  #define REG_PIOB_IFSR    (*(__I  uint32_t*)0xFC06B028U) /**< \brief (PIOB) Glitch Input Filter Status Register */
  #define REG_PIOB_SODR    (*(__O  uint32_t*)0xFC06B030U) /**< \brief (PIOB) Set Output Data Register */
  #define REG_PIOB_CODR    (*(__O  uint32_t*)0xFC06B034U) /**< \brief (PIOB) Clear Output Data Register */
  #define REG_PIOB_ODSR    (*(__IO uint32_t*)0xFC06B038U) /**< \brief (PIOB) Output Data Status Register */
  #define REG_PIOB_PDSR    (*(__I  uint32_t*)0xFC06B03CU) /**< \brief (PIOB) Pin Data Status Register */
  #define REG_PIOB_IER     (*(__O  uint32_t*)0xFC06B040U) /**< \brief (PIOB) Interrupt Enable Register */
  #define REG_PIOB_IDR     (*(__O  uint32_t*)0xFC06B044U) /**< \brief (PIOB) Interrupt Disable Register */
  #define REG_PIOB_IMR     (*(__I  uint32_t*)0xFC06B048U) /**< \brief (PIOB) Interrupt Mask Register */
  #define REG_PIOB_ISR     (*(__I  uint32_t*)0xFC06B04CU) /**< \brief (PIOB) Interrupt Status Register */
  #define REG_PIOB_MDER    (*(__O  uint32_t*)0xFC06B050U) /**< \brief (PIOB) Multi-driver Enable Register */
  #define REG_PIOB_MDDR    (*(__O  uint32_t*)0xFC06B054U) /**< \brief (PIOB) Multi-driver Disable Register */
  #define REG_PIOB_MDSR    (*(__I  uint32_t*)0xFC06B058U) /**< \brief (PIOB) Multi-driver Status Register */
  #define REG_PIOB_PUDR    (*(__O  uint32_t*)0xFC06B060U) /**< \brief (PIOB) Pull-up Disable Register */
  #define REG_PIOB_PUER    (*(__O  uint32_t*)0xFC06B064U) /**< \brief (PIOB) Pull-up Enable Register */
  #define REG_PIOB_PUSR    (*(__I  uint32_t*)0xFC06B068U) /**< \brief (PIOB) Pad Pull-up Status Register */
  #define REG_PIOB_ABCDSR  (*(__IO uint32_t*)0xFC06B070U) /**< \brief (PIOB) Peripheral Select Register */
  #define REG_PIOB_IFSCDR  (*(__O  uint32_t*)0xFC06B080U) /**< \brief (PIOB) Input Filter Slow Clock Disable Register */
  #define REG_PIOB_IFSCER  (*(__O  uint32_t*)0xFC06B084U) /**< \brief (PIOB) Input Filter Slow Clock Enable Register */
  #define REG_PIOB_IFSCSR  (*(__I  uint32_t*)0xFC06B088U) /**< \brief (PIOB) Input Filter Slow Clock Status Register */
  #define REG_PIOB_SCDR    (*(__IO uint32_t*)0xFC06B08CU) /**< \brief (PIOB) Slow Clock Divider Debouncing Register */
  #define REG_PIOB_PPDDR   (*(__O  uint32_t*)0xFC06B090U) /**< \brief (PIOB) Pad Pull-down Disable Register */
  #define REG_PIOB_PPDER   (*(__O  uint32_t*)0xFC06B094U) /**< \brief (PIOB) Pad Pull-down Enable Register */
  #define REG_PIOB_PPDSR   (*(__I  uint32_t*)0xFC06B098U) /**< \brief (PIOB) Pad Pull-down Status Register */
  #define REG_PIOB_OWER    (*(__O  uint32_t*)0xFC06B0A0U) /**< \brief (PIOB) Output Write Enable */
  #define REG_PIOB_OWDR    (*(__O  uint32_t*)0xFC06B0A4U) /**< \brief (PIOB) Output Write Disable */
  #define REG_PIOB_OWSR    (*(__I  uint32_t*)0xFC06B0A8U) /**< \brief (PIOB) Output Write Status Register */
  #define REG_PIOB_AIMER   (*(__O  uint32_t*)0xFC06B0B0U) /**< \brief (PIOB) Additional Interrupt Modes Enable Register */
  #define REG_PIOB_AIMDR   (*(__O  uint32_t*)0xFC06B0B4U) /**< \brief (PIOB) Additional Interrupt Modes Disables Register */
  #define REG_PIOB_AIMMR   (*(__I  uint32_t*)0xFC06B0B8U) /**< \brief (PIOB) Additional Interrupt Modes Mask Register */
  #define REG_PIOB_ESR     (*(__O  uint32_t*)0xFC06B0C0U) /**< \brief (PIOB) Edge Select Register */
  #define REG_PIOB_LSR     (*(__O  uint32_t*)0xFC06B0C4U) /**< \brief (PIOB) Level Select Register */
  #define REG_PIOB_ELSR    (*(__I  uint32_t*)0xFC06B0C8U) /**< \brief (PIOB) Edge/Level Status Register */
  #define REG_PIOB_FELLSR  (*(__O  uint32_t*)0xFC06B0D0U) /**< \brief (PIOB) Falling Edge/Low Level Select Register */
  #define REG_PIOB_REHLSR  (*(__O  uint32_t*)0xFC06B0D4U) /**< \brief (PIOB) Rising Edge/ High Level Select Register */
  #define REG_PIOB_FRLHSR  (*(__I  uint32_t*)0xFC06B0D8U) /**< \brief (PIOB) Fall/Rise - Low/High Status Register */
  #define REG_PIOB_WPMR    (*(__IO uint32_t*)0xFC06B0E4U) /**< \brief (PIOB) Write Protect Mode Register */
  #define REG_PIOB_WPSR    (*(__I  uint32_t*)0xFC06B0E8U) /**< \brief (PIOB) Write Protect Status Register */
  #define REG_PIOB_SCHMITT (*(__IO uint32_t*)0xFC06B100U) /**< \brief (PIOB) Schmitt Trigger Register */
  #define REG_PIOB_DRIVER1 (*(__IO uint32_t*)0xFC06B118U) /**< \brief (PIOB) I/O Drive Register 1 */
  #define REG_PIOB_DRIVER2 (*(__IO uint32_t*)0xFC06B11CU) /**< \brief (PIOB) I/O Drive Register 2 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for PIOC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOC_PER                      (0xFC06C000U) /**< \brief (PIOC) PIO Enable Register */
  #define REG_PIOC_PDR                      (0xFC06C004U) /**< \brief (PIOC) PIO Disable Register */
  #define REG_PIOC_PSR                      (0xFC06C008U) /**< \brief (PIOC) PIO Status Register */
  #define REG_PIOC_ISLR                     (0xFC06C00CU) /**< \brief (PIOC) PIO Interrupt Security Level Register */
  #define REG_PIOC_OER                      (0xFC06C010U) /**< \brief (PIOC) Output Enable Register */
  #define REG_PIOC_ODR                      (0xFC06C014U) /**< \brief (PIOC) Output Disable Register */
  #define REG_PIOC_OSR                      (0xFC06C018U) /**< \brief (PIOC) Output Status Register */
  #define REG_PIOC_IFER                     (0xFC06C020U) /**< \brief (PIOC) Glitch Input Filter Enable Register */
  #define REG_PIOC_IFDR                     (0xFC06C024U) /**< \brief (PIOC) Glitch Input Filter Disable Register */
  #define REG_PIOC_IFSR                     (0xFC06C028U) /**< \brief (PIOC) Glitch Input Filter Status Register */
  #define REG_PIOC_SODR                     (0xFC06C030U) /**< \brief (PIOC) Set Output Data Register */
  #define REG_PIOC_CODR                     (0xFC06C034U) /**< \brief (PIOC) Clear Output Data Register */
  #define REG_PIOC_ODSR                     (0xFC06C038U) /**< \brief (PIOC) Output Data Status Register */
  #define REG_PIOC_PDSR                     (0xFC06C03CU) /**< \brief (PIOC) Pin Data Status Register */
  #define REG_PIOC_IER                      (0xFC06C040U) /**< \brief (PIOC) Interrupt Enable Register */
  #define REG_PIOC_IDR                      (0xFC06C044U) /**< \brief (PIOC) Interrupt Disable Register */
  #define REG_PIOC_IMR                      (0xFC06C048U) /**< \brief (PIOC) Interrupt Mask Register */
  #define REG_PIOC_ISR                      (0xFC06C04CU) /**< \brief (PIOC) Interrupt Status Register */
  #define REG_PIOC_MDER                     (0xFC06C050U) /**< \brief (PIOC) Multi-driver Enable Register */
  #define REG_PIOC_MDDR                     (0xFC06C054U) /**< \brief (PIOC) Multi-driver Disable Register */
  #define REG_PIOC_MDSR                     (0xFC06C058U) /**< \brief (PIOC) Multi-driver Status Register */
  #define REG_PIOC_PUDR                     (0xFC06C060U) /**< \brief (PIOC) Pull-up Disable Register */
  #define REG_PIOC_PUER                     (0xFC06C064U) /**< \brief (PIOC) Pull-up Enable Register */
  #define REG_PIOC_PUSR                     (0xFC06C068U) /**< \brief (PIOC) Pad Pull-up Status Register */
  #define REG_PIOC_ABCDSR                   (0xFC06C070U) /**< \brief (PIOC) Peripheral Select Register */
  #define REG_PIOC_IFSCDR                   (0xFC06C080U) /**< \brief (PIOC) Input Filter Slow Clock Disable Register */
  #define REG_PIOC_IFSCER                   (0xFC06C084U) /**< \brief (PIOC) Input Filter Slow Clock Enable Register */
  #define REG_PIOC_IFSCSR                   (0xFC06C088U) /**< \brief (PIOC) Input Filter Slow Clock Status Register */
  #define REG_PIOC_SCDR                     (0xFC06C08CU) /**< \brief (PIOC) Slow Clock Divider Debouncing Register */
  #define REG_PIOC_PPDDR                    (0xFC06C090U) /**< \brief (PIOC) Pad Pull-down Disable Register */
  #define REG_PIOC_PPDER                    (0xFC06C094U) /**< \brief (PIOC) Pad Pull-down Enable Register */
  #define REG_PIOC_PPDSR                    (0xFC06C098U) /**< \brief (PIOC) Pad Pull-down Status Register */
  #define REG_PIOC_OWER                     (0xFC06C0A0U) /**< \brief (PIOC) Output Write Enable */
  #define REG_PIOC_OWDR                     (0xFC06C0A4U) /**< \brief (PIOC) Output Write Disable */
  #define REG_PIOC_OWSR                     (0xFC06C0A8U) /**< \brief (PIOC) Output Write Status Register */
  #define REG_PIOC_AIMER                    (0xFC06C0B0U) /**< \brief (PIOC) Additional Interrupt Modes Enable Register */
  #define REG_PIOC_AIMDR                    (0xFC06C0B4U) /**< \brief (PIOC) Additional Interrupt Modes Disables Register */
  #define REG_PIOC_AIMMR                    (0xFC06C0B8U) /**< \brief (PIOC) Additional Interrupt Modes Mask Register */
  #define REG_PIOC_ESR                      (0xFC06C0C0U) /**< \brief (PIOC) Edge Select Register */
  #define REG_PIOC_LSR                      (0xFC06C0C4U) /**< \brief (PIOC) Level Select Register */
  #define REG_PIOC_ELSR                     (0xFC06C0C8U) /**< \brief (PIOC) Edge/Level Status Register */
  #define REG_PIOC_FELLSR                   (0xFC06C0D0U) /**< \brief (PIOC) Falling Edge/Low Level Select Register */
  #define REG_PIOC_REHLSR                   (0xFC06C0D4U) /**< \brief (PIOC) Rising Edge/ High Level Select Register */
  #define REG_PIOC_FRLHSR                   (0xFC06C0D8U) /**< \brief (PIOC) Fall/Rise - Low/High Status Register */
  #define REG_PIOC_WPMR                     (0xFC06C0E4U) /**< \brief (PIOC) Write Protect Mode Register */
  #define REG_PIOC_WPSR                     (0xFC06C0E8U) /**< \brief (PIOC) Write Protect Status Register */
  #define REG_PIOC_SCHMITT                  (0xFC06C100U) /**< \brief (PIOC) Schmitt Trigger Register */
  #define REG_PIOC_DRIVER1                  (0xFC06C118U) /**< \brief (PIOC) I/O Drive Register 1 */
  #define REG_PIOC_DRIVER2                  (0xFC06C11CU) /**< \brief (PIOC) I/O Drive Register 2 */
#else
  #define REG_PIOC_PER     (*(__O  uint32_t*)0xFC06C000U) /**< \brief (PIOC) PIO Enable Register */
  #define REG_PIOC_PDR     (*(__O  uint32_t*)0xFC06C004U) /**< \brief (PIOC) PIO Disable Register */
  #define REG_PIOC_PSR     (*(__I  uint32_t*)0xFC06C008U) /**< \brief (PIOC) PIO Status Register */
  #define REG_PIOC_ISLR    (*(__IO uint32_t*)0xFC06C00CU) /**< \brief (PIOC) PIO Interrupt Security Level Register */
  #define REG_PIOC_OER     (*(__O  uint32_t*)0xFC06C010U) /**< \brief (PIOC) Output Enable Register */
  #define REG_PIOC_ODR     (*(__O  uint32_t*)0xFC06C014U) /**< \brief (PIOC) Output Disable Register */
  #define REG_PIOC_OSR     (*(__I  uint32_t*)0xFC06C018U) /**< \brief (PIOC) Output Status Register */
  #define REG_PIOC_IFER    (*(__O  uint32_t*)0xFC06C020U) /**< \brief (PIOC) Glitch Input Filter Enable Register */
  #define REG_PIOC_IFDR    (*(__O  uint32_t*)0xFC06C024U) /**< \brief (PIOC) Glitch Input Filter Disable Register */
  #define REG_PIOC_IFSR    (*(__I  uint32_t*)0xFC06C028U) /**< \brief (PIOC) Glitch Input Filter Status Register */
  #define REG_PIOC_SODR    (*(__O  uint32_t*)0xFC06C030U) /**< \brief (PIOC) Set Output Data Register */
  #define REG_PIOC_CODR    (*(__O  uint32_t*)0xFC06C034U) /**< \brief (PIOC) Clear Output Data Register */
  #define REG_PIOC_ODSR    (*(__IO uint32_t*)0xFC06C038U) /**< \brief (PIOC) Output Data Status Register */
  #define REG_PIOC_PDSR    (*(__I  uint32_t*)0xFC06C03CU) /**< \brief (PIOC) Pin Data Status Register */
  #define REG_PIOC_IER     (*(__O  uint32_t*)0xFC06C040U) /**< \brief (PIOC) Interrupt Enable Register */
  #define REG_PIOC_IDR     (*(__O  uint32_t*)0xFC06C044U) /**< \brief (PIOC) Interrupt Disable Register */
  #define REG_PIOC_IMR     (*(__I  uint32_t*)0xFC06C048U) /**< \brief (PIOC) Interrupt Mask Register */
  #define REG_PIOC_ISR     (*(__I  uint32_t*)0xFC06C04CU) /**< \brief (PIOC) Interrupt Status Register */
  #define REG_PIOC_MDER    (*(__O  uint32_t*)0xFC06C050U) /**< \brief (PIOC) Multi-driver Enable Register */
  #define REG_PIOC_MDDR    (*(__O  uint32_t*)0xFC06C054U) /**< \brief (PIOC) Multi-driver Disable Register */
  #define REG_PIOC_MDSR    (*(__I  uint32_t*)0xFC06C058U) /**< \brief (PIOC) Multi-driver Status Register */
  #define REG_PIOC_PUDR    (*(__O  uint32_t*)0xFC06C060U) /**< \brief (PIOC) Pull-up Disable Register */
  #define REG_PIOC_PUER    (*(__O  uint32_t*)0xFC06C064U) /**< \brief (PIOC) Pull-up Enable Register */
  #define REG_PIOC_PUSR    (*(__I  uint32_t*)0xFC06C068U) /**< \brief (PIOC) Pad Pull-up Status Register */
  #define REG_PIOC_ABCDSR  (*(__IO uint32_t*)0xFC06C070U) /**< \brief (PIOC) Peripheral Select Register */
  #define REG_PIOC_IFSCDR  (*(__O  uint32_t*)0xFC06C080U) /**< \brief (PIOC) Input Filter Slow Clock Disable Register */
  #define REG_PIOC_IFSCER  (*(__O  uint32_t*)0xFC06C084U) /**< \brief (PIOC) Input Filter Slow Clock Enable Register */
  #define REG_PIOC_IFSCSR  (*(__I  uint32_t*)0xFC06C088U) /**< \brief (PIOC) Input Filter Slow Clock Status Register */
  #define REG_PIOC_SCDR    (*(__IO uint32_t*)0xFC06C08CU) /**< \brief (PIOC) Slow Clock Divider Debouncing Register */
  #define REG_PIOC_PPDDR   (*(__O  uint32_t*)0xFC06C090U) /**< \brief (PIOC) Pad Pull-down Disable Register */
  #define REG_PIOC_PPDER   (*(__O  uint32_t*)0xFC06C094U) /**< \brief (PIOC) Pad Pull-down Enable Register */
  #define REG_PIOC_PPDSR   (*(__I  uint32_t*)0xFC06C098U) /**< \brief (PIOC) Pad Pull-down Status Register */
  #define REG_PIOC_OWER    (*(__O  uint32_t*)0xFC06C0A0U) /**< \brief (PIOC) Output Write Enable */
  #define REG_PIOC_OWDR    (*(__O  uint32_t*)0xFC06C0A4U) /**< \brief (PIOC) Output Write Disable */
  #define REG_PIOC_OWSR    (*(__I  uint32_t*)0xFC06C0A8U) /**< \brief (PIOC) Output Write Status Register */
  #define REG_PIOC_AIMER   (*(__O  uint32_t*)0xFC06C0B0U) /**< \brief (PIOC) Additional Interrupt Modes Enable Register */
  #define REG_PIOC_AIMDR   (*(__O  uint32_t*)0xFC06C0B4U) /**< \brief (PIOC) Additional Interrupt Modes Disables Register */
  #define REG_PIOC_AIMMR   (*(__I  uint32_t*)0xFC06C0B8U) /**< \brief (PIOC) Additional Interrupt Modes Mask Register */
  #define REG_PIOC_ESR     (*(__O  uint32_t*)0xFC06C0C0U) /**< \brief (PIOC) Edge Select Register */
  #define REG_PIOC_LSR     (*(__O  uint32_t*)0xFC06C0C4U) /**< \brief (PIOC) Level Select Register */
  #define REG_PIOC_ELSR    (*(__I  uint32_t*)0xFC06C0C8U) /**< \brief (PIOC) Edge/Level Status Register */
  #define REG_PIOC_FELLSR  (*(__O  uint32_t*)0xFC06C0D0U) /**< \brief (PIOC) Falling Edge/Low Level Select Register */
  #define REG_PIOC_REHLSR  (*(__O  uint32_t*)0xFC06C0D4U) /**< \brief (PIOC) Rising Edge/ High Level Select Register */
  #define REG_PIOC_FRLHSR  (*(__I  uint32_t*)0xFC06C0D8U) /**< \brief (PIOC) Fall/Rise - Low/High Status Register */
  #define REG_PIOC_WPMR    (*(__IO uint32_t*)0xFC06C0E4U) /**< \brief (PIOC) Write Protect Mode Register */
  #define REG_PIOC_WPSR    (*(__I  uint32_t*)0xFC06C0E8U) /**< \brief (PIOC) Write Protect Status Register */
  #define REG_PIOC_SCHMITT (*(__IO uint32_t*)0xFC06C100U) /**< \brief (PIOC) Schmitt Trigger Register */
  #define REG_PIOC_DRIVER1 (*(__IO uint32_t*)0xFC06C118U) /**< \brief (PIOC) I/O Drive Register 1 */
  #define REG_PIOC_DRIVER2 (*(__IO uint32_t*)0xFC06C11CU) /**< \brief (PIOC) I/O Drive Register 2 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* ========== Register definition for PIOE peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOE_PER                      (0xFC06D000U) /**< \brief (PIOE) PIO Enable Register */
  #define REG_PIOE_PDR                      (0xFC06D004U) /**< \brief (PIOE) PIO Disable Register */
  #define REG_PIOE_PSR                      (0xFC06D008U) /**< \brief (PIOE) PIO Status Register */
  #define REG_PIOE_ISLR                     (0xFC06D00CU) /**< \brief (PIOE) PIO Interrupt Security Level Register */
  #define REG_PIOE_OER                      (0xFC06D010U) /**< \brief (PIOE) Output Enable Register */
  #define REG_PIOE_ODR                      (0xFC06D014U) /**< \brief (PIOE) Output Disable Register */
  #define REG_PIOE_OSR                      (0xFC06D018U) /**< \brief (PIOE) Output Status Register */
  #define REG_PIOE_IFER                     (0xFC06D020U) /**< \brief (PIOE) Glitch Input Filter Enable Register */
  #define REG_PIOE_IFDR                     (0xFC06D024U) /**< \brief (PIOE) Glitch Input Filter Disable Register */
  #define REG_PIOE_IFSR                     (0xFC06D028U) /**< \brief (PIOE) Glitch Input Filter Status Register */
  #define REG_PIOE_SODR                     (0xFC06D030U) /**< \brief (PIOE) Set Output Data Register */
  #define REG_PIOE_CODR                     (0xFC06D034U) /**< \brief (PIOE) Clear Output Data Register */
  #define REG_PIOE_ODSR                     (0xFC06D038U) /**< \brief (PIOE) Output Data Status Register */
  #define REG_PIOE_PDSR                     (0xFC06D03CU) /**< \brief (PIOE) Pin Data Status Register */
  #define REG_PIOE_IER                      (0xFC06D040U) /**< \brief (PIOE) Interrupt Enable Register */
  #define REG_PIOE_IDR                      (0xFC06D044U) /**< \brief (PIOE) Interrupt Disable Register */
  #define REG_PIOE_IMR                      (0xFC06D048U) /**< \brief (PIOE) Interrupt Mask Register */
  #define REG_PIOE_ISR                      (0xFC06D04CU) /**< \brief (PIOE) Interrupt Status Register */
  #define REG_PIOE_MDER                     (0xFC06D050U) /**< \brief (PIOE) Multi-driver Enable Register */
  #define REG_PIOE_MDDR                     (0xFC06D054U) /**< \brief (PIOE) Multi-driver Disable Register */
  #define REG_PIOE_MDSR                     (0xFC06D058U) /**< \brief (PIOE) Multi-driver Status Register */
  #define REG_PIOE_PUDR                     (0xFC06D060U) /**< \brief (PIOE) Pull-up Disable Register */
  #define REG_PIOE_PUER                     (0xFC06D064U) /**< \brief (PIOE) Pull-up Enable Register */
  #define REG_PIOE_PUSR                     (0xFC06D068U) /**< \brief (PIOE) Pad Pull-up Status Register */
  #define REG_PIOE_ABCDSR                   (0xFC06D070U) /**< \brief (PIOE) Peripheral Select Register */
  #define REG_PIOE_IFSCDR                   (0xFC06D080U) /**< \brief (PIOE) Input Filter Slow Clock Disable Register */
  #define REG_PIOE_IFSCER                   (0xFC06D084U) /**< \brief (PIOE) Input Filter Slow Clock Enable Register */
  #define REG_PIOE_IFSCSR                   (0xFC06D088U) /**< \brief (PIOE) Input Filter Slow Clock Status Register */
  #define REG_PIOE_SCDR                     (0xFC06D08CU) /**< \brief (PIOE) Slow Clock Divider Debouncing Register */
  #define REG_PIOE_PPDDR                    (0xFC06D090U) /**< \brief (PIOE) Pad Pull-down Disable Register */
  #define REG_PIOE_PPDER                    (0xFC06D094U) /**< \brief (PIOE) Pad Pull-down Enable Register */
  #define REG_PIOE_PPDSR                    (0xFC06D098U) /**< \brief (PIOE) Pad Pull-down Status Register */
  #define REG_PIOE_OWER                     (0xFC06D0A0U) /**< \brief (PIOE) Output Write Enable */
  #define REG_PIOE_OWDR                     (0xFC06D0A4U) /**< \brief (PIOE) Output Write Disable */
  #define REG_PIOE_OWSR                     (0xFC06D0A8U) /**< \brief (PIOE) Output Write Status Register */
  #define REG_PIOE_AIMER                    (0xFC06D0B0U) /**< \brief (PIOE) Additional Interrupt Modes Enable Register */
  #define REG_PIOE_AIMDR                    (0xFC06D0B4U) /**< \brief (PIOE) Additional Interrupt Modes Disables Register */
  #define REG_PIOE_AIMMR                    (0xFC06D0B8U) /**< \brief (PIOE) Additional Interrupt Modes Mask Register */
  #define REG_PIOE_ESR                      (0xFC06D0C0U) /**< \brief (PIOE) Edge Select Register */
  #define REG_PIOE_LSR                      (0xFC06D0C4U) /**< \brief (PIOE) Level Select Register */
  #define REG_PIOE_ELSR                     (0xFC06D0C8U) /**< \brief (PIOE) Edge/Level Status Register */
  #define REG_PIOE_FELLSR                   (0xFC06D0D0U) /**< \brief (PIOE) Falling Edge/Low Level Select Register */
  #define REG_PIOE_REHLSR                   (0xFC06D0D4U) /**< \brief (PIOE) Rising Edge/ High Level Select Register */
  #define REG_PIOE_FRLHSR                   (0xFC06D0D8U) /**< \brief (PIOE) Fall/Rise - Low/High Status Register */
  #define REG_PIOE_WPMR                     (0xFC06D0E4U) /**< \brief (PIOE) Write Protect Mode Register */
  #define REG_PIOE_WPSR                     (0xFC06D0E8U) /**< \brief (PIOE) Write Protect Status Register */
  #define REG_PIOE_SCHMITT                  (0xFC06D100U) /**< \brief (PIOE) Schmitt Trigger Register */
  #define REG_PIOE_DRIVER1                  (0xFC06D118U) /**< \brief (PIOE) I/O Drive Register 1 */
  #define REG_PIOE_DRIVER2                  (0xFC06D11CU) /**< \brief (PIOE) I/O Drive Register 2 */
#else
  #define REG_PIOE_PER     (*(__O  uint32_t*)0xFC06D000U) /**< \brief (PIOE) PIO Enable Register */
  #define REG_PIOE_PDR     (*(__O  uint32_t*)0xFC06D004U) /**< \brief (PIOE) PIO Disable Register */
  #define REG_PIOE_PSR     (*(__I  uint32_t*)0xFC06D008U) /**< \brief (PIOE) PIO Status Register */
  #define REG_PIOE_ISLR    (*(__IO uint32_t*)0xFC06D00CU) /**< \brief (PIOE) PIO Interrupt Security Level Register */
  #define REG_PIOE_OER     (*(__O  uint32_t*)0xFC06D010U) /**< \brief (PIOE) Output Enable Register */
  #define REG_PIOE_ODR     (*(__O  uint32_t*)0xFC06D014U) /**< \brief (PIOE) Output Disable Register */
  #define REG_PIOE_OSR     (*(__I  uint32_t*)0xFC06D018U) /**< \brief (PIOE) Output Status Register */
  #define REG_PIOE_IFER    (*(__O  uint32_t*)0xFC06D020U) /**< \brief (PIOE) Glitch Input Filter Enable Register */
  #define REG_PIOE_IFDR    (*(__O  uint32_t*)0xFC06D024U) /**< \brief (PIOE) Glitch Input Filter Disable Register */
  #define REG_PIOE_IFSR    (*(__I  uint32_t*)0xFC06D028U) /**< \brief (PIOE) Glitch Input Filter Status Register */
  #define REG_PIOE_SODR    (*(__O  uint32_t*)0xFC06D030U) /**< \brief (PIOE) Set Output Data Register */
  #define REG_PIOE_CODR    (*(__O  uint32_t*)0xFC06D034U) /**< \brief (PIOE) Clear Output Data Register */
  #define REG_PIOE_ODSR    (*(__IO uint32_t*)0xFC06D038U) /**< \brief (PIOE) Output Data Status Register */
  #define REG_PIOE_PDSR    (*(__I  uint32_t*)0xFC06D03CU) /**< \brief (PIOE) Pin Data Status Register */
  #define REG_PIOE_IER     (*(__O  uint32_t*)0xFC06D040U) /**< \brief (PIOE) Interrupt Enable Register */
  #define REG_PIOE_IDR     (*(__O  uint32_t*)0xFC06D044U) /**< \brief (PIOE) Interrupt Disable Register */
  #define REG_PIOE_IMR     (*(__I  uint32_t*)0xFC06D048U) /**< \brief (PIOE) Interrupt Mask Register */
  #define REG_PIOE_ISR     (*(__I  uint32_t*)0xFC06D04CU) /**< \brief (PIOE) Interrupt Status Register */
  #define REG_PIOE_MDER    (*(__O  uint32_t*)0xFC06D050U) /**< \brief (PIOE) Multi-driver Enable Register */
  #define REG_PIOE_MDDR    (*(__O  uint32_t*)0xFC06D054U) /**< \brief (PIOE) Multi-driver Disable Register */
  #define REG_PIOE_MDSR    (*(__I  uint32_t*)0xFC06D058U) /**< \brief (PIOE) Multi-driver Status Register */
  #define REG_PIOE_PUDR    (*(__O  uint32_t*)0xFC06D060U) /**< \brief (PIOE) Pull-up Disable Register */
  #define REG_PIOE_PUER    (*(__O  uint32_t*)0xFC06D064U) /**< \brief (PIOE) Pull-up Enable Register */
  #define REG_PIOE_PUSR    (*(__I  uint32_t*)0xFC06D068U) /**< \brief (PIOE) Pad Pull-up Status Register */
  #define REG_PIOE_ABCDSR  (*(__IO uint32_t*)0xFC06D070U) /**< \brief (PIOE) Peripheral Select Register */
  #define REG_PIOE_IFSCDR  (*(__O  uint32_t*)0xFC06D080U) /**< \brief (PIOE) Input Filter Slow Clock Disable Register */
  #define REG_PIOE_IFSCER  (*(__O  uint32_t*)0xFC06D084U) /**< \brief (PIOE) Input Filter Slow Clock Enable Register */
  #define REG_PIOE_IFSCSR  (*(__I  uint32_t*)0xFC06D088U) /**< \brief (PIOE) Input Filter Slow Clock Status Register */
  #define REG_PIOE_SCDR    (*(__IO uint32_t*)0xFC06D08CU) /**< \brief (PIOE) Slow Clock Divider Debouncing Register */
  #define REG_PIOE_PPDDR   (*(__O  uint32_t*)0xFC06D090U) /**< \brief (PIOE) Pad Pull-down Disable Register */
  #define REG_PIOE_PPDER   (*(__O  uint32_t*)0xFC06D094U) /**< \brief (PIOE) Pad Pull-down Enable Register */
  #define REG_PIOE_PPDSR   (*(__I  uint32_t*)0xFC06D098U) /**< \brief (PIOE) Pad Pull-down Status Register */
  #define REG_PIOE_OWER    (*(__O  uint32_t*)0xFC06D0A0U) /**< \brief (PIOE) Output Write Enable */
  #define REG_PIOE_OWDR    (*(__O  uint32_t*)0xFC06D0A4U) /**< \brief (PIOE) Output Write Disable */
  #define REG_PIOE_OWSR    (*(__I  uint32_t*)0xFC06D0A8U) /**< \brief (PIOE) Output Write Status Register */
  #define REG_PIOE_AIMER   (*(__O  uint32_t*)0xFC06D0B0U) /**< \brief (PIOE) Additional Interrupt Modes Enable Register */
  #define REG_PIOE_AIMDR   (*(__O  uint32_t*)0xFC06D0B4U) /**< \brief (PIOE) Additional Interrupt Modes Disables Register */
  #define REG_PIOE_AIMMR   (*(__I  uint32_t*)0xFC06D0B8U) /**< \brief (PIOE) Additional Interrupt Modes Mask Register */
  #define REG_PIOE_ESR     (*(__O  uint32_t*)0xFC06D0C0U) /**< \brief (PIOE) Edge Select Register */
  #define REG_PIOE_LSR     (*(__O  uint32_t*)0xFC06D0C4U) /**< \brief (PIOE) Level Select Register */
  #define REG_PIOE_ELSR    (*(__I  uint32_t*)0xFC06D0C8U) /**< \brief (PIOE) Edge/Level Status Register */
  #define REG_PIOE_FELLSR  (*(__O  uint32_t*)0xFC06D0D0U) /**< \brief (PIOE) Falling Edge/Low Level Select Register */
  #define REG_PIOE_REHLSR  (*(__O  uint32_t*)0xFC06D0D4U) /**< \brief (PIOE) Rising Edge/ High Level Select Register */
  #define REG_PIOE_FRLHSR  (*(__I  uint32_t*)0xFC06D0D8U) /**< \brief (PIOE) Fall/Rise - Low/High Status Register */
  #define REG_PIOE_WPMR    (*(__IO uint32_t*)0xFC06D0E4U) /**< \brief (PIOE) Write Protect Mode Register */
  #define REG_PIOE_WPSR    (*(__I  uint32_t*)0xFC06D0E8U) /**< \brief (PIOE) Write Protect Status Register */
  #define REG_PIOE_SCHMITT (*(__IO uint32_t*)0xFC06D100U) /**< \brief (PIOE) Schmitt Trigger Register */
  #define REG_PIOE_DRIVER1 (*(__IO uint32_t*)0xFC06D118U) /**< \brief (PIOE) I/O Drive Register 1 */
  #define REG_PIOE_DRIVER2 (*(__IO uint32_t*)0xFC06D11CU) /**< \brief (PIOE) I/O Drive Register 2 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAMA5D4 */
/* ************************************************************************** */
/** \addtogroup SAMA5D4_id Peripheral Ids Definitions */
/*@{*/

#define ID_FIQ     ( 0) /**< \brief FIQ Interrupt ID (FIQ) */
#define ID_SYS     ( 1) /**< \brief System Controller Interrupt (SYS) */
#define ID_ARM     ( 2) /**< \brief Performance Monitor Unit (ARM) */
#define ID_PIT     ( 3) /**< \brief Periodic Interval Timer Interrupt (PIT) */
#define ID_WDT     ( 4) /**< \brief Watchdog timer Interrupt (WDT) */
#define ID_PIOD    ( 5) /**< \brief Parallel I/O Controller D (PIOD) */
#define ID_USART0  ( 6) /**< \brief USART 0 (USART0) */
#define ID_USART1  ( 7) /**< \brief USART 1 (USART1) */
#define ID_XDMAC0  ( 8) /**< \brief DMA Controller 0 (XDMAC0) */
#define ID_ICM     ( 9) /**< \brief Integritry Check Monitor (ICM) */
#define ID_AES     (12) /**< \brief Advanced Encryption Standard (AES) */
#define ID_AESB    (13) /**< \brief AES bridge (AESB) */
#define ID_TDES    (14) /**< \brief Triple Data Encryption Standard (TDES) */
#define ID_SHA     (15) /**< \brief SHA Signature (SHA) */
#define ID_MPDDRC  (16) /**< \brief MPDDR controller (MPDDRC) */
#define ID_MATRIX1 (17) /**< \brief H32MX, 32-bit AHB Matrix (MATRIX1) */
#define ID_MATRIX0 (18) /**< \brief H64MX, 64-bit AHB Matrix (MATRIX0) */
#define ID_VDEC    (19) /**< \brief Video Decoder (VDEC) */
#define ID_MSADCC  (21) /**< \brief Magnetic Stripe converter Controller (MSADCC) */
#define ID_HSMC    (22) /**< \brief Multi-bit ECC Interrupt (HSMC) */
#define ID_PIOA    (23) /**< \brief Parallel I/O Controller A (PIOA) */
#define ID_PIOB    (24) /**< \brief Parallel I/O Controller B (PIOB) */
#define ID_PIOC    (25) /**< \brief Parallel I/O Controller C (PIOC) */
#define ID_PIOE    (26) /**< \brief Parallel I/O Controller E (PIOE) */
#define ID_UART0   (27) /**< \brief UART 0 (UART0) */
#define ID_UART1   (28) /**< \brief UART 1 (UART1) */
#define ID_USART2  (29) /**< \brief USART 2 (USART2) */
#define ID_USART3  (30) /**< \brief USART 3 (USART3) */
#define ID_USART4  (31) /**< \brief USART 4 (USART4) */
#define ID_TWI0    (32) /**< \brief Two-Wire Interface 0 (TWI0) */
#define ID_TWI1    (33) /**< \brief Two-Wire Interface 1 (TWI1) */
#define ID_TWI2    (34) /**< \brief Two-Wire Interface 2 (TWI2) */
#define ID_HSMCI0  (35) /**< \brief High Speed Multimedia Card Interface 0 (HSMCI0) */
#define ID_HSMCI1  (36) /**< \brief High Speed Multimedia Card Interface 1 (HSMCI1) */
#define ID_SPI0    (37) /**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SPI1    (38) /**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_SPI2    (39) /**< \brief Serial Peripheral Interface 2 (SPI2) */
#define ID_TC0     (40) /**< \brief Timer Counter 0 (ch. 0, 1, 2) (TC0) */
#define ID_TC1     (41) /**< \brief Timer Counter 1 (ch. 3, 4, 5) (TC1) */
#define ID_TC2     (42) /**< \brief Timer Counter 2 (ch. 6, 7, 8) (TC2) */
#define ID_PWM     (43) /**< \brief Pulse Width Modulation Controller (PWM) */
#define ID_ADC     (44) /**< \brief Touch Screen ADC Controller (ADC) */
#define ID_DBGU    (45) /**< \brief Debug Unit Interrupt (DBGU) */
#define ID_UHPHS   (46) /**< \brief USB Host High Speed (UHPHS) */
#define ID_UDPHS   (47) /**< \brief USB Device High Speed (UDPHS) */
#define ID_SSC0    (48) /**< \brief Synchronous Serial Controller 0 (SSC0) */
#define ID_SSC1    (49) /**< \brief Synchronous Serial Controller 1 (SSC1) */
#define ID_XDMAC1  (50) /**< \brief DMA Controller 1 (XDMAC1) */
#define ID_LCDC    (51) /**< \brief LCD Controller (LCDC) */
#define ID_ISI     (52) /**< \brief Camera Interface (ISI) */
#define ID_TRNG    (53) /**< \brief True Random Number Generator (TRNG) */
#define ID_GMAC0   (54) /**< \brief Ethernet MAC 0 (GMAC0) */
#define ID_GMAC1   (55) /**< \brief Ethernet MAC 1 (GMAC1) */
#define ID_IRQ     (56) /**< \brief IRQ Interrupt ID (IRQ) */
#define ID_SFC     (57) /**< \brief Fuse Controller (SFC) */
#define ID_SMD     (61) /**< \brief SMD Soft Modem (SMD) */
#define ID_TWI3    (62) /**< \brief Two-Wire Interface 3 (TWI3) */
#define ID_CATB    (63) /**< \brief Capacitive Touch Controller (CATB) */
#define ID_SFR     (64) /**< \brief Special Function Register  (SFR) */
#define ID_AIC     (65) /**< \brief Advanced Interrupt Controller  (AIC) */
#define ID_SAIC    (66) /**< \brief Secured Advanced Interrupt Controller  (SAIC) */
#define ID_L2CC    (67) /**< \brief L2 Cache Controller  (L2CC) */

#define ID_PERIPH_COUNT (68) /**< \brief Number of peripheral IDs */
/*@}*/

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAMA5D4 */
/* ************************************************************************** */
/** \addtogroup SAMA5D4_base Peripheral Base Address Definitions */
/*@{*/

#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define AXIMX   (0x00700000U) /**< \brief (AXIMX  ) Base Address */
#define SMD     (0x00900000U) /**< \brief (SMD    ) Base Address */
#define L2CC    (0x00A00000U) /**< \brief (L2CC   ) Base Address */
#define LCDC    (0xF0000000U) /**< \brief (LCDC   ) Base Address */
#define AESB    (0xF0002000U) /**< \brief (AESB   ) Base Address */
#define XDMAC1  (0xF0004000U) /**< \brief (XDMAC1 ) Base Address */
#define ISI     (0xF0008000U) /**< \brief (ISI    ) Base Address */
#define MPDDRC  (0xF0010000U) /**< \brief (MPDDRC ) Base Address */
#define XDMAC0  (0xF0014000U) /**< \brief (XDMAC0 ) Base Address */
#define PMC     (0xF0018000U) /**< \brief (PMC    ) Base Address */
#define MATRIX0 (0xF001C000U) /**< \brief (MATRIX0) Base Address */
#define HSMCI0  (0xF8000000U) /**< \brief (HSMCI0 ) Base Address */
#define UART0   (0xF8004000U) /**< \brief (UART0  ) Base Address */
#define SSC0    (0xF8008000U) /**< \brief (SSC0   ) Base Address */
#define PWM     (0xF800C000U) /**< \brief (PWM    ) Base Address */
#define SPI0    (0xF8010000U) /**< \brief (SPI0   ) Base Address */
#define TWI0    (0xF8014000U) /**< \brief (TWI0   ) Base Address */
#define TWI1    (0xF8018000U) /**< \brief (TWI1   ) Base Address */
#define TC0     (0xF801C000U) /**< \brief (TC0    ) Base Address */
#define GMAC0   (0xF8020000U) /**< \brief (GMAC0  ) Base Address */
#define TWI2    (0xF8024000U) /**< \brief (TWI2   ) Base Address */
#define SFR     (0xF8028000U) /**< \brief (SFR    ) Base Address */
#define USART0  (0xF802C000U) /**< \brief (USART0 ) Base Address */
#define USART1  (0xF8030000U) /**< \brief (USART1 ) Base Address */
#define CATB    (0xF803C000U) /**< \brief (CATB   ) Base Address */
#define HSMCI1  (0xFC000000U) /**< \brief (HSMCI1 ) Base Address */
#define UART1   (0xFC004000U) /**< \brief (UART1  ) Base Address */
#define USART2  (0xFC008000U) /**< \brief (USART2 ) Base Address */
#define USART3  (0xFC00C000U) /**< \brief (USART3 ) Base Address */
#define USART4  (0xFC010000U) /**< \brief (USART4 ) Base Address */
#define SSC1    (0xFC014000U) /**< \brief (SSC1   ) Base Address */
#define SPI1    (0xFC018000U) /**< \brief (SPI1   ) Base Address */
#define SPI2    (0xFC01C000U) /**< \brief (SPI2   ) Base Address */
#define TC1     (0xFC020000U) /**< \brief (TC1    ) Base Address */
#define TC2     (0xFC024000U) /**< \brief (TC2    ) Base Address */
#define GMAC1   (0xFC028000U) /**< \brief (GMAC1  ) Base Address */
#define UDPHS   (0xFC02C000U) /**< \brief (UDPHS  ) Base Address */
#define TRNG    (0xFC030000U) /**< \brief (TRNG   ) Base Address */
#define ADC     (0xFC034000U) /**< \brief (ADC    ) Base Address */
#define TWI3    (0xFC038000U) /**< \brief (TWI3   ) Base Address */
#define ICM     (0xFC040000U) /**< \brief (ICM    ) Base Address */
#define AES     (0xFC044000U) /**< \brief (AES    ) Base Address */
#define TDES    (0xFC04C000U) /**< \brief (TDES   ) Base Address */
#define SHA     (0xFC050000U) /**< \brief (SHA    ) Base Address */
#define MATRIX1 (0xFC054000U) /**< \brief (MATRIX1) Base Address */
#define HSMC    (0xFC05C000U) /**< \brief (HSMC   ) Base Address */
#define SFC     (0xFC060000U) /**< \brief (SFC    ) Base Address */
#define PIOD    (0xFC068000U) /**< \brief (PIOD   ) Base Address */
#define SAIC    (0xFC068400U) /**< \brief (SAIC   ) Base Address */
#define RSTC    (0xFC068600U) /**< \brief (RSTC   ) Base Address */
#define SHDWC   (0xFC068610U) /**< \brief (SHDWC  ) Base Address */
#define PIT     (0xFC068630U) /**< \brief (PIT    ) Base Address */
#define WDT     (0xFC068640U) /**< \brief (WDT    ) Base Address */
#define SCKC    (0xFC068650U) /**< \brief (SCKC   ) Base Address */
#define RTC     (0xFC0686B0U) /**< \brief (RTC    ) Base Address */
#define DBGU    (0xFC069000U) /**< \brief (DBGU   ) Base Address */
#define PIOA    (0xFC06A000U) /**< \brief (PIOA   ) Base Address */
#define PIOB    (0xFC06B000U) /**< \brief (PIOB   ) Base Address */
#define PIOC    (0xFC06C000U) /**< \brief (PIOC   ) Base Address */
#define PIOE    (0xFC06D000U) /**< \brief (PIOE   ) Base Address */
#define AIC     (0xFC06E000U) /**< \brief (AIC    ) Base Address */
#else
#define AXIMX   ((Aximx   *)0x00700000U) /**< \brief (AXIMX  ) Base Address */
#define SMD     ((Smd     *)0x00900000U) /**< \brief (SMD    ) Base Address */
#define L2CC    ((L2cc    *)0x00A00000U) /**< \brief (L2CC   ) Base Address */
#define LCDC    ((Lcdc    *)0xF0000000U) /**< \brief (LCDC   ) Base Address */
#define AESB    ((Aesb    *)0xF0002000U) /**< \brief (AESB   ) Base Address */
#define XDMAC1  ((Xdmac   *)0xF0004000U) /**< \brief (XDMAC1 ) Base Address */
#define ISI     ((Isi     *)0xF0008000U) /**< \brief (ISI    ) Base Address */
#define MPDDRC  ((Mpddrc  *)0xF0010000U) /**< \brief (MPDDRC ) Base Address */
#define XDMAC0  ((Xdmac   *)0xF0014000U) /**< \brief (XDMAC0 ) Base Address */
#define PMC     ((Pmc     *)0xF0018000U) /**< \brief (PMC    ) Base Address */
#define MATRIX0 ((Matrix  *)0xF001C000U) /**< \brief (MATRIX0) Base Address */
#define HSMCI0  ((Hsmci   *)0xF8000000U) /**< \brief (HSMCI0 ) Base Address */
#define UART0   ((Uart    *)0xF8004000U) /**< \brief (UART0  ) Base Address */
#define SSC0    ((Ssc     *)0xF8008000U) /**< \brief (SSC0   ) Base Address */
#define PWM     ((Pwm     *)0xF800C000U) /**< \brief (PWM    ) Base Address */
#define SPI0    ((Spi     *)0xF8010000U) /**< \brief (SPI0   ) Base Address */
#define TWI0    ((Twi     *)0xF8014000U) /**< \brief (TWI0   ) Base Address */
#define TWI1    ((Twi     *)0xF8018000U) /**< \brief (TWI1   ) Base Address */
#define TC0     ((Tc      *)0xF801C000U) /**< \brief (TC0    ) Base Address */
#define GMAC0   ((Gmac    *)0xF8020000U) /**< \brief (GMAC0  ) Base Address */
#define TWI2    ((Twi     *)0xF8024000U) /**< \brief (TWI2   ) Base Address */
#define SFR     ((Sfr     *)0xF8028000U) /**< \brief (SFR    ) Base Address */
#define USART0  ((Usart   *)0xF802C000U) /**< \brief (USART0 ) Base Address */
#define USART1  ((Usart   *)0xF8030000U) /**< \brief (USART1 ) Base Address */
#define CATB    ((Catb    *)0xF803C000U) /**< \brief (CATB   ) Base Address */
#define HSMCI1  ((Hsmci   *)0xFC000000U) /**< \brief (HSMCI1 ) Base Address */
#define UART1   ((Uart    *)0xFC004000U) /**< \brief (UART1  ) Base Address */
#define USART2  ((Usart   *)0xFC008000U) /**< \brief (USART2 ) Base Address */
#define USART3  ((Usart   *)0xFC00C000U) /**< \brief (USART3 ) Base Address */
#define USART4  ((Usart   *)0xFC010000U) /**< \brief (USART4 ) Base Address */
#define SSC1    ((Ssc     *)0xFC014000U) /**< \brief (SSC1   ) Base Address */
#define SPI1    ((Spi     *)0xFC018000U) /**< \brief (SPI1   ) Base Address */
#define SPI2    ((Spi     *)0xFC01C000U) /**< \brief (SPI2   ) Base Address */
#define TC1     ((Tc      *)0xFC020000U) /**< \brief (TC1    ) Base Address */
#define TC2     ((Tc      *)0xFC024000U) /**< \brief (TC2    ) Base Address */
#define GMAC1   ((Gmac    *)0xFC028000U) /**< \brief (GMAC1  ) Base Address */
#define UDPHS   ((Udphs   *)0xFC02C000U) /**< \brief (UDPHS  ) Base Address */
#define TRNG    ((Trng    *)0xFC030000U) /**< \brief (TRNG   ) Base Address */
#define ADC     ((Adc     *)0xFC034000U) /**< \brief (ADC    ) Base Address */
#define TWI3    ((Twi     *)0xFC038000U) /**< \brief (TWI3   ) Base Address */
#define ICM     ((Icm     *)0xFC040000U) /**< \brief (ICM    ) Base Address */
#define AES     ((Aes     *)0xFC044000U) /**< \brief (AES    ) Base Address */
#define TDES    ((Tdes    *)0xFC04C000U) /**< \brief (TDES   ) Base Address */
#define SHA     ((Sha     *)0xFC050000U) /**< \brief (SHA    ) Base Address */
#define MATRIX1 ((Matrix  *)0xFC054000U) /**< \brief (MATRIX1) Base Address */
#define HSMC    ((Hsmc    *)0xFC05C000U) /**< \brief (HSMC   ) Base Address */
#define SFC     ((Sfc     *)0xFC060000U) /**< \brief (SFC    ) Base Address */
#define PIOD    ((Pio     *)0xFC068000U) /**< \brief (PIOD   ) Base Address */
#define SAIC    ((Aic     *)0xFC068400U) /**< \brief (SAIC   ) Base Address */
#define RSTC    ((Rstc    *)0xFC068600U) /**< \brief (RSTC   ) Base Address */
#define SHDWC   ((Shdwc   *)0xFC068610U) /**< \brief (SHDWC  ) Base Address */
#define PIT     ((Pit     *)0xFC068630U) /**< \brief (PIT    ) Base Address */
#define WDT     ((Wdt     *)0xFC068640U) /**< \brief (WDT    ) Base Address */
#define SCKC    ((Sckc    *)0xFC068650U) /**< \brief (SCKC   ) Base Address */
#define RTC     ((Rtc     *)0xFC0686B0U) /**< \brief (RTC    ) Base Address */
#define DBGU    ((Dbgu    *)0xFC069000U) /**< \brief (DBGU   ) Base Address */
#define PIOA    ((Pio     *)0xFC06A000U) /**< \brief (PIOA   ) Base Address */
#define PIOB    ((Pio     *)0xFC06B000U) /**< \brief (PIOB   ) Base Address */
#define PIOC    ((Pio     *)0xFC06C000U) /**< \brief (PIOC   ) Base Address */
#define PIOE    ((Pio     *)0xFC06D000U) /**< \brief (PIOE   ) Base Address */
#define AIC     ((Aic     *)0xFC06E000U) /**< \brief (AIC    ) Base Address */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/*@}*/

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAMA5D4 */
/* ************************************************************************** */
/** \addtogroup SAMA5D4_pio Peripheral Pio Definitions */
/*@{*/

#define PIO_PA0              (1u << 0)  /**< \brief Pin Controlled by PA0 */
#define PIO_PA1              (1u << 1)  /**< \brief Pin Controlled by PA1 */
#define PIO_PA2              (1u << 2)  /**< \brief Pin Controlled by PA2 */
#define PIO_PA3              (1u << 3)  /**< \brief Pin Controlled by PA3 */
#define PIO_PA4              (1u << 4)  /**< \brief Pin Controlled by PA4 */
#define PIO_PA5              (1u << 5)  /**< \brief Pin Controlled by PA5 */
#define PIO_PA6              (1u << 6)  /**< \brief Pin Controlled by PA6 */
#define PIO_PA7              (1u << 7)  /**< \brief Pin Controlled by PA7 */
#define PIO_PA8              (1u << 8)  /**< \brief Pin Controlled by PA8 */
#define PIO_PA9              (1u << 9)  /**< \brief Pin Controlled by PA9 */
#define PIO_PA10             (1u << 10) /**< \brief Pin Controlled by PA10 */
#define PIO_PA11             (1u << 11) /**< \brief Pin Controlled by PA11 */
#define PIO_PA12             (1u << 12) /**< \brief Pin Controlled by PA12 */
#define PIO_PA13             (1u << 13) /**< \brief Pin Controlled by PA13 */
#define PIO_PA14             (1u << 14) /**< \brief Pin Controlled by PA14 */
#define PIO_PA15             (1u << 15) /**< \brief Pin Controlled by PA15 */
#define PIO_PA16             (1u << 16) /**< \brief Pin Controlled by PA16 */
#define PIO_PA17             (1u << 17) /**< \brief Pin Controlled by PA17 */
#define PIO_PA18             (1u << 18) /**< \brief Pin Controlled by PA18 */
#define PIO_PA19             (1u << 19) /**< \brief Pin Controlled by PA19 */
#define PIO_PA20             (1u << 20) /**< \brief Pin Controlled by PA20 */
#define PIO_PA21             (1u << 21) /**< \brief Pin Controlled by PA21 */
#define PIO_PA22             (1u << 22) /**< \brief Pin Controlled by PA22 */
#define PIO_PA23             (1u << 23) /**< \brief Pin Controlled by PA23 */
#define PIO_PA24             (1u << 24) /**< \brief Pin Controlled by PA24 */
#define PIO_PA25             (1u << 25) /**< \brief Pin Controlled by PA25 */
#define PIO_PA26             (1u << 26) /**< \brief Pin Controlled by PA26 */
#define PIO_PA27             (1u << 27) /**< \brief Pin Controlled by PA27 */
#define PIO_PA28             (1u << 28) /**< \brief Pin Controlled by PA28 */
#define PIO_PA29             (1u << 29) /**< \brief Pin Controlled by PA29 */
#define PIO_PA30             (1u << 30) /**< \brief Pin Controlled by PA30 */
#define PIO_PA31             (1u << 31) /**< \brief Pin Controlled by PA31 */
#define PIO_PB0              (1u << 0)  /**< \brief Pin Controlled by PB0 */
#define PIO_PB1              (1u << 1)  /**< \brief Pin Controlled by PB1 */
#define PIO_PB2              (1u << 2)  /**< \brief Pin Controlled by PB2 */
#define PIO_PB3              (1u << 3)  /**< \brief Pin Controlled by PB3 */
#define PIO_PB4              (1u << 4)  /**< \brief Pin Controlled by PB4 */
#define PIO_PB5              (1u << 5)  /**< \brief Pin Controlled by PB5 */
#define PIO_PB6              (1u << 6)  /**< \brief Pin Controlled by PB6 */
#define PIO_PB7              (1u << 7)  /**< \brief Pin Controlled by PB7 */
#define PIO_PB8              (1u << 8)  /**< \brief Pin Controlled by PB8 */
#define PIO_PB9              (1u << 9)  /**< \brief Pin Controlled by PB9 */
#define PIO_PB10             (1u << 10) /**< \brief Pin Controlled by PB10 */
#define PIO_PB11             (1u << 11) /**< \brief Pin Controlled by PB11 */
#define PIO_PB12             (1u << 12) /**< \brief Pin Controlled by PB12 */
#define PIO_PB13             (1u << 13) /**< \brief Pin Controlled by PB13 */
#define PIO_PB14             (1u << 14) /**< \brief Pin Controlled by PB14 */
#define PIO_PB15             (1u << 15) /**< \brief Pin Controlled by PB15 */
#define PIO_PB16             (1u << 16) /**< \brief Pin Controlled by PB16 */
#define PIO_PB17             (1u << 17) /**< \brief Pin Controlled by PB17 */
#define PIO_PB18             (1u << 18) /**< \brief Pin Controlled by PB18 */
#define PIO_PB19             (1u << 19) /**< \brief Pin Controlled by PB19 */
#define PIO_PB20             (1u << 20) /**< \brief Pin Controlled by PB20 */
#define PIO_PB21             (1u << 21) /**< \brief Pin Controlled by PB21 */
#define PIO_PB22             (1u << 22) /**< \brief Pin Controlled by PB22 */
#define PIO_PB23             (1u << 23) /**< \brief Pin Controlled by PB23 */
#define PIO_PB24             (1u << 24) /**< \brief Pin Controlled by PB24 */
#define PIO_PB25             (1u << 25) /**< \brief Pin Controlled by PB25 */
#define PIO_PB26             (1u << 26) /**< \brief Pin Controlled by PB26 */
#define PIO_PB27             (1u << 27) /**< \brief Pin Controlled by PB27 */
#define PIO_PB28             (1u << 28) /**< \brief Pin Controlled by PB28 */
#define PIO_PB29             (1u << 29) /**< \brief Pin Controlled by PB29 */
#define PIO_PB30             (1u << 30) /**< \brief Pin Controlled by PB30 */
#define PIO_PB31             (1u << 31) /**< \brief Pin Controlled by PB31 */
#define PIO_PC0              (1u << 0)  /**< \brief Pin Controlled by PC0 */
#define PIO_PC1              (1u << 1)  /**< \brief Pin Controlled by PC1 */
#define PIO_PC2              (1u << 2)  /**< \brief Pin Controlled by PC2 */
#define PIO_PC3              (1u << 3)  /**< \brief Pin Controlled by PC3 */
#define PIO_PC4              (1u << 4)  /**< \brief Pin Controlled by PC4 */
#define PIO_PC5              (1u << 5)  /**< \brief Pin Controlled by PC5 */
#define PIO_PC6              (1u << 6)  /**< \brief Pin Controlled by PC6 */
#define PIO_PC7              (1u << 7)  /**< \brief Pin Controlled by PC7 */
#define PIO_PC8              (1u << 8)  /**< \brief Pin Controlled by PC8 */
#define PIO_PC9              (1u << 9)  /**< \brief Pin Controlled by PC9 */
#define PIO_PC10             (1u << 10) /**< \brief Pin Controlled by PC10 */
#define PIO_PC11             (1u << 11) /**< \brief Pin Controlled by PC11 */
#define PIO_PC12             (1u << 12) /**< \brief Pin Controlled by PC12 */
#define PIO_PC13             (1u << 13) /**< \brief Pin Controlled by PC13 */
#define PIO_PC14             (1u << 14) /**< \brief Pin Controlled by PC14 */
#define PIO_PC15             (1u << 15) /**< \brief Pin Controlled by PC15 */
#define PIO_PC16             (1u << 16) /**< \brief Pin Controlled by PC16 */
#define PIO_PC17             (1u << 17) /**< \brief Pin Controlled by PC17 */
#define PIO_PC18             (1u << 18) /**< \brief Pin Controlled by PC18 */
#define PIO_PC19             (1u << 19) /**< \brief Pin Controlled by PC19 */
#define PIO_PC20             (1u << 20) /**< \brief Pin Controlled by PC20 */
#define PIO_PC21             (1u << 21) /**< \brief Pin Controlled by PC21 */
#define PIO_PC22             (1u << 22) /**< \brief Pin Controlled by PC22 */
#define PIO_PC23             (1u << 23) /**< \brief Pin Controlled by PC23 */
#define PIO_PC24             (1u << 24) /**< \brief Pin Controlled by PC24 */
#define PIO_PC25             (1u << 25) /**< \brief Pin Controlled by PC25 */
#define PIO_PC26             (1u << 26) /**< \brief Pin Controlled by PC26 */
#define PIO_PC27             (1u << 27) /**< \brief Pin Controlled by PC27 */
#define PIO_PC28             (1u << 28) /**< \brief Pin Controlled by PC28 */
#define PIO_PC29             (1u << 29) /**< \brief Pin Controlled by PC29 */
#define PIO_PC30             (1u << 30) /**< \brief Pin Controlled by PC30 */
#define PIO_PC31             (1u << 31) /**< \brief Pin Controlled by PC31 */
#define PIO_PD0              (1u << 0)  /**< \brief Pin Controlled by PD0 */
#define PIO_PD1              (1u << 1)  /**< \brief Pin Controlled by PD1 */
#define PIO_PD2              (1u << 2)  /**< \brief Pin Controlled by PD2 */
#define PIO_PD3              (1u << 3)  /**< \brief Pin Controlled by PD3 */
#define PIO_PD4              (1u << 4)  /**< \brief Pin Controlled by PD4 */
#define PIO_PD5              (1u << 5)  /**< \brief Pin Controlled by PD5 */
#define PIO_PD6              (1u << 6)  /**< \brief Pin Controlled by PD6 */
#define PIO_PD7              (1u << 7)  /**< \brief Pin Controlled by PD7 */
#define PIO_PD8              (1u << 8)  /**< \brief Pin Controlled by PD8 */
#define PIO_PD9              (1u << 9)  /**< \brief Pin Controlled by PD9 */
#define PIO_PD10             (1u << 10) /**< \brief Pin Controlled by PD10 */
#define PIO_PD11             (1u << 11) /**< \brief Pin Controlled by PD11 */
#define PIO_PD12             (1u << 12) /**< \brief Pin Controlled by PD12 */
#define PIO_PD13             (1u << 13) /**< \brief Pin Controlled by PD13 */
#define PIO_PD14             (1u << 14) /**< \brief Pin Controlled by PD14 */
#define PIO_PD15             (1u << 15) /**< \brief Pin Controlled by PD15 */
#define PIO_PD16             (1u << 16) /**< \brief Pin Controlled by PD16 */
#define PIO_PD17             (1u << 17) /**< \brief Pin Controlled by PD17 */
#define PIO_PD18             (1u << 18) /**< \brief Pin Controlled by PD18 */
#define PIO_PD19             (1u << 19) /**< \brief Pin Controlled by PD19 */
#define PIO_PD20             (1u << 20) /**< \brief Pin Controlled by PD20 */
#define PIO_PD21             (1u << 21) /**< \brief Pin Controlled by PD21 */
#define PIO_PD22             (1u << 22) /**< \brief Pin Controlled by PD22 */
#define PIO_PD23             (1u << 23) /**< \brief Pin Controlled by PD23 */
#define PIO_PD24             (1u << 24) /**< \brief Pin Controlled by PD24 */
#define PIO_PD25             (1u << 25) /**< \brief Pin Controlled by PD25 */
#define PIO_PD26             (1u << 26) /**< \brief Pin Controlled by PD26 */
#define PIO_PD27             (1u << 27) /**< \brief Pin Controlled by PD27 */
#define PIO_PD28             (1u << 28) /**< \brief Pin Controlled by PD28 */
#define PIO_PD29             (1u << 29) /**< \brief Pin Controlled by PD29 */
#define PIO_PD30             (1u << 30) /**< \brief Pin Controlled by PD30 */
#define PIO_PD31             (1u << 31) /**< \brief Pin Controlled by PD31 */
#define PIO_PE0              (1u << 0)  /**< \brief Pin Controlled by PE0 */
#define PIO_PE1              (1u << 1)  /**< \brief Pin Controlled by PE1 */
#define PIO_PE2              (1u << 2)  /**< \brief Pin Controlled by PE2 */
#define PIO_PE3              (1u << 3)  /**< \brief Pin Controlled by PE3 */
#define PIO_PE4              (1u << 4)  /**< \brief Pin Controlled by PE4 */
#define PIO_PE5              (1u << 5)  /**< \brief Pin Controlled by PE5 */
#define PIO_PE6              (1u << 6)  /**< \brief Pin Controlled by PE6 */
#define PIO_PE7              (1u << 7)  /**< \brief Pin Controlled by PE7 */
#define PIO_PE8              (1u << 8)  /**< \brief Pin Controlled by PE8 */
#define PIO_PE9              (1u << 9)  /**< \brief Pin Controlled by PE9 */
#define PIO_PE10             (1u << 10) /**< \brief Pin Controlled by PE10 */
#define PIO_PE11             (1u << 11) /**< \brief Pin Controlled by PE11 */
#define PIO_PE12             (1u << 12) /**< \brief Pin Controlled by PE12 */
#define PIO_PE13             (1u << 13) /**< \brief Pin Controlled by PE13 */
#define PIO_PE14             (1u << 14) /**< \brief Pin Controlled by PE14 */
#define PIO_PE15             (1u << 15) /**< \brief Pin Controlled by PE15 */
#define PIO_PE16             (1u << 16) /**< \brief Pin Controlled by PE16 */
#define PIO_PE17             (1u << 17) /**< \brief Pin Controlled by PE17 */
#define PIO_PE18             (1u << 18) /**< \brief Pin Controlled by PE18 */
#define PIO_PE19             (1u << 19) /**< \brief Pin Controlled by PE19 */
#define PIO_PE20             (1u << 20) /**< \brief Pin Controlled by PE20 */
#define PIO_PE21             (1u << 21) /**< \brief Pin Controlled by PE21 */
#define PIO_PE22             (1u << 22) /**< \brief Pin Controlled by PE22 */
#define PIO_PE23             (1u << 23) /**< \brief Pin Controlled by PE23 */
#define PIO_PE24             (1u << 24) /**< \brief Pin Controlled by PE24 */
#define PIO_PE25             (1u << 25) /**< \brief Pin Controlled by PE25 */
#define PIO_PE26             (1u << 26) /**< \brief Pin Controlled by PE26 */
#define PIO_PE27             (1u << 27) /**< \brief Pin Controlled by PE27 */
#define PIO_PE28             (1u << 28) /**< \brief Pin Controlled by PE28 */
#define PIO_PE29             (1u << 29) /**< \brief Pin Controlled by PE29 */
#define PIO_PE30             (1u << 30) /**< \brief Pin Controlled by PE30 */
#define PIO_PE31             (1u << 31) /**< \brief Pin Controlled by PE31 */
/* ========== Pio definition for ADC peripheral ========== */
#define PIO_PC27A_AD0        (1u << 27) /**< \brief Adc signal: AD0 */
#define PIO_PC28A_AD1        (1u << 28) /**< \brief Adc signal: AD1 */
#define PIO_PC29A_AD2        (1u << 29) /**< \brief Adc signal: AD2 */
#define PIO_PC30A_AD3        (1u << 30) /**< \brief Adc signal: AD3 */
#define PIO_PC31A_AD4        (1u << 31) /**< \brief Adc signal: AD4 */
#define PIO_PE31A_ADTRG      (1u << 31) /**< \brief Adc signal: ADTRG */
/* ========== Pio definition for AIC peripheral ========== */
#define PIO_PD9A_FIQ         (1u << 9)  /**< \brief Aic signal: FIQ */
#define PIO_PE25C_IRQ        (1u << 25) /**< \brief Aic signal: IRQ */
/* ========== Pio definition for ARM peripheral ========== */
#define PIO_PA16C_NTRST      (1u << 16) /**< \brief Arm signal: NTRST */
#define PIO_PA8C_TCK         (1u << 8)  /**< \brief Arm signal: TCK */
#define PIO_PB24C_TDI        (1u << 24) /**< \brief Arm signal: TDI */
#define PIO_PB25C_TDO        (1u << 25) /**< \brief Arm signal: TDO */
#define PIO_PA0C_TMS         (1u << 0)  /**< \brief Arm signal: TMS */
/* ========== Pio definition for CATB peripheral ========== */
#define PIO_PD29B_DIS        (1u << 29) /**< \brief Catb signal: DIS */
#define PIO_PD18B_SENSE0     (1u << 18) /**< \brief Catb signal: SENSE0 */
#define PIO_PD19B_SENSE1     (1u << 19) /**< \brief Catb signal: SENSE1 */
#define PIO_PD20B_SENSE2     (1u << 20) /**< \brief Catb signal: SENSE2 */
#define PIO_PD21B_SENSE3     (1u << 21) /**< \brief Catb signal: SENSE3 */
#define PIO_PD22B_SENSE4     (1u << 22) /**< \brief Catb signal: SENSE4 */
#define PIO_PD23B_SENSE5     (1u << 23) /**< \brief Catb signal: SENSE5 */
#define PIO_PD24B_SENSE6     (1u << 24) /**< \brief Catb signal: SENSE6 */
#define PIO_PD25B_SENSE7     (1u << 25) /**< \brief Catb signal: SENSE7 */
#define PIO_PD26B_SENSE8     (1u << 26) /**< \brief Catb signal: SENSE8 */
#define PIO_PD27B_SENSE9     (1u << 27) /**< \brief Catb signal: SENSE9 */
/* ========== Pio definition for DBGU peripheral ========== */
#define PIO_PB24A_DRXD       (1u << 24) /**< \brief Dbgu signal: DRXD */
#define PIO_PB25A_DTXD       (1u << 25) /**< \brief Dbgu signal: DTXD */
/* ========== Pio definition for EBI peripheral ========== */
#define PIO_PE0A_A0          (1u << 0)  /**< \brief Ebi signal: A0/NBS0 */
#define PIO_PE0A_NBS0        (1u << 0)  /**< \brief Ebi signal: A0/NBS0 */
#define PIO_PE1A_A1          (1u << 1)  /**< \brief Ebi signal: A1 */
#define PIO_PE10A_A10        (1u << 10) /**< \brief Ebi signal: A10 */
#define PIO_PE11A_A11        (1u << 11) /**< \brief Ebi signal: A11 */
#define PIO_PE12A_A12        (1u << 12) /**< \brief Ebi signal: A12 */
#define PIO_PE13A_A13        (1u << 13) /**< \brief Ebi signal: A13 */
#define PIO_PE14A_A14        (1u << 14) /**< \brief Ebi signal: A14 */
#define PIO_PE15A_A15        (1u << 15) /**< \brief Ebi signal: A15 */
#define PIO_PE16A_A16        (1u << 16) /**< \brief Ebi signal: A16 */
#define PIO_PE17A_A17        (1u << 17) /**< \brief Ebi signal: A17 */
#define PIO_PE18A_A18        (1u << 18) /**< \brief Ebi signal: A18 */
#define PIO_PE26C_A18        (1u << 26) /**< \brief Ebi signal: A18 */
#define PIO_PE19A_A19        (1u << 19) /**< \brief Ebi signal: A19 */
#define PIO_PE28C_A19        (1u << 28) /**< \brief Ebi signal: A19 */
#define PIO_PE2A_A2          (1u << 2)  /**< \brief Ebi signal: A2 */
#define PIO_PE20A_A20        (1u << 20) /**< \brief Ebi signal: A20 */
#define PIO_PC17A_A21        (1u << 17) /**< \brief Ebi signal: A21/NANDALE */
#define PIO_PC17A_NANDALE    (1u << 17) /**< \brief Ebi signal: A21/NANDALE */
#define PIO_PC18A_A22        (1u << 18) /**< \brief Ebi signal: A22/NANDCLE */
#define PIO_PC18A_NANDCLE    (1u << 18) /**< \brief Ebi signal: A22/NANDCLE */
#define PIO_PE21A_A23        (1u << 21) /**< \brief Ebi signal: A23 */
#define PIO_PE22A_A24        (1u << 22) /**< \brief Ebi signal: A24 */
#define PIO_PE23A_A25        (1u << 23) /**< \brief Ebi signal: A25 */
#define PIO_PE3A_A3          (1u << 3)  /**< \brief Ebi signal: A3 */
#define PIO_PE4A_A4          (1u << 4)  /**< \brief Ebi signal: A4 */
#define PIO_PE5A_A5          (1u << 5)  /**< \brief Ebi signal: A5 */
#define PIO_PE6A_A6          (1u << 6)  /**< \brief Ebi signal: A6 */
#define PIO_PE7A_A7          (1u << 7)  /**< \brief Ebi signal: A7 */
#define PIO_PE8A_A8          (1u << 8)  /**< \brief Ebi signal: A8 */
#define PIO_PE9A_A9          (1u << 9)  /**< \brief Ebi signal: A9 */
#define PIO_PC5A_D0          (1u << 5)  /**< \brief Ebi signal: D0 */
#define PIO_PC6A_D1          (1u << 6)  /**< \brief Ebi signal: D1 */
#define PIO_PB20B_D10        (1u << 20) /**< \brief Ebi signal: D10 */
#define PIO_PB21B_D11        (1u << 21) /**< \brief Ebi signal: D11 */
#define PIO_PB22B_D12        (1u << 22) /**< \brief Ebi signal: D12 */
#define PIO_PB23B_D13        (1u << 23) /**< \brief Ebi signal: D13 */
#define PIO_PB24B_D14        (1u << 24) /**< \brief Ebi signal: D14 */
#define PIO_PB25B_D15        (1u << 25) /**< \brief Ebi signal: D15 */
#define PIO_PC7A_D2          (1u << 7)  /**< \brief Ebi signal: D2 */
#define PIO_PC8A_D3          (1u << 8)  /**< \brief Ebi signal: D3 */
#define PIO_PC9A_D4          (1u << 9)  /**< \brief Ebi signal: D4 */
#define PIO_PC10A_D5         (1u << 10) /**< \brief Ebi signal: D5 */
#define PIO_PC11A_D6         (1u << 11) /**< \brief Ebi signal: D6 */
#define PIO_PC12A_D7         (1u << 12) /**< \brief Ebi signal: D7 */
#define PIO_PB18B_D8         (1u << 18) /**< \brief Ebi signal: D8 */
#define PIO_PB19B_D9         (1u << 19) /**< \brief Ebi signal: D9 */
#define PIO_PC16A_NANDRDY    (1u << 16) /**< \brief Ebi signal: NANDRDY */
#define PIO_PE24A_NCS0       (1u << 24) /**< \brief Ebi signal: NCS0 */
#define PIO_PE25A_NCS1       (1u << 25) /**< \brief Ebi signal: NCS1 */
#define PIO_PE26A_NCS2       (1u << 26) /**< \brief Ebi signal: NCS2 */
#define PIO_PC15A_NCS3       (1u << 15) /**< \brief Ebi signal: NCS3 */
#define PIO_PC13A_NRD        (1u << 13) /**< \brief Ebi signal: NRD/NANDOE */
#define PIO_PC13A_NANDOE     (1u << 13) /**< \brief Ebi signal: NRD/NANDOE */
#define PIO_PE28A_NWAIT      (1u << 28) /**< \brief Ebi signal: NWAIT */
#define PIO_PC14A_NWE        (1u << 14) /**< \brief Ebi signal: NWE/NANDWE */
#define PIO_PC14A_NANDWE     (1u << 14) /**< \brief Ebi signal: NWE/NANDWE */
#define PIO_PE27A_NWR1       (1u << 27) /**< \brief Ebi signal: NWR1/NBS1 */
#define PIO_PE27A_NBS1       (1u << 27) /**< \brief Ebi signal: NWR1/NBS1 */
/* ========== Pio definition for GMAC0 peripheral ========== */
#define PIO_PB5A_G0_COL      (1u << 5)  /**< \brief Gmac0 signal: G0_COL */
#define PIO_PB4A_G0_CRS      (1u << 4)  /**< \brief Gmac0 signal: G0_CRS */
#define PIO_PB16A_G0_MDC     (1u << 16) /**< \brief Gmac0 signal: G0_MDC */
#define PIO_PB17A_G0_MDIO    (1u << 17) /**< \brief Gmac0 signal: G0_MDIO */
#define PIO_PB8A_G0_RX0      (1u << 8)  /**< \brief Gmac0 signal: G0_RX0 */
#define PIO_PB9A_G0_RX1      (1u << 9)  /**< \brief Gmac0 signal: G0_RX1 */
#define PIO_PB10A_G0_RX2     (1u << 10) /**< \brief Gmac0 signal: G0_RX2 */
#define PIO_PB11A_G0_RX3     (1u << 11) /**< \brief Gmac0 signal: G0_RX3 */
#define PIO_PB1A_G0_RXCK     (1u << 1)  /**< \brief Gmac0 signal: G0_RXCK */
#define PIO_PB6A_G0_RXDV     (1u << 6)  /**< \brief Gmac0 signal: G0_RXDV */
#define PIO_PB7A_G0_RXER     (1u << 7)  /**< \brief Gmac0 signal: G0_RXER */
#define PIO_PB12A_G0_TX0     (1u << 12) /**< \brief Gmac0 signal: G0_TX0 */
#define PIO_PB13A_G0_TX1     (1u << 13) /**< \brief Gmac0 signal: G0_TX1 */
#define PIO_PB14A_G0_TX2     (1u << 14) /**< \brief Gmac0 signal: G0_TX2 */
#define PIO_PB15A_G0_TX3     (1u << 15) /**< \brief Gmac0 signal: G0_TX3 */
#define PIO_PB0A_G0_TXCK     (1u << 0)  /**< \brief Gmac0 signal: G0_TXCK */
#define PIO_PB2A_G0_TXEN     (1u << 2)  /**< \brief Gmac0 signal: G0_TXEN */
#define PIO_PB3A_G0_TXER     (1u << 3)  /**< \brief Gmac0 signal: G0_TXER */
/* ========== Pio definition for GMAC1 peripheral ========== */
#define PIO_PA9B_G1_COL      (1u << 9)  /**< \brief Gmac1 signal: G1_COL */
#define PIO_PA6B_G1_CRS      (1u << 6)  /**< \brief Gmac1 signal: G1_CRS */
#define PIO_PA22B_G1_MDC     (1u << 22) /**< \brief Gmac1 signal: G1_MDC */
#define PIO_PA23B_G1_MDIO    (1u << 23) /**< \brief Gmac1 signal: G1_MDIO */
#define PIO_PA12B_G1_RX0     (1u << 12) /**< \brief Gmac1 signal: G1_RX0 */
#define PIO_PA13B_G1_RX1     (1u << 13) /**< \brief Gmac1 signal: G1_RX1 */
#define PIO_PA18B_G1_RX2     (1u << 18) /**< \brief Gmac1 signal: G1_RX2 */
#define PIO_PA19B_G1_RX3     (1u << 19) /**< \brief Gmac1 signal: G1_RX3 */
#define PIO_PA3B_G1_RXCK     (1u << 3)  /**< \brief Gmac1 signal: G1_RXCK */
#define PIO_PA10B_G1_RXDV    (1u << 10) /**< \brief Gmac1 signal: G1_RXDV */
#define PIO_PA11B_G1_RXER    (1u << 11) /**< \brief Gmac1 signal: G1_RXER */
#define PIO_PA14B_G1_TX0     (1u << 14) /**< \brief Gmac1 signal: G1_TX0 */
#define PIO_PA15B_G1_TX1     (1u << 15) /**< \brief Gmac1 signal: G1_TX1 */
#define PIO_PA20B_G1_TX2     (1u << 20) /**< \brief Gmac1 signal: G1_TX2 */
#define PIO_PA21B_G1_TX3     (1u << 21) /**< \brief Gmac1 signal: G1_TX3 */
#define PIO_PA2B_G1_TXCK     (1u << 2)  /**< \brief Gmac1 signal: G1_TXCK */
#define PIO_PA4B_G1_TXEN     (1u << 4)  /**< \brief Gmac1 signal: G1_TXEN */
#define PIO_PA5B_G1_TXER     (1u << 5)  /**< \brief Gmac1 signal: G1_TXER */
/* ========== Pio definition for HSMCI0 peripheral ========== */
#define PIO_PC5B_MCI0_CDA    (1u << 5)  /**< \brief Hsmci0 signal: MCI0_CDA */
#define PIO_PE0B_MCI0_CDB    (1u << 0)  /**< \brief Hsmci0 signal: MCI0_CDB */
#define PIO_PC4B_MCI0_CK     (1u << 4)  /**< \brief Hsmci0 signal: MCI0_CK */
#define PIO_PC6B_MCI0_DA0    (1u << 6)  /**< \brief Hsmci0 signal: MCI0_DA0 */
#define PIO_PC7B_MCI0_DA1    (1u << 7)  /**< \brief Hsmci0 signal: MCI0_DA1 */
#define PIO_PC8B_MCI0_DA2    (1u << 8)  /**< \brief Hsmci0 signal: MCI0_DA2 */
#define PIO_PC9B_MCI0_DA3    (1u << 9)  /**< \brief Hsmci0 signal: MCI0_DA3 */
#define PIO_PC10B_MCI0_DA4   (1u << 10) /**< \brief Hsmci0 signal: MCI0_DA4 */
#define PIO_PC11B_MCI0_DA5   (1u << 11) /**< \brief Hsmci0 signal: MCI0_DA5 */
#define PIO_PC12B_MCI0_DA6   (1u << 12) /**< \brief Hsmci0 signal: MCI0_DA6 */
#define PIO_PC13B_MCI0_DA7   (1u << 13) /**< \brief Hsmci0 signal: MCI0_DA7 */
#define PIO_PE1B_MCI0_DB0    (1u << 1)  /**< \brief Hsmci0 signal: MCI0_DB0 */
#define PIO_PE2B_MCI0_DB1    (1u << 2)  /**< \brief Hsmci0 signal: MCI0_DB1 */
#define PIO_PE3B_MCI0_DB2    (1u << 3)  /**< \brief Hsmci0 signal: MCI0_DB2 */
#define PIO_PE4B_MCI0_DB3    (1u << 4)  /**< \brief Hsmci0 signal: MCI0_DB3 */
/* ========== Pio definition for HSMCI1 peripheral ========== */
#define PIO_PE19C_MCI1_CDA   (1u << 19) /**< \brief Hsmci1 signal: MCI1_CDA */
#define PIO_PE18C_MCI1_CK    (1u << 18) /**< \brief Hsmci1 signal: MCI1_CK */
#define PIO_PE20C_MCI1_DA0   (1u << 20) /**< \brief Hsmci1 signal: MCI1_DA0 */
#define PIO_PE21C_MCI1_DA1   (1u << 21) /**< \brief Hsmci1 signal: MCI1_DA1 */
#define PIO_PE22C_MCI1_DA2   (1u << 22) /**< \brief Hsmci1 signal: MCI1_DA2 */
#define PIO_PE23C_MCI1_DA3   (1u << 23) /**< \brief Hsmci1 signal: MCI1_DA3 */
/* ========== Pio definition for ISI peripheral ========== */
#define PIO_PC19A_ISI_D0     (1u << 19) /**< \brief Isi signal: ISI_D0 */
#define PIO_PC20A_ISI_D1     (1u << 20) /**< \brief Isi signal: ISI_D1 */
#define PIO_PC2C_ISI_D10     (1u << 2)  /**< \brief Isi signal: ISI_D10 */
#define PIO_PC3C_ISI_D11     (1u << 3)  /**< \brief Isi signal: ISI_D11 */
#define PIO_PC21A_ISI_D2     (1u << 21) /**< \brief Isi signal: ISI_D2 */
#define PIO_PC22A_ISI_D3     (1u << 22) /**< \brief Isi signal: ISI_D3 */
#define PIO_PC23A_ISI_D4     (1u << 23) /**< \brief Isi signal: ISI_D4 */
#define PIO_PC24A_ISI_D5     (1u << 24) /**< \brief Isi signal: ISI_D5 */
#define PIO_PC25A_ISI_D6     (1u << 25) /**< \brief Isi signal: ISI_D6 */
#define PIO_PC26A_ISI_D7     (1u << 26) /**< \brief Isi signal: ISI_D7 */
#define PIO_PC0C_ISI_D8      (1u << 0)  /**< \brief Isi signal: ISI_D8 */
#define PIO_PC1C_ISI_D9      (1u << 1)  /**< \brief Isi signal: ISI_D9 */
#define PIO_PB4C_ISI_HSYNC   (1u << 4)  /**< \brief Isi signal: ISI_HSYNC */
#define PIO_PB1C_ISI_PCK     (1u << 1)  /**< \brief Isi signal: ISI_PCK */
#define PIO_PB3C_ISI_VSYNC   (1u << 3)  /**< \brief Isi signal: ISI_VSYNC */
/* ========== Pio definition for LCDC peripheral ========== */
#define PIO_PA0A_LCDDAT0     (1u << 0)  /**< \brief Lcdc signal: LCDDAT0 */
#define PIO_PA1A_LCDDAT1     (1u << 1)  /**< \brief Lcdc signal: LCDDAT1 */
#define PIO_PA10A_LCDDAT10   (1u << 10) /**< \brief Lcdc signal: LCDDAT10 */
#define PIO_PA11A_LCDDAT11   (1u << 11) /**< \brief Lcdc signal: LCDDAT11 */
#define PIO_PA12A_LCDDAT12   (1u << 12) /**< \brief Lcdc signal: LCDDAT12 */
#define PIO_PA13A_LCDDAT13   (1u << 13) /**< \brief Lcdc signal: LCDDAT13 */
#define PIO_PA14A_LCDDAT14   (1u << 14) /**< \brief Lcdc signal: LCDDAT14 */
#define PIO_PA15A_LCDDAT15   (1u << 15) /**< \brief Lcdc signal: LCDDAT15 */
#define PIO_PA16A_LCDDAT16   (1u << 16) /**< \brief Lcdc signal: LCDDAT16 */
#define PIO_PA17A_LCDDAT17   (1u << 17) /**< \brief Lcdc signal: LCDDAT17 */
#define PIO_PA18A_LCDDAT18   (1u << 18) /**< \brief Lcdc signal: LCDDAT18 */
#define PIO_PA19A_LCDDAT19   (1u << 19) /**< \brief Lcdc signal: LCDDAT19 */
#define PIO_PA2A_LCDDAT2     (1u << 2)  /**< \brief Lcdc signal: LCDDAT2 */
#define PIO_PA20A_LCDDAT20   (1u << 20) /**< \brief Lcdc signal: LCDDAT20 */
#define PIO_PA21A_LCDDAT21   (1u << 21) /**< \brief Lcdc signal: LCDDAT21 */
#define PIO_PA22A_LCDDAT22   (1u << 22) /**< \brief Lcdc signal: LCDDAT22 */
#define PIO_PA23A_LCDDAT23   (1u << 23) /**< \brief Lcdc signal: LCDDAT23 */
#define PIO_PA3A_LCDDAT3     (1u << 3)  /**< \brief Lcdc signal: LCDDAT3 */
#define PIO_PA4A_LCDDAT4     (1u << 4)  /**< \brief Lcdc signal: LCDDAT4 */
#define PIO_PA5A_LCDDAT5     (1u << 5)  /**< \brief Lcdc signal: LCDDAT5 */
#define PIO_PA6A_LCDDAT6     (1u << 6)  /**< \brief Lcdc signal: LCDDAT6 */
#define PIO_PA7A_LCDDAT7     (1u << 7)  /**< \brief Lcdc signal: LCDDAT7 */
#define PIO_PA8A_LCDDAT8     (1u << 8)  /**< \brief Lcdc signal: LCDDAT8 */
#define PIO_PA9A_LCDDAT9     (1u << 9)  /**< \brief Lcdc signal: LCDDAT9 */
#define PIO_PA29A_LCDDEN     (1u << 29) /**< \brief Lcdc signal: LCDDEN */
#define PIO_PA25A_LCDDISP    (1u << 25) /**< \brief Lcdc signal: LCDDISP */
#define PIO_PA27A_LCDHSYNC   (1u << 27) /**< \brief Lcdc signal: LCDHSYNC */
#define PIO_PA28A_LCDPCK     (1u << 28) /**< \brief Lcdc signal: LCDPCK */
#define PIO_PA24A_LCDPWM     (1u << 24) /**< \brief Lcdc signal: LCDPWM */
#define PIO_PA26A_LCDVSYNC   (1u << 26) /**< \brief Lcdc signal: LCDVSYNC */
/* ========== Pio definition for PMC peripheral ========== */
#define PIO_PA24B_PCK0       (1u << 24) /**< \brief Pmc signal: PCK0 */
#define PIO_PB26A_PCK0       (1u << 26) /**< \brief Pmc signal: PCK0 */
#define PIO_PD8A_PCK0        (1u << 8)  /**< \brief Pmc signal: PCK0 */
#define PIO_PC4C_PCK1        (1u << 4)  /**< \brief Pmc signal: PCK1 */
#define PIO_PC24C_PCK1       (1u << 24) /**< \brief Pmc signal: PCK1 */
#define PIO_PD31B_PCK1       (1u << 31) /**< \brief Pmc signal: PCK1 */
#define PIO_PB5C_PCK2        (1u << 5)  /**< \brief Pmc signal: PCK2 */
#define PIO_PB10B_PCK2       (1u << 10) /**< \brief Pmc signal: PCK2 */
/* ========== Pio definition for PWM peripheral ========== */
#define PIO_PC29C_PWMFI0     (1u << 29) /**< \brief Pwm signal: PWMFI0 */
#define PIO_PE7C_PWMFI1      (1u << 7)  /**< \brief Pwm signal: PWMFI1 */
#define PIO_PA26B_PWMH0      (1u << 26) /**< \brief Pwm signal: PWMH0 */
#define PIO_PB14C_PWMH0      (1u << 14) /**< \brief Pwm signal: PWMH0 */
#define PIO_PB26C_PWMH0      (1u << 26) /**< \brief Pwm signal: PWMH0 */
#define PIO_PC30C_PWMH0      (1u << 30) /**< \brief Pwm signal: PWMH0 */
#define PIO_PA28B_PWMH1      (1u << 28) /**< \brief Pwm signal: PWMH1 */
#define PIO_PB11C_PWMH1      (1u << 11) /**< \brief Pwm signal: PWMH1 */
#define PIO_PB28C_PWMH1      (1u << 28) /**< \brief Pwm signal: PWMH1 */
#define PIO_PC31C_PWMH1      (1u << 31) /**< \brief Pwm signal: PWMH1 */
#define PIO_PC0B_PWMH2       (1u << 0)  /**< \brief Pwm signal: PWMH2 */
#define PIO_PE12C_PWMH2      (1u << 12) /**< \brief Pwm signal: PWMH2 */
#define PIO_PC2B_PWMH3       (1u << 2)  /**< \brief Pwm signal: PWMH3 */
#define PIO_PE14C_PWMH3      (1u << 14) /**< \brief Pwm signal: PWMH3 */
#define PIO_PA27B_PWML0      (1u << 27) /**< \brief Pwm signal: PWML0 */
#define PIO_PB15C_PWML0      (1u << 15) /**< \brief Pwm signal: PWML0 */
#define PIO_PB27C_PWML0      (1u << 27) /**< \brief Pwm signal: PWML0 */
#define PIO_PC27C_PWML0      (1u << 27) /**< \brief Pwm signal: PWML0 */
#define PIO_PA29B_PWML1      (1u << 29) /**< \brief Pwm signal: PWML1 */
#define PIO_PB10C_PWML1      (1u << 10) /**< \brief Pwm signal: PWML1 */
#define PIO_PB29C_PWML1      (1u << 29) /**< \brief Pwm signal: PWML1 */
#define PIO_PC28C_PWML1      (1u << 28) /**< \brief Pwm signal: PWML1 */
#define PIO_PC1B_PWML2       (1u << 1)  /**< \brief Pwm signal: PWML2 */
#define PIO_PE13C_PWML2      (1u << 13) /**< \brief Pwm signal: PWML2 */
#define PIO_PC3B_PWML3       (1u << 3)  /**< \brief Pwm signal: PWML3 */
#define PIO_PE8C_PWML3       (1u << 8)  /**< \brief Pwm signal: PWML3 */
/* ========== Pio definition for SMD peripheral ========== */
#define PIO_PE30A_DIBN       (1u << 30) /**< \brief Smd signal: DIBN */
#define PIO_PE29A_DIBP       (1u << 29) /**< \brief Smd signal: DIBP */
/* ========== Pio definition for SPI0 peripheral ========== */
#define PIO_PC0A_SPI0_MISO   (1u << 0)  /**< \brief Spi0 signal: SPI0_MISO */
#define PIO_PC1A_SPI0_MOSI   (1u << 1)  /**< \brief Spi0 signal: SPI0_MOSI */
#define PIO_PC3A_SPI0_NPCS0  (1u << 3)  /**< \brief Spi0 signal: SPI0_NPCS0 */
#define PIO_PC4A_SPI0_NPCS1  (1u << 4)  /**< \brief Spi0 signal: SPI0_NPCS1 */
#define PIO_PC27B_SPI0_NPCS1 (1u << 27) /**< \brief Spi0 signal: SPI0_NPCS1 */
#define PIO_PC28B_SPI0_NPCS2 (1u << 28) /**< \brief Spi0 signal: SPI0_NPCS2 */
#define PIO_PD31A_SPI0_NPCS2 (1u << 31) /**< \brief Spi0 signal: SPI0_NPCS2 */
#define PIO_PC29B_SPI0_NPCS3 (1u << 29) /**< \brief Spi0 signal: SPI0_NPCS3 */
#define PIO_PC2A_SPI0_SPCK   (1u << 2)  /**< \brief Spi0 signal: SPI0_SPCK */
/* ========== Pio definition for SPI1 peripheral ========== */
#define PIO_PB18A_SPI1_MISO  (1u << 18) /**< \brief Spi1 signal: SPI1_MISO */
#define PIO_PB19A_SPI1_MOSI  (1u << 19) /**< \brief Spi1 signal: SPI1_MOSI */
#define PIO_PB21A_SPI1_NPCS0 (1u << 21) /**< \brief Spi1 signal: SPI1_NPCS0 */
#define PIO_PA26C_SPI1_NPCS1 (1u << 26) /**< \brief Spi1 signal: SPI1_NPCS1 */
#define PIO_PB22A_SPI1_NPCS1 (1u << 22) /**< \brief Spi1 signal: SPI1_NPCS1 */
#define PIO_PA27C_SPI1_NPCS2 (1u << 27) /**< \brief Spi1 signal: SPI1_NPCS2 */
#define PIO_PB23A_SPI1_NPCS2 (1u << 23) /**< \brief Spi1 signal: SPI1_NPCS2 */
#define PIO_PA28C_SPI1_NPCS3 (1u << 28) /**< \brief Spi1 signal: SPI1_NPCS3 */
#define PIO_PB27A_SPI1_NPCS3 (1u << 27) /**< \brief Spi1 signal: SPI1_NPCS3 */
#define PIO_PB20A_SPI1_SPCK  (1u << 20) /**< \brief Spi1 signal: SPI1_SPCK */
/* ========== Pio definition for SPI2 peripheral ========== */
#define PIO_PD11B_SPI2_MISO  (1u << 11) /**< \brief Spi2 signal: SPI2_MISO */
#define PIO_PD13B_SPI2_MOSI  (1u << 13) /**< \brief Spi2 signal: SPI2_MOSI */
#define PIO_PD17B_SPI2_NPCS0 (1u << 17) /**< \brief Spi2 signal: SPI2_NPCS0 */
#define PIO_PB14B_SPI2_NPCS1 (1u << 14) /**< \brief Spi2 signal: SPI2_NPCS1 */
#define PIO_PB15B_SPI2_NPCS2 (1u << 15) /**< \brief Spi2 signal: SPI2_NPCS2 */
#define PIO_PB28A_SPI2_NPCS3 (1u << 28) /**< \brief Spi2 signal: SPI2_NPCS3 */
#define PIO_PD15B_SPI2_SPCK  (1u << 15) /**< \brief Spi2 signal: SPI2_SPCK */
/* ========== Pio definition for SSC0 peripheral ========== */
#define PIO_PB29B_RD0        (1u << 29) /**< \brief Ssc0 signal: RD0 */
#define PIO_PB30B_RF0        (1u << 30) /**< \brief Ssc0 signal: RF0 */
#define PIO_PB26B_RK0        (1u << 26) /**< \brief Ssc0 signal: RK0 */
#define PIO_PA25B_TD0        (1u << 25) /**< \brief Ssc0 signal: TD0 */
#define PIO_PB28B_TD0        (1u << 28) /**< \brief Ssc0 signal: TD0 */
#define PIO_PB31B_TF0        (1u << 31) /**< \brief Ssc0 signal: TF0 */
#define PIO_PB27B_TK0        (1u << 27) /**< \brief Ssc0 signal: TK0 */
/* ========== Pio definition for SSC1 peripheral ========== */
#define PIO_PC23B_RD1        (1u << 23) /**< \brief Ssc1 signal: RD1 */
#define PIO_PC22B_RF1        (1u << 22) /**< \brief Ssc1 signal: RF1 */
#define PIO_PC24B_RK1        (1u << 24) /**< \brief Ssc1 signal: RK1 */
#define PIO_PC21B_TD1        (1u << 21) /**< \brief Ssc1 signal: TD1 */
#define PIO_PC20B_TF1        (1u << 20) /**< \brief Ssc1 signal: TF1 */
#define PIO_PC19B_TK1        (1u << 19) /**< \brief Ssc1 signal: TK1 */
/* ========== Pio definition for TC0 peripheral ========== */
#define PIO_PE17C_TCLK0      (1u << 17) /**< \brief Tc0 signal: TCLK0 */
#define PIO_PE14B_TCLK1      (1u << 14) /**< \brief Tc0 signal: TCLK1 */
#define PIO_PE11B_TCLK2      (1u << 11) /**< \brief Tc0 signal: TCLK2 */
#define PIO_PE15C_TIOA0      (1u << 15) /**< \brief Tc0 signal: TIOA0 */
#define PIO_PE12B_TIOA1      (1u << 12) /**< \brief Tc0 signal: TIOA1 */
#define PIO_PE9B_TIOA2       (1u << 9)  /**< \brief Tc0 signal: TIOA2 */
#define PIO_PE16C_TIOB0      (1u << 16) /**< \brief Tc0 signal: TIOB0 */
#define PIO_PE13B_TIOB1      (1u << 13) /**< \brief Tc0 signal: TIOB1 */
#define PIO_PE10B_TIOB2      (1u << 10) /**< \brief Tc0 signal: TIOB2 */
/* ========== Pio definition for TC1 peripheral ========== */
#define PIO_PE8B_TCLK3       (1u << 8)  /**< \brief Tc1 signal: TCLK3 */
#define PIO_PE23B_TCLK4      (1u << 23) /**< \brief Tc1 signal: TCLK4 */
#define PIO_PE20B_TCLK5      (1u << 20) /**< \brief Tc1 signal: TCLK5 */
#define PIO_PE6B_TIOA3       (1u << 6)  /**< \brief Tc1 signal: TIOA3 */
#define PIO_PE21B_TIOA4      (1u << 21) /**< \brief Tc1 signal: TIOA4 */
#define PIO_PE18B_TIOA5      (1u << 18) /**< \brief Tc1 signal: TIOA5 */
#define PIO_PE7B_TIOB3       (1u << 7)  /**< \brief Tc1 signal: TIOB3 */
#define PIO_PE22B_TIOB4      (1u << 22) /**< \brief Tc1 signal: TIOB4 */
#define PIO_PE19B_TIOB5      (1u << 19) /**< \brief Tc1 signal: TIOB5 */
/* ========== Pio definition for TWI0 peripheral ========== */
#define PIO_PA31A_TWCK0      (1u << 31) /**< \brief Twi0 signal: TWCK0 */
#define PIO_PA30A_TWD0       (1u << 30) /**< \brief Twi0 signal: TWD0 */
/* ========== Pio definition for TWI1 peripheral ========== */
#define PIO_PE30C_TWCK1      (1u << 30) /**< \brief Twi1 signal: TWCK1 */
#define PIO_PE29C_TWD1       (1u << 29) /**< \brief Twi1 signal: TWD1 */
/* ========== Pio definition for TWI2 peripheral ========== */
#define PIO_PB30A_TWCK2      (1u << 30) /**< \brief Twi2 signal: TWCK2 */
#define PIO_PB29A_TWD2       (1u << 29) /**< \brief Twi2 signal: TWD2 */
/* ========== Pio definition for TWI3 peripheral ========== */
#define PIO_PC26B_TWCK3      (1u << 26) /**< \brief Twi3 signal: TWCK3 */
#define PIO_PC25B_TWD3       (1u << 25) /**< \brief Twi3 signal: TWD3 */
/* ========== Pio definition for UART0 peripheral ========== */
#define PIO_PE29B_URXD0      (1u << 29) /**< \brief Uart0 signal: URXD0 */
#define PIO_PE30B_UTXD0      (1u << 30) /**< \brief Uart0 signal: UTXD0 */
/* ========== Pio definition for UART1 peripheral ========== */
#define PIO_PC25C_URXD1      (1u << 25) /**< \brief Uart1 signal: URXD1 */
#define PIO_PC26C_UTXD1      (1u << 26) /**< \brief Uart1 signal: UTXD1 */
/* ========== Pio definition for USART0 peripheral ========== */
#define PIO_PD10A_CTS0       (1u << 10) /**< \brief Usart0 signal: CTS0 */
#define PIO_PD11A_RTS0       (1u << 11) /**< \brief Usart0 signal: RTS0 */
#define PIO_PD12A_RXD0       (1u << 12) /**< \brief Usart0 signal: RXD0 */
#define PIO_PD28A_SCK0       (1u << 28) /**< \brief Usart0 signal: SCK0 */
#define PIO_PD13A_TXD0       (1u << 13) /**< \brief Usart0 signal: TXD0 */
/* ========== Pio definition for USART1 peripheral ========== */
#define PIO_PD14A_CTS1       (1u << 14) /**< \brief Usart1 signal: CTS1 */
#define PIO_PD15A_RTS1       (1u << 15) /**< \brief Usart1 signal: RTS1 */
#define PIO_PD16A_RXD1       (1u << 16) /**< \brief Usart1 signal: RXD1 */
#define PIO_PD29A_SCK1       (1u << 29) /**< \brief Usart1 signal: SCK1 */
#define PIO_PD17A_TXD1       (1u << 17) /**< \brief Usart1 signal: TXD1 */
/* ========== Pio definition for USART2 peripheral ========== */
#define PIO_PB3B_CTS2        (1u << 3)  /**< \brief Usart2 signal: CTS2 */
#define PIO_PB11B_RTS2       (1u << 11) /**< \brief Usart2 signal: RTS2 */
#define PIO_PB4B_RXD2        (1u << 4)  /**< \brief Usart2 signal: RXD2 */
#define PIO_PB1B_SCK2        (1u << 1)  /**< \brief Usart2 signal: SCK2 */
#define PIO_PB5B_TXD2        (1u << 5)  /**< \brief Usart2 signal: TXD2 */
/* ========== Pio definition for USART3 peripheral ========== */
#define PIO_PE5B_CTS3        (1u << 5)  /**< \brief Usart3 signal: CTS3 */
#define PIO_PE24B_RTS3       (1u << 24) /**< \brief Usart3 signal: RTS3 */
#define PIO_PE16B_RXD3       (1u << 16) /**< \brief Usart3 signal: RXD3 */
#define PIO_PE15B_SCK3       (1u << 15) /**< \brief Usart3 signal: SCK3 */
#define PIO_PE17B_TXD3       (1u << 17) /**< \brief Usart3 signal: TXD3 */
/* ========== Pio definition for USART4 peripheral ========== */
#define PIO_PE0C_CTS4        (1u << 0)  /**< \brief Usart4 signal: CTS4 */
#define PIO_PE28B_RTS4       (1u << 28) /**< \brief Usart4 signal: RTS4 */
#define PIO_PE26B_RXD4       (1u << 26) /**< \brief Usart4 signal: RXD4 */
#define PIO_PE25B_SCK4       (1u << 25) /**< \brief Usart4 signal: SCK4 */
#define PIO_PE27B_TXD4       (1u << 27) /**< \brief Usart4 signal: TXD4 */
/* ========== Pio indexes ========== */
#define PIO_PA0_IDX          0
#define PIO_PA1_IDX          1
#define PIO_PA2_IDX          2
#define PIO_PA3_IDX          3
#define PIO_PA4_IDX          4
#define PIO_PA5_IDX          5
#define PIO_PA6_IDX          6
#define PIO_PA7_IDX          7
#define PIO_PA8_IDX          8
#define PIO_PA9_IDX          9
#define PIO_PA10_IDX         10
#define PIO_PA11_IDX         11
#define PIO_PA12_IDX         12
#define PIO_PA13_IDX         13
#define PIO_PA14_IDX         14
#define PIO_PA15_IDX         15
#define PIO_PA16_IDX         16
#define PIO_PA17_IDX         17
#define PIO_PA18_IDX         18
#define PIO_PA19_IDX         19
#define PIO_PA20_IDX         20
#define PIO_PA21_IDX         21
#define PIO_PA22_IDX         22
#define PIO_PA23_IDX         23
#define PIO_PA24_IDX         24
#define PIO_PA25_IDX         25
#define PIO_PA26_IDX         26
#define PIO_PA27_IDX         27
#define PIO_PA28_IDX         28
#define PIO_PA29_IDX         29
#define PIO_PA30_IDX         30
#define PIO_PA31_IDX         31
#define PIO_PB0_IDX          32
#define PIO_PB1_IDX          33
#define PIO_PB2_IDX          34
#define PIO_PB3_IDX          35
#define PIO_PB4_IDX          36
#define PIO_PB5_IDX          37
#define PIO_PB6_IDX          38
#define PIO_PB7_IDX          39
#define PIO_PB8_IDX          40
#define PIO_PB9_IDX          41
#define PIO_PB10_IDX         42
#define PIO_PB11_IDX         43
#define PIO_PB12_IDX         44
#define PIO_PB13_IDX         45
#define PIO_PB14_IDX         46
#define PIO_PB15_IDX         47
#define PIO_PB16_IDX         48
#define PIO_PB17_IDX         49
#define PIO_PB18_IDX         50
#define PIO_PB19_IDX         51
#define PIO_PB20_IDX         52
#define PIO_PB21_IDX         53
#define PIO_PB22_IDX         54
#define PIO_PB23_IDX         55
#define PIO_PB24_IDX         56
#define PIO_PB25_IDX         57
#define PIO_PB26_IDX         58
#define PIO_PB27_IDX         59
#define PIO_PB28_IDX         60
#define PIO_PB29_IDX         61
#define PIO_PB30_IDX         62
#define PIO_PB31_IDX         63
#define PIO_PC0_IDX          64
#define PIO_PC1_IDX          65
#define PIO_PC2_IDX          66
#define PIO_PC3_IDX          67
#define PIO_PC4_IDX          68
#define PIO_PC5_IDX          69
#define PIO_PC6_IDX          70
#define PIO_PC7_IDX          71
#define PIO_PC8_IDX          72
#define PIO_PC9_IDX          73
#define PIO_PC10_IDX         74
#define PIO_PC11_IDX         75
#define PIO_PC12_IDX         76
#define PIO_PC13_IDX         77
#define PIO_PC14_IDX         78
#define PIO_PC15_IDX         79
#define PIO_PC16_IDX         80
#define PIO_PC17_IDX         81
#define PIO_PC18_IDX         82
#define PIO_PC19_IDX         83
#define PIO_PC20_IDX         84
#define PIO_PC21_IDX         85
#define PIO_PC22_IDX         86
#define PIO_PC23_IDX         87
#define PIO_PC24_IDX         88
#define PIO_PC25_IDX         89
#define PIO_PC26_IDX         90
#define PIO_PC27_IDX         91
#define PIO_PC28_IDX         92
#define PIO_PC29_IDX         93
#define PIO_PC30_IDX         94
#define PIO_PC31_IDX         95
#define PIO_PD0_IDX          96
#define PIO_PD1_IDX          97
#define PIO_PD2_IDX          98
#define PIO_PD3_IDX          99
#define PIO_PD4_IDX          100
#define PIO_PD5_IDX          101
#define PIO_PD6_IDX          102
#define PIO_PD7_IDX          103
#define PIO_PD8_IDX          104
#define PIO_PD9_IDX          105
#define PIO_PD10_IDX         106
#define PIO_PD11_IDX         107
#define PIO_PD12_IDX         108
#define PIO_PD13_IDX         109
#define PIO_PD14_IDX         110
#define PIO_PD15_IDX         111
#define PIO_PD16_IDX         112
#define PIO_PD17_IDX         113
#define PIO_PD18_IDX         114
#define PIO_PD19_IDX         115
#define PIO_PD20_IDX         116
#define PIO_PD21_IDX         117
#define PIO_PD22_IDX         118
#define PIO_PD23_IDX         119
#define PIO_PD24_IDX         120
#define PIO_PD25_IDX         121
#define PIO_PD26_IDX         122
#define PIO_PD27_IDX         123
#define PIO_PD28_IDX         124
#define PIO_PD29_IDX         125
#define PIO_PD30_IDX         126
#define PIO_PD31_IDX         127
#define PIO_PE0_IDX          128
#define PIO_PE1_IDX          129
#define PIO_PE2_IDX          130
#define PIO_PE3_IDX          131
#define PIO_PE4_IDX          132
#define PIO_PE5_IDX          133
#define PIO_PE6_IDX          134
#define PIO_PE7_IDX          135
#define PIO_PE8_IDX          136
#define PIO_PE9_IDX          137
#define PIO_PE10_IDX         138
#define PIO_PE11_IDX         139
#define PIO_PE12_IDX         140
#define PIO_PE13_IDX         141
#define PIO_PE14_IDX         142
#define PIO_PE15_IDX         143
#define PIO_PE16_IDX         144
#define PIO_PE17_IDX         145
#define PIO_PE18_IDX         146
#define PIO_PE19_IDX         147
#define PIO_PE20_IDX         148
#define PIO_PE21_IDX         149
#define PIO_PE22_IDX         150
#define PIO_PE23_IDX         151
#define PIO_PE24_IDX         152
#define PIO_PE25_IDX         153
#define PIO_PE26_IDX         154
#define PIO_PE27_IDX         155
#define PIO_PE28_IDX         156
#define PIO_PE29_IDX         157
#define PIO_PE30_IDX         158
#define PIO_PE31_IDX         159
/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAMA5D4 */
/* ************************************************************************** */

#define IRAM_SIZE (0x20000u)
#define IROM_SIZE (0x20000u)

#define EBI_CS0_ADDR    (0x10000000u) /**< EBI Chip Select 0 base address */
#define DDR_CS_ADDR     (0x20000000u) /**< DDR Chip Select base address */
#define DDR_AES_CS_ADDR (0x40000000u) /**< DDR with AES Chip Select base address */
#define EBI_CS1_ADDR    (0x60000000u) /**< EBI Chip Select 1 base address */
#define EBI_CS2_ADDR    (0x70000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR    (0x80000000u) /**< EBI Chip Select 3 base address */
#define NFC_ADDR        (0x90000000u) /**< NAND Flash Controller Command base address */
#define IROM_ADDR       (0x00000000u) /**< Internal ROM base address */
#define NFC_RAM_ADDR    (0x00100000u) /**< NAND Flash Controller RAM base address */
#define IRAM_ADDR       (0x00200000u) /**< Internal RAM base address */
#define UDPHS_RAM_ADDR  (0x00400000u) /**< USB High Speed Device Port RAM base address */
#define UHP_OHCI_ADDR   (0x00500000u) /**< USB Host Port OHCI base address */
#define UHP_EHCI_ADDR   (0x00600000u) /**< USB Host Port EHCI base address */
#define AXIMX_ADDR      (0x00700000u) /**< AXI Bus Matrix base address */
#define DAP_ADDR        (0x00800000u) /**< Debug Access Port base address */
#define SMD_ADDR        (0x00900000u) /**< Software Modem Device base address */

/* ************************************************************************** */
/*   ELECTRICAL DEFINITIONS FOR SAMA5D4 */
/* ************************************************************************** */

/* %ATMEL_ELECTRICAL% */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SAMA5D4_ */
