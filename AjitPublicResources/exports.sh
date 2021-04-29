#!/bin/bash
CWD=$(pwd)
export AJIT_PROJECT_HOME=$(pwd)
export AJIT_PROCESSOR_ROOT=$(pwd)/processor/

export AJIT_C_REF_MODEL=$(pwd)/processor/64bit/C_multi_core_multi_thread
export AJIT_DEFAULT_VHDL_SIMULATOR=ghdl


#executable paths
export PATH=$AJIT_C_REF_MODEL/testbench/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/traceCompareServer/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/genVmapAsm/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/generateInitVal/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/vm/bin:$PATH

#AHIR-related
export LD_LIBRARY_PATH=$AHIR_RELEASE/functionLibrary/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AHIR_RELEASE/lib:$LD_LIBRARY_PATH

export PATH=$AJIT_PROJECT_HOME/tools/misc/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/scripts:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/linker:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/scripts/performance_analysis_setup:$PATH
export AJIT_AA_VALIDATION_EXECUTABLE_LOCATION=$AJIT_PROJECT_HOME/processor/Aa_v3/Testbenches/bin

export PYTHONPATH=$AJIT_PROJECT_HOME/tools/pyelftools-0.25:$PYTHONPATH
export PYTHONPATH=$AJIT_PROJECT_HOME/tools/scripts:$PYTHONPATH
