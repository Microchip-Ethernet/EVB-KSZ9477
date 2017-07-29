/*
 *  Driver for KS8695 serial ports
 *
 *  Based on drivers/serial/serial_amba.c, by Kam Lee.
 *
 *  Copyright 2002-2015 Micrel, Inc.
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


#define UART_NR		        1

#define SERIAL_KS8695_MAJOR	204
#define SERIAL_KS8695_MINOR	16
#define SERIAL_KS8695_NR	UART_NR

#ifdef SUPPORT_SYSRQ
static struct console ks8695_console;
#endif

static int initial_baud_rate;


#define KS8695_ISR_PASS_LIMIT	256

/*
 * Access macros for the KS8695 UART
 */
#define UART_GET_INT_STATUS(p)		\
	(*(volatile u_int *)((p)->membase + KS8695_INT_STATUS))
#define UART_CLR_INT_STATUS(p, c)	\
	(*(u_int *)((p)->membase + KS8695_INT_STATUS) = (c))
#define UART_GET_CHAR(p)		\
	((*(volatile u_int *)((p)->membase + KS8695_UART_RX_BUFFER)) & 0xFF)
#define UART_PUT_CHAR(p, c)		\
	(*(u_int *)((p)->membase + KS8695_UART_TX_HOLDING) = (c))
#define UART_GET_IER(p)			\
	(*(volatile u_int *)((p)->membase + KS8695_INT_ENABLE))
#define UART_PUT_IER(p, c)		\
	(*(u_int *)((p)->membase + KS8695_INT_ENABLE) = (c))
#define UART_GET_FCR(p)			\
	(*(volatile u_int *)((p)->membase + KS8695_UART_FIFO_CTRL))
#define UART_PUT_FCR(p, c)		\
	(*(u_int *)((p)->membase + KS8695_UART_FIFO_CTRL) = (c))
#define UART_GET_MSR(p)			\
	(*(volatile u_int *)((p)->membase + KS8695_UART_MODEM_STATUS))
#define UART_GET_LSR(p)			\
	(*(volatile u_int *)((p)->membase + KS8695_UART_LINE_STATUS))
#define UART_GET_LCR(p)			\
	(*(volatile u_int *)((p)->membase + KS8695_UART_LINE_CTRL))
#define UART_PUT_LCR(p, c)		\
	(*(u_int *)((p)->membase + KS8695_UART_LINE_CTRL) = (c))
#define UART_GET_MCR(p)			\
	(*(volatile u_int *)((p)->membase + KS8695_UART_MODEM_CTRL))
#define UART_PUT_MCR(p, c)		\
	(*(u_int *)((p)->membase + KS8695_UART_MODEM_CTRL) = (c))
#define UART_GET_BRDR(p)		\
	(*(volatile u_int *)((p)->membase + KS8695_UART_DIVISOR))
#define UART_PUT_BRDR(p, c)		\
	(*(u_int *)((p)->membase + KS8695_UART_DIVISOR) = (c))
#define UART_RX_DATA(s)			(((s) & KS8695_UART_LINES_RXFE) != 0)
#define UART_TX_READY(s)		(((s) & KS8695_UART_LINES_TXFE) != 0)

#define UART_DUMMY_LSR_RX	0x100
#define UART_PORT_SIZE			\
	(KS8695_IRQ_PEND_PRIORITY - KS8695_UART_RX_BUFFER + 4)

#define KS8695_UART_INTERRUPTS  (KS8695_INTMASK_UART_TX | \
	KS8695_INTMASK_UART_RX | KS8695_INTMASK_UART_LINE_ERR | \
	KS8695_INTMASK_UART_MODEMS)


static void ks8695_uart_stop_tx(struct uart_port *port)
{
	unsigned int ier;

	ier = UART_GET_IER(port);
	ier &= ~KS8695_INT_ENABLE_TX;
	UART_PUT_IER(port, ier);
}

static void ks8695_uart_start_tx(struct uart_port *port)
{
	unsigned int ier;

	ier = UART_GET_IER(port);
	if (ier & KS8695_INT_ENABLE_TX)
		return;
	else {
		ier |= KS8695_INT_ENABLE_TX;
		UART_PUT_IER(port, ier);
	}
}

static void ks8695_uart_stop_rx(struct uart_port *port)
{
	unsigned int ier;

	ier = UART_GET_IER(port);
	ier &= ~KS8695_INT_ENABLE_RX;
	UART_PUT_IER(port, ier);
}

static void ks8695_uart_enable_ms(struct uart_port *port)
{
	UART_PUT_IER(port, UART_GET_IER(port) | KS8695_INT_ENABLE_MODEM);
}

static void ks8695_uart_rx_chars(struct uart_port *port)
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
		if (unlikely(lsr & KS8695_UART_LINES_ANY)) {
			if (lsr & KS8695_UART_LINES_BE) {
				lsr &= ~(KS8695_UART_LINES_FE |
					KS8695_UART_LINES_PE);
				port->icount.brk++;
				if (uart_handle_break(port))
					goto ignore_char;
			} else if (lsr & KS8695_UART_LINES_PE)
				port->icount.parity++;
			else if (lsr & KS8695_UART_LINES_FE)
				port->icount.frame++;
			if (lsr & KS8695_UART_LINES_OE)
				port->icount.overrun++;

			lsr &= port->read_status_mask;

			if (lsr & KS8695_UART_LINES_BE)
				flag = TTY_BREAK;
			else if (lsr & KS8695_UART_LINES_PE)
				flag = TTY_PARITY;
			else if (lsr & KS8695_UART_LINES_FE)
				flag = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(port, ch))
			goto ignore_char;

		uart_insert_char(port, lsr, KS8695_UART_LINES_OE, ch, flag);

ignore_char:
		status = UART_GET_LSR(port);
	}
	tty_flip_buffer_push(&port->state->port);
	return;
}

static void ks8695_uart_modem_status(struct uart_port *port)
{
	unsigned int status, delta;

	/*
	 * clear modem interrupt by reading MSR
	 */
	status = UART_GET_MSR(port);

	delta = status & 0x0B;

	if (!delta)
		return;

	if (delta & KS8695_UART_MODEM_DDCD)
		uart_handle_dcd_change(port, status & KS8695_UART_MODEM_DDCD);

	if (delta & KS8695_UART_MODEM_DDSR)
		port->icount.dsr++;

	if (delta & KS8695_UART_MODEM_DCTS)
		uart_handle_cts_change(port, status & KS8695_UART_MODEM_DCTS);

	wake_up_interruptible(&port->state->port.delta_msr_wait);
}

static irqreturn_t ks8695_uart_int(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	unsigned int status, count;
	struct circ_buf *xmit = &port->state->xmit;

	status = UART_GET_INT_STATUS(port);

	if (status & KS8695_INTMASK_UART_RX)
		ks8695_uart_rx_chars(port);
	if (status & KS8695_INTMASK_UART_TX)
	do {
		if (port->x_char) {
			UART_CLR_INT_STATUS(port, KS8695_INTMASK_UART_TX);
			UART_PUT_CHAR(port, (u_int) port->x_char);
			port->icount.tx++;
			port->x_char = 0;
			break;
		}

		if (uart_tx_stopped(port) || uart_circ_empty(xmit)) {
			ks8695_uart_stop_tx(port);
			break;
		}

		count = 16;
		do {
			UART_CLR_INT_STATUS(port, KS8695_INTMASK_UART_TX);
			UART_PUT_CHAR(port, (u_int) (xmit->buf[xmit->tail]));
			xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
			port->icount.tx++;
			if (uart_circ_empty(xmit))
				break;
		} while (--count > 0);

		if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
			uart_write_wakeup(port);
	} while (0);

	if (status & KS8695_INTMASK_UART_MODEMS)
		ks8695_uart_modem_status(port);
	if (status & KS8695_INTMASK_UART_LINE_ERR)
		UART_GET_LSR(port);

	return IRQ_HANDLED;
}

static unsigned int ks8695_uart_tx_empty(struct uart_port *port)
{
	unsigned int status;

	status = UART_GET_LSR(port);
	return UART_TX_READY(status) ? TIOCSER_TEMT : 0;
}

static unsigned int ks8695_uart_get_mctrl(struct uart_port *port)
{
	unsigned int result = 0;
	unsigned int status;

	status = UART_GET_MSR(port);
	if (status & KS8695_UART_MODEM_DCD)
		result |= TIOCM_CAR;
	if (status & KS8695_UART_MODEM_DSR)
		result |= TIOCM_DSR;
	if (status & KS8695_UART_MODEM_CTS)
		result |= TIOCM_CTS;

	return result;
}

static void ks8695_uart_set_mctrl(struct uart_port *port, u_int mctrl)
{
	unsigned int mcr;

	mcr = UART_GET_MCR(port);
	if (mctrl & TIOCM_RTS)
		mcr |= KS8695_UART_MODEMC_RTS;
	else
		mcr &= ~KS8695_UART_MODEMC_RTS;

	if (mctrl & TIOCM_DTR)
		mcr |= KS8695_UART_MODEMC_DTR;
	else
		mcr &= ~KS8695_UART_MODEMC_DTR;

	UART_PUT_MCR(port, mcr);
}

static void ks8695_uart_break_ctl(struct uart_port *port, int break_state)
{
	unsigned long flags;
	unsigned int lcr;

	spin_lock_irqsave(&port->lock, flags);
	lcr = UART_GET_LCR(port);
	if (break_state == -1)
		lcr |= KS8695_UART_LINEC_BRK;
	else
		lcr &= ~KS8695_UART_LINEC_BRK;
	UART_PUT_LCR(port, lcr);
	spin_unlock_irqrestore(&port->lock, flags);
}

static int ks8695_uart_startup(struct uart_port *port)
{
	int retval;

	UART_PUT_IER(port, UART_GET_IER(port) & ~KS8695_UART_INTERRUPTS);

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(KS8695_INT_UART_TX, ks8695_uart_int,
		IRQF_DISABLED, "uart-tx", port);
	if (retval)
		return retval;

	retval = request_irq(KS8695_INT_UART_RX, ks8695_uart_int,
		IRQF_DISABLED, "uart-rx", port);
	if (retval)
		return retval;

	retval = request_irq(KS8695_INT_UART_LINE_ERR, ks8695_uart_int,
		IRQF_DISABLED, "uart-err", port);
	if (retval)
		return retval;

	retval = request_irq(KS8695_INT_UART_MODEMS, ks8695_uart_int,
		IRQF_DISABLED, "uart-md", port);
	if (retval)
		return retval;

	/*
	 * Finally, enable all UART interrupts except TX.
	 */
	UART_PUT_IER(port, (UART_GET_IER(port) | KS8695_UART_INTERRUPTS) &
		~KS8695_INT_ENABLE_TX);
	return 0;
}

static void ks8695_uart_shutdown(struct uart_port *port)
{
	/*
	 * Free the interrupt
	 */
	free_irq(KS8695_INT_UART_RX, port);
	free_irq(KS8695_INT_UART_TX, port);
	free_irq(KS8695_INT_UART_MODEMS, port);
	free_irq(KS8695_INT_UART_LINE_ERR, port);

	/*
	 * disable all interrupts, disable the port
	 */
	UART_PUT_IER(port, UART_GET_IER(port) & ~KS8695_UART_INTERRUPTS);

	/* disable break condition and fifos */
	UART_PUT_LCR(port, UART_GET_LCR(port) & ~KS8695_UART_LINEC_BRK);
	UART_PUT_FCR(port, UART_GET_FCR(port) & ~KS8695_UART_FIFO_FEN);
}

static void ks8695_uart_set_termios(struct uart_port *port,
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

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		lcr = KS8695_UART_LINEC_WLEN5;
		break;
	case CS6:
		lcr = KS8695_UART_LINEC_WLEN6;
		break;
	case CS7:
		lcr = KS8695_UART_LINEC_WLEN7;
		break;
	/* CS8 */
	default:
		lcr = KS8695_UART_LINEC_WLEN8;
		break;
	}
	if (termios->c_cflag & CSTOPB)
		lcr |= KS8695_UART_LINEC_STP2;
	if (termios->c_cflag & PARENB) {
		lcr |= KS8695_UART_LINEC_PEN;
		if (!(termios->c_cflag & PARODD))
			lcr |= KS8695_UART_LINEC_EPS;
	}
	if (port->fifosize > 1)
		fcr = KS8695_UART_FIFO_TRIG04 | KS8695_UART_FIFO_TXRST |
			KS8695_UART_FIFO_RXRST | KS8695_UART_FIFO_FEN;

	spin_lock_irqsave(&port->lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	port->read_status_mask = KS8695_UART_LINES_OE;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |=
			(KS8695_UART_LINES_FE | KS8695_UART_LINES_PE);
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		port->read_status_mask |= KS8695_UART_LINES_BE;

	/*
	 * Characters to ignore
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |=
			(KS8695_UART_LINES_FE | KS8695_UART_LINES_PE);
	if (termios->c_iflag & IGNBRK) {
		port->ignore_status_mask |= KS8695_UART_LINES_BE;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |= KS8695_UART_LINES_OE;
	}

	/*
	 * Ignore all characters if CREAD is not set.
	 */
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_DUMMY_LSR_RX;

	/* first, disable everything */
	old_ier = UART_GET_IER(port);
	UART_PUT_IER(port, old_ier & ~KS8695_UART_INTERRUPTS);
	old_ier &= ~KS8695_INT_ENABLE_MODEM;

	if (UART_ENABLE_MS(port, termios->c_cflag))
		old_ier |= KS8695_INT_ENABLE_MODEM;

	/* Set baud rate */
	UART_PUT_BRDR(port, quot);

	UART_PUT_LCR(port, lcr);
	UART_PUT_FCR(port, fcr);
	UART_PUT_IER(port, old_ier & ~KS8695_INT_ENABLE_TX);

	spin_unlock_irqrestore(&port->lock, flags);
}

static const char *ks8695_uart_type(struct uart_port *port)
{
	return port->type == PORT_KS8695 ? "Centaur" : NULL;
}

/*
 * Release the memory region(s) being used by 'port'
 */
static void ks8695_uart_release_port(struct uart_port *port)
{
	release_mem_region(port->mapbase, UART_PORT_SIZE);
}

/*
 * Request the memory region(s) being used by 'port'
 */
static int ks8695_uart_request_port(struct uart_port *port)
{
	return request_mem_region(port->mapbase, UART_PORT_SIZE,
		"centaur-serial")
		!= NULL ? 0 : -EBUSY;
}

/*
 * Configure/autoconfigure the port.
 */
static void ks8695_uart_config_port(struct uart_port *port, int flags)
{
	if (flags & UART_CONFIG_TYPE) {
		port->type = PORT_KS8695;
		ks8695_uart_request_port(port);
	}
}

/*
 * verify the new serial_struct (for TIOCSSERIAL).
 */
static int ks8695_uart_verify_port(struct uart_port *port,
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

static struct uart_ops ks8695_uart_pops = {
	.tx_empty	= ks8695_uart_tx_empty,
	.set_mctrl	= ks8695_uart_set_mctrl,
	.get_mctrl	= ks8695_uart_get_mctrl,
	.stop_tx	= ks8695_uart_stop_tx,
	.start_tx	= ks8695_uart_start_tx,
	.stop_rx	= ks8695_uart_stop_rx,
	.enable_ms	= ks8695_uart_enable_ms,
	.break_ctl	= ks8695_uart_break_ctl,
	.startup	= ks8695_uart_startup,
	.shutdown	= ks8695_uart_shutdown,
	.set_termios	= ks8695_uart_set_termios,
	.type		= ks8695_uart_type,
	.release_port	= ks8695_uart_release_port,
	.request_port	= ks8695_uart_request_port,
	.config_port	= ks8695_uart_config_port,
	.verify_port	= ks8695_uart_verify_port,
};

static struct uart_port ks8695_uart_ports[UART_NR] = {
	{
		.membase	= (void *)IO_ADDRESS(KS8695_IO_BASE),
		.mapbase	= KS8695_IO_BASE,
		.iotype		= SERIAL_IO_MEM,
		.irq		= KS8695_INT_UART_TX,
		.uartclk	= 25000000 * 16,
		.fifosize	= 16,
		.ops		= &ks8695_uart_pops,
		.flags		= ASYNC_BOOT_AUTOCONF,
		.line		= 0,
	}
};

#ifdef CONFIG_SERIAL_CENTAUR_CONSOLE
static void ks8695_console_write(struct console *co, const char *s, u_int count)
{
	struct uart_port *port = ks8695_uart_ports + co->index;
	unsigned int status, old_ier;
	int i = 0;
	u_char special_char;

	/*
	 *  Wait for any pending characters to be sent first and then
	 *  disable the interrupts; add count in case the interrupt is
	 *  locking the system.
	 */

	old_ier = UART_GET_IER(port);
	do {
		status = UART_GET_LSR(port);
	} while (!UART_TX_READY(status));

	UART_PUT_IER(port, old_ier & ~KS8695_UART_INTERRUPTS);

	/*
	 *	Now, do each character
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
	 *	Finally, wait for transmitter to become empty
	 *	and restore the TCR
	 */
	do {
		status = UART_GET_LSR(port);
	} while (!UART_TX_READY(status));
	UART_PUT_IER(port, old_ier);
}

static void __init ks8695_console_get_options(struct uart_port *port,
	int *baud, int *parity, int *bits)
{
	unsigned int lcr;

	lcr = UART_GET_LCR(port);

	*parity = 'n';
	if (lcr & KS8695_UART_LINEC_PEN) {
		if (lcr & KS8695_UART_LINEC_EPS)
			*parity = 'e';
		else
			*parity = 'o';
	}

	if ((lcr & 0x03) == KS8695_UART_LINEC_WLEN5)
		*bits = 5;
	else if ((lcr & 0x03) == KS8695_UART_LINEC_WLEN6)
		*bits = 6;
	else if ((lcr & 0x03) == KS8695_UART_LINEC_WLEN7)
		*bits = 7;
	else
		*bits = 8;

	*baud = port->uartclk / (UART_GET_BRDR(port) & 0x0FFF);
	*baud /= 16;
	*baud &= 0xFFFFFFF0;
}

static int __init ks8695_console_setup(struct console *co, char *options)
{
	struct uart_port *port;
	int baud = 38400;
	int bits = 8;
	int parity = 'n';
	int flow = 'n';

	/*
	 * Check whether an invalid uart number has been specified, and
	 * if so, search for the first available port that does have
	 * console support.
	 */
	port = uart_get_console(ks8695_uart_ports, UART_NR, co);

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	else
		ks8695_console_get_options(port, &baud, &parity, &bits);

	/* The spinlock is setup in uart_add_one_port function but that
	   function is not called yet.
	*/
	spin_lock_init(&port->lock);
	return uart_set_options(port, co, baud, parity, bits, flow);
}

static struct uart_driver ks8695_reg;

static struct console ks8695_console = {
	.name		= "ttyS",
	.write		= ks8695_console_write,
	.device		= uart_console_device,
	.setup		= ks8695_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &ks8695_reg,
};

static int __init ks8695_console_init(void)
{
	register_console(&ks8695_console);
	return 0;
}

console_initcall(ks8695_console_init);

static int __init ks8695_late_console_init(void)
{
	if (!(ks8695_console.flags & CON_ENABLED)) {
		struct uart_port *port;
		int bits;
		int parity;

		port = &ks8695_uart_ports[0];
		ks8695_console_get_options(port, &initial_baud_rate,
			&parity, &bits);
		register_console(&ks8695_console);
	}
	return 0;
}
late_initcall(ks8695_late_console_init);

#define KS8695_CONSOLE	(&ks8695_console)
#else
#define KS8695_CONSOLE	NULL
#endif

static struct uart_driver ks8695_reg = {
	.owner		= THIS_MODULE,
	.driver_name	= "ttyS",
	.dev_name	= "ttyS",
	.major		= SERIAL_KS8695_MAJOR,
	.minor		= SERIAL_KS8695_MINOR,
	.nr		= UART_NR,
	.cons		= KS8695_CONSOLE,
};

static int __init ks8695_uart_init(void)
{
	int ret;

	printk(KERN_INFO
		"Serial: Micrel Centaur UART driver version: 2.6.1.1\n");

	ret = uart_register_driver(&ks8695_reg);
	if (ret)
		return ret;
	uart_add_one_port(&ks8695_reg, &ks8695_uart_ports[0]);

	return 0;
}

static void __exit ks8695_uart_exit(void)
{
	uart_remove_one_port(&ks8695_reg, &ks8695_uart_ports[0]);
	uart_unregister_driver(&ks8695_reg);
}

module_init(ks8695_uart_init);
module_exit(ks8695_uart_exit);

MODULE_AUTHOR("Micrel, Inc. <www.micrel.com>");
MODULE_DESCRIPTION("Micrel Centaur serial port driver base on 16550");
MODULE_LICENSE("GPL");
