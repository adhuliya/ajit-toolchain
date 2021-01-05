
/lindata/My-work/Professional/iitb/tests/obj/ccc-umuld.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	82 00 40 22 	addd  %g1, %g2, %g1
   8:	82 80 40 22 	adddcc  %g1, %g2, %g1
   c:	82 20 40 22 	subd  %g1, %g2, %g1
  10:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  14:	80 58 40 02 	smul  %g1, %g2, %g0
  18:	80 58 40 22 	smuld  %g1, %g2, %g0
  1c:	80 50 40 02 	umul  %g1, %g2, %g0
  20:	80 50 40 22 	umuld  %g1, %g2, %g0
  24:	80 d0 40 22 	umuldcc  %g1, %g2, %g0
  28:	80 58 40 22 	smuld  %g1, %g2, %g0
  2c:	80 d8 40 22 	smuldcc  %g1, %g2, %g0
  30:	82 70 40 22 	udivd  %g1, %g2, %g1
  34:	84 70 40 22 	udivd  %g1, %g2, %g2
  38:	86 70 40 22 	udivd  %g1, %g2, %g3
  3c:	88 70 40 22 	udivd  %g1, %g2, %g4
  40:	8a 70 40 22 	udivd  %g1, %g2, %g5
  44:	8c 70 40 22 	udivd  %g1, %g2, %g6
  48:	82 78 40 22 	sdivd  %g1, %g2, %g1
  4c:	8c f0 40 22 	udivdcc  %g1, %g2, %g6
  50:	82 f8 40 22 	sdivdcc  %g1, %g2, %g1
  54:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  58:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  5c:	c0 27 bf fc 	clr  [ %fp + -4 ]
  60:	82 10 20 01 	mov  1, %g1
  64:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  68:	c0 27 bf f4 	clr  [ %fp + -12 ]
  6c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  70:	80 a0 60 01 	cmp  %g1, 1
  74:	04 80 00 60 	ble  1f4 <main+0x1f4>
  78:	01 00 00 00 	nop 
  7c:	10 80 00 19 	b  e0 <main+0xe0>
  80:	01 00 00 00 	nop 
  84:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  88:	83 28 60 02 	sll  %g1, 2, %g1
  8c:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  90:	82 00 80 01 	add  %g2, %g1, %g1
  94:	c2 00 40 00 	ld  [ %g1 ], %g1
  98:	90 10 00 01 	mov  %g1, %o0
  9c:	40 00 00 00 	call  9c <main+0x9c>
  a0:	01 00 00 00 	nop 
  a4:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  a8:	03 00 00 00 	sethi  %hi(0), %g1
  ac:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  b0:	c2 00 40 00 	ld  [ %g1 ], %g1
  b4:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  b8:	92 10 00 01 	mov  %g1, %o1
  bc:	40 00 00 00 	call  bc <main+0xbc>
  c0:	01 00 00 00 	nop 
  c4:	84 10 00 08 	mov  %o0, %g2
  c8:	03 00 00 00 	sethi  %hi(0), %g1
  cc:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  d0:	c4 20 40 00 	st  %g2, [ %g1 ]
  d4:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  d8:	82 00 60 01 	inc  %g1
  dc:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  e0:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  e4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  e8:	80 a0 80 01 	cmp  %g2, %g1
  ec:	06 bf ff e6 	bl  84 <main+0x84>
  f0:	01 00 00 00 	nop 
  f4:	03 00 00 00 	sethi  %hi(0), %g1
  f8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  fc:	c2 00 40 00 	ld  [ %g1 ], %g1
 100:	90 10 00 01 	mov  %g1, %o0
 104:	40 00 00 00 	call  104 <main+0x104>
 108:	01 00 00 00 	nop 
 10c:	84 10 00 08 	mov  %o0, %g2
 110:	03 00 00 00 	sethi  %hi(0), %g1
 114:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 118:	c4 20 40 00 	st  %g2, [ %g1 ]
 11c:	03 00 00 00 	sethi  %hi(0), %g1
 120:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 124:	c2 00 40 00 	ld  [ %g1 ], %g1
 128:	05 00 00 00 	sethi  %hi(0), %g2
 12c:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 130:	92 10 00 01 	mov  %g1, %o1
 134:	40 00 00 00 	call  134 <main+0x134>
 138:	01 00 00 00 	nop 
 13c:	03 00 00 00 	sethi  %hi(0), %g1
 140:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 144:	c2 00 40 00 	ld  [ %g1 ], %g1
 148:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 14c:	10 80 00 1b 	b  1b8 <main+0x1b8>
 150:	01 00 00 00 	nop 
 154:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 158:	40 00 00 00 	call  158 <main+0x158>
 15c:	01 00 00 00 	nop 
 160:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 164:	03 00 00 00 	sethi  %hi(0), %g1
 168:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 16c:	c2 00 40 00 	ld  [ %g1 ], %g1
 170:	82 00 60 01 	inc  %g1
 174:	05 00 00 00 	sethi  %hi(0), %g2
 178:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 17c:	92 10 00 01 	mov  %g1, %o1
 180:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 184:	40 00 00 00 	call  184 <main+0x184>
 188:	01 00 00 00 	nop 
 18c:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 190:	40 00 00 00 	call  190 <main+0x190>
 194:	01 00 00 00 	nop 
 198:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 19c:	03 00 00 00 	sethi  %hi(0), %g1
 1a0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1a4:	c2 00 40 00 	ld  [ %g1 ], %g1
 1a8:	84 00 60 01 	add  %g1, 1, %g2
 1ac:	03 00 00 00 	sethi  %hi(0), %g1
 1b0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1b4:	c4 20 40 00 	st  %g2, [ %g1 ]
 1b8:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 1bc:	80 a0 60 00 	cmp  %g1, 0
 1c0:	02 80 00 0f 	be  1fc <main+0x1fc>
 1c4:	01 00 00 00 	nop 
 1c8:	03 00 00 00 	sethi  %hi(0), %g1
 1cc:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1d0:	c4 00 40 00 	ld  [ %g1 ], %g2
 1d4:	03 00 00 00 	sethi  %hi(0), %g1
 1d8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1dc:	c2 00 40 00 	ld  [ %g1 ], %g1
 1e0:	80 a0 80 01 	cmp  %g2, %g1
 1e4:	06 bf ff dc 	bl  154 <main+0x154>
 1e8:	01 00 00 00 	nop 
 1ec:	10 80 00 04 	b  1fc <main+0x1fc>
 1f0:	01 00 00 00 	nop 
 1f4:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcab>
 1f8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1fc:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 200:	b0 10 00 01 	mov  %g1, %i0
 204:	81 e8 00 00 	restore 
 208:	81 c3 e0 08 	retl 
 20c:	01 00 00 00 	nop 

00000210 <cons>:
 210:	9d e3 bf 98 	save  %sp, -104, %sp
 214:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 218:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 21c:	c0 27 bf fc 	clr  [ %fp + -4 ]
 220:	90 10 20 01 	mov  1, %o0
 224:	92 10 20 08 	mov  8, %o1
 228:	40 00 00 00 	call  228 <cons+0x18>
 22c:	01 00 00 00 	nop 
 230:	82 10 00 08 	mov  %o0, %g1
 234:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 238:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 23c:	80 a0 60 00 	cmp  %g1, 0
 240:	02 80 00 0a 	be  268 <cons+0x58>
 244:	01 00 00 00 	nop 
 248:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 24c:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 250:	c4 20 40 00 	st  %g2, [ %g1 ]
 254:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 258:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 25c:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 260:	10 80 00 03 	b  26c <cons+0x5c>
 264:	01 00 00 00 	nop 
 268:	c0 27 bf fc 	clr  [ %fp + -4 ]
 26c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 270:	b0 10 00 01 	mov  %g1, %i0
 274:	81 e8 00 00 	restore 
 278:	81 c3 e0 08 	retl 
 27c:	01 00 00 00 	nop 

00000280 <car>:
 280:	9d e3 bf a0 	save  %sp, -96, %sp
 284:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 288:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 28c:	80 a0 60 00 	cmp  %g1, 0
 290:	02 80 00 06 	be  2a8 <car+0x28>
 294:	01 00 00 00 	nop 
 298:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 29c:	c2 00 40 00 	ld  [ %g1 ], %g1
 2a0:	10 80 00 03 	b  2ac <car+0x2c>
 2a4:	01 00 00 00 	nop 
 2a8:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcab>
 2ac:	b0 10 00 01 	mov  %g1, %i0
 2b0:	81 e8 00 00 	restore 
 2b4:	81 c3 e0 08 	retl 
 2b8:	01 00 00 00 	nop 

000002bc <cdr>:
 2bc:	9d e3 bf a0 	save  %sp, -96, %sp
 2c0:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2c4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2c8:	80 a0 60 00 	cmp  %g1, 0
 2cc:	02 80 00 06 	be  2e4 <cdr+0x28>
 2d0:	01 00 00 00 	nop 
 2d4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2d8:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2dc:	10 80 00 03 	b  2e8 <cdr+0x2c>
 2e0:	01 00 00 00 	nop 
 2e4:	82 10 20 00 	clr  %g1	! 0 <main>
 2e8:	b0 10 00 01 	mov  %g1, %i0
 2ec:	81 e8 00 00 	restore 
 2f0:	81 c3 e0 08 	retl 
 2f4:	01 00 00 00 	nop 

000002f8 <ll>:
 2f8:	9d e3 bf 98 	save  %sp, -104, %sp
 2fc:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 300:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 304:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 308:	c0 27 bf f8 	clr  [ %fp + -8 ]
 30c:	10 80 00 09 	b  330 <ll+0x38>
 310:	01 00 00 00 	nop 
 314:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 318:	82 00 60 01 	inc  %g1
 31c:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 320:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 324:	40 00 00 00 	call  324 <ll+0x2c>
 328:	01 00 00 00 	nop 
 32c:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 330:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 334:	80 a0 60 00 	cmp  %g1, 0
 338:	12 bf ff f7 	bne  314 <ll+0x1c>
 33c:	01 00 00 00 	nop 
 340:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 344:	b0 10 00 01 	mov  %g1, %i0
 348:	81 e8 00 00 	restore 
 34c:	81 c3 e0 08 	retl 
 350:	01 00 00 00 	nop 

00000354 <llrec>:
 354:	9d e3 bf 98 	save  %sp, -104, %sp
 358:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 35c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 360:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 364:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 368:	80 a0 60 00 	cmp  %g1, 0
 36c:	12 80 00 05 	bne  380 <llrec+0x2c>
 370:	01 00 00 00 	nop 
 374:	82 10 20 00 	clr  %g1	! 0 <main>
 378:	10 80 00 0b 	b  3a4 <llrec+0x50>
 37c:	01 00 00 00 	nop 
 380:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 384:	40 00 00 00 	call  384 <llrec+0x30>
 388:	01 00 00 00 	nop 
 38c:	82 10 00 08 	mov  %o0, %g1
 390:	90 10 00 01 	mov  %g1, %o0
 394:	40 00 00 00 	call  394 <llrec+0x40>
 398:	01 00 00 00 	nop 
 39c:	82 10 00 08 	mov  %o0, %g1
 3a0:	82 00 60 01 	inc  %g1
 3a4:	b0 10 00 01 	mov  %g1, %i0
 3a8:	81 e8 00 00 	restore 
 3ac:	81 c3 e0 08 	retl 
 3b0:	01 00 00 00 	nop 
