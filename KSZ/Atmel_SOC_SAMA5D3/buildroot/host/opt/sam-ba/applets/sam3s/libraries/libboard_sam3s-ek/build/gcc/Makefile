# ----------------------------------------------------------------------------
#         ATMEL Microcontroller Software Support 
# ----------------------------------------------------------------------------
# Copyright (c) 2010, Atmel Corporation
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

# Makefile for compiling libboard

#-------------------------------------------------------------------------------
# User-modifiable options
#-------------------------------------------------------------------------------

# Chip & board used for compilation
# (can be overriden by adding CHIP=chip and BOARD=board to the command-line)
SERIE = atsam3s
CHIP  = $(SERIE)4
BOARD = $(SERIE)-ek

# Trace level used for compilation
# (can be overriden by adding TRACE_LEVEL=#number to the command-line)
# TRACE_LEVEL_DEBUG      5
# TRACE_LEVEL_INFO       4
# TRACE_LEVEL_WARNING    3
# TRACE_LEVEL_ERROR      2
# TRACE_LEVEL_FATAL      1
# TRACE_LEVEL_NO_TRACE   0
ifdef DEBUG
TRACE_LEVEL = 3
else
TRACE_LEVEL = 0
endif

# Optimization level
# -O1 Optimize
# -O2 Optimize even more
# -O3 Optimize yet more
# -O0 Reduce compilation time and make debugging produce the expected results
# -Os Optimize for size
ifdef DEBUG
OPTIMIZATION = -g -O0 -D DEBUG
else
OPTIMIZATION = -Os
endif

#-------------------------------------------------------------------------------
# Path
#-------------------------------------------------------------------------------

# Output directories
ifdef DEBUG
BASE= debug
BIN = ../../lib
OBJ = debug/obj
else
BASE= release
BIN = ../../lib
OBJ = release/obj
endif

# Libraries
PATH_ATML_LIB_BOARD = ../..
PATH_ATML_LIB_CHIP = ../../../libchip_$(SERIE)

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

# Tool suffix when cross-compiling
CROSS_COMPILE = arm-none-eabi-

# Compilation tools
AR = $(CROSS_COMPILE)ar
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy

# Flags
INCLUDES  = -I$(PATH_ATML_LIB_CHIP)
INCLUDES += -I$(PATH_ATML_LIB_BOARD)

CFLAGS += -Wall -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int
CFLAGS += -Werror-implicit-function-declaration -Wmain -Wparentheses
CFLAGS += -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused
CFLAGS += -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef
CFLAGS += -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings
CFLAGS += -Wsign-compare -Waggregate-return -Wstrict-prototypes
CFLAGS += -Wmissing-prototypes -Wmissing-declarations
CFLAGS += -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations
CFLAGS += -Wpacked -Wredundant-decls -Wnested-externs -Winline -Wlong-long
CFLAGS += -Wunreachable-code
CFLAGS += -Wcast-align
#CFLAGS += -Wmissing-noreturn
#CFLAGS += -Wconversion

CFLAGS += -mcpu=cortex-m3 -mthumb -mlong-calls -ffunction-sections -DNDEBUG
CFLAGS += $(OPTIMIZATION) $(INCLUDES) -D$(CHIP) -DTRACE_LEVEL=$(TRACE_LEVEL)
ASFLAGS = -mcpu=cortex-m3 -mthumb -Wall -g $(OPTIMIZATION) $(INCLUDES) -D$(CHIP) -D__ASSEMBLY__

#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------
VPATH += $(PATH_ATML_LIB_BOARD)
VPATH += $(PATH_ATML_LIB_BOARD)/source
C_OBJECTS += $(OBJ)/at45d.o
C_OBJECTS += $(OBJ)/at45_spi.o
C_OBJECTS += $(OBJ)/board_lowlevel.o
C_OBJECTS += $(OBJ)/board_memories.o
C_OBJECTS += $(OBJ)/hamming.o
C_OBJECTS += $(OBJ)/trace.o
C_OBJECTS += $(OBJ)/uart_console.o

# Output file basename
ifdef DEBUG
OUTPUT = libboard_$(SERIE)_ek_gcc_dbg.a
else
OUTPUT = libboard_$(SERIE)_ek_gcc_rel.a
endif

#ifeq ( $(OS), 'Windows_NT' )
RM=del
RMDIR=del /f /q /s
#else
#RM=rm -f
#RMDIR=rm -fr
#endif

#	ifeq ( $(OS), 'Windows_NT' )
MV=move
#	else
#	MV=mv
#	endif

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------

all: $(BIN) $(OBJ) $(BIN)/$(OUTPUT)

$(BIN) $(OBJ):
	-mkdir $(BASE)
#ifeq ( $(OS), 'Windows_NT' )	
	-mkdir $(subst /,\,$@)
#else
	-mkdir $@
#endif

$(OBJ)/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ)/%.o : %.s
	$(AS) -c $(ASFLAGS) $< -o $@

$(BIN)/$(OUTPUT): $(C_OBJECTS)
	$(AR) -r $(BIN)/$(OUTPUT) $(C_OBJECTS)
#	$(MV) $(OUTPUT) $(BIN)

clean:
	-$(RM) $(C_OBJECTS) $(OUTPUT) $(BIN) $(OBJ)/*.*
	-$(RMDIR) debug
	-$(RMDIR) release

