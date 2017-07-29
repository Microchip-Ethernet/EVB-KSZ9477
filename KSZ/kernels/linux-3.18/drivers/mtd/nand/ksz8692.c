/*
 * Micrel Pegasus NAND driver
 *
 * Copyright (C) 2009-2015 Micrel, Inc.
 *
 * Based on generic platform driver by Vitaly Wool <vitalywool@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/io.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <mach/platform.h>


/* ------------------------------------------------------------------------- */

#define NAND_HW_READ(b, a)  readl((void *)((char *)(b) + a))
#define NAND_HW_WRITE(b, a, d)  writel(d, (void *)((char *)(b) + a))
#define NAND_BUSY()  KS8692_READ_REG(KS8692_NAND_BUSY_STATUS)


#define NAND_READY_CMD  0x10


static int nand_max_bank = 1;

static int nand_auto_page;
static int nand_bank;

static int nand_page_shift;
static int nand_bank_shift;
static int nand_oob_shift;
static int nand_size_shift;

static int nand_read_ptr;
static u_char nand_data_byte[4];
static u_int *nand_data_ptr = (u_int *) nand_data_byte;

static int ready_command_set;
static int last_command;

static int nand_acc;
static int nand_cnt;
static int nand_started;
static int nand_read_once;

static int nand_erase_size;
static int nand_sector_size;

/* ------------------------------------------------------------------------- */

static void nand_r_cmd(struct nand_chip *this)
{
	readl(this->IO_ADDR_W);
	nand_cnt++;
	nand_acc++;
}

static u_int nand_r_data(struct nand_chip *this)
{
	nand_cnt++;
	nand_acc++;
	return readl(this->IO_ADDR_R);
}

static void nand_w_cmd(struct nand_chip *this, u_int cmd)
{
	writel(cmd, this->IO_ADDR_W);
	nand_cnt++;
	nand_acc++;
}

static int nand_dev_ready(struct mtd_info *mtd)
{
#define READY_TRIES  800

	static int tries = READY_TRIES;
	int ready = !(NAND_BUSY() & (1 << nand_bank));

	if (ready)
		tries = READY_TRIES;
	else {
		--tries;
		if (0 == tries) {
			tries = READY_TRIES;
			ready = 1;
		}
	}
	return ready;
}

/**
 * nand_read_byte - [DEFAULT] read one byte from the chip
 * @mtd:	MTD device structure
 *
 * Default read function for 8bit buswith
 */
static u_char nand_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *this = mtd->priv;

	nand_read_ptr &= 3;
	if (!nand_read_ptr)
		*nand_data_ptr = nand_r_data(this);
	return nand_data_byte[nand_read_ptr++];
}

static void nand_write_cmd(struct mtd_info *mtd, u_int data)
{
	struct nand_chip *this = mtd->priv;
	int need_ready_command = 0;

	/* Need to write a special command to make hardware accept read/write
	   commands.
	*/
	if (NAND_READY_CMD == data)
		ready_command_set = 1;
	else if (NAND_CMD_READ0 == data ||
			NAND_CMD_READ1 == data ||
			NAND_CMD_SEQIN == data ||
			NAND_CMD_READOOB == data)
		need_ready_command = 1;
	if (need_ready_command && !ready_command_set) {
		nand_w_cmd(this, NAND_READY_CMD);
		if (nand_auto_page)
			nand_r_cmd(this);
		ready_command_set = 1;
	}
	last_command = data;

	/* Following commands have bank parameter. */
	switch (data) {
	case NAND_CMD_RESET:
	case NAND_CMD_STATUS:
	case NAND_CMD_READID:
		data |= nand_bank << NAND_CMD_BANK_SHIFT;
		break;
	}

	nand_w_cmd(this, data);

	/* Following commands will cause hardware not to accept read/write
	   commands.
	*/
	if (NAND_CMD_READ0 == data ||
			NAND_CMD_READ1 == data ||
			NAND_CMD_SEQIN == data ||
			NAND_CMD_READOOB == data)
		ready_command_set = 0;

	/* Need to write to data register to send read command. */
	if (NAND_CMD_READ0 == data ||
			NAND_CMD_READ1 == data ||
			NAND_CMD_READOOB == data)
		writel(0, this->IO_ADDR_R);

	/* Reset read data pointer. */
	nand_read_ptr = 0;

	/* A hack to return the right IDs when there are 5 instead of 4. */
	if (NAND_CMD_READID == (data & 0xFF)) {
		udelay(10);
		*nand_data_ptr = nand_r_data(this);
		data = NAND_HW_READ(this->IO_ADDR_R, KS8692_NAND_ID0);
		nand_cnt++;
		nand_acc++;
		if (nand_auto_page && !nand_started) {
			if (1 == nand_auto_page)
				nand_r_cmd(this);
			else
				nand_read_once = 1;
		}
		while (nand_read_ptr < 4 && nand_data_byte[nand_read_ptr] !=
				(data & 0xFF)) {
			nand_read_ptr++;
			data >>= 8;
		}
	}
}

/**
 * nand_command - [DEFAULT] Send command to NAND device
 * @mtd:	MTD device structure
 * @command:	the command to be sent
 * @column:	the column address for this command, -1 if none
 * @page_addr:	the page address for this command, -1 if none
 *
 * Send command to NAND device. This function is used for small page
 * devices (256/512 Bytes per page)
 */
static void nand_command(struct mtd_info *mtd, unsigned command, int column,
	int page_addr)
{
	register struct nand_chip *this = mtd->priv;

	if (column != -1 || page_addr != -1) {
		u_int data;
		u_int nand_column;
		u_int nand_page;

		nand_column = nand_page = 0;
		data = 0;

		if (column != -1) {
			if (mtd->writesize && column >= mtd->writesize &&
					nand_page_shift <= 9) {
				/* OOB area */
				column -= mtd->writesize;
				if (nand_oob_shift > 31)
					data = 1;
				else
					nand_column = 1 << nand_oob_shift;
			}

			/* Emulate NAND_CMD_READOOB */
			if (command == NAND_CMD_READOOB &&
					nand_page_shift > 9) {
				column += mtd->writesize;
				command = NAND_CMD_READ0;
			}

			/* Adjust columns for 16 bit buswidth */
			if (this->options & NAND_BUSWIDTH_16)
				column >>= 1;
			nand_column |= column;
		}
		if (page_addr != -1)
			nand_page = page_addr;

		if (nand_bank_shift >= 31 && nand_max_bank < 4)
			NAND_HW_WRITE(this->IO_ADDR_R, KS8692_NAND_EXT_INDEX,
				nand_bank >> 1);
		else if (nand_oob_shift > 31)
			NAND_HW_WRITE(this->IO_ADDR_R, KS8692_NAND_EXT_INDEX,
				data);

		data = (nand_page << nand_page_shift) + nand_column +
			(nand_bank << nand_bank_shift);
		NAND_HW_WRITE(this->IO_ADDR_R, KS8692_NAND_INDEX, data);
		nand_cnt++;
		nand_acc++;
	}

	/*
	 * Write out the command to the device.
	 */
	/* A hack to read Samsung chips that require a second 0x30 command. */
	if (nand_page_shift > 9 && NAND_CMD_READ0 == command)
		command = NAND_CMD_CE_OFF;
	nand_write_cmd(mtd, command);

	/*
	 * program and erase have their own busy handlers
	 * status and sequential in needs no delay
	*/
	switch (command) {

	case NAND_CMD_PAGEPROG:
	case NAND_CMD_ERASE2:
		if (nand_auto_page) {
			nand_r_cmd(this);
			udelay(10);
		}

	case NAND_CMD_ERASE1:
	case NAND_CMD_SEQIN:
	case NAND_CMD_STATUS:
		return;

	case NAND_CMD_RESET:
		if (this->dev_ready)
			break;
		udelay(this->chip_delay);
		nand_write_cmd(mtd, NAND_CMD_STATUS);
		while (!(this->read_byte(mtd) & NAND_STATUS_READY))
			;
		return;

	/* This applies to read commands */
	default:
		/*
		 * If we don't have access to the busy pin, we apply the given
		 * command delay
		*/
		if (!this->dev_ready) {
			udelay(this->chip_delay);
			return;
		}
	}

	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
	ndelay(100);

	nand_wait_ready(mtd);
}

static int last_chip = -1;

/**
 * nand_select_chip - [DEFAULT] control CE line
 * @mtd:	MTD device structure
 * @chip:	chipnumber to select, -1 for deselect
 *
 * Default select function for 1 chip devices.
 */
static void nand_select_chip(struct mtd_info *mtd, int chip)
{
	struct nand_chip *this = mtd->priv;

	/* A hack to avoid detecing wrong number of chips. */
	if (nand_bank != chip && chip != -1) {
		if (NAND_CMD_READID == last_command) {
			nand_w_cmd(this, NAND_CMD_STATUS);
			if (nand_auto_page)
				nand_r_cmd(this);
			last_command = 0;
		}
	}
	nand_bank = chip;
#if 0
	if (nand_page_shift <= 9)
		this->options &= ~NAND_NO_AUTOINCR;
#endif
	switch (chip) {
	case -1:
		NAND_HW_WRITE(this->IO_ADDR_R,
			KS8692_NAND_COMMAND, NAND_CMD_CE_OFF);
		nand_acc++;
		if (nand_auto_page) {
			if (nand_cnt & 1) {
				if (nand_read_once) {
					nand_read_once = 0;
					nand_r_cmd(this);
				}
			} else
				nand_r_cmd(this);
		}
		nand_cnt = 0;
		nand_bank = 0;
		break;

	default:
		if (chip > nand_max_bank)
			BUG();

#if 1
/* THa  2009/09/25
   The main NAND driver will normally select the chip and unselect it when it
   is executing NAND operations.  One case that it selects the chip twice is
   detecting more than 1 bank of flash chip.
*/
		if (last_chip != -1)
			nand_w_cmd(this, NAND_CMD_CE_OFF);
#endif

		NAND_HW_WRITE(this->IO_ADDR_R, KS8692_NAND_INDEX,
			nand_bank << nand_bank_shift);
/*
 * THa  2009/09/25
 * System may hang in the following code if the controller is not in the right
 * state.
 */
		NAND_HW_READ(this->IO_ADDR_R, KS8692_NAND_DATA);
		nand_cnt += 2;
		nand_acc += 2;
	}
	last_chip = chip;
}

/**
 * nand_write_buf - [DEFAULT] write buffer to chip
 * @mtd:	MTD device structure
 * @buf:	data buffer
 * @len:	number of bytes to write
 *
 * Default write function for 8bit buswith
 */
static void nand_write_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
	int i;
	struct nand_chip *this = mtd->priv;
	u_int *data = (u_int *) buf;

	for (i = 0; i < len; i += 4) {
		writel(*data++, this->IO_ADDR_R);

#if 1
/* THa  2009/09/24
   KSZ9692P booting in NAND flash has different NAND access timing, probably
   because of the auto page feature.
   When writing continually without a delay the system will get stuck.
*/
		if (nand_auto_page)
			udelay(1);
#endif
	}
}

/**
 * nand_read_buf - [DEFAULT] read chip data into buffer
 * @mtd:	MTD device structure
 * @buf:	buffer to store date
 * @len:	number of bytes to read
 *
 * Default read function for 8bit buswith
 */
static void nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	int i;
	struct nand_chip *this = mtd->priv;
	u_int *data = (u_int *) buf;

	for (i = 0; i < len; i += 4)
		*data++ = readl(this->IO_ADDR_R);
}


void board_nand_init(struct nand_chip *nand)
{
	u_int data;

	data = KS8692_READ_REG(KS8692_NAND_FLASH_CFG);

/* THa  2009/09/24
   KSZ9692P booting in NAND flash has different NAND access timing, probably
   because of the auto page feature.
*/
	if (data & NAND_FLASH_AUTO_PAGE)
		nand_auto_page = 1;

	data = NAND_HW_READ(nand->IO_ADDR_R, KS8692_NAND_CONF);

	nand_size_shift = data & NAND_SIZE_8GBIT;
	if (data & NAND_LARGE_BLOCK) {
		nand_erase_size = 0x20000;
		nand_sector_size = 0x800;
		nand_page_shift = 12;
		nand_bank_shift = 24 + nand_size_shift;
		if (data & NAND_WIDTH_16BIT) {
			nand_page_shift--;
			nand_bank_shift--;
		}
		if (nand_auto_page)
			nand_auto_page++;
	} else {
		nand_erase_size = 0x4000;
		nand_sector_size = 0x200;
		nand_page_shift = 9;
		nand_bank_shift = 23 + nand_size_shift;
		nand_oob_shift = nand_bank_shift + 2;
	}
	if (data & NAND_WIDTH_16BIT)
		nand->options |= NAND_BUSWIDTH_16;

	if (data & NAND_4_BANK)
		nand_max_bank = 4;
	else if (data & NAND_2_BANK)
		nand_max_bank = 2;

#if 1
/*
 * THa  2010/02/17
 * The NAND chips in auto-page mode hang during initialization when the
 * controller is not in the right state.
 * These code are like black magic.  Do not try to reason what they actually
 * do.
 */
	if (nand_auto_page) {
		nand_started = readl(nand->IO_ADDR_W);
		readl(nand->IO_ADDR_W);
		readl(nand->IO_ADDR_W);
		readl(nand->IO_ADDR_W);
		if (1 == nand_auto_page) {
			readl(nand->IO_ADDR_W);
			readl(nand->IO_ADDR_W);
		}
	}
#endif
	nand_acc = 0;
	if (1 == nand_auto_page)
		last_chip = 0;
	writel(NAND_CMD_CE_OFF, nand->IO_ADDR_W);

	nand->cmdfunc = nand_command;
	nand->read_byte = nand_read_byte;
	nand->read_buf = nand_read_buf;
	nand->write_buf = nand_write_buf;
}

/* ------------------------------------------------------------------------- */

struct pegasus_nand_data {
	struct nand_chip	chip;
	struct mtd_info		mtd;
	void __iomem		*io_base;
	int			nr_parts;
	struct mtd_partition	*parts;
};

/*
 * Probe for the NAND device.
 */
static int pegasus_nand_probe(struct platform_device *pdev)
{
	struct platform_nand_data *pdata = pdev->dev.platform_data;
	struct pegasus_nand_data *data;
	int res = 0;

	/* Allocate memory for the device structure (and zero it) */
	data = kzalloc(sizeof(struct pegasus_nand_data), GFP_KERNEL);
	if (!data) {
		dev_err(&pdev->dev, "failed to allocate device structure.\n");
		return -ENOMEM;
	}

	data->io_base = ioremap(pdev->resource[0].start,
		pdev->resource[0].end - pdev->resource[0].start + 1);
	if (data->io_base == NULL) {
		dev_err(&pdev->dev, "ioremap failed\n");
		kfree(data);
		return -EIO;
	}

	data->chip.priv = &data;
	data->mtd.priv = &data->chip;
	data->mtd.owner = THIS_MODULE;
	data->mtd.name = (char *) pdev->name;

	data->chip.IO_ADDR_R = data->io_base;
	data->chip.IO_ADDR_W = (void *)((char *)(data->io_base) +
		KS8692_NAND_COMMAND);
	data->chip.cmd_ctrl = pdata->ctrl.cmd_ctrl;
	data->chip.dev_ready = pdata->ctrl.dev_ready;
	data->chip.select_chip = pdata->ctrl.select_chip;
	data->chip.chip_delay = pdata->chip.chip_delay;
	data->chip.options |= pdata->chip.options;

	data->chip.ecc.hwctl = pdata->ctrl.hwcontrol;
	data->chip.ecc.mode = NAND_ECC_SOFT;

	board_nand_init(&data->chip);

	platform_set_drvdata(pdev, data);

	/* Scan to find existance of the device */
	if (nand_scan(&data->mtd, nand_max_bank)) {
		res = -ENXIO;
		goto out;
	}

	res = mtd_device_parse_register(&data->mtd,
		pdata->chip.part_probe_types, 0,
		pdata->chip.partitions, pdata->chip.nr_partitions);

	if (!res)
		return res;

	nand_release(&data->mtd);
out:
	platform_set_drvdata(pdev, NULL);
	iounmap(data->io_base);
	kfree(data);
	return res;
}

/*
 * Remove a NAND device.
 */
static int pegasus_nand_remove(struct platform_device *pdev)
{
	struct pegasus_nand_data *data = platform_get_drvdata(pdev);
	struct platform_nand_data *pdata = pdev->dev.platform_data;

	nand_release(&data->mtd);
	if (data->parts && data->parts != pdata->chip.partitions)
		kfree(data->parts);
	iounmap(data->io_base);
	kfree(data);

	return 0;
}

static struct platform_driver pegasus_nand_driver = {
	.probe		= pegasus_nand_probe,
	.remove		= pegasus_nand_remove,
	.driver		= {
		.name	= "pegasus-nand",
		.owner	= THIS_MODULE,
	},
};

/* ------------------------------------------------------------------------- */

/* Newer kernels use different name. */
#if !defined(CONFIG_MTD_SPLIT_ROOTFS) && defined(CONFIG_MTD_ROOTFS_SPLIT)
#define CONFIG_MTD_SPLIT_ROOTFS
#endif

/* CONFIG_MTD_CFI is not set */
#ifndef CONFIG_MTD_PHYSMAP_LEN
#define CONFIG_MTD_PHYSMAP_LEN  SZ_8M
#endif

#ifdef CONFIG_MTD_CFI
/* Should be zero but leave some space for now for development. */
#if 1
#define CONFIG_CENTAUR_STORAGE_OFFSET  CONFIG_MTD_PHYSMAP_LEN
#else
#define CONFIG_CENTAUR_STORAGE_OFFSET  0
#endif
#else
#define CONFIG_CENTAUR_STORAGE_OFFSET  CONFIG_MTD_PHYSMAP_LEN
#endif

/* This is the size of the image that can be written. */
#define CONFIG_CENTAUR_IMAGE_SIZE	\
	(CONFIG_MTD_PHYSMAP_LEN -	\
	CONFIG_CENTAUR_LOADER_SIZE -	\
	CONFIG_CENTAUR_SPARE_SIZE)

/* This is the size of the root filesystem image that is supposedly read-only.
*/
#if defined(CONFIG_BLK_DEV_INITRD) || defined(CONFIG_CRAMFS) || \
	(defined(CONFIG_SQUASHFS) && !defined(CONFIG_MTD_SPLIT_ROOTFS))
#define CONFIG_CENTAUR_RAMDISK_OFFSET	\
	(CONFIG_CENTAUR_LOADER_SIZE + CONFIG_CENTAUR_KERNEL_SIZE)
#define CONFIG_CENTAUR_RAMDISK_SIZE	\
	(CONFIG_CENTAUR_IMAGE_SIZE -	\
	CONFIG_CENTAUR_KERNEL_SIZE -	\
	CONFIG_CENTAUR_FS_SIZE)
#define CONFIG_CENTAUR_FS_OFFSET	MTDPART_OFS_APPEND
#else
#define CONFIG_CENTAUR_RAMDISK_SIZE	0
#define CONFIG_CENTAUR_FS_OFFSET	\
	(CONFIG_CENTAUR_LOADER_SIZE + CONFIG_CENTAUR_KERNEL_SIZE)
#endif

#if (CONFIG_CENTAUR_FS_SIZE == 0)
#if defined(CONFIG_JFFS2_FS) || defined(CONFIG_MTD_SPLIT_ROOTFS)
#undef CONFIG_CENTAUR_FS_SIZE
#define CONFIG_CENTAUR_FS_SIZE		\
	(CONFIG_CENTAUR_IMAGE_SIZE - CONFIG_CENTAUR_KERNEL_SIZE)
#endif
#endif

static struct mtd_partition nand_partition_info[] = {

#ifndef CONFIG_MTD_CFI
	{
		.name =		"loader",
		.offset =	MTDPART_OFS_APPEND,
		.size =		CONFIG_CENTAUR_LOADER_SIZE,
		.mask_flags =	MTD_WRITEABLE,
	},
	{
		.name =		"image",
		.offset =	MTDPART_OFS_APPEND,
		.size =		CONFIG_CENTAUR_IMAGE_SIZE,
	},

#if (CONFIG_CENTAUR_RAMDISK_SIZE != 0)
	{
		.name =		"rootfs",
		.offset =	CONFIG_CENTAUR_RAMDISK_OFFSET,
		.size =		CONFIG_CENTAUR_RAMDISK_SIZE,
	},
#endif

#if (CONFIG_CENTAUR_FS_SIZE != 0)
	{
#if (CONFIG_CENTAUR_RAMDISK_SIZE != 0)
		.name =		"rootfs_data",
#else
		.name =		"rootfs",
#endif
		.offset =	CONFIG_CENTAUR_FS_OFFSET,
		.size =		CONFIG_CENTAUR_FS_SIZE,
	},
#endif

#if (CONFIG_CENTAUR_SPARE_SIZE != 0)
	{
		.name =		"spare",
		.offset =	CONFIG_MTD_PHYSMAP_LEN -
			CONFIG_CENTAUR_SPARE_SIZE,
		.size =		CONFIG_CENTAUR_SPARE_SIZE,
	},
#endif
#endif

#if (CONFIG_CENTAUR_NAND_SIZE != 0)
	{
		.name =		"storage",
		.offset =	CONFIG_CENTAUR_STORAGE_OFFSET,
		.size =		CONFIG_CENTAUR_NAND_SIZE,
	},
#endif
};

static const char *nand_part_probes[] = { "cmdlinepart", NULL };

static struct platform_nand_data pegasus_nand_platdata = {
	.chip = {
		.nr_chips = 1,
		.chip_offset = 0,
		.nr_partitions = ARRAY_SIZE(nand_partition_info),
		.partitions = nand_partition_info,
		.chip_delay = 10,
		.part_probe_types = nand_part_probes,
	},
	.ctrl = {
		.hwcontrol = 0,
		.dev_ready = nand_dev_ready,
		.select_chip = nand_select_chip,
		.cmd_ctrl = 0,
	},
};

static struct resource pegasus_nand_resource[] = {
	[0] = {
		.start = 0,
		.end   = 0,
		.flags = IORESOURCE_MEM,
	},
};

static struct platform_device nand_flash_device = {
	.name		= "pegasus-nand",
	.num_resources	= ARRAY_SIZE(pegasus_nand_resource),
	.resource	= pegasus_nand_resource,
	.id		= -1,
	.dev		= {
		.platform_data = &pegasus_nand_platdata,
	}
};

static int __init pegasus_nand_init(void)
{
	unsigned int nand_base;

	nand_base = KS8692_READ_REG(KS8692_NAND_FLASH_CFG);
	nand_base &= NAND_FLASH_BASE_MASK;
	pegasus_nand_resource[0].start = nand_base;
	pegasus_nand_resource[0].end = nand_base + 0x8080 - 1;

	platform_device_register(&nand_flash_device);
	return platform_driver_register(&pegasus_nand_driver);
}

static void __exit pegasus_nand_exit(void)
{
	platform_driver_unregister(&pegasus_nand_driver);
	platform_device_unregister(&nand_flash_device);
}

module_init(pegasus_nand_init);
module_exit(pegasus_nand_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Micrel, Inc.");
MODULE_DESCRIPTION("Micrel Pegasus NAND driver");
