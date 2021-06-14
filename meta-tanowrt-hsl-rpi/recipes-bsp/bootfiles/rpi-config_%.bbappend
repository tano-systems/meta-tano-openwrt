#
# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Tano Systems LLC. All rights reserved.
#

PR_append = ".tano1"

RPI_CMDLINE ?= ""

do_deploy_append() {
	if [ -n "${RPI_CMDLINE}" ]; then
		echo "${RPI_CMDLINE}" > ${DEPLOYDIR}/${BOOTFILES_DIR_NAME}/cmdline.txt
	fi

	if [ "${@bb.utils.contains('COMBINED_FEATURES', 'alsa', '1', '0', d)}" = "1" ]; then
		echo "# Enable audio (loads snd_bcm2835)" >> ${DEPLOYDIR}/${BOOTFILES_DIR_NAME}/config.txt
		echo "dtparam=audio=on" >> ${DEPLOYDIR}/${BOOTFILES_DIR_NAME}/config.txt
	fi
}