genVmapAsm vmap.txt setup_page_tables.s
compileToSparc.py -I /usr/include -I ./ -o 2 -s init.s -s setup_page_tables.s  -s $AJIT_TOOLS_RELEASE/ajit_access_routines/asm/trap_handlers.s -I $AJIT_TOOLS_RELEASE/ajit_access_routines/include -C $AJIT_TOOLS_RELEASE/ajit_access_routines/src -C $AJIT_TOOLS_RELEASE/minimal_printf_timer/src -I $AJIT_TOOLS_RELEASE/minimal_printf_timer/include -c main.c -c mem.c -c scale.c -c circshift.c -c correlate.c -E mem_bw.elf -V mem_bw.vars -H mem_bw.hex -M mem_bw.mmap -O mem_bw.objdump  -L LinkerScript.lnk -D NITERS=4 -D NSIZE=8
sparc-linux-readelf  --hex-dump=1 --hex-dump=2 --hex-dump=3  --hex-dump=.bss mem_bw.elf | grep 0x > mem_bw.hex 
generateMemoryMap_Byte mem_bw.hex > mem_bw.mmap
remapMemmap vmap.txt mem_bw.mmap mem_bw.mmap.remapped
