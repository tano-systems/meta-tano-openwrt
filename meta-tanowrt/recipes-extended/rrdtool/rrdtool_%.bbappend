#
# SPDX-License-Identifier: MIT
# Copyright (c) 2018-2020 Tano Systems LLC. All rights reserved.
#
PR_append = "${@oe.utils.version_less_or_equal('PV', '1.0.50', '', '.tano0', d)}"
RDEPENDS_${PN} += "${@oe.utils.version_less_or_equal('PV', '1.0.50', '', 'ttf-dejavu-sans-mono', d)}"
