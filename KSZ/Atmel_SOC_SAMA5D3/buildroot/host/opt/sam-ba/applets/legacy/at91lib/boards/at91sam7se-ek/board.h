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
/// Definition and functions for using AT91SAM7SE-related features, such
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
/// Definition of AT91SAM7SE-EK characteristics, AT91SAM7SE-dependant PIOs and
/// external components interfacing.
/// 
/// !Usage
/// -# For operating frequency information, see "SAM7SE-EK - Operating frequencies".
/// -# For using portable PIO definitions, see "SAM7SE-EK - PIO definitions".
/// -# Several USB definitions are included here (see "SAM7SE-EK - USB device").
/// -# For external components definitions, see "SAM7SE-EK - External components".
/// -# For memory-related definitions, see "SAM7SE-EK - Memories".
//------------------------------------------------------------------------------

#ifndef BOARD_H 
#define BOARD_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#if defined(at91sam7se32)
    #include "at91sam7se32/chip.h"
    #include "at91sam7se32/AT91SAM7SE32.h"
#elif defined(at91sam7se256)
    #include "at91sam7se256/chip.h"
    #include "at91sam7se256/AT91SAM7SE256.h"
#elif defined(at91sam7se512)
    #include "at91sam7se512/chip.h"
    #include "at91sam7se512/AT91SAM7SE512.h"
#else
    #error Board does not support the specified chip.
#endif

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM7SE-EK - Board Description"
/// This page lists several definition related to the board description
///
/// !Definitions
/// - BOARD_NAME

/// Name of the board.
#define BOARD_NAME "AT91SAM7SE-EK"
/// Board definition.
#define at91sam7seek
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM7SE-EK - Operating frequencies"
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
// ADC
//------------------------------------------------------------------------------
/// ADC clock frequency, at 10-bit resolution (in Hz)
#define ADC_MAX_CK_10BIT         5000000
/// ADC clock frequency, at 8-bit resolution (in Hz)
#define ADC_MAX_CK_8BIT          8000000
/// Startup time max, return from Idle mode (in µs)
#define ADC_STARTUP_TIME_MAX       20
/// Track and hold Acquisition Time min (in ns)
#define ADC_TRACK_HOLD_TIME_MIN   600


//------------------------------------------------------------------------------
/// \page "SAM7SE-EK - USB device"
/// 
/// !Constants
/// - BOARD_USB_BMATTRIBUTES

/// USB attributes configuration descriptor (bus or self powered, remote wakeup)
#define BOARD_USB_BMATTRIBUTES USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM7SE-EK - PIO definitions"
/// This pages lists all the pio definitions contained in board.h. The constants
/// are named using the following convention: PIN_* for a constant which defines
/// a single Pin instance (but may include several PIOs sharing the same
/// controller), and PINS_* for a list of Pin instances.
///
/// !Clocks
/// - PIN_PCK2
/// 
/// !DBGU
/// - PINS_DBGU
/// 
/// !LEDs
/// - PIN_LED_0
/// - PIN_LED_1
/// - PIN_LED_2
/// - PINS_LEDS
/// - LED_DS1
/// - LED_DS2
/// - LED_POWER
/// 
/// !Push buttons
/// - PIN_PUSHBUTTON_1
/// - PIN_PUSHBUTTON_2
/// - PINS_PUSHBUTTONS
/// - PUSHBUTTON_BP1
/// - PUSHBUTTON_BP2
///
/// !Joystick buttons
/// - PIN_JOYSTICK_UP
/// - PIN_JOYSTICK_DOWN
/// - PIN_JOYSTICK_LEFT
/// - PIN_JOYSTICK_RIGHT
/// - PIN_JOYSTICK_LCLIC, PIN_JOYSTICK_PUSH
/// - PIN_JOYSTICK_RCLIC
/// - PINS_JOYSTICK_MOVE, PINS_JOYSTICK_CLIC, PINS_JOYSTICK
/// - JOYSTICK_UP
/// - JOYSTICK_DOWN
/// - JOYSTICK_LEFT
/// - JOYSTICK_RIGHT
/// - JOYSTICK_LCLIC, JOYSTICK_PUSH
/// - JOYSTICK_RCLIC
/// 
/// !USART0
/// - PIN_USART0_RXD
/// - PIN_USART0_TXD
/// - PIN_USART0_SCK
/// 
/// !SPI
/// - PIN_SPI_MISO
/// - PIN_SPI_MOSI
/// - PIN_SPI_SPCK
/// - PINS_SPI
/// - PIN_SPI_NPCS0
/// - PIN_SPI_NPCS1
/// 
/// !SSC
/// - PINS_SSC_TX
///
/// !PWMC
/// - PIN_PWMC_PWM0
/// - PIN_PWMC_PWM1
/// - PIN_PWMC_PWM2
///
/// !ADC
/// - PIN_ADC_ADC0
/// - PIN_ADC_ADC1
/// - PIN_ADC_ADC2
/// - PIN_ADC_ADC3
/// - PINS_ADC
///
/// !TWI
/// - PINS_TWI
/// 
/// !USB
/// - PIN_USB_VBUS

/// Programmable clock output 2 pin definition.
#define PIN_PCK2    {1 << 31, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

/// DBGU pins (DTXD and DRXD) definitions.
#define PINS_DBGU  {0x00000600, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// LED #0 pin definition.
#define PIN_LED_0  {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
/// LED #1 pin definition.
#define PIN_LED_1  {1 << 1, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #2 pin definition.
#define PIN_LED_2  {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// List of all LEDs pin definitions.
#define PINS_LEDS  PIN_LED_0, PIN_LED_1, PIN_LED_2
/// DS1 LED index.
#define LED_DS1          1
/// DS2 LED index.
#define LED_DS2          2
/// Power LED index.
#define LED_POWER        0 

/// Push button #1 definition.
#define PIN_PUSHBUTTON_1  {1 << 25, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Push button #2 definition.
#define PIN_PUSHBUTTON_2  {1 << 22, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// List of all push button definitions.
#define PINS_PUSHBUTTONS  PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2
/// Push button #1 index.
#define PUSHBUTTON_BP1   0
/// Push button #2 index.
#define PUSHBUTTON_BP2   1

// Joystick definition.
/// Joystick UP.
#define PIN_JOYSTICK_UP    {1 << 23, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick DOWN.
#define PIN_JOYSTICK_DOWN  {1 << 24, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick LEFT.
#define PIN_JOYSTICK_LEFT  {1 << 27, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick RIGHT.
#define PIN_JOYSTICK_RIGHT {1 << 26, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick LEFT clic.
#define PIN_JOYSTICK_LCLIC {1 << 25, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// Joystick PUSH button.
#define PIN_JOYSTICK_PUSH  PIN_JOYSTICK_LCLIC
/// Joystick RIGHT clic push button.
#define PIN_JOYSTICK_RCLIC {1 << 22, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP}
/// List of all Joystick click definitions
#define PINS_JOYSTICK_CLIC   PIN_JOYSTICK_RCLIC, PIN_JOYSTICK_LCLIC
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
/// Joystick RIGHT CLIC index.
#define JOYSTICK_RCLIC      5

/// USART0 TXD pin definition.
#define PIN_USART0_RXD  {1 << 5, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 RXD pin definition.
#define PIN_USART0_TXD  {1 << 6, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 RTS pin definition
#define PIN_USART0_RTS  {1 << 7, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 CTS pin definition
#define PIN_USART0_CTS  {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 SCK pin definition
#define PIN_USART0_SCK  {1 << 2, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}


/// SPI MISO pin definition.
#define PIN_SPI_MISO   {1 << 12, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// SPI MOSI pin definition.
#define PIN_SPI_MOSI   {1 << 13, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// SPI SPCK pin definition.
#define PIN_SPI_SPCK   {1 << 14, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// List of SPI pin definitions (MISO, MOSI & SPCK).
#define PINS_SPI       PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_SPCK
/// SPI chip select 0 pin definition.
#define PIN_SPI_NPCS0  {1 << 11, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// SPI chip select 1 pin definition.
#define PIN_SPI_NPCS1  {1 << 31, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// SPI chip select 2 pin definition.
#define PIN_SPI_NPCS2  {1 << 10, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}
/// SPI chip select 3 pin definition.
#define PIN_SPI_NPCS3  {1 <<  3, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}

/// SSC transmitter pins definition.
#define PINS_SSC_TX { (1 << 15) | (1 << 16) | (1 << 17), \
                      AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// PWMC PWM0 pin definition.
#define PIN_PWMC_PWM0  {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// PWMC PWM0 pin definition.
#define PIN_PWMC_PWM1  {1 << 1, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// PWMC PWM0 pin definition.
#define PIN_PWMC_PWM2  {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// PWM pin definition for LED0
#define PIN_PWM_LED0 PIN_PWMC_PWM1
/// PWM pin definition for LED1
#define PIN_PWM_LED1 PIN_PWMC_PWM2
/// PWM channel for LED0
#define CHANNEL_PWM_LED0 1
/// PWM channel for LED1
#define CHANNEL_PWM_LED1 2

/// ADC_AD0 pin definition.
#define PIN_ADC_ADC0 {1 << 17, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD1 pin definition.
#define PIN_ADC_ADC1 {1 << 18, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD2 pin definition.
#define PIN_ADC_ADC2 {1 << 19, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD3 pin definition.
#define PIN_ADC_ADC3 {1 << 20, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// Pins ADC
#define PINS_ADC PIN_ADC_ADC0, PIN_ADC_ADC1, PIN_ADC_ADC2, PIN_ADC_ADC3

/// TWI pins definition.
#define PINS_TWI  {0x00000018, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_OPENDRAIN}

/// USB VBus monitoring pin definition.
#define PIN_USB_VBUS    {1 << 19, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_DEFAULT}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM7SE-EK - External components"
/// This page lists the definitions related to external on-board components
/// located in the board.h file for the AT91SAM7SE-EK.
/// 
/// !AT45 Dataflash (serial onboard DataFlash)
/// - BOARD_AT45_A_SPI_BASE
/// - BOARD_AT45_A_SPI_ID
/// - BOARD_AT45_A_SPI_PINS
/// - BOARD_AT45_A_SPI
/// - BOARD_AT45_A_NPCS
/// - BOARD_AT45_A_NPCS_PIN
///
/// !AT26 Serialflash 
/// - BOARD_AT26_A_SPI_BASE
/// - BOARD_AT26_A_SPI_ID
/// - BOARD_AT26_A_SPI_PINS
/// - BOARD_AT26_A_SPI
/// - BOARD_AT26_A_NPCS
/// - BOARD_AT26_A_NPCS_PIN
///
/// !AT73C213
/// - BOARD_AT73C213_SPI
/// - BOARD_AT73C213_SPI_ID
/// - BOARD_AT73C213_NPCS
/// - BOARD_AT73C213_SSC
/// - BOARD_AT73C213_SSC_ID
/// - BOARD_AT73C213_MCK
///
/// !SD Card SPI
/// - BOARD_SD_SPI_BASE
/// - BOARD_SD_SPI_ID  
/// - BOARD_SD_SPI_PINS
/// - BOARD_SD_NPCS    

/// Base address of SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_BASE         AT91C_BASE_SPI
/// Identifier of SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_ID           AT91C_ID_SPI
/// Pins of the SPI peripheral connected to the dataflash.
#define BOARD_AT45_A_SPI_PINS         PINS_SPI
/// Dataflash SPI peripheral index.
#define BOARD_AT45_A_SPI              0
/// Chip select connected to the dataflash.
#define BOARD_AT45_A_NPCS             0
/// Chip select pin connected to the dataflash.
#define BOARD_AT45_A_NPCS_PIN         PIN_SPI_NPCS0

/// Base address of SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_BASE         AT91C_BASE_SPI
/// Identifier of SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_ID           AT91C_ID_SPI
/// Pins of the SPI peripheral connected to the serialflash.
#define BOARD_AT26_A_SPI_PINS         PINS_SPI
/// Serialflash SPI number.
#define BOARD_AT26_A_SPI              0
/// Chip select connected to the serialflash.
#define BOARD_AT26_A_NPCS             0
/// Chip select pin connected to the serialflash.
#define BOARD_AT26_A_NPCS_PIN         PIN_SPI_NPCS0

/// Base address of SPI peripheral to which the DAC is connected.
#define BOARD_AT73C213_SPI          AT91C_BASE_SPI
/// Peripheral ID of the SPI connected to the DAC.
#define BOARD_AT73C213_SPI_ID       AT91C_ID_SPI
/// Chip select value for accessing the DAC with the SPI.
#define BOARD_AT73C213_SPI_NPCS     1
/// Pins required by the SPI interface.
#define BOARD_AT73C213_SPI_PINS     PINS_SPI, PIN_SPI_NPCS1
/// SSC peripheral to which the DAC is connected.
#define BOARD_AT73C213_SSC          AT91C_BASE_SSC
/// Peripheral ID of the SSC connected to the DAC.
#define BOARD_AT73C213_SSC_ID       AT91C_ID_SSC
/// Pins required by the SSC interface.
#define BOARD_AT73C213_SSC_PINS     PINS_SSC_TX
/// PCK pin connected to the DAC MCK pin
#define BOARD_AT73C213_MCK          PIN_PCK2

/// Not define in our board, but customer can add this feature
/// Base address of the SPI peripheral connected to the SD card.
#define BOARD_SD_SPI_BASE   AT91C_BASE_SPI
/// Identifier of the SPI peripheral connected to the SD card.
#define BOARD_SD_SPI_ID     AT91C_ID_SPI
/// List of pins to configure to access the SD card
#define BOARD_SD_SPI_PINS   PINS_SPI, PIN_SPI_NPCS2
/// NPCS number
#define BOARD_SD_NPCS       2

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM7SE-EK - Memories"
/// This page lists definitions related to external on-board memories.
///
/// !SDRAM
/// - AT91C_EBI_SDRAM
/// - BOARD_SDRAM_SIZE
/// - PINS_SDRAM
/// - BOARD_SDRAM_BUSWIDTH
/// 
/// !Nandflash
/// - BOARD_NF_COMMAND_ADDR
/// - BOARD_NF_ADDRESS_ADDR
/// - BOARD_NF_DATA_ADDR
/// - BOARD_NF_CE_PIN
/// - BOARD_NF_RB_PIN
/// - PINS_NANDFLASH
///
/// !NorFlash
/// - BOARD_NORFLASH_ADDR


/// Base address of the SDRAM memory connected to the EBI.
#define AT91C_EBI_SDRAM    ((volatile unsigned char *) 0x20000000)
/// Board SDRAM size
#define BOARD_SDRAM_SIZE   (64*1024*1024)  // 64 MB
/// List of the pins used by the EBI to connect to the external SDRAM chip.
#define PINS_SDRAM  \
    {0x3F800000, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}, \
    {0x0003FFFF, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}, \
    {0x0000FFFF, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/// SDRAM bus width.
#define BOARD_SDRAM_BUSWIDTH 16

/// Nandflash controller peripheral pins definition.
#define PINS_NANDFLASH          {0x001800FF, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}, \
                                {0x00060000, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}, \
                                BOARD_NF_CE_PIN
/// Nandflash chip enable pin definition.
#define BOARD_NF_CE_PIN         {1 << 18, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
/// Address for transferring command bytes to the nandflash.
#define BOARD_NF_COMMAND_ADDR   0x40400000
/// Address for transferring address bytes to the nandflash.
#define BOARD_NF_ADDRESS_ADDR   0x40200000
/// Address for transferring data bytes to the nandflash.
#define BOARD_NF_DATA_ADDR      0x40000000

/// NORFlash peripheral pins definition.
#define PINS_NORFLASH           {0xC0000000, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}, \
                                {0xFFFFFFFE, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT},\
                                {0x001FFFFF, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT},\
                                {0x00E00000, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/// Address for transferring command bytes to the norflash.
#define BOARD_NORFLASH_ADDR     0x10000000
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM7SE-EK - External components"
/// This page lists the definitions related to external on-board components
/// located in the board.h file for the SAM7SE-EK.
/// 
/// !ISO7816
/// - PIN_SMARTCARD_CONNECT
/// - PIN_ISO7816_RSTMC
/// - PINS_ISO7816

/// Smartcard detection pin
#define PIN_SMARTCARD_CONNECT   {1 << 5, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// PIN used for reset the smartcard
#define PIN_ISO7816_RSTMC       {1 << 7, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
/// Pins used for connect the smartcard
#define PINS_ISO7816            PIN_USART0_TXD, PIN_USART0_SCK, PIN_ISO7816_RSTMC
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM7SE-EK - Individual chip definition"
/// This page lists the definitions related to different chip's definition
/// located in the board.h file for the SAM7SE-EK.

/// Twi eeprom
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

