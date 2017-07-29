/**
 * \file
 *
 * \brief Chip-specific oscillator management functions
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 *    AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
#include <osc.h>

#ifdef BOARD_OSC0_HZ
void osc_priv_enable_osc0(void)
{
	irqflags_t flags;

	flags = cpu_irq_save();
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->OSCCTRL0 - (uint32_t)SCIF);
	SCIF->OSCCTRL0 =
			(SCIF_OSCCTRL0_STARTUP(OSC0_STARTUP_VALUE))
# if BOARD_OSC0_IS_XTAL == true
			| (SCIF_OSCCTRL0_GAIN(OSC0_GAIN_VALUE))
#endif
			| OSC0_MODE_VALUE
			| SCIF_OSCCTRL0_OSCEN;
	cpu_irq_restore(flags);
}

void osc_priv_disable_osc0(void)
{
	irqflags_t flags;

	flags = cpu_irq_save();
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->OSCCTRL0 - (uint32_t)SCIF);
	SCIF->OSCCTRL0 = 0;
	cpu_irq_restore(flags);
}
#endif /* BOARD_OSC0_HZ */

#ifdef BOARD_OSC32_HZ
void osc_priv_enable_osc32(void)
{
	irqflags_t flags;

	flags = cpu_irq_save();
	BSCIF->UNLOCK = BSCIF_UNLOCK_KEY(0xAAUL)
		| BSCIF_UNLOCK_ADDR((uint32_t)&BSCIF->OSCCTRL32 - (uint32_t)BSCIF);
	BSCIF->OSCCTRL32 =
			OSC32_STARTUP_VALUE
			| BSCIF_OSCCTRL32_SELCURR(BOARD_OSC32_SELCURR)
			| OSC32_MODE_VALUE
			| BSCIF_OSCCTRL32_EN32K
			| BSCIF_OSCCTRL32_OSC32EN;
	cpu_irq_restore(flags);
}

void osc_priv_disable_osc32(void)
{
	irqflags_t flags;

	flags = cpu_irq_save();
	BSCIF->UNLOCK = BSCIF_UNLOCK_KEY(0xAAUL)
		| BSCIF_UNLOCK_ADDR((uint32_t)&BSCIF->OSCCTRL32 - (uint32_t)BSCIF);
	BSCIF->OSCCTRL32 = 0;
	cpu_irq_restore(flags);
}
#endif /* BOARD_OSC32_HZ */

void osc_priv_enable_rc32k(void)
{
	irqflags_t flags;
	uint32_t tempo;
	flags = cpu_irq_save();
	tempo = BSCIF->RC32KCR;
	BSCIF->UNLOCK = BSCIF_UNLOCK_KEY(0xAAUL)
		| BSCIF_UNLOCK_ADDR((uint32_t)&BSCIF->RC32KCR - (uint32_t)BSCIF);
	BSCIF->RC32KCR = tempo|BSCIF_RC32KCR_EN;
	cpu_irq_restore(flags);
}

void osc_priv_disable_rc32k(void)
{
	irqflags_t flags;
	uint32_t tempo;
	flags = cpu_irq_save();
	tempo = BSCIF->RC32KCR;
	tempo &= ~BSCIF_RC32KCR_EN;
	BSCIF->UNLOCK = BSCIF_UNLOCK_KEY(0xAAUL)
		| BSCIF_UNLOCK_ADDR((uint32_t)&BSCIF->RC32KCR - (uint32_t)BSCIF);
	BSCIF->RC32KCR = tempo;
	cpu_irq_restore(flags);
}

void osc_priv_enable_rc80m(void)
{
	irqflags_t flags;
	uint32_t tempo;
	flags = cpu_irq_save();
	tempo = SCIF->RC80MCR;
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->RC80MCR - (uint32_t)SCIF);
	SCIF->RC80MCR = tempo|SCIF_RC80MCR_EN;
	cpu_irq_restore(flags);
}

void osc_priv_disable_rc80m(void)
{
	irqflags_t flags;
	uint32_t tempo;
	flags = cpu_irq_save();
	tempo = SCIF->RC80MCR;
	tempo &= ~SCIF_RC80MCR_EN ;
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->RC80MCR - (uint32_t)SCIF);
	SCIF->RC80MCR = tempo;
	cpu_irq_restore(flags);
}

void osc_priv_enable_rc1m(void)
{
	irqflags_t flags;
	uint32_t tempo;
	flags = cpu_irq_save();
	tempo = BSCIF->RC1MCR;
	BSCIF->UNLOCK = BSCIF_UNLOCK_KEY(0xAAUL)
		| BSCIF_UNLOCK_ADDR((uint32_t)&BSCIF->RC1MCR - (uint32_t)BSCIF);
	BSCIF->RC1MCR = tempo | BSCIF_RC1MCR_CLKOE;
	cpu_irq_restore(flags);
}

void osc_priv_disable_rc1m(void)
{
	irqflags_t flags;
	uint32_t tempo;
	flags = cpu_irq_save();
	tempo = BSCIF->RC1MCR;
	tempo &= ~BSCIF_RC1MCR_CLKOE;
	BSCIF->UNLOCK = BSCIF_UNLOCK_KEY(0xAAUL)
		| BSCIF_UNLOCK_ADDR((uint32_t)&BSCIF->RC1MCR - (uint32_t)BSCIF);
	BSCIF->RC1MCR = tempo;
	cpu_irq_restore(flags);
}

void osc_priv_enable_rcfast(void)
{
	irqflags_t flags;
	uint32_t tempo;
	flags = cpu_irq_save();
	// Let FCD and calibration value by default
	tempo = SCIF->RCFASTCFG;
	// Clear previous FRANGE value
	tempo &= ~SCIF_RCFASTCFG_FRANGE(3);
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->RCFASTCFG - (uint32_t)SCIF);
	SCIF->RCFASTCFG = tempo|SCIF_RCFASTCFG_EN|SCIF_RCFASTCFG_FRANGE(CONFIG_RCFAST_FRANGE);
	cpu_irq_restore(flags);
}

void osc_priv_disable_rcfast(void)
{
	irqflags_t flags;
	uint32_t tempo;
	flags = cpu_irq_save();
	// Let FCD and calibration value by default
	tempo = SCIF->RCFASTCFG;
	// Clear previous FRANGE value
	tempo &= ~SCIF_RCFASTCFG_EN;
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->RCFASTCFG - (uint32_t)SCIF);
	SCIF->RCFASTCFG = tempo;
	cpu_irq_restore(flags);
}
