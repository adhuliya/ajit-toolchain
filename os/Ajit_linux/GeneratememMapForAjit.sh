
BUILDROOT_BUILD_DIR=$PWD/buildroot-2014.08
LINUX_BUILD_DIR=$PWD/buildroot-2014.08/output/build/linux-custom
BUILDROOT_TAR=$PWD/buildroot-2014.08.tar.gz

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

# make BR2_EXTERNAL=$PWD/../Ajit_buildroot_configs Ajit_defconfig

# portion that builts a rootfs and copies it for the intiramfs
make clean
make BR2_EXTERNAL=$PWD/../Ajit_buildroot_configs Ajit_rootfs_$1_defconfig
make && \
cp ./output/images/rootfs.tar ./../Ajit_buildroot_configs/board/overlay/initramfs

# building initramfs with the overlay that has the above rootfs, 
# kernel and then combining both to a single binary
# make clean
make BR2_EXTERNAL=$PWD/../Ajit_buildroot_configs Ajit_initramfs_$1_defconfig
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


