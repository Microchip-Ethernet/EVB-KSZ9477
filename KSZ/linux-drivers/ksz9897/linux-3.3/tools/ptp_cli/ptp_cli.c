#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <netinet/in.h>

#define USE_DEV_IOCTL
#define USE_GPIO_EVENT
#define USE_TIMESTAMP_OPER

#include "ksz_ptp.c"


struct dev_info {
	int fd;
	u8 *udp_buf;
	int udp_len;
	int index;
	int left;
};

#define DATA_BUFFER_SIZE  2000

static struct dev_info dev[2];

static u8 ptp_tsi_units;
static u8 ptp_tsi_events;
static u8 ptp_tsi_extra;

int tsm_init(void)
{
	char device[20];

	sprintf(device, "/dev/ptp_dev");
	dev[0].fd = open(device, O_RDWR);
	if (dev[0].fd < 0) {
		printf("cannot open ptp device\n");
		return -1;
	}
	sprintf(device, "/dev/ptp_event");
	dev[1].fd = open(device, O_RDWR);
	dev[0].udp_len = DATA_BUFFER_SIZE;
	dev[0].udp_buf = malloc(dev[0].udp_len);
	dev[0].index = 0;
	dev[0].left = 0;
	dev[1].udp_len = DATA_BUFFER_SIZE;
	dev[1].udp_buf = malloc(dev[1].udp_len);
	dev[1].index = 0;
	dev[1].left = 0;

	if (ptp_dev_init(&dev[0].fd, 0, &ptp_drift, &ptp_version, &ptp_ports,
	    &ptp_host_port))
		return 1;
	printf("drift=%d version=%d ports=%d\n",
		ptp_drift, ptp_version, ptp_ports);
	ptp_tsi_units = 12;
	ptp_tsi_events = 2;
	ptp_tsi_extra = 6;
	if (ptp_version >= 2) {
		int rc;

		rc = get_rx_event_info(&dev[0].fd,
			&ptp_tsi_units, &ptp_tsi_events, &ptp_tsi_extra);
		if (rc) {
			ptp_tsi_units = 12;
			ptp_tsi_events = 2;
			ptp_tsi_extra = 6;
		}
		printf("units=%d events=%d num=%d\n",
			ptp_tsi_units, ptp_tsi_events, ptp_tsi_extra);
	}

	return 0;
}

void tsm_cleanup(void)
{
	free(dev[0].udp_buf);
	free(dev[1].udp_buf);
}

int tsm_exit(void)
{
	int rc = 0;

	if (dev[0].fd > 0) {
		rc = ptp_dev_exit(&dev[0].fd);

		/* Wait until tasks exit of loop. */
		usleep(10 * 1000);
		close(dev[0].fd);
		dev[0].fd = 0;
	}
	if (dev[1].fd > 0) {
		close(dev[1].fd);
		dev[1].fd = 0;
	}
	return rc;
}

static int tsm_recv(struct dev_info *info, u8 data[], int len)
{
	struct ptp_udp_msg *udp;
	int n;

	/* There are data left. */
	if (info->left) {
		udp = (struct ptp_udp_msg *) &info->udp_buf[info->index];

		/* But not enough. */
		if (info->left < udp->len) {
			memcpy(info->udp_buf, &info->udp_buf[info->index],
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
			n = read(info->fd, &info->udp_buf[info->index],
				info->udp_len - info->index);
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
	udp = (struct ptp_udp_msg *) &info->udp_buf[info->index];
	if (udp->len > len) {
printf("  ??  %d; %d, %d %d\n", udp->len, len, info->index, info->left);
		exit(1);
	}
	info->index += udp->len;
	info->left -= udp->len;
#if 0
printf("left: i: %d l: %d; u: %d\n", info->index, info->left, udp->len);
#endif
	udp->len -= 2;

	if (len > udp->len)
		len = udp->len;
	memcpy(data, udp->data, len);
	return len;
}

static int tsm_send(u8 data[], int len)
{
	return write(dev[0].fd, data, len);
}

static int waiting_for_resp;

static int tsm_cmd_get_gps(void)
{
	struct tsm_get_gps tsm;

	tsm.cmd = TSM_CMD_GET_GPS_TS;
	waiting_for_resp = 1;
	return tsm_send((u8 *) &tsm, sizeof(tsm));
}

static int tsm_cmd_get_time(u32 timestamp)
{
	struct tsm_get_time tsm;

	tsm.cmd = TSM_CMD_DB_GET_TIME;
	tsm.nsec = htonl(timestamp);
	waiting_for_resp = 1;
	return tsm_send((u8 *) &tsm, sizeof(tsm));
}

static int tsm_cmd_get(u8 msg, u8 port)
{
	struct tsm_db tsm;

	tsm.cmd = TSM_CMD_DB_GET | msg;
	tsm.index = 1 << port;
	tsm.seqid = 0;
	tsm.mac[0] = tsm.mac[1] = 0;
	waiting_for_resp = 1;
	return tsm_send((u8 *) &tsm, sizeof(tsm));
}


struct ptp_utime in_event[2][32];
struct ptp_utime out_event[2][20];
int first_rx = 0;
u8 irig_in[100];
int irig_index;

void setup_rx_event(u8 *data, size_t len)
{
	int i;
	int unit;
	u32 edge;
	struct ptp_tsi_info *info = (struct ptp_tsi_info *) data;
	struct ptp_utime *t;
	struct ptp_utime *in = NULL;

	i = info->num * sizeof(struct ptp_utime) +
		SIZEOF_ptp_tsi_info;
	if (info->event < 2) {
		if (ptp_tsi_extra) {
			if (11 == info->unit)
				in = in_event[info->event];
			else if (0 == info->unit)
				in = &in_event[info->event][8];
			else if (1 == info->unit)
				in = &in_event[info->event][10];
			else if (info->unit > 1 && info->unit < 11)
				in = &in_event[info->event][
					(info->unit - 2) * ptp_tsi_events];
		} else
			in = &in_event[info->event][
				info->unit * ptp_tsi_events];
	}
	unit = info->unit;
	if (unit < first_rx)
#if 0
		unit += 15;
#else
		unit += ptp_tsi_units + ptp_tsi_extra / ptp_tsi_events;
#endif
	unit -= first_rx;
	edge = info->edge;
	t = info->t;
	for (i = 0; i < info->num; i++) {
		if (2 == info->event)
#if 0
			in = &in_event[edge & 1][unit * 2 + i];
#else
#endif
			in = &in_event[edge & 1][unit * ptp_tsi_events + i];
		if (in) {
			in->sec = t->sec;
			in->nsec = t->nsec;
			++in;
		}
		edge >>= 1;
		++t;
	}
}

void clear_rx_event(void)
{
	memset(in_event, 0, sizeof(struct ptp_utime) * 32 * 2);
	in_event[0][31].nsec = 1;
	in_event[1][31].nsec = 1;
	irig_index = 0;
}

static struct ptp_utime *next_event(struct ptp_utime *prev)
{
	struct ptp_utime *next = prev;

	while (!next->sec && !next->nsec)
		++next;
	if (!next->sec)
		next = NULL;
	return next;
}

static int later_time(struct ptp_utime *prev, struct ptp_utime *next)
{
	if (next->sec == prev->sec && next->nsec == prev->nsec)
		return 0;
	if (next->sec > prev->sec || (next->sec == prev->sec &&
			next->nsec > prev->nsec))
		return 1;
	return -1;
}

static void check_rx_event(void)
{
	struct ptp_utime *pair[2];
	struct ptp_utime *next;
	struct ptp_utime *next_next;
	struct ptp_utime *prev;
	struct ptp_utime *temp;
	int diff;
	int later = 0;
	int up;

	memset(out_event, 0, 2 * sizeof(struct ptp_utime) * 20);
	pair[0] = out_event[0];
	pair[1] = out_event[1];

	prev = next_event(in_event[0]);
	next = next_event(in_event[1]);
	if (prev && next)
		up = 0;
	else if (prev)
		up = 0;
	else
		up = 1;
	while (prev || next) {
		if (prev && next) {
			diff = later_time(prev, next);
			if (!later)
				later = diff;
			if (-1 == diff) {
				temp = prev;
				prev = next;
				next = temp;
				up = !up;
			} else {
				*pair[up] = *prev;
				pair[up] = pair[up] + 1;
				next_next = next_event(prev + 1);
				diff = 0;
				if (next_next)
					diff = later_time(next, next_next);
				if (diff >= 0) {
					prev = next;
					next = next_next;
					up = !up;
				} else {
					prev = next_next;
					*pair[!up] = *prev;
					pair[!up] = pair[!up] + 1;
				}
			}
		} else if (prev) {
			next = next_event(prev + 1);
				*pair[up] = *prev;
				pair[up] = pair[up] + 1;
			if (next) {
				*pair[!up] = *prev;
				pair[!up] = pair[!up] + 1;
			}
			prev = next;
			next = NULL;
			if (!later)
				later = 1;
		} else {
			*pair[up] = *next;
			pair[up] = pair[up] + 1;
			prev = next_event(next + 1);
			if (prev) {
				*pair[!up] = *next;
				pair[!up] = pair[!up] + 1;
			}
			next = prev;
			prev = NULL;
			if (!later)
				later = -1;
		}
	}
	diff = later_time(out_event[0], out_event[1]);
	if (!diff && later) {
		if (1 == later)
			out_event[0][0].nsec--;
		else
			out_event[1][0].nsec--;
	}
}

void analyze_rx_event(void)
{
	int up;
	u32 factor = 0;
	u32 num;
	u32 nsec;
	u32 sec;
	u32 prev_up = 0;
	u32 prev_dn = 0;
	struct ptp_utime *dn;
	struct ptp_utime *next = out_event[0];
	struct ptp_utime *prev = out_event[1];

	check_rx_event();
	if (next->sec > prev->sec || (next->sec == prev->sec &&
			next->nsec >= prev->nsec))
		up = 1;
	else {
		up = 0;
		next = out_event[1];
		prev = out_event[0];
	}
	while (prev->sec && next->sec) {
		sec = next->sec;
		nsec = next->nsec;
		if (nsec < prev->nsec) {
			if (sec > prev->sec) {
				sec--;
				nsec += 1000000000;
			} else {
				dn = prev + 0;
				prev = next;
				next = dn;
				up = !up;
				continue;
			}
		}
		if (up)
			printf("up=");
		else
			printf("dn=");
		if (sec != prev->sec)
			printf("%d:", sec - prev->sec);
		else if (up)
			prev_up = ((nsec - prev->nsec) + 5) / 10 * 10;
		else {
			if (!factor) {
				prev_dn = ((nsec - prev->nsec) + 5) / 10 * 10;
				num = prev_dn % 10;
				while (!num && prev_dn) {
					++factor;
					prev_dn /= 10;
					num = prev_dn % 10;
				}
				if (prev_dn < 10) {
					num = factor;
					factor = 1;
					while (num) {
						factor *= 10;
						--num;
					}
				} else
					factor = 0;
			}
			prev_dn = ((nsec - prev->nsec) + 5) / 10 * 10;
		}
		printf("%d ", nsec - prev->nsec);
		if (factor && !up)
			if ((prev_up + prev_dn) / factor == 10)
				irig_in[irig_index++] = prev_up / factor;
		dn = prev + 1;
		prev = next;
		next = dn;
		up = !up;
	}
	printf("\n");
	if (irig_index) {
		for (up = 0; up < irig_index; up++)
			printf("%d ", irig_in[up]);
		printf("\n");
	}
}

int reset_hw(unsigned int bit)
{
	int rc;
	struct ksz_request_actual req;

	req.size = sizeof(struct ksz_request);
	req.cmd = DEV_CMD_INFO;
	req.subcmd = DEV_INFO_RESET;
	req.output = bit;
	rc = ioctl(dev[1].fd, DEV_IOC_PTP, &req);
	if (!rc)
		rc = req.result;
	return rc;
}  /* reset_hw */

static void update_cascade_time(int event, u32 pulse, u32 cycle, int cnt,
	int gap, u32 *start, u32 *stop, int i, u32 *sec, u32 *nsec)
{
	u32 len;

	len = 0;

	if (event >= TRIG_NEG_PERIOD) {
		if (cnt)
			len += cycle * cnt;
		else
			len += 0xF0000000;
	} else if (event >= TRIG_NEG_PULSE)
		len += pulse * 8;
	else
		len += 8;
	i--;
	start[i] = *nsec;
	stop[i] = len;
	len += gap;
	*nsec += len;
	while (*nsec >= 1000000000) {
		*nsec -= 1000000000;
		(*sec)++;
	}
}

static void cascade_chk(u32 *start, u32 *len, u32 *stop, u32 *iterate, int cnt,
	int repeat)
{
	int i;
	int j;
	int min_cnt;
	int diff;
	int gap[10];

	start[cnt] = start[0] + iterate[0];
	for (i = 0; i < cnt; i++) {
		stop[i] = start[i] + len[i];
		gap[i] = start[i + 1] - stop[i];
		if (gap[i] < 0 && (i < cnt - 1 || 1 != repeat)) {
			printf("gap too small: %d=%d\n", i, gap[i]);
			return;
		}
	}
	printf("<");
	for (i = 1; i < cnt; i++) {
		if (iterate[i] < iterate[i - 1]) {
			diff = iterate[i - 1] - iterate[i];
			min_cnt = gap[i - 1] / diff + 1;
printf("less: %d %d %d\n", diff, gap[i - 1], min_cnt);
			min_cnt++;
		} else if (iterate[i] > iterate[i - 1]) {
			diff = iterate[i] - iterate[i - 1];
			min_cnt = gap[i] / diff + 1;
printf("more: %d %d %d\n", diff, gap[i], min_cnt);
			min_cnt++;
		} else
			min_cnt = repeat;
		if (repeat > min_cnt)
			repeat = min_cnt;
	}
printf("repeat: %d\n", repeat);
	for (i = 0; i < repeat; i++) {
		for (j = 0; j < cnt; j++) {
			printf("%d: %u %u %d %u: %u\n",
				j, start[j], len[j], gap[j],
				iterate[j], stop[j]);
			if (stop[j] > start[j + 1])
				printf("> %d %u %u\n", j,
					stop[j], start[j + 1]);
			start[j] += iterate[j];
			stop[j] = start[j] + len[j];
			if (!j)
				start[cnt] = start[0];
		}
		printf("%u\n", start[cnt]);
	}
	printf(">\n");
}

static int irig_pattern[10] = {
	0x0000,
	0x0001,
	0x0003,
	0x0007,
	0x000f,
	0x001f,
	0x003f,
	0x007f,
	0x00ff,
	0x01ff,
};

#define IRIG_INTERVAL			1000000

void irig(u32 num, u32 cycle)
{
	u8 hi;
	u8 lo;
	int cnt;
	int i;
	int m;
	int n;
	int rc;
	int tso;
	int cascade = 0;
	int tx_flags = PTP_CMD_INTR_OPER | PTP_CMD_SILENT_OPER |
		PTP_CMD_ON_TIME | PTP_CMD_REL_TIME;
	u32 cascade_sec;
	u32 cascade_nsec;
	u64 nsec;
	u8 pulse[40];
	u16 pattern;
	int *fd = &dev[1].fd;
	
	hi = (num >> 4) & 0xff;
	lo = num & 0xff;
	pulse[0] = 8;
	n = 1;
	for (i = 0; i < 4; i++, n++) {
		if (lo & 1)
			pulse[n] = 5;
		else
			pulse[n] = 2;
		lo >>= 1;
	}
	pulse[n++] = 2;
	num >>= 4;
	lo = num & 0xff;
	for (i = 0; i < 3; i++, n++) {
		if (lo & 1)
			pulse[n] = 5;
		else
			pulse[n] = 2;
		lo >>= 1;
	}
	pulse[n++] = 8;
	num >>= 4;
	if (num) {
	lo = num & 0xff;
	for (i = 0; i < 4; i++, n++) {
		if (lo & 1)
			pulse[n] = 5;
		else
			pulse[n] = 2;
		lo >>= 1;
	}
	pulse[n++] = 2;
	num >>= 4;
	lo = num & 0xff;
	for (i = 0; i < 4; i++, n++) {
		if (lo & 1)
			pulse[n] = 5;
		else
			pulse[n] = 2;
		lo >>= 1;
	}
	pulse[n++] = 8;
	}
	for (i = 0; i < n; i++)
		printf("%d ", pulse[i]);
	printf("\n");
#if 0
	n = 8;
#endif
	tso = 0;
	cascade_sec = 2;
	cascade_nsec = 0;
	nsec = 0;
	i = 0;
	while (i < n) {
		rc = tx_cascade_init(fd, tso, 1, 1, 0, NULL);
		if (rc) {
			printf("init failed: %d\n", tso);
			break;
		}
		cascade = 1;
		if (i + 1 < n && 10 + pulse[i + 1] < 16) {
			pattern = irig_pattern[pulse[i]] |
				(irig_pattern[pulse[i + 1]] << 10);
			m = 2;
			cnt = pulse[i + 1] + 1 + 10;
		} else {
			pattern = irig_pattern[pulse[i]];
			m = 1;
			cnt = pulse[i] + 1;
		}
#if 0
printf("%d %d %x\n", pulse[i], pulse[i+1], pattern);
#endif
		rc = tx_event(fd, tso, 1, TRIG_REG_OUTPUT, pattern, cycle, cnt,
			0, cascade_sec, cascade_nsec, tx_flags, NULL);
		if (rc) {
			printf("tx failed: %d\n", tso);
			break;
		}
		rc = tx_cascade(fd, tso, 1, 1, 1, tx_flags);
		if (rc) {
			printf("cascade failed: %d\n", tso);
			break;
		}
		nsec += (u64) 10 * cycle * m;
		while (nsec >= 1000000000) {
			nsec -= 1000000000;
			cascade_sec++;
		}
		cascade_nsec = (u32) nsec;
		cascade = 0;
		tso++;
		i += m;
	}
}


struct ptp_clock_identity selfClockIdentity;
struct ptp_clock_identity masterClockIdentity;

#if 0
static int ptp_msg_2step;
static int ptp_msg_alternate;
static int ptp_msg_unicast;
static int ptp_correction;
static int ptp_msg_count = 1;
static int ptp_msg_domain;
static int ptp_dst_port;
static int ptp_req_port = 1;
static int ptp_src_port;

static u16 seqid_sync;
static u16 seqid_delay_req;
static u16 seqid_pdelay_req;
static u16 seqid_management;
static u16 seqid_signaling;
static u32 sync_sec;

void prepare_hdr(struct ptp_msg_hdr *hdr, int message, int len, int seqid,
	int ctrl, int interval, struct ptp_clock_identity *id)
{
	len += sizeof(struct ptp_msg_hdr);

	hdr->transportSpecific = 0;
	hdr->messageType = message;
	hdr->reserved1 = 0;
	hdr->versionPTP = 2;
	hdr->messageLength = htons(len);
	hdr->domainNumber = ptp_msg_domain;
	hdr->reserved2 = 0;
	hdr->reserved2 = ptp_dst_port;
	hdr->flagField.data = 0;
	if (ptp_msg_alternate && (SYNC_MSG == message ||
			FOLLOW_UP_MSG == message ||
			ANNOUNCE_MSG == message ||
			DELAY_RESP_MSG == message))
		hdr->flagField.flag.alternateMasterFlag = 1;
	if (ptp_msg_2step && (SYNC_MSG == message ||
			PDELAY_RESP_MSG == message))
		hdr->flagField.flag.twoStepFlag = 1;
	if (ptp_msg_unicast)
		hdr->flagField.flag.unicastFlag = 1;
	hdr->correctionField.scaled_nsec_hi = 0;
	hdr->correctionField.scaled_nsec_lo = 0;
	if (ptp_correction) {
		hdr->correctionField.scaled_nsec_hi =
			htonl(ptp_correction >> 16);
		hdr->correctionField.scaled_nsec_lo =
			htonl(ptp_correction << SCALED_NANOSEC_SHIFT);
	}
	hdr->reserved3 = 0;
	memcpy(&hdr->sourcePortIdentity.clockIdentity, id,
		sizeof(struct ptp_clock_identity));
	hdr->sourcePortIdentity.port = htons(1);
	hdr->sequenceId = htons(seqid);
	hdr->controlField = ctrl;
	hdr->logMessageInterval = interval;
}

struct ptp_msg *signaling_msg(int type, int message, u8 period, u32 duration)
{
	static char payload[(sizeof(struct ptp_msg) + 2000) & ~3];
	struct ptp_msg* msg = (struct ptp_msg *) payload;
	int len;
	int logInterval;
	int seqid;
	int ctrl;
	struct ptp_clock_identity *clock;
	struct ptp_msg_signaling *signaling;
	struct ptp_request_unicast_tlv *request;
	struct ptp_grant_unicast_tlv *grant;
	struct ptp_cancel_unicast_tlv *cancel;

	ctrl = 5;
	logInterval = 0x7F;
	seqid_signaling++;
	seqid = seqid_signaling;
	signaling = &msg->data.signaling;
	switch (type) {
	case TLV_REQUEST_UNICAST_TRANSMISSION:
		clock = &selfClockIdentity;
		memcpy(&signaling->b.targetPortIdentity.clockIdentity,
			&masterClockIdentity,
			sizeof(struct ptp_clock_identity));
		signaling->b.targetPortIdentity.port = htons(0xffff);
		request = signaling->tlv.request;
		request->tlv.tlvType = htons(type);
		request->tlv.lengthField = htons(sizeof(*request) - 4);
		request->messageType = message;
		request->reserved1 = 0;
		request->logInterMessagePeriod = period;
		request->durationField = htonl(duration);
		break;
	case TLV_GRANT_UNICAST_TRANSMISSION:
		clock = &masterClockIdentity;
		memcpy(&signaling->b.targetPortIdentity.clockIdentity,
			&selfClockIdentity,
			sizeof(struct ptp_clock_identity));
		signaling->b.targetPortIdentity.port = htons(1);
		grant = signaling->tlv.grant;
		grant->tlv.tlvType = htons(type);
		grant->tlv.lengthField = htons(sizeof(*grant) - 4);
		grant->messageType = message;
		grant->reserved1 = 0;
		grant->logInterMessagePeriod = period;
		grant->durationField = htonl(duration);
		grant->reserved2 = 0;
		grant->renewal = 1;
		break;
	case TLV_CANCEL_UNICAST_TRANSMISSION:
		clock = &selfClockIdentity;
		memcpy(&signaling->b.targetPortIdentity.clockIdentity,
			&masterClockIdentity,
			sizeof(struct ptp_clock_identity));
		signaling->b.targetPortIdentity.port = htons(0xffff);
		cancel = signaling->tlv.cancel;
		cancel->tlv.tlvType = htons(type);
		cancel->tlv.lengthField = htons(sizeof(*cancel) - 4);
		cancel->messageType = message;
		cancel->reserved1 = 0;
		cancel->reserved2 = 0;
		break;
	case TLV_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION:
		clock = &masterClockIdentity;
		memcpy(&signaling->b.targetPortIdentity.clockIdentity,
			&selfClockIdentity,
			sizeof(struct ptp_clock_identity));
		signaling->b.targetPortIdentity.port = htons(1);
		cancel = signaling->tlv.cancel;
		cancel->tlv.tlvType = htons(type);
		cancel->tlv.lengthField = htons(sizeof(*cancel) - 4);
		cancel->messageType = message;
		cancel->reserved1 = 0;
		cancel->reserved2 = 0;
		break;
	}
	len = sizeof(struct ptp_msg_signaling_base) + 4 +
		ntohs(signaling->tlv.request[0].tlv.lengthField);
	prepare_hdr(&msg->hdr, SIGNALING_MSG, len, seqid, ctrl, logInterval,
		clock);
	return msg;
}

struct ptp_msg *management_msg(int id, int error_id, int n)
{
	static char payload[(sizeof(struct ptp_msg) + 2000) & ~3];
	struct ptp_msg* msg = (struct ptp_msg *) payload;
	int len;
	int logInterval;
	int seqid;
	int ctrl;
	int i;
	int m;
	char ch;
	struct ptp_clock_identity *clock;
	struct ptp_msg_management *management;
	struct ptp_management_error_tlv *error;
	struct ptp_management_tlv *tlv;
	struct ptp_timestamp *ts;
	struct ptp_text *text;

	clock = &selfClockIdentity;
	ctrl = 4;
	logInterval = 0x7F;
	seqid_management++;
	seqid = seqid_management;
	management = &msg->data.management;
	memcpy(&management->b.targetPortIdentity.clockIdentity,
		&masterClockIdentity, sizeof(struct ptp_clock_identity));
	management->b.targetPortIdentity.port = htons(1);
	management->b.startingBoundaryHops = 5;
	management->b.boundaryHops = 5;
	management->b.actionField = MANAGEMENT_RESPONSE;
	management->b.reserved2 = 0;
	if (error_id) {
		error = management->tlv.error;
		error->tlv.tlvType = htons(TLV_MANAGEMENT_ERROR_STATUS);
		m = 8 + n;
		if (m & 1)
			m++;
		error->tlv.lengthField = htons(m);
		error->managementErrorId = htons(error_id);
		error->managementId = htons(id);
		error->reserved1 = 0;
		text = (struct ptp_text *) error->data;
		if (n > 51)
			text->lengthField = 50;
		else
			text->lengthField = n - 1;
		ch = 'A';
		for (i = 0; i < text->lengthField; i++) {
			text->textField[i] = ch;
			ch++;
			if (ch > 'z')
				ch = 'A';
		}
		for (; i < m; i++)
			text->textField[i] = '\0';
		len = sizeof(struct ptp_msg_management_base) + 4 +
			ntohs(error->tlv.lengthField);
	} else {
		tlv = management->tlv.normal;
		tlv->tlv.tlvType = htons(TLV_MANAGEMENT);
		switch (id) {
		case M_TIME:
			n = 10;
			tlv->tlv.lengthField = htons(2 + n);
			tlv->managementId = htons(M_TIME);
			ts = (struct ptp_timestamp *) tlv->dataField;
			ts->sec.hi = 0;
			ts->sec.lo = htonl(1234);
			ts->nsec = htonl(5678);
			len = sizeof(struct ptp_msg_management_base) + 4 +
				ntohs(tlv->tlv.lengthField);
			break;
		}
	}
	prepare_hdr(&msg->hdr, MANAGEMENT_MSG, len, seqid, ctrl, logInterval,
		clock);
	return msg;
}

void prepare_msg(struct ptp_msg *msg, int message)
{
	int len;
	int logInterval;
	int seqid;
	int ctrl;
	int correction;
	struct ptp_clock_identity *clock;
	struct ptp_msg_sync *sync;
	struct ptp_msg_follow_up *follow_up;
	struct ptp_msg_delay_resp *delay_resp;
	struct ptp_msg_pdelay_req *pdelay_req;
	struct ptp_msg_pdelay_resp *pdelay_resp;
	struct ptp_msg_pdelay_resp_follow_up *pdelay_follow_up;

	correction = ptp_correction;
	clock = &selfClockIdentity;
	ctrl = 5;
	logInterval = 0x7F;
	switch (message) {
	case SYNC_MSG:
		len = sizeof(struct ptp_msg_sync);
		ctrl = 0;
		if (!ptp_msg_unicast)
			logInterval = 0;
		seqid_sync++;
		seqid = seqid_sync;
		sync = &msg->data.sync;
		sync->originTimestamp.sec.hi = 0;
		if (ptp_msg_2step || ptp_dst_port) {
			sync->originTimestamp.sec.lo = 0;
			sync->originTimestamp.nsec = 0;
		} else {
			sync->originTimestamp.sec.lo = htonl(sync_sec++);
			sync->originTimestamp.nsec = htonl(1000);
		}
		clock = &masterClockIdentity;
		break;
	case FOLLOW_UP_MSG:
		len = sizeof(struct ptp_msg_follow_up);
		ctrl = 2;
		if (!ptp_msg_unicast)
			logInterval = 0;
		seqid = seqid_sync;
		follow_up = &msg->data.follow_up;
		follow_up->preciseOriginTimestamp.sec.hi = 0;
		follow_up->preciseOriginTimestamp.sec.lo = htonl(sync_sec);
		follow_up->preciseOriginTimestamp.nsec = htonl(1000);
		clock = &masterClockIdentity;
		break;
	case DELAY_REQ_MSG:
		len = sizeof(struct ptp_msg_sync);
		ctrl = 1;
		seqid_delay_req++;
		seqid = seqid_delay_req;
		sync = &msg->data.sync;
		sync->originTimestamp.sec.hi = 0;
		sync->originTimestamp.sec.lo = 0;
		sync->originTimestamp.nsec = 0;
		break;
	case DELAY_RESP_MSG:
		len = sizeof(struct ptp_msg_delay_resp);
		ctrl = 3;
		if (!ptp_msg_unicast)
			logInterval = 1;
		seqid = seqid_delay_req;
		delay_resp = &msg->data.delay_resp;
		delay_resp->receiveTimestamp.sec.hi = 0;
		delay_resp->receiveTimestamp.sec.lo = htonl(sync_sec);
		delay_resp->receiveTimestamp.nsec = htonl(2000);
		memcpy(&delay_resp->requestingPortIdentity.clockIdentity,
			&selfClockIdentity, sizeof(struct ptp_clock_identity));
		delay_resp->requestingPortIdentity.port = htons(ptp_req_port);
		clock = &masterClockIdentity;
		break;
	case PDELAY_REQ_MSG:
		len = sizeof(struct ptp_msg_pdelay_req);
		seqid_pdelay_req++;
		seqid = seqid_pdelay_req;
		pdelay_req = &msg->data.pdelay_req;
		pdelay_req->originTimestamp.sec.hi = 0;
		pdelay_req->originTimestamp.sec.lo = htonl(sync_sec);
		pdelay_req->originTimestamp.nsec = htonl(1000);
		break;
	case PDELAY_RESP_MSG:
		len = sizeof(struct ptp_msg_pdelay_resp);
		seqid = seqid_pdelay_req;
		pdelay_resp = &msg->data.pdelay_resp;
		pdelay_resp->requestReceiptTimestamp.sec.hi = 0;
		if (ptp_msg_2step) {
			pdelay_resp->requestReceiptTimestamp.sec.lo =
				htonl(sync_sec);
			pdelay_resp->requestReceiptTimestamp.nsec =
				htonl(2000);
		} else {
			pdelay_resp->requestReceiptTimestamp.sec.lo = 0;
			pdelay_resp->requestReceiptTimestamp.nsec = 0;
			ptp_correction = 12345;
		}
		memcpy(&pdelay_resp->requestingPortIdentity.clockIdentity,
			&selfClockIdentity, sizeof(struct ptp_clock_identity));
		pdelay_resp->requestingPortIdentity.port = htons(ptp_req_port);
		clock = &masterClockIdentity;
		break;
	case PDELAY_RESP_FOLLOW_UP_MSG:
		len = sizeof(struct ptp_msg_pdelay_resp_follow_up);
		seqid = seqid_pdelay_req;
		pdelay_follow_up = &msg->data.pdelay_resp_follow_up;
		pdelay_follow_up->responseOriginTimestamp.sec.hi = 0;
		pdelay_follow_up->responseOriginTimestamp.sec.lo =
			htonl(sync_sec);
		pdelay_follow_up->responseOriginTimestamp.nsec =
			htonl(3000);
		memcpy(&pdelay_follow_up->requestingPortIdentity.clockIdentity,
			&selfClockIdentity, sizeof(struct ptp_clock_identity));
		pdelay_follow_up->requestingPortIdentity.port =
			htons(ptp_req_port);
		clock = &masterClockIdentity;
		break;
	case ANNOUNCE_MSG:
	default:
		seqid = 0;
		break;
	}
	prepare_hdr(&msg->hdr, message, len, seqid, ctrl, logInterval,
		clock);
	if (PDELAY_REQ_MSG == message && ptp_dst_port)
		msg->hdr.sourcePortIdentity.port = htons(ptp_src_port);
	ptp_correction = correction;
}

int send_msg(struct ptp_msg *msg, int len)
{
	int rc;
	struct ksz_request_actual req;
	struct ptp_msg_hdr *param = (struct ptp_msg_hdr *) &req.param;

	if (!len)
		len = ntohs(msg->hdr.messageLength);
	memcpy(param, msg, len);
	req.size = sizeof(struct ksz_request) + len;
	req.cmd = DEV_CMD_INFO;
	req.subcmd = DEV_INFO_MSG;
	rc = ioctl(dev[1].fd, DEV_IOC_PTP, &req);
	if (!rc)
		rc = req.result;
	return rc;
}

void resp_msg(struct ptp_msg *req)
{
	char payload[sizeof(struct ptp_msg) + 4];
	struct ptp_msg* resp = (struct ptp_msg *) payload;
	int len;
	int logInterval;
	int message;
	int seqid;
	int ctrl;
	int correction;
	u32 nsec_hi;
	u32 nsec_lo;
	struct ptp_clock_identity *clock;
	struct ptp_msg_delay_resp *delay_resp;
	struct ptp_msg_pdelay_resp *pdelay_resp;
	struct ptp_msg_pdelay_resp_follow_up *pdelay_follow_up;

	/* Own multicast mesage. */
	if (!memcmp(&req->hdr.sourcePortIdentity.clockIdentity,
			&selfClockIdentity,
			sizeof(struct ptp_clock_identity)))
		return;

	/* Not same domain. */
	if (req->hdr.domainNumber != ptp_msg_domain)
		return;

	correction = ptp_correction;
	clock = &selfClockIdentity;
	logInterval = 0x7F;
	switch (req->hdr.messageType) {
	case DELAY_REQ_MSG:
		message = DELAY_RESP_MSG;
		len = sizeof(struct ptp_msg_delay_resp);
		ctrl = 3;
		logInterval = 0x7F;
		seqid = ntohs(req->hdr.sequenceId);
		nsec_hi = ntohl(req->hdr.correctionField.scaled_nsec_hi);
		nsec_lo = ntohl(req->hdr.correctionField.scaled_nsec_lo);
		ptp_correction = (nsec_hi << 16) | (nsec_lo >> 16);
		delay_resp = &resp->data.delay_resp;
		delay_resp->receiveTimestamp.sec.hi = 0;
		delay_resp->receiveTimestamp.sec.lo = htonl(sync_sec);
		delay_resp->receiveTimestamp.nsec = htonl(2000);
		memcpy(&delay_resp->requestingPortIdentity,
			&req->hdr.sourcePortIdentity,
			sizeof(struct ptp_port_identity));
		break;
	case PDELAY_REQ_MSG:
		message = PDELAY_RESP_MSG;
		len = sizeof(struct ptp_msg_pdelay_resp);
		ctrl = 5;
		logInterval = 0x7F;
		seqid = ntohs(req->hdr.sequenceId);
		pdelay_resp = &resp->data.pdelay_resp;
		pdelay_resp->requestReceiptTimestamp.sec.hi = 0;
		if (ptp_msg_2step) {
			pdelay_resp->requestReceiptTimestamp.sec.lo =
				htonl(sync_sec);
			pdelay_resp->requestReceiptTimestamp.nsec =
				htonl(2000);
		} else {
			nsec_hi = ntohl(
				req->hdr.correctionField.scaled_nsec_hi);
			nsec_lo = ntohl(
				req->hdr.correctionField.scaled_nsec_lo);
			ptp_correction = (nsec_hi << 16) | (nsec_lo >> 16);
			ptp_correction += 12345;
			pdelay_resp->requestReceiptTimestamp.sec.lo = 0;
			pdelay_resp->requestReceiptTimestamp.nsec = 0;
		}
		memcpy(&pdelay_resp->requestingPortIdentity,
			&req->hdr.sourcePortIdentity,
			sizeof(struct ptp_port_identity));
		if (ptp_msg_2step) {
			prepare_hdr(&resp->hdr, message, len, seqid, ctrl,
				logInterval, clock);
			send_msg(resp, 0);
		} else
			break;

		message = PDELAY_RESP_FOLLOW_UP_MSG;
		len = sizeof(struct ptp_msg_pdelay_resp_follow_up);
		ctrl = 5;
		logInterval = 0x7F;
		seqid = ntohs(req->hdr.sequenceId);
		nsec_hi = ntohl(req->hdr.correctionField.scaled_nsec_hi);
		nsec_lo = ntohl(req->hdr.correctionField.scaled_nsec_lo);
		ptp_correction = (nsec_hi << 16) | (nsec_lo >> 16);
		pdelay_follow_up = &resp->data.pdelay_resp_follow_up;
		pdelay_follow_up->responseOriginTimestamp.sec.hi = 0;
		pdelay_follow_up->responseOriginTimestamp.sec.lo =
			htonl(sync_sec);
		pdelay_follow_up->responseOriginTimestamp.nsec =
			htonl(3000);
		memcpy(&pdelay_follow_up->requestingPortIdentity,
			&req->hdr.sourcePortIdentity,
			sizeof(struct ptp_port_identity));
		break;
	default:
		return;
	}
	prepare_hdr(&resp->hdr, message, len, seqid, ctrl, logInterval,
		clock);
	ptp_correction = correction;
	send_msg(resp, 0);
}

void send_ptp_msg(char *line, int hcount, unsigned int *hex, int count,
	unsigned int *num)
{
	char payload[(sizeof(struct ptp_msg) + 2000) & ~3];
	struct ptp_msg* msg = (struct ptp_msg *) payload;
	int ptp_msg_len = 0;

	if (!strcmp(line, "mg")) {
		msg = management_msg(M_NULL_MANAGEMENT, M_NO_SUCH_ID, 1412);
		send_msg(msg, ptp_msg_len);
		msg = management_msg(M_TIME, 0, 0);
		send_msg(msg, ptp_msg_len);
	} else if (!strcmp(line, "sg")) {
		msg = signaling_msg(TLV_REQUEST_UNICAST_TRANSMISSION,
			ANNOUNCE_MSG, 0, 60);
		send_msg(msg, ptp_msg_len);
		msg = signaling_msg(TLV_GRANT_UNICAST_TRANSMISSION,
			ANNOUNCE_MSG, 0, 60);
		send_msg(msg, ptp_msg_len);
		msg = signaling_msg(TLV_CANCEL_UNICAST_TRANSMISSION,
			ANNOUNCE_MSG, 0, 0);
		send_msg(msg, ptp_msg_len);
		msg = signaling_msg(
			TLV_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION,
			ANNOUNCE_MSG, 0, 0);
		send_msg(msg, ptp_msg_len);
	} else
	switch (line[0]) {
	case 'l':
		if (count >= 2)
			ptp_msg_len = num[0];
		else
			printf("%d\n", ptp_msg_len);
		break;
	case 'm':
		if (hcount >= 2)
			seqid_sync += hex[0];
		prepare_msg(msg, SYNC_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case 'n':
		if (hcount >= 2)
			seqid_sync += hex[0];
		prepare_msg(msg, FOLLOW_UP_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case 'a':
		if (hcount >= 2)
			seqid_delay_req += hex[0];
		prepare_msg(msg, DELAY_REQ_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case 'b':
		if (hcount >= 2)
			seqid_delay_req += hex[0];
		prepare_msg(msg, DELAY_RESP_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case 'x':
		if (hcount >= 2)
			seqid_pdelay_req += hex[0];
		prepare_msg(msg, PDELAY_REQ_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case 'y':
		if (hcount >= 2)
			seqid_pdelay_req += hex[0];
		prepare_msg(msg, PDELAY_RESP_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case 'z':
		if (hcount >= 2)
			seqid_pdelay_req += hex[0];
		prepare_msg(msg, PDELAY_RESP_FOLLOW_UP_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case 'c':
		if (count >= 2)
			ptp_correction = num[0];
		else
			printf("%d\n", ptp_correction);
		break;
	case 'd':
		if (count >= 2)
			ptp_msg_domain = num[0];
		else
			printf("%d\n", ptp_msg_domain);
		break;
	case 'p':
		if (count >= 2)
			ptp_dst_port = num[0];
		else
			printf("%d\n", ptp_dst_port);
		break;
	case 'r':
		if (count >= 2)
			ptp_req_port = num[0];
		else
			printf("%d\n", ptp_req_port);
		break;
	case 's':
		if (count >= 2)
			ptp_src_port = num[0];
		else
			printf("%d\n", ptp_src_port);
		break;
	case 't':
		if (count >= 2)
			ptp_msg_2step = num[0];
		else
			printf("2-step=%d\n", ptp_msg_2step);
		break;
	case 'u':
		if (count >= 2)
			ptp_msg_count = num[0];
		else
			printf("%d\n", ptp_msg_count);
		break;
	}
}

int send_ptp_event(int msg_type, int port, int seqid)
{
	char payload[(sizeof(struct ptp_msg) + 2000) & ~3];
	struct ptp_msg* msg = (struct ptp_msg *) payload;
	int ptp_msg_len = 0;
	int rc = 0;

	ptp_dst_port = port;
	switch (msg_type) {
	case SYNC_MSG:
		seqid_sync = seqid;
		prepare_msg(msg, SYNC_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case DELAY_REQ_MSG:
		seqid_delay_req = seqid;
		prepare_msg(msg, DELAY_REQ_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case PDELAY_REQ_MSG:
		seqid_pdelay_req = seqid;
		prepare_msg(msg, PDELAY_REQ_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	case PDELAY_RESP_MSG:
		seqid_pdelay_req = seqid;
		prepare_msg(msg, PDELAY_RESP_MSG);
		send_msg(msg, ptp_msg_len);
		break;
	default:
		rc = -EINVAL;
	}
	return rc;
}
#endif

void get_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[10];
	unsigned int hex[10];
	int rc;
	int cont = 1;
	char cmd[80];
	char line[80];
	int rx_unit;
	int tx_unit;
	int rx_latency;
	int tx_latency;
	int asym_delay;
	u16 tx_cnt = 1;
	u16 tx_pattern = 0x5A;
	u32 tx_pulse = 100;
	u32 tx_cycle = 1000;
	u32 tx_nsec = 0;
	u32 tx_sec = 2;
	u32 cascade_gap = 120;
	u16 cascade_cnt = 1;
	u32 cascade_iterate = 10000;
	u32 rx_timeout = 2000;
	int rx_flags = PTP_CMD_INTR_OPER;
	int tx_flags = PTP_CMD_INTR_OPER | PTP_CMD_ON_TIME | PTP_CMD_REL_TIME;
	u8 ptp_domain = 0;
	u32 ptp_access_delay = 0;
	int ptp_alternate = 0;
	int ptp_as = 0;
	int ptp_check = 0;
	int ptp_csum = 0;
	int ptp_master = 0;
	int ptp_2step = 0;
	int ptp_p2p = 0;
	int ptp_unicast = 0;
	int ptp_drop_sync = 0;
	int ptp_delay_assoc = 0;
	int ptp_pdelay_assoc = 0;
	int ptp_sync_assoc = 0;
	int ptp_priority = 0;
	int ptp_started = 0;
	int cascade = 0;
	u32 cascade_sec;
	u32 cascade_nsec;
	u32 start[10];
	u32 len[10];
	u32 stop[10];
	u32 iterate[10];
	int *fd = &dev[1].fd;

	get_global_cfg(fd, &ptp_master, &ptp_2step, &ptp_p2p,
		&ptp_as, &ptp_unicast, &ptp_alternate, &ptp_csum, &ptp_check,
		&ptp_delay_assoc, &ptp_pdelay_assoc, &ptp_sync_assoc,
		&ptp_drop_sync, &ptp_priority, &ptp_domain, &ptp_access_delay,
		&ptp_started);
	printf("access delay = %u\n", ptp_access_delay);
	if (!ptp_started)
		printf("PTP not started!  Some operations may not work.\n");
	do {
		printf("> ");
		if (fgets(line, 80, fp) == NULL)
			break;
		cmd[0] = '\0';
		count = sscanf(line, "%s %u %u %u %u %u %u %u %u %u %u", cmd,
			(unsigned int *) &num[0],
			(unsigned int *) &num[1],
			(unsigned int *) &num[2],
			(unsigned int *) &num[3],
			(unsigned int *) &num[4],
			(unsigned int *) &num[5],
			(unsigned int *) &num[6],
			(unsigned int *) &num[7],
			(unsigned int *) &num[8],
			(unsigned int *) &num[9]);
		hcount = sscanf(line, "%s %x %x %x %x %x %x %x %x %x %x", cmd,
			(unsigned int *) &hex[0],
			(unsigned int *) &hex[1],
			(unsigned int *) &hex[2],
			(unsigned int *) &hex[3],
			(unsigned int *) &hex[4],
			(unsigned int *) &hex[5],
			(unsigned int *) &hex[6],
			(unsigned int *) &hex[7],
			(unsigned int *) &hex[8],
			(unsigned int *) &hex[9]);
		if (count > 1 && !num[0] && hex[0])
			for (rc = 0; rc < count - 1; rc++)
				num[rc] = hex[rc];
		if (!strcmp(cmd, "sci") || !strcmp(cmd, "mci")) {
			struct ptp_clock_identity id;
			struct ptp_clock_identity* clock;

			count = sscanf(line, "%s %x:%x:%x:%x:%x:%x:%x:%x", cmd,
				&num[0], &num[1], &num[2], &num[3],
				&num[4], &num[5], &num[6], &num[7]);
			if (!strcmp(cmd, "sci"))
				clock = &selfClockIdentity;
			else
				clock = &masterClockIdentity;
			if (count >= 9) {
				for (count = 0; count < 8; count++)
					id.addr[count] = (u8) num[count];
				memcpy(clock, &id,
					sizeof(struct ptp_clock_identity));
				if (!strcmp(cmd, "sci")) {
					rc = set_clock_ident(fd, 0, &id);
					print_err(rc);
				}
			}
			printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
				clock->addr[0],
				clock->addr[1],
				clock->addr[2],
				clock->addr[3],
				clock->addr[4],
				clock->addr[5],
				clock->addr[6],
				clock->addr[7]);
		} else if (!strcmp(cmd, "irig")) {
			if (hcount >= 2)
				irig(hex[0], tx_cycle);
		} else if (!strcmp(cmd, "huc")) {
			if (count >= 2) {
				ptp_csum = num[0];
				set_hw_csum(fd, ptp_csum);
			} else
				printf("udp csum = %d\n", ptp_csum);
		} else if (!strcmp(cmd, "has")) {
			if (count >= 2) {
				ptp_as = num[0];
				set_hw_as(fd, ptp_as);
			} else
				printf("802.1as = %d\n", ptp_as);
		} else if (!strcmp(cmd, "hds")) {
			if (count >= 2) {
				ptp_drop_sync = num[0];
				set_hw_drop_sync(fd, ptp_drop_sync);
			} else
				printf("drop sync = %d\n", ptp_drop_sync);
		} else if (!strcmp(cmd, "hda")) {
			if (count >= 2) {
				ptp_delay_assoc = num[0];
				set_hw_delay_assoc(fd, ptp_delay_assoc);
			} else
				printf("delay assoc = %d\n", ptp_delay_assoc);
		} else if (!strcmp(cmd, "hpda")) {
			if (count >= 2) {
				ptp_pdelay_assoc = num[0];
				set_hw_pdelay_assoc(fd, ptp_pdelay_assoc);
			} else
				printf("pdelay assoc = %d\n", ptp_pdelay_assoc);
		} else if (!strcmp(cmd, "hsa")) {
			if (count >= 2) {
				ptp_sync_assoc = num[0];
				set_hw_sync_assoc(fd, ptp_sync_assoc);
			} else
				printf("sync assoc = %d\n", ptp_sync_assoc);
		} else if (!strcmp(cmd, "hp")) {
			if (count >= 2) {
				ptp_priority = num[0];
				set_hw_priority(fd, ptp_priority);
			} else
				printf("priority = %d\n", ptp_priority);
#if 0
		} else if (!strcmp(cmd, "mg")) {
			send_ptp_msg(cmd, 0, NULL, 0, NULL);
		} else if (!strcmp(cmd, "sg")) {
			send_ptp_msg(cmd, 0, NULL, 0, NULL);
#endif
		} else if (!strcmp(cmd, "die")) {
			printf("divide by zero...\n");
			printf("%f\n", 8.0 / num[0]);
			printf("floating point division\n");
			printf("%d\n", 8 / num[0]);
			printf("divide by zero.\n");
		} else if ('c' == line[1]) {
			switch (line[0]) {
			case 'g':
				rc = get_clock(fd, &num[0], &num[1]);
				if (!rc)
					printf("%x:%9u\n", num[0], num[1]);
				else
					print_err(rc);
				break;
			case 's':
				if (count < 2)
					break;
				if (count < 3)
					num[1] = 0;
				rc = set_clock(fd, num[0], num[1]);
				print_err(rc);
				break;
			case 'i':
				if (count < 2)
					break;
				if (count < 3)
					num[1] = 0;
				if (900000000 <= num[0] && count >= 4)
					rc = set_clock(fd,
						0xffffffff, 100000000);
				rc = get_clock(fd, &num[2], &num[3]);
				rc = adj_freq(fd, num[1], num[0], 0, 0);
				rc = get_clock(fd, &num[4], &num[5]);
				printf("%x:%9u\n", num[2], num[3]);
				printf("%x:%9u\n", num[4], num[5]);
				break;
			case 'd':
				if (count < 2)
					break;
				if (count < 3)
					num[1] = 0;
				if (900000000 <= num[0] && count >= 4)
					rc = set_clock(fd, 1, 0);
				rc = get_clock(fd, &num[2], &num[3]);
				rc = adj_freq(fd, -num[1], -num[0], 0, 0);
				rc = get_clock(fd, &num[4], &num[5]);
				printf("%x:%9u\n", num[2], num[3]);
				printf("%x:%9u\n", num[4], num[5]);
				break;
			case 'a':
				if (count < 2) {
					rc = get_freq(fd, &ptp_drift);
					if (!rc)
						printf("drift = %d\n",
							ptp_drift);
					else
						print_err(rc);
					break;
				}
				if (count < 3)
					printf("[");
				if (count < 3) {
					num[1] = 1000000000;
					printf("%u]\n", num[1]);
				}
				rc = adj_freq(fd, 0, 0, num[0], num[1]);
				print_err(rc);
				break;
			}
		} else if ('d' == line[1]) {
			switch (line[0]) {
			case 'g':
				if (count < 2)
					break;
				rc = get_delays(fd, num[0], &rx_latency,
					&tx_latency, &asym_delay);
				if (!rc)
					printf("%u:%u %u %d\n", num[0],
						rx_latency, tx_latency,
						asym_delay);
				else
					print_err(rc);
				break;
			case 's':
				if (count < 5)
					break;
				rc = set_delays(fd, num[0], num[1], num[2],
					num[3]);
				print_err(rc);
				break;
			case 'p':
				if (count < 2)
					break;
				if (count < 3) {
					rc = get_peer_delay(fd, num[0],
						&asym_delay);
					if (!rc)
						printf("%u:%u\n", num[0],
							asym_delay);
					else
						print_err(rc);
				} else {
					rc = set_peer_delay(fd, num[0],
						num[1]);
					print_err(rc);
				}
				break;
			}
		} else if ('e' == line[1]) {
			switch (line[0]) {
			case 'd':
				/* Requires tsi, gpi, event. */
				if (count < 4)
					break;
				if (count < 7)
					printf("[");

				/* Default is normal mode. */
				if (count < 5) {
					num[3] = 1;
					printf("%u ", num[3]);
				}

				/* Default is interrupt mode. */
				if (count < 6) {
					num[4] = rx_flags;
					printf("0x%x ", num[4]);
				}

				/* Default is have timeout. */
				if (count < 7) {
					num[5] = rx_timeout;
					printf("%u]\n", num[5]);
				}
				clear_rx_event();
				rc = rx_event(fd, num[0], num[1], num[2],
					num[3], num[4], num[5], &rx_unit);
				if (print_err(rc))
					break;
				printf("unit = %d\n", rx_unit);
				first_rx = num[0];
				break;
			case 'e':
				if (count < 2)
					break;
				rc = rx_event(fd, num[0], 0, 0, 0,
					PTP_CMD_CANCEL_OPER, 0, NULL);
				print_err(rc);
				break;
			case 'z':
				rc = rx_event(fd, 10, 0, 0, 0,
					PTP_CMD_CANCEL_OPER, 0, NULL);
				rc = rx_event(fd, 10, 6, 1, 1,
					PTP_CMD_INTR_OPER |
					PTP_CMD_SILENT_OPER, 0, &rx_unit);
				print_err(rc);
				break;
			case 't':
				/* Requires gpi. */
				if (count < 2)
					break;
				clear_rx_event();
				rc = rx_event(fd, 11, num[0], 1, 3, rx_flags,
					rx_timeout, &rx_unit);
				if (print_err(rc))
					break;
				rc = rx_event(fd, 2, num[0], 0, 6, rx_flags,
					rx_timeout, &rx_unit);
				if (print_err(rc))
					break;
				break;
			case 'g':
				if (count < 2)
					break;
				rc = get_rx_event(fd, num[0]);
				print_err(rc);
				break;
			case 'p':
				if (count < 2)
					break;
				rc = poll_rx_event(fd, num[0]);
				print_err(rc);
				break;
			case 'r':
				if (hcount >= 2)
					rx_flags = hex[0];
				else if (count >= 2)
					rx_flags = num[0];
				else {
					printf("rx_flags = 0x%x\n", rx_flags);
					if (rx_flags & PTP_CMD_INTR_OPER)
						printf("intr ");
					if (rx_flags & PTP_CMD_SILENT_OPER)
						printf("silent ");
					if (rx_flags)
						printf("\n");
				}
				break;
			case 'm':
				if (count >= 2) {
					rx_timeout = num[0];
				} else
					printf("rx_timeout = %u\n",
						rx_timeout);
				break;
			case 'a':
				analyze_rx_event();
				break;
			}
		} else if ('o' == line[1]) {
			switch (line[0]) {
			case 'i':
				printf("pulse = %u; cycle = %u; cnt = %u\n",
					tx_pulse * 8, tx_cycle, tx_cnt);
				printf("sec = %u; nsec = %u\n",
					tx_sec, tx_nsec);
				printf("pattern = %x\n", tx_pattern);
				printf("iterate = %u; gap = %u; cnt = %u\n",
					cascade_iterate, cascade_gap,
					cascade_cnt);
				printf("sec = %u; nsec = %u\n",
					cascade_sec, cascade_nsec);
				break;
			case 'n':
				if (count >= 2) {
					tx_nsec = num[0];
				} else
					printf("tx_nsec = %u\n", tx_nsec);
				break;
			case 's':
				if (count >= 2) {
					tx_sec = num[0];
				} else
					printf("tx_sec = %u\n", tx_sec);
				break;
			case 'z':
				if (count < 2)
					break;
				rc = tx_event(fd, 11, 0, 0, tx_pulse,
					tx_cycle, tx_cnt, 0, tx_sec, tx_nsec,
					PTP_CMD_CANCEL_OPER, NULL);
				rc = tx_event(fd, 11, num[0], TRIG_POS_PERIOD,
					20000000 / 8, 1000000000, 0,
					0, 1, 0, PTP_CMD_REL_TIME, NULL);
				print_err(rc);
				break;
			case 'r':
				if (hcount >= 2)
					tx_flags = hex[0];
				else if (count >= 2)
					tx_flags = num[0];
				else {
					printf("tx_flags = 0x%x\n", tx_flags);
					if (tx_flags & PTP_CMD_INTR_OPER)
						printf("intr ");
					if (tx_flags & PTP_CMD_SILENT_OPER)
						printf("silent ");
					if (tx_flags & PTP_CMD_ON_TIME)
						printf("on ");
					if (tx_flags & PTP_CMD_REL_TIME)
						printf("rel ");
					if (tx_flags & PTP_CMD_CLK_OPT)
						printf("clk ");
					if (tx_flags)
						printf("\n");
				}
				break;
			case 't':
				/* Requires tso, gpo, event. */
				if (count < 4)
					break;
				if (count < 11)
					printf("[");
				if (TRIG_REG_OUTPUT == num[2]) {
					if (count < 5) {
						num[3] = tx_pattern;
						printf("%x ", num[3]);
					}
				} else {
					if (count < 5) {
						num[3] = tx_pulse;
						printf("%u ", num[3] * 8);
					} else
						num[3] /= 8;
				}
				if (count < 6) {
					num[4] = tx_cycle;
					printf("%u ", num[4]);
				}
				if (count < 7) {
					num[5] = tx_cnt;
					printf("%u ", num[5]);
				}
				if (cascade) {
					u32 gap;

					if (count < 8) {
						num[6] = cascade_iterate;
						printf("%u ", num[6]);
					}
					if (count < 9)
						num[7] = cascade_gap;
					gap = num[7];
					num[7] = cascade_sec;
					num[8] = cascade_nsec;
					printf("%u:%u ", num[7], num[8]);
					iterate[cascade - 1] = num[6];
					update_cascade_time(num[2], num[3],
						num[4], num[5], gap,
						start, len, cascade,
						&cascade_sec, &cascade_nsec);
					cascade++;
				} else {
					if (count < 8) {
						num[6] = 0;
						printf("%u ", num[6]);
					}
					if (count < 9) {
						num[7] = tx_sec;
						printf("%u", num[7]);
					}
					if (count < 10) {
						num[8] = tx_nsec;
						printf(":%u ", num[8]);
					}
				}

				/* Default is interrupt mode. */
				if (count < 11) {
					num[9] = tx_flags;
					printf("0x%x]\n", num[9]);
				}
				rc = tx_event(fd, num[0], num[1], num[2],
					num[3], num[4], num[5], num[6], num[7],
					num[8], num[9], &tx_unit);
				if (print_err(rc))
					break;
				printf("unit = %d\n", tx_unit);
				break;
			case 'a':
				if (count < 4)
					break;
				if (count < 5)
					num[3] = 0;
				rc = tx_cascade_init(fd, num[0], num[1], num[2],
					num[3], &tx_unit);
				if (print_err(rc))
					break;
				printf("unit = %d\n", tx_unit);
				cascade = 1;
				cascade_sec = tx_sec;
				cascade_nsec = tx_nsec;
				break;
			case 'b':
				if (count < 4)
					break;
				if (count < 6)
					printf("[");
				if (count < 5) {
					num[3] = cascade_cnt;
					printf("%u ", num[3]);
				}
				if (count < 6) {
					num[4] = tx_flags;
					printf("0x%x]\n", num[4]);
				}
				cascade_chk(start, len, stop, iterate,
					cascade - 1, num[3]);
				rc = tx_cascade(fd, num[0], num[1], num[2],
					num[3], num[4]);
				if (print_err(rc))
					break;
				cascade = 0;
				break;
			case 'd':
				if (count < 4)
					break;
				rc = tx_cascade_init(fd, num[0], num[1], num[2],
					PTP_CMD_CANCEL_OPER, &tx_unit);
				if (print_err(rc))
					break;
				printf("unit = %d\n", tx_unit);
				cascade = 0;
				break;
			case 'o':
				if (count < 2)
					break;
				rc = tx_event(fd, num[0], 0, 0, tx_pulse,
					tx_cycle, tx_cnt, 0, tx_sec, tx_nsec,
					PTP_CMD_CANCEL_OPER, NULL);
				print_err(rc);
				break;
			case 'c':
				if (count >= 2) {
					tx_cnt = num[0];
				} else
					printf("tx_cnt = %u\n", tx_cnt);
				break;
			case 'y':
				if (count >= 2) {
					tx_cycle = num[0];
				} else
					printf("tx_cycle = %u\n", tx_cycle);
				break;
			case 'p':
				if (hcount >= 2) {
					tx_pattern = hex[0];
				} else
					printf("tx_pattern = %x\n", tx_pattern);
				break;
			case 'u':
				if (count >= 2) {
					tx_pulse = num[0] / 8;
					if (tx_pulse < 1)
						tx_pulse = 1;
				} else
					printf("tx_pulse = %u\n", tx_pulse * 8);
				break;
			case 'v':
				if (count >= 2) {
					cascade_iterate = num[0];
				} else
					printf("cascade_iterate = %u\n",
						cascade_iterate);
				break;
			case 'w':
				if (count >= 2) {
					cascade_gap = num[0];
				} else
					printf("cascade_gap = %u\n",
						cascade_gap);
				break;
			case 'x':
				if (count >= 2) {
					cascade_cnt = num[0];
				} else
					printf("cascade_cnt = %u\n",
						cascade_cnt);
				break;
			case 'g':
				if (count < 2)
					break;
				rc = tx_get_output(fd, num[0], &tx_unit);
				if (print_err(rc))
					break;
				printf("%04x\n", tx_unit);
				break;
			case 'j':
				rc = tx_event(fd, 0, 1, TRIG_POS_EDGE,
					tx_pulse, tx_cycle,
					tx_cnt, 0, tx_sec, tx_nsec, tx_flags,
					NULL);
				print_err(rc);
				rc = tx_event(fd, 1, 1, TRIG_NEG_EDGE,
					tx_pulse, tx_cycle,
					tx_cnt, 0, tx_sec,
					tx_nsec + 8 + cascade_gap, tx_flags,
					NULL);
				print_err(rc);
				break;
			case 'k':
				rc = tx_event(fd, 0, 1, TRIG_POS_PERIOD,
					tx_pulse, tx_cycle,
					tx_cnt, 0, tx_sec, tx_nsec, tx_flags,
					NULL);
				print_err(rc);
				rc = tx_event(fd, 1, 1, TRIG_POS_EDGE,
					tx_pulse, tx_cycle,
					tx_cnt, 0, tx_sec, 
					tx_nsec + tx_cycle + cascade_gap,
					tx_flags, NULL);
				print_err(rc);
				break;
			case 'l':
				rc = tx_event(fd, 0, 1, TRIG_POS_PERIOD,
					tx_pulse, tx_cycle,
					tx_cnt, 0, tx_sec, tx_nsec, tx_flags,
					NULL);
				print_err(rc);
				rc = tx_event(fd, 1, 1, TRIG_POS_EDGE,
					tx_pulse, tx_cycle,
					tx_cnt, 0, tx_sec,
					tx_nsec + tx_cycle + cascade_gap,
					tx_flags, NULL);
				print_err(rc);
				break;
			}
#if 0
		} else if ('m' == line[1]) {
			send_ptp_msg(line, hcount, hex, count, num);
#endif
		} else if ('t' == line[1]) {
			int port;
			int i;

			switch (line[0]) {
			case 'g':
				if (hcount < 2)
					hex[0] = 0;
				if (hcount < 3)
					hex[1] = SYNC_MSG;
				if (hcount < 4)
					hex[2] = 0;
				if (hcount < 5)
					hex[3] = 0xffff;
				if (hcount < 6)
					hex[4] = 0x1234;
				if (hcount <= 2)
					tsm_cmd_get_time(hex[0]);
				port = hex[2] + 1;
				rc = 0;
#if 0
				if (!hex[0]) {
					rc = send_ptp_event(hex[1], hex[2],
						hex[3]);
					if (rc) {
						printf("not applicable: %x\n",
							hex[1]);
						break;
					}
					port = hex[2];
					hex[4] = htons(hex[4] & 0xffff);
					if (port > (1 << ptp_ports) - 1 ||
							!port)
						port = (1 << ptp_ports) - 1;
				}
#endif
				for (i = 0; i < ptp_ports; i++) {
					if (!(port & (1 << i)))
						continue;
					rc = get_timestamp(fd, hex[1], i,
						hex[3], (u8 *) &hex[4], hex[0],
						&cascade_sec, &cascade_nsec);
					if (rc)
						continue;
					printf("%u=%x:%9u\n", i,
						cascade_sec, cascade_nsec);
				}
				break;
			case 'p':
				tsm_cmd_get_gps();
				break;
			}
		} else if ('b' == line[1]) {
			switch (line[0]) {
			case 'g':
				if (count < 2)
					num[0] = SYNC_MSG;
				if (count < 3)
					num[1] = 0;
				tsm_cmd_get(num[0], num[1]);
				break;
			}
		} else
		switch (line[0]) {
		case 'a':
			if (count >= 2) {
				ptp_alternate = num[0];
				set_hw_alternate(fd, ptp_alternate);
			} else
				printf("alternate = %d\n", ptp_alternate);
			break;
		case 'c':
			if (count >= 2) {
				ptp_check = num[0];
				set_hw_domain_check(fd, ptp_check);
			} else
				printf("domain check = %d\n", ptp_check);
			break;
		case 'd':
			if (count >= 2) {
				ptp_domain = (u8) num[0];
				set_hw_domain(fd, ptp_domain);
			} else
				printf("domain = %u\n", ptp_domain);
			break;
		case 'e':
			if (count >= 2) {
				ptp_p2p = num[0];
				set_hw_p2p(fd, ptp_p2p);
			} else
				printf("p2p = %d\n", ptp_p2p);
			break;
		case 'm':
			if (count >= 2) {
				ptp_master = num[0];
				set_hw_master(fd, ptp_master);
			} else
				printf("master = %d\n", ptp_master);
			break;
		case 'p':
			if (count >= 2) {
				ptp_2step = num[0];
				set_hw_2_step(fd, ptp_2step);
			} else
				printf("2-step = %d\n", ptp_2step);
			break;
		case 'u':
			if (count >= 2) {
				ptp_unicast = num[0];
				set_hw_unicast(fd, ptp_unicast);
			} else
				printf("unicast = %d\n", ptp_unicast);
			break;
		case 'r':
			if (hcount < 2)
				break;
			if (hcount < 3)
				hex[1] = 2;
			if ('1' == line[1])
				hex[1] = 1;
			else if ('2' == line[1])
				hex[1] = 2;
			else if ('4' == line[1])
				hex[1] = 4;
			hex[2] = hex[1];
			rc = get_reg(fd, hex[2], hex[0], &hex[1]);
			if (!rc) {
				if (4 == hex[2])
					printf("%08x\n", hex[1]);
				else if (1 == hex[2])
					printf("%02x\n", hex[1]);
				else
					printf("%04x\n", hex[1]);
			} else
				print_err(rc);
			break;
		case 'w':
			if (hcount < 3)
				break;
			if (hcount < 4)
				hex[2] = 2;
			if ('1' == line[1])
				hex[2] = 1;
			else if ('2' == line[1])
				hex[2] = 2;
			else if ('4' == line[1])
				hex[2] = 4;
			rc = set_reg(fd, hex[2], hex[0], hex[1]);
			break;
		case 'h':
			printf("\tde tsi gpi event [total] [flags] [timeout]\n");
			printf("\tee tsi\t\tcancel input unit\n");
			printf("\tge tsi\t\tget event from unit\n");
			printf("\tpe tsi\t\tpoll event from unit\n");
			printf("\tme [timeout]\n");
			printf("\tre [rx_flags]\n");
			printf("\tte gpi\n");
			printf("\tae\t\tanalyze events\n");
			printf("\tze\t\trestart second tracking\n");
			printf("\n");
			printf("\tto tso gpo event\n");
			printf("\t\t[pulse] [cycle] [cnt] ");
			printf("[iterate] [sec] [nsec] [flags]\n");
			printf("\too tso\t\tcancel output unit\n");
			printf("\tao tso gpo total [flags]\tcascade init\n");
			printf("\tbo tso gpo total [cnt] [flags]");
			printf("\tcascade start\n");
			printf("\tdo tso gpo total\t\tcancel cascade output\n");
			printf("\tzo gpo\n");
			printf("\tco [tx_cnt]\n");
			printf("\tyo [tx_cycle]\n");
			printf("\tpo [tx_pattern]\n");
			printf("\tuo [tx_pulse]\n");
			printf("\tso [tx_sec]\n");
			printf("\tno [tx_nsec]\n");
			printf("\tvo [cascade_iterate]\n");
			printf("\two [cascade_gap]\n");
			printf("\txo [cascade_cnt]\n");
			printf("\tro [tx_flags]\n");
			printf("\tio\t\toutput parameter info\n");
			printf("\tirig code\tIRIG sample output on GPIO 1\n");
			printf("\tgo gpo\t\tunits holding GPIO high\n");
			printf("\n");
			printf("\tgc\n");
			printf("\tsc sec [nsec]\n");
			printf("\tic nsec [sec]\n");
			printf("\tdc nsec [sec]\n");
			printf("\tac drift [interval]\n");
			printf("\n");
			printf("\tgd port\n");
			printf("\tsd port rx tx asym\n");
			printf("\tpd port [delay]\n");
			printf("\n");
			printf("\tgb msg port\n");
			printf("\tgt [timestamp] [msg] [dst_port] [seqid] [mac]\n");
			printf("\tpt gps\n");
			printf("\n");
			printf("\tsci [clockIdentity]\n");
			printf("\tmci [clockIdentity]\n");
			printf("\n");
			printf("\td [domain]\n");
			printf("\ta [0,1]\t\talternate\n");
			printf("\tc [0,1]\t\tdomain check\n");
			printf("\te [0,1]\t\tp2p\n");
			printf("\tm [0,1]\t\tmaster\n");
			printf("\tp [0,1]\t\t2-step\n");
			printf("\tu [0,1]\t\tunicast\n");
			printf("\thas [0,1]\t802.1as\n");
			printf("\thds [0,1]\tdrop Sync/Delay_Req\n");
			printf("\thuc [0,1]\tUDP checksum\n");
			printf("\thda [0,1]\tdelay assoc\n");
			printf("\thpda [0,1]\tpdelay assoc\n");
			printf("\thsa [0,1]\tsync assoc\n");
			printf("\thp [0,1]\tmessage priority\n");
			printf("\n");
			printf("\tr[1|2|4] reg [1|2|4]\n");
			printf("\tw[1|2|4] reg val [1|2|4]\n");
			printf("\tz [bit]\t\treset hardware\n");
			break;
		case 'z':
			if (count < 2)
				num[0] = 0;
			rc = reset_hw(num[0]);
			print_err(rc);
			get_global_cfg(fd, &ptp_master, &ptp_2step, &ptp_p2p,
				&ptp_as, &ptp_unicast, &ptp_alternate,
				&ptp_csum, &ptp_check, &ptp_delay_assoc,
				&ptp_pdelay_assoc, &ptp_sync_assoc,
				&ptp_drop_sync, &ptp_priority, &ptp_domain,
				&ptp_access_delay, &ptp_started);
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
}

struct task_param {
	pthread_cond_t *req_cond;
	pthread_cond_t *resp_cond;
	pthread_mutex_t *resp_mutex;
	int pid;
	int stop;
};

static void proc_tsm_resp(u8 data[], int len)
{
	switch (data[0] & 0xf0) {
	case TSM_CMD_GET_GPS_TS:
		if (data[0] & TSM_CMD_GET_TIME_RESP) {
			struct tsm_get_gps *tsm =
				(struct tsm_get_gps *) data;

			printf("%04x=%x:%9u\n", ntohs(tsm->seqid),
				ntohl(tsm->sec), ntohl(tsm->nsec));
		}
		break;
	case TSM_CMD_DB_GET_TIME:
		if (data[0] & TSM_CMD_GET_TIME_RESP) {
			struct tsm_get_time *tsm =
				(struct tsm_get_time *) data;

			printf("%x:%9u\n", ntohl(tsm->sec), ntohl(tsm->nsec));
		}
		break;
	case TSM_CMD_DB_GET:
		if (data[0] & TSM_CMD_RESP) {
			struct tsm_db *tsm =
				(struct tsm_db *) data;

			printf("%d %04x %02x:%02x %x:%9u %9u\n",
				tsm->index, ntohs(tsm->seqid),
				tsm->mac[0], tsm->mac[1],
				ntohl(tsm->cur_sec), ntohl(tsm->cur_nsec),
				ntohl(tsm->timestamp));
		}
		break;
	case 0xF0:
		break;
	default:
		printf("%x\n", data[0]);
	}
}  /* proc_tsm_resp */

#if 0
static void proc_eth_msg(u8 *data, size_t len)
{
	int i;
	u8 cmd = *data;
	struct ptp_msg *msg = (struct ptp_msg *) &data[4];

	if (cmd != (PTP_CMD_GET_MSG | PTP_CMD_RESP)) {
		printf("%x is not right\n", cmd);
		return;
	}
	i = ntohs(msg->hdr.messageLength) + 4;
	if (len < i) {
		printf("%d is not correct\n", len);
		return;
	}
	if (ptp_msg_count > 0 &&
			(DELAY_REQ_MSG == msg->hdr.messageType ||
			PDELAY_REQ_MSG == msg->hdr.messageType)) {
		int count;
		u16 seqid = ntohs(msg->hdr.sequenceId) - ptp_msg_count + 1;

		if (ptp_msg_count > 2)
			seqid++;
		for (count = 0; count < ptp_msg_count; count++) {
			msg->hdr.sequenceId = htons(seqid);
			resp_msg(msg);
			seqid++;
		}
	}
}
#endif

void *notification_task(void *param)
{
	int len;
	u8 data[MAX_REQUEST_SIZE];
	struct task_param *task = param;

	task->stop = 0;
	do {
		len = tsm_recv(&dev[1], data, MAX_REQUEST_SIZE);
		if (len > 0) {
			if ((data[0] & 0x0f) == PTP_CMD_RESP) {
				switch (data[0] & 0xf0) {
				case PTP_CMD_GET_EVENT:
					if (!proc_rx_event(data, len))
						setup_rx_event(data, len);
					break;
				case PTP_CMD_GET_OUTPUT:
					proc_tx_event(data, len);
					break;
#if 0
				case PTP_CMD_GET_MSG:
					proc_eth_msg(data, len);
					break;
#endif
				}
			}
		}
	} while (!task->stop);
	return NULL;
}

void *tsm_task(void *param)
{
	int len;
	u8 data[MAX_REQUEST_SIZE];
	struct task_param *task = param;

	task->stop = 0;
	do {
		len = tsm_recv(&dev[0], data, MAX_REQUEST_SIZE);
		if (len > 0) {
			if (waiting_for_resp) {
				waiting_for_resp--;
				proc_tsm_resp(data, len);
			}
		}
	} while (!task->stop);
	return NULL;
}

int main(void)
{
	pthread_t tid[2];
	void *status;
	struct task_param param[2];
	int id;
	pthread_cond_t req_cond = PTHREAD_COND_INITIALIZER;
	pthread_cond_t resp_cond = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t resp_mutex = PTHREAD_MUTEX_INITIALIZER;

	if (tsm_init()) {
		printf("Cannot access device\n");
		return 1;
	}

	id = getpid();

	param[0].req_cond = &req_cond;
	param[0].resp_cond = &resp_cond;
	param[0].resp_mutex = &resp_mutex;
	param[0].pid = id;
	param[1].req_cond = &req_cond;
	param[1].resp_cond = &resp_cond;
	param[1].resp_mutex = &resp_mutex;
	param[1].pid = id;

	pthread_create(&tid[0], NULL, tsm_task, &param[0]);
	pthread_create(&tid[1], NULL, notification_task, &param[1]);

	masterClockIdentity.addr[0] = 0x00;
	masterClockIdentity.addr[1] = 0x22;
	masterClockIdentity.addr[2] = 0x19;
	masterClockIdentity.addr[3] = 0xFF;
	masterClockIdentity.addr[4] = 0xFE;
	masterClockIdentity.addr[5] = 0xFA;
	masterClockIdentity.addr[6] = 0x23;
	masterClockIdentity.addr[7] = 0x88;

	selfClockIdentity.addr[0] = 0x00;
	selfClockIdentity.addr[1] = 0x10;
	selfClockIdentity.addr[2] = 0xA1;
	selfClockIdentity.addr[3] = 0xFF;
	selfClockIdentity.addr[4] = 0xFE;
	selfClockIdentity.addr[5] = 0x83;
	selfClockIdentity.addr[6] = 0x63;
	selfClockIdentity.addr[7] = 0x88;
	get_clock_ident(&dev[0].fd, 0, &selfClockIdentity);

	get_cmd(stdin);
	param[0].stop = 1;
	param[1].stop = 1;
	tsm_exit();

	pthread_join(tid[0], &status);
	pthread_join(tid[1], &status);
	tsm_cleanup();
	return 0;
}
