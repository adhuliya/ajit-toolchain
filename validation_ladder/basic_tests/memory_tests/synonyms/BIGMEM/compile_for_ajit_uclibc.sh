MAIN=synonyms
AAR=$AJIT_PROJECT_HOME/tools/ajit_access_routines_mt
PT=$AJIT_PROJECT_HOME/tools/minimal_printf_timer
SRCS=" -c ../main.c -C $AAR/src -s ../init.s -s ../trap_handlers.s -C $PT/src "
INCLUDES=" -I ../ -I $AAR/include -I $PT/include "
DEFS=" -D NO_GLIBC " 
makeLinkerScript.py -t 0x40000000 -d 0x40010000 -o customLinkerScript.lnk
compileToSparcUclibc.py -o 2  -V VMAP.TXT $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk -D HAS_FLOAT -D AJIT   $DEFS
