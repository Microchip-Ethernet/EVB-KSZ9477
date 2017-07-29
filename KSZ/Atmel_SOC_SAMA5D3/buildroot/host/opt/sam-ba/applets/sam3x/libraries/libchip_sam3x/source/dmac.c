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
 * \file
 *
 * Implementation of DMA controller (DMAC).
 *
 */
 
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include <stdint.h>
#include <assert.h>
/** \addtogroup dmac_functions DMAC Functions
 *@{
 */

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures an DMAC peripheral with modified round robin arbiter.
 *
 * \param pDmac  Pointer to the DMAC peripheral.
 */
extern void DMAC_Modified_Arbiter( Dmac* pDmac )
{
    assert(pDmac);
    pDmac->DMAC_GCFG = DMAC_GCFG_ARB_CFG ;
}

/**
 * \brief Enables a DMAC peripheral.
 *
 * \param pDmac  Pointer to the DMAC peripheral.
 */
extern void DMAC_Enable( Dmac* pDmac )
{
    assert(pDmac);
    pDmac->DMAC_EN = DMAC_EN_ENABLE;
}

/**
 * \brief Disables a DMAC peripheral.
 *
 * \param pDmac Pointer to the DMAC peripheral .
 */
extern void DMAC_Disable( Dmac* pDmac )
{
    assert(pDmac);
    pDmac->DMAC_EN = ~(uint32_t)DMAC_EN_ENABLE;
}

/**
 * \brief Enables DMAC interrupt.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param dwInteruptMask IT to be enabled.
 */
extern void DMAC_EnableIt (Dmac* pDmac, uint32_t dwInteruptMask )
{
    assert(pDmac);
    pDmac->DMAC_EBCIER = dwInteruptMask;
}

/**
 * \brief Disables DMAC interrupt
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param dwInteruptMask IT to be enabled
 */
extern void DMAC_DisableIt (Dmac* pDmac, uint32_t dwInteruptMask )
{
    assert(pDmac);
    pDmac->DMAC_EBCIDR = dwInteruptMask;
}

/**
 * \brief Get DMAC Interrupt Mask Status.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \return DMAC Error, buffer transfer and chained buffer
 *  transfer interrupt mask register value.
 */
extern uint32_t DMAC_GetInterruptMask( Dmac* pDmac )
{
    assert(pDmac);
    return (pDmac->DMAC_EBCIMR);
}

/**
 * \brief Get DMAC Error, buffer transfer and chained buffer
 *  transfer status register.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \return DMAC Error, buffer transfer and chained buffer
 *  transfer status register.
 */
extern uint32_t DMAC_GetStatus( Dmac* pDmac )
{
    assert(pDmac);
    return (pDmac->DMAC_EBCISR);
}

/**
 * \brief Get DMAC Error, buffer transfer and chained buffer
 *  transfer status register of the given DMAC peripheral, but
 *  masking interrupt sources which are not currently enabled.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \return DMAC Error, buffer transfer and chained buffer
 *  transfer status register.
 */
extern uint32_t DMAC_GetMaskedStatus( Dmac* pDmac )
{
    uint32_t dwStatus;
    assert(pDmac);
    dwStatus = pDmac->DMAC_EBCISR;
    dwStatus &= pDmac->DMAC_EBCIMR;
    return dwStatus;
}

/**
 * \brief enables the relevant channel of given DMAC.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 */
extern void DMAC_EnableChannel( Dmac* pDmac, uint8_t ucChannel )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CHER |= DMAC_CHER_ENA0 << ucChannel;
}

/**
 * \brief enables the relevant channels of given DMAC.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Channels bitmap.
 */
extern void DMAC_EnableChannels( Dmac* pDmac, uint8_t ucChannel )
{
    assert(pDmac);
    pDmac->DMAC_CHER = ucChannel;
}

/**
 * \brief Disables the relevant channel of given DMAC.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 */
extern void DMAC_DisableChannel( Dmac* pDmac, uint8_t ucChannel )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CHDR |= DMAC_CHDR_DIS0 << ucChannel;
}

/**
 * \brief Disables the relevant channels of given DMAC.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Channels bitmap.
 */
extern void DMAC_DisableChannels( Dmac* pDmac, uint8_t ucChannel )
{
    assert(pDmac);
    pDmac->DMAC_CHDR = ucChannel;
}

/**
 * \brief freezes the relevant channel of given DMAC.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 */
extern void DMAC_SuspendChannel( Dmac* pDmac, uint8_t ucChannel )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CHER |= DMAC_CHER_SUSP0 << ucChannel;
}

/**
 * \brief resumes the current channel from an automatic
 * stall state of given DMAC.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 */
extern void DMAC_KeepChannel( Dmac* pDmac, uint8_t ucChannel )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CHER |= DMAC_CHER_KEEP0 << ucChannel;
}

/**
 * \brief resume the channel transfer restoring its context.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 */
extern void DMAC_RestoreChannel( Dmac* pDmac, uint8_t ucChannel )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CHDR |= DMAC_CHDR_RES0 << ucChannel;
}

/**
 * \brief Get DMAC channel handler Status.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \return DMAC channel handler status register.
 */
extern uint32_t DMAC_GetChannelStatus( Dmac* pDmac )
{
    assert(pDmac);
    return (pDmac->DMAC_CHSR);
}

/**
 * \brief Set DMAC source address in a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param dwSaddr sources address.
 * \note This register must be aligned with the source transfer width.
 */
extern void DMAC_SetSourceAddr( Dmac* pDmac,
                         uint8_t ucChannel,
                         uint32_t dwSaddr )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_SADDR = dwSaddr;
}

/**
 * \brief Return DMAC source address of a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 */
extern uint32_t DMAC_GetSourceAddr( Dmac* pDmac,
                             uint8_t ucChannel )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    return pDmac->DMAC_CH_NUM[ucChannel].DMAC_SADDR;
}

/**
 * \brief Set DMAC destination address in a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param dwDaddr sources address.
 * \note This register must be aligned with the source transfer width.
 */
extern void DMAC_SetDestinationAddr( Dmac* pDmac,
                              uint8_t ucChannel,
                              uint32_t dwDaddr )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_DADDR = dwDaddr;
}

/**
 * \brief Return DMAC destination address of a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 */
extern uint32_t DMAC_GetDestinationAddr( Dmac* pDmac,
                                  uint8_t ucChannel )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    return pDmac->DMAC_CH_NUM[ucChannel].DMAC_DADDR;
}

/**
 * \brief Set DMAC descriptor address used by a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param dwDescr Buffer Transfer descriptor address
 * \param ucDescrif AHB-Lite interface to be fetched
 */
extern void DMAC_SetDescriptorAddr( Dmac* pDmac,
                             uint8_t ucChannel,
                             uint32_t dwDescr,
                             uint8_t ucDescrif )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    assert(ucDescrif < 2);
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_DSCR = ( dwDescr & 0xFFFFFFFC ) | ucDescrif;
}

/**
 * \brief Set DMAC controlA used by a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param dwControlA Configuration for controlA register.
 */
extern void DMAC_SetControlA( Dmac* pDmac,
                       uint8_t ucChannel,
                       uint32_t dwControlA )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLA = dwControlA;
}


/**
 * \brief Set DMAC buffer transfer size used by a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param uwBuffsize number of transfers to be performed.
 */
extern void DMAC_SetBufferSize( Dmac* pDmac,
                         uint8_t ucChannel,
                         uint16_t uwBuffsize)
{
   assert(pDmac);
   assert(ucChannel < DMAC_CHANNEL_NUM);
   pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLA &= ~DMAC_CTRLA_BTSIZE_Msk;
   pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLA |= DMAC_CTRLA_BTSIZE( uwBuffsize );
}

/**
 * \brief Set DMAC single transfer size used by a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param ucSrcWidth source width for single transfer.
 * \param ucDstWidth destination width for single transfer.
 */
extern void DMAC_SetSingleTransferSize ( Dmac* pDmac,
                                  uint8_t ucChannel,
                                  uint8_t ucSrcWidth,
                                  uint8_t ucDstWidth )
{
   assert(pDmac);
   assert(ucChannel < DMAC_CHANNEL_NUM);
   pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLA &= ~DMAC_CTRLA_SRC_WIDTH_Msk;
   pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLA &= ~DMAC_CTRLA_DST_WIDTH_Msk;
   pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLA |= ucSrcWidth | ucDstWidth;
}

/**
 * \brief Set DMAC single transfer size used by a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param ucScSize Size of source chunk transfer.
 * \param ucDcSize Size of destination chunk transfer.
 */
extern void DMAC_SetChunkTransferSize ( Dmac* pDmac,
                                 uint8_t ucChannel,
                                 uint8_t ucScSize,
                                 uint8_t ucDcSize)
{
   assert(pDmac);
   assert(ucChannel < DMAC_CHANNEL_NUM);
   pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLA &= ~DMAC_CTRLA_SCSIZE_Msk;
   pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLA &= ~DMAC_CTRLA_DCSIZE_Msk;
   pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLA |= ucScSize | ucDcSize;
}

/**
 * \brief Set DMAC controlB used by a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param dwControlB Configuration for controlB register.
 */
extern void DMAC_SetControlB( Dmac* pDmac,
                       uint8_t ucChannel,
                       uint32_t dwControlB )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLB = dwControlB;
}

/**
 * \brief Set DMAC buffer descriptor fetch mode.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param ucSrcDscr Source buffer descriptor fetch mode.
 * \param ucDstDscr destination buffer descriptor fetch mode.
 */
extern void DMAC_SetDescFetchMode( Dmac* pDmac,
                            uint8_t ucChannel,
                            uint8_t ucSrcDscr,
                            uint8_t ucDstDscr )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM );
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLB &= ~DMAC_CTRLB_SRC_DSCR;
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLB &= ~DMAC_CTRLB_DST_DSCR;
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLB |= ucSrcDscr | ucDstDscr;
}

/**
 * \brief Set DMAC control B register Flow control bit field.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param ucFlowControl Flow which device controls the size of the buffer transfer.
 */
extern void DMAC_SetFlowControl( Dmac* pDmac,
                          uint8_t ucChannel,
                          uint8_t ucFlowControl )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLB &= ~DMAC_CTRLB_FC_Msk;
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CTRLB |= ucFlowControl;
}

/**
 * \brief Set DMAC CFG register used by a DMAC channel.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param ucChannel Particular channel number.
 * \param dwConfiguration Configuration for CFG register.
 */
extern void DMAC_SetCFG( Dmac* pDmac,
                  uint8_t ucChannel,
                  uint32_t dwConfiguration )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM);
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CFG = dwConfiguration;
}

/**
 * \brief Set DMAC SW/HW handshaking interface used to 
 *        trigger a transfer request.
 *
 * \param pDmac Pointer to the DMAC peripheral.
 * \param channel Particular channel number.
 * \param srcH2sel Source handshaking interface. 
 * \param dstH2sel Destination handshaking interface.
 */
extern void DMAC_SethandshakeInterface( Dmac* pDmac,
                                 uint8_t ucChannel,
                                 uint8_t ucSrcH2sel,
                                 uint8_t ucDstH2sel )
{
    assert(pDmac);
    assert(ucChannel < DMAC_CHANNEL_NUM );
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CFG &= ~DMAC_CFG_SRC_H2SEL;
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CFG &= ~DMAC_CFG_DST_H2SEL;
    pDmac->DMAC_CH_NUM[ucChannel].DMAC_CFG |= ucSrcH2sel | ucDstH2sel;
}
/**@}*/

