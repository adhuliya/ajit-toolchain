AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
TEXTBASE=0x40000000
DATABASE=0x40040000
VMAP=VMAP.TXT
CLKFREQ=80000000
#1 generate linker script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2 compile the application
compileToSparcUclibc.py -g -V $VMAP -N hello_world\
			-s ../init.s -s $AAR/asm/trap_handlers.s -s $AAR/asm/generic_sys_calls.s \
			-L customLinkerScript.lnk \
			-I $AAR/include -I $PT/include \
			-F "mflat"\
			-c ../main.c -C $AAR/src -C $PT/src -D VA_DATA_SECTION_START=$DATABASE -D CLK_FREQUENCY=$CLKFREQ
