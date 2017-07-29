
#ifndef _AT91SAMA5_
#define _AT91SAMA5_

/** \addtogroup AT91SAMA5_definitions AT91SAMA5 definitions
  This file defines all structures and symbols for AT91SAMA5:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef __ASSEMBLY__
#include <stdint.h>
#ifndef __cplusplus
typedef volatile const uint32_t RoReg; /**< Read only 32-bit register (volatile const unsigned int) */
#else
typedef volatile       uint32_t RoReg; /**< Read only 32-bit register (volatile const unsigned int) */
#endif
typedef volatile       uint32_t WoReg; /**< Write only 32-bit register (volatile unsigned int) */
typedef volatile       uint32_t RwReg; /**< Read-Write 32-bit register (volatile unsigned int) */
#endif

typedef enum IRQn
{
  FIQ_IRQn             =  0, /**<  0 AT91SAMA5 Advanced Interrupt Controller (FIQ) */
  SYS_IRQn             =  1, /**<  1 AT91SAMA5 System Controller Interrupt (SYS) */
  DBGU_IRQn            =  2, /**<  2 AT91SAMA5 Debug Unit Interrupt (DBGU) */
  PIT_IRQn             =  3, /**<  3 AT91SAMA5 Periodic Interval Timer Interrupt (PIT) */
  WDT_IRQn             =  4, /**<  4 AT91SAMA5 Watchdog timer Interrupt (WDT) */
  SMC_IRQn             =  5, /**<  5 AT91SAMA5 Multi-bit ECC Interrupt (SMC) */
  PIOA_IRQn            =  6, /**<  6 AT91SAMA5 Parallel I/O Controller A (PIOA) */
  PIOB_IRQn            =  7, /**<  7 AT91SAMA5 Parallel I/O Controller B (PIOB) */
  PIOC_IRQn            =  8, /**<  8 AT91SAMA5 Parallel I/O Controller C (PIOC) */
  PIOD_IRQn            =  9, /**<  9 AT91SAMA5 Parallel I/O Controller D (PIOD) */
  PIOE_IRQn            = 10, /**< 10 AT91SAMA5 Parallel I/O Controller E (PIOE) */
  SMD_IRQn             = 11, /**< 11 AT91SAMA5 SMD Soft Modem (SMD) */
  USART0_IRQn          = 12, /**< 12 AT91SAMA5 USART 0 (USART0) */
  USART1_IRQn          = 13, /**< 13 AT91SAMA5 USART 1 (USART1) */
  USART2_IRQn          = 14, /**< 14 AT91SAMA5 USART 2 (USART2) */
  USART3_IRQn          = 15, /**< 15 AT91SAMA5 USART 3 (USART3) */
  UART0_IRQn           = 16, /**< 16 AT91SAMA5 UART 0 (UART0) */
  UART1_IRQn           = 17, /**< 17 AT91SAMA5 UART 1 (UART1) */
  TWI0_IRQn            = 18, /**< 18 AT91SAMA5 Two-Wire Interface 0 (TWI0) */
  TWI1_IRQn            = 19, /**< 19 AT91SAMA5 Two-Wire Interface 1 (TWI1) */
  TWI2_IRQn            = 20, /**< 20 AT91SAMA5 Two-Wire Interface 2 (TWI2) */
  HSMCI0_IRQn          = 21, /**< 21 AT91SAMA5 High Speed Multimedia Card Interface 0 (HSMCI0) */
  HSMCI1_IRQn          = 22, /**< 22 AT91SAMA5 High Speed Multimedia Card Interface 1 (HSMCI1) */
  HSMCI2_IRQn          = 23, /**< 23 AT91SAMA5 High Speed Multimedia Card Interface 2 (HSMCI2) */
  SPI0_IRQn            = 24, /**< 24 AT91SAMA5 Serial Peripheral Interface 0 (SPI0) */
  SPI1_IRQn            = 25, /**< 25 AT91SAMA5 Serial Peripheral Interface 1 (SPI1) */
  TC0_IRQn             = 26, /**< 26 AT91SAMA5 Timer Counter 0 (ch. 0, 1, 2) (TC0) */
  TC1_IRQn             = 27, /**< 27 AT91SAMA5 Timer Counter 1 (ch. 3, 4, 5) (TC1) */
  PWM_IRQn             = 28, /**< 28 AT91SAMA5 Pulse Width Modulation Controller (PWM) */
  ADC_IRQn             = 29, /**< 29 AT91SAMA5 Touch Screen ADC Controller (ADC) */
  DMAC0_IRQn           = 30, /**< 30 AT91SAMA5 DMA Controller 0 (DMAC0) */
  DMAC1_IRQn           = 31, /**< 31 AT91SAMA5 DMA Controller 1 (DMAC1) */
  UHPHS_IRQn           = 32, /**< 32 AT91SAMA5 USB Host High Speed (UHPHS) */
  UDPHS_IRQn           = 33, /**< 33 AT91SAMA5 USB Device High Speed (UDPHS) */
  GMAC_IRQn            = 34, /**< 34 AT91SAMA5 Gigabit Ethernet MAC (GMAC) */
  EMAC_IRQn            = 35, /**< 35 AT91SAMA5 Ethernet MAC (EMAC) */
  LCDC_IRQn            = 36, /**< 36 AT91SAMA5 LCD Controller (LCDC) */
  ISI_IRQn             = 37, /**< 37 AT91SAMA5 Image Sensor Interface (ISI) */
  SSC0_IRQn            = 38, /**< 38 AT91SAMA5 Synchronous Serial Controller 0 (SSC0) */
  SSC1_IRQn            = 39, /**< 39 AT91SAMA5 Synchronous Serial Controller 1 (SSC1) */
  CAN0_IRQn            = 40, /**< 40 AT91SAMA5 CAN controller 0 (CAN0) */
  CAN1_IRQn            = 41, /**< 41 AT91SAMA5 CAN controller 1 (CAN1) */
  SHA_IRQn             = 42, /**< 42 AT91SAMA5 Secure Hash Algorithm (SHA) */
  AES_IRQn             = 43, /**< 43 AT91SAMA5 Advanced Encryption Standard (AES) */
  TDES_IRQn            = 44, /**< 44 AT91SAMA5 Triple Data EncryptionStandard (TDES) */
  TRNG_IRQn            = 45, /**< 45 AT91SAMA5 True Random Number Generator (TRNG) */
  ARM_IRQn             = 46, /**< 46 AT91SAMA5 Performance Monitor Unit (ARM) */
  IRQ_IRQn             = 47, /**< 47 AT91SAMA5 Advanced Interrupt Controller (IRQ) */
  FUSE_IRQn            = 48, /**< 48 AT91SAMA5 Fuse Controller (FUSE) */
  MPDDRC_IRQn          = 49  /**< 49 AT91SAMA5 MPDDR controller (MPDDRC) */
} IRQn_Type;

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR AT91SAMA5 */
/* ************************************************************************** */
/** \addtogroup AT91SAMA5_api Peripheral Software API */
/*@{*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Advanced Interrupt Controller */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_AIC Advanced Interrupt Controller */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Aic hardware registers */
typedef struct {
  RwReg AIC_SSR;       /**< \brief (Aic Offset: 0x00) Source Select Register */
  RwReg AIC_SMR;       /**< \brief (Aic Offset: 0x04) Source Mode Register */
  RwReg AIC_SVR;       /**< \brief (Aic Offset: 0x08) Source Vector Register */
  RoReg Reserved1[1];
  RoReg AIC_IVR;       /**< \brief (Aic Offset: 0x10) Interrupt Vector Register */
  RoReg AIC_FVR;       /**< \brief (Aic Offset: 0x14) FIQ Interrupt Vector Register */
  RoReg AIC_ISR;       /**< \brief (Aic Offset: 0x18) Interrupt Status Register */
  RoReg Reserved2[1];
  RoReg AIC_IPR0;      /**< \brief (Aic Offset: 0x20) Interrupt Pending Register 0 */
  RoReg AIC_IPR1;      /**< \brief (Aic Offset: 0x24) Interrupt Pending Register 1 */
  RoReg AIC_IPR2;      /**< \brief (Aic Offset: 0x28) Interrupt Pending Register 2 */
  RoReg AIC_IPR3;      /**< \brief (Aic Offset: 0x2C) Interrupt Pending Register 3 */
  RoReg AIC_IMR;       /**< \brief (Aic Offset: 0x30) Interrupt Mask Register */
  RoReg AIC_CISR;      /**< \brief (Aic Offset: 0x34) Core Interrupt Status Register */
  WoReg AIC_EOICR;     /**< \brief (Aic Offset: 0x38) End of Interrupt Command Register */
  RwReg AIC_SPU;       /**< \brief (Aic Offset: 0x3C) Spurious Interrupt Vector Register */
  WoReg AIC_IECR;      /**< \brief (Aic Offset: 0x40) Interrupt Enable Command Register */
  WoReg AIC_IDCR;      /**< \brief (Aic Offset: 0x44) Interrupt Disable Command Register */
  WoReg AIC_ICCR;      /**< \brief (Aic Offset: 0x48) Interrupt Clear Command Register */
  WoReg AIC_ISCR;      /**< \brief (Aic Offset: 0x4C) Interrupt Set Command Register */
  WoReg AIC_FFER;      /**< \brief (Aic Offset: 0x50) Fast Forcing Enable Register */
  WoReg AIC_FFDR;      /**< \brief (Aic Offset: 0x54) Fast Forcing Disable Register */
  RoReg AIC_FFSR;      /**< \brief (Aic Offset: 0x58) Fast Forcing Status Register */
  RoReg Reserved3;
  WoReg AIC_SVRRER;    /**< \brief (Aic Offset: 0x60) AIC SVR Return Enable Register */
  WoReg AIC_SVRRDR;    /**< \brief (Aic Offset: 0x54) AIC SVR Return Disable Register */
  RoReg AIC_SVRRSR;    /**< \brief (Aic Offset: 0x68) AIC SVR Return status Register */
  RwReg AIC_DCR;       /**< \brief (Aic Offset: 0x6C) Debug Control Register */
  RoReg Reserved4[29];
  RwReg AIC_WPMR;      /**< \brief (Aic Offset: 0xE4) Write Protect Mode Register */
  RoReg AIC_WPSR;      /**< \brief (Aic Offset: 0xE8) Write Protect Status Register */
} Aic;
#endif /* __ASSEMBLY__ */
/* -------- AIC_SSR : (AIC Offset: 0x00) Source Select Register -------- */
#define AIC_SSR_INTSEL_Pos 0
#define AIC_SSR_INTSEL_Msk (0x7fu << AIC_SSR_INTSEL_Pos) /**< \brief (AIC_SSR) Interrupt line Selection */
#define AIC_SSR_INTSEL(value) ((AIC_SSR_INTSEL_Msk & ((value) << AIC_SSR_INTSEL_Pos)))
/* -------- AIC_SMR : (AIC Offset: 0x04) Source Mode Register -------- */
#define AIC_SMR_PRIOR_Pos 0
#define AIC_SMR_PRIOR_Msk (0x7u << AIC_SMR_PRIOR_Pos) /**< \brief (AIC_SMR) Priority Level */
#define AIC_SMR_PRIOR(value) ((AIC_SMR_PRIOR_Msk & ((value) << AIC_SMR_PRIOR_Pos)))
#define AIC_SMR_SRCTYPE_Pos 5
#define AIC_SMR_SRCTYPE_Msk (0x3u << AIC_SMR_SRCTYPE_Pos) /**< \brief (AIC_SMR) Interrupt Source Type */
#define   AIC_SMR_SRCTYPE_INT_LEVEL_SENSITIVE (0x0u << 5) /**< \brief (AIC_SMR) High level Sensitive for internal sourceLow level Sensitive for external source */
#define   AIC_SMR_SRCTYPE_INT_EDGE_TRIGGERED (0x1u << 5) /**< \brief (AIC_SMR) Positive edge triggered for internal sourceNegative edge triggered for external source */
#define   AIC_SMR_SRCTYPE_EXT_HIGH_LEVEL (0x2u << 5) /**< \brief (AIC_SMR) High level Sensitive for internal sourceHigh level Sensitive for external source */
#define   AIC_SMR_SRCTYPE_EXT_POSITIVE_EDGE (0x3u << 5) /**< \brief (AIC_SMR) Positive edge triggered for internal sourcePositive edge triggered for external source */
/* -------- AIC_SVR : (AIC Offset: 0x08) Source Vector Register -------- */
#define AIC_SVR_VECTOR_Pos 0
#define AIC_SVR_VECTOR_Msk (0xffffffffu << AIC_SVR_VECTOR_Pos) /**< \brief (AIC_SVR) Source Vector */
#define AIC_SVR_VECTOR(value) ((AIC_SVR_VECTOR_Msk & ((value) << AIC_SVR_VECTOR_Pos)))
/* -------- AIC_IVR : (AIC Offset: 0x10) Interrupt Vector Register -------- */
#define AIC_IVR_IRQV_Pos 0
#define AIC_IVR_IRQV_Msk (0xffffffffu << AIC_IVR_IRQV_Pos) /**< \brief (AIC_IVR) Interrupt Vector Register */
/* -------- AIC_FVR : (AIC Offset: 0x14) FIQ Interrupt Vector Register -------- */
#define AIC_FVR_FIQV_Pos 0
#define AIC_FVR_FIQV_Msk (0xffffffffu << AIC_FVR_FIQV_Pos) /**< \brief (AIC_FVR) FIQ Vector Register */
/* -------- AIC_ISR : (AIC Offset: 0x18) Interrupt Status Register -------- */
#define AIC_ISR_IRQID_Pos 0
#define AIC_ISR_IRQID_Msk (0x7fu << AIC_ISR_IRQID_Pos) /**< \brief (AIC_ISR) Current Interrupt Identifier */
/* -------- AIC_IPR0 : (AIC Offset: 0x20) Interrupt Pending Register 0 -------- */
#define AIC_IPR0_FIQ (0x1u << 0) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_SYS (0x1u << 1) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID2 (0x1u << 2) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID3 (0x1u << 3) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID4 (0x1u << 4) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID5 (0x1u << 5) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID6 (0x1u << 6) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID7 (0x1u << 7) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID8 (0x1u << 8) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID9 (0x1u << 9) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID10 (0x1u << 10) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID11 (0x1u << 11) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID12 (0x1u << 12) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID13 (0x1u << 13) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID14 (0x1u << 14) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID15 (0x1u << 15) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID16 (0x1u << 16) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID17 (0x1u << 17) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID18 (0x1u << 18) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID19 (0x1u << 19) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID20 (0x1u << 20) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID21 (0x1u << 21) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID22 (0x1u << 22) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID23 (0x1u << 23) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID24 (0x1u << 24) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID25 (0x1u << 25) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID26 (0x1u << 26) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID27 (0x1u << 27) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID28 (0x1u << 28) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID29 (0x1u << 29) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID30 (0x1u << 30) /**< \brief (AIC_IPR0) Interrupt Pending */
#define AIC_IPR0_PID31 (0x1u << 31) /**< \brief (AIC_IPR0) Interrupt Pending */
/* -------- AIC_IPR1 : (AIC Offset: 0x24) Interrupt Pending Register 1 -------- */
#define AIC_IPR1_PID32 (0x1u << 0) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID33 (0x1u << 1) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID34 (0x1u << 2) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID35 (0x1u << 3) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID36 (0x1u << 4) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID37 (0x1u << 5) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID38 (0x1u << 6) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID39 (0x1u << 7) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID40 (0x1u << 8) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID41 (0x1u << 9) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID42 (0x1u << 10) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID43 (0x1u << 11) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID44 (0x1u << 12) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID45 (0x1u << 13) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID46 (0x1u << 14) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID47 (0x1u << 15) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID48 (0x1u << 16) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID49 (0x1u << 17) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID50 (0x1u << 18) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID51 (0x1u << 19) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID52 (0x1u << 20) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID53 (0x1u << 21) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID54 (0x1u << 22) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID55 (0x1u << 23) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID56 (0x1u << 24) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID57 (0x1u << 25) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID58 (0x1u << 26) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID59 (0x1u << 27) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID60 (0x1u << 28) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID61 (0x1u << 29) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID62 (0x1u << 30) /**< \brief (AIC_IPR1) Interrupt Pending */
#define AIC_IPR1_PID63 (0x1u << 31) /**< \brief (AIC_IPR1) Interrupt Pending */
/* -------- AIC_IPR2 : (AIC Offset: 0x28) Interrupt Pending Register 2 -------- */
#define AIC_IPR2_PID64 (0x1u << 0) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID65 (0x1u << 1) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID66 (0x1u << 2) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID67 (0x1u << 3) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID68 (0x1u << 4) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID69 (0x1u << 5) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID70 (0x1u << 6) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID71 (0x1u << 7) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID72 (0x1u << 8) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID73 (0x1u << 9) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID74 (0x1u << 10) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID75 (0x1u << 11) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID76 (0x1u << 12) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID77 (0x1u << 13) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID78 (0x1u << 14) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID79 (0x1u << 15) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID80 (0x1u << 16) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID81 (0x1u << 17) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID82 (0x1u << 18) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID83 (0x1u << 19) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID84 (0x1u << 20) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID85 (0x1u << 21) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID86 (0x1u << 22) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID87 (0x1u << 23) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID88 (0x1u << 24) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID89 (0x1u << 25) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID90 (0x1u << 26) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID91 (0x1u << 27) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID92 (0x1u << 28) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID93 (0x1u << 29) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID94 (0x1u << 30) /**< \brief (AIC_IPR2) Interrupt Pending */
#define AIC_IPR2_PID95 (0x1u << 31) /**< \brief (AIC_IPR2) Interrupt Pending */
/* -------- AIC_IPR3 : (AIC Offset: 0x2C) Interrupt Pending Register 3 -------- */
#define AIC_IPR3_PID96 (0x1u << 0) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID97 (0x1u << 1) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID98 (0x1u << 2) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID99 (0x1u << 3) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID100 (0x1u << 4) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID101 (0x1u << 5) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID102 (0x1u << 6) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID103 (0x1u << 7) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID104 (0x1u << 8) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID105 (0x1u << 9) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID106 (0x1u << 10) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID107 (0x1u << 11) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID108 (0x1u << 12) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID109 (0x1u << 13) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID110 (0x1u << 14) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID111 (0x1u << 15) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID112 (0x1u << 16) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID113 (0x1u << 17) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID114 (0x1u << 18) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID115 (0x1u << 19) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID116 (0x1u << 20) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID117 (0x1u << 21) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID118 (0x1u << 22) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID119 (0x1u << 23) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID120 (0x1u << 24) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID121 (0x1u << 25) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID122 (0x1u << 26) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID123 (0x1u << 27) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID124 (0x1u << 28) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID125 (0x1u << 29) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID126 (0x1u << 30) /**< \brief (AIC_IPR3) Interrupt Pending */
#define AIC_IPR3_PID127 (0x1u << 31) /**< \brief (AIC_IPR3) Interrupt Pending */
/* -------- AIC_IMR : (AIC Offset: 0x30) Interrupt Mask Register -------- */
#define AIC_IMR_INTM (0x1u << 0) /**< \brief (AIC_IMR) Interrupt Mask */
/* -------- AIC_CISR : (AIC Offset: 0x34) Core Interrupt Status Register -------- */
#define AIC_CISR_NFIQ (0x1u << 0) /**< \brief (AIC_CISR) NFIQ Status */
#define AIC_CISR_NIRQ (0x1u << 1) /**< \brief (AIC_CISR) NIRQ Status */
/* -------- AIC_SPU : (AIC Offset: 0x3C) Spurious Interrupt Vector Register -------- */
#define AIC_SPU_SIVR_Pos 0
#define AIC_SPU_SIVR_Msk (0xffffffffu << AIC_SPU_SIVR_Pos) /**< \brief (AIC_SPU) Spurious Interrupt Vector Register */
#define AIC_SPU_SIVR(value) ((AIC_SPU_SIVR_Msk & ((value) << AIC_SPU_SIVR_Pos)))
/* -------- AIC_IECR : (AIC Offset: 0x40) Interrupt Enable Command Register -------- */
#define AIC_IECR_INTEN (0x1u << 0) /**< \brief (AIC_IECR) Interrupt Enable */
/* -------- AIC_IDCR : (AIC Offset: 0x44) Interrupt Disable Command Register -------- */
#define AIC_IDCR_INTD (0x1u << 0) /**< \brief (AIC_IDCR) Interrupt Disable */
/* -------- AIC_ICCR : (AIC Offset: 0x48) Interrupt Clear Command Register -------- */
#define AIC_ICCR_INTCLR (0x1u << 0) /**< \brief (AIC_ICCR) Interrupt Clear */
/* -------- AIC_ISCR : (AIC Offset: 0x4C) Interrupt Set Command Register -------- */
#define AIC_ISCR_INTSET (0x1u << 0) /**< \brief (AIC_ISCR) Interrupt Set */
/* -------- AIC_FFER : (AIC Offset: 0x50) Fast Forcing Enable Register -------- */
#define AIC_FFER_FFEN (0x1u << 0) /**< \brief (AIC_FFER) Fast Forcing Enable */
/* -------- AIC_FFDR : (AIC Offset: 0x54) Fast Forcing Disable Register -------- */
#define AIC_FFDR_FFDIS (0x1u << 0) /**< \brief (AIC_FFDR) Fast Forcing Disable */
/* -------- AIC_FFSR : (AIC Offset: 0x58) Fast Forcing Status Register -------- */
#define AIC_FFSR_FFS (0x1u << 0) /**< \brief (AIC_FFSR) Fast Forcing Status */
/* -------- AIC_DCR : (AIC Offset: 0x6C) Debug Control Register -------- */
#define AIC_DCR_PROT (0x1u << 0) /**< \brief (AIC_DCR) Protection Mode */
#define AIC_DCR_GMSK (0x1u << 1) /**< \brief (AIC_DCR) General Mask */
/* -------- AIC_WPMR : (AIC Offset: 0xE4) Write Protect Mode Register -------- */
#define AIC_WPMR_WPEN (0x1u << 0) /**< \brief (AIC_WPMR) Write Protect Enable */
#define AIC_WPMR_WPKEY_Pos 8
#define AIC_WPMR_WPKEY_Msk (0xffffffu << AIC_WPMR_WPKEY_Pos) /**< \brief (AIC_WPMR) Write Protect KEY */
#define AIC_WPMR_WPKEY(value) ((AIC_WPMR_WPKEY_Msk & ((value) << AIC_WPMR_WPKEY_Pos)))
/* -------- AIC_WPSR : (AIC Offset: 0xE8) Write Protect Status Register -------- */
#define AIC_WPSR_WPVS (0x1u << 0) /**< \brief (AIC_WPSR) Write Protect Violation Status */
#define AIC_WPSR_WPVSRC_Pos 8
#define AIC_WPSR_WPVSRC_Msk (0xffffu << AIC_WPSR_WPVSRC_Pos) /**< \brief (AIC_WPSR) Write Protect Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR AXI MATRIX */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_AXIMX AXI MATRIX */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Aximx hardware registers */
typedef struct {
  WoReg AXIMX_REMAP;               /**< \brief (Aximx Offset: 0x00) Remap Register */
  RoReg Reserved1[2035];
  RoReg AXIMX_PERIPH_ID4;          /**< \brief (Aximx Offset: 0x1FD0) Peripheral ID Register 4 */
  RoReg AXIMX_PERIPH_ID5;          /**< \brief (Aximx Offset: 0x1FD4) Peripheral ID Register 5 */
  RoReg AXIMX_PERIPH_ID6;          /**< \brief (Aximx Offset: 0x1FD8) Peripheral ID Register 6 */
  RoReg AXIMX_PERIPH_ID7;          /**< \brief (Aximx Offset: 0x1FDC) Peripheral ID Register 7 */
  RoReg AXIMX_PERIPH_ID0;          /**< \brief (Aximx Offset: 0x1FE0) Peripheral ID Register 0 */
  RoReg AXIMX_PERIPH_ID1;          /**< \brief (Aximx Offset: 0x1FE4) Peripheral ID Register 1 */
  RoReg AXIMX_PERIPH_ID2;          /**< \brief (Aximx Offset: 0x1FE8) Peripheral ID Register 2 */
  RoReg AXIMX_PERIPH_ID3;          /**< \brief (Aximx Offset: 0x1FEC) Peripheral ID Register 3 */
  RoReg AXIMX_COMP_ID[4];          /**< \brief (Aximx Offset: 0x1FF0) Component ID Register */
  RoReg Reserved2[3074];
  RwReg AXIMX_AMIB3_FN_MOD_BM_ISS; /**< \brief (Aximx Offset: 0x5008) AMIB3 Bus Matrix Functionality Modification Register */
  RoReg Reserved3[6];
  RwReg AXIMX_AMIB3_FN_MOD2;       /**< \brief (Aximx Offset: 0x5024) AMIB3 Bypass Merge */
  RoReg Reserved4[62518];
  RwReg AXIMX_ASIB0_READ_QOS;      /**< \brief (Aximx Offset: 0x42100) ASIB0 Read Channel QoS Register */
  RwReg AXIMX_ASIB0_WRITE_QOS;     /**< \brief (Aximx Offset: 0x42104) ASIB0 Write Channel QoS Register */
  RoReg Reserved5[968];
  RwReg AXIMX_ASIB1_FN_MOD_AHB;    /**< \brief (Aximx Offset: 0x43028) ASIB1 AHB Functionality Modification Register */
  RoReg Reserved6[53];
  RwReg AXIMX_ASIB1_READ_QOS;      /**< \brief (Aximx Offset: 0x43100) ASIB1 Read Channel QoS Register */
  RwReg AXIMX_ASIB1_WRITE_QOS;     /**< \brief (Aximx Offset: 0x43104) ASIB1 Write Channel QoS Register */
  RwReg AXIMX_ASIB1_FN_MOD;        /**< \brief (Aximx Offset: 0x43108) ASIB1 Issuing Functionality Modification Register */
} Aximx;
#endif /* __ASSEMBLY__ */
/* -------- AXIMX_REMAP : (AXIMX Offset: 0x00) Remap Register -------- */
#define AXIMX_REMAP_REMAP0 (0x1u << 0) /**< \brief (AXIMX_REMAP) Remap State 0 */
#define AXIMX_REMAP_REMAP1 (0x1u << 1) /**< \brief (AXIMX_REMAP) Remap State 1 */
/* -------- AXIMX_PERIPH_ID4 : (AXIMX Offset: 0x1FD0) Peripheral ID Register 4 -------- */
#define AXIMX_PERIPH_ID4_ID_Pos 0
#define AXIMX_PERIPH_ID4_ID_Msk (0xffu << AXIMX_PERIPH_ID4_ID_Pos) /**< \brief (AXIMX_PERIPH_ID4) Peripheral ID */
#define   AXIMX_PERIPH_ID4_ID_ID0 (0x1u << 0) /**< \brief (AXIMX_PERIPH_ID4) Part Number */
#define   AXIMX_PERIPH_ID4_ID_ID4 (0x4u << 0) /**< \brief (AXIMX_PERIPH_ID4) 4KB count, JEP106 continuation code */
#define   AXIMX_PERIPH_ID4_ID_ID1 (0xB3u << 0) /**< \brief (AXIMX_PERIPH_ID4) JEP106[3:0, part number[11:8] */
#define   AXIMX_PERIPH_ID4_ID_ID2 (0xB6u << 0) /**< \brief (AXIMX_PERIPH_ID4) Revision, JEP106 code flag, JEP106[6:4] */
/* -------- AXIMX_PERIPH_ID5 : (AXIMX Offset: 0x1FD4) Peripheral ID Register 5 -------- */
#define AXIMX_PERIPH_ID5_ID_Pos 0
#define AXIMX_PERIPH_ID5_ID_Msk (0xffu << AXIMX_PERIPH_ID5_ID_Pos) /**< \brief (AXIMX_PERIPH_ID5) Peripheral ID */
#define   AXIMX_PERIPH_ID5_ID_ID0 (0x1u << 0) /**< \brief (AXIMX_PERIPH_ID5) Part Number */
#define   AXIMX_PERIPH_ID5_ID_ID4 (0x4u << 0) /**< \brief (AXIMX_PERIPH_ID5) 4KB count, JEP106 continuation code */
#define   AXIMX_PERIPH_ID5_ID_ID1 (0xB3u << 0) /**< \brief (AXIMX_PERIPH_ID5) JEP106[3:0, part number[11:8] */
#define   AXIMX_PERIPH_ID5_ID_ID2 (0xB6u << 0) /**< \brief (AXIMX_PERIPH_ID5) Revision, JEP106 code flag, JEP106[6:4] */
/* -------- AXIMX_PERIPH_ID6 : (AXIMX Offset: 0x1FD8) Peripheral ID Register 6 -------- */
#define AXIMX_PERIPH_ID6_ID_Pos 0
#define AXIMX_PERIPH_ID6_ID_Msk (0xffu << AXIMX_PERIPH_ID6_ID_Pos) /**< \brief (AXIMX_PERIPH_ID6) Peripheral ID */
#define   AXIMX_PERIPH_ID6_ID_ID0 (0x1u << 0) /**< \brief (AXIMX_PERIPH_ID6) Part Number */
#define   AXIMX_PERIPH_ID6_ID_ID4 (0x4u << 0) /**< \brief (AXIMX_PERIPH_ID6) 4KB count, JEP106 continuation code */
#define   AXIMX_PERIPH_ID6_ID_ID1 (0xB3u << 0) /**< \brief (AXIMX_PERIPH_ID6) JEP106[3:0, part number[11:8] */
#define   AXIMX_PERIPH_ID6_ID_ID2 (0xB6u << 0) /**< \brief (AXIMX_PERIPH_ID6) Revision, JEP106 code flag, JEP106[6:4] */
/* -------- AXIMX_PERIPH_ID7 : (AXIMX Offset: 0x1FDC) Peripheral ID Register 7 -------- */
#define AXIMX_PERIPH_ID7_ID_Pos 0
#define AXIMX_PERIPH_ID7_ID_Msk (0xffu << AXIMX_PERIPH_ID7_ID_Pos) /**< \brief (AXIMX_PERIPH_ID7) Peripheral ID */
#define   AXIMX_PERIPH_ID7_ID_ID0 (0x1u << 0) /**< \brief (AXIMX_PERIPH_ID7) Part Number */
#define   AXIMX_PERIPH_ID7_ID_ID4 (0x4u << 0) /**< \brief (AXIMX_PERIPH_ID7) 4KB count, JEP106 continuation code */
#define   AXIMX_PERIPH_ID7_ID_ID1 (0xB3u << 0) /**< \brief (AXIMX_PERIPH_ID7) JEP106[3:0, part number[11:8] */
#define   AXIMX_PERIPH_ID7_ID_ID2 (0xB6u << 0) /**< \brief (AXIMX_PERIPH_ID7) Revision, JEP106 code flag, JEP106[6:4] */
/* -------- AXIMX_PERIPH_ID0 : (AXIMX Offset: 0x1FE0) Peripheral ID Register 0 -------- */
#define AXIMX_PERIPH_ID0_ID_Pos 0
#define AXIMX_PERIPH_ID0_ID_Msk (0xffu << AXIMX_PERIPH_ID0_ID_Pos) /**< \brief (AXIMX_PERIPH_ID0) Peripheral ID */
#define   AXIMX_PERIPH_ID0_ID_ID0 (0x1u << 0) /**< \brief (AXIMX_PERIPH_ID0) Part Number */
#define   AXIMX_PERIPH_ID0_ID_ID4 (0x4u << 0) /**< \brief (AXIMX_PERIPH_ID0) 4KB count, JEP106 continuation code */
#define   AXIMX_PERIPH_ID0_ID_ID1 (0xB3u << 0) /**< \brief (AXIMX_PERIPH_ID0) JEP106[3:0, part number[11:8] */
#define   AXIMX_PERIPH_ID0_ID_ID2 (0xB6u << 0) /**< \brief (AXIMX_PERIPH_ID0) Revision, JEP106 code flag, JEP106[6:4] */
/* -------- AXIMX_PERIPH_ID1 : (AXIMX Offset: 0x1FE4) Peripheral ID Register 1 -------- */
#define AXIMX_PERIPH_ID1_ID_Pos 0
#define AXIMX_PERIPH_ID1_ID_Msk (0xffu << AXIMX_PERIPH_ID1_ID_Pos) /**< \brief (AXIMX_PERIPH_ID1) Peripheral ID */
#define   AXIMX_PERIPH_ID1_ID_ID0 (0x1u << 0) /**< \brief (AXIMX_PERIPH_ID1) Part Number */
#define   AXIMX_PERIPH_ID1_ID_ID4 (0x4u << 0) /**< \brief (AXIMX_PERIPH_ID1) 4KB count, JEP106 continuation code */
#define   AXIMX_PERIPH_ID1_ID_ID1 (0xB3u << 0) /**< \brief (AXIMX_PERIPH_ID1) JEP106[3:0, part number[11:8] */
#define   AXIMX_PERIPH_ID1_ID_ID2 (0xB6u << 0) /**< \brief (AXIMX_PERIPH_ID1) Revision, JEP106 code flag, JEP106[6:4] */
/* -------- AXIMX_PERIPH_ID2 : (AXIMX Offset: 0x1FE8) Peripheral ID Register 2 -------- */
#define AXIMX_PERIPH_ID2_ID_Pos 0
#define AXIMX_PERIPH_ID2_ID_Msk (0xffu << AXIMX_PERIPH_ID2_ID_Pos) /**< \brief (AXIMX_PERIPH_ID2) Peripheral ID */
#define   AXIMX_PERIPH_ID2_ID_ID0 (0x1u << 0) /**< \brief (AXIMX_PERIPH_ID2) Part Number */
#define   AXIMX_PERIPH_ID2_ID_ID4 (0x4u << 0) /**< \brief (AXIMX_PERIPH_ID2) 4KB count, JEP106 continuation code */
#define   AXIMX_PERIPH_ID2_ID_ID1 (0xB3u << 0) /**< \brief (AXIMX_PERIPH_ID2) JEP106[3:0, part number[11:8] */
#define   AXIMX_PERIPH_ID2_ID_ID2 (0xB6u << 0) /**< \brief (AXIMX_PERIPH_ID2) Revision, JEP106 code flag, JEP106[6:4] */
/* -------- AXIMX_PERIPH_ID3 : (AXIMX Offset: 0x1FEC) Peripheral ID Register 3 -------- */
#define AXIMX_PERIPH_ID3_ID_Pos 0
#define AXIMX_PERIPH_ID3_ID_Msk (0xffu << AXIMX_PERIPH_ID3_ID_Pos) /**< \brief (AXIMX_PERIPH_ID3) Peripheral ID */
#define   AXIMX_PERIPH_ID3_ID_ID0 (0x1u << 0) /**< \brief (AXIMX_PERIPH_ID3) Part Number */
#define   AXIMX_PERIPH_ID3_ID_ID4 (0x4u << 0) /**< \brief (AXIMX_PERIPH_ID3) 4KB count, JEP106 continuation code */
#define   AXIMX_PERIPH_ID3_ID_ID1 (0xB3u << 0) /**< \brief (AXIMX_PERIPH_ID3) JEP106[3:0, part number[11:8] */
#define   AXIMX_PERIPH_ID3_ID_ID2 (0xB6u << 0) /**< \brief (AXIMX_PERIPH_ID3) Revision, JEP106 code flag, JEP106[6:4] */
/* -------- AXIMX_COMP_ID[4] : (AXIMX Offset: 0x1FF0) Component ID Register -------- */
#define AXIMX_COMP_ID_ID_Pos 0
#define AXIMX_COMP_ID_ID_Msk (0xffu << AXIMX_COMP_ID_ID_Pos) /**< \brief (AXIMX_COMP_ID[4]) Component ID */
/* -------- AXIMX_AMIB3_FN_MOD_BM_ISS : (AXIMX Offset: 0x5008) AMIB3 Bus Matrix Functionality Modification Register -------- */
#define AXIMX_AMIB3_FN_MOD_BM_ISS_RD_ISS (0x1u << 0) /**< \brief (AXIMX_AMIB3_FN_MOD_BM_ISS) Read Issuing */
#define AXIMX_AMIB3_FN_MOD_BM_ISS_WR_ISS (0x1u << 1) /**< \brief (AXIMX_AMIB3_FN_MOD_BM_ISS) Write Issuing */
/* -------- AXIMX_AMIB3_FN_MOD2 : (AXIMX Offset: 0x5024) AMIB3 Bypass Merge -------- */
#define AXIMX_AMIB3_FN_MOD2_BP_MRG (0x1u << 0) /**< \brief (AXIMX_AMIB3_FN_MOD2) Bypass Merge */
/* -------- AXIMX_ASIB0_READ_QOS : (AXIMX Offset: 0x42100) ASIB0 Read Channel QoS Register -------- */
#define AXIMX_ASIB0_READ_QOS_RD_QOS_Pos 0
#define AXIMX_ASIB0_READ_QOS_RD_QOS_Msk (0xfu << AXIMX_ASIB0_READ_QOS_RD_QOS_Pos) /**< \brief (AXIMX_ASIB0_READ_QOS) Read QoS */
#define AXIMX_ASIB0_READ_QOS_RD_QOS(value) ((AXIMX_ASIB0_READ_QOS_RD_QOS_Msk & ((value) << AXIMX_ASIB0_READ_QOS_RD_QOS_Pos)))
/* -------- AXIMX_ASIB0_WRITE_QOS : (AXIMX Offset: 0x42104) ASIB0 Write Channel QoS Register -------- */
#define AXIMX_ASIB0_WRITE_QOS_WR_QOS_Pos 0
#define AXIMX_ASIB0_WRITE_QOS_WR_QOS_Msk (0xfu << AXIMX_ASIB0_WRITE_QOS_WR_QOS_Pos) /**< \brief (AXIMX_ASIB0_WRITE_QOS) Write QoS */
#define AXIMX_ASIB0_WRITE_QOS_WR_QOS(value) ((AXIMX_ASIB0_WRITE_QOS_WR_QOS_Msk & ((value) << AXIMX_ASIB0_WRITE_QOS_WR_QOS_Pos)))
/* -------- AXIMX_ASIB1_FN_MOD_AHB : (AXIMX Offset: 0x43028) ASIB1 AHB Functionality Modification Register -------- */
#define AXIMX_ASIB1_FN_MOD_AHB_RD_INCR_OVR (0x1u << 0) /**< \brief (AXIMX_ASIB1_FN_MOD_AHB) Read INCR Override */
#define AXIMX_ASIB1_FN_MOD_AHB_WR_INCR_OVR (0x1u << 1) /**< \brief (AXIMX_ASIB1_FN_MOD_AHB) Write INCR override */
#define AXIMX_ASIB1_FN_MOD_AHB_LOCK_OVR (0x1u << 2) /**< \brief (AXIMX_ASIB1_FN_MOD_AHB) Lock Override */
/* -------- AXIMX_ASIB1_READ_QOS : (AXIMX Offset: 0x43100) ASIB1 Read Channel QoS Register -------- */
#define AXIMX_ASIB1_READ_QOS_RD_QOS_Pos 0
#define AXIMX_ASIB1_READ_QOS_RD_QOS_Msk (0xfu << AXIMX_ASIB1_READ_QOS_RD_QOS_Pos) /**< \brief (AXIMX_ASIB1_READ_QOS) Read QoS */
#define AXIMX_ASIB1_READ_QOS_RD_QOS(value) ((AXIMX_ASIB1_READ_QOS_RD_QOS_Msk & ((value) << AXIMX_ASIB1_READ_QOS_RD_QOS_Pos)))
/* -------- AXIMX_ASIB1_WRITE_QOS : (AXIMX Offset: 0x43104) ASIB1 Write Channel QoS Register -------- */
#define AXIMX_ASIB1_WRITE_QOS_WR_QOS_Pos 0
#define AXIMX_ASIB1_WRITE_QOS_WR_QOS_Msk (0xfu << AXIMX_ASIB1_WRITE_QOS_WR_QOS_Pos) /**< \brief (AXIMX_ASIB1_WRITE_QOS) Write QoS */
#define AXIMX_ASIB1_WRITE_QOS_WR_QOS(value) ((AXIMX_ASIB1_WRITE_QOS_WR_QOS_Msk & ((value) << AXIMX_ASIB1_WRITE_QOS_WR_QOS_Pos)))
/* -------- AXIMX_ASIB1_FN_MOD : (AXIMX Offset: 0x43108) ASIB1 Issuing Functionality Modification Register -------- */
#define AXIMX_ASIB1_FN_MOD_RD_ISS (0x1u << 0) /**< \brief (AXIMX_ASIB1_FN_MOD) Read Issuing */
#define AXIMX_ASIB1_FN_MOD_WR_ISS (0x1u << 1) /**< \brief (AXIMX_ASIB1_FN_MOD) Write Issuing */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Boot Sequence Controller */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_BSC Boot Sequence Controller */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Bsc hardware registers */
typedef struct {
  RwReg BSC_CR; /**< \brief (Bsc Offset: 0x0) Boot Sequence Configuration Register */
} Bsc;
#endif /* __ASSEMBLY__ */
/* -------- BSC_CR : (BSC Offset: 0x0) Boot Sequence Configuration Register -------- */
#define BSC_CR_BOOT_Pos 0
#define BSC_CR_BOOT_Msk (0xffffffu << BSC_CR_BOOT_Pos) /**< \brief (BSC_CR)  */
#define BSC_CR_BOOT(value) ((BSC_CR_BOOT_Msk & ((value) << BSC_CR_BOOT_Pos)))
#define BSC_CR_BOOTKEY_Pos 24
#define BSC_CR_BOOTKEY_Msk (0xffu << BSC_CR_BOOTKEY_Pos) /**< \brief (BSC_CR)  */
#define   BSC_CR_BOOTKEY_VALID (0xB5u << 24) /**< \brief (BSC_CR) valid boot key */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Debug Unit */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_DBGU Debug Unit */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Dbgu hardware registers */
typedef struct {
  WoReg DBGU_CR;      /**< \brief (Dbgu Offset: 0x0000) Control Register */
  RwReg DBGU_MR;      /**< \brief (Dbgu Offset: 0x0004) Mode Register */
  WoReg DBGU_IER;     /**< \brief (Dbgu Offset: 0x0008) Interrupt Enable Register */
  WoReg DBGU_IDR;     /**< \brief (Dbgu Offset: 0x000C) Interrupt Disable Register */
  RoReg DBGU_IMR;     /**< \brief (Dbgu Offset: 0x0010) Interrupt Mask Register */
  RoReg DBGU_SR;      /**< \brief (Dbgu Offset: 0x0014) Status Register */
  RoReg DBGU_RHR;     /**< \brief (Dbgu Offset: 0x0018) Receive Holding Register */
  WoReg DBGU_THR;     /**< \brief (Dbgu Offset: 0x001C) Transmit Holding Register */
  RwReg DBGU_BRGR;    /**< \brief (Dbgu Offset: 0x0020) Baud Rate Generator Register */
  RoReg Reserved1[7];
  RoReg DBGU_CIDR;    /**< \brief (Dbgu Offset: 0x0040) Chip ID Register */
  RoReg DBGU_EXID;    /**< \brief (Dbgu Offset: 0x0044) Chip ID Extension Register */
  RwReg DBGU_FNR;     /**< \brief (Dbgu Offset: 0x0048) Force NTRST Register */
} Dbgu;
#endif /* __ASSEMBLY__ */
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
#define   DBGU_CIDR_EPROC_CA5 (0x6u << 5) /**< \brief (DBGU_CIDR) Cortex-A5 */
#define DBGU_CIDR_NVPSIZ_Pos 8
#define DBGU_CIDR_NVPSIZ_Msk (0xfu << DBGU_CIDR_NVPSIZ_Pos) /**< \brief (DBGU_CIDR) Nonvolatile Program Memory Size */
#define   DBGU_CIDR_NVPSIZ_NONE (0x0u << 8) /**< \brief (DBGU_CIDR) None */
#define   DBGU_CIDR_NVPSIZ_8K (0x1u << 8) /**< \brief (DBGU_CIDR) 8K bytes */
#define   DBGU_CIDR_NVPSIZ_16K (0x2u << 8) /**< \brief (DBGU_CIDR) 16K bytes */
#define   DBGU_CIDR_NVPSIZ_32K (0x3u << 8) /**< \brief (DBGU_CIDR) 32K bytes */
#define   DBGU_CIDR_NVPSIZ_64K (0x5u << 8) /**< \brief (DBGU_CIDR) 64K bytes */
#define   DBGU_CIDR_NVPSIZ_128K (0x7u << 8) /**< \brief (DBGU_CIDR) 128K bytes */
#define   DBGU_CIDR_NVPSIZ_256K (0x9u << 8) /**< \brief (DBGU_CIDR) 256K bytes */
#define   DBGU_CIDR_NVPSIZ_512K (0xAu << 8) /**< \brief (DBGU_CIDR) 512K bytes */
#define   DBGU_CIDR_NVPSIZ_1024K (0xCu << 8) /**< \brief (DBGU_CIDR) 1024K bytes */
#define   DBGU_CIDR_NVPSIZ_2048K (0xEu << 8) /**< \brief (DBGU_CIDR) 2048K bytes */
#define DBGU_CIDR_NVPSIZ2_Pos 12
#define DBGU_CIDR_NVPSIZ2_Msk (0xfu << DBGU_CIDR_NVPSIZ2_Pos) /**< \brief (DBGU_CIDR)  */
#define   DBGU_CIDR_NVPSIZ2_NONE (0x0u << 12) /**< \brief (DBGU_CIDR) None */
#define   DBGU_CIDR_NVPSIZ2_8K (0x1u << 12) /**< \brief (DBGU_CIDR) 8K bytes */
#define   DBGU_CIDR_NVPSIZ2_16K (0x2u << 12) /**< \brief (DBGU_CIDR) 16K bytes */
#define   DBGU_CIDR_NVPSIZ2_32K (0x3u << 12) /**< \brief (DBGU_CIDR) 32K bytes */
#define   DBGU_CIDR_NVPSIZ2_64K (0x5u << 12) /**< \brief (DBGU_CIDR) 64K bytes */
#define   DBGU_CIDR_NVPSIZ2_128K (0x7u << 12) /**< \brief (DBGU_CIDR) 128K bytes */
#define   DBGU_CIDR_NVPSIZ2_256K (0x9u << 12) /**< \brief (DBGU_CIDR) 256K bytes */
#define   DBGU_CIDR_NVPSIZ2_512K (0xAu << 12) /**< \brief (DBGU_CIDR) 512K bytes */
#define   DBGU_CIDR_NVPSIZ2_1024K (0xCu << 12) /**< \brief (DBGU_CIDR) 1024K bytes */
#define   DBGU_CIDR_NVPSIZ2_2048K (0xEu << 12) /**< \brief (DBGU_CIDR) 2048K bytes */
#define DBGU_CIDR_SRAMSIZ_Pos 16
#define DBGU_CIDR_SRAMSIZ_Msk (0xfu << DBGU_CIDR_SRAMSIZ_Pos) /**< \brief (DBGU_CIDR) Internal SRAM Size */
#define   DBGU_CIDR_SRAMSIZ_1K (0x1u << 16) /**< \brief (DBGU_CIDR) 1K bytes */
#define   DBGU_CIDR_SRAMSIZ_2K (0x2u << 16) /**< \brief (DBGU_CIDR) 2K bytes */
#define   DBGU_CIDR_SRAMSIZ_6K (0x3u << 16) /**< \brief (DBGU_CIDR) 6K bytes */
#define   DBGU_CIDR_SRAMSIZ_112K (0x4u << 16) /**< \brief (DBGU_CIDR) 112K bytes */
#define   DBGU_CIDR_SRAMSIZ_4K (0x5u << 16) /**< \brief (DBGU_CIDR) 4K bytes */
#define   DBGU_CIDR_SRAMSIZ_80K (0x6u << 16) /**< \brief (DBGU_CIDR) 80K bytes */
#define   DBGU_CIDR_SRAMSIZ_160K (0x7u << 16) /**< \brief (DBGU_CIDR) 160K bytes */
#define   DBGU_CIDR_SRAMSIZ_8K (0x8u << 16) /**< \brief (DBGU_CIDR) 8K bytes */
#define   DBGU_CIDR_SRAMSIZ_16K (0x9u << 16) /**< \brief (DBGU_CIDR) 16K bytes */
#define   DBGU_CIDR_SRAMSIZ_32K (0xAu << 16) /**< \brief (DBGU_CIDR) 32K bytes */
#define   DBGU_CIDR_SRAMSIZ_64K (0xBu << 16) /**< \brief (DBGU_CIDR) 64K bytes */
#define   DBGU_CIDR_SRAMSIZ_128K (0xCu << 16) /**< \brief (DBGU_CIDR) 128K bytes */
#define   DBGU_CIDR_SRAMSIZ_256K (0xDu << 16) /**< \brief (DBGU_CIDR) 256K bytes */
#define   DBGU_CIDR_SRAMSIZ_96K (0xEu << 16) /**< \brief (DBGU_CIDR) 96K bytes */
#define   DBGU_CIDR_SRAMSIZ_512K (0xFu << 16) /**< \brief (DBGU_CIDR) 512K bytes */
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
/**  SOFTWARE API DEFINITION FOR DMA Controller */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_DMAC DMA Controller */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief DmacCh_num hardware registers */
typedef struct {
  RwReg       DMAC_SADDR;     /**< \brief (DmacCh_num Offset: 0x0) DMAC Channel Source Address Register */
  RwReg       DMAC_DADDR;     /**< \brief (DmacCh_num Offset: 0x4) DMAC Channel Destination Address Register */
  RwReg       DMAC_DSCR;      /**< \brief (DmacCh_num Offset: 0x8) DMAC Channel Descriptor Address Register */
  RwReg       DMAC_CTRLA;     /**< \brief (DmacCh_num Offset: 0xC) DMAC Channel Control A Register */
  RwReg       DMAC_CTRLB;     /**< \brief (DmacCh_num Offset: 0x10) DMAC Channel Control B Register */
  RwReg       DMAC_CFG;       /**< \brief (DmacCh_num Offset: 0x14) DMAC Channel Configuration Register */
  RwReg       DMAC_SPIP;      /**< \brief (DmacCh_num Offset: 0x18) DMAC Channel Source Picture-in-Picture Configuration Register */
  RwReg       DMAC_DPIP;      /**< \brief (DmacCh_num Offset: 0x1C) DMAC Channel Destination Picture-in-Picture Configuration Register */
  RoReg       Reserved1[2];
} DmacCh_num;
/** \brief Dmac hardware registers */
#define DMACCH_NUM_NUMBER 8
typedef struct {
  RwReg       DMAC_GCFG;      /**< \brief (Dmac Offset: 0x000) DMAC Global Configuration Register */
  RwReg       DMAC_EN;        /**< \brief (Dmac Offset: 0x004) DMAC Enable Register */
  RwReg       DMAC_SREQ;      /**< \brief (Dmac Offset: 0x008) DMAC Software Single Request Register */
  RwReg       DMAC_CREQ;      /**< \brief (Dmac Offset: 0x00C) DMAC Software Chunk Transfer Request Register */
  RwReg       DMAC_LAST;      /**< \brief (Dmac Offset: 0x010) DMAC Software Last Transfer Flag Register */
  RoReg       Reserved1[1];
  WoReg       DMAC_EBCIER;    /**< \brief (Dmac Offset: 0x018) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Enable register. */
  WoReg       DMAC_EBCIDR;    /**< \brief (Dmac Offset: 0x01C) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Disable register. */
  RoReg       DMAC_EBCIMR;    /**< \brief (Dmac Offset: 0x020) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Mask Register. */
  RoReg       DMAC_EBCISR;    /**< \brief (Dmac Offset: 0x024) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Status Register. */
  WoReg       DMAC_CHER;      /**< \brief (Dmac Offset: 0x028) DMAC Channel Handler Enable Register */
  WoReg       DMAC_CHDR;      /**< \brief (Dmac Offset: 0x02C) DMAC Channel Handler Disable Register */
  RoReg       DMAC_CHSR;      /**< \brief (Dmac Offset: 0x030) DMAC Channel Handler Status Register */
  RoReg       Reserved2[2];
  DmacCh_num  DMAC_CH_NUM[DMACCH_NUM_NUMBER]; /**< \brief (Dmac Offset: 0x3C) ch_num = 0 .. 7 */
  RoReg       Reserved3[26];
  RwReg       DMAC_WPMR;      /**< \brief (Dmac Offset: 0x1E4) DMAC Write Protect Mode Register */
  RoReg       DMAC_WPSR;      /**< \brief (Dmac Offset: 0x1E8) DMAC Write Protect Status Register */
} Dmac;
#endif /* __ASSEMBLY__ */
/* -------- DMAC_GCFG : (DMAC Offset: 0x000) DMAC Global Configuration Register -------- */
#define DMAC_GCFG_ARB_CFG (0x1u << 4) /**< \brief (DMAC_GCFG) Arbiter Configuration */
#define   DMAC_GCFG_ARB_CFG_FIXED (0x0u << 4) /**< \brief (DMAC_GCFG) Fixed priority arbiter. */
#define   DMAC_GCFG_ARB_CFG_ROUND_ROBIN (0x1u << 4) /**< \brief (DMAC_GCFG) Modified round robin arbiter. */
#define DMAC_GCFG_DICEN (0x1u << 8) /**< \brief (DMAC_GCFG) Descriptor Integrity Check */
/* -------- DMAC_EN : (DMAC Offset: 0x004) DMAC Enable Register -------- */
#define DMAC_EN_ENABLE (0x1u << 0) /**< \brief (DMAC_EN)  */
/* -------- DMAC_SREQ : (DMAC Offset: 0x008) DMAC Software Single Request Register -------- */
#define DMAC_SREQ_SSREQ0 (0x1u << 0) /**< \brief (DMAC_SREQ) Source Request */
#define DMAC_SREQ_DSREQ0 (0x1u << 1) /**< \brief (DMAC_SREQ) Destination Request */
#define DMAC_SREQ_SSREQ1 (0x1u << 2) /**< \brief (DMAC_SREQ) Source Request */
#define DMAC_SREQ_DSREQ1 (0x1u << 3) /**< \brief (DMAC_SREQ) Destination Request */
#define DMAC_SREQ_SSREQ2 (0x1u << 4) /**< \brief (DMAC_SREQ) Source Request */
#define DMAC_SREQ_DSREQ2 (0x1u << 5) /**< \brief (DMAC_SREQ) Destination Request */
#define DMAC_SREQ_SSREQ3 (0x1u << 6) /**< \brief (DMAC_SREQ) Source Request */
#define DMAC_SREQ_DSREQ3 (0x1u << 7) /**< \brief (DMAC_SREQ) Destination Request */
#define DMAC_SREQ_SSREQ4 (0x1u << 8) /**< \brief (DMAC_SREQ) Source Request */
#define DMAC_SREQ_DSREQ4 (0x1u << 9) /**< \brief (DMAC_SREQ) Destination Request */
#define DMAC_SREQ_SSREQ5 (0x1u << 10) /**< \brief (DMAC_SREQ) Source Request */
#define DMAC_SREQ_DSREQ5 (0x1u << 11) /**< \brief (DMAC_SREQ) Destination Request */
#define DMAC_SREQ_SSREQ6 (0x1u << 12) /**< \brief (DMAC_SREQ) Source Request */
#define DMAC_SREQ_DSREQ6 (0x1u << 13) /**< \brief (DMAC_SREQ) Destination Request */
#define DMAC_SREQ_SSREQ7 (0x1u << 14) /**< \brief (DMAC_SREQ) Source Request */
#define DMAC_SREQ_DSREQ7 (0x1u << 15) /**< \brief (DMAC_SREQ) Destination Request */
/* -------- DMAC_CREQ : (DMAC Offset: 0x00C) DMAC Software Chunk Transfer Request Register -------- */
#define DMAC_CREQ_SCREQ0 (0x1u << 0) /**< \brief (DMAC_CREQ) Source Chunk Request */
#define DMAC_CREQ_DCREQ0 (0x1u << 1) /**< \brief (DMAC_CREQ) Destination Chunk Request */
#define DMAC_CREQ_SCREQ1 (0x1u << 2) /**< \brief (DMAC_CREQ) Source Chunk Request */
#define DMAC_CREQ_DCREQ1 (0x1u << 3) /**< \brief (DMAC_CREQ) Destination Chunk Request */
#define DMAC_CREQ_SCREQ2 (0x1u << 4) /**< \brief (DMAC_CREQ) Source Chunk Request */
#define DMAC_CREQ_DCREQ2 (0x1u << 5) /**< \brief (DMAC_CREQ) Destination Chunk Request */
#define DMAC_CREQ_SCREQ3 (0x1u << 6) /**< \brief (DMAC_CREQ) Source Chunk Request */
#define DMAC_CREQ_DCREQ3 (0x1u << 7) /**< \brief (DMAC_CREQ) Destination Chunk Request */
#define DMAC_CREQ_SCREQ4 (0x1u << 8) /**< \brief (DMAC_CREQ) Source Chunk Request */
#define DMAC_CREQ_DCREQ4 (0x1u << 9) /**< \brief (DMAC_CREQ) Destination Chunk Request */
#define DMAC_CREQ_SCREQ5 (0x1u << 10) /**< \brief (DMAC_CREQ) Source Chunk Request */
#define DMAC_CREQ_DCREQ5 (0x1u << 11) /**< \brief (DMAC_CREQ) Destination Chunk Request */
#define DMAC_CREQ_SCREQ6 (0x1u << 12) /**< \brief (DMAC_CREQ) Source Chunk Request */
#define DMAC_CREQ_DCREQ6 (0x1u << 13) /**< \brief (DMAC_CREQ) Destination Chunk Request */
#define DMAC_CREQ_SCREQ7 (0x1u << 14) /**< \brief (DMAC_CREQ) Source Chunk Request */
#define DMAC_CREQ_DCREQ7 (0x1u << 15) /**< \brief (DMAC_CREQ) Destination Chunk Request */
/* -------- DMAC_LAST : (DMAC Offset: 0x010) DMAC Software Last Transfer Flag Register -------- */
#define DMAC_LAST_SLAST0 (0x1u << 0) /**< \brief (DMAC_LAST) Source Last */
#define DMAC_LAST_DLAST0 (0x1u << 1) /**< \brief (DMAC_LAST) Destination Last */
#define DMAC_LAST_SLAST1 (0x1u << 2) /**< \brief (DMAC_LAST) Source Last */
#define DMAC_LAST_DLAST1 (0x1u << 3) /**< \brief (DMAC_LAST) Destination Last */
#define DMAC_LAST_SLAST2 (0x1u << 4) /**< \brief (DMAC_LAST) Source Last */
#define DMAC_LAST_DLAST2 (0x1u << 5) /**< \brief (DMAC_LAST) Destination Last */
#define DMAC_LAST_SLAST3 (0x1u << 6) /**< \brief (DMAC_LAST) Source Last */
#define DMAC_LAST_DLAST3 (0x1u << 7) /**< \brief (DMAC_LAST) Destination Last */
#define DMAC_LAST_SLAST4 (0x1u << 8) /**< \brief (DMAC_LAST) Source Last */
#define DMAC_LAST_DLAST4 (0x1u << 9) /**< \brief (DMAC_LAST) Destination Last */
#define DMAC_LAST_SLAST5 (0x1u << 10) /**< \brief (DMAC_LAST) Source Last */
#define DMAC_LAST_DLAST5 (0x1u << 11) /**< \brief (DMAC_LAST) Destination Last */
#define DMAC_LAST_SLAST6 (0x1u << 12) /**< \brief (DMAC_LAST) Source Last */
#define DMAC_LAST_DLAST6 (0x1u << 13) /**< \brief (DMAC_LAST) Destination Last */
#define DMAC_LAST_SLAST7 (0x1u << 14) /**< \brief (DMAC_LAST) Source Last */
#define DMAC_LAST_DLAST7 (0x1u << 15) /**< \brief (DMAC_LAST) Destination Last */
/* -------- DMAC_EBCIER : (DMAC Offset: 0x018) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Enable register. -------- */
#define DMAC_EBCIER_BTC0 (0x1u << 0) /**< \brief (DMAC_EBCIER) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_BTC1 (0x1u << 1) /**< \brief (DMAC_EBCIER) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_BTC2 (0x1u << 2) /**< \brief (DMAC_EBCIER) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_BTC3 (0x1u << 3) /**< \brief (DMAC_EBCIER) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_BTC4 (0x1u << 4) /**< \brief (DMAC_EBCIER) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_BTC5 (0x1u << 5) /**< \brief (DMAC_EBCIER) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_BTC6 (0x1u << 6) /**< \brief (DMAC_EBCIER) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_BTC7 (0x1u << 7) /**< \brief (DMAC_EBCIER) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_CBTC0 (0x1u << 8) /**< \brief (DMAC_EBCIER) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_CBTC1 (0x1u << 9) /**< \brief (DMAC_EBCIER) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_CBTC2 (0x1u << 10) /**< \brief (DMAC_EBCIER) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_CBTC3 (0x1u << 11) /**< \brief (DMAC_EBCIER) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_CBTC4 (0x1u << 12) /**< \brief (DMAC_EBCIER) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_CBTC5 (0x1u << 13) /**< \brief (DMAC_EBCIER) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_CBTC6 (0x1u << 14) /**< \brief (DMAC_EBCIER) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_CBTC7 (0x1u << 15) /**< \brief (DMAC_EBCIER) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIER_ERR0 (0x1u << 16) /**< \brief (DMAC_EBCIER) Access Error [7:0] */
#define DMAC_EBCIER_ERR1 (0x1u << 17) /**< \brief (DMAC_EBCIER) Access Error [7:0] */
#define DMAC_EBCIER_ERR2 (0x1u << 18) /**< \brief (DMAC_EBCIER) Access Error [7:0] */
#define DMAC_EBCIER_ERR3 (0x1u << 19) /**< \brief (DMAC_EBCIER) Access Error [7:0] */
#define DMAC_EBCIER_ERR4 (0x1u << 20) /**< \brief (DMAC_EBCIER) Access Error [7:0] */
#define DMAC_EBCIER_ERR5 (0x1u << 21) /**< \brief (DMAC_EBCIER) Access Error [7:0] */
#define DMAC_EBCIER_ERR6 (0x1u << 22) /**< \brief (DMAC_EBCIER) Access Error [7:0] */
#define DMAC_EBCIER_ERR7 (0x1u << 23) /**< \brief (DMAC_EBCIER) Access Error [7:0] */
#define DMAC_EBCIER_DICERR0 (0x1u << 24) /**< \brief (DMAC_EBCIER) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIER_DICERR1 (0x1u << 25) /**< \brief (DMAC_EBCIER) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIER_DICERR2 (0x1u << 26) /**< \brief (DMAC_EBCIER) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIER_DICERR3 (0x1u << 27) /**< \brief (DMAC_EBCIER) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIER_DICERR4 (0x1u << 28) /**< \brief (DMAC_EBCIER) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIER_DICERR5 (0x1u << 29) /**< \brief (DMAC_EBCIER) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIER_DICERR6 (0x1u << 30) /**< \brief (DMAC_EBCIER) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIER_DICERR7 (0x1u << 31) /**< \brief (DMAC_EBCIER) Descriptor Integrity Check Error [7:0] */
/* -------- DMAC_EBCIDR : (DMAC Offset: 0x01C) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Disable register. -------- */
#define DMAC_EBCIDR_BTC0 (0x1u << 0) /**< \brief (DMAC_EBCIDR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_BTC1 (0x1u << 1) /**< \brief (DMAC_EBCIDR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_BTC2 (0x1u << 2) /**< \brief (DMAC_EBCIDR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_BTC3 (0x1u << 3) /**< \brief (DMAC_EBCIDR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_BTC4 (0x1u << 4) /**< \brief (DMAC_EBCIDR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_BTC5 (0x1u << 5) /**< \brief (DMAC_EBCIDR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_BTC6 (0x1u << 6) /**< \brief (DMAC_EBCIDR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_BTC7 (0x1u << 7) /**< \brief (DMAC_EBCIDR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_CBTC0 (0x1u << 8) /**< \brief (DMAC_EBCIDR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_CBTC1 (0x1u << 9) /**< \brief (DMAC_EBCIDR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_CBTC2 (0x1u << 10) /**< \brief (DMAC_EBCIDR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_CBTC3 (0x1u << 11) /**< \brief (DMAC_EBCIDR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_CBTC4 (0x1u << 12) /**< \brief (DMAC_EBCIDR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_CBTC5 (0x1u << 13) /**< \brief (DMAC_EBCIDR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_CBTC6 (0x1u << 14) /**< \brief (DMAC_EBCIDR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_CBTC7 (0x1u << 15) /**< \brief (DMAC_EBCIDR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIDR_ERR0 (0x1u << 16) /**< \brief (DMAC_EBCIDR) Access Error [7:0] */
#define DMAC_EBCIDR_ERR1 (0x1u << 17) /**< \brief (DMAC_EBCIDR) Access Error [7:0] */
#define DMAC_EBCIDR_ERR2 (0x1u << 18) /**< \brief (DMAC_EBCIDR) Access Error [7:0] */
#define DMAC_EBCIDR_ERR3 (0x1u << 19) /**< \brief (DMAC_EBCIDR) Access Error [7:0] */
#define DMAC_EBCIDR_ERR4 (0x1u << 20) /**< \brief (DMAC_EBCIDR) Access Error [7:0] */
#define DMAC_EBCIDR_ERR5 (0x1u << 21) /**< \brief (DMAC_EBCIDR) Access Error [7:0] */
#define DMAC_EBCIDR_ERR6 (0x1u << 22) /**< \brief (DMAC_EBCIDR) Access Error [7:0] */
#define DMAC_EBCIDR_ERR7 (0x1u << 23) /**< \brief (DMAC_EBCIDR) Access Error [7:0] */
#define DMAC_EBCIDR_DICERR0 (0x1u << 24) /**< \brief (DMAC_EBCIDR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIDR_DICERR1 (0x1u << 25) /**< \brief (DMAC_EBCIDR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIDR_DICERR2 (0x1u << 26) /**< \brief (DMAC_EBCIDR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIDR_DICERR3 (0x1u << 27) /**< \brief (DMAC_EBCIDR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIDR_DICERR4 (0x1u << 28) /**< \brief (DMAC_EBCIDR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIDR_DICERR5 (0x1u << 29) /**< \brief (DMAC_EBCIDR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIDR_DICERR6 (0x1u << 30) /**< \brief (DMAC_EBCIDR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIDR_DICERR7 (0x1u << 31) /**< \brief (DMAC_EBCIDR) Descriptor Integrity Check Error [7:0] */
/* -------- DMAC_EBCIMR : (DMAC Offset: 0x020) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Mask Register. -------- */
#define DMAC_EBCIMR_BTC0 (0x1u << 0) /**< \brief (DMAC_EBCIMR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_BTC1 (0x1u << 1) /**< \brief (DMAC_EBCIMR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_BTC2 (0x1u << 2) /**< \brief (DMAC_EBCIMR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_BTC3 (0x1u << 3) /**< \brief (DMAC_EBCIMR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_BTC4 (0x1u << 4) /**< \brief (DMAC_EBCIMR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_BTC5 (0x1u << 5) /**< \brief (DMAC_EBCIMR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_BTC6 (0x1u << 6) /**< \brief (DMAC_EBCIMR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_BTC7 (0x1u << 7) /**< \brief (DMAC_EBCIMR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_CBTC0 (0x1u << 8) /**< \brief (DMAC_EBCIMR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_CBTC1 (0x1u << 9) /**< \brief (DMAC_EBCIMR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_CBTC2 (0x1u << 10) /**< \brief (DMAC_EBCIMR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_CBTC3 (0x1u << 11) /**< \brief (DMAC_EBCIMR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_CBTC4 (0x1u << 12) /**< \brief (DMAC_EBCIMR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_CBTC5 (0x1u << 13) /**< \brief (DMAC_EBCIMR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_CBTC6 (0x1u << 14) /**< \brief (DMAC_EBCIMR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_CBTC7 (0x1u << 15) /**< \brief (DMAC_EBCIMR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCIMR_ERR0 (0x1u << 16) /**< \brief (DMAC_EBCIMR) Access Error [7:0] */
#define DMAC_EBCIMR_ERR1 (0x1u << 17) /**< \brief (DMAC_EBCIMR) Access Error [7:0] */
#define DMAC_EBCIMR_ERR2 (0x1u << 18) /**< \brief (DMAC_EBCIMR) Access Error [7:0] */
#define DMAC_EBCIMR_ERR3 (0x1u << 19) /**< \brief (DMAC_EBCIMR) Access Error [7:0] */
#define DMAC_EBCIMR_ERR4 (0x1u << 20) /**< \brief (DMAC_EBCIMR) Access Error [7:0] */
#define DMAC_EBCIMR_ERR5 (0x1u << 21) /**< \brief (DMAC_EBCIMR) Access Error [7:0] */
#define DMAC_EBCIMR_ERR6 (0x1u << 22) /**< \brief (DMAC_EBCIMR) Access Error [7:0] */
#define DMAC_EBCIMR_ERR7 (0x1u << 23) /**< \brief (DMAC_EBCIMR) Access Error [7:0] */
#define DMAC_EBCIMR_DICERR0 (0x1u << 24) /**< \brief (DMAC_EBCIMR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIMR_DICERR1 (0x1u << 25) /**< \brief (DMAC_EBCIMR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIMR_DICERR2 (0x1u << 26) /**< \brief (DMAC_EBCIMR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIMR_DICERR3 (0x1u << 27) /**< \brief (DMAC_EBCIMR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIMR_DICERR4 (0x1u << 28) /**< \brief (DMAC_EBCIMR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIMR_DICERR5 (0x1u << 29) /**< \brief (DMAC_EBCIMR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIMR_DICERR6 (0x1u << 30) /**< \brief (DMAC_EBCIMR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCIMR_DICERR7 (0x1u << 31) /**< \brief (DMAC_EBCIMR) Descriptor Integrity Check Error [7:0] */
/* -------- DMAC_EBCISR : (DMAC Offset: 0x024) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Status Register. -------- */
#define DMAC_EBCISR_BTC0 (0x1u << 0) /**< \brief (DMAC_EBCISR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_BTC1 (0x1u << 1) /**< \brief (DMAC_EBCISR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_BTC2 (0x1u << 2) /**< \brief (DMAC_EBCISR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_BTC3 (0x1u << 3) /**< \brief (DMAC_EBCISR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_BTC4 (0x1u << 4) /**< \brief (DMAC_EBCISR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_BTC5 (0x1u << 5) /**< \brief (DMAC_EBCISR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_BTC6 (0x1u << 6) /**< \brief (DMAC_EBCISR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_BTC7 (0x1u << 7) /**< \brief (DMAC_EBCISR) Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_CBTC0 (0x1u << 8) /**< \brief (DMAC_EBCISR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_CBTC1 (0x1u << 9) /**< \brief (DMAC_EBCISR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_CBTC2 (0x1u << 10) /**< \brief (DMAC_EBCISR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_CBTC3 (0x1u << 11) /**< \brief (DMAC_EBCISR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_CBTC4 (0x1u << 12) /**< \brief (DMAC_EBCISR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_CBTC5 (0x1u << 13) /**< \brief (DMAC_EBCISR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_CBTC6 (0x1u << 14) /**< \brief (DMAC_EBCISR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_CBTC7 (0x1u << 15) /**< \brief (DMAC_EBCISR) Chained Buffer Transfer Completed [7:0] */
#define DMAC_EBCISR_ERR0 (0x1u << 16) /**< \brief (DMAC_EBCISR) Access Error [7:0] */
#define DMAC_EBCISR_ERR1 (0x1u << 17) /**< \brief (DMAC_EBCISR) Access Error [7:0] */
#define DMAC_EBCISR_ERR2 (0x1u << 18) /**< \brief (DMAC_EBCISR) Access Error [7:0] */
#define DMAC_EBCISR_ERR3 (0x1u << 19) /**< \brief (DMAC_EBCISR) Access Error [7:0] */
#define DMAC_EBCISR_ERR4 (0x1u << 20) /**< \brief (DMAC_EBCISR) Access Error [7:0] */
#define DMAC_EBCISR_ERR5 (0x1u << 21) /**< \brief (DMAC_EBCISR) Access Error [7:0] */
#define DMAC_EBCISR_ERR6 (0x1u << 22) /**< \brief (DMAC_EBCISR) Access Error [7:0] */
#define DMAC_EBCISR_ERR7 (0x1u << 23) /**< \brief (DMAC_EBCISR) Access Error [7:0] */
#define DMAC_EBCISR_DICERR0 (0x1u << 24) /**< \brief (DMAC_EBCISR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCISR_DICERR1 (0x1u << 25) /**< \brief (DMAC_EBCISR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCISR_DICERR2 (0x1u << 26) /**< \brief (DMAC_EBCISR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCISR_DICERR3 (0x1u << 27) /**< \brief (DMAC_EBCISR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCISR_DICERR4 (0x1u << 28) /**< \brief (DMAC_EBCISR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCISR_DICERR5 (0x1u << 29) /**< \brief (DMAC_EBCISR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCISR_DICERR6 (0x1u << 30) /**< \brief (DMAC_EBCISR) Descriptor Integrity Check Error [7:0] */
#define DMAC_EBCISR_DICERR7 (0x1u << 31) /**< \brief (DMAC_EBCISR) Descriptor Integrity Check Error [7:0] */
/* -------- DMAC_CHER : (DMAC Offset: 0x028) DMAC Channel Handler Enable Register -------- */
#define DMAC_CHER_ENA0 (0x1u << 0) /**< \brief (DMAC_CHER) Enable [7:0] */
#define DMAC_CHER_ENA1 (0x1u << 1) /**< \brief (DMAC_CHER) Enable [7:0] */
#define DMAC_CHER_ENA2 (0x1u << 2) /**< \brief (DMAC_CHER) Enable [7:0] */
#define DMAC_CHER_ENA3 (0x1u << 3) /**< \brief (DMAC_CHER) Enable [7:0] */
#define DMAC_CHER_ENA4 (0x1u << 4) /**< \brief (DMAC_CHER) Enable [7:0] */
#define DMAC_CHER_ENA5 (0x1u << 5) /**< \brief (DMAC_CHER) Enable [7:0] */
#define DMAC_CHER_ENA6 (0x1u << 6) /**< \brief (DMAC_CHER) Enable [7:0] */
#define DMAC_CHER_ENA7 (0x1u << 7) /**< \brief (DMAC_CHER) Enable [7:0] */
#define DMAC_CHER_SUSP0 (0x1u << 8) /**< \brief (DMAC_CHER) Suspend [7:0] */
#define DMAC_CHER_SUSP1 (0x1u << 9) /**< \brief (DMAC_CHER) Suspend [7:0] */
#define DMAC_CHER_SUSP2 (0x1u << 10) /**< \brief (DMAC_CHER) Suspend [7:0] */
#define DMAC_CHER_SUSP3 (0x1u << 11) /**< \brief (DMAC_CHER) Suspend [7:0] */
#define DMAC_CHER_SUSP4 (0x1u << 12) /**< \brief (DMAC_CHER) Suspend [7:0] */
#define DMAC_CHER_SUSP5 (0x1u << 13) /**< \brief (DMAC_CHER) Suspend [7:0] */
#define DMAC_CHER_SUSP6 (0x1u << 14) /**< \brief (DMAC_CHER) Suspend [7:0] */
#define DMAC_CHER_SUSP7 (0x1u << 15) /**< \brief (DMAC_CHER) Suspend [7:0] */
#define DMAC_CHER_KEEP0 (0x1u << 24) /**< \brief (DMAC_CHER) Keep on [7:0] */
#define DMAC_CHER_KEEP1 (0x1u << 25) /**< \brief (DMAC_CHER) Keep on [7:0] */
#define DMAC_CHER_KEEP2 (0x1u << 26) /**< \brief (DMAC_CHER) Keep on [7:0] */
#define DMAC_CHER_KEEP3 (0x1u << 27) /**< \brief (DMAC_CHER) Keep on [7:0] */
#define DMAC_CHER_KEEP4 (0x1u << 28) /**< \brief (DMAC_CHER) Keep on [7:0] */
#define DMAC_CHER_KEEP5 (0x1u << 29) /**< \brief (DMAC_CHER) Keep on [7:0] */
#define DMAC_CHER_KEEP6 (0x1u << 30) /**< \brief (DMAC_CHER) Keep on [7:0] */
#define DMAC_CHER_KEEP7 (0x1u << 31) /**< \brief (DMAC_CHER) Keep on [7:0] */
/* -------- DMAC_CHDR : (DMAC Offset: 0x02C) DMAC Channel Handler Disable Register -------- */
#define DMAC_CHDR_DIS0 (0x1u << 0) /**< \brief (DMAC_CHDR) Disable [7:0] */
#define DMAC_CHDR_DIS1 (0x1u << 1) /**< \brief (DMAC_CHDR) Disable [7:0] */
#define DMAC_CHDR_DIS2 (0x1u << 2) /**< \brief (DMAC_CHDR) Disable [7:0] */
#define DMAC_CHDR_DIS3 (0x1u << 3) /**< \brief (DMAC_CHDR) Disable [7:0] */
#define DMAC_CHDR_DIS4 (0x1u << 4) /**< \brief (DMAC_CHDR) Disable [7:0] */
#define DMAC_CHDR_DIS5 (0x1u << 5) /**< \brief (DMAC_CHDR) Disable [7:0] */
#define DMAC_CHDR_DIS6 (0x1u << 6) /**< \brief (DMAC_CHDR) Disable [7:0] */
#define DMAC_CHDR_DIS7 (0x1u << 7) /**< \brief (DMAC_CHDR) Disable [7:0] */
#define DMAC_CHDR_RES0 (0x1u << 8) /**< \brief (DMAC_CHDR) Resume [7:0] */
#define DMAC_CHDR_RES1 (0x1u << 9) /**< \brief (DMAC_CHDR) Resume [7:0] */
#define DMAC_CHDR_RES2 (0x1u << 10) /**< \brief (DMAC_CHDR) Resume [7:0] */
#define DMAC_CHDR_RES3 (0x1u << 11) /**< \brief (DMAC_CHDR) Resume [7:0] */
#define DMAC_CHDR_RES4 (0x1u << 12) /**< \brief (DMAC_CHDR) Resume [7:0] */
#define DMAC_CHDR_RES5 (0x1u << 13) /**< \brief (DMAC_CHDR) Resume [7:0] */
#define DMAC_CHDR_RES6 (0x1u << 14) /**< \brief (DMAC_CHDR) Resume [7:0] */
#define DMAC_CHDR_RES7 (0x1u << 15) /**< \brief (DMAC_CHDR) Resume [7:0] */
/* -------- DMAC_CHSR : (DMAC Offset: 0x030) DMAC Channel Handler Status Register -------- */
#define DMAC_CHSR_ENA0 (0x1u << 0) /**< \brief (DMAC_CHSR) Enable [7:0] */
#define DMAC_CHSR_ENA1 (0x1u << 1) /**< \brief (DMAC_CHSR) Enable [7:0] */
#define DMAC_CHSR_ENA2 (0x1u << 2) /**< \brief (DMAC_CHSR) Enable [7:0] */
#define DMAC_CHSR_ENA3 (0x1u << 3) /**< \brief (DMAC_CHSR) Enable [7:0] */
#define DMAC_CHSR_ENA4 (0x1u << 4) /**< \brief (DMAC_CHSR) Enable [7:0] */
#define DMAC_CHSR_ENA5 (0x1u << 5) /**< \brief (DMAC_CHSR) Enable [7:0] */
#define DMAC_CHSR_ENA6 (0x1u << 6) /**< \brief (DMAC_CHSR) Enable [7:0] */
#define DMAC_CHSR_ENA7 (0x1u << 7) /**< \brief (DMAC_CHSR) Enable [7:0] */
#define DMAC_CHSR_SUSP0 (0x1u << 8) /**< \brief (DMAC_CHSR) Suspend [7:0] */
#define DMAC_CHSR_SUSP1 (0x1u << 9) /**< \brief (DMAC_CHSR) Suspend [7:0] */
#define DMAC_CHSR_SUSP2 (0x1u << 10) /**< \brief (DMAC_CHSR) Suspend [7:0] */
#define DMAC_CHSR_SUSP3 (0x1u << 11) /**< \brief (DMAC_CHSR) Suspend [7:0] */
#define DMAC_CHSR_SUSP4 (0x1u << 12) /**< \brief (DMAC_CHSR) Suspend [7:0] */
#define DMAC_CHSR_SUSP5 (0x1u << 13) /**< \brief (DMAC_CHSR) Suspend [7:0] */
#define DMAC_CHSR_SUSP6 (0x1u << 14) /**< \brief (DMAC_CHSR) Suspend [7:0] */
#define DMAC_CHSR_SUSP7 (0x1u << 15) /**< \brief (DMAC_CHSR) Suspend [7:0] */
#define DMAC_CHSR_EMPT0 (0x1u << 16) /**< \brief (DMAC_CHSR) Empty [7:0] */
#define DMAC_CHSR_EMPT1 (0x1u << 17) /**< \brief (DMAC_CHSR) Empty [7:0] */
#define DMAC_CHSR_EMPT2 (0x1u << 18) /**< \brief (DMAC_CHSR) Empty [7:0] */
#define DMAC_CHSR_EMPT3 (0x1u << 19) /**< \brief (DMAC_CHSR) Empty [7:0] */
#define DMAC_CHSR_EMPT4 (0x1u << 20) /**< \brief (DMAC_CHSR) Empty [7:0] */
#define DMAC_CHSR_EMPT5 (0x1u << 21) /**< \brief (DMAC_CHSR) Empty [7:0] */
#define DMAC_CHSR_EMPT6 (0x1u << 22) /**< \brief (DMAC_CHSR) Empty [7:0] */
#define DMAC_CHSR_EMPT7 (0x1u << 23) /**< \brief (DMAC_CHSR) Empty [7:0] */
#define DMAC_CHSR_STAL0 (0x1u << 24) /**< \brief (DMAC_CHSR) Stalled [7:0] */
#define DMAC_CHSR_STAL1 (0x1u << 25) /**< \brief (DMAC_CHSR) Stalled [7:0] */
#define DMAC_CHSR_STAL2 (0x1u << 26) /**< \brief (DMAC_CHSR) Stalled [7:0] */
#define DMAC_CHSR_STAL3 (0x1u << 27) /**< \brief (DMAC_CHSR) Stalled [7:0] */
#define DMAC_CHSR_STAL4 (0x1u << 28) /**< \brief (DMAC_CHSR) Stalled [7:0] */
#define DMAC_CHSR_STAL5 (0x1u << 29) /**< \brief (DMAC_CHSR) Stalled [7:0] */
#define DMAC_CHSR_STAL6 (0x1u << 30) /**< \brief (DMAC_CHSR) Stalled [7:0] */
#define DMAC_CHSR_STAL7 (0x1u << 31) /**< \brief (DMAC_CHSR) Stalled [7:0] */
/* -------- DMAC_SADDR : (DMAC Offset: N/A) DMAC Channel Source Address Register -------- */
#define DMAC_SADDR_SADDR_Pos 0
#define DMAC_SADDR_SADDR_Msk (0xffffffffu << DMAC_SADDR_SADDR_Pos) /**< \brief (DMAC_SADDR) Channel x Source Address */
#define DMAC_SADDR_SADDR(value) ((DMAC_SADDR_SADDR_Msk & ((value) << DMAC_SADDR_SADDR_Pos)))
/* -------- DMAC_DADDR : (DMAC Offset: N/A) DMAC Channel Destination Address Register -------- */
#define DMAC_DADDR_DADDR_Pos 0
#define DMAC_DADDR_DADDR_Msk (0xffffffffu << DMAC_DADDR_DADDR_Pos) /**< \brief (DMAC_DADDR) Channel x Destination Address */
#define DMAC_DADDR_DADDR(value) ((DMAC_DADDR_DADDR_Msk & ((value) << DMAC_DADDR_DADDR_Pos)))
/* -------- DMAC_DSCR : (DMAC Offset: N/A) DMAC Channel Descriptor Address Register -------- */
#define DMAC_DSCR_DSCR_IF_Pos 0
#define DMAC_DSCR_DSCR_IF_Msk (0x3u << DMAC_DSCR_DSCR_IF_Pos) /**< \brief (DMAC_DSCR)  */
#define   DMAC_DSCR_DSCR_IF_AHB_IF0 (0x0u << 0) /**< \brief (DMAC_DSCR) The buffer transfer descriptor is fetched via AHB-Lite Interface 0 */
#define   DMAC_DSCR_DSCR_IF_AHB_IF1 (0x1u << 0) /**< \brief (DMAC_DSCR) The buffer transfer descriptor is fetched via AHB-Lite Interface 1 */
#define   DMAC_DSCR_DSCR_IF_AHB_IF2 (0x2u << 0) /**< \brief (DMAC_DSCR) The buffer transfer descriptor is fetched via AHB-Lite Interface 2 */
#define DMAC_DSCR_DSCR_Pos 2
#define DMAC_DSCR_DSCR_Msk (0x3fffffffu << DMAC_DSCR_DSCR_Pos) /**< \brief (DMAC_DSCR) Buffer Transfer Descriptor Address */
#define DMAC_DSCR_DSCR(value) ((DMAC_DSCR_DSCR_Msk & ((value) << DMAC_DSCR_DSCR_Pos)))
/* -------- DMAC_CTRLA : (DMAC Offset: N/A) DMAC Channel Control A Register -------- */
#define DMAC_CTRLA_BTSIZE_Pos 0
#define DMAC_CTRLA_BTSIZE_Msk (0xffffu << DMAC_CTRLA_BTSIZE_Pos) /**< \brief (DMAC_CTRLA) Buffer Transfer Size */
#define DMAC_CTRLA_BTSIZE(value) ((DMAC_CTRLA_BTSIZE_Msk & ((value) << DMAC_CTRLA_BTSIZE_Pos)))
#define DMAC_CTRLA_SCSIZE_Pos 16
#define DMAC_CTRLA_SCSIZE_Msk (0x7u << DMAC_CTRLA_SCSIZE_Pos) /**< \brief (DMAC_CTRLA) Source Chunk Transfer Size. */
#define   DMAC_CTRLA_SCSIZE_CHK_1 (0x0u << 16) /**< \brief (DMAC_CTRLA) 1 data transferred */
#define   DMAC_CTRLA_SCSIZE_CHK_4 (0x1u << 16) /**< \brief (DMAC_CTRLA) 4 data transferred */
#define   DMAC_CTRLA_SCSIZE_CHK_8 (0x2u << 16) /**< \brief (DMAC_CTRLA) 8 data transferred */
#define   DMAC_CTRLA_SCSIZE_CHK_16 (0x3u << 16) /**< \brief (DMAC_CTRLA) 16 data transferred */
#define   DMAC_CTRLA_SCSIZE_CHK_32 (0x4u << 16) /**< \brief (DMAC_CTRLA) 32 data transferred */
#define   DMAC_CTRLA_SCSIZE_CHK_64 (0x5u << 16) /**< \brief (DMAC_CTRLA) 64 data transferred */
#define   DMAC_CTRLA_SCSIZE_CHK_128 (0x6u << 16) /**< \brief (DMAC_CTRLA) 128 data transferred */
#define   DMAC_CTRLA_SCSIZE_CHK_256 (0x7u << 16) /**< \brief (DMAC_CTRLA) 256 data transferred */
#define DMAC_CTRLA_DCSIZE_Pos 20
#define DMAC_CTRLA_DCSIZE_Msk (0x7u << DMAC_CTRLA_DCSIZE_Pos) /**< \brief (DMAC_CTRLA) Destination Chunk Transfer Size */
#define   DMAC_CTRLA_DCSIZE_CHK_1 (0x0u << 20) /**< \brief (DMAC_CTRLA) 1 data transferred */
#define   DMAC_CTRLA_DCSIZE_CHK_4 (0x1u << 20) /**< \brief (DMAC_CTRLA) 4 data transferred */
#define   DMAC_CTRLA_DCSIZE_CHK_8 (0x2u << 20) /**< \brief (DMAC_CTRLA) 8 data transferred */
#define   DMAC_CTRLA_DCSIZE_CHK_16 (0x3u << 20) /**< \brief (DMAC_CTRLA) 16 data transferred */
#define   DMAC_CTRLA_DCSIZE_CHK_32 (0x4u << 20) /**< \brief (DMAC_CTRLA) 32 data transferred */
#define   DMAC_CTRLA_DCSIZE_CHK_64 (0x5u << 20) /**< \brief (DMAC_CTRLA) 64 data transferred */
#define   DMAC_CTRLA_DCSIZE_CHK_128 (0x6u << 20) /**< \brief (DMAC_CTRLA) 128 data transferred */
#define   DMAC_CTRLA_DCSIZE_CHK_256 (0x7u << 20) /**< \brief (DMAC_CTRLA) 256 data transferred */
#define DMAC_CTRLA_SRC_WIDTH_Pos 24
#define DMAC_CTRLA_SRC_WIDTH_Msk (0x3u << DMAC_CTRLA_SRC_WIDTH_Pos) /**< \brief (DMAC_CTRLA) Transfer Width for the Source */
#define   DMAC_CTRLA_SRC_WIDTH_BYTE (0x0u << 24) /**< \brief (DMAC_CTRLA) the transfer size is set to 8-bit width */
#define   DMAC_CTRLA_SRC_WIDTH_HALF_WORD (0x1u << 24) /**< \brief (DMAC_CTRLA) the transfer size is set to 16-bit width */
#define   DMAC_CTRLA_SRC_WIDTH_WORD (0x2u << 24) /**< \brief (DMAC_CTRLA) the transfer size is set to 32-bit width */
#define   DMAC_CTRLA_SRC_WIDTH_DWORD (0x3u << 24) /**< \brief (DMAC_CTRLA) the transfer size is set to 64-bit width */
#define DMAC_CTRLA_DST_WIDTH_Pos 28
#define DMAC_CTRLA_DST_WIDTH_Msk (0x3u << DMAC_CTRLA_DST_WIDTH_Pos) /**< \brief (DMAC_CTRLA) Transfer Width for the Destination */
#define   DMAC_CTRLA_DST_WIDTH_BYTE (0x0u << 28) /**< \brief (DMAC_CTRLA) the transfer size is set to 8-bit width */
#define   DMAC_CTRLA_DST_WIDTH_HALF_WORD (0x1u << 28) /**< \brief (DMAC_CTRLA) the transfer size is set to 16-bit width */
#define   DMAC_CTRLA_DST_WIDTH_WORD (0x2u << 28) /**< \brief (DMAC_CTRLA) the transfer size is set to 32-bit width */
#define   DMAC_CTRLA_DST_WIDTH_DWORD (0x3u << 28) /**< \brief (DMAC_CTRLA) the transfer size is set to 64-bit width */
#define DMAC_CTRLA_DONE (0x1u << 31) /**< \brief (DMAC_CTRLA)  */
/* -------- DMAC_CTRLB : (DMAC Offset: N/A) DMAC Channel Control B Register -------- */
#define DMAC_CTRLB_SIF_Pos 0
#define DMAC_CTRLB_SIF_Msk (0x3u << DMAC_CTRLB_SIF_Pos) /**< \brief (DMAC_CTRLB) Source Interface Selection Field */
#define   DMAC_CTRLB_SIF_AHB_IF0 (0x0u << 0) /**< \brief (DMAC_CTRLB) The source transfer is done via AHB-Lite Interface 0 */
#define   DMAC_CTRLB_SIF_AHB_IF1 (0x1u << 0) /**< \brief (DMAC_CTRLB) The source transfer is done via AHB-Lite Interface 1 */
#define   DMAC_CTRLB_SIF_AHB_IF2 (0x2u << 0) /**< \brief (DMAC_CTRLB) The source transfer is done via AHB-Lite Interface 2 */
#define DMAC_CTRLB_DIF_Pos 4
#define DMAC_CTRLB_DIF_Msk (0x3u << DMAC_CTRLB_DIF_Pos) /**< \brief (DMAC_CTRLB) Destination Interface Selection Field */
#define   DMAC_CTRLB_DIF_AHB_IF0 (0x0u << 4) /**< \brief (DMAC_CTRLB) The destination transfer is done via AHB-Lite Interface 0 */
#define   DMAC_CTRLB_DIF_AHB_IF1 (0x1u << 4) /**< \brief (DMAC_CTRLB) The destination transfer is done via AHB-Lite Interface 1 */
#define   DMAC_CTRLB_DIF_AHB_IF2 (0x2u << 4) /**< \brief (DMAC_CTRLB) The destination transfer is done via AHB-Lite Interface 2 */
#define DMAC_CTRLB_SRC_PIP (0x1u << 8) /**< \brief (DMAC_CTRLB) Source Picture-in-Picture Mode */
#define   DMAC_CTRLB_SRC_PIP_DISABLE (0x0u << 8) /**< \brief (DMAC_CTRLB) Picture-in-Picture mode is disabled. The source data area is contiguous. */
#define   DMAC_CTRLB_SRC_PIP_ENABLE (0x1u << 8) /**< \brief (DMAC_CTRLB) Picture-in-Picture mode is enabled. When the source PIP counter reaches the programmable boundary, the address is automatically incremented by a user defined amount. */
#define DMAC_CTRLB_DST_PIP (0x1u << 12) /**< \brief (DMAC_CTRLB) Destination Picture-in-Picture Mode */
#define   DMAC_CTRLB_DST_PIP_DISABLE (0x0u << 12) /**< \brief (DMAC_CTRLB) Picture-in-Picture mode is disabled. The Destination data area is contiguous. */
#define   DMAC_CTRLB_DST_PIP_ENABLE (0x1u << 12) /**< \brief (DMAC_CTRLB) Picture-in-Picture mode is enabled. When the Destination PIP counter reaches the programmable boundary the address is automatically incremented by a user-defined amount. */
#define DMAC_CTRLB_SRC_DSCR (0x1u << 16) /**< \brief (DMAC_CTRLB) Source Address Descriptor */
#define   DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM (0x0u << 16) /**< \brief (DMAC_CTRLB) Source address is updated when the descriptor is fetched from the memory. */
#define   DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE (0x1u << 16) /**< \brief (DMAC_CTRLB) Buffer Descriptor Fetch operation is disabled for the source. */
#define DMAC_CTRLB_DST_DSCR (0x1u << 20) /**< \brief (DMAC_CTRLB) Destination Address Descriptor */
#define   DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM (0x0u << 20) /**< \brief (DMAC_CTRLB) Destination address is updated when the descriptor is fetched from the memory. */
#define   DMAC_CTRLB_DST_DSCR_FETCH_DISABLE (0x1u << 20) /**< \brief (DMAC_CTRLB) Buffer Descriptor Fetch operation is disabled for the destination. */
#define DMAC_CTRLB_FC_Pos 21
#define DMAC_CTRLB_FC_Msk (0x7u << DMAC_CTRLB_FC_Pos) /**< \brief (DMAC_CTRLB) Flow Control */
#define   DMAC_CTRLB_FC_MEM2MEM_DMA_FC (0x0u << 21) /**< \brief (DMAC_CTRLB) Memory-to-Memory Transfer DMAC is flow controller */
#define   DMAC_CTRLB_FC_MEM2PER_DMA_FC (0x1u << 21) /**< \brief (DMAC_CTRLB) Memory-to-Peripheral Transfer DMAC is flow controller */
#define   DMAC_CTRLB_FC_PER2MEM_DMA_FC (0x2u << 21) /**< \brief (DMAC_CTRLB) Peripheral-to-Memory Transfer DMAC is flow controller */
#define   DMAC_CTRLB_FC_PER2PER_DMA_FC (0x3u << 21) /**< \brief (DMAC_CTRLB) Peripheral-to-Peripheral Transfer DMAC is flow controller */
#define DMAC_CTRLB_SRC_INCR_Pos 24
#define DMAC_CTRLB_SRC_INCR_Msk (0x3u << DMAC_CTRLB_SRC_INCR_Pos) /**< \brief (DMAC_CTRLB) Incrementing, Decrementing or Fixed Address for the Source */
#define   DMAC_CTRLB_SRC_INCR_INCREMENTING (0x0u << 24) /**< \brief (DMAC_CTRLB) The source address is incremented */
#define   DMAC_CTRLB_SRC_INCR_DECREMENTING (0x1u << 24) /**< \brief (DMAC_CTRLB) The source address is decremented */
#define   DMAC_CTRLB_SRC_INCR_FIXED (0x2u << 24) /**< \brief (DMAC_CTRLB) The source address remains unchanged */
#define DMAC_CTRLB_DST_INCR_Pos 28
#define DMAC_CTRLB_DST_INCR_Msk (0x3u << DMAC_CTRLB_DST_INCR_Pos) /**< \brief (DMAC_CTRLB) Incrementing, Decrementing or Fixed Address for the Destination */
#define   DMAC_CTRLB_DST_INCR_INCREMENTING (0x0u << 28) /**< \brief (DMAC_CTRLB) The destination address is incremented */
#define   DMAC_CTRLB_DST_INCR_DECREMENTING (0x1u << 28) /**< \brief (DMAC_CTRLB) The destination address is decremented */
#define   DMAC_CTRLB_DST_INCR_FIXED (0x2u << 28) /**< \brief (DMAC_CTRLB) The destination address remains unchanged */
#define DMAC_CTRLB_IEN (0x1u << 30) /**< \brief (DMAC_CTRLB)  */
#define DMAC_CTRLB_AUTO (0x1u << 31) /**< \brief (DMAC_CTRLB) Automatic Multiple Buffer Transfer */
#define   DMAC_CTRLB_AUTO_DISABLE (0x0u << 31) /**< \brief (DMAC_CTRLB) Automatic multiple buffer transfer is disabled. */
#define   DMAC_CTRLB_AUTO_ENABLE (0x1u << 31) /**< \brief (DMAC_CTRLB) Automatic multiple buffer transfer is enabled. This bit enables replay mode or contiguous mode when several buffers are transferred. */
/* -------- DMAC_CFG : (DMAC Offset: N/A) DMAC Channel Configuration Register -------- */
#define DMAC_CFG_SRC_PER_Pos 0
#define DMAC_CFG_SRC_PER_Msk (0xfu << DMAC_CFG_SRC_PER_Pos) /**< \brief (DMAC_CFG) Source with Peripheral identifier */
#define DMAC_CFG_SRC_PER(value) ((DMAC_CFG_SRC_PER_Msk & ((value) << DMAC_CFG_SRC_PER_Pos)))
#define DMAC_CFG_DST_PER_Pos 4
#define DMAC_CFG_DST_PER_Msk (0xfu << DMAC_CFG_DST_PER_Pos) /**< \brief (DMAC_CFG) Destination with Peripheral identifier */
#define DMAC_CFG_DST_PER(value) ((DMAC_CFG_DST_PER_Msk & ((value) << DMAC_CFG_DST_PER_Pos)))
#define DMAC_CFG_SRC_REP (0x1u << 8) /**< \brief (DMAC_CFG) Source Reloaded from Previous */
#define   DMAC_CFG_SRC_REP_CONTIGUOUS_ADDR (0x0u << 8) /**< \brief (DMAC_CFG) When automatic mode is activated, source address is contiguous between two buffers. */
#define   DMAC_CFG_SRC_REP_RELOAD_ADDR (0x1u << 8) /**< \brief (DMAC_CFG) When automatic mode is activated, the source address and the control register are reloaded from previous transfer. */
#define DMAC_CFG_SRC_H2SEL (0x1u << 9) /**< \brief (DMAC_CFG) Software or Hardware Selection for the Source */
#define   DMAC_CFG_SRC_H2SEL_SW (0x0u << 9) /**< \brief (DMAC_CFG) Software handshaking interface is used to trigger a transfer request. */
#define   DMAC_CFG_SRC_H2SEL_HW (0x1u << 9) /**< \brief (DMAC_CFG) Hardware handshaking interface is used to trigger a transfer request. */
#define DMAC_CFG_SRC_PER_MSB_Pos 10
#define DMAC_CFG_SRC_PER_MSB_Msk (0x3u << DMAC_CFG_SRC_PER_MSB_Pos) /**< \brief (DMAC_CFG) SRC_PER Most Significant Bits */
#define DMAC_CFG_SRC_PER_MSB(value) ((DMAC_CFG_SRC_PER_MSB_Msk & ((value) << DMAC_CFG_SRC_PER_MSB_Pos)))
#define DMAC_CFG_DST_REP (0x1u << 12) /**< \brief (DMAC_CFG) Destination Reloaded from Previous */
#define   DMAC_CFG_DST_REP_CONTIGUOUS_ADDR (0x0u << 12) /**< \brief (DMAC_CFG) When automatic mode is activated, destination address is contiguous between two buffers. */
#define   DMAC_CFG_DST_REP_RELOAD_ADDR (0x1u << 12) /**< \brief (DMAC_CFG) When automatic mode is activated, the destination and the control register are reloaded from the pre-vious transfer. */
#define DMAC_CFG_DST_H2SEL (0x1u << 13) /**< \brief (DMAC_CFG) Software or Hardware Selection for the Destination */
#define   DMAC_CFG_DST_H2SEL_SW (0x0u << 13) /**< \brief (DMAC_CFG) Software handshaking interface is used to trigger a transfer request. */
#define   DMAC_CFG_DST_H2SEL_HW (0x1u << 13) /**< \brief (DMAC_CFG) Hardware handshaking interface is used to trigger a transfer request. */
#define DMAC_CFG_DST_PER_MSB_Pos 14
#define DMAC_CFG_DST_PER_MSB_Msk (0x3u << DMAC_CFG_DST_PER_MSB_Pos) /**< \brief (DMAC_CFG) DST_PER Most Significant Bits */
#define DMAC_CFG_DST_PER_MSB(value) ((DMAC_CFG_DST_PER_MSB_Msk & ((value) << DMAC_CFG_DST_PER_MSB_Pos)))
#define DMAC_CFG_SOD (0x1u << 16) /**< \brief (DMAC_CFG) Stop On Done */
#define   DMAC_CFG_SOD_DISABLE (0x0u << 16) /**< \brief (DMAC_CFG) STOP ON DONE disabled, the descriptor fetch operation ignores DONE Field of CTRLA register. */
#define   DMAC_CFG_SOD_ENABLE (0x1u << 16) /**< \brief (DMAC_CFG) STOP ON DONE activated, the DMAC module is automatically disabled if DONE FIELD is set to 1. */
#define DMAC_CFG_LOCK_IF (0x1u << 20) /**< \brief (DMAC_CFG) Interface Lock */
#define   DMAC_CFG_LOCK_IF_DISABLE (0x0u << 20) /**< \brief (DMAC_CFG) Interface Lock capability is disabled */
#define   DMAC_CFG_LOCK_IF_ENABLE (0x1u << 20) /**< \brief (DMAC_CFG) Interface Lock capability is enabled */
#define DMAC_CFG_LOCK_B (0x1u << 21) /**< \brief (DMAC_CFG) Bus Lock */
#define   DMAC_CFG_LOCK_B_DISABLE (0x0u << 21) /**< \brief (DMAC_CFG) AHB Bus Locking capability is disabled. */
#define DMAC_CFG_LOCK_IF_L (0x1u << 22) /**< \brief (DMAC_CFG) Master Interface Arbiter Lock */
#define   DMAC_CFG_LOCK_IF_L_CHUNK (0x0u << 22) /**< \brief (DMAC_CFG) The Master Interface Arbiter is locked by the channel x for a chunk transfer. */
#define   DMAC_CFG_LOCK_IF_L_BUFFER (0x1u << 22) /**< \brief (DMAC_CFG) The Master Interface Arbiter is locked by the channel x for a buffer transfer. */
#define DMAC_CFG_AHB_PROT_Pos 24
#define DMAC_CFG_AHB_PROT_Msk (0x7u << DMAC_CFG_AHB_PROT_Pos) /**< \brief (DMAC_CFG) AHB Protection */
#define DMAC_CFG_AHB_PROT(value) ((DMAC_CFG_AHB_PROT_Msk & ((value) << DMAC_CFG_AHB_PROT_Pos)))
#define DMAC_CFG_FIFOCFG_Pos 28
#define DMAC_CFG_FIFOCFG_Msk (0x3u << DMAC_CFG_FIFOCFG_Pos) /**< \brief (DMAC_CFG) FIFO Configuration */
#define   DMAC_CFG_FIFOCFG_ALAP_CFG (0x0u << 28) /**< \brief (DMAC_CFG) The largest defined length AHB burst is performed on the destination AHB interface. */
#define   DMAC_CFG_FIFOCFG_HALF_CFG (0x1u << 28) /**< \brief (DMAC_CFG) When half FIFO size is available/filled, a source/destination request is serviced. */
#define   DMAC_CFG_FIFOCFG_ASAP_CFG (0x2u << 28) /**< \brief (DMAC_CFG) When there is enough space/data available to perform a single AHB access, then the request is serviced. */
/* -------- DMAC_SPIP : (DMAC Offset: N/A) DMAC Channel Source Picture-in-Picture Configuration Register -------- */
#define DMAC_SPIP_SPIP_HOLE_Pos 0
#define DMAC_SPIP_SPIP_HOLE_Msk (0xffffu << DMAC_SPIP_SPIP_HOLE_Pos) /**< \brief (DMAC_SPIP) Source Picture-in-Picture Hole */
#define DMAC_SPIP_SPIP_HOLE(value) ((DMAC_SPIP_SPIP_HOLE_Msk & ((value) << DMAC_SPIP_SPIP_HOLE_Pos)))
#define DMAC_SPIP_SPIP_BOUNDARY_Pos 16
#define DMAC_SPIP_SPIP_BOUNDARY_Msk (0x3ffu << DMAC_SPIP_SPIP_BOUNDARY_Pos) /**< \brief (DMAC_SPIP) Source Picture-in-Picture Boundary */
#define DMAC_SPIP_SPIP_BOUNDARY(value) ((DMAC_SPIP_SPIP_BOUNDARY_Msk & ((value) << DMAC_SPIP_SPIP_BOUNDARY_Pos)))
/* -------- DMAC_DPIP : (DMAC Offset: N/A) DMAC Channel Destination Picture-in-Picture Configuration Register -------- */
#define DMAC_DPIP_DPIP_HOLE_Pos 0
#define DMAC_DPIP_DPIP_HOLE_Msk (0xffffu << DMAC_DPIP_DPIP_HOLE_Pos) /**< \brief (DMAC_DPIP) Destination Picture-in-Picture Hole */
#define DMAC_DPIP_DPIP_HOLE(value) ((DMAC_DPIP_DPIP_HOLE_Msk & ((value) << DMAC_DPIP_DPIP_HOLE_Pos)))
#define DMAC_DPIP_DPIP_BOUNDARY_Pos 16
#define DMAC_DPIP_DPIP_BOUNDARY_Msk (0x3ffu << DMAC_DPIP_DPIP_BOUNDARY_Pos) /**< \brief (DMAC_DPIP) Destination Picture-in-Picture Boundary */
#define DMAC_DPIP_DPIP_BOUNDARY(value) ((DMAC_DPIP_DPIP_BOUNDARY_Msk & ((value) << DMAC_DPIP_DPIP_BOUNDARY_Pos)))
/* -------- DMAC_WPMR : (DMAC Offset: 0x1E4) DMAC Write Protect Mode Register -------- */
#define DMAC_WPMR_WPEN (0x1u << 0) /**< \brief (DMAC_WPMR) Write Protect Enable */
#define DMAC_WPMR_WPKEY_Pos 8
#define DMAC_WPMR_WPKEY_Msk (0xffffffu << DMAC_WPMR_WPKEY_Pos) /**< \brief (DMAC_WPMR) Write Protect KEY */
#define DMAC_WPMR_WPKEY(value) ((DMAC_WPMR_WPKEY_Msk & ((value) << DMAC_WPMR_WPKEY_Pos)))
/* -------- DMAC_WPSR : (DMAC Offset: 0x1E8) DMAC Write Protect Status Register -------- */
#define DMAC_WPSR_WPVS (0x1u << 0) /**< \brief (DMAC_WPSR) Write Protect Violation Status */
#define DMAC_WPSR_WPVSRC_Pos 8
#define DMAC_WPSR_WPVSRC_Msk (0xffffu << DMAC_WPSR_WPVSRC_Pos) /**< \brief (DMAC_WPSR) Write Protect Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Fuse Controller */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_FUSE Fuse Controller */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Fuse hardware registers */
typedef struct {
  WoReg FUSE_CR;    /**< \brief (Fuse Offset: 0x00) Fuse Control Register */
  WoReg FUSE_MR;    /**< \brief (Fuse Offset: 0x04) Fuse Mode Register */
  RwReg FUSE_IR;    /**< \brief (Fuse Offset: 0x08) Fuse Index Register */
  WoReg FUSE_DR;    /**< \brief (Fuse Offset: 0x0C) Fuse Data Register */
  RoReg FUSE_SR[8]; /**< \brief (Fuse Offset: 0x10) Fuse Status Register */
} Fuse;
#endif /* __ASSEMBLY__ */
/* -------- FUSE_CR : (FUSE Offset: 0x00) Fuse Control Register -------- */
#define FUSE_CR_WRQ (0x1u << 0) /**< \brief (FUSE_CR) Write Request */
#define FUSE_CR_RRQ (0x1u << 1) /**< \brief (FUSE_CR) Read Request */
#define FUSE_CR_KEY_Pos 8
#define FUSE_CR_KEY_Msk (0xffu << FUSE_CR_KEY_Pos) /**< \brief (FUSE_CR) Key code */
#define   FUSE_CR_KEY_VALID (0xFBu << 8) /**< \brief (FUSE_CR) valid key. */
/* -------- FUSE_MR : (FUSE Offset: 0x04) Fuse Mode Register -------- */
#define FUSE_MR_MSK (0x1u << 0) /**< \brief (FUSE_MR) Mask Fuse Status Registers */
/* -------- FUSE_IR : (FUSE Offset: 0x08) Fuse Index Register -------- */
#define FUSE_IR_WS (0x1u << 0) /**< \brief (FUSE_IR) Write Status */
#define FUSE_IR_RS (0x1u << 1) /**< \brief (FUSE_IR) Read Status */
#define FUSE_IR_WSEL_Pos 8
#define FUSE_IR_WSEL_Msk (0xfu << FUSE_IR_WSEL_Pos) /**< \brief (FUSE_IR) Word Selection */
#define FUSE_IR_WSEL(value) ((FUSE_IR_WSEL_Msk & ((value) << FUSE_IR_WSEL_Pos)))
/* -------- FUSE_DR : (FUSE Offset: 0x0C) Fuse Data Register -------- */
#define FUSE_DR_DATA_Pos 0
#define FUSE_DR_DATA_Msk (0xffffffffu << FUSE_DR_DATA_Pos) /**< \brief (FUSE_DR) Data to Program */
#define FUSE_DR_DATA(value) ((FUSE_DR_DATA_Msk & ((value) << FUSE_DR_DATA_Pos)))
/* -------- FUSE_SR[8] : (FUSE Offset: 0x10) Fuse Status Register -------- */
#define FUSE_SR_FUSE_Pos 0
#define FUSE_SR_FUSE_Msk (0xffffffffu << FUSE_SR_FUSE_Pos) /**< \brief (FUSE_SR[8]) Fuse Status */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR High Speed MultiMedia Card Interface */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_HSMCI High Speed MultiMedia Card Interface */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Hsmci hardware registers */
typedef struct {
  WoReg HSMCI_CR;        /**< \brief (Hsmci Offset: 0x00) Control Register */
  RwReg HSMCI_MR;        /**< \brief (Hsmci Offset: 0x04) Mode Register */
  RwReg HSMCI_DTOR;      /**< \brief (Hsmci Offset: 0x08) Data Timeout Register */
  RwReg HSMCI_SDCR;      /**< \brief (Hsmci Offset: 0x0C) SD/SDIO Card Register */
  RwReg HSMCI_ARGR;      /**< \brief (Hsmci Offset: 0x10) Argument Register */
  WoReg HSMCI_CMDR;      /**< \brief (Hsmci Offset: 0x14) Command Register */
  RwReg HSMCI_BLKR;      /**< \brief (Hsmci Offset: 0x18) Block Register */
  RwReg HSMCI_CSTOR;     /**< \brief (Hsmci Offset: 0x1C) Completion Signal Timeout Register */
  RoReg HSMCI_RSPR[4];   /**< \brief (Hsmci Offset: 0x20) Response Register */
  RoReg HSMCI_RDR;       /**< \brief (Hsmci Offset: 0x30) Receive Data Register */
  WoReg HSMCI_TDR;       /**< \brief (Hsmci Offset: 0x34) Transmit Data Register */
  RoReg Reserved1[2];
  RoReg HSMCI_SR;        /**< \brief (Hsmci Offset: 0x40) Status Register */
  WoReg HSMCI_IER;       /**< \brief (Hsmci Offset: 0x44) Interrupt Enable Register */
  WoReg HSMCI_IDR;       /**< \brief (Hsmci Offset: 0x48) Interrupt Disable Register */
  RoReg HSMCI_IMR;       /**< \brief (Hsmci Offset: 0x4C) Interrupt Mask Register */
  RwReg HSMCI_DMA;       /**< \brief (Hsmci Offset: 0x50) DMA Configuration Register */
  RwReg HSMCI_CFG;       /**< \brief (Hsmci Offset: 0x54) Configuration Register */
  RoReg Reserved2[35];
  RwReg HSMCI_WPMR;      /**< \brief (Hsmci Offset: 0xE4) Write Protection Mode Register */
  RoReg HSMCI_WPSR;      /**< \brief (Hsmci Offset: 0xE8) Write Protection Status Register */
  RoReg Reserved3[69];
  RwReg HSMCI_FIFO[256]; /**< \brief (Hsmci Offset: 0x200) FIFO Memory Aperture0 */
} Hsmci;
#endif /* __ASSEMBLY__ */
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
#define HSMCI_MR_RDPROOF (0x1u << 11) /**< \brief (HSMCI_MR)  */
#define HSMCI_MR_WRPROOF (0x1u << 12) /**< \brief (HSMCI_MR)  */
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
#define   HSMCI_CMDR_TRTYP_SINGLE (0x0u << 19) /**< \brief (HSMCI_CMDR) MMC/SDCard Single Block */
#define   HSMCI_CMDR_TRTYP_MULTIPLE (0x1u << 19) /**< \brief (HSMCI_CMDR) MMC/SDCard Multiple Block */
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
#define   HSMCI_BLKR_BCNT_MULTIPLE (0x0u << 0) /**< \brief (HSMCI_BLKR) MMC/SDCARD Multiple BlockFrom 1 to 1: Value 0 corresponds to an infinite block transfer. */
#define   HSMCI_BLKR_BCNT_BYTE (0x4u << 0) /**< \brief (HSMCI_BLKR) SDIO ByteFrom 1 to 512 bytes: Value 0 corresponds to a 512-byte transfer.Values from 0x200 to 0xFFFF are forbidden. */
#define   HSMCI_BLKR_BCNT_BLOCK (0x5u << 0) /**< \brief (HSMCI_BLKR) SDIO BlockFrom 1 to 511 blocks: Value 0 corresponds to an infinite block transfer.Values from 0x200 to 0xFFFF are forbidden. */
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
#define HSMCI_SR_DMADONE (0x1u << 25) /**< \brief (HSMCI_SR) DMA Transfer done */
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
#define HSMCI_IER_DMADONE (0x1u << 25) /**< \brief (HSMCI_IER) DMA Transfer completed Interrupt Enable */
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
#define HSMCI_IDR_DMADONE (0x1u << 25) /**< \brief (HSMCI_IDR) DMA Transfer completed Interrupt Disable */
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
#define HSMCI_IMR_DMADONE (0x1u << 25) /**< \brief (HSMCI_IMR) DMA Transfer Completed Interrupt Mask */
#define HSMCI_IMR_FIFOEMPTY (0x1u << 26) /**< \brief (HSMCI_IMR) FIFO Empty Interrupt Mask */
#define HSMCI_IMR_XFRDONE (0x1u << 27) /**< \brief (HSMCI_IMR) Transfer Done Interrupt Mask */
#define HSMCI_IMR_ACKRCV (0x1u << 28) /**< \brief (HSMCI_IMR) Boot Operation Acknowledge Received Interrupt Mask */
#define HSMCI_IMR_ACKRCVE (0x1u << 29) /**< \brief (HSMCI_IMR) Boot Operation Acknowledge Error Interrupt Mask */
#define HSMCI_IMR_OVRE (0x1u << 30) /**< \brief (HSMCI_IMR) Overrun Interrupt Mask */
#define HSMCI_IMR_UNRE (0x1u << 31) /**< \brief (HSMCI_IMR) Underrun Interrupt Mask */
/* -------- HSMCI_DMA : (HSMCI Offset: 0x50) DMA Configuration Register -------- */
#define HSMCI_DMA_OFFSET_Pos 0
#define HSMCI_DMA_OFFSET_Msk (0x3u << HSMCI_DMA_OFFSET_Pos) /**< \brief (HSMCI_DMA) DMA Write Buffer Offset */
#define HSMCI_DMA_OFFSET(value) ((HSMCI_DMA_OFFSET_Msk & ((value) << HSMCI_DMA_OFFSET_Pos)))
#define HSMCI_DMA_CHKSIZE_Pos 4
#define HSMCI_DMA_CHKSIZE_Msk (0x7u << HSMCI_DMA_CHKSIZE_Pos) /**< \brief (HSMCI_DMA) DMA Channel Read and Write Chunk Size */
#define   HSMCI_DMA_CHKSIZE_1 (0x0u << 4) /**< \brief (HSMCI_DMA) 1 data available */
#define   HSMCI_DMA_CHKSIZE_4 (0x1u << 4) /**< \brief (HSMCI_DMA) 4 data available */
#define   HSMCI_DMA_CHKSIZE_8 (0x2u << 4) /**< \brief (HSMCI_DMA) 8 data available */
#define   HSMCI_DMA_CHKSIZE_16 (0x3u << 4) /**< \brief (HSMCI_DMA) 16 data available */
#define   HSMCI_DMA_CHKSIZE_32 (0x4u << 4) /**< \brief (HSMCI_DMA) 32 data available */
#define HSMCI_DMA_DMAEN (0x1u << 8) /**< \brief (HSMCI_DMA) DMA Hardware Handshaking Enable */
#define HSMCI_DMA_ROPT (0x1u << 12) /**< \brief (HSMCI_DMA) Read Optimization with padding */
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
/* -------- HSMCI_FIFO[256] : (HSMCI Offset: 0x200) FIFO Memory Aperture0 -------- */
#define HSMCI_FIFO_DATA_Pos 0
#define HSMCI_FIFO_DATA_Msk (0xffffffffu << HSMCI_FIFO_DATA_Pos) /**< \brief (HSMCI_FIFO[256]) Data to Read or Data to Write */
#define HSMCI_FIFO_DATA(value) ((HSMCI_FIFO_DATA_Msk & ((value) << HSMCI_FIFO_DATA_Pos)))


/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR AHB Bus Matrix */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_MATRIX AHB Bus Matrix */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief MatrixPr hardware registers */
typedef struct {
  RwReg     MATRIX_PRAS;     /**< \brief (MatrixPr Offset: 0x0) Priority Register A for Slave 0 */
  RwReg     MATRIX_PRBS;     /**< \brief (MatrixPr Offset: 0x4) Priority Register B for Slave 0 */
} MatrixPr;
/** \brief Matrix hardware registers */
#define MATRIXPR_NUMBER 16
typedef struct {
  RwReg     MATRIX_MCFG[16]; /**< \brief (Matrix Offset: 0x0000) Master Configuration Register */
  RwReg     MATRIX_SCFG[16]; /**< \brief (Matrix Offset: 0x0040) Slave Configuration Register */
  MatrixPr  MATRIX_PR[MATRIXPR_NUMBER]; /**< \brief (Matrix Offset: 0x0080) 0 .. 15 */
  RwReg     MATRIX_MRCR;     /**< \brief (Matrix Offset: 0x0100) Master Remap Control Register */
  RoReg     Reserved1[3];
  RwReg     MATRIX_SFR[16];  /**< \brief (Matrix Offset: 0x0110) Special Function Register */
  RoReg     Reserved2[37];
  RwReg     MATRIX_WPMR;     /**< \brief (Matrix Offset: 0x01E4) Write Protect Mode Register */
  RoReg     MATRIX_WPSR;     /**< \brief (Matrix Offset: 0x01E8) Write Protect Status Register */
} Matrix;
#endif /* __ASSEMBLY__ */
/* -------- MATRIX_MCFG[16] : (MATRIX Offset: 0x0000) Master Configuration Register -------- */
#define MATRIX_MCFG_ULBT_Pos 0
#define MATRIX_MCFG_ULBT_Msk (0x7u << MATRIX_MCFG_ULBT_Pos) /**< \brief (MATRIX_MCFG[16]) Undefined Length Burst Type */
#define MATRIX_MCFG_ULBT(value) ((MATRIX_MCFG_ULBT_Msk & ((value) << MATRIX_MCFG_ULBT_Pos)))
/* -------- MATRIX_SCFG[16] : (MATRIX Offset: 0x0040) Slave Configuration Register -------- */
#define MATRIX_SCFG_SLOT_CYCLE_Pos 0
#define MATRIX_SCFG_SLOT_CYCLE_Msk (0x1ffu << MATRIX_SCFG_SLOT_CYCLE_Pos) /**< \brief (MATRIX_SCFG[16]) Maximum Bus Grant Duration for Masters */
#define MATRIX_SCFG_SLOT_CYCLE(value) ((MATRIX_SCFG_SLOT_CYCLE_Msk & ((value) << MATRIX_SCFG_SLOT_CYCLE_Pos)))
#define MATRIX_SCFG_DEFMSTR_TYPE_Pos 16
#define MATRIX_SCFG_DEFMSTR_TYPE_Msk (0x3u << MATRIX_SCFG_DEFMSTR_TYPE_Pos) /**< \brief (MATRIX_SCFG[16]) Default Master Type */
#define MATRIX_SCFG_DEFMSTR_TYPE(value) ((MATRIX_SCFG_DEFMSTR_TYPE_Msk & ((value) << MATRIX_SCFG_DEFMSTR_TYPE_Pos)))
#define MATRIX_SCFG_FIXED_DEFMSTR_Pos 18
#define MATRIX_SCFG_FIXED_DEFMSTR_Msk (0xfu << MATRIX_SCFG_FIXED_DEFMSTR_Pos) /**< \brief (MATRIX_SCFG[16]) Fixed Default Master */
#define MATRIX_SCFG_FIXED_DEFMSTR(value) ((MATRIX_SCFG_FIXED_DEFMSTR_Msk & ((value) << MATRIX_SCFG_FIXED_DEFMSTR_Pos)))
/* -------- MATRIX_PRAS : (MATRIX Offset: N/A) Priority Register A for Slave 0 -------- */
#define MATRIX_PRAS_M0PR_Pos 0
#define MATRIX_PRAS_M0PR_Msk (0x3u << MATRIX_PRAS_M0PR_Pos) /**< \brief (MATRIX_PRAS) Master 0 Priority */
#define MATRIX_PRAS_M0PR(value) ((MATRIX_PRAS_M0PR_Msk & ((value) << MATRIX_PRAS_M0PR_Pos)))
#define MATRIX_PRAS_M1PR_Pos 4
#define MATRIX_PRAS_M1PR_Msk (0x3u << MATRIX_PRAS_M1PR_Pos) /**< \brief (MATRIX_PRAS) Master 1 Priority */
#define MATRIX_PRAS_M1PR(value) ((MATRIX_PRAS_M1PR_Msk & ((value) << MATRIX_PRAS_M1PR_Pos)))
#define MATRIX_PRAS_M2PR_Pos 8
#define MATRIX_PRAS_M2PR_Msk (0x3u << MATRIX_PRAS_M2PR_Pos) /**< \brief (MATRIX_PRAS) Master 2 Priority */
#define MATRIX_PRAS_M2PR(value) ((MATRIX_PRAS_M2PR_Msk & ((value) << MATRIX_PRAS_M2PR_Pos)))
#define MATRIX_PRAS_M3PR_Pos 12
#define MATRIX_PRAS_M3PR_Msk (0x3u << MATRIX_PRAS_M3PR_Pos) /**< \brief (MATRIX_PRAS) Master 3 Priority */
#define MATRIX_PRAS_M3PR(value) ((MATRIX_PRAS_M3PR_Msk & ((value) << MATRIX_PRAS_M3PR_Pos)))
#define MATRIX_PRAS_M4PR_Pos 16
#define MATRIX_PRAS_M4PR_Msk (0x3u << MATRIX_PRAS_M4PR_Pos) /**< \brief (MATRIX_PRAS) Master 4 Priority */
#define MATRIX_PRAS_M4PR(value) ((MATRIX_PRAS_M4PR_Msk & ((value) << MATRIX_PRAS_M4PR_Pos)))
#define MATRIX_PRAS_M5PR_Pos 20
#define MATRIX_PRAS_M5PR_Msk (0x3u << MATRIX_PRAS_M5PR_Pos) /**< \brief (MATRIX_PRAS) Master 5 Priority */
#define MATRIX_PRAS_M5PR(value) ((MATRIX_PRAS_M5PR_Msk & ((value) << MATRIX_PRAS_M5PR_Pos)))
#define MATRIX_PRAS_M6PR_Pos 24
#define MATRIX_PRAS_M6PR_Msk (0x3u << MATRIX_PRAS_M6PR_Pos) /**< \brief (MATRIX_PRAS) Master 6 Priority */
#define MATRIX_PRAS_M6PR(value) ((MATRIX_PRAS_M6PR_Msk & ((value) << MATRIX_PRAS_M6PR_Pos)))
#define MATRIX_PRAS_M7PR_Pos 28
#define MATRIX_PRAS_M7PR_Msk (0x3u << MATRIX_PRAS_M7PR_Pos) /**< \brief (MATRIX_PRAS) Master 7 Priority */
#define MATRIX_PRAS_M7PR(value) ((MATRIX_PRAS_M7PR_Msk & ((value) << MATRIX_PRAS_M7PR_Pos)))
/* -------- MATRIX_PRBS : (MATRIX Offset: N/A) Priority Register B for Slave 0 -------- */
#define MATRIX_PRBS_M8PR_Pos 0
#define MATRIX_PRBS_M8PR_Msk (0x3u << MATRIX_PRBS_M8PR_Pos) /**< \brief (MATRIX_PRBS) Master 8 Priority */
#define MATRIX_PRBS_M8PR(value) ((MATRIX_PRBS_M8PR_Msk & ((value) << MATRIX_PRBS_M8PR_Pos)))
#define MATRIX_PRBS_M9PR_Pos 4
#define MATRIX_PRBS_M9PR_Msk (0x3u << MATRIX_PRBS_M9PR_Pos) /**< \brief (MATRIX_PRBS) Master 9 Priority */
#define MATRIX_PRBS_M9PR(value) ((MATRIX_PRBS_M9PR_Msk & ((value) << MATRIX_PRBS_M9PR_Pos)))
#define MATRIX_PRBS_M10PR_Pos 8
#define MATRIX_PRBS_M10PR_Msk (0x3u << MATRIX_PRBS_M10PR_Pos) /**< \brief (MATRIX_PRBS) Master 10 Priority */
#define MATRIX_PRBS_M10PR(value) ((MATRIX_PRBS_M10PR_Msk & ((value) << MATRIX_PRBS_M10PR_Pos)))
#define MATRIX_PRBS_M11PR_Pos 12
#define MATRIX_PRBS_M11PR_Msk (0x3u << MATRIX_PRBS_M11PR_Pos) /**< \brief (MATRIX_PRBS) Master 11 Priority */
#define MATRIX_PRBS_M11PR(value) ((MATRIX_PRBS_M11PR_Msk & ((value) << MATRIX_PRBS_M11PR_Pos)))
#define MATRIX_PRBS_M12PR_Pos 16
#define MATRIX_PRBS_M12PR_Msk (0x3u << MATRIX_PRBS_M12PR_Pos) /**< \brief (MATRIX_PRBS) Master 12 Priority */
#define MATRIX_PRBS_M12PR(value) ((MATRIX_PRBS_M12PR_Msk & ((value) << MATRIX_PRBS_M12PR_Pos)))
#define MATRIX_PRBS_M13PR_Pos 20
#define MATRIX_PRBS_M13PR_Msk (0x3u << MATRIX_PRBS_M13PR_Pos) /**< \brief (MATRIX_PRBS) Master 13 Priority */
#define MATRIX_PRBS_M13PR(value) ((MATRIX_PRBS_M13PR_Msk & ((value) << MATRIX_PRBS_M13PR_Pos)))
#define MATRIX_PRBS_M14PR_Pos 24
#define MATRIX_PRBS_M14PR_Msk (0x3u << MATRIX_PRBS_M14PR_Pos) /**< \brief (MATRIX_PRBS) Master 14 Priority */
#define MATRIX_PRBS_M14PR(value) ((MATRIX_PRBS_M14PR_Msk & ((value) << MATRIX_PRBS_M14PR_Pos)))
#define MATRIX_PRBS_M15PR_Pos 28
#define MATRIX_PRBS_M15PR_Msk (0x3u << MATRIX_PRBS_M15PR_Pos) /**< \brief (MATRIX_PRBS) Master 15 Priority */
#define MATRIX_PRBS_M15PR(value) ((MATRIX_PRBS_M15PR_Msk & ((value) << MATRIX_PRBS_M15PR_Pos)))
/* -------- MATRIX_MRCR : (MATRIX Offset: 0x0100) Master Remap Control Register -------- */
#define MATRIX_MRCR_RCB0 (0x1u << 0) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB1 (0x1u << 1) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB2 (0x1u << 2) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB3 (0x1u << 3) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB4 (0x1u << 4) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB5 (0x1u << 5) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB6 (0x1u << 6) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB7 (0x1u << 7) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB8 (0x1u << 8) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB9 (0x1u << 9) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB10 (0x1u << 10) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB11 (0x1u << 11) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB12 (0x1u << 12) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB13 (0x1u << 13) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB14 (0x1u << 14) /**< \brief (MATRIX_MRCR)  */
#define MATRIX_MRCR_RCB15 (0x1u << 15) /**< \brief (MATRIX_MRCR)  */
/* -------- MATRIX_SFR[16] : (MATRIX Offset: 0x0110) Special Function Register -------- */
#define MATRIX_SFR_SFR_Pos 0
#define MATRIX_SFR_SFR_Msk (0xffffffffu << MATRIX_SFR_SFR_Pos) /**< \brief (MATRIX_SFR[16]) Special Function Register Fields */
#define MATRIX_SFR_SFR(value) ((MATRIX_SFR_SFR_Msk & ((value) << MATRIX_SFR_SFR_Pos)))
/* -------- MATRIX_WPMR : (MATRIX Offset: 0x01E4) Write Protect Mode Register -------- */
#define MATRIX_WPMR_WPEN (0x1u << 0) /**< \brief (MATRIX_WPMR) Write Protect Enable */
#define MATRIX_WPMR_WPKEY_Pos 8
#define MATRIX_WPMR_WPKEY_Msk (0xffffffu << MATRIX_WPMR_WPKEY_Pos) /**< \brief (MATRIX_WPMR) Write Protect KEY (Write-only) */
#define MATRIX_WPMR_WPKEY(value) ((MATRIX_WPMR_WPKEY_Msk & ((value) << MATRIX_WPMR_WPKEY_Pos)))
/* -------- MATRIX_WPSR : (MATRIX Offset: 0x01E8) Write Protect Status Register -------- */
#define MATRIX_WPSR_WPVS (0x1u << 0) /**< \brief (MATRIX_WPSR) Write Protect Violation Status */
#define MATRIX_WPSR_WPVSRC_Pos 8
#define MATRIX_WPSR_WPVSRC_Msk (0xffffu << MATRIX_WPSR_WPVSRC_Pos) /**< \brief (MATRIX_WPSR) Write Protect Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR AHB Multi-port DDR-SDRAM Controller */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_MPDDRC AHB Multi-port DDR-SDRAM Controller */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Mpddrc hardware registers */
typedef struct {
  RwReg MPDDRC_MR;             /**< \brief (Mpddrc Offset: 0x00) MPDDRC Mode Register */
  RwReg MPDDRC_RTR;            /**< \brief (Mpddrc Offset: 0x04) MPDDRC Refresh Timer Register */
  RwReg MPDDRC_CR;             /**< \brief (Mpddrc Offset: 0x08) MPDDRC Configuration Register */
  RwReg MPDDRC_TPR0;           /**< \brief (Mpddrc Offset: 0x0C) MPDDRC Timing Parameter 0 Register */
  RwReg MPDDRC_TPR1;           /**< \brief (Mpddrc Offset: 0x10) MPDDRC Timing Parameter 1 Register */
  RwReg MPDDRC_TPR2;           /**< \brief (Mpddrc Offset: 0x14) MPDDRC Timing Parameter 2 Register */
  RoReg Reserved1[1];
  RwReg MPDDRC_LPR;            /**< \brief (Mpddrc Offset: 0x1C) MPDDRC Low-power Register */
  RwReg MPDDRC_MD;             /**< \brief (Mpddrc Offset: 0x20) MPDDRC Memory Device Register */
  RoReg Reserved2[1];
  RwReg MPDDRC_LPDDR2_LPR;     /**< \brief (Mpddrc Offset: 0x28) MPDDRC LPDDR2 Low-power Register */
  RwReg MPDDRC_LPDDR2_CAL_MR4; /**< \brief (Mpddrc Offset: 0x2C) MPDDRC LPDDR2 Calibration and MR4 Register */
  RwReg MPDDRC_LPDDR2_TIM_CAL; /**< \brief (Mpddrc Offset: 0x30) MPDDRC LPDDR2 Timing Calibration Register */
  RwReg MPDDRC_IO_CALIBR;      /**< \brief (Mpddrc Offset: 0x34) MPDDRC IO Calibration */
  RwReg MPDDRC_OCMS;           /**< \brief (Mpddrc Offset: 0x38) MPDDRC OCMS Register */
  WoReg MPDDRC_OCMS_KEY1;      /**< \brief (Mpddrc Offset: 0x3C) MPDDRC OCMS KEY1 Register */
  WoReg MPDDRC_OCMS_KEY2;      /**< \brief (Mpddrc Offset: 0x40) MPDDRC OCMS KEY2 Register */
  RoReg Reserved3[12];
  RwReg MPDDRC_DLL_MOR;        /**< \brief (Mpddrc Offset: 0x74) MPDDRC DLL Master Offset Register */
  RwReg MPDDRC_DLL_SOR;        /**< \brief (Mpddrc Offset: 0x78) MPDDRC DLL Slave Offset Register */
  RoReg MPDDRC_DLL_MSR;        /**< \brief (Mpddrc Offset: 0x7C) MPDDRC DLL Master Status Register */
  RoReg MPDDRC_DLL_SxSR[2];    /**< \brief (Mpddrc Offset: 0x80) MPDDRC DLL Slave 0 Status Register */
  RoReg Reserved4[23];
  RwReg MPDDRC_WPCR;           /**< \brief (Mpddrc Offset: 0xE4) MPDDRC Write Protect Control Register */
  RoReg MPDDRC_WPSR;           /**< \brief (Mpddrc Offset: 0xE8) MPDDRC Write Protect Status Register */
} Mpddrc;
#endif /* __ASSEMBLY__ */
/* -------- MPDDRC_MR : (MPDDRC Offset: 0x00) MPDDRC Mode Register -------- */
#define MPDDRC_MR_MODE_Pos 0
#define MPDDRC_MR_MODE_Msk (0x7u << MPDDRC_MR_MODE_Pos) /**< \brief (MPDDRC_MR) MPDDRC Command Mode */
#define   MPDDRC_MR_MODE_NORMAL_CMD (0x0u << 0) /**< \brief (MPDDRC_MR) Normal Mode. Any access to the MPDDRC will be decoded normally. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_NOP_CMD (0x1u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an NOP command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_PRCGALL_CMD (0x2u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an "All Banks Precharge" command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the SDRAM. */
#define   MPDDRC_MR_MODE_LMR_CMD (0x3u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues a "Load Mode Register" command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_RFSH_CMD (0x4u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an "Auto-Refresh" Command when the DDR-SDRAM device is accessed regardless of the cycle. Previously, an "All Banks Precharge" command must be issued. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_EXT_LMR_CMD (0x5u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an "Extended Load Mode Register" command when the SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. The write in the DDR-SDRAM must be done in the appropriate bank. */
#define   MPDDRC_MR_MODE_DEEP_CMD (0x6u << 0) /**< \brief (MPDDRC_MR) Deep power mode: Access to deep power-down mode */
#define   MPDDRC_MR_MODE_LPDDR2_CMD (0x7u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an "LPDDR2 Mode Register" command when the Low-power DDR2-SDRAM device is accessed regardless of the cycle. To activate this mode, the "Mode Register" command must be followed by a write to the Low-power DDR2-SDRAM. */
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
#define MPDDRC_CR_NC_Msk (0x3u << MPDDRC_CR_NC_Pos) /**< \brief (MPDDRC_CR) Number of Column Bits. */
#define   MPDDRC_CR_NC_9 (0x0u << 0) /**< \brief (MPDDRC_CR) 9 DDR column bits */
#define   MPDDRC_CR_NC_10 (0x1u << 0) /**< \brief (MPDDRC_CR) 10 DDR column bits */
#define   MPDDRC_CR_NC_11 (0x2u << 0) /**< \brief (MPDDRC_CR) 11 DDR column bits */
#define   MPDDRC_CR_NC_12 (0x3u << 0) /**< \brief (MPDDRC_CR) 12 DDR column bits */
#define   MPDDRC_CR_NC(value) ((MPDDRC_CR_NC_Msk & ((value) << MPDDRC_CR_NC_Pos)))
#define MPDDRC_CR_NR_Pos 2
#define MPDDRC_CR_NR_Msk (0x3u << MPDDRC_CR_NR_Pos) /**< \brief (MPDDRC_CR) Number of Row Bits */
#define   MPDDRC_CR_NR_11 (0x0u << 2) /**< \brief (MPDDRC_CR) 11 row bits */
#define   MPDDRC_CR_NR_12 (0x1u << 2) /**< \brief (MPDDRC_CR) 12 row bits */
#define   MPDDRC_CR_NR_13 (0x2u << 2) /**< \brief (MPDDRC_CR) 13 row bits */
#define   MPDDRC_CR_NR_14 (0x3u << 2) /**< \brief (MPDDRC_CR) 14 row bits */
#define   MPDDRC_CR_NR(value) ((MPDDRC_CR_NR_Msk & ((value) << MPDDRC_CR_NR_Pos)))
#define MPDDRC_CR_CAS_Pos 4
#define MPDDRC_CR_CAS_Msk (0x7u << MPDDRC_CR_CAS_Pos) /**< \brief (MPDDRC_CR) CAS Latency */
#define   MPDDRC_CR_CAS_2_DDR1 (0x2u << 4) /**< \brief (MPDDRC_CR) DDR1 CAS Latency 2 */
#define   MPDDRC_CR_CAS_3_DDR2 (0x3u << 4) /**< \brief (MPDDRC_CR) DDR2 CAS Latency 3 */
#define   MPDDRC_CR_CAS_3_LPDDR2 (0x3u << 4) /**< \brief (MPDDRC_CR) LPDDR2 CAS Latency 3 */
#define   MPDDRC_CR_CAS_3_DDR1 (0x3u << 4) /**< \brief (MPDDRC_CR) DDR1 CAS Latency 3 */
#define   MPDDRC_CR_CAS_4_DDR2 (0x4u << 4) /**< \brief (MPDDRC_CR) DDR2 CAS Latency 4 */
#define   MPDDRC_CR_CAS_4_LPDDR2 (0x4u << 4) /**< \brief (MPDDRC_CR) LPDDR2 CAS Latency 4 */
#define   MPDDRC_CR_CAS_5_DDR2 (0x5u << 4) /**< \brief (MPDDRC_CR) DDR2 CAS Latency 5 */
#define   MPDDRC_CR_CAS_5_LPDDR2 (0x5u << 4) /**< \brief (MPDDRC_CR) LPDDR2 CAS Latency 5 */
#define   MPDDRC_CR_CAS_6_DDR2 (0x6u << 4) /**< \brief (MPDDRC_CR) DDR2 CAS Latency 6 */
#define   MPDDRC_CR_CAS_2_5_DDR1 (0x6u << 4) /**< \brief (MPDDRC_CR) DDR1 CAS Latency 2.5 */
#define   MPDDRC_CR_CAS(value) ((MPDDRC_CR_CAS_Msk & ((value) << MPDDRC_CR_CAS_Pos)))
#define MPDDRC_CR_DLL (0x1u << 7) /**< \brief (MPDDRC_CR) Reset DLL */
#define   MPDDRC_CR_DLL_RESET_DISABLED (0x0u << 7) /**< \brief (MPDDRC_CR) Disable DLL reset. */
#define   MPDDRC_CR_DLL_RESET_ENABLED (0x1u << 7) /**< \brief (MPDDRC_CR) Enable DLL reset. */
#define MPDDRC_CR_DIC_DS (0x1u << 8) /**< \brief (MPDDRC_CR) Output Driver Impedance Control (Drive Strength) */
#define MPDDRC_CR_DIS_DLL (0x1u << 9) /**< \brief (MPDDRC_CR) DISABLE DLL */
#define MPDDRC_CR_ZQ_Pos 10
#define MPDDRC_CR_ZQ_Msk (0x3u << MPDDRC_CR_ZQ_Pos) /**< \brief (MPDDRC_CR) ZQ Calibration */
#define   MPDDRC_CR_ZQ_INIT (0x0u << 10) /**< \brief (MPDDRC_CR) Calibration command after initialization */
#define   MPDDRC_CR_ZQ_LONG (0x1u << 10) /**< \brief (MPDDRC_CR) Long calibration */
#define   MPDDRC_CR_ZQ_SHORT (0x2u << 10) /**< \brief (MPDDRC_CR) Short calibration */
#define   MPDDRC_CR_ZQ_RESET (0x3u << 10) /**< \brief (MPDDRC_CR) ZQ Reset */
#define MPDDRC_CR_OCD_Pos 12
#define MPDDRC_CR_OCD_Msk (0x7u << MPDDRC_CR_OCD_Pos) /**< \brief (MPDDRC_CR) Off-chip Driver */
#define MPDDRC_CR_OCD(value) ((MPDDRC_CR_OCD_Msk & ((value) << MPDDRC_CR_OCD_Pos)))
#define MPDDRC_CR_DQMS (0x1u << 16) /**< \brief (MPDDRC_CR) Mask Data is Shared */
#define   MPDDRC_CR_DQMS_NOT_SHARED (0x0u << 16) /**< \brief (MPDDRC_CR) DQM is not shared with another controller. */
#define   MPDDRC_CR_DQMS_SHARED (0x1u << 16) /**< \brief (MPDDRC_CR) DQM is shared with another controller. */
#define MPDDRC_CR_ENRDM (0x1u << 17) /**< \brief (MPDDRC_CR) Enable Read Measure */
#define   MPDDRC_CR_ENRDM_OFF (0x0u << 17) /**< \brief (MPDDRC_CR) DQS/DDR_DATA phase error correction is disabled. */
#define   MPDDRC_CR_ENRDM_ON (0x1u << 17) /**< \brief (MPDDRC_CR) DQS/DDR_DATA phase error correction is enabled. */
#define MPDDRC_CR_NB (0x1u << 20) /**< \brief (MPDDRC_CR) Number of Banks. */
#define   MPDDRC_CR_NB_4 (0x0u << 20) /**< \brief (MPDDRC_CR) 4 banks */
#define   MPDDRC_CR_NB_8 (0x1u << 20) /**< \brief (MPDDRC_CR) 8 banks */
#define MPDDRC_CR_NDQS (0x1u << 21) /**< \brief (MPDDRC_CR) Not DQS: */
#define   MPDDRC_CR_NDQS_ENABLED (0x0u << 21) /**< \brief (MPDDRC_CR) Not DQS is enabled. */
#define   MPDDRC_CR_NDQS_DISABLED (0x1u << 21) /**< \brief (MPDDRC_CR) Not DQS is disabled. */
#define MPDDRC_CR_DECOD (0x1u << 22) /**< \brief (MPDDRC_CR) Type of Decoding */
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
#define MPDDRC_TPR1_TRFC_Msk (0x1fu << MPDDRC_TPR1_TRFC_Pos) /**< \brief (MPDDRC_TPR1) Row Cycle Delay */
#define MPDDRC_TPR1_TRFC(value) ((MPDDRC_TPR1_TRFC_Msk & ((value) << MPDDRC_TPR1_TRFC_Pos)))
#define MPDDRC_TPR1_TXSNR_Pos 8
#define MPDDRC_TPR1_TXSNR_Msk (0xffu << MPDDRC_TPR1_TXSNR_Pos) /**< \brief (MPDDRC_TPR1) Exit Self Refresh Delay to Non Read Command */
#define MPDDRC_TPR1_TXSNR(value) ((MPDDRC_TPR1_TXSNR_Msk & ((value) << MPDDRC_TPR1_TXSNR_Pos)))
#define MPDDRC_TPR1_TXSRD_Pos 16
#define MPDDRC_TPR1_TXSRD_Msk (0xffu << MPDDRC_TPR1_TXSRD_Pos) /**< \brief (MPDDRC_TPR1) Exit Self Refresh Delay to Read Command */
#define MPDDRC_TPR1_TXSRD(value) ((MPDDRC_TPR1_TXSRD_Msk & ((value) << MPDDRC_TPR1_TXSRD_Pos)))
#define MPDDRC_TPR1_TXP_Pos 24
#define MPDDRC_TPR1_TXP_Msk (0xfu << MPDDRC_TPR1_TXP_Pos) /**< \brief (MPDDRC_TPR1) Exit Power-down Delay to First Command */
#define MPDDRC_TPR1_TXP(value) ((MPDDRC_TPR1_TXP_Msk & ((value) << MPDDRC_TPR1_TXP_Pos)))
/* -------- MPDDRC_TPR2 : (MPDDRC Offset: 0x14) MPDDRC Timing Parameter 2 Register -------- */
#define MPDDRC_TPR2_TXARD_Pos 0
#define MPDDRC_TPR2_TXARD_Msk (0xfu << MPDDRC_TPR2_TXARD_Pos) /**< \brief (MPDDRC_TPR2) Exit Active Power Down Delay to Read Command in Mode "Fast Exit". */
#define MPDDRC_TPR2_TXARD(value) ((MPDDRC_TPR2_TXARD_Msk & ((value) << MPDDRC_TPR2_TXARD_Pos)))
#define MPDDRC_TPR2_TXARDS_Pos 4
#define MPDDRC_TPR2_TXARDS_Msk (0xfu << MPDDRC_TPR2_TXARDS_Pos) /**< \brief (MPDDRC_TPR2) Exit Active Power Down Delay to Read Command in Mode "Slow Exit". */
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
#define   MPDDRC_LPR_LPCB_DISABLED (0x0u << 0) /**< \brief (MPDDRC_LPR) Low-power Feature is inhibited. No power-down, self refresh and deep-power modes are issued to the DDR-SDRAM device. */
#define   MPDDRC_LPR_LPCB_SELFREFRESH (0x1u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a Self Refresh command to the DDR-SDRAM device, the clock(s) is/are de-activated and the CKE signal is set low. The DDR-SDRAM device leaves the self refresh mode when accessed and reenters it after the access. */
#define   MPDDRC_LPR_LPCB_POWERDOWN (0x2u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a Power-down Command to the DDR-SDRAM device after each access, the CKE signal is set low. The DDR-SDRAM device leaves the power-down mode when accessed and reenters it after the access. */
#define   MPDDRC_LPR_LPCB_DEEP_PWD (0x3u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a Deep Power-down command to the Low-power DDR-SDRAM device. */
#define MPDDRC_LPR_CLK_FR (0x1u << 2) /**< \brief (MPDDRC_LPR) Clock Frozen Command Bit */
#define   MPDDRC_LPR_CLK_FR_DISABLED (0x0u << 2) /**< \brief (MPDDRC_LPR) Clock(s) is/are not frozen. */
#define   MPDDRC_LPR_CLK_FR_ENABLED (0x1u << 2) /**< \brief (MPDDRC_LPR) Clock(s) is/are frozen. */
#define MPDDRC_LPR_LPDDR2_PWOFF (0x1u << 3) /**< \brief (MPDDRC_LPR) LPDDR2 Power Off Bit */
#define   MPDDRC_LPR_LPDDR2_PWOFF_DISABLED (0x0u << 3) /**< \brief (MPDDRC_LPR) No power off sequence applied to LPDDR2. */
#define   MPDDRC_LPR_LPDDR2_PWOFF_ENABLED (0x1u << 3) /**< \brief (MPDDRC_LPR) A power off sequence is applied to the LPDDR2 device. CKE is forced low. */
#define MPDDRC_LPR_PASR_Pos 4
#define MPDDRC_LPR_PASR_Msk (0x7u << MPDDRC_LPR_PASR_Pos) /**< \brief (MPDDRC_LPR) Partial Array Self Refresh */
#define MPDDRC_LPR_PASR(value) ((MPDDRC_LPR_PASR_Msk & ((value) << MPDDRC_LPR_PASR_Pos)))
#define MPDDRC_LPR_DS_Pos 8
#define MPDDRC_LPR_DS_Msk (0x7u << MPDDRC_LPR_DS_Pos) /**< \brief (MPDDRC_LPR) Drive Strength */
#define MPDDRC_LPR_DS(value) ((MPDDRC_LPR_DS_Msk & ((value) << MPDDRC_LPR_DS_Pos)))
#define MPDDRC_LPR_TIMEOUT_Pos 12
#define MPDDRC_LPR_TIMEOUT_Msk (0x3u << MPDDRC_LPR_TIMEOUT_Pos) /**< \brief (MPDDRC_LPR) Enter Low-power Mode */
#define   MPDDRC_LPR_TIMEOUT_0 (0x0u << 12) /**< \brief (MPDDRC_LPR) The SDRAM controller activates the SDRAM low-power mode immediately after the end of the last transfer. */
#define   MPDDRC_LPR_TIMEOUT_64 (0x1u << 12) /**< \brief (MPDDRC_LPR) The SDRAM controller activates the SDRAM low-power mode 64 clock cycles after the end of the last transfer. */
#define   MPDDRC_LPR_TIMEOUT_128 (0x2u << 12) /**< \brief (MPDDRC_LPR) The SDRAM controller activates the SDRAM low-power mode 128 clock cycles after the end of the last transfer. */
#define MPDDRC_LPR_APDE (0x1u << 16) /**< \brief (MPDDRC_LPR) Active Power Down Exit Time */
#define   MPDDRC_LPR_APDE_FAST (0x0u << 16) /**< \brief (MPDDRC_LPR) Fast Exit. */
#define   MPDDRC_LPR_APDE_SLOW (0x1u << 16) /**< \brief (MPDDRC_LPR) Low Exit. */
#define MPDDRC_LPR_UPD_MR_Pos 20
#define MPDDRC_LPR_UPD_MR_Msk (0x3u << MPDDRC_LPR_UPD_MR_Pos) /**< \brief (MPDDRC_LPR) Update Load Mode Register and Extended Mode Register */
#define MPDDRC_LPR_UPD_MR(value) ((MPDDRC_LPR_UPD_MR_Msk & ((value) << MPDDRC_LPR_UPD_MR_Pos)))
/* -------- MPDDRC_MD : (MPDDRC Offset: 0x20) MPDDRC Memory Device Register -------- */
#define MPDDRC_MD_MD_Pos 0
#define MPDDRC_MD_MD_Msk (0x7u << MPDDRC_MD_MD_Pos) /**< \brief (MPDDRC_MD) Memory Device */
#define   MPDDRC_MD_MD_DDR_SDRAM (0x2u << 0) /**< \brief (MPDDRC_MD) DDR1-SDRAM */
#define   MPDDRC_MD_MD_LPDDR_SDRAM (0x3u << 0) /**< \brief (MPDDRC_MD) Low-power DDR1-SDRAM */
#define   MPDDRC_MD_MD_DDR2_SDRAM (0x6u << 0) /**< \brief (MPDDRC_MD) DDR2-SDRAM */
#define   MPDDRC_MD_MD_LPDDR2_SDRAM (0x7u << 0) /**< \brief (MPDDRC_MD) Low-Power DDR2-SDRAM */
#define MPDDRC_MD_DBW (0x1u << 4) /**< \brief (MPDDRC_MD) Data Bus Width */
/* -------- MPDDRC_LPDDR2_LPR : (MPDDRC Offset: 0x28) MPDDRC LPDDR2 Low-power Register -------- */
#define MPDDRC_LPDDR2_LPR_BK_MASK_Pos 0
#define MPDDRC_LPDDR2_LPR_BK_MASK_Msk (0xffu << MPDDRC_LPDDR2_LPR_BK_MASK_Pos) /**< \brief (MPDDRC_LPDDR2_LPR)  */
#define MPDDRC_LPDDR2_LPR_BK_MASK(value) ((MPDDRC_LPDDR2_LPR_BK_MASK_Msk & ((value) << MPDDRC_LPDDR2_LPR_BK_MASK_Pos)))
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
#define MPDDRC_IO_CALIBR_RDIV_Msk (0x7u << MPDDRC_IO_CALIBR_RDIV_Pos) /**< \brief (MPDDRC_IO_CALIBR) Resistor Divider */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_34 (0x1u << 0) /**< \brief (MPDDRC_IO_CALIBR) RZQ = 34,3 Ohm */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_40 (0x2u << 0) /**< \brief (MPDDRC_IO_CALIBR) RZQ = 40 Ohm */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_48 (0x3u << 0) /**< \brief (MPDDRC_IO_CALIBR) RZQ =48 Ohm */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_60 (0x4u << 0) /**< \brief (MPDDRC_IO_CALIBR) RZQ =60 Ohm */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_80 (0x6u << 0) /**< \brief (MPDDRC_IO_CALIBR) RZQ = 80 Ohm */
#define   MPDDRC_IO_CALIBR_RDIV_RZQ_120 (0x7u << 0) /**< \brief (MPDDRC_IO_CALIBR) RZQ = 120 Ohm */
#define MPDDRC_IO_CALIBR_TZQIO_Pos 8
#define MPDDRC_IO_CALIBR_TZQIO_Msk (0x1fu << MPDDRC_IO_CALIBR_TZQIO_Pos) /**< \brief (MPDDRC_IO_CALIBR) IO Calibration */
#define MPDDRC_IO_CALIBR_TZQIO(value) ((MPDDRC_IO_CALIBR_TZQIO_Msk & ((value) << MPDDRC_IO_CALIBR_TZQIO_Pos)))
#define MPDDRC_IO_CALIBR_CALCODEP_Pos 16
#define MPDDRC_IO_CALIBR_CALCODEP_Msk (0xfu << MPDDRC_IO_CALIBR_CALCODEP_Pos) /**< \brief (MPDDRC_IO_CALIBR) Number of Transistor P */
#define MPDDRC_IO_CALIBR_CALCODEP(value) ((MPDDRC_IO_CALIBR_CALCODEP_Msk & ((value) << MPDDRC_IO_CALIBR_CALCODEP_Pos)))
#define MPDDRC_IO_CALIBR_CALCODEN_Pos 20
#define MPDDRC_IO_CALIBR_CALCODEN_Msk (0xfu << MPDDRC_IO_CALIBR_CALCODEN_Pos) /**< \brief (MPDDRC_IO_CALIBR) Number of Transistor N */
#define MPDDRC_IO_CALIBR_CALCODEN(value) ((MPDDRC_IO_CALIBR_CALCODEN_Msk & ((value) << MPDDRC_IO_CALIBR_CALCODEN_Pos)))
/* -------- MPDDRC_OCMS_KEY1 : (MPDDRC Offset: 0x3C) MPDDRC OCMS KEY1 Register -------- */
#define MPDDRC_OCMS_KEY1_KEY1n_Pos 0
#define MPDDRC_OCMS_KEY1_KEY1n_Msk (0xffu << MPDDRC_OCMS_KEY1_KEY1n_Pos) /**< \brief (MPDDRC_OCMS_KEY1)  */
#define MPDDRC_OCMS_KEY1_KEY1n(value) ((MPDDRC_OCMS_KEY1_KEY1n_Msk & ((value) << MPDDRC_OCMS_KEY1_KEY1n_Pos)))
#define MPDDRC_OCMS_KEY1_KEY1_Pos 8
#define MPDDRC_OCMS_KEY1_KEY1_Msk (0xffffffu << MPDDRC_OCMS_KEY1_KEY1_Pos) /**< \brief (MPDDRC_OCMS_KEY1) Off Chip Memory Scrambling (OCMS) Key Part 1 */
#define MPDDRC_OCMS_KEY1_KEY1(value) ((MPDDRC_OCMS_KEY1_KEY1_Msk & ((value) << MPDDRC_OCMS_KEY1_KEY1_Pos)))
/* -------- MPDDRC_OCMS_KEY2 : (MPDDRC Offset: 0x40) MPDDRC OCMS KEY2 Register -------- */
#define MPDDRC_OCMS_KEY2_KEY2_Pos 0
#define MPDDRC_OCMS_KEY2_KEY2_Msk (0xffffffffu << MPDDRC_OCMS_KEY2_KEY2_Pos) /**< \brief (MPDDRC_OCMS_KEY2) Off Chip Memory Scrambling (OCMS) Key Part 2 */
#define MPDDRC_OCMS_KEY2_KEY2(value) ((MPDDRC_OCMS_KEY2_KEY2_Msk & ((value) << MPDDRC_OCMS_KEY2_KEY2_Pos)))
/* -------- MPDDRC_DLL_MOR : (MPDDRC Offset: 0x74) MPDDRC DLL Master Offset Register -------- */
#define MPDDRC_DLL_MOR_MOFF_Pos 0
#define MPDDRC_DLL_MOR_MOFF_Msk (0xfu << MPDDRC_DLL_MOR_MOFF_Pos) /**< \brief (MPDDRC_DLL_MOR) DLL Master Delay Line Offset */
#define MPDDRC_DLL_MOR_MOFF(value) ((MPDDRC_DLL_MOR_MOFF_Msk & ((value) << MPDDRC_DLL_MOR_MOFF_Pos)))
#define MPDDRC_DLL_MOR_CLK90OFF_Pos 8
#define MPDDRC_DLL_MOR_CLK90OFF_Msk (0x1fu << MPDDRC_DLL_MOR_CLK90OFF_Pos) /**< \brief (MPDDRC_DLL_MOR) DLL CLK90 Delay Line Offset */
#define MPDDRC_DLL_MOR_CLK90OFF(value) ((MPDDRC_DLL_MOR_CLK90OFF_Msk & ((value) << MPDDRC_DLL_MOR_CLK90OFF_Pos)))
#define MPDDRC_DLL_MOR_SELOFF (0x1u << 16) /**< \brief (MPDDRC_DLL_MOR) DLL Offset Selection */
/* -------- MPDDRC_DLL_MSR : (MPDDRC Offset: 0x7C) MPDDRC DLL Master Status Register -------- */
#define MPDDRC_DLL_MSR_MDINC (0x1u << 0) /**< \brief (MPDDRC_DLL_MSR) DLL Master Delay Increment */
#define MPDDRC_DLL_MSR_MDDEC (0x1u << 1) /**< \brief (MPDDRC_DLL_MSR) DLL Master Delay Decrement */
#define MPDDRC_DLL_MSR_MDOVF (0x1u << 2) /**< \brief (MPDDRC_DLL_MSR) DLL Master Delay Overflow Flag */
#define MPDDRC_DLL_MSR_MDVAL_Pos 8
#define MPDDRC_DLL_MSR_MDVAL_Msk (0xffu << MPDDRC_DLL_MSR_MDVAL_Pos) /**< \brief (MPDDRC_DLL_MSR) DLL Master Delay Value */
/* -------- MPDDRC_DLL_S0SR : (MPDDRC Offset: 0x80) MPDDRC DLL Slave 0 Status Register -------- */
#define MPDDRC_DLL_S0SR_SDCOVF (0x1u << 0) /**< \brief (MPDDRC_DLL_S0SR) DLL Slave x Delay Correction Overflow Flag */
#define MPDDRC_DLL_S0SR_SDCUDF (0x1u << 1) /**< \brief (MPDDRC_DLL_S0SR) DLL Slave x Delay Correction Underflow Flag */
#define MPDDRC_DLL_S0SR_SDERF (0x1u << 2) /**< \brief (MPDDRC_DLL_S0SR) DLL Slave x Delay Correction Error Flag */
#define MPDDRC_DLL_S0SR_SDVAL_Pos 8
#define MPDDRC_DLL_S0SR_SDVAL_Msk (0xffu << MPDDRC_DLL_S0SR_SDVAL_Pos) /**< \brief (MPDDRC_DLL_S0SR) DLL Slave x Delay Value */
#define MPDDRC_DLL_S0SR_SDCVAL_Pos 16
#define MPDDRC_DLL_S0SR_SDCVAL_Msk (0xffu << MPDDRC_DLL_S0SR_SDCVAL_Pos) /**< \brief (MPDDRC_DLL_S0SR) DLL Slave x Delay Correction Value */
/* -------- MPDDRC_DLL_S1SR : (MPDDRC Offset: 0x84) MPDDRC DLL Slave 1 Status Register -------- */
#define MPDDRC_DLL_S1SR_SDCOVF (0x1u << 0) /**< \brief (MPDDRC_DLL_S1SR) DLL Slave x Delay Correction Overflow Flag */
#define MPDDRC_DLL_S1SR_SDCUDF (0x1u << 1) /**< \brief (MPDDRC_DLL_S1SR) DLL Slave x Delay Correction Underflow Flag */
#define MPDDRC_DLL_S1SR_SDERF (0x1u << 2) /**< \brief (MPDDRC_DLL_S1SR) DLL Slave x Delay Correction Error Flag */
#define MPDDRC_DLL_S1SR_SDVAL_Pos 8
#define MPDDRC_DLL_S1SR_SDVAL_Msk (0xffu << MPDDRC_DLL_S1SR_SDVAL_Pos) /**< \brief (MPDDRC_DLL_S1SR) DLL Slave x Delay Value */
#define MPDDRC_DLL_S1SR_SDCVAL_Pos 16
#define MPDDRC_DLL_S1SR_SDCVAL_Msk (0xffu << MPDDRC_DLL_S1SR_SDCVAL_Pos) /**< \brief (MPDDRC_DLL_S1SR) DLL Slave x Delay Correction Value */
/* -------- MPDDRC_WPCR : (MPDDRC Offset: 0xE4) MPDDRC Write Protect Control Register -------- */
#define MPDDRC_WPCR_WPEN (0x1u << 0) /**< \brief (MPDDRC_WPCR) Write Protection Enable */
#define MPDDRC_WPCR_WPKEY_Pos 8
#define MPDDRC_WPCR_WPKEY_Msk (0xffffffu << MPDDRC_WPCR_WPKEY_Pos) /**< \brief (MPDDRC_WPCR) Write Protection KEY */
#define MPDDRC_WPCR_WPKEY(value) ((MPDDRC_WPCR_WPKEY_Msk & ((value) << MPDDRC_WPCR_WPKEY_Pos)))
/* -------- MPDDRC_WPSR : (MPDDRC Offset: 0xE8) MPDDRC Write Protect Status Register -------- */
#define MPDDRC_WPSR_WPVS (0x1u << 0) /**< \brief (MPDDRC_WPSR) Write Protection Enable */
#define MPDDRC_WPSR_WPVSRC_Pos 8
#define MPDDRC_WPSR_WPVSRC_Msk (0xffffu << MPDDRC_WPSR_WPVSRC_Pos) /**< \brief (MPDDRC_WPSR) Write Protection Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Parallel Input/Output Controller */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_PIO Parallel Input/Output Controller */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Pio hardware registers */
typedef struct {
  WoReg PIO_PER;       /**< \brief (Pio Offset: 0x0000) PIO Enable Register */
  WoReg PIO_PDR;       /**< \brief (Pio Offset: 0x0004) PIO Disable Register */
  RoReg PIO_PSR;       /**< \brief (Pio Offset: 0x0008) PIO Status Register */
  RoReg Reserved1[1];
  WoReg PIO_OER;       /**< \brief (Pio Offset: 0x0010) Output Enable Register */
  WoReg PIO_ODR;       /**< \brief (Pio Offset: 0x0014) Output Disable Register */
  RoReg PIO_OSR;       /**< \brief (Pio Offset: 0x0018) Output Status Register */
  RoReg Reserved2[1];
  WoReg PIO_IFER;      /**< \brief (Pio Offset: 0x0020) Glitch Input Filter Enable Register */
  WoReg PIO_IFDR;      /**< \brief (Pio Offset: 0x0024) Glitch Input Filter Disable Register */
  RoReg PIO_IFSR;      /**< \brief (Pio Offset: 0x0028) Glitch Input Filter Status Register */
  RoReg Reserved3[1];
  WoReg PIO_SODR;      /**< \brief (Pio Offset: 0x0030) Set Output Data Register */
  WoReg PIO_CODR;      /**< \brief (Pio Offset: 0x0034) Clear Output Data Register */
  RwReg PIO_ODSR;      /**< \brief (Pio Offset: 0x0038) Output Data Status Register */
  RoReg PIO_PDSR;      /**< \brief (Pio Offset: 0x003C) Pin Data Status Register */
  WoReg PIO_IER;       /**< \brief (Pio Offset: 0x0040) Interrupt Enable Register */
  WoReg PIO_IDR;       /**< \brief (Pio Offset: 0x0044) Interrupt Disable Register */
  RoReg PIO_IMR;       /**< \brief (Pio Offset: 0x0048) Interrupt Mask Register */
  RoReg PIO_ISR;       /**< \brief (Pio Offset: 0x004C) Interrupt Status Register */
  WoReg PIO_MDER;      /**< \brief (Pio Offset: 0x0050) Multi-driver Enable Register */
  WoReg PIO_MDDR;      /**< \brief (Pio Offset: 0x0054) Multi-driver Disable Register */
  RoReg PIO_MDSR;      /**< \brief (Pio Offset: 0x0058) Multi-driver Status Register */
  RoReg Reserved4[1];
  WoReg PIO_PUDR;      /**< \brief (Pio Offset: 0x0060) Pull-up Disable Register */
  WoReg PIO_PUER;      /**< \brief (Pio Offset: 0x0064) Pull-up Enable Register */
  RoReg PIO_PUSR;      /**< \brief (Pio Offset: 0x0068) Pad Pull-up Status Register */
  RoReg Reserved5[1];
  RwReg PIO_ABCDSR[2]; /**< \brief (Pio Offset: 0x0070) Peripheral Select Register */
  RoReg Reserved6[2];
  WoReg PIO_IFSCDR;    /**< \brief (Pio Offset: 0x0080) Input Filter Slow Clock Disable Register */
  WoReg PIO_IFSCER;    /**< \brief (Pio Offset: 0x0084) Input Filter Slow Clock Enable Register */
  RoReg PIO_IFSCSR;    /**< \brief (Pio Offset: 0x0088) Input Filter Slow Clock Status Register */
  RwReg PIO_SCDR;      /**< \brief (Pio Offset: 0x008C) Slow Clock Divider Debouncing Register */
  WoReg PIO_PPDDR;     /**< \brief (Pio Offset: 0x0090) Pad Pull-down Disable Register */
  WoReg PIO_PPDER;     /**< \brief (Pio Offset: 0x0094) Pad Pull-down Enable Register */
  RoReg PIO_PPDSR;     /**< \brief (Pio Offset: 0x0098) Pad Pull-down Status Register */
  RoReg Reserved7[1];
  WoReg PIO_OWER;      /**< \brief (Pio Offset: 0x00A0) Output Write Enable */
  WoReg PIO_OWDR;      /**< \brief (Pio Offset: 0x00A4) Output Write Disable */
  RoReg PIO_OWSR;      /**< \brief (Pio Offset: 0x00A8) Output Write Status Register */
  RoReg Reserved8[1];
  WoReg PIO_AIMER;     /**< \brief (Pio Offset: 0x00B0) Additional Interrupt Modes Enable Register */
  WoReg PIO_AIMDR;     /**< \brief (Pio Offset: 0x00B4) Additional Interrupt Modes Disables Register */
  RoReg PIO_AIMMR;     /**< \brief (Pio Offset: 0x00B8) Additional Interrupt Modes Mask Register */
  RoReg Reserved9[1];
  WoReg PIO_ESR;       /**< \brief (Pio Offset: 0x00C0) Edge Select Register */
  WoReg PIO_LSR;       /**< \brief (Pio Offset: 0x00C4) Level Select Register */
  RoReg PIO_ELSR;      /**< \brief (Pio Offset: 0x00C8) Edge/Level Status Register */
  RoReg Reserved10[1];
  WoReg PIO_FELLSR;    /**< \brief (Pio Offset: 0x00D0) Falling Edge/Low Level Select Register */
  WoReg PIO_REHLSR;    /**< \brief (Pio Offset: 0x00D4) Rising Edge/ High Level Select Register */
  RoReg PIO_FRLHSR;    /**< \brief (Pio Offset: 0x00D8) Fall/Rise - Low/High Status Register */
  RoReg Reserved11[1];
  RoReg PIO_LOCKSR;    /**< \brief (Pio Offset: 0x00E0) Lock Status */
  RwReg PIO_WPMR;      /**< \brief (Pio Offset: 0x00E4) Write Protect Mode Register */
  RoReg PIO_WPSR;      /**< \brief (Pio Offset: 0x00E8) Write Protect Status Register */
  RoReg Reserved12[5];
  RwReg PIO_SCHMITT;   /**< \brief (Pio Offset: 0x0100) Schmitt Trigger Register */
  RoReg Reserved13[5];
  RwReg PIO_DRIVER1;   /**< \brief (Pio Offset: 0x0118) I/O Drive Register 1 */
  RwReg PIO_DRIVER2;   /**< \brief (Pio Offset: 0x011C) I/O Drive Register 2 */
} Pio;
#endif /* __ASSEMBLY__ */
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
#define PIO_MDER_P0 (0x1u << 0) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P1 (0x1u << 1) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P2 (0x1u << 2) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P3 (0x1u << 3) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P4 (0x1u << 4) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P5 (0x1u << 5) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P6 (0x1u << 6) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P7 (0x1u << 7) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P8 (0x1u << 8) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P9 (0x1u << 9) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P10 (0x1u << 10) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P11 (0x1u << 11) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P12 (0x1u << 12) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P13 (0x1u << 13) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P14 (0x1u << 14) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P15 (0x1u << 15) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P16 (0x1u << 16) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P17 (0x1u << 17) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P18 (0x1u << 18) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P19 (0x1u << 19) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P20 (0x1u << 20) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P21 (0x1u << 21) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P22 (0x1u << 22) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P23 (0x1u << 23) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P24 (0x1u << 24) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P25 (0x1u << 25) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P26 (0x1u << 26) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P27 (0x1u << 27) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P28 (0x1u << 28) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P29 (0x1u << 29) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P30 (0x1u << 30) /**< \brief (PIO_MDER) Multi Drive Enable. */
#define PIO_MDER_P31 (0x1u << 31) /**< \brief (PIO_MDER) Multi Drive Enable. */
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
#define PIO_SCDR_DIV_Msk (0x3fffu << PIO_SCDR_DIV_Pos) /**< \brief (PIO_SCDR)  */
#define PIO_SCDR_DIV(value) ((PIO_SCDR_DIV_Msk & ((value) << PIO_SCDR_DIV_Pos)))
/* -------- PIO_PPDDR : (PIO Offset: 0x0090) Pad Pull-down Disable Register -------- */
#define PIO_PPDDR_P0 (0x1u << 0) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P1 (0x1u << 1) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P2 (0x1u << 2) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P3 (0x1u << 3) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P4 (0x1u << 4) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P5 (0x1u << 5) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P6 (0x1u << 6) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P7 (0x1u << 7) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P8 (0x1u << 8) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P9 (0x1u << 9) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P10 (0x1u << 10) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P11 (0x1u << 11) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P12 (0x1u << 12) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P13 (0x1u << 13) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P14 (0x1u << 14) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P15 (0x1u << 15) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P16 (0x1u << 16) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P17 (0x1u << 17) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P18 (0x1u << 18) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P19 (0x1u << 19) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P20 (0x1u << 20) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P21 (0x1u << 21) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P22 (0x1u << 22) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P23 (0x1u << 23) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P24 (0x1u << 24) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P25 (0x1u << 25) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P26 (0x1u << 26) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P27 (0x1u << 27) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P28 (0x1u << 28) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P29 (0x1u << 29) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P30 (0x1u << 30) /**< \brief (PIO_PPDDR) Pull Down Disable. */
#define PIO_PPDDR_P31 (0x1u << 31) /**< \brief (PIO_PPDDR) Pull Down Disable. */
/* -------- PIO_PPDER : (PIO Offset: 0x0094) Pad Pull-down Enable Register -------- */
#define PIO_PPDER_P0 (0x1u << 0) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P1 (0x1u << 1) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P2 (0x1u << 2) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P3 (0x1u << 3) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P4 (0x1u << 4) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P5 (0x1u << 5) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P6 (0x1u << 6) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P7 (0x1u << 7) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P8 (0x1u << 8) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P9 (0x1u << 9) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P10 (0x1u << 10) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P11 (0x1u << 11) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P12 (0x1u << 12) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P13 (0x1u << 13) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P14 (0x1u << 14) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P15 (0x1u << 15) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P16 (0x1u << 16) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P17 (0x1u << 17) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P18 (0x1u << 18) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P19 (0x1u << 19) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P20 (0x1u << 20) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P21 (0x1u << 21) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P22 (0x1u << 22) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P23 (0x1u << 23) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P24 (0x1u << 24) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P25 (0x1u << 25) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P26 (0x1u << 26) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P27 (0x1u << 27) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P28 (0x1u << 28) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P29 (0x1u << 29) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P30 (0x1u << 30) /**< \brief (PIO_PPDER) Pull Down Enable. */
#define PIO_PPDER_P31 (0x1u << 31) /**< \brief (PIO_PPDER) Pull Down Enable. */
/* -------- PIO_PPDSR : (PIO Offset: 0x0098) Pad Pull-down Status Register -------- */
#define PIO_PPDSR_P0 (0x1u << 0) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P1 (0x1u << 1) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P2 (0x1u << 2) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P3 (0x1u << 3) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P4 (0x1u << 4) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P5 (0x1u << 5) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P6 (0x1u << 6) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P7 (0x1u << 7) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P8 (0x1u << 8) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P9 (0x1u << 9) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P10 (0x1u << 10) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P11 (0x1u << 11) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P12 (0x1u << 12) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P13 (0x1u << 13) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P14 (0x1u << 14) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P15 (0x1u << 15) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P16 (0x1u << 16) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P17 (0x1u << 17) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P18 (0x1u << 18) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P19 (0x1u << 19) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P20 (0x1u << 20) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P21 (0x1u << 21) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P22 (0x1u << 22) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P23 (0x1u << 23) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P24 (0x1u << 24) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P25 (0x1u << 25) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P26 (0x1u << 26) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P27 (0x1u << 27) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P28 (0x1u << 28) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P29 (0x1u << 29) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P30 (0x1u << 30) /**< \brief (PIO_PPDSR) Pull Down Status. */
#define PIO_PPDSR_P31 (0x1u << 31) /**< \brief (PIO_PPDSR) Pull Down Status. */
/* -------- PIO_OWER : (PIO Offset: 0x00A0) Output Write Enable -------- */
#define PIO_OWER_P0 (0x1u << 0) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P1 (0x1u << 1) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P2 (0x1u << 2) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P3 (0x1u << 3) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P4 (0x1u << 4) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P5 (0x1u << 5) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P6 (0x1u << 6) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P7 (0x1u << 7) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P8 (0x1u << 8) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P9 (0x1u << 9) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P10 (0x1u << 10) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P11 (0x1u << 11) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P12 (0x1u << 12) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P13 (0x1u << 13) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P14 (0x1u << 14) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P15 (0x1u << 15) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P16 (0x1u << 16) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P17 (0x1u << 17) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P18 (0x1u << 18) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P19 (0x1u << 19) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P20 (0x1u << 20) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P21 (0x1u << 21) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P22 (0x1u << 22) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P23 (0x1u << 23) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P24 (0x1u << 24) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P25 (0x1u << 25) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P26 (0x1u << 26) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P27 (0x1u << 27) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P28 (0x1u << 28) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P29 (0x1u << 29) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P30 (0x1u << 30) /**< \brief (PIO_OWER) Output Write Enable. */
#define PIO_OWER_P31 (0x1u << 31) /**< \brief (PIO_OWER) Output Write Enable. */
/* -------- PIO_OWDR : (PIO Offset: 0x00A4) Output Write Disable -------- */
#define PIO_OWDR_P0 (0x1u << 0) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P1 (0x1u << 1) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P2 (0x1u << 2) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P3 (0x1u << 3) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P4 (0x1u << 4) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P5 (0x1u << 5) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P6 (0x1u << 6) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P7 (0x1u << 7) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P8 (0x1u << 8) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P9 (0x1u << 9) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P10 (0x1u << 10) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P11 (0x1u << 11) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P12 (0x1u << 12) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P13 (0x1u << 13) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P14 (0x1u << 14) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P15 (0x1u << 15) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P16 (0x1u << 16) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P17 (0x1u << 17) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P18 (0x1u << 18) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P19 (0x1u << 19) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P20 (0x1u << 20) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P21 (0x1u << 21) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P22 (0x1u << 22) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P23 (0x1u << 23) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P24 (0x1u << 24) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P25 (0x1u << 25) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P26 (0x1u << 26) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P27 (0x1u << 27) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P28 (0x1u << 28) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P29 (0x1u << 29) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P30 (0x1u << 30) /**< \brief (PIO_OWDR) Output Write Disable. */
#define PIO_OWDR_P31 (0x1u << 31) /**< \brief (PIO_OWDR) Output Write Disable. */
/* -------- PIO_OWSR : (PIO Offset: 0x00A8) Output Write Status Register -------- */
#define PIO_OWSR_P0 (0x1u << 0) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P1 (0x1u << 1) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P2 (0x1u << 2) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P3 (0x1u << 3) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P4 (0x1u << 4) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P5 (0x1u << 5) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P6 (0x1u << 6) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P7 (0x1u << 7) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P8 (0x1u << 8) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P9 (0x1u << 9) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P10 (0x1u << 10) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P11 (0x1u << 11) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P12 (0x1u << 12) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P13 (0x1u << 13) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P14 (0x1u << 14) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P15 (0x1u << 15) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P16 (0x1u << 16) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P17 (0x1u << 17) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P18 (0x1u << 18) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P19 (0x1u << 19) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P20 (0x1u << 20) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P21 (0x1u << 21) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P22 (0x1u << 22) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P23 (0x1u << 23) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P24 (0x1u << 24) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P25 (0x1u << 25) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P26 (0x1u << 26) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P27 (0x1u << 27) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P28 (0x1u << 28) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P29 (0x1u << 29) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P30 (0x1u << 30) /**< \brief (PIO_OWSR) Output Write Status. */
#define PIO_OWSR_P31 (0x1u << 31) /**< \brief (PIO_OWSR) Output Write Status. */
/* -------- PIO_AIMER : (PIO Offset: 0x00B0) Additional Interrupt Modes Enable Register -------- */
#define PIO_AIMER_P0 (0x1u << 0) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P1 (0x1u << 1) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P2 (0x1u << 2) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P3 (0x1u << 3) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P4 (0x1u << 4) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P5 (0x1u << 5) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P6 (0x1u << 6) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P7 (0x1u << 7) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P8 (0x1u << 8) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P9 (0x1u << 9) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P10 (0x1u << 10) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P11 (0x1u << 11) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P12 (0x1u << 12) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P13 (0x1u << 13) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P14 (0x1u << 14) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P15 (0x1u << 15) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P16 (0x1u << 16) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P17 (0x1u << 17) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P18 (0x1u << 18) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P19 (0x1u << 19) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P20 (0x1u << 20) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P21 (0x1u << 21) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P22 (0x1u << 22) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P23 (0x1u << 23) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P24 (0x1u << 24) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P25 (0x1u << 25) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P26 (0x1u << 26) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P27 (0x1u << 27) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P28 (0x1u << 28) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P29 (0x1u << 29) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P30 (0x1u << 30) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
#define PIO_AIMER_P31 (0x1u << 31) /**< \brief (PIO_AIMER) Additional Interrupt Modes Enable. */
/* -------- PIO_AIMDR : (PIO Offset: 0x00B4) Additional Interrupt Modes Disables Register -------- */
#define PIO_AIMDR_P0 (0x1u << 0) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P1 (0x1u << 1) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P2 (0x1u << 2) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P3 (0x1u << 3) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P4 (0x1u << 4) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P5 (0x1u << 5) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P6 (0x1u << 6) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P7 (0x1u << 7) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P8 (0x1u << 8) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P9 (0x1u << 9) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P10 (0x1u << 10) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P11 (0x1u << 11) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P12 (0x1u << 12) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P13 (0x1u << 13) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P14 (0x1u << 14) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P15 (0x1u << 15) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P16 (0x1u << 16) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P17 (0x1u << 17) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P18 (0x1u << 18) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P19 (0x1u << 19) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P20 (0x1u << 20) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P21 (0x1u << 21) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P22 (0x1u << 22) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P23 (0x1u << 23) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P24 (0x1u << 24) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P25 (0x1u << 25) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P26 (0x1u << 26) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P27 (0x1u << 27) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P28 (0x1u << 28) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P29 (0x1u << 29) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P30 (0x1u << 30) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
#define PIO_AIMDR_P31 (0x1u << 31) /**< \brief (PIO_AIMDR) Additional Interrupt Modes Disable. */
/* -------- PIO_AIMMR : (PIO Offset: 0x00B8) Additional Interrupt Modes Mask Register -------- */
#define PIO_AIMMR_P0 (0x1u << 0) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P1 (0x1u << 1) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P2 (0x1u << 2) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P3 (0x1u << 3) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P4 (0x1u << 4) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P5 (0x1u << 5) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P6 (0x1u << 6) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P7 (0x1u << 7) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P8 (0x1u << 8) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P9 (0x1u << 9) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P10 (0x1u << 10) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P11 (0x1u << 11) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P12 (0x1u << 12) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P13 (0x1u << 13) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P14 (0x1u << 14) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P15 (0x1u << 15) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P16 (0x1u << 16) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P17 (0x1u << 17) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P18 (0x1u << 18) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P19 (0x1u << 19) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P20 (0x1u << 20) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P21 (0x1u << 21) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P22 (0x1u << 22) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P23 (0x1u << 23) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P24 (0x1u << 24) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P25 (0x1u << 25) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P26 (0x1u << 26) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P27 (0x1u << 27) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P28 (0x1u << 28) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P29 (0x1u << 29) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P30 (0x1u << 30) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
#define PIO_AIMMR_P31 (0x1u << 31) /**< \brief (PIO_AIMMR) Peripheral CD Status. */
/* -------- PIO_ESR : (PIO Offset: 0x00C0) Edge Select Register -------- */
#define PIO_ESR_P0 (0x1u << 0) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P1 (0x1u << 1) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P2 (0x1u << 2) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P3 (0x1u << 3) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P4 (0x1u << 4) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P5 (0x1u << 5) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P6 (0x1u << 6) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P7 (0x1u << 7) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P8 (0x1u << 8) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P9 (0x1u << 9) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P10 (0x1u << 10) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P11 (0x1u << 11) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P12 (0x1u << 12) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P13 (0x1u << 13) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P14 (0x1u << 14) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P15 (0x1u << 15) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P16 (0x1u << 16) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P17 (0x1u << 17) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P18 (0x1u << 18) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P19 (0x1u << 19) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P20 (0x1u << 20) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P21 (0x1u << 21) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P22 (0x1u << 22) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P23 (0x1u << 23) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P24 (0x1u << 24) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P25 (0x1u << 25) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P26 (0x1u << 26) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P27 (0x1u << 27) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P28 (0x1u << 28) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P29 (0x1u << 29) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P30 (0x1u << 30) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
#define PIO_ESR_P31 (0x1u << 31) /**< \brief (PIO_ESR) Edge Interrupt Selection. */
/* -------- PIO_LSR : (PIO Offset: 0x00C4) Level Select Register -------- */
#define PIO_LSR_P0 (0x1u << 0) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P1 (0x1u << 1) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P2 (0x1u << 2) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P3 (0x1u << 3) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P4 (0x1u << 4) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P5 (0x1u << 5) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P6 (0x1u << 6) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P7 (0x1u << 7) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P8 (0x1u << 8) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P9 (0x1u << 9) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P10 (0x1u << 10) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P11 (0x1u << 11) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P12 (0x1u << 12) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P13 (0x1u << 13) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P14 (0x1u << 14) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P15 (0x1u << 15) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P16 (0x1u << 16) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P17 (0x1u << 17) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P18 (0x1u << 18) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P19 (0x1u << 19) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P20 (0x1u << 20) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P21 (0x1u << 21) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P22 (0x1u << 22) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P23 (0x1u << 23) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P24 (0x1u << 24) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P25 (0x1u << 25) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P26 (0x1u << 26) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P27 (0x1u << 27) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P28 (0x1u << 28) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P29 (0x1u << 29) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P30 (0x1u << 30) /**< \brief (PIO_LSR) Level Interrupt Selection. */
#define PIO_LSR_P31 (0x1u << 31) /**< \brief (PIO_LSR) Level Interrupt Selection. */
/* -------- PIO_ELSR : (PIO Offset: 0x00C8) Edge/Level Status Register -------- */
#define PIO_ELSR_P0 (0x1u << 0) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P1 (0x1u << 1) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P2 (0x1u << 2) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P3 (0x1u << 3) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P4 (0x1u << 4) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P5 (0x1u << 5) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P6 (0x1u << 6) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P7 (0x1u << 7) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P8 (0x1u << 8) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P9 (0x1u << 9) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P10 (0x1u << 10) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P11 (0x1u << 11) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P12 (0x1u << 12) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P13 (0x1u << 13) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P14 (0x1u << 14) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P15 (0x1u << 15) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P16 (0x1u << 16) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P17 (0x1u << 17) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P18 (0x1u << 18) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P19 (0x1u << 19) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P20 (0x1u << 20) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P21 (0x1u << 21) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P22 (0x1u << 22) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P23 (0x1u << 23) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P24 (0x1u << 24) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P25 (0x1u << 25) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P26 (0x1u << 26) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P27 (0x1u << 27) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P28 (0x1u << 28) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P29 (0x1u << 29) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P30 (0x1u << 30) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
#define PIO_ELSR_P31 (0x1u << 31) /**< \brief (PIO_ELSR) Edge/Level Interrupt source selection. */
/* -------- PIO_FELLSR : (PIO Offset: 0x00D0) Falling Edge/Low Level Select Register -------- */
#define PIO_FELLSR_P0 (0x1u << 0) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P1 (0x1u << 1) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P2 (0x1u << 2) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P3 (0x1u << 3) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P4 (0x1u << 4) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P5 (0x1u << 5) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P6 (0x1u << 6) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P7 (0x1u << 7) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P8 (0x1u << 8) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P9 (0x1u << 9) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P10 (0x1u << 10) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P11 (0x1u << 11) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P12 (0x1u << 12) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P13 (0x1u << 13) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P14 (0x1u << 14) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P15 (0x1u << 15) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P16 (0x1u << 16) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P17 (0x1u << 17) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P18 (0x1u << 18) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P19 (0x1u << 19) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P20 (0x1u << 20) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P21 (0x1u << 21) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P22 (0x1u << 22) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P23 (0x1u << 23) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P24 (0x1u << 24) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P25 (0x1u << 25) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P26 (0x1u << 26) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P27 (0x1u << 27) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P28 (0x1u << 28) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P29 (0x1u << 29) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P30 (0x1u << 30) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
#define PIO_FELLSR_P31 (0x1u << 31) /**< \brief (PIO_FELLSR) Falling Edge/Low Level Interrupt Selection. */
/* -------- PIO_REHLSR : (PIO Offset: 0x00D4) Rising Edge/ High Level Select Register -------- */
#define PIO_REHLSR_P0 (0x1u << 0) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P1 (0x1u << 1) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P2 (0x1u << 2) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P3 (0x1u << 3) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P4 (0x1u << 4) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P5 (0x1u << 5) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P6 (0x1u << 6) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P7 (0x1u << 7) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P8 (0x1u << 8) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P9 (0x1u << 9) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P10 (0x1u << 10) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P11 (0x1u << 11) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P12 (0x1u << 12) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P13 (0x1u << 13) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P14 (0x1u << 14) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P15 (0x1u << 15) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P16 (0x1u << 16) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P17 (0x1u << 17) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P18 (0x1u << 18) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P19 (0x1u << 19) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P20 (0x1u << 20) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P21 (0x1u << 21) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P22 (0x1u << 22) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P23 (0x1u << 23) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P24 (0x1u << 24) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P25 (0x1u << 25) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P26 (0x1u << 26) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P27 (0x1u << 27) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P28 (0x1u << 28) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P29 (0x1u << 29) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P30 (0x1u << 30) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
#define PIO_REHLSR_P31 (0x1u << 31) /**< \brief (PIO_REHLSR) Rising Edge /High Level Interrupt Selection. */
/* -------- PIO_FRLHSR : (PIO Offset: 0x00D8) Fall/Rise - Low/High Status Register -------- */
#define PIO_FRLHSR_P0 (0x1u << 0) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P1 (0x1u << 1) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P2 (0x1u << 2) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P3 (0x1u << 3) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P4 (0x1u << 4) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P5 (0x1u << 5) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P6 (0x1u << 6) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P7 (0x1u << 7) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P8 (0x1u << 8) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P9 (0x1u << 9) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P10 (0x1u << 10) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P11 (0x1u << 11) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P12 (0x1u << 12) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P13 (0x1u << 13) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P14 (0x1u << 14) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P15 (0x1u << 15) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P16 (0x1u << 16) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P17 (0x1u << 17) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P18 (0x1u << 18) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P19 (0x1u << 19) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P20 (0x1u << 20) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P21 (0x1u << 21) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P22 (0x1u << 22) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P23 (0x1u << 23) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P24 (0x1u << 24) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P25 (0x1u << 25) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P26 (0x1u << 26) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P27 (0x1u << 27) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P28 (0x1u << 28) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P29 (0x1u << 29) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P30 (0x1u << 30) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
#define PIO_FRLHSR_P31 (0x1u << 31) /**< \brief (PIO_FRLHSR) Edge /Level Interrupt Source Selection. */
/* -------- PIO_LOCKSR : (PIO Offset: 0x00E0) Lock Status -------- */
#define PIO_LOCKSR_P0 (0x1u << 0) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P1 (0x1u << 1) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P2 (0x1u << 2) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P3 (0x1u << 3) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P4 (0x1u << 4) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P5 (0x1u << 5) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P6 (0x1u << 6) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P7 (0x1u << 7) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P8 (0x1u << 8) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P9 (0x1u << 9) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P10 (0x1u << 10) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P11 (0x1u << 11) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P12 (0x1u << 12) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P13 (0x1u << 13) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P14 (0x1u << 14) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P15 (0x1u << 15) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P16 (0x1u << 16) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P17 (0x1u << 17) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P18 (0x1u << 18) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P19 (0x1u << 19) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P20 (0x1u << 20) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P21 (0x1u << 21) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P22 (0x1u << 22) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P23 (0x1u << 23) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P24 (0x1u << 24) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P25 (0x1u << 25) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P26 (0x1u << 26) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P27 (0x1u << 27) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P28 (0x1u << 28) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P29 (0x1u << 29) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P30 (0x1u << 30) /**< \brief (PIO_LOCKSR) Lock Status. */
#define PIO_LOCKSR_P31 (0x1u << 31) /**< \brief (PIO_LOCKSR) Lock Status. */
/* -------- PIO_WPMR : (PIO Offset: 0x00E4) Write Protect Mode Register -------- */
#define PIO_WPMR_WPEN (0x1u << 0) /**< \brief (PIO_WPMR) Write Protect Enable */
#define PIO_WPMR_WPKEY_Pos 8
#define PIO_WPMR_WPKEY_Msk (0xffffffu << PIO_WPMR_WPKEY_Pos) /**< \brief (PIO_WPMR) Write Protect KEY */
#define PIO_WPMR_WPKEY(value) ((PIO_WPMR_WPKEY_Msk & ((value) << PIO_WPMR_WPKEY_Pos)))
/* -------- PIO_WPSR : (PIO Offset: 0x00E8) Write Protect Status Register -------- */
#define PIO_WPSR_WPVS (0x1u << 0) /**< \brief (PIO_WPSR) Write Protect Violation Status */
#define PIO_WPSR_WPVSRC_Pos 8
#define PIO_WPSR_WPVSRC_Msk (0xffffu << PIO_WPSR_WPVSRC_Pos) /**< \brief (PIO_WPSR) Write Protect Violation Source */
/* -------- PIO_SCHMITT : (PIO Offset: 0x0100) Schmitt Trigger Register -------- */
#define PIO_SCHMITT_SCHMITT0 (0x1u << 0) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT1 (0x1u << 1) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT2 (0x1u << 2) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT3 (0x1u << 3) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT4 (0x1u << 4) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT5 (0x1u << 5) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT6 (0x1u << 6) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT7 (0x1u << 7) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT8 (0x1u << 8) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT9 (0x1u << 9) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT10 (0x1u << 10) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT11 (0x1u << 11) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT12 (0x1u << 12) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT13 (0x1u << 13) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT14 (0x1u << 14) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT15 (0x1u << 15) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT16 (0x1u << 16) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT17 (0x1u << 17) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT18 (0x1u << 18) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT19 (0x1u << 19) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT20 (0x1u << 20) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT21 (0x1u << 21) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT22 (0x1u << 22) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT23 (0x1u << 23) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT24 (0x1u << 24) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT25 (0x1u << 25) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT26 (0x1u << 26) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT27 (0x1u << 27) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT28 (0x1u << 28) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT29 (0x1u << 29) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT30 (0x1u << 30) /**< \brief (PIO_SCHMITT)  */
#define PIO_SCHMITT_SCHMITT31 (0x1u << 31) /**< \brief (PIO_SCHMITT)  */
/* -------- PIO_DRIVER1 : (PIO Offset: 0x0118) I/O Drive Register 1 -------- */
#define PIO_DRIVER1_LINE0_Pos 0
#define PIO_DRIVER1_LINE0_Msk (0x3u << PIO_DRIVER1_LINE0_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 0 */
#define   PIO_DRIVER1_LINE0_HI_DRIVE (0x0u << 0) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE0_ME_DRIVE (0x1u << 0) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE0_LO_DRIVE (0x2u << 0) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE1_Pos 2
#define PIO_DRIVER1_LINE1_Msk (0x3u << PIO_DRIVER1_LINE1_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 1 */
#define   PIO_DRIVER1_LINE1_HI_DRIVE (0x0u << 2) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE1_ME_DRIVE (0x1u << 2) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE1_LO_DRIVE (0x2u << 2) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE2_Pos 4
#define PIO_DRIVER1_LINE2_Msk (0x3u << PIO_DRIVER1_LINE2_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 2 */
#define   PIO_DRIVER1_LINE2_HI_DRIVE (0x0u << 4) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE2_ME_DRIVE (0x1u << 4) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE2_LO_DRIVE (0x2u << 4) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE3_Pos 6
#define PIO_DRIVER1_LINE3_Msk (0x3u << PIO_DRIVER1_LINE3_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 3 */
#define   PIO_DRIVER1_LINE3_HI_DRIVE (0x0u << 6) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE3_ME_DRIVE (0x1u << 6) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE3_LO_DRIVE (0x2u << 6) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE4_Pos 8
#define PIO_DRIVER1_LINE4_Msk (0x3u << PIO_DRIVER1_LINE4_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 4 */
#define   PIO_DRIVER1_LINE4_HI_DRIVE (0x0u << 8) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE4_ME_DRIVE (0x1u << 8) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE4_LO_DRIVE (0x2u << 8) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE5_Pos 10
#define PIO_DRIVER1_LINE5_Msk (0x3u << PIO_DRIVER1_LINE5_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 5 */
#define   PIO_DRIVER1_LINE5_HI_DRIVE (0x0u << 10) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE5_ME_DRIVE (0x1u << 10) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE5_LO_DRIVE (0x2u << 10) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE6_Pos 12
#define PIO_DRIVER1_LINE6_Msk (0x3u << PIO_DRIVER1_LINE6_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 6 */
#define   PIO_DRIVER1_LINE6_HI_DRIVE (0x0u << 12) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE6_ME_DRIVE (0x1u << 12) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE6_LO_DRIVE (0x2u << 12) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE7_Pos 14
#define PIO_DRIVER1_LINE7_Msk (0x3u << PIO_DRIVER1_LINE7_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 7 */
#define   PIO_DRIVER1_LINE7_HI_DRIVE (0x0u << 14) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE7_ME_DRIVE (0x1u << 14) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE7_LO_DRIVE (0x2u << 14) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE8_Pos 16
#define PIO_DRIVER1_LINE8_Msk (0x3u << PIO_DRIVER1_LINE8_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 8 */
#define   PIO_DRIVER1_LINE8_HI_DRIVE (0x0u << 16) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE8_ME_DRIVE (0x1u << 16) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE8_LO_DRIVE (0x2u << 16) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE9_Pos 18
#define PIO_DRIVER1_LINE9_Msk (0x3u << PIO_DRIVER1_LINE9_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 9 */
#define   PIO_DRIVER1_LINE9_HI_DRIVE (0x0u << 18) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE9_ME_DRIVE (0x1u << 18) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE9_LO_DRIVE (0x2u << 18) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE10_Pos 20
#define PIO_DRIVER1_LINE10_Msk (0x3u << PIO_DRIVER1_LINE10_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 10 */
#define   PIO_DRIVER1_LINE10_HI_DRIVE (0x0u << 20) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE10_ME_DRIVE (0x1u << 20) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE10_LO_DRIVE (0x2u << 20) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE11_Pos 22
#define PIO_DRIVER1_LINE11_Msk (0x3u << PIO_DRIVER1_LINE11_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 11 */
#define   PIO_DRIVER1_LINE11_HI_DRIVE (0x0u << 22) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE11_ME_DRIVE (0x1u << 22) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE11_LO_DRIVE (0x2u << 22) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE12_Pos 24
#define PIO_DRIVER1_LINE12_Msk (0x3u << PIO_DRIVER1_LINE12_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 12 */
#define   PIO_DRIVER1_LINE12_HI_DRIVE (0x0u << 24) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE12_ME_DRIVE (0x1u << 24) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE12_LO_DRIVE (0x2u << 24) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE13_Pos 26
#define PIO_DRIVER1_LINE13_Msk (0x3u << PIO_DRIVER1_LINE13_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 13 */
#define   PIO_DRIVER1_LINE13_HI_DRIVE (0x0u << 26) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE13_ME_DRIVE (0x1u << 26) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE13_LO_DRIVE (0x2u << 26) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE14_Pos 28
#define PIO_DRIVER1_LINE14_Msk (0x3u << PIO_DRIVER1_LINE14_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 14 */
#define   PIO_DRIVER1_LINE14_HI_DRIVE (0x0u << 28) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE14_ME_DRIVE (0x1u << 28) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE14_LO_DRIVE (0x2u << 28) /**< \brief (PIO_DRIVER1) Low drive */
#define PIO_DRIVER1_LINE15_Pos 30
#define PIO_DRIVER1_LINE15_Msk (0x3u << PIO_DRIVER1_LINE15_Pos) /**< \brief (PIO_DRIVER1) Drive of PIO line 15 */
#define   PIO_DRIVER1_LINE15_HI_DRIVE (0x0u << 30) /**< \brief (PIO_DRIVER1) High drive */
#define   PIO_DRIVER1_LINE15_ME_DRIVE (0x1u << 30) /**< \brief (PIO_DRIVER1) Medium drive */
#define   PIO_DRIVER1_LINE15_LO_DRIVE (0x2u << 30) /**< \brief (PIO_DRIVER1) Low drive */
/* -------- PIO_DRIVER2 : (PIO Offset: 0x011C) I/O Drive Register 2 -------- */
#define PIO_DRIVER2_LINE16_Pos 0
#define PIO_DRIVER2_LINE16_Msk (0x3u << PIO_DRIVER2_LINE16_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 16 */
#define   PIO_DRIVER2_LINE16_HI_DRIVE (0x0u << 0) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE16_ME_DRIVE (0x1u << 0) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE16_LO_DRIVE (0x2u << 0) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE17_Pos 2
#define PIO_DRIVER2_LINE17_Msk (0x3u << PIO_DRIVER2_LINE17_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 17 */
#define   PIO_DRIVER2_LINE17_HI_DRIVE (0x0u << 2) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE17_ME_DRIVE (0x1u << 2) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE17_LO_DRIVE (0x2u << 2) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE18_Pos 4
#define PIO_DRIVER2_LINE18_Msk (0x3u << PIO_DRIVER2_LINE18_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 18 */
#define   PIO_DRIVER2_LINE18_HI_DRIVE (0x0u << 4) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE18_ME_DRIVE (0x1u << 4) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE18_LO_DRIVE (0x2u << 4) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE19_Pos 6
#define PIO_DRIVER2_LINE19_Msk (0x3u << PIO_DRIVER2_LINE19_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 19 */
#define   PIO_DRIVER2_LINE19_HI_DRIVE (0x0u << 6) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE19_ME_DRIVE (0x1u << 6) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE19_LO_DRIVE (0x2u << 6) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE20_Pos 8
#define PIO_DRIVER2_LINE20_Msk (0x3u << PIO_DRIVER2_LINE20_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 20 */
#define   PIO_DRIVER2_LINE20_HI_DRIVE (0x0u << 8) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE20_ME_DRIVE (0x1u << 8) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE20_LO_DRIVE (0x2u << 8) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE21_Pos 10
#define PIO_DRIVER2_LINE21_Msk (0x3u << PIO_DRIVER2_LINE21_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 21 */
#define   PIO_DRIVER2_LINE21_HI_DRIVE (0x0u << 10) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE21_ME_DRIVE (0x1u << 10) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE21_LO_DRIVE (0x2u << 10) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE22_Pos 12
#define PIO_DRIVER2_LINE22_Msk (0x3u << PIO_DRIVER2_LINE22_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 22 */
#define   PIO_DRIVER2_LINE22_HI_DRIVE (0x0u << 12) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE22_ME_DRIVE (0x1u << 12) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE22_LO_DRIVE (0x2u << 12) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE23_Pos 14
#define PIO_DRIVER2_LINE23_Msk (0x3u << PIO_DRIVER2_LINE23_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 23 */
#define   PIO_DRIVER2_LINE23_HI_DRIVE (0x0u << 14) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE23_ME_DRIVE (0x1u << 14) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE23_LO_DRIVE (0x2u << 14) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE24_Pos 16
#define PIO_DRIVER2_LINE24_Msk (0x3u << PIO_DRIVER2_LINE24_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 24 */
#define   PIO_DRIVER2_LINE24_HI_DRIVE (0x0u << 16) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE24_ME_DRIVE (0x1u << 16) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE24_LO_DRIVE (0x2u << 16) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE25_Pos 18
#define PIO_DRIVER2_LINE25_Msk (0x3u << PIO_DRIVER2_LINE25_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 25 */
#define   PIO_DRIVER2_LINE25_HI_DRIVE (0x0u << 18) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE25_ME_DRIVE (0x1u << 18) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE25_LO_DRIVE (0x2u << 18) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE26_Pos 20
#define PIO_DRIVER2_LINE26_Msk (0x3u << PIO_DRIVER2_LINE26_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 26 */
#define   PIO_DRIVER2_LINE26_HI_DRIVE (0x0u << 20) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE26_ME_DRIVE (0x1u << 20) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE26_LO_DRIVE (0x2u << 20) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE27_Pos 22
#define PIO_DRIVER2_LINE27_Msk (0x3u << PIO_DRIVER2_LINE27_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 27 */
#define   PIO_DRIVER2_LINE27_HI_DRIVE (0x0u << 22) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE27_ME_DRIVE (0x1u << 22) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE27_LO_DRIVE (0x2u << 22) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE28_Pos 24
#define PIO_DRIVER2_LINE28_Msk (0x3u << PIO_DRIVER2_LINE28_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 28 */
#define   PIO_DRIVER2_LINE28_HI_DRIVE (0x0u << 24) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE28_ME_DRIVE (0x1u << 24) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE28_LO_DRIVE (0x2u << 24) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE29_Pos 26
#define PIO_DRIVER2_LINE29_Msk (0x3u << PIO_DRIVER2_LINE29_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 29 */
#define   PIO_DRIVER2_LINE29_HI_DRIVE (0x0u << 26) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE29_ME_DRIVE (0x1u << 26) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE29_LO_DRIVE (0x2u << 26) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE30_Pos 28
#define PIO_DRIVER2_LINE30_Msk (0x3u << PIO_DRIVER2_LINE30_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 30 */
#define   PIO_DRIVER2_LINE30_HI_DRIVE (0x0u << 28) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE30_ME_DRIVE (0x1u << 28) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE30_LO_DRIVE (0x2u << 28) /**< \brief (PIO_DRIVER2) Low drive */
#define PIO_DRIVER2_LINE31_Pos 30
#define PIO_DRIVER2_LINE31_Msk (0x3u << PIO_DRIVER2_LINE31_Pos) /**< \brief (PIO_DRIVER2) Drive of PIO line 31 */
#define   PIO_DRIVER2_LINE31_HI_DRIVE (0x0u << 30) /**< \brief (PIO_DRIVER2) High drive */
#define   PIO_DRIVER2_LINE31_ME_DRIVE (0x1u << 30) /**< \brief (PIO_DRIVER2) Medium drive */
#define   PIO_DRIVER2_LINE31_LO_DRIVE (0x2u << 30) /**< \brief (PIO_DRIVER2) Low drive */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Periodic Interval Timer */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_PIT Periodic Interval Timer */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Pit hardware registers */
typedef struct {
  RwReg PIT_MR;   /**< \brief (Pit Offset: 0x00) Mode Register */
  RoReg PIT_SR;   /**< \brief (Pit Offset: 0x04) Status Register */
  RoReg PIT_PIVR; /**< \brief (Pit Offset: 0x08) Periodic Interval Value Register */
  RoReg PIT_PIIR; /**< \brief (Pit Offset: 0x0C) Periodic Interval Image Register */
} Pit;
#endif /* __ASSEMBLY__ */
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
/** \addtogroup AT91SAMA5_PMC Power Management Controller */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Pmc hardware registers */
typedef struct {
  WoReg PMC_SCER;      /**< \brief (Pmc Offset: 0x0000) System Clock Enable Register */
  WoReg PMC_SCDR;      /**< \brief (Pmc Offset: 0x0004) System Clock Disable Register */
  RoReg PMC_SCSR;      /**< \brief (Pmc Offset: 0x0008) System Clock Status Register */
  RoReg Reserved1[1];
  WoReg PMC_PCER0;     /**< \brief (Pmc Offset: 0x0010) Peripheral Clock Enable Register 0 */
  WoReg PMC_PCDR0;     /**< \brief (Pmc Offset: 0x0014) Peripheral Clock Disable Register 0 */
  RoReg PMC_PCSR0;     /**< \brief (Pmc Offset: 0x0018) Peripheral Clock Status Register 0 */
  RwReg CKGR_UCKR;     /**< \brief (Pmc Offset: 0x001C) UTMI Clock Register */
  RwReg CKGR_MOR;      /**< \brief (Pmc Offset: 0x0020) Main Oscillator Register */
  RoReg CKGR_MCFR;     /**< \brief (Pmc Offset: 0x0024) Main Clock Frequency Register */
  RwReg CKGR_PLLAR;    /**< \brief (Pmc Offset: 0x0028) PLLA Register */
  RoReg Reserved2[1];
  RwReg PMC_MCKR;      /**< \brief (Pmc Offset: 0x0030) Master Clock Register */
  RoReg Reserved3[1];
  RwReg PMC_USB;       /**< \brief (Pmc Offset: 0x0038) USB Clock Register */
  RwReg PMC_SMD;       /**< \brief (Pmc Offset: 0x003C) Soft Modem Clock Register */
  RwReg PMC_PCK[3];    /**< \brief (Pmc Offset: 0x0040) Programmable Clock 0 Register */
  RoReg Reserved4[5];
  WoReg PMC_IER;       /**< \brief (Pmc Offset: 0x0060) Interrupt Enable Register */
  WoReg PMC_IDR;       /**< \brief (Pmc Offset: 0x0064) Interrupt Disable Register */
  RoReg PMC_SR;        /**< \brief (Pmc Offset: 0x0068) Status Register */
  RoReg PMC_IMR;       /**< \brief (Pmc Offset: 0x006C) Interrupt Mask Register */
  RoReg Reserved5[4];
  WoReg PMC_PLLICPR;   /**< \brief (Pmc Offset: 0x0080) PLL Charge Pump Current Register */
  RoReg Reserved6[24];
  RwReg PMC_WPMR;      /**< \brief (Pmc Offset: 0x00E4) Write Protect Mode Register */
  RoReg PMC_WPSR;      /**< \brief (Pmc Offset: 0x00E8) Write Protect Status Register */
  RoReg Reserved7[5];
  WoReg PMC_PCER1;     /**< \brief (Pmc Offset: 0x00100) Peripheral Clock Enable Register 1 */
  WoReg PMC_PCDR1;     /**< \brief (Pmc Offset: 0x00104) Peripheral Clock Disable Register 1 */
  RoReg PMC_PCSR1;     /**< \brief (Pmc Offset: 0x00108) Peripheral Clock Status Register 1 */
  RwReg PMC_PCR;       /**< \brief (Pmc Offset: 0x010C) Peripheral Control Register */
} Pmc;
#endif /* __ASSEMBLY__ */
/* -------- PMC_SCER : (PMC Offset: 0x0000) System Clock Enable Register -------- */
#define PMC_SCER_DDRCK (0x1u << 2) /**< \brief (PMC_SCER) DDR Clock Enable */
#define PMC_SCER_SMDCK (0x1u << 4) /**< \brief (PMC_SCER) SMD Clock Enable */
#define PMC_SCER_UHP (0x1u << 6) /**< \brief (PMC_SCER) USB Host OHCI Clocks Enable */
#define PMC_SCER_UDP (0x1u << 7) /**< \brief (PMC_SCER) USB Device Clock Enable */
#define PMC_SCER_PCK0 (0x1u << 8) /**< \brief (PMC_SCER) Programmable Clock 0 Output Enable */
#define PMC_SCER_PCK1 (0x1u << 9) /**< \brief (PMC_SCER) Programmable Clock 1 Output Enable */
#define PMC_SCER_PCK2 (0x1u << 10) /**< \brief (PMC_SCER) Programmable Clock 2 Output Enable */
/* -------- PMC_SCDR : (PMC Offset: 0x0004) System Clock Disable Register -------- */
#define PMC_SCDR_PCK (0x1u << 0) /**< \brief (PMC_SCDR) Processor Clock Disable */
#define PMC_SCDR_DDRCK (0x1u << 2) /**< \brief (PMC_SCDR) DDR Clock Disable */
#define PMC_SCDR_SMDCK (0x1u << 4) /**< \brief (PMC_SCDR) SMD Clock Disable */
#define PMC_SCDR_UHP (0x1u << 6) /**< \brief (PMC_SCDR) USB Host OHCI Clock Disable */
#define PMC_SCDR_UDP (0x1u << 7) /**< \brief (PMC_SCDR) USB Device Clock Enable */
#define PMC_SCDR_PCK0 (0x1u << 8) /**< \brief (PMC_SCDR) Programmable Clock 0 Output Disable */
#define PMC_SCDR_PCK1 (0x1u << 9) /**< \brief (PMC_SCDR) Programmable Clock 1 Output Disable */
#define PMC_SCDR_PCK2 (0x1u << 10) /**< \brief (PMC_SCDR) Programmable Clock 2 Output Disable */
/* -------- PMC_SCSR : (PMC Offset: 0x0008) System Clock Status Register -------- */
#define PMC_SCSR_PCK (0x1u << 0) /**< \brief (PMC_SCSR) Processor Clock Status */
#define PMC_SCSR_DDRCK (0x1u << 2) /**< \brief (PMC_SCSR) DDR Clock Status */
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
#define CKGR_MOR_MOSCRCEN (0x1u << 3) /**< \brief (CKGR_MOR) Main On-Chip RC Oscillator Enable */
#define CKGR_MOR_MOSCXTST_Pos 8
#define CKGR_MOR_MOSCXTST_Msk (0xffu << CKGR_MOR_MOSCXTST_Pos) /**< \brief (CKGR_MOR) Main Crystal Oscillator Start-up Time */
#define CKGR_MOR_MOSCXTST(value) ((CKGR_MOR_MOSCXTST_Msk & ((value) << CKGR_MOR_MOSCXTST_Pos)))
#define CKGR_MOR_KEY_Pos 16
#define CKGR_MOR_KEY_Msk (0xffu << CKGR_MOR_KEY_Pos) /**< \brief (CKGR_MOR) Password */
#define CKGR_MOR_KEY(value) ((CKGR_MOR_KEY_Msk & ((value) << CKGR_MOR_KEY_Pos)))
#define CKGR_MOR_MOSCSEL (0x1u << 24) /**< \brief (CKGR_MOR) Main Oscillator Selection */
#define CKGR_MOR_CFDEN (0x1u << 25) /**< \brief (CKGR_MOR) Clock Failure Detector Enable */
/* -------- CKGR_MCFR : (PMC Offset: 0x0024) Main Clock Frequency Register -------- */
#define CKGR_MCFR_MAINF_Pos 0
#define CKGR_MCFR_MAINF_Msk (0xffffu << CKGR_MCFR_MAINF_Pos) /**< \brief (CKGR_MCFR) Main Clock Frequency */
#define CKGR_MCFR_MAINFRDY (0x1u << 16) /**< \brief (CKGR_MCFR) Main Clock Ready */
/* -------- CKGR_PLLAR : (PMC Offset: 0x0028) PLLA Register -------- */
#define CKGR_PLLAR_DIVA_Pos 0
#define CKGR_PLLAR_DIVA_Msk (0xffu << CKGR_PLLAR_DIVA_Pos) /**< \brief (CKGR_PLLAR) Divider A */
#define CKGR_PLLAR_DIVA(value) ((CKGR_PLLAR_DIVA_Msk & ((value) << CKGR_PLLAR_DIVA_Pos)))
#define CKGR_PLLAR_PLLACOUNT_Pos 8
#define CKGR_PLLAR_PLLACOUNT_Msk (0x3fu << CKGR_PLLAR_PLLACOUNT_Pos) /**< \brief (CKGR_PLLAR) PLLA Counter */
#define CKGR_PLLAR_PLLACOUNT(value) ((CKGR_PLLAR_PLLACOUNT_Msk & ((value) << CKGR_PLLAR_PLLACOUNT_Pos)))
#define CKGR_PLLAR_OUTA_Pos 14
#define CKGR_PLLAR_OUTA_Msk (0xfu << CKGR_PLLAR_OUTA_Pos) /**< \brief (CKGR_PLLAR) PLLA Clock Frequency Range */
#define CKGR_PLLAR_OUTA(value) ((CKGR_PLLAR_OUTA_Msk & ((value) << CKGR_PLLAR_OUTA_Pos)))
#define CKGR_PLLAR_MULA_Pos 18
#define CKGR_PLLAR_MULA_Msk (0x7ffu << CKGR_PLLAR_MULA_Pos) /**< \brief (CKGR_PLLAR) PLLA Multiplier */
#define CKGR_PLLAR_MULA(value) ((CKGR_PLLAR_MULA_Msk & ((value) << CKGR_PLLAR_MULA_Pos)))
#define CKGR_PLLAR_STUCKTO1 (0x1u << 29) /**< \brief (CKGR_PLLAR)  */
/* -------- PMC_MCKR : (PMC Offset: 0x0030) Master Clock Register -------- */
#define PMC_MCKR_CSS_Pos 0
#define PMC_MCKR_CSS_Msk (0x3u << PMC_MCKR_CSS_Pos) /**< \brief (PMC_MCKR) Master/Processor Clock Source Selection */
#define   PMC_MCKR_CSS_SLOW_CLK (0x0u << 0) /**< \brief (PMC_MCKR) Slow Clock is selected */
#define   PMC_MCKR_CSS_MAIN_CLK (0x1u << 0) /**< \brief (PMC_MCKR) Main Clock is selected */
#define   PMC_MCKR_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_MCKR) PLLACK/PLLADIV2 is selected */
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
#define PMC_MCKR_PLLADIV2 (0x1u << 12) /**< \brief (PMC_MCKR) PLLA divisor by 2 */
#define   PMC_MCKR_PLLADIV2_NOT_DIV2 (0x0u << 12) /**< \brief (PMC_MCKR) PLLA clock frequency is divided by 1. */
#define   PMC_MCKR_PLLADIV2_DIV2 (0x1u << 12) /**< \brief (PMC_MCKR) PLLA clock frequency is divided by 2. */
/* -------- PMC_USB : (PMC Offset: 0x0038) USB Clock Register -------- */
#define PMC_USB_USBS (0x1u << 0) /**< \brief (PMC_USB) USB OHCI Input Clock Selection */
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
#define   PMC_PCK_CSS_PLLA_CLK (0x2u << 0) /**< \brief (PMC_PCK[3]) PLLACK/PLLADIV2 is selected */
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
#define PMC_IMR_MOSCSELS (0x1u << 16) /**< \brief (PMC_IMR) Main Oscillator Selection Status Interrupt Mask */
#define PMC_IMR_MOSCRCS (0x1u << 17) /**< \brief (PMC_IMR) Main On-Chip RC Status Interrupt Mask */
#define PMC_IMR_CFDEV (0x1u << 18) /**< \brief (PMC_IMR) Clock Failure Detector Event Interrupt Mask */
/* -------- PMC_PLLICPR : (PMC Offset: 0x0080) PLL Charge Pump Current Register -------- */
#define PMC_PLLICPR_ICPLLA (0x1u << 0) /**< \brief (PMC_PLLICPR) Charge Pump Current */
/* -------- PMC_WPMR : (PMC Offset: 0x00E4) Write Protect Mode Register -------- */
#define PMC_WPMR_WPEN (0x1u << 0) /**< \brief (PMC_WPMR) Write Protect Enable */
#define PMC_WPMR_WPKEY_Pos 8
#define PMC_WPMR_WPKEY_Msk (0xffffffu << PMC_WPMR_WPKEY_Pos) /**< \brief (PMC_WPMR) Write Protect KEY */
#define PMC_WPMR_WPKEY(value) ((PMC_WPMR_WPKEY_Msk & ((value) << PMC_WPMR_WPKEY_Pos)))
/* -------- PMC_WPSR : (PMC Offset: 0x00E8) Write Protect Status Register -------- */
#define PMC_WPSR_WPVS (0x1u << 0) /**< \brief (PMC_WPSR) Write Protect Violation Status */
#define PMC_WPSR_WPVSRC_Pos 8
#define PMC_WPSR_WPVSRC_Msk (0xffffu << PMC_WPSR_WPVSRC_Pos) /**< \brief (PMC_WPSR) Write Protect Violation Source */
/* -------- PMC_PCER1 : (PMC Offset: 0x00100) Peripheral Clock Enable Register 1 -------- */
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
#define PMC_PCER1_PID53_Pos 20
#define PMC_PCER1_PID53_Msk (0x3u << PMC_PCER1_PID53_Pos) /**< \brief (PMC_PCER1) Peripheral Clock 53 Enable */
#define PMC_PCER1_PID53(value) ((PMC_PCER1_PID53_Msk & ((value) << PMC_PCER1_PID53_Pos)))
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
/* -------- PMC_PCDR1 : (PMC Offset: 0x00104) Peripheral Clock Disable Register 1 -------- */
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
#define PMC_PCDR1_PID53_Pos 20
#define PMC_PCDR1_PID53_Msk (0x3u << PMC_PCDR1_PID53_Pos) /**< \brief (PMC_PCDR1) Peripheral Clock 53 Disable */
#define PMC_PCDR1_PID53(value) ((PMC_PCDR1_PID53_Msk & ((value) << PMC_PCDR1_PID53_Pos)))
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
/* -------- PMC_PCSR1 : (PMC Offset: 0x00108) Peripheral Clock Status Register 1 -------- */
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
#define PMC_PCSR1_PID53_Pos 20
#define PMC_PCSR1_PID53_Msk (0x3u << PMC_PCSR1_PID53_Pos) /**< \brief (PMC_PCSR1) Peripheral Clock 53 Status */
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
#define PMC_PCR_DIV_Msk (0x3u << PMC_PCR_DIV_Pos) /**< \brief (PMC_PCR) Divisor Value */
#define   PMC_PCR_DIV_PERIPH_DIV_MCK (0x0u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK */
#define   PMC_PCR_DIV_PERIPH_DIV2_MCK (0x1u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK/2 */
#define   PMC_PCR_DIV_PERIPH_DIV4_MCK (0x2u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK/4 */
#define   PMC_PCR_DIV_PERIPH_DIV8_MCK (0x3u << 16) /**< \brief (PMC_PCR) Peripheral clock is MCK/8 */
#define PMC_PCR_EN (0x1u << 28) /**< \brief (PMC_PCR) Enable */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Reset Controller */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_RSTC Reset Controller */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Rstc hardware registers */
typedef struct {
  WoReg RSTC_CR; /**< \brief (Rstc Offset: 0x00) Control Register */
  RoReg RSTC_SR; /**< \brief (Rstc Offset: 0x04) Status Register */
  RwReg RSTC_MR; /**< \brief (Rstc Offset: 0x08) Mode Register */
} Rstc;
#endif /* __ASSEMBLY__ */
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
#define RSTC_MR_ERSTL_Pos 8
#define RSTC_MR_ERSTL_Msk (0xfu << RSTC_MR_ERSTL_Pos) /**< \brief (RSTC_MR) External Reset Length */
#define RSTC_MR_ERSTL(value) ((RSTC_MR_ERSTL_Msk & ((value) << RSTC_MR_ERSTL_Pos)))
#define RSTC_MR_KEY_Pos 24
#define RSTC_MR_KEY_Msk (0xffu << RSTC_MR_KEY_Pos) /**< \brief (RSTC_MR) Password */
#define RSTC_MR_KEY(value) ((RSTC_MR_KEY_Msk & ((value) << RSTC_MR_KEY_Pos)))

/*@}*/


#ifndef __ASSEMBLY__
/** \brief Sckc hardware registers */
typedef struct {
  RwReg SCKC_CR; /**< \brief (Sckc Offset: 0x0) Slow Clock Configuration Register */
} Sckc;
#endif /* __ASSEMBLY__ */
/* -------- SCKC_CR : (SCKC Offset: 0x0) Slow Clock Configuration Register -------- */
#define SCKC_CR_RCEN (0x1u << 0) /**< \brief (SCKC_CR) Internal 32 kHz RC Oscillator */
#define SCKC_CR_OSC32EN (0x1u << 1) /**< \brief (SCKC_CR) 32,768 Hz Oscillator */
#define SCKC_CR_OSC32BYP (0x1u << 2) /**< \brief (SCKC_CR) 32,768Hz Oscillator Bypass */
#define SCKC_CR_OSCSEL (0x1u << 3) /**< \brief (SCKC_CR) Slow Clock Selector */
#define   SCKC_CR_OSCSEL_RC (0x0u << 3) /**< \brief (SCKC_CR) Slow clock is internal 32 kHz RC oscillator. */
#define   SCKC_CR_OSCSEL_XTAL (0x1u << 3) /**< \brief (SCKC_CR) Slow clock is 32,768 Hz oscillator. */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Special Function Registers */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_SFR Special Function Registers */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Sfr hardware registers */
typedef struct {
  RoReg Reserved1[4];
  RwReg SFR_OHCIICR;    /**< \brief (Sfr Offset: 0x10) OHCI Interrupt Configuration Register */
  RoReg SFR_OHCIISR;    /**< \brief (Sfr Offset: 0x14) OHCI Interrupt Status Register */
  RoReg Reserved2[2];
  RwReg SFR_AHB;        /**< \brief (Sfr Offset: 0x20) AHB Configuration Register */
  RwReg SFR_BRIDGE;     /**< \brief (Sfr Offset: 0x24) Bridge Configuration Register */
  RwReg SFR_SECURE;     /**< \brief (Sfr Offset: 0x28) Security Configuration Register */
  RoReg Reserved3[1];
  RwReg SFR_UTMICKTRIM; /**< \brief (Sfr Offset: 0x30) UTMI Clock Trimming Register */
  RwReg SFR_UTMIHSTRIM; /**< \brief (Sfr Offset: 0x34) UTMI High Speed Trimming Register */
  RwReg SFR_UTMIFSTRIM; /**< \brief (Sfr Offset: 0x38) UTMI Full Speed Trimming Register */
  RwReg SFR_UTMISWAP;   /**< \brief (Sfr Offset: 0x3C) UTMI DP/DM Pin Swapping Register */
  RwReg SFR_EBICFG;     /**< \brief (Sfr Offset: 0x40) EBI Configuration Register */
} Sfr;
#endif /* __ASSEMBLY__ */
/* -------- SFR_OHCIICR : (SFR Offset: 0x10) OHCI Interrupt Configuration Register -------- */
#define SFR_OHCIICR_RES0 (0x1u << 0) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_RES1 (0x1u << 1) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_RES2 (0x1u << 2) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_ARIE (0x1u << 4) /**< \brief (SFR_OHCIICR) OHCI Asynchronous Resume Interrupt Enable */
#define SFR_OHCIICR_APPSTART (0x1u << 5) /**< \brief (SFR_OHCIICR) Reserved */
#define SFR_OHCIICR_UDPPUDIS (0x1u << 23) /**< \brief (SFR_OHCIICR) OHCI USB DEVICE PULL-UP DISABLE */
/* -------- SFR_OHCIISR : (SFR Offset: 0x14) OHCI Interrupt Status Register -------- */
#define SFR_OHCIISR_RIS0 (0x1u << 0) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 0 */
#define SFR_OHCIISR_RIS1 (0x1u << 1) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 1 */
#define SFR_OHCIISR_RIS2 (0x1u << 2) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 2 */
/* -------- SFR_AHB : (SFR Offset: 0x20) AHB Configuration Register -------- */
#define SFR_AHB_PFETCH10 (0x1u << 10) /**< \brief (SFR_AHB) AHB MASTERx 10 Converter Prefetch */
#define   SFR_AHB_PFETCH10_INCR4 (0x0u << 10) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 4 beats. */
#define   SFR_AHB_PFETCH10_INCR8 (0x1u << 10) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 8 beats. */
#define SFR_AHB_PFETCH11 (0x1u << 11) /**< \brief (SFR_AHB) AHB MASTERx 11 Converter Prefetch */
#define   SFR_AHB_PFETCH11_INCR4 (0x0u << 11) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 4 beats. */
#define   SFR_AHB_PFETCH11_INCR8 (0x1u << 11) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 8 beats. */
#define SFR_AHB_PFETCH12 (0x1u << 12) /**< \brief (SFR_AHB) AHB MASTERx 12 Converter Prefetch */
#define   SFR_AHB_PFETCH12_INCR4 (0x0u << 12) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 4 beats. */
#define   SFR_AHB_PFETCH12_INCR8 (0x1u << 12) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 8 beats. */
#define SFR_AHB_PFETCH13 (0x1u << 13) /**< \brief (SFR_AHB) AHB MASTERx 13 Converter Prefetch */
#define   SFR_AHB_PFETCH13_INCR4 (0x0u << 13) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 4 beats. */
#define   SFR_AHB_PFETCH13_INCR8 (0x1u << 13) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 8 beats. */
#define SFR_AHB_PFETCH14 (0x1u << 14) /**< \brief (SFR_AHB) AHB MASTERx 14 Converter Prefetch */
#define   SFR_AHB_PFETCH14_INCR4 (0x0u << 14) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 4 beats. */
#define   SFR_AHB_PFETCH14_INCR8 (0x1u << 14) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 8 beats. */
#define SFR_AHB_DLBOPT10 (0x1u << 26) /**< \brief (SFR_AHB) AHB MASTERx 10 Converter Define Length Burst Optimization */
#define SFR_AHB_DLBOPT11 (0x1u << 27) /**< \brief (SFR_AHB) AHB MASTERx 11 Converter Define Length Burst Optimization */
#define SFR_AHB_DLBOPT12 (0x1u << 28) /**< \brief (SFR_AHB) AHB MASTERx 12 Converter Define Length Burst Optimization */
#define SFR_AHB_DLBOPT13 (0x1u << 29) /**< \brief (SFR_AHB) AHB MASTERx 13 Converter Define Length Burst Optimization */
#define SFR_AHB_DLBOPT14 (0x1u << 30) /**< \brief (SFR_AHB) AHB MASTERx 14 Converter Define Length Burst Optimization */
/* -------- SFR_BRIDGE : (SFR Offset: 0x24) Bridge Configuration Register -------- */
#define SFR_BRIDGE_APBTURBO (0x1u << 0) /**< \brief (SFR_BRIDGE) AHB to APB Bridge mode */
#define SFR_BRIDGE_AXI2AHBSEL (0x1u << 8) /**< \brief (SFR_BRIDGE) AXI to AHB bridge for DDR controller selection */
#define   SFR_BRIDGE_AXI2AHBSEL_SINGLE (0x0u << 8) /**< \brief (SFR_BRIDGE) use single port bridge. */
#define   SFR_BRIDGE_AXI2AHBSEL_DUAL (0x1u << 8) /**< \brief (SFR_BRIDGE) use dual port bridge. */
/* -------- SFR_SECURE : (SFR Offset: 0x28) Security Configuration Register -------- */
#define SFR_SECURE_ROM (0x1u << 0) /**< \brief (SFR_SECURE) Disable Access to ROM Code */
#define SFR_SECURE_FUSE (0x1u << 8) /**< \brief (SFR_SECURE) Disable Access to Fuse Controller */
/* -------- SFR_UTMICKTRIM : (SFR Offset: 0x30) UTMI Clock Trimming Register -------- */
#define SFR_UTMICKTRIM_FREQ_Pos 0
#define SFR_UTMICKTRIM_FREQ_Msk (0x3u << SFR_UTMICKTRIM_FREQ_Pos) /**< \brief (SFR_UTMICKTRIM) UTMI Reference Clock Frequency */
#define   SFR_UTMICKTRIM_FREQ_12 (0x0u << 0) /**< \brief (SFR_UTMICKTRIM) 12 MHz reference clock */
#define   SFR_UTMICKTRIM_FREQ_16 (0x1u << 0) /**< \brief (SFR_UTMICKTRIM) 16 MHz reference clock */
#define   SFR_UTMICKTRIM_FREQ_24 (0x2u << 0) /**< \brief (SFR_UTMICKTRIM) 24 MHz reference clock */
#define   SFR_UTMICKTRIM_FREQ_48 (0x3u << 0) /**< \brief (SFR_UTMICKTRIM) 48 MHz reference clock */
#define SFR_UTMICKTRIM_VBG_Pos 16
#define SFR_UTMICKTRIM_VBG_Msk (0xfu << SFR_UTMICKTRIM_VBG_Pos) /**< \brief (SFR_UTMICKTRIM) UTMI Band Gap Voltage Trimming */
#define SFR_UTMICKTRIM_VBG(value) ((SFR_UTMICKTRIM_VBG_Msk & ((value) << SFR_UTMICKTRIM_VBG_Pos)))
/* -------- SFR_UTMIHSTRIM : (SFR Offset: 0x34) UTMI High Speed Trimming Register -------- */
#define SFR_UTMIHSTRIM_SQUELCH_Pos 0
#define SFR_UTMIHSTRIM_SQUELCH_Msk (0x7u << SFR_UTMIHSTRIM_SQUELCH_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS SQUELCH Voltage Trimming */
#define SFR_UTMIHSTRIM_SQUELCH(value) ((SFR_UTMIHSTRIM_SQUELCH_Msk & ((value) << SFR_UTMIHSTRIM_SQUELCH_Pos)))
#define SFR_UTMIHSTRIM_DISC_Pos 4
#define SFR_UTMIHSTRIM_DISC_Msk (0x7u << SFR_UTMIHSTRIM_DISC_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI Disconnect Voltage Trimming */
#define SFR_UTMIHSTRIM_DISC(value) ((SFR_UTMIHSTRIM_DISC_Msk & ((value) << SFR_UTMIHSTRIM_DISC_Pos)))
#define SFR_UTMIHSTRIM_SLOPE0_Pos 8
#define SFR_UTMIHSTRIM_SLOPE0_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE0_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE0(value) ((SFR_UTMIHSTRIM_SLOPE0_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE0_Pos)))
#define SFR_UTMIHSTRIM_SLOPE1_Pos 12
#define SFR_UTMIHSTRIM_SLOPE1_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE1_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE1(value) ((SFR_UTMIHSTRIM_SLOPE1_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE1_Pos)))
#define SFR_UTMIHSTRIM_SLOPE2_Pos 16
#define SFR_UTMIHSTRIM_SLOPE2_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE2_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE2(value) ((SFR_UTMIHSTRIM_SLOPE2_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE2_Pos)))
/* -------- SFR_UTMIFSTRIM : (SFR Offset: 0x38) UTMI Full Speed Trimming Register -------- */
#define SFR_UTMIFSTRIM_RISE_Pos 0
#define SFR_UTMIFSTRIM_RISE_Msk (0x7u << SFR_UTMIFSTRIM_RISE_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver output rising slope trimming */
#define SFR_UTMIFSTRIM_RISE(value) ((SFR_UTMIFSTRIM_RISE_Msk & ((value) << SFR_UTMIFSTRIM_RISE_Pos)))
#define SFR_UTMIFSTRIM_FALL_Pos 4
#define SFR_UTMIFSTRIM_FALL_Msk (0x7u << SFR_UTMIFSTRIM_FALL_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver output falling slope trimming */
#define SFR_UTMIFSTRIM_FALL(value) ((SFR_UTMIFSTRIM_FALL_Msk & ((value) << SFR_UTMIFSTRIM_FALL_Pos)))
#define SFR_UTMIFSTRIM_XCVR_Pos 8
#define SFR_UTMIFSTRIM_XCVR_Msk (0x3u << SFR_UTMIFSTRIM_XCVR_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver crossover voltage trimming */
#define SFR_UTMIFSTRIM_XCVR(value) ((SFR_UTMIFSTRIM_XCVR_Msk & ((value) << SFR_UTMIFSTRIM_XCVR_Pos)))
#define SFR_UTMIFSTRIM_ZN_Pos 16
#define SFR_UTMIFSTRIM_ZN_Msk (0x7u << SFR_UTMIFSTRIM_ZN_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver NMOS impedance trimming */
#define SFR_UTMIFSTRIM_ZN(value) ((SFR_UTMIFSTRIM_ZN_Msk & ((value) << SFR_UTMIFSTRIM_ZN_Pos)))
#define SFR_UTMIFSTRIM_ZP_Pos 20
#define SFR_UTMIFSTRIM_ZP_Msk (0x7u << SFR_UTMIFSTRIM_ZP_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver PMOS impedance trimming */
#define SFR_UTMIFSTRIM_ZP(value) ((SFR_UTMIFSTRIM_ZP_Msk & ((value) << SFR_UTMIFSTRIM_ZP_Pos)))
/* -------- SFR_UTMISWAP : (SFR Offset: 0x3C) UTMI DP/DM Pin Swapping Register -------- */
#define SFR_UTMISWAP_PORT0 (0x1u << 0) /**< \brief (SFR_UTMISWAP) PORT 0 DP/DM Pin Swapping */
#define   SFR_UTMISWAP_PORT0_NORMAL (0x0u << 0) /**< \brief (SFR_UTMISWAP) DP/DM normal pinout. */
#define   SFR_UTMISWAP_PORT0_SWAPPED (0x1u << 0) /**< \brief (SFR_UTMISWAP) DP/DM swapped pinout. */
#define SFR_UTMISWAP_PORT1 (0x1u << 1) /**< \brief (SFR_UTMISWAP) PORT 1 DP/DM Pin Swapping */
#define   SFR_UTMISWAP_PORT1_NORMAL (0x0u << 1) /**< \brief (SFR_UTMISWAP) DP/DM normal pinout. */
#define   SFR_UTMISWAP_PORT1_SWAPPED (0x1u << 1) /**< \brief (SFR_UTMISWAP) DP/DM swapped pinout. */
#define SFR_UTMISWAP_PORT2 (0x1u << 2) /**< \brief (SFR_UTMISWAP) PORT 2 DP/DM Pin Swapping */
#define   SFR_UTMISWAP_PORT2_NORMAL (0x0u << 2) /**< \brief (SFR_UTMISWAP) DP/DM normal pinout. */
#define   SFR_UTMISWAP_PORT2_SWAPPED (0x1u << 2) /**< \brief (SFR_UTMISWAP) DP/DM swapped pinout. */
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


/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Static Memory Controller */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_SMC Static Memory Controller */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief SmcCs_number hardware registers */
typedef struct {
  RwReg         SMC_SETUP;        /**< \brief (SmcCs_number Offset: 0x0) SMC Setup Register */
  RwReg         SMC_PULSE;        /**< \brief (SmcCs_number Offset: 0x4) SMC Pulse Register */
  RwReg         SMC_CYCLE;        /**< \brief (SmcCs_number Offset: 0x8) SMC Cycle Register */
  RwReg         SMC_TIMINGS;      /**< \brief (SmcCs_number Offset: 0xC) SMC Timings Register */
  RwReg         SMC_MODE;         /**< \brief (SmcCs_number Offset: 0x10) SMC Mode Register */
} SmcCs_number;
/** \brief SmcPmecc hardware registers */
typedef struct {
  RwReg         SMC_PMECC[11];    /**< \brief (SmcPmecc Offset: 0x0) PMECC Redundancy x Register */
  RoReg         Reserved1[5];
} SmcPmecc;
/** \brief SmcRem hardware registers */
typedef struct {
  RwReg         SMC_REM[12];      /**< \brief (SmcRem Offset: 0x0) PMECC Remainder x Register */
  RoReg         Reserved2[4];
} SmcRem;
/** \brief Smc hardware registers */
#define SMCPMECC_NUMBER 8
#define SMCREM_NUMBER 8
#define SMCCS_NUMBER_NUMBER 4
typedef struct {
  RwReg         SMC_CFG;          /**< \brief (Smc Offset: 0x000) SMC NFC Configuration Register */
  WoReg         SMC_CTRL;         /**< \brief (Smc Offset: 0x004) SMC NFC Control Register */
  RoReg         SMC_SR;           /**< \brief (Smc Offset: 0x008) SMC NFC Status Register */
  WoReg         SMC_IER;          /**< \brief (Smc Offset: 0x00C) SMC NFC Interrupt Enable Register */
  WoReg         SMC_IDR;          /**< \brief (Smc Offset: 0x010) SMC NFC Interrupt Disable Register */
  RoReg         SMC_IMR;          /**< \brief (Smc Offset: 0x014) SMC NFC Interrupt Mask Register */
  RwReg         SMC_ADDR;         /**< \brief (Smc Offset: 0x018) SMC NFC Address Cycle Zero Register */
  RwReg         SMC_BANK;         /**< \brief (Smc Offset: 0x01C) SMC Bank Address Register */
  WoReg         SMC_ECC_CTRL;     /**< \brief (Smc Offset: 0x020) SMC ECC Control Register */
  RwReg         SMC_ECC_MD;       /**< \brief (Smc Offset: 0x024) SMC ECC Mode Register */
  RoReg         SMC_ECC_SR1;      /**< \brief (Smc Offset: 0x028) SMC ECC Status 1 Register */
  RoReg         SMC_ECC_PR0;      /**< \brief (Smc Offset: 0x02C) SMC ECC Parity 0 Register */
  RoReg         SMC_ECC_PR1;      /**< \brief (Smc Offset: 0x030) SMC ECC parity 1 Register */
  RoReg         SMC_ECC_SR2;      /**< \brief (Smc Offset: 0x034) SMC ECC status 2 Register */
  RoReg         SMC_ECC_PR2;      /**< \brief (Smc Offset: 0x038) SMC ECC parity 2 Register */
  RoReg         SMC_ECC_PR3;      /**< \brief (Smc Offset: 0x03C) SMC ECC parity 3 Register */
  RoReg         SMC_ECC_PR4;      /**< \brief (Smc Offset: 0x040) SMC ECC parity 4 Register */
  RoReg         SMC_ECC_PR5;      /**< \brief (Smc Offset: 0x044) SMC ECC parity 5 Register */
  RoReg         SMC_ECC_PR6;      /**< \brief (Smc Offset: 0x048) SMC ECC parity 6 Register */
  RoReg         SMC_ECC_PR7;      /**< \brief (Smc Offset: 0x04C) SMC ECC parity 7 Register */
  RoReg         SMC_ECC_PR8;      /**< \brief (Smc Offset: 0x050) SMC ECC parity 8 Register */
  RoReg         SMC_ECC_PR9;      /**< \brief (Smc Offset: 0x054) SMC ECC parity 9 Register */
  RoReg         SMC_ECC_PR10;     /**< \brief (Smc Offset: 0x058) SMC ECC parity 10 Register */
  RoReg         SMC_ECC_PR11;     /**< \brief (Smc Offset: 0x05C) SMC ECC parity 11 Register */
  RoReg         SMC_ECC_PR12;     /**< \brief (Smc Offset: 0x060) SMC ECC parity 12 Register */
  RoReg         SMC_ECC_PR13;     /**< \brief (Smc Offset: 0x064) SMC ECC parity 13 Register */
  RoReg         SMC_ECC_PR14;     /**< \brief (Smc Offset: 0x068) SMC ECC parity 14 Register */
  RoReg         SMC_ECC_PR15;     /**< \brief (Smc Offset: 0x06C) SMC ECC parity 15 Register */
  RwReg         SMC_PMECCFG;      /**< \brief (Smc Offset: 0x70) PMECC Configuration Register */
  RwReg         SMC_PMECCSAREA;   /**< \brief (Smc Offset: 0x74) PMECC Spare Area Size Register */
  RwReg         SMC_PMECCSADDR;   /**< \brief (Smc Offset: 0x78) PMECC Start Address Register */
  RwReg         SMC_PMECCEADDR;   /**< \brief (Smc Offset: 0x7C) PMECC End Address Register */
  RoReg         Reserved1[1];
  WoReg         SMC_PMECCTRL;     /**< \brief (Smc Offset: 0x84) PMECC Control Register */
  RoReg         SMC_PMECCSR;      /**< \brief (Smc Offset: 0x88) PMECC Status Register */
  WoReg         SMC_PMECCIER;     /**< \brief (Smc Offset: 0x8C) PMECC Interrupt Enable register */
  WoReg         SMC_PMECCIDR;     /**< \brief (Smc Offset: 0x90) PMECC Interrupt Disable Register */
  RoReg         SMC_PMECCIMR;     /**< \brief (Smc Offset: 0x94) PMECC Interrupt Mask Register */
  RoReg         SMC_PMECCISR;     /**< \brief (Smc Offset: 0x98) PMECC Interrupt Status Register */
  RoReg         Reserved2[5];
  SmcPmecc      SMC_PMECC[SMCPMECC_NUMBER]; /**< \brief (Smc Offset: 0xB0) sec_num = 0 .. 7 */
  SmcRem        SMC_REM[SMCREM_NUMBER]; /**< \brief (Smc Offset: 0x2B0) sec_num = 0 .. 7 */
  RoReg         Reserved3[20];
  RwReg         SMC_ELCFG;        /**< \brief (Smc Offset: 0x500) PMECCError Location Configuration Register */
  RoReg         SMC_ELPRIM;       /**< \brief (Smc Offset: 0x504) PMECC Error Location Primitive Register */
  WoReg         SMC_ELEN;         /**< \brief (Smc Offset: 0x508) PMECC Error Location Enable Register */
  WoReg         SMC_ELDIS;        /**< \brief (Smc Offset: 0x50C) PMECC Error Location Disable Register */
  RoReg         SMC_ELSR;         /**< \brief (Smc Offset: 0x510) PMECC Error Location Status Register */
  WoReg         SMC_ELIER;        /**< \brief (Smc Offset: 0x514) PMECC Error Location Interrupt Enable register */
  WoReg         SMC_ELIDR;        /**< \brief (Smc Offset: 0x518) PMECC Error Location Interrupt Disable Register */
  RoReg         SMC_ELIMR;        /**< \brief (Smc Offset: 0x51C) PMECC Error Location Interrupt Mask Register */
  RoReg         SMC_ELISR;        /**< \brief (Smc Offset: 0x520) PMECC Error Location Interrupt Status Register */
  RoReg         Reserved4[1];
  RwReg         SMC_SIGMA0;       /**< \brief (Smc Offset: 0x528) PMECC Error Location SIGMA 0 Register */
  RwReg         SMC_SIGMA1;       /**< \brief (Smc Offset: 0x52C) PMECC Error Location SIGMA 1 Register */
  RwReg         SMC_SIGMA2;       /**< \brief (Smc Offset: 0x530) PMECC Error Location SIGMA 2 Register */
  RwReg         SMC_SIGMA3;       /**< \brief (Smc Offset: 0x534) PMECC Error Location SIGMA 3 Register */
  RwReg         SMC_SIGMA4;       /**< \brief (Smc Offset: 0x538) PMECC Error Location SIGMA 4 Register */
  RwReg         SMC_SIGMA5;       /**< \brief (Smc Offset: 0x53C) PMECC Error Location SIGMA 5 Register */
  RwReg         SMC_SIGMA6;       /**< \brief (Smc Offset: 0x540) PMECC Error Location SIGMA 6 Register */
  RwReg         SMC_SIGMA7;       /**< \brief (Smc Offset: 0x544) PMECC Error Location SIGMA 7 Register */
  RwReg         SMC_SIGMA8;       /**< \brief (Smc Offset: 0x548) PMECC Error Location SIGMA 8 Register */
  RwReg         SMC_SIGMA9;       /**< \brief (Smc Offset: 0x54C) PMECC Error Location SIGMA 9 Register */
  RwReg         SMC_SIGMA10;      /**< \brief (Smc Offset: 0x550) PMECC Error Location SIGMA 10 Register */
  RwReg         SMC_SIGMA11;      /**< \brief (Smc Offset: 0x554) PMECC Error Location SIGMA 11 Register */
  RwReg         SMC_SIGMA12;      /**< \brief (Smc Offset: 0x558) PMECC Error Location SIGMA 12 Register */
  RwReg         SMC_SIGMA13;      /**< \brief (Smc Offset: 0x55C) PMECC Error Location SIGMA 13 Register */
  RwReg         SMC_SIGMA14;      /**< \brief (Smc Offset: 0x560) PMECC Error Location SIGMA 14 Register */
  RwReg         SMC_SIGMA15;      /**< \brief (Smc Offset: 0x564) PMECC Error Location SIGMA 15 Register */
  RwReg         SMC_SIGMA16;      /**< \brief (Smc Offset: 0x568) PMECC Error Location SIGMA 16 Register */
  RwReg         SMC_SIGMA17;      /**< \brief (Smc Offset: 0x56C) PMECC Error Location SIGMA 17 Register */
  RwReg         SMC_SIGMA18;      /**< \brief (Smc Offset: 0x570) PMECC Error Location SIGMA 18 Register */
  RwReg         SMC_SIGMA19;      /**< \brief (Smc Offset: 0x574) PMECC Error Location SIGMA 19 Register */
  RwReg         SMC_SIGMA20;      /**< \brief (Smc Offset: 0x578) PMECC Error Location SIGMA 20 Register */
  RwReg         SMC_SIGMA21;      /**< \brief (Smc Offset: 0x57C) PMECC Error Location SIGMA 21 Register */
  RwReg         SMC_SIGMA22;      /**< \brief (Smc Offset: 0x580) PMECC Error Location SIGMA 22 Register */
  RwReg         SMC_SIGMA23;      /**< \brief (Smc Offset: 0x584) PMECC Error Location SIGMA 23 Register */
  RwReg         SMC_SIGMA24;      /**< \brief (Smc Offset: 0x588) PMECC Error Location SIGMA 24 Register */
  RoReg         SMC_ERRLOC[24];   /**< \brief (Smc Offset: 0x58C) PMECC Error Location 0 Register */
  RoReg         Reserved5[5];
  SmcCs_number  SMC_CS_NUMBER[SMCCS_NUMBER_NUMBER]; /**< \brief (Smc Offset: 0x600) CS_number = 0 .. 3 */
  RoReg         Reserved6[20];
  RwReg         SMC_OCMS;         /**< \brief (Smc Offset: 0x6A0) SMC OCMS Register */
  WoReg         SMC_KEY1;         /**< \brief (Smc Offset: 0x6A4) SMC OCMS KEY1 Register */
  WoReg         SMC_KEY2;         /**< \brief (Smc Offset: 0x6A8) SMC OCMS KEY2 Register */
  RoReg         Reserved7[14];
  WoReg         SMC_WPCR;         /**< \brief (Smc Offset: 0x6E4) SMC Write Protection Control Register */
  RoReg         SMC_WPSR;         /**< \brief (Smc Offset: 0x6E8) SMC Write Protection Status Register */
} Smc;
#endif /* __ASSEMBLY__ */
/* -------- SMC_CFG : (SMC Offset: 0x000) SMC NFC Configuration Register -------- */
#define SMC_CFG_PAGESIZE_Pos 0
#define SMC_CFG_PAGESIZE_Msk (0x7u << SMC_CFG_PAGESIZE_Pos) /**< \brief (SMC_CFG)  */
#define   SMC_CFG_PAGESIZE_PS512_16 (0x0u << 0) /**< \brief (SMC_CFG) Main area 512 Bytes + Spare area 16 Bytes = 528 Bytes */
#define   SMC_CFG_PAGESIZE_PS1024_32 (0x1u << 0) /**< \brief (SMC_CFG) Main area 1024 Bytes + Spare area 32 Bytes = 1056 Bytes */
#define   SMC_CFG_PAGESIZE_PS2048_64 (0x2u << 0) /**< \brief (SMC_CFG) Main area 2048 Bytes + Spare area 64 Bytes = 2112 Bytes */
#define   SMC_CFG_PAGESIZE_PS4096_128 (0x3u << 0) /**< \brief (SMC_CFG) Main area 4096 Bytes + Spare area 128 Bytes = 4224 Bytes */
#define SMC_CFG_WSPARE (0x1u << 8) /**< \brief (SMC_CFG) Write Spare Area */
#define SMC_CFG_RSPARE (0x1u << 9) /**< \brief (SMC_CFG) Read Spare Area */
#define SMC_CFG_EDGECTRL (0x1u << 12) /**< \brief (SMC_CFG) Rising/Falling Edge Detection Control */
#define SMC_CFG_RBEDGE (0x1u << 13) /**< \brief (SMC_CFG) Ready/Busy Signal Edge Detection */
#define SMC_CFG_DTOCYC_Pos 16
#define SMC_CFG_DTOCYC_Msk (0xfu << SMC_CFG_DTOCYC_Pos) /**< \brief (SMC_CFG) Data Timeout Cycle Number */
#define SMC_CFG_DTOCYC(value) ((SMC_CFG_DTOCYC_Msk & ((value) << SMC_CFG_DTOCYC_Pos)))
#define SMC_CFG_DTOMUL_Pos 20
#define SMC_CFG_DTOMUL_Msk (0x7u << SMC_CFG_DTOMUL_Pos) /**< \brief (SMC_CFG) Data Timeout Multiplier */
#define   SMC_CFG_DTOMUL_X1 (0x0u << 20) /**< \brief (SMC_CFG) DTOCYC */
#define   SMC_CFG_DTOMUL_X16 (0x1u << 20) /**< \brief (SMC_CFG) DTOCYC x 16 */
#define   SMC_CFG_DTOMUL_X128 (0x2u << 20) /**< \brief (SMC_CFG) DTOCYC x 128 */
#define   SMC_CFG_DTOMUL_X256 (0x3u << 20) /**< \brief (SMC_CFG) DTOCYC x 256 */
#define   SMC_CFG_DTOMUL_X1024 (0x4u << 20) /**< \brief (SMC_CFG) DTOCYC x 1024 */
#define   SMC_CFG_DTOMUL_X4096 (0x5u << 20) /**< \brief (SMC_CFG) DTOCYC x 4096 */
#define   SMC_CFG_DTOMUL_X65536 (0x6u << 20) /**< \brief (SMC_CFG) DTOCYC x 65536 */
#define   SMC_CFG_DTOMUL_X1048576 (0x7u << 20) /**< \brief (SMC_CFG) DTOCYC x 1048576 */
#define SMC_CFG_NFCSPARESIZE_Pos 24
#define SMC_CFG_NFCSPARESIZE_Msk (0x7fu << SMC_CFG_NFCSPARESIZE_Pos) /**< \brief (SMC_CFG) NAND Flash Spare Area Size Retrieved by the Host Controller */
#define SMC_CFG_NFCSPARESIZE(value) ((SMC_CFG_NFCSPARESIZE_Msk & ((value) << SMC_CFG_NFCSPARESIZE_Pos)))
/* -------- SMC_CTRL : (SMC Offset: 0x004) SMC NFC Control Register -------- */
#define SMC_CTRL_NFCEN (0x1u << 0) /**< \brief (SMC_CTRL) NAND Flash Controller Enable */
#define SMC_CTRL_NFCDIS (0x1u << 1) /**< \brief (SMC_CTRL) NAND Flash Controller Disable */
/* -------- SMC_SR : (SMC Offset: 0x008) SMC NFC Status Register -------- */
#define SMC_SR_SMCSTS (0x1u << 0) /**< \brief (SMC_SR) NAND Flash Controller Status (this field cannot be reset) */
#define SMC_SR_RB_RISE (0x1u << 4) /**< \brief (SMC_SR) Selected Ready Busy Rising Edge Detected */
#define SMC_SR_RB_FALL (0x1u << 5) /**< \brief (SMC_SR) Selected Ready Busy Falling Edge Detected */
#define SMC_SR_NFCBUSY (0x1u << 8) /**< \brief (SMC_SR) NFC Busy (this field cannot be reset) */
#define SMC_SR_NFCWR (0x1u << 11) /**< \brief (SMC_SR) NFC Write/Read Operation (this field cannot be reset) */
#define SMC_SR_NFCSID_Pos 12
#define SMC_SR_NFCSID_Msk (0x7u << SMC_SR_NFCSID_Pos) /**< \brief (SMC_SR) NFC Chip Select ID (this field cannot be reset) */
#define SMC_SR_XFRDONE (0x1u << 16) /**< \brief (SMC_SR) NFC Data Transfer Terminated */
#define SMC_SR_CMDDONE (0x1u << 17) /**< \brief (SMC_SR) Command Done */
#define SMC_SR_ECCRDY (0x1u << 18) /**< \brief (SMC_SR) Hamming ECC Ready */
#define SMC_SR_DTOE (0x1u << 20) /**< \brief (SMC_SR) Data Timeout Error */
#define SMC_SR_UNDEF (0x1u << 21) /**< \brief (SMC_SR) Undefined Area Error */
#define SMC_SR_AWB (0x1u << 22) /**< \brief (SMC_SR) Accessing While Busy */
#define SMC_SR_NFCASE (0x1u << 23) /**< \brief (SMC_SR) NFC Access Size Error */
#define SMC_SR_RB_EDGE3 (0x1u << 27) /**< \brief (SMC_SR) Ready/Busy Line 3 Edge Detected */
/* -------- SMC_IER : (SMC Offset: 0x00C) SMC NFC Interrupt Enable Register -------- */
#define SMC_IER_RB_RISE (0x1u << 4) /**< \brief (SMC_IER) Ready Busy Rising Edge Detection Interrupt Enable */
#define SMC_IER_RB_FALL (0x1u << 5) /**< \brief (SMC_IER) Ready Busy Falling Edge Detection Interrupt Enable */
#define SMC_IER_XFRDONE (0x1u << 16) /**< \brief (SMC_IER) Transfer Done Interrupt Enable */
#define SMC_IER_CMDDONE (0x1u << 17) /**< \brief (SMC_IER) Command Done Interrupt Enable */
#define SMC_IER_DTOE (0x1u << 20) /**< \brief (SMC_IER) Data Timeout Error Interrupt Enable */
#define SMC_IER_UNDEF (0x1u << 21) /**< \brief (SMC_IER) Undefined Area Access Interrupt Enable */
#define SMC_IER_AWB (0x1u << 22) /**< \brief (SMC_IER) Accessing While Busy Interrupt Enable */
#define SMC_IER_NFCASE (0x1u << 23) /**< \brief (SMC_IER) NFC Access Size Error Interrupt Enable */
#define SMC_IER_RB_EDGE3 (0x1u << 27) /**< \brief (SMC_IER) Ready/Busy Line 3 Interrupt Enable */
/* -------- SMC_IDR : (SMC Offset: 0x010) SMC NFC Interrupt Disable Register -------- */
#define SMC_IDR_RB_RISE (0x1u << 4) /**< \brief (SMC_IDR) Ready Busy Rising Edge Detection Interrupt Disable */
#define SMC_IDR_RB_FALL (0x1u << 5) /**< \brief (SMC_IDR) Ready Busy Falling Edge Detection Interrupt Disable */
#define SMC_IDR_XFRDONE (0x1u << 16) /**< \brief (SMC_IDR) Transfer Done Interrupt Disable */
#define SMC_IDR_CMDDONE (0x1u << 17) /**< \brief (SMC_IDR) Command Done Interrupt Disable */
#define SMC_IDR_DTOE (0x1u << 20) /**< \brief (SMC_IDR) Data Timeout Error Interrupt Disable */
#define SMC_IDR_UNDEF (0x1u << 21) /**< \brief (SMC_IDR) Undefined Area Access Interrupt Disable */
#define SMC_IDR_AWB (0x1u << 22) /**< \brief (SMC_IDR) Accessing While Busy Interrupt Disable */
#define SMC_IDR_NFCASE (0x1u << 23) /**< \brief (SMC_IDR) NFC Access Size Error Interrupt Disable */
#define SMC_IDR_RB_EDGE3 (0x1u << 27) /**< \brief (SMC_IDR) Ready/Busy Line 3 Interrupt Disable */
/* -------- SMC_IMR : (SMC Offset: 0x014) SMC NFC Interrupt Mask Register -------- */
#define SMC_IMR_RB_RISE (0x1u << 4) /**< \brief (SMC_IMR) Ready Busy Rising Edge Detection Interrupt Mask */
#define SMC_IMR_RB_FALL (0x1u << 5) /**< \brief (SMC_IMR) Ready Busy Falling Edge Detection Interrupt Mask */
#define SMC_IMR_XFRDONE (0x1u << 16) /**< \brief (SMC_IMR) Transfer Done Interrupt Mask */
#define SMC_IMR_CMDDONE (0x1u << 17) /**< \brief (SMC_IMR) Command Done Interrupt Mask */
#define SMC_IMR_DTOE (0x1u << 20) /**< \brief (SMC_IMR) Data Timeout Error Interrupt Mask */
#define SMC_IMR_UNDEF (0x1u << 21) /**< \brief (SMC_IMR) Undefined Area Access Interrupt Mask5 */
#define SMC_IMR_AWB (0x1u << 22) /**< \brief (SMC_IMR) Accessing While Busy Interrupt Mask */
#define SMC_IMR_NFCASE (0x1u << 23) /**< \brief (SMC_IMR) NFC Access Size Error Interrupt Mask */
#define SMC_IMR_RB_EDGE3 (0x1u << 27) /**< \brief (SMC_IMR) Ready/Busy Line 3 Interrupt Mask */
/* -------- SMC_ADDR : (SMC Offset: 0x018) SMC NFC Address Cycle Zero Register -------- */
#define SMC_ADDR_ADDR_CYCLE0_Pos 0
#define SMC_ADDR_ADDR_CYCLE0_Msk (0xffu << SMC_ADDR_ADDR_CYCLE0_Pos) /**< \brief (SMC_ADDR) NAND Flash Array Address Cycle 0 */
#define SMC_ADDR_ADDR_CYCLE0(value) ((SMC_ADDR_ADDR_CYCLE0_Msk & ((value) << SMC_ADDR_ADDR_CYCLE0_Pos)))
/* -------- SMC_BANK : (SMC Offset: 0x01C) SMC Bank Address Register -------- */
#define SMC_BANK_BANK (0x1u << 0) /**< \brief (SMC_BANK) Bank Identifier */
/* -------- SMC_ECC_CTRL : (SMC Offset: 0x020) SMC ECC Control Register -------- */
#define SMC_ECC_CTRL_RST (0x1u << 0) /**< \brief (SMC_ECC_CTRL) Reset ECC */
#define SMC_ECC_CTRL_SWRST (0x1u << 1) /**< \brief (SMC_ECC_CTRL) Software Reset */
/* -------- SMC_ECC_MD : (SMC Offset: 0x024) SMC ECC Mode Register -------- */
#define SMC_ECC_MD_ECC_PAGESIZE_Pos 0
#define SMC_ECC_MD_ECC_PAGESIZE_Msk (0x3u << SMC_ECC_MD_ECC_PAGESIZE_Pos) /**< \brief (SMC_ECC_MD) ECC Page Size */
#define   SMC_ECC_MD_ECC_PAGESIZE_PS512_16 (0x0u << 0) /**< \brief (SMC_ECC_MD) Main area 512 Bytes + Spare area 16 Bytes = 528 Bytes */
#define   SMC_ECC_MD_ECC_PAGESIZE_PS1024_32 (0x1u << 0) /**< \brief (SMC_ECC_MD) Main area 1024 Bytes + Spare area 32 Bytes = 1056 Bytes */
#define   SMC_ECC_MD_ECC_PAGESIZE_PS2048_64 (0x2u << 0) /**< \brief (SMC_ECC_MD) Main area 2048 Bytes + Spare area 64 Bytes = 2112 Bytes */
#define   SMC_ECC_MD_ECC_PAGESIZE_PS4096_128 (0x3u << 0) /**< \brief (SMC_ECC_MD) Main area 4096 Bytes + Spare area 128 Bytes = 4224 Bytes */
#define SMC_ECC_MD_TYPCORREC_Pos 4
#define SMC_ECC_MD_TYPCORREC_Msk (0x3u << SMC_ECC_MD_TYPCORREC_Pos) /**< \brief (SMC_ECC_MD) Type of Correction */
#define   SMC_ECC_MD_TYPCORREC_CPAGE (0x0u << 4) /**< \brief (SMC_ECC_MD) 1 bit correction for a page of 512/1024/2048/4096 Bytes  (for 8 or 16-bit NAND Flash) */
#define   SMC_ECC_MD_TYPCORREC_C256B (0x1u << 4) /**< \brief (SMC_ECC_MD) 1 bit correction for 256 Bytes of data for a page of 512/2048/4096 bytes (for 8-bit NAND Flash only) */
#define   SMC_ECC_MD_TYPCORREC_C512B (0x2u << 4) /**< \brief (SMC_ECC_MD) 1 bit correction for 512 Bytes of data for a page of 512/2048/4096 bytes (for 8-bit NAND Flash only) */
#define SMC_ECC_MD_HAMMING (0x1u << 8) /**< \brief (SMC_ECC_MD) Hamming Error Correcting Code Selected */
/* -------- SMC_ECC_SR1 : (SMC Offset: 0x028) SMC ECC Status 1 Register -------- */
#define SMC_ECC_SR1_RECERR0 (0x1u << 0) /**< \brief (SMC_ECC_SR1) Recoverable Error */
#define SMC_ECC_SR1_ECCERR0_Pos 1
#define SMC_ECC_SR1_ECCERR0_Msk (0x3u << SMC_ECC_SR1_ECCERR0_Pos) /**< \brief (SMC_ECC_SR1) ECC Error */
#define SMC_ECC_SR1_RECERR1 (0x1u << 4) /**< \brief (SMC_ECC_SR1) Recoverable Error in the page between the 256th and the 511th Bytes or the 512nd and the 1023rd Bytes */
#define SMC_ECC_SR1_ECCERR1 (0x1u << 5) /**< \brief (SMC_ECC_SR1) ECC Error in the page between the 256th and the 511th Bytes or between the 512nd and the 1023rd Bytes */
#define SMC_ECC_SR1_MULERR1 (0x1u << 6) /**< \brief (SMC_ECC_SR1) Multiple Error in the page between the 256th and the 511th Bytes or between the 512nd and the 1023rd Bytes */
#define SMC_ECC_SR1_RECERR2 (0x1u << 8) /**< \brief (SMC_ECC_SR1) Recoverable Error in the page between the 512nd and the 767th Bytes or between the 1024th and the 1535th Bytes */
#define SMC_ECC_SR1_ECCERR2 (0x1u << 9) /**< \brief (SMC_ECC_SR1) ECC Error in the page between the 512nd and the 767th Bytes or between the 1024th and the 1535th Bytes */
#define SMC_ECC_SR1_MULERR2 (0x1u << 10) /**< \brief (SMC_ECC_SR1) Multiple Error in the page between the 512nd and the 767th Bytes or between the 1024th and the 1535th Bytes */
#define SMC_ECC_SR1_RECERR3 (0x1u << 12) /**< \brief (SMC_ECC_SR1) Recoverable Error in the page between the 768th and the 1023rd Bytes or between the 1536th and the 2047th Bytes */
#define SMC_ECC_SR1_ECCERR3 (0x1u << 13) /**< \brief (SMC_ECC_SR1) ECC Error in the page between the 768th and the 1023rd Bytes or between the 1536th and the 2047th Bytes */
#define SMC_ECC_SR1_MULERR3 (0x1u << 14) /**< \brief (SMC_ECC_SR1) Multiple Error in the page between the 768th and the 1023rd Bytes or between the 1536th and the 2047th Bytes */
#define SMC_ECC_SR1_RECERR4 (0x1u << 16) /**< \brief (SMC_ECC_SR1) Recoverable Error in the page between the 1024th and the 1279th Bytes or between the 2048th and the 2559th Bytes */
#define SMC_ECC_SR1_ECCERR4_Pos 17
#define SMC_ECC_SR1_ECCERR4_Msk (0x3u << SMC_ECC_SR1_ECCERR4_Pos) /**< \brief (SMC_ECC_SR1) ECC Error in the page between the 1024th and the 1279th Bytes or between the 2048th and the 2559th Bytes */
#define SMC_ECC_SR1_RECERR5 (0x1u << 20) /**< \brief (SMC_ECC_SR1) Recoverable Error in the page between the 1280th and the 1535th Bytes or between the 2560th and the 3071st Bytes */
#define SMC_ECC_SR1_ECCERR5_Pos 21
#define SMC_ECC_SR1_ECCERR5_Msk (0x3u << SMC_ECC_SR1_ECCERR5_Pos) /**< \brief (SMC_ECC_SR1) ECC Error in the page between the 1280th and the 1535th Bytes or between the 2560th and the 3071st Bytes */
#define SMC_ECC_SR1_RECERR6 (0x1u << 24) /**< \brief (SMC_ECC_SR1) Recoverable Error in the page between the 1536th and the 1791st Bytes or between the 3072nd and the 3583rd Bytes */
#define SMC_ECC_SR1_ECCERR6_Pos 25
#define SMC_ECC_SR1_ECCERR6_Msk (0x3u << SMC_ECC_SR1_ECCERR6_Pos) /**< \brief (SMC_ECC_SR1) ECC Error in the page between the 1536th and the 1791st Bytes or between the 3072nd and the 3583rd Bytes */
#define SMC_ECC_SR1_RECERR7 (0x1u << 28) /**< \brief (SMC_ECC_SR1) Recoverable Error in the page between the 1792nd and the 2047th Bytes or between the 3584th and the 4095th Bytes */
#define SMC_ECC_SR1_ECCERR7_Pos 29
#define SMC_ECC_SR1_ECCERR7_Msk (0x3u << SMC_ECC_SR1_ECCERR7_Pos) /**< \brief (SMC_ECC_SR1) ECC Error in the page between the 1792nd and the 2047th Bytes or between the 3584th and the 4095th Bytes */
/* -------- SMC_ECC_PR0 : (SMC Offset: 0x02C) SMC ECC Parity 0 Register -------- */
#define SMC_ECC_PR0_BITADDR_Pos 0
#define SMC_ECC_PR0_BITADDR_Msk (0xfu << SMC_ECC_PR0_BITADDR_Pos) /**< \brief (SMC_ECC_PR0) Bit Address */
#define SMC_ECC_PR0_WORDADDR_Pos 4
#define SMC_ECC_PR0_WORDADDR_Msk (0xfffu << SMC_ECC_PR0_WORDADDR_Pos) /**< \brief (SMC_ECC_PR0) Word Address */
/* -------- SMC_ECC_PR1 : (SMC Offset: 0x030) SMC ECC parity 1 Register -------- */
#define SMC_ECC_PR1_NPARITY_Pos 0
#define SMC_ECC_PR1_NPARITY_Msk (0xffffu << SMC_ECC_PR1_NPARITY_Pos) /**< \brief (SMC_ECC_PR1) Parity N */
/* -------- SMC_ECC_SR2 : (SMC Offset: 0x034) SMC ECC status 2 Register -------- */
#define SMC_ECC_SR2_RECERR8 (0x1u << 0) /**< \brief (SMC_ECC_SR2) Recoverable Error in the page between the 2048th and the 2303rd Bytes */
#define SMC_ECC_SR2_ECCERR8_Pos 1
#define SMC_ECC_SR2_ECCERR8_Msk (0x3u << SMC_ECC_SR2_ECCERR8_Pos) /**< \brief (SMC_ECC_SR2) ECC Error in the page between the 2048th and the 2303rd Bytes */
#define SMC_ECC_SR2_RECERR9 (0x1u << 4) /**< \brief (SMC_ECC_SR2) Recoverable Error in the page between the 2304th and the 2559th Bytes */
#define SMC_ECC_SR2_ECCERR9 (0x1u << 5) /**< \brief (SMC_ECC_SR2) ECC Error in the page between the 2304th and the 2559th Bytes */
#define SMC_ECC_SR2_MULERR9 (0x1u << 6) /**< \brief (SMC_ECC_SR2) Multiple Error in the page between the 2304th and the 2559th Bytes */
#define SMC_ECC_SR2_RECERR10 (0x1u << 8) /**< \brief (SMC_ECC_SR2) Recoverable Error in the page between the 2560th and the 2815th Bytes */
#define SMC_ECC_SR2_ECCERR10 (0x1u << 9) /**< \brief (SMC_ECC_SR2) ECC Error in the page between the 2560th and the 2815th Bytes */
#define SMC_ECC_SR2_MULERR10 (0x1u << 10) /**< \brief (SMC_ECC_SR2) Multiple Error in the page between the 2560th and the 2815th Bytes */
#define SMC_ECC_SR2_RECERR11 (0x1u << 12) /**< \brief (SMC_ECC_SR2) Recoverable Error in the page between the 2816th and the 3071st Bytes */
#define SMC_ECC_SR2_ECCERR11 (0x1u << 13) /**< \brief (SMC_ECC_SR2) ECC Error in the page between the 2816th and the 3071st Bytes */
#define SMC_ECC_SR2_MULERR11 (0x1u << 14) /**< \brief (SMC_ECC_SR2) Multiple Error in the page between the 2816th and the 3071st Bytes */
#define SMC_ECC_SR2_RECERR12 (0x1u << 16) /**< \brief (SMC_ECC_SR2) Recoverable Error in the page between the 3072nd and the 3327th Bytes */
#define SMC_ECC_SR2_ECCERR12_Pos 17
#define SMC_ECC_SR2_ECCERR12_Msk (0x3u << SMC_ECC_SR2_ECCERR12_Pos) /**< \brief (SMC_ECC_SR2) ECC Error in the page between the 3072nd and the 3327th Bytes */
#define SMC_ECC_SR2_RECERR13 (0x1u << 20) /**< \brief (SMC_ECC_SR2) Recoverable Error in the page between the 3328th and the 3583rd Bytes */
#define SMC_ECC_SR2_ECCERR13_Pos 21
#define SMC_ECC_SR2_ECCERR13_Msk (0x3u << SMC_ECC_SR2_ECCERR13_Pos) /**< \brief (SMC_ECC_SR2) ECC Error in the page between the 3328th and the 3583rd Bytes */
#define SMC_ECC_SR2_RECERR14 (0x1u << 24) /**< \brief (SMC_ECC_SR2) Recoverable Error in the page between the 3584th and the 3839th Bytes */
#define SMC_ECC_SR2_ECCERR14_Pos 25
#define SMC_ECC_SR2_ECCERR14_Msk (0x3u << SMC_ECC_SR2_ECCERR14_Pos) /**< \brief (SMC_ECC_SR2) ECC Error in the page between the 3584th and the 3839th Bytes */
#define SMC_ECC_SR2_RECERR15 (0x1u << 28) /**< \brief (SMC_ECC_SR2) Recoverable Error in the page between the 3840th and the 4095th Bytes */
#define SMC_ECC_SR2_ECCERR15_Pos 29
#define SMC_ECC_SR2_ECCERR15_Msk (0x3u << SMC_ECC_SR2_ECCERR15_Pos) /**< \brief (SMC_ECC_SR2) ECC Error in the page between the 3840th and the 4095th Bytes */
/* -------- SMC_PMECCFG : (SMC Offset: 0x70) PMECC Configuration Register -------- */
#define SMC_PMECCFG_BCH_ERR_Pos 0
#define SMC_PMECCFG_BCH_ERR_Msk (0x7u << SMC_PMECCFG_BCH_ERR_Pos) /**< \brief (SMC_PMECCFG) Error Correcting Capability */
#define   SMC_PMECCFG_BCH_ERR_BCH_ERR2 (0x0u << 0) /**< \brief (SMC_PMECCFG) 2 errors */
#define   SMC_PMECCFG_BCH_ERR_BCH_ERR4 (0x1u << 0) /**< \brief (SMC_PMECCFG) 4 errors */
#define   SMC_PMECCFG_BCH_ERR_BCH_ERR8 (0x2u << 0) /**< \brief (SMC_PMECCFG) 8 errors */
#define   SMC_PMECCFG_BCH_ERR_BCH_ERR12 (0x3u << 0) /**< \brief (SMC_PMECCFG) 12 errors */
#define   SMC_PMECCFG_BCH_ERR_BCH_ERR24 (0x4u << 0) /**< \brief (SMC_PMECCFG) 24 errors */
#define SMC_PMECCFG_SECTORSZ (0x1u << 4) /**< \brief (SMC_PMECCFG) Sector Size */
#define SMC_PMECCFG_PAGESIZE_Pos 8
#define SMC_PMECCFG_PAGESIZE_Msk (0x3u << SMC_PMECCFG_PAGESIZE_Pos) /**< \brief (SMC_PMECCFG) Number of Sectors in the Page */
#define   SMC_PMECCFG_PAGESIZE_PAGESIZE_1SEC (0x0u << 8) /**< \brief (SMC_PMECCFG) 1 sector for main area (512 or 1024 Bytes) */
#define   SMC_PMECCFG_PAGESIZE_PAGESIZE_2SEC (0x1u << 8) /**< \brief (SMC_PMECCFG) 2 sectors for main area (1024 or 2048 Bytes) */
#define   SMC_PMECCFG_PAGESIZE_PAGESIZE_4SEC (0x2u << 8) /**< \brief (SMC_PMECCFG) 4 sectors for main area (2048 or 4096 Bytes) */
#define   SMC_PMECCFG_PAGESIZE_PAGESIZE_8SEC (0x3u << 8) /**< \brief (SMC_PMECCFG) 8 sectors for main area (4096 or 8192 Bytes) */
#define SMC_PMECCFG_NANDWR (0x1u << 12) /**< \brief (SMC_PMECCFG) NAND Write Access */
#define SMC_PMECCFG_SPAREEN (0x1u << 16) /**< \brief (SMC_PMECCFG) Spare Enable */
#define SMC_PMECCFG_AUTO (0x1u << 20) /**< \brief (SMC_PMECCFG) Automatic Mode Enable */
/* -------- SMC_PMECCSAREA : (SMC Offset: 0x74) PMECC Spare Area Size Register -------- */
#define SMC_PMECCSAREA_SPARESIZE_Pos 0
#define SMC_PMECCSAREA_SPARESIZE_Msk (0x1ffu << SMC_PMECCSAREA_SPARESIZE_Pos) /**< \brief (SMC_PMECCSAREA) Spare Area Size */
#define SMC_PMECCSAREA_SPARESIZE(value) ((SMC_PMECCSAREA_SPARESIZE_Msk & ((value) << SMC_PMECCSAREA_SPARESIZE_Pos)))
/* -------- SMC_PMECCSADDR : (SMC Offset: 0x78) PMECC Start Address Register -------- */
#define SMC_PMECCSADDR_STARTADDR_Pos 0
#define SMC_PMECCSADDR_STARTADDR_Msk (0x1ffu << SMC_PMECCSADDR_STARTADDR_Pos) /**< \brief (SMC_PMECCSADDR) ECC Area Start Address */
#define SMC_PMECCSADDR_STARTADDR(value) ((SMC_PMECCSADDR_STARTADDR_Msk & ((value) << SMC_PMECCSADDR_STARTADDR_Pos)))
/* -------- SMC_PMECCEADDR : (SMC Offset: 0x7C) PMECC End Address Register -------- */
#define SMC_PMECCEADDR_ENDADDR_Pos 0
#define SMC_PMECCEADDR_ENDADDR_Msk (0x1ffu << SMC_PMECCEADDR_ENDADDR_Pos) /**< \brief (SMC_PMECCEADDR) ECC Area End Address */
#define SMC_PMECCEADDR_ENDADDR(value) ((SMC_PMECCEADDR_ENDADDR_Msk & ((value) << SMC_PMECCEADDR_ENDADDR_Pos)))
/* -------- SMC_PMECCTRL : (SMC Offset: 0x84) PMECC Control Register -------- */
#define SMC_PMECCTRL_RST (0x1u << 0) /**< \brief (SMC_PMECCTRL) Reset the PMECC Module */
#define SMC_PMECCTRL_DATA (0x1u << 1) /**< \brief (SMC_PMECCTRL) Start a Data Phase */
#define SMC_PMECCTRL_USER (0x1u << 2) /**< \brief (SMC_PMECCTRL) Start a User Mode Phase */
#define SMC_PMECCTRL_ENABLE (0x1u << 4) /**< \brief (SMC_PMECCTRL) PMECC Enable */
#define SMC_PMECCTRL_DISABLE (0x1u << 5) /**< \brief (SMC_PMECCTRL) PMECC Enable */
/* -------- SMC_PMECCSR : (SMC Offset: 0x88) PMECC Status Register -------- */
#define SMC_PMECCSR_BUSY (0x1u << 0) /**< \brief (SMC_PMECCSR) The kernel of the PMECC is busy */
#define SMC_PMECCSR_ENABLE (0x1u << 4) /**< \brief (SMC_PMECCSR) PMECC Enable bit */
/* -------- SMC_PMECCIER : (SMC Offset: 0x8C) PMECC Interrupt Enable register -------- */
#define SMC_PMECCIER_ERRIE (0x1u << 0) /**< \brief (SMC_PMECCIER) Error Interrupt Enable */
/* -------- SMC_PMECCIDR : (SMC Offset: 0x90) PMECC Interrupt Disable Register -------- */
#define SMC_PMECCIDR_ERRID (0x1u << 0) /**< \brief (SMC_PMECCIDR) Error Interrupt Disable */
/* -------- SMC_PMECCIMR : (SMC Offset: 0x94) PMECC Interrupt Mask Register -------- */
#define SMC_PMECCIMR_ERRIM (0x1u << 0) /**< \brief (SMC_PMECCIMR) Error Interrupt Mask */
/* -------- SMC_PMECCISR : (SMC Offset: 0x98) PMECC Interrupt Status Register -------- */
#define SMC_PMECCISR_ERRIS_Pos 0
#define SMC_PMECCISR_ERRIS_Msk (0xffu << SMC_PMECCISR_ERRIS_Pos) /**< \brief (SMC_PMECCISR) Error Interrupt Status Register */
/* -------- SMC_PMECC[11] : (SMC Offset: N/A) PMECC Redundancy x Register -------- */
#define SMC_PMECC_ECC_Pos 0
#define SMC_PMECC_ECC_Msk (0xffffffffu << SMC_PMECC_ECC_Pos) /**< \brief (SMC_PMECC[11]) BCH Redundancy */
/* -------- SMC_REM[12] : (SMC Offset: N/A) PMECC Remainder x Register -------- */
#define SMC_REM_REM2NP1_Pos 0
#define SMC_REM_REM2NP1_Msk (0x3fffu << SMC_REM_REM2NP1_Pos) /**< \brief (SMC_REM[12]) BCH Remainder 2 * N + 1 */
#define SMC_REM_REM2NP3_Pos 16
#define SMC_REM_REM2NP3_Msk (0x3fffu << SMC_REM_REM2NP3_Pos) /**< \brief (SMC_REM[12]) BCH Remainder 2 * N + 3 */
/* -------- SMC_ELCFG : (SMC Offset: 0x500) PMECCError Location Configuration Register -------- */
#define SMC_ELCFG_SECTORSZ (0x1u << 0) /**< \brief (SMC_ELCFG) Sector Size */
#define SMC_ELCFG_ERRNUM_Pos 16
#define SMC_ELCFG_ERRNUM_Msk (0x1fu << SMC_ELCFG_ERRNUM_Pos) /**< \brief (SMC_ELCFG) Number of Errors */
#define SMC_ELCFG_ERRNUM(value) ((SMC_ELCFG_ERRNUM_Msk & ((value) << SMC_ELCFG_ERRNUM_Pos)))
/* -------- SMC_ELEN : (SMC Offset: 0x508) PMECC Error Location Enable Register -------- */
#define SMC_ELEN_ENINIT_Pos 0
#define SMC_ELEN_ENINIT_Msk (0x3fffu << SMC_ELEN_ENINIT_Pos) /**< \brief (SMC_ELEN) Error Location Enable */
#define SMC_ELEN_ENINIT(value) ((SMC_ELEN_ENINIT_Msk & ((value) << SMC_ELEN_ENINIT_Pos)))
/* -------- SMC_ELDIS : (SMC Offset: 0x50C) PMECC Error Location Disable Register -------- */
#define SMC_ELDIS_DIS (0x1u << 0) /**< \brief (SMC_ELDIS) Disable Error Location Engine */
/* -------- SMC_ELSR : (SMC Offset: 0x510) PMECC Error Location Status Register -------- */
#define SMC_ELSR_BUSY (0x1u << 0) /**< \brief (SMC_ELSR) Error Location Engine Busy */
/* -------- SMC_ELIER : (SMC Offset: 0x514) PMECC Error Location Interrupt Enable register -------- */
#define SMC_ELIER_DONE (0x1u << 0) /**< \brief (SMC_ELIER) Computation Terminated Interrupt Enable */
/* -------- SMC_ELIDR : (SMC Offset: 0x518) PMECC Error Location Interrupt Disable Register -------- */
#define SMC_ELIDR_DONE (0x1u << 0) /**< \brief (SMC_ELIDR) Computation Terminated Interrupt Disable */
/* -------- SMC_ELIMR : (SMC Offset: 0x51C) PMECC Error Location Interrupt Mask Register -------- */
#define SMC_ELIMR_DONE (0x1u << 0) /**< \brief (SMC_ELIMR) Computation Terminated Interrupt Mask */
/* -------- SMC_ELISR : (SMC Offset: 0x520) PMECC Error Location Interrupt Status Register -------- */
#define SMC_ELISR_DONE (0x1u << 0) /**< \brief (SMC_ELISR) Computation Terminated Interrupt Status */
#define SMC_ELISR_ERR_CNT_Pos 8
#define SMC_ELISR_ERR_CNT_Msk (0x1fu << SMC_ELISR_ERR_CNT_Pos) /**< \brief (SMC_ELISR) Error Counter value */
/* -------- SMC_SIGMA0 : (SMC Offset: 0x528) PMECC Error Location SIGMA 0 Register -------- */
#define SMC_SIGMA0_SIGMA0_Pos 0
#define SMC_SIGMA0_SIGMA0_Msk (0x3fffu << SMC_SIGMA0_SIGMA0_Pos) /**< \brief (SMC_SIGMA0) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA0_SIGMA0(value) ((SMC_SIGMA0_SIGMA0_Msk & ((value) << SMC_SIGMA0_SIGMA0_Pos)))
/* -------- SMC_SIGMA1 : (SMC Offset: 0x52C) PMECC Error Location SIGMA 1 Register -------- */
#define SMC_SIGMA1_SIGMA1_Pos 0
#define SMC_SIGMA1_SIGMA1_Msk (0x3fffu << SMC_SIGMA1_SIGMA1_Pos) /**< \brief (SMC_SIGMA1) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA1_SIGMA1(value) ((SMC_SIGMA1_SIGMA1_Msk & ((value) << SMC_SIGMA1_SIGMA1_Pos)))
/* -------- SMC_SIGMA2 : (SMC Offset: 0x530) PMECC Error Location SIGMA 2 Register -------- */
#define SMC_SIGMA2_SIGMA2_Pos 0
#define SMC_SIGMA2_SIGMA2_Msk (0x3fffu << SMC_SIGMA2_SIGMA2_Pos) /**< \brief (SMC_SIGMA2) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA2_SIGMA2(value) ((SMC_SIGMA2_SIGMA2_Msk & ((value) << SMC_SIGMA2_SIGMA2_Pos)))
/* -------- SMC_SIGMA3 : (SMC Offset: 0x534) PMECC Error Location SIGMA 3 Register -------- */
#define SMC_SIGMA3_SIGMA3_Pos 0
#define SMC_SIGMA3_SIGMA3_Msk (0x3fffu << SMC_SIGMA3_SIGMA3_Pos) /**< \brief (SMC_SIGMA3) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA3_SIGMA3(value) ((SMC_SIGMA3_SIGMA3_Msk & ((value) << SMC_SIGMA3_SIGMA3_Pos)))
/* -------- SMC_SIGMA4 : (SMC Offset: 0x538) PMECC Error Location SIGMA 4 Register -------- */
#define SMC_SIGMA4_SIGMA4_Pos 0
#define SMC_SIGMA4_SIGMA4_Msk (0x3fffu << SMC_SIGMA4_SIGMA4_Pos) /**< \brief (SMC_SIGMA4) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA4_SIGMA4(value) ((SMC_SIGMA4_SIGMA4_Msk & ((value) << SMC_SIGMA4_SIGMA4_Pos)))
/* -------- SMC_SIGMA5 : (SMC Offset: 0x53C) PMECC Error Location SIGMA 5 Register -------- */
#define SMC_SIGMA5_SIGMA5_Pos 0
#define SMC_SIGMA5_SIGMA5_Msk (0x3fffu << SMC_SIGMA5_SIGMA5_Pos) /**< \brief (SMC_SIGMA5) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA5_SIGMA5(value) ((SMC_SIGMA5_SIGMA5_Msk & ((value) << SMC_SIGMA5_SIGMA5_Pos)))
/* -------- SMC_SIGMA6 : (SMC Offset: 0x540) PMECC Error Location SIGMA 6 Register -------- */
#define SMC_SIGMA6_SIGMA6_Pos 0
#define SMC_SIGMA6_SIGMA6_Msk (0x3fffu << SMC_SIGMA6_SIGMA6_Pos) /**< \brief (SMC_SIGMA6) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA6_SIGMA6(value) ((SMC_SIGMA6_SIGMA6_Msk & ((value) << SMC_SIGMA6_SIGMA6_Pos)))
/* -------- SMC_SIGMA7 : (SMC Offset: 0x544) PMECC Error Location SIGMA 7 Register -------- */
#define SMC_SIGMA7_SIGMA7_Pos 0
#define SMC_SIGMA7_SIGMA7_Msk (0x3fffu << SMC_SIGMA7_SIGMA7_Pos) /**< \brief (SMC_SIGMA7) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA7_SIGMA7(value) ((SMC_SIGMA7_SIGMA7_Msk & ((value) << SMC_SIGMA7_SIGMA7_Pos)))
/* -------- SMC_SIGMA8 : (SMC Offset: 0x548) PMECC Error Location SIGMA 8 Register -------- */
#define SMC_SIGMA8_SIGMA8_Pos 0
#define SMC_SIGMA8_SIGMA8_Msk (0x3fffu << SMC_SIGMA8_SIGMA8_Pos) /**< \brief (SMC_SIGMA8) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA8_SIGMA8(value) ((SMC_SIGMA8_SIGMA8_Msk & ((value) << SMC_SIGMA8_SIGMA8_Pos)))
/* -------- SMC_SIGMA9 : (SMC Offset: 0x54C) PMECC Error Location SIGMA 9 Register -------- */
#define SMC_SIGMA9_SIGMA9_Pos 0
#define SMC_SIGMA9_SIGMA9_Msk (0x3fffu << SMC_SIGMA9_SIGMA9_Pos) /**< \brief (SMC_SIGMA9) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA9_SIGMA9(value) ((SMC_SIGMA9_SIGMA9_Msk & ((value) << SMC_SIGMA9_SIGMA9_Pos)))
/* -------- SMC_SIGMA10 : (SMC Offset: 0x550) PMECC Error Location SIGMA 10 Register -------- */
#define SMC_SIGMA10_SIGMA10_Pos 0
#define SMC_SIGMA10_SIGMA10_Msk (0x3fffu << SMC_SIGMA10_SIGMA10_Pos) /**< \brief (SMC_SIGMA10) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA10_SIGMA10(value) ((SMC_SIGMA10_SIGMA10_Msk & ((value) << SMC_SIGMA10_SIGMA10_Pos)))
/* -------- SMC_SIGMA11 : (SMC Offset: 0x554) PMECC Error Location SIGMA 11 Register -------- */
#define SMC_SIGMA11_SIGMA11_Pos 0
#define SMC_SIGMA11_SIGMA11_Msk (0x3fffu << SMC_SIGMA11_SIGMA11_Pos) /**< \brief (SMC_SIGMA11) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA11_SIGMA11(value) ((SMC_SIGMA11_SIGMA11_Msk & ((value) << SMC_SIGMA11_SIGMA11_Pos)))
/* -------- SMC_SIGMA12 : (SMC Offset: 0x558) PMECC Error Location SIGMA 12 Register -------- */
#define SMC_SIGMA12_SIGMA12_Pos 0
#define SMC_SIGMA12_SIGMA12_Msk (0x3fffu << SMC_SIGMA12_SIGMA12_Pos) /**< \brief (SMC_SIGMA12) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA12_SIGMA12(value) ((SMC_SIGMA12_SIGMA12_Msk & ((value) << SMC_SIGMA12_SIGMA12_Pos)))
/* -------- SMC_SIGMA13 : (SMC Offset: 0x55C) PMECC Error Location SIGMA 13 Register -------- */
#define SMC_SIGMA13_SIGMA13_Pos 0
#define SMC_SIGMA13_SIGMA13_Msk (0x3fffu << SMC_SIGMA13_SIGMA13_Pos) /**< \brief (SMC_SIGMA13) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA13_SIGMA13(value) ((SMC_SIGMA13_SIGMA13_Msk & ((value) << SMC_SIGMA13_SIGMA13_Pos)))
/* -------- SMC_SIGMA14 : (SMC Offset: 0x560) PMECC Error Location SIGMA 14 Register -------- */
#define SMC_SIGMA14_SIGMA14_Pos 0
#define SMC_SIGMA14_SIGMA14_Msk (0x3fffu << SMC_SIGMA14_SIGMA14_Pos) /**< \brief (SMC_SIGMA14) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA14_SIGMA14(value) ((SMC_SIGMA14_SIGMA14_Msk & ((value) << SMC_SIGMA14_SIGMA14_Pos)))
/* -------- SMC_SIGMA15 : (SMC Offset: 0x564) PMECC Error Location SIGMA 15 Register -------- */
#define SMC_SIGMA15_SIGMA15_Pos 0
#define SMC_SIGMA15_SIGMA15_Msk (0x3fffu << SMC_SIGMA15_SIGMA15_Pos) /**< \brief (SMC_SIGMA15) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA15_SIGMA15(value) ((SMC_SIGMA15_SIGMA15_Msk & ((value) << SMC_SIGMA15_SIGMA15_Pos)))
/* -------- SMC_SIGMA16 : (SMC Offset: 0x568) PMECC Error Location SIGMA 16 Register -------- */
#define SMC_SIGMA16_SIGMA16_Pos 0
#define SMC_SIGMA16_SIGMA16_Msk (0x3fffu << SMC_SIGMA16_SIGMA16_Pos) /**< \brief (SMC_SIGMA16) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA16_SIGMA16(value) ((SMC_SIGMA16_SIGMA16_Msk & ((value) << SMC_SIGMA16_SIGMA16_Pos)))
/* -------- SMC_SIGMA17 : (SMC Offset: 0x56C) PMECC Error Location SIGMA 17 Register -------- */
#define SMC_SIGMA17_SIGMA17_Pos 0
#define SMC_SIGMA17_SIGMA17_Msk (0x3fffu << SMC_SIGMA17_SIGMA17_Pos) /**< \brief (SMC_SIGMA17) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA17_SIGMA17(value) ((SMC_SIGMA17_SIGMA17_Msk & ((value) << SMC_SIGMA17_SIGMA17_Pos)))
/* -------- SMC_SIGMA18 : (SMC Offset: 0x570) PMECC Error Location SIGMA 18 Register -------- */
#define SMC_SIGMA18_SIGMA18_Pos 0
#define SMC_SIGMA18_SIGMA18_Msk (0x3fffu << SMC_SIGMA18_SIGMA18_Pos) /**< \brief (SMC_SIGMA18) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA18_SIGMA18(value) ((SMC_SIGMA18_SIGMA18_Msk & ((value) << SMC_SIGMA18_SIGMA18_Pos)))
/* -------- SMC_SIGMA19 : (SMC Offset: 0x574) PMECC Error Location SIGMA 19 Register -------- */
#define SMC_SIGMA19_SIGMA19_Pos 0
#define SMC_SIGMA19_SIGMA19_Msk (0x3fffu << SMC_SIGMA19_SIGMA19_Pos) /**< \brief (SMC_SIGMA19) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA19_SIGMA19(value) ((SMC_SIGMA19_SIGMA19_Msk & ((value) << SMC_SIGMA19_SIGMA19_Pos)))
/* -------- SMC_SIGMA20 : (SMC Offset: 0x578) PMECC Error Location SIGMA 20 Register -------- */
#define SMC_SIGMA20_SIGMA20_Pos 0
#define SMC_SIGMA20_SIGMA20_Msk (0x3fffu << SMC_SIGMA20_SIGMA20_Pos) /**< \brief (SMC_SIGMA20) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA20_SIGMA20(value) ((SMC_SIGMA20_SIGMA20_Msk & ((value) << SMC_SIGMA20_SIGMA20_Pos)))
/* -------- SMC_SIGMA21 : (SMC Offset: 0x57C) PMECC Error Location SIGMA 21 Register -------- */
#define SMC_SIGMA21_SIGMA21_Pos 0
#define SMC_SIGMA21_SIGMA21_Msk (0x3fffu << SMC_SIGMA21_SIGMA21_Pos) /**< \brief (SMC_SIGMA21) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA21_SIGMA21(value) ((SMC_SIGMA21_SIGMA21_Msk & ((value) << SMC_SIGMA21_SIGMA21_Pos)))
/* -------- SMC_SIGMA22 : (SMC Offset: 0x580) PMECC Error Location SIGMA 22 Register -------- */
#define SMC_SIGMA22_SIGMA22_Pos 0
#define SMC_SIGMA22_SIGMA22_Msk (0x3fffu << SMC_SIGMA22_SIGMA22_Pos) /**< \brief (SMC_SIGMA22) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA22_SIGMA22(value) ((SMC_SIGMA22_SIGMA22_Msk & ((value) << SMC_SIGMA22_SIGMA22_Pos)))
/* -------- SMC_SIGMA23 : (SMC Offset: 0x584) PMECC Error Location SIGMA 23 Register -------- */
#define SMC_SIGMA23_SIGMA23_Pos 0
#define SMC_SIGMA23_SIGMA23_Msk (0x3fffu << SMC_SIGMA23_SIGMA23_Pos) /**< \brief (SMC_SIGMA23) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA23_SIGMA23(value) ((SMC_SIGMA23_SIGMA23_Msk & ((value) << SMC_SIGMA23_SIGMA23_Pos)))
/* -------- SMC_SIGMA24 : (SMC Offset: 0x588) PMECC Error Location SIGMA 24 Register -------- */
#define SMC_SIGMA24_SIGMA24_Pos 0
#define SMC_SIGMA24_SIGMA24_Msk (0x3fffu << SMC_SIGMA24_SIGMA24_Pos) /**< \brief (SMC_SIGMA24) Coefficient of degree x in the SIGMA polynomial. */
#define SMC_SIGMA24_SIGMA24(value) ((SMC_SIGMA24_SIGMA24_Msk & ((value) << SMC_SIGMA24_SIGMA24_Pos)))
/* -------- SMC_ERRLOC[24] : (SMC Offset: 0x58C) PMECC Error Location 0 Register -------- */
#define SMC_ERRLOC_ERRLOCN_Pos 0
#define SMC_ERRLOC_ERRLOCN_Msk (0x3fffu << SMC_ERRLOC_ERRLOCN_Pos) /**< \brief (SMC_ERRLOC[24]) Error Position within the Set {sector area, spare area} */
/* -------- SMC_SETUP : (SMC Offset: N/A) SMC Setup Register -------- */
#define SMC_SETUP_NWE_SETUP_Pos 0
#define SMC_SETUP_NWE_SETUP_Msk (0x3fu << SMC_SETUP_NWE_SETUP_Pos) /**< \brief (SMC_SETUP) NWE Setup Length */
#define SMC_SETUP_NWE_SETUP(value) ((SMC_SETUP_NWE_SETUP_Msk & ((value) << SMC_SETUP_NWE_SETUP_Pos)))
#define SMC_SETUP_NCS_WR_SETUP_Pos 8
#define SMC_SETUP_NCS_WR_SETUP_Msk (0x3fu << SMC_SETUP_NCS_WR_SETUP_Pos) /**< \brief (SMC_SETUP) NCS Setup Length in Write Access */
#define SMC_SETUP_NCS_WR_SETUP(value) ((SMC_SETUP_NCS_WR_SETUP_Msk & ((value) << SMC_SETUP_NCS_WR_SETUP_Pos)))
#define SMC_SETUP_NRD_SETUP_Pos 16
#define SMC_SETUP_NRD_SETUP_Msk (0x3fu << SMC_SETUP_NRD_SETUP_Pos) /**< \brief (SMC_SETUP) NRD Setup Length */
#define SMC_SETUP_NRD_SETUP(value) ((SMC_SETUP_NRD_SETUP_Msk & ((value) << SMC_SETUP_NRD_SETUP_Pos)))
#define SMC_SETUP_NCS_RD_SETUP_Pos 24
#define SMC_SETUP_NCS_RD_SETUP_Msk (0x3fu << SMC_SETUP_NCS_RD_SETUP_Pos) /**< \brief (SMC_SETUP) NCS Setup Length in Read Access */
#define SMC_SETUP_NCS_RD_SETUP(value) ((SMC_SETUP_NCS_RD_SETUP_Msk & ((value) << SMC_SETUP_NCS_RD_SETUP_Pos)))
/* -------- SMC_PULSE : (SMC Offset: N/A) SMC Pulse Register -------- */
#define SMC_PULSE_NWE_PULSE_Pos 0
#define SMC_PULSE_NWE_PULSE_Msk (0x3fu << SMC_PULSE_NWE_PULSE_Pos) /**< \brief (SMC_PULSE) NWE Pulse Length */
#define SMC_PULSE_NWE_PULSE(value) ((SMC_PULSE_NWE_PULSE_Msk & ((value) << SMC_PULSE_NWE_PULSE_Pos)))
#define SMC_PULSE_NCS_WR_PULSE_Pos 8
#define SMC_PULSE_NCS_WR_PULSE_Msk (0x3fu << SMC_PULSE_NCS_WR_PULSE_Pos) /**< \brief (SMC_PULSE) NCS Pulse Length in WRITE Access */
#define SMC_PULSE_NCS_WR_PULSE(value) ((SMC_PULSE_NCS_WR_PULSE_Msk & ((value) << SMC_PULSE_NCS_WR_PULSE_Pos)))
#define SMC_PULSE_NRD_PULSE_Pos 16
#define SMC_PULSE_NRD_PULSE_Msk (0x3fu << SMC_PULSE_NRD_PULSE_Pos) /**< \brief (SMC_PULSE) NRD Pulse Length */
#define SMC_PULSE_NRD_PULSE(value) ((SMC_PULSE_NRD_PULSE_Msk & ((value) << SMC_PULSE_NRD_PULSE_Pos)))
#define SMC_PULSE_NCS_RD_PULSE_Pos 24
#define SMC_PULSE_NCS_RD_PULSE_Msk (0x3fu << SMC_PULSE_NCS_RD_PULSE_Pos) /**< \brief (SMC_PULSE) NCS Pulse Length in READ Access */
#define SMC_PULSE_NCS_RD_PULSE(value) ((SMC_PULSE_NCS_RD_PULSE_Msk & ((value) << SMC_PULSE_NCS_RD_PULSE_Pos)))
/* -------- SMC_CYCLE : (SMC Offset: N/A) SMC Cycle Register -------- */
#define SMC_CYCLE_NWE_CYCLE_Pos 0
#define SMC_CYCLE_NWE_CYCLE_Msk (0x1ffu << SMC_CYCLE_NWE_CYCLE_Pos) /**< \brief (SMC_CYCLE) Total Write Cycle Length */
#define SMC_CYCLE_NWE_CYCLE(value) ((SMC_CYCLE_NWE_CYCLE_Msk & ((value) << SMC_CYCLE_NWE_CYCLE_Pos)))
#define SMC_CYCLE_NRD_CYCLE_Pos 16
#define SMC_CYCLE_NRD_CYCLE_Msk (0x1ffu << SMC_CYCLE_NRD_CYCLE_Pos) /**< \brief (SMC_CYCLE) Total Read Cycle Length */
#define SMC_CYCLE_NRD_CYCLE(value) ((SMC_CYCLE_NRD_CYCLE_Msk & ((value) << SMC_CYCLE_NRD_CYCLE_Pos)))
/* -------- SMC_TIMINGS : (SMC Offset: N/A) SMC Timings Register -------- */
#define SMC_TIMINGS_TCLR_Pos 0
#define SMC_TIMINGS_TCLR_Msk (0xfu << SMC_TIMINGS_TCLR_Pos) /**< \brief (SMC_TIMINGS) CLE to REN Low Delay */
#define SMC_TIMINGS_TCLR(value) ((SMC_TIMINGS_TCLR_Msk & ((value) << SMC_TIMINGS_TCLR_Pos)))
#define SMC_TIMINGS_TADL_Pos 4
#define SMC_TIMINGS_TADL_Msk (0xfu << SMC_TIMINGS_TADL_Pos) /**< \brief (SMC_TIMINGS) ALE to Data Start */
#define SMC_TIMINGS_TADL(value) ((SMC_TIMINGS_TADL_Msk & ((value) << SMC_TIMINGS_TADL_Pos)))
#define SMC_TIMINGS_TAR_Pos 8
#define SMC_TIMINGS_TAR_Msk (0xfu << SMC_TIMINGS_TAR_Pos) /**< \brief (SMC_TIMINGS) ALE to REN Low Delay */
#define SMC_TIMINGS_TAR(value) ((SMC_TIMINGS_TAR_Msk & ((value) << SMC_TIMINGS_TAR_Pos)))
#define SMC_TIMINGS_OCMS (0x1u << 12) /**< \brief (SMC_TIMINGS) Off Chip Memory Scrambling Enable */
#define SMC_TIMINGS_TRR_Pos 16
#define SMC_TIMINGS_TRR_Msk (0xfu << SMC_TIMINGS_TRR_Pos) /**< \brief (SMC_TIMINGS) Ready to REN Low Delay */
#define SMC_TIMINGS_TRR(value) ((SMC_TIMINGS_TRR_Msk & ((value) << SMC_TIMINGS_TRR_Pos)))
#define SMC_TIMINGS_TWB_Pos 24
#define SMC_TIMINGS_TWB_Msk (0xfu << SMC_TIMINGS_TWB_Pos) /**< \brief (SMC_TIMINGS) WEN High to REN to Busy */
#define SMC_TIMINGS_TWB(value) ((SMC_TIMINGS_TWB_Msk & ((value) << SMC_TIMINGS_TWB_Pos)))
#define SMC_TIMINGS_RBNSEL_Pos 28
#define SMC_TIMINGS_RBNSEL_Msk (0x7u << SMC_TIMINGS_RBNSEL_Pos) /**< \brief (SMC_TIMINGS) Ready/Busy Line Selection */
#define SMC_TIMINGS_RBNSEL(value) ((SMC_TIMINGS_RBNSEL_Msk & ((value) << SMC_TIMINGS_RBNSEL_Pos)))
#define SMC_TIMINGS_NFSEL (0x1u << 31) /**< \brief (SMC_TIMINGS) NAND Flash Selection */
/* -------- SMC_MODE : (SMC Offset: N/A) SMC Mode Register -------- */
#define SMC_MODE_READ_MODE (0x1u << 0) /**< \brief (SMC_MODE)  */
#define   SMC_MODE_READ_MODE_NCS_CTRL (0x0u << 0) /**< \brief (SMC_MODE) The Read operation is controlled by the NCS signal. */
#define   SMC_MODE_READ_MODE_NRD_CTRL (0x1u << 0) /**< \brief (SMC_MODE) The Read operation is controlled by the NRD signal. */
#define SMC_MODE_WRITE_MODE (0x1u << 1) /**< \brief (SMC_MODE)  */
#define   SMC_MODE_WRITE_MODE_NCS_CTRL (0x0u << 1) /**< \brief (SMC_MODE) The Write operation is controller by the NCS signal. */
#define   SMC_MODE_WRITE_MODE_NWE_CTRL (0x1u << 1) /**< \brief (SMC_MODE) The Write operation is controlled by the NWE signal. */
#define SMC_MODE_EXNW_MODE_Pos 4
#define SMC_MODE_EXNW_MODE_Msk (0x3u << SMC_MODE_EXNW_MODE_Pos) /**< \brief (SMC_MODE) NWAIT Mode */
#define   SMC_MODE_EXNW_MODE_DISABLED (0x0u << 4) /**< \brief (SMC_MODE) Disabled */
#define   SMC_MODE_EXNW_MODE_FROZEN (0x2u << 4) /**< \brief (SMC_MODE) Frozen Mode */
#define   SMC_MODE_EXNW_MODE_READY (0x3u << 4) /**< \brief (SMC_MODE) Ready Mode */
#define SMC_MODE_BAT (0x1u << 8) /**< \brief (SMC_MODE) Byte Access Type */
#define SMC_MODE_DBW (0x1u << 12) /**< \brief (SMC_MODE) Data Bus Width */
#define   SMC_MODE_DBW_BIT_8 (0x0u << 12) /**< \brief (SMC_MODE) 8-bit bus */
#define   SMC_MODE_DBW_BIT_16 (0x1u << 12) /**< \brief (SMC_MODE) 16-bit bus */
#define SMC_MODE_TDF_CYCLES_Pos 16
#define SMC_MODE_TDF_CYCLES_Msk (0xfu << SMC_MODE_TDF_CYCLES_Pos) /**< \brief (SMC_MODE) Data Float Time */
#define SMC_MODE_TDF_CYCLES(value) ((SMC_MODE_TDF_CYCLES_Msk & ((value) << SMC_MODE_TDF_CYCLES_Pos)))
#define SMC_MODE_TDF_MODE (0x1u << 20) /**< \brief (SMC_MODE) TDF Optimization */
/* -------- SMC_OCMS : (SMC Offset: 0x6A0) SMC OCMS Register -------- */
#define SMC_OCMS_SMSE (0x1u << 0) /**< \brief (SMC_OCMS) Static Memory Controller Scrambling Enable */
#define SMC_OCMS_SRSE (0x1u << 1) /**< \brief (SMC_OCMS) SRAM Scrambling Enable */
/* -------- SMC_KEY1 : (SMC Offset: 0x6A4) SMC OCMS KEY1 Register -------- */
#define SMC_KEY1_KEY1_Pos 0
#define SMC_KEY1_KEY1_Msk (0xffffffffu << SMC_KEY1_KEY1_Pos) /**< \brief (SMC_KEY1) Off Chip Memory Scrambling (OCMS) Key Part 1 */
#define SMC_KEY1_KEY1(value) ((SMC_KEY1_KEY1_Msk & ((value) << SMC_KEY1_KEY1_Pos)))
/* -------- SMC_KEY2 : (SMC Offset: 0x6A8) SMC OCMS KEY2 Register -------- */
#define SMC_KEY2_KEY2_Pos 0
#define SMC_KEY2_KEY2_Msk (0xffffffffu << SMC_KEY2_KEY2_Pos) /**< \brief (SMC_KEY2) Off Chip Memory Scrambling (OCMS) Key Part 2 */
#define SMC_KEY2_KEY2(value) ((SMC_KEY2_KEY2_Msk & ((value) << SMC_KEY2_KEY2_Pos)))
/* -------- SMC_WPCR : (SMC Offset: 0x6E4) SMC Write Protection Control Register -------- */
#define SMC_WPCR_WP_EN (0x1u << 0) /**< \brief (SMC_WPCR) Write Protection Enable */
#define SMC_WPCR_WP_KEY_Pos 8
#define SMC_WPCR_WP_KEY_Msk (0xffffffu << SMC_WPCR_WP_KEY_Pos) /**< \brief (SMC_WPCR) Write Protection KEY password */
#define SMC_WPCR_WP_KEY(value) ((SMC_WPCR_WP_KEY_Msk & ((value) << SMC_WPCR_WP_KEY_Pos)))
/* -------- SMC_WPSR : (SMC Offset: 0x6E8) SMC Write Protection Status Register -------- */
#define SMC_WPSR_WP_VS_Pos 0
#define SMC_WPSR_WP_VS_Msk (0xfu << SMC_WPSR_WP_VS_Pos) /**< \brief (SMC_WPSR) Write Protection Violation Status */
#define SMC_WPSR_WP_VSRC_Pos 8
#define SMC_WPSR_WP_VSRC_Msk (0xffffu << SMC_WPSR_WP_VSRC_Pos) /**< \brief (SMC_WPSR) Write Protection Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Serial Peripheral Interface */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_SPI Serial Peripheral Interface */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Spi hardware registers */
typedef struct {
  WoReg SPI_CR;        /**< \brief (Spi Offset: 0x00) Control Register */
  RwReg SPI_MR;        /**< \brief (Spi Offset: 0x04) Mode Register */
  RoReg SPI_RDR;       /**< \brief (Spi Offset: 0x08) Receive Data Register */
  WoReg SPI_TDR;       /**< \brief (Spi Offset: 0x0C) Transmit Data Register */
  RoReg SPI_SR;        /**< \brief (Spi Offset: 0x10) Status Register */
  WoReg SPI_IER;       /**< \brief (Spi Offset: 0x14) Interrupt Enable Register */
  WoReg SPI_IDR;       /**< \brief (Spi Offset: 0x18) Interrupt Disable Register */
  RoReg SPI_IMR;       /**< \brief (Spi Offset: 0x1C) Interrupt Mask Register */
  RoReg Reserved1[4];
  RwReg SPI_CSR[4];    /**< \brief (Spi Offset: 0x30) Chip Select Register */
  RoReg Reserved2[41];
  RwReg SPI_WPMR;      /**< \brief (Spi Offset: 0xE4) Write Protection Control Register */
  RoReg SPI_WPSR;      /**< \brief (Spi Offset: 0xE8) Write Protection Status Register */
} Spi;
#endif /* __ASSEMBLY__ */
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
#define SPI_SR_ENDRX (0x1u << 4) /**< \brief (SPI_SR)  */
#define SPI_SR_ENDTX (0x1u << 5) /**< \brief (SPI_SR)  */
#define SPI_SR_RXBUFF (0x1u << 6) /**< \brief (SPI_SR)  */
#define SPI_SR_TXBUFE (0x1u << 7) /**< \brief (SPI_SR)  */
#define SPI_SR_NSSR (0x1u << 8) /**< \brief (SPI_SR) NSS Rising */
#define SPI_SR_TXEMPTY (0x1u << 9) /**< \brief (SPI_SR) Transmission Registers Empty */
#define SPI_SR_UNDES (0x1u << 10) /**< \brief (SPI_SR) Underrun Error Status (Slave Mode Only) */
#define SPI_SR_SPIENS (0x1u << 16) /**< \brief (SPI_SR) SPI Enable Status */
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- */
#define SPI_IER_RDRF (0x1u << 0) /**< \brief (SPI_IER) Receive Data Register Full Interrupt Enable */
#define SPI_IER_TDRE (0x1u << 1) /**< \brief (SPI_IER) SPI Transmit Data Register Empty Interrupt Enable */
#define SPI_IER_MODF (0x1u << 2) /**< \brief (SPI_IER) Mode Fault Error Interrupt Enable */
#define SPI_IER_OVRES (0x1u << 3) /**< \brief (SPI_IER) Overrun Error Interrupt Enable */
#define SPI_IER_ENDRX (0x1u << 4) /**< \brief (SPI_IER)  */
#define SPI_IER_ENDTX (0x1u << 5) /**< \brief (SPI_IER)  */
#define SPI_IER_RXBUFF (0x1u << 6) /**< \brief (SPI_IER)  */
#define SPI_IER_TXBUFE (0x1u << 7) /**< \brief (SPI_IER)  */
#define SPI_IER_NSSR (0x1u << 8) /**< \brief (SPI_IER) NSS Rising Interrupt Enable */
#define SPI_IER_TXEMPTY (0x1u << 9) /**< \brief (SPI_IER) Transmission Registers Empty Enable */
#define SPI_IER_UNDES (0x1u << 10) /**< \brief (SPI_IER) Underrun Error Interrupt Enable */
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
#define SPI_IDR_RDRF (0x1u << 0) /**< \brief (SPI_IDR) Receive Data Register Full Interrupt Disable */
#define SPI_IDR_TDRE (0x1u << 1) /**< \brief (SPI_IDR) SPI Transmit Data Register Empty Interrupt Disable */
#define SPI_IDR_MODF (0x1u << 2) /**< \brief (SPI_IDR) Mode Fault Error Interrupt Disable */
#define SPI_IDR_OVRES (0x1u << 3) /**< \brief (SPI_IDR) Overrun Error Interrupt Disable */
#define SPI_IDR_ENDRX (0x1u << 4) /**< \brief (SPI_IDR)  */
#define SPI_IDR_ENDTX (0x1u << 5) /**< \brief (SPI_IDR)  */
#define SPI_IDR_RXBUFF (0x1u << 6) /**< \brief (SPI_IDR)  */
#define SPI_IDR_TXBUFE (0x1u << 7) /**< \brief (SPI_IDR)  */
#define SPI_IDR_NSSR (0x1u << 8) /**< \brief (SPI_IDR) NSS Rising Interrupt Disable */
#define SPI_IDR_TXEMPTY (0x1u << 9) /**< \brief (SPI_IDR) Transmission Registers Empty Disable */
#define SPI_IDR_UNDES (0x1u << 10) /**< \brief (SPI_IDR) Underrun Error Interrupt Disable */
/* -------- SPI_IMR : (SPI Offset: 0x1C) Interrupt Mask Register -------- */
#define SPI_IMR_RDRF (0x1u << 0) /**< \brief (SPI_IMR) Receive Data Register Full Interrupt Mask */
#define SPI_IMR_TDRE (0x1u << 1) /**< \brief (SPI_IMR) SPI Transmit Data Register Empty Interrupt Mask */
#define SPI_IMR_MODF (0x1u << 2) /**< \brief (SPI_IMR) Mode Fault Error Interrupt Mask */
#define SPI_IMR_OVRES (0x1u << 3) /**< \brief (SPI_IMR) Overrun Error Interrupt Mask */
#define SPI_IMR_ENDRX (0x1u << 4) /**< \brief (SPI_IMR)  */
#define SPI_IMR_ENDTX (0x1u << 5) /**< \brief (SPI_IMR)  */
#define SPI_IMR_RXBUFF (0x1u << 6) /**< \brief (SPI_IMR)  */
#define SPI_IMR_TXBUFE (0x1u << 7) /**< \brief (SPI_IMR)  */
#define SPI_IMR_NSSR (0x1u << 8) /**< \brief (SPI_IMR) NSS Rising Interrupt Mask */
#define SPI_IMR_TXEMPTY (0x1u << 9) /**< \brief (SPI_IMR) Transmission Registers Empty Mask */
#define SPI_IMR_UNDES (0x1u << 10) /**< \brief (SPI_IMR) Underrun Error Interrupt Mask */
/* -------- SPI_CSR[4] : (SPI Offset: 0x30) Chip Select Register -------- */
#define SPI_CSR_CPOL (0x1u << 0) /**< \brief (SPI_CSR[4]) Clock Polarity */
#define SPI_CSR_NCPHA (0x1u << 1) /**< \brief (SPI_CSR[4]) Clock Phase */
#define SPI_CSR_CSNAAT (0x1u << 2) /**< \brief (SPI_CSR[4]) Chip Select Not Active After Transfer (Ignored if CSAAT = 1) */
#define SPI_CSR_CSAAT (0x1u << 3) /**< \brief (SPI_CSR[4]) Chip Select Not Active After Transfer (Ignored if CSAAT = 1) */
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
#define SPI_WPMR_SPIWPEN (0x1u << 0) /**< \brief (SPI_WPMR) SPI Write Protection Enable */
#define SPI_WPMR_SPIWPKEY_Pos 8
#define SPI_WPMR_SPIWPKEY_Msk (0xffffffu << SPI_WPMR_SPIWPKEY_Pos) /**< \brief (SPI_WPMR) SPI Write Protection Key Password */
#define SPI_WPMR_SPIWPKEY(value) ((SPI_WPMR_SPIWPKEY_Msk & ((value) << SPI_WPMR_SPIWPKEY_Pos)))
/* -------- SPI_WPSR : (SPI Offset: 0xE8) Write Protection Status Register -------- */
#define SPI_WPSR_SPIWPVS_Pos 0
#define SPI_WPSR_SPIWPVS_Msk (0x7u << SPI_WPSR_SPIWPVS_Pos) /**< \brief (SPI_WPSR) SPI Write Protection Violation Status */
#define SPI_WPSR_SPIWPVSRC_Pos 8
#define SPI_WPSR_SPIWPVSRC_Msk (0xffu << SPI_WPSR_SPIWPVSRC_Pos) /**< \brief (SPI_WPSR) SPI Write Protection Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Timer Counter */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_TC Timer Counter */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief TcChannel hardware registers */
typedef struct {
  RwReg      TC_CCR;        /**< \brief (TcChannel Offset: 0x0) Channel Control Register */
  RwReg      TC_CMR;        /**< \brief (TcChannel Offset: 0x4) Channel Mode Register */
  RwReg      TC_SMMR;       /**< \brief (TcChannel Offset: 0x8) Stepper Motor Mode Register */
  RwReg      TC_RAB;        /**< \brief (TcChannel Offset: 0xC) Register AB */
  RwReg      TC_CV;         /**< \brief (TcChannel Offset: 0x10) Counter Value */
  RwReg      TC_RA;         /**< \brief (TcChannel Offset: 0x14) Register A */
  RwReg      TC_RB;         /**< \brief (TcChannel Offset: 0x18) Register B */
  RwReg      TC_RC;         /**< \brief (TcChannel Offset: 0x1C) Register C */
  RwReg      TC_SR;         /**< \brief (TcChannel Offset: 0x20) Status Register */
  RwReg      TC_IER;        /**< \brief (TcChannel Offset: 0x24) Interrupt Enable Register */
  RwReg      TC_IDR;        /**< \brief (TcChannel Offset: 0x28) Interrupt Disable Register */
  RwReg      TC_IMR;        /**< \brief (TcChannel Offset: 0x2C) Interrupt Mask Register */
  RoReg      Reserved1[4];
} TcChannel;
/** \brief Tc hardware registers */
#define TCCHANNEL_NUMBER 3
typedef struct {
  TcChannel  TC_CHANNEL[TCCHANNEL_NUMBER]; /**< \brief (Tc Offset: 0x0) channel = 0 .. 2 */
  WoReg      TC_BCR;        /**< \brief (Tc Offset: 0xC0) Block Control Register */
  RwReg      TC_BMR;        /**< \brief (Tc Offset: 0xC4) Block Mode Register */
  RoReg      Reserved1[7];
  RwReg      TC_WPMR;       /**< \brief (Tc Offset: 0xE4) Write Protect Mode Register */
} Tc;
#endif /* __ASSEMBLY__ */
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
/* -------- TC_WPMR : (TC Offset: 0xE4) Write Protect Mode Register -------- */
#define TC_WPMR_WPEN (0x1u << 0) /**< \brief (TC_WPMR) Write Protect Enable */
#define TC_WPMR_WPKEY_Pos 8
#define TC_WPMR_WPKEY_Msk (0xffffffu << TC_WPMR_WPKEY_Pos) /**< \brief (TC_WPMR) Write Protect KEY */
#define TC_WPMR_WPKEY(value) ((TC_WPMR_WPKEY_Msk & ((value) << TC_WPMR_WPKEY_Pos)))

/*@}*/
/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Two-wire Interface */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_TWI Two-wire Interface */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Twi hardware registers */
typedef struct {
  WoReg TWI_CR;           /**< \brief (Twi Offset: 0x00) Control Register */
  RwReg TWI_MMR;          /**< \brief (Twi Offset: 0x04) Master Mode Register */
  RwReg TWI_SMR;          /**< \brief (Twi Offset: 0x08) Slave Mode Register */
  RwReg TWI_IADR;         /**< \brief (Twi Offset: 0x0C) Internal Address Register */
  RwReg TWI_CWGR;         /**< \brief (Twi Offset: 0x10) Clock Waveform Generator Register */
  RoReg Reserved1[3];
  RoReg TWI_SR;           /**< \brief (Twi Offset: 0x20) Status Register */
  WoReg TWI_IER;          /**< \brief (Twi Offset: 0x24) Interrupt Enable Register */
  WoReg TWI_IDR;          /**< \brief (Twi Offset: 0x28) Interrupt Disable Register */
  RoReg TWI_IMR;          /**< \brief (Twi Offset: 0x2C) Interrupt Mask Register */
  RoReg TWI_RHR;          /**< \brief (Twi Offset: 0x30) Receive Holding Register */
  WoReg TWI_THR;          /**< \brief (Twi Offset: 0x34) Transmit Holding Register */
  RoReg Reserved2[43];
  RwReg TWI_WPROT_MODE;   /**< \brief (Twi Offset: 0xE4) Protection Mode Register */
  RoReg TWI_WPROT_STATUS; /**< \brief (Twi Offset: 0xE8) Protection Status Register */
} Twi;
#endif /* __ASSEMBLY__ */
/* -------- TWI_CR : (TWI Offset: 0x00) Control Register -------- */
#define TWI_CR_START (0x1u << 0) /**< \brief (TWI_CR) Send a START Condition */
#define TWI_CR_STOP (0x1u << 1) /**< \brief (TWI_CR) Send a STOP Condition */
#define TWI_CR_MSEN (0x1u << 2) /**< \brief (TWI_CR) TWI Master Mode Enabled */
#define TWI_CR_MSDIS (0x1u << 3) /**< \brief (TWI_CR) TWI Master Mode Disabled */
#define TWI_CR_SVEN (0x1u << 4) /**< \brief (TWI_CR) TWI Slave Mode Enabled */
#define TWI_CR_SVDIS (0x1u << 5) /**< \brief (TWI_CR) TWI Slave Mode Disabled */
#define TWI_CR_QUICK (0x1u << 6) /**< \brief (TWI_CR) SMBUS Quick Command */
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
/* -------- TWI_WPROT_MODE : (TWI Offset: 0xE4) Protection Mode Register -------- */
#define TWI_WPROT_MODE_WPROT (0x1u << 0) /**< \brief (TWI_WPROT_MODE) Write protection bit */
#define TWI_WPROT_MODE_SECURITY_CODE_Pos 8
#define TWI_WPROT_MODE_SECURITY_CODE_Msk (0xffffffu << TWI_WPROT_MODE_SECURITY_CODE_Pos) /**< \brief (TWI_WPROT_MODE) Write protection mode security code */
#define TWI_WPROT_MODE_SECURITY_CODE(value) ((TWI_WPROT_MODE_SECURITY_CODE_Msk & ((value) << TWI_WPROT_MODE_SECURITY_CODE_Pos)))
/* -------- TWI_WPROT_STATUS : (TWI Offset: 0xE8) Protection Status Register -------- */
#define TWI_WPROT_STATUS_WPROTERR (0x1u << 0) /**< \brief (TWI_WPROT_STATUS) Write Protection Error */
#define TWI_WPROT_STATUS_WPROTADDR_Pos 8
#define TWI_WPROT_STATUS_WPROTADDR_Msk (0xffffffu << TWI_WPROT_STATUS_WPROTADDR_Pos) /**< \brief (TWI_WPROT_STATUS) Write Protection Error Address */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Universal Asynchronous Receiver Transmitter */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_UART Universal Asynchronous Receiver Transmitter */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Uart hardware registers */
typedef struct {
  WoReg UART_CR;   /**< \brief (Uart Offset: 0x0000) Control Register */
  RwReg UART_MR;   /**< \brief (Uart Offset: 0x0004) Mode Register */
  WoReg UART_IER;  /**< \brief (Uart Offset: 0x0008) Interrupt Enable Register */
  WoReg UART_IDR;  /**< \brief (Uart Offset: 0x000C) Interrupt Disable Register */
  RoReg UART_IMR;  /**< \brief (Uart Offset: 0x0010) Interrupt Mask Register */
  RoReg UART_SR;   /**< \brief (Uart Offset: 0x0014) Status Register */
  RoReg UART_RHR;  /**< \brief (Uart Offset: 0x0018) Receive Holding Register */
  WoReg UART_THR;  /**< \brief (Uart Offset: 0x001C) Transmit Holding Register */
  RwReg UART_BRGR; /**< \brief (Uart Offset: 0x0020) Baud Rate Generator Register */
} Uart;
#endif /* __ASSEMBLY__ */
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
#define   UART_MR_PAR_EVEN (0x0u << 9) /**< \brief (UART_MR) Even parity */
#define   UART_MR_PAR_ODD (0x1u << 9) /**< \brief (UART_MR) Odd parity */
#define   UART_MR_PAR_SPACE (0x2u << 9) /**< \brief (UART_MR) Space: parity forced to 0 */
#define   UART_MR_PAR_MARK (0x3u << 9) /**< \brief (UART_MR) Mark: parity forced to 1 */
#define   UART_MR_PAR_NO (0x4u << 9) /**< \brief (UART_MR) No parity */
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
/** \addtogroup AT91SAMA5_USART Universal Synchronous Asynchronous Receiver Transmitter */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Usart hardware registers */
typedef struct {
  WoReg US_CR;         /**< \brief (Usart Offset: 0x0000) Control Register */
  RwReg US_MR;         /**< \brief (Usart Offset: 0x0004) Mode Register */
  WoReg US_IER;        /**< \brief (Usart Offset: 0x0008) Interrupt Enable Register */
  WoReg US_IDR;        /**< \brief (Usart Offset: 0x000C) Interrupt Disable Register */
  RoReg US_IMR;        /**< \brief (Usart Offset: 0x0010) Interrupt Mask Register */
  RoReg US_CSR;        /**< \brief (Usart Offset: 0x0014) Channel Status Register */
  RoReg US_RHR;        /**< \brief (Usart Offset: 0x0018) Receiver Holding Register */
  WoReg US_THR;        /**< \brief (Usart Offset: 0x001C) Transmitter Holding Register */
  RwReg US_BRGR;       /**< \brief (Usart Offset: 0x0020) Baud Rate Generator Register */
  RwReg US_RTOR;       /**< \brief (Usart Offset: 0x0024) Receiver Time-out Register */
  RwReg US_TTGR;       /**< \brief (Usart Offset: 0x0028) Transmitter Timeguard Register */
  RoReg Reserved1[5];
  RwReg US_FIDI;       /**< \brief (Usart Offset: 0x0040) FI DI Ratio Register */
  RoReg US_NER;        /**< \brief (Usart Offset: 0x0044) Number of Errors Register */
  RoReg Reserved2[1];
  RwReg US_IF;         /**< \brief (Usart Offset: 0x004C) IrDA Filter Register */
  RwReg US_MAN;        /**< \brief (Usart Offset: 0x0050) Manchester Encoder Decoder Register */
  RoReg Reserved3[36];
  RwReg US_WPMR;       /**< \brief (Usart Offset: 0xE4) Write Protect Mode Register */
  RoReg US_WPSR;       /**< \brief (Usart Offset: 0xE8) Write Protect Status Register */
} Usart;
#endif /* __ASSEMBLY__ */
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
#define US_CR_FCS (0x1u << 18) /**< \brief (US_CR) Force SPI Chip Select */
#define US_CR_RTSDIS (0x1u << 19) /**< \brief (US_CR) Request to Send Disable */
#define US_CR_RCS (0x1u << 19) /**< \brief (US_CR) Release SPI Chip Select */
/* -------- US_MR : (USART Offset: 0x0004) Mode Register -------- */
#define US_MR_USART_MODE_Pos 0
#define US_MR_USART_MODE_Msk (0xfu << US_MR_USART_MODE_Pos) /**< \brief (US_MR)  */
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
#define US_MR_CPHA (0x1u << 8) /**< \brief (US_MR) SPI Clock Phase */
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
#define US_MR_CPOL (0x1u << 16) /**< \brief (US_MR) SPI Clock Polarity */
#define US_MR_MODE9 (0x1u << 17) /**< \brief (US_MR) 9-bit Character Length */
#define US_MR_CLKO (0x1u << 18) /**< \brief (US_MR) Clock Output Select */
#define US_MR_OVER (0x1u << 19) /**< \brief (US_MR) Oversampling Mode */
#define US_MR_INACK (0x1u << 20) /**< \brief (US_MR) Inhibit Non Acknowledge */
#define US_MR_DSNACK (0x1u << 21) /**< \brief (US_MR) Disable Successive NACK */
#define US_MR_VAR_SYNC (0x1u << 22) /**< \brief (US_MR) Variable Synchronization of Command/Data Sync Start Frame Delimiter */
#define US_MR_INVDATA (0x1u << 23) /**< \brief (US_MR) INverted Data */
#define US_MR_MAX_ITERATION_Pos 24
#define US_MR_MAX_ITERATION_Msk (0x7u << US_MR_MAX_ITERATION_Pos) /**< \brief (US_MR)  */
#define US_MR_MAX_ITERATION(value) ((US_MR_MAX_ITERATION_Msk & ((value) << US_MR_MAX_ITERATION_Pos)))
#define US_MR_FILTER (0x1u << 28) /**< \brief (US_MR) Infrared Receive Line Filter */
#define US_MR_MAN (0x1u << 29) /**< \brief (US_MR) Manchester Encoder/Decoder Enable */
#define US_MR_MODSYNC (0x1u << 30) /**< \brief (US_MR) Manchester Synchronization Mode */
#define US_MR_ONEBIT (0x1u << 31) /**< \brief (US_MR) Start Frame Delimiter Selector */
/* -------- US_IER : (USART Offset: 0x0008) Interrupt Enable Register -------- */
#define US_IER_RXRDY (0x1u << 0) /**< \brief (US_IER) RXRDY Interrupt Enable */
#define US_IER_TXRDY (0x1u << 1) /**< \brief (US_IER) TXRDY Interrupt Enable */
#define US_IER_RXBRK (0x1u << 2) /**< \brief (US_IER) Receiver Break Interrupt Enable */
#define US_IER_OVRE (0x1u << 5) /**< \brief (US_IER) Overrun Error Interrupt Enable */
#define US_IER_FRAME (0x1u << 6) /**< \brief (US_IER) Framing Error Interrupt Enable */
#define US_IER_PARE (0x1u << 7) /**< \brief (US_IER) Parity Error Interrupt Enable */
#define US_IER_TIMEOUT (0x1u << 8) /**< \brief (US_IER) Time-out Interrupt Enable */
#define US_IER_TXEMPTY (0x1u << 9) /**< \brief (US_IER) TXEMPTY Interrupt Enable */
#define US_IER_ITER (0x1u << 10) /**< \brief (US_IER) Max number of Repetitions Reached */
#define US_IER_UNRE (0x1u << 10) /**< \brief (US_IER) SPI Underrun Error */
#define US_IER_NACK (0x1u << 13) /**< \brief (US_IER) Non AcknowledgeInterrupt Enable */
#define US_IER_CTSIC (0x1u << 19) /**< \brief (US_IER) Clear to Send Input Change Interrupt Enable */
#define US_IER_MANE (0x1u << 24) /**< \brief (US_IER) Manchester Error Interrupt Enable */
/* -------- US_IDR : (USART Offset: 0x000C) Interrupt Disable Register -------- */
#define US_IDR_RXRDY (0x1u << 0) /**< \brief (US_IDR) RXRDY Interrupt Disable */
#define US_IDR_TXRDY (0x1u << 1) /**< \brief (US_IDR) TXRDY Interrupt Disable */
#define US_IDR_RXBRK (0x1u << 2) /**< \brief (US_IDR) Receiver Break Interrupt Disable */
#define US_IDR_OVRE (0x1u << 5) /**< \brief (US_IDR) Overrun Error Interrupt Disable */
#define US_IDR_FRAME (0x1u << 6) /**< \brief (US_IDR) Framing Error Interrupt Disable */
#define US_IDR_PARE (0x1u << 7) /**< \brief (US_IDR) Parity Error Interrupt Disable */
#define US_IDR_TIMEOUT (0x1u << 8) /**< \brief (US_IDR) Time-out Interrupt Disable */
#define US_IDR_TXEMPTY (0x1u << 9) /**< \brief (US_IDR) TXEMPTY Interrupt Disable */
#define US_IDR_ITER (0x1u << 10) /**< \brief (US_IDR) Max number of Repetitions Reached Disable */
#define US_IDR_UNRE (0x1u << 10) /**< \brief (US_IDR) SPI Underrun Error Disable */
#define US_IDR_NACK (0x1u << 13) /**< \brief (US_IDR) Non AcknowledgeInterrupt Disable */
#define US_IDR_CTSIC (0x1u << 19) /**< \brief (US_IDR) Clear to Send Input Change Interrupt Disable */
#define US_IDR_MANE (0x1u << 24) /**< \brief (US_IDR) Manchester Error Interrupt Disable */
/* -------- US_IMR : (USART Offset: 0x0010) Interrupt Mask Register -------- */
#define US_IMR_RXRDY (0x1u << 0) /**< \brief (US_IMR) RXRDY Interrupt Mask */
#define US_IMR_TXRDY (0x1u << 1) /**< \brief (US_IMR) TXRDY Interrupt Mask */
#define US_IMR_RXBRK (0x1u << 2) /**< \brief (US_IMR) Receiver Break Interrupt Mask */
#define US_IMR_OVRE (0x1u << 5) /**< \brief (US_IMR) Overrun Error Interrupt Mask */
#define US_IMR_FRAME (0x1u << 6) /**< \brief (US_IMR) Framing Error Interrupt Mask */
#define US_IMR_PARE (0x1u << 7) /**< \brief (US_IMR) Parity Error Interrupt Mask */
#define US_IMR_TIMEOUT (0x1u << 8) /**< \brief (US_IMR) Time-out Interrupt Mask */
#define US_IMR_TXEMPTY (0x1u << 9) /**< \brief (US_IMR) TXEMPTY Interrupt Mask */
#define US_IMR_ITER (0x1u << 10) /**< \brief (US_IMR) Max number of Repetitions Reached Mask */
#define US_IMR_UNRE (0x1u << 10) /**< \brief (US_IMR) SPI Underrun Error Mask */
#define US_IMR_NACK (0x1u << 13) /**< \brief (US_IMR) Non AcknowledgeInterrupt Mask */
#define US_IMR_CTSIC (0x1u << 19) /**< \brief (US_IMR) Clear to Send Input Change Interrupt Mask */
#define US_IMR_MANE (0x1u << 24) /**< \brief (US_IMR) Manchester Error Interrupt Mask */
/* -------- US_CSR : (USART Offset: 0x0014) Channel Status Register -------- */
#define US_CSR_RXRDY (0x1u << 0) /**< \brief (US_CSR) Receiver Ready */
#define US_CSR_TXRDY (0x1u << 1) /**< \brief (US_CSR) Transmitter Ready */
#define US_CSR_RXBRK (0x1u << 2) /**< \brief (US_CSR) Break Received/End of Break */
#define US_CSR_OVRE (0x1u << 5) /**< \brief (US_CSR) Overrun Error */
#define US_CSR_FRAME (0x1u << 6) /**< \brief (US_CSR) Framing Error */
#define US_CSR_PARE (0x1u << 7) /**< \brief (US_CSR) Parity Error */
#define US_CSR_TIMEOUT (0x1u << 8) /**< \brief (US_CSR) Receiver Time-out */
#define US_CSR_TXEMPTY (0x1u << 9) /**< \brief (US_CSR) Transmitter Empty */
#define US_CSR_ITER (0x1u << 10) /**< \brief (US_CSR) Max number of Repetitions Reached */
#define US_CSR_UNRE (0x1u << 10) /**< \brief (US_CSR) SPI Underrun Error */
#define US_CSR_NACK (0x1u << 13) /**< \brief (US_CSR) Non AcknowledgeInterrupt */
#define US_CSR_CTSIC (0x1u << 19) /**< \brief (US_CSR) Clear to Send Input Change Flag */
#define US_CSR_CTS (0x1u << 23) /**< \brief (US_CSR) Image of CTS Input */
#define US_CSR_MANERR (0x1u << 24) /**< \brief (US_CSR) Manchester Error */
/* -------- US_RHR : (USART Offset: 0x0018) Receiver Holding Register -------- */
#define US_RHR_RXCHR_Pos 0
#define US_RHR_RXCHR_Msk (0x1ffu << US_RHR_RXCHR_Pos) /**< \brief (US_RHR) Received Character */
#define US_RHR_RXSYNH (0x1u << 15) /**< \brief (US_RHR) Received Sync */
/* -------- US_THR : (USART Offset: 0x001C) Transmitter Holding Register -------- */
#define US_THR_TXCHR_Pos 0
#define US_THR_TXCHR_Msk (0x1ffu << US_THR_TXCHR_Pos) /**< \brief (US_THR) Character to be Transmitted */
#define US_THR_TXCHR(value) ((US_THR_TXCHR_Msk & ((value) << US_THR_TXCHR_Pos)))
#define US_THR_TXSYNH (0x1u << 15) /**< \brief (US_THR) Sync Field to be transmitted */
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
#define US_FIDI_FI_DI_RATIO_Msk (0x7ffu << US_FIDI_FI_DI_RATIO_Pos) /**< \brief (US_FIDI) FI Over DI Ratio Value */
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
#define US_MAN_STUCKTO1 (0x1u << 29) /**< \brief (US_MAN)  */
#define US_MAN_DRIFT (0x1u << 30) /**< \brief (US_MAN) Drift compensation */
/* -------- US_WPMR : (USART Offset: 0xE4) Write Protect Mode Register -------- */
#define US_WPMR_WPEN (0x1u << 0) /**< \brief (US_WPMR) Write Protect Enable */
#define US_WPMR_WPKEY_Pos 8
#define US_WPMR_WPKEY_Msk (0xffffffu << US_WPMR_WPKEY_Pos) /**< \brief (US_WPMR) Write Protect KEY */
#define US_WPMR_WPKEY(value) ((US_WPMR_WPKEY_Msk & ((value) << US_WPMR_WPKEY_Pos)))
/* -------- US_WPSR : (USART Offset: 0xE8) Write Protect Status Register -------- */
#define US_WPSR_WPVS (0x1u << 0) /**< \brief (US_WPSR) Write Protect Violation Status */
#define US_WPSR_WPVSRC_Pos 8
#define US_WPSR_WPVSRC_Msk (0xffffu << US_WPSR_WPVSRC_Pos) /**< \brief (US_WPSR) Write Protect Violation Source */

/*@}*/

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Watchdog Timer */
/* ============================================================================= */
/** \addtogroup AT91SAMA5_WDT Watchdog Timer */
/*@{*/

#ifndef __ASSEMBLY__
/** \brief Wdt hardware registers */
typedef struct {
  WoReg WDT_CR; /**< \brief (Wdt Offset: 0x00) Control Register */
  RwReg WDT_MR; /**< \brief (Wdt Offset: 0x04) Mode Register */
  RoReg WDT_SR; /**< \brief (Wdt Offset: 0x08) Status Register */
} Wdt;
#endif /* __ASSEMBLY__ */
/* -------- WDT_CR : (WDT Offset: 0x00) Control Register -------- */
#define WDT_CR_WDRSTT (0x1u << 0) /**< \brief (WDT_CR) Watchdog Restart */
#define WDT_CR_KEY_Pos 24
#define WDT_CR_KEY_Msk (0xffu << WDT_CR_KEY_Pos) /**< \brief (WDT_CR) Password */
#define WDT_CR_KEY(value) ((WDT_CR_KEY_Msk & ((value) << WDT_CR_KEY_Pos)))
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

/*@}*/

/* ************************************************************************** */
/*   REGISTER ACCESS DEFINITIONS FOR AT91SAMA5 */
/* ************************************************************************** */
/** \addtogroup AT91SAMA5_reg Registers Access Definitions */
/*@{*/

/* ========== Register definition for AXIMX peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_AXIMX_REMAP                        (0x00800000U) /**< \brief (AXIMX) Remap Register */
#define REG_AXIMX_PERIPH_ID4                   (0x00801FD0U) /**< \brief (AXIMX) Peripheral ID Register 4 */
#define REG_AXIMX_PERIPH_ID5                   (0x00801FD4U) /**< \brief (AXIMX) Peripheral ID Register 5 */
#define REG_AXIMX_PERIPH_ID6                   (0x00801FD8U) /**< \brief (AXIMX) Peripheral ID Register 6 */
#define REG_AXIMX_PERIPH_ID7                   (0x00801FDCU) /**< \brief (AXIMX) Peripheral ID Register 7 */
#define REG_AXIMX_PERIPH_ID0                   (0x00801FE0U) /**< \brief (AXIMX) Peripheral ID Register 0 */
#define REG_AXIMX_PERIPH_ID1                   (0x00801FE4U) /**< \brief (AXIMX) Peripheral ID Register 1 */
#define REG_AXIMX_PERIPH_ID2                   (0x00801FE8U) /**< \brief (AXIMX) Peripheral ID Register 2 */
#define REG_AXIMX_PERIPH_ID3                   (0x00801FECU) /**< \brief (AXIMX) Peripheral ID Register 3 */
#define REG_AXIMX_COMP_ID                      (0x00801FF0U) /**< \brief (AXIMX) Component ID Register */
#define REG_AXIMX_AMIB3_FN_MOD_BM_ISS          (0x00805008U) /**< \brief (AXIMX) AMIB3 Bus Matrix Functionality Modification Register */
#define REG_AXIMX_AMIB3_FN_MOD2                (0x00805024U) /**< \brief (AXIMX) AMIB3 Bypass Merge */
#define REG_AXIMX_ASIB0_READ_QOS               (0x00842100U) /**< \brief (AXIMX) ASIB0 Read Channel QoS Register */
#define REG_AXIMX_ASIB0_WRITE_QOS              (0x00842104U) /**< \brief (AXIMX) ASIB0 Write Channel QoS Register */
#define REG_AXIMX_ASIB1_FN_MOD_AHB             (0x00843028U) /**< \brief (AXIMX) ASIB1 AHB Functionality Modification Register */
#define REG_AXIMX_ASIB1_READ_QOS               (0x00843100U) /**< \brief (AXIMX) ASIB1 Read Channel QoS Register */
#define REG_AXIMX_ASIB1_WRITE_QOS              (0x00843104U) /**< \brief (AXIMX) ASIB1 Write Channel QoS Register */
#define REG_AXIMX_ASIB1_FN_MOD                 (0x00843108U) /**< \brief (AXIMX) ASIB1 Issuing Functionality Modification Register */
#else
#define REG_AXIMX_REMAP               (*(WoReg*)0x00800000U) /**< \brief (AXIMX) Remap Register */
#define REG_AXIMX_PERIPH_ID4          (*(RoReg*)0x00801FD0U) /**< \brief (AXIMX) Peripheral ID Register 4 */
#define REG_AXIMX_PERIPH_ID5          (*(RoReg*)0x00801FD4U) /**< \brief (AXIMX) Peripheral ID Register 5 */
#define REG_AXIMX_PERIPH_ID6          (*(RoReg*)0x00801FD8U) /**< \brief (AXIMX) Peripheral ID Register 6 */
#define REG_AXIMX_PERIPH_ID7          (*(RoReg*)0x00801FDCU) /**< \brief (AXIMX) Peripheral ID Register 7 */
#define REG_AXIMX_PERIPH_ID0          (*(RoReg*)0x00801FE0U) /**< \brief (AXIMX) Peripheral ID Register 0 */
#define REG_AXIMX_PERIPH_ID1          (*(RoReg*)0x00801FE4U) /**< \brief (AXIMX) Peripheral ID Register 1 */
#define REG_AXIMX_PERIPH_ID2          (*(RoReg*)0x00801FE8U) /**< \brief (AXIMX) Peripheral ID Register 2 */
#define REG_AXIMX_PERIPH_ID3          (*(RoReg*)0x00801FECU) /**< \brief (AXIMX) Peripheral ID Register 3 */
#define REG_AXIMX_COMP_ID             (*(RoReg*)0x00801FF0U) /**< \brief (AXIMX) Component ID Register */
#define REG_AXIMX_AMIB3_FN_MOD_BM_ISS (*(RwReg*)0x00805008U) /**< \brief (AXIMX) AMIB3 Bus Matrix Functionality Modification Register */
#define REG_AXIMX_AMIB3_FN_MOD2       (*(RwReg*)0x00805024U) /**< \brief (AXIMX) AMIB3 Bypass Merge */
#define REG_AXIMX_ASIB0_READ_QOS      (*(RwReg*)0x00842100U) /**< \brief (AXIMX) ASIB0 Read Channel QoS Register */
#define REG_AXIMX_ASIB0_WRITE_QOS     (*(RwReg*)0x00842104U) /**< \brief (AXIMX) ASIB0 Write Channel QoS Register */
#define REG_AXIMX_ASIB1_FN_MOD_AHB    (*(RwReg*)0x00843028U) /**< \brief (AXIMX) ASIB1 AHB Functionality Modification Register */
#define REG_AXIMX_ASIB1_READ_QOS      (*(RwReg*)0x00843100U) /**< \brief (AXIMX) ASIB1 Read Channel QoS Register */
#define REG_AXIMX_ASIB1_WRITE_QOS     (*(RwReg*)0x00843104U) /**< \brief (AXIMX) ASIB1 Write Channel QoS Register */
#define REG_AXIMX_ASIB1_FN_MOD        (*(RwReg*)0x00843108U) /**< \brief (AXIMX) ASIB1 Issuing Functionality Modification Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for HSMCI0 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_HSMCI0_CR                          (0xF0000000U) /**< \brief (HSMCI0) Control Register */
#define REG_HSMCI0_MR                          (0xF0000004U) /**< \brief (HSMCI0) Mode Register */
#define REG_HSMCI0_DTOR                        (0xF0000008U) /**< \brief (HSMCI0) Data Timeout Register */
#define REG_HSMCI0_SDCR                        (0xF000000CU) /**< \brief (HSMCI0) SD/SDIO Card Register */
#define REG_HSMCI0_ARGR                        (0xF0000010U) /**< \brief (HSMCI0) Argument Register */
#define REG_HSMCI0_CMDR                        (0xF0000014U) /**< \brief (HSMCI0) Command Register */
#define REG_HSMCI0_BLKR                        (0xF0000018U) /**< \brief (HSMCI0) Block Register */
#define REG_HSMCI0_CSTOR                       (0xF000001CU) /**< \brief (HSMCI0) Completion Signal Timeout Register */
#define REG_HSMCI0_RSPR                        (0xF0000020U) /**< \brief (HSMCI0) Response Register */
#define REG_HSMCI0_RDR                         (0xF0000030U) /**< \brief (HSMCI0) Receive Data Register */
#define REG_HSMCI0_TDR                         (0xF0000034U) /**< \brief (HSMCI0) Transmit Data Register */
#define REG_HSMCI0_SR                          (0xF0000040U) /**< \brief (HSMCI0) Status Register */
#define REG_HSMCI0_IER                         (0xF0000044U) /**< \brief (HSMCI0) Interrupt Enable Register */
#define REG_HSMCI0_IDR                         (0xF0000048U) /**< \brief (HSMCI0) Interrupt Disable Register */
#define REG_HSMCI0_IMR                         (0xF000004CU) /**< \brief (HSMCI0) Interrupt Mask Register */
#define REG_HSMCI0_DMA                         (0xF0000050U) /**< \brief (HSMCI0) DMA Configuration Register */
#define REG_HSMCI0_CFG                         (0xF0000054U) /**< \brief (HSMCI0) Configuration Register */
#define REG_HSMCI0_WPMR                        (0xF00000E4U) /**< \brief (HSMCI0) Write Protection Mode Register */
#define REG_HSMCI0_WPSR                        (0xF00000E8U) /**< \brief (HSMCI0) Write Protection Status Register */
#define REG_HSMCI0_FIFO                        (0xF0000200U) /**< \brief (HSMCI0) FIFO Memory Aperture0 */
#else
#define REG_HSMCI0_CR                 (*(WoReg*)0xF0000000U) /**< \brief (HSMCI0) Control Register */
#define REG_HSMCI0_MR                 (*(RwReg*)0xF0000004U) /**< \brief (HSMCI0) Mode Register */
#define REG_HSMCI0_DTOR               (*(RwReg*)0xF0000008U) /**< \brief (HSMCI0) Data Timeout Register */
#define REG_HSMCI0_SDCR               (*(RwReg*)0xF000000CU) /**< \brief (HSMCI0) SD/SDIO Card Register */
#define REG_HSMCI0_ARGR               (*(RwReg*)0xF0000010U) /**< \brief (HSMCI0) Argument Register */
#define REG_HSMCI0_CMDR               (*(WoReg*)0xF0000014U) /**< \brief (HSMCI0) Command Register */
#define REG_HSMCI0_BLKR               (*(RwReg*)0xF0000018U) /**< \brief (HSMCI0) Block Register */
#define REG_HSMCI0_CSTOR              (*(RwReg*)0xF000001CU) /**< \brief (HSMCI0) Completion Signal Timeout Register */
#define REG_HSMCI0_RSPR               (*(RoReg*)0xF0000020U) /**< \brief (HSMCI0) Response Register */
#define REG_HSMCI0_RDR                (*(RoReg*)0xF0000030U) /**< \brief (HSMCI0) Receive Data Register */
#define REG_HSMCI0_TDR                (*(WoReg*)0xF0000034U) /**< \brief (HSMCI0) Transmit Data Register */
#define REG_HSMCI0_SR                 (*(RoReg*)0xF0000040U) /**< \brief (HSMCI0) Status Register */
#define REG_HSMCI0_IER                (*(WoReg*)0xF0000044U) /**< \brief (HSMCI0) Interrupt Enable Register */
#define REG_HSMCI0_IDR                (*(WoReg*)0xF0000048U) /**< \brief (HSMCI0) Interrupt Disable Register */
#define REG_HSMCI0_IMR                (*(RoReg*)0xF000004CU) /**< \brief (HSMCI0) Interrupt Mask Register */
#define REG_HSMCI0_DMA                (*(RwReg*)0xF0000050U) /**< \brief (HSMCI0) DMA Configuration Register */
#define REG_HSMCI0_CFG                (*(RwReg*)0xF0000054U) /**< \brief (HSMCI0) Configuration Register */
#define REG_HSMCI0_WPMR               (*(RwReg*)0xF00000E4U) /**< \brief (HSMCI0) Write Protection Mode Register */
#define REG_HSMCI0_WPSR               (*(RoReg*)0xF00000E8U) /**< \brief (HSMCI0) Write Protection Status Register */
#define REG_HSMCI0_FIFO               (*(RwReg*)0xF0000200U) /**< \brief (HSMCI0) FIFO Memory Aperture0 */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for SPI0 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_SPI0_CR                            (0xF0004000U) /**< \brief (SPI0) Control Register */
#define REG_SPI0_MR                            (0xF0004004U) /**< \brief (SPI0) Mode Register */
#define REG_SPI0_RDR                           (0xF0004008U) /**< \brief (SPI0) Receive Data Register */
#define REG_SPI0_TDR                           (0xF000400CU) /**< \brief (SPI0) Transmit Data Register */
#define REG_SPI0_SR                            (0xF0004010U) /**< \brief (SPI0) Status Register */
#define REG_SPI0_IER                           (0xF0004014U) /**< \brief (SPI0) Interrupt Enable Register */
#define REG_SPI0_IDR                           (0xF0004018U) /**< \brief (SPI0) Interrupt Disable Register */
#define REG_SPI0_IMR                           (0xF000401CU) /**< \brief (SPI0) Interrupt Mask Register */
#define REG_SPI0_CSR                           (0xF0004030U) /**< \brief (SPI0) Chip Select Register */
#define REG_SPI0_WPMR                          (0xF00040E4U) /**< \brief (SPI0) Write Protection Control Register */
#define REG_SPI0_WPSR                          (0xF00040E8U) /**< \brief (SPI0) Write Protection Status Register */
#else
#define REG_SPI0_CR                   (*(WoReg*)0xF0004000U) /**< \brief (SPI0) Control Register */
#define REG_SPI0_MR                   (*(RwReg*)0xF0004004U) /**< \brief (SPI0) Mode Register */
#define REG_SPI0_RDR                  (*(RoReg*)0xF0004008U) /**< \brief (SPI0) Receive Data Register */
#define REG_SPI0_TDR                  (*(WoReg*)0xF000400CU) /**< \brief (SPI0) Transmit Data Register */
#define REG_SPI0_SR                   (*(RoReg*)0xF0004010U) /**< \brief (SPI0) Status Register */
#define REG_SPI0_IER                  (*(WoReg*)0xF0004014U) /**< \brief (SPI0) Interrupt Enable Register */
#define REG_SPI0_IDR                  (*(WoReg*)0xF0004018U) /**< \brief (SPI0) Interrupt Disable Register */
#define REG_SPI0_IMR                  (*(RoReg*)0xF000401CU) /**< \brief (SPI0) Interrupt Mask Register */
#define REG_SPI0_CSR                  (*(RwReg*)0xF0004030U) /**< \brief (SPI0) Chip Select Register */
#define REG_SPI0_WPMR                 (*(RwReg*)0xF00040E4U) /**< \brief (SPI0) Write Protection Control Register */
#define REG_SPI0_WPSR                 (*(RoReg*)0xF00040E8U) /**< \brief (SPI0) Write Protection Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for SSC0 peripheral ========== */

/* ========== Register definition for TC0 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_TC0_CCR0                           (0xF0010000U) /**< \brief (TC0) Channel Control Register (channel = 0) */
#define REG_TC0_CMR0                           (0xF0010004U) /**< \brief (TC0) Channel Mode Register (channel = 0) */
#define REG_TC0_SMMR0                          (0xF0010008U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 0) */
#define REG_TC0_RAB0                           (0xF001000CU) /**< \brief (TC0) Register AB (channel = 0) */
#define REG_TC0_CV0                            (0xF0010010U) /**< \brief (TC0) Counter Value (channel = 0) */
#define REG_TC0_RA0                            (0xF0010014U) /**< \brief (TC0) Register A (channel = 0) */
#define REG_TC0_RB0                            (0xF0010018U) /**< \brief (TC0) Register B (channel = 0) */
#define REG_TC0_RC0                            (0xF001001CU) /**< \brief (TC0) Register C (channel = 0) */
#define REG_TC0_SR0                            (0xF0010020U) /**< \brief (TC0) Status Register (channel = 0) */
#define REG_TC0_IER0                           (0xF0010024U) /**< \brief (TC0) Interrupt Enable Register (channel = 0) */
#define REG_TC0_IDR0                           (0xF0010028U) /**< \brief (TC0) Interrupt Disable Register (channel = 0) */
#define REG_TC0_IMR0                           (0xF001002CU) /**< \brief (TC0) Interrupt Mask Register (channel = 0) */
#define REG_TC0_CCR1                           (0xF0010040U) /**< \brief (TC0) Channel Control Register (channel = 1) */
#define REG_TC0_CMR1                           (0xF0010044U) /**< \brief (TC0) Channel Mode Register (channel = 1) */
#define REG_TC0_SMMR1                          (0xF0010048U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 1) */
#define REG_TC0_RAB1                           (0xF001004CU) /**< \brief (TC0) Register AB (channel = 1) */
#define REG_TC0_CV1                            (0xF0010050U) /**< \brief (TC0) Counter Value (channel = 1) */
#define REG_TC0_RA1                            (0xF0010054U) /**< \brief (TC0) Register A (channel = 1) */
#define REG_TC0_RB1                            (0xF0010058U) /**< \brief (TC0) Register B (channel = 1) */
#define REG_TC0_RC1                            (0xF001005CU) /**< \brief (TC0) Register C (channel = 1) */
#define REG_TC0_SR1                            (0xF0010060U) /**< \brief (TC0) Status Register (channel = 1) */
#define REG_TC0_IER1                           (0xF0010064U) /**< \brief (TC0) Interrupt Enable Register (channel = 1) */
#define REG_TC0_IDR1                           (0xF0010068U) /**< \brief (TC0) Interrupt Disable Register (channel = 1) */
#define REG_TC0_IMR1                           (0xF001006CU) /**< \brief (TC0) Interrupt Mask Register (channel = 1) */
#define REG_TC0_CCR2                           (0xF0010080U) /**< \brief (TC0) Channel Control Register (channel = 2) */
#define REG_TC0_CMR2                           (0xF0010084U) /**< \brief (TC0) Channel Mode Register (channel = 2) */
#define REG_TC0_SMMR2                          (0xF0010088U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 2) */
#define REG_TC0_RAB2                           (0xF001008CU) /**< \brief (TC0) Register AB (channel = 2) */
#define REG_TC0_CV2                            (0xF0010090U) /**< \brief (TC0) Counter Value (channel = 2) */
#define REG_TC0_RA2                            (0xF0010094U) /**< \brief (TC0) Register A (channel = 2) */
#define REG_TC0_RB2                            (0xF0010098U) /**< \brief (TC0) Register B (channel = 2) */
#define REG_TC0_RC2                            (0xF001009CU) /**< \brief (TC0) Register C (channel = 2) */
#define REG_TC0_SR2                            (0xF00100A0U) /**< \brief (TC0) Status Register (channel = 2) */
#define REG_TC0_IER2                           (0xF00100A4U) /**< \brief (TC0) Interrupt Enable Register (channel = 2) */
#define REG_TC0_IDR2                           (0xF00100A8U) /**< \brief (TC0) Interrupt Disable Register (channel = 2) */
#define REG_TC0_IMR2                           (0xF00100ACU) /**< \brief (TC0) Interrupt Mask Register (channel = 2) */
#define REG_TC0_BCR                            (0xF00100C0U) /**< \brief (TC0) Block Control Register */
#define REG_TC0_BMR                            (0xF00100C4U) /**< \brief (TC0) Block Mode Register */
#define REG_TC0_WPMR                           (0xF00100E4U) /**< \brief (TC0) Write Protect Mode Register */
#else
#define REG_TC0_CCR0                  (*(WoReg*)0xF0010000U) /**< \brief (TC0) Channel Control Register (channel = 0) */
#define REG_TC0_CMR0                  (*(RwReg*)0xF0010004U) /**< \brief (TC0) Channel Mode Register (channel = 0) */
#define REG_TC0_SMMR0                 (*(RwReg*)0xF0010008U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 0) */
#define REG_TC0_RAB0                  (*(RoReg*)0xF001000CU) /**< \brief (TC0) Register AB (channel = 0) */
#define REG_TC0_CV0                   (*(RoReg*)0xF0010010U) /**< \brief (TC0) Counter Value (channel = 0) */
#define REG_TC0_RA0                   (*(RwReg*)0xF0010014U) /**< \brief (TC0) Register A (channel = 0) */
#define REG_TC0_RB0                   (*(RwReg*)0xF0010018U) /**< \brief (TC0) Register B (channel = 0) */
#define REG_TC0_RC0                   (*(RwReg*)0xF001001CU) /**< \brief (TC0) Register C (channel = 0) */
#define REG_TC0_SR0                   (*(RoReg*)0xF0010020U) /**< \brief (TC0) Status Register (channel = 0) */
#define REG_TC0_IER0                  (*(WoReg*)0xF0010024U) /**< \brief (TC0) Interrupt Enable Register (channel = 0) */
#define REG_TC0_IDR0                  (*(WoReg*)0xF0010028U) /**< \brief (TC0) Interrupt Disable Register (channel = 0) */
#define REG_TC0_IMR0                  (*(RoReg*)0xF001002CU) /**< \brief (TC0) Interrupt Mask Register (channel = 0) */
#define REG_TC0_CCR1                  (*(WoReg*)0xF0010040U) /**< \brief (TC0) Channel Control Register (channel = 1) */
#define REG_TC0_CMR1                  (*(RwReg*)0xF0010044U) /**< \brief (TC0) Channel Mode Register (channel = 1) */
#define REG_TC0_SMMR1                 (*(RwReg*)0xF0010048U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 1) */
#define REG_TC0_RAB1                  (*(RoReg*)0xF001004CU) /**< \brief (TC0) Register AB (channel = 1) */
#define REG_TC0_CV1                   (*(RoReg*)0xF0010050U) /**< \brief (TC0) Counter Value (channel = 1) */
#define REG_TC0_RA1                   (*(RwReg*)0xF0010054U) /**< \brief (TC0) Register A (channel = 1) */
#define REG_TC0_RB1                   (*(RwReg*)0xF0010058U) /**< \brief (TC0) Register B (channel = 1) */
#define REG_TC0_RC1                   (*(RwReg*)0xF001005CU) /**< \brief (TC0) Register C (channel = 1) */
#define REG_TC0_SR1                   (*(RoReg*)0xF0010060U) /**< \brief (TC0) Status Register (channel = 1) */
#define REG_TC0_IER1                  (*(WoReg*)0xF0010064U) /**< \brief (TC0) Interrupt Enable Register (channel = 1) */
#define REG_TC0_IDR1                  (*(WoReg*)0xF0010068U) /**< \brief (TC0) Interrupt Disable Register (channel = 1) */
#define REG_TC0_IMR1                  (*(RoReg*)0xF001006CU) /**< \brief (TC0) Interrupt Mask Register (channel = 1) */
#define REG_TC0_CCR2                  (*(WoReg*)0xF0010080U) /**< \brief (TC0) Channel Control Register (channel = 2) */
#define REG_TC0_CMR2                  (*(RwReg*)0xF0010084U) /**< \brief (TC0) Channel Mode Register (channel = 2) */
#define REG_TC0_SMMR2                 (*(RwReg*)0xF0010088U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 2) */
#define REG_TC0_RAB2                  (*(RoReg*)0xF001008CU) /**< \brief (TC0) Register AB (channel = 2) */
#define REG_TC0_CV2                   (*(RoReg*)0xF0010090U) /**< \brief (TC0) Counter Value (channel = 2) */
#define REG_TC0_RA2                   (*(RwReg*)0xF0010094U) /**< \brief (TC0) Register A (channel = 2) */
#define REG_TC0_RB2                   (*(RwReg*)0xF0010098U) /**< \brief (TC0) Register B (channel = 2) */
#define REG_TC0_RC2                   (*(RwReg*)0xF001009CU) /**< \brief (TC0) Register C (channel = 2) */
#define REG_TC0_SR2                   (*(RoReg*)0xF00100A0U) /**< \brief (TC0) Status Register (channel = 2) */
#define REG_TC0_IER2                  (*(WoReg*)0xF00100A4U) /**< \brief (TC0) Interrupt Enable Register (channel = 2) */
#define REG_TC0_IDR2                  (*(WoReg*)0xF00100A8U) /**< \brief (TC0) Interrupt Disable Register (channel = 2) */
#define REG_TC0_IMR2                  (*(RoReg*)0xF00100ACU) /**< \brief (TC0) Interrupt Mask Register (channel = 2) */
#define REG_TC0_BCR                   (*(WoReg*)0xF00100C0U) /**< \brief (TC0) Block Control Register */
#define REG_TC0_BMR                   (*(RwReg*)0xF00100C4U) /**< \brief (TC0) Block Mode Register */
#define REG_TC0_WPMR                  (*(RwReg*)0xF00100E4U) /**< \brief (TC0) Write Protect Mode Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for TWI0 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_TWI0_CR                            (0xF0014000U) /**< \brief (TWI0) Control Register */
#define REG_TWI0_MMR                           (0xF0014004U) /**< \brief (TWI0) Master Mode Register */
#define REG_TWI0_SMR                           (0xF0014008U) /**< \brief (TWI0) Slave Mode Register */
#define REG_TWI0_IADR                          (0xF001400CU) /**< \brief (TWI0) Internal Address Register */
#define REG_TWI0_CWGR                          (0xF0014010U) /**< \brief (TWI0) Clock Waveform Generator Register */
#define REG_TWI0_SR                            (0xF0014020U) /**< \brief (TWI0) Status Register */
#define REG_TWI0_IER                           (0xF0014024U) /**< \brief (TWI0) Interrupt Enable Register */
#define REG_TWI0_IDR                           (0xF0014028U) /**< \brief (TWI0) Interrupt Disable Register */
#define REG_TWI0_IMR                           (0xF001402CU) /**< \brief (TWI0) Interrupt Mask Register */
#define REG_TWI0_RHR                           (0xF0014030U) /**< \brief (TWI0) Receive Holding Register */
#define REG_TWI0_THR                           (0xF0014034U) /**< \brief (TWI0) Transmit Holding Register */
#define REG_TWI0_WPROT_MODE                    (0xF00140E4U) /**< \brief (TWI0) Protection Mode Register */
#define REG_TWI0_WPROT_STATUS                  (0xF00140E8U) /**< \brief (TWI0) Protection Status Register */
#else
#define REG_TWI0_CR                   (*(WoReg*)0xF0014000U) /**< \brief (TWI0) Control Register */
#define REG_TWI0_MMR                  (*(RwReg*)0xF0014004U) /**< \brief (TWI0) Master Mode Register */
#define REG_TWI0_SMR                  (*(RwReg*)0xF0014008U) /**< \brief (TWI0) Slave Mode Register */
#define REG_TWI0_IADR                 (*(RwReg*)0xF001400CU) /**< \brief (TWI0) Internal Address Register */
#define REG_TWI0_CWGR                 (*(RwReg*)0xF0014010U) /**< \brief (TWI0) Clock Waveform Generator Register */
#define REG_TWI0_SR                   (*(RoReg*)0xF0014020U) /**< \brief (TWI0) Status Register */
#define REG_TWI0_IER                  (*(WoReg*)0xF0014024U) /**< \brief (TWI0) Interrupt Enable Register */
#define REG_TWI0_IDR                  (*(WoReg*)0xF0014028U) /**< \brief (TWI0) Interrupt Disable Register */
#define REG_TWI0_IMR                  (*(RoReg*)0xF001402CU) /**< \brief (TWI0) Interrupt Mask Register */
#define REG_TWI0_RHR                  (*(RoReg*)0xF0014030U) /**< \brief (TWI0) Receive Holding Register */
#define REG_TWI0_THR                  (*(WoReg*)0xF0014034U) /**< \brief (TWI0) Transmit Holding Register */
#define REG_TWI0_WPROT_MODE           (*(RwReg*)0xF00140E4U) /**< \brief (TWI0) Protection Mode Register */
#define REG_TWI0_WPROT_STATUS         (*(RoReg*)0xF00140E8U) /**< \brief (TWI0) Protection Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for TWI1 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_TWI1_CR                            (0xF0018000U) /**< \brief (TWI1) Control Register */
#define REG_TWI1_MMR                           (0xF0018004U) /**< \brief (TWI1) Master Mode Register */
#define REG_TWI1_SMR                           (0xF0018008U) /**< \brief (TWI1) Slave Mode Register */
#define REG_TWI1_IADR                          (0xF001800CU) /**< \brief (TWI1) Internal Address Register */
#define REG_TWI1_CWGR                          (0xF0018010U) /**< \brief (TWI1) Clock Waveform Generator Register */
#define REG_TWI1_SR                            (0xF0018020U) /**< \brief (TWI1) Status Register */
#define REG_TWI1_IER                           (0xF0018024U) /**< \brief (TWI1) Interrupt Enable Register */
#define REG_TWI1_IDR                           (0xF0018028U) /**< \brief (TWI1) Interrupt Disable Register */
#define REG_TWI1_IMR                           (0xF001802CU) /**< \brief (TWI1) Interrupt Mask Register */
#define REG_TWI1_RHR                           (0xF0018030U) /**< \brief (TWI1) Receive Holding Register */
#define REG_TWI1_THR                           (0xF0018034U) /**< \brief (TWI1) Transmit Holding Register */
#define REG_TWI1_WPROT_MODE                    (0xF00180E4U) /**< \brief (TWI1) Protection Mode Register */
#define REG_TWI1_WPROT_STATUS                  (0xF00180E8U) /**< \brief (TWI1) Protection Status Register */
#else
#define REG_TWI1_CR                   (*(WoReg*)0xF0018000U) /**< \brief (TWI1) Control Register */
#define REG_TWI1_MMR                  (*(RwReg*)0xF0018004U) /**< \brief (TWI1) Master Mode Register */
#define REG_TWI1_SMR                  (*(RwReg*)0xF0018008U) /**< \brief (TWI1) Slave Mode Register */
#define REG_TWI1_IADR                 (*(RwReg*)0xF001800CU) /**< \brief (TWI1) Internal Address Register */
#define REG_TWI1_CWGR                 (*(RwReg*)0xF0018010U) /**< \brief (TWI1) Clock Waveform Generator Register */
#define REG_TWI1_SR                   (*(RoReg*)0xF0018020U) /**< \brief (TWI1) Status Register */
#define REG_TWI1_IER                  (*(WoReg*)0xF0018024U) /**< \brief (TWI1) Interrupt Enable Register */
#define REG_TWI1_IDR                  (*(WoReg*)0xF0018028U) /**< \brief (TWI1) Interrupt Disable Register */
#define REG_TWI1_IMR                  (*(RoReg*)0xF001802CU) /**< \brief (TWI1) Interrupt Mask Register */
#define REG_TWI1_RHR                  (*(RoReg*)0xF0018030U) /**< \brief (TWI1) Receive Holding Register */
#define REG_TWI1_THR                  (*(WoReg*)0xF0018034U) /**< \brief (TWI1) Transmit Holding Register */
#define REG_TWI1_WPROT_MODE           (*(RwReg*)0xF00180E4U) /**< \brief (TWI1) Protection Mode Register */
#define REG_TWI1_WPROT_STATUS         (*(RoReg*)0xF00180E8U) /**< \brief (TWI1) Protection Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for USART0 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_USART0_CR                          (0xF001C000U) /**< \brief (USART0) Control Register */
#define REG_USART0_MR                          (0xF001C004U) /**< \brief (USART0) Mode Register */
#define REG_USART0_IER                         (0xF001C008U) /**< \brief (USART0) Interrupt Enable Register */
#define REG_USART0_IDR                         (0xF001C00CU) /**< \brief (USART0) Interrupt Disable Register */
#define REG_USART0_IMR                         (0xF001C010U) /**< \brief (USART0) Interrupt Mask Register */
#define REG_USART0_CSR                         (0xF001C014U) /**< \brief (USART0) Channel Status Register */
#define REG_USART0_RHR                         (0xF001C018U) /**< \brief (USART0) Receiver Holding Register */
#define REG_USART0_THR                         (0xF001C01CU) /**< \brief (USART0) Transmitter Holding Register */
#define REG_USART0_BRGR                        (0xF001C020U) /**< \brief (USART0) Baud Rate Generator Register */
#define REG_USART0_RTOR                        (0xF001C024U) /**< \brief (USART0) Receiver Time-out Register */
#define REG_USART0_TTGR                        (0xF001C028U) /**< \brief (USART0) Transmitter Timeguard Register */
#define REG_USART0_FIDI                        (0xF001C040U) /**< \brief (USART0) FI DI Ratio Register */
#define REG_USART0_NER                         (0xF001C044U) /**< \brief (USART0) Number of Errors Register */
#define REG_USART0_IF                          (0xF001C04CU) /**< \brief (USART0) IrDA Filter Register */
#define REG_USART0_MAN                         (0xF001C050U) /**< \brief (USART0) Manchester Encoder Decoder Register */
#define REG_USART0_WPMR                        (0xF001C0E4U) /**< \brief (USART0) Write Protect Mode Register */
#define REG_USART0_WPSR                        (0xF001C0E8U) /**< \brief (USART0) Write Protect Status Register */
#else
#define REG_USART0_CR                 (*(WoReg*)0xF001C000U) /**< \brief (USART0) Control Register */
#define REG_USART0_MR                 (*(RwReg*)0xF001C004U) /**< \brief (USART0) Mode Register */
#define REG_USART0_IER                (*(WoReg*)0xF001C008U) /**< \brief (USART0) Interrupt Enable Register */
#define REG_USART0_IDR                (*(WoReg*)0xF001C00CU) /**< \brief (USART0) Interrupt Disable Register */
#define REG_USART0_IMR                (*(RoReg*)0xF001C010U) /**< \brief (USART0) Interrupt Mask Register */
#define REG_USART0_CSR                (*(RoReg*)0xF001C014U) /**< \brief (USART0) Channel Status Register */
#define REG_USART0_RHR                (*(RoReg*)0xF001C018U) /**< \brief (USART0) Receiver Holding Register */
#define REG_USART0_THR                (*(WoReg*)0xF001C01CU) /**< \brief (USART0) Transmitter Holding Register */
#define REG_USART0_BRGR               (*(RwReg*)0xF001C020U) /**< \brief (USART0) Baud Rate Generator Register */
#define REG_USART0_RTOR               (*(RwReg*)0xF001C024U) /**< \brief (USART0) Receiver Time-out Register */
#define REG_USART0_TTGR               (*(RwReg*)0xF001C028U) /**< \brief (USART0) Transmitter Timeguard Register */
#define REG_USART0_FIDI               (*(RwReg*)0xF001C040U) /**< \brief (USART0) FI DI Ratio Register */
#define REG_USART0_NER                (*(RoReg*)0xF001C044U) /**< \brief (USART0) Number of Errors Register */
#define REG_USART0_IF                 (*(RwReg*)0xF001C04CU) /**< \brief (USART0) IrDA Filter Register */
#define REG_USART0_MAN                (*(RwReg*)0xF001C050U) /**< \brief (USART0) Manchester Encoder Decoder Register */
#define REG_USART0_WPMR               (*(RwReg*)0xF001C0E4U) /**< \brief (USART0) Write Protect Mode Register */
#define REG_USART0_WPSR               (*(RoReg*)0xF001C0E8U) /**< \brief (USART0) Write Protect Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for USART1 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_USART1_CR                          (0xF0020000U) /**< \brief (USART1) Control Register */
#define REG_USART1_MR                          (0xF0020004U) /**< \brief (USART1) Mode Register */
#define REG_USART1_IER                         (0xF0020008U) /**< \brief (USART1) Interrupt Enable Register */
#define REG_USART1_IDR                         (0xF002000CU) /**< \brief (USART1) Interrupt Disable Register */
#define REG_USART1_IMR                         (0xF0020010U) /**< \brief (USART1) Interrupt Mask Register */
#define REG_USART1_CSR                         (0xF0020014U) /**< \brief (USART1) Channel Status Register */
#define REG_USART1_RHR                         (0xF0020018U) /**< \brief (USART1) Receiver Holding Register */
#define REG_USART1_THR                         (0xF002001CU) /**< \brief (USART1) Transmitter Holding Register */
#define REG_USART1_BRGR                        (0xF0020020U) /**< \brief (USART1) Baud Rate Generator Register */
#define REG_USART1_RTOR                        (0xF0020024U) /**< \brief (USART1) Receiver Time-out Register */
#define REG_USART1_TTGR                        (0xF0020028U) /**< \brief (USART1) Transmitter Timeguard Register */
#define REG_USART1_FIDI                        (0xF0020040U) /**< \brief (USART1) FI DI Ratio Register */
#define REG_USART1_NER                         (0xF0020044U) /**< \brief (USART1) Number of Errors Register */
#define REG_USART1_IF                          (0xF002004CU) /**< \brief (USART1) IrDA Filter Register */
#define REG_USART1_MAN                         (0xF0020050U) /**< \brief (USART1) Manchester Encoder Decoder Register */
#define REG_USART1_WPMR                        (0xF00200E4U) /**< \brief (USART1) Write Protect Mode Register */
#define REG_USART1_WPSR                        (0xF00200E8U) /**< \brief (USART1) Write Protect Status Register */
#else
#define REG_USART1_CR                 (*(WoReg*)0xF0020000U) /**< \brief (USART1) Control Register */
#define REG_USART1_MR                 (*(RwReg*)0xF0020004U) /**< \brief (USART1) Mode Register */
#define REG_USART1_IER                (*(WoReg*)0xF0020008U) /**< \brief (USART1) Interrupt Enable Register */
#define REG_USART1_IDR                (*(WoReg*)0xF002000CU) /**< \brief (USART1) Interrupt Disable Register */
#define REG_USART1_IMR                (*(RoReg*)0xF0020010U) /**< \brief (USART1) Interrupt Mask Register */
#define REG_USART1_CSR                (*(RoReg*)0xF0020014U) /**< \brief (USART1) Channel Status Register */
#define REG_USART1_RHR                (*(RoReg*)0xF0020018U) /**< \brief (USART1) Receiver Holding Register */
#define REG_USART1_THR                (*(WoReg*)0xF002001CU) /**< \brief (USART1) Transmitter Holding Register */
#define REG_USART1_BRGR               (*(RwReg*)0xF0020020U) /**< \brief (USART1) Baud Rate Generator Register */
#define REG_USART1_RTOR               (*(RwReg*)0xF0020024U) /**< \brief (USART1) Receiver Time-out Register */
#define REG_USART1_TTGR               (*(RwReg*)0xF0020028U) /**< \brief (USART1) Transmitter Timeguard Register */
#define REG_USART1_FIDI               (*(RwReg*)0xF0020040U) /**< \brief (USART1) FI DI Ratio Register */
#define REG_USART1_NER                (*(RoReg*)0xF0020044U) /**< \brief (USART1) Number of Errors Register */
#define REG_USART1_IF                 (*(RwReg*)0xF002004CU) /**< \brief (USART1) IrDA Filter Register */
#define REG_USART1_MAN                (*(RwReg*)0xF0020050U) /**< \brief (USART1) Manchester Encoder Decoder Register */
#define REG_USART1_WPMR               (*(RwReg*)0xF00200E4U) /**< \brief (USART1) Write Protect Mode Register */
#define REG_USART1_WPSR               (*(RoReg*)0xF00200E8U) /**< \brief (USART1) Write Protect Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for UART0 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_UART0_CR                           (0xF0024000U) /**< \brief (UART0) Control Register */
#define REG_UART0_MR                           (0xF0024004U) /**< \brief (UART0) Mode Register */
#define REG_UART0_IER                          (0xF0024008U) /**< \brief (UART0) Interrupt Enable Register */
#define REG_UART0_IDR                          (0xF002400CU) /**< \brief (UART0) Interrupt Disable Register */
#define REG_UART0_IMR                          (0xF0024010U) /**< \brief (UART0) Interrupt Mask Register */
#define REG_UART0_SR                           (0xF0024014U) /**< \brief (UART0) Status Register */
#define REG_UART0_RHR                          (0xF0024018U) /**< \brief (UART0) Receive Holding Register */
#define REG_UART0_THR                          (0xF002401CU) /**< \brief (UART0) Transmit Holding Register */
#define REG_UART0_BRGR                         (0xF0024020U) /**< \brief (UART0) Baud Rate Generator Register */
#else
#define REG_UART0_CR                  (*(WoReg*)0xF0024000U) /**< \brief (UART0) Control Register */
#define REG_UART0_MR                  (*(RwReg*)0xF0024004U) /**< \brief (UART0) Mode Register */
#define REG_UART0_IER                 (*(WoReg*)0xF0024008U) /**< \brief (UART0) Interrupt Enable Register */
#define REG_UART0_IDR                 (*(WoReg*)0xF002400CU) /**< \brief (UART0) Interrupt Disable Register */
#define REG_UART0_IMR                 (*(RoReg*)0xF0024010U) /**< \brief (UART0) Interrupt Mask Register */
#define REG_UART0_SR                  (*(RoReg*)0xF0024014U) /**< \brief (UART0) Status Register */
#define REG_UART0_RHR                 (*(RoReg*)0xF0024018U) /**< \brief (UART0) Receive Holding Register */
#define REG_UART0_THR                 (*(WoReg*)0xF002401CU) /**< \brief (UART0) Transmit Holding Register */
#define REG_UART0_BRGR                (*(RwReg*)0xF0024020U) /**< \brief (UART0) Baud Rate Generator Register */
#endif /* __ASSEMBLY__ */

/* ========== Register definition for SFR peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_SFR_OHCIICR                        (0xF0038010U) /**< \brief (SFR) OHCI Interrupt Configuration Register */
#define REG_SFR_OHCIISR                        (0xF0038014U) /**< \brief (SFR) OHCI Interrupt Status Register */
#define REG_SFR_AHB                            (0xF0038020U) /**< \brief (SFR) AHB Configuration Register */
#define REG_SFR_BRIDGE                         (0xF0038024U) /**< \brief (SFR) Bridge Configuration Register */
#define REG_SFR_SECURE                         (0xF0038028U) /**< \brief (SFR) Security Configuration Register */
#define REG_SFR_UTMICKTRIM                     (0xF0038030U) /**< \brief (SFR) UTMI Clock Trimming Register */
#define REG_SFR_UTMIHSTRIM                     (0xF0038034U) /**< \brief (SFR) UTMI High Speed Trimming Register */
#define REG_SFR_UTMIFSTRIM                     (0xF0038038U) /**< \brief (SFR) UTMI Full Speed Trimming Register */
#define REG_SFR_UTMISWAP                       (0xF003803CU) /**< \brief (SFR) UTMI DP/DM Pin Swapping Register */
#define REG_SFR_EBICFG                         (0xF0038040U) /**< \brief (SFR) EBI Configuration Register */
#else
#define REG_SFR_OHCIICR               (*(RwReg*)0xF0038010U) /**< \brief (SFR) OHCI Interrupt Configuration Register */
#define REG_SFR_OHCIISR               (*(RoReg*)0xF0038014U) /**< \brief (SFR) OHCI Interrupt Status Register */
#define REG_SFR_AHB                   (*(RwReg*)0xF0038020U) /**< \brief (SFR) AHB Configuration Register */
#define REG_SFR_BRIDGE                (*(RwReg*)0xF0038024U) /**< \brief (SFR) Bridge Configuration Register */
#define REG_SFR_SECURE                (*(RwReg*)0xF0038028U) /**< \brief (SFR) Security Configuration Register */
#define REG_SFR_UTMICKTRIM            (*(RwReg*)0xF0038030U) /**< \brief (SFR) UTMI Clock Trimming Register */
#define REG_SFR_UTMIHSTRIM            (*(RwReg*)0xF0038034U) /**< \brief (SFR) UTMI High Speed Trimming Register */
#define REG_SFR_UTMIFSTRIM            (*(RwReg*)0xF0038038U) /**< \brief (SFR) UTMI Full Speed Trimming Register */
#define REG_SFR_UTMISWAP              (*(RwReg*)0xF003803CU) /**< \brief (SFR) UTMI DP/DM Pin Swapping Register */
#define REG_SFR_EBICFG                (*(RwReg*)0xF0038040U) /**< \brief (SFR) EBI Configuration Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for HSMCI1 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_HSMCI1_CR                          (0xF8000000U) /**< \brief (HSMCI1) Control Register */
#define REG_HSMCI1_MR                          (0xF8000004U) /**< \brief (HSMCI1) Mode Register */
#define REG_HSMCI1_DTOR                        (0xF8000008U) /**< \brief (HSMCI1) Data Timeout Register */
#define REG_HSMCI1_SDCR                        (0xF800000CU) /**< \brief (HSMCI1) SD/SDIO Card Register */
#define REG_HSMCI1_ARGR                        (0xF8000010U) /**< \brief (HSMCI1) Argument Register */
#define REG_HSMCI1_CMDR                        (0xF8000014U) /**< \brief (HSMCI1) Command Register */
#define REG_HSMCI1_BLKR                        (0xF8000018U) /**< \brief (HSMCI1) Block Register */
#define REG_HSMCI1_CSTOR                       (0xF800001CU) /**< \brief (HSMCI1) Completion Signal Timeout Register */
#define REG_HSMCI1_RSPR                        (0xF8000020U) /**< \brief (HSMCI1) Response Register */
#define REG_HSMCI1_RDR                         (0xF8000030U) /**< \brief (HSMCI1) Receive Data Register */
#define REG_HSMCI1_TDR                         (0xF8000034U) /**< \brief (HSMCI1) Transmit Data Register */
#define REG_HSMCI1_SR                          (0xF8000040U) /**< \brief (HSMCI1) Status Register */
#define REG_HSMCI1_IER                         (0xF8000044U) /**< \brief (HSMCI1) Interrupt Enable Register */
#define REG_HSMCI1_IDR                         (0xF8000048U) /**< \brief (HSMCI1) Interrupt Disable Register */
#define REG_HSMCI1_IMR                         (0xF800004CU) /**< \brief (HSMCI1) Interrupt Mask Register */
#define REG_HSMCI1_DMA                         (0xF8000050U) /**< \brief (HSMCI1) DMA Configuration Register */
#define REG_HSMCI1_CFG                         (0xF8000054U) /**< \brief (HSMCI1) Configuration Register */
#define REG_HSMCI1_WPMR                        (0xF80000E4U) /**< \brief (HSMCI1) Write Protection Mode Register */
#define REG_HSMCI1_WPSR                        (0xF80000E8U) /**< \brief (HSMCI1) Write Protection Status Register */
#define REG_HSMCI1_FIFO                        (0xF8000200U) /**< \brief (HSMCI1) FIFO Memory Aperture0 */
#else
#define REG_HSMCI1_CR                 (*(WoReg*)0xF8000000U) /**< \brief (HSMCI1) Control Register */
#define REG_HSMCI1_MR                 (*(RwReg*)0xF8000004U) /**< \brief (HSMCI1) Mode Register */
#define REG_HSMCI1_DTOR               (*(RwReg*)0xF8000008U) /**< \brief (HSMCI1) Data Timeout Register */
#define REG_HSMCI1_SDCR               (*(RwReg*)0xF800000CU) /**< \brief (HSMCI1) SD/SDIO Card Register */
#define REG_HSMCI1_ARGR               (*(RwReg*)0xF8000010U) /**< \brief (HSMCI1) Argument Register */
#define REG_HSMCI1_CMDR               (*(WoReg*)0xF8000014U) /**< \brief (HSMCI1) Command Register */
#define REG_HSMCI1_BLKR               (*(RwReg*)0xF8000018U) /**< \brief (HSMCI1) Block Register */
#define REG_HSMCI1_CSTOR              (*(RwReg*)0xF800001CU) /**< \brief (HSMCI1) Completion Signal Timeout Register */
#define REG_HSMCI1_RSPR               (*(RoReg*)0xF8000020U) /**< \brief (HSMCI1) Response Register */
#define REG_HSMCI1_RDR                (*(RoReg*)0xF8000030U) /**< \brief (HSMCI1) Receive Data Register */
#define REG_HSMCI1_TDR                (*(WoReg*)0xF8000034U) /**< \brief (HSMCI1) Transmit Data Register */
#define REG_HSMCI1_SR                 (*(RoReg*)0xF8000040U) /**< \brief (HSMCI1) Status Register */
#define REG_HSMCI1_IER                (*(WoReg*)0xF8000044U) /**< \brief (HSMCI1) Interrupt Enable Register */
#define REG_HSMCI1_IDR                (*(WoReg*)0xF8000048U) /**< \brief (HSMCI1) Interrupt Disable Register */
#define REG_HSMCI1_IMR                (*(RoReg*)0xF800004CU) /**< \brief (HSMCI1) Interrupt Mask Register */
#define REG_HSMCI1_DMA                (*(RwReg*)0xF8000050U) /**< \brief (HSMCI1) DMA Configuration Register */
#define REG_HSMCI1_CFG                (*(RwReg*)0xF8000054U) /**< \brief (HSMCI1) Configuration Register */
#define REG_HSMCI1_WPMR               (*(RwReg*)0xF80000E4U) /**< \brief (HSMCI1) Write Protection Mode Register */
#define REG_HSMCI1_WPSR               (*(RoReg*)0xF80000E8U) /**< \brief (HSMCI1) Write Protection Status Register */
#define REG_HSMCI1_FIFO               (*(RwReg*)0xF8000200U) /**< \brief (HSMCI1) FIFO Memory Aperture0 */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for HSMCI2 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_HSMCI2_CR                          (0xF8004000U) /**< \brief (HSMCI2) Control Register */
#define REG_HSMCI2_MR                          (0xF8004004U) /**< \brief (HSMCI2) Mode Register */
#define REG_HSMCI2_DTOR                        (0xF8004008U) /**< \brief (HSMCI2) Data Timeout Register */
#define REG_HSMCI2_SDCR                        (0xF800400CU) /**< \brief (HSMCI2) SD/SDIO Card Register */
#define REG_HSMCI2_ARGR                        (0xF8004010U) /**< \brief (HSMCI2) Argument Register */
#define REG_HSMCI2_CMDR                        (0xF8004014U) /**< \brief (HSMCI2) Command Register */
#define REG_HSMCI2_BLKR                        (0xF8004018U) /**< \brief (HSMCI2) Block Register */
#define REG_HSMCI2_CSTOR                       (0xF800401CU) /**< \brief (HSMCI2) Completion Signal Timeout Register */
#define REG_HSMCI2_RSPR                        (0xF8004020U) /**< \brief (HSMCI2) Response Register */
#define REG_HSMCI2_RDR                         (0xF8004030U) /**< \brief (HSMCI2) Receive Data Register */
#define REG_HSMCI2_TDR                         (0xF8004034U) /**< \brief (HSMCI2) Transmit Data Register */
#define REG_HSMCI2_SR                          (0xF8004040U) /**< \brief (HSMCI2) Status Register */
#define REG_HSMCI2_IER                         (0xF8004044U) /**< \brief (HSMCI2) Interrupt Enable Register */
#define REG_HSMCI2_IDR                         (0xF8004048U) /**< \brief (HSMCI2) Interrupt Disable Register */
#define REG_HSMCI2_IMR                         (0xF800404CU) /**< \brief (HSMCI2) Interrupt Mask Register */
#define REG_HSMCI2_DMA                         (0xF8004050U) /**< \brief (HSMCI2) DMA Configuration Register */
#define REG_HSMCI2_CFG                         (0xF8004054U) /**< \brief (HSMCI2) Configuration Register */
#define REG_HSMCI2_WPMR                        (0xF80040E4U) /**< \brief (HSMCI2) Write Protection Mode Register */
#define REG_HSMCI2_WPSR                        (0xF80040E8U) /**< \brief (HSMCI2) Write Protection Status Register */
#define REG_HSMCI2_FIFO                        (0xF8004200U) /**< \brief (HSMCI2) FIFO Memory Aperture0 */
#else
#define REG_HSMCI2_CR                 (*(WoReg*)0xF8004000U) /**< \brief (HSMCI2) Control Register */
#define REG_HSMCI2_MR                 (*(RwReg*)0xF8004004U) /**< \brief (HSMCI2) Mode Register */
#define REG_HSMCI2_DTOR               (*(RwReg*)0xF8004008U) /**< \brief (HSMCI2) Data Timeout Register */
#define REG_HSMCI2_SDCR               (*(RwReg*)0xF800400CU) /**< \brief (HSMCI2) SD/SDIO Card Register */
#define REG_HSMCI2_ARGR               (*(RwReg*)0xF8004010U) /**< \brief (HSMCI2) Argument Register */
#define REG_HSMCI2_CMDR               (*(WoReg*)0xF8004014U) /**< \brief (HSMCI2) Command Register */
#define REG_HSMCI2_BLKR               (*(RwReg*)0xF8004018U) /**< \brief (HSMCI2) Block Register */
#define REG_HSMCI2_CSTOR              (*(RwReg*)0xF800401CU) /**< \brief (HSMCI2) Completion Signal Timeout Register */
#define REG_HSMCI2_RSPR               (*(RoReg*)0xF8004020U) /**< \brief (HSMCI2) Response Register */
#define REG_HSMCI2_RDR                (*(RoReg*)0xF8004030U) /**< \brief (HSMCI2) Receive Data Register */
#define REG_HSMCI2_TDR                (*(WoReg*)0xF8004034U) /**< \brief (HSMCI2) Transmit Data Register */
#define REG_HSMCI2_SR                 (*(RoReg*)0xF8004040U) /**< \brief (HSMCI2) Status Register */
#define REG_HSMCI2_IER                (*(WoReg*)0xF8004044U) /**< \brief (HSMCI2) Interrupt Enable Register */
#define REG_HSMCI2_IDR                (*(WoReg*)0xF8004048U) /**< \brief (HSMCI2) Interrupt Disable Register */
#define REG_HSMCI2_IMR                (*(RoReg*)0xF800404CU) /**< \brief (HSMCI2) Interrupt Mask Register */
#define REG_HSMCI2_DMA                (*(RwReg*)0xF8004050U) /**< \brief (HSMCI2) DMA Configuration Register */
#define REG_HSMCI2_CFG                (*(RwReg*)0xF8004054U) /**< \brief (HSMCI2) Configuration Register */
#define REG_HSMCI2_WPMR               (*(RwReg*)0xF80040E4U) /**< \brief (HSMCI2) Write Protection Mode Register */
#define REG_HSMCI2_WPSR               (*(RoReg*)0xF80040E8U) /**< \brief (HSMCI2) Write Protection Status Register */
#define REG_HSMCI2_FIFO               (*(RwReg*)0xF8004200U) /**< \brief (HSMCI2) FIFO Memory Aperture0 */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for SPI1 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_SPI1_CR                            (0xF8008000U) /**< \brief (SPI1) Control Register */
#define REG_SPI1_MR                            (0xF8008004U) /**< \brief (SPI1) Mode Register */
#define REG_SPI1_RDR                           (0xF8008008U) /**< \brief (SPI1) Receive Data Register */
#define REG_SPI1_TDR                           (0xF800800CU) /**< \brief (SPI1) Transmit Data Register */
#define REG_SPI1_SR                            (0xF8008010U) /**< \brief (SPI1) Status Register */
#define REG_SPI1_IER                           (0xF8008014U) /**< \brief (SPI1) Interrupt Enable Register */
#define REG_SPI1_IDR                           (0xF8008018U) /**< \brief (SPI1) Interrupt Disable Register */
#define REG_SPI1_IMR                           (0xF800801CU) /**< \brief (SPI1) Interrupt Mask Register */
#define REG_SPI1_CSR                           (0xF8008030U) /**< \brief (SPI1) Chip Select Register */
#define REG_SPI1_WPMR                          (0xF80080E4U) /**< \brief (SPI1) Write Protection Control Register */
#define REG_SPI1_WPSR                          (0xF80080E8U) /**< \brief (SPI1) Write Protection Status Register */
#else
#define REG_SPI1_CR                   (*(WoReg*)0xF8008000U) /**< \brief (SPI1) Control Register */
#define REG_SPI1_MR                   (*(RwReg*)0xF8008004U) /**< \brief (SPI1) Mode Register */
#define REG_SPI1_RDR                  (*(RoReg*)0xF8008008U) /**< \brief (SPI1) Receive Data Register */
#define REG_SPI1_TDR                  (*(WoReg*)0xF800800CU) /**< \brief (SPI1) Transmit Data Register */
#define REG_SPI1_SR                   (*(RoReg*)0xF8008010U) /**< \brief (SPI1) Status Register */
#define REG_SPI1_IER                  (*(WoReg*)0xF8008014U) /**< \brief (SPI1) Interrupt Enable Register */
#define REG_SPI1_IDR                  (*(WoReg*)0xF8008018U) /**< \brief (SPI1) Interrupt Disable Register */
#define REG_SPI1_IMR                  (*(RoReg*)0xF800801CU) /**< \brief (SPI1) Interrupt Mask Register */
#define REG_SPI1_CSR                  (*(RwReg*)0xF8008030U) /**< \brief (SPI1) Chip Select Register */
#define REG_SPI1_WPMR                 (*(RwReg*)0xF80080E4U) /**< \brief (SPI1) Write Protection Control Register */
#define REG_SPI1_WPSR                 (*(RoReg*)0xF80080E8U) /**< \brief (SPI1) Write Protection Status Register */
#endif /* __ASSEMBLY__ */

/* ========== Register definition for TC1 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_TC1_CCR0                           (0xF8014000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
#define REG_TC1_CMR0                           (0xF8014004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
#define REG_TC1_SMMR0                          (0xF8014008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
#define REG_TC1_RAB0                           (0xF801400CU) /**< \brief (TC1) Register AB (channel = 0) */
#define REG_TC1_CV0                            (0xF8014010U) /**< \brief (TC1) Counter Value (channel = 0) */
#define REG_TC1_RA0                            (0xF8014014U) /**< \brief (TC1) Register A (channel = 0) */
#define REG_TC1_RB0                            (0xF8014018U) /**< \brief (TC1) Register B (channel = 0) */
#define REG_TC1_RC0                            (0xF801401CU) /**< \brief (TC1) Register C (channel = 0) */
#define REG_TC1_SR0                            (0xF8014020U) /**< \brief (TC1) Status Register (channel = 0) */
#define REG_TC1_IER0                           (0xF8014024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
#define REG_TC1_IDR0                           (0xF8014028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
#define REG_TC1_IMR0                           (0xF801402CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
#define REG_TC1_CCR1                           (0xF8014040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
#define REG_TC1_CMR1                           (0xF8014044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
#define REG_TC1_SMMR1                          (0xF8014048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
#define REG_TC1_RAB1                           (0xF801404CU) /**< \brief (TC1) Register AB (channel = 1) */
#define REG_TC1_CV1                            (0xF8014050U) /**< \brief (TC1) Counter Value (channel = 1) */
#define REG_TC1_RA1                            (0xF8014054U) /**< \brief (TC1) Register A (channel = 1) */
#define REG_TC1_RB1                            (0xF8014058U) /**< \brief (TC1) Register B (channel = 1) */
#define REG_TC1_RC1                            (0xF801405CU) /**< \brief (TC1) Register C (channel = 1) */
#define REG_TC1_SR1                            (0xF8014060U) /**< \brief (TC1) Status Register (channel = 1) */
#define REG_TC1_IER1                           (0xF8014064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
#define REG_TC1_IDR1                           (0xF8014068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
#define REG_TC1_IMR1                           (0xF801406CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
#define REG_TC1_CCR2                           (0xF8014080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
#define REG_TC1_CMR2                           (0xF8014084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
#define REG_TC1_SMMR2                          (0xF8014088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
#define REG_TC1_RAB2                           (0xF801408CU) /**< \brief (TC1) Register AB (channel = 2) */
#define REG_TC1_CV2                            (0xF8014090U) /**< \brief (TC1) Counter Value (channel = 2) */
#define REG_TC1_RA2                            (0xF8014094U) /**< \brief (TC1) Register A (channel = 2) */
#define REG_TC1_RB2                            (0xF8014098U) /**< \brief (TC1) Register B (channel = 2) */
#define REG_TC1_RC2                            (0xF801409CU) /**< \brief (TC1) Register C (channel = 2) */
#define REG_TC1_SR2                            (0xF80140A0U) /**< \brief (TC1) Status Register (channel = 2) */
#define REG_TC1_IER2                           (0xF80140A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
#define REG_TC1_IDR2                           (0xF80140A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
#define REG_TC1_IMR2                           (0xF80140ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
#define REG_TC1_BCR                            (0xF80140C0U) /**< \brief (TC1) Block Control Register */
#define REG_TC1_BMR                            (0xF80140C4U) /**< \brief (TC1) Block Mode Register */
#define REG_TC1_WPMR                           (0xF80140E4U) /**< \brief (TC1) Write Protect Mode Register */
#else
#define REG_TC1_CCR0                  (*(WoReg*)0xF8014000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
#define REG_TC1_CMR0                  (*(RwReg*)0xF8014004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
#define REG_TC1_SMMR0                 (*(RwReg*)0xF8014008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
#define REG_TC1_RAB0                  (*(RoReg*)0xF801400CU) /**< \brief (TC1) Register AB (channel = 0) */
#define REG_TC1_CV0                   (*(RoReg*)0xF8014010U) /**< \brief (TC1) Counter Value (channel = 0) */
#define REG_TC1_RA0                   (*(RwReg*)0xF8014014U) /**< \brief (TC1) Register A (channel = 0) */
#define REG_TC1_RB0                   (*(RwReg*)0xF8014018U) /**< \brief (TC1) Register B (channel = 0) */
#define REG_TC1_RC0                   (*(RwReg*)0xF801401CU) /**< \brief (TC1) Register C (channel = 0) */
#define REG_TC1_SR0                   (*(RoReg*)0xF8014020U) /**< \brief (TC1) Status Register (channel = 0) */
#define REG_TC1_IER0                  (*(WoReg*)0xF8014024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
#define REG_TC1_IDR0                  (*(WoReg*)0xF8014028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
#define REG_TC1_IMR0                  (*(RoReg*)0xF801402CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
#define REG_TC1_CCR1                  (*(WoReg*)0xF8014040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
#define REG_TC1_CMR1                  (*(RwReg*)0xF8014044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
#define REG_TC1_SMMR1                 (*(RwReg*)0xF8014048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
#define REG_TC1_RAB1                  (*(RoReg*)0xF801404CU) /**< \brief (TC1) Register AB (channel = 1) */
#define REG_TC1_CV1                   (*(RoReg*)0xF8014050U) /**< \brief (TC1) Counter Value (channel = 1) */
#define REG_TC1_RA1                   (*(RwReg*)0xF8014054U) /**< \brief (TC1) Register A (channel = 1) */
#define REG_TC1_RB1                   (*(RwReg*)0xF8014058U) /**< \brief (TC1) Register B (channel = 1) */
#define REG_TC1_RC1                   (*(RwReg*)0xF801405CU) /**< \brief (TC1) Register C (channel = 1) */
#define REG_TC1_SR1                   (*(RoReg*)0xF8014060U) /**< \brief (TC1) Status Register (channel = 1) */
#define REG_TC1_IER1                  (*(WoReg*)0xF8014064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
#define REG_TC1_IDR1                  (*(WoReg*)0xF8014068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
#define REG_TC1_IMR1                  (*(RoReg*)0xF801406CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
#define REG_TC1_CCR2                  (*(WoReg*)0xF8014080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
#define REG_TC1_CMR2                  (*(RwReg*)0xF8014084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
#define REG_TC1_SMMR2                 (*(RwReg*)0xF8014088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
#define REG_TC1_RAB2                  (*(RoReg*)0xF801408CU) /**< \brief (TC1) Register AB (channel = 2) */
#define REG_TC1_CV2                   (*(RoReg*)0xF8014090U) /**< \brief (TC1) Counter Value (channel = 2) */
#define REG_TC1_RA2                   (*(RwReg*)0xF8014094U) /**< \brief (TC1) Register A (channel = 2) */
#define REG_TC1_RB2                   (*(RwReg*)0xF8014098U) /**< \brief (TC1) Register B (channel = 2) */
#define REG_TC1_RC2                   (*(RwReg*)0xF801409CU) /**< \brief (TC1) Register C (channel = 2) */
#define REG_TC1_SR2                   (*(RoReg*)0xF80140A0U) /**< \brief (TC1) Status Register (channel = 2) */
#define REG_TC1_IER2                  (*(WoReg*)0xF80140A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
#define REG_TC1_IDR2                  (*(WoReg*)0xF80140A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
#define REG_TC1_IMR2                  (*(RoReg*)0xF80140ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
#define REG_TC1_BCR                   (*(WoReg*)0xF80140C0U) /**< \brief (TC1) Block Control Register */
#define REG_TC1_BMR                   (*(RwReg*)0xF80140C4U) /**< \brief (TC1) Block Mode Register */
#define REG_TC1_WPMR                  (*(RwReg*)0xF80140E4U) /**< \brief (TC1) Write Protect Mode Register */
#endif /* __ASSEMBLY__ */

/* ========== Register definition for TWI2 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_TWI2_CR                            (0xF801C000U) /**< \brief (TWI2) Control Register */
#define REG_TWI2_MMR                           (0xF801C004U) /**< \brief (TWI2) Master Mode Register */
#define REG_TWI2_SMR                           (0xF801C008U) /**< \brief (TWI2) Slave Mode Register */
#define REG_TWI2_IADR                          (0xF801C00CU) /**< \brief (TWI2) Internal Address Register */
#define REG_TWI2_CWGR                          (0xF801C010U) /**< \brief (TWI2) Clock Waveform Generator Register */
#define REG_TWI2_SR                            (0xF801C020U) /**< \brief (TWI2) Status Register */
#define REG_TWI2_IER                           (0xF801C024U) /**< \brief (TWI2) Interrupt Enable Register */
#define REG_TWI2_IDR                           (0xF801C028U) /**< \brief (TWI2) Interrupt Disable Register */
#define REG_TWI2_IMR                           (0xF801C02CU) /**< \brief (TWI2) Interrupt Mask Register */
#define REG_TWI2_RHR                           (0xF801C030U) /**< \brief (TWI2) Receive Holding Register */
#define REG_TWI2_THR                           (0xF801C034U) /**< \brief (TWI2) Transmit Holding Register */
#define REG_TWI2_WPROT_MODE                    (0xF801C0E4U) /**< \brief (TWI2) Protection Mode Register */
#define REG_TWI2_WPROT_STATUS                  (0xF801C0E8U) /**< \brief (TWI2) Protection Status Register */
#else
#define REG_TWI2_CR                   (*(WoReg*)0xF801C000U) /**< \brief (TWI2) Control Register */
#define REG_TWI2_MMR                  (*(RwReg*)0xF801C004U) /**< \brief (TWI2) Master Mode Register */
#define REG_TWI2_SMR                  (*(RwReg*)0xF801C008U) /**< \brief (TWI2) Slave Mode Register */
#define REG_TWI2_IADR                 (*(RwReg*)0xF801C00CU) /**< \brief (TWI2) Internal Address Register */
#define REG_TWI2_CWGR                 (*(RwReg*)0xF801C010U) /**< \brief (TWI2) Clock Waveform Generator Register */
#define REG_TWI2_SR                   (*(RoReg*)0xF801C020U) /**< \brief (TWI2) Status Register */
#define REG_TWI2_IER                  (*(WoReg*)0xF801C024U) /**< \brief (TWI2) Interrupt Enable Register */
#define REG_TWI2_IDR                  (*(WoReg*)0xF801C028U) /**< \brief (TWI2) Interrupt Disable Register */
#define REG_TWI2_IMR                  (*(RoReg*)0xF801C02CU) /**< \brief (TWI2) Interrupt Mask Register */
#define REG_TWI2_RHR                  (*(RoReg*)0xF801C030U) /**< \brief (TWI2) Receive Holding Register */
#define REG_TWI2_THR                  (*(WoReg*)0xF801C034U) /**< \brief (TWI2) Transmit Holding Register */
#define REG_TWI2_WPROT_MODE           (*(RwReg*)0xF801C0E4U) /**< \brief (TWI2) Protection Mode Register */
#define REG_TWI2_WPROT_STATUS         (*(RoReg*)0xF801C0E8U) /**< \brief (TWI2) Protection Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for USART2 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_USART2_CR                          (0xF8020000U) /**< \brief (USART2) Control Register */
#define REG_USART2_MR                          (0xF8020004U) /**< \brief (USART2) Mode Register */
#define REG_USART2_IER                         (0xF8020008U) /**< \brief (USART2) Interrupt Enable Register */
#define REG_USART2_IDR                         (0xF802000CU) /**< \brief (USART2) Interrupt Disable Register */
#define REG_USART2_IMR                         (0xF8020010U) /**< \brief (USART2) Interrupt Mask Register */
#define REG_USART2_CSR                         (0xF8020014U) /**< \brief (USART2) Channel Status Register */
#define REG_USART2_RHR                         (0xF8020018U) /**< \brief (USART2) Receiver Holding Register */
#define REG_USART2_THR                         (0xF802001CU) /**< \brief (USART2) Transmitter Holding Register */
#define REG_USART2_BRGR                        (0xF8020020U) /**< \brief (USART2) Baud Rate Generator Register */
#define REG_USART2_RTOR                        (0xF8020024U) /**< \brief (USART2) Receiver Time-out Register */
#define REG_USART2_TTGR                        (0xF8020028U) /**< \brief (USART2) Transmitter Timeguard Register */
#define REG_USART2_FIDI                        (0xF8020040U) /**< \brief (USART2) FI DI Ratio Register */
#define REG_USART2_NER                         (0xF8020044U) /**< \brief (USART2) Number of Errors Register */
#define REG_USART2_IF                          (0xF802004CU) /**< \brief (USART2) IrDA Filter Register */
#define REG_USART2_MAN                         (0xF8020050U) /**< \brief (USART2) Manchester Encoder Decoder Register */
#define REG_USART2_WPMR                        (0xF80200E4U) /**< \brief (USART2) Write Protect Mode Register */
#define REG_USART2_WPSR                        (0xF80200E8U) /**< \brief (USART2) Write Protect Status Register */
#else
#define REG_USART2_CR                 (*(WoReg*)0xF8020000U) /**< \brief (USART2) Control Register */
#define REG_USART2_MR                 (*(RwReg*)0xF8020004U) /**< \brief (USART2) Mode Register */
#define REG_USART2_IER                (*(WoReg*)0xF8020008U) /**< \brief (USART2) Interrupt Enable Register */
#define REG_USART2_IDR                (*(WoReg*)0xF802000CU) /**< \brief (USART2) Interrupt Disable Register */
#define REG_USART2_IMR                (*(RoReg*)0xF8020010U) /**< \brief (USART2) Interrupt Mask Register */
#define REG_USART2_CSR                (*(RoReg*)0xF8020014U) /**< \brief (USART2) Channel Status Register */
#define REG_USART2_RHR                (*(RoReg*)0xF8020018U) /**< \brief (USART2) Receiver Holding Register */
#define REG_USART2_THR                (*(WoReg*)0xF802001CU) /**< \brief (USART2) Transmitter Holding Register */
#define REG_USART2_BRGR               (*(RwReg*)0xF8020020U) /**< \brief (USART2) Baud Rate Generator Register */
#define REG_USART2_RTOR               (*(RwReg*)0xF8020024U) /**< \brief (USART2) Receiver Time-out Register */
#define REG_USART2_TTGR               (*(RwReg*)0xF8020028U) /**< \brief (USART2) Transmitter Timeguard Register */
#define REG_USART2_FIDI               (*(RwReg*)0xF8020040U) /**< \brief (USART2) FI DI Ratio Register */
#define REG_USART2_NER                (*(RoReg*)0xF8020044U) /**< \brief (USART2) Number of Errors Register */
#define REG_USART2_IF                 (*(RwReg*)0xF802004CU) /**< \brief (USART2) IrDA Filter Register */
#define REG_USART2_MAN                (*(RwReg*)0xF8020050U) /**< \brief (USART2) Manchester Encoder Decoder Register */
#define REG_USART2_WPMR               (*(RwReg*)0xF80200E4U) /**< \brief (USART2) Write Protect Mode Register */
#define REG_USART2_WPSR               (*(RoReg*)0xF80200E8U) /**< \brief (USART2) Write Protect Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for USART3 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_USART3_CR                          (0xF8024000U) /**< \brief (USART3) Control Register */
#define REG_USART3_MR                          (0xF8024004U) /**< \brief (USART3) Mode Register */
#define REG_USART3_IER                         (0xF8024008U) /**< \brief (USART3) Interrupt Enable Register */
#define REG_USART3_IDR                         (0xF802400CU) /**< \brief (USART3) Interrupt Disable Register */
#define REG_USART3_IMR                         (0xF8024010U) /**< \brief (USART3) Interrupt Mask Register */
#define REG_USART3_CSR                         (0xF8024014U) /**< \brief (USART3) Channel Status Register */
#define REG_USART3_RHR                         (0xF8024018U) /**< \brief (USART3) Receiver Holding Register */
#define REG_USART3_THR                         (0xF802401CU) /**< \brief (USART3) Transmitter Holding Register */
#define REG_USART3_BRGR                        (0xF8024020U) /**< \brief (USART3) Baud Rate Generator Register */
#define REG_USART3_RTOR                        (0xF8024024U) /**< \brief (USART3) Receiver Time-out Register */
#define REG_USART3_TTGR                        (0xF8024028U) /**< \brief (USART3) Transmitter Timeguard Register */
#define REG_USART3_FIDI                        (0xF8024040U) /**< \brief (USART3) FI DI Ratio Register */
#define REG_USART3_NER                         (0xF8024044U) /**< \brief (USART3) Number of Errors Register */
#define REG_USART3_IF                          (0xF802404CU) /**< \brief (USART3) IrDA Filter Register */
#define REG_USART3_MAN                         (0xF8024050U) /**< \brief (USART3) Manchester Encoder Decoder Register */
#define REG_USART3_WPMR                        (0xF80240E4U) /**< \brief (USART3) Write Protect Mode Register */
#define REG_USART3_WPSR                        (0xF80240E8U) /**< \brief (USART3) Write Protect Status Register */
#else
#define REG_USART3_CR                 (*(WoReg*)0xF8024000U) /**< \brief (USART3) Control Register */
#define REG_USART3_MR                 (*(RwReg*)0xF8024004U) /**< \brief (USART3) Mode Register */
#define REG_USART3_IER                (*(WoReg*)0xF8024008U) /**< \brief (USART3) Interrupt Enable Register */
#define REG_USART3_IDR                (*(WoReg*)0xF802400CU) /**< \brief (USART3) Interrupt Disable Register */
#define REG_USART3_IMR                (*(RoReg*)0xF8024010U) /**< \brief (USART3) Interrupt Mask Register */
#define REG_USART3_CSR                (*(RoReg*)0xF8024014U) /**< \brief (USART3) Channel Status Register */
#define REG_USART3_RHR                (*(RoReg*)0xF8024018U) /**< \brief (USART3) Receiver Holding Register */
#define REG_USART3_THR                (*(WoReg*)0xF802401CU) /**< \brief (USART3) Transmitter Holding Register */
#define REG_USART3_BRGR               (*(RwReg*)0xF8024020U) /**< \brief (USART3) Baud Rate Generator Register */
#define REG_USART3_RTOR               (*(RwReg*)0xF8024024U) /**< \brief (USART3) Receiver Time-out Register */
#define REG_USART3_TTGR               (*(RwReg*)0xF8024028U) /**< \brief (USART3) Transmitter Timeguard Register */
#define REG_USART3_FIDI               (*(RwReg*)0xF8024040U) /**< \brief (USART3) FI DI Ratio Register */
#define REG_USART3_NER                (*(RoReg*)0xF8024044U) /**< \brief (USART3) Number of Errors Register */
#define REG_USART3_IF                 (*(RwReg*)0xF802404CU) /**< \brief (USART3) IrDA Filter Register */
#define REG_USART3_MAN                (*(RwReg*)0xF8024050U) /**< \brief (USART3) Manchester Encoder Decoder Register */
#define REG_USART3_WPMR               (*(RwReg*)0xF80240E4U) /**< \brief (USART3) Write Protect Mode Register */
#define REG_USART3_WPSR               (*(RoReg*)0xF80240E8U) /**< \brief (USART3) Write Protect Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for UART1 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_UART1_CR                           (0xF8028000U) /**< \brief (UART1) Control Register */
#define REG_UART1_MR                           (0xF8028004U) /**< \brief (UART1) Mode Register */
#define REG_UART1_IER                          (0xF8028008U) /**< \brief (UART1) Interrupt Enable Register */
#define REG_UART1_IDR                          (0xF802800CU) /**< \brief (UART1) Interrupt Disable Register */
#define REG_UART1_IMR                          (0xF8028010U) /**< \brief (UART1) Interrupt Mask Register */
#define REG_UART1_SR                           (0xF8028014U) /**< \brief (UART1) Status Register */
#define REG_UART1_RHR                          (0xF8028018U) /**< \brief (UART1) Receive Holding Register */
#define REG_UART1_THR                          (0xF802801CU) /**< \brief (UART1) Transmit Holding Register */
#define REG_UART1_BRGR                         (0xF8028020U) /**< \brief (UART1) Baud Rate Generator Register */
#else
#define REG_UART1_CR                  (*(WoReg*)0xF8028000U) /**< \brief (UART1) Control Register */
#define REG_UART1_MR                  (*(RwReg*)0xF8028004U) /**< \brief (UART1) Mode Register */
#define REG_UART1_IER                 (*(WoReg*)0xF8028008U) /**< \brief (UART1) Interrupt Enable Register */
#define REG_UART1_IDR                 (*(WoReg*)0xF802800CU) /**< \brief (UART1) Interrupt Disable Register */
#define REG_UART1_IMR                 (*(RoReg*)0xF8028010U) /**< \brief (UART1) Interrupt Mask Register */
#define REG_UART1_SR                  (*(RoReg*)0xF8028014U) /**< \brief (UART1) Status Register */
#define REG_UART1_RHR                 (*(RoReg*)0xF8028018U) /**< \brief (UART1) Receive Holding Register */
#define REG_UART1_THR                 (*(WoReg*)0xF802801CU) /**< \brief (UART1) Transmit Holding Register */
#define REG_UART1_BRGR                (*(RwReg*)0xF8028020U) /**< \brief (UART1) Baud Rate Generator Register */
#endif /* __ASSEMBLY__ */

/* ========== Register definition for SMC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_SMC_CFG                            (0xFFFFC000U) /**< \brief (SMC) SMC NFC Configuration Register */
#define REG_SMC_CTRL                           (0xFFFFC004U) /**< \brief (SMC) SMC NFC Control Register */
#define REG_SMC_SR                             (0xFFFFC008U) /**< \brief (SMC) SMC NFC Status Register */
#define REG_SMC_IER                            (0xFFFFC00CU) /**< \brief (SMC) SMC NFC Interrupt Enable Register */
#define REG_SMC_IDR                            (0xFFFFC010U) /**< \brief (SMC) SMC NFC Interrupt Disable Register */
#define REG_SMC_IMR                            (0xFFFFC014U) /**< \brief (SMC) SMC NFC Interrupt Mask Register */
#define REG_SMC_ADDR                           (0xFFFFC018U) /**< \brief (SMC) SMC NFC Address Cycle Zero Register */
#define REG_SMC_BANK                           (0xFFFFC01CU) /**< \brief (SMC) SMC Bank Address Register */
#define REG_SMC_ECC_CTRL                       (0xFFFFC020U) /**< \brief (SMC) SMC ECC Control Register */
#define REG_SMC_ECC_MD                         (0xFFFFC024U) /**< \brief (SMC) SMC ECC Mode Register */
#define REG_SMC_ECC_SR1                        (0xFFFFC028U) /**< \brief (SMC) SMC ECC Status 1 Register */
#define REG_SMC_ECC_PR0                        (0xFFFFC02CU) /**< \brief (SMC) SMC ECC Parity 0 Register */
#define REG_SMC_ECC_PR1                        (0xFFFFC030U) /**< \brief (SMC) SMC ECC parity 1 Register */
#define REG_SMC_ECC_SR2                        (0xFFFFC034U) /**< \brief (SMC) SMC ECC status 2 Register */
#define REG_SMC_ECC_PR2                        (0xFFFFC038U) /**< \brief (SMC) SMC ECC parity 2 Register */
#define REG_SMC_ECC_PR3                        (0xFFFFC03CU) /**< \brief (SMC) SMC ECC parity 3 Register */
#define REG_SMC_ECC_PR4                        (0xFFFFC040U) /**< \brief (SMC) SMC ECC parity 4 Register */
#define REG_SMC_ECC_PR5                        (0xFFFFC044U) /**< \brief (SMC) SMC ECC parity 5 Register */
#define REG_SMC_ECC_PR6                        (0xFFFFC048U) /**< \brief (SMC) SMC ECC parity 6 Register */
#define REG_SMC_ECC_PR7                        (0xFFFFC04CU) /**< \brief (SMC) SMC ECC parity 7 Register */
#define REG_SMC_ECC_PR8                        (0xFFFFC050U) /**< \brief (SMC) SMC ECC parity 8 Register */
#define REG_SMC_ECC_PR9                        (0xFFFFC054U) /**< \brief (SMC) SMC ECC parity 9 Register */
#define REG_SMC_ECC_PR10                       (0xFFFFC058U) /**< \brief (SMC) SMC ECC parity 10 Register */
#define REG_SMC_ECC_PR11                       (0xFFFFC05CU) /**< \brief (SMC) SMC ECC parity 11 Register */
#define REG_SMC_ECC_PR12                       (0xFFFFC060U) /**< \brief (SMC) SMC ECC parity 12 Register */
#define REG_SMC_ECC_PR13                       (0xFFFFC064U) /**< \brief (SMC) SMC ECC parity 13 Register */
#define REG_SMC_ECC_PR14                       (0xFFFFC068U) /**< \brief (SMC) SMC ECC parity 14 Register */
#define REG_SMC_ECC_PR15                       (0xFFFFC06CU) /**< \brief (SMC) SMC ECC parity 15 Register */
#define REG_SMC_PMECCFG                        (0xFFFFC070U) /**< \brief (SMC) PMECC Configuration Register */
#define REG_SMC_PMECCSAREA                     (0xFFFFC074U) /**< \brief (SMC) PMECC Spare Area Size Register */
#define REG_SMC_PMECCSADDR                     (0xFFFFC078U) /**< \brief (SMC) PMECC Start Address Register */
#define REG_SMC_PMECCEADDR                     (0xFFFFC07CU) /**< \brief (SMC) PMECC End Address Register */
#define REG_SMC_PMECCTRL                       (0xFFFFC084U) /**< \brief (SMC) PMECC Control Register */
#define REG_SMC_PMECCSR                        (0xFFFFC088U) /**< \brief (SMC) PMECC Status Register */
#define REG_SMC_PMECCIER                       (0xFFFFC08CU) /**< \brief (SMC) PMECC Interrupt Enable register */
#define REG_SMC_PMECCIDR                       (0xFFFFC090U) /**< \brief (SMC) PMECC Interrupt Disable Register */
#define REG_SMC_PMECCIMR                       (0xFFFFC094U) /**< \brief (SMC) PMECC Interrupt Mask Register */
#define REG_SMC_PMECCISR                       (0xFFFFC098U) /**< \brief (SMC) PMECC Interrupt Status Register */
#define REG_SMC_PMECC0_0                       (0xFFFFC0B0U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 0) */
#define REG_SMC_PMECC1_0                       (0xFFFFC0B4U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 0) */
#define REG_SMC_PMECC2_0                       (0xFFFFC0B8U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 0) */
#define REG_SMC_PMECC3_0                       (0xFFFFC0BCU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 0) */
#define REG_SMC_PMECC4_0                       (0xFFFFC0C0U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 0) */
#define REG_SMC_PMECC5_0                       (0xFFFFC0C4U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 0) */
#define REG_SMC_PMECC6_0                       (0xFFFFC0C8U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 0) */
#define REG_SMC_PMECC7_0                       (0xFFFFC0CCU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 0) */
#define REG_SMC_PMECC8_0                       (0xFFFFC0D0U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 0) */
#define REG_SMC_PMECC9_0                       (0xFFFFC0D4U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 0) */
#define REG_SMC_PMECC10_0                      (0xFFFFC0D8U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 0) */
#define REG_SMC_PMECC0_1                       (0xFFFFC0F0U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 1) */
#define REG_SMC_PMECC1_1                       (0xFFFFC0F4U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 1) */
#define REG_SMC_PMECC2_1                       (0xFFFFC0F8U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 1) */
#define REG_SMC_PMECC3_1                       (0xFFFFC0FCU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 1) */
#define REG_SMC_PMECC4_1                       (0xFFFFC100U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 1) */
#define REG_SMC_PMECC5_1                       (0xFFFFC104U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 1) */
#define REG_SMC_PMECC6_1                       (0xFFFFC108U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 1) */
#define REG_SMC_PMECC7_1                       (0xFFFFC10CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 1) */
#define REG_SMC_PMECC8_1                       (0xFFFFC110U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 1) */
#define REG_SMC_PMECC9_1                       (0xFFFFC114U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 1) */
#define REG_SMC_PMECC10_1                      (0xFFFFC118U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 1) */
#define REG_SMC_PMECC0_2                       (0xFFFFC130U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 2) */
#define REG_SMC_PMECC1_2                       (0xFFFFC134U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 2) */
#define REG_SMC_PMECC2_2                       (0xFFFFC138U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 2) */
#define REG_SMC_PMECC3_2                       (0xFFFFC13CU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 2) */
#define REG_SMC_PMECC4_2                       (0xFFFFC140U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 2) */
#define REG_SMC_PMECC5_2                       (0xFFFFC144U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 2) */
#define REG_SMC_PMECC6_2                       (0xFFFFC148U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 2) */
#define REG_SMC_PMECC7_2                       (0xFFFFC14CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 2) */
#define REG_SMC_PMECC8_2                       (0xFFFFC150U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 2) */
#define REG_SMC_PMECC9_2                       (0xFFFFC154U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 2) */
#define REG_SMC_PMECC10_2                      (0xFFFFC158U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 2) */
#define REG_SMC_PMECC0_3                       (0xFFFFC170U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 3) */
#define REG_SMC_PMECC1_3                       (0xFFFFC174U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 3) */
#define REG_SMC_PMECC2_3                       (0xFFFFC178U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 3) */
#define REG_SMC_PMECC3_3                       (0xFFFFC17CU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 3) */
#define REG_SMC_PMECC4_3                       (0xFFFFC180U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 3) */
#define REG_SMC_PMECC5_3                       (0xFFFFC184U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 3) */
#define REG_SMC_PMECC6_3                       (0xFFFFC188U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 3) */
#define REG_SMC_PMECC7_3                       (0xFFFFC18CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 3) */
#define REG_SMC_PMECC8_3                       (0xFFFFC190U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 3) */
#define REG_SMC_PMECC9_3                       (0xFFFFC194U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 3) */
#define REG_SMC_PMECC10_3                      (0xFFFFC198U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 3) */
#define REG_SMC_PMECC0_4                       (0xFFFFC1B0U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 4) */
#define REG_SMC_PMECC1_4                       (0xFFFFC1B4U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 4) */
#define REG_SMC_PMECC2_4                       (0xFFFFC1B8U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 4) */
#define REG_SMC_PMECC3_4                       (0xFFFFC1BCU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 4) */
#define REG_SMC_PMECC4_4                       (0xFFFFC1C0U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 4) */
#define REG_SMC_PMECC5_4                       (0xFFFFC1C4U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 4) */
#define REG_SMC_PMECC6_4                       (0xFFFFC1C8U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 4) */
#define REG_SMC_PMECC7_4                       (0xFFFFC1CCU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 4) */
#define REG_SMC_PMECC8_4                       (0xFFFFC1D0U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 4) */
#define REG_SMC_PMECC9_4                       (0xFFFFC1D4U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 4) */
#define REG_SMC_PMECC10_4                      (0xFFFFC1D8U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 4) */
#define REG_SMC_PMECC0_5                       (0xFFFFC1F0U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 5) */
#define REG_SMC_PMECC1_5                       (0xFFFFC1F4U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 5) */
#define REG_SMC_PMECC2_5                       (0xFFFFC1F8U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 5) */
#define REG_SMC_PMECC3_5                       (0xFFFFC1FCU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 5) */
#define REG_SMC_PMECC4_5                       (0xFFFFC200U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 5) */
#define REG_SMC_PMECC5_5                       (0xFFFFC204U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 5) */
#define REG_SMC_PMECC6_5                       (0xFFFFC208U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 5) */
#define REG_SMC_PMECC7_5                       (0xFFFFC20CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 5) */
#define REG_SMC_PMECC8_5                       (0xFFFFC210U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 5) */
#define REG_SMC_PMECC9_5                       (0xFFFFC214U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 5) */
#define REG_SMC_PMECC10_5                      (0xFFFFC218U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 5) */
#define REG_SMC_PMECC0_6                       (0xFFFFC230U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 6) */
#define REG_SMC_PMECC1_6                       (0xFFFFC234U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 6) */
#define REG_SMC_PMECC2_6                       (0xFFFFC238U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 6) */
#define REG_SMC_PMECC3_6                       (0xFFFFC23CU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 6) */
#define REG_SMC_PMECC4_6                       (0xFFFFC240U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 6) */
#define REG_SMC_PMECC5_6                       (0xFFFFC244U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 6) */
#define REG_SMC_PMECC6_6                       (0xFFFFC248U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 6) */
#define REG_SMC_PMECC7_6                       (0xFFFFC24CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 6) */
#define REG_SMC_PMECC8_6                       (0xFFFFC250U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 6) */
#define REG_SMC_PMECC9_6                       (0xFFFFC254U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 6) */
#define REG_SMC_PMECC10_6                      (0xFFFFC258U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 6) */
#define REG_SMC_PMECC0_7                       (0xFFFFC270U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 7) */
#define REG_SMC_PMECC1_7                       (0xFFFFC274U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 7) */
#define REG_SMC_PMECC2_7                       (0xFFFFC278U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 7) */
#define REG_SMC_PMECC3_7                       (0xFFFFC27CU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 7) */
#define REG_SMC_PMECC4_7                       (0xFFFFC280U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 7) */
#define REG_SMC_PMECC5_7                       (0xFFFFC284U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 7) */
#define REG_SMC_PMECC6_7                       (0xFFFFC288U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 7) */
#define REG_SMC_PMECC7_7                       (0xFFFFC28CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 7) */
#define REG_SMC_PMECC8_7                       (0xFFFFC290U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 7) */
#define REG_SMC_PMECC9_7                       (0xFFFFC294U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 7) */
#define REG_SMC_PMECC10_7                      (0xFFFFC298U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 7) */
#define REG_SMC_REM0_0                         (0xFFFFC2B0U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 0) */
#define REG_SMC_REM1_0                         (0xFFFFC2B4U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 0) */
#define REG_SMC_REM2_0                         (0xFFFFC2B8U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 0) */
#define REG_SMC_REM3_0                         (0xFFFFC2BCU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 0) */
#define REG_SMC_REM4_0                         (0xFFFFC2C0U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 0) */
#define REG_SMC_REM5_0                         (0xFFFFC2C4U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 0) */
#define REG_SMC_REM6_0                         (0xFFFFC2C8U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 0) */
#define REG_SMC_REM7_0                         (0xFFFFC2CCU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 0) */
#define REG_SMC_REM8_0                         (0xFFFFC2D0U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 0) */
#define REG_SMC_REM9_0                         (0xFFFFC2D4U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 0) */
#define REG_SMC_REM10_0                        (0xFFFFC2D8U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 0) */
#define REG_SMC_REM11_0                        (0xFFFFC2DCU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 0) */
#define REG_SMC_REM0_1                         (0xFFFFC2F0U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 1) */
#define REG_SMC_REM1_1                         (0xFFFFC2F4U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 1) */
#define REG_SMC_REM2_1                         (0xFFFFC2F8U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 1) */
#define REG_SMC_REM3_1                         (0xFFFFC2FCU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 1) */
#define REG_SMC_REM4_1                         (0xFFFFC300U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 1) */
#define REG_SMC_REM5_1                         (0xFFFFC304U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 1) */
#define REG_SMC_REM6_1                         (0xFFFFC308U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 1) */
#define REG_SMC_REM7_1                         (0xFFFFC30CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 1) */
#define REG_SMC_REM8_1                         (0xFFFFC310U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 1) */
#define REG_SMC_REM9_1                         (0xFFFFC314U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 1) */
#define REG_SMC_REM10_1                        (0xFFFFC318U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 1) */
#define REG_SMC_REM11_1                        (0xFFFFC31CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 1) */
#define REG_SMC_REM0_2                         (0xFFFFC330U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 2) */
#define REG_SMC_REM1_2                         (0xFFFFC334U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 2) */
#define REG_SMC_REM2_2                         (0xFFFFC338U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 2) */
#define REG_SMC_REM3_2                         (0xFFFFC33CU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 2) */
#define REG_SMC_REM4_2                         (0xFFFFC340U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 2) */
#define REG_SMC_REM5_2                         (0xFFFFC344U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 2) */
#define REG_SMC_REM6_2                         (0xFFFFC348U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 2) */
#define REG_SMC_REM7_2                         (0xFFFFC34CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 2) */
#define REG_SMC_REM8_2                         (0xFFFFC350U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 2) */
#define REG_SMC_REM9_2                         (0xFFFFC354U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 2) */
#define REG_SMC_REM10_2                        (0xFFFFC358U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 2) */
#define REG_SMC_REM11_2                        (0xFFFFC35CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 2) */
#define REG_SMC_REM0_3                         (0xFFFFC370U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 3) */
#define REG_SMC_REM1_3                         (0xFFFFC374U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 3) */
#define REG_SMC_REM2_3                         (0xFFFFC378U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 3) */
#define REG_SMC_REM3_3                         (0xFFFFC37CU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 3) */
#define REG_SMC_REM4_3                         (0xFFFFC380U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 3) */
#define REG_SMC_REM5_3                         (0xFFFFC384U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 3) */
#define REG_SMC_REM6_3                         (0xFFFFC388U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 3) */
#define REG_SMC_REM7_3                         (0xFFFFC38CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 3) */
#define REG_SMC_REM8_3                         (0xFFFFC390U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 3) */
#define REG_SMC_REM9_3                         (0xFFFFC394U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 3) */
#define REG_SMC_REM10_3                        (0xFFFFC398U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 3) */
#define REG_SMC_REM11_3                        (0xFFFFC39CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 3) */
#define REG_SMC_REM0_4                         (0xFFFFC3B0U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 4) */
#define REG_SMC_REM1_4                         (0xFFFFC3B4U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 4) */
#define REG_SMC_REM2_4                         (0xFFFFC3B8U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 4) */
#define REG_SMC_REM3_4                         (0xFFFFC3BCU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 4) */
#define REG_SMC_REM4_4                         (0xFFFFC3C0U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 4) */
#define REG_SMC_REM5_4                         (0xFFFFC3C4U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 4) */
#define REG_SMC_REM6_4                         (0xFFFFC3C8U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 4) */
#define REG_SMC_REM7_4                         (0xFFFFC3CCU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 4) */
#define REG_SMC_REM8_4                         (0xFFFFC3D0U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 4) */
#define REG_SMC_REM9_4                         (0xFFFFC3D4U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 4) */
#define REG_SMC_REM10_4                        (0xFFFFC3D8U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 4) */
#define REG_SMC_REM11_4                        (0xFFFFC3DCU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 4) */
#define REG_SMC_REM0_5                         (0xFFFFC3F0U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 5) */
#define REG_SMC_REM1_5                         (0xFFFFC3F4U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 5) */
#define REG_SMC_REM2_5                         (0xFFFFC3F8U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 5) */
#define REG_SMC_REM3_5                         (0xFFFFC3FCU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 5) */
#define REG_SMC_REM4_5                         (0xFFFFC400U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 5) */
#define REG_SMC_REM5_5                         (0xFFFFC404U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 5) */
#define REG_SMC_REM6_5                         (0xFFFFC408U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 5) */
#define REG_SMC_REM7_5                         (0xFFFFC40CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 5) */
#define REG_SMC_REM8_5                         (0xFFFFC410U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 5) */
#define REG_SMC_REM9_5                         (0xFFFFC414U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 5) */
#define REG_SMC_REM10_5                        (0xFFFFC418U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 5) */
#define REG_SMC_REM11_5                        (0xFFFFC41CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 5) */
#define REG_SMC_REM0_6                         (0xFFFFC430U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 6) */
#define REG_SMC_REM1_6                         (0xFFFFC434U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 6) */
#define REG_SMC_REM2_6                         (0xFFFFC438U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 6) */
#define REG_SMC_REM3_6                         (0xFFFFC43CU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 6) */
#define REG_SMC_REM4_6                         (0xFFFFC440U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 6) */
#define REG_SMC_REM5_6                         (0xFFFFC444U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 6) */
#define REG_SMC_REM6_6                         (0xFFFFC448U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 6) */
#define REG_SMC_REM7_6                         (0xFFFFC44CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 6) */
#define REG_SMC_REM8_6                         (0xFFFFC450U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 6) */
#define REG_SMC_REM9_6                         (0xFFFFC454U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 6) */
#define REG_SMC_REM10_6                        (0xFFFFC458U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 6) */
#define REG_SMC_REM11_6                        (0xFFFFC45CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 6) */
#define REG_SMC_REM0_7                         (0xFFFFC470U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 7) */
#define REG_SMC_REM1_7                         (0xFFFFC474U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 7) */
#define REG_SMC_REM2_7                         (0xFFFFC478U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 7) */
#define REG_SMC_REM3_7                         (0xFFFFC47CU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 7) */
#define REG_SMC_REM4_7                         (0xFFFFC480U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 7) */
#define REG_SMC_REM5_7                         (0xFFFFC484U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 7) */
#define REG_SMC_REM6_7                         (0xFFFFC488U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 7) */
#define REG_SMC_REM7_7                         (0xFFFFC48CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 7) */
#define REG_SMC_REM8_7                         (0xFFFFC490U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 7) */
#define REG_SMC_REM9_7                         (0xFFFFC494U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 7) */
#define REG_SMC_REM10_7                        (0xFFFFC498U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 7) */
#define REG_SMC_REM11_7                        (0xFFFFC49CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 7) */
#define REG_SMC_ELCFG                          (0xFFFFC500U) /**< \brief (SMC) PMECCError Location Configuration Register */
#define REG_SMC_ELPRIM                         (0xFFFFC504U) /**< \brief (SMC) PMECC Error Location Primitive Register */
#define REG_SMC_ELEN                           (0xFFFFC508U) /**< \brief (SMC) PMECC Error Location Enable Register */
#define REG_SMC_ELDIS                          (0xFFFFC50CU) /**< \brief (SMC) PMECC Error Location Disable Register */
#define REG_SMC_ELSR                           (0xFFFFC510U) /**< \brief (SMC) PMECC Error Location Status Register */
#define REG_SMC_ELIER                          (0xFFFFC514U) /**< \brief (SMC) PMECC Error Location Interrupt Enable register */
#define REG_SMC_ELIDR                          (0xFFFFC518U) /**< \brief (SMC) PMECC Error Location Interrupt Disable Register */
#define REG_SMC_ELIMR                          (0xFFFFC51CU) /**< \brief (SMC) PMECC Error Location Interrupt Mask Register */
#define REG_SMC_ELISR                          (0xFFFFC520U) /**< \brief (SMC) PMECC Error Location Interrupt Status Register */
#define REG_SMC_SIGMA0                         (0xFFFFC528U) /**< \brief (SMC) PMECC Error Location SIGMA 0 Register */
#define REG_SMC_SIGMA1                         (0xFFFFC52CU) /**< \brief (SMC) PMECC Error Location SIGMA 1 Register */
#define REG_SMC_SIGMA2                         (0xFFFFC530U) /**< \brief (SMC) PMECC Error Location SIGMA 2 Register */
#define REG_SMC_SIGMA3                         (0xFFFFC534U) /**< \brief (SMC) PMECC Error Location SIGMA 3 Register */
#define REG_SMC_SIGMA4                         (0xFFFFC538U) /**< \brief (SMC) PMECC Error Location SIGMA 4 Register */
#define REG_SMC_SIGMA5                         (0xFFFFC53CU) /**< \brief (SMC) PMECC Error Location SIGMA 5 Register */
#define REG_SMC_SIGMA6                         (0xFFFFC540U) /**< \brief (SMC) PMECC Error Location SIGMA 6 Register */
#define REG_SMC_SIGMA7                         (0xFFFFC544U) /**< \brief (SMC) PMECC Error Location SIGMA 7 Register */
#define REG_SMC_SIGMA8                         (0xFFFFC548U) /**< \brief (SMC) PMECC Error Location SIGMA 8 Register */
#define REG_SMC_SIGMA9                         (0xFFFFC54CU) /**< \brief (SMC) PMECC Error Location SIGMA 9 Register */
#define REG_SMC_SIGMA10                        (0xFFFFC550U) /**< \brief (SMC) PMECC Error Location SIGMA 10 Register */
#define REG_SMC_SIGMA11                        (0xFFFFC554U) /**< \brief (SMC) PMECC Error Location SIGMA 11 Register */
#define REG_SMC_SIGMA12                        (0xFFFFC558U) /**< \brief (SMC) PMECC Error Location SIGMA 12 Register */
#define REG_SMC_SIGMA13                        (0xFFFFC55CU) /**< \brief (SMC) PMECC Error Location SIGMA 13 Register */
#define REG_SMC_SIGMA14                        (0xFFFFC560U) /**< \brief (SMC) PMECC Error Location SIGMA 14 Register */
#define REG_SMC_SIGMA15                        (0xFFFFC564U) /**< \brief (SMC) PMECC Error Location SIGMA 15 Register */
#define REG_SMC_SIGMA16                        (0xFFFFC568U) /**< \brief (SMC) PMECC Error Location SIGMA 16 Register */
#define REG_SMC_SIGMA17                        (0xFFFFC56CU) /**< \brief (SMC) PMECC Error Location SIGMA 17 Register */
#define REG_SMC_SIGMA18                        (0xFFFFC570U) /**< \brief (SMC) PMECC Error Location SIGMA 18 Register */
#define REG_SMC_SIGMA19                        (0xFFFFC574U) /**< \brief (SMC) PMECC Error Location SIGMA 19 Register */
#define REG_SMC_SIGMA20                        (0xFFFFC578U) /**< \brief (SMC) PMECC Error Location SIGMA 20 Register */
#define REG_SMC_SIGMA21                        (0xFFFFC57CU) /**< \brief (SMC) PMECC Error Location SIGMA 21 Register */
#define REG_SMC_SIGMA22                        (0xFFFFC580U) /**< \brief (SMC) PMECC Error Location SIGMA 22 Register */
#define REG_SMC_SIGMA23                        (0xFFFFC584U) /**< \brief (SMC) PMECC Error Location SIGMA 23 Register */
#define REG_SMC_SIGMA24                        (0xFFFFC588U) /**< \brief (SMC) PMECC Error Location SIGMA 24 Register */
#define REG_SMC_ERRLOC                         (0xFFFFC58CU) /**< \brief (SMC) PMECC Error Location 0 Register */
#define REG_SMC_SETUP0                         (0xFFFFC600U) /**< \brief (SMC) SMC Setup Register (CS_number = 0) */
#define REG_SMC_PULSE0                         (0xFFFFC604U) /**< \brief (SMC) SMC Pulse Register (CS_number = 0) */
#define REG_SMC_CYCLE0                         (0xFFFFC608U) /**< \brief (SMC) SMC Cycle Register (CS_number = 0) */
#define REG_SMC_TIMINGS0                       (0xFFFFC60CU) /**< \brief (SMC) SMC Timings Register (CS_number = 0) */
#define REG_SMC_MODE0                          (0xFFFFC610U) /**< \brief (SMC) SMC Mode Register (CS_number = 0) */
#define REG_SMC_SETUP1                         (0xFFFFC614U) /**< \brief (SMC) SMC Setup Register (CS_number = 1) */
#define REG_SMC_PULSE1                         (0xFFFFC618U) /**< \brief (SMC) SMC Pulse Register (CS_number = 1) */
#define REG_SMC_CYCLE1                         (0xFFFFC61CU) /**< \brief (SMC) SMC Cycle Register (CS_number = 1) */
#define REG_SMC_TIMINGS1                       (0xFFFFC620U) /**< \brief (SMC) SMC Timings Register (CS_number = 1) */
#define REG_SMC_MODE1                          (0xFFFFC624U) /**< \brief (SMC) SMC Mode Register (CS_number = 1) */
#define REG_SMC_SETUP2                         (0xFFFFC628U) /**< \brief (SMC) SMC Setup Register (CS_number = 2) */
#define REG_SMC_PULSE2                         (0xFFFFC62CU) /**< \brief (SMC) SMC Pulse Register (CS_number = 2) */
#define REG_SMC_CYCLE2                         (0xFFFFC630U) /**< \brief (SMC) SMC Cycle Register (CS_number = 2) */
#define REG_SMC_TIMINGS2                       (0xFFFFC634U) /**< \brief (SMC) SMC Timings Register (CS_number = 2) */
#define REG_SMC_MODE2                          (0xFFFFC638U) /**< \brief (SMC) SMC Mode Register (CS_number = 2) */
#define REG_SMC_SETUP3                         (0xFFFFC63CU) /**< \brief (SMC) SMC Setup Register (CS_number = 3) */
#define REG_SMC_PULSE3                         (0xFFFFC640U) /**< \brief (SMC) SMC Pulse Register (CS_number = 3) */
#define REG_SMC_CYCLE3                         (0xFFFFC644U) /**< \brief (SMC) SMC Cycle Register (CS_number = 3) */
#define REG_SMC_TIMINGS3                       (0xFFFFC648U) /**< \brief (SMC) SMC Timings Register (CS_number = 3) */
#define REG_SMC_MODE3                          (0xFFFFC64CU) /**< \brief (SMC) SMC Mode Register (CS_number = 3) */
#define REG_SMC_OCMS                           (0xFFFFC6A0U) /**< \brief (SMC) SMC OCMS Register */
#define REG_SMC_KEY1                           (0xFFFFC6A4U) /**< \brief (SMC) SMC OCMS KEY1 Register */
#define REG_SMC_KEY2                           (0xFFFFC6A8U) /**< \brief (SMC) SMC OCMS KEY2 Register */
#define REG_SMC_WPCR                           (0xFFFFC6E4U) /**< \brief (SMC) SMC Write Protection Control Register */
#define REG_SMC_WPSR                           (0xFFFFC6E8U) /**< \brief (SMC) SMC Write Protection Status Register */
#else
#define REG_SMC_CFG                   (*(RwReg*)0xFFFFC000U) /**< \brief (SMC) SMC NFC Configuration Register */
#define REG_SMC_CTRL                  (*(WoReg*)0xFFFFC004U) /**< \brief (SMC) SMC NFC Control Register */
#define REG_SMC_SR                    (*(RoReg*)0xFFFFC008U) /**< \brief (SMC) SMC NFC Status Register */
#define REG_SMC_IER                   (*(WoReg*)0xFFFFC00CU) /**< \brief (SMC) SMC NFC Interrupt Enable Register */
#define REG_SMC_IDR                   (*(WoReg*)0xFFFFC010U) /**< \brief (SMC) SMC NFC Interrupt Disable Register */
#define REG_SMC_IMR                   (*(RoReg*)0xFFFFC014U) /**< \brief (SMC) SMC NFC Interrupt Mask Register */
#define REG_SMC_ADDR                  (*(RwReg*)0xFFFFC018U) /**< \brief (SMC) SMC NFC Address Cycle Zero Register */
#define REG_SMC_BANK                  (*(RwReg*)0xFFFFC01CU) /**< \brief (SMC) SMC Bank Address Register */
#define REG_SMC_ECC_CTRL              (*(WoReg*)0xFFFFC020U) /**< \brief (SMC) SMC ECC Control Register */
#define REG_SMC_ECC_MD                (*(RwReg*)0xFFFFC024U) /**< \brief (SMC) SMC ECC Mode Register */
#define REG_SMC_ECC_SR1               (*(RoReg*)0xFFFFC028U) /**< \brief (SMC) SMC ECC Status 1 Register */
#define REG_SMC_ECC_PR0               (*(RoReg*)0xFFFFC02CU) /**< \brief (SMC) SMC ECC Parity 0 Register */
#define REG_SMC_ECC_PR1               (*(RoReg*)0xFFFFC030U) /**< \brief (SMC) SMC ECC parity 1 Register */
#define REG_SMC_ECC_SR2               (*(RoReg*)0xFFFFC034U) /**< \brief (SMC) SMC ECC status 2 Register */
#define REG_SMC_ECC_PR2               (*(RoReg*)0xFFFFC038U) /**< \brief (SMC) SMC ECC parity 2 Register */
#define REG_SMC_ECC_PR3               (*(RoReg*)0xFFFFC03CU) /**< \brief (SMC) SMC ECC parity 3 Register */
#define REG_SMC_ECC_PR4               (*(RoReg*)0xFFFFC040U) /**< \brief (SMC) SMC ECC parity 4 Register */
#define REG_SMC_ECC_PR5               (*(RoReg*)0xFFFFC044U) /**< \brief (SMC) SMC ECC parity 5 Register */
#define REG_SMC_ECC_PR6               (*(RoReg*)0xFFFFC048U) /**< \brief (SMC) SMC ECC parity 6 Register */
#define REG_SMC_ECC_PR7               (*(RoReg*)0xFFFFC04CU) /**< \brief (SMC) SMC ECC parity 7 Register */
#define REG_SMC_ECC_PR8               (*(RoReg*)0xFFFFC050U) /**< \brief (SMC) SMC ECC parity 8 Register */
#define REG_SMC_ECC_PR9               (*(RoReg*)0xFFFFC054U) /**< \brief (SMC) SMC ECC parity 9 Register */
#define REG_SMC_ECC_PR10              (*(RoReg*)0xFFFFC058U) /**< \brief (SMC) SMC ECC parity 10 Register */
#define REG_SMC_ECC_PR11              (*(RoReg*)0xFFFFC05CU) /**< \brief (SMC) SMC ECC parity 11 Register */
#define REG_SMC_ECC_PR12              (*(RoReg*)0xFFFFC060U) /**< \brief (SMC) SMC ECC parity 12 Register */
#define REG_SMC_ECC_PR13              (*(RoReg*)0xFFFFC064U) /**< \brief (SMC) SMC ECC parity 13 Register */
#define REG_SMC_ECC_PR14              (*(RoReg*)0xFFFFC068U) /**< \brief (SMC) SMC ECC parity 14 Register */
#define REG_SMC_ECC_PR15              (*(RoReg*)0xFFFFC06CU) /**< \brief (SMC) SMC ECC parity 15 Register */
#define REG_SMC_PMECCFG               (*(RwReg*)0xFFFFC070U) /**< \brief (SMC) PMECC Configuration Register */
#define REG_SMC_PMECCSAREA            (*(RwReg*)0xFFFFC074U) /**< \brief (SMC) PMECC Spare Area Size Register */
#define REG_SMC_PMECCSADDR            (*(RwReg*)0xFFFFC078U) /**< \brief (SMC) PMECC Start Address Register */
#define REG_SMC_PMECCEADDR            (*(RwReg*)0xFFFFC07CU) /**< \brief (SMC) PMECC End Address Register */
#define REG_SMC_PMECCTRL              (*(WoReg*)0xFFFFC084U) /**< \brief (SMC) PMECC Control Register */
#define REG_SMC_PMECCSR               (*(RoReg*)0xFFFFC088U) /**< \brief (SMC) PMECC Status Register */
#define REG_SMC_PMECCIER              (*(WoReg*)0xFFFFC08CU) /**< \brief (SMC) PMECC Interrupt Enable register */
#define REG_SMC_PMECCIDR              (*(WoReg*)0xFFFFC090U) /**< \brief (SMC) PMECC Interrupt Disable Register */
#define REG_SMC_PMECCIMR              (*(RoReg*)0xFFFFC094U) /**< \brief (SMC) PMECC Interrupt Mask Register */
#define REG_SMC_PMECCISR              (*(RoReg*)0xFFFFC098U) /**< \brief (SMC) PMECC Interrupt Status Register */
#define REG_SMC_PMECC0_0              (*(RoReg*)0xFFFFC0B0U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 0) */
#define REG_SMC_PMECC1_0              (*(RoReg*)0xFFFFC0B4U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 0) */
#define REG_SMC_PMECC2_0              (*(RoReg*)0xFFFFC0B8U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 0) */
#define REG_SMC_PMECC3_0              (*(RoReg*)0xFFFFC0BCU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 0) */
#define REG_SMC_PMECC4_0              (*(RoReg*)0xFFFFC0C0U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 0) */
#define REG_SMC_PMECC5_0              (*(RoReg*)0xFFFFC0C4U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 0) */
#define REG_SMC_PMECC6_0              (*(RoReg*)0xFFFFC0C8U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 0) */
#define REG_SMC_PMECC7_0              (*(RoReg*)0xFFFFC0CCU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 0) */
#define REG_SMC_PMECC8_0              (*(RoReg*)0xFFFFC0D0U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 0) */
#define REG_SMC_PMECC9_0              (*(RoReg*)0xFFFFC0D4U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 0) */
#define REG_SMC_PMECC10_0             (*(RoReg*)0xFFFFC0D8U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 0) */
#define REG_SMC_PMECC0_1              (*(RoReg*)0xFFFFC0F0U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 1) */
#define REG_SMC_PMECC1_1              (*(RoReg*)0xFFFFC0F4U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 1) */
#define REG_SMC_PMECC2_1              (*(RoReg*)0xFFFFC0F8U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 1) */
#define REG_SMC_PMECC3_1              (*(RoReg*)0xFFFFC0FCU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 1) */
#define REG_SMC_PMECC4_1              (*(RoReg*)0xFFFFC100U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 1) */
#define REG_SMC_PMECC5_1              (*(RoReg*)0xFFFFC104U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 1) */
#define REG_SMC_PMECC6_1              (*(RoReg*)0xFFFFC108U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 1) */
#define REG_SMC_PMECC7_1              (*(RoReg*)0xFFFFC10CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 1) */
#define REG_SMC_PMECC8_1              (*(RoReg*)0xFFFFC110U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 1) */
#define REG_SMC_PMECC9_1              (*(RoReg*)0xFFFFC114U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 1) */
#define REG_SMC_PMECC10_1             (*(RoReg*)0xFFFFC118U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 1) */
#define REG_SMC_PMECC0_2              (*(RoReg*)0xFFFFC130U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 2) */
#define REG_SMC_PMECC1_2              (*(RoReg*)0xFFFFC134U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 2) */
#define REG_SMC_PMECC2_2              (*(RoReg*)0xFFFFC138U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 2) */
#define REG_SMC_PMECC3_2              (*(RoReg*)0xFFFFC13CU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 2) */
#define REG_SMC_PMECC4_2              (*(RoReg*)0xFFFFC140U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 2) */
#define REG_SMC_PMECC5_2              (*(RoReg*)0xFFFFC144U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 2) */
#define REG_SMC_PMECC6_2              (*(RoReg*)0xFFFFC148U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 2) */
#define REG_SMC_PMECC7_2              (*(RoReg*)0xFFFFC14CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 2) */
#define REG_SMC_PMECC8_2              (*(RoReg*)0xFFFFC150U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 2) */
#define REG_SMC_PMECC9_2              (*(RoReg*)0xFFFFC154U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 2) */
#define REG_SMC_PMECC10_2             (*(RoReg*)0xFFFFC158U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 2) */
#define REG_SMC_PMECC0_3              (*(RoReg*)0xFFFFC170U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 3) */
#define REG_SMC_PMECC1_3              (*(RoReg*)0xFFFFC174U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 3) */
#define REG_SMC_PMECC2_3              (*(RoReg*)0xFFFFC178U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 3) */
#define REG_SMC_PMECC3_3              (*(RoReg*)0xFFFFC17CU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 3) */
#define REG_SMC_PMECC4_3              (*(RoReg*)0xFFFFC180U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 3) */
#define REG_SMC_PMECC5_3              (*(RoReg*)0xFFFFC184U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 3) */
#define REG_SMC_PMECC6_3              (*(RoReg*)0xFFFFC188U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 3) */
#define REG_SMC_PMECC7_3              (*(RoReg*)0xFFFFC18CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 3) */
#define REG_SMC_PMECC8_3              (*(RoReg*)0xFFFFC190U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 3) */
#define REG_SMC_PMECC9_3              (*(RoReg*)0xFFFFC194U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 3) */
#define REG_SMC_PMECC10_3             (*(RoReg*)0xFFFFC198U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 3) */
#define REG_SMC_PMECC0_4              (*(RoReg*)0xFFFFC1B0U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 4) */
#define REG_SMC_PMECC1_4              (*(RoReg*)0xFFFFC1B4U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 4) */
#define REG_SMC_PMECC2_4              (*(RoReg*)0xFFFFC1B8U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 4) */
#define REG_SMC_PMECC3_4              (*(RoReg*)0xFFFFC1BCU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 4) */
#define REG_SMC_PMECC4_4              (*(RoReg*)0xFFFFC1C0U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 4) */
#define REG_SMC_PMECC5_4              (*(RoReg*)0xFFFFC1C4U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 4) */
#define REG_SMC_PMECC6_4              (*(RoReg*)0xFFFFC1C8U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 4) */
#define REG_SMC_PMECC7_4              (*(RoReg*)0xFFFFC1CCU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 4) */
#define REG_SMC_PMECC8_4              (*(RoReg*)0xFFFFC1D0U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 4) */
#define REG_SMC_PMECC9_4              (*(RoReg*)0xFFFFC1D4U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 4) */
#define REG_SMC_PMECC10_4             (*(RoReg*)0xFFFFC1D8U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 4) */
#define REG_SMC_PMECC0_5              (*(RoReg*)0xFFFFC1F0U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 5) */
#define REG_SMC_PMECC1_5              (*(RoReg*)0xFFFFC1F4U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 5) */
#define REG_SMC_PMECC2_5              (*(RoReg*)0xFFFFC1F8U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 5) */
#define REG_SMC_PMECC3_5              (*(RoReg*)0xFFFFC1FCU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 5) */
#define REG_SMC_PMECC4_5              (*(RoReg*)0xFFFFC200U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 5) */
#define REG_SMC_PMECC5_5              (*(RoReg*)0xFFFFC204U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 5) */
#define REG_SMC_PMECC6_5              (*(RoReg*)0xFFFFC208U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 5) */
#define REG_SMC_PMECC7_5              (*(RoReg*)0xFFFFC20CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 5) */
#define REG_SMC_PMECC8_5              (*(RoReg*)0xFFFFC210U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 5) */
#define REG_SMC_PMECC9_5              (*(RoReg*)0xFFFFC214U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 5) */
#define REG_SMC_PMECC10_5             (*(RoReg*)0xFFFFC218U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 5) */
#define REG_SMC_PMECC0_6              (*(RoReg*)0xFFFFC230U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 6) */
#define REG_SMC_PMECC1_6              (*(RoReg*)0xFFFFC234U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 6) */
#define REG_SMC_PMECC2_6              (*(RoReg*)0xFFFFC238U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 6) */
#define REG_SMC_PMECC3_6              (*(RoReg*)0xFFFFC23CU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 6) */
#define REG_SMC_PMECC4_6              (*(RoReg*)0xFFFFC240U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 6) */
#define REG_SMC_PMECC5_6              (*(RoReg*)0xFFFFC244U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 6) */
#define REG_SMC_PMECC6_6              (*(RoReg*)0xFFFFC248U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 6) */
#define REG_SMC_PMECC7_6              (*(RoReg*)0xFFFFC24CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 6) */
#define REG_SMC_PMECC8_6              (*(RoReg*)0xFFFFC250U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 6) */
#define REG_SMC_PMECC9_6              (*(RoReg*)0xFFFFC254U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 6) */
#define REG_SMC_PMECC10_6             (*(RoReg*)0xFFFFC258U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 6) */
#define REG_SMC_PMECC0_7              (*(RoReg*)0xFFFFC270U) /**< \brief (SMC) PMECC Redundancy 0 Register (sec_num = 7) */
#define REG_SMC_PMECC1_7              (*(RoReg*)0xFFFFC274U) /**< \brief (SMC) PMECC Redundancy 1 Register (sec_num = 7) */
#define REG_SMC_PMECC2_7              (*(RoReg*)0xFFFFC278U) /**< \brief (SMC) PMECC Redundancy 2 Register (sec_num = 7) */
#define REG_SMC_PMECC3_7              (*(RoReg*)0xFFFFC27CU) /**< \brief (SMC) PMECC Redundancy 3 Register (sec_num = 7) */
#define REG_SMC_PMECC4_7              (*(RoReg*)0xFFFFC280U) /**< \brief (SMC) PMECC Redundancy 4 Register (sec_num = 7) */
#define REG_SMC_PMECC5_7              (*(RoReg*)0xFFFFC284U) /**< \brief (SMC) PMECC Redundancy 5 Register (sec_num = 7) */
#define REG_SMC_PMECC6_7              (*(RoReg*)0xFFFFC288U) /**< \brief (SMC) PMECC Redundancy 6 Register (sec_num = 7) */
#define REG_SMC_PMECC7_7              (*(RoReg*)0xFFFFC28CU) /**< \brief (SMC) PMECC Redundancy 7 Register (sec_num = 7) */
#define REG_SMC_PMECC8_7              (*(RoReg*)0xFFFFC290U) /**< \brief (SMC) PMECC Redundancy 8 Register (sec_num = 7) */
#define REG_SMC_PMECC9_7              (*(RoReg*)0xFFFFC294U) /**< \brief (SMC) PMECC Redundancy 9 Register (sec_num = 7) */
#define REG_SMC_PMECC10_7             (*(RoReg*)0xFFFFC298U) /**< \brief (SMC) PMECC Redundancy 10 Register (sec_num = 7) */
#define REG_SMC_REM0_0                (*(RoReg*)0xFFFFC2B0U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 0) */
#define REG_SMC_REM1_0                (*(RoReg*)0xFFFFC2B4U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 0) */
#define REG_SMC_REM2_0                (*(RoReg*)0xFFFFC2B8U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 0) */
#define REG_SMC_REM3_0                (*(RoReg*)0xFFFFC2BCU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 0) */
#define REG_SMC_REM4_0                (*(RoReg*)0xFFFFC2C0U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 0) */
#define REG_SMC_REM5_0                (*(RoReg*)0xFFFFC2C4U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 0) */
#define REG_SMC_REM6_0                (*(RoReg*)0xFFFFC2C8U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 0) */
#define REG_SMC_REM7_0                (*(RoReg*)0xFFFFC2CCU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 0) */
#define REG_SMC_REM8_0                (*(RoReg*)0xFFFFC2D0U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 0) */
#define REG_SMC_REM9_0                (*(RoReg*)0xFFFFC2D4U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 0) */
#define REG_SMC_REM10_0               (*(RoReg*)0xFFFFC2D8U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 0) */
#define REG_SMC_REM11_0               (*(RoReg*)0xFFFFC2DCU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 0) */
#define REG_SMC_REM0_1                (*(RoReg*)0xFFFFC2F0U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 1) */
#define REG_SMC_REM1_1                (*(RoReg*)0xFFFFC2F4U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 1) */
#define REG_SMC_REM2_1                (*(RoReg*)0xFFFFC2F8U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 1) */
#define REG_SMC_REM3_1                (*(RoReg*)0xFFFFC2FCU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 1) */
#define REG_SMC_REM4_1                (*(RoReg*)0xFFFFC300U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 1) */
#define REG_SMC_REM5_1                (*(RoReg*)0xFFFFC304U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 1) */
#define REG_SMC_REM6_1                (*(RoReg*)0xFFFFC308U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 1) */
#define REG_SMC_REM7_1                (*(RoReg*)0xFFFFC30CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 1) */
#define REG_SMC_REM8_1                (*(RoReg*)0xFFFFC310U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 1) */
#define REG_SMC_REM9_1                (*(RoReg*)0xFFFFC314U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 1) */
#define REG_SMC_REM10_1               (*(RoReg*)0xFFFFC318U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 1) */
#define REG_SMC_REM11_1               (*(RoReg*)0xFFFFC31CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 1) */
#define REG_SMC_REM0_2                (*(RoReg*)0xFFFFC330U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 2) */
#define REG_SMC_REM1_2                (*(RoReg*)0xFFFFC334U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 2) */
#define REG_SMC_REM2_2                (*(RoReg*)0xFFFFC338U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 2) */
#define REG_SMC_REM3_2                (*(RoReg*)0xFFFFC33CU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 2) */
#define REG_SMC_REM4_2                (*(RoReg*)0xFFFFC340U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 2) */
#define REG_SMC_REM5_2                (*(RoReg*)0xFFFFC344U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 2) */
#define REG_SMC_REM6_2                (*(RoReg*)0xFFFFC348U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 2) */
#define REG_SMC_REM7_2                (*(RoReg*)0xFFFFC34CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 2) */
#define REG_SMC_REM8_2                (*(RoReg*)0xFFFFC350U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 2) */
#define REG_SMC_REM9_2                (*(RoReg*)0xFFFFC354U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 2) */
#define REG_SMC_REM10_2               (*(RoReg*)0xFFFFC358U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 2) */
#define REG_SMC_REM11_2               (*(RoReg*)0xFFFFC35CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 2) */
#define REG_SMC_REM0_3                (*(RoReg*)0xFFFFC370U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 3) */
#define REG_SMC_REM1_3                (*(RoReg*)0xFFFFC374U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 3) */
#define REG_SMC_REM2_3                (*(RoReg*)0xFFFFC378U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 3) */
#define REG_SMC_REM3_3                (*(RoReg*)0xFFFFC37CU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 3) */
#define REG_SMC_REM4_3                (*(RoReg*)0xFFFFC380U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 3) */
#define REG_SMC_REM5_3                (*(RoReg*)0xFFFFC384U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 3) */
#define REG_SMC_REM6_3                (*(RoReg*)0xFFFFC388U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 3) */
#define REG_SMC_REM7_3                (*(RoReg*)0xFFFFC38CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 3) */
#define REG_SMC_REM8_3                (*(RoReg*)0xFFFFC390U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 3) */
#define REG_SMC_REM9_3                (*(RoReg*)0xFFFFC394U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 3) */
#define REG_SMC_REM10_3               (*(RoReg*)0xFFFFC398U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 3) */
#define REG_SMC_REM11_3               (*(RoReg*)0xFFFFC39CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 3) */
#define REG_SMC_REM0_4                (*(RoReg*)0xFFFFC3B0U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 4) */
#define REG_SMC_REM1_4                (*(RoReg*)0xFFFFC3B4U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 4) */
#define REG_SMC_REM2_4                (*(RoReg*)0xFFFFC3B8U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 4) */
#define REG_SMC_REM3_4                (*(RoReg*)0xFFFFC3BCU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 4) */
#define REG_SMC_REM4_4                (*(RoReg*)0xFFFFC3C0U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 4) */
#define REG_SMC_REM5_4                (*(RoReg*)0xFFFFC3C4U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 4) */
#define REG_SMC_REM6_4                (*(RoReg*)0xFFFFC3C8U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 4) */
#define REG_SMC_REM7_4                (*(RoReg*)0xFFFFC3CCU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 4) */
#define REG_SMC_REM8_4                (*(RoReg*)0xFFFFC3D0U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 4) */
#define REG_SMC_REM9_4                (*(RoReg*)0xFFFFC3D4U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 4) */
#define REG_SMC_REM10_4               (*(RoReg*)0xFFFFC3D8U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 4) */
#define REG_SMC_REM11_4               (*(RoReg*)0xFFFFC3DCU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 4) */
#define REG_SMC_REM0_5                (*(RoReg*)0xFFFFC3F0U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 5) */
#define REG_SMC_REM1_5                (*(RoReg*)0xFFFFC3F4U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 5) */
#define REG_SMC_REM2_5                (*(RoReg*)0xFFFFC3F8U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 5) */
#define REG_SMC_REM3_5                (*(RoReg*)0xFFFFC3FCU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 5) */
#define REG_SMC_REM4_5                (*(RoReg*)0xFFFFC400U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 5) */
#define REG_SMC_REM5_5                (*(RoReg*)0xFFFFC404U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 5) */
#define REG_SMC_REM6_5                (*(RoReg*)0xFFFFC408U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 5) */
#define REG_SMC_REM7_5                (*(RoReg*)0xFFFFC40CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 5) */
#define REG_SMC_REM8_5                (*(RoReg*)0xFFFFC410U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 5) */
#define REG_SMC_REM9_5                (*(RoReg*)0xFFFFC414U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 5) */
#define REG_SMC_REM10_5               (*(RoReg*)0xFFFFC418U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 5) */
#define REG_SMC_REM11_5               (*(RoReg*)0xFFFFC41CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 5) */
#define REG_SMC_REM0_6                (*(RoReg*)0xFFFFC430U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 6) */
#define REG_SMC_REM1_6                (*(RoReg*)0xFFFFC434U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 6) */
#define REG_SMC_REM2_6                (*(RoReg*)0xFFFFC438U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 6) */
#define REG_SMC_REM3_6                (*(RoReg*)0xFFFFC43CU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 6) */
#define REG_SMC_REM4_6                (*(RoReg*)0xFFFFC440U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 6) */
#define REG_SMC_REM5_6                (*(RoReg*)0xFFFFC444U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 6) */
#define REG_SMC_REM6_6                (*(RoReg*)0xFFFFC448U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 6) */
#define REG_SMC_REM7_6                (*(RoReg*)0xFFFFC44CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 6) */
#define REG_SMC_REM8_6                (*(RoReg*)0xFFFFC450U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 6) */
#define REG_SMC_REM9_6                (*(RoReg*)0xFFFFC454U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 6) */
#define REG_SMC_REM10_6               (*(RoReg*)0xFFFFC458U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 6) */
#define REG_SMC_REM11_6               (*(RoReg*)0xFFFFC45CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 6) */
#define REG_SMC_REM0_7                (*(RoReg*)0xFFFFC470U) /**< \brief (SMC) PMECC Remainder 0 Register (sec_num = 7) */
#define REG_SMC_REM1_7                (*(RoReg*)0xFFFFC474U) /**< \brief (SMC) PMECC Remainder 1 Register (sec_num = 7) */
#define REG_SMC_REM2_7                (*(RoReg*)0xFFFFC478U) /**< \brief (SMC) PMECC Remainder 2 Register (sec_num = 7) */
#define REG_SMC_REM3_7                (*(RoReg*)0xFFFFC47CU) /**< \brief (SMC) PMECC Remainder 3 Register (sec_num = 7) */
#define REG_SMC_REM4_7                (*(RoReg*)0xFFFFC480U) /**< \brief (SMC) PMECC Remainder 4 Register (sec_num = 7) */
#define REG_SMC_REM5_7                (*(RoReg*)0xFFFFC484U) /**< \brief (SMC) PMECC Remainder 5 Register (sec_num = 7) */
#define REG_SMC_REM6_7                (*(RoReg*)0xFFFFC488U) /**< \brief (SMC) PMECC Remainder 6 Register (sec_num = 7) */
#define REG_SMC_REM7_7                (*(RoReg*)0xFFFFC48CU) /**< \brief (SMC) PMECC Remainder 7 Register (sec_num = 7) */
#define REG_SMC_REM8_7                (*(RoReg*)0xFFFFC490U) /**< \brief (SMC) PMECC Remainder 8 Register (sec_num = 7) */
#define REG_SMC_REM9_7                (*(RoReg*)0xFFFFC494U) /**< \brief (SMC) PMECC Remainder 9 Register (sec_num = 7) */
#define REG_SMC_REM10_7               (*(RoReg*)0xFFFFC498U) /**< \brief (SMC) PMECC Remainder 10 Register (sec_num = 7) */
#define REG_SMC_REM11_7               (*(RoReg*)0xFFFFC49CU) /**< \brief (SMC) PMECC Remainder 11 Register (sec_num = 7) */
#define REG_SMC_ELCFG                 (*(RwReg*)0xFFFFC500U) /**< \brief (SMC) PMECCError Location Configuration Register */
#define REG_SMC_ELPRIM                (*(RoReg*)0xFFFFC504U) /**< \brief (SMC) PMECC Error Location Primitive Register */
#define REG_SMC_ELEN                  (*(WoReg*)0xFFFFC508U) /**< \brief (SMC) PMECC Error Location Enable Register */
#define REG_SMC_ELDIS                 (*(WoReg*)0xFFFFC50CU) /**< \brief (SMC) PMECC Error Location Disable Register */
#define REG_SMC_ELSR                  (*(RoReg*)0xFFFFC510U) /**< \brief (SMC) PMECC Error Location Status Register */
#define REG_SMC_ELIER                 (*(WoReg*)0xFFFFC514U) /**< \brief (SMC) PMECC Error Location Interrupt Enable register */
#define REG_SMC_ELIDR                 (*(WoReg*)0xFFFFC518U) /**< \brief (SMC) PMECC Error Location Interrupt Disable Register */
#define REG_SMC_ELIMR                 (*(RoReg*)0xFFFFC51CU) /**< \brief (SMC) PMECC Error Location Interrupt Mask Register */
#define REG_SMC_ELISR                 (*(RoReg*)0xFFFFC520U) /**< \brief (SMC) PMECC Error Location Interrupt Status Register */
#define REG_SMC_SIGMA0                (*(RwReg*)0xFFFFC528U) /**< \brief (SMC) PMECC Error Location SIGMA 0 Register */
#define REG_SMC_SIGMA1                (*(RwReg*)0xFFFFC52CU) /**< \brief (SMC) PMECC Error Location SIGMA 1 Register */
#define REG_SMC_SIGMA2                (*(RwReg*)0xFFFFC530U) /**< \brief (SMC) PMECC Error Location SIGMA 2 Register */
#define REG_SMC_SIGMA3                (*(RwReg*)0xFFFFC534U) /**< \brief (SMC) PMECC Error Location SIGMA 3 Register */
#define REG_SMC_SIGMA4                (*(RwReg*)0xFFFFC538U) /**< \brief (SMC) PMECC Error Location SIGMA 4 Register */
#define REG_SMC_SIGMA5                (*(RwReg*)0xFFFFC53CU) /**< \brief (SMC) PMECC Error Location SIGMA 5 Register */
#define REG_SMC_SIGMA6                (*(RwReg*)0xFFFFC540U) /**< \brief (SMC) PMECC Error Location SIGMA 6 Register */
#define REG_SMC_SIGMA7                (*(RwReg*)0xFFFFC544U) /**< \brief (SMC) PMECC Error Location SIGMA 7 Register */
#define REG_SMC_SIGMA8                (*(RwReg*)0xFFFFC548U) /**< \brief (SMC) PMECC Error Location SIGMA 8 Register */
#define REG_SMC_SIGMA9                (*(RwReg*)0xFFFFC54CU) /**< \brief (SMC) PMECC Error Location SIGMA 9 Register */
#define REG_SMC_SIGMA10               (*(RwReg*)0xFFFFC550U) /**< \brief (SMC) PMECC Error Location SIGMA 10 Register */
#define REG_SMC_SIGMA11               (*(RwReg*)0xFFFFC554U) /**< \brief (SMC) PMECC Error Location SIGMA 11 Register */
#define REG_SMC_SIGMA12               (*(RwReg*)0xFFFFC558U) /**< \brief (SMC) PMECC Error Location SIGMA 12 Register */
#define REG_SMC_SIGMA13               (*(RwReg*)0xFFFFC55CU) /**< \brief (SMC) PMECC Error Location SIGMA 13 Register */
#define REG_SMC_SIGMA14               (*(RwReg*)0xFFFFC560U) /**< \brief (SMC) PMECC Error Location SIGMA 14 Register */
#define REG_SMC_SIGMA15               (*(RwReg*)0xFFFFC564U) /**< \brief (SMC) PMECC Error Location SIGMA 15 Register */
#define REG_SMC_SIGMA16               (*(RwReg*)0xFFFFC568U) /**< \brief (SMC) PMECC Error Location SIGMA 16 Register */
#define REG_SMC_SIGMA17               (*(RwReg*)0xFFFFC56CU) /**< \brief (SMC) PMECC Error Location SIGMA 17 Register */
#define REG_SMC_SIGMA18               (*(RwReg*)0xFFFFC570U) /**< \brief (SMC) PMECC Error Location SIGMA 18 Register */
#define REG_SMC_SIGMA19               (*(RwReg*)0xFFFFC574U) /**< \brief (SMC) PMECC Error Location SIGMA 19 Register */
#define REG_SMC_SIGMA20               (*(RwReg*)0xFFFFC578U) /**< \brief (SMC) PMECC Error Location SIGMA 20 Register */
#define REG_SMC_SIGMA21               (*(RwReg*)0xFFFFC57CU) /**< \brief (SMC) PMECC Error Location SIGMA 21 Register */
#define REG_SMC_SIGMA22               (*(RwReg*)0xFFFFC580U) /**< \brief (SMC) PMECC Error Location SIGMA 22 Register */
#define REG_SMC_SIGMA23               (*(RwReg*)0xFFFFC584U) /**< \brief (SMC) PMECC Error Location SIGMA 23 Register */
#define REG_SMC_SIGMA24               (*(RwReg*)0xFFFFC588U) /**< \brief (SMC) PMECC Error Location SIGMA 24 Register */
#define REG_SMC_ERRLOC                (*(RoReg*)0xFFFFC58CU) /**< \brief (SMC) PMECC Error Location 0 Register */
#define REG_SMC_SETUP0                (*(RwReg*)0xFFFFC600U) /**< \brief (SMC) SMC Setup Register (CS_number = 0) */
#define REG_SMC_PULSE0                (*(RwReg*)0xFFFFC604U) /**< \brief (SMC) SMC Pulse Register (CS_number = 0) */
#define REG_SMC_CYCLE0                (*(RwReg*)0xFFFFC608U) /**< \brief (SMC) SMC Cycle Register (CS_number = 0) */
#define REG_SMC_TIMINGS0              (*(RwReg*)0xFFFFC60CU) /**< \brief (SMC) SMC Timings Register (CS_number = 0) */
#define REG_SMC_MODE0                 (*(RwReg*)0xFFFFC610U) /**< \brief (SMC) SMC Mode Register (CS_number = 0) */
#define REG_SMC_SETUP1                (*(RwReg*)0xFFFFC614U) /**< \brief (SMC) SMC Setup Register (CS_number = 1) */
#define REG_SMC_PULSE1                (*(RwReg*)0xFFFFC618U) /**< \brief (SMC) SMC Pulse Register (CS_number = 1) */
#define REG_SMC_CYCLE1                (*(RwReg*)0xFFFFC61CU) /**< \brief (SMC) SMC Cycle Register (CS_number = 1) */
#define REG_SMC_TIMINGS1              (*(RwReg*)0xFFFFC620U) /**< \brief (SMC) SMC Timings Register (CS_number = 1) */
#define REG_SMC_MODE1                 (*(RwReg*)0xFFFFC624U) /**< \brief (SMC) SMC Mode Register (CS_number = 1) */
#define REG_SMC_SETUP2                (*(RwReg*)0xFFFFC628U) /**< \brief (SMC) SMC Setup Register (CS_number = 2) */
#define REG_SMC_PULSE2                (*(RwReg*)0xFFFFC62CU) /**< \brief (SMC) SMC Pulse Register (CS_number = 2) */
#define REG_SMC_CYCLE2                (*(RwReg*)0xFFFFC630U) /**< \brief (SMC) SMC Cycle Register (CS_number = 2) */
#define REG_SMC_TIMINGS2              (*(RwReg*)0xFFFFC634U) /**< \brief (SMC) SMC Timings Register (CS_number = 2) */
#define REG_SMC_MODE2                 (*(RwReg*)0xFFFFC638U) /**< \brief (SMC) SMC Mode Register (CS_number = 2) */
#define REG_SMC_SETUP3                (*(RwReg*)0xFFFFC63CU) /**< \brief (SMC) SMC Setup Register (CS_number = 3) */
#define REG_SMC_PULSE3                (*(RwReg*)0xFFFFC640U) /**< \brief (SMC) SMC Pulse Register (CS_number = 3) */
#define REG_SMC_CYCLE3                (*(RwReg*)0xFFFFC644U) /**< \brief (SMC) SMC Cycle Register (CS_number = 3) */
#define REG_SMC_TIMINGS3              (*(RwReg*)0xFFFFC648U) /**< \brief (SMC) SMC Timings Register (CS_number = 3) */
#define REG_SMC_MODE3                 (*(RwReg*)0xFFFFC64CU) /**< \brief (SMC) SMC Mode Register (CS_number = 3) */
#define REG_SMC_OCMS                  (*(RwReg*)0xFFFFC6A0U) /**< \brief (SMC) SMC OCMS Register */
#define REG_SMC_KEY1                  (*(WoReg*)0xFFFFC6A4U) /**< \brief (SMC) SMC OCMS KEY1 Register */
#define REG_SMC_KEY2                  (*(WoReg*)0xFFFFC6A8U) /**< \brief (SMC) SMC OCMS KEY2 Register */
#define REG_SMC_WPCR                  (*(WoReg*)0xFFFFC6E4U) /**< \brief (SMC) SMC Write Protection Control Register */
#define REG_SMC_WPSR                  (*(RoReg*)0xFFFFC6E8U) /**< \brief (SMC) SMC Write Protection Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for FUSE peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_FUSE_CR                            (0xFFFFE400U) /**< \brief (FUSE) Fuse Control Register */
#define REG_FUSE_MR                            (0xFFFFE404U) /**< \brief (FUSE) Fuse Mode Register */
#define REG_FUSE_IR                            (0xFFFFE408U) /**< \brief (FUSE) Fuse Index Register */
#define REG_FUSE_DR                            (0xFFFFE40CU) /**< \brief (FUSE) Fuse Data Register */
#define REG_FUSE_SR                            (0xFFFFE410U) /**< \brief (FUSE) Fuse Status Register */
#else
#define REG_FUSE_CR                   (*(WoReg*)0xFFFFE400U) /**< \brief (FUSE) Fuse Control Register */
#define REG_FUSE_MR                   (*(WoReg*)0xFFFFE404U) /**< \brief (FUSE) Fuse Mode Register */
#define REG_FUSE_IR                   (*(RwReg*)0xFFFFE408U) /**< \brief (FUSE) Fuse Index Register */
#define REG_FUSE_DR                   (*(WoReg*)0xFFFFE40CU) /**< \brief (FUSE) Fuse Data Register */
#define REG_FUSE_SR                   (*(RoReg*)0xFFFFE410U) /**< \brief (FUSE) Fuse Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for DMAC0 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_DMAC0_GCFG                         (0xFFFFE600U) /**< \brief (DMAC0) DMAC Global Configuration Register */
#define REG_DMAC0_EN                           (0xFFFFE604U) /**< \brief (DMAC0) DMAC Enable Register */
#define REG_DMAC0_SREQ                         (0xFFFFE608U) /**< \brief (DMAC0) DMAC Software Single Request Register */
#define REG_DMAC0_CREQ                         (0xFFFFE60CU) /**< \brief (DMAC0) DMAC Software Chunk Transfer Request Register */
#define REG_DMAC0_LAST                         (0xFFFFE610U) /**< \brief (DMAC0) DMAC Software Last Transfer Flag Register */
#define REG_DMAC0_EBCIER                       (0xFFFFE618U) /**< \brief (DMAC0) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Enable register. */
#define REG_DMAC0_EBCIDR                       (0xFFFFE61CU) /**< \brief (DMAC0) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Disable register. */
#define REG_DMAC0_EBCIMR                       (0xFFFFE620U) /**< \brief (DMAC0) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Mask Register. */
#define REG_DMAC0_EBCISR                       (0xFFFFE624U) /**< \brief (DMAC0) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Status Register. */
#define REG_DMAC0_CHER                         (0xFFFFE628U) /**< \brief (DMAC0) DMAC Channel Handler Enable Register */
#define REG_DMAC0_CHDR                         (0xFFFFE62CU) /**< \brief (DMAC0) DMAC Channel Handler Disable Register */
#define REG_DMAC0_CHSR                         (0xFFFFE630U) /**< \brief (DMAC0) DMAC Channel Handler Status Register */
#define REG_DMAC0_SADDR0                       (0xFFFFE63CU) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 0) */
#define REG_DMAC0_DADDR0                       (0xFFFFE640U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 0) */
#define REG_DMAC0_DSCR0                        (0xFFFFE644U) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 0) */
#define REG_DMAC0_CTRLA0                       (0xFFFFE648U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 0) */
#define REG_DMAC0_CTRLB0                       (0xFFFFE64CU) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 0) */
#define REG_DMAC0_CFG0                         (0xFFFFE650U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 0) */
#define REG_DMAC0_SPIP0                        (0xFFFFE654U) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 0) */
#define REG_DMAC0_DPIP0                        (0xFFFFE658U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 0) */
#define REG_DMAC0_SADDR1                       (0xFFFFE664U) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 1) */
#define REG_DMAC0_DADDR1                       (0xFFFFE668U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 1) */
#define REG_DMAC0_DSCR1                        (0xFFFFE66CU) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 1) */
#define REG_DMAC0_CTRLA1                       (0xFFFFE670U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 1) */
#define REG_DMAC0_CTRLB1                       (0xFFFFE674U) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 1) */
#define REG_DMAC0_CFG1                         (0xFFFFE678U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 1) */
#define REG_DMAC0_SPIP1                        (0xFFFFE67CU) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 1) */
#define REG_DMAC0_DPIP1                        (0xFFFFE680U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 1) */
#define REG_DMAC0_SADDR2                       (0xFFFFE68CU) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 2) */
#define REG_DMAC0_DADDR2                       (0xFFFFE690U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 2) */
#define REG_DMAC0_DSCR2                        (0xFFFFE694U) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 2) */
#define REG_DMAC0_CTRLA2                       (0xFFFFE698U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 2) */
#define REG_DMAC0_CTRLB2                       (0xFFFFE69CU) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 2) */
#define REG_DMAC0_CFG2                         (0xFFFFE6A0U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 2) */
#define REG_DMAC0_SPIP2                        (0xFFFFE6A4U) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 2) */
#define REG_DMAC0_DPIP2                        (0xFFFFE6A8U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 2) */
#define REG_DMAC0_SADDR3                       (0xFFFFE6B4U) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 3) */
#define REG_DMAC0_DADDR3                       (0xFFFFE6B8U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 3) */
#define REG_DMAC0_DSCR3                        (0xFFFFE6BCU) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 3) */
#define REG_DMAC0_CTRLA3                       (0xFFFFE6C0U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 3) */
#define REG_DMAC0_CTRLB3                       (0xFFFFE6C4U) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 3) */
#define REG_DMAC0_CFG3                         (0xFFFFE6C8U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 3) */
#define REG_DMAC0_SPIP3                        (0xFFFFE6CCU) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 3) */
#define REG_DMAC0_DPIP3                        (0xFFFFE6D0U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 3) */
#define REG_DMAC0_SADDR4                       (0xFFFFE6DCU) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 4) */
#define REG_DMAC0_DADDR4                       (0xFFFFE6E0U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 4) */
#define REG_DMAC0_DSCR4                        (0xFFFFE6E4U) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 4) */
#define REG_DMAC0_CTRLA4                       (0xFFFFE6E8U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 4) */
#define REG_DMAC0_CTRLB4                       (0xFFFFE6ECU) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 4) */
#define REG_DMAC0_CFG4                         (0xFFFFE6F0U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 4) */
#define REG_DMAC0_SPIP4                        (0xFFFFE6F4U) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 4) */
#define REG_DMAC0_DPIP4                        (0xFFFFE6F8U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 4) */
#define REG_DMAC0_SADDR5                       (0xFFFFE704U) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 5) */
#define REG_DMAC0_DADDR5                       (0xFFFFE708U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 5) */
#define REG_DMAC0_DSCR5                        (0xFFFFE70CU) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 5) */
#define REG_DMAC0_CTRLA5                       (0xFFFFE710U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 5) */
#define REG_DMAC0_CTRLB5                       (0xFFFFE714U) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 5) */
#define REG_DMAC0_CFG5                         (0xFFFFE718U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 5) */
#define REG_DMAC0_SPIP5                        (0xFFFFE71CU) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 5) */
#define REG_DMAC0_DPIP5                        (0xFFFFE720U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 5) */
#define REG_DMAC0_SADDR6                       (0xFFFFE72CU) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 6) */
#define REG_DMAC0_DADDR6                       (0xFFFFE730U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 6) */
#define REG_DMAC0_DSCR6                        (0xFFFFE734U) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 6) */
#define REG_DMAC0_CTRLA6                       (0xFFFFE738U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 6) */
#define REG_DMAC0_CTRLB6                       (0xFFFFE73CU) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 6) */
#define REG_DMAC0_CFG6                         (0xFFFFE740U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 6) */
#define REG_DMAC0_SPIP6                        (0xFFFFE744U) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 6) */
#define REG_DMAC0_DPIP6                        (0xFFFFE748U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 6) */
#define REG_DMAC0_SADDR7                       (0xFFFFE754U) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 7) */
#define REG_DMAC0_DADDR7                       (0xFFFFE758U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 7) */
#define REG_DMAC0_DSCR7                        (0xFFFFE75CU) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 7) */
#define REG_DMAC0_CTRLA7                       (0xFFFFE760U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 7) */
#define REG_DMAC0_CTRLB7                       (0xFFFFE764U) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 7) */
#define REG_DMAC0_CFG7                         (0xFFFFE768U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 7) */
#define REG_DMAC0_SPIP7                        (0xFFFFE76CU) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 7) */
#define REG_DMAC0_DPIP7                        (0xFFFFE770U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 7) */
#define REG_DMAC0_WPMR                         (0xFFFFE7E4U) /**< \brief (DMAC0) DMAC Write Protect Mode Register */
#define REG_DMAC0_WPSR                         (0xFFFFE7E8U) /**< \brief (DMAC0) DMAC Write Protect Status Register */
#else
#define REG_DMAC0_GCFG                (*(RwReg*)0xFFFFE600U) /**< \brief (DMAC0) DMAC Global Configuration Register */
#define REG_DMAC0_EN                  (*(RwReg*)0xFFFFE604U) /**< \brief (DMAC0) DMAC Enable Register */
#define REG_DMAC0_SREQ                (*(RwReg*)0xFFFFE608U) /**< \brief (DMAC0) DMAC Software Single Request Register */
#define REG_DMAC0_CREQ                (*(RwReg*)0xFFFFE60CU) /**< \brief (DMAC0) DMAC Software Chunk Transfer Request Register */
#define REG_DMAC0_LAST                (*(RwReg*)0xFFFFE610U) /**< \brief (DMAC0) DMAC Software Last Transfer Flag Register */
#define REG_DMAC0_EBCIER              (*(WoReg*)0xFFFFE618U) /**< \brief (DMAC0) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Enable register. */
#define REG_DMAC0_EBCIDR              (*(WoReg*)0xFFFFE61CU) /**< \brief (DMAC0) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Disable register. */
#define REG_DMAC0_EBCIMR              (*(RoReg*)0xFFFFE620U) /**< \brief (DMAC0) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Mask Register. */
#define REG_DMAC0_EBCISR              (*(RoReg*)0xFFFFE624U) /**< \brief (DMAC0) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Status Register. */
#define REG_DMAC0_CHER                (*(WoReg*)0xFFFFE628U) /**< \brief (DMAC0) DMAC Channel Handler Enable Register */
#define REG_DMAC0_CHDR                (*(WoReg*)0xFFFFE62CU) /**< \brief (DMAC0) DMAC Channel Handler Disable Register */
#define REG_DMAC0_CHSR                (*(RoReg*)0xFFFFE630U) /**< \brief (DMAC0) DMAC Channel Handler Status Register */
#define REG_DMAC0_SADDR0              (*(RwReg*)0xFFFFE63CU) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 0) */
#define REG_DMAC0_DADDR0              (*(RwReg*)0xFFFFE640U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 0) */
#define REG_DMAC0_DSCR0               (*(RwReg*)0xFFFFE644U) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 0) */
#define REG_DMAC0_CTRLA0              (*(RwReg*)0xFFFFE648U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 0) */
#define REG_DMAC0_CTRLB0              (*(RwReg*)0xFFFFE64CU) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 0) */
#define REG_DMAC0_CFG0                (*(RwReg*)0xFFFFE650U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 0) */
#define REG_DMAC0_SPIP0               (*(RwReg*)0xFFFFE654U) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 0) */
#define REG_DMAC0_DPIP0               (*(RwReg*)0xFFFFE658U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 0) */
#define REG_DMAC0_SADDR1              (*(RwReg*)0xFFFFE664U) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 1) */
#define REG_DMAC0_DADDR1              (*(RwReg*)0xFFFFE668U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 1) */
#define REG_DMAC0_DSCR1               (*(RwReg*)0xFFFFE66CU) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 1) */
#define REG_DMAC0_CTRLA1              (*(RwReg*)0xFFFFE670U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 1) */
#define REG_DMAC0_CTRLB1              (*(RwReg*)0xFFFFE674U) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 1) */
#define REG_DMAC0_CFG1                (*(RwReg*)0xFFFFE678U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 1) */
#define REG_DMAC0_SPIP1               (*(RwReg*)0xFFFFE67CU) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 1) */
#define REG_DMAC0_DPIP1               (*(RwReg*)0xFFFFE680U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 1) */
#define REG_DMAC0_SADDR2              (*(RwReg*)0xFFFFE68CU) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 2) */
#define REG_DMAC0_DADDR2              (*(RwReg*)0xFFFFE690U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 2) */
#define REG_DMAC0_DSCR2               (*(RwReg*)0xFFFFE694U) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 2) */
#define REG_DMAC0_CTRLA2              (*(RwReg*)0xFFFFE698U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 2) */
#define REG_DMAC0_CTRLB2              (*(RwReg*)0xFFFFE69CU) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 2) */
#define REG_DMAC0_CFG2                (*(RwReg*)0xFFFFE6A0U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 2) */
#define REG_DMAC0_SPIP2               (*(RwReg*)0xFFFFE6A4U) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 2) */
#define REG_DMAC0_DPIP2               (*(RwReg*)0xFFFFE6A8U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 2) */
#define REG_DMAC0_SADDR3              (*(RwReg*)0xFFFFE6B4U) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 3) */
#define REG_DMAC0_DADDR3              (*(RwReg*)0xFFFFE6B8U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 3) */
#define REG_DMAC0_DSCR3               (*(RwReg*)0xFFFFE6BCU) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 3) */
#define REG_DMAC0_CTRLA3              (*(RwReg*)0xFFFFE6C0U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 3) */
#define REG_DMAC0_CTRLB3              (*(RwReg*)0xFFFFE6C4U) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 3) */
#define REG_DMAC0_CFG3                (*(RwReg*)0xFFFFE6C8U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 3) */
#define REG_DMAC0_SPIP3               (*(RwReg*)0xFFFFE6CCU) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 3) */
#define REG_DMAC0_DPIP3               (*(RwReg*)0xFFFFE6D0U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 3) */
#define REG_DMAC0_SADDR4              (*(RwReg*)0xFFFFE6DCU) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 4) */
#define REG_DMAC0_DADDR4              (*(RwReg*)0xFFFFE6E0U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 4) */
#define REG_DMAC0_DSCR4               (*(RwReg*)0xFFFFE6E4U) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 4) */
#define REG_DMAC0_CTRLA4              (*(RwReg*)0xFFFFE6E8U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 4) */
#define REG_DMAC0_CTRLB4              (*(RwReg*)0xFFFFE6ECU) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 4) */
#define REG_DMAC0_CFG4                (*(RwReg*)0xFFFFE6F0U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 4) */
#define REG_DMAC0_SPIP4               (*(RwReg*)0xFFFFE6F4U) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 4) */
#define REG_DMAC0_DPIP4               (*(RwReg*)0xFFFFE6F8U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 4) */
#define REG_DMAC0_SADDR5              (*(RwReg*)0xFFFFE704U) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 5) */
#define REG_DMAC0_DADDR5              (*(RwReg*)0xFFFFE708U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 5) */
#define REG_DMAC0_DSCR5               (*(RwReg*)0xFFFFE70CU) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 5) */
#define REG_DMAC0_CTRLA5              (*(RwReg*)0xFFFFE710U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 5) */
#define REG_DMAC0_CTRLB5              (*(RwReg*)0xFFFFE714U) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 5) */
#define REG_DMAC0_CFG5                (*(RwReg*)0xFFFFE718U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 5) */
#define REG_DMAC0_SPIP5               (*(RwReg*)0xFFFFE71CU) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 5) */
#define REG_DMAC0_DPIP5               (*(RwReg*)0xFFFFE720U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 5) */
#define REG_DMAC0_SADDR6              (*(RwReg*)0xFFFFE72CU) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 6) */
#define REG_DMAC0_DADDR6              (*(RwReg*)0xFFFFE730U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 6) */
#define REG_DMAC0_DSCR6               (*(RwReg*)0xFFFFE734U) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 6) */
#define REG_DMAC0_CTRLA6              (*(RwReg*)0xFFFFE738U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 6) */
#define REG_DMAC0_CTRLB6              (*(RwReg*)0xFFFFE73CU) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 6) */
#define REG_DMAC0_CFG6                (*(RwReg*)0xFFFFE740U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 6) */
#define REG_DMAC0_SPIP6               (*(RwReg*)0xFFFFE744U) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 6) */
#define REG_DMAC0_DPIP6               (*(RwReg*)0xFFFFE748U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 6) */
#define REG_DMAC0_SADDR7              (*(RwReg*)0xFFFFE754U) /**< \brief (DMAC0) DMAC Channel Source Address Register (ch_num = 7) */
#define REG_DMAC0_DADDR7              (*(RwReg*)0xFFFFE758U) /**< \brief (DMAC0) DMAC Channel Destination Address Register (ch_num = 7) */
#define REG_DMAC0_DSCR7               (*(RwReg*)0xFFFFE75CU) /**< \brief (DMAC0) DMAC Channel Descriptor Address Register (ch_num = 7) */
#define REG_DMAC0_CTRLA7              (*(RwReg*)0xFFFFE760U) /**< \brief (DMAC0) DMAC Channel Control A Register (ch_num = 7) */
#define REG_DMAC0_CTRLB7              (*(RwReg*)0xFFFFE764U) /**< \brief (DMAC0) DMAC Channel Control B Register (ch_num = 7) */
#define REG_DMAC0_CFG7                (*(RwReg*)0xFFFFE768U) /**< \brief (DMAC0) DMAC Channel Configuration Register (ch_num = 7) */
#define REG_DMAC0_SPIP7               (*(RwReg*)0xFFFFE76CU) /**< \brief (DMAC0) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 7) */
#define REG_DMAC0_DPIP7               (*(RwReg*)0xFFFFE770U) /**< \brief (DMAC0) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 7) */
#define REG_DMAC0_WPMR                (*(RwReg*)0xFFFFE7E4U) /**< \brief (DMAC0) DMAC Write Protect Mode Register */
#define REG_DMAC0_WPSR                (*(RoReg*)0xFFFFE7E8U) /**< \brief (DMAC0) DMAC Write Protect Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for DMAC1 peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_DMAC1_GCFG                         (0xFFFFE800U) /**< \brief (DMAC1) DMAC Global Configuration Register */
#define REG_DMAC1_EN                           (0xFFFFE804U) /**< \brief (DMAC1) DMAC Enable Register */
#define REG_DMAC1_SREQ                         (0xFFFFE808U) /**< \brief (DMAC1) DMAC Software Single Request Register */
#define REG_DMAC1_CREQ                         (0xFFFFE80CU) /**< \brief (DMAC1) DMAC Software Chunk Transfer Request Register */
#define REG_DMAC1_LAST                         (0xFFFFE810U) /**< \brief (DMAC1) DMAC Software Last Transfer Flag Register */
#define REG_DMAC1_EBCIER                       (0xFFFFE818U) /**< \brief (DMAC1) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Enable register. */
#define REG_DMAC1_EBCIDR                       (0xFFFFE81CU) /**< \brief (DMAC1) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Disable register. */
#define REG_DMAC1_EBCIMR                       (0xFFFFE820U) /**< \brief (DMAC1) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Mask Register. */
#define REG_DMAC1_EBCISR                       (0xFFFFE824U) /**< \brief (DMAC1) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Status Register. */
#define REG_DMAC1_CHER                         (0xFFFFE828U) /**< \brief (DMAC1) DMAC Channel Handler Enable Register */
#define REG_DMAC1_CHDR                         (0xFFFFE82CU) /**< \brief (DMAC1) DMAC Channel Handler Disable Register */
#define REG_DMAC1_CHSR                         (0xFFFFE830U) /**< \brief (DMAC1) DMAC Channel Handler Status Register */
#define REG_DMAC1_SADDR0                       (0xFFFFE83CU) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 0) */
#define REG_DMAC1_DADDR0                       (0xFFFFE840U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 0) */
#define REG_DMAC1_DSCR0                        (0xFFFFE844U) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 0) */
#define REG_DMAC1_CTRLA0                       (0xFFFFE848U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 0) */
#define REG_DMAC1_CTRLB0                       (0xFFFFE84CU) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 0) */
#define REG_DMAC1_CFG0                         (0xFFFFE850U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 0) */
#define REG_DMAC1_SPIP0                        (0xFFFFE854U) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 0) */
#define REG_DMAC1_DPIP0                        (0xFFFFE858U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 0) */
#define REG_DMAC1_SADDR1                       (0xFFFFE864U) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 1) */
#define REG_DMAC1_DADDR1                       (0xFFFFE868U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 1) */
#define REG_DMAC1_DSCR1                        (0xFFFFE86CU) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 1) */
#define REG_DMAC1_CTRLA1                       (0xFFFFE870U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 1) */
#define REG_DMAC1_CTRLB1                       (0xFFFFE874U) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 1) */
#define REG_DMAC1_CFG1                         (0xFFFFE878U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 1) */
#define REG_DMAC1_SPIP1                        (0xFFFFE87CU) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 1) */
#define REG_DMAC1_DPIP1                        (0xFFFFE880U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 1) */
#define REG_DMAC1_SADDR2                       (0xFFFFE88CU) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 2) */
#define REG_DMAC1_DADDR2                       (0xFFFFE890U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 2) */
#define REG_DMAC1_DSCR2                        (0xFFFFE894U) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 2) */
#define REG_DMAC1_CTRLA2                       (0xFFFFE898U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 2) */
#define REG_DMAC1_CTRLB2                       (0xFFFFE89CU) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 2) */
#define REG_DMAC1_CFG2                         (0xFFFFE8A0U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 2) */
#define REG_DMAC1_SPIP2                        (0xFFFFE8A4U) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 2) */
#define REG_DMAC1_DPIP2                        (0xFFFFE8A8U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 2) */
#define REG_DMAC1_SADDR3                       (0xFFFFE8B4U) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 3) */
#define REG_DMAC1_DADDR3                       (0xFFFFE8B8U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 3) */
#define REG_DMAC1_DSCR3                        (0xFFFFE8BCU) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 3) */
#define REG_DMAC1_CTRLA3                       (0xFFFFE8C0U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 3) */
#define REG_DMAC1_CTRLB3                       (0xFFFFE8C4U) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 3) */
#define REG_DMAC1_CFG3                         (0xFFFFE8C8U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 3) */
#define REG_DMAC1_SPIP3                        (0xFFFFE8CCU) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 3) */
#define REG_DMAC1_DPIP3                        (0xFFFFE8D0U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 3) */
#define REG_DMAC1_SADDR4                       (0xFFFFE8DCU) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 4) */
#define REG_DMAC1_DADDR4                       (0xFFFFE8E0U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 4) */
#define REG_DMAC1_DSCR4                        (0xFFFFE8E4U) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 4) */
#define REG_DMAC1_CTRLA4                       (0xFFFFE8E8U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 4) */
#define REG_DMAC1_CTRLB4                       (0xFFFFE8ECU) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 4) */
#define REG_DMAC1_CFG4                         (0xFFFFE8F0U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 4) */
#define REG_DMAC1_SPIP4                        (0xFFFFE8F4U) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 4) */
#define REG_DMAC1_DPIP4                        (0xFFFFE8F8U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 4) */
#define REG_DMAC1_SADDR5                       (0xFFFFE904U) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 5) */
#define REG_DMAC1_DADDR5                       (0xFFFFE908U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 5) */
#define REG_DMAC1_DSCR5                        (0xFFFFE90CU) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 5) */
#define REG_DMAC1_CTRLA5                       (0xFFFFE910U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 5) */
#define REG_DMAC1_CTRLB5                       (0xFFFFE914U) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 5) */
#define REG_DMAC1_CFG5                         (0xFFFFE918U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 5) */
#define REG_DMAC1_SPIP5                        (0xFFFFE91CU) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 5) */
#define REG_DMAC1_DPIP5                        (0xFFFFE920U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 5) */
#define REG_DMAC1_SADDR6                       (0xFFFFE92CU) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 6) */
#define REG_DMAC1_DADDR6                       (0xFFFFE930U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 6) */
#define REG_DMAC1_DSCR6                        (0xFFFFE934U) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 6) */
#define REG_DMAC1_CTRLA6                       (0xFFFFE938U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 6) */
#define REG_DMAC1_CTRLB6                       (0xFFFFE93CU) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 6) */
#define REG_DMAC1_CFG6                         (0xFFFFE940U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 6) */
#define REG_DMAC1_SPIP6                        (0xFFFFE944U) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 6) */
#define REG_DMAC1_DPIP6                        (0xFFFFE948U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 6) */
#define REG_DMAC1_SADDR7                       (0xFFFFE954U) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 7) */
#define REG_DMAC1_DADDR7                       (0xFFFFE958U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 7) */
#define REG_DMAC1_DSCR7                        (0xFFFFE95CU) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 7) */
#define REG_DMAC1_CTRLA7                       (0xFFFFE960U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 7) */
#define REG_DMAC1_CTRLB7                       (0xFFFFE964U) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 7) */
#define REG_DMAC1_CFG7                         (0xFFFFE968U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 7) */
#define REG_DMAC1_SPIP7                        (0xFFFFE96CU) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 7) */
#define REG_DMAC1_DPIP7                        (0xFFFFE970U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 7) */
#define REG_DMAC1_WPMR                         (0xFFFFE9E4U) /**< \brief (DMAC1) DMAC Write Protect Mode Register */
#define REG_DMAC1_WPSR                         (0xFFFFE9E8U) /**< \brief (DMAC1) DMAC Write Protect Status Register */
#else
#define REG_DMAC1_GCFG                (*(RwReg*)0xFFFFE800U) /**< \brief (DMAC1) DMAC Global Configuration Register */
#define REG_DMAC1_EN                  (*(RwReg*)0xFFFFE804U) /**< \brief (DMAC1) DMAC Enable Register */
#define REG_DMAC1_SREQ                (*(RwReg*)0xFFFFE808U) /**< \brief (DMAC1) DMAC Software Single Request Register */
#define REG_DMAC1_CREQ                (*(RwReg*)0xFFFFE80CU) /**< \brief (DMAC1) DMAC Software Chunk Transfer Request Register */
#define REG_DMAC1_LAST                (*(RwReg*)0xFFFFE810U) /**< \brief (DMAC1) DMAC Software Last Transfer Flag Register */
#define REG_DMAC1_EBCIER              (*(WoReg*)0xFFFFE818U) /**< \brief (DMAC1) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Enable register. */
#define REG_DMAC1_EBCIDR              (*(WoReg*)0xFFFFE81CU) /**< \brief (DMAC1) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer Transfer Completed Interrupt Disable register. */
#define REG_DMAC1_EBCIMR              (*(RoReg*)0xFFFFE820U) /**< \brief (DMAC1) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Mask Register. */
#define REG_DMAC1_EBCISR              (*(RoReg*)0xFFFFE824U) /**< \brief (DMAC1) DMAC Error, Chained Buffer Transfer Completed Interrupt and Buffer transfer completed Status Register. */
#define REG_DMAC1_CHER                (*(WoReg*)0xFFFFE828U) /**< \brief (DMAC1) DMAC Channel Handler Enable Register */
#define REG_DMAC1_CHDR                (*(WoReg*)0xFFFFE82CU) /**< \brief (DMAC1) DMAC Channel Handler Disable Register */
#define REG_DMAC1_CHSR                (*(RoReg*)0xFFFFE830U) /**< \brief (DMAC1) DMAC Channel Handler Status Register */
#define REG_DMAC1_SADDR0              (*(RwReg*)0xFFFFE83CU) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 0) */
#define REG_DMAC1_DADDR0              (*(RwReg*)0xFFFFE840U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 0) */
#define REG_DMAC1_DSCR0               (*(RwReg*)0xFFFFE844U) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 0) */
#define REG_DMAC1_CTRLA0              (*(RwReg*)0xFFFFE848U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 0) */
#define REG_DMAC1_CTRLB0              (*(RwReg*)0xFFFFE84CU) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 0) */
#define REG_DMAC1_CFG0                (*(RwReg*)0xFFFFE850U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 0) */
#define REG_DMAC1_SPIP0               (*(RwReg*)0xFFFFE854U) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 0) */
#define REG_DMAC1_DPIP0               (*(RwReg*)0xFFFFE858U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 0) */
#define REG_DMAC1_SADDR1              (*(RwReg*)0xFFFFE864U) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 1) */
#define REG_DMAC1_DADDR1              (*(RwReg*)0xFFFFE868U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 1) */
#define REG_DMAC1_DSCR1               (*(RwReg*)0xFFFFE86CU) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 1) */
#define REG_DMAC1_CTRLA1              (*(RwReg*)0xFFFFE870U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 1) */
#define REG_DMAC1_CTRLB1              (*(RwReg*)0xFFFFE874U) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 1) */
#define REG_DMAC1_CFG1                (*(RwReg*)0xFFFFE878U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 1) */
#define REG_DMAC1_SPIP1               (*(RwReg*)0xFFFFE87CU) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 1) */
#define REG_DMAC1_DPIP1               (*(RwReg*)0xFFFFE880U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 1) */
#define REG_DMAC1_SADDR2              (*(RwReg*)0xFFFFE88CU) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 2) */
#define REG_DMAC1_DADDR2              (*(RwReg*)0xFFFFE890U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 2) */
#define REG_DMAC1_DSCR2               (*(RwReg*)0xFFFFE894U) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 2) */
#define REG_DMAC1_CTRLA2              (*(RwReg*)0xFFFFE898U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 2) */
#define REG_DMAC1_CTRLB2              (*(RwReg*)0xFFFFE89CU) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 2) */
#define REG_DMAC1_CFG2                (*(RwReg*)0xFFFFE8A0U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 2) */
#define REG_DMAC1_SPIP2               (*(RwReg*)0xFFFFE8A4U) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 2) */
#define REG_DMAC1_DPIP2               (*(RwReg*)0xFFFFE8A8U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 2) */
#define REG_DMAC1_SADDR3              (*(RwReg*)0xFFFFE8B4U) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 3) */
#define REG_DMAC1_DADDR3              (*(RwReg*)0xFFFFE8B8U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 3) */
#define REG_DMAC1_DSCR3               (*(RwReg*)0xFFFFE8BCU) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 3) */
#define REG_DMAC1_CTRLA3              (*(RwReg*)0xFFFFE8C0U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 3) */
#define REG_DMAC1_CTRLB3              (*(RwReg*)0xFFFFE8C4U) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 3) */
#define REG_DMAC1_CFG3                (*(RwReg*)0xFFFFE8C8U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 3) */
#define REG_DMAC1_SPIP3               (*(RwReg*)0xFFFFE8CCU) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 3) */
#define REG_DMAC1_DPIP3               (*(RwReg*)0xFFFFE8D0U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 3) */
#define REG_DMAC1_SADDR4              (*(RwReg*)0xFFFFE8DCU) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 4) */
#define REG_DMAC1_DADDR4              (*(RwReg*)0xFFFFE8E0U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 4) */
#define REG_DMAC1_DSCR4               (*(RwReg*)0xFFFFE8E4U) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 4) */
#define REG_DMAC1_CTRLA4              (*(RwReg*)0xFFFFE8E8U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 4) */
#define REG_DMAC1_CTRLB4              (*(RwReg*)0xFFFFE8ECU) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 4) */
#define REG_DMAC1_CFG4                (*(RwReg*)0xFFFFE8F0U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 4) */
#define REG_DMAC1_SPIP4               (*(RwReg*)0xFFFFE8F4U) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 4) */
#define REG_DMAC1_DPIP4               (*(RwReg*)0xFFFFE8F8U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 4) */
#define REG_DMAC1_SADDR5              (*(RwReg*)0xFFFFE904U) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 5) */
#define REG_DMAC1_DADDR5              (*(RwReg*)0xFFFFE908U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 5) */
#define REG_DMAC1_DSCR5               (*(RwReg*)0xFFFFE90CU) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 5) */
#define REG_DMAC1_CTRLA5              (*(RwReg*)0xFFFFE910U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 5) */
#define REG_DMAC1_CTRLB5              (*(RwReg*)0xFFFFE914U) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 5) */
#define REG_DMAC1_CFG5                (*(RwReg*)0xFFFFE918U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 5) */
#define REG_DMAC1_SPIP5               (*(RwReg*)0xFFFFE91CU) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 5) */
#define REG_DMAC1_DPIP5               (*(RwReg*)0xFFFFE920U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 5) */
#define REG_DMAC1_SADDR6              (*(RwReg*)0xFFFFE92CU) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 6) */
#define REG_DMAC1_DADDR6              (*(RwReg*)0xFFFFE930U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 6) */
#define REG_DMAC1_DSCR6               (*(RwReg*)0xFFFFE934U) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 6) */
#define REG_DMAC1_CTRLA6              (*(RwReg*)0xFFFFE938U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 6) */
#define REG_DMAC1_CTRLB6              (*(RwReg*)0xFFFFE93CU) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 6) */
#define REG_DMAC1_CFG6                (*(RwReg*)0xFFFFE940U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 6) */
#define REG_DMAC1_SPIP6               (*(RwReg*)0xFFFFE944U) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 6) */
#define REG_DMAC1_DPIP6               (*(RwReg*)0xFFFFE948U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 6) */
#define REG_DMAC1_SADDR7              (*(RwReg*)0xFFFFE954U) /**< \brief (DMAC1) DMAC Channel Source Address Register (ch_num = 7) */
#define REG_DMAC1_DADDR7              (*(RwReg*)0xFFFFE958U) /**< \brief (DMAC1) DMAC Channel Destination Address Register (ch_num = 7) */
#define REG_DMAC1_DSCR7               (*(RwReg*)0xFFFFE95CU) /**< \brief (DMAC1) DMAC Channel Descriptor Address Register (ch_num = 7) */
#define REG_DMAC1_CTRLA7              (*(RwReg*)0xFFFFE960U) /**< \brief (DMAC1) DMAC Channel Control A Register (ch_num = 7) */
#define REG_DMAC1_CTRLB7              (*(RwReg*)0xFFFFE964U) /**< \brief (DMAC1) DMAC Channel Control B Register (ch_num = 7) */
#define REG_DMAC1_CFG7                (*(RwReg*)0xFFFFE968U) /**< \brief (DMAC1) DMAC Channel Configuration Register (ch_num = 7) */
#define REG_DMAC1_SPIP7               (*(RwReg*)0xFFFFE96CU) /**< \brief (DMAC1) DMAC Channel Source Picture-in-Picture Configuration Register (ch_num = 7) */
#define REG_DMAC1_DPIP7               (*(RwReg*)0xFFFFE970U) /**< \brief (DMAC1) DMAC Channel Destination Picture-in-Picture Configuration Register (ch_num = 7) */
#define REG_DMAC1_WPMR                (*(RwReg*)0xFFFFE9E4U) /**< \brief (DMAC1) DMAC Write Protect Mode Register */
#define REG_DMAC1_WPSR                (*(RoReg*)0xFFFFE9E8U) /**< \brief (DMAC1) DMAC Write Protect Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for MPDDRC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_MPDDRC_MR                          (0xFFFFEA00U) /**< \brief (MPDDRC) MPDDRC Mode Register */
#define REG_MPDDRC_RTR                         (0xFFFFEA04U) /**< \brief (MPDDRC) MPDDRC Refresh Timer Register */
#define REG_MPDDRC_CR                          (0xFFFFEA08U) /**< \brief (MPDDRC) MPDDRC Configuration Register */
#define REG_MPDDRC_TPR0                        (0xFFFFEA0CU) /**< \brief (MPDDRC) MPDDRC Timing Parameter 0 Register */
#define REG_MPDDRC_TPR1                        (0xFFFFEA10U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 1 Register */
#define REG_MPDDRC_TPR2                        (0xFFFFEA14U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 2 Register */
#define REG_MPDDRC_LPR                         (0xFFFFEA1CU) /**< \brief (MPDDRC) MPDDRC Low-power Register */
#define REG_MPDDRC_MD                          (0xFFFFEA20U) /**< \brief (MPDDRC) MPDDRC Memory Device Register */
#define REG_MPDDRC_LPDDR2_LPR                  (0xFFFFEA28U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Low-power Register */
#define REG_MPDDRC_LPDDR2_CAL_MR4              (0xFFFFEA2CU) /**< \brief (MPDDRC) MPDDRC LPDDR2 Calibration and MR4 Register */
#define REG_MPDDRC_LPDDR2_TIM_CAL              (0xFFFFEA30U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Timing Calibration Register */
#define REG_MPDDRC_IO_CALIBR                   (0xFFFFEA34U) /**< \brief (MPDDRC) MPDDRC IO Calibration */
#define REG_MPDDRC_OCMS                        (0xFFFFEA38U) /**< \brief (MPDDRC) MPDDRC OCMS Register */
#define REG_MPDDRC_OCMS_KEY1                   (0xFFFFEA3CU) /**< \brief (MPDDRC) MPDDRC OCMS KEY1 Register */
#define REG_MPDDRC_OCMS_KEY2                   (0xFFFFEA40U) /**< \brief (MPDDRC) MPDDRC OCMS KEY2 Register */
#define REG_MPDDRC_DLL_MOR                     (0xFFFFEA74U) /**< \brief (MPDDRC) MPDDRC DLL Master Offset Register */
#define REG_MPDDRC_DLL_SOR                     (0xFFFFEA78U) /**< \brief (MPDDRC) MPDDRC DLL Slave Offset Register */
#define REG_MPDDRC_DLL_MSR                     (0xFFFFEA7CU) /**< \brief (MPDDRC) MPDDRC DLL Master Status Register */
#define REG_MPDDRC_DLL_S0SR                    (0xFFFFEA80U) /**< \brief (MPDDRC) MPDDRC DLL Slave 0 Status Register */
#define REG_MPDDRC_DLL_S1SR                    (0xFFFFEA84U) /**< \brief (MPDDRC) MPDDRC DLL Slave 1 Status Register */
#define REG_MPDDRC_WPCR                        (0xFFFFEAE4U) /**< \brief (MPDDRC) MPDDRC Write Protect Control Register */
#define REG_MPDDRC_WPSR                        (0xFFFFEAE8U) /**< \brief (MPDDRC) MPDDRC Write Protect Status Register */
#else
#define REG_MPDDRC_MR                 (*(RwReg*)0xFFFFEA00U) /**< \brief (MPDDRC) MPDDRC Mode Register */
#define REG_MPDDRC_RTR                (*(RwReg*)0xFFFFEA04U) /**< \brief (MPDDRC) MPDDRC Refresh Timer Register */
#define REG_MPDDRC_CR                 (*(RwReg*)0xFFFFEA08U) /**< \brief (MPDDRC) MPDDRC Configuration Register */
#define REG_MPDDRC_TPR0               (*(RwReg*)0xFFFFEA0CU) /**< \brief (MPDDRC) MPDDRC Timing Parameter 0 Register */
#define REG_MPDDRC_TPR1               (*(RwReg*)0xFFFFEA10U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 1 Register */
#define REG_MPDDRC_TPR2               (*(RwReg*)0xFFFFEA14U) /**< \brief (MPDDRC) MPDDRC Timing Parameter 2 Register */
#define REG_MPDDRC_LPR                (*(RwReg*)0xFFFFEA1CU) /**< \brief (MPDDRC) MPDDRC Low-power Register */
#define REG_MPDDRC_MD                 (*(RwReg*)0xFFFFEA20U) /**< \brief (MPDDRC) MPDDRC Memory Device Register */
#define REG_MPDDRC_LPDDR2_LPR         (*(RwReg*)0xFFFFEA28U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Low-power Register */
#define REG_MPDDRC_LPDDR2_CAL_MR4     (*(RwReg*)0xFFFFEA2CU) /**< \brief (MPDDRC) MPDDRC LPDDR2 Calibration and MR4 Register */
#define REG_MPDDRC_LPDDR2_TIM_CAL     (*(RwReg*)0xFFFFEA30U) /**< \brief (MPDDRC) MPDDRC LPDDR2 Timing Calibration Register */
#define REG_MPDDRC_IO_CALIBR          (*(RwReg*)0xFFFFEA34U) /**< \brief (MPDDRC) MPDDRC IO Calibration */
#define REG_MPDDRC_OCMS               (*(RwReg*)0xFFFFEA38U) /**< \brief (MPDDRC) MPDDRC OCMS Register */
#define REG_MPDDRC_OCMS_KEY1          (*(WoReg*)0xFFFFEA3CU) /**< \brief (MPDDRC) MPDDRC OCMS KEY1 Register */
#define REG_MPDDRC_OCMS_KEY2          (*(WoReg*)0xFFFFEA40U) /**< \brief (MPDDRC) MPDDRC OCMS KEY2 Register */
#define REG_MPDDRC_DLL_MOR            (*(RwReg*)0xFFFFEA74U) /**< \brief (MPDDRC) MPDDRC DLL Master Offset Register */
#define REG_MPDDRC_DLL_SOR            (*(RwReg*)0xFFFFEA78U) /**< \brief (MPDDRC) MPDDRC DLL Slave Offset Register */
#define REG_MPDDRC_DLL_MSR            (*(RoReg*)0xFFFFEA7CU) /**< \brief (MPDDRC) MPDDRC DLL Master Status Register */
#define REG_MPDDRC_DLL_S0SR           (*(RoReg*)0xFFFFEA80U) /**< \brief (MPDDRC) MPDDRC DLL Slave 0 Status Register */
#define REG_MPDDRC_DLL_S1SR           (*(RoReg*)0xFFFFEA84U) /**< \brief (MPDDRC) MPDDRC DLL Slave 1 Status Register */
#define REG_MPDDRC_WPCR               (*(RwReg*)0xFFFFEAE4U) /**< \brief (MPDDRC) MPDDRC Write Protect Control Register */
#define REG_MPDDRC_WPSR               (*(RoReg*)0xFFFFEAE8U) /**< \brief (MPDDRC) MPDDRC Write Protect Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for MATRIX peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_MATRIX_MCFG                        (0xFFFFEC00U) /**< \brief (MATRIX) Master Configuration Register */
#define REG_MATRIX_SCFG                        (0xFFFFEC40U) /**< \brief (MATRIX) Slave Configuration Register */
#define REG_MATRIX_PRAS0                       (0xFFFFEC80U) /**< \brief (MATRIX) Priority Register A for Slave 0 */
#define REG_MATRIX_PRBS0                       (0xFFFFEC84U) /**< \brief (MATRIX) Priority Register B for Slave 0 */
#define REG_MATRIX_PRAS1                       (0xFFFFEC88U) /**< \brief (MATRIX) Priority Register A for Slave 1 */
#define REG_MATRIX_PRBS1                       (0xFFFFEC8CU) /**< \brief (MATRIX) Priority Register B for Slave 1 */
#define REG_MATRIX_PRAS2                       (0xFFFFEC90U) /**< \brief (MATRIX) Priority Register A for Slave 2 */
#define REG_MATRIX_PRBS2                       (0xFFFFEC94U) /**< \brief (MATRIX) Priority Register B for Slave 2 */
#define REG_MATRIX_PRAS3                       (0xFFFFEC98U) /**< \brief (MATRIX) Priority Register A for Slave 3 */
#define REG_MATRIX_PRBS3                       (0xFFFFEC9CU) /**< \brief (MATRIX) Priority Register B for Slave 3 */
#define REG_MATRIX_PRAS4                       (0xFFFFECA0U) /**< \brief (MATRIX) Priority Register A for Slave 4 */
#define REG_MATRIX_PRBS4                       (0xFFFFECA4U) /**< \brief (MATRIX) Priority Register B for Slave 4 */
#define REG_MATRIX_PRAS5                       (0xFFFFECA8U) /**< \brief (MATRIX) Priority Register A for Slave 5 */
#define REG_MATRIX_PRBS5                       (0xFFFFECACU) /**< \brief (MATRIX) Priority Register B for Slave 5 */
#define REG_MATRIX_PRAS6                       (0xFFFFECB0U) /**< \brief (MATRIX) Priority Register A for Slave 6 */
#define REG_MATRIX_PRBS6                       (0xFFFFECB4U) /**< \brief (MATRIX) Priority Register B for Slave 6 */
#define REG_MATRIX_PRAS7                       (0xFFFFECB8U) /**< \brief (MATRIX) Priority Register A for Slave 7 */
#define REG_MATRIX_PRBS7                       (0xFFFFECBCU) /**< \brief (MATRIX) Priority Register B for Slave 7 */
#define REG_MATRIX_PRAS8                       (0xFFFFECC0U) /**< \brief (MATRIX) Priority Register A for Slave 8 */
#define REG_MATRIX_PRBS8                       (0xFFFFECC4U) /**< \brief (MATRIX) Priority Register B for Slave 8 */
#define REG_MATRIX_PRAS9                       (0xFFFFECC8U) /**< \brief (MATRIX) Priority Register A for Slave 9 */
#define REG_MATRIX_PRBS9                       (0xFFFFECCCU) /**< \brief (MATRIX) Priority Register B for Slave 9 */
#define REG_MATRIX_PRAS10                      (0xFFFFECD0U) /**< \brief (MATRIX) Priority Register A for Slave 10 */
#define REG_MATRIX_PRBS10                      (0xFFFFECD4U) /**< \brief (MATRIX) Priority Register B for Slave 10 */
#define REG_MATRIX_PRAS11                      (0xFFFFECD8U) /**< \brief (MATRIX) Priority Register A for Slave 11 */
#define REG_MATRIX_PRBS11                      (0xFFFFECDCU) /**< \brief (MATRIX) Priority Register B for Slave 11 */
#define REG_MATRIX_PRAS12                      (0xFFFFECE0U) /**< \brief (MATRIX) Priority Register A for Slave 12 */
#define REG_MATRIX_PRBS12                      (0xFFFFECE4U) /**< \brief (MATRIX) Priority Register B for Slave 12 */
#define REG_MATRIX_PRAS13                      (0xFFFFECE8U) /**< \brief (MATRIX) Priority Register A for Slave 13 */
#define REG_MATRIX_PRBS13                      (0xFFFFECECU) /**< \brief (MATRIX) Priority Register B for Slave 13 */
#define REG_MATRIX_PRAS14                      (0xFFFFECF0U) /**< \brief (MATRIX) Priority Register A for Slave 14 */
#define REG_MATRIX_PRBS14                      (0xFFFFECF4U) /**< \brief (MATRIX) Priority Register B for Slave 14 */
#define REG_MATRIX_PRAS15                      (0xFFFFECF8U) /**< \brief (MATRIX) Priority Register A for Slave 15 */
#define REG_MATRIX_PRBS15                      (0xFFFFECFCU) /**< \brief (MATRIX) Priority Register B for Slave 15 */
#define REG_MATRIX_MRCR                        (0xFFFFED00U) /**< \brief (MATRIX) Master Remap Control Register */
#define REG_MATRIX_SFR                         (0xFFFFED10U) /**< \brief (MATRIX) Special Function Register */
#define REG_MATRIX_WPMR                        (0xFFFFEDE4U) /**< \brief (MATRIX) Write Protect Mode Register */
#define REG_MATRIX_WPSR                        (0xFFFFEDE8U) /**< \brief (MATRIX) Write Protect Status Register */
#else
#define REG_MATRIX_MCFG               (*(RwReg*)0xFFFFEC00U) /**< \brief (MATRIX) Master Configuration Register */
#define REG_MATRIX_SCFG               (*(RwReg*)0xFFFFEC40U) /**< \brief (MATRIX) Slave Configuration Register */
#define REG_MATRIX_PRAS0              (*(RwReg*)0xFFFFEC80U) /**< \brief (MATRIX) Priority Register A for Slave 0 */
#define REG_MATRIX_PRBS0              (*(RwReg*)0xFFFFEC84U) /**< \brief (MATRIX) Priority Register B for Slave 0 */
#define REG_MATRIX_PRAS1              (*(RwReg*)0xFFFFEC88U) /**< \brief (MATRIX) Priority Register A for Slave 1 */
#define REG_MATRIX_PRBS1              (*(RwReg*)0xFFFFEC8CU) /**< \brief (MATRIX) Priority Register B for Slave 1 */
#define REG_MATRIX_PRAS2              (*(RwReg*)0xFFFFEC90U) /**< \brief (MATRIX) Priority Register A for Slave 2 */
#define REG_MATRIX_PRBS2              (*(RwReg*)0xFFFFEC94U) /**< \brief (MATRIX) Priority Register B for Slave 2 */
#define REG_MATRIX_PRAS3              (*(RwReg*)0xFFFFEC98U) /**< \brief (MATRIX) Priority Register A for Slave 3 */
#define REG_MATRIX_PRBS3              (*(RwReg*)0xFFFFEC9CU) /**< \brief (MATRIX) Priority Register B for Slave 3 */
#define REG_MATRIX_PRAS4              (*(RwReg*)0xFFFFECA0U) /**< \brief (MATRIX) Priority Register A for Slave 4 */
#define REG_MATRIX_PRBS4              (*(RwReg*)0xFFFFECA4U) /**< \brief (MATRIX) Priority Register B for Slave 4 */
#define REG_MATRIX_PRAS5              (*(RwReg*)0xFFFFECA8U) /**< \brief (MATRIX) Priority Register A for Slave 5 */
#define REG_MATRIX_PRBS5              (*(RwReg*)0xFFFFECACU) /**< \brief (MATRIX) Priority Register B for Slave 5 */
#define REG_MATRIX_PRAS6              (*(RwReg*)0xFFFFECB0U) /**< \brief (MATRIX) Priority Register A for Slave 6 */
#define REG_MATRIX_PRBS6              (*(RwReg*)0xFFFFECB4U) /**< \brief (MATRIX) Priority Register B for Slave 6 */
#define REG_MATRIX_PRAS7              (*(RwReg*)0xFFFFECB8U) /**< \brief (MATRIX) Priority Register A for Slave 7 */
#define REG_MATRIX_PRBS7              (*(RwReg*)0xFFFFECBCU) /**< \brief (MATRIX) Priority Register B for Slave 7 */
#define REG_MATRIX_PRAS8              (*(RwReg*)0xFFFFECC0U) /**< \brief (MATRIX) Priority Register A for Slave 8 */
#define REG_MATRIX_PRBS8              (*(RwReg*)0xFFFFECC4U) /**< \brief (MATRIX) Priority Register B for Slave 8 */
#define REG_MATRIX_PRAS9              (*(RwReg*)0xFFFFECC8U) /**< \brief (MATRIX) Priority Register A for Slave 9 */
#define REG_MATRIX_PRBS9              (*(RwReg*)0xFFFFECCCU) /**< \brief (MATRIX) Priority Register B for Slave 9 */
#define REG_MATRIX_PRAS10             (*(RwReg*)0xFFFFECD0U) /**< \brief (MATRIX) Priority Register A for Slave 10 */
#define REG_MATRIX_PRBS10             (*(RwReg*)0xFFFFECD4U) /**< \brief (MATRIX) Priority Register B for Slave 10 */
#define REG_MATRIX_PRAS11             (*(RwReg*)0xFFFFECD8U) /**< \brief (MATRIX) Priority Register A for Slave 11 */
#define REG_MATRIX_PRBS11             (*(RwReg*)0xFFFFECDCU) /**< \brief (MATRIX) Priority Register B for Slave 11 */
#define REG_MATRIX_PRAS12             (*(RwReg*)0xFFFFECE0U) /**< \brief (MATRIX) Priority Register A for Slave 12 */
#define REG_MATRIX_PRBS12             (*(RwReg*)0xFFFFECE4U) /**< \brief (MATRIX) Priority Register B for Slave 12 */
#define REG_MATRIX_PRAS13             (*(RwReg*)0xFFFFECE8U) /**< \brief (MATRIX) Priority Register A for Slave 13 */
#define REG_MATRIX_PRBS13             (*(RwReg*)0xFFFFECECU) /**< \brief (MATRIX) Priority Register B for Slave 13 */
#define REG_MATRIX_PRAS14             (*(RwReg*)0xFFFFECF0U) /**< \brief (MATRIX) Priority Register A for Slave 14 */
#define REG_MATRIX_PRBS14             (*(RwReg*)0xFFFFECF4U) /**< \brief (MATRIX) Priority Register B for Slave 14 */
#define REG_MATRIX_PRAS15             (*(RwReg*)0xFFFFECF8U) /**< \brief (MATRIX) Priority Register A for Slave 15 */
#define REG_MATRIX_PRBS15             (*(RwReg*)0xFFFFECFCU) /**< \brief (MATRIX) Priority Register B for Slave 15 */
#define REG_MATRIX_MRCR               (*(RwReg*)0xFFFFED00U) /**< \brief (MATRIX) Master Remap Control Register */
#define REG_MATRIX_SFR                (*(RwReg*)0xFFFFED10U) /**< \brief (MATRIX) Special Function Register */
#define REG_MATRIX_WPMR               (*(RwReg*)0xFFFFEDE4U) /**< \brief (MATRIX) Write Protect Mode Register */
#define REG_MATRIX_WPSR               (*(RoReg*)0xFFFFEDE8U) /**< \brief (MATRIX) Write Protect Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for DBGU peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_DBGU_CR                            (0xFFFFEE00U) /**< \brief (DBGU) Control Register */
#define REG_DBGU_MR                            (0xFFFFEE04U) /**< \brief (DBGU) Mode Register */
#define REG_DBGU_IER                           (0xFFFFEE08U) /**< \brief (DBGU) Interrupt Enable Register */
#define REG_DBGU_IDR                           (0xFFFFEE0CU) /**< \brief (DBGU) Interrupt Disable Register */
#define REG_DBGU_IMR                           (0xFFFFEE10U) /**< \brief (DBGU) Interrupt Mask Register */
#define REG_DBGU_SR                            (0xFFFFEE14U) /**< \brief (DBGU) Status Register */
#define REG_DBGU_RHR                           (0xFFFFEE18U) /**< \brief (DBGU) Receive Holding Register */
#define REG_DBGU_THR                           (0xFFFFEE1CU) /**< \brief (DBGU) Transmit Holding Register */
#define REG_DBGU_BRGR                          (0xFFFFEE20U) /**< \brief (DBGU) Baud Rate Generator Register */
#define REG_DBGU_CIDR                          (0xFFFFEE40U) /**< \brief (DBGU) Chip ID Register */
#define REG_DBGU_EXID                          (0xFFFFEE44U) /**< \brief (DBGU) Chip ID Extension Register */
#define REG_DBGU_FNR                           (0xFFFFEE48U) /**< \brief (DBGU) Force NTRST Register */
#else
#define REG_DBGU_CR                   (*(WoReg*)0xFFFFEE00U) /**< \brief (DBGU) Control Register */
#define REG_DBGU_MR                   (*(RwReg*)0xFFFFEE04U) /**< \brief (DBGU) Mode Register */
#define REG_DBGU_IER                  (*(WoReg*)0xFFFFEE08U) /**< \brief (DBGU) Interrupt Enable Register */
#define REG_DBGU_IDR                  (*(WoReg*)0xFFFFEE0CU) /**< \brief (DBGU) Interrupt Disable Register */
#define REG_DBGU_IMR                  (*(RoReg*)0xFFFFEE10U) /**< \brief (DBGU) Interrupt Mask Register */
#define REG_DBGU_SR                   (*(RoReg*)0xFFFFEE14U) /**< \brief (DBGU) Status Register */
#define REG_DBGU_RHR                  (*(RoReg*)0xFFFFEE18U) /**< \brief (DBGU) Receive Holding Register */
#define REG_DBGU_THR                  (*(WoReg*)0xFFFFEE1CU) /**< \brief (DBGU) Transmit Holding Register */
#define REG_DBGU_BRGR                 (*(RwReg*)0xFFFFEE20U) /**< \brief (DBGU) Baud Rate Generator Register */
#define REG_DBGU_CIDR                 (*(RoReg*)0xFFFFEE40U) /**< \brief (DBGU) Chip ID Register */
#define REG_DBGU_EXID                 (*(RoReg*)0xFFFFEE44U) /**< \brief (DBGU) Chip ID Extension Register */
#define REG_DBGU_FNR                  (*(RwReg*)0xFFFFEE48U) /**< \brief (DBGU) Force NTRST Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for AIC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_AIC_SSR                            (0xFFFFF000U) /**< \brief (AIC) Source Select Register */
#define REG_AIC_SMR                            (0xFFFFF004U) /**< \brief (AIC) Source Mode Register */
#define REG_AIC_SVR                            (0xFFFFF008U) /**< \brief (AIC) Source Vector Register */
#define REG_AIC_IVR                            (0xFFFFF010U) /**< \brief (AIC) Interrupt Vector Register */
#define REG_AIC_FVR                            (0xFFFFF014U) /**< \brief (AIC) FIQ Interrupt Vector Register */
#define REG_AIC_ISR                            (0xFFFFF018U) /**< \brief (AIC) Interrupt Status Register */
#define REG_AIC_IPR0                           (0xFFFFF020U) /**< \brief (AIC) Interrupt Pending Register 0 */
#define REG_AIC_IPR1                           (0xFFFFF024U) /**< \brief (AIC) Interrupt Pending Register 1 */
#define REG_AIC_IPR2                           (0xFFFFF028U) /**< \brief (AIC) Interrupt Pending Register 2 */
#define REG_AIC_IPR3                           (0xFFFFF02CU) /**< \brief (AIC) Interrupt Pending Register 3 */
#define REG_AIC_IMR                            (0xFFFFF030U) /**< \brief (AIC) Interrupt Mask Register */
#define REG_AIC_CISR                           (0xFFFFF034U) /**< \brief (AIC) Core Interrupt Status Register */
#define REG_AIC_EOICR                          (0xFFFFF038U) /**< \brief (AIC) End of Interrupt Command Register */
#define REG_AIC_SPU                            (0xFFFFF03CU) /**< \brief (AIC) Spurious Interrupt Vector Register */
#define REG_AIC_IECR                           (0xFFFFF040U) /**< \brief (AIC) Interrupt Enable Command Register */
#define REG_AIC_IDCR                           (0xFFFFF044U) /**< \brief (AIC) Interrupt Disable Command Register */
#define REG_AIC_ICCR                           (0xFFFFF048U) /**< \brief (AIC) Interrupt Clear Command Register */
#define REG_AIC_ISCR                           (0xFFFFF04CU) /**< \brief (AIC) Interrupt Set Command Register */
#define REG_AIC_FFER                           (0xFFFFF050U) /**< \brief (AIC) Fast Forcing Enable Register */
#define REG_AIC_FFDR                           (0xFFFFF054U) /**< \brief (AIC) Fast Forcing Disable Register */
#define REG_AIC_FFSR                           (0xFFFFF058U) /**< \brief (AIC) Fast Forcing Status Register */
#define REG_AIC_DCR                            (0xFFFFF06CU) /**< \brief (AIC) Debug Control Register */
#define REG_AIC_WPMR                           (0xFFFFF0E4U) /**< \brief (AIC) Write Protect Mode Register */
#define REG_AIC_WPSR                           (0xFFFFF0E8U) /**< \brief (AIC) Write Protect Status Register */
#else
#define REG_AIC_SSR                   (*(RwReg*)0xFFFFF000U) /**< \brief (AIC) Source Select Register */
#define REG_AIC_SMR                   (*(RwReg*)0xFFFFF004U) /**< \brief (AIC) Source Mode Register */
#define REG_AIC_SVR                   (*(RwReg*)0xFFFFF008U) /**< \brief (AIC) Source Vector Register */
#define REG_AIC_IVR                   (*(RoReg*)0xFFFFF010U) /**< \brief (AIC) Interrupt Vector Register */
#define REG_AIC_FVR                   (*(RoReg*)0xFFFFF014U) /**< \brief (AIC) FIQ Interrupt Vector Register */
#define REG_AIC_ISR                   (*(RoReg*)0xFFFFF018U) /**< \brief (AIC) Interrupt Status Register */
#define REG_AIC_IPR0                  (*(RoReg*)0xFFFFF020U) /**< \brief (AIC) Interrupt Pending Register 0 */
#define REG_AIC_IPR1                  (*(RoReg*)0xFFFFF024U) /**< \brief (AIC) Interrupt Pending Register 1 */
#define REG_AIC_IPR2                  (*(RoReg*)0xFFFFF028U) /**< \brief (AIC) Interrupt Pending Register 2 */
#define REG_AIC_IPR3                  (*(RoReg*)0xFFFFF02CU) /**< \brief (AIC) Interrupt Pending Register 3 */
#define REG_AIC_IMR                   (*(RoReg*)0xFFFFF030U) /**< \brief (AIC) Interrupt Mask Register */
#define REG_AIC_CISR                  (*(RoReg*)0xFFFFF034U) /**< \brief (AIC) Core Interrupt Status Register */
#define REG_AIC_EOICR                 (*(WoReg*)0xFFFFF038U) /**< \brief (AIC) End of Interrupt Command Register */
#define REG_AIC_SPU                   (*(RwReg*)0xFFFFF03CU) /**< \brief (AIC) Spurious Interrupt Vector Register */
#define REG_AIC_IECR                  (*(WoReg*)0xFFFFF040U) /**< \brief (AIC) Interrupt Enable Command Register */
#define REG_AIC_IDCR                  (*(WoReg*)0xFFFFF044U) /**< \brief (AIC) Interrupt Disable Command Register */
#define REG_AIC_ICCR                  (*(WoReg*)0xFFFFF048U) /**< \brief (AIC) Interrupt Clear Command Register */
#define REG_AIC_ISCR                  (*(WoReg*)0xFFFFF04CU) /**< \brief (AIC) Interrupt Set Command Register */
#define REG_AIC_FFER                  (*(WoReg*)0xFFFFF050U) /**< \brief (AIC) Fast Forcing Enable Register */
#define REG_AIC_FFDR                  (*(WoReg*)0xFFFFF054U) /**< \brief (AIC) Fast Forcing Disable Register */
#define REG_AIC_FFSR                  (*(RoReg*)0xFFFFF058U) /**< \brief (AIC) Fast Forcing Status Register */
#define REG_AIC_DCR                   (*(RwReg*)0xFFFFF06CU) /**< \brief (AIC) Debug Control Register */
#define REG_AIC_WPMR                  (*(RwReg*)0xFFFFF0E4U) /**< \brief (AIC) Write Protect Mode Register */
#define REG_AIC_WPSR                  (*(RoReg*)0xFFFFF0E8U) /**< \brief (AIC) Write Protect Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for PIOA peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_PIOA_PER                           (0xFFFFF200U) /**< \brief (PIOA) PIO Enable Register */
#define REG_PIOA_PDR                           (0xFFFFF204U) /**< \brief (PIOA) PIO Disable Register */
#define REG_PIOA_PSR                           (0xFFFFF208U) /**< \brief (PIOA) PIO Status Register */
#define REG_PIOA_OER                           (0xFFFFF210U) /**< \brief (PIOA) Output Enable Register */
#define REG_PIOA_ODR                           (0xFFFFF214U) /**< \brief (PIOA) Output Disable Register */
#define REG_PIOA_OSR                           (0xFFFFF218U) /**< \brief (PIOA) Output Status Register */
#define REG_PIOA_IFER                          (0xFFFFF220U) /**< \brief (PIOA) Glitch Input Filter Enable Register */
#define REG_PIOA_IFDR                          (0xFFFFF224U) /**< \brief (PIOA) Glitch Input Filter Disable Register */
#define REG_PIOA_IFSR                          (0xFFFFF228U) /**< \brief (PIOA) Glitch Input Filter Status Register */
#define REG_PIOA_SODR                          (0xFFFFF230U) /**< \brief (PIOA) Set Output Data Register */
#define REG_PIOA_CODR                          (0xFFFFF234U) /**< \brief (PIOA) Clear Output Data Register */
#define REG_PIOA_ODSR                          (0xFFFFF238U) /**< \brief (PIOA) Output Data Status Register */
#define REG_PIOA_PDSR                          (0xFFFFF23CU) /**< \brief (PIOA) Pin Data Status Register */
#define REG_PIOA_IER                           (0xFFFFF240U) /**< \brief (PIOA) Interrupt Enable Register */
#define REG_PIOA_IDR                           (0xFFFFF244U) /**< \brief (PIOA) Interrupt Disable Register */
#define REG_PIOA_IMR                           (0xFFFFF248U) /**< \brief (PIOA) Interrupt Mask Register */
#define REG_PIOA_ISR                           (0xFFFFF24CU) /**< \brief (PIOA) Interrupt Status Register */
#define REG_PIOA_MDER                          (0xFFFFF250U) /**< \brief (PIOA) Multi-driver Enable Register */
#define REG_PIOA_MDDR                          (0xFFFFF254U) /**< \brief (PIOA) Multi-driver Disable Register */
#define REG_PIOA_MDSR                          (0xFFFFF258U) /**< \brief (PIOA) Multi-driver Status Register */
#define REG_PIOA_PUDR                          (0xFFFFF260U) /**< \brief (PIOA) Pull-up Disable Register */
#define REG_PIOA_PUER                          (0xFFFFF264U) /**< \brief (PIOA) Pull-up Enable Register */
#define REG_PIOA_PUSR                          (0xFFFFF268U) /**< \brief (PIOA) Pad Pull-up Status Register */
#define REG_PIOA_ABCDSR                        (0xFFFFF270U) /**< \brief (PIOA) Peripheral Select Register */
#define REG_PIOA_IFSCDR                        (0xFFFFF280U) /**< \brief (PIOA) Input Filter Slow Clock Disable Register */
#define REG_PIOA_IFSCER                        (0xFFFFF284U) /**< \brief (PIOA) Input Filter Slow Clock Enable Register */
#define REG_PIOA_IFSCSR                        (0xFFFFF288U) /**< \brief (PIOA) Input Filter Slow Clock Status Register */
#define REG_PIOA_SCDR                          (0xFFFFF28CU) /**< \brief (PIOA) Slow Clock Divider Debouncing Register */
#define REG_PIOA_PPDDR                         (0xFFFFF290U) /**< \brief (PIOA) Pad Pull-down Disable Register */
#define REG_PIOA_PPDER                         (0xFFFFF294U) /**< \brief (PIOA) Pad Pull-down Enable Register */
#define REG_PIOA_PPDSR                         (0xFFFFF298U) /**< \brief (PIOA) Pad Pull-down Status Register */
#define REG_PIOA_OWER                          (0xFFFFF2A0U) /**< \brief (PIOA) Output Write Enable */
#define REG_PIOA_OWDR                          (0xFFFFF2A4U) /**< \brief (PIOA) Output Write Disable */
#define REG_PIOA_OWSR                          (0xFFFFF2A8U) /**< \brief (PIOA) Output Write Status Register */
#define REG_PIOA_AIMER                         (0xFFFFF2B0U) /**< \brief (PIOA) Additional Interrupt Modes Enable Register */
#define REG_PIOA_AIMDR                         (0xFFFFF2B4U) /**< \brief (PIOA) Additional Interrupt Modes Disables Register */
#define REG_PIOA_AIMMR                         (0xFFFFF2B8U) /**< \brief (PIOA) Additional Interrupt Modes Mask Register */
#define REG_PIOA_ESR                           (0xFFFFF2C0U) /**< \brief (PIOA) Edge Select Register */
#define REG_PIOA_LSR                           (0xFFFFF2C4U) /**< \brief (PIOA) Level Select Register */
#define REG_PIOA_ELSR                          (0xFFFFF2C8U) /**< \brief (PIOA) Edge/Level Status Register */
#define REG_PIOA_FELLSR                        (0xFFFFF2D0U) /**< \brief (PIOA) Falling Edge/Low Level Select Register */
#define REG_PIOA_REHLSR                        (0xFFFFF2D4U) /**< \brief (PIOA) Rising Edge/ High Level Select Register */
#define REG_PIOA_FRLHSR                        (0xFFFFF2D8U) /**< \brief (PIOA) Fall/Rise - Low/High Status Register */
#define REG_PIOA_LOCKSR                        (0xFFFFF2E0U) /**< \brief (PIOA) Lock Status */
#define REG_PIOA_WPMR                          (0xFFFFF2E4U) /**< \brief (PIOA) Write Protect Mode Register */
#define REG_PIOA_WPSR                          (0xFFFFF2E8U) /**< \brief (PIOA) Write Protect Status Register */
#define REG_PIOA_SCHMITT                       (0xFFFFF300U) /**< \brief (PIOA) Schmitt Trigger Register */
#define REG_PIOA_DRIVER1                       (0xFFFFF318U) /**< \brief (PIOA) I/O Drive Register 1 */
#define REG_PIOA_DRIVER2                       (0xFFFFF31CU) /**< \brief (PIOA) I/O Drive Register 2 */
#else
#define REG_PIOA_PER                  (*(WoReg*)0xFFFFF200U) /**< \brief (PIOA) PIO Enable Register */
#define REG_PIOA_PDR                  (*(WoReg*)0xFFFFF204U) /**< \brief (PIOA) PIO Disable Register */
#define REG_PIOA_PSR                  (*(RoReg*)0xFFFFF208U) /**< \brief (PIOA) PIO Status Register */
#define REG_PIOA_OER                  (*(WoReg*)0xFFFFF210U) /**< \brief (PIOA) Output Enable Register */
#define REG_PIOA_ODR                  (*(WoReg*)0xFFFFF214U) /**< \brief (PIOA) Output Disable Register */
#define REG_PIOA_OSR                  (*(RoReg*)0xFFFFF218U) /**< \brief (PIOA) Output Status Register */
#define REG_PIOA_IFER                 (*(WoReg*)0xFFFFF220U) /**< \brief (PIOA) Glitch Input Filter Enable Register */
#define REG_PIOA_IFDR                 (*(WoReg*)0xFFFFF224U) /**< \brief (PIOA) Glitch Input Filter Disable Register */
#define REG_PIOA_IFSR                 (*(RoReg*)0xFFFFF228U) /**< \brief (PIOA) Glitch Input Filter Status Register */
#define REG_PIOA_SODR                 (*(WoReg*)0xFFFFF230U) /**< \brief (PIOA) Set Output Data Register */
#define REG_PIOA_CODR                 (*(WoReg*)0xFFFFF234U) /**< \brief (PIOA) Clear Output Data Register */
#define REG_PIOA_ODSR                 (*(RwReg*)0xFFFFF238U) /**< \brief (PIOA) Output Data Status Register */
#define REG_PIOA_PDSR                 (*(RoReg*)0xFFFFF23CU) /**< \brief (PIOA) Pin Data Status Register */
#define REG_PIOA_IER                  (*(WoReg*)0xFFFFF240U) /**< \brief (PIOA) Interrupt Enable Register */
#define REG_PIOA_IDR                  (*(WoReg*)0xFFFFF244U) /**< \brief (PIOA) Interrupt Disable Register */
#define REG_PIOA_IMR                  (*(RoReg*)0xFFFFF248U) /**< \brief (PIOA) Interrupt Mask Register */
#define REG_PIOA_ISR                  (*(RoReg*)0xFFFFF24CU) /**< \brief (PIOA) Interrupt Status Register */
#define REG_PIOA_MDER                 (*(WoReg*)0xFFFFF250U) /**< \brief (PIOA) Multi-driver Enable Register */
#define REG_PIOA_MDDR                 (*(WoReg*)0xFFFFF254U) /**< \brief (PIOA) Multi-driver Disable Register */
#define REG_PIOA_MDSR                 (*(RoReg*)0xFFFFF258U) /**< \brief (PIOA) Multi-driver Status Register */
#define REG_PIOA_PUDR                 (*(WoReg*)0xFFFFF260U) /**< \brief (PIOA) Pull-up Disable Register */
#define REG_PIOA_PUER                 (*(WoReg*)0xFFFFF264U) /**< \brief (PIOA) Pull-up Enable Register */
#define REG_PIOA_PUSR                 (*(RoReg*)0xFFFFF268U) /**< \brief (PIOA) Pad Pull-up Status Register */
#define REG_PIOA_ABCDSR               (*(RwReg*)0xFFFFF270U) /**< \brief (PIOA) Peripheral Select Register */
#define REG_PIOA_IFSCDR               (*(WoReg*)0xFFFFF280U) /**< \brief (PIOA) Input Filter Slow Clock Disable Register */
#define REG_PIOA_IFSCER               (*(WoReg*)0xFFFFF284U) /**< \brief (PIOA) Input Filter Slow Clock Enable Register */
#define REG_PIOA_IFSCSR               (*(RoReg*)0xFFFFF288U) /**< \brief (PIOA) Input Filter Slow Clock Status Register */
#define REG_PIOA_SCDR                 (*(RwReg*)0xFFFFF28CU) /**< \brief (PIOA) Slow Clock Divider Debouncing Register */
#define REG_PIOA_PPDDR                (*(WoReg*)0xFFFFF290U) /**< \brief (PIOA) Pad Pull-down Disable Register */
#define REG_PIOA_PPDER                (*(WoReg*)0xFFFFF294U) /**< \brief (PIOA) Pad Pull-down Enable Register */
#define REG_PIOA_PPDSR                (*(RoReg*)0xFFFFF298U) /**< \brief (PIOA) Pad Pull-down Status Register */
#define REG_PIOA_OWER                 (*(WoReg*)0xFFFFF2A0U) /**< \brief (PIOA) Output Write Enable */
#define REG_PIOA_OWDR                 (*(WoReg*)0xFFFFF2A4U) /**< \brief (PIOA) Output Write Disable */
#define REG_PIOA_OWSR                 (*(RoReg*)0xFFFFF2A8U) /**< \brief (PIOA) Output Write Status Register */
#define REG_PIOA_AIMER                (*(WoReg*)0xFFFFF2B0U) /**< \brief (PIOA) Additional Interrupt Modes Enable Register */
#define REG_PIOA_AIMDR                (*(WoReg*)0xFFFFF2B4U) /**< \brief (PIOA) Additional Interrupt Modes Disables Register */
#define REG_PIOA_AIMMR                (*(RoReg*)0xFFFFF2B8U) /**< \brief (PIOA) Additional Interrupt Modes Mask Register */
#define REG_PIOA_ESR                  (*(WoReg*)0xFFFFF2C0U) /**< \brief (PIOA) Edge Select Register */
#define REG_PIOA_LSR                  (*(WoReg*)0xFFFFF2C4U) /**< \brief (PIOA) Level Select Register */
#define REG_PIOA_ELSR                 (*(RoReg*)0xFFFFF2C8U) /**< \brief (PIOA) Edge/Level Status Register */
#define REG_PIOA_FELLSR               (*(WoReg*)0xFFFFF2D0U) /**< \brief (PIOA) Falling Edge/Low Level Select Register */
#define REG_PIOA_REHLSR               (*(WoReg*)0xFFFFF2D4U) /**< \brief (PIOA) Rising Edge/ High Level Select Register */
#define REG_PIOA_FRLHSR               (*(RoReg*)0xFFFFF2D8U) /**< \brief (PIOA) Fall/Rise - Low/High Status Register */
#define REG_PIOA_LOCKSR               (*(RoReg*)0xFFFFF2E0U) /**< \brief (PIOA) Lock Status */
#define REG_PIOA_WPMR                 (*(RwReg*)0xFFFFF2E4U) /**< \brief (PIOA) Write Protect Mode Register */
#define REG_PIOA_WPSR                 (*(RoReg*)0xFFFFF2E8U) /**< \brief (PIOA) Write Protect Status Register */
#define REG_PIOA_SCHMITT              (*(RwReg*)0xFFFFF300U) /**< \brief (PIOA) Schmitt Trigger Register */
#define REG_PIOA_DRIVER1              (*(RwReg*)0xFFFFF318U) /**< \brief (PIOA) I/O Drive Register 1 */
#define REG_PIOA_DRIVER2              (*(RwReg*)0xFFFFF31CU) /**< \brief (PIOA) I/O Drive Register 2 */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for PIOB peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_PIOB_PER                           (0xFFFFF400U) /**< \brief (PIOB) PIO Enable Register */
#define REG_PIOB_PDR                           (0xFFFFF404U) /**< \brief (PIOB) PIO Disable Register */
#define REG_PIOB_PSR                           (0xFFFFF408U) /**< \brief (PIOB) PIO Status Register */
#define REG_PIOB_OER                           (0xFFFFF410U) /**< \brief (PIOB) Output Enable Register */
#define REG_PIOB_ODR                           (0xFFFFF414U) /**< \brief (PIOB) Output Disable Register */
#define REG_PIOB_OSR                           (0xFFFFF418U) /**< \brief (PIOB) Output Status Register */
#define REG_PIOB_IFER                          (0xFFFFF420U) /**< \brief (PIOB) Glitch Input Filter Enable Register */
#define REG_PIOB_IFDR                          (0xFFFFF424U) /**< \brief (PIOB) Glitch Input Filter Disable Register */
#define REG_PIOB_IFSR                          (0xFFFFF428U) /**< \brief (PIOB) Glitch Input Filter Status Register */
#define REG_PIOB_SODR                          (0xFFFFF430U) /**< \brief (PIOB) Set Output Data Register */
#define REG_PIOB_CODR                          (0xFFFFF434U) /**< \brief (PIOB) Clear Output Data Register */
#define REG_PIOB_ODSR                          (0xFFFFF438U) /**< \brief (PIOB) Output Data Status Register */
#define REG_PIOB_PDSR                          (0xFFFFF43CU) /**< \brief (PIOB) Pin Data Status Register */
#define REG_PIOB_IER                           (0xFFFFF440U) /**< \brief (PIOB) Interrupt Enable Register */
#define REG_PIOB_IDR                           (0xFFFFF444U) /**< \brief (PIOB) Interrupt Disable Register */
#define REG_PIOB_IMR                           (0xFFFFF448U) /**< \brief (PIOB) Interrupt Mask Register */
#define REG_PIOB_ISR                           (0xFFFFF44CU) /**< \brief (PIOB) Interrupt Status Register */
#define REG_PIOB_MDER                          (0xFFFFF450U) /**< \brief (PIOB) Multi-driver Enable Register */
#define REG_PIOB_MDDR                          (0xFFFFF454U) /**< \brief (PIOB) Multi-driver Disable Register */
#define REG_PIOB_MDSR                          (0xFFFFF458U) /**< \brief (PIOB) Multi-driver Status Register */
#define REG_PIOB_PUDR                          (0xFFFFF460U) /**< \brief (PIOB) Pull-up Disable Register */
#define REG_PIOB_PUER                          (0xFFFFF464U) /**< \brief (PIOB) Pull-up Enable Register */
#define REG_PIOB_PUSR                          (0xFFFFF468U) /**< \brief (PIOB) Pad Pull-up Status Register */
#define REG_PIOB_ABCDSR                        (0xFFFFF470U) /**< \brief (PIOB) Peripheral Select Register */
#define REG_PIOB_IFSCDR                        (0xFFFFF480U) /**< \brief (PIOB) Input Filter Slow Clock Disable Register */
#define REG_PIOB_IFSCER                        (0xFFFFF484U) /**< \brief (PIOB) Input Filter Slow Clock Enable Register */
#define REG_PIOB_IFSCSR                        (0xFFFFF488U) /**< \brief (PIOB) Input Filter Slow Clock Status Register */
#define REG_PIOB_SCDR                          (0xFFFFF48CU) /**< \brief (PIOB) Slow Clock Divider Debouncing Register */
#define REG_PIOB_PPDDR                         (0xFFFFF490U) /**< \brief (PIOB) Pad Pull-down Disable Register */
#define REG_PIOB_PPDER                         (0xFFFFF494U) /**< \brief (PIOB) Pad Pull-down Enable Register */
#define REG_PIOB_PPDSR                         (0xFFFFF498U) /**< \brief (PIOB) Pad Pull-down Status Register */
#define REG_PIOB_OWER                          (0xFFFFF4A0U) /**< \brief (PIOB) Output Write Enable */
#define REG_PIOB_OWDR                          (0xFFFFF4A4U) /**< \brief (PIOB) Output Write Disable */
#define REG_PIOB_OWSR                          (0xFFFFF4A8U) /**< \brief (PIOB) Output Write Status Register */
#define REG_PIOB_AIMER                         (0xFFFFF4B0U) /**< \brief (PIOB) Additional Interrupt Modes Enable Register */
#define REG_PIOB_AIMDR                         (0xFFFFF4B4U) /**< \brief (PIOB) Additional Interrupt Modes Disables Register */
#define REG_PIOB_AIMMR                         (0xFFFFF4B8U) /**< \brief (PIOB) Additional Interrupt Modes Mask Register */
#define REG_PIOB_ESR                           (0xFFFFF4C0U) /**< \brief (PIOB) Edge Select Register */
#define REG_PIOB_LSR                           (0xFFFFF4C4U) /**< \brief (PIOB) Level Select Register */
#define REG_PIOB_ELSR                          (0xFFFFF4C8U) /**< \brief (PIOB) Edge/Level Status Register */
#define REG_PIOB_FELLSR                        (0xFFFFF4D0U) /**< \brief (PIOB) Falling Edge/Low Level Select Register */
#define REG_PIOB_REHLSR                        (0xFFFFF4D4U) /**< \brief (PIOB) Rising Edge/ High Level Select Register */
#define REG_PIOB_FRLHSR                        (0xFFFFF4D8U) /**< \brief (PIOB) Fall/Rise - Low/High Status Register */
#define REG_PIOB_LOCKSR                        (0xFFFFF4E0U) /**< \brief (PIOB) Lock Status */
#define REG_PIOB_WPMR                          (0xFFFFF4E4U) /**< \brief (PIOB) Write Protect Mode Register */
#define REG_PIOB_WPSR                          (0xFFFFF4E8U) /**< \brief (PIOB) Write Protect Status Register */
#define REG_PIOB_SCHMITT                       (0xFFFFF500U) /**< \brief (PIOB) Schmitt Trigger Register */
#define REG_PIOB_DRIVER1                       (0xFFFFF518U) /**< \brief (PIOB) I/O Drive Register 1 */
#define REG_PIOB_DRIVER2                       (0xFFFFF51CU) /**< \brief (PIOB) I/O Drive Register 2 */
#else
#define REG_PIOB_PER                  (*(WoReg*)0xFFFFF400U) /**< \brief (PIOB) PIO Enable Register */
#define REG_PIOB_PDR                  (*(WoReg*)0xFFFFF404U) /**< \brief (PIOB) PIO Disable Register */
#define REG_PIOB_PSR                  (*(RoReg*)0xFFFFF408U) /**< \brief (PIOB) PIO Status Register */
#define REG_PIOB_OER                  (*(WoReg*)0xFFFFF410U) /**< \brief (PIOB) Output Enable Register */
#define REG_PIOB_ODR                  (*(WoReg*)0xFFFFF414U) /**< \brief (PIOB) Output Disable Register */
#define REG_PIOB_OSR                  (*(RoReg*)0xFFFFF418U) /**< \brief (PIOB) Output Status Register */
#define REG_PIOB_IFER                 (*(WoReg*)0xFFFFF420U) /**< \brief (PIOB) Glitch Input Filter Enable Register */
#define REG_PIOB_IFDR                 (*(WoReg*)0xFFFFF424U) /**< \brief (PIOB) Glitch Input Filter Disable Register */
#define REG_PIOB_IFSR                 (*(RoReg*)0xFFFFF428U) /**< \brief (PIOB) Glitch Input Filter Status Register */
#define REG_PIOB_SODR                 (*(WoReg*)0xFFFFF430U) /**< \brief (PIOB) Set Output Data Register */
#define REG_PIOB_CODR                 (*(WoReg*)0xFFFFF434U) /**< \brief (PIOB) Clear Output Data Register */
#define REG_PIOB_ODSR                 (*(RwReg*)0xFFFFF438U) /**< \brief (PIOB) Output Data Status Register */
#define REG_PIOB_PDSR                 (*(RoReg*)0xFFFFF43CU) /**< \brief (PIOB) Pin Data Status Register */
#define REG_PIOB_IER                  (*(WoReg*)0xFFFFF440U) /**< \brief (PIOB) Interrupt Enable Register */
#define REG_PIOB_IDR                  (*(WoReg*)0xFFFFF444U) /**< \brief (PIOB) Interrupt Disable Register */
#define REG_PIOB_IMR                  (*(RoReg*)0xFFFFF448U) /**< \brief (PIOB) Interrupt Mask Register */
#define REG_PIOB_ISR                  (*(RoReg*)0xFFFFF44CU) /**< \brief (PIOB) Interrupt Status Register */
#define REG_PIOB_MDER                 (*(WoReg*)0xFFFFF450U) /**< \brief (PIOB) Multi-driver Enable Register */
#define REG_PIOB_MDDR                 (*(WoReg*)0xFFFFF454U) /**< \brief (PIOB) Multi-driver Disable Register */
#define REG_PIOB_MDSR                 (*(RoReg*)0xFFFFF458U) /**< \brief (PIOB) Multi-driver Status Register */
#define REG_PIOB_PUDR                 (*(WoReg*)0xFFFFF460U) /**< \brief (PIOB) Pull-up Disable Register */
#define REG_PIOB_PUER                 (*(WoReg*)0xFFFFF464U) /**< \brief (PIOB) Pull-up Enable Register */
#define REG_PIOB_PUSR                 (*(RoReg*)0xFFFFF468U) /**< \brief (PIOB) Pad Pull-up Status Register */
#define REG_PIOB_ABCDSR               (*(RwReg*)0xFFFFF470U) /**< \brief (PIOB) Peripheral Select Register */
#define REG_PIOB_IFSCDR               (*(WoReg*)0xFFFFF480U) /**< \brief (PIOB) Input Filter Slow Clock Disable Register */
#define REG_PIOB_IFSCER               (*(WoReg*)0xFFFFF484U) /**< \brief (PIOB) Input Filter Slow Clock Enable Register */
#define REG_PIOB_IFSCSR               (*(RoReg*)0xFFFFF488U) /**< \brief (PIOB) Input Filter Slow Clock Status Register */
#define REG_PIOB_SCDR                 (*(RwReg*)0xFFFFF48CU) /**< \brief (PIOB) Slow Clock Divider Debouncing Register */
#define REG_PIOB_PPDDR                (*(WoReg*)0xFFFFF490U) /**< \brief (PIOB) Pad Pull-down Disable Register */
#define REG_PIOB_PPDER                (*(WoReg*)0xFFFFF494U) /**< \brief (PIOB) Pad Pull-down Enable Register */
#define REG_PIOB_PPDSR                (*(RoReg*)0xFFFFF498U) /**< \brief (PIOB) Pad Pull-down Status Register */
#define REG_PIOB_OWER                 (*(WoReg*)0xFFFFF4A0U) /**< \brief (PIOB) Output Write Enable */
#define REG_PIOB_OWDR                 (*(WoReg*)0xFFFFF4A4U) /**< \brief (PIOB) Output Write Disable */
#define REG_PIOB_OWSR                 (*(RoReg*)0xFFFFF4A8U) /**< \brief (PIOB) Output Write Status Register */
#define REG_PIOB_AIMER                (*(WoReg*)0xFFFFF4B0U) /**< \brief (PIOB) Additional Interrupt Modes Enable Register */
#define REG_PIOB_AIMDR                (*(WoReg*)0xFFFFF4B4U) /**< \brief (PIOB) Additional Interrupt Modes Disables Register */
#define REG_PIOB_AIMMR                (*(RoReg*)0xFFFFF4B8U) /**< \brief (PIOB) Additional Interrupt Modes Mask Register */
#define REG_PIOB_ESR                  (*(WoReg*)0xFFFFF4C0U) /**< \brief (PIOB) Edge Select Register */
#define REG_PIOB_LSR                  (*(WoReg*)0xFFFFF4C4U) /**< \brief (PIOB) Level Select Register */
#define REG_PIOB_ELSR                 (*(RoReg*)0xFFFFF4C8U) /**< \brief (PIOB) Edge/Level Status Register */
#define REG_PIOB_FELLSR               (*(WoReg*)0xFFFFF4D0U) /**< \brief (PIOB) Falling Edge/Low Level Select Register */
#define REG_PIOB_REHLSR               (*(WoReg*)0xFFFFF4D4U) /**< \brief (PIOB) Rising Edge/ High Level Select Register */
#define REG_PIOB_FRLHSR               (*(RoReg*)0xFFFFF4D8U) /**< \brief (PIOB) Fall/Rise - Low/High Status Register */
#define REG_PIOB_LOCKSR               (*(RoReg*)0xFFFFF4E0U) /**< \brief (PIOB) Lock Status */
#define REG_PIOB_WPMR                 (*(RwReg*)0xFFFFF4E4U) /**< \brief (PIOB) Write Protect Mode Register */
#define REG_PIOB_WPSR                 (*(RoReg*)0xFFFFF4E8U) /**< \brief (PIOB) Write Protect Status Register */
#define REG_PIOB_SCHMITT              (*(RwReg*)0xFFFFF500U) /**< \brief (PIOB) Schmitt Trigger Register */
#define REG_PIOB_DRIVER1              (*(RwReg*)0xFFFFF518U) /**< \brief (PIOB) I/O Drive Register 1 */
#define REG_PIOB_DRIVER2              (*(RwReg*)0xFFFFF51CU) /**< \brief (PIOB) I/O Drive Register 2 */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for PIOC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_PIOC_PER                           (0xFFFFF600U) /**< \brief (PIOC) PIO Enable Register */
#define REG_PIOC_PDR                           (0xFFFFF604U) /**< \brief (PIOC) PIO Disable Register */
#define REG_PIOC_PSR                           (0xFFFFF608U) /**< \brief (PIOC) PIO Status Register */
#define REG_PIOC_OER                           (0xFFFFF610U) /**< \brief (PIOC) Output Enable Register */
#define REG_PIOC_ODR                           (0xFFFFF614U) /**< \brief (PIOC) Output Disable Register */
#define REG_PIOC_OSR                           (0xFFFFF618U) /**< \brief (PIOC) Output Status Register */
#define REG_PIOC_IFER                          (0xFFFFF620U) /**< \brief (PIOC) Glitch Input Filter Enable Register */
#define REG_PIOC_IFDR                          (0xFFFFF624U) /**< \brief (PIOC) Glitch Input Filter Disable Register */
#define REG_PIOC_IFSR                          (0xFFFFF628U) /**< \brief (PIOC) Glitch Input Filter Status Register */
#define REG_PIOC_SODR                          (0xFFFFF630U) /**< \brief (PIOC) Set Output Data Register */
#define REG_PIOC_CODR                          (0xFFFFF634U) /**< \brief (PIOC) Clear Output Data Register */
#define REG_PIOC_ODSR                          (0xFFFFF638U) /**< \brief (PIOC) Output Data Status Register */
#define REG_PIOC_PDSR                          (0xFFFFF63CU) /**< \brief (PIOC) Pin Data Status Register */
#define REG_PIOC_IER                           (0xFFFFF640U) /**< \brief (PIOC) Interrupt Enable Register */
#define REG_PIOC_IDR                           (0xFFFFF644U) /**< \brief (PIOC) Interrupt Disable Register */
#define REG_PIOC_IMR                           (0xFFFFF648U) /**< \brief (PIOC) Interrupt Mask Register */
#define REG_PIOC_ISR                           (0xFFFFF64CU) /**< \brief (PIOC) Interrupt Status Register */
#define REG_PIOC_MDER                          (0xFFFFF650U) /**< \brief (PIOC) Multi-driver Enable Register */
#define REG_PIOC_MDDR                          (0xFFFFF654U) /**< \brief (PIOC) Multi-driver Disable Register */
#define REG_PIOC_MDSR                          (0xFFFFF658U) /**< \brief (PIOC) Multi-driver Status Register */
#define REG_PIOC_PUDR                          (0xFFFFF660U) /**< \brief (PIOC) Pull-up Disable Register */
#define REG_PIOC_PUER                          (0xFFFFF664U) /**< \brief (PIOC) Pull-up Enable Register */
#define REG_PIOC_PUSR                          (0xFFFFF668U) /**< \brief (PIOC) Pad Pull-up Status Register */
#define REG_PIOC_ABCDSR                        (0xFFFFF670U) /**< \brief (PIOC) Peripheral Select Register */
#define REG_PIOC_IFSCDR                        (0xFFFFF680U) /**< \brief (PIOC) Input Filter Slow Clock Disable Register */
#define REG_PIOC_IFSCER                        (0xFFFFF684U) /**< \brief (PIOC) Input Filter Slow Clock Enable Register */
#define REG_PIOC_IFSCSR                        (0xFFFFF688U) /**< \brief (PIOC) Input Filter Slow Clock Status Register */
#define REG_PIOC_SCDR                          (0xFFFFF68CU) /**< \brief (PIOC) Slow Clock Divider Debouncing Register */
#define REG_PIOC_PPDDR                         (0xFFFFF690U) /**< \brief (PIOC) Pad Pull-down Disable Register */
#define REG_PIOC_PPDER                         (0xFFFFF694U) /**< \brief (PIOC) Pad Pull-down Enable Register */
#define REG_PIOC_PPDSR                         (0xFFFFF698U) /**< \brief (PIOC) Pad Pull-down Status Register */
#define REG_PIOC_OWER                          (0xFFFFF6A0U) /**< \brief (PIOC) Output Write Enable */
#define REG_PIOC_OWDR                          (0xFFFFF6A4U) /**< \brief (PIOC) Output Write Disable */
#define REG_PIOC_OWSR                          (0xFFFFF6A8U) /**< \brief (PIOC) Output Write Status Register */
#define REG_PIOC_AIMER                         (0xFFFFF6B0U) /**< \brief (PIOC) Additional Interrupt Modes Enable Register */
#define REG_PIOC_AIMDR                         (0xFFFFF6B4U) /**< \brief (PIOC) Additional Interrupt Modes Disables Register */
#define REG_PIOC_AIMMR                         (0xFFFFF6B8U) /**< \brief (PIOC) Additional Interrupt Modes Mask Register */
#define REG_PIOC_ESR                           (0xFFFFF6C0U) /**< \brief (PIOC) Edge Select Register */
#define REG_PIOC_LSR                           (0xFFFFF6C4U) /**< \brief (PIOC) Level Select Register */
#define REG_PIOC_ELSR                          (0xFFFFF6C8U) /**< \brief (PIOC) Edge/Level Status Register */
#define REG_PIOC_FELLSR                        (0xFFFFF6D0U) /**< \brief (PIOC) Falling Edge/Low Level Select Register */
#define REG_PIOC_REHLSR                        (0xFFFFF6D4U) /**< \brief (PIOC) Rising Edge/ High Level Select Register */
#define REG_PIOC_FRLHSR                        (0xFFFFF6D8U) /**< \brief (PIOC) Fall/Rise - Low/High Status Register */
#define REG_PIOC_LOCKSR                        (0xFFFFF6E0U) /**< \brief (PIOC) Lock Status */
#define REG_PIOC_WPMR                          (0xFFFFF6E4U) /**< \brief (PIOC) Write Protect Mode Register */
#define REG_PIOC_WPSR                          (0xFFFFF6E8U) /**< \brief (PIOC) Write Protect Status Register */
#define REG_PIOC_SCHMITT                       (0xFFFFF700U) /**< \brief (PIOC) Schmitt Trigger Register */
#define REG_PIOC_DRIVER1                       (0xFFFFF718U) /**< \brief (PIOC) I/O Drive Register 1 */
#define REG_PIOC_DRIVER2                       (0xFFFFF71CU) /**< \brief (PIOC) I/O Drive Register 2 */
#else
#define REG_PIOC_PER                  (*(WoReg*)0xFFFFF600U) /**< \brief (PIOC) PIO Enable Register */
#define REG_PIOC_PDR                  (*(WoReg*)0xFFFFF604U) /**< \brief (PIOC) PIO Disable Register */
#define REG_PIOC_PSR                  (*(RoReg*)0xFFFFF608U) /**< \brief (PIOC) PIO Status Register */
#define REG_PIOC_OER                  (*(WoReg*)0xFFFFF610U) /**< \brief (PIOC) Output Enable Register */
#define REG_PIOC_ODR                  (*(WoReg*)0xFFFFF614U) /**< \brief (PIOC) Output Disable Register */
#define REG_PIOC_OSR                  (*(RoReg*)0xFFFFF618U) /**< \brief (PIOC) Output Status Register */
#define REG_PIOC_IFER                 (*(WoReg*)0xFFFFF620U) /**< \brief (PIOC) Glitch Input Filter Enable Register */
#define REG_PIOC_IFDR                 (*(WoReg*)0xFFFFF624U) /**< \brief (PIOC) Glitch Input Filter Disable Register */
#define REG_PIOC_IFSR                 (*(RoReg*)0xFFFFF628U) /**< \brief (PIOC) Glitch Input Filter Status Register */
#define REG_PIOC_SODR                 (*(WoReg*)0xFFFFF630U) /**< \brief (PIOC) Set Output Data Register */
#define REG_PIOC_CODR                 (*(WoReg*)0xFFFFF634U) /**< \brief (PIOC) Clear Output Data Register */
#define REG_PIOC_ODSR                 (*(RwReg*)0xFFFFF638U) /**< \brief (PIOC) Output Data Status Register */
#define REG_PIOC_PDSR                 (*(RoReg*)0xFFFFF63CU) /**< \brief (PIOC) Pin Data Status Register */
#define REG_PIOC_IER                  (*(WoReg*)0xFFFFF640U) /**< \brief (PIOC) Interrupt Enable Register */
#define REG_PIOC_IDR                  (*(WoReg*)0xFFFFF644U) /**< \brief (PIOC) Interrupt Disable Register */
#define REG_PIOC_IMR                  (*(RoReg*)0xFFFFF648U) /**< \brief (PIOC) Interrupt Mask Register */
#define REG_PIOC_ISR                  (*(RoReg*)0xFFFFF64CU) /**< \brief (PIOC) Interrupt Status Register */
#define REG_PIOC_MDER                 (*(WoReg*)0xFFFFF650U) /**< \brief (PIOC) Multi-driver Enable Register */
#define REG_PIOC_MDDR                 (*(WoReg*)0xFFFFF654U) /**< \brief (PIOC) Multi-driver Disable Register */
#define REG_PIOC_MDSR                 (*(RoReg*)0xFFFFF658U) /**< \brief (PIOC) Multi-driver Status Register */
#define REG_PIOC_PUDR                 (*(WoReg*)0xFFFFF660U) /**< \brief (PIOC) Pull-up Disable Register */
#define REG_PIOC_PUER                 (*(WoReg*)0xFFFFF664U) /**< \brief (PIOC) Pull-up Enable Register */
#define REG_PIOC_PUSR                 (*(RoReg*)0xFFFFF668U) /**< \brief (PIOC) Pad Pull-up Status Register */
#define REG_PIOC_ABCDSR               (*(RwReg*)0xFFFFF670U) /**< \brief (PIOC) Peripheral Select Register */
#define REG_PIOC_IFSCDR               (*(WoReg*)0xFFFFF680U) /**< \brief (PIOC) Input Filter Slow Clock Disable Register */
#define REG_PIOC_IFSCER               (*(WoReg*)0xFFFFF684U) /**< \brief (PIOC) Input Filter Slow Clock Enable Register */
#define REG_PIOC_IFSCSR               (*(RoReg*)0xFFFFF688U) /**< \brief (PIOC) Input Filter Slow Clock Status Register */
#define REG_PIOC_SCDR                 (*(RwReg*)0xFFFFF68CU) /**< \brief (PIOC) Slow Clock Divider Debouncing Register */
#define REG_PIOC_PPDDR                (*(WoReg*)0xFFFFF690U) /**< \brief (PIOC) Pad Pull-down Disable Register */
#define REG_PIOC_PPDER                (*(WoReg*)0xFFFFF694U) /**< \brief (PIOC) Pad Pull-down Enable Register */
#define REG_PIOC_PPDSR                (*(RoReg*)0xFFFFF698U) /**< \brief (PIOC) Pad Pull-down Status Register */
#define REG_PIOC_OWER                 (*(WoReg*)0xFFFFF6A0U) /**< \brief (PIOC) Output Write Enable */
#define REG_PIOC_OWDR                 (*(WoReg*)0xFFFFF6A4U) /**< \brief (PIOC) Output Write Disable */
#define REG_PIOC_OWSR                 (*(RoReg*)0xFFFFF6A8U) /**< \brief (PIOC) Output Write Status Register */
#define REG_PIOC_AIMER                (*(WoReg*)0xFFFFF6B0U) /**< \brief (PIOC) Additional Interrupt Modes Enable Register */
#define REG_PIOC_AIMDR                (*(WoReg*)0xFFFFF6B4U) /**< \brief (PIOC) Additional Interrupt Modes Disables Register */
#define REG_PIOC_AIMMR                (*(RoReg*)0xFFFFF6B8U) /**< \brief (PIOC) Additional Interrupt Modes Mask Register */
#define REG_PIOC_ESR                  (*(WoReg*)0xFFFFF6C0U) /**< \brief (PIOC) Edge Select Register */
#define REG_PIOC_LSR                  (*(WoReg*)0xFFFFF6C4U) /**< \brief (PIOC) Level Select Register */
#define REG_PIOC_ELSR                 (*(RoReg*)0xFFFFF6C8U) /**< \brief (PIOC) Edge/Level Status Register */
#define REG_PIOC_FELLSR               (*(WoReg*)0xFFFFF6D0U) /**< \brief (PIOC) Falling Edge/Low Level Select Register */
#define REG_PIOC_REHLSR               (*(WoReg*)0xFFFFF6D4U) /**< \brief (PIOC) Rising Edge/ High Level Select Register */
#define REG_PIOC_FRLHSR               (*(RoReg*)0xFFFFF6D8U) /**< \brief (PIOC) Fall/Rise - Low/High Status Register */
#define REG_PIOC_LOCKSR               (*(RoReg*)0xFFFFF6E0U) /**< \brief (PIOC) Lock Status */
#define REG_PIOC_WPMR                 (*(RwReg*)0xFFFFF6E4U) /**< \brief (PIOC) Write Protect Mode Register */
#define REG_PIOC_WPSR                 (*(RoReg*)0xFFFFF6E8U) /**< \brief (PIOC) Write Protect Status Register */
#define REG_PIOC_SCHMITT              (*(RwReg*)0xFFFFF700U) /**< \brief (PIOC) Schmitt Trigger Register */
#define REG_PIOC_DRIVER1              (*(RwReg*)0xFFFFF718U) /**< \brief (PIOC) I/O Drive Register 1 */
#define REG_PIOC_DRIVER2              (*(RwReg*)0xFFFFF71CU) /**< \brief (PIOC) I/O Drive Register 2 */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for PIOD peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_PIOD_PER                           (0xFFFFF800U) /**< \brief (PIOD) PIO Enable Register */
#define REG_PIOD_PDR                           (0xFFFFF804U) /**< \brief (PIOD) PIO Disable Register */
#define REG_PIOD_PSR                           (0xFFFFF808U) /**< \brief (PIOD) PIO Status Register */
#define REG_PIOD_OER                           (0xFFFFF810U) /**< \brief (PIOD) Output Enable Register */
#define REG_PIOD_ODR                           (0xFFFFF814U) /**< \brief (PIOD) Output Disable Register */
#define REG_PIOD_OSR                           (0xFFFFF818U) /**< \brief (PIOD) Output Status Register */
#define REG_PIOD_IFER                          (0xFFFFF820U) /**< \brief (PIOD) Glitch Input Filter Enable Register */
#define REG_PIOD_IFDR                          (0xFFFFF824U) /**< \brief (PIOD) Glitch Input Filter Disable Register */
#define REG_PIOD_IFSR                          (0xFFFFF828U) /**< \brief (PIOD) Glitch Input Filter Status Register */
#define REG_PIOD_SODR                          (0xFFFFF830U) /**< \brief (PIOD) Set Output Data Register */
#define REG_PIOD_CODR                          (0xFFFFF834U) /**< \brief (PIOD) Clear Output Data Register */
#define REG_PIOD_ODSR                          (0xFFFFF838U) /**< \brief (PIOD) Output Data Status Register */
#define REG_PIOD_PDSR                          (0xFFFFF83CU) /**< \brief (PIOD) Pin Data Status Register */
#define REG_PIOD_IER                           (0xFFFFF840U) /**< \brief (PIOD) Interrupt Enable Register */
#define REG_PIOD_IDR                           (0xFFFFF844U) /**< \brief (PIOD) Interrupt Disable Register */
#define REG_PIOD_IMR                           (0xFFFFF848U) /**< \brief (PIOD) Interrupt Mask Register */
#define REG_PIOD_ISR                           (0xFFFFF84CU) /**< \brief (PIOD) Interrupt Status Register */
#define REG_PIOD_MDER                          (0xFFFFF850U) /**< \brief (PIOD) Multi-driver Enable Register */
#define REG_PIOD_MDDR                          (0xFFFFF854U) /**< \brief (PIOD) Multi-driver Disable Register */
#define REG_PIOD_MDSR                          (0xFFFFF858U) /**< \brief (PIOD) Multi-driver Status Register */
#define REG_PIOD_PUDR                          (0xFFFFF860U) /**< \brief (PIOD) Pull-up Disable Register */
#define REG_PIOD_PUER                          (0xFFFFF864U) /**< \brief (PIOD) Pull-up Enable Register */
#define REG_PIOD_PUSR                          (0xFFFFF868U) /**< \brief (PIOD) Pad Pull-up Status Register */
#define REG_PIOD_ABCDSR                        (0xFFFFF870U) /**< \brief (PIOD) Peripheral Select Register */
#define REG_PIOD_IFSCDR                        (0xFFFFF880U) /**< \brief (PIOD) Input Filter Slow Clock Disable Register */
#define REG_PIOD_IFSCER                        (0xFFFFF884U) /**< \brief (PIOD) Input Filter Slow Clock Enable Register */
#define REG_PIOD_IFSCSR                        (0xFFFFF888U) /**< \brief (PIOD) Input Filter Slow Clock Status Register */
#define REG_PIOD_SCDR                          (0xFFFFF88CU) /**< \brief (PIOD) Slow Clock Divider Debouncing Register */
#define REG_PIOD_PPDDR                         (0xFFFFF890U) /**< \brief (PIOD) Pad Pull-down Disable Register */
#define REG_PIOD_PPDER                         (0xFFFFF894U) /**< \brief (PIOD) Pad Pull-down Enable Register */
#define REG_PIOD_PPDSR                         (0xFFFFF898U) /**< \brief (PIOD) Pad Pull-down Status Register */
#define REG_PIOD_OWER                          (0xFFFFF8A0U) /**< \brief (PIOD) Output Write Enable */
#define REG_PIOD_OWDR                          (0xFFFFF8A4U) /**< \brief (PIOD) Output Write Disable */
#define REG_PIOD_OWSR                          (0xFFFFF8A8U) /**< \brief (PIOD) Output Write Status Register */
#define REG_PIOD_AIMER                         (0xFFFFF8B0U) /**< \brief (PIOD) Additional Interrupt Modes Enable Register */
#define REG_PIOD_AIMDR                         (0xFFFFF8B4U) /**< \brief (PIOD) Additional Interrupt Modes Disables Register */
#define REG_PIOD_AIMMR                         (0xFFFFF8B8U) /**< \brief (PIOD) Additional Interrupt Modes Mask Register */
#define REG_PIOD_ESR                           (0xFFFFF8C0U) /**< \brief (PIOD) Edge Select Register */
#define REG_PIOD_LSR                           (0xFFFFF8C4U) /**< \brief (PIOD) Level Select Register */
#define REG_PIOD_ELSR                          (0xFFFFF8C8U) /**< \brief (PIOD) Edge/Level Status Register */
#define REG_PIOD_FELLSR                        (0xFFFFF8D0U) /**< \brief (PIOD) Falling Edge/Low Level Select Register */
#define REG_PIOD_REHLSR                        (0xFFFFF8D4U) /**< \brief (PIOD) Rising Edge/ High Level Select Register */
#define REG_PIOD_FRLHSR                        (0xFFFFF8D8U) /**< \brief (PIOD) Fall/Rise - Low/High Status Register */
#define REG_PIOD_LOCKSR                        (0xFFFFF8E0U) /**< \brief (PIOD) Lock Status */
#define REG_PIOD_WPMR                          (0xFFFFF8E4U) /**< \brief (PIOD) Write Protect Mode Register */
#define REG_PIOD_WPSR                          (0xFFFFF8E8U) /**< \brief (PIOD) Write Protect Status Register */
#define REG_PIOD_SCHMITT                       (0xFFFFF900U) /**< \brief (PIOD) Schmitt Trigger Register */
#define REG_PIOD_DRIVER1                       (0xFFFFF918U) /**< \brief (PIOD) I/O Drive Register 1 */
#define REG_PIOD_DRIVER2                       (0xFFFFF91CU) /**< \brief (PIOD) I/O Drive Register 2 */
#else
#define REG_PIOD_PER                  (*(WoReg*)0xFFFFF800U) /**< \brief (PIOD) PIO Enable Register */
#define REG_PIOD_PDR                  (*(WoReg*)0xFFFFF804U) /**< \brief (PIOD) PIO Disable Register */
#define REG_PIOD_PSR                  (*(RoReg*)0xFFFFF808U) /**< \brief (PIOD) PIO Status Register */
#define REG_PIOD_OER                  (*(WoReg*)0xFFFFF810U) /**< \brief (PIOD) Output Enable Register */
#define REG_PIOD_ODR                  (*(WoReg*)0xFFFFF814U) /**< \brief (PIOD) Output Disable Register */
#define REG_PIOD_OSR                  (*(RoReg*)0xFFFFF818U) /**< \brief (PIOD) Output Status Register */
#define REG_PIOD_IFER                 (*(WoReg*)0xFFFFF820U) /**< \brief (PIOD) Glitch Input Filter Enable Register */
#define REG_PIOD_IFDR                 (*(WoReg*)0xFFFFF824U) /**< \brief (PIOD) Glitch Input Filter Disable Register */
#define REG_PIOD_IFSR                 (*(RoReg*)0xFFFFF828U) /**< \brief (PIOD) Glitch Input Filter Status Register */
#define REG_PIOD_SODR                 (*(WoReg*)0xFFFFF830U) /**< \brief (PIOD) Set Output Data Register */
#define REG_PIOD_CODR                 (*(WoReg*)0xFFFFF834U) /**< \brief (PIOD) Clear Output Data Register */
#define REG_PIOD_ODSR                 (*(RwReg*)0xFFFFF838U) /**< \brief (PIOD) Output Data Status Register */
#define REG_PIOD_PDSR                 (*(RoReg*)0xFFFFF83CU) /**< \brief (PIOD) Pin Data Status Register */
#define REG_PIOD_IER                  (*(WoReg*)0xFFFFF840U) /**< \brief (PIOD) Interrupt Enable Register */
#define REG_PIOD_IDR                  (*(WoReg*)0xFFFFF844U) /**< \brief (PIOD) Interrupt Disable Register */
#define REG_PIOD_IMR                  (*(RoReg*)0xFFFFF848U) /**< \brief (PIOD) Interrupt Mask Register */
#define REG_PIOD_ISR                  (*(RoReg*)0xFFFFF84CU) /**< \brief (PIOD) Interrupt Status Register */
#define REG_PIOD_MDER                 (*(WoReg*)0xFFFFF850U) /**< \brief (PIOD) Multi-driver Enable Register */
#define REG_PIOD_MDDR                 (*(WoReg*)0xFFFFF854U) /**< \brief (PIOD) Multi-driver Disable Register */
#define REG_PIOD_MDSR                 (*(RoReg*)0xFFFFF858U) /**< \brief (PIOD) Multi-driver Status Register */
#define REG_PIOD_PUDR                 (*(WoReg*)0xFFFFF860U) /**< \brief (PIOD) Pull-up Disable Register */
#define REG_PIOD_PUER                 (*(WoReg*)0xFFFFF864U) /**< \brief (PIOD) Pull-up Enable Register */
#define REG_PIOD_PUSR                 (*(RoReg*)0xFFFFF868U) /**< \brief (PIOD) Pad Pull-up Status Register */
#define REG_PIOD_ABCDSR               (*(RwReg*)0xFFFFF870U) /**< \brief (PIOD) Peripheral Select Register */
#define REG_PIOD_IFSCDR               (*(WoReg*)0xFFFFF880U) /**< \brief (PIOD) Input Filter Slow Clock Disable Register */
#define REG_PIOD_IFSCER               (*(WoReg*)0xFFFFF884U) /**< \brief (PIOD) Input Filter Slow Clock Enable Register */
#define REG_PIOD_IFSCSR               (*(RoReg*)0xFFFFF888U) /**< \brief (PIOD) Input Filter Slow Clock Status Register */
#define REG_PIOD_SCDR                 (*(RwReg*)0xFFFFF88CU) /**< \brief (PIOD) Slow Clock Divider Debouncing Register */
#define REG_PIOD_PPDDR                (*(WoReg*)0xFFFFF890U) /**< \brief (PIOD) Pad Pull-down Disable Register */
#define REG_PIOD_PPDER                (*(WoReg*)0xFFFFF894U) /**< \brief (PIOD) Pad Pull-down Enable Register */
#define REG_PIOD_PPDSR                (*(RoReg*)0xFFFFF898U) /**< \brief (PIOD) Pad Pull-down Status Register */
#define REG_PIOD_OWER                 (*(WoReg*)0xFFFFF8A0U) /**< \brief (PIOD) Output Write Enable */
#define REG_PIOD_OWDR                 (*(WoReg*)0xFFFFF8A4U) /**< \brief (PIOD) Output Write Disable */
#define REG_PIOD_OWSR                 (*(RoReg*)0xFFFFF8A8U) /**< \brief (PIOD) Output Write Status Register */
#define REG_PIOD_AIMER                (*(WoReg*)0xFFFFF8B0U) /**< \brief (PIOD) Additional Interrupt Modes Enable Register */
#define REG_PIOD_AIMDR                (*(WoReg*)0xFFFFF8B4U) /**< \brief (PIOD) Additional Interrupt Modes Disables Register */
#define REG_PIOD_AIMMR                (*(RoReg*)0xFFFFF8B8U) /**< \brief (PIOD) Additional Interrupt Modes Mask Register */
#define REG_PIOD_ESR                  (*(WoReg*)0xFFFFF8C0U) /**< \brief (PIOD) Edge Select Register */
#define REG_PIOD_LSR                  (*(WoReg*)0xFFFFF8C4U) /**< \brief (PIOD) Level Select Register */
#define REG_PIOD_ELSR                 (*(RoReg*)0xFFFFF8C8U) /**< \brief (PIOD) Edge/Level Status Register */
#define REG_PIOD_FELLSR               (*(WoReg*)0xFFFFF8D0U) /**< \brief (PIOD) Falling Edge/Low Level Select Register */
#define REG_PIOD_REHLSR               (*(WoReg*)0xFFFFF8D4U) /**< \brief (PIOD) Rising Edge/ High Level Select Register */
#define REG_PIOD_FRLHSR               (*(RoReg*)0xFFFFF8D8U) /**< \brief (PIOD) Fall/Rise - Low/High Status Register */
#define REG_PIOD_LOCKSR               (*(RoReg*)0xFFFFF8E0U) /**< \brief (PIOD) Lock Status */
#define REG_PIOD_WPMR                 (*(RwReg*)0xFFFFF8E4U) /**< \brief (PIOD) Write Protect Mode Register */
#define REG_PIOD_WPSR                 (*(RoReg*)0xFFFFF8E8U) /**< \brief (PIOD) Write Protect Status Register */
#define REG_PIOD_SCHMITT              (*(RwReg*)0xFFFFF900U) /**< \brief (PIOD) Schmitt Trigger Register */
#define REG_PIOD_DRIVER1              (*(RwReg*)0xFFFFF918U) /**< \brief (PIOD) I/O Drive Register 1 */
#define REG_PIOD_DRIVER2              (*(RwReg*)0xFFFFF91CU) /**< \brief (PIOD) I/O Drive Register 2 */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for PIOE peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_PIOE_PER                           (0xFFFFFA00U) /**< \brief (PIOE) PIO Enable Register */
#define REG_PIOE_PDR                           (0xFFFFFA04U) /**< \brief (PIOE) PIO Disable Register */
#define REG_PIOE_PSR                           (0xFFFFFA08U) /**< \brief (PIOE) PIO Status Register */
#define REG_PIOE_OER                           (0xFFFFFA10U) /**< \brief (PIOE) Output Enable Register */
#define REG_PIOE_ODR                           (0xFFFFFA14U) /**< \brief (PIOE) Output Disable Register */
#define REG_PIOE_OSR                           (0xFFFFFA18U) /**< \brief (PIOE) Output Status Register */
#define REG_PIOE_IFER                          (0xFFFFFA20U) /**< \brief (PIOE) Glitch Input Filter Enable Register */
#define REG_PIOE_IFDR                          (0xFFFFFA24U) /**< \brief (PIOE) Glitch Input Filter Disable Register */
#define REG_PIOE_IFSR                          (0xFFFFFA28U) /**< \brief (PIOE) Glitch Input Filter Status Register */
#define REG_PIOE_SODR                          (0xFFFFFA30U) /**< \brief (PIOE) Set Output Data Register */
#define REG_PIOE_CODR                          (0xFFFFFA34U) /**< \brief (PIOE) Clear Output Data Register */
#define REG_PIOE_ODSR                          (0xFFFFFA38U) /**< \brief (PIOE) Output Data Status Register */
#define REG_PIOE_PDSR                          (0xFFFFFA3CU) /**< \brief (PIOE) Pin Data Status Register */
#define REG_PIOE_IER                           (0xFFFFFA40U) /**< \brief (PIOE) Interrupt Enable Register */
#define REG_PIOE_IDR                           (0xFFFFFA44U) /**< \brief (PIOE) Interrupt Disable Register */
#define REG_PIOE_IMR                           (0xFFFFFA48U) /**< \brief (PIOE) Interrupt Mask Register */
#define REG_PIOE_ISR                           (0xFFFFFA4CU) /**< \brief (PIOE) Interrupt Status Register */
#define REG_PIOE_MDER                          (0xFFFFFA50U) /**< \brief (PIOE) Multi-driver Enable Register */
#define REG_PIOE_MDDR                          (0xFFFFFA54U) /**< \brief (PIOE) Multi-driver Disable Register */
#define REG_PIOE_MDSR                          (0xFFFFFA58U) /**< \brief (PIOE) Multi-driver Status Register */
#define REG_PIOE_PUDR                          (0xFFFFFA60U) /**< \brief (PIOE) Pull-up Disable Register */
#define REG_PIOE_PUER                          (0xFFFFFA64U) /**< \brief (PIOE) Pull-up Enable Register */
#define REG_PIOE_PUSR                          (0xFFFFFA68U) /**< \brief (PIOE) Pad Pull-up Status Register */
#define REG_PIOE_ABCDSR                        (0xFFFFFA70U) /**< \brief (PIOE) Peripheral Select Register */
#define REG_PIOE_IFSCDR                        (0xFFFFFA80U) /**< \brief (PIOE) Input Filter Slow Clock Disable Register */
#define REG_PIOE_IFSCER                        (0xFFFFFA84U) /**< \brief (PIOE) Input Filter Slow Clock Enable Register */
#define REG_PIOE_IFSCSR                        (0xFFFFFA88U) /**< \brief (PIOE) Input Filter Slow Clock Status Register */
#define REG_PIOE_SCDR                          (0xFFFFFA8CU) /**< \brief (PIOE) Slow Clock Divider Debouncing Register */
#define REG_PIOE_PPDDR                         (0xFFFFFA90U) /**< \brief (PIOE) Pad Pull-down Disable Register */
#define REG_PIOE_PPDER                         (0xFFFFFA94U) /**< \brief (PIOE) Pad Pull-down Enable Register */
#define REG_PIOE_PPDSR                         (0xFFFFFA98U) /**< \brief (PIOE) Pad Pull-down Status Register */
#define REG_PIOE_OWER                          (0xFFFFFAA0U) /**< \brief (PIOE) Output Write Enable */
#define REG_PIOE_OWDR                          (0xFFFFFAA4U) /**< \brief (PIOE) Output Write Disable */
#define REG_PIOE_OWSR                          (0xFFFFFAA8U) /**< \brief (PIOE) Output Write Status Register */
#define REG_PIOE_AIMER                         (0xFFFFFAB0U) /**< \brief (PIOE) Additional Interrupt Modes Enable Register */
#define REG_PIOE_AIMDR                         (0xFFFFFAB4U) /**< \brief (PIOE) Additional Interrupt Modes Disables Register */
#define REG_PIOE_AIMMR                         (0xFFFFFAB8U) /**< \brief (PIOE) Additional Interrupt Modes Mask Register */
#define REG_PIOE_ESR                           (0xFFFFFAC0U) /**< \brief (PIOE) Edge Select Register */
#define REG_PIOE_LSR                           (0xFFFFFAC4U) /**< \brief (PIOE) Level Select Register */
#define REG_PIOE_ELSR                          (0xFFFFFAC8U) /**< \brief (PIOE) Edge/Level Status Register */
#define REG_PIOE_FELLSR                        (0xFFFFFAD0U) /**< \brief (PIOE) Falling Edge/Low Level Select Register */
#define REG_PIOE_REHLSR                        (0xFFFFFAD4U) /**< \brief (PIOE) Rising Edge/ High Level Select Register */
#define REG_PIOE_FRLHSR                        (0xFFFFFAD8U) /**< \brief (PIOE) Fall/Rise - Low/High Status Register */
#define REG_PIOE_LOCKSR                        (0xFFFFFAE0U) /**< \brief (PIOE) Lock Status */
#define REG_PIOE_WPMR                          (0xFFFFFAE4U) /**< \brief (PIOE) Write Protect Mode Register */
#define REG_PIOE_WPSR                          (0xFFFFFAE8U) /**< \brief (PIOE) Write Protect Status Register */
#define REG_PIOE_SCHMITT                       (0xFFFFFB00U) /**< \brief (PIOE) Schmitt Trigger Register */
#define REG_PIOE_DRIVER1                       (0xFFFFFB18U) /**< \brief (PIOE) I/O Drive Register 1 */
#define REG_PIOE_DRIVER2                       (0xFFFFFB1CU) /**< \brief (PIOE) I/O Drive Register 2 */
#else
#define REG_PIOE_PER                  (*(WoReg*)0xFFFFFA00U) /**< \brief (PIOE) PIO Enable Register */
#define REG_PIOE_PDR                  (*(WoReg*)0xFFFFFA04U) /**< \brief (PIOE) PIO Disable Register */
#define REG_PIOE_PSR                  (*(RoReg*)0xFFFFFA08U) /**< \brief (PIOE) PIO Status Register */
#define REG_PIOE_OER                  (*(WoReg*)0xFFFFFA10U) /**< \brief (PIOE) Output Enable Register */
#define REG_PIOE_ODR                  (*(WoReg*)0xFFFFFA14U) /**< \brief (PIOE) Output Disable Register */
#define REG_PIOE_OSR                  (*(RoReg*)0xFFFFFA18U) /**< \brief (PIOE) Output Status Register */
#define REG_PIOE_IFER                 (*(WoReg*)0xFFFFFA20U) /**< \brief (PIOE) Glitch Input Filter Enable Register */
#define REG_PIOE_IFDR                 (*(WoReg*)0xFFFFFA24U) /**< \brief (PIOE) Glitch Input Filter Disable Register */
#define REG_PIOE_IFSR                 (*(RoReg*)0xFFFFFA28U) /**< \brief (PIOE) Glitch Input Filter Status Register */
#define REG_PIOE_SODR                 (*(WoReg*)0xFFFFFA30U) /**< \brief (PIOE) Set Output Data Register */
#define REG_PIOE_CODR                 (*(WoReg*)0xFFFFFA34U) /**< \brief (PIOE) Clear Output Data Register */
#define REG_PIOE_ODSR                 (*(RwReg*)0xFFFFFA38U) /**< \brief (PIOE) Output Data Status Register */
#define REG_PIOE_PDSR                 (*(RoReg*)0xFFFFFA3CU) /**< \brief (PIOE) Pin Data Status Register */
#define REG_PIOE_IER                  (*(WoReg*)0xFFFFFA40U) /**< \brief (PIOE) Interrupt Enable Register */
#define REG_PIOE_IDR                  (*(WoReg*)0xFFFFFA44U) /**< \brief (PIOE) Interrupt Disable Register */
#define REG_PIOE_IMR                  (*(RoReg*)0xFFFFFA48U) /**< \brief (PIOE) Interrupt Mask Register */
#define REG_PIOE_ISR                  (*(RoReg*)0xFFFFFA4CU) /**< \brief (PIOE) Interrupt Status Register */
#define REG_PIOE_MDER                 (*(WoReg*)0xFFFFFA50U) /**< \brief (PIOE) Multi-driver Enable Register */
#define REG_PIOE_MDDR                 (*(WoReg*)0xFFFFFA54U) /**< \brief (PIOE) Multi-driver Disable Register */
#define REG_PIOE_MDSR                 (*(RoReg*)0xFFFFFA58U) /**< \brief (PIOE) Multi-driver Status Register */
#define REG_PIOE_PUDR                 (*(WoReg*)0xFFFFFA60U) /**< \brief (PIOE) Pull-up Disable Register */
#define REG_PIOE_PUER                 (*(WoReg*)0xFFFFFA64U) /**< \brief (PIOE) Pull-up Enable Register */
#define REG_PIOE_PUSR                 (*(RoReg*)0xFFFFFA68U) /**< \brief (PIOE) Pad Pull-up Status Register */
#define REG_PIOE_ABCDSR               (*(RwReg*)0xFFFFFA70U) /**< \brief (PIOE) Peripheral Select Register */
#define REG_PIOE_IFSCDR               (*(WoReg*)0xFFFFFA80U) /**< \brief (PIOE) Input Filter Slow Clock Disable Register */
#define REG_PIOE_IFSCER               (*(WoReg*)0xFFFFFA84U) /**< \brief (PIOE) Input Filter Slow Clock Enable Register */
#define REG_PIOE_IFSCSR               (*(RoReg*)0xFFFFFA88U) /**< \brief (PIOE) Input Filter Slow Clock Status Register */
#define REG_PIOE_SCDR                 (*(RwReg*)0xFFFFFA8CU) /**< \brief (PIOE) Slow Clock Divider Debouncing Register */
#define REG_PIOE_PPDDR                (*(WoReg*)0xFFFFFA90U) /**< \brief (PIOE) Pad Pull-down Disable Register */
#define REG_PIOE_PPDER                (*(WoReg*)0xFFFFFA94U) /**< \brief (PIOE) Pad Pull-down Enable Register */
#define REG_PIOE_PPDSR                (*(RoReg*)0xFFFFFA98U) /**< \brief (PIOE) Pad Pull-down Status Register */
#define REG_PIOE_OWER                 (*(WoReg*)0xFFFFFAA0U) /**< \brief (PIOE) Output Write Enable */
#define REG_PIOE_OWDR                 (*(WoReg*)0xFFFFFAA4U) /**< \brief (PIOE) Output Write Disable */
#define REG_PIOE_OWSR                 (*(RoReg*)0xFFFFFAA8U) /**< \brief (PIOE) Output Write Status Register */
#define REG_PIOE_AIMER                (*(WoReg*)0xFFFFFAB0U) /**< \brief (PIOE) Additional Interrupt Modes Enable Register */
#define REG_PIOE_AIMDR                (*(WoReg*)0xFFFFFAB4U) /**< \brief (PIOE) Additional Interrupt Modes Disables Register */
#define REG_PIOE_AIMMR                (*(RoReg*)0xFFFFFAB8U) /**< \brief (PIOE) Additional Interrupt Modes Mask Register */
#define REG_PIOE_ESR                  (*(WoReg*)0xFFFFFAC0U) /**< \brief (PIOE) Edge Select Register */
#define REG_PIOE_LSR                  (*(WoReg*)0xFFFFFAC4U) /**< \brief (PIOE) Level Select Register */
#define REG_PIOE_ELSR                 (*(RoReg*)0xFFFFFAC8U) /**< \brief (PIOE) Edge/Level Status Register */
#define REG_PIOE_FELLSR               (*(WoReg*)0xFFFFFAD0U) /**< \brief (PIOE) Falling Edge/Low Level Select Register */
#define REG_PIOE_REHLSR               (*(WoReg*)0xFFFFFAD4U) /**< \brief (PIOE) Rising Edge/ High Level Select Register */
#define REG_PIOE_FRLHSR               (*(RoReg*)0xFFFFFAD8U) /**< \brief (PIOE) Fall/Rise - Low/High Status Register */
#define REG_PIOE_LOCKSR               (*(RoReg*)0xFFFFFAE0U) /**< \brief (PIOE) Lock Status */
#define REG_PIOE_WPMR                 (*(RwReg*)0xFFFFFAE4U) /**< \brief (PIOE) Write Protect Mode Register */
#define REG_PIOE_WPSR                 (*(RoReg*)0xFFFFFAE8U) /**< \brief (PIOE) Write Protect Status Register */
#define REG_PIOE_SCHMITT              (*(RwReg*)0xFFFFFB00U) /**< \brief (PIOE) Schmitt Trigger Register */
#define REG_PIOE_DRIVER1              (*(RwReg*)0xFFFFFB18U) /**< \brief (PIOE) I/O Drive Register 1 */
#define REG_PIOE_DRIVER2              (*(RwReg*)0xFFFFFB1CU) /**< \brief (PIOE) I/O Drive Register 2 */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for PMC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_PMC_SCER                           (0xFFFFFC00U) /**< \brief (PMC) System Clock Enable Register */
#define REG_PMC_SCDR                           (0xFFFFFC04U) /**< \brief (PMC) System Clock Disable Register */
#define REG_PMC_SCSR                           (0xFFFFFC08U) /**< \brief (PMC) System Clock Status Register */
#define REG_PMC_PCER0                          (0xFFFFFC10U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
#define REG_PMC_PCDR0                          (0xFFFFFC14U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */
#define REG_PMC_PCSR0                          (0xFFFFFC18U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
#define REG_CKGR_UCKR                          (0xFFFFFC1CU) /**< \brief (PMC) UTMI Clock Register */
#define REG_CKGR_MOR                           (0xFFFFFC20U) /**< \brief (PMC) Main Oscillator Register */
#define REG_CKGR_MCFR                          (0xFFFFFC24U) /**< \brief (PMC) Main Clock Frequency Register */
#define REG_CKGR_PLLAR                         (0xFFFFFC28U) /**< \brief (PMC) PLLA Register */
#define REG_PMC_MCKR                           (0xFFFFFC30U) /**< \brief (PMC) Master Clock Register */
#define REG_PMC_USB                            (0xFFFFFC38U) /**< \brief (PMC) USB Clock Register */
#define REG_PMC_SMD                            (0xFFFFFC3CU) /**< \brief (PMC) Soft Modem Clock Register */
#define REG_PMC_PCK                            (0xFFFFFC40U) /**< \brief (PMC) Programmable Clock 0 Register */
#define REG_PMC_IER                            (0xFFFFFC60U) /**< \brief (PMC) Interrupt Enable Register */
#define REG_PMC_IDR                            (0xFFFFFC64U) /**< \brief (PMC) Interrupt Disable Register */
#define REG_PMC_SR                             (0xFFFFFC68U) /**< \brief (PMC) Status Register */
#define REG_PMC_IMR                            (0xFFFFFC6CU) /**< \brief (PMC) Interrupt Mask Register */
#define REG_PMC_PLLICPR                        (0xFFFFFC80U) /**< \brief (PMC) PLL Charge Pump Current Register */
#define REG_PMC_WPMR                           (0xFFFFFCE4U) /**< \brief (PMC) Write Protect Mode Register */
#define REG_PMC_WPSR                           (0xFFFFFCE8U) /**< \brief (PMC) Write Protect Status Register */
#define REG_PMC_PCER1                          (0xFFFFFD00U) /**< \brief (PMC) Peripheral Clock Enable Register 1 */
#define REG_PMC_PCDR1                          (0xFFFFFD04U) /**< \brief (PMC) Peripheral Clock Disable Register 1 */
#define REG_PMC_PCSR1                          (0xFFFFFD08U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
#define REG_PMC_PCR                            (0xFFFFFD0CU) /**< \brief (PMC) Peripheral Control Register */
#else
#define REG_PMC_SCER                  (*(WoReg*)0xFFFFFC00U) /**< \brief (PMC) System Clock Enable Register */
#define REG_PMC_SCDR                  (*(WoReg*)0xFFFFFC04U) /**< \brief (PMC) System Clock Disable Register */
#define REG_PMC_SCSR                  (*(RoReg*)0xFFFFFC08U) /**< \brief (PMC) System Clock Status Register */
#define REG_PMC_PCER0                 (*(WoReg*)0xFFFFFC10U) /**< \brief (PMC) Peripheral Clock Enable Register 0 */
#define REG_PMC_PCDR0                 (*(WoReg*)0xFFFFFC14U) /**< \brief (PMC) Peripheral Clock Disable Register 0 */
#define REG_PMC_PCSR0                 (*(RoReg*)0xFFFFFC18U) /**< \brief (PMC) Peripheral Clock Status Register 0 */
#define REG_CKGR_UCKR                 (*(RwReg*)0xFFFFFC1CU) /**< \brief (PMC) UTMI Clock Register */
#define REG_CKGR_MOR                  (*(RwReg*)0xFFFFFC20U) /**< \brief (PMC) Main Oscillator Register */
#define REG_CKGR_MCFR                 (*(RoReg*)0xFFFFFC24U) /**< \brief (PMC) Main Clock Frequency Register */
#define REG_CKGR_PLLAR                (*(RwReg*)0xFFFFFC28U) /**< \brief (PMC) PLLA Register */
#define REG_PMC_MCKR                  (*(RwReg*)0xFFFFFC30U) /**< \brief (PMC) Master Clock Register */
#define REG_PMC_USB                   (*(RwReg*)0xFFFFFC38U) /**< \brief (PMC) USB Clock Register */
#define REG_PMC_SMD                   (*(RwReg*)0xFFFFFC3CU) /**< \brief (PMC) Soft Modem Clock Register */
#define REG_PMC_PCK                   (*(RwReg*)0xFFFFFC40U) /**< \brief (PMC) Programmable Clock 0 Register */
#define REG_PMC_IER                   (*(WoReg*)0xFFFFFC60U) /**< \brief (PMC) Interrupt Enable Register */
#define REG_PMC_IDR                   (*(WoReg*)0xFFFFFC64U) /**< \brief (PMC) Interrupt Disable Register */
#define REG_PMC_SR                    (*(RoReg*)0xFFFFFC68U) /**< \brief (PMC) Status Register */
#define REG_PMC_IMR                   (*(RoReg*)0xFFFFFC6CU) /**< \brief (PMC) Interrupt Mask Register */
#define REG_PMC_PLLICPR               (*(WoReg*)0xFFFFFC80U) /**< \brief (PMC) PLL Charge Pump Current Register */
#define REG_PMC_WPMR                  (*(RwReg*)0xFFFFFCE4U) /**< \brief (PMC) Write Protect Mode Register */
#define REG_PMC_WPSR                  (*(RoReg*)0xFFFFFCE8U) /**< \brief (PMC) Write Protect Status Register */
#define REG_PMC_PCER1                 (*(WoReg*)0xFFFFFD00U) /**< \brief (PMC) Peripheral Clock Enable Register 1 */
#define REG_PMC_PCDR1                 (*(WoReg*)0xFFFFFD04U) /**< \brief (PMC) Peripheral Clock Disable Register 1 */
#define REG_PMC_PCSR1                 (*(RoReg*)0xFFFFFD08U) /**< \brief (PMC) Peripheral Clock Status Register 1 */
#define REG_PMC_PCR                   (*(RwReg*)0xFFFFFD0CU) /**< \brief (PMC) Peripheral Control Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for RSTC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_RSTC_CR                            (0xFFFFFE00U) /**< \brief (RSTC) Control Register */
#define REG_RSTC_SR                            (0xFFFFFE04U) /**< \brief (RSTC) Status Register */
#define REG_RSTC_MR                            (0xFFFFFE08U) /**< \brief (RSTC) Mode Register */
#else
#define REG_RSTC_CR                   (*(WoReg*)0xFFFFFE00U) /**< \brief (RSTC) Control Register */
#define REG_RSTC_SR                   (*(RoReg*)0xFFFFFE04U) /**< \brief (RSTC) Status Register */
#define REG_RSTC_MR                   (*(RwReg*)0xFFFFFE08U) /**< \brief (RSTC) Mode Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for SHDWC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_SHDWC_CR                           (0xFFFFFE10U) /**< \brief (SHDWC) Shutdown Control Register */
#define REG_SHDWC_MR                           (0xFFFFFE14U) /**< \brief (SHDWC) Shutdown Mode Register */
#define REG_SHDWC_SR                           (0xFFFFFE18U) /**< \brief (SHDWC) Shutdown Status Register */
#else
#define REG_SHDWC_CR                  (*(WoReg*)0xFFFFFE10U) /**< \brief (SHDWC) Shutdown Control Register */
#define REG_SHDWC_MR                  (*(RwReg*)0xFFFFFE14U) /**< \brief (SHDWC) Shutdown Mode Register */
#define REG_SHDWC_SR                  (*(RoReg*)0xFFFFFE18U) /**< \brief (SHDWC) Shutdown Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for PIT peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_PIT_MR                             (0xFFFFFE30U) /**< \brief (PIT) Mode Register */
#define REG_PIT_SR                             (0xFFFFFE34U) /**< \brief (PIT) Status Register */
#define REG_PIT_PIVR                           (0xFFFFFE38U) /**< \brief (PIT) Periodic Interval Value Register */
#define REG_PIT_PIIR                           (0xFFFFFE3CU) /**< \brief (PIT) Periodic Interval Image Register */
#else
#define REG_PIT_MR                    (*(RwReg*)0xFFFFFE30U) /**< \brief (PIT) Mode Register */
#define REG_PIT_SR                    (*(RoReg*)0xFFFFFE34U) /**< \brief (PIT) Status Register */
#define REG_PIT_PIVR                  (*(RoReg*)0xFFFFFE38U) /**< \brief (PIT) Periodic Interval Value Register */
#define REG_PIT_PIIR                  (*(RoReg*)0xFFFFFE3CU) /**< \brief (PIT) Periodic Interval Image Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for WDT peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_WDT_CR                             (0xFFFFFE40U) /**< \brief (WDT) Control Register */
#define REG_WDT_MR                             (0xFFFFFE44U) /**< \brief (WDT) Mode Register */
#define REG_WDT_SR                             (0xFFFFFE48U) /**< \brief (WDT) Status Register */
#else
#define REG_WDT_CR                    (*(WoReg*)0xFFFFFE40U) /**< \brief (WDT) Control Register */
#define REG_WDT_MR                    (*(RwReg*)0xFFFFFE44U) /**< \brief (WDT) Mode Register */
#define REG_WDT_SR                    (*(RoReg*)0xFFFFFE48U) /**< \brief (WDT) Status Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for SCKC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_SCKC_CR                            (0xFFFFFE50U) /**< \brief (SCKC) Slow Clock Configuration Register */
#else
#define REG_SCKC_CR                   (*(RwReg*)0xFFFFFE50U) /**< \brief (SCKC) Slow Clock Configuration Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for BSC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_BSC_CR                             (0xFFFFFE54U) /**< \brief (BSC) Boot Sequence Configuration Register */
#else
#define REG_BSC_CR                    (*(RwReg*)0xFFFFFE54U) /**< \brief (BSC) Boot Sequence Configuration Register */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for GPBR peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_GPBR_GPBR0                         (0xFFFFFE60U) /**< \brief (GPBR) General Purpose Backup Register 0 */
#define REG_GPBR_GPBR1                         (0xFFFFFE64U) /**< \brief (GPBR) General Purpose Backup Register 1 */
#define REG_GPBR_GPBR2                         (0xFFFFFE68U) /**< \brief (GPBR) General Purpose Backup Register 2 */
#define REG_GPBR_GPBR3                         (0xFFFFFE6CU) /**< \brief (GPBR) General Purpose Backup Register 3 */
#else
#define REG_GPBR_GPBR0                (*(RwReg*)0xFFFFFE60U) /**< \brief (GPBR) General Purpose Backup Register 0 */
#define REG_GPBR_GPBR1                (*(RwReg*)0xFFFFFE64U) /**< \brief (GPBR) General Purpose Backup Register 1 */
#define REG_GPBR_GPBR2                (*(RwReg*)0xFFFFFE68U) /**< \brief (GPBR) General Purpose Backup Register 2 */
#define REG_GPBR_GPBR3                (*(RwReg*)0xFFFFFE6CU) /**< \brief (GPBR) General Purpose Backup Register 3 */
#endif /* __ASSEMBLY__ */
/* ========== Register definition for RTC peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_RTC_CR                             (0xFFFFFEB0U) /**< \brief (RTC) Control Register */
#define REG_RTC_MR                             (0xFFFFFEB4U) /**< \brief (RTC) Mode Register */
#define REG_RTC_TIMR                           (0xFFFFFEB8U) /**< \brief (RTC) Time Register */
#define REG_RTC_CALR                           (0xFFFFFEBCU) /**< \brief (RTC) Calendar Register */
#define REG_RTC_TIMALR                         (0xFFFFFEC0U) /**< \brief (RTC) Time Alarm Register */
#define REG_RTC_CALALR                         (0xFFFFFEC4U) /**< \brief (RTC) Calendar Alarm Register */
#define REG_RTC_SR                             (0xFFFFFEC8U) /**< \brief (RTC) Status Register */
#define REG_RTC_SCCR                           (0xFFFFFECCU) /**< \brief (RTC) Status Clear Command Register */
#define REG_RTC_IER                            (0xFFFFFED0U) /**< \brief (RTC) Interrupt Enable Register */
#define REG_RTC_IDR                            (0xFFFFFED4U) /**< \brief (RTC) Interrupt Disable Register */
#define REG_RTC_IMR                            (0xFFFFFED8U) /**< \brief (RTC) Interrupt Mask Register */
#define REG_RTC_VER                            (0xFFFFFEDCU) /**< \brief (RTC) Valid Entry Register */
#else
#define REG_RTC_CR                    (*(RwReg*)0xFFFFFEB0U) /**< \brief (RTC) Control Register */
#define REG_RTC_MR                    (*(RwReg*)0xFFFFFEB4U) /**< \brief (RTC) Mode Register */
#define REG_RTC_TIMR                  (*(RwReg*)0xFFFFFEB8U) /**< \brief (RTC) Time Register */
#define REG_RTC_CALR                  (*(RwReg*)0xFFFFFEBCU) /**< \brief (RTC) Calendar Register */
#define REG_RTC_TIMALR                (*(RwReg*)0xFFFFFEC0U) /**< \brief (RTC) Time Alarm Register */
#define REG_RTC_CALALR                (*(RwReg*)0xFFFFFEC4U) /**< \brief (RTC) Calendar Alarm Register */
#define REG_RTC_SR                    (*(RoReg*)0xFFFFFEC8U) /**< \brief (RTC) Status Register */
#define REG_RTC_SCCR                  (*(WoReg*)0xFFFFFECCU) /**< \brief (RTC) Status Clear Command Register */
#define REG_RTC_IER                   (*(WoReg*)0xFFFFFED0U) /**< \brief (RTC) Interrupt Enable Register */
#define REG_RTC_IDR                   (*(WoReg*)0xFFFFFED4U) /**< \brief (RTC) Interrupt Disable Register */
#define REG_RTC_IMR                   (*(RoReg*)0xFFFFFED8U) /**< \brief (RTC) Interrupt Mask Register */
#define REG_RTC_VER                   (*(RoReg*)0xFFFFFEDCU) /**< \brief (RTC) Valid Entry Register */
#endif /* __ASSEMBLY__ */


/* ========== Register definition for RTT peripheral ========== */
#ifdef __ASSEMBLY__
#define REG_RTT_MR                             (0xFFFFFE20U) /**< \brief (RTT) Mode Register */
#define REG_RTT_AR                             (0xFFFFFE24U) /**< \brief (RTT) Alarm Register */
#define REG_RTT_VR                             (0xFFFFFE28U) /**< \brief (RTT) Value Register */
#define REG_RTT_SR                             (0xFFFFFE2CU) /**< \brief (RTT) Status Register */
#else
#define REG_RTT_MR                             (RwReg, 0xFFFFFE20U) /**< \brief (RTT) Mode Register */
#define REG_RTT_AR                             (RwReg, 0xFFFFFE24U) /**< \brief (RTT) Alarm Register */
#define REG_RTT_VR                             (RoReg, 0xFFFFFE28U) /**< \brief (RTT) Value Register */
#define REG_RTT_SR                             (RoReg, 0xFFFFFE2CU) /**< \brief (RTT) Status Register */
#endif /* __ASSEMBLY__ */

/*@}*/

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR AT91SAMA5 */
/* ************************************************************************** */
/** \addtogroup AT91SAMA5_id Peripheral Ids Definitions */
/*@{*/

#define ID_FIQ    ( 0) /**< \brief Advanced Interrupt Controller (FIQ) */
#define ID_SYS    ( 1) /**< \brief System Controller Interrupt (SYS) */
#define ID_DBGU   ( 2) /**< \brief Debug Unit Interrupt (DBGU) */
#define ID_PIT    ( 3) /**< \brief Periodic Interval Timer Interrupt (PIT) */
#define ID_WDT    ( 4) /**< \brief Watchdog timer Interrupt (WDT) */
#define ID_SMC    ( 5) /**< \brief Multi-bit ECC Interrupt (SMC) */
#define ID_PIOA   ( 6) /**< \brief Parallel I/O Controller A (PIOA) */
#define ID_PIOB   ( 7) /**< \brief Parallel I/O Controller B (PIOB) */
#define ID_PIOC   ( 8) /**< \brief Parallel I/O Controller C (PIOC) */
#define ID_PIOD   ( 9) /**< \brief Parallel I/O Controller D (PIOD) */
#define ID_PIOE   (10) /**< \brief Parallel I/O Controller E (PIOE) */
#define ID_SMD    (11) /**< \brief SMD Soft Modem (SMD) */
#define ID_USART0 (12) /**< \brief USART 0 (USART0) */
#define ID_USART1 (13) /**< \brief USART 1 (USART1) */
#define ID_USART2 (14) /**< \brief USART 2 (USART2) */
#define ID_USART3 (15) /**< \brief USART 3 (USART3) */
#define ID_UART0  (16) /**< \brief UART 0 (UART0) */
#define ID_UART1  (17) /**< \brief UART 1 (UART1) */
#define ID_TWI0   (18) /**< \brief Two-Wire Interface 0 (TWI0) */
#define ID_TWI1   (19) /**< \brief Two-Wire Interface 1 (TWI1) */
#define ID_TWI2   (20) /**< \brief Two-Wire Interface 2 (TWI2) */
#define ID_HSMCI0 (21) /**< \brief High Speed Multimedia Card Interface 0 (HSMCI0) */
#define ID_HSMCI1 (22) /**< \brief High Speed Multimedia Card Interface 1 (HSMCI1) */
#define ID_HSMCI2 (23) /**< \brief High Speed Multimedia Card Interface 2 (HSMCI2) */
#define ID_SPI0   (24) /**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SPI1   (25) /**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_TC0    (26) /**< \brief Timer Counter 0 (ch. 0, 1, 2) (TC0) */
#define ID_TC1    (27) /**< \brief Timer Counter 1 (ch. 3, 4, 5) (TC1) */
#define ID_PWM    (28) /**< \brief Pulse Width Modulation Controller (PWM) */
#define ID_ADC    (29) /**< \brief Touch Screen ADC Controller (ADC) */
#define ID_DMAC0  (30) /**< \brief DMA Controller 0 (DMAC0) */
#define ID_DMAC1  (31) /**< \brief DMA Controller 1 (DMAC1) */
#define ID_UHPHS  (32) /**< \brief USB Host High Speed (UHPHS) */
#define ID_UDPHS  (33) /**< \brief USB Device High Speed (UDPHS) */
#define ID_GMAC   (34) /**< \brief Gigabit Ethernet MAC (GMAC) */
#define ID_EMAC   (35) /**< \brief Ethernet MAC (EMAC) */
#define ID_LCDC   (36) /**< \brief LCD Controller (LCDC) */
#define ID_ISI    (37) /**< \brief Image Sensor Interface (ISI) */
#define ID_SSC0   (38) /**< \brief Synchronous Serial Controller 0 (SSC0) */
#define ID_SSC1   (39) /**< \brief Synchronous Serial Controller 1 (SSC1) */
#define ID_CAN0   (40) /**< \brief CAN controller 0 (CAN0) */
#define ID_CAN1   (41) /**< \brief CAN controller 1 (CAN1) */
#define ID_SHA    (42) /**< \brief Secure Hash Algorithm (SHA) */
#define ID_AES    (43) /**< \brief Advanced Encryption Standard (AES) */
#define ID_TDES   (44) /**< \brief Triple Data EncryptionStandard (TDES) */
#define ID_TRNG   (45) /**< \brief True Random Number Generator (TRNG) */
#define ID_ARM    (46) /**< \brief Performance Monitor Unit (ARM) */
#define ID_IRQ    (47) /**< \brief Advanced Interrupt Controller (IRQ) */
#define ID_FUSE   (48) /**< \brief Fuse Controller (FUSE) */
#define ID_MPDDRC (49) /**< \brief MPDDR controller (MPDDRC) */
/*@}*/

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR AT91SAMA5 */
/* ************************************************************************** */
/** \addtogroup AT91SAMA5_base Peripheral Base Address Definitions */
/*@{*/

#ifdef __ASSEMBLY__
#define SMD    (0x00400000U) /**< \brief (SMD   ) Base Address */
#define AXIMX  (0x00800000U) /**< \brief (AXIMX ) Base Address */
#define HSMCI0 (0xF0000000U) /**< \brief (HSMCI0) Base Address */
#define SPI0   (0xF0004000U) /**< \brief (SPI0  ) Base Address */
#define SSC0   (0xF0008000U) /**< \brief (SSC0  ) Base Address */
#define CAN0   (0xF000C000U) /**< \brief (CAN0  ) Base Address */
#define TC0    (0xF0010000U) /**< \brief (TC0   ) Base Address */
#define TWI0   (0xF0014000U) /**< \brief (TWI0  ) Base Address */
#define TWI1   (0xF0018000U) /**< \brief (TWI1  ) Base Address */
#define USART0 (0xF001C000U) /**< \brief (USART0) Base Address */
#define USART1 (0xF0020000U) /**< \brief (USART1) Base Address */
#define UART0  (0xF0024000U) /**< \brief (UART0 ) Base Address */
#define GMAC   (0xF0028000U) /**< \brief (GMAC  ) Base Address */
#define PWM    (0xF002C000U) /**< \brief (PWM   ) Base Address */
#define LCDC   (0xF0030000U) /**< \brief (LCDC  ) Base Address */
#define ISI    (0xF0034000U) /**< \brief (ISI   ) Base Address */
#define SFR    (0xF0038000U) /**< \brief (SFR   ) Base Address */
#define HSMCI1 (0xF8000000U) /**< \brief (HSMCI1) Base Address */
#define HSMCI2 (0xF8004000U) /**< \brief (HSMCI2) Base Address */
#define SPI1   (0xF8008000U) /**< \brief (SPI1  ) Base Address */
#define SSC1   (0xF800C000U) /**< \brief (SSC1  ) Base Address */
#define CAN1   (0xF8010000U) /**< \brief (CAN1  ) Base Address */
#define TC1    (0xF8014000U) /**< \brief (TC1   ) Base Address */
#define ADC    (0xF8018000U) /**< \brief (ADC   ) Base Address */
#define TWI2   (0xF801C000U) /**< \brief (TWI2  ) Base Address */
#define USART2 (0xF8020000U) /**< \brief (USART2) Base Address */
#define USART3 (0xF8024000U) /**< \brief (USART3) Base Address */
#define UART1  (0xF8028000U) /**< \brief (UART1 ) Base Address */
#define EMAC   (0xF802C000U) /**< \brief (EMAC  ) Base Address */
#define UDPHS  (0xF8030000U) /**< \brief (UDPHS ) Base Address */
#define SHA    (0xF8034000U) /**< \brief (SHA   ) Base Address */
#define AES    (0xF8038000U) /**< \brief (AES   ) Base Address */
#define TDES   (0xF803C000U) /**< \brief (TDES  ) Base Address */
#define TRNG   (0xF8040000U) /**< \brief (TRNG  ) Base Address */
#define SMC    (0xFFFFC000U) /**< \brief (SMC   ) Base Address */
#define FUSE   (0xFFFFE400U) /**< \brief (FUSE  ) Base Address */
#define DMAC0  (0xFFFFE600U) /**< \brief (DMAC0 ) Base Address */
#define DMAC1  (0xFFFFE800U) /**< \brief (DMAC1 ) Base Address */
#define MPDDRC (0xFFFFEA00U) /**< \brief (MPDDRC) Base Address */
#define MATRIX (0xFFFFEC00U) /**< \brief (MATRIX) Base Address */
#define DBGU   (0xFFFFEE00U) /**< \brief (DBGU  ) Base Address */
#define AIC    (0xFFFFF000U) /**< \brief (AIC   ) Base Address */
#define PIOA   (0xFFFFF200U) /**< \brief (PIOA  ) Base Address */
#define PIOB   (0xFFFFF400U) /**< \brief (PIOB  ) Base Address */
#define PIOC   (0xFFFFF600U) /**< \brief (PIOC  ) Base Address */
#define PIOD   (0xFFFFF800U) /**< \brief (PIOD  ) Base Address */
#define PIOE   (0xFFFFFA00U) /**< \brief (PIOE  ) Base Address */
#define PMC    (0xFFFFFC00U) /**< \brief (PMC   ) Base Address */
#define RSTC   (0xFFFFFE00U) /**< \brief (RSTC  ) Base Address */
#define SHDWC  (0xFFFFFE10U) /**< \brief (SHDWC ) Base Address */
//kzhang add RTT definition
#define RTT    (0xFFFFFE20U) /**< \brief (RTT   ) Base Address */
#define PIT    (0xFFFFFE30U) /**< \brief (PIT   ) Base Address */
#define WDT    (0xFFFFFE40U) /**< \brief (WDT   ) Base Address */
#define SCKC   (0xFFFFFE50U) /**< \brief (SCKC  ) Base Address */
#define BSC    (0xFFFFFE54U) /**< \brief (BSC   ) Base Address */
#define GPBR   (0xFFFFFE60U) /**< \brief (GPBR  ) Base Address */
#define RTC    (0xFFFFFEB0U) /**< \brief (RTC   ) Base Address */
#else
#define SMD    ((Smd    *)0x00400000U) /**< \brief (SMD   ) Base Address */
#define AXIMX  ((Aximx  *)0x00800000U) /**< \brief (AXIMX ) Base Address */
#define HSMCI0 ((Hsmci  *)0xF0000000U) /**< \brief (HSMCI0) Base Address */
#define SPI0   ((Spi    *)0xF0004000U) /**< \brief (SPI0  ) Base Address */
#define SSC0   ((Ssc    *)0xF0008000U) /**< \brief (SSC0  ) Base Address */
#define CAN0   ((Can    *)0xF000C000U) /**< \brief (CAN0  ) Base Address */
#define TC0    ((Tc     *)0xF0010000U) /**< \brief (TC0   ) Base Address */
#define TWI0   ((Twi    *)0xF0014000U) /**< \brief (TWI0  ) Base Address */
#define TWI1   ((Twi    *)0xF0018000U) /**< \brief (TWI1  ) Base Address */
#define USART0 ((Usart  *)0xF001C000U) /**< \brief (USART0) Base Address */
#define USART1 ((Usart  *)0xF0020000U) /**< \brief (USART1) Base Address */
#define UART0  ((Uart   *)0xF0024000U) /**< \brief (UART0 ) Base Address */
#define GMAC   ((Gmac   *)0xF0028000U) /**< \brief (GMAC  ) Base Address */
#define PWM    ((Pwm    *)0xF002C000U) /**< \brief (PWM   ) Base Address */
#define LCDC   ((Lcdc   *)0xF0030000U) /**< \brief (LCDC  ) Base Address */
#define ISI    ((Isi    *)0xF0034000U) /**< \brief (ISI   ) Base Address */
#define SFR    ((Sfr    *)0xF0038000U) /**< \brief (SFR   ) Base Address */
#define HSMCI1 ((Hsmci  *)0xF8000000U) /**< \brief (HSMCI1) Base Address */
#define HSMCI2 ((Hsmci  *)0xF8004000U) /**< \brief (HSMCI2) Base Address */
#define SPI1   ((Spi    *)0xF8008000U) /**< \brief (SPI1  ) Base Address */
#define SSC1   ((Ssc    *)0xF800C000U) /**< \brief (SSC1  ) Base Address */
#define CAN1   ((Can    *)0xF8010000U) /**< \brief (CAN1  ) Base Address */
#define TC1    ((Tc     *)0xF8014000U) /**< \brief (TC1   ) Base Address */
#define ADC    ((Adc    *)0xF8018000U) /**< \brief (ADC   ) Base Address */
#define TWI2   ((Twi    *)0xF801C000U) /**< \brief (TWI2  ) Base Address */
#define USART2 ((Usart  *)0xF8020000U) /**< \brief (USART2) Base Address */
#define USART3 ((Usart  *)0xF8024000U) /**< \brief (USART3) Base Address */
#define UART1  ((Uart   *)0xF8028000U) /**< \brief (UART1 ) Base Address */
#define EMAC   ((Emac   *)0xF802C000U) /**< \brief (EMAC  ) Base Address */
#define UDPHS  ((Udphs  *)0xF8030000U) /**< \brief (UDPHS ) Base Address */
#define SHA    ((Sha    *)0xF8034000U) /**< \brief (SHA   ) Base Address */
#define AES    ((Aes    *)0xF8038000U) /**< \brief (AES   ) Base Address */
#define TDES   ((Tdes   *)0xF803C000U) /**< \brief (TDES  ) Base Address */
#define TRNG   ((Trng   *)0xF8040000U) /**< \brief (TRNG  ) Base Address */
#define SMC    ((Smc    *)0xFFFFC000U) /**< \brief (SMC   ) Base Address */
#define FUSE   ((Fuse   *)0xFFFFE400U) /**< \brief (FUSE  ) Base Address */
#define DMAC0  ((Dmac   *)0xFFFFE600U) /**< \brief (DMAC0 ) Base Address */
#define DMAC1  ((Dmac   *)0xFFFFE800U) /**< \brief (DMAC1 ) Base Address */
#define MPDDRC ((Mpddrc *)0xFFFFEA00U) /**< \brief (MPDDRC) Base Address */
#define MATRIX ((Matrix *)0xFFFFEC00U) /**< \brief (MATRIX) Base Address */
#define DBGU   ((Dbgu   *)0xFFFFEE00U) /**< \brief (DBGU  ) Base Address */
#define AIC    ((Aic    *)0xFFFFF000U) /**< \brief (AIC   ) Base Address */
#define PIOA   ((Pio    *)0xFFFFF200U) /**< \brief (PIOA  ) Base Address */
#define PIOB   ((Pio    *)0xFFFFF400U) /**< \brief (PIOB  ) Base Address */
#define PIOC   ((Pio    *)0xFFFFF600U) /**< \brief (PIOC  ) Base Address */
#define PIOD   ((Pio    *)0xFFFFF800U) /**< \brief (PIOD  ) Base Address */
#define PIOE   ((Pio    *)0xFFFFFA00U) /**< \brief (PIOE  ) Base Address */
#define PMC    ((Pmc    *)0xFFFFFC00U) /**< \brief (PMC   ) Base Address */
#define RSTC   ((Rstc   *)0xFFFFFE00U) /**< \brief (RSTC  ) Base Address */
#define SHDWC  ((Shdwc  *)0xFFFFFE10U) /**< \brief (SHDWC ) Base Address */
//kzhang add RTT definition
#define RTT    ((Rtt    *)0xFFFFFE20U) /**< \brief (rtt   ) Base Address */
#define PIT    ((Pit    *)0xFFFFFE30U) /**< \brief (PIT   ) Base Address */
#define WDT    ((Wdt    *)0xFFFFFE40U) /**< \brief (WDT   ) Base Address */
#define SCKC   ((Sckc   *)0xFFFFFE50U) /**< \brief (SCKC  ) Base Address */
#define BSC    ((Bsc    *)0xFFFFFE54U) /**< \brief (BSC   ) Base Address */
#define GPBR   ((Gpbr   *)0xFFFFFE60U) /**< \brief (GPBR  ) Base Address */
#define RTC    ((Rtc    *)0xFFFFFEB0U) /**< \brief (RTC   ) Base Address */
#endif /* __ASSEMBLY__ */
/*@}*/

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR AT91SAMA5 */
/* ************************************************************************** */
/** \addtogroup AT91SAMA5_pio Peripheral Pio Definitions */
/*@{*/

/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR AT91SAMA5 */
/* ************************************************************************** */

#define IRAM0_SIZE (0x10000u)
#define IRAM1_SIZE (0x10000u)
#define IROM_SIZE  (0x20000u)
#define IRAM_SIZE  (0x20000u)

#define EBI_CS0_ADDR   (0x10000000u) /**< EBI Chip Select 0 base address */
#define DDR_CS_ADDR    (0x20000000u) /**< DDR Chip Select base address */
#define EBI_CS1_ADDR   (0x40000000u) /**< EBI Chip Select 1 base address */
#define EBI_CS2_ADDR   (0x50000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR   (0x60000000u) /**< EBI Chip Select 3 base address */
#define EBI_NF_ADDR    (0x60000000u) /**< NAND Flash on EBI Chip Select 3 base address */
#define IROM_ADDR      (0x00100000u) /**< Internal ROM base address */
#define IRAM0_ADDR     (0x00300000u) /**< Internal RAM 0 base address */
#if defined IRAM0_SIZE
#define IRAM1_ADDR     (IRAM0_ADDR+IRAM0_SIZE) /**< Internal RAM 1 base address */
#endif
#define SMD_ADDR       (0x00400000u) /**< Software Modem Device base address */
#define UDPHS_RAM_ADDR (0x00500000u) /**< USB High Speed Device Port RAM base address */
#define UHP_OHCI_ADDR  (0x00600000u) /**< USB Host Port OHCI base address */
#define UHP_EHCI_ADDR  (0x00700000u) /**< USB Host Port EHCI base address */
#define AXIMX_ADDR     (0x00800000u) /**< AXI Bus Matrix base address */
#define DAP_ADDR       (0x00900000u) /**< Debug Access Port base address */

/* ************************************************************************** */
/*   ELECTRICAL DEFINITIONS FOR AT91SAMA5 */
/* ************************************************************************** */

/* %ATMEL_ELECTRICAL% */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _AT91SAMA5_ */
