

CROSS_COMPILE ?= arm-linux-

CFLAGS += -Wall -Wno-array-bounds -pthread

ifeq (-gnueabi-, $(findstring -gnueabi-, $(CROSS_COMPILE)))
	CFLAGS += -march=armv4t
	LDFLAGS += -march=armv4t
endif

EXE=ptp_cli mrp_cli

all: $(EXE)

ptp_cli: ptp_cli.c ksz_ptp.c ksz_ptp.h
	$(CROSS_COMPILE)gcc -o ptp_cli $(CFLAGS) ptp_cli.c

mrp_cli: mrp_cli.c ksz_mrp_api.c ksz_mrp_api.h
	$(CROSS_COMPILE)gcc -o mrp_cli $(CFLAGS) mrp_cli.c

clean:
	$(RM) $(EXE)
