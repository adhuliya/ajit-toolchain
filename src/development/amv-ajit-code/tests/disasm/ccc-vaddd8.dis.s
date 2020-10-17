
/home/gauri/ajit-toolchain//development/amv-ajit-code/tests/obj/ccc-vaddd8.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	9d e3 bf 88 	save  %sp, -120, %sp
   4:	82 00 40 c2 	vaddd8  %g1, %g2, %g1
   8:	82 20 40 c2 	vsubd8  %g1, %g2, %g1
   c:	82 50 40 c2 	vumuld8  %g1, %g2, %g1
  10:	82 d0 40 c2 	vsmuld8  %g1, %g2, %g1
  14:	82 80 40 22 	adddcc  %g1, %g2, %g1
  18:	82 20 40 22 	subd  %g1, %g2, %g1
  1c:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  20:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
  24:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
  28:	c0 27 bf fc 	clr  [ %fp + -4 ]
  2c:	82 10 20 01 	mov  1, %g1
  30:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  34:	c0 27 bf f4 	clr  [ %fp + -12 ]
  38:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  3c:	80 a0 60 01 	cmp  %g1, 1
  40:	04 80 00 60 	ble  1c0 <main+0x1c0>
  44:	01 00 00 00 	nop 
  48:	10 80 00 19 	b  ac <main+0xac>
  4c:	01 00 00 00 	nop 
  50:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  54:	83 28 60 02 	sll  %g1, 2, %g1
  58:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
  5c:	82 00 80 01 	add  %g2, %g1, %g1
  60:	c2 00 40 00 	ld  [ %g1 ], %g1
  64:	90 10 00 01 	mov  %g1, %o0
  68:	40 00 00 00 	call  68 <main+0x68>
  6c:	01 00 00 00 	nop 
  70:	d0 27 bf f0 	st  %o0, [ %fp + -16 ]
  74:	03 00 00 00 	sethi  %hi(0), %g1
  78:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  7c:	c2 00 40 00 	ld  [ %g1 ], %g1
  80:	d0 07 bf f0 	ld  [ %fp + -16 ], %o0
  84:	92 10 00 01 	mov  %g1, %o1
  88:	40 00 00 00 	call  88 <main+0x88>
  8c:	01 00 00 00 	nop 
  90:	84 10 00 08 	mov  %o0, %g2
  94:	03 00 00 00 	sethi  %hi(0), %g1
  98:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  9c:	c4 20 40 00 	st  %g2, [ %g1 ]
  a0:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
  a4:	82 00 60 01 	inc  %g1
  a8:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
  ac:	c4 07 bf f8 	ld  [ %fp + -8 ], %g2
  b0:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
  b4:	80 a0 80 01 	cmp  %g2, %g1
  b8:	06 bf ff e6 	bl  50 <main+0x50>
  bc:	01 00 00 00 	nop 
  c0:	03 00 00 00 	sethi  %hi(0), %g1
  c4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  c8:	c2 00 40 00 	ld  [ %g1 ], %g1
  cc:	90 10 00 01 	mov  %g1, %o0
  d0:	40 00 00 00 	call  d0 <main+0xd0>
  d4:	01 00 00 00 	nop 
  d8:	84 10 00 08 	mov  %o0, %g2
  dc:	03 00 00 00 	sethi  %hi(0), %g1
  e0:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  e4:	c4 20 40 00 	st  %g2, [ %g1 ]
  e8:	03 00 00 00 	sethi  %hi(0), %g1
  ec:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
  f0:	c2 00 40 00 	ld  [ %g1 ], %g1
  f4:	05 00 00 00 	sethi  %hi(0), %g2
  f8:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
  fc:	92 10 00 01 	mov  %g1, %o1
 100:	40 00 00 00 	call  100 <main+0x100>
 104:	01 00 00 00 	nop 
 108:	03 00 00 00 	sethi  %hi(0), %g1
 10c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 110:	c2 00 40 00 	ld  [ %g1 ], %g1
 114:	c2 27 bf f4 	st  %g1, [ %fp + -12 ]
 118:	10 80 00 1b 	b  184 <main+0x184>
 11c:	01 00 00 00 	nop 
 120:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 124:	40 00 00 00 	call  124 <main+0x124>
 128:	01 00 00 00 	nop 
 12c:	d0 27 bf ec 	st  %o0, [ %fp + -20 ]
 130:	03 00 00 00 	sethi  %hi(0), %g1
 134:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 138:	c2 00 40 00 	ld  [ %g1 ], %g1
 13c:	82 00 60 01 	inc  %g1
 140:	05 00 00 00 	sethi  %hi(0), %g2
 144:	90 10 a0 00 	mov  %g2, %o0	! 0 <main>
 148:	92 10 00 01 	mov  %g1, %o1
 14c:	d4 07 bf ec 	ld  [ %fp + -20 ], %o2
 150:	40 00 00 00 	call  150 <main+0x150>
 154:	01 00 00 00 	nop 
 158:	d0 07 bf f4 	ld  [ %fp + -12 ], %o0
 15c:	40 00 00 00 	call  15c <main+0x15c>
 160:	01 00 00 00 	nop 
 164:	d0 27 bf f4 	st  %o0, [ %fp + -12 ]
 168:	03 00 00 00 	sethi  %hi(0), %g1
 16c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 170:	c2 00 40 00 	ld  [ %g1 ], %g1
 174:	84 00 60 01 	add  %g1, 1, %g2
 178:	03 00 00 00 	sethi  %hi(0), %g1
 17c:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 180:	c4 20 40 00 	st  %g2, [ %g1 ]
 184:	c2 07 bf f4 	ld  [ %fp + -12 ], %g1
 188:	80 a0 60 00 	cmp  %g1, 0
 18c:	02 80 00 0f 	be  1c8 <main+0x1c8>
 190:	01 00 00 00 	nop 
 194:	03 00 00 00 	sethi  %hi(0), %g1
 198:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 19c:	c4 00 40 00 	ld  [ %g1 ], %g2
 1a0:	03 00 00 00 	sethi  %hi(0), %g1
 1a4:	82 10 60 00 	mov  %g1, %g1	! 0 <main>
 1a8:	c2 00 40 00 	ld  [ %g1 ], %g1
 1ac:	80 a0 80 01 	cmp  %g2, %g1
 1b0:	06 bf ff dc 	bl  120 <main+0x120>
 1b4:	01 00 00 00 	nop 
 1b8:	10 80 00 04 	b  1c8 <main+0x1c8>
 1bc:	01 00 00 00 	nop 
 1c0:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcdf>
 1c4:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 1c8:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 1cc:	b0 10 00 01 	mov  %g1, %i0
 1d0:	81 e8 00 00 	restore 
 1d4:	81 c3 e0 08 	retl 
 1d8:	01 00 00 00 	nop 

000001dc <cons>:
 1dc:	9d e3 bf 98 	save  %sp, -104, %sp
 1e0:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 1e4:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
 1e8:	c0 27 bf fc 	clr  [ %fp + -4 ]
 1ec:	90 10 20 01 	mov  1, %o0
 1f0:	92 10 20 08 	mov  8, %o1
 1f4:	40 00 00 00 	call  1f4 <cons+0x18>
 1f8:	01 00 00 00 	nop 
 1fc:	82 10 00 08 	mov  %o0, %g1
 200:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 204:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 208:	80 a0 60 00 	cmp  %g1, 0
 20c:	02 80 00 0a 	be  234 <cons+0x58>
 210:	01 00 00 00 	nop 
 214:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 218:	c4 07 a0 44 	ld  [ %fp + 0x44 ], %g2
 21c:	c4 20 40 00 	st  %g2, [ %g1 ]
 220:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 224:	c4 07 a0 48 	ld  [ %fp + 0x48 ], %g2
 228:	c4 20 60 04 	st  %g2, [ %g1 + 4 ]
 22c:	10 80 00 03 	b  238 <cons+0x5c>
 230:	01 00 00 00 	nop 
 234:	c0 27 bf fc 	clr  [ %fp + -4 ]
 238:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 23c:	b0 10 00 01 	mov  %g1, %i0
 240:	81 e8 00 00 	restore 
 244:	81 c3 e0 08 	retl 
 248:	01 00 00 00 	nop 

0000024c <car>:
 24c:	9d e3 bf a0 	save  %sp, -96, %sp
 250:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 254:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 258:	80 a0 60 00 	cmp  %g1, 0
 25c:	02 80 00 06 	be  274 <car+0x28>
 260:	01 00 00 00 	nop 
 264:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 268:	c2 00 40 00 	ld  [ %g1 ], %g1
 26c:	10 80 00 03 	b  278 <car+0x2c>
 270:	01 00 00 00 	nop 
 274:	82 10 3f ff 	mov  -1, %g1	! ffffffff <llrec+0xfffffcdf>
 278:	b0 10 00 01 	mov  %g1, %i0
 27c:	81 e8 00 00 	restore 
 280:	81 c3 e0 08 	retl 
 284:	01 00 00 00 	nop 

00000288 <cdr>:
 288:	9d e3 bf a0 	save  %sp, -96, %sp
 28c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 290:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 294:	80 a0 60 00 	cmp  %g1, 0
 298:	02 80 00 06 	be  2b0 <cdr+0x28>
 29c:	01 00 00 00 	nop 
 2a0:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2a4:	c2 00 60 04 	ld  [ %g1 + 4 ], %g1
 2a8:	10 80 00 03 	b  2b4 <cdr+0x2c>
 2ac:	01 00 00 00 	nop 
 2b0:	82 10 20 00 	clr  %g1	! 0 <main>
 2b4:	b0 10 00 01 	mov  %g1, %i0
 2b8:	81 e8 00 00 	restore 
 2bc:	81 c3 e0 08 	retl 
 2c0:	01 00 00 00 	nop 

000002c4 <ll>:
 2c4:	9d e3 bf 98 	save  %sp, -104, %sp
 2c8:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 2cc:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 2d0:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 2d4:	c0 27 bf f8 	clr  [ %fp + -8 ]
 2d8:	10 80 00 09 	b  2fc <ll+0x38>
 2dc:	01 00 00 00 	nop 
 2e0:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 2e4:	82 00 60 01 	inc  %g1
 2e8:	c2 27 bf f8 	st  %g1, [ %fp + -8 ]
 2ec:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 2f0:	40 00 00 00 	call  2f0 <ll+0x2c>
 2f4:	01 00 00 00 	nop 
 2f8:	d0 27 bf fc 	st  %o0, [ %fp + -4 ]
 2fc:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 300:	80 a0 60 00 	cmp  %g1, 0
 304:	12 bf ff f7 	bne  2e0 <ll+0x1c>
 308:	01 00 00 00 	nop 
 30c:	c2 07 bf f8 	ld  [ %fp + -8 ], %g1
 310:	b0 10 00 01 	mov  %g1, %i0
 314:	81 e8 00 00 	restore 
 318:	81 c3 e0 08 	retl 
 31c:	01 00 00 00 	nop 

00000320 <llrec>:
 320:	9d e3 bf 98 	save  %sp, -104, %sp
 324:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
 328:	c2 07 a0 44 	ld  [ %fp + 0x44 ], %g1
 32c:	c2 27 bf fc 	st  %g1, [ %fp + -4 ]
 330:	c2 07 bf fc 	ld  [ %fp + -4 ], %g1
 334:	80 a0 60 00 	cmp  %g1, 0
 338:	12 80 00 05 	bne  34c <llrec+0x2c>
 33c:	01 00 00 00 	nop 
 340:	82 10 20 00 	clr  %g1	! 0 <main>
 344:	10 80 00 0b 	b  370 <llrec+0x50>
 348:	01 00 00 00 	nop 
 34c:	d0 07 bf fc 	ld  [ %fp + -4 ], %o0
 350:	40 00 00 00 	call  350 <llrec+0x30>
 354:	01 00 00 00 	nop 
 358:	82 10 00 08 	mov  %o0, %g1
 35c:	90 10 00 01 	mov  %g1, %o0
 360:	40 00 00 00 	call  360 <llrec+0x40>
 364:	01 00 00 00 	nop 
 368:	82 10 00 08 	mov  %o0, %g1
 36c:	82 00 60 01 	inc  %g1
 370:	b0 10 00 01 	mov  %g1, %i0
 374:	81 e8 00 00 	restore 
 378:	81 c3 e0 08 	retl 
 37c:	01 00 00 00 	nop 
