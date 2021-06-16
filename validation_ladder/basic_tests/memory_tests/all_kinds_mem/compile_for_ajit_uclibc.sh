if [ $# -ne 4 ];
    then echo "illegal number of parameters, specify memory locations of text, data sections and vmap file and clk_freq"
        echo "eg: ./compile_for_ajit_uclibc.sh 0x0 0x8000 VMAPLOWMEM.TXT 80000000 "
    exit 1
fi

AAR=$AJIT_ACCESS_ROUTINES
PT=$AJIT_MINIMAL_PRINTF_TIMER
TEXTBASE=$1
DATABASE=$2
VMAP=$3
CLKFREQ=$4
#1 generate linker script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2 compile the application
compileToSparcUclibc.py -g -V $VMAP -N all_kinds_mem\
			-s init.s -s trap_handlers.s \
			-L customLinkerScript.lnk \
			-I $AAR/include -I $PT/include \
			-c main.c -C $AAR/src -C $PT/src -D VA_DATA_SECTION_START=$2 -D CLK_FREQUENCY=$4
if [ $1 != "0x0" ]
then
echo "Creating the flash Image"
#3 convert application's mmap to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 all_kinds_mem.mmap.remapped all_kinds_mem_copy_asm.s $1 0x50000
#4.a -> linker script for bootstrap.. there is no data needed.
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#4.b -> compile boostrap to get the mmap
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s all_kinds_mem_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk
#5 -> generate bin file from mmap of bootstrap
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin
else
echo "No file needed for flash image when instructions are at 0x0"
fi
