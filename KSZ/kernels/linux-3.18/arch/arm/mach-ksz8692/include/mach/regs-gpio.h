/*
 * arch/arm/mach-ksz8692/include/mach/regs-gpio.h
 *
 * Copyright (C) 2007 Andrew Victor
 *
 * KSZ8692 - GPIO control registers and bit definitions.
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef KSZ8692_GPIO_H
#define KSZ8692_GPIO_H


/* I/O Port Mode Register */
#define KS_IOPM			(KS8692_GPIO_MODE + 0x00)
/* I/O Port Control Register */
#define KS_IOPC			(KS8692_GPIO_MODE + 0x04)
/* I/O Port Data Register */
#define KS_IOPD			(KS8692_GPIO_MODE + 0x08)

#define KS_INT_EXT_INT0		KS8692_INT_EXT_INT0
#define KS_INT_EXT_INT1		KS8692_INT_EXT_INT1
#define KS_INT_EXT_INT2		KS8692_INT_EXT_INT2
#define KS_INT_EXT_INT3		KS8692_INT_EXT_INT3


/* Port Mode Register */
/* Mode for GPIO Pin x */
#define IOPM(x)			(1 << (x))

/* Port Control Register */
/* GPIO Pin for Timer1 Enable */
#define IOPC_IOTIM1EN		(1 << 17)
/* GPIO Pin for Timer0 Enable */
#define IOPC_IOTIM0EN		(1 << 16)
/* GPIO Pin for External/Soft Interrupt 3 Enable */
#define IOPC_IOEINT3EN		(1 << 15)
/* GPIO Pin for External/Soft Interrupt 3 Trigger Mode */
#define IOPC_IOEINT3TM		(7 << 12)
#define IOPC_IOEINT3_MODE(x)	((x) << 12)
/* GPIO Pin for External/Soft Interrupt 2 Enable */
#define IOPC_IOEINT2EN		(1 << 11)
/* GPIO Pin for External/Soft Interrupt 2 Trigger Mode */
#define IOPC_IOEINT2TM		(7 << 8)
#define IOPC_IOEINT2_MODE(x)	((x) << 8)
/* GPIO Pin for External/Soft Interrupt 1 Enable */
#define IOPC_IOEINT1EN		(1 << 7)
/* GPIO Pin for External/Soft Interrupt 1 Trigger Mode */
#define IOPC_IOEINT1TM		(7 << 4)
#define IOPC_IOEINT1_MODE(x)	((x) << 4)
/* GPIO Pin for External/Soft Interrupt 0 Enable */
#define IOPC_IOEINT0EN		(1 << 3)
/* GPIO Pin for External/Soft Interrupt 0 Trigger Mode */
#define IOPC_IOEINT0TM		(7 << 0)
#define IOPC_IOEINT0_MODE(x)	((x) << 0)

 /* Trigger Modes */
/* Level Detection (Active Low) */
#define IOPC_TM_LOW		(0)
/* Level Detection (Active High) */
#define IOPC_TM_HIGH		(1)
/* Rising Edge Detection */
#define IOPC_TM_RISING		(2)
/* Falling Edge Detection */
#define IOPC_TM_FALLING		(4)
/* Both Edge Detection */
#define IOPC_TM_EDGE		(6)

/* Port Data Register */
/* Signal Level of GPIO Pin x */
#define IOPD(x)			(1 << (x))

#endif
