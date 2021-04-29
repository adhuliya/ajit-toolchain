MAIN=mem_with_context_switch
AAR=$AJIT_ACCESS_ROUTINES
PT=$AJIT_MINIMAL_PRINTF_TIMER
DEFS=" -D AJIT -D NITERS=1024 -D NSIZE=9192 -D HAS_FLOAT -D NO_GLIBC"
SRCS=" -c main.c -c mem.c -C $AAR/src -s init.s -s $AAR/asm/trap_handlers.s -C $PT/src "
INCLUDES=" -I ./ -I $AAR/include -I $PT/include "
#Step 1: Generate the Linker Script
makeLinkerScript.py -t 0x40000000 -d 0x40040000 -o customLinkerScript.lnk
#Step 2: Compile the application
compileToSparcUclibc.py -o 2 -V vmap.txt $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS
#3 convert application's mmap to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 mem_with_context_switch.mmap.remapped mem_with_context_switch_copy_asm.s 0x40000000 0x50000
#4.a -> linker script for bootstrap
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#4.b -> compile boostrap to get the mmap
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s mem_with_context_switch_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk
#5 -> generate bin file from mmap of bootstrap
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin

