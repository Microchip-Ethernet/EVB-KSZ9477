################################################################################
#
# ksz_Open-AVB
#
################################################################################

KSZ_OPENAVB_VERSION = 0
KSZ_OPENAVB_SITE = $(KSZ_HOME)/ptp/Open-AVB/main
KSZ_OPENAVB_SITE_METHOD = local
#KSZ_OPENAVB_SOURCE = ksz_Open-AVB.tar.bz2
KSZ_OPENAVB_LICENSE = GPLv2

KSZ_CFLAGS=-Wno-unused-but-set-variable

define KSZ_OPENAVB_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS) $(KSZ_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		$(MAKE) -C $(@D)/daemons/mrpd
	CFLAGS="$(TARGET_CFLAGS) $(KSZ_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		$(MAKE) -C $(@D)/examples/mrp_client
	CFLAGS="$(TARGET_CFLAGS) $(KSZ_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		$(MAKE) -C $(@D)/examples/simple_listener
	CFLAGS="$(TARGET_CFLAGS) $(KSZ_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		$(MAKE) -C $(@D)/examples/simple_talker
endef

define KSZ_OPENAVB_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/daemons/mrpd/mrpd \
		$(TARGET_DIR)/usr/sbin/mrpd
	$(INSTALL) -D -m 755 $(@D)/examples/mrp_client/mrpl \
		$(TARGET_DIR)/usr/sbin/mrpl
	$(INSTALL) -D -m 755 $(@D)/examples/mrp_client/mrpq \
		$(TARGET_DIR)/usr/sbin/mrpq
	$(INSTALL) -D -m 755 $(@D)/examples/simple_listener/l \
		$(TARGET_DIR)/usr/sbin/l
	$(INSTALL) -D -m 755 $(@D)/examples/simple_talker/t \
		$(TARGET_DIR)/usr/sbin/t
endef

$(eval $(generic-package))
