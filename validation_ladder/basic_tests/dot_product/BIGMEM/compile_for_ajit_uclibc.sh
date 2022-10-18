TEXTBASE=0x40000000
DATABASE=0x40040000
MAIN=dot_product
AAR=$AJIT_HOME/AjitPublicResources/tools/ajit_access_routines_mt
PT=$AJIT_HOME/AjitPublicResources/tools/minimal_printf_timer
DEFS=" -D AJIT -D VECTORSIZE=1024 -D NITERATIONS=1024 -D HAS_FLOAT  -D CLK_FREQUENCY=80000000"
SRCS=" -C ../src/ -C $AAR/src -C $PT/src -s $AAR/asm/trap_handlers.s -s ../src/init.s "
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ../src/ -I ../ -I $AAR/include -I $PT/include"
# -I /usr/include " see if really needed
OPTS=" -F fschedule-insns -F fschedule-insns2 -F frename-registers "
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
compileToSparcUclibc.py -o 3 -U $SRCS $INCLUDES -N ${MAIN} $OPTS -L customLinkerScript.lnk $DEFS
