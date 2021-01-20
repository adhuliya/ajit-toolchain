#!/usr/bin/env bash

if [[ -z $AJIT_AHIR_DIR ]]; then
  echo "ERROR: Please set the env variable \$AJIT_AHIR_DIR";
  echo "Find the file 'ajit_env' and source it from its dir.";
  exit 1;
fi

if [[ -z $AJIT_CMODEL_DIR ]]; then
  echo "ERROR: Please set the env variable \$AJIT_CMODEL_DIR";
  echo "Find the file 'ajit_env' and source it from its dir.";
  exit 1;
fi

cd $AJIT_AHIR_DIR;
source ./ahir_bashrc;

cd $AJIT_TOOLS_DIR;
./build.sh;


