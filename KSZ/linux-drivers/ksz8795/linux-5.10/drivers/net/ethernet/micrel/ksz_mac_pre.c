

#ifndef KSZ_MAC_PRE
#define KSZ_MAC_PRE

static struct ksz_mac *get_ksz_mac(void *ptr);
static struct ksz_mac *get_netdev_priv(struct net_device *dev);
static void sw_reset_mac_mib(struct ksz_mac *priv);
static void hw_set_multicast(void *priv, int multicast);
static void hw_set_promisc(void *priv, int promisc);
static int sw_mac_init(struct net_device *net, struct ksz_mac *priv);


#if defined(CONFIG_IBA_KSZ9897) || defined(CONFIG_IBA_LAN937X)
#define CONFIG_KSZ_IBA_ONLY
#endif

#ifdef CONFIG_KSZ_SWITCH_EMBEDDED
#include <linux/of_irq.h>
#include <linux/spi/spi.h>
#include <linux/crc32.h>
#include <linux/ip.h>
#include <net/ip.h>
#include <net/ipv6.h>

/* Need to predefine get_sysfs_data. */

#ifndef get_sysfs_data
struct ksz_port;

static void get_sysfs_data_(struct net_device *dev,
	struct semaphore **proc_sem, struct ksz_port **port);

#define get_sysfs_data		get_sysfs_data_
#endif

static void copy_old_skb(struct sk_buff *old, struct sk_buff *skb);
#define DO_NOT_USE_COPY_SKB

#if defined(CONFIG_IBA_KSZ9897)
#include "iba-ksz9897.c"
#elif defined(CONFIG_HAVE_KSZ9897)
#include "i2c-ksz9897.c"
#elif defined(CONFIG_HAVE_KSZ8795)
#include "spi-ksz8795.c"
#elif defined(CONFIG_SMI_KSZ8895)
#include "smi-ksz8895.c"
#elif defined(CONFIG_HAVE_KSZ8895)
#include "spi-ksz8895.c"
#elif defined(CONFIG_SMI_KSZ8863)
#include "smi-ksz8863.c"
#elif defined(CONFIG_HAVE_KSZ8863)
#include "i2c-ksz8863.c"
#elif defined(CONFIG_IBA_LAN937X)
#include "../microchip/iba-lan937x.c"
#elif defined(CONFIG_SMI_LAN937X)
#include "../microchip/smi-lan937x.c"
#elif defined(CONFIG_HAVE_LAN937X)
#include "../microchip/spi-lan937x.c"
#endif
#endif

#include "ksz_mac.h"

#endif

