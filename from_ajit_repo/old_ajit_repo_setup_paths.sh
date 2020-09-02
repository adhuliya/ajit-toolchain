#!/bin/bash
export AJIT_PROJECT_HOME=$(pwd)
export AJIT_C_LEGACY_MODEL=$(pwd)/processor/C_legacy
#export AJIT_C_REF_MODEL=$(pwd)/processor/C_reference_model
export AJIT_C_REF_MODEL=$(pwd)/processor/64bit/C
export AJIT_GLIBC_INSTALL_DIR=$AJIT_PROJECT_HOME/tools/glibc/

# cross-compiler
#  (either sparc-elf or sparc-linux)
#
#export AJIT_PROJECT_CROSS_COMPILER=sparc-elf
export AJIT_PROJECT_CROSS_COMPILER=sparc-linux

# default simulator.
export AJIT_DEFAULT_VHDL_SIMULATOR=ghdl
#export AJIT_DEFAULT_VHDL_SIMULATOR=modelsim

# default board
#export fpga_board=kc705
export fpga_board=vc709
#export fpga_board=ml605


#executable paths
export PATH=$AJIT_C_REF_MODEL/testbench/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/processor/Aa_v3/Testbenches/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/traceCompareServer/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/genVmapAsm/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/generateInitVal/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/vm/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/processor/Aa_v3/TestSetups/cpu/tb/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/processor/Aa_v3/TestSetups/core/tb/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/processor/Aa_v3/TestSetups/cpu/ghdl/cpu_test_bed_test_bench:$PATH

#AHIR-related
export LD_LIBRARY_PATH=$AHIR_RELEASE/functionLibrary/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AHIR_RELEASE/lib:$LD_LIBRARY_PATH

#------------------------------------------------------------------------------
# cross compiler:
# 
# Sparc v8 cross compiler release for x86_64 ubuntu obtained using ubuntu.
# For a different host architecture/OS, change the path to point to your own
# buildroot installation.
export PATH=$AJIT_PROJECT_HOME/tools/cross-compiler/buildroot_cross_compiler/usr/bin:$PATH
export LD_LIBRARY_PATH=$AJIT_PROJECT_HOME/tools/cross-compiler/buildroot_cross_compiler/usr/lib:$LD_LIBRARY_PATH

## deprecated cross compiler:
# (recommended to use the buildroot cross compiler )
#    (at least this one works..)
export PATH=$PATH:$AJIT_PROJECT_HOME/tools/cross-compiler/release/bin
export PATH=$PATH:$AJIT_PROJECT_HOME/tools/cross-compiler/release/lib


export PATH=$AJIT_PROJECT_HOME/tools/misc/bin:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/scripts:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/linker:$PATH
export PATH=$AJIT_PROJECT_HOME/tools/scripts/performance_analysis_setup:$PATH

export AJIT_AA_VALIDATION_EXECUTABLE_LOCATION=$AJIT_PROJECT_HOME/processor/Aa_v3/Testbenches/bin

#export PATH=$AJIT_PROJECT_HOME/tools/buildroot/buildroot-2014.08/output/host/usr/bin/:$PATH
export PYTHONPATH=$AJIT_PROJECT_HOME/tools/pyelftools-0.25:$PYTHONPATH
export PYTHONPATH=$AJIT_PROJECT_HOME/tools/scripts:$PYTHONPATH



