if [ $# -ne 3 ];
    then echo "specify memory locations of text, data sections"
	echo "eg: ./compile_for_ajit_uclibc.sh 0x0 0x40040000 VMAPLOW.txt "
    exit 1
fi 
MAIN=context_switches
TEXTBASE=$1
DATABASE=$2
VMAP=$3
AAR=$AJIT_ACCESS_ROUTINES
PT=$AJIT_MINIMAL_PRINTF_TIMER
DEFS=" -D AJIT -D NITERS=100000 -D CLK_FREQUENCY=100 -D HAS_FLOAT  "
SRCS=" -s init.s -c main.c -C $AAR/src -s $AAR/asm/trap_handlers.s -C $PT/src "
INCLUDES="-I ./ -I $AAR/include -I $PT/include -I /usr/include/x86_64-linux-gnu/gnu"
#1 LinkerScript
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2 Compile the application
compileToSparcUclibc.py -o 2 -U -V $VMAP $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS
if [ $1 != "0x0" ]
then
echo "Creating the flash Image"
#3 convert application's mmap to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 context_switches.mmap.remapped context_switches_copy_asm.s $TEXTBASE 0x50000
#4.a -> linker script for bootstrap
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#4.b -> compile boostrap to get the mmap
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s context_switches_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk
#5 -> generate bin file from mmap of bootstrap
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin
else
echo "No file needed for flash image when instructions are at 0x0"
fi