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

/** \addtogroup dmad_module 
 *
 * \section DmaConfig Dma Configuration Usage
 *
 * To configure a DMA channel, the user has to follow these few steps :
 * <ul>
 * <li> Initialize a DMA driver instance by DMAD_Initialize().</li>
 * <li> choose an available (disabled) channel using DMAD_AllocateChannel().</li>
 * <li> After the DMAC selected channel has been programmed, DMAD_PrepareChannel() is to enable 
 * clock and dma peripheral of the DMA, and set Configuration register to set up the transfer type 
 * (memory or non-memory peripheral for source and destination) and flow control device.</li>
 * <li> Configure DMA multi-buffer transfers using DMAD_PrepareMultiTransfer() to set up the chain of Linked List Items,
 * single-buffer transfers using DMAD_PrepareSingleTransfer().</li>
 * <li> Invoke DMAD_StartTransfer() to start DMA transfer, or DMAD_StopTransfer() to force stop DMA transfer.</li>
 * <li> If picture-in-picture mode is enabled, DMAD_ConfigurePIP() helps to configure PIP mode.</li>
 * <li> Once the buffer of data is transferred, DMAD_IsTransferDone() checks if DMA transfer is finished.</li>
 * <li> DMAD_Handler() handles DMA interrupt, and invoking DMAD_SetCallback() if provided.</li>
 * </ul>
 *
 * Related files:\n
 * \ref dmad.h\n
 * \ref dmad.c.\n
 */

/** \file */

/** \addtogroup dmad_functions
  @{*/
 
/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include "board.h"
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Try to allocate a DMA channel for on given controller.
 * \param pDmad  Pointer to DMA driver instance.
 * \param ucDmac  DMA controller ID.
 * \param ucSrcID Source peripheral ID, 0xFF for memory.
 * \param ucDstID Destination peripheral ID, 0xFF for memory.
 * \return Channel number if allocation sucessful, return 
 * DMA_ALLOC_FAILED if allocation failed.
 */
static uint32_t DMAD_AllocateDmacChannel( sDmad *pDmad,
                                          uint8_t ucDmac,
                                          uint8_t ucSrcID, 
                                          uint8_t ucDstID)
{
    uint32_t i;

    /* Can't support peripheral to peripheral */
    if ((( ucSrcID != DMA_TRANSFER_MEMORY ) && ( ucDstID != DMA_TRANSFER_MEMORY ))) 
    {
        return DMA_ALLOC_FAILED;
    }
    /* dma transfer from peripheral to memory */
    if ( ucDstID == DMA_TRANSFER_MEMORY)
    {
        if( (!DMAIF_IsValidatedPeripherOnDma(ucDmac, ucSrcID)) )
        {
            return DMA_ALLOC_FAILED;
        }
    }
    /* dma transfer from memory to peripheral */
    if ( ucSrcID == DMA_TRANSFER_MEMORY )
    {
        if( (!DMAIF_IsValidatedPeripherOnDma(ucDmac, ucDstID)) )
        {
            return DMA_ALLOC_FAILED;
        }
    }
    for (i = 0; i < pDmad->ucNumChannels; i ++)
    {
        if ( pDmad->dmaChannels[ucDmac][i].ucState == DMAD_FREE ) 
        {
            /* Allocate the channel */
            pDmad->dmaChannels[ucDmac][i].ucState = DMAD_IN_USE;
            /* Get general informations */
            pDmad->dmaChannels[ucDmac][i].ucSrcPeriphID = ucSrcID;
            pDmad->dmaChannels[ucDmac][i].ucDstPeriphID = ucDstID;
            pDmad->dmaChannels[ucDmac][i].ucSrcTxIfID =
                DMAIF_GetChannelNumber(ucDmac, ucSrcID, 0);
            pDmad->dmaChannels[ucDmac][i].ucSrcRxIfID =
                DMAIF_GetChannelNumber(ucDmac, ucSrcID, 1);
            pDmad->dmaChannels[ucDmac][i].ucDstTxIfID =
                DMAIF_GetChannelNumber(ucDmac, ucDstID, 0);
            pDmad->dmaChannels[ucDmac][i].ucDstRxIfID =
                DMAIF_GetChannelNumber(ucDmac, ucDstID, 1);

            return ((ucDmac << DMAC_CHANNEL_NUM)) | ((i) & 0xFF);
        }
    }
    return DMA_ALLOC_FAILED;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initialize DMA driver instance.
 * \param pDmad Pointer to DMA driver instance.
 * \param ucPollingMode Polling DMA transfer:
 *                     1. Via DMAD_IsTransferDone(); or
 *                     2. Via DMAD_Handler().
 */
void DMAD_Initialize( sDmad *pDmad,
                      uint8_t ucPollingMode )
{
    uint32_t i, j;
    
    assert( pDmad != NULL ) ;
    
    pDmad->pDmacs[0] = DMAC;
    pDmad->ucPollingModes = ucPollingMode;
    pDmad->ucNumControllers = DMAC_CONTROLLER_NUM;
    pDmad->ucNumChannels    = DMAC_CHANNEL_NUM;
    
    for (i = 0; i < pDmad->ucNumControllers; i ++)
    {
        for (j = 0; j < pDmad->ucNumChannels; j ++)
        {
            pDmad->dmaChannels[i][j].fCallback = 0;
            pDmad->dmaChannels[i][j].pArg      = 0;

            pDmad->dmaChannels[i][j].ucIrqOwner    = 0;
            pDmad->dmaChannels[i][j].ucSrcPeriphID = 0;
            pDmad->dmaChannels[i][j].ucDstPeriphID = 0;
            pDmad->dmaChannels[i][j].ucSrcTxIfID   = 0;
            pDmad->dmaChannels[i][j].ucSrcRxIfID   = 0;
            pDmad->dmaChannels[i][j].ucDstTxIfID   = 0;
            pDmad->dmaChannels[i][j].ucDstRxIfID   = 0;
            
            pDmad->dmaChannels[i][j].ucState = DMAD_FREE;
        }
    }
}

/**
 * \brief DMA interrupt handler
 * \param pDmad Pointer to DMA driver instance.
 */
void DMAD_Handler( sDmad *pDmad )
{
    Dmac *pDmac;
    sDmadChannel *pCh;
    uint8_t ucController, ucChannel;
    uint32_t dmaSr, chSr;
    uint32_t dmaRc = DMAD_OK;

    assert( pDmad != NULL ) ;
    
    for (ucController = 0; ucController < pDmad->ucNumControllers; ucController ++)
    {
        pDmac = pDmad->pDmacs[ucController];

        /* Check raw status but not masked one for polling mode support */
        dmaSr = DMAC_GetStatus( pDmac );
        if ((dmaSr & 0x00FFFFFF) == 0) continue;

        chSr  = DMAC_GetChannelStatus( pDmac );
//        printf("iDma(%x,%x)\n\r", dmaSr, chSr);

        for (ucChannel = 0; ucChannel < pDmad->ucNumChannels; ucChannel ++)
        {
            uint8_t bExec = 1;

            pCh = &pDmad->dmaChannels[ucController][ucChannel];
            /* Error */
            if (dmaSr & (DMAC_EBCIDR_ERR0 << ucChannel))
            {
                DMAC_DisableChannel( pDmac, ucChannel );
                if (pCh->ucState > DMAD_IN_USE)   pCh->ucState = DMAD_STALL;
                dmaRc = DMAD_ERROR;
            }
            /* Chained buffer complete */
            else if (dmaSr & (DMAC_EBCIDR_CBTC0 << ucChannel))
            {
                DMAC_DisableChannel( pDmac, ucChannel );
                if (pCh->ucState > DMAD_IN_USE)   pCh->ucState = DMAD_IN_USE;
                dmaRc = DMAD_OK;
                
            }
            /* Buffer complete */
            else if (dmaSr & (DMAC_EBCIDR_BTC0 << ucChannel))
            {
                dmaRc = DMAD_PARTIAL_DONE;
                /* Re-enable */
                if ((chSr & (DMAC_CHSR_ENA0 << ucChannel)) == 0)
                {
                    DMAC_EnableChannel( pDmac, ucChannel );
                }
            }
            else
            {
                bExec = 0;
            }
            /* Execute callback */
            if (bExec && pCh->fCallback)
            {
                pCh->fCallback(dmaRc, pCh->pArg);
            }
        }
    }
}

/**
 * \brief Allocate a DMA channel for upper layer.
 * \param pDmad  Pointer to DMA driver instance.
 * \param ucSrcID Source peripheral ID, 0xFF for memory.
 * \param ucDstID Destination peripheral ID, 0xFF for memory.
 * \return Channel number if allocation sucessful, return 
 * DMA_ALLOC_FAILED if allocation failed.
 */
uint32_t DMAD_AllocateChannel( sDmad *pDmad,
                               uint8_t ucSrcID, 
                               uint8_t ucDstID)
{
    uint8_t ucController;
    uint32_t dwChannel = DMA_ALLOC_FAILED;

    for ( ucController = 0; ucController < pDmad->ucNumControllers; ucController ++)
    {
        dwChannel = DMAD_AllocateDmacChannel( pDmad, ucController,
                                              ucSrcID, ucDstID );
        if (dwChannel != DMA_ALLOC_FAILED)
            break;
    }
    return dwChannel;
}

/**
 * \brief Free the specified DMA channel.
 * \param pDmad     Pointer to DMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 */
eDmadRC DMAD_FreeChannel( sDmad *pDmad, uint32_t dwChannel )
{
    uint8_t ucController = (dwChannel >> DMAC_CHANNEL_NUM);
    uint8_t ucChannel    = (dwChannel) & 0xFF;
    
    assert( pDmad != NULL ) ;
    switch ( pDmad->dmaChannels[ucController][ucChannel].ucState )
    {

    case DMAD_IN_XFR:
        return DMAD_BUSY;

    case DMAD_IN_USE:
        pDmad->dmaChannels[ucController][ucChannel].ucState = DMAD_FREE;
        break;
    }
    return DMAD_OK;
}

/**
 * \brief Set the callback function for DMA channel transfer.
 * \param pDmad     Pointer to DMA driver instance.
 * \param dwChannel ControllerNumber << DMAC_CHANNEL_NUM | ChannelNumber.
 * \param fCallback Pointer to callback function.
 * \param pArg Pointer to optional argument for callback.
 */
eDmadRC DMAD_SetCallback( sDmad *pDmad, uint32_t dwChannel,
                          DmadTransferCallback fCallback, void* pArg )
{
    uint8_t ucController = (dwChannel >> DMAC_CHANNEL_NUM);
    uint8_t ucChannel    = (dwChannel) & 0xFF;
    
    assert( pDmad != NULL ) ;
    if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_FREE )
        {printf("DMAD set call back error \n\r");
        return DMAD_ERROR;}

    else if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_IN_XFR )
        return DMAD_BUSY;
    
    pDmad->dmaChannels[ucController][ucChannel].fCallback = fCallback;
    pDmad->dmaChannels[ucController][ucChannel].pArg = pArg;
    
    return DMAD_OK;
}

/**
 * \brief Enable clock of the DMA peripheral, Enable the dma peripheral, 
 * configure configuration register for DMA transfer.
 * \param pDmad     Pointer to DMA driver instance.
 * \param dwChannel ControllerNumber << DMAC_CHANNEL_NUM | ChannelNumber.
 * \param dwCfg     Configuration value.
 */
eDmadRC DMAD_PrepareChannel( sDmad *pDmad, 
                             uint32_t dwChannel,
                             uint32_t dwCfg )
{
    uint8_t ucController = (dwChannel >> DMAC_CHANNEL_NUM);
    uint8_t ucChannel    = (dwChannel) & 0xFF;

    assert( pDmad != NULL ) ;
    Dmac *pDmac = pDmad->pDmacs[ucController];

    if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_FREE )
        return DMAD_ERROR;
    else if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_IN_XFR )
        return DMAD_BUSY;
    DMAC_SetCFG( pDmac, ucChannel, dwCfg );

    /* Enable clock of the DMA peripheral */
    if (!PMC_IsPeriphEnabled( ID_DMAC ))
    {
        PMC_EnablePeripheral( ID_DMAC );
    }
    /* Enables the DMAC peripheral. */
    DMAC_Enable( pDmac );
    /* Disables DMAC interrupt for the given channel. */
    DMAC_DisableIt (pDmac, 
                    (DMAC_EBCIDR_BTC0 << ucChannel)
                   |(DMAC_EBCIDR_CBTC0 << ucChannel)
                   |(DMAC_EBCIDR_ERR0 << ucChannel) );
    /* Disable the given dma channel. */
    DMAC_DisableChannel( pDmac, ucChannel );

    return DMAD_OK;
}

/**
 * \brief Check if DMA transfer is finished.
 *        In polling mode DMAD_Handler() is polled.
 * \param pDmad     Pointer to DMA driver instance.
 * \param dwChannel ControllerNumber << DMAC_CHANNEL_NUM | ChannelNumber.
 */
eDmadRC DMAD_IsTransferDone( sDmad *pDmad, uint32_t dwChannel )
{
    uint8_t ucController = (dwChannel >> DMAC_CHANNEL_NUM);
    uint8_t ucChannel    = (dwChannel) & 0xFF;

    assert( pDmad != NULL ) ;
    if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_FREE )
        return DMAD_ERROR;
    else if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_IN_XFR )
    {
        if ( pDmad->ucPollingModes ) DMAD_Handler( pDmad );
        return DMAD_BUSY;
    }
    return DMAD_OK;
}

/**
 * \brief Start DMA transfer.
 * \param pDmad     Pointer to DMA driver instance.
 * \param dwChannel ControllerNumber << DMAC_CHANNEL_NUM | ChannelNumber.
 */
eDmadRC DMAD_StartTransfer( sDmad *pDmad, uint32_t dwChannel )
{
    uint8_t ucController = (dwChannel >> DMAC_CHANNEL_NUM);
    uint8_t ucChannel    = (dwChannel) & 0xFF;
    
    assert( pDmad != NULL ) ;
    Dmac *pDmac = pDmad->pDmacs[ucController];

    if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_FREE )
        {
        printf("DMAD_START TRANSFER ERROR\n\r");
        return DMAD_ERROR;
        }
    else if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_IN_XFR )
        {
        printf("DMAD_START TRANSFER BUSY\n\r");
        return DMAD_BUSY;
        }
    /* Change ucState to transferring */
    pDmad->dmaChannels[ucController][ucChannel].ucState = DMAD_IN_XFR;
    DMAC_EnableChannel(pDmac, ucChannel);
    if ( pDmad->ucPollingModes == 0 )
    {
        /* Monitor status in interrupt handler */
        DMAC_EnableIt(pDmac, (DMAC_EBCIDR_BTC0 << ucChannel)
                            |(DMAC_EBCIDR_CBTC0 << ucChannel)
                            |(DMAC_EBCIDR_ERR0 << ucChannel) );
    }
    
    return DMAD_OK;
}

/**
 * \brief Start DMA transfers on the same controller.
 * \param pDmad      Pointer to DMA driver instance.
 * \param bDmac      DMA Controller number. 
 * \param bmChannels Channels bitmap.
 */
eDmadRC DMAD_StartTransfers( sDmad *pDmad, uint8_t bDmac, uint32_t bmChannels )
{
    uint32_t ucChannel;
    uint32_t dwChs = 0, dwIts = 0;

    assert( pDmad != NULL ) ;
    Dmac *pDmac = pDmad->pDmacs[bDmac];

    for (ucChannel = 0; ucChannel < pDmad->ucNumChannels; ucChannel ++)
    {
        uint32_t dwChBit = 1 << ucChannel;

        /* Skipped channels */
        if ( pDmad->dmaChannels[bDmac][ucChannel].ucState == DMAD_FREE )
            continue;
        else if ( pDmad->dmaChannels[bDmac][ucChannel].ucState == DMAD_IN_XFR )
            continue;
        /* Log to start bit map */
        if (bmChannels & dwChBit)
        {
            dwChs |= dwChBit;
            dwIts |= (  (DMAC_EBCIDR_BTC0 << ucChannel)
                       |(DMAC_EBCIDR_CBTC0 << ucChannel)
                       |(DMAC_EBCIDR_ERR0 << ucChannel) );
            /* Change ucState */
            pDmad->dmaChannels[bDmac][ucChannel].ucState = DMAD_IN_XFR;
        }
    }

    DMAC_EnableChannels(pDmac, dwChs);
    if ( pDmad->ucPollingModes == 0 )
    {
        /* Monitor status in interrupt handler */
        DMAC_EnableIt( pDmac, dwIts );
    }
    
    return DMAD_OK;
}

/**
 * \brief Stop DMA transfer.
 * \param pDmad     Pointer to DMA driver instance.
 * \param dwChannel ControllerNumber << DMAC_CHANNEL_NUM | ChannelNumber.
 */
eDmadRC DMAD_StopTransfer( sDmad *pDmad, uint32_t dwChannel )
{
    uint8_t ucController = (dwChannel >> DMAC_CHANNEL_NUM);
    uint8_t ucChannel    = (dwChannel) & 0xFF;
    
    assert( pDmad != NULL ) ;
    Dmac *pDmac = pDmad->pDmacs[ucController];
    sDmadChannel *pCh = &pDmad->dmaChannels[ucController][ucChannel];

    uint32_t to = 0x1000;

    if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_FREE )
        return DMAD_ERROR;
    if ( pDmad->dmaChannels[ucController][ucChannel].ucState != DMAD_IN_XFR )
    {
        /* Disable channel */
        DMAC_DisableChannel(pDmac, ucChannel);
        /* Disable interrupts */
        DMAC_DisableIt(pDmac, (DMAC_EBCIDR_BTC0 << ucChannel)
                             |(DMAC_EBCIDR_CBTC0 << ucChannel)
                             |(DMAC_EBCIDR_ERR0 << ucChannel) );
        /* Clear pending status */
        DMAC_GetChannelStatus(pDmac);
        DMAC_GetStatus(pDmac);

        return DMAD_OK;
     }
    /* Suspend */
    DMAC_SuspendChannel(pDmac, ucChannel);

    /* Poll empty */
    for (;to; to --)
    {
        if (DMAC_GetChannelStatus(pDmac) & (DMAC_CHSR_EMPT0 << ucChannel))
        {
            break;
        }
    }

    /* Disable channel */
    DMAC_DisableChannel(pDmac, ucChannel);
    /* Disable interrupts */
    DMAC_DisableIt(pDmac, (DMAC_EBCIDR_BTC0 << ucChannel)
                         |(DMAC_EBCIDR_CBTC0 << ucChannel)
                         |(DMAC_EBCIDR_ERR0 << ucChannel) );
    /* Clear pending status */
    DMAC_GetChannelStatus(pDmac);
    DMAC_GetStatus(pDmac);
    /* Resume */
    DMAC_RestoreChannel(pDmac, ucChannel);
    /* Change ucState */
    pDmad->dmaChannels[ucController][ucChannel].ucState = DMAD_IN_USE;
    /* Invoke callback */
    if (pCh->fCallback) pCh->fCallback(DMAD_CANCELED, pCh->pArg);
    return DMAD_OK;
}

/**
 * \brief Configure DMA for a single transfefr.
 * \param pDmad     Pointer to DMA driver instance.
 * \param dwChannel ControllerNumber << DMAC_CHANNEL_NUM | ChannelNumber.
  * \param pXfrDesc  Pointer to DMA Linked List.
 */
eDmadRC DMAD_PrepareSingleTransfer( sDmad *pDmad, 
                                    uint32_t dwChannel,
                                    sDmaTransferDescriptor *pXfrDesc )
{
    uint8_t ucController = (dwChannel >> DMAC_CHANNEL_NUM);
    uint8_t ucChannel    = (dwChannel) & 0xFF;
    Dmac *pDmac = pDmad->pDmacs[ucController];

    if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_FREE )
        return DMAD_ERROR;

    if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_IN_XFR )
        return DMAD_BUSY;

    DMAC_SetSourceAddr(pDmac, ucChannel, pXfrDesc->dwSrcAddr);
    DMAC_SetDestinationAddr(pDmac, ucChannel, pXfrDesc->dwDstAddr);
    DMAC_SetDescriptorAddr(pDmac, ucChannel, 0, 0);
    DMAC_SetControlA(pDmac, ucChannel, pXfrDesc->dwCtrlA);
    DMAC_SetControlB(pDmac, ucChannel, pXfrDesc->dwCtrlB);

    return DMAD_OK;
}

/**
 * \brief Configure DMA multi-buffer transfers using linked lists
 * \param pDmad     Pointer to DMA driver instance.
 * \param _dwChannel ControllerNumber << DMAC_CHANNEL_NUM | ChannelNumber.
 * \param pXfrDesc  Pointer to DMA Linked List.
 */
eDmadRC DMAD_PrepareMultiTransfer( sDmad *pDmad, 
                                   uint32_t dwChannel,
                                   sDmaTransferDescriptor *pXfrDesc )
{
    uint8_t ucController = (dwChannel >> DMAC_CHANNEL_NUM);
    uint8_t ucChannel    = (dwChannel) & 0xFF;
    
    assert( pDmad != NULL ) ;
    Dmac *pDmac = pDmad->pDmacs[ucController];

    if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_FREE )
        return DMAD_ERROR;
    if ( pDmad->dmaChannels[ucController][ucChannel].ucState == DMAD_IN_XFR )
        return DMAD_BUSY;
    
    DMAC_SetDescriptorAddr( pDmac, ucChannel, (uint32_t)pXfrDesc, 0 );
    DMAC_SetControlB( pDmac, ucChannel, 0);

    return DMAD_OK;
}

/**@}*/

