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

#ifndef _SAM4C_SMC0_INSTANCE_
#define _SAM4C_SMC0_INSTANCE_

/* ========== Register definition for SMC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SMC0_SETUP0          (0x400E0000U) /**< \brief (SMC0) SMC Setup Register (CS_number = 0) */
#define REG_SMC0_PULSE0          (0x400E0004U) /**< \brief (SMC0) SMC Pulse Register (CS_number = 0) */
#define REG_SMC0_CYCLE0          (0x400E0008U) /**< \brief (SMC0) SMC Cycle Register (CS_number = 0) */
#define REG_SMC0_MODE0           (0x400E000CU) /**< \brief (SMC0) SMC Mode Register (CS_number = 0) */
#define REG_SMC0_SETUP1          (0x400E0010U) /**< \brief (SMC0) SMC Setup Register (CS_number = 1) */
#define REG_SMC0_PULSE1          (0x400E0014U) /**< \brief (SMC0) SMC Pulse Register (CS_number = 1) */
#define REG_SMC0_CYCLE1          (0x400E0018U) /**< \brief (SMC0) SMC Cycle Register (CS_number = 1) */
#define REG_SMC0_MODE1           (0x400E001CU) /**< \brief (SMC0) SMC Mode Register (CS_number = 1) */
#define REG_SMC0_SETUP2          (0x400E0020U) /**< \brief (SMC0) SMC Setup Register (CS_number = 2) */
#define REG_SMC0_PULSE2          (0x400E0024U) /**< \brief (SMC0) SMC Pulse Register (CS_number = 2) */
#define REG_SMC0_CYCLE2          (0x400E0028U) /**< \brief (SMC0) SMC Cycle Register (CS_number = 2) */
#define REG_SMC0_MODE2           (0x400E002CU) /**< \brief (SMC0) SMC Mode Register (CS_number = 2) */
#define REG_SMC0_SETUP3          (0x400E0030U) /**< \brief (SMC0) SMC Setup Register (CS_number = 3) */
#define REG_SMC0_PULSE3          (0x400E0034U) /**< \brief (SMC0) SMC Pulse Register (CS_number = 3) */
#define REG_SMC0_CYCLE3          (0x400E0038U) /**< \brief (SMC0) SMC Cycle Register (CS_number = 3) */
#define REG_SMC0_MODE3           (0x400E003CU) /**< \brief (SMC0) SMC Mode Register (CS_number = 3) */
#define REG_SMC0_OCMS            (0x400E0080U) /**< \brief (SMC0) SMC OCMS MODE Register */
#define REG_SMC0_KEY1            (0x400E0084U) /**< \brief (SMC0) SMC OCMS KEY1 Register */
#define REG_SMC0_KEY2            (0x400E0088U) /**< \brief (SMC0) SMC OCMS KEY2 Register */
#define REG_SMC0_WPMR            (0x400E00E4U) /**< \brief (SMC0) SMC Write Protect Mode Register */
#define REG_SMC0_WPSR            (0x400E00E8U) /**< \brief (SMC0) SMC Write Protect Status Register */
#else
#define REG_SMC0_SETUP0 (*(RwReg*)0x400E0000U) /**< \brief (SMC0) SMC Setup Register (CS_number = 0) */
#define REG_SMC0_PULSE0 (*(RwReg*)0x400E0004U) /**< \brief (SMC0) SMC Pulse Register (CS_number = 0) */
#define REG_SMC0_CYCLE0 (*(RwReg*)0x400E0008U) /**< \brief (SMC0) SMC Cycle Register (CS_number = 0) */
#define REG_SMC0_MODE0  (*(RwReg*)0x400E000CU) /**< \brief (SMC0) SMC Mode Register (CS_number = 0) */
#define REG_SMC0_SETUP1 (*(RwReg*)0x400E0010U) /**< \brief (SMC0) SMC Setup Register (CS_number = 1) */
#define REG_SMC0_PULSE1 (*(RwReg*)0x400E0014U) /**< \brief (SMC0) SMC Pulse Register (CS_number = 1) */
#define REG_SMC0_CYCLE1 (*(RwReg*)0x400E0018U) /**< \brief (SMC0) SMC Cycle Register (CS_number = 1) */
#define REG_SMC0_MODE1  (*(RwReg*)0x400E001CU) /**< \brief (SMC0) SMC Mode Register (CS_number = 1) */
#define REG_SMC0_SETUP2 (*(RwReg*)0x400E0020U) /**< \brief (SMC0) SMC Setup Register (CS_number = 2) */
#define REG_SMC0_PULSE2 (*(RwReg*)0x400E0024U) /**< \brief (SMC0) SMC Pulse Register (CS_number = 2) */
#define REG_SMC0_CYCLE2 (*(RwReg*)0x400E0028U) /**< \brief (SMC0) SMC Cycle Register (CS_number = 2) */
#define REG_SMC0_MODE2  (*(RwReg*)0x400E002CU) /**< \brief (SMC0) SMC Mode Register (CS_number = 2) */
#define REG_SMC0_SETUP3 (*(RwReg*)0x400E0030U) /**< \brief (SMC0) SMC Setup Register (CS_number = 3) */
#define REG_SMC0_PULSE3 (*(RwReg*)0x400E0034U) /**< \brief (SMC0) SMC Pulse Register (CS_number = 3) */
#define REG_SMC0_CYCLE3 (*(RwReg*)0x400E0038U) /**< \brief (SMC0) SMC Cycle Register (CS_number = 3) */
#define REG_SMC0_MODE3  (*(RwReg*)0x400E003CU) /**< \brief (SMC0) SMC Mode Register (CS_number = 3) */
#define REG_SMC0_OCMS   (*(RwReg*)0x400E0080U) /**< \brief (SMC0) SMC OCMS MODE Register */
#define REG_SMC0_KEY1   (*(WoReg*)0x400E0084U) /**< \brief (SMC0) SMC OCMS KEY1 Register */
#define REG_SMC0_KEY2   (*(WoReg*)0x400E0088U) /**< \brief (SMC0) SMC OCMS KEY2 Register */
#define REG_SMC0_WPMR   (*(RwReg*)0x400E00E4U) /**< \brief (SMC0) SMC Write Protect Mode Register */
#define REG_SMC0_WPSR   (*(RoReg*)0x400E00E8U) /**< \brief (SMC0) SMC Write Protect Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM4C_SMC0_INSTANCE_ */
