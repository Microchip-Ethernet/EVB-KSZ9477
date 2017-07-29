/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/**
 * \page sam4c_ek_board_desc SAM4C-EK - Board Description
 *
 * \section Purpose
 *
 * This file is dedicated to describe the SAM4C-EK board.
 *
 * \section Contents
 *
 *  - For SAM4C-EK information, see \subpage sam4c_ek_board_info.
 *  - For operating frequency information, see \subpage sam4c_ek_opfreq.
 *  - For using portable PIO definitions, see \subpage sam4c_ek_piodef.
 *  - For External components, see \subpage sam4c_ek_extcomp.
 *  - For Individual chip definition, see \subpage sam4c_ek_chipdef.
 *
 * To get more software details and the full list of parameters related to the
 * SAM4C-EK board configuration, please have a look at the source file:
 * \ref board.h\n
 *
 * \section Usage
 *
 *  - The code for booting the board is provided by board_cstartup_xxx.c and
 *    board_lowlevel.c.
 *  - For using board PIOs, board characteristics (clock, etc.) and external
 *    components, see board.h.
 *  - For manipulating memories, see board_memories.h.
 *
 * This file can be used as a template and modified to fit a custom board, with
 * specific PIOs usage or memory connections.
 */

/**
 *  \file board.h
 *
 *  Definition of SAM4C-EK characteristics, PIOs and
 *  external components interface.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "include/board_lowlevel.h"
#include "include/math.h"
#include "include/uart_console.h"


/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * \page sam4c_ek_board_info "SAM4C-EK - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "SAM4C-EK"

/*----------------------------------------------------------------------------*/
/**
 *  \page sam4c_ek_opfreq "SAM4C-EK - Operating frequencies"
 *  This page lists several definition related to the board operating frequency
 *  (when using the initialization done by board_lowlevel.c).
 *
 *  \section Definitions
 *  - \ref BOARD_MAINOSC
 *  - \ref BOARD_MCK
 */

/** Frequency of the board main oscillator */
#define BOARD_MAINOSC           8000000

/** Master clock frequency (when using board_lowlevel.c) */
#define BOARD_MCK               (48000000)

/*----------------------------------------------------------------------------*/
/**
 * \page sam4c_ek_piodef "SAM4C-EK - PIO definitions"
 * This pages lists all the pio definitions contained in board.h. The constants
 * are named using the following convention: PIN_* for a constant which defines
 * a single Pin instance (but may include several PIOs sharing the same
 * controller), and PINS_* for a list of Pin instances.
 *
 * ADC
 * - \ref PIN_ADC0_AD0
 * - \ref PIN_ADC0_AD1
 * - \ref PIN_ADC0_AD2
 * - \ref PIN_ADC0_AD3
 * - \ref PIN_ADC0_AD4
 * - \ref PIN_ADC0_AD5
 * - \ref PINS_ADC
 *
 * UART
 * - \ref PINS_UART
 *
 * LEDs
 * - \ref PIN_LED_0
 * - \ref PIN_LED_1
 * - \ref PIN_LED_2
 * - \ref PINS_LEDS
 *
 * Push buttons
 * - \ref PIN_PUSHBUTTON_1
 * - \ref PIN_PUSHBUTTON_2
 * - \ref PINS_PUSHBUTTONS
 * - \ref PUSHBUTTON_BP1
 * - \ref PUSHBUTTON_BP2
 *
 * SPI
 * - \ref PIN_SPI_MISO
 * - \ref PIN_SPI_MOSI
 * - \ref PIN_SPI_SPCK
 * - \ref PINS_SPI
 * - \ref PIN_SPI_NPCS0_PA11
 *
 * PCK0
 * - \ref PIN_PCK0
 *
 * PIO PARALLEL CAPTURE
 * - \ref PIN_PIODCEN1
 * - \ref PIN_PIODCEN2
 *
 * TWI
 * - \ref TWI_V3XX
 * - \ref PIN_TWI_TWD0
 * - \ref PIN_TWI_TWCK0
 * - \ref PINS_TWI0
 * - \ref PIN_TWI_TWD1
 * - \ref PIN_TWI_TWCK1
 * - \ref PINS_TWI1
 *
 * USART0
 * - \ref PIN_USART0_RXD
 * - \ref PIN_USART0_TXD
 * - \ref PIN_USART0_CTS
 * - \ref PIN_USART0_RTS
 * - \ref PIN_USART0_SCK
 *
 */

/** ADC_AD0 pin definition. */
#define PIN_ADC0_AD0 {1 << 12, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/** ADC_AD1 pin definition. */
#define PIN_ADC0_AD1 {1 << 4, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/** ADC_AD2 pin definition. */
#define PIN_ADC0_AD2 {1 << 5, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/** ADC_AD3 pin definition. */
#define PIN_ADC0_AD3 {1 << 13, PIOB, ID_PIOB, PIO_INPUT, PIO_DEFAULT}
/** ADC_AD4 pin definition. */
#define PIN_ADC0_AD4 {1 << 23, PIOB, ID_PIOB, PIO_INPUT, PIO_DEFAULT}
/** ADC_AD5 pin definition. */
#define PIN_ADC0_AD5 {1 << 31, PIOB, ID_PIOB, PIO_INPUT, PIO_DEFAULT}

/** Pins ADC */
#define PINS_ADC PIN_ADC0_AD0, PIN_ADC0_AD1, PIN_ADC0_AD2, PIN_ADC0_AD3, PIN_ADC0_AD4, PIN_ADC0_AD5

/** Startup time max, return from Idle mode (in µs) */
#define ADC_STARTUP_TIME_MAX       15
/** Track and hold Acquisition Time min (in ns) */
#define ADC_TRACK_HOLD_TIME_MIN  1200
/** ADC clock frequence */
#define BOARD_ADC_FREQ     (6000000)

/** UART pins (UTXD0 and URXD0) definitions, PB4,5. */
#define PINS_UART  { PIO_PB4A_URXD0|PIO_PB5A_UTXD0, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

/** LED #0 pin definition (Green). */
#define PIN_LED_0   {PIO_PC6, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
/** LED #1 pin definition (Amber). */
#define PIN_LED_1   {PIO_PC7, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
/** LED #2 pin definition (Blue). */
#define PIN_LED_2   {PIO_PC8, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}

/** List of all LEDs definitions. */
#define PINS_LEDS   PIN_LED_0, PIN_LED_1, PIN_LED_2

/** Push button #0 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PIN_PUSHBUTTON_1    {PIO_PA19, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PIN_PUSHBUTTON_2    {PIO_PA20, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
/** List of all push button definitions. */
#define PINS_PUSHBUTTONS    PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2

/** Push button #1 index. */
#define PUSHBUTTON_BP1   0
/** Push button #2 index. */
#define PUSHBUTTON_BP2   1

/** SPI MISO pin definition. */
#define PIN_SPI_MISO    {PIO_PC3A_SPI1_MISO, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI MOSI pin definition. */
#define PIN_SPI_MOSI    {PIO_PC4A_SPI1_MOSI, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI SPCK pin definition. */
#define PIN_SPI_SPCK    {PIO_PC5A_SPI1_SPCK, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI chip select pin definition. */
#define PIN_SPI_NPCS0_PA11  {PIO_PC2A_SPI1_NPCS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** List of SPI pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI        PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_SPCK

/** PCK0 */
#define PIN_PCK0        {PIO_PB13A_PCK0, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_PCK1        {PIO_PA29A_PCK1,PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/** TWI ver 3.xx */
#define TWI_V3XX
/** TWI0 data pin */
#define PIN_TWI_TWD0   {PIO_PA24A_TWD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** TWI0 clock pin */
#define PIN_TWI_TWCK0  {PIO_PA25A_TWCK0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** TWI0 pins */
#define PINS_TWI0      PIN_TWI_TWD0, PIN_TWI_TWCK0
/** TWI1 data pin */
#define PIN_TWI_TWD1   {PIO_PB0A_TWD1, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** TWI1 clock pin */
#define PIN_TWI_TWCK1  {PIO_PB1A_TWCK1, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** TWI1 pins */
#define PINS_TWI1      PIN_TWI_TWD1, PIN_TWI_TWCK1

/** USART0 pin RX */
#define PIN_USART0_RXD    {PIO_PB16A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** USART0 pin TX */
#define PIN_USART0_TXD    {PIO_PB17A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** USART0 pin CTS */
#define PIN_USART0_CTS    {PIO_PA20A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** USART0 pin RTS */
#define PIN_USART0_RTS    {PIO_PA19A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** USART0 pin SCK */
#define PIN_USART0_SCK    {PIO_PB18A_SCK0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/** USART1 pin RX */
#define PIN_USART1_RXD    {PIO_PA11A_RXD1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** USART1 pin TX */
#define PIN_USART1_TXD    {PIO_PA12A_TXD1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** USART1 pin CTS */
#define PIN_USART1_CTS    {PIO_PA18A_CTS1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** USART1 pin RTS */
#define PIN_USART1_RTS    {PIO_PA17A_RTS1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** USART1 pin ENABLE */
#define PIN_USART1_EN     {PIO_PA16A_SCK1, PIOA, ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
/** USART1 pin SCK */
#define PIN_USART1_SCK    {PIO_PA16A_SCK1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/*----------------------------------------------------------------------------*/
/**
 * \page sam4c_ek_chipdef "SAM4C-EK - Individual chip definition"
 * This page lists the definitions related to different chip's definition
 *
 * \section USART
 * - \ref BOARD_PIN_USART_RXD
 * - \ref BOARD_PIN_USART_TXD
 * - \ref BOARD_PIN_USART_CTS
 * - \ref BOARD_PIN_USART_RTS
 * - \ref BOARD_PIN_USART_EN
 * - \ref BOARD_USART_BASE
 * - \ref BOARD_ID_USART
 */

/** Rtc */
#define BOARD_RTC_ID                ID_RTC

/** USART RX pin for application */
#define BOARD_PIN_USART_RXD        PIN_USART1_RXD
/** USART TX pin for application */
#define BOARD_PIN_USART_TXD        PIN_USART1_TXD
/** USART CTS pin for application */
#define BOARD_PIN_USART_CTS        PIN_USART1_CTS
/** USART RTS pin for application */
#define BOARD_PIN_USART_RTS        PIN_USART1_RTS
/** USART ENABLE pin for application */
#define BOARD_PIN_USART_EN         PIN_USART1_EN
/** USART Base for application */
#define BOARD_USART_BASE           USART1
/** USART ID for application */
#define BOARD_ID_USART             ID_USART1

#endif /* #ifndef _BOARD_H_ */

