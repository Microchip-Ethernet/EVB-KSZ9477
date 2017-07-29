/*
 *  Driver for KSZ8692 serial ports
 *
 *  Based on drivers/serial/serial_amba.c, by Kam Lee.
 *
 *  Copyright 2006-2015 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * This is a generic driver for ARM AMBA-type serial ports.  This is
 * based on 16550.
 */

#if defined(CONFIG_SERIAL_CENTAUR_CONSOLE) && defined(CONFIG_MAGIC_SYSRQ)
#define SUPPORT_SYSRQ
#endif

#include <linux/module.h>
#include <linux/version.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/sysrq.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial_core.h>
#include <linux/serial.h>

#include <linux/io.h>
#include <asm/irq.h>


#define UART_NR		        4

#define SERIAL_KS8692_MAJOR	204
#define SERIAL_KS8692_MINOR	16

#ifdef SUPPORT_SYSRQ
static struct console ks8692_console;
#endif

static struct uart_port *console_port;
static int initial_baud_rate;


/*
 * Access macros for the KS8692 UART
 */

#define UART_GET_IER(p)			\
	(*(volatile u_int *)(VIO(KS8692_INT_ENABLE2)))
#define UART_PUT_IER(p, c)		\
	(*(u_int *)(VIO(KS8692_INT_ENABLE2)) = (c))
#define UART_GET_INT_STATUS(p)		\
	(*(volatile u_int *)(VIO(KS8692_INT_STATUS2)))
#define UART_CLR_INT_STATUS(p, c)	\
	(*(u_int *)(VIO(KS8692_INT_STATUS2)) = (c))

#define UART_GET_CHAR(p)		\
	((*(volatile u_int *)((p)->membase + KS_UART_RX_BUFFER)) &	\
		UART_RX_DATA_MASK)
#define UART_PUT_CHAR(p, c)		\
	(*(u_int *)((p)->membase + KS_UART_TX_HOLDING) =		\
		(c & UART_RX_DATA_MASK))
#define UART_GET_FCR(p)			\
	(*(volatile u_int *)((p)->membase + KS_UART_FIFO_CTRL))
#define UART_PUT_FCR(p, c)		\
	(*(u_int *)((p)->membase + KS_UART_FIFO_CTRL) = (c))
#define UART_GET_MSR(p)			\
	(*(volatile u_int *)((p)->membase + KS_UART_MODEM_STATUS))
#define UART_GET_LSR(p)			\
	(*(volatile u_int *)((p)->membase + KS_UART_LINE_STATUS))
#define UART_GET_LCR(p)			\
	(*(volatile u_int *)((p)->membase + KS_UART_LINE_CTRL))
#define UART_PUT_LCR(p, c)		\
	(*(u_int *)((p)->membase + KS_UART_LINE_CTRL) = (c))
#define UART_GET_MCR(p)			\
	(*(volatile u_int *)((p)->membase + KS_UART_MODEM_CTRL))
#define UART_PUT_MCR(p, c)		\
	(*(u_int *)((p)->membase + KS_UART_MODEM_CTRL) = (c))
#define UART_GET_BRDR(p)		\
	(*(volatile u_int *)((p)->membase + KS_UART_DIVISOR))
#define UART_PUT_BRDR(p, c)		\
	(*(u_int *)((p)->membase + KS_UART_DIVISOR) = (c))

#define UART_RX_DATA(s)			(((s) & UART_LINES_RX_READY) != 0)
#define UART_TX_READY(s)		(((s) & UART_LINES_TX_HOLD_EMPTY) != 0)

#define UART_DUMMY_LSR_RX	0x100

#define UART_PORT_SIZE		0x24

#define INT_UART_TX(port)	KS_INT_UART_TX((port)->irq - LOW_IRQS)
#define INT_UART_RX(port)	KS_INT_UART_RX((port)->irq - LOW_IRQS)
#define INT_UART_LINE(port)	KS_INT_UART_LINE((port)->irq - LOW_IRQS)
#define INT_UART_MODEM(port)	KS_INT_UART_MODEM((port)->irq - LOW_IRQS)
#define INT_UART_MASK(port)	KS_INT_UART_MASK((port)->irq - LOW_IRQS)

#define TX_IRQ(port)            ((port)->irq)
#define RX_IRQ(port)            ((port)->irq + 1)
#define tx_enabled(port)        ((port)->unused[0])


static void ks8692_uart_stop_tx(struct uart_port *port)
{
	unsigned int ier;

	ier = UART_GET_IER(port);
	ier &= ~INT_UART_TX(port);
	UART_PUT_IER(port, ier);
}

static void ks8692_uart_start_tx(struct uart_port *port)
{
	unsigned int ier;

	ier = UART_GET_IER(port);
	if (ier & INT_UART_TX(port))
		return;
	else {
		ier |= INT_UART_TX(port);
		UART_PUT_IER(port, ier);
	}
}

static void ks8692_uart_stop_rx(struct uart_port *port)
{
	unsigned int ier;

	ier = UART_GET_IER(port);
	ier &= ~INT_UART_RX(port);
	UART_PUT_IER(port, ier);
}

static void ks8692_uart_enable_ms(struct uart_port *port)
{
	if (LOW_IRQS + KS8692_INT_UART1_TX == port->irq)
		UART_PUT_IER(port, UART_GET_IER(port) | INT_UART_MODEM(port));
}

static void ks8692_uart_rx_chars(struct uart_port *port)
{
	unsigned int status, ch, flag, lsr, max_count = 256;

	status = UART_GET_LSR(port);
	while (UART_RX_DATA(status) && max_count--) {
		ch = UART_GET_CHAR(port);
		flag = TTY_NORMAL;

		port->icount.rx++;

		/*
		 * Note that the error handling code is
		 * out of the main execution path
		 */
		lsr = UART_GET_LSR(port) | UART_DUMMY_LSR_RX;
		if (lsr & UART_RX_ERRORS) {
			if (lsr & UART_LINES_RX_BREAK_ERR) {
				lsr &= ~(UART_LINES_RX_PARITY_ERR |
					UART_LINES_RX_FRAME_ERR);
				port->icount.brk++;
				if (uart_handle_break(port))
					goto ignore_char;
			} else if (lsr & UART_LINES_RX_PARITY_ERR)
				port->icount.parity++;
			else if (lsr & UART_LINES_RX_FRAME_ERR)
				port->icount.frame++;
			if (lsr & UART_LINES_RX_OVERRUN_ERR)
				port->icount.overrun++;

			lsr &= port->read_status_mask;

			if (lsr & UART_LINES_RX_BREAK_ERR)
				flag = TTY_BREAK;
			else if (lsr & UART_LINES_RX_PARITY_ERR)
				flag = TTY_PARITY;
			else if (lsr & UART_LINES_RX_FRAME_ERR)
				flag = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(port, ch))
			goto ignore_char;

		uart_insert_char(port, lsr, UART_LINES_RX_OVERRUN_ERR, ch,
			flag);

ignore_char:
		status = UART_GET_LSR(port);
	}
	tty_flip_buffer_push(&port->state->port);
	return;
}

static void ks8692_uart_modem_status(struct uart_port *port)
{
	unsigned int status, delta;

	/*
	 * clear modem interrupt by reading MSR
	 */
	status = UART_GET_MSR(port);

	delta = status & UART_MODEM_STATUS_CHANGE;

	if (!delta)
		return;

	if (delta & UART_MODEM_DDCD)
		uart_handle_dcd_change(port, status & UART_MODEM_DDCD);

	if (delta & UART_MODEM_DDSR)
		port->icount.dsr++;

	if (delta & UART_MODEM_DCTS)
		uart_handle_cts_change(port, status & UART_MODEM_DCTS);

	wake_up_interruptible(&port->state->port.delta_msr_wait);
}

static irqreturn_t ks8692_uart_int(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned int status, count;
	struct circ_buf *xmit = &port->state->xmit;

	status = UART_GET_INT_STATUS(port);

	if (status & INT_UART_RX(port))
		ks8692_uart_rx_chars(port);

	if (status & INT_UART_TX(port))
	do {
		if (port->x_char) {
			UART_CLR_INT_STATUS(port, INT_UART_TX(port));
			UART_PUT_CHAR(port, (u_int) port->x_char);
			port->icount.tx++;
			port->x_char = 0;
			break;
		}

		if (uart_tx_stopped(port) || uart_circ_empty(xmit)) {
			ks8692_uart_stop_tx(port);
			break;
		}

		count = 16;
		do {
			UART_CLR_INT_STATUS(port, INT_UART_TX(port));
			UART_PUT_CHAR(port, (u_int) (xmit->buf[xmit->tail]));
			xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
			port->icount.tx++;
			if (uart_circ_empty(xmit))
				break;
		} while (--count > 0);

		if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
			uart_write_wakeup(port);
	} while (0);

	if (status & INT_UART_LINE(port))
		UART_GET_LSR(port);

	if (LOW_IRQS + KS8692_INT_UART1_TX == port->irq)
		if (status & INT_UART_MODEM(port))
			ks8692_uart_modem_status(port);

	return IRQ_HANDLED;
}

static unsigned int ks8692_uart_tx_empty(struct uart_port *port)
{
	unsigned int status;

	status = UART_GET_LSR(port);
	return UART_TX_READY(status) ? TIOCSER_TEMT : 0;
}

static unsigned int ks8692_uart_get_mctrl(struct uart_port *port)
{
	unsigned int result = 0;
	unsigned int status;

	status = UART_GET_MSR(port);
	if (status & UART_MODEM_DCD)
		result |= TIOCM_CAR;
	if (status & UART_MODEM_DSR)
		result |= TIOCM_DSR;
	if (status & UART_MODEM_CTS)
		result |= TIOCM_CTS;

	return result;
}

static void ks8692_uart_set_mctrl(struct uart_port *port, u_int mctrl)
{
#if 0
	unsigned int mcr;

	mcr = UART_GET_MCR(port);
	if (mctrl & TIOCM_RTS)
		mcr |= UART_MODEMC_RTS;
	else
		mcr &= ~UART_MODEMC_RTS;

	if (mctrl & TIOCM_DTR)
		mcr |= UART_MODEMC_DTR;
	else
		mcr &= ~UART_MODEMC_DTR;

	UART_PUT_MCR(port, mcr);
#endif
}

static void ks8692_uart_break_ctl(struct uart_port *port, int break_state)
{
	unsigned long flags;
	unsigned int lcr;

	spin_lock_irqsave(&port->lock, flags);
	lcr = UART_GET_LCR(port);
	if (break_state == -1)
		lcr |= UART_LINEC_BREAK;
	else
		lcr &= ~UART_LINEC_BREAK;
	UART_PUT_LCR(port, lcr);
	spin_unlock_irqrestore(&port->lock, flags);
}

static char irq_names[MAX_UART_PORTS][4][20];

static int ks8692_uart_startup(struct uart_port *port)
{
	char irq_name[20];
	char *name;
	int dev;
	int irq;
	int len;
	int retval;
	int irq_num = 3;

	UART_PUT_IER(port, UART_GET_IER(port) & ~INT_UART_MASK(port));

	/*
	 * Allocate the IRQ
	 */

	switch (port->irq - LOW_IRQS) {
	case KS8692_INT_UART2_TX:
		dev = 1;
		break;
	case KS8692_INT_UART3_TX:
		dev = 2;
		break;
	case KS8692_INT_UART4_TX:
		dev = 3;
		break;
	default:
	case KS8692_INT_UART1_TX:
		irq_num = 4;
		dev = 0;
		break;
	}
	len = sprintf(irq_name, "uart%d-", dev);
	for (irq = port->irq; irq < port->irq + irq_num; irq++) {
		switch (irq - port->irq) {
		case 0:
			strcpy(&irq_name[len], "tx");
			break;
		case 1:
			strcpy(&irq_name[len], "rx");
			break;
		case 2:
			strcpy(&irq_name[len], "err");
			break;
		default:
		case 3:
			strcpy(&irq_name[len], "md");
			break;
		}
		name = irq_names[dev][irq - port->irq];
		strcpy(name, irq_name);
		retval = request_irq(irq, ks8692_uart_int,
			IRQF_DISABLED,
			name, port);
		if (retval)
			return retval;
	}

	/*
	 * Finally, enable all UART interrupts except TX.
	 */
	UART_PUT_IER(port, (UART_GET_IER(port) | INT_UART_MASK(port)) &
		~INT_UART_TX(port));
	if (port != console_port) {
		unsigned int mcr;

		mcr = UART_GET_MCR(port);
		mcr |= UART_ENABLE;
		mcr |= UART_OUT1_ASSERT_LOW | UART_OUT2_ASSERT_LOW;
		UART_PUT_MCR(port, mcr);
	}
	return 0;
}

static void ks8692_uart_shutdown(struct uart_port *port)
{
	int irq;
	int irq_num = 4;

	if (LOW_IRQS + KS8692_INT_UART1_TX != port->irq)
		irq_num = 3;
	for (irq = port->irq; irq < port->irq + irq_num; irq++)
		free_irq(irq, port);

	/*
	 * disable all interrupts, disable the port
	 */
	UART_PUT_IER(port, UART_GET_IER(port) & ~INT_UART_MASK(port));

	/* disable break condition and fifos */
	UART_PUT_LCR(port, UART_GET_LCR(port) & ~UART_LINEC_BREAK);
	UART_PUT_FCR(port, UART_GET_FCR(port) & ~UART_FIFO_ENABLE);
	if (port != console_port) {
		unsigned int mcr;

		mcr = UART_GET_MCR(port);
		mcr &= ~UART_ENABLE;
		UART_PUT_MCR(port, mcr);
	}
}

static void ks8692_uart_set_termios(struct uart_port *port,
	struct ktermios *termios, struct ktermios *old)
{
	unsigned int lcr, old_ier, fcr = 0;
	unsigned long flags;
	unsigned int baud, quot;

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	baud = initial_baud_rate;
	if (!baud)
		baud = uart_get_baud_rate(port, termios, old, 0,
			port->uartclk / 16);
	quot = uart_get_divisor(port, baud);

	/* Baud rate */
	switch (termios->c_cflag & CSIZE) {
	case CS5:
		lcr = UART_LINEC_5DATA_BIT;
		break;
	case CS6:
		lcr = UART_LINEC_6DATA_BIT;
		break;
	case CS7:
		lcr = UART_LINEC_7DATA_BIT;
		break;
	/* CS8 */
	default:
		lcr = UART_LINEC_8DATA_BIT;
		break;
	}

	/* Stop bit */
	if (termios->c_cflag & CSTOPB)
		lcr |= UART_LINEC_2STOP_BIT;

	/* Parity check */
	if (termios->c_cflag & PARENB) {
		lcr |= UART_LINEC_PARITY_EN;
		if (!(termios->c_cflag & PARODD))
			lcr |= UART_LINEC_EVEN_PARITY;
	}

	/* Config UART FIFO Control */
	if (port->fifosize > 1)
		fcr = UART_FIFO_TRIG_8BYTE | UART_FIFO_TX_RESET |
			UART_FIFO_RX_RESET | UART_FIFO_ENABLE;

	spin_lock_irqsave(&port->lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	port->read_status_mask = UART_LINES_RX_OVERRUN_ERR;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |=
			(UART_LINES_RX_FRAME_ERR | UART_LINES_RX_PARITY_ERR);
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		port->read_status_mask |= UART_LINES_RX_BREAK_ERR;

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |=
			(UART_LINES_RX_FRAME_ERR | UART_LINES_RX_PARITY_ERR);
	if (termios->c_iflag & IGNBRK) {
		port->ignore_status_mask |= UART_LINES_RX_BREAK_ERR;

		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |= UART_LINES_RX_OVERRUN_ERR;
	}

	/*
	 * Ignore all characters if CREAD is not set.
	 */
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_DUMMY_LSR_RX;

	/* first, disable everything */
	old_ier = UART_GET_IER(port);
	UART_PUT_IER(port, old_ier & ~INT_UART_MASK(port));
	if (LOW_IRQS + KS8692_INT_UART1_TX == port->irq) {
		old_ier &= ~INT_UART1_MODEM;

		if (UART_ENABLE_MS(port, termios->c_cflag))
			old_ier |= INT_UART1_MODEM;
	}

	/* Set baud rate */
	UART_PUT_BRDR(port, quot);

	UART_PUT_LCR(port, lcr);
	UART_PUT_FCR(port, fcr);
	UART_PUT_IER(port, old_ier & ~INT_UART_TX(port));

	spin_unlock_irqrestore(&port->lock, flags);
}

static const char *ks8692_uart_type(struct uart_port *port)
{
	return port->type == PORT_KS8695 ? "Pegasus" : NULL;
}

/*
 * Release the memory region(s) being used by 'port'
 */
static void ks8692_uart_release_port(struct uart_port *port)
{
	release_mem_region(port->mapbase, UART_PORT_SIZE);
}

/*
 * Request the memory region(s) being used by 'port'
 */

static char dev_names[MAX_UART_PORTS][20];

static int ks8692_uart_request_port(struct uart_port *port)
{
	char *name;
	int irq;

	switch (port->irq - LOW_IRQS) {
	case KS8692_INT_UART2_TX:
		irq = 1;
		break;
	case KS8692_INT_UART3_TX:
		irq = 2;
		break;
	case KS8692_INT_UART4_TX:
		irq = 3;
		break;
	default:
	case KS8692_INT_UART1_TX:
		irq = 0;
		break;
	}
	name = dev_names[irq];
	sprintf(name, "pegasus-serial.%d", irq);
	return request_mem_region(port->mapbase, UART_PORT_SIZE, name)
		!= NULL ? 0 : -EBUSY;
}

/*
 * Configure/autoconfigure the port.
 */
static void ks8692_uart_config_port(struct uart_port *port, int flags)
{
	if (flags & UART_CONFIG_TYPE) {
		port->type = PORT_KS8695;
		ks8692_uart_request_port(port);
	}
}

/*
 * verify the new serial_struct (for TIOCSSERIAL).
 */
static int ks8692_uart_verify_port(struct uart_port *port,
	struct serial_struct *ser)
{
	int ret = 0;

	if (ser->type != PORT_UNKNOWN && ser->type != PORT_KS8695)
		ret = -EINVAL;
	if (ser->irq < 0 || ser->irq >= NR_IRQS)
		ret = -EINVAL;
	if (ser->baud_base < 9600)
		ret = -EINVAL;
	return ret;
}

static struct uart_ops ks8692_uart_pops = {
	.tx_empty	= ks8692_uart_tx_empty,
	.set_mctrl	= ks8692_uart_set_mctrl,
	.get_mctrl	= ks8692_uart_get_mctrl,
	.stop_tx	= ks8692_uart_stop_tx,
	.start_tx	= ks8692_uart_start_tx,
	.stop_rx	= ks8692_uart_stop_rx,
	.enable_ms	= ks8692_uart_enable_ms,
	.break_ctl	= ks8692_uart_break_ctl,
	.startup	= ks8692_uart_startup,
	.shutdown	= ks8692_uart_shutdown,
	.set_termios	= ks8692_uart_set_termios,
	.type		= ks8692_uart_type,
	.release_port	= ks8692_uart_release_port,
	.request_port	= ks8692_uart_request_port,
	.config_port	= ks8692_uart_config_port,
	.verify_port	= ks8692_uart_verify_port,
};

static struct uart_port ks8692_uart_ports[UART_NR] = {
	{
		.membase	= (void *) VIO(KS8692_UART1_RX_BUFFER),
		.mapbase	= KS8692_IO_BASE + KS8692_UART1_RX_BUFFER,
		.iotype		= SERIAL_IO_MEM,
		.irq		= (LOW_IRQS + KS8692_INT_UART1_TX),
		.uartclk	= 25000000 * 16,
		.fifosize	= 16,
		.ops		= &ks8692_uart_pops,
		.flags		= ASYNC_BOOT_AUTOCONF,
		.line		= 0,
	}
#if UART_NR > 1
	,
	{
		.membase	= (void *) VIO(KS8692_UART2_RX_BUFFER),
		.mapbase	= KS8692_IO_BASE + KS8692_UART2_RX_BUFFER,
		.iotype		= SERIAL_IO_MEM,
		.irq		= (LOW_IRQS + KS8692_INT_UART2_TX),
		.uartclk	= 25000000 * 16,
		.fifosize	= 16,
		.ops		= &ks8692_uart_pops,
		.flags		= ASYNC_BOOT_AUTOCONF,
		.line		= 1,
	}
#if UART_NR > 2
	,
	{
		.membase	= (void *) VIO(KS8692_UART3_RX_BUFFER),
		.mapbase	= KS8692_IO_BASE + KS8692_UART3_RX_BUFFER,
		.iotype		= SERIAL_IO_MEM,
		.irq		= (LOW_IRQS + KS8692_INT_UART3_TX),
		.uartclk	= 25000000 * 16,
		.fifosize	= 16,
		.ops		= &ks8692_uart_pops,
		.flags		= ASYNC_BOOT_AUTOCONF,
		.line		= 2,
	}
#if UART_NR > 3
	,
	{
		.membase	= (void *) VIO(KS8692_UART4_RX_BUFFER),
		.mapbase	= KS8692_IO_BASE + KS8692_UART4_RX_BUFFER,
		.iotype		= SERIAL_IO_MEM,
		.irq		= (LOW_IRQS + KS8692_INT_UART4_TX),
		.uartclk	= 25000000 * 16,
		.fifosize	= 16,
		.ops		= &ks8692_uart_pops,
		.flags		= ASYNC_BOOT_AUTOCONF,
		.line		= 3,
	}
#endif
#endif
#endif
};

#ifdef CONFIG_SERIAL_CENTAUR_CONSOLE
static void ks8692_console_write(struct console *co, const char *s,
	u_int count)
{
	struct uart_port *port;
	unsigned int status, old_ier;
	int i = 0;
	u_char special_char;

	if (co->index >= UART_NR)
		co->index = 0;
	port = ks8692_uart_ports + co->index;

	/*
	 *  Wait for any pending characters to be sent first and then
	 *  disable the interrupts; add count in case the interrupt is
	 *  locking the system.
	 */

	old_ier = UART_GET_IER(port);
	do {
		status = UART_GET_LSR(port);
	} while (!UART_TX_READY(status));

	/* Disable UART1 all the interrupt bit */
	UART_PUT_IER(port, old_ier & ~INT_UART_MASK(port));

	/*
	 * Now, do each character
	 */
	for (i = 0; i < count; i++) {
		do {
			status = UART_GET_LSR(port);
		} while (!UART_TX_READY(status));
		UART_PUT_CHAR(port, (u_int) s[i]);
		if (s[i] == '\n') {
			do {
				status = UART_GET_LSR(port);
			} while (!UART_TX_READY(status));
			special_char = '\r';
			UART_PUT_CHAR(port, (u_int) special_char);
		}
	}

	/*
	 * Finally, wait for transmitter to become empty
	 * and restore the TCR
	 */
	do {
		status = UART_GET_LSR(port);
	} while (!UART_TX_READY(status));

	/* Restore UART1 interrupt */
	UART_PUT_IER(port, old_ier);
}

static void __init ks8692_console_get_options(struct uart_port *port,
	int *baud, int *parity, int *bits)
{
	u_int lcr;

	lcr = UART_GET_LCR(port);

	*parity = 'n';
	if (lcr & UART_LINEC_PARITY_EN) {
		if (lcr & UART_LINEC_EVEN_PARITY)
			*parity = 'e';
		else
			*parity = 'o';
	}

	if ((lcr & UART_LINEC_BAUD_RATE_MASK) == UART_LINEC_5DATA_BIT)
		*bits = 5;
	else if ((lcr & UART_LINEC_BAUD_RATE_MASK) == UART_LINEC_6DATA_BIT)
		*bits = 6;
	else if ((lcr & UART_LINEC_BAUD_RATE_MASK) == UART_LINEC_7DATA_BIT)
		*bits = 7;
	else
		*bits = 8;

	*baud = port->uartclk / (UART_GET_BRDR(port) & 0x0FFF);
	*baud /= 16;
	*baud &= 0xFFFFFFF0;
}

static int __init ks8692_console_setup(struct console *co, char *options)
{
	struct uart_port *port;
	int baud = 38400;
	int bits = 8;
	int parity = 'n';
	int flow = 'n';
	unsigned int mcr;

	/*
	 * Check whether an invalid uart number has been specified, and
	 * if so, search for the first available port that does have
	 * console support.
	 */
	port = uart_get_console(ks8692_uart_ports, UART_NR, co);

	console_port = port;
	mcr = UART_GET_MCR(port);
	mcr |= UART_ENABLE;
	mcr |= UART_OUT1_ASSERT_LOW | UART_OUT2_ASSERT_LOW;
	UART_PUT_MCR(port, mcr);

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	else
		ks8692_console_get_options(port, &baud, &parity, &bits);

	/* The spinlock is setup in uart_add_one_port function but that
	   function is not called yet.
	*/
	spin_lock_init(&port->lock);
	return uart_set_options(port, co, baud, parity, bits, flow);
}

static struct uart_driver ks8692_reg;

static struct console ks8692_console = {
	.name		= "ttyS",
	.write		= ks8692_console_write,
	.device		= uart_console_device,
	.setup		= ks8692_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &ks8692_reg,
};

static int __init ks8692_console_init(void)
{
	register_console(&ks8692_console);
	return 0;
}

console_initcall(ks8692_console_init);

static int __init ks8692_late_console_init(void)
{
	if (!(ks8692_console.flags & CON_ENABLED)) {
		struct uart_port *port;
		int bits;
		int parity;

		port = &ks8692_uart_ports[0];
		ks8692_console_get_options(port, &initial_baud_rate,
			&parity, &bits);
		register_console(&ks8692_console);
	}
	return 0;
}
late_initcall(ks8692_late_console_init);

#define KS8692_CONSOLE	(&ks8692_console)
#else
#define KS8692_CONSOLE	NULL
#endif

static struct uart_driver ks8692_reg = {
	.owner		= THIS_MODULE,
	.driver_name	= "ttyS",
	.dev_name	= "ttyS",
	.major		= SERIAL_KS8692_MAJOR,
	.minor		= SERIAL_KS8692_MINOR,
	.nr		= UART_NR,
	.cons		= KS8692_CONSOLE,
};

static int __init ks8692_uart_init(void)
{
	int ret;
	int i;

	printk(KERN_INFO
		"Serial: Micrel Pegasus UART driver version: 2.6.1.0\n");

	ret = uart_register_driver(&ks8692_reg);
	if (ret)
		return ret;

	for (i = 0; i < UART_NR; i++)
		ret = uart_add_one_port(&ks8692_reg, &ks8692_uart_ports[i]);
	return 0;
}

static void __exit ks8692_uart_exit(void)
{
	int i;

	for (i = 0; i < UART_NR; i++)
		uart_remove_one_port(&ks8692_reg, &ks8692_uart_ports[i]);
	uart_unregister_driver(&ks8692_reg);
}

module_init(ks8692_uart_init);
module_exit(ks8692_uart_exit);

MODULE_AUTHOR("Micrel, Inc. <www.micrel.com>");
MODULE_DESCRIPTION("Micrel Pegasus serial port driver base on 16550");
MODULE_LICENSE("GPL");
