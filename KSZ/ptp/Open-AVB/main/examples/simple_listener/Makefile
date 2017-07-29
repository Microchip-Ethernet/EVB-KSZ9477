CC = $(CROSS_COMPILE)gcc
#LDLIBS = -std=gnu99 -lpcap -lsndfile
LDLIBS = -std=gnu99

ifeq (-gnueabi-, $(findstring -gnueabi-, $(CC)))
	CFLAGS += -march=armv4t
	LDFLAGS += -march=armv4t
endif
LDFLAGS += -pthread

l: l.c
	$(CC) -o $@ $< $(LDLIBS) $(LDFLAGS)

simple_listener: simple_listener.c
	$(CC) -o $@ $< $(LDLIBS) $(LDFLAGS)

all: l

clean:
	rm -f l simple_listener
