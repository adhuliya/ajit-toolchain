MAIN=dhrystone
AAR=$AJIT_PROJECT_HOME/tools/ajit_access_routines_mt
PT=$AJIT_PROJECT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D DHRYOPT -D HAS_FLOAT -D NO_GLIBC -D NDHRYSTONE_ITERS=10"
SRCS=" -c dhry_1.c -c dhry_2.c -c utils.c -C $AAR/src -s init.s -C $PT/src "
INCLUDES=" -I ./ -I $AAR/include -I $PT/include "
#1 Compile the application
compileToSparcUclibc.py -o 3  $SRCS $INCLUDES -N ${MAIN} -L LinkerScript.lnk $DEFS
#2 convert the memory map of the application to assembly
#$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 dhrystone.mmap dhrystone_copy_asm.s 0x40000000 0x20000
#4.a -> linker script for bootstrap
#makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#4.b -> compile boostrap to get the mmap
#compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s dhrystone_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk
#5 -> generate bin file from mmap of bootstrap
#$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin
