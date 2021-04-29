MAIN=memcopy_test
AJITPHOME=/home/madhav/AjitProject/Git/AjitRepoV2
AAR=$AJITPHOME/tools/ajit_access_routines
PT=$AJITPHOME/tools/minimal_printf_timer
SRCS=" -c main.c -c test.c -C $AAR/src -s init.s -s trap_handlers.s -C $PT/src "
INCLUDES=" -I /usr/include  -I ./ -I $AAR/include -I $PT/include "
DEFS=" -DNITERS=256  " 
makeLinkerScript.py -t 0x0 - d 0x40040000 -o customLinkerScript.lnk
compileToSparcUclibc.py -o 2 -U  -V VMAP.TXT $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk -D HAS_FLOAT -D AJIT   $DEFS
