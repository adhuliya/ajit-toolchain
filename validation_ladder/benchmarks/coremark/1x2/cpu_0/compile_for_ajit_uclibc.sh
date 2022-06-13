MAIN=coremark
AAR=$AJIT_ACCESS_ROUTINES_MT
INCLUDES="-I ../ -I ../../ajit_test/include/ -I ../../ajit_test/env/ -I $AAR/include"
SRCS="-C ../../ajit_test/env/ -C ../../ajit_test/src/ -C $AAR/src -s ../../ajit_test/init.s -s ../../ajit_test/trap_handlers.s"
DEFS="-D NO_GLIBC -D PERFORMANCE_RUN=1 -D ITERATIONS=2000 -D CORE_DEBUG=0 -D COMPILER_REQUIRES_SORT_RETURN=1"

#Step 1: Generate the Linker Script
makeLinkerScript.py -t 0x40020000 -d 0x40030000 -o customLinkerScript.lnk

#Step 2: Compile the application using uclibc
compileToSparcUclibc.py -o 3 -U -N ${MAIN} $INCLUDES $SRCS -L customLinkerScript.lnk $DEFS -F 'fgcse-sm' 

