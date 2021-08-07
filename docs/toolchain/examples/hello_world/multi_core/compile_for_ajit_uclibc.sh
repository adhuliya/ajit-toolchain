# make linker script: text at 0x0, data at 0x8000
makeLinkerScript.py -t 0x0 -d 0x40000 -o customLinkerScript.lnk
# application name
MAIN=hello_world
# support infrastructure.
#   for enabling serial device etc.
AAR_MT=$AJIT_PROJECT_HOME/tools/ajit_access_routines_mt
AAR=$AJIT_ACCESS_ROUTINES
MUTEXES=$AAR_MT/asm/mutexes.s
#   timer.
PT=$AJIT_MINIMAL_PRINTF_TIMER
#   trap handlers
TRAP_HANDLERS=$AAR/asm/trap_handlers.s
# compile sources.
SRCS=" -c bugCheck/main.c -s init.s -s $MUTEXES -s $TRAP_HANDLERS -C $AAR/src -C $PT/src"
# compile includes.
INCLUDES="-I ./ -I $AAR/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include "
# compile the application.
compileToSparcUclibc.py -g -V bugCheck/VMAP.TXT -U $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk 

