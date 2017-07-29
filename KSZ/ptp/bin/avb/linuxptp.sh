#!/bin/sh

# This script invokes Linux PTP to run in AVB mode.

ETH=0
VLAN=201
VERBOSE="-l 4"
START=

if [ "$1" = "-v" ]; then
    VERBOSE="-m"
    shift
fi

if [ ! -z "$1" ]; then
    ETH=$1
    shift
fi

if [ "$1" = "-v" ]; then
    VERBOSE="-m"
    shift
fi

if [ -e "/sys/class/net/eth$ETH/sw/vlan_start" ]; then
    VLAN=$(cat /sys/class/net/eth$ETH/sw/vlan_start)
    let VLAN=$VLAN+1
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
    let q=$VLAN+$p
    if [ ! -e "/sys/class/net/eth$ETH.$q" ]; then
        echo "eth$ETH.$q not existed"
        exit 1
    fi
    let p=$p+1
done

ptp4l -p /dev/ptp0 -i eth$ETH.$VLAN -n $PORTS -f gPTP.cfg $VERBOSE $START
