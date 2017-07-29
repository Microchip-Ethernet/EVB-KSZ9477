################################################################################
#
# mdio-tool
#
################################################################################

MDIO_TOOL_VERSION = 0
MDIO_TOOL_SITE = $(KSZ_HOME)/app_utils/mdio-tool
MDIO_TOOL_SITE_METHOD = local
MDIO_TOOL_LICENSE = GPLv2

define MDIO_TOOL_EXTRACT_CMDS
	cp $(BR2_DL_DIR)/$(MDIO_TOOL_SOURCE) $(@D)/mdio-tool.c
endef

define MDIO_TOOL_BUILD_CMDS
	$(TARGET_CC) $(TARGET_CFLAGS) \
		-o $(@D)/mdio-tool $(@D)/mdio-tool.c
endef

define MDIO_TOOL_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/mdio-tool \
		$(TARGET_DIR)/usr/sbin/mdio-tool
endef

$(eval $(generic-package))
