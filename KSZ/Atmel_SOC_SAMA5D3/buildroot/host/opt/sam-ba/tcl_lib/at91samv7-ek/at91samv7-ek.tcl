#  ----------------------------------------------------------------------------
#          SAM Software Package License
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
array set devicesList { same70x21 0xa1020e00
                        same70x20 0xa1020c00
                        same70x19 0xa10d0a00
                        sams70x21 0xa1120e00
                        sams70x20 0xa1120c00
                        sams70x19 0xa11d0a00
                        samv71x21 0xa1220e00
                        samv71x20 0xa1220c00
                        samv71x19 0xa12d0a00
                        samv70x20 0xa1320c00
                        samv70x19 0xa13d0a00
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
    variable sramSize         0x00060000
    variable maxBootSize      0
    # Vdd Memory 1.8V = 0 / Vdd Memory 3.3V = 1
    variable extRamVdd 1
    # External SDRAM = 0 / External DDR = 1 External PSRAM = 2 (not used)
    variable extRamType 0
    # Set bus width (16 or 32)
    variable extRamDataBusWidth 16
    # DDRAM Model (not used)
    variable extDDRamModel 0
}

set target(board) at91samv7-ek

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
    "SRAM"         "::at91samv7_sram"
    "Flash"        "::at91samv7_flash"
    "QspiFlash"    "::at91samv7_qspiflash"
    "Peripheral"   "::at91samv7_peripheral"
    "REMAP"        "::at91samv7_remap"
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
array set at91samv7_sram {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x20400000
    dftSize     0x60000
    dftSend     "RAM::sendFile"
    dftReceive  "RAM::receiveFile"
    dftScripts  ""
}

################################################################################
## FLASH
################################################################################
array set at91samv7_flash {
    dftDisplay  1
    dftDefault  1
    dftAddress  0x00400000
    dftSize     0x200000
    dftSend     "FLASH::SendFile"
    dftReceive  "FLASH::ReceiveFile"
    dftScripts  "::at91samv7_flash_scripts"
}
array set at91samv7_flash_scripts {
        "Enable Security Bit (GPNVM0)"         "FLASH::ScriptGPNMV 0"
        "Boot from Flash (GPNVM1)"             "FLASH::ScriptGPNMV 2"
        "Boot from ROM (GPNVM1)"               "FLASH::ScriptGPNMV 3"
        "Erase All Flash"                      "FLASH::EraseAll"
        "Enable Flash access"                  "FLASH::Init "
        "Read unique ID"                       "FLASH::ReadUniqueID"
}

set FLASH::appletAddr             0x20401000
set FLASH::appletMailboxAddr      0x20401040
set FLASH::appletFileName         "$libPath(extLib)/$target(board)/applet-flash-samv7.bin"


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
## QSPI FLASH
################################################################################
array set at91samv7_qspiflash {
    dftDisplay  1
    dftDefault  1
    dftAddress  0
    dftSize     "$GENERIC::memorySize"
    dftSend     "GENERIC::SendFile"
    dftReceive  "GENERIC::ReceiveFile"
    dftScripts  "::at91samv7_qspi_scripts"
}
array set at91samv7_qspi_scripts {
    "Enable Qspi S25fl116K flash"     "SERIALFLASH::Init 0"
    "Erase All"                       "SERIALFLASH::EraseAll"
    "Enter XIP mode and execute from QSPI flash" "SERIALFLASH::Xip"
}

set SERIALFLASH::appletAddr             0x20401000
set SERIALFLASH::appletMailboxAddr      0x20401040
set SERIALFLASH::appletFileName         "$libPath(extLib)/$target(board)/applet-qspi-samv7.bin"


################################################################################
array set at91samv7_peripheral {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x40000000
    dftSize     0x10000000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

array set at91samv7_remap {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x00000000
    dftSize     0x40000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

