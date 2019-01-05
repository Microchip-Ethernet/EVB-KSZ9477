/**
 * Microchip switch driver API code
 *
 * Copyright (c) 2016-2017 Microchip Technology Inc.
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


#include <stdint.h>
#include <net/if.h>
#include <sys/ioctl.h>

#ifndef KSZ_SW_API_H

/* Data types used in the DLR header file. */

typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

/* Pack structure as necessary. */

#ifndef __packed
#define __packed __attribute__((packed))
#endif

/* Define this for ksz_request. */
#define MAX_REQUEST_SIZE		2000

#include "ksz_req.h"
#include "ksz_sw_api.h"
#endif

#ifdef USE_DEV_IOCTL
#define DEV_IO_SW			0

#define DEV_IOC_DLR			\
	_IOW(DEV_IOC_MAGIC, DEV_IO_SW, struct ksz_request)

struct dev_info {
	int fd;
	u8 *buf;
	int len;
	int index;
	int left;
};

static int sw_recv(struct dev_info *info, u8 data[], int len)
{
	struct ksz_read_msg *msg;
	int n;

	/* There are data left. */
	if (info->left) {
		msg = (struct ksz_read_msg *) &info->buf[info->index];

		/* But not enough. */
		if (info->left < msg->len) {
			memcpy(info->buf, &info->buf[info->index],
				info->left);
			info->index = info->left;
			info->left = 0;
		}
	} else
		info->index = 0;

	/* No more data. */
	if (!info->left) {

		/* Read from device. */
		do {
			/* This will be blocked if no data. */
			n = read(info->fd, &info->buf[info->index],
				info->len - info->index);
#if 0
printf("r: %d %d\n", n, info->index);
#endif
			if (n < 0) {
				printf("read failure\n");
				exit(1);
			}
			info->index += n;
		} while (!n && !info->index);
		info->left = info->index;
		info->index = 0;
#if 0
printf("l: %d i: %d\n", info->left, info->index);
#endif
	}
	msg = (struct ksz_read_msg *) &info->buf[info->index];
	if (msg->len > len) {
printf("  ??  %d; %d, %d %d\n", msg->len, len, info->index, info->left);
		exit(1);
	}
	info->index += msg->len;
	info->left -= msg->len;
#if 0
printf("left: i: %d l: %d; u: %d\n", info->index, info->left, msg->len);
#endif
	msg->len -= 2;

	if (len > msg->len)
		len = msg->len;
	memcpy(data, msg->data, len);
	return len;
}

int sw_init(struct dev_info *dev)
{
	char device[20];

	sprintf(device, "/dev/sw_dev");
	dev->fd = open(device, O_RDWR);
	if (dev->fd < 0) {
		printf("cannot open sw device\n");
		return - 1;
	}
	dev->len = MAX_REQUEST_SIZE;
	dev->buf = malloc(dev->len);
	dev->index = 0;
	dev->left = 0;
	return 0;
}

void sw_exit(struct dev_info *dev)
{
	if (dev->fd <= 0)
		return;
	usleep(10 * 1000);
	close(dev->fd);
	dev->fd = 0;
	free(dev->buf);
}

int sw_ioctl(void *fd, void *req)
{
	struct dev_info *info = fd;

	return ioctl(info->fd, DEV_IOC_DLR, req);
}
#endif

#ifdef USE_NET_IOCTL
struct dev_info {
	int sock;
	char name[20];
};

int sw_ioctl(void *fd, void *req)
{
	struct dev_info *info = fd;
	struct ifreq dev;

	memset(&dev, 0, sizeof(struct ifreq));
	strncpy(dev.ifr_name, info->name, sizeof(dev.ifr_name));
	dev.ifr_data = (char *) req;
	return ioctl(info->sock, SIOCDEVPRIVATE + 13, &dev);
}
#endif


/* Used to indicate which APIs are supported. */
static int sw_version;

/* Used to indicate how many ports are in the switch. */
static int sw_ports;


static void sw_exit_req(void *ptr)
{
	struct ksz_request *req = ptr;

	req->size = SIZEOF_ksz_request;
	req->cmd = DEV_CMD_INFO;
	req->cmd |= DEV_MOD_BASE << 16;
	req->subcmd = DEV_INFO_EXIT;
	req->output = 0;
}  /* sw_exit_req */

static void sw_init_req(void *ptr,
	int capability)
{
	struct ksz_request *req = ptr;

	req->size = SIZEOF_ksz_request + 8;
	req->cmd = DEV_CMD_INFO;
	req->cmd |= DEV_MOD_BASE << 16;
	req->subcmd = DEV_INFO_INIT;
	req->output = capability;
	req->param.data[0] = 'K';
	req->param.data[1] = 'S';
	req->param.data[2] = 'Z';
	req->param.data[3] = 'A';
	req->param.data[4] = 'P';
	req->param.data[5] = 'I';
}  /* sw_init_req */

int sw_dev_exit(void *fd)
{
	struct ksz_request_actual req;
	int rc;

	sw_exit_req(&req);
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* sw_dev_exit */

int sw_dev_init(void *fd,
	int capability, int *version, int *ports)
{
	struct ksz_request_actual req;
	int rc;

	sw_init_req(&req, capability);
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		if ('M' == req.param.data[0] &&
		    'i' == req.param.data[1] &&
		    'c' == req.param.data[2] &&
		    'r' == req.param.data[3]) {
			*version = req.param.data[4];
			*ports = req.param.data[5];
		}
	}
	return rc;
}  /* sw_dev_init */

static void set_sw_req(void *ptr, int cmd, int subcmd, void *data,
	size_t data_size)
{
	struct ksz_request *req = ptr;

	memset(&req->param, 0, sizeof(struct ksz_info_opt));
	req->size = SIZEOF_ksz_request;
	req->size += data_size;
	cmd |= DEV_MOD_BASE << 16;
	req->cmd = cmd;
	req->subcmd = subcmd;
	req->output = 0;
	if (data)
		memcpy(&req->param, data, data_size);
}  /* set_sw_req */

int set_sw_notify(void *fd,
	uint notify)
{
	struct ksz_request_actual req;
	int rc;

	set_sw_req(&req, DEV_CMD_INFO, DEV_INFO_NOTIFY, &notify, sizeof(uint));
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_sw_notify */

static void port_cfg_req(struct ksz_info_opt *opt, int port, int set, int cfg)
{
	opt->num = 1;
	opt->port = (u8) port;
	opt->data.cfg.set |= cfg;
	if (set)
		opt->data.cfg.on_off |= cfg;
}  /* port_cfg_req */

static int get_port_cfg(void *fd,
	int port, int *get, int cfg)
{
	struct ksz_request_actual req;
	struct ksz_info_opt opt;
	size_t data_size;
	int chk;
	int rc;

	memset(&opt, 0, sizeof(struct ksz_info_opt));
	port_cfg_req(&opt, port, 0, cfg);
	data_size = 2 + sizeof(struct ksz_info_cfg);
	set_sw_req(&req, DEV_CMD_GET, DEV_SW_CFG, &opt, data_size);
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		struct ksz_info_opt *out = (struct ksz_info_opt *) &req.param;

		*get = !!(out->data.cfg.on_off & cfg);
	}
	return rc;
}  /* get_port_cfg */

static int set_port_cfg(void *fd,
	int port, int set, int cfg)
{
	struct ksz_request_actual req;
	struct ksz_info_opt opt;
	size_t data_size;
	int rc;

	memset(&opt, 0, sizeof(struct ksz_info_opt));
	port_cfg_req(&opt, port, set, cfg);
	data_size = 2 + sizeof(struct ksz_info_cfg);
	set_sw_req(&req, DEV_CMD_PUT, DEV_SW_CFG, &opt, data_size);
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_port_cfg */

int get_port_learn(void *fd,
	int port, int *get)
{
	return get_port_cfg(fd, port, get,
		SP_LEARN);
}

int set_port_learn(void *fd,
	int port, int set)
{
	return set_port_cfg(fd, port, set,
		SP_LEARN);
}

int get_port_rx(void *fd,
	int port, int *get)
{
	return get_port_cfg(fd, port, get,
		SP_RX);
}

int set_port_rx(void *fd,
	int port, int set)
{
	return set_port_cfg(fd, port, set,
		SP_RX);
}

int get_port_tx(void *fd,
	int port, int *get)
{
	return get_port_cfg(fd, port, get,
		SP_TX);
}

int set_port_tx(void *fd,
	int port, int set)
{
	return set_port_cfg(fd, port, set,
		SP_TX);
}

int get_port_power(void *fd,
	int port, int *get)
{
	return get_port_cfg(fd, port, get,
		SP_PHY_POWER);
}

int set_port_power(void *fd,
	int port, int set)
{
	return set_port_cfg(fd, port, set,
		SP_PHY_POWER);
}

#include <errno.h>

int print_sw_err(int rc)
{
	if (rc < 0) {
		switch (-rc) {
		case EAGAIN:
			break;
		case EINVAL:
			printf("  invalid value\n");
			break;
		default:
			printf("err: %d\n", rc);
		}
	} else if (rc > 0) {
		switch (rc) {
		case DEV_IOC_INVALID_SIZE:
			printf("  invalid size\n");
			break;
		case DEV_IOC_INVALID_CMD:
			printf("  invalid cmd\n");
			break;
		case DEV_IOC_INVALID_LEN:
			printf("  invalid len\n");
			break;
		}
	}
	return rc;
}  /* print_sw_err */

