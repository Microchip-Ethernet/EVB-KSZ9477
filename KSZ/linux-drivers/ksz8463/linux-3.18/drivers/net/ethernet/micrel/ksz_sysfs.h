/**
 * Microchip switch common sysfs header
 *
 * Copyright (c) 2016 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef KSZ_SYSFS_H
#define KSZ_SYSFS_H


#ifndef get_private_data

#ifndef get_sysfs_data
static void get_sysfs_data_(struct net_device *dev,
	struct semaphore **proc_sem, struct ksz_port **port)
{}

#define get_sysfs_data		get_sysfs_data_
#endif

static void get_private_data_(struct device *d, struct semaphore **proc_sem,
	struct ksz_sw **sw, struct ksz_port **port)
{
	if (d->bus && (
#if defined(__LINUX_SPI_H)
	    d->bus == &spi_bus_type
#endif
#if defined(__LINUX_SPI_H) && defined(_LINUX_I2C_H)
	    ||
#endif
#if defined(_LINUX_I2C_H)
	    d->bus == &i2c_bus_type
#endif
#if !defined(__LINUX_SPI_H) && !defined(_LINUX_I2C_H)
	    d->bus
#endif
	    )) {
		struct sw_priv *hw_priv;

		hw_priv = dev_get_drvdata(d);
		if (port && hw_priv->phydev) {
			struct phy_priv *phydata;

			phydata = hw_priv->phydev->priv;
			*port = phydata->port;
		}
		*proc_sem = &hw_priv->proc_sem;
		*sw = &hw_priv->sw;
	} else {
		struct net_device *dev;
		struct ksz_port *p = NULL;

		dev = to_net_dev(d);
		get_sysfs_data(dev, proc_sem, &p);
		*sw = p->sw;
		if (port)
			*port = p;
	}
}

#define get_private_data	get_private_data_
#endif

#ifndef get_num_val
static int get_num_val_(const char *buf)
{
	int num = -1;

	if ('0' == buf[0] && 'x' == buf[1])
		sscanf(&buf[2], "%x", (unsigned int *) &num);
	else if ('0' == buf[0] && 'b' == buf[1]) {
		int i = 2;

		num = 0;
		while (buf[i]) {
			num <<= 1;
			num |= buf[i] - '0';
			i++;
		}
	} else if ('0' == buf[0] && 'd' == buf[1])
		sscanf(&buf[2], "%u", &num);
	else
		sscanf(buf, "%d", &num);
	return num;
}  /* get_num_val */

#define get_num_val		get_num_val_
#endif

#ifdef USE_SHOW_HELP_
enum {
	SHOW_HELP_NONE,
	SHOW_HELP_ON_OFF,
	SHOW_HELP_NUM,
	SHOW_HELP_HEX,
	SHOW_HELP_HEX_2,
	SHOW_HELP_HEX_4,
	SHOW_HELP_HEX_8,
	SHOW_HELP_SPECIAL,
};

static char *help_formats[] = {
	"",
	"%d%s\n",
	"%u%s\n",
	"0x%x%s\n",
	"0x%02x%s\n",
	"0x%04x%s\n",
	"0x%08x%s\n",
	"%d%s\n",
};

static char *display_strs[] = {
	" (off)",
	" (on)",
};

static char *show_on_off(uint on)
{
	if (on <= 1)
		return display_strs[on];
	return NULL;
}  /* show_on_off */

static ssize_t sysfs_show(ssize_t len, char *buf, int type, int chk, char *ptr,
	int verbose)
{
	if (type) {
		if (verbose) {
			if (SHOW_HELP_ON_OFF == type)
				ptr = show_on_off(chk);
		}
		len += sprintf(buf + len, help_formats[type], chk, ptr);
	}
	return len;
}  /* sysfs_show */
#endif

static int alloc_dev_attr(struct attribute **attrs, size_t attr_size, int item,
	struct ksz_dev_attr **ksz_attrs, struct attribute ***item_attrs,
	char *item_name, struct ksz_dev_attr **attrs_ptr)
{
	struct attribute **attr_ptr;
	struct device_attribute *dev_attr;
	struct ksz_dev_attr *new_attr;

	*item_attrs = kmalloc(attr_size * sizeof(void *), GFP_KERNEL);
	if (!*item_attrs)
		return -ENOMEM;

	attr_size--;
	attr_size *= sizeof(struct ksz_dev_attr);
	*ksz_attrs = *attrs_ptr;
	*attrs_ptr += attr_size / sizeof(struct ksz_dev_attr);

	new_attr = *ksz_attrs;
	attr_ptr = *item_attrs;
	while (*attrs != NULL) {
		if (item_name && !strcmp((*attrs)->name, item_name))
			break;
		dev_attr = container_of(*attrs, struct device_attribute, attr);
		memcpy(new_attr, dev_attr, sizeof(struct device_attribute));
		strncpy(new_attr->dev_name, (*attrs)->name, DEV_NAME_SIZE);
		if (10 <= item && item <= 15)
			new_attr->dev_name[0] = item - 10 + 'a';
		else
			new_attr->dev_name[0] = item + '0';
		new_attr->dev_attr.attr.name = new_attr->dev_name;
		*attr_ptr = &new_attr->dev_attr.attr;
		new_attr++;
		attr_ptr++;
		attrs++;
	}
	*attr_ptr = NULL;
	return 0;
}

#endif
