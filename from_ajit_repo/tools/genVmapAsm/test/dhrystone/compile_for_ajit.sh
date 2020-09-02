../../bin/genVmapAsm vmap.txt setup_page_tables.s
compileToSparc.py -o 3 -s init.s -s setup_page_tables.s -c utils.c -c unified.c  -E dhry.elf -V dhry.vars -H dhry.hex -M dhry.mmap -O dhry.objdump -D AJIT -D DHRYOPT -L LinkerScript.lnk -I /usr/include 
sparc-linux-readelf  --hex-dump=1 --hex-dump=2 --hex-dump=3  --hex-dump=.bss dhry.elf | grep 0x > dhry.hex 
generateMemoryMap_Byte dhry.hex > dhry.mmap
../../bin/remapMemmap vmap.txt dhry.mmap dhry.mmap.remapped
