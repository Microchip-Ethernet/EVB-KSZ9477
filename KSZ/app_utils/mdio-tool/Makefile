

#CROSS_COMPILE ?= arm-linux-

#RAMDISK_DIR = ../ramdisk/usr/sbin

#CFLAGS = -Wall

#ifeq (none-linux-gnueabi, $(findstring none-linux-gnueabi, $(CROSS_COMPILE)))
#	CFLAGS += -march=armv4t
#	LDFLAGS += -march=armv4t
#endif

EXE=mdio-tool

all: $(EXE)

mdio-tool: mdio-tool.c
	$(CROSS_COMPILE)gcc -o mdio-tool $(CFLAGS) mdio-tool.c

clean:
	$(RM) $(EXE)

install: $(EXE)
	#@install -D -m 755 $(EXE) $(RAMDISK_DIR)/
	cp -r $(EXE) $(DESTDIR)

