if [ $# -ne 3 ];
    then echo "specify memory locations of text, data sections and vmap file"
	echo "eg: ./compile_for_ajit_uclibc.sh 0x40000000 0x40040000 VMAPHIGH.txt"
	echo "or ./compile_for_ajit_uclibc.sh 0x0 0x40000000 VMAPLOW.txt"
    exit 1
fi
AAR=$AJIT_ACCESS_ROUTINES
PT=$AJIT_MINIMAL_PRINTF_TIMER
TEXTBASE=$1
DATABASE=$2
VMAP=$3
#1 generate linker script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2 compile the application
compileToSparcUclibc.py -g -V $VMAP -N time\
	-s init.s -s trap_handlers.s \
	-L customLinkerScript.lnk \
	-I $AAR/include -I $PT/include \
	-c main.c -C $AAR/src -C $PT/src
if [ $1 != "0x0" ]
then
echo "Creating the flash Image"
#3 convert application's mmap to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 time.mmap.remapped time_copy_asm.s $TEXTBASE 0x50000
#4.a -> linker script for bootstrap
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#4.b -> compile boostrap to get the mmap
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s time_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk
#5 -> generate bin file from mmap of bootstrap
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin
else
echo "No file needed for flash image when instructions are at 0x0"
fi
