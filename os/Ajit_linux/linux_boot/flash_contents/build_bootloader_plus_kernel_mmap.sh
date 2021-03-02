#!/bin/bash
cat ../bootloader/AjitBootloader_memmap.txt  > boot_loader_plus_kernel.mmap
cat ../kernel_mmap/kernel_mem_map.txt >> boot_loader_plus_kernel.mmap
