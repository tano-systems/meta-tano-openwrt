#
# SPDX-License-Identifier: MIT
#
# LuCI Material Theme (default)
#
# This file Copyright (c) 2018 Tano Systems LLC. All rights reserved.
# Anton Kikin <a.kikin@tano-systems.com>
#
PR = "tano3"
DESCRIPTION = "LuCI Material Theme"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

LUCI_THEME_NAME = "material"

inherit tanowrt-luci-theme

SRC_URI = "${LUCI_GIT_URI};branch=${LUCI_GIT_BRANCH};protocol=${LUCI_GIT_PROTOCOL};subpath=themes/luci-theme-material;destsuffix=git/"
SRCREV = "${LUCI_GIT_SRCREV}"
S = "${WORKDIR}/git"
