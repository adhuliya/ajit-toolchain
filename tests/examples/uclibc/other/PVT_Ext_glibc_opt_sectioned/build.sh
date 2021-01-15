#!/bin/sh
GLIBC=$AJIT_TOOLS_RELEASE/tools/glibc/2.21
MAIN=sat_pos
BUIDROOT=/home/anshuman/buildroot-2014.08 

genVmapAsm vmap.txt setup_page_tables.s

./compileToSparc.py -o 3 -I $BUIDROOT/output/host/usr/sparc-buidroot-linux-uclibc/sysroot/usr/include -I /usr/include -I ./ -s init.s -s setup_page_tables.s  -s $AJIT_TOOLS_RELEASE/tools/ajit_access_routines/asm/trap_handlers.s -I $AJIT_TOOLS_RELEASE/tools/ajit_access_routines/include -C $AJIT_TOOLS_RELEASE/tools/ajit_access_routines/src -C $AJIT_TOOLS_RELEASE/tools/minimal_printf_timer/src -I $AJIT_TOOLS_RELEASE/tools/minimal_printf_timer/include -c PVT.c -c ExtractData.c -c fpop.c -c math_func.c  -E ${MAIN}.elf -V ${MAIN}.vars -H ${MAIN}.hex -M ${MAIN}.mmap -O ${MAIN}.objdump  -L LinkerScript.lnk  -D AJIT -D HAS_FLOAT -G 2.21 -D NO_MEMCPY
  
echo "\nREADELF\n"
sparc-linux-readelf  --hex-dump=.text --hex-dump=.data --hex-dump=.rodata --hex-dump=.tdata1 --hex-dump=.tdata  --hex-dump=.bss --hex-dump=.tbss --hex-dump=.got --hex-dump=.dtors --hex-dump=.eh_frame --hex-dump=__libc_freeres_fn --hex-dump=__libc_thread_fre --hex-dump=__libc_subfreeres --hex-dump=.gnu.linkonce.b._ --hex-dump=.__libc_freeres_pt ${MAIN}.elf | grep 0x > ${MAIN}.hex 

generateMemoryMap_Byte ${MAIN}.hex > ${MAIN}.mmap

remapMemmap vmap.txt ${MAIN}.mmap ${MAIN}.mmap.remapped
