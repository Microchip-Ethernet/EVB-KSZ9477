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

#ifndef NORFLASHCFI_H
#define NORFLASHCFI_H

//------------------------------------------------------------------------------
//         Local constants
//------------------------------------------------------------------------------

#define CFI_MAX_ERASE_REGION    4

/// Common flash interface query command.
#define CFI_QUERY_COMMAND     0x98
#define CFI_QUERY_ADDRESS     0x55
#define CFI_QUERY_OFFSET      0x10

//------------------------------------------------------------------------------
//        Exported defination
//------------------------------------------------------------------------------
/// Vendor command set control interface ID code .
#define CMD_SET_NULL          0x0000
#define CMD_SET_INTEL_EXT     0x0001 
#define CMD_SET_AMD           0x0002
#define CMD_SET_INTEL         0x0003
#define CMD_SET_AMD_EXT       0x0004
#define CMD_SET_MISUBISHI     0x0100
#define CMD_SET_MISUBISHI_EXT 0x0101
#define CMD_SET_SST           0x0102


/// Indicates the maximum region for norflash device.
#define NORFLASH_MAXNUMRIGONS 4
/// Indicates the NorFlash uses an 8-bit address bus.
#define FLASH_CHIP_WIDTH_8BITS  0x01
/// Indicates the NorFlash uses an 16-bit address bus.
#define FLASH_CHIP_WIDTH_16BITS 0x02
/// Indicates the NorFlash uses an 32-bit address bus.
#define FLASH_CHIP_WIDTH_32BITS 0x04
/// Indicates the NorFlash uses an 64-bit address bus.
#define FLASH_CHIP_WIDTH_64BITS 0x08

//------------------------------------------------------------------------------
//        Local Type
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Describes a Norflash CFI query system interface information.
//------------------------------------------------------------------------------
#ifdef __ICCARM__          // IAR
#pragma pack(1)            // IAR
#define __attribute__(...) // IAR
#endif                     // IAR

struct NorFlashCfiQueryInfo {

    /// Query Unique String "QRY".
    unsigned char queryUniqueString[3];
    /// Primary vendor command set and control interface ID .
    unsigned short primaryCode;
    /// Address for primary extended query table.
    unsigned short primaryAddr;
    /// Alternate vendor command set and control interface ID .
    unsigned short alternateCode;
    /// Address for alternate extended query table.
    unsigned short alternateAddr;
    /// Vcc logic supply minimum write/erase voltage.
    unsigned char minVcc;
    /// Vcc logic supply maximum write/erase voltage.
    unsigned char maxVcc;
    /// Vpp logic supply minimum write/erase voltage.
    unsigned char minVpp;
    /// Vpp logic supply maximum write/erase voltage.
    unsigned char maxVpp;
    /// Timeout per single write (2<<n) in microsecond.
    unsigned char minTimeOutWrite;
    /// Timeout for minimum-size buffer write (2<<n) in microsecond.
    unsigned char minTimeOutBuffer;
    /// Timeout for block erase (2<<n) in microsecond.
    unsigned char minTimeOutBlockErase;
    /// Timeout for chip erase (2<<n) in microsecond.
    unsigned char minTimeOutChipErase;
    /// Maximum timeout per write (2<<n) in microsecond.
    unsigned char maxTimeOutWrite;
    /// Maximum timeout for buffer write (2<<n) in microsecond.
    unsigned char maxTimeOutBuffer;
    /// Maximum timeout for block erase (2<<n) in microsecond.
    unsigned char maxTimeOutBlockErase;
    /// Maximum timeout for chip erase (2<<n) in microsecond.
    unsigned char maxTimeOutChipErase;
}__attribute__ ((packed));

//------------------------------------------------------------------------------
/// Describes a Norflash CFI Erase block Region information.
//------------------------------------------------------------------------------
struct EraseRegionInfo {
    /// Number of erase blocks within the region.
    unsigned short Y;
    /// Size within the region.
    unsigned short Z;
}__attribute__ ((packed));

//------------------------------------------------------------------------------
/// Describes a Norflash CFI critical details of device geometry.
//------------------------------------------------------------------------------
struct NorFlashCfiDeviceGeometry {

    /// Size of Device (2<<n) in number of bytes.
    unsigned char deviceSize;
    /// Flash device interface description.
    unsigned short deviceInterface;
    /// Maximum number of bytes in multi-byte write (2<<n).
    unsigned short numMultiWrite;
    /// Number of erase block regions.
    unsigned char numEraseRegion;
    /// Erase block Region information.
    struct EraseRegionInfo eraseRegionInfo[16];
}__attribute__ ((packed));

#ifdef __ICCARM__          // IAR
#pragma pack()             // IAR
#endif                     // IAR

//------------------------------------------------------------------------------
/// Describes a Norflash Common Flash Interface information.
//------------------------------------------------------------------------------
struct NorFlashCFI {
    ///CFI query system interface information.
    struct NorFlashCfiQueryInfo norFlashCfiQueryInfo;
    /// CFI critical details of device geometry.
    struct NorFlashCfiDeviceGeometry norFlashCfiDeviceGeometry;
};

//------------------------------------------------------------------------------
/// Describes a particular model of NandFlash device.
//------------------------------------------------------------------------------
struct NorFlashInfo {
	/// Base address.
    unsigned int baseAddress;
    /// Address bus using giving by CFI detection.
    /// It can not retrieve info directly from  the NorFlashCFI, it depend on hardware connection.
    unsigned char deviceChipWidth;
    /// Indicate the decive CFI is compatible
    unsigned char cfiCompatible;
    /// Norflash Common Flash Interface information.
    struct NorFlashCFI  cfiDescription;
};


//------------------------------------------------------------------------------
/// Describes a particular model of NandFlash device.
//------------------------------------------------------------------------------

struct NorFlash {
   const struct NorFlashOperations *pOperations;
   struct NorFlashInfo norFlashInfo;
};

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------


extern unsigned char NorFlash_CFI_Detect(
    struct NorFlash *norFlash, 
    unsigned char hardwareBusWidth);
    

unsigned int NorFlash_GetDeviceNumOfBlocks( struct NorFlashInfo *pNorFlashInfo);

unsigned int NorFlash_GetDeviceMinBlockSize(struct NorFlashInfo *pNorFlashInfo);

unsigned int NorFlash_GetDeviceMaxBlockSize(
    struct NorFlashInfo *pNorFlashInfo);
    
unsigned int NorFlash_GetDeviceBlockSize(
    struct NorFlashInfo *pNorFlashInfo,
    unsigned int sector);

unsigned short NorFlash_GetDeviceSectorInRegion(
    struct NorFlashInfo *pNorFlashInfo,
    unsigned int memoryOffset);

unsigned int NorFlash_GetDeviceSectorAddress(
    struct NorFlashInfo *pNorFlashInfo,
    unsigned int sector);

unsigned int NorFlash_GetByteAddress(
   struct NorFlashInfo *pNorFlashInfo, unsigned int offset);

unsigned int NorFlash_GetByteAddressInChip(
   struct NorFlashInfo *pNorFlashInfo, unsigned int offset);

unsigned int NorFlash_GetAddressInChip(
   struct NorFlashInfo *pNorFlashInfo, unsigned int offset);
					 
unsigned char NorFlash_GetDataBusWidth(
   struct NorFlashInfo *pNorFlashInfo);

unsigned long  NorFlash_GetDeviceSizeInBytes(
   struct NorFlashInfo *pNorFlashInfo);

#endif //#ifndef NORFLASHCFI_H

