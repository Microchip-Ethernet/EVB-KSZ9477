################################################################################
#
# web gui
#
################################################################################

WEB_GUI_VERSION = 0
WEB_GUI_SITE = $(KSZ_HOME)/app_utils/web_gui
WEB_GUI_SITE_METHOD = local
WEB_GUI_LICENSE = GPLv2
WEB_GUI_DEPENDENCIES = python thttpd

define WEB_GUI_EXTRACT_CMDS
	cp $(BR2_DL_DIR)/$(WEB_GUI_SOURCE) $(@D)/
endef

define WEB_GUI_INSTALL_TARGET_CMDS
	$(INSTALL) -d $(TARGET_DIR)/var/www/data/cgi-bin
	$(INSTALL) -D -m 755 $(@D)/swcfg \
		$(TARGET_DIR)/bin/swcfg
	$(INSTALL) -D -m 644 $(@D)/index.html \
		$(TARGET_DIR)/var/www/data/
	$(INSTALL) -D -m 755 $(@D)/config.py \
		$(TARGET_DIR)/var/www/data/cgi-bin/config.py
	$(INSTALL) -D -m 755 $(@D)/user_auth.py \
		$(TARGET_DIR)/var/www/data/cgi-bin/user_auth.py
	$(INSTALL) -D -m 644 $(@D)/microchip_logo.png \
		$(TARGET_DIR)/var/www/data/microchip_logo.png
endef

$(eval $(generic-package))
