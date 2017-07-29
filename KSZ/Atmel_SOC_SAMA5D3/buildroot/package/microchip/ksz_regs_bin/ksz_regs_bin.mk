################################################################################
#
# ksz_regs_bin
#
################################################################################

KSZ_REGS_BIN_VERSION = 0
KSZ_REGS_BIN_SITE = $(KSZ_HOME)/app_utils/regs_bin
KSZ_REGS_BIN_SITE_METHOD = local
#KSZ_REGS_BIN_SOURCE = regs_bin.c
KSZ_REGS_BIN_LICENSE = GPLv2

define KSZ_REGS_BIN_EXTRACT_CMDS
	cp $(BR2_DL_DIR)/$(KSZ_REGS_BIN_SOURCE) $(@D)/regs_bin.c
endef

define KSZ_REGS_BIN_BUILD_CMDS
	$(TARGET_CC) $(TARGET_CFLAGS) \
		-o $(@D)/regs_bin $(@D)/regs_bin.c
endef

define KSZ_REGS_BIN_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/regs_bin \
		$(TARGET_DIR)/usr/sbin/regs_bin
endef

$(eval $(generic-package))
