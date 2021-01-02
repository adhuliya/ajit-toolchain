
/lindata/My-work/Professional/iitb/tests/obj/only-ajit.o:     file format elf32-sparc


Disassembly of section .text:

00000000 <main>:
   0:	82 80 40 22 	adddcc  %g1, %g2, %g1
   4:	84 80 80 24 	adddcc  %g2, %g4, %g2
   8:	82 00 40 22 	addd  %g1, %g2, %g1
   c:	84 00 80 24 	addd  %g2, %g4, %g2
  10:	89 68 81 01 	adddreduce16  %g2, %g1, %g4
  14:	89 68 80 81 	adddreduce8  %g2, %g1, %g4
  18:	82 88 40 22 	anddcc  %g1, %g2, %g1
  1c:	82 08 40 22 	andd  %g1, %g2, %g1
  20:	82 a8 40 22 	anddncc  %g1, %g2, %g1
  24:	82 28 40 22 	anddn  %g1, %g2, %g1
  28:	89 78 81 01 	anddreduce16  %g2, %g1, %g4
  2c:	89 78 80 81 	anddreduce8  %g2, %g1, %g4
  30:	c9 f8 af ff 	cswapa  [ %g2 + 0xfff ], %g4
  34:	c9 f8 81 41 	cswapa  [ %g2 + %g1 ] (10), %g4
  38:	c9 7f bf f8 	cswap  [ %fp + -8 ], %g4
  3c:	c9 78 af ff 	cswap  [ %g2 + 0xfff ], %g4
  40:	c9 78 81 01 	cswap  [ %g2 + %g1 ] (8), %g4
  44:	89 a0 aa 00 	faddreduce16  %f2, %f4
  48:	87 a0 6a 40 	fhtos  %f1, %f3
  4c:	87 a0 6a 20 	fstoh  %f1, %f3
  50:	82 90 40 22 	ordcc  %g1, %g2, %g1
  54:	82 10 40 22 	ord  %g1, %g2, %g1
  58:	82 b0 40 22 	ordncc  %g1, %g2, %g1
  5c:	82 30 40 22 	ordn  %g1, %g2, %g1
  60:	89 70 81 01 	ordreduce16  %g2, %g1, %g4
  64:	89 70 80 81 	ordreduce8  %g2, %g1, %g4
  68:	9d e3 bf 88 	save  %sp, -120, %sp
  6c:	82 f8 40 22 	sdivdcc  %g1, %g2, %g1
  70:	82 78 40 22 	sdivd  %g1, %g2, %g1
  74:	85 28 60 98 	slld  %g1, 0x18, %g2
  78:	85 28 40 83 	slld  %g1, %g3, %g2
  7c:	a5 28 a0 82 	slld  %g2, 2, %l2
  80:	a5 28 80 84 	slld  %g2, %g4, %l2
  84:	80 d8 40 22 	smuldcc  %g1, %g2, %g0
  88:	80 58 40 22 	smuld  %g1, %g2, %g0
  8c:	80 58 40 02 	smul  %g1, %g2, %g0
  90:	85 38 60 98 	srad  %g1, 0x18, %g2
  94:	85 38 40 83 	srad  %g1, %g3, %g2
  98:	a1 38 a0 82 	srad  %g2, 2, %l0
  9c:	a1 38 80 84 	srad  %g2, %g4, %l0
  a0:	85 30 60 98 	srld  %g1, 0x18, %g2
  a4:	85 30 40 83 	srld  %g1, %g3, %g2
  a8:	8d 30 a0 82 	srld  %g2, 2, %g6
  ac:	8d 30 80 84 	srld  %g2, %g4, %g6
  b0:	82 a0 40 22 	subdcc  %g1, %g2, %g1
  b4:	84 a0 80 24 	subdcc  %g2, %g4, %g2
  b8:	82 20 40 22 	subd  %g1, %g2, %g1
  bc:	84 20 80 24 	subd  %g2, %g4, %g2
  c0:	8c f0 40 22 	udivdcc  %g1, %g2, %g6
  c4:	82 70 40 22 	udivd  %g1, %g2, %g1
  c8:	84 70 40 22 	udivd  %g1, %g2, %g2
  cc:	86 70 40 22 	udivd  %g1, %g2, %g3
  d0:	88 70 40 22 	udivd  %g1, %g2, %g4
  d4:	8a 70 40 22 	udivd  %g1, %g2, %g5
  d8:	8c 70 40 22 	udivd  %g1, %g2, %g6
  dc:	84 70 80 24 	udivd  %g2, %g4, %g2
  e0:	80 d0 40 22 	umuldcc  %g1, %g2, %g0
  e4:	80 50 40 22 	umuld  %g1, %g2, %g0
  e8:	80 50 40 02 	umul  %g1, %g2, %g0
  ec:	82 00 41 42 	vaddd16  %g1, %g2, %g1
  f0:	8c 00 81 44 	vaddd16  %g2, %g4, %g6
  f4:	82 00 42 42 	vaddd32  %g1, %g2, %g1
  f8:	8c 00 82 44 	vaddd32  %g2, %g4, %g6
  fc:	82 00 40 c2 	vaddd8  %g1, %g2, %g1
 100:	8c 00 80 c4 	vaddd8  %g2, %g4, %g6
 104:	8d a0 a8 64 	vfadd16  %f2, %f4, %f6
 108:	8d a0 a8 44 	vfadd32  %f2, %f4, %f6
 10c:	8d a0 a8 e4 	vfmul16  %f2, %f4, %f6
 110:	8d a0 a8 c4 	vfmul32  %f2, %f4, %f6
 114:	8d a0 a8 a4 	vfsub16  %f2, %f4, %f6
 118:	8d a0 a8 84 	vfsub32  %f2, %f4, %f6
 11c:	82 58 41 42 	vsmuld16  %g1, %g2, %g1
 120:	8c 58 81 44 	vsmuld16  %g2, %g4, %g6
 124:	82 58 42 42 	vsmuld32  %g1, %g2, %g1
 128:	8c 58 82 44 	vsmuld32  %g2, %g4, %g6
 12c:	82 58 40 c2 	vsmuld8  %g1, %g2, %g1
 130:	8c 58 80 c4 	vsmuld8  %g2, %g4, %g6
 134:	82 20 41 42 	vsubd16  %g1, %g2, %g1
 138:	8c 20 81 44 	vsubd16  %g2, %g4, %g6
 13c:	82 20 42 42 	vsubd32  %g1, %g2, %g1
 140:	8c 20 82 44 	vsubd32  %g2, %g4, %g6
 144:	82 20 40 c2 	vsubd8  %g1, %g2, %g1
 148:	8c 20 80 c4 	vsubd8  %g2, %g4, %g6
 14c:	82 50 41 42 	vumuld16  %g1, %g2, %g1
 150:	8c 50 81 44 	vumuld16  %g2, %g4, %g6
 154:	82 50 42 42 	vumuld32  %g1, %g2, %g1
 158:	8c 50 82 44 	vumuld32  %g2, %g4, %g6
 15c:	82 50 40 c2 	vumuld8  %g1, %g2, %g1
 160:	8c 50 80 c4 	vumuld8  %g2, %g4, %g6
 164:	82 b8 40 22 	xnordcc  %g1, %g2, %g1
 168:	82 38 40 22 	xnord  %g1, %g2, %g1
 16c:	82 98 40 22 	xordcc  %g1, %g2, %g1
 170:	89 f0 81 01 	xordreduce16  %g2, %g1, %g4
 174:	89 f0 80 81 	xordreduce8  %g2, %g1, %g4
 178:	89 f8 a0 ff 	zbytedpos  %g2, 0xff, %g4
 17c:	89 f8 80 01 	zbytedpos  %g2, %g1, %g4
 180:	01 00 00 00 	nop 
