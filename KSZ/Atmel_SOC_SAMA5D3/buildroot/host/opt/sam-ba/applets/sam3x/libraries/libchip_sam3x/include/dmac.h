/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
 * 
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the disclaimer below in the documentation and/or
 * other materials provided with the distribution. 
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

/** \addtogroup dmac_module Working with DMAC
 *
 * \section Usage
 * <ul>
 * <li> Enable or disable the a DMAC controller with DMAC_Enable() and or DMAC_Disable().</li>
 * <li> Enable or disable %Dma interrupt using DMAC_EnableIt()or DMAC_DisableIt().</li>
 * <li> Get %Dma interrupt status by DMAC_GetStatus() and DMAC_GetInterruptMask().</li>
 * <li> Enable or disable specified %Dma channel with DMAC_EnableChannel() or DMAC_DisableChannel().</li>
 * <li> Get %Dma channel status by DMAC_GetChannelStatus().</li>
 * <li> ControlA and ControlB register is set by DMAC_SetControlA() and DMAC_SetControlB().</li>
 * <li> Configure source and/or destination start address with DMAC_SetSourceAddr() and/or DMAC_SetDestinationAddr().</li>
 * <li> Set %Dma descriptor address using DMAC_SetDescriptorAddr().</li>
 * <li> Set source transfer buffer size with DMAC_SetBufferSize().</li>
 * <li> Configure source and/or destination Picture-In-Picutre mode with DMAC_SetSourcePip() and/or DMAC_SetDestPip().</li>
 * </ul>
 *
 * For more accurate information, please look at the DMAC section of the
 * Datasheet.
 *
 * \sa \ref dmad_module
 *
 * Related files :\n
 * \ref dmac.c\n
 * \ref dmac.h.\n
 *
 */

#ifndef DMAC_H
#define DMAC_H
/**@{*/
#if defined sam3x2
#elif defined sam3x2c | defined sam3a2
#elif defined sam3x4
#elif defined sam3x4c | defined sam3a4
#elif defined sam3x8
#elif defined sam3x8c | defined sam3a8
#else
  #error Library does not support the specified device.
#endif

/*------------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include <stdint.h>

/*------------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/** \addtogroup dmac_defines DMAC Definitions
 *      @{
 */
 /** Number of DMA controllers */
#define DMAC_CONTROLLER_NUM          1
/** Number of DMA channels */
#define DMAC_CHANNEL_NUM          6
/** Max DMA single transfer size */
#define DMAC_MAX_BT_SIZE          0xFFFF
/**     @}*/

/*------------------------------------------------------------------------------
 *         Data structs
 *----------------------------------------------------------------------------*/

/** \addtogroup dmac_struct DMAC Data Structs
 *      @{
 */
/** DMA Transfer Descriptor as well as Linked List Item */
typedef struct _DmaTransferDescriptor {
    uint32_t dwSrcAddr;     /**< Source buffer address */
    uint32_t dwDstAddr;     /**< Destination buffer address */
    uint32_t dwCtrlA;       /**< Control A register settings */
    uint32_t dwCtrlB;       /**< Control B register settings */
    uint32_t dwDscAddr;     /**< Next descriptor address */
} sDmaTransferDescriptor;

/** DMA channel control A */
typedef struct _DmaCtrlA {
    uint32_t btSize:16,     /**< Buffer Transfer size */
             scSize:3,      /**< Source Chunk Transfer size */
             reserve1:1,
             dcSize:3,      /**< Destination Chunk Transfer size */
             reserve2:1,
             srcWidth:2,    /**< Source width */
             reserve3:2,
             dstWidth:2,    /**< Destination width */
             reserve4:1,
             done:1;        /**< The transfer is done */
} sDmaCtrlA;

/** DMA channel control B */
typedef struct _DmaCtrlB {
    uint32_t sIf:2,         /**< Source Interface Selection Field */
             reserve1:2,
             dIf:2,         /**< Destination Interface Selection Field */
             reserve2:2,
             srcPip:1,      /**< Source Picture-in-picture mode enable */
             reserve3:3,
             dstPip:1,      /**< Destination Picture-in-picture mode enable */
             reserve4:3,
             srcDscr:1,     /**< Source Descriptor disabled */
             reserve5:3,
             dstDscr:1,     /**< Destination Descriptor disabled */
             fc:3,          /**< Flow Controller */
             srcIncr:2,     /**< Source Fixed/Dec/Inc setting */
             reserve6,
             dstIncr:2,     /**< Destination Fixed/Dec/Inc setting */
             iEn:1,         /**< Active low to enable interrupt */
             autoEn:1;      /**< Automatic multiple buffer transfer */
} sDmaCtrlB;

/** DMA channel Picture-In-Picture */
typedef struct _DmaPip {
    uint32_t pipHole:16,    /**< Hole size */
             pipBoundary:10,/**< Number of transfers to perform before
                                 hole increse */
             reserve:6;
} sDmaPIP;
/**         @}*/

/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/
/** \addtogroup dmac_functions
 *      @{
 */

#ifdef __cplusplus
 extern "C" {
#endif

extern void     DMAC_Modified_Arbiter( Dmac* pDmac);
extern void     DMAC_Enable( Dmac* pDmac );
extern void     DMAC_Disable( Dmac* pDmac );
extern void     DMAC_EnableIt (Dmac* pDmac, uint32_t dwInteruptMask );
extern void     DMAC_DisableIt (Dmac* pDmac, uint32_t dwInteruptMask );
extern uint32_t DMAC_GetInterruptMask( Dmac* pDmac );
extern uint32_t DMAC_GetStatus( Dmac* pDmac );
extern uint32_t DMAC_GetMaskedStatus( Dmac* pDmac );
extern void     DMAC_EnableChannel( Dmac* pDmac, uint8_t ucChannel );
extern void     DMAC_EnableChannels( Dmac* pDmac, uint8_t ucChannel );
extern void     DMAC_DisableChannel( Dmac* pDmac, uint8_t ucChannel );
extern void     DMAC_DisableChannels( Dmac* pDmac, uint8_t ucChannel );
extern void     DMAC_SuspendChannel( Dmac* pDmac, uint8_t ucChannel );
extern void     DMAC_KeepChannel( Dmac* pDmac, uint8_t ucChannel );
extern void     DMAC_RestoreChannel( Dmac* pDmac, uint8_t ucChannel );
extern uint32_t DMAC_GetChannelStatus( Dmac* pDmac );
extern void     DMAC_SetSourceAddr( Dmac* pDmac,
                                uint8_t ucChannel,
                                uint32_t dwSaddr );
extern uint32_t DMAC_GetSourceAddr( Dmac * pDmac,
                                uint8_t ucChannel );
extern void     DMAC_SetDestinationAddr( Dmac* pDmac,
                                     uint8_t ucChannel,
                                     uint32_t dwDaddr );
extern uint32_t DMAC_GetDestinationAddr( Dmac * pDmac,
                                     uint8_t ucChannel );
extern void     DMAC_SetDescriptorAddr( Dmac* pDmac,
                                    uint8_t ucChannel,
                                    uint32_t dwDescr,
                                    uint8_t ucDescrif );
extern void     DMAC_SetControlA( Dmac* pDmac,
                              uint8_t ucChannel,
                              uint32_t controlA );
extern void     DMAC_SetBufferSize( Dmac* pDmac,
                                uint8_t ucChannel,
                                uint16_t uwBuffsize);
extern void     DMAC_SetSingleTransferSize ( Dmac* pDmac,
                                         uint8_t ucChannel,
                                         uint8_t ucSrcWidth,
                                         uint8_t ucDstWidth );
extern void     DMAC_SetChunkTransferSize ( Dmac* pDmac,
                                        uint8_t ucChannel,
                                        uint8_t ucScSize,
                                        uint8_t ucDcSize);
extern void     DMAC_SetControlB( Dmac* pDmac,
                              uint8_t ucChannel,
                              uint32_t dwControlB );
extern void     DMAC_SetDescFetchMode( Dmac* pDmac,
                                   uint8_t ucChannel,
                                   uint8_t ucSrcDscr,
                                   uint8_t ucDstDscr );
extern void     DMAC_SetFlowControl( Dmac* pDmac,
                                 uint8_t ucChannel,
                                 uint8_t ucFlowControl );
extern void     DMAC_SetCFG( Dmac* pDmac,
                         uint8_t ucChannel,
                         uint32_t dwConfiguration );
extern void     DMAC_SethandshakeInterface( Dmac* pDmac,
                                        uint8_t ucChannel,
                                        uint8_t ucSrcH2sel,
                                        uint8_t ucDstH2sel );
#ifdef __cplusplus
}
#endif

/**     @}*/
/**@}*/
#endif //#ifndef DMAC_H

