#!/bin/sh

# This script invokes Linux PTP phc2sys to synchronize system clock.

VERBOSE="-l 4"

if [ "$1" = "-v" ]; then
    VERBOSE="-m"
    shift
fi

phc2sys -s /dev/ptp0 -w $VERBOSE
