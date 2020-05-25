
/home/codeman/.itsoflife/mydata/local/packages-live/ajit-toolchain/development/amv-ajit-code/tests/obj/ccc-simd-2.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	89 68 80 01 	addbyter  %g2, %g1, %g4
   8:	89 70 80 01 	ordbyter  %g2, %g1, %g4
   c:	89 78 80 01 	anddbyter  %g2, %g1, %g4
  10:	89 f0 80 01 	xordbyter  %g2, %g1, %g4
  14:	89 f8 80 01 	zbytedpos  %g2, %g1, %g4
  18:	89 f8 a0 ff 	zbytedpos  %g2, 0xff, %g4
  1c:	82 80 40 22 	adddcc  %g1, %g2, %g1
  20:	82 20 40 22 	subd  %g1, %g2, %g1
  24:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  28:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  2c:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  30:	c0 27 bf fc 	clr  [ %fp + -4 ]
  34:	82 10 20 01 	mov  1, %g1
  38:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  3c:	c0 27 bf f4 	clr  [ %fp + -12 ]
  40:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  44:	80 a0 60 01 	cmp  %g1, 1
  48:	04 80 00 60 	ble  1c8 <main+0x1c8>
  4c:	01 00 00 00 	nop 
  50:	10 80 00 19 	b  b4 <main+0xb4>
  54:	01 00 00 00 	nop 
  58:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  5c:	83 28 60 02 	sll  %g1, 2, %g1
  60:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  64:	82 00 80 01 	add  %g2, %g1, %g1
  68:	c2 00 40 00 	ld  [ %g1 ], %g1
  6c:	90 10 00 01 	mov  %g1, %o0
  70:	40 00 00 00 	call  70 <main+0x70>
  74:	01 00 00 00 	nop 
  78:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  7c:	03 00 00 00 	sethi  %hi(0), %g1
  80:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  84:	c2 00 40 00 	ld  [ %g1 ], %g1
  88:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  8c:	92 10 00 01 	mov  %g1, %o1
  90:	40 00 00 00 	call  90 <main+0x90>
  94:	01 00 00 00 	nop 
  98:	84 10 00 08 	mov  %o0, %g2
  9c:	03 00 00 00 	sethi  %hi(0), %g1
  a0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  a4:	c4 20 40 00 	st  %g2, [ %g1 ]
  a8:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  ac:	82 00 60 01 	inc  %g1
  b0:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  b4:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  b8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  bc:	80 a0 80 01 	cmp  %g2, %g1
  c0:	06 bf ff e6 	bl  58 <main+0x58>
  c4:	01 00 00 00 	nop 
  c8:	03 00 00 00 	sethi  %hi(0), %g1
  cc:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  d0:	c2 00 40 00 	ld  [ %g1 ], %g1
  d4:	90 10 00 01 	mov  %g1, %o0
  d8:	40 00 00 00 	call  d8 <main+0xd8>
  dc:	01 00 00 00 	nop 
  e0:	84 10 00 08 	mov  %o0, %g2
  e4:	03 00 00 00 	sethi  %hi(0), %g1
  e8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  ec:	c4 20 40 00 	st  %g2, [ %g1 ]
  f0:	03 00 00 00 	sethi  %hi(0), %g1
  f4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  f8:	c2 00 40 00 	ld  [ %g1 ], %g1
  fc:	05 00 00 00 	sethi  %hi(0), %g2
 100:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 104:	92 10 00 01 	mov  %g1, %o1
 108:	40 00 00 00 	call  108 <main+0x108>
 10c:	01 00 00 00 	nop 
 110:	03 00 00 00 	sethi  %hi(0), %g1
 114:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 118:	c2 00 40 00 	ld  [ %g1 ], %g1
 11c:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 120:	10 80 00 1b 	b  18c <main+0x18c>
 124:	01 00 00 00 	nop 
 128:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 12c:	40 00 00 00 	call  12c <main+0x12c>
 130:	01 00 00 00 	nop 
 134:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 138:	03 00 00 00 	sethi  %hi(0), %g1
 13c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 140:	c2 00 40 00 	ld  [ %g1 ], %g1
 144:	82 00 60 01 	inc  %g1
 148:	05 00 00 00 	sethi  %hi(0), %g2
 14c:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 150:	92 10 00 01 	mov  %g1, %o1
 154:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 158:	40 00 00 00 	call  158 <main+0x158>
 15c:	01 00 00 00 	nop 
 160:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 164:	40 00 00 00 	call  164 <main+0x164>
 168:	01 00 00 00 	nop 
 16c:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 170:	03 00 00 00 	sethi  %hi(0), %g1
 174:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 178:	c2 00 40 00 	ld  [ %g1 ], %g1
 17c:	84 00 60 01 	add  %g1, 1, %g2
 180:	03 00 00 00 	sethi  %hi(0), %g1
 184:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 188:	c4 20 40 00 	st  %g2, [ %g1 ]
 18c:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 190:	80 a0 60 00 	cmp  %g1, 0
 194:	02 80 00 0f 	be  1d0 <main+0x1d0>
 198:	01 00 00 00 	nop 
 19c:	03 00 00 00 	sethi  %hi(0), %g1
 1a0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1a4:	c4 00 40 00 	ld  [ %g1 ], %g2
 1a8:	03 00 00 00 	sethi  %hi(0), %g1
 1ac:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1b0:	c2 00 40 00 	ld  [ %g1 ], %g1
 1b4:	80 a0 80 01 	cmp  %g2, %g1
 1b8:	06 bf ff dc 	bl  128 <main+0x128>
 1bc:	01 00 00 00 	nop 
 1c0:	10 80 00 04 	b  1d0 <main+0x1d0>
 1c4:	01 00 00 00 	nop 
 1c8:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcd7>
 1cc:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1d0:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1d4:	b0 10 00 01 	mov  %g1, %i0
 1d8:	81 e8 00 00 	restore 
 1dc:	81 c3 e0 08 	retl 
 1e0:	01 00 00 00 	nop 

000001e4 <cons>:
 1e4:	9d e3 bf 98 	save  %sp, -104, %sp
 1e8:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1ec:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 1f0:	c0 27 bf fc 	clr  [ %fp + -4 ]
 1f4:	90 10 20 01 	mov  1, %o0
 1f8:	92 10 20 08 	mov  8, %o1
 1fc:	40 00 00 00 	call  1fc <cons+0x18>
 200:	01 00 00 00 	nop 
 204:	82 10 00 08 	mov  %o0, %g1
 208:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 20c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 210:	80 a0 60 00 	cmp  %g1, 0
 214:	02 80 00 0a 	be  23c <cons+0x58>
 218:	01 00 00 00 	nop 
 21c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 220:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 224:	c4 20 40 00 	st  %g2, [ %g1 ]
 228:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 22c:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 230:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 234:	10 80 00 03 	b  240 <cons+0x5c>
 238:	01 00 00 00 	nop 
 23c:	c0 27 bf fc 	clr  [ %fp + -4 ]
 240:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 244:	b0 10 00 01 	mov  %g1, %i0
 248:	81 e8 00 00 	restore 
 24c:	81 c3 e0 08 	retl 
 250:	01 00 00 00 	nop 

00000254 <car>:
 254:	9d e3 bf a0 	save  %sp, -96, %sp
 258:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 25c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 260:	80 a0 60 00 	cmp  %g1, 0
 264:	02 80 00 06 	be  27c <car+0x28>
 268:	01 00 00 00 	nop 
 26c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 270:	c2 00 40 00 	ld  [ %g1 ], %g1
 274:	10 80 00 03 	b  280 <car+0x2c>
 278:	01 00 00 00 	nop 
 27c:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcd7>
 280:	b0 10 00 01 	mov  %g1, %i0
 284:	81 e8 00 00 	restore 
 288:	81 c3 e0 08 	retl 
 28c:	01 00 00 00 	nop 

00000290 <cdr>:
 290:	9d e3 bf a0 	save  %sp, -96, %sp
 294:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 298:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 29c:	80 a0 60 00 	cmp  %g1, 0
 2a0:	02 80 00 06 	be  2b8 <cdr+0x28>
 2a4:	01 00 00 00 	nop 
 2a8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2ac:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2b0:	10 80 00 03 	b  2bc <cdr+0x2c>
 2b4:	01 00 00 00 	nop 
 2b8:	82 10 20 00 	clr  %g1	! 0 <main>
 2bc:	b0 10 00 01 	mov  %g1, %i0
 2c0:	81 e8 00 00 	restore 
 2c4:	81 c3 e0 08 	retl 
 2c8:	01 00 00 00 	nop 

000002cc <ll>:
 2cc:	9d e3 bf 98 	save  %sp, -104, %sp
 2d0:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2d4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2d8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2dc:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2e0:	10 80 00 09 	b  304 <ll+0x38>
 2e4:	01 00 00 00 	nop 
 2e8:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 2ec:	82 00 60 01 	inc  %g1
 2f0:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 2f4:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 2f8:	40 00 00 00 	call  2f8 <ll+0x2c>
 2fc:	01 00 00 00 	nop 
 300:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 304:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 308:	80 a0 60 00 	cmp  %g1, 0
 30c:	12 bf ff f7 	bne  2e8 <ll+0x1c>
 310:	01 00 00 00 	nop 
 314:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 318:	b0 10 00 01 	mov  %g1, %i0
 31c:	81 e8 00 00 	restore 
 320:	81 c3 e0 08 	retl 
 324:	01 00 00 00 	nop 

00000328 <llrec>:
 328:	9d e3 bf 98 	save  %sp, -104, %sp
 32c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 330:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 334:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 338:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 33c:	80 a0 60 00 	cmp  %g1, 0
 340:	12 80 00 05 	bne  354 <llrec+0x2c>
 344:	01 00 00 00 	nop 
 348:	82 10 20 00 	clr  %g1	! 0 <main>
 34c:	10 80 00 0b 	b  378 <llrec+0x50>
 350:	01 00 00 00 	nop 
 354:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 358:	40 00 00 00 	call  358 <llrec+0x30>
 35c:	01 00 00 00 	nop 
 360:	82 10 00 08 	mov  %o0, %g1
 364:	90 10 00 01 	mov  %g1, %o0
 368:	40 00 00 00 	call  368 <llrec+0x40>
 36c:	01 00 00 00 	nop 
 370:	82 10 00 08 	mov  %o0, %g1
 374:	82 00 60 01 	inc  %g1
 378:	b0 10 00 01 	mov  %g1, %i0
 37c:	81 e8 00 00 	restore 
 380:	81 c3 e0 08 	retl 
 384:	01 00 00 00 	nop 
