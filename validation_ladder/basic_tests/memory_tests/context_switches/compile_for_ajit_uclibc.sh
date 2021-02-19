MAIN=context_switches
AAR=$AJIT_HOME/tools/ajit_access_routines
PT=$AJIT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D NITERS=100000 -D CLK_FREQUENCY=100 -D HAS_FLOAT  "
SRCS=" -s init.s -c main.c -C $AAR/src -s $AAR/asm/trap_handlers.s -C $PT/src "
INCLUDES=" -I /usr/include -I ./ -I $AAR/include -I $PT/include "
compileToSparcUclibc.py -o 2 -U  -V vmap.txt $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk $DEFS
