################################################################################
#
# ksz_linuxptp
#
################################################################################

KSZ_LINUXPTP_3_1_1_VERSION = 3
KSZ_LINUXPTP_3_1_1_SITE = $(KSZ_HOME)/ptp/linuxptp/linuxptp-3.1.1
KSZ_LINUXPTP_3_1_1_SITE_METHOD = local
KSZ_LINUXPTP_3_1_1_LICENSE = GPLv2

KSZ_CFLAGS=-Wno-unused-but-set-variable

define KSZ_LINUXPTP_3_1_1_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS) $(KSZ_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		KBUILD_OUTPUT="../linux-headers-custom" \
		$(MAKE) -C $(@D) \
		EXTRA_CFLAGS=-DKSZ_1588_PTP
endef

define KSZ_LINUXPTP_3_1_1_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/ptp4l \
		$(TARGET_DIR)/usr/sbin/p3/ptp4l
	$(INSTALL) -D -m 755 $(@D)/phc2sys \
		$(TARGET_DIR)/usr/sbin/p3/phc2sys
	$(INSTALL) -D -m 755 $(@D)/phc_ctl \
		$(TARGET_DIR)/usr/sbin/p3/phc_ctl
	$(INSTALL) -D -m 755 $(@D)/hwstamp_ctl \
		$(TARGET_DIR)/usr/sbin/p3/hwstamp_ctl
	$(INSTALL) -D -m 755 $(@D)/pmc \
		$(TARGET_DIR)/usr/sbin/p3/pmc
	$(INSTALL) -D -m 755 $(@D)/timemaster \
		$(TARGET_DIR)/usr/sbin/p3/timemaster
	$(INSTALL) -D -m 755 $(@D)/nsm \
		$(TARGET_DIR)/usr/sbin/p3/nsm
	$(INSTALL) -D -m 755 $(@D)/ts2phc \
		$(TARGET_DIR)/usr/sbin/p3/ts2phc
endef

$(eval $(generic-package))
