/**
 * \file
 *
 * \brief Chip-specific system clock management functions
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 *    AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
#ifndef CHIP_SYSCLK_H_INCLUDED
#define CHIP_SYSCLK_H_INCLUDED

#include <board.h>
#include "interrupt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \weakgroup sysclk_group
 * @{
 */

//! \name System clock source
//@{
#define SYSCLK_SRC_RCSYS        0     //!< System RC oscillator
#define SYSCLK_SRC_OSC0         1     //!< Oscillator 0
#define SYSCLK_SRC_PLL0         2     //!< Phase Locked Loop 0
#define SYSCLK_SRC_DFLL         3     //!< Digital Frequency Locked Loop
#define SYSCLK_SRC_RC80M        4     //!< 80 MHz RC oscillator
#define SYSCLK_SRC_RCFAST       5     //!< 4-8-12 MHz RC oscillator
#define SYSCLK_SRC_RC1M         6     //!< 1 MHz RC oscillator

//! \name USB Clock Sources
//@{
#define USBCLK_SRC_OSC0         GENCLK_SRC_OSC0     //!< Use OSC0
#define USBCLK_SRC_PLL0         GENCLK_SRC_PLL0     //!< Use PLL0
#define USBCLK_SRC_DFLL         GENCLK_SRC_DFLL     //!< Use DFLL
#define USBCLK_SRC_GCLKIN0      GENCLK_SRC_GCLKIN0  //!< Use GCLKIN0
//@}

//@}

//! \name Clocks derived from the CPU clock
//@{
//! On-Chip Debug system
#define SYSCLK_OCD              1
//@}

//! \name Clocks derived from the HSB clock
//@{
//! PDCA memory interface
#define SYSCLK_PDCA_HSB         (PM_HSBMASK_PDCA)
//! USBC DMA and FIFO interface
#define SYSCLK_USBC_DATA        (PM_HSBMASK_USBC)
//! Flash data interface
#define SYSCLK_HFLASHC_DATA     (PM_HSBMASK_HFLASHC)
//! HSB<->PBA bridge
#define SYSCLK_PBA_BRIDGE       (PM_HSBMASK_HTOP0)
//! HSB<->PBB bridge
#define SYSCLK_PBB_BRIDGE       (PM_HSBMASK_HTOP1)
//! HSB<->PBC bridge
#define SYSCLK_PBC_BRIDGE       (PM_HSBMASK_HTOP2)
//! HSB<->PBD bridge
#define SYSCLK_PBD_BRIDGE       (PM_HSBMASK_HTOP3)
//! AESA Controller
#define SYSCLK_AESA_HSB         (PM_HSBMASK_AESA)
//! PTC Controller
#define SYSCLK_PTC_HSB          (PM_HSBMASK_PTC)
//@}

//! \name Clocks derived from the PBA clock
//@{
//! PDCA peripheral bus interface
//! IISC Controller
#define SYSCLK_IISC             (PM_PBAMASK_IISC)
//! SPI Controller
#define SYSCLK_SPI              (PM_PBAMASK_SPI)
//! Timer/Counter 0
#define SYSCLK_TC0              (PM_PBAMASK_TC0)
//! Timer/Counter 0
#define SYSCLK_TC1              (PM_PBAMASK_TC1)
//! TWI Master 0
#define SYSCLK_TWIM0            (PM_PBAMASK_TWIM0)
//! TWI Slave 0
#define SYSCLK_TWIS0            (PM_PBAMASK_TWIS0)
//! TWI Master 0
#define SYSCLK_TWIM1            (PM_PBAMASK_TWIM1)
//! TWI Slave 0
#define SYSCLK_TWIS1            (PM_PBAMASK_TWIS1)
//! USART 0
#define SYSCLK_USART0           (PM_PBAMASK_USART0)
//! USART 1
#define SYSCLK_USART1           (PM_PBAMASK_USART1)
//! USART 2
#define SYSCLK_USART2           (PM_PBAMASK_USART2)
//! USART 3
#define SYSCLK_USART3           (PM_PBAMASK_USART3)
//! A/D Converter
#define SYSCLK_ADCIFE           (PM_PBAMASK_ADCIFE)
//! D/A Converter
#define SYSCLK_DACC             (PM_PBAMASK_DACC)
//! Analog Comparator
#define SYSCLK_ACIFC            (PM_PBAMASK_ACIFC)
//! Glue Logic Controller
#define SYSCLK_GLOC             (PM_PBAMASK_GLOC)
//! ABDACB Controller
#define SYSCLK_ABDACB           (PM_PBAMASK_ABDACB)
//! TRNG Controller
#define SYSCLK_TRNG             (PM_PBAMASK_TRNG)
//! PARC Controller
#define SYSCLK_PARC             (PM_PBAMASK_PARC)
//! CATB Controller
#define SYSCLK_CATB             (PM_PBAMASK_CATB)
//! TWIM2 Controller
#define SYSCLK_TWIM2           (PM_PBAMASK_TWIM2)
//! TWIM3 Controller
#define SYSCLK_TWIM3           (PM_PBAMASK_TWIM3)
//! LCDCA Controller
#define SYSCLK_LCDCA           (PM_PBAMASK_LCDCA)
//@}

//! \name Clocks derived from the PBB clock
//@{
//! HCACHE registers
#define SYSCLK_HCACHE_REGS       (PM_PBBMASK_HCACHE)
//! Flash Controller registers
#define SYSCLK_HFLASHC_REGS      (PM_PBBMASK_HFLASHC)
//! USBC registers
#define SYSCLK_USBC_REGS         (PM_PBBMASK_USBC)
//! HSB Matrix configuration
#define SYSCLK_HMATRIX           (PM_PBBMASK_HMATRIX)
//! Peripheral Event System
#define SYSCLK_EVENT             (PM_PBBMASK_PEVC)
//! PDCA
#define SYSCLK_PDCA              (PM_PBBMASK_PDCA)
//! CRCCU
#define SYSCLK_CRCCU             (PM_PBBMASK_CRCCU)

//@}

//! \name Clocks derived from the PBD clock
//@{
//! BPM registers
#define SYSCLK_BPM                 (PM_PBDMASK_BPM)
//! BSCIF registers
#define SYSCLK_BSCIF               (PM_PBDMASK_BSCIF)
//! AST registers
#define SYSCLK_AST                 (PM_PBDMASK_AST)
//! WDT configuration
#define SYSCLK_WDT                 (PM_PBDMASK_WDT)
//! EIC System
#define SYSCLK_EIC                 (PM_PBDMASK_EIC)
//! PICOUART registers
#define SYSCLK_PICOUART            (PM_PBDMASK_PICOUART)

//@}

#ifndef __ASSEMBLY__

#include "io.h"
#include <dfll.h>
#include <osc.h>
#include <pll.h>
#include <genclk.h>

// Use the slow clock (RCOSC) with no prescaling if config was empty.
#ifndef CONFIG_SYSCLK_SOURCE
# define CONFIG_SYSCLK_SOURCE    SYSCLK_SRC_RCSYS
#endif /* CONFIG_SYSCLK_SOURCE */

/**
 * \def CONFIG_SYSCLK_CPU_DIV
 * \brief Configuration symbol for dividing the CPU clock frequency by
 * \f$2^{CONFIG\_SYSCLK\_CPU\_DIV}\f$
 *
 * If this symbol is not defined, the CPU clock frequency is not divided.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifndef CONFIG_SYSCLK_CPU_DIV
# define CONFIG_SYSCLK_CPU_DIV   0
#endif /* CONFIG_SYSCLK_CPU_DIV */

/**
 * \def CONFIG_SYSCLK_INIT_HSBMASK
 * \brief Configuration symbol for the HSB clocks enabled at power-on after the
 * sysclock module has been initialized. By default, all HSB clocks are left
 * enabled, however to save power these can be automatically disabled by defining
 * this value to a mask of \c SYSCLOCK_xxx settings.
 *
 * If this symbol is not defined, then all HSB clocks are left enabled.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifdef __DOXYGEN__
# define CONFIG_SYSCLK_INIT_HSBMASK
#endif

/**
 * \def CONFIG_SYSCLK_PBA_DIV
 * \brief Configuration symbol for dividing the PBA clock frequency by
 * \f$2^{CONFIG\_SYSCLK\_PBA\_DIV}\f$
 *
 * If this symbol is not defined, the PBA clock frequency is not divided.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifndef CONFIG_SYSCLK_PBA_DIV
# define CONFIG_SYSCLK_PBA_DIV   0
#endif /* CONFIG_SYSCLK_PBA_DIV */

/**
 * \def CONFIG_SYSCLK_PBB_DIV
 * \brief Configuration symbol for dividing the PBB clock frequency by
 * \f$2^{CONFIG\_SYSCLK\_PBB\_DIV}\f$
 *
 * If this symbol is not defined, the PBB clock frequency is not divided.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifndef CONFIG_SYSCLK_PBB_DIV
# define CONFIG_SYSCLK_PBB_DIV   0
#endif /* CONFIG_SYSCLK_PBB_DIV */

/**
 * \def CONFIG_SYSCLK_PBC_DIV
 * \brief Configuration symbol for dividing the PBC clock frequency by
 * \f$2^{CONFIG\_SYSCLK\_PBC\_DIV}\f$
 *
 * If this symbol is not defined, the PBC clock frequency is not divided.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifndef CONFIG_SYSCLK_PBC_DIV
# define CONFIG_SYSCLK_PBC_DIV   0
#endif /* CONFIG_SYSCLK_PBC_DIV */

/**
 * \def CONFIG_SYSCLK_PBD_DIV
 * \brief Configuration symbol for dividing the PBD clock frequency by
 * \f$2^{CONFIG\_SYSCLK\_PBD\_DIV}\f$
 *
 * If this symbol is not defined, the PBD clock frequency is not divided.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifndef CONFIG_SYSCLK_PBD_DIV
# define CONFIG_SYSCLK_PBD_DIV   0
#endif /* CONFIG_SYSCLK_PBD_DIV */

/**
 * \def CONFIG_SYSCLK_INIT_CPUMASK
 * \brief Configuration symbol for the CPU clocks enabled at power-on after the
 * sysclock module has been initialized. By default, all CPU clocks are left
 * enabled, however to save power these can be automatically disabled by defining
 * this value to a mask of \c SYSCLOCK_xxx settings.
 *
 * If this symbol is not defined, then all CPU clocks are left enabled.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifdef __DOXYGEN__
# define CONFIG_SYSCLK_INIT_CPUMASK
#endif

/**
 * \def CONFIG_SYSCLK_INIT_PBAMASK
 * \brief Configuration symbol for the PBA clocks enabled at power-on after the
 * sysclock module has been initialized. By default, all PBA clocks are left
 * enabled, however to save power these can be automatically disabled by defining
 * this value to a mask of \c SYSCLOCK_xxx settings.
 *
 * If this symbol is not defined, then all PBA clocks are left enabled.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifdef __DOXYGEN__
# define CONFIG_SYSCLK_INIT_PBAMASK
#endif

/**
 * \def CONFIG_SYSCLK_INIT_PBBMASK
 * \brief Configuration symbol for the PBB clocks enabled at power-on after the
 * sysclock module has been initialized. By default, all PBB clocks are left
 * enabled, however to save power these can be automatically disabled by defining
 * this value to a mask of \c SYSCLOCK_xxx settings.
 *
 * If this symbol is not defined, then all PBB clocks are left enabled.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifdef __DOXYGEN__
# define CONFIG_SYSCLK_INIT_PBBMASK
#endif

/**
 * \def CONFIG_SYSCLK_INIT_PBCMASK
 * \brief Configuration symbol for the PBC clocks enabled at power-on after the
 * sysclock module has been initialized. By default, all PBC clocks are left
 * enabled, however to save power these can be automatically disabled by defining
 * this value to a mask of \c SYSCLOCK_xxx settings.
 *
 * If this symbol is not defined, then all PBC clocks are left enabled.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifdef __DOXYGEN__
# define CONFIG_SYSCLK_INIT_PBCMASK
#endif

/**
 * \def CONFIG_SYSCLK_INIT_PBDMASK
 * \brief Configuration symbol for the PBD clocks enabled at power-on after the
 * sysclock module has been initialized. By default, all PBD clocks are left
 * enabled, however to save power these can be automatically disabled by defining
 * this value to a mask of \c SYSCLOCK_xxx settings.
 *
 * If this symbol is not defined, then all PBD clocks are left enabled.
 *
 * This symbol may be defined in \ref conf_clock.h.
 */
#ifdef __DOXYGEN__
# define CONFIG_SYSCLK_INIT_PBDMASK
#endif


/**
 * \def CONFIG_USBCLK_SOURCE
 * \brief Configuration symbol for the USB generic clock source
 *
 * Sets the clock source to use for the USB. The source must also be properly
 * configured.
 *
 * Define this to one of the \c USBCLK_SRC_xxx settings. Leave it undefined if
 * USB is not required.
 */
#ifdef __DOXYGEN__
# define CONFIG_USBCLK_SOURCE
#endif

/**
 * \def CONFIG_USBCLK_DIV
 * \brief Configuration symbol for the USB generic clock divider setting
 *
 * Sets the clock division for the USB generic clock. If a USB clock source is
 * selected with CONFIG_USBCLK_SOURCE, this configuration symbol must also be
 * defined.
 *
 * Define this as any value that does not exceed \c GENCLK_DIV_MAX, and which
 * will give a 48 MHz clock frequency from the selected source.
 */
#ifdef __DOXYGEN__
# define CONFIG_USBCLK_DIV
#endif

/**
 * \name Querying the system clock and its derived clocks
 *
 * The following functions may be used to query the current frequency of
 * the system clock and the CPU and bus clocks derived from it.
 * sysclk_get_main_hz() and sysclk_get_cpu_hz() can be assumed to be
 * available on all platforms, although some platforms may define
 * additional accessors for various chip-internal bus clocks. These are
 * usually not intended to be queried directly by generic code.
 */
//@{

/**
 * \brief Return the current rate in Hz of the main system clock
 *
 * \todo This function assumes that the main clock source never changes
 * once it's been set up, and that PLL0 always runs at the compile-time
 * configured default rate. While this is probably the most common
 * configuration, which we want to support as a special case for
 * performance reasons, we will at some point need to support more
 * dynamic setups as well.
 */
#if (defined CONFIG_SYSCLK_DEFAULT_RETURNS_SLOW_OSC)
extern bool sysclk_initialized;
#endif
static inline uint32_t sysclk_get_main_hz(void)
{
#if (defined CONFIG_SYSCLK_DEFAULT_RETURNS_SLOW_OSC)
	if (!sysclk_initialized ) {
		return OSC_RCSYS_NOMINAL_HZ;
	}
#endif

	switch (CONFIG_SYSCLK_SOURCE) {
	case SYSCLK_SRC_RCSYS:
		return OSC_RCSYS_NOMINAL_HZ;

#ifdef BOARD_OSC0_HZ
	case SYSCLK_SRC_OSC0:
		return BOARD_OSC0_HZ;
#endif


#ifdef CONFIG_DFLL0_SOURCE
	case SYSCLK_SRC_DFLL:
		return dfll_get_default_rate(0);
#endif

	case SYSCLK_SRC_RC1M:
		return OSC_RC1M_NOMINAL_HZ;

	case SYSCLK_SRC_RC80M:
		return OSC_RC80M_NOMINAL_HZ;

	case SYSCLK_SRC_RCFAST:
		switch (CONFIG_RCFAST_FRANGE) {
		case 0:
			return OSC_RCFAST4M_NOMINAL_HZ;
		case 1:
			return OSC_RCFAST8M_NOMINAL_HZ;
		case 2:
		default:
			return OSC_RCFAST12M_NOMINAL_HZ;
		}

#ifdef CONFIG_PLL0_SOURCE
	case SYSCLK_SRC_PLL0:
		return pll_get_default_rate(0);
#endif

	default:
		/* unhandled_case(CONFIG_SYSCLK_SOURCE); */
		return 0;
	}
}

/**
 * \brief Return the current rate in Hz of the CPU clock
 *
 * \todo This function assumes that the CPU always runs at the system
 * clock frequency. We want to support at least two more scenarios:
 * Fixed CPU/bus clock dividers (config symbols) and dynamic CPU/bus
 * clock dividers (which may change at run time). Ditto for all the bus
 * clocks.
 *
 * \return Frequency of the CPU clock, in Hz.
 */
static inline uint32_t sysclk_get_cpu_hz(void)
{
	return sysclk_get_main_hz() >> CONFIG_SYSCLK_CPU_DIV;
}

/**
 * \brief Return the current rate in Hz of the High-Speed Bus clock
 *
 * \return Frequency of the High Speed Peripheral Bus clock, in Hz.
 */
static inline uint32_t sysclk_get_hsb_hz(void)
{
	return sysclk_get_main_hz() >> CONFIG_SYSCLK_CPU_DIV;
}

/**
 * \brief Return the current rate in Hz of the Peripheral Bus A clock
 *
 * \return Frequency of the Peripheral Bus A clock, in Hz.
 */
static inline uint32_t sysclk_get_pba_hz(void)
{
	return sysclk_get_main_hz() >> CONFIG_SYSCLK_PBA_DIV;
}

/**
 * \brief Return the current rate in Hz of the Peripheral Bus B cl ock
 *
 * \return Frequency of the Peripheral Bus B clock, in Hz.
 */
static inline uint32_t sysclk_get_pbb_hz(void)
{
	return sysclk_get_main_hz() >> CONFIG_SYSCLK_PBB_DIV;
}

/**
 * \brief Return the current rate in Hz of the Peripheral Bus B cl ock
 *
 * \return Frequency of the Peripheral Bus C clock, in Hz.
 */
static inline uint32_t sysclk_get_pbc_hz(void)
{
	return sysclk_get_main_hz() >> CONFIG_SYSCLK_PBC_DIV;
}

/**
 * \brief Return the current rate in Hz of the Peripheral Bus B cl ock
 *
 * \return Frequency of the Peripheral Bus D clock, in Hz.
 */
static inline uint32_t sysclk_get_pbd_hz(void)
{
	return sysclk_get_main_hz() >> CONFIG_SYSCLK_PBD_DIV;
}

/**
 * \brief Retrieves the current rate in Hz of the Peripheral Bus clock attached
 *        to the specified peripheral.
 *
 * \param module Pointer to the module's base address.
 *
 * \return Frequency of the bus attached to the specified peripheral, in Hz.
 */
static inline uint32_t sysclk_get_peripheral_bus_hz(const volatile void *module)
{

	/* Fallthroughs intended for modules sharing the same peripheral bus. */
	switch ((uintptr_t)module) {
	case IISC_ADDR:
	case SPI_ADDR:
	case TC0_ADDR:
	case TC1_ADDR:
	case TWIM0_ADDR:
	case TWIS0_ADDR:
	case TWIM1_ADDR:
	case TWIS1_ADDR:
	case USART0_ADDR:
	case USART1_ADDR:
	case USART2_ADDR:
	case USART3_ADDR:
	case ADCIFE_ADDR:
	case DACC_ADDR:
	case ACIFC_ADDR:
	case GLOC_ADDR:
	case ABDACB_ADDR:
	case TRNG_ADDR:
	case PARC_ADDR:
	case CATB_ADDR:
	case PTC_ADDR:
	case TWIM2_ADDR:
	case TWIM3_ADDR:
	case LCDCA_ADDR:
		return sysclk_get_pba_hz();

	case HFLASHC_ADDR:
	case HCACHE_ADDR:
	case HMATRIX_ADDR:
	case PDCA_ADDR:
	case CRCCU_ADDR:
	case USBC_ADDR:
	case PEVC_ADDR:
		return sysclk_get_pbb_hz();

	case BPM_ADDR:
	case BSCIF_ADDR:
	case AST_ADDR:
	case WDT_ADDR:
	case EIC_ADDR:
	case PICOUART_ADDR:
		return sysclk_get_pbd_hz();

	default:
		Assert(false);
		return 0;
	}
}

//@}

extern void sysclk_priv_enable_module(RwReg *pClkMaskReg, uint32_t mask);
extern void sysclk_priv_disable_module(RwReg *pClkMaskReg, uint32_t mask);

//! \name Enabling and disabling synchronous clocks
//@{

/**
 * \brief Enable a module clock derived from the CPU clock
 * \param index Index of the module clock in the CPUMASK register
 */
static inline void sysclk_enable_cpu_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->CPUMASK;
        tempo |= index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->CPUMASK - (uint32_t)PM);
	PM->CPUMASK = tempo;
}

/**
 * \brief Disable a module clock derived from the CPU clock
 * \param index Index of the module clock in the CPUMASK register
 */
static inline void sysclk_disable_cpu_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->CPUMASK;
        tempo &= ~index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->CPUMASK - (uint32_t)PM);
	PM->CPUMASK = tempo;
}

/**
 * \brief Enable a module clock derived from the HSB clock
 * \param index Index of the module clock in the HSBMASK register
 */
static inline void sysclk_enable_hsb_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->HSBMASK;
        tempo |= index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->HSBMASK - (uint32_t)PM);
	PM->HSBMASK = tempo;
}

/**
 * \brief Disable a module clock derived from the HSB clock
 * \param index Index of the module clock in the HSBMASK register
 */
static inline void sysclk_disable_hsb_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->HSBMASK;
        tempo &= ~index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->HSBMASK - (uint32_t)PM);
	PM->HSBMASK = tempo;
}

/**
 * \brief Enable a module clock derived from the PBA clock
 * \param index Index of the module clock in the PBAMASK register
 */
static inline void sysclk_enable_pba_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->PBAMASK;
        tempo |= index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBAMASK - (uint32_t)PM);
	PM->PBAMASK = tempo;
}

/**
 * \brief Disable a module clock derived from the PBA clock
 * \param index Index of the module clock in the PBAMASK register
 */
static inline void sysclk_disable_pba_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->PBAMASK;
        tempo &= ~index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBAMASK - (uint32_t)PM);
	PM->PBAMASK = tempo;
}

static inline void sysclk_enable_pbb_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->PBBMASK;
        tempo |= index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBBMASK - (uint32_t)PM);
	PM->PBBMASK = tempo;
}

static inline void sysclk_disable_pbb_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->PBBMASK;
        tempo &= ~index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBBMASK - (uint32_t)PM);
	PM->PBBMASK = tempo;
}

static inline void sysclk_enable_pbd_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->PBDMASK;
        tempo |= index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBDMASK - (uint32_t)PM);
	PM->PBDMASK = tempo;
}

static inline void sysclk_disable_pbd_module(unsigned int index)
{
        uint32_t tempo;
        tempo = PM->PBDMASK;
        tempo &= ~index;
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBDMASK - (uint32_t)PM);
	PM->PBDMASK = tempo;
}



/**
 * \brief Enable a peripheral's clock from its base address.
 *
 *  Enables the clock to a peripheral, given its base address. If the peripheral
 *  has an associated clock on the HSB bus, this will be enabled also.
 *
 * \param module Pointer to the module's base address.
 */
static inline void sysclk_enable_peripheral_clock(const volatile void *module)
{
	switch ((uint32_t)module) {
		case IISC_ADDR:
			sysclk_enable_hsb_module(SYSCLK_IISC);
			break;
		case SPI_ADDR:
			sysclk_enable_hsb_module(SYSCLK_SPI);
			break;
		case TC0_ADDR:
			sysclk_enable_pba_module(SYSCLK_TC0);
			break;
		case TC1_ADDR:
			sysclk_enable_pba_module(SYSCLK_TC1);
			break;
		case TWIM0_ADDR:
			sysclk_enable_pba_module(SYSCLK_TWIM0);
			break;
		case TWIS0_ADDR:
			sysclk_enable_pba_module(SYSCLK_TWIS0);
			break;
		case TWIM1_ADDR:
			sysclk_enable_pba_module(SYSCLK_TWIM1);
			break;
		case TWIS1_ADDR:
			sysclk_enable_pba_module(SYSCLK_TWIS1);
			break;
		case USART0_ADDR:
			sysclk_enable_pba_module(SYSCLK_USART0);
			break;
		case USART1_ADDR:
			sysclk_enable_pba_module(SYSCLK_USART1);
			break;
		case USART2_ADDR:
			sysclk_enable_pba_module(SYSCLK_USART2);
			break;
		case USART3_ADDR:
			sysclk_enable_pba_module(SYSCLK_USART3);
			break;
		case ADCIFE_ADDR:
			sysclk_enable_pba_module(SYSCLK_ADCIFE);
			break;
		case DACC_ADDR:
			sysclk_enable_pba_module(SYSCLK_DACC);
			break;
		case GLOC_ADDR:
			sysclk_enable_pba_module(SYSCLK_GLOC);
			break;
		case ABDACB_ADDR:
			sysclk_enable_pba_module(SYSCLK_ABDACB);
			break;
		case TRNG_ADDR:
			sysclk_enable_pba_module(SYSCLK_TRNG);
			break;
		case PARC_ADDR:
			sysclk_enable_pba_module(SYSCLK_PARC);
			break;
		case CATB_ADDR:
			sysclk_enable_pba_module(SYSCLK_CATB);
			break;
		case TWIM2_ADDR:
			sysclk_enable_pba_module(SYSCLK_TWIM2);
			break;
		case TWIM3_ADDR:
			sysclk_enable_pba_module(SYSCLK_TWIM3);
			break;
		case LCDCA_ADDR:
			sysclk_enable_pba_module(SYSCLK_LCDCA);
			break;
		case HFLASHC_ADDR:
			sysclk_enable_hsb_module(SYSCLK_HFLASHC_DATA);
			sysclk_enable_pbb_module(SYSCLK_HFLASHC_REGS);
			break;
		case HCACHE_ADDR:
			sysclk_enable_pbb_module(SYSCLK_HCACHE_REGS);
			break;
		case HMATRIX_ADDR:
			sysclk_enable_pbb_module(SYSCLK_HMATRIX);
			break;
		case PDCA_ADDR:
			sysclk_enable_hsb_module(SYSCLK_PDCA_HSB);
			sysclk_enable_pbb_module(SYSCLK_PDCA);
			break;
		case CRCCU_ADDR:
			sysclk_enable_pbb_module(SYSCLK_CRCCU);
			break;
		case USBC_ADDR:
			sysclk_enable_hsb_module(SYSCLK_USBC_DATA);
			sysclk_enable_pbb_module(SYSCLK_USBC_REGS);
			break;
		case PEVC_ADDR:
			sysclk_enable_pbb_module(SYSCLK_EVENT);
			break;
		case AESA_ADDR:
			sysclk_enable_hsb_module(SYSCLK_AESA_HSB);
			break;
		case BPM_ADDR:
			sysclk_enable_pbd_module(SYSCLK_BPM);
			break;
		case BSCIF_ADDR:
			sysclk_enable_pbd_module(SYSCLK_BSCIF);
			break;
		case AST_ADDR:
			sysclk_enable_pbd_module(SYSCLK_AST);
			break;
		case WDT_ADDR:
			sysclk_enable_pbd_module(SYSCLK_WDT);
			break;
		case EIC_ADDR:
			sysclk_enable_pbd_module(SYSCLK_EIC);
			break;
		case PICOUART_ADDR:
			sysclk_enable_pbd_module(SYSCLK_PICOUART);
			break;

		default:
			Assert(false);
			return;
	}
}

/**
 * \brief Disable a peripheral's clock from its base address.
 *
 *  Disables the clock to a peripheral, given its base address. If the peripheral
 *  has an associated clock on the HSB bus, this will be disabled also.
 *
 * \param module Pointer to the module's base address.
 */
static inline void sysclk_disable_peripheral_clock(const volatile void *module)
{
	switch ((uint32_t)module) {
		case IISC_ADDR:
			sysclk_disable_hsb_module(SYSCLK_IISC);
			break;
		case SPI_ADDR:
			sysclk_disable_hsb_module(SYSCLK_SPI);
			break;
		case TC0_ADDR:
			sysclk_disable_pba_module(SYSCLK_TC0);
			break;
		case TC1_ADDR:
			sysclk_disable_pba_module(SYSCLK_TC1);
			break;
		case TWIM0_ADDR:
			sysclk_disable_pba_module(SYSCLK_TWIM0);
			break;
		case TWIS0_ADDR:
			sysclk_disable_pba_module(SYSCLK_TWIS0);
			break;
		case TWIM1_ADDR:
			sysclk_disable_pba_module(SYSCLK_TWIM1);
			break;
		case TWIS1_ADDR:
			sysclk_disable_pba_module(SYSCLK_TWIS1);
			break;
		case USART0_ADDR:
			sysclk_disable_pba_module(SYSCLK_USART0);
			break;
		case USART1_ADDR:
			sysclk_disable_pba_module(SYSCLK_USART1);
			break;
		case USART2_ADDR:
			sysclk_disable_pba_module(SYSCLK_USART2);
			break;
		case USART3_ADDR:
			sysclk_disable_pba_module(SYSCLK_USART3);
			break;
		case ADCIFE_ADDR:
			sysclk_disable_pba_module(SYSCLK_ADCIFE);
			break;
		case DACC_ADDR:
			sysclk_disable_pba_module(SYSCLK_DACC);
			break;
		case GLOC_ADDR:
			sysclk_disable_pba_module(SYSCLK_GLOC);
			break;
		case ABDACB_ADDR:
			sysclk_disable_pba_module(SYSCLK_ABDACB);
			break;
		case TRNG_ADDR:
			sysclk_disable_pba_module(SYSCLK_TRNG);
			break;
		case PARC_ADDR:
			sysclk_disable_pba_module(SYSCLK_PARC);
			break;
		case CATB_ADDR:
			sysclk_disable_pba_module(SYSCLK_CATB);
			break;
		case TWIM2_ADDR:
			sysclk_disable_pba_module(SYSCLK_TWIM2);
			break;
		case TWIM3_ADDR:
			sysclk_disable_pba_module(SYSCLK_TWIM3);
			break;
		case LCDCA_ADDR:
			sysclk_disable_pba_module(SYSCLK_LCDCA);
			break;
		case HFLASHC_ADDR:
			sysclk_disable_hsb_module(SYSCLK_HFLASHC_DATA);
			sysclk_disable_pbb_module(SYSCLK_HFLASHC_REGS);
			break;
		case HCACHE_ADDR:
			sysclk_disable_pbb_module(SYSCLK_HCACHE_REGS);
			break;
		case HMATRIX_ADDR:
			sysclk_disable_pbb_module(SYSCLK_HMATRIX);
			break;
		case PDCA_ADDR:
			sysclk_disable_hsb_module(SYSCLK_PDCA_HSB);
			sysclk_disable_pbb_module(SYSCLK_PDCA);
			break;
		case CRCCU_ADDR:
			sysclk_disable_pbb_module(SYSCLK_CRCCU);
			break;
		case USBC_ADDR:
			sysclk_disable_hsb_module(SYSCLK_USBC_DATA);
			sysclk_disable_pbb_module(SYSCLK_USBC_REGS);
			break;
		case PEVC_ADDR:
			sysclk_disable_pbb_module(SYSCLK_EVENT);
			break;
		case AESA_ADDR:
			sysclk_disable_hsb_module(SYSCLK_AESA_HSB);
			break;
		case BPM_ADDR:
			sysclk_disable_pbd_module(SYSCLK_BPM);
			break;
		case BSCIF_ADDR:
			sysclk_disable_pbd_module(SYSCLK_BSCIF);
			break;
		case AST_ADDR:
			sysclk_disable_pbd_module(SYSCLK_AST);
			break;
		case WDT_ADDR:
			sysclk_disable_pbd_module(SYSCLK_WDT);
			break;
		case EIC_ADDR:
			sysclk_disable_pbd_module(SYSCLK_EIC);
			break;
		case PICOUART_ADDR:
			sysclk_disable_pbd_module(SYSCLK_PICOUART);
			break;

		default:
			Assert(false);
			return;
	}
}

//@}

//! \name System Clock Source and Prescaler configuration
//@{

extern void sysclk_set_prescalers(unsigned int cpu_shift,
		unsigned int pba_shift, unsigned int pbb_shift, 
		unsigned int pbc_shift, unsigned int pbd_shift);
extern void sysclk_set_source(uint_fast8_t src);

//@}

#if defined(CONFIG_USBCLK_SOURCE) || defined(__DOXYGEN__)

/**
 * \def USBCLK_STARTUP_TIMEOUT
 * \brief Number of us to wait for USB clock to start
 */
#if CONFIG_USBCLK_SOURCE==USBCLK_SRC_OSC0
#  define USBCLK_STARTUP_TIMEOUT    (OSC0_STARTUP_TIMEOUT*(1000000/SCIF_RCOSC_FREQUENCY))
#elif CONFIG_USBCLK_SOURCE==USBCLK_SRC_PLL0
#  if CONFIG_PLL0_SOURCE==PLL_SRC_OSC0
#    define USBCLK_STARTUP_TIMEOUT    (OSC0_STARTUP_TIMEOUT*(1000000/SCIF_RCOSC_FREQUENCY))
#  else
#    error Unknown value for CONFIG_PLL0_SOURCE, see conf_clock.h.
#  endif
#else
#  error Unknown value for CONFIG_USBCLK_SOURCE, see conf_clock.h.
#endif

extern void sysclk_enable_usb(void);
extern void sysclk_disable_usb(void);
#endif

extern void sysclk_init(void);

#endif /* !__ASSEMBLY__ */

//! @}

#ifdef __cplusplus
}
#endif

#endif /* CHIP_SYSCLK_H_INCLUDED */
