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
  *  \file
  *
  *  Include Defines & macros for DMA logical device.
  */


#ifndef _DMAD_H
#define _DMAD_H
/** \addtogroup dmad_module
 *@{
 */

/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/


/** \addtogroup dmad_defines DMA Driver Defines
        @{*/
/*----------------------------------------------------------------------------
 *        Consts
 *----------------------------------------------------------------------------*/
#define DMA_TRANSFER_MEMORY  0xFF   /**< DMA transfer from or to memory */
#define DMA_ALLOC_FAILED     0xFFFF /**< Channel allocate failed */
#define DMA_TRANSFER_RX      1      /**< DMA transfer type is receive */
#define DMA_TRANSFER_TX      0      /**< DMA transfer type is transmit */

/*----------------------------------------------------------------------------
 *        MACRO
 *----------------------------------------------------------------------------*/

/**     @}*/

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
/** \addtogroup dmad_structs DMA Driver Structs
        @{*/

/** DMA status or return code */
typedef enum _DmadStatus {
    DMAD_OK = 0,        /**< Operation is sucessful */
    DMAD_BUSY,          /**< Channel occupied or transfer not finished */
    DMAD_PARTIAL_DONE,  /**< Partial of LLI finished (on each buffer done) */
    DMAD_ERROR,         /**< Operation failed */
    DMAD_CANCELED       /**< Operation canceled */
} eDmadStatus, eDmadRC;

/** DMA state for channel */
typedef enum _DmadState {
    DMAD_FREE = 0,      /**< Free channel */
    DMAD_IN_USE,        /**< Allocated to some peripheral */
    DMAD_IN_XFR,        /**< Transferring something */
    DMAD_STALL          /**< Error stall */
} eDmadState;

/** DMA transfer callback */
typedef void (*DmadTransferCallback)(uint32_t status, void* pArg);

/** DMA driver channel */
typedef struct _DmadChannel {
    DmadTransferCallback fCallback; /**< Callback */
    void* pArg;                     /**< Callback argument */

    uint8_t ucIrqOwner;              /**< Uses DMA handler or external one */
    uint8_t ucSrcPeriphID;           /**< HW ID for source */
    uint8_t ucDstPeriphID;           /**< HW ID for destination */
    uint8_t ucSrcTxIfID;             /**< DMA Tx Interface ID for source */
    uint8_t ucSrcRxIfID;             /**< DMA Rx Interface ID for source */
    uint8_t ucDstTxIfID;             /**< DMA Tx Interface ID for destination */
    uint8_t ucDstRxIfID;             /**< DMA Rx Interface ID for destination */

    volatile uint8_t ucState;         /**< DMA channel state */
} sDmadChannel;

/** DMA driver instance */
typedef struct _Dmad {
    Dmac *pDmacs[DMAC_CONTROLLER_NUM];
    sDmadChannel dmaChannels[DMAC_CONTROLLER_NUM][DMAC_CHANNEL_NUM];
    uint8_t  ucNumControllers;
    uint8_t  ucNumChannels;  
    uint8_t  ucPollingModes;
    uint8_t  ucPollingTimeout;
} sDmad;

/** DMA driver channel ID */
typedef struct _DmadChannelID {
    uint8_t ucDmac;      /**< DMA Controller number */
    uint8_t ucChannel;   /**< Channel number */
} sDmadChannelID;

/**     @}*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/** \addtogroup dmad_functions DMA Driver Functionos
        @{*/
extern void DMAD_Initialize( sDmad *pDmad,
                             uint8_t bPollingMode );

extern void DMAD_Handler( sDmad *pDmad );

extern uint32_t DMAD_AllocateChannel( sDmad *pDmad,
                                      uint8_t ucSrcID, uint8_t ucDstID);
extern eDmadRC DMAD_FreeChannel( sDmad *pDmad, uint32_t dwChannel );

extern eDmadRC DMAD_SetCallback( sDmad *pDmad, uint32_t dwChannel,
                                  DmadTransferCallback fCallback, void* pArg );
  
extern eDmadRC DMAD_PrepareChannel( sDmad *pDmad, uint32_t dwChannel,
                                   uint32_t dwCfg );
   
extern eDmadRC DMAD_IsTransferDone( sDmad *pDmad, uint32_t dwChannel );

extern eDmadRC DMAD_StartTransfer( sDmad *pDmad, uint32_t dwChannel );
extern eDmadRC DMAD_StartTransfers( sDmad *pDmad,
                                    uint8_t bDmac, uint32_t bmChannels );

extern eDmadRC DMAD_StopTransfer( sDmad *pDmad, uint32_t dwChannel );
extern eDmadRC DMAD_PrepareSingleTransfer( sDmad *pDmad, uint32_t dwChannel,
                                           sDmaTransferDescriptor *pXfrDesc );
   
extern eDmadRC DMAD_PrepareMultiTransfer( sDmad *pDmad, uint32_t dwChannel,
                                          sDmaTransferDescriptor *pXfrDesc );
#endif //#ifndef _DMAD_H
