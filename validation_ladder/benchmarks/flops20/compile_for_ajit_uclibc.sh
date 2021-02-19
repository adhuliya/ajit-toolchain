MAIN=flops20
AAR=$AJIT_HOME/tools/ajit_access_routines
PT=$AJIT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D ROPT -D HAS_FLOAT "
SRCS=" -C src/ -C $AAR/src -C $PT/src -s $AAR/asm/trap_handlers.s -s init.s "
INCLUDES=" -I src/ -I ./ -I $AAR/include -I $PT/include -I /usr/include "
OPTS=" -F fschedule-insns -F fschedule-insns2 -F frename-registers "
compileToSparcUclibc.py -o 3  $SRCS $INCLUDES -N ${MAIN} $OPTS -L LinkerScript.lnk $DEFS -U
