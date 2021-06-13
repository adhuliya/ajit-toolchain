if [ $# -ne 3 ];
    then echo "specify memory locations of text, data sections and vmap file; in that order"
    exit 1
fi
TEXTBASE=$1
DATABASE=$2
VMAP=$3
MAIN=mem_with_context_switch
AAR=$AJIT_ACCESS_ROUTINES
PT=$AJIT_MINIMAL_PRINTF_TIMER
DEFS=" -D AJIT -D NITERS=1024 -D NSIZE=9192 -D HAS_FLOAT -D NO_GLIBC"
SRCS=" -c main.c -c mem.c -C $AAR/src -s init.s -s $AAR/asm/trap_handlers.s -C $PT/src "
INCLUDES=" -I ./ -I $AAR/include -I $PT/include "
#Step 1: Generate the Linker Script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#Step 2: Compile the application
compileToSparcUclibc.py -o 2 -V $VMAP $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS
if [ $1 != "0x0" ]
then
echo "Creating the flash Image" 
#3 convert application's mmap to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 mem_with_context_switch.mmap.remapped mem_with_context_switch_copy_asm.s $TEXTBASE 0x50000
#4.a -> linker script for bootstrap
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#4.b -> compile boostrap to get the mmap
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s mem_with_context_switch_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk
#5 -> generate bin file from mmap of bootstrap
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin
else
echo "No file needed for flash image when instructions are at 0x0"
fi
