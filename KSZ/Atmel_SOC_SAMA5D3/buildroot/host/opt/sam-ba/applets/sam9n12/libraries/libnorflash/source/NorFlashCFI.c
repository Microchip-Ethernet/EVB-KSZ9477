/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <board.h>
#include <libnorflash.h>
#include <string.h>
extern const struct NorFlashOperations amdOperations;
extern const struct NorFlashOperations intelOperations;
/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
#define DUMP_CFI

/*----------------------------------------------------------------------------
 *        Internal functions
 *----------------------------------------------------------------------------*/

/**
 * \brief  Dump the Common Flash Interface Definition Table.
 * \param pNorFlashCFI  Pointer to an NorFlashCFI instance.
 */
static void NorFlash_CFI_DumpConfigruation(struct NorFlashCFI *pNorFlashCFI)
{
    uint8_t i;
    
    TRACE_INFO("Common Flash Interface Definition Table\n\r");
    TRACE_INFO("Addr. Data   Description \n\r");
    TRACE_INFO("0x10  %04Xh  Query Unique ASCII string\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.queryUniqueString[0]);
    TRACE_INFO("0x11  %04Xh  \n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.queryUniqueString[1]);
    TRACE_INFO("0x12  %04Xh  \n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.queryUniqueString[2]);
    TRACE_INFO("0x13  %04Xh  Primary OEM Command Set\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.primaryCode);
    TRACE_INFO("0x15  %04Xh  Address for Primary Extended Table\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.primaryAddr);
    TRACE_INFO("0x17  %04Xh  Alternate OEM Command Set\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.alternateCode);
    TRACE_INFO("0x19  %04Xh  Address for Alternate OEM Extended Table\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.alternateAddr);
    TRACE_INFO("0x1B  %04Xh  VCC min write/erase\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.minVcc);
    TRACE_INFO("0x1C  %04Xh  VCC max write/erase\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.maxVcc);
    TRACE_INFO("0x1D  %04Xh  VPP min voltage\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.minVpp);
    TRACE_INFO("0x1E  %04Xh  VPP max voltage\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.maxVpp);
    TRACE_INFO("0x1F  %04Xh  Typical timeout per single word write\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.minTimeOutWrite);
    TRACE_INFO("0x20  %04Xh  Typical timeout for Min. size buffer write\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.minTimeOutBuffer);
    TRACE_INFO("0x21  %04Xh  Typical timeout per individual block erase\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.minTimeOutBlockErase);
    TRACE_INFO("0x22  %04Xh  Typical timeout for full chip erase\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.minTimeOutChipErase);
    TRACE_INFO("0x23  %04Xh  Max. timeout for word write\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.maxTimeOutWrite);
    TRACE_INFO("0x24  %04Xh  Max. timeout for buffer write\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.maxTimeOutBuffer);
    TRACE_INFO("0x25  %04Xh  Max. timeout per individual block erase\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.maxTimeOutBlockErase);
    TRACE_INFO("0x26  %04Xh  Max. timeout for full chip erase\n\r",
    pNorFlashCFI->norFlashCfiQueryInfo.maxTimeOutChipErase);
    
    TRACE_INFO("0x27  %04Xh  Device Size = 2N byte\n\r",
    pNorFlashCFI->norFlashCfiDeviceGeometry.deviceSize);
    TRACE_INFO("0x28  %04Xh  Flash Device Interface description\n\r",
    pNorFlashCFI->norFlashCfiDeviceGeometry.deviceInterface);
    TRACE_INFO("0x2A  %04Xh  Max. number of byte in multi-byte write\n\r",
    pNorFlashCFI->norFlashCfiDeviceGeometry.numMultiWrite);
    TRACE_INFO("0x2C  %04Xh  Number of Erase Block Regions within device\n\r",
    pNorFlashCFI->norFlashCfiDeviceGeometry.numEraseRegion);
    for(i = 0; i < pNorFlashCFI->norFlashCfiDeviceGeometry.numEraseRegion; i++) {
        TRACE_INFO("0x%2X  %04Xh  Number of Erase Blocks of identical size within region %x \n\r",
            0x2D + i * 4, pNorFlashCFI->norFlashCfiDeviceGeometry.eraseRegionInfo[i].Y, i );
        TRACE_INFO("0x%2X  %04Xh  (z) times 256 bytes within region %x \n\r",
            0x2E + i * 4, pNorFlashCFI->norFlashCfiDeviceGeometry.eraseRegionInfo[i].Z, i );
    }
}


/*----------------------------------------------------------------------------
 *        Export functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Returns the numbers of block in all Norflash regions.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 */
uint32_t NorFlash_GetDeviceNumOfBlocks(
    struct NorFlashInfo *pNorFlashInfo)
{
    uint8_t i;
    uint32_t blocks = 0;
    uint16_t numBlockRegion;
    
    numBlockRegion = pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.numEraseRegion;
   
    for (i = 0; i < numBlockRegion; i++) {
        blocks += (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i]).Y + 1;
    }
    return blocks;
}

/**
 * \brief Returns the minimun block size in all Norflash regions.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 */
uint32_t NorFlash_GetDeviceMinBlockSize(
    struct NorFlashInfo *pNorFlashInfo)
{
    uint8_t i;
    uint16_t numBlockRegion;
    unsigned long size ;
    numBlockRegion = pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.numEraseRegion;
    
    size = (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[0].Z) * 256;
    
    for (i = 1; i < numBlockRegion; i++) {
        if (size > (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i].Z) * 256) {
            size = (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i].Z) * 256 ;
        }
    }
    return size;
}

/**
 * \brief Returns the maximun block size in all Norflash regions.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 */
uint32_t NorFlash_GetDeviceMaxBlockSize(
    struct NorFlashInfo *pNorFlashInfo)
{
    uint8_t i;
    uint16_t numBlockRegion;
    unsigned long size ;
    numBlockRegion = pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.numEraseRegion;
    
    size = (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[0].Z) * 256;
    
    for (i = 1; i < numBlockRegion; i++) {
        if (size < (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i].Z) * 256) {
            size = (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i].Z) * 256 ;
        }
    }
    return size;
}

/**
 * \brief Returns the block size in giving block number.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 * \param sector  Sector number.
 */
uint32_t NorFlash_GetDeviceBlockSize(
    struct NorFlashInfo *pNorFlashInfo,
    uint32_t sector)
{
    uint16_t i;
    uint16_t j;
    uint16_t numBlockRegion,numBlockPerRegion;
    uint32_t block = 0;
    
    numBlockRegion = pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.numEraseRegion;
    for (i = 0; i < numBlockRegion; i++) {
        numBlockPerRegion = (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i]).Y + 1;
        for (j = 0; j < numBlockPerRegion; j++) {
            if (block == sector) {
                return (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i].Z) * 256 ;
            }
            block++;
        }
    }
    return 0;
}

/**
 * \brief Returns secort number on specified memory offset.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 * \param memoryOffset  Memory offset.
 */
uint16_t NorFlash_GetDeviceSectorInRegion(
    struct NorFlashInfo *pNorFlashInfo,
    uint32_t memoryOffset)
{
    uint16_t numBlockRegion,numBlockPerRegion;
    uint16_t sectorId = 0;
    uint32_t size = 0;
    uint8_t done = 0;
    uint16_t i , j;
    
    numBlockRegion = pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.numEraseRegion;
    
    for (i = 0; i < numBlockRegion; i++) {
        numBlockPerRegion = (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i]).Y + 1;
        for (j = 0; j < numBlockPerRegion; j++) {
            size+= (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i].Z) * 256 ;
            if(size > memoryOffset) {
                done = 1;
                break;
            }
            sectorId++;
        }
        if (done) break;
    }
    
    return sectorId;
}

/**
 * \brief Returns start address of specified sector number.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 * \param sector  Sector number.
 */
uint32_t NorFlash_GetDeviceSectorAddress(
    struct NorFlashInfo *pNorFlashInfo,
    uint32_t sector)
{
    uint16_t numBlockRegion,numBlockPerRegion;
    uint16_t sectorId = 0;
    uint32_t address = 0;
    uint8_t done = 0;
    uint16_t i , j;
    
    numBlockRegion = pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.numEraseRegion;
    for (i = 0; i < numBlockRegion; i++) {
        numBlockPerRegion = (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i]).Y + 1;
        for (j = 0; j < numBlockPerRegion; j++) {
            if (sector == sectorId) {
                done = 1;
                break;
            }
            address+= (pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i].Z) * 256 ;
            sectorId++;
        }
        if (done) break;
    }
    
    return address;
}

/**
 * \brief Convert address to byte addressing.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 * \Param offset Address offset
 */
uint32_t NorFlash_GetByteAddress(
   struct NorFlashInfo *pNorFlashInfo, uint32_t offset)
{
    return (offset * pNorFlashInfo-> deviceChipWidth);
}

/**
 * \brief Convert address to byte addressing and return the address in chip.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 * \Param offset Address offset
 */
uint32_t NorFlash_GetByteAddressInChip(
   struct NorFlashInfo *pNorFlashInfo, uint32_t offset)
{
    return (pNorFlashInfo->baseAddress + (offset * pNorFlashInfo-> deviceChipWidth));
}


/**
 * \brief Returns the address in chip.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 * \Param offset Address offset
  */
uint32_t NorFlash_GetAddressInChip(struct NorFlashInfo *pNorFlashInfo, uint32_t offset)
{
    return (pNorFlashInfo->baseAddress + offset);
}

/**
 * \brief Returns bus width in bits of giving device.
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 */
uint8_t NorFlash_GetDataBusWidth( struct NorFlashInfo *pNorFlashInfo)
{
    return (pNorFlashInfo->deviceChipWidth * 8);
}
    
/**
 * \brief Returns the size of the whole device in bytes 
 * \param pNorFlashInfo  Pointer to a NorFlashInfo instance.
 */
unsigned long  NorFlash_GetDeviceSizeInBytes(
   struct NorFlashInfo *pNorFlashInfo)
{
    return ((unsigned long) 2 << ((pNorFlashInfo->cfiDescription.norFlashCfiDeviceGeometry.deviceSize) - 1));
}

/**
 * \brief Looks for query struct in Norflash common flash interface.
 * If found, the model variable is filled with the correct values.
 * This function returns 0 if a matching model has been found; otherwise it
 * \return NorCommon_ERROR_UNKNOWNMODEL.
 */ 
uint8_t NorFlash_CFI_Detect(
    struct NorFlash *pNorFlash, 
    uint8_t hardwareBusWidth)
{
    
    uint8_t i;
    uint8_t pCfi[256];
    //uint8_t *pCfi = (uint8_t*)(&(pNorFlash->norFlashInfo.cfiDescription));
    uint32_t address;
    pNorFlash->norFlashInfo.cfiCompatible = 0;
    pNorFlash->norFlashInfo.deviceChipWidth = hardwareBusWidth;
    address = CFI_QUERY_OFFSET;
    for(i = 0; i< sizeof(struct NorFlashInfo) ; i++){
        WriteCommand(8, NorFlash_GetByteAddressInChip(&(pNorFlash->norFlashInfo), CFI_QUERY_ADDRESS), CFI_QUERY_COMMAND);
        ReadRawData(8, NorFlash_GetByteAddressInChip(&(pNorFlash->norFlashInfo), address), &pCfi[i]);
        address++;
    }
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.queryUniqueString[0] = pCfi[0];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.queryUniqueString[1] = pCfi[1];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.queryUniqueString[2] = pCfi[2];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.primaryCode = pCfi[4]<<8 | pCfi[3];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.primaryAddr = pCfi[6]<<8 | pCfi[5];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.alternateCode = pCfi[8]<<8 | pCfi[7];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.alternateAddr = pCfi[10]<<8 | pCfi[9];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.minVcc = pCfi[11];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.maxVcc = pCfi[12];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.minVpp = pCfi[13];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.maxVpp = pCfi[14];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.minTimeOutWrite = pCfi[15];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.minTimeOutBuffer = pCfi[16];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.minTimeOutBlockErase = pCfi[17];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.minTimeOutChipErase = pCfi[18];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.maxTimeOutWrite = pCfi[19];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.maxTimeOutBuffer = pCfi[20];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.maxTimeOutBlockErase = pCfi[21];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.maxTimeOutChipErase = pCfi[22];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiDeviceGeometry.deviceSize =  pCfi[23];

    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiDeviceGeometry.deviceInterface =  pCfi[25]<<8 | pCfi[24];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiDeviceGeometry.numMultiWrite = pCfi[27]<<8 | pCfi[26];
    pNorFlash->norFlashInfo.cfiDescription.norFlashCfiDeviceGeometry.numEraseRegion = pCfi[28];
    for (i = 0; i< 16*4; i+=4) {
        pNorFlash->norFlashInfo.cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i>>2].Y = pCfi[30+i]<<8 | pCfi[29+i];
        pNorFlash->norFlashInfo.cfiDescription.norFlashCfiDeviceGeometry.eraseRegionInfo[i>>2].Z = pCfi[32+i]<<8 | pCfi[31+i];
    }
    // Check the query-unique ASCII string "QRY"
    if( (pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.queryUniqueString[0] != 'Q' )
        || (pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.queryUniqueString[1] != 'R') 
        || (pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.queryUniqueString[2] != 'Y') ) {
        return NorCommon_ERROR_UNKNOWNMODEL;
    }
    
#ifdef DUMP_CFI
    NorFlash_CFI_DumpConfigruation(&(pNorFlash->norFlashInfo.cfiDescription));
#endif

    if (pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.primaryCode == CMD_SET_AMD) {
        pNorFlash->cmdSet = CMD_SET_AMD;
    }
    else if ((pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.primaryCode == CMD_SET_INTEL_EXT)
     || (pNorFlash->norFlashInfo.cfiDescription.norFlashCfiQueryInfo.primaryCode == CMD_SET_INTEL)) {
        pNorFlash->cmdSet = CMD_SET_INTEL;
    }
    else {
        return NorCommon_ERROR_UNKNOWNMODEL;
    }
    
    pNorFlash->norFlashInfo.cfiCompatible = 1;
    NORFLASH_Reset(pNorFlash, 0);
    return 0;
}

