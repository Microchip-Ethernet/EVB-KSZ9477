#!/usr/bin/python

##############################################################################################################################################
import cgi, cgitb
##############################################################################################################################################
import os
import sys
import subprocess
##############################################################################################################################################
version = "1.0"
##############################################################################################################################################

############  Function to execute Shell Commands ################################
## cmd: ifconfig, swcfg ...
## return: returns the output of shell command

def	exe_shell_cmd(cmd):
	proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True)
	(out, err) = proc.communicate()
	
	return out;

############ Function to get KSZ Switch Interface ####################
## return: interface name on success else -1 on failure

def	get_interface():

	out = exe_shell_cmd("dmesg | grep attached| grep KSZ")
	
	if len(out) != 0:
		interface = (out.split()[3]).split(":",1)[0]
		out = exe_shell_cmd("ifconfig " + interface + " | grep " + interface)

		if len(out) and interface == out.split()[0]:
			return interface;
		else:
			return -1;

	return -1;

############ Function to get network info of KSZ interface  ####################
## interface: eth1
## return: <Ipaddr>:<Netmask>:<Gateway>

def network_info(interface) : 
	cmdout = exe_shell_cmd("/sbin/ifconfig "+ interface + " | grep -sw \"inet\" | tr \":\" \" \" ")
	if len(cmdout) != 0:
		response = cmdout.split()[2] + ":" + cmdout.split()[6] + ":"
		cmdout = exe_shell_cmd("/sbin/route -n"+ "| head -n3 | grep " + interface)
		if len(cmdout) != 0:
			response += cmdout.split()[1]
		else:
			response += "0.0.0.0"
	else: 
		response = "0.0.0.0:0.0.0.0:0.0.0.0"

	return response;

############ Function to set PVID Configurations  ####################
## Port: <0-6>
## PVID: <PVID Value>
## IngressFilter: 1-Enable 0-Disable
## FrameAccType: AA - AcceptALl, AT - AcceptTagged, AU-AcceptUntagged
## PortPriority: <0-7>
## return: Success string

def set_pvidCfg(Port, PVID, IngressFilter, FrameAccType, PortPriority) :

	exe_shell_cmd("swcfg PortCfg set " + str(Port) + " vid " + str(int(PVID) | (int(PortPriority) << 13)))
	exe_shell_cmd("swcfg PortCfg set " + str(Port) + " ingress " + str(int(IngressFilter)))
	
	if FrameAccType == "AA":
		dnv = "0"
		dv  = "0"
	else:
		if FrameAccType == "AT":
			dnv = "1"
			dv  = "0"
		else:
			dnv = "0"
			dv  = "1"
	
	exe_shell_cmd("swcfg PortCfg set " + str(Port) + " drop_non_vlan " + dnv)
	exe_shell_cmd("swcfg PortCfg set " + str(Port) + " drop_tagged " + dv)

	return "Success";

############ Function to get PVID information  ####################
## ports: <No of Ports>
## return: return the all Ports info >  <PVID>:<Ingress>:<FrameAccType>:<Priority>

def pvid_info(ports) :
	port = 0
	response = ''
	while (port < ports) :
		vid = int(exe_shell_cmd("swcfg PortCfg get " + str(port) + " vid "),16)
		dnv = int(exe_shell_cmd("swcfg PortCfg get " + str(port) + " drop_non_vlan "))
		dv = int(exe_shell_cmd("swcfg PortCfg get " + str(port) + " drop_tagged "))
		ingress = int(exe_shell_cmd("swcfg PortCfg get " + str(port) + " ingress "))

		pvid = vid & ~(0xf000)
		prio = ((vid & ~(0x1fff)) >> 13)

		response += str(pvid) + ":"

		response += str(ingress) + ":"
		
		if dnv == 0 and dv == 0 :
			response += "AA:"
		else:
			if(dnv == 1) :
				response += "AT:"
			else :
				response += "AU:"
		response += str(prio) + ":"
		
		port = port + 1
		
	return response;

##############################################################################################
# 0x00 Basic Control Register	- 0.11:PowerDown 0.12:AutoNeg 0.8:DuplexMode [0.6,0.13]:Speed
# 0x01 Basic Status Register	- 1.2:LinkStatus 1.11:10HD 1.12:10FD 1.13:100HD 1.14:100FD
# 0x0a 1000Base Status Register	- a.10:HD a.11:FD
# 0x05 Partner Ability Register	- 5.8:100MFD 5.7:100MHD 5.6:10MFD 5.5:10MHD
##############################################################################################

############ Function to set Port Spped Configurations  ####################
## Port: <1-6>
## PortMode: <10MHD - 1000MFD - Auto)
## return: SUCCESS

def set_portCfg(Port,PortMode,PortSpeed) :
	# 0x00h Basic Control Register
	RegVal = int(exe_shell_cmd("swcfg PhyCfg get " + str(Port) + " 0x00"),16)
################ FIXME Need to Add Phase 2 #########################
#	if PortMode == "disable":
#		RegVal |= (0x0800)	#Set PowerDown Bit 0.11
#	else:
#		RegVal &= ~(0x0800)	#Clear PowerDown Bit 0.11
###################################################################
	if PortSpeed == "Auto" :
		RegVal |= (0x1000)	#Set AutoNeg Bit 0.12
	else:
		#Set/Clear Duplex Mode Bit 0.8 : 0 - Half, 1 - Full
		#Spped Select Bit 0.6,0.13
		# [0,0] 10Mbps : [0,1] 100Mbps : [1,0] 1000Mbps
		RegVal &= ~(0x1000) #Clear AutoNeg

		if PortSpeed == "10MHD" :
			RegVal &= ~(0x2140)
		elif PortSpeed == "10MFD" :
			RegVal |= (0x0100)
			RegVal &= ~(0x2040)
		elif PortSpeed == "100MHD" :
			RegVal &= ~(0x0140)
			RegVal |= (0x2000)
		elif PortSpeed == "100MFD" :
			RegVal &= ~(0x0040)
			RegVal |= (0x2100)
		elif PortSpeed == "1000MHD" :
			RegVal &= ~(0x2100)
			RegVal |= (0x0040)
		else :
			RegVal &= ~(0x2000)
			RegVal |= (0x0140)
		
	exe_shell_cmd("swcfg PhyCfg set " + str(Port) + " 0x00  " + hex(RegVal))	

# delay
	delay = 10000
	while delay:
		subdelay = 10000
		while subdelay:
			subdelay = subdelay -1

		delay = delay -1	

	return "SUCCESS"

############ Function to get PHY port settings  ####################
## ports : No of ports
## return: <Speed>:<LinkStatus LinkSpeed>

def port_info(ports) :
	port = 1
	response = ''
	while (port < ports) :
		RegBC = int(exe_shell_cmd("swcfg PhyCfg get " + str(port) + " 0x00"),16)
		RegBS = int(exe_shell_cmd("swcfg PhyCfg get " + str(port) + " 0x01"),16)
		RegLPA = int(exe_shell_cmd("swcfg PhyCfg get " + str(port) + " 0x05"),16)
		Reg1000BS = int(exe_shell_cmd("swcfg PhyCfg get " + str(port) + " 0x0a"),16)
################ FIXME Need to add in Phas 2 ###############
#		if (RegBC & (0x0800)) :
#			response += "disable:"
#		else :
#			response += "enable:"
############################################################
		if (RegBC & (0x1000)) :
			response += "Auto:"
		else :
			if (RegBC & (0x0100)) :
				if (RegBC & (0x0040)) and not(RegBC & (0x2000)) :
					response += "1000MFD:"
				elif not(RegBC & (0x0040)) and (RegBC & (0x2000)) :
					response += "100MFD:"
				else :
					response += "10MFD:" 
			else:
				if (RegBC & (0x0040)) and not(RegBC & (0x2000)) :
					response += "1000MHD:"
				elif not(RegBC & (0x0040)) and (RegBC & (0x2000)) :
					response += "100MHD:"
				else :
					response += "10MHD:" 

		if (RegBS & (0x0004)) :
			response += "Link Up"
			if (RegBC & (0x1000)) :
				if (Reg1000BS & (0x0c00)):
					if(Reg1000BS &(0x0800)):
						response += " - 1G Full Duplex:"
					else:
						response += " - 1G Half Duplex:"
				else:
					if(RegLPA & (0x0100)) :
						response += " - 100M Full Duplex:"
					elif (RegLPA &(0x0080)) :
						response += " - 100M Half Duplex:"
					elif (RegLPA &(0x0040)) :
						response += " - 10M Full Duplex:"
					else:
						response += " - 10M Half Duplex:"
			else:
				response += ":"
		else:
			response += "Link Down:"

		port = port + 1

	return response;

############ Function to get current VLAN configurations  ####################
## return: <No Of ALU entries>:<AluIndex>:<MAC Addr>::<PortMemberShif[M- -M]>
def static_mac_tbl_info(maxports) :
	response = "Hai"
	cmdout = exe_shell_cmd("swcfg GlobalCfg get static_table")
	alu = 0
	alus = len(cmdout.splitlines()) - 1
	
	empty_lines = 0
	while(alu < alus):
		aluinfo = cmdout.split('\n')[alu]
		if len(aluinfo.strip()) == 0 :
			empty_lines = empty_lines + 1
		alu = alu + 1
	response = str(alus - empty_lines) + "*"
	alu = 0
	while(alu < alus):
		aluinfo		= cmdout.split('\n')[alu]
		if len(aluinfo.strip()) == 0 :
			alu = alu+1
			continue
		alu_index	= int(aluinfo.split()[0].split(":")[0],16)
		alu_mac		= aluinfo.split()[1]
		mports		= int(aluinfo.split()[2],16)

		response += str(alu_index) + "*" + alu_mac + "*"
		port = 0;
		while port < maxports:
			if(mports & 1 << port):
				response += 'M-'
			else:
				response += 'N-'
			port = port+1
		alu = alu+1
		#response = response[:-1]
		response += "*"

	return response

############ Function to get current VLAN configurations  ####################
## return: <No Of Vlans>:<String>:<VlanID>:<FID>:<PortMemberShif[T-U-N]>

def vlan_info() :
	cmdout = exe_shell_cmd("swcfg GlobalCfg get vlan_table")
	vid = 0
	vids = len(cmdout.splitlines()) - 1
	
	response = str(vids) + ":" + "Ports:"
	
	while vid < vids:
		vidinfo	= cmdout.split('\n')[vid]
		vlanid 	= int(vidinfo.split()[0].split(":")[0],16)
		fid 	= int(vidinfo.split()[1],16)
		tagtype	= int(vidinfo.split()[5],16)
		mports 	= int(vidinfo.split()[6],16)
		response += str(vlanid) + ":" + str(fid) + ":"
		port = 0
		maxports = 7
		while port < maxports:
			if (mports & 1 << port):
				if (tagtype & 1 << port):
					response += ' U -';
				else:
					response += ' T -';
			else:
				response += ' N -';
			port = port +1
		vid = vid+1
		response = response[:-1]
		response += ":"
		
	return response;
	
##############################################################################################################################################

## To check if KSZ device present ##
#interface = get_interface()

interface = "eth0"

if isinstance(interface, int):
	print interface
	print "No Device Found!"
	exit()

sysfs	= "/sys/class/net/"+ interface
sw	= sysfs + "/sw"

##############################################################################################################################################
## Function to handle HTML form requests

def	exe_py_cgi():
	#### ******************** ####
	print "Content-type: text/html"
	print ""
	#### ******************** ####
	if CfgType == "DevInfo" :
		response = exe_shell_cmd("swcfg SwitchCfg get 0x0")
		response += ":" + "FutureUse:"
		response += exe_shell_cmd("swcfg GlobalCfg get ports")
		response += ":"
		response += "EVB-KSZ9477 Rev.A (UNG_8071)"
		#print "DevID:DevCap:DevPort:DisplayString:"
	elif CfgType == "SysAuth" :
		user    = form.getvalue('UserName')
		passwd  = form.getvalue('UserPasswd')
		response = exe_shell_cmd("python user_auth.py "+ user + " " +passwd)
		response = response.strip("\n")
		# FIXME
		response += ":NewlineHack"
	elif CfgType == "HostInfo" :
		response = "Host Details:\n"
		response += exe_shell_cmd("uname -a")
		#response += "\nOS Release:\n"
		#response += exe_shell_cmd("lsb_release -a")

	elif CfgType == "DrvInfo" :
		response = "lan78xx Info:\n"
		response += exe_shell_cmd("/usr/sbin/ethtool --driver "+ interface)
		response += "\nKSZ Info:\n"
		response += exe_shell_cmd("swcfg GlobalCfg get version")
		response += "GUI Version:\n"
		response += version

	elif CfgType == "TgtInfo" :
		response = "Target Chip Id:\n"
		response += exe_shell_cmd("swcfg SwitchCfg get 0x00")
		response += "\nNo Of Ports:\n"
		response += exe_shell_cmd("swcfg GlobalCfg get ports")

	elif CfgType == "SWDebug" :
		access  = form.getvalue('access')
		swreg   = form.getvalue('swReg')
		regval  = form.getvalue('RegVal')
		if regval == None :
			regval = "NULL"
		response = exe_shell_cmd("swcfg SwitchCfg "+ access + " " + swreg + " " + regval)

	elif CfgType == "PHYDebug" :
		access  = form.getvalue('access')
		phyid   =  form.getvalue('PhyId')
		phyreg     =  form.getvalue('PhyReg')
		regval  = form.getvalue('RegVal')

		if regval == None :
			regval = "NULL"

		response = exe_shell_cmd("swcfg PhyCfg "+ access + " " + phyid + " " + phyreg + " " + regval)

	elif CfgType == "SystemDebug" :
		cmd = form.getvalue('ShellCmd')
		response = exe_shell_cmd(cmd)

	elif CfgType == "IPSettings" :
		SetType = form.getvalue('IpSetType')
		IpAddr = form.getvalue('IpAddr')
		SNMask = form.getvalue('SNMask')
		DGAddr = form.getvalue('DGAddr')

		if SetType == "manual" :
			exe_shell_cmd("swcfg SystemCfg "+ "\"/sbin/ifconfig "+ interface + " " + IpAddr + " " + "netmask "+ SNMask + " up\"")
			exe_shell_cmd("swcfg SystemCfg \"/sbin/route add default gw " + DGAddr + "\"" )
		if SetType == "dhcp" :
			#exe_shell_cmd("swcfg SystemCfg \"/sbin/ifconfig " + interface + " 0.0.0.0 up\"")
			exe_shell_cmd("swcfg SystemCfg \"/usr/bin/killall udhcpc " + "\"")
			exe_shell_cmd("swcfg SystemCfg \"/sbin/udhcpc " + "\"")

		response = network_info(interface)

	elif CfgType == "GVLANCfg" :
		GVlanCfg = form.getvalue('VlanState')
	#FIXME	Parsing is not generic
		if GVlanCfg != "x":
			exe_shell_cmd("swcfg GlobalCfg set vlan "+ GVlanCfg)
		
		cmdout = exe_shell_cmd("swcfg GlobalCfg get vlan")
		response = cmdout.split('\n')[0]
		if cmdout.split('\n')[0] == "1":
			response = "1:1"
		else:
			response = "0:0"

	elif CfgType == "GMTUInfo" :
		mtu_size = form.getvalue('MTUSize')
		if mtu_size == None :
			return exe_shell_cmd("swcfg GlobalCfg get mtu")
		exe_shell_cmd("swcfg GlobalCfg set mtu "+ mtu_size)
		response = exe_shell_cmd("swcfg GlobalCfg get mtu")

	elif CfgType == "GJumboSupport" :
		jumbo_support = form.getvalue('JumboFrame')
	#FIXME	Parsing is not generic
		if jumbo_support != "x":
			exe_shell_cmd("swcfg GlobalCfg set jumbo_packet "+ jumbo_support)

		cmdout = exe_shell_cmd("swcfg GlobalCfg get jumbo_packet")
		if cmdout.split('\n')[0] == "1":
			response = "1:1"
		else:
			response = "0:0"

	elif CfgType == "PortCfg" :
		Port = form.getvalue('Port')
		if Port != None :
			mode = "Mode" + Port
			speed = "LinkSpeed" + Port
			PortMode	= form.getvalue(mode)
			PortSpeed	= form.getvalue(speed)
			response = set_portCfg(int(Port),PortMode,PortSpeed)
		else:
			Port = "FIXME"
		response = port_info(6)
		#response = "disable:10MFD:P1:disable:100MFD:P2:disable:1000MFD:P3:enable:10MHD:P4:enable:100MHD:P5:disable:1000MHD:HIT"

	elif CfgType == "VlanInfo" :
		response = vlan_info()

	elif CfgType == "VlanCfg" :
		VID		= form.getvalue("Vid")
		FID 		= form.getvalue('Fid')
		UntagMembers 	= form.getvalue("UntagMembers")
		VlanMembers 	= form.getvalue("VlanMembers")
		VlanAction 	= form.getvalue("VlanAction")
		exe_shell_cmd("swcfg GlobalCfg set vlan_index "+ VID)
		exe_shell_cmd("swcfg GlobalCfg set vlan_fid "+ FID)
		exe_shell_cmd("swcfg GlobalCfg set vlan_ports "+ hex(int(VlanMembers)))
		exe_shell_cmd("swcfg GlobalCfg set vlan_untag "+ hex(int(UntagMembers)))
		if VlanAction == "Add":
			exe_shell_cmd("swcfg GlobalCfg set vlan_valid 1")
		else:
			exe_shell_cmd("swcfg GlobalCfg set vlan_valid 0")
		response = "Success"

	elif CfgType == "PVIDCfg" :
		Port = form.getvalue('PVIDPort')
		if Port != None :
			PVID		= form.getvalue("Pvid"+Port)
			IngressFilter	= form.getvalue("IngressFilter"+Port)
			FrameAccType	= form.getvalue("FrameAccType"+Port)
			PortPriority	= form.getvalue("PortPriority"+Port)
			set_pvidCfg(int(Port)-1,PVID,IngressFilter,FrameAccType,PortPriority)
		else:
			Port = "FIXME"

		#response = "HI:1:AA:5:11:1:AA:5:11:1:AA:6:11:1:AA:6:11:1:AA:6:11:1:AA:6:11:1:AA:6:"
		response = pvid_info(7)

	elif CfgType == "DynamicMACInfo" :
		TblClear = form.getvalue('FormCmd')
		TblType = form.getvalue('TblType')
		if TblClear == "Clear" :
			exe_shell_cmd("swcfg GlobalCfg set "+TblType+" 0")
		response = exe_shell_cmd("swcfg GlobalCfg get "+TblType)

	elif CfgType == "StaticMacCfg" :
		alu_index		= form.getvalue('ALUIndex')
		alu_addr		= form.getvalue('ALUMACAddr')
		alu_port_members	= form.getvalue('ALUMembers')
		alu_action		= form.getvalue('ALUAction')	

		exe_shell_cmd("swcfg GlobalCfg set alu_index " + str(hex(int(alu_index))))
		exe_shell_cmd("swcfg GlobalCfg set alu_addr " +  alu_addr)
		exe_shell_cmd("swcfg GlobalCfg set alu_ports " + str(hex(int(alu_port_members))))
		
		if alu_action == "Add":
			exe_shell_cmd("swcfg GlobalCfg set alu_valid 1")
		else:
			exe_shell_cmd("swcfg GlobalCfg set alu_valid 0")
		response = str(hex(int(alu_index))) + ":" + alu_addr + "#" + str(hex(int(alu_port_members)))
			
	elif CfgType == "StaticMacInfo" :
		response = static_mac_tbl_info(7)
		#response = "1*10*AA:BB:CC:DD:EE:FF*M-M-M- -M-M-M"

	elif CfgType == "SWStats" :
		MIBClear = form.getvalue('FormCmd')
		if MIBClear == "Clear" :
			exe_shell_cmd("swcfg GlobalCfg set mib 0")
		response = exe_shell_cmd("swcfg GlobalCfg get mib")

	elif CfgType == "PortStats" :
		MIBClear = form.getvalue('FormCmd')
		Port = form.getvalue('StatPort')
		if Port != None :
			if MIBClear != None and MIBClear == "Clear" :
				response = exe_shell_cmd("swcfg PortCfg set "+ str(Port) + " mib 0")
			response = exe_shell_cmd("swcfg PortCfg get "+ str(Port) + " mib")
		else:
			response = "Port Not Selected!"

	else:
		print "Invalid Request!"
		exit()
	#cgi.escape(exe_shell_cmd("ifconfig"))

	return response

##############################################################################################################################################
## Getting Form Parameters
form = cgi.FieldStorage()
CfgType	= form.getvalue("CMD") ## CMD is PostMethod argument to differentiate the request type.

print exe_py_cgi() ## Backend request / response Processing

exit()

##############################################################################################################################################
