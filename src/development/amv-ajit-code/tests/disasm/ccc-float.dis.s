
/home/gauri/NEW/ajit-toolchain//development/amv-ajit-code/tests/obj/ccc-float.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	8d a0 a8 44 	vfadd32  %f2, %f4, %f6
   8:	8d a0 a8 84 	vfsub32  %f2, %f4, %f6
   c:	8d a0 a8 c4 	vfmul32  %f2, %f4, %f6
  10:	8d a0 a8 64 	vfadd16  %f2, %f4, %f6
  14:	8d a0 a8 a4 	vfsub16  %f2, %f4, %f6
  18:	8d a0 a8 e4 	vfmul16  %f2, %f4, %f6
  1c:	85 a0 2a 00 	faddreduce16  %f0, %f2
  20:	85 a0 6a 20 	fstoh  %f1, %f2
  24:	87 a0 6a 40 	fhtos  %f1, %f3
  28:	89 a0 29 02 	vfi16toh  %f0, %f2, %f4
  2c:	89 a0 29 22 	vfhtoi16  %f0, %f2, %f4
  30:	82 80 40 22 	adddcc  %g1, %g2, %g1
  34:	82 20 40 22 	subd  %g1, %g2, %g1
  38:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  3c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  40:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  44:	c0 27 bf fc 	clr  [ %fp + -4 ]
  48:	82 10 20 01 	mov  1, %g1
  4c:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  50:	c0 27 bf f4 	clr  [ %fp + -12 ]
  54:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  58:	80 a0 60 01 	cmp  %g1, 1
  5c:	04 80 00 60 	ble  1dc <main+0x1dc>
  60:	01 00 00 00 	nop 
  64:	10 80 00 19 	b  c8 <main+0xc8>
  68:	01 00 00 00 	nop 
  6c:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  70:	83 28 60 02 	sll  %g1, 2, %g1
  74:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  78:	82 00 80 01 	add  %g2, %g1, %g1
  7c:	c2 00 40 00 	ld  [ %g1 ], %g1
  80:	90 10 00 01 	mov  %g1, %o0
  84:	40 00 00 00 	call  84 <main+0x84>
  88:	01 00 00 00 	nop 
  8c:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  90:	03 00 00 00 	sethi  %hi(0), %g1
  94:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  98:	c2 00 40 00 	ld  [ %g1 ], %g1
  9c:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  a0:	92 10 00 01 	mov  %g1, %o1
  a4:	40 00 00 00 	call  a4 <main+0xa4>
  a8:	01 00 00 00 	nop 
  ac:	84 10 00 08 	mov  %o0, %g2
  b0:	03 00 00 00 	sethi  %hi(0), %g1
  b4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  b8:	c4 20 40 00 	st  %g2, [ %g1 ]
  bc:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  c0:	82 00 60 01 	inc  %g1
  c4:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  c8:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  cc:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  d0:	80 a0 80 01 	cmp  %g2, %g1
  d4:	06 bf ff e6 	bl  6c <main+0x6c>
  d8:	01 00 00 00 	nop 
  dc:	03 00 00 00 	sethi  %hi(0), %g1
  e0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  e4:	c2 00 40 00 	ld  [ %g1 ], %g1
  e8:	90 10 00 01 	mov  %g1, %o0
  ec:	40 00 00 00 	call  ec <main+0xec>
  f0:	01 00 00 00 	nop 
  f4:	84 10 00 08 	mov  %o0, %g2
  f8:	03 00 00 00 	sethi  %hi(0), %g1
  fc:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 100:	c4 20 40 00 	st  %g2, [ %g1 ]
 104:	03 00 00 00 	sethi  %hi(0), %g1
 108:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 10c:	c2 00 40 00 	ld  [ %g1 ], %g1
 110:	05 00 00 00 	sethi  %hi(0), %g2
 114:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 118:	92 10 00 01 	mov  %g1, %o1
 11c:	40 00 00 00 	call  11c <main+0x11c>
 120:	01 00 00 00 	nop 
 124:	03 00 00 00 	sethi  %hi(0), %g1
 128:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 12c:	c2 00 40 00 	ld  [ %g1 ], %g1
 130:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 134:	10 80 00 1b 	b  1a0 <main+0x1a0>
 138:	01 00 00 00 	nop 
 13c:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 140:	40 00 00 00 	call  140 <main+0x140>
 144:	01 00 00 00 	nop 
 148:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 14c:	03 00 00 00 	sethi  %hi(0), %g1
 150:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 154:	c2 00 40 00 	ld  [ %g1 ], %g1
 158:	82 00 60 01 	inc  %g1
 15c:	05 00 00 00 	sethi  %hi(0), %g2
 160:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 164:	92 10 00 01 	mov  %g1, %o1
 168:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 16c:	40 00 00 00 	call  16c <main+0x16c>
 170:	01 00 00 00 	nop 
 174:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 178:	40 00 00 00 	call  178 <main+0x178>
 17c:	01 00 00 00 	nop 
 180:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 184:	03 00 00 00 	sethi  %hi(0), %g1
 188:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 18c:	c2 00 40 00 	ld  [ %g1 ], %g1
 190:	84 00 60 01 	add  %g1, 1, %g2
 194:	03 00 00 00 	sethi  %hi(0), %g1
 198:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 19c:	c4 20 40 00 	st  %g2, [ %g1 ]
 1a0:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 1a4:	80 a0 60 00 	cmp  %g1, 0
 1a8:	02 80 00 0f 	be  1e4 <main+0x1e4>
 1ac:	01 00 00 00 	nop 
 1b0:	03 00 00 00 	sethi  %hi(0), %g1
 1b4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1b8:	c4 00 40 00 	ld  [ %g1 ], %g2
 1bc:	03 00 00 00 	sethi  %hi(0), %g1
 1c0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1c4:	c2 00 40 00 	ld  [ %g1 ], %g1
 1c8:	80 a0 80 01 	cmp  %g2, %g1
 1cc:	06 bf ff dc 	bl  13c <main+0x13c>
 1d0:	01 00 00 00 	nop 
 1d4:	10 80 00 04 	b  1e4 <main+0x1e4>
 1d8:	01 00 00 00 	nop 
 1dc:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcc3>
 1e0:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1e4:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1e8:	b0 10 00 01 	mov  %g1, %i0
 1ec:	81 e8 00 00 	restore 
 1f0:	81 c3 e0 08 	retl 
 1f4:	01 00 00 00 	nop 

000001f8 <cons>:
 1f8:	9d e3 bf 98 	save  %sp, -104, %sp
 1fc:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 200:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 204:	c0 27 bf fc 	clr  [ %fp + -4 ]
 208:	90 10 20 01 	mov  1, %o0
 20c:	92 10 20 08 	mov  8, %o1
 210:	40 00 00 00 	call  210 <cons+0x18>
 214:	01 00 00 00 	nop 
 218:	82 10 00 08 	mov  %o0, %g1
 21c:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 220:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 224:	80 a0 60 00 	cmp  %g1, 0
 228:	02 80 00 0a 	be  250 <cons+0x58>
 22c:	01 00 00 00 	nop 
 230:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 234:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 238:	c4 20 40 00 	st  %g2, [ %g1 ]
 23c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 240:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 244:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 248:	10 80 00 03 	b  254 <cons+0x5c>
 24c:	01 00 00 00 	nop 
 250:	c0 27 bf fc 	clr  [ %fp + -4 ]
 254:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 258:	b0 10 00 01 	mov  %g1, %i0
 25c:	81 e8 00 00 	restore 
 260:	81 c3 e0 08 	retl 
 264:	01 00 00 00 	nop 

00000268 <car>:
 268:	9d e3 bf a0 	save  %sp, -96, %sp
 26c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 270:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 274:	80 a0 60 00 	cmp  %g1, 0
 278:	02 80 00 06 	be  290 <car+0x28>
 27c:	01 00 00 00 	nop 
 280:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 284:	c2 00 40 00 	ld  [ %g1 ], %g1
 288:	10 80 00 03 	b  294 <car+0x2c>
 28c:	01 00 00 00 	nop 
 290:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcc3>
 294:	b0 10 00 01 	mov  %g1, %i0
 298:	81 e8 00 00 	restore 
 29c:	81 c3 e0 08 	retl 
 2a0:	01 00 00 00 	nop 

000002a4 <cdr>:
 2a4:	9d e3 bf a0 	save  %sp, -96, %sp
 2a8:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2ac:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2b0:	80 a0 60 00 	cmp  %g1, 0
 2b4:	02 80 00 06 	be  2cc <cdr+0x28>
 2b8:	01 00 00 00 	nop 
 2bc:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2c0:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2c4:	10 80 00 03 	b  2d0 <cdr+0x2c>
 2c8:	01 00 00 00 	nop 
 2cc:	82 10 20 00 	clr  %g1	! 0 <main>
 2d0:	b0 10 00 01 	mov  %g1, %i0
 2d4:	81 e8 00 00 	restore 
 2d8:	81 c3 e0 08 	retl 
 2dc:	01 00 00 00 	nop 

000002e0 <ll>:
 2e0:	9d e3 bf 98 	save  %sp, -104, %sp
 2e4:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2e8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2ec:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2f0:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2f4:	10 80 00 09 	b  318 <ll+0x38>
 2f8:	01 00 00 00 	nop 
 2fc:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 300:	82 00 60 01 	inc  %g1
 304:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 308:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 30c:	40 00 00 00 	call  30c <ll+0x2c>
 310:	01 00 00 00 	nop 
 314:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 318:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 31c:	80 a0 60 00 	cmp  %g1, 0
 320:	12 bf ff f7 	bne  2fc <ll+0x1c>
 324:	01 00 00 00 	nop 
 328:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 32c:	b0 10 00 01 	mov  %g1, %i0
 330:	81 e8 00 00 	restore 
 334:	81 c3 e0 08 	retl 
 338:	01 00 00 00 	nop 

0000033c <llrec>:
 33c:	9d e3 bf 98 	save  %sp, -104, %sp
 340:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 344:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 348:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 34c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 350:	80 a0 60 00 	cmp  %g1, 0
 354:	12 80 00 05 	bne  368 <llrec+0x2c>
 358:	01 00 00 00 	nop 
 35c:	82 10 20 00 	clr  %g1	! 0 <main>
 360:	10 80 00 0b 	b  38c <llrec+0x50>
 364:	01 00 00 00 	nop 
 368:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 36c:	40 00 00 00 	call  36c <llrec+0x30>
 370:	01 00 00 00 	nop 
 374:	82 10 00 08 	mov  %o0, %g1
 378:	90 10 00 01 	mov  %g1, %o0
 37c:	40 00 00 00 	call  37c <llrec+0x40>
 380:	01 00 00 00 	nop 
 384:	82 10 00 08 	mov  %o0, %g1
 388:	82 00 60 01 	inc  %g1
 38c:	b0 10 00 01 	mov  %g1, %i0
 390:	81 e8 00 00 	restore 
 394:	81 c3 e0 08 	retl 
 398:	01 00 00 00 	nop 
