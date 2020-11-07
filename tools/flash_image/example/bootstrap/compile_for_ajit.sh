# There is no data section in the bootstrap image.
makeLinkerScript.py -t 0x0 -d 0x40000000 -o customLinkerScript.lnk
# compile
compileToSparc.py -o 2 -I /usr/include -I ./  -s ../../asm/bootstrap.s -s ../code/rpn_assy.s   -E bootstrap.elf -V bootstrap.vars -H bootstrap.hex -M bootstrap.mmap -O bootstrap.objdump  -L customLinkerScript.lnk  
echo "\nREADELF\n"
sparc-linux-readelf  --hex-dump=.text  bootstrap.elf | grep 0x > bootstrap.hex 
# this mmap file should be loaded into memory (flash)
generateMemoryMap_Byte bootstrap.hex > bootstrap.mmap
