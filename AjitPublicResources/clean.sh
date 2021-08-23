#!/bin/bash
CCWD=$(pwd)

if [[ -z $AHIR_RELEASE ]]; then
  echo "ERROR: Please set the env variable \$AHIR_RELEASE";
  exit 1;
fi

rm build.log;

echo "Cleaning: AJIT_POJECT_HOME/tools";
cd ./tools;
scons -c;
cd -;

echo "Cleaning: AJIT_PROJECT_HOME/processor/TestEnvironments";
cd ./processor/TestEnvironments;
scons -c;
cd -;

echo "Cleaning: AJIT_PROJECT_HOME/processor/C_reference_model";
cd ./processor/C_reference_model;
scons -c;
cd -;

echo "Cleaning: AJIT_PROJECT_HOME/processor/64bit/C_multi_core_multi_thread";
cd ./processor/64bit/C_multi_core_multi_thread;
scons -c;
cd -;

echo "Cleaning: AJIT_PROJECT_HOME/tools/ajit_debug_monitor_mt";
cd ./tools/ajit_debug_monitor_mt;
scons -c;
cd -;

echo "Cleaning: AJIT_PROJECT_HOME/tools/ajit_debug_monitor";
cd ./tools/ajit_debug_monitor;
scons -c;
cd -;

# remove the dblite files if any
find -name .sconsign.dblite | xargs rm;


