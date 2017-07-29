

RAMDISK_DIR := ../../ramdisk


all:
clean:

install:
	@if [ -e ontime ]; then \
		cp -f ontime $(RAMDISK_DIR)/usr/sbin/; \
		cp -f ptpProfile.txt $(RAMDISK_DIR)/etc/; \
	fi
	@if [ -e 802.1as ]; then \
		cp -f 802.1as $(RAMDISK_DIR)/usr/sbin/; \
		cp -f avbProfile.txt $(RAMDISK_DIR)/etc/; \
	fi
	@mkdir -p $(RAMDISK_DIR)/ptp
	@if [ -e README ]; then \
		cp -f README $(RAMDISK_DIR)/ptp/; \
	fi
	@if [ -e power.sh ]; then \
		cp -f power.sh $(RAMDISK_DIR)/ptp/; \
	fi
	@if [ -e vlan.sh ]; then \
		cp -f vlan.sh $(RAMDISK_DIR)/ptp/; \
	fi
	@if [ -d e2e ]; then \
		mkdir -p $(RAMDISK_DIR)/ptp/e2e; \
		cp -rf e2e/* $(RAMDISK_DIR)/ptp/e2e; \
	fi
	@if [ -d p2p ]; then \
		mkdir -p $(RAMDISK_DIR)/ptp/p2p; \
		cp -rf p2p/* $(RAMDISK_DIR)/ptp/p2p; \
	fi
	@if [ -d power ]; then \
		mkdir -p $(RAMDISK_DIR)/ptp/power; \
		cp -rf power/* $(RAMDISK_DIR)/ptp/power; \
	fi
	@if [ -d telecom ]; then \
		mkdir -p $(RAMDISK_DIR)/ptp/telecom; \
		cp -rf telecom/* $(RAMDISK_DIR)/ptp/telecom; \
	fi
	@if [ -d avb ]; then \
		mkdir -p $(RAMDISK_DIR)/ptp/avb; \
		cp -rf avb/* $(RAMDISK_DIR)/ptp/avb; \
	fi

