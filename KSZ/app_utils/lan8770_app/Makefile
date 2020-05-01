

CROSS_COMPILE ?= arm-linux-

#RAMDISK_DIR = ../ramdisk/usr/sbin

#CFLAGS = -Wall

ifeq (none-linux-gnueabi, $(findstring none-linux-gnueabi, $(CROSS_COMPILE)))
	CFLAGS += -march=armv4t
	LDFLAGS += -march=armv4t
endif

EXE=lan8770_app

all: $(EXE)

lan8770_app: lan8770_app.c
	$(CROSS_COMPILE)gcc -o lan8770_app $(CFLAGS) lan8770_app.c

clean:
	$(RM) $(EXE)

install: $(EXE)
	#@install -D -m 755 $(EXE) $(RAMDISK_DIR)/
	cp -r $(EXE) $(DESTDIR)

