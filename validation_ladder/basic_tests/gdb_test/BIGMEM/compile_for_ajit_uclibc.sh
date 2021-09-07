TEXTBASE=0x40000000
DATABASE=0x40040000
MAIN=gdb_test
AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
SRCS=" -c ../main.c -s ../init.s -s $AAR/asm/trap_handlers.s -C $AAR/src -C $PT/src"
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ../ -I $AAR/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include"
# linker script for application
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
# compile the application.
compileToSparcUclibc.py -g -U $SRCS $INCLUDES -N ${MAIN} -g -L customLinkerScript.lnk $DEFS

