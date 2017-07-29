# ----------------------------------------------------------------------------
#         SAM Software Package License
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

all: applets

applets:
	(cd dataflash && $(MAKE) BOARD=at91sam7a3-ek CHIP=at91sam7a3 MEMORIES=sram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se256 MEMORIES=sdram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se32 MEMORIES=sdram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se512 MEMORIES=sdram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x128 MEMORIES=sram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x256 MEMORIES=sram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x512 MEMORIES=sram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9260-ek CHIP=at91sam9260 MEMORIES=sdram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9261-ek CHIP=at91sam9261 MEMORIES=sram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9263-ek CHIP=at91sam9263 MEMORIES=sram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9g10-ek CHIP=at91sam9g10 MEMORIES=sdram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9g20-ek CHIP=at91sam9g20 MEMORIES=sram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9m10-ek CHIP=at91sam9m10 MEMORIES=sram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9rl-ek CHIP=at91sam9rl64 MEMORIES=sram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe128 MEMORIES=sdram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe256 MEMORIES=sdram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe512 MEMORIES=sdram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91cap9-dk CHIP=at91cap9 MEMORIES=sdram -f Makefile clean all)
	(cd dataflash && $(MAKE) BOARD=at91cap9-stk CHIP=at91cap9 MEMORIES=sdram -f Makefile clean all)
	
	(cd eeprom && $(MAKE) BOARD=at91sam7a3-ek CHIP=at91sam7a3 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s128 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s256 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s512 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s64 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se256 MEMORIES=sdram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se32 MEMORIES=sdram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se512 MEMORIES=sdram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x128 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x256 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x512 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9260-ek CHIP=at91sam9260 MEMORIES=sdram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9261-ek CHIP=at91sam9261 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9263-ek CHIP=at91sam9263 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9g10-ek CHIP=at91sam9g10 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9g20-ek CHIP=at91sam9g20 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9m10-ek CHIP=at91sam9m10 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9rl-ek CHIP=at91sam9rl64 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe128 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe256 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe512 MEMORIES=sram -f Makefile clean all) 
	(cd eeprom && $(MAKE) BOARD=at91cap9-dk CHIP=at91cap9 MEMORIES=sram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91cap9-dk CHIP=at91cap9 MEMORIES=sdram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91cap9-stk CHIP=at91cap9 MEMORIES=sdram -f Makefile clean all)
	(cd eeprom && $(MAKE) BOARD=at91cap9-stk CHIP=at91cap9 MEMORIES=sram -f Makefile clean all)


	(cd extram && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u1 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u2 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u4 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se256 MEMORIES=sram Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se32 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se512 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9260-ek CHIP=at91sam9260 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9261-ek CHIP=at91sam9261 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9263-ek CHIP=at91sam9263 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9g10-ek CHIP=at91sam9g10 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9g20-ek CHIP=at91sam9g20 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9m10-ek CHIP=at91sam9m10 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9rl-ek CHIP=at91sam9rl64 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe128 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe256 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe512 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91cap9-dk CHIP=at91cap9 MEMORIES=sram -f Makefile clean all)
	(cd extram && $(MAKE) BOARD=at91cap9-stk CHIP=at91cap9 MEMORIES=sram -f Makefile clean all)
	
	(cd flash && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u1 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u2 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u4 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7a3-ek CHIP=at91sam7a3 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7l-ek CHIP=at91sam7l128 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7l-ek CHIP=at91sam7l64 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s128 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s256 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s161 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s32 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s321 MEMORIES=sram -f Makefile clean all) 
	(cd flash && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s512 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s64 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se256 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se32 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se512 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x128 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x256 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x512 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe128 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe256 MEMORIES=sram -f Makefile clean all)
	(cd flash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe512 MEMORIES=sram -f Makefile clean all)

	(cd lowlevelinit && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u1 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u2 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u4 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9260-ek CHIP=at91sam9260 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9261-ek CHIP=at91sam9261 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9263-ek CHIP=at91sam9263 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9g10-ek CHIP=at91sam9g10 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9g20-ek CHIP=at91sam9g20 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9m10-ek CHIP=at91sam9m10 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9rl-ek CHIP=at91sam9rl64 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe128 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe256 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe512 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91cap9-dk CHIP=at91cap9 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91cap9-stk CHIP=at91cap9 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7a3-ek CHIP=at91sam7a3 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7l-ek CHIP=at91sam7l128 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7l-ek CHIP=at91sam7l64 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s128 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s256 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s161 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s32 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s321 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s512 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7s-ek CHIP=at91sam7s64 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se256 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se32 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se512 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x128 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x256 MEMORIES=sram -f Makefile clean all)
	(cd lowlevelinit && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x512 MEMORIES=sram -f Makefile clean all)
	
	(cd nandflash && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u1 MEMORIES=sram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u2 MEMORIES=sram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam3u-ek CHIP=at91sam3u4 MEMORIES=sram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se256 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se32 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se512 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9260-ek CHIP=at91sam9260 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9261-ek CHIP=at91sam9261 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9263-ek CHIP=at91sam9263 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9g10-ek CHIP=at91sam9g10 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9g20-ek CHIP=at91sam9g20 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9m10-ek CHIP=at91sam9m10 MEMORIES=ddram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9rl-ek CHIP=at91sam9rl64 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe128 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe256 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe512 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91cap9-dk CHIP=at91cap9 MEMORIES=sdram -f Makefile clean all)
	(cd nandflash && $(MAKE) BOARD=at91cap9-stk CHIP=at91cap9 MEMORIES=sdram -f Makefile clean all)
	
	(cd norflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se256 MEMORIES=sdram -f Makefile clean all)
	(cd norflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se32 MEMORIES=sdram -f Makefile clean all)
	(cd norflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se512 MEMORIES=sdram -f Makefile clean all)
	(cd norflash && $(MAKE) BOARD=at91sam9260-ek CHIP=at91sam9260 MEMORIES=sdram -f Makefile clean all)
	(cd norflash && $(MAKE) BOARD=at91sam9261-ek CHIP=at91sam9261 MEMORIES=sdram -f Makefile clean all) 
	(cd norflash && $(MAKE) BOARD=at91sam9263-ek CHIP=at91sam9263 MEMORIES=sdram -f Makefile clean all) 
	(cd norflash && $(MAKE) BOARD=at91sam9g10-ek CHIP=at91sam9g10 MEMORIES=sdram -f Makefile clean all) 
	(cd norflash && $(MAKE) BOARD=at91sam9g20-ek CHIP=at91sam9g20 MEMORIES=sdram -f Makefile clean all) 
	(cd norflash && $(MAKE) BOARD=at91sam9m10-ek CHIP=at91sam9m10 MEMORIES=ddram -f Makefile clean all) 
	(cd norflash && $(MAKE) BOARD=at91sam9rl-ek CHIP=at91sam9rl64 MEMORIES=sdram -f Makefile clean all) 
	(cd norflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe128 MEMORIES=sdram -f Makefile clean all) 
	(cd norflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe256 MEMORIES=sdram -f Makefile clean all) 
	(cd norflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe512 MEMORIES=sdram -f Makefile clean all) 
	(cd norflash && $(MAKE) BOARD=at91cap9-dk CHIP=at91cap9 MEMORIES=sdram -f Makefile clean all) 
	
	(cd rommonitor && $(MAKE) BOARD=at91sam9m10-ek CHIP=at91sam9m10 MEMORIES=sram -f Makefile clean all) 

	(cd serialflash && $(MAKE) BOARD=at91sam7a3-ek CHIP=at91sam7a3 MEMORIES=sram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se256 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se32 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam7se-ek CHIP=at91sam7se512 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x128 MEMORIES=sram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x256 MEMORIES=sram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam7x-ek CHIP=at91sam7x512 MEMORIES=sram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9260-ek CHIP=at91sam9260 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9261-ek CHIP=at91sam9261 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9263-ek CHIP=at91sam9263 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9g10-ek CHIP=at91sam9g10 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9g20-ek CHIP=at91sam9g20 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9m10-ek CHIP=at91sam9m10 MEMORIES=sram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9rl-ek CHIP=at91sam9rl64 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe128 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe256 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91sam9xe-ek CHIP=at91sam9xe512 MEMORIES=sdram -f Makefile clean all) 
	(cd serialflash && $(MAKE) BOARD=at91cap9-dk CHIP=at91cap9 MEMORIES=sdram -f Makefile clean all) 
	


