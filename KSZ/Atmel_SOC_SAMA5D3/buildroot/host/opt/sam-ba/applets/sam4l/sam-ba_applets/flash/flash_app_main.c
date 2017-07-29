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

/** \page flash_applet Flash Applet
 * Flash applet is a small piece of software running on the target board, embedding the
 * flash read, write, and erase algorithms etc. \n
 *
 * SAM-BA host controls commands and data transfering, it loads flash applet and
 * executes it to implement flash memory operation.
 * An applet consists of:
 * <ul>
 * <li>A mailbox which can share information between the applet and SAM-BA host.</li>
 * <li>Implement APPLET_CMD_INIT command to initializes EEFC and reports memory size,
 * number of lock region, lock region size and buffer size through the mailbox.</li>
 * <li>A flash programming algorithm works for APPLET_CMD_WRITE command, it erases and programs
 * flash data in buffer at the address which specified in mailbox.</li>
 * <li>Erase all algorithm is necessary to erasing entire flash memory. </li>
 * <li>Some other commands such as APPLET_CMD_LOCK, APPLET_CMD_UNLOCK and APPLET_CMD_GPNVM
 * all has its process entry to implement.</li>
 * </ul>
 *
 * It reports command status and written/read size (for write/read algorithm) in mailbox to
 * SAM-BA host while the command is achieved.
 *
 * For more accurate information, please look at the \ref flashd_module and \ref efc_module.
 *
 * Related files :\n
 * \ref main.c\n
 * \ref efc.c\n
 * \ref efc.h.\n
 * \ref flashd.c\n
 * \ref flashd.h.\n
*/
/*@{*/
/*@}*/


/**
 * \file
 *
 * Implementation of flash applet for ISP.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "../common/applet.h"

#include <string.h>
#include <flashcalw.h>


/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
/** stack size for flash applet */
#define STACK_SIZE (0x100)
#define MONITOR_SIZE (0x4000)

//Device specific defines
#define UNIQUE_SERIAL_NUMBER_ADDR (0x0080020C)
#define UNIQUE_SERIAL_NUMBER_SIZE (0xF)

// Empty macro
#define TRACE_DEBUG(...)      { }
#define TRACE_INFO(...)       { }
#define TRACE_WARNING(...)    { }               
#define TRACE_ERROR(...)      { }
#define TRACE_FATAL(...)      { while(1); }
#define TRACE_PERM(...)       { }


/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/

/** \brief Structure for storing parameters for each command that can be
 *   performed by the applet. */
struct _Mailbox {

    /** Command send to the monitor to be executed. */
    uint32_t command;
    /** Returned status, updated at the end of the monitor execution.*/
    uint32_t status;

    /** Input Arguments in the argument area. */
    union {

        /** Input arguments for the Init command.*/
        struct {

            /** Communication link used.*/
            uint32_t comType;
            /** Trace level.*/
            uint32_t traceLevel;
            /** Memory Bank to write in.*/
            uint32_t bank;

        } inputInit;

        /** Output arguments for the Init command.*/
        struct {

            /** Memory size.*/
            uint32_t memorySize;
            /** Buffer address.*/
            uint32_t bufferAddress;
            /** Buffer size.*/
            uint32_t bufferSize;
            struct {
                /** Lock region size in byte.*/
                uint16_t lockRegionSize;
                /** Number of Lock Bits.*/
                uint16_t numbersLockBits;
            } memoryInfo;
			/** extended infos.*/
			uint32_t pageSize;
			uint32_t nbPages;
			uint32_t appStartPage;			
        } outputInit;

        /** Input arguments for the Write command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;

        } inputWrite;

        /** Output arguments for the Write command.*/
        struct {

            /** Bytes written.*/
            uint32_t bytesWritten;
        } outputWrite;

        /** Input arguments for the Read command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;

        } inputRead;

        /** Output arguments for the Read command.*/
        struct {

            /** Bytes read.*/
            uint32_t bytesRead;

        } outputRead;

        /** Input arguments for the Full Erase command.*/
        /** NONE*/

         /** Input arguments for the Lock page command.*/
        struct {

            /** Sector number to be lock.*/
            uint32_t sector;

        } inputLock;

        /** Output arguments for the Lock  page command.*/
        /** NONE*/

        /*/ Input arguments for the Unlock  page command.*/
        struct {

            /** Sector number to be unlock.*/
            uint32_t sector;

        } inputUnlock;

        /** Output arguments for the Unlock  page command.*/
        /** NONE*/

         /** Input arguments for the set/clear GPNVM bits command.*/
        struct {

            /** Activates or Deactivates*/
            uint32_t action;
            /** NVM bit to set/clear*/
            uint32_t bitsOfNVM;

        } inputGPNVM;

        /** Output arguments for the set/clear GPNVM bits command.*/
        /** NONE*/

        /** Input arguments for the set secuity bit command.*/
        /** NONE*/

        /** Output arguments for the set secuity bit command.*/
        /** NONE*/

		/** Input arguments for the set/clear FUSES bits command.*/
        struct {
            /** bit values to be set*/
            uint64_t value;
            /** bitmask to select bits to write*/
            uint64_t writebitmask;
            /** bitmask to select bits to write*/
            uint64_t errors;
        } inputFUSES;

        /** Output arguments for the set/clear GPNVM bits command.*/
        struct {
            /** bit values to be set*/
            uint64_t value;
            /** bitmask to select bits to write*/
            uint64_t writebitmask;
            /** errors results*/
            uint64_t errors;
        } outputFUSES;


        /** Input arguments for the Read Unique SN command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
        } inputReadUniqueSN;

        /** Output arguments for the Read Unique SN command.*/
        /** NONE*/

        /** Input arguments for the Security command.*/
        struct {

            /** Activates*/
            uint32_t action;
        } inputSecurity;

        /** Output arguments for the Security command.*/
        struct {

            /** Bytes written.*/
            uint32_t secure_state;
        } outputSecurity;

        /** Input arguments for the Write command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;

        } inputWriteUserPage;

        /** Output arguments for the Write command.*/
        struct {

            /** Bytes written.*/
            uint32_t bytesWritten;
        } outputWriteUserPage;
		
        /** Input arguments for the Read command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;

        } inputReadUserPage;

        /** Output arguments for the Read command.*/
        struct {

            /** Bytes read.*/
            uint32_t bytesRead;

        } outputReadUserPage;
        /** Input arguments for the erase region command.*/
        struct {
            /** page.*/
            uint32_t page;
        } inputErasePage;

        /** Output arguments for the  erase region command.*/
		/*NONE*/
		
    } argument;
};



bool applet_flashcalw_islocked(uint32_t addstart,uint32_t addend)
{
	uint32_t region_start;
	uint32_t region_end;
	uint32_t reg;
	
	//Get region number from address
	region_start=flashcalw_get_page_region((addstart-FLASH_ADDR)/FLASH_PAGE_SIZE);
	//Get region number from address
	region_end=flashcalw_get_page_region((addend-FLASH_ADDR)/FLASH_PAGE_SIZE);
	
	//Now check that all regions between start and end (included) are not locked
	for(reg=region_start;reg<=region_end;reg++)
	{
		if(flashcalw_is_region_locked(reg))
			return(true);
	}
	//No locked region found
	return(false);
}

bool applet_flashcalw_readserialnumber(uint32_t * ptrbuffer)
{
		memcpy((void *)ptrbuffer,(void *)UNIQUE_SERIAL_NUMBER_ADDR,UNIQUE_SERIAL_NUMBER_SIZE);
		return(true);
}


/*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/
/** End of program space (code + data).*/
extern uint32_t end;

/** Size of the buffer used for read/write operations in bytes.*/
static uint32_t bufferSize;
/** Communication type with SAM-BA GUI.*/
static uint32_t comType;

/** Flash base address*/
static volatile  uint32_t flashBaseAddr;
/** Flash base address at applet init*/
static volatile  uint32_t flashBaseAddrInit;
/** Flash size*/
static volatile  uint32_t flashSize;
/** Flash page size*/
static volatile uint32_t flashPageSize;
/** Flash nb of lock bits*/
static volatile  uint32_t flashNbLockBits;
/** Flash lock region size*/
static volatile  uint32_t flashLockRegionSize;
/* Address in sector which has been written */
static volatile  uint32_t lastWrittenAddr = 0;


/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/
/**
 * \brief  Applet main entry. This function decodes received command and executes it.
 *
 * \param argc  always 1
 * \param argv  Address of the argument area..
 */
int applet_main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;

    uint32_t bytesToWrite, bufferAddr, memoryOffset;
    uint32_t p;
    /* Save info of communication link */
    comType = pMailbox->argument.inputInit.comType;
	
	//Applet vars are cleared on every load
	flashBaseAddr       = FLASH_ADDR;
	flashBaseAddrInit   = FLASH_ADDR;
	flashSize           = flashcalw_get_flash_size();
	flashPageSize       = FLASH_PAGE_SIZE;
	flashNbLockBits     = 16; //Hardcoded
	flashLockRegionSize = flashSize/flashNbLockBits;

    /*----------------------------------------------------------
     * INIT:
     *----------------------------------------------------------*/
    if (pMailbox->command == APPLET_CMD_INIT) {
        /*  Re-configurate UART   (MCK maybe change in LowLevelInit())  */
        //UART_Configure(115200, BOARD_MCK);
        /* flash accesses must be 4 bytes aligned */
        pMailbox->argument.outputInit.bufferAddress = ((uint32_t) &end);

        bufferSize = HRAMC0_SIZE                            /* sram size */
                     - ( ((uint32_t) &end) - HRAMC0_ADDR )  /* program size (romcode, code+data) */
                     - STACK_SIZE;                         /* stack size at the end */
        /* integer number of pages can be contained in each buffer */
        /* operation is : buffersize -= bufferSize % flashPageSize */
        /* modulo can be done with a mask since flashpagesize is a power of two integer */
        //bufferSize = bufferSize > SECTOR_SIZE ? SECTOR_SIZE: bufferSize;
		//Timeout issue
		//bufferSize = (bufferSize/flashPageSize)*flashPageSize;
		bufferSize = flashPageSize;
        pMailbox->argument.outputInit.bufferSize = bufferSize;
        pMailbox->argument.outputInit.memorySize = flashSize;
        pMailbox->argument.outputInit.memoryInfo.lockRegionSize = flashLockRegionSize;
        pMailbox->argument.outputInit.memoryInfo.numbersLockBits = flashNbLockBits;
        pMailbox->argument.outputInit.pageSize = flashPageSize;
        pMailbox->argument.outputInit.nbPages = flashcalw_get_flash_size()/flashPageSize;
        pMailbox->argument.outputInit.appStartPage = MONITOR_SIZE/flashPageSize;
		
        TRACE_INFO("bufferSize : %d  bufferAddr: 0x%x \n\r",
               (int)pMailbox->argument.outputInit.bufferSize,
               (uint32_t) &end );

        TRACE_INFO("memorySize : %d lockRegionSize : 0x%x numbersLockBits : 0x%x \n\r",
               (int)pMailbox->argument.outputInit.memorySize,
               (uint32_t)pMailbox->argument.outputInit.memoryInfo.lockRegionSize,
               (uint32_t)pMailbox->argument.outputInit.memoryInfo.numbersLockBits);

        pMailbox->status = APPLET_SUCCESS;
    }
    /*----------------------------------------------------------
     * WRITE:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_WRITE) {

        memoryOffset  = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr    = pMailbox->argument.inputWrite.bufferAddr;
        bytesToWrite  = pMailbox->argument.inputWrite.bufferSize;

        TRACE_INFO("WRITE at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes (flash base addr : 0x%x)\n\r",
                   (uint32_t)memoryOffset, (uint32_t)bufferAddr,
                   (uint32_t)bytesToWrite, (uint32_t)flashBaseAddr);
		//Protect monitor address space from write
		if((flashBaseAddr + memoryOffset)<MONITOR_SIZE)
		{	//Forbidden !
            TRACE_INFO("Error write operation\n\r");
            pMailbox->argument.outputWrite.bytesWritten = 0;
            pMailbox->status = APPLET_WRITE_FAIL;
            goto exit;
        }
	
        /* Check if one of the given regions is locked */
        if (applet_flashcalw_islocked(flashBaseAddr + memoryOffset, (flashBaseAddr + memoryOffset + bytesToWrite)-1) != 0) {

            TRACE_INFO("Error page locked\n\r");
            pMailbox->argument.outputWrite.bytesWritten = 0;
            pMailbox->status = APPLET_WRITE_FAIL;
            goto exit;
        }

        TRACE_INFO("Write <%x> bytes from <#%x> \n\r", (uint32_t )writeSize, (uint32_t )memoryOffset );
		
		flashcalw_memcpy((void volatile*)(flashBaseAddr + memoryOffset),(void const*)bufferAddr,bytesToWrite,true);
		if(flashcalw_is_programming_error())
		{				
            TRACE_INFO("Error write operation\n\r");
            pMailbox->argument.outputWrite.bytesWritten = bytesToWrite ;
            pMailbox->status = APPLET_WRITE_FAIL;
            goto exit;
        }
		if(flashcalw_is_lock_error())
		{				
            TRACE_INFO("Error write operation\n\r");
            pMailbox->argument.outputWrite.bytesWritten = bytesToWrite ;
            pMailbox->status = APPLET_WRITE_FAIL;
            goto exit;
        }
        TRACE_INFO("Write achieved\n\r");
        pMailbox->argument.outputWrite.bytesWritten = bytesToWrite;
        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * READ:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_READ) {

        memoryOffset = pMailbox->argument.inputRead.memoryOffset;
        bufferAddr   = pMailbox->argument.inputRead.bufferAddr;
        bufferSize   = pMailbox->argument.inputRead.bufferSize;
        TRACE_INFO("READ at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes (flash base addr : 0x%x)\n\r",
                   (uint32_t)memoryOffset, (uint32_t)bufferAddr,
                   (uint32_t)bufferSize,
                   (uint32_t)flashBaseAddr);

        /* read data */
        memcpy((void *)bufferAddr, (void *)(flashBaseAddr + memoryOffset), bufferSize);
        TRACE_INFO("Read achieved\n\r");
        pMailbox->argument.outputRead.bytesRead = bufferSize;
        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * APPLET_CMD_ERASE_REGION:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_ERASE_PAGE) {
        TRACE_INFO("APPLET_CMD_ERASE_PAGE command \n\r");

        /* Check if at least one page of the region has been locked */
        if (flashcalw_is_region_locked(flashcalw_get_page_region(pMailbox->argument.inputErasePage.page)) != 0) 
		{
            TRACE_INFO("Error page locked \n\r");
            pMailbox->status = APPLET_PROTECT_FAIL;
            goto exit;
        }
				
		//We won't erase the monitor in flash (region 0)
		//we'll keep the first x pages containing the monitor untouched
		if(pMailbox->argument.inputErasePage.page<(MONITOR_SIZE/flashPageSize))
		{
            TRACE_INFO("Error page locked \n\r");
            pMailbox->status = APPLET_PROTECT_FAIL;
            goto exit;
        }
		
        /* Erase the flash page */
		if(flashcalw_erase_page(pMailbox->argument.inputErasePage.page,true)!=true)
		{
			TRACE_INFO("Flash erase failed! \n\r");
			pMailbox->status = APPLET_ERASE_FAIL;
			goto exit;
		}
        lastWrittenAddr = 0;
        TRACE_INFO("Full erase achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
    /*----------------------------------------------------------
     * LOCK SECTOR/REGION:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_LOCK) {
        TRACE_INFO("LOCK command \n\r");

		flashcalw_lock_region(pMailbox->argument.inputLock.sector,true);
		
        if(flashcalw_is_lock_error() || flashcalw_is_programming_error())
		{
            TRACE_INFO("Lock failed! \n\r");
            pMailbox->status = APPLET_PROTECT_FAIL;
            goto exit;
        }
        TRACE_INFO("Lock sector achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * UNLOCK SECTOR:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_UNLOCK) {
        TRACE_INFO("UNLOCK command \n\r");
		
		flashcalw_lock_region(pMailbox->argument.inputLock.sector,false);
        
        if(flashcalw_is_lock_error() || flashcalw_is_programming_error())
		{
            TRACE_INFO("Unlock failed! \n\r");
            pMailbox->status = APPLET_UNPROTECT_FAIL;
            goto exit;
        }

        TRACE_INFO("Unlock sector achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * FUSES :
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_FUSES) {

		pMailbox->argument.outputFUSES.errors = 0;
		//on the 64 bits of fuses
		for(p=0;p<64;p++)
		{
			if(pMailbox->argument.inputFUSES.writebitmask&1)
			{
				//Write this fuse with the specified value
				flashcalw_set_gp_fuse_bit(p,(pMailbox->argument.inputFUSES.value&1));
				if(flashcalw_is_lock_error() || flashcalw_is_programming_error())
				{
					pMailbox->argument.outputFUSES.errors|=(1ULL<<63);
				}
			}
			//Shift vars for next bits
			pMailbox->argument.inputFUSES.value>>=1;
			pMailbox->argument.inputFUSES.writebitmask>>=1;
			pMailbox->argument.outputFUSES.errors>>=1;
		}
		//update fuse value
		pMailbox->argument.outputFUSES.value=flashcalw_read_all_gp_fuses();
		if(pMailbox->argument.outputFUSES.errors==0)
		{
			TRACE_INFO("FUSES achieved\n\r");
			pMailbox->status = APPLET_SUCCESS;
		}
		else
		{
            TRACE_INFO("FUSES failed! \n\r");
            pMailbox->status = APPLET_FAIL;
            goto exit;
		}
    }
    /*----------------------------------------------------------
     * READ UNIQUE ID :
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_READ_UNIQUE_SN) 
	{
        if (applet_flashcalw_readserialnumber((uint32_t *)(pMailbox->argument.inputReadUniqueSN.bufferAddr)) != 0) {
            TRACE_INFO("Read Unique ID failed! \n\r");
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }

        TRACE_INFO("Read Unique ID achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
    /*----------------------------------------------------------
     * READ SECURITY BIT :
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_SECURITY) 
	{
        if (pMailbox->argument.inputSecurity.action>0) {
            TRACE_INFO("Setting secure state! \n\r");
			flashcalw_activate_security_bit();
        }
		//Read security bit and set output var
		pMailbox->argument.outputSecurity.secure_state=flashcalw_is_security_bit_active();

        TRACE_INFO("Read Unique ID achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
    /*----------------------------------------------------------
     * WRITE USER PAGE:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_WRITEUSERPAGE) {

        memoryOffset  = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr    = pMailbox->argument.inputWrite.bufferAddr;
        bytesToWrite  = pMailbox->argument.inputWrite.bufferSize;

        TRACE_INFO("WRITE at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes (flash base addr : 0x%x)\n\r",
                   (uint32_t)memoryOffset, (uint32_t)bufferAddr,
                   (uint32_t)bytesToWrite, (uint32_t)flashBaseAddr);

        TRACE_INFO("Write <%x> bytes from <#%x> \n\r", (uint32_t )writeSize, (uint32_t )memoryOffset );
		
		flashcalw_memcpy((void volatile*)(FLASH_USER_PAGE_ADDR + memoryOffset),(void const*)bufferAddr,bytesToWrite,true);
		if(flashcalw_is_lock_error() || flashcalw_is_programming_error())
		{				
            TRACE_INFO("Error write operation\n\r");
            pMailbox->argument.outputWrite.bytesWritten = bytesToWrite ;
            pMailbox->status = APPLET_WRITE_FAIL;
            goto exit;
        }
        TRACE_INFO("Write achieved\n\r");
        pMailbox->argument.outputWrite.bytesWritten = bytesToWrite;
        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * READ:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_READUSERPAGE) {

        memoryOffset = pMailbox->argument.inputRead.memoryOffset;
        bufferAddr   = pMailbox->argument.inputRead.bufferAddr;
        bufferSize   = pMailbox->argument.inputRead.bufferSize;
        TRACE_INFO("READ at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes (flash base addr : 0x%x)\n\r",
                   (uint32_t)memoryOffset, (uint32_t)bufferAddr,
                   (uint32_t)bufferSize,
                   (uint32_t)flashBaseAddr);

        /* read data */
        memcpy((void *)bufferAddr, (void *)(FLASH_USER_PAGE_ADDR + memoryOffset), bufferSize);
        TRACE_INFO("Read achieved\n\r");
        pMailbox->argument.outputRead.bytesRead = bufferSize;
        pMailbox->status = APPLET_SUCCESS;
    }
	
exit:
    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of Applet %x %x.\n\r",
              (uint32_t)pMailbox->command,
              (uint32_t)pMailbox->status);
    /* Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);

		//while (!(USART2->US_CSR & US_CSR_TXRDY)) {
		//}
	   //USART2->US_THR = US_THR_TXCHR(0x06);
    return 0;
}

