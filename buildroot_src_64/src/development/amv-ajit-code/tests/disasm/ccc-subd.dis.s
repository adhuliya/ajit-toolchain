
/lindata/My-work/Professional/iitb/tests/obj/ccc-subd.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	82 00 40 22 	addd  %g1, %g2, %g1
   8:	82 80 40 22 	adddcc  %g1, %g2, %g1
   c:	82 20 40 22 	subd  %g1, %g2, %g1
  10:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  14:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  18:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  1c:	c0 27 bf fc 	clr  [ %fp + -4 ]
  20:	82 10 20 01 	mov  1, %g1
  24:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  28:	c0 27 bf f4 	clr  [ %fp + -12 ]
  2c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  30:	80 a0 60 01 	cmp  %g1, 1
  34:	04 80 00 60 	ble  1b4 <main+0x1b4>
  38:	01 00 00 00 	nop 
  3c:	10 80 00 19 	b  a0 <main+0xa0>
  40:	01 00 00 00 	nop 
  44:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  48:	83 28 60 02 	sll  %g1, 2, %g1
  4c:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  50:	82 00 80 01 	add  %g2, %g1, %g1
  54:	c2 00 40 00 	ld  [ %g1 ], %g1
  58:	90 10 00 01 	mov  %g1, %o0
  5c:	40 00 00 00 	call  5c <main+0x5c>
  60:	01 00 00 00 	nop 
  64:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  68:	03 00 00 00 	sethi  %hi(0), %g1
  6c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  70:	c2 00 40 00 	ld  [ %g1 ], %g1
  74:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  78:	92 10 00 01 	mov  %g1, %o1
  7c:	40 00 00 00 	call  7c <main+0x7c>
  80:	01 00 00 00 	nop 
  84:	84 10 00 08 	mov  %o0, %g2
  88:	03 00 00 00 	sethi  %hi(0), %g1
  8c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  90:	c4 20 40 00 	st  %g2, [ %g1 ]
  94:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  98:	82 00 60 01 	inc  %g1
  9c:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  a0:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  a4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  a8:	80 a0 80 01 	cmp  %g2, %g1
  ac:	06 bf ff e6 	bl  44 <main+0x44>
  b0:	01 00 00 00 	nop 
  b4:	03 00 00 00 	sethi  %hi(0), %g1
  b8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  bc:	c2 00 40 00 	ld  [ %g1 ], %g1
  c0:	90 10 00 01 	mov  %g1, %o0
  c4:	40 00 00 00 	call  c4 <main+0xc4>
  c8:	01 00 00 00 	nop 
  cc:	84 10 00 08 	mov  %o0, %g2
  d0:	03 00 00 00 	sethi  %hi(0), %g1
  d4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  d8:	c4 20 40 00 	st  %g2, [ %g1 ]
  dc:	03 00 00 00 	sethi  %hi(0), %g1
  e0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  e4:	c2 00 40 00 	ld  [ %g1 ], %g1
  e8:	05 00 00 00 	sethi  %hi(0), %g2
  ec:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
  f0:	92 10 00 01 	mov  %g1, %o1
  f4:	40 00 00 00 	call  f4 <main+0xf4>
  f8:	01 00 00 00 	nop 
  fc:	03 00 00 00 	sethi  %hi(0), %g1
 100:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 104:	c2 00 40 00 	ld  [ %g1 ], %g1
 108:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 10c:	10 80 00 1b 	b  178 <main+0x178>
 110:	01 00 00 00 	nop 
 114:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 118:	40 00 00 00 	call  118 <main+0x118>
 11c:	01 00 00 00 	nop 
 120:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 124:	03 00 00 00 	sethi  %hi(0), %g1
 128:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 12c:	c2 00 40 00 	ld  [ %g1 ], %g1
 130:	82 00 60 01 	inc  %g1
 134:	05 00 00 00 	sethi  %hi(0), %g2
 138:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 13c:	92 10 00 01 	mov  %g1, %o1
 140:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 144:	40 00 00 00 	call  144 <main+0x144>
 148:	01 00 00 00 	nop 
 14c:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 150:	40 00 00 00 	call  150 <main+0x150>
 154:	01 00 00 00 	nop 
 158:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 15c:	03 00 00 00 	sethi  %hi(0), %g1
 160:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 164:	c2 00 40 00 	ld  [ %g1 ], %g1
 168:	84 00 60 01 	add  %g1, 1, %g2
 16c:	03 00 00 00 	sethi  %hi(0), %g1
 170:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 174:	c4 20 40 00 	st  %g2, [ %g1 ]
 178:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 17c:	80 a0 60 00 	cmp  %g1, 0
 180:	02 80 00 0f 	be  1bc <main+0x1bc>
 184:	01 00 00 00 	nop 
 188:	03 00 00 00 	sethi  %hi(0), %g1
 18c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 190:	c4 00 40 00 	ld  [ %g1 ], %g2
 194:	03 00 00 00 	sethi  %hi(0), %g1
 198:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 19c:	c2 00 40 00 	ld  [ %g1 ], %g1
 1a0:	80 a0 80 01 	cmp  %g2, %g1
 1a4:	06 bf ff dc 	bl  114 <main+0x114>
 1a8:	01 00 00 00 	nop 
 1ac:	10 80 00 04 	b  1bc <main+0x1bc>
 1b0:	01 00 00 00 	nop 
 1b4:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffceb>
 1b8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1bc:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1c0:	b0 10 00 01 	mov  %g1, %i0
 1c4:	81 e8 00 00 	restore 
 1c8:	81 c3 e0 08 	retl 
 1cc:	01 00 00 00 	nop 

000001d0 <cons>:
 1d0:	9d e3 bf 98 	save  %sp, -104, %sp
 1d4:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1d8:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 1dc:	c0 27 bf fc 	clr  [ %fp + -4 ]
 1e0:	90 10 20 01 	mov  1, %o0
 1e4:	92 10 20 08 	mov  8, %o1
 1e8:	40 00 00 00 	call  1e8 <cons+0x18>
 1ec:	01 00 00 00 	nop 
 1f0:	82 10 00 08 	mov  %o0, %g1
 1f4:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1f8:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1fc:	80 a0 60 00 	cmp  %g1, 0
 200:	02 80 00 0a 	be  228 <cons+0x58>
 204:	01 00 00 00 	nop 
 208:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 20c:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 210:	c4 20 40 00 	st  %g2, [ %g1 ]
 214:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 218:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 21c:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 220:	10 80 00 03 	b  22c <cons+0x5c>
 224:	01 00 00 00 	nop 
 228:	c0 27 bf fc 	clr  [ %fp + -4 ]
 22c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 230:	b0 10 00 01 	mov  %g1, %i0
 234:	81 e8 00 00 	restore 
 238:	81 c3 e0 08 	retl 
 23c:	01 00 00 00 	nop 

00000240 <car>:
 240:	9d e3 bf a0 	save  %sp, -96, %sp
 244:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 248:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 24c:	80 a0 60 00 	cmp  %g1, 0
 250:	02 80 00 06 	be  268 <car+0x28>
 254:	01 00 00 00 	nop 
 258:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 25c:	c2 00 40 00 	ld  [ %g1 ], %g1
 260:	10 80 00 03 	b  26c <car+0x2c>
 264:	01 00 00 00 	nop 
 268:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffceb>
 26c:	b0 10 00 01 	mov  %g1, %i0
 270:	81 e8 00 00 	restore 
 274:	81 c3 e0 08 	retl 
 278:	01 00 00 00 	nop 

0000027c <cdr>:
 27c:	9d e3 bf a0 	save  %sp, -96, %sp
 280:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 284:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 288:	80 a0 60 00 	cmp  %g1, 0
 28c:	02 80 00 06 	be  2a4 <cdr+0x28>
 290:	01 00 00 00 	nop 
 294:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 298:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 29c:	10 80 00 03 	b  2a8 <cdr+0x2c>
 2a0:	01 00 00 00 	nop 
 2a4:	82 10 20 00 	clr  %g1	! 0 <main>
 2a8:	b0 10 00 01 	mov  %g1, %i0
 2ac:	81 e8 00 00 	restore 
 2b0:	81 c3 e0 08 	retl 
 2b4:	01 00 00 00 	nop 

000002b8 <ll>:
 2b8:	9d e3 bf 98 	save  %sp, -104, %sp
 2bc:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2c0:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2c4:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2c8:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2cc:	10 80 00 09 	b  2f0 <ll+0x38>
 2d0:	01 00 00 00 	nop 
 2d4:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 2d8:	82 00 60 01 	inc  %g1
 2dc:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 2e0:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 2e4:	40 00 00 00 	call  2e4 <ll+0x2c>
 2e8:	01 00 00 00 	nop 
 2ec:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 2f0:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 2f4:	80 a0 60 00 	cmp  %g1, 0
 2f8:	12 bf ff f7 	bne  2d4 <ll+0x1c>
 2fc:	01 00 00 00 	nop 
 300:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 304:	b0 10 00 01 	mov  %g1, %i0
 308:	81 e8 00 00 	restore 
 30c:	81 c3 e0 08 	retl 
 310:	01 00 00 00 	nop 

00000314 <llrec>:
 314:	9d e3 bf 98 	save  %sp, -104, %sp
 318:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 31c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 320:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 324:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 328:	80 a0 60 00 	cmp  %g1, 0
 32c:	12 80 00 05 	bne  340 <llrec+0x2c>
 330:	01 00 00 00 	nop 
 334:	82 10 20 00 	clr  %g1	! 0 <main>
 338:	10 80 00 0b 	b  364 <llrec+0x50>
 33c:	01 00 00 00 	nop 
 340:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 344:	40 00 00 00 	call  344 <llrec+0x30>
 348:	01 00 00 00 	nop 
 34c:	82 10 00 08 	mov  %o0, %g1
 350:	90 10 00 01 	mov  %g1, %o0
 354:	40 00 00 00 	call  354 <llrec+0x40>
 358:	01 00 00 00 	nop 
 35c:	82 10 00 08 	mov  %o0, %g1
 360:	82 00 60 01 	inc  %g1
 364:	b0 10 00 01 	mov  %g1, %i0
 368:	81 e8 00 00 	restore 
 36c:	81 c3 e0 08 	retl 
 370:	01 00 00 00 	nop 
