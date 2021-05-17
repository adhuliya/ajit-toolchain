#!/usr/bin/env bash

# source this bash script


# important env variables
export BUILDROOT_DIR_NAME=buildroot-2014.08
export RELATIVE_BIN_DIR_PATH=$BUILDROOT_DIR_NAME/output/host/usr/bin;
export ABS_BIN_DIR_PATH="`pwd`/$RELATIVE_BIN_DIR_PATH";
export BUILD_OUTFILE=output.log;
#export BUILDROOT_SOURCE_TAR=src/${BUILDROOT_DIR_NAME}-offline.tgz;
export DEVELOPMENT=development;


# STEP 0: Some basic tests and init the log file
source src/checks.sh;
echo -e "\n\nSTART: `date`\n\n" |& tee -a $BUILD_OUTFILE;


# STEP 1: Start the build.
./src/start_build.sh;


# STPE 2: set the path
source src/pathsetup.sh


# STEP 3: add $DEVELOPMENT work.
echo -e "\n\nAdding new assembler instructions. `date`\n" |& tee -a $BUILD_OUTFILE;
sleep 3;
cp -r src/$DEVELOPMENT $DEVELOPMENT;
export AJITTOPHOME=`pwd`;
./src/update-all-ajit-code-and-run-tests.sh |& tee -a $BUILD_OUTFILE;




