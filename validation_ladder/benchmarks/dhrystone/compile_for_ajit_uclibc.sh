MAIN=dhrystone
AAR=$AJIT_HOME/tools/ajit_access_routines
PT=$AJIT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D DHRYOPT -D HAS_FLOAT -D NO_GLIBC "
SRCS=" -c unified.c -C $AAR/src -s init.s -C $PT/src "
INCLUDES=" -I ./ -I $AAR/include -I $PT/include "
compileToSparcUclibc.py -o 3  $SRCS $INCLUDES -N ${MAIN} -L LinkerScript.lnk $DEFS
