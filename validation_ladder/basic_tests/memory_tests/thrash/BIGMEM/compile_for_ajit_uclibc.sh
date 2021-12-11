AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
TEXTBASE=0x40000000
DATABASE=0x41000000
VMAP=VMAP.TXT
CLKFREQ=100000000
#1 generate linker script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2 compile the application
compileToSparcUclibc.py -U -V $VMAP -N thrash\
			-s ../init.s -s $AAR/asm/trap_handlers.s \
			-L customLinkerScript.lnk \
			-I $AAR/include -I $PT/include \
			-c ../main.c -c ../test.c -C $AAR/src -C $PT/src -D NSWEEPS=16 -D CLK_FREQUENCY=$CLKFREQ\
			-D SWEEP_SIZE=1024
