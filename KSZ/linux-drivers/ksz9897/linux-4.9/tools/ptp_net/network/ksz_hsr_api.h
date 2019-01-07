/**
 * Microchip HSR driver API header
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


#ifndef KSZ_HSR_API_H
#define KSZ_HSR_API_H

#ifndef ETH_ALEN
#define ETH_ALEN				6
#endif


enum {
	DEV_INFO_HSR_LINK = DEV_INFO_LAST,
};

#define HSR_INFO_LINK_LOST			(1 << 0)


#define HSR_GET_NETWORK_STATUS			2
#define HSR_GET_RING_PARTICIPANTS_COUNT		8
#define HSR_GET_RING_PARTICIPANTS_LIST		9
#define HSR_GET_CAPABILITY_FLAGS		12

#define HSR_CAP_DUPLICATE_DISCARD		(1 << 0)
#define HSR_CAP_REDBOX_CAPABLE			(1 << 1)


struct ksz_hsr_node {
	u8 addr[ETH_ALEN];
} __packed;

union hsr_data {
	struct ksz_hsr_node active;
	u32 dword;
	u16 word;
	u8 byte;
} __packed;

#endif
