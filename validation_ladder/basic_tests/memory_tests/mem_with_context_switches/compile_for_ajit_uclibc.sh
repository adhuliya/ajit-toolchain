MAIN=mem_with_context_switch
AAR=$AJIT_HOME/tools/ajit_access_routines
PT=$AJIT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D NITERS=1024 -D NSIZE=9192 -D HAS_FLOAT -D NO_GLIBC "
SRCS=" -c main.c -c mem.c -C $AAR/src -s init.s -s $AAR/asm/trap_handlers.s -C $PT/src "
INCLUDES=" -I ./ -I $AAR/include -I $PT/include "
compileToSparcUclibc.py -o 2  -V vmap.txt $SRCS $INCLUDES -N ${MAIN} -L LinkerScript.lnk $DEFS
