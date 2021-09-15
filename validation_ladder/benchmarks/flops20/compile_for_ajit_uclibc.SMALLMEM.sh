MAIN=flops20
AAR=$AJIT_PROJECT_HOME/tools/ajit_access_routines_mt
PT=$AJIT_PROJECT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D ROPT -D HAS_FLOAT "
SRCS=" -C src/ -C $AAR/src -C $PT/src -s $AAR/asm/trap_handlers.s -s init.s "
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I src/ -I ./ -I $AAR/include -I $PT/include"
# -I /usr/include " see if really needed
OPTS=" -F fschedule-insns -F fschedule-insns2 -F frename-registers "
#Step 1: Compile the application. [ NOTE: Linker is not generated through makeLinkerScript.py ]
compileToSparcUclibc.py -o 3 -U $SRCS $INCLUDES -N ${MAIN} $OPTS -L LinkerScript.SMALLMEM.lnk $DEFS
