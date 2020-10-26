
/home/gauri/isav2/ajit-toolchain//development/amv-ajit-code/tests/obj/ccc-umuld.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	82 00 40 22 	addd  %g1, %g2, %g1
   8:	82 80 40 22 	adddcc  %g1, %g2, %g1
   c:	82 20 40 22 	subd  %g1, %g2, %g1
  10:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  14:	80 50 40 22 	umuld  %g1, %g2, %g0
  18:	80 d0 40 22 	umuldcc  %g1, %g2, %g0
  1c:	80 58 40 22 	smuld  %g1, %g2, %g0
  20:	80 d8 40 22 	smuldcc  %g1, %g2, %g0
  24:	82 70 40 22 	udivd  %g1, %g2, %g1
  28:	84 70 40 22 	udivd  %g1, %g2, %g2
  2c:	86 70 40 22 	udivd  %g1, %g2, %g3
  30:	88 70 40 22 	udivd  %g1, %g2, %g4
  34:	8a 70 40 22 	udivd  %g1, %g2, %g5
  38:	8c 70 40 22 	udivd  %g1, %g2, %g6
  3c:	82 78 40 22 	sdivd  %g1, %g2, %g1
  40:	8c f0 40 22 	udivdcc  %g1, %g2, %g6
  44:	82 f8 40 22 	sdivdcc  %g1, %g2, %g1
  48:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  4c:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  50:	c0 27 bf fc 	clr  [ %fp + -4 ]
  54:	82 10 20 01 	mov  1, %g1
  58:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  5c:	c0 27 bf f4 	clr  [ %fp + -12 ]
  60:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  64:	80 a0 60 01 	cmp  %g1, 1
  68:	04 80 00 60 	ble  1e8 <main+0x1e8>
  6c:	01 00 00 00 	nop 
  70:	10 80 00 19 	b  d4 <main+0xd4>
  74:	01 00 00 00 	nop 
  78:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  7c:	83 28 60 02 	sll  %g1, 2, %g1
  80:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  84:	82 00 80 01 	add  %g2, %g1, %g1
  88:	c2 00 40 00 	ld  [ %g1 ], %g1
  8c:	90 10 00 01 	mov  %g1, %o0
  90:	40 00 00 00 	call  90 <main+0x90>
  94:	01 00 00 00 	nop 
  98:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  9c:	03 00 00 00 	sethi  %hi(0), %g1
  a0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  a4:	c2 00 40 00 	ld  [ %g1 ], %g1
  a8:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  ac:	92 10 00 01 	mov  %g1, %o1
  b0:	40 00 00 00 	call  b0 <main+0xb0>
  b4:	01 00 00 00 	nop 
  b8:	84 10 00 08 	mov  %o0, %g2
  bc:	03 00 00 00 	sethi  %hi(0), %g1
  c0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  c4:	c4 20 40 00 	st  %g2, [ %g1 ]
  c8:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  cc:	82 00 60 01 	inc  %g1
  d0:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  d4:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  d8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  dc:	80 a0 80 01 	cmp  %g2, %g1
  e0:	06 bf ff e6 	bl  78 <main+0x78>
  e4:	01 00 00 00 	nop 
  e8:	03 00 00 00 	sethi  %hi(0), %g1
  ec:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  f0:	c2 00 40 00 	ld  [ %g1 ], %g1
  f4:	90 10 00 01 	mov  %g1, %o0
  f8:	40 00 00 00 	call  f8 <main+0xf8>
  fc:	01 00 00 00 	nop 
 100:	84 10 00 08 	mov  %o0, %g2
 104:	03 00 00 00 	sethi  %hi(0), %g1
 108:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 10c:	c4 20 40 00 	st  %g2, [ %g1 ]
 110:	03 00 00 00 	sethi  %hi(0), %g1
 114:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 118:	c2 00 40 00 	ld  [ %g1 ], %g1
 11c:	05 00 00 00 	sethi  %hi(0), %g2
 120:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 124:	92 10 00 01 	mov  %g1, %o1
 128:	40 00 00 00 	call  128 <main+0x128>
 12c:	01 00 00 00 	nop 
 130:	03 00 00 00 	sethi  %hi(0), %g1
 134:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 138:	c2 00 40 00 	ld  [ %g1 ], %g1
 13c:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 140:	10 80 00 1b 	b  1ac <main+0x1ac>
 144:	01 00 00 00 	nop 
 148:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 14c:	40 00 00 00 	call  14c <main+0x14c>
 150:	01 00 00 00 	nop 
 154:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 158:	03 00 00 00 	sethi  %hi(0), %g1
 15c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 160:	c2 00 40 00 	ld  [ %g1 ], %g1
 164:	82 00 60 01 	inc  %g1
 168:	05 00 00 00 	sethi  %hi(0), %g2
 16c:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 170:	92 10 00 01 	mov  %g1, %o1
 174:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 178:	40 00 00 00 	call  178 <main+0x178>
 17c:	01 00 00 00 	nop 
 180:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 184:	40 00 00 00 	call  184 <main+0x184>
 188:	01 00 00 00 	nop 
 18c:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 190:	03 00 00 00 	sethi  %hi(0), %g1
 194:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 198:	c2 00 40 00 	ld  [ %g1 ], %g1
 19c:	84 00 60 01 	add  %g1, 1, %g2
 1a0:	03 00 00 00 	sethi  %hi(0), %g1
 1a4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1a8:	c4 20 40 00 	st  %g2, [ %g1 ]
 1ac:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 1b0:	80 a0 60 00 	cmp  %g1, 0
 1b4:	02 80 00 0f 	be  1f0 <main+0x1f0>
 1b8:	01 00 00 00 	nop 
 1bc:	03 00 00 00 	sethi  %hi(0), %g1
 1c0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1c4:	c4 00 40 00 	ld  [ %g1 ], %g2
 1c8:	03 00 00 00 	sethi  %hi(0), %g1
 1cc:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1d0:	c2 00 40 00 	ld  [ %g1 ], %g1
 1d4:	80 a0 80 01 	cmp  %g2, %g1
 1d8:	06 bf ff dc 	bl  148 <main+0x148>
 1dc:	01 00 00 00 	nop 
 1e0:	10 80 00 04 	b  1f0 <main+0x1f0>
 1e4:	01 00 00 00 	nop 
 1e8:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcb7>
 1ec:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1f0:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1f4:	b0 10 00 01 	mov  %g1, %i0
 1f8:	81 e8 00 00 	restore 
 1fc:	81 c3 e0 08 	retl 
 200:	01 00 00 00 	nop 

00000204 <cons>:
 204:	9d e3 bf 98 	save  %sp, -104, %sp
 208:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 20c:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 210:	c0 27 bf fc 	clr  [ %fp + -4 ]
 214:	90 10 20 01 	mov  1, %o0
 218:	92 10 20 08 	mov  8, %o1
 21c:	40 00 00 00 	call  21c <cons+0x18>
 220:	01 00 00 00 	nop 
 224:	82 10 00 08 	mov  %o0, %g1
 228:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 22c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 230:	80 a0 60 00 	cmp  %g1, 0
 234:	02 80 00 0a 	be  25c <cons+0x58>
 238:	01 00 00 00 	nop 
 23c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 240:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 244:	c4 20 40 00 	st  %g2, [ %g1 ]
 248:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 24c:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 250:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 254:	10 80 00 03 	b  260 <cons+0x5c>
 258:	01 00 00 00 	nop 
 25c:	c0 27 bf fc 	clr  [ %fp + -4 ]
 260:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 264:	b0 10 00 01 	mov  %g1, %i0
 268:	81 e8 00 00 	restore 
 26c:	81 c3 e0 08 	retl 
 270:	01 00 00 00 	nop 

00000274 <car>:
 274:	9d e3 bf a0 	save  %sp, -96, %sp
 278:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 27c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 280:	80 a0 60 00 	cmp  %g1, 0
 284:	02 80 00 06 	be  29c <car+0x28>
 288:	01 00 00 00 	nop 
 28c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 290:	c2 00 40 00 	ld  [ %g1 ], %g1
 294:	10 80 00 03 	b  2a0 <car+0x2c>
 298:	01 00 00 00 	nop 
 29c:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcb7>
 2a0:	b0 10 00 01 	mov  %g1, %i0
 2a4:	81 e8 00 00 	restore 
 2a8:	81 c3 e0 08 	retl 
 2ac:	01 00 00 00 	nop 

000002b0 <cdr>:
 2b0:	9d e3 bf a0 	save  %sp, -96, %sp
 2b4:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2b8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2bc:	80 a0 60 00 	cmp  %g1, 0
 2c0:	02 80 00 06 	be  2d8 <cdr+0x28>
 2c4:	01 00 00 00 	nop 
 2c8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2cc:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2d0:	10 80 00 03 	b  2dc <cdr+0x2c>
 2d4:	01 00 00 00 	nop 
 2d8:	82 10 20 00 	clr  %g1	! 0 <main>
 2dc:	b0 10 00 01 	mov  %g1, %i0
 2e0:	81 e8 00 00 	restore 
 2e4:	81 c3 e0 08 	retl 
 2e8:	01 00 00 00 	nop 

000002ec <ll>:
 2ec:	9d e3 bf 98 	save  %sp, -104, %sp
 2f0:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2f4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2f8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2fc:	c0 27 bf f8 	clr  [ %fp + -8 ]
 300:	10 80 00 09 	b  324 <ll+0x38>
 304:	01 00 00 00 	nop 
 308:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 30c:	82 00 60 01 	inc  %g1
 310:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 314:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 318:	40 00 00 00 	call  318 <ll+0x2c>
 31c:	01 00 00 00 	nop 
 320:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 324:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 328:	80 a0 60 00 	cmp  %g1, 0
 32c:	12 bf ff f7 	bne  308 <ll+0x1c>
 330:	01 00 00 00 	nop 
 334:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 338:	b0 10 00 01 	mov  %g1, %i0
 33c:	81 e8 00 00 	restore 
 340:	81 c3 e0 08 	retl 
 344:	01 00 00 00 	nop 

00000348 <llrec>:
 348:	9d e3 bf 98 	save  %sp, -104, %sp
 34c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 350:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 354:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 358:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 35c:	80 a0 60 00 	cmp  %g1, 0
 360:	12 80 00 05 	bne  374 <llrec+0x2c>
 364:	01 00 00 00 	nop 
 368:	82 10 20 00 	clr  %g1	! 0 <main>
 36c:	10 80 00 0b 	b  398 <llrec+0x50>
 370:	01 00 00 00 	nop 
 374:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 378:	40 00 00 00 	call  378 <llrec+0x30>
 37c:	01 00 00 00 	nop 
 380:	82 10 00 08 	mov  %o0, %g1
 384:	90 10 00 01 	mov  %g1, %o0
 388:	40 00 00 00 	call  388 <llrec+0x40>
 38c:	01 00 00 00 	nop 
 390:	82 10 00 08 	mov  %o0, %g1
 394:	82 00 60 01 	inc  %g1
 398:	b0 10 00 01 	mov  %g1, %i0
 39c:	81 e8 00 00 	restore 
 3a0:	81 c3 e0 08 	retl 
 3a4:	01 00 00 00 	nop 
