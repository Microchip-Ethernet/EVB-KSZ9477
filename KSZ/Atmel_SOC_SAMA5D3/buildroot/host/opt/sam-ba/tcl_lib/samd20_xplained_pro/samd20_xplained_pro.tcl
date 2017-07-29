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

set cidr_addr 0x41002018
# *****************************************************************************
#                       CHIP NAME   CHIPID_CIDR
# *****************************************************************************
array set devicesList { samd20e15 0x1000000D
                        samd20e16 0x1000000C
                        samd20e17 0x1000000B
                        samd20e18 0x1000000A
                        samd20g15 0x10000008
                        samd20g16 0x10000007
                        samd20g17 0x10000006
                        samd20g18 0x10000005
                        samd20j15 0x10000003
                        samd20j16 0x10000002
                        samd20j17 0x10000001
                        samd20j18 0x10000000
                      }
global target
global commandLineMode
set isValidChipOfBoard 0
set version_mask 0xFFBF00FF
                 
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
    variable sramSize         0x00008000
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

# Standard applet commands + some SAMD20 specific commands
array set appletCmdSamd20 {
    init            0x00
    fullErase       0x01
    write           0x02
    read            0x03
    lock            0x04
    unlock          0x05
    gpnvm           0x06
    security        0x07
    erasebuffer     0x08
    binarypage      0x09
    otpRead         0x0a
    otpWrite        0x0b
    listbadblocks   0x10
    tagBlock        0x11
    readUniqueID    0x12
    eraseBlocks     0x13
    batchErase      0x14
    pmeccParam      0x15
    pmeccBoot       0x16
    switchEccMode   0x17
    trimffsMode     0x18
    eraseRow        0x40
    readDeviceID    0x41
    readLocks       0x42
    readFuses       0x43
    eraseApp        0x44
}


set target(board) "samd20_xplained_pro"

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
    "SRAM"            "::atsamd20_sram"
    "Flash"           "::atsamd20_flash"
    "Peripheral"      "::atsamd20_peripheral"
}

################################################################################
## Low Level Initialization
################################################################################


################################################################################
## SRAM : 32k
################################################################################
array set atsamd20_sram {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x20000000
    dftSize     0x8000
    dftSend     "RAM::sendFile"
    dftReceive  "RAM::receiveFile"
    dftScripts  ""
}

################################################################################
## FLASH : 256k
################################################################################
array set atsamd20_flash {
    dftDisplay  1
    dftDefault  1
    dftAddress  0x00000
    dftSize     0x40000
    dftSend     "FLASH::SendFileNoLock"
    dftReceive  "FLASH::ReceiveFile"
    dftScripts  "::atsamd20_flash_scripts"
}

array set atsamd20_flash_scripts {
        "Read Device ID"                        "FLASH::ReadDeviceID"
        "Read Lock Fuses"                       "FLASH::ReadLocks"
        "Unlock All"                            "FLASH::UnlockAll"
        "Set Lock Bit 00"                       "FLASH::SetLock 0"
        "Set Lock Bit 01"                       "FLASH::SetLock 1"
        "Set Lock Bit 02"                       "FLASH::SetLock 2"
        "Set Lock Bit 03"                       "FLASH::SetLock 3"
        "Set Lock Bit 04"                       "FLASH::SetLock 4"
        "Set Lock Bit 05"                       "FLASH::SetLock 5"
        "Set Lock Bit 06"                       "FLASH::SetLock 6"
        "Set Lock Bit 07"                       "FLASH::SetLock 7"
        "Set Lock Bit 08"                       "FLASH::SetLock 8"
        "Set Lock Bit 09"                       "FLASH::SetLock 9"
        "Set Lock Bit 10"                       "FLASH::SetLock 10"
        "Set Lock Bit 11"                       "FLASH::SetLock 11"
        "Set Lock Bit 12"                       "FLASH::SetLock 12"
        "Set Lock Bit 13"                       "FLASH::SetLock 13"
        "Set Lock Bit 14"                       "FLASH::SetLock 14"
        "Set Lock Bit 15"                       "FLASH::SetLock 15"
        "Invalidate application"                "FLASH::EraseRow 32"
        "Erase application area [0x800 - ...]"  "FLASH::EraseApp"
        "Read Fuses"                            "FLASH::ReadFuses"
        "Set Security Bit"                      "FLASH::SetSecurity"
}

set FLASH::appletAddr             0x20000100
set FLASH::appletMailboxAddr      0x20000140
set FLASH::appletFileName         "$libPath(extLib)/$target(board)/applet-flash-samd20j18.bin"

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
        #retrieve additionnal parameters from the Init function
        set appletAddrArgvps      [expr $FLASH::appletMailboxAddr + 0x18]
        set appletAddrArgvnp      [expr $FLASH::appletMailboxAddr + 0x1c]
        set appletAddrArgvasp     [expr $FLASH::appletMailboxAddr + 0x20]

        set flashPageSize         [TCL_Read_Int $target(handle) $appletAddrArgvps]
        set flashNbPage         [TCL_Read_Int $target(handle) $appletAddrArgvnp]
        set flashAppStartPage     [TCL_Read_Int $target(handle) $appletAddrArgvasp]

        puts "flashPageSize     [format "0x%08x" $flashPageSize]"
        puts "flashNbPage         [format "%d" $flashNbPage]"
        puts "flashAppStartPage [format "%d" $flashAppStartPage]"
        puts "-I- FLASH initialized"
}


################################################################################
array set atsamd20_peripheral {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x40000000
    dftSize     0x10000000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

#===============================================================================
#  proc FLASH::ReadDeviceID
#===============================================================================
proc FLASH::ReadDeviceID { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    # Init the ping pong algorithm: the buffer is active
    set bufferAddress $GENERIC::appletBufferAddress

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSamd20(readDeviceID) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) $bufferAddress $appletAddrArgv0} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSamd20(readDeviceID)]} dummy_err]} {
        error "Applet readDeviceID command has not been launched ($dummy_err)"
    }

    puts "buffer address [format "0x%08x" $bufferAddress]"

    puts "Device ID :"

    set addr [expr $bufferAddress]
    # Return the error code returned by the applet
    if {[catch {set data [TCL_Read_Int $target(handle) $addr]} dummy_err] } {
        error "Error reading the buffer containing Device ID"
    }

    puts [format "0x%08x" $data]
}

#===============================================================================
#  proc FLASH::ReadFuses
#===============================================================================
proc FLASH::ReadFuses { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]

    # Init the ping pong algorithm: the buffer is active
    set bufferAddress $GENERIC::appletBufferAddress

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSamd20(readFuses) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) $bufferAddress $appletAddrArgv0} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSamd20(readFuses)]} dummy_err]} {
        error "Applet readDeviceID command has not been launched ($dummy_err)"
    }

    puts "buffer address [format "0x%08x" $bufferAddress]"

    puts "Fuses :"

    set i 0
    set addr [expr $bufferAddress]
    while {$i < [expr 2]} {
        # Return the error code returned by the applet
        if {[catch {set data [TCL_Read_Int $target(handle) $addr]} dummy_err] } {
            error "Error reading the buffer containing Device ID"
        }
        incr addr +4
        incr i +1
        puts [format "0x%08x" $data]
    }
}

#===============================================================================
#  proc FLASH::ReadLocks
#===============================================================================
proc FLASH::ReadLocks { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArgv0     [expr $appletMailboxAddr + 0x08]
    set appletAddrArgv1     [expr $appletMailboxAddr + 0x0c]
    set appletAddrArgv2     [expr $appletMailboxAddr + 0x10]
    set appletAddrArgv3     [expr $appletMailboxAddr + 0x14]

    # Init the ping pong algorithm: the buffer is active
    set bufferAddress $GENERIC::appletBufferAddress

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSamd20(readLocks) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) $bufferAddress $appletAddrArgv0} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSamd20(readLocks)]} dummy_err]} {
        error "Applet readDeviceID command has not been launched ($dummy_err)"
    }

    puts "buffer address [format "0x%08x" $bufferAddress]"

    puts "Lock status :"

    set addr [expr $bufferAddress]
    # Return the error code returned by the applet
    if {[catch {set data [TCL_Read_Short $target(handle) $addr]} dummy_err] } {
        error "Error reading the buffer containing Device ID"
    }

    puts [format "0x%4x" $data]
}

#===============================================================================
#  proc FLASH::SetLock
#===============================================================================
proc FLASH::SetLock { lockbit } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_value [expr $appletMailboxAddr + 0x08]

    if {$lockbit > [expr 16]} {
        error "Wrong lock bit number"
    }

    set writemask [expr 1 << $lockbit ]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSamd20(lock) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write value in the argument area
    if {[catch {TCL_Write_Int $target(handle) [expr $lockbit] $appletAddrArg_value} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSamd20(lock)]} dummy_err]} {
        error "Applet lock command has not been launched ($dummy_err)"
    }

    puts "Region locked"
}


#===============================================================================
#  proc FLASH::UnlockAll
#===============================================================================
proc FLASH::UnlockAll { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_value [expr $appletMailboxAddr + 0x08]

    set lockbit 0
    while { $lockbit < [expr 16]} {
        set writemask [expr 1 << $lockbit ]

        # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $::appletCmdSamd20(unlock) $appletAddrCmd} dummy_err] } {
            error "Error Writing Applet command ($dummy_err)"
        }
        # Write value in the argument area
        if {[catch {TCL_Write_Int $target(handle) [expr $lockbit] $appletAddrArg_value} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        # Launch the applet Jumping to the appletAddr
        if {[catch {set result [GENERIC::Run $::appletCmdSamd20(unlock)]} dummy_err]} {
            error "Applet lock command has not been launched ($dummy_err)"
        }

        puts "Region ($lockbit) unlocked"

        incr lockbit +1
    }
}

#===============================================================================
#  proc FLASH::SetSecurity
#===============================================================================
proc FLASH::SetSecurity { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd       [expr $appletMailboxAddr]
    set appletAddrStatus    [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_param [expr $appletMailboxAddr + 0x08]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSamd20(security) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the param value in the argument area
    if {[catch {TCL_Write_Int $target(handle) 1 $appletAddrArg_param} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    puts "About to launch set security bit procedure ..."

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSamd20(security)]} dummy_err]} {
        error "Applet security command has not been launched ($dummy_err)"
    } else {
        puts "Part is secured"
    }
}

#===============================================================================
#  proc FLASH::SendFileNoLock
#===============================================================================
proc FLASH::SendFileNoLock { name addr } {
    variable flashSize  
    variable flashLockRegionSize   
    variable flashNumbersLockBits 
    variable appletBufferAddress
    global   commandLineMode

    if { [catch {set f [open $name r]}] } {
        puts "-E- Can't open file $name"
        return -1
    }
    fconfigure $f -translation binary

    #First Step check the locked sector 
    set dummy_err 0
    set rewrite 0
    set size [file size $name]

    set dest [expr $addr & [expr  $flashSize - 1]]
    set first_page [expr $dest / $::flashPageSize]

    puts "File size : $size"
    puts "Flash size : $flashSize Flash page size : $::flashPageSize First page : $first_page"
    puts "Dest : $dest"

    if { $first_page < $::flashAppStartPage } {
        if {$commandLineMode == 0} {
            set answer [tk_messageBox -title "Attempt to write monitor area"\
            -message " Writing to the monitor area (0x0 .. 0x800) is forbidden, write operation aborted "\
            -icon error \
            -type ok]
        }
        return -1
    }

    if {[catch {GENERIC::Write $dest $size $f 0} dummy_err] } {
        puts "-E- Generic::Write returned error ($dummy_err)"
        close $f
        return -1
    }
    close $f
}

#===============================================================================
#  proc FLASH::EraseRow
#===============================================================================
proc FLASH::EraseRow { flashrow } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_param         [expr $appletMailboxAddr + 0x08]

    if {$flashrow > [expr 1024]} {
        error "Wrong flash region number"
    }

    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSamd20(eraseRow) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the param value in the argument area
    if {[catch {TCL_Write_Int $target(handle) [expr $flashrow] $appletAddrArg_param} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSamd20(eraseRow)]} dummy_err]} {
        error "Applet eraseRow command has not been launched ($dummy_err)"
    }
    puts "Flash memory row erased."

}

#===============================================================================
#  proc FLASH::EraseApp
#===============================================================================
proc FLASH::EraseApp { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_start_row     [expr $appletMailboxAddr + 0x08]
    set appletAddrArg_end_row       [expr $appletMailboxAddr + 0x0c]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSamd20(eraseApp) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    set start    [expr $::flashAppStartPage/4]
    set end      [expr $::flashNbPage/4]

    # Write the starting row number in the argument area
    if {[catch {TCL_Write_Int $target(handle) [expr $start] $appletAddrArg_start_row} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Write the ending row number in the argument area
    if {[catch {TCL_Write_Int $target(handle) [expr $end] $appletAddrArg_end_row} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    puts "Start row: [format "0x%08x" $start]"
    puts "End row: [format "0x%08x" $end]"

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSamd20(eraseApp)]} dummy_err]} {
        error "Applet eraseApp command has not been launched ($dummy_err)"
    }

    puts "Application area erased"
}
