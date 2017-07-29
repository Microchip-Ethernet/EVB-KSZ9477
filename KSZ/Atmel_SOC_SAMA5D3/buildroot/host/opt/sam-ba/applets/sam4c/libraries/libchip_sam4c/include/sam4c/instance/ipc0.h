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

#ifndef _SAM4C_IPC0_INSTANCE_
#define _SAM4C_IPC0_INSTANCE_

/* ========== Register definition for IPC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_IPC0_ISCR          (0x4004C000U) /**< \brief (IPC0) Interrupt Set Command Register */
#define REG_IPC0_ICCR          (0x4004C004U) /**< \brief (IPC0) Interrupt Clear Command Register */
#define REG_IPC0_IPR           (0x4004C008U) /**< \brief (IPC0) Interrupt Pending Register */
#define REG_IPC0_IECR          (0x4004C00CU) /**< \brief (IPC0) Interrupt Enable Command Register */
#define REG_IPC0_IDCR          (0x4004C010U) /**< \brief (IPC0) Interrupt Disable Command Register */
#define REG_IPC0_IMR           (0x4004C014U) /**< \brief (IPC0) Interrupt Mask Register */
#define REG_IPC0_ISR           (0x4004C018U) /**< \brief (IPC0) Interrupt Status Register */
#else
#define REG_IPC0_ISCR (*(WoReg*)0x4004C000U) /**< \brief (IPC0) Interrupt Set Command Register */
#define REG_IPC0_ICCR (*(WoReg*)0x4004C004U) /**< \brief (IPC0) Interrupt Clear Command Register */
#define REG_IPC0_IPR  (*(RoReg*)0x4004C008U) /**< \brief (IPC0) Interrupt Pending Register */
#define REG_IPC0_IECR (*(WoReg*)0x4004C00CU) /**< \brief (IPC0) Interrupt Enable Command Register */
#define REG_IPC0_IDCR (*(WoReg*)0x4004C010U) /**< \brief (IPC0) Interrupt Disable Command Register */
#define REG_IPC0_IMR  (*(RoReg*)0x4004C014U) /**< \brief (IPC0) Interrupt Mask Register */
#define REG_IPC0_ISR  (*(RoReg*)0x4004C018U) /**< \brief (IPC0) Interrupt Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM4C_IPC0_INSTANCE_ */
