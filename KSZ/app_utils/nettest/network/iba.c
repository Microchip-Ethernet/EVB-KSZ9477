#include "wnp.h"
#include "unpifi.h"
#include "datatype.h"

#ifndef _SYS_SOCKET_H
#include <sys\timeb.h>
#include <process.h>
#include "ip_icmp.h"

#else
#include <net/if.h>
#include <linux/sockios.h>
#include <linux/if_packet.h>
#define ARPHRD_ETHER 	1		/* Ethernet 10Mbps		*/
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <sys/timeb.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "wrapthread.h"
#ifndef IPV6_TCLASS
#define IPV6_TCLASS		67
#endif

#define _PATH_PROCNET_IFINET6           "/proc/net/if_inet6"

struct ipv6_info {
	char devname[20];
	struct sockaddr_in6 addr;
	int plen;
	int scope;
	int if_idx;
};

#define _PATH_SYSNET_DEV		"/sys/class/net/"

#define NETDEV_ADDRESS			"address"
#define NETDEV_FLAGS			"flags"
#define NETDEV_IFINDEX			"ifindex"
#define NETDEV_OPERSTATE		"operstate"

#endif


typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;


#if defined(_MSC_VER)
#include <packon.h>
#define __packed;
#endif

#if defined(__GNUC__)
#ifndef __packed
#define __packed __attribute__((packed))
#endif
#endif

#define NUM_OF_PORTS			4


pthread_mutex_t disp_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sec_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tx_mutex = PTHREAD_MUTEX_INITIALIZER;

void pthread_cond_init_(pthread_cond_t *cond)
{
	pthread_cond_init(cond, NULL);
}

void pthread_mutex_init_(pthread_mutex_t *mutex)
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutex_init(mutex, &attr);
}

struct thread_info {
	pthread_cond_t  cond;
	pthread_mutex_t mutex;
};

int rx_wait[NUM_OF_PORTS];
struct thread_info rx_thread[NUM_OF_PORTS];
struct thread_info tx_done_thread;
struct thread_info tx_job_thread;
struct thread_info tx_next_thread;
struct thread_info tx_periodic_thread;
struct thread_info rx_resp_thread;
int rx_resp_cnt = 0;

static void signal_update(struct thread_info *pthread, int *signal, int val)
{
	Pthread_mutex_lock(&pthread->mutex);
	if (signal)
		*signal = val;
	pthread_cond_signal(&pthread->cond);
	Pthread_mutex_unlock(&pthread->mutex);
}

static void signal_wait_(struct thread_info *pthread, int cond,
	struct timespec *ts)
{
	int n;

	Pthread_mutex_lock(&pthread->mutex);
	if (!cond)
		n = pthread_cond_timedwait(&pthread->cond,
			&pthread->mutex, ts);
	Pthread_mutex_unlock(&pthread->mutex);
}

static void signal_long_wait(struct thread_info *pthread, int cond)
{
	struct timeb tb;
	struct timespec ts;
	int n;

	ftime(&tb);
	ts.tv_sec = tb.time;
	ts.tv_nsec = (tb.millitm + 100 - 10) * 1000 * 1000;
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}
	ts.tv_sec += 2;

	signal_wait_(pthread, cond, &ts);
}

static void signal_wait(struct thread_info *pthread, int cond)
{
	struct timeb tb;
	struct timespec ts;
	int n;

	ftime(&tb);
	ts.tv_sec = tb.time;
	ts.tv_nsec = (tb.millitm + 10) * 1000 * 1000;
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}

	signal_wait_(pthread, cond, &ts);
}

static void signal_init(struct thread_info *pthread)
{
	pthread_cond_init_(&pthread->cond);
	pthread_mutex_init_(&pthread->mutex);
}

int dbg_rcv = 0;

#if 1
#define DBG_IBA
#endif

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
#define IBA_FORMAT_KSZ93XX	0x9300

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
	u16 tag_type;
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	u8 *buf;
	u8 *packet;
	struct iba_frame *frame;
	struct iba_cmd *cmds;
	struct iba_cmd *regs;
	u8 id;
	u8 seqid;
	u8 respid;
	int cnt;
	u32 cfg;

	/* Used for putting in commands. */
	u32 *data;
	void *fptr;
	int index;
	int len;
};

#define ETH_P_IBA			IBA_TAG_TYPE

u16 iba_ksz_format = IBA_FORMAT_KSZ98XX;

static void prepare_iba(struct ksz_iba_info *iba, u8 *dst, u8 *src)
{
	if (iba->dst != dst)
		memcpy(iba->dst, dst, ETH_ALEN);
	if (iba->src != src)
		memcpy(iba->src, src, ETH_ALEN);
	memcpy(iba->packet, iba->dst, ETH_ALEN);
	memcpy(&iba->packet[ETH_ALEN], iba->src, ETH_ALEN);

	iba->frame->tag.type = htons(iba->tag_type);
	iba->frame->tag.prio = 0;
	iba->frame->tag.cfi = 0;
	iba->frame->tag.mode = 1;
	iba->frame->format.format = htons(iba_ksz_format);
	iba->frame->format.reserved = 0;

	iba->cmds[0].cmd = 0;
}  /* prepare_iba */

static void *iba_command(void *frame, int *size, u32 cmd, int cnt, u32 *data)
{
	struct iba_cmd *iba = frame;
	int i;
	int len = 4;
	int final_len = *size + sizeof(u32) * cnt + 8;

	if (final_len > IBA_LEN_MAX && cmd) {
		cnt = (IBA_LEN_MAX - *size - 8) / (int) sizeof(u32);
		if (cnt > 0)
			data[0] = cnt - 1;
		else
			cmd = 0;
	}

	iba->cmd = htonl(cmd);
	for (i = 0; i < cnt; i++) {
		iba->data[i] = htonl(data[i]);
		len += 4;
	}
	frame = &iba->data[i];
	*size += len;
	return frame;
}  /* iba_command */

static void *iba_pre_cmd(struct ksz_iba_info *info, u16 code)
{
	struct iba_frame *iba = info->frame;

	info->index = 0;
	info->len = sizeof(struct iba_frame) - sizeof(struct iba_cmd) +
		ETH_ALEN * 2;
	iba->code = htons(code);
	return &iba->cmd;
}  /* iba_pre_cmd */

static u32 iba_get_val(u32 size, u32 val)
{
	int shift;

	switch (size) {
	case IBA_CMD_32:
		break;
	case IBA_CMD_16:
		val >>= 16;
		break;
	case IBA_CMD_16_M:
		val >>= 8;
		val &= 0xffff;
		break;
	case IBA_CMD_16_H:
		val &= 0xffff;
		break;
	case IBA_CMD_24:
		val >>= 8;
		break;
	case IBA_CMD_24_H:
		val &= 0xffffff;
		break;
	default:
		switch (size) {
		case IBA_CMD_BYTE_0:
			shift = 3;
			break;
		case IBA_CMD_BYTE_1:
			shift = 2;
			break;
		case IBA_CMD_BYTE_2:
			shift = 1;
			break;
		default:
			shift = 0;
			break;
		}
		val >>= shift * 8;
		val &= 0xff;
	}
	return val;
}  /* iba_get_val */

static u32 iba_set_size(u32 addr, u32 size)
{
	switch (size) {
	case IBA_CMD_8:
		size = IBA_CMD_8 >> (addr & 3);
		break;
	case IBA_CMD_16:
		if (addr & 2)
			size = IBA_CMD_16 >> 2;
		else if (addr & 1)
			size = IBA_CMD_16 >> 1;
		break;
	case IBA_CMD_24:
		size = IBA_CMD_24 >> (addr & 1);
		break;
	}
	return size;
}  /* iba_set_size */

static u32 iba_set_val(u32 size, u32 addr, u32 val)
{
	switch (size) {
	case IBA_CMD_8:
		val &= 0xff;
		val <<= (3 - (addr & 3)) * 8;
		break;
	case IBA_CMD_16:
		val &= 0xffff;
		if (!(addr & 2)) {
			if (addr & 1)
				val <<= 1 * 8;
			else
				val <<= 2 * 8;
		}
		break;
	case IBA_CMD_24:
		val &= 0xffffff;
		val <<= (1 - (addr & 1)) * 8;
		break;
	}
	return val;
}  /* iba_set_val */

static void *iba_cmd_data(struct ksz_iba_info *info, u32 cmd, u32 size,
	u32 addr)
{
	int cnt = 1;
	int shift = IBA_CMD_S;
	struct iba_frame *iba = info->frame;

	if (iba->code == htons(IBA_CODE_BURST)) {
		cnt = info->data[0] + 1;
		shift = IBA_BURST_S;
	} else {
		/* write can be 8-bit, 16-bit, or 32-bit. */
		if (IBA_CMD_READ != cmd) {
			info->data[0] = iba_set_val(size, addr, info->data[0]);
		}
		size = iba_set_size(addr, size);
	}
	cmd <<= shift;
	cmd |= size;
	cmd |= addr & IBA_CMD_ADDR_M;
	info->cmds[info->index].data[0] = info->data[0];
	info->cmds[info->index++].cmd = cmd;
	info->fptr = iba_command(info->fptr, &info->len, cmd, cnt, info->data);
	if (info->len + 4 >= IBA_LEN_MAX && iba->code == htons(IBA_CODE_BURST))
		info->cmds[info->index - 1].data[0] = info->data[0];
	return info->fptr;
}  /* iba_cmd_data */

static void *iba_post_cmd(struct ksz_iba_info *info)
{
	struct iba_frame *iba = info->frame;

	info->cmds[info->index++].cmd = 0;
	info->fptr = iba_command(info->fptr, &info->len, 0, 0, NULL);
	iba->tag.seqid = ++info->seqid;
	iba->length = htons(info->len);
	return info->fptr;
}  /* iba_post_cmd */

static int iba_xmit(struct ksz_iba_info *info);

/**
 * iba_r_pre - IBA register read pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for register read operation.
 *
 * Return the IBA frame pointer.
 */
static void *iba_r_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;

	info->data[0] = 0;
	info->fptr = iba_cmd_data(info, IBA_CMD_READ, data[0], data[1]);
	return info->fptr;
}  /* iba_r_pre */

/**
 * iba_r_post - IBA register read post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA register read operation.
 *
 * Return number of registers read.
 */
static int iba_r_post(struct ksz_iba_info *info, void *out, void *obj)
{
	u32 *data = out;
	int i = 0;

	while (info->regs[i].cmd != (u32) -1) {
		if (IBA_CMD_READ == (info->regs[i].cmd >> IBA_CMD_S)) {
			u32 reg = (info->regs[i].cmd & IBA_CMD_ADDR_M);
			u32 size = (info->regs[i].cmd & IBA_CMD_32);
			int j = 0;

			while (data[j] != -1) {
				if (reg == data[j] &&
				    (data[j + 1] & 0xffff0000) == 0xdead0000) {
					data[j + 1] = iba_get_val(size,
						info->regs[i].data[0]);
					break;
				}
				j += 2;
			}
		}
		i++;
	}
	return i;
}  /* iba_r_post */

/**
 * iba_w_pre - IBA register write pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for register write operation.
 *
 * Return the IBA frame pointer.
 */
static void *iba_w_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;

	info->data[0] = data[2];
	info->fptr = iba_cmd_data(info, IBA_CMD_WRITE, data[0], data[1]);
	return info->fptr;
}  /* iba_w_pre */

static void *iba_w_b_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;

	info->data[0] = 0;
	info->fptr = iba_cmd_data(info, IBA_CMD_READ, data[0], data[1]);
	info->data[0] = data[2];
	info->fptr = iba_cmd_data(info, data[3], data[0], data[1]);
	return info->fptr;
}  /* iba_w_b_pre */

static void *iba_wait_on_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;

	info->data[0] = data[2];
	info->fptr = iba_cmd_data(info, data[3], data[0], data[1]);
	return info->fptr;
}  /* iba_wait_on_pre */

/**
 * iba_reqs - IBA register request
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 * @func:	The pre-processing routines.
 * @post:	The post-processing function.
 *
 * This function sends a request with many pre-processing routines to IBA and
 * waits for a response.
 *
 */
static int iba_reqs(struct ksz_iba_info *info, void **in, void *out, void *obj,
	void **func,
	int (*post)(struct ksz_iba_info *info, void *out, void *obj))
{
	int rc;
	unsigned long wait;
	u16 code = IBA_CODE_NORMAL;
	void *(*prepare)(struct ksz_iba_info *info, void *in, void *obj);

	memset(info->data, 0, sizeof(u32) * IBA_BURST_CNT_MAX);
	info->fptr = iba_pre_cmd(info, code);

	do {
		prepare = *func;
		info->fptr = prepare(info, *in, obj);
		++func;
		++in;
	} while (*func);

	info->fptr = iba_post_cmd(info);
	info->regs[0].cmd = (u32) -1;
	rc = iba_xmit(info);
	signal_wait(&rx_resp_thread, rx_resp_cnt);

	rc = 1;
	if (post)
		rc = post(info, out, obj);
	return rc * 4;
}  /* iba_reqs */

/**
 * iba_req - IBA basic register request
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 * @prepare:	The pre-processing routine.
 * @post:	The post-processing function.
 *
 * This function sends a request to IBA and waits for a response.
 *
 * Return number of bytes read.
 */
static int iba_req(struct ksz_iba_info *info, void *in, void *out, void *obj,
	void *(*prepare)(struct ksz_iba_info *info, void *in, void *obj),
	int (*post)(struct ksz_iba_info *info, void *out, void *obj))
{
	int rc;
	void *func[2];
	void *data_in[1];
	int i = 0;

	data_in[i] = in;
	func[i++] = prepare;

	func[i] = NULL;
	rc = iba_reqs(info, data_in, out, obj, func, post);
	return rc;
}  /* iba_req */

/**
 * iba_r - IBA basic register read
 * @info:	The IBA instance.
 * @reg:	The register to read.
 * @size:	The data size.
 *
 * This function reads a register through IBA.
 */
static u32 iba_r(struct ksz_iba_info *info, unsigned reg, u32 size)
{
	u32 data[4];
	int rc;

	data[0] = size;
	data[1] = reg;
	data[2] = 0xdeadbeaf;
	data[3] = -1;
	rc = iba_req(info, data, data + 1, NULL, iba_r_pre, iba_r_post);
	return data[2];
}  /* iba_r */

/**
 * iba_r8 - IBA 8-bit register read
 * @info:	The IBA instance.
 * @reg:	The register to read.
 *
 * This function reads a 8-bit register through IBA.
 */
static u8 iba_r8(struct ksz_iba_info *iba, unsigned reg)
{
	return (u8) iba_r(iba, reg, IBA_CMD_8);
}  /* iba_r8 */

/**
 * iba_r16 - IBA 16-bit register read
 * @info:	The IBA instance.
 * @reg:	The register to read.
 *
 * This function reads a 16-bit register through IBA.
 */
static u16 iba_r16(struct ksz_iba_info *iba, unsigned reg)
{
	return (u16) iba_r(iba, reg, IBA_CMD_16);
}  /* iba_r16 */

/**
 * iba_r24 - IBA 24-bit register read
 * @info:	The IBA instance.
 * @reg:	The register to read.
 *
 * This function reads a 24-bit register through IBA.
 */
static u32 iba_r24(struct ksz_iba_info *iba, unsigned reg)
{
	return iba_r(iba, reg, IBA_CMD_24);
}  /* iba_r24 */

/**
 * iba_r32 - IBA 32-bit register read
 * @info:	The IBA instance.
 * @reg:	The register to read.
 *
 * This function reads a 32-bit register through IBA.
 */
static u32 iba_r32(struct ksz_iba_info *iba, unsigned reg)
{
	return iba_r(iba, reg, IBA_CMD_32);
}  /* iba_r32 */

/**
 * iba_w - IBA basic register write
 * @info:	The IBA instance.
 * @reg:	The register to write.
 * @val:	The value to write.
 * @size:	The data size.
 *
 * This function writes a register through IBA.
 */
static void iba_w(struct ksz_iba_info *info, unsigned reg, unsigned val,
	u32 size)
{
	u32 data[3];
	int rc;

	data[0] = size;
	data[1] = reg;
	data[2] = val;
	rc = iba_req(info, data, NULL, NULL, iba_w_pre, NULL);
}  /* iba_w */

/**
 * iba_w8 - IBA 8-bit register write
 * @info:	The IBA instance.
 * @reg:	The register to write.
 * @val:	The value to write.
 *
 * This function writes a 8-bit register through IBA.
 */
static void iba_w8(struct ksz_iba_info *iba, unsigned reg, unsigned val)
{
	iba_w(iba, reg, val, IBA_CMD_8);
}  /* iba_w8 */

/**
 * iba_w16 - IBA 16-bit register write
 * @info:	The IBA instance.
 * @reg:	The register to write.
 * @val:	The value to write.
 *
 * This function writes a 16-bit register through IBA.
 */
static void iba_w16(struct ksz_iba_info *iba, unsigned reg, unsigned val)
{
	iba_w(iba, reg, val, IBA_CMD_16);
}  /* iba_w16 */

/**
 * iba_w24 - IBA 24-bit register write
 * @info:	The IBA instance.
 * @reg:	The register to write.
 * @val:	The value to write.
 *
 * This function writes a 24-bit register through IBA.
 */
static void iba_w24(struct ksz_iba_info *iba, unsigned reg, unsigned val)
{
	iba_w(iba, reg, val, IBA_CMD_24);
}  /* iba_w24 */

/**
 * iba_w32 - IBA 32-bit register write
 * @info:	The IBA instance.
 * @reg:	The register to write.
 * @val:	The value to write.
 *
 * This function writes a 32-bit register through IBA.
 */
static void iba_w32(struct ksz_iba_info *iba, unsigned reg, unsigned val)
{
	iba_w(iba, reg, val, IBA_CMD_32);
}  /* iba_w32 */

static void iba_w_b(struct ksz_iba_info *info, unsigned reg, unsigned val,
	u32 cmd, u32 size)
{
	u32 data[4];
	int rc;

	data[0] = size;
	data[1] = reg;
	data[2] = val;
	data[3] = cmd;
	rc = iba_req(info, data, NULL, NULL, iba_w_b_pre, NULL);
}  /* iba_w_b */

static void iba_wait_on(struct ksz_iba_info *info, unsigned reg, unsigned val,
	u32 cmd, u32 size)
{
	u32 data[4];
	int rc;

	data[0] = size;
	data[1] = reg;
	data[2] = val;
	data[3] = cmd;
	rc = iba_req(info, data, NULL, NULL, iba_wait_on_pre, NULL);
}  /* iba_wait_on */

#define iba_s0_1(iba, reg, val)		iba_w_b(iba, reg, val, \
	IBA_CMD_WRITE_0, IBA_CMD_8)
#define iba_s0_2(iba, reg, val)		iba_w_b(iba, reg, val, \
	IBA_CMD_WRITE_0, IBA_CMD_16)
#define iba_s0_3(iba, reg, val)		iba_w_b(iba, reg, val, \
	IBA_CMD_WRITE_0, IBA_CMD_24)
#define iba_s0_4(iba, reg, val)		iba_w_b(iba, reg, val, \
	IBA_CMD_WRITE_0, IBA_CMD_32)
#define iba_s1_1(iba, reg, val)		iba_w_b(iba, reg, val, \
	IBA_CMD_WRITE_1, IBA_CMD_8)
#define iba_s1_2(iba, reg, val)		iba_w_b(iba, reg, val, \
	IBA_CMD_WRITE_1, IBA_CMD_16)
#define iba_s1_3(iba, reg, val)		iba_w_b(iba, reg, val, \
	IBA_CMD_WRITE_1, IBA_CMD_24)
#define iba_s1_4(iba, reg, val)		iba_w_b(iba, reg, val, \
	IBA_CMD_WRITE_1, IBA_CMD_32)
#define iba_w0_1(iba, reg, val)		iba_wait_on(iba, reg, val, \
	IBA_CMD_WAIT_ON_0, IBA_CMD_8)
#define iba_w0_2(iba, reg, val)		iba_wait_on(iba, reg, val, \
	IBA_CMD_WAIT_ON_0, IBA_CMD_16)
#define iba_w0_3(iba, reg, val)		iba_wait_on(iba, reg, val, \
	IBA_CMD_WAIT_ON_0, IBA_CMD_24)
#define iba_w0_4(iba, reg, val)		iba_wait_on(iba, reg, val, \
	IBA_CMD_WAIT_ON_0, IBA_CMD_32)
#define iba_w1_1(iba, reg, val)		iba_wait_on(iba, reg, val, \
	IBA_CMD_WAIT_ON_1, IBA_CMD_8)
#define iba_w1_2(iba, reg, val)		iba_wait_on(iba, reg, val, \
	IBA_CMD_WAIT_ON_1, IBA_CMD_16)
#define iba_w1_3(iba, reg, val)		iba_wait_on(iba, reg, val, \
	IBA_CMD_WAIT_ON_1, IBA_CMD_24)
#define iba_w1_4(iba, reg, val)		iba_wait_on(iba, reg, val, \
	IBA_CMD_WAIT_ON_1, IBA_CMD_32)

/**
 * iba_get_pre - IBA burst read pre-processing
 * @info:	The IBA instance.
 * @cnt:	The buffer count.
 * @buf:	The buffer.
 *
 * This routine prepares IBA for burst read operation.
 */
static void iba_get_pre(u32 *data, int cnt, char *buf)
{}

/**
 * iba_get_post - IBA burst read post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 * @b:		Endian indication.
 *
 * This helper function retrieves the result of IBA burst read operation.
 *
 * Return number of registers read.
 */
static int iba_get_post(struct ksz_iba_info *info, void *out, void *obj, int b)
{
	u32 *ptr = (u32 *) out;
	int i = 0;

	while (info->regs[i].cmd != (u32) -1) {
		*ptr = iba_get_val((info->regs[i].cmd & IBA_CMD_32),
			info->regs[i].data[0]);
		if (b)
			*ptr = htonl(*ptr);
		ptr++;
		i++;
	}
	return i;
}  /* iba_get_post */

/**
 * iba_get_post_be - IBA big-endian burst read post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA big-endian burst read operation.
 *
 * Return number of registers read.
 */
static int iba_get_post_be(struct ksz_iba_info *info, void *out, void *obj)
{
	return iba_get_post(info, out, obj, 1);
}  /* iba_get_post_be */

/**
 * iba_get_post_le - IBA little-endian burst read post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA little-endian burst read
 * operation.
 *
 * Return number of registers read.
 */
static int iba_get_post_le(struct ksz_iba_info *info, void *out, void *obj)
{
	return iba_get_post(info, out, obj, 0);
}  /* iba_get_post_le */

/**
 * iba_set_pre - IBA burst write pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This routine prepares IBA for burst write operation.
 */
static void iba_set_pre(u32 *data, int cnt, char *buf)
{
	u32 *ptr = (u32 *) buf;
	int i;

	i = 0;
	if (cnt > 1)
		i = 1;
	while (cnt > 0) {
		data[i++] = *ptr++;
		cnt--;
	}
}  /* iba_set_pre */

/**
 * iba_set_post - IBA burst write post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA burst write operation.
 *
 * Return number of registers written.
 */
static int iba_set_post(struct ksz_iba_info *info, void *out, void *obj)
{
	int i = 0;

	while (info->regs[i].cmd != (u32) -1) {
		i++;
	}
	return i;
}  /* iba_set_post */

/**
 * iba_burst - IBA burst request
 * @info:	The IBA instance.
 * @addr:	The starting address.
 * @cnt:	The number of addresses.
 * @buf:	Buffer holding the data.
 * @write:	Write indication.
 * @prepare:	The pre-processing routine.
 * @post:	The post-processing function.
 *
 * This function sends a burst request to IBA and waits for a response.
 *
 * Return number of bytes read.
 */
static int iba_burst(struct ksz_iba_info *info, u32 addr, size_t cnt,
	char *buf, int write, void (*prepare)(u32 *data, int cnt, char *buf),
	int (*post)(struct ksz_iba_info *info, void *out, void *obj))
{
	int mult;
	int rc;
	unsigned long wait;
	u32 val;
	u16 code = IBA_CODE_NORMAL;
	u32 cmd = IBA_CMD_READ;
	u32 size = IBA_CMD_32;
	void *data = buf;

	memset(info->data, 0, sizeof(u32) * IBA_BURST_CNT_MAX);
	if (cnt > 4) {
		mult = cnt / 4;
		info->data[0] = mult;
		code = IBA_CODE_BURST;
		cmd = IBA_BURST_READ;
	} else {
		mult = 1;
		if (1 == cnt) {
			if (write) {
				u8 *ptr = data;

				val = *ptr;
				data = &val;
			}
			size = IBA_CMD_8;
		} else if (2 == cnt) {
			if (write) {
				u16 *ptr = data;

				val = *ptr;
				data = &val;
			}
			size = IBA_CMD_16;
		} else if (addr & 1)
			size = IBA_CMD_8;
		else if (addr & 2)
			size = IBA_CMD_16;
	}
	cmd += write;
	info->fptr = iba_pre_cmd(info, code);

	prepare(info->data, mult, data);
	info->fptr = iba_cmd_data(info, cmd, size, addr);

	info->fptr = iba_post_cmd(info);
	info->regs[0].cmd = (u32) -1;
	rc = iba_xmit(info);
	signal_wait(&rx_resp_thread, rx_resp_cnt);

	rc = post(info, data, NULL);
	rc *= 4;
	return rc;
}  /* iba_burst */

static void iba_r_buf(struct ksz_iba_info *iba, unsigned reg, void *buf,
	size_t count)
{
	u8 *orig_buf = buf;
	size_t orig_cnt = count;
	int start = 0;

	/* Not in multiple of 4. */
	if ((count & 3) || (reg & 3)) {
		orig_buf = buf;
		orig_cnt = count;
		start = reg & 3;
		reg &= ~3;
		buf = iba->buf;
		count += start;
		count += 3;
		count &= ~3;
	}
	iba_burst(iba, reg, count, buf, 0,
		iba_get_pre, iba_get_post_be);
	if (orig_buf != buf)
		memcpy(orig_buf, &iba->buf[start], orig_cnt);
}  /* iba_r_buf */

static u32 buf_to_val(u8 *buf, int i, int cnt)
{
	int j;
	u32 val = buf[i];

	for (j = 1; j < cnt; j++) {
		val <<= 8;
		val |= buf[i + j];
	}
	return val;
}  /* buf_to_val */

/**
 * w_buf_pre - IBA buffer write pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for buffer write operation.
 *
 * Return the IBA frame pointer.
 */
static void *w_buf_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	u8 *buf = obj;
	u16 reg = data[0];
	size_t cnt = data[1];
	int i;
	u32 size;
	u32 val;

	/* Register may not be in 4-byte boundary. */
	switch (reg & 3) {
	case 1:
		size = IBA_CMD_24;
		i = 3;
		break;
	case 2:
		size = IBA_CMD_16;
		i = 2;
		break;
	case 3:
		size = IBA_CMD_8;
		i = 1;
		break;
	default:
		size = IBA_CMD_32;
		i = 4;
		break;
	}

	/* Count may be too small. */
	if (i > cnt) {
		i = cnt;
		switch (i) {
		case 1:
			size = IBA_CMD_8;
			break;
		case 2:
			size = IBA_CMD_16;
			break;
		default:
			size = IBA_CMD_24;
			break;
		}
	}

	/* Prepare the initial value. */
	val = buf_to_val(buf, 0, i);

	cnt -= i;
	info->data[0] = val;
	info->fptr = iba_cmd_data(info, IBA_CMD_WRITE, size, reg);
	reg &= ~3;
	size = IBA_CMD_32;
	while (cnt >= 4) {
		val = buf_to_val(buf, i, 4);
		reg += 4;
		info->data[0] = val;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE, size, reg);
		i += 4;
		cnt -= 4;
	}
	if (cnt) {
		switch (cnt) {
		case 1:
			size = IBA_CMD_8;
			break;
		case 2:
			size = IBA_CMD_16;
			break;
		default:
			size = IBA_CMD_24;
			break;
		}
		val = buf_to_val(buf, i, cnt);
		reg += 4;
		info->data[0] = val;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE, size, reg);
	}
	return info->fptr;
}  /* w_buf_pre */

static void iba_w_buf(struct ksz_iba_info *iba, unsigned reg, void *buf,
	size_t count)
{
	/* Not in multiple of 4. */
	if ((count & 3) || (reg & 3)) {
		u32 data[3];

		data[0] = reg;
		data[1] = count;
		iba_req(iba, data, NULL, buf, w_buf_pre,
			iba_set_post);
	} else {
		int i;
		u32 *src = buf;
		u32 *dst = (u32 *) iba->buf;

		for (i = 0; i < count; i += 4)
			*dst++ = ntohl(*src++);
		buf = iba->buf;
		iba_burst(iba, reg, count, buf, 1,
			iba_set_pre, iba_set_post);
	}
}  /* iba_w_buf */

static int iba_get(struct ksz_iba_info *iba, u32 reg, size_t count, char *buf)
{
	int rc;

	rc = iba_burst(iba, reg, count, buf, 0,
		iba_get_pre, iba_get_post_le);

	/*
	 * Return zero to let the calling program know the boundary must be
	 * 32-bit.
	 */
	if (4 == count && (reg & 3))
		rc = 0;
	return rc;
}  /* iba_get */

static int iba_set(struct ksz_iba_info *iba, u32 reg, size_t count, char *buf)
{
	return iba_burst(iba, reg, count, buf, 1,
		iba_set_pre, iba_set_post);
}  /* iba_set */

/**
 * iba_rcv - Receive IBA response.
 * @info:	The IBA instance.
 * @skb:	The received socket buffer.
 *
 * This function processes IBA response.
 */
static int iba_rcv(struct ksz_iba_info *info, u8 *rdata, int rlen)
{
	int i;
	int j;
	int k;
	int cnt;
	int len;
	int cmd_shift;
	u32 cmd;
	u32 cmds;
	u32 addr;
	u32 data;
	struct iba_frame *iba;
	struct iba_cmd *frame;
	u8 *ptr;
	int ret = 1;

	ptr = rdata;
	ptr += ETH_ALEN * 2;
	iba = (struct iba_frame *) ptr;

	if (iba->tag.type != htons(info->tag_type) ||
	    iba->format.format != htons(iba_ksz_format))
		goto out_drop;

	if (!info->cmds[0].cmd)
		goto out_drop;

	if (iba->tag.seqid != info->seqid)
		goto out_debug;

	len = ntohs(iba->length);
	cnt = rlen;
	if (len != cnt) {
		if (dbg_rcv)
		if (rlen > 61 && len + 4 != cnt)
			printf("len: %d != %d\n", len, cnt);
		if (len > cnt)
			len = cnt;
	}
	len -= ETH_ALEN * 2 + sizeof(struct iba_frame) -
		sizeof(struct iba_cmd);
	if (ntohs(iba->code) == IBA_CODE_NORMAL) {
#ifdef DBG_IBA
		if (dbg_rcv)
		printf("normal\n");
#endif
		cmd_shift = IBA_CMD_S;
	} else {
#ifdef DBG_IBA
		if (dbg_rcv)
		printf("burst\n");
#endif
		cmd_shift = IBA_BURST_S;
	}
	frame = &iba->cmd;
	j = 0;
	k = 0;
	while (len >= 4 && frame->cmd) {
		cmd = ntohl(frame->cmd);
		if (0xdeadbeef == cmd) {
#if 0
printf("apb: %08x\n", last_iba_addr);
#endif
			break;
		}
		cmds = cmd;
		addr = cmd & IBA_CMD_ADDR_M;
		i = 0;
		data = ntohl(frame->data[i++]);
		if (cmd != info->cmds[j].cmd || (IBA_BURST_S == cmd_shift
				&& data != info->cmds[j].data[0]))
			printf("?cmd %x=%x %x=%x\n", info->cmds[j].cmd, cmd,
				info->cmds[j].data[0], data);
		cmd >>= cmd_shift;
		if (IBA_BURST_S == cmd_shift) {
			cnt = data;
			if (IBA_BURST_WRITE == cmd) {
#ifdef DBG_IBA
				if (dbg_rcv)
				printf("w: %08x=%d\n", addr, cnt);
#endif
#if 0
				i += cnt;
#else
				for (; i <= cnt; i++) {
					data = ntohl(frame->data[i]);
					cmds += 4;
#ifdef DBG_IBA
					if (dbg_rcv)
					printf("%08x ", data);
#endif
				}
#ifdef DBG_IBA
				if (dbg_rcv)
				if (cnt)
					printf("\n");
#endif
#endif
			} else if (IBA_BURST_READ == cmd) {
#ifdef DBG_IBA
				if (dbg_rcv)
				printf("r: %08x=%d\n", addr, cnt);
#endif
				info->regs[k].cmd = cmds;
				for (; i <= cnt; i++) {
					data = ntohl(frame->data[i]);
					info->regs[k++].data[0] = data;
					info->regs[k].cmd =
						info->regs[k - 1].cmd + 4;
#ifdef DBG_IBA
					if (dbg_rcv)
					printf("%08x ", data);
#endif
				}
#ifdef DBG_IBA
				if (dbg_rcv)
				if (cnt)
					printf("\n");
#endif
			} else
				break;
			len -= sizeof(u32) * cnt;
		} else {
			switch (cmd) {
			case IBA_CMD_READ:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef DBG_IBA
				if (dbg_rcv)
				printf("r: ");
#endif
				break;
			case IBA_CMD_WRITE:
#ifdef DBG_IBA
				if (dbg_rcv)
				printf("w: ");
#endif
				break;
			case IBA_CMD_WAIT_ON_0:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef DBG_IBA
				if (dbg_rcv)
				printf("z: ");
#endif
				break;
			case IBA_CMD_WAIT_ON_1:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef DBG_IBA
				if (dbg_rcv)
				printf("s: ");
#endif
				break;
			case IBA_CMD_WRITE_0:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef DBG_IBA
				if (dbg_rcv)
				printf("0: ");
#endif
				break;
			case IBA_CMD_WRITE_1:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef DBG_IBA
				if (dbg_rcv)
				printf("1: ");
#endif
				break;
			}
#ifdef DBG_IBA
			if (dbg_rcv)
			printf("%08x=%08x\n", addr, data);
#endif
		}
		j++;
		len -= sizeof(struct iba_cmd);
		frame = (struct iba_cmd *) &frame->data[i];
	}
	info->cmds[0].cmd = 0;
	info->regs[k].cmd = (u32) -1;
	info->respid = iba->tag.seqid;

	return 0;

out_debug:
	printf("seq: %x\n", info->seqid);
	for (i = 0; i < ntohs(info->frame->length); i++) {
		printf("%02x ", info->packet[i]);
		if (15 == (i % 16))
			printf("\n");
	}
	if (15 != (i % 16))
		printf("\n");
	for (i = 0; i < rlen; i++) {
		printf("%02x ", rdata[i]);
		if (15 == (i % 16))
			printf("\n");
	}
	if (15 != (i % 16))
		printf("\n");

out_drop:
	return ret;
}  /* iba_rcv */

#if defined(_MSC_VER)
#include <packoff.h>
#endif


int gWaitDelay = 100;

#define PTP_EVENT_PORT			319
#define PTP_GENERAL_PORT		320

int ip_family;
int ipv6_interface = 0;

SOCKET eth_fd[NUM_OF_PORTS];
char ethnames[20];

char devname[20];

u8 ptp_len = 0;
u8 tail_tag_len = 0;
u8 tail_tag = 3 << (1 + 3);

#ifdef _SYS_SOCKET_H
struct sockaddr_ll eth_iba_addr[2];
u8 *eth_iba_buf[2];

u8 eth_iba[] = { 0x01, 0x00, 0x50, 0x00, 0x01, 0x80 };

u8 hw_addr[ETH_ALEN];

#endif

u8 host_addr[16];
u8 host_addr6[16];

struct rx_param {
	int *iba;
	int cnt;
};

typedef struct {
	int fTaskStop;
	void *param;

#if defined(_WIN32)
	HANDLE hevTaskComplete;
#endif
} TTaskParam, *PTTaskParam;


static int test_port = 1;
static int ptp_correction;
static int ptp_domain;
static int ptp_dst_port;
static int ptp_src_port;
static int reserved3;

static u16 seqid_sync;
static u16 seqid_delay_req;
static u16 seqid_pdelay_req;
static u32 sync_sec;

static u8 transport;

#define NUM_OF_ADDR			6

static u8 rx_addr[NUM_OF_ADDR][6];
static int rx_num[NUM_OF_ADDR][NUM_OF_PORTS];
static int rx_cnt;

static u8 ts_addr[NUM_OF_PORTS][6];
static int tx_delay;


/**
 * iba_xmit - Transmit IBA request.
 * @info:	The IBA instance.
 *
 * This function prepares IBA request for transmit.
 */
static int iba_xmit(struct ksz_iba_info *info)
{
	SOCKET sockfd = eth_fd[info->id];
	SAI *pservaddr;
	socklen_t servlen;
	int rc = 0;
	int len = ntohs(info->frame->length);

	pservaddr = (SAI *) &eth_iba_addr[0];
	servlen = sizeof(eth_iba_addr[0]);
	if (info->id)
		info->tag_type |= 0x0100;
	else
		info->tag_type &= ~0x0100;
	info->frame->tag.type = htons(info->tag_type);
	if (len < 60) {
		memset(&info->packet[len], 0, 60 - len);
		len = 60;
	}
	if (tail_tag_len) {
		if (ptp_len) {
			memset(&info->packet[len], 0, 4);
			len += 4;
		}
		memset(&info->packet[len], 0, 3);
		info->packet[len] = tail_tag;
		len += tail_tag_len;
	}
#if 0
do {
	int i;
	for (i = 0; i < len; i++) {
printf("%02x ", info->packet[i]);
if ((i % 16) == 15)
printf("\n");
	}
printf("\n");
} while (0);
#endif

	Sendto(sockfd, info->packet, len, 0, (SA *) pservaddr, servlen);
	return rc;
}  /* iba_xmit */

static void ksz_iba_init(struct ksz_iba_info *iba)
{
	u32 data;
	u16 tag_type;

	tag_type = ETH_P_IBA;

	iba->packet = malloc(IBA_LEN_MAX);
	iba->buf = malloc(IBA_LEN_MAX);
	iba->data = malloc(IBA_BURST_CNT_MAX * sizeof(u32));
	iba->regs = malloc(IBA_BURST_CNT_MAX * sizeof(struct iba_cmd));
	iba->cmds = malloc(IBA_BURST_CNT_MAX * sizeof(struct iba_cmd) / 4);
	iba->frame = (struct iba_frame *) &iba->packet[ETH_ALEN * 2];
	iba->tag_type = tag_type;
	memcpy(iba->dst, eth_iba, ETH_ALEN);
	iba->src[0] = 0x00;
	iba->src[1] = 0x10;
	iba->src[2] = 0xA1;
	iba->src[3] = 0x98;
	iba->src[4] = 0x97;
	iba->src[5] = 0x81;
}  /* ksz_iba_init */

static void ksz_iba_exit(struct ksz_iba_info *iba)
{
	free(iba->cmds);
	free(iba->regs);
	free(iba->data);
	free(iba->buf);
	free(iba->packet);
}  /* ksz_iba_exit */


struct ksz_iba_info iba_info;

int get_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[8];
	unsigned int hex[8];
	unsigned int val;
	int cont = 1;
	int i;
	int n;
	int p = 0;
	char cmd[80];
	char line[80];
	u32 buf[0x20];

	do {
		printf("> ");
		if (fgets(line, 80, fp) == NULL)
			break;
		cmd[0] = '\0';
		count = sscanf(line, "%s %d %d %d %d", cmd,
			(unsigned int *) &num[0],
			(unsigned int *) &num[1],
			(unsigned int *) &num[2],
			(unsigned int *) &num[3]);
		hcount = sscanf(line, "%s %x %x %x %x", cmd,
			(unsigned int *) &hex[0],
			(unsigned int *) &hex[1],
			(unsigned int *) &hex[2],
			(unsigned int *) &hex[3]);
		switch (line[0]) {
		case 'r':
			if (hcount < 2)
				break;
			if (line[1] == 'b') {
				val = iba_r8(&iba_info, hex[0]);
				printf("%u.%04x: %02x\n",
					iba_info.id, hex[0], val);
			} else if (line[1] == 'w') {
				val = iba_r16(&iba_info, hex[0]);
				printf("%u.%04x: %04x\n",
					iba_info.id, hex[0], val);
			} else if (line[1] == 't') {
				val = iba_r24(&iba_info, hex[0]);
				printf("%u.%04x: %06x\n",
					iba_info.id, hex[0], val);
			} else if (hcount > 2) {
				if (hex[1] > 0x20)
					hex[1] = 0x20;
				i = iba_get(&iba_info, hex[0], hex[1] * 4,
					(char *)buf);
				if (!i)
					break;
				for (i = 0; i < hex[1]; i++) {
					if ((i % 8) == 0)
						printf("%u.%04x: ",
							iba_info.id,
							hex[0] + i * 4);
					printf("%08x ", buf[i]);
					if ((i % 8) == 7)
						printf("\n");
				}
				if ((i % 8) != 0)
					printf("\n");
			} else {
				val = iba_r32(&iba_info, hex[0]);
				printf("%u.%04x: %08x\n",
					iba_info.id, hex[0], val);
			}
			break;
		case 'w':
			if (hcount < 3)
				break;
			if (line[1] == 'b')
				iba_w8(&iba_info, hex[0], hex[1]);
			else if (line[1] == 'w')
				iba_w16(&iba_info, hex[0], hex[1]);
			else if (line[1] == 't')
				iba_w24(&iba_info, hex[0], hex[1]);
			else
				iba_w32(&iba_info, hex[0], hex[1]);
			break;
		case 'a':
			if (hcount < 3)
				break;
			if (line[1] == 'b')
				iba_s0_1(&iba_info, hex[0], hex[1]);
			else if (line[1] == 'w')
				iba_s0_2(&iba_info, hex[0], hex[1]);
			else if (line[1] == 't')
				iba_s0_3(&iba_info, hex[0], hex[1]);
			else
				iba_s0_4(&iba_info, hex[0], hex[1]);
			break;
		case 'b':
			if (hcount < 3)
				break;
			if (line[1] == 'b')
				iba_s1_1(&iba_info, hex[0], hex[1]);
			else if (line[1] == 'w')
				iba_s1_2(&iba_info, hex[0], hex[1]);
			else if (line[1] == 't')
				iba_s1_3(&iba_info, hex[0], hex[1]);
			else
				iba_s1_4(&iba_info, hex[0], hex[1]);
			break;
		case 'm':
			if (hcount < 3)
				break;
			if (line[1] == 'b')
				iba_w0_1(&iba_info, hex[0], hex[1]);
			else if (line[1] == 'w')
				iba_w0_2(&iba_info, hex[0], hex[1]);
			else if (line[1] == 't')
				iba_w0_3(&iba_info, hex[0], hex[1]);
			else
				iba_w0_4(&iba_info, hex[0], hex[1]);
			break;
		case 'n':
			if (hcount < 3)
				break;
			if (line[1] == 'b')
				iba_w1_1(&iba_info, hex[0], hex[1]);
			else if (line[1] == 'w')
				iba_w1_2(&iba_info, hex[0], hex[1]);
			else if (line[1] == 't')
				iba_w1_3(&iba_info, hex[0], hex[1]);
			else
				iba_w1_4(&iba_info, hex[0], hex[1]);
			break;
		case 'c':
			if (count > 1) {
				if (num[0])
					iba_info.id = 1;
				else
					iba_info.id = 0;
			} else
				printf("%u\n", iba_info.id);
			break;
		case 'f':
			if (count > 1) {
				iba_ksz_format = hex[0];
				iba_info.frame->format.format =
					htons(iba_ksz_format);
			} else
				printf("%04x\n", iba_ksz_format);
			break;
		case 'p':
			if (count > 1) {
				if (num[0])
					ptp_len = 4;
				else
					ptp_len = 0;
			} else
				printf("%u\n", ptp_len);
			break;
		case 'l':
			if (count > 1) {
				if (num[0] > 8)
					num[0] = 8;
				tail_tag_len = num[0];
			} else
				printf("%u\n", tail_tag_len);
			break;
		case 't':
			if (count > 1) {
				tail_tag = (u8)hex[0];
			} else
				printf("0x%02x\n", tail_tag);
			break;
		case 'h':
		case '?':
			printf("\tr <reg> [cnt]\tread register\n");
			printf("\trb <reg>\n");
			printf("\trw <reg>\n");
			printf("\trt <reg>\n");
			printf("\tw  <reg> <val>\twrite register\n");
			printf("\twb <reg> <val>\n");
			printf("\tww <reg> <val>\n");
			printf("\twt <reg> <val>\n");
			printf("\ta  <reg> <mask>\tclear bits\n");
			printf("\tab <reg> <mask>\n");
			printf("\taw <reg> <mask>\n");
			printf("\tat <reg> <mask>\n");
			printf("\tb  <reg> <mask>\tset bits\n");
			printf("\tbb <reg> <mask>\n");
			printf("\tbw <reg> <mask>\n");
			printf("\tbt <reg> <mask>\n");
			printf("\tm  <reg> <mask>\twait on 0 bits\n");
			printf("\tmb <reg> <mask>\n");
			printf("\tmw <reg> <mask>\n");
			printf("\tmt <reg> <mask>\n");
			printf("\tn  <reg> <mask>\twait on 1 bits\n");
			printf("\tnb <reg> <mask>\n");
			printf("\tnw <reg> <mask>\n");
			printf("\tnt <reg> <mask>\n");
			printf("\tf [9300|9800]\tchange format\n");
			printf("\tl <len>\t\tset tail tag length\n");
			printf("\tt <tag>\t\tset tail tag value\n");
			printf("\tp [0|1]\t\tchange PTP\n");
			printf("\tc [0|1]\t\tchange chip id\n");
			printf("\th\t\thelp\n");
			printf("\tq\t\tquit\n");
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
	return 0;
}  /* get_cmd */

struct sock_buf {
	struct sockaddr *from;
	u8 *buf;
	int len;
};

static int check_loop(struct sockaddr *sa, int salen, int port)
{
	struct sockaddr_in *addr4;
	struct sockaddr_in6 *addr6;
#ifdef _SYS_SOCKET_H
	struct sockaddr_ll *addr;
#endif

	if (AF_INET6 == sa->sa_family) {
		addr6 = (struct sockaddr_in6 *) sa;
		if (memcmp(&addr6->sin6_addr, host_addr6, 16) == 0)
			return 1;
		if (memcmp(&addr6->sin6_addr.s6_addr[12], host_addr, 4) == 0)
			return 2;
	} else if (AF_INET == sa->sa_family) {
		addr4 = (struct sockaddr_in *) sa;
		if (memcmp(&addr4->sin_addr, host_addr, 4) == 0)
			return 1;
	} else {
#ifdef _SYS_SOCKET_H
		addr = (struct sockaddr_ll *) sa;
		if (addr->sll_ifindex != eth_iba_addr[port].sll_ifindex)
			return 2;
		if (memcmp(addr->sll_addr, hw_addr, ETH_ALEN) == 0)
			return 1;
#endif
	}
	return 0;
}

static int check_dup(struct sock_buf *cur, struct sock_buf *last, int len)
{
#if 0
	if (cur->len == last->len &&
			memcmp(cur->from, last->from, len) == 0 &&
			memcmp(cur->buf, last->buf, cur->len) == 0)
		return 1;
#endif
	return 0;
}

#ifdef _SYS_SOCKET_H
void *

#else
void
#endif
ReceiveTask(void *param)
{
	PTTaskParam pTaskParam;
	struct rx_param *rx_param;
	u8 *recvbuf;
	SOCKET sockfd;
	SOCKET fd[8];
	struct sock_buf buf[2];
	struct sockaddr_in6 cliaddr[2];
	struct sockaddr_in *addr4;
	struct sockaddr_in6 *addr6;
#ifdef _SYS_SOCKET_H
	struct sockaddr_ll *addr;
#endif
	struct timeval timer;
	fd_set rset;
	fd_set allrset;
	socklen_t len;
	int maxfdp1;
	void *iba;
	int i;
	int j;
	char in_addr[80];
	int cur;
	int last;
	int nsel;
	int looped;
	int msglen;

	pTaskParam = (PTTaskParam) param;
	rx_param = pTaskParam->param;

	len = (MAXBUFFER + 3) & ~3;
	recvbuf = malloc(len * 2);
	buf[0].len = buf[1].len = 0;
	buf[0].buf = recvbuf;
	buf[1].buf = recvbuf + len;
	buf[0].from = (struct sockaddr *) &cliaddr[0];
	buf[1].from = (struct sockaddr *) &cliaddr[1];
	cur = 0;
	last = 1;

#ifdef _WIN32
	SetEvent( pTaskParam->hevTaskComplete );
#endif

	bzero(cliaddr, sizeof(cliaddr));

	FD_ZERO(&allrset);
	maxfdp1 = rx_param->iba[0];
	j = 0;
	for (i = 0; i < rx_param->cnt; i++) {
		fd[j] = rx_param->iba[i];
		FD_SET(fd[j], &allrset);
		if (fd[j] > maxfdp1)
			maxfdp1 = fd[j];
		++j;
	}
	maxfdp1++;
	FOREVER {
		if ( pTaskParam->fTaskStop ) {
			break;
		}

		rset = allrset;
		sockfd = 0;

		timerclear( &timer );
		timer.tv_usec = gWaitDelay * 1000;

		nsel = Select( maxfdp1, &rset, NULL, NULL, &timer );

		/* socket is not readable */
		if (!nsel) {
			if (pTaskParam->fTaskStop) {
				break;
			}
			continue;
		}

		for (i = 0; i < rx_param->cnt * 2; i++) {
			if (nsel <= 0)
				break;

			len = sizeof(struct sockaddr_in6);
			if (FD_ISSET(fd[i], &rset) && sockfd != fd[i])
				sockfd = fd[i];
			else
				continue;

			buf[cur].len = Recvfrom(sockfd, buf[cur].buf,
				MAXBUFFER, 0, buf[cur].from, &len);
			--nsel;
			addr = NULL;
			if (AF_INET6 == buf[cur].from->sa_family) {
				addr6 = (struct sockaddr_in6 *) buf[cur].from;
				inet_ntop(AF_INET6, &addr6->sin6_addr,
					in_addr, sizeof(in_addr));
			} else if (AF_INET == buf[cur].from->sa_family) {
				addr4 = (struct sockaddr_in *) buf[cur].from;
				inet_ntop(AF_INET, &addr4->sin_addr,
					in_addr, sizeof(in_addr));
			} else {
#ifdef _SYS_SOCKET_H
				addr = (struct sockaddr_ll *) buf[cur].from;
				sprintf(in_addr,
					"%02x:%02x:%02x:%02x:%02x:%02x [%d]",
					addr->sll_addr[0], addr->sll_addr[1],
					addr->sll_addr[2], addr->sll_addr[3],
					addr->sll_addr[4], addr->sll_addr[5],
					addr->sll_ifindex);
#endif
			}
				Pthread_mutex_lock(&disp_mutex);
			if (dbg_rcv)
				printf("r: %d=%d %d=%s  ", sockfd,
					buf[cur].len, len, in_addr);
			iba = NULL;
			msglen = buf[cur].len;
#ifdef _SYS_SOCKET_H
			if (AF_PACKET == buf[cur].from->sa_family) {
				iba = (struct iba_frame *) buf[cur].buf;
			}
#endif
			looped = check_loop(buf[cur].from, len,
				i / 2);
			if (looped) {
				int ignored = 1;

				if (1 == looped)
					ignored = 0;
				if (ignored) {
						printf("(ignored)\n");
						Pthread_mutex_unlock(
							&disp_mutex);
					continue;
				}
			}
			if (check_dup(&buf[cur], &buf[last], len)) {
					printf("(dup)\n");
					Pthread_mutex_unlock(&disp_mutex);
				continue;
			} else {
				if (dbg_rcv) {
					if (looped)
						printf("(looped)\n");
					else
						printf("\n");
				}
				cur = !cur;
				last = !last;
			}
			j = i / 2;
			if (iba) {
				iba_rcv(&iba_info, iba, msglen);
				if (!iba_info.regs[0].cmd) {
					rx_resp_cnt = 1;
					signal_update(&rx_resp_thread, NULL, 0);
				}
				rx_resp_cnt = 0;
			}
				Pthread_mutex_unlock(&disp_mutex);
		}
	}
	free(recvbuf);
	pTaskParam->fTaskStop = TRUE;

#ifdef _WIN32
	SetEvent( pTaskParam->hevTaskComplete );
#endif

#ifdef _SYS_SOCKET_H
	return NULL;
#endif
}  /* ReceiveTask */

struct ip_info {
	struct sockaddr_in addr;
	struct sockaddr_in6 addr6;
	u8 hwaddr[8];
	int plen;
	int scope;
	int if_idx;
};

int get_host_info(char *devname, struct ip_info *info)
{
	struct ifi_info *ifi;
	struct ifi_info *ifihead;

	ifihead = get_ifi_info(AF_INET, 1);
	for (ifi = ifihead; ifi != NULL; ifi = ifi->ifi_next) {
		if (!strcmp(devname, ifi->ifi_name)) {
			info->if_idx = ifi->ifi_index;
			if (ifi->ifi_addr != NULL)
				memcpy(&info->addr, ifi->ifi_addr,
					sizeof(struct sockaddr_in));
			memset(info->hwaddr, 0, 8);
			if (ifi->ifi_hlen > 0)
				memcpy(info->hwaddr, ifi->ifi_haddr,
					ifi->ifi_hlen);
			info->plen = 0;
			if (ifi->ifi_addr6 != NULL) {
				memcpy(&info->addr6, ifi->ifi_addr6,
					sizeof(struct sockaddr_in6));
				info->plen = ifi->ifi_plen;
				info->scope = ifi->ifi_scope;
			} else if (ifi->ifi_hlen > 0) {
				u8 *data = (u8 *) &info->addr6.sin6_addr;

				memset(data, 0, 16);
				data[0] = 0xfe;
				data[1] = 0x80;
				memcpy(&data[8], ifi->ifi_haddr, 3);
				data[8] ^= 0x02;
				data[11] = 0xff;
				data[12] = 0xfe;
				memcpy(&data[13], &ifi->ifi_haddr[3], 3);
				info->addr6.sin6_family = AF_INET6;
				info->plen = 64;
				info->scope = 0x20;
			}
			return 1;
		}
	}
	free_ifi_info(ifihead);
	return 0;
}

#ifdef _SYS_SOCKET_H
int get_dev_info(char *devname, struct ip_info *info)
{
	FILE *f;
	int dad_status;
	int count;
	int rc;
	char addr6[40];
	char addr6p[8][5];

	struct ipv6_info *ipv6;
	struct ipv6_info *ipv6head = NULL;

	char path[80];
	char file[40];
	int num[6];
	int found = FALSE;

	/* No IP address. */
	info->addr.sin_family = AF_UNSPEC;

	/* Assume no IPv6 address. */
	info->plen = 0;
	memset(info->hwaddr, 0, 8);

	f = fopen(_PATH_PROCNET_IFINET6, "r");
	if (!f)
		goto get_dev_raw;
	count = 10;
	ipv6head = calloc(count, sizeof(struct ipv6_info));
	ipv6 = ipv6head;
	while (fscanf(f, "%4s%4s%4s%4s%4s%4s%4s%4s %02x %02x %02x %02x %20s\n",
			addr6p[0], addr6p[1], addr6p[2], addr6p[3], addr6p[4],
			addr6p[5], addr6p[6], addr6p[7],
			&ipv6->if_idx, &ipv6->plen, &ipv6->scope, &dad_status,
			ipv6->devname) != EOF) {
		sprintf(addr6, "%s:%s:%s:%s:%s:%s:%s:%s",
			addr6p[0], addr6p[1], addr6p[2], addr6p[3],
			addr6p[4], addr6p[5], addr6p[6], addr6p[7]);
		inet_pton(AF_INET6, addr6,
			(struct sockaddr *) &ipv6->addr.sin6_addr);
		ipv6->addr.sin6_family = AF_INET6;
		if (!strcmp(devname, ipv6->devname)) {
			memcpy(&info->addr6, &ipv6->addr,
				sizeof(struct sockaddr_in6));
			info->if_idx = ipv6->if_idx;
			info->plen = ipv6->plen;
			info->scope = ipv6->scope;
			found = TRUE;
			break;
		}
		ipv6++;
		count--;
		if (1 == count)
			break;
	}
	free(ipv6head);
	fclose(f);

get_dev_raw:
	if (found)
		goto get_dev_addr;

	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_FLAGS);
	f = fopen(path, "r");
	if (!f)
		goto get_dev_done;
	rc = fscanf(f, "%x", &num[0]);
	fclose(f);

	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_OPERSTATE);
	f = fopen(path, "r");
	if (!f)
		goto get_dev_addr;
	rc = fscanf(f, "%s", file);
	fclose(f);
	if ((!strcmp(file, "up") && !(num[0] & IFF_UP)) ||
	    (!strcmp(file, "down") && (num[0] & IFF_UP)))
		printf(" ? %s 0x%04x\n", file, num[0]);

	/* Device not running. */
	if (!(num[0] & IFF_UP))
		goto get_dev_done;

get_dev_addr:
	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_IFINDEX);
	f = fopen(path, "r");
	if (f) {
		rc = fscanf(f, "%u", &num[0]);
		fclose(f);
		if (!found)
			info->if_idx = num[0];
		else if (info->if_idx != num[0])
			printf(" ? %d %d\n", info->if_idx, num[0]);
	}

	found = TRUE;

	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_ADDRESS);
	f = fopen(path, "r");
	if (!f)
		goto get_dev_done;
	rc = fscanf(f, "%x:%x:%x:%x:%x:%x",
		&num[0], &num[1], &num[2], &num[3], &num[4], &num[5]);
	fclose(f);
	for (count = 0; count < 6; count++)
		info->hwaddr[count] = (u8) num[count];

get_dev_done:
	return found;
}

static void add_multi(SOCKET sockfd, char *local_if, u8 *addr)
{
	struct ifreq ifr;
	int rc;

	strcpy(ifr.ifr_name, local_if);
	ifr.ifr_hwaddr.sa_family = AF_UNSPEC;
	memcpy(ifr.ifr_hwaddr.sa_data, addr, ETH_ALEN);
	rc = ioctl(sockfd, SIOCADDMULTI, &ifr);
}

static void del_multi(SOCKET sockfd, char *local_if, u8 *addr)
{
	struct ifreq ifr;
	int rc;

	strcpy(ifr.ifr_name, local_if);
	ifr.ifr_hwaddr.sa_family = AF_UNSPEC;
	memcpy(ifr.ifr_hwaddr.sa_data, addr, ETH_ALEN);
	rc = ioctl(sockfd, SIOCDELMULTI, &ifr);
}

static SOCKET create_raw(struct ip_info *info, char *dest, int p)
{
	SOCKET sockfd;
	struct ethhdr *eh;
	struct llc *llc;
	int addr[ETH_ALEN];
	int cnt;
	u16 proto;
	u16 *word;
	struct sockaddr_ll *sock_addr;
	u8 *eth_addr;
	u8 **eth_buf;

	proto = htons(ETH_P_IBA);
	if (p)
		proto |= 0x01;
	sock_addr = &eth_iba_addr[p];
	eth_addr = eth_iba;
	eth_buf = &eth_iba_buf[p];
	sockfd = Socket(AF_PACKET, SOCK_RAW, proto);
	if (sockfd < 0)
		return sockfd;

	cnt = sscanf(dest, "%x:%x:%x:%x:%x:%x",
		&addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]);
	sock_addr->sll_family = PF_PACKET;
	sock_addr->sll_protocol = proto;
	sock_addr->sll_ifindex = info->if_idx + 0;
	sock_addr->sll_hatype = ARPHRD_ETHER;
	sock_addr->sll_halen = ETH_ALEN;
	if (ETH_ALEN == cnt) {
		sock_addr->sll_pkttype = PACKET_OTHERHOST;
		sock_addr->sll_addr[0] = (u8) addr[0];
		sock_addr->sll_addr[1] = (u8) addr[1];
		sock_addr->sll_addr[2] = (u8) addr[2];
		sock_addr->sll_addr[3] = (u8) addr[3];
		sock_addr->sll_addr[4] = (u8) addr[4];
		sock_addr->sll_addr[5] = (u8) addr[5];
	} else {
		sock_addr->sll_pkttype = PACKET_MULTICAST;
		memcpy(sock_addr->sll_addr, eth_addr, ETH_ALEN);
	}
	sock_addr->sll_addr[6] = 0x00;
	sock_addr->sll_addr[7] = 0x00;
#if 1
	if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
	    ethnames, strlen(ethnames))) {
		err_ret("bindtodev");
		return -1;
	}
#endif

	*eth_buf = malloc(1518);
	memcpy(*eth_buf, sock_addr->sll_addr, ETH_ALEN);
	memcpy((*eth_buf) + ETH_ALEN, info->hwaddr, ETH_ALEN);
	eh = (struct ethhdr *) *eth_buf;
	eh->h_proto = proto;
	memcpy(ts_addr[p], info->hwaddr, ETH_ALEN);

	return sockfd;
}
#endif

int main(int argc, char *argv[])
{
	TTaskParam param[4];

#ifdef _SYS_SOCKET_H
	pthread_t tid[4];
	void *status;

#elif defined( _WIN32 )
	DWORD rc;
#endif
	char dest_ip[40];
	char host_ip4[40];
	char host_ip6[40];
	char *host_ip;
	int family;
	int i;
	int p;
	struct ip_info info;
	struct rx_param rx_param;

	SocketInit(0);

	if (argc < 2) {
		printf("usage: %s <local_if>",
			argv[0]);
		printf("\t[-p<#>] [-v] [-x #][-y #][-l]\n");
		return 1;
	}
	family = AF_PACKET;
	dest_ip[0] = '\0';
	if (argc > 2) {
		i = 2;
		while (i < argc) {
			if ('-' == argv[i][0]) {
				switch (argv[i][1]) {
				case 'd':
					dbg_rcv = 1;
					break;
				case 'u':
					++i;
					if (i >= argc)
						break;
					strcpy(dest_ip, argv[i]);
					break;
				}
			}
			++i;
		}
	}
	strncpy(devname, argv[1], sizeof(devname));
	host_ip = strchr(devname, '.');
	if (host_ip != NULL)
		*host_ip = 0;
	strncpy(ethnames, argv[1], 20);

	if (get_host_info(argv[1], &info)) {
		memcpy(host_addr, &info.addr.sin_addr, 4);
		inet_ntop(AF_INET, &info.addr.sin_addr,
			host_ip4, sizeof(host_ip4));
		printf("%s\n", host_ip4);
		ipv6_interface = info.if_idx;
		if (info.plen) {
			inet_ntop(AF_INET6, &info.addr6.sin6_addr,
				host_ip6, sizeof(host_ip6));
			printf("%s\n", host_ip6);
			memcpy(host_addr6, &info.addr6.sin6_addr, 16);
			ipv6_interface = info.if_idx;
		}
		memcpy(hw_addr, info.hwaddr, ETH_ALEN);
#ifdef _SYS_SOCKET_H
	} else if (get_dev_info(argv[1], &info)) {
		ipv6_interface = info.if_idx;
		if (info.plen) {
			inet_ntop(AF_INET6, &info.addr6.sin6_addr,
				host_ip6, sizeof(host_ip6));
			printf("%s\n", host_ip6);
			memcpy(host_addr6, &info.addr6.sin6_addr, 16);
			ipv6_interface = info.if_idx;
		}
		memcpy(hw_addr, info.hwaddr, ETH_ALEN);
#endif
	} else {
		printf("cannot locate IP address\n");
		exit(1);
	}

	ip_family = family;

	for (p = 0; p < 2; p++) {
		eth_fd[p] = create_raw(&info, dest_ip, p);
		if (eth_fd[p] < 0) {
			printf("Cannot create socket\n");
			return 1;
		}
		add_multi(eth_fd[p], ethnames, eth_iba);
	}
	signal_init(&tx_job_thread);
	signal_init(&rx_resp_thread);
	rx_resp_cnt = 0;

	ksz_iba_init(&iba_info);
	prepare_iba(&iba_info, iba_info.dst, info.hwaddr);

	rx_param.iba = eth_fd;
	rx_param.cnt = 2;

	for (i = 0; i < 3; i++) {
		param[i].fTaskStop = FALSE;
	}
	param[0].param = &rx_param;

	Pthread_create(&tid[0], NULL, ReceiveTask, &param[0]);

	if ( !param[0].fTaskStop ) {
		do {
			if (!get_cmd(stdin))
				break;
		} while (1);
		for (i = 0; i < 3; i++) {
			param[i].fTaskStop = TRUE;
		}
	}
	signal_update(&tx_job_thread, NULL, 0);
	signal_update(&rx_resp_thread, NULL, 0);

	// wait for task to end
	for (i = 0; i < 1; i++) {
		Pthread_join( tid[i], &status );
	}

	for (p = 0; p < 2; p++) {
		if (eth_fd[p] > 0) {
			del_multi(eth_fd[p], ethnames, eth_iba);
			free(eth_iba_buf[p]);
			closesocket(eth_fd[p]);
		}
	}
	ksz_iba_exit(&iba_info);
	SocketExit();

	return 0;
}
