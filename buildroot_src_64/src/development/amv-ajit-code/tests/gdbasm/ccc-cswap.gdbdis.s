Dump of assembler code for function main:
   0x00000000 <+0>:	9d e3 bf 88	save  %sp, -120, %sp
   0x00000004 <+4>:	c9 78 81 01	cswap  [ %g2 + %g1 ] (8), %g4
   0x00000008 <+8>:	c9 78 af ff	cswap  [ %g2 + 0xfff ], %g4
   0x0000000c <+12>:	c9 f8 81 41	cswapa  [ %g2 + %g1 ] (10), %g4
   0x00000010 <+16>:	c9 f8 af ff	cswapa  [ %g2 + 0xfff ], %g4
   0x00000014 <+20>:	c9 7f bf f8	cswap  [ %fp + -8 ], %g4
   0x00000018 <+24>:	82 80 40 22	adddcc  %g1, %g2, %g1
   0x0000001c <+28>:	82 20 40 22	subd  %g1, %g2, %g1
   0x00000020 <+32>:	82 a0 40 22	subdcc  %g1, %g2, %g1
   0x00000024 <+36>:	f0 27 a0 44	st  %i0, [ %fp + 0x44 ]
   0x00000028 <+40>:	f2 27 a0 48	st  %i1, [ %fp + 0x48 ]
   0x0000002c <+44>:	c0 27 bf fc	clr  [ %fp + -4 ]
   0x00000030 <+48>:	82 10 20 01	mov  1, %g1
   0x00000034 <+52>:	c2 27 bf f8	st  %g1, [ %fp + -8 ]
   0x00000038 <+56>:	c0 27 bf f4	clr  [ %fp + -12 ]
   0x0000003c <+60>:	c2 07 a0 44	ld  [ %fp + 0x44 ], %g1
   0x00000040 <+64>:	80 a0 60 01	cmp  %g1, 1
   0x00000044 <+68>:	04 80 00 60	ble  0x1c4 <main+452>
   0x00000048 <+72>:	01 00 00 00	nop 
   0x0000004c <+76>:	10 80 00 19	b  0xb0 <main+176>
   0x00000050 <+80>:	01 00 00 00	nop 
   0x00000054 <+84>:	c2 07 bf f8	ld  [ %fp + -8 ], %g1
   0x00000058 <+88>:	83 28 60 02	sll  %g1, 2, %g1
   0x0000005c <+92>:	c4 07 a0 48	ld  [ %fp + 0x48 ], %g2
   0x00000060 <+96>:	82 00 80 01	add  %g2, %g1, %g1
   0x00000064 <+100>:	c2 00 40 00	ld  [ %g1 ], %g1
   0x00000068 <+104>:	90 10 00 01	mov  %g1, %o0
   0x0000006c <+108>:	40 00 00 00	call  0x6c <main+108>
   0x00000070 <+112>:	01 00 00 00	nop 
   0x00000074 <+116>:	d0 27 bf f0	st  %o0, [ %fp + -16 ]
   0x00000078 <+120>:	03 00 00 00	sethi  %hi(0), %g1
   0x0000007c <+124>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x00000080 <+128>:	c2 00 40 00	ld  [ %g1 ], %g1
   0x00000084 <+132>:	d0 07 bf f0	ld  [ %fp + -16 ], %o0
   0x00000088 <+136>:	92 10 00 01	mov  %g1, %o1
   0x0000008c <+140>:	40 00 00 00	call  0x8c <main+140>
   0x00000090 <+144>:	01 00 00 00	nop 
   0x00000094 <+148>:	84 10 00 08	mov  %o0, %g2
   0x00000098 <+152>:	03 00 00 00	sethi  %hi(0), %g1
   0x0000009c <+156>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x000000a0 <+160>:	c4 20 40 00	st  %g2, [ %g1 ]
   0x000000a4 <+164>:	c2 07 bf f8	ld  [ %fp + -8 ], %g1
   0x000000a8 <+168>:	82 00 60 01	inc  %g1
   0x000000ac <+172>:	c2 27 bf f8	st  %g1, [ %fp + -8 ]
   0x000000b0 <+176>:	c4 07 bf f8	ld  [ %fp + -8 ], %g2
   0x000000b4 <+180>:	c2 07 a0 44	ld  [ %fp + 0x44 ], %g1
   0x000000b8 <+184>:	80 a0 80 01	cmp  %g2, %g1
   0x000000bc <+188>:	06 bf ff e6	bl  0x54 <main+84>
   0x000000c0 <+192>:	01 00 00 00	nop 
   0x000000c4 <+196>:	03 00 00 00	sethi  %hi(0), %g1
   0x000000c8 <+200>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x000000cc <+204>:	c2 00 40 00	ld  [ %g1 ], %g1
   0x000000d0 <+208>:	90 10 00 01	mov  %g1, %o0
   0x000000d4 <+212>:	40 00 00 00	call  0xd4 <main+212>
   0x000000d8 <+216>:	01 00 00 00	nop 
   0x000000dc <+220>:	84 10 00 08	mov  %o0, %g2
   0x000000e0 <+224>:	03 00 00 00	sethi  %hi(0), %g1
   0x000000e4 <+228>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x000000e8 <+232>:	c4 20 40 00	st  %g2, [ %g1 ]
   0x000000ec <+236>:	03 00 00 00	sethi  %hi(0), %g1
   0x000000f0 <+240>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x000000f4 <+244>:	c2 00 40 00	ld  [ %g1 ], %g1
   0x000000f8 <+248>:	05 00 00 00	sethi  %hi(0), %g2
   0x000000fc <+252>:	90 10 a0 00	mov  %g2, %o0	! 0x0 <main>
   0x00000100 <+256>:	92 10 00 01	mov  %g1, %o1
   0x00000104 <+260>:	40 00 00 00	call  0x104 <main+260>
   0x00000108 <+264>:	01 00 00 00	nop 
   0x0000010c <+268>:	03 00 00 00	sethi  %hi(0), %g1
   0x00000110 <+272>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x00000114 <+276>:	c2 00 40 00	ld  [ %g1 ], %g1
   0x00000118 <+280>:	c2 27 bf f4	st  %g1, [ %fp + -12 ]
   0x0000011c <+284>:	10 80 00 1b	b  0x188 <main+392>
   0x00000120 <+288>:	01 00 00 00	nop 
   0x00000124 <+292>:	d0 07 bf f4	ld  [ %fp + -12 ], %o0
   0x00000128 <+296>:	40 00 00 00	call  0x128 <main+296>
   0x0000012c <+300>:	01 00 00 00	nop 
   0x00000130 <+304>:	d0 27 bf ec	st  %o0, [ %fp + -20 ]
   0x00000134 <+308>:	03 00 00 00	sethi  %hi(0), %g1
   0x00000138 <+312>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x0000013c <+316>:	c2 00 40 00	ld  [ %g1 ], %g1
   0x00000140 <+320>:	82 00 60 01	inc  %g1
   0x00000144 <+324>:	05 00 00 00	sethi  %hi(0), %g2
   0x00000148 <+328>:	90 10 a0 00	mov  %g2, %o0	! 0x0 <main>
   0x0000014c <+332>:	92 10 00 01	mov  %g1, %o1
   0x00000150 <+336>:	d4 07 bf ec	ld  [ %fp + -20 ], %o2
   0x00000154 <+340>:	40 00 00 00	call  0x154 <main+340>
   0x00000158 <+344>:	01 00 00 00	nop 
   0x0000015c <+348>:	d0 07 bf f4	ld  [ %fp + -12 ], %o0
   0x00000160 <+352>:	40 00 00 00	call  0x160 <main+352>
   0x00000164 <+356>:	01 00 00 00	nop 
   0x00000168 <+360>:	d0 27 bf f4	st  %o0, [ %fp + -12 ]
   0x0000016c <+364>:	03 00 00 00	sethi  %hi(0), %g1
   0x00000170 <+368>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x00000174 <+372>:	c2 00 40 00	ld  [ %g1 ], %g1
   0x00000178 <+376>:	84 00 60 01	add  %g1, 1, %g2
   0x0000017c <+380>:	03 00 00 00	sethi  %hi(0), %g1
   0x00000180 <+384>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x00000184 <+388>:	c4 20 40 00	st  %g2, [ %g1 ]
   0x00000188 <+392>:	c2 07 bf f4	ld  [ %fp + -12 ], %g1
   0x0000018c <+396>:	80 a0 60 00	cmp  %g1, 0
   0x00000190 <+400>:	02 80 00 0f	be  0x1cc <main+460>
   0x00000194 <+404>:	01 00 00 00	nop 
   0x00000198 <+408>:	03 00 00 00	sethi  %hi(0), %g1
   0x0000019c <+412>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x000001a0 <+416>:	c4 00 40 00	ld  [ %g1 ], %g2
   0x000001a4 <+420>:	03 00 00 00	sethi  %hi(0), %g1
   0x000001a8 <+424>:	82 10 60 00	mov  %g1, %g1	! 0x0 <main>
   0x000001ac <+428>:	c2 00 40 00	ld  [ %g1 ], %g1
   0x000001b0 <+432>:	80 a0 80 01	cmp  %g2, %g1
   0x000001b4 <+436>:	06 bf ff dc	bl  0x124 <main+292>
   0x000001b8 <+440>:	01 00 00 00	nop 
   0x000001bc <+444>:	10 80 00 04	b  0x1cc <main+460>
   0x000001c0 <+448>:	01 00 00 00	nop 
   0x000001c4 <+452>:	82 10 3f ff	mov  -1, %g1	! 0xffffffff
   0x000001c8 <+456>:	c2 27 bf fc	st  %g1, [ %fp + -4 ]
   0x000001cc <+460>:	c2 07 bf fc	ld  [ %fp + -4 ], %g1
   0x000001d0 <+464>:	b0 10 00 01	mov  %g1, %i0
   0x000001d4 <+468>:	81 e8 00 00	restore 
   0x000001d8 <+472>:	81 c3 e0 08	retl 
   0x000001dc <+476>:	01 00 00 00	nop 
End of assembler dump.
