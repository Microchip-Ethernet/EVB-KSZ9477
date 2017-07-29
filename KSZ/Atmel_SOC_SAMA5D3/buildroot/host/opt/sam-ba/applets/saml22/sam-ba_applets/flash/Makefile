# ----------------------------------------------------------------------------
#         SAM Software Package License
# ----------------------------------------------------------------------------
# Copyright (c) 2013, Atmel Corporation
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

# Makefile for compiling applet-flash

#-------------------------------------------------------------------------------
# User-modifiable options
#-------------------------------------------------------------------------------

# Chip & board used for compilation
# (can be overriden by adding CHIP=chip and BOARD=board to the command-line)
SERIE = saml22
CHIP  = $(SERIE)n18a
BOARD = $(SERIE)_xplained_pro

ifeq (saml22n18a,$(CHIP))
BOARD_DIR = saml22_xplained_pro
CHIP_NAME  = __SAML22N18A__
endif

MEMORIES = sram

# Trace level used for compilation
# (can be overriden by adding TRACE_LEVEL=#number to the command-line)
# TRACE_LEVEL_DEBUG      5
# TRACE_LEVEL_INFO       4
# TRACE_LEVEL_WARNING    3
# TRACE_LEVEL_ERROR      2
# TRACE_LEVEL_FATAL      1
# TRACE_LEVEL_NO_TRACE   0
#TRACE_LEVEL = 0    # use dynamic trace level instead

# Optimization level
# -O1 Optimize
# -O2 Optimize even more
# -O3 Optimize yet more
# -O0 Reduce compilation time and make debugging produce the expected results
# -Os Optimize for size

OPTIMIZATION = -Os

#-------------------------------------------------------------------------------
# Path
#-------------------------------------------------------------------------------

# Output file basename
OUTPUT = applet-flash-$(CHIP)

# Output directories
BIN = bin
OBJ = obj

# Libraries
SAMBA = ..
INSTALLDIR = "../../../../tcl_lib/$(BOARD_DIR)/"
APPLET_LINKER_SCRIPT = "../linker_script/sram_samba.lds"

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
OBJDUMP = $(CROSS_COMPILE)objdump

# Flags
ASF_BRANCH_PATH = ../../libraries
INCLUDES += -I$(ASF_BRANCH_PATH)/common/utils
INCLUDES += -I$(ASF_BRANCH_PATH)/common/utils/interrupt
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/utils
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/utils/header_files
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/utils/preprocessor
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/utils/cmsis/saml22/include
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/utils/cmsis/saml22/source
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/drivers/system
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/drivers/system/clock
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/drivers/system/clock/clock_saml22
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/drivers/system/pinmux
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/drivers/system/interrupt
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/drivers/system/interrupt/system_interrupt_saml22
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/drivers/system/reset/reset_sam_l
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/drivers/system/power/power_sam_l
INCLUDES += -I$(ASF_BRANCH_PATH)/sam0/drivers/nvm
INCLUDES += -I$(ASF_BRANCH_PATH)/thirdparty/CMSIS
INCLUDES += -I$(ASF_BRANCH_PATH)/thirdparty/CMSIS/Include

CFLAGS += -mthumb -mcpu=cortex-m0plus -mlong-calls -ffunction-sections -Wall -DNDEBUG -D__SAMBA__ -DARM_MATH_CM0=true
CFLAGS += -g $(OPTIMIZATION) $(INCLUDES) -D$(CHIP_NAME)
CFLAGS += -DDYN_TRACES
#CFLAGS += -v
CFLAGS += -c -g
CFLAGS += -DTRACE_LEVEL=$(TRACE_LEVEL)
CFLAGS += -std=gnu99
ASFLAGS = -mthumb -Wall -g $(OPTIMIZATION) $(INCLUDES) -D$(CHIP_NAME)
# -D__ASSEMBLY__
LDFLAGS = -g $(OPTIMIZATION) -nostartfiles -mthumb -mcpu=cortex-m0plus -Wl,-Map=$(OUTPUT).map,--cref,--gc-sections

#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------
VPATH += $(SAMBA)/common
VPATH += $(ASF_BRANCH_PATH)\sam0\utils
VPATH += $(ASF_BRANCH_PATH)\common\utils\interrupt
VPATH += $(ASF_BRANCH_PATH)\sam0\drivers\nvm
VPATH += $(ASF_BRANCH_PATH)\sam0\drivers\system

C_OBJECTS += interrupt_sam_nvic.o
C_OBJECTS += nvm.o
C_OBJECTS += system.o
C_OBJECTS += flash_app_main.o
C_OBJECTS += applet_cstartup.o


# Append OBJ and BIN directories to output filename
OUTPUT := $(BIN)/$(OUTPUT)

MEMORIES = sram

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------

all: $(BIN) $(OBJ) $(MEMORIES)

$(BIN) $(OBJ):
	mkdir $@

define RULES
C_OBJECTS_$(1) = $(addprefix $(OBJ)/$(1)_, $(C_OBJECTS))
ASM_OBJECTS_$(1) = $(addprefix $(OBJ)/$(1)_, $(ASM_OBJECTS))

$(1): $$(ASM_OBJECTS_$(1)) $$(C_OBJECTS_$(1))
	@$(CC) $(LDFLAGS) -T"$(APPLET_LINKER_SCRIPT)" -o $(OUTPUT).elf $$^
	$(OBJCOPY) -O binary $(OUTPUT).elf $(OUTPUT).bin
	$(SIZE) $$^ $(OUTPUT).elf
	$(OBJDUMP) -h -S $(OUTPUT).elf > $(OUTPUT).lss
	@[ -e $(INSTALLDIR) ] || mkdir $(INSTALLDIR)
	@cp -f $(OUTPUT).bin $(INSTALLDIR)
	@$(OBJDUMP) -S $(OUTPUT).elf > $(OUTPUT)_dis.txt
	
$$(C_OBJECTS_$(1)): $(OBJ)/$(1)_%.o: %.c Makefile $(OBJ) $(BIN)
	@$(CC) $(CFLAGS) -D$(1) -c -o $$@ $$<

$$(ASM_OBJECTS_$(1)): $(OBJ)/$(1)_%.o: %.S Makefile $(OBJ) $(BIN)
	@$(CC) $(ASFLAGS) -D$(1) -c -o $$@ $$<

endef

$(foreach MEMORY, $(MEMORIES), $(eval $(call RULES,$(MEMORY))))

clean:
	-rm -fR $(OBJ) $(BIN)
