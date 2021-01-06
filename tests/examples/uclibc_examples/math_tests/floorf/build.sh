#!/bin/sh
#GLIBC=/home/codeman/.itsoflife/local/packages-live/sparc-glibc-2.21_second/install
GLIBC=/home/codeman/.itsoflife/local/packages-live/sparc-glibc-2-21/install

# STEP 1: setup page tables.
genVmapAsm vmap.txt setup_page_tables.s

# STEP 2: compile to generate elf file.
./compileToSparc_local.py -g -I $GLIBC/include -I /usr/include -I ./ -s init.s -s setup_page_tables.s -s $AJIT_TOOLS_RELEASE/tools/ajit_access_routines/asm/trap_handlers.s -I $AJIT_TOOLS_RELEASE/tools/ajit_access_routines/include -C $AJIT_TOOLS_RELEASE/tools/ajit_access_routines/src -C $AJIT_TOOLS_RELEASE/tools/minimal_printf_timer/src -I $AJIT_TOOLS_RELEASE/tools/minimal_printf_timer/include -c main.c -E test_pow.elf -V test_pow.vars -H test_pow.hex -M test_pow.mmap -O test_pow.objdump  -L LinkerScript.lnk  -D AJIT 

# STEP 3: Read elf to generate mmap file.
echo "\nAD: NOW READING ELF...\n"

# generate the mmap file for deployment on the processor
sparc-linux-readelf  --hex-dump=.text --hex-dump=.data --hex-dump=.rodata --hex-dump=.tdata1  --hex-dump=.tdata  --hex-dump=.bss ${MAIN}.elf | grep 0x > ${MAIN}.hex 
generateMemoryMap_Byte test_pow.hex > test_pow.mmap
remapMemmap vmap.txt test_pow.mmap test_pow.mmap.remapped

