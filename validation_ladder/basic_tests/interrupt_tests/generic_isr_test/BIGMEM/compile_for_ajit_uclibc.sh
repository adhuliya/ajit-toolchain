TEXTBASE=0x40000000
DATABASE=0x40040000
VMAP="VMAP.TXT"
MAIN=generic_isr_test
AAR=$AJIT_ACCESS_ROUTINES_MT
APT=$AAR
PT=$AJIT_MINIMAL_PRINTF_TIMER
SRCS=" -c ../main.c -c ../delay.c -s ../init.s -s $APT/asm/clear_stack_pointers.s -s $APT/asm/trap_handlers_for_rtos.s -s $APT/asm/generic_isr_mt.s -C $APT/src -C $PT/src"
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ../ -I $APT/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include"
DEFS="-D NITERS=1 -D NSIZE=64  -D AJIT -D USE_VMAP"
# linker script for application
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
# compile the application.
compileToSparcUclibc.py -g -U -V $VMAP $SRCS $INCLUDES -N ${MAIN} -o 3 -L customLinkerScript.lnk $DEFS

