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
/// Definition and functions for using AT91CAP9-related features, such
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
/// Definition of AT91CAP9-DK characteristics, AT91CAP9-dependant PIOs and
/// external components interfacing.
///
/// !Usage
/// -# For operating frequency information, see "AT91CAP9-DK - Operating frequencies".
/// -# For using portable PIO definitions, see "AT91CAP9-DK - PIO definitions".
/// -# Several USB definitions are included here (see "AT91CAP9-DK - USB device").
/// -# For external components definitions, see "AT91CAP9-DK - External components".
/// -# For memory-related definitions, see "AT91CAP9-DK - Memories".
//------------------------------------------------------------------------------

#ifndef BOARD_H
#define BOARD_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#if defined(at91cap9)
    #include "at91cap9/chip.h"
    #include "at91cap9/AT91CAP9.h"
#else
    #error Board does not support the specified chip.
#endif

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-DK - Board Description"
/// This page lists several definition related to the board description
///
/// !Definitions
/// - BOARD_NAME

/// Name of the board.
#define BOARD_NAME "AT91CAP9-DK"
/// Board definition.
#define at91cap9dk
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-DK - Operating frequencies"
/// This page lists several definition related to the board operating frequency
/// (when using the initialization done by board_lowlevel.c).
///
/// !Definitions
/// - BOARD_MAINOSC
/// - BOARD_MCK

/// Frequency of the board main oscillator.
#define BOARD_MAINOSC           12000000

/// Master clock frequency (when using board_lowlevel.c).
#define BOARD_MCK               ((12000000 * 50 / 3) / 2)

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ADC
//------------------------------------------------------------------------------
/// ADC clock frequency, at 10-bit resolution (in Hz)
#define ADC_MAX_CK_10BIT         5000000
/// Startup time max, return from Idle mode (in µs)
#define ADC_STARTUP_TIME_MAX       40
/// Track and hold Acquisition Time min (in ns)
#define ADC_TRACK_HOLD_TIME_MIN   500

//------------------------------------------------------------------------------
/// \page "AT91CAP9-DK - USB device"
///
/// !Constants
/// - BOARD_USB_BMATTRIBUTES

/// USB attributes configuration descriptor (bus or self powered, remote wakeup)
#define BOARD_USB_BMATTRIBUTES USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-DK - PIO definitions"
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
/// - LED_DS2
/// 
/// !Push buttons
/// - PIN_KEYBOARD_COL0
/// - PIN_KEYBOARD_COL1
/// - PIN_KEYBOARD_COL2
/// - PIN_KEYBOARD_COL3
/// - PIN_KEYBOARD_ROW0
/// - PIN_KEYBOARD_ROW1
/// - PIN_KEYBOARD_ROW2
/// - PIN_KEYBOARD_ROW3
/// - PINS_KEYBOARD_COL
/// - PINS_KEYBOARD_ROW
/// - PIN_PUSHBUTTON_1
/// - PIN_PUSHBUTTON_2
/// - PIN_PUSHBUTTON_3
/// - PIN_PUSHBUTTON_4
/// - PINS_PUSHBUTTONS
/// - PUSHBUTTON_BP1
/// - PUSHBUTTON_BP2
/// - JOYSTICK_LEFT
/// - JOYSTICK_RIGHT
/// - JOYSTICK_UP
/// - JOYSTICK_DOWN
/// 
/// !USART0
/// - PIN_USART0_RXD
/// - PIN_USART0_TXD
/// - PIN_USART0_RTS
/// - PIN_USART0_CTS
/// - PIN_USART0_SCK
/// 
/// !USART1
/// - PIN_USART1_RXD
/// - PIN_USART1_TXD
///
/// !USART2
/// - PIN_USART2_RXD
/// - PIN_USART2_TXD
///
/// !SPI0
/// - PIN_SPI0_MISO
/// - PIN_SPI0_MOSI
/// - PIN_SPI0_SPCK
/// - PINS_SPI0
/// - PIN_SPI0_NPCS0
/// 
/// !AC97
/// - PINS_AC97
///
/// !PWMC
/// - PIN_PWMC_PWM0
/// - PIN_PWMC_PWM1
/// - PIN_PWM_LED0
/// - PIN_PWM_LED1
/// - CHANNEL_PWM_LED0
/// - CHANNEL_PWM_LED1
///
/// !ADC
/// - PIN_ADC_ADC0
/// - PIN_ADC_ADC1
/// - PIN_ADC_ADC2
/// - PIN_ADC_ADC3
/// - PINS_ADC
///
/// !SSC
/// - PINS_SSC_TX
/// 
/// !USB
/// - PIN_USB_VBUS
///
/// !CAN
/// - PIN_CAN_TRANSCEIVER_RS
/// - PIN_CAN1_TRANSCEIVER_TXD
/// - PIN_CAN1_TRANSCEIVER_RXD
/// - PIN_CAN2_TRANSCEIVER_TXD
/// - PIN_CAN2_TRANSCEIVER_RXD
/// - PINS_CAN_TRANSCEIVER_TXD
/// - PINS_CAN_TRANSCEIVER_RXD

/// !PCK
/// - PIN_PCK0
/// - PIN_PCK1
/// - PIN_PCK2

/// List of all DBGU pin definitions.
#define PINS_DBGU   {(1<<30)|(1<<31), AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// LED #0 pin definition.
#define PIN_LED_0  {AT91C_PIO_PA10, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
/// LED #1 pin definition.
#define PIN_LED_1  {AT91C_PIO_PA11, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
/// LED #2 pin definition.
#define PIN_LED_2  {AT91C_PIO_PC29, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
/// List of all LEDs definitions.
#define PINS_LEDS  PIN_LED_0, PIN_LED_1, PIN_LED_2

/// Keyboard rows ( scanning output )
#define PIN_KEYBOARD_ROW0 {1 << 10, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_KEYBOARD_ROW1 {1 << 11, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_KEYBOARD_ROW2 {1 << 12, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_KEYBOARD_ROW3 {1 << 13, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}

#define PIN_KEYBOARD_COL0 {1 << 9, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}
#define PIN_KEYBOARD_COL1 {1 << 8, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}
#define PIN_KEYBOARD_COL2 {1 << 7, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}
#define PIN_KEYBOARD_COL3 {1 << 6, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}

#define PINS_KEYBOARD_ROW PIN_KEYBOARD_ROW0, PIN_KEYBOARD_ROW1, PIN_KEYBOARD_ROW2, PIN_KEYBOARD_ROW3
#define PINS_KEYBOARD_COL PIN_KEYBOARD_COL0, PIN_KEYBOARD_COL1, PIN_KEYBOARD_COL2, PIN_KEYBOARD_COL3

/// Push button #1 pin definition.
#define PIN_PUSHBUTTON_1  PIN_KEYBOARD_COL0
/// Push button #2 pin definition.
#define PIN_PUSHBUTTON_2  PIN_KEYBOARD_COL1
/// Push button #3 pin definition.
#define PIN_PUSHBUTTON_3  PIN_KEYBOARD_COL2
/// Push button #4 pin definition.
#define PIN_PUSHBUTTON_4  PIN_KEYBOARD_COL3
/// List of push button pin definitions.
#define PINS_PUSHBUTTONS  PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2, PIN_PUSHBUTTON_3, PIN_PUSHBUTTON_4
/// Push button #1 index.
#define PUSHBUTTON_BP1   0
/// Push button #2 index.
#define PUSHBUTTON_BP2   1
/// Simulated joystick LEFT index.
#define JOYSTICK_LEFT       0
/// Simulated joystick RIGHT index.
#define JOYSTICK_RIGHT      1
/// Simulated joystick UP index.
#define JOYSTICK_UP         2
/// Simulated joystick DOWN index.
#define JOYSTICK_DOWN       3

/// USART0 TXD pin definition.
#define PIN_USART0_RXD  {1 << 23, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 RXD pin definition.
#define PIN_USART0_TXD  {1 << 22, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 RTS pin definition.
#define PIN_USART0_RTS  {1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 CTS pin definition.
#define PIN_USART0_CTS  {1 << 25, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 SCK pin definition.
#define PIN_USART0_SCK  {1 << 26, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// USART1 TXD pin definition.
#define PIN_USART1_RXD  {1 << 1, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// USART1 RXD pin definition.
#define PIN_USART1_TXD  {1 << 0, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// USART2 TXD pin definition.
#define PIN_USART2_RXD  {1 << 3, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// USART2 RXD pin definition.
#define PIN_USART2_TXD  {1 << 2, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// SPI MISO pin definition.
#define PIN_SPI0_MISO  {AT91C_PA0_SPI0_MISO, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_PULLUP}
/// SPI MOSI pin definition.
#define PIN_SPI0_MOSI  {AT91C_PA1_SPI0_MOSI, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
/// SPI SPCK pin definition.
#define PIN_SPI0_SPCK  {AT91C_PA2_SPI0_SPCK, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
/// List of SPI pin definitions (MISO, MOSI & SPCK).
#define PINS_SPI0      PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK
/// SPI chip select 0 pin definition.
#define PIN_SPI0_NPCS0 {AT91C_PA5_SPI0_NPCS0, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
/// SPI chip select 1 pin definition.
#define PIN_SPI0_NPCS1 {AT91C_PA3_SPI0_NPCS1, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
/// SPI chip select 2 pin definition.
#define PIN_SPI0_NPCS2 {AT91C_PA4_SPI0_NPCS2A, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
/// SPI chip select 3 pin definition.
#define PIN_SPI0_NPCS3 {AT91C_PD1_SPI0_NPCS3D, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}

/// AC97 pins definition.
#define PINS_AC97   {0x000003C0, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// PWMC PWM1 pin definition.
#define PIN_PWMC_PWM1  {1 << 10, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
/// PWMC PWM2 pin definition.
#define PIN_PWMC_PWM3  {1 << 11, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
/// PWM pin definition for LED0
#define PIN_PWM_LED0 PIN_PWMC_PWM1
/// PWM pin definition for LED1
#define PIN_PWM_LED1 PIN_PWMC_PWM3
/// PWM channel for LED0
#define CHANNEL_PWM_LED0 1
/// PWM channel for LED1
#define CHANNEL_PWM_LED1 3

/// ADC_AD0 pin definition.
#define PIN_ADC_ADC0  {AT91C_PB13_AD0, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD1 pin definition.
#define PIN_ADC_ADC1  {AT91C_PB14_AD1, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD2 pin definition.
#define PIN_ADC_ADC2  {AT91C_PB15_AD2, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD3 pin definition.
#define PIN_ADC_ADC3  {AT91C_PB16_AD3, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD0 pin definition.
#define PIN_ADC_ADC4  {AT91C_PB17_AD4, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD1 pin definition.
#define PIN_ADC_ADC5  {AT91C_PB18_AD5, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD2 pin definition.
#define PIN_ADC_ADC6  {AT91C_PB19_AD6, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD3 pin definition.
#define PIN_ADC_ADC7  {AT91C_PB20_AD7, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}
/// Pins ADC
#define PINS_ADC PIN_ADC_ADC0, PIN_ADC_ADC1, PIN_ADC_ADC2, PIN_ADC_ADC3

/// SSC transmitter pins definition.
#define PINS_SSC_TX { (1 << 0) | (1 << 1) | (1 << 2), \
                      AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// USB VBus monitoring pin definition.
#define PIN_USB_VBUS    {1 << 31, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}

/// CAN Definition
/// RS: Select input for high speed mode or silent mode
#define PIN_CAN_TRANSCEIVER_RS  {1<<12, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_OUTPUT_1, PIO_DEFAULT}

/// TXD: Transmit data input
#define PIN_CAN1_TRANSCEIVER_TXD  {1<<12, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// RXD: Receive data output
#define PIN_CAN1_TRANSCEIVER_RXD  {1<<13, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// TXD pins
#define PINS_CAN_TRANSCEIVER_TXD  PIN_CAN1_TRANSCEIVER_TXD
/// RXD pins
#define PINS_CAN_TRANSCEIVER_RXD  PIN_CAN1_TRANSCEIVER_RXD

// PCK pins
#define PIN_PCK0    {1 << 12, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_PCK1    {1 << 27, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_PCK1bis {1 << 10, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_PCK2    {1 << 15, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-DK - External components"
/// This page lists the definitions related to external on-board components
/// located in the board.h file for the AT91CAP9-DK.
/// 
/// !AT45 Dataflash
/// - BOARD_AT45_A_SPI_BASE
/// - BOARD_AT45_A_SPI_ID
/// - BOARD_AT45_A_SPI_PINS
/// - BOARD_AT45_A_SPI
/// - BOARD_AT45_A_NPCS
/// - BOARD_AT45_A_NPCS_PIN
///
/// !AT26 Serial Flash
/// - BOARD_AT26_A_SPI_BASE
/// - BOARD_AT26_A_SPI_ID
/// - BOARD_AT26_A_SPI_PINS
/// - BOARD_AT26_A_SPI
/// - BOARD_AT26_A_NPCS
/// - BOARD_AT26_A_NPCS_PIN
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
/// !TouchScreen
/// - BOARD_TSC_ADS7843
/// - PIN_TCS_IRQ
/// - PIN_TCS_BUSY
/// - BOARD_TSC_SPI_BASE
/// - BOARD_TSC_SPI_ID
/// - BOARD_TSC_SPI_PINS
/// - BOARD_TSC_NPCS
/// - BOARD_TSC_NPCS_PIN
/// 
/// !SD Card (MCI0)
/// - BOARD_SD_MCI_BASE
/// - BOARD_SD_MCI_ID
/// - BOARD_SD_PINS
/// - BOARD_SD_PIN_CD
/// - BOARD_SD_SLOT
///
/// !SD Card (MCI1)
/// - BOARD_SD_MCI1_BASE
/// - BOARD_SD_MCI1_ID
/// - BOARD_SD_MCI1_PINS
/// - BOARD_SD_MCI1_PIN_CD
/// - BOARD_SD_BOOT_MCISLOT
///
/// !SD Card SPI
/// - BOARD_SD_SPI_BASE
/// - BOARD_SD_SPI_ID
/// - BOARD_SD_SPI_PINS
/// - BOARD_SD_NPCS
///
/// !EMAC
/// - BOARD_EMAC_PHY_ADDR
/// - BOARD_EMAC_PHY_COMP_DM9161
/// - BOARD_EMAC_POWER_ALWAYS_ON
/// - BOARD_EMAC_MODE_RMII
/// - BOARD_EMAC_PINS
/// - BOARD_EMAC_PIN_RXDV
/// - BOARD_EMAC_PIN_COL
/// - BOARD_EMAC_RST_PINS
///
/// !UDA1342
/// - BOARD_UDA1342_TWI_BASE
/// - BOARD_UDA1342_TWI_ID
/// - BOARD_UDA1342_TWI_PINS
/// - BOARD_UDA1342_SSC_BASE
/// - BOARD_UDA1342_SSC_ID
/// - BOARD_UDA1342_SSC_PINS
/// - BOARD_UDA1342_MCK_PIN
/// - BOARD_UDA1342_SLAVE_ADDR
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
///
/// !AT98SC
/// - BOARD_AT98SC_SPI_BASE
/// - BOARD_AT98SC_SPI_ID
/// - BOARD_AT98SC_SPI_PINS
/// - BOARD_AT98SC_NPCS
/// - BOARD_AT98SC_NPCS_PIN

/// Base address of SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_PINS         PINS_SPI0
/// Dataflahs SPI number.
#define BOARD_AT45_A_SPI              0
/// Chip select connected to the dataflash.
#define BOARD_AT45_A_NPCS             0
/// Chip select pin connected to the dataflash.
#define BOARD_AT45_A_NPCS_PIN         PIN_SPI0_NPCS0

/// Base address of SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_PINS         PINS_SPI0
/// Serialflash SPI number.
#define BOARD_AT26_A_SPI              0
/// Chip select connected to the serialflash.
#define BOARD_AT26_A_NPCS             0
/// Chip select pin connected to the serialflash.
#define BOARD_AT26_A_NPCS_PIN         PIN_SPI0_NPCS0

/// LCD pin list.
#define PINS_LCD    \
    {0x00000200, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}, \
    {0x0FCFCFCE, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// Display width in pixels.
#define BOARD_LCD_WIDTH             240
/// Display height in pixels.
#define BOARD_LCD_HEIGHT            320
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
#define BOARD_LCD_POLARITY_INVFRAME AT91C_LCDC_INVFRAME_NORMALPOL
/// LCDHSYNC polarity.
#define BOARD_LCD_POLARITY_INVLINE  AT91C_LCDC_INVLINE_NORMALPOL
/// LCDDOTCLK polarity.
#define BOARD_LCD_POLARITY_INVCLK   AT91C_LCDC_INVCLK_NORMALPOL
/// LCDDEN polarity.
#define BOARD_LCD_POLARITY_INVDVAL  AT91C_LCDC_INVDVAL_NORMALPOL
/// Pixel clock mode.
#define BOARD_LCD_CLOCKMODE         AT91C_LCDC_CLKMOD_ALWAYSACTIVE
/// Vertical front porch in number of lines.
#define BOARD_LCD_TIMING_VFP        2
/// Vertical back porch in number of lines.
#define BOARD_LCD_TIMING_VBP        4
/// Vertical pulse width in LCDDOTCLK cycles.
#define BOARD_LCD_TIMING_VPW        1
/// Number of cycles between VSYNC edge and HSYNC rising edge.
#define BOARD_LCD_TIMING_VHDLY      1
/// Horizontal front porch in LCDDOTCLK cycles.
#define BOARD_LCD_TIMING_HFP        11
/// Horizontal back porch in LCDDOTCLK cycles.
#define BOARD_LCD_TIMING_HBP        17
/// Horizontal pulse width in LCDDOTCLK cycles.
#define BOARD_LCD_TIMING_HPW        5

/// Indicates board has an ADS7843 external component to manage Touch Screen
#define BOARD_TSC_ADS7843

/// Touchscreen controller IRQ pin definition.
#define PIN_TCS_IRQ {AT91C_PIO_PC4, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}
/// Touchscreen controller Busy pin definition.
#define PIN_TCS_BUSY {AT91C_PIO_PC5, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}

/// Base address of SPI peripheral connected to the touchscreen controller.
#define BOARD_TSC_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the touchscreen controller.
#define BOARD_TSC_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the touchscreen controller.
#define BOARD_TSC_SPI_PINS         PINS_SPI0
/// Chip select connected to the touchscreen controller.
#define BOARD_TSC_NPCS             3
/// Chip select pin connected to the touchscreen controller.
#define BOARD_TSC_NPCS_PIN         PIN_SPI0_NPCS3

/// Base address of the MCI peripheral connected to the SD card.
#define BOARD_SD_MCI_BASE           AT91C_BASE_MCI0
/// Peripheral identifier of the MCI connected to the SD card.
#define BOARD_SD_MCI_ID             AT91C_ID_MCI0
/// MCI pins that shall be configured to access the SD card.
#define BOARD_SD_PINS               PINS_MCI
/// MCI slot to which the SD card is connected to.
#define BOARD_SD_SLOT               MCI_SD_SLOTA
/// SD card detection pin definition.
#define BOARD_SD_PIN_CD     {AT91C_PIO_PC20, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}
/// SD boot slot
#define BOARD_SD_BOOT_MCISLOT    0

/// List of MCI pins definitions.
#define PINS_MCI  {0x0000003F, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// Base address of the MCI peripheral connected to the SD card.
#define BOARD_SD_MCI1_BASE           AT91C_BASE_MCI1
/// Peripheral identifier of the MCI connected to the SD card.
#define BOARD_SD_MCI1_ID             AT91C_ID_MCI1
/// MCI pins that shall be configured to access the SD card.
#define BOARD_SD_MCI1_PINS          PINS_MCI1
/// Second MCI slot to which the SD card is connected to.
#define BOARD_SD_MCI1_SLOT          MCI_SD_SLOTA
/// SD card detection pin definition.
#define BOARD_SD_MCI1_PIN_CD     {AT91C_PIO_PC21, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}

/// List of MCI pins definitions.
#define PINS_MCI1  {0x003F0000, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// Base address of the SPI peripheral connected to the SD card.
#define BOARD_SD_SPI_BASE   AT91C_BASE_SPI0
/// Identifier of the SPI peripheral connected to the SD card.
#define BOARD_SD_SPI_ID     AT91C_ID_SPI0
/// List of pins to configure to access the SD card
#define BOARD_SD_SPI_PINS   PINS_SPI0, PIN_SPI0_NPCS0
/// NPCS number
#define BOARD_SD_NPCS       0

/// TWI0 pins definition.
#define PINS_TWI  {(1<<4) | (1<<5), AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}


/// PHY address
#define BOARD_EMAC_PHY_ADDR         0
/// PHY Component
#define BOARD_EMAC_PHY_COMP_DM9161  1
/// Board EMAC power control - ALWAYS ON
#define BOARD_EMAC_POWER_ALWAYS_ON
/// Board EMAC work mode - RMII/MII ( 1 / 0 )
#define BOARD_EMAC_MODE_RMII        1

/// The PIN list of PIO for EMAC
#define BOARD_EMAC_PINS     {0x7FE00000, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}, \
                            {0x0FF00000, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
#define BOARD_EMAC_PIN_RXDV {(1<<22), AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_EMAC_PIN_COL  {(1<<26), AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// The PIN Configure list for EMAC on power up reset (MII)
#define BOARD_EMAC_RST_PINS BOARD_EMAC_PIN_RXDV, BOARD_EMAC_PIN_COL
/// The runtime pin configure list for EMAC
#define BOARD_EMAC_RUN_PINS BOARD_EMAC_PINS

/// UDA1342
#define BOARD_UDA1342_TWI_BASE   AT91C_BASE_TWI
#define BOARD_UDA1342_TWI_ID     AT91C_ID_TWI
#define BOARD_UDA1342_TWI_PINS   PINS_TWI
#define BOARD_UDA1342_SSC_BASE   AT91C_BASE_SSC0
#define BOARD_UDA1342_SSC_ID     AT91C_ID_SSC0
#define BOARD_UDA1342_SSC_PINS   PINS_SSC_TX
#define BOARD_UDA1342_MCK_PIN    PIN_PCK1bis
#define BOARD_UDA1342_SLAVE_ADDR 0x1A

/// ISI
#define BOARD_CAPTOR_OV9650
#define BOARD_ISI_PIO_CTRL1 {(1<<14), AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
#define BOARD_ISI_PIO_CTRL2 {(1<<15), AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
#define BOARD_ISI_TWCK      {(1<<5),  AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
#define BOARD_ISI_TWD       {(1<<4),  AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
// PCK1 use instead of ISI_MCK
#define BOARD_ISI_MCK       {(1<<27), AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_ISI_VSYNC     {(1<<26), AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
#define BOARD_ISI_HSYNC     {(1<<25), AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
#define BOARD_ISI_PCK       {(1<<24), AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
#define BOARD_ISI_PINS_DATA {(1<<16)|(1<<17)|(1<<18)|(1<<19)|(1<<20)|(1<<21)|(1<<22)|\
                             (1<<23)|(1<<28)|(1<<29)|(1<<30)|(1<<31),\
                             AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}

/// Base address of SPI peripheral connected to the AT98 secure chip.
#define BOARD_AT98SC_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the AT98 secure chip.
#define BOARD_AT98SC_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the AT98 secure chip.
#define BOARD_AT98SC_SPI_PINS         PINS_SPI0
/// Chip select connected to the AT98 secure chip.
#define BOARD_AT98SC_NPCS             0
/// Chip select pin connected to the AT98 secure chip.
#define BOARD_AT98SC_NPCS_PIN         PIN_SPI0_NPCS0

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-DK - Memories"
/// This page lists definitions related to external on-board memories.
/// 
/// !SDRAM
/// - BOARD_SDRAM_SIZE
/// - PINS_SDRAM
/// - BOARD_SDRAM_BUSWIDTH
///
/// !DDRAM
/// - BOARD_DDRAM_SIZE
/// - BOARD_DDRAM_BUSWIDTH
///
/// !BCRAM
/// - BOARD_BCRAM_SIZE
/// - BOARD_BCRAM_BUSWIDTH
///
/// !Nandflash
/// - PINS_NANDFLASH
/// - BOARD_NF_CE_PIN
/// - BOARD_NF_RB_PIN
/// - BOARD_NF_COMMAND_ADDR
/// - BOARD_NF_ADDRESS_ADDR
/// - BOARD_NF_DATA_ADDR
///
/// !NorFlash
/// - BOARD_NORFLASH_ADDR
/// - BOARD_NORFLASH_DFT_BUS_SIZE

/// Board SDRAM size
#define BOARD_SDRAM_SIZE        (64*1024*1024)  // with AT91CAP-MEM33 extension
/// List of all SDRAM pins definitions.
#define PINS_SDRAM              {0xFFFF0000, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// SDRAM bus width.
#define BOARD_SDRAM_BUSWIDTH    32

/// Board DDRAM size
#define BOARD_DDRAM_SIZE   (32*1024*1024) // with AT91CAP-MEM18 extension
/// DDRAM bus width.
#define BOARD_DDRAM_BUSWIDTH    16

/// Board BCRAM size
#define BOARD_BCRAM_SIZE   (16*1024*1024) // with AT91CAP-MEM18 extension
/// BCRAM bus width.
#define BOARD_BCRAM_BUSWIDTH    16

/// Nandflash controller peripheral pins definition.
#define PINS_NANDFLASH          BOARD_NF_CE_PIN
/// Nandflash output enable pin definition.
//#define PIN_NF_OE              // => dedicated pin
/// Nandflash write enable pin definition
//#define PIN_NF_WE              // => dedicated pin
/// Nandflash chip enable pin definition.
#define BOARD_NF_CE_PIN        {1 << 15, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_OUTPUT_1, PIO_DEFAULT}
/// Nandflash ready/busy pin definition.
#define BOARD_NF_RB_PIN        { 0, 0, 0, 0, 0}// Not used on the DK board. Use Read Status Register Command
/// Address for transferring command bytes to the nandflash.
#define BOARD_NF_COMMAND_ADDR  0x40400000
/// Address for transferring address bytes to the nandflash.
#define BOARD_NF_ADDRESS_ADDR  0x40200000
/// Address for transferring data bytes to the nandflash.
#define BOARD_NF_DATA_ADDR     0x40000000

/// Address for transferring command bytes to the norflash.
#define BOARD_NORFLASH_ADDR  0x10000000
/// Dafult Nor bus size after power reser
#define BOARD_NORFLASH_DFT_BUS_SIZE 16

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Library naming workaround
//------------------------------------------------------------------------------

/// Source type definition
#define AIC_SRCTYPE   AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL

#define AT91C_EBI_DDRAM  (AT91_CAST(char *)     0x70000000) // DDRAM on EBI Chip Select 6 base address
#define AT91C_EBI_DDRAM_SIZE     (16*1024*1024) // DDRAM on EBI Chip Select 6 size in byte (262144 Kbytes)

//------------------------------------------------------------------------------
/// \page "AT91CAP9-DK - Individual chip definition"
/// This page lists the definitions related to different chip's definition
/// located in the board.h file for the AT91CAP9-DK

/// Twi define
#define BOARD_ID_TWI_EEPROM         AT91C_ID_TWI
#define BOARD_BASE_TWI_EEPROM       AT91C_BASE_TWI
#define BOARD_PINS_TWI_EEPROM       PINS_TWI

/// USART
#define BOARD_PIN_USART_RXD        PIN_USART0_RXD
#define BOARD_PIN_USART_TXD        PIN_USART0_TXD
#define BOARD_PIN_USART_CTS        PIN_USART0_CTS
#define BOARD_PIN_USART_RTS        PIN_USART0_RTS
#define BOARD_USART_BASE           AT91C_BASE_US0
#define BOARD_ID_USART             AT91C_ID_US0
//------------------------------------------------------------------------------


#endif //#ifndef BOARD_H

