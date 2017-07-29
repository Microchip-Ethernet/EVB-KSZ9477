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
//         Headers
//------------------------------------------------------------------------------

#include "board.h"
#include "board_memories.h"
#include <pio/pio.h>
#include <utility/trace.h>
#include <pmc/pmc.h>

//------------------------------------------------------------------------------
//         Internal definitions
//------------------------------------------------------------------------------
/*
    Constants: Clock and PLL settings

        BOARD_OSCOUNT - Startup time of main oscillator (in number of slow clock
                        ticks). 
        BOARD_USBDIV - USB PLL divisor value to obtain a 48MHz clock.
        BOARD_CKGR_PLL - PLL frequency range.
        BOARD_PLLCOUNT - PLL startup time (in number of slow clock ticks).
        BOARD_MUL - PLL MUL value.
        BOARD_DIV - PLL DIV value.
        BOARD_PRESCALER - Master clock prescaler value.
*/
#define BOARD_OSCOUNT           (AT91C_CKGR_OSCOUNT & (64 << 8))

#define BOARD_CKGR_PLLA         (AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_2)
#define BOARD_PLLACOUNT         (63 << 8)                               // maximum
#define BOARD_MULA              (AT91C_CKGR_MULA & (49 << 16))
#define BOARD_DIVA              (AT91C_CKGR_DIVA & 3)

#define BOARD_USBDIV            AT91C_CKGR_USBDIV_2
#define BOARD_CKGR_PLLB         AT91C_CKGR_OUTB_0
#define BOARD_PLLBCOUNT         BOARD_PLLACOUNT
#define BOARD_MULB              (175 << 16)
#define BOARD_DIVB              15

#define BOARD_PRESCALER         AT91C_PMC_MDIV_2

//------------------------------------------------------------------------------
//         Internal functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// Default spurious interrupt handler. Infinite loop.
//------------------------------------------------------------------------------
void defaultSpuriousHandler( void )
{
    //while (1);
}

//------------------------------------------------------------------------------
/// Default handler for fast interrupt requests. Infinite loop.
//------------------------------------------------------------------------------
void defaultFiqHandler( void )
{
    while (1);
}

//------------------------------------------------------------------------------
/// Default handler for standard interrupt requests. Infinite loop.
//------------------------------------------------------------------------------
void defaultIrqHandler( void )
{
    while (1);
}


/// Slave address of AT73C223 chips.
#define AT73C223_SLAVEADDRESS_U4   0x48    // 1001000
#define AT73C223_SLAVEADDRESS_U5   0x49    // 1001001

//------------------------------------------------------------------------------
/// Initialize AT73C224
//------------------------------------------------------------------------------
static void BOARD_AT73C224_initialize(void)
{
    /// configure Pio pins
    static const Pin pinTWI[] = {PINS_TWI};  
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_TWI;
    PIO_Configure(pinTWI, 1);
    
    // Reset the TWI
    AT91C_BASE_TWI->TWI_CR = AT91C_TWI_SWRST;
    // Set master mode
    AT91C_BASE_TWI->TWI_CR = AT91C_TWI_MSEN;
    // Set Clock Waveform Generator Register
    // MCK  = 100000000
    // TWCK = 400000
    AT91C_BASE_TWI->TWI_CWGR = 0x00007A7A;    
}

//------------------------------------------------------------------------------
/// Read data from AT73C224
//------------------------------------------------------------------------------
static void BOARD_AT73C224_Read(
    unsigned char *pByte,
    unsigned char registerAddress,
    unsigned char address
    )
{
    // Set STOP signal if only one byte is sent
    //--------------------------------------------------------------------------  
    AT91C_BASE_TWI->TWI_CR = AT91C_TWI_STOP;

    // Start read
    //--------------------------------------------------------------------------
    // Set slave address and number of internal address bytes
    AT91C_BASE_TWI->TWI_MMR = (1 << 8) | AT91C_TWI_MREAD | (address << 16);
    // Set internal address bytes
    AT91C_BASE_TWI->TWI_IADR = registerAddress;
    // Send START condition
    AT91C_BASE_TWI->TWI_CR = AT91C_TWI_START;
    
    // Read all bytes, setting STOP before the last byte
    //--------------------------------------------------------------------------    
    AT91C_BASE_TWI->TWI_CR = AT91C_TWI_STOP;

    // Wait for byte then read and store it
    //--------------------------------------------------------------------------    
    while (! ((AT91C_BASE_TWI->TWI_SR & AT91C_TWI_RXRDY) == AT91C_TWI_RXRDY)) ;
    //(unsigned char)*buffer = AT91C_BASE_TWI->TWI_RHR;
    *pByte = AT91C_BASE_TWI->TWI_RHR;
    
    // Wait for transfer to be complete
    //--------------------------------------------------------------------------    
    while (! ((AT91C_BASE_TWI->TWI_SR & AT91C_TWI_TXCOMP_MASTER) == AT91C_TWI_TXCOMP_MASTER));
}

//------------------------------------------------------------------------------
/// Write data to AT73C224
//------------------------------------------------------------------------------
static void BOARD_AT73C224_Write(
    unsigned char byte,
    unsigned char registerAddress,
    unsigned char address
    )
{
    // Set slave address and number of internal address bytes
    AT91C_BASE_TWI->TWI_MMR = (1 << 8) | (address << 16);
    // Set internal address bytes
    AT91C_BASE_TWI->TWI_IADR = registerAddress;
    // Write the byte
    AT91C_BASE_TWI->TWI_THR = byte;
    
    // Wait for transfer to be complete
    while (! ((AT91C_BASE_TWI->TWI_SR & AT91C_TWI_TXCOMP_MASTER) == AT91C_TWI_TXCOMP_MASTER));
}

//------------------------------------------------------------------------------
/// Power configuration
//------------------------------------------------------------------------------
static unsigned char configure_AT73C224(void)
{
    unsigned char buff;

    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);
    //TRACE_INFO("configure_AT73C224\n\r");
    
    BOARD_AT73C224_initialize();

    // Check that we are communicating with the good device
    BOARD_AT73C224_Read(&buff, 0x01, AT73C223_SLAVEADDRESS_U4);
    //TRACE_INFO("device adresse = 0x%X\n\r", buff);
    if(buff != 0x48) {

        TRACE_ERROR("Wrong device adressed\n\r");
        return 0;
    }
    // Check that the BUCK default voltage is 0x09 (1.8V)
    BOARD_AT73C224_Read(&buff, 0x15, AT73C223_SLAVEADDRESS_U4);   // BCK_VOLT : 0x15 ;
    //TRACE_INFO("BCK_VOLT = 0x%X\n\r", buff);
    if(buff != 0x09) {

        TRACE_ERROR("Wrong default output voltage\r\n");
        return 0;
    }

    // Check that the BUCK converter is started
    BOARD_AT73C224_Read(&buff, 0x13, AT73C223_SLAVEADDRESS_U4);  // BCK_CTRL : 0x13 ;
    //TRACE_INFO("BCK_CTRL = 0x%X\n\r", buff);
    if(buff != 0x01) {

        TRACE_ERROR("BUCK converter is started\n\r");
        return 0;
    }

    // Check that all interrupts are masked
    BOARD_AT73C224_Read(&buff, 0x32, AT73C223_SLAVEADDRESS_U4);  // IRQ_MSK : 0x32 ;
    //TRACE_INFO("IRQ_MSK = 0x%X\n\r", buff);
    if(buff != 0x00) {

        TRACE_ERROR("not all interrupts are masked\n\r");
        return 0;
    }

    // Check that the boost output voltage is configured in 5V mode
    BOARD_AT73C224_Read(&buff, 0x12, AT73C223_SLAVEADDRESS_U4);   // BST_VOLT : 0x12 ;
    //TRACE_INFO("BST_VOLT = 0x%X\n\r", buff);
    // resut: BST_VOLT = 0x28

    // Check that the current limitation is not too low
    BOARD_AT73C224_Read(&buff, 0x11, AT73C223_SLAVEADDRESS_U4);   // BST_CFG : 0x11 ;
    //TRACE_INFO("BST_CFG = 0x%X\n\r", buff);
    // result: BST_CFG = 0x1B
    if(buff < 0x01) {

        TRACE_ERROR("Too low current limitation\n\r");
        return 0;
    }

    // Setting the ramp for optimal operation for the application CAP
    BOARD_AT73C224_Write(0x40, 0x72, AT73C223_SLAVEADDRESS_U4);   // RTRIM : 0x72 ;

    // 0x0B @ 0x11 : on 2 chips
    BOARD_AT73C224_Write(0x0B, 0x11, AT73C223_SLAVEADDRESS_U4);
    BOARD_AT73C224_Write(0x0B, 0x11, AT73C223_SLAVEADDRESS_U5);

    // Passage of Buck in PWM mode
    // Write 0xD8 @ 0x14           
    BOARD_AT73C224_Write(0xD8, 0x14, AT73C223_SLAVEADDRESS_U4);

    // Setting the ramp for optimal operation for the application CAP
    BOARD_AT73C224_Write(0x40, 0x72, AT73C223_SLAVEADDRESS_U5);   // RTRIM : 0x72 ;

    // Passage of Buck in PWM mode
    // Write 0xD8 @ 0x14                 
    BOARD_AT73C224_Write(0xD8, 0x14, AT73C223_SLAVEADDRESS_U5);

    // Init for USB Host
    /*
    // At the start-up, it is recommended to put 1Amp over current threshold 
    // in order not to generate a reset of the product.
    BOARD_AT73C224_Write(0x01, 0x11, AT73C223_SLAVEADDRESS_U4);

    // setting VBOOST = 5V
    BOARD_AT73C224_Write(0x28, 0x12, AT73C223_SLAVEADDRESS_U4);

    // Start VBOOST
    BOARD_AT73C224_Write(0x01, 0x10, AT73C223_SLAVEADDRESS_U4);

    // put 6Amp over current threshold.
    BOARD_AT73C224_Write(0x0B, 0x11, AT73C223_SLAVEADDRESS_U4);
    */

    return 1;
}

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
///    Performs the low-level initialization of the chip.
//------------------------------------------------------------------------------
void LowLevelInit(unsigned int clockConfigEnable)
{
    unsigned char i;
    if (clockConfigEnable)
    {
        // Initialize main oscillator
        AT91C_BASE_PMC->PMC_MOR = BOARD_OSCOUNT | AT91C_CKGR_MOSCEN;
        // Wait the main oscillator stabilization
        while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCS));
        // Initialize PLLA at 200MHz
        AT91C_BASE_PMC->PMC_PLLAR = BOARD_CKGR_PLLA
                                    | BOARD_PLLACOUNT
                                    | BOARD_MULA
                                    | BOARD_DIVA;
        // Wait the PLLA locking
        while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKA));
        // Wait for the master clock if it was already initialized
        while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY));

        // Set Master Clock Division only (before select the clock)
        // Processor clock = PLLA (200 MHz)
        // Master clock    = PLLA / 2 (100 MHz)   
        AT91C_BASE_PMC->PMC_MCKR = AT91C_PMC_CSS_SLOW_CLK | AT91C_PMC_PRES_CLK | AT91C_PMC_MDIV_2;
        while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY));

        // Select PLLA
        AT91C_BASE_PMC->PMC_MCKR = AT91C_PMC_CSS_PLLA_CLK | AT91C_PMC_PRES_CLK | AT91C_PMC_MDIV_2;
        while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY));
    }
    /* Initialize AIC
     ****************/
    AT91C_BASE_AIC->AIC_IDCR = 0xFFFFFFFF;
    AT91C_BASE_AIC->AIC_SVR[0] = (unsigned int) defaultFiqHandler;
    for (i = 1; i < 31; i++) {

        AT91C_BASE_AIC->AIC_SVR[i] = (unsigned int) defaultIrqHandler;
    }
    AT91C_BASE_AIC->AIC_SPU = (unsigned int) defaultSpuriousHandler;

    // Unstack nested interrupts
    for (i = 0; i < 8 ; i++) {

        AT91C_BASE_AIC->AIC_EOICR = 0;
    }

    /* Watchdog initialization
     *************************/
    AT91C_BASE_WDTC->WDTC_WDMR = AT91C_WDTC_WDDIS;

    /* Remap
     *******/
    BOARD_RemapRam();   
    
    configure_AT73C224();
}

