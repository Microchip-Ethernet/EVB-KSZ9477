#!/bin/sh

BOARD_DIR="$(dirname $0)"
GENIMAGE_CFG="${BOARD_DIR}/genimage.cfg"
GENIMAGE_TMP="${BUILD_DIR}/genimage.tmp"

DTB=$(grep BR2_LINUX_KERNEL_INTREE_DTS_NAME $BR2_CONFIG | cut -d"\"" -f2)

cp -p ${BINARIES_DIR}/$DTB.dtb ${BINARIES_DIR}/at91-sama5d3_xplained.dtb
install -p -m 644 ${BOARD_DIR}/uboot.env ${BINARIES_DIR}/uboot.env

rm -rf "${GENIMAGE_TMP}"

genimage                               \
	--rootpath "${TARGET_DIR}"     \
	--tmppath "${GENIMAGE_TMP}"    \
	--inputpath "${BINARIES_DIR}"  \
	--outputpath "${BINARIES_DIR}" \
	--config "${GENIMAGE_CFG}"
