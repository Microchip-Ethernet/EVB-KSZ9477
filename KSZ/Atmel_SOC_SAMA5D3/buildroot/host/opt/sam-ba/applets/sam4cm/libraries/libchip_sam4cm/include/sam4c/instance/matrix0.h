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

#ifndef _SAM4C_MATRIX0_INSTANCE_
#define _SAM4C_MATRIX0_INSTANCE_

/* ========== Register definition for MATRIX0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_MATRIX0_MCFG              (0x400E0200U) /**< \brief (MATRIX0) Master Configuration Register */
#define REG_MATRIX0_SCFG              (0x400E0240U) /**< \brief (MATRIX0) Slave Configuration Register */
#define REG_MATRIX0_PRAS0             (0x400E0280U) /**< \brief (MATRIX0) Priority Register A for Slave 0 */
#define REG_MATRIX0_PRBS0             (0x400E0284U) /**< \brief (MATRIX0) Priority Register B for Slave 0 */
#define REG_MATRIX0_PRAS1             (0x400E0288U) /**< \brief (MATRIX0) Priority Register A for Slave 1 */
#define REG_MATRIX0_PRBS1             (0x400E028CU) /**< \brief (MATRIX0) Priority Register B for Slave 1 */
#define REG_MATRIX0_PRAS2             (0x400E0290U) /**< \brief (MATRIX0) Priority Register A for Slave 2 */
#define REG_MATRIX0_PRBS2             (0x400E0294U) /**< \brief (MATRIX0) Priority Register B for Slave 2 */
#define REG_MATRIX0_PRAS3             (0x400E0298U) /**< \brief (MATRIX0) Priority Register A for Slave 3 */
#define REG_MATRIX0_PRBS3             (0x400E029CU) /**< \brief (MATRIX0) Priority Register B for Slave 3 */
#define REG_MATRIX0_PRAS4             (0x400E02A0U) /**< \brief (MATRIX0) Priority Register A for Slave 4 */
#define REG_MATRIX0_PRBS4             (0x400E02A4U) /**< \brief (MATRIX0) Priority Register B for Slave 4 */
#define REG_MATRIX0_PRAS5             (0x400E02A8U) /**< \brief (MATRIX0) Priority Register A for Slave 5 */
#define REG_MATRIX0_PRBS5             (0x400E02ACU) /**< \brief (MATRIX0) Priority Register B for Slave 5 */
#define REG_MATRIX0_PRAS6             (0x400E02B0U) /**< \brief (MATRIX0) Priority Register A for Slave 6 */
#define REG_MATRIX0_PRBS6             (0x400E02B4U) /**< \brief (MATRIX0) Priority Register B for Slave 6 */
#define REG_MATRIX0_PRAS7             (0x400E02B8U) /**< \brief (MATRIX0) Priority Register A for Slave 7 */
#define REG_MATRIX0_PRBS7             (0x400E02BCU) /**< \brief (MATRIX0) Priority Register B for Slave 7 */
#define REG_MATRIX0_PRAS8             (0x400E02C0U) /**< \brief (MATRIX0) Priority Register A for Slave 8 */
#define REG_MATRIX0_PRBS8             (0x400E02C4U) /**< \brief (MATRIX0) Priority Register B for Slave 8 */
#define REG_MATRIX0_PRAS9             (0x400E02C8U) /**< \brief (MATRIX0) Priority Register A for Slave 9 */
#define REG_MATRIX0_PRBS9             (0x400E02CCU) /**< \brief (MATRIX0) Priority Register B for Slave 9 */
#define REG_MATRIX0_PRAS10            (0x400E02D0U) /**< \brief (MATRIX0) Priority Register A for Slave 10 */
#define REG_MATRIX0_PRBS10            (0x400E02D4U) /**< \brief (MATRIX0) Priority Register B for Slave 10 */
#define REG_MATRIX0_PRAS11            (0x400E02D8U) /**< \brief (MATRIX0) Priority Register A for Slave 11 */
#define REG_MATRIX0_PRBS11            (0x400E02DCU) /**< \brief (MATRIX0) Priority Register B for Slave 11 */
#define REG_MATRIX0_PRAS12            (0x400E02E0U) /**< \brief (MATRIX0) Priority Register A for Slave 12 */
#define REG_MATRIX0_PRBS12            (0x400E02E4U) /**< \brief (MATRIX0) Priority Register B for Slave 12 */
#define REG_MATRIX0_PRAS13            (0x400E02E8U) /**< \brief (MATRIX0) Priority Register A for Slave 13 */
#define REG_MATRIX0_PRBS13            (0x400E02ECU) /**< \brief (MATRIX0) Priority Register B for Slave 13 */
#define REG_MATRIX0_PRAS14            (0x400E02F0U) /**< \brief (MATRIX0) Priority Register A for Slave 14 */
#define REG_MATRIX0_PRBS14            (0x400E02F4U) /**< \brief (MATRIX0) Priority Register B for Slave 14 */
#define REG_MATRIX0_PRAS15            (0x400E02F8U) /**< \brief (MATRIX0) Priority Register A for Slave 15 */
#define REG_MATRIX0_PRBS15            (0x400E02FCU) /**< \brief (MATRIX0) Priority Register B for Slave 15 */
#define REG_MATRIX0_MRCR              (0x400E0300U) /**< \brief (MATRIX0) Master Remap Control Register */
#define REG_MATRIX0_SFR               (0x400E0310U) /**< \brief (MATRIX0) Special Function Register */
#define REG_MATRIX0_MEIER             (0x400E0350U) /**< \brief (MATRIX0) Master Error Interrupt Enable Register */
#define REG_MATRIX0_MEIDR             (0x400E0354U) /**< \brief (MATRIX0) Master Error Interrupt Disable Register */
#define REG_MATRIX0_MEIMR             (0x400E0358U) /**< \brief (MATRIX0) Master Error Interrupt Mask Register */
#define REG_MATRIX0_MESR              (0x400E035CU) /**< \brief (MATRIX0) Master Error Status Register */
#define REG_MATRIX0_MEAR              (0x400E0360U) /**< \brief (MATRIX0) Master 0 Error Address Register */
#define REG_MATRIX0_WPMR              (0x400E03E4U) /**< \brief (MATRIX0) Write Protect Mode Register */
#define REG_MATRIX0_WPSR              (0x400E03E8U) /**< \brief (MATRIX0) Write Protect Status Register */
#else
#define REG_MATRIX0_MCFG     (*(RwReg*)0x400E0200U) /**< \brief (MATRIX0) Master Configuration Register */
#define REG_MATRIX0_SCFG     (*(RwReg*)0x400E0240U) /**< \brief (MATRIX0) Slave Configuration Register */
#define REG_MATRIX0_PRAS0    (*(RwReg*)0x400E0280U) /**< \brief (MATRIX0) Priority Register A for Slave 0 */
#define REG_MATRIX0_PRBS0    (*(RwReg*)0x400E0284U) /**< \brief (MATRIX0) Priority Register B for Slave 0 */
#define REG_MATRIX0_PRAS1    (*(RwReg*)0x400E0288U) /**< \brief (MATRIX0) Priority Register A for Slave 1 */
#define REG_MATRIX0_PRBS1    (*(RwReg*)0x400E028CU) /**< \brief (MATRIX0) Priority Register B for Slave 1 */
#define REG_MATRIX0_PRAS2    (*(RwReg*)0x400E0290U) /**< \brief (MATRIX0) Priority Register A for Slave 2 */
#define REG_MATRIX0_PRBS2    (*(RwReg*)0x400E0294U) /**< \brief (MATRIX0) Priority Register B for Slave 2 */
#define REG_MATRIX0_PRAS3    (*(RwReg*)0x400E0298U) /**< \brief (MATRIX0) Priority Register A for Slave 3 */
#define REG_MATRIX0_PRBS3    (*(RwReg*)0x400E029CU) /**< \brief (MATRIX0) Priority Register B for Slave 3 */
#define REG_MATRIX0_PRAS4    (*(RwReg*)0x400E02A0U) /**< \brief (MATRIX0) Priority Register A for Slave 4 */
#define REG_MATRIX0_PRBS4    (*(RwReg*)0x400E02A4U) /**< \brief (MATRIX0) Priority Register B for Slave 4 */
#define REG_MATRIX0_PRAS5    (*(RwReg*)0x400E02A8U) /**< \brief (MATRIX0) Priority Register A for Slave 5 */
#define REG_MATRIX0_PRBS5    (*(RwReg*)0x400E02ACU) /**< \brief (MATRIX0) Priority Register B for Slave 5 */
#define REG_MATRIX0_PRAS6    (*(RwReg*)0x400E02B0U) /**< \brief (MATRIX0) Priority Register A for Slave 6 */
#define REG_MATRIX0_PRBS6    (*(RwReg*)0x400E02B4U) /**< \brief (MATRIX0) Priority Register B for Slave 6 */
#define REG_MATRIX0_PRAS7    (*(RwReg*)0x400E02B8U) /**< \brief (MATRIX0) Priority Register A for Slave 7 */
#define REG_MATRIX0_PRBS7    (*(RwReg*)0x400E02BCU) /**< \brief (MATRIX0) Priority Register B for Slave 7 */
#define REG_MATRIX0_PRAS8    (*(RwReg*)0x400E02C0U) /**< \brief (MATRIX0) Priority Register A for Slave 8 */
#define REG_MATRIX0_PRBS8    (*(RwReg*)0x400E02C4U) /**< \brief (MATRIX0) Priority Register B for Slave 8 */
#define REG_MATRIX0_PRAS9    (*(RwReg*)0x400E02C8U) /**< \brief (MATRIX0) Priority Register A for Slave 9 */
#define REG_MATRIX0_PRBS9    (*(RwReg*)0x400E02CCU) /**< \brief (MATRIX0) Priority Register B for Slave 9 */
#define REG_MATRIX0_PRAS10   (*(RwReg*)0x400E02D0U) /**< \brief (MATRIX0) Priority Register A for Slave 10 */
#define REG_MATRIX0_PRBS10   (*(RwReg*)0x400E02D4U) /**< \brief (MATRIX0) Priority Register B for Slave 10 */
#define REG_MATRIX0_PRAS11   (*(RwReg*)0x400E02D8U) /**< \brief (MATRIX0) Priority Register A for Slave 11 */
#define REG_MATRIX0_PRBS11   (*(RwReg*)0x400E02DCU) /**< \brief (MATRIX0) Priority Register B for Slave 11 */
#define REG_MATRIX0_PRAS12   (*(RwReg*)0x400E02E0U) /**< \brief (MATRIX0) Priority Register A for Slave 12 */
#define REG_MATRIX0_PRBS12   (*(RwReg*)0x400E02E4U) /**< \brief (MATRIX0) Priority Register B for Slave 12 */
#define REG_MATRIX0_PRAS13   (*(RwReg*)0x400E02E8U) /**< \brief (MATRIX0) Priority Register A for Slave 13 */
#define REG_MATRIX0_PRBS13   (*(RwReg*)0x400E02ECU) /**< \brief (MATRIX0) Priority Register B for Slave 13 */
#define REG_MATRIX0_PRAS14   (*(RwReg*)0x400E02F0U) /**< \brief (MATRIX0) Priority Register A for Slave 14 */
#define REG_MATRIX0_PRBS14   (*(RwReg*)0x400E02F4U) /**< \brief (MATRIX0) Priority Register B for Slave 14 */
#define REG_MATRIX0_PRAS15   (*(RwReg*)0x400E02F8U) /**< \brief (MATRIX0) Priority Register A for Slave 15 */
#define REG_MATRIX0_PRBS15   (*(RwReg*)0x400E02FCU) /**< \brief (MATRIX0) Priority Register B for Slave 15 */
#define REG_MATRIX0_MRCR     (*(RwReg*)0x400E0300U) /**< \brief (MATRIX0) Master Remap Control Register */
#define REG_MATRIX0_SFR      (*(RwReg*)0x400E0310U) /**< \brief (MATRIX0) Special Function Register */
#define REG_MATRIX0_MEIER    (*(WoReg*)0x400E0350U) /**< \brief (MATRIX0) Master Error Interrupt Enable Register */
#define REG_MATRIX0_MEIDR    (*(WoReg*)0x400E0354U) /**< \brief (MATRIX0) Master Error Interrupt Disable Register */
#define REG_MATRIX0_MEIMR    (*(RoReg*)0x400E0358U) /**< \brief (MATRIX0) Master Error Interrupt Mask Register */
#define REG_MATRIX0_MESR     (*(RoReg*)0x400E035CU) /**< \brief (MATRIX0) Master Error Status Register */
#define REG_MATRIX0_MEAR     (*(RoReg*)0x400E0360U) /**< \brief (MATRIX0) Master 0 Error Address Register */
#define REG_MATRIX0_WPMR     (*(RwReg*)0x400E03E4U) /**< \brief (MATRIX0) Write Protect Mode Register */
#define REG_MATRIX0_WPSR     (*(RoReg*)0x400E03E8U) /**< \brief (MATRIX0) Write Protect Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM4C_MATRIX0_INSTANCE_ */
