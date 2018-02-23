#!/bin/sh

# This script setups the VLAN for use with power profile.

ETH=0
VLAN=0
PRIO=4
DEV=0

if [ ! -z "$1" ]; then
    VLAN=$1
    if [ ! -z "$2" ]; then
        ETH=$2
        if [ ! -z "$3" ]; then
            PRIO=$3
        fi
    fi
fi

if [ -e "/sys/class/net/eth$ETH.$VLAN" ]; then
    exit 0
fi

if [ -e "/sys/class/net/eth$ETH/sw/dev_start" ]; then
    DEV=$(cat /sys/class/net/eth$ETH/sw/dev_start)
fi

PORTS=2
if [ -e "/sys/class/net/eth$ETH/sw/ports" ]; then
    PORTS=$(cat /sys/class/net/eth$ETH/sw/ports)
fi

MASK=0x7

HOST_PORT=3
if [ -e "/sys/class/net/eth$ETH/sw/host_port" ]; then
    HOST_PORT=$(cat /sys/class/net/eth$ETH/sw/host_port)
    if [ $PORTS -eq 7 ]; then
        MASK=0x7f
    elif [ $PORTS -eq 6 ]; then
        MASK=0x3f
    fi
    let PORTS=$PORTS-1
fi

vconfig add eth$ETH $VLAN
vconfig set_egress_map eth$ETH.$VLAN 0 $PRIO
ifconfig eth$ETH.$VLAN up

if [ $DEV -gt 0 ]; then
    p=0
    while [ $p -lt $PORTS ]; do
        let q=$DEV+$p
        vconfig add eth$ETH.$q $VLAN
        vconfig set_egress_map eth$ETH.$q.$VLAN 0 $PRIO
        ifconfig eth$ETH.$q.$VLAN up
        let p=$p+1
    done
fi

if [ -e "/sys/class/net/eth$ETH/sw/vlan_index" ]; then
    echo $VLAN > "/sys/class/net/eth$ETH/sw/vlan_index"
    echo $MASK > "/sys/class/net/eth$ETH/sw/vlan_ports"
    echo 1 > "/sys/class/net/eth$ETH/sw/vlan_valid"
fi

