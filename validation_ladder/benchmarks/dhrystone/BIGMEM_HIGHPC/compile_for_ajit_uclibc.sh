MAIN=dhrystone
AAR=$AJIT_PROJECT_HOME/tools/ajit_access_routines_mt
PT=$AJIT_PROJECT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D DHRYOPT -D HAS_FLOAT -D NO_GLIBC -D NDHRYSTONE_ITERS=100000"
SRCS=" -c ../unified.c -c $AAR/src/ajit_access_routines.c -s ../init.s -C $PT/src  "
INCLUDES=" -I ./ -I $AAR/include -I $PT/include "
makeLinkerScript.py -t 0x40000000 -d 0x40010000 -o customLinkerScript.lnk
compileToSparcUclibc.py -o 3 $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS

