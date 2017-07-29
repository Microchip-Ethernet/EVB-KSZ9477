/**
 * \file
 *
 * \brief SAM4L-EK Board header file.
 *
 * This file contains definitions and services related to the features of the
 * SAM4L-EK Board.
 *
 * To use this board define BOARD=SAM4L_EK.
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
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
#ifndef _SAM4L_EK_H_
#define _SAM4L_EK_H_

#include "compiler.h"

/**
 * \defgroup sam4l_ek_group SAM4L-EK Board
 * @{
 */

/**
 * \defgroup sam4l_ek_feature_group Feature definitions
 * @{
 */

//! \name Miscellaneous data
//@{
//@}

//! Osc frequency (Hz.) and startup time (RCOsc periods).
#define FOSC0                       (12000000)

//! Osc32 frequency (Hz.) and startup time (RCOsc periods).
#define FOSC32                      (32768)

/**
 * \name Board oscillator configuration
 *
 */
//@{
#define BOARD_OSC32_IS_XTAL         true
#define BOARD_OSC32_HZ              FOSC32
#define BOARD_OSC32_STARTUP_US      (71000)
#define BOARD_OSC32_SELCURR         10
//LLG #define BOARD_OSC0_IS_XTAL          true
#define BOARD_OSC0_IS_XTAL          false
#define BOARD_OSC0_HZ               FOSC0
#define BOARD_OSC0_STARTUP_US       (1100)
//@}

/*! \name Number of LEDs.
 */
//! @{
#define LED_COUNT   1
//! @}

/**
 * \name LEDs
 *
 * LED0 is a single yellow LED that is active low.
 */
//@{
#define LED0                            PC10
#define LED0_GPIO                       PIN_PC10
#define LED0_GPIO_MASK                  GPIO_PC10
//@}

/**
 * \name LCD Backlight
 */
//@{
#if defined(SAM4L_EK_REV1)
#define LCD_BL                          PA02
#define LCD_BL_GPIO                     PIN_PA02
#define LCD_BL_GPIO_MASK                GPIO_PA02
#else
#define LCD_BL                          PC14
#define LCD_BL_GPIO                     PIN_PC14
#define LCD_BL_GPIO_MASK                GPIO_PC14
#endif
//@}

/*! \name GPIO Connections of Push Buttons
 */
//! @{
#define GPIO_PUSH_BUTTON_0              PIN_PC03
#define GPIO_PUSH_BUTTON_0_MASK         GPIO_PC03
//! @}

/*! \name Push Button Connection on External Interrupt line
 */
//! @{
#define GPIO_PUSH_BUTTON_EIC_PIN        PIN_PC03B_EIC_EXTINT5
#define GPIO_PUSH_BUTTON_EIC_PIN_MASK   GPIO_PC03B_EIC_EXTINT5
#define GPIO_PUSH_BUTTON_EIC_PIN_MUX    MUX_PC03B_EIC_EXTINT5
#define GPIO_PUSH_BUTTON_EIC_LINE       5
//! @}


/*! \name GPIO Connections of Touch sensors
 */
//! @{
#define GPIO_QTOUCH_SLIDER_0            PIN_PB02
#define GPIO_QTOUCH_SLIDER_0_MASK       GPIO_PB02
#define GPIO_QTOUCH_SLIDER_0_MUX        MUX_PB02G_CATB_SENSE23
#define GPIO_QTOUCH_SLIDER_1            PIN_PA04
#define GPIO_QTOUCH_SLIDER_1_MASK       GPIO_PA04
#define GPIO_QTOUCH_SLIDER_1_MUX       	MUX_PA04G_CATB_SENSE0
#define GPIO_QTOUCH_SLIDER_2            PIN_PA05
#define GPIO_QTOUCH_SLIDER_2_MASK       GPIO_PA05
#define GPIO_QTOUCH_SLIDER_2_MUX        MUX_PA05G_CATB_SENSE1
#define GPIO_QTOUCH_DISCHARGE           PIN_PB03
#define GPIO_QTOUCH_DISCHARGE_MASK      GPIO_PB03
#define GPIO_QTOUCH_DISCHARGE_MUX       MUX_PB03G_CATB_DIS
#define GPIO_QTOUCH_BUTTON              PIN_PB04
#define GPIO_QTOUCH_BUTTON_MASK         GPIO_PB04
#define GPIO_QTOUCH_BUTTON_MUX          MUX_PB04G_CATB_SENSE24
//! @}

/*! \name Touch sensors pin assignements
 */
//! @{
#define QTOUCH_PINSEL_SLIDER_0          23
#define QTOUCH_PINSEL_SLIDER_1          0
#define QTOUCH_PINSEL_SLIDER_2          1
#define QTOUCH_PINSEL_BUTTON            24
//! @}

/*! \name GPIO Connections of SAM4L4C VBUS monitoring
 */
//! @{
#if defined(SAM4L_EK_REV1)
#   define GPIO_VBUS_INPUT                 PIN_PC14
#   define GPIO_VBUS_INPUT_MASK            GPIO_PC14
#else
#   define GPIO_VBUS_INPUT                 PIN_PA06
#   define GPIO_VBUS_INPUT_MASK            GPIO_PA06
#endif
//! @}

/*! \name GPIO Connections of SAM4L4C VBUS Power Control
 */
//! @{
#define VBOF_GPIO                       PIN_PC08
#define VBOF_GPIO_MASK                  GPIO_PC08
//! @}

//! \name USART connections to GPIO for Virtual Com Port
// @{
#define COM_PORT_USART                 USART2
#define COM_PORT_USART_ID              ID_USART2
#define COM_PORT_RX_PIN                PIN_PC11B_USART2_RXD
#define COM_PORT_RX_GPIO               GPIO_PC11B_USART2_RXD
#define COM_PORT_RX_MUX                MUX_PC11B_USART2_RXD
#define COM_PORT_TX_PIN                PIN_PC12B_USART2_TXD
#define COM_PORT_TX_GPIO               GPIO_PC12B_USART2_TXD
#define COM_PORT_TX_MUX                MUX_PC12B_USART2_TXD
// @}

//! \name USART connections to the Board Monitor
// @{
#define BM_USART_USART                 USART0
#define BM_USART_USART_ID              ID_USART0
#define BM_USART_RX_PIN                PIN_PC02C_USART0_RXD
#define BM_USART_RX_GPIO               GPIO_PC02C_USART0_RXD
#define BM_USART_RX_MUX                MUX_PC02C_USART0_RXD
#define BM_USART_TX_PIN                PIN_PA07B_USART0_TXD
#define BM_USART_TX_GPIO               GPIO_PA07B_USART0_TXD
#define BM_USART_TX_MUX                MUX_PA07B_USART0_TXD
// @}

/**
 * @}
 */

#endif /* _SAM4L_EK_H_ */
