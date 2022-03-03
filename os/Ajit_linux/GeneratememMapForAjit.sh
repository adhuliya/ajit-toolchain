#!/bin/bash

CWD=$PWD
BUILD_DIR=$CWD/build
BUILD_C_DIR=$CWD/build/c_model
BUILD_FPGA_DIR=$CWD/build/fpga
BUILD_COMMON_DIR=$CWD/build/common
BUILDROOT_TAR=$CWD/buildroot-2014.08.tar.gz
OVERLAY_DIR=$CWD/Ajit_overlay
BUILDROOT_BUILD_DIR=$BUILD_COMMON_DIR/buildroot-2014.08
FPGA_BIN_DIR=$BUILD_FPGA_DIR/linux_boot
BOOTLOADER_C_BUILD_DIR=$BUILD_C_DIR/Ajit_bootloader
BOOTLOADER_FPGA_BUILD_DIR=$BUILD_FPGA_DIR/Ajit_bootloader
LINUX_BUILD_DIR=$BUILDROOT_BUILD_DIR/output/build/linux-custom
BUSYBOX_BUILD_DIR=$BUILDROOT_BUILD_DIR/output/build/busybox-1.22.1

# Check for presence of Argumentsand throw an error when there is none or invalid one.
if [ "$#" -ne 1 ] || [ "$1" -lt 1 ] || [ "$1" -gt 2 ]; then
  echo "ERROR: Invalid or missing argument...."
  echo "Usage: $0 <DEFCONFIG>"
  echo ""
  echo "DEFCONFIG values"
  echo "    <1> legacy initramfs system config;no rootfs-tmpfs present"
  echo "    <2> rootfs-tmpfs with satic-lib & static device list"
  exit 1
fi

function copy_things() {
  # If you're running this script for the first time,
  # the destination folders may not exist.
  # Let's create them first.

  if ! [ -d "$BUILD_DIR" ]; then
    echo "================================================="
    echo " STEP 0.1: "
    echo " Creating folder build"
    echo "================================================="
    mkdir -p $BUILD_C_DIR $BUILD_FPGA_DIR $BUILD_COMMON_DIR
  fi

  # Copy device-tree and bootloader sources to build area.
  cp -r $CWD/Ajit_device_tree $BUILD_C_DIR
  cp -r $CWD/Ajit_device_tree $BUILD_FPGA_DIR
  cp -r $CWD/Ajit_bootloader $BUILD_C_DIR
  cp -r $CWD/Ajit_bootloader $BUILD_FPGA_DIR

  if ! [ -d "$BUILDROOT_BUILD_DIR" ]; then
    tar -xvf $BUILDROOT_TAR --directory=$BUILD_COMMON_DIR
    mkdir -p $BUILDROOT_BUILD_DIR/dl && \
    cp $CWD/br2-dl/* $BUILDROOT_BUILD_DIR/dl
  fi

  if ! [ -d "$LINUX_BUILD_DIR" ]; then
    echo "================================================="
    echo " STEP 0.2: "
    echo " Creating folder build/buildroot-2014.08/output/build/linux-custom"
    echo "================================================="
    mkdir -p $LINUX_BUILD_DIR
  fi

  if ! [ -d "$BUSYBOX_BUILD_DIR" ]; then
    echo "================================================="
    echo " STEP 0.3: "
    echo " Creating folder build/buildroot-2014.08/output/build/busybox-1.22.1"
    echo "================================================="
    mkdir -p $BUSYBOX_BUILD_DIR
  fi

  # copy FPGA bin generation files to build area
  cp $CWD/linux_boot $BUILD_FPGA_DIR

  echo "================================================="
  echo " STEP 1.1: "
  echo "  copying kernel source code (using rync)"
  echo "  from: ./Ajit_linux_3.16.1/"
  echo "  to  : ./buildroot-2014.08/output/build/linux-custom"
  echo "================================================="

  rsync -av --exclude .svn --exclude .git --exclude .hg --exclude .bzr --exclude CVS $CWD/Ajit_linux_3.16.1/ $LINUX_BUILD_DIR

  echo "================================================="
  echo " STEP 1.2: "
  echo "  copying Busybox source code (using rync)"
  echo "  from: ./Ajit_busybox-1.22.1/"
  echo "  to  : ./buildroot-2014.08/output/build/busybox-1.22.1"
  echo "================================================="

  rsync -av --exclude .svn --exclude .git --exclude .hg --exclude .bzr --exclude CVS $CWD/Ajit_busybox-1.22.1/ $BUSYBOX_BUILD_DIR


  echo " Running make clean inside linux build directory"
  cd $LINUX_BUILD_DIR
  make clean

  echo "================================================="
  echo " STEP 1.3: "
  echo "  copying Overlay to rootfs"
  echo "  from: ./Ajit_overlay /"
  echo "  to  : ./Ajit_buildroot_configs/board/rootfs_overlay/home"
  echo "        ./Ajit_buildroot_configs/board/overlay/rootfs/home"
  echo "================================================="

  cp -r $OVERLAY_DIR $AJIT_LINUX_DIR/Ajit_buildroot_configs/board/rootfs_overlay/home
  cp -r $OVERLAY_DIR $AJIT_LINUX_DIR/Ajit_buildroot_configs/board/overlay/rootfs/home


}

function linux_build() {
  echo "================================================="
  echo " STEP 2: "
  echo "  Running 'make' inside buildroot folder."
  echo "================================================="

  cd $BUILDROOT_BUILD_DIR

  if [ "$1" -eq 1 ]; then
    # Original defconfig with just the initial ramfs
    echo ""
    echo "****Defconfig: Ajit_defconfig****"
    echo ""
    make BR2_EXTERNAL=$CWD/Ajit_buildroot_configs Ajit_defconfig
  elif ! [ "$1" -eq 2]; then
    echo ""
    echo "****Defconfig: Ajit_rootfs_$1_defconfig****"
    echo ""
    make BR2_EXTERNAL=$CWD/Ajit_buildroot_configs Ajit_rootfs_$1_defconfig
    make && \
    cp $BUILDROOT_BUILD_DIR/output/images/rootfs.tar $CWD/Ajit_buildroot_configs/board/overlay/initramfs

    # building initramfs with overlay that has the above rootfs, 
    # kernel, and then combining both to a single binary
    # make clean
    echo ""
    echo "****Defconfig: Ajit_rootfs_$1_defconfig****"
    echo ""
    make BR2_EXTERNAL=$CWD/Ajit_buildroot_configs Ajit_initramfs_$1_defconfig
  fi

  make
}

function ajit_dt() {
  echo "================================================="
  echo " STEP 3: "
  echo "  Compiling the device tree."
  echo "================================================="
  cd $DEVICE_TREE_BUILD_DIR
  echo "Checking if Device tree compiler (dtc) is installed ..."
  command -v dtc
  if [ $? -eq 0 ]
  then
    echo "dtc is installed."
    ./compile_device_tree.sh
  else
    echo "ERROR!!: Device tree compiler (dtc) is not installed."
    echo "Please install dtc, preferably version 1.4.0"
    echo "For now, using the existing pre-compiled file Ajit_device_tree.s for generating bootloader image"
  fi
}

function ajit_bl() {
  echo "================================================="
  echo " STEP 4: "
  echo "  Compiling bootloader code."
  echo "================================================="
  cd $BOOTLOADER_BUILD_DIR
  ./compileBootloader.py AjitBootloader.c $DEVICE_TREE_BUILD_DIR/Ajit_device_tree.s

  echo "================================================="
  echo " STEP 5: "
  echo "  Combining the bootloader executable and the kernel image "
  echo "  into a single memory-map"
  echo "================================================="

  if [[ ! -d $BUILD_DIR/Generated_memory_map ]]
  then
    mkdir $BUILD_DIR/Generated_memory_map
  fi
  cp $BOOTLOADER_BUILD_DIR/output/AjitBootloader.elf $BUILD_DIR/Generated_memory_map/
  cp $BOOTLOADER_BUILD_DIR/output/AjitBootloader_*.txt $BUILD_DIR/Generated_memory_map/
  cp $BUILDROOT_BUILD_DIR/output/images/vmlinux $BUILD_DIR/Generated_memory_map/


  cd $BUILD_DIR/Generated_memory_map/
  vmlinuxToMemmap.py AjitBootloader.elf vmlinux

  cd $CWD
}

echo "================================================="
echo " "
echo " C-model build start here "
echo " "
echo "================================================="
copy_things
linux_build $1
DEVICE_TREE_BUILD_DIR=$BUILD_C_DIR/Ajit_device_tree
BOOTLOADER_BUILD_DIR=$BOOTLOADER_C_BUILD_DIR
{
  BUILD_DIR=$BUILD_C_DIR
  ajit_dt
  ajit_bl
}
echo "================================================="
echo " "
echo " C-model build finish here "
echo " "
echo "================================================="
echo ""
echo ""
echo ""
echo ""
echo ""
echo "================================================="
echo " "
echo " FPGA build begin here "
echo " "
echo "================================================="
DEVICE_TREE_BUILD_DIR=$BUILD_FPGA_DIR/Ajit_device_tree
BOOTLOADER_BUILD_DIR=$BOOTLOADER_FPGA_BUILD_DIR
{
  BUILD_DIR=$BUILD_FPGA_DIR
  cd $DEVICE_TREE_BUILD_DIR && ./fpga_script.sh
  ajit_dt
  ajit_bl
}

echo "================================================="
echo " "
echo "  If there were no errors, "
echo "    1. The memory maps will be created in "
echo "        build/**/Generated_memory_map/Output/mem_map.txt"
echo "    2. The FPGA bin will be created in "
echo "        build/fpga/linux_boot/flash_contents/boottrap_u64.bin"
echo " "
echo "================================================="
