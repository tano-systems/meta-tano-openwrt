#
# SPDX-License-Identifier: MIT
#
# Copyright (C) 2021 Tano Systems LLC. All rights reserved.
# Authors: Anton Kikin <a.kikin@tano-systems.com>
#

PR_append = ".1"

KCONFIG_MODE = "--alldefconfig"

# Config
SRC_URI_append_evb-ksz9563 = " file://defconfig"

# Devicetree files
SRC_URI_append = "\
	file://at91-evb-ksz9563.dts \
"

require ${TANOWRT_BASE}/recipes-kernel/linux-addons/microchip-ethernet.inc
