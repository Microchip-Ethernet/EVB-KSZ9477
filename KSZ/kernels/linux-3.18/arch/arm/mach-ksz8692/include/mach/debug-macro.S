/* arch/arm/mach-ksz8692/include/mach/debug-macro.S
 *
 * Debugging macro include header
 *
 *  Copyright (C) 2006-2011 Micrel, Inc.
 *  Copyright (C) 1994-1999 Russell King
 *  Moved from linux/arch/arm/kernel/debug.S by Ben Dooks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
*/

#include <linux/version.h>
#include <mach/platform.h>

		.macro	addruart,rx
		mrc	p15, 0, \rx, c1, c0
		tst	\rx, #1			@ MMU enabled?
		ldreq	\rx, =KS_IO_BASE	@ physical base address
		ldrne	\rx, =KS_VIO_BASE	@ virtual base
		add	\rx, \rx, #KS_UART_RX_BUFFER
		.endm

		.macro	senduart,rd,rx
		strb	\rd, [\rx, #4]
		.endm

		.macro	waituart,rd,rx
1001:		ldr	\rd, [\rx, #0x14]	@ UART LINE STATUS
		tst	\rd, #1 << 5		@ UART RUTHRE - 0 when full
		beq	1001b
		.endm

		.macro	busyuart,rd,rx
1001:		ldr	\rd, [\rx, #0x14]	@ UART LINE STATUS
		tst	\rd, #1 << 6		@ UART URTE - 0 when busy
		beq	1001b
		.endm
