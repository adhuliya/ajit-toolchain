#!/bin/sh

# the place where the buildroot is installed
THE_BUILDROOT=/home/gaurip/OPEN_ME_TO_README/buildroot-2014.08

# the header files used for development
UCLIBC_HEADERS=$THE_BUILDROOT/output/host/usr/sparc-buildroot-linux-uclibc/sysroot/usr/include
MAIN=main

# STEP 1: setup page tables.
genVmapAsm vmap.txt setup_page_tables.s

# STEP 2: compile to generate elf file.
# NOTE: the use of `-U` to enable uclibc
./compileToSparc.py -I $UCLIBC_HEADERS -I /usr/include -I ./ -s init.s -s setup_page_tables.s -s trap_handlers.s -s add.s -c ${MAIN}.c -E ${MAIN}.elf -V ${MAIN}.vars -H ${MAIN}.hex -M ${MAIN}.mmap -O ${MAIN}.objdump  -L LinkerScript.lnk  -D AJIT -U

# STEP 3: Read elf to generate mmap file.
echo "\nAD: NOW READING ELF...\n"

# generate the mmap file for deployment on the processor
#sparc-linux-readelf  --hex-dump=.text --hex-dump=.data --hex-dump=.rodata --hex-dump=.tdata1  --hex-dump=.tdata  --hex-dump=.bss ${MAIN}.elf | grep 0x > ${MAIN}.hex 
# NOTE: the use of `./pt_load_sections.py` script to extract loadable modules
sparc-linux-readelf `./pt_load_sections.py ${MAIN}.elf` ${MAIN}.elf | grep 0x > ${MAIN}.hex 
generateMemoryMap_Byte ${MAIN}.hex > ${MAIN}.mmap
remapMemmap vmap.txt ${MAIN}.mmap ${MAIN}.mmap.remapped

