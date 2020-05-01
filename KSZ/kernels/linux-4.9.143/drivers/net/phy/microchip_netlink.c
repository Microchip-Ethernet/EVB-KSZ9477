/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */

#include <linux/bitmap.h>
#include <linux/rtnetlink.h>
#include <net/sock.h>
#include <linux/phy.h>
#include <linux/netdevice.h>
#include <net/genetlink.h>
#include <net/sock.h>
#include <linux/version.h>

#pragma pack(1)

#define		MDIO_CONTRL1			0x0F;
#define 	MDIO_CONTRL2			0x10
#define 	MODE_STATUS				0x11
#define		LOOPBACK_CTRL			0x12
#define 	RESET_CONTROL			0x13
#define		EXT_REG_CTRL			0x14
#define	  EXT_REG_RD_DATA		0x15
#define   EXT_REG_WR_DATA		0x16
#define 	PCS_CTRL					0x17
#define 	INT_SOURCE				0x18
#define		INT_MASK					0x19
#define		POWER_DOWN				0x1A

typedef union{
	struct{
		unsigned short reg_addr		:8;
		unsigned short bank_access	:3;
		unsigned short write				:1;
		unsigned short read				:1;
		unsigned short reserved		:2;
		unsigned short count_reset :1;		
	}s;
	unsigned short extphyctrl;	
}EXTPHYCTRL;

/* genetlink setup */
enum {
	PHYNL_CMD_NOOP,
	PHYNL_CMD_EVENT,		/* only for notifications */

	PHYNL_CMD_RDWR_REG, //PHYNL_CMD_WAKE,
	PHYNL_CMD_SLEEP,

	__PHYNL_CMD_CNT,
	PHYNL_CMD_MAX = (__PHYNL_CMD_CNT - 1)
};

enum {
	PHYNL_ATTR_NOOP,
	PHYNL_ATTR_REGACCESS,//WAKE_ATTR_PHYACCESS,		/* phyaccess nested types */
	WAKE_ATTR_NOTIFICATION,
	__PHYNL_ATTR_CNT,
	PHYNL_ATTR_MAX = (__PHYNL_ATTR_CNT - 1)
};

/* phyaccess nested types */
#define	PHYACC_ATTR_MODE_READ		0
#define	PHYACC_ATTR_MODE_WRITE		1

#define	PHYACC_ATTR_BANK_SMI		0
#define	PHYACC_ATTR_BANK_MISC		1
#define	PHYACC_ATTR_BANK_PCS		2
#define	PHYACC_ATTR_BANK_AFE		3
#define	PHYACC_ATTR_BANK_DSP		4
#define	PHYACC_ATTR_BANK_INSTRUMENT	5

enum {
	PHYACC_ATTR_NOOP,
	PHYACC_ATTR_IFNAME,
	PHYACC_ATTR_MODE,
	PHYACC_ATTR_BANK_ADDR,
	PHYACC_ATTR_OFFSET_ADDR,
	PHYACC_ATTR_VAL,

	__PHYACC_ATTR_CNT,
	PHYACC_ATTR_MAX = (__PHYACC_ATTR_CNT - 1)
};

#define	WAKENOTI_ATTR_STATUS_OK		0
#define	WAKENOTI_ATTR_STATUS_ABORT	1
#define	WAKENOTI_ATTR_STATUS_FAILURE	2

enum {
	WAKENOTI_ATTR_NOOP,
	WAKENOTI_ATTR_STATUS,

	__WAKENOTI_ATTR_CNT,
	WAKENOTI_ATTR_MAX = (__WAKENOTI_ATTR_CNT - 1)
};
static const struct nla_policy phy_rdwr_policy/*phy_wake_policy*/[PHYNL_ATTR_MAX+1] = {
	[PHYNL_ATTR_REGACCESS/*WAKE_ATTR_PHYACCESS*/]		= { .type = NLA_NESTED },
};

static const struct nla_policy phy_acc_policy[PHYACC_ATTR_MAX + 1] = {
	[PHYACC_ATTR_IFNAME] 		= { .type = NLA_STRING },
	[PHYACC_ATTR_MODE]		= { .type = NLA_U8 },
	[PHYACC_ATTR_BANK_ADDR]		= { .type = NLA_U8 },
	[PHYACC_ATTR_OFFSET_ADDR]	= { .type = NLA_U16 },
	[PHYACC_ATTR_VAL] 		= { .type = NLA_U16 },
};

extern struct genl_family microchipphy_genl_family;

static struct phy_device *phydev;
static struct phy_driver *phydriver;

static int do_phy_read(struct phy_device *phydev, unsigned short phybank, unsigned short phyaddr)
{
	int val;
  EXTPHYCTRL extctrl;
				
	/* do phy read
	 * For now, SMI access only.
	 */
	if (!phydev)
		return -EINVAL;

	if (phybank == PHYACC_ATTR_BANK_SMI) {
		val = phy_read(phydev, phyaddr);	
	}
  else {
  		extctrl.extphyctrl=0;
			extctrl.s.reg_addr=phyaddr;
			extctrl.s.bank_access=phybank;
			extctrl.s.read=1;
			phy_write(phydev,EXT_REG_CTRL,extctrl.extphyctrl);
			val=phy_read(phydev,EXT_REG_RD_DATA);
		   //printk("readbank extctrl=0x%x v=0x%x\n",extctrl.extphyctrl,val);
	
	}
	return val;
}

static void do_phy_write(struct phy_device *phydev, unsigned short phybank, unsigned short phyaddr, int phyval)
{
	EXTPHYCTRL extctrl;
	/* do phy write
	 * For now, SMI access only.
	 */
	if (!phydev)
		return;

	if (phybank == PHYACC_ATTR_BANK_SMI) {
		phy_write(phydev, phyaddr, (u16)phyval);
	}
	else {
		extctrl.extphyctrl=0;
		extctrl.s.reg_addr=phyaddr;
		extctrl.s.bank_access=phybank;
		extctrl.s.write=1;
		phy_write(phydev,EXT_REG_WR_DATA,phyval);
		phy_write(phydev,EXT_REG_CTRL,extctrl.extphyctrl);
		//printk("writebank extctrl=0x%x v=0x%x\n",extctrl.extphyctrl,phyval);
	}
}

static int phy_register_access(struct genl_info *info, struct nlattr *nest)
{
	struct net *net = genl_info_net(info);
	struct nlattr *tb[PHYACC_ATTR_MAX + 1];
	struct net_device *netdev=NULL;
	unsigned short mode=0, phybank=0;
	unsigned short phyaddr = 0;
	int phyval = 0;
	struct sk_buff *msg;
	int ret=0;
	void *hdr;

	if (!nest) {
		printk("message error\n");
		return -EINVAL;
	}

#if (LINUX_VERSION_CODE <= KERNEL_VERSION(4,9,143))
	ret = nla_parse_nested(tb, PHYACC_ATTR_MAX, nest, phy_acc_policy);
#else
	ret = nla_parse_nested(tb, PHYACC_ATTR_MAX, nest, phy_acc_policy, info->extack);
#endif
	if (ret < 0)
		return ret;

	if (tb[PHYACC_ATTR_IFNAME]) {
		netdev = dev_get_by_name(net, (char *)nla_data(tb[PHYACC_ATTR_IFNAME]));
		if (netdev) {
			//printk("netdev->name = %s\n", netdev->name);
			phydev = netdev->phydev;
			if (phydev) {
				//printk("phydev->phy_id = 0x%x\n", phydev->phy_id);
				if (phydev->drv) {
					phydriver = netdev->phydev->drv;
				} else {
					printk("netdev->phydev->drv == NULL\n");
					return -EINVAL;
				}
			} else {
				dev_put(netdev);
				printk("netdev->phydev == NULL\n");
				return -EINVAL;
			}
		} else {
			printk("can't find net device\n");
			return -ENODEV;
		}
	}

	if (tb[PHYACC_ATTR_MODE])
		mode = nla_get_u16(tb[PHYACC_ATTR_MODE]);

	if (tb[PHYACC_ATTR_BANK_ADDR])
		phybank = nla_get_u16(tb[PHYACC_ATTR_BANK_ADDR]);

	if (tb[PHYACC_ATTR_OFFSET_ADDR])
		phyaddr = nla_get_u16(tb[PHYACC_ATTR_OFFSET_ADDR]);

	if (tb[PHYACC_ATTR_VAL])
		phyval = (int)nla_get_u32(tb[PHYACC_ATTR_VAL]);

	if (phydev) {
		if (mode == PHYACC_ATTR_MODE_READ) {
			/* do PHY read */
			phyval = do_phy_read(phydev, phybank, phyaddr);
		} else if (mode == PHYACC_ATTR_MODE_WRITE) {
			/* do PHY write */
			do_phy_write(phydev, phybank, phyaddr, phyval);
		}
	} else {
		printk("phydev == NULL\n");
		return -ENODEV;
	}

	/* reply back */
	msg = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = genlmsg_put_reply(msg, info, &microchipphy_genl_family, 0, PHYNL_CMD_RDWR_REG/*PHYNL_CMD_WAKE*/);

	nest = nla_nest_start(msg, PHYNL_ATTR_REGACCESS/*WAKE_ATTR_PHYACCESS*/ | NLA_F_NESTED);
	nla_put_u16(msg, PHYACC_ATTR_MODE, mode);
	nla_put_u16(msg, PHYACC_ATTR_BANK_ADDR, phybank);
	nla_put_u16(msg, PHYACC_ATTR_OFFSET_ADDR, phyaddr);
	nla_put_u32(msg, PHYACC_ATTR_VAL, phyval);
	nla_nest_end(msg, nest);

	genlmsg_end(msg, hdr);
	genlmsg_reply(msg, info);

	if (netdev)
		dev_put(netdev);

	return 0;
}

int phynl_rdwr_reg/*phynl_wake_doit*/(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr *tb[PHYNL_ATTR_MAX+1];
	int ret;

	/* handle received params */
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(4,9,143))
	ret = genlmsg_parse(info->nlhdr, &microchipphy_genl_family, tb, PHYNL_ATTR_MAX, phy_rdwr_policy/*phy_wake_policy*/);
#else
	ret = genlmsg_parse(info->nlhdr, &microchipphy_genl_family, tb, PHYNL_ATTR_MAX, phy_rdwr_policy/*phy_wake_policy*/, info ? info->extack : NULL);
#endif
	if (ret < 0) {
		printk("%s(): genlmsg_parse returns %d\n", __func__, ret);
		return ret;
	}

	if (tb[PHYNL_ATTR_REGACCESS/*WAKE_ATTR_PHYACCESS*/]) {
		/* do phy register access */
		ret = phy_register_access(info, tb[PHYNL_ATTR_REGACCESS/*WAKE_ATTR_PHYACCESS*/]);
		if (ret < 0) {
			printk("phy_register_access returns %d\n", ret);
			return ret;
		}
	}

	return 0;
}

int phynl_wake_notification(int notification_type)
{
	struct nlattr *nest;
	struct sk_buff *msg;
	void *hdr;

	/* notify event to user space */
	msg = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &microchipphy_genl_family, 0, PHYNL_CMD_RDWR_REG/*PHYNL_CMD_WAKE*/);

	nest = nla_nest_start(msg, WAKE_ATTR_NOTIFICATION | NLA_F_NESTED);
	nla_put_u32(msg, WAKENOTI_ATTR_STATUS, notification_type);
	nla_nest_end(msg, nest);

	genlmsg_end(msg, hdr);
	genlmsg_multicast(&microchipphy_genl_family, msg, 0, 0, GFP_ATOMIC);
	return 0;
}
EXPORT_SYMBOL(phynl_wake_notification);

#define	MICROCHIPPHY_GENL_NAME		"microchipphy"
#define	MICROCHIPPHY_GENL_VERSION	1
#define	MICROCHIPPHY_MCGRP_MONITOR	"phy_monitor"

static struct genl_multicast_group microchipphy_genl_mcgroups[] = {
	{
		.name = MICROCHIPPHY_MCGRP_MONITOR
	},
};

static const struct genl_ops microchipphy_genl_ops[] = {
	{
		.cmd	= PHYNL_CMD_RDWR_REG,//PHYNL_CMD_WAKE,
		.doit	= phynl_rdwr_reg,//phynl_wake_doit,
	},
};

struct genl_family microchipphy_genl_family = {
	.hdrsize	= 0,
	.name		= MICROCHIPPHY_GENL_NAME,
	.version	= MICROCHIPPHY_GENL_VERSION,
	.netnsok	= true,
	.parallel_ops	= false,
	.ops		= microchipphy_genl_ops,
	.n_ops		= ARRAY_SIZE(microchipphy_genl_ops),
	.mcgrps		= microchipphy_genl_mcgroups,
	.n_mcgrps	= ARRAY_SIZE(microchipphy_genl_mcgroups),
};

/* module setup */

static int __init microchipphy_genl_init(void)
{
	int ret;

	printk("%s()\n", __func__);
	ret = genl_register_family(&microchipphy_genl_family);
	if (ret < 0)
		panic("microchipphy: could not register genetlink family\n");

	return 0;
}

static void __exit microchipphy_genl_exit(void)
{
	genl_unregister_family(&microchipphy_genl_family);
	printk("%s()\n", __func__);
}

module_init(microchipphy_genl_init);
module_exit(microchipphy_genl_exit);

