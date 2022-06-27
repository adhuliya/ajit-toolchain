CWD=$(pwd)
rm -rf *.mmap *.elf *.vars *.obj* sparc* *.hex customLinke*
cd cpu_0
rm -rf *.mmap *.elf *.vars *.obj* sparc* *.hex customLinke*
cd $CWD
cd cpu_1
rm -rf *.mmap *.elf *.vars *.obj* sparc* *.hex customLinke*
cd $CWD
