TEXTBASE=0x40000000
DATABASE=0x40040000
VMAP="VMAP.TXT"
MAIN=generic_sw_trap_test
AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
SRCS=" -c ../main.c -s ../init.s -s $AAR/asm/clear_stack_pointers.s -s $AAR/asm/trap_handlers_for_rtos.s -s $AAR/asm/generic_sw_trap_mt.s -s $AAR/asm/generic_isr_mt.s -C $AAR/src -C $PT/src"
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ../ -I $AAR/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include"
DEFS="-D NITERS=1 -D NSIZE=64  -D AJIT -D USE_VMAP"
# linker script for application
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
# compile the application.
compileToSparcUclibc.py -g -U -V $VMAP $SRCS $INCLUDES -N ${MAIN} -o 3 -L customLinkerScript.lnk $DEFS

