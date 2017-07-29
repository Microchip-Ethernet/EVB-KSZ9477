/**
 * Micrel KSZ8692 SPI host controller driver
 *
 * Copyright (c) 2015-2017 Microchip Technology Inc.
 * Copyright (c) 2007-2015 Micrel, Inc.
 *
 * SPI driver for Micrel Pegasus SPI controller.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
*/


#include <linux/init.h>
#include <linux/spinlock.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/spi/spi.h>
#include <linux/version.h>
#include <mach/platform.h>
#include <mach/gpio.h>

#if (0)
#define CONFIG_SPI_DEBUG
#endif

#ifdef CONFIG_SPI_DEBUG
#define DBG_PRINT(f, x...) \
	printk(KERN_INFO KS8692_SPI_DRIVER " [%s()]: " f, __func__, ## x)
#else
#define DBG_PRINT(f, x...)	do { } while (0)
#endif

#define KS8692_SPI_DRIVER	"pegasus-spi"

#define KS_TX_FIFO_SIZE    16
#define KS_RX_FIFO_SIZE    16
#define KS_TX_THRESHOLD    1
#define KS_RX_THRESHOLD    8
#define KS_TX_FIFO_ALLOW   (KS_TX_FIFO_SIZE/* - KS_TX_THRESHOLD*/)

struct ks8692_spi {
	struct completion tx_completion;
	struct completion rx_completion;
	struct timer_list tx_timer;
	struct timer_list rx_timer;
	int tx_wait;
	int rx_wait;
	struct work_struct cs_end;
	struct spi_device *last_spi;

	void __iomem* regBase;
	int irq;
	int len;
	int tx_count;
	int rx_count;
	int operation;
	int read_len;
	/* SPI enable status (1: enabled, 0: disabled) */
	int chipselect;

	/* rx & tx data buffers from\to the spi_transfer */
	const u8 *tx;
	u8 *rx;

	struct {
		unsigned rx_len[16];
		unsigned rx_off;
		unsigned tx_len;
		unsigned tx_max;
	} xfer;
	int rx_xfer;
	unsigned rx_width;
	int rx_fifo_cnt;
	int rx_fifo_left;
	int tx_fifo_left;

	u8 bits_per_word;
	u8 mode;
	u32 div_rate;
	u32 speed_hz;

	u32 sysclk;
	struct resource *ioarea;
	struct spi_master *master;
	struct device *dev;
	spinlock_t hwlock;
};

struct rateToRegValue {
	int rate;
	unsigned long regValue;
};

static struct rateToRegValue rateToRegValueTable[] = {
	{   16,    SPI_SYSCLK_BY16 },	/*  divided SYSCLK by 16 */
	{   32,    SPI_SYSCLK_BY32 },	/*  divided SYSCLK by 32 */
	{   64,    SPI_SYSCLK_BY64 },	/*  divided SYSCLK by 64 */
	{   128,   SPI_SYSCLK_BY128 },	/*  divided SYSCLK by 128 */
	{   256,   SPI_SYSCLK_BY256 },	/*  divided SYSCLK by 256 */
	{   1024,  SPI_SYSCLK_BY1024 },	/*  divided SYSCLK by 1024 */
	{   8192,  SPI_SYSCLK_BY8192 },	/*  divided SYSCLK by 8192 */
	{   65536, SPI_SYSCLK_BY65536 }	/*  divided SYSCLK by 65536 */
};

static int getRegValueToRate(u32 dwRegValue)
{
	int rate = 0;
	int i;

	for (i = 0; i < 8; i++) {
		if (dwRegValue == rateToRegValueTable[i].regValue)
			return rateToRegValueTable[i].rate;
	}

	/* not set, return zero (not rate limit) */
	return rate;
}

static void spi_tx_timeout(unsigned long data)
{
	struct ks8692_spi *ks_spi = (struct ks8692_spi *) data;
	u32 intStatus;
	u32 intMask;
	u32 unTxData_len;

	DBG_PRINT("%s: start.\n", __func__);

	if (ks_spi->tx_wait != 1)
		return;

	intStatus = readl(ks_spi->regBase + KS8692_SPI_INT_STATUS);
	intMask = readl(ks_spi->regBase + KS8692_SPI_INT_ENABLE);
	unTxData_len = readl(ks_spi->regBase + KS8692_SPI_BUF_STATUS);

	printk(KERN_DEBUG
		"%s: Timeout waiting for tx complete! tx_len=%d, tx_count=%d\n",
		__func__, ks_spi->len, ks_spi->tx_count);
	printk(KERN_DEBUG
		"%s: intStatus=0x%08x, intMask=0x%08x, unTxData_len=0x%08x\n",
		__func__, intStatus, intMask, unTxData_len);
	printk(KERN_DEBUG
		"%s: (SPI_CSR)0x%08X: %08x\n",
		__func__, (int)(ks_spi->regBase + KS8692_SPI_CS),
		(int)readl(ks_spi->regBase + KS8692_SPI_CS));
	printk(KERN_DEBUG
		"%s: (SPI_CTR)0x%08X: %08x\n",
		__func__, (int)(ks_spi->regBase + KS8692_SPI_CTRL),
		(int)readl(ks_spi->regBase + KS8692_SPI_CTRL));
	printk(KERN_DEBUG
		"%s: (SPI_TDR)0x%08X: %08x\n",
		__func__, (int)(ks_spi->regBase + KS8692_SPI_TX_DATA),
		(int)readl(ks_spi->regBase + KS8692_SPI_TX_DATA));

	ks_spi->tx_wait++;
	complete(&ks_spi->tx_completion);
}

static void spi_rx_timeout(unsigned long data)
{
	struct ks8692_spi *ks_spi = (struct ks8692_spi *) data;
	u32 intStatus;
	u32 intMask;
	u32 rxReadyData_len;

	DBG_PRINT("%s: start.\n", __func__);

	if (ks_spi->rx_wait != 1)
		return;

	intStatus = readl(ks_spi->regBase + KS8692_SPI_INT_STATUS);
	intMask = readl(ks_spi->regBase + KS8692_SPI_INT_ENABLE);
	rxReadyData_len = readl(ks_spi->regBase + KS8692_SPI_BUF_STATUS);

	printk(KERN_DEBUG
		"%s: Timeout waiting for rx complete! rx_len=%d, rx_count=%d\n",
		__func__, ks_spi->len, ks_spi->rx_count);
	printk(KERN_DEBUG
		"%s: intStatus=0x%08x, intMask=0x%08x, ReadyData_len=0x%08x\n",
		__func__, intStatus, intMask, rxReadyData_len);
	printk(KERN_DEBUG
		"%s: (SPI_CSR)0x%08X: %08x\n",
		__func__, (int)(ks_spi->regBase + KS8692_SPI_CS),
		(int)readl(ks_spi->regBase + KS8692_SPI_CS));
	printk(KERN_DEBUG
		"%s: (SPI_CTR)0x%08X: %08x\n",
		__func__, (int)(ks_spi->regBase + KS8692_SPI_CTRL),
		(int)readl(ks_spi->regBase + KS8692_SPI_CTRL));

	ks_spi->rx_wait++;
	complete(&ks_spi->rx_completion);
}

static void spi_timer_init(struct ks8692_spi *ks_spi)
{
	/* init spi tx timer */
	init_timer(&ks_spi->tx_timer);
	ks_spi->tx_timer.function = &spi_tx_timeout;
	ks_spi->tx_timer.expires = jiffies + (HZ / 2);   /* 500 ms */
	ks_spi->tx_timer.data = (unsigned long) ks_spi;

	/* init spi rx timer */
	init_timer(&ks_spi->rx_timer);
	ks_spi->rx_timer.function = &spi_rx_timeout;
	ks_spi->rx_timer.expires = jiffies + (HZ / 2);   /* 500 ms */
	ks_spi->rx_timer.data = (unsigned long) ks_spi;
}

/*
 * Reset SPI controller.
 */
static inline void ks_spi_reset(struct ks8692_spi *ks_spi)
{
	DBG_PRINT("\n");

	/* reset */
	writel(SPI_RESET, ks_spi->regBase + KS8692_SPI_CTRL);
	mdelay(1);
}

/*
 * Init SPI Control register and enable it.
 */
static inline void ks_spi_init(struct ks8692_spi *ks_spi)
{
	unsigned long regData;

	/*
	 * Set 1 delay between consecutive transfers, and between chip selects.
	 * Transmit buffer threshold for 1 byte
	 */
	regData = readl(ks_spi->regBase + KS8692_SPI_CS);
	regData &= ~(SPI_TX_THRESHOLD_MASK);
	regData |= (KS_TX_THRESHOLD << 20);
	writel(regData, ks_spi->regBase + KS8692_SPI_CS);

	DBG_PRINT("(SPI_CSR)0x%08X: %08x\n",
		(int)(ks_spi->regBase + KS8692_SPI_CS),
		(int)(int)readl(ks_spi->regBase + KS8692_SPI_CS));
}

/*
 * Get System clock  SYSCLK.
 */
static inline void ks_spi_getclk(struct ks8692_spi *ks_spi)
{
	unsigned long regData;
	unsigned long fAPB;

	/* Get APB system clock in Hz */
	regData = KS8692_READ_REG(KS8692_SYSTEM_BUS_CLOCK);
	fAPB = regData & SYSTEM_BUS_CLOCK_MASK;

	switch (fAPB) {
	case SYSTEM_BUS_CLOCK_200:
		ks_spi->sysclk = 200 * 1000 * 1000;
		break;
	case SYSTEM_BUS_CLOCK_166:
		ks_spi->sysclk = 166 * 1000 * 1000;
		break;
	case SYSTEM_BUS_CLOCK_125:
		ks_spi->sysclk = 125 * 1000 * 1000;
		break;
	case SYSTEM_BUS_CLOCK_50:
	default:
		ks_spi->sysclk = 50 * 1000 * 1000;
		break;
	}
}

static void extend_timer(struct timer_list *spi_timer)
{
	if (timer_pending(spi_timer))
		mod_timer(spi_timer, (jiffies + (HZ / 2)));
	else {
		/* 500 ms */
		spi_timer->expires = jiffies + (HZ / 2);
		add_timer(spi_timer);
	}
}

static inline u32 ks_spi_read(struct ks8692_spi *ks_spi, u32 reg)
{
	return readl(ks_spi->regBase + reg);
}

static inline void ks_spi_write(struct ks8692_spi *ks_spi, u32 reg, u32 val)
{
	writel(val, ks_spi->regBase + reg);
}

static int chk_tx_fifo(struct ks8692_spi *ks_spi, int minimum_len)
{
	int tx_fifo_len;
	int tx_left;
	u32 intr_mask;

	reinit_completion(&ks_spi->tx_completion);

	/* Check available TX FIFO space. */
	tx_fifo_len = ks_spi_read(ks_spi, KS8692_SPI_BUF_STATUS) &
		SPI_UNTX_LEN_MASK;
	tx_left = KS_TX_FIFO_SIZE - tx_fifo_len;
	if (tx_left < minimum_len && 15 == tx_left) {
		int timeout = 20;

		do {
			udelay(1);
			tx_fifo_len = ks_spi_read(ks_spi,
				KS8692_SPI_BUF_STATUS) & SPI_UNTX_LEN_MASK;
			tx_left = KS_TX_FIFO_SIZE - tx_fifo_len;
			if (!--timeout)
				break;
		} while (tx_left < minimum_len);
	}
	if (tx_left < minimum_len) {

		/* Setup interrupt timeout. */
		extend_timer(&ks_spi->tx_timer);
		ks_spi->tx_wait = 1;

		/* enable SPI TB_TH interrupt */
		spin_lock_irq(&ks_spi->hwlock);
		intr_mask = ks_spi_read(ks_spi, KS8692_SPI_INT_ENABLE);
		intr_mask |= (SPI_INT_TDTH);
		ks_spi_write(ks_spi, KS8692_SPI_INT_ENABLE, intr_mask);
		spin_unlock_irq(&ks_spi->hwlock);

		/*
		 * There may be no wait at all if the interrupt handling is
		 * fast enough.
		 */
		wait_for_completion(&ks_spi->tx_completion);

		/* Not cleared by interrupt. */
		if (ks_spi->tx_wait > 1)
			tx_left = -1;
		else
			tx_left = 0;
		ks_spi->tx_wait = 0;
	}
	return tx_left;
}  /* chk_tx_fifo */

static int chk_tx_empty(struct ks8692_spi *ks_spi)
{
	int fifo_size = KS_TX_FIFO_SIZE;

	if (ks_spi->div_rate <= 32)
		fifo_size--;
	do {
		/* This call will be blocked if no FIFO space. */
		ks_spi->tx_fifo_left = chk_tx_fifo(ks_spi, fifo_size);

		/* Still no FIFO space. */
		if (ks_spi->tx_fifo_left <= 0) {

			/* Something is wrong. */
			if (ks_spi->tx_fifo_left < 0)
				break;

			/* Check TX FIFO again. */
			continue;
		}
	} while (ks_spi->tx_fifo_left < fifo_size);
	return ks_spi->tx_fifo_left == KS_TX_FIFO_SIZE;
}

#define USE_MICREL_MODE_

static void ks_spi_issue_read_cmd(struct ks8692_spi *ks_spi)
{
	u32 data;
	unsigned rx_len = ks_spi->read_len - ks_spi->rx_count;

	/* Try to use 16-bit read as much as possible. */
	if (rx_len > 8)
		rx_len &= ~1;
	if (rx_len & 1)
		ks_spi->rx_width = 1;
	else
		ks_spi->rx_width = 2;
	rx_len /= ks_spi->rx_width;
	if (rx_len > KS_RX_FIFO_SIZE)
		rx_len = KS_RX_FIFO_SIZE;
	ks_spi->rx_fifo_cnt = rx_len;
	rx_len--;

	data = 0;
#ifndef USE_MICREL_MODE
	if (2 == ks_spi->rx_width)
		data |= SPI_TX_16_BITS;
	data |= SPI_TX_HIZEXT_ENABLE;
	data |= rx_len;
	data |= SPI_TX_HIZ_ENABLE;
#else
		data |= SPI_TX_HIZ_ENABLE;
		data |= rx_len;
		data |= SPI_MICREL_MODE;
#endif
	ks_spi_write(ks_spi, KS8692_SPI_TX_DATA, data);
}  /* ks_spi_issue_read_cmd */

/*
 * ks_spi_issue_first_read_cmd
 *
 * Send SPI read command, and address offset to spi target.
 */
static void ks_spi_issue_first_read_cmd(struct ks8692_spi *ks_spi)
{
	u32 data;
	int count;
	const u8 *cp = ks_spi->tx;
	int len = ks_spi->len;
	int rx_len = ks_spi->read_len;

	/* Default is byte transfer. */
	ks_spi->rx_width = 1;

	/* Assume read request is not sent. */
	ks_spi->rx_fifo_cnt = 0;

	/* Try to use 16-bit read if big enough. */
	if (rx_len > KS_RX_FIFO_SIZE)
		rx_len &= ~1;

	/* Use 16-bit write whenever possible. */
	for (count = 0; count < len - 2; count += 2) {
		data = SPI_TX_16_BITS;
		data |= (*cp++ << 24);
		data |= (*cp++ << 16);
		ks_spi_write(ks_spi, KS8692_SPI_TX_DATA, data);
	}

	/* Can use 16-bit if both write and read lengths are even. */
	if (!(len & 1) && !(rx_len & 1)) {
		data = SPI_TX_16_BITS;
		data |= (*cp++ << 24);
		data |= (*cp++ << 16);
		data |= SPI_TX_HIZEXT_ENABLE;
		ks_spi->rx_width = 2;
		rx_len /= ks_spi->rx_width;
		if (rx_len > KS_RX_FIFO_SIZE)
			rx_len = KS_RX_FIFO_SIZE;
		ks_spi->rx_fifo_cnt = rx_len;
		data |= rx_len;
		ks_spi_write(ks_spi, KS8692_SPI_TX_DATA, data);
	} else {
		if (count < len - 1) {
			data = (*cp++ << 16);
			ks_spi_write(ks_spi, KS8692_SPI_TX_DATA, data);
		}
		data = (*cp++ << 16);

		/* Use 16-bit read for large read transfer. */
		if (rx_len < KS_RX_FIFO_SIZE) {
			data |= SPI_TX_HIZEXT_ENABLE;
			ks_spi->rx_fifo_cnt = rx_len;
			data |= rx_len;
		}
		ks_spi_write(ks_spi, KS8692_SPI_TX_DATA, data);
	}
	ks_spi->tx_count += len;

	if (!ks_spi->rx_fifo_cnt)
		ks_spi_issue_read_cmd(ks_spi);

	chk_tx_empty(ks_spi);
}  /* ks_spi_issue_first_read_cmd */

/*
 * Read data from the SPI device through ks8692 SPI interface to spi_transfer
 * by one BYTE.
 */
static int ks_spi_rx_buf(struct ks8692_spi *ks_spi)
{
	u32 data;
	int rx_count;
	int rx_left;
	u8 *rx = ks_spi->rx;

	/* How much data to read. */
	rx_left = ks_spi->len - ks_spi->rx_count;

	ks_spi->rx_fifo_left *= ks_spi->rx_width;

	/* If too big use the maximum allowed. */
	if (rx_left > ks_spi->rx_fifo_left)
		rx_left = ks_spi->rx_fifo_left;

	/* How much data will be received. */
	rx_count = rx_left;
	ks_spi->rx_count += rx_count;
	rx_left /= ks_spi->rx_width;

	ks_spi->rx_fifo_cnt -= rx_left;
	while (rx_left--) {
		data = ks_spi_read(ks_spi, KS8692_SPI_RX_DATA);
		data >>= 16;
		if (2 == ks_spi->rx_width)
			*rx++ = (u8)(data >> 8);
		*rx++ = (u8) data;
	}
	ks_spi->rx = rx;

	/* Still more data to read. */
	if (ks_spi->rx_fifo_cnt <= 0 && ks_spi->rx_count < ks_spi->len)
		ks_spi_issue_read_cmd(ks_spi);

	return rx_count;
}  /* ks_spi_rx_buf */

static int chk_rx_fifo(struct ks8692_spi *ks_spi)
{
	int rx_fifo_len;
	u32 intr_mask;

	reinit_completion(&ks_spi->rx_completion);

	/* return error if SPI receive buffer is not available */
	rx_fifo_len = (ks_spi_read(ks_spi, KS8692_SPI_BUF_STATUS) &
		SPI_RX_LEN_MASK) >> 16;
	if (!rx_fifo_len) {

		/* Setup interrupt timeout. */
		extend_timer(&ks_spi->rx_timer);
		ks_spi->rx_wait = 1;

		spin_lock_irq(&ks_spi->hwlock);
		intr_mask = ks_spi_read(ks_spi, KS8692_SPI_INT_ENABLE);
		intr_mask |= (SPI_INT_RDRDY | SPI_INT_RDBU);
		ks_spi_write(ks_spi, KS8692_SPI_INT_ENABLE, intr_mask);
		spin_unlock_irq(&ks_spi->hwlock);

		/*
		 * There may be no wait at all if the interrupt handling is
		 * fast enough.
		 */
		wait_for_completion(&ks_spi->rx_completion);

		/* Not cleared by interrupt. */
		if (ks_spi->rx_wait)
			rx_fifo_len--;
		ks_spi->rx_wait = 0;
	}
	return rx_fifo_len;
}  /* chk_rx_fifo */

static int ks_spi_tx_buf(struct ks8692_spi *ks_spi)
{
	u32 data;
	int count;
	int tx_count;
	int tx_left;
	int last_tx = 0;
	const u8 *tx = ks_spi->tx;

	/* How much data to send out. */
	tx_left = ks_spi->len - ks_spi->tx_count;

	ks_spi->tx_fifo_left *= 2;

	/* If too big use the maximum allowed. */
	if (tx_left > ks_spi->tx_fifo_left)
		tx_left = ks_spi->tx_fifo_left;
	else {
		/* The last byte will be sent. */
		tx_left--;
		last_tx = 1;
	}

	/* How much data will be sent out. */
	tx_count = tx_left + last_tx;
	ks_spi->tx_count += tx_count;

	/* Use 16-bit write whenever possible. */
	for (count = 0; count < tx_left + last_tx - 2 * last_tx; count += 2) {
		data = SPI_TX_16_BITS;
		data |= (*tx++ << 24);
		data |= (*tx++ << 16);
		ks_spi_write(ks_spi, KS8692_SPI_TX_DATA, data);
	}
	if (last_tx) {
		data = 0;
		if (count < tx_left) {
			data = SPI_TX_16_BITS;
			data |= (*tx++ << 24);
		}
		data |= (*tx++ << 16);
		ks_spi->xfer.tx_len -= ks_spi->tx_count;
		if (!ks_spi->xfer.tx_len)
			data |= SPI_TX_CS_END;
		ks_spi_write(ks_spi, KS8692_SPI_TX_DATA, data);
	}
	ks_spi->tx = tx;

	return tx_count;
}  /* ks_spi_tx_buf */

static inline struct ks8692_spi *to_hw(struct spi_device *sdev)
{
	return spi_master_get_devdata(sdev->master);
}

static void spi_set_cs(struct spi_device *spi, bool enable)
{
	if (spi->mode & SPI_CS_HIGH)
		enable = !enable;

	if (spi->cs_gpio >= 0)
		gpio_set_value(spi->cs_gpio, !enable);
}

static void ks_cs_end(struct work_struct *work)
{
	struct ks8692_spi *ks_spi = container_of(work,
		struct ks8692_spi, cs_end);

	if (ks_spi->chipselect & 2) {
		ks_spi_write(ks_spi, KS8692_SPI_CTRL, 0);
		ks_spi->chipselect = 0;
		spi_set_cs(ks_spi->last_spi, false);
	}
}  /* ks_cs_end */

static void ks8692_spi_chipsel(struct spi_device *spi, int cs)
{
}

static int _ks8692_spi_setupxfer(struct spi_device *spi, struct spi_transfer *t)
{
	struct ks8692_spi *ks_spi = to_hw(spi);
	u8 bpw;
	u32 hz;
	unsigned int div;
	unsigned long regData;
	unsigned long uninitialized_var(sysclkDivider);
	int spi_divider;

	if (t)
		DBG_PRINT("bpw %d, hz %d\n", t->bits_per_word, t->speed_hz);
	else
		DBG_PRINT("spi_bpw %d, spi_hz %d\n",
			spi->bits_per_word, spi->max_speed_hz);

	bpw = (t && t->bits_per_word) ? t->bits_per_word : spi->bits_per_word;
	hz  = (t && t->speed_hz) ? t->speed_hz : spi->max_speed_hz;

	/* Make sure its a bit width we support [8, 16] */
	if ((bpw != 8) && (bpw != 16)) {
		dev_err(&spi->dev, "invalid bits-per-word (%d)\n", bpw);
		return -EINVAL;
	}
	ks_spi->mode = spi->mode;
	ks_spi->bits_per_word = bpw;
	ks_spi->speed_hz = hz;

	DBG_PRINT("(SPI_TDR)0x%08X: %08x\n",
		(int)(ks_spi->regBase + KS8692_SPI_TX_DATA),
		(int)readl(ks_spi->regBase + KS8692_SPI_TX_DATA));

	/* Get the clock divider */
	div = ks_spi->sysclk / hz;

	DBG_PRINT("max_speed_hz=%d, sysclk=%d, hz=%d, div=%d\n",
		spi->max_speed_hz, ks_spi->sysclk, hz, div);

	if (div <= 16)
		sysclkDivider = SPI_SYSCLK_BY16;
	else if ((div > 16) && (div <= 32))
		sysclkDivider = SPI_SYSCLK_BY32;
	else if ((div > 32) && (div <= 64))
		sysclkDivider = SPI_SYSCLK_BY64;
	else if ((div > 64) && (div <= 128))
		sysclkDivider = SPI_SYSCLK_BY128;
	else if ((div > 128) && (div <= 256))
		sysclkDivider = SPI_SYSCLK_BY256;
	else if ((div > 256) && (div <= 1024))
		sysclkDivider = SPI_SYSCLK_BY1024;
	else if ((div > 1024) && (div <= 8192))
		sysclkDivider = SPI_SYSCLK_BY8192;
	else if ((div > 8192) && (div <= 65536))
		sysclkDivider = SPI_SYSCLK_BY65536;
	else if (div > 65536)
		sysclkDivider = SPI_SYSCLK_BY65536;

	spi_divider = getRegValueToRate(sysclkDivider);
	DBG_PRINT("sysclkDivider=%08x, spi_divider=%d\n", (int) sysclkDivider,
		spi_divider);
	DBG_PRINT("hz=%d, clkdivisor=%d SYSCLK=%d spi_clock=%d\n",
		hz, spi_divider, ks_spi->sysclk, (ks_spi->sysclk/spi_divider));
	ks_spi->div_rate = spi_divider;

	/* Program SPCK clock rate to the device */
	regData = readl(ks_spi->regBase + KS8692_SPI_CS);
	regData &= ~SPI_SYSCLK_MASK;
	regData |= (sysclkDivider | SPI_CS_SETUP_TIME_EN |
		SPI_DATA_DELAY_1 | SPI_CS_DELAY_1);

	/* Clock Phase Select (CPHA) */
	if (spi->mode & SPI_CPHA)
		regData &= ~SPI_DATA_LEADING_EDGE;
	else
		regData |= SPI_DATA_LEADING_EDGE;

	/* Clock polarity select (CPOL) */
	if (spi->mode & SPI_CPOL)
		regData |= SPI_SPCK_INACTIVE_HIGH;
	else
		regData &= ~SPI_SPCK_INACTIVE_HIGH;

	/* Active level of chip select */
	if (spi->mode & SPI_CS_HIGH)
		regData |= SPI_CS_ACTIVE_HIGH;  /* chipselect active high? */
	else
		regData &= ~SPI_CS_ACTIVE_HIGH;

	/* write new configration */
	writel(regData, ks_spi->regBase + KS8692_SPI_CS);
	DBG_PRINT("(SPI_CSR)0x%08X: %08x\n",
		(int)(ks_spi->regBase + KS8692_SPI_CS),
		(int)readl(ks_spi->regBase + KS8692_SPI_CS));

	return 0;
}

static int ks8692_spi_setupxfer(struct spi_device *spi, struct spi_transfer *t)
{
	struct ks8692_spi *ks_spi = to_hw(spi);
	u8 bpw;
	u32 hz;

	bpw = (t && t->bits_per_word) ? t->bits_per_word : spi->bits_per_word;
	hz  = (t && t->speed_hz) ? t->speed_hz : spi->max_speed_hz;
	if (bpw != ks_spi->bits_per_word || hz != ks_spi->speed_hz ||
			spi->mode != ks_spi->mode)
		return _ks8692_spi_setupxfer(spi, t);

	return 0;
}

/* the spi->mode bits understood by this driver: */
#define MODEBITS	(SPI_CPOL | SPI_CPHA | SPI_CS_HIGH)

static int ks8692_spi_setup(struct spi_device *spi)
{
	int ret;

	DBG_PRINT("mode %d, %u bpw, %d hz\n",
		spi->mode, spi->bits_per_word, spi->max_speed_hz);

	if (spi->mode & ~MODEBITS)
		return -EINVAL;

	if (!spi->bits_per_word)
		spi->bits_per_word = 8;

	ret = _ks8692_spi_setupxfer(spi, NULL);
	if (ret < 0) {
		dev_err(&spi->dev, "setupxfer returned %d\n", ret);
		return ret;
	}

	return 0;
}

static void ks_spi_rx(struct ks8692_spi *ks_spi)
{
	/* Read raw data from SPI device. */
	while (ks_spi->rx_count < ks_spi->len) {

		/* This call will be blocked if no FIFO space. */
		ks_spi->rx_fifo_left = chk_rx_fifo(ks_spi);

		/* Still no FIFO space. */
		if (ks_spi->rx_fifo_left <= 0) {

			/* Something is wrong. */
			if (ks_spi->rx_fifo_left < 0)
				break;

			/* Check RX FIFO again. */
			continue;
		}

		/* read until there is an error */
		if (ks_spi_rx_buf(ks_spi) < 0)
			break;
	}
}  /* ks_spi_rx */

static void ks_spi_tx(struct ks8692_spi *ks_spi)
{
	int len;

	/* Write raw data to SPI device. */
	while (ks_spi->tx_count < ks_spi->len) {
		len = ks_spi->len - ks_spi->tx_count;
		len++;
		len /= 2;
		if (len > 8)
			len = 8;

		/* This call will be blocked if no FIFO space. */
		ks_spi->tx_fifo_left = chk_tx_fifo(ks_spi, len);

		/* Still no FIFO space. */
		if (ks_spi->tx_fifo_left <= 0) {

			/* Something is wrong. */
			if (ks_spi->tx_fifo_left < 0)
				break;

			/* Check TX FIFO again. */
			continue;
		}

		/* write until there is an error */
		if (ks_spi_tx_buf(ks_spi) < 0)
			break;
	}
}  /* ks_spi_tx */

static int ks8692_spi_txrx(struct spi_device *spi, struct spi_transfer *t)
{
	struct ks8692_spi *ks_spi = to_hw(spi);

	DBG_PRINT("tx %p, rx %p, len %d, operation %d\n",
		t->tx_buf, t->rx_buf, t->len, ks_spi->operation);

	ks_spi->tx = t->tx_buf;
	ks_spi->rx = t->rx_buf;
	ks_spi->len = t->len;
	ks_spi->tx_count = 0;
	ks_spi->rx_count = 0;
	reinit_completion(&ks_spi->tx_completion);
	reinit_completion(&ks_spi->rx_completion);
	ks_spi->tx_wait = 0;
	ks_spi->rx_wait = 0;

	/* There is a write transfer. */
	if (ks_spi->tx) {

		/* This is a read command. */
		if (ks_spi->xfer.rx_len[0]) {
			ks_spi->len = ks_spi->xfer.tx_len;
			ks_spi->read_len = ks_spi->xfer.rx_len[0];
			ks_spi_issue_first_read_cmd(ks_spi);
		} else
			ks_spi_tx(ks_spi);
	}

	/* There is a read transfer. */
	if (ks_spi->rx) {
		if (ks_spi->rx_xfer == 16)
			return 0;
		ks_spi->len = ks_spi->xfer.rx_len[ks_spi->rx_xfer];
		ks_spi->read_len = ks_spi->len;
		ks_spi->rx += ks_spi->xfer.rx_off;
		ks_spi->tx_count = 0;
		if (!ks_spi->rx_fifo_cnt)
			ks_spi_issue_read_cmd(ks_spi);
		ks_spi_rx(ks_spi);
		ks_spi->rx_count += ks_spi->xfer.rx_off;
		ks_spi->rx_xfer++;
	}

	return ks_spi->rx_count > ks_spi->tx_count ?
		ks_spi->rx_count : ks_spi->tx_count;
}

static irqreturn_t ks8692_spi_irq(int irq, void *dev)
{
	struct ks8692_spi *ks_spi = dev;
	u32 intStatus;
	u32 intMask;
	u32 save_mask;
	u32 save_intr;

	/* Get interrupt status */
	intStatus = readl(ks_spi->regBase + KS8692_SPI_INT_STATUS);
	intMask = readl(ks_spi->regBase + KS8692_SPI_INT_ENABLE);
	save_intr = intStatus;
	save_mask = intMask;
	intStatus &= intMask;
	DBG_PRINT("%s: 0x%08x\n", __func__, intStatus);

	/* spi receive data ready, we need handle RX first */
	if ((intStatus & SPI_INT_RDRDY) || (intStatus & SPI_INT_RDBU)) {
		intMask &= ~(SPI_INT_RDRDY | SPI_INT_RDBU);
		ks_spi->rx_wait = 0;
		complete(&ks_spi->rx_completion);
	}

	/* spi transmit buffer level is lower than the threshole */
	if (intStatus & SPI_INT_TDTH) {
		intMask &= ~(SPI_INT_TDTH);
		ks_spi->tx_wait = 0;
		complete(&ks_spi->tx_completion);
	}
	save_intr &= save_mask;
	ks_spi_write(ks_spi, KS8692_SPI_INT_STATUS, save_intr);
	if (intMask != save_mask)
		ks_spi_write(ks_spi, KS8692_SPI_INT_ENABLE, intMask);

	return IRQ_HANDLED;
}

/*----------------------------------------------------------------------*/

extern unsigned int ksz_system_bus_clock;
static u32 start_cnt;
static u32 stop_cnt;

static int ks8692_spi_prepare_hardware(struct spi_master *master)
{
	struct ks8692_spi *ks_spi = spi_master_get_devdata(master);

	if (ks_spi->chipselect & 2) {
		ks_spi_write(ks_spi, KS8692_SPI_CTRL, 0);
		ks_spi->chipselect = 0;
		spi_set_cs(ks_spi->last_spi, false);
	}

	/* Enable SPI to transfer and receive data */
	ks_spi_write(ks_spi, KS8692_SPI_CTRL, SPI_ENABLE);
	ks_spi->chipselect = 1;
	start_cnt = KS_R(KS8692_TIMER1_COUNTER);
	return 0;
}

static int ks8692_spi_unprepare_hardware(struct spi_master *master)
{
	struct ks8692_spi *ks_spi = spi_master_get_devdata(master);

	if (ks_spi->xfer.tx_max < KS_TX_FIFO_SIZE) {
		chk_tx_empty(ks_spi);

		if (start_cnt && !ks_spi->xfer.rx_len[0] &&
		    ks_spi->div_rate > 32) {
			u32 cnt;
			u64 clk;
			u32 rem;

			stop_cnt = KS_R(KS8692_TIMER1_COUNTER);
			cnt = stop_cnt - start_cnt;
			clk = cnt;
			clk *= 1000;
			clk = div_u64_rem(clk, ksz_system_bus_clock, &rem);
			cnt = (u32) clk;
			if (cnt < 15) {
				cnt = 15 - cnt;
				udelay(cnt);
			}
		}
		ks_spi_write(ks_spi, KS8692_SPI_CTRL, 0);
		ks_spi->chipselect = 0;
		spi_set_cs(ks_spi->last_spi, false);
	} else {
		ks_spi->chipselect |= 2;
		schedule_work(&ks_spi->cs_end);
	}
	return 0;
}

static int ks8692_spi_transfer_one_message(struct spi_master *master,
	struct spi_message *m)
{
	struct ks8692_spi *ks_spi;
	struct spi_transfer	*t = NULL;
	unsigned		cs_change;
	int			status;
	int			do_setup = -1;
	struct spi_device	*spi = m->spi;

	cs_change = 1;
	status = 0;

	ks_spi = spi_master_get_devdata(master);
	for (ks_spi->rx_xfer = 0; ks_spi->rx_xfer < 16; ks_spi->rx_xfer++)
		ks_spi->xfer.rx_len[ks_spi->rx_xfer] = 0;
	ks_spi->rx_xfer = 0;
	ks_spi->xfer.rx_off = 0;
	ks_spi->xfer.tx_len = 0;
	ks_spi->xfer.tx_max = 0;

	list_for_each_entry(t, &m->transfers, transfer_list) {
		const u8	*tx_buf = t->tx_buf;
		u8		*rx_buf = t->rx_buf;
		unsigned	len = t->len;

		if (!t->len)
			break;
		if (tx_buf != NULL) {
			ks_spi->xfer.tx_len += len;
			if (rx_buf != NULL) {
				unsigned tx_len;

				/* Find the actual read length. */
				for (tx_len = 1; tx_len < len; tx_len++)
					if (rx_buf[tx_len] !=
					    tx_buf[tx_len])
						break;
				ks_spi->xfer.rx_len[0] = len - tx_len;
				ks_spi->xfer.rx_off = tx_len;
				ks_spi->xfer.tx_len = tx_len;
				break;
			}
			status = 1;
		}
		if (rx_buf != NULL) {
			if (ks_spi->rx_xfer == 16)
				break;
			ks_spi->xfer.rx_len[ks_spi->rx_xfer] = len;
			ks_spi->rx_xfer++;
		}
	}
	ks_spi->xfer.tx_max = ks_spi->xfer.tx_len;

	ks_spi->last_spi = m->spi;
	spi_set_cs(m->spi, true);
	ks_spi->rx_xfer = 0;
	list_for_each_entry(t, &m->transfers, transfer_list) {
		if (!t->len)
			break;

		/* override speed or wordsize? */
		if (t->speed_hz || t->bits_per_word)
			do_setup = 1;

		/* init (-1) or override (1) transfer params */
		if (do_setup != 0) {
			status = ks8692_spi_setupxfer(spi, t);
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
			ks8692_spi_chipsel(spi, true);
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
			status = ks8692_spi_txrx(spi, t);
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
			ks8692_spi_chipsel(spi, false);
		}
	}

	m->status = status;

	/* normally deactivate chipselect ... unless no error and
	 * cs_change has hinted that the next message will probably
	 * be for this chip too.
	 */
	if (!(status == 0 && cs_change)) {
		ks8692_spi_chipsel(spi, false);
	}
	spi_finalize_current_message(master);

	return status;
}

static int ks8692_spi_probe(struct platform_device *pdev)
{
	struct ks8692_spi *ks_spi;
	struct spi_master *master;
	struct resource *res;
	int err = 0;

	master = spi_alloc_master(&pdev->dev, sizeof(struct ks8692_spi));
	if (master == NULL) {
		dev_err(&pdev->dev, "No memory for spi_master\n");
		err = -ENOMEM;
		goto err_nomem;
	}

	ks_spi = spi_master_get_devdata(master);
	memset(ks_spi, 0, sizeof(struct ks8692_spi));

	ks_spi->master = spi_master_get(master);
	ks_spi->dev = &pdev->dev;

	DBG_PRINT("pdev=0x%08x, ks_spi=0x%08x, ks_spi->dev=0x%08x\n",
		(int)pdev, (int)ks_spi, (int)ks_spi->dev);

	platform_set_drvdata(pdev, ks_spi);
	init_completion(&ks_spi->tx_completion);
	init_completion(&ks_spi->rx_completion);
	ks_spi->tx_wait = 0;
	ks_spi->rx_wait = 0;
	INIT_WORK(&ks_spi->cs_end, ks_cs_end);

	/* setup master bus number */
	master->bus_num = pdev->id;

	master->setup = ks8692_spi_setup;
	master->prepare_transfer_hardware = ks8692_spi_prepare_hardware;
	master->unprepare_transfer_hardware = ks8692_spi_unprepare_hardware;
	master->transfer_one_message = ks8692_spi_transfer_one_message;
	master->num_chipselect = 4;
	master->mode_bits = MODEBITS;

	spin_lock_init(&ks_spi->hwlock);

	/* find and map our resources */

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "Cannot get IORESOURCE_MEM\n");
		err = -ENOENT;
		goto err_no_iores;
	}

	ks_spi->ioarea = request_mem_region(res->start,
		(res->end - res->start) + 1, pdev->name);
	if (ks_spi->ioarea == NULL) {
		dev_err(&pdev->dev, "Cannot reserve region\n");
		err = -ENXIO;
		goto err_no_iores;
	}

	/* SPI controller virtual address */
	ks_spi->regBase = VIO(KS8692_SPI_BASE);

	ks_spi->irq = platform_get_irq(pdev, 0);
	if (ks_spi->irq < 0) {
		dev_err(&pdev->dev, "No IRQ specified\n");
		err = -ENOENT;
		goto err_no_iomap;
	}

	err = request_irq(ks_spi->irq, ks8692_spi_irq, 0, "spi", ks_spi);
	if (err) {
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		goto err_no_iomap;
	}

	/* program defaults into the registers */

	ks_spi_reset(ks_spi);
	ks_spi_init(ks_spi);

	/* Get System clock  SYSCLK */
	ks_spi_getclk(ks_spi);

	/* init SPI timer */
	spi_timer_init(ks_spi);

	/* register our spi controller */
	do {
		int i;
		int *cs_gpios = pdev->dev.platform_data;

		if (-ENOENT == cs_gpios[0])
			break;
		master->cs_gpios = cs_gpios;

		for (i = 0; i < master->num_chipselect; i++) {
			if (-ENOENT == cs_gpios[i])
				break;
			err = gpio_request(cs_gpios[i], "KSZ");
			gpio_direction_output(cs_gpios[i], 1);
		}
	} while (0);
	err = spi_register_master(master);
	if (err) {
		dev_err(&pdev->dev, "Failed to register SPI master\n");
		goto err_register;
	}

#if (1)
	printk(KERN_INFO "%s at 0x%08x ioaddr 0x%08x irq %d\n", pdev->name,
		(int)ks_spi->ioarea, (int)ks_spi->regBase, ks_spi->irq);
#endif

	return 0;

err_register:
	free_irq(ks_spi->irq, ks_spi);

err_no_iomap:
	if (ks_spi->ioarea)
		release_resource(ks_spi->ioarea);

err_no_iores:
	spi_master_put(ks_spi->master);

err_nomem:
	return err;
}

static int ks8692_spi_remove(struct platform_device *dev)
{
	struct ks8692_spi *ks_spi = platform_get_drvdata(dev);

	del_timer(&ks_spi->tx_timer);
	del_timer(&ks_spi->rx_timer);

	platform_set_drvdata(dev, NULL);

	spi_unregister_master(ks_spi->master);

	free_irq(ks_spi->irq, ks_spi);

	release_resource(ks_spi->ioarea);

	spi_master_put(ks_spi->master);
	return 0;
}

static struct platform_driver ks8692_spidrv = {
	.probe		= ks8692_spi_probe,
	.remove		= ks8692_spi_remove,
	.driver		= {
		.name	= KS8692_SPI_DRIVER,
		.owner	= THIS_MODULE,
	},
};

module_platform_driver(ks8692_spidrv);

MODULE_DESCRIPTION("Micrel Pegasus SPI Driver");
MODULE_LICENSE("GPL");
