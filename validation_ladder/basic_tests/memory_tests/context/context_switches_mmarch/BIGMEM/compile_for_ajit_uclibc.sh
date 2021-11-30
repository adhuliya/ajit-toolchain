MAIN=context_switches
TEXTBASE=0x40000000
DATABASE=0x40020000
VMAP=VMAP.TXT
AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
DEFS=" -D AJIT -D NITERS=16 -D CLK_FREQUENCY=100 -D HAS_FLOAT  "
SRCS=" -s ../init.s -c ../main.c -c ../march.c  -C $AAR/src -s $AAR/asm/trap_handlers.s -C $PT/src "
INCLUDES="-I ../ -I $AAR/include -I $PT/include -I /usr/include/x86_64-linux-gnu/gnu"
#1 LinkerScript
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#2 Compile the application
compileToSparcUclibc.py -o 2 -U -V $VMAP $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS
