/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation
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
 * \page sam3n_ek_board_desc SAM3N-EK - Board Description
 *
 * \section Purpose
 *
 * A file is dedicated to descibe the SAM3N-EK board.
 *
 * \section Contents
 *
 *  - For SAM3N-EK information, see \subpage sam3n_ek_board_info.
 *  - For operating frequency information, see \subpage sam3n_ek_opfreq.
 *  - For using portable PIO definitions, see \subpage sam3n_ek_piodef.
 *  - For on-board memories, see \subpage sam3n_ek_mem.
 *  - For LCD parameters, see \subpage sam3n_ek_lcd.
 *  - For SD Card parameters, see \subpage sam3n_ek_sd.
 *  - For serial flash parameters, see \subpage sam3n_ek_sf.
 *
 * To get more software details and the full list of parameters related to the
 * SAM3N-EK board configuration, please have a look at the source file:
 * \ref board.h\n
 *
 * \section Usage
 *
 *  - The code for booting the board is provided by board_cstartup_xxx.c and
 *    board_lowlevel.c.
 *  - For using board PIOs, board characteristics (clock, etc.) and external
 *    components, see board.h.
 *
 * This file can be used as a template and modified to fit a custom board, with
 * specific PIOs usage or memory connections.
 */

/**
 *  \file board.h
 *
 *  Definition of SAM3N-EK characteristics, dependant PIOs and
 *  external components interfacing.
 */

#ifndef BOARD_H
#define BOARD_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "chip.h"

#include "include/board_lowlevel.h"
#include <include/at25d.h>
#include <include/at25_spi.h>

#include "include/math.h"
#include "include/uart_console.h"

/**
 * Libc porting layers
 */
#if defined   ( __CC_ARM   ) /* Keil µVision 4 */
#    include "include/rand.h"
#elif defined ( __ICCARM__ ) /* IAR Ewarm 5.41+ */
#    include "include/rand.h"
//#elif defined (  __GNUC__  ) /* GCC CS3 2009q3-68/2010q1-188 */
//#    include "include/syscalls.h" /** RedHat Newlib minimal stub */
#endif

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * \page sam3n_ek_board_info "SAM3N-EK - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "SAM3N-EK"
/** Board definition */
#define sam3nek
/** Family definition (already defined) */
#define sam3n
/** Core definition */
#define cortexm3

/*----------------------------------------------------------------------------*/
/**
 *  \page sam3n_ek_opfreq "SAM3N-EK - Operating frequencies"
 *  This page lists several definition related to the board operating frequency
 *  (when using the initialization done by board_lowlevel.c).
 *
 *  \section Definitions
 *  - \ref BOARD_MAINOSC
 *  - \ref BOARD_MCK
 */

/** Frequency of the board main oscillator */
#define BOARD_MAINOSC           12000000

/** Master clock frequency (when using board_lowlevel.c) */
#define BOARD_MCK               48000000

/*----------------------------------------------------------------------------*/
/**
 * \page sam3n_ek_piodef "SAM3N-EK - PIO definitions"
 * This pages lists all the pio definitions contained in board.h. The constants
 * are named using the following convention: PIN_* for a constant which defines
 * a single Pin instance (but may include several PIOs sharing the same
 * controller), and PINS_* for a list of Pin instances.
 *
 * Uart0
 * - \ref PINS_UART0
 *
 * Leds
 * - \ref PIN_POWER_LED
 * - \ref PIN_LED_BLUE
 * - \ref PIN_LED_AMBER
 * - \ref PIN_LED_GREEN
 * - \ref PINS_LEDS
 *
 * Spi
 * - \ref PIN_SPI_MISO
 * - \ref PIN_SPI_MOSI
 * - \ref PIN_SPI_SPCK
 * - \ref PINS_SPI
 * - \ref PIN_SPI_NPCS0_SDCARD
 * - \ref PIN_SPI_NPCS1_ZIGBEE
 * - \ref PIN_SPI_NPCS2_LCD
 * - \ref PIN_SPI_NPCS3_AT25
 *
 * Push buttons
 * - \ref PIN_PB_USER1
 * - \ref PIN_PB_USER2
 * - \ref PINS_PB_USER
 *
 * Lcd
 * - \ref PIN_LCD_RS
 * - \ref PIN_LCD_RSTN
 * - \ref PIN_LCD_BACKLIGTH
 * - \ref PINS_LCD
 *
 * Serial flash
 * - \ref PINS_AT25
 *
 * Sdcard
 * - \ref PINS_SDCARD
 *
 * Zigbee
 * - \ref PINS_ZIGBEE
 *
 * PWM for Buzzer
 * - \ref PIN_PWM_BUZZER
 * - \ref CHANNEL_PWM_BUZZER
 *
 * PWM for LEDs
 * - \ref PIN_PWM_LED0
 * - \ref PIN_PWM_LED1
 * - \ref PIN_PWM_LED2
 * - \ref CHANNEL_PWM_LED0
 * - \ref CHANNEL_PWM_LED1
 * - \ref CHANNEL_PWM_LED2
 *
 * QTouch Slider
 * - \ref SLIDER_IOMASK_SNS
 * - \ref SLIDER_IOMASK_SNSK
 * - \ref PINS_SLIDER_SNS
 * - \ref PINS_SLIDER_SNSK
 *
 * QTouch Keys
 * - \ref KEY_IOMASK_SNS
 * - \ref KEY_IOMASK_SNSK
 * - \ref PINS_KEY_SNS
 * - \ref PINS_KEY_SNSK
 *
 * TWI
 * - \ref PINS_TWI0
 * - \ref PINS_TWI1
 *
 * PCK
 * - \ref PIN_PCK0
 * - \ref PIN_PCK1
 *
 * USART
 * - \ref PIN_USART0_RXD
 * - \ref PIN_USART0_TXD
 * - \ref PIN_USART0_RTS
 * - \ref PIN_USART0_CTS
 * - \ref PIN_USART0_SCK
 * - \ref PIN_USART1_RXD
 * - \ref PIN_USART1_TXD
 * - \ref PIN_USART1_RTS
 * - \ref PIN_USART1_CTS
 * - \ref PIN_USART1_SCK
 *
 * ISO7816
 * - \ref PIN_ISO7816_RSTMC
 * - \ref PINS_ISO7816
 * - \ref BOARD_ISO7816_BASE_USART
 * - \ref BOARD_ISO7816_ID_USART
 */

/* ===============  LED =============== */
/** POWER_LED pin definition (RED). */
#define PIN_POWER_LED   {PIO_PA0, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/** LED BLUE pin definition. */
#define PIN_LED_BLUE    {PIO_PA23, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/** LED AMBER pin definition. */
#define PIN_LED_AMBER   {PIO_PA25, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/** LED GREEN pin definition. */
#define PIN_LED_GREEN   {PIO_PB14, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}

/** List of all LEDs definitions. */
#define PINS_LEDS   PIN_LED_BLUE, PIN_LED_GREEN, PIN_LED_AMBER, PIN_POWER_LED

/* =============== UART0 =============== */
/** UART0 pin RX */
#define PIN_RX_UART0    {PIO_PA9A_URXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** UART0 pin TX */
#define PIN_TX_UART0    {PIO_PA10A_UTXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** UART0 pin definitions */
#define PINS_UART0 PIN_RX_UART0, PIN_TX_UART0

/* =============== SPI =============== */
/** SPI MISO pin definition. */
#define PIN_SPI_MISO    {PIO_PA12A_MISO, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI MOSI pin definition. */
#define PIN_SPI_MOSI    {PIO_PA13A_MOSI, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI SPCK pin definition. */
#define PIN_SPI_SPCK    {PIO_PA14A_SPCK, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI chip select pin definition for Micro SD connector. */
#define PIN_SPI_NPCS0_SDCARD  {PIO_PA11A_NPCS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI chip select pin definition for Zigbee extension board. */
#define PIN_SPI_NPCS1_ZIGBEE  {PIO_PA31A_NPCS1, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/** SPI chip select pin definition for LCD. */
#define PIN_SPI_NPCS2_LCD     {PIO_PA30B_NPCS2, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/** SPI chip select pin definition for Serial Flash. */
#define PIN_SPI_NPCS3_AT25    {PIO_PA22B_NPCS3, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/** List of SPI pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI        PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_SPCK

/* =============== Push Buttons =============== */
/** Push button #0 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PIN_PB_USER1    {PIO_PA15, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on falling edge. */
#define PIN_PB_USER2    {PIO_PA16, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
/** List of all push button definitions. */
#define PINS_PB_USER    PIN_PB_USER1, PIN_PB_USER2

/* =============== LCD =============== */
/** LCD Register Select pin definition. */
#define PIN_LCD_RS  {PIO_PA28, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/** LCD Reset pin definition: active low */
#define PIN_LCD_RSTN {PIO_PA29, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/** LCD backlight definition */
#define PIN_LCD_BACKLIGTH {PIO_PC13, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
/** List of all LCD pin definitions. */
#define PINS_LCD    PIN_SPI_SPCK, PIN_SPI_MOSI, PIN_SPI_NPCS2_LCD, PIN_LCD_RS, PIN_LCD_RSTN

/* =============== DATAFLASH =============== */
/** List of all Serial flash pin definitions. */
#define PINS_AT25         PINS_SPI, PIN_SPI_NPCS3_AT25

/* =============== SDCARD =============== */
/** List of all SDCARD pin definitions. */
#define PINS_SDCARD       PINS_SPI, PIN_SPI_NPCS0_SDCARD

/* =============== ZIGBEE =============== */
/** Zigbee Reset pin definition: active low */
#define PIN_ZIGBEE_RSTN {PIO_PC23, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
/** Zigbee Irq1 definition */
#define PIN_ZIGBEE_IRQ1 {PIO_PC25, PIOC, ID_PIOC, PIO_INPUT, PIO_PULLUP | PIO_IT_RISE_EDGE}
/** List of all SDCARD pin definitions. */
#define PINS_ZIGBEE       PINS_SPI, PIN_SPI_NPCS1_ZIGBEE, PIN_ZIGBEE_RSTN, PIN_ZIGBEE_IRQ1

/* =============== PWM for BUZZER =============== */
/** PWM pins definition for buzzer */
#define PIN_PWM_BUZZER {PIO_PA1A_PWM1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** PWM channel for BUZZER */
#define CHANNEL_PWM_BUZZER 1

/* =============== PWM for LEDs =============== */
/** PWM pins definition for LED0 */
#define PIN_PWM_LED0 {PIO_PA23B_PWM0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/** PWM pins definition for LED1 */
#define PIN_PWM_LED1 {PIO_PB14B_PWM3, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/** PWM pins definition for LED2 */
#define PIN_PWM_LED2 {PIO_PA25B_PWM2, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/** PWM channel for LED0 */
#define CHANNEL_PWM_LED0 0
/** PWM channel for LED1 */
#define CHANNEL_PWM_LED1 3
/** PWM channel for LED2 */
#define CHANNEL_PWM_LED2 2

/* =============== QTOUCH =============== */
/** List of all Slider pin definitions. */
#define SLIDER_IOMASK_SNS   (PIO_PC0 | PIO_PC2 | PIO_PC4)
#define SLIDER_IOMASK_SNSK  (PIO_PC1 | PIO_PC3 | PIO_PC5)
#define PINS_SLIDER_SNS     {SLIDER_IOMASK_SNS,  PIOC, ID_PIOC, PIO_INPUT, PIO_DEFAULT}
#define PINS_SLIDER_SNSK    {SLIDER_IOMASK_SNSK, PIOC, ID_PIOC, PIO_INPUT, PIO_DEFAULT}

/** List of all Keys pin definitions. */
#define KEY_IOMASK_SNS   (PIO_PC8 | PIO_PC10 )
#define KEY_IOMASK_SNSK  (PIO_PC9 | PIO_PC11 )
#define PINS_KEY_SNS     {KEY_IOMASK_SNS,  PIOC, ID_PIOC, PIO_INPUT, PIO_DEFAULT}
#define PINS_KEY_SNSK    {KEY_IOMASK_SNSK, PIOC, ID_PIOC, PIO_INPUT, PIO_DEFAULT}

/** PIOS for QTouch */
#define PINS_QTOUCH     PINS_SLIDER_SNS, PINS_SLIDER_SNSK, PINS_KEY_SNS, PINS_KEY_SNSK

/* =============== TWI =============== */
/** TWI0 peripheral */
#define PIN_TWI_TWD0    {PIO_PA3A_TWD0,  PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_TWI_TWCK0   {PIO_PA4A_TWCK0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/** TWI1 peripheral */
#define PIN_TWI_TWD1    {PIO_PB4A_TWD1,  PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_TWI_TWCK1   {PIO_PB5A_TWCK1, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

/** TWI0 pin definitions */
#define PINS_TWI0       PIN_TWI_TWD0, PIN_TWI_TWCK0
/** TWI1 pin definitions */
#define PINS_TWI1       PIN_TWI_TWD1, PIN_TWI_TWCK1

/* =============== PCK =============== */
/** PCK0 pin definition. */
#define PIN_PCK0        {PIO_PA6B_PCK0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/** PCK1 pin definition. */
#define PIN_PCK1        {PIO_PA17B_PCK1,PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}

/* =============== USART =============== */
/** RXD0 pin definition. */
#define PIN_USART0_RXD  {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** TXD0 pin definition. */
#define PIN_USART0_TXD  {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** RTS0 pin definition. */
#define PIN_USART0_RTS  {PIO_PA7A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** CTS0 pin definition. */
#define PIN_USART0_CTS  {PIO_PA8A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** SCK0 pin definition. */
#define PIN_USART0_SCK  {PIO_PA2B_SCK0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}

/** RXD1 pin definition. */
#define PIN_USART1_RXD  {PIO_PA21A_RXD1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** TXD1 pin definition. */
#define PIN_USART1_TXD  {PIO_PA22A_TXD1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** RTS1 pin definition. */
#define PIN_USART1_RTS  {PIO_PA24A_RTS1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** CTS1 pin definition. */
#define PIN_USART1_CTS  {PIO_PA25A_CTS1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** SCK1 pin definition. */
#define PIN_USART1_SCK  {PIO_PA23A_SCK1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/* =============== ISO7816 =============== */
/** PIN used for reset the smartcard */
#define PIN_ISO7816_RSTMC       {1 << 17, PIOA, ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
/** Pins used for connect the smartcard */
#define PINS_ISO7816            PIN_USART0_TXD, PIN_USART0_SCK, PIN_ISO7816_RSTMC
/** Base address of USART for the smartcard */
#define BOARD_ISO7816_BASE_USART    USART0
/** Peripheral ID of USART for the smartcard */
#define BOARD_ISO7816_ID_USART      ID_USART0


/*----------------------------------------------------------------------------*/
/**
 * \page sam3n_ek_mem "SAM3N-EK - Memories"
 * This page lists definitions related to internal & external on-board memories.
 *
 * \section SRAM
 * - \ref AT91C_IRAM
 * - \ref AT91C_IRAM_SIZE
 *
 * \section Flash
 * - \ref AT91C_IFLASH_SIZE
 * - \ref AT91C_IFLASH_PAGE_SIZE
 * - \ref AT91C_IFLASH_NB_OF_PAGES
 * - \ref AT91C_IFLASH_LOCK_REGION_SIZE
 * - \ref AT91C_IFLASH_NB_OF_LOCK_BITS
 */
/* Add new memories here. */


/*----------------------------------------------------------------------------*/
/**
 *  \page sam3n_ek_lcd "SAM3N-EK - LCD parameters"
 *  This page lists several definition related to the lcd parameters
 *
 *  \section Definitions
 *  - \ref BOARD_LCD_SPCK
 *  - \ref BOARD_LCD_NPCS
 *  - \ref BOARD_LCD_DLYBS
 *  - \ref BOARD_LCD_DLYBCT
 *  - \ref BOARD_LCD_WIDTH
 *  - \ref BOARD_LCD_HEIGHT
 */
/** LCD Spi Clock frequency */
#define BOARD_LCD_SPCK             (BOARD_MCK)
/** LCD Spi Chip Select */
#define BOARD_LCD_NPCS              2
/** LCD Spi Delay Before SPCK: >=10ns */
#define BOARD_LCD_DLYBS             1
/** LCD Spi DLYBCT: Delay Between Consecutive Transfers */
#define BOARD_LCD_DLYBCT            0
/** Display width in pixels. */
#define BOARD_LCD_WIDTH             176
/** Display height in pixels. */
#define BOARD_LCD_HEIGHT            220


/*----------------------------------------------------------------------------*/
/**
 *  \page sam3n_ek_sd "SAM3N-EK - SD(SPI) parameters"
 *  This page lists several definition related to the SD(SPI) parameters
 *
 *  \section Definitions
 *  - \ref BOARD_SD_SPCK
 *  - \ref BOARD_SD_PIN_CD
 *  - \ref BOARD_SD_SPI_BASE
 *  - \ref BOARD_SD_SPI_ID
 *  - \ref BOARD_SD_SPI_PINS
 *  - \ref BOARD_SD_SPI_IRQn
 *  - \ref BOARD_SD_NPCS
 */
/** SD Spi Clock frequency */
#define BOARD_SD_SPCK               10000000ul
/** SD Card Detect */
#define BOARD_SD_PIN_CD             {PIO_PA19, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP}
/** SD Spi Base */
#define BOARD_SD_SPI_BASE           SPI
/** SD Spi ID */
#define BOARD_SD_SPI_ID             ID_SPI
/** SD Spi Pins (and init other used NPCS to avoid conflict) */
#define BOARD_SD_SPI_PINS           PINS_SDCARD ,\
                                    PIN_SPI_NPCS1_ZIGBEE, \
                                    PIN_SPI_NPCS2_LCD, \
                                    PIN_SPI_NPCS3_AT25
/** SD SPI IRQn */
#define BOARD_SD_SPI_IRQn           SPI_IRQn
/** SD Spi Chip Select */
#define BOARD_SD_NPCS               0

/*----------------------------------------------------------------------------*/
/**
 *  \page sam3n_ek_sf "SAM3N-EK - Serial flash(SPI) parameters"
 *  This page lists several definition related to the serial flash(SPI) parameters.
 */
/** AT25 Spi Clock frequency */
#define BOARD_SF_SPCK               10000000ul
/** AT25 Spi Chip Select */
#define BOARD_AT25_NPCS             3

#endif /* #ifndef BOARD_H */

