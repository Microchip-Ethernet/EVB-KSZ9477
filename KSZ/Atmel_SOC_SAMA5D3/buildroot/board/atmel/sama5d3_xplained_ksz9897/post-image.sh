#!/bin/sh

DTB=$(grep BR2_LINUX_KERNEL_INTREE_DTS_NAME .config | cut -d"\"" -f2)

cp -p ${BINARIES_DIR}/$DTB.dtb ${BINARIES_DIR}/at91-sama5d3_xplained.dtb

