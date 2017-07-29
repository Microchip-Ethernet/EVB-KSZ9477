#  ----------------------------------------------------------------------------
#          ATMEL Microcontroller Software Support
#  ----------------------------------------------------------------------------
#  Copyright (c) 2014, Atmel Corporation
#
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of source code must retain the above copyright notice,
#  this list of conditions and the disclaimer below.
#
#  Atmel's name may not be used to endorse or promote products derived from
#  this software without specific prior written permission. 
#
#  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
#  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
#  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#  ----------------------------------------------------------------------------


set cidr_addr 0xFC069040
# *****************************************************************************
#                       CHIP NAME   CHIPID_CIDR
# *****************************************************************************
array set devicesList { at91sama5d4x_0 0x8a5c07c1
                        at91sama5d4x_1 0x8a5c0760
                      }
global target
global commandLineMode
set isValidChipOfBoard 0
set version_mask 0xFFFFFFE0
set chipname_list [array names ::devicesList]
set chip_id [format "0x%08x" [TCL_Read_Int $target(handle) $cidr_addr err_code]]
puts "Read device Chip ID at $cidr_addr --- get $chip_id"
set proc_id_masked [format "0x%08x" [expr $chip_id & $version_mask]]
foreach {key value} [array get devicesList] {
   set masked_chipId_Cidr [format "0x%08x" [expr $value & $version_mask]]
   if {[regexp $proc_id_masked $masked_chipId_Cidr] != 0} {
       puts "-I- Found chip : $key (Chip ID : $chip_id)"
       set isValidChipOfBoard 1
       break
   }
} 

if { $isValidChipOfBoard == 0 } {
    if { $commandLineMode == 1 } {
        puts "-E- Invalid device or board!"
    } else {
        tk_messageBox -title "Invalid chip ID" -message "Can't connect $target(board)\n" -icon error -type ok
    }
    TCL_Close $target(handle)
    exit
}

################################################################################
## BOARD SPECIFIC PARAMETERS
################################################################################
namespace eval BOARD {
    variable sramSize         0x20000
    variable maxBootSize      [expr 60 * 1024]

# Supported setting for DRAM
  
    #default DDR model for sama5d4-ek board
    variable extDDRamModel 2

    if {[regexp "xplained" $target(board)]} {
        # DDR2 (MT47H128M16-25E X 2) for sama5d4-xplained 
        set extDDRamModel 3
    }
   
    # All supported DDR devices:

    # 1：LPDDR1 (MT46H128M16LFCK_5 X 2)
    # 2: DDR2 (MT47H128M8CF-25E X 4)
    # 3：DDR2 (MT47H128M16-25E X 2):
    # 4：DDR2 (MT47H64M16-25 X 2):
    # 5：LPDDR2 (MT42L128M32D1GU-25 X 2): 
    # 6：LPDDR2 (MT42L128M16D1KL-25 X 4): 

    # 1：LPDDR1 (MT46H128M16LFCK_5)
    #    * 1.8V
    #    * 32 Meg x 16 x 4 Banks
    #    * 256MB x 2 chip = 512MB

    # 2: DDR2 (MT47H128M8CF-25E)
    #    * 1.8V
    #    * 128 Meg x 8 (16 Meg x 8 x 8 banks)
    #    * 128MB x 4 chip = 512MB

    # 3：DDR2 (MT47H128M16-25E X 2):
    #    * 1.8V
    #    * 128 Meg x 16 (16 Meg x 16 x 8 banks) 
    #    * 256MB x 2 chip = 512MB

    # 4：DDR2 (MT47H64M16-25 X 2):
    #    * 1.8V
    #    * 64 Meg x 16 (8 Meg x 16 x 8 banks) 
    #    * 128MB x 2 chip = 256MB

    # 5：LPDDR2 (MT42L128M32D1GU-25): 
    #    * 1.2V
    #    * 8 Meg x 32 x 8 banks x 2 die 
    #    * 512MB x 2 chip = 1G

    # 6：LPDDR2 (MT42L128M16D1KL-25): 
    #    * 1.2V
    #    * 8 Meg x 16 x 8 banks x 2 die 
    #    * 256MB x 4 chip = 1G

    variable eepromDeviceAddress 0x51
    # Note: DEVICE/ADDRESSES (A2, A1, A0): The A2, A1 or A0 pins are device address inputs 
    # that are hardwired or left not connected for hardware compatibility with other AT24CXX devices.
    # Modify 'eepromDeviceAddress' to meet the hardware connection.
   
}

set target(board) at91sama5d4x-ek

# Source procedures for compatibility with older SAM-BA versions
if { [ catch { source "$libPath(extLib)/common/functions.tcl"} errMsg] } {
    if {$commandLineMode == 0} {
        tk_messageBox -title "File not found" -message "Function file not found:\n$errMsg" -type ok -icon error
    } else {
        puts "-E- Function file not found:\n$errMsg"
        puts "-E- Connection abort"
    }
    exit
}

array set memoryAlgo {
    "SRAM"                    "::sama5d4x_sram"
    "DDRAM"                   "::sama5d4x_ddram"
    "SD / eMMC"               "::sama5d4x_sdmmc"
    "SerialFlash AT25/AT26"   "::sama5d4x_serialflash"
    "NandFlash"               "::sama5d4x_nandflash"
    "One-wire EEPROM"         "::sama5d4x_ow"
    "DDR2 / SDRAM Map"        "::sama5d4x_ddr2_sdram_map"
    "Peripheral"              "::sama5d4x_peripheral"
    "ROM"                     "::sama5d4x_rom"
    "REMAP"                   "::sama5d4x_remap"
}


################################################################################
## Low Level Initialization
################################################################################
if { [ catch { source "$libPath(extLib)/$target(board)/lowlevelinit.tcl"} errMsg] } {
    set continue no
    if {$commandLineMode == 0} {
        set continue [tk_messageBox -title "File not found" -message "Low level initialization file not found.\nContinue anyway ?" -icon warning -type yesno]
    } else {
        puts "-E- Low level initialization file not found."
        puts "-E- Connection abort!"
    }

    if {$continue == no} {
        TCL_Close $target(handle)
        exit
    }
}
LOWLEVEL::Init

################################################################################
## SRAM
################################################################################
array set sama5d4x_sram {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x00200000
    dftSize     0x20000
    dftSend     "RAM::sendFile"
    dftReceive  "RAM::receiveFile"
    dftScripts  ""
}


################################################################################
## DDRAM
################################################################################
array set sama5d4x_ddram {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x20000000
    dftSize     "$GENERIC::memorySize"
    dftSend     "RAM::sendFile"
    dftReceive  "RAM::receiveFile"
    dftScripts  "::sama5d4x_ddram_scripts"
}

set RAM::appletAddr          0x200000
set RAM::appletMailboxAddr   0x200004
set RAM::appletFileName      "$libPath(extLib)/$target(board)/applet-extram-sama5d4x.bin"

array set sama5d4x_ddram_scripts {
    "Enable DDRAM"   "GENERIC::Init $RAM::appletAddr $RAM::appletMailboxAddr $RAM::appletFileName [list $::target(comType) $::target(traceLevel) $BOARD::extDDRamModel]"
}


# Initialize SDRAM/DDRAM
if {[catch {GENERIC::Init $RAM::appletAddr $RAM::appletMailboxAddr $RAM::appletFileName [list $::target(comType) $::target(traceLevel) $BOARD::extDDRamModel]} dummy_err] } {
    set continue no
    if {$commandLineMode == 0} {
        set continue [tk_messageBox -title "External RAM init" -message "External RAM initialization failed.\nExternal RAM access is required to run applets.\nContinue anyway ?" -icon warning -type yesno]
    } else {
        puts "-E- Error during external RAM initialization."
        puts "-E- External RAM access is required to run applets."
        puts "-E- Connection abort"
    }
    # Close link
    if {$continue == no} {
        TCL_Close $target(handle)
        exit
    }
} else {
        puts "-I- External RAM initialized"
}

################################################################################
## SERIALFLASH
################################################################################
array set sama5d4x_serialflash {
    dftDisplay  1
    dftDefault  1
    dftAddress  0x0
    dftSize     "$GENERIC::memorySize"
    dftSend     "GENERIC::SendFile"
    dftReceive  "GENERIC::ReceiveFile"
    dftScripts  "::sama5d4x_serialflash_scripts"
}

array set sama5d4x_serialflash_scripts {
    "Enable Serialflash (SPI0 CS0)"   "SERIALFLASH::Init 0"
    "Send Boot File"                  "GENERIC::SendBootFileGUI"
    "Erase All"                       "SERIALFLASH::EraseAll"
}

set SERIALFLASH::appletAddr          0x20000000
set SERIALFLASH::appletMailboxAddr   0x20000004
set SERIALFLASH::appletFileName      "$libPath(extLib)/$target(board)/applet-serialflash-sama5d4x.bin"

################################################################################
## One-Wire EEPROM
################################################################################
array set sama5d4x_ow {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x0
    dftSize     "$GENERIC::memorySize"
    dftSend     "GENERIC::SendFile"
    dftReceive  "GENERIC::ReceiveFile"
    dftScripts  "::sama5d4x_ow_scripts"
}

array set sama5d4x_ow_scripts {
    "Search One-Wire EEPROM"    "OW::Init"
    "Select Target One-Wire EEPROM"   "OW::SelectDevice"
}

set OW::appletAddr          0x200000
set OW::appletMailboxAddr   0x200004
set OW::appletFileName      "$libPath(extLib)/$target(board)/applet-oweeprom-sama5d4x.bin"

################################################################################
## NANDFLASH
################################################################################
array set sama5d4x_nandflash {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x0
    dftSize     "$GENERIC::memorySize"
    dftSend     "GENERIC::SendFile"
    dftReceive  "GENERIC::ReceiveFile"
    dftScripts  "::sama5d4x_nandflash_scripts"
}

array set sama5d4x_nandflash_scripts {
    "Enable NandFlash"             "NANDFLASH::Init"
    "Enable OS PMECC parameters"   "NANDFLASH::NandHeaderValue HEADER 0xc1e04e07"
    "Pmecc configuration"          "NANDFLASH::NandHeaderValue"
    "Send Boot File"               "NANDFLASH::SendBootFilePmecc"
    "Erase All"                    "NANDFLASH::EraseAll"
    "Scrub NandFlash"              "NANDFLASH::EraseAll $NANDFLASH::scrubErase"
    "List Bad Blocks"              "NANDFLASH::BadBlockList"
}

set NANDFLASH::appletAddr          0x20000000
set NANDFLASH::appletMailboxAddr   0x20000004
set NANDFLASH::appletFileName      "$libPath(extLib)/$target(board)/applet-nandflash-sama5d4x.bin"


################################################################################
## SDMMC
################################################################################
array set sama5d4x_sdmmc {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x0
    dftSize     "$GENERIC::memorySize"
    dftSend     "GENERIC::SendFile"
    dftReceive  "GENERIC::ReceiveFile"
    dftScripts  "::sama5d4x_sdmmc_scripts"
}

array set sama5d4x_sdmmc_scripts {
    "Launch SD/eMMC MassStorage "           "SDMMC::Init"
}

set SDMMC::appletAddr          0x20000000
set SDMMC::appletFileName      "$libPath(extLib)/$target(board)/sdmmc-massstorage.bin"


array set sama5d4x_ddr2_sdram_map {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x20000000
    dftSize     0x10000000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

array set sama5d4x_norflash_map {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x10000000
    dftSize     0x10000000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}
array set sama5d4x_peripheral {
    dftDisplay  0
    dftDefault  0
    dftAddress  0xF0000000
    dftSize     0x10000000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

array set sama5d4x_rom {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x100000
    dftSize     0x8000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

array set sama5d4x_remap {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x00000000
    dftSize     0x8000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

