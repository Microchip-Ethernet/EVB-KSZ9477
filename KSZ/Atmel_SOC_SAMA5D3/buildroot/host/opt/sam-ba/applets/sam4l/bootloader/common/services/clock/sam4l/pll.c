/**
 * \file
 *
 * \brief Chip-specific PLL implementation
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

#include <compiler.h>
#include <pll.h>

void pll_config_write(const struct pll_config *cfg, unsigned int pll_id)
{
	irqflags_t flags;

	Assert(pll_id < NR_PLLS);

	flags = cpu_irq_save();
	
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->Pll[0].PLL + (4 * pll_id) - (uint32_t)SCIF);
	SCIF->Pll[0].PLL  = cfg->ctrl;
	cpu_irq_restore(flags);
}

void pll_enable(const struct pll_config *cfg, unsigned int pll_id)
{
	irqflags_t flags;

	Assert(pll_id < NR_PLLS);

	flags = cpu_irq_save();
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->Pll[0].PLL + (4 * pll_id) - (uint32_t)SCIF);
	SCIF->Pll[0].PLL  = cfg->ctrl | SCIF_PLL_PLLEN;
	cpu_irq_restore(flags);
}

void pll_disable(unsigned int pll_id)
{
	irqflags_t flags;

	Assert(pll_id < NR_PLLS);

	flags = cpu_irq_save();
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->Pll[0].PLL + (4 * pll_id) - (uint32_t)SCIF);
	SCIF->Pll[0].PLL  = 0;
	cpu_irq_restore(flags);
}
