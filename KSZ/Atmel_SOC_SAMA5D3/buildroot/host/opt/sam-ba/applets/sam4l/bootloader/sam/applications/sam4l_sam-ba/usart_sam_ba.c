/**
 * \file
 *
 * \brief USART functions for SAM-BA on SAM4L
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
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

#include <asf.h>
#include "usart_sam_ba.h"
#include "conf_board.h"

//Local reference to current Usart instance in use with this driver
Usart * p_usart;

//Variable to let the main task select the appropriate communication interface
volatile uint8_t b_sharp_received;

//RX and TX Buffers + rw pointers for each buffer
volatile uint8_t buffer_rx_usart[USART_BUFFER_SIZE];

volatile uint8_t idx_rx_read;
volatile uint8_t idx_rx_write;

volatile uint8_t buffer_tx_usart[USART_BUFFER_SIZE];

volatile uint8_t idx_tx_read;
volatile uint8_t idx_tx_write;

// Test for timeout in AT91F_GetChar
uint8_t error_timeout;
uint16_t size_of_data;
uint8_t mode_of_transfer;

//Define the appropriate handler name using CONF_SAMBA_USART define
void ATPASTE3( USART, CONF_SAMBA_USART, _Handler)
()
{
	uint8_t u8tmp;
	if(p_usart->CSR&US_USART_CSR_RXRDY)
	{ //A new char is available in rx buffer
		u8tmp = p_usart->RHR;
		if(u8tmp == SHARP_CHARACTER)
		b_sharp_received = true;

		buffer_rx_usart[idx_rx_write] = u8tmp;
		idx_rx_write = (idx_rx_write+1)&(USART_BUFFER_SIZE-1);
	}

	if(p_usart->CSR&US_USART_CSR_TXRDY)
	{ //The tx buffer is free
		if(idx_tx_read!=idx_tx_write)
		{
			p_usart->THR = buffer_tx_usart[idx_tx_read];
			idx_tx_read = (idx_tx_read+1)&(USART_BUFFER_SIZE-1);
		}
		else
		{
			p_usart->IDR = US_USART_IER_TXRDY;
		}
	}
}

/*! \brief Open the given USART
 * \param Usart instance
 * \param Requested baudrate
 * \param Usart Input clock
 */
uint32_t usart_open(Usart * p_usart_inst, uint32_t baudrate, uint32_t clockfreq) {
	uint32_t over;
	uint32_t cd_fp;
	uint32_t cd;
	uint32_t fp;

	p_usart = p_usart_inst;

	/* Reset mode and other registers that could cause unpredictable behavior after reset. */
	p_usart->MR = 0;
	p_usart->RTOR = 0;
	p_usart->TTGR = 0;

	/* Calculate the receiver sampling divide of baudrate clock. */
	if (clockfreq >= HIGH_FRQ_SAMPLE_DIV * baudrate) {
		over = HIGH_FRQ_SAMPLE_DIV;
	} else {
		over = LOW_FRQ_SAMPLE_DIV;
	}

	/* Calculate the clock divider according to the fraction calculated formula. */
	cd_fp = (8 * clockfreq + (over * baudrate) / 2) / (over * baudrate);
	cd = cd_fp >> 3;
	fp = cd_fp & 0x07;
	if (cd < MIN_CD_VALUE || cd > MAX_CD_VALUE) {
		return 1;
	}

	/* Configure the OVER bit in MR register. */
	if (over == 8) {
		p_usart->MR |= US_USART_MR_OVER;
	}

	/* Configure the baudrate generate register. */
	p_usart->BRGR = (cd << US_BRGR_CD_Pos) | (fp << US_BRGR_FP_Pos);

	//Default configuration for SAM-BA : 8N1
	p_usart->MR |= US_USART_MR_MODE_NORMAL | US_USART_MR_CHRL_8
	        | US_USART_MR_PAR_NONE | US_USART_MR_NBSTOP_1;

	NVIC_ClearPendingIRQ(CONF_SAMBA_USART_IRQNUMBER);
	NVIC_SetPriority(CONF_SAMBA_USART_IRQNUMBER, 1);
	NVIC_EnableIRQ(CONF_SAMBA_USART_IRQNUMBER);

#if	USART_USE_INTERRUPTS
	p_usart->IER = US_USART_IER_RXRDY;
#endif

	p_usart->CR = US_USART_CR_RXEN | US_USART_CR_TXEN;
	//Initialize flag
	b_sharp_received = false;
	idx_rx_read = 0;
	idx_rx_write = 0;
	idx_tx_read = 0;
	idx_tx_write = 0;

	error_timeout = 0;

	return 0;
}

/*! \brief Configures communication line
 *
 */
uint32_t usart_close(void) {
	p_usart->CR = US_USART_CR_RXDIS | US_USART_CR_TXDIS;
	p_usart->IDR = US_USART_IDR_RXRDY | US_USART_IDR_TXRDY;
	return (0);
}

/**
 * \brief Puts a byte on usart line
 * The type int is used to support printf redirection from compiler LIB.
 *
 * \param value      Value to put
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
int usart_putc(int value) {
#if	USART_USE_INTERRUPTS
	//Warning : no buffer overrun control !
	buffer_tx_usart[idx_tx_write] = value;
	idx_tx_write = (idx_tx_write+1)&(USART_BUFFER_SIZE-1);
	//Enable tx rdy interrupt
	p_usart->IER = US_USART_IER_TXRDY;
	return(1);
#else
	//Wait until output buffer is free
	while ((p_usart->CSR & US_USART_CSR_TXRDY) == 0);
	p_usart->THR = value;
	return(1);
#endif
}

int usart_getc(void) {
	int retval;
#if	USART_USE_INTERRUPTS
	while(!(usart_is_rx_ready()));
	retval = buffer_rx_usart[idx_rx_read];
	idx_rx_read = (idx_rx_read+1)&(USART_BUFFER_SIZE-1);
	return(retval);
#else
	//Wait until input buffer is filled
	while ((p_usart->CSR & US_USART_CSR_RXRDY) == 0);
	retval = p_usart->RHR;
	return(retval);
#endif

}

int usart_sharp_received(void) {
#if	USART_USE_INTERRUPTS
	return(b_sharp_received);
#else
	if (usart_is_rx_ready()) {
		if (usart_getc() == SHARP_CHARACTER)
			return (true);
	}
	return (false);
#endif
}

bool usart_is_rx_ready(void) {
#if	USART_USE_INTERRUPTS
	return(idx_rx_read!=idx_rx_write);
#else
	return((p_usart->CSR&US_USART_CSR_RXRDY) != 0);
#endif
}

int usart_readc(void) {
	int retval;
	retval = buffer_rx_usart[idx_rx_read];
	idx_rx_read = (idx_rx_read + 1) & (USART_BUFFER_SIZE - 1);
	return (retval);
}
//Send given data (polling)
uint32_t usart_putdata(void const* data, uint32_t length) {
	uint32_t i;
	uint8_t* ptrdata;
	ptrdata = (uint8_t*) data;
	for (i = 0; i < length; i++) {
		usart_putc(*ptrdata);
		ptrdata++;
	}
	return (i);
}

//Get data from comm. device
uint32_t usart_getdata(void* data, uint32_t length) {
	uint8_t* ptrdata;
	ptrdata = (uint8_t*) data;
	*ptrdata = usart_getc();
	return (1);
}

//*----------------------------------------------------------------------------
//* \fn    add_crc
//* \brief Compute the CRC
//*----------------------------------------------------------------------------
unsigned short add_crc(char ptr, unsigned short crc) {

	unsigned short cmpt;

	crc = crc ^ (int) ptr << 8;

	for (cmpt = 0; cmpt < 8; cmpt++) {
		if (crc & 0x8000)
			crc = crc << 1 ^ CRC16POLY;
		else
			crc = crc << 1;
	}

	return (crc & 0xFFFF);
}

//*----------------------------------------------------------------------------
//* \fn    getbytes
//* \brief
//*----------------------------------------------------------------------------
static uint16_t getbytes(uint8_t *ptr_data, uint16_t length) {
	uint16_t crc = 0;
	uint16_t cpt;
	uint8_t c;

	for (cpt = 0; cpt < length; ++cpt) {
		c = usart_getc();
		if (error_timeout)
			return 1;
		crc = add_crc(c, crc);
		//crc = (crc << 8) ^ xcrc16tab[(crc>>8) ^ c];
		if (size_of_data || mode_of_transfer) {
			*ptr_data++ = c;
			if (length == PKTLEN_128)
				size_of_data--;
		}
	}

	return crc;
}

//*----------------------------------------------------------------------------
//* \fn    putPacket
//* \brief Used by Xup to send packets.
//*----------------------------------------------------------------------------
static int putPacket(uint8_t *tmppkt, uint8_t sno) {
	uint32_t i;
	uint16_t chksm;
	uint8_t data;

	chksm = 0;

	usart_putc(SOH);

	usart_putc(sno);
	usart_putc((uint8_t) ~(sno));

	for (i = 0; i < PKTLEN_128; i++) {
		if (size_of_data || mode_of_transfer) {
			data = *tmppkt++;
			size_of_data--;
		} else
			data = 0x00;

		usart_putc(data);

		//chksm = (chksm<<8) ^ xcrc16tab[(chksm>>8)^data];
		chksm = add_crc(data, chksm);
	}

	/* An "endian independent way to extract the CRC bytes. */
	usart_putc((uint8_t) (chksm >> 8));
	usart_putc((uint8_t) chksm);

	return (usart_getc()); /* Wait for ack */
}

//*----------------------------------------------------------------------------
//* \fn    getPacket
//* \brief Used by Xdown to retrieve packets.
//*----------------------------------------------------------------------------
uint8_t getPacket(uint8_t *ptr_data, uint8_t sno) {
	uint8_t seq[2];
	uint16_t crc, xcrc;

	getbytes(seq, 2);
	xcrc = getbytes(ptr_data, PKTLEN_128);
	if (error_timeout)
		return (false);

	/* An "endian independent way to combine the CRC bytes. */
	crc = (uint16_t) usart_getc() << 8;
	crc += (uint16_t) usart_getc();

	if (error_timeout == 1)
		return (false);

	if ((crc != xcrc) || (seq[0] != sno) || (seq[1] != (uint8_t) (~sno))) {
		usart_putc(CAN);
		return (false);
	}

	usart_putc(ACK);
	return (true);
}

//*----------------------------------------------------------------------------
//* \fn    Xup
//* \brief Called when a transfer from target to host is being made (considered
//*        an upload).
//*----------------------------------------------------------------------------
//static void Xup(char *ptr_data, uint16_t length)
//Send given data (polling) using xmodem (if necessary)
uint32_t usart_putdata_xmd(void const* data, uint32_t length) {
	uint8_t c, sno = 1;
	uint8_t done;
	uint8_t * ptr_data = (uint8_t *) data;
	error_timeout = 0;
	if (!length)
		mode_of_transfer = 1;
	else {
		size_of_data = length;
		mode_of_transfer = 0;
	}

	if (length & (PKTLEN_128 - 1)) {
		length += PKTLEN_128;
		length &= ~(PKTLEN_128 - 1);
	}

	/* Startup synchronization... */
	/* Wait to receive a NAK or 'C' from receiver. */
	done = 0;
	while (!done) {
		c = (uint8_t) usart_getc();
		if (error_timeout) { // Test for timeout in usart_getc
			error_timeout = 0;
			c = (uint8_t) usart_getc();
			if (error_timeout) {
				error_timeout = 0;
				return (0);
//                return -2;
			}
		}
		switch (c) {
		case NAK:
			done = 1;
			// ("CSM");
			break;
		case 'C':
			done = 1;
			// ("CRC");
			break;
		case 'q': /* ELS addition, not part of XMODEM spec. */
			return (0);
//           return(0);
		default:
			break;
		}
	}

	done = 0;
	sno = 1;
	while (!done) {
		c = (uint8_t) putPacket((uint8_t *) ptr_data, sno);
		if (error_timeout) { // Test for timeout in usart_getc
			error_timeout = 0;
			return (0);
//            return (-1);
		}
		switch (c) {
		case ACK:
			++sno;
			length -= PKTLEN_128;
			ptr_data += PKTLEN_128;
			// ("A");
			break;
		case NAK:
			// ("N");
			break;
		case CAN:
		case EOT:
		default:
			done = 0;
			break;
		}
		if (!length) {
			usart_putc(EOT);
			usart_getc(); /* Flush the ACK */
			break;
		}
		// ("!");
	}

	mode_of_transfer = 0;
	// ("Xup_done.");
	return (1);
	//    return(0);
}

//*----------------------------------------------------------------------------
//* \fn    Xdown
//* \brief Called when a transfer from host to target is being made (considered
//*        an download).
//*----------------------------------------------------------------------------
//static void Xdown(char *ptr_data, uint16_t length)
//Get data from comm. device using xmodem (if necessary)
uint32_t usart_getdata_xmd(void* data, uint32_t length) {
	uint32_t timeout;
	char c;
	uint8_t * ptr_data = (uint8_t *) data;
	uint32_t b_run, nbr_of_timeout = 100;
	uint8_t sno = 0x01;
	uint32_t data_transfered = 0;

	//Copied from legacy source code ... might need some tweaking
	uint32_t loops_per_second = CONFIG_SYSCLK_CPU_FREQ / 10;

	error_timeout = 0;

	if (length == 0)
		mode_of_transfer = 1;
	else {
		size_of_data = length;
		mode_of_transfer = 0;
	}

	/* Startup synchronization... */
	/* Continuously send NAK or 'C' until sender responds. */
	// ("Xdown");
	while (1) {
		usart_putc('C');
		timeout = loops_per_second;
		while (!(usart_is_rx_ready()) && timeout)
			timeout--;
		if (timeout)
			break;

		if (!(--nbr_of_timeout))
			return (0);
//            return -1;
	}

	b_run = true;
	// ("Got response");
	while (b_run != false) {
		c = (char) usart_getc();
		if (error_timeout) { // Test for timeout in usart_getc
			error_timeout = 0;
			return (0);
//            return (-1);
		}
		switch (c) {
		case SOH: /* 128-byte incoming packet */
			// ("O");
			b_run = getPacket(ptr_data, sno);
			if (error_timeout) { // Test for timeout in usart_getc
				error_timeout = 0;
				return (0);
//                return (-1);
			}
			if (b_run == true) {
				++sno;
				ptr_data += PKTLEN_128;
				data_transfered += PKTLEN_128;
			}
			break;
		case EOT: // ("E");
			usart_putc(ACK);
			b_run = false;
			break;
		case CAN: // ("C");
		case ESC: /* "X" User-invoked abort */
		default:
			b_run = false;
			break;
		}
		// ("!");
	}
	mode_of_transfer = 0;
	return (true);
//    return(b_run);
}

