/**
 * Micrel IBA header
 *
 * Copyright (c) 2015 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2013-2015 Micrel, Inc.
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


#ifndef KSZ_IBA_H
#define KSZ_IBA_H


#define IBA_TAG_TYPE		0x40FE

struct iba_tag {
	u16 type;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 prio:3;
	u8 cfi:1;
	u8 mode:4;
#else
	u8 mode:4;
	u8 cfi:1;
	u8 prio:3;
#endif
	u8 seqid;
} __packed;

#define IBA_FORMAT_KSZ98XX	0x9800

struct iba_format {
	u16 format;
	u16 reserved;
} __packed;

#define IBA_CODE_NORMAL		0x0001
#define IBA_CODE_BURST		0x0002

#define IBA_CMD_READ		1
#define IBA_CMD_WRITE		2
#define IBA_CMD_WAIT_ON_0	4
#define IBA_CMD_WAIT_ON_1	5
#define IBA_CMD_WRITE_0		6
#define IBA_CMD_WRITE_1		7
#define IBA_CMD_S		29

#define IBA_CMD_BYTE_0		(1 << 27)
#define IBA_CMD_BYTE_1		(1 << 26)
#define IBA_CMD_BYTE_2		(1 << 25)
#define IBA_CMD_BYTE_3		(1 << 24)

#define IBA_CMD_32		\
	(IBA_CMD_BYTE_0 | IBA_CMD_BYTE_1 | IBA_CMD_BYTE_2 | IBA_CMD_BYTE_3)
#define IBA_CMD_24		\
	(IBA_CMD_BYTE_0 | IBA_CMD_BYTE_1 | IBA_CMD_BYTE_2)
#define IBA_CMD_24_H		\
	(IBA_CMD_BYTE_1 | IBA_CMD_BYTE_2 | IBA_CMD_BYTE_3)
#define IBA_CMD_16		(IBA_CMD_BYTE_0 | IBA_CMD_BYTE_1)
#define IBA_CMD_16_M		(IBA_CMD_BYTE_1 | IBA_CMD_BYTE_2)
#define IBA_CMD_16_H		(IBA_CMD_BYTE_2 | IBA_CMD_BYTE_3)
#define IBA_CMD_8		(IBA_CMD_BYTE_0)

#define IBA_CMD_ADDR_M		((1 << 24) - 1)

#define IBA_BURST_READ		1
#define IBA_BURST_WRITE		2
#define IBA_BURST_S		30
#define IBA_BURST_CNT_MAX	(1 << 7)
#define IBA_BURST_CNT_M		((1 << 7) - 1)

struct iba_cmd {
	u32 cmd;
	u32 data[1];
} __packed;

struct iba_frame {
	struct iba_tag tag;
	u16 length;
	struct iba_format format;
	u16 code;
	struct iba_cmd cmd;
};

#define IBA_LEN_MAX		288

struct ksz_iba_info {
	int use_iba;
	void *sw_dev;
	u16 tag_type;
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	u8 *buf;
	u8 *packet;
	struct iba_frame *frame;
	struct iba_cmd *cmds;
	struct iba_cmd *regs;
	u8 seqid;
	u8 respid;
	struct completion done;
	wait_queue_head_t queue;
	unsigned long delay_ticks;
	struct net_device *dev;
	struct mutex lock;
	int cnt;
	u32 cfg;

	/* Used for putting in commands. */
	u32 *data;
	void *fptr;
	int index;
	int len;
};

#endif
