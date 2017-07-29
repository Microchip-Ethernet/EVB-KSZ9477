

#ifndef KSZ_REQ_H
#define KSZ_REQ_H

enum {
	DEV_IOC_OK,
	DEV_IOC_INVALID_SIZE,
	DEV_IOC_INVALID_CMD,
	DEV_IOC_INVALID_LEN,
	DEV_IOC_LAST
#if 0
	DEV_IOC_UNIT_UNAVAILABLE,
	DEV_IOC_UNIT_USED,
	DEV_IOC_UNIT_ERROR,
#endif
};

enum {
	DEV_CMD_INFO,
	DEV_CMD_GET,
	DEV_CMD_PUT,
	DEV_CMD_LAST
};

enum {
	DEV_INFO_INIT,
	DEV_INFO_EXIT,
	DEV_INFO_QUIT,
	DEV_INFO_LAST
};

struct ksz_request {
	int size;
	int cmd;
	int subcmd;
	int output;
	int result;
	union {
		u8 data[1];
		int num[1];
	} param;
};

#define SIZEOF_ksz_request	(sizeof(struct ksz_request) - sizeof(int))

/* Not used in the driver. */

#ifndef MAX_REQUEST_SIZE
#define MAX_REQUEST_SIZE	20
#endif

struct ksz_request_actual {
	int size;
	int cmd;
	int subcmd;
	int output;
	int result;
	union {
		u8 data[MAX_REQUEST_SIZE];
		int num[MAX_REQUEST_SIZE / sizeof(int)];
	} param;
};

#define DEV_IOC_MAGIC			0x92

#define DEV_IOC_MAX			1

#endif
