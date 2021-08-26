MAIN=coremark
AAR=$AJIT_ACCESS_ROUTINES_MT
INCLUDES="-I ./ -I include/ -I env/ -I $AAR/include"
SRCS="-C env/ -C src/ -C $AAR/src -s init.s -s trap_handlers.s"
DEFS="-D NO_GLIBC -D PERFORMANCE_RUN=1 -D ITERATIONS=2000 -D CORE_DEBUG=0 -D COMPILER_REQUIRES_SORT_RETURN=1"

#Step 1: Generate the Linker Script
makeLinkerScript.py -t 0x40000000 -d 0x40010000 -o customLinkerScript.lnk

#Step 2: Compile the application using uclibc
compileToSparcUclibc.py -o 3 -U -N ${MAIN} $INCLUDES $SRCS -L customLinkerScript.lnk $DEFS -F 'fgcse-sm' 

#Step 3: Convert the program into assembly
$AJIT_FLASH_IMAGE_DIR/bin/mmapToAssyU64 coremark.mmap coremark_copy_asm.s 0x40000000 0x20000

#Step 4.a: Prepare bootstrap Linker script
makeLinkerScript.py -t 0x0 -d 0x10000000 -o bootstrapLinkerScript.lnk

#Step 4.b: Compile the bootstrap application
compileToSparcUclibc.py -s $AJIT_FLASH_IMAGE_DIR/asm/bootstrap_u64.s -s coremark_copy_asm.s -N bootstrap -L bootstrapLinkerScript.lnk

#Step 5: -> generate bin file from mmap of bootstrap
$AJIT_FLASH_IMAGE_DIR/bin/mmapToBin 20 bootstrap.mmap bootstrap.bin





