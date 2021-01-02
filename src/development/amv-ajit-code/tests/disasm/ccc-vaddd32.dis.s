
/lindata/My-work/Professional/iitb/tests/obj/ccc-vaddd32.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	82 00 42 42 	vaddd32  %g1, %g2, %g1
   8:	82 20 42 42 	vsubd32  %g1, %g2, %g1
   c:	82 50 42 42 	vumuld32  %g1, %g2, %g1
  10:	82 58 42 42 	vsmuld32  %g1, %g2, %g1
  14:	82 80 40 22 	adddcc  %g1, %g2, %g1
  18:	82 20 40 22 	subd  %g1, %g2, %g1
  1c:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  20:	8c 00 82 44 	vaddd32  %g2, %g4, %g6
  24:	8c 20 82 44 	vsubd32  %g2, %g4, %g6
  28:	8c 50 82 44 	vumuld32  %g2, %g4, %g6
  2c:	8c 58 82 44 	vsmuld32  %g2, %g4, %g6
  30:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  34:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  38:	c0 27 bf fc 	clr  [ %fp + -4 ]
  3c:	82 10 20 01 	mov  1, %g1
  40:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  44:	c0 27 bf f4 	clr  [ %fp + -12 ]
  48:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  4c:	80 a0 60 01 	cmp  %g1, 1
  50:	04 80 00 60 	ble  1d0 <main+0x1d0>
  54:	01 00 00 00 	nop 
  58:	10 80 00 19 	b  bc <main+0xbc>
  5c:	01 00 00 00 	nop 
  60:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  64:	83 28 60 02 	sll  %g1, 2, %g1
  68:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  6c:	82 00 80 01 	add  %g2, %g1, %g1
  70:	c2 00 40 00 	ld  [ %g1 ], %g1
  74:	90 10 00 01 	mov  %g1, %o0
  78:	40 00 00 00 	call  78 <main+0x78>
  7c:	01 00 00 00 	nop 
  80:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  84:	03 00 00 00 	sethi  %hi(0), %g1
  88:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  8c:	c2 00 40 00 	ld  [ %g1 ], %g1
  90:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  94:	92 10 00 01 	mov  %g1, %o1
  98:	40 00 00 00 	call  98 <main+0x98>
  9c:	01 00 00 00 	nop 
  a0:	84 10 00 08 	mov  %o0, %g2
  a4:	03 00 00 00 	sethi  %hi(0), %g1
  a8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  ac:	c4 20 40 00 	st  %g2, [ %g1 ]
  b0:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  b4:	82 00 60 01 	inc  %g1
  b8:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  bc:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  c0:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  c4:	80 a0 80 01 	cmp  %g2, %g1
  c8:	06 bf ff e6 	bl  60 <main+0x60>
  cc:	01 00 00 00 	nop 
  d0:	03 00 00 00 	sethi  %hi(0), %g1
  d4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  d8:	c2 00 40 00 	ld  [ %g1 ], %g1
  dc:	90 10 00 01 	mov  %g1, %o0
  e0:	40 00 00 00 	call  e0 <main+0xe0>
  e4:	01 00 00 00 	nop 
  e8:	84 10 00 08 	mov  %o0, %g2
  ec:	03 00 00 00 	sethi  %hi(0), %g1
  f0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  f4:	c4 20 40 00 	st  %g2, [ %g1 ]
  f8:	03 00 00 00 	sethi  %hi(0), %g1
  fc:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 100:	c2 00 40 00 	ld  [ %g1 ], %g1
 104:	05 00 00 00 	sethi  %hi(0), %g2
 108:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 10c:	92 10 00 01 	mov  %g1, %o1
 110:	40 00 00 00 	call  110 <main+0x110>
 114:	01 00 00 00 	nop 
 118:	03 00 00 00 	sethi  %hi(0), %g1
 11c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 120:	c2 00 40 00 	ld  [ %g1 ], %g1
 124:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 128:	10 80 00 1b 	b  194 <main+0x194>
 12c:	01 00 00 00 	nop 
 130:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 134:	40 00 00 00 	call  134 <main+0x134>
 138:	01 00 00 00 	nop 
 13c:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 140:	03 00 00 00 	sethi  %hi(0), %g1
 144:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 148:	c2 00 40 00 	ld  [ %g1 ], %g1
 14c:	82 00 60 01 	inc  %g1
 150:	05 00 00 00 	sethi  %hi(0), %g2
 154:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 158:	92 10 00 01 	mov  %g1, %o1
 15c:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 160:	40 00 00 00 	call  160 <main+0x160>
 164:	01 00 00 00 	nop 
 168:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 16c:	40 00 00 00 	call  16c <main+0x16c>
 170:	01 00 00 00 	nop 
 174:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 178:	03 00 00 00 	sethi  %hi(0), %g1
 17c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 180:	c2 00 40 00 	ld  [ %g1 ], %g1
 184:	84 00 60 01 	add  %g1, 1, %g2
 188:	03 00 00 00 	sethi  %hi(0), %g1
 18c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 190:	c4 20 40 00 	st  %g2, [ %g1 ]
 194:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 198:	80 a0 60 00 	cmp  %g1, 0
 19c:	02 80 00 0f 	be  1d8 <main+0x1d8>
 1a0:	01 00 00 00 	nop 
 1a4:	03 00 00 00 	sethi  %hi(0), %g1
 1a8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1ac:	c4 00 40 00 	ld  [ %g1 ], %g2
 1b0:	03 00 00 00 	sethi  %hi(0), %g1
 1b4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1b8:	c2 00 40 00 	ld  [ %g1 ], %g1
 1bc:	80 a0 80 01 	cmp  %g2, %g1
 1c0:	06 bf ff dc 	bl  130 <main+0x130>
 1c4:	01 00 00 00 	nop 
 1c8:	10 80 00 04 	b  1d8 <main+0x1d8>
 1cc:	01 00 00 00 	nop 
 1d0:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffccf>
 1d4:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1d8:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1dc:	b0 10 00 01 	mov  %g1, %i0
 1e0:	81 e8 00 00 	restore 
 1e4:	81 c3 e0 08 	retl 
 1e8:	01 00 00 00 	nop 

000001ec <cons>:
 1ec:	9d e3 bf 98 	save  %sp, -104, %sp
 1f0:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1f4:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 1f8:	c0 27 bf fc 	clr  [ %fp + -4 ]
 1fc:	90 10 20 01 	mov  1, %o0
 200:	92 10 20 08 	mov  8, %o1
 204:	40 00 00 00 	call  204 <cons+0x18>
 208:	01 00 00 00 	nop 
 20c:	82 10 00 08 	mov  %o0, %g1
 210:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 214:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 218:	80 a0 60 00 	cmp  %g1, 0
 21c:	02 80 00 0a 	be  244 <cons+0x58>
 220:	01 00 00 00 	nop 
 224:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 228:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 22c:	c4 20 40 00 	st  %g2, [ %g1 ]
 230:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 234:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 238:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 23c:	10 80 00 03 	b  248 <cons+0x5c>
 240:	01 00 00 00 	nop 
 244:	c0 27 bf fc 	clr  [ %fp + -4 ]
 248:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 24c:	b0 10 00 01 	mov  %g1, %i0
 250:	81 e8 00 00 	restore 
 254:	81 c3 e0 08 	retl 
 258:	01 00 00 00 	nop 

0000025c <car>:
 25c:	9d e3 bf a0 	save  %sp, -96, %sp
 260:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 264:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 268:	80 a0 60 00 	cmp  %g1, 0
 26c:	02 80 00 06 	be  284 <car+0x28>
 270:	01 00 00 00 	nop 
 274:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 278:	c2 00 40 00 	ld  [ %g1 ], %g1
 27c:	10 80 00 03 	b  288 <car+0x2c>
 280:	01 00 00 00 	nop 
 284:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffccf>
 288:	b0 10 00 01 	mov  %g1, %i0
 28c:	81 e8 00 00 	restore 
 290:	81 c3 e0 08 	retl 
 294:	01 00 00 00 	nop 

00000298 <cdr>:
 298:	9d e3 bf a0 	save  %sp, -96, %sp
 29c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2a0:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2a4:	80 a0 60 00 	cmp  %g1, 0
 2a8:	02 80 00 06 	be  2c0 <cdr+0x28>
 2ac:	01 00 00 00 	nop 
 2b0:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2b4:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2b8:	10 80 00 03 	b  2c4 <cdr+0x2c>
 2bc:	01 00 00 00 	nop 
 2c0:	82 10 20 00 	clr  %g1	! 0 <main>
 2c4:	b0 10 00 01 	mov  %g1, %i0
 2c8:	81 e8 00 00 	restore 
 2cc:	81 c3 e0 08 	retl 
 2d0:	01 00 00 00 	nop 

000002d4 <ll>:
 2d4:	9d e3 bf 98 	save  %sp, -104, %sp
 2d8:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2dc:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2e0:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2e4:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2e8:	10 80 00 09 	b  30c <ll+0x38>
 2ec:	01 00 00 00 	nop 
 2f0:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 2f4:	82 00 60 01 	inc  %g1
 2f8:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 2fc:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 300:	40 00 00 00 	call  300 <ll+0x2c>
 304:	01 00 00 00 	nop 
 308:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 30c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 310:	80 a0 60 00 	cmp  %g1, 0
 314:	12 bf ff f7 	bne  2f0 <ll+0x1c>
 318:	01 00 00 00 	nop 
 31c:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 320:	b0 10 00 01 	mov  %g1, %i0
 324:	81 e8 00 00 	restore 
 328:	81 c3 e0 08 	retl 
 32c:	01 00 00 00 	nop 

00000330 <llrec>:
 330:	9d e3 bf 98 	save  %sp, -104, %sp
 334:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 338:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 33c:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 340:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 344:	80 a0 60 00 	cmp  %g1, 0
 348:	12 80 00 05 	bne  35c <llrec+0x2c>
 34c:	01 00 00 00 	nop 
 350:	82 10 20 00 	clr  %g1	! 0 <main>
 354:	10 80 00 0b 	b  380 <llrec+0x50>
 358:	01 00 00 00 	nop 
 35c:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 360:	40 00 00 00 	call  360 <llrec+0x30>
 364:	01 00 00 00 	nop 
 368:	82 10 00 08 	mov  %o0, %g1
 36c:	90 10 00 01 	mov  %g1, %o0
 370:	40 00 00 00 	call  370 <llrec+0x40>
 374:	01 00 00 00 	nop 
 378:	82 10 00 08 	mov  %o0, %g1
 37c:	82 00 60 01 	inc  %g1
 380:	b0 10 00 01 	mov  %g1, %i0
 384:	81 e8 00 00 	restore 
 388:	81 c3 e0 08 	retl 
 38c:	01 00 00 00 	nop 
