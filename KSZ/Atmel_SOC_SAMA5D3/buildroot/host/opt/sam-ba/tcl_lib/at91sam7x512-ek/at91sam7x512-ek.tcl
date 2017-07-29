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

set cidr_addr 0xFFFFF240
# *****************************************************************************
#                       CHIP NAME   CHIPID_CIDR
# *****************************************************************************
array set devicesList { at91sam7x512  0x275c0a40
                        at91sam7xc512 0x271c0a40
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
    variable maxBootSize      0
}

set target(board) at91sam7x512-ek

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
    "SRAM"                    "::at91sam7x512_sram"
    "Flash"                   "::at91sam7x512_flash"
    "DataFlash AT45DB/DCB"    "::at91sam7x512_dataflash"
    "SerialFlash AT25/AT26"	  "::at91sam7x512_serialflash"
    "EEPROM AT24"             "::at91sam7x512_eeprom"
    "Peripheral"              "::at91sam7x512_peripheral"
    "ROM"                     "::at91sam7x512_rom"
    "REMAP"                   "::at91sam7x512_remap"
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
array set at91sam7x512_sram {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x200000
    dftSize     0x20000
    dftSend     "RAM::sendFile"
    dftReceive  "RAM::receiveFile"
    dftScripts  ""
}

################################################################################
## FLASH
################################################################################
array set at91sam7x512_flash {
    dftDisplay  1
    dftDefault  1
    dftAddress  0x100000
    dftSize     0x80000
    dftSend     "FLASH::SendFile"
    dftReceive  "FLASH::ReceiveFile"
    dftScripts  "::at91sam7x512_flash_scripts"
}
set FLASH::appletAddr          0x202000
set FLASH::appletMailboxAddr   0x202004
set FLASH::appletFileName      "$libPath(extLib)/$target(board)/applet-flash-at91sam7x512.bin"

array set at91sam7x512_flash_scripts {
    "Erase All Flash"                      "FLASH::EraseAll"
    "Enable BrownOut Detector (GPNVM0)"    "FLASH::ScriptGPNMV 0"
    "Disable BrownOut Detector (GPNVM0)"   "FLASH::ScriptGPNMV 1"
    "Enable BrownOut Reset (GPNVM1)"       "FLASH::ScriptGPNMV 2"
    "Disable BrownOut Reset (GPNVM1)"      "FLASH::ScriptGPNMV 3"
    "Boot from Flash (GPNVM2)"             "FLASH::ScriptGPNMV 4"
    "Boot from ROM (GPNVM2)"               "FLASH::ScriptGPNMV 5"
    "Enable Security Bit"                  "FLASH::ScriptSetSecurityBit"
    "Enable Flash access"                  "FLASH::Init"
}
# Initialize FLASH
if {[catch {FLASH::Init } dummy_err] } {
    set continue no
    if {$commandLineMode == 0} {
        set continue [tk_messageBox -title "FLASH init" -message "Failed to initialize FLASH accesses.\nContinue anyway ?" -icon warning -type yesno]
    } else {
        puts "-E- Error during FLASH initialization."
    }
    # Close link
    if {$continue == no} {
        TCL_Close $target(handle)
        exit
    }
} else {
        puts "-I- FLASH initialized"
}

################################################################################
## DATAFLASH
################################################################################
array set at91sam7x512_dataflash {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x0
    dftSize     "$GENERIC::memorySize"
    dftSend     "GENERIC::SendFile"
    dftReceive  "GENERIC::ReceiveFile"
    dftScripts  "::at91sam7x512_dataflash_scripts"
}

array set at91sam7x512_dataflash_scripts {
    "Enable Dataflash (SPI0 CS0)"                        "DATAFLASH::Init 1"
    "Enable Dataflash (SPI0 CS1)"                        "DATAFLASH::Init 0"
    "Set DF in Power-Of-2 Page Size mode (Binary mode)"  "DATAFLASH::BinaryPage"
    "Erase All"                                          "DATAFLASH::EraseAll"
}

set DATAFLASH::appletAddr          0x202000
set DATAFLASH::appletMailboxAddr   0x202004
set DATAFLASH::appletFileName      "$libPath(extLib)/$target(board)/applet-dataflash-at91sam7x512.bin"


################################################################################
## SERIALFLASH
################################################################################
array set at91sam7x512_serialflash {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x0
    dftSize     "$GENERIC::memorySize"
    dftSend     "GENERIC::SendFile"
    dftReceive  "GENERIC::ReceiveFile"
    dftScripts  "::at91sam7x512_serialflash_scripts"
}

array set at91sam7x512_serialflash_scripts {
    "Enable Serialflash (SPI0 CS1)"   "SERIALFLASH::Init 0"
    "Erase All"                       "SERIALFLASH::EraseAll"
}

set SERIALFLASH::appletAddr          0x202000
set SERIALFLASH::appletMailboxAddr   0x202004
set SERIALFLASH::appletFileName      "$libPath(extLib)/$target(board)/applet-serialflash-at91sam7x512.bin"

################################################################################
## EEPROM
################################################################################
array set at91sam7x512_eeprom {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x0
    dftSize     "$GENERIC::memorySize"
    dftSend     "GENERIC::SendFile"
    dftReceive  "GENERIC::ReceiveFile"
    dftScripts  "::at91sam7x512_eeprom_scripts"
}

array set at91sam7x512_eeprom_scripts {
    "Enable EEPROM AT24C01x"          "EEPROM::Init 0"
    "Enable EEPROM AT24C02x"          "EEPROM::Init 1"
    "Enable EEPROM AT24C04x"          "EEPROM::Init 2"
    "Enable EEPROM AT24C08x"          "EEPROM::Init 3"
    "Enable EEPROM AT24C16x"          "EEPROM::Init 4"
    "Enable EEPROM AT24C32x"          "EEPROM::Init 5"
    "Enable EEPROM AT24C64x"          "EEPROM::Init 6"
    "Enable EEPROM AT24C128x"         "EEPROM::Init 7"
    "Enable EEPROM AT24C256x"         "EEPROM::Init 8"
    "Enable EEPROM AT24C512x"         "EEPROM::Init 9"
    "Enable EEPROM AT24C1024x"        "EEPROM::Init 10"
}

set EEPROM::appletAddr          0x202000
set EEPROM::appletMailboxAddr   0x202004
set EEPROM::appletFileName      "$libPath(extLib)/$target(board)/applet-eeprom-at91sam7x512.bin"

################################################################################
array set at91sam7x512_peripheral {
    dftDisplay  0
    dftDefault  0
    dftAddress  0xF0000000
    dftSize     0x10000000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

array set at91sam7x512_rom {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x300000
    dftSize     0x2000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

array set at91sam7x512_remap {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x00000000
    dftSize     0x2000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}
