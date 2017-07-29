OPT=-O2
CFLAGS=$(OPT) -Wall -W -Wno-parentheses

CC=$(CROSS_COMPILE)gcc
INCFLAGS=-I../../lib/igb
LDLIBS=-lrt -lm -pthread
#LDLIBS=-ligb -lpci -lz -lrt -lm -pthread
#LDFLAGS=-L../../lib/igb

ifeq (-gnueabi-, $(findstring -gnueabi-, $(CC)))
	CFLAGS += -march=armv4t
	LDFLAGS += -march=armv4t
endif

all: t

t: t.o

t.o: t.c
	$(CC) -c $(INCFLAGS) -I../../daemons/mrpd $(CFLAGS) t.c

simple_talker: simple_talker.o

simple_talker.o: simple_talker.c
	gcc -c $(INCFLAGS) -I../../daemons/mrpd $(CFLAGS) simple_talker.c

%: %.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f t
	rm -f `find . -name "*~" -o -name "*.[oa]" -o -name "\#*\#" -o -name TAGS -o -name core -o -name "*.orig"` simple_talker

