
/lindata/My-work/Professional/iitb/tests/obj/ccc-cswap.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	c9 78 81 01 	cswap  [ %g2 + %g1 ] (8), %g4
   8:	c9 78 af ff 	cswap  [ %g2 + 0xfff ], %g4
   c:	c9 f8 81 41 	cswapa  [ %g2 + %g1 ] (10), %g4
  10:	c9 f8 af ff 	cswapa  [ %g2 + 0xfff ], %g4
  14:	c9 7f bf f8 	cswap  [ %fp + -8 ], %g4
  18:	82 80 40 22 	adddcc  %g1, %g2, %g1
  1c:	82 20 40 22 	subd  %g1, %g2, %g1
  20:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  24:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  28:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  2c:	c0 27 bf fc 	clr  [ %fp + -4 ]
  30:	82 10 20 01 	mov  1, %g1
  34:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  38:	c0 27 bf f4 	clr  [ %fp + -12 ]
  3c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  40:	80 a0 60 01 	cmp  %g1, 1
  44:	04 80 00 60 	ble  1c4 <main+0x1c4>
  48:	01 00 00 00 	nop 
  4c:	10 80 00 19 	b  b0 <main+0xb0>
  50:	01 00 00 00 	nop 
  54:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  58:	83 28 60 02 	sll  %g1, 2, %g1
  5c:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  60:	82 00 80 01 	add  %g2, %g1, %g1
  64:	c2 00 40 00 	ld  [ %g1 ], %g1
  68:	90 10 00 01 	mov  %g1, %o0
  6c:	40 00 00 00 	call  6c <main+0x6c>
  70:	01 00 00 00 	nop 
  74:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  78:	03 00 00 00 	sethi  %hi(0), %g1
  7c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  80:	c2 00 40 00 	ld  [ %g1 ], %g1
  84:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  88:	92 10 00 01 	mov  %g1, %o1
  8c:	40 00 00 00 	call  8c <main+0x8c>
  90:	01 00 00 00 	nop 
  94:	84 10 00 08 	mov  %o0, %g2
  98:	03 00 00 00 	sethi  %hi(0), %g1
  9c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  a0:	c4 20 40 00 	st  %g2, [ %g1 ]
  a4:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  a8:	82 00 60 01 	inc  %g1
  ac:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  b0:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  b4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  b8:	80 a0 80 01 	cmp  %g2, %g1
  bc:	06 bf ff e6 	bl  54 <main+0x54>
  c0:	01 00 00 00 	nop 
  c4:	03 00 00 00 	sethi  %hi(0), %g1
  c8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  cc:	c2 00 40 00 	ld  [ %g1 ], %g1
  d0:	90 10 00 01 	mov  %g1, %o0
  d4:	40 00 00 00 	call  d4 <main+0xd4>
  d8:	01 00 00 00 	nop 
  dc:	84 10 00 08 	mov  %o0, %g2
  e0:	03 00 00 00 	sethi  %hi(0), %g1
  e4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  e8:	c4 20 40 00 	st  %g2, [ %g1 ]
  ec:	03 00 00 00 	sethi  %hi(0), %g1
  f0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  f4:	c2 00 40 00 	ld  [ %g1 ], %g1
  f8:	05 00 00 00 	sethi  %hi(0), %g2
  fc:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 100:	92 10 00 01 	mov  %g1, %o1
 104:	40 00 00 00 	call  104 <main+0x104>
 108:	01 00 00 00 	nop 
 10c:	03 00 00 00 	sethi  %hi(0), %g1
 110:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 114:	c2 00 40 00 	ld  [ %g1 ], %g1
 118:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 11c:	10 80 00 1b 	b  188 <main+0x188>
 120:	01 00 00 00 	nop 
 124:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 128:	40 00 00 00 	call  128 <main+0x128>
 12c:	01 00 00 00 	nop 
 130:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 134:	03 00 00 00 	sethi  %hi(0), %g1
 138:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 13c:	c2 00 40 00 	ld  [ %g1 ], %g1
 140:	82 00 60 01 	inc  %g1
 144:	05 00 00 00 	sethi  %hi(0), %g2
 148:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 14c:	92 10 00 01 	mov  %g1, %o1
 150:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 154:	40 00 00 00 	call  154 <main+0x154>
 158:	01 00 00 00 	nop 
 15c:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 160:	40 00 00 00 	call  160 <main+0x160>
 164:	01 00 00 00 	nop 
 168:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 16c:	03 00 00 00 	sethi  %hi(0), %g1
 170:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 174:	c2 00 40 00 	ld  [ %g1 ], %g1
 178:	84 00 60 01 	add  %g1, 1, %g2
 17c:	03 00 00 00 	sethi  %hi(0), %g1
 180:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 184:	c4 20 40 00 	st  %g2, [ %g1 ]
 188:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 18c:	80 a0 60 00 	cmp  %g1, 0
 190:	02 80 00 0f 	be  1cc <main+0x1cc>
 194:	01 00 00 00 	nop 
 198:	03 00 00 00 	sethi  %hi(0), %g1
 19c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1a0:	c4 00 40 00 	ld  [ %g1 ], %g2
 1a4:	03 00 00 00 	sethi  %hi(0), %g1
 1a8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1ac:	c2 00 40 00 	ld  [ %g1 ], %g1
 1b0:	80 a0 80 01 	cmp  %g2, %g1
 1b4:	06 bf ff dc 	bl  124 <main+0x124>
 1b8:	01 00 00 00 	nop 
 1bc:	10 80 00 04 	b  1cc <main+0x1cc>
 1c0:	01 00 00 00 	nop 
 1c4:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcdb>
 1c8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1cc:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1d0:	b0 10 00 01 	mov  %g1, %i0
 1d4:	81 e8 00 00 	restore 
 1d8:	81 c3 e0 08 	retl 
 1dc:	01 00 00 00 	nop 

000001e0 <cons>:
 1e0:	9d e3 bf 98 	save  %sp, -104, %sp
 1e4:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1e8:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 1ec:	c0 27 bf fc 	clr  [ %fp + -4 ]
 1f0:	90 10 20 01 	mov  1, %o0
 1f4:	92 10 20 08 	mov  8, %o1
 1f8:	40 00 00 00 	call  1f8 <cons+0x18>
 1fc:	01 00 00 00 	nop 
 200:	82 10 00 08 	mov  %o0, %g1
 204:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 208:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 20c:	80 a0 60 00 	cmp  %g1, 0
 210:	02 80 00 0a 	be  238 <cons+0x58>
 214:	01 00 00 00 	nop 
 218:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 21c:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 220:	c4 20 40 00 	st  %g2, [ %g1 ]
 224:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 228:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 22c:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 230:	10 80 00 03 	b  23c <cons+0x5c>
 234:	01 00 00 00 	nop 
 238:	c0 27 bf fc 	clr  [ %fp + -4 ]
 23c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 240:	b0 10 00 01 	mov  %g1, %i0
 244:	81 e8 00 00 	restore 
 248:	81 c3 e0 08 	retl 
 24c:	01 00 00 00 	nop 

00000250 <car>:
 250:	9d e3 bf a0 	save  %sp, -96, %sp
 254:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 258:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 25c:	80 a0 60 00 	cmp  %g1, 0
 260:	02 80 00 06 	be  278 <car+0x28>
 264:	01 00 00 00 	nop 
 268:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 26c:	c2 00 40 00 	ld  [ %g1 ], %g1
 270:	10 80 00 03 	b  27c <car+0x2c>
 274:	01 00 00 00 	nop 
 278:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcdb>
 27c:	b0 10 00 01 	mov  %g1, %i0
 280:	81 e8 00 00 	restore 
 284:	81 c3 e0 08 	retl 
 288:	01 00 00 00 	nop 

0000028c <cdr>:
 28c:	9d e3 bf a0 	save  %sp, -96, %sp
 290:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 294:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 298:	80 a0 60 00 	cmp  %g1, 0
 29c:	02 80 00 06 	be  2b4 <cdr+0x28>
 2a0:	01 00 00 00 	nop 
 2a4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2a8:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2ac:	10 80 00 03 	b  2b8 <cdr+0x2c>
 2b0:	01 00 00 00 	nop 
 2b4:	82 10 20 00 	clr  %g1	! 0 <main>
 2b8:	b0 10 00 01 	mov  %g1, %i0
 2bc:	81 e8 00 00 	restore 
 2c0:	81 c3 e0 08 	retl 
 2c4:	01 00 00 00 	nop 

000002c8 <ll>:
 2c8:	9d e3 bf 98 	save  %sp, -104, %sp
 2cc:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2d0:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2d4:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2d8:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2dc:	10 80 00 09 	b  300 <ll+0x38>
 2e0:	01 00 00 00 	nop 
 2e4:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 2e8:	82 00 60 01 	inc  %g1
 2ec:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 2f0:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 2f4:	40 00 00 00 	call  2f4 <ll+0x2c>
 2f8:	01 00 00 00 	nop 
 2fc:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 300:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 304:	80 a0 60 00 	cmp  %g1, 0
 308:	12 bf ff f7 	bne  2e4 <ll+0x1c>
 30c:	01 00 00 00 	nop 
 310:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 314:	b0 10 00 01 	mov  %g1, %i0
 318:	81 e8 00 00 	restore 
 31c:	81 c3 e0 08 	retl 
 320:	01 00 00 00 	nop 

00000324 <llrec>:
 324:	9d e3 bf 98 	save  %sp, -104, %sp
 328:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 32c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 330:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 334:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 338:	80 a0 60 00 	cmp  %g1, 0
 33c:	12 80 00 05 	bne  350 <llrec+0x2c>
 340:	01 00 00 00 	nop 
 344:	82 10 20 00 	clr  %g1	! 0 <main>
 348:	10 80 00 0b 	b  374 <llrec+0x50>
 34c:	01 00 00 00 	nop 
 350:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 354:	40 00 00 00 	call  354 <llrec+0x30>
 358:	01 00 00 00 	nop 
 35c:	82 10 00 08 	mov  %o0, %g1
 360:	90 10 00 01 	mov  %g1, %o0
 364:	40 00 00 00 	call  364 <llrec+0x40>
 368:	01 00 00 00 	nop 
 36c:	82 10 00 08 	mov  %o0, %g1
 370:	82 00 60 01 	inc  %g1
 374:	b0 10 00 01 	mov  %g1, %i0
 378:	81 e8 00 00 	restore 
 37c:	81 c3 e0 08 	retl 
 380:	01 00 00 00 	nop 
