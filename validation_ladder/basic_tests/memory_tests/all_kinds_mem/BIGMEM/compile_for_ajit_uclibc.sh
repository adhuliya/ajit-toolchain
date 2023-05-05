AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
TEXTBASE=0x40000000
DATABASE=0x40040000
VMAP=VMAP.TXT
CLKFREQ=80000000
#1 generate linker script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2 compile the application
compileToSparcUclibc.py -g -V $VMAP -N all_kinds_mem\
			-s ../init.s -s $AAR/asm/trap_handlers.s -s $AAR/asm/generic_sys_calls.s \
			-L customLinkerScript.lnk \
			-I $AAR/include -I $PT/include \
			-c ../main.c -C $AAR/src -C $PT/src -D VA_DATA_SECTION_START=$DATABASE -D CLK_FREQUENCY=$CLKFREQ
#echo "Creating the flash Image"
#3 convert application's mmap to assembly
#$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 all_kinds_mem.mmap.remapped all_kinds_mem_copy_asm.s 0x40000000 0x50000
#4.a -> linker script for bootstrap.. there is no data needed.
#makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#4.b -> compile boostrap to get the mmap
#compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s all_kinds_mem_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk
#5 -> generate bin file from mmap of bootstrap
#$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin
