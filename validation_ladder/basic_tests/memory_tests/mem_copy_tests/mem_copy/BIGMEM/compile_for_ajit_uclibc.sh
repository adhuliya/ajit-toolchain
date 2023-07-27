MAIN=memcopy_test
AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
TEXTBASE=0x40000000
DATABASE=0x41000000
VMAP=VMAP.TXT
SRCS=" -c ../main.c -c ../test.c -C $AAR/src -s ../init.s -s $AAR/asm/trap_handlers.s -C $PT/src "
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ./ -I $AAR/include -I $PT/include"
DEFS="-D CHUNK=1024 -D NITERS=256 -D HAS_FLOAT -D AJIT"
#
#Step 1: Generate the Linker Script
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
#Step 2: Compile the application
compileToSparcUclibc.py -o 3 -g -U -V $VMAP $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS
