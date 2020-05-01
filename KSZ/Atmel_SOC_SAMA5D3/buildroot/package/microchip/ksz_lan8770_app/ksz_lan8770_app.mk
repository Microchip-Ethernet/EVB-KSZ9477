################################################################################
#
# ksz_lan8770_app
#
################################################################################

KSZ_LAN8770_APP_VERSION = 0
KSZ_LAN8770_APP_SITE = $(KSZ_HOME)/app_utils/lan8770_app
KSZ_LAN8770_APP_SITE_METHOD = local
KSZ_LAN8770_APP_INSTALL_STAGING = YES
KSZ_LAN8770_APP_DEPENDENCIES = libmnl
KSZ_LAN8770_APP_LICENSE = GPLv2
TARGET_CFLAGS += -L$(TARGET_DIR)/usr/lib 

LAN8770_APP_CFLAGS += -lmnl -lpthread

define KSZ_LAN8770_APP_EXTRACT_CMDS
	cp $(BR2_DL_DIR)/$(KSZ_LAN8770_APP_SOURCE) $(@D)
endef

define KSZ_LAN8770_APP_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS) $(LAN8770_APP_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		$(MAKE) -C $(@D)
endef


define KSZ_LAN8770_APP_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/lan8770_app \
		$(TARGET_DIR)/usr/sbin/lan8770_app
endef

$(eval $(generic-package))
