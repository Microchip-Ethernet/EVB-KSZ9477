# ----------------------------------------------------------------------------
#         ATMEL Microcontroller Software Support 
# ----------------------------------------------------------------------------
# Copyright (c) 2012, Atmel Corporation
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

SERIE = sam9xx5
CHIP = sam9g15
DYN = ON

# Makefile for compiling libchip

SUBMAKE_FILES=debug.mk gcc.mk iar.mk mdk.mk release.mk win.mk linux.mk sam9xx5.mk
#SUBMAKE_OPTIONS=--no-builtin-rules --no-builtin-variables -d -p
SUBMAKE_OPTIONS=--no-builtin-rules --no-builtin-variables
SUBMAKE_VARS=

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------

all: $(CHIP)

$(CHIP): libchip_$(CHIP)_gcc_dbg.a libchip_$(CHIP)_gcc_rel.a

libchip_$(CHIP)_gcc_dbg.a:
	@echo --- Making $@
	@$(MAKE) CHIP=$(CHIP) DYN=$(DYN) DEBUG=1 $(SUBMAKE_OPTIONS) -f sam9xx5.mk

libchip_$(CHIP)_gcc_rel.a:
	@echo --- Making $@
	@$(MAKE) CHIP=$(CHIP) DYN=$(DYN) $(SUBMAKE_OPTIONS) -f sam9xx5.mk
  

.PHONY: clean
clean:
	
	@echo --- Cleaning $(CHIP)
	@$(MAKE) CHIP=$(CHIP) DYN=$(DYN) $(SUBMAKE_OPTIONS) -f $(SERIE).mk $@
	@$(MAKE) CHIP=$(CHIP) DYN=$(DYN) DEBUG=1 $(SUBMAKE_OPTIONS) -f sam9xx5.mk $@
  


