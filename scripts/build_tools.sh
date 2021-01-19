#!/usr/bin/env bash

# must run this script from its absolute position

AHIR_DIR="$AJIT_HOME/ahir_release";
TOOLS_DIR="$AJIT_HOME/tools";

cd $AHIR_DIR;
source ./ahir_bashrc;

cd $TOOLS_DIR;
./build.sh;


