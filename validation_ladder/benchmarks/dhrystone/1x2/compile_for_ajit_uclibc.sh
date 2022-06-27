makeLinkerScript.py -t 0x40000000 -d 0x40010000 -o customLinkerScript.lnk
# application name
MAIN=dhrystone_wrap
# support infrastructure.
#   for enabling serial device etc.
AAR=$AJIT_ACCESS_ROUTINES_MT
MUTEXES=$AAR/asm/mutexes.s
#   timer.
PT=$AJIT_MINIMAL_PRINTF_TIMER
#   trap handlers
TRAP_HANDLERS=$AAR/asm/trap_handlers.s
# compile sources.
SRCS="-c main.c -s init.s -s $MUTEXES -s $TRAP_HANDLERS -C $AAR/src -C $PT/src"
# compile includes.
INCLUDES="-I ../ -I $AAR/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include "
# compile the application.
compileToSparcUclibc.py -o 2  -U $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk 

