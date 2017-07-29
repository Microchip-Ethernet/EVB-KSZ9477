SAM-BA 2.13 Readme file


Contents
--------
 1. Abstract
 2. Installation
 3. Upgrading From an Earlier Version
 4. USB driver installation
 5. What's New
 6. Running SAM-BA
 7. Contact Info

1. Abstract
-----------
The SAM Boot Assistant (SAM-BA)(R) software provides a means of easily 
programming different Atmel AT91SAM ARM(R) Thumb(R)-based devices. 
It runs under Windows(R) XP, Windows(R) Vista, Windows(R) 7, and Windows(R) 8.

2. Installation
---------------
The software can be found and downloaded from ATMEL's website at 
http://www.atmel.com/tools/atmelsam-bain-systemprogrammer.aspx
  
- sam-ba_2.13.exe for Windows Install files for 
  the SAM-BA package.  Execute sam-ba_2.11.exe to install. 
- It is recommended to uninstalling the old version before 
  install SAM-BA.
- It is also recommended that you accept the default installation 
  location. 

3. Upgrading From an Earlier Version
------------------------------------
You can install this version over an earlier version if you wish.
If you want to install two versions of SAM-BA(R) on the same computer, 
you must make sure the new version is not installed in the same 
directory as the old version to avoid confusion. 
For Windows Vista(R), Windows(R) 7, and Windows(R) 8 we recommend to select
"run as administrator" to install/launch sam-ba.

4. USB driver installation
--------------------------
SAM-BA can communicate with ATMEL ARM-based devices via a USB CDC Serial 
communication channel. The device uses the USB communication device class (CDC) 
drivers to take advantage of the installed PC RS-232 software to talk over 
the USB. The CDC class is implemented in all releases of Windows. 
The CDC document, available at www.usb.org, describes a way to implement 
devices such as virtual COM ports. The Vendor ID is Atmel's vendor ID: 0x03EB. 
The product ID is 0x6124. These references are used by the host operating 
system to mount the correct driver. On Windows systems, the atm6124_cdc.inf
files contain the correspondance between vendor ID and product ID.

If your Atmel EK board is recognized as an ATMEL AT91xxxxx Test Board using
atm6124.sys driver, you have to uninstall this driver first, or connect the
board to another USB port on the computer where the board will be detected as a
new device.

To uninstall a previously installed driver on a USB port, you have to open the
Windows Device Manager tool (the following steps are explained for Windows XP,
but very similar for the other versions of the OS) :
- Connect the board to the computer via a USB port and power it up,
- Control panel -> System -> 'Hardware' pane,
- Expand the 'Universal Serial Bus controllers' folder,
- Right click on the 'atm6124.Sys ATMEL AT91xxxxx Test Board' entry,
- Choose 'uninstall' and confirm, (the entry disappears from the list)
- Power down the board.

To install the CDC Serial driver :
- Power UP the board.
- The system finds a new hardware and asks you to search a new driver for it,
- Tell it to NOT connect to Windows update, then 'Next' button,
- Choose to install from a list or specific location (Advanced), then 'Next' button,
- Click on 'Don't search, ...', then 'Next' button,
- Choose 'Have Disk...' button, and look for the 'atm6124_cdc.inf' file where 
  you have installed this CDC version of SAM-BA, then 'Open' and 'OK',
- Select the Model : 'AT91 USB to Serial Converter' in the list and click 'Next',
- Click on 'Continue Anyway' in the next window, and then 'Finish'.

IMPORTANT : If you change the USB port on wich you connect the board, you will
need to redo the install procedure described above.  

In the 'Device Manager' window, your board appears in the 'Ports (COM & LPT)'
folder, with the 'virual' COM port name indicated in parenthesis.

IMPORTANT : You have to keep this COM number in mind to select it when SAM-BA shows
the 'Choose Connection' message box.  

5. What's New
-------------
For a complete new features and history of earlier releases, 
see the file releasenote.txt

6. Running SAM-BA
-----------------
Launch 'sam-ba.exe' file, and select your board and the COM
port number where your board in connected to.

7. Contact Info
----------------
If you have any questions, comments or suggestions, we would be happy
to hear from you. Current contact information can be found on our web
site at:  www.atmel.com

