/**
 * Micrel Pegasus I2C Controller
 *
 * Copyright (C) 2007 - 2008 Micrel, Inc.
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


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/slab.h>

#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/time.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include <mach/platform.h>
#include <asm/irq.h>
#include <linux/io.h>


#if (0)
#define CONFIG_I2C_DEBUG_BUS
#endif

#ifdef CONFIG_I2C_DEBUG_BUS
#define DBG_PRINT(f, x...) \
	printk(KERN_DEBUG " [%s()]: " f, __func__, ## x)
#else
#define DBG_PRINT(f, x...)	do { } while (0)
#endif


#define KS8692_I2C_DRIVER	"pegasus-i2c"
#define DEFAULT_I2C_BIT_RATE    400000 /* 400000 */      /* 400KHz bit rate */

/* To support RADOM READ operation */

#if (1)
#define TWO_BYTE_ADDRESS
#endif

#ifdef TWO_BYTE_ADDRESS
/* for I2C device required two-byte address fields */
#define I2C_ADDRESS_LEN   2
typedef unsigned short    REG_TYPE;

#else
/* for I2C device required one-byte address fields */
#define I2C_ADDRESS_LEN   1
typedef unsigned char     REG_TYPE;
#endif


struct ks8692_i2c {
	spinlock_t		    lock;
	wait_queue_head_t	wait;

	struct i2c_msg		*msg;

	unsigned int        sysclk;
	unsigned int        bit_rate;
	unsigned long       i2c_status;
	unsigned long       i2c_done;

	void __iomem		*regs;
	struct device		*dev;
	unsigned short      reg_offset;
	int                 regoffset_length;
	int                 irq;
	struct resource		*ioarea;
	struct i2c_adapter	adap;
};

/* irq enable/disable functions */

static inline void ks8692_i2c_disable_irq(struct ks8692_i2c *i2c)
{
	unsigned long tmp;

	tmp = KS8692_READ_REG(KS8692_INT_ENABLE2);
	KS8692_WRITE_REG(KS8692_INT_ENABLE2, tmp & ~INT_I2C);
}

static inline void ks8692_i2c_enable_irq(struct ks8692_i2c *i2c)
{
	unsigned long tmp;

	tmp = KS8692_READ_REG(KS8692_INT_ENABLE2);
	KS8692_WRITE_REG(KS8692_INT_ENABLE2, tmp | INT_I2C);
}


static inline void ks8692_i2c_enable(struct ks8692_i2c *i2c)
{
	unsigned long iic_gcr = readl(i2c->regs + KS8692_I2C_CTRL);

	/* Enable I2C */
	iic_gcr |= I2C_ENABLE;
	writel(iic_gcr, i2c->regs + KS8692_I2C_CTRL);

	DBG_PRINT("iic_gcr 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_CTRL),
		(int)readl(i2c->regs + KS8692_I2C_CTRL));
}

static inline void ks8692_i2c_disable(struct ks8692_i2c *i2c)
{
	unsigned long iic_gcr = readl(i2c->regs + KS8692_I2C_CTRL);

	/* Disable I2C */
	iic_gcr &= ~I2C_ENABLE;
	writel(iic_gcr, i2c->regs + KS8692_I2C_CTRL);

	DBG_PRINT("iic_gcr 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_CTRL),
		(int)readl(i2c->regs + KS8692_I2C_CTRL));
}

/*
 * ks8692_i2c_wait_SCL:
 *
 * Wait for SCL, SDA ready (I2C_SR).
 */
static inline int ks8692_i2c_wait_SCL(struct ks8692_i2c *i2c)
{
	unsigned long orig_jiffies = jiffies;
	unsigned long iic_sr;

	dev_dbg(i2c->dev, "wait_SCL\n");

	/* Allow bus up to 1s to become not busy */
	iic_sr = readl(i2c->regs + KS8692_I2C_STATUS);
	while (!(iic_sr & I2C_SCL) || !(iic_sr & I2C_SDA)) {
		if (signal_pending(current)) {
			pr_debug("I2C: Interrupted\n");
			printk(KERN_DEBUG "%s: Interrupted. iic_sr 0x%08X: %08x\n",
				__func__,
				(int)(i2c->regs + KS8692_I2C_STATUS),
				(int)iic_sr);
			return -EINTR;
		}
		if (time_after(jiffies, orig_jiffies + HZ)) {
			pr_debug("I2C: timeout\n");
			printk(KERN_DEBUG "%s: timeout. iic_sr 0x%08X: %08x\n",
				__func__,
				(int)(i2c->regs + KS8692_I2C_STATUS),
				(int)iic_sr);
			return -EIO;
		}
		schedule();
		iic_sr = readl(i2c->regs + KS8692_I2C_STATUS);
	}

	DBG_PRINT("iic_sr 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_STATUS), (int)iic_sr);
	return 0;
}

/*
 * i2c_wait()
 *
 * Wait for I2C transaction completed.
 * Return number of bytes this transaction complete if no error,
 * otherwise, return -EIO.
 */
static int i2c_wait(struct ks8692_i2c *i2c, unsigned timeout, int writing)
{
	unsigned long orig_jiffies = jiffies;
	int ret_length;
	int result = 0;

	if (i2c->irq == 0) {
		DBG_PRINT(" polling I2C_SCR, timeout=%d, writing=%d.\n",
			(int)timeout, (int)writing);

		/* wait I2C transaction completed by polling */
		while (!(readl(i2c->regs + KS8692_I2C_COMMAND) & I2C_START)) {
			schedule();
			if (time_after(jiffies, orig_jiffies + timeout)) {
				pr_debug("I2C: timeout\n");
				result = -EIO;
				break;
			}
		}

		/* Record I2C transaction status */
		i2c->i2c_status = readl(i2c->regs + KS8692_I2C_STATUS);
	} else {
		DBG_PRINT(" wait for I2C_SCR by interrupt, timeout=%d, writing=%d.\n",
			(int)timeout, (int)writing);

		/* Interrupt mode */
		result = wait_event_interruptible_timeout(i2c->wait,
			i2c->i2c_done, timeout * HZ);

		DBG_PRINT("iic_sr 0x%08X: %08x, i2c_done=%d, result=0x%x\n",
			(int)(i2c->regs + KS8692_I2C_STATUS),
			(int)i2c->i2c_status, (int)i2c->i2c_done, (int)result);

		if (unlikely(result < 0)) {
			pr_debug("I2C: wait interrupted\n");
			printk(KERN_DEBUG "%s: wait interrupted. result %d\n",
				__func__,
				result);
		} else if (unlikely(!i2c->i2c_done)) {
			unsigned long iic_scr;
			iic_scr = readl(i2c->regs + KS8692_I2C_COMMAND);
			pr_debug("I2C: wait timeout\n");
			printk(KERN_DEBUG "%s: wait timeout. iic_scr 0x%08X: %08x\n",
				__func__,
				(int)(i2c->regs + KS8692_I2C_COMMAND),
				(int)iic_scr);
			result = -ETIMEDOUT;
		}
	}

	if (result < 0)
		return result;

	if (!(i2c->i2c_status & I2C_DATA_DONE) ||
			(i2c->i2c_status & I2C_ERROR_MASK)) {
		pr_debug("I2C: %s transaction is not completed due to error %08x\n",
			writing ? "write" : "read" , (int)i2c->i2c_status);
		printk(KERN_DEBUG "%s: %s transaction is not completed due to error %08x\n",
			__func__,
			writing ? "write" : "read" , (int)i2c->i2c_status);
		return -EIO;
	}

	/* Get transaction byte done from I2C */
	if (writing)
		ret_length = (i2c->i2c_status & I2C_BYTE_WRITE_MASK) >> 12;
	else
		ret_length = (i2c->i2c_status & I2C_BYTE_READ_MASK) >> 8;

	DBG_PRINT("%s transaction is completed by %d bytes. (%08x)\n",
		writing ? "write" : "read" , (int)ret_length,
		(int)i2c->i2c_status);

	return ret_length;
}

static inline int ks8692_i2c_start(struct ks8692_i2c *i2c, unsigned timeout,
	int writing, int *ret_length)
{
	/* Wait for SCL, SDA ready */
	if (ks8692_i2c_wait_SCL(i2c) != 0)
		return -1;

	/* reset i2c_done wait_event condition */
	i2c->i2c_done = 0;
	i2c->i2c_status = 0;

	/* Start I2C transaction */
	writel(I2C_START, i2c->regs + KS8692_I2C_COMMAND);
	DBG_PRINT("iic_scr 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_COMMAND), (int)I2C_START);

	/* Wait for I2C transaction completed */
	*ret_length = i2c_wait(i2c, timeout, writing);

	return 0;
}


/* ks8692_i2c_irq
 *
 * top level IRQ servicing routine
 */

static irqreturn_t ks8692_i2c_irq(int irqno, void *dev_id)
{
	struct ks8692_i2c *i2c = dev_id;
	unsigned long iic_scr;
	unsigned long isr;

	/* Read interrupt status */
	isr = KS8692_READ_REG(KS8692_INT_STATUS2);

	if (isr & INT_I2C) {
		iic_scr = readl(i2c->regs + KS8692_I2C_COMMAND);
		DBG_PRINT("iic_scr 0x%08X: %08x\n",
			(int)(i2c->regs + KS8692_I2C_COMMAND), (int)iic_scr);

		/* I2C transaction is completed */
		if (!(iic_scr & I2C_START)) {
			i2c->i2c_done = 1;

			/* Record I2C transaction status to clear interrupt
			 * source
			 */
			i2c->i2c_status = readl(i2c->regs + KS8692_I2C_STATUS);

			DBG_PRINT("iic_sr 0x%08X: %08x\n",
				(int)(i2c->regs + KS8692_I2C_STATUS),
				(int)i2c->i2c_status);

			wake_up_interruptible(&i2c->wait);
		}

		/* Ack I2C interrupt */
	} else {
		iic_scr = readl(i2c->regs + KS8692_I2C_COMMAND);
		printk(KERN_DEBUG "%s: unexpect interrupt. iic_sr 0x%08X: %08x\n",
			__func__,
			(int)(i2c->regs + KS8692_I2C_COMMAND), (int)iic_scr);
	}

	return IRQ_HANDLED;
}


/*
 * ks8692_i2c_write_offset()
 *
 * issuing two byte of register offset 'reg_offset'
 * following the device address 'dev_addr' to I2C device.
 */
static inline int ks8692_i2c_write_offset(struct ks8692_i2c *i2c,
	unsigned int dev_addr, REG_TYPE reg_offset, int regoffset_length)
{
	unsigned timeout = i2c->adap.timeout;
	unsigned long  iic_gcr = readl(i2c->regs + KS8692_I2C_CTRL);
	unsigned long  iic_ar;
	int actuallyWriteLen = 0;

	DBG_PRINT("dev_addr=%x, reg_offset=%x, regoffset_length=%d, timeout=%d\n",
		(int)dev_addr, (int)reg_offset, (int)regoffset_length,
		(int)timeout);

	/* Don't issure Stop bit in the 1st operation when write 2-byte device
	 * address offset.
	 */
	iic_gcr &= ~I2C_STOP_BIT;
	writel(iic_gcr, i2c->regs + KS8692_I2C_CTRL);
	DBG_PRINT("iic_gcr 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_CTRL), (int)iic_gcr);

	/* write register offset into I2C_WDR0 */
	writel(reg_offset, i2c->regs + KS8692_I2C_WRITE_DATA0);
	DBG_PRINT("I2C_WDR0 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_WRITE_DATA0),
		(int)readl(i2c->regs + KS8692_I2C_WRITE_DATA0));

	/* Set I2C_AR */
	iic_ar = (((regoffset_length << 20) & I2C_BYTE_TO_WRITE_MASK) |
		((dev_addr & I2C_ADDR_MASK) | I2C_WRITE));
	writel(iic_ar, i2c->regs + KS8692_I2C_ADDR);
	DBG_PRINT("iic_ar 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_ADDR), (int)iic_ar);

	/* Start I2C transaction */
	if (ks8692_i2c_start(i2c, timeout, 1, &actuallyWriteLen) == -1)
		return -1;

	/* Wait for I2C transaction completed */
	if (actuallyWriteLen != regoffset_length)
		return -1;

	return 0;
}


/*
 * ks8692_i2c_prepare_for_read()
 *
 * Initiates a current address read.
 */
static inline void ks8692_i2c_prepare_for_read(struct ks8692_i2c *i2c,
	unsigned int dev_addr, int read_length)
{
	unsigned long  iic_gcr = readl(i2c->regs + KS8692_I2C_CTRL);
	unsigned long  iic_ar;

	/* Now, issure Stop bit for 2nd read operation. */
	iic_gcr |= I2C_STOP_BIT;
	writel(iic_gcr, i2c->regs + KS8692_I2C_CTRL);
	DBG_PRINT("iic_gcr 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_CTRL), (int)iic_gcr);

	/* Set I2C_AR */
	iic_ar = (((read_length << 16) & I2C_BYTE_TO_READ_MASK) |
		((dev_addr & I2C_ADDR_MASK) | I2C_READ));
	writel(iic_ar, i2c->regs + KS8692_I2C_ADDR);
	DBG_PRINT("iic_ar 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_ADDR), (int)iic_ar);
}

/*
 * ks8692_i2c_prepare_for_write()
 *
 * Prepare for write operation.
 */
static inline void ks8692_i2c_prepare_for_write(struct ks8692_i2c *i2c,
	unsigned int dev_addr, int write_length)
{
	unsigned long  iic_gcr = readl(i2c->regs + KS8692_I2C_CTRL);
	unsigned long  iic_ar;

	/* Now, issure Stop bit for 2nd read operation. */
	iic_gcr |= I2C_STOP_BIT;
	writel(iic_gcr, i2c->regs + KS8692_I2C_CTRL);
	DBG_PRINT("iic_gcr 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_CTRL), (int)iic_gcr);

	/* Set I2C_AR */
	iic_ar = (((write_length << 20) & I2C_BYTE_TO_WRITE_MASK) |
		((dev_addr & I2C_ADDR_MASK) | I2C_WRITE));
	writel(iic_ar, i2c->regs + KS8692_I2C_ADDR);

	DBG_PRINT("iic_ar 0x%08X: %08x\n",
		(int)(i2c->regs + KS8692_I2C_ADDR), (int)iic_ar);
}

/*
 * ks8692_i2c_byte_write()
 *
 * Write data to I2C device chip address 'dev_addr', to
 * data buffer 'data' by 'length' through KS8692 I2C controller.
 * we only support support 'BYTE WRITE' in this driver.
 */
static int ks8692_i2c_byte_write(struct ks8692_i2c *i2c, struct i2c_msg *msg,
	int restart)
{
	unsigned int  dev_addr = (msg->addr & 0x7f) << 1;
	REG_TYPE  reg_offset = *(REG_TYPE *)msg->buf;
	u8  *data = msg->buf;
	int  length = msg->len;
	unsigned timeout = i2c->adap.timeout;
	int    writeLen = 0, writeLenTemp;
	int    actuallyWriteLen, regLen;
	unsigned long regData = 0;
	int i;

	DBG_PRINT("dev_addr=%x, reg_offset=%x, data=%08x, length=%d, timeout=%d, restart=%d\n",
		(int)dev_addr, (int)reg_offset, (int)data, (int)length,
		(int)timeout, (int)restart);

	/* Just to scan the I2C device on the bus */
	if (length == 0) {
		/* Configure I2C controller, prepare I2C read operation */
		ks8692_i2c_prepare_for_write(i2c, dev_addr, writeLen);

		/* Start I2C transaction */
		if (ks8692_i2c_start(i2c, timeout, 1, &actuallyWriteLen) == -1)
			return -1;

		/* Wait for I2C transaction completed */
		if (actuallyWriteLen != writeLen)
			return -1;

		printk(KERN_DEBUG "%s: Found I2C device with device address %x on I2C bus.\n",
			__func__,
			(int)dev_addr);
		return 0;
	}

	/* record this operation's 'word address' and 'word address' length */
	if (!restart) {
		i2c->regoffset_length = msg->len;
		if (i2c->regoffset_length == 2) {
			i2c->reg_offset =  ((reg_offset & 0xff00) >> 8);
			i2c->reg_offset |= ((reg_offset & 0x00ff) << 8);
		} else
			i2c->reg_offset = reg_offset;
	} else {
		/* Some data to write */
		while (length > 0) {
			writeLen = length > 1 ? 1 : length;
			writeLenTemp = writeLen;

			/* Configure I2C controller, prepare I2C read operation
			 */
			ks8692_i2c_prepare_for_write(i2c, dev_addr,
				(writeLen + i2c->regoffset_length));

			/* write register offset into I2C_WDR0 */
			regData = i2c->reg_offset;

			/* Write data to I2C_WDR0 */
			regLen = writeLenTemp > 2 ? 2 : writeLenTemp;
			for (i = 0; i < regLen; i++)
				regData |= (*data++ << (i*8)) << 16;
			writel(regData, i2c->regs + KS8692_I2C_WRITE_DATA0);
			DBG_PRINT("I2C_WDR0 0x%08X: %08x\n",
				(int)(i2c->regs + KS8692_I2C_WRITE_DATA0),
				(int)readl(i2c->regs + KS8692_I2C_WRITE_DATA0));

			/* Write to I2C_WDR1 */
			writeLenTemp -= regLen;
			if (writeLenTemp > 0) {
				regData = 0;
				regLen = (writeLenTemp > 4) ? 4 : writeLenTemp;
				for (i = 0; i < regLen; i++)
					regData |= (*data++ << (i*8));
				writel(regData, i2c->regs +
					KS8692_I2C_WRITE_DATA1);
				DBG_PRINT("I2C_WDR1 0x%08X: %08x\n",
					(i2c->regs + KS8692_I2C_WRITE_DATA1),
					readl(i2c->regs +
						KS8692_I2C_WRITE_DATA1));
			}

			/* Start I2C transaction */
			if (ks8692_i2c_start(i2c, timeout, 1, &actuallyWriteLen)
					== -1)
				return -1;

			/* Wait for I2C transaction completed */
			if (actuallyWriteLen != (writeLen +
					i2c->regoffset_length))
				return -1;

			i2c->reg_offset += writeLen;
			length -= writeLen;

			mdelay(timeout);
		}
	}

	return 0;
}

/*
 * ks8692_i2c_random_read()
 *
 * Read data from I2C device chip address 'dev_addr', to
 * data buffer 'data' by 'length' through KS8692 I2C controller.
 *
 * Since the application has already set the register offset by WRITE operation
 * with the length of address fields before call READ operation. So here,
 * we only support support 'RANDOM READ'.
 * If user application can support 'RANDOM READ', then, in the beginning of
 * msg->buf[] must contains register offset value.
 */
static int ks8692_i2c_random_read(struct ks8692_i2c *i2c, struct i2c_msg *msg,
	int restart)
{
	unsigned int  dev_addr = (msg->addr & 0x7f) << 1;
	REG_TYPE  reg_offset = *(REG_TYPE *)msg->buf;
	u8  *data = msg->buf;
	int  length = msg->len;
	unsigned timeout = i2c->adap.timeout;
	int    readLen, readLenTemp;
	int    actuallyReadLen = 0;
	unsigned long   regData;
	unsigned char  *bData;
	int i;

	DBG_PRINT("dev_addr=%x, reg_offset=%x, data=%08x, length=%d, timeout=%d, restart=%d\n",
		(int)dev_addr, (int)reg_offset, (int)data, (int)length,
		(int)timeout, (int)restart);

	/* record this operation's 'word address' and 'word address' length */
	if (!restart) {
		i2c->regoffset_length = msg->len;
		if (i2c->regoffset_length == 2) {
			i2c->reg_offset =  ((reg_offset & 0xff00) >> 8);
			i2c->reg_offset |= ((reg_offset & 0x00ff) << 8);
		} else
			i2c->reg_offset = reg_offset;
	} else {
		while (length > 0) {
			readLen = length > 1 ? 1 : length;

			/*
			 * First, transfer I2C device address follow by 2-byte
			 * device address offset to I2C bus with 'dummy' WRITE
			 *operation.
			 */
			if (ks8692_i2c_write_offset(i2c, dev_addr,
				i2c->reg_offset, i2c->regoffset_length) == -1)
				return -1;

			/*
			 * Second, transfer I2C device address to I2C bus with
			 * READ operation.
			 * (Initiates a current address read).
			 */
			ks8692_i2c_prepare_for_read(i2c, dev_addr, readLen);

			/* Start I2C transaction */
			if (ks8692_i2c_start(i2c, timeout, 0, &actuallyReadLen)
					== -1)
				return -1;

			if (actuallyReadLen != readLen)
				return -1;

			/* Read data from I2C_RDR0 */
			regData = readb(i2c->regs + KS8692_I2C_READ_DATA0);
			bData = (unsigned char *)&regData;
			DBG_PRINT("I2C_RDR0 0x%08X: %08x\n",
				(int)(i2c->regs + KS8692_I2C_READ_DATA0),
				(int)regData);

			readLenTemp = readLen > 4 ? 4 : readLen;
			for (i = 0; i < readLenTemp; i++)
				*data++ = *bData++;

			/* Read data from I2C_RDR1 */
			readLen -= readLenTemp;
			if (readLen > 0) {
				regData = readb(i2c->regs +
					KS8692_I2C_READ_DATA1);
				bData = (unsigned char *)&regData;
				DBG_PRINT("I2C_RDR1 0x%08X: %08x\n",
					(i2c->regs + KS8692_I2C_READ_DATA1),
					(int)regData);

				for (i = 0; i < readLen; i++)
					*data++ = *bData++;
			}

			i2c->reg_offset += actuallyReadLen;
			length -= actuallyReadLen;

			mdelay(timeout);
		}
	}
	return msg->len;
}


/* ks8692_i2c_xfer
 *
 * first port of call from the i2c bus code when an message needs
 * transferring across the i2c bus.
 */

static int ks8692_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
	int num)
{
	struct ks8692_i2c *i2c = (struct ks8692_i2c *)adap->algo_data;
	struct i2c_msg *pmsg;
	int i;
	int ret = 0;

	DBG_PRINT("num=%d, addr=%04x, flags=%04x, len=%d\n",
		(int)num, (int)msgs->addr, (int)msgs->flags, (int)msgs->len);

	ks8692_i2c_enable(i2c);

	for (i = 0; ret >= 0 && i < num; i++) {
		pmsg = &msgs[i];
		pr_debug("Doing %s %d bytes to 0x%02x - %d of %d messages\n",
			pmsg->flags & I2C_M_RD ? "read" : "write",
			pmsg->len, pmsg->addr, i + 1, num);

		if (pmsg->flags & I2C_M_RD)
			ret = ks8692_i2c_random_read(i2c, pmsg, i);
		else
			ret = ks8692_i2c_byte_write(i2c, pmsg, i);
	}

	mdelay(2);
	ks8692_i2c_disable(i2c);

	return (ret < 0) ? ret : num;
}

/* declare our i2c functionality */
static u32 ks8692_i2c_func(struct i2c_adapter *adap)
{
	return I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR | /* I2C_FUNC_SMBUS_EMUL | */
		I2C_FUNC_PROTOCOL_MANGLING;
}

/* i2c bus registration info */

static struct i2c_algorithm ks8692_i2c_algorithm = {
	.master_xfer		= ks8692_i2c_xfer,
	.functionality		= ks8692_i2c_func,
};


/* ks8692_i2c_setclock
 *
 * work out a divisor for the user requested frequency setting.
 */

static int ks8692_i2c_setclock(struct ks8692_i2c *i2c)
{
	unsigned long  regData;
	unsigned long  bitPeriod;
	unsigned long  fAPB;

	/* Get APB system clock in Hz */
	regData = KS8692_READ_REG(KS8692_SYSTEM_BUS_CLOCK);
	fAPB = regData & SYSTEM_BUS_CLOCK_MASK;
	DBG_PRINT("regData=%08x\n", (int)regData);

	switch (fAPB) {
	case SYSTEM_BUS_CLOCK_200:
		i2c->sysclk = 200 * 1000 * 1000;
		break;
	case SYSTEM_BUS_CLOCK_166:
		i2c->sysclk = 166 * 1000 * 1000;
		break;
	case SYSTEM_BUS_CLOCK_125:
		i2c->sysclk = 125 * 1000 * 1000;
		break;
	case SYSTEM_BUS_CLOCK_50:
	default:
		i2c->sysclk = 50 * 1000 * 1000;
		break;
	}

	bitPeriod = i2c->sysclk / i2c->bit_rate / 8;
	DBG_PRINT("sysclk=%d, bit_rate=%d, bitPeriod=%d(0x%x)\n",
		(int)i2c->sysclk, (int)i2c->bit_rate, (int)bitPeriod,
		(int)bitPeriod);

	/* exceed the device bit period range */
	if (bitPeriod > 0x1FF)
		return -EINVAL;

	/* Set bit period */
	regData = readl(i2c->regs + KS8692_I2C_CTRL);
	DBG_PRINT("%08X: %08x\n", (int)(i2c->regs + KS8692_I2C_CTRL),
		(int)regData);
	regData &= ~(I2C_BIT_PERIOD_MASK | I2C_ENABLE);
	regData |= ((bitPeriod << 1) & I2C_BIT_PERIOD_MASK);
	writel(regData, i2c->regs + KS8692_I2C_CTRL);
	DBG_PRINT("%08X: %08x\n", (int)(i2c->regs + KS8692_I2C_CTRL),
		(int)regData);

	return 0;
}


/* ks8692_i2c_hw_init
 *
 * initialise the controller, set the IO lines and frequency
 */

static int ks8692_i2c_hw_init(struct ks8692_i2c *i2c)
{
	unsigned long  regData;

	/* we need to work out the divisors for the clock... */

	if (ks8692_i2c_setclock(i2c) != 0) {
		dev_err(i2c->dev, "cannot meet bus frequency required\n");
		return -EINVAL;
	}

	/*
	   set timeout to allowe the i2c to complete transaction before aborting
	   for now, just use i2c hardware default value.
	*/
	regData = readl(i2c->regs + KS8692_I2C_CTRL);
	regData &= ~I2C_TIMEOUT_MASK;
	regData |= (0x30 << 16);
	regData |= I2C_STOP_BIT;
	writel(regData, i2c->regs + KS8692_I2C_CTRL);

	return 0;
}

static void ks8692_i2c_free(struct platform_device *pdev)
{
	struct ks8692_i2c *i2c = platform_get_drvdata(pdev);

	if (i2c != NULL) {
		i2c_del_adapter(&i2c->adap);

		if (i2c->irq != 0)
			free_irq(i2c->irq, i2c);

		if (i2c->ioarea != NULL) {
			release_resource(i2c->ioarea);
			kfree(i2c->ioarea);
			i2c->ioarea = NULL;
		}

		platform_set_drvdata(pdev, NULL);
		kfree(i2c);
	}
}

/*
 * Check all resources for the host.
 */
static struct resource *platform_device_resource(struct platform_device *pdev,
	unsigned int mask, int nr)
{
	int i;

	for (i = 0; i < pdev->num_resources; i++)
		if (pdev->resource[i].flags == mask && nr-- == 0)
			return &pdev->resource[i];
	return NULL;
}

/*
 * Check IRQ.
 */
static int platform_device_irq(struct platform_device *pdev, int nr)
{
	int i;

	for (i = 0; i < pdev->num_resources; i++)
		if (pdev->resource[i].flags == IORESOURCE_IRQ && nr-- == 0)
			return pdev->resource[i].start;
	return NO_IRQ;
}

/* ks8692_i2c_probe
 *
 * called by the bus driver when a suitable device is found
*/

static int ks8692_i2c_probe(struct platform_device *pdev)
{
	struct ks8692_i2c *i2c;
	struct resource *res;
	int ret;

	/* alloca/initialize i2c struct */
	i2c = kzalloc(sizeof(struct ks8692_i2c), GFP_KERNEL);
	if (!i2c)
		return -ENOMEM;

	strcpy(i2c->adap.name, KS8692_I2C_DRIVER);
	i2c->adap.algo = &ks8692_i2c_algorithm;
	i2c->adap.owner = THIS_MODULE;
	i2c->adap.class = I2C_CLASS_HWMON;
	i2c->adap.retries = 2;

	init_waitqueue_head(&i2c->wait);
	spin_lock_init(&i2c->lock);

	/* setup info block for the i2c core */

	i2c_set_adapdata(&i2c->adap, i2c);
	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &pdev->dev;

	i2c->dev = &pdev->dev;
	i2c->reg_offset = 0;

	platform_set_drvdata(pdev, i2c);

	/* map the registers */

	res = platform_device_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "cannot find IO resource\n");
		ret = -ENOENT;
		goto out;
	}

	res = request_mem_region(res->start, (res->end-res->start) + 1,
		KS8692_I2C_DRIVER);
	if (res == NULL) {
		dev_err(&pdev->dev, "cannot request IO\n");
		ret = -ENXIO;
		goto out;
	}

	i2c->ioarea = res;

	/* I2C controller virtual address */
	i2c->regs = (void __iomem *) VIO(KS8692_I2C_BASE);

	dev_dbg(&pdev->dev, "registers %p (%p, %p)\n", i2c->regs, i2c->ioarea,
		res);

	/* initialise the i2c controller */
	i2c->bit_rate = DEFAULT_I2C_BIT_RATE;

	ret = ks8692_i2c_hw_init(i2c);
	if (ret != 0)
		goto out;

	/* find the IRQ for this unit (note, this relies on the init call to
	 * ensure no current IRQs pending
	 */
	i2c->irq = 0;

#if (1)
	i2c->irq = platform_device_irq(pdev, 0);
	if (i2c->irq < 0) {
		dev_err(&pdev->dev, "cannot find IRQ\n");
		ret = -ENOENT;
		goto out;
	}

	ret = request_irq(i2c->irq, ks8692_i2c_irq,
		IRQF_DISABLED,
		"i2c", i2c);

	if (ret != 0) {
		dev_err(&pdev->dev, "cannot claim IRQ\n");
		goto out;
	}
#endif

#if (1)
	printk(KERN_INFO "%s at 0x%08x ioaddr 0x%08x irq %d\n",
		i2c->adap.name, (int)i2c->ioarea, (int)i2c->regs, i2c->irq);
#endif

	ret = i2c_add_adapter(&i2c->adap);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to add bus to i2c core\n");
		goto out;
	}

out:
	if (ret < 0)
		ks8692_i2c_free(pdev);

	return ret;
}

/* ks8692_i2c_remove
 *
 * called when device is removed from the bus
*/

static int ks8692_i2c_remove(struct platform_device *pdev)
{
	ks8692_i2c_free(pdev);
	return 0;
}


/* device driver for platform bus bits */

static struct platform_driver ks8592_i2c_driver = {
	.probe		= ks8692_i2c_probe,
	.remove		= ks8692_i2c_remove,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= KS8692_I2C_DRIVER,
	},
};

static int __init ks8692_i2c_init(void)
{
	return platform_driver_register(&ks8592_i2c_driver);
}

static void __exit ks8692_i2c_exit(void)
{
	platform_driver_unregister(&ks8592_i2c_driver);
}

module_init(ks8692_i2c_init);
module_exit(ks8692_i2c_exit);

MODULE_DESCRIPTION("Micrel Pegasus I2C Bus driver");
MODULE_LICENSE("GPL");
