
/home/gauri/ajit-toolchain//development/amv-ajit-code/tests/obj/vaddd.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	25 3c 02 31 	sethi  %hi(0xf008c400), %l2
   4:	a4 14 a2 f8 	or  %l2, 0x2f8, %l2	! f008c6f8 <end+0xf008c6cc>
   8:	27 3c 02 31 	sethi  %hi(0xf008c400), %l3
   c:	a6 14 e2 f8 	or  %l3, 0x2f8, %l3	! f008c6f8 <end+0xf008c6cc>
  10:	29 3c 00 34 	sethi  %hi(0xf000d000), %l4
  14:	a8 15 22 fa 	or  %l4, 0x2fa, %l4	! f000d2fa <end+0xf000d2ce>
  18:	2b 3c 00 34 	sethi  %hi(0xf000d000), %l5
  1c:	aa 15 62 fa 	or  %l5, 0x2fa, %l5	! f000d2fa <end+0xf000d2ce>
  20:	84 04 80 d4 	vaddd8  %l2, %l4, %g2
  24:	88 04 81 54 	vaddd16  %l2, %l4, %g4
  28:	8c 04 82 54 	vaddd32  %l2, %l4, %g6

0000002c <end>:
  2c:	91 d0 20 00 	ta  0
