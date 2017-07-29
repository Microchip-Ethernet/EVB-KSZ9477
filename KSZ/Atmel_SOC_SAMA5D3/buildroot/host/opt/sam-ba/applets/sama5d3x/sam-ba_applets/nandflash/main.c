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

/** \page nandflash_applet Nand Flash Applet
 * Nand Flash applet is a small piece of software running on the target board, embedding the
 * NAND flash read, write, and erase algorithms etc. \n
 *
 * SAM-BA host controls commands and data transfering, it loads Nand flash applet and
 * executes it to implement NAND flash memory operation.
 * An applet consists of:
 * <ul>
 * <li>A mailbox which can share information between the applet and SAM-BA host.</li>
 * <li>Implement APPLET_CMD_INIT command to initializes NAND device, PMECC and reports memory size,
 * buffer address, size of buffer and current pmecc parameter header configuration through the mailbox.</li>
 * Note: Tries to detect NAND Flash device connected to EBI CS3, with data lines connected to D0-D7, 
 * then on NAND Flash connected to D16-D23. 
 * <li>A NAND flash programming algorithm works for APPLET_CMD_PMECC_HEADER command, it configure pemcc parameter 
 * which is made of 52 times the same 32-bit word.
 * <li>A NAND flash programming algorithm works for APPLET_CMD_WRITE command, it erases and programs
 * NAND flash data in buffer at the address which specified in mailbox.</li>
 * <li>Erase all algorithm is necessary to erasing entire flash memory. </li>
 * </ul>
 *
 * It reports command status and written/read size (for write/read algorithm) in mailbox to
 * SAM-BA host while the command is achieved.
 *
 *
*/
/*@{*/
/*@}*/


/**
 * \file
 *
 * Implementation of Nand flash applet for SAM-BA 2.12 (sama5d3x only).
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "../common/applet.h"
#include <board.h>
#include <libnandflash.h>
#include <libpmecc.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
#define ECCHEADER_USEPMECC   1
#define ECCHEADER_SECTORS    2
#define ECCHEADER_SPARE      3
#define ECCHEADER_ECCBIT     4
#define ECCHEADER_SECTORSIZE 5
#define ECCHEADER_ECCOFFSET  6
#define ECCHEADER_ALL        7

#define ECC_ENABLE_SOFT      0
#define ECC_DISABLE_SOFT     1
#define ECC_ENABLE_PMECC     2
#define ECC_DISABLE_PMECC    3
#define ECC_ENABLE_INTEECC   4

/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/

/** \brief Structure for storing parameters for each command that can be
 * performed by the applet.*/

struct _Mailbox {

    /** Command send to the monitor to be executed. */
    uint32_t command;
    /** Returned status, updated at the end of the monitor execution. */
    uint32_t status;

    /** Input Arguments in the argument area */
    union {

        /** Input arguments for the Init command. */
        struct {

            /** Communication link used. */
            uint32_t comType;

            /** Trace level. */
            uint32_t traceLevel;

        } inputInit;

        /** Output arguments for the Init command. */
        struct {

            /** Memory size. */
            uint32_t memorySize;
            /** Buffer address. */
            uint32_t bufferAddress;
            /** Buffer size. */
            uint32_t bufferSize;
            /** Current pmecc parameter header configuration. */
            uint32_t pmeccParamHeader;

        } outputInit;

        /** Input arguments for the switchEccMode command. */
        struct {
            /** Ecc mode to be switched*/
            uint32_t eccMode;
            /** Ecc Offset for software ecc. */
            uint32_t sweccOffset;

        } inputEccMode;

        /** Output arguments for the switchEccMode command. */
        /* NONE */

        /** Input arguments for the trimffs command. */
        struct {
            /** Ecc mode to be switched*/
            uint32_t trim;

        } inputTrimMode;

        /** Output arguments for the TrimFfs command. */
        /* NONE */

        /** Input arguments for the pmeccHeader command. */
        struct {
            /** pmeccParam index*/
            uint32_t pmeccParamIndex;
            /** Pmecc value. */
            uint32_t pmeccParamValue;

        } inputPmeccHeader;

        /** Output arguments for the pmeccHeader command. */
        struct {
           /** Current pmecc parameter header configuration. */
            uint32_t pmeccParamHeader;
        } outputPmeccHeader;

        /** Input arguments for the Write command. */
        struct {

            /** Buffer address. */
            uint32_t bufferAddr;
            /** Buffer size. */
            uint32_t bufferSize;
            /** Memory offset. */
            uint32_t memoryOffset;

        } inputWrite;

        /** Output arguments for the Write command. */
        struct {

            /** Bytes written. */
            uint32_t bytesWritten;

        } outputWrite;

        /** Input arguments for the Read command. */
        struct {

            /** Buffer address. */
            uint32_t bufferAddr;
            /** Buffer size. */
            uint32_t bufferSize;
            /** Memory offset. */
            uint32_t memoryOffset;

        } inputRead;

        /** Output arguments for the Read command. */
        struct {

            /** Bytes read. */
            uint32_t bytesRead;

        } outputRead;

        /** Input arguments for the Full Erase command. */
        struct {

            /** Type of Erase to perform */
            uint32_t eraseType;

        } inputFullErase;

        /** Input arguments for the Batch Erase command. */
        struct {
            /** Type of Erase to perform */
            uint32_t eraseType;
            /** Batch number. */
            uint32_t batch;
        } inputBatchErase;

         /** Input arguments for the Block Erase command. */
        struct {

            /** Memory start offset to be erased. */
            uint32_t memoryOffsetStart;
            /** Memory end offset to be erased. */
            uint32_t memoryOffsetEnd;
        } inputBlocksErase;
        
        /** Output arguments for the Full Erase command. */
        /* NONE */

        /** Output arguments for the Batch Erase command. */
        struct {
            /** next eraseing batch. */
            uint32_t nextBatch;
        } outputBatchErase;
        /** Input arguments for the List Bad Blocks command. */
        /* NONE  */

        /** Output arguments for the List Bad Blocks command. */
        struct {

            /** Number of bad blocks found */
            uint32_t nbBadBlocks;
            /** Address of the buffer containing bad block list */
            uint32_t bufferAddress;

        } outputListBadBlocks;

        /** Input arguments for the Tag Block command. */
        struct {

            /** ID of the block to tag */
            uint32_t blockId;
            /** Data to be written in the bad block marker word */
            uint32_t tag;

        } inputTagBlock;

        /** Output arguments for the Tag Block command. */
        /* NONE */

    } argument;
};

/* Here is the structure to insert at beginning of NAND flash. That will inform RomCode about how to configure NAND reading & PMECC.*/
/* This header may have been written by the flash programmer at the beginning of Nandflash
   and contains Flash parameters required to configure correctly the PMECC.
   It has been written .
   It must be duplicated 49 times and we get the value for each field by
   applying a "majority test" algorithm.
   In case it is not present, we will try to detect flash structure with ONFI paramaters. */
typedef struct _nfParamHeader_t {
    uint32_t usePmecc          : 1;
    uint32_t nbSectorPerPage   : 3;   // 0, 1,2,3
    uint32_t spareSize         : 9;   // size of spare zone in bytes
    uint32_t eccBitReq         : 3;   // 0,1,2,3,4
    uint32_t sectorSize        : 2;   // 0 for 512 bytes, 1 for 1024 bytes per sector, other val for future use
    uint32_t eccOffset         : 9;   // offset of the first ecc byte in spare zone
    uint32_t reserved          : 1;
    uint32_t key               : 4;

} nfParamHeader_t;

/*----------------------------------------------------------------------------
 *         Global variables
 *----------------------------------------------------------------------------*/
/** End of program space (code + data). */
extern uint32_t _end;


/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/
/** Nandflash memory size. */
static uint32_t memSize;
/** Number of blocks in nandflash. */
static uint32_t numBlocks;
/** Size of one block in the nandflash, in bytes. */
static uint32_t blockSize;
/** Size of the data area of in the nandflash, in bytes.*/
static uint32_t pageSize = 0;
/** Size of the spare area of in the nandflash, in bytes.*/
static uint32_t spareSize;
/** Number of page per block */
static uint32_t numPagesPerBlock;
/** Nandflash bus width */
static uint8_t nfBusWidth = 8;

/** Pins used to access to nandflash. */
static const Pin pPinsNf[] = {PINS_NANDFLASH};
/** Nandflash device structure. */
static struct SkipBlockNandFlash skipBlockNf;

/** Nandflash device structure. */
static struct NandFlashModel modelListfromOnfi;

/** Spare area placement scheme for 4096 byte pages */
static struct NandSpareScheme nandScheme4096;

/** Global DMA driver instance for all DMA transfers in application. */
static sDmad dmad;
/** Global PMECC instance. */
static PmeccDescriptor pmeccDesc;
/** Global OnfiPageParameter instance. */
static OnfiPageParam OnfiPageParameter;
/** Address for transferring command bytes to the nandflash. */
static uint32_t cmdBytesAddr = BOARD_NF_COMMAND_ADDR;
/** Address for transferring address bytes to the nandflash. */
static uint32_t addrBytesAddr = BOARD_NF_ADDRESS_ADDR;
/** Address for transferring data bytes to the nandflash. */
static uint32_t dataBytesAddr = BOARD_NF_DATA_ADDR;
/** Nandflash chip enable pin. */
static const Pin nfCePin = {0, 0, 0, 0, 0};
/** Nandflash ready/busy pin. */
//static const Pin nfRbPin = BOARD_NF_RB_PIN;
static const Pin nfRbPin = {0, 0, 0, 0, 0};
/** Ecc type  0:ECC_NO, 1:ECC_SOFT, 2:ECC_PMECC 3:ECC_INTERNAL */
static uint32_t eccType = SMC_ECC_NOECC;
/** Ecc Correctability */
static uint8_t eccCorrectability = 2;
/** Sector size 0 for 512, 1 for 1024 */
static uint8_t sectorSize;
/** offset of the first ecc byte in spare zone */
static uint16_t eccOffset;
/** ParamHeader instance for NAND boot */
static nfParamHeader_t bootNfParamHeader[52];
/* ParamHeader */
nfParamHeader_t currentPmeccHeader, backupPmeccHeader;
/** Communication type with SAM-BA GUI. */
static uint32_t comType;
/** Number of bits of ECC correction */
static uint8_t onfiEccCorrectability = 0xFF;
/*----------------------------------------------------------------------------
 *         Definiation
 *----------------------------------------------------------------------------*/
/** Polling or interrupt mode */
#define POLLING_MODE    1
#define ERASE_BATCH     8
uint32_t isValidPmeccParam (nfParamHeader_t* pPmeccHeader);

/*----------------------------------------------------------------------------
 *         local functions
 *----------------------------------------------------------------------------*/
 /**
 * \brief Check is the pmecc parameter header is valid 
  \return 1 if the pmecc parameter header is valid; otherwise returns 0
 */
uint32_t isValidPmeccParam (nfParamHeader_t* pPmeccHeader)
{
   /* something for PMECC algo */
    uint32_t mm, nErrorCorrctionBits, nSectors, eccSizeByte, eccEndAddr,nbSectorsPerPage;
    /* Programmable Number of Sectors per page*/
    uint8_t sectorSizePerPage [4] = {1, 2, 4, 8};
    /* Number of ECC bits required */
    uint8_t eccBitReq2TT [5] = {2, 4, 8, 12, 24};
    if(pPmeccHeader->nbSectorPerPage > 3) {
        TRACE_INFO("\nbSectorPerPage Unknown\n\r");
        return 0;
    };
    if(pPmeccHeader->sectorSize > 1) {
        TRACE_INFO("Invalid sectorSize\n\r");
        return 0;
    }
    if(pPmeccHeader->spareSize != spareSize) {
        TRACE_INFO("Invalid spareSize\n\r");
        return 0;
    }
    if(pPmeccHeader->eccBitReq > 4) {
        TRACE_INFO("Invalid eccBitReq\n\r");
        return 0;
    }
    if(pPmeccHeader->key != 0x0C) { 
        TRACE_INFO("Invalid key\n\r");
        return 0;
    }
    nbSectorsPerPage = (pPmeccHeader->sectorSize == 0) ? pageSize/512 : pageSize/1024;
    if(nbSectorsPerPage != (power(2,pPmeccHeader->nbSectorPerPage))) {
        TRACE_INFO("Invalid nbSectorsPerPage %d, %d\n\r", 
                    (unsigned int)nbSectorsPerPage, (unsigned int)(pPmeccHeader->nbSectorPerPage + 1));
        return 0;
    }
    mm = (pPmeccHeader->sectorSize == 0)? 13: 14;
    nErrorCorrctionBits = eccBitReq2TT[pPmeccHeader->eccBitReq];

    if (nErrorCorrctionBits < onfiEccCorrectability && onfiEccCorrectability!= 0xFF) {
        TRACE_INFO("Warning: number of ECC bit correction asked is less than requested by the Nandflash Manufacturer (from ONFI params) (%d vs %d)\n\r"
                    ,(unsigned int)nErrorCorrctionBits, (unsigned int)onfiEccCorrectability);
    }

    nSectors = sectorSizePerPage[pPmeccHeader->nbSectorPerPage];
    if( nSectors > nbSectorsPerPage ) {
        TRACE_INFO("Invalid nSectors\n\r");
        return 0;
    }
    if ((( mm * nErrorCorrctionBits ) % 8 ) == 0)
    {
        eccSizeByte = ((mm * nErrorCorrctionBits ) / 8) * nSectors;
    }
    else 
    {
        eccSizeByte = (((mm * nErrorCorrctionBits ) / 8 ) + 1 ) * nSectors;
    }
    eccEndAddr = pPmeccHeader->eccOffset + eccSizeByte;
    if (pPmeccHeader->eccOffset > spareSize) {
        TRACE_INFO("Invalid eccOffset\n\r");
        return 0;
    }                
    if ( eccEndAddr > spareSize) {
        TRACE_INFO("Invalid eccEndAddr\n\r");
        return 0;
    }
    return 1;
}

/**
 * \brief Return numbers of sectors have been erased before.
 * \param pageSize  Size of page in byte.
 * \param sectorSize  Size of sector Size.
 * \param buf  Buffer containing the data area.
 * \return return numbers of sectors erased before.
*/
static uint32_t drop_ffs( uint8_t * buf)
{
    uint32_t l, i;
    for (i = blockSize - 1; i >= 0; i--) {
        if (buf[i] != 0xFF)
            break;
    }
    /* The resulting length must be aligned to the minimum ECC page size */
    l = i + 1;
    l = (l + pageSize - 1) / pageSize;
    
    return l;
}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/
/**
 * \brief  Applet main entry. This function decodes received command and executes it.
 *
 * \param argc  always 1
 * \param argv  Address of the argument area..
 */
int main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;
    uint32_t bufferSize, bufferAddr, memoryOffset, bytesToWrite;
    uint32_t bytesRead = 0;
    uint32_t nbBadBlocks = 0;
    uint32_t nbBlocks = 0;
    uint8_t onficompatible = 0;
    /* Temporary buffer used for non block aligned read / write  */
    uint32_t tempBufferAddr;
    uint16_t block, page, offset, i;
    /* Index in source buffer during buffer copy */
    uint32_t offsetInSourceBuff;
    /* Index in destination buffer during buffer copy */
    uint32_t offsetInTargetBuff;
    /* Errors returned by SkipNandFlash functions */
    uint8_t error = 0;
    /* current pmecc parameter header value */
    uint32_t currentPmeccHeaderValue;
    /* Index and value of pmecc command  */
    uint32_t nIndex, nValue;
    /* Number of ECC bits required */
    uint8_t eccBitReq2TT [5] = {2, 4, 8, 12, 24};
    /* Ecc mode to be swtich */
    uint32_t eccMode;
    uint32_t trimPage;
    /* Disable watchdog */
    WDT_Disable( WDT ) ;

    /* ---------------------------------------------------------- */
    /* INIT:                                                      */
    /* ---------------------------------------------------------- */
    if (pMailbox->command == APPLET_CMD_INIT) {
        /* Save communication link type */
        comType = pMailbox->argument.inputInit.comType;

#if (DYN_TRACES == 1)
        dwTraceLevel = pMailbox->argument.inputInit.traceLevel;
#endif
        TRACE_INFO("-- NandFlash SAM-BA applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);
        TRACE_INFO("INIT command\n\r");

        /* Configure SMC for Nandflash accesses (done each time applet is launched because of old ROM codes) */
        TRACE_INFO("BOARD_ConfigureNandFlash\n\r");
        BOARD_ConfigureNandFlash(nfBusWidth);
        Smc_OpConfigure(0);
        /* Device model */
        /* Tries to detect NAND Flash device connected to EBI CS3*/
        if (!NandEbiDetect()) {
            pMailbox->status = APPLET_DEV_UNKNOWN;
            TRACE_INFO("\tDevice Unknown\n\r");
            goto exit;
        }
        memset(&skipBlockNf, 0, sizeof(skipBlockNf));
        if (NandGetOnfiPageParam (&OnfiPageParameter)){
            TRACE_INFO("\tOpen NAND Flash Interface (ONFI)-compliant\n\r");
            modelListfromOnfi.deviceId = OnfiPageParameter.manufacturerId;
            modelListfromOnfi.options = OnfiPageParameter.onfiBusWidth? NandFlashModel_DATABUS16:NandFlashModel_DATABUS8;
            modelListfromOnfi.pageSizeInBytes = OnfiPageParameter.onfiPageSize;
            modelListfromOnfi.spareSizeInBytes = OnfiPageParameter.onfiSpareSize;
            modelListfromOnfi.deviceSizeInMegaBytes = (( OnfiPageParameter.onfiPagesPerBlock \
                                                     * OnfiPageParameter.onfiBlocksPerLun )/1024)
                                                     * OnfiPageParameter.onfiPageSize /1024;
            modelListfromOnfi.blockSizeInKBytes = (OnfiPageParameter.onfiPagesPerBlock \
                                                 * OnfiPageParameter.onfiPageSize )/ 1024;
            onfiEccCorrectability = OnfiPageParameter.onfiEccCorrectability;
            if (onfiEccCorrectability != 0xFF) eccCorrectability = onfiEccCorrectability;
            switch (OnfiPageParameter.onfiPageSize) {
                case 256: modelListfromOnfi.scheme = &nandSpareScheme256; break;
                case 512: modelListfromOnfi.scheme = &nandSpareScheme512; break;
                case 2048: modelListfromOnfi.scheme = &nandSpareScheme2048; break;
                case 4096: modelListfromOnfi.scheme = &nandSpareScheme4096; break;
                case 8192: modelListfromOnfi.scheme = &nandSpareScheme8192; break;
            }
            onficompatible = 1;
        }
        NandDisableInternalEcc();
        if (SkipBlockNandFlash_Initialize(&skipBlockNf,
                                         (onficompatible ? &modelListfromOnfi: 0),
                                         cmdBytesAddr,
                                         addrBytesAddr,
                                         dataBytesAddr,
                                         nfCePin,
                                         nfRbPin)) {
            pMailbox->status = APPLET_DEV_UNKNOWN;
            pMailbox->argument.outputInit.bufferSize = 0;
            pMailbox->argument.outputInit.memorySize = 0;
            TRACE_INFO("\tDevice Unknown\n\r");
        }
        else 
        {
            /* Check the data bus width of the NandFlash */
            nfBusWidth = NandFlashModel_GetDataBusWidth((struct NandFlashModel *)&skipBlockNf);
            /* Reconfigure bus width */
            if ( nfBusWidth != 8) {
                BOARD_ConfigureNandFlash(nfBusWidth);
            }
            TRACE_INFO("\tNandflash driver initialized\n\r");
            pMailbox->argument.outputInit.bufferAddress = (uint32_t) &_end;
            /* Get device parameters */
            memSize = NandFlashModel_GetDeviceSizeInBytes(&skipBlockNf.ecc.raw.model);
            if (NandFlashModel_GetDeviceSizeInMBytes(&skipBlockNf.ecc.raw.model) >= 0x1000) {
                memSize = 0xFFFFFFFF - (0xFFFFFFFF % pageSize);
            }
            blockSize = NandFlashModel_GetBlockSizeInBytes(&skipBlockNf.ecc.raw.model);
            numBlocks = NandFlashModel_GetDeviceSizeInBlocks(&skipBlockNf.ecc.raw.model);
            pageSize = NandFlashModel_GetPageDataSize(&skipBlockNf.ecc.raw.model);
            spareSize = NandFlashModel_GetPageSpareSize(&skipBlockNf.ecc.raw.model);
            numPagesPerBlock = NandFlashModel_GetBlockSizeInPages(&skipBlockNf.ecc.raw.model);


            pMailbox->status = APPLET_SUCCESS;
            pMailbox->argument.outputInit.bufferSize = blockSize;
            pMailbox->argument.outputInit.memorySize = memSize;
            pMailbox->argument.outputInit.pmeccParamHeader = 0;
            TRACE_INFO("\tpageSize : 0x%x blockSize : 0x%x blockNb : 0x%x spareSize :0x%x numPagesPerBlock :0x%x\n\r",
                        (unsigned int)pageSize, (unsigned int)blockSize, (unsigned int)numBlocks,(unsigned int)spareSize,(unsigned int)numPagesPerBlock);
        }
        /* By default, we use pmecc, except MICRON MLC nand with internal ECC controller */
        eccOffset = 2;
        /* By defaut, 2 error bit correction, eccOffset = 2 */
        PMECC_Initialize(&pmeccDesc, 0, eccCorrectability, pageSize, spareSize, eccOffset, 0);
        TRACE_INFO("\tNandflash PMECC initialized\n\r");
        DMAD_Initialize( &dmad, POLLING_MODE ); 
        if ( NandFlashConfigureDmaChannels( &dmad )) {
            pMailbox->status =APPLET_DEV_UNKNOWN;
            goto exit;
        }
        /* Initialize current pmecc parameter header, This 32-bit word is configured below */
        currentPmeccHeader.usePmecc = 1;
        currentPmeccHeader.nbSectorPerPage = pmeccDesc.pageSize >> 8;
        currentPmeccHeader.spareSize = spareSize;
        currentPmeccHeader.eccBitReq = pmeccDesc.errBitNbrCapability;
        currentPmeccHeader.sectorSize = pmeccDesc.sectorSize>> 4;
        currentPmeccHeader.eccOffset = pmeccDesc.eccStartAddr;
        currentPmeccHeader.reserved = 0;
        currentPmeccHeader.key = 12;
        memcpy(&backupPmeccHeader, &currentPmeccHeader, sizeof(nfParamHeader_t));
        memcpy(&currentPmeccHeaderValue, &currentPmeccHeader, sizeof(nfParamHeader_t));
        pMailbox->argument.outputInit.pmeccParamHeader = currentPmeccHeaderValue;
        /* The Boot Program reads the first page without ECC check, to determine if the NAND parameter 
           header is present. The header is made of 52 times the same 32-bit word (for redundancy
           reasons) which must contain NAND and PMECC parameters used to correctly perform the read of the rest 
           of the data in the NAND. */
        for (i = 0; i< 52; i++) memcpy(&bootNfParamHeader[i], &currentPmeccHeader, sizeof(nfParamHeader_t));
        setSmcOpEccType(SMC_ECC_PMECC);
        pMailbox->status = APPLET_SUCCESS;
    }
    /* ---------------------------------------------------------- */
    /* APPLET_CMD_TRIMFSS                                        */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_TRIMFFS) 
    {
        TRACE_INFO("TRIMFFS command\n\r");
        eccType = getSmcOpEccType();
        if (eccType != SMC_ECC_PMECC)
        {
            pMailbox->status = APPLET_PMECC_CONFIG;
            TRACE_INFO("\tOnly support for pmecc enabled.\n\r");
            goto exit;
        }
        
        NandSetTrimffs(pMailbox->argument.inputTrimMode.trim);
        TRACE_INFO("Current TRIMFFS is %d\n\r", isNandTrimffs());
        pMailbox->status = APPLET_SUCCESS;
    }
    /* ---------------------------------------------------------- */
    /* APPLET_CMD_PMECC_HEADER                                    */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_PMECC_HEADER) 
    {
        TRACE_INFO("PMECC Header configuration command\n\r");
        eccType = getSmcOpEccType();
        if (eccType != SMC_ECC_PMECC)
        {
            pMailbox->status = APPLET_PMECC_CONFIG;
            TRACE_INFO("\tOnly support for pmecc enabled.\n\r");
            goto exit;
        }
        nIndex = pMailbox->argument.inputPmeccHeader.pmeccParamIndex;
        nValue = pMailbox->argument.inputPmeccHeader.pmeccParamValue;
        memcpy(&backupPmeccHeader, &currentPmeccHeader, sizeof(nfParamHeader_t));
        switch ( nIndex )
        {
            case ECCHEADER_USEPMECC:
                TRACE_INFO("\tConfigure 'usePmecc' to %x.\n\r", (unsigned int)nValue);
                backupPmeccHeader.usePmecc = nValue;
                break;
            case ECCHEADER_SECTORS:
                TRACE_INFO("\tConfigure 'nbSectorPerPage' to %x \n\r", (unsigned int)nValue);
                backupPmeccHeader.nbSectorPerPage = nValue;
                break;
            case ECCHEADER_SPARE:
                TRACE_INFO("\tConfigure 'spareSize' to %x \n\r", (unsigned int)nValue);
                backupPmeccHeader.spareSize = nValue;
                break;
            case ECCHEADER_ECCBIT:
                TRACE_INFO("\tConfigure 'eccBitReq' to [%x, %d-bit ECC] \n\r", (unsigned int)nValue, eccBitReq2TT[nValue]);
                backupPmeccHeader.eccBitReq = nValue;
                break;
            case ECCHEADER_SECTORSIZE:
                TRACE_INFO("\tConfigure 'sectorSize' to  [%x,%d bytes] \n\r", (unsigned int)nValue,
                           ((nValue == 0) ? 512 : 1024));
                backupPmeccHeader.sectorSize = nValue;
                break;
            case ECCHEADER_ECCOFFSET:
                TRACE_INFO("\tConfigure 'eccOffset' to %x.\n\r", (unsigned int)nValue);
                backupPmeccHeader.eccOffset = nValue;
                break;
           case ECCHEADER_ALL:
                TRACE_INFO("\tConfigure paramHeader to %x.\n\r", (unsigned int)nValue);
                memcpy(&backupPmeccHeader, &nValue, sizeof(nfParamHeader_t));
                break;
           default:
               break;
        }
        if (!isValidPmeccParam (&backupPmeccHeader))
        {
            pMailbox->status = APPLET_PMECC_CONFIG;
            TRACE_INFO("\tSome parameter error in pmecc header configuration. \n\r");
            goto exit;
        }
        memcpy(&currentPmeccHeader, &backupPmeccHeader, sizeof(nfParamHeader_t));
        sectorSize = currentPmeccHeader.sectorSize;
        spareSize = currentPmeccHeader.spareSize;
        eccOffset = currentPmeccHeader.eccOffset;
        eccCorrectability = eccBitReq2TT[currentPmeccHeader.eccBitReq];

        /* The header is made of 52 times the same 32-bit word  */
        for (i = 0; i< 52; i++) memcpy(&bootNfParamHeader[i], &currentPmeccHeader, sizeof(nfParamHeader_t));
        if (currentPmeccHeader.usePmecc) {
            TRACE_INFO("\tNandflash PMECC nbSectorPerPage is %d\n\r", (unsigned int)currentPmeccHeader.nbSectorPerPage );
            TRACE_INFO("\tNandflash PMECC spareSize is %d\n\r",(unsigned int)spareSize );
            TRACE_INFO("\tNandflash PMECC eccBitReq is %d\n\r", (unsigned int)eccCorrectability );
            TRACE_INFO("\tNandflash PMECC sectorSize is %d\n\r", (unsigned int)currentPmeccHeader.sectorSize );
            TRACE_INFO("\tNandflash PMECC eccOffset is %d\n\r", (unsigned int)currentPmeccHeader.eccOffset );
            PMECC_Initialize(&pmeccDesc, sectorSize, eccCorrectability, pageSize, spareSize , eccOffset, 0);
        }
        memcpy(&currentPmeccHeaderValue, &currentPmeccHeader, sizeof(nfParamHeader_t));
        pMailbox->argument.outputPmeccHeader.pmeccParamHeader = currentPmeccHeaderValue;
        TRACE_INFO("\tNandflash PMECC currentPmeccHeaderValue is %x\n\r", (unsigned int)currentPmeccHeaderValue );
        pMailbox->status = APPLET_SUCCESS;
    }

    /* ---------------------------------------------------------- */
    /* Switch ECC mode:                                           */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_SWITCH_ECC) {
        eccMode = pMailbox->argument.inputEccMode.eccMode;
        error = 0;
        eccType = getSmcOpEccType();
        switch ( eccMode ) {
            case ECC_ENABLE_SOFT:
                TRACE_INFO("\tEnable software ECC\n\r");
                //if ( eccType != SMC_ECC_NOECC) error = 1;
                break;
            case ECC_DISABLE_SOFT:
                TRACE_INFO("\tDisable software ECC\n\r");
                if ( eccType == SMC_ECC_NOECC) error = 1;
                break;
            case ECC_ENABLE_PMECC:
                TRACE_INFO("\tEnable PMECC\n\r");
                //if ( eccType != SMC_ECC_NOECC) error = 1;
                break;
            case ECC_DISABLE_PMECC:
                TRACE_INFO("\tDisable PMECC\n\r");
                if ( eccType == SMC_ECC_NOECC) error = 1;
                break;
            case ECC_ENABLE_INTEECC:
                TRACE_INFO("\tEnable Micron Nandflash Internal Ecc\n\r");
                //if ( eccType != ECC_NO) error = 1;
                break;
            default:
                error = 1;
                break;
        }
        if ( error) {
            pMailbox->status = APPLET_FAIL;
            TRACE_INFO("\tSome parameter error in switching ecc mode. \n\r");
            goto exit;
        }
        if ( (eccMode == ECC_DISABLE_PMECC) || (eccMode == ECC_ENABLE_SOFT) || (eccMode == ECC_ENABLE_INTEECC)) {
            NandFlashFreeDma();
            PMECC_Disable();
        }
        if ( (eccMode == ECC_DISABLE_SOFT) || (eccMode == ECC_DISABLE_PMECC)) {
            setSmcOpEccType(SMC_ECC_NOECC);
        }
        if ( eccMode == ECC_ENABLE_SOFT) {
            nValue = pMailbox->argument.inputEccMode.sweccOffset;
            setSmcOpEccType(SMC_ECC_SOFTWARE);
        }
        if ( eccMode == ECC_ENABLE_INTEECC) {
           /* Detect if the NAND device have internal ECC controller (some MICRON nand )*/
            if (!NandEnableInternalEcc()) {
                pMailbox->status = APPLET_FAIL;
                TRACE_INFO("\tCan't detect a MICRON Nandflash device with internal ECC!\n\r");
                goto exit;
            }
        }
        if ( eccMode == ECC_ENABLE_PMECC) {
            eccOffset = 2;
            /* By defaut, 2 error bit correction, eccOffset = 2 */
            PMECC_Initialize(&pmeccDesc, 0, eccCorrectability, pageSize, spareSize, eccOffset, 0);
            TRACE_INFO("\tNandflash PMECC initialized\n\r");
            DMAD_Initialize( &dmad, POLLING_MODE ); 
            if ( NandFlashConfigureDmaChannels( &dmad ))
            {
                pMailbox->status =APPLET_DEV_UNKNOWN;
                goto exit;
            }
            /* Initialize current pmecc parameter header, This 32-bit word is configured below */
            currentPmeccHeader.usePmecc = 1;
            currentPmeccHeader.nbSectorPerPage = pmeccDesc.pageSize >> 8;
            currentPmeccHeader.spareSize = spareSize;
            currentPmeccHeader.eccBitReq = pmeccDesc.errBitNbrCapability;
            currentPmeccHeader.sectorSize = pmeccDesc.sectorSize;
            currentPmeccHeader.eccOffset = pmeccDesc.eccStartAddr;
            currentPmeccHeader.reserved = 0;
            currentPmeccHeader.key = 12;
            memcpy(&backupPmeccHeader, &currentPmeccHeader, sizeof(nfParamHeader_t));
            memcpy(&currentPmeccHeaderValue, &currentPmeccHeader, sizeof(nfParamHeader_t));
            pMailbox->argument.outputInit.pmeccParamHeader = currentPmeccHeaderValue;
            /* The Boot Program reads the first page without ECC check, to determine if the NAND parameter 
               header is present. The header is made of 52 times the same 32-bit word (for redundancy
               reasons) which must contain NAND and PMECC parameters used to correctly perform the read of the rest 
                of the data in the NAND. */
            for (i = 0; i< 52; i++) memcpy(&bootNfParamHeader[i], &currentPmeccHeader, sizeof(nfParamHeader_t));
            setSmcOpEccType(SMC_ECC_PMECC);
        }
        if ( eccMode != ECC_ENABLE_PMECC) {
            /* Set usePmecc as 0 in header */
            currentPmeccHeader.usePmecc = 0;
            currentPmeccHeader.nbSectorPerPage = pmeccDesc.pageSize >> 8;
            currentPmeccHeader.spareSize = spareSize;
            currentPmeccHeader.eccBitReq = 0;
            currentPmeccHeader.sectorSize = pmeccDesc.sectorSize;
            currentPmeccHeader.eccOffset = 0;
            currentPmeccHeader.reserved = 0;
            currentPmeccHeader.key = 12;
            memcpy(&backupPmeccHeader, &currentPmeccHeader, sizeof(nfParamHeader_t));
            memcpy(&currentPmeccHeaderValue, &currentPmeccHeader, sizeof(nfParamHeader_t));
            pMailbox->argument.outputPmeccHeader.pmeccParamHeader = currentPmeccHeaderValue;
            /* The Boot Program reads the first page without ECC check, to determine if the NAND parameter 
            header is present. The header is made of 52 times the same 32-bit word (for redundancy
            reasons) which must contain NAND and PMECC parameters used to correctly perform the read of the rest 
            of the data in the NAND. */
            for (i = 0; i< 52; i++) memcpy(&bootNfParamHeader[i], &currentPmeccHeader, sizeof(nfParamHeader_t));
            if ( spareSize > 64) {
                TRACE_INFO(" Configure ecc offset for SW ecc( SpareSIze > 64)");
                if (!NandSpareScheme_build4096(&nandScheme4096, spareSize, nValue)) {
                    modelListfromOnfi.scheme = &nandScheme4096;
                    skipBlockNf.ecc.raw.model = modelListfromOnfi;
                }
            }
        }
        pMailbox->status = APPLET_SUCCESS;
    }

    /* ---------------------------------------------------------- */
    /* WRITE:                                                     */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_WRITE) {
        TRACE_INFO("SEND FILE command\n\r");
        eccType = getSmcOpEccType();
        if (eccType == SMC_ECC_PMECC) {
           PMECC_Initialize(&pmeccDesc, sectorSize, eccCorrectability, pageSize, spareSize , eccOffset, 0);
           TRACE_INFO("Pmecc initialized \n\r");
        } 
        memoryOffset = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr = pMailbox->argument.inputWrite.bufferAddr;
        tempBufferAddr = bufferAddr + blockSize;
        bytesToWrite = pMailbox->argument.inputWrite.bufferSize;

        TRACE_INFO("WRITE arguments : offset 0x%x, buffer at 0x%x, of 0x%x Bytes\n\r",
               (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bytesToWrite);
        
        pMailbox->argument.outputWrite.bytesWritten = 0;

        /* Check word alignment */
        if (memoryOffset % 4) {

            pMailbox->status = APPLET_ALIGN_ERROR;
            goto exit;
        }
       
        /* Retrieve page and block addresses */
        if (NandFlashModel_TranslateAccess(&(skipBlockNf.ecc.raw.model),
                                           memoryOffset,
                                           bytesToWrite,
                                           &block,
                                           &page,
                                           &offset)) {
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }

        TRACE_INFO("WRITE at block 0x%x, page 0x%x, offset 0x%x\n\r", block, page, offset);
        if (page || offset || (bytesToWrite < blockSize)) {
            /* We are not block aligned, retrieve block content to update it */
            memset((uint32_t *)tempBufferAddr, 0xFF, blockSize);
            TRACE_INFO("Retrieve data in block,%d \n\r", (unsigned int)block);
            error = SkipBlockNandFlash_ReadBlock(&skipBlockNf, block, (uint32_t *)tempBufferAddr);
            if (error == NandCommon_ERROR_BADBLOCK) {
                pMailbox->status = APPLET_BAD_BLOCK;
                goto exit;
            }
            if (error) {
                pMailbox->status = APPLET_FAIL;
                goto exit;
            }
            /* Fill retrieved block with data to be programmed */
            offsetInTargetBuff = (page * pageSize) + offset;
            offsetInSourceBuff = 0;
            while ((offsetInTargetBuff < blockSize) && (bytesToWrite > 0)) {
                *(uint32_t *)(tempBufferAddr + offsetInTargetBuff) = *(uint32_t *)(bufferAddr + offsetInSourceBuff);
                offsetInSourceBuff += 4;
                offsetInTargetBuff += 4;
                bytesToWrite -= 4;
            }
            if (isNandTrimffs()) {
                NandSetTrimPage ( blockSize / pageSize );
                trimPage = drop_ffs((uint8_t *)tempBufferAddr);
                NandSetTrimPage((uint16_t)trimPage);
                if (trimPage <= (blockSize/pageSize)) {
                    TRACE_INFO(" -------------------------------------\n\r");
                    TRACE_INFO("TRIM JFSS @ page %d \n\r", (unsigned int)trimPage);
                    TRACE_INFO(" -------------------------------------\n\r");
                }
            }
        }
        else {
            if (isNandTrimffs()) {
                NandSetTrimPage ( blockSize / pageSize );
                if (( offset == 0) && (bytesToWrite == blockSize)) {
                    trimPage = drop_ffs((uint8_t *)bufferAddr);
                    NandSetTrimPage((uint16_t)trimPage);
                    if (trimPage <= (blockSize/pageSize)) {
                        TRACE_INFO(" -------------------------------------\n\r");
                        TRACE_INFO("TRIM JFSS @ page %d \n\r",(unsigned int)trimPage);
                        TRACE_INFO(" -------------------------------------\n\r");
                    }
                }
            }
            /* Write a full and aligned block */
            tempBufferAddr = bufferAddr;
            bytesToWrite = 0;
        }
        /* Erase target block */
        error = SkipBlockNandFlash_EraseBlock(&skipBlockNf, block, NORMAL_ERASE);
        if (error == NandCommon_ERROR_BADBLOCK) {
            pMailbox->status = APPLET_BAD_BLOCK;
            goto exit;
        }
        if (error) {
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }
        /* Write target block */
        error = SkipBlockNandFlash_WriteBlock(&skipBlockNf, block, (uint32_t *)tempBufferAddr);
        if (error == NandCommon_ERROR_BADBLOCK) {
            pMailbox->status = APPLET_BAD_BLOCK;
            goto exit;
        }
        if (error) {
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }
        pMailbox->argument.outputWrite.bytesWritten = pMailbox->argument.inputWrite.bufferSize - bytesToWrite;
        pMailbox->status = APPLET_SUCCESS;
    }

    /* ---------------------------------------------------------- */
    /* READ:                                                      */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_READ) {
        eccType = getSmcOpEccType();
        if (eccType == SMC_ECC_PMECC) { 
            PMECC_Initialize(&pmeccDesc, sectorSize, eccCorrectability, pageSize, spareSize , eccOffset, 0);
        }
        memoryOffset = pMailbox->argument.inputRead.memoryOffset;
        bufferAddr   = pMailbox->argument.inputRead.bufferAddr;
        tempBufferAddr = bufferAddr + blockSize;
        bufferSize   = pMailbox->argument.inputRead.bufferSize;

        TRACE_INFO("READ at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
               (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bufferSize);

        pMailbox->argument.outputRead.bytesRead = 0;

        /* Check word alignment */
        if (memoryOffset % 4) {

            pMailbox->status = APPLET_ALIGN_ERROR;
            goto exit;
        }

        /* Retrieve page and block addresses*/
        if (NandFlashModel_TranslateAccess(&(skipBlockNf.ecc.raw.model),
                                           memoryOffset,
                                           bufferSize,
                                           &block,
                                           &page,
                                           &offset)) {
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }
        
        TRACE_INFO("READ at block 0x%x, page 0x%x, offset in page 0x%x\n\r", 
                    (unsigned int)block, (unsigned int)page, (unsigned int)offset);

        if (page || offset) {
            memset((uint32_t *)tempBufferAddr, 0xFF, blockSize);

            error = SkipBlockNandFlash_ReadBlock(&skipBlockNf, block, (uint32_t *)tempBufferAddr);
            if (error == NandCommon_ERROR_BADBLOCK) {
                pMailbox->status = APPLET_BAD_BLOCK;
                goto exit;
            }
            if (error) {
                pMailbox->status = APPLET_FAIL;
                goto exit;
            }

            /* Fill dest buffer with read data */
            offsetInSourceBuff = (page * pageSize) + offset;
            offsetInTargetBuff = 0;

            while ((offsetInSourceBuff < blockSize)
                    && (offsetInTargetBuff < blockSize)
                    && (bytesRead < bufferSize)) {

                *(uint32_t *)(bufferAddr + offsetInTargetBuff) = *(uint32_t *)(tempBufferAddr + offsetInSourceBuff);
                offsetInSourceBuff += 4;
                offsetInTargetBuff += 4;
                bytesRead += 4;
            }

            pMailbox->argument.outputRead.bytesRead = bytesRead;
            pMailbox->status = APPLET_SUCCESS;
        }
        else {

            memset((uint32_t *)bufferAddr, 0xFF, blockSize);
                
            error = SkipBlockNandFlash_ReadBlock(&skipBlockNf, block, (uint32_t *)bufferAddr);
            if (error == NandCommon_ERROR_BADBLOCK) {
                pMailbox->status = APPLET_BAD_BLOCK;
                goto exit;
            }
            if (error) {
                pMailbox->status = APPLET_FAIL;
                goto exit;
            }

            pMailbox->argument.outputRead.bytesRead = bufferSize;
            pMailbox->status = APPLET_SUCCESS;
        }
    }

    /* ---------------------------------------------------------- */
    /* SEND BOOT FILE:                                            */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_SENDBOOT) {
        TRACE_INFO("SEND BOOT FILE command\n\r");
        eccType = getSmcOpEccType();
        if (eccType == SMC_ECC_PMECC) { 
            PMECC_Initialize(&pmeccDesc, sectorSize, eccCorrectability, pageSize, spareSize , eccOffset, 0);
        }
        bufferAddr = pMailbox->argument.inputWrite.bufferAddr;
        bytesToWrite = pMailbox->argument.inputWrite.bufferSize;
        tempBufferAddr = bufferAddr + blockSize;
        memset((uint32_t *)tempBufferAddr, 0xFF, blockSize);
        error = SkipBlockNandFlash_EraseBlock(&skipBlockNf, 0, NORMAL_ERASE);
        if (error == NandCommon_ERROR_BADBLOCK) {

            pMailbox->status = APPLET_BAD_BLOCK;
            goto exit;
        }
        if (error) {

            pMailbox->status = APPLET_FAIL;
            goto exit;
        }
        /* The Boot Program reads the first page without ECC check, to determine if the NAND
           parameter header is present. The header is made of 52 times the same 32-bit word (for redundancy
           reasons) which must contain NAND and PMECC parameters used to correctly perform the read of the rest 
           of the data in the NAND.*/

        memcpy((uint32_t *)tempBufferAddr, (uint32_t *)bootNfParamHeader, 52 * 4);
        memcpy((uint32_t *)tempBufferAddr + 52, (uint32_t *)bufferAddr, bytesToWrite);
        /* Write target block */
        error = SkipBlockNandFlash_WriteBlock ( &skipBlockNf, 0, (uint32_t *)tempBufferAddr);
        if (error == NandCommon_ERROR_BADBLOCK) {

            pMailbox->status = APPLET_BAD_BLOCK;
            goto exit;
        }
        if (error) {
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }
        pMailbox->status = APPLET_SUCCESS;
    }
    /* ---------------------------------------------------------- */
    /* FULL ERASE:                                                */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_FULL_ERASE) {

        TRACE_INFO("FULL ERASE command\n\r");
        TRACE_INFO("\tForce erase flag: 0x%x\n\r", (unsigned int)pMailbox->argument.inputFullErase.eraseType);
        for (i = 0; i < numBlocks; i++) {

            /* Erase the page */
            if (SkipBlockNandFlash_EraseBlock(&skipBlockNf, i, pMailbox->argument.inputFullErase.eraseType)) {

                TRACE_INFO("Found block #%d BAD, skip it\n\r", (unsigned int)i);
            }
        }
        TRACE_INFO("Full Erase achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

    /* ---------------------------------------------------------- */
    /* BATCH FULL ERASE:                                          */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_BATCH_ERASE) {

        TRACE_INFO("BATCH ERASE command\n\r");
        block = pMailbox->argument.inputBatchErase.batch * (numBlocks / ERASE_BATCH);

        TRACE_INFO("Erase block from #%d to #%d\n\r", (unsigned int)block,(unsigned int)( block + (numBlocks / ERASE_BATCH)));
        for (i = block ; i < block + (numBlocks / ERASE_BATCH) ; i++) {

            /* Erase the block */
            if (SkipBlockNandFlash_EraseBlock(&skipBlockNf, i, pMailbox->argument.inputBatchErase.eraseType)) {

                TRACE_INFO("Found block #%d BAD, skip it\n\r", (unsigned int)i);
            }
        }

        if ((pMailbox->argument.inputBatchErase.batch + 1) == ERASE_BATCH) {
            TRACE_INFO("Full Erase achieved, erase type is %d\n\r", (unsigned int)pMailbox->argument.inputBatchErase.eraseType);
            pMailbox->argument.outputBatchErase.nextBatch = 0;
        }
        else {
            pMailbox->argument.outputBatchErase.nextBatch =  pMailbox->argument.inputBatchErase.batch + 1;
            TRACE_INFO("Batch Erase achieved\n\r");
        }
        pMailbox->status = APPLET_SUCCESS;
    }

    /* ---------------------------------------------------------- */
    /* ERASE_BLOCKS:                                              */
    /* ---------------------------------------------------------- */

    else if (pMailbox->command == APPLET_CMD_ERASE_BLOCKS) {

        TRACE_INFO("BLOCKS ERASE command\n\r");
        memoryOffset = pMailbox->argument.inputBlocksErase.memoryOffsetStart;
        if ((pMailbox->argument.inputBlocksErase.memoryOffsetEnd > memSize) || (pMailbox->argument.inputBlocksErase.memoryOffsetEnd < memoryOffset) ) {
            TRACE_INFO("Out of memory space\n\r");
            pMailbox->status = APPLET_ERASE_FAIL;
            goto exit;
        }
        nbBlocks = ((pMailbox->argument.inputBlocksErase.memoryOffsetEnd- memoryOffset)/ blockSize) + 1;

        TRACE_INFO("Erase blocks from %d  to %d \n\r",  
                   (unsigned int)(memoryOffset / blockSize), (unsigned int)((memoryOffset / blockSize)+ nbBlocks) );
        /* Erase blocks */
        for (i =  memoryOffset / blockSize; i < memoryOffset / blockSize + nbBlocks ; i++) {
            if (SkipBlockNandFlash_EraseBlock(&skipBlockNf,  i , NORMAL_ERASE)) {
                 TRACE_INFO("Found block #%d BAD, skip it\n\r",  (unsigned int)i);
            }
        }
        TRACE_INFO("Blocks Erase achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
    /* ---------------------------------------------------------- */
    /* LIST BAD BLOCKS:                                           */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_LIST_BAD_BLOCKS) {

        TRACE_INFO("LIST BAD BLOCKS command\n\r");
        nbBadBlocks = 0;
        bufferAddr = (uint32_t) &_end;
        pMailbox->argument.outputListBadBlocks.bufferAddress = bufferAddr;

        for (i = 0; i < numBlocks; i++) {

            /* Erase the page */
            if (SkipBlockNandFlash_CheckBlock(&skipBlockNf, i) == BADBLOCK) {

                nbBadBlocks++;
                *((uint32_t *)bufferAddr) = i;
                bufferAddr += 4;
                TRACE_INFO("Found block #%d BAD\n\r", (unsigned int)i);
            }
        }
        TRACE_INFO("LIST BAD BLOCKS achieved\n\r");
        pMailbox->argument.outputListBadBlocks.nbBadBlocks = nbBadBlocks;
        pMailbox->status = APPLET_SUCCESS;
    }

    /* ---------------------------------------------------------- */
    /* TAG BLOCK:                                                 */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_TAG_BLOCK) {

        TRACE_INFO("TAG BLOCK command\n\r");
        bufferAddr = (uint32_t) &_end;
        block = pMailbox->argument.inputTagBlock.blockId;

        /* To tag the block as good, just erase it without bad block check */
        if ((uint8_t)pMailbox->argument.inputTagBlock.tag == 0xFF)
        {
            if (SkipBlockNandFlash_EraseBlock(&skipBlockNf, block, SCRUB_ERASE)) {

                TRACE_INFO("Cannot erase block %d\n\r", block);
                pMailbox->status = APPLET_FAIL;
                goto exit;
            }
        }
        else {
            for (i = 0; i < 2; i++) {

                /* Start by reading the spare */
                memset((uint8_t *)bufferAddr, 0xFF, pageSize);
                memset((uint8_t *)(bufferAddr+pageSize), 0xFF, NandCommon_MAXSPAREECCBYTES);
                
                TRACE_INFO("Tag to write : 0x%x\n\r", (uint8_t)pMailbox->argument.inputTagBlock.tag);

                NandSpareScheme_WriteBadBlockMarker((struct NandSpareScheme *)(NandFlashModel_GetScheme((struct NandFlashModel *)(&skipBlockNf))),
                                                    (uint8_t *)(bufferAddr+pageSize),
                                                    ((uint8_t)pMailbox->argument.inputTagBlock.tag));
                eccType = getSmcOpEccType();
                setSmcOpEccType(SMC_ECC_NOECC);
                if (RawNandFlash_WritePage((struct RawNandFlash *)(&skipBlockNf), block, i, (uint8_t *)bufferAddr, (uint8_t *)(bufferAddr+pageSize))) {
                    setSmcOpEccType(eccType);
                    TRACE_ERROR("Failed to write spare data of page %d of block %d\n\r", 
                                (unsigned int)i, (unsigned int)block);
                    pMailbox->status = APPLET_FAIL;
                    goto exit;
                }
                setSmcOpEccType(eccType);
            }
        }
        TRACE_INFO("TAG BLOCK achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

exit :
    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of applet (command : %x --- status : %x)\n\r", 
                 (unsigned int)pMailbox->command, (unsigned int)pMailbox->status);
    /* Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);
    /* Send ACK character */
    if (comType == DBGU_COM_TYPE) {
         /* Wait for the transmitter to be ready */
        while ( (DBGU->DBGU_SR & DBGU_SR_TXEMPTY) == 0 ) ;
        /* Send character */
         DBGU->DBGU_THR= 0x06 ;
    }
    return 0;
}

