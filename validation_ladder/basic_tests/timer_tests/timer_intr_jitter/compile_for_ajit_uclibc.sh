if [ $# -ne 3 ];
    then echo "specify memory locations of text, data sections and vmap file"
	echo "eg: ./compile_for_ajit_uclibc.sh 0x40000000 0x40040000 VMAPHIGH.txt"
	echo "or ./compile_for_ajit_uclibc.sh 0x0 0x40000000 VMAPLOW.txt"
    exit 1
fi
MAIN=timer_jitter
AAR="$AJIT_ACCESS_ROUTINES"
PT="$AJIT_MINIMAL_PRINTF_TIMER"
TEXTBASE=$1
DATABASE=$2
VMAP=$3
#1 Linker script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2 Compile the application
compileToSparcUclibc.py -N ${MAIN} -U -V $VMAP -g -I ./ \
-s init.s -s trap_handlers.s \
-C $AAR/src -C $PT/src -I $PT/include -I $AJIT_UCLIBC_HEADERS_DIR \
-I $AJIT_LIBGCC_INSTALL_DIR/include \
-I $AAR/include -I /usr/include/x86_64-linux-gnu/gnu/ \
-c main.c -L customLinkerScript.lnk -D AJIT -D HAS_FLOAT -D TIMERSAMPLES=1000 \
-D TIMERCOUNT=100000 -D NO_GLIBC
if [ $1 != "0x0" ]
then
echo "Creating the flash Image"
#3 Convert application memory map to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 timer_jitter.mmap.remapped timer_jitter_copy_asm.s $TEXTBASE 0x50000
#4.a Bootstrap Linker Script
makeLinkerScript.py -t 0x0 -d 0x100000000 -o bootstrapLinkerScript.lnk
#Step 4.b: Compile the application with boostrap wrapper
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s \
-s timer_jitter_copy_asm.s -N bootstrap  -L bootstrapLinkerScript.lnk
#Step 5: Generate bin file to be loaded in FPGA's flash memory
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin
else
echo "No file needed for flash image when instructions are at 0x0"
fi

