#!/bin/bash
#if [ -z $1 ]; then
#echo -e "\n\nUsage: $0 <name of test file>\n\n"
#exit 0
#fi
#
#echo -e "\n\n"

LIB_DIRECTORY=$AJIT_PROJECT_HOME/cross-compiler/release/lib
INCLUDE_DIRECTORY=$AJIT_PROJECT_HOME/cross_compiler/release/include

echo Compiling test program 
#sparc-elf-gcc -S -Wall -std=c99 -msoft-float -m32 -mcpu=v8 -ffreestanding -nostdlib  -O1 $1 -o test.s
#sparc-elf-gcc -O0 -S -Wall -std=c99 -msoft-float -m32 -mcpu=v8 -ffreestanding -nostdlib -I$OS_DIRECTORY  $1 -o test.s
#sparc-elf-gcc -O0 -S -Wall -m32 -mcpu=v8 -ffreestanding -nostdlib  $1 -o test.s

echo Assembling test program
sparc-elf-as test.s -o test.o	
sparc-elf-as sparc_stdio.s -o sparc_stdio.o

echo Linking with sparc_stdio
sparc-elf-ld -e main -T LinkerScript.lnk -o test.elf test.o sparc_stdio.o -lgcc -L$LIB_DIRECTORY 

echo Generating hexdump file  "hexdump.txt"
sparc-elf-objdump -d  test.elf > objdump.txt && #for viewing execution
sparc-elf-readelf --hex-dump=.text --hex-dump=.rodata --hex-dump=.data test.elf > hexdump1.txt &&
grep "0x" hexdump1.txt > hexdump.txt #read by simulator

./generateMemoryMap_Byte hexdump.txt > tmp.txt

rm -f variables.txt
sparc-elf-readelf  --symbols test.elf >> variables.txt # variables.txt is a text file for viewing at what addresses variables are stored 

#cleanup
#rm -f hexdump1.txt
rm -f test.o
#rm -f test.s
#rm -f test.elf

echo -e "\n"
exit $?
