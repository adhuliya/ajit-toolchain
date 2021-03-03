import os

# Commands to assemble and disassemble the assembly code (TODO:gdb needs to be added)

cmd = 'sparc-buildroot-linux-uclibc-as -Av8 main.s -o main.o'
os.system(cmd)
cmd_dis = 'sparc-buildroot-linux-uclibc-objdump -d main.o > main.dis.s'
os.system(cmd_dis)



