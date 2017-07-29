/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation
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

/** \file */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "chip.h"

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures a list of Pin instances, each of which can either hold a single
 * pin or a group of pins, depending on the mask value; all pins are configured
 * by this function. The size of the array must also be provided and is easily
 * computed using PIO_LISTSIZE whenever its length is not known in advance.
 *
 * \param list  Pointer to a list of Pin instances.
 * \param size  Size of the Pin list (calculated using PIO_LISTSIZE).
 *
 * \return 1 if the pins have been configured properly; otherwise 0.
 */
extern uint32_t PIO_PinConfigure( const Pin* pPins, uint32_t dwSize )
{
    uint32_t dwOptions=0 ;

    /* Configure pins */
    while ( dwSize > 0 )
    {
        switch ( pPins->type )
        {
            case PIO_PERIPH_A :
                if ( pPins->attribute & PIO_PULLUP )
                {
                    dwOptions=PIO_PULLUP ;
                }

                PIO_SetPeripheralA( pPins->pio, pPins->mask, dwOptions ) ;
            break ;

            case PIO_PERIPH_B :
                if ( pPins->attribute & PIO_PULLUP )
                {
                    dwOptions=PIO_PULLUP ;
                }

                PIO_SetPeripheralB( pPins->pio, pPins->mask, dwOptions ) ;
            break ;

            case PIO_INPUT :
                PMC_EnablePeripheral( pPins->id ) ;
                PIO_SetInput( pPins->pio, pPins->mask, pPins->attribute ) ;
            break ;

            case PIO_OUTPUT_0 :
            case PIO_OUTPUT_1 :
                if ( pPins->type == PIO_OUTPUT_1 )
                {
                    dwOptions|=PIO_OUTPUT_HIGH ;
                }

                if ( pPins->attribute & PIO_OPENDRAIN )
                {
                    dwOptions|=PIO_OPENDRAIN ;
                }

                if ( pPins->attribute & PIO_PULLUP )
                {
                    dwOptions|=PIO_PULLUP ;
                }

                PIO_SetOutput( pPins->pio, pPins->mask, dwOptions ) ;
            break ;

            default :
                return 0 ;
        }

        pPins++ ;
        dwSize-- ;
    }

    return 1 ;
}

/**
 * \brief Sets a high output level on all the PIOs defined in the given Pin instance.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will memorize the value they are changed to outputs.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
extern void PIO_PinSet( const Pin* pPin )
{
    pPin->pio->PIO_SODR = pPin->mask ;
}

/**
 * \brief Sets a low output level on all the PIOs defined in the given Pin instance.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will memorize the value they are changed to outputs.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
extern void PIO_PinClear( const Pin* pPin )
{
    pPin->pio->PIO_CODR = pPin->mask ;
}

/**
 * \brief Returns 1 if one or more PIO of the given Pin instance currently have
 * a high level; otherwise returns 0. This method returns the actual value that
 * is being read on the pin. To return the supposed output value of a pin, use
 * PIO_GetOutputDataStatus() instead.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 *
 * \return 1 if the Pin instance contains at least one PIO that currently has
 * a high level; otherwise 0.
 */
extern uint32_t PIO_PinGet( const Pin* pPin )
{
    uint32_t dwReg ;

    if ( (pPin->type == PIO_OUTPUT_0) || (pPin->type == PIO_OUTPUT_1) )
    {
        dwReg = pPin->pio->PIO_ODSR ;
    }
    else
    {
        dwReg = pPin->pio->PIO_PDSR ;
    }

    if ( (dwReg & pPin->mask) == 0 )
    {
        return 0 ;
    }
    else
    {
        return 1 ;
    }
}

/**
 * \brief Returns 1 if one or more PIO of the given Pin are configured to output a
 * high level (even if they are not output).
 * To get the actual value of the pin, use PIO_Get() instead.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 *
 * \return 1 if the Pin instance contains at least one PIO that is configured
 * to output a high level; otherwise 0.
 */
extern uint32_t PIO_PinGetOutputDataStatus( const Pin* pPin )
{
    if ( (pPin->pio->PIO_ODSR & pPin->mask) == 0 )
    {
        return 0 ;
    }
    else
    {
        return 1 ;
    }
}

/*
 * \brief Configures Glitch or Debouncing filter for input.
 *
 * \param pPin       Pointer to a Pin instance describing one or more pins.
 * \param dwCutOff  Cut off frequency for debounce filter.
 */
extern void PIO_PinSetDebounceFilter( const Pin* pPin, uint32_t dwCutOff )
{
    Pio* pPio = pPin->pio ;

    pPio->PIO_DIFSR = pPin->mask; /* set Debouncing, 0 bit field no effect */
    pPio->PIO_SCDR = PIO_SCDR_DIV( (32678/(dwCutOff << 1)) - 1 ) ;
}
/*
 * \brief Enable write protect.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void PIO_PinEnableWriteProtect( const Pin *pin )
{
   Pio *pio = pin->pio;

   pio->PIO_WPMR = ( PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_EN );
}

/*
 * \brief Disable write protect.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */

void PIO_PinDisableWriteProtect( const Pin *pin )
{
   Pio *pio = pin->pio;

   pio->PIO_WPMR = ( PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_DIS );
}

/*
 * \brief Get write protect violation information.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */

uint32_t PIO_PinGetWriteProtectViolationInfo( const Pin * pin )
{
    Pio *pio = pin->pio;
    return (pio->PIO_WPSR);
}
/* \brief Set pin type
 * the pin is controlled by the corresponding peripheral (A, B, C, D,E)
 * \param pin      Pointer to a Pin instance describing one or more pins.
 * \param pinType  PIO_PERIPH_A, PIO_PERIPH_B, ...
 */

void PIO_PinSetPinType( Pin * pin, uint8_t pinType)
{
    pin->type = pinType;
}

