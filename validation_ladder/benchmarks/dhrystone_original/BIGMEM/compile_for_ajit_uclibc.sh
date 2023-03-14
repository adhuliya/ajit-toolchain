MAIN=dhrystone
AAR=$AJIT_PROJECT_HOME/tools/ajit_access_routines_mt
PT=$AJIT_PROJECT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D DHRYOPT -D HAS_FLOAT -D NO_GLIBC -D NDHRYSTONE_ITERS=1000000"
SRCS=" -c ../dhry_1.c -c ../dhry_2.c -c ../utils.c -c $AAR/src/ajit_access_routines.c  -s ../init.s -C $PT/src "
INCLUDES=" -I ../ -I $AAR/include -I $PT/include "
makeLinkerScript.py -t 0x40000000 -d 0x40010000 -o customLinkerScript.lnk
compileToSparcUclibc.py   -o 2  $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS   -F 'funroll-loops'
