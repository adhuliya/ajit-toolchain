if [ $# -ne 3 ];
    then echo "specify memory locations of text, data sections and vmap file"
	echo "eg: ./compile_for_ajit_uclibc.sh 0x40000000 0x40040000 VMAPHIGH.txt"
	echo "or ./compile_for_ajit_uclibc.sh 0x0 0x40000000 VMAPLOW.txt"

    exit 1
fi 
MAIN=dcache_loadstore_miss
AAR=$AJIT_ACCESS_ROUTINES
PT=$AJIT_MINIMAL_PRINTF_TIMER
TEXTBASE=$1
DATABASE=$2
VMAP=$3
SRCS=" -c main.c -c test.c -C $AAR/src -s init.s -s trap_handlers.s -C $PT/src "
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ./ -I $AAR/include -I $PT/include"
DEFS=" -D HAS_FLOAT -D AJIT -D LENGTH=1024"
#
#Step 1: Generate the Linker Script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#Step 2: Compile the application 
compileToSparcUclibc.py -o 3 -U -V $VMAP $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS
if [ $1 != "0x0" ]
then
echo "Creating the flash Image"
#Step 3: convert application's mmap to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 dcache_loadstore_miss.mmap dcache_loadstore_miss_copy_asm.s $TEXTBASE 0x50000
#Step 4.a: linker script for bootstrapping
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#Step 4.b: Compile the application with boostrap wrapper
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s dcache_loadstore_miss_copy_asm.s -N bootstrap  -L bootstrapLinkerScript.lnk
#Step 5: Generate bin file to be loaded in FPGA's flash memory
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin 
else
echo "No file needed for flash image when instructions are at 0x0"
fi
