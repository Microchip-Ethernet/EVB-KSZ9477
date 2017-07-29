/**
 * \file
 *
 * \brief ASF Patch Header file definitions for SAM4L.
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 
 * 4. This software may only be redistributed and used in connection with an 
 *    Atmel microcontroller product.
 * 
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#ifndef SAM4L4_PATCH_ASF_H_INCLUDED
#define SAM4L4_PATCH_ASF_H_INCLUDED

// These defines are used for sam/drivers/flashcalw implementation.
#define   FLASHCALW_FCMD_CMD_HSEN    (0x10u <<  0)
#define   FLASHCALW_FCMD_CMD_HSDIS   (0x11u <<  0)

// These defines are used to keep compatibility with existing 
// sam/drivers/usart implementation from SAM3/4 products with SAM4L product.
#define US_MR                               MR
#define US_WPMR                             WPMR
#define US_BRGR                             BRGR
#define US_RTOR                             RTOR
#define US_TTOR                             TTOR
#define US_TTGR                             TTGR
#define US_FIDI                             FIDI
#define US_CR                               CR
#define US_CSR                              CSR
#define US_IER                              IER
#define US_IDR                              IDR
#define US_IMR                              IMR
#define US_RHR                              RHR
#define US_THR                              THR
#define US_WPSR                             WPSR
#define US_WPSR_WPVS                        US_WPSR_WPV
#define US_MR_PAR_MULTIDROP                 US_USART_MR_PAR_MULTI
#define US_NER                              NER
#define US_IF                               IFR
#define US_MR_USART_MODE_NORMAL             US_USART_MR_MODE_NORMAL
#define US_MR_USART_MODE_Msk                US_USART_MR_MODE_Msk
#define US_MR_USART_MODE_HW_HANDSHAKING     US_USART_MR_MODE_HARDWARE
#define US_MR_USART_MODE_RS485              US_USART_MR_MODE_RS485
#define US_MR_USART_MODE_IRDA               US_USART_MR_MODE_IRDA
#define US_MR_USART_MODE_IS07816_T_0        US_USART_MR_MODE_ISO7816_T0
#define US_MR_USART_MODE_IS07816_T_1        US_USART_MR_MODE_ISO7816_T1
#define US_MR_NBSTOP_2_BIT                  US_USART_MR_NBSTOP_2
#define US_MR_NBSTOP_1_BIT                  US_USART_MR_NBSTOP_1
#define US_MR_USART_MODE_SPI_MASTER         US_USART_MR_MODE_SPI_MASTER 
#define US_MR_USART_MODE_SPI_SLAVE          US_USART_MR_MODE_SPI_SLAVE
#define US_MR_CHRL_8_BIT                    US_USART_MR_CHRL_8
#define US_MR_PAR_NO                        US_USART_MR_PAR_NONE
#define US_MR_CHMODE_NORMAL                 US_USART_MR_CHMODE_NORMAL
#define US_MR_OVER                          US_USART_MR_OVER
#define US_MR_USCLKS_Msk                    US_USART_MR_USCLKS_Msk
#define US_MR_USCLKS_MCK                    US_USART_MR_USCLKS_MCK
#define US_MR_SYNC                          US_USART_MR_SYNC
#define US_MR_CLKO                          US_USART_MR_CLKO
#define US_MR_USCLKS_SCK                    US_USART_MR_USCLKS_SCK
#define US_MR_PAR_EVEN                      US_USART_MR_PAR_EVEN
#define US_MR_PAR_ODD                       US_USART_MR_PAR_ODD
#define US_MR_MAX_ITERATION_Pos             US_USART_MR_MAX_ITERATION_Pos
#define US_MR_MSBF                          US_USART_MR_MSBF
#define US_MR_INACK                         US_USART_MR_INACK
#define US_MR_DSNACK                        US_USART_MR_DSNACK
#define US_MR_CPHA                          US_SPI_MR_CPHA
#define US_MR_CPOL                          US_SPI_MR_CPOL
#define US_CR_TXEN                          US_USART_CR_TXEN
#define US_CR_TXDIS                         US_USART_CR_TXDIS
#define US_CR_RSTTX                         US_USART_CR_RSTTX
#define US_CR_RXEN                          US_USART_CR_RXEN
#define US_CR_RXDIS                         US_USART_CR_RXDIS
#define US_CR_RSTRX                         US_USART_CR_RSTRX
#define US_CR_RSTSTA                        US_USART_CR_RSTSTA
#define US_CR_STTBRK                        US_USART_CR_STTBRK
#define US_CR_STPBRK                        US_USART_CR_STPBRK
#define US_CR_STTTO                         US_USART_CR_STTTO
#define US_CR_SENDA                         US_USART_CR_SENDA
#define US_CR_RSTIT                         US_USART_CR_RSTIT
#define US_CR_RSTNACK                       US_USART_CR_RSTNACK
#define US_CR_RETTO                         US_USART_CR_RETTO
#define US_CR_RTSEN                         US_USART_CR_RTSEN
#define US_CR_RTSDIS                        US_USART_CR_RTSDIS
#define US_CR_FCS                           US_SPI_MASTER_CR_FCS
#define US_CR_RCS                           US_SPI_MASTER_CR_RCS
#define US_CSR_TXRDY                        US_USART_CSR_TXRDY
#define US_CSR_TXEMPTY                      US_USART_CSR_TXEMPTY
#define US_CSR_RXRDY                        US_USART_CSR_RXRDY
#define US_CSR_ENDRX                        US_USART_CSR_ENDRX
#define US_CSR_ENDTX                        US_USART_CSR_ENDTX
#define US_CSR_RXBUFF                       US_USART_CSR_RXBUFF
#define US_CSR_TXBUFE                       US_USART_CSR_TXBUFE
#define US_CSR_TXRDY                        US_USART_CSR_TXRDY
#define US_CSR_RXRDY                        US_USART_CSR_RXRDY

#if (!defined SCIF_RCOSC_FREQUENCY)
#    define SCIF_RCOSC_FREQUENCY            115200
#endif

// These defines for homogeneity with other SAM header files.
#define CHIP_FREQ_FWS_0                     (18000000UL) /**< \brief Maximum operating frequency when FWS is 0 */
#define CHIP_FREQ_FWS_1                     (36000000UL) /**< \brief Maximum operating frequency when FWS is 1 */
// WARNING NOTE: these are preliminary values.
#define CHIP_FREQ_FLASH_HSEN_FWS_0          (18000000UL) /**< \brief Maximum operating frequency when FWS is 0 and the FLASH HS mode is enabled */
#define CHIP_FREQ_FLASH_HSEN_FWS_1          (36000000UL) /**< \brief Maximum operating frequency when FWS is 1 and the FLASH HS mode is enabled */

// Size of HRAMC1 with 32-bit access
#undef HRAMC1_SIZE
#define HRAMC1_SIZE                         (0x800UL)

// USBC related offsets
#define USBC_UHINT_P0INT_Pos                                   8
#define USBC_UHINTE_P0INTE_Pos                                 8
#define USBC_UPCFG0_PBK_Pos                                    2
#define USBC_UPCFG0_PBK_Msk                     (0x1u << USBC_UPCFG0_PBK_Pos)

#endif  // SAM4L4_PATCH_ASF_H_INCLUDED
