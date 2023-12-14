

#ifndef KSZ_MAC_H
#define KSZ_MAC_H

#if defined(CONFIG_HAVE_KSZ9897)
#include "ksz_cfg_9897.h"
#elif defined(CONFIG_HAVE_KSZ8795)
#include "ksz_cfg_8795.h"
#elif defined(CONFIG_HAVE_KSZ8895)
#include "ksz_cfg_8895.h"
#elif defined(CONFIG_HAVE_KSZ8863)
#include "ksz_cfg_8863.h"
#elif defined(CONFIG_HAVE_KSZ8463)
#include "ksz_cfg_8463.h"
#elif defined(CONFIG_HAVE_LAN937X)
#include "../microchip/lan937x_cfg.h"
#endif

#ifndef CONFIG_KSZ_SWITCH_EMBEDDED
#ifdef CONFIG_HAVE_LAN937X
#include "../microchip/lan937x_dev.h"
#else
#include "ksz_spi_net.h"
#endif
#endif

struct ksz_mac {
	void			*dev;
	struct net_device	*net;
	struct ksz_mac		*hw_priv;
	struct platform_device	*sw_pdev;
	struct phy_device	dummy_phy;
	struct phy_device	*saved_phy;
	struct ksz_port		port;
	spinlock_t		tx_lock;
	int			msg_enable;
	int			phy_addr;
	u32			multi:2;
	u32			promisc:1;
	u8			opened;
	u8			hw_multi;
	u8			hw_promisc;
	void			*parent;
	struct delayed_work	promisc_reset;
	struct work_struct	rmv_dev;
	struct ksz_sw_sysfs	sysfs;
#ifdef CONFIG_1588_PTP
	struct ksz_ptp_sysfs	ptp_sysfs;
#endif
#if defined(CONFIG_PHYLINK) || defined(CONFIG_PHYLINK_MODULE)
	struct phylink		*phylink;
#endif
};

#endif

