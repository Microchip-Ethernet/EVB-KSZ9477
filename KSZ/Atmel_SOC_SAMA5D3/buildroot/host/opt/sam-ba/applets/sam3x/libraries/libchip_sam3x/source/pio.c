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

/** \file
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "chip.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures one or more pin(s) of a PIO controller as being controlled by
 * peripheral A. Optionally, the corresponding internal pull-up(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
extern void PIO_SetPeripheralA( Pio *pio, uint32_t dwMask, uint32_t dwOptions )
{
    /* Disable interrupts on the pin(s) */
    pio->PIO_IDR = dwMask ;

    /* Enable the pull-up(s) if necessary */
    if ( dwOptions == PIO_PULLUP )
    {
        pio->PIO_PUER = dwMask ;
    }
    else
    {
        pio->PIO_PUDR = dwMask ;
    }

    pio->PIO_ABSR &= ~dwMask ;
    pio->PIO_PDR = dwMask ;
}

/**
 * \brief Configures one or more pin(s) of a PIO controller as being controlled by
 * peripheral B. Optionally, the corresponding internal pull-up(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
extern void PIO_SetPeripheralB( Pio *pio, uint32_t dwMask, uint32_t dwOptions )
{
    /* Disable interrupts on the pin(s) */
    pio->PIO_IDR = dwMask ;

    /* Enable the pull-up(s) if necessary */
    if ( dwOptions == PIO_PULLUP )
    {
        pio->PIO_PUER = dwMask ;
    }
    else
    {
        pio->PIO_PUDR = dwMask ;
    }

    pio->PIO_ABSR |= dwMask ;
    pio->PIO_PDR = dwMask ;
}

/**
 * \brief Configures one or more pin(s) or a PIO controller as inputs. Optionally,
 * the corresponding internal pull-up(s) and glitch filter(s) can be enabled.
 *
 * \param pPio          Pointer to a PIO controller.
 * \param dwMask        Bitmask indicating which pin(s) to configure as input(s).
 * \param dwAttribute   Input attributes.
 */
extern void PIO_SetInput( Pio* pPio, uint32_t dwMask, uint32_t dwAttributes )
{
    /* Disable interrupts */
    pPio->PIO_IDR = dwMask ;

    /* Enable pull-up(s) if necessary */
    if ( dwAttributes & PIO_PULLUP )
    {
        pPio->PIO_PUER = dwMask ;
    }
    else
    {
        pPio->PIO_PUDR = dwMask ;
    }

    /* Enable Input Filter if necessary */
    if ( dwAttributes & (PIO_DEGLITCH | PIO_DEBOUNCE) )
    {
        pPio->PIO_IFER = dwMask ;
    }
    else
    {
        pPio->PIO_IFDR = dwMask ;
    }

    /* Enable de-glitch or de-bounce if necessary */
    if ( dwAttributes & PIO_DEGLITCH )
    {
        pPio->PIO_SCIFSR = dwMask ;
    }
    else
    {
        if ( dwAttributes & PIO_DEBOUNCE )
        {
            pPio->PIO_DIFSR = dwMask ;
        }
    }

    /* Configure pin as input */
    pPio->PIO_ODR = dwMask ;
    pPio->PIO_PER = dwMask ;
}

/**
 * \brief Configures one or more pin(s) of a PIO controller as outputs, with the
 * given default value. Optionally, the multi-drive feature can be enabled
 * on the pin(s).
 *
 * \param pPio  Pointer to a PIO controller.
 * \param dwMask  Bitmask indicating which pin(s) to configure.
 * \param dwOptions  Default level on the pin(s).
 */
extern void PIO_SetOutput( Pio* pPio, uint32_t dwMask, uint32_t dwOptions )
{
    /* Disable interrupts */
    pPio->PIO_IDR = dwMask ;

    /* Enable pull-up(s) if necessary */
    if ( (dwOptions & PIO_PULLUP) == PIO_PULLUP )
    {
        pPio->PIO_PUER = dwMask ;
    }
    else
    {
        pPio->PIO_PUDR = dwMask ;
    }

    /* Enable multi-drive if necessary */
    if ( (dwOptions & PIO_OPENDRAIN) == PIO_OPENDRAIN )
    {
        pPio->PIO_MDER = dwMask ;
    }
    else
    {
        pPio->PIO_MDDR = dwMask ;
    }

    /* Set default value */
    if ( (dwOptions & PIO_OUTPUT_HIGH) == PIO_OUTPUT_HIGH )
    {
        pPio->PIO_SODR = dwMask ;
    }
    else
    {
        pPio->PIO_CODR = dwMask ;
    }

    /* Configure pin(s) as output(s) */
    pPio->PIO_OER = dwMask ;
    pPio->PIO_PER = dwMask ;
}
