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

set cidr_addr 0x400E0740
# *****************************************************************************
#                       CHIP NAME   CHIPID_CIDR
# *****************************************************************************
array set devicesList { at91sam4l_0 0xab0a09e0
                        at91sam4l_1 0xab0a07e0
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

# Standard applet commands + some SAM4L specific commands
array set appletCmdSam4l {
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
    rwFuses            0x40
    writeUserPage    0x41
    readUserPage    0x42    
    readUniqueSN    0x43        
    erasePage     0x44    
}

set target(board) "at91sam4l-ek"

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
    "SRAM"            "::at91sam4l_sram"
    "Flash"           "::at91sam4l_flash"
    "Peripheral"      "::at91sam4l_peripheral"
    "FlashUserPage"   "::at91sam4l_userpage"
}

################################################################################
## Low Level Initialization
################################################################################


################################################################################
## SRAM : 32k
################################################################################
array set at91sam4l_sram {
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
array set at91sam4l_flash {
    dftDisplay  1
    dftDefault  1
    dftAddress  0x00000
    dftSize     0x40000
    dftSend     "FLASH::SendFileNoLock"
    dftReceive  "FLASH::ReceiveFile"
    dftScripts  "::at91sam4l_flash_scripts"
}

array set at91sam4l_flash_scripts {
        "Read Unique Serial Number"            "FLASH::ReadUniqueSerialNumber"
        "Read Lock Fuses"                      "FLASH::ReadLocks"
        "Unlock All"                           "FLASH::UnlockAll"        
        "Set Lock Bit 00"                      "FLASH::SetLock 0"
        "Set Lock Bit 01"                      "FLASH::SetLock 1"
        "Set Lock Bit 02"                      "FLASH::SetLock 2"
        "Set Lock Bit 03"                      "FLASH::SetLock 3"
        "Set Lock Bit 04"                      "FLASH::SetLock 4"
        "Set Lock Bit 05"                      "FLASH::SetLock 5"
        "Set Lock Bit 06"                      "FLASH::SetLock 6"
        "Set Lock Bit 07"                      "FLASH::SetLock 7"
        "Set Lock Bit 08"                      "FLASH::SetLock 8"
        "Set Lock Bit 09"                      "FLASH::SetLock 9"
        "Set Lock Bit 10"                      "FLASH::SetLock 10"
        "Set Lock Bit 11"                      "FLASH::SetLock 11"
        "Set Lock Bit 12"                      "FLASH::SetLock 12"
        "Set Lock Bit 13"                      "FLASH::SetLock 13"
        "Set Lock Bit 14"                      "FLASH::SetLock 14"
        "Set Lock Bit 15"                      "FLASH::SetLock 15"
        "Invalidate application"               "FLASH::ErasePage 32"        
        "Erase application area [0x4000 - ...]" "FLASH::ErasePage -1"        
        "Read General Purpose Fuses"           "FLASH::ReadFuses"
        "Read Security Bit"                    "FLASH::ReadSecurity"
        "Set Security Bit"                     "FLASH::SetSecurity"
}

set FLASH::appletAddr             0x20002000
set FLASH::appletMailboxAddr      0x20002040
set FLASH::appletFileName         "$libPath(extLib)/$target(board)/applet-flash-sam4l4.bin"

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
        #retrieve additionnal parameters from the Init function (SAM4L specific)
        set appletAddrArgvps     [expr $FLASH::appletMailboxAddr + 0x18]
        set appletAddrArgvnp    [expr $FLASH::appletMailboxAddr + 0x1c]
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
## NAMESPACE USERPAGE
################################################################################
namespace eval USERPAGE {
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName
    variable userpageSize
}

set USERPAGE::appletAddr             0x20002000
set USERPAGE::appletMailboxAddr      0x20002040
set USERPAGE::appletFileName         "$libPath(extLib)/$target(board)/applet-flash-sam4l4.bin"
set USERPAGE::userpageSize           0x200


################################################################################
array set at91sam4l_peripheral {
    dftDisplay  0
    dftDefault  0
    dftAddress  0x40000000
    dftSize     0x10000000
    dftSend     ""
    dftReceive  ""
    dftScripts  ""
}

array set at91sam4l_userpage {
    dftDisplay  1
    dftDefault  0
    dftAddress  0x00000000
    dftSize     0x200
    dftSend     "USERPAGE::SendFile"
    dftReceive  "USERPAGE::ReceiveFile"
    dftScripts  ""
}


#===============================================================================
#  proc FLASH::ReadUniqueID
#-------------------------------------------------------------------------------
proc FLASH::ReadUniqueSerialNumber { } {
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
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(readUniqueSN) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) $bufferAddress $appletAddrArgv0} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSam4l(readUniqueSN)]} dummy_err]} {
        error "Applet readUniqueSN command has not been launched ($dummy_err)"
    }

    puts "buffer address [format "0x%08x" $bufferAddress]"

    puts "Unique Serial Number :"

    # Read the page containing the unique SN
    set i 0
    while {$i < [expr 15]} {
        set addr [expr $bufferAddress + $i]
        # Return the error code returned by the applet
        if {[catch {set data [TCL_Read_Byte $target(handle) $addr]} dummy_err] } {
            error "Error reading the buffer containing Unique SN"
        }

        puts [format "\t0x%02x : 0x%02x" [expr $i] $data]
        incr i +1
    }
}



#===============================================================================
#  proc FLASH::ReadFuses
#-------------------------------------------------------------------------------
proc FLASH::ReadFuses { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_value_l         [expr $appletMailboxAddr + 0x08]
    set appletAddrArg_value_h         [expr $appletMailboxAddr + 0x0c]
    set appletAddrArg_writemask_l   [expr $appletMailboxAddr + 0x10]
    set appletAddrArg_writemask_h   [expr $appletMailboxAddr + 0x14]
    set appletAddrArg_errors_l         [expr $appletMailboxAddr + 0x18]
    set appletAddrArg_errors_h         [expr $appletMailboxAddr + 0x1c]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(rwFuses) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_value_l} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_value_h} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_writemask_l} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_writemask_h} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSam4l(rwFuses)]} dummy_err]} {
        error "Applet rwFuses command has not been launched ($dummy_err)"
    }

    puts "buffer address [format "0x%08x" $appletAddrArg_value_l]"

    puts "Fuses :"

    # Read the value of fuses in applet struct
    set i 0
    while {$i < [expr 8]} {
        set addr [expr $appletAddrArg_value_l + $i]
        # Return the error code returned by the applet
        if {[catch {set data [TCL_Read_Byte $target(handle) $addr]} dummy_err] } {
            error "Error reading the buffer containing fuses"
        }

        puts [format "\t0x%02x : 0x%02x" [expr $i] $data]
        incr i +1
    }
}

#===============================================================================
#  proc FLASH::ReadLocks
#-------------------------------------------------------------------------------
proc FLASH::ReadLocks { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_value_l         [expr $appletMailboxAddr + 0x08]
    set appletAddrArg_value_h         [expr $appletMailboxAddr + 0x0c]
    set appletAddrArg_writemask_l   [expr $appletMailboxAddr + 0x10]
    set appletAddrArg_writemask_h   [expr $appletMailboxAddr + 0x14]
    set appletAddrArg_errors_l         [expr $appletMailboxAddr + 0x18]
    set appletAddrArg_errors_h         [expr $appletMailboxAddr + 0x1c]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(rwFuses) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write value in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_value_l} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write value in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_value_h} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write writemask in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_writemask_l} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write writemask in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_writemask_h} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSam4l(rwFuses)]} dummy_err]} {
        error "Applet rwFuses command has not been launched ($dummy_err)"
    }

    puts "buffer address [format "0x%08x" $appletAddrArg_value_l]"

    puts "Locks :"

    # Read the value of fuses in applet struct
    set i 0
    while {$i < [expr 2]} {
        set addr [expr $appletAddrArg_value_l + $i]
        # Return the error code returned by the applet
        if {[catch {set data [TCL_Read_Byte $target(handle) $addr]} dummy_err] } {
            error "Error reading the buffer containing locks"
        }

        puts [format "\t0x%02x : 0x%02x" [expr $i] $data]
        incr i +1
    }
}

#===============================================================================
#  proc FLASH::SetLock
#-------------------------------------------------------------------------------
proc FLASH::SetLock { lockbit } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_value_l         [expr $appletMailboxAddr + 0x08]
    set appletAddrArg_value_h         [expr $appletMailboxAddr + 0x0c]
    set appletAddrArg_writemask_l   [expr $appletMailboxAddr + 0x10]
    set appletAddrArg_writemask_h   [expr $appletMailboxAddr + 0x14]
    set appletAddrArg_errors_l         [expr $appletMailboxAddr + 0x18]
    set appletAddrArg_errors_h         [expr $appletMailboxAddr + 0x1c]

    if {$lockbit > [expr 16]} {
        error "Wrong lock bit number"
    }

    set writemask [expr 1 << $lockbit ]
    
    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(rwFuses) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write value in the argument area
    if {[catch {TCL_Write_Int $target(handle) [expr ~$writemask] $appletAddrArg_value_l} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write value in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_value_h} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write writemask in the argument area
    if {[catch {TCL_Write_Int $target(handle) $writemask $appletAddrArg_writemask_l} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write writemask in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_writemask_h} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSam4l(rwFuses)]} dummy_err]} {
        error "Applet rwFuses command has not been launched ($dummy_err)"
    }

    puts "buffer address [format "0x%08x" $appletAddrArg_value_l]"

    puts "Locks :"

    # Read the value of fuses in applet struct
    set i 0
    while {$i < [expr 2]} {
        set addr [expr $appletAddrArg_value_l + $i]
        # Return the error code returned by the applet
        if {[catch {set data [TCL_Read_Byte $target(handle) $addr]} dummy_err] } {
            error "Error reading the buffer containing locks"
        }

        puts [format "\t0x%02x : 0x%02x" [expr $i] $data]
        incr i +1
    }
}




#===============================================================================
#  proc FLASH::UnlockAll
#-------------------------------------------------------------------------------
proc FLASH::UnlockAll { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_value_l         [expr $appletMailboxAddr + 0x08]
    set appletAddrArg_value_h         [expr $appletMailboxAddr + 0x0c]
    set appletAddrArg_writemask_l   [expr $appletMailboxAddr + 0x10]
    set appletAddrArg_writemask_h   [expr $appletMailboxAddr + 0x14]
    set appletAddrArg_errors_l         [expr $appletMailboxAddr + 0x18]
    set appletAddrArg_errors_h         [expr $appletMailboxAddr + 0x1c]
    
    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(rwFuses) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write value in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0xFFFF $appletAddrArg_value_l} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write value in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_value_h} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write writemask in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0xFFFF $appletAddrArg_writemask_l} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Write writemask in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_writemask_h} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSam4l(rwFuses)]} dummy_err]} {
        error "Applet rwFuses command has not been launched ($dummy_err)"
    }

    puts "buffer address [format "0x%08x" $appletAddrArg_value_l]"

    puts "Locks :"

    # Read the value of fuses in applet struct
    set i 0
    while {$i < [expr 2]} {
        set addr [expr $appletAddrArg_value_l + $i]
        # Return the error code returned by the applet
        if {[catch {set data [TCL_Read_Byte $target(handle) $addr]} dummy_err] } {
            error "Error reading the buffer containing locks"
        }

        puts [format "\t0x%02x : 0x%02x" [expr $i] $data]
        incr i +1
    }
}

#===============================================================================
#  proc FLASH::ReadSecurity
#-------------------------------------------------------------------------------
proc FLASH::ReadSecurity { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_param         [expr $appletMailboxAddr + 0x08]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(security) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the buffer address in the argument area
    if {[catch {TCL_Write_Int $target(handle) 0 $appletAddrArg_param} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSam4l(security)]} dummy_err]} {
        error "Applet security command has not been launched ($dummy_err)"
    }

    
    # Read the value of security bit in applet struct
    # Return the error code returned by the applet
    if {[catch {set data [TCL_Read_Int $target(handle) $appletAddrArg_param]} dummy_err] } {
        error "Error reading the buffer containing fuses"
    }
    
    if {$data >0} {
        puts "Security bit is set."
    } else {
        puts "Security bit is NOT set."
    }
}

#===============================================================================
#  proc FLASH::SetSecurity
#-------------------------------------------------------------------------------
proc FLASH::SetSecurity { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_param         [expr $appletMailboxAddr + 0x08]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(security) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the param value in the argument area
    if {[catch {TCL_Write_Int $target(handle) 1 $appletAddrArg_param} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }

    puts "About to launch set security bit procedure ..."
    
    
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSam4l(security)]} dummy_err]} {
        error "Applet security command has not been launched ($dummy_err)"
    } else {
        puts "Part is secured"    
    }
}

#===============================================================================
#  proc FLASH::SendFileNoLock
#-------------------------------------------------------------------------------
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
    
    if { $first_page < $::flashAppStartPage } {
    
        if {$commandLineMode == 0} {
            set answer [tk_messageBox -title "Attempt to write monitor area"\
            -message " Writing to the monitor area (0x0 .. 0x4000) is forbidden, write operation aborted "\
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
#  proc USERPAGE::Init
#-------------------------------------------------------------------------------
proc USERPAGE::Init { {bank 0} } {
    global target
    variable appletAddr
    variable appletMailboxAddr
    variable appletFileName

    # bank parameter is used for SAM3 devices where two flash memories are at two different base addresses
    GENERIC::Init $USERPAGE::appletAddr $USERPAGE::appletMailboxAddr $USERPAGE::appletFileName [list $target(comType) $target(traceLevel) $bank]
}

#===============================================================================
#  proc USERPAGE::receiveFile
#-------------------------------------------------------------------------------
proc USERPAGE::ReceiveFile { name addr size } {

    variable userpageSize  
    set dummy_err 0
    
    #override read command value to access userpage instead of flash
    set GENERIC::appletCmd(read) [expr $::appletCmdSam4l(readUserPage)]
    
    if {[catch {GENERIC::ReceiveFile $name $addr $size} dummy_err] } {
        puts "-E- Generic:: receiveFile returned error ($dummy_err)"
    }
    
    #replace standard read command value to access flash
    set GENERIC::appletCmd(read) $::appletCmdSam4l(read)
}

#===============================================================================
#  proc USERPAGE::SendFile
#-------------------------------------------------------------------------------
proc USERPAGE::SendFile { name addr } {
    variable userpageSize  
    variable flashLockRegionSize   
    variable flashNumbersLockBits 
    variable appletBufferAddress
    variable retval

    set retval 0
    
    if { [catch {set f [open $name r]}] } {
        puts "-E- Can't open file $name"
        return -1
    }
    fconfigure $f -translation binary
    
    set size [file size $name]

    #override write command value to access userpage instead of flash
    set GENERIC::appletCmd(write) [expr $::appletCmdSam4l(writeUserPage)]

    if {[catch {GENERIC::Write $addr $size $f 0} dummy_err] } {
        puts "-E- Generic::Write returned error ($dummy_err)"
        set retval -1
    }
    close $f

    #replace standard write command value to access flash
    set GENERIC::appletCmd(write) [expr $::appletCmdSam4l(write)]
    
    return $retval
}





#===============================================================================
#  proc FLASH::EraseAll
#-------------------------------------------------------------------------------
proc FLASH::EraseAll { } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_param         [expr $appletMailboxAddr + 0x08]

    # Write the Cmd op code in the argument area
    if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(fullErase) $appletAddrCmd} dummy_err] } {
        error "Error Writing Applet command ($dummy_err)"
    }
    # Write the param value in the argument area
    if {[catch {TCL_Write_Int $target(handle) 1 $appletAddrArg_param} dummy_err] } {
        error "[format "0x%08x" $dummy_err]"
    }
    
    # Launch the applet Jumping to the appletAddr
    if {[catch {set result [GENERIC::Run $::appletCmdSam4l(fullErase)]} dummy_err]} {
        error "Applet fullErase command has not been launched ($dummy_err)"
    }
    puts "Flash memory erased."
}

#===============================================================================
#  proc FLASH::ErasePage
#-------------------------------------------------------------------------------
proc FLASH::ErasePage { flashpage } {
    global   target
    variable appletMailboxAddr
    set      dummy_err 0

    # Mailbox is 32 word long (add variable here if you need read/write more data)
    set appletAddrCmd               [expr $appletMailboxAddr]
    set appletAddrStatus            [expr $appletMailboxAddr + 0x04]
    set appletAddrArg_param         [expr $appletMailboxAddr + 0x08]

    if {$flashpage > [expr 512]} {
        error "Wrong flash region number"
    }

    if {$flashpage == [expr -1]} {
       for {set page $::flashAppStartPage} {$page < [expr $::flashNbPage]} {incr page 1} {
            puts "-I- \tErasing page N° [format "%04d" $page] ..."            
            # Write the Cmd op code in the argument area
            if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(erasePage) $appletAddrCmd} dummy_err] } {
                error "Error Writing Applet command ($dummy_err)"
            }
            # Write the param value in the argument area
            if {[catch {TCL_Write_Int $target(handle) [expr $page] $appletAddrArg_param} dummy_err] } {
                error "[format "0x%08x" $dummy_err]"
            }
            
            # Launch the applet Jumping to the appletAddr
            if {[catch {set result [GENERIC::Run $::appletCmdSam4l(erasePage)]} dummy_err]} {
                error "Applet erasePage command has not been launched ($dummy_err)"
            }
        }
    } else {
        # Write the Cmd op code in the argument area
        if {[catch {TCL_Write_Int $target(handle) $::appletCmdSam4l(erasePage) $appletAddrCmd} dummy_err] } {
            error "Error Writing Applet command ($dummy_err)"
        }
        # Write the param value in the argument area
        if {[catch {TCL_Write_Int $target(handle) [expr $flashpage] $appletAddrArg_param} dummy_err] } {
            error "[format "0x%08x" $dummy_err]"
        }
        
        # Launch the applet Jumping to the appletAddr
        if {[catch {set result [GENERIC::Run $::appletCmdSam4l(erasePage)]} dummy_err]} {
            error "Applet erasePage command has not been launched ($dummy_err)"
        }
        puts "Flash memory page erased."
    }
}
