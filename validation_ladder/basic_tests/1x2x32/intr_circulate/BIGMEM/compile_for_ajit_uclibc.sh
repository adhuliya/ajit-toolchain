makeLinkerScript.py -t 0x40000000 -d 0x40040000 -o customLinkerScript.lnk
# application name
MAIN=intr_circulate
# support infrastructure.
#   for enabling serial device etc.
AAR=$AJIT_ACCESS_ROUTINES_MT
#   timer.
PT=$AJIT_MINIMAL_PRINTF_TIMER
#   trap handlers
# compile sources.
SRCS=" -c ../main.c -c ../rsum.c  -s ../init.s -s ../trap_handlers.s -s $AAR/asm/generic_isr_mt.s -C $AAR/src -C $PT/src"
# compile includes.
INCLUDES="-I ../ -I $AAR/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include "
# compile the application.
compileToSparcUclibc.py -g -V VMAP.TXT -U $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk 

