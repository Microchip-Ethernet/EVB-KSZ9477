/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
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

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "spid.h"
#include <board.h>
#include <dma/dma.h>
#include <drivers/dmad/dmad.h>
#include <irq/irq.h>

//------------------------------------------------------------------------------
//         Defines
//------------------------------------------------------------------------------

/// DMA Link List size
#define SIZE_LL     2

/// DMA Width BYTE
#define DMA_WIDTH   0

//------------------------------------------------------------------------------
//         Macros
//------------------------------------------------------------------------------

/// Write PMC register
#define WRITE_PMC(pPmc, regName, value) pPmc->regName = (value)

/// Write SPI register
#define WRITE_SPI(pSpi, regName, value) pSpi->regName = (value)

/// Read SPI registers
#define READ_SPI(pSpi, regName) (pSpi->regName)

/// Enable Peripheral
#define PERIPH_ENABLE(id) \
    WRITE_PMC(AT91C_BASE_PMC, PMC_PCER, (1 << (id)))
/// Disable Peripheral
#define PERIPH_DISABLE(id) \
    WRITE_PMC(AT91C_BASE_PMC, PMC_PCDR, (1 << (id)))


//------------------------------------------------------------------------------
//         Local Variables
//------------------------------------------------------------------------------

/// Linked lists for multi transfer buffer chaining structure instance.
static DmaLinkList dmaTxLinkList[SIZE_LL];
static DmaLinkList dmaRxLinkList[SIZE_LL];

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Configure the DMA Channels: 0 RX, 1 TX.
/// Channels are disabled after configure.
//------------------------------------------------------------------------------
static void configureDmaChannels(void)
{
    // Enable DMA Peripheral
    PERIPH_ENABLE(AT91C_ID_HDMA);
    // Enable DMA
    DMA_Enable();

    // Free status
    DMA_DisableIt(0xFFFFFFFF);
    DMA_GetChannelStatus();
    DMA_GetStatus();
    DMA_DisableChannels((1 << DMA_CHANNEL_0) | (1 << DMA_CHANNEL_1));
    // RX channel 0
    DMA_SetConfiguration(DMA_CHANNEL_0,
                          AT91C_HDMA_SRC_PER_2
                        | AT91C_HDMA_DST_PER_2
                        | AT91C_HDMA_SRC_H2SEL_HW
                        | AT91C_HDMA_DST_H2SEL_SW
                        | AT91C_HDMA_SOD_ENABLE
                        | AT91C_HDMA_FIFOCFG_LARGESTBURST
                        );

    // TX channel 1
    DMA_SetConfiguration(DMA_CHANNEL_1,
                          AT91C_HDMA_SRC_PER_1
                        | AT91C_HDMA_DST_PER_1
                        | AT91C_HDMA_SRC_H2SEL_SW
                        | AT91C_HDMA_DST_H2SEL_HW
                        | AT91C_HDMA_SOD_ENABLE
                        | AT91C_HDMA_FIFOCFG_LARGESTBURST
                        );
}

//------------------------------------------------------------------------------
/// Configure the DMA source and destination with Linker List mode.
/// \param pCommand Pointer to command
//------------------------------------------------------------------------------
static void configureLinkList(AT91S_SPI *pSpiHw,
                              SpidCmd *pCommand)
{
    // Setup RX Link List
    dmaRxLinkList[0].sourceAddress = (unsigned int)&pSpiHw->SPI_RDR;
    dmaRxLinkList[0].destAddress   = (unsigned int)pCommand->pCmd;
    dmaRxLinkList[0].controlA      = pCommand->cmdSize
                                   | AT91C_HDMA_SRC_WIDTH_BYTE
                                   | AT91C_HDMA_DST_WIDTH_BYTE
                                   ;
    dmaRxLinkList[0].controlB      = 0
                                   //| AT91C_HDMA_SIF_0
                                   //| AT91C_HDMA_DIF_0
                                   | AT91C_HDMA_SRC_DSCR_FETCH_FROM_MEM
                                   | AT91C_HDMA_DST_DSCR_FETCH_FROM_MEM
                                   | AT91C_HDMA_FC_PER2MEM
                                   | AT91C_HDMA_SRC_ADDRESS_MODE_FIXED
                                   | AT91C_HDMA_DST_ADDRESS_MODE_INCR
                                   ;
    dmaTxLinkList[0].sourceAddress = (unsigned int)pCommand->pCmd;
    dmaTxLinkList[0].destAddress   = (unsigned int)&pSpiHw->SPI_TDR;
    dmaTxLinkList[0].controlA      = pCommand->cmdSize
                                   | AT91C_HDMA_SRC_WIDTH_BYTE
                                   | AT91C_HDMA_DST_WIDTH_BYTE
                                   ;
    dmaTxLinkList[0].controlB      = 0
                                   //| AT91C_HDMA_SIF_0
                                   //| AT91C_HDMA_DIF_0
                                   | AT91C_HDMA_SRC_DSCR_FETCH_FROM_MEM
                                   | AT91C_HDMA_DST_DSCR_FETCH_FROM_MEM
                                   | AT91C_HDMA_FC_MEM2PER
                                   | AT91C_HDMA_SRC_ADDRESS_MODE_INCR
                                   | AT91C_HDMA_DST_ADDRESS_MODE_FIXED
                                   ;
    // Only command
    if (pCommand->pData == 0) {

        dmaRxLinkList[0].descriptor    = 0;
        dmaTxLinkList[0].descriptor    = 0;
    }
    // Command & Data
    else {

        dmaRxLinkList[0].descriptor    = (unsigned int)&dmaRxLinkList[1];
        dmaRxLinkList[1].sourceAddress = (unsigned int)&pSpiHw->SPI_RDR;
        dmaRxLinkList[1].destAddress   = (unsigned int)pCommand->pData;
        dmaRxLinkList[1].controlA      = pCommand->dataSize
                                       | AT91C_HDMA_SRC_WIDTH_BYTE
                                       | AT91C_HDMA_DST_WIDTH_BYTE
                                       ;
        dmaRxLinkList[1].controlB      = 0
                                       //| AT91C_HDMA_SIF_0
                                       //| AT91C_HDMA_DIF_0
                                       | AT91C_HDMA_SRC_DSCR_FETCH_DISABLE
                                       | AT91C_HDMA_DST_DSCR_FETCH_DISABLE
                                       | AT91C_HDMA_FC_PER2MEM
                                       | AT91C_HDMA_SRC_ADDRESS_MODE_FIXED
                                       | AT91C_HDMA_DST_ADDRESS_MODE_INCR
                                       ;
        dmaRxLinkList[1].descriptor    = 0;
        
        dmaTxLinkList[0].descriptor    = (unsigned int)&dmaTxLinkList[1];
        dmaTxLinkList[1].sourceAddress = (unsigned int)pCommand->pData;
        dmaTxLinkList[1].destAddress   = (unsigned int)&pSpiHw->SPI_TDR;
        dmaTxLinkList[1].controlA      = pCommand->dataSize
                                       | AT91C_HDMA_SRC_WIDTH_BYTE
                                       | AT91C_HDMA_DST_WIDTH_BYTE
                                       ;
        dmaTxLinkList[1].controlB      = 0
                                       //| AT91C_HDMA_SIF_0
                                       //| AT91C_HDMA_DIF_0
                                       | AT91C_HDMA_SRC_DSCR_FETCH_DISABLE
                                       | AT91C_HDMA_DST_DSCR_FETCH_DISABLE
                                       | AT91C_HDMA_FC_MEM2PER
                                       | AT91C_HDMA_SRC_ADDRESS_MODE_INCR
                                       | AT91C_HDMA_DST_ADDRESS_MODE_FIXED
                                       ;
        dmaTxLinkList[1].descriptor    = 0;
    }


    // Setup registers
    DMA_SetDescriptorAddr(DMA_CHANNEL_0, (unsigned int)&dmaRxLinkList[0]);
    DMA_SetDescriptorAddr(DMA_CHANNEL_1, (unsigned int)&dmaTxLinkList[0]);
    AT91C_BASE_HDMA->HDMA_CH[DMA_CHANNEL_0].HDMA_CTRLB = 0
                      | AT91C_HDMA_SRC_DSCR_FETCH_FROM_MEM
                      | AT91C_HDMA_DST_DSCR_FETCH_FROM_MEM
                      ;
    AT91C_BASE_HDMA->HDMA_CH[DMA_CHANNEL_1].HDMA_CTRLB = 0
                      | AT91C_HDMA_SRC_DSCR_FETCH_FROM_MEM
                      | AT91C_HDMA_DST_DSCR_FETCH_FROM_MEM
                      ;
}

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Initializes the Spid structure and the corresponding SPI & DMA hardware.
/// The driver will uses DMA channel 0 for RX and DMA channel 1 for TX.
/// The DMA channels are freed automatically when no SPI command processing.
/// \param pSpid  Pointer to a Spid instance.
/// \param pSpiHw  Associated SPI peripheral.
/// \param spiId  SPI peripheral identifier.
/// \return Always 0.
//------------------------------------------------------------------------------
unsigned char SPID_Configure(Spid *pSpid, AT91S_SPI *pSpiHw, unsigned char spiId)
{
    // Initialize the SPI structure
    pSpid->pSpiHw = pSpiHw;
    pSpid->spiId  = spiId;
    pSpid->semaphore = 1;
    pSpid->pCurrentCommand = 0;

    // Enable the SPI Peripheral
    PERIPH_ENABLE(pSpid->spiId);
    
    // Execute a software reset of the SPI twice
    WRITE_SPI(pSpiHw, SPI_CR, AT91C_SPI_SWRST);
    WRITE_SPI(pSpiHw, SPI_CR, AT91C_SPI_SWRST);

    // Configure SPI in Master Mode with No CS selected !!!
    WRITE_SPI(pSpiHw, SPI_MR, AT91C_SPI_MSTR | AT91C_SPI_MODFDIS | AT91C_SPI_PCS);
     
    // Disable the PDC transfer
  #if !defined(at91sam3u)
    WRITE_SPI(pSpiHw, SPI_PTCR, AT91C_PDC_RXTDIS | AT91C_PDC_TXTDIS);
  #endif

    // Disable the SPI TX & RX
    WRITE_SPI(pSpiHw, SPI_CR, AT91C_SPI_SPIDIS);

    // Disable the SPI Peripheral
    PERIPH_DISABLE(pSpid->spiId);

    return 0;
}

//------------------------------------------------------------------------------
/// Configures the parameters for the device corresponding to the cs.
/// \param pSpid  Pointer to a Spid instance.
/// \param cs  number corresponding to the SPI chip select.
/// \param csr  SPI_CSR value to setup.
//------------------------------------------------------------------------------
void SPID_ConfigureCS(Spid *pSpid, unsigned char cs, unsigned int csr)
{
    AT91S_SPI *pSpiHw = pSpid->pSpiHw;

    // Enable the SPI Peripheral
    PERIPH_ENABLE(pSpid->spiId);

    // Write CS
    WRITE_SPI(pSpiHw, SPI_CSR[cs], csr);

    // Disable the SPI Peripheral
    PERIPH_DISABLE(pSpid->spiId);
}
    
//------------------------------------------------------------------------------
/// Starts a SPI master transfer. This is a non blocking function. It will
/// return as soon as the transfer is started.
/// Returns 0 if the transfer has been started successfully; otherwise returns
/// SPID_ERROR_LOCK is the driver is in use, or SPID_ERROR if the command is not
/// valid.
/// \param pSpid  Pointer to a Spid instance.
/// \param pCommand Pointer to the SPI command to execute.
//------------------------------------------------------------------------------
unsigned char SPID_SendCommand(Spid *pSpid, SpidCmd *pCommand)
{
    AT91S_SPI *pSpiHw = pSpid->pSpiHw;
     unsigned int spiMr;
         
     // Try to get the dataflash semaphore
     if (pSpid->semaphore == 0) {
    
         return SPID_ERROR_LOCK;
    }
     pSpid->semaphore--;

    // Enable the SPI Peripheral
    PERIPH_ENABLE(pSpid->spiId);
    
    // Disable PDC transmitter and receiver
  #if !defined(at91sam3u)
    WRITE_SPI(pSpiHw, SPI_PTCR, AT91C_PDC_RXTDIS | AT91C_PDC_TXTDIS);
  #endif

    // Write to the MR register
    spiMr = READ_SPI(pSpiHw, SPI_MR);
    spiMr |= AT91C_SPI_PCS;
    spiMr &= ~((1 << pCommand->spiCs) << 16);
    WRITE_SPI(pSpiHw, SPI_MR, spiMr);

    // Initialize DMA controller using channel 0 for RX, 1 for TX.
    configureDmaChannels();
    configureLinkList(pSpiHw, pCommand);

    // Initialize the callback
    pSpid->pCurrentCommand = pCommand;
    
    // Enable the SPI TX & RX
    WRITE_SPI(pSpiHw, SPI_CR, AT91C_SPI_SPIEN);

    // Start DMA 0(RX) && 1(TX)
    DMA_EnableChannels((1 << DMA_CHANNEL_0) | (1 << DMA_CHANNEL_1));

    // Enable DMA Interrupts
    DMA_EnableIt(  (DMA_CBTC << DMA_CHANNEL_0)
                 | (DMA_CBTC << DMA_CHANNEL_1));

    return 0;    
}

//------------------------------------------------------------------------------
/// SPI DMA transfer ISR, Handle RX complete
//------------------------------------------------------------------------------
void SPID_Handler(Spid *pSpid)
{
    unsigned int dmaStatus;
    SpidCmd *pSpidCmd = pSpid->pCurrentCommand;
    AT91S_SPI *pSpiHw = pSpid->pSpiHw;

    dmaStatus = DMA_GetStatus();

    if ((dmaStatus & AT91C_CBTC) == 0)
        return;

    if ((dmaStatus & (DMA_CBTC << DMA_CHANNEL_0)) == 0)
        return;

    // Disable the SPI TX & RX
    WRITE_SPI(pSpiHw, SPI_CR, AT91C_SPI_SPIDIS);
    // Disable the SPI Peripheral
    PERIPH_DISABLE(pSpid->spiId);

    // Disable DMA
    DMA_Disable();
    // Disable DMA Peripheral
    PERIPH_DISABLE(AT91C_ID_HDMA);
    
    // Release the dataflash semaphore
    pSpid->semaphore++;
        
    // Invoke the callback associated with the current command
    if (pSpidCmd && pSpidCmd->callback) {
    
        pSpidCmd->callback(0, pSpidCmd->pArgument);
    }
        
}

//------------------------------------------------------------------------------
/// Returns 1 if the SPI driver is currently busy executing a command; otherwise
/// returns 0.
/// \param pSpid  Pointer to a SPI driver instance.
//------------------------------------------------------------------------------
unsigned char SPID_IsBusy(const Spid *pSpid)
{
    if (pSpid->semaphore == 0) {

        return 1;
    }
    else {

        return 0;
    }
}

