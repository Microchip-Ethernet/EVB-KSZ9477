################################################################################
#
# ksz_ptp_test
#
################################################################################

KSZ_PTP_TEST_VERSION = 0
KSZ_PTP_TEST_SITE = $(KSZ_HOME)/app_utils/nettest
KSZ_PTP_TEST_SITE_METHOD = local
#KSZ_PTP_TEST_SOURCE = ksz_ptp_test.tar.bz2
KSZ_PTP_TEST_LICENSE = GPLv2

KSZ_CFLAGS=-Wno-unused-but-set-variable

define KSZ_PTP_TEST_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS) $(KSZ_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		$(MAKE) -C $(@D)/network
endef

define KSZ_PTP_TEST_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/network/ptp \
		$(TARGET_DIR)/usr/bin/ptp
	$(INSTALL) -D -m 755 $(@D)/network/authtest \
		$(TARGET_DIR)/usr/sbin/authen
	$(INSTALL) -D -m 755 $(@D)/network/kszsw \
		$(TARGET_DIR)/usr/sbin/kszsw
	$(INSTALL) -D -m 755 $(@D)/network/dlr_daemon \
		$(TARGET_DIR)/usr/sbin/dlr_daemon
	$(INSTALL) -D -m 755 $(@D)/network/nettest \
		$(TARGET_DIR)/usr/sbin/nettest
endef

$(eval $(generic-package))
