/**
 * ksz_ptp.h - Micrel PTP common header
 *
 * Copyright (c) 2010-2014 Micrel, Inc.
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

#ifndef KSZ_PTP_H
#define KSZ_PTP_H


struct ptp_time {
	int sec;
	int nsec;
};

struct ptp_utime {
	u32 sec;
	u32 nsec;
};

struct ptp_ts {
	struct ptp_utime r;
	struct ptp_utime t;
	u32 timestamp;
};

#ifndef _ptp_second
struct ptp_second {
	u16 hi;
	u32 lo;
} __packed;
#endif

struct ptp_timestamp {
	struct ptp_second sec;
	u32 nsec;
} __packed;

#define SCALED_NANOSEC_S		16
#define SCALED_NANOSEC_MULT		(1 << SCALED_NANOSEC_S)

struct ptp_scaled_ns {
	int hi;
	s64 lo;
} __packed;

struct ptp_correction {
	int scaled_nsec_hi;
	int scaled_nsec_lo;
} __packed;

struct ptp_clock_identity {
	u8 addr[8];
};

struct ptp_port_identity {
	struct ptp_clock_identity clockIdentity;
	u16 port;
} __packed;

struct ptp_clock_quality {
	u8 clockClass;
	u8 clockAccuracy;
	u16 offsetScaledLogVariance;
} __packed;

struct ptp_port_address {
	u16 networkProtocol;
	u16 addressLength;
	u8 addressField[1];
} __packed;

#ifndef _ptp_text
struct ptp_text {
	u8 lengthField;
	u8 textField[1];
} __packed;
#endif

#define SYNC_MSG			0x0
#define DELAY_REQ_MSG			0x1
#define PDELAY_REQ_MSG			0x2
#define PDELAY_RESP_MSG			0x3
#define FOLLOW_UP_MSG			0x8
#define DELAY_RESP_MSG			0x9
#define PDELAY_RESP_FOLLOW_UP_MSG	0xA
#define ANNOUNCE_MSG			0xB
#define SIGNALING_MSG			0xC
#define MANAGEMENT_MSG			0xD

struct ptp_msg_hdr {
#ifdef __BIG_ENDIAN_BITFIELD
	u8 transportSpecific:4;
	u8 messageType:4;
	u8 reserved1:4;
	u8 versionPTP:4;
#else
	u8 messageType:4;
	u8 transportSpecific:4;
	u8 versionPTP:4;
	u8 reserved1:4;
#endif
	u16 messageLength;
	u8 domainNumber;
	u8 reserved2;
	union {
		struct {
#ifdef __BIG_ENDIAN_BITFIELD
			u8 reservedFlag7:1;
			u8 profileSpecific1:1;
			u8 profileSpecific2:1;
			u8 reservedFlag4:1;
			u8 reservedFlag3:1;
			u8 unicastFlag:1;
			u8 twoStepFlag:1;
			u8 alternateMasterFlag:1;
			u8 reservedFlag6:1;
			u8 reservedFlag5:1;
			u8 frequencyTraceable:1;
			u8 timeTraceable:1;
			u8 ptpTimescale:1;
			u8 utcOffsetValid:1;
			u8 leap59:1;
			u8 leap61:1;
#else
			u8 alternateMasterFlag:1;
			u8 twoStepFlag:1;
			u8 unicastFlag:1;
			u8 reservedFlag3:1;
			u8 reservedFlag4:1;
			u8 profileSpecific1:1;
			u8 profileSpecific2:1;
			u8 reservedFlag7:1;
			u8 leap61:1;
			u8 leap59:1;
			u8 utcOffsetValid:1;
			u8 ptpTimescale:1;
			u8 timeTraceable:1;
			u8 frequencyTraceable:1;
			u8 reservedFlag5:1;
			u8 reservedFlag6:1;
#endif
		} __packed flag;
		u16 data;
	} __packed flagField;
	struct ptp_correction correctionField;
	u32 reserved3;
	struct ptp_port_identity sourcePortIdentity;
	u16 sequenceId;
	u8 controlField;
	char logMessageInterval;
} __packed;

struct ptp_msg_sync {
	struct ptp_timestamp originTimestamp;
} __packed;

struct ptp_msg_follow_up {
	struct ptp_timestamp preciseOriginTimestamp;
} __packed;

struct ptp_msg_delay_resp {
	struct ptp_timestamp receiveTimestamp;
	struct ptp_port_identity requestingPortIdentity;
} __packed;

struct ptp_msg_pdelay_req {
	struct ptp_timestamp originTimestamp;
	struct ptp_port_identity reserved;
} __packed;

struct ptp_msg_pdelay_resp {
	struct ptp_timestamp requestReceiptTimestamp;
	struct ptp_port_identity requestingPortIdentity;
} __packed;

struct ptp_msg_pdelay_resp_follow_up {
	struct ptp_timestamp responseOriginTimestamp;
	struct ptp_port_identity requestingPortIdentity;
} __packed;

#define TLV_MANAGEMENT					0x0001
#define TLV_MANAGEMENT_ERROR_STATUS			0x0002
#define TLV_ORGANIZATION_EXTENSION			0x0003
#define TLV_REQUEST_UNICAST_TRANSMISSION		0x0004
#define TLV_GRANT_UNICAST_TRANSMISSION			0x0005
#define TLV_CANCEL_UNICAST_TRANSMISSION			0x0006
#define TLV_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION	0x0007
#define TLV_PATH_TRACE					0x0008
#define TLV_ALTERNATE_TIME_OFFSET_INDICATOR		0x0009

struct ptp_tlv {
	u16 tlvType;
	u16 lengthField;
} __packed;

struct ptp_organization_ext_tlv {
	struct ptp_tlv tlv;
	u8 organizationId[3];
	u8 organizationSubType[3];
	u8 dataField[1];
} __packed;

struct IEEE_C37_238_data {
	u16 grandmasterID;
	u32 grandmasterTimeInaccuracy;
	u32 networkTimeInaccuracy;
	u16 reserved;
} __packed;

struct IEEE_802_1AS_data_1 {
	int cumulativeScaledRateOffset;
	u16 gmTimeBaseIndicator;
	struct ptp_scaled_ns lastGmPhaseChange;
	int scaledLastGmFreqChange;
} __packed;

struct IEEE_802_1AS_data_2 {
	char linkDelayInterval;
	char timeSyncInterval;
	char announceInterval;
	u8 flags;
	u16 reserved;
} __packed;

struct ptp_request_unicast_tlv {
	struct ptp_tlv tlv;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 messageType:4;
	u8 reserved1:4;
#else
	u8 reserved1:4;
	u8 messageType:4;
#endif
	char logInterMessagePeriod;
	u32 durationField;
} __packed;

struct ptp_grant_unicast_tlv {
	struct ptp_tlv tlv;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 messageType:4;
	u8 reserved1:4;
#else
	u8 reserved1:4;
	u8 messageType:4;
#endif
	char logInterMessagePeriod;
	u32 durationField;
	u8 reserved2;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 reserved3:7;
	u8 renewal:1;
#else
	u8 renewal:1;
	u8 reserved3:7;
#endif
} __packed;

struct ptp_cancel_unicast_tlv {
	struct ptp_tlv tlv;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 messageType:4;
	u8 reserved1:4;
#else
	u8 reserved1:4;
	u8 messageType:4;
#endif
	u8 reserved2;
} __packed;

struct ptp_alternate_time_offset_tlv {
	struct ptp_tlv tlv;
	u8 keyField;
	int currentOffset;
	int jumpSeconds;
	struct ptp_second timeOfNextJump;
	struct ptp_text displayName;
} __packed;

struct ptp_msg_signaling_base {
	struct ptp_port_identity targetPortIdentity;
} __packed;

struct ptp_msg_signaling {
	struct ptp_msg_signaling_base b;
	union {
		struct ptp_request_unicast_tlv request[1];
		struct ptp_grant_unicast_tlv grant[1];
		struct ptp_cancel_unicast_tlv cancel[1];
	} tlv;
} __packed;

#define M_NULL_MANAGEMENT				0x0000
#define M_CLOCK_DESCRIPTION				0x0001
#define M_DEFAULT_DATA_SET				0x2000
#define M_CURRENT_DATA_SET				0x2001
#define M_PARENT_DATA_SET				0x2002
#define M_PORT_DATA_SET					0x2004
#define M_PRIORITY1					0x2005
#define M_PRIORITY2					0x2006
#define M_DOMAIN					0x2007
#define M_SLAVE_ONLY					0x2008
#define M_VERSION_NUMBER				0x200C
#define M_ENABLE_PORT					0x200D
#define M_DISABLE_PORT					0x200E
#define M_TIME						0x200F
#define M_UNICAST_NEGOTIATION_ENABLE			0x2014
#define M_PATH_TRACE_LIST				0x2015
#define M_PATH_TRACE_ENABLE				0x2016
#define M_GRANDMASTER_CLUSTER_TABLE			0x2017
#define M_UNICAST_MASTER_TABLE				0x2018
#define M_UNICAST_MASTER_MAX_TABLE_SIZE			0x2019
#define M_ACCEPTABLE_MASTER_TABLE			0x201A
#define M_ACCEPTABLE_MASTER_TABLE_ENABLED		0x201B
#define M_ACCEPTABLE_MASTER_MAX_TABLE_SIZE		0x201C
#define M_ALTERNATE_MASTER				0x201D
#define M_ALTERNATE_TIME_OFFSET_ENABLE			0x201E
#define M_ALTERNATE_TIME_OFFSET_NAME			0x201F
#define M_ALTERNATE_TIME_OFFSET_MAX_KEY			0x2020
#define M_ALTERNATE_TIME_OFFSET_PROPERTIES		0x2021

struct ptp_management_unicast_negotiation {
#ifdef __BIG_ENDIAN_BITFIELD
	u8 reserved1:7;
	u8 enable:1;
#else
	u8 enable:1;
	u8 reserved1:7;
#endif
	u8 reserved2;
} __packed;

struct ptp_management_unicast_master_table {
	u8 logQueryInterval;
	u16 tableSize;
	struct ptp_port_address unicastMasterTable[1];
} __packed;

struct ptp_management_unicast_master_max_table_size {
	u16 maxTableSize;
} __packed;

struct ptp_management_alternate_time_offset {
	u8 keyField;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 reserved1:7;
	u8 enable:1;
#else
	u8 enable:1;
	u8 reserved1:7;
#endif
} __packed;

struct ptp_management_alternate_time_offset_name {
	u8 keyField;
	struct ptp_text displayName;
} __packed;

struct ptp_management_alternate_time_offset_max_key {
	u8 keyField;
	u8 reserved;
} __packed;

struct ptp_management_alternate_time_offset_properties {
	u8 keyField;
	int currentOffset;
	int jumpSeconds;
	struct ptp_second timeOfNextJump;
	u8 reserved;
} __packed;

struct ptp_management_tlv {
	struct ptp_tlv tlv;
	u16 managementId;
	u8 dataField[1];
} __packed;

#define M_RESPONSE_TOO_BIG		0x0001
#define M_NO_SUCH_ID			0x0002
#define M_WRONG_LENGTH			0x0003
#define M_WRONG_VALUE			0x0004
#define M_NOT_SETABLE			0x0005
#define M_NOT_SUPPORTED			0x0006
#define M_GENERAL_ERROR			0xFFFE

struct ptp_management_error_tlv {
	struct ptp_tlv tlv;
	u16 managementErrorId;
	u16 managementId;
	u32 reserved1;
	u8 data[1];
} __packed;

#define MANAGEMENT_GET			0
#define MANAGEMENT_SET			1
#define MANAGEMENT_RESPONSE		2
#define MANAGEMENT_COMMAND		3
#define MANAGEMENT_ACKNOWLEDGE		4

struct ptp_msg_management_base {
	struct ptp_port_identity targetPortIdentity;
	u8 startingBoundaryHops;
	u8 boundaryHops;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 reserved1:4;
	u8 actionField:4;
#else
	u8 actionField:4;
	u8 reserved1:4;
#endif
	u8 reserved2;
} __packed;

struct ptp_msg_management {
	struct ptp_msg_management_base b;
	union {
		struct ptp_management_tlv normal[1];
		struct ptp_management_error_tlv error[1];
	} tlv;
} __packed;

struct ptp_msg_announce {
	struct ptp_timestamp originTimestamp;
	s16 currentUtcOffset;
	u8 reserved;
	u8 grandmasterPriority1;
	struct ptp_clock_quality grandmasterClockQuality;
	u8 grandmasterPriority2;
	struct ptp_clock_identity grandmasterIdentity;
	u16 stepsRemoved;
	u8 timeSource;
} __packed;

union ptp_msg_data {
	struct ptp_msg_sync sync;
	struct ptp_msg_follow_up follow_up;
	struct ptp_msg_delay_resp delay_resp;
	struct ptp_msg_pdelay_req pdelay_req;
	struct ptp_msg_pdelay_resp pdelay_resp;
	struct ptp_msg_pdelay_resp_follow_up pdelay_resp_follow_up;
	struct ptp_msg_signaling signaling;
	struct ptp_msg_management management;
	struct ptp_msg_announce announce;
	u8 data[8];
} __packed;

struct ptp_msg {
	struct ptp_msg_hdr hdr;
	union ptp_msg_data data;
} __packed;


struct ptp_id {
	u16 seq;
	struct ptp_clock_identity clock;
	u8 mac[2];
	u8 msg;
	u8 port;
};

struct ptp_cfg_options {
	u8 master:1;
	u8 two_step:1;
	u8 p2p:1;
	u8 as:1;
	u8 domain_check:1;
	u8 udp_csum:1;
	u8 unicast:1;
	u8 alternate:1;
	u8 delay_assoc:1;
	u8 pdelay_assoc:1;
	u8 sync_assoc:1;
	u8 drop_sync:1;
	u8 priority:1;
	u8 reserved:3;
	u8 master_set:1;
	u8 two_step_set:1;
	u8 p2p_set:1;
	u8 as_set:1;
	u8 domain_check_set:1;
	u8 udp_csum_set:1;
	u8 unicast_set:1;
	u8 alternate_set:1;
	u8 delay_assoc_set:1;
	u8 pdelay_assoc_set:1;
	u8 sync_assoc_set:1;
	u8 drop_sync_set:1;
	u8 priority_set:1;
	u8 reserved_set:2;
	u8 domain_set:1;
	u8 domain;
	u8 reserved3;
	u32 access_delay;
} __packed;

#define PTP_CMD_RESP			0x01
#define PTP_CMD_GET_MSG			0x00
#define PTP_CMD_GET_OUTPUT		0xE0
#define PTP_CMD_GET_EVENT		0xF0

#define PTP_CMD_INTR_OPER		0x01
#define PTP_CMD_SILENT_OPER		0x02
#define PTP_CMD_ON_TIME			0x04
#define PTP_CMD_REL_TIME		0x08
#define PTP_CMD_CLK_OPT			0x10
#define PTP_CMD_CASCADE_RESET_OPER	0x40
#define PTP_CMD_CANCEL_OPER		0x80

struct ptp_tsi_info {
	u8 cmd;
	u8 unit;
	u8 event;
	u8 num;
	u32 edge;
	struct ptp_utime t[0];
} __packed;

#define SIZEOF_ptp_tsi_info		sizeof(struct ptp_tsi_info)

struct ptp_tsi_options {
	u8 tsi;
	u8 gpi;
	u8 event;
	u8 flags;
	u8 total;
	u8 reserved[3];
	u32 timeout;
} __packed;

struct ptp_tso_options {
	u8 tso;
	u8 gpo;
	u8 event;
	u8 flags;
	u8 total;
	u8 reserved[1];
	u16 cnt;
	u32 pulse;
	u32 cycle;
	u32 sec;
	u32 nsec;
	u32 iterate;
} __packed;

struct ptp_clk_options {
	u32 sec;
	u32 nsec;
	int drift;
	u32 interval;
} __packed;

struct ptp_ts_options {
	u32 timestamp;
	u32 sec;
	u32 nsec;
	u8 msg;
	u8 port;
	u16 seqid;
	u8 mac[2];
} __packed;

struct ptp_delay_values {
	u16 rx_latency;
	u16 tx_latency;
	short asym_delay;
	u16 reserved;
} __packed;

struct ptp_msg_options {
	struct ptp_port_identity id;
	u16 seqid;
	u8 domain;
	u8 msg;
	u8 reserved[2];
	u32 port;
	struct ptp_ts ts;
} __packed;

struct ptp_udp_msg {
	u16 len;
	u8 data[0];
} __packed;

enum {
	DEV_IOC_UNIT_UNAVAILABLE = DEV_IOC_LAST,
	DEV_IOC_UNIT_USED,
	DEV_IOC_UNIT_ERROR,
};

enum {
	DEV_INFO_MSG = DEV_INFO_LAST,
	DEV_INFO_RESET,
};

enum {
	DEV_PTP_CFG,
	DEV_PTP_TEVT,
	DEV_PTP_TOUT,
	DEV_PTP_CLK,
	DEV_PTP_CASCADE,
	DEV_PTP_DELAY,
	DEV_PTP_REG,
	DEV_PTP_IDENTITY,
	DEV_PTP_PEER_DELAY,
	DEV_PTP_UTC_OFFSET,
	DEV_PTP_TIMESTAMP,
	DEV_PTP_MSG,
};

#ifndef TSM_CMD_CLOCK_SET
#define TSM_CMD_RESP			0x04
#define TSM_CMD_GET_TIME_RESP		0x08

#define TSM_CMD_CLOCK_SET		0x10
#define TSM_CMD_CLOCK_CORRECT		0x20
#define TSM_CMD_DB_SET			0x30
#define TSM_CMD_DB_GET			0x40
#define TSM_CMD_STAT_CLEAR		0x50
#define TSM_CMD_STAT_GET		0x60
#define TSM_CMD_CNF_SET			0x70
#define TSM_CMD_CNF_GET			0x80
#define TSM_CMD_GPIO_SET		0x90
#define TSM_CMD_GPIO_GET		0xA0
#define	TSM_CMD_SET_SECONDS		0xB0
/* todo */
#define TSM_CMD_GET_GPS_TS		0xE0

/* used for accessing reserved DB entry for a given port for SYNC or DELAY_REQ
 * packets on egress
 */
#define TSM_CMD_DB_GET_RESRV1		0xB0
/* used for accessing reserved DB entry for a given port for P2P PATH_DEL_REQ
 * packets on egress
 */
#define TSM_CMD_DB_GET_RESRV2		0xC0
/* used for getting time from TSM, no look-up of a DB entry with an ingress or
 * egress time stamp
 */
#define TSM_CMD_DB_GET_TIME		0xD0
#define TSM_CMD_DB_SET_TIME		0xF0
#endif

struct tsm_cfg {
	u8 cmd;
	u8 port;
	u8 enable;
	u8 gmp;
	u32 ingress_delay;
	u16 egress_delay;
} __packed;

struct tsm_clock_set {
	u8 cmd;
	u32 timestamp;
	u32 nsec;
	u32 sec;
	u8 reserved[5];
} __packed;

struct tsm_clock_correct {
	u8 cmd;
	u8 add;
	u32 sec;
	u32 nsec;
	u32 drift;
	u32 offset;
} __packed;

struct tsm_db {
	u8 cmd;
	u8 index;
	u16 seqid;
	u8 mac[2];
	u32 cur_sec;
	u32 cur_nsec;
	u32 timestamp;
} __packed;

struct tsm_get_gps {
	u8 cmd;
	u8 reserved[7];
	u16 seqid;
	u32 sec;
	u32 nsec;
} __packed;

struct tsm_get_time {
	u8 cmd;
	u16 seqid;
	u8 msg;
	u32 sec;
	u32 nsec;
} __packed;

#define PTP_CAN_RX_TIMESTAMP		(1 << 0)
#define PTP_KNOW_ABOUT_LATENCY		(1 << 1)
#define PTP_HAVE_MULT_DEVICES		(1 << 2)
#define PTP_HAVE_MULT_PORTS		(1 << 3)
#define PTP_KNOW_ABOUT_MULT_PORTS	(1 << 4)

#ifdef USE_DEV_IOCTL
#define DEV_IO_PTP			0

#define DEV_IOC_PTP			\
	_IOW(DEV_IOC_MAGIC, DEV_IO_PTP, struct ksz_request)

int ptp_ioctl(void *fd, void *req)
{
	int *dev = (int *) fd;

	return ioctl(*dev, DEV_IOC_PTP, req);
}
#endif

#ifdef USE_NET_IOCTL
struct dev_info {
	int sock;
	char name[20];
};

int ptp_ioctl(void *fd, void *req)
{
	struct dev_info *info = (struct dev_info *) fd;
	struct ifreq dev;

	memset(&dev, 0, sizeof(struct ifreq));
	strncpy(dev.ifr_name, info->name, sizeof(dev.ifr_name));
	dev.ifr_data = (char *) req;
	return ioctl(info->sock, SIOCDEVPRIVATE + 15, &dev);
}
#endif

#endif
