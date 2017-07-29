/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
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

//------------------------------------------------------------------------------
/// \dir
/// !Purpose
///
/// Definition and functions for using AT91SAM9M10-related features, such
/// has PIO pins, memories, etc.
///
/// !Usage
/// -# The code for booting the board is provided by board_cstartup.S and
///    board_lowlevel.c.
/// -# For using board PIOs, board characteristics (clock, etc.) and external
///    components, see board.h.
/// -# For manipulating memories (remapping, SDRAM, etc.), see board_memories.h.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \unit
/// !Purpose
///
/// Definition of AT91SAM9M10-EK characteristics, AT91SAM9M10-dependant PIOs and
/// external components interfacing.
///
/// !Usage
/// -# For operating frequency information, see "SAM9M10-EK - Operating frequencies".
/// -# For using portable PIO definitions, see "SAM9M10-EK - PIO definitions".
/// -# Several USB definitions are included here (see "SAM9M10-EK - USB device").
/// -# For external components definitions, see "SAM79260-EK - External components".
/// -# For memory-related definitions, see "SAM79260-EK - Memories".
//------------------------------------------------------------------------------

#ifndef BOARD_H
#define BOARD_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#if defined(at91sam9m10)
    #include "at91sam9m10/chip.h"
    #include "at91sam9m10/AT91SAM9M10.h"
#else
    #error Board does not support the specified chip.
#endif

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9M10-EK - Board Description"
/// This page lists several definition related to the board description.
///
/// !Definitions
/// - BOARD_NAME

/// Name of the board.
#define BOARD_NAME              "AT91SAM9M10-EK"
/// Board definition.
#define at91sam9m10ek
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9M10-EK - Operating frequencies"
/// This page lists several definition related to the board operating frequency
/// (when using the initialization done by board_lowlevel.c).
///
/// !Definitions
/// - BOARD_MAINOSC
/// - BOARD_MCK

/// Frequency of the board main oscillator.
#define BOARD_MAINOSC           12000000

/// Master clock frequency (when using board_lowlevel.c).
#define BOARD_MCK               ((unsigned long)((BOARD_MAINOSC / 3 / 2 / 3) * 200 )) // 133MHz

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9M10-EK - USB device"
///
/// !Constants
/// - BOARD_USB_BMATTRIBUTES

/// USB attributes configuration descriptor (bus or self powered, remote wakeup)
//#define BOARD_USB_BMATTRIBUTES USBConfigurationDescriptor_SELFPOWERED_RWAKEUP
#define BOARD_USB_BMATTRIBUTES   USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9M10-EK - PIO definitions"
/// This pages lists all the pio definitions contained in board.h. The constants
/// are named using the following convention: PIN_* for a constant which defines
/// a single Pin instance (but may include several PIOs sharing the same
/// controller), and PINS_* for a list of Pin instances.
///
/// !DBGU
/// - PINS_DBGU
///
/// !LEDs
/// - PIN_LED_0
/// - PIN_LED_1
/// - PINS_LEDS
/// - LED_POWER
/// - LED_DS1
///
/// !Push buttons
/// - PIN_PUSHBUTTON_1
/// - PIN_PUSHBUTTON_2
/// - PINS_PUSHBUTTONS
/// - PUSHBUTTON_BP1
/// - PUSHBUTTON_BP2
/// - JOYSTICK_LEFT
/// - JOYSTICK_RIGHT
///
/// !Joystick buttons
/// - PIN_JOYSTICK_UP
/// - PIN_JOYSTICK_DOWN
/// - PIN_JOYSTICK_LEFT
/// - PIN_JOYSTICK_RIGHT
/// - PIN_JOYSTICK_LCLIC, PIN_JOYSTICK_PUSH
/// - PINS_JOYSTICK_MOVE, PINS_JOYSTICK_CLIC, PINS_JOYSTICK
/// - JOYSTICK_UP
/// - JOYSTICK_DOWN
/// - JOYSTICK_LEFT
/// - JOYSTICK_RIGHT
/// - JOYSTICK_LCLIC, JOYSTICK_PUSH
///
/// !USART0
/// - PIN_USART0_RXD
/// - PIN_USART0_TXD
///
/// !SPI0
/// - PIN_SPI0_MISO
/// - PIN_SPI0_MOSI
/// - PIN_SPI0_SPCK
/// - PINS_SPI0
/// - PIN_SPI0_NPCS0
/// - PIN_SPI0_NPCS1
///
/// !SSC
/// - PINS_SSC_TX
///
/// !USB
/// - PIN_USB_VBUS
///
/// !MCI
/// - PINS_MCI
///
/// !PWM
/// - PIN_PWMC_PWM1
/// - PIN_PWMC_PWM3
/// - PIN_PWM_LED0
/// - PIN_PWM_LED1
/// - CHANNEL_PWM_LED0
/// - CHANNEL_PWM_LED1
///
/// !TWI
/// - PINS_TWI0
///
/// !TSADC
/// - PINS_TSADCC

/// List of all DBGU pin definitions.
#define PINS_DBGU  {(1<<12) | (1<<13), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

/// LED #0 pin definition.
#define PIN_LED_0   {1 << 0, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #1 pin definition.
#define PIN_LED_1   {1 << 31, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_OUTPUT_1, PIO_DEFAULT}
/// List of all LED definitions.
#define PINS_LEDS   PIN_LED_0, PIN_LED_1
/// Power LED index.
#define LED_POWER       0
/// DS1 LED index.
#define LED_DS1         1

/// Push button #1 pin definition.
#define PIN_PUSHBUTTON_1  {1 << 6, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Pusb button #2 pin definition.
#define PIN_PUSHBUTTON_2  {1 << 7, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// List of all pushbutton pin definitions.
#define PINS_PUSHBUTTONS  PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2
/// Push button #1 index.
#define PUSHBUTTON_BP1   0
/// Push button #2 index.
#define PUSHBUTTON_BP2   1

// Joystick definition.
/// Joystick UP.
#define PIN_JOYSTICK_UP    {1 << 16, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick DOWN.
#define PIN_JOYSTICK_DOWN  {1 << 17, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick LEFT.
#define PIN_JOYSTICK_LEFT  {1 << 14, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick RIGHT.
#define PIN_JOYSTICK_RIGHT {1 << 15, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick LEFT clic.
#define PIN_JOYSTICK_LCLIC {1 << 18, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick PUSH button.
#define PIN_JOYSTICK_PUSH  PIN_JOYSTICK_LCLIC
/// List of all Joystick click definitions
#define PINS_JOYSTICK_CLIC   PIN_JOYSTICK_LCLIC
/// List of all Joystick movement direction definitions
#define PINS_JOYSTICK_MOVE  PIN_JOYSTICK_UP, PIN_JOYSTICK_DOWN, \
                            PIN_JOYSTICK_LEFT, PIN_JOYSTICK_RIGHT
/// List of all Joystick definitions
#define PINS_JOYSTICK  PINS_JOYSTICK_MOVE, \
                       PINS_JOYSTICK_CLIC
/// Joystick UP index.
#define JOYSTICK_UP         0
/// Joystick DOWN index.
#define JOYSTICK_DOWN       1
/// Joystick LEFT index.
#define JOYSTICK_LEFT       2
/// Joystick RIGHT index.
#define JOYSTICK_RIGHT      3
/// Joystick LEFT CLICK index.
#define JOYSTICK_LCLIC      4
/// Joystick PUSH button index.
#define JOYSTICK_PUSH       4

/// USART0 TXD pin definition.
#define PIN_USART0_TXD  {1 << 19, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 RXD pin definition.
#define PIN_USART0_RXD  {1 << 18, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 RTS pin definition.
#define PIN_USART0_RTS  {1 << 17, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/// USART0 CTS pin definition.
#define PIN_USART0_CTS  {1 << 15, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/// USART0 SCK pin definition.
#define PIN_USART0_SCK  {1 << 16, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/// USART1 TXD pin definition.
#define PIN_USART1_TXD  {1 <<  4, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/// USART1 RXD pin definition.
#define PIN_USART1_RXD  {1 <<  5, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/// USART1 RTS pin definition.
#define PIN_USART1_RTS  {1 << 16, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_B, PIO_DEFAULT}
/// USART1 CTS pin definition.
#define PIN_USART1_CTS  {1 << 17, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_B, PIO_DEFAULT}
/// USART1 SCK pin definition.
#define PIN_USART1_SCK  {1 << 29, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_B, PIO_DEFAULT}

/// SPI0 MISO pin definition.
#define PIN_SPI0_MISO  {1 << 0, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}
/// SPI0 MOSI pin definition.
#define PIN_SPI0_MOSI  {1 << 1, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI0 SPCK pin definition.
#define PIN_SPI0_SPCK  {1 << 2, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/// List of SPI0 pin definitions (MISO, MOSI & SPCK).
#define PINS_SPI0      PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK
/// SPI0 chip select 0 pin definition.
#define PIN_SPI0_NPCS0 {1 << 3, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

/// SSC transmitter pins definition.
#define PINS_SSC_TX { (1 << 0) | (1 << 1) | (1 << 2), \
                      AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_A, PIO_DEFAULT}

/// USB VBus monitoring pin definition.
#define PIN_USB_VBUS    {1 << 19, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_DEFAULT}

/// USB VBus supply pin definition (SP2526A-2, active LOW, default to OFF).
#define PIN_USB_POWER_ENA {1 << 1, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_USB_POWER_ENB {1 << 3, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_OUTPUT_1, PIO_DEFAULT}

/// List of MCI pins definitions.
#define PINS_MCI0 \
    {(0x3EUL <<  0), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}, \
    {(0x1UL <<  0), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PINS_MCI1 \
    {(0x1FUL << 22), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}, \
    {(0x1UL <<  31), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_MCI0_DAT0 \
    {AT91C_PIO_PA2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_MCI1_DAT1 \
    {AT91C_PIO_PA23, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
#define PINS_MCI0_CD \
    {AT91C_PIO_PD10, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_INPUT, PIO_PULLUP}
#define PINS_MCI1_CD \
    {AT91C_PIO_PD11, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_INPUT, PIO_PULLUP}
#define PINS_MCI1_WP \
    {AT91C_PIO_PD29, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_INPUT, PIO_PULLUP}

/*
#define PINS_MCI  \
    {0x0000003B, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}, \
    {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
*/

/// PWMC PWM0 pin definition.
#define PIN_PWMC_PWM0  {1 << 24, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_B, PIO_DEFAULT}
/// PWMC PWM1 pin definition.
#define PIN_PWMC_PWM1  {1 << 31, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_B, PIO_DEFAULT}
/// PWMC PWM2 pin definition.
#define PIN_PWMC_PWM2  {1 << 26, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_B, PIO_DEFAULT}
/// PWMC PWM2 pin definition.
#define PIN_PWMC_PWM3  {1 <<  0, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_B, PIO_DEFAULT}

/// PWM pin definition for LED0
#define PIN_PWM_LED0 PIN_PWMC_PWM3
/// PWM pin definition for LED1
#define PIN_PWM_LED1 PIN_PWMC_PWM1
/// PWM channel for LED0
#define CHANNEL_PWM_LED0 3
/// PWM channel for LED1
#define CHANNEL_PWM_LED1 1

/// TWI  version 3xx
#define TWI_V3XX
/// TWI pins definition.
#define PINS_TWI0  {(1<<20) | (1<<21), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// TSADCC pins definition.
#define PINS_TSADCC {(1 << 20)|(1 << 21)|(1 << 22)|(1 << 23),\
                     AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_A, PIO_DEFAULT}

/// PCK0: PA31.B, PD12.B, PE0.B
//#define PIN_PCK0    {1 << 12, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
/// PCK1: PB31.B, PE31.B, 
#define PIN_PCK1    {1 << 31, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}

/// PIN used for reset the smartcard
#define PIN_ISO7816_RSTMC       {1 << 7, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}

/// Pins used for connect the smartcard
#define PINS_ISO7816            PIN_USART0_TXD, PIN_USART0_SCK, PIN_ISO7816_RSTMC

/// IRDA SD pin
#define PIN_IRDA_SD {0x1 << 8, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9M10-EK - External components"
/// This page lists the definitions related to external on-board components
/// located in the board.h file for the AT91SAM9M10-EK.
///
/// !AT45 Dataflash Card (A)
/// - BOARD_AT45_A_SPI_BASE
/// - BOARD_AT45_A_SPI_ID
/// - BOARD_AT45_A_SPI_PINS
/// - BOARD_AT45_A_SPI
/// - BOARD_AT45_A_NPCS
/// - BOARD_AT45_A_NPCS_PIN
///
/// !AT45 Dataflash (B)
/// - BOARD_AT45_B_SPI_BASE
/// - BOARD_AT45_B_SPI_ID
/// - BOARD_AT45_B_SPI_PINS
/// - BOARD_AT45_B_SPI
/// - BOARD_AT45_B_NPCS
/// - BOARD_AT45_B_NPCS_PIN
///
/// !LCD
/// - PINS_LCD
/// - BOARD_LCD_WIDTH
/// - BOARD_LCD_HEIGHT
/// - BOARD_LCD_BPP
/// - BOARD_LCD_IFWIDTH
/// - BOARD_LCD_FRAMESIZE_PIXELS
/// - BOARD_LCD_FRAMESIZE
/// - BOARD_LCD_FRAMERATE
/// - BOARD_LCD_PIXELCLOCK
/// - BOARD_LCD_DISPLAYTYPE
/// - BOARD_LCD_POLARITY_INVVD
/// - BOARD_LCD_POLARITY_INVFRAME
/// - BOARD_LCD_POLARITY_INVLINE
/// - BOARD_LCD_POLARITY_INVCLK
/// - BOARD_LCD_POLARITY_INVDVAL
/// - BOARD_LCD_CLOCKMODE
/// - BOARD_LCD_TIMING_VFP
/// - BOARD_LCD_TIMING_VBP
/// - BOARD_LCD_TIMING_VPW
/// - BOARD_LCD_TIMING_VHDLY
/// - BOARD_LCD_TIMING_HFP
/// - BOARD_LCD_TIMING_HBP
/// - BOARD_LCD_TIMING_HPW
///
/// !LCD
/// - PINS_LCD
/// - BOARD_LCD_WIDTH
/// - BOARD_LCD_HEIGHT
/// - BOARD_LCD_BPP
/// - BOARD_LCD_IFWIDTH
/// - BOARD_LCD_FRAMESIZE_PIXELS
/// - BOARD_LCD_FRAMESIZE
/// - BOARD_LCD_FRAMERATE
/// - BOARD_LCD_PIXELCLOCK
/// - BOARD_LCD_DISPLAYTYPE
/// - BOARD_LCD_POLARITY_INVVD
/// - BOARD_LCD_POLARITY_INVFRAME
/// - BOARD_LCD_POLARITY_INVLINE
/// - BOARD_LCD_POLARITY_INVCLK
/// - BOARD_LCD_POLARITY_INVDVAL
/// - BOARD_LCD_CLOCKMODE
/// - BOARD_LCD_TIMING_VFP
/// - BOARD_LCD_TIMING_VBP
/// - BOARD_LCD_TIMING_VPW
/// - BOARD_LCD_TIMING_VHDLY
/// - BOARD_LCD_TIMING_HFP
/// - BOARD_LCD_TIMING_HBP
/// - BOARD_LCD_TIMING_HPW
/// 
/// !Touchscreen
/// - BOARD_TOUCHSCREEN_ADCCLK
/// - BOARD_TOUCHSCREEN_STARTUP
/// - BOARD_TOUCHSCREEN_SHTIM
/// - BOARD_TOUCHSCREEN_DEBOUNCE
/// 
/// !SD Card
/// - BOARD_SD_MCI_BASE
/// - BOARD_SD_MCI_ID
/// - BOARD_SD_PINS
/// - BOARD_SD_SLOT
/// - BOARD_SD_BOOT_MCISLOT
///
/// !AC97
/// - PINS_AC97
///
/// !ISI
/// - BOARD_ISI_PIO_CNTRL1
/// - BOARD_ISI_PIO_CNTRL2
/// - BOARD_ISI_TWCK
/// - BOARD_ISI_TWD
/// - BOARD_ISI_MCK
/// - BOARD_ISI_VSYNC
/// - BOARD_ISI_HSYNC
/// - BOARD_ISI_PCK
/// - BOARD_ISI_PINS_DATA

/// Base address of SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_PINS         PINS_SPI0
/// Dataflash SPI number.
#define BOARD_AT45_A_SPI              0
/// Chip select connected to the dataflash.
#define BOARD_AT45_A_NPCS             0
/// Chip select pin connected to the dataflash.
#define BOARD_AT45_A_NPCS_PIN         PIN_SPI0_NPCS0


/// Base address of SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the dataflash.
#define BOARD_AT26_A_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the dataflash.
#define BOARD_AT26_A_SPI_PINS         PINS_SPI0
/// Dataflahs SPI number.
#define BOARD_AT26_A_SPI              0
/// Chip select connected to the dataflash.
#define BOARD_AT26_A_NPCS             0
/// Chip select pin connected to the dataflash.
#define BOARD_AT26_A_NPCS_PIN         PIN_SPI0_NPCS0

/// LCD pin list.
#define PINS_LCD    \
    {0x7FFFFFFD, AT91C_BASE_PIOE, AT91C_ID_PIOD_E, PIO_PERIPH_A, PIO_DEFAULT}

/// LCD enable & disable pin list
#define BOARD_LCD_ENABLE     {0x05, AT91C_BASE_PIOE, AT91C_ID_PIOD_E, PIO_OUTPUT_1, PIO_DEFAULT},\
                             {0x40, AT91C_BASE_PIOE, AT91C_ID_PIOD_E, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_LCD_DISABLE    {0x45, AT91C_BASE_PIOE, AT91C_ID_PIOD_E, PIO_OUTPUT_0, PIO_DEFAULT}

/// TV enable & disable pin list
#define BOARD_TV_ENABLE      {0x40, AT91C_BASE_PIOE, AT91C_ID_PIOD_E, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_TV_DISABLE     {0x40, AT91C_BASE_PIOE, AT91C_ID_PIOD_E, PIO_OUTPUT_0, PIO_DEFAULT}

/// Board is wired in RGB 565.
#define BOARD_LCD_BGR565
/// LCD pixel clock is not divide by two
#define LCDC_PIXELCLOCK_DOUBLE
/// Display width in pixels.
#define BOARD_LCD_WIDTH             480
/// Display height in pixels.
#define BOARD_LCD_HEIGHT            272
/// Display resolution in bits per pixel (bpp).
#define BOARD_LCD_BPP               AT91C_LCDC_PIXELSIZE_TWENTYFOURBITSPERPIXEL
/// Display interface width in bits.
#define BOARD_LCD_IFWIDTH           24
/// Frame size in pixels (height * width * bpp).
#define BOARD_LCD_FRAMESIZE_PIXELS  (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * 24)
/// Frame size in words (height * width * bpp / 32)
#define BOARD_LCD_FRAMESIZE         (BOARD_LCD_FRAMESIZE_PIXELS / 32)
/// Frame rate in Hz.
#define BOARD_LCD_FRAMERATE         60
/// Pixel clock rate in Hz (frameSize * frameRate / interfaceWidth).
#define BOARD_LCD_PIXELCLOCK        (BOARD_LCD_FRAMESIZE_PIXELS * BOARD_LCD_FRAMERATE / BOARD_LCD_IFWIDTH)
/// LCD display type.
#define BOARD_LCD_DISPLAYTYPE       AT91C_LCDC_DISTYPE_TFT
/// LCDC polarity.
#define BOARD_LCD_POLARITY_INVVD    AT91C_LCDC_INVVD_NORMALPOL
/// LCDVSYNC polarity.
#define BOARD_LCD_POLARITY_INVFRAME AT91C_LCDC_INVFRAME_INVERTEDPOL
/// LCDHSYNC polarity.
#define BOARD_LCD_POLARITY_INVLINE  AT91C_LCDC_INVLINE_INVERTEDPOL
/// LCDDOTCLK polarity.
#define BOARD_LCD_POLARITY_INVCLK   AT91C_LCDC_INVCLK_NORMALPOL
/// LCDDEN polarity.
#define BOARD_LCD_POLARITY_INVDVAL  AT91C_LCDC_INVDVAL_NORMALPOL
/// Pixel clock mode.
#define BOARD_LCD_CLOCKMODE         AT91C_LCDC_CLKMOD_ALWAYSACTIVE
/// Vertical front porch in number of lines.
#define BOARD_LCD_TIMING_VFP        4
/// Vertical back porch in number of lines.
#define BOARD_LCD_TIMING_VBP        4
/// Vertical pulse width in LCDDOTCLK cycles.
#define BOARD_LCD_TIMING_VPW        4
/// Number of cycles between VSYNC edge and HSYNC rising edge.
#define BOARD_LCD_TIMING_VHDLY      2
/// Horizontal front porch in LCDDOTCLK cycles.
#define BOARD_LCD_TIMING_HFP        5
/// Horizontal back porch in LCDDOTCLK cycles.
#define BOARD_LCD_TIMING_HBP        5
/// Horizontal pulse width in LCDDOTCLK cycles.
#define BOARD_LCD_TIMING_HPW        5
/// Touchscreen ADC clock frequency to use.
#define BOARD_TOUCHSCREEN_ADCCLK    300000 // 8MHz max
/// Touchscreen ADC startup time in µseconds.
#define BOARD_TOUCHSCREEN_STARTUP   40
/// Touchscreen ADC track and hold time in nanoseconds.
#define BOARD_TOUCHSCREEN_SHTIM     2000    // min 1µs at 8MHz
/// Touchscreen pen debounce time in nanoseconds.
#define BOARD_TOUCHSCREEN_DEBOUNCE  10000000

/// Base address of the MCI peripheral connected to the SD card.
#define BOARD_SD_MCI_BASE           AT91C_BASE_MCI0
#if defined(ORIGIN_SD_PORT_MCI1)
#undef BOARD_SD_MCI_BASE
#define BOARD_SD_MCI_BASE           AT91C_BASE_MCI1
#endif
#define BOARD_SD_MCI1_BASE           AT91C_BASE_MCI1
/// Dma channel number the mci is using
#define BOARD_MCI_DMA_CHANNEL       0
/// Peripheral identifier of the MCI connected to the SD card.
#define BOARD_SD_MCI_ID             AT91C_ID_MCI0
#if defined(ORIGIN_SD_PORT_MCI1)
#undef BOARD_SD_MCI_ID
#define BOARD_SD_MCI_ID             AT91C_ID_MCI1
#endif
#define BOARD_SD_MCI1_ID             AT91C_ID_MCI1
/// MCI pins that shall be configured to access the SD card.
#define BOARD_SD_PINS               PINS_MCI0
#define BOARD_SD_DAT0               PIN_MCI0_DAT0
#if defined(ORIGIN_SD_PORT_MCI1)
#undef BOARD_SD_PINS
#define BOARD_SD_PINS               PINS_MCI1
#undef BOARD_SD_DAT0
#define BOARD_SD_DAT0               PIN_MCI1_DAT0
#endif
#define BOARD_SD_MCI1_PINS          PINS_MCI1
/// MCI slot to which the SD card is connected to.
#define BOARD_SD_SLOT               MCI_SD_SLOTA
#if defined(ORIGIN_SD_PORT_MCI1)
#undef BOARD_SD_SLOT
#define BOARD_SD_SLOT               MCI_SD_SLOTA  // MCI1 using MCI1's slotA
#endif
#define BOARD_SD_MCI1_SLOT          MCI_SD_SLOTA  // MCI1 using MCI1's slotA
/// SD card write protection pin definition.
//#define BOARD_SD_PIN_WP             PINS_MCI1_WP
/// SD card detection pin definition.
#define BOARD_SD_PIN_CD             PINS_MCI0_CD
#if defined(ORIGIN_SD_PORT_MCI1)
#undef BOARD_SD_PIN_CD
#define BOARD_SD_PIN_CD             PINS_MCI1_CD
#endif
#define BOARD_SD_MCI1_PIN_CD             PINS_MCI1_CD
/// MCI0 DMA hardware handshaking ID
#define DMA_HW_SRC_REQ_ID_MCI0      AT91C_HDMA_SRC_PER_0
#define DMA_HW_DEST_REQ_ID_MCI0     AT91C_HDMA_DST_PER_0
/// MCI1 DMA hardware handshaking ID
#define DMA_HW_SRC_REQ_ID_MCI1      AT91C_HDMA_SRC_PER_13
#define DMA_HW_DEST_REQ_ID_MCI1     AT91C_HDMA_DST_PER_13
/// SD DMA hardware handshaking ID
#define BOARD_SD_DMA_HW_SRC_REQ_ID      DMA_HW_SRC_REQ_ID_MCI0
#define BOARD_SD_DMA_HW_DEST_REQ_ID     DMA_HW_DEST_REQ_ID_MCI0
#if defined(ORIGIN_SD_PORT_MCI1)
#undef BOARD_SD_DMA_HW_SRC_REQ_ID
#define BOARD_SD_DMA_HW_SRC_REQ_ID      DMA_HW_SRC_REQ_ID_MCI1
#undef BOARD_SD_DMA_HW_DEST_REQ_ID
#define BOARD_SD_DMA_HW_DEST_REQ_ID     DMA_HW_DEST_REQ_ID_MCI1
#endif
/// SD boot slot
#define BOARD_SD_BOOT_MCISLOT    0

/// PHY address
#define BOARD_EMAC_PHY_ADDR         0
/// PHY Component
#define BOARD_EMAC_PHY_COMP_DM9161  1
/// Board EMAC power control - ALWAYS ON
#define BOARD_EMAC_POWER_ALWAYS_ON
/// Board EMAC work mode - RMII/MII ( 1 / 0 )
#define BOARD_EMAC_MODE_RMII        1

/// The PIN list of PIO for EMAC
#define BOARD_EMAC_PINS     {  (1<<27)|(1<<28)|(1<<29)|(1<<30)\
                              |(1<< 6)|(1<< 7)|(1<< 8)|(1<< 9),\
                              AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}, \
                            {  (1<<10)|(1<<11)|(1<<12)|(1<<13)|(1<<14)|(1<<15)\
                              |(1<<16)|(1<<17)|(1<<18)|(1<<19),\
                              AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// The power up reset latch PIO for PHY
#define BOARD_EMAC_PIN_TEST   {(1<<15), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}//RX_DV
#define BOARD_EMAC_PIN_RMII   {(1<<30), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}//COL
// We force the address
//(1<<12) RXD0/PHY address 0, (1<<13) RXD1/PHY address 1, (1<<8) RXD2/PHY address 2,
//(1<<9) RXD3/PHY address 3, (1<<29) CRS/PHY address 4
#define BOARD_EMAC_PINS_PHYAD {(1<<12)|(1<<13)|(1<<8)|(1<<9)|(1<<29),\
                               AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define BOARD_EMAC_PIN_10BT   {(1<<28), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}//RX_CLK
#define BOARD_EMAC_PIN_RPTR   {(1<<16), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}//RX_ER/RXD4
/// The PIN Configure list for EMAC on power up reset (RMII)
#define BOARD_EMAC_RST_PINS BOARD_EMAC_PINS_PHYAD, \
                            BOARD_EMAC_PIN_TEST, BOARD_EMAC_PIN_RMII, \
                            BOARD_EMAC_PIN_10BT, BOARD_EMAC_PIN_RPTR

/// The runtime pin configure list for EMAC
#define BOARD_EMAC_RUN_PINS BOARD_EMAC_PINS

/// AC97 pins definition.
#define PINS_AC97   {(1<<6)|(1<<7)|(1<<8)|(1<<9),\
                     AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_PERIPH_A, PIO_DEFAULT}

/// ISI
#define BOARD_ISI_V200
#define BOARD_CAPTOR_OV2640
#define BOARD_ISI_PIO_CTRL1 {(1<<12), AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_OUTPUT_0, PIO_DEFAULT}
#define BOARD_ISI_PIO_CTRL2 {(1<<13), AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_OUTPUT_0, PIO_DEFAULT}
#define BOARD_ISI_TWCK      {(1<<21), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_ISI_TWD       {(1<<20), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
// PCK1 use instead of ISI_MCK
#define BOARD_ISI_MCK       {(1<<31), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define BOARD_ISI_VSYNC     {(1<<29), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_ISI_HSYNC     {(1<<30), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_ISI_PCK       {(1<<28), AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_ISI_PINS_DATA {(1<<20)|(1<<21)|(1<<22)|(1<<23)|(1<<24)|(1<<25)|(1<<26)|(1<<27),\
                             AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT},\
                            {(1<<8)|(1<<9)|(1<<10)|(1<<11),\
                             AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9M10-EK - Memories"
/// This page lists definitions related to external on-board memories.
///
/// !DDRAM
/// - BOARD_DDRAM_SIZE
/// - PINS_DDRAM
/// - BOARD_DDRAM_BUSWIDTH
/// - BOARD_SDRAM_BUSWIDTH
///
/// !Nandflash
/// - PINS_NANDFLASH
/// - BOARD_NF_EBI_COMMAND_ADDR
/// - BOARD_NF_EBI_ADDRESS_ADDR
/// - BOARD_NF_EBI_DATA_ADDR
/// - BOARD_NF_CE_PIN
/// - BOARD_NF_RB_PIN
///
/// !NorFlash
/// - BOARD_NORFLASH_ADDR
/// - BOARD_NORFLASH_DFT_BUS_SIZE

/// Board DDRAM size
#define BOARD_DDRAM_SIZE        (128*1024*1024)  // 128 MB
/// List of all SDRAM pins definitions.
#define PINS_DDRAM              {0xFFFF0000, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/// DDRAM bus width.
#define BOARD_DDRAM_BUSWIDTH    16
/// SDRAM bus width.
#define BOARD_SDRAM_BUSWIDTH    32

/// Nandflash controller peripheral pins definition.
#define PINS_NANDFLASH          BOARD_NF_CE_PIN
/// Nandflash chip enable pin definition.
#define BOARD_NF_CE_PIN         {1 << 14, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
/// Address for transferring command bytes to the nandflash.
#define BOARD_NF_COMMAND_ADDR   0x40400000
/// Address for transferring address bytes to the nandflash.
#define BOARD_NF_ADDRESS_ADDR   0x40200000
/// Address for transferring data bytes to the nandflash.
#define BOARD_NF_DATA_ADDR      0x40000000

/// Address for transferring command bytes to the norflash.
#define BOARD_NORFLASH_ADDR     0x10000000
/// Default NOR bus size after power up reset
#define BOARD_NORFLASH_DFT_BUS_SIZE 16
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9M10-EK- Individual chip definition"
/// This page lists the definitions related to different chip's definition
/// located in the board.h file for the SAM9M10-EK.
#define BOARD_RTC_ID                AT91C_ID_SYS

/// Twi eeprom
#define BOARD_ID_TWI_EEPROM         AT91C_ID_TWI0
#define BOARD_BASE_TWI_EEPROM       AT91C_BASE_TWI0
#define BOARD_PINS_TWI_EEPROM       PINS_TWI0

/// USART
#define BOARD_PIN_USART_RXD        PIN_USART1_RXD
#define BOARD_PIN_USART_TXD        PIN_USART1_TXD
#define BOARD_PIN_USART_CTS        PIN_USART1_CTS
#define BOARD_PIN_USART_RTS        PIN_USART1_RTS
#define BOARD_USART_BASE           AT91C_BASE_US1
#define BOARD_ID_USART             AT91C_ID_US1
//------------------------------------------------------------------------------

#endif //#ifndef BOARD_H

