/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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

/**
  *  \file dma_hardware_interface.h
  *
  *  Include Defines & macros for DMA hardware interface.
  */

#ifndef _DMAD_IF_H
#define _DMAD_IF_H

/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include "board.h"

/*----------------------------------------------------------------------------
 *        Consts
 *----------------------------------------------------------------------------*/

#define PERI_DBGU    32

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** DMA hardware interface */
typedef struct _DmaHardwareInterface {
    uint8_t ucDmac;                  /**< DMA Controller number */
    uint8_t ucPeriphID;             /**< Peripheral ID */
    uint8_t ucTransfer;              /**< Transfer type 0: Tx, 1 :Rx*/
    uint8_t ucIfID;                  /**< DMA Interface ID */
} DmaHardwareInterface;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern uint8_t DMAIF_IsValidatedPeripherOnDma( uint8_t ucDmac, uint8_t ucPeriphID);
extern uint8_t DMAIF_GetChannelNumber (uint8_t ucDmac, uint8_t ucPeriphID, uint8_t ucTransfer);

#endif //#ifndef _DMAD_IF_H

