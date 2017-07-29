/**
 * \file
 *
 * \brief SAM D20 Non Volatile Memory driver
 *
 * Copyright (C) 2012-2013 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
#include "nvm.h"
#include <string.h>


/**
 * \internal Internal device instance struct
 *
 * This struct contains information about the NVM module which is
 * often used by the different functions. The information is loaded
 * into the struct in the nvm_init() function.
 */
struct _nvm_module {
	/** Number of bytes contained per page */
	uint16_t page_size;
	/** Total number of pages in the NVM memory */
	uint16_t number_of_pages;
	/** If \c false, a page write command will be issued automatically when the
	 *  page buffer is full. */
	bool manual_page_write;
};

/**
 * \internal Instance of the internal device struct
 */
static struct _nvm_module _nvm_dev;

/**
 * \internal Pointer to the NVM MEMORY region start address
 */
#define NVM_MEMORY        ((volatile uint16_t *)FLASH_ADDR)

/**
 * \internal Pointer to the NVM USER MEMORY region start address
 */
#define NVM_USER_MEMORY   ((volatile uint16_t *)NVMCTRL_USER)


/**
 * \brief Sets the up the NVM hardware module based on the configuration.
 *
 * Writes a given configuration of a NVM controller configuration to the
 * hardware module, and initializes the internal device struct
 *
 * \param[in] config    Configuration settings for the NVM controller
 *
 * \note The security bit must be cleared in order successfully use this
 *       function. This can only be done by a chip erase.
 *
 * \return Status of the configuration procedure.
 *
 * \retval STATUS_OK      If the initialization was a success
 * \retval STATUS_BUSY    If the module was busy when the operation was attempted
 * \retval STATUS_ERR_IO  If the security bit has been set, preventing the
 *                        EEPROM and/or auxiliary space configuration from being
 *                        altered
 */
enum status_code nvm_set_config(void)
{
	/* Get a pointer to the module hardware instance */
	Nvmctrl *const nvm_module = NVMCTRL;

	/* Initialize the internal device struct */
	_nvm_dev.page_size         = (8 << nvm_module->PARAM.bit.PSZ);
	_nvm_dev.number_of_pages   = nvm_module->PARAM.bit.NVMP;
	_nvm_dev.manual_page_write = false;

	return STATUS_OK;
}

/**
 * \brief Executes a command on the NVM controller.
 *
 * Executes an asynchronous command on the NVM controller, to perform a requested
 * action such as a NVM page read or write operation.
 *
 * \note The function will return before the execution of the given command is
 *       completed.
 *
 * \param[in] command    Command to issue to the NVM controller
 * \param[in] address    Address to pass to the NVM controller in NVM memory
 *                       space
 * \param[in] parameter  Parameter to pass to the NVM controller, not used
 *                       for this driver
 *
 * \return Status of the attempt to execute a command.
 *
 * \retval STATUS_OK               If the command was accepted and execution
 *                                 is now in progress
 * \retval STATUS_BUSY             If the NVM controller was already busy
 *                                 executing a command when the new command
 *                                 was issued
 * \retval STATUS_ERR_IO           If the command was invalid due to memory or
 *                                 security locking
 * \retval STATUS_ERR_INVALID_ARG  If the given command was invalid or
 *                                 unsupported
 * \retval STATUS_ERR_BAD_ADDRESS  If the given address was invalid
 */
enum status_code nvm_execute_command(
		const enum nvm_command command,
		const uint32_t address,
		const uint32_t parameter)
{
	/* Get a pointer to the module hardware instance */
	Nvmctrl *const nvm_module = NVMCTRL;

	/* Clear error flags */
	nvm_module->STATUS.reg &= ~NVMCTRL_STATUS_MASK;

	/* Check if the module is busy */
	if (!nvm_is_ready()) {
		return STATUS_BUSY;
	}
	
	if(command == NVM_COMMAND_LOCK_REGION || command == NVM_COMMAND_UNLOCK_REGION)
	{
		nvm_module->ADDR.reg = (uintptr_t)&NVM_MEMORY[address / 4];
	}
	else if(command == NVM_COMMAND_SET_SECURITY_BIT)
	{
		;
	}
	else
	{
		return STATUS_ERR_INVALID_ARG;
	}

	/* Set command */
	nvm_module->CTRLA.reg = command | NVMCTRL_CTRLA_CMDEX_KEY;

	return STATUS_OK;
}

/**
 * \brief Updates an arbitrary section of a page with new data.
 *
 * Writes from a buffer to a given page in the NVM memory, retaining any
 * unmodified data already stored in the page.
 *
 * \warning This routine is unsafe if data integrity is critical; a system reset
 *          during the update process will result in up to one row of data being
 *          lost. If corruption must be avoided in all circumstances (including
 *          power loss or system reset) this function should not be used.
 *
 * \param[in]  destination_address  Destination page address to write to
 * \param[in]  buffer               Pointer to buffer where the data to write is
 *                                  stored
 * \param[in]  offset               Number of bytes to offset the data write in
 *                                  the page
 * \param[in]  length               Number of bytes in the page to update
 *
 * \return Status of the attempt to update a page.
 *
 * \retval STATUS_OK               Requested NVM memory page was successfully
 *                                 read
 * \retval STATUS_BUSY             NVM controller was busy when the operation
 *                                 was attempted
 * \retval STATUS_ERR_BAD_ADDRESS  The requested address was outside the
 *                                 acceptable range of the NVM memory region
 * \retval STATUS_ERR_INVALID_ARG  The supplied length and offset was invalid
 */
enum status_code nvm_update_buffer(
		const uint32_t destination_address,
		uint8_t *const buffer,
		uint16_t offset,
		uint16_t length)
{
	enum status_code error_code = STATUS_OK;
	uint8_t row_buffer[NVMCTRL_ROW_PAGES][NVMCTRL_PAGE_SIZE];

	/* Ensure the read does not overflow the page size */
	if ((offset + length) > _nvm_dev.page_size) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Calculate the starting row address of the page to update */
	uint32_t row_start_address =
			destination_address & ~((_nvm_dev.page_size * NVMCTRL_ROW_PAGES) - 1);

	/* Read in the current row contents */
	for (uint32_t i = 0; i < NVMCTRL_ROW_PAGES; i++) {
		do
		{
			error_code = nvm_read_buffer(
					row_start_address + (i * _nvm_dev.page_size),
					row_buffer[i], _nvm_dev.page_size);
		} while (error_code == STATUS_BUSY);

		if (error_code != STATUS_OK) {
			return error_code;
		}
	}

	/* Calculate the starting page in the row that is to be updated */
	uint8_t page_in_row =
			(destination_address % (_nvm_dev.page_size * NVMCTRL_ROW_PAGES)) /
			_nvm_dev.page_size;

	/* Update the specified bytes in the page buffer */
	for (uint32_t i = 0; i < length; i++) {
		row_buffer[page_in_row][offset + i] = buffer[i];
	}

	system_interrupt_enter_critical_section();

	/* Erase the row */
	do
	{
		error_code = nvm_erase_row(row_start_address);
	} while (error_code == STATUS_BUSY);

	if (error_code != STATUS_OK) {
		return error_code;
	}

	/* Write the updated row contents to the erased row */
	for (uint32_t i = 0; i < NVMCTRL_ROW_PAGES; i++) {
		do
		{
			error_code = nvm_write_buffer(
					row_start_address + (i * _nvm_dev.page_size),
					row_buffer[i], _nvm_dev.page_size);
		} while (error_code == STATUS_BUSY);

		if (error_code != STATUS_OK) {
			return error_code;
		}
	}

	system_interrupt_leave_critical_section();

	return error_code;
}

/**
 * \brief Writes a number of bytes to a page in the NVM memory region
 *
 * Writes from a buffer to a given page address in the NVM memory.
 *
 * \param[in]  destination_address  Destination page address to write to
 * \param[in]  buffer               Pointer to buffer where the data to write is
 *                                  stored
 * \param[in]  length               Number of bytes in the page to write
 *
 * \note If writing to a page that has previously been written to, the page's
 *       row should be erased (via \ref nvm_erase_row()) before attempting to
 *       write new data to the page.
 *
 * \return Status of the attempt to write a page.
 *
 * \retval STATUS_OK               Requested NVM memory page was successfully
 *                                 read
 * \retval STATUS_BUSY             NVM controller was busy when the operation
 *                                 was attempted
 * \retval STATUS_ERR_BAD_ADDRESS  The requested address was outside the
 *                                 acceptable range of the NVM memory region or
 *                                 not aligned to the start of a page
 * \retval STATUS_ERR_INVALID_ARG  The supplied write length was invalid
 */
enum status_code nvm_write_buffer(
		const uint32_t destination_address,
		const uint8_t *buffer,
		uint16_t length)
{
	/* Get a pointer to the module hardware instance */
	Nvmctrl *const nvm_module = NVMCTRL;

	/* Check if the module is busy */
	if (!nvm_is_ready()) {
		return STATUS_BUSY;
	}

	/* Erase the page buffer before buffering new data */
	nvm_module->CTRLA.reg = NVM_COMMAND_PAGE_BUFFER_CLEAR | NVMCTRL_CTRLA_CMDEX_KEY;

	/* Check if the module is busy */
	while (!nvm_is_ready()) {
		/* Force-wait for the buffer clear to complete */
	}

	/* Clear error flags */
	nvm_module->STATUS.reg &= ~NVMCTRL_STATUS_MASK;

	uint32_t nvm_address = destination_address / 2;

	/* NVM _must_ be accessed as a series of 16-bit words, perform manual copy
	 * to ensure alignment */
	for (uint16_t i = 0; i < length; i += 2) {
		uint16_t data;

		/* Copy first byte of the 16-bit chunk to the temporary buffer */
		data = buffer[i];

		/* If we are not at the end of a write request with an odd byte count,
		 * store the next byte of data as well */
		if (i < (length - 1)) {
			data |= (buffer[i + 1] << 8);
		}

		/* Store next 16-bit chunk to the NVM memory space */
		NVM_MEMORY[nvm_address++] = data;
	}

	return STATUS_OK;
}

/**
 * \brief Reads a number of bytes from a page in the NVM memory region
 *
 * Reads a given number of bytes from a given page address in the NVM memory
 * space into a buffer.
 *
 * \param[in]  source_address  Source page address to read from
 * \param[out] buffer          Pointer to a buffer where the content of the read
 *                             page will be stored
 * \param[in]  length          Number of bytes in the page to read
 *
 * \return Status of the page read attempt.
 *
 * \retval STATUS_OK               Requested NVM memory page was successfully
 *                                 read
 * \retval STATUS_BUSY             NVM controller was busy when the operation
 *                                 was attempted
 * \retval STATUS_ERR_BAD_ADDRESS  The requested address was outside the
 *                                 acceptable range of the NVM memory region or
 *                                 not aligned to the start of a page
 * \retval STATUS_ERR_INVALID_ARG  The supplied read length was invalid
 */
enum status_code nvm_read_buffer(
		const uint32_t source_address,
		uint8_t *const buffer,
		uint16_t length)
{
	/* Get a pointer to the module hardware instance */
	Nvmctrl *const nvm_module = NVMCTRL;

	/* Check if the module is busy */
	if (!nvm_is_ready()) {
		return STATUS_BUSY;
	}

	/* Clear error flags */
	nvm_module->STATUS.reg &= ~NVMCTRL_STATUS_MASK;

	uint32_t page_address = source_address / 2;

	/* NVM _must_ be accessed as a series of 16-bit words, perform manual copy
	 * to ensure alignment */
	for (uint16_t i = 0; i < length; i += 2) {
		/* Fetch next 16-bit chunk from the NVM memory space */
		uint16_t data = NVM_MEMORY[page_address++];

		/* Copy first byte of the 16-bit chunk to the destination buffer */
		buffer[i] = (data & 0xFF);

		/* If we are not at the end of a read request with an odd byte count,
		 * store the next byte of data as well */
		if (i < (length - 1)) {
			buffer[i + 1] = (data >> 8);
		}
	}

	return STATUS_OK;
}

/**
 * \brief Erases a row in the NVM memory space
 *
 * Erases a given row in the NVM memory region.
 *
 * \param[in] row_address  Address of the row to erase
 *
 * \return Status of the NVM row erase attempt.
 *
 * \retval STATUS_OK               Requested NVM memory row was successfully
 *                                 erased
 * \retval STATUS_BUSY             NVM controller was busy when the operation
 *                                 was attempted
 * \retval STATUS_ERR_BAD_ADDRESS  The requested row address was outside the
 *                                 acceptable range of the NVM memory region or
 *                                 not aligned to the start of a row
 */
enum status_code nvm_erase_row(
		const uint32_t row_address)
{
	if (row_address < 0x00000800)
		return STATUS_ERR_INVALID_ARG;
		
	/* Get a pointer to the module hardware instance */
	Nvmctrl *const nvm_module = NVMCTRL;

	/* Check if the module is busy */
	if (!nvm_is_ready()) {
		return STATUS_BUSY;
	}

	/* Clear error flags */
	nvm_module->STATUS.reg &= ~NVMCTRL_STATUS_MASK;

	/* Set address and command */
	nvm_module->ADDR.reg  = (uintptr_t)&NVM_MEMORY[row_address / 4];
	nvm_module->CTRLA.reg = NVM_COMMAND_ERASE_ROW | NVMCTRL_CTRLA_CMDEX_KEY;

	return STATUS_OK;
}

/**
 * \brief Reads the parameters of the NVM controller.
 *
 * Retrieves the page size, number of pages and other configuration settings
 * of the NVM region.
 *
 * \param[out] parameters    Parameter structure, which holds page size and
 *                           number of pages in the NVM memory
 */
void nvm_get_parameters(
		struct nvm_parameters *const parameters)
{
	/* Sanity check parameters */
	Assert(parameters);

	/* Get a pointer to the module hardware instance */
	Nvmctrl *const nvm_module = NVMCTRL;

	/* Clear error flags */
	nvm_module->STATUS.reg &= ~NVMCTRL_STATUS_MASK;

	/* Read out from the PARAM register */
	uint32_t param_reg = nvm_module->PARAM.reg;

	/* Mask out page size exponent and convert to a number of bytes */
	parameters->page_size =
			8 << ((param_reg & NVMCTRL_PARAM_PSZ_Msk) >> NVMCTRL_PARAM_PSZ_Pos);

	/* Mask out number of pages count */
	parameters->nvm_number_of_pages =
			(param_reg & NVMCTRL_PARAM_NVMP_Msk) >> NVMCTRL_PARAM_NVMP_Pos;

	/* Read the current EEPROM fuse value from the USER row */
	uint16_t eeprom_fuse_value =
			(NVM_USER_MEMORY[NVMCTRL_FUSES_EEPROM_SIZE_Pos / 16] &
			NVMCTRL_FUSES_EEPROM_SIZE_Msk) >> NVMCTRL_FUSES_EEPROM_SIZE_Pos;

	/* Translate the EEPROM fuse byte value to a number of NVM pages */
	if (eeprom_fuse_value == 7) {
		parameters->eeprom_number_of_pages = 0;
	}
	else {
		parameters->eeprom_number_of_pages =
				NVMCTRL_ROW_PAGES << (6 - eeprom_fuse_value);
	}

	/* Read the current BOOTSZ fuse value from the USER row */
	uint16_t boot_fuse_value =
			(NVM_USER_MEMORY[NVMCTRL_FUSES_BOOTPROT_Pos / 16] &
			NVMCTRL_FUSES_BOOTPROT_Msk) >> NVMCTRL_FUSES_BOOTPROT_Pos;

	/* Translate the BOOTSZ fuse byte value to a number of NVM pages */
	if (boot_fuse_value == 7) {
		parameters->bootloader_number_of_pages = 0;
	}
	else {
		parameters->bootloader_number_of_pages =
				NVMCTRL_ROW_PAGES << (7 - boot_fuse_value);
	}
}

/**
 * \brief Checks whether the page region is locked
 *
 * Extracts the region to which the given page belongs and checks whether
 * that region is locked.
 *
 * \param[in] page_number    Page number to be checked
 *
 * \return Page lock status
 *
 * \retval true              Page is locked
 * \retval false             Page is not locked
 *
 */
bool nvm_is_page_locked(uint16_t page_number)
{
	uint16_t pages_in_region;
	uint16_t region_number;

	/* Get a pointer to the module hardware instance */
	Nvmctrl *const nvm_module = NVMCTRL;

	/* Get number of pages in a region */
	pages_in_region = _nvm_dev.number_of_pages /16;

	/* Get region for given page */
	region_number = page_number / pages_in_region;

	return !(nvm_module->LOCK.reg & (1 << region_number));
}

/**
 * \internal
 * \name Fusebit mask for reserved bits
 *
 * These macros create a fuse bit mask for reserved bits. These bits should always read 1.
 *
 * @{
 */
#define _NVM_FUSEBITS_0_RESERVED_BITS ~(NVMCTRL_FUSES_BOOTPROT_Msk | NVMCTRL_FUSES_EEPROM_SIZE_Msk | \
	SYSCTRL_FUSES_BOD33USERLEVEL_Msk | SYSCTRL_FUSES_BOD33_EN_Msk | SYSCTRL_FUSES_BOD33_ACTION_Msk | \
	SYSCTRL_FUSES_BOD12USERLEVEL_Msk | SYSCTRL_FUSES_BOD12_EN_Msk | SYSCTRL_FUSES_BOD12_ACTION_Msk | \
	WDT_FUSES_ENABLE_Msk | WDT_FUSES_ALWAYSON_Msk | WDT_FUSES_PER_Msk | WDT_FUSES_WINDOW_0_Msk)

#define _NVM_FUSEBITS_1_RESERVED_BITS ~(WDT_FUSES_WINDOW_1_Msk | WDT_FUSES_EWOFFSET_Msk | \
	WDT_FUSES_WEN_Msk | NVMCTRL_FUSES_REGION_LOCKS_Msk)

/** @} */

/**
 * \brief Get fuses from user row
 *
 * Read out the fuse settings from the user row
 *
 * \param[in] fusebits Pointer to a 64bit wide memory buffer of type struct nvm_fusebits
 *
 * \return             Status of read fuses attempt
 *
 * \retval STATUS_OK   This function will always return STATUS_OK
 */
enum status_code nvm_get_fuses (
		struct nvm_fusebits *fusebits)
{
	enum status_code error_code = STATUS_OK;
	uint32_t raw_fusebits[2];

	/* Make sure the module is ready */
	while (!nvm_is_ready()) {
	};

	/* Read the fuse settings in the user row, 64 bit */
	((uint16_t*)&raw_fusebits)[0] = (uint16_t)NVM_MEMORY[NVMCTRL_USER / 2];
	((uint16_t*)&raw_fusebits)[1] = (uint16_t)NVM_MEMORY[(NVMCTRL_USER / 2) + 1];
	((uint16_t*)&raw_fusebits)[2] = (uint16_t)NVM_MEMORY[(NVMCTRL_USER / 2) + 2];
	((uint16_t*)&raw_fusebits)[3] = (uint16_t)NVM_MEMORY[(NVMCTRL_USER / 2) + 3];

	_nvm_translate_raw_fusebits_to_struct(raw_fusebits, fusebits);

	return error_code;
}


///@cond INTERNAL

/**
 * \internal
 * \name Fuse write function states
 *
 * This defines internal states for the fuse write function
 *
 * @{
 */
#define _NVM_SET_FUSES_STATE_ERASE_ROW         0
#define _NVM_SET_FUSES_STATE_ERASE_PAGE_BUFFER 1
#define _NVM_SET_FUSES_STATE_WRITE_FUSES       2
#define _NVM_SET_FUSES_STATE_END               3
/** @} */

///@endcond

/**
 * \brief Set fuses in user row
 *
 * Write new fuse setting to user row
 *
 * \param[in] fusebits Pointer to a 64bit wide memory buffer with new fuse settings
 *
 * \return Status of write attempt
 *
 * \retval STATUS_OK          New fuse settings where written sucessfully to user row
 *
 * \retval STATUS_ERR_IO      Secitity bit is set, user row can not be written
 *
 * \retval STATUS_ERR_IO      Writing of fuses to user row failed
 */
enum status_code nvm_set_fuses(
		struct nvm_fusebits *fusebits)
{
	Nvmctrl *const nvm_module = NVMCTRL;
	uint8_t state = _NVM_SET_FUSES_STATE_ERASE_ROW;
	uint32_t raw_fusebits[2];
	enum status_code err = STATUS_OK;

	/* If the security bit is set, the auxiliary space cannot be written */
	if (nvm_module->STATUS.reg & NVMCTRL_STATUS_SB) {
		return STATUS_ERR_IO;
	}

	/* Enter critcal section to avoid context switching */
	system_interrupt_enter_critical_section();

	do {

		/* Wait for the nvm controller to become ready */
		while (!nvm_is_ready()) {
		}

		/* Has something gone wrong? */
		if (nvm_module->INTFLAG.reg & NVMCTRL_INTFLAG_ERROR) {
			/* Don't bother about what, just clear status flags and return error status*/
			nvm_module->STATUS.reg  |= ~NVMCTRL_STATUS_MASK;
			nvm_module->INTFLAG.reg |= NVMCTRL_INTFLAG_ERROR;

			err = STATUS_ERR_IO;
			break;
		}

		switch (state) {

		case _NVM_SET_FUSES_STATE_ERASE_ROW:
			/* Erase AUX row */
			nvm_module->PARAM.reg = 0;
			nvm_module->ADDR.reg = NVMCTRL_USER / 2;
			nvm_module->CTRLA.reg = NVM_COMMAND_ERASE_AUX_ROW | NVMCTRL_CTRLA_CMDEX_KEY;
			break;

		case _NVM_SET_FUSES_STATE_ERASE_PAGE_BUFFER:
			/* Erase the page buffer before buffering new data */
			nvm_module->CTRLA.reg = NVM_COMMAND_PAGE_BUFFER_CLEAR | NVMCTRL_CTRLA_CMDEX_KEY;
			break;

		case _NVM_SET_FUSES_STATE_WRITE_FUSES:
			_nvm_translate_struct_to_raw_fusebits(fusebits, raw_fusebits);

			/* Write new user row content (address must be converted from 8-bit to 16-bit aligned) */
			NVM_MEMORY[NVMCTRL_USER / 2]       = ((uint16_t*)raw_fusebits)[0];
			NVM_MEMORY[(NVMCTRL_USER / 2) + 1] = ((uint16_t*)raw_fusebits)[1];
			NVM_MEMORY[(NVMCTRL_USER / 2) + 2] = ((uint16_t*)raw_fusebits)[2];
			NVM_MEMORY[(NVMCTRL_USER / 2) + 3] = ((uint16_t*)raw_fusebits)[3];

			nvm_module->CTRLA.reg = NVM_COMMAND_WRITE_AUX_ROW | NVMCTRL_CTRLA_CMDEX_KEY;
			break;

		default:
			/* Should never be executed */
			Assert(false);
			break;
		}

		/* Goto next state */
		state++;

	} while (state != _NVM_SET_FUSES_STATE_END);

	system_interrupt_leave_critical_section();

	return err;
}

