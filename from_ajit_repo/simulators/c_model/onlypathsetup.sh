#!/usr/bin/env bash
export AJIT_C_REF_MODEL=$(pwd)/code
SIM_DIR="$(pwd)";
#AHIR related
cd ahir_release;
AHIR_DIR="$(pwd)";
source ahir_bashrc;
cd $SIM_DIR/code;

export LD_LIBRARY_PATH=$SIM_DIR/code/debugger/doval/antlr3Cruntime/build/lib:$LD_LIBRARY_PATH
export PATH=$PATH:$SIM_DIR/code/debugger/doval/include
export PATH=$PATH:$SIM_DIR/code/debugger/doval/antlr3runtime/build/include

