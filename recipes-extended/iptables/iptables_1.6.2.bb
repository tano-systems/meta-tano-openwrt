PR = "tano3"

SUMMARY = "Tools for managing kernel packet filtering capabilities"
DESCRIPTION = "iptables is the userspace command line program used to configure and control network packet \
filtering code in Linux."
HOMEPAGE = "http://www.netfilter.org/"
BUGTRACKER = "http://bugzilla.netfilter.org/"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263\
                    file://iptables/iptables.c;beginline=13;endline=25;md5=c5cffd09974558cf27d0f763df2a12dc"

RDEPENDS_${PN} += "kmod-ipt-core"
RDEPENDS_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'ipv6', 'kmod-ip6tables', '', d)}"
do_configure[depends] += "virtual/kernel:do_shared_workdir"

FILES_${PN} =+ "${libdir}/xtables/ ${datadir}/xtables"

SRC_URI = "http://netfilter.org/projects/iptables/files/iptables-${PV}.tar.bz2 \
           file://0001-configure-Add-option-to-enable-disable-libnfnetlink.patch \
           file://0002-configure.ac-only-check-conntrack-when-libnfnetlink-enabled.patch \
"

SRC_URI[md5sum] = "7d2b7847e4aa8832a18437b8a4c1873d"
SRC_URI[sha256sum] = "55d02dfa46263343a401f297d44190f2a3e5113c8933946f094ed40237053733"

inherit autotools pkgconfig

EXTRA_OECONF = "--with-kernel=${STAGING_INCDIR} \
               "
PACKAGECONFIG ?= "${@bb.utils.filter('DISTRO_FEATURES', 'ipv6', d)}"

PACKAGECONFIG[ipv6] = "--enable-ipv6,--disable-ipv6,"

# libnfnetlink recipe is in meta-networking layer
PACKAGECONFIG[libnfnetlink] = "--enable-libnfnetlink,--disable-libnfnetlink,libnfnetlink libnetfilter-conntrack"

# libnftnl recipe is in meta-networking layer(previously known as libnftables)
PACKAGECONFIG[libnftnl] = "--enable-nftables,--disable-nftables,libnftnl"

do_configure_prepend() {
	# Remove some libtool m4 files
	# Keep ax_check_linker_flags.m4 which belongs to autoconf-archive.
	rm -f libtool.m4 lt~obsolete.m4 ltoptions.m4 ltsugar.m4 ltversion.m4
}
