#
# SPDX-License-Identifier: MIT
#
# Copyright (C) 2015 Khem Raj <raj.khem@gmail.com>
# Copyright (C) 2018 Daniel Dickinson <cshored@thecshore.com>
# Copyright (C) 2018-2021 Anton Kikin <a.kikin@tano-systems.com>
#

INC_PR = "11"

PACKAGECONFIG[ubus] = ",,libubus"
PACKAGECONFIG[broken-rtc] = ",,"
PACKAGECONFIG[no-id] = ",,"

EXTRA_OEMAKE += "\
    'COPTS+=${@bb.utils.contains('PACKAGECONFIG', 'ubus', '-DHAVE_UBUS', '', d)}' \
    'COPTS+=${@bb.utils.contains('PACKAGECONFIG', 'no-id', '-DNO_ID', '', d)}' \
    'COPTS+=${@bb.utils.contains('PACKAGECONFIG', 'broken-rtc', '-DHAVE_BROKEN_RTC', '', d)}' \
"

PACKAGECONFIG += "ubus conntrack no-id"

# Patches
SRC_URI += "\
	file://0001-Tweak-sort-order-of-tags-in-get-version.patch \
	file://0002-Tweak-f1204a875e0f16fd645df965db346fc56d2ab1dd.patch \
	file://100-remove-old-runtime-kernel-support.patch \
"

# Files
SRC_URI += "\
	file://dhcp.conf \
	file://dnsmasq.conf \
	file://dhcpbogushostname.conf \
	file://dnsmasqsec.hotplug \
	file://dnsmasq.init \
	file://dnsmasq_acl.json \
	file://dhcp-script.sh \
	file://rfc6761.conf \
	file://50-dnsmasq-migrate-resolv-conf-auto.sh \
"

inherit tanowrt-services useradd

TANOWRT_SERVICE_PACKAGES = "dnsmasq"
TANOWRT_SERVICE_SCRIPTS_dnsmasq += "dnsmasq"
TANOWRT_SERVICE_STATE_dnsmasq-dnsmasq ?= "enabled"

do_install_append() {
    install -d ${D}${sysconfdir}
    install -d ${D}${sysconfdir}/config
    install -d ${D}${sysconfdir}/init.d
    install -d ${D}${sysconfdir}/rc.d
    install -d ${D}${sbindir}

    install -m 0644 ${WORKDIR}/dnsmasq.conf ${D}${sysconfdir}/
    install -m 0644 ${WORKDIR}/dhcp.conf ${D}${sysconfdir}/config/dhcp
    install -m 0755 ${WORKDIR}/dnsmasq.init ${D}${sysconfdir}/init.d/dnsmasq

    install -d ${D}${sysconfdir}/hotplug.d/ntp
    install -d ${D}${sysconfdir}/hotplug.d/dhcp
    install -d ${D}${sysconfdir}/hotplug.d/neigh
    install -d ${D}${sysconfdir}/hotplug.d/tftp
    install -m 0644 ${WORKDIR}/dnsmasqsec.hotplug ${D}${sysconfdir}/hotplug.d/ntp/25-dnsmasqsec

    install -d ${D}/usr/lib/dnsmasq
    install -m 0755 ${WORKDIR}/dhcp-script.sh ${D}/usr/lib/dnsmasq/dhcp-script.sh

    install -d ${D}/usr/share/dnsmasq
    install -m 0644 ${WORKDIR}/rfc6761.conf ${D}/usr/share/dnsmasq/rfc6761.conf
    install -m 0644 ${WORKDIR}/dhcpbogushostname.conf ${D}/usr/share/dnsmasq/dhcpbogushostname.conf
    install -m 0644 ${B}/trust-anchors.conf ${D}/usr/share/dnsmasq

    install -d ${D}/usr/share/acl.d
    install -m 0644 ${WORKDIR}/dnsmasq_acl.json ${D}/usr/share/acl.d/dnsmasq_acl.json

    install -d ${D}${sysconfdir}/uci-defaults
    install -m 0755 ${WORKDIR}/50-dnsmasq-migrate-resolv-conf-auto.sh ${D}${sysconfdir}/uci-defaults/

    # dnsmasq installs in /usr/bin, openwrt looks for it in /usr/sbin
    ln -s ${bindir}/dnsmasq ${D}${sbindir}/dnsmasq

    # remove unused in OpenWrt files/folders
    rm -rf ${D}${bindir}/dhcp_release
    rm -rf ${D}${sysconfdir}/dnsmasq.d
    rm -rf ${D}${sysconfdir}/systemd
    rm -rf ${D}${sysconfdir}/rc.d
}

USERADD_PACKAGES = "${PN}"

USERADD_PARAM_${PN} = "--system -d /var/run/dnsmasq --no-create-home \
  --shell /bin/false --user-group dnsmasq"

RDEPENDS_${PN} += "jsonpath"
inherit kmod/ipt-ipset
do_configure[depends] += "virtual/kernel:do_shared_workdir"

FILES_${PN}_append = "\
	/usr/share \
"

CONFFILES_${PN}_append = "\
	${sysconfdir}/config/dhcp \
	${sysconfdir}/dnsmasq.conf \
	${sysconfdir}/dnsmasq.d/ \
"

inherit uci-config

TANOWRT_DHCPS_CONFIGURE ?= "0"
TANOWRT_DHCPS_LAN_ENABLE ?= "1"
TANOWRT_DHCPS_LAN_INTERFACE ?= "lan"
TANOWRT_DHCPS_LAN_START ?= "100"
TANOWRT_DHCPS_LAN_LIMIT ?= "150"
TANOWRT_DHCPS_LAN_UCI_SECTION ?= "${TANOWRT_DHCPS_LAN_INTERFACE}"

do_uci_config_append() {
	if [ "${TANOWRT_DHCPS_CONFIGURE}" = "1" ]; then
		if [ "${TANOWRT_DHCPS_LAN_ENABLE}" = "1" ]; then
			${UCI} set dhcp.${TANOWRT_DHCPS_LAN_UCI_SECTION}.ignore="0"
			${UCI} set dhcp.${TANOWRT_DHCPS_LAN_UCI_SECTION}.start="${TANOWRT_DHCPS_LAN_START}"
			${UCI} set dhcp.${TANOWRT_DHCPS_LAN_UCI_SECTION}.limit="${TANOWRT_DHCPS_LAN_LIMIT}"
			${UCI} set dhcp.${TANOWRT_DHCPS_LAN_UCI_SECTION}.interface="${TANOWRT_DHCPS_LAN_INTERFACE}"
		else
			${UCI} set dhcp.${TANOWRT_DHCPS_LAN_UCI_SECTION}.ignore="1"
		fi

		${UCI} commit dhcp
	fi
}
