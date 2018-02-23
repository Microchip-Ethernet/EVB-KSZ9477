#!/bin/sh

# This script invokes Linux PTP to run in power profile mode.

ETH=0
VLAN=0
DEV=0
VERBOSE="-l 4"
ETH_SET=0
VLAN_SET=0

while [ ! -z "$1" ]; do
    if [ "$1" = "-v" ]; then
        VERBOSE="-m"
    elif [ $1 -ge 0 ] && [ $1 -lt 4096 ]; then
        if [ $VLAN_SET -eq 0 ]; then
            VLAN=$1
            VLAN_SET=1
        elif [ $ETH_SET -eq 0 ]; then
            ETH=$1
            ETH_SET=1
        fi
    fi
    shift
done

if [ -e "/sys/class/net/eth$ETH/sw/dev_start" ]; then
    DEV=$(cat /sys/class/net/eth$ETH/sw/dev_start)
fi

PORTS=2
if [ -e "/sys/class/net/eth$ETH/sw/ports" ]; then
    PORTS=$(cat /sys/class/net/eth$ETH/sw/ports)
fi

HOST_PORT=3
if [ -e "/sys/class/net/eth$ETH/sw/host_port" ]; then
    HOST_PORT=$(cat /sys/class/net/eth$ETH/sw/host_port)
    let PORTS=$PORTS-1
fi

p=0
while [ $p -lt $PORTS ]; do
    let q=$DEV+$p
    if [ ! -e "/sys/class/net/eth$ETH.$q.$VLAN" ]; then
        echo "eth$ETH.$q.$VLAN not existed"
        exit 1
    fi
    let p=$p+1
done

ptp4l -p /dev/ptp0 -i eth$ETH.$DEV.$VLAN -n $PORTS -f default.cfg $VERBOSE -R
