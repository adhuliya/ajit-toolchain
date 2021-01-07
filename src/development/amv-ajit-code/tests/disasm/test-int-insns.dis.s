
/lindata/My-work/Professional/iitb/tests/obj/test-int-insns.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	82 00 40 22 	addd  %g1, %g2, %g1
   8:	82 80 40 22 	adddcc  %g1, %g2, %g1
   c:	82 20 40 22 	subd  %g1, %g2, %g1
  10:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  14:	85 28 60 98 	slld  %g1, 0x18, %g2
  18:	85 30 60 98 	srld  %g1, 0x18, %g2
  1c:	85 38 60 98 	srad  %g1, 0x18, %g2
  20:	85 28 40 83 	slld  %g1, %g3, %g2
  24:	85 30 40 83 	srld  %g1, %g3, %g2
  28:	85 38 40 83 	srad  %g1, %g3, %g2
  2c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  30:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  34:	c0 27 bf fc 	clr  [ %fp + -4 ]
  38:	82 10 20 01 	mov  1, %g1
  3c:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  40:	c0 27 bf f4 	clr  [ %fp + -12 ]
  44:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  48:	80 a0 60 01 	cmp  %g1, 1
  4c:	04 80 00 60 	ble  1cc <main+0x1cc>
  50:	01 00 00 00 	nop 
  54:	10 80 00 19 	b  b8 <main+0xb8>
  58:	01 00 00 00 	nop 
  5c:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  60:	83 28 60 02 	sll  %g1, 2, %g1
  64:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  68:	82 00 80 01 	add  %g2, %g1, %g1
  6c:	c2 00 40 00 	ld  [ %g1 ], %g1
  70:	90 10 00 01 	mov  %g1, %o0
  74:	40 00 00 00 	call  74 <main+0x74>
  78:	01 00 00 00 	nop 
  7c:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  80:	03 00 00 00 	sethi  %hi(0), %g1
  84:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  88:	c2 00 40 00 	ld  [ %g1 ], %g1
  8c:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  90:	92 10 00 01 	mov  %g1, %o1
  94:	40 00 00 00 	call  94 <main+0x94>
  98:	01 00 00 00 	nop 
  9c:	84 10 00 08 	mov  %o0, %g2
  a0:	03 00 00 00 	sethi  %hi(0), %g1
  a4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  a8:	c4 20 40 00 	st  %g2, [ %g1 ]
  ac:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  b0:	82 00 60 01 	inc  %g1
  b4:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  b8:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  bc:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  c0:	80 a0 80 01 	cmp  %g2, %g1
  c4:	06 bf ff e6 	bl  5c <main+0x5c>
  c8:	01 00 00 00 	nop 
  cc:	03 00 00 00 	sethi  %hi(0), %g1
  d0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  d4:	c2 00 40 00 	ld  [ %g1 ], %g1
  d8:	90 10 00 01 	mov  %g1, %o0
  dc:	40 00 00 00 	call  dc <main+0xdc>
  e0:	01 00 00 00 	nop 
  e4:	84 10 00 08 	mov  %o0, %g2
  e8:	03 00 00 00 	sethi  %hi(0), %g1
  ec:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  f0:	c4 20 40 00 	st  %g2, [ %g1 ]
  f4:	03 00 00 00 	sethi  %hi(0), %g1
  f8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  fc:	c2 00 40 00 	ld  [ %g1 ], %g1
 100:	05 00 00 00 	sethi  %hi(0), %g2
 104:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 108:	92 10 00 01 	mov  %g1, %o1
 10c:	40 00 00 00 	call  10c <main+0x10c>
 110:	01 00 00 00 	nop 
 114:	03 00 00 00 	sethi  %hi(0), %g1
 118:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 11c:	c2 00 40 00 	ld  [ %g1 ], %g1
 120:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 124:	10 80 00 1b 	b  190 <main+0x190>
 128:	01 00 00 00 	nop 
 12c:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 130:	40 00 00 00 	call  130 <main+0x130>
 134:	01 00 00 00 	nop 
 138:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 13c:	03 00 00 00 	sethi  %hi(0), %g1
 140:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 144:	c2 00 40 00 	ld  [ %g1 ], %g1
 148:	82 00 60 01 	inc  %g1
 14c:	05 00 00 00 	sethi  %hi(0), %g2
 150:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 154:	92 10 00 01 	mov  %g1, %o1
 158:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 15c:	40 00 00 00 	call  15c <main+0x15c>
 160:	01 00 00 00 	nop 
 164:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 168:	40 00 00 00 	call  168 <main+0x168>
 16c:	01 00 00 00 	nop 
 170:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 174:	03 00 00 00 	sethi  %hi(0), %g1
 178:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 17c:	c2 00 40 00 	ld  [ %g1 ], %g1
 180:	84 00 60 01 	add  %g1, 1, %g2
 184:	03 00 00 00 	sethi  %hi(0), %g1
 188:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 18c:	c4 20 40 00 	st  %g2, [ %g1 ]
 190:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 194:	80 a0 60 00 	cmp  %g1, 0
 198:	02 80 00 0f 	be  1d4 <main+0x1d4>
 19c:	01 00 00 00 	nop 
 1a0:	03 00 00 00 	sethi  %hi(0), %g1
 1a4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1a8:	c4 00 40 00 	ld  [ %g1 ], %g2
 1ac:	03 00 00 00 	sethi  %hi(0), %g1
 1b0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1b4:	c2 00 40 00 	ld  [ %g1 ], %g1
 1b8:	80 a0 80 01 	cmp  %g2, %g1
 1bc:	06 bf ff dc 	bl  12c <main+0x12c>
 1c0:	01 00 00 00 	nop 
 1c4:	10 80 00 04 	b  1d4 <main+0x1d4>
 1c8:	01 00 00 00 	nop 
 1cc:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcd3>
 1d0:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1d4:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1d8:	b0 10 00 01 	mov  %g1, %i0
 1dc:	81 e8 00 00 	restore 
 1e0:	81 c3 e0 08 	retl 
 1e4:	01 00 00 00 	nop 

000001e8 <cons>:
 1e8:	9d e3 bf 98 	save  %sp, -104, %sp
 1ec:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1f0:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 1f4:	c0 27 bf fc 	clr  [ %fp + -4 ]
 1f8:	90 10 20 01 	mov  1, %o0
 1fc:	92 10 20 08 	mov  8, %o1
 200:	40 00 00 00 	call  200 <cons+0x18>
 204:	01 00 00 00 	nop 
 208:	82 10 00 08 	mov  %o0, %g1
 20c:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 210:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 214:	80 a0 60 00 	cmp  %g1, 0
 218:	02 80 00 0a 	be  240 <cons+0x58>
 21c:	01 00 00 00 	nop 
 220:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 224:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 228:	c4 20 40 00 	st  %g2, [ %g1 ]
 22c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 230:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 234:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 238:	10 80 00 03 	b  244 <cons+0x5c>
 23c:	01 00 00 00 	nop 
 240:	c0 27 bf fc 	clr  [ %fp + -4 ]
 244:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 248:	b0 10 00 01 	mov  %g1, %i0
 24c:	81 e8 00 00 	restore 
 250:	81 c3 e0 08 	retl 
 254:	01 00 00 00 	nop 

00000258 <car>:
 258:	9d e3 bf a0 	save  %sp, -96, %sp
 25c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 260:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 264:	80 a0 60 00 	cmp  %g1, 0
 268:	02 80 00 06 	be  280 <car+0x28>
 26c:	01 00 00 00 	nop 
 270:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 274:	c2 00 40 00 	ld  [ %g1 ], %g1
 278:	10 80 00 03 	b  284 <car+0x2c>
 27c:	01 00 00 00 	nop 
 280:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcd3>
 284:	b0 10 00 01 	mov  %g1, %i0
 288:	81 e8 00 00 	restore 
 28c:	81 c3 e0 08 	retl 
 290:	01 00 00 00 	nop 

00000294 <cdr>:
 294:	9d e3 bf a0 	save  %sp, -96, %sp
 298:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 29c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2a0:	80 a0 60 00 	cmp  %g1, 0
 2a4:	02 80 00 06 	be  2bc <cdr+0x28>
 2a8:	01 00 00 00 	nop 
 2ac:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2b0:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2b4:	10 80 00 03 	b  2c0 <cdr+0x2c>
 2b8:	01 00 00 00 	nop 
 2bc:	82 10 20 00 	clr  %g1	! 0 <main>
 2c0:	b0 10 00 01 	mov  %g1, %i0
 2c4:	81 e8 00 00 	restore 
 2c8:	81 c3 e0 08 	retl 
 2cc:	01 00 00 00 	nop 

000002d0 <ll>:
 2d0:	9d e3 bf 98 	save  %sp, -104, %sp
 2d4:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2d8:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2dc:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2e0:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2e4:	10 80 00 09 	b  308 <ll+0x38>
 2e8:	01 00 00 00 	nop 
 2ec:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 2f0:	82 00 60 01 	inc  %g1
 2f4:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 2f8:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 2fc:	40 00 00 00 	call  2fc <ll+0x2c>
 300:	01 00 00 00 	nop 
 304:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 308:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 30c:	80 a0 60 00 	cmp  %g1, 0
 310:	12 bf ff f7 	bne  2ec <ll+0x1c>
 314:	01 00 00 00 	nop 
 318:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 31c:	b0 10 00 01 	mov  %g1, %i0
 320:	81 e8 00 00 	restore 
 324:	81 c3 e0 08 	retl 
 328:	01 00 00 00 	nop 

0000032c <llrec>:
 32c:	9d e3 bf 98 	save  %sp, -104, %sp
 330:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 334:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 338:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 33c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 340:	80 a0 60 00 	cmp  %g1, 0
 344:	12 80 00 05 	bne  358 <llrec+0x2c>
 348:	01 00 00 00 	nop 
 34c:	82 10 20 00 	clr  %g1	! 0 <main>
 350:	10 80 00 0b 	b  37c <llrec+0x50>
 354:	01 00 00 00 	nop 
 358:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 35c:	40 00 00 00 	call  35c <llrec+0x30>
 360:	01 00 00 00 	nop 
 364:	82 10 00 08 	mov  %o0, %g1
 368:	90 10 00 01 	mov  %g1, %o0
 36c:	40 00 00 00 	call  36c <llrec+0x40>
 370:	01 00 00 00 	nop 
 374:	82 10 00 08 	mov  %o0, %g1
 378:	82 00 60 01 	inc  %g1
 37c:	b0 10 00 01 	mov  %g1, %i0
 380:	81 e8 00 00 	restore 
 384:	81 c3 e0 08 	retl 
 388:	01 00 00 00 	nop 
