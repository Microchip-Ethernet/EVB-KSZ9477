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

/** \file */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include <libnandflash.h>
/*----------------------------------------------------------------------------
 *        Local Variables
 *----------------------------------------------------------------------------*/

/** Current initialized sXdmad instance*/
static sXdmad *pCurrentDma = 0;

/* DMA driver instance */
static uint32_t nandDmaRxChannel;
static uint32_t nandDmaTxChannel;


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Configure the DMA Channels.
 * Channels are disabled after configure.
 * \returns 0 if the dma channel configuration successfully; otherwise returns
 * NandCommon_ERROR_XXX.
 */
uint8_t NandFlashConfigureDmaChannels( sXdmad *pXdmad )
{
    /* Allocate a DMA channel for NAND RX. */
    nandDmaRxChannel = XDMAD_AllocateChannel( pXdmad, XDMAD_TRANSFER_MEMORY, XDMAD_TRANSFER_MEMORY);
    {
        if ( nandDmaRxChannel == XDMAD_ALLOC_FAILED ) 
        {
            return NandCommon_ERROR_DMA;
        }
    }
    /* Allocate a DMA channel for NAND TX. */
    nandDmaTxChannel = XDMAD_AllocateChannel( pXdmad, XDMAD_TRANSFER_MEMORY, XDMAD_TRANSFER_MEMORY);
    {
        if ( nandDmaTxChannel == XDMAD_ALLOC_FAILED ) 
        {
            return NandCommon_ERROR_DMA;
        }
    }
    pCurrentDma = pXdmad;
    return 0;
}

/**
 * \brief Configure the DMA Channels for Tx.
 * \param ramAddr Source address to be transfered.
 * \param destAddr Destination address to be transfered.
 * \param size Transfer size in byte.
 * \returns 0 if the dma channel configuration and transfer successfully; otherwise returns
 * NandCommon_ERROR_XXX.
 */
uint8_t NandFlashDmaTransferToNand( uint32_t srcAddr, uint32_t destAddr, uint32_t size )
{ 
    sXdmadCfg xdmadCfg;
    uint8_t nfcSram = 0;
    if (!pCurrentDma) return NandCommon_ERROR_DMA;
    //CP15_coherent_dcache_for_dma(srcAddr, srcAddr + size );
    if (isSmcOpNfcSramEn()) nfcSram = 1;
    xdmadCfg.mbr_ubc = ((size + 3) >> 2);
    xdmadCfg.mbr_sa = (uint32_t)srcAddr;
    xdmadCfg.mbr_da = (uint32_t)destAddr;
    xdmadCfg.mbr_cfg = XDMAC_CC_TYPE_MEM_TRAN |
                       XDMAC_CC_MEMSET_NORMAL_MODE |
                       XDMAC_CC_CSIZE_CHK_1 |
                       XDMAC_CC_DWIDTH_WORD |
                       XDMAC_CC_SIF_AHB_IF0 |
                       XDMAC_CC_DIF_AHB_IF0 |
                       XDMAC_CC_SAM_INCREMENTED_AM|
                       nfcSram ? XDMAC_CC_DAM_INCREMENTED_AM : XDMAC_CC_DAM_FIXED_AM;
    XDMAD_ConfigureTransfer( pCurrentDma, nandDmaTxChannel, &xdmadCfg, 0, 0);
    if (XDMAD_StartTransfer( pCurrentDma, nandDmaTxChannel ))
        return NandCommon_ERROR_DMA;
    while (XDMAD_IsTransferDone( pCurrentDma, nandDmaTxChannel ));
    return 0;
}  

/**
 * \brief Configure the DMA Channels for Rx.
 * \param scrAddr Source address to be transfered.
 * \param destAddr Destination address to be transfered.
 * \param size Transfer size in byte.
 * \returns 0 if the dma channel configuration and transfer successfully; otherwise returns
 * NandCommon_ERROR_XXX.
 */
uint8_t NandFlashDmaTransferFromNand( uint32_t srcAddr, uint32_t destAddr, uint32_t size )
{
    sXdmadCfg xdmadCfg; 
    uint8_t nfcSram = 0;    
    if (!pCurrentDma) return NandCommon_ERROR_DMA;
    //CP15_coherent_dcache_for_dma(srcAddr, srcAddr + size );
    if (isSmcOpNfcSramEn()) nfcSram = 1;
    xdmadCfg.mbr_ubc = ((size + 3) >> 2);
    xdmadCfg.mbr_sa = (uint32_t)srcAddr;
    xdmadCfg.mbr_da = (uint32_t)destAddr;
    xdmadCfg.mbr_cfg = XDMAC_CC_TYPE_MEM_TRAN |
                       XDMAC_CC_MEMSET_NORMAL_MODE |
                       XDMAC_CC_CSIZE_CHK_1 |
                       XDMAC_CC_DWIDTH_WORD |
                       XDMAC_CC_SIF_AHB_IF0 |
                       XDMAC_CC_DIF_AHB_IF0 |
                       nfcSram ? XDMAC_CC_SAM_INCREMENTED_AM : XDMAC_CC_SAM_FIXED_AM |
                       XDMAC_CC_DAM_INCREMENTED_AM;
    XDMAD_ConfigureTransfer( pCurrentDma, nandDmaRxChannel, &xdmadCfg, 0, 0);
    if (XDMAD_StartTransfer( pCurrentDma, nandDmaRxChannel ))
        return NandCommon_ERROR_DMA;
    while (XDMAD_IsTransferDone( pCurrentDma, nandDmaRxChannel ));
//    CP15_flush_dcache_for_dma(destAddr, destAddr + size );
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
 * \param pXdmad  Pointer to a Dmad instance. 
 */
void NandFlashFreeDma( void )
{
    if (!pCurrentDma) return; /* already free */
    while(XDMAD_FreeChannel( pCurrentDma, nandDmaRxChannel ));
    while(XDMAD_FreeChannel( pCurrentDma, nandDmaTxChannel ));
    pCurrentDma = 0;
}

