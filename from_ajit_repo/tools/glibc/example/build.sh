#!/bin/sh
#GLIBC=/home/codeman/.itsoflife/local/packages-live/sparc-glibc-2.21_second/install
GLIBC=$AJIT_TOOLS_RELEASE/tools/glibc/2.21
MAIN=main

# STEP 1: setup page tables.
genVmapAsm vmap.txt setup_page_tables.s

# STEP 2: compile to generate elf file.
./compileToSparc_local.py -g -I $GLIBC/include -I /usr/include -I ./ -s init.s -s setup_page_tables.s -s $AJIT_TOOLS_RELEASE/tools/ajit_access_routines/asm/trap_handlers.s -I $AJIT_TOOLS_RELEASE/tools/ajit_access_routines/include -C $AJIT_TOOLS_RELEASE/tools/ajit_access_routines/src -c main.c -E ${MAIN}.elf -V ${MAIN}.vars -H ${MAIN}.hex -M ${MAIN}.mmap -O ${MAIN}.objdump  -L LinkerScript.lnk  -D AJIT -G 2.21

# STEP 3: Read elf to generate mmap file.
echo "\nAD: NOW READING ELF...\n"

# generate the mmap file for deployment on the processor
sparc-linux-readelf  --hex-dump=.text --hex-dump=.data --hex-dump=.rodata --hex-dump=.tdata1  --hex-dump=.tdata  --hex-dump=.bss ${MAIN}.elf | grep 0x > ${MAIN}.hex 
generateMemoryMap_Byte ${MAIN}.hex > ${MAIN}.mmap
remapMemmap vmap.txt ${MAIN}.mmap ${MAIN}.mmap.remapped

