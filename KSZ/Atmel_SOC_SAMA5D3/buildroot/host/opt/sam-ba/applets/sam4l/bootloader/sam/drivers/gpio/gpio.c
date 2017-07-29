/**
 * \file
 *
 * \brief GPIO driver for SAM4L.
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include "gpio.h"


/*! \name Peripheral Bus Interface
 */
//! @{


int gpio_enable_module(const gpio_map_t gpiomap, uint32_t size)
{
	int status = GPIO_SUCCESS;
	uint32_t i;

	for (i = 0; i < size; i++) {
		status |= gpio_enable_module_pin(gpiomap->pin, gpiomap->pin_mask, gpiomap->function);
		gpiomap++;
	}

	return status;
}


int gpio_enable_module_pin(uint32_t pin, uint32_t pin_mask, uint32_t function)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];

	// Enable the correct function.
	switch (function) {
	case 0: // A function.
		gpio_port->PMR0C = pin_mask;
		gpio_port->PMR1C = pin_mask;
#if defined(REV_GPIO) && (REV_GPIO >= 0x210)
		gpio_port->PMR2C = pin_mask;
#endif
		break;

	case 1: // B function.
		gpio_port->PMR0S = pin_mask;
		gpio_port->PMR1C = pin_mask;
#if defined(REV_GPIO) && (REV_GPIO >= 0x210)
		gpio_port->PMR2C = pin_mask;
#endif
		break;

	case 2: // C function.
		gpio_port->PMR0C = pin_mask;
		gpio_port->PMR1S = pin_mask;
#if defined(REV_GPIO) && (REV_GPIO >= 0x210)
		gpio_port->PMR2C = pin_mask;
#endif
		break;

	case 3: // D function.
		gpio_port->PMR0S = pin_mask;
		gpio_port->PMR1S = pin_mask;
#if defined(REV_GPIO) && (REV_GPIO >= 0x210)
		gpio_port->PMR2C = pin_mask;
#endif
		break;

#if defined(REV_GPIO) && (REV_GPIO >= 0x210)
	case 4: // E function.
		gpio_port->PMR0C = pin_mask;
		gpio_port->PMR1C = pin_mask;
		gpio_port->PMR2S = pin_mask;
		break;

	case 5: // F function.
		gpio_port->PMR0S = pin_mask;
		gpio_port->PMR1C = pin_mask;
		gpio_port->PMR2S = pin_mask;
		break;

	case 6: // G function.
		gpio_port->PMR0C = pin_mask;
		gpio_port->PMR1S = pin_mask;
		gpio_port->PMR2S = pin_mask;
		break;

	case 7: // H function.
		gpio_port->PMR0S = pin_mask;
		gpio_port->PMR1S = pin_mask;
		gpio_port->PMR2S = pin_mask;
		break;
#endif

	default:
		return GPIO_INVALID_ARGUMENT;
	}

	// Disable GPIO control.
	gpio_port->GPERC = pin_mask;

	return GPIO_SUCCESS;
}


void gpio_enable_gpio(const gpio_map_t gpiomap, uint32_t size)
{
	uint32_t i;

	for (i = 0; i < size; i++) {
		gpio_enable_gpio_pin(gpiomap->pin, gpiomap->pin_mask);
		gpiomap++;
	}
}


void gpio_enable_gpio_pin(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->ODERC = pin_mask;
	gpio_port->GPERS = pin_mask;
}


// The open-drain mode of the GPIO module is not synthesized on the current SAM
// products.
// If one day some SAM products have this feature, the corresponding part
// numbers should be listed in the #if below.
// Note that other functions are available in this driver to use pins with open
// drain in GPIO mode. The advantage of the open-drain mode functions over these
// other functions is that they can be used not only in GPIO mode but also in
// module mode.
#if 0


void gpio_enable_pin_open_drain(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->ODMERS = pin_mask;
}


void gpio_disable_pin_open_drain(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->ODMERC = pin_mask;
}


#endif


void gpio_enable_pin_pull_up(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->PUERS = pin_mask;
#if defined(REV_GPIO) && (REV_GPIO == 0x215)
	gpio_port->PDERC = pin_mask;
#endif
}


void gpio_disable_pin_pull_up(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->PUERC = pin_mask;
}

#if defined(REV_GPIO) || (REV_GPIO == 0x215)
// Added support of Pull-up Resistor, Pull-down Resistor and Buskeeper Control.

/*! \brief Enables the pull-down resistor of a pin.
 *
 * \param pin The pin number.
 */
void gpio_enable_pin_pull_down(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->PUERC = pin_mask;
	gpio_port->PDERS = pin_mask;
}

/*! \brief Disables the pull-down resistor of a pin.
 *
 * \param pin The pin number.
 */
void gpio_disable_pin_pull_down(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->PDERC = pin_mask;
}

/*! \brief Enables the buskeeper functionality on a pin.
 *
 * \param pin The pin number.
 */
void gpio_enable_pin_buskeeper(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->PUERS = pin_mask;
	gpio_port->PDERS = pin_mask;
}

/*! \brief Disables the buskeeper functionality on a pin.
 *
 * \param pin The pin number.
 */
void gpio_disable_pin_buskeeper(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->PUERC = pin_mask;
	gpio_port->PDERC = pin_mask;
}

void gpio_enable_pin_schmitt(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->STERS = pin_mask;
}

void gpio_disable_pin_schmitt(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->STERC = pin_mask;
}

#endif // #if defined(REV_GPIO) || (REV_GPIO == 0x215)

void gpio_configure_pin(uint32_t pin, uint32_t pin_mask, uint32_t flags)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];

	/* Both pull-up and pull-down set means buskeeper */
#if defined(REV_GPIO) || (REV_GPIO == 0x215)
	if (flags & GPIO_PULL_DOWN) {
		gpio_port->PDERS = pin_mask;
	} else {
		gpio_port->PDERC = pin_mask;
	}
#endif
	if (flags & GPIO_PULL_UP) {
		gpio_port->PUERS = pin_mask;
	} else {
		gpio_port->PUERC = pin_mask;
	}

	/* Enable open-drain mode if requested */
#if 0
	if (flags & GPIO_OPEN_DRAIN) {
		gpio_port->ODMERS = pin_mask;
	} else {
		gpio_port->ODMERC = pin_mask;
	}

	if (flags & GPIO_OPEN_DRAIN) {
		gpio_port->PDERS = pin_mask;
	} else {
		gpio_port->PDERC = pin_mask;
	}
#endif

#if defined(REV_GPIO) || (REV_GPIO == 0x215)
	/* Select drive strength */
	if (flags & GPIO_DRIVE_LOW) {
		gpio_port->ODCR0S = pin_mask;
	} else {
		gpio_port->ODCR0C = pin_mask;
	}
	if (flags & GPIO_DRIVE_HIGH) {
		gpio_port->ODCR1S = pin_mask;
	} else {
		gpio_port->ODCR1C = pin_mask;
	}
#endif

	/* Select interrupt level for group */
	if (flags & GPIO_INTERRUPT) {
		if (flags & GPIO_BOTHEDGES) {
			gpio_port->IMR0C = pin_mask;
			gpio_port->IMR1C = pin_mask;
		}
		else if (flags & GPIO_RISING) {
			gpio_port->IMR0S = pin_mask;
			gpio_port->IMR1C = pin_mask;
		}
		else if (flags & GPIO_FALLING) {
			gpio_port->IMR0C = pin_mask;
			gpio_port->IMR1S = pin_mask;
		}
	}

	/* Select direction and initial pin state */
	if (flags & GPIO_DIR_OUTPUT) {
		if (flags & GPIO_INIT_HIGH) {
			gpio_port->OVRS = pin_mask;
		} else {
			gpio_port->OVRC = pin_mask;
		}
		gpio_port->ODERS = pin_mask;
#if defined(REV_GPIO) || (REV_GPIO == 0x215)
		// Always disable the Schmitt trigger for output pins.
		gpio_port->STERC = pin_mask;
#endif
	} else {
		gpio_port->ODERC = pin_mask;
#if defined(REV_GPIO) || (REV_GPIO == 0x215)
		// Always enable the Schmitt trigger for input pins.
		gpio_port->STERS = pin_mask;
#endif
	}

	/* Enable GPIO */
	gpio_port->GPERS = pin_mask;
}

void gpio_configure_group(uint32_t port, uint32_t mask, uint32_t flags)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[port];

	/* Both pull-up and pull-down set means buskeeper */
#if defined(REV_GPIO) || (REV_GPIO == 0x215)
	if (flags & GPIO_PULL_DOWN) {
		gpio_port->PDERS = mask;
	} else {
		gpio_port->PDERC = mask;
	}
#endif
	if (flags & GPIO_PULL_UP) {
		gpio_port->PUERS = mask;
	} else {
		gpio_port->PUERC = mask;
	}

	/* Enable open-drain mode if requested */
#if 0
	if (flags & GPIO_OPEN_DRAIN) {
		gpio_port->ODMERS = mask;
	} else {
		gpio_port->ODMERC = mask;
	}

	if (flags & GPIO_OPEN_DRAIN) {
		gpio_port->PDERS = mask;
	} else {
		gpio_port->PDERC = mask;
	}
#endif

#if defined(REV_GPIO) || (REV_GPIO == 0x215)
	/* Select drive strength */
	if (flags & GPIO_DRIVE_LOW) {
		gpio_port->ODCR0S = mask;
	} else {
		gpio_port->ODCR0C = mask;
	}

	if (flags & GPIO_DRIVE_HIGH) {
		gpio_port->ODCR1S = mask;
	} else {
		gpio_port->ODCR1C = mask;
	}
#endif

	/* Select interrupt level for group */
	if (flags & GPIO_INTERRUPT) {
		if (flags & GPIO_BOTHEDGES) {
			gpio_port->IMR0C = mask;
			gpio_port->IMR1C = mask;

		} else if (flags & GPIO_RISING) {
			gpio_port->IMR0S = mask;
			gpio_port->IMR1C = mask;

		} else if (flags & GPIO_FALLING) {
			gpio_port->IMR0C = mask;
			gpio_port->IMR1S = mask;
		}
	}

	/* Select direction and initial pin state */
	if (flags & GPIO_DIR_OUTPUT) {
		if (flags & GPIO_INIT_HIGH) {
			gpio_port->OVRS = mask;
		} else {
			gpio_port->OVRC = mask;
		}
		gpio_port->ODERS = mask;
#if defined(REV_GPIO) || (REV_GPIO == 0x215)
		// Always disable the Schmitt trigger for output pins.
		gpio_port->STERC = mask;
#endif
	} else {
		gpio_port->ODERC = mask;
#if defined(REV_GPIO) || (REV_GPIO == 0x215)
		// Always enable the Schmitt trigger for input pins.
		gpio_port->STERS = mask;
#endif
	}

	/* Enable GPIO */
	gpio_port->GPERS = mask;
}

int gpio_get_pin_value(uint32_t pin)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	return (gpio_port->PVR >> (pin & 0x1F)) & 1;
}


int gpio_get_gpio_pin_output_value(uint32_t pin)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	return (gpio_port->OVR >> (pin & 0x1F)) & 1;
}


int gpio_get_gpio_open_drain_pin_output_value(uint32_t pin)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	return ((gpio_port->ODER >> (pin & 0x1F)) & 1) ^ 1;
}


void gpio_set_gpio_pin(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->OVRS  = pin_mask; // Value to be driven on the I/O line: 1.
	gpio_port->ODERS = pin_mask; // The GPIO output driver is enabled for that pin.
	gpio_port->GPERS = pin_mask; // The GPIO module controls that pin.
}

void gpio_set_pin_high(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->OVRS  = pin_mask; // Value to be driven on the I/O line: 1.
}

void gpio_set_group_high(uint32_t port, uint32_t mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[port];
	gpio_port->OVRS  = mask; // Value to be driven on the I/O group: 1.
}


void gpio_set_pin_low(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->OVRC  = pin_mask; // Value to be driven on the I/O line: 0.
}

void gpio_clr_gpio_pin(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->OVRC  = pin_mask; // Value to be driven on the I/O line: 0.
	gpio_port->ODERS = pin_mask; // The GPIO output driver is enabled for that pin.
	gpio_port->GPERS = pin_mask; // The GPIO module controls that pin.
}

void gpio_set_group_low(uint32_t port, uint32_t mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[port];
	gpio_port->OVRC  = mask; // Value to be driven on the I/O group: 0.
}

void gpio_tgl_gpio_pin(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->OVRT  = pin_mask; // Toggle the I/O line.
	gpio_port->ODERS = pin_mask; // The GPIO output driver is enabled for that pin.
	gpio_port->GPERS = pin_mask; // The GPIO module controls that pin.
}

void gpio_toggle_pin(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->OVRT  = pin_mask; // Toggle the I/O line.
}

void gpio_toggle_group(uint32_t port, uint32_t mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[port];
	gpio_port->OVRT  = mask; // Toggle the I/O port.
}

void gpio_set_gpio_open_drain_pin(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];

	gpio_port->ODERC = pin_mask; // The GPIO output driver is disabled for that pin.
	gpio_port->GPERS = pin_mask; // The GPIO module controls that pin.
}


void gpio_clr_gpio_open_drain_pin(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];

	gpio_port->OVRC  = pin_mask; // Value to be driven on the I/O line: 0.
	gpio_port->ODERS = pin_mask; // The GPIO output driver is enabled for that pin.
	gpio_port->GPERS = pin_mask; // The GPIO module controls that pin.
}


void gpio_tgl_gpio_open_drain_pin(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];

	gpio_port->OVRC  = pin_mask; // Value to be driven on the I/O line if the GPIO output driver is enabled: 0.
	gpio_port->ODERT = pin_mask; // The GPIO output driver is toggled for that pin.
	gpio_port->GPERS = pin_mask; // The GPIO module controls that pin.
}


void gpio_enable_pin_glitch_filter(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->GFERS = pin_mask;
}


void gpio_disable_pin_glitch_filter(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->GFERC = pin_mask;
}

/*! \brief Configure the edge detector of an input pin
 *
 * \param pin The pin number.
 * \param pin_mask The pin mask.
 * \param mode The edge detection mode (\ref GPIO_PIN_CHANGE, \ref GPIO_RISING_EDGE
 *             or \ref GPIO_FALLING_EDGE).
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
static int gpio_configure_edge_detector(uint32_t pin, uint32_t pin_mask, uint32_t mode)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];

	// Configure the edge detector.
	switch (mode) {
	case GPIO_PIN_CHANGE:
		gpio_port->IMR0C = pin_mask;
		gpio_port->IMR1C = pin_mask;
		break;

	case GPIO_RISING_EDGE:
		gpio_port->IMR0S = pin_mask;
		gpio_port->IMR1C = pin_mask;
		break;

	case GPIO_FALLING_EDGE:
		gpio_port->IMR0C = pin_mask;
		gpio_port->IMR1S = pin_mask;
		break;

	default:
		return GPIO_INVALID_ARGUMENT;
	}

	return GPIO_SUCCESS;
}


int gpio_enable_pin_interrupt(uint32_t pin, uint32_t pin_mask, uint32_t mode)
{
	volatile GpioPort  *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];

	// Enable the glitch filter.
	gpio_port->GFERS = pin_mask;

	// Configure the edge detector.
	if(GPIO_INVALID_ARGUMENT == gpio_configure_edge_detector(pin, pin_mask, mode)) {
		return GPIO_INVALID_ARGUMENT;
	}

	// Enable interrupt.
	gpio_port->IERS = pin_mask;

	return GPIO_SUCCESS;
}


void gpio_disable_pin_interrupt(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	gpio_port->IERC = pin_mask;
}


int gpio_get_pin_interrupt_flag(uint32_t pin)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];
	return (gpio_port->IFR >> (pin & 0x1F)) & 1;
}


void gpio_clear_pin_interrupt_flag(uint32_t pin, uint32_t pin_mask)
{
	volatile GpioPort *gpio_port = &(*((volatile Gpio*)GPIO)).Port[pin >> 5];

	gpio_port->IFRC = pin_mask;
}




//! @}
