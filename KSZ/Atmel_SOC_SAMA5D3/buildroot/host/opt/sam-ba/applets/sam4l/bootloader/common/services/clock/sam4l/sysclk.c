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

#include <compiler.h>
#include <stdbool.h>
#include <sysclk.h>
#include <flashcalw.h>
#include <osc.h>

/**
 * \weakgroup sysclk_group
 * @{
 */

#if ((CONFIG_SYSCLK_CPU_DIV > CONFIG_SYSCLK_PBA_DIV) || \
     (CONFIG_SYSCLK_CPU_DIV > CONFIG_SYSCLK_PBB_DIV))
# error CONFIG_SYSCLK_PBx_DIV must be equal to or more than CONFIG_SYSCLK_CPU_DIV.
#endif

/**
 * \internal
 * \defgroup sysclk_internals_group System Clock internals
 *
 * System clock management is fairly straightforward apart from one
 * thing: Enabling and disabling bus bridges. When all peripherals on a
 * given bus are disabled, the bridge to the bus may be disabled. Only
 * the PBA and PBB busses support this, and it is not practical to
 * disable the PBA bridge as it includes the PM and SCIF modules, so turning
 * it off would make it impossible to turn anything back on again.
 *
 * The system clock implementation keeps track of a reference count for
 * PBB. When the reference count is zero, the bus bridge is disabled, otherwise
 * it is enabled.
 *
 * @{
 */

/**
 * \internal
 * \name Initial module clock masks
 *
 * These are the mask values written to the xxxMASK registers during
 * initialization if the user has overriden the default behaviour of all clocks
 * left enabled. These values assume that:
 *   - Debugging should be possible
 *   - The program may be running from flash
 *   - The PM should be available to unmask other clocks
 *   - All on-chip RAM should be available
 *   - INTC, SCIF, PM and GPIO are made permanently available for now; this
 *     may change in the future.
 */
//@{
//! \internal
//! \brief Initial value of CPUMASK
#define SYSCLK_INIT_MINIMAL_CPUMASK                                    \
	(SYSCLK_OCD)
//! \internal
//! \brief Initial value of HSBMASK
#define SYSCLK_INIT_MINIMAL_HSBMASK                                    \
	((SYSCLK_HFLASHC_DATA)                                        \
	| (SYSCLK_PBA_BRIDGE)                                        \
	| (SYSCLK_PBB_BRIDGE)                                        \
	| (SYSCLK_PBC_BRIDGE)                                        \
	| (SYSCLK_PBD_BRIDGE))

//! \internal
//! \brief Initial value of PBAMASK
#define SYSCLK_INIT_MINIMAL_PBAMASK                                    \
	(SYSCLK_FLASHCALW_REGS)

//! \internal
//! \brief Initial value of PBBMASK
#define SYSCLK_INIT_MINIMAL_PBBMASK                                    \
	(SYSCLK_HFLASHC_REGS)

//! \internal
//! \brief Initial value of PBDMASK
#define SYSCLK_INIT_MINIMAL_PBDMASK                                    \
	((SYSCLK_BPM)                                                 \
	| (SYSCLK_BSCIF))
//@}

/**
 * \internal
 * \brief Number of enabled peripherals on the PBB bus.
 */
static uint8_t sysclk_pbb_refcount;

#if defined(CONFIG_SYSCLK_DEFAULT_RETURNS_SLOW_OSC)
/**
 * \brief boolean signaling that the sysclk_init is done.
 */
bool sysclk_initialized = false;
#endif


//! @}

/**
 * \brief Set system clock prescaler configuration
 *
 * This function will change the system clock prescaler configuration to
 * match the parameters.
 *
 * \note The parameters to this function are device-specific.
 *
 * \param cpu_shift The CPU clock will be divided by \f$2^{cpu\_shift}\f$
 * \param pba_shift The PBA clock will be divided by \f$2^{pba\_shift}\f$
 * \param pbb_shift The PBB clock will be divided by \f$2^{pbb\_shift}\f$
 * \param pbc_shift The PBC clock will be divided by \f$2^{pbb\_shift}\f$
 * \param pbd_shift The PBD clock will be divided by \f$2^{pbd\_shift}\f$
 */
void sysclk_set_prescalers(unsigned int cpu_shift,
		unsigned int pba_shift, 
		unsigned int pbb_shift,
		unsigned int pbc_shift,		
		unsigned int pbd_shift)
{
	irqflags_t flags;
	uint32_t   cpu_cksel = 0;
	uint32_t   pba_cksel = 0;
	uint32_t   pbb_cksel = 0;
	uint32_t   pbc_cksel = 0;	
	uint32_t   pbd_cksel = 0;

	Assert(cpu_shift <= pba_shift);
	Assert(cpu_shift <= pbb_shift);
	Assert(cpu_shift <= pbc_shift);
	Assert(cpu_shift <= pbd_shift);

	if (cpu_shift > 0)
		cpu_cksel = (PM_CPUSEL_CPUSEL(cpu_shift - 1))
				| PM_CPUSEL_CPUDIV;

	if (pba_shift > 0)
		pba_cksel = (PM_PBASEL_PBSEL(pba_shift - 1))
				| PM_PBASEL_PBDIV;

	if (pbb_shift > 0)
		pbb_cksel = (PM_PBBSEL_PBSEL(pbb_shift - 1))
				| PM_PBBSEL_PBDIV;

	if (pbc_shift > 0)
		pbc_cksel = (PM_PBCSEL_PBSEL(pbc_shift - 1))
				| PM_PBCSEL_PBDIV;

	if (pbd_shift > 0)
		pbd_cksel = (PM_PBDSEL_PBSEL(pbd_shift - 1))
				| PM_PBDSEL_PBDIV;

	flags = cpu_irq_save();
	
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->CPUSEL - (uint32_t)PM);
	PM->CPUSEL = cpu_cksel;
	
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBASEL - (uint32_t)PM);
	PM->PBASEL = pba_cksel;
	
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBBSEL - (uint32_t)PM);
	PM->PBBSEL = pbb_cksel;
	
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBCSEL - (uint32_t)PM);
	PM->PBCSEL = pbc_cksel;

	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBDSEL - (uint32_t)PM);
	PM->PBDSEL = pbd_cksel;

	cpu_irq_restore(flags);
}

/**
 * \brief Change the source of the main system clock.
 *
 * \param src The new system clock source. Must be one of the constants
 * from the <em>System Clock Sources</em> section.
 */
void sysclk_set_source(uint_fast8_t src)
{
	irqflags_t flags;
	Assert(src <= SYSCLK_SRC_RC12M);

	flags = cpu_irq_save();
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->MCCTRL - (uint32_t)PM);
	PM->MCCTRL = src;
	cpu_irq_restore(flags);
}

#if defined(CONFIG_USBCLK_SOURCE) || defined(__DOXYGEN__)
/**
 * \brief Enable the USB generic clock
 *
 * \pre The USB generick clock must be configued to 48MHz.
 * CONFIG_USBCLK_SOURCE and CONFIG_USBCLK_DIV must be defined with proper
 * configuration. The selected clock source must also be configured.
 */
void sysclk_enable_usb(void)
{
	// Note: the SYSCLK_PBB_BRIDGE clock is enabled by
	// sysclk_enable_pbb_module().
	sysclk_enable_hsb_module(SYSCLK_USBC_DATA);
	sysclk_enable_pbb_module(SYSCLK_USBC_REGS);

	genclk_enable_config(7, CONFIG_USBCLK_SOURCE, CONFIG_USBCLK_DIV);
}

/**
 * \brief Disable the USB generic clock
 */
void sysclk_disable_usb(void)
{
   genclk_disable(7);
}
#endif // CONFIG_USBCLK_SOURCE

void sysclk_init(void)
{
	/* Set up system clock dividers if different from defaults */
	if ((CONFIG_SYSCLK_CPU_DIV > 0) || 
		(CONFIG_SYSCLK_PBA_DIV > 0) ||
		(CONFIG_SYSCLK_PBB_DIV > 0) ||
		(CONFIG_SYSCLK_PBC_DIV > 0) ||
		(CONFIG_SYSCLK_PBD_DIV > 0)) {
		sysclk_set_prescalers(CONFIG_SYSCLK_CPU_DIV,
				CONFIG_SYSCLK_PBA_DIV,
				CONFIG_SYSCLK_PBB_DIV,
				CONFIG_SYSCLK_PBC_DIV,
                CONFIG_SYSCLK_PBD_DIV);
	}

	/* Switch to system clock selected by user */
	switch (CONFIG_SYSCLK_SOURCE) {
	case SYSCLK_SRC_RCSYS:
		/* Already running from RCSYS */
		break;

#ifdef BOARD_OSC0_HZ
	case SYSCLK_SRC_OSC0:
		osc_enable(OSC_ID_OSC0);
		osc_wait_ready(OSC_ID_OSC0);
		// Set a flash wait state depending on the new cpu frequency.
		flash_set_bus_freq(sysclk_get_cpu_hz());
		sysclk_set_source(SYSCLK_SRC_OSC0);
		break;
#endif

#ifdef CONFIG_DFLL0_SOURCE
	case SYSCLK_SRC_DFLL:
		dfll_enable_config_defaults(0);
		// Set a flash wait state depending on the new cpu frequency.
		flash_set_bus_freq(sysclk_get_cpu_hz());
		sysclk_set_source(SYSCLK_SRC_DFLL);
		break;
#endif

#ifdef CONFIG_PLL0_SOURCE
	case SYSCLK_SRC_PLL0: {
		pll_enable_config_defaults(0);
		// Set a flash wait state depending on the new cpu frequency.
		flash_set_bus_freq(sysclk_get_cpu_hz());
		sysclk_set_source(SYSCLK_SRC_PLL0);
		break;
	}
#endif

	case SYSCLK_SRC_RC1M:
		osc_enable(OSC_ID_RC1M);
		osc_wait_ready(OSC_ID_RC1M);
		// Set a flash wait state depending on the new cpu frequency.
		flash_set_bus_freq(sysclk_get_cpu_hz());
		sysclk_set_source(6);
		break;

	case SYSCLK_SRC_RC80M:
		osc_enable(OSC_ID_RC80M);
		osc_wait_ready(OSC_ID_RC80M);
		// Set a flash wait state depending on the new cpu frequency.
		flash_set_bus_freq(sysclk_get_cpu_hz());
		sysclk_set_source(SYSCLK_SRC_RC80M);
		break;

	case SYSCLK_SRC_RCFAST:
		osc_enable(OSC_ID_RCFAST);
		osc_wait_ready(OSC_ID_RCFAST);
		// Set a flash wait state depending on the new cpu frequency.
		flash_set_bus_freq(sysclk_get_cpu_hz());
		sysclk_set_source(SYSCLK_SRC_RCFAST);
		break;

	default:
		Assert(false);
		break;
	}

	/* If the user has specified clock masks, enable only requested clocks */
	irqflags_t const flags = cpu_irq_save();
#if defined(CONFIG_SYSCLK_INIT_CPUMASK)
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->CPUMASK - (uint32_t)PM);
	PM->CPUMASK = SYSCLK_INIT_MINIMAL_CPUMASK | CONFIG_SYSCLK_INIT_CPUMASK;
#endif
#if defined(CONFIG_SYSCLK_INIT_PBAMASK)
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBAMASK - (uint32_t)PM);
	PM->PBAMASK = CONFIG_SYSCLK_INIT_PBAMASK;
#endif
#if defined(CONFIG_SYSCLK_INIT_PBBMASK)
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBBMASK - (uint32_t)PM);
	PM->PBBMASK = SYSCLK_INIT_MINIMAL_PBBMASK | CONFIG_SYSCLK_INIT_PBBMASK;
#endif
#if defined(CONFIG_SYSCLK_INIT_PBDMASK)
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBDMASK - (uint32_t)PM);
	PM->PBDMASK = SYSCLK_INIT_MINIMAL_PBDMASK | CONFIG_SYSCLK_INIT_PBDMASK;
#endif
#if defined(CONFIG_SYSCLK_INIT_HSBMASK)
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->HSBMASK - (uint32_t)PM);
	PM->HSBMASK = SYSCLK_INIT_MINIMAL_HSBMASK | CONFIG_SYSCLK_INIT_HSBMASK;
#endif
	cpu_irq_restore(flags);

#if (defined CONFIG_SYSCLK_DEFAULT_RETURNS_SLOW_OSC)
	/* Signal that the internal frequencies are setup */
	sysclk_initialized = true;
#endif
}

//! @}
