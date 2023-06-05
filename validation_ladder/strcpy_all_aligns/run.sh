#!/usr/bin/env bash

_BUILD_DIR="cortos_build";
cp run_cmodel.sh cortos_build/
cd $_BUILD_DIR && ./run_cmodel.sh;

