/**
 * Micrel KSZ8462 HLI Ethernet driver
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/**
 * Supports:
 * KSZ8462/KSZ8441 16bit HLI chip from Micrel Inc.
 */

#if 0
#define DEBUG
#endif

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/cache.h>
#include <linux/crc32.h>
#include <linux/mii.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/eeprom_93cx6.h>
#include <linux/if_vlan.h>
#include <linux/net_tstamp.h>
#include <linux/phy.h>
#include <net/ip.h>
#include <net/ipv6.h>
#include <net/tcp.h>

#define KSZ846X_HLI
#include "ks846xReg.h"
#include "ksz8463.h"
#include "ksz8462.h"

#ifdef CONFIG_KSZ8462_HLI_STP
#define CONFIG_KSZ_STP
#endif

#ifdef CONFIG_KSZ_STP
#include <../net/bridge/br_private.h>
#endif

#ifdef CONFIG_KSZ8462_HLI_PTP
#define CONFIG_1588_PTP
#endif

/* For experiment. */
#if 0
#define KSZ_DLR
#endif

#ifdef DEBUG
#define DEBUG_MSG
#endif

/*
 * THa  2012/10/30
 * There are 4 ways to handle not enough transmit buffer space to transmit a
 * packet.  First is just simply return busy so the upper layer keeps calling
 * the driver to send the packet.  This is not desirable as it wastes CPU time.
 * The preferable way is to stop the transmit queue and restart the queue after
 * the transmit buffer has enough space to continue transmitting.  Normally
 * this is done using the interrupt mechanism.
 * Using the transmit buffer space request interrupt produces the best transmit
 * throughput.  When the transmit buffer reaches a set threshold an interrupt
 * will be triggered to let the driver know to wake up the transmit queue.
 * By experiment it was found using the threshold close to the maximum buffer
 * size yields the highest transmit throughput.
 * The transmit done interrupt can be used to simulate the transmit buffer
 * request interrupt behavior.  When the transmit buffer is less than 1520
 * bytes the queue is stopped and the packet is sent with interrupt on.  When
 * the transmit done interrupt is triggered then the transmit buffer should
 * have more than (1520 * 3) bytes available.
 * Unfortunately the current chip has problems using the transmit interrupts.
 * That leaves only the polling way.  A workqueue is scheduled to check the
 * transmit buffer size is greater than a certain threshold until the condition
 * is met.  The transmit throughput is the lowest, but the CPU time used is
 * much less.
 */

#define TX_BUF_MIN			4
#define TXFID_INTR_DONE			0x20

#if 0
#define USE_TX_DONE_INTR
#define TX_DONE_MIN			(1520 + TX_BUF_MIN)
#endif

#if 1
#define USE_TX_BUF_INTR
#endif

#if 0
#define USE_2_BYTE_OFFSET
#endif

#define DRV_NAME			"ksz8462_hli"
#define DRV_VERSION			"1.0.0"

#define MAX_RECV_FRAMES			180 /* 32 */
#define MAX_BUF_SIZE			2048
#define TX_BUF_SIZE			2000
#define RX_BUF_SIZE			2000


#define	ENUM_BUS_NONE			0
#define	ENUM_BUS_8BIT			1
#define	ENUM_BUS_16BIT			2
#define	ENUM_BUS_32BIT			3

#define MAX_MCAST_LST			32
#define HW_MCAST_SIZE			4

#define MIB_COUNTER_RX_LO_PRIORITY	0x00
#define MIB_COUNTER_RX_HI_PRIORITY	0x01
#define MIB_COUNTER_RX_UNDERSIZE	0x02
#define MIB_COUNTER_RX_FRAGMENT		0x03
#define MIB_COUNTER_RX_OVERSIZE		0x04
#define MIB_COUNTER_RX_JABBER		0x05
#define MIB_COUNTER_RX_SYMBOL_ERR	0x06
#define MIB_COUNTER_RX_CRC_ERR		0x07
#define MIB_COUNTER_RX_ALIGNMENT_ERR	0x08
#define MIB_COUNTER_RX_CTRL_8808	0x09
#define MIB_COUNTER_RX_PAUSE		0x0A
#define MIB_COUNTER_RX_BROADCAST	0x0B
#define MIB_COUNTER_RX_MULTICAST	0x0C
#define MIB_COUNTER_RX_UNICAST		0x0D
#define MIB_COUNTER_RX_OCTET_64		0x0E
#define MIB_COUNTER_RX_OCTET_65_127	0x0F
#define MIB_COUNTER_RX_OCTET_128_255	0x10
#define MIB_COUNTER_RX_OCTET_256_511	0x11
#define MIB_COUNTER_RX_OCTET_512_1023	0x12
#define MIB_COUNTER_RX_OCTET_1024_1522	0x13
#define MIB_COUNTER_TX_LO_PRIORITY	0x14
#define MIB_COUNTER_TX_HI_PRIORITY	0x15
#define MIB_COUNTER_TX_LATE_COLLISION	0x16
#define MIB_COUNTER_TX_PAUSE		0x17
#define MIB_COUNTER_TX_BROADCAST	0x18
#define MIB_COUNTER_TX_MULTICAST	0x19
#define MIB_COUNTER_TX_UNICAST		0x1A
#define MIB_COUNTER_TX_DEFERRED		0x1B
#define MIB_COUNTER_TX_TOTAL_COLLISION	0x1C
#define MIB_COUNTER_TX_EXCESS_COLLISION	0x1D
#define MIB_COUNTER_TX_SINGLE_COLLISION	0x1E
#define MIB_COUNTER_TX_MULTI_COLLISION	0x1F

#define MIB_COUNTER_RX_DROPPED_PACKET	0x20
#define MIB_COUNTER_TX_DROPPED_PACKET	0x21

/* -------------------------------------------------------------------------- */

/**
 * struct ks_rxctrl - KSZ8462SLI driver rx control
 * @mchash: Multicast hash-table data.
 * @rxcr1: KS_RXCR1 register setting
 * @rxcr2: KS_RXCR2 register setting
 *
 * Representation of the settings needs to control the receive filtering
 * such as the multicast hash-filter and the receive register settings. This
 * is used to make the job of working out if the receive settings change and
 * then issuing the new settings to the worker that will send the necessary
 * commands.
 */
struct ks_rxctrl {
	u16	mchash[4];
	u16	rxcr1;
	u16	rxcr2;
};

/**
 * union ks_tx_hdr - tx header data
 * @txb: The header as bytes
 * @txw: The header as 16bit, little-endian words
 *
 * A dual representation of the tx header data to allow
 * access to individual bytes, and to allow 16bit accesses
 * with 16bit alignment.
 */
union ks_tx_hdr {
	u8	txb[6];
	__le16	txw[3];
};

/* Receive multiplex framer header info */
struct type_frame_head {
	u16	sts;         /* Frame status */
	u16	len;         /* Byte count */
};

/* Hardware features and bug fixes. */

/* Software overrides. */
#define RX_LOOPBACK			(1 << 3)
#define RX_ALL				(1 << 4)
#define DATA_HEADER			(1 << 5)

struct ksz_hw {
	void __iomem *hw_addr;
	void __iomem *hw_addr_cmd;
	union ks_tx_hdr txh ____cacheline_aligned;
	struct type_frame_head *frame_head_info;
	int			frame_cnt;
	int			frame_max;
	int			bus_width;
	int			RX_MAX;
	u32			rx_cont;
	int			rx_fragment;
	int			rx_final;
	int			rx_tcp;
	int			rx_max;
	int			rx_num;
	unsigned long		isr_jiffies;
	unsigned long		rx_jiffies;
	u16			rx_cnt;
	u16			rx_intr;
	u16			rc_ccr;
	u16			rc_ier;
	u16			rc_isr;
	u16			rc_rxcr1;
	u16			rc_txqcr;
	u16			rc_rxqcr;
	u32			rc_qcr;

	struct ks_rxctrl	rxctrl;

	u16			sharedbus;
	u16			cmd_reg_cache_int;
	u16			tx_max;
	u16			tx_len;
	u8			fid;
	u8			extra_byte;
	u8			promiscuous;
	u8			all_mcast;
	u8			mac_addr[ETH_ALEN];
	u8			enabled;
	u8			mcast_lst_reserved;
	u8			mcast_lst_size;
	u8			mcast_lst[MAX_MCAST_LST][ETH_ALEN];
	u16			mcast_bits[HW_MCAST_SIZE];

	uint oper_state;
#define OPER_STATE_TX_PAUSED	(1 << 0)
#define OPER_STATE_TX_RESET	(1 << 1)

	uint features;
	uint overrides;
};

enum {
	PHY_NO_FLOW_CTRL,
	PHY_FLOW_CTRL,
	PHY_TX_ONLY,
	PHY_RX_ONLY
};

enum {
	media_connected,
	media_disconnected,
	media_unknown
};

/* -------------------------------------------------------------------------- */

/**
 * struct ksz_timer_info - Timer information data structure
 * @timer:	Kernel timer.
 * @cnt:	Running timer counter.
 * @max:	Number of times to run timer; -1 for infinity.
 * @period:	Timer period in jiffies.
 */
struct ksz_timer_info {
	struct timer_list timer;
	int cnt;
	int max;
	int period;
};

/**
 * struct ksz_counter_info - OS dependent counter information data structure
 * @counter:	Wait queue to wakeup after counters are read.
 * @time:	Next time in jiffies to read counter.
 * @read:	Indication of counters read in full or not.
 */
struct ksz_counter_info {
	wait_queue_head_t counter;
	unsigned long time;
	int read;
};

#define DEV_NAME_SIZE			20

struct ksz_dev_attr {
	struct device_attribute dev_attr;
	char dev_name[DEV_NAME_SIZE];
};

#ifdef CONFIG_1588_PTP
/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.c"
#endif

/* -------------------------------------------------------------------------- */

#include "ksz_sw.h"

#define HW_R(ks, reg)		ks_rdreg16(&(ks)->hw, reg)
#define HW_W(ks, reg, val)	ks_wrreg16(&(ks)->hw, reg, val)

/**
 * struct dev_priv - Network device private data structure
 * @adapter:		Adapter device information.
 * @port:		Port information.
 * @monitor_time_info:	Timer to monitor ports.
 * @stats:		Network statistics.
 * @proc_sem:		Semaphore for proc accessing.
 * @id:			Device ID.
 * @mii_if:		MII interface information.
 * @advertising:	Temporary variable to store advertised settings.
 * @msg_enable:		The message flags controlling driver output.
 * @media_state:	The connection status of the device.
 * @multicast:		The all multicast state of the device.
 * @promiscuous:	The promiscuous state of the device.
 */
struct dev_info {
	struct platform_device *pdev;
	struct net_device *dev;
	struct napi_struct napi;
	int use_napi;

	struct ksz_hw hw;
	struct ksz_sw sw;

	struct ksz_sw_sysfs sysfs;
#ifdef CONFIG_1588_PTP
	struct ksz_ptp_sysfs ptp_sysfs;
#endif
	struct semaphore proc_sem;

	struct mutex hwlock;
	struct mutex lock;

	struct delayed_work link_read;
	struct work_struct mib_read;
	struct delayed_work stp_monitor;
	struct ksz_timer_info mib_timer_info;
	struct ksz_timer_info monitor_timer_info;
	struct ksz_counter_info counter[TOTAL_PORT_NUM];

	struct dentry *debug_root;
	struct dentry *debug_file;

	struct eeprom_93cx6 eeprom;

	struct work_struct rxctrl_work;

	struct tasklet_struct rx_tasklet;

	int opened;

	int wol_enable;
	int wol_support;

	struct work_struct tx_reset;
};

/**
 * struct ks_net - KSZ8461/2 HLI driver private data
 * @net_device	: The network device we're bound to
 * @stats:		Network statistics.
 * @hw_addr	: start address of data register.
 * @hw_addr_cmd	: start address of command register.
 * @txh		: temporaly buffer to save status/length.
 * @lock	: Lock to ensure that the device is not accessed when busy.
 * @pdev	: Pointer to platform device.
 * @mii		: The MII state information for the mii calls.
 * @frame_head_info	: frame header information for multi-pkt rx.
 * @statelock	: Lock on this structure for tx list.
 * @msg_enable	: The message flags controlling driver output (see ethtool).
 * @frame_cnt	: number of frames received.
 * @bus_width	: i/o bus width.
 * @irq		: irq number assigned to this device.
 * @rc_rxqcr	: Cached copy of KS_RXQCR.
 * @rc_txcr	: Cached copy of KS_TXCR.
 * @rc_ier	: Cached copy of KS_IER.
 * @sharedbus	: Multipex(addr and data bus) mode indicator.
 * @cmd_reg_cache_int	: command register cached. Used in the irq handler.
 * @promiscuous	: promiscuous mode indicator.
 * @all_mcast	: mutlicast indicator.
 * @mcast_lst_size	: size of multicast list.
 * @mcast_lst	: multicast list.
 * @mcast_bits	: multicast enabed.
 * @mac_addr	: MAC address assigned to this device.
 * @fid		: frame id.
 * @extra_byte	: number of extra byte prepended rx pkt.
 * @enabled	: indicator this device works.
 *
 * The @lock ensures that the chip is protected when certain operations are
 * in progress. When the read or write packet transfer is in progress, most
 * of the chip registers are not accessible until the transfer is finished and
 * the DMA has been de-asserted.
 *
 * The @statelock is used to protect information in the structure which may
 * need to be accessed via several sources, such as the network driver layer
 * or one of the work queues.
 *
 */
struct ks_net {
	struct net_device *netdev;
	struct dev_info *adapter;
	struct ksz_port port;
	struct net_device_stats stats;

	int id;

	/* spinlock to be interrupt safe */
	struct mutex lock;
	spinlock_t statelock;

	struct device *dev;

	struct mii_if_info mii_if;
	u32 advertising;

	u32 msg_enable;
	int irq;
	int media_state;
	int multicast;
	int promiscuous;
	u8 phy_addr;
	u8 state;
	u8 multi_list_size;
	u8 multi_list[MAX_MCAST_LST][ETH_ALEN];
};

#define dev_priv			ks_net


#define BE3             0x8000      /* Byte Enable 3 */
#define BE2             0x4000      /* Byte Enable 2 */
#define BE1             0x2000      /* Byte Enable 1 */
#define BE0             0x1000      /* Byte Enable 0 */

/**
 * register read/write calls.
 *
 * All these calls issue transactions to access the chip's registers. They
 * all require that the necessary lock is held to prevent accesses when the
 * chip is busy transfering packet data (RX/TX FIFO accesses).
 */

/**
 * ks_rdreg8 - read 8 bit register from device
 * @hw:		The hardware instance.
 * @offset:	The register address.
 *
 * Read a 8bit register from the chip, returning the result.
 */
static u8 ks_rdreg8(struct ksz_hw *hw, int offset)
{
	u16 addr;
	u16 data;
	u8 shift_bit = offset & 0x03;
	u8 shift_data = (offset & 1) << 3;

	addr = (u16) offset | (u16)(BE0 << shift_bit);
	iowrite16(addr, hw->hw_addr_cmd);
	data = ioread16(hw->hw_addr);
	return (u8)(data >> shift_data);
}

/**
 * ks_rdreg16 - read 16 bit register from device
 * @hw:		The hardware instance.
 * @offset:	The register address.
 *
 * Read a 16bit register from the chip, returning the result.
 */
static u16 ks_rdreg16(struct ksz_hw *hw, int offset)
{
	u16 addr;

	addr = (u16) offset | ((BE1 | BE0) << (offset & 0x02));
	iowrite16(addr, hw->hw_addr_cmd);
	return ioread16(hw->hw_addr);
}

/**
 * ks_rdreg32 - read 32-bit register from device
 * @hw:		The hardware instance.
 * @offset:	The register address.
 *
 * Read a 32-bit register from the chip, returning the result.
 */
static u32 ks_rdreg32(struct ksz_hw *hw, int offset)
{
	u32 data;

	data = ks_rdreg16(hw, offset + 2);
	data <<= 16;
	data |= ks_rdreg16(hw, offset);
	return data;
}

/**
 * ks_wrreg8 - write 8bit register value to chip
 * @hw:		The hardware instance.
 * @offset:	The register address.
 * @value:	The value to write.
 *
 */
static void ks_wrreg8(struct ksz_hw *hw, int offset, u8 value)
{
	u16 addr;
	u8 shift_bit = (offset & 0x03);
	u16 value_write = (u16)(value << ((offset & 1) << 3));

	addr = (u16) offset | (BE0 << shift_bit);
	iowrite16(addr, hw->hw_addr_cmd);
	iowrite16(value_write, hw->hw_addr);
}

/**
 * ks_wrreg16 - write 16bit register value to chip
 * @hw:		The hardware instance.
 * @offset:	The register address.
 * @value:	The value to write.
 *
 */

static void ks_wrreg16(struct ksz_hw *hw, int offset, u16 value)
{
	u16 addr;

	addr = (u16) offset | ((BE1 | BE0) << (offset & 0x02));
	iowrite16(addr, hw->hw_addr_cmd);
	iowrite16(value, hw->hw_addr);
}

/**
 * ks_wrreg32 - write 32-bit register value to chip
 * @hw:		The hardware instance.
 * @offset:	The register address.
 * @value:	The value to write.
 *
 */
static void ks_wrreg32(struct ksz_hw *hw, int offset, u32 value)
{
	ks_wrreg16(hw, offset, (u16) value);
	ks_wrreg16(hw, offset + 2, value >> 16);
}

/**
 * ks_inblk - read a block of data from QMU.  This is called after pseudo DMA
 *	mode is enabled.
 * @hw:		The hardware instance.
 * @wptr:	buffer address to save data.
 * @len:	length in byte to read.
 *
 */
static inline void ks_inblk(struct ksz_hw *hw, u16 *wptr, u32 len)
{
	len >>= 1;
	while (len--)
		*wptr++ = (u16) ioread16(hw->hw_addr);
}

/**
 * ks_outblk - write data to QMU.  This is called after pseudo DMA mode is
 *	enabled.
 * @hw:		The hardware instance.
 * @wptr:	buffer address.
 * @len:	length in byte to write.
 *
 */
static inline void ks_outblk(struct ksz_hw *hw, u16 *wptr, u32 len)
{
	len >>= 1;
	while (len--)
		iowrite16(*wptr++, hw->hw_addr);
}

/**
 * ks_save_cmd_reg - save the command register from the cache.
 * @hw:		The hardware instance.
 *
 */
static inline void ks_save_cmd_reg(struct ksz_hw *hw)
{
	hw->cmd_reg_cache_int = ioread16(hw->hw_addr_cmd);
}

/**
 * ks_restore_cmd_reg - restore the command register from the cache and
 *	write to hardware register.
 * @hw:		The hardware instance.
 *
 */
static inline void ks_restore_cmd_reg(struct ksz_hw *hw)
{
	iowrite16(hw->cmd_reg_cache_int, hw->hw_addr_cmd);
}

/**
 * ks_dbg_dumpkkt - dump initial packet contents to debug
 * @ks:		The device state.
 * @rxpkt:	The data for the received packet.
 *
 * Dump the initial data from the packet to dev_dbg().
 */
static void ks_dbg_dumpkkt(struct ks_net *ks, u8 *rxpkt, int len, int flag)
{
	int j = 0, k;
	u8 *data = rxpkt;

	printk(KERN_DEBUG "%s On port\n", (flag == 1) ? "Tx" : "Rx");
	printk(KERN_DEBUG "Pkt Len=%d\n", len);
	do {
		printk(KERN_DEBUG "\n %04x   ", j);
		for (k = 0; (k < 16 && len); k++, data++, len--)
			printk(KERN_DEBUG "%02x  ", *data);
		j += 16;
	} while (len > 0);
	printk(KERN_DEBUG "\n");
}

/* -------------------------------------------------------------------------- */

/**
 * delay_micro - delay in microsecond
 * @microsec:	Number of microseconds to delay.
 *
 * This routine delays in microseconds.
 */
static inline void delay_micro(uint microsec)
{
	uint millisec = microsec / 1000;

	microsec %= 1000;
	if (millisec)
		mdelay(millisec);
	if (microsec)
		udelay(microsec);
}

/**
 * delay_milli - delay in millisecond
 * @millisec:	Number of milliseconds to delay.
 *
 * This routine delays in milliseconds.
 */
static void delay_milli(uint millisec)
{
	unsigned long ticks = millisec * HZ / 1000;

	if (!ticks || in_interrupt())
		mdelay(millisec);
	else {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(ticks);
	}
}

/* -------------------------------------------------------------------------- */

static struct hw_regs {
	int start;
	int end;
} hw_regs_range[] = {
	{ 0x000, 0x1BA },
	{ 0x200, 0x398 },
	{ 0x400, 0x690 },
	{ 0x734, 0x736 },
	{ 0x748, 0x74E },
	{ 0, 0 }
};

#define KSZSW_REGS_SIZE			0x800

static int check_sw_reg_range(unsigned addr)
{
	struct hw_regs *range = hw_regs_range;

	while (range->end > range->start) {
		if (range->start <= addr && addr < range->end)
			return true;
		range++;
	}
	return false;
}

static struct ksz_sw *get_sw_data(struct device *d)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	return &hw_priv->sw;
}

/* -------------------------------------------------------------------------- */

static inline void copy_old_skb(struct sk_buff *old, struct sk_buff *skb)
{
	skb->dev = old->dev;
	skb->protocol = old->protocol;
	skb->ip_summed = old->ip_summed;
	skb->csum = old->csum;
	skb_set_network_header(skb, ETH_HLEN);

	dev_kfree_skb(old);
}  /* copy_old_skb */

#include "ksz_common.c"

static inline int sw_is_switch(struct ksz_sw *sw)
{
	return sw->info != NULL;
}

/* -------------------------------------------------------------------------- */

#define MIB_READ_INTERVAL		(HZ / 2)

static unsigned long next_jiffies;

static int exit_mib_read(struct ksz_sw *sw)
{
	return false;
}  /* exit_mib_read */

static void sw_ena_intr(struct ksz_sw *sw)
{
}  /* sw_ena_intr */

static u8 sw_r8(struct ksz_sw *sw, unsigned reg)
{
	return ks_rdreg8(sw->dev, reg);
}

static u16 sw_r16(struct ksz_sw *sw, unsigned reg)
{
	return ks_rdreg16(sw->dev, reg);
}

static u32 sw_r32(struct ksz_sw *sw, unsigned reg)
{
	return ks_rdreg32(sw->dev, reg);
}

static void sw_w8(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	ks_wrreg8(sw->dev, reg, val);
}

static void sw_w16(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	ks_wrreg16(sw->dev, reg, val);
}

static void sw_w32(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	ks_wrreg32(sw->dev, reg, val);
}

#ifdef CONFIG_1588_PTP
/* These are chip dependent 1588 PTP code. */

#ifdef ENABLE_IRIG
#define IRIG_INTERVAL			10000000
#define IRIG_GPIO			2
#endif

static int ks_start_xmit(struct sk_buff *skb, struct net_device *dev);
#define netdev_tx			ks_start_xmit

#define ADDR_SHIFT			14
#define ADDR_8				1
#define ADDR_16				2
#define ADDR_32				3

#define BANK_SHIFT			12
#define BANK_SWITCH			0
#define BANK_TOUT			1
#define BANK_TEVT			2
#define BANK_PTP			3
#endif

#ifdef CONFIG_KSZ_STP
static u8 get_port_state(struct net_device *dev, struct net_device **br_dev)
{
	struct net_bridge_port *p;
	u8 state;

	/* This state is not defined in kernel. */
	state = STP_STATE_SIMPLE;
	if (br_port_exists(dev)) {
		p = br_port_get_rcu(dev);
		state = p->state;

		/* Port is under bridge. */
		*br_dev = p->br->dev;
	}
	return state;
}  /* get_port_state */
#endif

static void link_update_work(struct work_struct *work)
{
#ifdef KSZ_DLR
	struct ksz_port *port =
		container_of(work, struct ksz_port, link_update);
	struct ksz_sw *sw = port->sw;
	struct ksz_dlr_info *dlr = &sw->info->dlr;

	dlr->ops->link_change(dlr,
		sw->port_info[0].state == media_connected,
		sw->port_info[1].state == media_connected);
#endif
}

#define USE_DIFF_PORT_PRIORITY
#include "ksz_sw.c"

static void sw_disable(struct ksz_sw *sw)
{
	SW_D data;

	if (sw->port_info[0].fiber) {
		data = SW_R(sw, REG_CFG_CTRL);
		data &= ~PORT_1_COPPER_MODE;
		SW_W(sw, REG_CFG_CTRL, data);
		data = SW_R(sw, REG_DSP_CTRL_6);
		data &= ~COPPER_RECEIVE_ADJUSTMENT;
		SW_W(sw, REG_DSP_CTRL_6, data);
	}
	sw_set_global_ctrl(sw);

	/*
	 * Switch actually cannot do auto-negotiation with old 10Mbit hub.
	 */
	port_r(sw, 0, P_FORCE_CTRL, &data);
	if (sw->port_info[0].fiber) {
		port_cfg_force_flow_ctrl(sw, 0, 1);
		data &= ~PORT_AUTO_NEG_ENABLE;
		data |= PORT_FORCE_FULL_DUPLEX;
	} else {
		port_cfg_force_flow_ctrl(sw, 0, 0);
		data &= ~PORT_FORCE_FULL_DUPLEX;
	}
	port_w(sw, 0, P_FORCE_CTRL, data);

	sw_setup_mirror(sw);

	port_cfg_rx(sw, 1, 0);
	port_cfg_tx(sw, 1, 0);
}

/* -------------------------------------------------------------------------- */

/**
 * hw_cfg_wol - configure Wake-on-LAN features
 * @hw:		The hardware instance.
 * @frame:	The pattern frame bit.
 * @set:	The flag indicating whether to enable or disable.
 *
 * This routine is used to enable or disable certain Wake-on-LAN features.
 */
static void hw_cfg_wol(struct ksz_hw *hw, u16 frame, int set)
{
	u16 data;

	data = ks_rdreg16(hw, REG_WOL_CTRL_ETH);
	if (set)
		data |= frame;
	else
		data &= ~frame;
	ks_wrreg16(hw, REG_WOL_CTRL_ETH, data);
}

/**
 * hw_set_wol_frame - program Wake-on-LAN pattern
 * @hw:		The hardware instance.
 * @i:		The frame index.
 * @mask_size:	The size of the mask.
 * @mask:	Mask to ignore certain bytes in the pattern.
 * @frame_size:	The size of the frame.
 * @pattern:	The frame data.
 *
 * This routine is used to program Wake-on-LAN pattern.
 */
static void hw_set_wol_frame(struct ksz_hw *hw, int i, uint mask_size,
	u8 *mask, uint frame_size, u8 *pattern)
{
	int bits;
	int from;
	int len;
	int to;
	u32 crc;
	u8 data[64];
	u8 val = 0;

	if (frame_size > mask_size * 8)
		frame_size = mask_size * 8;
	if (frame_size > 64)
		frame_size = 64;

	i *= 0x10;
	ks_wrreg32(hw, REG_WOL_FRAME0_BYTE_MASK0 + i, 0);
	ks_wrreg32(hw, REG_WOL_FRAME0_BYTE_MASK2 + i, 0);

	bits = len = from = to = 0;
	do {
		if (bits) {
			if ((val & 1))
				data[to++] = pattern[from];
			val >>= 1;
			++from;
			--bits;
		} else {
			val = mask[len];
			ks_wrreg8(hw, REG_WOL_FRAME0_BYTE_MASK0 + i + len,
				val);
			++len;
			if (val)
				bits = 8;
			else
				from += 8;
		}
	} while (from < (int) frame_size);
	if (val) {
		bits = mask[len - 1];
		val <<= (from % 8);
		bits &= ~val;
		ks_wrreg8(hw, REG_WOL_FRAME0_BYTE_MASK0 + i + len - 1, bits);
	}
	crc = ether_crc(to, data);
	ks_wrreg32(hw, REG_WOL_FRAME0_CRC0 + i, crc);
}

/**
 * hw_add_wol_arp - add ARP pattern
 * @hw:		The hardware instance.
 * @ip_addr:	The IPv4 address assigned to the device.
 *
 * This routine is used to add ARP pattern for waking up the host.
 */
static void hw_add_wol_arp(struct ksz_hw *hw, u8 *ip_addr)
{
	u8 mask[6] = { 0x3F, 0xF0, 0x3F, 0x00, 0xC0, 0x03 };
	u8 pattern[42] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x06,
		0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00 };

	memcpy(&pattern[38], ip_addr, 4);
	hw_set_wol_frame(hw, 3, 6, mask, 42, pattern);
}

/**
 * hw_add_wol_bcast - add broadcast pattern
 * @hw:		The hardware instance.
 *
 * This routine is used to add broadcast pattern for waking up the host.
 */
static void hw_add_wol_bcast(struct ksz_hw *hw)
{
	u8 mask[] = { 0x3F };
	u8 pattern[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

	hw_set_wol_frame(hw, 2, 1, mask, ETH_ALEN, pattern);
}

/**
 * hw_add_wol_mcast - add multicast pattern
 * @hw:		The hardware instance.
 *
 * This routine is used to add multicast pattern for waking up the host.
 *
 * It is assumed the multicast packet is the ICMPv6 neighbor solicitation used
 * by IPv6 ping command.  Note that multicast packets are filtred through the
 * multicast hash table, so not all multicast packets can wake up the host.
 */
static void hw_add_wol_mcast(struct ksz_hw *hw)
{
	u8 mask[] = { 0x3F };
	u8 pattern[] = { 0x33, 0x33, 0xFF, 0x00, 0x00, 0x00 };

	memcpy(&pattern[3], &hw->mac_addr[3], 3);
	hw_set_wol_frame(hw, 1, 1, mask, 6, pattern);
}

/**
 * hw_add_wol_ucast - add unicast pattern
 * @hw:		The hardware instance.
 *
 * This routine is used to add unicast pattern to wakeup the host.
 *
 * It is assumed the unicast packet is directed to the device, as the hardware
 * can only receive them in normal case.
 */
static void hw_add_wol_ucast(struct ksz_hw *hw)
{
	u8 mask[] = { 0x3F };

	hw_set_wol_frame(hw, 0, 1, mask, ETH_ALEN, hw->mac_addr);
}

/**
 * hw_enable_wol - enable Wake-on-LAN
 * @hw:		The hardware instance.
 * @wol_enable:	The Wake-on-LAN settings.
 * @net_addr:	The IPv4 address assigned to the device.
 *
 * This routine is used to enable Wake-on-LAN depending on driver settings.
 */
static void hw_enable_wol(struct ksz_hw *hw, u32 wol_enable, u8 *net_addr)
{
	hw_cfg_wol(hw, WOL_MAGIC_ENABLE_ETH, (wol_enable & WAKE_MAGIC));
	hw_cfg_wol(hw, WOL_FRAME0_ENABLE_ETH, (wol_enable & WAKE_UCAST));
	hw_add_wol_ucast(hw);
	hw_cfg_wol(hw, WOL_FRAME1_ENABLE_ETH, (wol_enable & WAKE_MCAST));
	hw_add_wol_mcast(hw);
	hw_cfg_wol(hw, WOL_FRAME2_ENABLE_ETH, (wol_enable & WAKE_BCAST));
	hw_cfg_wol(hw, WOL_FRAME3_ENABLE_ETH, (wol_enable & WAKE_ARP));
	hw_add_wol_arp(hw, net_addr);
}

/* EEPROM support */

static void ks_eeprom_regread(struct eeprom_93cx6 *ee)
{
	struct ksz_hw *hw = ee->data;
	unsigned val;

	val = ks_rdreg16(hw, KS_EEPCR);

	ee->reg_data_out = (val & EEPCR_EESB) ? 1 : 0;
	ee->reg_data_clock = (val & EEPCR_EESCK) ? 1 : 0;
	ee->reg_chip_select = (val & EEPCR_EECS) ? 1 : 0;
}

static void ks_eeprom_regwrite(struct eeprom_93cx6 *ee)
{
	struct ksz_hw *hw = ee->data;
	unsigned val = EEPCR_EESA;	/* default - eeprom access on */

	if (ee->drive_data)
		val |= EEPCR_EEDW;
	if (ee->reg_data_in)
		val |= EEPCR_EEDO;
	if (ee->reg_data_clock)
		val |= EEPCR_EESCK;
	if (ee->reg_chip_select)
		val |= EEPCR_EECS;

	ks_wrreg16(hw, KS_EEPCR, val);
}

/**
 * ks_eeprom_claim - claim device EEPROM and activate the interface
 * @ks: The network device state.
 *
 * Check for the presence of an EEPROM, and then activate software access
 * to the device.
 */
static int ks_eeprom_claim(struct dev_info *ks)
{
	struct ksz_hw *hw = &ks->hw;

	if (!(hw->rc_ccr & CCR_EEPROM))
		return -ENOENT;

	mutex_lock(&ks->lock);

	/* start with clock low, cs high */
	ks_wrreg16(hw, KS_EEPCR, EEPCR_EESA | EEPCR_EECS);
	return 0;
}

/**
 * ks_eeprom_release - release the EEPROM interface
 * @ks: The device state
 *
 * Release the software access to the device EEPROM
 */
static void ks_eeprom_release(struct dev_info *ks)
{
	struct ksz_hw *hw = &ks->hw;
	unsigned val = ks_rdreg16(hw, KS_EEPCR);

	ks_wrreg16(hw, KS_EEPCR, val & ~EEPCR_EESA);
	mutex_unlock(&ks->lock);
}

/* -------------------------------------------------------------------------- */

/* debugfs code */
static int state_show(struct seq_file *seq, void *v)
{
	int i;
	int j;
	SW_D data[16 / SW_SIZE];
	struct dev_info *ks = seq->private;

	for (i = 0; i < 0x100; i += 16) {
		seq_printf(seq, SW_SIZE_STR":\t", i);
		mutex_lock(&ks->lock);
		for (j = 0; j < 16 / SW_SIZE; j++)
			data[j] = HW_R(ks, i + j * SW_SIZE);
		mutex_unlock(&ks->lock);
		for (j = 0; j < 16 / SW_SIZE; j++)
			seq_printf(seq, SW_SIZE_STR" ", data[j]);
		seq_printf(seq, "\n");
	}
	return 0;
}

static int state_open(struct inode *inode, struct file *file)
{
	return single_open(file, state_show, inode->i_private);
}

static const struct file_operations state_fops = {
	.owner	= THIS_MODULE,
	.open	= state_open,
	.read	= seq_read,
	.llseek	= seq_lseek,
	.release = single_release,
};

/**
 * dev_create_debugfs - create debugfs directory and files
 * @ks:		The device structure.
 *
 * Create the debugfs entries for the specific device.
 */
static void dev_create_debugfs(struct dev_info *ks)
{
	struct dentry *root;
	char root_name[32];

	snprintf(root_name, sizeof(root_name), "net_%s",
		 dev_name(&ks->pdev->dev));

	root = debugfs_create_dir(root_name, NULL);
	if (IS_ERR(root)) {
		pr_err("cannot create debugfs root\n");
		return;
	}

	ks->debug_root = root;
	ks->debug_file = debugfs_create_file("state", 0444, root,
		ks, &state_fops);
	if (IS_ERR(ks->debug_file))
		pr_err("cannot create debugfs state file\n");
}

static void dev_delete_debugfs(struct dev_info *ks)
{
	debugfs_remove(ks->debug_file);
	debugfs_remove(ks->debug_root);
}

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_1588_PTP
#ifdef CONFIG_ARCH_MICREL_PEGASUS
extern unsigned int ksz_system_bus_clock;

static u32 get_clk_cnt(void)
{
	return KS_R(KS8692_TIMER1_COUNTER);
}
#endif
#endif

/* -------------------------------------------------------------------------- */

static void get_private_data(struct device *d, struct semaphore **proc_sem,
	struct ksz_sw **sw, struct ksz_port **port)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	*proc_sem = &hw_priv->proc_sem;
	*sw = &hw_priv->sw;
	if (port)
		*port = &priv->port;
}

#include "ksz_sw_sysfs.c"

#ifdef CONFIG_1588_PTP
#include "ksz_ptp_sysfs.c"
#endif
#ifdef KSZ_DLR
#include "ksz_dlr_sysfs.c"
#endif

/* -------------------------------------------------------------------------- */

static void set_media_state(struct net_device *dev, int media_state)
{
	struct ks_net *priv = netdev_priv(dev);

	if (media_state == priv->media_state)
		netif_carrier_on(dev);
	else
		netif_carrier_off(dev);
	netif_info(priv, link, dev, "link %s\n",
		media_state == priv->media_state ? "on" : "off");
}

static void update_link(struct net_device *dev, struct ks_net *priv,
	struct ksz_port *port)
{
	if (priv->media_state != port->linked->state) {
		priv->media_state = port->linked->state;
		if (netif_running(dev))
			set_media_state(dev, media_connected);
	}
}

static void mib_read_work(struct work_struct *work)
{
	struct dev_info *hw_priv =
		container_of(work, struct dev_info, mib_read);
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port_mib *mib;
	int i;

	next_jiffies = jiffies;
	for (i = 0; i < sw->mib_port_cnt; i++) {
		mib = &sw->port_mib[i];

		/* Reading MIB counters or requested to read. */
		if (mib->cnt_ptr || 1 == hw_priv->counter[i].read) {

			/* Need to process interrupt. */
			if (sw->ops->port_r_cnt(sw, i))
				return;
			hw_priv->counter[i].read = 0;

			/* Finish reading counters. */
			if (0 == mib->cnt_ptr) {
				hw_priv->counter[i].read = 2;
				wake_up_interruptible(
					&hw_priv->counter[i].counter);
			}
		} else if (jiffies >= hw_priv->counter[i].time) {
			/* Only read MIB counters when the port is connected. */
			if (media_connected == sw->port_state[i].state)
				hw_priv->counter[i].read = 1;

			/* Read dropped counters. */
			else
				mib->cnt_ptr = SWITCH_COUNTER_NUM;
			next_jiffies += MIB_READ_INTERVAL * sw->mib_port_cnt;
			hw_priv->counter[i].time = next_jiffies;

		/* Port is just disconnected. */
		} else if (sw->port_state[i].link_down) {
			sw->port_state[i].link_down = 0;

			/* Read counters one last time after link is lost. */
			hw_priv->counter[i].read = 1;
		}
	}
}

static void link_read_work(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct dev_info *hw_priv =
		container_of(dwork, struct dev_info, link_read);
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port *port = NULL;
	int i;
	int changes = 0;

	sw->ops->acquire(sw);
	for (i = 0; i < sw->dev_count + sw->dev_offset; i++) {
		struct dev_priv *priv;
		struct net_device *dev = sw->netdev[i];

		if (dev) {
			priv = netdev_priv(dev);
			port = &priv->port;
		} else
			break;
		changes |= sw->ops->port_get_link_speed(port);
		update_link(dev, priv, port);
	}
	sw->ops->release(sw);

	/* Not to read PHY registers unnecessarily if no link change. */
	if (!changes)
		return;

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		for (i = 0; i < MAX_PTP_PORT; i++)
			ptp->linked[i] = (sw->port_info[i].state ==
				media_connected);
	}
#endif
}  /* link_read_work */

static void stp_work(struct work_struct *work)
{
#ifdef CONFIG_KSZ_STP
	struct delayed_work *dwork = to_delayed_work(work);
	struct dev_info *hw_priv =
		container_of(dwork, struct dev_info, stp_monitor);
	struct ksz_sw *sw = &hw_priv->sw;

	sw->net_ops->monitor_ports(sw);
#endif
}  /* stp_work */

/*
 * Hardware monitoring
 */

static void mib_monitor(unsigned long ptr)
{
	struct dev_info *hw_priv = (struct dev_info *) ptr;

	/* Timer routine is in interrupt context. */
	schedule_work(&hw_priv->mib_read);

	ksz_update_timer(&hw_priv->mib_timer_info);
}

static void dev_monitor(unsigned long ptr)
{
	struct dev_info *hw_priv = (struct dev_info *) ptr;

	if (!(hw_priv->sw.features & STP_SUPPORT))
		return;
	if (hw_priv->sw.features & STP_SUPPORT)
		schedule_delayed_work(&hw_priv->stp_monitor, 0);

	ksz_update_timer(&hw_priv->monitor_timer_info);
}  /* dev_monitor */

/* -------------------------------------------------------------------------- */

static ssize_t display_info(char *buf, ssize_t len)
{
	len += sprintf(buf + len, "duplex:\t\t");
	len += sprintf(buf + len, "0 for auto; ");
	len += sprintf(buf + len,
		"set to 1 for half-duplex; 2, full-duplex\n");
	len += sprintf(buf + len, "speed:\t\t");
	len += sprintf(buf + len,
		"0 for auto; set to 10 or 100\n");
	len += sprintf(buf + len, "force:\t\t");
	len += sprintf(buf + len,
		"set to 1 to force link to specific speed setting\n");
	len += sprintf(buf + len, "flow_ctrl:\t");
	len += sprintf(buf + len,
		"set to 0 to disable flow control\n");
	len += sprintf(buf + len, "mib:\t\t");
	len += sprintf(buf + len,
		"display the MIB table\n");
	return len;
}

static ssize_t net_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	ssize_t len = -EINVAL;
	int proc_num;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	len = 0;
	proc_num = offset / sizeof(int);
	switch (proc_num) {
	case PROC_SW_INFO:
		len = display_info(buf, len);
		break;
	case PROC_SET_SW_FEATURES:
		len += sprintf(buf + len, "%08x:\n", hw->features);
		break;
	case PROC_SET_SW_OVERRIDES:
		len += sprintf(buf + len, "%08x:\n", hw->overrides);
		len += sprintf(buf + len, "\t%08x = rx loopback\n",
			RX_LOOPBACK);
		len += sprintf(buf + len, "\t%08x = rx all\n",
			RX_ALL);
		len += sprintf(buf + len, "\t%08x = data header only\n",
			DATA_HEADER);
		break;
	}
	up(&hw_priv->proc_sem);
	return len;
}

static ssize_t net_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	ssize_t ret = -EINVAL;
	int changes;
	int num;
	int proc_num;

	if ('0' == buf[0] && 'x' == buf[1])
		sscanf(&buf[2], "%x", (unsigned int *) &num);
	else if ('0' == buf[0] && 'b' == buf[1]) {
		int i = 2;

		num = 0;
		while (buf[i]) {
			num <<= 1;
			num |= buf[i] - '0';
			i++;
		}
	} else if ('0' == buf[0] && 'd' == buf[1])
		sscanf(&buf[2], "%u", &num);
	else
		sscanf(buf, "%d", &num);
	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;
	mutex_lock(&hw_priv->lock);
	switch (proc_num) {
	case PROC_SET_SW_FEATURES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = hw->features ^ num;
		hw->features = num;
		break;
	case PROC_SET_SW_OVERRIDES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = hw->overrides ^ num;
		if ((changes & (RX_LOOPBACK |
				0)) &&
				hw_priv->opened) {
			printk(KERN_INFO "Stop device first\n");
			break;
		}
		hw->overrides = num;
		break;
	}
	mutex_unlock(&hw_priv->lock);
	up(&hw_priv->proc_sem);
	return ret;
}

/* generate a read-only attribute */
#define NET_RD_ENTRY(name)						\
static ssize_t show_##name(struct device *d,				\
	struct device_attribute *attr, char *buf)			\
{									\
	return net_show(d, attr, buf,					\
		offsetof(struct lan_attributes, name));			\
}									\
static DEVICE_ATTR(name, S_IRUGO, show_##name, NULL)

/* generate a write-able attribute */
#define NET_WR_ENTRY(name)						\
static ssize_t show_##name(struct device *d,				\
	struct device_attribute *attr, char *buf)			\
{									\
	return net_show(d, attr, buf,					\
		offsetof(struct lan_attributes, name));			\
}									\
static ssize_t store_##name(struct device *d,				\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return net_store(d, attr, buf, count,				\
		offsetof(struct lan_attributes, name));			\
}									\
static DEVICE_ATTR(name, S_IRUGO | S_IWUSR, show_##name, store_##name)

NET_RD_ENTRY(info);
NET_WR_ENTRY(features);
NET_WR_ENTRY(overrides);

static struct attribute *wan_attrs[] = {
	&lan_attr_duplex.attr,
	&lan_attr_speed.attr,
	&lan_attr_force.attr,
	&lan_attr_flow_ctrl.attr,
	&lan_attr_mib.attr,
	&dev_attr_info.attr,
	&dev_attr_features.attr,
	&dev_attr_overrides.attr,
	NULL
};

static struct attribute_group all_group = {
	.name  = "general",
	.attrs  = wan_attrs,
};

static void exit_sysfs(struct net_device *dev)
{
	sysfs_remove_group(&dev->dev.kobj, &all_group);
	sysfs_remove_bin_file(&dev->dev.kobj, &kszsw_registers_attr);
}

static int init_sysfs(struct net_device *dev)
{
	int err;

	err = sysfs_create_bin_file(&dev->dev.kobj, &kszsw_registers_attr);
	if (err)
		return err;
	err = sysfs_create_group(&dev->dev.kobj, &all_group);
	return err;
}

/* MII interface controls */

/**
 * ks_phy_reg - convert MII register into a KSZ846x register
 * @reg: MII register number.
 *
 * Return the KSZ846x register number for the corresponding MII PHY register
 * if possible. Return zero if the MII register has no direct mapping to the
 * KSZ846x register set.
 */
static int ks_phy_reg(int reg)
{
	switch (reg) {
	case MII_BMCR:
		return PHY_REG_CTRL;
	case MII_BMSR:
		return PHY_REG_STATUS;
	case MII_PHYSID1:
		return PHY_REG_ID_2;
	case MII_PHYSID2:
		return PHY_REG_ID_1;
	case MII_ADVERTISE:
		return PHY_REG_AUTO_NEGOTIATION;
	case MII_LPA:
		return PHY_REG_REMOTE_CAPABILITY;
	}

	return 0x0;
}

/**
 * ks_phy_read - MII interface PHY register read.
 * @netdev: The network device the PHY is on.
 * @phy_addr: Address of PHY (ignored as we only have one)
 * @reg: The register to read.
 *
 * This call reads data from the PHY register specified in @reg. Since the
 * device does not support all the MII registers, the non-existant values
 * are always returned as zero.
 *
 * We return zero for unsupported registers as the MII code does not check
 * the value returned for any error status, and simply returns it to the
 * caller. The mii-tool that the driver was tested with takes any -ve error
 * as real PHY capabilities, thus displaying incorrect data to the user.
 */
static int ks_phy_read(struct net_device *netdev, int phy_addr, int reg)
{
	struct ks_net *priv = netdev_priv(netdev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *ks = &hw_priv->hw;
	struct ksz_port *port = &priv->port;
	int ksreg;
	int result;

	ksreg = ks_phy_reg(reg);
	if (!ksreg)
		return 0x0;	/* no error return allowed, so use zero */

	ksreg += port->linked->port_id * 0xC;
	mutex_lock(&hw_priv->lock);
	result = ks_rdreg16(ks, ksreg);
	mutex_unlock(&hw_priv->lock);

	return result;
}

static void ks_phy_write(struct net_device *netdev, int phy, int reg,
	int value)
{
	struct ks_net *priv = netdev_priv(netdev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *ks = &hw_priv->hw;
	struct ksz_port *port = &priv->port;
	int ksreg;

	ksreg = ks_phy_reg(reg);
	if (ksreg) {
		ksreg += port->linked->port_id * 0xC;
		mutex_lock(&hw_priv->lock);
		ks_wrreg16(ks, ksreg, value);
		mutex_unlock(&hw_priv->lock);
	}
}

/**
 * ks_read_config - read chip configuration of bus width.
 * @ks: The chip information
 *
 */
static void ks_read_config(struct ksz_hw *ks)
{
	u16 reg_data = 0;

	/* Regardless of bus width, 8 bit read should always work.*/
	reg_data = ks_rdreg8(ks, KS_CCR) & 0x00FF;
	reg_data |= ks_rdreg8(ks, KS_CCR + 1) << 8;

	/* addr/data bus are multiplexed */
	ks->sharedbus = (reg_data & CCR_SHARED) == CCR_SHARED;

	/*
	 * There are garbage data when reading data from QMU,
	 * depending on bus-width.
	 */
	if (reg_data & CCR_8BIT) {
		ks->bus_width = ENUM_BUS_8BIT;
		ks->extra_byte = 1;
	} else if (reg_data & CCR_16BIT) {
		ks->bus_width = ENUM_BUS_16BIT;
		ks->extra_byte = 2;
	} else {
		ks->bus_width = ENUM_BUS_32BIT;
		ks->extra_byte = 4;
	}
}

/**
 * ks_soft_reset - issue one of the soft reset to the device
 * @hw:		The hardware instance.
 * @op:		The bit(s) to set in the GRR.
 *
 * Issue the relevant soft-reset command to the device's GRR register
 * specified by @op.
 *
 * Note, the delays are in there as a caution to ensure that the reset
 * has time to take effect and then complete. Since the datasheet does
 * not currently specify the exact sequence, we have chosen something
 * that seems to work with our device.
 */
static void ks_soft_reset(struct ksz_hw *hw, unsigned op)
{
	ks_wrreg16(hw, KS_GRR, op);
	udelay(10);	/* wait a short time to effect reset */
	ks_wrreg16(hw, KS_GRR, 0);
	udelay(1);	/* wait for condition to clear */
}

/**
 * ks_set_powermode - set power mode of the device
 * @hw:		The hardware instance.
 * @pwrmode:	The power mode value to write to KS_PMCTRL.
 *
 * Change the power mode of the chip.
 */
static void ks_set_powermode(struct ksz_hw *hw, unsigned pwrmode)
{
	unsigned pmecr;

	pmecr = ks_rdreg16(hw, KS_PMCTRL);
	pmecr &= ~PMCTRL_PM_MASK;
	pmecr |= pwrmode;
	ks_wrreg16(hw, KS_PMCTRL, pmecr);
}

static inline void ks_disable_int(struct ksz_hw *hw)
{
	ks_wrreg16(hw, KS_IER, 0x0000);
}  /* ks_disable_int */

static inline void ks_enable_int(struct ksz_hw *hw)
{
	ks_wrreg16(hw, KS_IER, hw->rc_ier & ~(IRQ_TS | IRQ_TRIG));
}  /* ks_enable_int */

#define TX_FIFO_TIMEOUT			8
#define TX_FIFO_TRIES			2

/**
 * ks_tx_fifo_space - return the available hardware buffer size.
 * @hw:		The hardware instance.
 *
 */
static u16 ks_tx_fifo_space(struct ksz_hw *hw)
{
	u16 data;
	int timeout = TX_FIFO_TIMEOUT;

	do {
		data = ks_rdreg16(hw, KS_TXMIR);
	} while (!data && --timeout);
	return data & 0x1fff;
}

/**
 * ks_start_rx - ready to serve pkts
 * @ks		: The chip information
 *
 */
static void ks_start_rx(struct ksz_hw *hw)
{
	/* Enable QMU Receive (RXCR1). */
	hw->rc_rxcr1 |= RXCR1_RXE;
	ks_wrreg16(hw, KS_RXCR1, hw->rc_rxcr1);
}  /* ks_start_rx */

/**
 * ks_stop_rx - stop to serve pkts
 * @ks		: The chip information
 *
 */
static void ks_stop_rx(struct ksz_hw *hw)
{
	/* Disable QMU Receive (RXCR1). */
	hw->rc_rxcr1 &= ~RXCR1_RXE;
	ks_wrreg16(hw, KS_RXCR1, hw->rc_rxcr1);
	udelay(1);
}  /* ks_stop_rx */

static void ks_read_mac(struct ksz_hw *hw, u8 *data)
{
	u16 w;
	u16 *pw = (u16 *) data;

	w = ks_rdreg16(hw, KS_MARH);
	*pw++ = htons(w);

	w = ks_rdreg16(hw, KS_MARM);
	*pw++ = htons(w);

	w = ks_rdreg16(hw, KS_MARL);
	*pw++ = htons(w);
}

/**
 * ks_set_mac - write mac address to device registers
 * @hw:		The hardware instance.
 * @data:	The MAC address.
 *
 * Update the KSZ8461/2 MAC address registers.
 */
static void ks_set_mac(struct ksz_hw *hw, u8 *data)
{
	u16 *pw = (u16 *) data;
	u16 u, w;

	u = *pw++;
	w = (u16)(((u & 0xFF) << 8) | ((u >> 8) & 0xFF));
	ks_wrreg16(hw, KS_MARH, w);

	u = *pw++;
	w = (u16)(((u & 0xFF) << 8) | ((u >> 8) & 0xFF));
	ks_wrreg16(hw, KS_MARM, w);

	u = *pw;
	w = (u16)(((u & 0xFF) << 8) | ((u >> 8) & 0xFF));
	ks_wrreg16(hw, KS_MARL, w);

	memcpy(hw->mac_addr, data, ETH_ALEN);
}

static void ks_enable_qmu(struct ksz_hw *hw)
{
	u16 w;

	/* Enable QMU Transmit (TXCR). */
	w = ks_rdreg16(hw, KS_TXCR);
	ks_wrreg16(hw, KS_TXCR, w | TXCR_TXE);

	/* Enable QMU Receive (RXCR1). */
	hw->rc_rxcr1 = ks_rdreg16(hw, KS_RXCR1);
	ks_start_rx(hw);

	hw->enabled = true;
}  /* ks_enable_qmu */

static void ks_disable_qmu(struct ksz_hw *hw)
{
	u16 w;

	/* Disable QMU Transmit (TXCR). */
	w = ks_rdreg16(hw, KS_TXCR);
	w &= ~TXCR_TXE;
	ks_wrreg16(hw, KS_TXCR, w);

	/* Disable QMU Receive (RXCR1). */
	hw->rc_rxcr1 = ks_rdreg16(hw, KS_RXCR1);
	ks_stop_rx(hw);

	hw->enabled = false;
}  /* ks_disable_qmu */

/**
 * ks_read_qmu - read 1 pkt data from the QMU.
 * @hw:		The hardware instance.
 * @buf:	Buffer address to save 1 pkt.
 * @len:	Pkt length.
 *
 * Here is the sequence to read 1 pkt:
 *	1. set pseudo DMA mode
 *	2. read prepend data
 *	3. read pkt data
 *	4. reset pseudo DMA Mode
 */
static inline void ks_read_qmu(struct ksz_hw *hw, void *buf, u32 len)
{
	u32 r = hw->extra_byte & 0x1;
	u32 w = hw->extra_byte - r;

	/* 1. set pseudo DMA mode */
	ks_wrreg16(hw, KS_RXFDPR, RXFDPR_RXFPAI);
	ks_wrreg8(hw, KS_RXQCR, (hw->rc_rxqcr | RXQCR_SDA) & 0xff);

	/* 2. read prepend data */
	/**
	 * read 4 + extra bytes and discard them.
	 * extra bytes for dummy, 2 for status, 2 for len
	 */

	/* use likely(r) for 8 bit access for performance */
	if (unlikely(r))
		ioread8(hw->hw_addr);
	ks_inblk(hw, buf, w + 2 + 2);

	/* 3. read pkt data */
	ks_inblk(hw, buf, ALIGN(len, 4));

	/* 4. reset pseudo DMA Mode */
	ks_wrreg8(hw, KS_RXQCR, hw->rc_rxqcr);
}

/**
 * ks_write_qmu - write 1 pkt data to the QMU.
 * @hw:		The hardware instance.
 * @pdata:	Buffer address to save 1 pkt.
 * @len:	Pkt length in byte.
 *
 * Here is the sequence to write 1 pkt:
 *	1. set pseudo DMA mode
 *	2. write status/length
 *	3. write pkt data
 *	4. reset pseudo DMA Mode
 *	5. enqueue pkt
 *	6. wait until pkt is out
 */
static void ks_write_qmu(struct ksz_hw *hw, void *pdata, u16 len)
{
	u8 fid = ++hw->fid;

	hw->fid &= (TXFID_INTR_DONE - 1);

	/* start header at txb[0] to align txw entries */
	hw->txh.txw[0] = 0;
	hw->txh.txw[0] = fid;
#ifdef USE_TX_DONE_INTR
	if (hw->tx_len < TX_DONE_MIN) {
		hw->txh.txw[0] |= TXFR_TXIC;
		hw->txh.txw[0] |= TXFID_INTR_DONE;
	}
#endif
	hw->txh.txw[1] = cpu_to_le16(len);

	/* 1. set pseudo-DMA mode */
	ks_wrreg8(hw, KS_RXQCR, (hw->rc_rxqcr | RXQCR_SDA) & 0xff);
	/* 2. write status/lenth info */
	ks_outblk(hw, hw->txh.txw, 4);
	/* 3. write pkt data */
	ks_outblk(hw, pdata, ALIGN(len, 4));
	/* 4. reset pseudo-DMA mode */
	ks_wrreg8(hw, KS_RXQCR, hw->rc_rxqcr);
	/* 5. Enqueue Tx(move the pkt from TX buffer into TXQ) */
	ks_wrreg16(hw, KS_TXQCR, TXQCR_METFE);
	/* 6. wait until TXQCR_METFE is auto-cleared */
	while (ks_rdreg16(hw, KS_TXQCR) & TXQCR_METFE)
		;
}

static int priv_promiscuous(void *ptr)
{
	struct ks_net *priv = ptr;

	return priv->promiscuous;
}  /* priv_promiscuous */

static int priv_match_multi(void *ptr, u8 *data)
{
	int i;
	struct ks_net *priv = ptr;
	int drop = false;

	if (priv->multi_list_size)
		drop = true;
	for (i = 0; i < priv->multi_list_size; i++)
		if (!memcmp(data, priv->multi_list[i], ETH_ALEN)) {
			drop = false;
			break;
		}
	return drop;
}  /* priv_match_multi */

static u8 get_priv_state(struct net_device *dev)
{
	struct ks_net *priv = netdev_priv(dev);

	return priv->state;
}  /* get_priv_state */

static void set_priv_state(struct net_device *dev, u8 state)
{
	struct ks_net *priv = netdev_priv(dev);

	priv->state = state;
}  /* set_priv_state */

static struct ksz_port *get_priv_port(struct net_device *dev)
{
	struct ks_net *priv = netdev_priv(dev);

	return &priv->port;
}  /* get_priv_port */

static u16 chk_rcv(struct ksz_hw *hw)
{
	u16 status;

	status = ks_rdreg16(hw, KS_ISR);
	status &= IRQ_RXI;
	if (status)
		ks_wrreg16(hw, KS_ISR, IRQ_RXI);
	return status;
}

static int chk_tcp(u8 *data)
{
	struct ethhdr *eth = (struct ethhdr *) data;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;
	struct iphdr *iph = NULL;
	struct ipv6hdr *ip6h = NULL;
	int ipv6;
	int tcp = 0;

	if (eth->h_proto == htons(ETH_P_8021Q)) {
		if (vlan->h_vlan_encapsulated_proto == htons(ETH_P_8021Q)) {
			unsigned char *ptr = (unsigned char *) vlan;

			ptr += VLAN_HLEN;
			vlan = (struct vlan_ethhdr *) ptr;
		}
		ipv6 = vlan->h_vlan_encapsulated_proto == htons(ETH_P_IPV6);
		if (vlan->h_vlan_encapsulated_proto != htons(ETH_P_IP) &&
				!ipv6)
			return 0;
		ip6h = (struct ipv6hdr *)(vlan + 1);
		iph = (struct iphdr *)(vlan + 1);
	} else {
		ipv6 = eth->h_proto == htons(ETH_P_IPV6);
		if (eth->h_proto != htons(ETH_P_IP) && !ipv6)
			return 0;
		ip6h = (struct ipv6hdr *)(eth + 1);
		iph = (struct iphdr *)(eth + 1);
	}
	if (ipv6) {
		if (IPPROTO_TCP == ip6h->nexthdr)
			tcp = 1;
		else if (IPPROTO_UDP == ip6h->nexthdr)
			tcp = 2;
		else if (IPPROTO_UDP == ip6h->nexthdr)
			tcp = 4;
		if (ip6h->nexthdr == NEXTHDR_FRAGMENT)
			tcp |= 0x8000;
	} else {
		int offset = ntohs(iph->frag_off);

		if (IPPROTO_TCP == iph->protocol)
			tcp = 1;
		else if (IPPROTO_UDP == iph->protocol)
			tcp = 2;
		else if (IPPROTO_ICMP == iph->protocol)
			tcp = 4;

		/* Not the first IP fragment. */
		if ((offset & IP_OFFSET))
			tcp |= 0x8000;
	}
	return tcp;
}

static int det_rcv_cnt(struct ksz_hw *hw, u8 *data, int len)
{
	int tcp = hw->rx_tcp;

	/* Using receive interrupt. */
	if (MAX_RECV_FRAMES == hw->rx_max) {
		if (hw->isr_jiffies != hw->rx_jiffies) {
			hw->rx_jiffies = hw->isr_jiffies;
			hw->rx_cnt = 0;
			hw->rx_cont = 0;
			hw->rx_fragment = 0;
			hw->rx_final = 0;
		} else
			++hw->rx_cnt;
		if (hw->rx_cnt >= 8) {

			/* Try to parse the packet to determine type. */
			if (tcp != 1 || ((hw->rx_cnt & 7) == 0)) {
				tcp = chk_tcp(data);
				hw->rx_tcp = tcp;
				if (2 == tcp) {

					/* Try to get number of fragments. */
					if (hw->rx_final < hw->rx_fragment)
						hw->rx_final = hw->rx_fragment;
					hw->rx_fragment = 0;
				} else if (tcp & 0x8000)
					++hw->rx_fragment;
			}
			if (1 == tcp)
				return tcp;

			hw->rx_cont += len;

			/* A condition of continual packet read is reached. */
			if (hw->rx_cont >= 1514 * 10) {

				/* Limit the read to this number. */
				hw->rx_max = hw->RX_MAX;

				if (2 != (tcp & 0xff))
					return tcp;

				/* Get the final fragment count. */
				if (hw->rx_final < hw->rx_fragment)
					hw->rx_final = hw->rx_fragment;

				/* Further reduce it if packet is short. */
				if (hw->rx_final < 3 && hw->rx_max)
					hw->rx_max--;
			}
		}
	}
	return tcp;
}

static int rx_proc(struct dev_info *hw_priv, struct sk_buff *skb,
	u16 sts, u32 len)
{
	struct net_device *parent_dev = NULL;
	struct sk_buff *parent_skb = NULL;
	struct net_device *dev = hw_priv->dev;
	struct ks_net *priv;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	unsigned long flags;
	int extra_skb;
	int forward = 0;
	int tcp = hw->rx_tcp;
	int rx_port = 0;
	int tag = 0;
	void *ptr = NULL;
	void (*rx_tstamp)(void *ptr, struct sk_buff *skb) = NULL;
#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp = &sw->ptp_hw;
	int ptp_tag = 0;
#endif

	priv = netdev_priv(dev);
	spin_lock_irqsave(&priv->statelock, flags);
#ifdef USE_2_BYTE_OFFSET
	ks_read_qmu(hw, skb->data, len);
	len -= 2;
	skb_reserve(skb, 2);
#else
	skb_reserve(skb, 2);

	/* read data block including CRC 4 bytes */
	ks_read_qmu(hw, skb->data, len);
#endif
	spin_unlock_irqrestore(&priv->statelock, flags);

	/* vlan_get_tag requires network device in socket buffer. */
	skb->dev = dev;
	if (sw_is_switch(sw)) {
		dev = sw->net_ops->rx_dev(sw, skb->data, &len, &tag, &rx_port);
		if (!dev) {
			dev_kfree_skb_irq(skb);
			return -ENODEV;
		}
	}
	priv = netdev_priv(dev);

	if (netif_msg_pktdata(priv)) {
		pr_info("rx: stat=0x%04x, len=0x%04x\n",
			sts, len);
		ks_dbg_dumpkkt(priv, skb->data, len, 0);
	}

	len -= 4;
	skb_put(skb, len);
	if (sw_is_switch(sw) && !sw->net_ops->match_pkt(sw, &dev,
			(void **) &priv, priv_promiscuous, priv_match_multi,
			skb, hw->promiscuous)) {
		dev_kfree_skb_irq(skb);
		return 0;
	}

#ifdef CONFIG_KSZ_STP
	if (sw_is_switch(sw) && sw->net_ops->stp_rx(sw, dev, skb, rx_port,
			&forward)) {
		if (!forward) {
			if (!sw->net_ops->blocked_rx(sw, skb->data))
				dbg_msg(
					"rxd%d=%02x:%02x:%02x:%02x:%02x:%02x\n",
					rx_port,
					skb->data[0], skb->data[1],
					skb->data[2], skb->data[3],
					skb->data[4], skb->data[5]);
			dev_kfree_skb_irq(skb);
			return 0;
		}
	}
#endif

#ifdef CONFIG_1588_PTP
	ptr = ptp;
	if ((sw->features & PTP_HW)) {
		if (ptp->ops->drop_pkt(ptp, skb, sw->vlan_id, &tag, &ptp_tag)) {
			dev_kfree_skb_irq(skb);
			return 0;
		}
		if (ptp_tag) {
			rx_tstamp = ptp->ops->get_rx_tstamp;
			if (!forward)
				forward = FWD_VLAN_DEV | FWD_MAIN_DEV;
		}
	}
#endif
	if (sw_is_switch(sw))
		dev = sw->net_ops->parent_rx(sw, dev, skb, forward,
			&parent_dev, &parent_skb);
	extra_skb = (parent_skb != NULL);

	/* Update receive statistics. */
	priv = netdev_priv(dev);
	priv->stats.rx_packets++;
	priv->stats.rx_bytes += len;

#ifdef KSZ_DLR
	if (sw_is_switch(sw)) {
		if (!sw->net_ops->drv_rx(sw, skb, rx_port))
			return 0;
	}
#endif
	if (sw_is_switch(sw))
		extra_skb |= sw->net_ops->port_vlan_rx(sw, dev, parent_dev,
			skb, forward, tag, ptr, rx_tstamp);
	if (!hw_priv->use_napi)
		tcp = det_rcv_cnt(hw, skb->data, len);
	skb->protocol = eth_type_trans(skb, dev);

	if (skb) {
		if (hw_priv->use_napi)
			netif_receive_skb(skb);
		else
			netif_rx(skb);
	}

	if (parent_skb) {
		struct dev_priv *parent_priv = netdev_priv(parent_dev);

		/* Update receive statistics. */
		parent_priv->stats.rx_packets++;
		parent_priv->stats.rx_bytes += len;

		/* Notify upper layer for received packet. */
		parent_dev->last_rx = jiffies;

#ifdef CONFIG_1588_PTP
		if (ptp_tag && (ptp->rx_en & 1))
			ptp->ops->get_rx_tstamp(ptp, parent_skb);
#endif
		parent_skb->protocol = eth_type_trans(parent_skb, parent_dev);
		if (hw_priv->use_napi)
			netif_receive_skb(parent_skb);
		else
			netif_rx(parent_skb);
	}
	return tcp;
}

/**
 * ks_rcv - read multiple pkts data from the QMU.
 * @hw:		The hardware instance.
 * @dev:	The network device being opened.
 *
 * Read all of header information before reading pkt content.
 * It is not allowed only port of pkts in QMU after issuing
 * interrupt ack.
 */
static int ks_rcv(struct dev_info *hw_priv)
{
	int i;
	struct ksz_hw *hw = &hw_priv->hw;
	struct type_frame_head *frame_hdr = hw->frame_head_info;
	struct sk_buff *skb;
	int num = 0;
	int cnt = 0;
	int tcp = hw->rx_tcp;
	int rx_max = hw->rx_max;

	/* Indicate this is not a continual read processing if empty. */
	int cont = hw->frame_cnt;

ks_rcv_begin:

	/* A new read procedure is started. */
	if (!hw->frame_cnt) {
		hw->frame_cnt = RXFC_GET(ks_rdreg16(hw, KS_RXFC));

		/* Remember the number of frames available. */
		hw->frame_max = hw->frame_cnt;

		/* read all header information */
		for (i = 0; i < hw->frame_cnt; i++) {
			/* Checking Received packet status */
			frame_hdr->sts = ks_rdreg16(hw, KS_RXFHSR);
			/* Get packet len from hardware */
			frame_hdr->len = ks_rdreg16(hw, KS_RXFHBCR);
			frame_hdr++;
		}
	}

	frame_hdr = hw->frame_head_info;
	frame_hdr = &hw->frame_head_info[hw->frame_max - hw->frame_cnt];
	while (hw->frame_cnt) {
		skb = dev_alloc_skb(frame_hdr->len + 16);
		if (likely(skb && !(frame_hdr->sts & RXFSHR_ERR) &&
				(frame_hdr->len < RX_BUF_SIZE) &&
				frame_hdr->len)) {
			tcp = rx_proc(hw_priv, skb, frame_hdr->sts,
				frame_hdr->len);
			if (tcp != 1)
				++cnt;
		} else {
			pr_err("%s: receive error frame or no skb! "
				"rx: stat=0x%04x, len=0x%04x, skb=%p\n",
				__func__, frame_hdr->sts, frame_hdr->len, skb);

			/* drop this error frame */
			ks_wrreg16(hw, KS_RXQCR, (hw->rc_rxqcr | RXQCR_RRXEF));

			if (skb)
				dev_kfree_skb_irq(skb);
		}
		num++;
		frame_hdr++;
		hw->frame_cnt--;

		/* Enough packets are processed. */
		if (cnt >= rx_max) {
			hw->rx_intr = IRQ_RXI;
			cont = 0;
			break;
		}
	}

	/* Try to see if there are new received packets. */
	if (cont && !hw->frame_cnt) {
		if (chk_rcv(hw)) {
			frame_hdr = hw->frame_head_info;
			goto ks_rcv_begin;
		}
	}
	if (!hw->frame_cnt)
		hw->rx_intr = 0;
	hw->rx_num = num;
	return num;
}

static void rx_proc_task(unsigned long data)
{
	struct dev_info *hw_priv = (struct dev_info *) data;
	struct ksz_hw *hw = &hw_priv->hw;
	struct net_device *dev = hw_priv->dev;
	u16 status = hw->rx_intr;

	if (!status)
		status = chk_rcv(hw);
	if (!status || unlikely(!ks_rcv(hw_priv))) {
		struct ks_net *priv = netdev_priv(dev);

		if (hw_priv->use_napi)
			napi_complete(&hw_priv->napi);
		spin_lock_irq(&priv->statelock);
		hw->rx_max = MAX_RECV_FRAMES;
		hw->rx_tcp = 0;
		hw->rc_ier |= IRQ_RXI;
		hw->rc_isr |= IRQ_RXI;
		ks_enable_int(hw);
		spin_unlock_irq(&priv->statelock);
	} else {
		if (!hw_priv->use_napi)
			tasklet_schedule(&hw_priv->rx_tasklet);
	}
}  /* rx_proc_task */

static int rx_napi_proc(struct napi_struct *napi, int budget)
{
	struct dev_info *ks = container_of(napi, struct dev_info, napi);
	struct ksz_hw *hw = &ks->hw;

	hw->rx_max = budget;
	hw->rx_num = 0;
	rx_proc_task((unsigned long) ks);
	return hw->rx_num;
}  /* rx_napi_poll */

static void tx_done(struct dev_info *hw_priv)
{
	struct ksz_sw *sw = &hw_priv->sw;

	hw_priv->hw.oper_state &= ~OPER_STATE_TX_PAUSED;
	if (sw_is_switch(sw))
		sw->net_ops->netdev_wake_queue(sw, hw_priv->dev);
	else
		netif_wake_queue(hw_priv->dev);
}  /* tx_done */

/**
 * ks_irq - device interrupt handler
 * @irq: Interrupt number passed from the IRQ hnalder.
 * @pw: The private word passed to register_irq(), our struct ks_net.
 *
 * This is the handler invoked to find out what happened
 *
 * Read the interrupt status, work out what needs to be done and then clear
 * any of the interrupts that are not needed.
 */
static irqreturn_t ks_irq(int irq, void *pw)
{
	struct dev_info *ks = pw;
	struct ksz_hw *hw = &ks->hw;
	u16 status;

	/* this should be the first in IRQ handler */
	ks_save_cmd_reg(hw);
	hw->isr_jiffies = jiffies;

	status = ks_rdreg16(hw, KS_ISR);
	status &= hw->rc_isr;
	ks_wrreg16(hw, KS_ISR, status);
	status &= hw->rc_ier;
	if (unlikely(!status)) {
		ks_restore_cmd_reg(hw);
		return IRQ_NONE;
	}

#ifdef CONFIG_1588_PTP
	if (likely(status & (IRQ_TS | IRQ_TRIG))) {
		struct ksz_sw *sw = &ks->sw;
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->ops->proc_intr(ptp);
	}
#endif

	if (likely(status & IRQ_RXI)) {
		if (ks->use_napi) {
			if (likely(napi_schedule_prep(&ks->napi))) {
				hw->rc_ier &= ~IRQ_RXI;
				hw->rc_isr &= ~IRQ_RXI;
				ks_enable_int(hw);
				hw->rx_intr = status;
				__napi_schedule(&ks->napi);
			}
		} else {

			/* Process received packets using receive interrupt. */
			if (MAX_RECV_FRAMES == hw->rx_max)
				ks_rcv(ks);
			else {
				hw->rc_ier &= ~IRQ_RXI;
				hw->rc_isr &= ~IRQ_RXI;
				ks_enable_int(hw);
				hw->rx_intr = status;
				hw->rx_cont = 0;
				hw->rx_tcp = 0;
				rx_proc_task((unsigned long) ks);
			}
		}
	}

#if defined(USE_TX_DONE_INTR)
	if (likely(status & IRQ_TXI)) {
		u16 fifo = ks_tx_fifo_space(hw);

		if (fifo >= 1520 * 3) {
			hw->tx_max = fifo;
			tx_done(ks);
		}
	}
#endif

#if defined(USE_TX_BUF_INTR)
	if (likely(status & IRQ_TXSAI)) {
		u16 data = ks_rdreg16(hw, KS_RXQCR);

		if ((data & ~RXQCR_STATUS) != hw->rc_rxqcr)
			ks_wrreg16(hw, KS_RXQCR, hw->rc_rxqcr);
		hw->rc_txqcr &= ~TXQCR_TXQMAM;
		hw->rc_qcr = (hw->rc_rxqcr << 16) | hw->rc_txqcr;
		tx_done(ks);
	}
#endif

	if (unlikely(status & IRQ_LCI))
		schedule_delayed_work(&ks->link_read, 0);

	if (unlikely(status & (IRQ_RXWFDI | IRQ_RXMPDI | IRQ_LDI | IRQ_EDI))) {
		u16 pmecr = ks_rdreg16(hw, KS_PMCTRL);

		pmecr &= ~PMCTRL_WKEVT_MASK;
		if (status & IRQ_RXWFDI)
			pmecr |= PMCTRL_WKEVT_FRAME;
		if (status & IRQ_RXMPDI)
			pmecr |= PMCTRL_WKEVT_MAGICPKT;
		if (status & IRQ_LDI)
			pmecr |= PMCTRL_WKEVT_LINK;
		if (status & IRQ_EDI)
			pmecr |= PMCTRL_WKEVT_ENERGY;
		ks_wrreg16(hw, KS_PMCTRL, pmecr);
		pmecr = ks_rdreg16(hw, KS_PME);
		pmecr &= ~PME_POLARITY;
		ks_wrreg16(hw, KS_PME, pmecr);
	}

	/* this should be the last in IRQ handler */
	ks_restore_cmd_reg(hw);
	return IRQ_HANDLED;
}

static int empty_addr(u8 *addr)
{
	u16 *addr1 = (u16 *) addr;
	u16 *addr2 = (u16 *) &addr[2];
	u16 *addr3 = (u16 *) &addr[4];

	return (0 == *addr1 && 0 == *addr2 && 0 == *addr3) ||
		(0xffff == *addr1 && 0xffff == *addr2 && 0xffff == *addr3);
}  /* empty_addr */

static int ks_hw_init(struct ksz_hw *hw)
{
	static u8 KS_DEFAULT_MAC_ADDRESS[] = {
		0x00, 0x10, 0xA1, 0x84, 0x62, 0x11 };

	/* cache the contents of the CCR register for EEPROM, etc. */
	hw->rc_ccr = ks_rdreg16(hw, KS_CCR);

	ks_read_mac(hw, hw->mac_addr);
	if (empty_addr(hw->mac_addr) || !is_valid_ether_addr(hw->mac_addr))
		ks_set_mac(hw, KS_DEFAULT_MAC_ADDRESS);
	return true;
}

static void ks_setup(struct ksz_hw *hw)
{
	u16 w;

	/* Setup flow control watermark. */
	ks_wrreg16(hw, KS_FCLWR, 0x800);

	/**
	 * Configure QMU Transmit
	 */

	/* Setup Transmit Frame Data Pointer Auto-Increment (TXFDPR) */
	ks_wrreg16(hw, KS_TXFDPR, TXFDPR_TXFPAI);

	/* Setup Receive Frame Data Pointer Auto-Increment */
	ks_wrreg16(hw, KS_RXFDPR, RXFDPR_RXFPAI);

	/* Setup Receive Frame Threshold - 1 frame */
	ks_wrreg16(hw, KS_RXFTR, 1 & RXFTR_MASK);

	/* Setup RxQ Command Control (RXQCR) */
	hw->rc_rxqcr = RXQCR_CMD_CNTL;
#ifdef USE_2_BYTE_OFFSET
	hw->rc_rxqcr |= RXQCR_RXIPHTOE;
#endif

	/* Adjust these settings for best performance. */
	ks_wrreg16(hw, KS_RXFTR, 3 & RXFTR_MASK);
	ks_wrreg16(hw, KS_RXDTTR, 1000);
	ks_wrreg16(hw, KS_RXDBCTR, 1518 * 2);
	hw->rc_rxqcr |= RXQCR_RXDTTE;
	hw->rc_rxqcr |= RXQCR_RXDBCTE;
	ks_wrreg16(hw, KS_RXQCR, hw->rc_rxqcr);
	hw->rc_txqcr = 0;
	hw->rc_qcr = (hw->rc_rxqcr << 16) | hw->rc_txqcr;

	w = TXCR_TXFCE | TXCR_TXPE | TXCR_TXCRC;
	ks_wrreg16(hw, KS_TXCR, w);

	w = RXCR1_RXFCE | RXCR1_RXBE | RXCR1_RXUE | RXCR1_RXME | RXCR1_RXIPFCC;

	if (hw->promiscuous)
		w |= (RXCR1_RXAE | RXCR1_RXINVF);
	else if (hw->all_mcast)
		/* Multicast address passed mode */
		w |= (RXCR1_RXAE | RXCR1_RXMAFMA | RXCR1_RXPAFMA);
	else
		/* Normal mode */
		w |= RXCR1_RXPAFMA;

	ks_wrreg16(hw, KS_RXCR1, w);
	hw->rc_rxcr1 = w;

	w = ks_rdreg16(hw, KS_RXCR2);
	w |= RXCR2_IUFFP;
	ks_wrreg16(hw, KS_RXCR2, w);
}  /* ks_setup */

static void ks_setup_int(struct ksz_hw *hw)
{
	hw->rc_ier = 0x00;

	/* Clear the interrupts status of the hardware. */
	ks_wrreg16(hw, KS_ISR, 0xffff);

	/* Enable the interrupts of the hardware. */
	hw->rc_ier = (IRQ_LCI | IRQ_RXI);
#ifdef CONFIG_1588_PTP
	/*
	 * PTP interrupts are always enabled by their own interrupt registers.
	 * It is not necessary to manually enable them in the main interrupt
	 * register.
	 */
	hw->rc_ier |= (IRQ_TS | IRQ_TRIG);
#endif
#ifdef USE_TX_DONE_INTR
	hw->rc_ier |= IRQ_TXI;
#endif
#ifdef USE_TX_BUF_INTR
	hw->rc_ier |= IRQ_TXSAI;
#endif
	hw->rc_ier |= IRQ_RXWFDI | IRQ_RXMPDI | IRQ_LDI | IRQ_EDI;
	hw->rc_isr = hw->rc_ier;
	hw->rc_isr |= (IRQ_RXOI | IRQ_RXPSI | IRQ_TXPSI);
}  /* ks_setup_int */

#ifdef CONFIG_NET_POLL_CONTROLLER
static void netdev_netpoll(struct net_device *dev)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	ks_disable_int(hw);
	ks_irq(dev->irq, hw_priv);
	ks_enable_int(hw);
}  /* netdev_netpoll */
#endif

static void reset_hw(struct dev_info *hw_priv, int complete)
{
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	int reset = false;

	if (sw_is_switch(sw))
		reset = sw->net_ops->stop(sw, complete);
#ifdef CONFIG_1588_PTP
	else if (complete && (sw->features & PTP_HW)) {
		struct ptp_info *ptp = &sw->ptp_hw;

		reset = ptp->ops->stop(ptp);
	}
#endif

	mutex_lock(&hw_priv->lock);
	if (!reset) {
		if (complete)
			ks_soft_reset(hw, GRR_GSR);
		else
			ks_soft_reset(hw, GRR_QMU);
	}
	mutex_unlock(&hw_priv->lock);
}  /* reset_hw */

static void start_hw(struct dev_info *ks, struct ksz_hw *hw)
{
	mutex_lock(&ks->lock);

	ks_wrreg16(hw, KS_ISR, 0xffff);
	ks_enable_int(hw);
	ks_enable_qmu(hw);
	hw->tx_max = ks_tx_fifo_space(hw);
	if (!hw->tx_max)
		hw->tx_max = 6144;
	hw->oper_state = 0;

	mutex_unlock(&ks->lock);

#ifdef CONFIG_1588_PTP
	do {
		struct ksz_sw *sw = &ks->sw;

		if ((sw->features & PTP_HW) && !sw_is_switch(sw)) {
			struct ptp_info *ptp = &sw->ptp_hw;

			ptp->reg->start(ptp, true);
		}
	} while (0);
#endif
}  /* start_hw */

#define	KS_INT_FLAGS	(IRQF_DISABLED | IRQF_TRIGGER_LOW)

static int netdev_open_before(struct net_device *dev, struct dev_priv *priv,
	struct dev_info *hw_priv, struct ksz_hw *hw)
{
	int err;
	struct ksz_sw *sw = &hw_priv->sw;

	hw->all_mcast = 0;
	hw->mcast_lst_size = hw->mcast_lst_reserved;

	mutex_lock(&hw_priv->lock);

	/* wake up powermode to normal mode */
	netif_dbg(priv, hw, dev, "setting power mode %d\n", PMCTRL_PM_NORMAL);
	ks_set_powermode(hw, PMCTRL_PM_NORMAL);

	/* wait for normal mode to take effect */
	mdelay(1);

	ks_disable_qmu(hw);
	if (hw->overrides & RX_LOOPBACK)
		hw->promiscuous++;
	ks_setup(hw);
	ks_setup_int(hw);
	mutex_unlock(&hw_priv->lock);

	/* Remember the network device that requests interrupts. */
	hw_priv->dev = dev;
	err = request_irq(dev->irq, ks_irq, KS_INT_FLAGS, DRV_NAME, hw_priv);
	if (err) {
		pr_err("Failed to request IRQ: %d: %d\n", dev->irq, err);
		return err;
	}
	tasklet_enable(&hw_priv->rx_tasklet);
	napi_enable(&hw_priv->napi);

	/* Default is to use receive interrupt. */
	hw->rx_max = MAX_RECV_FRAMES;

	mutex_lock(&hw_priv->lock);
	hw_add_wol_bcast(hw);
	mutex_unlock(&hw_priv->lock);

	if (sw_is_switch(sw))
		sw->net_ops->open_dev(sw, dev, hw->mac_addr);
	else {
		sw_init_mib(sw);
		sw_disable(sw);
	}
	return 0;
}  /* netdev_open_before */

/**
 * ks_net_open - open network device
 * @dev:	The network device being opened.
 *
 * Called when the network device is marked active, such as a user executing
 * 'ifconfig up' on the device.
 */
static int ks_net_open(struct net_device *dev)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port *port = &priv->port;
	int err;

	netif_dbg(priv, ifup, dev, "opening\n");
	priv->multicast = 0;
	priv->promiscuous = 0;

	/* Reset device statistics. */
	memset(&priv->stats, 0, sizeof(struct net_device_stats));

	if (!(hw_priv->opened)) {
		err = netdev_open_before(dev, priv, hw_priv, hw);
		if (err)
			return err;
	}
	sw->net_ops->open_port(sw, dev, &priv->port, &priv->state);

	if (!(hw_priv->opened)) {
		start_hw(hw_priv, hw);
		sw->net_ops->open(sw);
	}

	hw_priv->opened++;

	priv->media_state = port->linked->state;
	set_media_state(dev, media_connected);

	netif_start_queue(dev);

	netif_dbg(priv, ifup, dev, "network device up\n");
	netif_info(priv, ifup, dev, "up\n");

	return 0;
}

/**
 * ks_net_stop - close network device
 * @dev:	The device being closed.
 *
 * Called to close down a network device which has been active. Cancell any
 * work, shutdown the RX and TX process and then place the chip into a low
 * power state whilst it is not being used.
 */
static int ks_net_stop(struct net_device *dev)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;

	netif_info(priv, ifdown, dev, "shutting down\n");

	netif_stop_queue(dev);

	sw->net_ops->close_port(sw, dev, &priv->port);

	if (priv->multicast)
		--hw->all_mcast;
	if (priv->promiscuous)
		--hw->promiscuous;

	hw_priv->opened--;
	if (hw_priv->opened)
		return 0;

	sw->net_ops->close(sw);
	reset_hw(hw_priv, true);

	mutex_lock(&hw_priv->lock);

	/* turn off the IRQs and ack any outstanding */
	ks_wrreg16(hw, KS_IER, 0x0000);
	ks_wrreg16(hw, KS_ISR, 0xffff);

	/* shutdown RX/TX QMU */
	ks_disable_qmu(hw);

	/* set powermode to soft power down to save power */
	netif_dbg(priv, hw, dev, "setting power mode %d\n", PMCTRL_PM_SOFTDOWN);
	ks_set_powermode(hw, PMCTRL_PM_SOFTDOWN);

	mutex_unlock(&hw_priv->lock);

	napi_disable(&hw_priv->napi);
	tasklet_disable(&hw_priv->rx_tasklet);

	free_irq(dev->irq, hw_priv);
	return 0;
}

/**
 * Called in interrupt context.
 */
static void ks_tx_timeout(struct net_device *dev)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	if (hw_priv->hw.oper_state & OPER_STATE_TX_RESET)
		return;

	dbg_msg("tx timeout:%lx\n", jiffies);
	printk(KERN_DEBUG "tx timeout:%lx\n", jiffies);

	hw_priv->hw.oper_state |= OPER_STATE_TX_RESET;
	schedule_work(&hw_priv->tx_reset);
}

static void ks_tx_reset(struct work_struct *work)
{
	struct dev_info *ks = container_of(work, struct dev_info, tx_reset);
	struct ksz_hw *hw = &ks->hw;
	struct ksz_sw *sw = &ks->sw;

	reset_hw(ks, false);

	mutex_lock(&ks->lock);
	ks_setup(hw);
	mutex_unlock(&ks->lock);

	if (sw_is_switch(sw))
		sw->net_ops->start(sw, hw->mac_addr);
	else
		sw_disable(sw);

	sw->net_ops->netdev_open_port(sw, ks->dev);

	start_hw(ks, hw);

	if (sw_is_switch(sw))
		sw->net_ops->netdev_start_queue(sw, ks->dev);
	else {
		ks->dev->trans_start = jiffies;
		netif_start_queue(ks->dev);
	}

	schedule_work(&ks->rxctrl_work);
}

/**
 * ks_start_xmit - transmit packet
 * @skb:	The buffer to transmit
 * @dev:	The device used to transmit the packet.
 *
 * Called by the network layer to transmit the @skb.
 * spin_lock_irqsave is required because tx and rx should be mutual exclusive.
 * So while tx is in-progress, prevent IRQ interrupt from happenning.
 */
static int ks_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	unsigned long flags;
	int retv = NETDEV_TX_OK;
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	int len;

	if (sw_is_switch(sw)) {
		skb = sw->net_ops->check_tx(sw, dev, skb, &priv->port);
		if (!skb)
			return 0;
	}

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		if (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)
			ptp->ops->get_tx_tstamp(ptp, skb);
	}
#endif

/*
 * THa  2012/10/24
 * The formula of the packet length is (MTU + 14 - 2) / 8 * 8 + 2).
 * The formula of the required buffer is (ALIGN(len + 4), 4).
 * So the required buffer length can be (len + 4 + 2).
 *
 * Keep a minimum of 4 bytes in the buffer to easily detect the zero buffer
 * problem.
 */
	len = ALIGN(skb->len + 4, 4);
	spin_lock_irqsave(&priv->statelock, flags);
	ks_save_cmd_reg(hw);

	hw->tx_len = ks_tx_fifo_space(hw);
	if (likely(hw->tx_len - TX_BUF_MIN >= len)) {
		hw->tx_len -= len;
		hw->tx_max = hw->tx_len;
#ifdef USE_TX_DONE_INTR
		if (hw->tx_len < TX_DONE_MIN) {
			if (sw_is_switch(sw))
				sw->net_ops->netdev_stop_queue(sw, dev);
			else
				netif_stop_queue(dev);
			hw->oper_state |= OPER_STATE_TX_PAUSED;
		}
#endif
		ks_write_qmu(hw, skb->data, skb->len);
		if (netif_msg_pktdata(priv))
			ks_dbg_dumpkkt(priv, skb->data, skb->len, 1);

		/* Update transmit statistics. */
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += skb->len;

#ifdef CONFIG_1588_PTP
		/* Still waiting for tx timestamp. */
		if (skb_shinfo(skb)->tx_flags &	SKBTX_IN_PROGRESS)
			skb_shinfo(skb)->tx_flags &= ~SKBTX_HW_TSTAMP;
		else
#endif
		dev_kfree_skb(skb);
	} else {
		if (sw_is_switch(sw))
			sw->net_ops->netdev_stop_queue(sw, dev);
		else
			netif_stop_queue(dev);
		hw->oper_state |= OPER_STATE_TX_PAUSED;
#ifdef USE_TX_BUF_INTR
		hw->rc_txqcr = ks_rdreg16(hw, KS_TXQCR);

/*
 * THa  2012/10/04
 * The size requested is actually in multiple of 4 bytes.  Setting a larger
 * size actually has better transmit performance maybe due to not to process
 * too many interrupts.
 * In revisions C and older, setting a size more than 1568 will trigger the
 * 2-byte offset bit setting bug in the receive configuration register.
 */
		ks_wrreg16(hw, KS_TXNTFSR, (1520 * 3) / 4);
		hw->rc_txqcr |= TXQCR_TXQMAM;
		hw->rc_qcr = (hw->rc_rxqcr << 16) | hw->rc_txqcr;
		ks_wrreg16(hw, KS_TXQCR, hw->rc_txqcr);
#endif
		retv = NETDEV_TX_BUSY;
	}

	ks_restore_cmd_reg(hw);
	spin_unlock_irqrestore(&priv->statelock, flags);
	return retv;
}

static void set_multi_hash(u8 *addr, u16 *bits)
{
	int position;
	int index;
	int value;

	position = (ether_crc(6, addr) >> (32 - 6));
	index = position >> 4;
	value = 1 << (position & 0xf);
	bits[index] |= (u16) value;
}  /* set_multi_hash */

/**
 * ks_set_grpaddr - set multicast information
 * @hw:		The hardware instance.
 *
 * It is assumed the registers will be programmed in another routine.
 */
static void ks_set_grpaddr(struct ksz_hw *hw)
{
	u8 i;

	memset(hw->mcast_bits, 0, sizeof(u16) * HW_MCAST_SIZE);

	for (i = 0; i < hw->mcast_lst_size; i++)
		set_multi_hash(hw->mcast_lst[i], hw->mcast_bits);
}  /* ks_set_grpaddr */

/**
 * ks_clear_mcast - clear multicast information
 * @hw:		The hardware instance.
 *
 * This routine removes all mcast addresses set in the hardware.
 * It is assumed the registers will be programmed in another routine.
 */
static void ks_clear_mcast(struct ksz_hw *hw)
{
	int i;

	for (i = 0; i < HW_MCAST_SIZE; i++)
		hw->mcast_bits[i] = 0;
}

static void ks_set_promis(struct ksz_hw *hw, int promiscuous_mode)
{
	hw->rc_rxcr1 &= ~RXCR1_FILTER_MASK;
	if (promiscuous_mode)
		/* Enable Promiscuous mode */
		hw->rc_rxcr1 |= RXCR1_RXAE | RXCR1_RXINVF;
	else if (hw->all_mcast)
		/* Enable "Perfect with Multicast address passed mode" */
		hw->rc_rxcr1 |= (RXCR1_RXAE | RXCR1_RXMAFMA | RXCR1_RXPAFMA);
	else
		/* Disable Promiscuous mode (default normal mode) */
		hw->rc_rxcr1 |= RXCR1_RXPAFMA;
}  /* ks_set_promis */

static void ks_set_mcast(struct ksz_hw *hw, int mcast)
{
	if (hw->promiscuous)
		return;

	hw->rc_rxcr1 &= ~RXCR1_FILTER_MASK;
	if (mcast)
		/* Enable "Perfect with Multicast address passed mode" */
		hw->rc_rxcr1 |= (RXCR1_RXAE | RXCR1_RXMAFMA | RXCR1_RXPAFMA);
	else
		/**
		 * Disable "Perfect with Multicast address passed
		 * mode" (normal mode).
		 */
		hw->rc_rxcr1 |= RXCR1_RXPAFMA;
}  /* ks_set_mcast */

static void dev_set_promiscuous(struct net_device *dev, struct ks_net *priv,
	struct ksz_hw *hw, struct ksz_sw *sw, int promiscuous)
{
	if (promiscuous != priv->promiscuous) {
		u8 prev_state = hw->promiscuous;

		if (promiscuous)
			++hw->promiscuous;
		else
			--hw->promiscuous;
		priv->promiscuous = promiscuous;

		/* Turn on/off promiscuous mode. */
		if (hw->promiscuous <= 1 && prev_state <= 1)
			ks_set_promis(hw, hw->promiscuous);
	}
}

static void dev_set_multicast(struct ks_net *priv, struct ksz_hw *hw,
	int multicast)
{
	if (multicast != priv->multicast) {
		u8 all_mcast = hw->all_mcast;

		if (multicast)
			++hw->all_mcast;
		else
			--hw->all_mcast;
		priv->multicast = multicast;

		/* Turn on/off all multicast mode. */
		if (hw->all_mcast <= 1 && all_mcast <= 1)
			ks_set_mcast(hw, hw->all_mcast);
	}
}

/**
 * ks_rxctrl_work - work handler to change rx mode
 * @work: The work structure this belongs to.
 *
 * Lock the device and issue the necessary changes to the receive mode from
 * the network device layer. This is done so that we can do this without
 * having to sleep whilst holding the network device lock.
 *
 * Since the recommendation from Micrel is that the RXQ is shutdown whilst the
 * receive parameters are programmed, we issue a write to disable the RXQ and
 * then wait for the interrupt handler to be triggered once the RXQ shutdown is
 * complete. The interrupt handler then writes the new values into the chip.
 */
static void ks_rxctrl_work(struct work_struct *work)
{
	int i;
	struct dev_info *ks = container_of(work, struct dev_info, rxctrl_work);
	struct ksz_hw *hw = &ks->hw;

	mutex_lock(&ks->lock);

	/* Stop receiving for reconfiguration */
	ks_stop_rx(hw);

	for (i = 0; i < HW_MCAST_SIZE; i++)
		ks_wrreg16(hw, KS_MAHTR0 + i * 2, hw->mcast_bits[i]);
	ks_wrreg16(hw, KS_RXCR1, hw->rc_rxcr1);
	memcpy(&hw->rxctrl, hw->mcast_bits, sizeof(hw->mcast_bits));
	hw->rxctrl.rxcr1 = hw->rc_rxcr1;

	if (hw->enabled)
		ks_start_rx(hw);

	mutex_unlock(&ks->lock);
}

static void ks_set_rx_mode(struct net_device *dev)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *ks = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	int flags = dev->flags;
	int multicast = ((dev->flags & IFF_ALLMULTI) == IFF_ALLMULTI);

	/* Turn on/off promiscuous mode. */
	dev_set_promiscuous(dev, priv, ks, sw,
		((dev->flags & IFF_PROMISC) == IFF_PROMISC));

	/* Turn on/off all mcast mode. */
	if (sw->dev_count > 1) {
#ifdef CONFIG_KSZ_STP
		if ((flags & IFF_MULTICAST) && !netdev_mc_empty(dev))
			sw->net_ops->set_multi(sw, dev, &priv->port);
#endif
		priv->multi_list_size = 0;

		/* Do not update multi_list_size. */
		if (flags & IFF_ALLMULTI)
			flags &= ~IFF_MULTICAST;

		/* Turn on all multicast. */
		multicast |= ((dev->flags & IFF_MULTICAST) == IFF_MULTICAST);
	}
	dev_set_multicast(priv, ks, multicast);

	if ((flags & IFF_MULTICAST) && !netdev_mc_empty(dev)) {
		if (netdev_mc_count(dev) <= MAX_MCAST_LST) {
			int i = ks->mcast_lst_reserved;
			struct netdev_hw_addr *ha;

			if (i) {
				int j;

				for (j = 0; j < i; j++)
					memcpy(priv->multi_list[j],
						ks->mcast_lst[j], ETH_ALEN);
			}
			netdev_for_each_mc_addr(ha, dev) {
				if (!(*ha->addr & 1))
					continue;
				if (i >= MAX_MCAST_LST)
					break;
				memcpy(priv->multi_list[i], ha->addr, ETH_ALEN);
				memcpy(ks->mcast_lst[i++], ha->addr, ETH_ALEN);
			}
			priv->multi_list_size = (u8) i;
			ks->mcast_lst_size = (u8) i;
			ks_set_grpaddr(ks);
		} else {
			/**
			 * List too big to support so
			 * turn on all mcast mode.
			 */
			priv->multi_list_size = 0;
			ks->mcast_lst_size = MAX_MCAST_LST;
			ks_set_mcast(ks, true);
		}
	} else {
		priv->multi_list_size = ks->mcast_lst_reserved;
		ks->mcast_lst_size = ks->mcast_lst_reserved;
		if (!ks->mcast_lst_size)
			ks_clear_mcast(ks);
	}
	schedule_work(&hw_priv->rxctrl_work);
}  /* ks_set_rx_mode */

static int ks_set_mac_address(struct net_device *dev, void *addr)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct sockaddr *sa = addr;
	u8 *da;

	memcpy(dev->dev_addr, sa->sa_data, dev->addr_len);

	da = (u8 *) dev->dev_addr;

	ks_stop_rx(hw);  /* Stop receiving for reconfiguration */
	ks_set_mac(hw, dev->dev_addr);
	if (hw->enabled)
		ks_start_rx(hw);

	if (sw->info) {
		u8 promiscuous = hw->promiscuous;

		promiscuous = sw->net_ops->set_mac_addr(sw, dev, promiscuous,
			priv->port.first_port);
		if (promiscuous != hw->promiscuous) {
			hw->promiscuous = promiscuous;
			if (hw->promiscuous <= 1 && promiscuous <= 1)
				ks_set_promis(hw, hw->promiscuous);
		}
	}

#ifdef CONFIG_1588_PTP
	if ((sw->features & PTP_HW) && !sw_is_switch(sw)) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->ops->set_identity(ptp, hw->mac_addr);
	}
#endif
	return 0;
}

static int netdev_add_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;

	if ((sw->features & VLAN_PORT) && vid >= VLAN_PORT_START) {
		vid -= VLAN_PORT_START;
		if (vid <= SWITCH_PORT_NUM)
			sw->vlan_id |= (1 << vid);
	}
	return 0;
}

static int netdev_kill_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;

	if ((sw->features & VLAN_PORT) && vid >= VLAN_PORT_START) {
		vid -= VLAN_PORT_START;
		if (vid <= SWITCH_PORT_NUM)
			sw->vlan_id &= ~(1 << vid);
	}
	return 0;
}

/* RX errors = rx_errors */
/* RX dropped = rx_dropped */
/* RX overruns = rx_fifo_errors */
/* RX frame = rx_crc_errors + rx_frame_errors + rx_length_errors */
/* TX errors = tx_errors */
/* TX dropped = tx_dropped */
/* TX overruns = tx_fifo_errors */
/* TX carrier = tx_aborted_errors + tx_carrier_errors + tx_window_errors */
/* collisions = collisions */

/**
 * ks_net_query_statistics - query network device statistics
 * @dev:	Network device.
 *
 * This function returns the statistics of the network device.  The device
 * needs not be opened.
 *
 * Return network device statistics.
 */
static struct net_device_stats *ks_net_query_statistics(struct net_device *dev)
{
	struct ks_net *priv = netdev_priv(dev);
	struct ksz_port *port = &priv->port;
	struct ksz_sw *sw = &priv->adapter->sw;
	struct ksz_port_mib *mib;
	int i;
	int p;

	/* Reset to zero to add count later. */
	priv->stats.multicast = 0;
	priv->stats.collisions = 0;
	priv->stats.rx_length_errors = 0;
	priv->stats.rx_crc_errors = 0;
	priv->stats.rx_frame_errors = 0;
	priv->stats.tx_window_errors = 0;

	for (i = 0, p = port->first_port; i < port->mib_port_cnt; i++, p++) {
		mib = &sw->port_mib[p];

		priv->stats.multicast += (unsigned long)
			mib->counter[MIB_COUNTER_RX_MULTICAST];

		priv->stats.collisions += (unsigned long)
			mib->counter[MIB_COUNTER_TX_TOTAL_COLLISION];

		priv->stats.rx_length_errors += (unsigned long)(
			mib->counter[MIB_COUNTER_RX_UNDERSIZE] +
			mib->counter[MIB_COUNTER_RX_FRAGMENT] +
			mib->counter[MIB_COUNTER_RX_OVERSIZE] +
			mib->counter[MIB_COUNTER_RX_JABBER]);
		priv->stats.rx_crc_errors += (unsigned long)
			mib->counter[MIB_COUNTER_RX_CRC_ERR];
		priv->stats.rx_frame_errors += (unsigned long)(
			mib->counter[MIB_COUNTER_RX_ALIGNMENT_ERR] +
			mib->counter[MIB_COUNTER_RX_SYMBOL_ERR]);

		priv->stats.tx_window_errors += (unsigned long)
			mib->counter[MIB_COUNTER_TX_LATE_COLLISION];
	}

	return &priv->stats;
}

static int ks_net_ioctl(struct net_device *dev, struct ifreq *req, int cmd)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
#ifdef CONFIG_1588_PTP
	struct ksz_sw *sw = &hw_priv->sw;
	struct ptp_info *ptp = &sw->ptp_hw;
#endif
	int result = 0;

	if (!netif_running(dev))
		return -EINVAL;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	switch (cmd) {
#ifdef CONFIG_1588_PTP
	case SIOCSHWTSTAMP:
		result = -EOPNOTSUPP;
		if (sw->features & PTP_HW)
			result = ptp->ops->hwtstamp_ioctl(ptp, req);
		break;
	case SIOCDEVPRIVATE + 15:
		result = -EOPNOTSUPP;
		if (sw->features & PTP_HW)
			result = ptp->ops->dev_req(ptp, req->ifr_data,
				NULL);
		break;
#endif
	default:
#ifdef CONFIG_1588_PTP
		if (sw->features & PTP_HW) {
			result = ptp->ops->ixxat_ioctl(ptp, cmd, req);
			if (!result)
				break;
		}
#endif
		result = generic_mii_ioctl(&priv->mii_if, if_mii(req), cmd,
			NULL);
	}

	up(&hw_priv->proc_sem);

	return result;
}

/* ethtool support */

static void ks_get_drvinfo(struct net_device *dev,
	struct ethtool_drvinfo *di)
{
	strlcpy(di->driver, DRV_NAME, sizeof(di->driver));
	strlcpy(di->version, DRV_VERSION, sizeof(di->version));
	strlcpy(di->bus_info, dev_name(dev->dev.parent), sizeof(di->bus_info));
}

static u32 ks_get_msglevel(struct net_device *dev)
{
	struct ks_net *ks = netdev_priv(dev);
	return ks->msg_enable;
}

static void ks_set_msglevel(struct net_device *dev, u32 to)
{
	struct ks_net *ks = netdev_priv(dev);
	struct dev_info *hw_priv = ks->adapter;
	struct ksz_sw *sw = &hw_priv->sw;

	sw->msg_enable = to;
	ks->msg_enable = to;
}

static int ks_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct ks_net *ks = netdev_priv(dev);
	return mii_ethtool_gset(&ks->mii_if, cmd);
}

static int ks_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct ks_net *ks = netdev_priv(dev);
	return mii_ethtool_sset(&ks->mii_if, cmd);
}

static u32 ks_get_link(struct net_device *dev)
{
	struct ks_net *ks = netdev_priv(dev);
	return mii_link_ok(&ks->mii_if);
}

static int ks_nway_reset(struct net_device *dev)
{
	struct ks_net *ks = netdev_priv(dev);
	return mii_nway_restart(&ks->mii_if);
}

/**
 * ks_get_regs_len - get length of register dump
 * @dev:	Network device.
 *
 * This function returns the length of the register dump.
 *
 * Return length of the register dump.
 */
static int ks_get_regs_len(struct net_device *dev)
{
	struct hw_regs *range = hw_regs_range;
	int len;
	int num;
	int regs_len;

	regs_len = 0;
	while (range->end > range->start) {
		num = (range->end - range->start + 1) / 2;
		num = (num + 7) / 8;
		len = (8 * 5 + 6) * num;
		regs_len += len;
		range++;
	}
	return regs_len;
}  /* ks_get_regs_len */

/**
 * ks_get_regs - get register dump
 * @dev:	Network device.
 * @regs:	Ethtool registers data structure.
 * @ptr:	Buffer to store the register values.
 *
 * This procedure dumps the register values in the provided buffer.
 */
static void ks_get_regs(struct net_device *dev, struct ethtool_regs *regs,
	void *ptr)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	char *buf = ptr;
	struct hw_regs *range = hw_regs_range;
	int i;
	int len;
	int val;

	regs->version = 0;
	while (range->end > range->start) {
		len = range->start;
		while (len < range->end) {
			buf += sprintf(buf, "%04x:", len);
			for (i = 0; i < 8; i++, len += 2) {
				mutex_lock(&hw_priv->lock);
				val = ks_rdreg16(hw, len);
				mutex_unlock(&hw_priv->lock);
				buf += sprintf(buf, " %04x", val);
			}
			buf += sprintf(buf, "\n");
		}
		range++;
	}
}  /* ks_get_regs */

#define WOL_SUPPORT			\
	(WAKE_PHY | WAKE_MAGIC |	\
	WAKE_UCAST | WAKE_MCAST |	\
	WAKE_BCAST | WAKE_ARP)

/**
 * ks_get_wol - get Wake-on-LAN support
 * @dev:	Network device.
 * @wol:	Ethtool Wake-on-LAN data structure.
 *
 * This procedure returns Wake-on-LAN support.
 */
static void ks_get_wol(struct net_device *dev,
	struct ethtool_wolinfo *wol)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	wol->supported = hw_priv->wol_support;
	wol->wolopts = hw_priv->wol_enable;
	memset(&wol->sopass, 0, sizeof(wol->sopass));
}

/**
 * ks_set_wol - set Wake-on-LAN support
 * @dev:	Network device.
 * @wol:	Ethtool Wake-on-LAN data structure.
 *
 * This function sets Wake-on-LAN support.
 *
 * Return 0 if successful; otherwise an error code.
 */
static int ks_set_wol(struct net_device *dev,
	struct ethtool_wolinfo *wol)
{
	struct ks_net *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	/* Need to find a way to retrieve the device IP address. */
	u8 net_addr[] = { 192, 168, 1, 1 };

	if (wol->wolopts & ~hw_priv->wol_support)
		return -EINVAL;

	hw_priv->wol_enable = wol->wolopts;

	/* Link wakeup cannot really be disabled. */
	if (wol->wolopts)
		hw_priv->wol_enable |= WAKE_PHY;
	hw_enable_wol(&hw_priv->hw, hw_priv->wol_enable, net_addr);
	return 0;
}

static struct {
	char string[ETH_GSTRING_LEN];
} ethtool_stats_keys[TOTAL_SWITCH_COUNTER_NUM] = {
	{ "rx_lo_priority_octets" },
	{ "rx_hi_priority_octets" },
	{ "rx_undersize_packets" },
	{ "rx_fragments" },
	{ "rx_oversize_packets" },
	{ "rx_jabbers" },
	{ "rx_symbol_errors" },
	{ "rx_crc_errors" },
	{ "rx_align_errors" },
	{ "rx_mac_ctrl_packets" },
	{ "rx_pause_packets" },
	{ "rx_bcast_packets" },
	{ "rx_mcast_packets" },
	{ "rx_ucast_packets" },
	{ "rx_64_or_less_octet_packets" },
	{ "rx_65_to_127_octet_packets" },
	{ "rx_128_to_255_octet_packets" },
	{ "rx_256_to_511_octet_packets" },
	{ "rx_512_to_1023_octet_packets" },
	{ "rx_1024_to_1522_octet_packets" },

	{ "tx_lo_priority_octets" },
	{ "tx_hi_priority_octets" },
	{ "tx_late_collisions" },
	{ "tx_pause_packets" },
	{ "tx_bcast_packets" },
	{ "tx_mcast_packets" },
	{ "tx_ucast_packets" },
	{ "tx_deferred" },
	{ "tx_total_collisions" },
	{ "tx_excessive_collisions" },
	{ "tx_single_collisions" },
	{ "tx_mult_collisions" },

	{ "rx_discards" },
	{ "tx_discards" },
};

/**
 * ks_get_strings - get statistics identity strings
 * @dev:	Network device.
 * @stringset:	String set identifier.
 * @buf:	Buffer to store the strings.
 *
 * This procedure returns the strings used to identify the statistics.
 */
static void ks_get_strings(struct net_device *dev, u32 stringset, u8 *buf)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;

	if (ETH_SS_STATS == stringset)
		memcpy(buf, &ethtool_stats_keys,
			ETH_GSTRING_LEN * sw->mib_cnt);
}  /* ks_get_strings */

/**
 * ks_get_sset_count - get statistics size
 * @dev:	Network device.
 * @sset:	The statistics set number.
 *
 * This function returns the size of the statistics to be reported.
 *
 * Return size of the statistics to be reported.
 */
static int ks_get_sset_count(struct net_device *dev, int sset)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;

	switch (sset) {
	case ETH_SS_STATS:
		return sw->mib_cnt;
	default:
		return -EOPNOTSUPP;
	}
}

/**
 * ks_get_ethtool_stats - get network device statistics
 * @dev:	Network device.
 * @stats:	Ethtool statistics data structure.
 * @data:	Buffer to store the statistics.
 *
 * This procedure returns the statistics.
 */
static void ks_get_ethtool_stats(struct net_device *dev,
	struct ethtool_stats *stats, u64 *data)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port *port = &priv->port;
	int n_stats = stats->n_stats;
	int i;
	int n;
	int p;
	int rc;
	u64 counter[TOTAL_SWITCH_COUNTER_NUM];

	n = SWITCH_PORT_NUM;
	for (i = 0, p = port->first_port; i < port->mib_port_cnt; i++, p++) {
		if (media_connected == sw->port_state[p].state) {
			hw_priv->counter[p].read = 1;

			/* Remember first port that requests read. */
			if (n == SWITCH_PORT_NUM)
				n = p;
		}
	}

	if (n < SWITCH_PORT_NUM)
		schedule_work(&hw_priv->mib_read);

	if (1 == port->mib_port_cnt && n < SWITCH_PORT_NUM) {
		p = n;
		rc = wait_event_interruptible_timeout(
			hw_priv->counter[p].counter,
			2 == hw_priv->counter[p].read,
			HZ * 1);
	} else
		for (i = 0, p = n; i < port->mib_port_cnt - n; i++, p++) {
			if (0 == i) {
				rc = wait_event_interruptible_timeout(
					hw_priv->counter[p].counter,
					2 == hw_priv->counter[p].read,
					HZ * 2);
			} else if (sw->port_mib[p].cnt_ptr) {
				rc = wait_event_interruptible_timeout(
					hw_priv->counter[p].counter,
					2 == hw_priv->counter[p].read,
					HZ * 1);
			}
		}

	sw->ops->get_mib_counters(sw, port->first_port, port->mib_port_cnt,
		counter);
	n = sw->mib_cnt;
	if (n > n_stats)
		n = n_stats;
	n_stats -= n;
	for (i = 0; i < n; i++)
		*data++ = counter[i];
}  /* ks_get_ethtool_stats */

#define KS_EEPROM_MAGIC (0x00008462)

static int ks_set_eeprom(struct net_device *dev,
	struct ethtool_eeprom *ee, u8 *data)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *ks = priv->adapter;
	int offset = ee->offset;
	int len = ee->len;
	u16 tmp;

	/* currently only support byte writing */
	if (len != 1)
		return -EINVAL;

	if (ee->magic != KS_EEPROM_MAGIC)
		return -EINVAL;

	if (ks_eeprom_claim(ks))
		return -ENOENT;

	eeprom_93cx6_wren(&ks->eeprom, true);

	/* ethtool currently only supports writing bytes, which means
	 * we have to read/modify/write our 16bit EEPROMs */

	eeprom_93cx6_read(&ks->eeprom, offset/2, &tmp);

	if (offset & 1) {
		tmp &= 0xff;
		tmp |= *data << 8;
	} else {
		tmp &= 0xff00;
		tmp |= *data;
	}

	eeprom_93cx6_write(&ks->eeprom, offset/2, tmp);
	eeprom_93cx6_wren(&ks->eeprom, false);

	ks_eeprom_release(ks);

	return 0;
}

static int ks_get_eeprom(struct net_device *dev,
	struct ethtool_eeprom *ee, u8 *data)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *ks = priv->adapter;
	int offset = ee->offset;
	int len = ee->len;

	/* must be 2 byte aligned */
	if (len & 1 || offset & 1)
		return -EINVAL;

	if (ks_eeprom_claim(ks))
		return -ENOENT;

	ee->magic = KS_EEPROM_MAGIC;

	eeprom_93cx6_multiread(&ks->eeprom, offset/2, (__le16 *)data, len/2);
	ks_eeprom_release(ks);

	return 0;
}

static int ks_get_eeprom_len(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	/* currently, we assume it is an 93C46 attached, so return 128 */
	return hw->rc_ccr & CCR_EEPROM ? 128 : 0;
}

static const struct ethtool_ops ks_ethtool_ops = {
	.get_drvinfo		= ks_get_drvinfo,
	.get_regs_len		= ks_get_regs_len,
	.get_regs		= ks_get_regs,
	.get_wol		= ks_get_wol,
	.set_wol		= ks_set_wol,
	.get_msglevel		= ks_get_msglevel,
	.set_msglevel		= ks_set_msglevel,
	.get_settings		= ks_get_settings,
	.set_settings		= ks_set_settings,
	.get_link		= ks_get_link,
	.nway_reset		= ks_nway_reset,
	.get_strings		= ks_get_strings,
	.get_sset_count		= ks_get_sset_count,
	.get_ethtool_stats	= ks_get_ethtool_stats,
	.get_eeprom_len		= ks_get_eeprom_len,
	.get_eeprom		= ks_get_eeprom,
	.set_eeprom		= ks_set_eeprom,
};

/**
 * ks_read_selftest - read the selftest memory info.
 * @ks: The device state
 *
 * Read and check the TX/RX memory selftest information.
 */
static int ks_read_selftest(struct ksz_hw *ks)
{
	unsigned both_done = MBIR_TXMBF | MBIR_RXMBF;
	int ret = 0;
	int timeout = 10;
	unsigned rd;

	ks_wrreg16(ks, KS_GRR, GRR_BIST);
	do {
		rd = ks_rdreg16(ks, KS_MBIR);
		mdelay(1);
		--timeout;
	} while (!(rd & MBIR_DONE) && timeout);
	if ((rd & both_done) != both_done) {
		pr_warning("Memory selftest not finished\n");
		goto selftest_done;
	}

	if (rd & MBIR_TXMBFA) {
		pr_err("TX memory selftest fail: %u\n",
			(rd >> MBIR_TX_SHIFT) & MBIR_FAIL_CNT);
		ret |= 1;
	}

	if (rd & MBIR_RXMBFA) {
		pr_err("RX memory selftest fail: %u\n",
			(rd >> MBIR_RX_SHIFT) & MBIR_FAIL_CNT);
		ret |= 2;
	}

selftest_done:
	ks_wrreg16(ks, KS_GRR, 0);
	return ret;
}

/*
 * Linux network device interface functions
 */

/* Driver exported variables */

static int msg_enable;
static int napi;
static int rx_max = 2;
static int fiber;

static char *macaddr = ":";

static int netdev_init(struct net_device *netdev)
{
	struct ks_net *ks = netdev_priv(netdev);
	struct dev_info *hw_priv = ks->adapter;
	struct ksz_sw *sw = &hw_priv->sw;

	mutex_init(&ks->lock);
	spin_lock_init(&ks->statelock);

	netdev->watchdog_timeo = HZ;

	/* setup mii state */
	ks->mii_if.dev		= netdev;
	ks->mii_if.phy_id	= ks->port.first_port + 1;
	if (sw->dev_count > 1 && sw->dev_offset && ks->port.port_cnt != 1)
		ks->mii_if.phy_id = 0;
	ks->mii_if.phy_id_mask	= (1 << SWITCH_PORT_NUM) - 1;
	ks->mii_if.reg_num_mask	= 0xf;
	ks->mii_if.mdio_read	= ks_phy_read;
	ks->mii_if.mdio_write	= ks_phy_write;

	/* set the default message enable */
	ks->msg_enable = netif_msg_init(msg_enable, (NETIF_MSG_DRV |
						     NETIF_MSG_PROBE |
						     NETIF_MSG_LINK));
	sw->msg_enable = ks->msg_enable;
	return 0;
}

static const struct net_device_ops ks_netdev_ops = {
	.ndo_init		= netdev_init,
	.ndo_open		= ks_net_open,
	.ndo_stop		= ks_net_stop,
	.ndo_get_stats		= ks_net_query_statistics,
	.ndo_do_ioctl		= ks_net_ioctl,
	.ndo_start_xmit		= ks_start_xmit,
	.ndo_tx_timeout		= ks_tx_timeout,
	.ndo_set_mac_address	= ks_set_mac_address,
	.ndo_set_rx_mode	= ks_set_rx_mode,
	.ndo_change_mtu		= eth_change_mtu,
	.ndo_validate_addr	= eth_validate_addr,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller	= netdev_netpoll,
#endif
	.ndo_vlan_rx_add_vid	= netdev_add_vid,
	.ndo_vlan_rx_kill_vid	= netdev_kill_vid,
};

static void netdev_free(struct net_device *dev)
{
	exit_sysfs(dev);
	if (dev->watchdog_timeo)
		unregister_netdev(dev);

	free_netdev(dev);
}

struct platform_info {
	struct dev_info dev_info;
	struct net_device *netdev[TOTAL_PORT_NUM];
};

static int net_device_present;

static int ks846x_probe(struct platform_device *pdev)
{
	int err = -ENOMEM;
	int irq;
	struct resource *io_d, *io_c;
	struct net_device *netdev;
	struct ks_net *priv;
	struct dev_info *ks;
	struct platform_info *info;
	struct ksz_hw *hw;
	struct ksz_sw *sw;
	u16 id;
	int cnt;
	int i;
	int dev_count;
	char dev_name[IFNAMSIZ];
	int mib_port_count;
	int port_count;
	int ptp_ports;

	io_d = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	io_c = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	if (!request_mem_region(io_d->start, resource_size(io_d), DRV_NAME))
		goto err_mem_region_data;

	if (!request_mem_region(io_c->start, resource_size(io_c), DRV_NAME))
		goto err_mem_region_cmd;

	info = kzalloc(sizeof(struct platform_info), GFP_KERNEL);
	if (!info)
		goto err_devinfo;

	ks = &info->dev_info;
	ks->pdev = pdev;
	hw = &ks->hw;

	hw->hw_addr = ioremap(io_d->start, resource_size(io_d));
	if (!hw->hw_addr)
		goto err_ioremap_data;

	hw->hw_addr_cmd = ioremap(io_c->start, resource_size(io_c));
	if (!hw->hw_addr_cmd)
		goto err_ioremap_cmd;

	mutex_init(&ks->hwlock);
	mutex_init(&ks->lock);

	ks_read_config(hw);

	/* simple check for a valid chip being connected to the bus */
	id = ks_rdreg16(hw, KS_CIDER);
	if (((id & CIDER_ID_MASK) != CIDER_ID_8462) &&
			((id & CIDER_ID_MASK) != CIDER_ID_8441)) {
		dev_err(&pdev->dev, "failed to read device ID(0x%x,0x%x)\n",
			id, (id & CIDER_ID_MASK));
		err = -ENODEV;
		goto err_hw;
	}

#define	MHEADER_SIZE	(sizeof(struct type_frame_head) * MAX_RECV_FRAMES)
	hw->frame_head_info = (struct type_frame_head *)
		kmalloc(MHEADER_SIZE, GFP_KERNEL);
	if (!hw->frame_head_info) {
		dev_err(&pdev->dev, "Error: Fail to allocate frame memory\n");
		goto err_hw;
	}

	ks_read_selftest(hw);
	ks_soft_reset(hw, GRR_GSR);

	if (macaddr[0] != ':') {
		int n;
		unsigned int hex[6];
		u8 data[6];

		n = sscanf(macaddr, "%x:%x:%x:%x:%x:%x",
			&hex[0], &hex[1], &hex[2], &hex[3], &hex[4], &hex[5]);
		if (ETH_ALEN == n) {
			while (n > 0) {
				--n;
				data[n] = (u8) hex[n];
			}
			ks_set_mac(hw, data);
		}
	}

	ks_hw_init(hw);

	ks->eeprom.data = hw;
	ks->eeprom.width = PCI_EEPROM_WIDTH_93C46;
	ks->eeprom.register_read = ks_eeprom_regread;
	ks->eeprom.register_write = ks_eeprom_regwrite;

	dev_info(&pdev->dev,
		"Found chip, family: 0x%x, id: 0x%x, rev: 0x%x, irq: %d\n",
		(id >> 8) & 0xff, (id >> 4) & 0xf, (id >> 1) & 0x7, irq);

	if ((id & CIDER_ID_MASK) == CIDER_ID_8462)
		cnt = 2;
	else
		cnt = 1;
	ptp_ports = cnt;
	sw = &ks->sw;
	mutex_init(&sw->lock);
	sw->hwlock = &ks->hwlock;
	sw->reglock = &ks->lock;

	/* Assume device has only one port. */
	sw->dev_count = 1;
	dev_count = 1;
	port_count = 1;
	mib_port_count = 1;

	sw->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;
	sw->mib_port_cnt = 1;

	sw->dev = hw;
	sw->id = net_device_present;

	if (1 == ptp_ports)
		multi_dev = stp = 0;
	sw->multi_dev |= multi_dev;
	sw->stp |= stp;
	sw->fast_aging |= fast_aging;

	sw->reg = &sw_reg_ops;
	sw->net_ops = &sw_net_ops;
	sw->ops = &sw_ops;

	sw->net_ops->get_state = get_priv_state;
	sw->net_ops->set_state = set_priv_state;
	sw->net_ops->get_priv_port = get_priv_port;

	/* Device has a switch with multiple ports. */
	if (2 == cnt) {
		sw->net_ops->setup_special(sw, &port_count, &mib_port_count,
			&dev_count);
		sw->mib_port_cnt = TOTAL_PORT_NUM;
		sw->info = kzalloc(sizeof(struct ksz_sw_info), GFP_KERNEL);
		if (!sw->info) {
			err = -ENOMEM;
			goto err_frame_head;
		}
	}
	sw->port_cnt = sw->mib_port_cnt;
	sw->PORT_MASK = (1 << TOTAL_PORT_NUM) - 1;
	sw->HOST_PORT = SWITCH_PORT_NUM;
	sw->HOST_MASK = (1 << sw->HOST_PORT);

	init_waitqueue_head(&sw->queue);

	INIT_DELAYED_WORK(&ks->link_read, link_read_work);
	INIT_DELAYED_WORK(&ks->stp_monitor, stp_work);

	sw->counter = ks->counter;
	sw->monitor_timer_info = &ks->monitor_timer_info;
	sw->link_read = &ks->link_read;
	sw->stp_monitor = &ks->stp_monitor;

	sw_init_mib(sw);

	for (i = 0; i < cnt; i++) {
		if (fiber & (1 << i))
			sw->port_info[i].fiber = true;
	}

	/* tasklet is enabled. */
	tasklet_init(&ks->rx_tasklet, rx_proc_task,
		(unsigned long) ks);

	/* tasklet_enable will decrement the atomic counter. */
	tasklet_disable(&ks->rx_tasklet);

	for (i = 0; i < TOTAL_PORT_NUM; i++)
		init_waitqueue_head(&ks->counter[i].counter);

	dev_create_debugfs(ks);

	sw->ops->acquire(sw);
	if (sw->info) {
		sw_init(sw);
		sw_setup(sw);
	} else
		sw_disable(sw);
	sw->ops->release(sw);

	ks->wol_support = WOL_SUPPORT;
	ks->wol_enable = 0;

	for (i = 0; i < dev_count; i++) {
		netdev = alloc_etherdev(sizeof(struct ks_net));
		if (!netdev)
			goto err_register;
		info->netdev[i] = netdev;

		SET_NETDEV_DEV(netdev, &pdev->dev);

		priv = netdev_priv(netdev);
		priv->netdev = netdev;
		priv->dev = &pdev->dev;
		priv->adapter = ks;
		priv->id = net_device_present;

		sw->net_ops->setup_dev(sw, netdev, dev_name, &priv->port, i,
			port_count, mib_port_count);

		netdev->mem_start = (unsigned long) hw->hw_addr;
		netdev->mem_end = netdev->mem_start + 0x20 - 1;
		netdev->irq = irq;
		memcpy(netdev->dev_addr, hw->mac_addr, ETH_ALEN);

		netdev->netdev_ops = &ks_netdev_ops;
		netdev->ethtool_ops = &ks_ethtool_ops;

		err = register_netdev(netdev);
		if (err)
			goto err_register;
		err = init_sysfs(netdev);
		if (err)
			goto err_register;
		net_device_present++;

		/* Save the base device name. */
		if (!i)
			strlcpy(dev_name, netdev->name, IFNAMSIZ);
	}
	sema_init(&ks->proc_sem, 1);
	if (TOTAL_PORT_NUM == sw->mib_port_cnt) {
		err = init_sw_sysfs(sw, &ks->sysfs, &info->netdev[0]->dev);
		if (err)
			goto err_register;
	}
	netdev = info->netdev[0];

	if (rx_max < 1)
		rx_max = 1;
	hw->RX_MAX = rx_max;
	ks->use_napi = napi;
	netif_napi_add(netdev, &ks->napi, rx_napi_proc, rx_max);

#ifdef CONFIG_1588_PTP
	err = init_ptp_sysfs(&ks->ptp_sysfs, &info->netdev[0]->dev);
	if (err)
		goto err_register;
	sw->features |= PTP_HW;
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->reg = &ptp_reg_ops;
		ptp->ops = &ptp_ops;
		ptp->parent = &pdev->dev;

#ifdef CONFIG_ARCH_MICREL_PEGASUS
		ptp->get_clk_cnt = get_clk_cnt;
		ptp->clk_divider = ksz_system_bus_clock;
#endif
		ptp->ops->init(ptp, hw->mac_addr);
		ptp->ports = ptp_ports;
		if (ptp->version < 1)
			sw->features &= ~VLAN_PORT_REMOVE_TAG;
	}
#endif
#ifdef KSZ_DLR
	ksz_dlr_init(&sw->info->dlr, sw);
	err = init_dlr_sysfs(&info->netdev[0]->dev);
	hw->mcast_lst_reserved = 5;
	for (i = 0; i < hw->mcast_lst_reserved; i++) {
		hw->mcast_lst[i][0] = 0x01;
		hw->mcast_lst[i][1] = 0x21;
		hw->mcast_lst[i][2] = 0x6C;
		hw->mcast_lst[i][3] = 0x00;
		hw->mcast_lst[i][4] = 0x00;
		hw->mcast_lst[i][5] = i + 1;
	}
#endif

	INIT_WORK(&ks->rxctrl_work, ks_rxctrl_work);

	INIT_WORK(&ks->mib_read, mib_read_work);

	/* 500 ms timeout */
	ksz_init_timer(&ks->mib_timer_info, 500 * HZ / 1000,
		mib_monitor, ks);
	ksz_init_timer(&ks->monitor_timer_info, 100 * HZ / 1000,
		dev_monitor, ks);

	ksz_start_timer(&ks->mib_timer_info, ks->mib_timer_info.period);

	INIT_WORK(&ks->tx_reset, ks_tx_reset);

	platform_set_drvdata(pdev, info);
	return 0;

err_register:
	for (i = 0; i < sw->dev_count; i++) {
		if (info->netdev[i]) {
			netdev_free(info->netdev[i]);
			info->netdev[i] = NULL;
			sw->netdev[i] = NULL;
		}
	}
	kfree(sw->info);

err_frame_head:
	kfree(hw->frame_head_info);

err_hw:
	iounmap(hw->hw_addr_cmd);

err_ioremap_cmd:
	iounmap(hw->hw_addr);

err_ioremap_data:
	kfree(info);

err_devinfo:
	release_mem_region(io_c->start, resource_size(io_c));

err_mem_region_cmd:
	release_mem_region(io_d->start, resource_size(io_d));

err_mem_region_data:
	return err;
}

static int ks846x_remove(struct platform_device *pdev)
{
	int i;
	struct resource *iomem;
	struct platform_info *info = platform_get_drvdata(pdev);
	struct dev_info *ks = &info->dev_info;
	struct ksz_hw *hw = &ks->hw;
	struct ksz_sw *sw = &ks->sw;

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		exit_ptp_sysfs(&ks->ptp_sysfs, &info->netdev[0]->dev);
		ptp->ops->exit(ptp);
	}
#endif
#ifdef KSZ_DLR
	exit_dlr_sysfs(&info->netdev[0]->dev);
	ksz_dlr_exit(&sw->info->dlr);
#endif

	ksz_stop_timer(&ks->mib_timer_info);
	flush_work(&ks->mib_read);

	iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(iomem->start, resource_size(iomem));
	iomem = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	release_mem_region(iomem->start, resource_size(iomem));
	if (TOTAL_PORT_NUM == sw->mib_port_cnt)
		exit_sw_sysfs(sw, &ks->sysfs, &info->netdev[0]->dev);
	for (i = 0; i < sw->dev_count + sw->dev_offset; i++) {
		if (info->netdev[i])
			netdev_free(info->netdev[i]);
	}
	if (hw->hw_addr_cmd)
		iounmap(hw->hw_addr_cmd);
	if (hw->hw_addr)
		iounmap(hw->hw_addr);
	kfree(hw->frame_head_info);
	kfree(sw->info);
	dev_delete_debugfs(ks);
	platform_set_drvdata(pdev, NULL);
	kfree(info);

	return 0;
}

static int netdev_resume(struct platform_device *pdev)
{
	int i;
	struct net_device *dev;
	struct platform_info *info = platform_get_drvdata(pdev);
	struct dev_info *hw_priv = &info->dev_info;
	struct ksz_sw *sw = &hw_priv->sw;

	for (i = 0; i < sw->dev_count + sw->dev_offset; i++) {
		dev = info->netdev[i];
		if (dev && netif_running(dev)) {
			ks_net_open(dev);
			netif_device_attach(dev);
		}
	}
	return 0;
}  /* netdev_resume */

static int netdev_suspend(struct platform_device *pdev, pm_message_t state)
{
	int i;
	struct net_device *dev;
	struct platform_info *info = platform_get_drvdata(pdev);
	struct dev_info *hw_priv = &info->dev_info;
	struct ksz_sw *sw = &hw_priv->sw;

	for (i = 0; i < sw->dev_count + sw->dev_offset; i++) {
		dev = info->netdev[i];
		if (dev && netif_running(dev)) {
			netif_device_detach(dev);
			ks_net_stop(dev);
		}
	}
	return 0;
}  /* netdev_suspend */

static void netdev_shutdown(struct platform_device *pdev)
{
	int i;
	struct net_device *dev;
	struct platform_info *info = platform_get_drvdata(pdev);
	struct dev_info *hw_priv = &info->dev_info;
	struct ksz_sw *sw = &hw_priv->sw;

	for (i = 0; i < sw->dev_count + sw->dev_offset; i++) {
		dev = info->netdev[i];
		if (dev && netif_running(dev)) {
			netif_device_detach(dev);
			ks_net_stop(dev);
		}
	}
}  /* netdev_shutdown */

static struct platform_driver ks846x_platform_driver = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
	.probe = ks846x_probe,
	.remove = ks846x_remove,
	.suspend = netdev_suspend,
	.resume = netdev_resume,
	.shutdown = netdev_shutdown,
};

static int __init ksz8462_hli_init(void)
{
#ifdef DEBUG_MSG
	if (init_dbg())
		return -ENOMEM;
#endif
	return platform_driver_register(&ks846x_platform_driver);
}

static void __exit ksz8462_hli_exit(void)
{
	platform_driver_unregister(&ks846x_platform_driver);
#ifdef DEBUG_MSG
	exit_dbg();
#endif
}

module_init(ksz8462_hli_init);
module_exit(ksz8462_hli_exit);

MODULE_DESCRIPTION("Micrel KSZ8462 HLI Network Driver");
MODULE_AUTHOR("Tristram Ha <tristram.ha@microchip.com>");
MODULE_LICENSE("GPL");

module_param_named(message, msg_enable, int, 0);
MODULE_PARM_DESC(message, "Message verbosity level (0=none, 31=all)");

module_param(napi, int, 0);
MODULE_PARM_DESC(napi, "Use NAPI");
module_param(rx_max, int, 0);
MODULE_PARM_DESC(rx_max, "Specify maximum non-TCP receive packets");

module_param(fiber, int, 0);
MODULE_PARM_DESC(fiber, "Use fiber in ports");

module_param(macaddr, charp, 0);
module_param(fast_aging, int, 0);
module_param(multi_dev, int, 0);
module_param(stp, int, 0);
MODULE_PARM_DESC(macaddr, "MAC address");
MODULE_PARM_DESC(fast_aging, "Fast aging");
MODULE_PARM_DESC(multi_dev, "Multiple device interfaces");
MODULE_PARM_DESC(stp, "STP support");
