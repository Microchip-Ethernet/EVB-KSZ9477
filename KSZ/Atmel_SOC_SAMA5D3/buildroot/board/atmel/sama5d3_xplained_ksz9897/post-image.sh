#!/bin/sh

DTB=$(grep BR2_LINUX_KERNEL_INTREE_DTS_NAME $BR2_CONFIG | cut -d"\"" -f2)

if [ "$DTB" != "at91-sama5d3_xplained" ]; then
cp -p ${BINARIES_DIR}/$DTB.dtb ${BINARIES_DIR}/at91-sama5d3_xplained.dtb
fi

