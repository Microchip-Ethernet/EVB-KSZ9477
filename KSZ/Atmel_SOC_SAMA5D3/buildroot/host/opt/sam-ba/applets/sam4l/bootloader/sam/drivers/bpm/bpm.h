/**
 * \file
 *
 * \brief BPM driver.
 *
 * Copyright (C) 2012 Atmel Corporation. All rights reserved.
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

#ifndef _BPM_H_
#define _BPM_H_

/**
 * \defgroup group_sam_drivers_bpm BPM - Backup Power Manager
 *
 * Driver for the BPM (Backup Power Manager).
 * Provides functions for configuring the Backup Power Event.
 *
 * \{
 */

#include "compiler.h"

#define BPM_UNLOCK(reg) do {AVR32_BPM.unlock = (0xAA << AVR32_BPM_UNLOCK_KEY) | ((reg) << AVR32_BPM_UNLOCK_ADDR); } while(0)

// define EIC pads dedicated to backup mode
#define BKUP_PAD_EIC0                  PAD_PB01
#define BKUP_PAD_EIC1                  PAD_PA06
#define BKUP_PAD_EIC2                  PAD_PA04
#define BKUP_PAD_EIC3                  PAD_PA05
#define BKUP_PAD_EIC4                  PAD_PA07
#define BKUP_PAD_EIC5                  PAD_PC03
#define BKUP_PAD_EIC6                  PAD_PC04
#define BKUP_PAD_EIC7                  PAD_PC05
#define BKUP_PAD_EIC8                  PAD_PC06

#define BKUP_PIN_EIC0                  0
#define BKUP_PIN_EIC1                  1
#define BKUP_PIN_EIC2                  2
#define BKUP_PIN_EIC3                  3
#define BKUP_PIN_EIC4                  4
#define BKUP_PIN_EIC5                  5
#define BKUP_PIN_EIC6                  6
#define BKUP_PIN_EIC7                  7
#define BKUP_PIN_EIC8                  8

#define POWER_SCALING_IS_NOT_IMMEDIATE 0
#define POWER_SCALING_IS_IMMEDIATE     1

#define PS0                            0
#define PS1                            1
#define PS2                            2
#define PS3                            3

//! \name CLK32 32Khz-1Khz Clock Source Selection
//@{
//! OSC32K : Low frequency crystal oscillator
#define BPM_CLK32_SOURCE_OSC32K  0
//! RC32K : Internal Low frequency RC oscillator
#define BPM_CLK32_SOURCE_RC32K   1
//@}

void         bpm_psave_mode (volatile Bpm* bpm, unsigned int sleep);
void         bpm_configure_power_scaling(volatile Bpm* bpm, uint32_t ps_value, uint32_t pscm);
bool         bpm_get_psok_status(volatile Bpm* bpm);
void         bpm_configure_bkup_pin(volatile Bpm* bpm, uint32_t bkup_pin);
void         bpm_enable_wakeup_source(volatile Bpm* bpm, uint32_t source);
void         bpm_set_clk32_source(volatile Bpm* bpm, uint8_t source);
#endif /* __BPM_H__ */
