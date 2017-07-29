#  ----------------------------------------------------------------------------
#          SAM Software Package License
#  ----------------------------------------------------------------------------
#  Copyright (c) 2013, Atmel Corporation
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

################################################################################
# List of target supported by SAM-BA software
# Board folder MUST have the same name as the board

array set boards {
    "at91sam3x2-ek"     "at91sam3x2-ek/at91sam3x2-ek.tcl"
    "at91sam3x4-ek"     "at91sam3x4-ek/at91sam3x4-ek.tcl"
    "at91sam3x8-ek"     "at91sam3x8-ek/at91sam3x8-ek.tcl"
    "at91sam3a2_on_sam3x2-ek" "at91sam3x2-ek/at91sam3x2-ek.tcl"
    "at91sam3a4_on_sam3x4-ek" "at91sam3x4-ek/at91sam3x4-ek.tcl"
    "at91sam3a8_on_sam3x8-ek" "at91sam3x8-ek/at91sam3x8-ek.tcl"
    "at91sam3n00-ek"    "at91sam3n00-ek/at91sam3n00-ek.tcl"
    "at91sam3n0-ek"     "at91sam3n0-ek/at91sam3n0-ek.tcl"
    "at91sam3n1-ek"     "at91sam3n1-ek/at91sam3n1-ek.tcl"
    "at91sam3n2-ek"     "at91sam3n2-ek/at91sam3n2-ek.tcl"
    "at91sam3n4-ek"     "at91sam3n4-ek/at91sam3n4-ek.tcl"
    "at91sam3s1-ek"     "at91sam3s1-ek/at91sam3s1-ek.tcl"
    "at91sam3s2-ek"     "at91sam3s2-ek/at91sam3s2-ek.tcl"
    "at91sam3s4-ek"     "at91sam3s4-ek/at91sam3s4-ek.tcl"
    "rf231usb-rd"       "rf231usb-rd/rf231usb-rd.tcl"
    "at91sam3s8-ek"     "at91sam3s8-ek/at91sam3s8-ek.tcl"
    "at91sam3sd8-ek"    "at91sam3sd8-ek/at91sam3sd8-ek.tcl"
    "at91sam3s16-ek"    "at91sam3s16-ek/at91sam3s16-ek.tcl"
    "at91sam4e8-ek"     "at91sam4e8-ek/at91sam4e8-ek.tcl"
    "at91sam4e16-ek"    "at91sam4e16-ek/at91sam4e16-ek.tcl"
    "at91sam4s2-ek"     "at91sam4s2-ek/at91sam4s2-ek.tcl"
    "at91sam4s4-ek"     "at91sam4s4-ek/at91sam4s4-ek.tcl"
    "at91sam4s8-ek"     "at91sam4s8-ek/at91sam4s8-ek.tcl"
    "at91sam4s16-ek"    "at91sam4s16-ek/at91sam4s16-ek.tcl"
    "at91sam4sd32-ek"   "at91sam4sd32-ek/at91sam4sd32-ek.tcl"
    "at91sam4s-xpld"    "at91sam4s16-ek/at91sam4s16-ek.tcl"
    "at91sam4n8-xpro"   "at91sam4n8-xpro/at91sam4n8-xpro.tcl"
    "at91sam4n16-xpro"  "at91sam4n16-xpro/at91sam4n16-xpro.tcl"
    "at91sam4c32-ek"    "at91sam4c32-ek/at91sam4c32-ek.tcl"
    "at91sam4c16-ek"    "at91sam4c16-ek/at91sam4c16-ek.tcl"
    "at91sam4c8-ek"     "at91sam4c8-ek/at91sam4c8-ek.tcl"
    "at91sam4c4-ek"     "at91sam4c4-ek/at91sam4c4-ek.tcl"
    "at91sam4cm32-db"   "at91sam4cm32-db/at91sam4cm32-db.tcl"
    "at91sam4cm16-db"   "at91sam4cm16-db/at91sam4cm16-db.tcl"
    "at91sam4cm8-db"    "at91sam4cm8-db/at91sam4cm8-db.tcl"
    "at91sam4cm4-db"   "at91sam4cm4-db/at91sam4cm4-db.tcl"
    "at91sam4cp16-mb"   "at91sam4cp16-mb/at91sam4cp16-mb.tcl"
    "at91sam3u1-ek"     "at91sam3u1-ek/at91sam3u1-ek.tcl"
    "at91sam3u2-ek"     "at91sam3u2-ek/at91sam3u2-ek.tcl"
    "at91sam3u4-ek"     "at91sam3u4-ek/at91sam3u4-ek.tcl"
    "at91sam7a3-ek"     "at91sam7a3-ek/at91sam7a3-ek.tcl"
    "at91sam7l64-ek"    "at91sam7l64-ek/at91sam7l64-ek.tcl"
    "at91sam7l128-ek"   "at91sam7l128-ek/at91sam7l128-ek.tcl"
    "at91sam7s161-ek"   "at91sam7s161-ek/at91sam7s161-ek.tcl"
    "at91sam7s16-ek"    "at91sam7s161-ek/at91sam7s161-ek.tcl"
    "at91sam7s32-ek"    "at91sam7s32-ek/at91sam7s32-ek.tcl"
    "at91sam7s321-ek"   "at91sam7s321-ek/at91sam7s321-ek.tcl"
    "at91sam7s64-ek"    "at91sam7s64-ek/at91sam7s64-ek.tcl"
    "at91sam7s128-ek"   "at91sam7s128-ek/at91sam7s128-ek.tcl"
    "at91sam7s256-ek"   "at91sam7s256-ek/at91sam7s256-ek.tcl"
    "at91sam7s512-ek"   "at91sam7s512-ek/at91sam7s512-ek.tcl"
    "at91sam7se32-ek"   "at91sam7se32-ek/at91sam7se32-ek.tcl"
    "at91sam7se256-ek"  "at91sam7se256-ek/at91sam7se256-ek.tcl"
    "at91sam7se512-ek"  "at91sam7se512-ek/at91sam7se512-ek.tcl"
    "at91sam7x128-ek"   "at91sam7x128-ek/at91sam7x128-ek.tcl"
    "at91sam7x256-ek"   "at91sam7x256-ek/at91sam7x256-ek.tcl"
    "at91sam7x512-ek"   "at91sam7x512-ek/at91sam7x512-ek.tcl"
    "at91sam7xc128-ek"  "at91sam7x128-ek/at91sam7x128-ek.tcl"
    "at91sam7xc256-ek"  "at91sam7x256-ek/at91sam7x256-ek.tcl"
    "at91sam7xc512-ek"  "at91sam7x512-ek/at91sam7x512-ek.tcl"
    "at91sam9260-ek"    "at91sam9260-ek/at91sam9260-ek.tcl"
    "at91sam9261-ek"    "at91sam9261-ek/at91sam9261-ek.tcl"
    "at91sam9263-ek"    "at91sam9263-ek/at91sam9263-ek.tcl"
    "at91sam9g10-ek"    "at91sam9g10-ek/at91sam9g10-ek.tcl"
    "at91sam9g20-ek"    "at91sam9g20-ek/at91sam9g20-ek.tcl"
    "at91sam9g15-ek"    "at91sam9g15-ek/at91sam9g15-ek.tcl"
    "at91sam9g25-ek"    "at91sam9g15-ek/at91sam9g15-ek.tcl"
    "at91sam9g35-ek"    "at91sam9g15-ek/at91sam9g15-ek.tcl"
    "at91sam9x25-ek"    "at91sam9g15-ek/at91sam9g15-ek.tcl"
    "at91sam9x35-ek"    "at91sam9g15-ek/at91sam9g15-ek.tcl"
    "at91sam9n12-ek"    "at91sam9n12-ek/at91sam9n12-ek.tcl"
    "at91sam9cn12-ek"   "at91sam9n12-ek/at91sam9n12-ek.tcl"
    "at91sam9n11-ek"    "at91sam9n12-ek/at91sam9n12-ek.tcl"
    "at91sam9cn11-ek"   "at91sam9n12-ek/at91sam9n12-ek.tcl"
    "at91sam9g45-ekes"  "at91sam9m10-ek/at91sam9m10-ek.tcl"
    "at91sam9m10-ekes"  "at91sam9m10-ek/at91sam9m10-ek.tcl"
    "at91sam9m10-g45-ek" "at91sam9m10-ek/at91sam9m10-ek.tcl"
    "at91sam9rl64-ek"   "at91sam9rl64-ek/at91sam9rl64-ek.tcl"
    "at91sam9xe128-ek"  "at91sam9xe128-ek/at91sam9xe128-ek.tcl"
    "at91sam9xe256-ek"  "at91sam9xe256-ek/at91sam9xe256-ek.tcl"
    "at91sam9xe512-ek"  "at91sam9xe512-ek/at91sam9xe512-ek.tcl"
    "at91cap9-dk_mem33" "at91cap9-dk/at91cap9-dk-mem33.tcl"
    "at91cap9-dk_mem18" "at91cap9-dk/at91cap9-dk-mem18.tcl"
    "at91cap9-stk"      "at91cap9-stk/at91cap9-stk.tcl"
    "at91sama5d3x-ek"   "at91sama5d3x-ek/at91sama5d3x-ek.tcl"
    "at91sama5d3x-xplained" "at91sama5d3x-ek/at91sama5d3x-ek.tcl"
    "at91sama5d3x-cmp" "at91sama5d3x-ek/at91sama5d3x-ek.tcl"
    "at91sama5d4x-ek"   "at91sama5d4x-ek/at91sama5d4x-ek.tcl"
    "at91sama5d4x-xplained" "at91sama5d4x-ek/at91sama5d4x-ek.tcl"
    "at91samv71-xplained" "at91samv7-ek/at91samv7-ek.tcl"
    "at91same70-xplained" "at91samv7-ek/at91samv7-ek.tcl"
    "sam4l-ek[not factory programmed]" "at91sam4l-ek/at91sam4l-ek.tcl"
    "samd20_xplained_pro[not factory programmed]" "samd20_xplained_pro/samd20_xplained_pro.tcl"
    "samd21_xplained_pro[not factory programmed]" "samd21_xplained_pro/samd21_xplained_pro.tcl"
    "samda1_xplained_pro[not factory programmed]" "samda1_xplained_pro/samda1_xplained_pro.tcl"
    "saml21_xplained_pro[not factory programmed]" "saml21_xplained_pro/saml21_xplained_pro.tcl"
    "saml22_xplained_pro[not factory programmed]" "saml22_xplained_pro/saml22_xplained_pro.tcl"
    "samc21_xplained_pro[not factory programmed]" "samc21_xplained_pro/samc21_xplained_pro.tcl"
}

#
 # Add user board here, for example add 
 # "devicename-userboard" "devicename-userboard/devicename-userboard.tcl"
 # Note2: devicename should also add with chip id in devices list in devices/devices.tcl
 # Please see user guide to get more information.

 array set user_boards {
}

#example Add:
# "test-stk"      "test-stk/test-stk.tcl"
