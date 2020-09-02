genVmapAsm vmap.txt setup_page_tables.s
makeLinkerScript.py -t 0x40000000 -d 0x80000000 -o customLinkerScript.lnk
compileToSparc.py -o 2 -I /usr/include -I ./  -s init.s -s setup_page_tables.s  -s trap_handlers.s -I $AJIT_PROJECT_HOME/tools/ajit_access_routines/include -C $AJIT_PROJECT_HOME/tools/ajit_access_routines/src -C $AJIT_PROJECT_HOME/tools/minimal_printf_timer/src -I $AJIT_PROJECT_HOME/tools/minimal_printf_timer/include -c main.c -c stack.c -c delay.c -E rpn.elf -V rpn.vars -H rpn.hex -M rpn.mmap -O rpn.objdump  -L customLinkerScript.lnk  -D AJIT
echo "\nREADELF\n"
sparc-linux-readelf  --hex-dump=.text.startup --hex-dump=1 --hex-dump=2 --hex-dump=3  --hex-dump=.bss rpn.elf | grep 0x > rpn.hex 
generateMemoryMap_Byte rpn.hex > rpn.mmap
remapMemmap vmap.txt rpn.mmap rpn.mmap.remapped
