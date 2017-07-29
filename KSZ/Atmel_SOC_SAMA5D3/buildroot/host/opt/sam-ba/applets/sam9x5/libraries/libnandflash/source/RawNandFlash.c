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

/**
 * \brief Waiting for the completion of a page program, erase and random read completion.
 * \param raw  Pointer to a RawNandFlash instance.
 */
static void WaitReady(const struct RawNandFlash *raw)
{
    if (raw->pinReadyBusy.mask) {
        while (!PIO_Get(&(raw->pinReadyBusy)));
    }
    else {
        WRITE_COMMAND(raw, COMMAND_STATUS);
        while ((READ_DATA8(raw) & STATUS_READY) != STATUS_READY);
    }
}

/**
 * \brief  Return 1 if program or erase operation is completed.
 * and the program or erase operation is completed successfully, otherwise return 0.
 * \param raw  Pointer to a RawNandFlash instance.
 */
static uint8_t IsOperationComplete(const struct RawNandFlash *raw)
{
    uint8_t status;

    WRITE_COMMAND(raw, COMMAND_STATUS);

    status = READ_DATA8(raw);

    if (((status & STATUS_READY) != STATUS_READY) || ((status & STATUS_ERROR) != 0)) {
        return 0;
    }
    return 1;
}

/**
 * \brief Sends data to the NandFlash chip from the provided buffer.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param buffer  Buffer where the data is stored.
 * \param size  Number of bytes that will be written
 */
static void WriteData(
    const struct RawNandFlash *raw,
    uint8_t *buffer,
    uint32_t size)
{
    uint16_t i;
    if (NandFlashIsDmaActived())
    {
        /* Check the data bus width of the NandFlash */
        if (NandFlashModel_GetDataBusWidth(MODEL(raw)) == 16) {
            size >>= 1;
            NandFlashDmaTransferRam2Nand( (uint32_t)buffer, size );
        }
        else 
        {
            NandFlashDmaTransferRam2Nand( (uint32_t)buffer, size );
        }
    }
    else
    {
        /* Check the data bus width of the NandFlash */
        if (NandFlashModel_GetDataBusWidth(MODEL(raw)) == 16) {
            uint16_t *pbuff16 = (uint16_t *)(void*) buffer;
            volatile uint16_t * pDataAddress16 = (volatile uint16_t *) raw->dataAddress;
            size >>= 1;
            for(i = size; i != 0; i--)
            {
                *pDataAddress16 = *(pbuff16++);
            }
        }
        else 
        {
            uint8_t *pbuff8 = buffer; 
            volatile uint8_t * pDataAddress8 = (volatile uint8_t *) raw->dataAddress;
            for(i = size; i != 0; i--)
            {
                *pDataAddress8 = *(pbuff8++);
            } 
        }
    }
}

/**
 * \brief Reads data from the NandFlash chip into the provided buffer.
 * \param nand  Pointer to a RawNandFlash instance.
 * \param buffer  Buffer where the data will be stored.
 * \param size  Number of bytes that will be read
 */
static void ReadData(
    const struct RawNandFlash *raw,
    uint8_t *buffer,
    uint32_t size)
{
    uint16_t i;
    if (NandFlashIsDmaActived())
    {
        /* Check the data bus width of the NandFlash */
        if (NandFlashModel_GetDataBusWidth(MODEL(raw)) == 16) 
        {
            size = (size + 1)>> 1;
            NandFlashDmaTransferNand2Ram( (uint32_t)buffer, size );
        }
        else 
        {
            NandFlashDmaTransferNand2Ram( (uint32_t)buffer, size );
        }
    }
    else
    {
        /* Check the data bus width of the NandFlash */
        if (NandFlashModel_GetDataBusWidth(MODEL(raw)) == 16) 
        {
            uint16_t *pbuff16 = (uint16_t *)((void *)buffer);
            volatile uint16_t * pDataAddress16 = (volatile uint16_t *) raw->dataAddress;
            size = (size + 1)>> 1;
            for(i = size; i != 0; i--)
            {
                *(pbuff16++) = *pDataAddress16 ;
            }
        }
        else 
        {
            uint8_t *pbuff8 = buffer; 
            volatile uint8_t * pDataAddress8 = (volatile uint8_t *) raw->dataAddress;
            for(i = size; i != 0; i--)
            {
                *(pbuff8++) = *pDataAddress8;
            }
        }
    }
}

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

    /* Start erase */
    ENABLE_CE(raw);
    WRITE_COMMAND(raw, COMMAND_ERASE_1);
    WriteRowAddress(raw, rowAddress);
    WRITE_COMMAND(raw, COMMAND_ERASE_2);

    WaitReady(raw);
#if !defined (OP_BOOTSTRAP_on)
    if (!IsOperationComplete(raw)) {
        TRACE_ERROR(
                 "EraseBlock: Could not erase block %d.\n\r",
                 block);
        error = NandCommon_ERROR_CANNOTERASE;
    }
#endif
    DISABLE_CE(raw);
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
    uint8_t hasSmallBlocks = NandFlashModel_HasSmallBlocks(MODEL(raw));
    uint32_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));
    uint32_t pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(raw));
    uint32_t colAddress;
    uint32_t rowAddress;
    uint8_t eccStatus;

    assert ( data || spare); /* RawNandFlash_ReadPage: At least one area must be read */
    
    TRACE_DEBUG("RdPg(B#%d:P#%d)\r\n", block, page);

    /* Calculate actual address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;

    /* Start operation */
    ENABLE_CE( raw );

    if ( data ) {
        colAddress = 0;
    }
    else {
        /* to read spare area in sequential access */
        colAddress = pageDataSize;
    }

    /* Use either small blocks or large blocks data area read */
    if ( hasSmallBlocks ) {
        if( colAddress == 0) {
            WRITE_COMMAND( raw, COMMAND_READ_A);
        }
        else if(colAddress == pageDataSize) {
            WRITE_COMMAND( raw, COMMAND_READ_C);
        }
        WriteColumnAddress( raw, colAddress);
        WriteRowAddress( raw, rowAddress);
    }
    else {

        WRITE_COMMAND( raw, COMMAND_READ_1);
        WriteColumnAddress( raw, colAddress);
        WriteRowAddress( raw, rowAddress);
        WRITE_COMMAND( raw, COMMAND_READ_2);
    }

    /* Wait for the nand to be ready */
    WaitReady( raw );

    /* Read data area if needed */
    if ( data ) {
        WRITE_COMMAND(raw, COMMAND_READ_1);
        ReadData(raw, (uint8_t *) data, pageDataSize);

        if ( spare ) {
            ReadData( raw, (uint8_t *) spare, pageSpareSize);
        }
    }
    else {
        /* Read spare area only */
        WRITE_COMMAND( raw, COMMAND_READ_1);
        ReadData( raw, (uint8_t *) spare, pageSpareSize);
    }
    if (NandGetEccStatus() == ECC_INTERNAL)
    {
        /* When internal ECC is enabled, the READ STATUS (70h) command is required after the
           completion of the data transfer to determine whether an uncorrectable read
           error occured. */
        WRITE_COMMAND(raw, COMMAND_STATUS);
        eccStatus = (READ_DATA8(raw) & STATUS_ERROR);
        DISABLE_CE( raw );
        return eccStatus;
    }
    /* Disable CE */
    DISABLE_CE( raw );
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
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
static uint8_t ReadPageWithPmecc(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data)
{
    uint32_t pageDataSize = NandFlashModel_GetPageDataSize( MODEL(raw) );
    uint32_t spareDataSize = NandFlashModel_GetPageSpareSize(MODEL(raw));
    uint32_t colAddress;
    uint32_t rowAddress;
    
    TRACE_DEBUG("RdPg(B#%d:P#%d)\r\n", block, page);

    /* Calculate actual address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages( MODEL(raw)) + page;

    PMECC->PMECC_CTRL = PMECC_CTRL_RST;
    PMECC->PMECC_CTRL = PMECC_CTRL_ENABLE;
    if ((PMECC->PMECC_CFG & PMECC_CFG_SPAREEN) != PMECC_CFG_SPAREEN) {
        PMECC->PMECC_CFG |= PMECC_CFG_AUTO;
    }
    /* Start operation */
    ENABLE_CE( raw );
    if ( data ) {
        colAddress = 0;
    }
    else {
        /* to read spare area in sequential access */
        colAddress = pageDataSize;
    }
    WRITE_COMMAND( raw, COMMAND_READ_1 );
    WriteColumnAddress( raw, colAddress );
    WriteRowAddress( raw, rowAddress );
    WRITE_COMMAND( raw, COMMAND_READ_2 );

    /* Wait for the nand to be ready */
    WaitReady( raw );

    WRITE_COMMAND( raw, COMMAND_READ_1 );
    /* Reset the ECC module*/
    PMECC->PMECC_CTRL |= PMECC_CTRL_RST;
    /* Start a Data Phase */
    PMECC->PMECC_CTRL |= PMECC_CTRL_DATA;

    /* Spare is written here as well since it is more efficient */
    if (PMECC->PMECC_CFG & PMECC_CFG_SPAREEN) 
    {
        /* When the page has been fully retrieved from NAND, the ECC area is read using the user mode by writing one to the
        USER field of the PMECC_CTRL register*/
        PMECC->PMECC_CTRL |= PMECC_CTRL_USER;
        ReadData( raw, (uint8_t *) data, pageDataSize + spareDataSize );
    }
    else
    {
        ReadData( raw, (uint8_t *) data, pageDataSize + (PMECC->PMECC_EADDR + 1) );
    }
    /* Wait until the kernel of the PMECC is not busy */
    while(( PMECC->PMECC_SR) & PMECC_SR_BUSY);
    /* Disable CE */
    DISABLE_CE( raw );
    return 0;
}

static uint8_t WritePage(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t error = 0;
    uint32_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));
    uint32_t spareDataSize = NandFlashModel_GetPageSpareSize(MODEL(raw));
    uint32_t rowAddress;

    //TRACE_DEBUG("WritePage(B#%d:P#%d)\r\n", block, page);
    /* Calculate physical address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;

    /* Start write operation*/
    ENABLE_CE(raw);

    /* Write data area if needed */
    if (data) {

        WRITE_COMMAND(raw, COMMAND_WRITE_1);
        WriteColumnAddress(raw, 0);
        WriteRowAddress(raw, rowAddress);
        WriteData(raw, (uint8_t *) data, pageDataSize);

        /* Spare is written here as well since it is more efficient */
        if (spare) {

            WriteData(raw, (uint8_t *) spare, spareDataSize);
        }
        WRITE_COMMAND(raw, COMMAND_WRITE_2);

        WaitReady(raw);
        if (!IsOperationComplete(raw)) {
            TRACE_ERROR("WritePage: Failed writing data area.\n\r");
            error = NandCommon_ERROR_CANNOTWRITE;
        }
    }

    /* Write spare area alone if needed */
    if (spare && !data) {

        WRITE_COMMAND(raw, COMMAND_WRITE_1);
        WriteColumnAddress(raw, pageDataSize);
        WriteRowAddress(raw, rowAddress);
        WriteData(raw, (uint8_t *) spare, spareDataSize);
        WRITE_COMMAND(raw, COMMAND_WRITE_2);

        WaitReady(raw);
        if (!IsOperationComplete(raw)) {
            TRACE_ERROR("WritePage: Failed writing data area.\n\r");
            error = NandCommon_ERROR_CANNOTWRITE;
        }
    }
    /* Disable chip */
    DISABLE_CE(raw);
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
    void *data)
{
    uint8_t error = 0;
    uint32_t pageDataSize;
    uint32_t spareDataSize;
    uint32_t rowAddress;
    uint32_t eccStartaddr;
    uint32_t bytesNumberPerSector;
    uint32_t sectorNumber;
    uint32_t sectorIndex;
    uint32_t byteNumber;
    uint8_t *pmecc[8];
    uint8_t eccTable[NAND_MAX_PMECCSIZE];
    PmeccDescriptor *pPmeccDescriptor;
    uint8_t nbSectorsPerPage;

    TRACE_DEBUG("WritePage(B#%d:P#%d) with PMECC\r\n", block, page);
    pPmeccDescriptor = PMECC_GetCurrentPmeccDescriptor();
    pageDataSize = NandFlashModel_GetPageDataSize(MODEL(raw));
    spareDataSize = NandFlashModel_GetPageSpareSize(MODEL(raw));
       
    switch ( pPmeccDescriptor->pageSize )
    {
        case PMECC_CFG_PAGESIZE_PAGESIZE_1SEC:
            nbSectorsPerPage = 1;
            break;
        case PMECC_CFG_PAGESIZE_PAGESIZE_2SEC:
            nbSectorsPerPage = 2;
            break;
        case PMECC_CFG_PAGESIZE_PAGESIZE_4SEC:
            nbSectorsPerPage = 4;
            break;
        case PMECC_CFG_PAGESIZE_PAGESIZE_8SEC:
            nbSectorsPerPage = 8;
            break;
        default :
            nbSectorsPerPage = 1;
            break;
    }
    PMECC->PMECC_CTRL = PMECC_CTRL_RST;
    PMECC->PMECC_CTRL = PMECC_CTRL_ENABLE;

    pmecc[0] = (uint8_t*)(&PMECC->PMECC_ECC[0]);
    pmecc[1] = (uint8_t*)(&PMECC->PMECC_ECC[1]);
    pmecc[2] = (uint8_t*)(&PMECC->PMECC_ECC[2]);
    pmecc[3] = (uint8_t*)(&PMECC->PMECC_ECC[3]);
    pmecc[4] = (uint8_t*)(&PMECC->PMECC_ECC[4]);
    pmecc[5] = (uint8_t*)(&PMECC->PMECC_ECC[5]);
    pmecc[6] = (uint8_t*)(&PMECC->PMECC_ECC[6]);
    pmecc[7] = (uint8_t*)(&PMECC->PMECC_ECC[7]);

    /* Calculate physical address of the page */
    rowAddress = block * NandFlashModel_GetBlockSizeInPages(MODEL(raw)) + page;
    eccStartaddr = pageDataSize + PMECC->PMECC_SADDR;
    PMECC->PMECC_CFG |= PMECC_CFG_NANDWR;

    /* Start write operation*/
    ENABLE_CE(raw);
    /* Write data area if needed */
    if (data) {
        WRITE_COMMAND(raw, COMMAND_WRITE_1);
        WriteColumnAddress(raw, 0);
        WriteRowAddress(raw, rowAddress);
        /* Start a Data Phase */
        PMECC->PMECC_CTRL |= PMECC_CTRL_DATA;
        /* Spare is written here as well since it is more efficient */
        if (PMECC->PMECC_CFG & PMECC_CFG_SPAREEN) 
        {
            /* When the SPAREEN field of the PMECC_CFG register is set to one, 
            the spare area of the page is encoded with the stream of data of the last sector of the page */
            PMECC->PMECC_CTRL |= PMECC_CTRL_USER;
            WriteData(raw, (uint8_t *) data, pageDataSize + spareDataSize);
        }
        else
        {
            /* When the SPAREEN field of PMECC_CFG is set to zero the spare area is not encoded with the stream of data.*/
            WriteData(raw, (uint8_t *) data, pageDataSize);
        }
        WRITE_COMMAND(raw, COMMAND_RANDOM_IN);
        WriteColumnAddress(raw, eccStartaddr);
        /* Wait until the kernel of the PMECC is not busy */
        while((PMECC->PMECC_SR) & PMECC_SR_BUSY);

        bytesNumberPerSector = (pPmeccDescriptor->eccSizeByte) / nbSectorsPerPage;
        sectorNumber = 1 << ((pPmeccDescriptor->pageSize >> 8) & 0x3);

        if (isNandTrimffs() && page >= NandGetTrimPage()) {
            /* This behaviour was found to fix both UBI and JFFS2 images written to
              cleanly erased NAND partitions*/
            for(sectorIndex = 0; sectorIndex < sectorNumber; sectorIndex++)
            {
                for(byteNumber = 0; byteNumber < bytesNumberPerSector; byteNumber++)
                {
                    eccTable[sectorIndex * bytesNumberPerSector + byteNumber] = 0xFF;
                }
            }
        }    
        else 
        {
            /* Read all ECC registers */
            for(sectorIndex = 0; sectorIndex < sectorNumber; sectorIndex++)
            {
                for(byteNumber = 0; byteNumber < bytesNumberPerSector; byteNumber++)
                
                {
                    eccTable[sectorIndex * bytesNumberPerSector + byteNumber] = pmecc[sectorIndex][byteNumber];
                }
            }
        }
        WriteData(raw, (uint8_t *) eccTable, sectorNumber * bytesNumberPerSector);
        WRITE_COMMAND(raw, COMMAND_WRITE_2);
        WaitReady(raw);
        if (!IsOperationComplete(raw)) {
            TRACE_ERROR("WritePage: Failed writing data area.\n\r");
            error = NandCommon_ERROR_CANNOTWRITE;
        }
    }
    /* Disable chip */
    DISABLE_CE(raw);
    PMECC->PMECC_CFG &= ~PMECC_CFG_NANDWR;
    return error;
}

/**
 * \brief Copies the data in a page of the NandFlash device to an other page on that
 * same chip. Both pages must have be even or odd; it is not possible to copy
 * and even page to an odd page and vice-versa.
 * NandCommon_ERROR code.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param sourceBlock  Source block number.
 * \param sourcePage  Source page number inside the source block.
 * \param destBlock  Destination block number.
 * \param destPage  Destination page number inside the destination block.
 * \return 0 if the operation is successful; otherwise returns error message.
*/

static uint8_t CopyPage(
    const struct RawNandFlash *raw,
    uint16_t sourceBlock,
    uint16_t sourcePage,
    uint16_t destBlock,
    uint16_t destPage)
{
    uint16_t numPages = NandFlashModel_GetBlockSizeInPages(MODEL(raw));
    uint32_t sourceRow = sourceBlock * numPages + sourcePage;
    uint32_t destRow = destBlock * numPages + destPage;
    uint8_t error = 0;
    
    assert((sourcePage & 1) == (destPage & 1)); /* CopyPage: Source and destination page must have the same parity*/
    TRACE_DEBUG("CopyPage(B#%d:P#%d -> B#%d:P#%d)\n\r",  sourceBlock, sourcePage, destBlock, destPage);

    /* Use the copy-back facility if available */
    if (NandFlashModel_SupportsCopyBack(MODEL(raw))) {

        /* Start operation */
        ENABLE_CE(raw);

        /* Start copy-back read */
        WRITE_COMMAND(raw, COMMAND_COPYBACK_READ_1);
        WriteColumnAddress(raw, 0);
        WriteRowAddress(raw, sourceRow);
        WRITE_COMMAND(raw, COMMAND_COPYBACK_READ_2);
        WaitReady(raw);

        /* Start copy-back write */
        WRITE_COMMAND(raw, COMMAND_COPYBACK_PROGRAM_1);
        WriteColumnAddress(raw, 0);
        WriteRowAddress(raw, destRow);
        WRITE_COMMAND(raw, COMMAND_COPYBACK_PROGRAM_2);
        WaitReady(raw);

        /* Check status */
        if (!IsOperationComplete(raw)) {
            TRACE_ERROR("CopyPage: Failed to copy page.\n\r");
            error = NandCommon_ERROR_CANNOTCOPY;
        }

        /* Finish operation */
        DISABLE_CE(raw);
    }
    else {

        /* Software copy */
        uint8_t data[NandCommon_MAXPAGEDATASIZE];
        uint8_t spare[NandCommon_MAXPAGESPARESIZE];
        if (RawNandFlash_ReadPage(raw, sourceBlock, sourcePage, data, spare)) {

            TRACE_ERROR("CopyPage: Failed to read page to copy\n\r");
            error = NandCommon_ERROR_CANNOTREAD;
        }
        else if (RawNandFlash_WritePage(raw, destBlock, destPage, data, spare)) {

            TRACE_ERROR("CopyPage: Failed to write dest. page\n\r");
            error = NandCommon_ERROR_CANNOTWRITE;
        }
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

    ENABLE_CE(raw);
    WRITE_COMMAND16(raw, COMMAND_RESET);
    WaitReady(raw);
    DISABLE_CE(raw);
}

/**
 * \brief Reads and returns the identifiers of a NandFlash chip.
 * \param raw  Pointer to a RawNandFlash instance.
 * \return id1|(id2<<8)|(id3<<16)|(id4<<24)
*/

uint32_t RawNandFlash_ReadId(const struct RawNandFlash *raw)
{
    uint32_t chipId;
    uint32_t chipId2;
    TRACE_DEBUG("RawNandFlash_ReadId()\n\r");

    ENABLE_CE(raw);
    //WRITE_COMMAND16(raw, COMMAND_READID);
    WRITE_COMMAND(raw, COMMAND_READID); 
    WRITE_ADDRESS(raw, 0);
    chipId  = READ_DATA8(raw);
    chipId |= READ_DATA8(raw) << 8;
    chipId |= READ_DATA8(raw) << 16;
    chipId |= READ_DATA8(raw) << 24;
    chipId2  = READ_DATA8(raw);
    DISABLE_CE(raw);
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
    #if !defined(OP_BOOTSTRAP_on)
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
    #else
    return EraseBlock(raw, block);
    #endif
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
    if (spare) 
    {
        return ReadPage( raw, block, page, 0, spare);
    }
    if ( PMECC_GetCurrentPmeccDescriptor() )
    {
        return ReadPageWithPmecc( raw, block, page, data);
    }
    else 
    {
        return ReadPage( raw, block, page, data, spare);
    }
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
    uint8_t numTries = NUMWRITETRIES;

    TRACE_DEBUG("RawNandFlash_WritePage(B#%d:P#%d)\r\n", block, page);
    if ( PMECC_GetCurrentPmeccDescriptor() )
    {
        while ( numTries > 0 ) 
        {
            if ( !WritePageWithPmecc(raw, block, page, data )) {
                return 0;
            }
            numTries--;
        }
    }
    else 
    {
        while ( numTries > 0 ) 
        {
            if ( !WritePage(raw, block, page, data, spare )) {
                return 0;
            }
            numTries--;
        }
    }
    //TRACE_ERROR ( "RawNandFlash_WritePage: Failed to write page after %d tries\n\r", NUMWRITETRIES);
    return NandCommon_ERROR_BADBLOCK;
}

/**
 * \brief Copy the data in a page of the NandFlash device to an other page on that
 * same chip. Both pages must have be even or odd; it is not possible to copy
 * and even page to an odd page and vice-versa. Several retries are attempted
 * if errors are encountered.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param sourceBlock  Source block number.
 * \param sourcePage  Source page number inside the source block.
 * \param destBlock  Destination block number.
 * \param destPage  Destination page number inside the destination block.
 * \return 0 if the operation is successful; otherwise returns
 * NandCommon_ERROR_BADBLOCK indicating that the destination block is bad.
*/
uint8_t RawNandFlash_CopyPage(
    const struct RawNandFlash *raw,
    uint16_t sourceBlock,
    uint16_t sourcePage,
    uint16_t destBlock,
    uint16_t destPage)
{
    uint8_t numTries = NUMCOPYTRIES;

    TRACE_DEBUG("RawNandFlash_CopyPage(B#%d:P#%d -> B#%d:P#%d)\n\r",
              sourceBlock, sourcePage, destBlock, destPage);

    while (numTries) {

        if (!CopyPage(raw, sourceBlock, sourcePage, destBlock, destPage)) {

            return 0;
        }
        numTries--;
    }

    TRACE_ERROR("RawNandFlash_CopyPage: Failed to copy page after %d tries\n\r", NUMCOPYTRIES);
    return NandCommon_ERROR_BADBLOCK;
}

/**
 * \brief Copies the data of one whole block of a NandFlash device to another block.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param sourceBlock  Source block number.
 * \param destBlock  Destination block number.
 * \return 0 if successful; otherwise returns NandCommon_ERROR_BADBLOCK.
*/
uint8_t RawNandFlash_CopyBlock(
    const struct RawNandFlash *raw,
    uint16_t sourceBlock,
    uint16_t destBlock)
{
    uint16_t numPages = NandFlashModel_GetBlockSizeInPages(MODEL(raw));
    uint32_t i;

    assert (sourceBlock != destBlock );  /*RawNandFlash_CopyBlock: Source block must be different from dest block */
    TRACE_DEBUG("RawNandFlash_CopyBlock(B#%d->B#%d)\n\r",
              sourceBlock, destBlock);

    /* Copy all pages */
    for (i=0; i < numPages; i++) {

        if (RawNandFlash_CopyPage(raw, sourceBlock, i, destBlock, i)) {

            TRACE_ERROR("RawNandFlash_CopyBlock: Failed to copy page %lu\n\r", i);
            return NandCommon_ERROR_BADBLOCK;
        }
    }

    return 0;
}

