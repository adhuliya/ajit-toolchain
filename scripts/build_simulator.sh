#!/usr/bin/env bash

# must run this script from its absolute position

SIM_DIR="$AJIT_HOME/simulators/c_model";
AHIR_DIR="$AJIT_HOME/ahir_release";

cd $AHIR_DIR;
source ./ahir_bashrc;

cd $SIM_DIR/code;
export AJIT_C_REF_MODEL="$(pwd)";

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


