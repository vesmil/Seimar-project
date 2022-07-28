#!/bin/sh
PKG_CONFIG_SYSROOT_DIR=/opt/petalinux/2021.2/sysroots/cortexa72-cortexa53-xilinx-linux
export PKG_CONFIG_SYSROOT_DIR
PKG_CONFIG_LIBDIR=/opt/host-wiris-pro-tinyrex/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/pkgconfig:/opt/host-wiris-pro-tinyrex/arm-buildroot-linux-gnueabihf/sysroot/usr/share/pkgconfig:/opt/host-wiris-pro-tinyrex/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/arm-linux-gnueabihf/pkgconfig
export PKG_CONFIG_LIBDIR
exec pkg-config "$@"
