#!/usr/bin/env bash
# cleans the parent directory

BUILDROOT_DIR_NAME=buildroot-2014.08
DEVELOPMENT=development
BUILD_OUTPUT=output.log;

rm -Rf $BUILDROOT_DIR_NAME;
rm -Rf $DEVELOPMENT;
rm $BUILD_OUTPUT;
