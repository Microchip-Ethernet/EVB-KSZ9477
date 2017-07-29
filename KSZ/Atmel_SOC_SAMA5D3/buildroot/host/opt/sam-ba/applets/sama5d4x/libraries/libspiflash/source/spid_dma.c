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

 /**
 * \addtogroup spi_dma_module SPI xDMA driver
 * \ingroup lib_spiflash
 * \section Usage
 *
 * <ul>
 * <li> SPID_Configure() initializes and configures the SPI peripheral and xDMA for data transfer.</li>
 * <li> Configures the parameters for the device corresponding to the cs value by SPID_ConfigureCS(). </li>
 * <li> Starts a SPI master transfer. This is a non blocking function SPID_SendCommand(). It will
 * return as soon as the transfer is started..</li>
 * </ul>
 *
 */

/**
 * \file
 *
 * Implementation for the SPI Flash with xDMA driver.
 *
 */

 
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include <libspiflash.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** xDMA support */
#define USE_SPI_DMA

/** xDMA Link List size for spi transation*/
#define DMA_SPI_LLI     2

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

 /*----------------------------------------------------------------------------
 *        Local Variables
 *----------------------------------------------------------------------------*/

#if defined(USE_SPI_DMA)
/*  DMA driver instance */
static uint32_t spiDmaTxChannel;
static uint32_t spiDmaRxChannel;

/* Linked lists for multi transfer buffer chaining structure instance. */
__attribute__((aligned(4)))
static LinkedListDescriporView0 dmaTxLinkList[DMA_SPI_LLI];
__attribute__((aligned(4)))
static LinkedListDescriporView0 dmaRxLinkList[DMA_SPI_LLI];

#endif

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

#if defined(USE_SPI_DMA)
/**
 * \brief SPI xDMA Rx callback
 * Invoked on SPi DMA reception done.
 * \param channel DMA channel.
 * \param pArg Pointer to callback argument - Pointer to Spid instance.   
 */ 
static void SPID_Rx_Cb(uint32_t channel, Spid* pArg)
{
    SpidCmd *pSpidCmd = pArg->pCurrentCommand;
    Spi *pSpiHw = pArg->pSpiHw;
    if (channel != spiDmaRxChannel)
        return;

    /* Disable the SPI TX & RX */
    SPI_Disable ( pSpiHw );
    
    /* Disable the SPI Peripheral */
    PMC_DisablePeripheral ( pArg->spiId );
    
    /* Release CS */
    SPI_ReleaseCS(pSpiHw);
    
    /* Release the DMA channels */
    //printf("XDMAD_FreeChannel %x\n\r",spiDmaRxChannel);
    //printf("XDMAD_FreeChannel %x\n\r",spiDmaTxChannel);
    XDMAD_FreeChannel(pArg->pXdmad, spiDmaRxChannel);
    XDMAD_FreeChannel(pArg->pXdmad, spiDmaTxChannel);

    /* Release the dataflash semaphore */
    pArg->semaphore++;
        
    /* Invoke the callback associated with the current command */
    if (pSpidCmd && pSpidCmd->callback) {
    
        pSpidCmd->callback(0, pSpidCmd->pArgument);
    }
}

/**
 * \brief Configure the DMA Channels: 0 RX, 1 TX.
 * Channels are disabled after configure.
 * \returns 0 if the dma channel configuration successfully; otherwise returns
 * SPID_ERROR_XXX.
 */
static uint8_t _spid_configureDmaChannels( Spid* pSpid )
{
    /* Allocate a DMA channel for SPI0/1 TX. */
    spiDmaTxChannel = XDMAD_AllocateChannel( pSpid->pXdmad, XDMAD_TRANSFER_MEMORY, pSpid->spiId);
    {
        if ( spiDmaTxChannel == XDMAD_ALLOC_FAILED ) 
        {
            return SPID_ERROR;
        }
    }
    /* Allocate a DMA channel for SPI0/1 RX. */
    spiDmaRxChannel = XDMAD_AllocateChannel( pSpid->pXdmad, pSpid->spiId, XDMAD_TRANSFER_MEMORY);
    {
        if ( spiDmaRxChannel == XDMAD_ALLOC_FAILED ) 
        {
            return SPID_ERROR;
        }
    }
//    printf("_spid_configureDmaChannels TX:%x, RX:%x \n\r",spiDmaTxChannel,spiDmaRxChannel);
    /* Setup callbacks for SPI0/1 RX */
    XDMAD_SetCallback(pSpid->pXdmad, spiDmaRxChannel, (XdmadTransferCallback)SPID_Rx_Cb, pSpid);
    if (XDMAD_PrepareChannel( pSpid->pXdmad, spiDmaRxChannel ))
        return SPID_ERROR;

    /* Setup callbacks for SPI0/1 TX (ignored) */
    XDMAD_SetCallback(pSpid->pXdmad, spiDmaTxChannel, NULL, NULL);
    if ( XDMAD_PrepareChannel( pSpid->pXdmad, spiDmaTxChannel ))
        return SPID_ERROR;
    return 0;
}

/**
 * \brief Configure the DMA source and destination with Linker List mode.
 *
 * \param pCommand Pointer to command
  * \returns 0 if the dma multibuffer configuration successfully; otherwise returns
 * SPID_ERROR_XXX.
 */
static uint8_t _spid_configureLinkList(Spi *pSpiHw, void *pXdmad, SpidCmd *pCommand)
{
    sXdmadCfg xdmadRxCfg,xdmadTxCfg;
    uint32_t xdmaCndc;
    uint32_t spiId;
    if ((unsigned int)pSpiHw == (unsigned int)SPI0 ) spiId = ID_SPI0;
    if ((unsigned int)pSpiHw == (unsigned int)SPI1 ) spiId = ID_SPI1;
    /* Setup RX Link List */
    dmaRxLinkList[0].mbr_ubc = XDMA_UBC_NVIEW_NDV0 |
                               ((pCommand->pData == 0) ? 0: XDMA_UBC_NDE_FETCH_EN)|
                               XDMA_UBC_NDEN_UPDATED |
                               pCommand->cmdSize;
    dmaRxLinkList[0].mbr_ta = (uint32_t)pCommand->pCmd;
   
    /* Setup TX Link List */ 
    dmaTxLinkList[0].mbr_ubc = XDMA_UBC_NVIEW_NDV0 |
                               ((pCommand->pData == 0) ? 0: XDMA_UBC_NDE_FETCH_EN)|
                               XDMA_UBC_NSEN_UPDATED |
                               pCommand->cmdSize;
    dmaTxLinkList[0].mbr_ta = (uint32_t)pCommand->pCmd;

    /* In case command only */
    if (pCommand->pData == 0) {
        dmaRxLinkList[0].mbr_nda = 0;
        dmaTxLinkList[0].mbr_nda = 0;
    }
    /* In case Command & data */
    else {
        dmaRxLinkList[0].mbr_nda =(uint32_t)&dmaRxLinkList[1];
        dmaRxLinkList[1].mbr_ta = (uint32_t)pCommand->pData;
        dmaRxLinkList[1].mbr_ubc = XDMA_UBC_NVIEW_NDV0 |
                                   pCommand->dataSize;
        dmaRxLinkList[1].mbr_nda = 0;

        dmaTxLinkList[0].mbr_nda = (uint32_t)&dmaTxLinkList[1];
        dmaTxLinkList[1].mbr_ta = (uint32_t)pCommand->pData;
        dmaTxLinkList[1].mbr_ubc = XDMA_UBC_NVIEW_NDV0 |
                                   pCommand->dataSize;
        dmaTxLinkList[1].mbr_nda = 0;
    }
    xdmadRxCfg.mbr_sa = (uint32_t)&pSpiHw->SPI_RDR;
    xdmadRxCfg.mbr_cfg = XDMAC_CC_TYPE_PER_TRAN |
                         XDMAC_CC_MBSIZE_SINGLE |
                         XDMAC_CC_DSYNC_PER2MEM |
                         XDMAC_CC_CSIZE_CHK_1 |
                         XDMAC_CC_DWIDTH_BYTE|
                         XDMAC_CC_SIF_AHB_IF1 |
                         XDMAC_CC_DIF_AHB_IF0 |
                         XDMAC_CC_SAM_FIXED_AM |
                         XDMAC_CC_DAM_INCREMENTED_AM |
                         XDMAC_CC_PERID(XDMAIF_Get_ChannelNumber( 0, spiId, XDMAD_TRANSFER_RX ));
    
    xdmadTxCfg.mbr_da = (uint32_t)&pSpiHw->SPI_TDR;
    xdmadTxCfg.mbr_cfg = XDMAC_CC_TYPE_PER_TRAN |
                         XDMAC_CC_MBSIZE_SINGLE |
                         XDMAC_CC_DSYNC_MEM2PER |
                         XDMAC_CC_CSIZE_CHK_1 |
                         XDMAC_CC_DWIDTH_BYTE|
                         XDMAC_CC_SIF_AHB_IF0 |
                         XDMAC_CC_DIF_AHB_IF1 |
                         XDMAC_CC_SAM_INCREMENTED_AM |
                         XDMAC_CC_DAM_FIXED_AM |
                         XDMAC_CC_PERID(XDMAIF_Get_ChannelNumber( 0, spiId, XDMAD_TRANSFER_TX ));

    xdmaCndc = XDMAC_CNDC_NDVIEW_NDV0 | 
               XDMAC_CNDC_NDE_DSCR_FETCH_EN |
               XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED|
               XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED ;

     
     
    if (XDMAD_ConfigureTransfer( pXdmad, spiDmaRxChannel, &xdmadRxCfg, xdmaCndc, (uint32_t)&dmaRxLinkList[0]))
       return SPID_ERROR;
       
    if (XDMAD_ConfigureTransfer( pXdmad, spiDmaTxChannel, &xdmadTxCfg, xdmaCndc, (uint32_t)&dmaTxLinkList[0]))
        return SPID_ERROR;
    return 0;
}
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Initializes the Spid structure and the corresponding SPI & DMA hardware.
 * select value.
 * The driver will uses DMA channel 0 for RX and DMA channel 1 for TX.
 * The DMA channels are freed automatically when no SPI command processing.
 *
 * \param pSpid  Pointer to a Spid instance.
 * \param pSpiHw Associated SPI peripheral.
 * \param spiId  SPI peripheral identifier.
 * \param pDmad  Pointer to a Dmad instance. 
 */
uint32_t SPID_Configure( Spid *pSpid ,
                         Spi *pSpiHw , 
                         uint8_t spiId,
                         sXdmad *pXdmad )
{
    /* Initialize the SPI structure */
    pSpid->pSpiHw = pSpiHw;
    pSpid->spiId  = spiId;
    pSpid->semaphore = 1;
    pSpid->pCurrentCommand = 0;
    pSpid->pXdmad = pXdmad;

    /* Enable the SPI Peripheral ,Execute a software reset of the SPI, Configure SPI in Master Mode*/
    SPI_Configure ( pSpiHw, pSpid->spiId, SPI_MR_MSTR | SPI_MR_MODFDIS | SPI_MR_PCS_Msk );
    /* Disable the SPI Peripheral */
    PMC_DisablePeripheral (pSpid->spiId );
    return 0;
}

/**
 * \brief Configures the parameters for the device corresponding to the cs value.
 *
 * \param pSpid  Pointer to a Spid instance.
 * \param cs number corresponding to the SPI chip select.
 * \param csr SPI_CSR value to setup.
 */
void SPID_ConfigureCS( Spid *pSpid, 
                       uint32_t dwCS, 
                       uint32_t dwCsr)
{
    Spi *pSpiHw = pSpid->pSpiHw;
    
    /* Enable the SPI Peripheral */
    PMC_EnablePeripheral (pSpid->spiId );
    /* Configure SPI Chip Select Register */
    SPI_ConfigureNPCS( pSpiHw, dwCS, dwCsr );
    /* Disable the SPI Peripheral */
    PMC_DisablePeripheral (pSpid->spiId );
}

/**
 * \brief Starts a SPI master transfer. This is a non blocking function. It will
 *  return as soon as the transfer is started.
 *
 * \param pSpid  Pointer to a Spid instance.
 * \param pCommand Pointer to the SPI command to execute.
 * \returns 0 if the transfer has been started successfully; otherwise returns
 * SPID_ERROR_LOCK is the driver is in use, or SPID_ERROR if the command is not
 * valid.
 */
uint32_t SPID_SendCommand( Spid *pSpid, SpidCmd *pCommand)
{
    Spi *pSpiHw = pSpid->pSpiHw;
         
    /* Try to get the dataflash semaphore */
    if (pSpid->semaphore == 0) {
    
         return SPID_ERROR_LOCK;
    }
     pSpid->semaphore--;

    /* Enable the SPI Peripheral */
    PMC_EnablePeripheral (pSpid->spiId );
    
    /* SPI chip select */
    SPI_ChipSelect (pSpiHw, 1 << pCommand->spiCs);

#if !defined(USE_SPI_DMA)
    /* Initialize the callback */
    pSpid->pCurrentCommand = pCommand;
    /* Enables the SPI to transfer and receive data. */
    SPI_Enable (pSpiHw );
    {
        uint32_t i;
        /* Transfer command */
        for (i = 0; i < pCommand->cmdSize; i ++)
        {
            SPI_Write(pSpiHw, pCommand->spiCs, pCommand->pCmd[i]);
            SPI_Read(pSpiHw);
        }
        /* Transfer data */
        for (i = 0; i < pCommand->dataSize; i ++)
        {
            SPI_Write(pSpiHw, pCommand->spiCs, pCommand->pData[i]);
            pCommand->pData[i] = SPI_Read(pSpiHw);
        }
        SPI_ReleaseCS(pSpiHw);
        
        /* Unlock */
        pSpid->semaphore ++;
        
        /* Callback */
        if (pCommand->callback)
        {
            pCommand->callback(0, pCommand->pArgument);
        }
    }
#else
    /* Initialize DMA controller using channel 0 for RX, 1 for TX. */
    if (_spid_configureDmaChannels(pSpid) )
        return SPID_ERROR_LOCK;
    if (_spid_configureLinkList(pSpiHw, pSpid->pXdmad, pCommand))
        return SPID_ERROR_LOCK;

    // Initialize the callback
    pSpid->pCurrentCommand = pCommand;
    /* Enables the SPI to transfer and receive data. */
    SPI_Enable (pSpiHw );

    /* Start DMA 0(RX) && 1(TX) */
    if (XDMAD_StartTransfer( pSpid->pXdmad, spiDmaRxChannel )) 
        return SPID_ERROR_LOCK;
    if (XDMAD_StartTransfer( pSpid->pXdmad, spiDmaTxChannel )) 
        return SPID_ERROR_LOCK;
#endif
    return 0;
}

/**
 * \brief SPI transfer ISR.
 */
void SPID_Handler( Spid *pSpid )
{
    pSpid = pSpid;
}

/**
 * \brief DMA transfer ISR for SPI driver.
 */
void SPID_DmaHandler( Spid *pSpid )
{
    XDMAD_Handler( pSpid->pXdmad, spiDmaRxChannel );
    XDMAD_Handler( pSpid->pXdmad, spiDmaTxChannel );
}

/**
 * \brief Check if the SPI driver is busy.
 *
 * \param pSpid  Pointer to a Spid instance.
 * \returns 1 if the SPI driver is currently busy executing a command; otherwise
 */
uint32_t SPID_IsBusy(const Spid *pSpid)
{
    if (pSpid->semaphore == 0) {

        return 1;
    }
    else {

        return 0;
    }
}
