MAIN=memcpy_no_conflicts
AAR=$AJIT_ACCESS_ROUTINES
PT=$AJIT_MINIMAL_PRINTF_TIMER
SRCS=" -c main.c -c test.c -C $AAR/src -s init.s -s trap_handlers.s -C $PT/src "
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ./ -I $AAR/include -I $PT/include"
DEFS=" -DNITERS=256 -D HAS_FLOAT -D AJIT"
#Step 1: Generate the Linker Script
makeLinkerScript.py -t 0x40000000 -d 0x40008000 -o customLinkerScript.lnk
#Step 2: Compile the application 
compileToSparcUclibc.py -o 2 -U -V vmap.txt $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS
#Step 3: convert application's mmap to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 memcpy_no_conflicts.mmap memcpy_no_conflicts_copy_asm.s 0x40000000 0x10000
#Step 4.a: linker script for bootstrapping
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#Step 4.b: Compile the application with boostrap wrapper
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s memcpy_no_conflicts_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk
#Step 5: Generate bin file to be loaded in FPGA's flash memory
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin

