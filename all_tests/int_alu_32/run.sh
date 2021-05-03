python inst_generate.py
sparc-buildroot-linux-uclibc-as -Av8 -a -s integer_alu_64.s -o main.o > main.as.s
sparc-buildroot-linux-uclibc-objdump -d main.o > main.dis.s
sparc-buildroot-linux-uclibc-gdb -batch -x script.gdb main.o > main.gdbdis.s
python opcodes_generate.py > opcodes.asm.s
python extract.py
diff data.asm.s main.as.s.tmp
sed '1d' main.dis.s.tmp > tmpfile; mv tmpfile main.dis.s.tmp
diff3 main.dis.s.tmp main.as.s.tmp main.gdbdis.s.tmp

