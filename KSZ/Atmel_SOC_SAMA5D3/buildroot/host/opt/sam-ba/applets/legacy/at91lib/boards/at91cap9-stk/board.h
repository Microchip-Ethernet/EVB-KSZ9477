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
/// Definition of AT91CAP9-STK characteristics, AT91CAP9-dependant PIOs and
/// external components interfacing.
/// 
/// !Usage
/// -# For operating frequency information, see "AT91CAP9-STK - Operating frequencies".
/// -# For using portable PIO definitions, see "AT91CAP9-STK - PIO definitions".
/// -# Several USB definitions are included here (see "AT91CAP9-STK - USB device").
/// -# For external components definitions, see "AT91CAP9-STK - External components".
/// -# For memory-related definitions, see "AT91CAP9-STK - Memories".
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
/// \page "AT91CAP9-STK - Board Description"
/// This page lists several definition related to the board description
///
/// !Definitions
/// - BOARD_NAME

/// Name of the board.
#define BOARD_NAME "AT91CAP9-STK"
/// Board definition.
#define at91cap9stk
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-STK - Operating frequencies"
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
/// \page "AT91CAP9-STK - USB device"
/// 
/// !Constants
/// - BOARD_USB_BMATTRIBUTES

/// USB attributes configuration descriptor (bus or self powered, remote wakeup)
#define BOARD_USB_BMATTRIBUTES USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-STK - PIO definitions"
/// This pages lists all the pio definitions contained in board.h. The constants
/// are named using the following convention: PIN_* for a constant which defines
/// a single Pin instance (but may include several PIOs sharing the same
/// controller), and PINS_* for a list of Pin instances.
///
/// !Programmable clocks
/// - PIN_PCK2
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
/// - PIN_PUSHBUTTON_1
/// - PIN_PUSHBUTTON_2
/// - PINS_PUSHBUTTONS
/// - PUSHBUTTON_BP1
/// - PUSHBUTTON_BP2
/// - JOYSTICK_LEFT
/// - JOYSTICK_RIGHT
/// 
/// !SPI0
/// - PIN_SPI0_MISO
/// - PIN_SPI0_MOSI
/// - PIN_SPI0_SPCK
/// - PINS_SPI0
/// - PIN_SPI0_NPCS0
/// - PIN_SPI0_NPCS1
/// - PIN_SPI0_NPCS2
///
/// !SPI1
/// - PIN_SPI1_MISO
/// - PIN_SPI1_MOSI
/// - PIN_SPI1_SPCK
/// - PINS_SPI1
/// - PIN_SPI1_NPCS0
///
/// !SSC
/// - PINS_SSC_TX
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
/// !USB
/// - PIN_USB_VBUS
/// 
/// !MCI
/// - PINS_MCI
/// 
/// !TWI
/// - PINS_TWI

/// PCK0 pin definition.
#define PIN_PCK2  {AT91C_PA15_PCK2, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}

/// List of all DBGU pin definitions.
#define PINS_DBGU   {(1<<30)|(1<<31), AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// LED #0 pin definition.
#define PIN_LED_0  {AT91C_PIO_PA10, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
/// LED #1 pin definition.
#define PIN_LED_1  {AT91C_PIO_PA14, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_OUTPUT_0, PIO_DEFAULT}
/// List of all LEDs definitions.
#define PINS_LEDS  PIN_LED_0, PIN_LED_1

/// Push button #1 pin definition.
#define PIN_PUSHBUTTON_1  {1 << 9, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}
/// Push button #2 pin definition.
#define PIN_PUSHBUTTON_2  {1 << 8, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}
/// List of push button pin definitions.
#define PINS_PUSHBUTTONS  PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2
/// Push button #1 index.
#define PUSHBUTTON_BP1   0
/// Push button #2 index.
#define PUSHBUTTON_BP2   1
/// Simulated joystick LEFT index.
#define JOYSTICK_LEFT    0
/// Simulated joystick RIGHT index.
#define JOYSTICK_RIGHT   1

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

/// SPI MISO pin definition.
#define PIN_SPI1_MISO  {AT91C_PB12_SPI1_MISO, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_PULLUP}
/// SPI MOSI pin definition.
#define PIN_SPI1_MOSI  {AT91C_PB13_SPI1_MOSI, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI SPCK pin definition.
#define PIN_SPI1_SPCK  {AT91C_PB14_SPI1_SPCK, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// List of SPI pin definitions (MISO, MOSI & SPCK).
#define PINS_SPI1      PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK
/// SPI chip select 0 pin definition.
#define PIN_SPI1_NPCS0 {AT91C_PB15_SPI1_NPCS0, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI chip select 1 pin definition.
#define PIN_SPI1_NPCS1 {AT91C_PB16_SPI1_NPCS1, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI chip select 2 pin definition.
#define PIN_SPI1_NPCS2 {AT91C_PB17_SPI1_NPCS2B, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI chip select 3 pin definition.
#define PIN_SPI1_NPCS3 {AT91C_PB18_SPI1_NPCS3B, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// SSC transmitter pins definition.
#define PINS_SSC_TX { (1 << 0) | (1 << 1) | (1 << 2), \
                      AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

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

/// USB  monitoring pin definition.
#define PIN_USB_VBUS    {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_INPUT, PIO_DEFAULT}

/// List of MCI pins definitions.
#define PINS_MCI  {0x003F0000, AT91C_BASE_PIOA, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}

/// TWI0 pins definition.
#define PINS_TWI  {(1<<4) | (1<<5), AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-STK - External components"
/// This page lists the definitions related to external on-board components
/// located in the board.h file for the AT91CAP9-STK.
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
/// !SD Card
/// - BOARD_SD_MCI_BASE
/// - BOARD_SD_MCI_ID
/// - BOARD_SD_PINS
/// - BOARD_SD_PIN_CD
/// - BOARD_SD_SLOT
///
/// !EMAC
/// - BOARD_EMAC_PHY_ADDR
/// - BOARD_EMAC_PHY_COMP_LAN8700
/// - BOARD_EMAC_PIN_PWRDN
/// - BOARD_EMAC_MODE_RMII
/// - BOARD_EMAC_PINS
/// - BOARD_EMAC_PIN_RXDV
/// - BOARD_EMAC_PIN_COL
/// - BOARD_EMAC_RST_PINS
/// - BOARD_EMAC_RUN_PINS
///
/// !AT73C213
/// - BOARD_AT73C213_SPI
/// - BOARD_AT73C213_SPI_ID
/// - BOARD_AT73C213_NPCS
/// - BOARD_AT73C213_SSC
/// - BOARD_AT73C213_SSC_ID
/// - BOARD_AT73C213_MCK
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
#define BOARD_AT26_A_SPI_BASE         AT91C_BASE_SPI
/// Identifier of SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_ID           AT91C_ID_SPI
/// Pins of the SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_PINS         PINS_SPI0
/// Serialflash SPI number.
#define BOARD_AT26_A_SPI              0
/// Chip select connected to the serialflash.
#define BOARD_AT26_A_NPCS             0
/// Chip select pin connected to the serialflash.
#define BOARD_AT26_A_NPCS_PIN         PIN_SPI_NPCS0

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
#define BOARD_TSC_NPCS             1
/// Chip select pin connected to the touchscreen controller.
#define BOARD_TSC_NPCS_PIN         PIN_SPI0_NPCS1

/// Base address of the MCI peripheral connected to the SD card.
#define BOARD_SD_MCI_BASE           AT91C_BASE_MCI1
/// Peripheral identifier of the MCI connected to the SD card.
#define BOARD_SD_MCI_ID             AT91C_ID_MCI1
/// MCI pins that shall be configured to access the SD card.
#define BOARD_SD_PINS               PINS_MCI
/// MCI slot to which the SD card is connected to.
#define BOARD_SD_SLOT               MCI_SD_SLOTA
/// SD card detection pin definition.
#define BOARD_SD_PIN_CD     {AT91C_PIO_PC21, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_INPUT, PIO_PULLUP}

/// Base address of the MCI peripheral connected to the SD card.
#define BOARD_SD_MCI1_BASE           BOARD_SD_MCI_BASE
/// Peripheral identifier of the MCI connected to the SD card.
#define BOARD_SD_MCI1_ID             BOARD_SD_MCI_ID
/// MCI pins that shall be configured to access the SD card.
#define BOARD_SD_MCI1_PINS          PINS_MCI
/// Second MCI slot to which the SD card is connected to.
#define BOARD_SD_MCI1_SLOT          MCI_SD_SLOTA
/// SD card detection pin definition.
#define BOARD_SD_MCI1_PIN_CD     BOARD_SD_PIN_CD

/// PHY address
#define BOARD_EMAC_PHY_ADDR        31
/// PHY component
#define BOARD_EMAC_PHY_COMP_LAN8700 1
/// Board EMAC work mode - RMII/MII ( 1 / 0 )
#define BOARD_EMAC_MODE_RMII 1       
/// Board EMAC Power Up control pin
#define BOARD_EMAC_PIN_PWRDN { (1<<31), AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_OUTPUT_1, PIO_DEFAULT}
/// The PIN list of PIO for EMAC
#define BOARD_EMAC_PINS     {0x7FE00000, AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}, \
                            {0x0FF00000, AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_PERIPH_B, PIO_DEFAULT}
#define BOARD_EMAC_PIN_RXDV {(1<<22), AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_EMAC_PIN_COL  {(1<<26), AT91C_BASE_PIOC, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
#define BOARD_EMAC_RESET    {(1<<9),  AT91C_BASE_PIOB, AT91C_ID_PIOABCD, PIO_OUTPUT_1, PIO_DEFAULT}
/// The PIN Configure list for EMAC on power up reset (MII)
#define BOARD_EMAC_RST_PINS BOARD_EMAC_PIN_RXDV, BOARD_EMAC_PIN_COL
/// The runtime pin configure list for EMAC
#define BOARD_EMAC_RUN_PINS BOARD_EMAC_PINS

/// Base address of SPI peripheral to which the DAC is connected.
#define BOARD_AT73C213_SPI          AT91C_BASE_SPI0
/// Peripheral ID of the SPI connected to the DAC.
#define BOARD_AT73C213_SPI_ID       AT91C_ID_SPI0
/// Chip select value for accessing the DAC with the SPI.
#define BOARD_AT73C213_SPI_NPCS     2
/// Pins to configure for the SPI interface.
#define BOARD_AT73C213_SPI_PINS     PINS_SPI0, PIN_SPI0_NPCS2
/// SSC peripheral to which the DAC is connected.
#define BOARD_AT73C213_SSC          AT91C_BASE_SSC0
/// Peripheral ID of the SSC connected to the DAC.
#define BOARD_AT73C213_SSC_ID       AT91C_ID_SSC0
/// Pins to configure for the SSC interface.
#define BOARD_AT73C213_SSC_PINS     PINS_SSC_TX
/// PCK pin connected to the DAC MCK pin
#define BOARD_AT73C213_MCK          PIN_PCK2

/// Base address of SPI peripheral connected to the AT98 secure chip
#define BOARD_AT98SC_SPI_BASE         AT91C_BASE_SPI1
/// Identifier of SPI peripheral connected to the AT98 secure chip
#define BOARD_AT98SC_SPI_ID           AT91C_ID_SPI1
/// Pins of the SPI peripheral connected to the AT98 secure chip
#define BOARD_AT98SC_SPI_PINS         PINS_SPI1
/// Chip select connected to the AT98 secure chip
#define BOARD_AT98SC_NPCS             0
/// Chip select pin connected to the AT98 secure chip
#define BOARD_AT98SC_NPCS_PIN         PIN_SPI1_NPCS0

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-STK - Memories"
/// This page lists definitions related to external on-board memories.
/// 
/// !SDRAM
/// - BOARD_SDRAM_SIZE
/// - PIN_SDRAM
/// - BOARD_SDRAM_BUSWIDTH
///
/// !Nandflash
/// - PINS_NANDFLASH
/// - BOARD_NF_CE_PIN
/// - BOARD_NF_RB_PIN
/// - BOARD_NF_COMMAND_ADDR
/// - BOARD_NF_ADDRESS_ADDR
/// - BOARD_NF_DATA_ADDR

/// Board SDRAM size
#define BOARD_SDRAM_SIZE        (64*1024*1024)  // 64 MB
/// List of all SDRAM pins definitions.
#define PINS_SDRAM              {0xFFFF0000, AT91C_BASE_PIOD, AT91C_ID_PIOABCD, PIO_PERIPH_A, PIO_DEFAULT}
/// SDRAM bus width.
#define BOARD_SDRAM_BUSWIDTH    32

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

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Library naming workaround
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91CAP9-STK- Individual chip definition"
/// This page lists the definitions related to different chip's definition
/// located in the board.h file for the AT91CAP9-STK.

/// Twi eeprom
#define BOARD_ID_TWI_EEPROM         AT91C_ID_TWI
#define BOARD_BASE_TWI_EEPROM       AT91C_BASE_TWI
#define BOARD_PINS_TWI_EEPROM       PINS_TWI
//------------------------------------------------------------------------------


#endif //#ifndef BOARD_H

