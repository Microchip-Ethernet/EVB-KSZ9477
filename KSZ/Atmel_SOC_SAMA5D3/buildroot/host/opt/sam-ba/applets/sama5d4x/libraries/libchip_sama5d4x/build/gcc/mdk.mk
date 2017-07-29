
# Compilation tools
AR = armar.exe
CC = armcc.exe
LD = armar.exe
SIZE = 
OBJCOPY = 

# Flags

CFLAGS += $(OPTIMIZATION) $(INCLUDES) -D$(CHIP) -DTRACE_LEVEL=$(TRACE_LEVEL)

ASFLAGS = $(OPTIMIZATION) $(INCLUDES) -D$(CHIP) -D__ASSEMBLY__

LDFLAGS = 
