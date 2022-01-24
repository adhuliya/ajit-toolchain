TEXTBASE=0x40000000
DATABASE=0x40040000
VMAP="VMAP.TXT"
MAIN=hello_world
AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
ASSEMBLY=" -s ../init.s -s $AAR/asm/clear_stack_pointers.s -s $AAR/asm/trap_handlers_for_rtos.s -s $AAR/asm/generic_sw_trap_mt.s -s $AAR/asm/generic_isr_mt.s "
CSRCS=" -c ../main.c -C $AAR/src -C $PT/src"
PROTOTHREADS=" -I $AJIT_HOME/application_development/protothreads/include "
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ../ -I $AAR/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include $PROTOTHREADS "
DEFS=" -D AJIT -D USE_VMAP "
# linker script for application
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
# compile the application.
compileToSparcUclibc.py -g -U -V $VMAP $ASSEMBLY $CSRCS $INCLUDES -N ${MAIN} -o 3 -L customLinkerScript.lnk $DEFS

