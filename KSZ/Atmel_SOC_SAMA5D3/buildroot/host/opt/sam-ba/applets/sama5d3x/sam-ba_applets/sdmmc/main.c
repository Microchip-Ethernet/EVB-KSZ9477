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

/**
 * \file
 *
 * Implementation of SDMMC applet for SAM-BA 2.12 (sama5d3x only).
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "../common/applet.h"
#include <board.h>
#include <libsdmmc.h>
#include <string.h>

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

            /** sd port index.*/
            uint32_t mciIdx;
        } inputInit;

        /** Output arguments for the Init command. */
        struct {

            /** Memory size. */
            uint32_t memorySize;
            /** Buffer address. */
            uint32_t bufferAddress;
            /** Buffer size. */
            uint32_t bufferSize;

        } outputInit;

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
        /* NONE */

        /** Input arguments for the Batch Erase command. */
        /* NONE */

         /** Input arguments for the Block Erase command. */
        /* NONE */
        
        /** Output arguments for the Full Erase command. */
        /* NONE */

        /** Output arguments for the Batch Erase command. */
        /* NONE */

        /** Input arguments for the List Bad Blocks command. */
        /* NONE  */

    } argument;
};


/*----------------------------------------------------------------------------
 *         Global variables
 *----------------------------------------------------------------------------*/
/** End of program space (code + data). */
extern uint32_t _end;

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

/** DMA driver instance */
static sDmad dmaDrv;

/** MCI driver instance. */
static sMcid mciDrv[BOARD_NUM_MCI];

/** SDCard driver instance. */
static sSdCard sdDrv[BOARD_NUM_MCI];

/** Current selected MCI interface */
static uint8_t bMciID = 0;

/** SD card pins instance. */
static const Pin pinsSd[] = {BOARD_MCI0_PINS, BOARD_MCI1_PINS};

/** SD card detection pin instance. */
static const Pin pinsCd[] = {BOARD_MCI0_PIN_CD,BOARD_MCI1_PIN_CD};

/** SD card Power control pin instance. */
static const Pin pinsPu[] = {BOARD_MCI0_PIN_POWER,BOARD_MCI1_PIN_POWER};

/** Buffer for test data blocks */
static uint8_t tempBlockBuffer[SDMMC_BLOCK_SIZE ];

static uint8_t comType;
/*----------------------------------------------------------------------------
 *         Local macros
 *----------------------------------------------------------------------------*/

#define POLLING_MODE    1

/** \macro SDT_ReadFun
 * Function used for SD card test reading.
 * \param pSd  Pointer to a SD card driver instance.
 * \param address  Address of the block to read.
 * \param nbBlocks Number of blocks to be read.
 * \param pData    Data buffer whose size is at least the block size.
 */
#define MMCT_ReadFun(pSd, blk, nbBlk, pData) SD_ReadBlocks(pSd, blk, pData, nbBlk)

/** \macro SDT_WriteFun
 * Function used for SD card test writing.
 * \param pSd  Pointer to a SD card driver instance.
 * \param address  Address of the block to read.
 * \param nbBlocks Number of blocks to be read.
 * \param pData    Data buffer whose size is at least the block size.
 */
#define MMCT_WriteFun(pSd, blk, nbBlk, pData)  SD_WriteBlocks(pSd, blk, pData, nbBlk)
/*----------------------------------------------------------------------------
 *         local functions
 *----------------------------------------------------------------------------*/

/**
 * Display: Dump Splitting row
 */
static void DumpSeperator(void)
{
    printf("\n\r==========================================\n\r");
}


/**
 * Dump card registers
 * \param iMci Controller number.
 */
static void DumpCardInfo(uint8_t iMci)
{
    sSdCard *pSd = &sdDrv[iMci];

    if (SD_GetCardType(pSd) & CARD_TYPE_bmSDIO)
    {
        SDIO_DumpCardInformation(pSd);
    }

    if (SD_GetCardType(pSd) & CARD_TYPE_bmSDMMC)
    {
        SD_DumpCID(pSd->CID);
        //SD_DumpCSD(pSd->CSD);
        //SD_DumpExtCSD(pSd->EXT);
    }
}


/**
 * Run tests on the inserted card
 * \param iMci Controller number.
 */
static uint8_t CardInit(uint8_t iMci)
{
    sSdCard *pSd = &sdDrv[iMci];
    uint8_t error;
    uint8_t retry = 2;

    DumpSeperator();

    while(retry --)
    {
        error = SD_Init(pSd);
        if (error == SDMMC_OK) break;
    }
    if (error)
    {
        printf("-E- SD/MMC card initialization failed: %d\n\r", error);
        return 0;
    }
    printf("-I- SD/MMC card initialization successful\n\r");
    if (SD_GetCardType(pSd) & CARD_TYPE_bmSDMMC)
    {
        printf("-I- MEM Card OK, size: %d MB", (int)SD_GetTotalSizeKB(pSd)/1000);
        printf(", %d * %dB\n\r", (int)SD_GetNumberBlocks(pSd), (int)SD_GetBlockSize(pSd));
    }
    if (SD_GetCardType(pSd) & CARD_TYPE_bmSDIO)
    {
        printf("-I- IO Card Detected OK\n\r");
    }

    DumpCardInfo(iMci);
    return 1;
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
    uint8_t i;
    uint32_t memoryOffset, bufferAddr, bytesToWrite,bytesToRead;
    uint32_t block, blockOffset, bufOffset;
    uint32_t error;
    sSdCard *pSd;

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
        TRACE_INFO("-- SDMMC SAM-BA applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);
        TRACE_INFO("INIT command\n\r");

        TRACE_INFO("Pin configration\n\r");
        /* Configure SDcard pins */
        PIO_Configure(pinsSd, PIO_LISTSIZE(pinsSd));
        /* Configure SD card detection */
        PIO_Configure(pinsCd, PIO_LISTSIZE(pinsCd));
        /* Configure SDcard power pins */
        PIO_Configure(pinsPu, PIO_LISTSIZE(pinsPu));

        bMciID = pMailbox->argument.inputInit.mciIdx;
        if (PIO_Get(&pinsCd[bMciID])){
            pMailbox->status = APPLET_DEV_UNKNOWN;
            printf("-E- Can't connect device\n\r");
            goto exit;
        }

        /* Initialize the DMA driver */
        DMAD_Initialize(&dmaDrv, POLLING_MODE);
        /* Initialize the HSMCI driver */
        MCID_Init(&mciDrv[0], HSMCI0, ID_HSMCI0, BOARD_MCK, &dmaDrv, POLLING_MODE ) ;
        MCID_Init(&mciDrv[1], HSMCI1, ID_HSMCI1, BOARD_MCK, &dmaDrv, POLLING_MODE ) ;
            /* Initialize SD driver */
        for (i = 0; i < BOARD_NUM_MCI; i ++)
        {
            SDD_InitializeSdmmcMode(&sdDrv[i], &mciDrv[i], 0);
        }
        if( !CardInit(bMciID)){
            pMailbox->status = APPLET_DEV_UNKNOWN;
            printf("-E- Can't connect device\n\r");
            goto exit;
        }
        pMailbox->argument.outputInit.bufferAddress = (uint32_t) &_end;
        pMailbox->argument.outputInit.bufferSize = 0x20000;
        pMailbox->argument.outputInit.memorySize = (unsigned int)SD_CSD_TOTAL_SIZE((&sdDrv[bMciID])->CSD);
        pMailbox->status = APPLET_SUCCESS;
    }
   
  
    /* ---------------------------------------------------------- */
    /* WRITE:                                                     */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_WRITE) {
        TRACE_INFO("SEND FILE command\n\r");
        pSd = &sdDrv[bMciID];
        memoryOffset = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr   = pMailbox->argument.inputWrite.bufferAddr;
        bytesToWrite = pMailbox->argument.inputWrite.bufferSize;
        block = memoryOffset / SDMMC_BLOCK_SIZE;
        blockOffset = memoryOffset % SDMMC_BLOCK_SIZE;
        /* not block aligned */
        if (blockOffset != 0) {
            bufOffset = SDMMC_BLOCK_SIZE - blockOffset;
            MMCT_ReadFun(pSd, block , 1, tempBlockBuffer);
            memcpy(tempBlockBuffer + blockOffset, (unsigned char *)bufferAddr, SDMMC_BLOCK_SIZE - bufOffset);
            error = MMCT_WriteFun(pSd, block , 1, tempBlockBuffer);
            block++;
            bufferAddr += bufOffset;
            bytesToWrite -= bufOffset;
        }
        while(bytesToWrite) {
            MMCT_WriteFun(pSd, block , 1, (unsigned char *)bufferAddr);
            bufferAddr += SDMMC_BLOCK_SIZE;
            if (bytesToWrite>=SDMMC_BLOCK_SIZE){
                bytesToWrite -= SDMMC_BLOCK_SIZE;
            } else {
                bytesToWrite = 0;
            }
            block++;
        }
        printf("WRITE return byte written : 0x%lx Bytes\n\r", pMailbox->argument.inputWrite.bufferSize - bytesToWrite);
        pMailbox->argument.outputWrite.bytesWritten = pMailbox->argument.inputWrite.bufferSize - bytesToWrite;
        pMailbox->status = APPLET_SUCCESS;
    }

    /* ---------------------------------------------------------- */
    /* READ:                                                      */
    /* ---------------------------------------------------------- */
    else if (pMailbox->command == APPLET_CMD_READ) {
        TRACE_INFO("RECEIVE FILE command\n\r");
        pSd = &sdDrv[bMciID];
        memoryOffset = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr   = pMailbox->argument.inputWrite.bufferAddr;
        bytesToRead = pMailbox->argument.inputWrite.bufferSize;
        block = memoryOffset / SDMMC_BLOCK_SIZE;
        blockOffset = memoryOffset % SDMMC_BLOCK_SIZE;
        /* not block aligned */
        if (blockOffset != 0) {
            bufOffset = SDMMC_BLOCK_SIZE - blockOffset;
            MMCT_ReadFun(pSd, block , 1, tempBlockBuffer);
            memcpy( (unsigned char *)bufferAddr, tempBlockBuffer + blockOffset, SDMMC_BLOCK_SIZE - bufOffset);
            block++;
            bufferAddr += bufOffset;
            bytesToRead -= bufOffset;
        }
        while(bytesToRead) {
            MMCT_ReadFun(pSd, block , 1, (unsigned char *)bufferAddr);
            bufferAddr += SDMMC_BLOCK_SIZE;
            if (bytesToRead >= SDMMC_BLOCK_SIZE){
                bytesToRead -= SDMMC_BLOCK_SIZE;
            } else {
                bytesToRead = 0;
            }
            block++;
        }
        printf("READ return byte read : 0x%lx Bytes\n\r", pMailbox->argument.inputRead.bufferSize - bytesToRead);
        pMailbox->argument.outputRead.bytesRead = pMailbox->argument.inputRead.bufferSize - bytesToRead;
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

