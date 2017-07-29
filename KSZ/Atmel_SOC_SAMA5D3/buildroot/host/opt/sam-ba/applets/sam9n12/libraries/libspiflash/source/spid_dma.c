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

 /**
 * \addtogroup spi_dma_module SPI DMA driver
 * \ingroup lib_spiflash
 * \section Usage
 *
 * <ul>
 * <li> SPID_Configure() initializes and configures the SPI peripheral and DMA for data transfer.</li>
 * <li> Configures the parameters for the device corresponding to the cs value by SPID_ConfigureCS(). </li>
 * <li> Starts a SPI master transfer. This is a non blocking function SPID_SendCommand(). It will
 * return as soon as the transfer is started..</li>
 * </ul>
 *
 */

/**
 * \file
 *
 * Implementation for the SPI Flash with DMA driver.
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

/** DMA support */
#define USE_SPI_DMA

/** DMA Link List size for spi transation*/
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
static sDmaTransferDescriptor dmaTxLinkList[DMA_SPI_LLI];
static sDmaTransferDescriptor dmaRxLinkList[DMA_SPI_LLI];
#endif

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

#if defined(USE_SPI_DMA)
/**
 * \brief SPI DMA Rx callback
 * Invoked on SPi DMA reception done.
 * \param dmaStatus DMA status.
 * \param pArg Pointer to callback argument - Pointer to Spid instance.   
 */ 
static void SPID_Rx_Cb(uint32_t dmaStatus, Spid* pArg)
{
    SpidCmd *pSpidCmd = pArg->pCurrentCommand;
    Spi *pSpiHw = pArg->pSpiHw;

    if (dmaStatus == DMAD_PARTIAL_DONE)
        return;

    /* Disable the SPI TX & RX */
    SPI_Disable ( pSpiHw );
    
    /* Disable the SPI Peripheral */
    PMC_DisablePeripheral ( pArg->spiId );
    
    /* Release CS */
    SPI_ReleaseCS(pSpiHw);
    
    /* Release the DMA channels */
    DMAD_FreeChannel(pArg->pDmad, spiDmaRxChannel);
    DMAD_FreeChannel(pArg->pDmad, spiDmaTxChannel);

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
    uint32_t dwCfg;
    uint8_t iController;

    /* Allocate a DMA channel for SPI0 TX. */
    spiDmaTxChannel = DMAD_AllocateChannel( pSpid->pDmad,
                                            DMAD_TRANSFER_MEMORY, ID_SPI0);
    {
        if ( spiDmaTxChannel == DMAD_ALLOC_FAILED ) 
        {
            return SPID_ERROR;
        }
    }
    /* Allocate a DMA channel for SPI0 RX. */
    spiDmaRxChannel = DMAD_AllocateChannel( pSpid->pDmad,
                                            ID_SPI0, DMAD_TRANSFER_MEMORY);
    {
        if ( spiDmaRxChannel == DMAD_ALLOC_FAILED ) 
        {
            return SPID_ERROR;
        }
    }
    iController = (spiDmaRxChannel >> 8);
    /* Setup callbacks for SPI0 RX */
    DMAD_SetCallback(pSpid->pDmad, spiDmaRxChannel,
                     (DmadTransferCallback)SPID_Rx_Cb, pSpid);

    /* Configure the allocated DMA channel for SPI0 RX. */
    dwCfg = 0
           | DMAC_CFG_SRC_PER(
              DMAIF_Get_ChannelNumber( iController, ID_SPI0, DMAD_TRANSFER_RX ))
           | DMAC_CFG_DST_PER(
              DMAIF_Get_ChannelNumber( iController, ID_SPI0, DMAD_TRANSFER_RX ))
           | DMAC_CFG_SRC_H2SEL
           | DMAC_CFG_SOD
           | DMAC_CFG_FIFOCFG_ALAP_CFG;

    if (DMAD_PrepareChannel( pSpid->pDmad, spiDmaRxChannel, dwCfg ))
        return SPID_ERROR;

    iController = (spiDmaTxChannel >> 8);
    /* Setup callbacks for SPI0 TX (ignored) */
    DMAD_SetCallback(pSpid->pDmad, spiDmaTxChannel, NULL, NULL);

    /* Configure the allocated DMA channel for SPI0 TX. */
    dwCfg = 0
           | DMAC_CFG_SRC_PER(
              DMAIF_Get_ChannelNumber( iController, ID_SPI0, DMAD_TRANSFER_TX ))
           | DMAC_CFG_DST_PER(
              DMAIF_Get_ChannelNumber( iController, ID_SPI0, DMAD_TRANSFER_TX ))
           | DMAC_CFG_DST_H2SEL
           | DMAC_CFG_SOD
           | DMAC_CFG_FIFOCFG_ALAP_CFG;

    if ( DMAD_PrepareChannel( pSpid->pDmad, spiDmaTxChannel, dwCfg ))
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
static uint8_t _spid_configureLinkList(Spi *pSpiHw, void *pDmad, SpidCmd *pCommand)
{
    /* Setup RX Link List */
    dmaRxLinkList[0].dwSrcAddr = (uint32_t)&pSpiHw->SPI_RDR;
    dmaRxLinkList[0].dwDstAddr = (uint32_t)pCommand->pCmd;
    dmaRxLinkList[0].dwCtrlA   = pCommand->cmdSize | DMAC_CTRLA_SRC_WIDTH_BYTE | DMAC_CTRLA_DST_WIDTH_BYTE;
    dmaRxLinkList[0].dwCtrlB   = DMAC_CTRLB_FC_PER2MEM_DMA_FC | DMAC_CTRLB_SRC_INCR_FIXED | DMAC_CTRLB_DST_INCR_INCREMENTING;

    /* Setup TX Link List */                           
    dmaTxLinkList[0].dwSrcAddr = (uint32_t)pCommand->pCmd;
    dmaTxLinkList[0].dwDstAddr = (uint32_t)&pSpiHw->SPI_TDR;
    dmaTxLinkList[0].dwCtrlA   = pCommand->cmdSize | DMAC_CTRLA_SRC_WIDTH_BYTE  | DMAC_CTRLA_DST_WIDTH_BYTE;
    dmaTxLinkList[0].dwCtrlB   = DMAC_CTRLB_FC_MEM2PER_DMA_FC | DMAC_CTRLB_SRC_INCR_INCREMENTING | DMAC_CTRLB_DST_INCR_FIXED;

    /* In case command only */
    if (pCommand->pData == 0) {

        dmaRxLinkList[0].dwDscAddr = 0;
        dmaTxLinkList[0].dwDscAddr = 0;
    }
    /* In case Command & data */
    else {
        dmaRxLinkList[0].dwDscAddr = (uint32_t)&dmaRxLinkList[1];
        dmaRxLinkList[1].dwSrcAddr = (uint32_t)&pSpiHw->SPI_RDR;
        dmaRxLinkList[1].dwDstAddr = (uint32_t)pCommand->pData;
        dmaRxLinkList[1].dwCtrlA   = pCommand->dataSize | DMAC_CTRLA_SRC_WIDTH_BYTE | DMAC_CTRLA_DST_WIDTH_BYTE;
        dmaRxLinkList[1].dwCtrlB   = DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR | DMAC_CTRLB_FC_PER2MEM_DMA_FC
                                  | DMAC_CTRLB_SRC_INCR_FIXED | DMAC_CTRLB_DST_INCR_INCREMENTING;
        dmaRxLinkList[1].dwDscAddr = 0;
        dmaTxLinkList[0].dwDscAddr = (uint32_t)&dmaTxLinkList[1];
        dmaTxLinkList[1].dwSrcAddr = (uint32_t)pCommand->pData;
        dmaTxLinkList[1].dwDstAddr = (uint32_t)&pSpiHw->SPI_TDR;
        dmaTxLinkList[1].dwCtrlA   = pCommand->dataSize | DMAC_CTRLA_SRC_WIDTH_BYTE | DMAC_CTRLA_DST_WIDTH_BYTE;
        dmaTxLinkList[1].dwCtrlB   =  DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR | DMAC_CTRLB_FC_MEM2PER_DMA_FC
                                  | DMAC_CTRLB_SRC_INCR_INCREMENTING | DMAC_CTRLB_DST_INCR_FIXED;
        dmaTxLinkList[1].dwDscAddr    = 0;
    }
    if ( DMAD_PrepareMultiTransfer( pDmad, spiDmaRxChannel, &dmaRxLinkList[0]))
        return SPID_ERROR;
    if ( DMAD_PrepareMultiTransfer( pDmad, spiDmaTxChannel, &dmaTxLinkList[0]))
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
                         sDmad *pDmad )
{
    /* Initialize the SPI structure */
    pSpid->pSpiHw = pSpiHw;
    pSpid->spiId  = spiId;
    pSpid->semaphore = 1;
    pSpid->pCurrentCommand = 0;
    pSpid->pDmad = pDmad;

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
    if (_spid_configureLinkList(pSpiHw, pSpid->pDmad, pCommand))
        return SPID_ERROR_LOCK;

    // Initialize the callback
    pSpid->pCurrentCommand = pCommand;
    /* Enables the SPI to transfer and receive data. */
    SPI_Enable (pSpiHw );

    /* Start DMA 0(RX) && 1(TX) */
    if (DMAD_StartTransfer( pSpid->pDmad, spiDmaRxChannel )) 
        return SPID_ERROR_LOCK;
    if (DMAD_StartTransfer( pSpid->pDmad, spiDmaTxChannel )) 
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
    DMAD_Handler( pSpid->pDmad );
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
