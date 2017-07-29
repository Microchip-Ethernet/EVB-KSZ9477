/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
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
 
/** \file
 *
 *  Implement for SD/MMC low level commands.
 *
 *  \sa \ref hsmci_module, \ref sdmmc_module
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "libsdmmc.h"

#include <assert.h>

/* ---- Compile options ---- */
//#define DBG_LOG

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/
/** \addtorgoup mcid_defines
 *      @{*/

/** Enable MCI */
#define MCI_ENABLE(pMciHw)     HSMCI_Enable(pMciHw)
/** Disable MCI */
#define MCI_DISABLE(pMciHw)    HSMCI_Disable(pMciHw)
/** Reset MCI */
#define MCI_RESET(pMciHw)      HSMCI_Reset(pMciHw, 0)

/** Return halfword(16-bit) count from byte count */
#define toHWCOUNT(byteCnt) (((byteCnt)&0x1) ? (((byteCnt)/2)+1) : ((byteCnt)/2))
/** Return word(32-bit) count from byte count */
#define toWCOUNT(byteCnt)  (((byteCnt)&0x3) ? (((byteCnt)/4)+1) : ((byteCnt)/4))


/** Bit mask for status register errors. */
#define STATUS_ERRORS ((uint32_t)(HSMCI_SR_UNRE  \
                       | HSMCI_SR_OVRE \
                       | HSMCI_SR_ACKRCVE \
                       /*| HSMCI_SR_BLKOVRE*/ \
                       | HSMCI_SR_CSTOE \
                       | HSMCI_SR_DTOE \
                       | HSMCI_SR_DCRCE \
                       | HSMCI_SR_RTOE \
                       | HSMCI_SR_RENDE \
                       | HSMCI_SR_RCRCE \
                       | HSMCI_SR_RDIRE \
                       | HSMCI_SR_RINDE))

/** Bit mask for response errors */
#define STATUS_ERRORS_RESP ((uint32_t)(HSMCI_SR_CSTOE \
                            | HSMCI_SR_RTOE \
                            | HSMCI_SR_RENDE \
                            | HSMCI_SR_RCRCE \
                            | HSMCI_SR_RDIRE \
                            | HSMCI_SR_RINDE))

/** Bit mask for data errors */
#define STATUS_ERRORS_DATA ((uint32_t)(HSMCI_SR_UNRE \
                            | HSMCI_SR_OVRE \
                            /*| HSMCI_SR_BLKOVRE*/ \
                            /*| HSMCI_SR_CSTOE*/ \
                            | HSMCI_SR_DTOE \
                            | HSMCI_SR_DCRCE))

/** Max DMA size in a single transfer */
#define MAX_DMA_SIZE                (DMAC_MAX_BT_SIZE & 0xFFFFFF00)

/** SD/MMC memory Single block */
#define _CMDR_SDMEM_SINGLE  \
    (HSMCI_CMDR_TRCMD_START_DATA | HSMCI_CMDR_TRTYP_SINGLE)
/** SD/MMC memory Multi block */
#define _CMDR_SDMEM_MULTI   \
    (HSMCI_CMDR_TRCMD_START_DATA | HSMCI_CMDR_TRTYP_MULTIPLE)
/** SDIO byte transfer */
#define _CMDR_SDIO_BYTE     \
    (HSMCI_CMDR_TRCMD_START_DATA | HSMCI_CMDR_TRTYP_BYTE)
/** SDIO block transfer */
#define _CMDR_SDIO_BLOCK    \
    (HSMCI_CMDR_TRCMD_START_DATA | HSMCI_CMDR_TRTYP_BLOCK)

/**     @}*/
/*---------------------------------------------------------------------------
 *         Local types
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *         Local variable
 *----------------------------------------------------------------------------*/

//#define MCID_DBG  0
//static uint8_t bMcidDBG = 0;

/** HAL for SD/MMC bus mode (MCI interface) */
static sSdHalFunctions sdHal = {
    (fSdmmcLock)MCID_Lock,
    (fSdmmcRelease)MCID_Release,
    (fSdmmcSendCommand)MCID_SendCmd,
    (fSdmmcIOCtrl)MCID_IOCtrl
};

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/** \addtogroup mcid_functions
 *@{
 */

/**
 * Enable MCI peripheral access clock
 */
static uint8_t _PeripheralEnable(uint32_t id)
{
    if (PMC_IsPeriphEnabled(id)) return 0;
    PMC_EnablePeripheral(id);
    return 1;
}

/**
 * Disable MCI peripheral access clock
 */
static void _PeripheralDisable(uint32_t id)
{
    PMC_DisablePeripheral(id);
}

/**
 * \brief Start DMA transfer for HSMCI.
 * Replace DMAD driver start function since there is DMADONE handler in HSMCI.
 * \param pDmad     Pointer to DMA driver instance.
 * \param dwCh      ControllerNumber << 8 | ChannelNumber.
 */
static void _MciDMAStart( sDmad *pDmad, uint32_t dwCh)
{
    uint8_t iController  = (dwCh >> 8);
    uint8_t iChannel     = (dwCh) & 0xFF;
    Dmac *pDmac = pDmad->pDmacs[iController];

    DMAC_EnableChannel(pDmac, iChannel);
    if ( pDmad->pollingMode == 0 )
    {
        /* Monitor error status in interrupt handler */
        DMAC_EnableIt(pDmac, (DMAC_EBCIDR_ERR0 << iChannel) );
    }
}

/**
 * HSMCI DMA R/W prepare
 */
static uint32_t _MciDMAPrepare(sMcid *pMcid, uint8_t bRd)
{
    sDmad *pDmad = pMcid->pDmad;
    //sSdmmcCommand *pCmd = pMcid->pCmd;
    uint8_t  iController, iChNb;

    /* Allocate a channel */
    pMcid->dwDmaCh = DMAD_AllocateChannel(pDmad, pMcid->bID, DMAD_TRANSFER_MEMORY);
    if (pMcid->dwDmaCh == DMAD_ALLOC_FAILED)
    {
        return SDMMC_ERROR_BUSY;
    }
    //printf("Dma%c %x\n\r", bRd ? 'R' : 'T', pMcid->dwDmaCh);
    DMAD_SetCallback(pDmad, pMcid->dwDmaCh,
                     (DmadTransferCallback)NULL,
                     NULL);
    iController = pMcid->dwDmaCh >> 8;
    if (bRd)
    {
        iChNb = DMAIF_Get_ChannelNumber(iController, pMcid->bID, DMAD_TRANSFER_RX);
        DMAD_PrepareChannel( pDmad, pMcid->dwDmaCh, DMAC_CFG_SRC_PER(iChNb)
                                                    |DMAC_CFG_SRC_H2SEL
                                                    |DMAC_CFG_SOD
                                                    |DMAC_CFG_FIFOCFG_ALAP_CFG );
    }
    else
    {
        iChNb = DMAIF_Get_ChannelNumber(iController, pMcid->bID, DMAD_TRANSFER_TX);
        DMAD_PrepareChannel( pDmad, pMcid->dwDmaCh, DMAC_CFG_DST_PER(iChNb)
                                                    |DMAC_CFG_DST_H2SEL
                                                    |DMAC_CFG_SOD
                                                    |DMAC_CFG_FIFOCFG_ALAP_CFG );
    }
    return SDMMC_SUCCESS;
}

/**
 * HSMCI DMA R/W
 * \return 1 if DMA started.
 */
static uint32_t _MciDMA(sMcid *pMcid, uint8_t bFByte, uint8_t bRd)
{
    Hsmci *pHw = pMcid->pMciHw;
    sDmad *pDmad = pMcid->pDmad;
    sSdmmcCommand *pCmd = pMcid->pCmd;
    sDmaTransferDescriptor td;
    uint32_t totalSize = pCmd->wNbBlocks * pCmd->wBlockSize;
    uint32_t maxXSize;
    uint32_t memAddress;
    uint8_t  bMByte;

    /* All transfer finished */
    if (pMcid->dwXfrNdx >= totalSize)
    {
        return 0;
    }
    /* Memory address and alignment */
    memAddress = (uint32_t)&pCmd->pData[pMcid->dwXfrNdx];
    bMByte = bFByte ? 1 : (((memAddress & 0x3) || (totalSize & 0x3)));
    /* P to M: Max size is P size */
    if (bRd)
    {
        maxXSize = bFByte ? MAX_DMA_SIZE : (MAX_DMA_SIZE * 4);
    }
    /* M to P: Max size is M size */
    else
    {
        maxXSize = bMByte ? MAX_DMA_SIZE : (MAX_DMA_SIZE * 4);
    }
    /* Update index */
    pMcid->dwXSize = totalSize - pMcid->dwXfrNdx;
    if (pMcid->dwXSize > maxXSize)
    {
        pMcid->dwXSize = maxXSize;
    }
    /* Prepare DMA transfer */
    if (bRd)
    {
        /* RX: bytes or words */
        uint32_t btR = DMAC_CTRLA_BTSIZE(bFByte ? pMcid->dwXSize :
                                                  toWCOUNT(pMcid->dwXSize));
        td.dwSrcAddr = (uint32_t)&(pHw->HSMCI_RDR);
        td.dwDstAddr = memAddress;
        td.dwCtrlA   = btR
                       | (bFByte ? DMAC_CTRLA_SRC_WIDTH_BYTE
                                 : DMAC_CTRLA_SRC_WIDTH_WORD)
                       | (bMByte ? DMAC_CTRLA_DST_WIDTH_BYTE
                                 : DMAC_CTRLA_DST_WIDTH_WORD)
                       ;
        td.dwCtrlB   = DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR
                       | DMAC_CTRLB_FC_PER2MEM_DMA_FC
                       | DMAC_CTRLB_SRC_INCR_FIXED
                       | DMAC_CTRLB_DST_INCR_INCREMENTING
                       | DMAC_CTRLB_IEN
                       | DMAC_CTRLB_SIF_AHB_IF2
                       | DMAC_CTRLB_DIF_AHB_IF0
                       ;
        td.dwDscAddr = 0;
    }
    else
    {

        /* TX: Always words */
        uint32_t btW = DMAC_CTRLA_BTSIZE(toWCOUNT(pMcid->dwXSize));
        td.dwSrcAddr = memAddress;
        td.dwDstAddr = (uint32_t)&(pHw->HSMCI_TDR);
        td.dwCtrlA   = btW
                       | (bMByte ? DMAC_CTRLA_SRC_WIDTH_BYTE
                                 : DMAC_CTRLA_SRC_WIDTH_WORD)
                       | (bFByte ? DMAC_CTRLA_DST_WIDTH_BYTE
                                 : DMAC_CTRLA_DST_WIDTH_WORD)
                       ;
        td.dwCtrlB   = DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR
                       | DMAC_CTRLB_FC_MEM2PER_DMA_FC
                       | DMAC_CTRLB_SRC_INCR_INCREMENTING
                       | DMAC_CTRLB_DST_INCR_FIXED
                       | DMAC_CTRLB_IEN
                       | DMAC_CTRLB_SIF_AHB_IF0
                       | DMAC_CTRLB_DIF_AHB_IF2
                       ;
        td.dwDscAddr = 0;
    }
    DMAD_PrepareSingleTransfer(pDmad, pMcid->dwDmaCh, &td);
    _MciDMAStart(pDmad, pMcid->dwDmaCh);

    return 1;
}

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

/**
 * Reset MCI HW interface and disable it.
 * \param keepSettings Keep old register settings, including
 *                     _MR, _SDCR, _DTOR, _CSTOR, _DMA and _CFG.
 */
static void MCI_Reset(sMcid *pMci, uint8_t keepSettings)
{
    Hsmci *pMciHw = pMci->pMciHw;

    assert(pMci);
    assert(pMci->pMciHw);

    HSMCI_Reset( pMciHw, keepSettings );
}

/**
 * Configure the  MCI CLKDIV in the MCI_MR register. The max. for MCI clock is
 * MCK/2 and corresponds to CLKDIV = 0
 * \param pMci  Pointer to the low level MCI driver.
 * \param mciSpeed  MCI clock speed in Hz, 0 will not change current speed.
 * \param mck       MCK to generate MCI Clock, in Hz
 * \return The actual speed used, 0 for fail.
 */
static uint32_t MCI_SetSpeed( sMcid* pMci, uint32_t mciSpeed, uint32_t mck )
{
    Hsmci *pMciHw = pMci->pMciHw;
    uint32_t clkdiv;

    assert(pMci);
    assert(pMciHw);

    /* Multimedia Card Interface clock (MCCK or MCI_CK) is Master Clock (MCK)
     * divided by (2*(CLKDIV+1))
     * mciSpeed = MCK / (2*(CLKDIV+1)) */
    if (mciSpeed > 0) {
        clkdiv = (mck / 2 / mciSpeed);
        /* Speed should not bigger than expired one */
        if (mciSpeed < mck/2/clkdiv)
        {
            clkdiv ++;
        }
        if ( clkdiv > 0 )
        {
            clkdiv -= 1;
        }
        assert( (clkdiv & 0xFFFFFF00) == 0 ) ; /* "mciSpeed too small" */
    }
    else
    {
        clkdiv = 0 ;
    }
    /* Actual MCI speed */
    mciSpeed = mck / 2 / (clkdiv + 1);

    /* Modify MR */
    HSMCI_DivCtrl( pMciHw, clkdiv, HSMCI_MR_CLKDIV(0x7) );
    return (mciSpeed);
}

/**
 */
static void _FinishCmd( sMcid* pMcid, uint8_t bStatus )
{
    sSdmmcCommand *pCmd = pMcid->pCmd;
    sDmad *pDmad        = pMcid->pDmad;
    //uint32_t memAddress;
    /* Release DMA channel (if used) */
    if (pMcid->dwDmaCh != DMAD_ALLOC_FAILED)
    {
        DMAD_FreeChannel(pDmad, pMcid->dwDmaCh);
        pMcid->dwDmaCh = DMAD_ALLOC_FAILED;
    }
    /* Release command */
    pMcid->pCmd   = NULL;
    pMcid->bState = MCID_LOCKED;
    pCmd->bStatus = bStatus;
    /* Invoke callback */
    if (pCmd->fCallback)
    {
        (pCmd->fCallback)(pCmd->bStatus, pCmd->pArg);
    }
}

/*---------------------------------------------------------------------------
 *      Exported functions
 *---------------------------------------------------------------------------*/

/**
 * Initialize MCI driver.
 */
void MCID_Init(sMcid *pMcid,
               Hsmci *pMci, uint8_t bID, uint32_t dwMck,
               sDmad *pDmad,
               uint8_t bPolling)
{
    uint16_t clkDiv;

    assert(pMcid);
    assert(pMci);

    /* Initialize driver struct */
    pMcid->pMciHw    = pMci;
    pMcid->pCmd      = NULL;

    pMcid->pDmad         = pDmad;
    pMcid->dwDmaCh       = DMAD_ALLOC_FAILED;
    pMcid->dwXfrNdx      = 0;

    pMcid->dwMck     = dwMck;

    pMcid->bID       = bID;
    pMcid->bPolling  = bPolling;
    pMcid->bState    = MCID_IDLE;

    _PeripheralEnable( bID );

    MCI_RESET( pMci );
    MCI_DISABLE ( pMci );
    HSMCI_DisableIt( pMci, 0xFFFFFFFF );

    HSMCI_ConfigureDataTO( pMci, HSMCI_DTOR_DTOCYC(0xFF)
                                |HSMCI_DTOR_DTOMUL_1048576 );
    HSMCI_ConfigureCompletionTO( pMci , HSMCI_CSTOR_CSTOCYC(0xFF)
                                       |HSMCI_CSTOR_CSTOMUL_1048576 );

    /* Set the Mode Register: 400KHz */
    clkDiv = (dwMck / (MCI_INITIAL_SPEED << 1)) - 1;
    HSMCI_ConfigureMode( pMci, (clkDiv | HSMCI_MR_PWSDIV(0x7)) );

    HSMCI_Enable( pMci );
    HSMCI_Configure( pMci, HSMCI_CFG_FIFOMODE | HSMCI_CFG_FERRCTRL );

    /* Enable DMA */
    HSMCI_EnableDma( pMci, 1 );
    
    _PeripheralDisable( bID );
}

/**
 * Lock the MCI driver for slot N access
 */
uint32_t MCID_Lock(sMcid *pMcid, uint8_t bSlot)
{
    Hsmci *pHw = pMcid->pMciHw;
    uint32_t sdcr;

    assert(pMcid);
    assert(pMcid->pMciHw);

    if (bSlot > 0)
    {
        return SDMMC_ERROR_PARAM;
    }
    if (pMcid->bState >= MCID_LOCKED)
    {
        return SDMMC_ERROR_LOCKED;
    }
    pMcid->bState = MCID_LOCKED;
    sdcr = pHw->HSMCI_SDCR & ~(uint32_t)HSMCI_SDCR_SDCSEL_Msk;
    pHw->HSMCI_SDCR = sdcr | (bSlot << HSMCI_SDCR_SDCSEL_Pos);
    return SDMMC_OK;
}

/**
 * Release the driver.
 */
uint32_t MCID_Release(sMcid *pMcid)
{
    assert(pMcid);

    if (pMcid->bState >= MCID_CMD)
    {
        return SDMMC_ERROR_BUSY;
    }
    pMcid->bState = MCID_IDLE;
    return SDMMC_OK;
}

//static uint32_t cmdr;
#ifdef DBG_LOG
#define NUM_LOGS        100
static uint32_t logIndex = 0;
static uint32_t srBLogs[NUM_LOGS];
static uint32_t srELogs[NUM_LOGS];
static uint8_t  rwLogs [NUM_LOGS];
static uint8_t  cmdLogs[NUM_LOGS];
void MCID_DumpLogs(void);
void MCID_DumpLogs(void)
{
    uint32_t i, index;
    printf("Last %d command finishing status:\n\r", NUM_LOGS);
    printf("- Cmd \tSR Start\tSR End\n\r");
    for (i = 0; i < NUM_LOGS; i ++)
    {
        index = (logIndex + i) % NUM_LOGS;
        printf("-%c %2d:\t%08x\t%08x\n\r", rwLogs[index], cmdLogs[index],
            srBLogs[index], srELogs[index]);
    }
}
#endif
/** Possible there will be DAT0 line busy */
static uint8_t bWrBusy = 0;
/**
 * SD/MMC command.
 */
uint32_t MCID_SendCmd(sMcid *pMcid, void *pCommand)
{
    Hsmci *pHw = pMcid->pMciHw;
    sSdmmcCommand *pCmd = pCommand;
    uint32_t mr, ier;
    uint32_t cmdr;

    assert(pMcid);
    assert(pMcid->pMciHw);
    assert(pCmd);

    if (!MCID_IsCmdCompleted(pMcid))
    {
        return SDMMC_ERROR_BUSY;
    }

    pMcid->bState = MCID_CMD;
    pMcid->pCmd   = pCmd;

    _PeripheralEnable(pMcid->bID);

    /* Not busy check for continuous R/W */
  #if 1
    if (bWrBusy && pCmd->cmdOp.bmBits.sendCmd) {
        bWrBusy = 0;
        volatile uint32_t busyWait = 0x0013000;
        while(-- busyWait)
        {
            uint32_t sr = HSMCI_GetStatus(pHw);
            if ((sr & HSMCI_SR_NOTBUSY) && ((sr & HSMCI_SR_DTIP) == 0))
            {
                break;
            }
        }
        //if (busyWait == 0)  printf("-W- SD Busy!\n\r");
    }
  #else
    if (pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_STOPXFR
        || pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_RX
        || pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_TX
        )
    {
        volatile uint32_t busyWait = 0x0015000;
        while(-- busyWait)
        {
            uint32_t sr = HSMCI_GetStatus(pHw);
            if ((sr & HSMCI_SR_NOTBUSY) && ((sr & HSMCI_SR_DTIP) == 0))
            {
                break;
            }
        }
        //if (busyWait == 0)  printf("-W- SD Busy!\n\r");
    }
  #endif
  #ifdef DBG_LOG
    if (pCmd->cmdOp.wVal == SDMMC_CMD_STOPXFR)
        rwLogs[logIndex] = 'S';
    else if (pCmd->cmdOp.wVal == SDMMC_CMD_DATARX)
        rwLogs[logIndex] = 'R';
    else if (pCmd->cmdOp.wVal == SDMMC_CMD_DATATX)
        rwLogs[logIndex] = 'T';
    else
        rwLogs[logIndex] = 'C';
    cmdLogs[logIndex] = pCmd->bCmd;
    srBLogs[logIndex] = HSMCI_GetStatus(pHw);
  #endif

    MCI_DISABLE(pHw);
    mr = HSMCI_GetMode(pHw) & (~(uint32_t)(HSMCI_MR_WRPROOF
                                            |HSMCI_MR_RDPROOF
                                            |HSMCI_MR_FBYTE));

    //printf("* Cmd%2d, op %08x: ", pCmd->bCmd, pCmd->cmdOp.wVal);
    /* Special: PowerON Init */
    if (pCmd->cmdOp.wVal == SDMMC_CMD_POWERONINIT)
    {
        //printf("P ");
        HSMCI_ConfigureMode(pHw, mr);
        ier = HSMCI_IER_XFRDONE;
    }
    /* Normal command: idle the bus */
    else if (pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_STOPXFR)
    {
        //printf("S ");

        HSMCI_ConfigureMode(pHw, mr);
        ier = HSMCI_IER_XFRDONE | STATUS_ERRORS_RESP;
        bWrBusy = 1;
    }
    /* No data transfer */
    else if ((pCmd->cmdOp.wVal & SDMMC_CMD_CNODATA(0xF)) == SDMMC_CMD_CNODATA(0))
    {
        //printf("C ");

        ier = HSMCI_IER_XFRDONE | STATUS_ERRORS_RESP;
        /* R3 response, no CRC */
        if (pCmd->cmdOp.bmBits.respType == 3)
        {
            ier &= ~(uint32_t)HSMCI_IER_RCRCE;
        }
    }
    /* Data command but no following: infinite block xfr */
    else if (pCmd->wNbBlocks == 0)
    {
        //printf("CZ ");

        /* Data length 0, no PDC */
        HSMCI_ConfigureMode(pHw, mr | HSMCI_MR_WRPROOF
                                    | HSMCI_MR_RDPROOF);
        /* Block size 0 */
        HSMCI_ConfigureTransfer(pHw, pCmd->wBlockSize, pCmd->wNbBlocks);
        ier = HSMCI_IER_CMDRDY | STATUS_ERRORS_RESP;
    }
    /* Command? with data */
    else
    {
        //printf("CD %dx%d ", pCmd->wNbBlocks, pCmd->wBlockSize);

        /* Setup block size */
        if (pCmd->cmdOp.bmBits.sendCmd)
        {
            HSMCI_ConfigureTransfer(pHw, pCmd->wBlockSize, pCmd->wNbBlocks);
        }

        /* Block size is 0, force byte */
        if (pCmd->wBlockSize == 0)
            pCmd->wBlockSize = 1;

        /* Force byte transfer */
        if (pCmd->wBlockSize & 0x3)
        {
            mr |= HSMCI_MR_FBYTE;
        }

        /* Set block size & MR */
        HSMCI_ConfigureMode(pHw, mr | HSMCI_MR_WRPROOF
                                    | HSMCI_MR_RDPROOF
                                    | (pCmd->wBlockSize << 16));
        /* Reset transferred number of blocks */
        pMcid->dwXfrNdx = 0;
        /* DMA write */
        if (pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_TX)
        {
            if (_MciDMAPrepare(pMcid, 0))
            {
                _FinishCmd(pMcid, SDMMC_ERROR_BUSY);
                return SDMMC_ERROR_BUSY;
            }
            _MciDMA(pMcid, (mr & HSMCI_MR_FBYTE) > 0, 0);
            //ier = (HSMCI_IER_DMADONE | STATUS_ERRORS_DATA) & ~(HSMCI_SR_DCRCE);
            bWrBusy = 1;
        }
        else
        {
            if (_MciDMAPrepare(pMcid, 1))
            {
                _FinishCmd(pMcid, SDMMC_ERROR_BUSY);
                return SDMMC_ERROR_BUSY;
            }
            _MciDMA(pMcid, (mr & HSMCI_MR_FBYTE) > 0, 1);
            //ier = HSMCI_IER_DMADONE | STATUS_ERRORS_DATA;
        }
        ier = HSMCI_IER_DMADONE | STATUS_ERRORS_DATA;
    }

    MCI_ENABLE(pHw);
    if (pCmd->cmdOp.wVal & (SDMMC_CMD_bmPOWERON | SDMMC_CMD_bmCOMMAND))
    {
        //uint32_t cmdr;
        cmdr = pCmd->bCmd;

        if (pCmd->cmdOp.bmBits.powerON)
        {
            cmdr |= (HSMCI_CMDR_OPDCMD | HSMCI_CMDR_SPCMD_INIT);
        }
        if (pCmd->cmdOp.bmBits.odON)
        {
            cmdr |= HSMCI_CMDR_OPDCMD;
        }
        if (pCmd->cmdOp.bmBits.sendCmd)
        {
            cmdr |= HSMCI_CMDR_MAXLAT;
        }
        switch(pCmd->cmdOp.bmBits.xfrData)
        {
            case SDMMC_CMD_TX:
                if (pCmd->cmdOp.bmBits.ioCmd)
                {
                    cmdr |= (pCmd->wBlockSize == 1) ?
                            _CMDR_SDIO_BYTE :
                            _CMDR_SDIO_BLOCK;
                }
                else
                {
                    cmdr |= (pCmd->wNbBlocks == 1) ?
                            _CMDR_SDMEM_SINGLE :
                            _CMDR_SDMEM_MULTI;
                }
                break;

            case SDMMC_CMD_RX:
                if (pCmd->cmdOp.bmBits.ioCmd)
                {
                    cmdr |= HSMCI_CMDR_TRDIR_READ
                            |((pCmd->wBlockSize == 1) ?
                               _CMDR_SDIO_BYTE :
                               _CMDR_SDIO_BLOCK)
                            ;
                }
                else
                {
                    cmdr |= HSMCI_CMDR_TRDIR_READ
                            |((pCmd->wNbBlocks == 1) ?
                               _CMDR_SDMEM_SINGLE :
                               _CMDR_SDMEM_MULTI)
                            ;
                }
                break;

            case SDMMC_CMD_STOPXFR:
                cmdr |= HSMCI_CMDR_TRCMD_STOP_DATA;
                break;
        }
        switch(pCmd->cmdOp.bmBits.respType)
        {
            case 3: case 4:
                /* ignore CRC error */
                ier &= ~(uint32_t)HSMCI_IER_RCRCE;
            case 1: case 5: case 6: case 7:
                cmdr |= HSMCI_CMDR_RSPTYP_48_BIT;
                break;
            case 2:
                cmdr |= HSMCI_CMDR_RSPTYP_136_BIT;
                break;
            /* No response, ignore RTOE */
            default:
                ier &= ~(uint32_t)HSMCI_IER_RTOE;
        }

        pHw->HSMCI_ARGR = pCmd->dwArg;
        //printf("_CMDR 0x%08X ", cmdr);
        #if 0
        if (pCmd->bCmd == 53 && pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_TX)
        {
        printf("\n\rCmd%d:\n\r", pCmd->bCmd);
        printf(" _MR %08x, _ARGR %08x, _CMDR %08x\n\r",
            pHw->HSMCI_MR, pHw->HSMCI_ARGR, cmdr);
        printf(" _BLKR %08x, _SR %08x, _IMR %08x\n\r",
            pHw->HSMCI_BLKR, pHw->HSMCI_SR, ier);
        printf(" _DMA %08x, _CFG %08x\n\r",
            pHw->HSMCI_DMA, pHw->HSMCI_CFG);
        }
        #endif
        pHw->HSMCI_CMDR = cmdr;
    }
    
    //printf("\n\r");
    #if 0
    /* Start sending DMA */
    if (   pCmd->wNbBlocks
        && pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_TX )
    {
        _MciDMA(pMcid, (mr & HSMCI_MR_FBYTE) > 0, 0);
    }
    #endif
    /* Ignore CRC error for R3 & R4 */
    /* Ignore data error on stop command */
    if (pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_STOPXFR)
    {
        ier &= ~STATUS_ERRORS_DATA;
    }

    /* Enable status flags */
    HSMCI_EnableIt(pHw, ier);

    return SDMMC_OK;
}

/**
 * Process pending events on the given MCI driver.
 */
void MCID_Handler(sMcid *pMcid)
{
    Hsmci *pHw = pMcid->pMciHw;
    sSdmmcCommand *pCmd = pMcid->pCmd;
    uint32_t dwSr, dwMsk, dwMaskedSr, memAddress;
    
    assert(pMcid);
    assert(pMcid->pMciHw);

    /* Do nothing if no pending command */
    if (pCmd == NULL)
    {
        if (pMcid->bState >= MCID_CMD)
        {
            pMcid->bState = MCID_LOCKED;
        }
        return;
    }

    /* Read status */
    dwSr  = HSMCI_GetStatus(pHw);
    dwMsk = HSMCI_GetItMask(pHw);
    dwMaskedSr = dwSr & dwMsk;

  #if 0
    if ( MCID_DBG &&
            (0
            //|| pCmd->bCmd == 25
            //|| pCmd->bCmd == 24
            //|| pCmd->bCmd == 17
            //|| pCmd->bCmd == 18
            || 1
            //|| pCmd->bCmd == 0
            //|| pCmd->bCmd == 13
            )
        )
    {
        //printf("%2d: s%08x m%08x -> %08x\n\r", pCmd->bCmd, dwSr, dwMsk, dwMaskedSr);
        printf("i%x\n\r", dwMaskedSr);
    }
  #endif

    /* Check errors */
    if (dwMaskedSr & STATUS_ERRORS)
    {
        if (dwMaskedSr & HSMCI_SR_RTOE)
        {
            pCmd->bStatus = SDMMC_ERROR_NORESPONSE;
        }
        else
        {
            TRACE_INFO("iErr %x: C%d, R%d\n\r",
                dwSr, pCmd->bCmd, pCmd->cmdOp.bmBits.respType);
            pCmd->bStatus = SDMMC_ERROR;
        }
        pMcid->bState = MCID_ERROR;
    }
    dwMsk &= ~STATUS_ERRORS;

    /* Check command complete */
    if (dwMaskedSr & HSMCI_SR_CMDRDY)
    {
        HSMCI_DisableIt(pHw, HSMCI_IDR_CMDRDY);
        dwMsk &= ~(uint32_t)HSMCI_IMR_CMDRDY;
    }
    /* Check transfer done */
    if (dwMaskedSr & HSMCI_SR_XFRDONE)
    {
        dwMsk &= ~(uint32_t)HSMCI_IMR_XFRDONE;
    }
    /* Check if not busy */
    if (dwMaskedSr & HSMCI_SR_NOTBUSY)
    {
        dwMsk &= ~(uint32_t)HSMCI_IMR_NOTBUSY;
    }
    /* Check if TX ready */
    if (dwMaskedSr & HSMCI_SR_TXRDY)
    {
        dwMsk &= ~(uint32_t)HSMCI_IMR_TXRDY;
    }
    /* Check if DMA finished */
    if (dwMaskedSr & HSMCI_SR_DMADONE)
    {
        uint8_t bGoon, bFByte = HSMCI_IsFByteEnabled(pHw);

        //printf(pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_TX ? "t" : "r");
        memAddress = (uint32_t)&pCmd->pData[pMcid->dwXfrNdx];
        /* Increase data index */
        pMcid->dwXfrNdx += pMcid->dwXSize;
        /* Next transfer */
        bGoon = _MciDMA(pMcid,
                        bFByte,
                        (pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_RX));
        if (bGoon)
        {
            /* Go on: Waiting DMADONE */
            //if (MCID_DBG) printf("+");
        }
        else
        {
            /* Disable DMA done */
            HSMCI_DisableIt(pHw, HSMCI_IDR_DMADONE);
            /* For TX, check FIFOEMPTY - BLKE - TXRDY */
            if (pCmd->cmdOp.bmBits.xfrData == SDMMC_CMD_TX)
            {
                HSMCI_EnableIt(pHw, HSMCI_IER_FIFOEMPTY);
            }
            else
            {
                dwMsk &= ~(uint32_t)HSMCI_IMR_DMADONE;
            }
        }
    }
    /* Check if FIFO empty (all data sent) */
    if (dwMaskedSr & HSMCI_SR_FIFOEMPTY)
    {
        /* Disable FIFO empty */
        HSMCI_DisableIt(pHw, HSMCI_IDR_FIFOEMPTY);
        /* Byte transfer no BLKE check */
        if (HSMCI_IsFByteEnabled(pHw))
        {
            dwMsk &= ~(uint32_t)HSMCI_IMR_FIFOEMPTY;
        }
        /* Continuous R/W */
        else if (pCmd->bCmd == 0)
        {
            /* Check _NOTBUSY */
            //if (dwSr & HSMCI_SR_NOTBUSY)
            {
                dwMsk &= ~(uint32_t)HSMCI_IMR_FIFOEMPTY;
            }
            //else
            //{
            //    HSMCI_EnableIt(pHw, HSMCI_IER_NOTBUSY);
            //}
        }
        /* Single block R/W */
        else
        {
            /* Check _NOTBUSY */
            if (dwSr & HSMCI_SR_NOTBUSY)
            {
                dwMsk &= ~(uint32_t)HSMCI_IMR_FIFOEMPTY;
            }
            else
            {
                HSMCI_EnableIt(pHw, HSMCI_IER_NOTBUSY);
            }
        }
    }
    /* All none error mask done, complete the command */
    if (0 == dwMsk || pMcid->bState == MCID_ERROR)
    {
        #if 0
        if (pCmd->bCmd == 12)
        printf("%2d: %x\n\r", pCmd->bCmd, dwSr);
        #endif

        /* Error reset */
        if (pMcid->bState == MCID_ERROR)
        {
            MCI_Reset(pMcid, 1);
        }
        else 
        {
            pCmd->bStatus = SDMMC_SUCCESS;

            if (pCmd->pResp)
            {
                uint8_t bRspSize, i;
                switch(pCmd->cmdOp.bmBits.respType)
                {
                    case 1: case 3: case 4: case 5: case 6: case 7:
                        bRspSize = 1;
                        break;

                    case 2:
                        bRspSize = 4;
                        break;

                    default:
                        bRspSize = 0;
                }
                for (i = 0; i < bRspSize; i ++)
                {
                    pCmd->pResp[i] = HSMCI_GetResponse(pHw);
                }
            }
        }
        /* Disable interrupts */
        HSMCI_DisableIt(pHw, HSMCI_GetItMask(pHw));
        /* Disable peripheral */
        _PeripheralDisable(pMcid->bID);
      #ifdef DBG_LOG
        /* Log debug data */
        srELogs[logIndex]  = dwSr;
        logIndex = (logIndex + 1) % NUM_LOGS;
      #endif
        /* Command is finished */
        _FinishCmd(pMcid, pCmd->bStatus);
    }
}

/**
 * Cancel pending SD/MMC command.
 */
uint32_t MCID_CancelCmd(sMcid *pMcid)
{
    if (pMcid->bState == MCID_IDLE)
    {
        return SDMMC_ERROR_STATE;
    }
    if (pMcid->bState == MCID_CMD)
    {
        /* Cancel ... */
        MCI_Reset(pMcid, 1);
        /* Command is finished */
        _FinishCmd(pMcid, SDMMC_ERROR_USER_CANCEL);
    }
    return SDMMC_OK;
}

/**
 * Reset MCID and disable HW
 */
void MCID_Reset(sMcid * pMcid)
{
    Hsmci *pHw = pMcid->pMciHw;

    MCID_CancelCmd(pMcid);

    _PeripheralEnable(pMcid->bID);

    /* Disable */
    MCI_DISABLE(pHw);
    /* MR reset */
    HSMCI_ConfigureMode(pHw, HSMCI_GetMode(pHw) & (HSMCI_MR_CLKDIV_Msk
                                                 | HSMCI_MR_PWSDIV_Msk));
    /* BLKR reset */
    HSMCI_ConfigureTransfer(pHw, 0, 0);
    
    /* Cancel ... */
    MCI_Reset(pMcid, 1);
    _PeripheralDisable(pMcid->bID);

    if (pMcid->bState == MCID_CMD)
    {
        /* Command is finished */
        _FinishCmd(pMcid, SDMMC_ERROR_USER_CANCEL);
    }
}

/**
 * Check if the command is finished
 */
uint32_t MCID_IsCmdCompleted(sMcid *pMcid)
{
    sSdmmcCommand *pCmd = pMcid->pCmd;

    if (pMcid->bPolling)
    {
        MCID_Handler(pMcid);
    }
    if (pMcid->bState == MCID_CMD)
    {
        return 0;
    }
    if (pCmd)
    {
        return 0;
    }
    return 1;
}

/**
 * IO control functions
 */
uint32_t MCID_IOCtrl(sMcid *pMcid, uint32_t bCtl, uint32_t param)
{
    Hsmci *pMciHw = pMcid->pMciHw;
    uint8_t mciDis;

    assert(pMcid);
    assert(pMcid->pMciHw);

    mciDis = _PeripheralEnable(pMcid->bID);

    switch (bCtl)
    {
        case SDMMC_IOCTL_BUSY_CHECK:
            *(uint32_t*)param = !MCID_IsCmdCompleted(pMcid);
            break;

        case SDMMC_IOCTL_POWER:
            return SDMMC_ERROR_NOT_SUPPORT;

        case SDMMC_IOCTL_RESET:
            MCID_Reset(pMcid);
            return SDMMC_SUCCESS;

        case SDMMC_IOCTL_CANCEL_CMD:
            return MCID_CancelCmd(pMcid);

        case SDMMC_IOCTL_SET_CLOCK:
            *(uint32_t*)param = MCI_SetSpeed(pMcid,
                                             *(uint32_t*)param,
                                             pMcid->dwMck);
            break;

        case SDMMC_IOCTL_SET_HSMODE:
            HSMCI_HsEnable( pMciHw, *(uint32_t*)param );
            *(uint32_t*)param = HSMCI_IsHsEnabled( pMciHw );
            break;

        case SDMMC_IOCTL_SET_BUSMODE:
            if (*(uint32_t*)param > 4)
            {
                *(uint32_t*)param = 4;
            }
            HSMCI_SetBusWidth( pMciHw, *(uint32_t*)param );
            break;

        case SDMMC_IOCTL_GET_BUSMODE:
            *(uint32_t*)param = 4; /* Max 4-bit bus */
            break;

        case SDMMC_IOCTL_GET_HSMODE:
            *(uint32_t*)param = 1; /* Supported */
            break;

        default:
            return SDMMC_ERROR_NOT_SUPPORT;
        
    }

    if (mciDis)
    {
        _PeripheralDisable(pMcid->bID);
    }
    return SDMMC_OK;
}

/**
 * Initialize the SD/MMC card driver struct for SD/MMC bus mode
 * \note defined in SD/MMC bus mode low level (Here uses MCI interface)
 */
void SDD_InitializeSdmmcMode(sSdCard * pSd,void * pDrv,uint8_t bSlot)
{
    SDD_Initialize(pSd, pDrv, bSlot, &sdHal);
}

/**@}*/

