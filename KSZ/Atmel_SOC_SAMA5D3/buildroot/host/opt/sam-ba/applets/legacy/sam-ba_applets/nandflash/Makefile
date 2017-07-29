# ----------------------------------------------------------------------------
#         ATMEL Microcontroller Software Support 
# ----------------------------------------------------------------------------
# Copyright (c) 2011, Atmel Corporation
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# - Redistributions of source code must retain the above copyright notice,
# this list of conditions and the disclaimer below.
#
# Atmel's name may not be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

# 	Makefile for compiling applet-project nandflash applet

# Chip & board used for compilation
# (can be overriden by adding CHIP=chip and BOARD=board to the command-line)
CHIP  = at91sam9260
BOARD = at91sam9260-ek

# Optimization level, put in comment for debugging
OPTIMIZATION = -Os

# define default install directory
BOARD_DIR = $(CHIP)-ek
ifeq ($(CHIP),at91cap9)
BOARD_DIR = $(BOARD)
endif
ifeq ($(CHIP),at91cap7)
BOARD_DIR = $(BOARD)
endif

INSTALLDIR = "../../../../tcl_lib/$(BOARD_DIR)/"

# AT91 library directory
AT91LIB = ../../at91lib

# Output file basename
OUTPUT = applet-nandflash-$(CHIP)
# Compile with chip specific features
include $(AT91LIB)/boards/$(BOARD)/$(CHIP)/chip.mak

# Compile for all memories available on the board (this sets $(MEMORIES))
include $(AT91LIB)/boards/$(BOARD)/board.mak

# Output directories
BIN = bin
OBJ = obj

#-------------------------------------------------------------------------------
#		Tools
#-------------------------------------------------------------------------------

# Tool suffix when cross-compiling
CROSS_COMPILE = arm-none-eabi-

# Compilation tools
CC = $(CROSS_COMPILE)gcc
SIZE = $(CROSS_COMPILE)size
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy

# Flags
INCLUDES = -I$(AT91LIB)/boards/$(BOARD) -I$(AT91LIB)/peripherals -I$(AT91LIB)/memories
INCLUDES += -I$(AT91LIB)/drivers
INCLUDES += -I$(AT91LIB)
ifeq (cortexm3,$(CHIP_CORE))
    # For Cortex-M3: thumb code only mthumb32
    TARGET_OPTS = -mcpu=cortex-m3 -mthumb 
    # Force usage of HW ECC
    CHIP_IP_ECC  = HW_ECC
    CHIP_IP_NAND = NAND_CTRL
    CFLAGS +=  -DHARDWARE_ECC
else
    # ARM7 or 9
    TARGET_OPTS =
endif

CFLAGS += $(TARGET_OPTS)
CFLAGS += -Wall -mlong-calls -ffunction-sections
CFLAGS += -g $(OPTIMIZATION) -mthumb $(INCLUDES) -D$(CHIP) -DDYN_TRACES
ASFLAGS = $(TARGET_OPTS) -Wall -g $(OPTIMIZATION) $(INCLUDES) -D$(CHIP) -D__ASSEMBLY__
LDFLAGS = -g $(OPTIMIZATION) $(TARGET_OPTS) -Wl,-Map=$(OUTPUT).map,--gc-sections 
#-nostartfiles 


#-------------------------------------------------------------------------------
# Trace level used for compilation
#-------------------------------------------------------------------------------
# (can be overriden by adding TRACE_LEVEL=#number to the command-line)
# TRACE_LEVEL_DEBUG      5
# TRACE_LEVEL_INFO       4
# TRACE_LEVEL_WARNING    3
# TRACE_LEVEL_ERROR      2
# TRACE_LEVEL_FATAL      1
# TRACE_LEVEL_NO_TRACE   0

# Define if traces are allowed depending on the chip
#-------------------------------------------------------------------------------
# Info traces allowed by default
TR_LEV = 4

# Disable trace capability for devices with few memory
ifeq ($(CHIP),at91sam7se32)
CFLAGS += -UDYN_TRACES
TR_LEV = 0
endif

ifeq ($(CHIP),at91sam3u2)
CFLAGS += -UDYN_TRACES
TR_LEV = 0
endif

ifeq ($(CHIP),at91sam3u1)
CFLAGS += -UDYN_TRACES
TR_LEV = 0
endif

CFLAGS += -DTRACE_LEVEL=$(TR_LEV)


#-------------------------------------------------------------------------------
#		Files
#-------------------------------------------------------------------------------

# Directories where source files can be found
ISP = ..
PERIPH = $(AT91LIB)/peripherals
BOARDS = $(AT91LIB)/boards
MEM = $(AT91LIB)/memories
UTILITY = $(AT91LIB)/utility
DRIVERS = $(AT91LIB)/drivers


VPATH += $(ISP)/common
VPATH += $(MEM)/nandflash
VPATH += $(UTILITY)
VPATH += $(PERIPH)/dbgu $(PERIPH)/pio $(PERIPH)/irq
VPATH += $(BOARDS)/$(BOARD) $(BOARDS)/$(BOARD)/$(CHIP)
VPATH += $(PERIPH)/hsmc4

# Objects built from C source files
C_OBJECTS = main.o

# Objects for chips with nfc
ifeq ($(CHIP_IP_NAND), NAND_CTRL)
C_OBJECTS += NfcRawNandFlash.o
C_OBJECTS += hsmc4.o
else
C_OBJECTS += RawNandFlash.o
endif

C_OBJECTS += EccNandFlash.o SkipBlockNandFlash.o
C_OBJECTS += NandFlashModel.o NandFlashModelList.o NandSpareScheme.o

ifeq ($(CHIP_IP_ECC), HW_ECC)
C_OBJECTS +=  hsmc4_ecc.o
endif

C_OBJECTS += math.o string.o stdio.o trace.o hamming.o
C_OBJECTS += dbgu.o pio.o 
C_OBJECTS += board_memories.o board_lowlevel.o

# Individual objects for different chips
C_OBJECTS += $(IRQ_OBJS)

ifeq (cortexm3,$(CHIP_CORE))
    # Cortex M3
    C_OBJECTS += applet_cstartup.o
else
	# Objects built from Assembly source files
	ASM_OBJECTS = applet_cstartup.o
endif

# Append OBJ and BIN directories to output filename
OUTPUT := $(BIN)/$(OUTPUT)

#-------------------------------------------------------------------------------
#		Rules
#-------------------------------------------------------------------------------

all: $(BIN) $(OBJ) $(MEMORIES)

$(BIN) $(OBJ):
	mkdir $@

define RULES
C_OBJECTS_$(1) = $(addprefix $(OBJ)/$(1)_, $(C_OBJECTS))
ASM_OBJECTS_$(1) = $(addprefix $(OBJ)/$(1)_, $(ASM_OBJECTS))

$(1): $$(ASM_OBJECTS_$(1)) $$(C_OBJECTS_$(1)) 
	$(CC) $(LDFLAGS) -T"$(AT91LIB)/boards/$(BOARD)/$(CHIP)/$$@_samba.lds" -o $(OUTPUT).elf $$^
	$(OBJCOPY) -O binary $(OUTPUT).elf $(OUTPUT).bin
	$(SIZE) $$^ $(OUTPUT).elf
	@[ -e $(INSTALLDIR) ] || mkdir $(INSTALLDIR)
	@cp -f $(OUTPUT).bin $(INSTALLDIR)

$$(C_OBJECTS_$(1)): $(OBJ)/$(1)_%.o: %.c Makefile $(OBJ) $(BIN)
	$(CC) $(CFLAGS) -D$(1) -c -o $$@ $$<

$$(ASM_OBJECTS_$(1)): $(OBJ)/$(1)_%.o: %.S Makefile $(OBJ) $(BIN)
	$(CC) $(ASFLAGS) -D$(1) -c -o $$@ $$<

debug:
	perl ../../resources/gdb/debug.pl $(OUTPUT).elf

endef

$(foreach MEMORY, $(MEMORIES), $(eval $(call RULES,$(MEMORY))))

clean:
	-rm -f $(OBJ)/*.o $(BIN)/*.bin $(BIN)/*.elf $(BIN)/*.map

