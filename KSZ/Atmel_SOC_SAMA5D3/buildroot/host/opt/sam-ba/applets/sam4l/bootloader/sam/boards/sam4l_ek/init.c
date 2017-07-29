/**
 * \file
 *
 * \brief SAM4L-EK Board init.
 *
 * This file contains board initialization function.
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
#include "sam4l_ek.h"
#include "conf_board.h"
#include "gpio.h"
#include "board.h"
/**
 * \addtogroup  sam4l_ek_group
 * @{
 */
void board_init(void)
{

	/* Configure the pins connected to LEDs as output and set their
	 * default initial state to high (LEDs off).
	 */
	gpio_configure_pin(LED0_GPIO, LED0_GPIO_MASK, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);

	// Set push button as input
	gpio_configure_pin (GPIO_PUSH_BUTTON_0, GPIO_PUSH_BUTTON_0_MASK, (GPIO_DIR_INPUT | GPIO_PULL_UP));

#if (defined CONF_BOARD_BL)
	// Configure LCD backlight
	gpio_configure_pin(LCD_BL_GPIO, LCD_BL_GPIO_MASK, GPIO_DIR_OUTPUT);
#endif

#if (defined CONF_BOARD_USB_PORT)
	gpio_enable_module_pin(PIN_PA25A_USBC_DM, GPIO_PA25A_USBC_DM, MUX_PA25A_USBC_DM);
	gpio_enable_module_pin(PIN_PA26A_USBC_DP, GPIO_PA26A_USBC_DP, MUX_PA26A_USBC_DP);
	gpio_configure_pin (GPIO_VBUS_INPUT, GPIO_VBUS_INPUT_MASK, GPIO_DIR_INPUT);
#endif

#if defined (CONF_BOARD_COM_PORT)
	gpio_enable_module_pin(COM_PORT_RX_PIN, COM_PORT_RX_GPIO, COM_PORT_RX_MUX);
	gpio_enable_module_pin(COM_PORT_TX_PIN, COM_PORT_TX_GPIO, COM_PORT_TX_MUX);
#endif

#if defined (CONF_BOARD_BM_USART)
	gpio_enable_module_pin(BM_USART_RX_PIN, BM_USART_RX_GPIO, BM_USART_RX_MUX);
	gpio_enable_module_pin(BM_USART_TX_PIN, BM_USART_TX_GPIO, BM_USART_TX_MUX);
#endif

}
/**
 * @}
 */
