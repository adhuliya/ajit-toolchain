
BUILDROOT_BUILD_DIR=$PWD/buildroot-2014.08
LINUX_BUILD_DIR=$PWD/buildroot-2014.08/output/build/linux-custom
BUILDROOT_TAR=$PWD/buildroot-2014.08.tar.gz

# Check for presence of Argumentsand throw an error when there is none or invalid one.
if [ "$#" -ne 1 ] || [ "$1" -lt 0 ] || [ "$1" -gt 3 ]; then
  echo "ERROR: Invalid or missing argument...."
  echo "Usage: $0 <DEFCONFIG>"
  echo ""
  echo "DEFCONFIG values"
  echo "    <0> rootfs-tmpfs with dynamic-lib & static device list"
  echo "    <1> rootfs-tmpfs with satic-lib & static device list"
  echo "    <2> rootfs-tmpfs with static-libs & dynamic device list"
  echo "    <3> legacy initramfs system config;no rootfs-tmpfs present"
  exit 1
fi

#If you're running this script for the first time,
#the destination folder may not exist.
#Let's create it first.

if ! [ -d "$BUILDROOT_BUILD_DIR" ]; then
  tar -xvf $BUILDROOT_TAR
fi

if ! [ -d "$LINUX_BUILD_DIR" ]; then
  echo "================================================="
  echo " STEP 0: "
  echo " Creating folder buildroot-2014.08/output/build/linux-custom"
  echo "================================================="
  mkdir -p $LINUX_BUILD_DIR
fi


echo "================================================="
echo " STEP 1: "
echo "  copying kernel source code (using rync)"
echo "  from: ./Ajit_linux_3.16.1/"
echo "  to  : ./buildroot-2014.08/output/build/linux-custom"
echo "================================================="

rsync -av --exclude .svn --exclude .git --exclude .hg --exclude .bzr --exclude CVS ./Ajit_linux_3.16.1/ ./buildroot-2014.08/output/build/linux-custom


echo " Running make clean inside linux build directory"
cd ./buildroot-2014.08/output/build/linux-custom/
make clean
cd -


echo "================================================="
echo " STEP 2: "
echo "  Running 'make' inside buildroot folder."
echo "================================================="

cd buildroot-2014.08

# make clean

if [ "$1" -eq 3 ]; then
  # Original defconfig with just the initial ramfs
  echo ""
  echo "****Defconfig: Ajit_defconfig****"
  echo ""
  make BR2_EXTERNAL=$PWD/../Ajit_buildroot_configs Ajit_defconfig
elif ! [ "$#" -eq 0]; then
  echo ""
  echo "****Defconfig: Ajit_rootfs_$1_defconfig****"
  echo ""
  make BR2_EXTERNAL=$PWD/../Ajit_buildroot_configs Ajit_rootfs_$1_defconfig
  make && \
  cp ./output/images/rootfs.tar ./../Ajit_buildroot_configs/board/overlay/initramfs

  # building initramfs with overlay that has the above rootfs, 
  # kernel, and then combining both to a single binary
  # make clean
  echo ""
  echo "****Defconfig: Ajit_rootfs_$1_defconfig****"
  echo ""
  make BR2_EXTERNAL=$PWD/../Ajit_buildroot_configs Ajit_initramfs_$1_defconfig
fi

make && \
cd -

echo "================================================="
echo " STEP 3: "
echo "  Compiling the device tree."
echo "================================================="
cd ./Ajit_device_tree/
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
cd -


echo "================================================="
echo " STEP 4: "
echo "  Compiling bootloader code."
echo "================================================="
cd ./Ajit_bootloader/
./compileBootloader.py AjitBootloader.c ../Ajit_device_tree/Ajit_device_tree.s
cd -


echo "================================================="
echo " STEP 5: "
echo "  Combining the bootloader executable and the kernel image "
echo "  into a single memory-map"
echo "================================================="

if [[ ! -d Generated_memory_map ]]
then
  mkdir Generated_memory_map
fi
cp Ajit_bootloader/output/AjitBootloader.elf ./Generated_memory_map/
cp Ajit_bootloader/output/AjitBootloader_*.txt ./Generated_memory_map/
cp buildroot-2014.08/output/images/vmlinux ./Generated_memory_map/


cd ./Generated_memory_map/
vmlinuxToMemmap.py AjitBootloader.elf vmlinux 
cd -

echo "================================================="
echo " "
echo "  If there were no errors, the memory map will be created in "
echo "  ./Generated_memory_map/Output/mem_map.txt"
echo " "
echo "================================================="


