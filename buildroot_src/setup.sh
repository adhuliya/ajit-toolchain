#!/usr/bin/env bash

# source this bash script


# important env variables
export SRC=$AJIT_HOME/buildroot_src;
export BUILD_DIR=$AJIT_HOME/build;
export BUILDROOT_DIR_NAME=buildroot-2014.08;
export RELATIVE_BIN_DIR_PATH=build/$BUILDROOT_DIR_NAME/output/host/usr/bin;
export ABS_BIN_DIR_PATH="$AJIT_HOME/$RELATIVE_BIN_DIR_PATH";
export BUILD_OUTFILE=$AJIT_HOME/build/output.log;
#export BUILDROOT_SOURCE_TAR=$SRC/${BUILDROOT_DIR_NAME}-offline.tgz;
export DEVELOPMENT=development;


mkdir -p $BUILD_DIR; # create the build dir

# STEP 0: Some basic tests and init the log file
source $SRC/checks.sh;
echo -e "\n\nSTART: `date`\n\n" |& tee -a $BUILD_OUTFILE;


# STEP 1: Start the build.
$SRC/start_build.sh;


# STPE 2: set the path
source $SRC/pathsetup.sh


# # STEP 3: add $DEVELOPMENT work.
# echo -e "\n\nAdding new assembler instructions. `date`\n" |& tee -a $BUILD_OUTFILE;
# sleep 3;
# cp -r $SRC/$DEVELOPMENT $BUILD_DIR/$DEVELOPMENT;
# export AJITTOPHOME=$BUILD_DIR;
# $SRC/update-all-ajit-code-and-run-tests.sh |& tee -a $BUILD_OUTFILE;




