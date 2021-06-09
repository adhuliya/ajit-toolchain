
/lindata/My-work/Professional/iitb/tests/obj/add-arith-insns.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	84 00 80 24 	addd  %g2, %g4, %g2
   8:	84 80 80 24 	adddcc  %g2, %g4, %g2
   c:	84 20 80 24 	subd  %g2, %g4, %g2
  10:	84 a0 80 24 	subdcc  %g2, %g4, %g2
  14:	84 70 80 24 	udivd  %g2, %g4, %g2
  18:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  1c:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  20:	c0 27 bf fc 	clr  [ %fp + -4 ]
  24:	82 10 20 01 	mov  1, %g1
  28:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  2c:	c0 27 bf f4 	clr  [ %fp + -12 ]
  30:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  34:	80 a0 60 01 	cmp  %g1, 1
  38:	04 80 00 60 	ble  1b8 <main+0x1b8>
  3c:	01 00 00 00 	nop 
  40:	10 80 00 19 	b  a4 <main+0xa4>
  44:	01 00 00 00 	nop 
  48:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  4c:	83 28 60 02 	sll  %g1, 2, %g1
  50:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  54:	82 00 80 01 	add  %g2, %g1, %g1
  58:	c2 00 40 00 	ld  [ %g1 ], %g1
  5c:	90 10 00 01 	mov  %g1, %o0
  60:	40 00 00 00 	call  60 <main+0x60>
  64:	01 00 00 00 	nop 
  68:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  6c:	03 00 00 00 	sethi  %hi(0), %g1
  70:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  74:	c2 00 40 00 	ld  [ %g1 ], %g1
  78:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  7c:	92 10 00 01 	mov  %g1, %o1
  80:	40 00 00 00 	call  80 <main+0x80>
  84:	01 00 00 00 	nop 
  88:	84 10 00 08 	mov  %o0, %g2
  8c:	03 00 00 00 	sethi  %hi(0), %g1
  90:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  94:	c4 20 40 00 	st  %g2, [ %g1 ]
  98:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  9c:	82 00 60 01 	inc  %g1
  a0:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  a4:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  a8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  ac:	80 a0 80 01 	cmp  %g2, %g1
  b0:	06 bf ff e6 	bl  48 <main+0x48>
  b4:	01 00 00 00 	nop 
  b8:	03 00 00 00 	sethi  %hi(0), %g1
  bc:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  c0:	c2 00 40 00 	ld  [ %g1 ], %g1
  c4:	90 10 00 01 	mov  %g1, %o0
  c8:	40 00 00 00 	call  c8 <main+0xc8>
  cc:	01 00 00 00 	nop 
  d0:	84 10 00 08 	mov  %o0, %g2
  d4:	03 00 00 00 	sethi  %hi(0), %g1
  d8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  dc:	c4 20 40 00 	st  %g2, [ %g1 ]
  e0:	03 00 00 00 	sethi  %hi(0), %g1
  e4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  e8:	c2 00 40 00 	ld  [ %g1 ], %g1
  ec:	05 00 00 00 	sethi  %hi(0), %g2
  f0:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
  f4:	92 10 00 01 	mov  %g1, %o1
  f8:	40 00 00 00 	call  f8 <main+0xf8>
  fc:	01 00 00 00 	nop 
 100:	03 00 00 00 	sethi  %hi(0), %g1
 104:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 108:	c2 00 40 00 	ld  [ %g1 ], %g1
 10c:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 110:	10 80 00 1b 	b  17c <main+0x17c>
 114:	01 00 00 00 	nop 
 118:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 11c:	40 00 00 00 	call  11c <main+0x11c>
 120:	01 00 00 00 	nop 
 124:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 128:	03 00 00 00 	sethi  %hi(0), %g1
 12c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 130:	c2 00 40 00 	ld  [ %g1 ], %g1
 134:	82 00 60 01 	inc  %g1
 138:	05 00 00 00 	sethi  %hi(0), %g2
 13c:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 140:	92 10 00 01 	mov  %g1, %o1
 144:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 148:	40 00 00 00 	call  148 <main+0x148>
 14c:	01 00 00 00 	nop 
 150:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 154:	40 00 00 00 	call  154 <main+0x154>
 158:	01 00 00 00 	nop 
 15c:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 160:	03 00 00 00 	sethi  %hi(0), %g1
 164:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 168:	c2 00 40 00 	ld  [ %g1 ], %g1
 16c:	84 00 60 01 	add  %g1, 1, %g2
 170:	03 00 00 00 	sethi  %hi(0), %g1
 174:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 178:	c4 20 40 00 	st  %g2, [ %g1 ]
 17c:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 180:	80 a0 60 00 	cmp  %g1, 0
 184:	02 80 00 0f 	be  1c0 <main+0x1c0>
 188:	01 00 00 00 	nop 
 18c:	03 00 00 00 	sethi  %hi(0), %g1
 190:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 194:	c4 00 40 00 	ld  [ %g1 ], %g2
 198:	03 00 00 00 	sethi  %hi(0), %g1
 19c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1a0:	c2 00 40 00 	ld  [ %g1 ], %g1
 1a4:	80 a0 80 01 	cmp  %g2, %g1
 1a8:	06 bf ff dc 	bl  118 <main+0x118>
 1ac:	01 00 00 00 	nop 
 1b0:	10 80 00 04 	b  1c0 <main+0x1c0>
 1b4:	01 00 00 00 	nop 
 1b8:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffce7>
 1bc:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1c0:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1c4:	b0 10 00 01 	mov  %g1, %i0
 1c8:	81 e8 00 00 	restore 
 1cc:	81 c3 e0 08 	retl 
 1d0:	01 00 00 00 	nop 

000001d4 <cons>:
 1d4:	9d e3 bf 98 	save  %sp, -104, %sp
 1d8:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1dc:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 1e0:	c0 27 bf fc 	clr  [ %fp + -4 ]
 1e4:	90 10 20 01 	mov  1, %o0
 1e8:	92 10 20 08 	mov  8, %o1
 1ec:	40 00 00 00 	call  1ec <cons+0x18>
 1f0:	01 00 00 00 	nop 
 1f4:	82 10 00 08 	mov  %o0, %g1
 1f8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1fc:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 200:	80 a0 60 00 	cmp  %g1, 0
 204:	02 80 00 0a 	be  22c <cons+0x58>
 208:	01 00 00 00 	nop 
 20c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 210:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 214:	c4 20 40 00 	st  %g2, [ %g1 ]
 218:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 21c:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 220:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 224:	10 80 00 03 	b  230 <cons+0x5c>
 228:	01 00 00 00 	nop 
 22c:	c0 27 bf fc 	clr  [ %fp + -4 ]
 230:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 234:	b0 10 00 01 	mov  %g1, %i0
 238:	81 e8 00 00 	restore 
 23c:	81 c3 e0 08 	retl 
 240:	01 00 00 00 	nop 

00000244 <car>:
 244:	9d e3 bf a0 	save  %sp, -96, %sp
 248:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 24c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 250:	80 a0 60 00 	cmp  %g1, 0
 254:	02 80 00 06 	be  26c <car+0x28>
 258:	01 00 00 00 	nop 
 25c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 260:	c2 00 40 00 	ld  [ %g1 ], %g1
 264:	10 80 00 03 	b  270 <car+0x2c>
 268:	01 00 00 00 	nop 
 26c:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffce7>
 270:	b0 10 00 01 	mov  %g1, %i0
 274:	81 e8 00 00 	restore 
 278:	81 c3 e0 08 	retl 
 27c:	01 00 00 00 	nop 

00000280 <cdr>:
 280:	9d e3 bf a0 	save  %sp, -96, %sp
 284:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 288:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 28c:	80 a0 60 00 	cmp  %g1, 0
 290:	02 80 00 06 	be  2a8 <cdr+0x28>
 294:	01 00 00 00 	nop 
 298:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 29c:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2a0:	10 80 00 03 	b  2ac <cdr+0x2c>
 2a4:	01 00 00 00 	nop 
 2a8:	82 10 20 00 	clr  %g1	! 0 <main>
 2ac:	b0 10 00 01 	mov  %g1, %i0
 2b0:	81 e8 00 00 	restore 
 2b4:	81 c3 e0 08 	retl 
 2b8:	01 00 00 00 	nop 

000002bc <ll>:
 2bc:	9d e3 bf 98 	save  %sp, -104, %sp
 2c0:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2c4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2c8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2cc:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2d0:	10 80 00 09 	b  2f4 <ll+0x38>
 2d4:	01 00 00 00 	nop 
 2d8:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 2dc:	82 00 60 01 	inc  %g1
 2e0:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 2e4:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 2e8:	40 00 00 00 	call  2e8 <ll+0x2c>
 2ec:	01 00 00 00 	nop 
 2f0:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 2f4:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 2f8:	80 a0 60 00 	cmp  %g1, 0
 2fc:	12 bf ff f7 	bne  2d8 <ll+0x1c>
 300:	01 00 00 00 	nop 
 304:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 308:	b0 10 00 01 	mov  %g1, %i0
 30c:	81 e8 00 00 	restore 
 310:	81 c3 e0 08 	retl 
 314:	01 00 00 00 	nop 

00000318 <llrec>:
 318:	9d e3 bf 98 	save  %sp, -104, %sp
 31c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 320:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 324:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 328:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 32c:	80 a0 60 00 	cmp  %g1, 0
 330:	12 80 00 05 	bne  344 <llrec+0x2c>
 334:	01 00 00 00 	nop 
 338:	82 10 20 00 	clr  %g1	! 0 <main>
 33c:	10 80 00 0b 	b  368 <llrec+0x50>
 340:	01 00 00 00 	nop 
 344:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 348:	40 00 00 00 	call  348 <llrec+0x30>
 34c:	01 00 00 00 	nop 
 350:	82 10 00 08 	mov  %o0, %g1
 354:	90 10 00 01 	mov  %g1, %o0
 358:	40 00 00 00 	call  358 <llrec+0x40>
 35c:	01 00 00 00 	nop 
 360:	82 10 00 08 	mov  %o0, %g1
 364:	82 00 60 01 	inc  %g1
 368:	b0 10 00 01 	mov  %g1, %i0
 36c:	81 e8 00 00 	restore 
 370:	81 c3 e0 08 	retl 
 374:	01 00 00 00 	nop 
