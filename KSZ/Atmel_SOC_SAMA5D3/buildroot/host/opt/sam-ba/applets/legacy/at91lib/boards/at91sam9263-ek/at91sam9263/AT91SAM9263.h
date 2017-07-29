//  ----------------------------------------------------------------------------
//          ATMEL Microcontroller Software Support  -  ROUSSET  -
//  ----------------------------------------------------------------------------
//  Copyright (c) 2008, Atmel Corporation
// 
//  All rights reserved.
// 
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
// 
//  - Redistributions of source code must retain the above copyright notice,
//  this list of conditions and the disclaimer below.
// 
//  Atmel's name may not be used to endorse or promote products derived from
//  this software without specific prior written permission. 
//  
//  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
//  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
//  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  ----------------------------------------------------------------------------
// File Name           : AT91SAM9263.h
// Object              : AT91SAM9263 definitions
// Generated           : AT91 SW Application Group  01/23/2009 (11:53:35)
//  ----------------------------------------------------------------------------

#ifndef AT91SAM9263_H
#define AT91SAM9263_H

#ifndef __ASSEMBLY__
typedef volatile unsigned int AT91_REG;// Hardware register definition
#define AT91_CAST(a) (a)
#else
#define AT91_CAST(a)
#endif

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR System Peripherals
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_SYS {
	AT91_REG	 SYS_ECC0; 	// ECC 0
	AT91_REG	 Reserved0[127]; 	// 
	AT91_REG	 SYS_SDRAMC0_MR; 	// SDRAM Controller Mode Register
	AT91_REG	 SYS_SDRAMC0_TR; 	// SDRAM Controller Refresh Timer Register
	AT91_REG	 SYS_SDRAMC0_CR; 	// SDRAM Controller Configuration Register
	AT91_REG	 SYS_SDRAMC0_HSR; 	// SDRAM Controller High Speed Register
	AT91_REG	 SYS_SDRAMC0_LPR; 	// SDRAM Controller Low Power Register
	AT91_REG	 SYS_SDRAMC0_IER; 	// SDRAM Controller Interrupt Enable Register
	AT91_REG	 SYS_SDRAMC0_IDR; 	// SDRAM Controller Interrupt Disable Register
	AT91_REG	 SYS_SDRAMC0_IMR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SYS_SDRAMC0_ISR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SYS_SDRAMC0_MDR; 	// SDRAM Memory Device Register
	AT91_REG	 Reserved1[118]; 	// 
	AT91_REG	 SYS_SMC0_SETUP0; 	//  Setup Register for CS 0
	AT91_REG	 SYS_SMC0_PULSE0; 	//  Pulse Register for CS 0
	AT91_REG	 SYS_SMC0_CYCLE0; 	//  Cycle Register for CS 0
	AT91_REG	 SYS_SMC0_CTRL0; 	//  Control Register for CS 0
	AT91_REG	 SYS_SMC0_SETUP1; 	//  Setup Register for CS 1
	AT91_REG	 SYS_SMC0_PULSE1; 	//  Pulse Register for CS 1
	AT91_REG	 SYS_SMC0_CYCLE1; 	//  Cycle Register for CS 1
	AT91_REG	 SYS_SMC0_CTRL1; 	//  Control Register for CS 1
	AT91_REG	 SYS_SMC0_SETUP2; 	//  Setup Register for CS 2
	AT91_REG	 SYS_SMC0_PULSE2; 	//  Pulse Register for CS 2
	AT91_REG	 SYS_SMC0_CYCLE2; 	//  Cycle Register for CS 2
	AT91_REG	 SYS_SMC0_CTRL2; 	//  Control Register for CS 2
	AT91_REG	 SYS_SMC0_SETUP3; 	//  Setup Register for CS 3
	AT91_REG	 SYS_SMC0_PULSE3; 	//  Pulse Register for CS 3
	AT91_REG	 SYS_SMC0_CYCLE3; 	//  Cycle Register for CS 3
	AT91_REG	 SYS_SMC0_CTRL3; 	//  Control Register for CS 3
	AT91_REG	 SYS_SMC0_SETUP4; 	//  Setup Register for CS 4
	AT91_REG	 SYS_SMC0_PULSE4; 	//  Pulse Register for CS 4
	AT91_REG	 SYS_SMC0_CYCLE4; 	//  Cycle Register for CS 4
	AT91_REG	 SYS_SMC0_CTRL4; 	//  Control Register for CS 4
	AT91_REG	 SYS_SMC0_SETUP5; 	//  Setup Register for CS 5
	AT91_REG	 SYS_SMC0_PULSE5; 	//  Pulse Register for CS 5
	AT91_REG	 SYS_SMC0_CYCLE5; 	//  Cycle Register for CS 5
	AT91_REG	 SYS_SMC0_CTRL5; 	//  Control Register for CS 5
	AT91_REG	 SYS_SMC0_SETUP6; 	//  Setup Register for CS 6
	AT91_REG	 SYS_SMC0_PULSE6; 	//  Pulse Register for CS 6
	AT91_REG	 SYS_SMC0_CYCLE6; 	//  Cycle Register for CS 6
	AT91_REG	 SYS_SMC0_CTRL6; 	//  Control Register for CS 6
	AT91_REG	 SYS_SMC0_SETUP7; 	//  Setup Register for CS 7
	AT91_REG	 SYS_SMC0_PULSE7; 	//  Pulse Register for CS 7
	AT91_REG	 SYS_SMC0_CYCLE7; 	//  Cycle Register for CS 7
	AT91_REG	 SYS_SMC0_CTRL7; 	//  Control Register for CS 7
	AT91_REG	 Reserved2[96]; 	// 
	AT91_REG	 SYS_ECC1; 	// ECC 0
	AT91_REG	 Reserved3[127]; 	// 
	AT91_REG	 SYS_SDRAMC1_MR; 	// SDRAM Controller Mode Register
	AT91_REG	 SYS_SDRAMC1_TR; 	// SDRAM Controller Refresh Timer Register
	AT91_REG	 SYS_SDRAMC1_CR; 	// SDRAM Controller Configuration Register
	AT91_REG	 SYS_SDRAMC1_HSR; 	// SDRAM Controller High Speed Register
	AT91_REG	 SYS_SDRAMC1_LPR; 	// SDRAM Controller Low Power Register
	AT91_REG	 SYS_SDRAMC1_IER; 	// SDRAM Controller Interrupt Enable Register
	AT91_REG	 SYS_SDRAMC1_IDR; 	// SDRAM Controller Interrupt Disable Register
	AT91_REG	 SYS_SDRAMC1_IMR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SYS_SDRAMC1_ISR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SYS_SDRAMC1_MDR; 	// SDRAM Memory Device Register
	AT91_REG	 Reserved4[118]; 	// 
	AT91_REG	 SYS_SMC1_SETUP0; 	//  Setup Register for CS 0
	AT91_REG	 SYS_SMC1_PULSE0; 	//  Pulse Register for CS 0
	AT91_REG	 SYS_SMC1_CYCLE0; 	//  Cycle Register for CS 0
	AT91_REG	 SYS_SMC1_CTRL0; 	//  Control Register for CS 0
	AT91_REG	 SYS_SMC1_SETUP1; 	//  Setup Register for CS 1
	AT91_REG	 SYS_SMC1_PULSE1; 	//  Pulse Register for CS 1
	AT91_REG	 SYS_SMC1_CYCLE1; 	//  Cycle Register for CS 1
	AT91_REG	 SYS_SMC1_CTRL1; 	//  Control Register for CS 1
	AT91_REG	 SYS_SMC1_SETUP2; 	//  Setup Register for CS 2
	AT91_REG	 SYS_SMC1_PULSE2; 	//  Pulse Register for CS 2
	AT91_REG	 SYS_SMC1_CYCLE2; 	//  Cycle Register for CS 2
	AT91_REG	 SYS_SMC1_CTRL2; 	//  Control Register for CS 2
	AT91_REG	 SYS_SMC1_SETUP3; 	//  Setup Register for CS 3
	AT91_REG	 SYS_SMC1_PULSE3; 	//  Pulse Register for CS 3
	AT91_REG	 SYS_SMC1_CYCLE3; 	//  Cycle Register for CS 3
	AT91_REG	 SYS_SMC1_CTRL3; 	//  Control Register for CS 3
	AT91_REG	 SYS_SMC1_SETUP4; 	//  Setup Register for CS 4
	AT91_REG	 SYS_SMC1_PULSE4; 	//  Pulse Register for CS 4
	AT91_REG	 SYS_SMC1_CYCLE4; 	//  Cycle Register for CS 4
	AT91_REG	 SYS_SMC1_CTRL4; 	//  Control Register for CS 4
	AT91_REG	 SYS_SMC1_SETUP5; 	//  Setup Register for CS 5
	AT91_REG	 SYS_SMC1_PULSE5; 	//  Pulse Register for CS 5
	AT91_REG	 SYS_SMC1_CYCLE5; 	//  Cycle Register for CS 5
	AT91_REG	 SYS_SMC1_CTRL5; 	//  Control Register for CS 5
	AT91_REG	 SYS_SMC1_SETUP6; 	//  Setup Register for CS 6
	AT91_REG	 SYS_SMC1_PULSE6; 	//  Pulse Register for CS 6
	AT91_REG	 SYS_SMC1_CYCLE6; 	//  Cycle Register for CS 6
	AT91_REG	 SYS_SMC1_CTRL6; 	//  Control Register for CS 6
	AT91_REG	 SYS_SMC1_SETUP7; 	//  Setup Register for CS 7
	AT91_REG	 SYS_SMC1_PULSE7; 	//  Pulse Register for CS 7
	AT91_REG	 SYS_SMC1_CYCLE7; 	//  Cycle Register for CS 7
	AT91_REG	 SYS_SMC1_CTRL7; 	//  Control Register for CS 7
	AT91_REG	 Reserved5[96]; 	// 
	AT91_REG	 SYS_MATRIX_MCFG0; 	//  Master Configuration Register 0 
	AT91_REG	 SYS_MATRIX_MCFG1; 	//  Master Configuration Register 1 
	AT91_REG	 SYS_MATRIX_MCFG2; 	//  Master Configuration Register 2 
	AT91_REG	 SYS_MATRIX_MCFG3; 	//  Master Configuration Register 3 
	AT91_REG	 SYS_MATRIX_MCFG4; 	//  Master Configuration Register 4 
	AT91_REG	 SYS_MATRIX_MCFG5; 	//  Master Configuration Register 5 
	AT91_REG	 SYS_MATRIX_MCFG6; 	//  Master Configuration Register 6 
	AT91_REG	 SYS_MATRIX_MCFG7; 	//  Master Configuration Register 7 
	AT91_REG	 SYS_MATRIX_MCFG8; 	//  Master Configuration Register 8 
	AT91_REG	 Reserved6[7]; 	// 
	AT91_REG	 SYS_MATRIX_SCFG0; 	//  Slave Configuration Register 0
	AT91_REG	 SYS_MATRIX_SCFG1; 	//  Slave Configuration Register 1
	AT91_REG	 SYS_MATRIX_SCFG2; 	//  Slave Configuration Register 2
	AT91_REG	 SYS_MATRIX_SCFG3; 	//  Slave Configuration Register 3
	AT91_REG	 SYS_MATRIX_SCFG4; 	//  Slave Configuration Register 4
	AT91_REG	 SYS_MATRIX_SCFG5; 	//  Slave Configuration Register 5
	AT91_REG	 SYS_MATRIX_SCFG6; 	//  Slave Configuration Register 6
	AT91_REG	 SYS_MATRIX_SCFG7; 	//  Slave Configuration Register 7
	AT91_REG	 Reserved7[8]; 	// 
	AT91_REG	 SYS_MATRIX_PRAS0; 	//  PRAS0
	AT91_REG	 SYS_MATRIX_PRBS0; 	//  PRBS0
	AT91_REG	 SYS_MATRIX_PRAS1; 	//  PRAS1
	AT91_REG	 SYS_MATRIX_PRBS1; 	//  PRBS1
	AT91_REG	 SYS_MATRIX_PRAS2; 	//  PRAS2
	AT91_REG	 SYS_MATRIX_PRBS2; 	//  PRBS2
	AT91_REG	 SYS_MATRIX_PRAS3; 	//  PRAS3
	AT91_REG	 SYS_MATRIX_PRBS3; 	//  PRBS3
	AT91_REG	 SYS_MATRIX_PRAS4; 	//  PRAS4
	AT91_REG	 SYS_MATRIX_PRBS4; 	//  PRBS4
	AT91_REG	 SYS_MATRIX_PRAS5; 	//  PRAS5
	AT91_REG	 SYS_MATRIX_PRBS5; 	//  PRBS5
	AT91_REG	 SYS_MATRIX_PRAS6; 	//  PRAS6
	AT91_REG	 SYS_MATRIX_PRBS6; 	//  PRBS6
	AT91_REG	 SYS_MATRIX_PRAS7; 	//  PRAS7
	AT91_REG	 SYS_MATRIX_PRBS7; 	//  PRBS7
	AT91_REG	 Reserved8[16]; 	// 
	AT91_REG	 SYS_MATRIX_MRCR; 	//  Master Remp Control Register 
	AT91_REG	 Reserved9[63]; 	// 
	AT91_REG	 SYS_DBGU_CR; 	// Control Register
	AT91_REG	 SYS_DBGU_MR; 	// Mode Register
	AT91_REG	 SYS_DBGU_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_DBGU_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_DBGU_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_DBGU_CSR; 	// Channel Status Register
	AT91_REG	 SYS_DBGU_RHR; 	// Receiver Holding Register
	AT91_REG	 SYS_DBGU_THR; 	// Transmitter Holding Register
	AT91_REG	 SYS_DBGU_BRGR; 	// Baud Rate Generator Register
	AT91_REG	 Reserved10[7]; 	// 
	AT91_REG	 SYS_DBGU_CIDR; 	// Chip ID Register
	AT91_REG	 SYS_DBGU_EXID; 	// Chip ID Extension Register
	AT91_REG	 SYS_DBGU_FNTR; 	// Force NTRST Register
	AT91_REG	 Reserved11[45]; 	// 
	AT91_REG	 SYS_DBGU_RPR; 	// Receive Pointer Register
	AT91_REG	 SYS_DBGU_RCR; 	// Receive Counter Register
	AT91_REG	 SYS_DBGU_TPR; 	// Transmit Pointer Register
	AT91_REG	 SYS_DBGU_TCR; 	// Transmit Counter Register
	AT91_REG	 SYS_DBGU_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 SYS_DBGU_RNCR; 	// Receive Next Counter Register
	AT91_REG	 SYS_DBGU_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 SYS_DBGU_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 SYS_DBGU_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 SYS_DBGU_PTSR; 	// PDC Transfer Status Register
	AT91_REG	 Reserved12[54]; 	// 
	AT91_REG	 SYS_AIC_SMR[32]; 	// Source Mode Register
	AT91_REG	 SYS_AIC_SVR[32]; 	// Source Vector Register
	AT91_REG	 SYS_AIC_IVR; 	// IRQ Vector Register
	AT91_REG	 SYS_AIC_FVR; 	// FIQ Vector Register
	AT91_REG	 SYS_AIC_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_AIC_IPR; 	// Interrupt Pending Register
	AT91_REG	 SYS_AIC_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_AIC_CISR; 	// Core Interrupt Status Register
	AT91_REG	 Reserved13[2]; 	// 
	AT91_REG	 SYS_AIC_IECR; 	// Interrupt Enable Command Register
	AT91_REG	 SYS_AIC_IDCR; 	// Interrupt Disable Command Register
	AT91_REG	 SYS_AIC_ICCR; 	// Interrupt Clear Command Register
	AT91_REG	 SYS_AIC_ISCR; 	// Interrupt Set Command Register
	AT91_REG	 SYS_AIC_EOICR; 	// End of Interrupt Command Register
	AT91_REG	 SYS_AIC_SPU; 	// Spurious Vector Register
	AT91_REG	 SYS_AIC_DCR; 	// Debug Control Register (Protect)
	AT91_REG	 Reserved14[1]; 	// 
	AT91_REG	 SYS_AIC_FFER; 	// Fast Forcing Enable Register
	AT91_REG	 SYS_AIC_FFDR; 	// Fast Forcing Disable Register
	AT91_REG	 SYS_AIC_FFSR; 	// Fast Forcing Status Register
	AT91_REG	 Reserved15[45]; 	// 
	AT91_REG	 SYS_PIOA_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOA_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOA_PSR; 	// PIO Status Register
	AT91_REG	 Reserved16[1]; 	// 
	AT91_REG	 SYS_PIOA_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOA_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOA_OSR; 	// Output Status Register
	AT91_REG	 Reserved17[1]; 	// 
	AT91_REG	 SYS_PIOA_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOA_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOA_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved18[1]; 	// 
	AT91_REG	 SYS_PIOA_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOA_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOA_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOA_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOA_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOA_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOA_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOA_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOA_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOA_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOA_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved19[1]; 	// 
	AT91_REG	 SYS_PIOA_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOA_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOA_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved20[1]; 	// 
	AT91_REG	 SYS_PIOA_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOA_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOA_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved21[9]; 	// 
	AT91_REG	 SYS_PIOA_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOA_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOA_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved22[85]; 	// 
	AT91_REG	 SYS_PIOB_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOB_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOB_PSR; 	// PIO Status Register
	AT91_REG	 Reserved23[1]; 	// 
	AT91_REG	 SYS_PIOB_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOB_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOB_OSR; 	// Output Status Register
	AT91_REG	 Reserved24[1]; 	// 
	AT91_REG	 SYS_PIOB_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOB_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOB_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved25[1]; 	// 
	AT91_REG	 SYS_PIOB_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOB_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOB_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOB_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOB_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOB_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOB_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOB_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOB_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOB_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOB_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved26[1]; 	// 
	AT91_REG	 SYS_PIOB_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOB_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOB_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved27[1]; 	// 
	AT91_REG	 SYS_PIOB_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOB_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOB_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved28[9]; 	// 
	AT91_REG	 SYS_PIOB_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOB_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOB_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved29[85]; 	// 
	AT91_REG	 SYS_PIOC_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOC_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOC_PSR; 	// PIO Status Register
	AT91_REG	 Reserved30[1]; 	// 
	AT91_REG	 SYS_PIOC_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOC_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOC_OSR; 	// Output Status Register
	AT91_REG	 Reserved31[1]; 	// 
	AT91_REG	 SYS_PIOC_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOC_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOC_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved32[1]; 	// 
	AT91_REG	 SYS_PIOC_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOC_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOC_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOC_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOC_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOC_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOC_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOC_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOC_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOC_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOC_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved33[1]; 	// 
	AT91_REG	 SYS_PIOC_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOC_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOC_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved34[1]; 	// 
	AT91_REG	 SYS_PIOC_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOC_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOC_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved35[9]; 	// 
	AT91_REG	 SYS_PIOC_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOC_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOC_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved36[85]; 	// 
	AT91_REG	 SYS_PIOD_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOD_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOD_PSR; 	// PIO Status Register
	AT91_REG	 Reserved37[1]; 	// 
	AT91_REG	 SYS_PIOD_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOD_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOD_OSR; 	// Output Status Register
	AT91_REG	 Reserved38[1]; 	// 
	AT91_REG	 SYS_PIOD_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOD_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOD_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved39[1]; 	// 
	AT91_REG	 SYS_PIOD_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOD_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOD_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOD_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOD_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOD_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOD_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOD_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOD_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOD_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOD_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved40[1]; 	// 
	AT91_REG	 SYS_PIOD_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOD_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOD_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved41[1]; 	// 
	AT91_REG	 SYS_PIOD_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOD_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOD_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved42[9]; 	// 
	AT91_REG	 SYS_PIOD_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOD_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOD_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved43[85]; 	// 
	AT91_REG	 SYS_PIOE_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOE_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOE_PSR; 	// PIO Status Register
	AT91_REG	 Reserved44[1]; 	// 
	AT91_REG	 SYS_PIOE_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOE_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOE_OSR; 	// Output Status Register
	AT91_REG	 Reserved45[1]; 	// 
	AT91_REG	 SYS_PIOE_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOE_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOE_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved46[1]; 	// 
	AT91_REG	 SYS_PIOE_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOE_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOE_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOE_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOE_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOE_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOE_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOE_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOE_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOE_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOE_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved47[1]; 	// 
	AT91_REG	 SYS_PIOE_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOE_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOE_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved48[1]; 	// 
	AT91_REG	 SYS_PIOE_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOE_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOE_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved49[9]; 	// 
	AT91_REG	 SYS_PIOE_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOE_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOE_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved50[85]; 	// 
	AT91_REG	 SYS_PMC_SCER; 	// System Clock Enable Register
	AT91_REG	 SYS_PMC_SCDR; 	// System Clock Disable Register
	AT91_REG	 SYS_PMC_SCSR; 	// System Clock Status Register
	AT91_REG	 Reserved51[1]; 	// 
	AT91_REG	 SYS_PMC_PCER; 	// Peripheral Clock Enable Register
	AT91_REG	 SYS_PMC_PCDR; 	// Peripheral Clock Disable Register
	AT91_REG	 SYS_PMC_PCSR; 	// Peripheral Clock Status Register
	AT91_REG	 Reserved52[1]; 	// 
	AT91_REG	 SYS_PMC_MOR; 	// Main Oscillator Register
	AT91_REG	 SYS_PMC_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 SYS_PMC_PLLAR; 	// PLL A Register
	AT91_REG	 SYS_PMC_PLLBR; 	// PLL B Register
	AT91_REG	 SYS_PMC_MCKR; 	// Master Clock Register
	AT91_REG	 Reserved53[3]; 	// 
	AT91_REG	 SYS_PMC_PCKR[8]; 	// Programmable Clock Register
	AT91_REG	 SYS_PMC_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PMC_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PMC_SR; 	// Status Register
	AT91_REG	 SYS_PMC_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved54[36]; 	// 
	AT91_REG	 SYS_RSTC_RCR; 	// Reset Control Register
	AT91_REG	 SYS_RSTC_RSR; 	// Reset Status Register
	AT91_REG	 SYS_RSTC_RMR; 	// Reset Mode Register
	AT91_REG	 Reserved55[1]; 	// 
	AT91_REG	 SYS_SHDWC_SHCR; 	// Shut Down Control Register
	AT91_REG	 SYS_SHDWC_SHMR; 	// Shut Down Mode Register
	AT91_REG	 SYS_SHDWC_SHSR; 	// Shut Down Status Register
	AT91_REG	 Reserved56[1]; 	// 
	AT91_REG	 SYS_RTTC0_RTMR; 	// Real-time Mode Register
	AT91_REG	 SYS_RTTC0_RTAR; 	// Real-time Alarm Register
	AT91_REG	 SYS_RTTC0_RTVR; 	// Real-time Value Register
	AT91_REG	 SYS_RTTC0_RTSR; 	// Real-time Status Register
	AT91_REG	 SYS_PITC_PIMR; 	// Period Interval Mode Register
	AT91_REG	 SYS_PITC_PISR; 	// Period Interval Status Register
	AT91_REG	 SYS_PITC_PIVR; 	// Period Interval Value Register
	AT91_REG	 SYS_PITC_PIIR; 	// Period Interval Image Register
	AT91_REG	 SYS_WDTC_WDCR; 	// Watchdog Control Register
	AT91_REG	 SYS_WDTC_WDMR; 	// Watchdog Mode Register
	AT91_REG	 SYS_WDTC_WDSR; 	// Watchdog Status Register
	AT91_REG	 Reserved57[1]; 	// 
	AT91_REG	 SYS_RTTC1_RTMR; 	// Real-time Mode Register
	AT91_REG	 SYS_RTTC1_RTAR; 	// Real-time Alarm Register
	AT91_REG	 SYS_RTTC1_RTVR; 	// Real-time Value Register
	AT91_REG	 SYS_RTTC1_RTSR; 	// Real-time Status Register
	AT91_REG	 SYS_GPBR[20]; 	// General Purpose Register
	AT91_REG	 Reserved58[19]; 	// 
	AT91_REG	 SYS_RSTC_VER; 	// Version Register
} AT91S_SYS, *AT91PS_SYS;
#else
#define ECC0            (AT91_CAST(AT91_REG *) 	0x00000000) // (ECC0) ECC 0
#define ECC1            (AT91_CAST(AT91_REG *) 	0x00000600) // (ECC1) ECC 0
#define GPBR            (AT91_CAST(AT91_REG *) 	0x00001D60) // (GPBR) General Purpose Register

#endif
// -------- GPBR : (SYS Offset: 0x1d60) GPBR General Purpose Register -------- 
#define AT91C_GPBR_GPRV       (0x0 <<  0) // (SYS) General Purpose Register Value

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR External Bus Interface 0
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_EBI0 {
	AT91_REG	 EBI0_DUMMY; 	// Dummy register - Do not use
} AT91S_EBI0, *AT91PS_EBI0;
#else
#define EBI0_DUMMY      (AT91_CAST(AT91_REG *) 	0x00000000) // (EBI0_DUMMY) Dummy register - Do not use

#endif

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR SDRAM Controller Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_SDRAMC {
	AT91_REG	 SDRAMC_MR; 	// SDRAM Controller Mode Register
	AT91_REG	 SDRAMC_TR; 	// SDRAM Controller Refresh Timer Register
	AT91_REG	 SDRAMC_CR; 	// SDRAM Controller Configuration Register
	AT91_REG	 SDRAMC_HSR; 	// SDRAM Controller High Speed Register
	AT91_REG	 SDRAMC_LPR; 	// SDRAM Controller Low Power Register
	AT91_REG	 SDRAMC_IER; 	// SDRAM Controller Interrupt Enable Register
	AT91_REG	 SDRAMC_IDR; 	// SDRAM Controller Interrupt Disable Register
	AT91_REG	 SDRAMC_IMR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SDRAMC_ISR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SDRAMC_MDR; 	// SDRAM Memory Device Register
} AT91S_SDRAMC, *AT91PS_SDRAMC;
#else
#define SDRAMC_MR       (AT91_CAST(AT91_REG *) 	0x00000000) // (SDRAMC_MR) SDRAM Controller Mode Register
#define SDRAMC_TR       (AT91_CAST(AT91_REG *) 	0x00000004) // (SDRAMC_TR) SDRAM Controller Refresh Timer Register
#define SDRAMC_CR       (AT91_CAST(AT91_REG *) 	0x00000008) // (SDRAMC_CR) SDRAM Controller Configuration Register
#define SDRAMC_HSR      (AT91_CAST(AT91_REG *) 	0x0000000C) // (SDRAMC_HSR) SDRAM Controller High Speed Register
#define SDRAMC_LPR      (AT91_CAST(AT91_REG *) 	0x00000010) // (SDRAMC_LPR) SDRAM Controller Low Power Register
#define SDRAMC_IER      (AT91_CAST(AT91_REG *) 	0x00000014) // (SDRAMC_IER) SDRAM Controller Interrupt Enable Register
#define SDRAMC_IDR      (AT91_CAST(AT91_REG *) 	0x00000018) // (SDRAMC_IDR) SDRAM Controller Interrupt Disable Register
#define SDRAMC_IMR      (AT91_CAST(AT91_REG *) 	0x0000001C) // (SDRAMC_IMR) SDRAM Controller Interrupt Mask Register
#define SDRAMC_ISR      (AT91_CAST(AT91_REG *) 	0x00000020) // (SDRAMC_ISR) SDRAM Controller Interrupt Mask Register
#define SDRAMC_MDR      (AT91_CAST(AT91_REG *) 	0x00000024) // (SDRAMC_MDR) SDRAM Memory Device Register

#endif
// -------- SDRAMC_MR : (SDRAMC Offset: 0x0) SDRAM Controller Mode Register -------- 
#define AT91C_SDRAMC_MODE     (0xF <<  0) // (SDRAMC) Mode
#define 	AT91C_SDRAMC_MODE_NORMAL_CMD           (0x0) // (SDRAMC) Normal Mode
#define 	AT91C_SDRAMC_MODE_NOP_CMD              (0x1) // (SDRAMC) Issue a NOP Command at every access
#define 	AT91C_SDRAMC_MODE_PRCGALL_CMD          (0x2) // (SDRAMC) Issue a All Banks Precharge Command at every access
#define 	AT91C_SDRAMC_MODE_LMR_CMD              (0x3) // (SDRAMC) Issue a Load Mode Register at every access
#define 	AT91C_SDRAMC_MODE_RFSH_CMD             (0x4) // (SDRAMC) Issue a Refresh
#define 	AT91C_SDRAMC_MODE_EXT_LMR_CMD          (0x5) // (SDRAMC) Issue an Extended Load Mode Register
#define 	AT91C_SDRAMC_MODE_DEEP_CMD             (0x6) // (SDRAMC) Enter Deep Power Mode
// -------- SDRAMC_TR : (SDRAMC Offset: 0x4) SDRAMC Refresh Timer Register -------- 
#define AT91C_SDRAMC_COUNT    (0xFFF <<  0) // (SDRAMC) Refresh Counter
// -------- SDRAMC_CR : (SDRAMC Offset: 0x8) SDRAM Configuration Register -------- 
#define AT91C_SDRAMC_NC       (0x3 <<  0) // (SDRAMC) Number of Column Bits
#define 	AT91C_SDRAMC_NC_8                    (0x0) // (SDRAMC) 8 Bits
#define 	AT91C_SDRAMC_NC_9                    (0x1) // (SDRAMC) 9 Bits
#define 	AT91C_SDRAMC_NC_10                   (0x2) // (SDRAMC) 10 Bits
#define 	AT91C_SDRAMC_NC_11                   (0x3) // (SDRAMC) 11 Bits
#define AT91C_SDRAMC_NR       (0x3 <<  2) // (SDRAMC) Number of Row Bits
#define 	AT91C_SDRAMC_NR_11                   (0x0 <<  2) // (SDRAMC) 11 Bits
#define 	AT91C_SDRAMC_NR_12                   (0x1 <<  2) // (SDRAMC) 12 Bits
#define 	AT91C_SDRAMC_NR_13                   (0x2 <<  2) // (SDRAMC) 13 Bits
#define AT91C_SDRAMC_NB       (0x1 <<  4) // (SDRAMC) Number of Banks
#define 	AT91C_SDRAMC_NB_2_BANKS              (0x0 <<  4) // (SDRAMC) 2 banks
#define 	AT91C_SDRAMC_NB_4_BANKS              (0x1 <<  4) // (SDRAMC) 4 banks
#define AT91C_SDRAMC_CAS      (0x3 <<  5) // (SDRAMC) CAS Latency
#define 	AT91C_SDRAMC_CAS_2                    (0x2 <<  5) // (SDRAMC) 2 cycles
#define 	AT91C_SDRAMC_CAS_3                    (0x3 <<  5) // (SDRAMC) 3 cycles
#define AT91C_SDRAMC_DBW      (0x1 <<  7) // (SDRAMC) Data Bus Width
#define 	AT91C_SDRAMC_DBW_32_BITS              (0x0 <<  7) // (SDRAMC) 32 Bits datas bus
#define 	AT91C_SDRAMC_DBW_16_BITS              (0x1 <<  7) // (SDRAMC) 16 Bits datas bus
#define AT91C_SDRAMC_TWR      (0xF <<  8) // (SDRAMC) Number of Write Recovery Time Cycles
#define 	AT91C_SDRAMC_TWR_0                    (0x0 <<  8) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TWR_1                    (0x1 <<  8) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TWR_2                    (0x2 <<  8) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TWR_3                    (0x3 <<  8) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TWR_4                    (0x4 <<  8) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TWR_5                    (0x5 <<  8) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TWR_6                    (0x6 <<  8) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TWR_7                    (0x7 <<  8) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TWR_8                    (0x8 <<  8) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TWR_9                    (0x9 <<  8) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TWR_10                   (0xA <<  8) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TWR_11                   (0xB <<  8) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TWR_12                   (0xC <<  8) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TWR_13                   (0xD <<  8) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TWR_14                   (0xE <<  8) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TWR_15                   (0xF <<  8) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRC      (0xF << 12) // (SDRAMC) Number of RAS Cycle Time Cycles
#define 	AT91C_SDRAMC_TRC_0                    (0x0 << 12) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRC_1                    (0x1 << 12) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRC_2                    (0x2 << 12) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRC_3                    (0x3 << 12) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRC_4                    (0x4 << 12) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRC_5                    (0x5 << 12) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRC_6                    (0x6 << 12) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRC_7                    (0x7 << 12) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRC_8                    (0x8 << 12) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRC_9                    (0x9 << 12) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRC_10                   (0xA << 12) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRC_11                   (0xB << 12) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRC_12                   (0xC << 12) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRC_13                   (0xD << 12) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRC_14                   (0xE << 12) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRC_15                   (0xF << 12) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRP      (0xF << 16) // (SDRAMC) Number of RAS Precharge Time Cycles
#define 	AT91C_SDRAMC_TRP_0                    (0x0 << 16) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRP_1                    (0x1 << 16) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRP_2                    (0x2 << 16) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRP_3                    (0x3 << 16) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRP_4                    (0x4 << 16) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRP_5                    (0x5 << 16) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRP_6                    (0x6 << 16) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRP_7                    (0x7 << 16) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRP_8                    (0x8 << 16) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRP_9                    (0x9 << 16) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRP_10                   (0xA << 16) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRP_11                   (0xB << 16) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRP_12                   (0xC << 16) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRP_13                   (0xD << 16) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRP_14                   (0xE << 16) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRP_15                   (0xF << 16) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRCD     (0xF << 20) // (SDRAMC) Number of RAS to CAS Delay Cycles
#define 	AT91C_SDRAMC_TRCD_0                    (0x0 << 20) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRCD_1                    (0x1 << 20) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRCD_2                    (0x2 << 20) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRCD_3                    (0x3 << 20) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRCD_4                    (0x4 << 20) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRCD_5                    (0x5 << 20) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRCD_6                    (0x6 << 20) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRCD_7                    (0x7 << 20) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRCD_8                    (0x8 << 20) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRCD_9                    (0x9 << 20) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRCD_10                   (0xA << 20) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRCD_11                   (0xB << 20) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRCD_12                   (0xC << 20) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRCD_13                   (0xD << 20) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRCD_14                   (0xE << 20) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRCD_15                   (0xF << 20) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRAS     (0xF << 24) // (SDRAMC) Number of RAS Active Time Cycles
#define 	AT91C_SDRAMC_TRAS_0                    (0x0 << 24) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRAS_1                    (0x1 << 24) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRAS_2                    (0x2 << 24) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRAS_3                    (0x3 << 24) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRAS_4                    (0x4 << 24) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRAS_5                    (0x5 << 24) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRAS_6                    (0x6 << 24) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRAS_7                    (0x7 << 24) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRAS_8                    (0x8 << 24) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRAS_9                    (0x9 << 24) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRAS_10                   (0xA << 24) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRAS_11                   (0xB << 24) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRAS_12                   (0xC << 24) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRAS_13                   (0xD << 24) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRAS_14                   (0xE << 24) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRAS_15                   (0xF << 24) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TXSR     (0xF << 28) // (SDRAMC) Number of Command Recovery Time Cycles
#define 	AT91C_SDRAMC_TXSR_0                    (0x0 << 28) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TXSR_1                    (0x1 << 28) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TXSR_2                    (0x2 << 28) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TXSR_3                    (0x3 << 28) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TXSR_4                    (0x4 << 28) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TXSR_5                    (0x5 << 28) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TXSR_6                    (0x6 << 28) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TXSR_7                    (0x7 << 28) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TXSR_8                    (0x8 << 28) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TXSR_9                    (0x9 << 28) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TXSR_10                   (0xA << 28) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TXSR_11                   (0xB << 28) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TXSR_12                   (0xC << 28) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TXSR_13                   (0xD << 28) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TXSR_14                   (0xE << 28) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TXSR_15                   (0xF << 28) // (SDRAMC) Value : 15
// -------- SDRAMC_HSR : (SDRAMC Offset: 0xc) SDRAM Controller High Speed Register -------- 
#define AT91C_SDRAMC_DA       (0x1 <<  0) // (SDRAMC) Decode Cycle Enable Bit
#define 	AT91C_SDRAMC_DA_DISABLE              (0x0) // (SDRAMC) Disable Decode Cycle
#define 	AT91C_SDRAMC_DA_ENABLE               (0x1) // (SDRAMC) Enable Decode Cycle
// -------- SDRAMC_LPR : (SDRAMC Offset: 0x10) SDRAM Controller Low-power Register -------- 
#define AT91C_SDRAMC_LPCB     (0x3 <<  0) // (SDRAMC) Low-power Configurations
#define 	AT91C_SDRAMC_LPCB_DISABLE              (0x0) // (SDRAMC) Disable Low Power Features
#define 	AT91C_SDRAMC_LPCB_SELF_REFRESH         (0x1) // (SDRAMC) Enable SELF_REFRESH
#define 	AT91C_SDRAMC_LPCB_POWER_DOWN           (0x2) // (SDRAMC) Enable POWER_DOWN
#define 	AT91C_SDRAMC_LPCB_DEEP_POWER_DOWN      (0x3) // (SDRAMC) Enable DEEP_POWER_DOWN
#define AT91C_SDRAMC_PASR     (0x7 <<  4) // (SDRAMC) Partial Array Self Refresh (only for Low Power SDRAM)
#define AT91C_SDRAMC_TCSR     (0x3 <<  8) // (SDRAMC) Temperature Compensated Self Refresh (only for Low Power SDRAM)
#define AT91C_SDRAMC_DS       (0x3 << 10) // (SDRAMC) Drive Strenght (only for Low Power SDRAM)
#define AT91C_SDRAMC_TIMEOUT  (0x3 << 12) // (SDRAMC) Time to define when Low Power Mode is enabled
#define 	AT91C_SDRAMC_TIMEOUT_0_CLK_CYCLES         (0x0 << 12) // (SDRAMC) Activate SDRAM Low Power Mode Immediately
#define 	AT91C_SDRAMC_TIMEOUT_64_CLK_CYCLES        (0x1 << 12) // (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer
#define 	AT91C_SDRAMC_TIMEOUT_128_CLK_CYCLES       (0x2 << 12) // (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer
// -------- SDRAMC_IER : (SDRAMC Offset: 0x14) SDRAM Controller Interrupt Enable Register -------- 
#define AT91C_SDRAMC_RES      (0x1 <<  0) // (SDRAMC) Refresh Error Status
// -------- SDRAMC_IDR : (SDRAMC Offset: 0x18) SDRAM Controller Interrupt Disable Register -------- 
// -------- SDRAMC_IMR : (SDRAMC Offset: 0x1c) SDRAM Controller Interrupt Mask Register -------- 
// -------- SDRAMC_ISR : (SDRAMC Offset: 0x20) SDRAM Controller Interrupt Status Register -------- 
// -------- SDRAMC_MDR : (SDRAMC Offset: 0x24) SDRAM Controller Memory Device Register -------- 
#define AT91C_SDRAMC_MD       (0x3 <<  0) // (SDRAMC) Memory Device Type
#define 	AT91C_SDRAMC_MD_SDRAM                (0x0) // (SDRAMC) SDRAM Mode
#define 	AT91C_SDRAMC_MD_LOW_POWER_SDRAM      (0x1) // (SDRAMC) SDRAM Low Power Mode

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Static Memory Controller Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_SMC {
	AT91_REG	 SMC_SETUP0; 	//  Setup Register for CS 0
	AT91_REG	 SMC_PULSE0; 	//  Pulse Register for CS 0
	AT91_REG	 SMC_CYCLE0; 	//  Cycle Register for CS 0
	AT91_REG	 SMC_CTRL0; 	//  Control Register for CS 0
	AT91_REG	 SMC_SETUP1; 	//  Setup Register for CS 1
	AT91_REG	 SMC_PULSE1; 	//  Pulse Register for CS 1
	AT91_REG	 SMC_CYCLE1; 	//  Cycle Register for CS 1
	AT91_REG	 SMC_CTRL1; 	//  Control Register for CS 1
	AT91_REG	 SMC_SETUP2; 	//  Setup Register for CS 2
	AT91_REG	 SMC_PULSE2; 	//  Pulse Register for CS 2
	AT91_REG	 SMC_CYCLE2; 	//  Cycle Register for CS 2
	AT91_REG	 SMC_CTRL2; 	//  Control Register for CS 2
	AT91_REG	 SMC_SETUP3; 	//  Setup Register for CS 3
	AT91_REG	 SMC_PULSE3; 	//  Pulse Register for CS 3
	AT91_REG	 SMC_CYCLE3; 	//  Cycle Register for CS 3
	AT91_REG	 SMC_CTRL3; 	//  Control Register for CS 3
	AT91_REG	 SMC_SETUP4; 	//  Setup Register for CS 4
	AT91_REG	 SMC_PULSE4; 	//  Pulse Register for CS 4
	AT91_REG	 SMC_CYCLE4; 	//  Cycle Register for CS 4
	AT91_REG	 SMC_CTRL4; 	//  Control Register for CS 4
	AT91_REG	 SMC_SETUP5; 	//  Setup Register for CS 5
	AT91_REG	 SMC_PULSE5; 	//  Pulse Register for CS 5
	AT91_REG	 SMC_CYCLE5; 	//  Cycle Register for CS 5
	AT91_REG	 SMC_CTRL5; 	//  Control Register for CS 5
	AT91_REG	 SMC_SETUP6; 	//  Setup Register for CS 6
	AT91_REG	 SMC_PULSE6; 	//  Pulse Register for CS 6
	AT91_REG	 SMC_CYCLE6; 	//  Cycle Register for CS 6
	AT91_REG	 SMC_CTRL6; 	//  Control Register for CS 6
	AT91_REG	 SMC_SETUP7; 	//  Setup Register for CS 7
	AT91_REG	 SMC_PULSE7; 	//  Pulse Register for CS 7
	AT91_REG	 SMC_CYCLE7; 	//  Cycle Register for CS 7
	AT91_REG	 SMC_CTRL7; 	//  Control Register for CS 7
} AT91S_SMC, *AT91PS_SMC;
#else
#define SETUP0          (AT91_CAST(AT91_REG *) 	0x00000000) // (SETUP0)  Setup Register for CS 0
#define PULSE0          (AT91_CAST(AT91_REG *) 	0x00000004) // (PULSE0)  Pulse Register for CS 0
#define CYCLE0          (AT91_CAST(AT91_REG *) 	0x00000008) // (CYCLE0)  Cycle Register for CS 0
#define CTRL0           (AT91_CAST(AT91_REG *) 	0x0000000C) // (CTRL0)  Control Register for CS 0
#define SETUP1          (AT91_CAST(AT91_REG *) 	0x00000010) // (SETUP1)  Setup Register for CS 1
#define PULSE1          (AT91_CAST(AT91_REG *) 	0x00000014) // (PULSE1)  Pulse Register for CS 1
#define CYCLE1          (AT91_CAST(AT91_REG *) 	0x00000018) // (CYCLE1)  Cycle Register for CS 1
#define CTRL1           (AT91_CAST(AT91_REG *) 	0x0000001C) // (CTRL1)  Control Register for CS 1
#define SETUP2          (AT91_CAST(AT91_REG *) 	0x00000020) // (SETUP2)  Setup Register for CS 2
#define PULSE2          (AT91_CAST(AT91_REG *) 	0x00000024) // (PULSE2)  Pulse Register for CS 2
#define CYCLE2          (AT91_CAST(AT91_REG *) 	0x00000028) // (CYCLE2)  Cycle Register for CS 2
#define CTRL2           (AT91_CAST(AT91_REG *) 	0x0000002C) // (CTRL2)  Control Register for CS 2
#define SETUP3          (AT91_CAST(AT91_REG *) 	0x00000030) // (SETUP3)  Setup Register for CS 3
#define PULSE3          (AT91_CAST(AT91_REG *) 	0x00000034) // (PULSE3)  Pulse Register for CS 3
#define CYCLE3          (AT91_CAST(AT91_REG *) 	0x00000038) // (CYCLE3)  Cycle Register for CS 3
#define CTRL3           (AT91_CAST(AT91_REG *) 	0x0000003C) // (CTRL3)  Control Register for CS 3
#define SETUP4          (AT91_CAST(AT91_REG *) 	0x00000040) // (SETUP4)  Setup Register for CS 4
#define PULSE4          (AT91_CAST(AT91_REG *) 	0x00000044) // (PULSE4)  Pulse Register for CS 4
#define CYCLE4          (AT91_CAST(AT91_REG *) 	0x00000048) // (CYCLE4)  Cycle Register for CS 4
#define CTRL4           (AT91_CAST(AT91_REG *) 	0x0000004C) // (CTRL4)  Control Register for CS 4
#define SETUP5          (AT91_CAST(AT91_REG *) 	0x00000050) // (SETUP5)  Setup Register for CS 5
#define PULSE5          (AT91_CAST(AT91_REG *) 	0x00000054) // (PULSE5)  Pulse Register for CS 5
#define CYCLE5          (AT91_CAST(AT91_REG *) 	0x00000058) // (CYCLE5)  Cycle Register for CS 5
#define CTRL5           (AT91_CAST(AT91_REG *) 	0x0000005C) // (CTRL5)  Control Register for CS 5
#define SETUP6          (AT91_CAST(AT91_REG *) 	0x00000060) // (SETUP6)  Setup Register for CS 6
#define PULSE6          (AT91_CAST(AT91_REG *) 	0x00000064) // (PULSE6)  Pulse Register for CS 6
#define CYCLE6          (AT91_CAST(AT91_REG *) 	0x00000068) // (CYCLE6)  Cycle Register for CS 6
#define CTRL6           (AT91_CAST(AT91_REG *) 	0x0000006C) // (CTRL6)  Control Register for CS 6
#define SETUP7          (AT91_CAST(AT91_REG *) 	0x00000070) // (SETUP7)  Setup Register for CS 7
#define PULSE7          (AT91_CAST(AT91_REG *) 	0x00000074) // (PULSE7)  Pulse Register for CS 7
#define CYCLE7          (AT91_CAST(AT91_REG *) 	0x00000078) // (CYCLE7)  Cycle Register for CS 7
#define CTRL7           (AT91_CAST(AT91_REG *) 	0x0000007C) // (CTRL7)  Control Register for CS 7

#endif
// -------- SMC_SETUP : (SMC Offset: 0x0) Setup Register for CS x -------- 
#define AT91C_SMC_NWESETUP    (0x3F <<  0) // (SMC) NWE Setup Length
#define AT91C_SMC_NCSSETUPWR  (0x3F <<  8) // (SMC) NCS Setup Length in WRite Access
#define AT91C_SMC_NRDSETUP    (0x3F << 16) // (SMC) NRD Setup Length
#define AT91C_SMC_NCSSETUPRD  (0x3F << 24) // (SMC) NCS Setup Length in ReaD Access
// -------- SMC_PULSE : (SMC Offset: 0x4) Pulse Register for CS x -------- 
#define AT91C_SMC_NWEPULSE    (0x7F <<  0) // (SMC) NWE Pulse Length
#define AT91C_SMC_NCSPULSEWR  (0x7F <<  8) // (SMC) NCS Pulse Length in WRite Access
#define AT91C_SMC_NRDPULSE    (0x7F << 16) // (SMC) NRD Pulse Length
#define AT91C_SMC_NCSPULSERD  (0x7F << 24) // (SMC) NCS Pulse Length in ReaD Access
// -------- SMC_CYC : (SMC Offset: 0x8) Cycle Register for CS x -------- 
#define AT91C_SMC_NWECYCLE    (0x1FF <<  0) // (SMC) Total Write Cycle Length
#define AT91C_SMC_NRDCYCLE    (0x1FF << 16) // (SMC) Total Read Cycle Length
// -------- SMC_CTRL : (SMC Offset: 0xc) Control Register for CS x -------- 
#define AT91C_SMC_READMODE    (0x1 <<  0) // (SMC) Read Mode
#define AT91C_SMC_WRITEMODE   (0x1 <<  1) // (SMC) Write Mode
#define AT91C_SMC_NWAITM      (0x3 <<  4) // (SMC) NWAIT Mode
#define 	AT91C_SMC_NWAITM_NWAIT_DISABLE        (0x0 <<  4) // (SMC) External NWAIT disabled.
#define 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  (0x2 <<  4) // (SMC) External NWAIT enabled in frozen mode.
#define 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   (0x3 <<  4) // (SMC) External NWAIT enabled in ready mode.
#define AT91C_SMC_BAT         (0x1 <<  8) // (SMC) Byte Access Type
#define 	AT91C_SMC_BAT_BYTE_SELECT          (0x0 <<  8) // (SMC) Write controled by ncs, nbs0, nbs1, nbs2, nbs3. Read controled by ncs, nrd, nbs0, nbs1, nbs2, nbs3.
#define 	AT91C_SMC_BAT_BYTE_WRITE           (0x1 <<  8) // (SMC) Write controled by ncs, nwe0, nwe1, nwe2, nwe3. Read controled by ncs and nrd.
#define AT91C_SMC_DBW         (0x3 << 12) // (SMC) Data Bus Width
#define 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     (0x0 << 12) // (SMC) 8 bits.
#define 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   (0x1 << 12) // (SMC) 16 bits.
#define 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS (0x2 << 12) // (SMC) 32 bits.
#define AT91C_SMC_TDF         (0xF << 16) // (SMC) Data Float Time.
#define AT91C_SMC_TDFEN       (0x1 << 20) // (SMC) TDF Enabled.
#define AT91C_SMC_PMEN        (0x1 << 24) // (SMC) Page Mode Enabled.
#define AT91C_SMC_PS          (0x3 << 28) // (SMC) Page Size
#define 	AT91C_SMC_PS_SIZE_FOUR_BYTES      (0x0 << 28) // (SMC) 4 bytes.
#define 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     (0x1 << 28) // (SMC) 8 bytes.
#define 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   (0x2 << 28) // (SMC) 16 bytes.
#define 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES (0x3 << 28) // (SMC) 32 bytes.
// -------- SMC_SETUP : (SMC Offset: 0x10) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x14) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x18) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x1c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x20) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x24) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x28) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x2c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x30) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x34) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x38) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x3c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x40) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x44) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x48) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x4c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x50) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x54) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x58) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x5c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x60) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x64) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x68) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x6c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x70) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x74) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x78) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x7c) Control Register for CS x -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR External Bus Interface 1
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_EBI1 {
	AT91_REG	 EBI1_DUMMY; 	// Dummy register - Do not use
} AT91S_EBI1, *AT91PS_EBI1;
#else
#define EBI1_DUMMY      (AT91_CAST(AT91_REG *) 	0x00000000) // (EBI1_DUMMY) Dummy register - Do not use

#endif

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR AHB Matrix Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_MATRIX {
	AT91_REG	 MATRIX_MCFG0; 	//  Master Configuration Register 0 
	AT91_REG	 MATRIX_MCFG1; 	//  Master Configuration Register 1 
	AT91_REG	 MATRIX_MCFG2; 	//  Master Configuration Register 2 
	AT91_REG	 MATRIX_MCFG3; 	//  Master Configuration Register 3 
	AT91_REG	 MATRIX_MCFG4; 	//  Master Configuration Register 4 
	AT91_REG	 MATRIX_MCFG5; 	//  Master Configuration Register 5 
	AT91_REG	 MATRIX_MCFG6; 	//  Master Configuration Register 6 
	AT91_REG	 MATRIX_MCFG7; 	//  Master Configuration Register 7 
	AT91_REG	 MATRIX_MCFG8; 	//  Master Configuration Register 8 
	AT91_REG	 Reserved0[7]; 	// 
	AT91_REG	 MATRIX_SCFG0; 	//  Slave Configuration Register 0
	AT91_REG	 MATRIX_SCFG1; 	//  Slave Configuration Register 1
	AT91_REG	 MATRIX_SCFG2; 	//  Slave Configuration Register 2
	AT91_REG	 MATRIX_SCFG3; 	//  Slave Configuration Register 3
	AT91_REG	 MATRIX_SCFG4; 	//  Slave Configuration Register 4
	AT91_REG	 MATRIX_SCFG5; 	//  Slave Configuration Register 5
	AT91_REG	 MATRIX_SCFG6; 	//  Slave Configuration Register 6
	AT91_REG	 MATRIX_SCFG7; 	//  Slave Configuration Register 7
	AT91_REG	 Reserved1[8]; 	// 
	AT91_REG	 MATRIX_PRAS0; 	//  PRAS0
	AT91_REG	 MATRIX_PRBS0; 	//  PRBS0
	AT91_REG	 MATRIX_PRAS1; 	//  PRAS1
	AT91_REG	 MATRIX_PRBS1; 	//  PRBS1
	AT91_REG	 MATRIX_PRAS2; 	//  PRAS2
	AT91_REG	 MATRIX_PRBS2; 	//  PRBS2
	AT91_REG	 MATRIX_PRAS3; 	//  PRAS3
	AT91_REG	 MATRIX_PRBS3; 	//  PRBS3
	AT91_REG	 MATRIX_PRAS4; 	//  PRAS4
	AT91_REG	 MATRIX_PRBS4; 	//  PRBS4
	AT91_REG	 MATRIX_PRAS5; 	//  PRAS5
	AT91_REG	 MATRIX_PRBS5; 	//  PRBS5
	AT91_REG	 MATRIX_PRAS6; 	//  PRAS6
	AT91_REG	 MATRIX_PRBS6; 	//  PRBS6
	AT91_REG	 MATRIX_PRAS7; 	//  PRAS7
	AT91_REG	 MATRIX_PRBS7; 	//  PRBS7
	AT91_REG	 Reserved2[16]; 	// 
	AT91_REG	 MATRIX_MRCR; 	//  Master Remp Control Register 
} AT91S_MATRIX, *AT91PS_MATRIX;
#else
#define MATRIX_MCFG0    (AT91_CAST(AT91_REG *) 	0x00000000) // (MATRIX_MCFG0)  Master Configuration Register 0 
#define MATRIX_MCFG1    (AT91_CAST(AT91_REG *) 	0x00000004) // (MATRIX_MCFG1)  Master Configuration Register 1 
#define MATRIX_MCFG2    (AT91_CAST(AT91_REG *) 	0x00000008) // (MATRIX_MCFG2)  Master Configuration Register 2 
#define MATRIX_MCFG3    (AT91_CAST(AT91_REG *) 	0x0000000C) // (MATRIX_MCFG3)  Master Configuration Register 3 
#define MATRIX_MCFG4    (AT91_CAST(AT91_REG *) 	0x00000010) // (MATRIX_MCFG4)  Master Configuration Register 4 
#define MATRIX_MCFG5    (AT91_CAST(AT91_REG *) 	0x00000014) // (MATRIX_MCFG5)  Master Configuration Register 5 
#define MATRIX_MCFG6    (AT91_CAST(AT91_REG *) 	0x00000018) // (MATRIX_MCFG6)  Master Configuration Register 6 
#define MATRIX_MCFG7    (AT91_CAST(AT91_REG *) 	0x0000001C) // (MATRIX_MCFG7)  Master Configuration Register 7 
#define MATRIX_MCFG8    (AT91_CAST(AT91_REG *) 	0x00000020) // (MATRIX_MCFG8)  Master Configuration Register 8 
#define MATRIX_SCFG0    (AT91_CAST(AT91_REG *) 	0x00000040) // (MATRIX_SCFG0)  Slave Configuration Register 0
#define MATRIX_SCFG1    (AT91_CAST(AT91_REG *) 	0x00000044) // (MATRIX_SCFG1)  Slave Configuration Register 1
#define MATRIX_SCFG2    (AT91_CAST(AT91_REG *) 	0x00000048) // (MATRIX_SCFG2)  Slave Configuration Register 2
#define MATRIX_SCFG3    (AT91_CAST(AT91_REG *) 	0x0000004C) // (MATRIX_SCFG3)  Slave Configuration Register 3
#define MATRIX_SCFG4    (AT91_CAST(AT91_REG *) 	0x00000050) // (MATRIX_SCFG4)  Slave Configuration Register 4
#define MATRIX_SCFG5    (AT91_CAST(AT91_REG *) 	0x00000054) // (MATRIX_SCFG5)  Slave Configuration Register 5
#define MATRIX_SCFG6    (AT91_CAST(AT91_REG *) 	0x00000058) // (MATRIX_SCFG6)  Slave Configuration Register 6
#define MATRIX_SCFG7    (AT91_CAST(AT91_REG *) 	0x0000005C) // (MATRIX_SCFG7)  Slave Configuration Register 7
#define MATRIX_PRAS0    (AT91_CAST(AT91_REG *) 	0x00000080) // (MATRIX_PRAS0)  PRAS0
#define MATRIX_PRBS0    (AT91_CAST(AT91_REG *) 	0x00000084) // (MATRIX_PRBS0)  PRBS0
#define MATRIX_PRAS1    (AT91_CAST(AT91_REG *) 	0x00000088) // (MATRIX_PRAS1)  PRAS1
#define MATRIX_PRBS1    (AT91_CAST(AT91_REG *) 	0x0000008C) // (MATRIX_PRBS1)  PRBS1
#define MATRIX_PRAS2    (AT91_CAST(AT91_REG *) 	0x00000090) // (MATRIX_PRAS2)  PRAS2
#define MATRIX_PRBS2    (AT91_CAST(AT91_REG *) 	0x00000094) // (MATRIX_PRBS2)  PRBS2
#define MATRIX_PRAS3    (AT91_CAST(AT91_REG *) 	0x00000098) // (MATRIX_PRAS3)  PRAS3
#define MATRIX_PRBS3    (AT91_CAST(AT91_REG *) 	0x0000009C) // (MATRIX_PRBS3)  PRBS3
#define MATRIX_PRAS4    (AT91_CAST(AT91_REG *) 	0x000000A0) // (MATRIX_PRAS4)  PRAS4
#define MATRIX_PRBS4    (AT91_CAST(AT91_REG *) 	0x000000A4) // (MATRIX_PRBS4)  PRBS4
#define MATRIX_PRAS5    (AT91_CAST(AT91_REG *) 	0x000000A8) // (MATRIX_PRAS5)  PRAS5
#define MATRIX_PRBS5    (AT91_CAST(AT91_REG *) 	0x000000AC) // (MATRIX_PRBS5)  PRBS5
#define MATRIX_PRAS6    (AT91_CAST(AT91_REG *) 	0x000000B0) // (MATRIX_PRAS6)  PRAS6
#define MATRIX_PRBS6    (AT91_CAST(AT91_REG *) 	0x000000B4) // (MATRIX_PRBS6)  PRBS6
#define MATRIX_PRAS7    (AT91_CAST(AT91_REG *) 	0x000000B8) // (MATRIX_PRAS7)  PRAS7
#define MATRIX_PRBS7    (AT91_CAST(AT91_REG *) 	0x000000BC) // (MATRIX_PRBS7)  PRBS7
#define MATRIX_MRCR     (AT91_CAST(AT91_REG *) 	0x00000100) // (MATRIX_MRCR)  Master Remp Control Register 

#endif
// -------- MATRIX_MCFG0 : (MATRIX Offset: 0x0) Master Configuration Register rom -------- 
#define AT91C_MATRIX_ULBT     (0x7 <<  0) // (MATRIX) Undefined Length Burst Type
// -------- MATRIX_MCFG1 : (MATRIX Offset: 0x4) Master Configuration Register htcm -------- 
// -------- MATRIX_MCFG2 : (MATRIX Offset: 0x8) Master Configuration Register gps_tcm -------- 
// -------- MATRIX_MCFG3 : (MATRIX Offset: 0xc) Master Configuration Register hperiphs -------- 
// -------- MATRIX_MCFG4 : (MATRIX Offset: 0x10) Master Configuration Register ebi0 -------- 
// -------- MATRIX_MCFG5 : (MATRIX Offset: 0x14) Master Configuration Register ebi1 -------- 
// -------- MATRIX_MCFG6 : (MATRIX Offset: 0x18) Master Configuration Register bridge -------- 
// -------- MATRIX_MCFG7 : (MATRIX Offset: 0x1c) Master Configuration Register gps -------- 
// -------- MATRIX_MCFG8 : (MATRIX Offset: 0x20) Master Configuration Register gps -------- 
// -------- MATRIX_SCFG0 : (MATRIX Offset: 0x40) Slave Configuration Register 0 -------- 
#define AT91C_MATRIX_SLOT_CYCLE (0xFF <<  0) // (MATRIX) Maximum Number of Allowed Cycles for a Burst
#define AT91C_MATRIX_DEFMSTR_TYPE (0x3 << 16) // (MATRIX) Default Master Type
#define 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           (0x0 << 16) // (MATRIX) No Default Master. At the end of current slave access, if no other master request is pending, the slave is deconnected from all masters. This results in having a one cycle latency for the first transfer of a burst.
#define 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         (0x1 << 16) // (MATRIX) Last Default Master. At the end of current slave access, if no other master request is pending, the slave stay connected with the last master having accessed it. This results in not having the one cycle latency when the last master re-trying access on the slave.
#define 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        (0x2 << 16) // (MATRIX) Fixed Default Master. At the end of current slave access, if no other master request is pending, the slave connects with fixed which number is in FIXED_DEFMSTR field. This results in not having the one cycle latency when the fixed master re-trying access on the slave.
#define AT91C_MATRIX_FIXED_DEFMSTR0 (0x7 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I              (0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D              (0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_PDC                  (0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_LCDC                 (0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_2DGC                 (0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ISI                  (0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA                  (0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_EMAC                 (0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_USB                  (0x8 << 18) // (MATRIX) USB Master is Default Master
#define AT91C_MATRIX_ARBT     (0x3 << 24) // (MATRIX) Arbitration Type
// -------- MATRIX_SCFG1 : (MATRIX Offset: 0x44) Slave Configuration Register 1 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR1 (0x7 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926I              (0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926D              (0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_PDC                  (0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_LCDC                 (0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_2DGC                 (0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ISI                  (0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_DMA                  (0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_EMAC                 (0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_USB                  (0x8 << 18) // (MATRIX) USB Master is Default Master
// -------- MATRIX_SCFG2 : (MATRIX Offset: 0x48) Slave Configuration Register 2 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR2 (0x1 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926I              (0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926D              (0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_DMA                  (0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
// -------- MATRIX_SCFG3 : (MATRIX Offset: 0x4c) Slave Configuration Register 3 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR3 (0x7 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926I              (0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926D              (0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_PDC                  (0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_LCDC                 (0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_2DGC                 (0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ISI                  (0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_DMA                  (0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_EMAC                 (0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_USB                  (0x8 << 18) // (MATRIX) USB Master is Default Master
// -------- MATRIX_SCFG4 : (MATRIX Offset: 0x50) Slave Configuration Register 4 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR4 (0x3 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926I              (0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926D              (0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_DMA                  (0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
// -------- MATRIX_SCFG5 : (MATRIX Offset: 0x54) Slave Configuration Register 5 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR5 (0x3 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_ARM926I              (0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_ARM926D              (0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_PDC                  (0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_LCDC                 (0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_2DGC                 (0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_ISI                  (0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_DMA                  (0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_EMAC                 (0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_USB                  (0x8 << 18) // (MATRIX) USB Master is Default Master
// -------- MATRIX_SCFG6 : (MATRIX Offset: 0x58) Slave Configuration Register 6 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR6 (0x3 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_ARM926I              (0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_ARM926D              (0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_PDC                  (0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_LCDC                 (0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_2DGC                 (0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_ISI                  (0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_DMA                  (0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_EMAC                 (0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_USB                  (0x8 << 18) // (MATRIX) USB Master is Default Master
// -------- MATRIX_SCFG7 : (MATRIX Offset: 0x5c) Slave Configuration Register 7 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR7 (0x3 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR7_ARM926I              (0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR7_ARM926D              (0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR7_PDC                  (0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR7_DMA                  (0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
// -------- MATRIX_PRAS0 : (MATRIX Offset: 0x80) PRAS0 Register -------- 
#define AT91C_MATRIX_M0PR     (0x3 <<  0) // (MATRIX) ARM926EJ-S Instruction priority
#define AT91C_MATRIX_M1PR     (0x3 <<  4) // (MATRIX) ARM926EJ-S Data priority
#define AT91C_MATRIX_M2PR     (0x3 <<  8) // (MATRIX) PDC priority
#define AT91C_MATRIX_M3PR     (0x3 << 12) // (MATRIX) LCDC priority
#define AT91C_MATRIX_M4PR     (0x3 << 16) // (MATRIX) 2DGC priority
#define AT91C_MATRIX_M5PR     (0x3 << 20) // (MATRIX) ISI priority
#define AT91C_MATRIX_M6PR     (0x3 << 24) // (MATRIX) DMA priority
#define AT91C_MATRIX_M7PR     (0x3 << 28) // (MATRIX) EMAC priority
// -------- MATRIX_PRBS0 : (MATRIX Offset: 0x84) PRBS0 Register -------- 
#define AT91C_MATRIX_M8PR     (0x3 <<  0) // (MATRIX) USB priority
// -------- MATRIX_PRAS1 : (MATRIX Offset: 0x88) PRAS1 Register -------- 
// -------- MATRIX_PRBS1 : (MATRIX Offset: 0x8c) PRBS1 Register -------- 
// -------- MATRIX_PRAS2 : (MATRIX Offset: 0x90) PRAS2 Register -------- 
// -------- MATRIX_PRBS2 : (MATRIX Offset: 0x94) PRBS2 Register -------- 
// -------- MATRIX_PRAS3 : (MATRIX Offset: 0x98) PRAS3 Register -------- 
// -------- MATRIX_PRBS3 : (MATRIX Offset: 0x9c) PRBS3 Register -------- 
// -------- MATRIX_PRAS4 : (MATRIX Offset: 0xa0) PRAS4 Register -------- 
// -------- MATRIX_PRBS4 : (MATRIX Offset: 0xa4) PRBS4 Register -------- 
// -------- MATRIX_PRAS5 : (MATRIX Offset: 0xa8) PRAS5 Register -------- 
// -------- MATRIX_PRBS5 : (MATRIX Offset: 0xac) PRBS5 Register -------- 
// -------- MATRIX_PRAS6 : (MATRIX Offset: 0xb0) PRAS6 Register -------- 
// -------- MATRIX_PRBS6 : (MATRIX Offset: 0xb4) PRBS6 Register -------- 
// -------- MATRIX_PRAS7 : (MATRIX Offset: 0xb8) PRAS7 Register -------- 
// -------- MATRIX_PRBS7 : (MATRIX Offset: 0xbc) PRBS7 Register -------- 
// -------- MATRIX_MRCR : (MATRIX Offset: 0x100) MRCR Register -------- 
#define AT91C_MATRIX_RCA926I  (0x1 <<  0) // (MATRIX) Remap Command Bit for ARM926EJ-S Instruction
#define AT91C_MATRIX_RCA926D  (0x1 <<  1) // (MATRIX) Remap Command Bit for ARM926EJ-S Data
#define AT91C_MATRIX_RCB2     (0x1 <<  2) // (MATRIX) Remap Command Bit for PDC
#define AT91C_MATRIX_RCB3     (0x1 <<  3) // (MATRIX) Remap Command Bit for LCD
#define AT91C_MATRIX_RCB4     (0x1 <<  4) // (MATRIX) Remap Command Bit for 2DGC
#define AT91C_MATRIX_RCB5     (0x1 <<  5) // (MATRIX) Remap Command Bit for ISI
#define AT91C_MATRIX_RCB6     (0x1 <<  6) // (MATRIX) Remap Command Bit for DMA
#define AT91C_MATRIX_RCB7     (0x1 <<  7) // (MATRIX) Remap Command Bit for EMAC
#define AT91C_MATRIX_RCB8     (0x1 <<  8) // (MATRIX) Remap Command Bit for USB

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR AHB CCFG Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_CCFG {
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 CCFG_TCMR; 	//  TCM configuration
	AT91_REG	 Reserved1[2]; 	// 
	AT91_REG	 CCFG_EBI0CSA; 	//  EBI0 Chip Select Assignement Register
	AT91_REG	 CCFG_EBI1CSA; 	//  EBI1 Chip Select Assignement Register
	AT91_REG	 Reserved2[53]; 	// 
	AT91_REG	 CCFG_MATRIXVERSION; 	//  Version Register
} AT91S_CCFG, *AT91PS_CCFG;
#else
#define CCFG_TCMR       (AT91_CAST(AT91_REG *) 	0x00000004) // (CCFG_TCMR)  TCM configuration
#define CCFG_EBI0CSA    (AT91_CAST(AT91_REG *) 	0x00000010) // (CCFG_EBI0CSA)  EBI0 Chip Select Assignement Register
#define CCFG_EBI1CSA    (AT91_CAST(AT91_REG *) 	0x00000014) // (CCFG_EBI1CSA)  EBI1 Chip Select Assignement Register
#define CCFG_MATRIXVERSION (AT91_CAST(AT91_REG *) 	0x000000EC) // (CCFG_MATRIXVERSION)  Version Register

#endif
// -------- CCFG_TCMR : (CCFG Offset: 0x4) TCM Configuration -------- 
#define AT91C_CCFG_ITCM_SIZE  (0xF <<  0) // (CCFG) Size of ITCM enabled memory block
#define 	AT91C_CCFG_ITCM_SIZE_0KB                  (0x0) // (CCFG) 0 KB (No ITCM Memory)
#define 	AT91C_CCFG_ITCM_SIZE_16KB                 (0x5) // (CCFG) 16 KB
#define 	AT91C_CCFG_ITCM_SIZE_32KB                 (0x6) // (CCFG) 32 KB
#define AT91C_CCFG_DTCM_SIZE  (0xF <<  4) // (CCFG) Size of DTCM enabled memory block
#define 	AT91C_CCFG_DTCM_SIZE_0KB                  (0x0 <<  4) // (CCFG) 0 KB (No DTCM Memory)
#define 	AT91C_CCFG_DTCM_SIZE_16KB                 (0x5 <<  4) // (CCFG) 16 KB
#define 	AT91C_CCFG_DTCM_SIZE_32KB                 (0x6 <<  4) // (CCFG) 32 KB
#define AT91C_CCFG_RM         (0xF <<  8) // (CCFG) Read Margin registers
// -------- CCFG_EBI0CSA : (CCFG Offset: 0x10) EBI0 Chip Select Assignment Register -------- 
#define AT91C_EBI_CS1A        (0x1 <<  1) // (CCFG) Chip Select 1 Assignment
#define 	AT91C_EBI_CS1A_SMC                  (0x0 <<  1) // (CCFG) Chip Select 1 is assigned to the Static Memory Controller.
#define 	AT91C_EBI_CS1A_SDRAMC               (0x1 <<  1) // (CCFG) Chip Select 1 is assigned to the SDRAM Controller.
#define AT91C_EBI_CS3A        (0x1 <<  3) // (CCFG) Chip Select 3 Assignment
#define 	AT91C_EBI_CS3A_SMC                  (0x0 <<  3) // (CCFG) Chip Select 3 is only assigned to the Static Memory Controller and NCS3 behaves as defined by the SMC.
#define 	AT91C_EBI_CS3A_SM                   (0x1 <<  3) // (CCFG) Chip Select 3 is assigned to the Static Memory Controller and the SmartMedia Logic is activated.
#define AT91C_EBI_CS4A        (0x1 <<  4) // (CCFG) Chip Select 4 Assignment
#define 	AT91C_EBI_CS4A_SMC                  (0x0 <<  4) // (CCFG) Chip Select 4 is only assigned to the Static Memory Controller and NCS4 behaves as defined by the SMC.
#define 	AT91C_EBI_CS4A_CF                   (0x1 <<  4) // (CCFG) Chip Select 4 is assigned to the Static Memory Controller and the CompactFlash Logic (first slot) is activated.
#define AT91C_EBI_CS5A        (0x1 <<  5) // (CCFG) Chip Select 5 Assignment
#define 	AT91C_EBI_CS5A_SMC                  (0x0 <<  5) // (CCFG) Chip Select 5 is only assigned to the Static Memory Controller and NCS5 behaves as defined by the SMC
#define 	AT91C_EBI_CS5A_CF                   (0x1 <<  5) // (CCFG) Chip Select 5 is assigned to the Static Memory Controller and the CompactFlash Logic (second slot) is activated.
#define AT91C_EBI_DBPUC       (0x1 <<  8) // (CCFG) Data Bus Pull-up Configuration
// -------- CCFG_EBI1CSA : (CCFG Offset: 0x14) EBI1 Chip Select Assignement Register -------- 
#define AT91C_EBI_CS2A        (0x1 <<  3) // (CCFG) EBI1 Chip Select 2 Assignment
#define 	AT91C_EBI_CS2A_SMC                  (0x0 <<  3) // (CCFG) Chip Select 2 is assigned to the Static Memory Controller.
#define 	AT91C_EBI_CS2A_SM                   (0x1 <<  3) // (CCFG) Chip Select 2 is assigned to the Static Memory Controller and the SmartMedia Logic is activated.

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_PDC {
	AT91_REG	 PDC_RPR; 	// Receive Pointer Register
	AT91_REG	 PDC_RCR; 	// Receive Counter Register
	AT91_REG	 PDC_TPR; 	// Transmit Pointer Register
	AT91_REG	 PDC_TCR; 	// Transmit Counter Register
	AT91_REG	 PDC_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 PDC_RNCR; 	// Receive Next Counter Register
	AT91_REG	 PDC_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 PDC_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 PDC_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 PDC_PTSR; 	// PDC Transfer Status Register
} AT91S_PDC, *AT91PS_PDC;
#else
#define PDC_RPR         (AT91_CAST(AT91_REG *) 	0x00000000) // (PDC_RPR) Receive Pointer Register
#define PDC_RCR         (AT91_CAST(AT91_REG *) 	0x00000004) // (PDC_RCR) Receive Counter Register
#define PDC_TPR         (AT91_CAST(AT91_REG *) 	0x00000008) // (PDC_TPR) Transmit Pointer Register
#define PDC_TCR         (AT91_CAST(AT91_REG *) 	0x0000000C) // (PDC_TCR) Transmit Counter Register
#define PDC_RNPR        (AT91_CAST(AT91_REG *) 	0x00000010) // (PDC_RNPR) Receive Next Pointer Register
#define PDC_RNCR        (AT91_CAST(AT91_REG *) 	0x00000014) // (PDC_RNCR) Receive Next Counter Register
#define PDC_TNPR        (AT91_CAST(AT91_REG *) 	0x00000018) // (PDC_TNPR) Transmit Next Pointer Register
#define PDC_TNCR        (AT91_CAST(AT91_REG *) 	0x0000001C) // (PDC_TNCR) Transmit Next Counter Register
#define PDC_PTCR        (AT91_CAST(AT91_REG *) 	0x00000020) // (PDC_PTCR) PDC Transfer Control Register
#define PDC_PTSR        (AT91_CAST(AT91_REG *) 	0x00000024) // (PDC_PTSR) PDC Transfer Status Register

#endif
// -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- 
#define AT91C_PDC_RXTEN       (0x1 <<  0) // (PDC) Receiver Transfer Enable
#define AT91C_PDC_RXTDIS      (0x1 <<  1) // (PDC) Receiver Transfer Disable
#define AT91C_PDC_TXTEN       (0x1 <<  8) // (PDC) Transmitter Transfer Enable
#define AT91C_PDC_TXTDIS      (0x1 <<  9) // (PDC) Transmitter Transfer Disable
// -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Debug Unit
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_DBGU {
	AT91_REG	 DBGU_CR; 	// Control Register
	AT91_REG	 DBGU_MR; 	// Mode Register
	AT91_REG	 DBGU_IER; 	// Interrupt Enable Register
	AT91_REG	 DBGU_IDR; 	// Interrupt Disable Register
	AT91_REG	 DBGU_IMR; 	// Interrupt Mask Register
	AT91_REG	 DBGU_CSR; 	// Channel Status Register
	AT91_REG	 DBGU_RHR; 	// Receiver Holding Register
	AT91_REG	 DBGU_THR; 	// Transmitter Holding Register
	AT91_REG	 DBGU_BRGR; 	// Baud Rate Generator Register
	AT91_REG	 Reserved0[7]; 	// 
	AT91_REG	 DBGU_CIDR; 	// Chip ID Register
	AT91_REG	 DBGU_EXID; 	// Chip ID Extension Register
	AT91_REG	 DBGU_FNTR; 	// Force NTRST Register
	AT91_REG	 Reserved1[45]; 	// 
	AT91_REG	 DBGU_RPR; 	// Receive Pointer Register
	AT91_REG	 DBGU_RCR; 	// Receive Counter Register
	AT91_REG	 DBGU_TPR; 	// Transmit Pointer Register
	AT91_REG	 DBGU_TCR; 	// Transmit Counter Register
	AT91_REG	 DBGU_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 DBGU_RNCR; 	// Receive Next Counter Register
	AT91_REG	 DBGU_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 DBGU_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 DBGU_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 DBGU_PTSR; 	// PDC Transfer Status Register
} AT91S_DBGU, *AT91PS_DBGU;
#else
#define DBGU_CR         (AT91_CAST(AT91_REG *) 	0x00000000) // (DBGU_CR) Control Register
#define DBGU_MR         (AT91_CAST(AT91_REG *) 	0x00000004) // (DBGU_MR) Mode Register
#define DBGU_IER        (AT91_CAST(AT91_REG *) 	0x00000008) // (DBGU_IER) Interrupt Enable Register
#define DBGU_IDR        (AT91_CAST(AT91_REG *) 	0x0000000C) // (DBGU_IDR) Interrupt Disable Register
#define DBGU_IMR        (AT91_CAST(AT91_REG *) 	0x00000010) // (DBGU_IMR) Interrupt Mask Register
#define DBGU_CSR        (AT91_CAST(AT91_REG *) 	0x00000014) // (DBGU_CSR) Channel Status Register
#define DBGU_RHR        (AT91_CAST(AT91_REG *) 	0x00000018) // (DBGU_RHR) Receiver Holding Register
#define DBGU_THR        (AT91_CAST(AT91_REG *) 	0x0000001C) // (DBGU_THR) Transmitter Holding Register
#define DBGU_BRGR       (AT91_CAST(AT91_REG *) 	0x00000020) // (DBGU_BRGR) Baud Rate Generator Register
#define DBGU_CIDR       (AT91_CAST(AT91_REG *) 	0x00000040) // (DBGU_CIDR) Chip ID Register
#define DBGU_EXID       (AT91_CAST(AT91_REG *) 	0x00000044) // (DBGU_EXID) Chip ID Extension Register
#define DBGU_FNTR       (AT91_CAST(AT91_REG *) 	0x00000048) // (DBGU_FNTR) Force NTRST Register

#endif
// -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- 
#define AT91C_US_RSTRX        (0x1 <<  2) // (DBGU) Reset Receiver
#define AT91C_US_RSTTX        (0x1 <<  3) // (DBGU) Reset Transmitter
#define AT91C_US_RXEN         (0x1 <<  4) // (DBGU) Receiver Enable
#define AT91C_US_RXDIS        (0x1 <<  5) // (DBGU) Receiver Disable
#define AT91C_US_TXEN         (0x1 <<  6) // (DBGU) Transmitter Enable
#define AT91C_US_TXDIS        (0x1 <<  7) // (DBGU) Transmitter Disable
#define AT91C_US_RSTSTA       (0x1 <<  8) // (DBGU) Reset Status Bits
// -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- 
#define AT91C_US_PAR          (0x7 <<  9) // (DBGU) Parity type
#define 	AT91C_US_PAR_EVEN                 (0x0 <<  9) // (DBGU) Even Parity
#define 	AT91C_US_PAR_ODD                  (0x1 <<  9) // (DBGU) Odd Parity
#define 	AT91C_US_PAR_SPACE                (0x2 <<  9) // (DBGU) Parity forced to 0 (Space)
#define 	AT91C_US_PAR_MARK                 (0x3 <<  9) // (DBGU) Parity forced to 1 (Mark)
#define 	AT91C_US_PAR_NONE                 (0x4 <<  9) // (DBGU) No Parity
#define 	AT91C_US_PAR_MULTI_DROP           (0x6 <<  9) // (DBGU) Multi-drop mode
#define AT91C_US_CHMODE       (0x3 << 14) // (DBGU) Channel Mode
#define 	AT91C_US_CHMODE_NORMAL               (0x0 << 14) // (DBGU) Normal Mode: The USART channel operates as an RX/TX USART.
#define 	AT91C_US_CHMODE_AUTO                 (0x1 << 14) // (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin.
#define 	AT91C_US_CHMODE_LOCAL                (0x2 << 14) // (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal.
#define 	AT91C_US_CHMODE_REMOTE               (0x3 << 14) // (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin.
// -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define AT91C_US_RXRDY        (0x1 <<  0) // (DBGU) RXRDY Interrupt
#define AT91C_US_TXRDY        (0x1 <<  1) // (DBGU) TXRDY Interrupt
#define AT91C_US_ENDRX        (0x1 <<  3) // (DBGU) End of Receive Transfer Interrupt
#define AT91C_US_ENDTX        (0x1 <<  4) // (DBGU) End of Transmit Interrupt
#define AT91C_US_OVRE         (0x1 <<  5) // (DBGU) Overrun Interrupt
#define AT91C_US_FRAME        (0x1 <<  6) // (DBGU) Framing Error Interrupt
#define AT91C_US_PARE         (0x1 <<  7) // (DBGU) Parity Error Interrupt
#define AT91C_US_TXEMPTY      (0x1 <<  9) // (DBGU) TXEMPTY Interrupt
#define AT91C_US_TXBUFE       (0x1 << 11) // (DBGU) TXBUFE Interrupt
#define AT91C_US_RXBUFF       (0x1 << 12) // (DBGU) RXBUFF Interrupt
#define AT91C_US_COMM_TX      (0x1 << 30) // (DBGU) COMM_TX Interrupt
#define AT91C_US_COMM_RX      (0x1 << 31) // (DBGU) COMM_RX Interrupt
// -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- 
// -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- 
#define AT91C_US_FORCE_NTRST  (0x1 <<  0) // (DBGU) Force NTRST in JTAG

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_AIC {
	AT91_REG	 AIC_SMR[32]; 	// Source Mode Register
	AT91_REG	 AIC_SVR[32]; 	// Source Vector Register
	AT91_REG	 AIC_IVR; 	// IRQ Vector Register
	AT91_REG	 AIC_FVR; 	// FIQ Vector Register
	AT91_REG	 AIC_ISR; 	// Interrupt Status Register
	AT91_REG	 AIC_IPR; 	// Interrupt Pending Register
	AT91_REG	 AIC_IMR; 	// Interrupt Mask Register
	AT91_REG	 AIC_CISR; 	// Core Interrupt Status Register
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 AIC_IECR; 	// Interrupt Enable Command Register
	AT91_REG	 AIC_IDCR; 	// Interrupt Disable Command Register
	AT91_REG	 AIC_ICCR; 	// Interrupt Clear Command Register
	AT91_REG	 AIC_ISCR; 	// Interrupt Set Command Register
	AT91_REG	 AIC_EOICR; 	// End of Interrupt Command Register
	AT91_REG	 AIC_SPU; 	// Spurious Vector Register
	AT91_REG	 AIC_DCR; 	// Debug Control Register (Protect)
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 AIC_FFER; 	// Fast Forcing Enable Register
	AT91_REG	 AIC_FFDR; 	// Fast Forcing Disable Register
	AT91_REG	 AIC_FFSR; 	// Fast Forcing Status Register
} AT91S_AIC, *AT91PS_AIC;
#else
#define AIC_SMR         (AT91_CAST(AT91_REG *) 	0x00000000) // (AIC_SMR) Source Mode Register
#define AIC_SVR         (AT91_CAST(AT91_REG *) 	0x00000080) // (AIC_SVR) Source Vector Register
#define AIC_IVR         (AT91_CAST(AT91_REG *) 	0x00000100) // (AIC_IVR) IRQ Vector Register
#define AIC_FVR         (AT91_CAST(AT91_REG *) 	0x00000104) // (AIC_FVR) FIQ Vector Register
#define AIC_ISR         (AT91_CAST(AT91_REG *) 	0x00000108) // (AIC_ISR) Interrupt Status Register
#define AIC_IPR         (AT91_CAST(AT91_REG *) 	0x0000010C) // (AIC_IPR) Interrupt Pending Register
#define AIC_IMR         (AT91_CAST(AT91_REG *) 	0x00000110) // (AIC_IMR) Interrupt Mask Register
#define AIC_CISR        (AT91_CAST(AT91_REG *) 	0x00000114) // (AIC_CISR) Core Interrupt Status Register
#define AIC_IECR        (AT91_CAST(AT91_REG *) 	0x00000120) // (AIC_IECR) Interrupt Enable Command Register
#define AIC_IDCR        (AT91_CAST(AT91_REG *) 	0x00000124) // (AIC_IDCR) Interrupt Disable Command Register
#define AIC_ICCR        (AT91_CAST(AT91_REG *) 	0x00000128) // (AIC_ICCR) Interrupt Clear Command Register
#define AIC_ISCR        (AT91_CAST(AT91_REG *) 	0x0000012C) // (AIC_ISCR) Interrupt Set Command Register
#define AIC_EOICR       (AT91_CAST(AT91_REG *) 	0x00000130) // (AIC_EOICR) End of Interrupt Command Register
#define AIC_SPU         (AT91_CAST(AT91_REG *) 	0x00000134) // (AIC_SPU) Spurious Vector Register
#define AIC_DCR         (AT91_CAST(AT91_REG *) 	0x00000138) // (AIC_DCR) Debug Control Register (Protect)
#define AIC_FFER        (AT91_CAST(AT91_REG *) 	0x00000140) // (AIC_FFER) Fast Forcing Enable Register
#define AIC_FFDR        (AT91_CAST(AT91_REG *) 	0x00000144) // (AIC_FFDR) Fast Forcing Disable Register
#define AIC_FFSR        (AT91_CAST(AT91_REG *) 	0x00000148) // (AIC_FFSR) Fast Forcing Status Register

#endif
// -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- 
#define AT91C_AIC_PRIOR       (0x7 <<  0) // (AIC) Priority Level
#define 	AT91C_AIC_PRIOR_LOWEST               (0x0) // (AIC) Lowest priority level
#define 	AT91C_AIC_PRIOR_HIGHEST              (0x7) // (AIC) Highest priority level
#define AT91C_AIC_SRCTYPE     (0x3 <<  5) // (AIC) Interrupt Source Type
#define 	AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL       (0x0 <<  5) // (AIC) Internal Sources Code Label High-level Sensitive
#define 	AT91C_AIC_SRCTYPE_EXT_LOW_LEVEL        (0x0 <<  5) // (AIC) External Sources Code Label Low-level Sensitive
#define 	AT91C_AIC_SRCTYPE_INT_POSITIVE_EDGE    (0x1 <<  5) // (AIC) Internal Sources Code Label Positive Edge triggered
#define 	AT91C_AIC_SRCTYPE_EXT_NEGATIVE_EDGE    (0x1 <<  5) // (AIC) External Sources Code Label Negative Edge triggered
#define 	AT91C_AIC_SRCTYPE_HIGH_LEVEL           (0x2 <<  5) // (AIC) Internal Or External Sources Code Label High-level Sensitive
#define 	AT91C_AIC_SRCTYPE_POSITIVE_EDGE        (0x3 <<  5) // (AIC) Internal Or External Sources Code Label Positive Edge triggered
// -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- 
#define AT91C_AIC_NFIQ        (0x1 <<  0) // (AIC) NFIQ Status
#define AT91C_AIC_NIRQ        (0x1 <<  1) // (AIC) NIRQ Status
// -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- 
#define AT91C_AIC_DCR_PROT    (0x1 <<  0) // (AIC) Protection Mode
#define AT91C_AIC_DCR_GMSK    (0x1 <<  1) // (AIC) General Mask

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Parallel Input Output Controler
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_PIO {
	AT91_REG	 PIO_PER; 	// PIO Enable Register
	AT91_REG	 PIO_PDR; 	// PIO Disable Register
	AT91_REG	 PIO_PSR; 	// PIO Status Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 PIO_OER; 	// Output Enable Register
	AT91_REG	 PIO_ODR; 	// Output Disable Registerr
	AT91_REG	 PIO_OSR; 	// Output Status Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 PIO_IFER; 	// Input Filter Enable Register
	AT91_REG	 PIO_IFDR; 	// Input Filter Disable Register
	AT91_REG	 PIO_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 PIO_SODR; 	// Set Output Data Register
	AT91_REG	 PIO_CODR; 	// Clear Output Data Register
	AT91_REG	 PIO_ODSR; 	// Output Data Status Register
	AT91_REG	 PIO_PDSR; 	// Pin Data Status Register
	AT91_REG	 PIO_IER; 	// Interrupt Enable Register
	AT91_REG	 PIO_IDR; 	// Interrupt Disable Register
	AT91_REG	 PIO_IMR; 	// Interrupt Mask Register
	AT91_REG	 PIO_ISR; 	// Interrupt Status Register
	AT91_REG	 PIO_MDER; 	// Multi-driver Enable Register
	AT91_REG	 PIO_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 PIO_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved3[1]; 	// 
	AT91_REG	 PIO_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 PIO_PPUER; 	// Pull-up Enable Register
	AT91_REG	 PIO_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved4[1]; 	// 
	AT91_REG	 PIO_ASR; 	// Select A Register
	AT91_REG	 PIO_BSR; 	// Select B Register
	AT91_REG	 PIO_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved5[9]; 	// 
	AT91_REG	 PIO_OWER; 	// Output Write Enable Register
	AT91_REG	 PIO_OWDR; 	// Output Write Disable Register
	AT91_REG	 PIO_OWSR; 	// Output Write Status Register
} AT91S_PIO, *AT91PS_PIO;
#else
#define PIO_PER         (AT91_CAST(AT91_REG *) 	0x00000000) // (PIO_PER) PIO Enable Register
#define PIO_PDR         (AT91_CAST(AT91_REG *) 	0x00000004) // (PIO_PDR) PIO Disable Register
#define PIO_PSR         (AT91_CAST(AT91_REG *) 	0x00000008) // (PIO_PSR) PIO Status Register
#define PIO_OER         (AT91_CAST(AT91_REG *) 	0x00000010) // (PIO_OER) Output Enable Register
#define PIO_ODR         (AT91_CAST(AT91_REG *) 	0x00000014) // (PIO_ODR) Output Disable Registerr
#define PIO_OSR         (AT91_CAST(AT91_REG *) 	0x00000018) // (PIO_OSR) Output Status Register
#define PIO_IFER        (AT91_CAST(AT91_REG *) 	0x00000020) // (PIO_IFER) Input Filter Enable Register
#define PIO_IFDR        (AT91_CAST(AT91_REG *) 	0x00000024) // (PIO_IFDR) Input Filter Disable Register
#define PIO_IFSR        (AT91_CAST(AT91_REG *) 	0x00000028) // (PIO_IFSR) Input Filter Status Register
#define PIO_SODR        (AT91_CAST(AT91_REG *) 	0x00000030) // (PIO_SODR) Set Output Data Register
#define PIO_CODR        (AT91_CAST(AT91_REG *) 	0x00000034) // (PIO_CODR) Clear Output Data Register
#define PIO_ODSR        (AT91_CAST(AT91_REG *) 	0x00000038) // (PIO_ODSR) Output Data Status Register
#define PIO_PDSR        (AT91_CAST(AT91_REG *) 	0x0000003C) // (PIO_PDSR) Pin Data Status Register
#define PIO_IER         (AT91_CAST(AT91_REG *) 	0x00000040) // (PIO_IER) Interrupt Enable Register
#define PIO_IDR         (AT91_CAST(AT91_REG *) 	0x00000044) // (PIO_IDR) Interrupt Disable Register
#define PIO_IMR         (AT91_CAST(AT91_REG *) 	0x00000048) // (PIO_IMR) Interrupt Mask Register
#define PIO_ISR         (AT91_CAST(AT91_REG *) 	0x0000004C) // (PIO_ISR) Interrupt Status Register
#define PIO_MDER        (AT91_CAST(AT91_REG *) 	0x00000050) // (PIO_MDER) Multi-driver Enable Register
#define PIO_MDDR        (AT91_CAST(AT91_REG *) 	0x00000054) // (PIO_MDDR) Multi-driver Disable Register
#define PIO_MDSR        (AT91_CAST(AT91_REG *) 	0x00000058) // (PIO_MDSR) Multi-driver Status Register
#define PIO_PPUDR       (AT91_CAST(AT91_REG *) 	0x00000060) // (PIO_PPUDR) Pull-up Disable Register
#define PIO_PPUER       (AT91_CAST(AT91_REG *) 	0x00000064) // (PIO_PPUER) Pull-up Enable Register
#define PIO_PPUSR       (AT91_CAST(AT91_REG *) 	0x00000068) // (PIO_PPUSR) Pull-up Status Register
#define PIO_ASR         (AT91_CAST(AT91_REG *) 	0x00000070) // (PIO_ASR) Select A Register
#define PIO_BSR         (AT91_CAST(AT91_REG *) 	0x00000074) // (PIO_BSR) Select B Register
#define PIO_ABSR        (AT91_CAST(AT91_REG *) 	0x00000078) // (PIO_ABSR) AB Select Status Register
#define PIO_OWER        (AT91_CAST(AT91_REG *) 	0x000000A0) // (PIO_OWER) Output Write Enable Register
#define PIO_OWDR        (AT91_CAST(AT91_REG *) 	0x000000A4) // (PIO_OWDR) Output Write Disable Register
#define PIO_OWSR        (AT91_CAST(AT91_REG *) 	0x000000A8) // (PIO_OWSR) Output Write Status Register

#endif

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Clock Generator Controler
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_CKGR {
	AT91_REG	 CKGR_MOR; 	// Main Oscillator Register
	AT91_REG	 CKGR_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 CKGR_PLLAR; 	// PLL A Register
	AT91_REG	 CKGR_PLLBR; 	// PLL B Register
} AT91S_CKGR, *AT91PS_CKGR;
#else
#define CKGR_MOR        (AT91_CAST(AT91_REG *) 	0x00000000) // (CKGR_MOR) Main Oscillator Register
#define CKGR_MCFR       (AT91_CAST(AT91_REG *) 	0x00000004) // (CKGR_MCFR) Main Clock  Frequency Register
#define CKGR_PLLAR      (AT91_CAST(AT91_REG *) 	0x00000008) // (CKGR_PLLAR) PLL A Register
#define CKGR_PLLBR      (AT91_CAST(AT91_REG *) 	0x0000000C) // (CKGR_PLLBR) PLL B Register

#endif
// -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- 
#define AT91C_CKGR_MOSCEN     (0x1 <<  0) // (CKGR) Main Oscillator Enable
#define AT91C_CKGR_OSCBYPASS  (0x1 <<  1) // (CKGR) Main Oscillator Bypass
#define AT91C_CKGR_OSCOUNT    (0xFF <<  8) // (CKGR) Main Oscillator Start-up Time
// -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- 
#define AT91C_CKGR_MAINF      (0xFFFF <<  0) // (CKGR) Main Clock Frequency
#define AT91C_CKGR_MAINRDY    (0x1 << 16) // (CKGR) Main Clock Ready
// -------- CKGR_PLLAR : (CKGR Offset: 0x8) PLL A Register -------- 
#define AT91C_CKGR_DIVA       (0xFF <<  0) // (CKGR) Divider A Selected
#define 	AT91C_CKGR_DIVA_0                    (0x0) // (CKGR) Divider A output is 0
#define 	AT91C_CKGR_DIVA_BYPASS               (0x1) // (CKGR) Divider A is bypassed
#define AT91C_CKGR_PLLACOUNT  (0x3F <<  8) // (CKGR) PLL A Counter
#define AT91C_CKGR_OUTA       (0x3 << 14) // (CKGR) PLL A Output Frequency Range
#define 	AT91C_CKGR_OUTA_0                    (0x0 << 14) // (CKGR) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_1                    (0x1 << 14) // (CKGR) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_2                    (0x2 << 14) // (CKGR) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_3                    (0x3 << 14) // (CKGR) Please refer to the PLLA datasheet
#define AT91C_CKGR_MULA       (0x7FF << 16) // (CKGR) PLL A Multiplier
#define AT91C_CKGR_SRCA       (0x1 << 29) // (CKGR) 
// -------- CKGR_PLLBR : (CKGR Offset: 0xc) PLL B Register -------- 
#define AT91C_CKGR_DIVB       (0xFF <<  0) // (CKGR) Divider B Selected
#define 	AT91C_CKGR_DIVB_0                    (0x0) // (CKGR) Divider B output is 0
#define 	AT91C_CKGR_DIVB_BYPASS               (0x1) // (CKGR) Divider B is bypassed
#define AT91C_CKGR_PLLBCOUNT  (0x3F <<  8) // (CKGR) PLL B Counter
#define AT91C_CKGR_OUTB       (0x3 << 14) // (CKGR) PLL B Output Frequency Range
#define 	AT91C_CKGR_OUTB_0                    (0x0 << 14) // (CKGR) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_1                    (0x1 << 14) // (CKGR) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_2                    (0x2 << 14) // (CKGR) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_3                    (0x3 << 14) // (CKGR) Please refer to the PLLB datasheet
#define AT91C_CKGR_MULB       (0x7FF << 16) // (CKGR) PLL B Multiplier
#define AT91C_CKGR_USBDIV     (0x3 << 28) // (CKGR) Divider for USB Clocks
#define 	AT91C_CKGR_USBDIV_0                    (0x0 << 28) // (CKGR) Divider output is PLL clock output
#define 	AT91C_CKGR_USBDIV_1                    (0x1 << 28) // (CKGR) Divider output is PLL clock output divided by 2
#define 	AT91C_CKGR_USBDIV_2                    (0x2 << 28) // (CKGR) Divider output is PLL clock output divided by 4

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Power Management Controler
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_PMC {
	AT91_REG	 PMC_SCER; 	// System Clock Enable Register
	AT91_REG	 PMC_SCDR; 	// System Clock Disable Register
	AT91_REG	 PMC_SCSR; 	// System Clock Status Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 PMC_PCER; 	// Peripheral Clock Enable Register
	AT91_REG	 PMC_PCDR; 	// Peripheral Clock Disable Register
	AT91_REG	 PMC_PCSR; 	// Peripheral Clock Status Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 PMC_MOR; 	// Main Oscillator Register
	AT91_REG	 PMC_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 PMC_PLLAR; 	// PLL A Register
	AT91_REG	 PMC_PLLBR; 	// PLL B Register
	AT91_REG	 PMC_MCKR; 	// Master Clock Register
	AT91_REG	 Reserved2[3]; 	// 
	AT91_REG	 PMC_PCKR[8]; 	// Programmable Clock Register
	AT91_REG	 PMC_IER; 	// Interrupt Enable Register
	AT91_REG	 PMC_IDR; 	// Interrupt Disable Register
	AT91_REG	 PMC_SR; 	// Status Register
	AT91_REG	 PMC_IMR; 	// Interrupt Mask Register
} AT91S_PMC, *AT91PS_PMC;
#else
#define PMC_SCER        (AT91_CAST(AT91_REG *) 	0x00000000) // (PMC_SCER) System Clock Enable Register
#define PMC_SCDR        (AT91_CAST(AT91_REG *) 	0x00000004) // (PMC_SCDR) System Clock Disable Register
#define PMC_SCSR        (AT91_CAST(AT91_REG *) 	0x00000008) // (PMC_SCSR) System Clock Status Register
#define PMC_PCER        (AT91_CAST(AT91_REG *) 	0x00000010) // (PMC_PCER) Peripheral Clock Enable Register
#define PMC_PCDR        (AT91_CAST(AT91_REG *) 	0x00000014) // (PMC_PCDR) Peripheral Clock Disable Register
#define PMC_PCSR        (AT91_CAST(AT91_REG *) 	0x00000018) // (PMC_PCSR) Peripheral Clock Status Register
#define PMC_MCKR        (AT91_CAST(AT91_REG *) 	0x00000030) // (PMC_MCKR) Master Clock Register
#define PMC_PCKR        (AT91_CAST(AT91_REG *) 	0x00000040) // (PMC_PCKR) Programmable Clock Register
#define PMC_IER         (AT91_CAST(AT91_REG *) 	0x00000060) // (PMC_IER) Interrupt Enable Register
#define PMC_IDR         (AT91_CAST(AT91_REG *) 	0x00000064) // (PMC_IDR) Interrupt Disable Register
#define PMC_SR          (AT91_CAST(AT91_REG *) 	0x00000068) // (PMC_SR) Status Register
#define PMC_IMR         (AT91_CAST(AT91_REG *) 	0x0000006C) // (PMC_IMR) Interrupt Mask Register

#endif
// -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
#define AT91C_PMC_PCK         (0x1 <<  0) // (PMC) Processor Clock
#define AT91C_PMC_OTG         (0x1 <<  5) // (PMC) USB OTG Clock
#define AT91C_PMC_UHP         (0x1 <<  6) // (PMC) USB Host Port Clock
#define AT91C_PMC_UDP         (0x1 <<  7) // (PMC) USB Device Port Clock
#define AT91C_PMC_PCK0        (0x1 <<  8) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK1        (0x1 <<  9) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK2        (0x1 << 10) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK3        (0x1 << 11) // (PMC) Programmable Clock Output
// -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
// -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
// -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
// -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
// -------- CKGR_PLLAR : (PMC Offset: 0x28) PLL A Register -------- 
// -------- CKGR_PLLBR : (PMC Offset: 0x2c) PLL B Register -------- 
// -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
#define AT91C_PMC_CSS         (0x3 <<  0) // (PMC) Programmable Clock Selection
#define 	AT91C_PMC_CSS_SLOW_CLK             (0x0) // (PMC) Slow Clock is selected
#define 	AT91C_PMC_CSS_MAIN_CLK             (0x1) // (PMC) Main Clock is selected
#define 	AT91C_PMC_CSS_PLLA_CLK             (0x2) // (PMC) Clock from PLL A is selected
#define 	AT91C_PMC_CSS_PLLB_CLK             (0x3) // (PMC) Clock from PLL B is selected
#define AT91C_PMC_PRES        (0x7 <<  2) // (PMC) Programmable Clock Prescaler
#define 	AT91C_PMC_PRES_CLK                  (0x0 <<  2) // (PMC) Selected clock
#define 	AT91C_PMC_PRES_CLK_2                (0x1 <<  2) // (PMC) Selected clock divided by 2
#define 	AT91C_PMC_PRES_CLK_4                (0x2 <<  2) // (PMC) Selected clock divided by 4
#define 	AT91C_PMC_PRES_CLK_8                (0x3 <<  2) // (PMC) Selected clock divided by 8
#define 	AT91C_PMC_PRES_CLK_16               (0x4 <<  2) // (PMC) Selected clock divided by 16
#define 	AT91C_PMC_PRES_CLK_32               (0x5 <<  2) // (PMC) Selected clock divided by 32
#define 	AT91C_PMC_PRES_CLK_64               (0x6 <<  2) // (PMC) Selected clock divided by 64
#define AT91C_PMC_MDIV        (0x3 <<  8) // (PMC) Master Clock Division
#define 	AT91C_PMC_MDIV_1                    (0x0 <<  8) // (PMC) The master clock and the processor clock are the same
#define 	AT91C_PMC_MDIV_2                    (0x1 <<  8) // (PMC) The processor clock is twice as fast as the master clock
#define 	AT91C_PMC_MDIV_3                    (0x2 <<  8) // (PMC) The processor clock is four times faster than the master clock
// -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
// -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
#define AT91C_PMC_MOSCS       (0x1 <<  0) // (PMC) MOSC Status/Enable/Disable/Mask
#define AT91C_PMC_LOCKA       (0x1 <<  1) // (PMC) PLL A Status/Enable/Disable/Mask
#define AT91C_PMC_LOCKB       (0x1 <<  2) // (PMC) PLL B Status/Enable/Disable/Mask
#define AT91C_PMC_MCKRDY      (0x1 <<  3) // (PMC) Master Clock Status/Enable/Disable/Mask
#define AT91C_PMC_PCK0RDY     (0x1 <<  8) // (PMC) PCK0_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCK1RDY     (0x1 <<  9) // (PMC) PCK1_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCK2RDY     (0x1 << 10) // (PMC) PCK2_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCK3RDY     (0x1 << 11) // (PMC) PCK3_RDY Status/Enable/Disable/Mask
// -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
// -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
// -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Reset Controller Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_RSTC {
	AT91_REG	 RSTC_RCR; 	// Reset Control Register
	AT91_REG	 RSTC_RSR; 	// Reset Status Register
	AT91_REG	 RSTC_RMR; 	// Reset Mode Register
	AT91_REG	 Reserved0[60]; 	// 
	AT91_REG	 RSTC_VER; 	// Version Register
} AT91S_RSTC, *AT91PS_RSTC;
#else
#define RSTC_RCR        (AT91_CAST(AT91_REG *) 	0x00000000) // (RSTC_RCR) Reset Control Register
#define RSTC_RSR        (AT91_CAST(AT91_REG *) 	0x00000004) // (RSTC_RSR) Reset Status Register
#define RSTC_RMR        (AT91_CAST(AT91_REG *) 	0x00000008) // (RSTC_RMR) Reset Mode Register
#define RSTC_VER        (AT91_CAST(AT91_REG *) 	0x000000FC) // (RSTC_VER) Version Register

#endif
// -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- 
#define AT91C_RSTC_PROCRST    (0x1 <<  0) // (RSTC) Processor Reset
#define AT91C_RSTC_ICERST     (0x1 <<  1) // (RSTC) ICE Interface Reset
#define AT91C_RSTC_PERRST     (0x1 <<  2) // (RSTC) Peripheral Reset
#define AT91C_RSTC_EXTRST     (0x1 <<  3) // (RSTC) External Reset
#define AT91C_RSTC_KEY        (0xFF << 24) // (RSTC) Password
// -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- 
#define AT91C_RSTC_URSTS      (0x1 <<  0) // (RSTC) User Reset Status
#define AT91C_RSTC_RSTTYP     (0x7 <<  8) // (RSTC) Reset Type
#define 	AT91C_RSTC_RSTTYP_GENERAL              (0x0 <<  8) // (RSTC) General reset. Both VDDCORE and VDDBU rising.
#define 	AT91C_RSTC_RSTTYP_WAKEUP               (0x1 <<  8) // (RSTC) WakeUp Reset. VDDCORE rising.
#define 	AT91C_RSTC_RSTTYP_WATCHDOG             (0x2 <<  8) // (RSTC) Watchdog Reset. Watchdog overflow occured.
#define 	AT91C_RSTC_RSTTYP_SOFTWARE             (0x3 <<  8) // (RSTC) Software Reset. Processor reset required by the software.
#define 	AT91C_RSTC_RSTTYP_USER                 (0x4 <<  8) // (RSTC) User Reset. NRST pin detected low.
#define AT91C_RSTC_NRSTL      (0x1 << 16) // (RSTC) NRST pin level
#define AT91C_RSTC_SRCMP      (0x1 << 17) // (RSTC) Software Reset Command in Progress.
// -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- 
#define AT91C_RSTC_URSTEN     (0x1 <<  0) // (RSTC) User Reset Enable
#define AT91C_RSTC_URSTIEN    (0x1 <<  4) // (RSTC) User Reset Interrupt Enable
#define AT91C_RSTC_ERSTL      (0xF <<  8) // (RSTC) User Reset Enable

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Shut Down Controller Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_SHDWC {
	AT91_REG	 SHDWC_SHCR; 	// Shut Down Control Register
	AT91_REG	 SHDWC_SHMR; 	// Shut Down Mode Register
	AT91_REG	 SHDWC_SHSR; 	// Shut Down Status Register
} AT91S_SHDWC, *AT91PS_SHDWC;
#else
#define SHDWC_SHCR      (AT91_CAST(AT91_REG *) 	0x00000000) // (SHDWC_SHCR) Shut Down Control Register
#define SHDWC_SHMR      (AT91_CAST(AT91_REG *) 	0x00000004) // (SHDWC_SHMR) Shut Down Mode Register
#define SHDWC_SHSR      (AT91_CAST(AT91_REG *) 	0x00000008) // (SHDWC_SHSR) Shut Down Status Register

#endif
// -------- SHDWC_SHCR : (SHDWC Offset: 0x0) Shut Down Control Register -------- 
#define AT91C_SHDWC_SHDW      (0x1 <<  0) // (SHDWC) Processor Reset
#define AT91C_SHDWC_KEY       (0xFF << 24) // (SHDWC) Shut down KEY Password
// -------- SHDWC_SHMR : (SHDWC Offset: 0x4) Shut Down Mode Register -------- 
#define AT91C_SHDWC_WKMODE0   (0x3 <<  0) // (SHDWC) Wake Up 0 Mode Selection
#define 	AT91C_SHDWC_WKMODE0_NONE                 (0x0) // (SHDWC) None. No detection is performed on the wake up input.
#define 	AT91C_SHDWC_WKMODE0_HIGH                 (0x1) // (SHDWC) High Level.
#define 	AT91C_SHDWC_WKMODE0_LOW                  (0x2) // (SHDWC) Low Level.
#define 	AT91C_SHDWC_WKMODE0_ANYLEVEL             (0x3) // (SHDWC) Any level change.
#define AT91C_SHDWC_CPTWK0    (0xF <<  4) // (SHDWC) Counter On Wake Up 0
#define AT91C_SHDWC_WKMODE1   (0x3 <<  8) // (SHDWC) Wake Up 1 Mode Selection
#define 	AT91C_SHDWC_WKMODE1_NONE                 (0x0 <<  8) // (SHDWC) None. No detection is performed on the wake up input.
#define 	AT91C_SHDWC_WKMODE1_HIGH                 (0x1 <<  8) // (SHDWC) High Level.
#define 	AT91C_SHDWC_WKMODE1_LOW                  (0x2 <<  8) // (SHDWC) Low Level.
#define 	AT91C_SHDWC_WKMODE1_ANYLEVEL             (0x3 <<  8) // (SHDWC) Any level change.
#define AT91C_SHDWC_CPTWK1    (0xF << 12) // (SHDWC) Counter On Wake Up 1
#define AT91C_SHDWC_RTTWKEN   (0x1 << 16) // (SHDWC) Real Time Timer Wake Up Enable
#define AT91C_SHDWC_RTCWKEN   (0x1 << 17) // (SHDWC) Real Time Clock Wake Up Enable
// -------- SHDWC_SHSR : (SHDWC Offset: 0x8) Shut Down Status Register -------- 
#define AT91C_SHDWC_WAKEUP0   (0x1 <<  0) // (SHDWC) Wake Up 0 Status
#define AT91C_SHDWC_WAKEUP1   (0x1 <<  1) // (SHDWC) Wake Up 1 Status
#define AT91C_SHDWC_FWKUP     (0x1 <<  2) // (SHDWC) Force Wake Up Status
#define AT91C_SHDWC_RTTWK     (0x1 << 16) // (SHDWC) Real Time Timer wake Up
#define AT91C_SHDWC_RTCWK     (0x1 << 17) // (SHDWC) Real Time Clock wake Up

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_RTTC {
	AT91_REG	 RTTC_RTMR; 	// Real-time Mode Register
	AT91_REG	 RTTC_RTAR; 	// Real-time Alarm Register
	AT91_REG	 RTTC_RTVR; 	// Real-time Value Register
	AT91_REG	 RTTC_RTSR; 	// Real-time Status Register
} AT91S_RTTC, *AT91PS_RTTC;
#else
#define RTTC_RTMR       (AT91_CAST(AT91_REG *) 	0x00000000) // (RTTC_RTMR) Real-time Mode Register
#define RTTC_RTAR       (AT91_CAST(AT91_REG *) 	0x00000004) // (RTTC_RTAR) Real-time Alarm Register
#define RTTC_RTVR       (AT91_CAST(AT91_REG *) 	0x00000008) // (RTTC_RTVR) Real-time Value Register
#define RTTC_RTSR       (AT91_CAST(AT91_REG *) 	0x0000000C) // (RTTC_RTSR) Real-time Status Register

#endif
// -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- 
#define AT91C_RTTC_RTPRES     (0xFFFF <<  0) // (RTTC) Real-time Timer Prescaler Value
#define AT91C_RTTC_ALMIEN     (0x1 << 16) // (RTTC) Alarm Interrupt Enable
#define AT91C_RTTC_RTTINCIEN  (0x1 << 17) // (RTTC) Real Time Timer Increment Interrupt Enable
#define AT91C_RTTC_RTTRST     (0x1 << 18) // (RTTC) Real Time Timer Restart
// -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- 
#define AT91C_RTTC_ALMV       (0x0 <<  0) // (RTTC) Alarm Value
// -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- 
#define AT91C_RTTC_CRTV       (0x0 <<  0) // (RTTC) Current Real-time Value
// -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- 
#define AT91C_RTTC_ALMS       (0x1 <<  0) // (RTTC) Real-time Alarm Status
#define AT91C_RTTC_RTTINC     (0x1 <<  1) // (RTTC) Real-time Timer Increment

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_PITC {
	AT91_REG	 PITC_PIMR; 	// Period Interval Mode Register
	AT91_REG	 PITC_PISR; 	// Period Interval Status Register
	AT91_REG	 PITC_PIVR; 	// Period Interval Value Register
	AT91_REG	 PITC_PIIR; 	// Period Interval Image Register
} AT91S_PITC, *AT91PS_PITC;
#else
#define PITC_PIMR       (AT91_CAST(AT91_REG *) 	0x00000000) // (PITC_PIMR) Period Interval Mode Register
#define PITC_PISR       (AT91_CAST(AT91_REG *) 	0x00000004) // (PITC_PISR) Period Interval Status Register
#define PITC_PIVR       (AT91_CAST(AT91_REG *) 	0x00000008) // (PITC_PIVR) Period Interval Value Register
#define PITC_PIIR       (AT91_CAST(AT91_REG *) 	0x0000000C) // (PITC_PIIR) Period Interval Image Register

#endif
// -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- 
#define AT91C_PITC_PIV        (0xFFFFF <<  0) // (PITC) Periodic Interval Value
#define AT91C_PITC_PITEN      (0x1 << 24) // (PITC) Periodic Interval Timer Enabled
#define AT91C_PITC_PITIEN     (0x1 << 25) // (PITC) Periodic Interval Timer Interrupt Enable
// -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- 
#define AT91C_PITC_PITS       (0x1 <<  0) // (PITC) Periodic Interval Timer Status
// -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- 
#define AT91C_PITC_CPIV       (0xFFFFF <<  0) // (PITC) Current Periodic Interval Value
#define AT91C_PITC_PICNT      (0xFFF << 20) // (PITC) Periodic Interval Counter
// -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_WDTC {
	AT91_REG	 WDTC_WDCR; 	// Watchdog Control Register
	AT91_REG	 WDTC_WDMR; 	// Watchdog Mode Register
	AT91_REG	 WDTC_WDSR; 	// Watchdog Status Register
} AT91S_WDTC, *AT91PS_WDTC;
#else
#define WDTC_WDCR       (AT91_CAST(AT91_REG *) 	0x00000000) // (WDTC_WDCR) Watchdog Control Register
#define WDTC_WDMR       (AT91_CAST(AT91_REG *) 	0x00000004) // (WDTC_WDMR) Watchdog Mode Register
#define WDTC_WDSR       (AT91_CAST(AT91_REG *) 	0x00000008) // (WDTC_WDSR) Watchdog Status Register

#endif
// -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- 
#define AT91C_WDTC_WDRSTT     (0x1 <<  0) // (WDTC) Watchdog Restart
#define AT91C_WDTC_KEY        (0xFF << 24) // (WDTC) Watchdog KEY Password
// -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- 
#define AT91C_WDTC_WDV        (0xFFF <<  0) // (WDTC) Watchdog Timer Restart
#define AT91C_WDTC_WDFIEN     (0x1 << 12) // (WDTC) Watchdog Fault Interrupt Enable
#define AT91C_WDTC_WDRSTEN    (0x1 << 13) // (WDTC) Watchdog Reset Enable
#define AT91C_WDTC_WDRPROC    (0x1 << 14) // (WDTC) Watchdog Timer Restart
#define AT91C_WDTC_WDDIS      (0x1 << 15) // (WDTC) Watchdog Disable
#define AT91C_WDTC_WDD        (0xFFF << 16) // (WDTC) Watchdog Delta Value
#define AT91C_WDTC_WDDBGHLT   (0x1 << 28) // (WDTC) Watchdog Debug Halt
#define AT91C_WDTC_WDIDLEHLT  (0x1 << 29) // (WDTC) Watchdog Idle Halt
// -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- 
#define AT91C_WDTC_WDUNF      (0x1 <<  0) // (WDTC) Watchdog Underflow
#define AT91C_WDTC_WDERR      (0x1 <<  1) // (WDTC) Watchdog Error

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_TC {
	AT91_REG	 TC_CCR; 	// Channel Control Register
	AT91_REG	 TC_CMR; 	// Channel Mode Register (Capture Mode / Waveform Mode)
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 TC_CV; 	// Counter Value
	AT91_REG	 TC_RA; 	// Register A
	AT91_REG	 TC_RB; 	// Register B
	AT91_REG	 TC_RC; 	// Register C
	AT91_REG	 TC_SR; 	// Status Register
	AT91_REG	 TC_IER; 	// Interrupt Enable Register
	AT91_REG	 TC_IDR; 	// Interrupt Disable Register
	AT91_REG	 TC_IMR; 	// Interrupt Mask Register
} AT91S_TC, *AT91PS_TC;
#else
#define TC_CCR          (AT91_CAST(AT91_REG *) 	0x00000000) // (TC_CCR) Channel Control Register
#define TC_CMR          (AT91_CAST(AT91_REG *) 	0x00000004) // (TC_CMR) Channel Mode Register (Capture Mode / Waveform Mode)
#define TC_CV           (AT91_CAST(AT91_REG *) 	0x00000010) // (TC_CV) Counter Value
#define TC_RA           (AT91_CAST(AT91_REG *) 	0x00000014) // (TC_RA) Register A
#define TC_RB           (AT91_CAST(AT91_REG *) 	0x00000018) // (TC_RB) Register B
#define TC_RC           (AT91_CAST(AT91_REG *) 	0x0000001C) // (TC_RC) Register C
#define TC_SR           (AT91_CAST(AT91_REG *) 	0x00000020) // (TC_SR) Status Register
#define TC_IER          (AT91_CAST(AT91_REG *) 	0x00000024) // (TC_IER) Interrupt Enable Register
#define TC_IDR          (AT91_CAST(AT91_REG *) 	0x00000028) // (TC_IDR) Interrupt Disable Register
#define TC_IMR          (AT91_CAST(AT91_REG *) 	0x0000002C) // (TC_IMR) Interrupt Mask Register

#endif
// -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- 
#define AT91C_TC_CLKEN        (0x1 <<  0) // (TC) Counter Clock Enable Command
#define AT91C_TC_CLKDIS       (0x1 <<  1) // (TC) Counter Clock Disable Command
#define AT91C_TC_SWTRG        (0x1 <<  2) // (TC) Software Trigger Command
// -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- 
#define AT91C_TC_CLKS         (0x7 <<  0) // (TC) Clock Selection
#define 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     (0x0) // (TC) Clock selected: TIMER_DIV1_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     (0x1) // (TC) Clock selected: TIMER_DIV2_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     (0x2) // (TC) Clock selected: TIMER_DIV3_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     (0x3) // (TC) Clock selected: TIMER_DIV4_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     (0x4) // (TC) Clock selected: TIMER_DIV5_CLOCK
#define 	AT91C_TC_CLKS_XC0                  (0x5) // (TC) Clock selected: XC0
#define 	AT91C_TC_CLKS_XC1                  (0x6) // (TC) Clock selected: XC1
#define 	AT91C_TC_CLKS_XC2                  (0x7) // (TC) Clock selected: XC2
#define AT91C_TC_CLKI         (0x1 <<  3) // (TC) Clock Invert
#define AT91C_TC_BURST        (0x3 <<  4) // (TC) Burst Signal Selection
#define 	AT91C_TC_BURST_NONE                 (0x0 <<  4) // (TC) The clock is not gated by an external signal
#define 	AT91C_TC_BURST_XC0                  (0x1 <<  4) // (TC) XC0 is ANDed with the selected clock
#define 	AT91C_TC_BURST_XC1                  (0x2 <<  4) // (TC) XC1 is ANDed with the selected clock
#define 	AT91C_TC_BURST_XC2                  (0x3 <<  4) // (TC) XC2 is ANDed with the selected clock
#define AT91C_TC_CPCSTOP      (0x1 <<  6) // (TC) Counter Clock Stopped with RC Compare
#define AT91C_TC_LDBSTOP      (0x1 <<  6) // (TC) Counter Clock Stopped with RB Loading
#define AT91C_TC_CPCDIS       (0x1 <<  7) // (TC) Counter Clock Disable with RC Compare
#define AT91C_TC_LDBDIS       (0x1 <<  7) // (TC) Counter Clock Disabled with RB Loading
#define AT91C_TC_ETRGEDG      (0x3 <<  8) // (TC) External Trigger Edge Selection
#define 	AT91C_TC_ETRGEDG_NONE                 (0x0 <<  8) // (TC) Edge: None
#define 	AT91C_TC_ETRGEDG_RISING               (0x1 <<  8) // (TC) Edge: rising edge
#define 	AT91C_TC_ETRGEDG_FALLING              (0x2 <<  8) // (TC) Edge: falling edge
#define 	AT91C_TC_ETRGEDG_BOTH                 (0x3 <<  8) // (TC) Edge: each edge
#define AT91C_TC_EEVTEDG      (0x3 <<  8) // (TC) External Event Edge Selection
#define 	AT91C_TC_EEVTEDG_NONE                 (0x0 <<  8) // (TC) Edge: None
#define 	AT91C_TC_EEVTEDG_RISING               (0x1 <<  8) // (TC) Edge: rising edge
#define 	AT91C_TC_EEVTEDG_FALLING              (0x2 <<  8) // (TC) Edge: falling edge
#define 	AT91C_TC_EEVTEDG_BOTH                 (0x3 <<  8) // (TC) Edge: each edge
#define AT91C_TC_EEVT         (0x3 << 10) // (TC) External Event  Selection
#define 	AT91C_TC_EEVT_TIOB                 (0x0 << 10) // (TC) Signal selected as external event: TIOB TIOB direction: input
#define 	AT91C_TC_EEVT_XC0                  (0x1 << 10) // (TC) Signal selected as external event: XC0 TIOB direction: output
#define 	AT91C_TC_EEVT_XC1                  (0x2 << 10) // (TC) Signal selected as external event: XC1 TIOB direction: output
#define 	AT91C_TC_EEVT_XC2                  (0x3 << 10) // (TC) Signal selected as external event: XC2 TIOB direction: output
#define AT91C_TC_ABETRG       (0x1 << 10) // (TC) TIOA or TIOB External Trigger Selection
#define AT91C_TC_ENETRG       (0x1 << 12) // (TC) External Event Trigger enable
#define AT91C_TC_WAVESEL      (0x3 << 13) // (TC) Waveform  Selection
#define 	AT91C_TC_WAVESEL_UP                   (0x0 << 13) // (TC) UP mode without atomatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UPDOWN               (0x1 << 13) // (TC) UPDOWN mode without automatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UP_AUTO              (0x2 << 13) // (TC) UP mode with automatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UPDOWN_AUTO          (0x3 << 13) // (TC) UPDOWN mode with automatic trigger on RC Compare
#define AT91C_TC_CPCTRG       (0x1 << 14) // (TC) RC Compare Trigger Enable
#define AT91C_TC_WAVE         (0x1 << 15) // (TC) 
#define AT91C_TC_ACPA         (0x3 << 16) // (TC) RA Compare Effect on TIOA
#define 	AT91C_TC_ACPA_NONE                 (0x0 << 16) // (TC) Effect: none
#define 	AT91C_TC_ACPA_SET                  (0x1 << 16) // (TC) Effect: set
#define 	AT91C_TC_ACPA_CLEAR                (0x2 << 16) // (TC) Effect: clear
#define 	AT91C_TC_ACPA_TOGGLE               (0x3 << 16) // (TC) Effect: toggle
#define AT91C_TC_LDRA         (0x3 << 16) // (TC) RA Loading Selection
#define 	AT91C_TC_LDRA_NONE                 (0x0 << 16) // (TC) Edge: None
#define 	AT91C_TC_LDRA_RISING               (0x1 << 16) // (TC) Edge: rising edge of TIOA
#define 	AT91C_TC_LDRA_FALLING              (0x2 << 16) // (TC) Edge: falling edge of TIOA
#define 	AT91C_TC_LDRA_BOTH                 (0x3 << 16) // (TC) Edge: each edge of TIOA
#define AT91C_TC_ACPC         (0x3 << 18) // (TC) RC Compare Effect on TIOA
#define 	AT91C_TC_ACPC_NONE                 (0x0 << 18) // (TC) Effect: none
#define 	AT91C_TC_ACPC_SET                  (0x1 << 18) // (TC) Effect: set
#define 	AT91C_TC_ACPC_CLEAR                (0x2 << 18) // (TC) Effect: clear
#define 	AT91C_TC_ACPC_TOGGLE               (0x3 << 18) // (TC) Effect: toggle
#define AT91C_TC_LDRB         (0x3 << 18) // (TC) RB Loading Selection
#define 	AT91C_TC_LDRB_NONE                 (0x0 << 18) // (TC) Edge: None
#define 	AT91C_TC_LDRB_RISING               (0x1 << 18) // (TC) Edge: rising edge of TIOA
#define 	AT91C_TC_LDRB_FALLING              (0x2 << 18) // (TC) Edge: falling edge of TIOA
#define 	AT91C_TC_LDRB_BOTH                 (0x3 << 18) // (TC) Edge: each edge of TIOA
#define AT91C_TC_AEEVT        (0x3 << 20) // (TC) External Event Effect on TIOA
#define 	AT91C_TC_AEEVT_NONE                 (0x0 << 20) // (TC) Effect: none
#define 	AT91C_TC_AEEVT_SET                  (0x1 << 20) // (TC) Effect: set
#define 	AT91C_TC_AEEVT_CLEAR                (0x2 << 20) // (TC) Effect: clear
#define 	AT91C_TC_AEEVT_TOGGLE               (0x3 << 20) // (TC) Effect: toggle
#define AT91C_TC_ASWTRG       (0x3 << 22) // (TC) Software Trigger Effect on TIOA
#define 	AT91C_TC_ASWTRG_NONE                 (0x0 << 22) // (TC) Effect: none
#define 	AT91C_TC_ASWTRG_SET                  (0x1 << 22) // (TC) Effect: set
#define 	AT91C_TC_ASWTRG_CLEAR                (0x2 << 22) // (TC) Effect: clear
#define 	AT91C_TC_ASWTRG_TOGGLE               (0x3 << 22) // (TC) Effect: toggle
#define AT91C_TC_BCPB         (0x3 << 24) // (TC) RB Compare Effect on TIOB
#define 	AT91C_TC_BCPB_NONE                 (0x0 << 24) // (TC) Effect: none
#define 	AT91C_TC_BCPB_SET                  (0x1 << 24) // (TC) Effect: set
#define 	AT91C_TC_BCPB_CLEAR                (0x2 << 24) // (TC) Effect: clear
#define 	AT91C_TC_BCPB_TOGGLE               (0x3 << 24) // (TC) Effect: toggle
#define AT91C_TC_BCPC         (0x3 << 26) // (TC) RC Compare Effect on TIOB
#define 	AT91C_TC_BCPC_NONE                 (0x0 << 26) // (TC) Effect: none
#define 	AT91C_TC_BCPC_SET                  (0x1 << 26) // (TC) Effect: set
#define 	AT91C_TC_BCPC_CLEAR                (0x2 << 26) // (TC) Effect: clear
#define 	AT91C_TC_BCPC_TOGGLE               (0x3 << 26) // (TC) Effect: toggle
#define AT91C_TC_BEEVT        (0x3 << 28) // (TC) External Event Effect on TIOB
#define 	AT91C_TC_BEEVT_NONE                 (0x0 << 28) // (TC) Effect: none
#define 	AT91C_TC_BEEVT_SET                  (0x1 << 28) // (TC) Effect: set
#define 	AT91C_TC_BEEVT_CLEAR                (0x2 << 28) // (TC) Effect: clear
#define 	AT91C_TC_BEEVT_TOGGLE               (0x3 << 28) // (TC) Effect: toggle
#define AT91C_TC_BSWTRG       (0x3 << 30) // (TC) Software Trigger Effect on TIOB
#define 	AT91C_TC_BSWTRG_NONE                 (0x0 << 30) // (TC) Effect: none
#define 	AT91C_TC_BSWTRG_SET                  (0x1 << 30) // (TC) Effect: set
#define 	AT91C_TC_BSWTRG_CLEAR                (0x2 << 30) // (TC) Effect: clear
#define 	AT91C_TC_BSWTRG_TOGGLE               (0x3 << 30) // (TC) Effect: toggle
// -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- 
#define AT91C_TC_COVFS        (0x1 <<  0) // (TC) Counter Overflow
#define AT91C_TC_LOVRS        (0x1 <<  1) // (TC) Load Overrun
#define AT91C_TC_CPAS         (0x1 <<  2) // (TC) RA Compare
#define AT91C_TC_CPBS         (0x1 <<  3) // (TC) RB Compare
#define AT91C_TC_CPCS         (0x1 <<  4) // (TC) RC Compare
#define AT91C_TC_LDRAS        (0x1 <<  5) // (TC) RA Loading
#define AT91C_TC_LDRBS        (0x1 <<  6) // (TC) RB Loading
#define AT91C_TC_ETRGS        (0x1 <<  7) // (TC) External Trigger
#define AT91C_TC_CLKSTA       (0x1 << 16) // (TC) Clock Enabling
#define AT91C_TC_MTIOA        (0x1 << 17) // (TC) TIOA Mirror
#define AT91C_TC_MTIOB        (0x1 << 18) // (TC) TIOA Mirror
// -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- 
// -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- 
// -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Timer Counter Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_TCB {
	AT91S_TC	 TCB_TC0; 	// TC Channel 0
	AT91_REG	 Reserved0[4]; 	// 
	AT91S_TC	 TCB_TC1; 	// TC Channel 1
	AT91_REG	 Reserved1[4]; 	// 
	AT91S_TC	 TCB_TC2; 	// TC Channel 2
	AT91_REG	 Reserved2[4]; 	// 
	AT91_REG	 TCB_BCR; 	// TC Block Control Register
	AT91_REG	 TCB_BMR; 	// TC Block Mode Register
	AT91_REG	 Reserved3[9]; 	// 
	AT91_REG	 TCB_ADDRSIZE; 	// TC ADDRSIZE REGISTER 
	AT91_REG	 TCB_IPNAME1; 	// TC IPNAME1 REGISTER 
	AT91_REG	 TCB_IPNAME2; 	// TC IPNAME2 REGISTER 
	AT91_REG	 TCB_FEATURES; 	// TC FEATURES REGISTER 
	AT91_REG	 TCB_VER; 	//  Version Register
} AT91S_TCB, *AT91PS_TCB;
#else
#define TCB_BCR         (AT91_CAST(AT91_REG *) 	0x000000C0) // (TCB_BCR) TC Block Control Register
#define TCB_BMR         (AT91_CAST(AT91_REG *) 	0x000000C4) // (TCB_BMR) TC Block Mode Register
#define TC_ADDRSIZE     (AT91_CAST(AT91_REG *) 	0x000000EC) // (TC_ADDRSIZE) TC ADDRSIZE REGISTER 
#define TC_IPNAME1      (AT91_CAST(AT91_REG *) 	0x000000F0) // (TC_IPNAME1) TC IPNAME1 REGISTER 
#define TC_IPNAME2      (AT91_CAST(AT91_REG *) 	0x000000F4) // (TC_IPNAME2) TC IPNAME2 REGISTER 
#define TC_FEATURES     (AT91_CAST(AT91_REG *) 	0x000000F8) // (TC_FEATURES) TC FEATURES REGISTER 
#define TC_VER          (AT91_CAST(AT91_REG *) 	0x000000FC) // (TC_VER)  Version Register

#endif
// -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- 
#define AT91C_TCB_SYNC        (0x1 <<  0) // (TCB) Synchro Command
// -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- 
#define AT91C_TCB_TC0XC0S     (0x3 <<  0) // (TCB) External Clock Signal 0 Selection
#define 	AT91C_TCB_TC0XC0S_TCLK0                (0x0) // (TCB) TCLK0 connected to XC0
#define 	AT91C_TCB_TC0XC0S_NONE                 (0x1) // (TCB) None signal connected to XC0
#define 	AT91C_TCB_TC0XC0S_TIOA1                (0x2) // (TCB) TIOA1 connected to XC0
#define 	AT91C_TCB_TC0XC0S_TIOA2                (0x3) // (TCB) TIOA2 connected to XC0
#define AT91C_TCB_TC1XC1S     (0x3 <<  2) // (TCB) External Clock Signal 1 Selection
#define 	AT91C_TCB_TC1XC1S_TCLK1                (0x0 <<  2) // (TCB) TCLK1 connected to XC1
#define 	AT91C_TCB_TC1XC1S_NONE                 (0x1 <<  2) // (TCB) None signal connected to XC1
#define 	AT91C_TCB_TC1XC1S_TIOA0                (0x2 <<  2) // (TCB) TIOA0 connected to XC1
#define 	AT91C_TCB_TC1XC1S_TIOA2                (0x3 <<  2) // (TCB) TIOA2 connected to XC1
#define AT91C_TCB_TC2XC2S     (0x3 <<  4) // (TCB) External Clock Signal 2 Selection
#define 	AT91C_TCB_TC2XC2S_TCLK2                (0x0 <<  4) // (TCB) TCLK2 connected to XC2
#define 	AT91C_TCB_TC2XC2S_NONE                 (0x1 <<  4) // (TCB) None signal connected to XC2
#define 	AT91C_TCB_TC2XC2S_TIOA0                (0x2 <<  4) // (TCB) TIOA0 connected to XC2
#define 	AT91C_TCB_TC2XC2S_TIOA1                (0x3 <<  4) // (TCB) TIOA2 connected to XC2

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Multimedia Card Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_MCI {
	AT91_REG	 MCI_CR; 	// MCI Control Register
	AT91_REG	 MCI_MR; 	// MCI Mode Register
	AT91_REG	 MCI_DTOR; 	// MCI Data Timeout Register
	AT91_REG	 MCI_SDCR; 	// MCI SD Card Register
	AT91_REG	 MCI_ARGR; 	// MCI Argument Register
	AT91_REG	 MCI_CMDR; 	// MCI Command Register
	AT91_REG	 MCI_BLKR; 	// MCI Block Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 MCI_RSPR[4]; 	// MCI Response Register
	AT91_REG	 MCI_RDR; 	// MCI Receive Data Register
	AT91_REG	 MCI_TDR; 	// MCI Transmit Data Register
	AT91_REG	 Reserved1[2]; 	// 
	AT91_REG	 MCI_SR; 	// MCI Status Register
	AT91_REG	 MCI_IER; 	// MCI Interrupt Enable Register
	AT91_REG	 MCI_IDR; 	// MCI Interrupt Disable Register
	AT91_REG	 MCI_IMR; 	// MCI Interrupt Mask Register
	AT91_REG	 Reserved2[43]; 	// 
	AT91_REG	 MCI_VR; 	// MCI Version Register
	AT91_REG	 MCI_RPR; 	// Receive Pointer Register
	AT91_REG	 MCI_RCR; 	// Receive Counter Register
	AT91_REG	 MCI_TPR; 	// Transmit Pointer Register
	AT91_REG	 MCI_TCR; 	// Transmit Counter Register
	AT91_REG	 MCI_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 MCI_RNCR; 	// Receive Next Counter Register
	AT91_REG	 MCI_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 MCI_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 MCI_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 MCI_PTSR; 	// PDC Transfer Status Register
} AT91S_MCI, *AT91PS_MCI;
#else
#define MCI_CR          (AT91_CAST(AT91_REG *) 	0x00000000) // (MCI_CR) MCI Control Register
#define MCI_MR          (AT91_CAST(AT91_REG *) 	0x00000004) // (MCI_MR) MCI Mode Register
#define MCI_DTOR        (AT91_CAST(AT91_REG *) 	0x00000008) // (MCI_DTOR) MCI Data Timeout Register
#define MCI_SDCR        (AT91_CAST(AT91_REG *) 	0x0000000C) // (MCI_SDCR) MCI SD Card Register
#define MCI_ARGR        (AT91_CAST(AT91_REG *) 	0x00000010) // (MCI_ARGR) MCI Argument Register
#define MCI_CMDR        (AT91_CAST(AT91_REG *) 	0x00000014) // (MCI_CMDR) MCI Command Register
#define MCI_BLKR        (AT91_CAST(AT91_REG *) 	0x00000018) // (MCI_BLKR) MCI Block Register
#define MCI_RSPR        (AT91_CAST(AT91_REG *) 	0x00000020) // (MCI_RSPR) MCI Response Register
#define MCI_RDR         (AT91_CAST(AT91_REG *) 	0x00000030) // (MCI_RDR) MCI Receive Data Register
#define MCI_TDR         (AT91_CAST(AT91_REG *) 	0x00000034) // (MCI_TDR) MCI Transmit Data Register
#define MCI_SR          (AT91_CAST(AT91_REG *) 	0x00000040) // (MCI_SR) MCI Status Register
#define MCI_IER         (AT91_CAST(AT91_REG *) 	0x00000044) // (MCI_IER) MCI Interrupt Enable Register
#define MCI_IDR         (AT91_CAST(AT91_REG *) 	0x00000048) // (MCI_IDR) MCI Interrupt Disable Register
#define MCI_IMR         (AT91_CAST(AT91_REG *) 	0x0000004C) // (MCI_IMR) MCI Interrupt Mask Register
#define MCI_VR          (AT91_CAST(AT91_REG *) 	0x000000FC) // (MCI_VR) MCI Version Register

#endif
// -------- MCI_CR : (MCI Offset: 0x0) MCI Control Register -------- 
#define AT91C_MCI_MCIEN       (0x1 <<  0) // (MCI) Multimedia Interface Enable
#define 	AT91C_MCI_MCIEN_0                    (0x0) // (MCI) No effect
#define 	AT91C_MCI_MCIEN_1                    (0x1) // (MCI) Enable the MultiMedia Interface if MCIDIS is 0
#define AT91C_MCI_MCIDIS      (0x1 <<  1) // (MCI) Multimedia Interface Disable
#define 	AT91C_MCI_MCIDIS_0                    (0x0 <<  1) // (MCI) No effect
#define 	AT91C_MCI_MCIDIS_1                    (0x1 <<  1) // (MCI) Disable the MultiMedia Interface
#define AT91C_MCI_PWSEN       (0x1 <<  2) // (MCI) Power Save Mode Enable
#define 	AT91C_MCI_PWSEN_0                    (0x0 <<  2) // (MCI) No effect
#define 	AT91C_MCI_PWSEN_1                    (0x1 <<  2) // (MCI) Enable the Power-saving mode if PWSDIS is 0.
#define AT91C_MCI_PWSDIS      (0x1 <<  3) // (MCI) Power Save Mode Disable
#define 	AT91C_MCI_PWSDIS_0                    (0x0 <<  3) // (MCI) No effect
#define 	AT91C_MCI_PWSDIS_1                    (0x1 <<  3) // (MCI) Disable the Power-saving mode.
#define AT91C_MCI_SWRST       (0x1 <<  7) // (MCI) MCI Software reset
#define 	AT91C_MCI_SWRST_0                    (0x0 <<  7) // (MCI) No effect
#define 	AT91C_MCI_SWRST_1                    (0x1 <<  7) // (MCI) Resets the MCI
// -------- MCI_MR : (MCI Offset: 0x4) MCI Mode Register -------- 
#define AT91C_MCI_CLKDIV      (0xFF <<  0) // (MCI) Clock Divider
#define AT91C_MCI_PWSDIV      (0x7 <<  8) // (MCI) Power Saving Divider
#define AT91C_MCI_RDPROOF     (0x1 << 11) // (MCI) Read Proof Enable
#define 	AT91C_MCI_RDPROOF_DISABLE              (0x0 << 11) // (MCI) Disables Read Proof
#define 	AT91C_MCI_RDPROOF_ENABLE               (0x1 << 11) // (MCI) Enables Read Proof
#define AT91C_MCI_WRPROOF     (0x1 << 12) // (MCI) Write Proof Enable
#define 	AT91C_MCI_WRPROOF_DISABLE              (0x0 << 12) // (MCI) Disables Write Proof
#define 	AT91C_MCI_WRPROOF_ENABLE               (0x1 << 12) // (MCI) Enables Write Proof
#define AT91C_MCI_PDCFBYTE    (0x1 << 13) // (MCI) PDC Force Byte Transfer
#define 	AT91C_MCI_PDCFBYTE_DISABLE              (0x0 << 13) // (MCI) Disables PDC Force Byte Transfer
#define 	AT91C_MCI_PDCFBYTE_ENABLE               (0x1 << 13) // (MCI) Enables PDC Force Byte Transfer
#define AT91C_MCI_PDCPADV     (0x1 << 14) // (MCI) PDC Padding Value
#define AT91C_MCI_PDCMODE     (0x1 << 15) // (MCI) PDC Oriented Mode
#define 	AT91C_MCI_PDCMODE_DISABLE              (0x0 << 15) // (MCI) Disables PDC Transfer
#define 	AT91C_MCI_PDCMODE_ENABLE               (0x1 << 15) // (MCI) Enables PDC Transfer
#define AT91C_MCI_BLKLEN      (0xFFFF << 16) // (MCI) Data Block Length
// -------- MCI_DTOR : (MCI Offset: 0x8) MCI Data Timeout Register -------- 
#define AT91C_MCI_DTOCYC      (0xF <<  0) // (MCI) Data Timeout Cycle Number
#define AT91C_MCI_DTOMUL      (0x7 <<  4) // (MCI) Data Timeout Multiplier
#define 	AT91C_MCI_DTOMUL_1                    (0x0 <<  4) // (MCI) DTOCYC x 1
#define 	AT91C_MCI_DTOMUL_16                   (0x1 <<  4) // (MCI) DTOCYC x 16
#define 	AT91C_MCI_DTOMUL_128                  (0x2 <<  4) // (MCI) DTOCYC x 128
#define 	AT91C_MCI_DTOMUL_256                  (0x3 <<  4) // (MCI) DTOCYC x 256
#define 	AT91C_MCI_DTOMUL_1024                 (0x4 <<  4) // (MCI) DTOCYC x 1024
#define 	AT91C_MCI_DTOMUL_4096                 (0x5 <<  4) // (MCI) DTOCYC x 4096
#define 	AT91C_MCI_DTOMUL_65536                (0x6 <<  4) // (MCI) DTOCYC x 65536
#define 	AT91C_MCI_DTOMUL_1048576              (0x7 <<  4) // (MCI) DTOCYC x 1048576
// -------- MCI_SDCR : (MCI Offset: 0xc) MCI SD Card Register -------- 
#define AT91C_MCI_SCDSEL      (0x3 <<  0) // (MCI) SD Card Selector
#define 	AT91C_MCI_SCDSEL_SLOTA                (0x0) // (MCI) Slot A selected
#define 	AT91C_MCI_SCDSEL_SLOTB                (0x1) // (MCI) Slot B selected
#define 	AT91C_MCI_SCDSEL_RESERVED1            (0x2) // (MCI) 
#define 	AT91C_MCI_SCDSEL_RESERVED2            (0x3) // (MCI) 
#define AT91C_MCI_SCDBUS      (0x1 <<  7) // (MCI) SDCard/SDIO Bus Width
#define 	AT91C_MCI_SCDBUS_1BIT                 (0x0 <<  7) // (MCI) 1-bit data bus
#define 	AT91C_MCI_SCDBUS_4BITS                (0x1 <<  7) // (MCI) 4-bits data bus
// -------- MCI_CMDR : (MCI Offset: 0x14) MCI Command Register -------- 
#define AT91C_MCI_CMDNB       (0x3F <<  0) // (MCI) Command Number
#define AT91C_MCI_RSPTYP      (0x3 <<  6) // (MCI) Response Type
#define 	AT91C_MCI_RSPTYP_NO                   (0x0 <<  6) // (MCI) No response
#define 	AT91C_MCI_RSPTYP_48                   (0x1 <<  6) // (MCI) 48-bit response
#define 	AT91C_MCI_RSPTYP_136                  (0x2 <<  6) // (MCI) 136-bit response
#define AT91C_MCI_SPCMD       (0x7 <<  8) // (MCI) Special CMD
#define 	AT91C_MCI_SPCMD_NONE                 (0x0 <<  8) // (MCI) Not a special CMD
#define 	AT91C_MCI_SPCMD_INIT                 (0x1 <<  8) // (MCI) Initialization CMD
#define 	AT91C_MCI_SPCMD_SYNC                 (0x2 <<  8) // (MCI) Synchronized CMD
#define 	AT91C_MCI_SPCMD_IT_CMD               (0x4 <<  8) // (MCI) Interrupt command
#define 	AT91C_MCI_SPCMD_IT_REP               (0x5 <<  8) // (MCI) Interrupt response
#define AT91C_MCI_OPDCMD      (0x1 << 11) // (MCI) Open Drain Command
#define 	AT91C_MCI_OPDCMD_PUSHPULL             (0x0 << 11) // (MCI) Push/pull command
#define 	AT91C_MCI_OPDCMD_OPENDRAIN            (0x1 << 11) // (MCI) Open drain command
#define AT91C_MCI_MAXLAT      (0x1 << 12) // (MCI) Maximum Latency for Command to respond
#define 	AT91C_MCI_MAXLAT_5                    (0x0 << 12) // (MCI) 5 cycles maximum latency
#define 	AT91C_MCI_MAXLAT_64                   (0x1 << 12) // (MCI) 64 cycles maximum latency
#define AT91C_MCI_TRCMD       (0x3 << 16) // (MCI) Transfer CMD
#define 	AT91C_MCI_TRCMD_NO                   (0x0 << 16) // (MCI) No transfer
#define 	AT91C_MCI_TRCMD_START                (0x1 << 16) // (MCI) Start transfer
#define 	AT91C_MCI_TRCMD_STOP                 (0x2 << 16) // (MCI) Stop transfer
#define AT91C_MCI_TRDIR       (0x1 << 18) // (MCI) Transfer Direction
#define 	AT91C_MCI_TRDIR_WRITE                (0x0 << 18) // (MCI) Write
#define 	AT91C_MCI_TRDIR_READ                 (0x1 << 18) // (MCI) Read
#define AT91C_MCI_TRTYP       (0x7 << 19) // (MCI) Transfer Type
#define 	AT91C_MCI_TRTYP_BLOCK                (0x0 << 19) // (MCI) MMC/SDCard Single Block Transfer type
#define 	AT91C_MCI_TRTYP_MULTIPLE             (0x1 << 19) // (MCI) MMC/SDCard Multiple Block transfer type
#define 	AT91C_MCI_TRTYP_STREAM               (0x2 << 19) // (MCI) MMC Stream transfer type
#define 	AT91C_MCI_TRTYP_SDIO_BYTE            (0x4 << 19) // (MCI) SDIO Byte transfer type
#define 	AT91C_MCI_TRTYP_SDIO_BLOCK           (0x5 << 19) // (MCI) SDIO Block transfer type
#define AT91C_MCI_IOSPCMD     (0x3 << 24) // (MCI) SDIO Special Command
#define 	AT91C_MCI_IOSPCMD_NONE                 (0x0 << 24) // (MCI) NOT a special command
#define 	AT91C_MCI_IOSPCMD_SUSPEND              (0x1 << 24) // (MCI) SDIO Suspend Command
#define 	AT91C_MCI_IOSPCMD_RESUME               (0x2 << 24) // (MCI) SDIO Resume Command
// -------- MCI_BLKR : (MCI Offset: 0x18) MCI Block Register -------- 
#define AT91C_MCI_BCNT        (0xFFFF <<  0) // (MCI) MMC/SDIO Block Count / SDIO Byte Count
// -------- MCI_SR : (MCI Offset: 0x40) MCI Status Register -------- 
#define AT91C_MCI_CMDRDY      (0x1 <<  0) // (MCI) Command Ready flag
#define AT91C_MCI_RXRDY       (0x1 <<  1) // (MCI) RX Ready flag
#define AT91C_MCI_TXRDY       (0x1 <<  2) // (MCI) TX Ready flag
#define AT91C_MCI_BLKE        (0x1 <<  3) // (MCI) Data Block Transfer Ended flag
#define AT91C_MCI_DTIP        (0x1 <<  4) // (MCI) Data Transfer in Progress flag
#define AT91C_MCI_NOTBUSY     (0x1 <<  5) // (MCI) Data Line Not Busy flag
#define AT91C_MCI_ENDRX       (0x1 <<  6) // (MCI) End of RX Buffer flag
#define AT91C_MCI_ENDTX       (0x1 <<  7) // (MCI) End of TX Buffer flag
#define AT91C_MCI_SDIOIRQA    (0x1 <<  8) // (MCI) SDIO Interrupt for Slot A
#define AT91C_MCI_SDIOIRQB    (0x1 <<  9) // (MCI) SDIO Interrupt for Slot B
#define AT91C_MCI_SDIOIRQC    (0x1 << 10) // (MCI) SDIO Interrupt for Slot C
#define AT91C_MCI_SDIOIRQD    (0x1 << 11) // (MCI) SDIO Interrupt for Slot D
#define AT91C_MCI_RXBUFF      (0x1 << 14) // (MCI) RX Buffer Full flag
#define AT91C_MCI_TXBUFE      (0x1 << 15) // (MCI) TX Buffer Empty flag
#define AT91C_MCI_RINDE       (0x1 << 16) // (MCI) Response Index Error flag
#define AT91C_MCI_RDIRE       (0x1 << 17) // (MCI) Response Direction Error flag
#define AT91C_MCI_RCRCE       (0x1 << 18) // (MCI) Response CRC Error flag
#define AT91C_MCI_RENDE       (0x1 << 19) // (MCI) Response End Bit Error flag
#define AT91C_MCI_RTOE        (0x1 << 20) // (MCI) Response Time-out Error flag
#define AT91C_MCI_DCRCE       (0x1 << 21) // (MCI) data CRC Error flag
#define AT91C_MCI_DTOE        (0x1 << 22) // (MCI) Data timeout Error flag
#define AT91C_MCI_OVRE        (0x1 << 30) // (MCI) Overrun flag
#define AT91C_MCI_UNRE        (0x1 << 31) // (MCI) Underrun flag
// -------- MCI_IER : (MCI Offset: 0x44) MCI Interrupt Enable Register -------- 
// -------- MCI_IDR : (MCI Offset: 0x48) MCI Interrupt Disable Register -------- 
// -------- MCI_IMR : (MCI Offset: 0x4c) MCI Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Two-wire Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_TWI {
	AT91_REG	 TWI_CR; 	// Control Register
	AT91_REG	 TWI_MMR; 	// Master Mode Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 TWI_IADR; 	// Internal Address Register
	AT91_REG	 TWI_CWGR; 	// Clock Waveform Generator Register
	AT91_REG	 Reserved1[3]; 	// 
	AT91_REG	 TWI_SR; 	// Status Register
	AT91_REG	 TWI_IER; 	// Interrupt Enable Register
	AT91_REG	 TWI_IDR; 	// Interrupt Disable Register
	AT91_REG	 TWI_IMR; 	// Interrupt Mask Register
	AT91_REG	 TWI_RHR; 	// Receive Holding Register
	AT91_REG	 TWI_THR; 	// Transmit Holding Register
	AT91_REG	 Reserved2[50]; 	// 
	AT91_REG	 TWI_RPR; 	// Receive Pointer Register
	AT91_REG	 TWI_RCR; 	// Receive Counter Register
	AT91_REG	 TWI_TPR; 	// Transmit Pointer Register
	AT91_REG	 TWI_TCR; 	// Transmit Counter Register
	AT91_REG	 TWI_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 TWI_RNCR; 	// Receive Next Counter Register
	AT91_REG	 TWI_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 TWI_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 TWI_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 TWI_PTSR; 	// PDC Transfer Status Register
} AT91S_TWI, *AT91PS_TWI;
#else
#define TWI_CR          (AT91_CAST(AT91_REG *) 	0x00000000) // (TWI_CR) Control Register
#define TWI_MMR         (AT91_CAST(AT91_REG *) 	0x00000004) // (TWI_MMR) Master Mode Register
#define TWI_IADR        (AT91_CAST(AT91_REG *) 	0x0000000C) // (TWI_IADR) Internal Address Register
#define TWI_CWGR        (AT91_CAST(AT91_REG *) 	0x00000010) // (TWI_CWGR) Clock Waveform Generator Register
#define TWI_SR          (AT91_CAST(AT91_REG *) 	0x00000020) // (TWI_SR) Status Register
#define TWI_IER         (AT91_CAST(AT91_REG *) 	0x00000024) // (TWI_IER) Interrupt Enable Register
#define TWI_IDR         (AT91_CAST(AT91_REG *) 	0x00000028) // (TWI_IDR) Interrupt Disable Register
#define TWI_IMR         (AT91_CAST(AT91_REG *) 	0x0000002C) // (TWI_IMR) Interrupt Mask Register
#define TWI_RHR         (AT91_CAST(AT91_REG *) 	0x00000030) // (TWI_RHR) Receive Holding Register
#define TWI_THR         (AT91_CAST(AT91_REG *) 	0x00000034) // (TWI_THR) Transmit Holding Register

#endif
// -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- 
#define AT91C_TWI_START       (0x1 <<  0) // (TWI) Send a START Condition
#define AT91C_TWI_STOP        (0x1 <<  1) // (TWI) Send a STOP Condition
#define AT91C_TWI_MSEN        (0x1 <<  2) // (TWI) TWI Master Transfer Enabled
#define AT91C_TWI_MSDIS       (0x1 <<  3) // (TWI) TWI Master Transfer Disabled
#define AT91C_TWI_SWRST       (0x1 <<  7) // (TWI) Software Reset
// -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- 
#define AT91C_TWI_IADRSZ      (0x3 <<  8) // (TWI) Internal Device Address Size
#define 	AT91C_TWI_IADRSZ_NO                   (0x0 <<  8) // (TWI) No internal device address
#define 	AT91C_TWI_IADRSZ_1_BYTE               (0x1 <<  8) // (TWI) One-byte internal device address
#define 	AT91C_TWI_IADRSZ_2_BYTE               (0x2 <<  8) // (TWI) Two-byte internal device address
#define 	AT91C_TWI_IADRSZ_3_BYTE               (0x3 <<  8) // (TWI) Three-byte internal device address
#define AT91C_TWI_MREAD       (0x1 << 12) // (TWI) Master Read Direction
#define AT91C_TWI_DADR        (0x7F << 16) // (TWI) Device Address
// -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- 
#define AT91C_TWI_CLDIV       (0xFF <<  0) // (TWI) Clock Low Divider
#define AT91C_TWI_CHDIV       (0xFF <<  8) // (TWI) Clock High Divider
#define AT91C_TWI_CKDIV       (0x7 << 16) // (TWI) Clock Divider
// -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- 
#define AT91C_TWI_TXCOMP      (0x1 <<  0) // (TWI) Transmission Completed
#define AT91C_TWI_RXRDY       (0x1 <<  1) // (TWI) Receive holding register ReaDY
#define AT91C_TWI_TXRDY       (0x1 <<  2) // (TWI) Transmit holding register ReaDY
#define AT91C_TWI_OVRE        (0x1 <<  6) // (TWI) Overrun Error
#define AT91C_TWI_UNRE        (0x1 <<  7) // (TWI) Underrun Error
#define AT91C_TWI_NACK        (0x1 <<  8) // (TWI) Not Acknowledged
#define AT91C_TWI_ENDRX       (0x1 << 12) // (TWI) 
#define AT91C_TWI_ENDTX       (0x1 << 13) // (TWI) 
#define AT91C_TWI_RXBUFF      (0x1 << 14) // (TWI) 
#define AT91C_TWI_TXBUFE      (0x1 << 15) // (TWI) 
// -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- 
// -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- 
// -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Usart
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_USART {
	AT91_REG	 US_CR; 	// Control Register
	AT91_REG	 US_MR; 	// Mode Register
	AT91_REG	 US_IER; 	// Interrupt Enable Register
	AT91_REG	 US_IDR; 	// Interrupt Disable Register
	AT91_REG	 US_IMR; 	// Interrupt Mask Register
	AT91_REG	 US_CSR; 	// Channel Status Register
	AT91_REG	 US_RHR; 	// Receiver Holding Register
	AT91_REG	 US_THR; 	// Transmitter Holding Register
	AT91_REG	 US_BRGR; 	// Baud Rate Generator Register
	AT91_REG	 US_RTOR; 	// Receiver Time-out Register
	AT91_REG	 US_TTGR; 	// Transmitter Time-guard Register
	AT91_REG	 Reserved0[5]; 	// 
	AT91_REG	 US_FIDI; 	// FI_DI_Ratio Register
	AT91_REG	 US_NER; 	// Nb Errors Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 US_IF; 	// IRDA_FILTER Register
	AT91_REG	 Reserved2[44]; 	// 
	AT91_REG	 US_RPR; 	// Receive Pointer Register
	AT91_REG	 US_RCR; 	// Receive Counter Register
	AT91_REG	 US_TPR; 	// Transmit Pointer Register
	AT91_REG	 US_TCR; 	// Transmit Counter Register
	AT91_REG	 US_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 US_RNCR; 	// Receive Next Counter Register
	AT91_REG	 US_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 US_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 US_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 US_PTSR; 	// PDC Transfer Status Register
} AT91S_USART, *AT91PS_USART;
#else
#define US_CR           (AT91_CAST(AT91_REG *) 	0x00000000) // (US_CR) Control Register
#define US_MR           (AT91_CAST(AT91_REG *) 	0x00000004) // (US_MR) Mode Register
#define US_IER          (AT91_CAST(AT91_REG *) 	0x00000008) // (US_IER) Interrupt Enable Register
#define US_IDR          (AT91_CAST(AT91_REG *) 	0x0000000C) // (US_IDR) Interrupt Disable Register
#define US_IMR          (AT91_CAST(AT91_REG *) 	0x00000010) // (US_IMR) Interrupt Mask Register
#define US_CSR          (AT91_CAST(AT91_REG *) 	0x00000014) // (US_CSR) Channel Status Register
#define US_RHR          (AT91_CAST(AT91_REG *) 	0x00000018) // (US_RHR) Receiver Holding Register
#define US_THR          (AT91_CAST(AT91_REG *) 	0x0000001C) // (US_THR) Transmitter Holding Register
#define US_BRGR         (AT91_CAST(AT91_REG *) 	0x00000020) // (US_BRGR) Baud Rate Generator Register
#define US_RTOR         (AT91_CAST(AT91_REG *) 	0x00000024) // (US_RTOR) Receiver Time-out Register
#define US_TTGR         (AT91_CAST(AT91_REG *) 	0x00000028) // (US_TTGR) Transmitter Time-guard Register
#define US_FIDI         (AT91_CAST(AT91_REG *) 	0x00000040) // (US_FIDI) FI_DI_Ratio Register
#define US_NER          (AT91_CAST(AT91_REG *) 	0x00000044) // (US_NER) Nb Errors Register
#define US_IF           (AT91_CAST(AT91_REG *) 	0x0000004C) // (US_IF) IRDA_FILTER Register

#endif
// -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- 
#define AT91C_US_STTBRK       (0x1 <<  9) // (USART) Start Break
#define AT91C_US_STPBRK       (0x1 << 10) // (USART) Stop Break
#define AT91C_US_STTTO        (0x1 << 11) // (USART) Start Time-out
#define AT91C_US_SENDA        (0x1 << 12) // (USART) Send Address
#define AT91C_US_RSTIT        (0x1 << 13) // (USART) Reset Iterations
#define AT91C_US_RSTNACK      (0x1 << 14) // (USART) Reset Non Acknowledge
#define AT91C_US_RETTO        (0x1 << 15) // (USART) Rearm Time-out
#define AT91C_US_DTREN        (0x1 << 16) // (USART) Data Terminal ready Enable
#define AT91C_US_DTRDIS       (0x1 << 17) // (USART) Data Terminal ready Disable
#define AT91C_US_RTSEN        (0x1 << 18) // (USART) Request to Send enable
#define AT91C_US_RTSDIS       (0x1 << 19) // (USART) Request to Send Disable
// -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- 
#define AT91C_US_USMODE       (0xF <<  0) // (USART) Usart mode
#define 	AT91C_US_USMODE_NORMAL               (0x0) // (USART) Normal
#define 	AT91C_US_USMODE_RS485                (0x1) // (USART) RS485
#define 	AT91C_US_USMODE_HWHSH                (0x2) // (USART) Hardware Handshaking
#define 	AT91C_US_USMODE_MODEM                (0x3) // (USART) Modem
#define 	AT91C_US_USMODE_ISO7816_0            (0x4) // (USART) ISO7816 protocol: T = 0
#define 	AT91C_US_USMODE_ISO7816_1            (0x6) // (USART) ISO7816 protocol: T = 1
#define 	AT91C_US_USMODE_IRDA                 (0x8) // (USART) IrDA
#define 	AT91C_US_USMODE_SWHSH                (0xC) // (USART) Software Handshaking
#define AT91C_US_CLKS         (0x3 <<  4) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CLKS_CLOCK                (0x0 <<  4) // (USART) Clock
#define 	AT91C_US_CLKS_FDIV1                (0x1 <<  4) // (USART) fdiv1
#define 	AT91C_US_CLKS_SLOW                 (0x2 <<  4) // (USART) slow_clock (ARM)
#define 	AT91C_US_CLKS_EXT                  (0x3 <<  4) // (USART) External (SCK)
#define AT91C_US_CHRL         (0x3 <<  6) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CHRL_5_BITS               (0x0 <<  6) // (USART) Character Length: 5 bits
#define 	AT91C_US_CHRL_6_BITS               (0x1 <<  6) // (USART) Character Length: 6 bits
#define 	AT91C_US_CHRL_7_BITS               (0x2 <<  6) // (USART) Character Length: 7 bits
#define 	AT91C_US_CHRL_8_BITS               (0x3 <<  6) // (USART) Character Length: 8 bits
#define AT91C_US_SYNC         (0x1 <<  8) // (USART) Synchronous Mode Select
#define AT91C_US_NBSTOP       (0x3 << 12) // (USART) Number of Stop bits
#define 	AT91C_US_NBSTOP_1_BIT                (0x0 << 12) // (USART) 1 stop bit
#define 	AT91C_US_NBSTOP_15_BIT               (0x1 << 12) // (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits
#define 	AT91C_US_NBSTOP_2_BIT                (0x2 << 12) // (USART) 2 stop bits
#define AT91C_US_MSBF         (0x1 << 16) // (USART) Bit Order
#define AT91C_US_MODE9        (0x1 << 17) // (USART) 9-bit Character length
#define AT91C_US_CKLO         (0x1 << 18) // (USART) Clock Output Select
#define AT91C_US_OVER         (0x1 << 19) // (USART) Over Sampling Mode
#define AT91C_US_INACK        (0x1 << 20) // (USART) Inhibit Non Acknowledge
#define AT91C_US_DSNACK       (0x1 << 21) // (USART) Disable Successive NACK
#define AT91C_US_MAX_ITER     (0x1 << 24) // (USART) Number of Repetitions
#define AT91C_US_FILTER       (0x1 << 28) // (USART) Receive Line Filter
// -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define AT91C_US_RXBRK        (0x1 <<  2) // (USART) Break Received/End of Break
#define AT91C_US_TIMEOUT      (0x1 <<  8) // (USART) Receiver Time-out
#define AT91C_US_ITERATION    (0x1 << 10) // (USART) Max number of Repetitions Reached
#define AT91C_US_NACK         (0x1 << 13) // (USART) Non Acknowledge
#define AT91C_US_RIIC         (0x1 << 16) // (USART) Ring INdicator Input Change Flag
#define AT91C_US_DSRIC        (0x1 << 17) // (USART) Data Set Ready Input Change Flag
#define AT91C_US_DCDIC        (0x1 << 18) // (USART) Data Carrier Flag
#define AT91C_US_CTSIC        (0x1 << 19) // (USART) Clear To Send Input Change Flag
// -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- 
#define AT91C_US_RI           (0x1 << 20) // (USART) Image of RI Input
#define AT91C_US_DSR          (0x1 << 21) // (USART) Image of DSR Input
#define AT91C_US_DCD          (0x1 << 22) // (USART) Image of DCD Input
#define AT91C_US_CTS          (0x1 << 23) // (USART) Image of CTS Input

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Serial Parallel Interface
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_SPI {
	AT91_REG	 SPI_CR; 	// Control Register
	AT91_REG	 SPI_MR; 	// Mode Register
	AT91_REG	 SPI_RDR; 	// Receive Data Register
	AT91_REG	 SPI_TDR; 	// Transmit Data Register
	AT91_REG	 SPI_SR; 	// Status Register
	AT91_REG	 SPI_IER; 	// Interrupt Enable Register
	AT91_REG	 SPI_IDR; 	// Interrupt Disable Register
	AT91_REG	 SPI_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved0[4]; 	// 
	AT91_REG	 SPI_CSR[4]; 	// Chip Select Register
	AT91_REG	 Reserved1[48]; 	// 
	AT91_REG	 SPI_RPR; 	// Receive Pointer Register
	AT91_REG	 SPI_RCR; 	// Receive Counter Register
	AT91_REG	 SPI_TPR; 	// Transmit Pointer Register
	AT91_REG	 SPI_TCR; 	// Transmit Counter Register
	AT91_REG	 SPI_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 SPI_RNCR; 	// Receive Next Counter Register
	AT91_REG	 SPI_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 SPI_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 SPI_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 SPI_PTSR; 	// PDC Transfer Status Register
} AT91S_SPI, *AT91PS_SPI;
#else
#define SPI_CR          (AT91_CAST(AT91_REG *) 	0x00000000) // (SPI_CR) Control Register
#define SPI_MR          (AT91_CAST(AT91_REG *) 	0x00000004) // (SPI_MR) Mode Register
#define SPI_RDR         (AT91_CAST(AT91_REG *) 	0x00000008) // (SPI_RDR) Receive Data Register
#define SPI_TDR         (AT91_CAST(AT91_REG *) 	0x0000000C) // (SPI_TDR) Transmit Data Register
#define SPI_SR          (AT91_CAST(AT91_REG *) 	0x00000010) // (SPI_SR) Status Register
#define SPI_IER         (AT91_CAST(AT91_REG *) 	0x00000014) // (SPI_IER) Interrupt Enable Register
#define SPI_IDR         (AT91_CAST(AT91_REG *) 	0x00000018) // (SPI_IDR) Interrupt Disable Register
#define SPI_IMR         (AT91_CAST(AT91_REG *) 	0x0000001C) // (SPI_IMR) Interrupt Mask Register
#define SPI_CSR         (AT91_CAST(AT91_REG *) 	0x00000030) // (SPI_CSR) Chip Select Register

#endif
// -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- 
#define AT91C_SPI_SPIEN       (0x1 <<  0) // (SPI) SPI Enable
#define AT91C_SPI_SPIDIS      (0x1 <<  1) // (SPI) SPI Disable
#define AT91C_SPI_SWRST       (0x1 <<  7) // (SPI) SPI Software reset
#define AT91C_SPI_LASTXFER    (0x1 << 24) // (SPI) SPI Last Transfer
// -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- 
#define AT91C_SPI_MSTR        (0x1 <<  0) // (SPI) Master/Slave Mode
#define AT91C_SPI_PS          (0x1 <<  1) // (SPI) Peripheral Select
#define 	AT91C_SPI_PS_FIXED                (0x0 <<  1) // (SPI) Fixed Peripheral Select
#define 	AT91C_SPI_PS_VARIABLE             (0x1 <<  1) // (SPI) Variable Peripheral Select
#define AT91C_SPI_PCSDEC      (0x1 <<  2) // (SPI) Chip Select Decode
#define AT91C_SPI_FDIV        (0x1 <<  3) // (SPI) Clock Selection
#define AT91C_SPI_MODFDIS     (0x1 <<  4) // (SPI) Mode Fault Detection
#define AT91C_SPI_LLB         (0x1 <<  7) // (SPI) Clock Selection
#define AT91C_SPI_PCS         (0xF << 16) // (SPI) Peripheral Chip Select
#define AT91C_SPI_DLYBCS      (0xFF << 24) // (SPI) Delay Between Chip Selects
// -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- 
#define AT91C_SPI_RD          (0xFFFF <<  0) // (SPI) Receive Data
#define AT91C_SPI_RPCS        (0xF << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- 
#define AT91C_SPI_TD          (0xFFFF <<  0) // (SPI) Transmit Data
#define AT91C_SPI_TPCS        (0xF << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- 
#define AT91C_SPI_RDRF        (0x1 <<  0) // (SPI) Receive Data Register Full
#define AT91C_SPI_TDRE        (0x1 <<  1) // (SPI) Transmit Data Register Empty
#define AT91C_SPI_MODF        (0x1 <<  2) // (SPI) Mode Fault Error
#define AT91C_SPI_OVRES       (0x1 <<  3) // (SPI) Overrun Error Status
#define AT91C_SPI_ENDRX       (0x1 <<  4) // (SPI) End of Receiver Transfer
#define AT91C_SPI_ENDTX       (0x1 <<  5) // (SPI) End of Receiver Transfer
#define AT91C_SPI_RXBUFF      (0x1 <<  6) // (SPI) RXBUFF Interrupt
#define AT91C_SPI_TXBUFE      (0x1 <<  7) // (SPI) TXBUFE Interrupt
#define AT91C_SPI_NSSR        (0x1 <<  8) // (SPI) NSSR Interrupt
#define AT91C_SPI_TXEMPTY     (0x1 <<  9) // (SPI) TXEMPTY Interrupt
#define AT91C_SPI_SPIENS      (0x1 << 16) // (SPI) Enable Status
// -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- 
// -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- 
// -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- 
// -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- 
#define AT91C_SPI_CPOL        (0x1 <<  0) // (SPI) Clock Polarity
#define AT91C_SPI_NCPHA       (0x1 <<  1) // (SPI) Clock Phase
#define AT91C_SPI_CSAAT       (0x1 <<  3) // (SPI) Chip Select Active After Transfer
#define AT91C_SPI_BITS        (0xF <<  4) // (SPI) Bits Per Transfer
#define 	AT91C_SPI_BITS_8                    (0x0 <<  4) // (SPI) 8 Bits Per transfer
#define 	AT91C_SPI_BITS_9                    (0x1 <<  4) // (SPI) 9 Bits Per transfer
#define 	AT91C_SPI_BITS_10                   (0x2 <<  4) // (SPI) 10 Bits Per transfer
#define 	AT91C_SPI_BITS_11                   (0x3 <<  4) // (SPI) 11 Bits Per transfer
#define 	AT91C_SPI_BITS_12                   (0x4 <<  4) // (SPI) 12 Bits Per transfer
#define 	AT91C_SPI_BITS_13                   (0x5 <<  4) // (SPI) 13 Bits Per transfer
#define 	AT91C_SPI_BITS_14                   (0x6 <<  4) // (SPI) 14 Bits Per transfer
#define 	AT91C_SPI_BITS_15                   (0x7 <<  4) // (SPI) 15 Bits Per transfer
#define 	AT91C_SPI_BITS_16                   (0x8 <<  4) // (SPI) 16 Bits Per transfer
#define AT91C_SPI_SCBR        (0xFF <<  8) // (SPI) Serial Clock Baud Rate
#define AT91C_SPI_DLYBS       (0xFF << 16) // (SPI) Delay Before SPCK
#define AT91C_SPI_DLYBCT      (0xFF << 24) // (SPI) Delay Between Consecutive Transfers

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR DMA controller from Synopsys
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_DMA {
	AT91_REG	 DMA_SAR0; 	// Source Address Register for channel 0
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 DMA_DAR0; 	// Destination Address Register for channel 0
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 DMA_LLP0; 	// Linked List Pointer Register for channel 0
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 DMA_CTL0l; 	// Control Register for channel 0 - low
	AT91_REG	 DMA_CTL0h; 	// Control Register for channel 0 - high
	AT91_REG	 DMA_SSTAT0; 	// Source Status Register for channel 0
	AT91_REG	 Reserved3[1]; 	// 
	AT91_REG	 DMA_DSTAT0; 	// Destination Status Register for channel 0
	AT91_REG	 Reserved4[1]; 	// 
	AT91_REG	 DMA_SSTATAR0; 	// Source Status Adress Register for channel 0
	AT91_REG	 Reserved5[1]; 	// 
	AT91_REG	 DMA_DSTATAR0; 	// Destination Status Adress Register for channel 0
	AT91_REG	 Reserved6[1]; 	// 
	AT91_REG	 DMA_CFG0l; 	// Configuration Register for channel 0 - low
	AT91_REG	 DMA_CFG0h; 	// Configuration Register for channel 0 - high
	AT91_REG	 DMA_SGR0; 	// Source Gather Register for channel 0
	AT91_REG	 Reserved7[1]; 	// 
	AT91_REG	 DMA_DSR0; 	// Destination Scatter Register for channel 0
	AT91_REG	 Reserved8[1]; 	// 
	AT91_REG	 DMA_SAR1; 	// Source Address Register for channel 1
	AT91_REG	 Reserved9[1]; 	// 
	AT91_REG	 DMA_DAR1; 	// Destination Address Register for channel 1
	AT91_REG	 Reserved10[1]; 	// 
	AT91_REG	 DMA_LLP1; 	// Linked List Pointer Register for channel 1
	AT91_REG	 Reserved11[1]; 	// 
	AT91_REG	 DMA_CTL1l; 	// Control Register for channel 1 - low
	AT91_REG	 DMA_CTL1h; 	// Control Register for channel 1 - high
	AT91_REG	 DMA_SSTAT1; 	// Source Status Register for channel 1
	AT91_REG	 Reserved12[1]; 	// 
	AT91_REG	 DMA_DSTAT1; 	// Destination Status Register for channel 1
	AT91_REG	 Reserved13[1]; 	// 
	AT91_REG	 DMA_SSTATAR1; 	// Source Status Adress Register for channel 1
	AT91_REG	 Reserved14[1]; 	// 
	AT91_REG	 DMA_DSTATAR1; 	// Destination Status Adress Register for channel 1
	AT91_REG	 Reserved15[1]; 	// 
	AT91_REG	 DMA_CFG1l; 	// Configuration Register for channel 1 - low
	AT91_REG	 DMA_CFG1h; 	// Configuration Register for channel 1 - high
	AT91_REG	 DMA_SGR1; 	// Source Gather Register for channel 1
	AT91_REG	 Reserved16[1]; 	// 
	AT91_REG	 DMA_DSR1; 	// Destination Scatter Register for channel 1
	AT91_REG	 Reserved17[133]; 	// 
	AT91_REG	 DMA_RAWTFR; 	// Raw Status for IntTfr Interrupt
	AT91_REG	 Reserved18[1]; 	// 
	AT91_REG	 DMA_RAWBLOCK; 	// Raw Status for IntBlock Interrupt
	AT91_REG	 Reserved19[1]; 	// 
	AT91_REG	 DMA_RAWSRCTRAN; 	// Raw Status for IntSrcTran Interrupt
	AT91_REG	 Reserved20[1]; 	// 
	AT91_REG	 DMA_RAWDSTTRAN; 	// Raw Status for IntDstTran Interrupt
	AT91_REG	 Reserved21[1]; 	// 
	AT91_REG	 DMA_RAWERR; 	// Raw Status for IntErr Interrupt
	AT91_REG	 Reserved22[1]; 	// 
	AT91_REG	 DMA_STATUSTFR; 	// Status for IntTfr Interrupt
	AT91_REG	 Reserved23[1]; 	// 
	AT91_REG	 DMA_STATUSBLOCK; 	// Status for IntBlock Interrupt
	AT91_REG	 Reserved24[1]; 	// 
	AT91_REG	 DMA_STATUSSRCTRAN; 	// Status for IntSrcTran Interrupt
	AT91_REG	 Reserved25[1]; 	// 
	AT91_REG	 DMA_STATUSDSTTRAN; 	// Status for IntDstTran IInterrupt
	AT91_REG	 Reserved26[1]; 	// 
	AT91_REG	 DMA_STATUSERR; 	// Status for IntErr IInterrupt
	AT91_REG	 Reserved27[1]; 	// 
	AT91_REG	 DMA_MASKTFR; 	// Mask for IntTfr Interrupt
	AT91_REG	 Reserved28[1]; 	// 
	AT91_REG	 DMA_MASKBLOCK; 	// Mask for IntBlock Interrupt
	AT91_REG	 Reserved29[1]; 	// 
	AT91_REG	 DMA_MASKSRCTRAN; 	// Mask for IntSrcTran Interrupt
	AT91_REG	 Reserved30[1]; 	// 
	AT91_REG	 DMA_MASKDSTTRAN; 	// Mask for IntDstTran Interrupt
	AT91_REG	 Reserved31[1]; 	// 
	AT91_REG	 DMA_MASKERR; 	// Mask for IntErr Interrupt
	AT91_REG	 Reserved32[1]; 	// 
	AT91_REG	 DMA_CLEARTFR; 	// Clear for IntTfr Interrupt
	AT91_REG	 Reserved33[1]; 	// 
	AT91_REG	 DMA_CLEARBLOCK; 	// Clear for IntBlock Interrupt
	AT91_REG	 Reserved34[1]; 	// 
	AT91_REG	 DMA_CLEARSRCTRAN; 	// Clear for IntSrcTran Interrupt
	AT91_REG	 Reserved35[1]; 	// 
	AT91_REG	 DMA_CLEARDSTTRAN; 	// Clear for IntDstTran IInterrupt
	AT91_REG	 Reserved36[1]; 	// 
	AT91_REG	 DMA_CLEARERR; 	// Clear for IntErr Interrupt
	AT91_REG	 Reserved37[1]; 	// 
	AT91_REG	 DMA_STATUSINT; 	// Status for each Interrupt Type
	AT91_REG	 Reserved38[1]; 	// 
	AT91_REG	 DMA_REQSRCREG; 	// Source Software Transaction Request Register
	AT91_REG	 Reserved39[1]; 	// 
	AT91_REG	 DMA_REQDSTREG; 	// Destination Software Transaction Request Register
	AT91_REG	 Reserved40[1]; 	// 
	AT91_REG	 DMA_SGLREQSRCREG; 	// Single Source Software Transaction Request Register
	AT91_REG	 Reserved41[1]; 	// 
	AT91_REG	 DMA_SGLREQDSTREG; 	// Single Destination Software Transaction Request Register
	AT91_REG	 Reserved42[1]; 	// 
	AT91_REG	 DMA_LSTREQSRCREG; 	// Last Source Software Transaction Request Register
	AT91_REG	 Reserved43[1]; 	// 
	AT91_REG	 DMA_LSTREQDSTREG; 	// Last Destination Software Transaction Request Register
	AT91_REG	 Reserved44[1]; 	// 
	AT91_REG	 DMA_DMACFGREG; 	// DW_ahb_dmac Configuration Register
	AT91_REG	 Reserved45[1]; 	// 
	AT91_REG	 DMA_CHENREG; 	// DW_ahb_dmac Channel Enable Register
	AT91_REG	 Reserved46[1]; 	// 
	AT91_REG	 DMA_DMAIDREG; 	// DW_ahb_dmac ID Register
	AT91_REG	 Reserved47[1]; 	// 
	AT91_REG	 DMA_DMATESTREG; 	// DW_ahb_dmac Test Register
	AT91_REG	 Reserved48[1]; 	// 
	AT91_REG	 DMA_VERSIONID; 	// DW_ahb_dmac Version ID Register
} AT91S_DMA, *AT91PS_DMA;
#else
#define DMA_SAR0        (AT91_CAST(AT91_REG *) 	0x00000000) // (DMA_SAR0) Source Address Register for channel 0
#define DMA_DAR0        (AT91_CAST(AT91_REG *) 	0x00000008) // (DMA_DAR0) Destination Address Register for channel 0
#define DMA_LLP0        (AT91_CAST(AT91_REG *) 	0x00000010) // (DMA_LLP0) Linked List Pointer Register for channel 0
#define DMA_CTL0l       (AT91_CAST(AT91_REG *) 	0x00000018) // (DMA_CTL0l) Control Register for channel 0 - low
#define DMA_CTL0h       (AT91_CAST(AT91_REG *) 	0x0000001C) // (DMA_CTL0h) Control Register for channel 0 - high
#define DMA_SSTAT0      (AT91_CAST(AT91_REG *) 	0x00000020) // (DMA_SSTAT0) Source Status Register for channel 0
#define DMA_DSTAT0      (AT91_CAST(AT91_REG *) 	0x00000028) // (DMA_DSTAT0) Destination Status Register for channel 0
#define DMA_SSTATAR0    (AT91_CAST(AT91_REG *) 	0x00000030) // (DMA_SSTATAR0) Source Status Adress Register for channel 0
#define DMA_DSTATAR0    (AT91_CAST(AT91_REG *) 	0x00000038) // (DMA_DSTATAR0) Destination Status Adress Register for channel 0
#define DMA_CFG0l       (AT91_CAST(AT91_REG *) 	0x00000040) // (DMA_CFG0l) Configuration Register for channel 0 - low
#define DMA_CFG0h       (AT91_CAST(AT91_REG *) 	0x00000044) // (DMA_CFG0h) Configuration Register for channel 0 - high
#define DMA_SGR0        (AT91_CAST(AT91_REG *) 	0x00000048) // (DMA_SGR0) Source Gather Register for channel 0
#define DMA_DSR0        (AT91_CAST(AT91_REG *) 	0x00000050) // (DMA_DSR0) Destination Scatter Register for channel 0
#define DMA_SAR1        (AT91_CAST(AT91_REG *) 	0x00000058) // (DMA_SAR1) Source Address Register for channel 1
#define DMA_DAR1        (AT91_CAST(AT91_REG *) 	0x00000060) // (DMA_DAR1) Destination Address Register for channel 1
#define DMA_LLP1        (AT91_CAST(AT91_REG *) 	0x00000068) // (DMA_LLP1) Linked List Pointer Register for channel 1
#define DMA_CTL1l       (AT91_CAST(AT91_REG *) 	0x00000070) // (DMA_CTL1l) Control Register for channel 1 - low
#define DMA_CTL1h       (AT91_CAST(AT91_REG *) 	0x00000074) // (DMA_CTL1h) Control Register for channel 1 - high
#define DMA_SSTAT1      (AT91_CAST(AT91_REG *) 	0x00000078) // (DMA_SSTAT1) Source Status Register for channel 1
#define DMA_DSTAT1      (AT91_CAST(AT91_REG *) 	0x00000080) // (DMA_DSTAT1) Destination Status Register for channel 1
#define DMA_SSTATAR1    (AT91_CAST(AT91_REG *) 	0x00000088) // (DMA_SSTATAR1) Source Status Adress Register for channel 1
#define DMA_DSTATAR1    (AT91_CAST(AT91_REG *) 	0x00000090) // (DMA_DSTATAR1) Destination Status Adress Register for channel 1
#define DMA_CFG1l       (AT91_CAST(AT91_REG *) 	0x00000098) // (DMA_CFG1l) Configuration Register for channel 1 - low
#define DMA_CFG1h       (AT91_CAST(AT91_REG *) 	0x0000009C) // (DMA_CFG1h) Configuration Register for channel 1 - high
#define DMA_SGR1        (AT91_CAST(AT91_REG *) 	0x000000A0) // (DMA_SGR1) Source Gather Register for channel 1
#define DMA_DSR1        (AT91_CAST(AT91_REG *) 	0x000000A8) // (DMA_DSR1) Destination Scatter Register for channel 1
#define DMA_RAWTFR      (AT91_CAST(AT91_REG *) 	0x000002C0) // (DMA_RAWTFR) Raw Status for IntTfr Interrupt
#define DMA_RAWBLOCK    (AT91_CAST(AT91_REG *) 	0x000002C8) // (DMA_RAWBLOCK) Raw Status for IntBlock Interrupt
#define DMA_RAWSRCTRAN  (AT91_CAST(AT91_REG *) 	0x000002D0) // (DMA_RAWSRCTRAN) Raw Status for IntSrcTran Interrupt
#define DMA_RAWDSTTRAN  (AT91_CAST(AT91_REG *) 	0x000002D8) // (DMA_RAWDSTTRAN) Raw Status for IntDstTran Interrupt
#define DMA_RAWERR      (AT91_CAST(AT91_REG *) 	0x000002E0) // (DMA_RAWERR) Raw Status for IntErr Interrupt
#define DMA_STATUSTFR   (AT91_CAST(AT91_REG *) 	0x000002E8) // (DMA_STATUSTFR) Status for IntTfr Interrupt
#define DMA_STATUSBLOCK (AT91_CAST(AT91_REG *) 	0x000002F0) // (DMA_STATUSBLOCK) Status for IntBlock Interrupt
#define DMA_STATUSSRCTRAN (AT91_CAST(AT91_REG *) 	0x000002F8) // (DMA_STATUSSRCTRAN) Status for IntSrcTran Interrupt
#define DMA_STATUSDSTTRAN (AT91_CAST(AT91_REG *) 	0x00000300) // (DMA_STATUSDSTTRAN) Status for IntDstTran IInterrupt
#define DMA_STATUSERR   (AT91_CAST(AT91_REG *) 	0x00000308) // (DMA_STATUSERR) Status for IntErr IInterrupt
#define DMA_MASKTFR     (AT91_CAST(AT91_REG *) 	0x00000310) // (DMA_MASKTFR) Mask for IntTfr Interrupt
#define DMA_MASKBLOCK   (AT91_CAST(AT91_REG *) 	0x00000318) // (DMA_MASKBLOCK) Mask for IntBlock Interrupt
#define DMA_MASKSRCTRAN (AT91_CAST(AT91_REG *) 	0x00000320) // (DMA_MASKSRCTRAN) Mask for IntSrcTran Interrupt
#define DMA_MASKDSTTRAN (AT91_CAST(AT91_REG *) 	0x00000328) // (DMA_MASKDSTTRAN) Mask for IntDstTran Interrupt
#define DMA_MASKERR     (AT91_CAST(AT91_REG *) 	0x00000330) // (DMA_MASKERR) Mask for IntErr Interrupt
#define DMA_CLEARTFR    (AT91_CAST(AT91_REG *) 	0x00000338) // (DMA_CLEARTFR) Clear for IntTfr Interrupt
#define DMA_CLEARBLOCK  (AT91_CAST(AT91_REG *) 	0x00000340) // (DMA_CLEARBLOCK) Clear for IntBlock Interrupt
#define DMA_CLEARSRCTRAN (AT91_CAST(AT91_REG *) 	0x00000348) // (DMA_CLEARSRCTRAN) Clear for IntSrcTran Interrupt
#define DMA_CLEARDSTTRAN (AT91_CAST(AT91_REG *) 	0x00000350) // (DMA_CLEARDSTTRAN) Clear for IntDstTran IInterrupt
#define DMA_CLEARERR    (AT91_CAST(AT91_REG *) 	0x00000358) // (DMA_CLEARERR) Clear for IntErr Interrupt
#define DMA_STATUSINT   (AT91_CAST(AT91_REG *) 	0x00000360) // (DMA_STATUSINT) Status for each Interrupt Type
#define DMA_REQSRCREG   (AT91_CAST(AT91_REG *) 	0x00000368) // (DMA_REQSRCREG) Source Software Transaction Request Register
#define DMA_REQDSTREG   (AT91_CAST(AT91_REG *) 	0x00000370) // (DMA_REQDSTREG) Destination Software Transaction Request Register
#define DMA_SGLREQSRCREG (AT91_CAST(AT91_REG *) 	0x00000378) // (DMA_SGLREQSRCREG) Single Source Software Transaction Request Register
#define DMA_SGLREQDSTREG (AT91_CAST(AT91_REG *) 	0x00000380) // (DMA_SGLREQDSTREG) Single Destination Software Transaction Request Register
#define DMA_LSTREQSRCREG (AT91_CAST(AT91_REG *) 	0x00000388) // (DMA_LSTREQSRCREG) Last Source Software Transaction Request Register
#define DMA_LSTREQDSTREG (AT91_CAST(AT91_REG *) 	0x00000390) // (DMA_LSTREQDSTREG) Last Destination Software Transaction Request Register
#define DMA_DMACFGREG   (AT91_CAST(AT91_REG *) 	0x00000398) // (DMA_DMACFGREG) DW_ahb_dmac Configuration Register
#define DMA_CHENREG     (AT91_CAST(AT91_REG *) 	0x000003A0) // (DMA_CHENREG) DW_ahb_dmac Channel Enable Register
#define DMA_DMAIDREG    (AT91_CAST(AT91_REG *) 	0x000003A8) // (DMA_DMAIDREG) DW_ahb_dmac ID Register
#define DMA_DMATESTREG  (AT91_CAST(AT91_REG *) 	0x000003B0) // (DMA_DMATESTREG) DW_ahb_dmac Test Register
#define DMA_VERSIONID   (AT91_CAST(AT91_REG *) 	0x000003B8) // (DMA_VERSIONID) DW_ahb_dmac Version ID Register

#endif
// -------- DMA_SAR : (DMA Offset: 0x0)  -------- 
#define AT91C_DMA_SADD        (0x0 <<  0) // (DMA) Source Address of DMA Transfer
// -------- DMA_DAR : (DMA Offset: 0x8)  -------- 
#define AT91C_DMA_DADD        (0x0 <<  0) // (DMA) Destination Address of DMA Transfer
// -------- DMA_LLP : (DMA Offset: 0x10)  -------- 
#define AT91C_DMA_LOC         (0x0 <<  0) // (DMA) Address of the Next LLI
// -------- DMA_CTLl : (DMA Offset: 0x18)  -------- 
#define AT91C_DMA_INT_EN      (0x1 <<  0) // (DMA) Interrupt Enable Bit
#define AT91C_DMA_DST_TR_WIDTH (0x7 <<  1) // (DMA) Destination Transfer Width
#define AT91C_DMA_SRC_TR_WIDTH (0x7 <<  4) // (DMA) Source Transfer Width
#define AT91C_DMA_DINC        (0x3 <<  7) // (DMA) Destination Address Increment
#define AT91C_DMA_SINC        (0x3 <<  9) // (DMA) Source Address Increment
#define AT91C_DMA_DEST_MSIZE  (0x7 << 11) // (DMA) Destination Burst Transaction Length
#define AT91C_DMA_SRC_MSIZE   (0x7 << 14) // (DMA) Source Burst Transaction Length
#define AT91C_DMA_S_GATH_EN   (0x1 << 17) // (DMA) Source Gather Enable Bit
#define AT91C_DMA_D_SCAT_EN   (0x1 << 18) // (DMA) Destination Scatter Enable Bit
#define AT91C_DMA_TT_FC       (0x7 << 20) // (DMA) Transfer Type and Flow Control
#define AT91C_DMA_DMS         (0x3 << 23) // (DMA) Destination Master Select
#define AT91C_DMA_SMS         (0x3 << 25) // (DMA) Source Master Select
#define AT91C_DMA_LLP_D_EN    (0x1 << 27) // (DMA) Destination Block Chaining Enable
#define AT91C_DMA_LLP_S_EN    (0x1 << 28) // (DMA) Source Block Chaining Enable
// -------- DMA_CTLh : (DMA Offset: 0x1c)  -------- 
#define AT91C_DMA_BLOCK_TS    (0xFFF <<  0) // (DMA) Block Transfer Size
#define AT91C_DMA_DONE        (0x1 << 12) // (DMA) Done bit
// -------- DMA_CFGl : (DMA Offset: 0x40)  -------- 
#define AT91C_DMA_CH_PRIOR    (0x7 <<  5) // (DMA) Channel Priority
#define AT91C_DMA_CH_SUSP     (0x1 <<  8) // (DMA) Channel Suspend
#define AT91C_DMA_FIFO_EMPT   (0x1 <<  9) // (DMA) Fifo Empty
#define AT91C_DMA_HS_SEL_DS   (0x1 << 10) // (DMA) Destination Software or Hardware Handshaking Select
#define AT91C_DMA_HS_SEL_SR   (0x1 << 11) // (DMA) Source Software or Hardware Handshaking Select
#define AT91C_DMA_LOCK_CH_L   (0x3 << 12) // (DMA) Channel Lock Level
#define AT91C_DMA_LOCK_B_L    (0x3 << 14) // (DMA) Bus Lock Level
#define AT91C_DMA_LOCK_CH     (0x1 << 16) // (DMA) Channel Lock Bit
#define AT91C_DMA_LOCK_B      (0x1 << 17) // (DMA) Bus Lock Bit
#define AT91C_DMA_DS_HS_POL   (0x1 << 18) // (DMA) Destination Handshaking Interface Polarity
#define AT91C_DMA_SR_HS_POL   (0x1 << 19) // (DMA) Source Handshaking Interface Polarity
#define AT91C_DMA_MAX_ABRST   (0x3FF << 20) // (DMA) Maximum AMBA Burst Length
#define AT91C_DMA_RELOAD_SR   (0x1 << 30) // (DMA) Automatic Source Reload
#define AT91C_DMA_RELOAD_DS   (0x1 << 31) // (DMA) Automatic Destination Reload
// -------- DMA_CFGh : (DMA Offset: 0x44)  -------- 
#define AT91C_DMA_FCMODE      (0x1 <<  0) // (DMA) Flow Control Mode
#define AT91C_DMA_FIFO_MODE   (0x1 <<  1) // (DMA) Fifo Mode Select
#define AT91C_DMA_PROTCTL     (0x7 <<  2) // (DMA) Protection Control
#define AT91C_DMA_DS_UPD_EN   (0x1 <<  5) // (DMA) Destination Status Update Enable
#define AT91C_DMA_SS_UPD_EN   (0x1 <<  6) // (DMA) Source Status Update Enable
#define AT91C_DMA_SRC_PER     (0xF <<  7) // (DMA) Source Hardware Handshaking Interface
#define AT91C_DMA_DEST_PER    (0xF << 11) // (DMA) Destination Hardware Handshaking Interface
// -------- DMA_SGR : (DMA Offset: 0x48)  -------- 
#define AT91C_DMA_SGI         (0xFFFFF <<  0) // (DMA) Source Gather Interval
#define AT91C_DMA_SGC         (0xFFF << 20) // (DMA) Source Gather Count
// -------- DMA_DSR : (DMA Offset: 0x50)  -------- 
#define AT91C_DMA_DSI         (0xFFFFF <<  0) // (DMA) Destination Scatter Interval
#define AT91C_DMA_DSC         (0xFFF << 20) // (DMA) Destination Scatter Count
// -------- DMA_SAR : (DMA Offset: 0x58)  -------- 
// -------- DMA_DAR : (DMA Offset: 0x60)  -------- 
// -------- DMA_LLP : (DMA Offset: 0x68)  -------- 
// -------- DMA_CTLl : (DMA Offset: 0x70)  -------- 
// -------- DMA_CTLh : (DMA Offset: 0x74)  -------- 
// -------- DMA_CFGl : (DMA Offset: 0x98)  -------- 
// -------- DMA_CFGh : (DMA Offset: 0x9c)  -------- 
// -------- DMA_SGR : (DMA Offset: 0xa0)  -------- 
// -------- DMA_DSR : (DMA Offset: 0xa8)  -------- 
// -------- DMA_RAWTFR : (DMA Offset: 0x2c0)  -------- 
#define AT91C_DMA_RAW         (0x7 <<  0) // (DMA) Raw Interrupt for each Channel
// -------- DMA_RAWBLOCK : (DMA Offset: 0x2c8)  -------- 
// -------- DMA_RAWSRCTRAN : (DMA Offset: 0x2d0)  -------- 
// -------- DMA_RAWDSTTRAN : (DMA Offset: 0x2d8)  -------- 
// -------- DMA_RAWERR : (DMA Offset: 0x2e0)  -------- 
// -------- DMA_STATUSTFR : (DMA Offset: 0x2e8)  -------- 
#define AT91C_DMA_STATUS      (0x7 <<  0) // (DMA) Interrupt for each Channel
// -------- DMA_STATUSBLOCK : (DMA Offset: 0x2f0)  -------- 
// -------- DMA_STATUSSRCTRAN : (DMA Offset: 0x2f8)  -------- 
// -------- DMA_STATUSDSTTRAN : (DMA Offset: 0x300)  -------- 
// -------- DMA_STATUSERR : (DMA Offset: 0x308)  -------- 
// -------- DMA_MASKTFR : (DMA Offset: 0x310)  -------- 
#define AT91C_DMA_INT_MASK    (0x7 <<  0) // (DMA) Interrupt Mask for each Channel
#define AT91C_DMA_INT_M_WE    (0x7 <<  8) // (DMA) Interrupt Mask Write Enable for each Channel
// -------- DMA_MASKBLOCK : (DMA Offset: 0x318)  -------- 
// -------- DMA_MASKSRCTRAN : (DMA Offset: 0x320)  -------- 
// -------- DMA_MASKDSTTRAN : (DMA Offset: 0x328)  -------- 
// -------- DMA_MASKERR : (DMA Offset: 0x330)  -------- 
// -------- DMA_CLEARTFR : (DMA Offset: 0x338)  -------- 
#define AT91C_DMA_CLEAR       (0x7 <<  0) // (DMA) Interrupt Clear for each Channel
// -------- DMA_CLEARBLOCK : (DMA Offset: 0x340)  -------- 
// -------- DMA_CLEARSRCTRAN : (DMA Offset: 0x348)  -------- 
// -------- DMA_CLEARDSTTRAN : (DMA Offset: 0x350)  -------- 
// -------- DMA_CLEARERR : (DMA Offset: 0x358)  -------- 
// -------- DMA_STATUSINT : (DMA Offset: 0x360)  -------- 
#define AT91C_DMA_TFR         (0x1 <<  0) // (DMA) OR of the content of StatusTfr Register
#define AT91C_DMA_BLOCK       (0x1 <<  1) // (DMA) OR of the content of StatusBlock Register
#define AT91C_DMA_SRCT        (0x1 <<  2) // (DMA) OR of the content of StatusSrcTran Register
#define AT91C_DMA_DSTT        (0x1 <<  3) // (DMA) OR of the content of StatusDstTran Register
#define AT91C_DMA_ERR         (0x1 <<  4) // (DMA) OR of the content of StatusErr Register
// -------- DMA_REQSRCREG : (DMA Offset: 0x368)  -------- 
#define AT91C_DMA_SRC_REQ     (0x7 <<  0) // (DMA) Source Request
#define AT91C_DMA_REQ_WE      (0x7 <<  8) // (DMA) Request Write Enable
// -------- DMA_REQDSTREG : (DMA Offset: 0x370)  -------- 
#define AT91C_DMA_DST_REQ     (0x7 <<  0) // (DMA) Destination Request
// -------- DMA_SGLREQSRCREG : (DMA Offset: 0x378)  -------- 
#define AT91C_DMA_S_SG_REQ    (0x7 <<  0) // (DMA) Source Single Request
// -------- DMA_SGLREQDSTREG : (DMA Offset: 0x380)  -------- 
#define AT91C_DMA_D_SG_REQ    (0x7 <<  0) // (DMA) Destination Single Request
// -------- DMA_LSTREQSRCREG : (DMA Offset: 0x388)  -------- 
#define AT91C_DMA_LSTSRC      (0x7 <<  0) // (DMA) Source Last Transaction Request
#define AT91C_DMA_LSTSR_WE    (0x7 <<  8) // (DMA) Source Last Transaction Request Write Enable
// -------- DMA_LSTREQDSTREG : (DMA Offset: 0x390)  -------- 
#define AT91C_DMA_LSTDST      (0x7 <<  0) // (DMA) Destination Last Transaction Request
#define AT91C_DMA_LSTDS_WE    (0x7 <<  8) // (DMA) Destination Last Transaction Request Write Enable
// -------- DMA_DMACFGREG : (DMA Offset: 0x398)  -------- 
#define AT91C_DMA_DMA_EN      (0x7 <<  0) // (DMA) Controller Enable
// -------- DMA_CHENREG : (DMA Offset: 0x3a0)  -------- 
#define AT91C_DMA_CH_EN       (0x7 <<  0) // (DMA) Channel Enable
#define AT91C_DMA_CH_EN_WE    (0x7 <<  8) // (DMA) Channel Enable Write Enable
// -------- DMA_DMATESTREG : (DMA Offset: 0x3b0)  -------- 
#define AT91C_DMA_TEST_SLV_IF (0x1 <<  0) // (DMA) Test Mode for Slave Interface


// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Error Correction Code controller
// *****************************************************************************
#ifndef __ASSEMBLY__
typedef struct _AT91S_ECC {
	AT91_REG	 ECC_CR; 	//  ECC reset register
	AT91_REG	 ECC_MR; 	//  ECC Page size register
	AT91_REG	 ECC_SR; 	//  ECC Status register
	AT91_REG	 ECC_PR; 	//  ECC Parity register
	AT91_REG	 ECC_NPR; 	//  ECC Parity N register
	AT91_REG	 Reserved0[58]; 	// 
	AT91_REG	 ECC_VR; 	//  ECC Version register
} AT91S_ECC, *AT91PS_ECC;
#else
#define ECC_CR          (AT91_CAST(AT91_REG *) 	0x00000000) // (ECC_CR)  ECC reset register
#define ECC_MR          (AT91_CAST(AT91_REG *) 	0x00000004) // (ECC_MR)  ECC Page size register
#define ECC_SR          (AT91_CAST(AT91_REG *) 	0x00000008) // (ECC_SR)  ECC Status register
#define ECC_PR          (AT91_CAST(AT91_REG *) 	0x0000000C) // (ECC_PR)  ECC Parity register
#define ECC_NPR         (AT91_CAST(AT91_REG *) 	0x00000010) // (ECC_NPR)  ECC Parity N register
#define ECC_VR          (AT91_CAST(AT91_REG *) 	0x000000FC) // (ECC_VR)  ECC Version register

#endif
// -------- ECC_CR : (ECC Offset: 0x0) ECC reset register -------- 
#define AT91C_ECC_RST         (0x1 <<  0) // (ECC) ECC reset parity
// -------- ECC_MR : (ECC Offset: 0x4) ECC page size register -------- 
#define AT91C_ECC_PAGE_SIZE   (0x3 <<  0) // (ECC) Nand Flash page size
// -------- ECC_SR : (ECC Offset: 0x8) ECC status register -------- 
#define AT91C_ECC_RECERR      (0x1 <<  0) // (ECC) ECC error
#define AT91C_ECC_ECCERR      (0x1 <<  1) // (ECC) ECC single error
#define AT91C_ECC_MULERR      (0x1 <<  2) // (ECC) ECC_MULERR
// -------- ECC_PR : (ECC Offset: 0xc) ECC parity register -------- 
#define AT91C_ECC_BITADDR     (0xF <<  0) // (ECC) Bit address error
#define AT91C_ECC_WORDADDR    (0xFFF <<  4) // (ECC) address of the failing bit
// -------- ECC_NPR : (ECC Offset: 0x10) ECC N parity register -------- 
#define AT91C_ECC_NPARITY     (0xFFFF <<  0) // (ECC) ECC parity N 
// -------- ECC_VR : (ECC Offset: 0xfc) ECC version register -------- 
#define AT91C_ECC_VR          (0xF <<  0) // (ECC) ECC version register

// *****************************************************************************
//               REGISTER ADDRESS DEFINITION FOR AT91SAM9263
// *****************************************************************************
// ========== Register definition for SYS peripheral ========== 
#define AT91C_SYS_ECC1  (AT91_CAST(AT91_REG *) 	0xFFFFE600) // (SYS) ECC 0
#define AT91C_SYS_ECC0  (AT91_CAST(AT91_REG *) 	0xFFFFE000) // (SYS) ECC 0
#define AT91C_SYS_GPBR  (AT91_CAST(AT91_REG *) 	0xFFFFFD60) // (SYS) General Purpose Register
// ========== Register definition for EBI0 peripheral ========== 
#define AT91C_EBI0_DUMMY (AT91_CAST(AT91_REG *) 	0xFFFFE200) // (EBI0) Dummy register - Do not use
// ========== Register definition for SDRAMC0 peripheral ========== 
#define AT91C_SDRAMC0_MDR (AT91_CAST(AT91_REG *) 	0xFFFFE224) // (SDRAMC0) SDRAM Memory Device Register
#define AT91C_SDRAMC0_IDR (AT91_CAST(AT91_REG *) 	0xFFFFE218) // (SDRAMC0) SDRAM Controller Interrupt Disable Register
#define AT91C_SDRAMC0_IMR (AT91_CAST(AT91_REG *) 	0xFFFFE21C) // (SDRAMC0) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC0_ISR (AT91_CAST(AT91_REG *) 	0xFFFFE220) // (SDRAMC0) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC0_HSR (AT91_CAST(AT91_REG *) 	0xFFFFE20C) // (SDRAMC0) SDRAM Controller High Speed Register
#define AT91C_SDRAMC0_TR (AT91_CAST(AT91_REG *) 	0xFFFFE204) // (SDRAMC0) SDRAM Controller Refresh Timer Register
#define AT91C_SDRAMC0_CR (AT91_CAST(AT91_REG *) 	0xFFFFE208) // (SDRAMC0) SDRAM Controller Configuration Register
#define AT91C_SDRAMC0_MR (AT91_CAST(AT91_REG *) 	0xFFFFE200) // (SDRAMC0) SDRAM Controller Mode Register
#define AT91C_SDRAMC0_LPR (AT91_CAST(AT91_REG *) 	0xFFFFE210) // (SDRAMC0) SDRAM Controller Low Power Register
#define AT91C_SDRAMC0_IER (AT91_CAST(AT91_REG *) 	0xFFFFE214) // (SDRAMC0) SDRAM Controller Interrupt Enable Register
// ========== Register definition for SMC0 peripheral ========== 
#define AT91C_SMC0_CYCLE6 (AT91_CAST(AT91_REG *) 	0xFFFFE468) // (SMC0)  Cycle Register for CS 6
#define AT91C_SMC0_SETUP6 (AT91_CAST(AT91_REG *) 	0xFFFFE460) // (SMC0)  Setup Register for CS 6
#define AT91C_SMC0_PULSE3 (AT91_CAST(AT91_REG *) 	0xFFFFE434) // (SMC0)  Pulse Register for CS 3
#define AT91C_SMC0_CYCLE1 (AT91_CAST(AT91_REG *) 	0xFFFFE418) // (SMC0)  Cycle Register for CS 1
#define AT91C_SMC0_SETUP5 (AT91_CAST(AT91_REG *) 	0xFFFFE450) // (SMC0)  Setup Register for CS 5
#define AT91C_SMC0_CYCLE7 (AT91_CAST(AT91_REG *) 	0xFFFFE478) // (SMC0)  Cycle Register for CS 7
#define AT91C_SMC0_PULSE0 (AT91_CAST(AT91_REG *) 	0xFFFFE404) // (SMC0)  Pulse Register for CS 0
#define AT91C_SMC0_CYCLE5 (AT91_CAST(AT91_REG *) 	0xFFFFE458) // (SMC0)  Cycle Register for CS 5
#define AT91C_SMC0_CTRL0 (AT91_CAST(AT91_REG *) 	0xFFFFE40C) // (SMC0)  Control Register for CS 0
#define AT91C_SMC0_SETUP7 (AT91_CAST(AT91_REG *) 	0xFFFFE470) // (SMC0)  Setup Register for CS 7
#define AT91C_SMC0_CTRL4 (AT91_CAST(AT91_REG *) 	0xFFFFE44C) // (SMC0)  Control Register for CS 4
#define AT91C_SMC0_CTRL1 (AT91_CAST(AT91_REG *) 	0xFFFFE41C) // (SMC0)  Control Register for CS 1
#define AT91C_SMC0_CYCLE2 (AT91_CAST(AT91_REG *) 	0xFFFFE428) // (SMC0)  Cycle Register for CS 2
#define AT91C_SMC0_PULSE7 (AT91_CAST(AT91_REG *) 	0xFFFFE474) // (SMC0)  Pulse Register for CS 7
#define AT91C_SMC0_PULSE6 (AT91_CAST(AT91_REG *) 	0xFFFFE464) // (SMC0)  Pulse Register for CS 6
#define AT91C_SMC0_CYCLE4 (AT91_CAST(AT91_REG *) 	0xFFFFE448) // (SMC0)  Cycle Register for CS 4
#define AT91C_SMC0_CYCLE0 (AT91_CAST(AT91_REG *) 	0xFFFFE408) // (SMC0)  Cycle Register for CS 0
#define AT91C_SMC0_CTRL6 (AT91_CAST(AT91_REG *) 	0xFFFFE46C) // (SMC0)  Control Register for CS 6
#define AT91C_SMC0_CTRL5 (AT91_CAST(AT91_REG *) 	0xFFFFE45C) // (SMC0)  Control Register for CS 5
#define AT91C_SMC0_SETUP0 (AT91_CAST(AT91_REG *) 	0xFFFFE400) // (SMC0)  Setup Register for CS 0
#define AT91C_SMC0_SETUP4 (AT91_CAST(AT91_REG *) 	0xFFFFE440) // (SMC0)  Setup Register for CS 4
#define AT91C_SMC0_PULSE1 (AT91_CAST(AT91_REG *) 	0xFFFFE414) // (SMC0)  Pulse Register for CS 1
#define AT91C_SMC0_CTRL2 (AT91_CAST(AT91_REG *) 	0xFFFFE42C) // (SMC0)  Control Register for CS 2
#define AT91C_SMC0_SETUP2 (AT91_CAST(AT91_REG *) 	0xFFFFE420) // (SMC0)  Setup Register for CS 2
#define AT91C_SMC0_CTRL3 (AT91_CAST(AT91_REG *) 	0xFFFFE43C) // (SMC0)  Control Register for CS 3
#define AT91C_SMC0_SETUP3 (AT91_CAST(AT91_REG *) 	0xFFFFE430) // (SMC0)  Setup Register for CS 3
#define AT91C_SMC0_CTRL7 (AT91_CAST(AT91_REG *) 	0xFFFFE47C) // (SMC0)  Control Register for CS 7
#define AT91C_SMC0_PULSE5 (AT91_CAST(AT91_REG *) 	0xFFFFE454) // (SMC0)  Pulse Register for CS 5
#define AT91C_SMC0_PULSE4 (AT91_CAST(AT91_REG *) 	0xFFFFE444) // (SMC0)  Pulse Register for CS 4
#define AT91C_SMC0_PULSE2 (AT91_CAST(AT91_REG *) 	0xFFFFE424) // (SMC0)  Pulse Register for CS 2
#define AT91C_SMC0_CYCLE3 (AT91_CAST(AT91_REG *) 	0xFFFFE438) // (SMC0)  Cycle Register for CS 3
#define AT91C_SMC0_SETUP1 (AT91_CAST(AT91_REG *) 	0xFFFFE410) // (SMC0)  Setup Register for CS 1
// ========== Register definition for EBI1 peripheral ========== 
#define AT91C_EBI1_DUMMY (AT91_CAST(AT91_REG *) 	0xFFFFE800) // (EBI1) Dummy register - Do not use
// ========== Register definition for SDRAMC1 peripheral ========== 
#define AT91C_SDRAMC1_IMR (AT91_CAST(AT91_REG *) 	0xFFFFE81C) // (SDRAMC1) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC1_LPR (AT91_CAST(AT91_REG *) 	0xFFFFE810) // (SDRAMC1) SDRAM Controller Low Power Register
#define AT91C_SDRAMC1_CR (AT91_CAST(AT91_REG *) 	0xFFFFE808) // (SDRAMC1) SDRAM Controller Configuration Register
#define AT91C_SDRAMC1_HSR (AT91_CAST(AT91_REG *) 	0xFFFFE80C) // (SDRAMC1) SDRAM Controller High Speed Register
#define AT91C_SDRAMC1_MDR (AT91_CAST(AT91_REG *) 	0xFFFFE824) // (SDRAMC1) SDRAM Memory Device Register
#define AT91C_SDRAMC1_MR (AT91_CAST(AT91_REG *) 	0xFFFFE800) // (SDRAMC1) SDRAM Controller Mode Register
#define AT91C_SDRAMC1_ISR (AT91_CAST(AT91_REG *) 	0xFFFFE820) // (SDRAMC1) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC1_IDR (AT91_CAST(AT91_REG *) 	0xFFFFE818) // (SDRAMC1) SDRAM Controller Interrupt Disable Register
#define AT91C_SDRAMC1_IER (AT91_CAST(AT91_REG *) 	0xFFFFE814) // (SDRAMC1) SDRAM Controller Interrupt Enable Register
#define AT91C_SDRAMC1_TR (AT91_CAST(AT91_REG *) 	0xFFFFE804) // (SDRAMC1) SDRAM Controller Refresh Timer Register
// ========== Register definition for SMC1 peripheral ========== 
#define AT91C_SMC1_PULSE4 (AT91_CAST(AT91_REG *) 	0xFFFFEA44) // (SMC1)  Pulse Register for CS 4
#define AT91C_SMC1_SETUP2 (AT91_CAST(AT91_REG *) 	0xFFFFEA20) // (SMC1)  Setup Register for CS 2
#define AT91C_SMC1_CYCLE0 (AT91_CAST(AT91_REG *) 	0xFFFFEA08) // (SMC1)  Cycle Register for CS 0
#define AT91C_SMC1_SETUP7 (AT91_CAST(AT91_REG *) 	0xFFFFEA70) // (SMC1)  Setup Register for CS 7
#define AT91C_SMC1_PULSE7 (AT91_CAST(AT91_REG *) 	0xFFFFEA74) // (SMC1)  Pulse Register for CS 7
#define AT91C_SMC1_CTRL0 (AT91_CAST(AT91_REG *) 	0xFFFFEA0C) // (SMC1)  Control Register for CS 0
#define AT91C_SMC1_SETUP3 (AT91_CAST(AT91_REG *) 	0xFFFFEA30) // (SMC1)  Setup Register for CS 3
#define AT91C_SMC1_SETUP4 (AT91_CAST(AT91_REG *) 	0xFFFFEA40) // (SMC1)  Setup Register for CS 4
#define AT91C_SMC1_CYCLE6 (AT91_CAST(AT91_REG *) 	0xFFFFEA68) // (SMC1)  Cycle Register for CS 6
#define AT91C_SMC1_CTRL1 (AT91_CAST(AT91_REG *) 	0xFFFFEA1C) // (SMC1)  Control Register for CS 1
#define AT91C_SMC1_CYCLE3 (AT91_CAST(AT91_REG *) 	0xFFFFEA38) // (SMC1)  Cycle Register for CS 3
#define AT91C_SMC1_CTRL5 (AT91_CAST(AT91_REG *) 	0xFFFFEA5C) // (SMC1)  Control Register for CS 5
#define AT91C_SMC1_CTRL3 (AT91_CAST(AT91_REG *) 	0xFFFFEA3C) // (SMC1)  Control Register for CS 3
#define AT91C_SMC1_CYCLE4 (AT91_CAST(AT91_REG *) 	0xFFFFEA48) // (SMC1)  Cycle Register for CS 4
#define AT91C_SMC1_SETUP6 (AT91_CAST(AT91_REG *) 	0xFFFFEA60) // (SMC1)  Setup Register for CS 6
#define AT91C_SMC1_PULSE3 (AT91_CAST(AT91_REG *) 	0xFFFFEA34) // (SMC1)  Pulse Register for CS 3
#define AT91C_SMC1_CTRL7 (AT91_CAST(AT91_REG *) 	0xFFFFEA7C) // (SMC1)  Control Register for CS 7
#define AT91C_SMC1_SETUP1 (AT91_CAST(AT91_REG *) 	0xFFFFEA10) // (SMC1)  Setup Register for CS 1
#define AT91C_SMC1_PULSE5 (AT91_CAST(AT91_REG *) 	0xFFFFEA54) // (SMC1)  Pulse Register for CS 5
#define AT91C_SMC1_PULSE0 (AT91_CAST(AT91_REG *) 	0xFFFFEA04) // (SMC1)  Pulse Register for CS 0
#define AT91C_SMC1_CYCLE5 (AT91_CAST(AT91_REG *) 	0xFFFFEA58) // (SMC1)  Cycle Register for CS 5
#define AT91C_SMC1_PULSE6 (AT91_CAST(AT91_REG *) 	0xFFFFEA64) // (SMC1)  Pulse Register for CS 6
#define AT91C_SMC1_SETUP5 (AT91_CAST(AT91_REG *) 	0xFFFFEA50) // (SMC1)  Setup Register for CS 5
#define AT91C_SMC1_CTRL6 (AT91_CAST(AT91_REG *) 	0xFFFFEA6C) // (SMC1)  Control Register for CS 6
#define AT91C_SMC1_CTRL2 (AT91_CAST(AT91_REG *) 	0xFFFFEA2C) // (SMC1)  Control Register for CS 2
#define AT91C_SMC1_SETUP0 (AT91_CAST(AT91_REG *) 	0xFFFFEA00) // (SMC1)  Setup Register for CS 0
#define AT91C_SMC1_CYCLE7 (AT91_CAST(AT91_REG *) 	0xFFFFEA78) // (SMC1)  Cycle Register for CS 7
#define AT91C_SMC1_CYCLE1 (AT91_CAST(AT91_REG *) 	0xFFFFEA18) // (SMC1)  Cycle Register for CS 1
#define AT91C_SMC1_PULSE2 (AT91_CAST(AT91_REG *) 	0xFFFFEA24) // (SMC1)  Pulse Register for CS 2
#define AT91C_SMC1_PULSE1 (AT91_CAST(AT91_REG *) 	0xFFFFEA14) // (SMC1)  Pulse Register for CS 1
#define AT91C_SMC1_CYCLE2 (AT91_CAST(AT91_REG *) 	0xFFFFEA28) // (SMC1)  Cycle Register for CS 2
#define AT91C_SMC1_CTRL4 (AT91_CAST(AT91_REG *) 	0xFFFFEA4C) // (SMC1)  Control Register for CS 4
// ========== Register definition for MATRIX peripheral ========== 
#define AT91C_MATRIX_MCFG7 (AT91_CAST(AT91_REG *) 	0xFFFFEC1C) // (MATRIX)  Master Configuration Register 7 
#define AT91C_MATRIX_MRCR (AT91_CAST(AT91_REG *) 	0xFFFFED00) // (MATRIX)  Master Remp Control Register 
#define AT91C_MATRIX_PRBS5 (AT91_CAST(AT91_REG *) 	0xFFFFECAC) // (MATRIX)  PRBS5
#define AT91C_MATRIX_SCFG6 (AT91_CAST(AT91_REG *) 	0xFFFFEC58) // (MATRIX)  Slave Configuration Register 6
#define AT91C_MATRIX_MCFG3 (AT91_CAST(AT91_REG *) 	0xFFFFEC0C) // (MATRIX)  Master Configuration Register 3 
#define AT91C_MATRIX_SCFG5 (AT91_CAST(AT91_REG *) 	0xFFFFEC54) // (MATRIX)  Slave Configuration Register 5
#define AT91C_MATRIX_MCFG1 (AT91_CAST(AT91_REG *) 	0xFFFFEC04) // (MATRIX)  Master Configuration Register 1 
#define AT91C_MATRIX_SCFG3 (AT91_CAST(AT91_REG *) 	0xFFFFEC4C) // (MATRIX)  Slave Configuration Register 3
#define AT91C_MATRIX_MCFG4 (AT91_CAST(AT91_REG *) 	0xFFFFEC10) // (MATRIX)  Master Configuration Register 4 
#define AT91C_MATRIX_MCFG2 (AT91_CAST(AT91_REG *) 	0xFFFFEC08) // (MATRIX)  Master Configuration Register 2 
#define AT91C_MATRIX_PRBS6 (AT91_CAST(AT91_REG *) 	0xFFFFECB4) // (MATRIX)  PRBS6
#define AT91C_MATRIX_SCFG4 (AT91_CAST(AT91_REG *) 	0xFFFFEC50) // (MATRIX)  Slave Configuration Register 4
#define AT91C_MATRIX_MCFG8 (AT91_CAST(AT91_REG *) 	0xFFFFEC20) // (MATRIX)  Master Configuration Register 8 
#define AT91C_MATRIX_PRAS3 (AT91_CAST(AT91_REG *) 	0xFFFFEC98) // (MATRIX)  PRAS3
#define AT91C_MATRIX_PRAS4 (AT91_CAST(AT91_REG *) 	0xFFFFECA0) // (MATRIX)  PRAS4
#define AT91C_MATRIX_PRAS1 (AT91_CAST(AT91_REG *) 	0xFFFFEC88) // (MATRIX)  PRAS1
#define AT91C_MATRIX_PRAS0 (AT91_CAST(AT91_REG *) 	0xFFFFEC80) // (MATRIX)  PRAS0
#define AT91C_MATRIX_SCFG0 (AT91_CAST(AT91_REG *) 	0xFFFFEC40) // (MATRIX)  Slave Configuration Register 0
#define AT91C_MATRIX_PRBS7 (AT91_CAST(AT91_REG *) 	0xFFFFECBC) // (MATRIX)  PRBS7
#define AT91C_MATRIX_PRBS4 (AT91_CAST(AT91_REG *) 	0xFFFFECA4) // (MATRIX)  PRBS4
#define AT91C_MATRIX_PRBS2 (AT91_CAST(AT91_REG *) 	0xFFFFEC94) // (MATRIX)  PRBS2
#define AT91C_MATRIX_MCFG5 (AT91_CAST(AT91_REG *) 	0xFFFFEC14) // (MATRIX)  Master Configuration Register 5 
#define AT91C_MATRIX_SCFG7 (AT91_CAST(AT91_REG *) 	0xFFFFEC5C) // (MATRIX)  Slave Configuration Register 7
#define AT91C_MATRIX_PRBS1 (AT91_CAST(AT91_REG *) 	0xFFFFEC8C) // (MATRIX)  PRBS1
#define AT91C_MATRIX_MCFG6 (AT91_CAST(AT91_REG *) 	0xFFFFEC18) // (MATRIX)  Master Configuration Register 6 
#define AT91C_MATRIX_PRBS0 (AT91_CAST(AT91_REG *) 	0xFFFFEC84) // (MATRIX)  PRBS0
#define AT91C_MATRIX_MCFG0 (AT91_CAST(AT91_REG *) 	0xFFFFEC00) // (MATRIX)  Master Configuration Register 0 
#define AT91C_MATRIX_PRAS5 (AT91_CAST(AT91_REG *) 	0xFFFFECA8) // (MATRIX)  PRAS5
#define AT91C_MATRIX_SCFG1 (AT91_CAST(AT91_REG *) 	0xFFFFEC44) // (MATRIX)  Slave Configuration Register 1
#define AT91C_MATRIX_PRAS7 (AT91_CAST(AT91_REG *) 	0xFFFFECB8) // (MATRIX)  PRAS7
#define AT91C_MATRIX_PRAS2 (AT91_CAST(AT91_REG *) 	0xFFFFEC90) // (MATRIX)  PRAS2
#define AT91C_MATRIX_PRAS6 (AT91_CAST(AT91_REG *) 	0xFFFFECB0) // (MATRIX)  PRAS6
#define AT91C_MATRIX_SCFG2 (AT91_CAST(AT91_REG *) 	0xFFFFEC48) // (MATRIX)  Slave Configuration Register 2
#define AT91C_MATRIX_PRBS3 (AT91_CAST(AT91_REG *) 	0xFFFFEC9C) // (MATRIX)  PRBS3
// ========== Register definition for CCFG peripheral ========== 
#define AT91C_CCFG_MATRIXVERSION (AT91_CAST(AT91_REG *) 	0xFFFFEDFC) // (CCFG)  Version Register
#define AT91C_CCFG_TCMR (AT91_CAST(AT91_REG *) 	0xFFFFED14) // (CCFG)  TCM configuration
#define AT91C_CCFG_EBI0CSA (AT91_CAST(AT91_REG *) 	0xFFFFED20) // (CCFG)  EBI0 Chip Select Assignement Register
#define AT91C_CCFG_EBI1CSA (AT91_CAST(AT91_REG *) 	0xFFFFED24) // (CCFG)  EBI1 Chip Select Assignement Register
// ========== Register definition for PDC_DBGU peripheral ========== 
#define AT91C_DBGU_PTCR (AT91_CAST(AT91_REG *) 	0xFFFFEF20) // (PDC_DBGU) PDC Transfer Control Register
#define AT91C_DBGU_RCR  (AT91_CAST(AT91_REG *) 	0xFFFFEF04) // (PDC_DBGU) Receive Counter Register
#define AT91C_DBGU_TCR  (AT91_CAST(AT91_REG *) 	0xFFFFEF0C) // (PDC_DBGU) Transmit Counter Register
#define AT91C_DBGU_RNCR (AT91_CAST(AT91_REG *) 	0xFFFFEF14) // (PDC_DBGU) Receive Next Counter Register
#define AT91C_DBGU_TNPR (AT91_CAST(AT91_REG *) 	0xFFFFEF18) // (PDC_DBGU) Transmit Next Pointer Register
#define AT91C_DBGU_RNPR (AT91_CAST(AT91_REG *) 	0xFFFFEF10) // (PDC_DBGU) Receive Next Pointer Register
#define AT91C_DBGU_PTSR (AT91_CAST(AT91_REG *) 	0xFFFFEF24) // (PDC_DBGU) PDC Transfer Status Register
#define AT91C_DBGU_RPR  (AT91_CAST(AT91_REG *) 	0xFFFFEF00) // (PDC_DBGU) Receive Pointer Register
#define AT91C_DBGU_TPR  (AT91_CAST(AT91_REG *) 	0xFFFFEF08) // (PDC_DBGU) Transmit Pointer Register
#define AT91C_DBGU_TNCR (AT91_CAST(AT91_REG *) 	0xFFFFEF1C) // (PDC_DBGU) Transmit Next Counter Register
// ========== Register definition for DBGU peripheral ========== 
#define AT91C_DBGU_BRGR (AT91_CAST(AT91_REG *) 	0xFFFFEE20) // (DBGU) Baud Rate Generator Register
#define AT91C_DBGU_CR   (AT91_CAST(AT91_REG *) 	0xFFFFEE00) // (DBGU) Control Register
#define AT91C_DBGU_THR  (AT91_CAST(AT91_REG *) 	0xFFFFEE1C) // (DBGU) Transmitter Holding Register
#define AT91C_DBGU_IDR  (AT91_CAST(AT91_REG *) 	0xFFFFEE0C) // (DBGU) Interrupt Disable Register
#define AT91C_DBGU_EXID (AT91_CAST(AT91_REG *) 	0xFFFFEE44) // (DBGU) Chip ID Extension Register
#define AT91C_DBGU_IMR  (AT91_CAST(AT91_REG *) 	0xFFFFEE10) // (DBGU) Interrupt Mask Register
#define AT91C_DBGU_FNTR (AT91_CAST(AT91_REG *) 	0xFFFFEE48) // (DBGU) Force NTRST Register
#define AT91C_DBGU_IER  (AT91_CAST(AT91_REG *) 	0xFFFFEE08) // (DBGU) Interrupt Enable Register
#define AT91C_DBGU_CSR  (AT91_CAST(AT91_REG *) 	0xFFFFEE14) // (DBGU) Channel Status Register
#define AT91C_DBGU_MR   (AT91_CAST(AT91_REG *) 	0xFFFFEE04) // (DBGU) Mode Register
#define AT91C_DBGU_RHR  (AT91_CAST(AT91_REG *) 	0xFFFFEE18) // (DBGU) Receiver Holding Register
#define AT91C_DBGU_CIDR (AT91_CAST(AT91_REG *) 	0xFFFFEE40) // (DBGU) Chip ID Register
// ========== Register definition for AIC peripheral ========== 
#define AT91C_AIC_IVR   (AT91_CAST(AT91_REG *) 	0xFFFFF100) // (AIC) IRQ Vector Register
#define AT91C_AIC_SMR   (AT91_CAST(AT91_REG *) 	0xFFFFF000) // (AIC) Source Mode Register
#define AT91C_AIC_FVR   (AT91_CAST(AT91_REG *) 	0xFFFFF104) // (AIC) FIQ Vector Register
#define AT91C_AIC_DCR   (AT91_CAST(AT91_REG *) 	0xFFFFF138) // (AIC) Debug Control Register (Protect)
#define AT91C_AIC_EOICR (AT91_CAST(AT91_REG *) 	0xFFFFF130) // (AIC) End of Interrupt Command Register
#define AT91C_AIC_SVR   (AT91_CAST(AT91_REG *) 	0xFFFFF080) // (AIC) Source Vector Register
#define AT91C_AIC_FFSR  (AT91_CAST(AT91_REG *) 	0xFFFFF148) // (AIC) Fast Forcing Status Register
#define AT91C_AIC_ICCR  (AT91_CAST(AT91_REG *) 	0xFFFFF128) // (AIC) Interrupt Clear Command Register
#define AT91C_AIC_ISR   (AT91_CAST(AT91_REG *) 	0xFFFFF108) // (AIC) Interrupt Status Register
#define AT91C_AIC_IMR   (AT91_CAST(AT91_REG *) 	0xFFFFF110) // (AIC) Interrupt Mask Register
#define AT91C_AIC_IPR   (AT91_CAST(AT91_REG *) 	0xFFFFF10C) // (AIC) Interrupt Pending Register
#define AT91C_AIC_FFER  (AT91_CAST(AT91_REG *) 	0xFFFFF140) // (AIC) Fast Forcing Enable Register
#define AT91C_AIC_IECR  (AT91_CAST(AT91_REG *) 	0xFFFFF120) // (AIC) Interrupt Enable Command Register
#define AT91C_AIC_ISCR  (AT91_CAST(AT91_REG *) 	0xFFFFF12C) // (AIC) Interrupt Set Command Register
#define AT91C_AIC_FFDR  (AT91_CAST(AT91_REG *) 	0xFFFFF144) // (AIC) Fast Forcing Disable Register
#define AT91C_AIC_CISR  (AT91_CAST(AT91_REG *) 	0xFFFFF114) // (AIC) Core Interrupt Status Register
#define AT91C_AIC_IDCR  (AT91_CAST(AT91_REG *) 	0xFFFFF124) // (AIC) Interrupt Disable Command Register
#define AT91C_AIC_SPU   (AT91_CAST(AT91_REG *) 	0xFFFFF134) // (AIC) Spurious Vector Register
// ========== Register definition for PIOA peripheral ========== 
#define AT91C_PIOA_OWDR (AT91_CAST(AT91_REG *) 	0xFFFFF2A4) // (PIOA) Output Write Disable Register
#define AT91C_PIOA_MDDR (AT91_CAST(AT91_REG *) 	0xFFFFF254) // (PIOA) Multi-driver Disable Register
#define AT91C_PIOA_IFSR (AT91_CAST(AT91_REG *) 	0xFFFFF228) // (PIOA) Input Filter Status Register
#define AT91C_PIOA_ISR  (AT91_CAST(AT91_REG *) 	0xFFFFF24C) // (PIOA) Interrupt Status Register
#define AT91C_PIOA_CODR (AT91_CAST(AT91_REG *) 	0xFFFFF234) // (PIOA) Clear Output Data Register
#define AT91C_PIOA_PDR  (AT91_CAST(AT91_REG *) 	0xFFFFF204) // (PIOA) PIO Disable Register
#define AT91C_PIOA_OWSR (AT91_CAST(AT91_REG *) 	0xFFFFF2A8) // (PIOA) Output Write Status Register
#define AT91C_PIOA_ASR  (AT91_CAST(AT91_REG *) 	0xFFFFF270) // (PIOA) Select A Register
#define AT91C_PIOA_PPUSR (AT91_CAST(AT91_REG *) 	0xFFFFF268) // (PIOA) Pull-up Status Register
#define AT91C_PIOA_IMR  (AT91_CAST(AT91_REG *) 	0xFFFFF248) // (PIOA) Interrupt Mask Register
#define AT91C_PIOA_OSR  (AT91_CAST(AT91_REG *) 	0xFFFFF218) // (PIOA) Output Status Register
#define AT91C_PIOA_ABSR (AT91_CAST(AT91_REG *) 	0xFFFFF278) // (PIOA) AB Select Status Register
#define AT91C_PIOA_MDER (AT91_CAST(AT91_REG *) 	0xFFFFF250) // (PIOA) Multi-driver Enable Register
#define AT91C_PIOA_IFDR (AT91_CAST(AT91_REG *) 	0xFFFFF224) // (PIOA) Input Filter Disable Register
#define AT91C_PIOA_PDSR (AT91_CAST(AT91_REG *) 	0xFFFFF23C) // (PIOA) Pin Data Status Register
#define AT91C_PIOA_SODR (AT91_CAST(AT91_REG *) 	0xFFFFF230) // (PIOA) Set Output Data Register
#define AT91C_PIOA_BSR  (AT91_CAST(AT91_REG *) 	0xFFFFF274) // (PIOA) Select B Register
#define AT91C_PIOA_OWER (AT91_CAST(AT91_REG *) 	0xFFFFF2A0) // (PIOA) Output Write Enable Register
#define AT91C_PIOA_IFER (AT91_CAST(AT91_REG *) 	0xFFFFF220) // (PIOA) Input Filter Enable Register
#define AT91C_PIOA_IDR  (AT91_CAST(AT91_REG *) 	0xFFFFF244) // (PIOA) Interrupt Disable Register
#define AT91C_PIOA_ODR  (AT91_CAST(AT91_REG *) 	0xFFFFF214) // (PIOA) Output Disable Registerr
#define AT91C_PIOA_IER  (AT91_CAST(AT91_REG *) 	0xFFFFF240) // (PIOA) Interrupt Enable Register
#define AT91C_PIOA_PPUER (AT91_CAST(AT91_REG *) 	0xFFFFF264) // (PIOA) Pull-up Enable Register
#define AT91C_PIOA_MDSR (AT91_CAST(AT91_REG *) 	0xFFFFF258) // (PIOA) Multi-driver Status Register
#define AT91C_PIOA_OER  (AT91_CAST(AT91_REG *) 	0xFFFFF210) // (PIOA) Output Enable Register
#define AT91C_PIOA_PER  (AT91_CAST(AT91_REG *) 	0xFFFFF200) // (PIOA) PIO Enable Register
#define AT91C_PIOA_PPUDR (AT91_CAST(AT91_REG *) 	0xFFFFF260) // (PIOA) Pull-up Disable Register
#define AT91C_PIOA_ODSR (AT91_CAST(AT91_REG *) 	0xFFFFF238) // (PIOA) Output Data Status Register
#define AT91C_PIOA_PSR  (AT91_CAST(AT91_REG *) 	0xFFFFF208) // (PIOA) PIO Status Register
// ========== Register definition for PIOB peripheral ========== 
#define AT91C_PIOB_ODR  (AT91_CAST(AT91_REG *) 	0xFFFFF414) // (PIOB) Output Disable Registerr
#define AT91C_PIOB_SODR (AT91_CAST(AT91_REG *) 	0xFFFFF430) // (PIOB) Set Output Data Register
#define AT91C_PIOB_ISR  (AT91_CAST(AT91_REG *) 	0xFFFFF44C) // (PIOB) Interrupt Status Register
#define AT91C_PIOB_ABSR (AT91_CAST(AT91_REG *) 	0xFFFFF478) // (PIOB) AB Select Status Register
#define AT91C_PIOB_IER  (AT91_CAST(AT91_REG *) 	0xFFFFF440) // (PIOB) Interrupt Enable Register
#define AT91C_PIOB_PPUDR (AT91_CAST(AT91_REG *) 	0xFFFFF460) // (PIOB) Pull-up Disable Register
#define AT91C_PIOB_IMR  (AT91_CAST(AT91_REG *) 	0xFFFFF448) // (PIOB) Interrupt Mask Register
#define AT91C_PIOB_PER  (AT91_CAST(AT91_REG *) 	0xFFFFF400) // (PIOB) PIO Enable Register
#define AT91C_PIOB_IFDR (AT91_CAST(AT91_REG *) 	0xFFFFF424) // (PIOB) Input Filter Disable Register
#define AT91C_PIOB_OWDR (AT91_CAST(AT91_REG *) 	0xFFFFF4A4) // (PIOB) Output Write Disable Register
#define AT91C_PIOB_MDSR (AT91_CAST(AT91_REG *) 	0xFFFFF458) // (PIOB) Multi-driver Status Register
#define AT91C_PIOB_IDR  (AT91_CAST(AT91_REG *) 	0xFFFFF444) // (PIOB) Interrupt Disable Register
#define AT91C_PIOB_ODSR (AT91_CAST(AT91_REG *) 	0xFFFFF438) // (PIOB) Output Data Status Register
#define AT91C_PIOB_PPUSR (AT91_CAST(AT91_REG *) 	0xFFFFF468) // (PIOB) Pull-up Status Register
#define AT91C_PIOB_OWSR (AT91_CAST(AT91_REG *) 	0xFFFFF4A8) // (PIOB) Output Write Status Register
#define AT91C_PIOB_BSR  (AT91_CAST(AT91_REG *) 	0xFFFFF474) // (PIOB) Select B Register
#define AT91C_PIOB_OWER (AT91_CAST(AT91_REG *) 	0xFFFFF4A0) // (PIOB) Output Write Enable Register
#define AT91C_PIOB_IFER (AT91_CAST(AT91_REG *) 	0xFFFFF420) // (PIOB) Input Filter Enable Register
#define AT91C_PIOB_PDSR (AT91_CAST(AT91_REG *) 	0xFFFFF43C) // (PIOB) Pin Data Status Register
#define AT91C_PIOB_PPUER (AT91_CAST(AT91_REG *) 	0xFFFFF464) // (PIOB) Pull-up Enable Register
#define AT91C_PIOB_OSR  (AT91_CAST(AT91_REG *) 	0xFFFFF418) // (PIOB) Output Status Register
#define AT91C_PIOB_ASR  (AT91_CAST(AT91_REG *) 	0xFFFFF470) // (PIOB) Select A Register
#define AT91C_PIOB_MDDR (AT91_CAST(AT91_REG *) 	0xFFFFF454) // (PIOB) Multi-driver Disable Register
#define AT91C_PIOB_CODR (AT91_CAST(AT91_REG *) 	0xFFFFF434) // (PIOB) Clear Output Data Register
#define AT91C_PIOB_MDER (AT91_CAST(AT91_REG *) 	0xFFFFF450) // (PIOB) Multi-driver Enable Register
#define AT91C_PIOB_PDR  (AT91_CAST(AT91_REG *) 	0xFFFFF404) // (PIOB) PIO Disable Register
#define AT91C_PIOB_IFSR (AT91_CAST(AT91_REG *) 	0xFFFFF428) // (PIOB) Input Filter Status Register
#define AT91C_PIOB_OER  (AT91_CAST(AT91_REG *) 	0xFFFFF410) // (PIOB) Output Enable Register
#define AT91C_PIOB_PSR  (AT91_CAST(AT91_REG *) 	0xFFFFF408) // (PIOB) PIO Status Register
// ========== Register definition for PIOC peripheral ========== 
#define AT91C_PIOC_OWDR (AT91_CAST(AT91_REG *) 	0xFFFFF6A4) // (PIOC) Output Write Disable Register
#define AT91C_PIOC_MDER (AT91_CAST(AT91_REG *) 	0xFFFFF650) // (PIOC) Multi-driver Enable Register
#define AT91C_PIOC_PPUSR (AT91_CAST(AT91_REG *) 	0xFFFFF668) // (PIOC) Pull-up Status Register
#define AT91C_PIOC_IMR  (AT91_CAST(AT91_REG *) 	0xFFFFF648) // (PIOC) Interrupt Mask Register
#define AT91C_PIOC_ASR  (AT91_CAST(AT91_REG *) 	0xFFFFF670) // (PIOC) Select A Register
#define AT91C_PIOC_PPUDR (AT91_CAST(AT91_REG *) 	0xFFFFF660) // (PIOC) Pull-up Disable Register
#define AT91C_PIOC_PSR  (AT91_CAST(AT91_REG *) 	0xFFFFF608) // (PIOC) PIO Status Register
#define AT91C_PIOC_IER  (AT91_CAST(AT91_REG *) 	0xFFFFF640) // (PIOC) Interrupt Enable Register
#define AT91C_PIOC_CODR (AT91_CAST(AT91_REG *) 	0xFFFFF634) // (PIOC) Clear Output Data Register
#define AT91C_PIOC_OWER (AT91_CAST(AT91_REG *) 	0xFFFFF6A0) // (PIOC) Output Write Enable Register
#define AT91C_PIOC_ABSR (AT91_CAST(AT91_REG *) 	0xFFFFF678) // (PIOC) AB Select Status Register
#define AT91C_PIOC_IFDR (AT91_CAST(AT91_REG *) 	0xFFFFF624) // (PIOC) Input Filter Disable Register
#define AT91C_PIOC_PDSR (AT91_CAST(AT91_REG *) 	0xFFFFF63C) // (PIOC) Pin Data Status Register
#define AT91C_PIOC_IDR  (AT91_CAST(AT91_REG *) 	0xFFFFF644) // (PIOC) Interrupt Disable Register
#define AT91C_PIOC_OWSR (AT91_CAST(AT91_REG *) 	0xFFFFF6A8) // (PIOC) Output Write Status Register
#define AT91C_PIOC_PDR  (AT91_CAST(AT91_REG *) 	0xFFFFF604) // (PIOC) PIO Disable Register
#define AT91C_PIOC_ODR  (AT91_CAST(AT91_REG *) 	0xFFFFF614) // (PIOC) Output Disable Registerr
#define AT91C_PIOC_IFSR (AT91_CAST(AT91_REG *) 	0xFFFFF628) // (PIOC) Input Filter Status Register
#define AT91C_PIOC_PPUER (AT91_CAST(AT91_REG *) 	0xFFFFF664) // (PIOC) Pull-up Enable Register
#define AT91C_PIOC_SODR (AT91_CAST(AT91_REG *) 	0xFFFFF630) // (PIOC) Set Output Data Register
#define AT91C_PIOC_ISR  (AT91_CAST(AT91_REG *) 	0xFFFFF64C) // (PIOC) Interrupt Status Register
#define AT91C_PIOC_ODSR (AT91_CAST(AT91_REG *) 	0xFFFFF638) // (PIOC) Output Data Status Register
#define AT91C_PIOC_OSR  (AT91_CAST(AT91_REG *) 	0xFFFFF618) // (PIOC) Output Status Register
#define AT91C_PIOC_MDSR (AT91_CAST(AT91_REG *) 	0xFFFFF658) // (PIOC) Multi-driver Status Register
#define AT91C_PIOC_IFER (AT91_CAST(AT91_REG *) 	0xFFFFF620) // (PIOC) Input Filter Enable Register
#define AT91C_PIOC_BSR  (AT91_CAST(AT91_REG *) 	0xFFFFF674) // (PIOC) Select B Register
#define AT91C_PIOC_MDDR (AT91_CAST(AT91_REG *) 	0xFFFFF654) // (PIOC) Multi-driver Disable Register
#define AT91C_PIOC_OER  (AT91_CAST(AT91_REG *) 	0xFFFFF610) // (PIOC) Output Enable Register
#define AT91C_PIOC_PER  (AT91_CAST(AT91_REG *) 	0xFFFFF600) // (PIOC) PIO Enable Register
// ========== Register definition for PIOD peripheral ========== 
#define AT91C_PIOD_OWDR (AT91_CAST(AT91_REG *) 	0xFFFFF8A4) // (PIOD) Output Write Disable Register
#define AT91C_PIOD_SODR (AT91_CAST(AT91_REG *) 	0xFFFFF830) // (PIOD) Set Output Data Register
#define AT91C_PIOD_PPUER (AT91_CAST(AT91_REG *) 	0xFFFFF864) // (PIOD) Pull-up Enable Register
#define AT91C_PIOD_CODR (AT91_CAST(AT91_REG *) 	0xFFFFF834) // (PIOD) Clear Output Data Register
#define AT91C_PIOD_PSR  (AT91_CAST(AT91_REG *) 	0xFFFFF808) // (PIOD) PIO Status Register
#define AT91C_PIOD_PDR  (AT91_CAST(AT91_REG *) 	0xFFFFF804) // (PIOD) PIO Disable Register
#define AT91C_PIOD_ODR  (AT91_CAST(AT91_REG *) 	0xFFFFF814) // (PIOD) Output Disable Registerr
#define AT91C_PIOD_PPUSR (AT91_CAST(AT91_REG *) 	0xFFFFF868) // (PIOD) Pull-up Status Register
#define AT91C_PIOD_ABSR (AT91_CAST(AT91_REG *) 	0xFFFFF878) // (PIOD) AB Select Status Register
#define AT91C_PIOD_IFSR (AT91_CAST(AT91_REG *) 	0xFFFFF828) // (PIOD) Input Filter Status Register
#define AT91C_PIOD_OER  (AT91_CAST(AT91_REG *) 	0xFFFFF810) // (PIOD) Output Enable Register
#define AT91C_PIOD_IMR  (AT91_CAST(AT91_REG *) 	0xFFFFF848) // (PIOD) Interrupt Mask Register
#define AT91C_PIOD_ASR  (AT91_CAST(AT91_REG *) 	0xFFFFF870) // (PIOD) Select A Register
#define AT91C_PIOD_MDDR (AT91_CAST(AT91_REG *) 	0xFFFFF854) // (PIOD) Multi-driver Disable Register
#define AT91C_PIOD_OWSR (AT91_CAST(AT91_REG *) 	0xFFFFF8A8) // (PIOD) Output Write Status Register
#define AT91C_PIOD_PER  (AT91_CAST(AT91_REG *) 	0xFFFFF800) // (PIOD) PIO Enable Register
#define AT91C_PIOD_IDR  (AT91_CAST(AT91_REG *) 	0xFFFFF844) // (PIOD) Interrupt Disable Register
#define AT91C_PIOD_MDER (AT91_CAST(AT91_REG *) 	0xFFFFF850) // (PIOD) Multi-driver Enable Register
#define AT91C_PIOD_PDSR (AT91_CAST(AT91_REG *) 	0xFFFFF83C) // (PIOD) Pin Data Status Register
#define AT91C_PIOD_MDSR (AT91_CAST(AT91_REG *) 	0xFFFFF858) // (PIOD) Multi-driver Status Register
#define AT91C_PIOD_OWER (AT91_CAST(AT91_REG *) 	0xFFFFF8A0) // (PIOD) Output Write Enable Register
#define AT91C_PIOD_BSR  (AT91_CAST(AT91_REG *) 	0xFFFFF874) // (PIOD) Select B Register
#define AT91C_PIOD_PPUDR (AT91_CAST(AT91_REG *) 	0xFFFFF860) // (PIOD) Pull-up Disable Register
#define AT91C_PIOD_IFDR (AT91_CAST(AT91_REG *) 	0xFFFFF824) // (PIOD) Input Filter Disable Register
#define AT91C_PIOD_IER  (AT91_CAST(AT91_REG *) 	0xFFFFF840) // (PIOD) Interrupt Enable Register
#define AT91C_PIOD_OSR  (AT91_CAST(AT91_REG *) 	0xFFFFF818) // (PIOD) Output Status Register
#define AT91C_PIOD_ODSR (AT91_CAST(AT91_REG *) 	0xFFFFF838) // (PIOD) Output Data Status Register
#define AT91C_PIOD_ISR  (AT91_CAST(AT91_REG *) 	0xFFFFF84C) // (PIOD) Interrupt Status Register
#define AT91C_PIOD_IFER (AT91_CAST(AT91_REG *) 	0xFFFFF820) // (PIOD) Input Filter Enable Register
// ========== Register definition for PIOE peripheral ========== 
#define AT91C_PIOE_ODSR (AT91_CAST(AT91_REG *) 	0xFFFFFA38) // (PIOE) Output Data Status Register
#define AT91C_PIOE_ABSR (AT91_CAST(AT91_REG *) 	0xFFFFFA78) // (PIOE) AB Select Status Register
#define AT91C_PIOE_PSR  (AT91_CAST(AT91_REG *) 	0xFFFFFA08) // (PIOE) PIO Status Register
#define AT91C_PIOE_PPUDR (AT91_CAST(AT91_REG *) 	0xFFFFFA60) // (PIOE) Pull-up Disable Register
#define AT91C_PIOE_OER  (AT91_CAST(AT91_REG *) 	0xFFFFFA10) // (PIOE) Output Enable Register
#define AT91C_PIOE_OWDR (AT91_CAST(AT91_REG *) 	0xFFFFFAA4) // (PIOE) Output Write Disable Register
#define AT91C_PIOE_PER  (AT91_CAST(AT91_REG *) 	0xFFFFFA00) // (PIOE) PIO Enable Register
#define AT91C_PIOE_IFSR (AT91_CAST(AT91_REG *) 	0xFFFFFA28) // (PIOE) Input Filter Status Register
#define AT91C_PIOE_IFER (AT91_CAST(AT91_REG *) 	0xFFFFFA20) // (PIOE) Input Filter Enable Register
#define AT91C_PIOE_ODR  (AT91_CAST(AT91_REG *) 	0xFFFFFA14) // (PIOE) Output Disable Registerr
#define AT91C_PIOE_PPUSR (AT91_CAST(AT91_REG *) 	0xFFFFFA68) // (PIOE) Pull-up Status Register
#define AT91C_PIOE_IFDR (AT91_CAST(AT91_REG *) 	0xFFFFFA24) // (PIOE) Input Filter Disable Register
#define AT91C_PIOE_PDSR (AT91_CAST(AT91_REG *) 	0xFFFFFA3C) // (PIOE) Pin Data Status Register
#define AT91C_PIOE_PPUER (AT91_CAST(AT91_REG *) 	0xFFFFFA64) // (PIOE) Pull-up Enable Register
#define AT91C_PIOE_IDR  (AT91_CAST(AT91_REG *) 	0xFFFFFA44) // (PIOE) Interrupt Disable Register
#define AT91C_PIOE_MDDR (AT91_CAST(AT91_REG *) 	0xFFFFFA54) // (PIOE) Multi-driver Disable Register
#define AT91C_PIOE_ISR  (AT91_CAST(AT91_REG *) 	0xFFFFFA4C) // (PIOE) Interrupt Status Register
#define AT91C_PIOE_OSR  (AT91_CAST(AT91_REG *) 	0xFFFFFA18) // (PIOE) Output Status Register
#define AT91C_PIOE_CODR (AT91_CAST(AT91_REG *) 	0xFFFFFA34) // (PIOE) Clear Output Data Register
#define AT91C_PIOE_MDSR (AT91_CAST(AT91_REG *) 	0xFFFFFA58) // (PIOE) Multi-driver Status Register
#define AT91C_PIOE_PDR  (AT91_CAST(AT91_REG *) 	0xFFFFFA04) // (PIOE) PIO Disable Register
#define AT91C_PIOE_IER  (AT91_CAST(AT91_REG *) 	0xFFFFFA40) // (PIOE) Interrupt Enable Register
#define AT91C_PIOE_OWSR (AT91_CAST(AT91_REG *) 	0xFFFFFAA8) // (PIOE) Output Write Status Register
#define AT91C_PIOE_BSR  (AT91_CAST(AT91_REG *) 	0xFFFFFA74) // (PIOE) Select B Register
#define AT91C_PIOE_ASR  (AT91_CAST(AT91_REG *) 	0xFFFFFA70) // (PIOE) Select A Register
#define AT91C_PIOE_SODR (AT91_CAST(AT91_REG *) 	0xFFFFFA30) // (PIOE) Set Output Data Register
#define AT91C_PIOE_IMR  (AT91_CAST(AT91_REG *) 	0xFFFFFA48) // (PIOE) Interrupt Mask Register
#define AT91C_PIOE_OWER (AT91_CAST(AT91_REG *) 	0xFFFFFAA0) // (PIOE) Output Write Enable Register
#define AT91C_PIOE_MDER (AT91_CAST(AT91_REG *) 	0xFFFFFA50) // (PIOE) Multi-driver Enable Register
// ========== Register definition for CKGR peripheral ========== 
#define AT91C_CKGR_MOR  (AT91_CAST(AT91_REG *) 	0xFFFFFC20) // (CKGR) Main Oscillator Register
#define AT91C_CKGR_PLLBR (AT91_CAST(AT91_REG *) 	0xFFFFFC2C) // (CKGR) PLL B Register
#define AT91C_CKGR_MCFR (AT91_CAST(AT91_REG *) 	0xFFFFFC24) // (CKGR) Main Clock  Frequency Register
#define AT91C_CKGR_PLLAR (AT91_CAST(AT91_REG *) 	0xFFFFFC28) // (CKGR) PLL A Register
// ========== Register definition for PMC peripheral ========== 
#define AT91C_PMC_PCER  (AT91_CAST(AT91_REG *) 	0xFFFFFC10) // (PMC) Peripheral Clock Enable Register
#define AT91C_PMC_PCKR  (AT91_CAST(AT91_REG *) 	0xFFFFFC40) // (PMC) Programmable Clock Register
#define AT91C_PMC_MCKR  (AT91_CAST(AT91_REG *) 	0xFFFFFC30) // (PMC) Master Clock Register
#define AT91C_PMC_PLLAR (AT91_CAST(AT91_REG *) 	0xFFFFFC28) // (PMC) PLL A Register
#define AT91C_PMC_PCDR  (AT91_CAST(AT91_REG *) 	0xFFFFFC14) // (PMC) Peripheral Clock Disable Register
#define AT91C_PMC_SCSR  (AT91_CAST(AT91_REG *) 	0xFFFFFC08) // (PMC) System Clock Status Register
#define AT91C_PMC_MCFR  (AT91_CAST(AT91_REG *) 	0xFFFFFC24) // (PMC) Main Clock  Frequency Register
#define AT91C_PMC_IMR   (AT91_CAST(AT91_REG *) 	0xFFFFFC6C) // (PMC) Interrupt Mask Register
#define AT91C_PMC_IER   (AT91_CAST(AT91_REG *) 	0xFFFFFC60) // (PMC) Interrupt Enable Register
#define AT91C_PMC_MOR   (AT91_CAST(AT91_REG *) 	0xFFFFFC20) // (PMC) Main Oscillator Register
#define AT91C_PMC_IDR   (AT91_CAST(AT91_REG *) 	0xFFFFFC64) // (PMC) Interrupt Disable Register
#define AT91C_PMC_PLLBR (AT91_CAST(AT91_REG *) 	0xFFFFFC2C) // (PMC) PLL B Register
#define AT91C_PMC_SCDR  (AT91_CAST(AT91_REG *) 	0xFFFFFC04) // (PMC) System Clock Disable Register
#define AT91C_PMC_PCSR  (AT91_CAST(AT91_REG *) 	0xFFFFFC18) // (PMC) Peripheral Clock Status Register
#define AT91C_PMC_SCER  (AT91_CAST(AT91_REG *) 	0xFFFFFC00) // (PMC) System Clock Enable Register
#define AT91C_PMC_SR    (AT91_CAST(AT91_REG *) 	0xFFFFFC68) // (PMC) Status Register
// ========== Register definition for RSTC peripheral ========== 
#define AT91C_RSTC_RCR  (AT91_CAST(AT91_REG *) 	0xFFFFFD00) // (RSTC) Reset Control Register
#define AT91C_RSTC_VER  (AT91_CAST(AT91_REG *) 	0xFFFFFDFC) // (RSTC) Version Register
#define AT91C_RSTC_RMR  (AT91_CAST(AT91_REG *) 	0xFFFFFD08) // (RSTC) Reset Mode Register
#define AT91C_RSTC_RSR  (AT91_CAST(AT91_REG *) 	0xFFFFFD04) // (RSTC) Reset Status Register
// ========== Register definition for SHDWC peripheral ========== 
#define AT91C_SHDWC_SHSR (AT91_CAST(AT91_REG *) 	0xFFFFFD18) // (SHDWC) Shut Down Status Register
#define AT91C_SHDWC_SHMR (AT91_CAST(AT91_REG *) 	0xFFFFFD14) // (SHDWC) Shut Down Mode Register
#define AT91C_SHDWC_SHCR (AT91_CAST(AT91_REG *) 	0xFFFFFD10) // (SHDWC) Shut Down Control Register
// ========== Register definition for RTTC0 peripheral ========== 
#define AT91C_RTTC0_RTSR (AT91_CAST(AT91_REG *) 	0xFFFFFD2C) // (RTTC0) Real-time Status Register
#define AT91C_RTTC0_RTMR (AT91_CAST(AT91_REG *) 	0xFFFFFD20) // (RTTC0) Real-time Mode Register
#define AT91C_RTTC0_RTVR (AT91_CAST(AT91_REG *) 	0xFFFFFD28) // (RTTC0) Real-time Value Register
#define AT91C_RTTC0_RTAR (AT91_CAST(AT91_REG *) 	0xFFFFFD24) // (RTTC0) Real-time Alarm Register
// ========== Register definition for RTTC1 peripheral ========== 
#define AT91C_RTTC1_RTAR (AT91_CAST(AT91_REG *) 	0xFFFFFD54) // (RTTC1) Real-time Alarm Register
#define AT91C_RTTC1_RTSR (AT91_CAST(AT91_REG *) 	0xFFFFFD5C) // (RTTC1) Real-time Status Register
#define AT91C_RTTC1_RTVR (AT91_CAST(AT91_REG *) 	0xFFFFFD58) // (RTTC1) Real-time Value Register
#define AT91C_RTTC1_RTMR (AT91_CAST(AT91_REG *) 	0xFFFFFD50) // (RTTC1) Real-time Mode Register
// ========== Register definition for PITC peripheral ========== 
#define AT91C_PITC_PIVR (AT91_CAST(AT91_REG *) 	0xFFFFFD38) // (PITC) Period Interval Value Register
#define AT91C_PITC_PISR (AT91_CAST(AT91_REG *) 	0xFFFFFD34) // (PITC) Period Interval Status Register
#define AT91C_PITC_PIIR (AT91_CAST(AT91_REG *) 	0xFFFFFD3C) // (PITC) Period Interval Image Register
#define AT91C_PITC_PIMR (AT91_CAST(AT91_REG *) 	0xFFFFFD30) // (PITC) Period Interval Mode Register
// ========== Register definition for WDTC peripheral ========== 
#define AT91C_WDTC_WDCR (AT91_CAST(AT91_REG *) 	0xFFFFFD40) // (WDTC) Watchdog Control Register
#define AT91C_WDTC_WDSR (AT91_CAST(AT91_REG *) 	0xFFFFFD48) // (WDTC) Watchdog Status Register
#define AT91C_WDTC_WDMR (AT91_CAST(AT91_REG *) 	0xFFFFFD44) // (WDTC) Watchdog Mode Register
// ========== Register definition for TC0 peripheral ========== 
#define AT91C_TC0_IER   (AT91_CAST(AT91_REG *) 	0xFFF7C024) // (TC0) Interrupt Enable Register
#define AT91C_TC0_IMR   (AT91_CAST(AT91_REG *) 	0xFFF7C02C) // (TC0) Interrupt Mask Register
#define AT91C_TC0_CCR   (AT91_CAST(AT91_REG *) 	0xFFF7C000) // (TC0) Channel Control Register
#define AT91C_TC0_RB    (AT91_CAST(AT91_REG *) 	0xFFF7C018) // (TC0) Register B
#define AT91C_TC0_CV    (AT91_CAST(AT91_REG *) 	0xFFF7C010) // (TC0) Counter Value
#define AT91C_TC0_SR    (AT91_CAST(AT91_REG *) 	0xFFF7C020) // (TC0) Status Register
#define AT91C_TC0_CMR   (AT91_CAST(AT91_REG *) 	0xFFF7C004) // (TC0) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC0_RA    (AT91_CAST(AT91_REG *) 	0xFFF7C014) // (TC0) Register A
#define AT91C_TC0_RC    (AT91_CAST(AT91_REG *) 	0xFFF7C01C) // (TC0) Register C
#define AT91C_TC0_IDR   (AT91_CAST(AT91_REG *) 	0xFFF7C028) // (TC0) Interrupt Disable Register
// ========== Register definition for TC1 peripheral ========== 
#define AT91C_TC1_IER   (AT91_CAST(AT91_REG *) 	0xFFF7C064) // (TC1) Interrupt Enable Register
#define AT91C_TC1_SR    (AT91_CAST(AT91_REG *) 	0xFFF7C060) // (TC1) Status Register
#define AT91C_TC1_RC    (AT91_CAST(AT91_REG *) 	0xFFF7C05C) // (TC1) Register C
#define AT91C_TC1_CV    (AT91_CAST(AT91_REG *) 	0xFFF7C050) // (TC1) Counter Value
#define AT91C_TC1_RA    (AT91_CAST(AT91_REG *) 	0xFFF7C054) // (TC1) Register A
#define AT91C_TC1_CMR   (AT91_CAST(AT91_REG *) 	0xFFF7C044) // (TC1) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC1_IDR   (AT91_CAST(AT91_REG *) 	0xFFF7C068) // (TC1) Interrupt Disable Register
#define AT91C_TC1_RB    (AT91_CAST(AT91_REG *) 	0xFFF7C058) // (TC1) Register B
#define AT91C_TC1_IMR   (AT91_CAST(AT91_REG *) 	0xFFF7C06C) // (TC1) Interrupt Mask Register
#define AT91C_TC1_CCR   (AT91_CAST(AT91_REG *) 	0xFFF7C040) // (TC1) Channel Control Register
// ========== Register definition for TC2 peripheral ========== 
#define AT91C_TC2_SR    (AT91_CAST(AT91_REG *) 	0xFFF7C0A0) // (TC2) Status Register
#define AT91C_TC2_IMR   (AT91_CAST(AT91_REG *) 	0xFFF7C0AC) // (TC2) Interrupt Mask Register
#define AT91C_TC2_IER   (AT91_CAST(AT91_REG *) 	0xFFF7C0A4) // (TC2) Interrupt Enable Register
#define AT91C_TC2_CV    (AT91_CAST(AT91_REG *) 	0xFFF7C090) // (TC2) Counter Value
#define AT91C_TC2_RB    (AT91_CAST(AT91_REG *) 	0xFFF7C098) // (TC2) Register B
#define AT91C_TC2_CCR   (AT91_CAST(AT91_REG *) 	0xFFF7C080) // (TC2) Channel Control Register
#define AT91C_TC2_CMR   (AT91_CAST(AT91_REG *) 	0xFFF7C084) // (TC2) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC2_RA    (AT91_CAST(AT91_REG *) 	0xFFF7C094) // (TC2) Register A
#define AT91C_TC2_IDR   (AT91_CAST(AT91_REG *) 	0xFFF7C0A8) // (TC2) Interrupt Disable Register
#define AT91C_TC2_RC    (AT91_CAST(AT91_REG *) 	0xFFF7C09C) // (TC2) Register C
// ========== Register definition for TCB0 peripheral ========== 
#define AT91C_TCB0_IPNAME1 (AT91_CAST(AT91_REG *) 	0xFFF7C0F0) // (TCB0) TC IPNAME1 REGISTER 
#define AT91C_TCB0_IPNAME2 (AT91_CAST(AT91_REG *) 	0xFFF7C0F4) // (TCB0) TC IPNAME2 REGISTER 
#define AT91C_TCB0_FEATURES (AT91_CAST(AT91_REG *) 	0xFFF7C0F8) // (TCB0) TC FEATURES REGISTER 
#define AT91C_TCB0_BCR  (AT91_CAST(AT91_REG *) 	0xFFF7C0C0) // (TCB0) TC Block Control Register
#define AT91C_TCB0_VER  (AT91_CAST(AT91_REG *) 	0xFFF7C0FC) // (TCB0)  Version Register
#define AT91C_TCB0_BMR  (AT91_CAST(AT91_REG *) 	0xFFF7C0C4) // (TCB0) TC Block Mode Register
#define AT91C_TCB0_ADDRSIZE (AT91_CAST(AT91_REG *) 	0xFFF7C0EC) // (TCB0) TC ADDRSIZE REGISTER 
// ========== Register definition for TCB1 peripheral ========== 
#define AT91C_TCB1_VER  (AT91_CAST(AT91_REG *) 	0xFFF7C13C) // (TCB1)  Version Register
#define AT91C_TCB1_IPNAME2 (AT91_CAST(AT91_REG *) 	0xFFF7C134) // (TCB1) TC IPNAME2 REGISTER 
#define AT91C_TCB1_ADDRSIZE (AT91_CAST(AT91_REG *) 	0xFFF7C12C) // (TCB1) TC ADDRSIZE REGISTER 
#define AT91C_TCB1_BMR  (AT91_CAST(AT91_REG *) 	0xFFF7C104) // (TCB1) TC Block Mode Register
#define AT91C_TCB1_FEATURES (AT91_CAST(AT91_REG *) 	0xFFF7C138) // (TCB1) TC FEATURES REGISTER 
#define AT91C_TCB1_BCR  (AT91_CAST(AT91_REG *) 	0xFFF7C100) // (TCB1) TC Block Control Register
#define AT91C_TCB1_IPNAME1 (AT91_CAST(AT91_REG *) 	0xFFF7C130) // (TCB1) TC IPNAME1 REGISTER 
// ========== Register definition for TCB2 peripheral ========== 
#define AT91C_TCB2_IPNAME2 (AT91_CAST(AT91_REG *) 	0xFFF7C174) // (TCB2) TC IPNAME2 REGISTER 
#define AT91C_TCB2_FEATURES (AT91_CAST(AT91_REG *) 	0xFFF7C178) // (TCB2) TC FEATURES REGISTER 
#define AT91C_TCB2_ADDRSIZE (AT91_CAST(AT91_REG *) 	0xFFF7C16C) // (TCB2) TC ADDRSIZE REGISTER 
#define AT91C_TCB2_VER  (AT91_CAST(AT91_REG *) 	0xFFF7C17C) // (TCB2)  Version Register
#define AT91C_TCB2_BCR  (AT91_CAST(AT91_REG *) 	0xFFF7C140) // (TCB2) TC Block Control Register
#define AT91C_TCB2_IPNAME1 (AT91_CAST(AT91_REG *) 	0xFFF7C170) // (TCB2) TC IPNAME1 REGISTER 
#define AT91C_TCB2_BMR  (AT91_CAST(AT91_REG *) 	0xFFF7C144) // (TCB2) TC Block Mode Register
// ========== Register definition for PDC_MCI0 peripheral ========== 
#define AT91C_MCI0_TCR  (AT91_CAST(AT91_REG *) 	0xFFF8010C) // (PDC_MCI0) Transmit Counter Register
#define AT91C_MCI0_TNCR (AT91_CAST(AT91_REG *) 	0xFFF8011C) // (PDC_MCI0) Transmit Next Counter Register
#define AT91C_MCI0_RNPR (AT91_CAST(AT91_REG *) 	0xFFF80110) // (PDC_MCI0) Receive Next Pointer Register
#define AT91C_MCI0_TPR  (AT91_CAST(AT91_REG *) 	0xFFF80108) // (PDC_MCI0) Transmit Pointer Register
#define AT91C_MCI0_TNPR (AT91_CAST(AT91_REG *) 	0xFFF80118) // (PDC_MCI0) Transmit Next Pointer Register
#define AT91C_MCI0_PTSR (AT91_CAST(AT91_REG *) 	0xFFF80124) // (PDC_MCI0) PDC Transfer Status Register
#define AT91C_MCI0_RCR  (AT91_CAST(AT91_REG *) 	0xFFF80104) // (PDC_MCI0) Receive Counter Register
#define AT91C_MCI0_PTCR (AT91_CAST(AT91_REG *) 	0xFFF80120) // (PDC_MCI0) PDC Transfer Control Register
#define AT91C_MCI0_RPR  (AT91_CAST(AT91_REG *) 	0xFFF80100) // (PDC_MCI0) Receive Pointer Register
#define AT91C_MCI0_RNCR (AT91_CAST(AT91_REG *) 	0xFFF80114) // (PDC_MCI0) Receive Next Counter Register
// ========== Register definition for MCI0 peripheral ========== 
#define AT91C_MCI0_CMDR (AT91_CAST(AT91_REG *) 	0xFFF80014) // (MCI0) MCI Command Register
#define AT91C_MCI0_IMR  (AT91_CAST(AT91_REG *) 	0xFFF8004C) // (MCI0) MCI Interrupt Mask Register
#define AT91C_MCI0_MR   (AT91_CAST(AT91_REG *) 	0xFFF80004) // (MCI0) MCI Mode Register
#define AT91C_MCI0_CR   (AT91_CAST(AT91_REG *) 	0xFFF80000) // (MCI0) MCI Control Register
#define AT91C_MCI0_IER  (AT91_CAST(AT91_REG *) 	0xFFF80044) // (MCI0) MCI Interrupt Enable Register
#define AT91C_MCI0_RDR  (AT91_CAST(AT91_REG *) 	0xFFF80030) // (MCI0) MCI Receive Data Register
#define AT91C_MCI0_SR   (AT91_CAST(AT91_REG *) 	0xFFF80040) // (MCI0) MCI Status Register
#define AT91C_MCI0_DTOR (AT91_CAST(AT91_REG *) 	0xFFF80008) // (MCI0) MCI Data Timeout Register
#define AT91C_MCI0_SDCR (AT91_CAST(AT91_REG *) 	0xFFF8000C) // (MCI0) MCI SD Card Register
#define AT91C_MCI0_BLKR (AT91_CAST(AT91_REG *) 	0xFFF80018) // (MCI0) MCI Block Register
#define AT91C_MCI0_VR   (AT91_CAST(AT91_REG *) 	0xFFF800FC) // (MCI0) MCI Version Register
#define AT91C_MCI0_TDR  (AT91_CAST(AT91_REG *) 	0xFFF80034) // (MCI0) MCI Transmit Data Register
#define AT91C_MCI0_ARGR (AT91_CAST(AT91_REG *) 	0xFFF80010) // (MCI0) MCI Argument Register
#define AT91C_MCI0_RSPR (AT91_CAST(AT91_REG *) 	0xFFF80020) // (MCI0) MCI Response Register
#define AT91C_MCI0_IDR  (AT91_CAST(AT91_REG *) 	0xFFF80048) // (MCI0) MCI Interrupt Disable Register
// ========== Register definition for PDC_MCI1 peripheral ========== 
#define AT91C_MCI1_PTCR (AT91_CAST(AT91_REG *) 	0xFFF84120) // (PDC_MCI1) PDC Transfer Control Register
#define AT91C_MCI1_PTSR (AT91_CAST(AT91_REG *) 	0xFFF84124) // (PDC_MCI1) PDC Transfer Status Register
#define AT91C_MCI1_TPR  (AT91_CAST(AT91_REG *) 	0xFFF84108) // (PDC_MCI1) Transmit Pointer Register
#define AT91C_MCI1_RPR  (AT91_CAST(AT91_REG *) 	0xFFF84100) // (PDC_MCI1) Receive Pointer Register
#define AT91C_MCI1_TNCR (AT91_CAST(AT91_REG *) 	0xFFF8411C) // (PDC_MCI1) Transmit Next Counter Register
#define AT91C_MCI1_RCR  (AT91_CAST(AT91_REG *) 	0xFFF84104) // (PDC_MCI1) Receive Counter Register
#define AT91C_MCI1_TNPR (AT91_CAST(AT91_REG *) 	0xFFF84118) // (PDC_MCI1) Transmit Next Pointer Register
#define AT91C_MCI1_TCR  (AT91_CAST(AT91_REG *) 	0xFFF8410C) // (PDC_MCI1) Transmit Counter Register
#define AT91C_MCI1_RNPR (AT91_CAST(AT91_REG *) 	0xFFF84110) // (PDC_MCI1) Receive Next Pointer Register
#define AT91C_MCI1_RNCR (AT91_CAST(AT91_REG *) 	0xFFF84114) // (PDC_MCI1) Receive Next Counter Register
// ========== Register definition for MCI1 peripheral ========== 
#define AT91C_MCI1_SR   (AT91_CAST(AT91_REG *) 	0xFFF84040) // (MCI1) MCI Status Register
#define AT91C_MCI1_RDR  (AT91_CAST(AT91_REG *) 	0xFFF84030) // (MCI1) MCI Receive Data Register
#define AT91C_MCI1_RSPR (AT91_CAST(AT91_REG *) 	0xFFF84020) // (MCI1) MCI Response Register
#define AT91C_MCI1_CMDR (AT91_CAST(AT91_REG *) 	0xFFF84014) // (MCI1) MCI Command Register
#define AT91C_MCI1_IMR  (AT91_CAST(AT91_REG *) 	0xFFF8404C) // (MCI1) MCI Interrupt Mask Register
#define AT91C_MCI1_DTOR (AT91_CAST(AT91_REG *) 	0xFFF84008) // (MCI1) MCI Data Timeout Register
#define AT91C_MCI1_SDCR (AT91_CAST(AT91_REG *) 	0xFFF8400C) // (MCI1) MCI SD Card Register
#define AT91C_MCI1_IDR  (AT91_CAST(AT91_REG *) 	0xFFF84048) // (MCI1) MCI Interrupt Disable Register
#define AT91C_MCI1_ARGR (AT91_CAST(AT91_REG *) 	0xFFF84010) // (MCI1) MCI Argument Register
#define AT91C_MCI1_TDR  (AT91_CAST(AT91_REG *) 	0xFFF84034) // (MCI1) MCI Transmit Data Register
#define AT91C_MCI1_BLKR (AT91_CAST(AT91_REG *) 	0xFFF84018) // (MCI1) MCI Block Register
#define AT91C_MCI1_VR   (AT91_CAST(AT91_REG *) 	0xFFF840FC) // (MCI1) MCI Version Register
#define AT91C_MCI1_CR   (AT91_CAST(AT91_REG *) 	0xFFF84000) // (MCI1) MCI Control Register
#define AT91C_MCI1_MR   (AT91_CAST(AT91_REG *) 	0xFFF84004) // (MCI1) MCI Mode Register
#define AT91C_MCI1_IER  (AT91_CAST(AT91_REG *) 	0xFFF84044) // (MCI1) MCI Interrupt Enable Register
// ========== Register definition for TWI peripheral ========== 
#define AT91C_TWI_IDR   (AT91_CAST(AT91_REG *) 	0xFFF88028) // (TWI) Interrupt Disable Register
#define AT91C_TWI_RHR   (AT91_CAST(AT91_REG *) 	0xFFF88030) // (TWI) Receive Holding Register
#define AT91C_TWI_IMR   (AT91_CAST(AT91_REG *) 	0xFFF8802C) // (TWI) Interrupt Mask Register
#define AT91C_TWI_THR   (AT91_CAST(AT91_REG *) 	0xFFF88034) // (TWI) Transmit Holding Register
#define AT91C_TWI_IER   (AT91_CAST(AT91_REG *) 	0xFFF88024) // (TWI) Interrupt Enable Register
#define AT91C_TWI_IADR  (AT91_CAST(AT91_REG *) 	0xFFF8800C) // (TWI) Internal Address Register
#define AT91C_TWI_MMR   (AT91_CAST(AT91_REG *) 	0xFFF88004) // (TWI) Master Mode Register
#define AT91C_TWI_CR    (AT91_CAST(AT91_REG *) 	0xFFF88000) // (TWI) Control Register
#define AT91C_TWI_SR    (AT91_CAST(AT91_REG *) 	0xFFF88020) // (TWI) Status Register
#define AT91C_TWI_CWGR  (AT91_CAST(AT91_REG *) 	0xFFF88010) // (TWI) Clock Waveform Generator Register
// ========== Register definition for PDC_US0 peripheral ========== 
#define AT91C_US0_TNPR  (AT91_CAST(AT91_REG *) 	0xFFF8C118) // (PDC_US0) Transmit Next Pointer Register
#define AT91C_US0_PTSR  (AT91_CAST(AT91_REG *) 	0xFFF8C124) // (PDC_US0) PDC Transfer Status Register
#define AT91C_US0_PTCR  (AT91_CAST(AT91_REG *) 	0xFFF8C120) // (PDC_US0) PDC Transfer Control Register
#define AT91C_US0_RNCR  (AT91_CAST(AT91_REG *) 	0xFFF8C114) // (PDC_US0) Receive Next Counter Register
#define AT91C_US0_RCR   (AT91_CAST(AT91_REG *) 	0xFFF8C104) // (PDC_US0) Receive Counter Register
#define AT91C_US0_TNCR  (AT91_CAST(AT91_REG *) 	0xFFF8C11C) // (PDC_US0) Transmit Next Counter Register
#define AT91C_US0_TCR   (AT91_CAST(AT91_REG *) 	0xFFF8C10C) // (PDC_US0) Transmit Counter Register
#define AT91C_US0_RNPR  (AT91_CAST(AT91_REG *) 	0xFFF8C110) // (PDC_US0) Receive Next Pointer Register
#define AT91C_US0_RPR   (AT91_CAST(AT91_REG *) 	0xFFF8C100) // (PDC_US0) Receive Pointer Register
#define AT91C_US0_TPR   (AT91_CAST(AT91_REG *) 	0xFFF8C108) // (PDC_US0) Transmit Pointer Register
// ========== Register definition for US0 peripheral ========== 
#define AT91C_US0_RTOR  (AT91_CAST(AT91_REG *) 	0xFFF8C024) // (US0) Receiver Time-out Register
#define AT91C_US0_NER   (AT91_CAST(AT91_REG *) 	0xFFF8C044) // (US0) Nb Errors Register
#define AT91C_US0_THR   (AT91_CAST(AT91_REG *) 	0xFFF8C01C) // (US0) Transmitter Holding Register
#define AT91C_US0_MR    (AT91_CAST(AT91_REG *) 	0xFFF8C004) // (US0) Mode Register
#define AT91C_US0_RHR   (AT91_CAST(AT91_REG *) 	0xFFF8C018) // (US0) Receiver Holding Register
#define AT91C_US0_CSR   (AT91_CAST(AT91_REG *) 	0xFFF8C014) // (US0) Channel Status Register
#define AT91C_US0_IMR   (AT91_CAST(AT91_REG *) 	0xFFF8C010) // (US0) Interrupt Mask Register
#define AT91C_US0_IDR   (AT91_CAST(AT91_REG *) 	0xFFF8C00C) // (US0) Interrupt Disable Register
#define AT91C_US0_FIDI  (AT91_CAST(AT91_REG *) 	0xFFF8C040) // (US0) FI_DI_Ratio Register
#define AT91C_US0_CR    (AT91_CAST(AT91_REG *) 	0xFFF8C000) // (US0) Control Register
#define AT91C_US0_IER   (AT91_CAST(AT91_REG *) 	0xFFF8C008) // (US0) Interrupt Enable Register
#define AT91C_US0_TTGR  (AT91_CAST(AT91_REG *) 	0xFFF8C028) // (US0) Transmitter Time-guard Register
#define AT91C_US0_BRGR  (AT91_CAST(AT91_REG *) 	0xFFF8C020) // (US0) Baud Rate Generator Register
#define AT91C_US0_IF    (AT91_CAST(AT91_REG *) 	0xFFF8C04C) // (US0) IRDA_FILTER Register
// ========== Register definition for PDC_US1 peripheral ========== 
#define AT91C_US1_PTCR  (AT91_CAST(AT91_REG *) 	0xFFF90120) // (PDC_US1) PDC Transfer Control Register
#define AT91C_US1_TNCR  (AT91_CAST(AT91_REG *) 	0xFFF9011C) // (PDC_US1) Transmit Next Counter Register
#define AT91C_US1_RCR   (AT91_CAST(AT91_REG *) 	0xFFF90104) // (PDC_US1) Receive Counter Register
#define AT91C_US1_RPR   (AT91_CAST(AT91_REG *) 	0xFFF90100) // (PDC_US1) Receive Pointer Register
#define AT91C_US1_TPR   (AT91_CAST(AT91_REG *) 	0xFFF90108) // (PDC_US1) Transmit Pointer Register
#define AT91C_US1_TCR   (AT91_CAST(AT91_REG *) 	0xFFF9010C) // (PDC_US1) Transmit Counter Register
#define AT91C_US1_RNPR  (AT91_CAST(AT91_REG *) 	0xFFF90110) // (PDC_US1) Receive Next Pointer Register
#define AT91C_US1_TNPR  (AT91_CAST(AT91_REG *) 	0xFFF90118) // (PDC_US1) Transmit Next Pointer Register
#define AT91C_US1_RNCR  (AT91_CAST(AT91_REG *) 	0xFFF90114) // (PDC_US1) Receive Next Counter Register
#define AT91C_US1_PTSR  (AT91_CAST(AT91_REG *) 	0xFFF90124) // (PDC_US1) PDC Transfer Status Register
// ========== Register definition for US1 peripheral ========== 
#define AT91C_US1_NER   (AT91_CAST(AT91_REG *) 	0xFFF90044) // (US1) Nb Errors Register
#define AT91C_US1_RHR   (AT91_CAST(AT91_REG *) 	0xFFF90018) // (US1) Receiver Holding Register
#define AT91C_US1_RTOR  (AT91_CAST(AT91_REG *) 	0xFFF90024) // (US1) Receiver Time-out Register
#define AT91C_US1_IER   (AT91_CAST(AT91_REG *) 	0xFFF90008) // (US1) Interrupt Enable Register
#define AT91C_US1_IF    (AT91_CAST(AT91_REG *) 	0xFFF9004C) // (US1) IRDA_FILTER Register
#define AT91C_US1_CR    (AT91_CAST(AT91_REG *) 	0xFFF90000) // (US1) Control Register
#define AT91C_US1_IMR   (AT91_CAST(AT91_REG *) 	0xFFF90010) // (US1) Interrupt Mask Register
#define AT91C_US1_TTGR  (AT91_CAST(AT91_REG *) 	0xFFF90028) // (US1) Transmitter Time-guard Register
#define AT91C_US1_MR    (AT91_CAST(AT91_REG *) 	0xFFF90004) // (US1) Mode Register
#define AT91C_US1_IDR   (AT91_CAST(AT91_REG *) 	0xFFF9000C) // (US1) Interrupt Disable Register
#define AT91C_US1_FIDI  (AT91_CAST(AT91_REG *) 	0xFFF90040) // (US1) FI_DI_Ratio Register
#define AT91C_US1_CSR   (AT91_CAST(AT91_REG *) 	0xFFF90014) // (US1) Channel Status Register
#define AT91C_US1_THR   (AT91_CAST(AT91_REG *) 	0xFFF9001C) // (US1) Transmitter Holding Register
#define AT91C_US1_BRGR  (AT91_CAST(AT91_REG *) 	0xFFF90020) // (US1) Baud Rate Generator Register
// ========== Register definition for PDC_US2 peripheral ========== 
#define AT91C_US2_RNCR  (AT91_CAST(AT91_REG *) 	0xFFF94114) // (PDC_US2) Receive Next Counter Register
#define AT91C_US2_PTCR  (AT91_CAST(AT91_REG *) 	0xFFF94120) // (PDC_US2) PDC Transfer Control Register
#define AT91C_US2_TNPR  (AT91_CAST(AT91_REG *) 	0xFFF94118) // (PDC_US2) Transmit Next Pointer Register
#define AT91C_US2_TNCR  (AT91_CAST(AT91_REG *) 	0xFFF9411C) // (PDC_US2) Transmit Next Counter Register
#define AT91C_US2_TPR   (AT91_CAST(AT91_REG *) 	0xFFF94108) // (PDC_US2) Transmit Pointer Register
#define AT91C_US2_RCR   (AT91_CAST(AT91_REG *) 	0xFFF94104) // (PDC_US2) Receive Counter Register
#define AT91C_US2_PTSR  (AT91_CAST(AT91_REG *) 	0xFFF94124) // (PDC_US2) PDC Transfer Status Register
#define AT91C_US2_TCR   (AT91_CAST(AT91_REG *) 	0xFFF9410C) // (PDC_US2) Transmit Counter Register
#define AT91C_US2_RPR   (AT91_CAST(AT91_REG *) 	0xFFF94100) // (PDC_US2) Receive Pointer Register
#define AT91C_US2_RNPR  (AT91_CAST(AT91_REG *) 	0xFFF94110) // (PDC_US2) Receive Next Pointer Register
// ========== Register definition for US2 peripheral ========== 
#define AT91C_US2_TTGR  (AT91_CAST(AT91_REG *) 	0xFFF94028) // (US2) Transmitter Time-guard Register
#define AT91C_US2_RHR   (AT91_CAST(AT91_REG *) 	0xFFF94018) // (US2) Receiver Holding Register
#define AT91C_US2_IMR   (AT91_CAST(AT91_REG *) 	0xFFF94010) // (US2) Interrupt Mask Register
#define AT91C_US2_IER   (AT91_CAST(AT91_REG *) 	0xFFF94008) // (US2) Interrupt Enable Register
#define AT91C_US2_NER   (AT91_CAST(AT91_REG *) 	0xFFF94044) // (US2) Nb Errors Register
#define AT91C_US2_CR    (AT91_CAST(AT91_REG *) 	0xFFF94000) // (US2) Control Register
#define AT91C_US2_FIDI  (AT91_CAST(AT91_REG *) 	0xFFF94040) // (US2) FI_DI_Ratio Register
#define AT91C_US2_MR    (AT91_CAST(AT91_REG *) 	0xFFF94004) // (US2) Mode Register
#define AT91C_US2_IDR   (AT91_CAST(AT91_REG *) 	0xFFF9400C) // (US2) Interrupt Disable Register
#define AT91C_US2_THR   (AT91_CAST(AT91_REG *) 	0xFFF9401C) // (US2) Transmitter Holding Register
#define AT91C_US2_IF    (AT91_CAST(AT91_REG *) 	0xFFF9404C) // (US2) IRDA_FILTER Register
#define AT91C_US2_BRGR  (AT91_CAST(AT91_REG *) 	0xFFF94020) // (US2) Baud Rate Generator Register
#define AT91C_US2_CSR   (AT91_CAST(AT91_REG *) 	0xFFF94014) // (US2) Channel Status Register
#define AT91C_US2_RTOR  (AT91_CAST(AT91_REG *) 	0xFFF94024) // (US2) Receiver Time-out Register
// ========== Register definition for PDC_SPI0 peripheral ========== 
#define AT91C_SPI0_TPR  (AT91_CAST(AT91_REG *) 	0xFFFA4108) // (PDC_SPI0) Transmit Pointer Register
#define AT91C_SPI0_PTCR (AT91_CAST(AT91_REG *) 	0xFFFA4120) // (PDC_SPI0) PDC Transfer Control Register
#define AT91C_SPI0_RNPR (AT91_CAST(AT91_REG *) 	0xFFFA4110) // (PDC_SPI0) Receive Next Pointer Register
#define AT91C_SPI0_TNCR (AT91_CAST(AT91_REG *) 	0xFFFA411C) // (PDC_SPI0) Transmit Next Counter Register
#define AT91C_SPI0_TCR  (AT91_CAST(AT91_REG *) 	0xFFFA410C) // (PDC_SPI0) Transmit Counter Register
#define AT91C_SPI0_RCR  (AT91_CAST(AT91_REG *) 	0xFFFA4104) // (PDC_SPI0) Receive Counter Register
#define AT91C_SPI0_RNCR (AT91_CAST(AT91_REG *) 	0xFFFA4114) // (PDC_SPI0) Receive Next Counter Register
#define AT91C_SPI0_TNPR (AT91_CAST(AT91_REG *) 	0xFFFA4118) // (PDC_SPI0) Transmit Next Pointer Register
#define AT91C_SPI0_RPR  (AT91_CAST(AT91_REG *) 	0xFFFA4100) // (PDC_SPI0) Receive Pointer Register
#define AT91C_SPI0_PTSR (AT91_CAST(AT91_REG *) 	0xFFFA4124) // (PDC_SPI0) PDC Transfer Status Register
// ========== Register definition for SPI0 peripheral ========== 
#define AT91C_SPI0_MR   (AT91_CAST(AT91_REG *) 	0xFFFA4004) // (SPI0) Mode Register
#define AT91C_SPI0_RDR  (AT91_CAST(AT91_REG *) 	0xFFFA4008) // (SPI0) Receive Data Register
#define AT91C_SPI0_CR   (AT91_CAST(AT91_REG *) 	0xFFFA4000) // (SPI0) Control Register
#define AT91C_SPI0_IER  (AT91_CAST(AT91_REG *) 	0xFFFA4014) // (SPI0) Interrupt Enable Register
#define AT91C_SPI0_TDR  (AT91_CAST(AT91_REG *) 	0xFFFA400C) // (SPI0) Transmit Data Register
#define AT91C_SPI0_IDR  (AT91_CAST(AT91_REG *) 	0xFFFA4018) // (SPI0) Interrupt Disable Register
#define AT91C_SPI0_CSR  (AT91_CAST(AT91_REG *) 	0xFFFA4030) // (SPI0) Chip Select Register
#define AT91C_SPI0_SR   (AT91_CAST(AT91_REG *) 	0xFFFA4010) // (SPI0) Status Register
#define AT91C_SPI0_IMR  (AT91_CAST(AT91_REG *) 	0xFFFA401C) // (SPI0) Interrupt Mask Register
// ========== Register definition for PDC_SPI1 peripheral ========== 
#define AT91C_SPI1_RNCR (AT91_CAST(AT91_REG *) 	0xFFFA8114) // (PDC_SPI1) Receive Next Counter Register
#define AT91C_SPI1_TCR  (AT91_CAST(AT91_REG *) 	0xFFFA810C) // (PDC_SPI1) Transmit Counter Register
#define AT91C_SPI1_RCR  (AT91_CAST(AT91_REG *) 	0xFFFA8104) // (PDC_SPI1) Receive Counter Register
#define AT91C_SPI1_TNPR (AT91_CAST(AT91_REG *) 	0xFFFA8118) // (PDC_SPI1) Transmit Next Pointer Register
#define AT91C_SPI1_RNPR (AT91_CAST(AT91_REG *) 	0xFFFA8110) // (PDC_SPI1) Receive Next Pointer Register
#define AT91C_SPI1_RPR  (AT91_CAST(AT91_REG *) 	0xFFFA8100) // (PDC_SPI1) Receive Pointer Register
#define AT91C_SPI1_TNCR (AT91_CAST(AT91_REG *) 	0xFFFA811C) // (PDC_SPI1) Transmit Next Counter Register
#define AT91C_SPI1_TPR  (AT91_CAST(AT91_REG *) 	0xFFFA8108) // (PDC_SPI1) Transmit Pointer Register
#define AT91C_SPI1_PTSR (AT91_CAST(AT91_REG *) 	0xFFFA8124) // (PDC_SPI1) PDC Transfer Status Register
#define AT91C_SPI1_PTCR (AT91_CAST(AT91_REG *) 	0xFFFA8120) // (PDC_SPI1) PDC Transfer Control Register
// ========== Register definition for SPI1 peripheral ========== 
#define AT91C_SPI1_CSR  (AT91_CAST(AT91_REG *) 	0xFFFA8030) // (SPI1) Chip Select Register
#define AT91C_SPI1_IER  (AT91_CAST(AT91_REG *) 	0xFFFA8014) // (SPI1) Interrupt Enable Register
#define AT91C_SPI1_RDR  (AT91_CAST(AT91_REG *) 	0xFFFA8008) // (SPI1) Receive Data Register
#define AT91C_SPI1_IDR  (AT91_CAST(AT91_REG *) 	0xFFFA8018) // (SPI1) Interrupt Disable Register
#define AT91C_SPI1_MR   (AT91_CAST(AT91_REG *) 	0xFFFA8004) // (SPI1) Mode Register
#define AT91C_SPI1_CR   (AT91_CAST(AT91_REG *) 	0xFFFA8000) // (SPI1) Control Register
#define AT91C_SPI1_SR   (AT91_CAST(AT91_REG *) 	0xFFFA8010) // (SPI1) Status Register
#define AT91C_SPI1_TDR  (AT91_CAST(AT91_REG *) 	0xFFFA800C) // (SPI1) Transmit Data Register
#define AT91C_SPI1_IMR  (AT91_CAST(AT91_REG *) 	0xFFFA801C) // (SPI1) Interrupt Mask Register

// ========== Register definition for DMA peripheral ========== 
#define AT91C_DMA_RAWSRCTRAN (AT91_CAST(AT91_REG *) 	0x008002D0) // (DMA) Raw Status for IntSrcTran Interrupt
#define AT91C_DMA_SGR0  (AT91_CAST(AT91_REG *) 	0x00800048) // (DMA) Source Gather Register for channel 0
#define AT91C_DMA_REQSRCREG (AT91_CAST(AT91_REG *) 	0x00800368) // (DMA) Source Software Transaction Request Register
#define AT91C_DMA_STATUSERR (AT91_CAST(AT91_REG *) 	0x00800308) // (DMA) Status for IntErr IInterrupt
#define AT91C_DMA_SAR1  (AT91_CAST(AT91_REG *) 	0x00800058) // (DMA) Source Address Register for channel 1
#define AT91C_DMA_CLEARDSTTRAN (AT91_CAST(AT91_REG *) 	0x00800350) // (DMA) Clear for IntDstTran IInterrupt
#define AT91C_DMA_STATUSSRCTRAN (AT91_CAST(AT91_REG *) 	0x008002F8) // (DMA) Status for IntSrcTran Interrupt
#define AT91C_DMA_REQDSTREG (AT91_CAST(AT91_REG *) 	0x00800370) // (DMA) Destination Software Transaction Request Register
#define AT91C_DMA_DSTATAR0 (AT91_CAST(AT91_REG *) 	0x00800038) // (DMA) Destination Status Adress Register for channel 0
#define AT91C_DMA_LSTREQDSTREG (AT91_CAST(AT91_REG *) 	0x00800390) // (DMA) Last Destination Software Transaction Request Register
#define AT91C_DMA_SGLREQDSTREG (AT91_CAST(AT91_REG *) 	0x00800380) // (DMA) Single Destination Software Transaction Request Register
#define AT91C_DMA_CTL1h (AT91_CAST(AT91_REG *) 	0x00800074) // (DMA) Control Register for channel 1 - high
#define AT91C_DMA_CLEARERR (AT91_CAST(AT91_REG *) 	0x00800358) // (DMA) Clear for IntErr Interrupt
#define AT91C_DMA_DSR0  (AT91_CAST(AT91_REG *) 	0x00800050) // (DMA) Destination Scatter Register for channel 0
#define AT91C_DMA_DMATESTREG (AT91_CAST(AT91_REG *) 	0x008003B0) // (DMA) DW_ahb_dmac Test Register
#define AT91C_DMA_DSR1  (AT91_CAST(AT91_REG *) 	0x008000A8) // (DMA) Destination Scatter Register for channel 1
#define AT91C_DMA_CTL0l (AT91_CAST(AT91_REG *) 	0x00800018) // (DMA) Control Register for channel 0 - low
#define AT91C_DMA_STATUSBLOCK (AT91_CAST(AT91_REG *) 	0x008002F0) // (DMA) Status for IntBlock Interrupt
#define AT91C_DMA_SAR0  (AT91_CAST(AT91_REG *) 	0x00800000) // (DMA) Source Address Register for channel 0
#define AT91C_DMA_LLP0  (AT91_CAST(AT91_REG *) 	0x00800010) // (DMA) Linked List Pointer Register for channel 0
#define AT91C_DMA_CTL1l (AT91_CAST(AT91_REG *) 	0x00800070) // (DMA) Control Register for channel 1 - low
#define AT91C_DMA_SGR1  (AT91_CAST(AT91_REG *) 	0x008000A0) // (DMA) Source Gather Register for channel 1
#define AT91C_DMA_CFG0l (AT91_CAST(AT91_REG *) 	0x00800040) // (DMA) Configuration Register for channel 0 - low
#define AT91C_DMA_CFG0h (AT91_CAST(AT91_REG *) 	0x00800044) // (DMA) Configuration Register for channel 0 - high
#define AT91C_DMA_STATUSTFR (AT91_CAST(AT91_REG *) 	0x008002E8) // (DMA) Status for IntTfr Interrupt
#define AT91C_DMA_MASKBLOCK (AT91_CAST(AT91_REG *) 	0x00800318) // (DMA) Mask for IntBlock Interrupt
#define AT91C_DMA_RAWBLOCK (AT91_CAST(AT91_REG *) 	0x008002C8) // (DMA) Raw Status for IntBlock Interrupt
#define AT91C_DMA_CHENREG (AT91_CAST(AT91_REG *) 	0x008003A0) // (DMA) DW_ahb_dmac Channel Enable Register
#define AT91C_DMA_DSTAT0 (AT91_CAST(AT91_REG *) 	0x00800028) // (DMA) Destination Status Register for channel 0
#define AT91C_DMA_CLEARSRCTRAN (AT91_CAST(AT91_REG *) 	0x00800348) // (DMA) Clear for IntSrcTran Interrupt
#define AT91C_DMA_DAR1  (AT91_CAST(AT91_REG *) 	0x00800060) // (DMA) Destination Address Register for channel 1
#define AT91C_DMA_CLEARBLOCK (AT91_CAST(AT91_REG *) 	0x00800340) // (DMA) Clear for IntBlock Interrupt
#define AT91C_DMA_CFG1h (AT91_CAST(AT91_REG *) 	0x0080009C) // (DMA) Configuration Register for channel 1 - high
#define AT91C_DMA_DSTATAR1 (AT91_CAST(AT91_REG *) 	0x00800090) // (DMA) Destination Status Adress Register for channel 1
#define AT91C_DMA_RAWERR (AT91_CAST(AT91_REG *) 	0x008002E0) // (DMA) Raw Status for IntErr Interrupt
#define AT91C_DMA_CTL0h (AT91_CAST(AT91_REG *) 	0x0080001C) // (DMA) Control Register for channel 0 - high
#define AT91C_DMA_SGLREQSRCREG (AT91_CAST(AT91_REG *) 	0x00800378) // (DMA) Single Source Software Transaction Request Register
#define AT91C_DMA_LLP1  (AT91_CAST(AT91_REG *) 	0x00800068) // (DMA) Linked List Pointer Register for channel 1
#define AT91C_DMA_MASKDSTTRAN (AT91_CAST(AT91_REG *) 	0x00800328) // (DMA) Mask for IntDstTran Interrupt
#define AT91C_DMA_MASKSRCTRAN (AT91_CAST(AT91_REG *) 	0x00800320) // (DMA) Mask for IntSrcTran Interrupt
#define AT91C_DMA_LSTREQSRCREG (AT91_CAST(AT91_REG *) 	0x00800388) // (DMA) Last Source Software Transaction Request Register
#define AT91C_DMA_CLEARTFR (AT91_CAST(AT91_REG *) 	0x00800338) // (DMA) Clear for IntTfr Interrupt
#define AT91C_DMA_SSTATAR1 (AT91_CAST(AT91_REG *) 	0x00800088) // (DMA) Source Status Adress Register for channel 1
#define AT91C_DMA_DAR0  (AT91_CAST(AT91_REG *) 	0x00800008) // (DMA) Destination Address Register for channel 0
#define AT91C_DMA_SSTAT0 (AT91_CAST(AT91_REG *) 	0x00800020) // (DMA) Source Status Register for channel 0
#define AT91C_DMA_DMAIDREG (AT91_CAST(AT91_REG *) 	0x008003A8) // (DMA) DW_ahb_dmac ID Register
#define AT91C_DMA_DSTAT1 (AT91_CAST(AT91_REG *) 	0x00800080) // (DMA) Destination Status Register for channel 1
#define AT91C_DMA_RAWTFR (AT91_CAST(AT91_REG *) 	0x008002C0) // (DMA) Raw Status for IntTfr Interrupt
#define AT91C_DMA_VERSIONID (AT91_CAST(AT91_REG *) 	0x008003B8) // (DMA) DW_ahb_dmac Version ID Register
#define AT91C_DMA_STATUSDSTTRAN (AT91_CAST(AT91_REG *) 	0x00800300) // (DMA) Status for IntDstTran IInterrupt
#define AT91C_DMA_MASKERR (AT91_CAST(AT91_REG *) 	0x00800330) // (DMA) Mask for IntErr Interrupt
#define AT91C_DMA_SSTATAR0 (AT91_CAST(AT91_REG *) 	0x00800030) // (DMA) Source Status Adress Register for channel 0
#define AT91C_DMA_MASKTFR (AT91_CAST(AT91_REG *) 	0x00800310) // (DMA) Mask for IntTfr Interrupt
#define AT91C_DMA_SSTAT1 (AT91_CAST(AT91_REG *) 	0x00800078) // (DMA) Source Status Register for channel 1
#define AT91C_DMA_STATUSINT (AT91_CAST(AT91_REG *) 	0x00800360) // (DMA) Status for each Interrupt Type
#define AT91C_DMA_DMACFGREG (AT91_CAST(AT91_REG *) 	0x00800398) // (DMA) DW_ahb_dmac Configuration Register
#define AT91C_DMA_RAWDSTTRAN (AT91_CAST(AT91_REG *) 	0x008002D8) // (DMA) Raw Status for IntDstTran Interrupt
#define AT91C_DMA_CFG1l (AT91_CAST(AT91_REG *) 	0x00800098) // (DMA) Configuration Register for channel 1 - low
// ========== Register definition for HECC0 peripheral ========== 
#define AT91C_HECC0_SR  (AT91_CAST(AT91_REG *) 	0xFFFFE008) // (HECC0)  ECC Status register
#define AT91C_HECC0_VR  (AT91_CAST(AT91_REG *) 	0xFFFFE0FC) // (HECC0)  ECC Version register
#define AT91C_HECC0_CR  (AT91_CAST(AT91_REG *) 	0xFFFFE000) // (HECC0)  ECC reset register
#define AT91C_HECC0_PR  (AT91_CAST(AT91_REG *) 	0xFFFFE00C) // (HECC0)  ECC Parity register
#define AT91C_HECC0_MR  (AT91_CAST(AT91_REG *) 	0xFFFFE004) // (HECC0)  ECC Page size register
#define AT91C_HECC0_NPR (AT91_CAST(AT91_REG *) 	0xFFFFE010) // (HECC0)  ECC Parity N register
// ========== Register definition for HECC1 peripheral ========== 
#define AT91C_HECC1_MR  (AT91_CAST(AT91_REG *) 	0xFFFFE604) // (HECC1)  ECC Page size register
#define AT91C_HECC1_VR  (AT91_CAST(AT91_REG *) 	0xFFFFE6FC) // (HECC1)  ECC Version register
#define AT91C_HECC1_PR  (AT91_CAST(AT91_REG *) 	0xFFFFE60C) // (HECC1)  ECC Parity register
#define AT91C_HECC1_CR  (AT91_CAST(AT91_REG *) 	0xFFFFE600) // (HECC1)  ECC reset register
#define AT91C_HECC1_NPR (AT91_CAST(AT91_REG *) 	0xFFFFE610) // (HECC1)  ECC Parity N register
#define AT91C_HECC1_SR  (AT91_CAST(AT91_REG *) 	0xFFFFE608) // (HECC1)  ECC Status register

// *****************************************************************************
//               PIO DEFINITIONS FOR AT91SAM9263
// *****************************************************************************
#define AT91C_PIO_PA0        (1 <<  0) // Pin Controlled by PA0
#define AT91C_PA0_MCI0_DA0 (AT91C_PIO_PA0) //  
#define AT91C_PA0_SPI0_MISO (AT91C_PIO_PA0) //  
#define AT91C_PIO_PA1        (1 <<  1) // Pin Controlled by PA1
#define AT91C_PA1_MCI0_CDA (AT91C_PIO_PA1) //  
#define AT91C_PA1_SPI0_MOSI (AT91C_PIO_PA1) //  
#define AT91C_PIO_PA10       (1 << 10) // Pin Controlled by PA10
#define AT91C_PA10_MCI1_DA2 (AT91C_PIO_PA10) //  
#define AT91C_PIO_PA11       (1 << 11) // Pin Controlled by PA11
#define AT91C_PA11_MCI1_DA3 (AT91C_PIO_PA11) //  
#define AT91C_PIO_PA12       (1 << 12) // Pin Controlled by PA12
#define AT91C_PA12_MCI0_CK  (AT91C_PIO_PA12) //  
#define AT91C_PIO_PA13       (1 << 13) // Pin Controlled by PA13
#define AT91C_PA13_CANTX    (AT91C_PIO_PA13) //  
#define AT91C_PA13_PCK0     (AT91C_PIO_PA13) //  
#define AT91C_PIO_PA14       (1 << 14) // Pin Controlled by PA14
#define AT91C_PA14_CANRX    (AT91C_PIO_PA14) //  
#define AT91C_PA14_IRQ0     (AT91C_PIO_PA14) //  
#define AT91C_PIO_PA15       (1 << 15) // Pin Controlled by PA15
#define AT91C_PA15_TCLK2    (AT91C_PIO_PA15) //  
#define AT91C_PA15_IRQ1     (AT91C_PIO_PA15) //  
#define AT91C_PIO_PA16       (1 << 16) // Pin Controlled by PA16
#define AT91C_PA16_MCI0_CDB (AT91C_PIO_PA16) //  
#define AT91C_PA16_EBI1_D16 (AT91C_PIO_PA16) //  
#define AT91C_PIO_PA17       (1 << 17) // Pin Controlled by PA17
#define AT91C_PA17_MCI0_DB0 (AT91C_PIO_PA17) //  
#define AT91C_PA17_EBI1_D17 (AT91C_PIO_PA17) //  
#define AT91C_PIO_PA18       (1 << 18) // Pin Controlled by PA18
#define AT91C_PA18_MCI0_DB1 (AT91C_PIO_PA18) //  
#define AT91C_PA18_EBI1_D18 (AT91C_PIO_PA18) //  
#define AT91C_PIO_PA19       (1 << 19) // Pin Controlled by PA19
#define AT91C_PA19_MCI0_DB2 (AT91C_PIO_PA19) //  
#define AT91C_PA19_EBI1_D19 (AT91C_PIO_PA19) //  
#define AT91C_PIO_PA2        (1 <<  2) // Pin Controlled by PA2
#define AT91C_PA2_UNCONNECTED_PA2_A (AT91C_PIO_PA2) //  
#define AT91C_PA2_SPI0_SPCK (AT91C_PIO_PA2) //  
#define AT91C_PIO_PA20       (1 << 20) // Pin Controlled by PA20
#define AT91C_PA20_MCI0_DB3 (AT91C_PIO_PA20) //  
#define AT91C_PA20_EBI1_D20 (AT91C_PIO_PA20) //  
#define AT91C_PIO_PA21       (1 << 21) // Pin Controlled by PA21
#define AT91C_PA21_MCI1_CDB (AT91C_PIO_PA21) //  
#define AT91C_PA21_EBI1_D21 (AT91C_PIO_PA21) //  
#define AT91C_PIO_PA22       (1 << 22) // Pin Controlled by PA22
#define AT91C_PA22_MCI1_DB0 (AT91C_PIO_PA22) //  
#define AT91C_PA22_EBI1_D22 (AT91C_PIO_PA22) //  
#define AT91C_PIO_PA23       (1 << 23) // Pin Controlled by PA23
#define AT91C_PA23_MCI1_DB1 (AT91C_PIO_PA23) //  
#define AT91C_PA23_EBI1_D23 (AT91C_PIO_PA23) //  
#define AT91C_PIO_PA24       (1 << 24) // Pin Controlled by PA24
#define AT91C_PA24_MCI1_DB2 (AT91C_PIO_PA24) //  
#define AT91C_PA24_EBI1_D24 (AT91C_PIO_PA24) //  
#define AT91C_PIO_PA25       (1 << 25) // Pin Controlled by PA25
#define AT91C_PA25_MCI1_DB3 (AT91C_PIO_PA25) //  
#define AT91C_PA25_EBI1_D25 (AT91C_PIO_PA25) //  
#define AT91C_PIO_PA26       (1 << 26) // Pin Controlled by PA26
#define AT91C_PA26_TXD0     (AT91C_PIO_PA26) //  
#define AT91C_PA26_EBI1_D26 (AT91C_PIO_PA26) //  
#define AT91C_PIO_PA27       (1 << 27) // Pin Controlled by PA27
#define AT91C_PA27_RXD0     (AT91C_PIO_PA27) //  
#define AT91C_PA27_EBI1_D27 (AT91C_PIO_PA27) //  
#define AT91C_PIO_PA28       (1 << 28) // Pin Controlled by PA28
#define AT91C_PA28_RTS0     (AT91C_PIO_PA28) //  
#define AT91C_PA28_EBI1_D28 (AT91C_PIO_PA28) //  
#define AT91C_PIO_PA29       (1 << 29) // Pin Controlled by PA29
#define AT91C_PA29_CTS0     (AT91C_PIO_PA29) //  
#define AT91C_PA29_EBI1_D29 (AT91C_PIO_PA29) //  
#define AT91C_PIO_PA3        (1 <<  3) // Pin Controlled by PA3
#define AT91C_PA3_MCI0_DA1 (AT91C_PIO_PA3) //  
#define AT91C_PA3_SPI0_NPCS1 (AT91C_PIO_PA3) //  
#define AT91C_PIO_PA30       (1 << 30) // Pin Controlled by PA30
#define AT91C_PA30_SCK0     (AT91C_PIO_PA30) //  
#define AT91C_PA30_EBI1_D30 (AT91C_PIO_PA30) //  
#define AT91C_PIO_PA31       (1 << 31) // Pin Controlled by PA31
#define AT91C_PA31_DMARQ0   (AT91C_PIO_PA31) //  
#define AT91C_PA31_EBI1_D31 (AT91C_PIO_PA31) //  
#define AT91C_PIO_PA4        (1 <<  4) // Pin Controlled by PA4
#define AT91C_PA4_MCI0_DA2 (AT91C_PIO_PA4) //  
#define AT91C_PA4_SPI0_NPCS2A (AT91C_PIO_PA4) //  
#define AT91C_PIO_PA5        (1 <<  5) // Pin Controlled by PA5
#define AT91C_PA5_MCI0_DA3 (AT91C_PIO_PA5) //  
#define AT91C_PA5_SPI0_NPCS0 (AT91C_PIO_PA5) //  
#define AT91C_PIO_PA6        (1 <<  6) // Pin Controlled by PA6
#define AT91C_PA6_MCI1_CK  (AT91C_PIO_PA6) //  
#define AT91C_PA6_PCK2     (AT91C_PIO_PA6) //  
#define AT91C_PIO_PA7        (1 <<  7) // Pin Controlled by PA7
#define AT91C_PA7_MCI1_CDA (AT91C_PIO_PA7) //  
#define AT91C_PIO_PA8        (1 <<  8) // Pin Controlled by PA8
#define AT91C_PA8_MCI1_DA0 (AT91C_PIO_PA8) //  
#define AT91C_PIO_PA9        (1 <<  9) // Pin Controlled by PA9
#define AT91C_PA9_MCI1_DA1 (AT91C_PIO_PA9) //  
#define AT91C_PIO_PB0        (1 <<  0) // Pin Controlled by PB0
#define AT91C_PB0_AC97FS   (AT91C_PIO_PB0) //  
#define AT91C_PB0_TF0      (AT91C_PIO_PB0) //  
#define AT91C_PIO_PB1        (1 <<  1) // Pin Controlled by PB1
#define AT91C_PB1_AC97CK   (AT91C_PIO_PB1) //  
#define AT91C_PB1_TK0      (AT91C_PIO_PB1) //  
#define AT91C_PIO_PB10       (1 << 10) // Pin Controlled by PB10
#define AT91C_PB10_RK1      (AT91C_PIO_PB10) //  
#define AT91C_PB10_PCK1     (AT91C_PIO_PB10) //  
#define AT91C_PIO_PB11       (1 << 11) // Pin Controlled by PB11
#define AT91C_PB11_RF1      (AT91C_PIO_PB11) //  
#define AT91C_PB11_SPI0_NPCS3B (AT91C_PIO_PB11) //  
#define AT91C_PIO_PB12       (1 << 12) // Pin Controlled by PB12
#define AT91C_PB12_SPI1_MISO (AT91C_PIO_PB12) //  
#define AT91C_PIO_PB13       (1 << 13) // Pin Controlled by PB13
#define AT91C_PB13_SPI1_MOSI (AT91C_PIO_PB13) //  
#define AT91C_PIO_PB14       (1 << 14) // Pin Controlled by PB14
#define AT91C_PB14_SPI1_SPCK (AT91C_PIO_PB14) //  
#define AT91C_PIO_PB15       (1 << 15) // Pin Controlled by PB15
#define AT91C_PB15_SPI1_NPCS0 (AT91C_PIO_PB15) //  
#define AT91C_PIO_PB16       (1 << 16) // Pin Controlled by PB16
#define AT91C_PB16_SPI1_NPCS1 (AT91C_PIO_PB16) //  
#define AT91C_PB16_PCK1     (AT91C_PIO_PB16) //  
#define AT91C_PIO_PB17       (1 << 17) // Pin Controlled by PB17
#define AT91C_PB17_SPI1_NPCS2B (AT91C_PIO_PB17) //  
#define AT91C_PB17_TIOA2    (AT91C_PIO_PB17) //  
#define AT91C_PIO_PB18       (1 << 18) // Pin Controlled by PB18
#define AT91C_PB18_SPI1_NPCS3B (AT91C_PIO_PB18) //  
#define AT91C_PB18_TIOB2    (AT91C_PIO_PB18) //  
#define AT91C_PIO_PB19       (1 << 19) // Pin Controlled by PB19
#define AT91C_PIO_PB2        (1 <<  2) // Pin Controlled by PB2
#define AT91C_PB2_AC97TX   (AT91C_PIO_PB2) //  
#define AT91C_PB2_TD0      (AT91C_PIO_PB2) //  
#define AT91C_PIO_PB20       (1 << 20) // Pin Controlled by PB20
#define AT91C_PIO_PB21       (1 << 21) // Pin Controlled by PB21
#define AT91C_PIO_PB22       (1 << 22) // Pin Controlled by PB22
#define AT91C_PIO_PB23       (1 << 23) // Pin Controlled by PB23
#define AT91C_PIO_PB24       (1 << 24) // Pin Controlled by PB24
#define AT91C_PB24_UNCONNECTED_PB24_A (AT91C_PIO_PB24) //  
#define AT91C_PB24_DMARQ3   (AT91C_PIO_PB24) //  
#define AT91C_PIO_PB25       (1 << 25) // Pin Controlled by PB25
#define AT91C_PIO_PB26       (1 << 26) // Pin Controlled by PB26
#define AT91C_PIO_PB27       (1 << 27) // Pin Controlled by PB27
#define AT91C_PB27_UNCONNECTED_PB27_A (AT91C_PIO_PB27) //  
#define AT91C_PB27_PWM2     (AT91C_PIO_PB27) //  
#define AT91C_PIO_PB28       (1 << 28) // Pin Controlled by PB28
#define AT91C_PB28_UNCONNECTED_PB28_A (AT91C_PIO_PB28) //  
#define AT91C_PB28_TCLK0    (AT91C_PIO_PB28) //  
#define AT91C_PIO_PB29       (1 << 29) // Pin Controlled by PB29
#define AT91C_PB29_UNCONNECTED_PB29_A (AT91C_PIO_PB29) //  
#define AT91C_PB29_PWM3     (AT91C_PIO_PB29) //  
#define AT91C_PIO_PB3        (1 <<  3) // Pin Controlled by PB3
#define AT91C_PB3_AC97RX   (AT91C_PIO_PB3) //  
#define AT91C_PB3_RD0      (AT91C_PIO_PB3) //  
#define AT91C_PIO_PB30       (1 << 30) // Pin Controlled by PB30
#define AT91C_PIO_PB31       (1 << 31) // Pin Controlled by PB31
#define AT91C_PIO_PB4        (1 <<  4) // Pin Controlled by PB4
#define AT91C_PB4_TWD      (AT91C_PIO_PB4) //  
#define AT91C_PB4_RK0      (AT91C_PIO_PB4) //  
#define AT91C_PIO_PB5        (1 <<  5) // Pin Controlled by PB5
#define AT91C_PB5_TWCK     (AT91C_PIO_PB5) //  
#define AT91C_PB5_RF0      (AT91C_PIO_PB5) //  
#define AT91C_PIO_PB6        (1 <<  6) // Pin Controlled by PB6
#define AT91C_PB6_TF1      (AT91C_PIO_PB6) //  
#define AT91C_PB6_DMARQ1   (AT91C_PIO_PB6) //  
#define AT91C_PIO_PB7        (1 <<  7) // Pin Controlled by PB7
#define AT91C_PB7_TK1      (AT91C_PIO_PB7) //  
#define AT91C_PB7_PWM0     (AT91C_PIO_PB7) //  
#define AT91C_PIO_PB8        (1 <<  8) // Pin Controlled by PB8
#define AT91C_PB8_TD1      (AT91C_PIO_PB8) //  
#define AT91C_PB8_PWM1     (AT91C_PIO_PB8) //  
#define AT91C_PIO_PB9        (1 <<  9) // Pin Controlled by PB9
#define AT91C_PB9_RD1      (AT91C_PIO_PB9) //  
#define AT91C_PB9_LCDCC    (AT91C_PIO_PB9) //  
#define AT91C_PIO_PC0        (1 <<  0) // Pin Controlled by PC0
#define AT91C_PC0_LCDVSYNC (AT91C_PIO_PC0) //  
#define AT91C_PIO_PC1        (1 <<  1) // Pin Controlled by PC1
#define AT91C_PC1_LCDHSYNC (AT91C_PIO_PC1) //  
#define AT91C_PIO_PC10       (1 << 10) // Pin Controlled by PC10
#define AT91C_PC10_LCDD6    (AT91C_PIO_PC10) //  
#define AT91C_PC10_LCDD11B  (AT91C_PIO_PC10) //  
#define AT91C_PIO_PC11       (1 << 11) // Pin Controlled by PC11
#define AT91C_PC11_LCDD7    (AT91C_PIO_PC11) //  
#define AT91C_PC11_LCDD12B  (AT91C_PIO_PC11) //  
#define AT91C_PIO_PC12       (1 << 12) // Pin Controlled by PC12
#define AT91C_PC12_LCDD8    (AT91C_PIO_PC12) //  
#define AT91C_PC12_LCDD13B  (AT91C_PIO_PC12) //  
#define AT91C_PIO_PC13       (1 << 13) // Pin Controlled by PC13
#define AT91C_PC13_LCDD9    (AT91C_PIO_PC13) //  
#define AT91C_PC13_LCDD14B  (AT91C_PIO_PC13) //  
#define AT91C_PIO_PC14       (1 << 14) // Pin Controlled by PC14
#define AT91C_PC14_LCDD10   (AT91C_PIO_PC14) //  
#define AT91C_PC14_LCDD15B  (AT91C_PIO_PC14) //  
#define AT91C_PIO_PC15       (1 << 15) // Pin Controlled by PC15
#define AT91C_PC15_LCDD11   (AT91C_PIO_PC15) //  
#define AT91C_PC15_LCDD19B  (AT91C_PIO_PC15) //  
#define AT91C_PIO_PC16       (1 << 16) // Pin Controlled by PC16
#define AT91C_PC16_LCDD12   (AT91C_PIO_PC16) //  
#define AT91C_PC16_LCDD20B  (AT91C_PIO_PC16) //  
#define AT91C_PIO_PC17       (1 << 17) // Pin Controlled by PC17
#define AT91C_PC17_LCDD13   (AT91C_PIO_PC17) //  
#define AT91C_PC17_LCDD21B  (AT91C_PIO_PC17) //  
#define AT91C_PIO_PC18       (1 << 18) // Pin Controlled by PC18
#define AT91C_PC18_LCDD14   (AT91C_PIO_PC18) //  
#define AT91C_PC18_LCDD22B  (AT91C_PIO_PC18) //  
#define AT91C_PIO_PC19       (1 << 19) // Pin Controlled by PC19
#define AT91C_PC19_LCDD15   (AT91C_PIO_PC19) //  
#define AT91C_PC19_LCDD23B  (AT91C_PIO_PC19) //  
#define AT91C_PIO_PC2        (1 <<  2) // Pin Controlled by PC2
#define AT91C_PC2_LCDDOTCK (AT91C_PIO_PC2) //  
#define AT91C_PIO_PC20       (1 << 20) // Pin Controlled by PC20
#define AT91C_PC20_LCDD16   (AT91C_PIO_PC20) //  
#define AT91C_PC20_ETX2     (AT91C_PIO_PC20) //  
#define AT91C_PIO_PC21       (1 << 21) // Pin Controlled by PC21
#define AT91C_PC21_LCDD17   (AT91C_PIO_PC21) //  
#define AT91C_PC21_ETX3     (AT91C_PIO_PC21) //  
#define AT91C_PIO_PC22       (1 << 22) // Pin Controlled by PC22
#define AT91C_PC22_LCDD18   (AT91C_PIO_PC22) //  
#define AT91C_PC22_ERX2     (AT91C_PIO_PC22) //  
#define AT91C_PIO_PC23       (1 << 23) // Pin Controlled by PC23
#define AT91C_PC23_LCDD19   (AT91C_PIO_PC23) //  
#define AT91C_PC23_ERX3     (AT91C_PIO_PC23) //  
#define AT91C_PIO_PC24       (1 << 24) // Pin Controlled by PC24
#define AT91C_PC24_LCDD20   (AT91C_PIO_PC24) //  
#define AT91C_PC24_ETXER    (AT91C_PIO_PC24) //  
#define AT91C_PIO_PC25       (1 << 25) // Pin Controlled by PC25
#define AT91C_PC25_LCDD21   (AT91C_PIO_PC25) //  
#define AT91C_PC25_ERXDV    (AT91C_PIO_PC25) //  
#define AT91C_PIO_PC26       (1 << 26) // Pin Controlled by PC26
#define AT91C_PC26_LCDD22   (AT91C_PIO_PC26) //  
#define AT91C_PC26_ECOL     (AT91C_PIO_PC26) //  
#define AT91C_PIO_PC27       (1 << 27) // Pin Controlled by PC27
#define AT91C_PC27_LCDD23   (AT91C_PIO_PC27) //  
#define AT91C_PC27_ERXCK    (AT91C_PIO_PC27) //  
#define AT91C_PIO_PC28       (1 << 28) // Pin Controlled by PC28
#define AT91C_PC28_PWM0     (AT91C_PIO_PC28) //  
#define AT91C_PC28_TCLK1    (AT91C_PIO_PC28) //  
#define AT91C_PIO_PC29       (1 << 29) // Pin Controlled by PC29
#define AT91C_PC29_PCK0     (AT91C_PIO_PC29) //  
#define AT91C_PC29_PWM2     (AT91C_PIO_PC29) //  
#define AT91C_PIO_PC3        (1 <<  3) // Pin Controlled by PC3
#define AT91C_PC3_LCDEN    (AT91C_PIO_PC3) //  
#define AT91C_PC3_PWM1     (AT91C_PIO_PC3) //  
#define AT91C_PIO_PC30       (1 << 30) // Pin Controlled by PC30
#define AT91C_PC30_DRXD     (AT91C_PIO_PC30) //  
#define AT91C_PIO_PC31       (1 << 31) // Pin Controlled by PC31
#define AT91C_PC31_DTXD     (AT91C_PIO_PC31) //  
#define AT91C_PIO_PC4        (1 <<  4) // Pin Controlled by PC4
#define AT91C_PC4_LCDD0    (AT91C_PIO_PC4) //  
#define AT91C_PC4_LCDD3B   (AT91C_PIO_PC4) //  
#define AT91C_PIO_PC5        (1 <<  5) // Pin Controlled by PC5
#define AT91C_PC5_LCDD1    (AT91C_PIO_PC5) //  
#define AT91C_PC5_LCDD4B   (AT91C_PIO_PC5) //  
#define AT91C_PIO_PC6        (1 <<  6) // Pin Controlled by PC6
#define AT91C_PC6_LCDD2    (AT91C_PIO_PC6) //  
#define AT91C_PC6_LCDD5B   (AT91C_PIO_PC6) //  
#define AT91C_PIO_PC7        (1 <<  7) // Pin Controlled by PC7
#define AT91C_PC7_LCDD3    (AT91C_PIO_PC7) //  
#define AT91C_PC7_LCDD6B   (AT91C_PIO_PC7) //  
#define AT91C_PIO_PC8        (1 <<  8) // Pin Controlled by PC8
#define AT91C_PC8_LCDD4    (AT91C_PIO_PC8) //  
#define AT91C_PC8_LCDD7B   (AT91C_PIO_PC8) //  
#define AT91C_PIO_PC9        (1 <<  9) // Pin Controlled by PC9
#define AT91C_PC9_LCDD5    (AT91C_PIO_PC9) //  
#define AT91C_PC9_LCDD10B  (AT91C_PIO_PC9) //  
#define AT91C_PIO_PD0        (1 <<  0) // Pin Controlled by PD0
#define AT91C_PD0_TXD1     (AT91C_PIO_PD0) //  
#define AT91C_PD0_SPI0_NPCS2D (AT91C_PIO_PD0) //  
#define AT91C_PIO_PD1        (1 <<  1) // Pin Controlled by PD1
#define AT91C_PD1_RXD1     (AT91C_PIO_PD1) //  
#define AT91C_PD1_SPI0_NPCS3D (AT91C_PIO_PD1) //  
#define AT91C_PIO_PD10       (1 << 10) // Pin Controlled by PD10
#define AT91C_PD10_UNCONNECTED_PD10_A (AT91C_PIO_PD10) //  
#define AT91C_PD10_SCK1     (AT91C_PIO_PD10) //  
#define AT91C_PIO_PD11       (1 << 11) // Pin Controlled by PD11
#define AT91C_PD11_EBI0_NCS2 (AT91C_PIO_PD11) //  
#define AT91C_PD11_TSYNC    (AT91C_PIO_PD11) //  
#define AT91C_PIO_PD12       (1 << 12) // Pin Controlled by PD12
#define AT91C_PD12_EBI0_A23 (AT91C_PIO_PD12) //  
#define AT91C_PD12_TCLK     (AT91C_PIO_PD12) //  
#define AT91C_PIO_PD13       (1 << 13) // Pin Controlled by PD13
#define AT91C_PD13_EBI0_A24 (AT91C_PIO_PD13) //  
#define AT91C_PD13_TPS0     (AT91C_PIO_PD13) //  
#define AT91C_PIO_PD14       (1 << 14) // Pin Controlled by PD14
#define AT91C_PD14_EBI0_A25_CFNRW (AT91C_PIO_PD14) //  
#define AT91C_PD14_TPS1     (AT91C_PIO_PD14) //  
#define AT91C_PIO_PD15       (1 << 15) // Pin Controlled by PD15
#define AT91C_PD15_EBI0_NCS3_NANDCS (AT91C_PIO_PD15) //  
#define AT91C_PD15_TPS2     (AT91C_PIO_PD15) //  
#define AT91C_PIO_PD16       (1 << 16) // Pin Controlled by PD16
#define AT91C_PD16_EBI0_D16 (AT91C_PIO_PD16) //  
#define AT91C_PD16_TPK0     (AT91C_PIO_PD16) //  
#define AT91C_PIO_PD17       (1 << 17) // Pin Controlled by PD17
#define AT91C_PD17_EBI0_D17 (AT91C_PIO_PD17) //  
#define AT91C_PD17_TPK1     (AT91C_PIO_PD17) //  
#define AT91C_PIO_PD18       (1 << 18) // Pin Controlled by PD18
#define AT91C_PD18_EBI0_D18 (AT91C_PIO_PD18) //  
#define AT91C_PD18_TPK2     (AT91C_PIO_PD18) //  
#define AT91C_PIO_PD19       (1 << 19) // Pin Controlled by PD19
#define AT91C_PD19_EBI0_D19 (AT91C_PIO_PD19) //  
#define AT91C_PD19_TPK3     (AT91C_PIO_PD19) //  
#define AT91C_PIO_PD2        (1 <<  2) // Pin Controlled by PD2
#define AT91C_PD2_TXD2     (AT91C_PIO_PD2) //  
#define AT91C_PD2_SPI1_NPCS2D (AT91C_PIO_PD2) //  
#define AT91C_PIO_PD20       (1 << 20) // Pin Controlled by PD20
#define AT91C_PD20_EBI0_D20 (AT91C_PIO_PD20) //  
#define AT91C_PD20_TPK4     (AT91C_PIO_PD20) //  
#define AT91C_PIO_PD21       (1 << 21) // Pin Controlled by PD21
#define AT91C_PD21_EBI0_D21 (AT91C_PIO_PD21) //  
#define AT91C_PD21_TPK5     (AT91C_PIO_PD21) //  
#define AT91C_PIO_PD22       (1 << 22) // Pin Controlled by PD22
#define AT91C_PD22_EBI0_D22 (AT91C_PIO_PD22) //  
#define AT91C_PD22_TPK6     (AT91C_PIO_PD22) //  
#define AT91C_PIO_PD23       (1 << 23) // Pin Controlled by PD23
#define AT91C_PD23_EBI0_D23 (AT91C_PIO_PD23) //  
#define AT91C_PD23_TPK7     (AT91C_PIO_PD23) //  
#define AT91C_PIO_PD24       (1 << 24) // Pin Controlled by PD24
#define AT91C_PD24_EBI0_D24 (AT91C_PIO_PD24) //  
#define AT91C_PD24_TPK8     (AT91C_PIO_PD24) //  
#define AT91C_PIO_PD25       (1 << 25) // Pin Controlled by PD25
#define AT91C_PD25_EBI0_D25 (AT91C_PIO_PD25) //  
#define AT91C_PD25_TPK9     (AT91C_PIO_PD25) //  
#define AT91C_PIO_PD26       (1 << 26) // Pin Controlled by PD26
#define AT91C_PD26_EBI0_D26 (AT91C_PIO_PD26) //  
#define AT91C_PD26_TPK10    (AT91C_PIO_PD26) //  
#define AT91C_PIO_PD27       (1 << 27) // Pin Controlled by PD27
#define AT91C_PD27_EBI0_D27 (AT91C_PIO_PD27) //  
#define AT91C_PD27_TPK11    (AT91C_PIO_PD27) //  
#define AT91C_PIO_PD28       (1 << 28) // Pin Controlled by PD28
#define AT91C_PD28_EBI0_D28 (AT91C_PIO_PD28) //  
#define AT91C_PD28_TPK12    (AT91C_PIO_PD28) //  
#define AT91C_PIO_PD29       (1 << 29) // Pin Controlled by PD29
#define AT91C_PD29_EBI0_D29 (AT91C_PIO_PD29) //  
#define AT91C_PD29_TPK13    (AT91C_PIO_PD29) //  
#define AT91C_PIO_PD3        (1 <<  3) // Pin Controlled by PD3
#define AT91C_PD3_RXD2     (AT91C_PIO_PD3) //  
#define AT91C_PD3_SPI1_NPCS3D (AT91C_PIO_PD3) //  
#define AT91C_PIO_PD30       (1 << 30) // Pin Controlled by PD30
#define AT91C_PD30_EBI0_D30 (AT91C_PIO_PD30) //  
#define AT91C_PD30_TPK14    (AT91C_PIO_PD30) //  
#define AT91C_PIO_PD31       (1 << 31) // Pin Controlled by PD31
#define AT91C_PD31_EBI0_D31 (AT91C_PIO_PD31) //  
#define AT91C_PD31_TPK15    (AT91C_PIO_PD31) //  
#define AT91C_PIO_PD4        (1 <<  4) // Pin Controlled by PD4
#define AT91C_PD4_FIQ      (AT91C_PIO_PD4) //  
#define AT91C_PD4_DMARQ2   (AT91C_PIO_PD4) //  
#define AT91C_PIO_PD5        (1 <<  5) // Pin Controlled by PD5
#define AT91C_PD5_EBI0_NWAIT (AT91C_PIO_PD5) //  
#define AT91C_PD5_RTS2     (AT91C_PIO_PD5) //  
#define AT91C_PIO_PD6        (1 <<  6) // Pin Controlled by PD6
#define AT91C_PD6_EBI0_NCS4_CFCS0 (AT91C_PIO_PD6) //  
#define AT91C_PD6_CTS2     (AT91C_PIO_PD6) //  
#define AT91C_PIO_PD7        (1 <<  7) // Pin Controlled by PD7
#define AT91C_PD7_EBI0_NCS5_CFCS1 (AT91C_PIO_PD7) //  
#define AT91C_PD7_RTS1     (AT91C_PIO_PD7) //  
#define AT91C_PIO_PD8        (1 <<  8) // Pin Controlled by PD8
#define AT91C_PD8_EBI0_CFCE1 (AT91C_PIO_PD8) //  
#define AT91C_PD8_CTS1     (AT91C_PIO_PD8) //  
#define AT91C_PIO_PD9        (1 <<  9) // Pin Controlled by PD9
#define AT91C_PD9_EBI0_CFCE2 (AT91C_PIO_PD9) //  
#define AT91C_PD9_SCK2     (AT91C_PIO_PD9) //  
#define AT91C_PIO_PE0        (1 <<  0) // Pin Controlled by PE0
#define AT91C_PE0_ISI_D0   (AT91C_PIO_PE0) //  
#define AT91C_PIO_PE1        (1 <<  1) // Pin Controlled by PE1
#define AT91C_PE1_ISI_D1   (AT91C_PIO_PE1) //  
#define AT91C_PIO_PE10       (1 << 10) // Pin Controlled by PE10
#define AT91C_PE10_ISI_VSYNC (AT91C_PIO_PE10) //  
#define AT91C_PE10_PWM3     (AT91C_PIO_PE10) //  
#define AT91C_PIO_PE11       (1 << 11) // Pin Controlled by PE11
#define AT91C_PE11_ISI_MCK  (AT91C_PIO_PE11) //  
#define AT91C_PE11_PCK3     (AT91C_PIO_PE11) //  
#define AT91C_PIO_PE12       (1 << 12) // Pin Controlled by PE12
#define AT91C_PE12_KBDR0    (AT91C_PIO_PE12) //  
#define AT91C_PE12_ISI_D8   (AT91C_PIO_PE12) //  
#define AT91C_PIO_PE13       (1 << 13) // Pin Controlled by PE13
#define AT91C_PE13_KBDR1    (AT91C_PIO_PE13) //  
#define AT91C_PE13_ISI_D9   (AT91C_PIO_PE13) //  
#define AT91C_PIO_PE14       (1 << 14) // Pin Controlled by PE14
#define AT91C_PE14_KBDR2    (AT91C_PIO_PE14) //  
#define AT91C_PE14_ISI_D10  (AT91C_PIO_PE14) //  
#define AT91C_PIO_PE15       (1 << 15) // Pin Controlled by PE15
#define AT91C_PE15_KBDR3    (AT91C_PIO_PE15) //  
#define AT91C_PE15_ISI_D11  (AT91C_PIO_PE15) //  
#define AT91C_PIO_PE16       (1 << 16) // Pin Controlled by PE16
#define AT91C_PE16_KBDR4    (AT91C_PIO_PE16) //  
#define AT91C_PIO_PE17       (1 << 17) // Pin Controlled by PE17
#define AT91C_PE17_KBDC0    (AT91C_PIO_PE17) //  
#define AT91C_PIO_PE18       (1 << 18) // Pin Controlled by PE18
#define AT91C_PE18_KBDC1    (AT91C_PIO_PE18) //  
#define AT91C_PE18_TIOA0    (AT91C_PIO_PE18) //  
#define AT91C_PIO_PE19       (1 << 19) // Pin Controlled by PE19
#define AT91C_PE19_KBDC2    (AT91C_PIO_PE19) //  
#define AT91C_PE19_TIOB0    (AT91C_PIO_PE19) //  
#define AT91C_PIO_PE2        (1 <<  2) // Pin Controlled by PE2
#define AT91C_PE2_ISI_D2   (AT91C_PIO_PE2) //  
#define AT91C_PIO_PE20       (1 << 20) // Pin Controlled by PE20
#define AT91C_PE20_KBDC3    (AT91C_PIO_PE20) //  
#define AT91C_PE20_EBI1_NWAIT (AT91C_PIO_PE20) //  
#define AT91C_PIO_PE21       (1 << 21) // Pin Controlled by PE21
#define AT91C_PE21_ETXCK    (AT91C_PIO_PE21) //  
#define AT91C_PE21_EBI1_NANDWE (AT91C_PIO_PE21) //  
#define AT91C_PIO_PE22       (1 << 22) // Pin Controlled by PE22
#define AT91C_PE22_ECRS     (AT91C_PIO_PE22) //  
#define AT91C_PE22_EBI1_NCS2_NANDCS (AT91C_PIO_PE22) //  
#define AT91C_PIO_PE23       (1 << 23) // Pin Controlled by PE23
#define AT91C_PE23_ETX0     (AT91C_PIO_PE23) //  
#define AT91C_PE23_EBI1_NANDOE (AT91C_PIO_PE23) //  
#define AT91C_PIO_PE24       (1 << 24) // Pin Controlled by PE24
#define AT91C_PE24_ETX1     (AT91C_PIO_PE24) //  
#define AT91C_PE24_EBI1_NWR3_NBS3 (AT91C_PIO_PE24) //  
#define AT91C_PIO_PE25       (1 << 25) // Pin Controlled by PE25
#define AT91C_PE25_ERX0     (AT91C_PIO_PE25) //  
#define AT91C_PE25_EBI1_NCS1_SDCS (AT91C_PIO_PE25) //  
#define AT91C_PIO_PE26       (1 << 26) // Pin Controlled by PE26
#define AT91C_PE26_ERX1     (AT91C_PIO_PE26) //  
#define AT91C_PIO_PE27       (1 << 27) // Pin Controlled by PE27
#define AT91C_PE27_ERXER    (AT91C_PIO_PE27) //  
#define AT91C_PE27_EBI1_SDCKE (AT91C_PIO_PE27) //  
#define AT91C_PIO_PE28       (1 << 28) // Pin Controlled by PE28
#define AT91C_PE28_ETXEN    (AT91C_PIO_PE28) //  
#define AT91C_PE28_EBI1_RAS (AT91C_PIO_PE28) //  
#define AT91C_PIO_PE29       (1 << 29) // Pin Controlled by PE29
#define AT91C_PE29_EMDC     (AT91C_PIO_PE29) //  
#define AT91C_PE29_EBI1_CAS (AT91C_PIO_PE29) //  
#define AT91C_PIO_PE3        (1 <<  3) // Pin Controlled by PE3
#define AT91C_PE3_ISI_D3   (AT91C_PIO_PE3) //  
#define AT91C_PIO_PE30       (1 << 30) // Pin Controlled by PE30
#define AT91C_PE30_EMDIO    (AT91C_PIO_PE30) //  
#define AT91C_PE30_EBI1_SDWE (AT91C_PIO_PE30) //  
#define AT91C_PIO_PE31       (1 << 31) // Pin Controlled by PE31
#define AT91C_PE31_EF100    (AT91C_PIO_PE31) //  
#define AT91C_PE31_EBI1_SDA10 (AT91C_PIO_PE31) //  
#define AT91C_PIO_PE4        (1 <<  4) // Pin Controlled by PE4
#define AT91C_PE4_ISI_D4   (AT91C_PIO_PE4) //  
#define AT91C_PIO_PE5        (1 <<  5) // Pin Controlled by PE5
#define AT91C_PE5_ISI_D5   (AT91C_PIO_PE5) //  
#define AT91C_PIO_PE6        (1 <<  6) // Pin Controlled by PE6
#define AT91C_PE6_ISI_D6   (AT91C_PIO_PE6) //  
#define AT91C_PIO_PE7        (1 <<  7) // Pin Controlled by PE7
#define AT91C_PE7_ISI_D7   (AT91C_PIO_PE7) //  
#define AT91C_PIO_PE8        (1 <<  8) // Pin Controlled by PE8
#define AT91C_PE8_ISI_PCK  (AT91C_PIO_PE8) //  
#define AT91C_PE8_TIOA1    (AT91C_PIO_PE8) //  
#define AT91C_PIO_PE9        (1 <<  9) // Pin Controlled by PE9
#define AT91C_PE9_ISI_HSYNC (AT91C_PIO_PE9) //  
#define AT91C_PE9_TIOB1    (AT91C_PIO_PE9) //  

// *****************************************************************************
//               PERIPHERAL ID DEFINITIONS FOR AT91SAM9263
// *****************************************************************************
#define AT91C_ID_FIQ    ( 0) // Advanced Interrupt Controller (FIQ)
#define AT91C_ID_SYS    ( 1) // System Controller
#define AT91C_ID_PIOA   ( 2) // Parallel IO Controller A
#define AT91C_ID_PIOB   ( 3) // Parallel IO Controller B
#define AT91C_ID_PIOCDE ( 4) // Parallel IO Controller C, Parallel IO Controller D, Parallel IO Controller E
#define AT91C_ID_US0    ( 7) // USART 0
#define AT91C_ID_US1    ( 8) // USART 1
#define AT91C_ID_US2    ( 9) // USART 2
#define AT91C_ID_MCI0   (10) // Multimedia Card Interface 0
#define AT91C_ID_MCI1   (11) // Multimedia Card Interface 1
#define AT91C_ID_CAN    (12) // CAN Controller
#define AT91C_ID_TWI    (13) // Two-Wire Interface
#define AT91C_ID_SPI0   (14) // Serial Peripheral Interface 0
#define AT91C_ID_SPI1   (15) // Serial Peripheral Interface 1
#define AT91C_ID_SSC0   (16) // Serial Synchronous Controller 0
#define AT91C_ID_SSC1   (17) // Serial Synchronous Controller 1
#define AT91C_ID_AC97C  (18) // AC97 Controller
#define AT91C_ID_TC012  (19) // Timer Counter 0, Timer Counter 1, Timer Counter 2
#define AT91C_ID_PWMC   (20) // PWM Controller
#define AT91C_ID_EMAC   (21) // Ethernet Mac
#define AT91C_ID_UDP    (24) // USB Device Port
#define AT91C_ID_ISI    (25) // Image Sensor Interface
#define AT91C_ID_LCDC   (26) // LCD Controller
#define AT91C_ID_DMA    (27) // DMA Controller
#define AT91C_ID_UHP    (29) // USB Host Port
#define AT91C_ID_IRQ0   (30) // Advanced Interrupt Controller (IRQ0)
#define AT91C_ID_IRQ1   (31) // Advanced Interrupt Controller (IRQ1)
#define AT91C_ALL_INT   (0xEF3FFF9F) // ALL VALID INTERRUPTS

// *****************************************************************************
//               BASE ADDRESS DEFINITIONS FOR AT91SAM9263
// *****************************************************************************
#define AT91C_BASE_SYS       (AT91_CAST(AT91PS_SYS) 	0xFFFFE000) // (SYS) Base Address
#define AT91C_BASE_EBI0      (AT91_CAST(AT91PS_EBI0) 	0xFFFFE200) // (EBI0) Base Address
#define AT91C_BASE_SDRAMC0   (AT91_CAST(AT91PS_SDRAMC) 	0xFFFFE200) // (SDRAMC0) Base Address
#define AT91C_BASE_SMC0      (AT91_CAST(AT91PS_SMC) 	0xFFFFE400) // (SMC0) Base Address
#define AT91C_BASE_EBI1      (AT91_CAST(AT91PS_EBI1) 	0xFFFFE800) // (EBI1) Base Address
#define AT91C_BASE_SDRAMC1   (AT91_CAST(AT91PS_SDRAMC) 	0xFFFFE800) // (SDRAMC1) Base Address
#define AT91C_BASE_SMC1      (AT91_CAST(AT91PS_SMC) 	0xFFFFEA00) // (SMC1) Base Address
#define AT91C_BASE_MATRIX    (AT91_CAST(AT91PS_MATRIX) 	0xFFFFEC00) // (MATRIX) Base Address
#define AT91C_BASE_CCFG      (AT91_CAST(AT91PS_CCFG) 	0xFFFFED10) // (CCFG) Base Address
#define AT91C_BASE_PDC_DBGU  (AT91_CAST(AT91PS_PDC) 	0xFFFFEF00) // (PDC_DBGU) Base Address
#define AT91C_BASE_DBGU      (AT91_CAST(AT91PS_DBGU) 	0xFFFFEE00) // (DBGU) Base Address
#define AT91C_BASE_AIC       (AT91_CAST(AT91PS_AIC) 	0xFFFFF000) // (AIC) Base Address
#define AT91C_BASE_PIOA      (AT91_CAST(AT91PS_PIO) 	0xFFFFF200) // (PIOA) Base Address
#define AT91C_BASE_PIOB      (AT91_CAST(AT91PS_PIO) 	0xFFFFF400) // (PIOB) Base Address
#define AT91C_BASE_PIOC      (AT91_CAST(AT91PS_PIO) 	0xFFFFF600) // (PIOC) Base Address
#define AT91C_BASE_PIOD      (AT91_CAST(AT91PS_PIO) 	0xFFFFF800) // (PIOD) Base Address
#define AT91C_BASE_PIOE      (AT91_CAST(AT91PS_PIO) 	0xFFFFFA00) // (PIOE) Base Address
#define AT91C_BASE_CKGR      (AT91_CAST(AT91PS_CKGR) 	0xFFFFFC20) // (CKGR) Base Address
#define AT91C_BASE_PMC       (AT91_CAST(AT91PS_PMC) 	0xFFFFFC00) // (PMC) Base Address
#define AT91C_BASE_RSTC      (AT91_CAST(AT91PS_RSTC) 	0xFFFFFD00) // (RSTC) Base Address
#define AT91C_BASE_SHDWC     (AT91_CAST(AT91PS_SHDWC) 	0xFFFFFD10) // (SHDWC) Base Address
#define AT91C_BASE_RTTC0     (AT91_CAST(AT91PS_RTTC) 	0xFFFFFD20) // (RTTC0) Base Address
#define AT91C_BASE_RTTC1     (AT91_CAST(AT91PS_RTTC) 	0xFFFFFD50) // (RTTC1) Base Address
#define AT91C_BASE_PITC      (AT91_CAST(AT91PS_PITC) 	0xFFFFFD30) // (PITC) Base Address
#define AT91C_BASE_WDTC      (AT91_CAST(AT91PS_WDTC) 	0xFFFFFD40) // (WDTC) Base Address
#define AT91C_BASE_TC0       (AT91_CAST(AT91PS_TC) 	0xFFF7C000) // (TC0) Base Address
#define AT91C_BASE_TC1       (AT91_CAST(AT91PS_TC) 	0xFFF7C040) // (TC1) Base Address
#define AT91C_BASE_TC2       (AT91_CAST(AT91PS_TC) 	0xFFF7C080) // (TC2) Base Address
#define AT91C_BASE_TCB0      (AT91_CAST(AT91PS_TCB) 	0xFFF7C000) // (TCB0) Base Address
#define AT91C_BASE_TCB1      (AT91_CAST(AT91PS_TCB) 	0xFFF7C040) // (TCB1) Base Address
#define AT91C_BASE_TCB2      (AT91_CAST(AT91PS_TCB) 	0xFFF7C080) // (TCB2) Base Address
#define AT91C_BASE_PDC_MCI0  (AT91_CAST(AT91PS_PDC) 	0xFFF80100) // (PDC_MCI0) Base Address
#define AT91C_BASE_MCI0      (AT91_CAST(AT91PS_MCI) 	0xFFF80000) // (MCI0) Base Address
#define AT91C_BASE_PDC_MCI1  (AT91_CAST(AT91PS_PDC) 	0xFFF84100) // (PDC_MCI1) Base Address
#define AT91C_BASE_MCI1      (AT91_CAST(AT91PS_MCI) 	0xFFF84000) // (MCI1) Base Address
#define AT91C_BASE_TWI       (AT91_CAST(AT91PS_TWI) 	0xFFF88000) // (TWI) Base Address
#define AT91C_BASE_PDC_US0   (AT91_CAST(AT91PS_PDC) 	0xFFF8C100) // (PDC_US0) Base Address
#define AT91C_BASE_US0       (AT91_CAST(AT91PS_USART) 	0xFFF8C000) // (US0) Base Address
#define AT91C_BASE_PDC_US1   (AT91_CAST(AT91PS_PDC) 	0xFFF90100) // (PDC_US1) Base Address
#define AT91C_BASE_US1       (AT91_CAST(AT91PS_USART) 	0xFFF90000) // (US1) Base Address
#define AT91C_BASE_PDC_US2   (AT91_CAST(AT91PS_PDC) 	0xFFF94100) // (PDC_US2) Base Address
#define AT91C_BASE_US2       (AT91_CAST(AT91PS_USART) 	0xFFF94000) // (US2) Base Address
#define AT91C_BASE_PDC_SSC0  (AT91_CAST(AT91PS_PDC) 	0xFFF98100) // (PDC_SSC0) Base Address
#define AT91C_BASE_SSC0      (AT91_CAST(AT91PS_SSC) 	0xFFF98000) // (SSC0) Base Address
#define AT91C_BASE_PDC_SSC1  (AT91_CAST(AT91PS_PDC) 	0xFFF9C100) // (PDC_SSC1) Base Address
#define AT91C_BASE_SSC1      (AT91_CAST(AT91PS_SSC) 	0xFFF9C000) // (SSC1) Base Address
#define AT91C_BASE_PDC_AC97C (AT91_CAST(AT91PS_PDC) 	0xFFFA0100) // (PDC_AC97C) Base Address
#define AT91C_BASE_AC97C     (AT91_CAST(AT91PS_AC97C) 	0xFFFA0000) // (AC97C) Base Address
#define AT91C_BASE_PDC_SPI0  (AT91_CAST(AT91PS_PDC) 	0xFFFA4100) // (PDC_SPI0) Base Address
#define AT91C_BASE_SPI0      (AT91_CAST(AT91PS_SPI) 	0xFFFA4000) // (SPI0) Base Address
#define AT91C_BASE_PDC_SPI1  (AT91_CAST(AT91PS_PDC) 	0xFFFA8100) // (PDC_SPI1) Base Address
#define AT91C_BASE_SPI1      (AT91_CAST(AT91PS_SPI) 	0xFFFA8000) // (SPI1) Base Address
#define AT91C_BASE_CAN_MB0   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC200) // (CAN_MB0) Base Address
#define AT91C_BASE_CAN_MB1   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC220) // (CAN_MB1) Base Address
#define AT91C_BASE_CAN_MB2   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC240) // (CAN_MB2) Base Address
#define AT91C_BASE_CAN_MB3   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC260) // (CAN_MB3) Base Address
#define AT91C_BASE_CAN_MB4   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC280) // (CAN_MB4) Base Address
#define AT91C_BASE_CAN_MB5   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC2A0) // (CAN_MB5) Base Address
#define AT91C_BASE_CAN_MB6   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC2C0) // (CAN_MB6) Base Address
#define AT91C_BASE_CAN_MB7   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC2E0) // (CAN_MB7) Base Address
#define AT91C_BASE_CAN_MB8   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC300) // (CAN_MB8) Base Address
#define AT91C_BASE_CAN_MB9   (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC320) // (CAN_MB9) Base Address
#define AT91C_BASE_CAN_MB10  (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC340) // (CAN_MB10) Base Address
#define AT91C_BASE_CAN_MB11  (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC360) // (CAN_MB11) Base Address
#define AT91C_BASE_CAN_MB12  (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC380) // (CAN_MB12) Base Address
#define AT91C_BASE_CAN_MB13  (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC3A0) // (CAN_MB13) Base Address
#define AT91C_BASE_CAN_MB14  (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC3C0) // (CAN_MB14) Base Address
#define AT91C_BASE_CAN_MB15  (AT91_CAST(AT91PS_CAN_MB) 	0xFFFAC3E0) // (CAN_MB15) Base Address
#define AT91C_BASE_CAN       (AT91_CAST(AT91PS_CAN) 	0xFFFAC000) // (CAN) Base Address
#define AT91C_BASE_PWMC_CH0  (AT91_CAST(AT91PS_PWMC_CH) 	0xFFFB8200) // (PWMC_CH0) Base Address
#define AT91C_BASE_PWMC_CH1  (AT91_CAST(AT91PS_PWMC_CH) 	0xFFFB8220) // (PWMC_CH1) Base Address
#define AT91C_BASE_PWMC_CH2  (AT91_CAST(AT91PS_PWMC_CH) 	0xFFFB8240) // (PWMC_CH2) Base Address
#define AT91C_BASE_PWMC_CH3  (AT91_CAST(AT91PS_PWMC_CH) 	0xFFFB8260) // (PWMC_CH3) Base Address
#define AT91C_BASE_PWMC      (AT91_CAST(AT91PS_PWMC) 	0xFFFB8000) // (PWMC) Base Address
#define AT91C_BASE_MACB      (AT91_CAST(AT91PS_EMAC) 	0xFFFBC000) // (MACB) Base Address
#define AT91C_BASE_LCDC      (AT91_CAST(AT91PS_LCDC) 	0x00700000) // (LCDC) Base Address
#define AT91C_BASE_DMA       (AT91_CAST(AT91PS_DMA) 	0x00800000) // (DMA) Base Address
#define AT91C_BASE_UDP       (AT91_CAST(AT91PS_UDP) 	0xFFF78000) // (UDP) Base Address
#define AT91C_BASE_UHP       (AT91_CAST(AT91PS_UHP) 	0x00A00000) // (UHP) Base Address
#define AT91C_BASE_TBOX      (AT91_CAST(AT91PS_TBOX) 	0x70000000) // (TBOX) Base Address
#define AT91C_BASE_HECC0     (AT91_CAST(AT91PS_ECC) 	0xFFFFE000) // (HECC0) Base Address
#define AT91C_BASE_HECC1     (AT91_CAST(AT91PS_ECC) 	0xFFFFE600) // (HECC1) Base Address
#define AT91C_BASE_ISI       (AT91_CAST(AT91PS_ISI) 	0xFFFC4000) // (ISI) Base Address

// *****************************************************************************
//               MEMORY MAPPING DEFINITIONS FOR AT91SAM9263
// *****************************************************************************
// ITCM
#define AT91C_ITCM 	 (0x00100000) // Maximum ITCM Area base address
#define AT91C_ITCM_SIZE	 (0x00010000) // Maximum ITCM Area size in byte (64 Kbytes)
// DTCM
#define AT91C_DTCM 	 (0x00200000) // Maximum DTCM Area base address
#define AT91C_DTCM_SIZE	 (0x00010000) // Maximum DTCM Area size in byte (64 Kbytes)
// IRAM
#define AT91C_IRAM 	 (0x00300000) // Maximum Internal SRAM base address
#define AT91C_IRAM_SIZE	 (0x00014000) // Maximum Internal SRAM size in byte (80 Kbytes)
// IRAM_MIN
#define AT91C_IRAM_MIN	 (0x00300000) // Minimum Internal RAM base address
#define AT91C_IRAM_MIN_SIZE	 (0x00004000) // Minimum Internal RAM size in byte (16 Kbytes)
// IROM
#define AT91C_IROM 	 (0x00400000) // Internal ROM base address
#define AT91C_IROM_SIZE	 (0x00020000) // Internal ROM size in byte (128 Kbytes)
// IRAM2
#define AT91C_IRAM2	 (0x00500000) // IRAM2 base address
#define AT91C_IRAM2_SIZE	 (0x00004000) // IRAM2 size in byte (16 Kbytes)
// EBI0_CS0
#define AT91C_EBI0_CS0	 (0x10000000) // EBI0 Chip Select 0 base address
#define AT91C_EBI0_CS0_SIZE	 (0x10000000) // EBI0 Chip Select 0 size in byte (262144 Kbytes)
// EBI0_CS1
#define AT91C_EBI0_CS1	 (0x20000000) // EBI0 Chip Select 1 base address
#define AT91C_EBI0_CS1_SIZE	 (0x10000000) // EBI0 Chip Select 1 size in byte (262144 Kbytes)
// EBI0_SDRAM
#define AT91C_EBI0_SDRAM	 (0x20000000) // SDRAM on EBI0 Chip Select 1 base address
#define AT91C_EBI0_SDRAM_SIZE	 (0x10000000) // SDRAM on EBI0 Chip Select 1 size in byte (262144 Kbytes)
// EBI0_SDRAM_16BIT
#define AT91C_EBI0_SDRAM_16BIT	 (0x20000000) // SDRAM on EBI0 Chip Select 1 base address
#define AT91C_EBI0_SDRAM_16BIT_SIZE	 (0x02000000) // SDRAM on EBI0 Chip Select 1 size in byte (32768 Kbytes)
// EBI0_SDRAM_32BIT
#define AT91C_EBI0_SDRAM_32BIT	 (0x20000000) // SDRAM on EBI0 Chip Select 1 base address
#define AT91C_EBI0_SDRAM_32BIT_SIZE	 (0x04000000) // SDRAM on EBI0 Chip Select 1 size in byte (65536 Kbytes)
// EBI0_CS2
#define AT91C_EBI0_CS2	 (0x30000000) // EBI0 Chip Select 2 base address
#define AT91C_EBI0_CS2_SIZE	 (0x10000000) // EBI0 Chip Select 2 size in byte (262144 Kbytes)
// EBI0_CS3
#define AT91C_EBI0_CS3	 (0x40000000) // EBI0 Chip Select 3 base address
#define AT91C_EBI0_CS3_SIZE	 (0x10000000) // EBI0 Chip Select 3 size in byte (262144 Kbytes)
// EBI0_SM
#define AT91C_EBI0_SM	 (0x40000000) // SmartMedia on EBI0 Chip Select 3 base address
#define AT91C_EBI0_SM_SIZE	 (0x10000000) // SmartMedia on EBI0 Chip Select 3 size in byte (262144 Kbytes)
// EBI0_CS4
#define AT91C_EBI0_CS4	 (0x50000000) // EBI0 Chip Select 4 base address
#define AT91C_EBI0_CS4_SIZE	 (0x10000000) // EBI0 Chip Select 4 size in byte (262144 Kbytes)
// EBI0_CF0
#define AT91C_EBI0_CF0	 (0x50000000) // CompactFlash 0 on EBI0 Chip Select 4 base address
#define AT91C_EBI0_CF0_SIZE	 (0x10000000) // CompactFlash 0 on EBI0 Chip Select 4 size in byte (262144 Kbytes)
// EBI0_CS5
#define AT91C_EBI0_CS5	 (0x60000000) // EBI0 Chip Select 5 base address
#define AT91C_EBI0_CS5_SIZE	 (0x10000000) // EBI0 Chip Select 5 size in byte (262144 Kbytes)
// EBI0_CF1
#define AT91C_EBI0_CF1	 (0x60000000) // CompactFlash 1 on EBI0Chip Select 5 base address
#define AT91C_EBI0_CF1_SIZE	 (0x10000000) // CompactFlash 1 on EBI0Chip Select 5 size in byte (262144 Kbytes)
// EBI1_CS0
#define AT91C_EBI1_CS0	 (0x70000000) // EBI1 Chip Select 0 base address
#define AT91C_EBI1_CS0_SIZE	 (0x10000000) // EBI1 Chip Select 0 size in byte (262144 Kbytes)
// EBI1_CS1
#define AT91C_EBI1_CS1	 (0x80000000) // EBI1 Chip Select 1 base address
#define AT91C_EBI1_CS1_SIZE	 (0x10000000) // EBI1 Chip Select 1 size in byte (262144 Kbytes)
// EBI1_SDRAM_16BIT
#define AT91C_EBI1_SDRAM_16BIT	 (0x80000000) // SDRAM on EBI1 Chip Select 1 base address
#define AT91C_EBI1_SDRAM_16BIT_SIZE	 (0x02000000) // SDRAM on EBI1 Chip Select 1 size in byte (32768 Kbytes)
// EBI1_SDRAM_32BIT
#define AT91C_EBI1_SDRAM_32BIT	 (0x80000000) // SDRAM on EBI1 Chip Select 1 base address
#define AT91C_EBI1_SDRAM_32BIT_SIZE	 (0x04000000) // SDRAM on EBI1 Chip Select 1 size in byte (65536 Kbytes)
// EBI1_CS2
#define AT91C_EBI1_CS2	 (0x90000000) // EBI1 Chip Select 2 base address
#define AT91C_EBI1_CS2_SIZE	 (0x10000000) // EBI1 Chip Select 2 size in byte (262144 Kbytes)
// EBI1_SM
#define AT91C_EBI1_SM	 (0x90000000) // SmartMedia on EBI1 Chip Select 2 base address
#define AT91C_EBI1_SM_SIZE	 (0x10000000) // SmartMedia on EBI1 Chip Select 2 size in byte (262144 Kbytes)

#endif
