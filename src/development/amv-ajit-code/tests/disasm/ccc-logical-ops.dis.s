
/home/gauri/NEW/ajit-toolchain//development/amv-ajit-code/tests/obj/ccc-logical-ops.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	82 10 40 22 	ord  %g1, %g2, %g1
   8:	82 90 40 22 	ordcc  %g1, %g2, %g1
   c:	82 30 40 22 	ordn  %g1, %g2, %g1
  10:	82 b0 40 22 	ordncc  %g1, %g2, %g1
  14:	82 18 40 22 	xord  %g1, %g2, %g1
  18:	82 98 40 22 	xordcc  %g1, %g2, %g1
  1c:	82 38 40 22 	xnord  %g1, %g2, %g1
  20:	82 b8 40 22 	xnordcc  %g1, %g2, %g1
  24:	82 08 40 22 	andd  %g1, %g2, %g1
  28:	82 88 40 22 	anddcc  %g1, %g2, %g1
  2c:	82 28 40 22 	anddn  %g1, %g2, %g1
  30:	82 a8 40 22 	anddncc  %g1, %g2, %g1
  34:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  38:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  3c:	c0 27 bf fc 	clr  [ %fp + -4 ]
  40:	82 10 20 01 	mov  1, %g1
  44:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  48:	c0 27 bf f4 	clr  [ %fp + -12 ]
  4c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  50:	80 a0 60 01 	cmp  %g1, 1
  54:	04 80 00 60 	ble  1d4 <main+0x1d4>
  58:	01 00 00 00 	nop 
  5c:	10 80 00 19 	b  c0 <main+0xc0>
  60:	01 00 00 00 	nop 
  64:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  68:	83 28 60 02 	sll  %g1, 2, %g1
  6c:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  70:	82 00 80 01 	add  %g2, %g1, %g1
  74:	c2 00 40 00 	ld  [ %g1 ], %g1
  78:	90 10 00 01 	mov  %g1, %o0
  7c:	40 00 00 00 	call  7c <main+0x7c>
  80:	01 00 00 00 	nop 
  84:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  88:	03 00 00 00 	sethi  %hi(0), %g1
  8c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  90:	c2 00 40 00 	ld  [ %g1 ], %g1
  94:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  98:	92 10 00 01 	mov  %g1, %o1
  9c:	40 00 00 00 	call  9c <main+0x9c>
  a0:	01 00 00 00 	nop 
  a4:	84 10 00 08 	mov  %o0, %g2
  a8:	03 00 00 00 	sethi  %hi(0), %g1
  ac:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  b0:	c4 20 40 00 	st  %g2, [ %g1 ]
  b4:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  b8:	82 00 60 01 	inc  %g1
  bc:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  c0:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  c4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  c8:	80 a0 80 01 	cmp  %g2, %g1
  cc:	06 bf ff e6 	bl  64 <main+0x64>
  d0:	01 00 00 00 	nop 
  d4:	03 00 00 00 	sethi  %hi(0), %g1
  d8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  dc:	c2 00 40 00 	ld  [ %g1 ], %g1
  e0:	90 10 00 01 	mov  %g1, %o0
  e4:	40 00 00 00 	call  e4 <main+0xe4>
  e8:	01 00 00 00 	nop 
  ec:	84 10 00 08 	mov  %o0, %g2
  f0:	03 00 00 00 	sethi  %hi(0), %g1
  f4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  f8:	c4 20 40 00 	st  %g2, [ %g1 ]
  fc:	03 00 00 00 	sethi  %hi(0), %g1
 100:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 104:	c2 00 40 00 	ld  [ %g1 ], %g1
 108:	05 00 00 00 	sethi  %hi(0), %g2
 10c:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 110:	92 10 00 01 	mov  %g1, %o1
 114:	40 00 00 00 	call  114 <main+0x114>
 118:	01 00 00 00 	nop 
 11c:	03 00 00 00 	sethi  %hi(0), %g1
 120:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 124:	c2 00 40 00 	ld  [ %g1 ], %g1
 128:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 12c:	10 80 00 1b 	b  198 <main+0x198>
 130:	01 00 00 00 	nop 
 134:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 138:	40 00 00 00 	call  138 <main+0x138>
 13c:	01 00 00 00 	nop 
 140:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 144:	03 00 00 00 	sethi  %hi(0), %g1
 148:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 14c:	c2 00 40 00 	ld  [ %g1 ], %g1
 150:	82 00 60 01 	inc  %g1
 154:	05 00 00 00 	sethi  %hi(0), %g2
 158:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 15c:	92 10 00 01 	mov  %g1, %o1
 160:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 164:	40 00 00 00 	call  164 <main+0x164>
 168:	01 00 00 00 	nop 
 16c:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 170:	40 00 00 00 	call  170 <main+0x170>
 174:	01 00 00 00 	nop 
 178:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 17c:	03 00 00 00 	sethi  %hi(0), %g1
 180:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 184:	c2 00 40 00 	ld  [ %g1 ], %g1
 188:	84 00 60 01 	add  %g1, 1, %g2
 18c:	03 00 00 00 	sethi  %hi(0), %g1
 190:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 194:	c4 20 40 00 	st  %g2, [ %g1 ]
 198:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 19c:	80 a0 60 00 	cmp  %g1, 0
 1a0:	02 80 00 0f 	be  1dc <main+0x1dc>
 1a4:	01 00 00 00 	nop 
 1a8:	03 00 00 00 	sethi  %hi(0), %g1
 1ac:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1b0:	c4 00 40 00 	ld  [ %g1 ], %g2
 1b4:	03 00 00 00 	sethi  %hi(0), %g1
 1b8:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1bc:	c2 00 40 00 	ld  [ %g1 ], %g1
 1c0:	80 a0 80 01 	cmp  %g2, %g1
 1c4:	06 bf ff dc 	bl  134 <main+0x134>
 1c8:	01 00 00 00 	nop 
 1cc:	10 80 00 04 	b  1dc <main+0x1dc>
 1d0:	01 00 00 00 	nop 
 1d4:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffccb>
 1d8:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1dc:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1e0:	b0 10 00 01 	mov  %g1, %i0
 1e4:	81 e8 00 00 	restore 
 1e8:	81 c3 e0 08 	retl 
 1ec:	01 00 00 00 	nop 

000001f0 <cons>:
 1f0:	9d e3 bf 98 	save  %sp, -104, %sp
 1f4:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1f8:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 1fc:	c0 27 bf fc 	clr  [ %fp + -4 ]
 200:	90 10 20 01 	mov  1, %o0
 204:	92 10 20 08 	mov  8, %o1
 208:	40 00 00 00 	call  208 <cons+0x18>
 20c:	01 00 00 00 	nop 
 210:	82 10 00 08 	mov  %o0, %g1
 214:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 218:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 21c:	80 a0 60 00 	cmp  %g1, 0
 220:	02 80 00 0a 	be  248 <cons+0x58>
 224:	01 00 00 00 	nop 
 228:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 22c:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 230:	c4 20 40 00 	st  %g2, [ %g1 ]
 234:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 238:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 23c:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 240:	10 80 00 03 	b  24c <cons+0x5c>
 244:	01 00 00 00 	nop 
 248:	c0 27 bf fc 	clr  [ %fp + -4 ]
 24c:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 250:	b0 10 00 01 	mov  %g1, %i0
 254:	81 e8 00 00 	restore 
 258:	81 c3 e0 08 	retl 
 25c:	01 00 00 00 	nop 

00000260 <car>:
 260:	9d e3 bf a0 	save  %sp, -96, %sp
 264:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 268:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 26c:	80 a0 60 00 	cmp  %g1, 0
 270:	02 80 00 06 	be  288 <car+0x28>
 274:	01 00 00 00 	nop 
 278:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 27c:	c2 00 40 00 	ld  [ %g1 ], %g1
 280:	10 80 00 03 	b  28c <car+0x2c>
 284:	01 00 00 00 	nop 
 288:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffccb>
 28c:	b0 10 00 01 	mov  %g1, %i0
 290:	81 e8 00 00 	restore 
 294:	81 c3 e0 08 	retl 
 298:	01 00 00 00 	nop 

0000029c <cdr>:
 29c:	9d e3 bf a0 	save  %sp, -96, %sp
 2a0:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2a4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2a8:	80 a0 60 00 	cmp  %g1, 0
 2ac:	02 80 00 06 	be  2c4 <cdr+0x28>
 2b0:	01 00 00 00 	nop 
 2b4:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2b8:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2bc:	10 80 00 03 	b  2c8 <cdr+0x2c>
 2c0:	01 00 00 00 	nop 
 2c4:	82 10 20 00 	clr  %g1	! 0 <main>
 2c8:	b0 10 00 01 	mov  %g1, %i0
 2cc:	81 e8 00 00 	restore 
 2d0:	81 c3 e0 08 	retl 
 2d4:	01 00 00 00 	nop 

000002d8 <ll>:
 2d8:	9d e3 bf 98 	save  %sp, -104, %sp
 2dc:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2e0:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2e4:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2e8:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2ec:	10 80 00 09 	b  310 <ll+0x38>
 2f0:	01 00 00 00 	nop 
 2f4:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 2f8:	82 00 60 01 	inc  %g1
 2fc:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 300:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 304:	40 00 00 00 	call  304 <ll+0x2c>
 308:	01 00 00 00 	nop 
 30c:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 310:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 314:	80 a0 60 00 	cmp  %g1, 0
 318:	12 bf ff f7 	bne  2f4 <ll+0x1c>
 31c:	01 00 00 00 	nop 
 320:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 324:	b0 10 00 01 	mov  %g1, %i0
 328:	81 e8 00 00 	restore 
 32c:	81 c3 e0 08 	retl 
 330:	01 00 00 00 	nop 

00000334 <llrec>:
 334:	9d e3 bf 98 	save  %sp, -104, %sp
 338:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 33c:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 340:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 344:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 348:	80 a0 60 00 	cmp  %g1, 0
 34c:	12 80 00 05 	bne  360 <llrec+0x2c>
 350:	01 00 00 00 	nop 
 354:	82 10 20 00 	clr  %g1	! 0 <main>
 358:	10 80 00 0b 	b  384 <llrec+0x50>
 35c:	01 00 00 00 	nop 
 360:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 364:	40 00 00 00 	call  364 <llrec+0x30>
 368:	01 00 00 00 	nop 
 36c:	82 10 00 08 	mov  %o0, %g1
 370:	90 10 00 01 	mov  %g1, %o0
 374:	40 00 00 00 	call  374 <llrec+0x40>
 378:	01 00 00 00 	nop 
 37c:	82 10 00 08 	mov  %o0, %g1
 380:	82 00 60 01 	inc  %g1
 384:	b0 10 00 01 	mov  %g1, %i0
 388:	81 e8 00 00 	restore 
 38c:	81 c3 e0 08 	retl 
 390:	01 00 00 00 	nop 
