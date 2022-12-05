TEXTBASE=0x0
DATABASE=0x40000
VMAP="VMAP.TXT"
MAIN=timer_intr_jitter
AAR=$AJIT_ACCESS_ROUTINES_MT
APT=$AAR
PT=$AJIT_MINIMAL_PRINTF_TIMER
SRCS=" -c ../main.c -s ../init.s -s $APT/asm/clear_stack_pointers.s -s $APT/asm/trap_handlers_for_rtos.s -s $APT/asm/generic_isr_single_stack_mt.s -s $APT/asm/generic_sys_calls.s  -s $APT/asm/generic_sw_trap_mt.s -C $APT/src -C $PT/src"
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ../ -I $APT/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include"
# for HW run, use the following:
#DEFS="-D TIMERCOUNT=100000 -D TIMERSAMPLES=1000 -D AJIT -D HAS_FLOAT -D USE_VMAP"
# for C model, use the following:
DEFS="-D TIMERCOUNT=100 -D TIMERSAMPLES=10 -D AJIT -D HAS_FLOAT -D USE_VMAP -D DEBUG_MODE"
# linker script for application
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
# compile the application.
compileToSparcUclibc.py -g -U -V $VMAP $SRCS $INCLUDES -N ${MAIN} -o 3 -L customLinkerScript.lnk $DEFS

