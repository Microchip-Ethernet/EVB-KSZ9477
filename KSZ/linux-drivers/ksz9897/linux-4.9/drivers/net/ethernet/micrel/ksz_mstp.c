/**
 * Microchip MSTP code
 *
 * Copyright (c) 2016-2019 Microchip Technology Inc.
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


#include <crypto/hash.h>


#if 0
#define DBG_STP_STATE
#ifdef DBG_STP_STATE
#if 1
#endif
#if 0
#define DBG_STP_STATE_RX
#define DBG_STP_STATE_PROTO
#define DBG_STP_STATE_INFO
#define DBG_STP_STATE_ROLE_TR
#define DBG_STP_STATE_TX
#define DBG_STP_STATE_TR
#define DBG_STP_STATE_TOPOLOGY
#endif
#endif
#endif

#if 0
#define DBG_STP_PORT_BLOCK
#endif
#if 0
#define DBG_STP_PORT_FLUSH
#endif
#if 0
#define DBG_STP_ROLE
#endif
#if 0
#define DBG_STP_RX
#endif
#if 0
#define DBG_STP_TX
#endif


#ifndef FALSE
#define FALSE	0
#define TRUE	1
#endif


#define BPDU_TYPE_CONFIG	0
#define BPDU_TYPE_CONFIG_RSTP	2
#define BPDU_TYPE_TCN		0x80


#define TOPOLOGY_CHANGE		(1 << 0)
#define PROPOSAL		(1 << 1)
#define PORT_ROLE_S		2
#define PORT_ROLE_MASTER	0
#define PORT_ROLE_ALTERNATE	1
#define PORT_ROLE_ROOT		2
#define PORT_ROLE_DESIGNATED	3
#define LEARNING		(1 << 4)
#define FORWARDING		(1 << 5)
#define AGREEMENT		(1 << 6)
#define TOPOLOGY_CHANGE_ACK	(1 << 7)
#define MASTER			(1 << 7)


static u8 CFG_DIGEST_SIGN_KEY[] = {
	0x13, 0xAC, 0x06, 0xA6, 0x2E, 0x47, 0xFD, 0x51,
	0xF9, 0x5D, 0x2B, 0xA2, 0x43, 0xCD, 0x03, 0x46
};

#if 0
static u8 ALL_VID_CIST[] = {
	0,
	'A', 'L', 'L', 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,
	0xAC, 0x36, 0x17, 0x7F, 0x50, 0x28, 0x3C, 0xD4,
	0xB8, 0x38, 0x21, 0xD8, 0xAB, 0x26, 0xDE, 0x62
};

static u8 ALL_VID_MSTID_1[] = {
	0,
	'M', 'S', 'T', 'I', 'D', '1', 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,
	0xE1, 0x3A, 0x80, 0xF1, 0x1E, 0xD0, 0x85, 0x6A,
	0xCD, 0x4E, 0xE3, 0x47, 0x69, 0x41, 0xC7, 0x3B
};

static u8 VID_MOD_32_MSTID[] = {
	0,
	'M', 'S', 'T', 'I', 'D', 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,
	0x9D, 0x14, 0x5C, 0x26, 0x7D, 0xBE, 0x9F, 0xB5,
	0xD8, 0x93, 0x44, 0x1B, 0xE3, 0xBA, 0x08, 0xCE
};
#endif

static u16 get_bpdu_time(u16 time)
{
	int val;

	val = ntohs(time);

	/* Round up to whole second. */
	val += 255;
	return (u16)(val / 256);
}  /* get_bpdu_time */

static void set_bpdu_time(u16 *dst, u16 src)
{
	if (src < 256) {
		src *= 256;
		*dst = htons(src);
	} else
		*dst = 0xffff;
}  /* set_bpdu_time */

static void set_bpdu_times(struct bpdu *bpdu, struct mstp_times *t,
	struct mstp_times *h)
{
	set_bpdu_time(&bpdu->message_age, t->message_age);
	set_bpdu_time(&bpdu->max_age, t->max_age);
	set_bpdu_time(&bpdu->hello_time, h->hello_time);
	set_bpdu_time(&bpdu->forward_delay, t->forward_delay);
}  /* set_bpdu_times */

static void prep_bpdu(struct bpdu *bpdu, struct stp_prio *p,
	struct mstp_times *t, struct mstp_times *h)
{
	bpdu->protocol = 0;
	bpdu->flags = 0;
	memcpy(&bpdu->root, p, sizeof(struct stp_prio));
	set_bpdu_times(bpdu, t, h);
	bpdu->version_1_length = 0;
}  /* prep_bpdu */

static void prep_stp(struct bpdu *bpdu, struct stp_prio *p,
	struct mstp_times *t, struct mstp_times *h)
{
	prep_bpdu(bpdu, p, t, h);
	bpdu->version = 0;
	bpdu->type = BPDU_TYPE_CONFIG;
}  /* prep_stp */

static void prep_rstp(struct bpdu *bpdu, struct stp_prio *p,
	struct mstp_times *t, struct mstp_times *h)
{
	prep_bpdu(bpdu, p, t, h);
	bpdu->version = 2;
	bpdu->type = BPDU_TYPE_CONFIG_RSTP;
}  /* prep_rstp */

#if defined(DBG_STP_RX) || defined(DBG_STP_TX)
static void disp_bpdu(struct bpdu *bpdu)
{
	u8 role;

	if (BPDU_TYPE_TCN != bpdu->type) {
		dbg_msg("%04x=%02x%02x%02x%02x%02x%02x "
			"%04x=%02x%02x%02x%02x%02x%02x:"
			"%02x%02x %u\n",
			ntohs(bpdu->root.prio),
			bpdu->root.addr[0],
			bpdu->root.addr[1],
			bpdu->root.addr[2],
			bpdu->root.addr[3],
			bpdu->root.addr[4],
			bpdu->root.addr[5],
			ntohs(bpdu->bridge_id.prio),
			bpdu->bridge_id.addr[0],
			bpdu->bridge_id.addr[1],
			bpdu->bridge_id.addr[2],
			bpdu->bridge_id.addr[3],
			bpdu->bridge_id.addr[4],
			bpdu->bridge_id.addr[5],
			bpdu->port_id.prio, bpdu->port_id.num,
			ntohl(bpdu->root_path_cost));
		dbg_msg("%u %u %u %u  ",
			htons(bpdu->message_age) / 256,
			htons(bpdu->max_age) / 256,
			htons(bpdu->hello_time) / 256,
			htons(bpdu->forward_delay) / 256);
		dbg_msg("%02X:", bpdu->flags);
		if (bpdu->flags & TOPOLOGY_CHANGE_ACK)
			dbg_msg("K");
		else
			dbg_msg("-");
		if (bpdu->flags & AGREEMENT)
			dbg_msg("A");
		else
			dbg_msg("-");
		if (bpdu->flags & FORWARDING)
			dbg_msg("F");
		else
			dbg_msg("-");
		if (bpdu->flags & LEARNING)
			dbg_msg("L");
		else
			dbg_msg("-");
		role = bpdu->flags >> PORT_ROLE_S;
		role &= PORT_ROLE_DESIGNATED;
		switch (role) {
		case PORT_ROLE_ALTERNATE:
			dbg_msg("N");
			break;
		case PORT_ROLE_ROOT:
			dbg_msg("R");
			break;
		case PORT_ROLE_DESIGNATED:
			dbg_msg("D");
			break;
		default:
			if (BPDU_TYPE_CONFIG_RSTP == bpdu->type)
				dbg_msg("?");
			else
				dbg_msg("-");
		}
		if (bpdu->flags & PROPOSAL)
			dbg_msg("P");
		else
			dbg_msg("-");
		if (bpdu->flags & TOPOLOGY_CHANGE)
			dbg_msg("T");
		else
			dbg_msg("-");
	}
	dbg_msg("  %04x %u %02x",
		htons(bpdu->protocol),
		bpdu->version, bpdu->type);
	if (BPDU_TYPE_CONFIG_RSTP == bpdu->type)
		dbg_msg(" %u", bpdu->version_1_length);
	dbg_msg("\n");
	if (BPDU_TYPE_CONFIG_RSTP == bpdu->type && bpdu->version >= 3) {
		int i;
		int len;
		struct msti_cfg *cfg;
		struct mstp_bpdu *mstp = &bpdu->mstp;

		len = ntohs(mstp->version_3_length);
		len += 2;
		for (i = 0; i < 16; i++)
			dbg_msg("%02X", mstp->MCID.digest[i]);
		dbg_msg("  %u %u  ", mstp->MCID.selector,
			htons(mstp->MCID.revision));
		for (i = 0; i < 32; i++) {
			if (mstp->MCID.name[i] != 0)
				dbg_msg("%c", mstp->MCID.name[i]);
			else
				break;
		}
		dbg_msg("\n");
		dbg_msg("%04x=%02x%02x%02x%02x%02x%02x  %u %u  %u\n",
			ntohs(mstp->id.prio),
			mstp->id.addr[0],
			mstp->id.addr[1],
			mstp->id.addr[2],
			mstp->id.addr[3],
			mstp->id.addr[4],
			mstp->id.addr[5],
			ntohl(mstp->internal_root_path_cost),
			mstp->max_hops, len);
		len -= sizeof(struct mstp_bpdu);
		cfg = (struct msti_cfg *)(mstp + 1);
		while (len >= sizeof(struct msti_cfg)) {
			dbg_msg("%04x=%02x%02x%02x%02x%02x%02x  ",
				ntohs(cfg->root.prio),
				cfg->root.addr[0],
				cfg->root.addr[1],
				cfg->root.addr[2],
				cfg->root.addr[3],
				cfg->root.addr[4],
				cfg->root.addr[5]);
			if (cfg->flags & MASTER)
				dbg_msg("M");
			else
				dbg_msg("-");
			if (cfg->flags & AGREEMENT)
				dbg_msg("A");
			else
				dbg_msg("-");
			if (cfg->flags & FORWARDING)
				dbg_msg("F");
			else
				dbg_msg("-");
			if (cfg->flags & LEARNING)
				dbg_msg("L");
			else
				dbg_msg("-");
			role = cfg->flags >> PORT_ROLE_S;
			role &= PORT_ROLE_DESIGNATED;
			switch (role) {
			case PORT_ROLE_ALTERNATE:
				dbg_msg("N");
				break;
			case PORT_ROLE_ROOT:
				dbg_msg("R");
				break;
			case PORT_ROLE_DESIGNATED:
				dbg_msg("D");
				break;
			default:
				dbg_msg("M");
			}
			if (cfg->flags & PROPOSAL)
				dbg_msg("P");
			else
				dbg_msg("-");
			if (cfg->flags & TOPOLOGY_CHANGE)
				dbg_msg("T");
			else
				dbg_msg("-");
			dbg_msg("  %02x %02x %u %u\n",
				cfg->br_prio, cfg->port_prio, cfg->max_hops,
				ntohl(cfg->root_path_cost));
			cfg++;
			len -= sizeof(struct msti_cfg);
		}
	}
}
#endif

static struct bpdu *chk_bpdu(u8 *data, u16 *size)
{
	struct llc *llc = (struct llc *) &data[12];
	u16 len = ntohs(llc->len);

	if (len < 1500) {
		if (0x42 == llc->dsap &&
		    0x42 == llc->ssap &&
		    0x03 == llc->ctrl)
		if (size)
			*size = len - 3;
		return (struct bpdu *)(llc + 1);
	}
	return NULL;
}  /* chk_bpdu */


#define STP_TIMER_TICK		200
#define STP_TIMER_SCALE		1000

#define to_stp_timer(x)		((x) * STP_TIMER_SCALE)
#define from_stp_timer(x)	((x) / STP_TIMER_SCALE)
#define NEQ(x, y)		(abs((y) - (x)) >= STP_TIMER_SCALE)


#define BridgeIdentifier	(p->br->mvars[p->br->MSTI].br_id_)
#define BridgePriority		(p->br->mvars[p->br->MSTI].bridgePrio_)
#define BridgeTimes		(p->br->mvars[p->br->MSTI].bridgeTimes_)
#define rootPortId		(p->br->mvars[p->br->MSTI].rootPortId_)
#define rootPriority		(p->br->mvars[p->br->MSTI].rootPrio_)
#define rootTimes		(p->br->mvars[p->br->MSTI].rootTimes_)

#define timeSinceTC		(p->br->mvars[p->br->MSTI].TC_sec_)
#define cntTC			(p->br->mvars[p->br->MSTI].TC_cnt_)
#define isTC			(p->br->mvars[p->br->MSTI].TC_set_)

/* MigrateTime is only used internally for timer. */
#define MigrateTime		(p->br->vars.MigrateTime_)
#define TxHoldCount		(p->br->vars.TxHoldCount_)
#define ForceProtocolVersion	(p->br->vars.ForceProtocolVersion_)
#define MstConfigId		(p->br->vars.MstConfigId_)


#define edgeDelayWhile		(p->vars.timers[0])
#define fdWhile			(p->vars.timers[1])
#define helloWhen		(p->vars.timers[2])

#define mdelayWhile		(p->mvars[p->MSTI].timers[0])
#define rbWhile			(p->mvars[p->MSTI].timers[1])
#define rcvdInfoWhile		(p->mvars[p->MSTI].timers[2])
#define rrWhile			(p->mvars[p->MSTI].timers[3])
#define tcWhile			(p->mvars[p->MSTI].timers[4])
#define tcDetected		(p->mvars[p->MSTI].timers[5])
#define tcPropWhile		(p->mvars[p->MSTI].timers[6])

#define AdminEdgePort		(p->vars.admin_var.AdminEdgePort_)
#define AdminPortPathCost	(p->vars.admin_var.adminPortPathCost_)
#define AutoEdgePort		(p->vars.admin_var.AutoEdgePort_)
#define AutoIsolate		(p->vars.admin_var.AutoIsolate_)
#define enableBPDUrx		(p->vars.admin_var.enableBPDUrx_)
#define enableBPDUtx		(p->vars.admin_var.enableBPDUtx_)
#define adminPointToPointMAC	(p->vars.admin_var.adminPointToPointMAC_)
#define operPointToPointMAC	(p->vars.admin_var.operPointToPointMAC_)

#define ageingTime		(p->vars.stp_var.ageingTime_)
#define infoInternal		(p->vars.stp_var.infoInternal_)
#define isolate			(p->vars.stp_var.isolate_)
#define master			(p->vars.stp_var.master_)
#define mastered		(p->vars.stp_var.mastered_)
#define mcheck			(p->vars.stp_var.mcheck_)
#define newInfo			(p->vars.stp_var.newInfo_)
#define newInfoMsti		(p->vars.stp_var.newInfoMsti_)
#define operEdge		(p->vars.stp_var.operEdge_)
#define portEnabled		(p->vars.stp_var.portEnabled_)
#define rcvdBPDU		(p->vars.stp_var.rcvdBPDU_)
#define rcvdInternal		(p->vars.stp_var.rcvdInternal_)
#define rcvdRSTP		(p->vars.stp_var.rcvdRSTP_)
#define rcvdSTP			(p->vars.stp_var.rcvdSTP_)
#define rcvdTcAck		(p->vars.stp_var.rcvdTcAck_)
#define rcvdTcn			(p->vars.stp_var.rcvdTcn_)
#define restrictedRole		(p->vars.stp_var.restrictedRole_)
#define restrictedTcn		(p->vars.stp_var.restrictedTcn_)
#define sendRSTP		(p->vars.stp_var.sendRSTP_)
#define tcAck			(p->vars.stp_var.tcAck_)
#define tick			(p->vars.stp_var.tick_)
#define txCount			(p->vars.stp_var.txCount_)
#define ExternalPortPathCost	(p->vars.stp_var.PortPathCost_)

#define agree			(p->mvars[p->MSTI].stp_var.agree_)
#define agreed			(p->mvars[p->MSTI].stp_var.agreed_)
#define designatedPriority	(p->mvars[p->MSTI].stp_var.desgPrio_)
#define designatedTimes		(p->mvars[p->MSTI].stp_var.desgTimes_)
#define CISTdesignatedTimes	(p->mvars[0].stp_var.desgTimes_)
#define disputed		(p->mvars[p->MSTI].stp_var.disputed_)
#define fdbFlush		(p->mvars[p->MSTI].stp_var.fdbFlush_)
#define forward			(p->mvars[p->MSTI].stp_var.forward_)
#define forwarding		(p->mvars[p->MSTI].stp_var.forwarding_)
#define infoIs			(p->mvars[p->MSTI].stp_var.infoIs_)
#define CISTinfoIs		(p->mvars[0].stp_var.infoIs_)
#define learn			(p->mvars[p->MSTI].stp_var.learn_)
#define learning		(p->mvars[p->MSTI].stp_var.learning_)
#define msgPriority		(p->mvars[p->MSTI].stp_var.msgPrio_)
#define CISTmsgPriority		(p->mvars[0].stp_var.msgPrio_)
#define msgTimes		(p->mvars[p->MSTI].stp_var.msgTimes_)
#define portId			(p->mvars[p->MSTI].stp_var.portId_)
#define portPriority		(p->mvars[p->MSTI].stp_var.portPrio_)
#define CISTportPriority	(p->mvars[0].stp_var.portPrio_)
#define portTimes		(p->mvars[p->MSTI].stp_var.portTimes_)
#define CISTportTimes		(p->mvars[0].stp_var.portTimes_)
#define proposed		(p->mvars[p->MSTI].stp_var.proposed_)
#define proposing		(p->mvars[p->MSTI].stp_var.proposing_)
#define rcvdInfo		(p->mvars[p->MSTI].stp_var.rcvdInfo_)
#define rcvdMsg			(p->mvars[p->MSTI].stp_var.rcvdMsg_)
#define rcvdTc			(p->mvars[p->MSTI].stp_var.rcvdTc_)
#define reRoot			(p->mvars[p->MSTI].stp_var.reRoot_)
#define reselect		(p->mvars[p->MSTI].stp_var.reselect_)
#define role			(p->mvars[p->MSTI].stp_var.role_)
#define selected		(p->mvars[p->MSTI].stp_var.selected_)
#define selectedRole		(p->mvars[p->MSTI].stp_var.selectedRole_)
#define CISTselectedRole	(p->mvars[0].stp_var.selectedRole_)
#define sync			(p->mvars[p->MSTI].stp_var.sync_)
#define synced			(p->mvars[p->MSTI].stp_var.synced_)
#define tcProp			(p->mvars[p->MSTI].stp_var.tcProp_)
#define updtInfo		(p->mvars[p->MSTI].stp_var.updtInfo_)
#define InternalPortPathCost	(p->mvars[p->MSTI].stp_var.PortPathCost_)

#define bpduVersion		(p->vars.bpduVersion_)
#define bpduType		(p->vars.bpduType_)
#define bpduMCID		(p->vars.bpduMCID_)

#define bpduFlags		(p->mvars[p->MSTI].bpduFlags_)
#define bpduRole		(p->mvars[p->MSTI].bpduRole_)
#define bpduPriority		(p->mvars[p->MSTI].bpduPrio_)
#define bpduTimes		(p->mvars[p->MSTI].bpduTimes_)

#define DesignatedPort		(ROLE_DESIGNATED == role)
#define RootPort		(ROLE_ROOT == role)
#define AlternatePort		(ROLE_ALTERNATE == role)
#define BackupPort		(ROLE_BACKUP == role)
#define MasterPort		(ROLE_MASTER == role)
#define DisabledPort		(ROLE_DISABLED == role)

#define ForwardPort		\
	(DesignatedPort || RootPort || MasterPort)

#define BridgeFwdDelay		(BridgeTimes.forward_delay)
#define BridgeHelloTime		(BridgeTimes.hello_time)
#define BridgeMaxAge		(BridgeTimes.max_age)
#define BridgeMaxHops		(BridgeTimes.max_hops)

#define AdminEdge		AdminEdgePort
#define AutoEdge		AutoEdgePort

#define EdgeDelay()		(operPointToPointMAC ? MigrateTime : MaxAge)
#define forwardDelay()		(sendRSTP ? HelloTime : FwdDelay)

/* These times are in timer unit. */
#define FwdDelay		to_stp_timer(CISTdesignatedTimes.forward_delay)
#define HelloTime		to_stp_timer(CISTportTimes.hello_time)
#define MaxAge			to_stp_timer(CISTdesignatedTimes.max_age)

#define rstpVersion		(ForceProtocolVersion >= 2)
#define stpVersion		(ForceProtocolVersion < 2)


/* Shortcuts for some common qualifications. */
#define canChange		(selected && !updtInfo)
#define canSend			\
	((txCount < TxHoldCount) && (helloWhen != 0))

/*
 * agree means the port accepts incoming Designated Port, and AGREEMNT flag is
 * set.
 * It means all ports are synchronized so that no loop occurs.
 *
 * agreed means the proposing Designated Port receives AGREEMENT and so can
 * stop proposing and can enable learning and forwarding immediately.
 * Not operPointToPointMAC causes that not to happen and the Designated Port
 * keeps proposing, but half-duplex connection will cause operPointToPoint to
 * be FALSE.  In old time half-duplex was associated with hub and what is
 * called Shared Media.  The sent BPDU may be dropped because of collisions,
 * but that is not what happens here.
 * agreed is used to qualify synced after betterorsameInfo call for Designated
 * Port.  It is set when the port becomes forwarding, but if the port is
 * already forwarding it is never set and so synced cannot be set, causing
 * the Root Port not to send anything back to the Designated Port.
 *
 * proposing means the Designated Port is asking approval before opening the
 * port, and PROPOSAL flag is set.
 * It is set when the Designated Port is not forwarding.  It is reset when
 * AGREEMENT flag is received, or when infoIs is set to Mine.
 * Does it mean in !operPointToPointMAC the PROPOSAL flag will be dropped when
 * the Designated Port information is changed?!
 * There is a case that after becoming Root Port proposing is not reset.  It
 * should not be set in DESIGNATED_PROPOSE state.
 *
 * proposed means receiving PROPOSAL from Desginated Port.  It will be reset
 * either agree is TRUE or not.  The only difference is setSyncTree will be
 * called when agree is FALSE.
 *
 * sync is set in the setSyncTree call.  It is reset when synced is set.
 * It is reset for Root Port but not Alternate Port.  It is required to be
 * FALSE for Designated Port to move to learning state.  If it is TRUE then
 * Designated Port moves to discarding state.
 *
 * synced is used in the allSynced call.  That call is only used to get into
 * _AGREED states in which proposed is reset and agree is set and a BPDU will
 * be sent.  It is also needed when Master Port goes to learning state.
 * proposed and synced are mutually exclusive.
 *
 * master is set for Root Port or Designated Port in MSTI when one of the ports
 * is Master Port.  It is also set when mastered is set in a Root Port or
 * Designated Port.  It is used for later enhancement.
 *
 * mastered means receiving MASTER.  It is used for later enhancement.
 *
 * operEdge means the port is not connected to another bridge so some variables
 * will be automatically set to put the port in forwarding state.
 *
 * isolate means the port will not go into learning state when it does not
 * receive any BPDU.  This means operEdge is also not set due to AdminEdge or
 * AutoEdge not being configured.
 *
 * AutoIsolate sets proposing when the port becomes Designated Port.  It has an
 * effect of going to isolated mode without sending a Proposal.
 *
 * tcAck is used by Designated Port to set TOPOLOGY_CHANGE_ACK flag in response
 * of TOPOLOGY_CHANGE flag.  It is no longer used in MSTP and the flag is
 * replaced with MASTER flag.  The topology change notification is
 * automatically shutdown after 3 seconds.  That may be why acknowledgement is
 * not needed.
 *
 * rcvdTc is not accepted from inferior designated port.
 *
 * rcvdTcAck is used by Root Port to stop sending topology change immediately.
 *
 * newInfo is set to send out BPDU.  It is checked periodically so that
 * Designated Port can always send but Root Port only sends when there is a
 * topology change.
 * It is set when agree is set the first time.  However, Alternate Port does
 * not always send after becoming one.
 * There is a case a BPDU is sent during initializion when the port role is not
 * defined yet.  It should be handled in the _DISABLE_PORT state.
 * HelloTime is zero when Port Transmit state machine starts.  Because of that
 * PERIODIC is called instead.  Is that the original intention?
 * Moving the Port Transmission state machine to last fixes this problem.
 * However, newInfo is still not cleared because of the OR operation.
 *
 * reselect means port information is being changed so selected will not be set
 * to TRUE.  Typically selected is set to FALSE while reselect is set so that
 * role selection is done.
 *
 * selected means the role selection is completed so states can be changed.  It
 * is set to FALSE when infoIs is changed.
 *
 * updtInfo is set when the port is becoming Designated Port or its parameters
 * are changed.  It is reset when the Designated Port sets infoIs to Mine.  It
 * is explicitly set to FALSE for other port roles.
 * !updtInfo is required in many state changes.  Basically it means the
 * Designated Port needs to set infoIs to Mine before moving to other states.
 * There is a case that a Designated Port changing to Root Port will set
 * proposing, even though it will not be a Designated Port.
 *
 * infoIs is initialized in Port Information state machine, so it should be run
 * before Port Role Selection state machine.
 *
 * reRoot is set by new Root Port to force prior Root Ports to Discarding
 * before it becomes forwarding.  It is mostly done by a prior Alternate Port
 * or a Designated Port not in forwarding state.
 *
 * selectedRole is initialized by updtRoleDisabledTree in INIT_BRIDGE, so
 * Port Role Selection state machine should be run before Port Role Transitions
 * state machine.
 *
 * There is a problem that selectedRole is changed to DesignatedPort but
 * DISABLE_PORT changes role like selectedRole is DisabledPort and is stuck in
 * DISABLED_PORT state.  Fixed in MSTP to explicitly set role to DisabledPort.
 *
 * MaxAge is initialized in updtRolesTree, so INIT_PORT should be called after
 * that.
 */


#define CMP(first, second)	memcmp(&first, &second, sizeof(first))
#define COPY(first, second)	memcpy(&first, &second, sizeof(first))
#define ZERO(first)		memset(&first, 0, sizeof(first))


#define COPY_PRIO(vector, p, id)	\
	memcpy(&(vector.prio), &p, sizeof(p));	\
	memcpy(&(vector.port_id), &id, sizeof(id));


static void copy_prio(struct mstp_prio *m, void *p)
{
	struct stp_prio *s = p;

	memcpy(&m->root, &s->root, sizeof(struct _bridge_id) + sizeof(u32) +
		sizeof(struct _bridge_id));
	memcpy(&m->bridge_id, &s->bridge_id, sizeof(struct _bridge_id));
	memcpy(&m->port_id, &s->port_id, sizeof(struct _port_id));
	m->internal_root_path_cost = 0;
}

static int superiorPriority(struct mstp_prio *first, struct mstp_prio *second)
{
	int prio;

	prio = memcmp(first, second, sizeof(struct mstp_prio));
	if (prio > 0 &&
	    !memcmp(first->bridge_id.addr, second->bridge_id.addr, ETH_ALEN) &&
	    first->port_id.num == second->port_id.num)
		prio = -256;
#ifdef DBG_STP_ROLE
if (prio < -127)
dbg_msg("  %s same br/port\n", __func__);
#endif
	return (prio < 0);
}

static void dbgPriority(struct mstp_prio *prio, struct _port_id *id)
{
	int j;
	u8 *data;

	data = (u8 *) prio;
	for (j = 0; j < sizeof(struct mstp_prio); j++) {
		if (8 == j || 12 == j || 20 == j || 24 == j)
			dbg_msg(" ");
		dbg_msg("%02x", data[j]);
	}
	if (id) {
		dbg_msg(" ");
		data = (u8 *) id;
		for (j = 0; j < sizeof(struct _port_id); j++)
			dbg_msg("%02x", data[j]);
	}
	dbg_msg("\n");
}

static int betterSamePriority(struct mstp_prio *first, struct mstp_prio *second)
{
	int prio;

	prio = memcmp(first, second, sizeof(struct mstp_prio));
	return (prio <= 0);
}

static int betterVector(struct mstp_vector *first, struct mstp_vector *second)
{
	int prio;

	prio = memcmp(&first->prio, &second->prio, sizeof(struct mstp_prio));
	if (!prio) {
#ifdef DBG_STP_ROLE
dbg_msg(" same prio\n");
		dbgPriority(&first->prio, &first->port_id);
		dbgPriority(&second->prio, &second->port_id);
#endif
		prio = memcmp(&first->port_id, &second->port_id,
			sizeof(struct _port_id));
	}
	return (prio < 0);
}


static int next_msti(struct ksz_stp_bridge *br, int msti)
{
	int cnt = NUM_OF_MSTI - msti - 1;

	while (!(br->MSTI_enabled & (1 << msti)) && cnt > 0) {
		++msti;
		--cnt;
	}
	return msti;
}

#define FOREACH_P_IN_T(statements...)					\
{									\
	int c;								\
	for (c = 0; c < p->br->port_cnt; c++) {				\
		p = &p->br->ports[c];					\
		p->MSTI = p->br->MSTI;					\
		statements						\
	}								\
}

#define FOREACH_T_IN_P(statements...)					\
{									\
	int c;								\
	int m;								\
if (p->MSTI) \
dbg_msg(" !!! %s %d %d\n", __func__, p->port_index, p->MSTI); \
	for (c = 0, m = 0; c < p->br->MSTI_cnt; c++, m++) {		\
		m = next_msti(p->br, m);				\
		p->MSTI = m;						\
		statements						\
	}								\
	p->MSTI = 0;							\
}

#define FOREACH_M_IN_P(statements...)					\
{									\
	int c;								\
	int m;								\
if (p->MSTI) \
dbg_msg(" !!! %s\n", __func__); \
	for (c = 1, m = 1; c < p->br->MSTI_cnt; c++, m++) {		\
		m = next_msti(p->br, m);				\
		p->MSTI = m;						\
		statements						\
	}								\
	p->MSTI = 0;							\
}


#define PATH_COST		20000000

static uint computePathCost(int speed)
{
	if (speed > 0)
		return speed < PATH_COST ? PATH_COST / speed : 1;
	else
		return PATH_COST * 10;
}  /* computePathCost */

static int checkP2P(struct ksz_stp_port *p)
{
	u8 p2p;

	if (ADMIN_P2P_AUTO == adminPointToPointMAC)
		p2p = !!p->duplex;
	else
		p2p = (ADMIN_P2P_FORCE_TRUE == adminPointToPointMAC);
	if (p2p != operPointToPointMAC) {
		operPointToPointMAC = p2p;
		return TRUE;
	}
	return FALSE;
}  /* checkP2P */

static int checkPathCost(struct ksz_stp_port *p)
{
	uint pathCost;

	if (!AdminPortPathCost)
		pathCost = computePathCost(p->speed);
	else
		pathCost = AdminPortPathCost;
	if (pathCost != ExternalPortPathCost) {
		ExternalPortPathCost = pathCost;
		InternalPortPathCost = pathCost;
		reselect = TRUE;
		selected = FALSE;
		FOREACH_M_IN_P(
			InternalPortPathCost = pathCost;
			reselect = TRUE;
			selected = FALSE;
		)
		return TRUE;
	}
	return FALSE;
}  /* checkPathCost */

static int checkParameters(int hello_time, int max_age, int fwd_delay)
{
	if (max_age < 6 || max_age > 40)
		return FALSE;
	if (fwd_delay < 4 || fwd_delay > 30)
		return FALSE;
	if (2 * (fwd_delay - 1) < max_age)
		return FALSE;
	if (max_age < 2 * (hello_time + 1))
		return FALSE;
	return TRUE;
}  /* checkParameters */

static int make_hmac_md5(void *in_data, int len, u8 *out_data)
{
	struct crypto_ahash *hmac_md5;
	struct ahash_request req;
	struct scatterlist sg[1];
	int err;

	hmac_md5 = crypto_alloc_ahash("hmac(md5)", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(hmac_md5)) {
		return -ENOMEM;
	}

	err = crypto_ahash_init(&req);
	if (err)
		goto out;
	err = crypto_ahash_setkey(hmac_md5, CFG_DIGEST_SIGN_KEY, 16);
	if (err)
		goto out;

	sg_init_one(sg, in_data, len);
	ahash_request_set_tfm(&req, hmac_md5);
	ahash_request_set_callback(&req, 0, NULL, NULL);
	ahash_request_set_crypt(&req, sg, out_data, len);
	err = crypto_ahash_digest(&req);
	ahash_request_zero(&req);

out:
	crypto_free_ahash(hmac_md5);
	return err;
}

static void recalc_cfg_digest(struct ksz_stp_port *p)
{
	int vid;
	struct ksz_stp_bridge *br = p->br;
	struct ksz_stp_info *stp = br->parent;
	struct ksz_sw *sw = stp->sw_dev;

	br->vid2mstid[0] = br->vid2mstid[NUM_OF_VID + 1] = 0;
	for (vid = 1; vid <= NUM_OF_VID; vid++)
		br->vid2mstid[vid] =
			htons(sw->info->fid2mstid[sw->info->vid2fid[vid]]);

	make_hmac_md5(br->vid2mstid, sizeof(br->vid2mstid),
		MstConfigId.digest);
}

static void sw_cfg_forwarding(struct ksz_sw *sw, uint port, bool open)
{
	struct ksz_sw_info *info = sw->info;
	int i = info->port_cfg[port].mstp;
	u8 member = info->member[i];
	uint m = BIT(port);

	if (open)
		member |= m;
	else
		member &= ~m;
	if (member != info->member[i]) {
		info->member[i] = member;
		bridge_change(sw);
#ifdef CONFIG_KSZ_MRP
		if (open && (sw->features & MRP_SUPPORT)) {
			struct mrp_info *mrp = &sw->mrp;

			mrp_open_port(mrp, port);
		}
#endif
	}
}  /* sw_cfg_forwarding */

static void doFlush_(struct ksz_stp_port *p)
{
	struct ksz_stp_info *stp = p->br->parent;
	struct ksz_sw *sw = stp->sw_dev;
	int i = p->port_index;
#ifdef DBG_STP_PORT_FLUSH
	struct ksz_stp_port *q;
	struct ksz_stp_dbg_times *x;
	struct ksz_stp_dbg_times *y;
#endif

	if (operEdge) {
dbg_msg(" no flush\n");
		fdbFlush = FALSE;
		return;
	}
	sw->ops->acquire(sw);
	port_cfg_mstp(sw, i, p->MSTI);
	sw_flush_dyn_mac_table(sw, i);
	sw->ops->release(sw);
	fdbFlush = FALSE;
#ifdef DBG_STP_PORT_FLUSH
	q = p;
	y = &q->dbg_times[p->MSTI];
	for (i = 0; i < p->br->port_cnt; i++) {
		p = &p->br->ports[i];
		if (q == p)
			continue;
		x = &p->dbg_times[p->MSTI];
		if (y->lastPriority.port_id.num) {
			int cmp = memcmp(&y->lastPriority.bridge_id,
				&x->downPriority.bridge_id,
				sizeof(struct _bridge_id));
			if (!cmp && x->learn_jiffies) {
dbg_msg(" %ld [%ld] %02x%02x ", jiffies - y->alt_jiffies,
jiffies - x->learn_jiffies, y->lastPriority.port_id.prio, y->lastPriority.port_id.num);
				x->learn_jiffies = 0;
				y->lastPriority.port_id.num = 0;
				y->learn_jiffies = 0;
				y->alt_jiffies = 0;
			}
		}
	}
	p = q;
	switch (y->role_ & 0x3) {
	case PORT_ROLE_ROOT:
		dbg_msg("  R");
		break;
	case PORT_ROLE_ALTERNATE:
		dbg_msg("  A");
		break;
	case PORT_ROLE_DESIGNATED:
		if (RootPort)
			dbg_msg("  r");
		else if (AlternatePort)
			dbg_msg("  a");
		else
			dbg_msg("  u");
		break;
	default:
		if (DisabledPort)
			dbg_msg("  Z");
		else
			dbg_msg("  M");
		break;
	}
dbg_msg("  F:%d:%d\n", q->port_index, q->MSTI);
#endif
}  /* doFlush_ */

#define doFlush()			doFlush_(p)

static void stp_chk_flush(struct ksz_stp_port *p)
{
#ifdef DBG_STP_PORT_FLUSH
	struct ksz_stp_port *q;
	struct ksz_stp_bridge *br = p->br;
	uint i;
	struct ksz_stp_dbg_times *x = &p->dbg_times[p->MSTI];
	struct ksz_stp_dbg_times *y;

	if (bpduRole == x->role_)
		return;
#if 0
dbg_msg("%d:%d %d %d %d %s\n", p->port_index, p->MSTI, bpduRole,
rcvdTc, learning, __func__);
#endif
	x->role_ = bpduRole;
	if (rcvdTc || !learning) {
		int flush = 0;

		for (i = 0; i < br->port_cnt; i++) {
			q = &br->ports[i];
			if (q == p)
				continue;
			y = &q->dbg_times[p->MSTI];
			if (y->downPriority.port_id.num) {
				int cmp = memcmp(&y->downPriority.bridge_id,
					&msgPriority.bridge_id,
					sizeof(struct _bridge_id));
				if (!cmp) {
					if (learning)
						x->learn_jiffies = jiffies;
					flush = q->port_index + 1;
					y->role_ = ROLE_ALT_BACKUP | 0x80;
					break;
				}
			}
		}
dbg_msg("  %s %d:%d=%d\n", __func__, p->port_index, p->MSTI, flush);
	}
	if (bpduRole == ROLE_ALT_BACKUP)
		x->alt_jiffies = jiffies;
	if (bpduRole == ROLE_ROOT) {
		COPY(x->downPriority, msgPriority);
		COPY(x->lastPriority, msgPriority);
	}
#endif
}

static int allSynced_(struct ksz_stp_port *p)
{
	struct ksz_stp_port *q = p;
	int ret = TRUE;
	int all_others = FALSE;
	int skip_root = FALSE;

	if (DesignatedPort || MasterPort)
		all_others = TRUE;
	else if (!DisabledPort)
		skip_root = TRUE;

	/* Check only when role is not in transition. */
	FOREACH_P_IN_T(
		if (!(selected && (role == selectedRole) && !updtInfo)) {
#if 0
dbg_msg(" allSync: %d= %d %d %d %d\n", i, selected, role, selectedRole, synced);
#endif
			ret = FALSE;
			break;
		} else {
			if ((all_others && p == q) ||
			    (skip_root && RootPort))
				continue;
			if (!synced) {
				ret = FALSE;
				break;
			}
		}
	)
	return ret;
}

#define allSynced()			allSynced_(p)

/* Called in PortTransmit state machine only. */
static int allTransmitReady_(struct ksz_stp_port *p)
{
	int ret = TRUE;

	FOREACH_T_IN_P(
		if (!selected || updtInfo) {
			ret = FALSE;
			break;
		}
	)
	return ret;
}

#define allTransmitReady()		allTransmitReady_(p)

static int cist_(struct ksz_stp_port *p)
{
	return 0 == p->MSTI;
}

#define cist()				cist_(p)

static int cistRootPort_(struct ksz_stp_port *p)
{
	int ret;
	int MSTI = p->MSTI;

	p->MSTI = 0;
	ret = (ROLE_ROOT == role);
	p->MSTI = MSTI;
	return ret;
}

#define cistRootPort()			cistRootPort_(p)

static int cistDesignatedPort_(struct ksz_stp_port *p)
{
	int ret;
	int MSTI = p->MSTI;

	p->MSTI = 0;
	ret = (ROLE_DESIGNATED == role);
	p->MSTI = MSTI;
	return ret;
}

#define cistDesignatedPort()		cistDesignatedPort_(p)

static int msti_(struct ksz_stp_port *p)
{
	return p->MSTI > 0;
}

#define msti()				msti_(p)

/* Called in PortTransmit state machine only. */
static int mstiDesignatedOrTCpropagatingRootPort_(struct ksz_stp_port *p)
{
	int ret = FALSE;

	FOREACH_M_IN_P(
		if (DesignatedPort || (RootPort && (tcWhile != 0))) {
			ret = TRUE;
			break;
		}
	)
	return ret;
}

#define mstiDesignatedOrTCpropagatingRootPort()	\
	mstiDesignatedOrTCpropagatingRootPort_(p)

/* Called in PortTransmit state machine only. */
static int mstiMasterPort_(struct ksz_stp_port *p)
{
	int ret = FALSE;

	FOREACH_M_IN_P(
		if (MasterPort) {
			ret = TRUE;
			break;
		}
	)
	return ret;
}

#define mstiMasterPort()		mstiMasterPort_(p)

static int rcvdAnyMsg_(struct ksz_stp_port *p)
{
	int ret = FALSE;

	FOREACH_T_IN_P(
		if (rcvdMsg) {
			ret = TRUE;
			break;
		}
	)
	return ret;
}

#define rcvdAnyMsg()			rcvdAnyMsg_(p)

static int rcvdCistMsg_(struct ksz_stp_port *p)
{
	int ret = FALSE;

	if (rcvdMsg)
		ret = TRUE;
	return ret;
}

#define rcvdCistMsg()			rcvdCistMsg_(p)

static int rcvdMstiMsg_(struct ksz_stp_port *p)
{
	int MSTI = p->MSTI;
	int ret = TRUE;

	p->MSTI = 0;
	if (rcvdMsg)
		ret = FALSE;
	p->MSTI = MSTI;
	if (!rcvdMsg)
		ret = FALSE;
	return ret;
}

#define rcvdMstiMsg()			rcvdMstiMsg_(p)

static int reRooted_(struct ksz_stp_port *p)
{
	struct ksz_stp_port *q = p;
	int ret = TRUE;

	FOREACH_P_IN_T(
		if (p == q)
			continue;
		if (0 != rrWhile) {
			ret = FALSE;
			break;
		}
	)
	return ret;
}

#define reRooted()			reRooted_(p)

static int updtCistInfo_(struct ksz_stp_port *p)
{
	int ret = FALSE;

	ret = updtInfo;
	return ret;
}

#define updtCistInfo()			updtCistInfo_(p)

static int updtMstiInfo_(struct ksz_stp_port *p)
{
	int MSTI = p->MSTI;
	int ret = FALSE;

	if (updtInfo)
		return TRUE;
	p->MSTI = 0;
	ret = updtInfo;
	p->MSTI = MSTI;
	return ret;
}

#define updtMstiInfo()			updtMstiInfo_(p)

static void newInfoXst_(struct ksz_stp_port *p, int set)
{
	if (msti())
		newInfoMsti = set;
	else
		newInfo = set;
#if 0
dbg_msg("%s %d=%d %d\n", __func__, p->port_index, newInfo, newInfoMsti);
#endif
}

#define newInfoXst(s)			newInfoXst_(p, s)

static int rcvdXstMsg_(struct ksz_stp_port *p)
{
	if (msti())
		return rcvdMstiMsg();
	return rcvdCistMsg();
}

#define rcvdXstMsg()			rcvdXstMsg_(p)

static int updtXstInfo_(struct ksz_stp_port *p)
{
	if (msti())
		return updtMstiInfo();
	return updtCistInfo();
}

#define updtXstInfo()			updtXstInfo_(p)

static int betterorsameInfo_(struct ksz_stp_port *p, u8 newInfoIs)
{
	int ret = FALSE;

	if (INFO_TYPE_RECEIVED == newInfoIs && INFO_TYPE_RECEIVED == infoIs) {
		ret = betterSamePriority(&msgPriority, &portPriority);
#ifdef DBG_STP_ROLE_
dbg_msg("  recd: %d\n", ret);
#endif
	} else if (INFO_TYPE_MINE == newInfoIs && INFO_TYPE_MINE == infoIs) {
		ret = betterSamePriority(&designatedPriority, &portPriority);
#ifdef DBG_STP_ROLE_
dbg_msg("  mine: %d\n", ret);
#endif
#if 0
	} else if (INFO_TYPE_MINE == newInfoIs && INFO_TYPE_AGED == infoIs) {
		ret = betterSamePriority(&designatedPriority, &portPriority);
dbgPriority(&designatedPriority, NULL);
dbgPriority(&portPriority, NULL);
#endif
	}
#ifdef DBG_STP_ROLE_
dbg_msg("%s %d\n", __func__, ret);
#endif
	return ret;
}

#define betterorsameInfo(i)		betterorsameInfo_(p, i)

static void clearAllRcvdMsgs_(struct ksz_stp_port *p)
{
	FOREACH_T_IN_P(
		rcvdMsg = FALSE;
	)
}

#define clearAllRcvdMsgs()		clearAllRcvdMsgs_(p)

static void clearReselectTree_(struct ksz_stp_bridge *br)
{
	struct ksz_stp_port *p = &br->ports[0];

	FOREACH_P_IN_T(
		reselect = FALSE;
	)
}

#define clearReselectTree()		clearReselectTree_(br)

static void disableForwarding_(struct ksz_stp_port *p)
{
	struct ksz_stp_info *stp = p->br->parent;
	struct ksz_sw *sw = stp->sw_dev;
	int i = p->port_index;

	sw->ops->acquire(sw);
	port_cfg_mstp(sw, i, p->MSTI);
	if (!learning) {
#ifdef DBG_STP_PORT_BLOCK
		struct ksz_stp_dbg_times *x = &p->dbg_times[p->MSTI];

		x->block_jiffies = jiffies;
#endif
		if (portEnabled)
			port_set_stp_state(sw, i, STP_STATE_BLOCKED);
		sw_cfg_forwarding(sw, i, false);
	} else {
		port_cfg_rx(sw, i, false);
		port_cfg_tx(sw, i, false);
	}
	sw->ops->release(sw);
}

#define disableForwarding()		disableForwarding_(p)

static void disableLearning_(struct ksz_stp_port *p)
{
	struct ksz_stp_info *stp = p->br->parent;
	struct ksz_sw *sw = stp->sw_dev;
	int i = p->port_index;

	sw->ops->acquire(sw);
	port_cfg_mstp(sw, i, p->MSTI);
	port_cfg_dis_learn(sw, i, true);
	sw->ops->release(sw);
}

#define disableLearning()		disableLearning_(p)

static void enableForwarding_(struct ksz_stp_port *p)
{
	struct ksz_stp_info *stp = p->br->parent;
	struct ksz_sw *sw = stp->sw_dev;
	int i = p->port_index;

	sw->ops->acquire(sw);
	port_cfg_mstp(sw, i, p->MSTI);
#ifdef DBG_STP_PORT_BLOCK
	do {
		struct ksz_stp_dbg_times *x = &p->dbg_times[p->MSTI];

		if (x->block_jiffies)
dbg_msg("  B:%d:%d=%ld\n", p->port_index, p->MSTI, jiffies - x->block_jiffies);
		x->block_jiffies = 0;
	} while (0);
#endif
	if (learning) {
		port_set_stp_state(sw, i, STP_STATE_FORWARDING);
		sw_cfg_forwarding(sw, i, true);
	} else {
		port_cfg_rx(sw, i, true);
		port_cfg_tx(sw, i, true);
	}
	sw->ops->release(sw);
}

#define enableForwarding()		enableForwarding_(p)

static void enableLearning_(struct ksz_stp_port *p)
{
	struct ksz_stp_info *stp = p->br->parent;
	struct ksz_sw *sw = stp->sw_dev;
	int i = p->port_index;

	sw->ops->acquire(sw);
	port_cfg_mstp(sw, i, p->MSTI);
	port_cfg_dis_learn(sw, i, false);
	sw->ops->release(sw);
#ifdef DBG_STP_PORT_BLOCK
	p->dbg_times[p->MSTI].learn_jiffies = jiffies;
#endif
}

#define enableLearning()		enableLearning_(p)

static int fromSameRegion_(struct ksz_stp_port *p)
{
	if (ForceProtocolVersion >= 3 && rcvdRSTP &&
	    !memcmp(&bpduMCID, &MstConfigId, sizeof(struct mst_cfg_id)))
		return TRUE;
	return FALSE;
}

#define fromSameRegion()		fromSameRegion_(p)

static void newTcDetected_(struct ksz_stp_port *p)
{
	if (tcDetected)
		return;
	if (rcvdRSTP) {
		tcDetected = to_stp_timer(CISTportTimes.hello_time + 1);
	} else {
		tcDetected = rootTimes.max_age + rootTimes.forward_delay;
		tcDetected = to_stp_timer(tcDetected);
	}
	do {
		struct ksz_stp_info *stp = p->br->parent;
		struct ksz_sw *sw = stp->sw_dev;

		sw->ops->tc_detected(sw, p->port_index);
	} while (0);
}

#define newTcDetected()			newTcDetected_(p)

static void newTcWhile_(struct ksz_stp_port *p)
{
	if (tcWhile)
		return;
	if (sendRSTP) {
		tcWhile = to_stp_timer(CISTportTimes.hello_time + 1);
		if (p->MSTI)
			newInfoMsti = TRUE;
		else
			newInfo = TRUE;
	} else {
		tcWhile = rootTimes.max_age + rootTimes.forward_delay;
		tcWhile = to_stp_timer(tcWhile);
	}
	if (!isTC) {
		timeSinceTC = 0;
		cntTC++;
	}
	isTC |= (1 << p->port_index);
}

#define newTcWhile()			newTcWhile_(p)

static u8 rcvInfo_(struct ksz_stp_port *p)
{
	int prio;
	int time;

	if (BPDU_TYPE_TCN == bpduType) {
		rcvdTcn = TRUE;
		return INFO_OTHER;
	}

	if (BPDU_TYPE_CONFIG == bpduType)
		bpduRole = ROLE_DESIGNATED;

	COPY(msgPriority, bpduPriority);
	COPY(msgTimes, bpduTimes);

	prio = CMP(msgPriority, portPriority);
	if (cist())
		time = CMP(msgTimes, portTimes);
	else
		time = msgTimes.max_hops - portTimes.max_hops;
	if (bpduRole == ROLE_DESIGNATED) {
		if (superiorPriority(&msgPriority, &portPriority))
			return INFO_SUPERIOR_DESIGNATED;

		if (0 == prio && time != 0)
			return INFO_SUPERIOR_DESIGNATED;

		if (0 == prio && 0 == time)
			return INFO_REPEATED_DESIGNATED;

		if (prio > 0)
			return INFO_INFERIOR_DESIGNATED;
	}

	if ((bpduRole == ROLE_ROOT || bpduRole == ROLE_ALT_BACKUP) &&
	    prio >= 0)
		return INFO_INFERIOR_ROOT_ALT;

	return INFO_OTHER;
}

#define rcvInfo()			rcvInfo_(p)

static void rcvMsgs_(struct ksz_stp_port *p)
{
	p->MSTI = 0;
	rcvdMsg = TRUE;
	if (rcvdInternal) {
		FOREACH_M_IN_P(
			if (bpduFlags)
				rcvdMsg = TRUE;
		)
	}
	if (rcvdTcn) {
		FOREACH_M_IN_P(
			rcvdTcn = TRUE;
		)
	}
}

#define rcvMsgs()			rcvMsgs_(p)

static void recordAgreement_(struct ksz_stp_port *p)
{
	/*
	 * Not operPointToPointMAC will keep proposing and root port sending
	 * agreement forever.
	 */
	if (cist()) {
		if (rstpVersion && operPointToPointMAC &&
		    (bpduFlags & AGREEMENT)) {
			agreed = TRUE;
			proposing = FALSE;
			if (!rcvdInternal) {
				FOREACH_M_IN_P(
					agreed = TRUE;
					proposing = FALSE;
				)
			}
		} else {
			agreed = FALSE;
		}
	} else {
		if (operPointToPointMAC &&
		    !memcmp(&CISTmsgPriority, &CISTportPriority,
		    sizeof(struct _bridge_id) * 2 + sizeof(u32)) &&
		    (bpduFlags & AGREEMENT)) {
			agreed = TRUE;
			proposing = FALSE;
		} else {
			agreed = FALSE;
		}
	}
}

#define recordAgreement()		recordAgreement_(p)

static void recordDispute_(struct ksz_stp_port *p)
{
	if ((bpduFlags & LEARNING)) {
		disputed = TRUE;
		agreed = FALSE;
		if (!p->MSTI && !rcvdInternal) {
			FOREACH_M_IN_P(
				disputed = TRUE;
				agreed = FALSE;
			)
		}
	}
}

#define recordDispute()			recordDispute_(p)

static void recordMastered_(struct ksz_stp_port *p)
{
	if (!p->MSTI && !rcvdInternal) {
		FOREACH_M_IN_P(
			mastered = FALSE;
		)
	}
	if (p->MSTI) {
		if (operPointToPointMAC && (bpduFlags & MASTER))
			mastered = TRUE;
		else
			mastered = FALSE;
	}
}

#define recordMastered()		recordMastered_(p)

static void recordPriority_(struct ksz_stp_port *p)
{
	COPY(portPriority, msgPriority);
}

#define recordPriority()		recordPriority_(p)

static void recordProposal_(struct ksz_stp_port *p)
{
	if (bpduRole == ROLE_DESIGNATED && (bpduFlags & PROPOSAL))
		proposed = TRUE;
	if (!p->MSTI && !rcvdInternal) {
		int flag = proposed;

		FOREACH_M_IN_P(
			proposed = flag;
		)
	}
}

#define recordProposal()		recordProposal_(p)

#define MIN_COMPAT_HELLO_TIME		1
#define FIXED_HELLO_TIME		2

static void recordTimes_(struct ksz_stp_port *p)
{
	if (cist()) {
		if (checkParameters(2, msgTimes.max_age,
		    msgTimes.forward_delay)) {
			COPY(portTimes, msgTimes);

			portTimes.hello_time = FIXED_HELLO_TIME;
			portTimes.max_hops = msgTimes.max_hops;
		} else
			portTimes.message_age = msgTimes.message_age;
	} else
		portTimes.max_hops = msgTimes.max_hops;
}

#define recordTimes()			recordTimes_(p)

static void setReRootTree_(struct ksz_stp_port *p)
{
	FOREACH_P_IN_T(
		reRoot = TRUE;
	)
}

#define setReRootTree()			setReRootTree_(p)

static void setSelectedTree_(struct ksz_stp_bridge *br)
{
	struct ksz_stp_port *p = &br->ports[0];

	FOREACH_P_IN_T(
		if (reselect)
{
dbg_msg("  !! %s %d\n", __func__, p->port_index);
			return;
}
	)
	FOREACH_P_IN_T(
		selected = TRUE;
	)
}

#define setSelectedTree()		setSelectedTree_(br)

static void setSyncTree_(struct ksz_stp_port *p)
{
	FOREACH_P_IN_T(
		sync = TRUE;
	)
}

#define setSyncTree()			setSyncTree_(p)

static void setTcFlags_(struct ksz_stp_port *p)
{
	if (bpduFlags & TOPOLOGY_CHANGE) {
		rcvdTc = TRUE;
		if (!p->MSTI && !rcvdInternal) {
			FOREACH_M_IN_P(
				rcvdTc = TRUE;
			)
		}
	}
	if (!p->MSTI && (bpduFlags & TOPOLOGY_CHANGE_ACK))
		rcvdTcAck = TRUE;
}

#define setTcFlags()			setTcFlags_(p)

static void setTcPropTree_(struct ksz_stp_port *p)
{
	struct ksz_stp_port *q = p;

	if (restrictedTcn)
		return;
#if 1
	/*
	 * Topology Change Acknowledge is no longer used!  The port will
	 * receive at least 2 Toplogy Change.  With self detection the
	 * PROPAGATING state may be activated up to 4 times!
	 * In newTcWhile the timer will only be updated if it is empty, but
	 * doFlush will be called many times which is really not necessary.
	 */
	if (sendRSTP) {
		if (tcPropWhile)
			return;
		tcPropWhile = to_stp_timer(CISTportTimes.hello_time + 1);
	}
#endif
	FOREACH_P_IN_T(
		if (p == q)
			continue;
		tcProp = TRUE;
	)
}

#define setTcPropTree()			setTcPropTree_(p)

static void syncMaster_(struct ksz_stp_bridge *br)
{
	struct ksz_stp_port *p = &br->ports[0];

dbg_msg("%s\n", __func__);
	FOREACH_P_IN_T(
		if (!infoInternal)
			continue;
		FOREACH_M_IN_P(
			agree = agreed = synced = FALSE;
			sync = TRUE;
		)
	)
}

#define syncMaster()			syncMaster_(p->br)

static int stp_xmit(struct ksz_stp_info *stp, u8 port)
{
	int rc;
	struct sk_buff *skb;
	u8 *frame = stp->tx_frame;
	struct ksz_sw *sw = stp->sw_dev;
	int len = stp->len;
	uint ports;
	const struct net_device_ops *ops = stp->dev->netdev_ops;
	struct llc *llc = (struct llc *) &frame[12];
	struct ksz_port_info *info = get_port_info(sw, port);

	/* Do not send if network device is not ready. */
	if (!netif_running(stp->dev))
		return 0;

	ports = (1 << port);
	ports |= TAIL_TAG_SET_OVERRIDE;
	ports |= TAIL_TAG_SET_QUEUE;

	len += 3;
	llc->len = htons(len);
	len += 14;
	if (len < 60) {
		memset(&frame[len], 0, 60 - len);
		len = 60;
	}

	/* Add extra for tail tagging. */
	skb = dev_alloc_skb(len + 4 + 8);
	if (!skb)
		return -ENOMEM;

	memcpy(skb->data, stp->tx_frame, len);
	memcpy(&skb->data[6], info->mac_addr, ETH_ALEN);

	skb_put(skb, len);
	sw->net_ops->add_tail_tag(sw, skb, ports);
	skb->protocol = htons(STP_TAG_TYPE);
	skb->dev = stp->dev;
	do {
		struct ksz_sw *sw = stp->sw_dev;

		rc = ops->ndo_start_xmit(skb, skb->dev);
		if (NETDEV_TX_BUSY == rc) {
			rc = wait_event_interruptible_timeout(sw->queue,
				!netif_queue_stopped(stp->dev),
				50 * HZ / 1000);

			rc = NETDEV_TX_BUSY;
		}
	} while (NETDEV_TX_BUSY == rc);
	return rc;
}  /* stp_xmit */

static void txConfig_(struct ksz_stp_port *p)
{
	int rc;
	struct stp_prio prio;
	struct ksz_stp_info *stp = p->br->parent;
	struct bpdu *bpdu = stp->bpdu;

	memcpy(&prio.root, &designatedPriority.root,
		sizeof(struct _bridge_id) + sizeof(u32));
	memcpy(&prio.bridge_id, &designatedPriority.bridge_id,
		sizeof(struct _bridge_id) + sizeof(struct _port_id));
	prep_stp(bpdu, &prio, &designatedTimes, &portTimes);
	bpdu->flags = 0;
	if (tcWhile != 0)
		bpdu->flags |= TOPOLOGY_CHANGE;
	if (tcAck)
		bpdu->flags |= TOPOLOGY_CHANGE_ACK;

	stp->len = sizeof(struct bpdu_v1) - 1;
	rc = stp_xmit(stp, p->port_index);
}

#define txConfig()			txConfig_(p)

static void txRstp_(struct ksz_stp_port *p)
{
	int rc;
	struct stp_prio prio;
	struct ksz_stp_info *stp = p->br->parent;
	struct bpdu *bpdu = stp->bpdu;
	u8 r = role;

if (!portEnabled)
dbg_msg(" ?! %s %d %d\n", __func__, p->port_index, r);
	memcpy(&prio.root, &designatedPriority.root,
		sizeof(struct _bridge_id) + sizeof(u32));
	memcpy(&prio.bridge_id, &designatedPriority.regional_root,
		sizeof(struct _bridge_id));
	memcpy(&prio.port_id, &designatedPriority.port_id,
		sizeof(struct _port_id));
	prep_rstp(bpdu, &prio, &designatedTimes, &portTimes);
	if (AlternatePort || BackupPort)
		r = PORT_ROLE_ALTERNATE;
if (r != PORT_ROLE_ALTERNATE && r != PORT_ROLE_ROOT && r != PORT_ROLE_DESIGNATED)
dbg_msg("  invalid role %d\n", r);
	r &= PORT_ROLE_DESIGNATED;
	r <<= PORT_ROLE_S;
	bpdu->flags = r;
	if (tcWhile != 0)
		bpdu->flags |= TOPOLOGY_CHANGE;
	if (agree)
		bpdu->flags |= AGREEMENT;
	if (proposing)
		bpdu->flags |= PROPOSAL;
	if (learning)
		bpdu->flags |= LEARNING;
	if (forwarding)
		bpdu->flags |= FORWARDING;
	/*
	 * Topology Change Acknowledge is no longer used in MSTP as the bit is
	 * used by Master indication, similar to Agreement.
	 */
	if (ForceProtocolVersion < 3 && tcAck)
		bpdu->flags |= TOPOLOGY_CHANGE_ACK;

	stp->len = sizeof(struct bpdu_v1);
	if (ForceProtocolVersion >= 3) {
		struct mstp_bpdu *mstp = &bpdu->mstp;
		struct msti_cfg *cfg = (struct msti_cfg *)(bpdu + 1);

		bpdu->version = 3;
		stp->len = sizeof(struct bpdu_v1);
		memcpy(&mstp->MCID, &MstConfigId, sizeof(struct mst_cfg_id));
		mstp->internal_root_path_cost =
			designatedPriority.internal_root_path_cost;
		memcpy(&mstp->id, &designatedPriority.bridge_id,
			sizeof(struct _bridge_id));
		mstp->max_hops = designatedTimes.max_hops;
		FOREACH_M_IN_P(
			p->br->MSTI = p->MSTI;
			r = role;
			if (AlternatePort || BackupPort)
				r = PORT_ROLE_ALTERNATE;
			else if (MasterPort)
				r = PORT_ROLE_MASTER;
			r &= PORT_ROLE_DESIGNATED;
			r <<= PORT_ROLE_S;
			cfg->flags = r;
			if (tcWhile != 0)
				cfg->flags |= TOPOLOGY_CHANGE;
			if (agree)
				cfg->flags |= AGREEMENT;
			if (proposing)
				cfg->flags |= PROPOSAL;
			if (learning)
				cfg->flags |= LEARNING;
			if (forwarding)
				cfg->flags |= FORWARDING;
			if (master)
				cfg->flags |= MASTER;
			memcpy(&cfg->root, &designatedPriority.regional_root,
				sizeof(struct _bridge_id));
			cfg->root_path_cost =
				designatedPriority.internal_root_path_cost;
			cfg->br_prio = BridgeIdentifier.prio & 0xF0;
			cfg->port_prio = portId.prio & 0xF0;
			cfg->max_hops = designatedTimes.max_hops;
			cfg++;
		)
		p->MSTI = p->br->MSTI = 0;
		mstp->version_3_length = sizeof(struct mstp_bpdu);
		mstp->version_3_length +=
			(p->br->MSTI_cnt - 1) * sizeof(struct msti_cfg);
		stp->len += mstp->version_3_length;
		mstp->version_3_length = htons(mstp->version_3_length - 2);
	}

#ifdef DBG_STP_TX
	do {
		int cmp = memcmp(&p->tx_bpdu0, bpdu, stp->len);

		if (cmp) {
			p->dbg_tx++;
			memcpy(&p->tx_bpdu0, bpdu, stp->len);
		}
		if (p->dbg_tx) {
			dbg_msg("<T> %d: ", p->port_index);
			disp_bpdu(bpdu);
			p->dbg_tx--;
		}
	} while (0);
#endif
	rc = stp_xmit(stp, p->port_index);
}

#define txRstp()			txRstp_(p)

static void txTcn_(struct ksz_stp_port *p)
{
	int rc;
	struct ksz_stp_info *stp = p->br->parent;
	struct bpdu *bpdu = stp->bpdu;

	bpdu->protocol = 0;
	bpdu->version = 0;
	bpdu->type = BPDU_TYPE_TCN;

	stp->len = 4;
	rc = stp_xmit(stp, p->port_index);
}

#define txTcn()				txTcn_(p)

static void updtBPDUVersion_(struct ksz_stp_port *p)
{
	if ((0 == bpduVersion || 1 == bpduVersion) &&
	    (BPDU_TYPE_TCN == bpduType || BPDU_TYPE_CONFIG == bpduType))
		rcvdSTP = TRUE;
	if (BPDU_TYPE_CONFIG_RSTP == bpduType)
		rcvdRSTP = TRUE;
}

#define updtBPDUVersion()		updtBPDUVersion_(p)

static void updtRcvdInfoWhile_(struct ksz_stp_port *p)
{
	/*
	 * Definition is not clear!
	 * It is mentioned several times that Message Age should be less than
	 * Max Age in BPDU to be accepted.
	 */
	if (!rcvdInternal && portTimes.message_age + 1 <= portTimes.max_age)
		rcvdInfoWhile = to_stp_timer(3 * portTimes.hello_time);
	else if (rcvdInternal && portTimes.max_hops > 1)
		rcvdInfoWhile = to_stp_timer(3 * portTimes.hello_time);
	else
		rcvdInfoWhile = 0;
}

#define updtRcvdInfoWhile()		updtRcvdInfoWhile_(p)

static void updtRoleDisabledTree_(struct ksz_stp_bridge *br)
{
	struct ksz_stp_port *p = &br->ports[0];

	FOREACH_P_IN_T(
		selectedRole = ROLE_DISABLED;
	)
}

#define updtRoleDisabledTree()		updtRoleDisabledTree_(br)

static u32 add_path_cost(u32 x, u32 y)
{
	u32 z;

	z = ntohl(x) + y;
	return htonl(z);
}

static void updtRole(struct ksz_stp_port *p, struct mstp_prio *priority)
{
	int id;
	int prio;
	int time;
#ifdef DBG_STP_PORT_FLUSH
	struct ksz_stp_dbg_times *x = &p->dbg_times[p->MSTI];
#endif

	COPY(designatedPriority, rootPriority);
	COPY(designatedPriority.bridge_id, BridgeIdentifier);
	COPY(designatedPriority.port_id, portId);

	COPY(designatedTimes, rootTimes);

	/*
	 * HelloTime was changed to come froom portTimes rather than
	 * designatedTimes.
	 */
	portTimes.hello_time = designatedTimes.hello_time;

	if (INFO_TYPE_UNKNOWN == infoIs)
dbg_msg("unknown\n");
	if (INFO_TYPE_DISABLED == infoIs) {
		selectedRole = ROLE_DISABLED;
#ifdef DBG_STP_PORT_FLUSH
		x->role_ = ROLE_DISABLED;
		x->downPriority.port_id.num = 0;
		x->learn_jiffies = 0;
#endif
	}
	if (msti() && (INFO_TYPE_RECEIVED == CISTinfoIs) && !infoInternal) {
		prio = 0;
		if (ROLE_ROOT == CISTselectedRole) {
			selectedRole = ROLE_MASTER;
			prio = 1;
		} else if (ROLE_ALTERNATE == CISTselectedRole) {
			selectedRole = ROLE_ALTERNATE;
			prio = 1;
		}
		if (prio) {
			prio = CMP(designatedPriority, portPriority);
			time = CMP(designatedTimes, portTimes);
			if (prio || time)
				updtInfo = TRUE;
		}
	} else {
		if (INFO_TYPE_AGED == infoIs) {
			updtInfo = TRUE;
			selectedRole = ROLE_DESIGNATED;
#ifdef DBG_STP_PORT_FLUSH
			if (ROLE_DISABLED == x->role_)
				x->role_ = ROLE_DESIGNATED;
#endif
#ifdef DBG_STP_RX
p->dbg_rx = 3;
#endif
#ifdef DBG_STP_TX
p->dbg_tx = 2;
#endif
		} else if (INFO_TYPE_MINE == infoIs) {
			selectedRole = ROLE_DESIGNATED;
			prio = CMP(designatedPriority, portPriority);
			time = CMP(designatedTimes, portTimes);
			if (prio || time)
				updtInfo = TRUE;
#ifdef DBG_STP_PORT_FLUSH
			if (ROLE_DISABLED == x->role_)
				x->role_ = ROLE_DESIGNATED;
#endif
#ifdef DBG_STP_RX
p->dbg_rx = 3;
#endif
#ifdef DBG_STP_TX
p->dbg_tx = 1;
#endif
		} else if (INFO_TYPE_RECEIVED == infoIs) {
			if (priority == &portPriority) {
				selectedRole = ROLE_ROOT;
				updtInfo = FALSE;
			} else {
				prio = CMP(designatedPriority, portPriority);
				if (prio >= 0) {
					id = CMP(portPriority.bridge_id.addr,
						BridgeIdentifier.addr);
					if (id)
						selectedRole = ROLE_ALTERNATE;
					else
						selectedRole = ROLE_BACKUP;
					updtInfo = FALSE;
#ifdef DBG_STP_PORT_FLUSH
					x->role_ = ROLE_DESIGNATED;
#endif
				} else {
					selectedRole = ROLE_DESIGNATED;
					updtInfo = TRUE;
				}
			}
#ifdef DBG_STP_RX
p->dbg_rx = 3;
#endif
#ifdef DBG_STP_TX
p->dbg_tx = 3;
#endif
		}
	}
#ifdef DBG_STP_ROLE
if (!p->off)
dbg_msg("  %s %d:%d %d\n", __func__, p->port_index, p->MSTI, selectedRole);
#endif
}

static void updtRolesTree_(struct ksz_stp_bridge *br)
{
	int better;
	int prio;
	struct ksz_stp_port *p = &br->ports[0];
	struct mstp_vector root_path;
	struct mstp_vector best_path;
	struct mstp_prio prevPriority;
	struct mstp_prio *root_Priority = NULL;
	struct _port_id prevPortId;
	struct _port_id root_PortId;
	struct ksz_stp_port *q = NULL;

	COPY(root_PortId, BridgePriority.port_id);

	/* Find out the best path from all ports. */
	FOREACH_P_IN_T(

		/* Check only after receiving new BPDU. */
		if (infoIs != INFO_TYPE_RECEIVED)
			continue;

		/* Not from self. */
		prio = CMP(portPriority.bridge_id.addr, BridgeIdentifier.addr);
		if (!prio)
			continue;

		if (restrictedRole)
			continue;

		/* Ports may receive same BPDU when coming through a hub. */
		COPY_PRIO(root_path, portPriority, portId);
		if (!infoInternal) {
			root_path.prio.internal_root_path_cost = 0;
			COPY(root_path.prio.regional_root, BridgeIdentifier);
			root_path.prio.root_path_cost = add_path_cost(
				root_path.prio.root_path_cost,
				ExternalPortPathCost);
		} else
			root_path.prio.internal_root_path_cost = add_path_cost(
				root_path.prio.internal_root_path_cost,
				InternalPortPathCost);

		better = FALSE;
		if (!root_Priority)
			better = TRUE;
		else if (betterVector(&root_path, &best_path))
			better = TRUE;
		if (better) {
			COPY(best_path, root_path);
			root_Priority = &portPriority;
			COPY(root_PortId, portId);
			q = p;
		}
	)
#ifdef DBG_STP_ROLE
if (root_Priority) {
dbg_msg(" best \n");
dbgPriority(&best_path.prio, &best_path.port_id);
#if 0
dbg_msg(" root prio\n");
dbgPriority(root_Priority, &root_PortId);
#endif
}
#endif

	/* Compare with the bridge. */
	better = FALSE;
	if (!root_Priority)
		better = TRUE;
	else if (betterVector(&BridgePriority, &best_path))
		better = TRUE;
	if (better) {
		COPY(best_path, BridgePriority);
		root_Priority = NULL;
		COPY(root_PortId, BridgePriority.port_id);
	}

	COPY(prevPriority, rootPriority);
	COPY(prevPortId, rootPortId);

	COPY(rootPriority, best_path.prio);
	COPY(rootPortId, best_path.port_id);

	if (root_Priority) {
		struct ksz_stp_info *stp = br->parent;
		struct ksz_sw *sw = stp->sw_dev;
		uint num;

		num = get_phy_port(sw, root_PortId.num);
		p = &br->ports[num];
		COPY(rootTimes, portTimes);
		if (!rcvdInternal)
			rootTimes.message_age += 1;
		else
			rootTimes.max_hops -= 1;
	} else {
		COPY(rootTimes, BridgeTimes);
	}

	if (cist() && (CMP(prevPriority, rootPriority) ||
	    CMP(prevPortId, rootPortId)) &&
	    CMP(prevPriority.regional_root, rootPriority.regional_root) &&
	    (prevPriority.root_path_cost || rootPriority.root_path_cost))
		syncMaster();

	FOREACH_P_IN_T(
		updtRole(p, root_Priority);
	)
}

#define updtRolesTree()			updtRolesTree_(br)


enum {
	STP_BEGIN,
	STP_LAST
};

enum {
	STP_PortTimers_ONE_SECOND = STP_LAST,
	STP_PortTimers_TICK,
};

enum {
	STP_PortReceive_DISCARD = STP_LAST,
	STP_PortReceive_RECEIVE,
};

enum {
	STP_PortProtoMigr_CHECKING_RSTP = STP_LAST,
	STP_PortProtoMigr_SELECTING_STP,
	STP_PortProtoMigr_SENSING,
};

enum {
	STP_BridgeDetection_EDGE = STP_LAST,
	STP_BridgeDetection_NOT_EDGE,
	STP_BridgeDetection_ISOLATED,
};

enum {
	STP_PortTransmit_INIT = STP_LAST,
	STP_PortTransmit_PERIODIC,
	STP_PortTransmit_CONFIG,
	STP_PortTransmit_TCN,
	STP_PortTransmit_RSTP,
	STP_PortTransmit_IDLE,
};

enum {
	STP_PortInfo_DISABLED = STP_LAST,
	STP_PortInfo_AGED,
	STP_PortInfo_UPDATE,
	STP_PortInfo_SUPERIOR_DESIGNATED,
	STP_PortInfo_REPEATED_DESIGNATED,
	STP_PortInfo_INFERIOR_DESIGNATED,
	STP_PortInfo_NOT_DESIGNATED,
	STP_PortInfo_OTHER,
	STP_PortInfo_CURRENT,
	STP_PortInfo_RECEIVE,
};

enum {
	STP_PortRoleSel_INIT_BRIDGE = STP_LAST,
	STP_PortRoleSel_ROLE_SELECTION,
};

enum {
	STP_PortRoleTrans_INIT_PORT = STP_LAST,
	STP_PortRoleTrans_DISABLE_PORT,
	STP_PortRoleTrans_DISABLED_PORT,
	STP_PortRoleTrans_MASTER_PROPOSED,
	STP_PortRoleTrans_MASTER_AGREED,
	STP_PortRoleTrans_MASTER_SYNCED,
	STP_PortRoleTrans_MASTER_RETIRED,
	STP_PortRoleTrans_MASTER_DISCARD,
	STP_PortRoleTrans_MASTER_LEARN,
	STP_PortRoleTrans_MASTER_FORWARD,
	STP_PortRoleTrans_MASTER_PORT,
	STP_PortRoleTrans_ROOT_PROPOSED,
	STP_PortRoleTrans_ROOT_AGREED,
	STP_PortRoleTrans_ROOT_SYNCED,
	STP_PortRoleTrans_ROOT_RETIRED,
	STP_PortRoleTrans_ROOT_DISCARD,
	STP_PortRoleTrans_REROOT,
	STP_PortRoleTrans_REROOTED,
	STP_PortRoleTrans_ROOT_LEARN,
	STP_PortRoleTrans_ROOT_FORWARD,
	STP_PortRoleTrans_ROOT_PORT,
	STP_PortRoleTrans_DESIGNATED_PROPOSE,
	STP_PortRoleTrans_DESIGNATED_AGREED,
	STP_PortRoleTrans_DESIGNATED_SYNCED,
	STP_PortRoleTrans_DESIGNATED_RETIRED,
	STP_PortRoleTrans_DESIGNATED_DISCARD,
	STP_PortRoleTrans_DESIGNATED_LEARN,
	STP_PortRoleTrans_DESIGNATED_FORWARD,
	STP_PortRoleTrans_DESIGNATED_PORT,
	STP_PortRoleTrans_BLOCK_PORT,
	STP_PortRoleTrans_ALTERNATE_PROPOSED,
	STP_PortRoleTrans_ALTERNATE_AGREED,
	STP_PortRoleTrans_BACKUP_PORT,
	STP_PortRoleTrans_ALTERNATE_PORT,
};

enum {
	STP_PortStateTrans_DISCARDING = STP_LAST,
	STP_PortStateTrans_LEARNING,
	STP_PortStateTrans_FORWARDING,
};

enum {
	STP_TopologyChange_INACTIVE = STP_LAST,
	STP_TopologyChange_LEARNING,
	STP_TopologyChange_DETECTED,
	STP_TopologyChange_ACKNOWLEDGED,
	STP_TopologyChange_PROPAGATING,
	STP_TopologyChange_NOTIFIED_TC,
	STP_TopologyChange_NOTIFIED_TCN,
	STP_TopologyChange_ACTIVE,
};

enum {
	STP_PortTimers,
	STP_PortReceive,
	STP_PortProtoMigr,
	STP_BridgeDetection,
	STP_PortInfo,
	STP_PortRoleTrans,
	STP_PortStateTrans,
	STP_TopologyChange,
	STP_PortTransmit,

	STP_PortRoleSel,
};

#ifdef DBG_STP_STATE
static char *PortTimers_names[] = {
	"ONE_SECOND",
	"TICK",
};

static char *PortReceive_names[] = {
	"DISCARD,"
	"RECEIVE",
};

static char *PortProtoMigr_names[] = {
	"CHECKING_RSTP",
	"SELECTING_STP",
	"SENSING",
};

static char *BridgeDetection_names[] = {
	"EDGE",
	"NOT_EDGE",
	"ISOLATED",
};

static char *PortTransmit_names[] = {
	"INIT",
	"PERIODIC",
	"CONFIG",
	"TCN",
	"RSTP",
	"IDLE",
};

static char *PortInfo_names[] = {
	"DISABLED",
	"AGED",
	"UPDATE",
	"SUPERIOR_DESIGNATED",
	"REPEATED_DESIGNATED",
	"INFERIOR_DESIGNATED",
	"NOT_DESIGNATED",
	"OTHER",
	"CURRENT",
	"RECEIVE",
};

static char *PortRoleSel_names[] = {
	"INIT_BRIDGE",
	"ROLE_SELECTION",
};

static char *PortRoleTrans_names[] = {
	"INIT_PORT",
	"DISABLE_PORT",
	"DISABLED_PORT",
	"MASTER_PROPOSED",
	"MASTER_AGREED",
	"MASTER_SYNCED",
	"MASTER_RETIRED",
	"MASTER_DISCARD",
	"MASTER_LEARN",
	"MASTER_FORWARD",
	"MASTER_PORT",
	"ROOT_PROPOSED",
	"ROOT_AGREED",
	"ROOT_SYNCED",
	"ROOT_RETIRED",
	"ROOT_DISCARD",
	"REROOT",
	"REROOTED",
	"ROOT_LEARN",
	"ROOT_FORWARD",
	"ROOT_PORT",
	"DESIGNATED_PROPOSE",
	"DESIGNATED_AGREED",
	"DESIGNATED_SYNCED",
	"DESIGNATED_RETIRED",
	"DESIGNATED_DISCARD",
	"DESIGNATED_LEARN",
	"DESIGNATED_FORWARD",
	"DESIGNATED_PORT",
	"BLOCK_PORT",
	"ALTERNATE_PROPOSED",
	"ALTERNATE_AGREED",
	"BACKUP_PORT",
	"ALTERNATE_PORT",
};

static char *PortStateTrans_names[] = {
	"DISCARDING",
	"LEARNING",
	"FORWARDING",
};

static char *TopologyChange_names[] = {
	"INACTIVE",
	"LEARNING",
	"DETECTED",
	"ACKNOWLEDGED",
	"PROPAGATING",
	"NOTIFIED_TC",
	"NOTIFIED_TCN",
	"ACTIVE",
};

static char **stp_state_names[] = {
	PortTimers_names,
	PortReceive_names,
	PortProtoMigr_names,
	BridgeDetection_names,
	PortInfo_names,
	PortRoleTrans_names,
	PortStateTrans_names,
	TopologyChange_names,
	PortTransmit_names,

	PortRoleSel_names,
};
#endif


struct ksz_stp_state {
	int index;
	int change;
	int new_state;
};

static int stp_proc_state(struct ksz_stp_port *p, struct ksz_stp_state *state,
	void (*state_init)(struct ksz_stp_port *p),
	void (*state_next)(struct ksz_stp_port *p, struct ksz_stp_state *state))
{
	if (state->new_state) {
		state->new_state = 0;
		state_init(p);
	}
	state_next(p, state);
	return 0;
}  /* stp_proc_state */

static void stp_change_state(struct ksz_stp_state *state, int cond, int new)
{
	if (!cond)
		return;
	if (state->new_state) {
#ifdef DBG_STP_STATE
		if (state->change) {
			char **names = stp_state_names[state->index];
			char *last;
			char *next;

			if (state->new_state != STP_BEGIN)
				last = names[state->new_state - STP_LAST];
			else
				last = "BEGIN";
			if (new != STP_BEGIN)
				next = names[new - STP_LAST];
			else
				next = "BEGIN";
dbg_msg("  %s %d %s %d %s\n", __func__, state->new_state, last, new, next);
		}
#endif
		return;
	}
	state->new_state = new;
}  /* stp_change_state */

#if defined(DBG_STP_STATE) || defined(DBG)
static void dbg_stp(struct ksz_stp_port *p, const char *msg, int rx)
{
	if (rx && !p->dbg_rx)
		return;
	dbg_msg(" %d:%d=", p->port_index, p->MSTI);
	switch (role) {
	case ROLE_DISABLED:
		dbg_msg("Z");
		break;
	case ROLE_DESIGNATED:
		dbg_msg("D");
		break;
	case ROLE_ROOT:
		dbg_msg("R");
		break;
	case ROLE_ALTERNATE:
		dbg_msg("A");
		break;
	case ROLE_BACKUP:
		dbg_msg("B");
		break;
	case ROLE_MASTER:
		dbg_msg("M");
		break;
	default:
		dbg_msg(".");
	}
	switch (selectedRole) {
	case ROLE_DISABLED:
		dbg_msg("z");
		break;
	case ROLE_DESIGNATED:
		dbg_msg("d");
		break;
	case ROLE_ROOT:
		dbg_msg("r");
		break;
	case ROLE_ALTERNATE:
		dbg_msg("a");
		break;
	case ROLE_BACKUP:
		dbg_msg("b");
		break;
	case ROLE_MASTER:
		dbg_msg("m");
		break;
	default:
		dbg_msg(".");
	}
	dbg_msg(" ");
	switch (infoIs) {
	case INFO_TYPE_DISABLED:
		dbg_msg("Z");
		break;
	case INFO_TYPE_MINE:
		dbg_msg("M");
		break;
	case INFO_TYPE_AGED:
		dbg_msg("A");
		break;
	case INFO_TYPE_RECEIVED:
		dbg_msg("R");
		break;
	default:
		dbg_msg(".");
	}
	dbg_msg(" ");
	dbg_msg("%c", agree ? 'A' : '.');
	dbg_msg("%c", agreed ? 'a' : '.');
	dbg_msg("%c", master ? 'M' : '.');
	dbg_msg("%c", mastered ? 'm' : '.');
	dbg_msg("%c", proposing ? 'P' : '.');
	dbg_msg("%c", proposed ? 'p' : '.');
	dbg_msg("%c", sync ? 'S' : '.');
	dbg_msg("%c", synced ? 's' : '.');
	dbg_msg("%c", learn ? 'L' : '.');
	dbg_msg("%c", learning ? 'l' : '.');
	dbg_msg("%c", forward ? 'F' : '.');
	dbg_msg("%c", forwarding ? 'f' : '.');
	dbg_msg("%c", disputed ? 'D' : '.');
	dbg_msg("%c", isolate ? 'I' : '.');
	dbg_msg("%c", operEdge ? 'E' : '.');
	dbg_msg("%c", reRoot ? 'R' : '.');
	dbg_msg("%c", tcProp ? 'T' : '.');
	dbg_msg("%c", rcvdTc ? 'C' : '.');
	dbg_msg("  ");
	for (rx = 0; rx < NUM_OF_PORT_STATE_MACHINES; rx++)
		dbg_msg("%2d", p->states[rx][p->MSTI]);
	dbg_msg("  %s\n", msg);
}  /* dbg_stp */

static void d_stp_states(struct ksz_stp_bridge *br)
{
	int i;
	struct ksz_stp_port *p;

	dbg_msg("\n");
	for (i = 0; i < br->port_cnt; i++) {
		p = &br->ports[i];
		if (p->off)
			continue;
		p->MSTI = 0;
		FOREACH_T_IN_P(
			dbg_stp(p, "", false);
		)
	}
}
#endif


static void stp_one_sec_init(struct ksz_stp_port *p)
{
	tick = FALSE;
}  /* stp_one_sec_init */

static void stp_one_sec_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state, (tick), STP_PortTimers_TICK);
}  /* stp_one_sec_next */

#define dec_timer(x)	if (x) x -= STP_TIMER_TICK
#define dec(x)		if (x) x--

static void stp_tick_init(struct ksz_stp_port *p)
{
	int i;

	for (i = 0; i < NUM_OF_PORT_TIMERS; i++)
		dec_timer(p->vars.timers[i]);
	FOREACH_T_IN_P(
		for (i = 0; i < NUM_OF_MSTI_TIMERS; i++)
			dec_timer(p->mvars[p->MSTI].timers[i]);
		p->br->MSTI = p->MSTI;
		if (!tcWhile)
			isTC &= ~(1 << p->port_index);
		if (!p->port_index && !(helloWhen % STP_TIMER_SCALE))
			timeSinceTC++;
	)
	p->br->MSTI = 0;
	if (!(helloWhen % STP_TIMER_SCALE))
		dec(txCount);
}  /* stp_tick_init */

static void stp_tick_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state, TRUE, STP_PortTimers_ONE_SECOND);
}  /* stp_tick_next */

static int PortTimers(struct ksz_stp_port *p)
{
	struct ksz_stp_state state_info;
	u8 *state = &p->states[p->state_index][0];
	int ret = 0;

	state_info.index = STP_PortTimers;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = STP_PortTimers_ONE_SECOND;
	}
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_PortTimers_ONE_SECOND:
			if (stp_proc_state(p, &state_info,
			    stp_one_sec_init, stp_one_sec_next))
				goto done;
			break;
		case STP_PortTimers_TICK:
			if (stp_proc_state(p, &state_info,
			    stp_tick_init, stp_tick_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* PortTimers */

static void stp_rx_discard_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_RX
	dbg_stp(p, __func__, false);
#endif
	rcvdBPDU = rcvdRSTP = rcvdSTP = FALSE;
	clearAllRcvdMsgs();
	edgeDelayWhile = MigrateTime;
}  /* stp_rx_discard_init */

static void stp_rx_discard_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(rcvdBPDU && portEnabled && enableBPDUrx),
		STP_PortReceive_RECEIVE);
}  /* stp_rx_discard_next */

static void stp_rx_receive_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_RX
	dbg_stp(p, __func__, true);
#endif
	updtBPDUVersion();
	rcvdInternal = fromSameRegion();
	rcvMsgs();
	isolate =
	operEdge = rcvdBPDU = FALSE;
	edgeDelayWhile = MigrateTime;
}  /* stp_rx_receive_init */

static void stp_rx_receive_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(rcvdBPDU && portEnabled && enableBPDUrx && !rcvdAnyMsg()),
		STP_PortReceive_RECEIVE);
}  /* stp_rx_receive_next */

static void stp_rx_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	/* Reset rcvdBPDU and edgeDelayWhile if !portEnabled. */
	stp_change_state(state,
		((rcvdBPDU || NEQ(edgeDelayWhile, MigrateTime)) &&
		!portEnabled),
		STP_PortReceive_DISCARD);
}  /* stp_rx_next */

static int PortReceive(struct ksz_stp_port *p)
{
	struct ksz_stp_state state_info;
	u8 *state = &p->states[p->state_index][0];
	int ret = 0;

	state_info.index = STP_PortReceive;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = STP_PortReceive_DISCARD;
	} else
		stp_rx_next(p, &state_info);
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_PortReceive_DISCARD:
			if (stp_proc_state(p, &state_info,
			    stp_rx_discard_init, stp_rx_discard_next))
				goto done;
			break;
		case STP_PortReceive_RECEIVE:
			if (stp_proc_state(p, &state_info,
			    stp_rx_receive_init, stp_rx_receive_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* PortReceive */

static void stp_proto_check_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_PROTO
	dbg_stp(p, __func__, false);
#endif
	mcheck = FALSE;
	sendRSTP = rstpVersion;
	mdelayWhile = MigrateTime;
}  /* stp_proto_check_init */

static void stp_proto_check_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(0 == mdelayWhile),
		STP_PortProtoMigr_SENSING);

	/* Reset mdelayWhile if !portEnabled */
	stp_change_state(state,
		(NEQ(mdelayWhile, MigrateTime) && !portEnabled),
		STP_PortProtoMigr_CHECKING_RSTP);
}  /* stp_proto_check_next */

static void stp_proto_select_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	sendRSTP = FALSE;
	mdelayWhile = MigrateTime;
}  /* stp_proto_select_init */

static void stp_proto_select_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		((0 == mdelayWhile) || !portEnabled || mcheck),
		STP_PortProtoMigr_SENSING);
}  /* stp_proto_select_next */

static void stp_proto_sense_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	rcvdRSTP = rcvdSTP = FALSE;
}  /* stp_proto_sense_init */

static void stp_proto_sense_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(!portEnabled || mcheck || (rstpVersion && !sendRSTP &&
		rcvdRSTP)),
		STP_PortProtoMigr_CHECKING_RSTP);
	stp_change_state(state,
		(sendRSTP && rcvdSTP),
		STP_PortProtoMigr_SELECTING_STP);
}  /* stp_proto_sense_next */

static int PortProtocolMigration(struct ksz_stp_port *p)
{
	struct ksz_stp_state state_info;
	u8 *state = &p->states[p->state_index][0];
	int ret = 0;

	state_info.index = STP_PortProtoMigr;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = STP_PortProtoMigr_CHECKING_RSTP;
	}
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_PortProtoMigr_CHECKING_RSTP:
			if (stp_proc_state(p, &state_info,
			    stp_proto_check_init, stp_proto_check_next))
				goto done;
			break;
		case STP_PortProtoMigr_SELECTING_STP:
			if (stp_proc_state(p, &state_info,
			    stp_proto_select_init, stp_proto_select_next))
				goto done;
			break;
		case STP_PortProtoMigr_SENSING:
			if (stp_proc_state(p, &state_info,
			    stp_proto_sense_init, stp_proto_sense_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* PortProtocolMigration */

static void stp_br_det_edge_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	operEdge = TRUE;
	isolate = FALSE;
do {
	struct ksz_stp_dbg_times *x = &p->dbg_times[p->MSTI];

if (x->block_jiffies)
dbg_msg(" b: %d:%d=%ld %s\n", p->port_index, p->MSTI,
jiffies - x->block_jiffies, __func__);
} while (0);
}  /* stp_br_det_edge_init */

static void stp_br_det_edge_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(((!portEnabled || !AutoEdge) && !AdminEdge) || !operEdge),
		STP_BridgeDetection_NOT_EDGE);
}  /* stp_br_det_edge_next */

static void stp_br_det_not_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_BR_DET
	dbg_stp(p, __func__, false);
#endif
	operEdge = FALSE;
	isolate = FALSE;
}  /* stp_br_det_not_init */

static void stp_br_det_not_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		((!portEnabled && AdminEdge) ||
		((0 == edgeDelayWhile) && AutoEdge && sendRSTP && proposing)),
		STP_BridgeDetection_EDGE);
	if (ForceProtocolVersion <= 2)
		return;

	/* Get in isolated mode where the port stays closed. */
	stp_change_state(state,
		((0 == edgeDelayWhile) && !AdminEdge && !AutoEdge && sendRSTP
		&& proposing && operPointToPointMAC),
		STP_BridgeDetection_ISOLATED);
}  /* stp_br_det_not_next */

static void stp_br_det_isolate_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_BR_DET
	dbg_stp(p, __func__, false);
#endif
	operEdge = FALSE;
	isolate = TRUE;
}  /* stp_br_det_isolate_init */

static void stp_br_det_isolate_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(AdminEdge || AutoEdge || !isolate || !operPointToPointMAC),
		STP_BridgeDetection_NOT_EDGE);
}  /* stp_br_det_isolate_next */

static int BridgeDetection(struct ksz_stp_port *p)
{
	struct ksz_stp_state state_info;
	u8 *state = &p->states[p->state_index][0];
	int ret = 0;

	state_info.index = STP_BridgeDetection;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = AdminEdge ?
			STP_BridgeDetection_EDGE :
			STP_BridgeDetection_NOT_EDGE;
	}
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_BridgeDetection_EDGE:
			if (stp_proc_state(p, &state_info,
			    stp_br_det_edge_init, stp_br_det_edge_next))
				goto done;
			break;
		case STP_BridgeDetection_NOT_EDGE:
			if (stp_proc_state(p, &state_info,
			    stp_br_det_not_init, stp_br_det_not_next))
				goto done;
			break;
		case STP_BridgeDetection_ISOLATED:
			if (stp_proc_state(p, &state_info,
			    stp_br_det_isolate_init, stp_br_det_isolate_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* BridgeDetection */

static void stp_tx_init_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TX
	dbg_stp(p, __func__, false);
#endif
#if 0

	/*
	 * Not sure why newInfo is set here.  For STP BPUDs are sent only
	 * when the port is Designated or Root.  For RSTP the txRstp routine
	 * can be called even when the port role is not defined!
	 */
#if 0
	/* Send RSTP after initialization when the port is disabled? */
	if (!sendRSTP)
#endif
	newInfo = newInfoMsti = TRUE;
#endif
	txCount = 0;
}  /* stp_tx_init_init */

static void stp_tx_init_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortTransmit_IDLE);
}  /* stp_tx_init_next */

static void stp_tx_periodic_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TX_0
	dbg_stp(p, __func__, false);
#endif
	newInfo = newInfo || (cistDesignatedPort() ||
		(cistRootPort() && (tcWhile != 0)));
	newInfoMsti = newInfoMsti || mstiDesignatedOrTCpropagatingRootPort();
}  /* stp_tx_periodic_init */

static void stp_tx_periodic_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortTransmit_IDLE);
}  /* stp_tx_periodic_next */

static void stp_tx_config_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TX
	dbg_stp(p, __func__, false);
#endif
	newInfo = FALSE;
	txConfig();
	txCount++;
	tcAck = FALSE;
}  /* stp_tx_config_init */

static void stp_tx_config_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortTransmit_IDLE);
}  /* stp_tx_config_next */

static void stp_tx_tcn_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TX
	dbg_stp(p, __func__, false);
#endif
	newInfo = FALSE;
	txTcn();
	txCount++;
}  /* stp_tx_tcn_init */

static void stp_tx_tcn_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortTransmit_IDLE);
}  /* stp_tx_tcn_next */

static void stp_tx_rstp_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TX
	dbg_stp(p, __func__, false);
#endif
	txRstp();
	newInfo = newInfoMsti = FALSE;
	txCount++;
	tcAck = FALSE;
}  /* stp_tx_rstp_init */

static void stp_tx_rstp_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortTransmit_IDLE);
}  /* stp_tx_rstp_next */

static void stp_tx_idle_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TX_0
	dbg_stp(p, __func__, false);
#endif
	helloWhen = HelloTime;
}  /* stp_tx_idle_init */

static void stp_tx_idle_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		((0 == helloWhen) && allTransmitReady()),
		STP_PortTransmit_PERIODIC);
	stp_change_state(state,
		((sendRSTP && (newInfo || (newInfoMsti && !mstiMasterPort())))
		&& allTransmitReady() && canSend),
		STP_PortTransmit_RSTP);
	stp_change_state(state,
		((!sendRSTP && newInfo && cistRootPort()) &&
		allTransmitReady() && canSend),
		STP_PortTransmit_TCN);
	stp_change_state(state,
		((!sendRSTP && newInfo && cistDesignatedPort()) &&
		allTransmitReady() && canSend),
		STP_PortTransmit_CONFIG);
}  /* stp_tx_idle_next */

static int PortTransmit(struct ksz_stp_port *p)
{
	struct ksz_stp_state state_info;
	u8 *state = &p->states[p->state_index][0];
	int ret = 0;

	state_info.index = STP_PortTransmit;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = STP_PortTransmit_INIT;
	}
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_PortTransmit_INIT:
			if (stp_proc_state(p, &state_info,
			    stp_tx_init_init, stp_tx_init_next))
				goto done;
			break;
		case STP_PortTransmit_PERIODIC:
			if (stp_proc_state(p, &state_info,
			    stp_tx_periodic_init, stp_tx_periodic_next))
				goto done;
			break;
		case STP_PortTransmit_CONFIG:
			if (stp_proc_state(p, &state_info,
			    stp_tx_config_init, stp_tx_config_next))
				goto done;
			break;
		case STP_PortTransmit_TCN:
			if (stp_proc_state(p, &state_info,
			    stp_tx_tcn_init, stp_tx_tcn_next))
				goto done;
			break;
		case STP_PortTransmit_RSTP:
			if (stp_proc_state(p, &state_info,
			    stp_tx_rstp_init, stp_tx_rstp_next))
				goto done;
			break;
		case STP_PortTransmit_IDLE:
			if (stp_proc_state(p, &state_info,
			    stp_tx_idle_init, stp_tx_idle_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* PortTransmit */

static void stp_info_disable_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_INFO
	dbg_stp(p, __func__, false);
#endif
	rcvdMsg = FALSE;
	proposing = proposed = agree = agreed = FALSE;
	rcvdInfoWhile = 0;

	/* Change role in PortRoleSelection. */
	infoIs = INFO_TYPE_DISABLED;
	reselect = TRUE;
	selected = FALSE;
}  /* stp_info_disable_init */

static void stp_info_disable_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(portEnabled),
		STP_PortInfo_AGED);
	stp_change_state(state,
		(rcvdMsg),
		STP_PortInfo_DISABLED);
}  /* stp_info_disable_next */

static void stp_info_age_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	/* Change role in PortRoleSelection. */
	infoIs = INFO_TYPE_AGED;
	reselect = TRUE;
	selected = FALSE;
}  /* stp_info_age_init */

static void stp_info_age_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(selected && updtInfo),
		STP_PortInfo_UPDATE);
}  /* stp_info_age_next */

static void stp_info_update_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	proposing = proposed = FALSE;
	agreed = agreed && betterorsameInfo(INFO_TYPE_MINE);

#if 1
	/*
	 * When switching back to Root Bridge because of timeout the port will
	 * have inferior priority, resetting both agreed and synced.  The port
	 * is still in forwarding state though.  When the port becomes
	 * forwarding agreed is always set.  Now that agreed is reset synced
	 * will not be set, making allSynced to always fail, which prevents
	 * the Root Port from sending an Agreement, thus failing RSTP.op.5.3.
	 */
	if (forward)
		agreed = sendRSTP;
#endif
	synced = synced && agreed;

#if 0
	/* agree is never turned off if priority is changed. */
	agree = FALSE;
#endif
#ifdef DBG_STP_STATE_INFO
dbg_msg("  %s %d %d\n", __func__, agreed, synced);
#endif
	COPY(portPriority, designatedPriority);
	COPY(portTimes, designatedTimes);
	updtInfo = FALSE;
	infoIs = INFO_TYPE_MINE;
	newInfoXst(TRUE);
}  /* stp_info_update_init */

static void stp_info_update_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortInfo_CURRENT);
}  /* stp_info_update_next */

static void stp_info_superior_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	infoInternal = rcvdInternal;
	agreed = proposing = FALSE;
	recordProposal();
	setTcFlags();
	agree = agree && betterorsameInfo(INFO_TYPE_RECEIVED);
	recordAgreement();
	synced = synced && agreed;
	recordPriority();
	recordTimes();

	/* Keep from aged out. */
	updtRcvdInfoWhile();

	/* Change role in PortRoleSelection. */
	infoIs = INFO_TYPE_RECEIVED;
	reselect = TRUE;
	selected = FALSE;

	rcvdMsg = FALSE;
}  /* stp_info_superior_init */

static void stp_info_superior_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortInfo_CURRENT);
}  /* stp_info_superior_next */

static void stp_info_repeat_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, true);
#endif
	infoInternal = rcvdInternal;
	recordProposal();
	setTcFlags();
	recordAgreement();

	/* Keep from aged out. */
	updtRcvdInfoWhile();
	rcvdMsg = FALSE;
}  /* stp_info_repeat_init */

static void stp_info_repeat_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortInfo_CURRENT);
}  /* stp_info_repeat_next */

static void stp_info_inferior_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	recordDispute();

#if 1
	/*
	 * Priority is not recorded, so in updtRolesTree this port is still
	 * selected as Root Port!
	 * This can happen in test tool as the bridge id and port id is changed
	 * from the port!
	 */
	if (p->br->hack_5_2 && INFO_TYPE_RECEIVED == infoIs &&
	    memcmp(msgPriority.bridge_id.addr, portPriority.bridge_id.addr,
	    ETH_ALEN)) {
dbg_msg(" bridge id changed!\n");
		recordPriority();
		recordTimes();
	}
#endif

	/* Will age out if keep receiving inferior messages. */
	rcvdMsg = FALSE;
}  /* stp_info_inferior_init */

static void stp_info_inferior_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortInfo_CURRENT);
}  /* stp_info_inferior_next */

static void stp_info_not_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_INFO
	dbg_stp(p, __func__, false);
#endif
	recordAgreement();
#if 1
	/*
	 * This port is not yet designated but receives an Agreement, most
	 * likely when running the test tool.  Prepare the portPriority so that
	 * betterorsameInfo can return true.
	 */
	if (agreed && role != ROLE_DESIGNATED && role != ROLE_BACKUP) {
dbgPriority(&rootPriority, &rootPortId);
		COPY(portPriority, rootPriority);
		COPY(portPriority.port_id, portId);
		COPY(portTimes, rootTimes);
	}
#endif
	setTcFlags();
	rcvdMsg = FALSE;

	if (role != ROLE_BACKUP)
		stp_chk_flush(p);
}  /* stp_info_not_init */

static void stp_info_not_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortInfo_CURRENT);
}  /* stp_info_not_next */

static void stp_info_other_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	rcvdMsg = FALSE;
}  /* stp_info_other_init */

static void stp_info_other_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortInfo_CURRENT);
}  /* stp_info_other_next */

static void stp_info_cur_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_INFO
	dbg_stp(p, __func__, true);
#endif
}  /* stp_info_cur_init */

static void stp_info_cur_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(selected && updtInfo),
		STP_PortInfo_UPDATE);
	stp_change_state(state,
		((infoIs == INFO_TYPE_RECEIVED) && (0 == rcvdInfoWhile) &&
		!updtInfo && !rcvdXstMsg()),
		STP_PortInfo_AGED);
	stp_change_state(state,
		(rcvdXstMsg() && !updtXstInfo()),
		STP_PortInfo_RECEIVE);
}  /* stp_info_cur_next */

static void stp_info_receive_init(struct ksz_stp_port *p)
{
	rcvdInfo = rcvInfo();
	recordMastered();
#ifdef DBG_STP_RX
if (p->dbg_rx)
dbg_msg("  %s:%u:%d=%d\n", __func__, p->port_index, p->MSTI, rcvdInfo);
#endif
}  /* stp_info_receive_init */

static void stp_info_receive_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(rcvdInfo == INFO_SUPERIOR_DESIGNATED),
		STP_PortInfo_SUPERIOR_DESIGNATED);
	stp_change_state(state,
		(rcvdInfo == INFO_REPEATED_DESIGNATED),
		STP_PortInfo_REPEATED_DESIGNATED);
	stp_change_state(state,
		(rcvdInfo == INFO_INFERIOR_DESIGNATED),
		STP_PortInfo_INFERIOR_DESIGNATED);
	stp_change_state(state,
		(rcvdInfo == INFO_INFERIOR_ROOT_ALT),
		STP_PortInfo_NOT_DESIGNATED);
	stp_change_state(state,
		(rcvdInfo == INFO_OTHER),
		STP_PortInfo_OTHER);
}  /* stp_info_receive_next */

static void stp_info_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	/* Notify port is disabled. */
	stp_change_state(state,
		(!portEnabled && (infoIs != INFO_TYPE_DISABLED)),
		STP_PortInfo_DISABLED);
}  /* stp_info_next */

static int PortInformation(struct ksz_stp_port *p)
{
	struct ksz_stp_state state_info;
	u8 *state = &p->states[p->state_index][p->MSTI];
	int ret = 0;

	state_info.index = STP_PortInfo;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = STP_PortInfo_DISABLED;
	} else
		stp_info_next(p, &state_info);
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_PortInfo_DISABLED:
			if (stp_proc_state(p, &state_info,
			    stp_info_disable_init, stp_info_disable_next))
				goto done;
			break;
		case STP_PortInfo_AGED:
			if (stp_proc_state(p, &state_info,
			    stp_info_age_init, stp_info_age_next))
				goto done;
			break;
		case STP_PortInfo_UPDATE:
			if (stp_proc_state(p, &state_info,
			    stp_info_update_init, stp_info_update_next))
				goto done;
			break;
		case STP_PortInfo_SUPERIOR_DESIGNATED:
			if (stp_proc_state(p, &state_info,
			    stp_info_superior_init, stp_info_superior_next))
				goto done;
			break;
		case STP_PortInfo_REPEATED_DESIGNATED:
			if (stp_proc_state(p, &state_info,
			    stp_info_repeat_init, stp_info_repeat_next))
				goto done;
			break;
		case STP_PortInfo_INFERIOR_DESIGNATED:
			if (stp_proc_state(p, &state_info,
			    stp_info_inferior_init, stp_info_inferior_next))
				goto done;
			break;
		case STP_PortInfo_NOT_DESIGNATED:
			if (stp_proc_state(p, &state_info,
			    stp_info_not_init, stp_info_not_next))
				goto done;
			break;
		case STP_PortInfo_OTHER:
			if (stp_proc_state(p, &state_info,
			    stp_info_other_init, stp_info_other_next))
				goto done;
			break;
		case STP_PortInfo_CURRENT:
			if (stp_proc_state(p, &state_info,
			    stp_info_cur_init, stp_info_cur_next))
				goto done;
			break;
		case STP_PortInfo_RECEIVE:
			if (stp_proc_state(p, &state_info,
			    stp_info_receive_init, stp_info_receive_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* PortInformation */

static void stp_role_sel_br_init(struct ksz_stp_port *p)
{
	struct ksz_stp_bridge *br = p->br;

#ifdef DBG_STP_STATE_ROLE_SEL
dbg_msg("  %s\n", __func__);
#endif
	updtRoleDisabledTree();
}  /* stp_role_sel_br_init */

static void stp_role_sel_br_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleSel_ROLE_SELECTION);
}  /* stp_role_sel_br_next */

static void stp_role_sel_role_init(struct ksz_stp_port *p)
{
	struct ksz_stp_bridge *br = p->br;

#ifdef DBG_STP_STATE_ROLE_SEL
dbg_msg("  %s\n", __func__);
#endif
	clearReselectTree();
	updtRolesTree();
	setSelectedTree();
}  /* stp_role_sel_role_init */

static void stp_role_sel_role_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	FOREACH_P_IN_T(
		if (reselect) {
			state->new_state = STP_PortRoleSel_ROLE_SELECTION;
			break;
		}
	)
	if (state->new_state && !p->br->MSTI) {
		FOREACH_P_IN_T(
			FOREACH_M_IN_P(
				reselect = TRUE;
			)
		)
	}
}  /* stp_role_sel_role_next */

static int PortRoleSelection(struct ksz_stp_bridge *br)
{
	struct ksz_stp_state state_info;
	struct ksz_stp_port *p = &br->ports[0];
	u8 *state = &br->states[br->state_index][br->MSTI];
	int ret = 0;

	state_info.index = STP_PortRoleSel;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = STP_PortRoleSel_INIT_BRIDGE;
	}
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_PortRoleSel_INIT_BRIDGE:
			if (stp_proc_state(p, &state_info,
			    stp_role_sel_br_init, stp_role_sel_br_next))
				goto done;
			break;
		case STP_PortRoleSel_ROLE_SELECTION:
			if (stp_proc_state(p, &state_info,
			    stp_role_sel_role_init, stp_role_sel_role_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* PortRoleSelection */

static void stp_role_tr_init_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_ROLE_TR
	dbg_stp(p, __func__, false);
#endif
	role = ROLE_DISABLED;
	learn = forward = FALSE;
	synced = FALSE;
	sync = reRoot = TRUE;
	rrWhile = FwdDelay;
	fdWhile = MaxAge;
	rbWhile = 0;
}  /* stp_role_tr_init_init */

static void stp_role_tr_init_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	int cond = canChange;

#if 1
	cond = TRUE;
#endif
	stp_change_state(state,
		cond, STP_PortRoleTrans_DISABLE_PORT);
}  /* stp_role_tr_init_next */

static void stp_role_tr_dis_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	role = ROLE_DISABLED;
	learn = forward = FALSE;

#if 1
	/* Port is disabled.  Do not send. */
#ifdef DBG_STP_STATE
if (newInfo)
dbg_msg("  %s clear newInfo\n", __func__);
if (newInfoMsti)
dbg_msg("  %s clear newInfoMsti\n", __func__);
#endif
#if 1
	newInfo = newInfoMsti = FALSE;
#endif
#endif
}  /* stp_role_tr_dis_init */

static void stp_role_tr_dis_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		((!learning && !forwarding) && canChange),
		STP_PortRoleTrans_DISABLED_PORT);
}  /* stp_role_tr_dis_next */

static void stp_role_tr_disd_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_ROLE_TR
	dbg_stp(p, __func__, false);
#endif
	fdWhile = MaxAge;
#ifdef DBG_STP_STATE
if (!synced)
dbg_msg(" %s:%u\n", __func__, p->port_index);
#endif
	synced = TRUE;
	rrWhile = 0;
	sync = reRoot = FALSE;
}  /* stp_role_tr_disd_init */

static void stp_role_tr_disd_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	/* Reset if !updtInfo. */
	stp_change_state(state,
		((NEQ(fdWhile, MaxAge) || sync || reRoot || !synced) &&
		canChange),
		STP_PortRoleTrans_DISABLED_PORT);
}  /* stp_role_tr_disd_next */

static void stp_role_tr_m_proposed_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	setSyncTree();
	proposed = FALSE;
}  /* stp_role_tr_m_proposed_init */

static void stp_role_tr_m_proposed_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_MASTER_PORT);
}  /* stp_role_tr_m_proposed_next */

static void stp_role_tr_m_agreed_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	proposed = sync = FALSE;
	agree = TRUE;
}  /* stp_role_tr_m_agreed_init */

static void stp_role_tr_m_agreed_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_MASTER_PORT);
}  /* stp_role_tr_m_agreed_next */

static void stp_role_tr_m_s_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	rrWhile = 0;
	synced = TRUE;
	sync = FALSE;
}  /* stp_role_tr_m_s_init */

static void stp_role_tr_m_s_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_MASTER_PORT);
}  /* stp_role_tr_m_s_next */

static void stp_role_tr_m_retired_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	reRoot = FALSE;
}  /* stp_role_tr_m_retired_init */

static void stp_role_tr_m_retired_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_MASTER_PORT);
}  /* stp_role_tr_m_retired_next */

static void stp_role_tr_m_discard_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	learn = forward = disputed = FALSE;
	fdWhile = forwardDelay();
}  /* stp_role_tr_m_discard_init */

static void stp_role_tr_m_discard_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_MASTER_PORT);
}  /* stp_role_tr_m_discard_next */

static void stp_role_tr_m_l_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	fdWhile = forwardDelay();
	learn = TRUE;
}  /* stp_role_tr_m_l_init */

static void stp_role_tr_m_l_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_MASTER_PORT);
}  /* stp_role_tr_m_l_next */

static void stp_role_tr_m_f_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	fdWhile = 0;
	forward = TRUE;
	agreed = sendRSTP;
}  /* stp_role_tr_m_f_init */

static void stp_role_tr_m_f_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_MASTER_PORT);
}  /* stp_role_tr_m_f_next */

static void stp_role_tr_m_p_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	if (role != ROLE_ROOT)
		dbg_stp(p, __func__, false);
#endif
	role = ROLE_MASTER;
}  /* stp_role_tr_m_p_init */

static void stp_role_tr_m_p_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		((proposed && !agree) && canChange),
		STP_PortRoleTrans_MASTER_PROPOSED);
	stp_change_state(state,
		(((allSynced() && !agree) || (proposed && agree)) && canChange),
		STP_PortRoleTrans_MASTER_AGREED);
	stp_change_state(state,
		(((!learning && !forwarding && !synced) ||
		(agreed && !synced) || (operEdge && !synced) ||
		(sync && synced)) && canChange),
		STP_PortRoleTrans_MASTER_SYNCED);
	stp_change_state(state,
		((reRoot && (0 == rrWhile)) && canChange),
		STP_PortRoleTrans_MASTER_RETIRED);
	stp_change_state(state,
		((((sync && !synced) || (reRoot && (rrWhile != 0)) || disputed)
		&& !operEdge && (learn || forward)) && canChange),
		STP_PortRoleTrans_MASTER_DISCARD);
	stp_change_state(state,
		((((0 == fdWhile) || allSynced()) && !learn) && canChange),
		STP_PortRoleTrans_MASTER_LEARN);
	stp_change_state(state,
		((((0 == fdWhile) || allSynced()) && (learn && !forward)) &&
		canChange),
		STP_PortRoleTrans_MASTER_FORWARD);
}  /* stp_role_tr_m_p_next */

static void stp_role_tr_reroot_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	setReRootTree();
}  /* stp_role_tr_reroot_init */

static void stp_role_tr_reroot_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ROOT_PORT);
}  /* stp_role_tr_reroot_next */

static void stp_role_tr_rerooted_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	reRoot = FALSE;
}  /* stp_role_tr_rerooted_init */

static void stp_role_tr_rerooted_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ROOT_PORT);
}  /* stp_role_tr_rerooted_next */

static void stp_role_tr_root_proposed_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	setSyncTree();
	proposed = FALSE;
}  /* stp_role_tr_root_proposed_init */

static void stp_role_tr_root_proposed_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ROOT_PORT);
}  /* stp_role_tr_root_proposed_next */

static void stp_role_tr_root_agreed_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	proposed = sync = FALSE;
	agree = TRUE;
	newInfoXst(TRUE);
}  /* stp_role_tr_root_agreed_init */

static void stp_role_tr_root_agreed_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ROOT_PORT);
}  /* stp_role_tr_root_agreed_next */

static void stp_role_tr_root_s_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	synced = TRUE;
	sync = FALSE;
}  /* stp_role_tr_root_s_init */

static void stp_role_tr_root_s_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ROOT_PORT);
}  /* stp_role_tr_root_s_next */

static void stp_role_tr_root_discard_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	if (disputed)
		rbWhile = 3 * HelloTime;
	learn = forward = disputed = FALSE;
	fdWhile = FwdDelay;
}  /* stp_role_tr_root_discard_init */

static void stp_role_tr_root_discard_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ROOT_PORT);
}  /* stp_role_tr_root_discard_next */

static void stp_role_tr_root_l_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	fdWhile = forwardDelay();
	learn = TRUE;
}  /* stp_role_tr_root_l_init */

static void stp_role_tr_root_l_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ROOT_PORT);
}  /* stp_role_tr_root_l_next */

static void stp_role_tr_root_f_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	fdWhile = 0;
	forward = TRUE;
}  /* stp_role_tr_root_f_init */

static void stp_role_tr_root_f_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ROOT_PORT);
}  /* stp_role_tr_root_f_next */

static void stp_role_tr_root_p_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	if (role != ROLE_ROOT)
		dbg_stp(p, __func__, false);
#endif
	do {
		struct ksz_stp_info *stp = p->br->parent;
		struct ksz_sw *sw = stp->sw_dev;

		if (DesignatedPort)
			sw->ops->from_designated(sw, p->port_index, false);
		else if (!RootPort)
			sw->ops->from_backup(sw, p->port_index);
	} while (0);
	role = ROLE_ROOT;
	rrWhile = FwdDelay;
}  /* stp_role_tr_root_p_init */

static void stp_role_tr_root_p_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		((proposed && !agree) && canChange),
		STP_PortRoleTrans_ROOT_PROPOSED);
	stp_change_state(state,
		(((allSynced() && !agree) || (proposed && agree)) && canChange),
		STP_PortRoleTrans_ROOT_AGREED);
	stp_change_state(state,
		(((agreed && !synced) || (sync && synced)) && canChange),
		STP_PortRoleTrans_ROOT_SYNCED);
	stp_change_state(state,
		((!forward && (0 == rbWhile) && !reRoot) && canChange),
		STP_PortRoleTrans_REROOT);
	stp_change_state(state,
		((reRoot && forward) && canChange),
		STP_PortRoleTrans_REROOTED);
	stp_change_state(state,
		((((0 == fdWhile) || ((reRooted() && (0 == rbWhile)) &&
		rstpVersion)) && !learn) && canChange),
		STP_PortRoleTrans_ROOT_LEARN);
	stp_change_state(state,
		((((0 == fdWhile) || ((reRooted() && (0 == rbWhile)) &&
		rstpVersion)) && learn && !forward) && canChange),
		STP_PortRoleTrans_ROOT_FORWARD);
	stp_change_state(state,
		((disputed) && canChange),
		STP_PortRoleTrans_ROOT_DISCARD);
	stp_change_state(state,
		(NEQ(rrWhile, FwdDelay) && canChange),
		STP_PortRoleTrans_ROOT_PORT);
}  /* stp_role_tr_root_p_next */

static void stp_role_tr_desg_r_init(struct ksz_stp_port *p)
{
	int delay = EdgeDelay();

	if (AutoEdge && p->br->hack_4_1)
		delay = 0;

#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	proposing = TRUE;
	if (cist())
		edgeDelayWhile = delay;
	newInfoXst(TRUE);
}  /* stp_role_tr_desg_r_init */

static void stp_role_tr_desg_r_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_DESIGNATED_PORT);
}  /* stp_role_tr_desg_r_next */

static void stp_role_tr_desg_a_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	proposed = sync = FALSE;
	agree = TRUE;
	newInfoXst(TRUE);
}  /* stp_role_tr_desg_a_init */

static void stp_role_tr_desg_a_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_DESIGNATED_PORT);
}  /* stp_role_tr_desg_a_next */

static void stp_role_tr_desg_s_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	rrWhile = 0;
	synced = TRUE;
	sync = FALSE;
}  /* stp_role_tr_desg_s_init */

static void stp_role_tr_desg_s_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_DESIGNATED_PORT);
}  /* stp_role_tr_desg_s_next */

static void stp_role_tr_desg_retired_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	reRoot = FALSE;
}  /* stp_role_tr_desg_retired_init */

static void stp_role_tr_desg_retired_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_DESIGNATED_PORT);
}  /* stp_role_tr_desg_retired_next */

static void stp_role_tr_desg_discard_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	learn = forward = disputed = FALSE;
	fdWhile = forwardDelay();
}  /* stp_role_tr_desg_discard_init */

static void stp_role_tr_desg_discard_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_DESIGNATED_PORT);
}  /* stp_role_tr_desg_discard_next */

static void stp_role_tr_desg_l_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	learn = TRUE;
	fdWhile = forwardDelay();
do {
	struct ksz_stp_dbg_times *x = &p->dbg_times[p->MSTI];

if (x->block_jiffies)
dbg_msg(" b: %d:%d=%ld %d %s\n", p->port_index, p->MSTI,
jiffies - x->block_jiffies, fdWhile,
__func__);
} while (0);
}  /* stp_role_tr_desg_l_init */

static void stp_role_tr_desg_l_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_DESIGNATED_PORT);
}  /* stp_role_tr_desg_l_next */

static void stp_role_tr_desg_f_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	forward = TRUE;
	fdWhile = 0;
	agreed = sendRSTP;

#if 1
	/*
	 * proposing will be reset when infoIs is changed and betterorsameInfo
	 * is called, even though the forwarding state is not changed.  Why
	 * not just reset here?
	 */
	if (proposing)
		proposing = FALSE;
#endif
#ifdef DBG_STP_STATE_
	do {
		char buf[40];

		sprintf(buf, " %s", __func__);
	dbg_stp(p, buf, false);
	} while (0);
#endif
}  /* stp_role_tr_desg_f_init */

static void stp_role_tr_desg_f_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_DESIGNATED_PORT);
}  /* stp_role_tr_desg_f_next */

static void stp_role_tr_desg_p_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	if (role != ROLE_DESIGNATED)
		dbg_stp(p, __func__, false);
#endif
do {
	struct ksz_stp_dbg_times *x = &p->dbg_times[p->MSTI];

if (x->block_jiffies && role != ROLE_DESIGNATED)
dbg_msg(" b: %d:%d=%ld %d %s\n", p->port_index, p->MSTI,
jiffies - x->block_jiffies, fdWhile,
__func__);
} while (0);
	if (RootPort || AlternatePort) {
		struct ksz_stp_info *stp = p->br->parent;
		struct ksz_sw *sw = stp->sw_dev;

		sw->ops->to_designated(sw, p->port_index);
	}
	if (BackupPort) {
		struct ksz_stp_info *stp = p->br->parent;
		struct ksz_sw *sw = stp->sw_dev;

		sw->ops->from_backup(sw, p->port_index);
	}
	role = ROLE_DESIGNATED;
	if (cist()) {
		proposing = proposing ||
			(!AdminEdge && !AutoEdge && AutoIsolate &&
			operPointToPointMAC);
	}
}  /* stp_role_tr_desg_p_init */

static void stp_role_tr_desg_p_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		((!forward && !agreed && !proposing && !operEdge) &&
		canChange),
		STP_PortRoleTrans_DESIGNATED_PROPOSE);
	stp_change_state(state,
		((allSynced() && (proposed || !agree)) && canChange),
		STP_PortRoleTrans_DESIGNATED_AGREED);
	stp_change_state(state,
		(((!learning && !forwarding && !synced) ||
		(agreed && !synced) || (operEdge && !synced) ||
		(sync && synced)) && canChange),
		STP_PortRoleTrans_DESIGNATED_SYNCED);
	stp_change_state(state,
		((reRoot && (0 == rrWhile)) && canChange),
		STP_PortRoleTrans_DESIGNATED_RETIRED);
	stp_change_state(state,
		((((sync && !synced) || (reRoot && (rrWhile != 0)) || disputed
		|| isolate) && !operEdge && (learn || forward)) && canChange),
		STP_PortRoleTrans_DESIGNATED_DISCARD);
	stp_change_state(state,
		((((0 == fdWhile) || agreed || operEdge) &&
		((0 == rrWhile) || !reRoot) && !sync && !learn && !isolate) &&
		canChange),
		STP_PortRoleTrans_DESIGNATED_LEARN);
	stp_change_state(state,
		((((0 == fdWhile) || agreed || operEdge) &&
		((0 == rrWhile) || !reRoot) && !sync && (learn && !forward) &&
		!isolate) && canChange),
		STP_PortRoleTrans_DESIGNATED_FORWARD);
}  /* stp_role_tr_desg_p_next */

static void stp_role_tr_block_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	do {
		struct ksz_stp_info *stp = p->br->parent;
		struct ksz_sw *sw = stp->sw_dev;

		if (DesignatedPort && selectedRole == ROLE_ALTERNATE)
			sw->ops->from_designated(sw, p->port_index, true);
		else
			sw->ops->to_backup(sw, p->port_index);
	} while (0);
	role = selectedRole;
	learn = forward = FALSE;
}  /* stp_role_tr_block_init */

static void stp_role_tr_block_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		((!learning && !forwarding) && canChange),
		STP_PortRoleTrans_ALTERNATE_PORT);
}  /* stp_role_tr_block_next */

static void stp_role_tr_backup_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, true);
#endif
	rbWhile = 2 * HelloTime;
}  /* stp_role_tr_backup_init */

static void stp_role_tr_backup_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ALTERNATE_PORT);
}  /* stp_role_tr_backup_next */

static void stp_role_tr_alt_proposed_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	setSyncTree();
	proposed = FALSE;
}  /* stp_role_tr_alt_proposed_init */

static void stp_role_tr_alt_proposed_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ALTERNATE_PORT);
}  /* stp_role_tr_alt_proposed_next */

static void stp_role_tr_alt_a_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	proposed = FALSE;
	agree = TRUE;
	newInfoXst(TRUE);
}  /* stp_role_tr_alt_a_init */

static void stp_role_tr_alt_a_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_PortRoleTrans_ALTERNATE_PORT);
}  /* stp_role_tr_alt_a_next */

static void stp_role_tr_alt_p_init(struct ksz_stp_port *p)
{
	int delay = forwardDelay();

	if (p->br->hack_4_2)
		delay = FwdDelay;

#ifdef DBG_STP_STATE_ROLE_TR
	dbg_stp(p, __func__, true);
#endif
	fdWhile = delay;
	synced = TRUE;
	rrWhile = 0;
	sync = reRoot = FALSE;
}  /* stp_role_tr_alt_p_init */

static void stp_role_tr_alt_p_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	int delay = forwardDelay();

	if (p->br->hack_4_2)
		delay = FwdDelay;

	stp_change_state(state,
		((proposed && !agree) && canChange),
		STP_PortRoleTrans_ALTERNATE_PROPOSED);
	stp_change_state(state,
		(((allSynced() && !agree) || (proposed && agree)) && canChange),
		STP_PortRoleTrans_ALTERNATE_AGREED);
	state->change = 0;
	stp_change_state(state,
		((NEQ(rbWhile, 2 * HelloTime) && BackupPort) && canChange),
		STP_PortRoleTrans_BACKUP_PORT);
	stp_change_state(state,
		((NEQ(fdWhile, delay) || sync || reRoot || !synced) &&
		canChange),
		STP_PortRoleTrans_ALTERNATE_PORT);
	state->change = 1;
}  /* stp_role_tr_alt_p_next */

static void stp_role_tr_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(((selectedRole == ROLE_DISABLED) && (role != selectedRole)) &&
		canChange),
		STP_PortRoleTrans_DISABLE_PORT);
	stp_change_state(state,
		(((selectedRole == ROLE_MASTER) && (role != selectedRole)) &&
		canChange),
		STP_PortRoleTrans_MASTER_PORT);
	stp_change_state(state,
		(((selectedRole == ROLE_ROOT) && (role != selectedRole)) &&
		canChange),
		STP_PortRoleTrans_ROOT_PORT);
	stp_change_state(state,
		(((selectedRole == ROLE_DESIGNATED) && (role != selectedRole))
		&& canChange),
		STP_PortRoleTrans_DESIGNATED_PORT);
	stp_change_state(state,
		((((selectedRole == ROLE_ALTERNATE) ||
		(selectedRole == ROLE_BACKUP)) && (role != selectedRole)) &&
		canChange),
		STP_PortRoleTrans_BLOCK_PORT);
}  /* stp_role_tr_next */

static int PortRoleTransitions(struct ksz_stp_port *p)
{
	struct ksz_stp_state state_info;
	u8 *state = &p->states[p->state_index][p->MSTI];
	int ret = 0;

	state_info.index = STP_PortRoleTrans;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = STP_PortRoleTrans_INIT_PORT;
	} else
		stp_role_tr_next(p, &state_info);
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_PortRoleTrans_INIT_PORT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_init_init, stp_role_tr_init_next))
				goto done;
			break;
		case STP_PortRoleTrans_DISABLE_PORT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_dis_init, stp_role_tr_dis_next))
				goto done;
			break;
		case STP_PortRoleTrans_DISABLED_PORT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_disd_init, stp_role_tr_disd_next))
				goto done;
			break;
		case STP_PortRoleTrans_MASTER_PROPOSED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_m_proposed_init,
			    stp_role_tr_m_proposed_next))
				goto done;
			break;
		case STP_PortRoleTrans_MASTER_AGREED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_m_agreed_init,
			    stp_role_tr_m_agreed_next))
				goto done;
			break;
		case STP_PortRoleTrans_MASTER_SYNCED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_m_s_init, stp_role_tr_m_s_next))
				goto done;
			break;
		case STP_PortRoleTrans_MASTER_RETIRED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_m_retired_init,
			    stp_role_tr_m_retired_next))
				goto done;
			break;
		case STP_PortRoleTrans_MASTER_DISCARD:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_m_discard_init,
			    stp_role_tr_m_discard_next))
				goto done;
			break;
		case STP_PortRoleTrans_MASTER_LEARN:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_m_l_init, stp_role_tr_m_l_next))
				goto done;
			break;
		case STP_PortRoleTrans_MASTER_FORWARD:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_m_f_init, stp_role_tr_m_f_next))
				goto done;
			break;
		case STP_PortRoleTrans_MASTER_PORT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_m_p_init, stp_role_tr_m_p_next))
				goto done;
			break;
		case STP_PortRoleTrans_ROOT_PROPOSED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_root_proposed_init,
			    stp_role_tr_root_proposed_next))
				goto done;
			break;
		case STP_PortRoleTrans_ROOT_AGREED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_root_agreed_init,
			    stp_role_tr_root_agreed_next))
				goto done;
			break;
		case STP_PortRoleTrans_ROOT_SYNCED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_root_s_init, stp_role_tr_root_s_next))
				goto done;
			break;
		case STP_PortRoleTrans_REROOT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_reroot_init, stp_role_tr_reroot_next))
				goto done;
			break;
		case STP_PortRoleTrans_REROOTED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_rerooted_init,
			    stp_role_tr_rerooted_next))
				goto done;
			break;
		case STP_PortRoleTrans_ROOT_DISCARD:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_root_discard_init,
			    stp_role_tr_root_discard_next))
				goto done;
			break;
		case STP_PortRoleTrans_ROOT_LEARN:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_root_l_init, stp_role_tr_root_l_next))
				goto done;
			break;
		case STP_PortRoleTrans_ROOT_FORWARD:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_root_f_init, stp_role_tr_root_f_next))
				goto done;
			break;
		case STP_PortRoleTrans_ROOT_PORT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_root_p_init, stp_role_tr_root_p_next))
				goto done;
			break;
		case STP_PortRoleTrans_DESIGNATED_PROPOSE:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_desg_r_init, stp_role_tr_desg_r_next))
				goto done;
			break;
		case STP_PortRoleTrans_DESIGNATED_AGREED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_desg_a_init, stp_role_tr_desg_a_next))
				goto done;
			break;
		case STP_PortRoleTrans_DESIGNATED_SYNCED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_desg_s_init, stp_role_tr_desg_s_next))
				goto done;
			break;
		case STP_PortRoleTrans_DESIGNATED_RETIRED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_desg_retired_init,
			    stp_role_tr_desg_retired_next))
				goto done;
			break;
		case STP_PortRoleTrans_DESIGNATED_DISCARD:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_desg_discard_init,
			    stp_role_tr_desg_discard_next))
				goto done;
			break;
		case STP_PortRoleTrans_DESIGNATED_LEARN:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_desg_l_init, stp_role_tr_desg_l_next))
				goto done;
			break;
		case STP_PortRoleTrans_DESIGNATED_FORWARD:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_desg_f_init, stp_role_tr_desg_f_next))
				goto done;
			break;
		case STP_PortRoleTrans_DESIGNATED_PORT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_desg_p_init, stp_role_tr_desg_p_next))
				goto done;
			break;
		case STP_PortRoleTrans_BLOCK_PORT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_block_init, stp_role_tr_block_next))
				goto done;
			break;
		case STP_PortRoleTrans_ALTERNATE_PROPOSED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_alt_proposed_init,
			    stp_role_tr_alt_proposed_next))
				goto done;
			break;
		case STP_PortRoleTrans_ALTERNATE_AGREED:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_alt_a_init, stp_role_tr_alt_a_next))
				goto done;
			break;
		case STP_PortRoleTrans_BACKUP_PORT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_backup_init, stp_role_tr_backup_next))
				goto done;
			break;
		case STP_PortRoleTrans_ALTERNATE_PORT:
			if (stp_proc_state(p, &state_info,
			    stp_role_tr_alt_p_init, stp_role_tr_alt_p_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* PortRoleTransitions */

static void stp_discarding_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TR
	dbg_stp(p, __func__, false);
#endif
	disableLearning();
	learning = FALSE;
	disableForwarding();
	forwarding = FALSE;
}  /* stp_discarding_init */

static void stp_discarding_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(learn),
		STP_PortStateTrans_LEARNING);
}  /* stp_discarding_next */

static void stp_learning_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TR
	dbg_stp(p, __func__, false);
#endif
	enableLearning();
	learning = TRUE;
}  /* stp_learning_init */

static void stp_learning_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(!learn),
		STP_PortStateTrans_DISCARDING);
	stp_change_state(state,
		(forward),
		STP_PortStateTrans_FORWARDING);
}  /* stp_learning_next */

static void stp_forwarding_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TR
	dbg_stp(p, __func__, false);
#endif
	enableForwarding();
	forwarding = TRUE;
}  /* stp_forwarding_init */

static void stp_forwarding_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(!forward),
		STP_PortStateTrans_DISCARDING);
}  /* stp_forwarding_next */

static int PortStateTransition(struct ksz_stp_port *p)
{
	struct ksz_stp_state state_info;
	u8 *state = &p->states[p->state_index][p->MSTI];
	int ret = 0;

	state_info.index = STP_PortStateTrans;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = STP_PortStateTrans_DISCARDING;
	}
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_PortStateTrans_DISCARDING:
			if (stp_proc_state(p, &state_info,
			    stp_discarding_init, stp_discarding_next))
				goto done;
			break;
		case STP_PortStateTrans_LEARNING:
			if (stp_proc_state(p, &state_info,
			    stp_learning_init, stp_learning_next))
				goto done;
			break;
		case STP_PortStateTrans_FORWARDING:
			if (stp_proc_state(p, &state_info,
			    stp_forwarding_init, stp_forwarding_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* PortStateTransition */

static void stp_top_inactive_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	fdbFlush = TRUE;
	doFlush();

	/* Stop sending topology change. */
	tcDetected = 0;
	tcWhile = 0;
	tcPropWhile = 0;
	if (cist())
		tcAck = FALSE;
}  /* stp_top_inactive_init */

static void stp_top_inactive_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(learn && !fdbFlush),
		STP_TopologyChange_LEARNING);
}  /* stp_top_inactive_next */

static void stp_top_learn_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TOPOLOGY
	dbg_stp(p, __func__, false);
#endif
	if (cist())
		rcvdTc = rcvdTcn = rcvdTcAck = FALSE;
	rcvdTc = FALSE;
	tcProp = FALSE;
}  /* stp_top_learn_init */

static void stp_top_learn_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		(ForwardPort && forward && !operEdge),
		STP_TopologyChange_DETECTED);
	stp_change_state(state,
		(!(ForwardPort) && !(learn || learning) &&
		!(rcvdTc || rcvdTcn || rcvdTcAck || tcProp)),
		STP_TopologyChange_INACTIVE);

	/*
	 * LEARNING will be called after DETECTED because the other port is
	 * in forwarding while this port is going forwarding.
	 */
	stp_change_state(state,
		(rcvdTc || rcvdTcn || rcvdTcAck || tcProp),
		STP_TopologyChange_LEARNING);
}  /* stp_top_learn_next */

static void stp_top_det_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TOPOLOGY
	dbg_stp(p, __func__, false);
#endif
	newTcWhile();
	setTcPropTree();
	newTcDetected();
	newInfoXst(TRUE);
}  /* stp_top_det_init */

static void stp_top_det_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_TopologyChange_ACTIVE);
}  /* stp_top_det_next */

static void stp_top_ack_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	/* Stop sending topology change. */
	tcWhile = 0;
	tcPropWhile = 0;
	rcvdTcAck = FALSE;
}  /* stp_top_ack_init */

static void stp_top_ack_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_TopologyChange_ACTIVE);
}  /* stp_top_ack_next */

static void stp_top_prop_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	newTcWhile();
	fdbFlush = TRUE;
	doFlush();
	tcProp = FALSE;
}  /* stp_top_prop_init */

static void stp_top_prop_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_TopologyChange_ACTIVE);
}  /* stp_top_prop_next */

static void stp_top_tc_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TOPOLOGY
	dbg_stp(p, __func__, false);
#endif
	rcvdTc = FALSE;
	if (cist()) {
		rcvdTcn = FALSE;
		if (role == ROLE_DESIGNATED)
			tcAck = TRUE;
	}
	setTcPropTree();
}  /* stp_top_tc_init */

static void stp_top_tc_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_TopologyChange_ACTIVE);
}  /* stp_top_tc_next */

static void stp_top_tcn_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE
	dbg_stp(p, __func__, false);
#endif
	newTcWhile();
}  /* stp_top_tcn_init */

static void stp_top_tcn_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	stp_change_state(state,
		TRUE, STP_TopologyChange_NOTIFIED_TC);
}  /* stp_top_tcn_next */

static void stp_top_active_init(struct ksz_stp_port *p)
{
#ifdef DBG_STP_STATE_TOPOLOGY
	dbg_stp(p, __func__, false);
#endif
}  /* stp_top_active_init */

static void stp_top_active_next(struct ksz_stp_port *p,
	struct ksz_stp_state *state)
{
	/*
	 * rcvd* variables are reset in LEARNING, so it does have higher
	 * precedence.
	 */
	stp_change_state(state,
		(!(ForwardPort) || operEdge),
		STP_TopologyChange_LEARNING);
	stp_change_state(state,
		(rcvdTcAck),
		STP_TopologyChange_ACKNOWLEDGED);
	stp_change_state(state,
		(tcProp && !operEdge),
		STP_TopologyChange_PROPAGATING);
	stp_change_state(state,
		(rcvdTc),
		STP_TopologyChange_NOTIFIED_TC);
	stp_change_state(state,
		(rcvdTcn),
		STP_TopologyChange_NOTIFIED_TCN);
}  /* stp_top_active_next */

static int TopologyChange(struct ksz_stp_port *p)
{
	struct ksz_stp_state state_info;
	u8 *state = &p->states[p->state_index][p->MSTI];
	int ret = 0;

	state_info.index = STP_TopologyChange;
	state_info.change = 1;
	state_info.new_state = 0;
	if (STP_BEGIN == *state) {
		state_info.new_state = STP_TopologyChange_INACTIVE;
	}
	do {

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			ret = state_info.change;
			ret = 1;
		}
		switch (*state) {
		case STP_TopologyChange_INACTIVE:
			if (stp_proc_state(p, &state_info,
			    stp_top_inactive_init, stp_top_inactive_next))
				goto done;
			break;
		case STP_TopologyChange_LEARNING:
			if (stp_proc_state(p, &state_info,
			    stp_top_learn_init, stp_top_learn_next))
				goto done;
			break;
		case STP_TopologyChange_DETECTED:
			if (stp_proc_state(p, &state_info,
			    stp_top_det_init, stp_top_det_next))
				goto done;
			break;
		case STP_TopologyChange_ACKNOWLEDGED:
			if (stp_proc_state(p, &state_info,
			    stp_top_ack_init, stp_top_ack_next))
				goto done;
			break;
		case STP_TopologyChange_PROPAGATING:
			if (stp_proc_state(p, &state_info,
			    stp_top_prop_init, stp_top_prop_next))
				goto done;
			break;
		case STP_TopologyChange_NOTIFIED_TC:
			if (stp_proc_state(p, &state_info,
			    stp_top_tc_init, stp_top_tc_next))
				goto done;
			break;
		case STP_TopologyChange_NOTIFIED_TCN:
			if (stp_proc_state(p, &state_info,
			    stp_top_tcn_init, stp_top_tcn_next))
				goto done;
			break;
		case STP_TopologyChange_ACTIVE:
			if (stp_proc_state(p, &state_info,
			    stp_top_active_init, stp_top_active_next))
				goto done;
			break;
		}
	} while (state_info.new_state);

done:
	return ret;
}  /* TopologyChange */


static
int (*bridge_stms[NUM_OF_BRIDGE_STATE_MACHINES])(struct ksz_stp_bridge *) = {
	PortRoleSelection,
};

/* The bridge state machine needs to be run between the port state machines. */
#define PORT_STATE_MACHINES_CIST	4
#define PORT_STATE_MACHINES_BREAK	5
#define PORT_STATE_MACHINES_TX		8

static
int (*port_stms[NUM_OF_PORT_STATE_MACHINES])(struct ksz_stp_port *) = {
	PortTimers,
	PortReceive,
	PortProtocolMigration,
	BridgeDetection,
	PortInformation,

	PortRoleTransitions,
	PortStateTransition,
	TopologyChange,
	PortTransmit,
};


static void stp_state_machines(struct ksz_stp_bridge *br)
{
	int changed;
	int update;
	int c;
	int i;
	int m;
	uint p;
	struct ksz_stp_port *port;

	do {
		changed = update = 0;
		m = 0;
		for (p = 0; p < br->port_cnt; p++) {
			br->MSTI = m;
			port = &br->ports[p];
			if (port->off)
				continue;
			for (i = 0; i < PORT_STATE_MACHINES_CIST; i++) {
				port->state_index = i;
				port->MSTI = m;
				changed = port_stms[i](port);
				update |= (changed << (1 + i));
			}
		}
		for (p = 0; p < br->port_cnt; p++) {
			port = &br->ports[p];
			if (port->off)
				continue;
			for (i = PORT_STATE_MACHINES_CIST;
			     i < PORT_STATE_MACHINES_BREAK; i++) {
				port->state_index = i;
				for (c = 0, m = 0; c < br->MSTI_cnt; c++, m++) {
					m = next_msti(br, m);
					br->MSTI = m;
					port->MSTI = m;
					changed = port_stms[i](port);
					update |= (changed << (1 + i));
				}
			}
#ifdef DEBUG_MSG
	dbg_print_work(&db.dbg_print);
#endif
		}
		for (i = 0; i < NUM_OF_BRIDGE_STATE_MACHINES; i++) {
			br->state_index = i;
			for (c = 0, m = 0; c < br->MSTI_cnt; c++, m++) {
				m = next_msti(br, m);
				br->MSTI = m;
				for (p = 0; p < br->port_cnt; p++) {
					port = &br->ports[p];
					port->MSTI = m;
				}
				changed = bridge_stms[i](br);
				update |= (changed << 0);
			}
		}
		for (p = 0; p < br->port_cnt; p++) {
			port = &br->ports[p];
			if (port->off)
				continue;
			for (i = PORT_STATE_MACHINES_BREAK;
			     i < PORT_STATE_MACHINES_TX; i++) {
				port->state_index = i;
				for (c = 0, m = 0; c < br->MSTI_cnt; c++, m++) {
					m = next_msti(br, m);
					br->MSTI = m;
					port->MSTI = m;
					changed = port_stms[i](port);
					update |= (changed << (1 + i));
				}
#ifdef DEBUG_MSG
	dbg_print_work(&db.dbg_print);
#endif
			}
		}

		/*
		 * Cannot send if all received BPDU are not processed in case
		 * they are looped back to the bridge.
		 */
		if (br->skip_tx)
			break;
		m = 0;
		for (p = 0; p < br->port_cnt; p++) {
			br->MSTI = m;
			port = &br->ports[p];
			if (port->off)
				continue;
			for (i = PORT_STATE_MACHINES_TX;
			     i < NUM_OF_PORT_STATE_MACHINES; i++) {
				port->state_index = i;
				port->MSTI = m;
				changed = port_stms[i](port);
				update |= (changed << (1 + i));
			}
		}
#ifdef DEBUG_MSG
	dbg_print_work(&db.dbg_print);
#endif
	} while (update);
}  /* stp_state_machines */

static void proc_state_machines(struct work_struct *work)
{
	struct ksz_stp_info *stp =
		container_of(work, struct ksz_stp_info, state_machine);

	stp->machine_running = true;
	mutex_lock(&stp->br.lock);
	stp_state_machines(&stp->br);
	mutex_unlock(&stp->br.lock);
	stp->machine_running = false;
	if (stp->br.skip_tx)
		schedule_work(&stp->rx_proc);
}  /* proc_state_machines */

static void invoke_state_machines(struct ksz_stp_bridge *br)
{
	struct ksz_stp_info *stp = br->parent;

	if (br->bridgeEnabled && stp->timer_tick)
		schedule_work(&stp->state_machine);
}  /* invoke_state_machines */

static void stp_br_msti_init(struct ksz_stp_port *p)
{
	BridgeIdentifier.prio = htons(0x8000 + p->br->MSTI);
	BridgePriority.prio.bridge_id.prio = BridgeIdentifier.prio;
	if (!p->br->MSTI)
		BridgePriority.prio.root.prio = BridgeIdentifier.prio;

	BridgeMaxHops = 20;
	BridgeHelloTime = 2;
	BridgeMaxAge = 20;
	BridgeFwdDelay = 15;
}

static void stp_br_init(struct ksz_stp_port *p)
{
	struct ksz_stp_bridge *br = p->br;

	/* MigrateTime is only used internally. */
	MigrateTime = to_stp_timer(3);
	TxHoldCount = 6;
	ForceProtocolVersion = 3;
#if 0
	ForceProtocolVersion = 2;
#endif
#if 0
	ForceProtocolVersion = 0;
#endif

	for (br->MSTI = 0; br->MSTI < NUM_OF_MSTI; br->MSTI++)
		stp_br_msti_init(p);
	br->MSTI = 0;
	br->MSTI_enabled = 1;
	br->MSTI_cnt = 1;
#if 0
	if (ForceProtocolVersion >= 3) {
		br->MSTI_enabled |= (1 << 1);
		br->MSTI_cnt++;
#if 0
		br->MSTI_enabled |= (1 << 7);
		br->MSTI_cnt++;
#endif
	}
#endif
	MstConfigId.name[0] = 'K';
	MstConfigId.name[1] = 'S';
	MstConfigId.name[2] = 'Z';
	recalc_cfg_digest(p);

	p->br->hack_4_1 = 0;
	p->br->hack_4_2 = 0;
	p->br->hack_5_2 = 0;
}  /* stp_br_init */

static void stp_port_msti_init(struct ksz_stp_port *p)
{
	portId.prio = 0x80;
}  /* stp_port_msti_init */

static void stp_port_init(struct ksz_stp_port *p)
{
	adminPointToPointMAC = ADMIN_P2P_AUTO;
	AdminPortPathCost = 0;
	AdminEdge = FALSE;
	AutoEdge = FALSE;
#if 1
	AutoEdge = TRUE;
#endif
#if 0
	AutoIsolate = TRUE;
#endif
	enableBPDUrx = enableBPDUtx = TRUE;
}  /* stp_port_init */

static void stp_state_init(struct ksz_stp_bridge *br)
{
	int i;
	int m;
	uint port;
	struct ksz_stp_port *p;
	struct ksz_stp_info *stp = br->parent;

	stp->timer_tick = 1000;
	for (i = 0; i < NUM_OF_BRIDGE_STATE_MACHINES; i++) {
		br->state_index = i;
		for (m = 0; m < NUM_OF_MSTI; m++)
			br->states[br->state_index][m] = STP_BEGIN;
	}
	for (port = 0; port < br->port_cnt; port++) {
		p = &br->ports[port];
		for (i = 0; i < NUM_OF_PORT_STATE_MACHINES; i++) {
			p->state_index = i;
			for (m = 0; m < NUM_OF_MSTI; m++)
				p->states[p->state_index][m] = STP_BEGIN;
		}

		memset(p->vars.timers, 0, sizeof(p->vars.timers));
		for (m = 0; m < NUM_OF_MSTI; m++) {
			memset(p->mvars[m].timers, 0,
				sizeof(p->mvars[m].timers));
			p->MSTI = m;
			selected = FALSE;
		}
	}
	invoke_state_machines(br);
}  /* stp_state_init */

static int stp_cfg_port(struct ksz_stp_port *p, int link, int speed,
	int duplex)
{
	int change = 0;

	if (link) {
		if (!portEnabled) {
			struct ksz_stp_dbg_times *x = &p->dbg_times[p->MSTI];

			portEnabled = TRUE;
if (x->block_jiffies) {
dbg_msg("%s %d %lu\n", __func__, p->port_index, jiffies - x->block_jiffies);
x->block_jiffies = jiffies;
}
			change = 1;
		}
		if (p->speed != speed) {
			p->speed = speed;
			p->MSTI = 0;
			if (checkPathCost(p))
				change = 1;
		}
		if (p->duplex != duplex) {
			p->duplex = duplex;
			if (checkP2P(p))
				change = 1;
		}
	} else {
		if (portEnabled) {
			portEnabled = FALSE;
			change = 1;
		}
	}
	return change;
}  /* stp_cfg_port */

static void stp_disable_port(struct ksz_stp_info *stp, uint port)
{
	struct ksz_stp_bridge *br = &stp->br;
	struct ksz_stp_port *p = &br->ports[port];

	portEnabled = FALSE;
	p->link = 0;
}  /* stp_disable_port */

static void stp_enable_port(struct ksz_stp_info *stp, uint port, u8 *state)
{
	struct ksz_stp_bridge *br = &stp->br;
	struct ksz_stp_port *p = &br->ports[port];

	if (br->bridgeEnabled && !p->off)
		*state = STP_STATE_DISABLED;
}  /* stp_enable_port */

#ifdef DBG_STP_RX
static int AllDesignatedPort(struct ksz_stp_port *p)
{
	int ret = true;

	p->MSTI = 0;
	FOREACH_T_IN_P(
		if (!DesignatedPort) {
			ret = false;
			break;
		}
	)
	return ret;
}
#endif

static void stp_proc_rx(struct ksz_stp_port *p, struct bpdu *bpdu, u16 len)
{
	u16 size;
#ifdef DBG_STP_RX
	int cmp;
	int bpdu_len = len;

	if (bpdu_len > sizeof(struct bpdu_v3))
		bpdu_len = sizeof(struct bpdu_v3);
	if (AllDesignatedPort(p)) {
	cmp = memcmp(&p->rx_bpdu0, bpdu, bpdu_len);
	if (cmp || ((bpdu->flags & (PORT_ROLE_DESIGNATED << PORT_ROLE_S)) !=
	    (PORT_ROLE_DESIGNATED << PORT_ROLE_S) &&
	    BPDU_TYPE_CONFIG_RSTP == bpdu->type)) {
		if (p->dbg_rx < 2)
			p->dbg_rx = 2;
	}
	}
	if (p->dbg_rx)
		p->dbg_rx--;
	if (p->dbg_rx && (bpdu->version <= 2 ||
	    (bpdu->version >= 3 && len >= sizeof(struct bpdu)))) {
dbg_msg("[R] %d: ", p->port_index);
		disp_bpdu(bpdu);
	}
	memcpy(&p->rx_bpdu0, bpdu, bpdu_len);
#endif

	/* Reject bad BPDU. */
	if (bpdu->protocol != 0)
		return;
	size = sizeof(struct bpdu_v1);
	if (BPDU_TYPE_CONFIG == bpdu->type)
		size--;
	else if (BPDU_TYPE_TCN == bpdu->type)
		size = 7;
	else if (BPDU_TYPE_CONFIG_RSTP != bpdu->type)
		size = 10000;
	if (len < size)
		return;
	if (3 == bpdu->version) {
		size = len - sizeof(struct bpdu) + sizeof(struct mstp_bpdu);
		size -= 2;

		/* Decode as RST BPDU. */
		if (bpdu->version_1_length ||
		    size != ntohs(bpdu->mstp.version_3_length))
			bpdu->version = 2;
	}
	p->MSTI = 0;
	bpduVersion = bpdu->version <= 3 ? bpdu->version : 3;
	bpduType = bpdu->type;
	bpduFlags = 0;
	bpduRole = (bpdu->flags >> PORT_ROLE_S) & PORT_ROLE_DESIGNATED;
	if (BPDU_TYPE_CONFIG_RSTP == bpdu->type)
		bpduFlags = bpdu->flags;
	else if (BPDU_TYPE_TCN != bpdu->type)
		bpduFlags = bpdu->flags &
			(TOPOLOGY_CHANGE_ACK | TOPOLOGY_CHANGE);
	if (BPDU_TYPE_TCN != bpdu->type) {
		copy_prio(&bpduPriority, &bpdu->root);
		bpduTimes.message_age = get_bpdu_time(bpdu->message_age);
		bpduTimes.max_age = get_bpdu_time(bpdu->max_age);
		bpduTimes.hello_time = get_bpdu_time(bpdu->hello_time);
		bpduTimes.forward_delay = get_bpdu_time(bpdu->forward_delay);
		bpduTimes.max_hops = BridgeMaxHops;
		if ((BPDU_TYPE_CONFIG == bpdu->type &&
		    bpduTimes.message_age >= bpduTimes.max_age) ||
		    bpduTimes.message_age > bpduTimes.max_age)
			return;
		if (3 <= bpdu->version && ForceProtocolVersion >= 3) {
			struct msti_cfg *cfg;
			struct _port_id port_id = bpduPriority.port_id;
			struct mstp_times times;
			struct mstp_bpdu *mstp = &bpdu->mstp;
			int len = ntohs(mstp->version_3_length);

			COPY(times, bpduTimes);
			memcpy(&bpduMCID, &mstp->MCID,
				sizeof(struct mst_cfg_id));
			memcpy(&bpduPriority.bridge_id, &mstp->id,
				sizeof(struct _bridge_id));
			bpduPriority.internal_root_path_cost =
				mstp->internal_root_path_cost;
			bpduTimes.max_hops = mstp->max_hops;

			/*
			 * Initialize bpudFlags in case MSTI is not reported so
			 * that rcvdMsg will not be set.
			 */
			FOREACH_M_IN_P(
				bpduFlags = 0;
			)
			len += 2;
			len -= sizeof(struct mstp_bpdu);
			cfg = (struct msti_cfg *)(mstp + 1);
			while (len >= sizeof(struct msti_cfg)) {
				p->MSTI = ntohs(cfg->root.prio) & 0x0fff;
				if (!(p->br->MSTI_enabled & (1 << p->MSTI)))
					goto next;
				bpduFlags = cfg->flags;
				bpduRole = (cfg->flags >> PORT_ROLE_S) &
					PORT_ROLE_DESIGNATED;
				memcpy(&bpduPriority.regional_root,
					&cfg->root, sizeof(struct _bridge_id));
				bpduPriority.internal_root_path_cost =
					cfg->root_path_cost;
				memcpy(&bpduPriority.bridge_id, &mstp->id,
					sizeof(struct _bridge_id));
				bpduPriority.bridge_id.prio =
					htons((cfg->br_prio << 8) | p->MSTI);
				bpduPriority.port_id = port_id;
				bpduPriority.port_id.prio = cfg->port_prio;
				COPY(bpduTimes, times);
				bpduTimes.max_hops = cfg->max_hops;

next:
				cfg++;
				len -= sizeof(struct msti_cfg);
			}
			p->MSTI = 0;
		} else {
			bpduPriority.internal_root_path_cost = 0;
			memcpy(&bpduPriority.bridge_id,
				&bpduPriority.regional_root,
				sizeof(struct _bridge_id));
		}
	} else {
		ZERO(bpduPriority);
		ZERO(bpduTimes);
	}
	rcvdBPDU = TRUE;
}  /* stp_proc_rx */

static void stp_proc_tick(struct ksz_stp_bridge *br)
{
	uint i;
	struct ksz_stp_port *p;

	for (i = 0; i < br->port_cnt; i++) {
		p = &br->ports[i];
		tick = TRUE;
if (p->dbg_rx)
	p->dbg_rx--;
	}
	invoke_state_machines(br);
}  /* stp_proc_tick */

static void proc_rx(struct work_struct *work)
{
	struct ksz_stp_info *stp =
		container_of(work, struct ksz_stp_info, rx_proc);
	struct ksz_stp_bridge *br = &stp->br;
	struct ksz_stp_port *p;
	uint i;
	bool not_empty;
	bool last;
	struct sk_buff *skb;

	if (mutex_is_locked(&stp->br.lock)) {
		schedule_work(&stp->rx_proc);
		return;
	}
	not_empty = false;
	for (i = 0; i < br->port_cnt; i++) {
		p = &br->ports[i];
		if (rcvdBPDU)
			continue;
		last = skb_queue_empty(&p->rxq);
		not_empty |= !last;
		if (!last) {
			skb = skb_dequeue(&p->rxq);
			last = skb_queue_empty(&p->rxq);
			if (skb) {
				uint port;
				struct bpdu *bpdu;
				u16 len = 0;

				port = skb->cb[0];
				bpdu = chk_bpdu(skb->data, &len);
				if (bpdu)
					stp_proc_rx(p, bpdu, len);
				dev_kfree_skb_irq(skb);
			}
		} else
			br->port_rx &= ~(1 << p->port_index);
	}
	if (not_empty || br->port_rx) {
		br->skip_tx = true;
		invoke_state_machines(br);
	} else if (!br->port_rx && br->skip_tx) {
		br->skip_tx = false;
		invoke_state_machines(br);
	}
}  /* proc_rx */

static int stp_rcv(struct ksz_stp_info *stp, struct sk_buff *skb, uint port)
{
	struct bpdu *bpdu;
	u16 len = 0;

	bpdu = chk_bpdu(skb->data, &len);
	if (bpdu) {
		struct ksz_stp_bridge *br = &stp->br;
		struct ksz_stp_port *p = &br->ports[port];

		if (stp->machine_running || rcvdBPDU || br->port_rx) {

			/* Use control buffer to save port information. */
			skb->cb[0] = (char) port;
			skb_queue_tail(&p->rxq, skb);
			br->port_rx |= (1 << port);
			schedule_work(&stp->rx_proc);
		} else {
			stp_proc_rx(p, bpdu, len);
			dev_kfree_skb_irq(skb);

			invoke_state_machines(br);
		}
		return 0;
	}
	return 1;
}  /* stp_rcv */

static void port_timer_monitor(unsigned long ptr)
{
	struct ksz_stp_info *stp = (struct ksz_stp_info *) ptr;

	stp_proc_tick(&stp->br);

	ksz_update_timer(&stp->port_timer_info);
}  /* port_timer_monitor */

static void reselectAll(struct ksz_stp_bridge *br)
{
	struct ksz_stp_port *p = &br->ports[0];

	FOREACH_P_IN_T(
		FOREACH_T_IN_P(
			reselect = TRUE;
			selected = FALSE;
		)
		p->rx_bpdu0.protocol = 0xff;
		p->tx_bpdu0.protocol = 0xff;
	)
}

static const u8 *stp_br_id(struct ksz_stp_info *stp)
{
	return (u8 *) &stp->br.mvars[0].br_id_;
}

static int stp_change_addr(struct ksz_stp_info *stp, u8 *addr)
{
	int diff;
	struct ksz_stp_bridge *br = &stp->br;
	struct ksz_stp_port *p = &br->ports[0];

	mutex_lock(&br->lock);
	br->MSTI = 0;
	diff = memcmp(BridgeIdentifier.addr, addr, ETH_ALEN);
	for (br->MSTI = 0; br->MSTI < NUM_OF_MSTI; br->MSTI++) {
		memcpy(BridgeIdentifier.addr, addr, ETH_ALEN);

		if (!br->MSTI)
			COPY(BridgePriority.prio.root, BridgeIdentifier);
		COPY(BridgePriority.prio.regional_root, BridgeIdentifier);
		COPY(BridgePriority.prio.bridge_id, BridgeIdentifier);
	}
	br->MSTI = 0;
	mutex_unlock(&br->lock);

	memcpy(&stp->tx_frame[6], addr, ETH_ALEN);
	if (diff) {
		reselectAll(br);
		invoke_state_machines(br);
	}
	return diff;
}  /* stp_change_addr */

static void stp_set_addr(struct ksz_stp_info *stp, u8 *addr)
{
	struct ksz_stp_bridge *br = &stp->br;
	struct ksz_stp_port *p = &br->ports[0];

	memcpy(BridgeIdentifier.addr, addr, ETH_ALEN);
}  /* stp_set_addr */

static void stp_link_change(struct ksz_stp_info *stp, int update)
{
	uint i;
	int m;
	int duplex;
	int speed;
	u8 state;
	int change = 0;
	struct ksz_port_info *info;
	struct ksz_stp_port *p;
	struct ksz_sw *sw = stp->sw_dev;
	struct ksz_stp_bridge *br = &stp->br;

	if (!br->bridgeEnabled)
		return;
	mutex_lock(&br->lock);
	for (i = 0; i < br->port_cnt; i++) {
		if (!(sw->dev_ports & (1 << i)))
			continue;
		p = &br->ports[i];
		if (p->off)
			continue;
		info = get_port_info(sw, i);
		if (p->link != (media_connected == info->state)) {
			p->link = (media_connected == info->state);
			if (p->link)
				state = STP_STATE_BLOCKED;
			else
				state = STP_STATE_DISABLED;
#ifdef CONFIG_KSZ_MRP
			if (!p->link && (sw->features & MRP_SUPPORT)) {
				struct mrp_info *mrp = &sw->mrp;

				mrp_close_port(mrp, i);
			}
#endif
			sw->ops->acquire(sw);
			for (m = 0; m < NUM_OF_MSTI; m++) {
				port_cfg_mstp(sw, i, m);
				port_set_stp_state(sw, i, state);
			}
			sw->ops->release(sw);
			duplex = (2 == info->duplex);
			speed = info->tx_rate / TX_RATE_UNIT;
			change |= stp_cfg_port(p, p->link, speed, duplex);
		}
	}
	mutex_unlock(&br->lock);
	if (change && update)
		invoke_state_machines(br);
}  /* stp_link_change */

static int stp_get_tcDetected(struct ksz_stp_info *stp, int i)
{
	struct ksz_stp_port *p;
	struct ksz_stp_bridge *br = &stp->br;

	p = &br->ports[i];
	return tcDetected != 0;
}  /* stp_get_tcDetected */

static void stp_start(struct ksz_stp_info *stp)
{
	uint i;
	uint n;
	struct ksz_stp_port *p;
	struct ksz_sw *sw = stp->sw_dev;
	struct ksz_stp_bridge *br = &stp->br;

	stp->dev = sw->main_dev;
	sw->ops->acquire(sw);
	for (n = 1; n <= sw->mib_port_cnt; n++) {
		i = get_phy_port(sw, n);
		p = &br->ports[i];
		if (p->off)
			continue;
		FOREACH_T_IN_P(
			port_cfg_mstp(sw, i, p->MSTI);
			port_set_stp_state(sw, i, STP_STATE_DISABLED);
		)
	}
	sw->ops->release(sw);
	do {
		struct ksz_vlan_table entry;
		int x;
		int y;

		memset(&entry, 0, sizeof(struct ksz_vlan_table));
		for (i = 2; i <= NUM_OF_VID; i++) {
			x = i / VID_IN_DATA;
			y = (VID_IN_DATA - 1) - (i % VID_IN_DATA);
			if (!(sw->info->vid[x] & (1 << y)))
				continue;
			x = sw->info->vid2fid[i];
			entry.fid = (u8) x;
			entry.untag = 0;
			entry.ports = sw->PORT_MASK;
			entry.mstp = sw->info->fid2mstid[x];
			entry.valid = 1;
			sw_w_vlan_table(sw, i, &entry);
		}
	} while (0);
	stp->timer_tick = 1000;
	ksz_start_timer(&stp->port_timer_info, stp->port_timer_info.period);
	stp_link_change(stp, false);
	if (!stp_change_addr(stp, sw->info->mac_addr))
		stp_state_init(&stp->br);
}  /* stp_start */

static void stp_stop(struct ksz_stp_info *stp, int hw_access)
{
	uint i;
	uint n;
	struct ksz_stp_port *p;
	struct ksz_sw *sw = stp->sw_dev;
	struct ksz_stp_bridge *br = &stp->br;

	if (hw_access) {
		sw->ops->acquire(sw);
		for (n = 1; n <= sw->mib_port_cnt; n++) {
			i = get_phy_port(sw, n);
			p = &br->ports[i];
			if (p->off)
				continue;
			FOREACH_T_IN_P(
				port_cfg_mstp(sw, i, p->MSTI);
				port_set_stp_state(sw, i, STP_STATE_FORWARDING);
			)
		}
		sw->ops->release(sw);
	}
	ksz_stop_timer(&stp->port_timer_info);
	stp->timer_tick = 0;
	flush_work(&stp->rx_proc);
	flush_work(&stp->state_machine);

	p = &br->ports[0];
	stp_br_init(p);
	for (i = 0; i < br->port_cnt; i++) {
		p = &br->ports[i];
		stp_port_init(p);
		FOREACH_T_IN_P(
			stp_port_msti_init(p);
		)
	}
}  /* stp_stop */

static void stp_br_test_setup(struct ksz_stp_bridge *br)
{
	uint i;
	struct ksz_stp_port *p;

	p = &br->ports[0];
	stp_br_init(p);
	for (i = 0; i < br->port_cnt; i++) {
		p = &br->ports[i];
		stp_port_init(p);

		/* Switch back to RSTP if port is in STP. */
		mcheck = TRUE;
		AdminPortPathCost = 200000;
		checkPathCost(p);
		checkP2P(p);
		p->rx_bpdu0.protocol = 0xff;
		FOREACH_T_IN_P(
			stp_port_msti_init(p);
		)
	}
}  /* stp_br_test_setup */

#define BR_ID_FMT  "%04x.%02x%02x%02x%02x%02x%02x"

#define BR_ID_ARGS(x)  \
	ntohs(x.prio), x.addr[0], x.addr[1], x.addr[2], \
	x.addr[3], x.addr[4], x.addr[5]

#define BOOL_STR(x)  ((x) ? "yes" : "no")

static char *get_admin_p2p_str(int p2p)
{
	switch (p2p) {
	case ADMIN_P2P_FORCE_FALSE:
		return "no";
	case ADMIN_P2P_FORCE_TRUE:
		return "yes";
	case ADMIN_P2P_AUTO:
		return "auto";
	}
	return "unk";
}

static char *get_port_state_str(int state)
{
	switch (state) {
	case STP_PortStateTrans_DISCARDING:
		return "discarding";
	case STP_PortStateTrans_LEARNING:
		return "learning";
	case STP_PortStateTrans_FORWARDING:
		return "forwarding";
	}
	return "unknown";
}

static char *get_port_role_str(int _role)
{
	switch (_role) {
	case ROLE_ROOT:
		return "root";
	case ROLE_DESIGNATED:
		return "designated";
	case ROLE_ALTERNATE:
		return "alternate";
	case ROLE_BACKUP:
		return "backup";
	case ROLE_DISABLED:
		return "disabled";
	case ROLE_MASTER:
		return "master";
	}
	return "unknown";
}

static ssize_t sysfs_stp_read(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	struct ksz_stp_info *stp = &sw->info->rstp;
	struct ksz_stp_port *p;
	struct _bridge_id root;
	char name[36];
	uint path_cost;
	int enabled;
	int i;
	int chk = 0;
	int type = SHOW_HELP_NUM;
	char note[40];

	note[0] = '\0';
	if (!(sw->features & STP_SUPPORT))
		return 0;
	mutex_lock(&stp->br.lock);
	p = &stp->br.ports[0];
	p->MSTI = p->br->MSTI = p->br->MSTI_index;
	switch (proc_num) {
	case PROC_GET_STP_BR_INFO:
		enabled = stp->br.bridgeEnabled;
		if (enabled && !(stp->br.MSTI_enabled & (1 << p->MSTI)))
			enabled = false;
		len += sprintf(buf + len,
			" enabled\t\t%4s\n",
			BOOL_STR(enabled));
		len += sprintf(buf + len,
			" bridge id\t\t" BR_ID_FMT "\n",
			BR_ID_ARGS(BridgeIdentifier));
		if (p->MSTI) {
			COPY(root, rootPriority.regional_root);
			path_cost = rootPriority.internal_root_path_cost;
		} else {
			COPY(root, rootPriority.root);
			path_cost = rootPriority.root_path_cost;
		}
		len += sprintf(buf + len,
			" designated root\t" BR_ID_FMT "",
			BR_ID_ARGS(root));
		len += sprintf(buf + len,
			"\tpath cost\t%12u\n",
			ntohl(path_cost));
		if (ForceProtocolVersion >= 3 && !p->MSTI) {
			COPY(root, rootPriority.regional_root);
			path_cost = rootPriority.internal_root_path_cost;
			len += sprintf(buf + len,
				" regional root\t\t" BR_ID_FMT "",
				BR_ID_ARGS(root));
			len += sprintf(buf + len,
				"\tpath cost\t%12u\n",
				ntohl(path_cost));
		}
		len += sprintf(buf + len,
			" root port\t\t%4u\n",
			rootPortId.num);
		if (!p->MSTI) {
			len += sprintf(buf + len,
				" max age\t\t%4u",
				rootTimes.max_age);
			len += sprintf(buf + len,
				"\t\t\tbridge max age\t\t%4u\n",
				BridgeMaxAge);
			len += sprintf(buf + len,
				" hello time\t\t%4u",
				rootTimes.hello_time);
			len += sprintf(buf + len,
				"\t\t\tbridge hello time\t%4u\n",
				BridgeHelloTime);
			len += sprintf(buf + len,
				" forward delay\t\t%4u",
				rootTimes.forward_delay);
			len += sprintf(buf + len,
				"\t\t\tbridge forward delay\t%4u\n",
				BridgeFwdDelay);
			len += sprintf(buf + len,
				" tx hold count\t\t%4u",
				TxHoldCount);
			len += sprintf(buf + len,
				"\t\t\tprotocol version\t%4u\n",
				ForceProtocolVersion);
		}
		if (ForceProtocolVersion >= 3) {
			len += sprintf(buf + len,
				" maximum hops\t\t%4u",
				rootTimes.max_hops);
			len += sprintf(buf + len,
				"\t\t\tbridge maximum hops\t%4u\n",
				BridgeMaxHops);
		}
		len += sprintf(buf + len,
			" time since topology change\t%9u\n",
			timeSinceTC);
		len += sprintf(buf + len,
			" topology change count\t\t%9u\n",
			cntTC);
		len += sprintf(buf + len,
			" topology change\t\t%9s\n",
			BOOL_STR(isTC));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_STP_BR_ON:
		chk = p->br->bridgeEnabled;
		type = SHOW_HELP_ON_OFF;
#if defined(DBG_STP_STATE) || defined(DBG)
		d_stp_states(p->br);
#endif
		break;
	case PROC_SET_STP_BR_PRIO:
		chk = ntohs(BridgeIdentifier.prio);
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_STP_BR_FWD_DELAY:
		chk = BridgeFwdDelay;
		break;
	case PROC_SET_STP_BR_MAX_AGE:
		chk = BridgeMaxAge;
		break;
	case PROC_SET_STP_BR_HELLO_TIME:
		chk = BridgeHelloTime;
		break;
	case PROC_SET_STP_BR_TX_HOLD:
		chk = TxHoldCount;
		break;
	case PROC_SET_STP_VERSION:
		chk = ForceProtocolVersion;
		if (sw->verbose) {
			switch (chk) {
			case 3:
				strcpy(note, " (mstp)");
				break;
			case 2:
				strcpy(note, " (rstp)");
				break;
			case 0:
				strcpy(note, " (stp)");
				break;
			default:
				strcpy(note, " (unknown)");
			}
		}
		break;
	case PROC_SET_STP_BR_MAX_HOPS:
		chk = BridgeMaxHops;
		break;
	case PROC_SET_STP_MSTI:
		chk = p->br->MSTI_index;
		break;
	case PROC_SET_STP_MSTI_VID:
		chk = p->br->MSTI_index;
		enabled = 0;
		for (i = 0; i < VLAN_TABLE_ENTRIES; i++) {
			if ((i % (32 * 8)) == 0)
				len += sprintf(buf + len,
					"%03x: ", i);
			enabled <<= 1;
			if (chk == sw->info->fid2mstid[sw->info->vid2fid[i]])
				enabled |= 1;
			if ((i % 32) == 31) {
				enabled &= sw->info->vid[i / VID_IN_DATA];
				len += sprintf(buf + len,
					"%08x ", enabled);
				enabled = 0;
			}
			if ((i % (32 * 8)) == (32 * 8 - 1))
				len += sprintf(buf + len,
					"\n");
		}
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_STP_MSTP_CFG:
		len += sprintf(buf + len,
			"%02x  %04x\n", MstConfigId.selector,
			htons(MstConfigId.revision));
		strncpy(name, MstConfigId.name, 32);
		name[32] = '\0';
		len += sprintf(buf + len,
			"%s\n", name);
		for (i = 0; i < 16; i++)
			len += sprintf(buf + len,
				"%02X", MstConfigId.digest[i]);
		len += sprintf(buf + len, "\n");
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_STP_MSTP_NAME:
		strncpy(name, MstConfigId.name, 32);
		name[32] = '\0';
		len += sprintf(buf + len,
			"%s\n", name);
		type = SHOW_HELP_NONE;
		break;
	default:
		type = SHOW_HELP_NONE;
	}
	p->MSTI = p->br->MSTI = 0;
	mutex_unlock(&stp->br.lock);
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_stp_read */

static int sysfs_stp_write(struct ksz_sw *sw, int proc_num, int num,
	const char *buf)
{
	struct ksz_stp_info *stp = &sw->info->rstp;
	struct ksz_stp_bridge *br = &stp->br;
	struct ksz_stp_port *p;
	char name[36];
	uint i;
	int set;
	int change = 0;
	int processed = true;

	if (!(sw->features & STP_SUPPORT))
		return false;
	mutex_lock(&stp->br.lock);
	p = &br->ports[0];
	p->MSTI = p->br->MSTI = p->br->MSTI_index;
	switch (proc_num) {
	case PROC_SET_STP_BR_ON:
		set = !!num;
		if (set != br->bridgeEnabled) {
			br->bridgeEnabled = set;
			if (br->bridgeEnabled) {
				mutex_unlock(&stp->br.lock);
				stp_start(stp);
				mutex_lock(&stp->br.lock);
			} else
				stp_stop(stp, true);
		}
		break;
	case PROC_SET_STP_BR_PRIO:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		if ((0 <= num && num <= 0xf000) && !(num & ~0xf000)) {
			u16 prio = ntohs(BridgeIdentifier.prio);

			if (num != prio) {
				prio = num | p->br->MSTI;
				BridgeIdentifier.prio = htons(prio);
				BridgePriority.prio.regional_root.prio =
				BridgePriority.prio.bridge_id.prio =
					BridgeIdentifier.prio;
				if (!p->br->MSTI)
					BridgePriority.prio.root.prio =
						BridgeIdentifier.prio;
				change = 1;
			}
		}
		break;
	case PROC_SET_STP_BR_FWD_DELAY:
		if (checkParameters(BridgeHelloTime, BridgeMaxAge, num)) {
			if (num != BridgeFwdDelay) {
				BridgeFwdDelay = num;
				change = 1;
			}
		}
		break;
	case PROC_SET_STP_BR_MAX_AGE:
		if (checkParameters(BridgeHelloTime, num, BridgeFwdDelay)) {
			if (num != BridgeMaxAge) {
				BridgeMaxAge = num;
				change = 1;
			}
		}
		break;
	case PROC_SET_STP_BR_HELLO_TIME:
		if (num == 2) {
			if (num != BridgeHelloTime) {
				BridgeHelloTime = num;
				change = 1;
			}
		}
		break;
	case PROC_SET_STP_BR_TX_HOLD:
		if (1 <= num && num <= 10) {
			if (num != TxHoldCount) {
				TxHoldCount = num;
				for (i = 0; i < br->port_cnt; i++) {
					p = &br->ports[i];
					txCount = 0;
				}
				change = 1;
			}
		}
		break;
	case PROC_SET_STP_VERSION:
		if (0 == num || 2 == num) {
			ForceProtocolVersion = num;
			change = 2;
		}
		if (1 == num) {
			stp_br_test_setup(br);
			change = 1;
		}
		if (41 == num)
			br->hack_4_1 = 1;
		if (42 == num)
			br->hack_4_2 = 1;
		if (52 == num)
			br->hack_5_2 = 1;
		break;
	case PROC_SET_STP_BR_MAX_HOPS:
		if (10 <= num && num <= 20) {
			if (num != BridgeMaxHops) {
				BridgeMaxHops = num;
				change = 1;
			}
		}
		break;
	case PROC_SET_STP_MSTI:
		if (0 <= num && num < NUM_OF_MSTI &&
		    ForceProtocolVersion >= 3) {
			p->br->MSTI_index = num;
			sw->ops->acquire(sw);
			for (i = 0; i < br->port_cnt; i++) {
				p = &br->ports[i];
				if (p->off)
					continue;
				port_cfg_mstp(sw, i, num);
			}
			sw->ops->release(sw);
		}
		break;
	case PROC_SET_STP_MSTP_NAME:
		strncpy(name, buf, 32);
		name[32] = '\0';
		i = strlen(name);
		if ('\n' == name[i - 1])
			name[i - 1] = '\0';
		if (strncmp(name, MstConfigId.name, 32)) {
			strncpy(MstConfigId.name, name, 32);
			change = 2;
		}
		if (sw->info->fid_updated) {
			sw->info->fid_updated = 0;
			recalc_cfg_digest(p);
			change = 2;
		}
		break;
	default:
		processed = false;
		break;
	}
	p->MSTI = p->br->MSTI = 0;
	mutex_unlock(&stp->br.lock);
	if (change && br->bridgeEnabled) {
		reselectAll(br);
		if (2 == change)
			stp_state_init(br);
		else
			invoke_state_machines(br);
	}
	return processed;
}  /* sysfs_stp_write */

static ssize_t sysfs_stp_port_read(struct ksz_sw *sw, int proc_num, uint port,
	ssize_t len, char *buf)
{
	struct ksz_stp_info *stp = &sw->info->rstp;
	struct ksz_stp_port *p;
	struct _bridge_id root;
	uint cost;
	uint path_cost;
	char *state_str;
	int enabled;
	int chk = 0;
	int type = SHOW_HELP_NONE;
	char note[40];

	note[0] = '\0';
	if (!(sw->features & STP_SUPPORT))
		return 0;
	port = get_sysfs_port(sw, port);
	if (port == sw->HOST_PORT)
		return 0;
	mutex_lock(&stp->br.lock);
	p = &stp->br.ports[port];
	p->MSTI = p->br->MSTI = p->br->MSTI_index;
	switch (proc_num) {
	case PROC_GET_STP_INFO:
		if (p->off)
			break;
		enabled = portEnabled;
		if (enabled && !(stp->br.MSTI_enabled & (1 << p->MSTI)))
			enabled = false;
		state_str = get_port_role_str(role);
		len += sprintf(buf + len,
			" enabled\t\t%4s",
			BOOL_STR(enabled));
		len += sprintf(buf + len,
			"\t\t\trole\t\t%12s\n",
			state_str);
		state_str = get_port_state_str(p->states[6][p->MSTI]);
		len += sprintf(buf + len,
			" port id\t\t%02x%02x\t\t\tstate\t\t%12s\n",
		       portId.prio, portId.num, state_str);
		if (p->MSTI) {
			path_cost = ExternalPortPathCost;
			COPY(root, designatedPriority.regional_root);
			cost = designatedPriority.internal_root_path_cost;
		} else {
			path_cost = InternalPortPathCost;
			COPY(root, designatedPriority.root);
			cost = designatedPriority.root_path_cost;
		}
		len += sprintf(buf + len,
			" path cost\t%12u\t\t\tadmin path cost\t%12u\n",
			path_cost, AdminPortPathCost);
		len += sprintf(buf + len,
			" designated root\t" BR_ID_FMT,
			BR_ID_ARGS(root));
		len += sprintf(buf + len,
			"\tdesignated cost\t%12u\n",
			ntohl(cost));
		len += sprintf(buf + len,
			" designated bridge\t" BR_ID_FMT,
			BR_ID_ARGS(designatedPriority.bridge_id));
		len += sprintf(buf + len,
			"\tdesignated port\t\t%02x%02x\n",
			designatedPriority.port_id.prio,
			designatedPriority.port_id.num);
		if (ForceProtocolVersion >= 3 && !p->MSTI) {
			COPY(root, designatedPriority.regional_root);
			cost = designatedPriority.internal_root_path_cost;
			len += sprintf(buf + len,
				" regional root\t\t" BR_ID_FMT,
				BR_ID_ARGS(root));
			len += sprintf(buf + len,
				"\tinternal cost\t%12u\n",
				ntohl(cost));
		}
		len += sprintf(buf + len,
			" admin edge port\t%4s",
			BOOL_STR(AdminEdge));
		len += sprintf(buf + len,
			"\t\t\tauto edge port\t\t%4s\n",
			BOOL_STR(AutoEdge));
		len += sprintf(buf + len,
			" oper edge port\t\t%4s",
			BOOL_STR(operEdge));
		len += sprintf(buf + len,
			"\t\t\ttopology change ack\t%4s\n",
			BOOL_STR(tcAck));
		len += sprintf(buf + len,
			" point to point\t\t%4s",
			BOOL_STR(operPointToPointMAC));
		len += sprintf(buf + len,
			"\t\t\tadmin point to point\t%4s\n",
			get_admin_p2p_str(adminPointToPointMAC));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_STP_ON:
		chk = portEnabled;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_STP_PRIO:
		chk = portId.prio;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_STP_ADMIN_PATH_COST:
		chk = AdminPortPathCost;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_STP_PATH_COST:
		chk = ExternalPortPathCost;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_STP_ADMIN_EDGE:
		chk = AdminEdge;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_STP_AUTO_EDGE:
		chk = AutoEdge;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_STP_MCHECK:
		chk = mcheck;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_STP_ADMIN_P2P:
		chk = adminPointToPointMAC;
		if (sw->verbose) {
			switch (chk) {
			case ADMIN_P2P_AUTO:
				strcpy(note, " (auto)");
				break;
			case ADMIN_P2P_FORCE_TRUE:
				strcpy(note, " (force true)");
				break;
			case ADMIN_P2P_FORCE_FALSE:
				strcpy(note, " (force false)");
				break;
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_STP_AUTO_ISOLATE:
		chk = AutoIsolate;
		type = SHOW_HELP_ON_OFF;
		break;
	}
	p->MSTI = p->br->MSTI = 0;
	mutex_unlock(&stp->br.lock);
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_stp_port_read */

static int sysfs_stp_port_write(struct ksz_sw *sw, int proc_num, uint port,
	int num, const char *buf)
{
	struct ksz_stp_info *stp = &sw->info->rstp;
	struct ksz_stp_port *p;
	int set;
	int change = 0;
	int processed = true;

	if (!(sw->features & STP_SUPPORT))
		return false;
	port = get_sysfs_port(sw, port);
	if (port == sw->HOST_PORT)
		return false;
	mutex_lock(&stp->br.lock);
	p = &stp->br.ports[port];
	p->MSTI = p->br->MSTI = p->br->MSTI_index;
	switch (proc_num) {
	case PROC_SET_STP_ON:
		set = !!num;
		if (set != portEnabled) {
			portEnabled = set;
			if (portEnabled && p->br->hack_4_2)
				mdelayWhile = 0;
			change = 1;
		}
		break;
	case PROC_SET_STP_PRIO:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		if ((0 <= num && num <= 0xf0) && !(num & ~0xf0)) {
			u8 prio = portId.prio;

			if (num != prio) {
				portId.prio = num;
				reselect = TRUE;
				selected = FALSE;
				change = 1;
			}
		}
		break;
	case PROC_SET_STP_ADMIN_PATH_COST:
		if (0 <= num && num <= PATH_COST * 10) {
			AdminPortPathCost = num;
			change = checkPathCost(p);
		}
		break;
	case PROC_SET_STP_PATH_COST:
		if (1 <= num && num <= PATH_COST * 10) {
			AdminPortPathCost = num;
			change = checkPathCost(p);
		}
		break;
	case PROC_SET_STP_ADMIN_EDGE:
		set = !!num;
		if (set != AdminEdge) {
			AdminEdge = set;
			change = 1;
		}
		break;
	case PROC_SET_STP_AUTO_EDGE:
		set = !!num;
		if (set != AutoEdge) {
			AutoEdge = set;
			change = 1;
		}
		break;
	case PROC_SET_STP_MCHECK:
		set = !!num;
		if (set != mcheck) {
			mcheck = set;
			change = 1;
		}
		break;
	case PROC_SET_STP_ADMIN_P2P:
		if (ADMIN_P2P_FORCE_FALSE <= num && num <= ADMIN_P2P_AUTO) {
			if (num != adminPointToPointMAC) {
				adminPointToPointMAC = num;
				change = checkP2P(p);
			}
		}
		break;
	case PROC_SET_STP_AUTO_ISOLATE:
		set = !!num;
		if (set != AutoIsolate) {
			AutoIsolate = set;
			change = 1;
		}
		break;
	default:
		processed = false;
		break;
	}
	p->MSTI = p->br->MSTI = 0;
	mutex_unlock(&stp->br.lock);
	if (change) {
		p->rx_bpdu0.protocol = 0xff;
		invoke_state_machines(p->br);
	}
	return processed;
}  /* sysfs_stp_port_write */

static u8 MAC_ADDR_STP[] = { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x00 };

static void prep_stp_mcast(struct net_device *dev)
{
	char addr[MAX_ADDR_LEN];

	memcpy(addr, MAC_ADDR_STP, ETH_ALEN);
	dev_mc_add(dev, addr);
}  /* prep_stp_mcast */

static void leave_stp(struct ksz_stp_info *stp)
{
	if (stp->dev)
		dev_mc_del(stp->dev, MAC_ADDR_STP);
}  /* leave_stp */

static struct stp_ops stp_ops = {
	.change_addr		= stp_change_addr,
	.link_change		= stp_link_change,

	.get_tcDetected		= stp_get_tcDetected,
};

static void ksz_stp_exit(struct ksz_stp_info *stp)
{
	flush_work(&stp->state_machine);
	flush_work(&stp->rx_proc);
}  /* ksz_stp_exit */

static void ksz_stp_init(struct ksz_stp_info *stp, struct ksz_sw *sw)
{
	struct ksz_stp_bridge *br;
	struct ksz_stp_port *p;
	uint i;
	int j;
	int num;
	struct llc *llc;
#ifdef DBG_STP_PORT_FLUSH
	struct ksz_stp_dbg_times *x;
#endif

	stp->sw_dev = sw;
	ksz_init_timer(&stp->port_timer_info, STP_TIMER_TICK * HZ / 1000,
		port_timer_monitor, stp);
	INIT_WORK(&stp->state_machine, proc_state_machines);
	INIT_WORK(&stp->rx_proc, proc_rx);
	mutex_init(&stp->br.lock);
	stp->ops = &stp_ops;

	memcpy(stp->tx_frame, MAC_ADDR_STP, ETH_ALEN);
	llc = (struct llc *) &stp->tx_frame[12];
	llc->dsap = 0x42;
	llc->ssap = 0x42;
	llc->ctrl = 0x03;
	stp->bpdu = (struct bpdu *)(llc + 1);

	br = &stp->br;
	br->parent = stp;
	if (sw->stp)
		br->bridgeEnabled = TRUE;

	br->port_cnt = sw->port_cnt;
	if (br->port_cnt > SWITCH_PORT_NUM)
		br->port_cnt = SWITCH_PORT_NUM;

	/* Can turn off ports.  Useful for using one port for telnet. */
	num = sw->stp;
	if (1 == num)
		num = sw->PORT_MASK;
	num &= ~sw->HOST_MASK;

	br->MSTI = 0;
	for (i = 0; i < SWITCH_PORT_NUM; i++) {
		p = &br->ports[i];
		p->MSTI = br->MSTI;
		if (!(num & (1 << i)))
			p->off = TRUE;
		skb_queue_head_init(&p->rxq);
		p->port_index = i;
		p->br = br;
		stp_port_init(p);
	}

	for (br->MSTI = 0; br->MSTI < NUM_OF_MSTI; br->MSTI++) {
		for (i = 0; i < br->port_cnt; i++) {
			p = &br->ports[i];
			p->MSTI = br->MSTI;
			if (p->off) {
				selectedRole = ROLE_DISABLED;
				role = ROLE_DISABLED;
				infoIs = INFO_TYPE_DISABLED;
				synced = TRUE;
				continue;
			}
			portId.num = get_log_port(sw, i);
			stp_port_msti_init(p);

#ifdef DBG_STP_PORT_FLUSH
			x = &p->dbg_times[p->MSTI];

			/* No Root Port connected to port yet. */
			x->role_ = ROLE_DISABLED;
			x->downPriority.port_id.num = 0;
#endif
		}

		p = &br->ports[0];
		ZERO(BridgePriority);
	}
	stp_br_init(p);
	for (i = 0; i < br->port_cnt; i++) {
		p = &br->ports[i];
		p->MSTI = br->MSTI;
	}

	sw->info->vid2fid[0] = sw->info->vid2fid[NUM_OF_VID + 1] = 0;
	for (i = 1; i < NUM_OF_VID; i++) {
		sw->info->vid2fid[i] = ((i - 1) % (FID_ENTRIES - 1)) + 1;
	}
	for (i = 1; i <= NUM_OF_MSTI; i++) {
		num = i / VID_IN_DATA;
		j = (VID_IN_DATA - 1) - (i % VID_IN_DATA);
		sw->info->vid[num] |= (1 << j);
	}
#if 0
	for (i = 0; i < FID_ENTRIES; i++)
		sw->info->fid2mstid[i] = 0;
#endif
#if 0
	for (i = 0; i < FID_ENTRIES; i++)
		sw->info->fid2mstid[i] = 1;
#endif
#if 0
	for (i = 0; i < FID_ENTRIES; i++)
		sw->info->fid2mstid[i] = (i % 32) + 1;
#endif
	for (i = 0; i < FID_ENTRIES; i++)
		sw->info->fid2mstid[i] = (i % NUM_OF_MSTI);
	recalc_cfg_digest(p);
}  /* ksz_stp_init */


#undef forward
#undef forwarding
#undef learn
#undef learning
#undef master
#undef mastered
#undef proposed
#undef proposing
#undef reselect
#undef selected
#undef sync
#undef synced

