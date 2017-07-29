#!/bin/sh

# This script setups the VLAN for use with power profile.

ETH=0
VLAN=0
PRIO=4

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

vconfig add eth$ETH $VLAN
vconfig set_egress_map eth$ETH.$VLAN 0 $PRIO
MAC=$(ifconfig eth$ETH | grep HWaddr | cut -d":" -f7)
SUBNET=$(ifconfig eth$ETH | grep "inet addr" | cut -d":" -f2 | cut -d" " -f1)
if [ ! -z "$SUBNET" ]; then
    SUBNET1=$(echo "$SUBNET" | cut -d"." -f1)
    SUBNET2=$(echo "$SUBNET" | cut -d"." -f2)
    SUBNET3=$(echo "$SUBNET" | cut -d"." -f3)
else
    SUBNET1="10"
    SUBNET2="1"
    SUBNET3="157"
fi
MAC=$((0x$MAC))
ifconfig eth$ETH.$VLAN $SUBNET1.$SUBNET2.$VLAN.$MAC
if [ -e "/sys/class/net/eth$ETH/ptp/vid" ]; then
    echo "$VLAN" > "/sys/class/net/eth$ETH/ptp/vid"
fi

