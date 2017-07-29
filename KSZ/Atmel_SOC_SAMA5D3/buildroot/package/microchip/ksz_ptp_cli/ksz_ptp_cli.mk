################################################################################
#
# ksz_ptp_cli
#
################################################################################

KSZ_PTP_CLI_VERSION = 0
KSZ_PTP_CLI_SITE = $(KSZ_HOME)/app_utils/ptp_cli
KSZ_PTP_CLI_SITE_METHOD = local
#KSZ_PTP_CLI_SOURCE = ksz_ptp_cli.tar.bz2
KSZ_PTP_CLI_LICENSE = GPLv2

KSZ_CFLAGS=-Wno-unused-but-set-variable

define KSZ_PTP_CLI_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS) $(KSZ_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		$(MAKE) -C $(@D)
endef

define KSZ_PTP_CLI_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/ptp_cli \
		$(TARGET_DIR)/usr/sbin/ptp_cli
endef

$(eval $(generic-package))
