################################################################################
#
# ksz_linuxptp
#
################################################################################

KSZ_LINUXPTP_VERSION = 0
#KSZ_LINUXPTP_SOURCE = ksz_linuxptp.tar.bz2
KSZ_LINUXPTP_SITE = $(KSZ_HOME)/ptp/linuxptp/main
KSZ_LINUXPTP_SITE_METHOD = local
KSZ_LINUXPTP_LICENSE = GPLv2

KSZ_CFLAGS=-Wno-unused-but-set-variable

define KSZ_LINUXPTP_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS) $(KSZ_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		KBUILD_OUTPUT="../linux-custom" \
		$(MAKE) -C $(@D) \
		EXTRA_CFLAGS=-DKSZ_1588_PTP
endef

define KSZ_LINUXPTP_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/ptp4l \
		$(TARGET_DIR)/usr/sbin/ptp4l
	$(INSTALL) -D -m 755 $(@D)/phc2sys \
		$(TARGET_DIR)/usr/sbin/phc2sys
	$(INSTALL) -D -m 755 $(@D)/phc_ctl \
		$(TARGET_DIR)/usr/sbin/phc_ctl
	$(INSTALL) -D -m 755 $(@D)/hwstamp_ctl \
		$(TARGET_DIR)/usr/sbin/hwstamp_ctl
	$(INSTALL) -D -m 755 $(@D)/pmc \
		$(TARGET_DIR)/usr/sbin/pmc
endef

$(eval $(generic-package))
