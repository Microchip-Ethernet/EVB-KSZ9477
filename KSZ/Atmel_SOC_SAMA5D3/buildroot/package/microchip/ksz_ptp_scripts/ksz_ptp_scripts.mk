################################################################################
#
# ksz_ptp_scripts
#
################################################################################

KSZ_PTP_SCRIPTS_VERSION = 0
KSZ_PTP_SCRIPTS_SITE = $(KSZ_HOME)/ptp/bin
KSZ_PTP_SCRIPTS_SITE_METHOD = local
#KSZ_PTP_SCRIPTS_SOURCE = ksz_ptp_scripts.tar.bz2
KSZ_PTP_SCRIPTS_LICENSE = GPLv2

define KSZ_PTP_SCRIPTS_INSTALL_TARGET_CMDS
	mkdir -p $(TARGET_DIR)/ptp
	cp -rp $(@D)/* $(TARGET_DIR)/ptp/
endef

$(eval $(generic-package))
