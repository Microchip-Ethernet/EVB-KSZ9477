/**
 * \file
 *
 * \brief BPM driver
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include "compiler.h"
#include "bpm.h"
#include "sleepmgr.h"
#include "gpio.h"

void bpm_psave_mode (volatile Bpm* bpm, unsigned int sleep)
{
	unsigned long pmcon;

	// Read
	pmcon = bpm->PMCON;
	pmcon &= ~BPM_PMCON_BKUP;
	pmcon &= ~BPM_PMCON_RET;
	pmcon &= ~BPM_PMCON_SLEEP_Msk;

	// UNLOCK
	bpm->UNLOCK = 0xAA000000 | BPM_UNLOCK_ADDR((uint32_t)& bpm->PMCON - (uint32_t)bpm);

	if (sleep == SLEEPMGR_SLEEP_0) {
		pmcon |= BPM_PMCON_SLEEP(0);
		bpm->PMCON = pmcon;
		SCB->SCR = SCB->SCR & ~SCB_SCR_SLEEPDEEP_Msk;
	} else if (sleep == SLEEPMGR_SLEEP_1) {
		pmcon |= BPM_PMCON_SLEEP(1);
		bpm->PMCON = pmcon;
		SCB->SCR = SCB->SCR & ~SCB_SCR_SLEEPDEEP_Msk;
	} else if (sleep == SLEEPMGR_SLEEP_2) {
		pmcon |= BPM_PMCON_SLEEP(2);
		bpm->PMCON = pmcon;
		SCB->SCR = SCB->SCR & ~SCB_SCR_SLEEPDEEP_Msk;
	} else if (sleep == SLEEPMGR_SLEEP_3) {
		pmcon |= BPM_PMCON_SLEEP(3);
		bpm->PMCON = pmcon;
		SCB->SCR = SCB->SCR & ~SCB_SCR_SLEEPDEEP_Msk;
	} else if (sleep == SLEEPMGR_WAIT) {
		bpm->PMCON = pmcon;
		SCB->SCR = SCB_SCR_SLEEPDEEP_Msk;
	} else if (sleep == SLEEPMGR_RET) {
		pmcon |= BPM_PMCON_RET;
		bpm->PMCON = pmcon;
		SCB->SCR = SCB_SCR_SLEEPDEEP_Msk;
	} else /* if (sleep == SLEEPMGR_BACKUP) */ {
		pmcon |= BPM_PMCON_BKUP;
		bpm->PMCON = pmcon;
		SCB->SCR = SCB_SCR_SLEEPDEEP_Msk;
	}

	while(!(BSCIF->PCLKSR & BSCIF_PCLKSR_VREGOK));// Wait until vreg is ok	
		
	asm volatile ("wfi");

	// The interrupts wake-up from the previous wfi, but there are still
	// masked since we are in the critical section thanks to the previous
	// set_pri_mask(1). Thus, we need to leave the critical section.
	// Please note that we should probably use something like
	// cpu_leave_critical(), using set_pri_mask(0)
	cpu_irq_enable();
}

void bpm_configure_power_scaling(volatile Bpm* bpm, uint32_t ps_value, uint32_t pscm) 
{
	uint32_t bpm_value = 0;
	// Read last PM_CON value
	bpm_value = bpm->PMCON;
	// Clear last PS Value
	bpm_value &= ~BPM_PMCON_PS(3);
	// Write new PS Value
	bpm_value |= BPM_PMCON_PS(ps_value);
	// Clear last PSM Value
	bpm_value &= ~BPM_PMCON_PSCM;
	// Write new PS Value
	bpm_value |= (pscm ? BPM_PMCON_PSCM : 0 );
	// Power Scaling Change Request
	bpm_value |= BPM_PMCON_PSCREQ;
	// UNLOCK
	bpm->UNLOCK = 0xAA000000 | BPM_UNLOCK_ADDR((uint32_t)& bpm->PMCON - (uint32_t)bpm);
	// Write back PM_CON value
	bpm->PMCON = bpm_value;
}

bool bpm_get_psok_status(volatile Bpm* bpm) 
{
	// Return PS OK value
	return ( bpm->SR & BPM_SR_PSOK );
}

void bpm_configure_bkup_pin(volatile Bpm* bpm, uint32_t bkup_pin)
{
	uint32_t bpm_value = 0;
	// Read last BKUPPMUX value
	bpm_value = BPM->BKUPPMUX;
	// Write new PS Value
	bpm_value |= (1<<bkup_pin);
	// UNLOCK
	bpm->UNLOCK = 0xAA000000 | BPM_UNLOCK_ADDR((uint32_t)& bpm->BKUPPMUX - (uint32_t)bpm);
	// Write back BKUPPMUX value
	bpm->BKUPPMUX = bpm_value;
}

void bpm_enable_wakeup_source(volatile Bpm* bpm, uint32_t source)
{
	uint32_t bpm_value = 0;
	// Read last BKUPWEN value
	bpm_value = bpm->BKUPWEN;
	// Write new PS Value
	bpm_value |= (1<<source);
	// UNLOCK
	bpm->UNLOCK = 0xAA000000 | BPM_UNLOCK_ADDR((uint32_t)& bpm->BKUPWEN - (uint32_t)bpm);
	// Write back BKUPWEN value
	bpm->BKUPWEN = bpm_value;
}

void bpm_set_clk32_source(volatile Bpm* bpm, uint8_t source)
{
	uint32_t bpm_value = 0;	
	// Read PMCON first
	bpm_value = BPM->PMCON;
	if(source == BPM_CLK32_SOURCE_OSC32K) {
		// Clear CK32S for OSC32K
		bpm_value &=~ BPM_PMCON_CK32S;
	}
	else {
		// Set CK32S for RC32K
		bpm_value |= BPM_PMCON_CK32S;
	}
	// Unlock PMCON register
	BPM->UNLOCK = BPM_UNLOCK_KEY(0xAAUL)
			| BPM_UNLOCK_ADDR((uint32_t)&BPM->PMCON - (uint32_t)BPM);
	BPM->PMCON = bpm_value;
}