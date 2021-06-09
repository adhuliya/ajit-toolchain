
/home/gauri/isav2/ajit-toolchain//development/amv-ajit-code/tests/obj/ccc-simd-2.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	8d 68 80 84 	adddreduce8  %g2, %g4, %g6
   8:	8f 68 81 05 	adddreduce16  %g2, %g5, %g7
   c:	8d 70 80 84 	ordreduce8  %g2, %g4, %g6
  10:	8f 70 81 05 	ordreduce16  %g2, %g5, %g7
  14:	8d 78 80 84 	anddreduce8  %g2, %g4, %g6
  18:	8f 78 81 05 	anddreduce16  %g2, %g5, %g7
  1c:	8d f0 80 84 	xordreduce8  %g2, %g4, %g6
  20:	8f f0 81 05 	xordreduce16  %g2, %g5, %g7
  24:	89 f8 80 01 	zbytedpos  %g2, %g1, %g4
  28:	89 f8 a0 ff 	zbytedpos  %g2, 0xff, %g4
  2c:	82 80 40 22 	adddcc  %g1, %g2, %g1
  30:	82 20 40 22 	subd  %g1, %g2, %g1
  34:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  38:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  3c:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  40:	c0 27 bf fc 	clr  [ %fp + -4 ]
  44:	82 10 20 01 	mov  1, %g1
  48:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  4c:	c0 27 bf f4 	clr  [ %fp + -12 ]
  50:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  54:	80 a0 60 01 	cmp  %g1, 1
  58:	04 80 00 60 	ble  1d8 <main+0x1d8>
  5c:	01 00 00 00 	nop 
  60:	10 80 00 19 	b  c4 <main+0xc4>
  64:	01 00 00 00 	nop 
  68:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  6c:	83 28 60 02 	sll  %g1, 2, %g1
  70:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  74:	82 00 80 01 	add  %g2, %g1, %g1
  78:	c2 00 40 00 	ld  [ %g1 ], %g1
  7c:	90 10 00 01 	mov  %g1, %o0
  80:	40 00 00 00 	call  80 <main+0x80>
  84:	01 00 00 00 	nop 
  88:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  8c:	03 00 00 00 	sethi  %hi(0), %g1
  90:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  94:	c2 00 40 00 	ld  [ %g1 ], %g1
  98:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  9c:	92 10 00 01 	mov  %g1, %o1
  a0:	40 00 00 00 	call  a0 <main+0xa0>
  a4:	01 00 00 00 	nop 
  a8:	84 10 00 08 	mov  %o0, %g2
  ac:	03 00 00 00 	sethi  %hi(0), %g1
  b0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  b4:	c4 20 40 00 	st  %g2, [ %g1 ]
  b8:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  bc:	82 00 60 01 	inc  %g1
  c0:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  c4:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  c8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  cc:	80 a0 80 01 	cmp  %g2, %g1
  d0:	06 bf ff e6 	bl  68 <main+0x68>
  d4:	01 00 00 00 	nop 
  d8:	03 00 00 00 	sethi  %hi(0), %g1
  dc:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  e0:	c2 00 40 00 	ld  [ %g1 ], %g1
  e4:	90 10 00 01 	mov  %g1, %o0
  e8:	40 00 00 00 	call  e8 <main+0xe8>
  ec:	01 00 00 00 	nop 
  f0:	84 10 00 08 	mov  %o0, %g2
  f4:	03 00 00 00 	sethi  %hi(0), %g1
  f8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  fc:	c4 20 40 00 	st  %g2, [ %g1 ]
 100:	03 00 00 00 	sethi  %hi(0), %g1
 104:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 108:	c2 00 40 00 	ld  [ %g1 ], %g1
 10c:	05 00 00 00 	sethi  %hi(0), %g2
 110:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 114:	92 10 00 01 	mov  %g1, %o1
 118:	40 00 00 00 	call  118 <main+0x118>
 11c:	01 00 00 00 	nop 
 120:	03 00 00 00 	sethi  %hi(0), %g1
 124:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 128:	c2 00 40 00 	ld  [ %g1 ], %g1
 12c:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 130:	10 80 00 1b 	b  19c <main+0x19c>
 134:	01 00 00 00 	nop 
 138:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 13c:	40 00 00 00 	call  13c <main+0x13c>
 140:	01 00 00 00 	nop 
 144:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 148:	03 00 00 00 	sethi  %hi(0), %g1
 14c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 150:	c2 00 40 00 	ld  [ %g1 ], %g1
 154:	82 00 60 01 	inc  %g1
 158:	05 00 00 00 	sethi  %hi(0), %g2
 15c:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 160:	92 10 00 01 	mov  %g1, %o1
 164:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 168:	40 00 00 00 	call  168 <main+0x168>
 16c:	01 00 00 00 	nop 
 170:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 174:	40 00 00 00 	call  174 <main+0x174>
 178:	01 00 00 00 	nop 
 17c:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 180:	03 00 00 00 	sethi  %hi(0), %g1
 184:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 188:	c2 00 40 00 	ld  [ %g1 ], %g1
 18c:	84 00 60 01 	add  %g1, 1, %g2
 190:	03 00 00 00 	sethi  %hi(0), %g1
 194:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 198:	c4 20 40 00 	st  %g2, [ %g1 ]
 19c:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 1a0:	80 a0 60 00 	cmp  %g1, 0
 1a4:	02 80 00 0f 	be  1e0 <main+0x1e0>
 1a8:	01 00 00 00 	nop 
 1ac:	03 00 00 00 	sethi  %hi(0), %g1
 1b0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1b4:	c4 00 40 00 	ld  [ %g1 ], %g2
 1b8:	03 00 00 00 	sethi  %hi(0), %g1
 1bc:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1c0:	c2 00 40 00 	ld  [ %g1 ], %g1
 1c4:	80 a0 80 01 	cmp  %g2, %g1
 1c8:	06 bf ff dc 	bl  138 <main+0x138>
 1cc:	01 00 00 00 	nop 
 1d0:	10 80 00 04 	b  1e0 <main+0x1e0>
 1d4:	01 00 00 00 	nop 
 1d8:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcc7>
 1dc:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1e0:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1e4:	b0 10 00 01 	mov  %g1, %i0
 1e8:	81 e8 00 00 	restore 
 1ec:	81 c3 e0 08 	retl 
 1f0:	01 00 00 00 	nop 

000001f4 <cons>:
 1f4:	9d e3 bf 98 	save  %sp, -104, %sp
 1f8:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1fc:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 200:	c0 27 bf fc 	clr  [ %fp + -4 ]
 204:	90 10 20 01 	mov  1, %o0
 208:	92 10 20 08 	mov  8, %o1
 20c:	40 00 00 00 	call  20c <cons+0x18>
 210:	01 00 00 00 	nop 
 214:	82 10 00 08 	mov  %o0, %g1
 218:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 21c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 220:	80 a0 60 00 	cmp  %g1, 0
 224:	02 80 00 0a 	be  24c <cons+0x58>
 228:	01 00 00 00 	nop 
 22c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 230:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 234:	c4 20 40 00 	st  %g2, [ %g1 ]
 238:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 23c:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 240:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 244:	10 80 00 03 	b  250 <cons+0x5c>
 248:	01 00 00 00 	nop 
 24c:	c0 27 bf fc 	clr  [ %fp + -4 ]
 250:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 254:	b0 10 00 01 	mov  %g1, %i0
 258:	81 e8 00 00 	restore 
 25c:	81 c3 e0 08 	retl 
 260:	01 00 00 00 	nop 

00000264 <car>:
 264:	9d e3 bf a0 	save  %sp, -96, %sp
 268:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 26c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 270:	80 a0 60 00 	cmp  %g1, 0
 274:	02 80 00 06 	be  28c <car+0x28>
 278:	01 00 00 00 	nop 
 27c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 280:	c2 00 40 00 	ld  [ %g1 ], %g1
 284:	10 80 00 03 	b  290 <car+0x2c>
 288:	01 00 00 00 	nop 
 28c:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcc7>
 290:	b0 10 00 01 	mov  %g1, %i0
 294:	81 e8 00 00 	restore 
 298:	81 c3 e0 08 	retl 
 29c:	01 00 00 00 	nop 

000002a0 <cdr>:
 2a0:	9d e3 bf a0 	save  %sp, -96, %sp
 2a4:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2a8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2ac:	80 a0 60 00 	cmp  %g1, 0
 2b0:	02 80 00 06 	be  2c8 <cdr+0x28>
 2b4:	01 00 00 00 	nop 
 2b8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2bc:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2c0:	10 80 00 03 	b  2cc <cdr+0x2c>
 2c4:	01 00 00 00 	nop 
 2c8:	82 10 20 00 	clr  %g1	! 0 <main>
 2cc:	b0 10 00 01 	mov  %g1, %i0
 2d0:	81 e8 00 00 	restore 
 2d4:	81 c3 e0 08 	retl 
 2d8:	01 00 00 00 	nop 

000002dc <ll>:
 2dc:	9d e3 bf 98 	save  %sp, -104, %sp
 2e0:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2e4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2e8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2ec:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2f0:	10 80 00 09 	b  314 <ll+0x38>
 2f4:	01 00 00 00 	nop 
 2f8:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 2fc:	82 00 60 01 	inc  %g1
 300:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 304:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 308:	40 00 00 00 	call  308 <ll+0x2c>
 30c:	01 00 00 00 	nop 
 310:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 314:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 318:	80 a0 60 00 	cmp  %g1, 0
 31c:	12 bf ff f7 	bne  2f8 <ll+0x1c>
 320:	01 00 00 00 	nop 
 324:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 328:	b0 10 00 01 	mov  %g1, %i0
 32c:	81 e8 00 00 	restore 
 330:	81 c3 e0 08 	retl 
 334:	01 00 00 00 	nop 

00000338 <llrec>:
 338:	9d e3 bf 98 	save  %sp, -104, %sp
 33c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 340:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 344:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 348:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 34c:	80 a0 60 00 	cmp  %g1, 0
 350:	12 80 00 05 	bne  364 <llrec+0x2c>
 354:	01 00 00 00 	nop 
 358:	82 10 20 00 	clr  %g1	! 0 <main>
 35c:	10 80 00 0b 	b  388 <llrec+0x50>
 360:	01 00 00 00 	nop 
 364:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 368:	40 00 00 00 	call  368 <llrec+0x30>
 36c:	01 00 00 00 	nop 
 370:	82 10 00 08 	mov  %o0, %g1
 374:	90 10 00 01 	mov  %g1, %o0
 378:	40 00 00 00 	call  378 <llrec+0x40>
 37c:	01 00 00 00 	nop 
 380:	82 10 00 08 	mov  %o0, %g1
 384:	82 00 60 01 	inc  %g1
 388:	b0 10 00 01 	mov  %g1, %i0
 38c:	81 e8 00 00 	restore 
 390:	81 c3 e0 08 	retl 
 394:	01 00 00 00 	nop 
