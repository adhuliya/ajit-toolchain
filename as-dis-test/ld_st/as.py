import os
### cmd = 'sparc-buildroot-linux-uclibc-as -Av8 main.s -o main.o'
cmd = '/lindata/My-work/Professional/iitb/build/buildroot-2014.08/output/host/usr/bin/sparc-buildroot-linux-uclibc-as -aghls=main.txt -Av8 main.s -o main.o'
os.system(cmd)
### cmd_dis = 'sparc-buildroot-linux-uclibc-objdump -d main.o > main.dis.s'
cmd_dis = '/lindata/My-work/Professional/iitb/build/buildroot-2014.08/output/host/usr/bin/sparc-buildroot-linux-uclibc-objdump -d -z main.o > main.dis.s'
os.system(cmd_dis)


