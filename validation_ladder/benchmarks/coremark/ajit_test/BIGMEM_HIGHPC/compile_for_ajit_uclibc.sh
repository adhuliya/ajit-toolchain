MAIN=coremark
AAR=$AJIT_ACCESS_ROUTINES_MT
INCLUDES="-I ../ -I ../include/ -I ../env/ -I $AAR/include"
SRCS="-C ../env/ -C ../src/ -C $AAR/src -s ../init.s -s ../trap_handlers.s"
DEFS="-D NO_GLIBC -D PERFORMANCE_RUN=1 -D ITERATIONS=5000 -D CORE_DEBUG=0 -D COMPILER_REQUIRES_SORT_RETURN=1 -DUSE_PERF_COUNTERS"

#Step 1: Generate the Linker Script
makeLinkerScript.py -t 0x40000000 -d 0x40020000 -o customLinkerScript.lnk

#Step 2: Compile the application using uclibc

# Gives 208.9 CM
#compileToSparcUclibc.py -o 2 -U -N ${MAIN} $INCLUDES $SRCS -L customLinkerScript.lnk $DEFS -F 'fgcse-sm'  -F 'funroll-loops'  -F 'finline-functions'
compileToSparcUclibc.py -o 2 -U -N ${MAIN} $INCLUDES $SRCS -L customLinkerScript.lnk $DEFS -F 'fgcse-sm'  -F 'funroll-loops'  -F 'finline-functions' 

