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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "../common/applet.h"
#include <board.h>
#include <pmc/pmc.h>
#include <board_lowlevel.h>
#include <board_memories.h>
#include <pio/pio.h>
#include <dbgu/dbgu.h>
#include <utility/assert.h>
#include <utility/trace.h>

#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
/* Initialization mode */
#define EK_MODE                 ((unsigned int) 0x00000000)
#define USER_DEFINED_CRYSTAL    ((unsigned int) 0x00000001)
#define BYPASS_MODE             ((unsigned int) 0x00000002)

#define CLOCK_CONFIGURE_DISABLE  0
#define CLOCK_CONFIGURE_ENABLE   1

#define N_BITS                    8
#define AT91C_2MHz                (2000000)
#define AT91C_3MHz                (3000000)
#define AT91C_6MHz                (6000000)
#define AT91C_8MHz                (8000000)
#define AT91C_12MHz               (12000000)
#define AT91C_15MHz               (15000000)
#define AT91C_20MHz               (20000000)
#define AT91C_28MHz               (28000000)
#define AT91C_50MHz               (50000000)

/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/
/** 
 * \brief Structure for storing parameters for each command that can be performed by the applet.
 */
struct _Mailbox {

    /* Command send to the monitor to be executed. */
    unsigned int command;
    /* Returned status, updated at the end of the monitor execution. */
    unsigned int status;

    /* Input Arguments in the argument area */
    union {

        /* Input arguments for the Init command. */
        struct {

            /* Communication link used. */
            unsigned int comType;
            /* Trace level. */
            unsigned int traceLevel;
            /* Low initialization mode */
            unsigned int Mode;
            /* frequency of user-defined crystal */
            unsigned int crystalFreq;
            /* frequency of external clock in bypass mode */
            unsigned int extClk;

        } inputInit;

        /* Output arguments for the Init command. */
        /* None */

        /* Input arguments for the Write command. */
        /* None */

        /* Output arguments for the Write command. */
        /* None */

        /* Input arguments for the Read command. */
        /* None */

        /* Output arguments for the Read command. */
        /* None */

        /* Input arguments for the Full Erase command. */
        /* NONE */

        /* Output arguments for the Full Erase command. */
        /* NONE */

        /* Input arguments for the Buffer Erase command. */
        /* None */

        /* Output arguments for the Buffer Erase command. */
        /* NONE */
    } argument;
};

unsigned int mul, div, usbdiv, pllout, prescaler, mdiv, plldiv2, mck;

static unsigned int user_Configrue_pll (unsigned int crystalFreq)
{

    mck = BOARD_MCK;
#if defined (at91sam7s) || defined (at91sam7l) || defined (at91sam7se) || defined (at91sam7x) ||\
    defined (at91sam7a3) || defined (at91cap9) || defined (at91sam7sl)
    return 1;
#else
    prescaler = AT91C_PMC_PRES_CLK;
#if defined AT91C_PMC_MDIV_2
    mdiv = AT91C_PMC_MDIV_2;
#endif
    plldiv2 = 0;
#endif

#if defined (at91sam3u)
    prescaler = AT91C_PMC_PRES_CLK_2;
    mdiv = 0;
    plldiv2 = 0;
#endif

#if defined (at91sam9261) || defined (at91sam9g10)|| defined (at91sam9263) ||\
    defined (at91sam9g20) || defined (at91sam9260) || defined (at91sam9xe)
    usbdiv = 0; 
#if defined (at91sam9g20)
    prescaler = AT91C_PMC_PRES_CLK_4; 
    mdiv = AT91C_PMC_MDIV_4; 
#endif
    switch (crystalFreq) {
#if defined (at91sam9260) || defined (at91sam9xe) 
        case 3000000:   mul = 32;  div = 1;  pllout = 0; break;
        case 3276800:   mul = 88;  div = 3;  pllout = 0; break;
        case 3686400:   mul = 26;  div = 1;  pllout = 0; break;
        case 3840000:   mul = 50;  div = 2;  pllout = 0; break;
        case 4000000:   mul = 48;  div = 2;  pllout = 0; break;
        case 4433619:   mul = 65;  div = 3;  pllout = 0; break;
        case 4915200:   mul = 39;  div = 2;  pllout = 0; break;
        case 5000000:   mul = 96;  div = 5;  pllout = 0; break;
        case 5242880:   mul = 55;  div = 3;  pllout = 0; break;
        case 6000000:   mul = 48;  div = 3;  pllout = 0; break;
        case 6144000:   mul = 78;  div = 5;  pllout = 0; break;
        case 6400000:   mul = 45;  div = 3;  pllout = 0; break;
        case 6553600:   mul = 44;  div = 3;  pllout = 0; break;
        case 7159090:   mul = 67;  div = 5;  pllout = 0; break;
        case 7372800:   mul = 39;  div = 3;  pllout = 0; break;
        case 7864320:   mul = 61;  div = 5;  pllout = 0; break;
        case 8000000:   mul = 48;  div = 4;  pllout = 0; break;
        case 9830400:   mul = 88;  div = 9;  pllout = 0; break;
        case 10000000:  mul = 48;  div = 5;  pllout = 0; break;
        case 11059200:  mul = 52;  div = 6;  pllout = 0; break;
        case 12000000:  mul = 48;  div = 6;  pllout = 0; break;
        case 12288000:  mul = 86;  div = 11; pllout = 0; break;
        case 13560000:  mul = 92;  div = 13; pllout = 0; break;
        case 14318180:  mul = 67;  div = 10; pllout = 0; break;
        case 14745600:  mul = 39;  div = 6;  pllout = 0; break;
        case 16000000:  mul = 48;  div = 8;  pllout = 0; break;
        case 16367667:  mul = 88;  div = 15; pllout = 0; break;
        case 17734470:  mul = 92;  div = 17; pllout = 0; break;
        case 18432000:  mul = 73;  div = 14; pllout = 0; break;
        case 20000000:  mul = 48;  div = 10; pllout = 0; break;
                                                               
#endif                                                         
                                                               
#if defined (at91sam9g20)                                      
        case 3686400:   mul = 26*8;  div = 1;  pllout = 0; break;
        case 3840000:   mul = 25*8;  div = 1;  pllout = 0; break;
        case 4000000:   mul = 24*8;  div = 1;  pllout = 0; break;
        case 5000000:   mul = 19*8;  div = 1;  pllout = 0; break;
        case 5242880:   mul = 37*4;  div = 1;  pllout = 0; break;
        case 6000000:   mul = 16*8;  div = 1;  pllout = 0; break;
        case 6400000:   mul = 15*8;  div = 1;  pllout = 0; break;
        case 7372800:   mul = 13*8;  div = 1;  pllout = 0; break;
        case 8000000:   mul = 12*8;  div = 1;  pllout = 0; break;
        case 11059200:  mul = 26*8;  div = 3;  pllout = 0; break;
        case 12000000:  mul = 8*8;   div = 1;  pllout = 0; break;
        case 13560000:  mul = 7*8;   div = 1;  pllout = 0; break;
        case 14745600:  mul = 13*8;  div = 2;  pllout = 0; break;
        case 16000000:  mul = 6*8;   div = 1;  pllout = 0; break;
        case 17734470:  mul = 27*8;  div = 5;  pllout = 0; break;
        case 18432000:  mul = 26*8;  div = 5;  pllout = 0; break;
        case 20000000:  mul = 24*8;  div = 5;  pllout = 0; break;
#endif                                                         
                                                               
#if defined (at91sam9261) || defined (at91sam9g10)             
        case 3000000:   mul = 32;  div = 1;  pllout = 0; break;
        case 3276800:   mul = 88;  div = 3;  pllout = 0; break;
        case 3686400:   mul = 26;  div = 1;  pllout = 0; break;
        case 3840000:   mul = 25;  div = 1;  pllout = 0; break;
        case 4000000:   mul = 24;  div = 1;  pllout = 0; break;
        case 4433619:   mul = 65;  div = 3;  pllout = 0; break;
        case 4608000:   mul = 104; div = 5;  pllout = 0; break;
        case 4915200:   mul = 39;  div = 2;  pllout = 0; break;
        case 5000000:   mul = 96;  div = 5;  pllout = 0; break;
        case 5242880:   mul = 55;  div = 3;  pllout = 0; break;
        case 6000000:   mul = 16;  div = 1;  pllout = 0; break;
        case 6144000:   mul = 78;  div = 5;  pllout = 0; break;
        case 6400000:   mul = 15;  div = 1;  pllout = 0; break;
        case 6553600:   mul = 44;  div = 3;  pllout = 0; break;
        case 7159090:   mul = 67;  div = 5;  pllout = 0; break;
        case 7372800:   mul = 13;  div = 1;  pllout = 0; break;
        case 7864320:   mul = 61;  div = 5;  pllout = 0; break;
        case 8000000:   mul = 12;  div = 1;  pllout = 0; break;
        case 9830400:   mul = 88;  div = 9;  pllout = 0; break;
        case 10000000:  mul = 48;  div = 5;  pllout = 0; break;
        case 11059200:  mul = 26;  div = 3;  pllout = 0; break;
        case 12000000:  mul = 8;   div = 1;  pllout = 0; break;
        case 12288000:  mul = 86;  div = 11; pllout = 0; break;
        case 13560000:  mul = 92;  div = 13; pllout = 0; break;
        case 14318180:  mul = 67;  div = 10; pllout = 0; break;
        case 14745600:  mul = 13;  div = 2;  pllout = 0; break;
        case 16000000:  mul = 6;   div = 1;  pllout = 0; break;
        case 17734470:  mul = 92;  div = 17; pllout = 0; break;
        case 18432000:  mul = 73;  div = 14; pllout = 0; break;
        case 20000000:  mul = 24;  div = 5;  pllout = 0; break;
#endif                                                         
                                                               
#if defined (at91sam9263)                                      
        case 3000000:   mul = 32;  div = 1;  pllout = 0; break;
        case 3276800:   mul = 88;  div = 3;  pllout = 0; break;
        case 3686400:   mul = 26;  div = 1;  pllout = 0; break;
        case 3840000:   mul = 25;  div = 1;  pllout = 0; break;
        case 4000000:   mul = 24;  div = 1;  pllout = 0; break;
        case 4433619:   mul = 65;  div = 3;  pllout = 0; break;
        case 4608000:   mul = 104; div = 5;  pllout = 0; break;
        case 4915200:   mul = 39;  div = 2;  pllout = 0; break;
        case 5000000:   mul = 96;  div = 5;  pllout = 0; break;
        case 5242880:   mul = 55;  div = 3;  pllout = 0; break;
        case 6000000:   mul = 16;  div = 1;  pllout = 0; break;
        case 6144000:   mul = 78;  div = 5;  pllout = 0; break;
        case 6400000:   mul = 15;  div = 1;  pllout = 0; break;
        case 6553600:   mul = 44;  div = 3;  pllout = 0; break;
        case 7159090:   mul = 67;  div = 5;  pllout = 0; break;
        case 7372800:   mul = 13;  div = 1;  pllout = 0; break;
        case 7864320:   mul = 61;  div = 5;  pllout = 0; break;
        case 8000000:   mul = 12;  div = 1;  pllout = 0; break;
        case 9830400:   mul = 88;  div = 9;  pllout = 0; break;
        case 10000000:  mul = 48;  div = 5;  pllout = 0; break;
        case 11059200:  mul = 26;  div = 3;  pllout = 0; break;
        case 12000000:  mul = 8;   div = 1;  pllout = 0; break;
        case 12288000:  mul = 86;  div = 11; pllout = 0; break;
        case 13000000:  mul = 96;  div = 13; pllout = 0; break;
        case 16367667:  mul = 88;  div = 15; pllout = 0; break;
        case 17734470:  mul = 92;  div = 17; pllout = 0; break;
        case 18432000:  mul = 73;  div = 14; pllout = 0; break;
        case 20000000:  mul = 24;  div = 5;  pllout = 0; break;
        case 24000000:  mul = 4;   div = 1;  pllout = 0; break;
        case 25000000:  mul = 96;  div = 25; pllout = 0; break;
        case 26000000:  mul = 48;  div = 13; pllout = 0; break;
        case 28224000:  mul = 17;  div = 5;  pllout = 0; break;
        case 32000000:  mul = 3;   div = 1;  pllout = 0; break;
        case 33000000:  mul = 32;  div = 11; pllout = 0; break;
        case 40000000:  mul = 24;  div = 10; pllout = 0; break;
#endif                                                         
                                                               
        default : return 1;                                    
    }                                                          
                                                               
    mck = ((crystalFreq * mul) / div ) / 2;                    
#endif                                                         
                                                               
#if defined (at91sam9m10)                                      
     if (crystalFreq == 12000000) {                            
         mul = 200;   div = 3;  mdiv = AT91C_PMC_MDIV_3;       
         prescaler = AT91C_PMC_PRES_CLK; plldiv2 = AT91C_PMC_PLLADIV2_2;
     }                                                         
#endif                                                         
                                                               
#if defined (at91sam9rl)                                       
     if (crystalFreq != AT91C_12MHz ) return 1;                
     mul = 8;  div = 1;                                        
     prescaler = AT91C_PMC_PRES_CLK;                           
     mdiv = AT91C_PMC_MDIV_2;                                  
     plldiv2 = 0;                                              
     mck = ((crystalFreq * mul) / div ) / 2;                   
#endif                                                         
    return 0;                                                  
}                                                              
                                                               
/**                                                            
 * \brief  Configure the PMC if the frequency of the external oscillator is different from the one mounted on EK
 * \param crystalFreq  The frequency of the external oscillator
 */                                                            
static unsigned int user_defined_LowlevelInit (unsigned int crystalFreq, unsigned int oscBypass)
{                                                              
    pllConfiguration pll;                                      
    mckrConfiguration mckr;                                    
                                                               
    if (user_Configrue_pll(crystalFreq)) return 1;             
#if defined (at91sam9261) || defined (at91sam9g10)|| defined (at91sam9263) || defined (at91sam9m10) || defined (at91sam9g45)
    // Switch MCK to Slow clock                                
    if (!oscBypass) {                                          
        PMC_SwitchMck2SlowClock();                             
    }                                                          
#endif                                                         
    if (!oscBypass) {                                          
        //  enable Main oscillator                             
        PMC_EnableMainOsc();                                   
    }                                                          
    else {                                                     
        PMC_BypassMainOsc();                                   
    }                                                          
    pll.mul = mul;  pll.div = div; pll.usbdiv = usbdiv; pll.pllout = pllout;
    mckr.prescaler = prescaler; mckr.mdiv = mdiv; mckr.plldiv2 = plldiv2;
    PMC_ConfigureMckWithPlla(&pll, &mckr);                     
    LowLevelInit(CLOCK_CONFIGURE_DISABLE);                     
    return 0;                                                  
}                                                              
                                                               
/*----------------------------------------------------------------------------
 *         Global functions                                    
 *----------------------------------------------------------------------------*/
/**                                                            
 * \brief  Applet main entry. This function decodes received command and executes it.
 *                                                             
 * \param argc  always 1                                       
 * \param argv  Address of the argument area..                 
 */                                                            
int main(int argc, char **argv)                                
{                                                              
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;      
    unsigned int mode, crystalFreq, extClk, comType;           
    mck = BOARD_MCK;                                           
    mode = pMailbox->argument.inputInit.Mode;                  
    crystalFreq = pMailbox->argument.inputInit.crystalFreq;    
    extClk = pMailbox->argument.inputInit.extClk;              
    comType = pMailbox->argument.inputInit.comType;            
                                                               
    switch (mode) {                                            
        case EK_MODE:                                          
            LowLevelInit(CLOCK_CONFIGURE_ENABLE);              
            pMailbox->status = APPLET_SUCCESS;                 
            break;                                             
        case USER_DEFINED_CRYSTAL:                             
            if (user_defined_LowlevelInit(crystalFreq, 0)) {   
                 pMailbox->status = APPLET_DEV_UNKNOWN;        
            } else {                                           
                 pMailbox->status = APPLET_SUCCESS;            
            }                                                  
            break;                                             
        case BYPASS_MODE:                                      
#if defined( at91sam9261) || defined( at91sam9g10)             
            pMailbox->status = APPLET_DEV_UNKNOWN;             
            break;                                             
#endif                                                         
            if ( user_defined_LowlevelInit(extClk, 1)) {       
                 pMailbox->status = APPLET_DEV_UNKNOWN;        
            } else {                                           
                 pMailbox->status = APPLET_SUCCESS;            
            }                                                  
            break;                                             
        default:                                               
            pMailbox->status = APPLET_DEV_UNKNOWN;             
            break;                                             
    }                                                          
    DBGU_Configure(DBGU_STANDARD, 115200, mck);                
                                                               
    /* Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);                  
    /* Send ACK character */                                   
    if (comType == DBGU_COM_TYPE) {                            
        DBGU_PutChar(0x6);                                     
    }                                                          
                                                               
    return 0;                                                  
}                                                              
                                                               
                                                               