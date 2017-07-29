/*
 *  arch/arm/mach-ksz8692/include/mach/uncompress.h
 *
 *  Copyright (C) 1999 ARM Limited
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
 */

#include <linux/version.h>
#include <linux/io.h>
#include <mach/platform.h>

#if (CONFIG_CONSOLE_PORT == 1)
#define KS8692_TX_HOLDING   (IOMEM(KS8692_IO_BASE) + KS8692_UART2_TX_HOLDING)
#define KS8692_LINE_STATUS  (IOMEM(KS8692_IO_BASE) + KS8692_UART2_LINE_STATUS)
#elif (CONFIG_CONSOLE_PORT == 2)
#define KS8692_TX_HOLDING   (IOMEM(KS8692_IO_BASE) + KS8692_UART3_TX_HOLDING)
#define KS8692_LINE_STATUS  (IOMEM(KS8692_IO_BASE) + KS8692_UART3_LINE_STATUS)
#elif (CONFIG_CONSOLE_PORT == 3)
#define KS8692_TX_HOLDING   (IOMEM(KS8692_IO_BASE) + KS8692_UART4_TX_HOLDING)
#define KS8692_LINE_STATUS  (IOMEM(KS8692_IO_BASE) + KS8692_UART4_LINE_STATUS)
#else
#define KS8692_TX_HOLDING   (IOMEM(KS8692_IO_BASE) + KS8692_UART1_TX_HOLDING)
#define KS8692_LINE_STATUS  (IOMEM(KS8692_IO_BASE) + KS8692_UART1_LINE_STATUS)
#endif


/*
 * This does not append a newline
 */
static void putc(int c)
{
	int timeout = 10000;

	while (!(__raw_readl(KS8692_LINE_STATUS) & UART_LINES_TX_HOLD_EMPTY) &&
		--timeout);
	if (timeout)
		__raw_writel(c, KS8692_TX_HOLDING);
}

static inline void flush(void)
{
	int timeout = 10000;

	while (!(__raw_readl(KS8692_LINE_STATUS) & UART_LINES_TX_HOLD_EMPTY) &&
		--timeout);
}

/*
 * nothing to do
 */
#define arch_decomp_setup()
