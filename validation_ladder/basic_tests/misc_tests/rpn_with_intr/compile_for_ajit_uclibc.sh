if [ $# -ne 3 ];
    then echo "specify memory locations of text, data sections and vmap file"
	echo "eg: ./compile_for_ajit_uclibc.sh 0x40000000 0x40040000 VMAPHIGH.txt"
	echo "or ./compile_for_ajit_uclibc.sh 0x0 0x40040000 VMAPLOW.txt"
    exit 1
fi
TEXTBASE=$1
DATABASE=$2
VMAP=$3
MAIN=rpn
AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
SRCS=" -c main.c -c delay.c -c stack.c -s init.s -s trap_handlers.s -C $AAR/src -C $PT/src"
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ./ -I $AAR/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include"
DEFS="-D NITERS=1 -D NSIZE=64  -D AJIT"
# linker script for application
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
# compile the application.
compileToSparcUclibc.py -g -U -V $VMAP $SRCS $INCLUDES -N ${MAIN} -o 3 -L customLinkerScript.lnk $DEFS
if [ $1 != "0x0" ]
then
echo "Creating the flash Image"
# convert application memory map to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 rpn.mmap rpn_copy_asm.s $TEXTBASE 0x10000
# linker script for bootstrap
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
# compile boostrap
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s rpn_copy_asm.s -N bootstrap  -L bootstrapLinkerScript.lnk
# generate bin file for FLASH
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin
else
echo "No file needed for flash image when instructions are at 0x0"
fi

