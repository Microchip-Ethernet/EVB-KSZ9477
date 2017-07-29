/**
 * \file
 *
 * \brief Main functions
 *
 * Copyright (c) 2009-2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
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

#ifndef _MAIN_H_
#define _MAIN_H_

#include "usb_protocol_cdc.h"

//Application start address (beggining of the intvect)
#define APP_START_ADDRESS 				0x4000
#define APP_START_PAGE	 				(APP_START_ADDRESS/FLASH_PAGE_SIZE)


//Offset in the user page to fetch the gpio to check for triggering boot entry
//The value at this address is the gpio bit number to check and active state
//The booloader doesn't PU or PD this line, so it has be stable when bootloader starts
#define USERPAGE_CONFWORD_OFFSET 		0x10

//Write this value at USERPAGE_CONFWORD_OFFSET to force monitor/boot entry
#define CONFWORD_FORCE_MONITOR_VALUE	0x4D4153
#define CONFWORD_FORCE_MONITOR_MASK		0xFFFFFF

//Bit in the booloader config word for vddin<1.8 -> PS1
#define CONFWORD_LOW_VDDIN_BIT_OFFSET	24


/*! \brief Init freqm using RCSYS as reference clock
 *
 */
void init_freqm(void);

/*! \brief Measure OSC0 for 1ms (115 cycles of RCSYS)
 *
 * \return Frequency is outputted in kHz
 */
uint32_t freqm_measure(void);

void check_start_application(void);
void erase_secured_device(void);

/*! \brief simple abs function
 * \param input value.\n
 * \return absolute part of value
 */
uint32_t i32abs(int32_t value);

//Setup necessary clocks for the bootloader
//Allow USB if one of the supported input frequency is available
void usb_clock_setup(void);


/*! \brief Wait one millisecond
 *
 * 
 */
void wait_1_ms(void);

/*! \brief Opens the communication port
 * This is called by CDC interface when USB Host enable it.
 *
 * \retval true if cdc startup is successfully done
 */
bool main_cdc_enable(uint8_t port);

/*! \brief Closes the communication port
 * This is called by CDC interface when USB Host disable it.
 */
void main_cdc_disable(uint8_t port);

/*! \brief Save new DTR state to change led behavior.
 * The DTR notify that the terminal have open or close the communication port.
 */
void main_cdc_set_dtr(uint8_t port, bool b_enable);

/*! \brief Called by CDC interface
 * Callback running when CDC device have received data
 */

void main_cdc_rx_notify(uint8_t port);

/*! \brief Configures communication line
 *
 * \param cfg      line configuration
 */
void main_cdc_set_coding(uint8_t port, usb_cdc_line_coding_t * cfg);

#endif // _MAIN_H_
