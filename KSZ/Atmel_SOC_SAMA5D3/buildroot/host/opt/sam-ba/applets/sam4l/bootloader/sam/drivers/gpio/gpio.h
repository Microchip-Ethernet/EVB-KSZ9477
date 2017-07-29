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
#ifndef _GPIO_H_
#define _GPIO_H_

/**
 * \defgroup group_sam_drivers_gpio GPIO - General-Purpose Input/Output
 *
 * GPIO gives access to the MCU pins.
 *
 * \{
 */

#include "compiler.h"

/*! \name Return Values of the GPIO API
 */
//! @{
#define GPIO_SUCCESS            0 //!< Function successfully completed.
#define GPIO_INVALID_ARGUMENT   1 //!< Input parameters are out of range.
//! @}


/*! \name Interrupt Trigger Modes
 */
//! @{
#define GPIO_PIN_CHANGE         0 //!< Interrupt triggered upon pin change.
#define GPIO_RISING_EDGE        1 //!< Interrupt triggered upon rising edge.
#define GPIO_FALLING_EDGE       2 //!< Interrupt triggered upon falling edge.
//! @}

/*! \name Common defines for GPIO_FLAGS parameter
 */
//! @{
#define GPIO_DIR_INPUT  (0 << 0) //!< Pin is Input
#define GPIO_DIR_OUTPUT (1 << 0) //!< Pin is Output
#define GPIO_INIT_LOW   (0 << 1) //!< Initial Output State is Low
#define GPIO_INIT_HIGH  (1 << 1) //!< Initial Output State is High
#define GPIO_PULL_UP    (1 << 2) //!< Pull-Up (when input)
#define GPIO_PULL_DOWN  (2 << 2) //!< Pull-Down (when input)
#define GPIO_BUSKEEPER  (3 << 2) //!< Bus Keeper
#define GPIO_DRIVE_MIN  (0 << 4) //!< Drive Min Configuration
#define GPIO_DRIVE_LOW  (1 << 4) //!< Drive Low Configuration
#define GPIO_DRIVE_HIGH (2 << 4) //!< Drive High Configuration
#define GPIO_DRIVE_MAX  (3 << 4) //!< Drive Max Configuration
#define GPIO_OPEN_DRAIN (1 << 6) //!< Open-Drain (when output)
#define GPIO_INTERRUPT  (1 << 7) //!< Enable Pin/Group Interrupt
#define GPIO_BOTHEDGES  (3 << 7) //!< Sense Both Edges
#define GPIO_RISING     (5 << 7) //!< Sense Risign Edge
#define GPIO_FALLING    (7 << 7) //!< Sense Falling Edge
//! @}

//! A type definition of pins and modules connectivity.
typedef struct {
	uint32_t pin_mask;        //!< Module pin mask
	uint8_t pin;              //!< Module pin.
	uint8_t function;         //!< Module function.
} gpio_map_t[];


/*! \name Peripheral Bus Interface
 *
 * Low-speed interface with a non-deterministic number of clock cycles per
 * access.
 *
 * This interface operates with lower clock frequencies (fPB <= fCPU), and its
 * timing is not deterministic since it needs to access a shared bus which may
 * be heavily loaded.
 *
 * \note This interface is immediately available without initialization.
 */
//! @{

/*! \brief Enables specific module modes for a set of pins.
 *
 * \param gpiomap The pin map.
 * \param size The number of pins in \a gpiomap.
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
extern int gpio_enable_module(const gpio_map_t gpiomap, uint32_t size);

/*! \brief Enables a specific module mode for a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.\n
 * \param function The pin function.\n
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
extern int gpio_enable_module_pin(uint32_t pin, uint32_t pin_mask, uint32_t function);

/*! \brief Enables the GPIO mode of a set of pins.
 *
 * \param gpiomap The pin map.
 * \param size The number of pins in \a gpiomap.
 */
extern void gpio_enable_gpio(const gpio_map_t gpiomap, uint32_t size);

/*! \brief Enables the GPIO mode of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_enable_gpio_pin(uint32_t pin, uint32_t pin_mask);

// The open-drain mode of the GPIO module is not synthesized on the current SAM
// products.
// If one day some SAM products have this feature, the corresponding part
// numbers should be listed in the #if below.
// Note that other functions are available in this driver to use pins with open
// drain in GPIO mode. The advantage of the open-drain mode functions over these
// other functions is that they can be used not only in GPIO mode but also in
// module mode.
#if 0

/*! \brief Enables the open-drain mode of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_enable_pin_open_drain(uint32_t pin, uint32_t pin_mask);

/*! \brief Disables the open-drain mode of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_disable_pin_open_drain(uint32_t pin, uint32_t pin_mask);

#endif

/*! \brief Enables the pull-up resistor of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_enable_pin_pull_up(uint32_t pin, uint32_t pin_mask);

/*! \brief Disables the pull-up resistor of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_disable_pin_pull_up(uint32_t pin, uint32_t pin_mask);

#if defined(REV_GPIO) || (REV_GPIO == 0x215)
// Added support of Pull-up Resistor, Pull-down Resistor and Buskeeper Control.

/*! \brief Enables the pull-down resistor of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_enable_pin_pull_down(uint32_t pin, uint32_t pin_mask);

/*! \brief Disables the pull-down resistor of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_disable_pin_pull_down(uint32_t pin, uint32_t pin_mask);

/*! \brief Enables the buskeeper functionality on a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_enable_pin_buskeeper(uint32_t pin, uint32_t pin_mask);

/*! \brief Disables the buskeeper functionality on a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_disable_pin_buskeeper(uint32_t pin, uint32_t pin_mask);

/*! \brief Enable the Schmitt trigger functionality on an input pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_enable_pin_schmitt(uint32_t pin, uint32_t pin_mask);

/*! \brief Disable the Schmitt trigger functionality on an input pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_disable_pin_schmitt(uint32_t pin, uint32_t pin_mask);

#endif

/*! \brief Configuration functionality on a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 * \param flags The configuration.
 */
extern void gpio_configure_pin(uint32_t pin, uint32_t pin_mask, uint32_t flags);

/*! \brief Configuration functionality on a port.
 *
 * \param port The port number.
 * \param mask The mask.
 * \param flags The configuration.
 */
extern void gpio_configure_group(uint32_t port, uint32_t mask, uint32_t flags);

/*! \brief Returns the value of a pin.
 *
 * \param pin The pin number.\n
 *
 * \return The pin value.
 */
extern int gpio_get_pin_value(uint32_t pin);

/*!
 * \brief Check if the pin is in low logical level.
 *
 * \param pin The pin number.\n
 *
 * \return bool      1 if the pin is in low logical level
 *                   0 if the pin is not in low logical level
 */
#define gpio_pin_is_low(pin)\
	(gpio_get_pin_value(pin)?0:1)

/*!
 * \brief Check if the pin is in high logical level.
 *
 * \param pin The pin number.\n
 *
 * \return bool      1 if the pin is in high logical level
 *                   0 if the pin is not in high logical level
 */
#define gpio_pin_is_high(pin) \
	(gpio_get_pin_value(pin)?1:0)

/*! \brief Returns the output value set for a GPIO pin.
 *
 * \param pin The pin number.\n
 *
 * \return The pin output value.
 *
 * \note This function must be used in conjunction with \ref gpio_set_gpio_pin,
 *       \ref gpio_clr_gpio_pin and \ref gpio_tgl_gpio_pin.
 */
extern int gpio_get_gpio_pin_output_value(uint32_t pin);

/*! \brief Returns the output value set for a GPIO pin using open drain.
 *
 * \param pin The pin number.\n
 *
 * \return The pin output value.
 *
 * \note This function must be used in conjunction with
 *       \ref gpio_set_gpio_open_drain_pin, \ref gpio_clr_gpio_open_drain_pin
 *       and \ref gpio_tgl_gpio_open_drain_pin.
 */
extern int gpio_get_gpio_open_drain_pin_output_value(uint32_t pin);

/*! \brief Drives a GPIO pin to 1.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_set_gpio_pin(uint32_t pin, uint32_t pin_mask);

/*! \brief Drives a GPIO pin to 1.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 *
 * \note The function \ref gpio_configure_pin must be called before.
 */
extern void gpio_set_pin_high(uint32_t pin, uint32_t pin_mask);


/*! \brief Drives a GPIO port to 1.
 *
 * \param port The port number.
 * \param mask The mask.
 */
extern void gpio_set_group_high(uint32_t port, uint32_t mask);

/*! \brief Drives a GPIO pin to 0.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_clr_gpio_pin(uint32_t pin, uint32_t pin_mask);

/*! \brief Drives a GPIO pin to 0.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 *
 * \note The function \ref gpio_configure_pin must be called before.
 */
extern void gpio_set_pin_low(uint32_t pin, uint32_t pin_mask);

/*! \brief Drives a GPIO port to 0.
 *
 * \param port The port number.
 * \param mask The mask.
 */
extern void gpio_set_group_low(uint32_t port, uint32_t mask);

/*! \brief Toggles a GPIO pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_tgl_gpio_pin(uint32_t pin, uint32_t pin_mask);

/*! \brief Toggles a GPIO pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 * \note The function \ref gpio_configure_pin must be called before.
 */
extern void gpio_toggle_pin(uint32_t pin, uint32_t pin_mask);

/*! \brief Toggles a GPIO group.
 *
 * \param port The port number.
 * \param mask The mask.
 */
extern void gpio_toggle_group(uint32_t port, uint32_t mask);

/*! \brief Drives a GPIO pin to 1 using open drain.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_set_gpio_open_drain_pin(uint32_t pin, uint32_t pin_mask);

/*! \brief Drives a GPIO pin to 0 using open drain.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_clr_gpio_open_drain_pin(uint32_t pin, uint32_t pin_mask);

/*! \brief Toggles a GPIO pin using open drain.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_tgl_gpio_open_drain_pin(uint32_t pin, uint32_t pin_mask);

/*! \brief Enables the glitch filter of a pin.
 *
 * When the glitch filter is enabled, a glitch with duration of less than 1
 * clock cycle is automatically rejected, while a pulse with duration of 2 clock
 * cycles or more is accepted. For pulse durations between 1 clock cycle and 2
 * clock cycles, the pulse may or may not be taken into account, depending on
 * the precise timing of its occurrence. Thus for a pulse to be guaranteed
 * visible it must exceed 2 clock cycles, whereas for a glitch to be reliably
 * filtered out, its duration must not exceed 1 clock cycle. The filter
 * introduces 2 clock cycles latency.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_enable_pin_glitch_filter(uint32_t pin, uint32_t pin_mask);

/*! \brief Disables the glitch filter of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_disable_pin_glitch_filter(uint32_t pin, uint32_t pin_mask);

/*! \brief Enables the interrupt of a pin with the specified settings.
 *
 * \param pin The pin number.
 * \param mode The trigger mode (\ref GPIO_PIN_CHANGE, \ref GPIO_RISING_EDGE or
 *             \ref GPIO_FALLING_EDGE).
 *
 * \return \ref GPIO_SUCCESS or \ref GPIO_INVALID_ARGUMENT.
 */
extern int gpio_enable_pin_interrupt(uint32_t pin, uint32_t pin_mask, uint32_t mode);

/*! \brief Disables the interrupt of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_disable_pin_interrupt(uint32_t pin, uint32_t pin_mask);

/*! \brief Gets the interrupt flag of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 *
 * \return The pin interrupt flag.
 */
extern int gpio_get_pin_interrupt_flag(uint32_t pin);

/*! \brief Clears the interrupt flag of a pin.
 *
 * \param pin The pin number.\n
 * \param pin_mask The pin mask.
 */
extern void gpio_clear_pin_interrupt_flag(uint32_t pin, uint32_t pin_mask);

//! @}

//! \}

#endif  // _GPIO_H_
