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

#ifndef _SAM4C_CMCC1_INSTANCE_
#define _SAM4C_CMCC1_INSTANCE_

/* ========== Register definition for CMCC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_CMCC1_TYPE            (0x48018000U) /**< \brief (CMCC1) Cache Type Register */
#define REG_CMCC1_CFG             (0x48018004U) /**< \brief (CMCC1) Cache Configuration Register */
#define REG_CMCC1_CTRL            (0x48018008U) /**< \brief (CMCC1) Cache Control Register */
#define REG_CMCC1_SR              (0x4801800CU) /**< \brief (CMCC1) Cache Status Register */
#define REG_CMCC1_MAINT0          (0x48018020U) /**< \brief (CMCC1) Cache Maintenance Register 0 */
#define REG_CMCC1_MAINT1          (0x48018024U) /**< \brief (CMCC1) Cache Maintenance Register 1 */
#define REG_CMCC1_MCFG            (0x48018028U) /**< \brief (CMCC1) Cache Monitor Configuration Register */
#define REG_CMCC1_MEN             (0x4801802CU) /**< \brief (CMCC1) Cache Monitor Enable Register */
#define REG_CMCC1_MCTRL           (0x48018030U) /**< \brief (CMCC1) Cache Monitor Control Register */
#define REG_CMCC1_MSR             (0x48018034U) /**< \brief (CMCC1) Cache Monitor Status Register */
#else
#define REG_CMCC1_TYPE   (*(RoReg*)0x48018000U) /**< \brief (CMCC1) Cache Type Register */
#define REG_CMCC1_CFG    (*(RwReg*)0x48018004U) /**< \brief (CMCC1) Cache Configuration Register */
#define REG_CMCC1_CTRL   (*(WoReg*)0x48018008U) /**< \brief (CMCC1) Cache Control Register */
#define REG_CMCC1_SR     (*(RoReg*)0x4801800CU) /**< \brief (CMCC1) Cache Status Register */
#define REG_CMCC1_MAINT0 (*(WoReg*)0x48018020U) /**< \brief (CMCC1) Cache Maintenance Register 0 */
#define REG_CMCC1_MAINT1 (*(WoReg*)0x48018024U) /**< \brief (CMCC1) Cache Maintenance Register 1 */
#define REG_CMCC1_MCFG   (*(RwReg*)0x48018028U) /**< \brief (CMCC1) Cache Monitor Configuration Register */
#define REG_CMCC1_MEN    (*(RwReg*)0x4801802CU) /**< \brief (CMCC1) Cache Monitor Enable Register */
#define REG_CMCC1_MCTRL  (*(WoReg*)0x48018030U) /**< \brief (CMCC1) Cache Monitor Control Register */
#define REG_CMCC1_MSR    (*(RoReg*)0x48018034U) /**< \brief (CMCC1) Cache Monitor Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM4C_CMCC1_INSTANCE_ */
