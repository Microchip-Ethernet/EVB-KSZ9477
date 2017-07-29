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

set cidr_addr 0x400E0940
# *****************************************************************************
#                       CHIP NAME   CHIPID_CIDR
# *****************************************************************************
array set devicesList { at91sam3x8_0 0x284e0a60
                        at91sam3x8_1 0x285e0a60
                        at91sam3x8_2 0x286e0a60
                        at91sam3x8_3 0x284e0a30
                        at91sam3x8_4 0x285e0a30
                        at91sam3x8_5 0x286e0a30
                        at91sam3a8_0 0x283e0a60
                        at91sam3a8_1 0x283e0a30
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


namespace eval BOARD {
    variable sramSize         0x00018000
    variable maxBootSize      0
    # Vdd Memory 1.8V = 0 / Vdd Memory 3.3V = 1
    variable extRamVdd 1
    # External SDRAM = 0 / External DDR = 1 External PSRAM = 2
    variable extRamType 0
    # Set bus width (16 or 32)
    variable extRamDataBusWidth 16
    # DDRAM Model (not used)
    variable extDDRamModel 0
}

set target(board) at91sam3x8-ek

################################################################################
## PROCEDURES FOR COMPATIBILITY WITH OLDER SAM-BA VERSIONS AND USER DEFINED
################################################################################
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
    "SRAM 0"       "::at91sam3x8_sram0"
    "SRAM 1"       "::at91sam3x8_sram1"
    "SDRAM"        "::at91sam3x8_sdram"
    "NandFlash"    "::at91sam3x8_nandflash"
    "Flash"        "::at91sam3x8_flash"
    "Peripheral"   "::at91sam3x8_peripheral"
    "REMAP"        "::at91sam3x8_remap"
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
#LOWLEVEL::Init

################################################################################
## SRAM
################################################################################
array set at91sam3x8_sram0 {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x20000000
    dftSize     0x10000
    dftSend     "RAM::sendFile"
    dftReceive  "RAM::receiveFile"
    dftScripts  ""
}

array set at91sam3x8_sram1 {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x20080000
    dftSize     0x8000
    dftSend     "RAM::sendFile"
    dftReceive  "RAM::receiveFile"
    dftScripts  ""
}

################################################################################
## SDRAM
################################################################################
array set at91sam3x8_sdram {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x70000000
    dftSize     "$GENERIC::memorySize"
    dftSend     "RAM::sendFile"
    dftReceive  "RAM::receiveFile"
    dftScripts  "::at91sam3x8_sdram_scripts"
}

puts "-I- External RAM Settings :  extRamVdd=$BOARD::extRamVdd, extRamType=$BOARD::extRamType, extRamDataBusWidth=$BOARD::extRamDataBusWidth, extDDRamModel=$BOARD::extDDRamModel"

set RAM::appletAddr          0x20001000
set RAM::appletMailboxAddr   0x20001040
set RAM::appletFileName      "$libPath(extLib)/$target(board)/applet-extram-sam3x8.bin"

array set at91sam3x8_sdram_scripts {
    "Enable SDRAM"   "GENERIC::Init $RAM::appletAddr $RAM::appletMailboxAddr $RAM::appletFileName [list $::target(comType) $::target(traceLevel) $BOARD::extRamVdd $BOARD::extRamType $BOARD::extRamDataBusWidth $BOARD::extDDRamModel]"
}

################################################################################
## NANDFLASH
################################################################################
array set at91sam3x8_nandflash {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x0
    dftSize     "$GENERIC::memorySize"
    dftSend     "GENERIC::SendFile"
    dftReceive  "GENERIC::ReceiveFile"
    dftScripts  "::at91sam3x8_nandflash_scripts"
}

array set at91sam3x8_nandflash_scripts {
    "Enable NandFlash"    "NANDFLASH::Init"
    "Erase All"           "GENERIC::EraseAll"
    "Scrub NandFlash"     "GENERIC::EraseAll $NANDFLASH::scrubErase"
    "List Bad Blocks"     "NANDFLASH::BadBlockList"
}
set NANDFLASH::appletAddr          0x20001000
set NANDFLASH::appletMailboxAddr   0x20001040
set NANDFLASH::appletFileName      "$libPath(extLib)/$target(board)/applet-nandflash-sam3x8.bin"

################################################################################
## FLASH
################################################################################
array set at91sam3x8_flash {
    dftDisplay  1
    dftDefault  1
    dftAddress  0x80000
    dftSize     0x80000
    dftSend     "FLASH::SendFile"
    dftReceive  "FLASH::ReceiveFile"
    dftScripts  "::at91sam3x8_flash_scripts"
}
array set at91sam3x8_flash_scripts {
        "Enable Security Bit (GPNVM0)"         "FLASH::ScriptGPNMV 0"
        "Boot from Flash (GPNVM1)"             "FLASH::ScriptGPNMV 2"
        "Boot from ROM (GPNVM1)"               "FLASH::ScriptGPNMV 3"
        "Select Flash0 for boot (GPNVM2)"      "FLASH::ScriptGPNMV 5"
        "Select Flash1 for boot (GPNVM2)"      "FLASH::ScriptGPNMV 4"
        "Erase All Flash"                      "FLASH::EraseAll"
        "Enable Flash access"                  "FLASH::Init "
        "Read unique ID"                          "FLASH::ReadUniqueID"
}

set FLASH::appletAddr             0x20001000
set FLASH::appletMailboxAddr      0x20001040
set FLASH::appletFileName         "$libPath(extLib)/$target(board)/applet-flash-sam3x8.bin"

# Initialize SDRAM
#if {[catch {GENERIC::Init $RAM::appletAddr $RAM::appletMailboxAddr $RAM::appletFileName [list $::target(comType) $::target(traceLevel) $BOARD::extRamVdd $BOARD::extRamType $BOARD::extRamDataBusWidth $BOARD::extDDRamModel]} dummy_err] } {
#    set continue no
#    if {$commandLineMode == 0} {
#        set continue [tk_messageBox -title "External RAM init" -message "External RAM initialization failed.\nExternal RAM access is required to run applets.\nContinue anyway ?" -icon warning -type yesno]
#    } else {
#        puts "-E- Error during external RAM initialization."
#        puts "-E- External RAM access is required to run applets."
#        puts "-E- Connection abort"
#    }
#    # Close link
#    if {$continue == no} {
#        TCL_Close $target(handle)
#        exit
#    }
#} else {
#    puts "-I- External RAM initialized"
#}

# Initialize FLASH
if {[catch {FLASH::Init} dummy_err]} {
    if {$commandLineMode == 0} {
        tk_messageBox -title "FLASH init" -message "Failed to initialize FLASH access" -icon error -type ok
    } else {
        puts "-E- Error during FLASH initialization"
        puts "-E- Connection abort"
    }
    # Close link
    TCL_Close $target(handle)
    exit
} else {
    puts "-I- FLASH initialized"
}

################################################################################
array set at91sam3x8_peripheral {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x40000000
    dftSize     0x10000000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

array set at91sam3x8_remap {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x00000000
    dftSize     0x40000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}
