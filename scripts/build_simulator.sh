#!/usr/bin/env bash

cd $AJIT_AHIR_DIR;
source ./ahir_bashrc;

if [[ -z $AHIR_RELEASE ]]; then
  echo "ERROR: Please set the env variable \$AHIR_RELEASE";
  echo "Find the file 'ahir_bashrc' and source it from its dir.";
  exit 1;
fi

if [[ -z $AJIT_CMODEL_DIR ]]; then
  echo "ERROR: Please set the env variable \$AJIT_CMODEL_DIR";
  echo "Find the file 'ajit_env' and source it from its dir.";
  exit 1;
fi

cd $AJIT_HOME/processor/TestEnvironments
scons

cd $AJIT_HOME/ajit_debug_monitor
scons

cd $AJIT_CMODEL_DIR;
./build.sh;

