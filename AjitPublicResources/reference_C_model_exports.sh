#!/bin/bash
export AJIT_C_REF_MODEL=$(pwd)/processor/C_reference_model

#library paths for processor components:
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/cache/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/common/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/cpu/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/cpu_interface/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/memory/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/mmu/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/devices/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/debugger/hwServer/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/debugger/doval/antlr3Cruntime/build/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/debugger/doval/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/debugger/gpb/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/debugger/spi_common/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AJIT_C_REF_MODEL/monitorLogger/lib:$LD_LIBRARY_PATH

#executable paths
export PATH=$AJIT_C_REF_MODEL/testbench/bin:$PATH


