# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: 2021 Tano Systems LLC

test -n ${loadaddr} || setenv loadaddr 0x82000000;
test -n ${baudrate} || setenv baudrate 115200;
test -n ${optargs} || setenv optargs "panic=15";
