/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <board.h>
#include <libnandflash.h>
#include <libpmecc.h>

#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
 

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

/** Number of tries for erasing a block */
#define NUMERASETRIES           2
/** Number of tries for writing a block */
#define NUMWRITETRIES           2
/** Number of tries for copying a block */
#define NUMCOPYTRIES            2

/*----------------------------------------------------------------------------
 *        Internal functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Erases the specified block of the device. Returns 0 if the operation was
 * successful; otherwise returns an error code.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param block  Number of the physical block to erase.
 */
static uint8_t EraseBlock(
    const struct RawNandFlash *raw,
    uint16_t block)
{
    uint8_t error = 0;
    uint32_t rowAddress;
    TRACE_DEBUG("EraseBlock(%d)\r\n", block);
    /* Calculate address used for erase */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw));
    Smc_Issue_Cle_Ale(raw, SMC_CLE_VCMD2_EN|SMC_ALE_ROW_EN, COMMAND_ERASE_1, COMMAND_ERASE_2, 0, rowAddress);
    Smc_WaitForNandReady(raw);
    if (!Smc_IsOperationComplete(raw)) {
        TRACE_ERROR(
                 "EraseBlock: Could not erase block %d.\n\r",
                 block);
        error = NandCommon_ERROR_CANNOTERASE;
    }
    return error;
}

/**
 * \brief Reads the data and/or the spare areas of a page of a NandFlash into the
 * provided buffers. If a buffer pointer is 0, the corresponding area is not
 * read.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param block  Number of the block where the page to read resides.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
static uint8_t ReadPage(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint32_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));
    uint32_t pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(raw));
    uint32_t busWidth = NandFlashModel_GetDataBusWidth(MODEL(raw));
    uint32_t colAddress, rowAddress, smcEccPageSize;
    uint32_t smcMode;
    uint32_t smcTransType = 0;
    
    SMC->SMC_ECC_MD &= ~SMC_ECC_MD_HAMMING;
    if(isSmcOpNfcEn())
    {
        switch (pageDataSize){
            case 512:  smcEccPageSize = SMC_CFG_PAGESIZE_PS512_16;  break;
            case 1024: smcEccPageSize = SMC_CFG_PAGESIZE_PS1024_32; break;
            case 2048: smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
            case 4096: smcEccPageSize = SMC_CFG_PAGESIZE_PS4096_128; break;
            default : smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
        }
        SMC->SMC_CFG = SMC_CFG_NFCSPARESIZE((pageSpareSize-1) >> 2) | 
                                SMC_CFG_DTOCYC(0xF) | 
                                SMC_CFG_DTOMUL_X1048576 | 
                                SMC_CFG_RBEDGE | 
                                0 << 8 | 
                                smcEccPageSize;
    }
    assert ( data || spare); /* RawNandFlash_ReadPage: At least one area must be read */
    TRACE_DEBUG("RdPg(B#%d:P#%d)\r\n", block, page);

    /* Calculate actual address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;
    if ( data ) colAddress = 0; else colAddress = pageDataSize;
    if(isSmcOpNfcSramEn()){
        smcTransType |= SMC_TRANS_HOST_EN;
        smcMode = SMC_ALE_COL_EN | SMC_ALE_ROW_EN | SMC_CLE_VCMD2_EN | SMC_CLE_DATA_EN;
        Smc_Issue_Cle_Ale(raw, smcMode, COMMAND_READ_1, COMMAND_READ_2, colAddress, rowAddress);
    } else {
        smcMode = SMC_ALE_COL_EN | SMC_ALE_ROW_EN | SMC_CLE_VCMD2_EN;
        Smc_Issue_Cle_Ale(raw, smcMode, COMMAND_READ_1, COMMAND_READ_2, colAddress, rowAddress);
    }
    if (!isSmcOpNfcEn()){
        /* Wait for the nand to be ready */
        Smc_WaitForNandReady( raw );
        Smc_Issue_Cle_Ale(raw, SMC_CLE_DATA_EN, COMMAND_READ_1, 0, 0, 0);
    } else {
        if(!isSmcOpNfcSramEn()) SMC_NFC_Wait_RBbusy();
    }
    /* Read data area if needed */
    if ( data ){
        Smc_Data_Array_In(busWidth, smcTransType, (uint8_t *)data, pageDataSize);
        if ( spare ) Smc_Data_Array_In(busWidth, smcTransType, (uint8_t *)spare, pageSpareSize);
    } else {
        /* Read spare area only */
        Smc_Data_Array_In(busWidth, smcTransType,(uint8_t *)spare, pageSpareSize);
    }
    return 0;
}

/**
 * \brief Reads the data and/or the spare areas of a page of a NandFlash into the
 * provided buffers. If a buffer pointer is 0, the corresponding area is not
 * read.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param block  Number of the block where the page to read resides.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
static uint8_t ReadPageWithPmecc(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint32_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));
    uint32_t pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(raw));
    uint32_t rowAddress, smcEccPageSize;
    uint32_t smcMode;
    uint32_t smcTransType = 0;
    if(isSmcOpNfcEn()){
        switch (pageDataSize){
            case 512:  smcEccPageSize = SMC_CFG_PAGESIZE_PS512_16;  break;
            case 1024: smcEccPageSize = SMC_CFG_PAGESIZE_PS1024_32; break;
            case 2048: smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
            case 4096: smcEccPageSize = SMC_CFG_PAGESIZE_PS4096_128; break;
            default : smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
        }
        SMC->SMC_CFG = SMC_CFG_NFCSPARESIZE((pageSpareSize-1) >> 2) | 
                                SMC_CFG_DTOCYC(0xF) | 
                                SMC_CFG_DTOMUL_X1048576 | 
                                SMC_CFG_RBEDGE | 
                                0 << 8 |
                                1 << 9 |
                                smcEccPageSize;
    }
    assert ( data || spare); /* RawNandFlash_ReadPage: At least one area must be read */
    TRACE_DEBUG("RdPg(B#%d:P#%d)\r\n", block, page);

    /* Calculate actual address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;
    if(isSmcOpNfcEn() && isSmcOpNfcSramEn()) smcTransType |= SMC_TRANS_HOST_EN;
    SMC->SMC_PMECCTRL = SMC_PMECCTRL_RST;
    SMC->SMC_PMECCTRL = SMC_PMECCTRL_ENABLE;
    if ((SMC->SMC_PMECCFG & SMC_PMECCFG_SPAREEN) != SMC_PMECCFG_SPAREEN) SMC->SMC_PMECCFG |= SMC_PMECCFG_AUTO;

    if(isSmcOpNfcSramEn()){
        smcTransType |= SMC_TRANS_HOST_EN;
        smcMode = SMC_ALE_COL_EN | SMC_ALE_ROW_EN | SMC_CLE_VCMD2_EN | SMC_CLE_DATA_EN;
        SMC->SMC_PMECCTRL |= SMC_PMECCTRL_DATA;
        Smc_Issue_Cle_Ale(raw, smcMode, COMMAND_READ_1, COMMAND_READ_2, 0, rowAddress);
    } else {
        smcMode = SMC_ALE_COL_EN | SMC_ALE_ROW_EN | SMC_CLE_VCMD2_EN;
        Smc_Issue_Cle_Ale(raw, smcMode, COMMAND_READ_1, COMMAND_READ_2, 0, rowAddress);
    }
    if (!isSmcOpNfcEn()){
        /* Wait for the nand to be ready */
        Smc_WaitForNandReady( raw );
        Smc_Issue_Cle_Ale(raw, 0, COMMAND_READ_1, 0, 0, 0);
    } else {
        if(!isSmcOpNfcSramEn()) SMC_NFC_Wait_RBbusy();
    }
    /* Reset the ECC module*/
    SMC->SMC_PMECCTRL |= SMC_PMECCTRL_RST;
    /* Start a Data Phase */
    SMC->SMC_PMECCTRL |= SMC_PMECCTRL_DATA;
    Smc_Data_Array_In(NandFlashModel_GetDataBusWidth(MODEL(raw)),
                      smcTransType,
                      (uint8_t *)data,
                      pageDataSize + (SMC->SMC_PMECCEADDR + 1));
    /* Wait until the kernel of the PMECC is not busy */
    while(( SMC->SMC_PMECCSR) & SMC_PMECCSR_BUSY);
    return 0;
}

static uint8_t ReadPageWithHwEcc(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint32_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));
    uint32_t pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(raw));
    uint32_t busWidth = NandFlashModel_GetDataBusWidth(MODEL(raw));
    uint32_t rowAddress,smcEccPageSize;
    uint32_t smcMode;
    uint32_t smcTransType = 0;
    uint32_t eccTable[48];
    volatile uint32_t delay;
    if(isSmcOpNfcEn())
    {
        switch (pageDataSize){
            case 512:  smcEccPageSize = SMC_CFG_PAGESIZE_PS512_16;  break;
            case 1024: smcEccPageSize = SMC_CFG_PAGESIZE_PS1024_32; break;
            case 2048: smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
            case 4096: smcEccPageSize = SMC_CFG_PAGESIZE_PS4096_128; break;
            default : smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
        }
        SMC->SMC_CFG = SMC_CFG_NFCSPARESIZE((pageSpareSize-1) >> 2) | 
                                SMC_CFG_DTOCYC(0xF) | 
                                SMC_CFG_DTOMUL_X1048576 | 
                                SMC_CFG_RBEDGE | 
                                0 << 8 | 
                                smcEccPageSize;
    }
    assert ( data || spare); /* RawNandFlash_ReadPage: At least one area must be read */
    TRACE_DEBUG("RdPg(B#%d:P#%d)\r\n", block, page);
    
    SMC->SMC_CFG = SMC_CFG_NFCSPARESIZE((pageSpareSize-1) >> 2) | 
                                SMC_CFG_DTOCYC(0xF) | 
                                SMC_CFG_DTOMUL_X1048576 | 
                                SMC_CFG_RBEDGE | 
                                1 << 9 | 
                                pageDataSize;
    SMC->SMC_ECC_CTRL = SMC_ECC_CTRL_RST;
    SMC->SMC_ECC_MD |=SMC_ECC_MD_HAMMING;
    SMC_NFC_EnableSpareRead();

    /* Calculate actual address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;
    if(isSmcOpNfcSramEn()){
        smcTransType |= SMC_TRANS_HOST_EN;
        smcMode = SMC_ALE_COL_EN | SMC_ALE_ROW_EN | SMC_CLE_VCMD2_EN | SMC_CLE_DATA_EN;
        Smc_Issue_Cle_Ale(raw, smcMode, COMMAND_READ_1, COMMAND_READ_2, 0, rowAddress);
    } else {
        smcMode = SMC_ALE_COL_EN | SMC_ALE_ROW_EN | SMC_CLE_VCMD2_EN;
        Smc_Issue_Cle_Ale(raw, smcMode, COMMAND_READ_1, COMMAND_READ_2, 0, rowAddress);
    }
    if(!isSmcOpNfcSramEn()) for( delay =0; delay<0xfffff; delay++);
    Smc_Data_Array_In(busWidth, smcTransType, (uint8_t *)data, pageDataSize);
    SMC_NFC_Wait_HammingReady();
    if(!isSmcOpNfcSramEn()) for( delay =0; delay<0xffff; delay++);
    delay = 0x12345678;
    while(1){
        delay = SMC->SMC_ECC_PR3;
        if(delay!=0x12345678) break;
    }
    Smc_Issue_Cle_Ale(raw, SMC_ALE_COL_EN | SMC_CLE_VCMD2_EN, COMMAND_RANDOM_OUT, COMMAND_RANDOM_OUT_2, pageDataSize+2, 0);
    Smc_Data_Array_In(busWidth, 0, (uint8_t *)eccTable, 32);
    
    return 0;
}

/**
 * \brief Writes the data and/or the spare area of a page on a NandFlash chip. If one
 * of the buffer pointer is 0, the corresponding area is not written.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param block  Number of the block where the page to write resides.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \return 0 if the write operation is successful; otherwise returns 1.
*/

static uint8_t WritePage(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t error = 0;
    uint32_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));
    uint32_t pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(raw));
    uint32_t rowAddress,smcEccPageSize;
    uint32_t busWidth = NandFlashModel_GetDataBusWidth(MODEL(raw));
    SMC->SMC_ECC_MD &= ~SMC_ECC_MD_HAMMING;
    if(isSmcOpNfcEn())
    {
        switch (pageDataSize){
            case 512:  smcEccPageSize = SMC_CFG_PAGESIZE_PS512_16;  break;
            case 1024: smcEccPageSize = SMC_CFG_PAGESIZE_PS1024_32; break;
            case 2048: smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
            case 4096: smcEccPageSize = SMC_CFG_PAGESIZE_PS4096_128; break;
            default : smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
        }
        SMC->SMC_CFG = SMC_CFG_NFCSPARESIZE((pageSpareSize-1) >> 2) | 
                                SMC_CFG_DTOCYC(0xF) | 
                                SMC_CFG_DTOMUL_X1048576 | 
                                SMC_CFG_RBEDGE | 
                                1 << 8 | 
                                smcEccPageSize;
    }
    /* Calculate physical address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;
    TRACE_DEBUG("WritePage(B#%d:P#%d)\r\n", block, page);
    /* Calculate physical address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;

    if(isSmcOpNfcEn() && isSmcOpNfcSramEn() && data)
    {
        Smc_Data_Array_Out(busWidth, SMC_TRANS_HOST_EN, (uint8_t *)data, pageDataSize);
    }
    /* Write data area if needed */
    if (data) {
        /* Start a Data Phase */
        if(isSmcOpNfcEn() && isSmcOpNfcSramEn()) {
            Smc_Issue_Cle_Ale(raw, 
                              SMC_CLE_WRITE_EN | SMC_ALE_COL_EN |SMC_ALE_ROW_EN |SMC_CLE_DATA_EN, 
                              COMMAND_WRITE_1, 0, 0, rowAddress);
        SMC_NFC_Wait_XfrDone();
        } else {
            Smc_Issue_Cle_Ale(raw, 
                              SMC_CLE_WRITE_EN | SMC_ALE_COL_EN |SMC_ALE_ROW_EN, 
                              COMMAND_WRITE_1, 0, 0, rowAddress);
        }
        if(!isSmcOpNfcSramEn()) Smc_Data_Array_Out(busWidth, 0, (uint8_t *)data, pageDataSize);
        /* Spare is written here as well since it is more efficient */
        if (spare) {
            Smc_Data_Array_Out(busWidth, 0, (uint8_t *)spare, pageSpareSize);
        }
        Smc_Issue_Cle_Ale(raw, SMC_CLE_WRITE_EN, COMMAND_WRITE_2, 0, 0, 0);
        if(!isSmcOpNfcEn()) {
            Smc_WaitForNandReady(raw);
        } else {
            SMC_NFC_Wait_RBbusy();
        }
        if (!Smc_IsOperationComplete(raw)) {
        TRACE_ERROR("WritePage: Failed writing data area.\n\r");
        error = NandCommon_ERROR_CANNOTWRITE;
        }
        /* Write spare area alone if needed */
        if (spare && !data) {
            Smc_Issue_Cle_Ale(raw, SMC_CLE_WRITE_EN|SMC_ALE_COL_EN|SMC_ALE_ROW_EN, COMMAND_WRITE_1,0,  pageDataSize, rowAddress);
            Smc_Data_Array_Out(busWidth, 0, (uint8_t *)spare, pageSpareSize);
            Smc_Issue_Cle_Ale(raw, SMC_CLE_WRITE_EN, COMMAND_WRITE_2,0, 0, 0);
            Smc_WaitForNandReady(raw);
            if (!Smc_IsOperationComplete(raw)) {
                TRACE_ERROR("WritePage: Failed writing data area.\n\r");
                error = NandCommon_ERROR_CANNOTWRITE;
            }
        }
    }
    return error;
}

/**
 * \brief Writes the data and/or the spare area of a page on a NandFlash chip. If one
 * of the buffer pointer is 0, the corresponding area is not written.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param block  Number of the block where the page to write resides.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \return 0 if the write operation is successful; otherwise returns 1.
*/
static uint8_t WritePageWithPmecc(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t error = 0;
    uint32_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));
    uint32_t rowAddress;
    uint32_t eccStartaddr;
    uint32_t bytesNumberPerSector;
    uint32_t sectorNumber;
    uint32_t sectorIndex;
    uint32_t byteNumber;
    uint8_t *pmecc[8];
    uint8_t i;
    uint8_t eccTable[NAND_MAX_PMECCSIZE];
    PmeccDescriptor *pPmeccDescriptor;
    uint8_t nbSectorsPerPage;
    uint32_t busWidth = NandFlashModel_GetDataBusWidth(MODEL(raw));
    /* Calculate physical address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;
    eccStartaddr = pageDataSize + SMC->SMC_PMECCSADDR;

    TRACE_DEBUG("WritePage(B#%d:P#%d)\r\n", block, page);
    /* Calculate physical address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;
    if (isNandTrimffs() && page >= NandGetTrimPage()) return 0;

    if(isSmcOpNfcEn() && isSmcOpNfcSramEn() && data)
        Smc_Data_Array_Out(busWidth, SMC_TRANS_HOST_EN, (uint8_t *)data, pageDataSize);
    /* Write data area if needed */
    pPmeccDescriptor = PMECC_GetCurrentPmeccDescriptor();
    switch ( pPmeccDescriptor->pageSize ) {
        case SMC_PMECCFG_PAGESIZE_PAGESIZE_1SEC: nbSectorsPerPage = 1; break;
        case SMC_PMECCFG_PAGESIZE_PAGESIZE_2SEC: nbSectorsPerPage = 2; break;
        case SMC_PMECCFG_PAGESIZE_PAGESIZE_4SEC: nbSectorsPerPage = 4; break;
        case SMC_PMECCFG_PAGESIZE_PAGESIZE_8SEC: nbSectorsPerPage = 8; break;
        default: nbSectorsPerPage = 1; break;
    } 
    SMC->SMC_PMECCTRL = SMC_PMECCTRL_RST;
    SMC->SMC_PMECCTRL = SMC_PMECCTRL_ENABLE;
    for (i=0; i < 8; i++) pmecc[i] = (uint8_t*)(&SMC->SMC_PMECC[i]);
    SMC->SMC_PMECCTRL |= SMC_PMECCTRL_DATA; /* Start a Data Phase */
    SMC->SMC_PMECCFG |= SMC_PMECCFG_NANDWR;
    if(isSmcOpNfcEn() && isSmcOpNfcSramEn()) {
        Smc_Issue_Cle_Ale(raw, 
                          SMC_CLE_WRITE_EN | SMC_ALE_COL_EN |SMC_ALE_ROW_EN |SMC_CLE_DATA_EN, 
                          COMMAND_WRITE_1, 0, 0, rowAddress);
        SMC_NFC_Wait_XfrDone();
    } else {
        Smc_Issue_Cle_Ale(raw, 
                          SMC_CLE_WRITE_EN | SMC_ALE_COL_EN |SMC_ALE_ROW_EN, 
                          COMMAND_WRITE_1, 0, 0, rowAddress);
    }
    if(!isSmcOpNfcSramEn()) Smc_Data_Array_Out(busWidth, 0, (uint8_t *)data, pageDataSize);
    Smc_Issue_Cle_Ale(raw, SMC_CLE_WRITE_EN|SMC_ALE_COL_EN, COMMAND_RANDOM_IN, 0, eccStartaddr, 0);
    /* Wait until the kernel of the PMECC is not busy */
    while((SMC->SMC_PMECCSR) & SMC_PMECCSR_BUSY);
    bytesNumberPerSector = (pPmeccDescriptor->eccSizeByte) / nbSectorsPerPage;
    sectorNumber = 1 << ((pPmeccDescriptor->pageSize >> 8) & 0x3);
    //if (isNandTrimffs() && page >= NandGetTrimPage()) {
        /* This behaviour was found to fix both UBI and JFFS2 images written to
           cleanly erased NAND partitions*/
      //  for(sectorIndex = 0; sectorIndex < sectorNumber; sectorIndex++)
        //{
          //  for(byteNumber = 0; byteNumber < bytesNumberPerSector; byteNumber++)
            //    eccTable[sectorIndex * bytesNumberPerSector + byteNumber] = 0xFF;
        //}
    //} else 
        {
        /* Read all ECC registers */
        for(sectorIndex = 0; sectorIndex < sectorNumber; sectorIndex++){
            for(byteNumber = 0; byteNumber < bytesNumberPerSector; byteNumber++)
                eccTable[sectorIndex * bytesNumberPerSector + byteNumber] = pmecc[sectorIndex][byteNumber];
        }
    }
    Smc_Data_Array_Out(busWidth, 0, (uint8_t *)(uint8_t *) eccTable, sectorNumber * bytesNumberPerSector);
    Smc_Issue_Cle_Ale(raw, SMC_CLE_WRITE_EN, COMMAND_WRITE_2, 0, 0, 0);
    Smc_WaitForNandReady(raw);
    if (!Smc_IsOperationComplete(raw)) {
        TRACE_ERROR("WritePage: Failed writing data area.\n\r");
        error = NandCommon_ERROR_CANNOTWRITE;
    }
    return error;
}

static uint8_t WritePageWithHwEcc(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t error = 0;
    uint32_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));
    uint32_t pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(raw));
    uint32_t rowAddress,smcEccPageSize;
    uint32_t busWidth = NandFlashModel_GetDataBusWidth(MODEL(raw));
    uint8_t eccTable[48];
    SMC->SMC_ECC_CTRL = SMC_ECC_CTRL_RST;
    SMC->SMC_ECC_MD |=SMC_ECC_MD_HAMMING;
    SMC_NFC_EnableSpareWrite();
    if(isSmcOpNfcEn())
    {
        switch (pageDataSize){
            case 512:  smcEccPageSize = SMC_CFG_PAGESIZE_PS512_16;  break;
            case 1024: smcEccPageSize = SMC_CFG_PAGESIZE_PS1024_32; break;
            case 2048: smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
            case 4096: smcEccPageSize = SMC_CFG_PAGESIZE_PS4096_128; break;
            default : smcEccPageSize = SMC_CFG_PAGESIZE_PS2048_64; break;
        }
        SMC->SMC_CFG = SMC_CFG_NFCSPARESIZE((pageSpareSize-1) >> 2) | 
                                SMC_CFG_DTOCYC(0xF) | 
                                SMC_CFG_DTOMUL_X1048576 | 
                                SMC_CFG_RBEDGE | 
                                1 << 8 | 
                                smcEccPageSize;
    }
    /* Calculate physical address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;
    TRACE_DEBUG("WritePage(B#%d:P#%d)\r\n", block, page);
    /* Calculate physical address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;

    if(isSmcOpNfcEn() && isSmcOpNfcSramEn() && data)
        Smc_Data_Array_Out(busWidth, SMC_TRANS_HOST_EN, (uint8_t *)data, pageDataSize);
    if(isSmcOpNfcEn() && isSmcOpNfcSramEn()) {
        Smc_Issue_Cle_Ale(raw, 
                          SMC_CLE_WRITE_EN | SMC_ALE_COL_EN |SMC_ALE_ROW_EN |SMC_CLE_DATA_EN, 
                          COMMAND_WRITE_1, 0, 0, rowAddress);
        SMC_NFC_Wait_XfrDone();
        } else {
            Smc_Issue_Cle_Ale(raw, 
                              SMC_CLE_WRITE_EN | SMC_ALE_COL_EN |SMC_ALE_ROW_EN, 
                              COMMAND_WRITE_1, 0, 0, rowAddress);
        }
        if(!isSmcOpNfcSramEn()) Smc_Data_Array_Out(busWidth, 0, (uint8_t *)data, pageDataSize);
       // SMC_NFC_Wait_HammingReady();
        SMC_ECC_GetEccParity(pageDataSize, eccTable, busWidth);

        Smc_Issue_Cle_Ale(raw, SMC_CLE_WRITE_EN|SMC_ALE_COL_EN, COMMAND_RANDOM_IN, 0, pageDataSize, 0);

        Smc_Data_Array_Out(busWidth, 0,(uint8_t *) eccTable, 16);
        Smc_Issue_Cle_Ale(raw, SMC_CLE_WRITE_EN, COMMAND_WRITE_2, 0, 0, 0);
        if(!isSmcOpNfcEn()) Smc_WaitForNandReady(raw); else  SMC_NFC_Wait_RBbusy();
        if (!Smc_IsOperationComplete(raw)) {
        TRACE_ERROR("WritePage: Failed writing data area.\n\r");
        error = NandCommon_ERROR_CANNOTWRITE;
    }
    return error;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

 /**
 * \brief Initializes a RawNandFlash instance based on the given model and physical
 * interface. If no model is provided, then the function tries to autodetect it.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param model  Pointer to the underlying nand chip model. Can be 0.
 * \param commandAddress  Address at which commands are sent.
 * \param addressAddress  Address at which addresses are sent.
 * \param dataAddress  Address at which data is sent.
 * \param pinChipEnable  Pin controlling the CE signal of the NandFlash.
 * \param pinReadyBusy  Pin used to monitor the ready/busy signal of the Nand.
 * \returns 0 if initialization is successful; otherwise returns
 * NandCommon_ERROR_UNKNOWNMODEL.
*/ 
uint8_t RawNandFlash_Initialize(
    struct RawNandFlash *raw,
    const struct NandFlashModel *model,
    uint32_t commandAddress,
    uint32_t addressAddress,
    uint32_t dataAddress,
    const Pin pinChipEnable,
    const Pin pinReadyBusy)
{
    TRACE_DEBUG("RawNandFlash_Initialize()\n\r");
    /* Initialize fields */
    raw->commandAddress = commandAddress;
    raw->addressAddress = addressAddress;
    raw->dataAddress = dataAddress;
    raw->pinChipEnable = pinChipEnable;
    raw->pinReadyBusy = pinReadyBusy;
    
    /* Reset */
    RawNandFlash_Reset(raw);

    /* If model is not provided, autodetect it */
    if (!model) {

        TRACE_DEBUG("No model provided, trying autodetection ...\n\r");
        if (NandFlashModel_Find(nandFlashModelList,
                                NandFlashModelList_SIZE,
                                RawNandFlash_ReadId(raw),
                                &(raw->model))) {
            TRACE_ERROR(
                      "RawNandFlash_Initialize: Could not autodetect chip.\n\r");
            return NandCommon_ERROR_UNKNOWNMODEL;
        }
    }
    else {

        /* Copy provided model */
        raw->model = *model;
    }

    return 0;
}

/**
 * \brief Resets a NandFlash device.
 * \param raw  Pointer to a RawNandFlash instance.
 */
void RawNandFlash_Reset(const struct RawNandFlash *raw)
{
    TRACE_DEBUG("RawNandFlash_Reset()\n\r");
    Smc_Issue_Cle_Ale(raw, 0, COMMAND_RESET, 0, 0, 0);
    Smc_WaitForNandReady(raw);
}

/**
 * \brief Reads and returns the identifiers of a NandFlash chip.
 * \param raw  Pointer to a RawNandFlash instance.
 * \return id1|(id2<<8)|(id3<<16)|(id4<<24)
*/
uint32_t RawNandFlash_ReadId(const struct RawNandFlash *raw)
{
    uint32_t chipId, chipId2;
    TRACE_DEBUG("RawNandFlash_ReadId()\n\r");
    //Smc_Issue_Cle_Ale(raw, SMC_ALE_ROW_EN, COMMAND_READID, 0, 0, 0);
    WRITE_COMMAND(raw, COMMAND_READID);
    WRITE_ADDRESS(raw, 0);
    chipId  = READ_DATA8(raw);
    chipId |= READ_DATA8(raw) << 8;
    chipId |= READ_DATA8(raw) << 16;
    chipId |= READ_DATA8(raw) << 24;
    chipId2  = READ_DATA8(raw);
    TRACE_INFO("CHIP ID %x %x %x %x %x\n\r",
    (unsigned int)(chipId & 0xFF), 
    (unsigned int)((chipId & 0xFF00)>>8), 
    (unsigned int)((chipId & 0xFF0000) >> 16), 
    (unsigned int)((chipId & 0xFF000000) >> 24),
    (unsigned int) chipId2);
    return chipId;
}

/**
 * \brief Erases the specified block of the device, retrying several time if it fails.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param block  Number of the physical block to erase.
 * \return 0 if successful; otherwise returns NandCommon_ERROR_BADBLOCK.
 */
uint8_t RawNandFlash_EraseBlock(
    const struct RawNandFlash *raw,
    uint16_t block)
{
    uint8_t numTries = NUMERASETRIES;
    TRACE_DEBUG("RawNandFlash_EraseBlock(B#%d)\n\r", block);
    while (numTries > 0) {
        if (!EraseBlock(raw, block)) {
            return 0;
        }
        numTries--;
    }
    TRACE_ERROR("RawNandFlash_EraseBlock: Failed to erase %d after %d tries\n\r",
                block, NUMERASETRIES);
    return NandCommon_ERROR_BADBLOCK;
}

/**
 * \brief Reads the data and/or the spare areas of a page of a NandFlash into the
 * provided buffers. If a buffer pointer is 0, the corresponding area is not
 * read.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param block  Number of the block where the page to read resides.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
uint8_t RawNandFlash_ReadPage(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t eccStatus;
    eccStatus = getSmcOpEccType();
    if ((eccStatus == SMC_ECC_NOECC) || 
        (eccStatus == SMC_ECC_INTERNAL) || 
        (eccStatus == SMC_ECC_SOFTWARE) ||
        spare) {
        return ReadPage( raw, block, page, data, spare);
    }
    if ((eccStatus == SMC_ECC_PMECC) && PMECC_GetCurrentPmeccDescriptor()){
        return ReadPageWithPmecc( raw, block, page, data,0);
    }
    if (eccStatus == SMC_ECC_HSIAO) return ReadPageWithHwEcc( raw, block, page, data,0);
    return NandCommon_ERROR_BADBLOCK;
}

/**
 * \brief Writes the data and/or the spare area of a page on a NandFlash chip. If one
 * of the buffer pointer is 0, the corresponding area is not written. Retries
 * several time if there is an error.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param block  Number of the block where the page to write resides.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \param spare  Buffer containing the spare area.
 * \return 0 if the write operation is successful; otherwise returns
 * NandCommon_ERROR_BADBLOCK.
 */
uint8_t RawNandFlash_WritePage (
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t eccStatus;
    uint8_t numTries = NUMWRITETRIES;
    eccStatus = getSmcOpEccType();
    TRACE_DEBUG("RawNandFlash_WritePage(B#%d:P#%d)\r\n", block, page);
    if ((eccStatus == SMC_ECC_NOECC) || 
        (eccStatus == SMC_ECC_INTERNAL) || 
        (eccStatus == SMC_ECC_SOFTWARE)) {
        while ( numTries > 0 ) 
        {
            if ( !WritePage(raw, block, page, data, spare )) {
                return 0;
            }
            numTries--;
        }
    }
    if ((eccStatus == SMC_ECC_PMECC) && PMECC_GetCurrentPmeccDescriptor()){
        numTries = 1;
        if ( !WritePageWithPmecc(raw, block, page, data, spare )) return 0;
    }
    if (eccStatus == SMC_ECC_HSIAO){
        numTries = 1;
        if ( !WritePageWithHwEcc(raw, block, page, data, spare )) return 0;
    }
    TRACE_ERROR ( "RawNandFlash_WritePage: Failed to write page after %d tries\n\r", NUMWRITETRIES);
    return NandCommon_ERROR_BADBLOCK;
}
