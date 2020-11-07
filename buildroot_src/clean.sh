#!/usr/bin/env bash
# cleans the parent directory

BUILDROOT_DIR_NAME=$AJIT_HOME/build/buildroot-2014.08;
DEVELOPMENT=$AJIT_HOME/build/development;
BUILD_OUTPUT=$AJIT_HOME/build/output.log;

rm -Rf $BUILDROOT_DIR_NAME;
rm -Rf $DEVELOPMENT;
rm $BUILD_OUTPUT;


