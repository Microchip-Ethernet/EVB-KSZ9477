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

#ifndef _SAM4C_ICM_INSTANCE_
#define _SAM4C_ICM_INSTANCE_

/* ========== Register definition for ICM peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_ICM_CFG                (0x40044000U) /**< \brief (ICM) Configuration Register */
#define REG_ICM_CTRL               (0x40044004U) /**< \brief (ICM) Control Register */
#define REG_ICM_SR                 (0x40044008U) /**< \brief (ICM) Status Register */
#define REG_ICM_IER                (0x40044010U) /**< \brief (ICM) Interrupt Enable Register */
#define REG_ICM_IDR                (0x40044014U) /**< \brief (ICM) Interrupt Disable Register */
#define REG_ICM_IMR                (0x40044018U) /**< \brief (ICM) Interrupt Mask Register */
#define REG_ICM_ISR                (0x4004401CU) /**< \brief (ICM) Interrupt Status Register */
#define REG_ICM_UASR               (0x40044020U) /**< \brief (ICM) Undefined Access Status Register */
#define REG_ICM_DSCR               (0x40044030U) /**< \brief (ICM) Region Descriptor Area Start Address Register */
#define REG_ICM_HASH               (0x40044034U) /**< \brief (ICM) Region Hash Area Start Address Register */
#define REG_ICM_UIHVAL             (0x40044038U) /**< \brief (ICM) User Initial Hash Value 0 Register */
#else
#define REG_ICM_CFG       (*(RwReg*)0x40044000U) /**< \brief (ICM) Configuration Register */
#define REG_ICM_CTRL      (*(WoReg*)0x40044004U) /**< \brief (ICM) Control Register */
#define REG_ICM_SR        (*(WoReg*)0x40044008U) /**< \brief (ICM) Status Register */
#define REG_ICM_IER       (*(WoReg*)0x40044010U) /**< \brief (ICM) Interrupt Enable Register */
#define REG_ICM_IDR       (*(WoReg*)0x40044014U) /**< \brief (ICM) Interrupt Disable Register */
#define REG_ICM_IMR       (*(RoReg*)0x40044018U) /**< \brief (ICM) Interrupt Mask Register */
#define REG_ICM_ISR       (*(RoReg*)0x4004401CU) /**< \brief (ICM) Interrupt Status Register */
#define REG_ICM_UASR      (*(RoReg*)0x40044020U) /**< \brief (ICM) Undefined Access Status Register */
#define REG_ICM_DSCR      (*(RwReg*)0x40044030U) /**< \brief (ICM) Region Descriptor Area Start Address Register */
#define REG_ICM_HASH      (*(RwReg*)0x40044034U) /**< \brief (ICM) Region Hash Area Start Address Register */
#define REG_ICM_UIHVAL    (*(WoReg*)0x40044038U) /**< \brief (ICM) User Initial Hash Value 0 Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM4C_ICM_INSTANCE_ */
