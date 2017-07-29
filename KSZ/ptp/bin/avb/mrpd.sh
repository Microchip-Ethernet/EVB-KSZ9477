#!/bin/sh

# This script invokes Intel MRP daemon.

PORT0=eth0

if [ ! -z "$1" ]; then
    PORT0=$1
fi
if [ ! -e "/sys/class/net/$PORT0" ]; then
    echo "$PORT0 not existed"
    exit 1
fi
ETH=0
VLAN=201

if [ ! -z "$1" ]; then
    ETH=$1
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

mrpd -mvsd -i eth$ETH
