/*
 * arch/arm/mach-ksz8695/include/mach/entry-macro.S
 *
 * Low-level IRQ helper macros for KS8695 platforms
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/version.h>
#include <mach/hardware.h>

 		.macro	get_irqnr_preamble, base, tmp
		.endm

		.macro	get_irqnr_and_base, irqnr, irqstat, base, tmp
/* FIXME: should not be using soo many LDRs here */
		ldr	\irqnr, =IO_ADDRESS(KS8695_IO_BASE)+KS8695_INT_MASK_STATUS
		ldr	\irqstat, [\irqnr]	@ get masked status
		mov	\irqnr, #0
1001:		tst	\irqstat, #1
		bne	1002f
		add	\irqnr, \irqnr, #1
		mov	\irqstat, \irqstat, lsr #1
		cmp	\irqnr, #32
		bcc	1001b
1002:		/* EQ will be set if no irqs pending */
		.endm

