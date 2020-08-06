#
# Copyright (c) 2018-2020, Anton Kikin <a.kikin@tano-systems.com>
#
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

PV = "${DISTRO_VERSION}"
PR = "tano3"

SRC_URI = "file://os-release"

PACKAGES = "${PN}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit tanowrt-version

do_install() {
	install -d ${D}${libdir}
	install -d ${D}${sysconfdir}

	install -m 0644 ${WORKDIR}/os-release ${D}${libdir}/os-release
	ln -s ${libdir}/os-release ${D}${sysconfdir}/os-release

	# Run VERSION_SED script
	${OPENWRT_VERSION_SED} \
		${D}/usr/lib/os-release
}

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

INSANE_SKIP_${PN} += "build-deps"

RPROVIDES_${PN} = "os-release"
RREPLACES_${PN} = "os-release"
RCONFLICTS_${PN} = "os-release"

FILES_${PN} += "${libdir}"
