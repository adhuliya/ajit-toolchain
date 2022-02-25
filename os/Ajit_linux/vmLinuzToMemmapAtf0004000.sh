# Script assumes that kernel has been built in buildroot.
CWD=$PWD
BUILDROOT_BUILD_DIR=$CWD/build/common/buildroot-2014.08


function build() {
        DEVICE_TREE_BUILD_DIR=$BUILD_DIR/Ajit_device_tree
        BOOTLOADER_BUILD_DIR=$BUILD_DIR/Ajit_bootloader

        # remove old stuff and make it again.
        rm -rf $BUILD_DIR/Generated_memory_map.f0004000
        mkdir -p $BUILD_DIR/Generated_memory_map.f0004000

        echo "================================================="
        echo " STEP 0: "
        echo "  Compiling bootloader code. starts at 0xf0000000"
        echo "================================================="
        cd $BOOTLOADER_BUILD_DIR
        ./compileBootloader.f0000000.py AjitBootloader.c $BUILD_DIR/Ajit_device_tree/Ajit_device_tree.s
        cd -


        echo "================================================="
        echo " STEP 1: "
        echo "  Combining the bootloader executable and the kernel image "
        echo "  into a single memory-map"
        echo "================================================="
        cp $BOOTLOADER_BUILD_DIR/output.f0000000/AjitBootloader.elf   $BUILD_DIR/Generated_memory_map.f0004000/
        cp $BOOTLOADER_BUILD_DIR/output.f0000000/AjitBootloader_*.txt $BUILD_DIR/Generated_memory_map.f0004000/
        cp $BUILDROOT_BUILD_DIR/output/images/vmlinux $BUILD_DIR/Generated_memory_map.f0004000/

        cd $BUILD_DIR/Generated_memory_map.f0004000/
        vmlinuxToMemmapRevised.py AjitBootloader.elf vmlinux 0xf0004000 -o Output.f0004000 
        cd $CWD
}

{
BUILD_DIR=$CWD/build/c_model
build
}

{
BUILD_DIR=$CWD/build/fpga
build
}

echo "================================================="
echo " "
echo "  If there were no errors, the memory map will be created in "
echo "  build/Generated_memory_map.f0004000/Output/mem_map.txt"
echo " "
echo "================================================="

echo "================================================="
echo " "
echo "  You can refer the log file of build in ./build/biuld.log"
echo " "
echo "================================================="
