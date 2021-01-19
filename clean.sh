#!/usr/bin/env bash

rm -Rf Dockerfile;
rm -Rf build/;

cd $AJIT_CMODEL_DIR;
./clean.sh;

cd $AJIT_TOOLS_DIR;
./clean.sh;

