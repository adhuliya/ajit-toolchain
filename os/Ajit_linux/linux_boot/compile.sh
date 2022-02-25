export PATH=$AJIT_TOOLS_DIR/flash_image/bin/:$PATH

if ! [ -d "boot_loader_plus_kernel_mmap" ]; then
  mkdir -p boot_loader_plus_kernel_mmap
fi

#copy the mmap
cp ../Generated_memory_map.f0004000/Output.f0004000/boot_loader_plus_kernel.mmap ./boot_loader_plus_kernel_mmap/ 

# Memory map file for OS + bootloader.
# generate mmap.remapped file for application.
cd flash_contents/
# generate assembly code for mmap..
mmapToAssyU64 ../boot_loader_plus_kernel_mmap/boot_loader_plus_kernel.mmap boot_loader_plus_kernel.s  0xf0000000 0x00600000
# produces mmap file for bootstrap.
./compile_for_ajit.sh
mmapToBin  24  bootstrap_u64.mmap bootstrap_u64.bin 
