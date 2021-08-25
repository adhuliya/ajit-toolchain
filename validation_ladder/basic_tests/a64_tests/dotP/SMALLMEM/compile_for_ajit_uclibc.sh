if [ $# -ne 3 ];
    then echo "specify memory locations of text, data sections and vmap file"
	echo "eg: ./compile_for_ajit_uclibc.sh 0x0 0x10000 VMAP.txt"
    exit 1
fi
TEXTBASE=$1
DATABASE=$2
VMAP=$3
MAIN=dotP
AAR=$AJIT_ACCESS_ROUTINES_MT
PT=$AJIT_MINIMAL_PRINTF_TIMER
SRCS=" -c ../src/main.c  -s ../src/init.s -s ../src/dotP.s -s $AAR/asm/trap_handlers.s -C $AAR/src -C $PT/src"
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I ../src -I $AAR/include -I $PT/include -I $AJIT_UCLIBC_HEADERS -I $AJIT_LIBGCC_INSTALL_DIR/include"
DEFS="-D NITERS=1 -D NSIZE=64  -D AJIT -D HAS_FLOAT"
# linker script for application
makeLinkerScript.py -t $TEXTBASE -d $DATABASE -o customLinkerScript.lnk
# compile the application.
echo $INCLUDES
echo $DEFS
compileToSparcUclibc.py -g -U -V $VMAP $SRCS ${INCLUDES} -N ${MAIN} -o 3 -L customLinkerScript.lnk $DEFS
