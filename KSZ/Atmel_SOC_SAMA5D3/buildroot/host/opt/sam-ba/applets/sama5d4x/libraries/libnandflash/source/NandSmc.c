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

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include <board.h>
#include <chip.h>
#include <libnandflash.h>
/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/** Nand flash chip status codes */
#define STATUS_READY                    (1 << 6)
#define STATUS_ERROR                    (1 << 0)

/** Nand flash commands */
#define COMMAND_READ_1                  0x00
#define COMMAND_READ_2                  0x30
#define COMMAND_COPYBACK_READ_1         0x00
#define COMMAND_COPYBACK_READ_2         0x35
#define COMMAND_COPYBACK_PROGRAM_1      0x85
#define COMMAND_COPYBACK_PROGRAM_2      0x10
#define COMMAND_RANDOM_OUT              0x05
#define COMMAND_RANDOM_OUT_2            0xE0
#define COMMAND_RANDOM_IN               0x85
#define COMMAND_READID                  0x90
#define COMMAND_WRITE_1                 0x80
#define COMMAND_WRITE_2                 0x10
#define COMMAND_ERASE_1                 0x60
#define COMMAND_ERASE_2                 0xD0
#define COMMAND_STATUS                  0x70
#define COMMAND_RESET                   0xFF


/** Nand flash commands (small blocks) */
#define COMMAND_READ_A                  0x00
#define COMMAND_READ_C                  0x50

//#define ENABLE_CE(raw)        PIO_Clear(&(raw->pinChipEnable))
//#define DISABLE_CE(raw)       PIO_Set(&(raw->pinChipEnable))

#define ENABLE_CE(raw)
#define DISABLE_CE(raw)

#define WRITE_COMMAND(raw, command) \
    {*((volatile uint8_t *) raw->commandAddress) = (uint8_t) command;}
#define WRITE_COMMAND16(raw, command) \
    {*((volatile uint16_t *) raw->commandAddress) = (uint16_t) command;}
#define WRITE_ADDRESS(raw, address) \
    {*((volatile uint8_t *) raw->addressAddress) = (uint8_t) address;}
#define WRITE_ADDRESS16(raw, address) \
    {*((volatile uint16_t *) raw->addressAddress) = (uint16_t) address;}
#define WRITE_DATA8(raw, data) \
    {*((volatile uint8_t *) raw->dataAddress) = (uint8_t) data;}
#define READ_DATA8(raw) \
    (*((volatile uint8_t *) raw->dataAddress))
#define WRITE_DATA16(raw, data) \
    {*((volatile uint16_t *) raw->dataAddress) = (uint16_t) data;}
#define READ_DATA16(raw) \
    (*((volatile uint16_t *) raw->dataAddress))

/** Internal cast macros */
#define MODEL(raw)  ((struct NandFlashModel *) raw)

static SmcOperation SmcOpConfiguration;

 /**
 * \brief Sends the column address to the NandFlash chip.
 *
 * \param raw  Pointer to a RawNandFlash instance.
 * \param columnAddress  Column address to send.
 */
static void WriteColumnAddress(
    const struct RawNandFlash *raw,
    uint16_t columnAddress)
{
    uint16_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));

    /* Check the data bus width of the NandFlash */
    if (NandFlashModel_GetDataBusWidth(MODEL(raw)) == 16) {
        /* Div 2 is because we address in word and not in byte */
        columnAddress >>= 1;
    }
    /* Send single column address byte for small block devices, or two column address bytes for large block devices*/
    while (pageDataSize > 2) {

        if (NandFlashModel_GetDataBusWidth(MODEL(raw)) == 16) {
            WRITE_ADDRESS16(raw, columnAddress & 0xFF);
        }
        else {
            WRITE_ADDRESS(raw, columnAddress & 0xFF);
        }
        pageDataSize >>= 8;
        columnAddress >>= 8;
    }
}

/**
 * \brief Sends the row address to the NandFlash chip.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param rowAddress  Row address to send.
 */
static void WriteRowAddress(
    const struct RawNandFlash *raw,
    uint32_t rowAddress)
{
    uint32_t numPages = NandFlashModel_GetDeviceSizeInPages(MODEL(raw));

    while (numPages > 0) {

        if (NandFlashModel_GetDataBusWidth(MODEL(raw)) == 16) {
            WRITE_ADDRESS16(raw, rowAddress & 0xFF);
        }
        else {
            WRITE_ADDRESS(raw, rowAddress & 0xFF);
        }
        numPages >>= 8;
        rowAddress >>= 8;
    }
}

static uint32_t NFC_GetCmd_Acycle(uint32_t numCycle)
{
    switch(numCycle) {
        case 1: return NFCADDR_CMD_ACYCLE_ONE;
        case 2: return NFCADDR_CMD_ACYCLE_TWO;
        case 3: return NFCADDR_CMD_ACYCLE_THREE;
        case 4: return NFCADDR_CMD_ACYCLE_FOUR;
        case 5: return NFCADDR_CMD_ACYCLE_FIVE;
    }
    return 0;
}

/**
 * \brief Translates the given column and row address into first and other (1-4) address
 *  cycles. The resulting values are stored in the provided variables if they are not null.
 * \param columnAddress  Column address to translate.
 * \param rowAddress  Row address to translate.
 * \param pAddressCycle0    First address cycle.
 * \param pAddressCycle1234 Four address cycles.
 * \param rowOnly           Only ROW address is used.
 * \return Number of address cycles converted.
 */
static uint32_t NFC_TranslateAddress(
    const struct RawNandFlash *raw,
    uint16_t columnAddress,
    uint32_t rowAddress,
    uint32_t *pAddressCycle0,
    uint32_t *pAddressCycle1234,
    uint8_t   rowOnly)
{
    uint16_t maxDataSize = NandFlashModel_GetPageDataSize(MODEL(raw))
                         + NandFlashModel_GetPageSpareSize(MODEL(raw))
                         - 1;
    uint32_t maxPageNum  = NandFlashModel_GetDeviceSizeInPages(MODEL(raw))-1;
    uint8_t  numCycles = 0;
    uint32_t addressCycle0 = 0;
    uint32_t addressCycle1234 = 0;
    uint8_t  cycleBytes[8], cycleIndex, bytePos;

    /* Check the data bus width of the NandFlash */
    if (NandFlashModel_GetDataBusWidth(MODEL(raw)) == 16) {
        /* Div 2 is because we address in word and not in byte */
        columnAddress >>= 1;
    }
    /* Convert column address */
    if (!rowOnly) {
        /* Send single column address byte for small block devices,
           or two column address bytes for large block devices */
        while (maxDataSize > 2) {
            cycleBytes[numCycles ++] = columnAddress & 0xFF;
            maxDataSize   >>= 8;
            columnAddress >>= 8;
        }
    }
    /* Convert row address */
    while (maxPageNum > 0) {
        cycleBytes[numCycles ++] = rowAddress & 0xFF;
        maxPageNum >>= 8;
        rowAddress >>= 8;
    }

    /* build addressCycle0 & addressCycle1234 */
    cycleIndex = 0;
    /* If more than 4 cycles, addressCycle0 is used */
    if (numCycles > 4) {
        for (bytePos = 0; cycleIndex < numCycles - 4; cycleIndex ++) {
            addressCycle0 += cycleBytes[cycleIndex] << bytePos;
            bytePos += 8;
        }
    }
    /* addressCycle1234 */
    for (bytePos = 0;cycleIndex < numCycles; cycleIndex ++) {
        addressCycle1234  += cycleBytes[cycleIndex] << bytePos;
        bytePos += 8;
    }

    /* Store values*/
    if (pAddressCycle0) {
        *pAddressCycle0 = addressCycle0;
    }
    if (pAddressCycle1234) {
        *pAddressCycle1234 = addressCycle1234;
    }
    //printf("%d cycles: %x %x\n\r", numCycles, addressCycle0, addressCycle1234);
    return numCycles;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Configure golbal parameter for SMC operation.
 *
 * \param cfg NAND SMC configuration.
 */
void Smc_OpConfigure(uint8_t cfg)
{
    SmcOpConfiguration.BCfg = cfg;
}

/**
 * \brief Get configuration of golbal parameter for SMC operation.
 */
uint8_t Smc_GetOpStatus(void)
{
   return SmcOpConfiguration.BCfg;
}

/**
 * \brief set SMC NAND global parameter to enable NFC
 */
void enableSmcOpNfc(void)
{
    SmcOpConfiguration.bCfg.nfc = SMC_NFC_ENABLE;
    HSMC->HSMC_CTRL = HSMC_CTRL_NFCEN;
}

/**
 * \brief set SMC NAND global parameter to disable NFC
 */
void disableSmcOpNfc(void)
{
    SmcOpConfiguration.bCfg.nfc = SMC_NFC_DISABLE;
    HSMC->HSMC_CTRL = HSMC_CTRL_NFCDIS;
}

/**
 * \brief return SMC NAND global parameter of NFC status
 */
uint8_t isSmcOpNfcEn(void)
{
   return SmcOpConfiguration.bCfg.nfc;
}

/**
 * \brief set SMC NAND global parameter to enable NFC Host SRAM
 */
void enableSmcOpNfcSram(void)
{
    SmcOpConfiguration.bCfg.nfcSram = SMC_NFC_SRAM_ENABLE;
}

/**
 * \brief set SMC NAND global parameter to disable NFC Host SRAM
 */
void disableSmcOpNfcSram(void)
{
    SmcOpConfiguration.bCfg.nfcSram = SMC_NFC_SRAM_DISABLE;
}

/**
 * \brief return SMC NAND global parameter of NFC Host SRAM status
 */
uint8_t isSmcOpNfcSramEn(void)
{
   return SmcOpConfiguration.bCfg.nfcSram;
}

/**
 * \brief set SMC NAND global parameter to enable DMA data transfer
 */
void enableSmcOpTransDma(void)
{
   SmcOpConfiguration.bCfg.xfrDma = SMC_TRANS_DMA_ENABLE;
}

/**
 * \brief set SMC NAND global parameter to disable DMA data transfer
 */
void disableSmcOpTransDma(void)
{
   SmcOpConfiguration.bCfg.xfrDma = SMC_TRANS_DMA_DISABLE;
}

/**
 * \brief return SMC NAND global parameter of DMA status
 */
uint8_t isSmcOpTransDmaEn(void)
{
   return SmcOpConfiguration.bCfg.xfrDma;
}

/**
 * \brief check if No ECC algorithm is avaliable of current SMC NAND global parameter
 */
uint8_t isSmcOpNoEcc(void)
{
   return (SmcOpConfiguration.bCfg.eccType == SMC_ECC_NOECC);
}

/**
 * \brief check if HSIAO ECC algorithm is avaliable of current SMC NAND global parameter
 */
uint8_t isSmcOpEccHsiao(void)
{
   return (SmcOpConfiguration.bCfg.eccType == SMC_ECC_HSIAO);
}

/**
 * \brief check if PMECC algorithm is avaliable of current SMC NAND global parameter
 */
uint8_t isSmcOpEccPmecc(void)
{
   return (SmcOpConfiguration.bCfg.eccType == SMC_ECC_PMECC);
}

/**
 * \brief set ecc type of SMC NAND global parameter
 */
void setSmcOpEccType(uint8_t eccTpye)
{
   SmcOpConfiguration.bCfg.eccType = eccTpye;
}

/**
 * \brief Return current ECC algorithm of current SMC NAND global parameter
 */
uint8_t getSmcOpEccType(void)
{
   return (SmcOpConfiguration.bCfg.eccType);
}

/**
 * \brief Sets NFC configuration.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param mode SMC ALE CLE mode parameter.
 * \param cmd1 First command to be sent.
 * \param cmd2 Second command to be sent.
 * \param colAddress Column address.
 * \param rowAddress Row address.
 */
 
void Smc_Issue_Cle_Ale(
     const struct RawNandFlash *raw,
     uint8_t mode,
     uint32_t cmd1,
     uint32_t cmd2,
     uint32_t colAddress,
     uint32_t rowAddress)
{
    uint32_t nfcCmd;
    uint32_t nfcData;
    uint32_t nfcRw;
    uint32_t nCycles, nfcAcycle;
    uint32_t addressCycle0 = 0;
    uint32_t addressCycle1234 = 0;

    /* Issue CLE and ALE through EBI */
    if(!isSmcOpNfcEn())
    {
        WRITE_COMMAND(raw, cmd1);
        if((mode & SMC_ALE_COL_EN) == SMC_ALE_COL_EN) WriteColumnAddress(raw, colAddress);
        if((mode & SMC_ALE_ROW_EN)== SMC_ALE_ROW_EN) WriteRowAddress(raw, rowAddress);
        if((mode & SMC_CLE_VCMD2_EN) == SMC_CLE_VCMD2_EN)
        /* When set to true, the CMD2 field is issued after the address cycle.*/
        {
            WRITE_COMMAND(raw, cmd2);
        }
    }
    /* Issue CLE and ALE using NFC */
    else 
    {
        if((mode & SMC_CLE_WRITE_EN) == SMC_CLE_WRITE_EN) 
        {
            nfcRw = NFCADDR_CMD_NFCWR;
        } else {
            nfcRw = NFCADDR_CMD_NFCRD;
        }
        if(((mode & SMC_CLE_DATA_EN) == SMC_CLE_DATA_EN) && isSmcOpNfcSramEn()) 
        {
            nfcData = NFCADDR_CMD_DATAEN;
        } else {
            nfcData = NFCADDR_CMD_DATADIS;
        }
        if(((mode & SMC_ALE_COL_EN) == SMC_ALE_COL_EN) ||
           ((mode & SMC_ALE_ROW_EN) == SMC_ALE_ROW_EN))
        {
            nCycles = NFC_TranslateAddress(raw, 
                                           colAddress, 
                                           rowAddress, 
                                           &addressCycle0, 
                                           &addressCycle1234, 
                                           (((mode & SMC_ALE_COL_EN) == 0) && 
                                           ((mode & SMC_ALE_ROW_EN) == SMC_ALE_ROW_EN)) ? 1 : 0);
            nfcAcycle = NFC_GetCmd_Acycle(nCycles);
        } else {
            nfcAcycle = NFCADDR_CMD_ACYCLE_NONE;
        }
        nfcCmd = (nfcRw |
                 nfcData | 
                 NFCADDR_CMD_CSID_3 |
                 nfcAcycle |
                 (((mode & SMC_CLE_VCMD2_EN) == SMC_CLE_VCMD2_EN) ? NFCADDR_CMD_VCMD2 : 0) |
                 (cmd1 << 2) |
                 (cmd2 << 10));
        SMC_NFC_SendCommand( nfcCmd, addressCycle1234, addressCycle0);
    }
}

static void Smc_CheckNandStatus (
     const struct RawNandFlash *raw,
     uint32_t status)
{
    Smc_Issue_Cle_Ale(raw, 0, COMMAND_STATUS, 0, 0, 0);
    while ((READ_DATA8(raw) & status) != status);
}

/**
 * \brief Waiting for the completion of a page program, erase and random read completion.
 * \param raw  Pointer to a RawNandFlash instance.
 */
void Smc_WaitForNandReady(const struct RawNandFlash *raw)
{
    if (raw->pinReadyBusy.mask) {
        while (!PIO_Get(&(raw->pinReadyBusy)));
    }
    else {
        Smc_CheckNandStatus(raw, STATUS_READY);
    }
}

/**
 * \brief  Return 1 if program or erase operation is completed.
 * and the program or erase operation is completed successfully, otherwise return 0.
 * \param raw  Pointer to a RawNandFlash instance.
 */
uint8_t Smc_IsOperationComplete(const struct RawNandFlash *raw)
{
    uint8_t status;
    Smc_Issue_Cle_Ale(raw, 0, COMMAND_STATUS, 0, 0, 0);
    status = READ_DATA8(raw);

    if (((status & STATUS_READY) != STATUS_READY) || ((status & STATUS_ERROR) != 0)) {
        return 0;
    }
    return 1;
}

/**
 * \brief Transfer data from NAND to the provided buffer.
 * \param busWidth  Nand flash data bus width
 * \param hostSram  Set 1 to enable NFC Host SRAM
 * \param buffer  Buffer where the data will be stored or sent.
 * \param size  Number of bytes that will be read
 */
void Smc_Data_Array_In(
    uint8_t busWidth,
    uint8_t hostSram,
    uint8_t *buffer,
    uint32_t size )
{
    uint32_t address;
    uint32_t i;
    if(hostSram)
    {
        address = NFC_SRAM_BASE_ADDRESS ;
        SMC_NFC_Wait_XfrDone();
    }  else {
        address = BOARD_NF_DATA_ADDR ;
    }
    if(isSmcOpTransDmaEn())
    {
       /* Check the data bus width of the NandFlash */
        NandFlashDmaTransferFromNand( address, (uint32_t)buffer, size );
    }
    /* Transfer without DMA */
    else
    {
        /* Check the data bus width of the NandFlash */
        if (busWidth == 16 && !hostSram) 
        {
            uint16_t *pbuff16 = (uint16_t *)((void *)buffer);
            volatile uint16_t * pDataAddress16 = (volatile uint16_t *)address;
            size = (size + 1) >> 1;
            if (hostSram){
                for(i = size; i != 0; i--)
                {
                    *(pbuff16++) = *pDataAddress16++;
                }
            }
            else {
                for(i = size; i != 0; i--)
                {
                    *(pbuff16++) = *pDataAddress16;
                }
            }
        }
        else 
        {
            uint8_t *pbuff8 = buffer; 
            volatile uint8_t * pDataAddress8 = (volatile uint8_t *)address;
            if (hostSram) {
                for(i = size; i != 0; i--)
                {
                    *(pbuff8++) = *pDataAddress8++;
                }
            }
            else {
                for(i = size; i != 0; i--)
                {
                    *(pbuff8++) = *pDataAddress8;
                }
            }
        }
    }
    
}

/**
 * \brief Transfer data to NAND from the provided buffer.
 * \param busWidth  Nand flash data bus width
 * \param hostSram  Set 1 to enable NFC Host SRAM
 * \param buffer  Buffer where the data will be stored or sent.
 * \param size  Number of bytes that will be read
 * \param offset Offset in bytes.
 */

void Smc_Data_Array_Out (
    uint8_t busWidth,
    uint8_t hostSram,
    uint8_t *buffer,
    uint32_t size,
    uint32_t offset )
{
    uint32_t address;
    uint32_t i;

    if (hostSram)
    {
        address = NFC_SRAM_BASE_ADDRESS ;
    }  else {
        address = BOARD_NF_DATA_ADDR ;
    }
    address += offset;
    if(isSmcOpTransDmaEn())
    {
       /* Check the data bus width of the NandFlash */
       NandFlashDmaTransferToNand((uint32_t)buffer, address, size );
    }
    /* Transfer without DMA */
    else
    {
        /* Check the data bus width of the NandFlash */
        if (busWidth == 16 && !hostSram) {
            uint16_t *pbuff16 = (uint16_t *)(void*) buffer;
            volatile uint16_t * pDataAddress16 = (volatile uint16_t *)address;
            size = (size + 1)>> 1;
            if (hostSram){
                for(i = size; i != 0; i--)
                {
                    *pDataAddress16++ = *(pbuff16++);
                }
            } else {
                for(i = size; i != 0; i--)
                {
                    *pDataAddress16 = *(pbuff16++);
                }
            }
        }
        else 
        {
            uint8_t *pbuff8 = buffer; 
            volatile uint8_t * pDataAddress8 = (volatile uint8_t *)address;
            if (hostSram){
                for(i = size; i != 0; i--)
                {
                    *pDataAddress8++ = *(pbuff8++);
                } 
            } else {
                for(i = size; i != 0; i--)
                {
                    *pDataAddress8 = *(pbuff8++);
                } 
            }
        }
    }
}
