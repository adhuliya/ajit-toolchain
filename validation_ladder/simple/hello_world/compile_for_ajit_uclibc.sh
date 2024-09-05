MAIN=hello_world
AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
INCLUDES="-I ../ -I ../include/ -I $AAR/include -I $PT/include "
SRCS=" -C ./ -C $AAR/src -C $PT/src -s ./init.s -s ./trap_handlers.s"
DEFINES=" -D CLK_FREQUENCY=80000000 "

#Step 1: Generate the Linker Script
makeLinkerScript.py -t 0x0 -d 0x10000 -o customLinkerScript.lnk

#Step 2: Compile the application using uclibc
compileToSparcUclibc.py -o 3 -U -N ${MAIN} $INCLUDES $SRCS $DEFINES -L customLinkerScript.lnk

