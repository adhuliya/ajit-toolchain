makeLinkerScript.py -t 0x40000000 -d 0x40040000 -o customLinkerScript.lnk
# application name
MAIN=hello_world
# support infrastructure.
#   for enabling serial device etc.
AAR=$AJIT_ACCESS_ROUTINES_MT
MUTEXES=$AAR/asm/mutexes.s
#   timer.
PT=$AJIT_MINIMAL_PRINTF_TIMER
#   trap handlers
TRAP_HANDLERS=$AAR/asm/trap_handlers.s
# compile sources.
SRCS=" -c ../main.c -s ../init.s -s $MUTEXES -s $TRAP_HANDLERS -C $AAR/src -C $PT/src"
# compile includes.
INCLUDES="-I ../ -I $AAR/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include "
# compile the application.
compileToSparcUclibc.py -g -V VMAP.TXT -U $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk 

