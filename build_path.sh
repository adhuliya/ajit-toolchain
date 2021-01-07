CURRDIR=$(pwd)
export PATH=$CURRDIR/buildroot-2014.08/output/host/usr/bin:$PATH

export AJIT_UCLIBC_INSTALL_DIR=$CURRDIR/buildroot-2014.08/output/build/uclibc-0.9.33.2
export UCLIBC_HEADERS=$CURRDIR/buildroot-2014.08/output/host/usr/sparc-buildroot-linux-uclibc/sysroot/usr/include
export AJIT_LIBGCC_INSTALL_DIR=$CURRDIR/buildroot-2014.08/output/build/host-gcc-final-4.7.4/build/gcc

export AJIT_TOOLS_RELEASE=$CURRDIR/from_ajit_repo/tools/
export AJIT_PROJECT_HOME=$CURRDIR/from_ajit_repo/tools/
export AJIT_PROJECT_CROSS_COMPILER=sparc-linux
export LD_LIBRARY_PATH=$AJIT_TOOLS_RELEASE/cross-compiler/lib/:$LD_LIBRARY_PATH
export PATH=$AJIT_TOOLS_RELEASE/scripts/:$PATH
export PATH=$AJIT_TOOLS_RELEASE/cross-compiler/bin/:$PATH
export PATH=$PATH:$CURRDIR/from_ajit_repo/tools/ajit_access_routines/asm
export PATH=$PATH:$CURRDIR/from_ajit_repo/tools/ajit_access_routines/src
export PATH=$PATH:$CURRDIR/from_ajit_repo/simulators/c_model/code/testbench/bin:$PATH
export AJIT_C_REF_MODEL=$CURRDIR/from_ajit_repo/simulators/c_model/code/
export AJIT_AA_VALIDATION_EXECUTABLE_LOCATION=$CURRDIR
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CURRDIR/from_ajit_repo/simulators/c_model/code/debugger/doval/antlr3Cruntime/build/lib/
~     
