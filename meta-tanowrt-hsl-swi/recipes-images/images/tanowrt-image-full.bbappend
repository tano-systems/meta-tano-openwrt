#
# SPDX-License-Identifier: MIT
# Copyright (c) 2020 Tano Systems LLC. All rights reserved.
#
PR_append = ".swi0"
inherit tanowrt-swi-image

CORE_IMAGE_EXTRA_INSTALL_remove = "\
	ncurses \
	ncurses-terminfo \
	htop \
"
