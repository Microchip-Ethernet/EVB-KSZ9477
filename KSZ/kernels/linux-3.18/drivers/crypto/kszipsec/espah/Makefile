#
# Proprietary Information of Elliptic Semiconductor
# Copyright (C) 2004, all rights reserved, Elliptic Semiconductor, Inc.
#
# As part of our confidentiality  agreement, Elliptic Semiconductor and the
# Company, as  a  Receiving Party, of  this  information  agrees to keep
# strictly  confidential  all Proprietary Information  so received from
# Elliptic Semiconductor. Such Proprietary Information can be used solely for
# the  purpose  of evaluating  and/or conducting a proposed business
# relationship  or  transaction  between  the  parties.  Each Party  agrees
# that  any  and  all  Proprietary  Information  is  and shall remain
# confidential and the property of Elliptic Semiconductor.  The  Company  may
# not  use  any of  the  Proprietary  Information of Elliptic Semiconductor for
# any purpose other  than  the  above-stated purpose  without the prior written
# consent of Elliptic Semiconductor.
#
# file    : Makefile
#
ELPCRYPTO_ROOT=..
OLIB=../lib
SINCLUDE=../include

include ${ELPCRYPTO_ROOT}/Makefile.rules
OBJS= kszespah.o


OUTPUT = ${OLIB}/kszespahlib.a
CFLAGS += -I${SINCLUDE} ${BUILD_OPT}

all: $(OBJS) ${OUTPUT} 
clean:
	rm -f $(OUTPUT) *.o *.core core *.bak *~ $(OUTPUT)


$(OUTPUT): $(OBJS)
	$(AR) $(ARFLAGS) $(OUTPUT) $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

