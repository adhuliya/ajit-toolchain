#!/bin/bash
export AJIT_PROJECT_HOME=$(pwd)
ROOTDIR=$(pwd)

#executable paths
export PATH=$ROOTDIR/tools/scripts:$PATH
export PATH=$ROOTDIR/tools/traceCompareServer/bin:$PATH
export PATH=$ROOTDIR/tools/genVmapAsm/bin:$PATH
export PATH=$ROOTDIR/tools/generateInitVal/bin:$PATH
export PATH=$ROOTDIR/tools/vm/bin:$PATH
export PATH=$ROOTDIR/tools/flash_image/bin/:$PATH

#AHIR-related
export LD_LIBRARY_PATH=$AHIR_RELEASE/functionLibrary/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$AHIR_RELEASE/lib:$LD_LIBRARY_PATH

export PATH=$ROOTDIR/tools/misc/bin:$PATH
export PATH=$ROOTDIR/tools/scripts:$PATH
export PATH=$ROOTDIR/tools/linker:$PATH

export PYTHONPATH=$ROOTDIR/tools/pyelftools-0.25:$PYTHONPATH
export PYTHONPATH=$ROOTDIR/tools/scripts:$PYTHONPATH

# $pwd/tools/cross-compiler/buildroot_cross_compiler/usr/bin/sparc-linux-readelf
# $pwd/tools/cross-compiler/buildroot_cross_compiler/usr/bin/sparc-linux-as

# not yet defined.
export AJIT_AA_VALIDATION_EXECUTABLE_LOCATION=UNDEFINED
