#!/bin/bash

# Remove 
#       - contents of "build" drirectory
#       - overlay contents from rootfs

rm -rf build/
rm -rf $AJIT_LINUX_DIR/Ajit_buildroot_configs/board/rootfs_overlay/home/Ajit_overlay
rm -rf $AJIT_LINUX_DIR/Ajit_buildroot_configs/board/overlay/rootfs/home/Ajit_overlay