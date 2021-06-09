#!/bin/bash
CCWD=$(pwd)
# build test-environments
cd processor/TestEnvironments
scons -c 
cd -
# the 64-bit C reference model testbench.
cd processor/64bit/C_multi_core_multi_thread/
scons -c
cd -
# ajit_debug_monitor_mt.
cd tools/ajit_debug_monitor_mt
scons -c
cd $CCWD
