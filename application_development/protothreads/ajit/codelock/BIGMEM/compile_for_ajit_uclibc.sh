MAIN=codelock
AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
TEXTBASE=0x40000000
DATABASE=0x40040000
VMAP=VMAP.TXT
SRCDIR=../../../
SRCS=" -c $SRCDIR/example-codelock.c -c $SRCDIR/ajit_timer.c  -C $AAR/src -s ../init.s -s $AAR/asm/trap_handlers.s -C $PT/src "
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ../../ -I $AAR/include -I $PT/include"
# Keep clock frequency at 256 for C model run.
# DEFS="-D AJIT_CLOCK_FREQUENCY=256 -D HAS_FLOAT -D AJIT"
DEFS="-D AJIT_CLOCK_FREQUENCY=100000000 -D HAS_FLOAT -D AJIT"
#
#Step 1: Generate the Linker Script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#Step 2: Compile the application
compileToSparcUclibc.py -o 3 -g -U -V $VMAP $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS
