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

#ifndef _SAM4C_MATRIX1_INSTANCE_
#define _SAM4C_MATRIX1_INSTANCE_

/* ========== Register definition for MATRIX1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_MATRIX1_MCFG              (0x48010000U) /**< \brief (MATRIX1) Master Configuration Register */
#define REG_MATRIX1_SCFG              (0x48010040U) /**< \brief (MATRIX1) Slave Configuration Register */
#define REG_MATRIX1_PRAS0             (0x48010080U) /**< \brief (MATRIX1) Priority Register A for Slave 0 */
#define REG_MATRIX1_PRBS0             (0x48010084U) /**< \brief (MATRIX1) Priority Register B for Slave 0 */
#define REG_MATRIX1_PRAS1             (0x48010088U) /**< \brief (MATRIX1) Priority Register A for Slave 1 */
#define REG_MATRIX1_PRBS1             (0x4801008CU) /**< \brief (MATRIX1) Priority Register B for Slave 1 */
#define REG_MATRIX1_PRAS2             (0x48010090U) /**< \brief (MATRIX1) Priority Register A for Slave 2 */
#define REG_MATRIX1_PRBS2             (0x48010094U) /**< \brief (MATRIX1) Priority Register B for Slave 2 */
#define REG_MATRIX1_PRAS3             (0x48010098U) /**< \brief (MATRIX1) Priority Register A for Slave 3 */
#define REG_MATRIX1_PRBS3             (0x4801009CU) /**< \brief (MATRIX1) Priority Register B for Slave 3 */
#define REG_MATRIX1_PRAS4             (0x480100A0U) /**< \brief (MATRIX1) Priority Register A for Slave 4 */
#define REG_MATRIX1_PRBS4             (0x480100A4U) /**< \brief (MATRIX1) Priority Register B for Slave 4 */
#define REG_MATRIX1_PRAS5             (0x480100A8U) /**< \brief (MATRIX1) Priority Register A for Slave 5 */
#define REG_MATRIX1_PRBS5             (0x480100ACU) /**< \brief (MATRIX1) Priority Register B for Slave 5 */
#define REG_MATRIX1_PRAS6             (0x480100B0U) /**< \brief (MATRIX1) Priority Register A for Slave 6 */
#define REG_MATRIX1_PRBS6             (0x480100B4U) /**< \brief (MATRIX1) Priority Register B for Slave 6 */
#define REG_MATRIX1_PRAS7             (0x480100B8U) /**< \brief (MATRIX1) Priority Register A for Slave 7 */
#define REG_MATRIX1_PRBS7             (0x480100BCU) /**< \brief (MATRIX1) Priority Register B for Slave 7 */
#define REG_MATRIX1_PRAS8             (0x480100C0U) /**< \brief (MATRIX1) Priority Register A for Slave 8 */
#define REG_MATRIX1_PRBS8             (0x480100C4U) /**< \brief (MATRIX1) Priority Register B for Slave 8 */
#define REG_MATRIX1_PRAS9             (0x480100C8U) /**< \brief (MATRIX1) Priority Register A for Slave 9 */
#define REG_MATRIX1_PRBS9             (0x480100CCU) /**< \brief (MATRIX1) Priority Register B for Slave 9 */
#define REG_MATRIX1_PRAS10            (0x480100D0U) /**< \brief (MATRIX1) Priority Register A for Slave 10 */
#define REG_MATRIX1_PRBS10            (0x480100D4U) /**< \brief (MATRIX1) Priority Register B for Slave 10 */
#define REG_MATRIX1_PRAS11            (0x480100D8U) /**< \brief (MATRIX1) Priority Register A for Slave 11 */
#define REG_MATRIX1_PRBS11            (0x480100DCU) /**< \brief (MATRIX1) Priority Register B for Slave 11 */
#define REG_MATRIX1_PRAS12            (0x480100E0U) /**< \brief (MATRIX1) Priority Register A for Slave 12 */
#define REG_MATRIX1_PRBS12            (0x480100E4U) /**< \brief (MATRIX1) Priority Register B for Slave 12 */
#define REG_MATRIX1_PRAS13            (0x480100E8U) /**< \brief (MATRIX1) Priority Register A for Slave 13 */
#define REG_MATRIX1_PRBS13            (0x480100ECU) /**< \brief (MATRIX1) Priority Register B for Slave 13 */
#define REG_MATRIX1_PRAS14            (0x480100F0U) /**< \brief (MATRIX1) Priority Register A for Slave 14 */
#define REG_MATRIX1_PRBS14            (0x480100F4U) /**< \brief (MATRIX1) Priority Register B for Slave 14 */
#define REG_MATRIX1_PRAS15            (0x480100F8U) /**< \brief (MATRIX1) Priority Register A for Slave 15 */
#define REG_MATRIX1_PRBS15            (0x480100FCU) /**< \brief (MATRIX1) Priority Register B for Slave 15 */
#define REG_MATRIX1_MRCR              (0x48010100U) /**< \brief (MATRIX1) Master Remap Control Register */
#define REG_MATRIX1_SFR               (0x48010110U) /**< \brief (MATRIX1) Special Function Register */
#define REG_MATRIX1_MEIER             (0x48010150U) /**< \brief (MATRIX1) Master Error Interrupt Enable Register */
#define REG_MATRIX1_MEIDR             (0x48010154U) /**< \brief (MATRIX1) Master Error Interrupt Disable Register */
#define REG_MATRIX1_MEIMR             (0x48010158U) /**< \brief (MATRIX1) Master Error Interrupt Mask Register */
#define REG_MATRIX1_MESR              (0x4801015CU) /**< \brief (MATRIX1) Master Error Status Register */
#define REG_MATRIX1_MEAR              (0x48010160U) /**< \brief (MATRIX1) Master 0 Error Address Register */
#define REG_MATRIX1_WPMR              (0x480101E4U) /**< \brief (MATRIX1) Write Protect Mode Register */
#define REG_MATRIX1_WPSR              (0x480101E8U) /**< \brief (MATRIX1) Write Protect Status Register */
#else
#define REG_MATRIX1_MCFG     (*(RwReg*)0x48010000U) /**< \brief (MATRIX1) Master Configuration Register */
#define REG_MATRIX1_SCFG     (*(RwReg*)0x48010040U) /**< \brief (MATRIX1) Slave Configuration Register */
#define REG_MATRIX1_PRAS0    (*(RwReg*)0x48010080U) /**< \brief (MATRIX1) Priority Register A for Slave 0 */
#define REG_MATRIX1_PRBS0    (*(RwReg*)0x48010084U) /**< \brief (MATRIX1) Priority Register B for Slave 0 */
#define REG_MATRIX1_PRAS1    (*(RwReg*)0x48010088U) /**< \brief (MATRIX1) Priority Register A for Slave 1 */
#define REG_MATRIX1_PRBS1    (*(RwReg*)0x4801008CU) /**< \brief (MATRIX1) Priority Register B for Slave 1 */
#define REG_MATRIX1_PRAS2    (*(RwReg*)0x48010090U) /**< \brief (MATRIX1) Priority Register A for Slave 2 */
#define REG_MATRIX1_PRBS2    (*(RwReg*)0x48010094U) /**< \brief (MATRIX1) Priority Register B for Slave 2 */
#define REG_MATRIX1_PRAS3    (*(RwReg*)0x48010098U) /**< \brief (MATRIX1) Priority Register A for Slave 3 */
#define REG_MATRIX1_PRBS3    (*(RwReg*)0x4801009CU) /**< \brief (MATRIX1) Priority Register B for Slave 3 */
#define REG_MATRIX1_PRAS4    (*(RwReg*)0x480100A0U) /**< \brief (MATRIX1) Priority Register A for Slave 4 */
#define REG_MATRIX1_PRBS4    (*(RwReg*)0x480100A4U) /**< \brief (MATRIX1) Priority Register B for Slave 4 */
#define REG_MATRIX1_PRAS5    (*(RwReg*)0x480100A8U) /**< \brief (MATRIX1) Priority Register A for Slave 5 */
#define REG_MATRIX1_PRBS5    (*(RwReg*)0x480100ACU) /**< \brief (MATRIX1) Priority Register B for Slave 5 */
#define REG_MATRIX1_PRAS6    (*(RwReg*)0x480100B0U) /**< \brief (MATRIX1) Priority Register A for Slave 6 */
#define REG_MATRIX1_PRBS6    (*(RwReg*)0x480100B4U) /**< \brief (MATRIX1) Priority Register B for Slave 6 */
#define REG_MATRIX1_PRAS7    (*(RwReg*)0x480100B8U) /**< \brief (MATRIX1) Priority Register A for Slave 7 */
#define REG_MATRIX1_PRBS7    (*(RwReg*)0x480100BCU) /**< \brief (MATRIX1) Priority Register B for Slave 7 */
#define REG_MATRIX1_PRAS8    (*(RwReg*)0x480100C0U) /**< \brief (MATRIX1) Priority Register A for Slave 8 */
#define REG_MATRIX1_PRBS8    (*(RwReg*)0x480100C4U) /**< \brief (MATRIX1) Priority Register B for Slave 8 */
#define REG_MATRIX1_PRAS9    (*(RwReg*)0x480100C8U) /**< \brief (MATRIX1) Priority Register A for Slave 9 */
#define REG_MATRIX1_PRBS9    (*(RwReg*)0x480100CCU) /**< \brief (MATRIX1) Priority Register B for Slave 9 */
#define REG_MATRIX1_PRAS10   (*(RwReg*)0x480100D0U) /**< \brief (MATRIX1) Priority Register A for Slave 10 */
#define REG_MATRIX1_PRBS10   (*(RwReg*)0x480100D4U) /**< \brief (MATRIX1) Priority Register B for Slave 10 */
#define REG_MATRIX1_PRAS11   (*(RwReg*)0x480100D8U) /**< \brief (MATRIX1) Priority Register A for Slave 11 */
#define REG_MATRIX1_PRBS11   (*(RwReg*)0x480100DCU) /**< \brief (MATRIX1) Priority Register B for Slave 11 */
#define REG_MATRIX1_PRAS12   (*(RwReg*)0x480100E0U) /**< \brief (MATRIX1) Priority Register A for Slave 12 */
#define REG_MATRIX1_PRBS12   (*(RwReg*)0x480100E4U) /**< \brief (MATRIX1) Priority Register B for Slave 12 */
#define REG_MATRIX1_PRAS13   (*(RwReg*)0x480100E8U) /**< \brief (MATRIX1) Priority Register A for Slave 13 */
#define REG_MATRIX1_PRBS13   (*(RwReg*)0x480100ECU) /**< \brief (MATRIX1) Priority Register B for Slave 13 */
#define REG_MATRIX1_PRAS14   (*(RwReg*)0x480100F0U) /**< \brief (MATRIX1) Priority Register A for Slave 14 */
#define REG_MATRIX1_PRBS14   (*(RwReg*)0x480100F4U) /**< \brief (MATRIX1) Priority Register B for Slave 14 */
#define REG_MATRIX1_PRAS15   (*(RwReg*)0x480100F8U) /**< \brief (MATRIX1) Priority Register A for Slave 15 */
#define REG_MATRIX1_PRBS15   (*(RwReg*)0x480100FCU) /**< \brief (MATRIX1) Priority Register B for Slave 15 */
#define REG_MATRIX1_MRCR     (*(RwReg*)0x48010100U) /**< \brief (MATRIX1) Master Remap Control Register */
#define REG_MATRIX1_SFR      (*(RwReg*)0x48010110U) /**< \brief (MATRIX1) Special Function Register */
#define REG_MATRIX1_MEIER    (*(WoReg*)0x48010150U) /**< \brief (MATRIX1) Master Error Interrupt Enable Register */
#define REG_MATRIX1_MEIDR    (*(WoReg*)0x48010154U) /**< \brief (MATRIX1) Master Error Interrupt Disable Register */
#define REG_MATRIX1_MEIMR    (*(RoReg*)0x48010158U) /**< \brief (MATRIX1) Master Error Interrupt Mask Register */
#define REG_MATRIX1_MESR     (*(RoReg*)0x4801015CU) /**< \brief (MATRIX1) Master Error Status Register */
#define REG_MATRIX1_MEAR     (*(RoReg*)0x48010160U) /**< \brief (MATRIX1) Master 0 Error Address Register */
#define REG_MATRIX1_WPMR     (*(RwReg*)0x480101E4U) /**< \brief (MATRIX1) Write Protect Mode Register */
#define REG_MATRIX1_WPSR     (*(RoReg*)0x480101E8U) /**< \brief (MATRIX1) Write Protect Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM4C_MATRIX1_INSTANCE_ */
