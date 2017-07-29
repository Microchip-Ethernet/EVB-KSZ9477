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

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------
#include "../common/applet.h"
#include <board.h>
#include <board_lowlevel.h>
#include <board_memories.h>
#include <dbgu/dbgu.h>
#include <memories/flash/flashd.h>
#include <pio/pio.h>
#include <utility/trace.h>

#include <string.h>


//------------------------------------------------------------------------------
//         Local definitions
//------------------------------------------------------------------------------

//#if defined (at91sam9xe)
//#define STACK_SIZE (AT91C_IFLASH_PAGE_SIZE + 0x100 + 0x1000)
//#else
//#define STACK_SIZE (AT91C_IFLASH_PAGE_SIZE + 0x100)
//#endif

#if defined (at91sam9xe)
#define STACK_SIZE (0x100 + 0x1000)
#else
#define STACK_SIZE (0x100)
#endif

#if defined (at91sam7x512) || (at91sam7xc512)
#define FLASH_SECOND_BANK_OFFSET  ((unsigned int) 256 * 1024)
#endif

#if defined(AT91C_PMC_CSS_PLLA_CLK) && !defined(AT91C_PMC_CSS_PLL_CLK)
    #define AT91C_PMC_CSS_PLL_CLK     AT91C_PMC_CSS_PLLA_CLK
#endif

#define MAX_BUF_SIZE 1024*32
//------------------------------------------------------------------------------
//         Local structures
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Structure for storing parameters for each command that can be performed by
/// the applet.
//------------------------------------------------------------------------------
struct _Mailbox {

    /// Command send to the monitor to be executed.
    unsigned int command;
    /// Returned status, updated at the end of the monitor execution.
    unsigned int status;

    /// Input Arguments in the argument area
    union {

        /// Input arguments for the Init command.
        struct {

            /// Communication link used.
            unsigned int comType;
            /// Trace level.
            unsigned int traceLevel;
            /// Memory Bank to write in.
            unsigned int bank;

        } inputInit;

        /// Output arguments for the Init command.
        struct {

            /// Memory size.
            unsigned int memorySize;
            /// Buffer address.
            unsigned int bufferAddress;
            /// Buffer size.
            unsigned int bufferSize;
            struct {
                /// Lock region size in byte.
                unsigned short lockRegionSize;
                /// Number of Lock Bits.
                unsigned short numbersLockBits;
            } memoryInfo;
        } outputInit;

        /// Input arguments for the Write command.
        struct {

            /// Buffer address.
            unsigned int bufferAddr;
            /// Buffer size.
            unsigned int bufferSize;
            /// Memory offset.
            unsigned int memoryOffset;

        } inputWrite;

        /// Output arguments for the Write command.
        struct {

            /// Bytes written.
            unsigned int bytesWritten;
        } outputWrite;

        /// Input arguments for the Read command.
        struct {

            /// Buffer address.
            unsigned int bufferAddr;
            /// Buffer size.
            unsigned int bufferSize;
            /// Memory offset.
            unsigned int memoryOffset;

        } inputRead;

        /// Output arguments for the Read command.
        struct {

            /// Bytes read.
            unsigned int bytesRead;

        } outputRead;

        /// Input arguments for the Full Erase command.
        // NONE

         /// Input arguments for the Lock page command.
        struct {

            /// Sector number to be lock.
            unsigned int sector;

        } inputLock;

        /// Output arguments for the Lock  page command.
        // NONE

         /// Input arguments for the Unlock  page command.
        struct {

            /// Sector number to be unlock.
            unsigned int sector;

        } inputUnlock;

        /// Output arguments for the Unlock  page command.
        // NONE

         /// Input arguments for the set/clear GPNVM bits command.
        struct {

            /// Activates or Deactivates
            unsigned int action;
            /// NVM bit to set/clear
            unsigned int bitsOfNVM;

        } inputGPNVM;

        /// Output arguments for the set/clear GPNVM bits command.
        // NONE

        /// Input arguments for the set secuity bit command.
        // NONE

        /// Output arguments for the set secuity bit command.
        // NONE

        /// Input arguments for the Read Unique ID command.
        struct {

            /// Buffer address.
            unsigned int bufferAddr;
        } inputReadUniqueID;

        /// Output arguments for the Read Unique ID command.
        // NONE

    } argument;
};

//------------------------------------------------------------------------------
//         Global variables
//------------------------------------------------------------------------------

/// End of program space (code + data).
extern unsigned int end;

/// Size of the buffer used for read/write operations in bytes.
static unsigned int bufferSize;
/// Communication type with SAM-BA GUI.
static unsigned int comType;

/// Flash base address
static unsigned int flashBaseAddr;
/// Flash base address at applet init
static unsigned int flashBaseAddrInit;
/// Flash size
static unsigned int flashSize;
/// Flash page size
static unsigned int flashPageSize;
/// Flash lock region size
static unsigned int flashLockRegionSize;

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Applet main entry. This function decodes received command and executes it.
/// \param argc  always 1
/// \param argv  Address of the argument area.
//------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;

    unsigned int bytesToWrite, bufferAddr, memoryOffset;

    unsigned int l_start;
    unsigned int l_end;
    unsigned int *pActualStart = NULL;
    unsigned int *pActualEnd = NULL;

    unsigned char error;

    TRACE_CONFIGURE_ISP(DBGU_STANDARD, 115200, BOARD_MCK);

    // ----------------------------------------------------------
    // INIT:
    // ----------------------------------------------------------
    if (pMailbox->command == APPLET_CMD_INIT) {
        // Save info of communication link
        comType = pMailbox->argument.inputInit.comType;

#if (DYN_TRACES == 1)
        traceLevel = pMailbox->argument.inputInit.traceLevel;
#endif

        switch (pMailbox->argument.inputInit.bank) {
            default:
            case 0:
                flashBaseAddr       = AT91C_IFLASH;
                flashBaseAddrInit   = AT91C_IFLASH;
#if defined (at91sam3u4)
                flashSize           = AT91C_IFLASH_SIZE + AT91C_IFLASH1_SIZE;
#else
                flashSize           = AT91C_IFLASH_SIZE;
#endif
                flashPageSize       = AT91C_IFLASH_PAGE_SIZE;
                pMailbox->argument.outputInit.memoryInfo.numbersLockBits = AT91C_IFLASH_NB_OF_LOCK_BITS;
                flashLockRegionSize = AT91C_IFLASH_LOCK_REGION_SIZE;
                break;
#if defined (at91sam3u4)
            case 1:
                flashBaseAddr       = AT91C_IFLASH1;
                flashBaseAddrInit   = AT91C_IFLASH1;
                flashSize           = AT91C_IFLASH1_SIZE;
                flashPageSize       = AT91C_IFLASH1_PAGE_SIZE;
                pMailbox->argument.outputInit.memoryInfo.numbersLockBits = AT91C_IFLASH1_NB_OF_LOCK_BITS;
                flashLockRegionSize = AT91C_IFLASH1_LOCK_REGION_SIZE;
                break;
#endif
        }

        TRACE_INFO("-- Internal Flash Applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);

        // Initialize flash driver
        FLASHD_Initialize(BOARD_MCK);
        // flash accesses must be 4 bytes aligned
        pMailbox->argument.outputInit.bufferAddress = ((unsigned int) &end);
        
#if defined (at91sam7s161) || defined (at91sam3u1)
        bufferSize = flashPageSize * 2;
#elif defined (at91sam7s32)  || defined (at91sam7s321) ||  defined (at91sam7l)
        bufferSize = flashPageSize;
#else        
        bufferSize = AT91C_ISRAM_SIZE                           // sram size
                     - ( ((unsigned int) &end) - AT91C_ISRAM )  // program size (romcode, code+data)
                     - STACK_SIZE;                              // stack size at the end
#endif                     
        // integer number of pages can be contained in each buffer
        // operation is : buffersize -= bufferSize % flashPageSize
        // modulo can be done with a mask since flashpagesize is a power  of two integer
        bufferSize -= (bufferSize & (flashPageSize - 1));
        if (bufferSize > MAX_BUF_SIZE && (comType == DBGU_COM_TYPE)) bufferSize = MAX_BUF_SIZE; 
        pMailbox->argument.outputInit.bufferSize = bufferSize;

        pMailbox->argument.outputInit.memorySize = flashSize;
        pMailbox->argument.outputInit.memoryInfo.lockRegionSize = flashLockRegionSize;

        TRACE_INFO("bufferSize : %d  bufferAddr: 0x%x \n\r",
               pMailbox->argument.outputInit.bufferSize,
               (unsigned int) &end );

        TRACE_INFO("memorySize : %d lockRegionSize : 0x%x numbersLockBits : 0x%x \n\r",
               pMailbox->argument.outputInit.memorySize,
               pMailbox->argument.outputInit.memoryInfo.lockRegionSize,
               pMailbox->argument.outputInit.memoryInfo.numbersLockBits);

        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // WRITE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_WRITE) {

        memoryOffset  = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr    = pMailbox->argument.inputWrite.bufferAddr;
        bytesToWrite  = pMailbox->argument.inputWrite.bufferSize;

#if defined (at91sam3u4)
        if (flashBaseAddrInit == AT91C_IFLASH) {
            if ((memoryOffset < AT91C_IFLASH_SIZE) && ((memoryOffset + bytesToWrite) > AT91C_IFLASH_SIZE)) {
                flashBaseAddr = AT91C_IFLASH;
                bytesToWrite = AT91C_IFLASH_SIZE - memoryOffset;
            }
            else if (memoryOffset >= AT91C_IFLASH_SIZE) {
                flashBaseAddr = AT91C_IFLASH1;
                memoryOffset -= AT91C_IFLASH_SIZE;
            }
        }
#endif

        TRACE_INFO("WRITE at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes (flash base addr : 0x%x)\n\r",
                   memoryOffset, bufferAddr, bytesToWrite, flashBaseAddr);

        // Check the giving sector have been locked before.
        if (FLASHD_IsLocked(flashBaseAddr + memoryOffset, flashBaseAddr + memoryOffset + bytesToWrite) != 0) {

            TRACE_INFO("Error page locked\n\r");
            pMailbox->argument.outputWrite.bytesWritten = 0;
            pMailbox->status = APPLET_PROTECT_FAIL;
            goto exit;
        }

        // Write data
        if (FLASHD_Write(flashBaseAddr + memoryOffset, (const void *)bufferAddr, bytesToWrite) != 0) {

            TRACE_INFO("Error write operation\n\r");
            pMailbox->argument.outputWrite.bytesWritten = 0;
            pMailbox->status = APPLET_WRITE_FAIL;
            goto exit;
        }

        TRACE_INFO("Write achieved\n\r");
        pMailbox->argument.outputWrite.bytesWritten = bytesToWrite;
        pMailbox->status = APPLET_SUCCESS;
    }
    // ----------------------------------------------------------
    // READ:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_READ) {

        memoryOffset = pMailbox->argument.inputRead.memoryOffset;
        bufferAddr   = pMailbox->argument.inputRead.bufferAddr;
        bufferSize   = pMailbox->argument.inputRead.bufferSize;

#if defined (at91sam3u4)
        if (flashBaseAddrInit == AT91C_IFLASH) {
            flashBaseAddr = AT91C_IFLASH;
            if ((memoryOffset < AT91C_IFLASH_SIZE) && ((memoryOffset + bufferSize) > AT91C_IFLASH_SIZE)) {
                bufferSize = AT91C_IFLASH_SIZE - memoryOffset;
            }
            else if (memoryOffset >= AT91C_IFLASH_SIZE) {
                flashBaseAddr = AT91C_IFLASH1;
                memoryOffset -= AT91C_IFLASH_SIZE;
            }
        }
#endif

        TRACE_INFO("READ at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes (flash base addr : 0x%x)\n\r",
                   memoryOffset, bufferAddr, bufferSize, flashBaseAddr);

        // read data
        memcpy((void *)bufferAddr, (void *)(flashBaseAddr + memoryOffset), bufferSize);

        TRACE_INFO("Read achieved\n\r");
        pMailbox->argument.outputRead.bytesRead = bufferSize;
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // FULL ERASE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_FULL_ERASE) {
        TRACE_INFO("FULL ERASE command \n\r");

#if defined (at91sam3u4)
        if (flashBaseAddrInit == AT91C_IFLASH) {
            flashBaseAddr = AT91C_IFLASH;
            // Check if at least one page has been locked
            if (FLASHD_IsLocked(flashBaseAddr, flashBaseAddr + AT91C_IFLASH_SIZE - 1) != 0) {

                TRACE_INFO("Error page locked \n\r");
                pMailbox->status = APPLET_PROTECT_FAIL;
                goto exit;
            }
        }
        else {
            // Check if at least one page has been locked
            if (FLASHD_IsLocked(flashBaseAddr, flashBaseAddr + AT91C_IFLASH1_SIZE - 1) != 0) {

                TRACE_INFO("Error page locked \n\r");
                pMailbox->status = APPLET_PROTECT_FAIL;
                goto exit;
            }
        }
#else
        // Check if at least one page has been locked
        if (FLASHD_IsLocked(flashBaseAddr, flashBaseAddr + flashSize) != 0) {

            TRACE_INFO("Error page locked \n\r");
            pMailbox->status = APPLET_PROTECT_FAIL;
            goto exit;
        }
#endif
        // Implement the erase all command
        if (FLASHD_Erase(flashBaseAddr) != 0) {

            TRACE_INFO("Full erase failed! \n\r");
            pMailbox->status = APPLET_ERASE_FAIL;
            goto exit;
        }

#if defined (at91sam7xc512) || (at91sam7x512)
        if (FLASHD_Erase(flashBaseAddr + FLASH_SECOND_BANK_OFFSET) != 0) {

            TRACE_INFO("Full erase failed! \n\r");
            pMailbox->status = APPLET_ERASE_FAIL;
            goto exit;
        }
#endif
        TRACE_INFO("Full erase achieved\n\r");

        pMailbox->status = APPLET_SUCCESS;
    }
    // ----------------------------------------------------------
    // LOCK SECTOR:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_LOCK) {
        TRACE_INFO("LOCK command \n\r");

#if defined (at91sam3u4)
        if (flashBaseAddrInit == AT91C_IFLASH) {
            flashBaseAddr = AT91C_IFLASH;
            if (pMailbox->argument.inputLock.sector >= AT91C_IFLASH_NB_OF_LOCK_BITS) {
                flashBaseAddr = AT91C_IFLASH1;
                pMailbox->argument.inputLock.sector -= AT91C_IFLASH_NB_OF_LOCK_BITS;
            }
        }
#endif
        l_start = (pMailbox->argument.inputLock.sector * flashLockRegionSize) + flashBaseAddr;
        l_end = l_start + flashLockRegionSize;

        if( FLASHD_Lock(l_start, l_end, pActualStart, pActualEnd) != 0) {

            TRACE_INFO("Lock failed! \n\r");
        //   ASSERT( *pActualStart == l_start, "-F- Lock failed! \n\r");
        //   ASSERT( *pActualEnd == (l_start + flashLockRegionSize), "-F- Lock failed! \n\r");
            pMailbox->status = APPLET_PROTECT_FAIL;
            goto exit;
        }

        TRACE_INFO("Lock sector achieved\n\r");

        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // UNLOCK SECTOR:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_UNLOCK) {
        TRACE_INFO("UNLOCK command \n\r");

#if defined (at91sam3u4)
        if (flashBaseAddrInit == AT91C_IFLASH) {
            flashBaseAddr = AT91C_IFLASH;
            if (pMailbox->argument.inputLock.sector >= AT91C_IFLASH_NB_OF_LOCK_BITS) {
                flashBaseAddr = AT91C_IFLASH1;
                pMailbox->argument.inputLock.sector -= AT91C_IFLASH_NB_OF_LOCK_BITS;
            }
        }
#endif
        l_start = (pMailbox->argument.inputLock.sector * flashLockRegionSize) + flashBaseAddr;
        l_end = l_start + flashLockRegionSize;

        if( FLASHD_Unlock(l_start, l_end, pActualStart, pActualEnd) != 0) {

            TRACE_INFO("Unlock failed! \n\r");
            //ASSERT( *pActualStart == l_start, "-F- Unlock failed! \n\r");
            //ASSERT( *pActualEnd == (l_start + flashLockRegionSize), "-F- Unock failed! \n\r");
            pMailbox->status = APPLET_UNPROTECT_FAIL;
            goto exit;
        }

        TRACE_INFO("Unlock sector achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // GPNVM :
    // ----------------------------------------------------------
#if !defined (at91sam7a3) 
    else if (pMailbox->command == APPLET_CMD_GPNVM) {
        if( pMailbox->argument.inputGPNVM.action == 0) {
            TRACE_INFO("DEACTIVATES GPNVM command \n\r");
            error = FLASHD_ClearGPNVM(pMailbox->argument.inputGPNVM.bitsOfNVM);
        }
        else {
            TRACE_INFO("ACTIVATES GPNVM command \n\r");
            error = FLASHD_SetGPNVM(pMailbox->argument.inputGPNVM.bitsOfNVM);
        }

        if(error != 0) {
            TRACE_INFO("GPNVM failed! \n\r");
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }

        TRACE_INFO("GPNVM achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
#endif // #if !defined (at91sam7a3)    

    // ----------------------------------------------------------
    // SET SECURITY :
    // ----------------------------------------------------------
#if defined(CHIP_FLASH_EFC) && !defined (at91sam7a3)
    else if (pMailbox->command == APPLET_CMD_SECURITY) {
        TRACE_INFO("SET SECURITY BIT command \n\r");

        if (FLASHD_SetSecurityBit() != 0)
        {
            TRACE_INFO("SET SECURITY BIT failed! \n\r");
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }

        TRACE_INFO("SET SECURITY BIT achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
#endif

#if defined(at91sam3u4)
    // ----------------------------------------------------------
    // READ UNIQUE ID :
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_READ_UNIQUE_ID) {
        TRACE_INFO("READ UNIQUE ID command \n\r");

        if (FLASHD_ReadUniqueID (pMailbox->argument.inputReadUniqueID.bufferAddr) != 0) {
            TRACE_INFO("Read Unique ID failed! \n\r");
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }

        TRACE_INFO("Read Unique ID achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
#endif

exit:
    // Acknowledge the end of command
    TRACE_INFO("\tEnd of Applet %x %x.\n\r", pMailbox->command, pMailbox->status);
    // Notify the host application of the end of the command processing
    pMailbox->command = ~(pMailbox->command);
    // Send ACK character
    if (comType == DBGU_COM_TYPE) {
        DBGU_PutChar(0x6);
    }

    return 0;
}

