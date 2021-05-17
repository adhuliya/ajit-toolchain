#!/bin/bash
CWD=$(pwd)
# build test-environments
echo "build processor/TestEnvironments"
cd processor/TestEnvironments
scons
cd -
# the C reference model testbench.
source reference_C_model_exports.sh
cd processor/C_reference_model/
echo "build processor/C_reference_model"
scons
cd -
# the 64-bit C reference model testbench.
source reference_64bit_C_model_exports.sh
cd processor/64bit/C_multi_core_multi_thread/
echo "build processor/64bit/C_multi_core_multi_thread/"
scons
cd -
# ajit_debug_monitor_mt.
echo "build tools/ajit_debug_monitor_mt"
cd tools/ajit_debug_monitor_mt
scons
