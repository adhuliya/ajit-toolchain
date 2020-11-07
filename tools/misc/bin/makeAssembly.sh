#!/bin/bash
if [ -z $1 ]; then
echo -e "\n\nUsage: $0 <name of test file>\n\n"
exit 0
fi

echo Compiling test program 
sparc-elf-gcc -O0 -S -Wall -m32 -mcpu=v8 -ffreestanding -nostdlib -I../include/  $1 -o $1.s
sparc-elf-gcc -O0 -S -Wall -m32 -mcpu=v8 -ffreestanding -nostdlib -I../include/ ../src/sparc_stdio.c -o sparc_stdio.s
