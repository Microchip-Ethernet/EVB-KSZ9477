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
/// Definition and functions for using AT91SAM3UE-related features, such
/// has PIO pins, memories, etc.
///
/// !Usage
/// -# The code for booting the board is provided by board_cstartup_xxx.c and
///    board_lowlevel.c.
/// -# For using board PIOs, board characteristics (clock, etc.) and external
///    components, see board.h.
/// -# For manipulating memories (NandFlash, PSRAM, etc.), see board_memories.h.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \unit
/// !Purpose
///
/// Definition of AT91SAM3UE-EK characteristics, AT91SAM3UE-dependant PIOs and
/// external components interfacing.
///
/// !Usage
/// -# For operating frequency information, see "SAM3UE-EK - Operating frequencies".
/// -# For using portable PIO definitions, see "SAM3UE-EK - PIO definitions".
/// -# Several USB definitions are included here (see "SAM3UE-EK - USB device").
//------------------------------------------------------------------------------

#ifndef BOARD_H
#define BOARD_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#if defined(at91sam3u4)
    #include "at91sam3u4/chip.h"
    #include "at91sam3u4/AT91SAM3U4.h"
#elif defined(at91sam3u2)
    #include "at91sam3u2/chip.h"
    #include "at91sam3u2/AT91SAM3U2.h"
#elif defined(at91sam3u1)
    #include "at91sam3u1/chip.h"
    #include "at91sam3u1/AT91SAM3U1.h"
#else
    #error Board does not support the specified chip.
#endif

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM3UE-EK - Board Description"
/// This page lists several definition related to the board description.
///
/// !Definitions
/// - BOARD_NAME

/// Name of the board.
#define BOARD_NAME "AT91SAM3U-EK"
/// Board definition.
#define at91sam3uek
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM3UE-EK - Operating frequencies"
/// This page lists several definition related to the board operating frequency
/// (when using the initialization done by board_lowlevel.c).
///
/// !Definitions
/// - BOARD_MAINOSC
/// - BOARD_MCK

/// Frequency of the board main oscillator.
#define BOARD_MAINOSC           12000000

/// Master clock frequency (when using board_lowlevel.c).
#define BOARD_MCK               48000000

//------------------------------------------------------------------------------
// ADC
//------------------------------------------------------------------------------
/// ADC clock frequency, at 10-bit resolution (in Hz)
#define ADC_MAX_CK_10BIT         5000000
/// Startup time max, return from Idle mode (in µs)
#define ADC_STARTUP_TIME_MAX       15
/// Track and hold Acquisition Time min (in ns)
#define ADC_TRACK_HOLD_TIME_MIN  1200

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM3UE-EK - USB device"
///
/// !Constants
/// - BOARD_USB_BMATTRIBUTES

/// USB attributes configuration descriptor (bus or self powered, remote wakeup)
#define BOARD_USB_BMATTRIBUTES              USBConfigurationDescriptor_SELFPOWERED_RWAKEUP
//#define BOARD_USB_BMATTRIBUTES            USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM3UE-EK - PIO definitions"
/// This pages lists all the pio definitions contained in board.h. The constants
/// are named using the following convention: PIN_* for a constant which defines
/// a single Pin instance (but may include several PIOs sharing the same
/// controller), and PINS_* for a list of Pin instances.
///
/// !ADC
/// - PIN_ADC0_AD0
/// - PIN_ADC0_AD1
/// - PIN_ADC0_AD2
/// - PIN_ADC0_AD3
/// - PIN_ADC0_AD4
/// - PIN_ADC0_AD5
/// - PIN_ADC0_AD6
/// - PIN_ADC0_AD7
/// - PINS_ADC
///
/// !DBGU
/// - PINS_DBGU
///
/// !EBI
/// - PIN_EBI_DATA_BUS
/// - PIN_EBI_NCS0
/// - PIN_EBI_NRD
/// - PIN_EBI_NWE
/// - PIN_EBI_PSRAM_ADDR_BUS
/// - PIN_EBI_PSRAM_NBS
/// - PIN_EBI_A1
/// - PIN_EBI_NCS2
/// - PIN_EBI_LCD_RS
///
/// !LEDs
/// - PIN_LED_0
/// - PIN_LED_1
/// - PIN_LED_2
/// - PINS_LEDS
///
/// !MCI
/// - PINS_MCI
/// - PIN_MCI_DAT0
/// - PIN_MCI_CD
///
/// !Push buttons
/// - PIN_PUSHBUTTON_1
/// - PIN_PUSHBUTTON_2
/// - PINS_PUSHBUTTONS
/// - PUSHBUTTON_BP1
/// - PUSHBUTTON_BP2
///
/// !PWMC
/// - PIN_PWMC_PWMH0
/// - PIN_PWMC_PWML0
/// - PIN_PWMC_PWMH1
/// - PIN_PWMC_PWML1
/// - PIN_PWMC_PWMH2
/// - PIN_PWMC_PWML2
/// - PIN_PWM_LED0
/// - PIN_PWM_LED1
/// - PIN_PWM_LED2
/// - CHANNEL_PWM_LED0
/// - CHANNEL_PWM_LED1
/// - CHANNEL_PWM_LED2
///
/// !SPI0
/// - PIN_SPI0_MISO
/// - PIN_SPI0_MOSI
/// - PIN_SPI0_SPCK
/// - PIN_SPI0_NPCS2_PC14
/// - PINS_SPI0
///
/// !SPI1
/// - PIN_SPI1_MISO
/// - PIN_SPI1_MOSI
/// - PIN_SPI1_SPCK
/// - PINS_SPI1
/// - PIN_SPI1_NPCS3
///
/// ! SSC
/// - PIN_SSC_TD
/// - PIN_SSC_TK
/// - PIN_SSC_TF
/// - PINS_SSC_CODEC
///
/// ! PCK0
/// - PIN_PCK0
///
/// !TWI
/// - TWI_V3XX
/// - PIN_TWI_TWD0
/// - PIN_TWI_TWCK0
/// - PINS_TWI0
/// - PIN_TWI_TWD1
/// - PIN_TWI_TWCK1
/// - PINS_TWI1
///
/// !USART0
/// - PIN_USART0_RXD
/// - PIN_USART0_TXD
/// - PIN_USART0_CTS
/// - PIN_USART0_RTS
/// - PIN_USART0_SCK
///
/// !USART1
/// - PIN_USART1_RXD
/// - PIN_USART1_TXD
/// - PIN_USART1_CTS
/// - PIN_USART1_RTS
/// - PIN_USART1_SCK
///
/// !USB
/// - PIN_USB_VBUS
///
/// ADC_AD0 pin definition.
#define PIN_ADC0_AD0 {1 << 21, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD1 pin definition.
#define PIN_ADC0_AD1 {1 << 30, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD2 pin definition.
#define PIN_ADC0_AD2 {1 << 3, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD3 pin definition.
#define PIN_ADC0_AD3 {1 << 4, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD4 pin definition.
#define PIN_ADC0_AD4 {1 << 15, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD5 pin definition.
#define PIN_ADC0_AD5 {1 << 16, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD6 pin definition.
#define PIN_ADC0_AD6 {1 << 17, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD7 pin definition.
#define PIN_ADC0_AD7 {1 << 18, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_DEFAULT}

/// Pins ADC
#define PINS_ADC PIN_ADC0_AD0, PIN_ADC0_AD1, PIN_ADC0_AD2, PIN_ADC0_AD3, PIN_ADC0_AD4, PIN_ADC0_AD5, PIN_ADC0_AD6, PIN_ADC0_AD7

/// DBGU pins (DTXD and DRXD) definitions, PA11,12.
#define PINS_DBGU  {0x00001800, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// EBI
#define PIN_EBI_DATA_BUS            {0xfe01fe00, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}, \
                                        {1 << 6, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_PULLUP}
#define PIN_EBI_NCS0                {1 << 20, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_EBI_NRD                 {1 << 19, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_EBI_NWE                 {1 << 23, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_EBI_PSRAM_ADDR_BUS      {0x3f00fff, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_EBI_PSRAM_NBS           {1 << 7, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_PULLUP}, \
                                        {1 << 15, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_EBI_A1                  {1 << 8, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_PULLUP}

#define PIN_EBI_NCS2                {1 << 16, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_EBI_LCD_RS              {1 << 8, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_PULLUP}


/// LED #0 pin definition.
#define PIN_LED_0   {1 << 0, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
/// LED #1 pin definition.
#define PIN_LED_1   {1 << 1, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #2 pin definition.
#define PIN_LED_2   {1 << 2, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
/// List of all LEDs definitions.
#define PINS_LEDS   PIN_LED_0, PIN_LED_1, PIN_LED_2

///// MCI pins definition.
#define PINS_MCI  {0x1f8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}, \
                      {1 << 3, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// MCI pin DAT0 (busy)
#define PIN_MCI_DAT0 \
    {AT91C_PIO_PA5, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// MCI pin Card Detect
#define PIN_MCI_CD \
    {AT91C_PIO_PA25, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_PULLUP}

/// Push button #0 definition.
#define PIN_PUSHBUTTON_1    {1 << 18, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEGLITCH | PIO_PULLUP}
/// Push button #1 definition.
#define PIN_PUSHBUTTON_2    {1 << 19, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEGLITCH | PIO_PULLUP}
/// Push button #2 definition
/// List of all push button definitions.
#define PINS_PUSHBUTTONS    PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2
/// Push button #1 index.
#define PUSHBUTTON_BP1   0
/// Push button #2 index.
#define PUSHBUTTON_BP2   1
/// Simulated joystick LEFT index.
#define JOYSTICK_LEFT    0
/// Simulated joystick RIGHT index.
#define JOYSTICK_RIGHT   1

/// PWMC PWM0 pin definition.
#define PIN_PWMC_PWMH0  {1 << 0, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_PWMC_PWML0  {1 << 7, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/// PWMC PWM1 pin definition.
#define PIN_PWMC_PWMH1  {1 << 1, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_PWMC_PWML1  {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/// PWMC PWM2 pin definition.
#define PIN_PWMC_PWMH2  {1 << 2, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_PWMC_PWML2  {1 << 9, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/// PWM pin definition for LED0
#define PIN_PWM_LED0 PIN_PWMC_PWMH0
/// PWM pin definition for LED1
#define PIN_PWM_LED1 PIN_PWMC_PWMH1
/// PWM pin definition for LED2
#define PIN_PWM_LED2 PIN_PWMC_PWMH2
/// PWM channel for LED0
#define CHANNEL_PWM_LED0 0
/// PWM channel for LED1
#define CHANNEL_PWM_LED1 1
/// PWM channel for LED2
#define CHANNEL_PWM_LED2 2

/// SPI0 MISO pin definition.
#define PIN_SPI0_MISO  {1 << 13, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI0 MOSI pin definition.
#define PIN_SPI0_MOSI  {1 << 14, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI0 SPCK pin definition.
#define PIN_SPI0_SPCK  {1 << 15, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI0 chip select 0 pin definition.
#define PIN_SPI0_NPCS0_PA16  {1 <<  16, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SPI0_NPCS0  PIN_SPI0_NPCS0_PA16
/// SPI0 chip select 2 pin definition.
#define PIN_SPI0_NPCS2_PC14  {1 <<  14, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/// List of SPI0 pin definitions (MISO, MOSI & SPCK).
#define PINS_SPI0      PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK

/// SSC pins definition.
#define PIN_SSC_TD      {0x1 << 26, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SSC_TK      {0x1 << 28, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SSC_TF      {0x1 << 30, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PINS_SSC_CODEC       PIN_SSC_TD,  PIN_SSC_TK, PIN_SSC_TF

/// PCK0
#define PIN_PCK0        {0x1 << 21, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}

/// TWI pins definition.
#define TWI_V3XX
#define PIN_TWI_TWD0    {0x1 << 9, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_TWI_TWCK0    {0x1 << 10, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PINS_TWI0     PIN_TWI_TWD0, PIN_TWI_TWCK0
#define PIN_TWI_TWD1    {0x1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_TWI_TWCK1    {0x1 << 25, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PINS_TWI1     PIN_TWI_TWD1, PIN_TWI_TWCK1

/// USART0
#define PIN_USART0_RXD    {0x1 << 19, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD    {0x1 << 18, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS    {0x1 << 8, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS    {0x1 << 7, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_SCK    {0x1 << 17, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// USART1
#define PIN_USART1_RXD    {0x1 << 21, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_TXD    {0x1 << 20, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_CTS    {0x1 << 23, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART1_RTS    {0x1 << 22, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART1_SCK    {0x1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}

/// USB VBus monitoring pin definition.
#define PIN_USB_VBUS    {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM3UE-EK - External components"
/// This page lists the definitions related to external on-board components
/// located in the board.h file for the AT91SAM3UE-EK.
///
/// !LCD
/// - BOARD_LCD_HX8347
/// - BOARD_LCD_PINS
/// - BOARD_BACKLIGHT_PIN
/// - BOARD_LCD_BASE
/// - BOARD_LCD_RS
/// - BOARD_LCD_WIDTH
/// - BOARD_LCD_HEIGHT
///
/// !PSRAM
/// - BOARD_PSRAM_PINS
///
/// !SD Card
/// - BOARD_SD_MCI_BASE
/// - BOARD_SD_MCI_ID
/// - BOARD_SD_PINS
/// - BOARD_SD_DAT0
/// - BOARD_SD_SLOT
/// - BOARD_SD_PIN_CD
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

/// Indicates board has an HX8347 external component to manage LCD.
#define BOARD_LCD_HX8347
/// LCD pins definition.
#define BOARD_LCD_PINS              PIN_EBI_DATA_BUS, PIN_EBI_LCD_RS, PIN_EBI_NRD, PIN_EBI_NWE, \
                                        PIN_EBI_NCS2
/// Backlight pin definition.
#define BOARD_BACKLIGHT_PIN       {1 << 19, AT91C_BASE_PIOC, AT91C_ID_PIOC, \
                                      PIO_OUTPUT_0, PIO_DEFAULT}
/// Define HX8347 base address.
#define BOARD_LCD_BASE            0x62000000
/// Define HX8347 register select signal.
#define BOARD_LCD_RS              (1 << 1)
/// Display width in pixels.
#define BOARD_LCD_WIDTH             240
/// Display height in pixels.
#define BOARD_LCD_HEIGHT            320

/// PSRAM pins
#define BOARD_PSRAM_PINS            PIN_EBI_DATA_BUS, PIN_EBI_NCS0, PIN_EBI_NRD, PIN_EBI_NWE, \
                                        PIN_EBI_PSRAM_ADDR_BUS, PIN_EBI_PSRAM_NBS, PIN_EBI_A1

/// Base address of the MCI peripheral connected to the SD card.
#define BOARD_SD_MCI_BASE           AT91C_BASE_MCI0//AT91C_BASE_MCI
/// Peripheral identifier of the MCI connected to the SD card.
#define BOARD_SD_MCI_ID             AT91C_ID_MCI0 //AT91C_ID_MCI
/// MCI pins that shall be configured to access the SD card.
#define BOARD_SD_PINS               PINS_MCI
/// MCI Pin DAT0
#define BOARD_SD_DAT0               PIN_MCI_DAT0
/// MCI slot to which the SD card is connected to.
#define BOARD_SD_SLOT               MCI_SD_SLOTA
/// MCI Card Detect pin.
#define BOARD_SD_PIN_CD             PIN_MCI_CD

/// Indicates board has an ADS7843 external component to manage Touch Screen
#define BOARD_TSC_ADS7843
/// Touchscreen controller IRQ pin definition.
#define PIN_TCS_IRQ {AT91C_PIO_PA24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_PULLUP}
/// Touchscreen controller Busy pin definition.
#define PIN_TCS_BUSY {AT91C_PIO_PA2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_PULLUP}

/// Base address of SPI peripheral connected to the touchscreen controller.
#define BOARD_TSC_SPI_BASE         AT91C_BASE_SPI0
/// Identifier of SPI peripheral connected to the touchscreen controller.
#define BOARD_TSC_SPI_ID           AT91C_ID_SPI0
/// Pins of the SPI peripheral connected to the touchscreen controller.
#define BOARD_TSC_SPI_PINS         PINS_SPI0
/// Chip select connected to the touchscreen controller.
#define BOARD_TSC_NPCS             2
/// Chip select pin connected to the touchscreen controller.
#define BOARD_TSC_NPCS_PIN         PIN_SPI0_NPCS2_PC14

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM3UE-EK - Memories"
/// This page lists definitions related to internal & external on-board memories.
///
/// !Internal SRAM
/// - AT91C_ISRAM
/// - AT91C_ISRAM_SIZE

/// !Embedded Flash
/// - AT91C_IFLASH
/// - AT91C_IFLASH_SIZE
/// - AT91C_IFLASH_PAGE_SIZE
/// - AT91C_IFLASH_NB_OF_PAGES
/// - AT91C_IFLASH_LOCK_REGION_SIZE
/// - AT91C_IFLASH_NB_OF_LOCK_BITS
///
/// - AT91C_BASE_EFC
///
/// !PSRAM
/// - BOARD_EBI_PSRAM
/// - BOARD_PSRAM_SIZE

/// Internal SRAM address
#define AT91C_ISRAM                     AT91C_IRAM
#define AT91C_ISRAM_SIZE                AT91C_IRAM_SIZE

#define AT91C_IFLASH                    AT91C_IFLASH0
#define AT91C_IFLASH_SIZE               AT91C_IFLASH0_SIZE
#define AT91C_IFLASH_PAGE_SIZE          AT91C_IFLASH0_PAGE_SIZE
#define AT91C_IFLASH_LOCK_REGION_SIZE   AT91C_IFLASH0_LOCK_REGION_SIZE
#define AT91C_IFLASH_NB_OF_PAGES        AT91C_IFLASH0_NB_OF_PAGES
#define AT91C_IFLASH_NB_OF_LOCK_BITS    AT91C_IFLASH0_NB_OF_LOCK_BITS

/// Indicates chip has an EFC.
#define AT91C_BASE_EFC    AT91C_BASE_EFC0

/// PSRAM base address
#define BOARD_EBI_PSRAM                 0x60000000
#define BOARD_PSRAM_SIZE                (0x100000)  // PSRAM size 1MBytes
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM3UE-EK - Individual chip definition"
/// This page lists the definitions related to different chip's definition
/// located in the board.h file for the SAM3UE-EK.
///
/// !DBGU
/// - BOARD_DBGU_ID
///
/// !DMA
/// - BOARD_MCI_DMA_CHANNEL
/// - BOARD_LCD_DMA_CHANNEL
/// - BOARD_SSC_DMA_CHANNEL
/// - BOARD_NAND_DMA_CHANNEL
///
/// - DMA_HW_SRC_REQ_ID_MCI0
/// - DMA_HW_DEST_REQ_ID_MCI0
/// - DMA_HW_SRC_REQ_ID_MCI1
/// - DMA_HW_DEST_REQ_ID_MCI1
///
/// - BOARD_SD_DMA_HW_SRC_REQ_ID
/// - BOARD_SD_DMA_HW_DEST_REQ_ID
/// - BOARD_SSC_DMA_HW_SRC_REQ_ID
/// - BOARD_SSC_DMA_HW_DEST_REQ_ID
///
/// !RTC
/// - BOARD_RTC_ID
///
/// !Twi eeprom
/// -BOARD_ID_TWI_EEPROM
/// -BOARD_BASE_TWI_EEPROM
/// -BOARD_PINS_TWI_EEPROM
///
/// !USART
/// -BOARD_PIN_USART_RXD
/// -BOARD_PIN_USART_TXD
/// -BOARD_PIN_USART_CTS
/// -BOARD_PIN_USART_RTS
/// -BOARD_USART_BASE
/// -BOARD_ID_USART
///

/// DBGU
#define BOARD_DBGU_ID               AT91C_ID_DBGU

/// Dma channel number
#define BOARD_MCI_DMA_CHANNEL                         0
#define BOARD_LCD_DMA_CHANNEL                         1
#define BOARD_SSC_DMA_CHANNEL                         2
#define BOARD_NAND_DMA_CHANNEL                        3
/// MCI0 DMA hardware handshaking ID
#define DMA_HW_SRC_REQ_ID_MCI0      AT91C_HDMA_SRC_PER_0
#define DMA_HW_DEST_REQ_ID_MCI0     AT91C_HDMA_DST_PER_0
/// MCI1 DMA hardware handshaking ID
#define DMA_HW_SRC_REQ_ID_MCI1      AT91C_HDMA_SRC_PER_13
#define DMA_HW_DEST_REQ_ID_MCI1     AT91C_HDMA_DST_PER_13
/// SD DMA hardware handshaking ID
#define BOARD_SD_DMA_HW_SRC_REQ_ID      DMA_HW_SRC_REQ_ID_MCI0
#define BOARD_SD_DMA_HW_DEST_REQ_ID     DMA_HW_DEST_REQ_ID_MCI0
/// SSC DMA hardware handshaking ID
#define BOARD_SSC_DMA_HW_SRC_REQ_ID      AT91C_HDMA_SRC_PER_3
#define BOARD_SSC_DMA_HW_DEST_REQ_ID     AT91C_HDMA_DST_PER_3

/// Rtc
#define BOARD_RTC_ID                AT91C_ID_RTC

/// Twi eeprom
#define BOARD_ID_TWI_EEPROM         AT91C_ID_TWI1
#define BOARD_BASE_TWI_EEPROM       AT91C_BASE_TWI1
#define BOARD_PINS_TWI_EEPROM       PINS_TWI1

/// USART
#define BOARD_PIN_USART_RXD        PIN_USART1_RXD
#define BOARD_PIN_USART_TXD        PIN_USART1_TXD
#define BOARD_PIN_USART_CTS        PIN_USART1_CTS
#define BOARD_PIN_USART_RTS        PIN_USART1_RTS
#define BOARD_USART_BASE           AT91C_BASE_US1
#define BOARD_ID_USART             AT91C_ID_US1

/// Interrupt source
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  AT91SAM3U4 specific Interrupt Numbers *********************************************************/
 IROn_SUPC                = AT91C_ID_SUPC , // SUPPLY CONTROLLER
 IROn_RSTC                = AT91C_ID_RSTC , // RESET CONTROLLER
 IROn_RTC                 = AT91C_ID_RTC  , // REAL TIME CLOCK
 IROn_RTT                 = AT91C_ID_RTT  , // REAL TIME TIMER
 IROn_WDG                 = AT91C_ID_WDG  , // WATCHDOG TIMER
 IROn_PMC                 = AT91C_ID_PMC  , // PMC
 IROn_EFC0                = AT91C_ID_EFC0 , // EFC0
 IROn_EFC1                = AT91C_ID_EFC1 , // EFC1
 IROn_DBGU                = AT91C_ID_DBGU , // DBGU
 IROn_HSMC4               = AT91C_ID_HSMC4, // HSMC4
 IROn_PIOA                = AT91C_ID_PIOA , // Parallel IO Controller A
 IROn_PIOB                = AT91C_ID_PIOB , // Parallel IO Controller B
 IROn_PIOC                = AT91C_ID_PIOC , // Parallel IO Controller C
 IROn_US0                 = AT91C_ID_US0  , // USART 0
 IROn_US1                 = AT91C_ID_US1  , // USART 1
 IROn_US2                 = AT91C_ID_US2  , // USART 2
 IROn_US3                 = AT91C_ID_US3  , // USART 3
 IROn_MCI0                = AT91C_ID_MCI0 , // Multimedia Card Interface
 IROn_TWI0                = AT91C_ID_TWI0 , // TWI 0
 IROn_TWI1                = AT91C_ID_TWI1 , // TWI 1
 IROn_SPI0                = AT91C_ID_SPI0 , // Serial Peripheral Interface
 IROn_SSC0                = AT91C_ID_SSC0 , // Serial Synchronous Controller 0
 IROn_TC0                 = AT91C_ID_TC0  , // Timer Counter 0
 IROn_TC1                 = AT91C_ID_TC1  , // Timer Counter 1
 IROn_TC2                 = AT91C_ID_TC2  , // Timer Counter 2
 IROn_PWMC                = AT91C_ID_PWMC , // Pulse Width Modulation Controller
 IROn_ADCC0               = AT91C_ID_ADC12B, // ADC controller0
 IROn_ADCC1               = AT91C_ID_ADC, // ADC controller1
 IROn_HDMA                = AT91C_ID_HDMA , // HDMA
 IROn_UDPHS               = AT91C_ID_UDPHS // USB Device High Speed
} IRQn_Type;  

//------------------------------------------------------------------------------

/// Nandflash
#define PIN_EBI_NANDOE          {1 << 17, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_EBI_NANDWE          {1 << 18, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_EBI_NANDCLE         {1 << 22, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}
#define PIN_EBI_NANDALE         {1 << 21, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_PULLUP}

#if defined(CHIP_NAND_CTRL)
/// Nandflash chip enable pin definition.
#define BOARD_NF_CE_PIN         {1 << 12, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}

/// Nandflash controller peripheral pins definition.
#define PINS_NANDFLASH          BOARD_NF_CE_PIN, PIN_EBI_NANDOE, PIN_EBI_NANDWE,\
                                PIN_EBI_NANDCLE, PIN_EBI_NANDALE, PIN_EBI_DATA_BUS
                                
/// Address for transferring command bytes to the nandflash.
#define BOARD_NF_COMMAND_ADDR   0x60000000
/// Address for transferring address bytes to the nandflash.
#define BOARD_NF_ADDRESS_ADDR   0x61200000
/// Address for transferring data bytes to the nandflash.
#define BOARD_NF_DATA_ADDR      0x61000000

#else
/// Nandflash controller peripheral pins definition.
#define PINS_NANDFLASH          PIN_EBI_DATA_BUS, BOARD_NF_CE_PIN, PIN_EBI_NANDOE, PIN_EBI_NANDWE,\
                                PIN_EBI_NANDCLE, PIN_EBI_NANDALE
/// Nandflash chip enable pin definition.
#define BOARD_NF_CE_PIN         {1 << 12, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
/// Address for transferring command bytes to the nandflash.
#define BOARD_NF_COMMAND_ADDR   0x61400000
/// Address for transferring address bytes to the nandflash.
#define BOARD_NF_ADDRESS_ADDR   0x61200000
/// Address for transferring data bytes to the nandflash.
#define BOARD_NF_DATA_ADDR      0x61000000

#endif

#endif //#ifndef BOARD_H

