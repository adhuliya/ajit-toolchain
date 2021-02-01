#!/bin/bash
cd test_bed
./build.sh
cd -
cd tb
scons
cd -
