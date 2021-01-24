# There is no data section in the bootstrap_u64 image.
makeLinkerScript.py -t 0x0 -d 0x40000000 -o customLinkerScript.lnk
# compile
compileToSparc.py -o 2 -I /usr/include -I ./  -s ./bootstrap_u64.s -s ./boot_loader_plus_kernel.s   -E bootstrap_u64.elf -V bootstrap_u64.vars -H bootstrap_u64.hex -M bootstrap_u64.mmap -O bootstrap_u64.objdump  -L customLinkerScript.lnk  
# generate bin


