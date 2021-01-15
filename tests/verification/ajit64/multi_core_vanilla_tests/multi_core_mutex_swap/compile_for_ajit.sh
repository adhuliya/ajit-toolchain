genVmapAsm vmap.txt setup_page_tables.s
compileToSparc.py -o 0 -s init.s -s setup_page_tables.s  -s $AJIT_PROJECT_HOME/tools/ajit_access_routines/asm/trap_handlers.s -I $AJIT_PROJECT_HOME/tools/ajit_access_routines/include -C $AJIT_PROJECT_HOME/tools/ajit_access_routines/src -C $AJIT_PROJECT_HOME/tools/minimal_printf_timer/src -I $AJIT_PROJECT_HOME/tools/minimal_printf_timer/include -c main.c  -E mem_bw.elf -V mem_bw.vars -H mem_bw.hex -M mem_bw.mmap -O mem_bw.objdump  -L LinkerScript.lnk 
#echo "sparc-linux-readelf  --hex-dump=1 --hex-dump=2 --hex-dump=3  --hex-dump=.bss mem_bw.elf | grep 0x > mem_bw.hex"
#sparc-linux-readelf  --hex-dump=1 --hex-dump=2 --hex-dump=3  --hex-dump=.bss mem_bw.elf | grep 0x > mem_bw.hex 
generateMemoryMap_Byte mem_bw.hex > mem_bw.mmap
remapMemmap vmap.txt mem_bw.mmap mem_bw.mmap.remapped
