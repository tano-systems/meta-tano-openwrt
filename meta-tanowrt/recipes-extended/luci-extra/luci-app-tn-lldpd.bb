#
# LuCI support for LLDP daemon
# OpenWrt/LEDE 18.06.x, 19.07
#
# Copyright (c) 2018-2020, Tano Systems. All Rights Reserved.
# Anton Kikin <a.kikin@tano-systems.com>
#
PV = "1.2.1+git${SRCPV}"
PR = "tano22"

SUMMARY = "LuCI support for LLDP daemon"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=aed2cf5a7c273a7c2dcdbd491a3a8416"

GIT_BRANCH   = "master"
GIT_SRCREV   = "e6a43a705345a3f3e04afef574575f075f63d620"
GIT_PROTOCOL = "https"

SRC_URI = "git://github.com/tano-systems/luci-app-tn-lldpd.git;branch=${GIT_BRANCH};protocol=${GIT_PROTOCOL}"
SRCREV = "${GIT_SRCREV}"

RDEPENDS_${PN} += "lldpd luci-compat"

S = "${WORKDIR}/git"

inherit openwrt-luci-app
inherit openwrt-luci-i18n
inherit luasrcdiet
