#!/bin/sh

MAIN=dhry_1

# STEP 2: compile to generate elf file.
# NOTE: the use of `-U` to enable uclibc
compileToSparcUclibc.py -I $AJIT_UCLIBC_HEADERS_DIR -I ./ -s init.s -c utils.c -c dhry_2.c -c ${MAIN}.c -N ${MAIN} -L LinkerScript.lnk -D AJIT -D DHRYOPT -U

# STEP 3: Read elf to generate mmap file.
echo "\nNOW READING ELF...\n"

# generate the mmap file for deployment on the processor
sparc-linux-readelf `pt_load_sections.py ${MAIN}.elf` ${MAIN}.elf | grep 0x > ${MAIN}.hex 
generateMemoryMap_Byte ${MAIN}.hex > ${MAIN}.mmap

