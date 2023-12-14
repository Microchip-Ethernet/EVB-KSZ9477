################################################################################
#
# ksz_linuxptp
#
################################################################################

KSZ_LINUXPTP_4_0_0_VERSION = 4
KSZ_LINUXPTP_4_0_0_SITE = $(KSZ_HOME)/ptp/linuxptp/linuxptp-4.0.0
KSZ_LINUXPTP_4_0_0_SITE_METHOD = local
KSZ_LINUXPTP_4_0_0_LICENSE = GPLv2

KSZ_CFLAGS=-Wno-unused-but-set-variable

define KSZ_LINUXPTP_4_0_0_BUILD_CMDS
	CFLAGS="$(TARGET_CFLAGS) $(KSZ_CFLAGS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		KBUILD_OUTPUT="../linux-headers-custom" \
		$(MAKE) -C $(@D) \
		EXTRA_CFLAGS=-DKSZ_1588_PTP
endef

define KSZ_LINUXPTP_4_0_0_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/ptp4l \
		$(TARGET_DIR)/usr/sbin/p4/ptp4l
	$(INSTALL) -D -m 755 $(@D)/phc2sys \
		$(TARGET_DIR)/usr/sbin/p4/phc2sys
	$(INSTALL) -D -m 755 $(@D)/phc_ctl \
		$(TARGET_DIR)/usr/sbin/p4/phc_ctl
	$(INSTALL) -D -m 755 $(@D)/hwstamp_ctl \
		$(TARGET_DIR)/usr/sbin/p4/hwstamp_ctl
	$(INSTALL) -D -m 755 $(@D)/pmc \
		$(TARGET_DIR)/usr/sbin/p4/pmc
	$(INSTALL) -D -m 755 $(@D)/timemaster \
		$(TARGET_DIR)/usr/sbin/p4/timemaster
	$(INSTALL) -D -m 755 $(@D)/nsm \
		$(TARGET_DIR)/usr/sbin/p4/nsm
	$(INSTALL) -D -m 755 $(@D)/ts2phc \
		$(TARGET_DIR)/usr/sbin/p4/ts2phc
	$(INSTALL) -D -m 755 $(@D)/tz2alt \
		$(TARGET_DIR)/usr/sbin/p4/tz2alt
endef

$(eval $(generic-package))
