#  Memory map file for OS + bootloader.
# generate mmap.remapped file for application.
cd flash_contents/
# generate assembly code for mmap..
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 ../boot_loader_plus_kernel_mmap/boot_loader_plus_kernel.mmap boot_loader_plus_kernel.s  0xf0000000 0x00200000
# produces mmap file for bootstrap.
./compile_for_ajit.sh
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 24 bootstrap_u64.mmap bootstrap_u64.bin 
