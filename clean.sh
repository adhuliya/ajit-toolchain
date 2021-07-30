#!/usr/bin/env bash

# STEP 1: Check the paths.
if [[ -z $AJIT_HOME ]]; then
  echo "ERROR: Please set the env variable \$AJIT_HOME";
  exit 1;
fi

if [[ -z $AJIT_CMODEL_DIR ]]; then
  echo "ERROR: Please set the env variable \$AJIT_CMODEL_DIR";
  exit 1;
fi

if [[ -z $AJIT_TOOLS_DIR ]]; then
  echo "ERROR: Please set the env variable \$AJIT_TOOLS_DIR";
  exit 1;
fi

if [[ -z $AJIT_TESTS_DIR ]]; then
  echo "ERROR: Please set the env variable \$AJIT_TESTS_DIR";
  exit 1;
fi

# STEP 2: Cleanup. May call sub-cleanup scripts.
cd $AJIT_HOME;
rm -Rf Dockerfile;
rm -Rf build/;
rm -Rf docker_build.log;
rm -Rf build.log;

cd $AJIT_PROJECT_HOME;
./clean.sh;

cd $AJIT_TESTS_DIR;
./clean.sh;

