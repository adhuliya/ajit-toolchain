# for llvm and clang:
export PATH=$PATH:/home/titto/Cron/AHIR/llvm/bin
export PATH=$PATH:/home/titto/Cron/AHIR/llvm-gcc/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/titto/Cron/AHIR/llvm/lib
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/titto/Cron/AHIR/llvm-gcc/bin
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/titto/Cron/AHIR/ahir/release/pipeHandler/lib/

# for ANTLR:
export ANTLR_PATH=/home/titto/Cron/AHIR/ahir/antlr2/x86_64/

# for AHIR:

# location of ahir release
export AHIR_RELEASE=/home/titto/Cron/AHIR/ahir/release

# path
export PATH=$AHIR_RELEASE/bin:$PATH

# ld-library-paths
export LD_LIBRARY_PATH=$AHIR_RELEASE/lib:$LD_LIBRARY_PATH
