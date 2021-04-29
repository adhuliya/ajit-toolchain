#!/bin/bash
if [ $# -lt 4 ]
  then
    echo "Supply start of text region, start of data region for linker, VMAP file, clock frequency"
    echo "example   0x0 0x8000 VMAPLOWMEM.TXT 80000000"
    echo "   Note: VMAP must be consistent with text and data regions"
    exit 1
fi
makeLinkerScript.py -t $1 -d $2 -o customLinkerScript.lnk
VA_DATA_SECTION=$2
MAIN=all_kinds_mem
AAR=$AJIT_HOME/tools/ajit_access_routines
PT=$AJIT_HOME/tools/minimal_printf_timer
SRCS=" -c main.c -C $AAR/src -s init.s -s trap_handlers.s -C $PT/src "
INCLUDES=" -I ./ -I $AAR/include -I $PT/include "
DEFS=" -D NO_GLIBC -D VA_DATA_SECTION_START=$2 -D CLK_FREQUENCY=$4 " 
compileToSparcUclibc.py -o 2  -V $3 $SRCS $INCLUDES -N ${MAIN} -L customLinkerScript.lnk -D HAS_FLOAT -D AJIT   $DEFS
