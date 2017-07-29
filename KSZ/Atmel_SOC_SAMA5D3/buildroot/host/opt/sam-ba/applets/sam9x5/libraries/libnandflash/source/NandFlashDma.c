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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include <libnandflash.h>
/*----------------------------------------------------------------------------
 *        Local Variables
 *----------------------------------------------------------------------------*/

/** Current initialized sDmad instance*/
static sDmad *pCurrentDma = 0;

/* DMA driver instance */
static uint32_t nandDmaRxChannel;
static uint32_t nandDmaTxChannel;

/* Linked lists for single transfer buffer chaining structure instance. */
static sDmaTransferDescriptor dmaNandRxDesc;
static sDmaTransferDescriptor dmaNandTxDesc;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Configure the DMA Channels.
 * Channels are disabled after configure.
 * \returns 0 if the dma channel configuration successfully; otherwise returns
 * NandCommon_ERROR_XXX.
 */
uint8_t NandFlashConfigureDmaChannels( sDmad *pDmad )
{
    uint32_t dwCfg;
    /* Configure the allocated DMA channel. */
    dwCfg = 0
           | DMAC_CFG_SRC_PER( 0 ) 
           | DMAC_CFG_DST_PER( 0 )
           | DMAC_CFG_FIFOCFG_HALF_CFG;

    /* Allocate a DMA channel for NAND RX. */
    nandDmaRxChannel = DMAD_AllocateChannel( pDmad, DMAD_TRANSFER_MEMORY, DMAD_TRANSFER_MEMORY);
    {
        if ( nandDmaRxChannel == DMAD_ALLOC_FAILED ) 
        {
            return NandCommon_ERROR_DMA;
        }
    }
    
    if (DMAD_PrepareChannel( pDmad, nandDmaRxChannel, dwCfg )) return NandCommon_ERROR_DMA;
    dmaNandRxDesc.dwSrcAddr = 0;
    dmaNandRxDesc.dwDstAddr = 0;
    dmaNandRxDesc.dwCtrlA   = 0;
    dmaNandRxDesc.dwCtrlB   = DMAC_CTRLB_SIF_AHB_IF1 | DMAC_CTRLB_DIF_AHB_IF0 
                            | DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR 
                            | DMAC_CTRLB_FC_MEM2MEM_DMA_FC
                            | DMAC_CTRLB_SRC_INCR_FIXED | DMAC_CTRLB_DST_INCR_INCREMENTING;
    if (DMAD_PrepareSingleTransfer( pDmad, nandDmaRxChannel, &dmaNandRxDesc )) return NandCommon_ERROR_DMA;


    /* Allocate a DMA channel for NAND TX. */
    nandDmaTxChannel = DMAD_AllocateChannel( pDmad, DMAD_TRANSFER_MEMORY, DMAD_TRANSFER_MEMORY);
    {
        if ( nandDmaTxChannel == DMAD_ALLOC_FAILED ) 
        {
            return NandCommon_ERROR_DMA;
        }
    }
    if (DMAD_PrepareChannel( pDmad, nandDmaTxChannel, dwCfg )) return NandCommon_ERROR_DMA;
    dmaNandTxDesc.dwSrcAddr = 0;
    dmaNandTxDesc.dwDstAddr = 0;
    dmaNandTxDesc.dwCtrlA   = 0;
    dmaNandTxDesc.dwCtrlB   = DMAC_CTRLB_SIF_AHB_IF1 | DMAC_CTRLB_DIF_AHB_IF0 
                           | DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR 
                           | DMAC_CTRLB_FC_MEM2MEM_DMA_FC
                           | DMAC_CTRLB_SRC_INCR_INCREMENTING | DMAC_CTRLB_DST_INCR_FIXED;
    if (DMAD_PrepareSingleTransfer( pDmad, nandDmaTxChannel, &dmaNandTxDesc )) return NandCommon_ERROR_DMA;
    pCurrentDma = pDmad;
    return 0;
}

/**
 * \brief Configure the DMA Channels for Tx.
 * \param ramAddr Source address to be transfered.
 * \param size Transfer size in byte.
 * \returns 0 if the dma channel configuration and transfer successfully; otherwise returns
 * NandCommon_ERROR_XXX.
 */
uint8_t NandFlashDmaTransferRam2Nand( uint32_t ramAddr, uint32_t size )
{ 
    if (!pCurrentDma) return NandCommon_ERROR_DMA;
    dmaNandTxDesc.dwSrcAddr = ramAddr;
    dmaNandTxDesc.dwDstAddr = (uint32_t) BOARD_NF_DATA_ADDR;
    dmaNandTxDesc.dwCtrlA   = ((size + 3) >> 2) | DMAC_CTRLA_SRC_WIDTH_WORD | DMAC_CTRLA_DST_WIDTH_WORD;
    if (DMAD_PrepareSingleTransfer( pCurrentDma, nandDmaTxChannel, &dmaNandTxDesc )) return NandCommon_ERROR_DMA;
    if (DMAD_StartTransfer( pCurrentDma, nandDmaTxChannel )) 
        return NandCommon_ERROR_DMA;
    while (DMAD_IsTransferDone( pCurrentDma, nandDmaTxChannel ));
    return 0;
}  

/**
 * \brief Configure the DMA Channels for Rx.
 * \param ramAddr Destination address to be transfered.
 * \param size Transfer size in byte.
 * \returns 0 if the dma channel configuration and transfer successfully; otherwise returns
 * NandCommon_ERROR_XXX.
 */
uint8_t NandFlashDmaTransferNand2Ram( uint32_t ramAddr, uint32_t size )
{
    if (!pCurrentDma) return NandCommon_ERROR_DMA;
    dmaNandRxDesc.dwSrcAddr = (uint32_t) BOARD_NF_DATA_ADDR;
    dmaNandRxDesc.dwDstAddr = ramAddr;
    dmaNandRxDesc.dwCtrlA   = ((size + 3) >> 2) | DMAC_CTRLA_SRC_WIDTH_WORD | DMAC_CTRLA_DST_WIDTH_WORD;
    if (DMAD_PrepareSingleTransfer( pCurrentDma, nandDmaRxChannel, &dmaNandRxDesc )) return NandCommon_ERROR_DMA;
    if (DMAD_StartTransfer( pCurrentDma, nandDmaRxChannel )) 
        return NandCommon_ERROR_DMA;
    while (DMAD_IsTransferDone( pCurrentDma, nandDmaRxChannel ));
    return 0;
} 

/**
 * \brief Return DMA flag: 1: Actived 0: inactive.
 */
uint8_t NandFlashIsDmaActived( void )
{
    if (pCurrentDma) return 1;
    return 0;
}

/**
 * \brief Free the nand DMA Rx and Tx channel.
 * \param pDmad  Pointer to a Dmad instance. 
 */
void NandFlashFreeDma( void )
{
    if (!pCurrentDma) return; /* already free */
    while(DMAD_FreeChannel( pCurrentDma, nandDmaRxChannel ));
    while(DMAD_FreeChannel( pCurrentDma, nandDmaTxChannel ));
    pCurrentDma = 0;
}

