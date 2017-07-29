/*
 * arch/arm/mach-ksz8692/include/mach/entry-macro.S
 *
 * Low-level IRQ helper macros for KS8692 platforms
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
		ldr	\base, =VIO(KS8692_INT_MASK1_STATUS)
		ldr	\irqstat, [\base]	@ get masked status
		mov	\irqnr, #0
1001:		tst	\irqstat, #1
		bne	1003f
		add	\irqnr, \irqnr, #1
		mov	\irqstat, \irqstat, lsr #1
		cmp	\irqnr, #32
		bcc	1001b

		ldr	\base, =VIO(KS8692_INT_MASK2_STATUS)
		ldr	\irqstat, [\base]	@ get masked status
1002:		tst	\irqstat, #1
		bne	1003f
		add	\irqnr, \irqnr, #1
		mov	\irqstat, \irqstat, lsr #1
		cmp	\irqnr, #64
		bcc	1002b

1003:		
		.endm

