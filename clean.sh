#!/usr/bin/env bash

rm -Rf Dockerfile;
rm -Rf build/;
rm -Rf docker_build.log;
rm -Rf build.log;

if [[ -z $AJIT_CMODEL_DIR ]]; then
  echo "ERROR: Please set the env variable \$AJIT_CMODEL_DIR";
  exit 1;
fi

if [[ -z $AJIT_TOOLS_DIR]]; then
  echo "ERROR: Please set the env variable \$AJIT_TOOLS_DIR";
  exit 1;
fi

cd $AJIT_CMODEL_DIR;
./clean.sh;

cd $AJIT_TOOLS_DIR;
./clean.sh;
