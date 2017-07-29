#ifndef __FTDIUSBSPI__H__
#define __FTDIUSBSPI__H__

#undef  true
#undef  false
#define true				1
#define false				0


#define MAX_LOW_SPEED		(6000*1000)
#define MAX_HIGH_SPEED		(6000*1000*5)
#define DEFAULT_SPEED		(3000*1000)

#define FTDI_VID		0x0403	/* Vendor Id */
/* AlphaMicro Components AMC-232USB01 device */
#define FTDI_AMC232_PID		0xFF00 /* Product Id */
/* www.canusb.com Lawicel CANUSB device */
#define FTDI_CANUSB_PID		0xFFA8 /* Product Id */
/* ACT Solutions HomePro ZWave interface (http://www.act-solutions.com/HomePro.htm) */
#define FTDI_ACTZWAVE_PID	0xF2D0
#define FTDI_8U232AM_PID	0x6001 /* Similar device to SIO above */
#define FTDI_8U232AM_ALT_PID	0x6006 /* FTDI's alternate PID for above */
#define FTDI_8U2232C_PID	0x6010 /* Dual channel device */


#define USB_URB_TYPE_ISO	0
#define USB_URB_TYPE_INTERRUPT	1
#define USB_URB_TYPE_CONTROL	2
#define USB_URB_TYPE_BULK	3


#define USB_ENDPOINT_IN			0x80
#define USB_ENDPOINT_OUT		0x00


#define FTDI_DEFAULT_EEPROM_SIZE 128

/** FTDI chip type */
enum ftdi_chip_type {
	TYPE_AM = 0,
	TYPE_BM = 1,
	TYPE_2232C = 2,
	TYPE_R = 3,
	TYPE_2232H = 4,
	TYPE_4232H = 5
};

/** Parity mode for ftdi_set_line_property() */
enum ftdi_parity_type {
	NONE = 0,
	ODD = 1,
	EVEN = 2,
	MARK = 3,
	SPACE = 4
};

/** Number of stop bits for ftdi_set_line_property() */
enum ftdi_stopbits_type {
	STOP_BIT_1 = 0,
	STOP_BIT_15 = 1,
	STOP_BIT_2 = 2
};

/** Number of bits for ftdi_set_line_property() */
enum ftdi_bits_type {
	BITS_7 = 7,
	BITS_8 = 8
};

/** Break type for ftdi_set_line_property2() */
enum ftdi_break_type {
	BREAK_OFF = 0,
	BREAK_ON = 1
};

/** MPSSE bitbang modes */
enum ftdi_mpsse_mode {
	/**< switch off bitbang mode, back to regular serial/FIFO */
	BITMODE_RESET	= 0x00,
	/**< classical asynchronous bitbang mode, introduced with B-type chips */
	BITMODE_BITBANG	= 0x01,
	/**< MPSSE mode, available on 2232x chips */
	BITMODE_MPSSE	= 0x02,
	/**< synchronous bitbang mode, available on 2232x and R-type chips  */
	BITMODE_SYNCBB	= 0x04,
	/**< MCU Host Bus Emulation mode, available on 2232x chips */
	BITMODE_MCU	= 0x08,
	/* CPU-style fifo mode gets set via EEPROM */
	/**< Fast Opto-Isolated Serial Interface Mode, available on 2232x chips  */
	BITMODE_OPTO	= 0x10,
	/**< Bitbang on CBUS pins of R-type chips, configure in EEPROM before */
	BITMODE_CBUS	= 0x20,
	/**< Single Channel Synchronous FIFO mode, available on 2232H chips */
	BITMODE_SYNCFF	= 0x40,
};

/** Port interface for chips with multiple interfaces */
enum ftdi_interface {
	INTERFACE_ANY = 0,
	INTERFACE_A   = 1,
	INTERFACE_B   = 2,
	INTERFACE_C   = 3,
	INTERFACE_D   = 4
};

/* Shifting commands IN MPSSE Mode*/
#define MPSSE_WRITE_NEG 0x01   /* Write TDI/DO on negative TCK/SK edge*/
#define MPSSE_BITMODE   0x02   /* Write bits, not bytes */
#define MPSSE_READ_NEG  0x04   /* Sample TDO/DI on negative TCK/SK edge */
#define MPSSE_LSB       0x08   /* LSB first */
#define MPSSE_DO_WRITE  0x10   /* Write TDI/DO */
#define MPSSE_DO_READ   0x20   /* Read TDO/DI */
#define MPSSE_WRITE_TMS 0x40   /* Write TMS/CS */

/* FTDI MPSSE commands */
#define SET_BITS_LOW   0x80
/*BYTE DATA*/
/*BYTE Direction*/
#define SET_BITS_HIGH  0x82
/*BYTE DATA*/
/*BYTE Direction*/

#define CLK_OUT			0x01
#define DATA_OUT		0x02
#define DATA_IN			0x04
#define CS_OUT			0x08

#define MPSSE_SPI_OUT		(CLK_OUT | DATA_OUT | CS_OUT)
#define MPSSE_OUT		(0xf0 | MPSSE_SPI_OUT)

#define GET_BITS_LOW   0x81
#define GET_BITS_HIGH  0x83
#define LOOPBACK_START 0x84
#define LOOPBACK_END   0x85
#define TCK_DIVISOR    0x86
/* Value Low */
/* Value HIGH */ /*rate is 12000000/((1+value)*2) */
#define DIV_VALUE(rate)	\
	((rate > 6000000) ? 0 : ((6000000 / rate - 1) > 0xffff) ? 0xffff : \
	(6000000 / rate - 1))

/* Commands in MPSSE and Host Emulation Mode */
#define SEND_IMMEDIATE 0x87
#define WAIT_ON_HIGH   0x88
#define WAIT_ON_LOW    0x89

#define DISABLE_CLK_DIV		0x8A
#define ENABLE_CLK_DIV		0x8B
#define ENABLE_3_PHASE		0x8C
#define DISABLE_3_PHASE		0x8D

/* Commands in Host Emulation Mode */
#define READ_SHORT     0x90
/* Address_Low */
#define READ_EXTENDED  0x91
/* Address High */
/* Address Low  */
#define WRITE_SHORT    0x92
/* Address_Low */
#define WRITE_EXTENDED 0x93
/* Address High */
/* Address Low  */

/* Definitions for flow control */
#define SIO_RESET          0 /* Reset the port */
#define SIO_MODEM_CTRL     1 /* Set the modem control register */
#define SIO_SET_FLOW_CTRL  2 /* Set flow control register */
#define SIO_SET_BAUD_RATE  3 /* Set baud rate */
#define SIO_SET_DATA       4 /* Set the data characteristics of the port */

#define FTDI_DEVICE_OUT_REQTYPE		(USB_TYPE_VENDOR | USB_RECIP_DEVICE \
	| USB_ENDPOINT_OUT)
#define FTDI_DEVICE_IN_REQTYPE		(USB_TYPE_VENDOR | USB_RECIP_DEVICE \
	| USB_ENDPOINT_IN)

/* Requests */
#define SIO_RESET_REQUEST		SIO_RESET
#define SIO_SET_BAUDRATE_REQUEST	SIO_SET_BAUD_RATE
#define SIO_SET_DATA_REQUEST		SIO_SET_DATA
#define SIO_SET_FLOW_CTRL_REQUEST	SIO_SET_FLOW_CTRL
#define SIO_SET_MODEM_CTRL_REQUEST	SIO_MODEM_CTRL
#define SIO_POLL_MODEM_STATUS_REQUEST	0x05
#define SIO_SET_EVENT_CHAR_REQUEST	0x06
#define SIO_SET_ERROR_CHAR_REQUEST	0x07
#define SIO_SET_LATENCY_TIMER_REQUEST	0x09
#define SIO_GET_LATENCY_TIMER_REQUEST	0x0A
#define SIO_SET_BITMODE_REQUEST		0x0B
#define SIO_READ_PINS_REQUEST		0x0C
#define SIO_READ_EEPROM_REQUEST		0x90
#define SIO_WRITE_EEPROM_REQUEST	0x91
#define SIO_ERASE_EEPROM_REQUEST	0x92


#define SIO_RESET_SIO		0
#define SIO_RESET_PURGE_RX	1
#define SIO_RESET_PURGE_TX	2

#define SIO_DISABLE_FLOW_CTRL	0x0
#define SIO_RTS_CTS_HS		(0x1 << 8)
#define SIO_DTR_DSR_HS		(0x2 << 8)
#define SIO_XON_XOFF_HS		(0x4 << 8)

#define SIO_SET_DTR_MASK	0x1
#define SIO_SET_DTR_HIGH	(1 | (SIO_SET_DTR_MASK  << 8))
#define SIO_SET_DTR_LOW		(0 | (SIO_SET_DTR_MASK  << 8))
#define SIO_SET_RTS_MASK	0x2
#define SIO_SET_RTS_HIGH	(2 | (SIO_SET_RTS_MASK << 8))
#define SIO_SET_RTS_LOW		(0 | (SIO_SET_RTS_MASK << 8))

#define SIO_RTS_CTS_HS		(0x1 << 8)


#define FTDIDRV_NAME   "ftdiusb-spi"

#define TXRX_BUFZISE		2048
#define  SPI_READ		0
#define  SPI_WRITE		1


struct ftdiusb_spi {
	struct spi_master *master;
	struct usb_device *udev;
	struct urb *rx_urb, *tx_urb, *intr_urb, *ctrl_urb;
	struct usb_ctrlrequest dr;
	unsigned long max_speed_hz;
	unsigned char *txbuf;
	unsigned char *rxbuf;
	struct work_struct init_work;
	struct completion tx_completion;
	struct completion rx_completion;
	int mode;
	int tx_len;
	struct {
		unsigned rx_len;
		unsigned rx_off;
		unsigned tx_len;
		unsigned tx_max;
	} xfer;
};

#endif
