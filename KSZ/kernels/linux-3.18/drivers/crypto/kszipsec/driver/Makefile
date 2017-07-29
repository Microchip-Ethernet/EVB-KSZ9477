#
# KSZ8692 IPsec driver makefile


# Device driver name
TARGETNAME := kszipsec

# For Linux 2.6 kernel
KBUILD_EXTMOD ?= .
ifeq ("$(KBUILD_EXTMOD)", "")
KBUILD_EXTMOD = drivers/crypto/kszipsec/driver
endif


# Driver hardware code

DRV_HEADERS = kszipsec.h Makefile
DRV_OBJS := kszipsec_main.o


# Elliptic library code

COMMON = ../common
CRYPTO = ../crypto_srm
ESPAH = ../espah
INCLUDES = ../include

ELP_HEADERS = $(INCLUDES)/elpcrypto.h $(INCLUDES)/elpcryptohw.h \
	$(INCLUDES)/elpipsec.h $(INCLUDES)/elpipsechw.h \
	$(INCLUDES)/elptypes.h $(INCLUDES)/elputils.h
ELP_OBJS = kszaes.o kszdes.o kszhmac.o kszrc4.o kszespah.o \
	kszcrypto.o kszcrypto_srm.o kszutils.o

INCDIR := -I$(KBUILD_EXTMOD)/$(INCLUDES)


HEADERS := $(DRV_HEADERS) $(ELP_HEADERS)
OBJS := $(DRV_OBJS) $(ELP_OBJS)


EXTRA_CFLAGS += $(INCDIR) -DDEF_KSZ -DDEF_LINUX -DVERSION=\"1.2\"
ifdef DEBUG
EXTRA_CFLAGS += -DDEBUG
else
EXTRA_CFLAGS += -DCRYPTO_NO_DEBUG
endif


# Build within Linux kernel

ifdef PATCHLEVEL

ifeq ($(PATCHLEVEL),4)
ifeq ($(SUBLEVEL),16)
EXTRA_CFLAGS_nostdinc := $(EXTRA_CFLAGS)
endif

%.o: $(CRYPTO)/%.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS_nostdinc) -DKBUILD_BASENAME=$(subst $(comma),_,$(subst -,_,$(*F))) $(CFLAGS_$(*F)) $(CFLAGS_$@) -c -o $@ $<
	@ ( \
	    echo 'ifeq ($(strip $(subst $(comma),:,$(CFLAGS) $(EXTRA_CFLAGS_nostdinc) $(CFLAGS_$(*F)) $(CFLAGS_$@))),$$(strip $$(subst $$(comma),:,$$(CFLAGS) $$(EXTRA_CFLAGS_nostdinc) $$(CFLAGS_$(*F)) $$(CFLAGS_$@))))' ; \
	    echo 'FILES_FLAGS_UP_TO_DATE += $@' ; \
	    echo 'endif' \
	) > $(dir $@)/.$(notdir $@).flags

%.o: $(ESPAH)/%.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS_nostdinc) -DKBUILD_BASENAME=$(subst $(comma),_,$(subst -,_,$(*F))) $(CFLAGS_$(*F)) $(CFLAGS_$@) -c -o $@ $<
	@ ( \
	    echo 'ifeq ($(strip $(subst $(comma),:,$(CFLAGS) $(EXTRA_CFLAGS_nostdinc) $(CFLAGS_$(*F)) $(CFLAGS_$@))),$$(strip $$(subst $$(comma),:,$$(CFLAGS) $$(EXTRA_CFLAGS_nostdinc) $$(CFLAGS_$(*F)) $$(CFLAGS_$@))))' ; \
	    echo 'FILES_FLAGS_UP_TO_DATE += $@' ; \
	    echo 'endif' \
	) > $(dir $@)/.$(notdir $@).flags

%.o: $(COMMON)/%.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS_nostdinc) -DKBUILD_BASENAME=$(subst $(comma),_,$(subst -,_,$(*F))) $(CFLAGS_$(*F)) $(CFLAGS_$@) -c -o $@ $<
	@ ( \
	    echo 'ifeq ($(strip $(subst $(comma),:,$(CFLAGS) $(EXTRA_CFLAGS_nostdinc) $(CFLAGS_$(*F)) $(CFLAGS_$@))),$$(strip $$(subst $$(comma),:,$$(CFLAGS) $$(EXTRA_CFLAGS_nostdinc) $$(CFLAGS_$(*F)) $$(CFLAGS_$@))))' ; \
	    echo 'FILES_FLAGS_UP_TO_DATE += $@' ; \
	    echo 'endif' \
	) > $(dir $@)/.$(notdir $@).flags


O_TARGET := $(TARGETNAME).o

obj-y   := $(OBJS)

obj-m   := $(O_TARGET)

include $(TOPDIR)/Rules.make

else
%.o: $(CRYPTO)/%.c
	$(call if_changed_dep,cc_o_c)

%.o: $(ESPAH)/%.c
	$(call if_changed_dep,cc_o_c)

%.o: $(COMMON)/%.c
	$(call if_changed_dep,cc_o_c)


ifndef CONFIG_CRYPTO_DEV_KSZIPSEC
CONFIG_CRYPTO_DEV_KSZIPSEC=m
endif

obj-$(CONFIG_CRYPTO_DEV_KSZIPSEC) += $(TARGETNAME).o

$(TARGETNAME)-objs := $(OBJS)
endif

else

# Find out if GCC tools are needed.
NO_CC := $(shell if [ "$(MAKECMDGOALS)" = "clean" ]  || \
    [ "$(MAKECMDGOALS)" = "zip" ]  || \
    [ "$(MAKECMDGOALS)" = "distclean" ]; then \
    echo "yes"; else echo ""; fi)
ifneq ("$(NO_CC)", "yes")

ifdef INTEL
CROSS_COMPILE ?=
KERNELDIR ?= /usr/src/linux-2.4

else
CROSS_COMPILE ?= arm-linux-
LINUX ?= /Centaur/linux
KERNELDIR ?= /Centaur/linux
endif
CFLAGS :=


GCC = $(CROSS_COMPILE)gcc
STRIP = $(CROSS_COMPILE)strip
LD = $(CROSS_COMPILE)ld


# Check which kernel is used

MAKE_FILE = $(KERNELDIR)/Makefile
PATCHLEVEL := $(shell grep "^PATCHLEVEL =" $(MAKE_FILE) | cut -d" " -f3)

ifeq ($(PATCHLEVEL),4)
O_TARGET := $(TARGETNAME).o

default: $(O_TARGET)

$(O_TARGET) : $(OBJS) $(HEADERS)
	@$(LD) -r $(OBJS) -o $@

else
O_TARGET := $(TARGETNAME).ko
TARGET := $(TARGETNAME).o

default: $(O_TARGET)

$(TARGET) : $(OBJS) $(HEADERS)
	@$(LD) -r $(OBJS) -o $@

$(TARGETNAME).mod.c: $(TARGETNAME).o
	@if [ -d $(LINUX)/scripts/mod ]; then \
	$(LINUX)/scripts/mod/modpost -i \
		$(LINUX)/Module.symvers $(LINUX)/vmlinux $<; \
	else \
	$(LINUX)/scripts/modpost -i \
		$(LINUX)/Module.symvers $(LINUX)/vmlinux $<; \
	fi
	touch $@

$(TARGETNAME).mod.o: .c=.o

$(O_TARGET): $(TARGETNAME).o $(TARGETNAME).mod.o
	$(LD) -EL -r -o $@ $^
endif
endif


CFLAGS := $(CFLAGS) -D__KERNEL__ -DMODULE -I$(KERNELDIR)/include -O2 -Wall
CFLAGS += -Wstrict-prototypes -fomit-frame-pointer -fno-common
ifndef INTEL
CFLAGS += -D__LINUX_ARM_ARCH__=4 -march=armv4 -mtune=arm9tdmi -msoft-float
endif
CFLAGS += -DKBUILD_BASENAME=$(TARGETNAME) -DKBUILD_MODNAME=$(TARGETNAME)

CFLAGS += $(EXTRA_CFLAGS)


%.o: %.c
	$(GCC) $(CFLAGS) $(CPPFLAGS) -c $<

%.o: $(CRYPTO)/%.c
	$(GCC) $(CFLAGS) $(CPPFLAGS) -c $<

%.o: $(ESPAH)/%.c
	$(GCC) $(CFLAGS) $(CPPFLAGS) -c $<

%.o: $(COMMON)/%.c
	$(GCC) $(CFLAGS) $(CPPFLAGS) -c $<


kszipsec_main.o : $(DRV_HEADERS)

kszaes.o        : $(CRYPTO)/kszaes.c $(ELP_HEADERS)
kszdes.o        : $(CRYPTO)/kszdes.c $(ELP_HEADERS)
kszhmac.o       : $(CRYPTO)/kszhmac.c $(ELP_HEADERS)
kszrc4.o        : $(CRYPTO)/kszrc4.c $(ELP_HEADERS)
kszcrypto.o     : $(CRYPTO)/kszcrypto.c $(ELP_HEADERS)
kszcrypto_srm.o : $(CRYPTO)/kszcrypto_srm.c $(ELP_HEADERS)
kszespah.o      : $(ESPAH)/kszespah.c $(ELP_HEADERS)
kszutils.o      : $(COMMON)/kszutils.c $(ELP_HEADERS)


clean:
	@$(RM) *.o *.a *~ *.out .*.flags
	@$(RM) *.mod.c .*.cmd Modules.symvers
	@$(RM) -fr .tmp_versions

distclean: clean
	@$(RM) $(O_TARGET) *.ko

zip: distclean
	tar -cvf $@.tar *.c *.h *.sh Makefile
	gzip $@.tar
endif
