genVmapAsm vmap.txt setup_page_tables.s
compileToSparc.py -g -s init.s -s setup_page_tables.s  -s $AJIT_PROJECT_HOME/tools/ajit_access_routines/asm/trap_handlers.s -c main.c -E mem_bw.elf -V mem_bw.vars -H mem_bw.hex -M mem_bw.mmap -O mem_bw.objdump  -L LinkerScript.lnk 
#sparc-linux-readelf  --hex-dump=.text --hex-dump=.rodata --hex-dump=.rdata  --hex-dump=.bss mem_bw.elf | grep 0x > mem_bw.hex 
generateMemoryMap_Byte mem_bw.hex > mem_bw.mmap
remapMemmap vmap.txt mem_bw.mmap mem_bw.mmap.remapped
