# Script assumes that kernel has been built in buildroot.

# remove old stuff and make it again.
rm -rf Generated_memory_map.f0004000
mkdir Generated_memory_map.f0004000

echo "================================================="
echo " STEP 0: "
echo "  Compiling bootloader code. starts at 0xf0000000"
echo "================================================="
cd ./Ajit_bootloader/
./compileBootloader.f0000000.py AjitBootloader.c ../Ajit_device_tree/Ajit_device_tree.s
cd -


echo "================================================="
echo " STEP 1: "
echo "  Combining the bootloader executable and the kernel image "
echo "  into a single memory-map"
echo "================================================="
cp Ajit_bootloader/output.f0000000/AjitBootloader.elf   ./Generated_memory_map.f0004000/
cp Ajit_bootloader/output.f0000000/AjitBootloader_*.txt ./Generated_memory_map.f0004000/
cp buildroot-2014.08/output/images/vmlinux ./Generated_memory_map.f0004000/

cd ./Generated_memory_map.f0004000/
vmlinuxToMemmapRevised.py AjitBootloader.elf vmlinux 0xf0004000 -o Output.f0004000 
cd -


