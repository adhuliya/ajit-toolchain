MAIN=coremark
AAR=$AJIT_ACCESS_ROUTINES_MT
INCLUDES="-I ../ -I ../include/ -I ../env/ -I $AAR/include"
SRCS="-C ../env/ -C ../src/ -C $AAR/src -s ./init.s -s ../trap_handlers.s -s $AAR/asm/mutexes.s "
DEFS="-D NO_GLIBC -D PERFORMANCE_RUN=1 -D ITERATIONS=2000 -D CORE_DEBUG=0 -D COMPILER_REQUIRES_SORT_RETURN=1"

#Step 1: Generate the Linker Script
makeLinkerScript.py -t 0x40040000 -d 0x40050000 -o customLinkerScript.lnk

#Step 2: Compile the application using uclibc
compileToSparcUclibc.py -o 2 -U -N ${MAIN} $INCLUDES $SRCS -L customLinkerScript.lnk $DEFS -F 'fgcse-sm' -F 'funroll-loops'  -F 'finline-functions'

