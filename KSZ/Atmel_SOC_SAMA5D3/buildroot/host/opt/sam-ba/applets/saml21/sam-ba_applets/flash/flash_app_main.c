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

/** \page flash_applet Flash Applet
 * Flash applet is a small piece of software running on the target board, embedding the
 * flash read, write, and erase algorithms etc. \n
 *
 * SAM-BA host controls commands and data transfering, it loads flash applet and
 * executes it to implement flash memory operation.
 * An applet consists of:
 * <ul>
 * <li>A mailbox which can share information between the applet and SAM-BA host.</li>
 * <li>Implement APPLET_CMD_INIT command to initializes NVM and reports memory size,
 * number of lock region, lock region size and buffer size through the mailbox.</li>
 * <li>A flash programming algorithm works for APPLET_CMD_WRITE command, it erases and programs
 * flash data in buffer at the address which specified in mailbox.</li>
 * <li>Erase all algorithm is necessary to erasing entire flash memory. </li>
 * <li>Some other commands such as APPLET_CMD_LOCK, APPLET_CMD_UNLOCK
 * all has its process entry to implement.</li>
 * </ul>
 *
 * It reports command status and written/read size (for write/read algorithm) in mailbox to
 * SAM-BA host while the command is achieved.
 *
 * For more accurate information, please look at the \ref asfdoc_samd20_nvm_group.
 *
 * Related files :\n
 * \ref main.c\n
 * \ref nvm.c\n
 * \ref nvm.h.\n
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
#include <nvm.h>
#include "status_codes.h"
#include <system.h>
#include <system_interrupt.h>


/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
/** stack size for flash applet */
#define STACK_SIZE (0x500)
//Typical monitor size when compiled (rounded to 8kb upper bound)
#define MONITOR_SIZE (0x2000)

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

         /** Input arguments for the Lock row command.*/
        struct {

            /** Row number to be lock.*/
            uint32_t row;

        } inputLock;

        /** Output arguments for the Lock row command.*/
        /** NONE*/

        /** Input arguments for the Unlock row command.*/
        struct {

            /** Row number to be unlock.*/
            uint32_t row;

        } inputUnlock;

        /** Output arguments for the Unlock row command.*/
        /** NONE*/

        /** Input arguments for the set security bit command.*/
        /** NONE*/

        /** Output arguments for the set security bit command.*/
        /** NONE*/

        /** Input arguments for the Read Locks command. */
        /** NONE */

        /** Output arguments for the Read Locks command. */
        struct {
            /** Buffer address. */
            uint32_t bufferAddr;
        } outputReadLocks;

        /** Input arguments for the Read Fuses command. */
        /** NONE */

        /** Output arguments for the Read Fuses command. */
        struct {
            /** Buffer address. */
            uint32_t bufferAddr;
        } outputReadFuses;

        /** Input arguments for the Read Unique SN command.*/
        struct {
            /** Buffer address.*/
            uint32_t bufferAddr;
        } inputReadUniqueID;

        /** Output arguments for the Read Unique SN command.*/
        /** NONE*/

        /** Input arguments for the Security command.*/
        struct {

            /** Activates*/
            uint32_t action;
        } inputSecurity;

        /** Output arguments for the Security command.*/
        /** NONE */

        /** Input arguments for the erase row command.*/
        struct {
            /** page.*/
            uint32_t row;
        } inputEraseRow;

        /** Output arguments for the  erase row command.*/
        /*NONE*/

        /** Input arguments for the erase app command */
        struct {
            /** Starting row number */
            uint32_t start_row;
            /** Ending row number */
            uint32_t end_row;
        } inputEraseApp;

        /** Output arguments for the erase app command */
        /** NONE */
    } argument;
};


bool applet_nvm_islocked(uint32_t addstart,uint32_t addend)
{
	uint16_t page_start;
	uint16_t page_end;
	uint16_t page;

	//Get region number from address
	page_start = (addstart - FLASH_ADDR) / FLASH_PAGE_SIZE;
	//Get region number from address
	page_end = (addend - FLASH_ADDR) / FLASH_PAGE_SIZE;

	//Now check that all regions between start and end (included) are not locked
	for (page = page_start; page <= page_end; page++) {
		if (nvm_is_page_locked(page)) {
			return (true);
		}
	}
	//No locked region found
	return (false);
}

enum status_code applet_nvm_memcpy(
		const uint32_t destination_address,
		uint8_t *const buffer,
		uint16_t length,
		bool erase_flag)
{
	enum status_code error_code = STATUS_OK;
	uint8_t row_buffer[NVMCTRL_ROW_PAGES * FLASH_PAGE_SIZE];
	volatile uint8_t *dest_add = (uint8_t *)destination_address;
	const uint8_t *src_buf = buffer;
	uint32_t i;

	/* Calculate the starting row address of the page to update */
	uint32_t row_start_address =
			destination_address & ~((FLASH_PAGE_SIZE * NVMCTRL_ROW_PAGES) - 1);

	while (length) {
		/* Backup the contents of a row */
		for (i = 0; i < NVMCTRL_ROW_PAGES; i++) {
			do
			{
				error_code = nvm_read_buffer(
				row_start_address + (i * FLASH_PAGE_SIZE),
				(row_buffer + (i * FLASH_PAGE_SIZE)), FLASH_PAGE_SIZE);
			} while (error_code == STATUS_BUSY);

			if (error_code != STATUS_OK) {
				return error_code;
			}
		}
		
		/* Update the buffer if necessary */
		for (i = row_start_address; i < row_start_address + (FLASH_PAGE_SIZE * NVMCTRL_ROW_PAGES); i++)
		{
			if (length && ((uint8_t *)i == dest_add)) {
				row_buffer[i-row_start_address] = *src_buf++;
				dest_add++;
				length--;
			}
		}
		
		system_interrupt_enter_critical_section();

		if (erase_flag) {
			/* Erase the row */
			do
			{
				error_code = nvm_erase_row(row_start_address);
			} while (error_code == STATUS_BUSY);

			if (error_code != STATUS_OK) {
				return error_code;
			}
		}

		/* Write the updated row contents to the erased row */
		for (i = 0; i < NVMCTRL_ROW_PAGES; i++) {
			do
			{
				error_code = nvm_write_buffer(
				row_start_address + (i * FLASH_PAGE_SIZE),
				(row_buffer + (i * FLASH_PAGE_SIZE)), FLASH_PAGE_SIZE);
			} while (error_code == STATUS_BUSY);

			if (error_code != STATUS_OK) {
				return error_code;
			}
		}

		system_interrupt_leave_critical_section();

		row_start_address += NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE;

	}

	return error_code;
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
/** Address in sector which has been written */
static volatile  uint32_t lastWrittenAddr = 0;
/** Flash pages in a row */
static volatile uint32_t flashNbPagesOneRow;
/** Current row number */
static volatile uint16_t row;

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
	struct nvm_config config;
	enum status_code status;

	uint32_t bytesToWrite, bufferAddr, memoryOffset;

	// Save info of communication link
	comType = pMailbox->argument.inputInit.comType;

	nvm_get_config_defaults(&config);
	nvm_set_config(&config);

	//Applet vars are cleared on every load
	flashBaseAddr       = FLASH_ADDR;
	flashBaseAddrInit   = FLASH_ADDR;
	flashSize           = FLASH_SIZE;
	flashPageSize       = FLASH_PAGE_SIZE;
	flashNbLockBits     = 16; //Hardcoded
	flashLockRegionSize = flashSize/flashNbLockBits;
	flashNbPagesOneRow  = 4; //Hardcoded

	/*----------------------------------------------------------
	 * INIT:
	 *----------------------------------------------------------*/
	if (pMailbox->command == APPLET_CMD_INIT) {
		/*  Re-configurate UART   (MCK maybe change in LowLevelInit())  */
		//UART_Configure(115200, BOARD_MCK);
		/* flash accesses must be 4 bytes aligned */
		pMailbox->argument.outputInit.bufferAddress = ((uint32_t) &end);

		//bufferSize = flashPageSize;
		bufferSize = HSRAM_SIZE                            /* sram size */
					- ( ((uint32_t) &end) - HSRAM_ADDR )  /* program size (romcode, code+data) */
					- STACK_SIZE;                         /* stack size at the end */
		/* integer number of pages can be contained in each buffer.
		 * operation is : buffersize -= bufferSize % flashPageSize */
		/* modulo can be done with a mask since flashpagesize is a power of two integer */
		bufferSize = bufferSize > (4 * flashPageSize) ? (4 * flashPageSize): bufferSize;
		//Timeout issue
		//bufferSize = (bufferSize/flashPageSize)*flashPageSize;
		//bufferSize = 128 * flashPageSize;
		pMailbox->argument.outputInit.bufferSize = bufferSize;
		pMailbox->argument.outputInit.memorySize = flashSize;
		pMailbox->argument.outputInit.memoryInfo.lockRegionSize = flashLockRegionSize;
		pMailbox->argument.outputInit.memoryInfo.numbersLockBits = flashNbLockBits;
		pMailbox->argument.outputInit.pageSize = flashPageSize;
		pMailbox->argument.outputInit.nbPages = flashSize/flashPageSize;
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
		if ((flashBaseAddr + memoryOffset) < MONITOR_SIZE) {
			//Forbidden !
			TRACE_INFO("Error write operation\n\r");
			pMailbox->argument.outputWrite.bytesWritten = 0;
			pMailbox->status = APPLET_WRITE_FAIL;
			goto exit;
		}
		/* Check if one of the given regions is locked */
		if (applet_nvm_islocked(flashBaseAddr + memoryOffset, (flashBaseAddr + memoryOffset + bytesToWrite)-1) != 0) {
			TRACE_INFO("Error page locked\n\r");
			pMailbox->argument.outputWrite.bytesWritten = 0;
			pMailbox->status = APPLET_WRITE_FAIL;
			goto exit;
		}

		TRACE_INFO("Write <%x> bytes from <#%x> \n\r", (uint32_t )writeSize, (uint32_t )memoryOffset );
		if (applet_nvm_memcpy(flashBaseAddr + memoryOffset, (uint8_t *const)bufferAddr, bytesToWrite, (((flashBaseAddr + memoryOffset) & 0xFF) == 0)) != STATUS_OK) {
			TRACE_INFO("Error in write operation\n\r");
			pMailbox->argument.outputWrite.bytesWritten = bytesToWrite;
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
	 * READ:
	 *----------------------------------------------------------*/
	else if (pMailbox->command == APPLET_CMD_READ_DEVICE_ID) {
		TRACE_INFO("READ DEVICE ID command \n\r");
		*((uint32_t *)(pMailbox->argument.inputReadUniqueID.bufferAddr)) = system_get_device_id();
		TRACE_INFO("Read achieved\n\r");
		pMailbox->argument.outputRead.bytesRead = bufferSize;
		pMailbox->status = APPLET_SUCCESS;
	}

	/*----------------------------------------------------------
	 * APPLET_CMD_ERASE_REGION:
	 * TODO: Check if this is mandatory
	 *----------------------------------------------------------*/
	else if (pMailbox->command == APPLET_CMD_ERASE_ROW) {
		TRACE_INFO("APPLET_CMD_ERASE_PAGE command \n\r");

		/* Check if at least one page of the region has been locked */
		if (nvm_is_page_locked(pMailbox->argument.inputEraseRow.row) != 0) {
			TRACE_INFO("Error page locked \n\r");
			pMailbox->status = APPLET_PROTECT_FAIL;
			goto exit;
		}

		//We won't erase the monitor in flash (region 0)
		//we'll keep the first x pages containing the monitor untouched
		if (((pMailbox->argument.inputEraseRow.row) * flashNbPagesOneRow)
				< (MONITOR_SIZE / flashPageSize)) {
			TRACE_INFO("Error page locked \n\r");
			pMailbox->status = APPLET_PROTECT_FAIL;
			goto exit;
		}

		/* Erase the flash row */
		if (nvm_erase_row(pMailbox->argument.inputEraseRow.row * 
				flashNbPagesOneRow *FLASH_PAGE_SIZE) != STATUS_OK) {
			TRACE_INFO("Flash erase failed! \n\r");
			pMailbox->status = APPLET_ERASE_FAIL;
			goto exit;
		}
		lastWrittenAddr = 0;
		TRACE_INFO("Full erase achieved\n\r");
		pMailbox->status = APPLET_SUCCESS;
	}

	/*-----------------------------------------------------------
	 * ERASE APP SECTION :
	 *-----------------------------------------------------------*/
	else if (pMailbox->command == APPLET_CMD_ERASE_APP) {
		row = pMailbox->argument.inputEraseApp.start_row + 32 - 1;
		TRACE_INFO("ERASE APP command \n\r");

		do {
			/* Erase the flash row */
			while (nvm_erase_row(row * 4 * FLASH_PAGE_SIZE) != STATUS_OK);
			row++;
		} while(row < pMailbox->argument.inputEraseApp.end_row);

		TRACE_INFO("Application area erased\n\r");
		pMailbox->status = APPLET_SUCCESS;
	}

	/*----------------------------------------------------------
	 * LOCK SECTOR/REGION:
	 *----------------------------------------------------------*/
	else if (pMailbox->command == APPLET_CMD_LOCK) {
		TRACE_INFO("LOCK command \n\r");

		status = nvm_execute_command(NVM_COMMAND_LOCK_REGION,
			(pMailbox->argument.inputLock.row * flashLockRegionSize), 0);

		if (status != STATUS_OK) {
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

		status = nvm_execute_command(NVM_COMMAND_UNLOCK_REGION,
			(pMailbox->argument.inputUnlock.row * flashLockRegionSize), 0);

		if (status != STATUS_OK) {
			TRACE_INFO("Unlock failed! \n\r");
			pMailbox->status = APPLET_UNPROTECT_FAIL;
			goto exit;
		}

		TRACE_INFO("Unlock sector achieved\n\r");
		pMailbox->status = APPLET_SUCCESS;
	}

	/*----------------------------------------------------------
	 * READ LOCKS:
	 *----------------------------------------------------------*/
	else if (pMailbox->command == APPLET_CMD_READ_LOCKS) {
		TRACE_INFO("READ LOCKS command \n\r");

		*((uint16_t *)(pMailbox->argument.outputReadLocks.bufferAddr)) = NVMCTRL->LOCK.reg;
		TRACE_INFO("Reading Locks achieved");
		pMailbox->status = APPLET_SUCCESS;
	}

	/*----------------------------------------------------------
	 * READ FUSES:
	 *----------------------------------------------------------*/
	else if (pMailbox->command == APPLET_CMD_READ_FUSES) {
		TRACE_INFO("READ FUSES command \n\r");

		*((uint64_t *)(pMailbox->argument.outputReadFuses.bufferAddr)) = *(uint64_t *)NVMCTRL_USER;

		TRACE_INFO("Reading fuses achieved");
		pMailbox->status = APPLET_SUCCESS;
	}

	/*----------------------------------------------------------
	 * SET SECURITY BIT :
	 *----------------------------------------------------------*/
	else if (pMailbox->command == APPLET_CMD_SECURITY) {
		if (pMailbox->argument.inputSecurity.action > 0) {
			TRACE_INFO("Setting secure state! \n\r");
			//flashcalw_activate_security_bit();
			nvm_execute_command(NVM_COMMAND_SET_SECURITY_BIT, 0, 0);
		}

		TRACE_INFO("Security bit activated\n\r");
		pMailbox->status = APPLET_SUCCESS;
	}


exit:
	/* Acknowledge the end of command */
	TRACE_INFO("\tEnd of Applet %x %x.\n\r",
				(uint32_t)pMailbox->command,
				(uint32_t)pMailbox->status);
	/* Notify the host application of the end of the command processing */
	pMailbox->command = ~(pMailbox->command);
	
	SERCOM3->USART.DATA.reg = 0x06;
	return 0;
}

