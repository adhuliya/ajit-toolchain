# Commands to assemble and disassemble the assembly code

python main.py
sparc-buildroot-linux-uclibc-as -Av8 -a -s main.s -o main.o > main.as.s
sparc-buildroot-linux-uclibc-objdump -d main.o > main.dis.s
sparc-buildroot-linux-uclibc-gdb -batch -x script.gdb main.o > main.gdbdis.s
python opcode.py
sed '1d' main.dis.s.tmp > tmpfile; mv tmpfile main.dis.s.tmp
diff3 main.dis.s.tmp main.as.s.tmp main.gdbdis.s.tmp

