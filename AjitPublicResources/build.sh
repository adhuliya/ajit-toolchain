#!/bin/bash
CCWD=$(pwd)
# build test-environments
echo "build processor/TestEnvironments"
cd processor/TestEnvironments
scons
cd -
# the 64-bit C reference model testbench.
cd processor/64bit/C_multi_core_multi_thread/
echo "build processor/64bit/C_multi_core_multi_thread/"
scons
cd -
# ajit_debug_monitor_mt.
echo "build tools/ajit_debug_monitor_mt"
cd tools/ajit_debug_monitor_mt
scons
cd $CCWD
