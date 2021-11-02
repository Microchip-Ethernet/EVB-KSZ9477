/**
 * Microchip IBA code
 *
 * Copyright (c) 2015-2021 Microchip Technology Inc.
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


#ifdef DEBUG
#if 0
#define SHOW_IBA
#endif
#endif

#if 1
#define RETRY_IBA
#endif

#define ETH_P_IBA			IBA_TAG_TYPE

static void prepare_iba(struct ksz_iba_info *iba, u8 *dst, u8 *src)
{
#ifndef CAPTURE_IBA
	if (iba->dst != dst)
		memcpy(iba->dst, dst, ETH_ALEN);
	if (iba->src != src)
		memcpy(iba->src, src, ETH_ALEN);
#endif
	memcpy(iba->packet, iba->dst, ETH_ALEN);
	memcpy(&iba->packet[ETH_ALEN], iba->src, ETH_ALEN);

	iba->frame->tag.type = htons(iba->tag_type);
	iba->frame->tag.prio = 0;
	iba->frame->tag.cfi = 0;
	iba->frame->tag.mode = 1;
	iba->frame->format.format = htons(IBA_FORMAT_KSZ98XX);
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
dbg_msg(" command: %d"NL, cnt);
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

static unsigned long last_iba_jiffies;
static int dbg_iba;
static int last_ok_iba;
static int last_ok_reg;

static void *iba_pre_cmd(struct ksz_iba_info *info, u16 code)
{
	struct iba_frame *iba = info->frame;

if (info->respid != info->seqid) {
dbg_msg(" pre %x %x; %x; %x %x"NL, info->respid, info->seqid, code,
last_iba_jiffies, jiffies);
dbg_iba = 1;
}
last_iba_jiffies = jiffies;
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

#if 0
/**
 * iba_chk_regs - IBA register check
 * @sw:		The switch instance.
 * @cmds:	The IBA command.
 * @data:	The IBA data.
 *
 * This routine checks the value written to specific registers to determine
 * the correct tail tag length to use.
 */
static void iba_chk_regs(struct ksz_sw *sw, u32 cmds, u32 data)
{
	u32 port_reg;
	u32 reg = cmds & IBA_CMD_ADDR_M;
	u32 size = cmds & IBA_CMD_32;
	u32 val = iba_get_val(size, data);
	int need_ptp_tag = 0;
	int need_tail_tag = 0;

	if (IBA_CMD_BYTE_1 == size && (REG_PTP_MSG_CONF1 + 1) == reg) {
		need_ptp_tag++;
		if (val & PTP_ENABLE)
			need_ptp_tag++;
	} else if (IBA_CMD_16 == size && REG_PTP_MSG_CONF1 == reg) {
		need_ptp_tag++;
		if (val & PTP_ENABLE)
			need_ptp_tag++;
	} else if (IBA_CMD_32 == size && REG_PTP_MSG_CONF1 == reg) {
		need_ptp_tag++;
		if (val & (PTP_ENABLE << 16))
			need_ptp_tag++;
	}

/* KSZ9567 S1 needs to have PTP tag all the time. */
#if 1
	if (!(sw->features & NEW_CAP) &&
	    sw->TAIL_TAG_LOOKUP >= 0x100 && 1 == need_ptp_tag)
		need_ptp_tag = 2;
#endif
	if (2 == need_ptp_tag)
		sw->overrides |= PTP_TAG;
	else if (1 == need_ptp_tag)
		sw->overrides &= ~PTP_TAG;

	port_reg = PORT_CTRL_ADDR(sw->HOST_PORT, REG_PORT_CTRL_0);
	if (IBA_CMD_BYTE_0 == size && port_reg == reg) {
		need_tail_tag++;
		if (val & PORT_TAIL_TAG_ENABLE)
			need_tail_tag++;
	} else if (IBA_CMD_16 == size && port_reg == reg) {
		need_tail_tag++;
		if (val & (PORT_TAIL_TAG_ENABLE << 8))
			need_tail_tag++;
	} else if (IBA_CMD_32 == size && port_reg == reg) {
		need_tail_tag++;
		if (val & (PORT_TAIL_TAG_ENABLE << 24))
			need_tail_tag++;
	}
	if (2 == need_tail_tag)
		sw->overrides |= TAIL_TAGGING;
	else if (1 == need_tail_tag)
		sw->overrides &= ~TAIL_TAGGING;
}  /* iba_chk_regs */
#endif

static u32 last_iba_addr;

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
		if (IBA_CMD_16 == size && 3 == (addr & 3))
			pr_info("16-bit used with register ended with 3"NL);

		/* write can be 8-bit, 16-bit, 24-bit, or 32-bit. */
		if (IBA_CMD_READ != cmd) {

#if 1
			/* Do not allow changing IBA port. */
			if (IBA_CMD_WRITE == cmd &&
			    REG_SW_IBA__4 <= addr && addr < REG_SW_IBA__4 + 4) {
				info->data[0] = info->cfg;
				addr = REG_SW_IBA__4;
				size = IBA_CMD_32;
			}
#endif
			info->data[0] = iba_set_val(size, addr, info->data[0]);
		}
		size = iba_set_size(addr, size);
	}
	cmd <<= shift;
	cmd |= size;
	cmd |= addr & IBA_CMD_ADDR_M;
	last_iba_addr = addr;
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

if (info->respid != info->seqid) {
dbg_msg(" post %x %x"NL, info->respid, info->seqid);
dbg_iba = 1;
}
	info->cmds[info->index++].cmd = 0;
	info->fptr = iba_command(info->fptr, &info->len, 0, 0, NULL);
	iba->tag.seqid = ++info->seqid;
	iba->length = htons(info->len);
	return info->fptr;
}  /* iba_post_cmd */

/**
 * iba_xmit - Transmit IBA request.
 * @info:	The IBA instance.
 *
 * This function prepares IBA request for transmit.
 */
static int iba_xmit(struct ksz_iba_info *info)
{
	int len = ntohs(info->frame->length);
	int rc;
	struct net_device *netdev = info->dev;
	const struct net_device_ops *ops = netdev->netdev_ops;
	struct sk_buff *skb;
	int timeout = 5;

	if (len < 60) {
		memset(&info->packet[len], 0, 60 - len);
		len = 60;
	}

	/* Add extra for tail tagging. */
	skb = dev_alloc_skb(len + 4 + 8);
	if (!skb)
		return -ENOMEM;

	memcpy(skb->data, info->packet, len);
	skb_put(skb, len);
	skb->protocol = htons(ETH_P_IBA);
	skb->dev = netdev;
	do {
		struct ksz_sw *sw = info->sw_dev;

		rc = ops->ndo_start_xmit(skb, skb->dev);
		if (NETDEV_TX_BUSY == rc) {
			rc = wait_event_interruptible_timeout(sw->queue,
				!netif_queue_stopped(netdev),
				50 * HZ / 1000);

			rc = NETDEV_TX_BUSY;
		}
	} while (NETDEV_TX_BUSY == rc && timeout--);
	return rc;
}  /* iba_xmit */

#ifdef VERIFY_IBA
static void prepare_cmd(struct ksz_iba_info *info, int message)
{
	memset(info->data, 0, sizeof(u32) * IBA_BURST_CNT_MAX);
	switch (message) {
	case 0:
		info->fptr = iba_pre_cmd(info, IBA_CODE_NORMAL);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ,
			IBA_CMD_32, 0);
		info->fptr = iba_cmd_data(info, IBA_CMD_READ,
			IBA_CMD_32, 4);
		break;
	case 1:
		info->fptr = iba_pre_cmd(info, IBA_CODE_NORMAL);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE,
			IBA_CMD_32, REG_PTP_UNIT_INDEX__4);
		info->data[0] = TS_RESET;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		info->data[0] = TS_RESET;
		info->fptr = iba_cmd_data(info, IBA_CMD_WAIT_ON_0,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		info->data[0] = TS_ENABLE;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		info->data[0] = TS_ENABLE;
		info->fptr = iba_cmd_data(info, IBA_CMD_WAIT_ON_1,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		break;
	case 2:
		info->fptr = iba_pre_cmd(info, IBA_CODE_NORMAL);
		info->data[0] = 0xB;
		info->data[0] <<= MIB_COUNTER_INDEX_S;
		info->data[0] |= MIB_COUNTER_READ;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE,
			IBA_CMD_32,
			PORT_CTRL_ADDR(0, REG_PORT_MIB_CTRL_STAT__4));
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ,
			IBA_CMD_32,
			PORT_CTRL_ADDR(0, REG_PORT_MIB_CTRL_STAT__4));
		info->fptr = iba_cmd_data(info, IBA_CMD_READ,
			IBA_CMD_32,
			PORT_CTRL_ADDR(0, REG_PORT_MIB_DATA));
		break;
	case 3:
		info->fptr = iba_pre_cmd(info, IBA_CODE_BURST);
		info->data[0] = 2;
		info->data[1] = 0x12340000;
		info->data[2] = 0x56780000;
		info->fptr = iba_cmd_data(info, IBA_BURST_WRITE,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		info->data[0] = 4;
		info->data[1] = 0x12340000;
		info->data[2] = 0x56780000;
		info->data[3] = 0x00001234;
		info->data[4] = 0x00005678;
		info->fptr = iba_cmd_data(info, IBA_BURST_WRITE,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_BURST_READ,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		info->data[0] = 60;
		info->fptr = iba_cmd_data(info, IBA_BURST_READ,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		if (info->len + 4 >= IBA_LEN_MAX)
			break;
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_BURST_READ,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		break;
	case 4:
#if 1
		info->fptr = iba_pre_cmd(info, IBA_CODE_NORMAL);
#else
		info->fptr = iba_pre_cmd(info, 4);
#endif
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ,
			IBA_CMD_32, REG_PTP_INT_STATUS__4);
		info->data[0] = 2;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE,
			IBA_CMD_32, REG_PTP_INT_STATUS__4);
		info->data[0] = 2;
		info->fptr = iba_cmd_data(info, IBA_CMD_WAIT_ON_0,
			IBA_CMD_32, REG_PTP_INT_STATUS__4);
#if 0
		info->data[0] = 2;
		info->fptr = iba_cmd_data(info, IBA_CMD_WAIT_ON_1,
			IBA_CMD_32, REG_PTP_INT_STATUS__4);
#endif
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ,
			IBA_CMD_32, REG_PTP_INT_STATUS__4);
#if 0
		info->fptr = iba_cmd_data(info, 3,
			IBA_CMD_32, REG_PTP_INT_STATUS__4);
#endif
		break;
	case 5:
		info->fptr = iba_pre_cmd(info, IBA_CODE_BURST);
		info->data[0] = 63;
		info->fptr = iba_cmd_data(info, IBA_BURST_READ,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
		break;
	case 6:
		info->fptr = iba_pre_cmd(info, IBA_CODE_NORMAL);
#if 1
		info->data[0] = 0x1;
		info->fptr = iba_cmd_data(info, IBA_CMD_WAIT_ON_0, IBA_CMD_32,
			0x300);
#endif
		info->data[0] = 0x00800000;
		info->fptr = iba_cmd_data(info, IBA_CMD_WAIT_ON_1, IBA_CMD_32,
			0x00);
		info->data[0] = 0x10000000;
		info->fptr = iba_cmd_data(info, IBA_CMD_WAIT_ON_0, IBA_CMD_32,
			0x300);
		info->data[0] = 0x10000000;
		info->fptr = iba_cmd_data(info, IBA_CMD_WAIT_ON_0, IBA_CMD_32,
			0x304);
		info->data[0] = 0x8;
		info->fptr = iba_cmd_data(info, IBA_CMD_WAIT_ON_1, IBA_CMD_32,
			0x304);
		break;
	case 7:
		info->fptr = iba_pre_cmd(info, IBA_CODE_NORMAL);
#if 0
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x300);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x300);
#endif
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x304);
		info->data[0] = 0x10000001;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE_1, IBA_CMD_32,
			0x304);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x304);
		info->data[0] = 0x10000001;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE_0, IBA_CMD_32,
			0x304);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x304);
		info->data[0] = 0x10000001;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE_1, IBA_CMD_32,
			0x304);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x304);
		info->data[0] = 0x10000001;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE_0, IBA_CMD_32,
			0x304);
		break;
	case 8:
		info->fptr = iba_pre_cmd(info, IBA_CODE_NORMAL);
#if 0
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x300);
#endif
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x300);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x304);
		info->data[0] = 0x10000001;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE_1, IBA_CMD_32,
			0x304);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x304);
		info->data[0] = 0x10000001;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE_0, IBA_CMD_32,
			0x304);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x304);
		info->data[0] = 0x10000001;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE_1, IBA_CMD_32,
			0x304);
		info->data[0] = 0;
		info->fptr = iba_cmd_data(info, IBA_CMD_READ, IBA_CMD_32,
			0x304);
		info->data[0] = 0x10000001;
		info->fptr = iba_cmd_data(info, IBA_CMD_WRITE_0, IBA_CMD_32,
			0x304);
		break;
	default:
		info->fptr = iba_pre_cmd(info, IBA_CODE_NORMAL);
		info->fptr = iba_cmd_data(info, IBA_BURST_READ,
			IBA_CMD_32, REG_PTP_CTRL_STAT__4);
	}
	info->fptr = iba_post_cmd(info);
}

static int dbg_iba_test;
static int iba_test(struct ksz_iba_info *info, int n)
{
	int k;
	int rc;
	unsigned long wait;

	prepare_cmd(info, n);
	info->regs[0].cmd = (u32) -1;
	init_completion(&info->done);
	rc = iba_xmit(info);
	if (rc) {
		dbg_msg("send err: %d"NL, rc);
		return rc;
	}
	wait = wait_for_completion_timeout(&info->done, info->delay_ticks);
	dbg_msg("wait: %lx"NL, wait);

	k = 0;
	while (info->regs[k].cmd != (u32) -1) {
		dbg_msg("%08x=%08x"NL, info->regs[k].cmd,
			info->regs[k].data[0]);
		k++;
	}
#ifndef TEST_IBA
	do {
		struct ksz_sw *sw = info->sw_dev;
		u32 status;

if (mutex_is_locked(sw->reglock))
printk(" reg locked"NL);
		mutex_lock(sw->reglock);
		info->use_iba = 0;
		status = sw->old->r32(sw, REG_SW_IBA_STATUS__4);
		dbg_msg("status %08x q:%d p:%d d:%d f:%d o:%d m:%d"NL, status,
			!!(status & SW_IBA_REQ),
			!!(status & SW_IBA_RESP),
			!!(status & SW_IBA_DA_MISMATCH),
			!!(status & SW_IBA_FMT_MISMATCH),
			!!(status & SW_IBA_CODE_ERROR),
			!!(status & SW_IBA_CMD_ERROR));
		status = sw->old->r32(sw, REG_SW_IBA_STATES__4);
		dbg_msg("states %08x %u"NL, status,
			((status >> SW_IBA_PACKET_SIZE_S) &
			SW_IBA_PACKET_SIZE_M) * 4);
		status = sw->old->r32(sw, REG_SW_IBA_RESULT__4);
		dbg_msg("result %08x %u"NL, status, status >> SW_IBA_SIZE_S);
		info->use_iba = 1;
		mutex_unlock(sw->reglock);
	} while (0);
#endif

	return 0;
}
#endif

static struct ksz_iba_info *iba_info;

static void iba_lock(struct ksz_sw *sw)
{
	const struct ksz_sw_reg_ops *reg_ops = sw->reg;

	mutex_lock(sw->hwlock);
	++sw->info->iba.cnt;
	if (sw->reg != reg_ops) {
printk(KERN_ALERT "%s changed"NL, __func__);
dbg_msg("  %s changed"NL, __func__);
		mutex_unlock(sw->hwlock);
		sw->reg->lock(sw);
	}
}  /* iba_lock */

static void iba_unlock(struct ksz_sw *sw)
{
	if (sw->info->iba.cnt)
		--sw->info->iba.cnt;
	else
printk("wrong release"NL);
	mutex_unlock(sw->hwlock);
}  /* iba_unlock */

/**
 * This helper function is used to prepare the read registers for use with
 * the iba_r_post function.
 */
static u32 *iba_prepare_data(u32 reg, u32 *data)
{
	data[0] = reg;
	if (-1 == reg)
		return data + 1;
	data[1] = 0xdeadfeed;
	return data + 2;
}  /* iba_prepare_data */

/**
 * This helper routine is used to check the allocated buffers for use with
 * the iba_reqs function.
 */
static void assert_buf(const char *name, int i, size_t func_size, u32 *buf,
	u32 *data, size_t buf_size)
{
	int _assert = false;

	if ((i + 1) > func_size / sizeof(void *)) {
		printk(KERN_INFO "  [%s func] %u %u"NL,
			name, i, (int)(func_size / sizeof(void *)));
		_assert = true;
	}
	if (data > buf + buf_size / sizeof(u32)) {
		printk(KERN_INFO "  [%s data] %u"NL,
			name, (int)(data - buf));
		_assert = true;
	}
	if (_assert)
		BUG();
}  /* assert_buf */

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

	iba_cmd_set(info, IBA_CMD_READ, data[0], data[1], 0);
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

if (info->seqid != info->respid)
dbg_msg(" id %x %x"NL, info->seqid, info->respid);
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

	iba_cmd_set(info, IBA_CMD_WRITE, data[0], data[1], data[2]);
	return info->fptr;
}  /* iba_w_pre */

/**
 * sw_setup_iba - Switch IBA setup
 * @sw:		The switch instance.
 *
 * This routines setups IBA function of the switch.
 */
static void sw_setup_iba(struct ksz_sw *sw)
{
	u32 data;

	data = sw->old->r32(sw, REG_SW_IBA__4);
	sw->info->iba.tag_type = (data & SW_IBA_FRAME_TPID_M);
	data &= ~(SW_IBA_PORT_M << SW_IBA_PORT_S);
	data |= sw->HOST_PORT << SW_IBA_PORT_S;
	data |= SW_IBA_ENABLE;
	data |= SW_IBA_INIT;
#if 0
	data |= SW_IBA_DA_MATCH;
#endif
	sw->old->w32(sw, REG_SW_IBA__4, data);
	data &= ~SW_IBA_INIT;
	sw->info->iba.cfg = data;
	dbg_msg("status %08x"NL, sw->old->r32(sw, REG_SW_IBA_STATUS__4));
	dbg_msg("states %08x"NL, sw->old->r32(sw, REG_SW_IBA_STATES__4));
	dbg_msg("result %08x"NL, sw->old->r32(sw, REG_SW_IBA_RESULT__4));
}  /* sw_setup_iba */

/**
 * iba_to_spi - Switch IBA to SPI
 * @sw:		The switch instance.
 * @info:	The IBA instance.
 *
 * This routine switches from using IBA to using SPI.
 */
static void iba_to_spi(struct ksz_sw *sw, struct ksz_iba_info *info)
{
	if (2 <= info->use_iba) {
if (info->use_iba != 5)
dbg_msg(" iba stops: %x"NL, info->use_iba);
		info->use_iba = 5;
		return;
	}

	/* Not calling from interrupt handling. */
	if (sw->intr_using != 2)
		mutex_lock(sw->reglock);
	sw_set_spi(sw, info);
	if (sw->intr_using != 2)
		mutex_unlock(sw->hwlock);
	printk(KERN_ALERT "revert to SPI"NL);

#ifdef RETRY_IBA
	sw_setup_iba(sw);
	schedule_delayed_work(&sw->set_ops, msecs_to_jiffies(1000));
#endif
}  /* iba_to_spi */

static void iba_dbg_states(struct ksz_iba_info *info)
{
	int i;
	u32 status;
	struct ksz_sw *sw = info->sw_dev;
	int iba_test_override = (sw->overrides & IBA_TEST);
	int use_iba = info->use_iba;

	if (2 <= info->use_iba)
		return;
#if 0
iba_test_override = 1;
#endif
	if (!iba_test_override)
		return;

dbg_msg(" w seq: %x"NL, info->seqid);
if (sw->intr_using < 2 && mutex_is_locked(sw->reglock))
printk(" reg locked: %d"NL, sw->intr_using);
	if (sw->intr_using < 2)
		mutex_lock(sw->reglock);
	info->use_iba = 0;
	status = sw->old->r32(sw, REG_SW_IBA_STATUS__4);
	dbg_msg("status %08x q:%d p:%d d:%d f:%d o:%d m:%d"NL, status,
		!!(status & SW_IBA_REQ),
		!!(status & SW_IBA_RESP),
		!!(status & SW_IBA_DA_MISMATCH),
		!!(status & SW_IBA_FMT_MISMATCH),
		!!(status & SW_IBA_CODE_ERROR),
		!!(status & SW_IBA_CMD_ERROR));
	status = sw->old->r32(sw, REG_SW_IBA_STATES__4);
	dbg_msg("states %08x %u"NL, status, ((status >> SW_IBA_PACKET_SIZE_S) &
		SW_IBA_PACKET_SIZE_M) * 4);
	status = sw->old->r32(sw, REG_SW_IBA_RESULT__4);
	dbg_msg("result %08x %u"NL, status, status >> SW_IBA_SIZE_S);
	info->use_iba = use_iba;
	if (sw->intr_using < 2)
		mutex_unlock(sw->reglock);

	for (i = 0; i < ntohs(info->frame->length); i++) {
		dbg_msg("%02x ", info->packet[i]);
		if (15 == (i % 16))
			dbg_msg(NL);
	}
	if (i % 16)
		dbg_msg(NL);
}  /* iba_dbg_states */

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

	if (5 == info->use_iba) {
		return 0;
	}
	do {
		struct ksz_sw *sw = info->sw_dev;

		if (!mutex_is_locked(sw->hwlock))
			pr_alert("IBA not locked"NL);
	} while (0);
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
	init_completion(&info->done);
	rc = iba_xmit(info);
	if (rc) {
printk("  !! %x"NL, rc);
		iba_dbg_states(info);

		/* Not testing if IBA is okay. */
		if (!(info->use_iba & 0x80))
			iba_to_spi(info->sw_dev, info);
		return 0;
	}
	if (info->use_iba & 0x40)
		wait = 1;
	else
	wait = wait_for_completion_timeout(&info->done, info->delay_ticks);
	if (!wait) {
if (dbg_iba)
dbg_msg("  w timeout"NL);
else
dbg_msg(" first fail: %02x %04x %04x"NL, info->respid, last_ok_reg,
	last_iba_addr);
		iba_dbg_states(info);

		/* Not testing if IBA is okay. */
		if (!(info->use_iba & 0x80))
			iba_to_spi(info->sw_dev, info);
		return 0;
	}

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

#ifdef CONFIG_LAN78XX_KSZ9897_IBA
	if (usb_disconnected)
		return 0;
#endif

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
	static int iba_r_enter;

	if (5 == info->use_iba) {
		return 0;
	}
	if (4 == info->use_iba)
		printk(KERN_WARNING " %s %x"NL, __func__, reg);
#if 1
if (info->respid != info->seqid || iba_r_enter) {
dbg_msg(" iba_r %x %x %d; %x %x; %d"NL, info->respid, info->seqid, info->cnt, reg,
last_ok_reg, iba_r_enter);
}
#endif
	++iba_r_enter;
	data[0] = size;
	data[1] = reg;
	data[2] = 0xdeadbeaf;
	data[3] = -1;
	rc = iba_req(info, data, data + 1, NULL, iba_r_pre, iba_r_post);
	if (!rc)
dbg_msg("r %x %x %08x"NL, reg, size, data[2]);
else if (dbg_iba)
dbg_msg(" ?? %d %08x"NL, rc, data[2]);
	last_ok_reg = reg;
	--iba_r_enter;
	return data[2];
}  /* iba_r */

/**
 * iba_r8 - IBA 8-bit register read
 * @info:	The IBA instance.
 * @reg:	The register to read.
 *
 * This function reads a 8-bit register through IBA.
 */
static u8 iba_r8(struct ksz_sw *sw, unsigned reg)
{
	return (u8) iba_r(&sw->info->iba, reg, IBA_CMD_8);
}  /* iba_r8 */

/**
 * iba_r16 - IBA 16-bit register read
 * @info:	The IBA instance.
 * @reg:	The register to read.
 *
 * This function reads a 16-bit register through IBA.
 */
static u16 iba_r16(struct ksz_sw *sw, unsigned reg)
{
	return (u16) iba_r(&sw->info->iba, reg, IBA_CMD_16);
}  /* iba_r16 */

/**
 * iba_r24 - IBA 24-bit register read
 * @info:	The IBA instance.
 * @reg:	The register to read.
 *
 * This function reads a 24-bit register through IBA.
 */
static u32 iba_r24(struct ksz_sw *sw, unsigned reg)
{
	return iba_r(&sw->info->iba, reg, IBA_CMD_24);
}  /* iba_r24 */

/**
 * iba_r32 - IBA 32-bit register read
 * @info:	The IBA instance.
 * @reg:	The register to read.
 *
 * This function reads a 32-bit register through IBA.
 */
static u32 iba_r32(struct ksz_sw *sw, unsigned reg)
{
	return iba_r(&sw->info->iba, reg, IBA_CMD_32);
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

	if (5 == info->use_iba) {
		return;
	}
	if (4 == info->use_iba)
		printk(KERN_WARNING " %s %x"NL, __func__, reg);
	data[0] = size;
	data[1] = reg;
	data[2] = val;
	rc = iba_req(info, data, NULL, NULL, iba_w_pre, NULL);
	if (!rc)
dbg_msg("w %x %x"NL, reg, size);
}  /* iba_w */

/**
 * iba_w8 - IBA 8-bit register write
 * @info:	The IBA instance.
 * @reg:	The register to write.
 * @val:	The value to write.
 *
 * This function writes a 8-bit register through IBA.
 */
static void iba_w8(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	iba_w(&sw->info->iba, reg, val, IBA_CMD_8);
}  /* iba_w8 */

/**
 * iba_w16 - IBA 16-bit register write
 * @info:	The IBA instance.
 * @reg:	The register to write.
 * @val:	The value to write.
 *
 * This function writes a 16-bit register through IBA.
 */
static void iba_w16(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	iba_w(&sw->info->iba, reg, val, IBA_CMD_16);
}  /* iba_w16 */

/**
 * iba_w24 - IBA 24-bit register write
 * @info:	The IBA instance.
 * @reg:	The register to write.
 * @val:	The value to write.
 *
 * This function writes a 24-bit register through IBA.
 */
static void iba_w24(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	iba_w(&sw->info->iba, reg, val, IBA_CMD_24);
}  /* iba_w24 */

/**
 * iba_w32 - IBA 32-bit register write
 * @info:	The IBA instance.
 * @reg:	The register to write.
 * @val:	The value to write.
 *
 * This function writes a 32-bit register through IBA.
 */
static void iba_w32(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	iba_w(&sw->info->iba, reg, val, IBA_CMD_32);
}  /* iba_w32 */

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
			*ptr = cpu_to_be32(*ptr);
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
		dbg_msg("%08x=%08x"NL, info->regs[i].cmd,
			info->regs[i].data[0]);
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
		if contain_reg(addr, cnt, REG_SW_IBA__4) {
			u32 *ptr = (u32 *) buf;
			u32 loc = (REG_SW_IBA__4 - addr) / 4;

			if (write)
				ptr[loc] = info->cfg;
		}
	} else {
		mult = 1;
		if (1 == cnt) {
#ifdef VERIFY_IBA
if (!dbg_iba_test) {
iba_test(info, 7);
dbg_iba_test = 1;
}
#endif
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
	init_completion(&info->done);
	rc = iba_xmit(info);
	if (rc) {
		iba_dbg_states(info);
		iba_to_spi(info->sw_dev, info);
		return 0;
	}
	wait = wait_for_completion_timeout(&info->done, info->delay_ticks);
	if (!wait) {
dbg_msg("burst to"NL);
		iba_dbg_states(info);
		iba_to_spi(info->sw_dev, info);
		return 0;
	}

	rc = post(info, data, NULL);
	rc *= 4;
	return rc;
}  /* iba_burst */

static void iba_r_buf(struct ksz_sw *sw, unsigned reg, void *buf, size_t count)
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
		buf = sw->info->iba.buf;
		count += start;
		count += 3;
		count &= ~3;
	}
	iba_burst(&sw->info->iba, reg, count, buf, 0,
		iba_get_pre, iba_get_post_be);
	if (orig_buf != buf)
		memcpy(orig_buf, &sw->info->iba.buf[start], orig_cnt);
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
	iba_cmd_set(info, IBA_CMD_WRITE, size, reg, val);
	reg &= ~3;
	size = IBA_CMD_32;
	while (cnt >= 4) {
		val = buf_to_val(buf, i, 4);
		reg += 4;
		iba_cmd_set(info, IBA_CMD_WRITE, size, reg, val);
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
		iba_cmd_set(info, IBA_CMD_WRITE, size, reg, val);
	}
	return info->fptr;
}  /* w_buf_pre */

static void iba_w_buf(struct ksz_sw *sw, unsigned reg, void *buf, size_t count)
{
	/* Not in multiple of 4. */
	if ((count & 3) || (reg & 3)) {
		u32 data[3];

		data[0] = reg;
		data[1] = count;
		iba_req(&sw->info->iba, data, NULL, buf, w_buf_pre,
			iba_set_post);
	} else {
		int i;
		u32 *src = buf;
		u32 *dst = (u32 *) sw->info->iba.buf;

		for (i = 0; i < count; i += 4)
			*dst++ = be32_to_cpu(*src++);
		buf = sw->info->iba.buf;
		iba_burst(&sw->info->iba, reg, count, buf, 1,
			iba_set_pre, iba_set_post);
	}
}  /* iba_w_buf */

static int iba_get(struct ksz_sw *sw, u32 reg, size_t count, void *buf)
{
	int rc;

	rc = iba_burst(&sw->info->iba, reg, count, buf, 0,
		iba_get_pre, iba_get_post_le);

	/*
	 * Return zero to let the calling program know the boundary must be
	 * 32-bit.
	 */
	if (4 == count && (reg & 3))
		rc = 0;
	return rc;
}  /* iba_get */

static int iba_set(struct ksz_sw *sw, u32 reg, size_t count, void *buf)
{
	return iba_burst(&sw->info->iba, reg, count, buf, 1,
		iba_set_pre, iba_set_post);
}  /* iba_set */

/**
 * r_mac_table_pre - IBA MAC table read pre-processing
 * @info:	The IBA instance.
 *
 * This routine prepares IBA for MAC table read operation.
 */
static void r_mac_table_pre(struct ksz_iba_info *info)
{
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_SW_ALU_VAL_A, 0);
	iba_cmd(info, IBA_CMD_READ, IBA_CMD_32, REG_SW_ALU_VAL_B);
	iba_cmd(info, IBA_CMD_READ, IBA_CMD_32, REG_SW_ALU_VAL_C);
	iba_cmd(info, IBA_CMD_READ, IBA_CMD_32, REG_SW_ALU_VAL_D);
}  /* r_mac_table_pre */

/**
 * r_mac_table_post - IBA MAC table read post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA MAC table read operation.
 *
 * Return number of registers read.
 */
static int r_mac_table_post(struct ksz_iba_info *info, void *out, void *obj)
{
	u16 *entry = out;
	struct ksz_mac_table *mac = obj;
	int i = 0;
	u32 data[5];

	memset(data, 0, sizeof(data));
	while (info->regs[i].cmd != (u32) -1) {
		if (IBA_CMD_READ == (info->regs[i].cmd >> IBA_CMD_S)) {
			u32 reg = (info->regs[i].cmd & IBA_CMD_ADDR_M);
			u32 size = (info->regs[i].cmd & IBA_CMD_32);

			switch (reg) {
			case REG_SW_ALU_VAL_A:
				data[0] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_SW_ALU_VAL_B:
				data[1] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_SW_ALU_VAL_C:
				data[2] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_SW_ALU_VAL_D:
				data[3] = iba_get_val(size,
					info->regs[i].data[0]);
				get_mac_table_info(mac, data);
				++mac;
				memset(data, 0, sizeof(data));
				break;
			case REG_SW_LUE_INDEX_0__2:
				data[4] = iba_get_val(size,
					info->regs[i].data[0]);
				if (entry) {
					*entry = (data[4] & ENTRY_INDEX_M) +
						1;
					++entry;
				}
				break;
			}
		}
		i++;
	}
	return i;
}  /* r_mac_table_post */

/**
 * w_mac_table_pre - IBA MAC table write pre-processing
 * @info:	The IBA instance.
 * @mac:	The MAC table entries.
 *
 * This routine prepares IBA for MAC table write operation.
 */
static void w_mac_table_pre(struct ksz_iba_info *info,
	struct ksz_mac_table *mac)
{
	u32 data[4];

	set_mac_table_info(mac, data);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_VAL_A,
		data[0]);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_VAL_B,
		data[1]);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_VAL_C,
		data[2]);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_VAL_D,
		data[3]);
}  /* w_mac_table_pre */

struct dyn_mac_param {
	u16 addr;
	u8 *src_addr;
	u16 src_fid;
};

/**
 * s_dyn_mac_pre - IBA dynamic MAC table set pre-processing
 * @info:	The IBA instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @src_fid:	The source FID.
 *
 * This helper routine prepares IBA for dynamic MAC table set operation.
 */
static u32 s_dyn_mac_pre(struct ksz_iba_info *info, u16 addr, u8 *src_addr,
	u16 src_fid)
{
	u32 ctrl;
	u32 data;

	ctrl = 0;
	if (addr) {
		data = (addr - 1) & ALU_DIRECT_INDEX_M;
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_SW_ALU_INDEX_1, data);
		ctrl |= ALU_DIRECT;
	} else {
		data = (u32) src_fid << ALU_FID_INDEX_S;
		data |= ((u32) src_addr[0] << 8) | src_addr[1];
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_SW_ALU_INDEX_0, data);
		data = ((u32) src_addr[2] << 24) |
			((u32) src_addr[3] << 16) |
			((u32) src_addr[4] << 8) | src_addr[5];
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_SW_ALU_INDEX_1, data);
	}
	ctrl |= ALU_START;
	return ctrl;
}  /* s_dyn_mac_pre */

/**
 * r_dyn_mac_pre - IBA dynamic MAC table read pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for dynamic MAC table read operation.
 *
 * Return the IBA frame pointer.
 */
static void *r_dyn_mac_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	struct dyn_mac_param *param = in;
	u8 *src_addr = param->src_addr;
	u16 src_fid = param->src_fid;
	u16 addr = param->addr;
	u32 ctrl;

	ctrl = s_dyn_mac_pre(info, addr, src_addr, src_fid);
	ctrl |= ALU_READ;

	/* Dynamic MAC table does not use USE_FID bit and does not clear it. */
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_VAL_B, 0);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_CTRL__4, ctrl);
	iba_cmd_set(info, IBA_CMD_WAIT_ON_0, IBA_CMD_32, REG_SW_ALU_CTRL__4,
		ALU_START);
	r_mac_table_pre(info);

	/* Hash read. */
	if (!addr) {
		iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_16,
			REG_SW_LUE_INDEX_0__2, 0);
	}
	return info->fptr;
}  /* r_dyn_mac_pre */

/**
 * iba_r_dyn_mac_hw - read from dynamic MAC table using IBA
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @src_fid:	The source FID.
 * @mac:	Buffer to store the MAC table entry.
 * @entry:	Buffer to store the actual entry if available.
 *
 * This function reads an entry of the dynamic MAC table using IBA.
 */
static int iba_r_dyn_mac_hw(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u16 src_fid, struct ksz_mac_table *mac, u16 *entry)
{
	struct dyn_mac_param data;

	data.addr = addr;
	data.src_addr = src_addr;
	data.src_fid = src_fid;
	return iba_req(&sw->info->iba, &data, entry, mac, r_dyn_mac_pre,
		r_mac_table_post);
}  /* iba_r_dyn_mac_hw */

/**
 * w_dyn_mac_pre - IBA dynamic MAC table write pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for dynamic MAC table write operation.
 *
 * Return the IBA frame pointer.
 */
static void *w_dyn_mac_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	struct ksz_mac_table *mac = obj;
	struct dyn_mac_param *param = in;
	u8 *src_addr = param->src_addr;
	u16 src_fid = param->src_fid;
	u16 addr = param->addr;
	u32 ctrl;

	ctrl = s_dyn_mac_pre(info, addr, src_addr, src_fid);
	ctrl |= ALU_WRITE;
	w_mac_table_pre(info, mac);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_CTRL__4, ctrl);
	return info->fptr;
}  /* w_dyn_mac_pre */

/**
 * iba_w_dyn_mac_hw - write to dynamic MAC table using IBA
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @src_fid:	The source FID.
 * @mac:	The MAC table entry.
 *
 * This function writes an entry of the dynamic MAC table using IBA.
 */
static int iba_w_dyn_mac_hw(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u16 src_fid, struct ksz_mac_table *mac)
{
	struct dyn_mac_param data;

	data.addr = addr;
	data.src_addr = src_addr;
	data.src_fid = src_fid;
	return iba_req(&sw->info->iba, &data, NULL, mac, w_dyn_mac_pre, NULL);
}  /* iba_w_dyn_mac_hw */

/**
 * start_dyn_mac_pre - IBA dynamic MAC table start pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for dynamic MAC table start operation.
 *
 * Return the IBA frame pointer.
 */
static void *start_dyn_mac_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 ctrl;

	ctrl = ALU_SEARCH;
	ctrl |= ALU_START;

	/* Dynamic MAC table does not use USE_FID bit and does not clear it. */
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_VAL_B, 0);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_CTRL__4, ctrl);
	return info->fptr;
}  /* start_dyn_mac_pre */

/**
 * iba_start_dyn_mac_hw - start dynamic MAC table search using IBA
 * @sw:		The switch instance.
 *
 * This function starts dynamic MAC table search using IBA.
 */
static int iba_start_dyn_mac_hw(struct ksz_sw *sw)
{
	return iba_req(&sw->info->iba, NULL, NULL, NULL, start_dyn_mac_pre,
		NULL);
}  /* iba_start_dyn_mac_hw */

/**
 * g_dyn_mac_pre - IBA dynamic MAC table retrieve pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for dynamic MAC table retrieve operation.
 *
 * Return the IBA frame pointer.
 */
static void *g_dyn_mac_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	r_mac_table_pre(info);
	return info->fptr;
}  /* g_dyn_mac_pre */

/**
 * iba_g_dyn_mac_hw - retrieve dynamic MAC table result using IBA
 * @sw:		The switch instance.
 * @mac:	Buffer to store the MAC table entry.
 *
 * This function retrieves dynamic MAC table result using IBA.
 */
static int iba_g_dyn_mac_hw(struct ksz_sw *sw, struct ksz_mac_table *mac)
{
	return iba_req(&sw->info->iba, NULL, NULL, mac, g_dyn_mac_pre,
		r_mac_table_post);
}  /* iba_g_dyn_mac_hw */

/**
 * stop_dyn_mac_pre - IBA dynamic MAC table stop pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for dynamic MAC table stop operation.
 *
 * Return the IBA frame pointer.
 */
static void *stop_dyn_mac_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_SW_ALU_CTRL__4, 0);
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_SW_ALU_CTRL__4, 0);
	return info->fptr;
}  /* stop_dyn_mac_pre */

/**
 * stop_dyn_mac_post - IBA dynamic MAC table stop post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA dynamic MAC table stop operation.
 *
 * Return number of registers read.
 */
static int stop_dyn_mac_post(struct ksz_iba_info *info, void *out, void *obj)
{
	u32 *data = out;
	int i = 0;

	while (info->regs[i].cmd != (u32) -1) {
		if (IBA_CMD_READ == (info->regs[i].cmd >> IBA_CMD_S)) {
			u32 reg = (info->regs[i].cmd & IBA_CMD_ADDR_M);
			u32 size = (info->regs[i].cmd & IBA_CMD_32);

			if (reg == REG_SW_ALU_CTRL__4)
				*data = iba_get_val(size,
					info->regs[i].data[0]);
		}
		i++;
	}
	return i;
}  /* stop_dyn_mac_post */

/**
 * iba_stop_dyn_mac_hw - stop dynamic MAC table search using IBA
 * @sw:		The switch instance.
 *
 * This function stops dynamic MAC table search using IBA.
 *
 * Return the last MAC table control.
 */
static u32 iba_stop_dyn_mac_hw(struct ksz_sw *sw)
{
	u32 ctrl;

	iba_req(&sw->info->iba, NULL, &ctrl, NULL, stop_dyn_mac_pre,
		stop_dyn_mac_post);
	return ctrl;
}  /* iba_stop_dyn_mac_hw */

/**
 * r_sta_mac_pre - IBA static MAC table read pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for static MAC table read operation.
 *
 * Return the IBA frame pointer.
 */
static void *r_sta_mac_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	int cnt = 0;
	int num = data[0];
	u32 *ctrl = &data[1];

	do {
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_SW_ALU_STAT_CTRL__4, *ctrl);
		iba_cmd_set(info, IBA_CMD_WAIT_ON_0, IBA_CMD_32,
			REG_SW_ALU_STAT_CTRL__4, ALU_STAT_START);
		r_mac_table_pre(info);
		++cnt;
		++ctrl;
	} while (cnt < num);
	return info->fptr;
}  /* r_sta_mac_pre */

/**
 * iba_r_sta_mac_hw - read from static MAC table using IBA
 * @sw:		The switch instance.
 * @ctrl:	The control values for read operation.
 * @num:	Number of entries to read.
 * @mac:	Buffer to hold the MAC table entries.
 *
 * This function reads from static MAC table using IBA.
 */
static int iba_r_sta_mac_hw(struct ksz_sw *sw, u32 ctrl[], int num,
	struct ksz_mac_table *mac)
{
	u32 data[MAX_IBA_MAC_ENTRIES + 1];

	if (num > MAX_IBA_MAC_ENTRIES)
		num = MAX_IBA_MAC_ENTRIES;
	data[0] = num;
	memcpy(&data[1], ctrl, sizeof(u32) * num);
	return iba_req(&sw->info->iba, data, NULL, mac, r_sta_mac_pre,
		r_mac_table_post);
}  /* iba_r_sta_mac_hw */

/**
 * w_sta_mac_pre - IBA static MAC table write pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for static MAC table write operation.
 *
 * Return the IBA frame pointer.
 */
static void *w_sta_mac_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	int cnt;
	int num = data[0];
	struct ksz_mac_table *mac = obj;

	for (cnt = 0; cnt < num; cnt++, data++) {
		w_mac_table_pre(info, mac);
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_SW_ALU_STAT_CTRL__4, data[1]);
		iba_cmd_set(info, IBA_CMD_WAIT_ON_0, IBA_CMD_32,
			REG_SW_ALU_STAT_CTRL__4, ALU_STAT_START);
		++mac;
	}
	return info->fptr;
}  /* w_sta_mac_pre */

/**
 * iba_w_sta_mac_hw - write to static MAC table using IBA
 * @sw:		The switch instance.
 * @ctrl:	The control values for write operation.
 * @num:	Number of entries to write.
 * @mac:	MAC table entries.
 *
 * This function writes to static MAC table using IBA.
 */
static int iba_w_sta_mac_hw(struct ksz_sw *sw, u32 ctrl[], int num,
	struct ksz_mac_table *mac)
{
	u32 data[MAX_IBA_MAC_ENTRIES + 1];

	if (num > MAX_IBA_MAC_ENTRIES)
		num = MAX_IBA_MAC_ENTRIES;
	data[0] = num;
	memcpy(&data[1], ctrl, sizeof(u32) * num);
	return iba_req(&sw->info->iba, data, NULL, mac, w_sta_mac_pre, NULL);
}  /* iba_w_sta_mac_hw */

/**
 * r_vlan_table_pre - IBA VLAN table read pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for VLAN table read operation.
 *
 * Return the IBA frame pointer.
 */
static void *r_vlan_table_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	u16 addr = data[3];
	u32 ctrl;
	int cnt = 0;
	int num = *((int *) obj);

	if (num > MAX_IBA_VLAN_ENTRIES)
		num = MAX_IBA_VLAN_ENTRIES;
	do {
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_16,
			REG_SW_VLAN_ENTRY_INDEX__2, addr);
		ctrl = VLAN_READ;
		ctrl |= VLAN_START;
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_8, REG_SW_VLAN_CTRL,
			ctrl);
		iba_cmd_set(info, IBA_CMD_WAIT_ON_0, IBA_CMD_8,
			REG_SW_VLAN_CTRL, VLAN_START);
		iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32,
			REG_SW_VLAN_ENTRY__4, 0);
		iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32,
			REG_SW_VLAN_ENTRY_UNTAG__4, 0);
		iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32,
			REG_SW_VLAN_ENTRY_PORTS__4, 0);
		++cnt;
		++addr;
	} while (cnt < num);
	return info->fptr;
}  /* r_vlan_table_pre */

/**
 * r_vlan_table_post - IBA VLAN table read post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA VLAN table read peration.
 *
 * Return number of registers read.
 */
static int r_vlan_table_post(struct ksz_iba_info *info, void *out, void *obj)
{
	int i = 0;
	u32 *data = out;
	int num = *((int *) obj);

	memset(data, 0, sizeof(u32) * num * READ_VLAN_ENTRY_SIZE);
	while (info->regs[i].cmd != (u32) -1) {
		if (IBA_CMD_READ == (info->regs[i].cmd >> IBA_CMD_S)) {
			u32 reg = (info->regs[i].cmd & IBA_CMD_ADDR_M);
			u32 size = (info->regs[i].cmd & IBA_CMD_32);

			switch (reg) {
			case REG_SW_VLAN_ENTRY__4:
				data[0] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_SW_VLAN_ENTRY_UNTAG__4:
				data[1] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_SW_VLAN_ENTRY_PORTS__4:
				data[2] = iba_get_val(size,
					info->regs[i].data[0]);
				data += READ_VLAN_ENTRY_SIZE;
				break;
			}
		}
		i++;
	}
	return i;
}  /* r_vlan_table_post */

/**
 * iba_r_vlan_hw - read from VLAN table using IBA
 * @sw:		The switch instance.
 * @data:	Buffer to hold the VLAN data.
 * @num:	Number of entries to read.
 *
 * This function reads from VLAN table using IBA.
 */
static int iba_r_vlan_hw(struct ksz_sw *sw, u32 data[], int num)
{
	return iba_req(&sw->info->iba, data, data, &num, r_vlan_table_pre,
		r_vlan_table_post);
}  /* iba_r_vlan_hw */

/**
 * w_vlan_table_pre - IBA VLAN table write pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for VLAN table write operation.
 *
 * Return the IBA frame pointer.
 */
static void *w_vlan_table_pre(struct ksz_iba_info *info, void *in,
	void *obj)
{
	u32 *data = in;
	u16 addr = data[3];
	u32 ctrl;
	int cnt;
	int num = *((int *) obj);

	if (num > MAX_IBA_VLAN_ENTRIES)
		num = MAX_IBA_VLAN_ENTRIES;
	for (cnt = 0; cnt < num; cnt++) {
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_SW_VLAN_ENTRY__4, data[0]);
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_SW_VLAN_ENTRY_UNTAG__4, data[1]);
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_SW_VLAN_ENTRY_PORTS__4, data[2]);
		addr = data[3];
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_16,
			REG_SW_VLAN_ENTRY_INDEX__2, addr);
		ctrl = VLAN_WRITE;
		ctrl |= VLAN_START;
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_8, REG_SW_VLAN_CTRL,
			ctrl);
		iba_cmd_set(info, IBA_CMD_WAIT_ON_0, IBA_CMD_8,
			REG_SW_VLAN_CTRL, VLAN_START);
		data += WRITE_VLAN_ENTRY_SIZE;
	}
	return info->fptr;
}  /* w_vlan_table_pre */

/**
 * iba_w_vlan_hw - write to VLAN table using IBA
 * @sw:		The switch instance.
 * @data:	VLAN data to write.
 * @num:	Number of entries to write.
 *
 * This function writes to VLAN table using IBA.
 */
static int iba_w_vlan_hw(struct ksz_sw *sw, u32 data[], int num)
{
	return iba_req(&sw->info->iba, data, NULL, &num, w_vlan_table_pre,
		NULL);
}  /* iba_w_vlan_hw */

#ifdef CONFIG_KSZ_HSR
/**
 * r_hsr_table_pre - IBA HSR table read pre-processing
 * @info:	The IBA instance.
 *
 * This routine prepares IBA for HSR table read operation.
 */
static void r_hsr_table_pre(struct ksz_iba_info *info)
{
	int i;

	for (i = 0; i < 7; i++) {
		iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32,
			REG_HSR_ALU_VAL_A + i * 4, 0);
	}
}  /* r_hsr_table_pre */

/**
 * r_hsr_table_post - IBA HSR table read post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA HSR table read operation.
 *
 * Return number of registers read.
 */
static int r_hsr_table_post(struct ksz_iba_info *info, void *out, void *obj)
{
	struct ksz_hsr_table *hsr = obj;
	int i = 0;
	u32 data[7];

	memset(data, 0, sizeof(data));
	while (info->regs[i].cmd != (u32) -1) {
		if (IBA_CMD_READ == (info->regs[i].cmd >> IBA_CMD_S)) {
			u32 reg = (info->regs[i].cmd & IBA_CMD_ADDR_M);
			u32 size = (info->regs[i].cmd & IBA_CMD_32);

			switch (reg) {
			case REG_HSR_ALU_VAL_A:
				data[0] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_HSR_ALU_VAL_B:
				data[1] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_HSR_ALU_VAL_C:
				data[2] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_HSR_ALU_VAL_D:
				data[3] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_HSR_ALU_VAL_E:
				data[4] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_HSR_ALU_VAL_F:
				data[5] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_HSR_ALU_VAL_G:
				data[6] = iba_get_val(size,
					info->regs[i].data[0]);
				get_hsr_table_info(hsr, data);
				++hsr;
				memset(data, 0, sizeof(data));
				break;
			}
		}
		i++;
	}
	return i;
}  /* r_hsr_table_post */

/**
 * w_hsr_table_pre - IBA HSR table write pre-processing
 * @info:	The IBA instance.
 * @mac:	The HSR table entries.
 *
 * This routine prepares IBA for HSR table write operation.
 */
static void w_hsr_table_pre(struct ksz_iba_info *info,
	struct ksz_hsr_table *hsr)
{
	u32 data[7];
	int i;

	set_hsr_table_info(hsr, data);
	for (i = 0; i < 7; i++) {
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_HSR_ALU_VAL_A + i * 4, data[i]);
	}
}  /* w_hsr_table_pre */

/**
 * s_hsr_pre - IBA HSR table set pre-processing
 * @info:	The IBA instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @path_id:	The path ID.
 *
 * This helper routine prepares IBA for HSR table set operation.
 */
static u32 s_hsr_pre(struct ksz_iba_info *info, u16 addr, u8 *src_addr,
	u8 path_id)
{
	u32 ctrl;
	u32 data;

	ctrl = 0;
	if (addr) {
		data = (addr - 1) & HSR_DIRECT_INDEX_M;
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_HSR_ALU_INDEX_2, data);
		ctrl |= HSR_DIRECT;
	} else {
		data = 0;
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_HSR_ALU_INDEX_0, data);
		data = ((u32) src_addr[0] << 8) | src_addr[1];
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_HSR_ALU_INDEX_1, data);
		data = ((u32) src_addr[2] << 24) |
			((u32) src_addr[3] << 16) |
			((u32) src_addr[4] << 8) | src_addr[5];
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_HSR_ALU_INDEX_2, data);
		data = path_id & HSR_PATH_INDEX_M;
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_HSR_ALU_INDEX_3, data);
	}
	ctrl |= HSR_START;
	return ctrl;
}  /* s_hsr_pre */

/**
 * r_hsr_pre - IBA HSR table read pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for HSR table read operation.
 *
 * Return the IBA frame pointer.
 */
static void *r_hsr_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	u16 addr = data[0];
	struct ksz_hsr_table *hsr = obj;
	u32 ctrl;

	ctrl = s_hsr_pre(info, addr, hsr->src_mac, hsr->path_id);
	ctrl |= HSR_READ;
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_HSR_ALU_CTRL__4,
		ctrl);
	iba_cmd_set(info, IBA_CMD_WAIT_ON_0, IBA_CMD_32, REG_HSR_ALU_CTRL__4,
		HSR_START);
	r_hsr_table_pre(info);
	return info->fptr;
}  /* r_hsr_pre */

/**
 * iba_r_hsr_hw - read from HSR table using IBA
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @hsr:	Buffer to store the HSR table entry.
 *
 * This function reads an entry of the HSR table using IBA.
 */
static int iba_r_hsr_hw(struct ksz_sw *sw, u16 addr,
	struct ksz_hsr_table *hsr)
{
	u32 data[1];

	data[0] = addr;
	return iba_req(&sw->info->iba, data, NULL, hsr, r_hsr_pre,
		r_hsr_table_post);
}  /* iba_r_hsr_hw */

/**
 * w_hsr_pre - IBA HSR table write pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for HSR table write operation.
 *
 * Return the IBA frame pointer.
 */
static void *w_hsr_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	struct ksz_hsr_table *hsr = obj;
	u16 addr = data[0];
	u32 ctrl;

	ctrl = s_hsr_pre(info, addr, hsr->src_mac, hsr->path_id);
	ctrl |= HSR_WRITE;
	w_hsr_table_pre(info, hsr);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_HSR_ALU_CTRL__4,
		ctrl);
	return info->fptr;
}  /* w_hsr_pre */

/**
 * iba_w_hsr_hw - write to HSR table using IBA
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @hsr:	The HSR table entry.
 *
 * This function writes an entry of the HSR table using IBA.
 */
static int iba_w_hsr_hw(struct ksz_sw *sw, u16 addr,
	struct ksz_hsr_table *hsr)
{
	u32 data[1];

	data[0] = addr;
	return iba_req(&sw->info->iba, data, NULL, hsr, w_hsr_pre, NULL);
}  /* iba_w_hsr_hw */

/**
 * start_hsr_pre - IBA HSR table start pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for HSR table start operation.
 *
 * Return the IBA frame pointer.
 */
static void *start_hsr_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 ctrl;

	ctrl = HSR_SEARCH;
	ctrl |= HSR_START;
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_HSR_ALU_CTRL__4,
		ctrl);
	return info->fptr;
}  /* start_hsr_pre */

/**
 * iba_start_hsr_hw - start HSR table search using IBA
 * @sw:		The switch instance.
 *
 * This function starts HSR table search using IBA.
 */
static int iba_start_hsr_hw(struct ksz_sw *sw)
{
	return iba_req(&sw->info->iba, NULL, NULL, NULL, start_hsr_pre, NULL);
}  /* iba_start_hsr_hw */

/**
 * g_hsr_pre - IBA HSR table retrieve pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for HSR table retrieve operation.
 *
 * Return the IBA frame pointer.
 */
static void *g_hsr_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	r_hsr_table_pre(info);
	return info->fptr;
}  /* g_hsr_pre */

/**
 * iba_g_hsr_hw - retrieve HSR table result using IBA
 * @sw:		The switch instance.
 * @hsr:	Buffer to store the HSR table entry.
 *
 * This function retrieves HSR table result using IBA.
 */
static int iba_g_hsr_hw(struct ksz_sw *sw, struct ksz_hsr_table *hsr)
{
	return iba_req(&sw->info->iba, NULL, NULL, hsr, g_hsr_pre,
		r_hsr_table_post);
}  /* iba_g_hsr_hw */

/**
 * stop_hsr_pre - IBA HSR table stop pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for HSR table stop operation.
 *
 * Return the IBA frame pointer.
 */
static void *stop_hsr_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 ctrl;

	ctrl = 0;
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_HSR_ALU_CTRL__4,
		ctrl);
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_HSR_ALU_CTRL__4, 0);
	return info->fptr;
}  /* stop_hsr_pre */

/**
 * stop_hsr_post - IBA HSR table stop post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA HSR table stop operation.
 *
 * Return number of registers read.
 */
static int stop_hsr_post(struct ksz_iba_info *info, void *out, void *obj)
{
	u32 *data = out;
	int i = 0;

	while (info->regs[i].cmd != (u32) -1) {
		if (IBA_CMD_READ == (info->regs[i].cmd >> IBA_CMD_S)) {
			u32 reg = (info->regs[i].cmd & IBA_CMD_ADDR_M);
			u32 size = (info->regs[i].cmd & IBA_CMD_32);

			if (reg == REG_HSR_ALU_CTRL__4)
				*data = iba_get_val(size,
					info->regs[i].data[0]);
		}
		i++;
	}
	return i;
}  /* stop_hsr_post */

/**
 * iba_stop_hsr_hw - stop HSR table search using IBA
 * @sw:		The switch instance.
 *
 * This function stops HSR table search using IBA.
 *
 * Return the last HSR table control.
 */
static u32 iba_stop_hsr_hw(struct ksz_sw *sw)
{
	u32 ctrl;

	iba_req(&sw->info->iba, NULL, &ctrl, NULL, stop_hsr_pre,
		stop_hsr_post);
	return ctrl;
}  /* iba_stop_hsr_hw */
#endif

/**
 * r_mib_cnt_pre - IBA MIB counter read pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for MIB counter read operation.
 *
 * Return the IBA frame pointer.
 */
static void *r_mib_cnt_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 ctrl;
	u32 *data = in;
	u32 *port_in = obj;
	int cnt;
	int num = data[0];
	uint p = port_in[0];
	u32 freeze = port_in[1];

	for (cnt = 0; cnt < num; cnt++, data++) {
		ctrl = data[1] & MIB_COUNTER_INDEX_M;
		ctrl <<= MIB_COUNTER_INDEX_S;
		ctrl |= MIB_COUNTER_READ;
		ctrl |= freeze;
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			PORT_CTRL_ADDR(p, REG_PORT_MIB_CTRL_STAT__4),
			ctrl);
		iba_cmd_set(info, IBA_CMD_WAIT_ON_1, IBA_CMD_32,
			PORT_CTRL_ADDR(p, REG_PORT_MIB_CTRL_STAT__4),
			MIB_COUNTER_VALID);
		iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32,
			PORT_CTRL_ADDR(p, REG_PORT_MIB_DATA), 0);
	}
	return info->fptr;
}  /* r_mib_cnt_pre */

/**
 * r_mib_cnt_post - IBA MIB counter read post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA MIB counter read peration.
 *
 * Return number of registers read.
 */
static int r_mib_cnt_post(struct ksz_iba_info *info, void *out, void *obj)
{
	u32 cmd;
	int i = 0;
	u32 *data = out;
	u32 *port_in = obj;
	uint p = port_in[0];

	while (info->regs[i].cmd != (u32) -1) {
		cmd = (info->regs[i].cmd >> IBA_CMD_S);
		if (IBA_CMD_READ == cmd || IBA_CMD_WAIT_ON_1 == cmd) {
			u32 reg = (info->regs[i].cmd & IBA_CMD_ADDR_M);
			u32 size = (info->regs[i].cmd & IBA_CMD_32);

#if 1
if (((reg >> 12) & 0xf) != p + 1)
dbg_msg(" ?? %s %x %x"NL, __func__, reg, p);
#endif
			reg &= ((1 << 12) - 1);
			switch (reg) {
			case REG_PORT_MIB_CTRL_STAT__4:
				data[0] = iba_get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_PORT_MIB_DATA:
				data[1] = iba_get_val(size,
					info->regs[i].data[0]);
				data += READ_MIB_ENTRY_SIZE;
				break;
			}
		}
		i++;
	}
	return i;
}  /* r_mib_cnt_post */

/**
 * iba_r_mib_cnt_hw - read MIB counters using IBA
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The addresses of the counters.
 * @num:	Number of entries to read.
 * @data:	Buffer to store the counters.
 *
 * This function reads MIB counters of the port using IBA.
 */
static int iba_r_mib_cnt_hw(struct ksz_sw *sw, uint port, u32 addr[], int num,
			    u32 data[])
{
	u32 data_in[MAX_IBA_MIB_ENTRIES + 1];
	u32 obj[2];
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);
	u32 freeze = cfg->freeze ? MIB_COUNTER_FLUSH_FREEZE : 0;
	uint p = port;

	obj[0] = p;
	obj[1] = freeze;
	if (num > MAX_IBA_MIB_ENTRIES)
		num = MAX_IBA_MIB_ENTRIES;
	data_in[0] = num;
	memcpy(&data_in[1], addr, sizeof(u32) * num);
	memset(data, 0, sizeof(u32) * num * READ_MIB_ENTRY_SIZE);
	return iba_req(&sw->info->iba, data_in, data, obj, r_mib_cnt_pre,
		r_mib_cnt_post);
}  /* iba_r_mib_cnt_hw */

#if defined(CONFIG_HAVE_KSZ9897)
/**
 * r_acl_table_pre - IBA ACL table read pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for ACL table read operation.
 *
 * Return the IBA frame pointer.
 */
static void *r_acl_table_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	uint *port = obj;
	u16 addr = data[4];
	u32 ctrl = (addr & PORT_ACL_INDEX_M);
	int i;

	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_8,
		PORT_CTRL_ADDR(*port, REG_PORT_ACL_CTRL_0), ctrl);
	iba_cmd_set(info, IBA_CMD_WAIT_ON_1, IBA_CMD_32,
		PORT_CTRL_ADDR(*port, REG_PORT_ACL_CTRL_0 & ~3),
		PORT_ACL_READ_DONE << 8);
	for (i = 0; i < 4; i++) {
		iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32,
			PORT_CTRL_ADDR(*port, REG_PORT_ACL_0 + 4 * i), 0);
	}
	return info->fptr;
}  /* r_acl_table_pre */

/**
 * r_acl_table_post - IBA ACL table read post-processing
 * @info:	The IBA instance.
 * @out:	The output pointer.
 * @obj:	The object pointer.
 *
 * This function retrieves the result of IBA ACL table read peration.
 *
 * Return number of registers read.
 */
static int r_acl_table_post(struct ksz_iba_info *info, void *out, void *obj)
{
	int i = 0;
	u32 *data = out;

	while (info->regs[i].cmd != (u32) -1) {
		if (IBA_CMD_READ == (info->regs[i].cmd >> IBA_CMD_S)) {
			u32 reg = (info->regs[i].cmd & IBA_CMD_ADDR_M);
			u32 size = (info->regs[i].cmd & IBA_CMD_32);

			reg &= ((1 << 12) - 1);
			switch (reg) {
			case REG_PORT_ACL_0:
				data[0] = iba_get_val(size,
					info->regs[i].data[0]);
				data[0] = cpu_to_be32(data[0]);
				break;
			case REG_PORT_ACL_4:
				data[1] = iba_get_val(size,
					info->regs[i].data[0]);
				data[1] = cpu_to_be32(data[1]);
				break;
			case REG_PORT_ACL_8:
				data[2] = iba_get_val(size,
					info->regs[i].data[0]);
				data[2] = cpu_to_be32(data[2]);
				break;
			case REG_PORT_ACL_C:
				data[3] = iba_get_val(size,
					info->regs[i].data[0]);
				data[3] = cpu_to_be32(data[3]);
				break;
			}
		}
		i++;
	}
	return i;
}  /* r_acl_table_post */

/**
 * iba_r_acl_hw - read from ACL table using IBA
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The ACL index.
 * @data:	Buffer to hold the ACL data.
 *
 * This function reads from ACL table of the port using IBA.
 */
static int iba_r_acl_hw(struct ksz_sw *sw, uint port, u16 addr, u8 data[])
{
	u32 *ptr_32 = (u32 *) data;

	memset(data, 0, sizeof(u32) * 4);
	ptr_32[4] = addr;
	return iba_req(&sw->info->iba, data, data, &port, r_acl_table_pre,
		r_acl_table_post);
}  /* iba_r_acl_hw */

/**
 * w_acl_table_pre - IBA ACL table write pre-processing
 * @info:	The IBA instance.
 * @in:		The input pointer.
 * @obj:	The object pointer.
 *
 * This function prepares IBA for ACL table write operation.
 *
 * Return the IBA frame pointer.
 */
static void *w_acl_table_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	uint *port = obj;
	u16 addr = data[4];
	u32 ctrl = (addr & PORT_ACL_INDEX_M) | PORT_ACL_WRITE;
	int i;

	for (i = 0; i < 4; i++) {
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			PORT_CTRL_ADDR(*port, REG_PORT_ACL_0 + 4 * i),
			be32_to_cpu(data[i]));
	}
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_8,
		PORT_CTRL_ADDR(*port, REG_PORT_ACL_CTRL_0), ctrl);
	iba_cmd_set(info, IBA_CMD_WAIT_ON_1, IBA_CMD_32,
		PORT_CTRL_ADDR(*port, REG_PORT_ACL_CTRL_0 & ~3),
		PORT_ACL_WRITE_DONE << 8);
	return info->fptr;
}  /* w_acl_table_pre */

/**
 * iba_w_acl_hw - write to ACL table using IBA
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The ACL index.
 * @data:	The ACL data to write.
 *
 * This function writes to ACL table of the port using IBA.
 */
static int iba_w_acl_hw(struct ksz_sw *sw, uint port, u16 addr, u8 data[])
{
	u32 *ptr_32 = (u32 *) data;

	ptr_32[4] = addr;
	return iba_req(&sw->info->iba, data, NULL, &port, w_acl_table_pre,
		NULL);
}  /* iba_w_acl_hw */
#endif

static struct ksz_sw_reg_ops sw_iba_ops = {
	.lock			= iba_lock,
	.unlock			= iba_unlock,

	.r8			= iba_r8,
	.r16			= iba_r16,
	.r24			= iba_r24,
	.r32			= iba_r32,
	.w8			= iba_w8,
	.w16			= iba_w16,
	.w24			= iba_w24,
	.w32			= iba_w32,

	.r			= iba_r_buf,
	.w			= iba_w_buf,

	.get			= iba_get,
	.set			= iba_set,

	.r_dyn_mac_hw		= iba_r_dyn_mac_hw,
	.w_dyn_mac_hw		= iba_w_dyn_mac_hw,
	.start_dyn_mac_hw	= iba_start_dyn_mac_hw,
	.g_dyn_mac_hw		= iba_g_dyn_mac_hw,
	.stop_dyn_mac_hw	= iba_stop_dyn_mac_hw,
	.r_sta_mac_hw		= iba_r_sta_mac_hw,
	.w_sta_mac_hw		= iba_w_sta_mac_hw,
	.r_vlan_hw		= iba_r_vlan_hw,
	.w_vlan_hw		= iba_w_vlan_hw,

#ifdef CONFIG_KSZ_HSR
	.r_hsr_hw		= iba_r_hsr_hw,
	.w_hsr_hw		= iba_w_hsr_hw,
	.start_hsr_hw		= iba_start_hsr_hw,
	.g_hsr_hw		= iba_g_hsr_hw,
	.stop_hsr_hw		= iba_stop_hsr_hw,
#endif

	.r_mib_cnt_hw		= iba_r_mib_cnt_hw,

#if defined(CONFIG_HAVE_KSZ9897)
	.r_acl_hw		= iba_r_acl_hw,
	.w_acl_hw		= iba_w_acl_hw,
#endif
};

/**
 * iba_rcv - Receive IBA response.
 * @info:	The IBA instance.
 * @skb:	The received socket buffer.
 *
 * This function processes IBA response.
 */
static int iba_rcv(struct ksz_iba_info *info, struct sk_buff *skb)
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
	struct iba_cmd *frame;
	struct iba_frame *iba;
	u8 *ptr;
	int ret = 1;
	u8 *rxdata = skb->data;
	int rxlen = skb->len;

	ptr = rxdata;
	ptr += ETH_ALEN * 2;
	iba = (struct iba_frame *) ptr;

	if (iba->tag.type != htons(info->tag_type) ||
	    iba->format.format != htons(IBA_FORMAT_KSZ98XX))
		goto out_drop;

if (dbg_iba)
dbg_msg(" iba rx: %x %x"NL, info->seqid, iba->tag.seqid);

	if (!info->cmds[0].cmd)
		goto out_drop;

#if 0
	dbg_msg("seq: %x"NL, iba->tag.seqid);
#endif
	if (iba->tag.seqid != info->seqid)
		goto out_debug;

	len = ntohs(iba->length);
	cnt = rxlen;
	if (len != cnt) {
		if (rxlen > 61 && len + 4 != cnt)
			dbg_msg("len: %d != %d"NL, len, cnt);
		if (len > cnt)
			len = cnt;
	}
	len -= ETH_ALEN * 2 + sizeof(struct iba_frame) -
		sizeof(struct iba_cmd);
	if (ntohs(iba->code) == IBA_CODE_NORMAL) {
#ifdef SHOW_IBA
		dbg_msg("normal"NL);
#endif
		cmd_shift = IBA_CMD_S;
	} else {
#ifdef SHOW_IBA
		dbg_msg("burst"NL);
#endif
		cmd_shift = IBA_BURST_S;
	}
	frame = &iba->cmd;
	j = 0;
	k = 0;
	while (len >= 4 && frame->cmd) {
		cmd = ntohl(frame->cmd);
		if (0xdeadbeef == cmd) {
dbg_msg("apb: %08x"NL, last_iba_addr);
			break;
		}
		cmds = cmd;
		addr = cmd & IBA_CMD_ADDR_M;
		i = 0;
		data = ntohl(frame->data[i++]);
		if (cmd != info->cmds[j].cmd || (IBA_BURST_S == cmd_shift
				&& data != info->cmds[j].data[0]))
			dbg_msg("?cmd %x=%x %x=%x"NL, info->cmds[j].cmd, cmd,
				info->cmds[j].data[0], data);
		cmd >>= cmd_shift;
		if (IBA_BURST_S == cmd_shift) {
			cnt = data;
			if (IBA_BURST_WRITE == cmd) {
#ifdef SHOW_IBA
				dbg_msg("w: %08x=%d"NL, addr, cnt);
#endif
#if 0
				i += cnt;
#else
				for (; i <= cnt; i++) {
					data = ntohl(frame->data[i]);
#if 0
					iba_chk_regs(info->sw_dev, cmds, data);
#endif
					cmds += 4;
#ifdef SHOW_IBA
					dbg_msg("%08x ", data);
#endif
				}
#ifdef SHOW_IBA
				if (cnt)
					dbg_msg(NL);
#endif
#endif
			} else if (IBA_BURST_READ == cmd) {
#ifdef SHOW_IBA
				dbg_msg("r: %08x=%d"NL, addr, cnt);
#endif
				info->regs[k].cmd = cmds;
				for (; i <= cnt; i++) {
					data = ntohl(frame->data[i]);
					info->regs[k++].data[0] = data;
					info->regs[k].cmd =
						info->regs[k - 1].cmd + 4;
#ifdef SHOW_IBA
					dbg_msg("%08x ", data);
#endif
				}
#ifdef SHOW_IBA
				if (cnt)
					dbg_msg(NL);
#endif
			} else
				break;
			len -= sizeof(u32) * cnt;
		} else {
			switch (cmd) {
			case IBA_CMD_READ:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef SHOW_IBA
				dbg_msg("r: ");
#endif
				break;
			case IBA_CMD_WRITE:
#if 0
				iba_chk_regs(info->sw_dev, cmds, data);
#endif
#ifdef SHOW_IBA
				dbg_msg("w: ");
#endif
				break;
			case IBA_CMD_WAIT_ON_0:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef SHOW_IBA
				dbg_msg("z: ");
#endif
				break;
			case IBA_CMD_WAIT_ON_1:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef SHOW_IBA
				dbg_msg("s: ");
#endif
				break;
			case IBA_CMD_WRITE_0:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef SHOW_IBA
				dbg_msg("0: ");
#endif
				break;
			case IBA_CMD_WRITE_1:
				info->regs[k].cmd = cmds;
				info->regs[k++].data[0] = data;
#ifdef SHOW_IBA
				dbg_msg("1: ");
#endif
				break;
			}
#ifdef SHOW_IBA
			dbg_msg("%08x=%08x"NL, addr, data);
#endif
		}
		j++;
		len -= sizeof(struct iba_cmd);
		frame = (struct iba_cmd *) &frame->data[i];
	}
#ifdef SHOW_IBA
	dbg_msg(NL);
#endif
	ptr = rxdata;
	if (len != 4)
		dbg_msg("?len: %d"NL, len);
	if (info->cmds[j].cmd != 0)
		dbg_msg("? %x"NL, info->cmds[j].cmd);
	if (len != 4 && info->cmds[j].cmd != 0) {
		for (i = 0; i < rxlen + ETH_ALEN * 2 + 2; i++) {
			dbg_msg("%02x ", ptr[i]);
			if (15 == (i % 16))
				dbg_msg(NL);
		}
		if (15 != (i % 16))
			dbg_msg(NL);
	}
	info->cmds[0].cmd = 0;
	info->regs[k].cmd = (u32) -1;
	info->respid = iba->tag.seqid;
if (dbg_iba) {
dbg_iba = 0;
dbg_msg("ok %x %x"NL, info->seqid, last_ok_iba);
}
last_ok_iba = info->respid;

	dev_kfree_skb_irq(skb);
	complete(&info->done);
	return 0;

out_debug:
dbg_iba = 1;
dbg_msg("last ok: %x"NL, last_ok_iba);
	dbg_msg("seq: %x"NL, info->seqid);
#if 0
	for (i = 0; i < sizeof(struct iba_frame) + 14; i++) {
		dbg_msg("%02x ", ptr[i]);
		if (15 == (i % 16))
			dbg_msg(NL);
	}
	if (15 != (i % 16))
		dbg_msg(NL);
#endif
	for (i = 0; i < ntohs(info->frame->length); i++) {
		dbg_msg("%02x ", info->packet[i]);
		if (15 == (i % 16))
			dbg_msg(NL);
	}
	if (15 != (i % 16))
		dbg_msg(NL);
	for (i = 0; i < rxlen; i++) {
		dbg_msg("%02x ", rxdata[i]);
		if (15 == (i % 16))
			dbg_msg(NL);
	}
	if (15 != (i % 16))
		dbg_msg(NL);

out_drop:
	return ret;
}  /* iba_rcv */

static struct iba_ops common_iba_ops = {
	.get_val		= iba_get_val,
	.cmd_data		= iba_cmd_data,
	.prepare_data		= iba_prepare_data,
	.assert			= assert_buf,
	.r_pre			= iba_r_pre,
	.r_post			= iba_r_post,
	.w_pre			= iba_w_pre,
	.get_post_be		= iba_get_post_be,
	.get_post_le		= iba_get_post_le,
	.get_pre		= iba_get_pre,
	.req			= iba_req,
	.reqs			= iba_reqs,
	.burst			= iba_burst,
};

static void ksz_iba_init(struct ksz_iba_info *iba, struct ksz_sw *sw)
{
	u32 data;
	u16 tag_type;

	/* Running nuttcp UDP TX can affect IBA communication if too short. */
	data = 200;
#ifdef CONFIG_KSZ_IBA_ONLY
	data = 800;
#endif
	iba->delay_ticks = msecs_to_jiffies(data);

	if (!iba->use_iba) {
		sw->ops->acquire(sw);
		data = sw->old->r32(sw, REG_SW_IBA__4);
		tag_type = (data & SW_IBA_FRAME_TPID_M);
		sw->ops->release(sw);
	} else
		tag_type = ETH_P_IBA;

	iba->sw_dev = sw;
	iba->packet = kzalloc(IBA_LEN_MAX, GFP_KERNEL);
	iba->buf = kzalloc(IBA_LEN_MAX, GFP_KERNEL);
	iba->data = kzalloc(IBA_BURST_CNT_MAX * sizeof(u32), GFP_KERNEL);
	iba->regs = kmalloc(IBA_BURST_CNT_MAX * sizeof(struct iba_cmd),
		GFP_KERNEL);
	iba->cmds = kmalloc(IBA_BURST_CNT_MAX * sizeof(struct iba_cmd) / 4,
		GFP_KERNEL);
	iba->frame = (struct iba_frame *) &iba->packet[ETH_ALEN * 2];
	iba->tag_type = tag_type;
	iba->dst[0] = 0x01;
	iba->dst[1] = 0x00;
	iba->dst[2] = 0x5E;
	iba->dst[3] = 0x00;
	iba->dst[4] = 0x01;
	iba->dst[5] = 0x81;
#ifndef CONFIG_KSZ_IBA_ONLY
#ifndef CAPTURE_IBA
	memcpy(iba->dst, sw->info->mac_addr, ETH_ALEN);
#endif
#endif
	iba->src[0] = 0x00;
#ifdef CAPTURE_IBA
	iba->src[0] = 0x01;
#endif
	iba->src[1] = 0x10;
	iba->src[2] = 0xA1;
	iba->src[3] = 0x98;
	iba->src[4] = 0x97;
	iba->src[5] = 0x81;

	init_completion(&iba->done);
	init_waitqueue_head(&iba->queue);
	mutex_init(&iba->lock);

	iba->ops = &common_iba_ops;

	iba_info = iba;
}  /* ksz_iba_init */

static void ksz_iba_exit(struct ksz_iba_info *iba)
{
	kfree(iba->cmds);
	kfree(iba->regs);
	kfree(iba->data);
	kfree(iba->buf);
	kfree(iba->packet);
}  /* ksz_iba_exit */

