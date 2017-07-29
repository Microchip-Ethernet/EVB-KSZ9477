#!/bin/sh

# This script invokes Linux PTP to run in E2E mode.

PORT0=eth0
VERBOSE="-l 4"

if [ "$1" = "-v" ]; then
    VERBOSE="-m"
    shift
fi
if [ ! -z "$1" ]; then
    PORT0=$1
fi
if [ ! -e "/sys/class/net/$PORT0" ]; then
    echo "$PORT0 not existed"
    exit 1
fi

ptp4l -p /dev/ptp0 -i $PORT0 -f default.cfg $VERBOSE
