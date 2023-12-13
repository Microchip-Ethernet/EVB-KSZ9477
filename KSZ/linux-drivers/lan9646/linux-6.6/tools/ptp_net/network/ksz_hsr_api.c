/**
 * Microchip HSR driver API code
 *
 * Copyright (c) 2017 Microchip Technology Inc.
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

#include "ksz_hsr_api.h"


/* Used to indicate which APIs are supported. */
static int hsr_version;

/* Used to indicate how many ports are in the switch. */
static int hsr_ports;


static void hsr_exit_req(void *ptr)
{
	struct ksz_request *req = ptr;

	req->size = SIZEOF_ksz_request;
	req->cmd = DEV_CMD_INFO;
	req->cmd |= DEV_MOD_HSR << 16;
	req->subcmd = DEV_INFO_EXIT;
	req->output = 0;
}  /* hsr_exit_req */

static void hsr_init_req(void *ptr,
	int capability)
{
	struct ksz_request *req = ptr;

	req->size = SIZEOF_ksz_request + 8;
	req->cmd = DEV_CMD_INFO;
	req->cmd |= DEV_MOD_HSR << 16;
	req->subcmd = DEV_INFO_INIT;
	req->output = capability;
	req->param.data[0] = 'H';
	req->param.data[1] = 'S';
	req->param.data[2] = 'R';
	req->param.data[3] = 'R';
	req->param.data[4] = 'E';
	req->param.data[5] = 'D';
}  /* hsr_init_req */

int hsr_dev_exit(void *fd)
{
	struct ksz_request_actual req;
	int rc;

	hsr_exit_req(&req);
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* hsr_dev_exit */

int hsr_dev_init(void *fd,
	int capability, int *version, int *ports)
{
	struct ksz_request_actual req;
	int rc;

	hsr_init_req(&req, capability);
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
}  /* hsr_dev_init */

static void set_hsr_req(void *ptr, int cmd, int subcmd,
	void *hsr, size_t hsr_size)
{
	struct ksz_request *req = ptr;

	req->size = SIZEOF_ksz_request;
	req->size += hsr_size;
	cmd |= DEV_MOD_HSR << 16;
	req->cmd = cmd;
	req->subcmd = subcmd;
	req->output = 0;
	if (hsr)
		memcpy(&req->param, hsr, hsr_size);
}  /* set_hsr_req */

int set_hsr_notify(void *fd,
	uint notify)
{
	struct ksz_request_actual req;
	int rc;

	hsr_exit_req(&req);
	req.size += sizeof(uint);
	req.subcmd = DEV_INFO_NOTIFY;
	memcpy(&req.param, &notify, sizeof(uint));
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_hsr_notify */

static int get_hsr_network(void *fd,
	u8 *network)
{
	struct ksz_request_actual req;
	int rc;

	set_hsr_req(&req, DEV_CMD_GET,
		HSR_GET_NETWORK_STATUS,
		NULL, sizeof(u8));
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union hsr_data *data = (union hsr_data *) &req.param;

		*network = data->byte;
	}
	return rc;
}  /* get_hsr_network */

static int get_hsr_ring_part_cnt(void *fd,
	u16 *cnt)
{
	struct ksz_request_actual req;
	int rc;

	set_hsr_req(&req, DEV_CMD_GET,
		HSR_GET_RING_PARTICIPANTS_COUNT,
		NULL, sizeof(u16));
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union hsr_data *data = (union hsr_data *) &req.param;

		*cnt = data->word;
	}
	return rc;
}  /* get_hsr_ring_part_cnt */

static int get_hsr_ring_part_list(void *fd,
	struct ksz_hsr_node *node, u16 *size, u8 *err)
{
	struct ksz_request_actual req;
	int rc;

	set_hsr_req(&req, DEV_CMD_GET,
		HSR_GET_RING_PARTICIPANTS_LIST,
		NULL, *size);
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		*err = (u8) req.output;
		*size = req.size - SIZEOF_ksz_request;
		memcpy(node, &req.param, *size);
	}
	return rc;
}  /* get_hsr_ring_part_list */

static int get_hsr_cap(void *fd,
	u32 *flags)
{
	struct ksz_request_actual req;
	int rc;

	set_hsr_req(&req, DEV_CMD_GET,
		HSR_GET_CAPABILITY_FLAGS,
		NULL, sizeof(u32));
	rc = sw_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union hsr_data *data = (union hsr_data *) &req.param;

		*flags = data->dword;
	}
	return rc;
}  /* get_hsr_cap */

