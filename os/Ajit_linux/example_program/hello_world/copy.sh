#!/bin/sh

# Script to copy the binary to corresponding Overlay locations.
# Comment out one/both of the following accoring to the build.
# Default: Both

# For initramfs filesystem
cp *.bin $AJIT_LINUX_DIR/Ajit_buildroot_configs/board/rootfs_overlay/home

# For tmpfs-rootfs filesystem
cp *.bin $AJIT_LINUX_DIR/Ajit_buildroot_configs/board/overlay/rootfs/home
