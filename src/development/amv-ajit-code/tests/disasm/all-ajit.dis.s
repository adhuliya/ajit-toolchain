
/lindata/My-work/Professional/iitb/tests/obj/all-ajit.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	84 00 80 24 	addd  %g2, %g4, %g2
   8:	84 80 80 24 	adddcc  %g2, %g4, %g2
   c:	84 20 80 24 	subd  %g2, %g4, %g2
  10:	84 a0 80 24 	subdcc  %g2, %g4, %g2
  14:	84 70 80 24 	udivd  %g2, %g4, %g2
  18:	82 00 40 22 	addd  %g1, %g2, %g1
  1c:	82 80 40 22 	adddcc  %g1, %g2, %g1
  20:	82 20 40 22 	subd  %g1, %g2, %g1
  24:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  28:	85 28 60 98 	slld  %g1, 0x18, %g2
  2c:	85 30 60 98 	srld  %g1, 0x18, %g2
  30:	85 38 60 98 	srad  %g1, 0x18, %g2
  34:	85 28 40 83 	slld  %g1, %g3, %g2
  38:	85 30 40 83 	srld  %g1, %g3, %g2
  3c:	85 38 40 83 	srad  %g1, %g3, %g2
  40:	82 00 40 22 	addd  %g1, %g2, %g1
  44:	82 80 40 22 	adddcc  %g1, %g2, %g1
  48:	82 20 40 22 	subd  %g1, %g2, %g1
  4c:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  50:	82 10 40 22 	ord  %g1, %g2, %g1
  54:	82 90 40 22 	ordcc  %g1, %g2, %g1
  58:	82 30 40 22 	ordn  %g1, %g2, %g1
  5c:	82 b0 40 22 	ordncc  %g1, %g2, %g1
  60:	82 98 40 22 	xordcc  %g1, %g2, %g1
  64:	82 38 40 22 	xnord  %g1, %g2, %g1
  68:	82 b8 40 22 	xnordcc  %g1, %g2, %g1
  6c:	82 08 40 22 	andd  %g1, %g2, %g1
  70:	82 88 40 22 	anddcc  %g1, %g2, %g1
  74:	82 28 40 22 	anddn  %g1, %g2, %g1
  78:	82 a8 40 22 	anddncc  %g1, %g2, %g1
  7c:	a5 28 80 84 	slld  %g2, %g4, %l2
  80:	a5 28 a0 82 	slld  %g2, 2, %l2
  84:	8d 30 80 84 	srld  %g2, %g4, %g6
  88:	8d 30 a0 82 	srld  %g2, 2, %g6
  8c:	a1 38 80 84 	srad  %g2, %g4, %l0
  90:	a1 38 a0 82 	srad  %g2, 2, %l0
  94:	82 00 40 22 	addd  %g1, %g2, %g1
  98:	82 80 40 22 	adddcc  %g1, %g2, %g1
  9c:	82 20 40 22 	subd  %g1, %g2, %g1
  a0:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  a4:	80 58 40 02 	smul  %g1, %g2, %g0
  a8:	80 58 40 22 	smuld  %g1, %g2, %g0
  ac:	80 50 40 02 	umul  %g1, %g2, %g0
  b0:	80 50 40 22 	umuld  %g1, %g2, %g0
  b4:	80 d0 40 22 	umuldcc  %g1, %g2, %g0
  b8:	80 58 40 22 	smuld  %g1, %g2, %g0
  bc:	80 d8 40 22 	smuldcc  %g1, %g2, %g0
  c0:	82 70 40 22 	udivd  %g1, %g2, %g1
  c4:	84 70 40 22 	udivd  %g1, %g2, %g2
  c8:	86 70 40 22 	udivd  %g1, %g2, %g3
  cc:	88 70 40 22 	udivd  %g1, %g2, %g4
  d0:	8a 70 40 22 	udivd  %g1, %g2, %g5
  d4:	8c 70 40 22 	udivd  %g1, %g2, %g6
  d8:	82 78 40 22 	sdivd  %g1, %g2, %g1
  dc:	8c f0 40 22 	udivdcc  %g1, %g2, %g6
  e0:	82 f8 40 22 	sdivdcc  %g1, %g2, %g1
  e4:	8d a0 a8 64 	vfadd16  %f2, %f4, %f6
  e8:	8d a0 a8 a4 	vfsub16  %f2, %f4, %f6
  ec:	8d a0 a8 e4 	vfmul16  %f2, %f4, %f6
  f0:	8d a0 a8 44 	vfadd32  %f2, %f4, %f6
  f4:	8d a0 a8 84 	vfsub32  %f2, %f4, %f6
  f8:	8d a0 a8 c4 	vfmul32  %f2, %f4, %f6
  fc:	89 a0 aa 00 	faddreduce16  %f2, %f4
 100:	87 a0 6a 20 	fstoh  %f1, %f3
 104:	87 a0 6a 40 	fhtos  %f1, %f3
 108:	82 80 40 22 	adddcc  %g1, %g2, %g1
 10c:	82 20 40 22 	subd  %g1, %g2, %g1
 110:	82 a0 40 22 	subdcc  %g1, %g2, %g1
 114:	89 68 80 81 	adddreduce8  %g2, %g1, %g4
 118:	89 70 80 81 	ordreduce8  %g2, %g1, %g4
 11c:	89 78 80 81 	anddreduce8  %g2, %g1, %g4
 120:	89 f0 80 81 	xordreduce8  %g2, %g1, %g4
 124:	89 f8 80 01 	zbytedpos  %g2, %g1, %g4
 128:	89 f8 a0 ff 	zbytedpos  %g2, 0xff, %g4
 12c:	89 68 81 01 	adddreduce16  %g2, %g1, %g4
 130:	89 70 81 01 	ordreduce16  %g2, %g1, %g4
 134:	89 78 81 01 	anddreduce16  %g2, %g1, %g4
 138:	89 f0 81 01 	xordreduce16  %g2, %g1, %g4
 13c:	82 80 40 22 	adddcc  %g1, %g2, %g1
 140:	82 20 40 22 	subd  %g1, %g2, %g1
 144:	82 a0 40 22 	subdcc  %g1, %g2, %g1
 148:	82 00 41 42 	vaddd16  %g1, %g2, %g1
 14c:	82 20 41 42 	vsubd16  %g1, %g2, %g1
 150:	82 50 41 42 	vumuld16  %g1, %g2, %g1
 154:	82 58 41 42 	vsmuld16  %g1, %g2, %g1
 158:	82 80 40 22 	adddcc  %g1, %g2, %g1
 15c:	82 20 40 22 	subd  %g1, %g2, %g1
 160:	82 a0 40 22 	subdcc  %g1, %g2, %g1
 164:	8c 00 81 44 	vaddd16  %g2, %g4, %g6
 168:	8c 20 81 44 	vsubd16  %g2, %g4, %g6
 16c:	8c 50 81 44 	vumuld16  %g2, %g4, %g6
 170:	8c 58 81 44 	vsmuld16  %g2, %g4, %g6
 174:	82 00 42 42 	vaddd32  %g1, %g2, %g1
 178:	82 20 42 42 	vsubd32  %g1, %g2, %g1
 17c:	82 50 42 42 	vumuld32  %g1, %g2, %g1
 180:	82 58 42 42 	vsmuld32  %g1, %g2, %g1
 184:	82 80 40 22 	adddcc  %g1, %g2, %g1
 188:	82 20 40 22 	subd  %g1, %g2, %g1
 18c:	82 a0 40 22 	subdcc  %g1, %g2, %g1
 190:	8c 00 82 44 	vaddd32  %g2, %g4, %g6
 194:	8c 20 82 44 	vsubd32  %g2, %g4, %g6
 198:	8c 50 82 44 	vumuld32  %g2, %g4, %g6
 19c:	8c 58 82 44 	vsmuld32  %g2, %g4, %g6
 1a0:	82 00 40 c2 	vaddd8  %g1, %g2, %g1
 1a4:	82 20 40 c2 	vsubd8  %g1, %g2, %g1
 1a8:	82 50 40 c2 	vumuld8  %g1, %g2, %g1
 1ac:	82 58 40 c2 	vsmuld8  %g1, %g2, %g1
 1b0:	82 80 40 22 	adddcc  %g1, %g2, %g1
 1b4:	82 20 40 22 	subd  %g1, %g2, %g1
 1b8:	82 a0 40 22 	subdcc  %g1, %g2, %g1
 1bc:	8c 00 80 c4 	vaddd8  %g2, %g4, %g6
 1c0:	8c 20 80 c4 	vsubd8  %g2, %g4, %g6
 1c4:	8c 50 80 c4 	vumuld8  %g2, %g4, %g6
 1c8:	8c 58 80 c4 	vsmuld8  %g2, %g4, %g6
 1cc:	c9 78 81 01 	cswap  [ %g2 + %g1 ] (8), %g4
 1d0:	c9 78 af ff 	cswap  [ %g2 + 0xfff ], %g4
 1d4:	c9 f8 81 41 	cswapa  [ %g2 + %g1 ] (10), %g4
 1d8:	c9 f8 af ff 	cswapa  [ %g2 + 0xfff ], %g4
 1dc:	c9 7f bf f8 	cswap  [ %fp + -8 ], %g4
 1e0:	82 80 40 22 	adddcc  %g1, %g2, %g1
 1e4:	82 20 40 22 	subd  %g1, %g2, %g1
 1e8:	82 a0 40 22 	subdcc  %g1, %g2, %g1
 1ec:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1f0:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 1f4:	c0 27 bf fc 	clr  [ %fp + -4 ]
 1f8:	82 10 20 01 	mov  1, %g1
 1fc:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 200:	c0 27 bf f4 	clr  [ %fp + -12 ]
 204:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 208:	80 a0 60 01 	cmp  %g1, 1
 20c:	04 80 00 60 	ble  38c <main+0x38c>
 210:	01 00 00 00 	nop 
 214:	10 80 00 19 	b  278 <main+0x278>
 218:	01 00 00 00 	nop 
 21c:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 220:	83 28 60 02 	sll  %g1, 2, %g1
 224:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 228:	82 00 80 01 	add  %g2, %g1, %g1
 22c:	c2 00 40 00 	ld  [ %g1 ], %g1
 230:	90 10 00 01 	mov  %g1, %o0
 234:	40 00 00 00 	call  234 <main+0x234>
 238:	01 00 00 00 	nop 
 23c:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
 240:	03 00 00 00 	sethi  %hi(0), %g1
 244:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 248:	c2 00 40 00 	ld  [ %g1 ], %g1
 24c:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
 250:	92 10 00 01 	mov  %g1, %o1
 254:	40 00 00 00 	call  254 <main+0x254>
 258:	01 00 00 00 	nop 
 25c:	84 10 00 08 	mov  %o0, %g2
 260:	03 00 00 00 	sethi  %hi(0), %g1
 264:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 268:	c4 20 40 00 	st  %g2, [ %g1 ]
 26c:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 270:	82 00 60 01 	inc  %g1
 274:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 278:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
 27c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 280:	80 a0 80 01 	cmp  %g2, %g1
 284:	06 bf ff e6 	bl  21c <main+0x21c>
 288:	01 00 00 00 	nop 
 28c:	03 00 00 00 	sethi  %hi(0), %g1
 290:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 294:	c2 00 40 00 	ld  [ %g1 ], %g1
 298:	90 10 00 01 	mov  %g1, %o0
 29c:	40 00 00 00 	call  29c <main+0x29c>
 2a0:	01 00 00 00 	nop 
 2a4:	84 10 00 08 	mov  %o0, %g2
 2a8:	03 00 00 00 	sethi  %hi(0), %g1
 2ac:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 2b0:	c4 20 40 00 	st  %g2, [ %g1 ]
 2b4:	03 00 00 00 	sethi  %hi(0), %g1
 2b8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 2bc:	c2 00 40 00 	ld  [ %g1 ], %g1
 2c0:	05 00 00 00 	sethi  %hi(0), %g2
 2c4:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 2c8:	92 10 00 01 	mov  %g1, %o1
 2cc:	40 00 00 00 	call  2cc <main+0x2cc>
 2d0:	01 00 00 00 	nop 
 2d4:	03 00 00 00 	sethi  %hi(0), %g1
 2d8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 2dc:	c2 00 40 00 	ld  [ %g1 ], %g1
 2e0:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 2e4:	10 80 00 1b 	b  350 <main+0x350>
 2e8:	01 00 00 00 	nop 
 2ec:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 2f0:	40 00 00 00 	call  2f0 <main+0x2f0>
 2f4:	01 00 00 00 	nop 
 2f8:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 2fc:	03 00 00 00 	sethi  %hi(0), %g1
 300:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 304:	c2 00 40 00 	ld  [ %g1 ], %g1
 308:	82 00 60 01 	inc  %g1
 30c:	05 00 00 00 	sethi  %hi(0), %g2
 310:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 314:	92 10 00 01 	mov  %g1, %o1
 318:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 31c:	40 00 00 00 	call  31c <main+0x31c>
 320:	01 00 00 00 	nop 
 324:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 328:	40 00 00 00 	call  328 <main+0x328>
 32c:	01 00 00 00 	nop 
 330:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 334:	03 00 00 00 	sethi  %hi(0), %g1
 338:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 33c:	c2 00 40 00 	ld  [ %g1 ], %g1
 340:	84 00 60 01 	add  %g1, 1, %g2
 344:	03 00 00 00 	sethi  %hi(0), %g1
 348:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 34c:	c4 20 40 00 	st  %g2, [ %g1 ]
 350:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 354:	80 a0 60 00 	cmp  %g1, 0
 358:	02 80 00 0f 	be  394 <main+0x394>
 35c:	01 00 00 00 	nop 
 360:	03 00 00 00 	sethi  %hi(0), %g1
 364:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 368:	c4 00 40 00 	ld  [ %g1 ], %g2
 36c:	03 00 00 00 	sethi  %hi(0), %g1
 370:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 374:	c2 00 40 00 	ld  [ %g1 ], %g1
 378:	80 a0 80 01 	cmp  %g2, %g1
 37c:	06 bf ff dc 	bl  2ec <main+0x2ec>
 380:	01 00 00 00 	nop 
 384:	10 80 00 04 	b  394 <main+0x394>
 388:	01 00 00 00 	nop 
 38c:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffb13>
 390:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 394:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 398:	b0 10 00 01 	mov  %g1, %i0
 39c:	81 e8 00 00 	restore 
 3a0:	81 c3 e0 08 	retl 
 3a4:	01 00 00 00 	nop 

000003a8 <cons>:
 3a8:	9d e3 bf 98 	save  %sp, -104, %sp
 3ac:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 3b0:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 3b4:	c0 27 bf fc 	clr  [ %fp + -4 ]
 3b8:	90 10 20 01 	mov  1, %o0
 3bc:	92 10 20 08 	mov  8, %o1
 3c0:	40 00 00 00 	call  3c0 <cons+0x18>
 3c4:	01 00 00 00 	nop 
 3c8:	82 10 00 08 	mov  %o0, %g1
 3cc:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 3d0:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 3d4:	80 a0 60 00 	cmp  %g1, 0
 3d8:	02 80 00 0a 	be  400 <cons+0x58>
 3dc:	01 00 00 00 	nop 
 3e0:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 3e4:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 3e8:	c4 20 40 00 	st  %g2, [ %g1 ]
 3ec:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 3f0:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 3f4:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 3f8:	10 80 00 03 	b  404 <cons+0x5c>
 3fc:	01 00 00 00 	nop 
 400:	c0 27 bf fc 	clr  [ %fp + -4 ]
 404:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 408:	b0 10 00 01 	mov  %g1, %i0
 40c:	81 e8 00 00 	restore 
 410:	81 c3 e0 08 	retl 
 414:	01 00 00 00 	nop 

00000418 <car>:
 418:	9d e3 bf a0 	save  %sp, -96, %sp
 41c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 420:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 424:	80 a0 60 00 	cmp  %g1, 0
 428:	02 80 00 06 	be  440 <car+0x28>
 42c:	01 00 00 00 	nop 
 430:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 434:	c2 00 40 00 	ld  [ %g1 ], %g1
 438:	10 80 00 03 	b  444 <car+0x2c>
 43c:	01 00 00 00 	nop 
 440:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffb13>
 444:	b0 10 00 01 	mov  %g1, %i0
 448:	81 e8 00 00 	restore 
 44c:	81 c3 e0 08 	retl 
 450:	01 00 00 00 	nop 

00000454 <cdr>:
 454:	9d e3 bf a0 	save  %sp, -96, %sp
 458:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 45c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 460:	80 a0 60 00 	cmp  %g1, 0
 464:	02 80 00 06 	be  47c <cdr+0x28>
 468:	01 00 00 00 	nop 
 46c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 470:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 474:	10 80 00 03 	b  480 <cdr+0x2c>
 478:	01 00 00 00 	nop 
 47c:	82 10 20 00 	clr  %g1	! 0 <main>
 480:	b0 10 00 01 	mov  %g1, %i0
 484:	81 e8 00 00 	restore 
 488:	81 c3 e0 08 	retl 
 48c:	01 00 00 00 	nop 

00000490 <ll>:
 490:	9d e3 bf 98 	save  %sp, -104, %sp
 494:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 498:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 49c:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 4a0:	c0 27 bf f8 	clr  [ %fp + -8 ]
 4a4:	10 80 00 09 	b  4c8 <ll+0x38>
 4a8:	01 00 00 00 	nop 
 4ac:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 4b0:	82 00 60 01 	inc  %g1
 4b4:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 4b8:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 4bc:	40 00 00 00 	call  4bc <ll+0x2c>
 4c0:	01 00 00 00 	nop 
 4c4:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 4c8:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 4cc:	80 a0 60 00 	cmp  %g1, 0
 4d0:	12 bf ff f7 	bne  4ac <ll+0x1c>
 4d4:	01 00 00 00 	nop 
 4d8:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 4dc:	b0 10 00 01 	mov  %g1, %i0
 4e0:	81 e8 00 00 	restore 
 4e4:	81 c3 e0 08 	retl 
 4e8:	01 00 00 00 	nop 

000004ec <llrec>:
 4ec:	9d e3 bf 98 	save  %sp, -104, %sp
 4f0:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 4f4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 4f8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 4fc:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 500:	80 a0 60 00 	cmp  %g1, 0
 504:	12 80 00 05 	bne  518 <llrec+0x2c>
 508:	01 00 00 00 	nop 
 50c:	82 10 20 00 	clr  %g1	! 0 <main>
 510:	10 80 00 0b 	b  53c <llrec+0x50>
 514:	01 00 00 00 	nop 
 518:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 51c:	40 00 00 00 	call  51c <llrec+0x30>
 520:	01 00 00 00 	nop 
 524:	82 10 00 08 	mov  %o0, %g1
 528:	90 10 00 01 	mov  %g1, %o0
 52c:	40 00 00 00 	call  52c <llrec+0x40>
 530:	01 00 00 00 	nop 
 534:	82 10 00 08 	mov  %o0, %g1
 538:	82 00 60 01 	inc  %g1
 53c:	b0 10 00 01 	mov  %g1, %i0
 540:	81 e8 00 00 	restore 
 544:	81 c3 e0 08 	retl 
 548:	01 00 00 00 	nop 
