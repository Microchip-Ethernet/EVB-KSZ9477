/**
 * Micrel MRP driver API code
 *
 * Copyright (c) 2014 Micrel, Inc.
 *	Tristram Ha <Tristram.Ha@micrel.com>
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

#ifndef KSZ_MRP_API_H

/* Data types used in the MRP header file. */

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
#include "ksz_mrp_api.h"
#endif

#ifdef USE_DEV_IOCTL
#define DEV_IO_MRP			0

#define DEV_IOC_MRP			\
	_IOW(DEV_IOC_MAGIC, DEV_IO_MRP, struct ksz_request)

int mrp_ioctl(void *fd, void *req)
{
	int *dev = fd;

	return ioctl(*dev, DEV_IOC_MRP, req);
}
#endif

#ifdef USE_NET_IOCTL
struct dev_info {
	int sock;
	char name[20];
};

int mrp_ioctl(void *fd, void *req)
{
	struct dev_info *info = fd;
	struct ifreq dev;

	memset(&dev, 0, sizeof(struct ifreq));
	strncpy(dev.ifr_name, info->name, sizeof(dev.ifr_name));
	dev.ifr_data = (char *) req;
	return ioctl(info->sock, SIOCDEVPRIVATE + 14, &dev);
}
#endif


/* Used to indicate which APIs are supported. */
static int mrp_version;

/* Used to indicate how many ports are in the switch. */
static int mrp_ports;


static void mrp_exit_req(void *ptr)
{
	struct ksz_request *req = ptr;

	req->size = SIZEOF_ksz_request;
	req->cmd = DEV_CMD_INFO;
	req->subcmd = DEV_INFO_EXIT;
	req->output = 0;
}  /* mrp_exit_req */

static void mrp_init_req(void *ptr,
	int capability)
{
	struct ksz_request *req = ptr;

	req->size = SIZEOF_ksz_request + 8;
	req->cmd = DEV_CMD_INFO;
	req->subcmd = DEV_INFO_INIT;
	req->output = capability;
	req->param.data[0] = '8';
	req->param.data[1] = '0';
	req->param.data[2] = '2';
	req->param.data[3] = '.';
	req->param.data[4] = '1';
	req->param.data[5] = 'Q';
}  /* mrp_init_req */

static void set_mrp_req(void *ptr,
	int cmd, int type, int action, int port, void *mrp, size_t mrp_size)
{
	struct ksz_request *req = ptr;
	struct mrp_cfg_options *param = (struct mrp_cfg_options *)
		&req->param;

	req->size = SIZEOF_ksz_request;
	req->size += mrp_size;
	req->size += 4;
	req->cmd = cmd;
	req->subcmd = DEV_MRP_ATTRIBUTE;
	req->output = 0;
	param->action = action;
	param->type = type;
	param->port = port;
	param->reserved = 0;
	if (mrp)
		memcpy(&param->data, mrp, mrp_size);
}  /* set_mrp_req */


int mrp_dev_exit(void *fd)
{
	struct ksz_request_actual req;
	int rc;

	mrp_exit_req(&req);
	rc = mrp_ioctl(fd, &req);
	return rc;
}

int mrp_dev_init(void *fd,
	int capability, int *version, int *ports)
{
	struct ksz_request_actual req;
	int rc;

	mrp_init_req(&req, capability);
	rc = mrp_ioctl(fd, &req);
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
}

int set_mac_lv(void *fd,
	int port, struct MRP_mac *mac)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_MAC, MRP_ACTION_LV, port,
		mac, sizeof(struct MRP_mac));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_mac_lv */

int set_mac_rx(void *fd,
	int port, struct MRP_mac *mac)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_MAC, MRP_ACTION_RX, port,
		mac, sizeof(struct MRP_mac));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_mac_rx */

int set_mac_on(void *fd,
	int port, struct MRP_mac *mac)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_MAC, MRP_ACTION_ON, port,
		mac, sizeof(struct MRP_mac));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_mac_on */

int set_mac_off(void *fd,
	int port, struct MRP_mac *mac)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_MAC, MRP_ACTION_OFF, port,
		mac, sizeof(struct MRP_mac));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_mac_off */

int set_vlan_on(void *fd,
	int port, struct MRP_vlan *vlan)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_VLAN, MRP_ACTION_ON, port,
		vlan, sizeof(struct MRP_vlan));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_vlan_on */

int set_vlan_off(void *fd,
	int port, struct MRP_vlan *vlan)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_VLAN, MRP_ACTION_OFF, port,
		vlan, sizeof(struct MRP_vlan));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_vlan_off */

int set_vlan_lv(void *fd,
	int port, struct MRP_vlan *vlan)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_VLAN, MRP_ACTION_LV, port,
		vlan, sizeof(struct MRP_vlan));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_vlan_lv */

int set_vlan_rx(void *fd,
	int port, struct MRP_vlan *vlan)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_VLAN, MRP_ACTION_RX, port,
		vlan, sizeof(struct MRP_vlan));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_vlan_rx */

int set_domain_lv(void *fd,
	int port, struct SRP_domain_class *domain)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_DOMAIN, MRP_ACTION_LV, port,
		domain, sizeof(struct SRP_domain_class));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_domain_lv */

int set_domain_rx(void *fd,
	int port, struct SRP_domain_class *domain)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_DOMAIN, MRP_ACTION_RX, port,
		domain, sizeof(struct SRP_domain_class));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_domain_rx */

int set_listener_lv(void *fd,
	int port, struct SRP_listener *listener)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_LISTENER, MRP_ACTION_LV, port,
		listener, sizeof(struct SRP_listener));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_listener_lv */

int set_listener_rx(void *fd,
	int port, struct SRP_listener *listener)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_LISTENER, MRP_ACTION_RX, port,
		listener, sizeof(struct SRP_listener));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_listener_rx */

int get_attribute(void *fd,
	int *port, int *type, int *action, void *buf, size_t size)
{
	struct ksz_request_actual req;
	int rc;
	size_t req_size;

	set_mrp_req(&req, DEV_CMD_GET, MRP_TYPE_UNKNOWN, MRP_ACTION_TX, 0,
		NULL, sizeof(struct SRP_talker));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	*type = MRP_TYPE_UNKNOWN;
	if (!rc || DEV_IOC_MRP_REPORT == rc) {
		struct mrp_cfg_options *param = (struct mrp_cfg_options *)
			&req.param;

		switch (param->type) {
		case MRP_TYPE_MAC:
			req_size = sizeof(struct MRP_mac);
			break;
		case MRP_TYPE_VLAN:
			req_size = sizeof(struct MRP_vlan);
			break;
		case MRP_TYPE_DOMAIN:
			req_size = sizeof(struct SRP_domain_class);
			break;
		case MRP_TYPE_LISTENER:
			req_size = sizeof(struct SRP_listener);
			break;
		case MRP_TYPE_TALKER:
		default:
			req_size = sizeof(struct SRP_talker);
			break;
		}
		if (size >= req_size) {
			*type = param->type;
			*action = param->action;
			*port = param->port;
			memcpy(buf, &param->data, req_size);
		} else
			rc = DEV_IOC_INVALID_SIZE;
	}
	return rc;
}  /* get_attribute */

int set_talker_lv(void *fd,
	int port, struct SRP_talker *talker)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_TALKER, MRP_ACTION_LV, port,
		talker, sizeof(struct SRP_talker));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_talker_lv */

int set_talker_rx(void *fd,
	int port, struct SRP_talker *talker)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_TALKER, MRP_ACTION_RX, port,
		talker, sizeof(struct SRP_talker));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_talker_rx */

int set_talker_on(void *fd,
	int port, struct SRP_talker *talker)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_TALKER, MRP_ACTION_ON, port,
		talker, sizeof(struct SRP_talker));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_talker_on */

int set_talker_off(void *fd,
	int port, struct SRP_talker *talker)
{
	struct ksz_request_actual req;
	int rc;

	set_mrp_req(&req, DEV_CMD_PUT, MRP_TYPE_TALKER, MRP_ACTION_OFF, port,
		talker, sizeof(struct SRP_talker));
	rc = mrp_ioctl(fd, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* set_talker_off */

char *get_failure_code(int code)
{
	char *error;

	switch (code) {
	case RFC_NO_ERROR:
		error = "no error";
		break;
	case RFC_NO_BANDWIDTH:
		error = "no bandwidth";
		break;
	case RFC_NO_RESOURCES:
		error = "no resources";
		break;
	case RFC_NO_BANDWIDTH_FOR_TRAFFIC_CLASS:
		error = "no bandwidth for traffic class";
		break;
	case RFC_STREAM_ID_USED:
		error = "stream id used";
		break;
	case RFC_DEST_ADDR_USED:
		error = "dest addr used";
		break;
	case RFC_PREEMPTED_BY_RANK:
		error = "preempted by rank";
		break;
	case RFC_LATENCY_CHANGED:
		error = "latency changed";
		break;
	case RFC_PORT_IS_NOT_AVB:
		error = "port is not avb";
		break;
	case RFC_USE_DIFF_DEST_ADDR:
		error = "use diff dest addr";
		break;
	case RFC_OUT_OF_MSRP_RESOURCE:
		error = "MSRP out of resource";
		break;
	case RFC_OUT_OF_MMRP_RESOURCE:
		error = "MMRP out of resource";
		break;
	case RFC_CANNOT_STORE_DEST_ADDR:
		error = "cannot store dest addr";
		break;
	case RFC_PRIORITY_IS_NOT_SR_CLASS:
		error = "priority is not sr class";
		break;
	case RFC_MAXFRAMESIZE_TOO_LARGE:
		error = "maxframesize too large";
		break;
	case RFC_MAXFANINPORTS_LIMIT_REACHED:
		error = "maxfaninports limit reached";
		break;
	case RFC_FIRSTVALUE_CHANGED:
		error = "first value changed";
		break;
	case RFC_VLAN_BLOCKED:
		error = "vlan blocked";
		break;
	case RFC_VLAN_TAGGING_DISABLED:
		error = "vlan tagging disabled";
		break;
	case RFC_SR_CLASS_PRIORITY_MISMATCHED:
		error = "sr class priority mismatched";
		break;
	default:
		error = "unknown";
	}
	return error;
}  /* get_failure_code */

#include <errno.h>

int print_mrp_err(int rc)
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
		case DEV_IOC_MRP_REPORT:
			printf("->");
			break;
		}
	}
	return rc;
}  /* print_mrp_err */

