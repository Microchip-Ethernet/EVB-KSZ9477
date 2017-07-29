/**
 * Micrel PTP common header
 *
 * Copyright (c) 2015 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2010-2015 Micrel, Inc.
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

#ifndef __KERNEL__
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef long long s64;
typedef unsigned long long u64;
#endif

struct ksz_ptp_time {
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

struct ptp_second {
	u16 hi;
	u32 lo;
} __packed;

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

struct ptp_text {
	u8 lengthField;
	u8 textField[1];
} __packed;

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

#ifdef __KERNEL__
#define NANOSEC_IN_SEC			1000000000

/* Host port can be any one of the ports. */
#define MAX_PTP_PORT			(SWITCH_PORT_NUM + 1)

#define MAX_TSM_UDP_LEN			100
#define MAX_TSM_UDP_CNT			(1 << 6)

struct ptp_ltime {
	s64 sec;
	s64 nsec;
};

struct ptp_hw_ts {
	struct ptp_id id;
	struct ptp_ts ts;
	int sim_2step;
	int update;
	int sending;
};

struct ptp_dev_info {
	void *ptp;
	unsigned int minor;
	u8 *write_buf;
	u8 *read_buf;
	size_t read_max;
	size_t read_len;
	size_t write_len;
	struct semaphore sem;
	struct mutex lock;
	wait_queue_head_t wait_udp;
	struct ptp_dev_info *next;
};

struct ptp_tx_ts {
	struct ptp_id id;
	struct ptp_ts ts;
	int missed;
	unsigned long req_time;
	unsigned long resp_time;
	struct {
		u8 buf[MAX_TSM_UDP_LEN];
		int len;
	} data;
	struct ptp_dev_info *dev;
	struct sk_buff *skb;
	struct ptp_msg *msg;
	struct ptp_msg_hdr hdr;
};

struct ptp_event {
	int max;
	int num;
	int event;
	int first;
	int last;
	u32 edge;
	struct ptp_utime t[MAX_TIMESTAMP_EVENT_UNIT];
	u32 timeout;
	unsigned long expired;
};

struct ptp_output {
	struct ptp_utime trig;
	struct ptp_utime start;
	struct ptp_utime stop;
	struct ksz_ptp_time gap;
	u32 iterate;
	u32 len;
	int gpo;
	int level;
};

#define CLOCK_ENTRIES		2

struct ptp_irig_info {
	u32 pulse[100];
	int index;
	u8 tso[8];
	int cur_tso;
	int max_tso;
	struct ptp_utime t;
};

struct ptp_msg_info {
	struct ptp_msg_options data;
	u32 sec;
	struct ptp_msg_info *next;
};

struct ptp_info;

struct ptp_work {
	struct work_struct work;
	struct completion done;
	struct ptp_info *ptp;
	int cmd;
	int subcmd;
	int option;
	int output;
	int result;
	int used;
	union {
		struct ptp_cfg_options cfg;
		struct ptp_tsi_info tsi;
		struct ptp_tsi_options tsi_opt;
		struct ptp_tso_options tso_opt;
		struct ptp_clk_options clk_opt;
		struct ptp_ts_options ts_opt;
		struct ptp_delay_values delay;
		u8 data[8];
	} param;
	struct ptp_dev_info *dev_info;
};

#define PTP_WORK_NUM			(1 << 4)
#define PTP_WORK_LAST			(PTP_WORK_NUM - 1)

struct ptp_access {
	int index;
	struct ptp_work works[PTP_WORK_NUM];
};

struct ptp_reg_ops {
	void (*lock)(struct ptp_info *ptp);
	void (*unlock)(struct ptp_info *ptp);

	void (*get_time)(struct ptp_info *ptp, struct ptp_utime *t);
	void (*set_time)(struct ptp_info *ptp, struct ptp_utime *t);
	void (*adjust_time)(struct ptp_info *ptp, int add, u32 sec, u32 nsec,
		int adj_hack);
	void (*adjust_sync_time)(struct ptp_info *ptp, int diff, u32 interval,
		u32 duration);

	void (*rx_off)(struct ptp_info *ptp, u8 tsi);
	void (*rx_reset)(struct ptp_info *ptp, u8 tsi, u32 *ctrl_ptr);
	void (*rx_restart)(struct ptp_info *ptp, u8 tsi);
	void (*rx_event)(struct ptp_info *ptp, u8 tsi, u8 gpi, u8 event,
		int intr);
	void (*rx_cascade_event)(struct ptp_info *ptp, u8 first, u8 total,
		u8 gpi, u8 event, int intr);
	void (*read_event)(struct ptp_info *ptp, u8 tsi);

	void (*tx_off)(struct ptp_info *ptp, u8 tso);
	void (*tx_event)(struct ptp_info *ptp, u8 tso, u8 gpo, u8 event,
		u32 pulse, u32 cycle, u16 cnt, u32 sec, u32 nsec, u32 iterate,
		int intr, int now, int opt);
	void (*pps_event)(struct ptp_info *ptp, u8 gpo, u32 sec);
	void (*ptp_10MHz)(struct ptp_info *ptp, u8 tso, u8 gpo, u32 sec);
	int (*tx_cascade)(struct ptp_info *ptp, u8 first, u8 total,
		u16 repeat, u32 sec, u32 nsec, int intr);

	void (*start)(struct ptp_info *ptp, int init);
};

struct ptp_ops {
	void (*acquire)(struct ptp_info *ptp);
	void (*release)(struct ptp_info *ptp);

	void (*init)(struct ptp_info *ptp, u8 *mac_addr);
	void (*exit)(struct ptp_info *ptp);
	int (*stop)(struct ptp_info *ptp);
	void (*set_identity)(struct ptp_info *ptp, u8 *addr);
	struct ptp_msg *(*check_msg)(u8 *data, u16 **udp_check_ptr);
	int (*update_msg)(u8 *data, u32 port, u32 overrides);
	void (*get_rx_tstamp)(void *ptr, struct sk_buff *skb);
	void (*get_tx_tstamp)(struct ptp_info *ptp, struct sk_buff *skb);
	int (*hwtstamp_ioctl)(struct ptp_info *ptp, struct ifreq *ifr);
	int (*ixxat_ioctl)(struct ptp_info *ptp, unsigned int cmd,
		struct ifreq *ifr);
	int (*dev_req)(struct ptp_info *ptp, char *arg,
		struct ptp_dev_info *info);
	void (*proc_intr)(struct ptp_info *ptp);

	ssize_t (*sysfs_read)(struct ptp_info *ptp, int proc_num, ssize_t len,
		char *buf);
	void (*sysfs_write)(struct ptp_info *ptp, int proc_num, int num,
		const char *buf);

	int (*drop_pkt)(struct ptp_info *ptp, struct sk_buff *skb, u32 vlan_id,
		int *tag, int *ptp_tag);

	void (*get_rx_info)(struct ptp_info *ptp, u8 *data, u8 port,
		u32 timestamp);
	void (*set_tx_info)(struct ptp_info *ptp, u8 *data, void *tag);
};

#define DEFAULT_GPS_GPI			1
#define DEFAULT_GPS_TSI			1

#define DEFAULT_PPS_TSI			1

#if 1
#define DEFAULT_MHZ_GPO			1
#define DEFAULT_PPS_GPO			0
#else
#define DEFAULT_MHZ_GPO			0
#define DEFAULT_PPS_GPO			1
#endif

/* TSO 1 is reserved if 10 MHz clock is used. */
#define DEFAULT_MHZ_TSO			0
#define DEFAULT_PPS_TSO			2

/* Switch features and bug fixes. */
#define PTP_ADJ_HACK			(1 << 0)
#define PTP_ADJ_SEC			(1 << 1)
#define PTP_PDELAY_HACK			(1 << 2)

/* Software overrides. */

#define PTP_PORT_FORWARD		(1 << 0)
#define PTP_PORT_TX_FORWARD		(1 << 1)

#define PTP_VERIFY_TIMESTAMP		(1 << 8)
#define PTP_ZERO_RESERVED_FIELD		(1 << 9)
#define PTP_CHECK_SYS_TIME		(1 << 16)
#define PTP_CHECK_SYNC_TIME		(1 << 24)
#define PTP_TEST_TX_INFO		(1 << 28)
#define PTP_USE_DEFAULT_PORT		(1 << 29)
#define PTP_KEEP_DST_PORT		(1 << 30)
#define PTP_UPDATE_DST_PORT		(1 << 31)

struct ptp_info {
	struct mutex lock;
	struct ptp_access hw_access;
	struct {
		u8 buf[MAX_TSM_UDP_LEN];
		int len;
	} udp[MAX_TSM_UDP_CNT];

	/* current system time. */
	struct ptp_utime cur_time;
	struct ptp_utime gps_time;
	struct ksz_ptp_time time_diff;
	u32 sec_hi;
	u32 sec_lo;
	struct delayed_work check_pps;
	struct delayed_work update_sec;
	unsigned long update_sec_jiffies;

	u32 adjust;
	int drift;
	int drift_set;

	int adjust_offset;
	int offset_changed;
	s64 adjust_sec;
	s64 sec_changed;

	struct ptp_utime time_set;

	u32 adj_delay;
	u32 get_delay;
	u32 set_delay;
	int pps_offset;
	struct ptp_dev_info *gps_dev;
	unsigned long gps_req_time;
	unsigned long gps_resp_time;
	u8 gps_gpi;
	u8 gps_tsi;
	u16 gps_seqid;
	u8 pps_tsi;
	u8 pps_tso;
	u8 pps_gpo;
	u8 mhz_tso;
	u8 mhz_gpo;
	u8 version;
	u8 ports;
	u8 started;

	/* hardware register values. */
	u16 rx_latency[MAX_PTP_PORT][3];
	u16 tx_latency[MAX_PTP_PORT][3];
	short asym_delay[MAX_PTP_PORT][3];
	u32 peer_delay[MAX_PTP_PORT];

	spinlock_t rx_msg_lock;
	spinlock_t tx_msg_lock;
	struct ptp_msg_info rx_msg_info[MANAGEMENT_MSG + 1];
	struct ptp_msg_info tx_msg_info[MANAGEMENT_MSG + 1];
#if 0
	struct ptp_msg_options rx_msg_chk[MANAGEMENT_MSG + 1];
#endif
	struct ptp_msg *rx_msg;
	struct ptp_msg *tx_msg;
	int tx_msg_cnt;
	int tx_msg_parsed;
	u32 tx_ports;
	int cap;
	int op_mode;
	int op_state;

	/* used to remember tx timestamp to differentiate between pdelay_req
	 * and pdelay_resp.
	 */
	u32 xdelay_ts[MAX_PTP_PORT];
	u32 pdresp_ts[MAX_PTP_PORT];

	/* tx timestamp */
	struct ptp_hw_ts hw_sync[MAX_PTP_PORT];
	struct ptp_hw_ts hw_dreq[MAX_PTP_PORT];
	struct ptp_hw_ts hw_resp[MAX_PTP_PORT];
	struct ptp_tx_ts tx_sync[MAX_PTP_PORT];
	struct ptp_tx_ts tx_dreq[MAX_PTP_PORT];
	struct ptp_tx_ts tx_resp[MAX_PTP_PORT];
	int linked[MAX_PTP_PORT];

	int state;
	u16 def_mode;
	u16 def_cfg;
	u16 mode;
	u16 cfg;
	u16 domain;
	u16 vid;
	int ptp_synt;
	u16 trig_intr;
	u16 ts_intr;
	u16 tx_intr;

	int tsi_intr;
	int tsi_used;
	int tsi_sys;
	int tso_intr;
	int tso_used;
	int tso_sys;
	int ts_status;
	int cascade;
	int cascade_rx;
	int cascade_tx;
	struct {
		int first;
		int total;
		int tso;
	} cascade_gpo[MAX_GPIO];
	struct ptp_clock_identity clockIdentity;
	struct ptp_clock_identity masterIdentity;
	struct ptp_event events[MAX_TIMESTAMP_UNIT];
	struct ptp_output outputs[MAX_TRIG_UNIT + 1];
	int udp_head;
	int udp_tail;
	int dev_major;
	struct ptp_dev_info *dev[2];
	struct ptp_dev_info *tsi_dev[MAX_TIMESTAMP_UNIT];
	struct ptp_dev_info *tso_dev[MAX_TRIG_UNIT];
	char dev_name[2][20];
	wait_queue_head_t wait_ts[MAX_PTP_PORT];
	wait_queue_head_t wait_intr;
	unsigned long delay_ticks;
	int rx_en;
	int tx_en;
	int utc_offset;

	u32 clk_divider;
	u32 (*get_clk_cnt)(void);
	u32 last_clk_cnt;
	u64 total_clk_cnt;
	u32 first_sec;
	u32 intr_sec;
	unsigned long last_jiffies;
	u64 total_jiffies;
	union ktime first_ktime;
	int first_drift;

	uint features;
	uint overrides;

	struct work_struct adj_clk;
	struct work_struct set_latency;

	const struct ptp_ops *ops;
	const struct ptp_reg_ops *reg;
	void (*test_access_time)(struct ptp_info *ptp);

	struct workqueue_struct *access;

	struct device *parent;
#ifdef CONFIG_PTP_1588_CLOCK
	void *clock_info;
	u32 clock_events;
#endif
};

struct ksz_ptp_sysfs {
	struct ksz_dev_attr *ksz_clock_attrs[CLOCK_ENTRIES];
	struct attribute **clock_attrs[CLOCK_ENTRIES];
};
#endif

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
#define PTP_USE_RESERVED_FIELDS		(1 << 5)

#ifdef __KERNEL__
struct ptp_attributes {
	int features;
	int overrides;
	int vid;
};
#endif

#endif
