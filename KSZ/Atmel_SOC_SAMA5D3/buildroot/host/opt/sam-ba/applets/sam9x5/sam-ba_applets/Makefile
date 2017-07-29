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

# Note: SAM9G15 applets also use for SAM9G25,SAM9G35,SAM9X25,SAM9X35

all: libboard libchip libnanflash libpmecc libspiflash liboweeprom applets

libchip:
	(cd ../libraries/libchip_sam9xx5/build/gcc && $(MAKE) CHIP=sam9g15 DYN=ON -f Makefile clean all)

libboard:
	(cd ../libraries/libboard_sam9xx5-ek/build/gcc && $(MAKE) CHIP=sam9g15 DYN=ON -f Makefile clean all)

libnanflash:
	(cd ../libraries/libnandflash/build/gcc && $(MAKE) DYN=ON PMECC_ALGO_ROM=ON -f Makefile clean all)

libpmecc:
	(cd ../libraries/libpmecc/build/gcc && $(MAKE) DYN=ON PMECC_ALGO_ROM=ON -f Makefile clean all)

libspiflash:
	(cd ../libraries/libspiflash/build/gcc && $(MAKE) DYN=ON -f Makefile clean all)

liboweeprom:
	(cd ../libraries/liboweeprom/build/gcc && $(MAKE) DYN=ON -f Makefile clean all)

applets:
	(cd lowlevelinit && $(MAKE) CHIP=sam9g15 DYN=ON -f Makefile clean all)
	
	(cd eeprom && $(MAKE) CHIP=sam9g15 DYN=ON -f Makefile clean all)
	
	(cd oweeprom && $(MAKE) CHIP=sam9g15 DYN=ON -f Makefile clean all)
	
	(cd extram && $(MAKE) CHIP=sam9g15 DYN=ON -f Makefile clean all) 
	
	(cd nandflash && $(MAKE) CHIP=sam9g15 DYN=ON -f Makefile clean all) 
	
	(cd serialflash && $(MAKE) CHIP=sam9g15 DYN=ON -f Makefile clean all) 
	
	(cd dataflash && $(MAKE) CHIP=sam9g15 DYN=ON -f Makefile clean all) 
	