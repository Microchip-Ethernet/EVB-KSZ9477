/**
 * \file
 *
 * \brief SAM4L-SAM-BA Bootloader
 *
 * Copyright (c) 2011 - 2012 Atmel Corporation. All rights reserved.
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
 
/*
--------------------
SAM-BA Implementation on SAM4L 
--------------------
Requirements to use SAM-BA : 

Supported communication interfaces : 
--------------------

USART0 : RX:PA05 TX:PA07
Baudrate : 115200 8N1

USB if a supported clock source running at a supported frequency is present 
	- a precise external clock at XIN (PA00) input (less than 100ppm error)
	- an XTAL between XIN (PA00) and XOUT (PA01)

Supported frequencies for USB:
	6 MHz +-2500ppm
	7,3728 MHz +-900ppm
	8 MHz +-2500ppm
	12 MHz +-2500ppm
	14,7456 MHz +-900ppm
	16 MHz +-2500ppm
	24 MHz +-2500ppm

Pins Usage
--------------------
The following pins are used by the program : 
PA05 : input
PA07 : output
PA00 : input
PA01 : output
PA25 : I/O usb
PA26 : I/O usb

The application board shall avoid driving the PA07,PA01,PA25 and PA26 signals 
while the boot program is running (after a POR for example)

Memory Mapping 
--------------------
SAM-BA code will be located at 0x0 and executed before any applicative code.

Applications compiled to be executed along with the bootloader will start at
0x4000
Before jumping to the application, the bootloader changes the VTOR register
to use the interrupt vectors of the application @0x4000.<- not required as application code is taking care of this
*/

#include "asf.h"
#include "conf_board.h"
#include "conf_clock.h"
#include <stdio.h>
#include <stdlib.h>

#include "conf_usb.h"
#include "main.h"
#include "sam_ba_monitor.h"
#include "usart_sam_ba.h"


//Init freqm using RCSYS as reference clock
//Measure OSC0 for 1ms (115 cycles of RCSYS)
void init_freqm()
{
	FREQM->MODE = 0;
	while((FREQM->STATUS & FREQM_STATUS_RCLKBUSY)>0);
	FREQM->MODE = FREQM_MODE_REFSEL(FREQM_REF_RCOSC);
	while((FREQM->STATUS & FREQM_STATUS_RCLKBUSY)>0);
	FREQM->MODE = FREQM_MODE_REFSEL(FREQM_REF_RCOSC)|FREQM_MODE_REFCEN;
	while((FREQM->STATUS & FREQM_STATUS_RCLKBUSY)>0);
	FREQM->MODE = FREQM_MODE_REFSEL(FREQM_REF_RCOSC)|FREQM_MODE_REFCEN|
	  		FREQM_MODE_REFNUM(115)|FREQM_MODE_CLKSEL(FREQM_OSC0);
}

//Measure OSC0 for 1ms (115 cycles of RCSYS)
//Frequency is outputted in kHz
uint32_t freqm_measure()
{
	FREQM->CTRL = FREQM_CTRL_START;
	while((FREQM->STATUS & FREQM_STATUS_BUSY)>0);
	return(FREQM->VALUE & FREQM_VALUE_VALUE_Msk);
}

void wait_1_ms(void)
{
  freqm_measure();
}

uint32_t osc0_freq;
int8_t	 i_selected_frequency;
uint8_t  u8_clock_status;
uint8_t  b_usb_clock_available;
uint8_t  b_usb_selected;

//Items type of supported frequencies LUT
typedef struct 
{
	uint32_t expected_measurement;
	uint32_t tolerance;
	uint32_t usbpll_setting;
}st_supported_freq;

//Define LUT with supported frequencies measurements as entry key
//Warning : supported frequencies shall not be too close to each other : 
//a supported frequency is selected automatically after a measurement
//done with an embedded oscillator with limited accuracy : +- 4.25%
// a 5% difference between 2 contiguous frequencies is necessary to cover
// all extreme conditions (temp,voltage)
st_supported_freq tab_supported_freq[] = 
{
     // Expected freq in kHz, Tolerance in kHz,Pll reg value : MUL,DIV,DIV2,Range
	{ 6000, 250,SCIF_PLL_PLLCOUNT_Msk|SCIF_PLL_PLLMUL(15)|SCIF_PLL_PLLDIV(1)|SCIF_PLL_PLLOPT(2)|SCIF_PLL_PLLOSC(0)},
	{ 7372, 300,SCIF_PLL_PLLCOUNT_Msk|SCIF_PLL_PLLMUL(12)|SCIF_PLL_PLLDIV(1)|SCIF_PLL_PLLOPT(2)|SCIF_PLL_PLLOSC(0)},
	{ 8000, 300,SCIF_PLL_PLLCOUNT_Msk|SCIF_PLL_PLLMUL(11)|SCIF_PLL_PLLDIV(1)|SCIF_PLL_PLLOPT(2)|SCIF_PLL_PLLOSC(0)},
	{12000, 550,SCIF_PLL_PLLCOUNT_Msk|SCIF_PLL_PLLMUL( 3)|SCIF_PLL_PLLDIV(0)|SCIF_PLL_PLLOPT(2)|SCIF_PLL_PLLOSC(0)},
	{14745, 600,SCIF_PLL_PLLCOUNT_Msk|SCIF_PLL_PLLMUL(12)|SCIF_PLL_PLLDIV(2)|SCIF_PLL_PLLOPT(2)|SCIF_PLL_PLLOSC(0)},
	{16000, 600,SCIF_PLL_PLLCOUNT_Msk|SCIF_PLL_PLLMUL( 2)|SCIF_PLL_PLLDIV(0)|SCIF_PLL_PLLOPT(2)|SCIF_PLL_PLLOSC(0)},
	{24000,1200,SCIF_PLL_PLLCOUNT_Msk|SCIF_PLL_PLLMUL( 7)|SCIF_PLL_PLLDIV(2)|SCIF_PLL_PLLOPT(2)|SCIF_PLL_PLLOSC(0)}
};

//Clock status flag (bit field)
#define CLOCK_STATUS_EXTCLK			1
#define CLOCK_STATUS_CRYSTAL		2

//simple abs function
uint32_t i32abs(int32_t value)
{
  if(value>0)
    return(value);
  else
    return(-value);
}

//Setup necessary clocks for the bootloader
//Allow USB if one of the supported input frequency is available
void usb_clock_setup(void)
{
  	uint8_t i;
	int32_t delta;
  	//Initialize clock status var
  	u8_clock_status = 0;
	  
	//Start OSC0 in external mode
	SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
		| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->OSCCTRL0 - (uint32_t)SCIF);
	SCIF->OSCCTRL0 = (SCIF_OSCCTRL0_STARTUP(0))|SCIF_OSCCTRL0_OSCEN;

	wait_1_ms();

	//Ext clock should be up and running at boot
	//Test if OSC0 clock is alive
	if((SCIF->PCLKSR&SCIF_PCLKSR_OSC0RDY)>0)
	{
	  	//Ext clock is alive
		u8_clock_status = CLOCK_STATUS_EXTCLK;
	}
	else
	{//Ext clock failed, now let's try crystal mode
		//Start OSC0 in crystal mode
		SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
			| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->OSCCTRL0 - (uint32_t)SCIF);
		SCIF->OSCCTRL0 = SCIF_OSCCTRL0_GAIN(3)|(SCIF_OSCCTRL0_STARTUP(0))|SCIF_OSCCTRL0_OSCEN|SCIF_OSCCTRL0_MODE;
		
		//Wait for oscillation start (up to 100ms for low freqs xtal)
		for(i=0;i<100;i++)
		{
			wait_1_ms();
		}	
		
		//Now the Test if OSC0 clock is alive
		if((SCIF->PCLKSR&SCIF_PCLKSR_OSC0RDY)>0)
		{
			u8_clock_status = CLOCK_STATUS_CRYSTAL;		  
		}
		else
		{
		  //No valid clock found, usb is not allowed, fall back to RCFAST
		  //Only USART will be available
		}
	}
	if((u8_clock_status & (CLOCK_STATUS_CRYSTAL|CLOCK_STATUS_EXTCLK))>0)
	{
		//One of the stable clock is available, measure it
		osc0_freq=freqm_measure();
		
		//No selected frequency
		i_selected_frequency = -1;
	
		//Search closest match in supported frequencies list
		for(i=0;i<(sizeof(tab_supported_freq)/sizeof(st_supported_freq));i++)
		{
		  	delta = tab_supported_freq[i].expected_measurement - osc0_freq;
			if(i32abs(delta)<tab_supported_freq[i].tolerance)
			{//Measurement is close enough, select this frequency
				i_selected_frequency = i;
				break;
			}
		}

		//Forbid USB until we find a suitable clock source
		b_usb_clock_available = false;
		
		//If a know frequencies is found, setup the PLL according to the table
		if(i_selected_frequency>0)
		{
			// Setup PLL with the selected config
			SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
				| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->Pll[0].PLL - (uint32_t)SCIF);
		  	SCIF->Pll[0].PLL = tab_supported_freq[i_selected_frequency].usbpll_setting;
			
			SCIF->UNLOCK = SCIF_UNLOCK_KEY(0xAAUL)
				| SCIF_UNLOCK_ADDR((uint32_t)&SCIF->Pll[0].PLL - (uint32_t)SCIF);
		  	SCIF->Pll[0].PLL = tab_supported_freq[i_selected_frequency].usbpll_setting|SCIF_PLL_PLLEN;
			
			//PLL Lock time should be less than 1 ms
			wait_1_ms();	
			if((SCIF->PCLKSR&SCIF_PCLKSR_PLL0LOCK)>0)
			{
				b_usb_clock_available = true;
			}
		}
	}
}

//Jump in applicative code when needed
void check_start_application(void)
{
	uint32_t * ptr_reset_vector;
	uint32_t * ptr_msp;	
	uint32_t * ptr_configword;		
	uint32_t bootloader_config_word;
	uint32_t app_start_add;	
	uint32_t pin_number;
	uint32_t pin_state;	
	uint8_t i;		
	uint8_t pin_forced_count;
	
	//Config word of the bootloader
	ptr_configword = (uint32_t *) (FLASH_USER_PAGE_ADDR+USERPAGE_CONFWORD_OFFSET);
	bootloader_config_word = (*ptr_configword);
	
	//Get reset vector from intvect table of application
	ptr_reset_vector = (uint32_t *) (APP_START_ADDRESS+4);

	//Test reset vector of application @APP_START_ADDRESS+4
	// Stay in SAM-BA if *(APP_START+0x4) == 0xFFFFFFFF
	//Application erased condition
	if(*ptr_reset_vector==0xFFFFFFFF)
	{
			//Stay in bootloader
			return;
	}
	if((bootloader_config_word&CONFWORD_FORCE_MONITOR_MASK)!=CONFWORD_FORCE_MONITOR_MASK)
	{
		//Check magic value to force monitor mode
		if((bootloader_config_word&CONFWORD_FORCE_MONITOR_MASK)==CONFWORD_FORCE_MONITOR_VALUE)
			return;
		//Expected format : 0xXX XX Xx NN where BIT8 is the active state (bootloader triggered)
		// NN is the GPIO number (ex : PIN_PC31=0x5F (95d))
		pin_number = bootloader_config_word&0xFF;
		pin_state = (bootloader_config_word>>8)&1;
		//Set the selected pin in input mode
		gpio_configure_pin(pin_number,(1<<(pin_number&0x1F)),GPIO_DIR_INPUT);
		//Wait for debounce time : 100ms
		for(i=0;i<100;i++)
			wait_1_ms();		
		//Test pin value on 3 samples
		pin_forced_count = 0;
		for(i=0;i<3;i++)
		{		
			if(gpio_get_pin_value(pin_number)==pin_state)
			{
				pin_forced_count++;
			}
			wait_1_ms();					
		}
		//Majority vote
		if(pin_forced_count>1)
		{
			//Stay in bootloader
			return;
		}
		//Pin not active, move to application
	}
	//None of the trigger conditions is true,
	//Jump in application

	//Put reset vector in function ptr
	//ptrfunc.__ptr = (void*)(*ptr_reset_vector);
	app_start_add = (*ptr_reset_vector);
	//On reset, the processor loads the MSP with the value from address 0x00000000	
	//So before jumping in application, bootloader loads the MSP 
	//with the value from address 0x00004000
	//Execute / jump in application
	ptr_msp = (uint32_t *) (APP_START_ADDRESS);	
	__set_MSP(*(ptr_msp));
	asm("bx %0"::"r"(app_start_add));
}

//Erase the entire application area if part is secured
void erase_secured_device(void)
{
	uint32_t p;		

	//Erase all application pages (monitor not erased)
	//Blank pages are not re-erase to avoid unnecessary wear of the flash
	for(p=APP_START_PAGE;p<flashcalw_get_page_count();p++)
	{
		if(flashcalw_quick_page_read(p)==false)
		{
			//Unlock if page is locked
			if(flashcalw_is_page_region_locked(p))
			{
				flashcalw_lock_page_region(p,false);		
			}
			//Erase & Ensure that page is successfully erased
			while(flashcalw_erase_page(p, true)==0);
		}
	}	
		
}
#if 0
#	define DEBUG_PIN_HIGH 	gpio_set_gpio_pin(PIN_PC13,GPIO_PC13)
#	define DEBUG_PIN_LOW 	gpio_clr_gpio_pin(PIN_PC13,GPIO_PC13)
#else
#	define DEBUG_PIN_HIGH 	do{}while(0)
#	define DEBUG_PIN_LOW 	do{}while(0)
#endif

static volatile bool main_b_cdc_enable = false;

/**
 *  \brief SAM4L SAM-BA Main loop.
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	volatile uint32_t tmp,u32;
	
	DEBUG_PIN_HIGH;		
	
	//Start FREQM, 	
	init_freqm();

	//Jump in application if condition is satisfied
	check_start_application();
	
	
	//Enable necessary clocks for monitor
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBAMASK - (uint32_t)PM);
	PM->PBAMASK = PM_PBAMASK_USART0;

	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBBMASK - (uint32_t)PM);
	PM->PBBMASK = PM_PBBMASK_HFLASHC|PM_PBBMASK_USBC;

	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBCMASK - (uint32_t)PM);
	PM->PBCMASK = PM_PBCMASK_PM|PM_PBCMASK_CHIPID|PM_PBCMASK_SCIF|
	  		PM_PBCMASK_FREQM|PM_PBCMASK_GPIO;
	
	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->PBDMASK - (uint32_t)PM);
	PM->PBDMASK = PM_PBDMASK_BPM|PM_PBDMASK_BSCIF|PM_PBDMASK_AST|
	  		PM_PBDMASK_WDT|PM_PBDMASK_EIC|PM_PBDMASK_PICOUART;

	PM->UNLOCK = PM_UNLOCK_KEY(0xAAUL)
		| PM_UNLOCK_ADDR((uint32_t)&PM->HSBMASK - (uint32_t)PM);
	PM->HSBMASK = PM_HSBMASK_USBC |	PM_HSBMASK_HFLASHC| PM_HSBMASK_HTOP0|
	  		PM_HSBMASK_HTOP1|PM_HSBMASK_HTOP2|PM_HSBMASK_HTOP3;
	
	DEBUG_PIN_LOW;			

	//Erase the entire application area if part is secured
	if(flashcalw_is_security_bit_active())
	{
		//Tested ok
		erase_secured_device();
	}
	DEBUG_PIN_HIGH;		
	//We have determined we should stay in the monitor,
	//Start SAM-BA init 
	
	//Switch to RCFAST
	osc_enable(OSC_ID_RCFAST);
	osc_wait_ready(OSC_ID_RCFAST);   
	sysclk_set_source(SYSCLK_SRC_RCFAST);
	
	DEBUG_PIN_LOW;			
	// Place XIN and XOUT as input before enabling SCIF.OSC0
	gpio_configure_pin (PIN_PA00, (1<<(PIN_PA00%32)), (GPIO_DIR_INPUT));
	gpio_configure_pin (PIN_PA01, (1<<(PIN_PA01%32)), (GPIO_DIR_INPUT));

	DEBUG_PIN_HIGH;		
	//Check available clock source for usb operation
	usb_clock_setup();
	DEBUG_PIN_LOW;			
	if(b_usb_clock_available)
	{
		//Enable pins for USB
		gpio_enable_module_pin (PIN_PA25A_USBC_DM, GPIO_PA25A_USBC_DM, MUX_PA25A_USBC_DM);	
		gpio_enable_module_pin (PIN_PA26A_USBC_DP, GPIO_PA26A_USBC_DP, MUX_PA26A_USBC_DP);	
		// Start USB stack 
		udc_start();
		// VBUS monitoring has no dedicated pin
		// so VBUS has to be considered as present
		udc_attach();
	}
	DEBUG_PIN_HIGH;		
	//Enable RX pins for USART2	
	gpio_enable_module_pin (PIN_PA05B_USART0_RXD, GPIO_PA05B_USART0_RXD, MUX_PA05B_USART0_RXD);	
	//UART is enabled in all cases
	usart_open(CONF_SAMBA_INSTANCE_USART,CONF_SAMBA_SPEED_USART,OSC_RCFAST12M_NOMINAL_HZ);
	
	b_usb_selected = false;
	DEBUG_PIN_LOW;		
	//Wait for a complete enum on usb or a '#' char on serial line
	while(1)
	{
		//Check if a USB enumeration has succeeded
		//And com port was opened
		if(main_b_cdc_enable)
		{
			sam_ba_monitor_init(SAM_BA_INTERFACE_USBCDC);			
			b_usb_selected = true;
			//SAM-BA on USB loop
			while(1)
			{
				sam_ba_monitor_run();
			}
		}
		//Check if a '#' has been received
		if(usart_sharp_received())
		{
			gpio_enable_module_pin (PIN_PA07B_USART0_TXD, GPIO_PA07B_USART0_TXD, MUX_PA07B_USART0_TXD);	
			sam_ba_monitor_init(SAM_BA_INTERFACE_USART);
		  	//SAM-BA on UART loop	  
			while(1)
			{
				sam_ba_monitor_run();
			}
		}
	}
}

bool main_cdc_enable(uint8_t port)
{
	main_b_cdc_enable = true;
	return true;
}

void main_cdc_disable(uint8_t port)
{
	main_b_cdc_enable = false;
}

void main_cdc_set_dtr(uint8_t port, bool b_enable)
{
}

void main_cdc_rx_notify(uint8_t port)
{
}

void main_cdc_set_coding(uint8_t port, usb_cdc_line_coding_t * cfg)
{
}
