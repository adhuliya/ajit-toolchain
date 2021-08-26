AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
#1 generate linker script
makeLinkerScript.py -t 0x0 -d 0x8000 -o customLinkerScript.lnk
#2 compile the application
compileToSparcUclibc.py -g -V VMAP.TXT -N all_kinds_mem\
			-s ../init.s -s $AAR/asm/trap_handlers.s \
			-L customLinkerScript.lnk \
			-I $AAR/include -I $PT/include \
			-c ../main.c -C $AAR/src -C $PT/src -D VA_DATA_SECTION_START=0x8000 -D CLK_FREQUENCY=80000000
