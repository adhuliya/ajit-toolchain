MAIN=dhrystone
AAR=$AJIT_PROJECT_HOME/tools/ajit_access_routines_mt
PT=$AJIT_PROJECT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D DHRYOPT -D HAS_FLOAT -D NO_GLIBC -D NDHRYSTONE_ITERS=2"
SRCS=" -c ../unified.c -C $AAR/src -s ../init.s -C $PT/src "
INCLUDES=" -I ../ -I $AAR/include -I $PT/include "
#1 Compile the application
compileToSparcUclibc.py -o 3  $SRCS $INCLUDES -N ${MAIN} -L LinkerScript.lnk $DEFS

