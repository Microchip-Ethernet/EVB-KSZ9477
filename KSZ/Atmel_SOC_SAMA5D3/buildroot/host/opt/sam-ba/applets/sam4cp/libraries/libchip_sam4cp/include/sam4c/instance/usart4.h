/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#ifndef _SAM4C_USART4_INSTANCE_
#define _SAM4C_USART4_INSTANCE_

/* ========== Register definition for USART4 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_USART4_CR          (0x40034000U) /**< \brief (USART4) Control Register */
#define REG_USART4_MR          (0x40034004U) /**< \brief (USART4) Mode Register */
#define REG_USART4_IER          (0x40034008U) /**< \brief (USART4) Interrupt Enable Register */
#define REG_USART4_IDR          (0x4003400CU) /**< \brief (USART4) Interrupt Disable Register */
#define REG_USART4_IMR          (0x40034010U) /**< \brief (USART4) Interrupt Mask Register */
#define REG_USART4_CSR          (0x40034014U) /**< \brief (USART4) Channel Status Register */
#define REG_USART4_RHR          (0x40034018U) /**< \brief (USART4) Receiver Holding Register */
#define REG_USART4_THR          (0x4003401CU) /**< \brief (USART4) Transmitter Holding Register */
#define REG_USART4_BRGR          (0x40034020U) /**< \brief (USART4) Baud Rate Generator Register */
#define REG_USART4_RTOR          (0x40034024U) /**< \brief (USART4) Receiver Time-out Register */
#define REG_USART4_TTGR          (0x40034028U) /**< \brief (USART4) Transmitter Timeguard Register */
#define REG_USART4_FIDI          (0x40034040U) /**< \brief (USART4) FI DI Ratio Register */
#define REG_USART4_NER          (0x40034044U) /**< \brief (USART4) Number of Errors Register */
#define REG_USART4_IF          (0x4003404CU) /**< \brief (USART4) IrDA Filter Register */
#define REG_USART4_MAN          (0x40034050U) /**< \brief (USART4) Manchester Encoder Decoder Register */
#define REG_USART4_RPR          (0x40034100U) /**< \brief (USART4) Receive Pointer Register */
#define REG_USART4_RCR          (0x40034104U) /**< \brief (USART4) Receive Counter Register */
#define REG_USART4_TPR          (0x40034108U) /**< \brief (USART4) Transmit Pointer Register */
#define REG_USART4_TCR          (0x4003410CU) /**< \brief (USART4) Transmit Counter Register */
#define REG_USART4_RNPR          (0x40034110U) /**< \brief (USART4) Receive Next Pointer Register */
#define REG_USART4_RNCR          (0x40034114U) /**< \brief (USART4) Receive Next Counter Register */
#define REG_USART4_TNPR          (0x40034118U) /**< \brief (USART4) Transmit Next Pointer Register */
#define REG_USART4_TNCR          (0x4003411CU) /**< \brief (USART4) Transmit Next Counter Register */
#define REG_USART4_PTCR          (0x40034120U) /**< \brief (USART4) Transfer Control Register */
#define REG_USART4_PTSR          (0x40034124U) /**< \brief (USART4) Transfer Status Register */
#else
#define REG_USART4_CR (*(WoReg*)0x40034000U) /**< \brief (USART4) Control Register */
#define REG_USART4_MR (*(RwReg*)0x40034004U) /**< \brief (USART4) Mode Register */
#define REG_USART4_IER (*(WoReg*)0x40034008U) /**< \brief (USART4) Interrupt Enable Register */
#define REG_USART4_IDR (*(WoReg*)0x4003400CU) /**< \brief (USART4) Interrupt Disable Register */
#define REG_USART4_IMR (*(RoReg*)0x40034010U) /**< \brief (USART4) Interrupt Mask Register */
#define REG_USART4_CSR (*(RoReg*)0x40034014U) /**< \brief (USART4) Channel Status Register */
#define REG_USART4_RHR (*(RoReg*)0x40034018U) /**< \brief (USART4) Receiver Holding Register */
#define REG_USART4_THR (*(WoReg*)0x4003401CU) /**< \brief (USART4) Transmitter Holding Register */
#define REG_USART4_BRGR (*(RwReg*)0x40034020U) /**< \brief (USART4) Baud Rate Generator Register */
#define REG_USART4_RTOR (*(RwReg*)0x40034024U) /**< \brief (USART4) Receiver Time-out Register */
#define REG_USART4_TTGR (*(RwReg*)0x40034028U) /**< \brief (USART4) Transmitter Timeguard Register */
#define REG_USART4_FIDI (*(RwReg*)0x40034040U) /**< \brief (USART4) FI DI Ratio Register */
#define REG_USART4_NER (*(RoReg*)0x40034044U) /**< \brief (USART4) Number of Errors Register */
#define REG_USART4_IF (*(RwReg*)0x4003404CU) /**< \brief (USART4) IrDA Filter Register */
#define REG_USART4_MAN (*(RwReg*)0x40034050U) /**< \brief (USART4) Manchester Encoder Decoder Register */
#define REG_USART4_RPR (*(RwReg*)0x40034100U) /**< \brief (USART4) Receive Pointer Register */
#define REG_USART4_RCR (*(RwReg*)0x40034104U) /**< \brief (USART4) Receive Counter Register */
#define REG_USART4_TPR (*(RwReg*)0x40034108U) /**< \brief (USART4) Transmit Pointer Register */
#define REG_USART4_TCR (*(RwReg*)0x4003410CU) /**< \brief (USART4) Transmit Counter Register */
#define REG_USART4_RNPR (*(RwReg*)0x40034110U) /**< \brief (USART4) Receive Next Pointer Register */
#define REG_USART4_RNCR (*(RwReg*)0x40034114U) /**< \brief (USART4) Receive Next Counter Register */
#define REG_USART4_TNPR (*(RwReg*)0x40034118U) /**< \brief (USART4) Transmit Next Pointer Register */
#define REG_USART4_TNCR (*(RwReg*)0x4003411CU) /**< \brief (USART4) Transmit Next Counter Register */
#define REG_USART4_PTCR (*(WoReg*)0x40034120U) /**< \brief (USART4) Transfer Control Register */
#define REG_USART4_PTSR (*(RoReg*)0x40034124U) /**< \brief (USART4) Transfer Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM4C_USART4_INSTANCE_ */
