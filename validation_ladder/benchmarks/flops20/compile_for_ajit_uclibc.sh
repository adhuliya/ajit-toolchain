MAIN=flops20
AAR=$AJIT_HOME/tools/ajit_access_routines
PT=$AJIT_HOME/tools/minimal_printf_timer
DEFS=" -D AJIT -D ROPT -D HAS_FLOAT "
SRCS=" -C src/ -C $AAR/src -C $PT/src -s $AAR/asm/trap_handlers.s -s init.s "
INCLUDES="-I /usr/include/x86_64-linux-gnu/gnu -I src/ -I ./ -I $AAR/include -I $PT/include"
# -I /usr/include " see if really needed
OPTS=" -F fschedule-insns -F fschedule-insns2 -F frename-registers "
#Step 1: Compile the application. [ NOTE: Linker is not generated through makeLinkerScript.py ]
compileToSparcUclibc.py -o 3 -U $SRCS $INCLUDES -N ${MAIN} $OPTS -L LinkerScript.lnk $DEFS
#Step 2: convert application's mmap to assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 flops20.mmap flops20_copy_asm.s 0x40000000 0x40000
#Step 2: linker script for bootstrapping
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk
#Step 3: Compile the application with boostrap wrapper
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s flops20_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk
#Step 4: Generate bin file to be loaded in FPGA's flash memory
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin