#!/usr/bin/env bash

if [[ -z $AJIT_HOME ]]; then
  echo "ERROR: Please set the env variable \$AJIT_HOME";
  echo "Find the file 'ahir_bashrc' and source it from its dir.";
  exit 1;
fi

cd $AJIT_HOME/buildroot_src && ./setup.sh;


