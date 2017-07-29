/*
 * Driver for FTDI USB/SPI controller on Micrel KSZ8692 SoC controller board.
 *
 * Copyright (C) 2010-2015 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/clk.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/workqueue.h>
#include <linux/dma-mapping.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/spi/spi.h>
#include <linux/usb.h>
#include <linux/usbdevice_fs.h>
#include "../usb/core/usb.h"
#include "spi-ftdiusb.h"

#if defined(CONFIG_SPI_FTDI)
extern void pegasus_init_late_call(void);
extern void pegasus_register_late_call(void *);
#endif


static struct usb_device *udev;

static void ftdiusbspi_disconnect(struct usb_interface *intf);
static int alloc_all_urbs(struct ftdiusb_spi *dev);
static int ftdiusb_sendbuf(struct ftdiusb_spi *ks_spi,
	const unsigned char *data, int length);
static int ftdiusb_getbuf(struct ftdiusb_spi *ks_spi, const unsigned char *buf,
	int size);
static int ftdiusb_reset(struct ftdiusb_spi *ks_spi);


static int alloc_all_urbs(struct ftdiusb_spi *dev)
{
	dev->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->rx_urb)
		return false;
	dev->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->tx_urb) {
		usb_free_urb(dev->rx_urb);
		return false;
	}
	dev->intr_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->intr_urb) {
		usb_free_urb(dev->rx_urb);
		usb_free_urb(dev->tx_urb);
		return false;
	}
	dev->ctrl_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->intr_urb) {
		usb_free_urb(dev->rx_urb);
		usb_free_urb(dev->tx_urb);
		usb_free_urb(dev->intr_urb);
		return false;
	}

	return true;
}

static void free_all_urbs(struct ftdiusb_spi *dev)
{
	usb_free_urb(dev->rx_urb);
	usb_free_urb(dev->tx_urb);
	usb_free_urb(dev->intr_urb);
	usb_free_urb(dev->ctrl_urb);
}

static void unlink_all_urbs(struct ftdiusb_spi *dev)
{
	usb_kill_urb(dev->rx_urb);
	usb_kill_urb(dev->tx_urb);
	usb_kill_urb(dev->intr_urb);
	usb_kill_urb(dev->ctrl_urb);
}

static void ftdiusbspi_disconnect(struct usb_interface *intf)
{
	struct ftdiusb_spi *ks_spi = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	if (ks_spi) {
		unlink_all_urbs(ks_spi);
		free_all_urbs(ks_spi);
		kfree(ks_spi->txbuf);
		kfree(ks_spi->rxbuf);
	}
}

static void ftdiusb_initwork(struct work_struct *work);

static int ftdiusbspi_probe(struct usb_interface *intf,
	const struct usb_device_id *id)
{
	struct ftdiusb_spi *ks_spi;
	int ret = 0;

	udev = interface_to_usbdev(intf);
	ks_spi = (void *) id->driver_info;
	if (ks_spi->udev)
		goto probe_done;

	ks_spi->udev = udev;
	usb_set_intfdata(intf, ks_spi);

	/* initialize the work queue for receiving task */
	init_completion(&ks_spi->tx_completion);
	init_completion(&ks_spi->rx_completion);

	ret = ftdiusb_reset(ks_spi);
	/* we need to call ftdiusb_sendbuf in a delay task */
	INIT_WORK(&ks_spi->init_work, ftdiusb_initwork);

	ftdiusb_initwork(&ks_spi->init_work);

	ret = spi_register_master(ks_spi->master);
	if (ret) {
		printk(KERN_DEBUG "register spi master failed!!! ret=%d\n",
			ret);
		goto probe_done;
	}

#ifdef CONFIG_SPI_FTDI
	pegasus_init_late_call();
#endif

probe_done:
	return 0;
}

static struct usb_device_id id_table_combined[] = {
	{ USB_DEVICE(FTDI_VID, FTDI_AMC232_PID) },
	{ USB_DEVICE(FTDI_VID, FTDI_CANUSB_PID) },
	{ USB_DEVICE(FTDI_VID, FTDI_ACTZWAVE_PID) },
	{ USB_DEVICE(FTDI_VID, FTDI_8U232AM_PID) },
	{ USB_DEVICE(FTDI_VID, FTDI_8U232AM_ALT_PID) },
	{ USB_DEVICE(FTDI_VID, FTDI_8U2232C_PID) },
	/* Terminating entry */
	{ }
};

MODULE_DEVICE_TABLE(usb, id_table_combined);

static struct usb_driver ftdiuspspi_driver = {
	.name =		"ftdi_usbspi",
	.probe =	ftdiusbspi_probe,
	.disconnect =	ftdiusbspi_disconnect,
	.id_table =	id_table_combined,
	.no_dynamic_id =	1,
};


static inline struct ftdiusb_spi *to_hw(struct spi_device *sdev)
{
	return spi_master_get_devdata(sdev->master);
}

#if 0
static void ftdiusb_set_clock(struct ftdiusb_spi *ks_spi)
{
	char txbuf[32];
	int bytes = 0;
	unsigned short clkdivisor = 1;
	int highspeed = false;

	if (ks_spi->max_speed_hz > MAX_HIGH_SPEED) {
		/* should not happen */
	/* high speed */
	} else if (ks_spi->max_speed_hz > MAX_LOW_SPEED) {
		highspeed = true;
		clkdivisor = (MAX_HIGH_SPEED) / ks_spi->max_speed_hz - 1;
	/* low speed */
	} else {
		highspeed = false;
		clkdivisor = (MAX_LOW_SPEED) / ks_spi->max_speed_hz - 1;
	}

	if (highspeed)
		/* Disable divide-by-5. */
		txbuf[bytes++] = 0x8a;
	else
		/* Enable divide-by-5. */
		txbuf[bytes++] = 0x8b;

	/* command "set divisor" */
	txbuf[bytes++] = 0x86;
	/* valueL/valueH are (desired_divisor - 1) */
	txbuf[bytes++] = (clkdivisor) & 0xff;
	txbuf[bytes++] = ((clkdivisor) >> 8) & 0xff;
	if (highspeed)
		printk(KERN_DEBUG "[%s] clkdivisor=%d highspeed=%d real_speed=%d\n",
			__func__, clkdivisor, highspeed,
			(MAX_HIGH_SPEED) / (clkdivisor + 1));
	else
		printk(KERN_DEBUG "[%s] clkdivisor=%d highspeed=%d real_speed=%d\n",
			__func__, clkdivisor, highspeed,
			(MAX_LOW_SPEED) / (clkdivisor + 1));
	ftdiusb_sendbuf(ks_spi, txbuf, bytes);
}
#endif

static void transmit_bulk_callback(struct urb *urb)
{
	struct ftdiusb_spi *ks_spi = urb->context;

	if (ks_spi && (urb == ks_spi->tx_urb))
		complete(&ks_spi->tx_completion);
}

static void receiving_bulk_callback(struct urb *urb)
{
	struct ftdiusb_spi *ks_spi = urb->context;

	if (ks_spi && (urb == ks_spi->rx_urb))
		complete(&ks_spi->rx_completion);
}

static int ftdiusb_reset(struct ftdiusb_spi *ks_spi)
{
	struct usbdevfs_ctrltransfer ctrl;
	struct usb_device *usbdev;
	int ret;
	unsigned char *tbuf = 0;

	usbdev = ks_spi->udev;
	/* we do some USB initialization */
	/* reset */
	ctrl.bRequest = SIO_RESET_REQUEST;
	ctrl.bRequestType = FTDI_DEVICE_OUT_REQTYPE;
	ctrl.wValue = SIO_RESET_SIO;
	ctrl.wIndex = 0;
	ctrl.wLength = 0;
	ctrl.timeout = 5000;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
		ctrl.bRequest, ctrl.bRequestType, ctrl.wValue, ctrl.wIndex,
		tbuf, ctrl.wLength, ctrl.timeout);
	if (ret != 0)
		return ret;

	/* set_latency_time */
	ctrl.bRequest = SIO_SET_LATENCY_TIMER_REQUEST;
	ctrl.bRequestType = FTDI_DEVICE_OUT_REQTYPE;
	ctrl.wValue = 0x0002;
	ctrl.wIndex = 0x0001;
	ctrl.wLength = 0;
	ctrl.timeout = 5000;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
		ctrl.bRequest, ctrl.bRequestType, ctrl.wValue, ctrl.wIndex,
		tbuf, ctrl.wLength, ctrl.timeout);
	if (ret != 0)
		return ret;

	/* set bit mode */
	ctrl.bRequest = SIO_SET_BITMODE_REQUEST;
	ctrl.bRequestType = FTDI_DEVICE_OUT_REQTYPE;
	ctrl.wValue = 0x0200;
	ctrl.wIndex = 0x0001;
	ctrl.wLength = 0;
	ctrl.timeout = 5000;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
		ctrl.bRequest, ctrl.bRequestType, ctrl.wValue, ctrl.wIndex,
		tbuf, ctrl.wLength, ctrl.timeout);

	return ret;
}

static int mpsse_3_phase(unsigned char *buf, int phase)
{
	int bytes = 0;

#if 1
phase = 1;
#endif
	buf[bytes++] = phase ? ENABLE_3_PHASE: DISABLE_3_PHASE;
	return bytes;
}

static int mpsse_loopback(unsigned char *buf, int loopback)
{
	int bytes = 0;

	buf[bytes++] = loopback ? LOOPBACK_START : LOOPBACK_END;
	return bytes;
}

static int mpsse_set_clk(unsigned char *buf, unsigned int hz)
{
	unsigned short clkdivisor;
	unsigned char clk_div;
	int bytes = 0;

	if (hz > MAX_LOW_SPEED) {
		clkdivisor = (MAX_HIGH_SPEED) / hz - 1;
		clk_div = DISABLE_CLK_DIV;
	} else {
		clkdivisor = (MAX_LOW_SPEED) / hz - 1;
		clk_div = ENABLE_CLK_DIV;
	}
	buf[bytes++] = clk_div;
	buf[bytes++] = TCK_DIVISOR;
	buf[bytes++] = clkdivisor & 0xff;
	buf[bytes++] = clkdivisor >> 8;
	return bytes;
}

static int mpsse_set_hi(unsigned char *buf, unsigned char val,
	unsigned char dir)
{
	int bytes = 0;

	buf[bytes++] = SET_BITS_HIGH;
	buf[bytes++] = val;
	buf[bytes++] = dir;
	return bytes;
}

static int mpsse_set_lo(unsigned char *buf, unsigned char val,
	unsigned char dir)
{
	int bytes = 0;

	buf[bytes++] = SET_BITS_LOW;
	buf[bytes++] = val;
	buf[bytes++] = dir;
	return bytes;
}

static int mpsse_read(unsigned char *buf, unsigned char mode,
	unsigned short len)
{
	unsigned char spi_mode = mode & SPI_MODE_3;
	unsigned char opcode = MPSSE_DO_READ;
	int bytes = 0;

	if (SPI_MODE_1 == spi_mode || SPI_MODE_2 == spi_mode)
		opcode |= MPSSE_READ_NEG;
#if 0
	if (5 == mode)
		opcode |= MPSSE_BITMODE;
#endif
	if (mode & SPI_LSB_FIRST)
		opcode |= MPSSE_LSB;
	buf[bytes++] = opcode;
	--len;
	buf[bytes++] = len & 0xff;
	buf[bytes++] = len >> 8;
	return bytes;
}

static int mpsse_write(unsigned char *buf, unsigned char mode,
	unsigned short len, unsigned char *data)
{
	unsigned char opcode = MPSSE_DO_WRITE;
	int bytes = 0;

	if (!(mode & SPI_CPOL))
		opcode |= MPSSE_WRITE_NEG;
#if 0
	if (5 == mode)
		opcode |= MPSSE_BITMODE;
#endif
	if (mode & SPI_LSB_FIRST)
		opcode |= MPSSE_LSB;
	buf[bytes++] = opcode;
	buf[bytes++] = (len - 1) & 0xff;
	buf[bytes++] = (len - 1) >> 8;
	memcpy(&buf[bytes], data, len);
	bytes += len;
	return bytes;
}

static unsigned char mpsse_start(unsigned char mode)
{
	unsigned char opcode = MPSSE_SPI_OUT;

	if (!(mode & SPI_CPOL))
		opcode &= ~CLK_OUT;
	return opcode;
}

static void ftdiusb_initwork(struct work_struct *work)
{
	unsigned char txbuf[32];
	struct ftdiusb_spi *ks_spi =
		container_of(work, struct ftdiusb_spi, init_work);
	int bytes = 0;

#if 0
	txbuf[0] = 0x85;
	ftdiusb_sendbuf(ks_spi, txbuf, 1);

	/* command "set divisor" */
	txbuf[0] = 0x86;
	/* (clkdivisor) & 0xff; */
	txbuf[1] = 0x03;
	/* ((clkdivisor) >> 8) & 0xff; */
	txbuf[2] = 0x00;

	ftdiusb_sendbuf(ks_spi, txbuf, 3);
	/* set default clock rate */
	ftdiusb_set_clock(ks_spi);
#endif
	bytes += mpsse_loopback(txbuf, false);
	bytes += mpsse_set_clk(&txbuf[bytes], ks_spi->max_speed_hz);
	bytes += mpsse_set_hi(&txbuf[bytes], 0x00, 0x0f);
	bytes += mpsse_set_lo(&txbuf[bytes], MPSSE_SPI_OUT, MPSSE_OUT);
	ftdiusb_sendbuf(ks_spi, txbuf, bytes);
}


static int ftdiusb_sendbuf(struct ftdiusb_spi *ks_spi,
	const unsigned char *data, int length)
{
	int ret, bytesdone = 0;
	unsigned char *p;

	reinit_completion(&ks_spi->tx_completion);

	/* now we can use URB to send data */
	while (bytesdone < length) {
		p = (unsigned char *) data + bytesdone;
		usb_fill_bulk_urb(ks_spi->tx_urb, ks_spi->udev,
			usb_sndbulkpipe(ks_spi->udev, 2),
			(void *) p, length - bytesdone, transmit_bulk_callback,
			(void *) ks_spi);
		ret = usb_submit_urb(ks_spi->tx_urb, GFP_ATOMIC);
		wait_for_completion(&ks_spi->tx_completion);
		if (ret != 0) {
			printk(KERN_DEBUG "%s: seen failed ret=%d\n",
				__func__, ret);
			return false;
		}
		bytesdone += ks_spi->tx_urb->actual_length;
	}

	if (bytesdone != length) {
		printk(KERN_DEBUG "%s: send data length=%d does not equal required size=%d\n",
			__func__, bytesdone, length);
		return false;
	}

	return true;
}

static int ftdiusb_getbuf(struct ftdiusb_spi *ks_spi, const unsigned char *buf,
	int size)
{
	int offset = 0, ret = 1, i, num_of_chunks, chunk_remains;
	/* the ftdi 2232H is 512, other type is 64 */
	int packet_size = 512;
	int readbuffer_offset = 0;
	int trys = 0;

	reinit_completion(&ks_spi->rx_completion);
	/* do the actual USB read */
	while ((offset < size) && (ret > 0)) {
		usb_fill_bulk_urb(ks_spi->rx_urb, ks_spi->udev,
			usb_rcvbulkpipe(ks_spi->udev, 1), ks_spi->rxbuf,
			TXRX_BUFZISE, receiving_bulk_callback, ks_spi);
		/* returns how much received */
		ret = usb_submit_urb(ks_spi->rx_urb, GFP_ATOMIC);
		wait_for_completion(&ks_spi->rx_completion);
		ret = ks_spi->rx_urb->actual_length;

		if (ret < 0) {
			printk(KERN_DEBUG "error: fail to do URB receive\n");
			return false;
		}

		if (ret > 2) {
			/* skip FTDI status bytes. */
			/* Maybe stored in the future to enable modem use */
			num_of_chunks = ret / packet_size;
			chunk_remains = ret % packet_size;
			readbuffer_offset += 2;
			ret -= 2;
			if (ret > packet_size - 2) {
				for (i = 1; i < num_of_chunks; i++)
					memmove(ks_spi->rxbuf +
						readbuffer_offset +
						(packet_size - 2) * i,
						ks_spi->rxbuf +
						readbuffer_offset +
						packet_size * i,
					packet_size - 2);
				if (chunk_remains > 2) {
					memmove(ks_spi->rxbuf +
						readbuffer_offset +
						(packet_size - 2) * i,
						ks_spi->rxbuf +
						readbuffer_offset +
						packet_size * i,
					chunk_remains - 2);
					ret -= 2 * num_of_chunks;
				} else
					ret -= 2 * (num_of_chunks - 1) +
						chunk_remains;
			}
		} else if (ret <= 2 && ret) {
			/* no more data to read? */
			if (trys++ <= 6)
				continue;
			else {
				printk(KERN_DEBUG "%s: fpdiusb fail to read, trys=%d, ret=%d, offset=%d\n",
					__func__, trys, ret, offset);
				return false;
			}
		}
		if (ret > 0) {
			/* data still fits in buf? */
force_try:
			if (offset + ret <= size) {
				memcpy((void *)(buf + offset),
					ks_spi->rxbuf + readbuffer_offset, ret);

				offset += ret;
				/*
				 * Did we read exactly the right amount of
				 * bytes?
				 */
				if (offset == size)
					/* normal return */
					return true;
			} else {
				printk(KERN_DEBUG "%s: error: got data length=%d bigger then buffer size=%d, fail to handle, 0x%02x 0x%02x 0x%02x\n",
					 __func__, (offset + ret), size,
					(ks_spi->rxbuf + readbuffer_offset)[0],
					(ks_spi->rxbuf + readbuffer_offset)[1],
					(ks_spi->rxbuf + readbuffer_offset)[2]);
				readbuffer_offset += 2;
				ret -= 2;
				if (ret <= 0)
					return false;
				else
					goto force_try;
				return false;
			}
		}
	}
	/* never reached */
	return false;
}

static void ftdiusb_spi_chipsel(struct spi_device *spi, int cs)
{
	struct ftdiusb_spi *ks_spi;

	ks_spi = spi_master_get_devdata(spi->master);
	if (cs) {
		unsigned char *txbuf = ks_spi->txbuf;
		unsigned char opcode = MPSSE_SPI_OUT;
		int bytes = 0;

		bytes += mpsse_3_phase(&txbuf[bytes],
			!!(ks_spi->mode & SPI_CPHA));
		opcode = mpsse_start(ks_spi->mode);
		bytes += mpsse_set_lo(&txbuf[bytes], opcode, MPSSE_OUT);
		opcode &= ~CS_OUT;
		bytes += mpsse_set_lo(&txbuf[bytes], opcode, MPSSE_OUT);
		ks_spi->tx_len = bytes;
	}
}

static int ftdiusb_spi_setupxfer(struct spi_device *spi, struct spi_transfer *t)
{
	 return 0;
}


static int ftdiusb_spi_setup(struct spi_device *spi)
{
	struct ftdiusb_spi *ks_spi;

	ks_spi = spi_master_get_devdata(spi->master);

	ks_spi->mode = spi->mode;

	if (spi->max_speed_hz <= MAX_HIGH_SPEED) {
		unsigned char *txbuf = ks_spi->txbuf;
		int bytes = 0;

		ks_spi->max_speed_hz = spi->max_speed_hz;
		bytes = mpsse_set_clk(txbuf, ks_spi->max_speed_hz);
		ftdiusb_sendbuf(ks_spi, txbuf, bytes);
	}
	printk(KERN_DEBUG "[%s] mode=%d hz=%d, ks_spi hz=%ld\n", __func__,
		spi->mode, spi->max_speed_hz, ks_spi->max_speed_hz);
	return 0;
}

static int ftdiusb_spi_txrx(struct spi_device *spi, struct spi_transfer *t)
{
	int bytes;
	unsigned char *data;
	struct ftdiusb_spi *ks_spi = to_hw(spi);
	unsigned char *rx_buf = t->rx_buf;
	unsigned len = t->len;

	if (t->len >= TXRX_BUFZISE) {
		printk(KERN_DEBUG "Failed: The transfer size bigger than the buffer limit =%d\n",
			TXRX_BUFZISE);
		return 0;
	}

	if (t->tx_buf && t->len) {
		unsigned char *txbuf = ks_spi->txbuf;

		/* This is a read command. */
		if (ks_spi->xfer.rx_len)
			len = ks_spi->xfer.tx_len;

		data = (unsigned char *) t->tx_buf;

		/* Start from last MPSSE command. */
		bytes = ks_spi->tx_len;
		bytes += mpsse_write(&txbuf[bytes], ks_spi->mode, len, data);

		ks_spi->xfer.tx_len -= len;
		if (!ks_spi->xfer.rx_len && !ks_spi->xfer.tx_len) {
			bytes += mpsse_set_lo(&txbuf[bytes],
				MPSSE_SPI_OUT & ~CS_OUT, MPSSE_OUT);
			bytes += mpsse_set_lo(&txbuf[bytes], MPSSE_SPI_OUT,
				MPSSE_OUT);
			if (ftdiusb_sendbuf(ks_spi, txbuf, bytes))
				return t->len;
			else
				return 0;
		}

		/* Remember last command location. */
		ks_spi->tx_len = bytes;
		if (!t->rx_buf)
			return t->len;
	}
	if (t->rx_buf && t->len) {
		unsigned char *txbuf = ks_spi->txbuf;

		len = ks_spi->xfer.rx_len;
		rx_buf += ks_spi->xfer.rx_off;

		/* Start from last MPSSE command. */
		bytes = ks_spi->tx_len;
		bytes += mpsse_read(&txbuf[bytes], ks_spi->mode, len);
			bytes += mpsse_set_lo(&txbuf[bytes],
				MPSSE_SPI_OUT & ~CS_OUT, MPSSE_OUT);
		bytes += mpsse_set_lo(&txbuf[bytes], MPSSE_SPI_OUT, MPSSE_OUT);
		ftdiusb_sendbuf(ks_spi, txbuf, bytes);

		/* now read back the data */
		if (ftdiusb_getbuf(ks_spi, rx_buf, len))
			return t->len;

		/*
		 * after changing the clock rate, the first read may fail,
		 * try one more time
		 */
		if (ftdiusb_getbuf(ks_spi, rx_buf, len))
			return t->len;
	}

	return 0;
}

/*-------------------------------------------------------------------------*/

/*
 * SECOND PART ... simple transfer queue runner.
 *
 * This costs a task context per controller, running the queue by
 * performing each transfer in sequence.  Smarter hardware can queue
 * several DMA transfers at once, and process several controller queues
 * in parallel; this driver doesn't match such hardware very well.
 *
 * Drivers can provide word-at-a-time i/o primitives, or provide
 * transfer-at-a-time ones to leverage dma or fifo hardware.
 */
static int ftdiusb_spi_transfer_one_message(struct spi_master *master,
	struct spi_message *m)
{
	struct ftdiusb_spi *ks_spi;
	struct spi_transfer	*t = NULL;
	unsigned		cs_change;
	int			status;
	int			do_setup = -1;
	struct spi_device	*spi = m->spi;

	cs_change = 1;
	status = 0;

	ks_spi = spi_master_get_devdata(master);
	ks_spi->xfer.rx_len = 0;
	ks_spi->xfer.rx_off = 0;
	ks_spi->xfer.tx_len = 0;
	ks_spi->xfer.tx_max = 0;

	list_for_each_entry(t, &m->transfers, transfer_list) {
		const u8	*tx_buf = t->tx_buf;
		u8		*rx_buf = t->rx_buf;
		unsigned	len = t->len;

		if (tx_buf != NULL) {
			ks_spi->xfer.tx_len += len;
			if (rx_buf != NULL) {
				unsigned tx_len;

				/* Find the actual read length. */
				for (tx_len = 1; tx_len < len; tx_len++)
					if (rx_buf[tx_len] !=
					    tx_buf[tx_len])
						break;
				ks_spi->xfer.rx_len = len - tx_len;
				ks_spi->xfer.rx_off = tx_len;
				ks_spi->xfer.tx_len = tx_len;
				break;
			}
			status = 1;
		}
		if (rx_buf != NULL) {
			ks_spi->xfer.rx_len = len;
			if (status)
				break;
		}
	}
	ks_spi->xfer.tx_max = ks_spi->xfer.tx_len;

	list_for_each_entry(t, &m->transfers, transfer_list) {

		/* override speed or wordsize? */
		if (t->speed_hz || t->bits_per_word)
			do_setup = 1;

		/* init (-1) or override (1) transfer params */
		if (do_setup != 0) {
			status = ftdiusb_spi_setupxfer(spi, t);
			if (status < 0)
				break;
			if (do_setup == -1)
				do_setup = 0;
		}

		/* set up default clock polarity, and activate chip;
		 * this implicitly updates clock and spi modes as
		 * previously recorded for this device via setup().
		 * (and also deselects any other chip that might be
		 * selected ...)
		 */
		if (cs_change) {
			ftdiusb_spi_chipsel(spi, true);
		}
		cs_change = t->cs_change;
		if (!t->tx_buf && !t->rx_buf && t->len) {
			status = -EINVAL;
			break;
		}

		/* transfer data.  the lower level code handles any
		 * new dma mappings it needs. our caller always gave
		 * us dma-safe buffers.
		 */
		if (t->len) {
			status = ftdiusb_spi_txrx(spi, t);
		}
		if (status > 0)
			m->actual_length += status;
		if (status != t->len) {
			/* always report some kind of error */
			if (status >= 0)
				status = -EREMOTEIO;
			break;
		}
		status = 0;

		/* protocol tweaks before next transfer */
		if (t->delay_usecs)
			udelay(t->delay_usecs);

		if (cs_change &&
		    !list_is_last(&t->transfer_list, &m->transfers)) {
			/* sometimes a short mid-message deselect of the chip
			 * may be needed to terminate a mode or command
			 */
			ftdiusb_spi_chipsel(spi, false);
		}
	}

	m->status = status;
	m->complete(m->context);

	/* normally deactivate chipselect ... unless no error and
	 * cs_change has hinted that the next message will probably
	 * be for this chip too.
	 */
	if (!(status == 0 && cs_change)) {
		ftdiusb_spi_chipsel(spi, true);
	}
	spi_finalize_current_message(master);

	return status;
}

static int ftdiusb_spi_probe(struct platform_device *pdev)
{
	int ret;
	struct spi_master *master;
	struct ftdiusb_spi *ks_spi;
	struct usb_device_id *id;

	ret = -ENOMEM;
	master = spi_alloc_master(&pdev->dev, sizeof(struct ftdiusb_spi));
	if (!master)
		return -ENOMEM;

	ks_spi = spi_master_get_devdata(master);
	memset(ks_spi, 0, sizeof(struct ftdiusb_spi));

	if (!alloc_all_urbs(ks_spi)) {
		printk(KERN_ALERT "fail to allocate urb\n");
		goto out_reset_hw;
	}

	ks_spi->txbuf = kmalloc(TXRX_BUFZISE, GFP_KERNEL);
	if (!ks_spi->txbuf)
		goto out_reset_hw;

	ks_spi->rxbuf = kmalloc(TXRX_BUFZISE, GFP_KERNEL);
	if (!ks_spi->rxbuf)
		goto out_reset_hw;

	ks_spi->max_speed_hz = DEFAULT_SPEED;

	ks_spi->master = spi_master_get(master);
	master->bus_num = pdev->id;
	platform_set_drvdata(pdev, master);
	printk(KERN_DEBUG "[%s] master->bus_num=%d\n", __func__,
		master->bus_num);

	ks_spi->mode = SPI_MODE_0;

	master->setup = ftdiusb_spi_setup;
	master->transfer_one_message = ftdiusb_spi_transfer_one_message;
	master->num_chipselect = 1;
	master->mode_bits = SPI_CPOL | SPI_CPHA;

	/* now let us register the usb driver */
	id = (struct usb_device_id *) ftdiuspspi_driver.id_table;
	while (id) {
		if (!id->idVendor)
			break;
		id->driver_info = (unsigned long) ks_spi;
		id++;
	}

	ret = usb_register(&ftdiuspspi_driver);
	if (ret) {
		printk(KERN_DEBUG "register usb driver failed!!! ret=%d\n",
			ret);
		goto out_reset_hw;
	}

	return 0;

out_reset_hw:
	spi_master_put(master);
	return ret;
}

static int ftdiusb_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct ftdiusb_spi *ks_spi;

	platform_set_drvdata(pdev, NULL);

	ks_spi = spi_master_get_devdata(master);

	spi_unregister_master(master);

	usb_deregister(&ftdiuspspi_driver);

	spi_master_put(master);

	return 0;
}


static struct platform_driver ftdiusb_spi_driver = {
	.driver		= {
		.name	= "ftdiusb-spi",
		.owner	= THIS_MODULE,
	},
	.probe		= ftdiusb_spi_probe,
	.remove		= ftdiusb_spi_remove,
};


static int __init ftdiusb_spi_init(void)
{
	return platform_driver_register(&ftdiusb_spi_driver);
}
module_init(ftdiusb_spi_init);

static void __exit ftdiusb_spi_exit(void)
{
	platform_driver_unregister(&ftdiusb_spi_driver);
}
module_exit(ftdiusb_spi_exit);

MODULE_DESCRIPTION("Micrel ftdiusb SPI Controller driver");
MODULE_AUTHOR("David Cai <boliang.cai@micrel.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ftdiusb-spi");

