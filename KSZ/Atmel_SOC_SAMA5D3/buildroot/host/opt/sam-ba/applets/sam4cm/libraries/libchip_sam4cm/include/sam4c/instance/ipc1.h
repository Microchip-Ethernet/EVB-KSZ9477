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

#ifndef _SAM4C_IPC1_INSTANCE_
#define _SAM4C_IPC1_INSTANCE_

/* ========== Register definition for IPC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_IPC1_ISCR          (0x48014000U) /**< \brief (IPC1) Interrupt Set Command Register */
#define REG_IPC1_ICCR          (0x48014004U) /**< \brief (IPC1) Interrupt Clear Command Register */
#define REG_IPC1_IPR           (0x48014008U) /**< \brief (IPC1) Interrupt Pending Register */
#define REG_IPC1_IECR          (0x4801400CU) /**< \brief (IPC1) Interrupt Enable Command Register */
#define REG_IPC1_IDCR          (0x48014010U) /**< \brief (IPC1) Interrupt Disable Command Register */
#define REG_IPC1_IMR           (0x48014014U) /**< \brief (IPC1) Interrupt Mask Register */
#define REG_IPC1_ISR           (0x48014018U) /**< \brief (IPC1) Interrupt Status Register */
#else
#define REG_IPC1_ISCR (*(WoReg*)0x48014000U) /**< \brief (IPC1) Interrupt Set Command Register */
#define REG_IPC1_ICCR (*(WoReg*)0x48014004U) /**< \brief (IPC1) Interrupt Clear Command Register */
#define REG_IPC1_IPR  (*(RoReg*)0x48014008U) /**< \brief (IPC1) Interrupt Pending Register */
#define REG_IPC1_IECR (*(WoReg*)0x4801400CU) /**< \brief (IPC1) Interrupt Enable Command Register */
#define REG_IPC1_IDCR (*(WoReg*)0x48014010U) /**< \brief (IPC1) Interrupt Disable Command Register */
#define REG_IPC1_IMR  (*(RoReg*)0x48014014U) /**< \brief (IPC1) Interrupt Mask Register */
#define REG_IPC1_ISR  (*(RoReg*)0x48014018U) /**< \brief (IPC1) Interrupt Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM4C_IPC1_INSTANCE_ */
