compileToSparc.py -o 2 -I /usr/include -s init.s -c utils.c -c dhry_1.c -c dhry_2.c -E dhry.elf -V dhry.vars -H dhry.hex -M dhry.mmap -O dhry.objdump -D AJIT -D DHRYOPT -L LinkerScript.lnk
sparc-elf-readelf  --hex-dump=1 --hex-dump=2 --hex-dump=3  --hex-dump=.bss dhry.elf | grep 0x > dhry.hex 
generateMemoryMap_Byte dhry.hex > dhry.mmap
