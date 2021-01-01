#!/usr/bin/env bash
# Taken from ajit-toolchain's marshal branch
# must run this script from its absolute position
source exports.sh
SIM_DIR="$(pwd)";

cd ahir_release;
AHIR_DIR="$(pwd)";
source ahir_bashrc;

cd $SIM_DIR/code;

export LD_LIBRARY_PATH=$SIM_DIR/code/debugger/doval/antlr3Cruntime/build/lib:$LD_LIBRARY_PATH
export PATH=$PATH:$SIM_DIR/code/debugger/doval/include
export PATH=$PATH:$SIM_DIR/code/debugger/doval/antlr3runtime/build/include

echo "Building antlr3Cruntime";     sleep 1;
cd $SIM_DIR/code/debugger/doval/antlr3Cruntime; scons;
echo "Building doval";              sleep 1;
cd $SIM_DIR/code/debugger/doval;                scons;
echo "Building console";            sleep 1;
cd $SIM_DIR/code/console;                       scons;
echo "Building char_client_server"; sleep 1;
cd $SIM_DIR/code/char_client_server;            scons;
echo "Building code";               sleep 1;
cd $SIM_DIR/code;                               scons;
cd $SIM_DIR;
cd $SIM_DIR/code/testbench/bin;
