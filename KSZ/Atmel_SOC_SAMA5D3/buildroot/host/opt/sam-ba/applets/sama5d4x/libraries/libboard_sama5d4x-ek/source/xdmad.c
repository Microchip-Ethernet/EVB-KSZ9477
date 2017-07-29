/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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

/** \addtogroup xdmad_module 
 *
 * \section Dma Config Dma Configuration Usage
 *
 * To configure a DMA channel, the user has to follow these few steps :
 * <ul>
 * <li> Initialize a DMA driver instance by DMAD_Initialize().</li>
 * <li> choose an available (disabled) channel using DMAD_AllocateChannel().</li>
 * <li> After the DMAC selected channel has been programmed, XDMAD_PrepareChannel() is to enable 
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

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Try to allocate a DMA channel for on given controller.
 * \param pDmad  Pointer to DMA driver instance.
 * \param bXdmac xDMA controller ID (0 ~ 1).
 * \param bSrcID Source peripheral ID, 0xFF for memory.
 * \param bDstID Destination peripheral ID, 0xFF for memory.
 * \return Channel number if allocation sucessful, return
 * DMAD_ALLOC_FAILED if allocation failed.
 */
static uint32_t XDMAD_AllocateXdmacChannel( sXdmad *pXdmad,
                                            uint8_t bXdmac,
                                            uint8_t bSrcID,
                                            uint8_t bDstID)
{
    uint32_t i;
    /* Can't support peripheral to peripheral */
    if ((( bSrcID != XDMAD_TRANSFER_MEMORY ) && ( bDstID != XDMAD_TRANSFER_MEMORY )))
    {
        return XDMAD_ALLOC_FAILED;
    }
    /* dma transfer from peripheral to memory */
    if ( bDstID == XDMAD_TRANSFER_MEMORY)
    {
        if( (!XDMAIF_IsValidatedPeripherOnDma(bXdmac, bSrcID)) )
        {
            return XDMAD_ALLOC_FAILED;
        }
    }
    /* dma transfer from memory to peripheral */
    if ( bSrcID == XDMAD_TRANSFER_MEMORY )
    {
        if( (!XDMAIF_IsValidatedPeripherOnDma(bXdmac, bDstID)) )
        {
            return XDMAD_ALLOC_FAILED;
        }
    }

    for (i = 0; i < pXdmad->numChannels; i ++)
    {
        if ( pXdmad->XdmaChannels[bXdmac][i].state == XDMAD_FREE )
        {
            /* Allocate the channel */
            pXdmad->XdmaChannels[bXdmac][i].state = XDMAD_IN_USE;
            /* Get general informations */
            pXdmad->XdmaChannels[bXdmac][i].bSrcPeriphID = bSrcID;
            pXdmad->XdmaChannels[bXdmac][i].bDstPeriphID = bDstID;
            pXdmad->XdmaChannels[bXdmac][i].bSrcTxIfID =
                XDMAIF_Get_ChannelNumber(bXdmac, bSrcID, 0);
            pXdmad->XdmaChannels[bXdmac][i].bSrcRxIfID =
                XDMAIF_Get_ChannelNumber(bXdmac, bSrcID, 1);
            pXdmad->XdmaChannels[bXdmac][i].bDstTxIfID =
                XDMAIF_Get_ChannelNumber(bXdmac, bDstID, 0);
            pXdmad->XdmaChannels[bXdmac][i].bDstTxIfID =
                XDMAIF_Get_ChannelNumber(bXdmac, bDstID, 1);

            return ((bXdmac << 8)) | ((i) & 0xFF);
        }
    }
    return XDMAD_ALLOC_FAILED;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initialize xDMA driver instance.
 * \param pXdmad Pointer to xDMA driver instance.
 * \param bPollingMode Polling DMA transfer:
 *                     1. Via XDMAD_IsTransferDone(); or
 *                     2. Via XDMAD_Handler().
 */
void XDMAD_Initialize( sXdmad *pXdmad, uint8_t bPollingMode )
{
    uint32_t i, j;

    pXdmad->pXdmacs[0] = XDMAC0;
    pXdmad->pXdmacs[1] = XDMAC1;
    pXdmad->pollingMode = bPollingMode;
    pXdmad->numControllers = XDMAC_CONTROLLER_NUM;
    pXdmad->numChannels    = XDMAC_CHANNEL_NUM;

    for (i = 0; i < pXdmad->numControllers; i ++)
    {
        for (j = 0; j < pXdmad->numChannels; j ++)
        {
            pXdmad->XdmaChannels[i][j].fCallback = 0;
            pXdmad->XdmaChannels[i][j].pArg      = 0;
            pXdmad->XdmaChannels[i][j].bIrqOwner    = 0;
            pXdmad->XdmaChannels[i][j].bSrcPeriphID = 0;
            pXdmad->XdmaChannels[i][j].bDstPeriphID = 0;
            pXdmad->XdmaChannels[i][j].bSrcTxIfID   = 0;
            pXdmad->XdmaChannels[i][j].bSrcRxIfID   = 0;
            pXdmad->XdmaChannels[i][j].bDstTxIfID   = 0;
            pXdmad->XdmaChannels[i][j].bDstRxIfID   = 0;
            pXdmad->XdmaChannels[i][j].state = XDMAD_FREE;
        }
    }
}


/**
 * \brief Allocate a XDMA channel for upper layer.
 * \param pXdmad  Pointer to xDMA driver instance.
 * \param bSrcID Source peripheral ID, 0xFF for memory.
 * \param bDstID Destination peripheral ID, 0xFF for memory.
 * \return Channel number if allocation sucessful, return
 * XDMAD_ALLOC_FAILED if allocation failed.
 */
uint32_t XDMAD_AllocateChannel( sXdmad *pXdmad,
                                uint8_t bSrcID,
                                uint8_t bDstID)
{
    uint32_t _iController;
    uint32_t dwChannel = XDMAD_ALLOC_FAILED;
    for ( _iController = 0; _iController < pXdmad->numControllers; _iController ++)
    {
        dwChannel = XDMAD_AllocateXdmacChannel( pXdmad, _iController, bSrcID, bDstID );
        if (dwChannel != XDMAD_ALLOC_FAILED)
            break;
    }
    return dwChannel;
}

/**
 * \brief Free the specified xDMA channel.
 * \param pXdmad     Pointer to xDMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 */
eXdmadRC XDMAD_FreeChannel( sXdmad *pXdmad, 
                            uint32_t dwChannel )
{
    uint8_t _iController = (dwChannel >> 8);
    uint8_t iChannel    = (dwChannel) & 0xFF;

    switch ( pXdmad->XdmaChannels[_iController][iChannel].state )
    {
        case XDMAD_IN_XFR:
            return XDMAD_BUSY;
        case XDMAD_IN_USE:
            pXdmad->XdmaChannels[_iController][iChannel].state = XDMAD_FREE;
            break;
    }
    return XDMAD_OK;
}


/**
 * \brief Set the callback function for xDMA channel transfer.
 * \param pXdmad     Pointer to xDMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 * \param fCallback Pointer to callback function.
 * \param pArg Pointer to optional argument for callback.
 */
eXdmadRC XDMAD_SetCallback( sXdmad *pXdmad, 
                            uint32_t dwChannel,
                            XdmadTransferCallback fCallback, 
                            void* pArg )
{
    uint8_t _iController = (dwChannel >> 8);
    uint8_t iChannel    = (dwChannel) & 0xFF;
    if ( pXdmad->XdmaChannels[_iController][iChannel].state == XDMAD_FREE )
        return XDMAD_ERROR;
    else if ( pXdmad->XdmaChannels[_iController][iChannel].state == XDMAD_IN_XFR )
        return XDMAD_BUSY;

    pXdmad->XdmaChannels[_iController][iChannel].fCallback = fCallback;
    pXdmad->XdmaChannels[_iController][iChannel].pArg = pArg;

    return XDMAD_OK;
}


/**
 * \brief Enable clock of the xDMA peripheral, Enable the dma peripheral,
 * configure configuration register for xDMA transfer.
 * \param pXdmad     Pointer to xDMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 * \param dwCfg     Configuration value.
 */
eXdmadRC XDMAD_PrepareChannel( sXdmad *pXdmad, uint32_t dwChannel)
{
    uint8_t _iController = (dwChannel >> 8);
    uint8_t iChannel    = (dwChannel) & 0xFF;
    uint32_t _dwdmaId;

    Xdmac *pXdmac = pXdmad->pXdmacs[_iController];

    if ( pXdmad->XdmaChannels[_iController][iChannel].state == XDMAD_FREE )
        return XDMAD_ERROR;
    else if ( pXdmad->XdmaChannels[_iController][iChannel].state == XDMAD_IN_XFR )
        return XDMAD_BUSY;
    /* Clear dummy status */
    XDMAC_GetChStatus( pXdmac );
    XDMAC_GetGIsr (pXdmac);
    _dwdmaId = (_iController == 0) ? ID_XDMAC0 : ID_XDMAC1;
    /* Enable clock of the DMA peripheral */
    if (!PMC_IsPeriphEnabled( _dwdmaId ))
    {
        PMC_EnablePeripheral( _dwdmaId );
    }
    /* Clear dummy status */
    XDMAC_GetChannelIsr( pXdmac,iChannel );
    /* Disables XDMAC interrupt for the given channel. */
    XDMAC_DisableGIt (pXdmac, -1);
    XDMAC_DisableChannelIt (pXdmac, iChannel, -1);
    /* Disable the given dma channel. */
    XDMAC_DisableChannel( pXdmac, iChannel );
    XDMAC_SetSourceAddr(pXdmac, iChannel, 0);
    XDMAC_SetDestinationAddr(pXdmac, iChannel, 0);
    XDMAC_SetBlockControl(pXdmac, iChannel, 0);
    XDMAC_SetChannelConfig( pXdmac, iChannel, 0x20);
    XDMAC_SetDescriptorAddr(pXdmac, iChannel, 0, 0);
    XDMAC_SetDescriptorControl(pXdmac, iChannel, 0);
    return XDMAD_OK;
}

/**
 * \brief xDMA interrupt handler
 * \param pxDmad Pointer to DMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 */
void XDMAD_Handler( sXdmad *pDmad, uint32_t dwChannel)
{
    Xdmac *pXdmac;
    sXdmadChannel *pCh;
    uint32_t chSr;
    uint32_t xdmaRc = XDMAD_OK;
    uint8_t bExec = 0;

    uint8_t _iController = (dwChannel >> 8);
    uint8_t iChannel    = (dwChannel) & 0xFF;

    pXdmac = pDmad->pXdmacs[_iController];
    pCh = &pDmad->XdmaChannels[_iController][iChannel];
    if ( pCh->state == XDMAD_FREE) return ;
    
    if ((XDMAC_GetChStatus(pXdmac) & ( XDMAC_GS_ST0 << iChannel)) == 0) 
    {
        chSr = XDMAC_GetChannelIsr( pXdmac,iChannel);
        if (chSr & XDMAC_CIS_LIS)
        {
             pCh->state = XDMAD_BUF ;
        }
        if (chSr & XDMAC_CIS_DIS )
        {
            if ( pCh->state == XDMAD_BUF)
            {
                 pCh->state = XDMAD_IN_USE ;
                 bExec = 1;
                 xdmaRc = XDMAD_OK;
            }
        }
    }
    /* Execute callback */
    if (bExec && pCh->fCallback)
    {
        pCh->fCallback(iChannel, pCh->pArg);
    }
}

/**
 * \brief Check if DMA transfer is finished.
 *        In polling mode XDMAD_Handler() is polled.
 * \param pDmad     Pointer to DMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 */
eXdmadRC XDMAD_IsTransferDone( sXdmad *pXdmad, uint32_t dwChannel )
{
    uint8_t _iController = (dwChannel >> 8);
    uint8_t iChannel    = (dwChannel) & 0xFF;

    if ( pXdmad->XdmaChannels[_iController][iChannel].state == XDMAD_FREE )
        return XDMAD_ERROR;
    else if ( pXdmad->XdmaChannels[_iController][iChannel].state != XDMAD_IN_USE )
    {
        if(pXdmad->pollingMode)  XDMAD_Handler( pXdmad, dwChannel);
        return XDMAD_BUSY;
    }
    return XDMAD_OK;
}


/**
 * \brief Configure DMA for a single transfer.
 * \param pXdmad     Pointer to xDMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 */
eXdmadRC XDMAD_ConfigureTransfer( sXdmad *pXdmad,
                                  uint32_t dwChannel,
                                  sXdmadCfg *pXdmaParam,
                                  uint32_t dwXdmaDescCfg,
                                  uint32_t dwXdmaDescAddr)
{
    uint8_t _iController = (dwChannel >> 8);
    uint8_t iChannel    = (dwChannel) & 0xFF;
    Xdmac *pXdmac = pXdmad->pXdmacs[_iController];

    if ( pXdmad->XdmaChannels[_iController][iChannel].state == XDMAD_FREE )
        return XDMAD_ERROR;
    if ( pXdmad->XdmaChannels[_iController][iChannel].state == XDMAD_IN_XFR )
        return XDMAD_BUSY;
    /* Linked List is enabled */
    if ((dwXdmaDescCfg & XDMAC_CNDC_NDE) == XDMAC_CNDC_NDE_DSCR_FETCH_EN)
    {
        if ((dwXdmaDescCfg & XDMAC_CNDC_NDVIEW_Msk) == XDMAC_CNDC_NDVIEW_NDV0) {
            XDMAC_SetChannelConfig( pXdmac, iChannel, pXdmaParam->mbr_cfg );
            XDMAC_SetSourceAddr(pXdmac, iChannel, pXdmaParam->mbr_sa);
            XDMAC_SetDestinationAddr(pXdmac, iChannel, pXdmaParam->mbr_da);
        }
        if ((dwXdmaDescCfg & XDMAC_CNDC_NDVIEW_Msk) == XDMAC_CNDC_NDVIEW_NDV1) {
            XDMAC_SetChannelConfig( pXdmac, iChannel, pXdmaParam->mbr_cfg );
        }
        XDMAC_SetDescriptorAddr(pXdmac, iChannel, dwXdmaDescAddr, 0);
        XDMAC_SetDescriptorControl(pXdmac, iChannel, dwXdmaDescCfg);
        XDMAC_DisableChannelIt (pXdmac, iChannel, -1);
        XDMAC_EnableChannelIt (pXdmac,
                               iChannel,
                               XDMAC_CIE_LIE);
    }
    /* LLI is disabled. */
    else
    {
        XDMAC_SetSourceAddr(pXdmac, iChannel, pXdmaParam->mbr_sa);
        XDMAC_SetDestinationAddr(pXdmac, iChannel, pXdmaParam->mbr_da);
        XDMAC_SetMicroblockControl(pXdmac, iChannel, pXdmaParam->mbr_ubc);
        XDMAC_SetBlockControl(pXdmac, iChannel, pXdmaParam->mbr_bc);
        XDMAC_SetDataStride_MemPattern(pXdmac, iChannel, pXdmaParam->mbr_ds);
        XDMAC_SetSourceMicroBlockStride(pXdmac, iChannel, pXdmaParam->mbr_sus);
        XDMAC_SetDestinationMicroBlockStride(pXdmac, iChannel, pXdmaParam->mbr_dus);
        XDMAC_SetChannelConfig( pXdmac, iChannel, pXdmaParam->mbr_cfg );
        XDMAC_SetDescriptorAddr(pXdmac, iChannel, 0, 0);
        XDMAC_SetDescriptorControl(pXdmac, iChannel, 0);
        XDMAC_EnableChannelIt (pXdmac,
                               iChannel,
                               XDMAC_CIE_BIE   |
                               XDMAC_CIE_DIE   |
                               XDMAC_CIE_FIE   |
                               XDMAC_CIE_RBIE  |
                               XDMAC_CIE_WBIE  |
                               XDMAC_CIE_ROIE);
    }
    return XDMAD_OK;
}

/**
 * \brief Start xDMA transfer.
 * \param pXdmad     Pointer to XDMA driver instance.
 * \param dwChannel ControllerNumber << 8 | ChannelNumber.
 */
eXdmadRC XDMAD_StartTransfer( sXdmad *pXdmad, uint32_t dwChannel )
{
    uint8_t _iController = (dwChannel >> 8);
    uint8_t iChannel    = (dwChannel) & 0xFF;

    Xdmac *pXdmac = pXdmad->pXdmacs[_iController];

    if ( pXdmad->XdmaChannels[_iController][iChannel].state == XDMAD_FREE )
        return XDMAD_ERROR;
    else if ( pXdmad->XdmaChannels[_iController][iChannel].state == XDMAD_IN_XFR )
        return XDMAD_BUSY;
    /* Change state to transferring */
    pXdmad->XdmaChannels[_iController][iChannel].state = XDMAD_IN_XFR;
    
    if ( pXdmad->pollingMode == 0 )
    {
        XDMAC_EnableGIt( pXdmac,1 << iChannel);
    }
    XDMAC_EnableChannel(pXdmac, iChannel);
    return XDMAD_OK;
}

/**@}*/

