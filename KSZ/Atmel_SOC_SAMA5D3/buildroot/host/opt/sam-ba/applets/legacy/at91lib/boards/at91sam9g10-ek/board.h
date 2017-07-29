/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
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

//------------------------------------------------------------------------------
/// \dir
/// !Purpose
/// 
/// Definition and functions for using AT91SAM9G10-related features, such
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
/// Definition of AT91SAM9G10-EK characteristics, AT91SAM9G10-dependant PIOs and
/// external components interfacing.
/// 
/// !Usage
/// -# For operating frequency information, see "SAM9G10-EK - Operating frequencies".
/// -# For using portable PIO definitions, see "SAM9G10-EK - PIO definitions".
/// -# Several USB definitions are included here (see "SAM9G10-EK - USB device").
/// -# For external components definitions, see "SAM9G10-EK - External components".
/// -# For memory-related definitions, see "SAM9G10-EK - Memories".
//------------------------------------------------------------------------------

#ifndef BOARD_H 
#define BOARD_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#if defined(at91sam9g10)
    #include "at91sam9g10/chip.h"
    #include "at91sam9g10/AT91SAM9G10.h"
#else
    #error Board does not support the specified chip.
#endif

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9G10-EK - Board Description"
/// This page lists several definition related to the board description.
///
/// !Definitions
/// - BOARD_NAME

/// Name of the board.
#define BOARD_NAME              "AT91SAM9G10-EK"
/// Board definition.
#define at91sam9g10ek

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9G10-EK - Operating frequencies"
/// This page lists several definition related to the board operating frequency
/// (when using the initialization done by board_lowlevel.c).
/// 
/// !Definitions
/// - BOARD_MAINOSC
/// - BOARD_MCK

/// Frequency of the board main oscillator.
#define BOARD_MAINOSC           18432000

/// Master clock frequency (when using board_lowlevel.c).
#define BOARD_MCK               48000000
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9G10-EK - USB device"
/// 
/// !Constants
/// - BOARD_USB_BMATTRIBUTES

/// USB attributes configuration descriptor (bus or self powered, remote wakeup)
#define BOARD_USB_BMATTRIBUTES USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9G10-EK - PIO definitions"
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
/// - PIN_LED_2
/// - PINS_LEDS
/// - LED_POWER
/// - LED_DS1
/// - LED_DS2
/// 
/// !Push buttons
/// - PIN_PUSHBUTTON_1
/// - PIN_PUSHBUTTON_2
/// - PIN_PUSHBUTTON_3
/// - PIN_PUSHBUTTON_4
/// - PINS_PUSHBUTTONS
/// - PUSHBUTTON_BP1
/// - PUSHBUTTON_BP2
/// - PUSHBUTTON_BP3
/// - PUSHBUTTON_BP4
/// - JOYSTICK_LEFT
/// - JOYSTICK_RIGHT
/// 
/// !SPI0
/// - PIN_SPI0_MISO
/// - PIN_SPI0_MOSI
/// - PIN_SPI0_SPCK
/// - PINS_SPI0
/// - PIN_SPI0_NPCS0
/// - PIN_SPI0_NPCS2
/// - PIN_SPI0_NPCS3
/// 
/// !SSC
/// - PINS_SSC_TX
/// 
/// !USB
/// - PIN_USB_VBUS

/// List of all DBGU pin definitions.
#define PINS_DBGU  {(1<<9) | (1<<10), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// LED #0 pin definition.
#define PIN_LED_0   {1 << 23, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
/// LED #1 pin definition.
#define PIN_LED_1   {1 << 13, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #2 pin definition.
#define PIN_LED_2   {1 << 14, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// List of all LED pins definitions.
#define PINS_LEDS   PIN_LED_0, PIN_LED_1, PIN_LED_2
/// Power LED index.
#define LED_POWER   0
/// DS1 LED index.
#define LED_DS1     1
/// DS2 LED index.
#define LED_DS2     2

/// Push button #1 pin definition.
#define PIN_PUSHBUTTON_1  {1 << 27, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_PULLUP}
/// Push button #2 pin definition.
#define PIN_PUSHBUTTON_2  {1 << 26, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_PULLUP}
/// Push button #3 pin definition.
#define PIN_PUSHBUTTON_3  {1 << 25, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_PULLUP}
/// Push button #4 pin definition.
#define PIN_PUSHBUTTON_4  {1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_PULLUP}
/// List of all pushbutton pins definitions.
#define PINS_PUSHBUTTONS  PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2, PIN_PUSHBUTTON_3, PIN_PUSHBUTTON_4
/// Push button #1 index.
#define PUSHBUTTON_BP1   0
/// Push button #2 index.
#define PUSHBUTTON_BP2   1
/// Push button #3 index.
#define PUSHBUTTON_BP3   2
/// Push button #4 index.
#define PUSHBUTTON_BP4   3
/// Simulated joystick LEFT index.
#define JOYSTICK_LEFT    0
/// Simulated joystick RIGHT index.
#define JOYSTICK_RIGHT   1

/// SPI0 MISO pin definition.
#define PIN_SPI0_MISO  {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI0 MOSI pin definition.
#define PIN_SPI0_MOSI  {1 << 1, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// SPI0 SPCK pin definition.
#define PIN_SPI0_SPCK  {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// SPI0 chip select 0 pin definition.
#define PIN_SPI0_NPCS0 {1 << 3, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// SPI0 chip select 2 pin definition.
#define PIN_SPI0_NPCS2_PA5  {1 <<  5, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_SPI0_NPCS2_PA28 {1 << 28, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
/// SPI0 chip select 3 pin definition.
#define PIN_SPI0_NPCS3 {1 << 6, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// List of SPI0 pin definitions (MISO, MOSI & SPCK).
#define PINS_SPI0      PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK

/// SSC transmitter pins definition.
#define PINS_SSC_TX { (1 << 21) | (1 << 22) | (1 << 23), \
                      AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

/// USB VBus monitoring pin definition.
#define PIN_USB_VBUS  {1 << 29, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_DEFAULT}

/// MCI peripheral pins definition.
#define PINS_MCI {0x00000077, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}	

/// TWI pins definition.
#define TWI_V3XX
#define PINS_TWI {0x00000180, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// SD boot slot
#define BOARD_SD_BOOT_MCISLOT    0

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9G10-EK - External components"
/// This page lists the definitions related to external on-board components
/// located in the board.h file for the AT91SAM9G10-EK.
/// 
/// !AT45 Dataflash
/// - BOARD_AT45_A_SPI_BASE
/// - BOARD_AT45_A_SPI_ID
/// - BOARD_AT45_A_SPI_PINS
/// - BOARD_AT45_A_SPI
/// - BOARD_AT45_A_NPCS
/// - BOARD_AT45_A_NPCS_PIN
///
/// - BOARD_AT45_B_SPI_BASE
/// - BOARD_AT45_B_SPI_ID
/// - BOARD_AT45_B_SPI_PINS
/// - BOARD_AT45_B_SPI
/// - BOARD_AT45_B_NPCS
/// - BOARD_AT45_B_NPCS_PIN
///
/// !AT26 Serial Flash
/// - BOARD_AT26_A_SPI_BASE
/// - BOARD_AT26_A_SPI_ID
/// - BOARD_AT26_A_SPI_PINS
/// - BOARD_AT26_A_SPI
/// - BOARD_AT26_A_NPCS
/// - BOARD_AT26_A_NPCS_PIN

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
/// - BOARD_SD_PIN_WP
/// - BOARD_SD_SLOT
///
/// !SD Card SPI
/// - BOARD_SD_SPI_BASE 
/// - BOARD_SD_SPI_ID   
/// - BOARD_SD_SPI_PINS 
/// - BOARD_SD_NPCS     
///

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

/// Base address of SPI peripheral connected to the dataflash.
#define BOARD_AT45_B_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the dataflash.
#define BOARD_AT45_B_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the dataflash.
#define BOARD_AT45_B_SPI_PINS         PINS_SPI0
/// Dataflahs SPI number.
#define BOARD_AT45_B_SPI              0
/// Chip select connected to the dataflash.
#define BOARD_AT45_B_NPCS             3
/// Chip select pin connected to the dataflash.
#define BOARD_AT45_B_NPCS_PIN         PIN_SPI0_NPCS3

/// Base address of SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_PINS         PINS_SPI0
/// Serialflash SPI number.
#define BOARD_AT26_A_SPI              0
/// Chip select connected to the serialflash.
#define BOARD_AT26_A_NPCS             3
/// Chip select pin connected to the serialflash.
#define BOARD_AT26_A_NPCS_PIN         PIN_SPI0_NPCS3

/// LCD pins list.
#define PINS_LCD    \
    {0x001F9F9E, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}, \
    {0x1F800000, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}, \
    {1 << 12, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// Board is wired in BGR 565.
#define BOARD_LCD_BGR565
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
#define PIN_TCS_IRQ {AT91C_PIO_PC2, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_PULLUP}
/// Touchscreen controller Busy pin definition.
#define PIN_TCS_BUSY {AT91C_PIO_PA11, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}

/// Base address of SPI peripheral connected to the touchscreen controller.
#define BOARD_TSC_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the touchscreen controller.
#define BOARD_TSC_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the touchscreen controller.
#define BOARD_TSC_SPI_PINS         PINS_SPI0
/// Chip select connected to the touchscreen controller.
#define BOARD_TSC_NPCS             2
/// Chip select pin connected to the touchscreen controller.
#define BOARD_TSC_NPCS_PIN         PIN_SPI0_NPCS2_PA28

/// Base address of the MCI peripheral connected to the SD card.
#define BOARD_SD_MCI_BASE   AT91C_BASE_MCI
/// Identifier of the MCI peripheral connected to the SD card.
#define BOARD_SD_MCI_ID     AT91C_ID_MCI
/// List of pins to configure to access the SD card
#define BOARD_SD_PINS       PINS_MCI
/// MCI slot connected to the SD card.
#define BOARD_SD_SLOT       MCI_SD_SLOTA

/// Base address of the SPI peripheral connected to the SD card.
#define BOARD_SD_SPI_BASE   AT91C_BASE_SPI0
/// Identifier of the SPI peripheral connected to the SD card.
#define BOARD_SD_SPI_ID     AT91C_ID_SPI0
/// List of pins to configure to access the SD card
#define BOARD_SD_SPI_PINS   PINS_SPI0, PIN_SPI0_NPCS0
/// NPCS number
#define BOARD_SD_NPCS       0

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9G10-EK - Memories"
/// This page lists definitions related to external on-board memories.
/// 
/// !SDRAM
/// - BOARD_SDRAM_SIZE
/// - PIN_SDRAM
/// - BOARD_SDRAM_BUSWIDTH
/// 
/// !Nandflash
/// - PINS_NANDFLASH
/// - PIN_NF_OE
/// - PIN_NF_WE
/// - BOARD_NF_COMMAND_ADDR
/// - BOARD_NF_ADDRESS_ADDR
/// - BOARD_NF_DATA_ADDR
/// - BOARD_NF_CE_PIN
/// - BOARD_NF_RB_PIN
///
/// !NorFlash
/// - BOARD_NORFLASH_ADDR
/// - BOARD_NORFLASH_DFT_BUS_SIZE

/// Board SDRAM size
#define BOARD_SDRAM_SIZE       (64*1024*1024)  // 64 MB
/// List of all SDRAM pins definitions.
#define PINS_SDRAM             {0xFFFF0000, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/// SDRAM bus width.
#define BOARD_SDRAM_BUSWIDTH   32

/// Nandflash controller peripheral pins definition.
#define PINS_NANDFLASH         PIN_NF_OE, PIN_NF_WE, BOARD_NF_CE_PIN
/// Nandflash output enable pin definition.
#define PIN_NF_OE              {1 << 0, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/// Nandflash write enable pin definition
#define PIN_NF_WE              {1 << 1, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/// Nandflash chip enable pin definition.
#define BOARD_NF_CE_PIN        {1 << 14, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
/// Address for transferring command bytes to the nandflash.
#define BOARD_NF_COMMAND_ADDR  0x40200000
/// Address for transferring address bytes to the nandflash.
#define BOARD_NF_ADDRESS_ADDR  0x40400000
/// Address for transferring data bytes to the nandflash.
#define BOARD_NF_DATA_ADDR     0x40000000

/// Address for transferring command bytes to the norflash.
#define BOARD_NORFLASH_ADDR  0x10000000
/// Default NOR bus size after power up reset
#define BOARD_NORFLASH_DFT_BUS_SIZE 16
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9G10-EK - Individual chip definition"
/// This page lists the definitions related to different chip's definition
/// located in the board.h file for the SAM9G10-EK.

/// Twi eeprom
#define BOARD_ID_TWI_EEPROM         AT91C_ID_TWI
#define BOARD_BASE_TWI_EEPROM       AT91C_BASE_TWI
#define BOARD_PINS_TWI_EEPROM       PINS_TWI
//------------------------------------------------------------------------------

#endif //#ifndef BOARD_H

