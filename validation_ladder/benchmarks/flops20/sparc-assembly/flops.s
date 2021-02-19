	.file	"flops.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.asciz	"\n"
	.align 8
.LC2:
	.asciz	"   FLOPS C Program (Double Precision), V2.0 18 Dec 1992\n\n"
	.align 8
.LC11:
	.asciz	"   Module     Error        RunTime      MFLOPS\n"
	.align 8
.LC12:
	.asciz	"                            (usec)\n"
	.align 8
.LC18:
	.asciz	"     1   %13.8lf  %10.4lf  %10.4lf\n"
	.align 8
.LC21:
	.asciz	"     2   %13.8lf  %10.4lf  %10.4lf\n"
	.align 8
.LC24:
	.asciz	"     3   %13.8lf  %10.4lf  %10.4lf\n"
	.align 8
.LC25:
	.asciz	"     4   %13.8lf  %10.4lf  %10.4lf\n"
	.align 8
.LC28:
	.asciz	"     5   %13.8lf  %10.4lf  %10.4lf\n"
	.align 8
.LC30:
	.asciz	"     6   %13.8lf  %10.4lf  %10.4lf\n"
	.align 8
.LC35:
	.asciz	"     7   %13.8lf  %10.4lf  %10.4lf\n"
	.align 8
.LC38:
	.asciz	"     8   %13.8lf  %10.4lf  %10.4lf\n"
	.align 8
.LC43:
	.asciz	"   Iterations      = %10ld\n"
	.align 8
.LC44:
	.asciz	"   NullTime (usec) = %10.4lf\n"
	.align 8
.LC45:
	.asciz	"   MFLOPS(1)       = %10.4lf\n"
	.align 8
.LC46:
	.asciz	"   MFLOPS(2)       = %10.4lf\n"
	.align 8
.LC47:
	.asciz	"   MFLOPS(3)       = %10.4lf\n"
	.align 8
.LC48:
	.asciz	"   MFLOPS(4)       = %10.4lf\n\n"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	0
	.align 8
.LC3:
	.long	1078984704
	.long	0
	.align 8
.LC4:
	.long	1076756480
	.long	0
	.align 8
.LC5:
	.long	1074340347
	.long	1413754136
	.align 8
.LC6:
	.long	1072693248
	.long	0
	.align 8
.LC7:
	.long	1073741824
	.long	0
	.align 8
.LC8:
	.long	1074266112
	.long	0
	.align 8
.LC9:
	.long	1074790400
	.long	0
	.align 8
.LC10:
	.long	1075052544
	.long	0
	.align 8
.LC13:
	.long	1106247680
	.long	0
	.align 8
.LC14:
	.long	1053129102
	.long	3794832442
	.align 8
.LC15:
	.long	1093567616
	.long	0
	.align 8
.LC16:
	.long	1076625408
	.long	0
	.align 8
.LC17:
	.long	1077490483
	.long	858993459
	.align 8
.LC19:
	.long	1075576832
	.long	0
	.align 8
.LC20:
	.long	1077886976
	.long	0
	.align 8
.LC22:
	.long	1076953088
	.long	0
	.align 8
.LC23:
	.long	1071644672
	.long	0
	.align 8
.LC26:
	.long	1077739520
	.long	0
	.align 8
.LC27:
	.long	1072049730
	.long	4277811695
	.align 8
.LC29:
	.long	1070596096
	.long	0
	.align 8
.LC31:
	.long	1079612737
	.long	4159804068
	.align 8
.LC32:
	.long	1076363264
	.long	0
	.align 8
.LC33:
	.long	1077018624
	.long	0
	.align 8
.LC34:
	.long	1082082099
	.long	858993459
	.align 8
.LC36:
	.long	1077805056
	.long	0
	.align 8
.LC37:
	.long	1070770858
	.long	2863311531
	.align 8
.LC39:
	.long	1078591488
	.long	0
	.align 8
.LC40:
	.long	1080229888
	.long	0
	.align 8
.LC41:
	.long	1080180736
	.long	0
	.align 8
.LC42:
	.long	1079427072
	.long	0
	.section	".text"
	.align 4
	.global ajit_main
	.type	ajit_main, #function
	.proc	04
ajit_main:
	save	%sp, -264, %sp
	call	ajit_init, 0
	 sethi	%hi(T), %i5
	sethi	%hi(.LC1), %g1
	call	ee_printf, 0
	 or	%g1, %lo(.LC1), %o0
	sethi	%hi(.LC2), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC2), %o0
	sethi	%hi(TLimit), %g1
	sethi	%hi(.LC4), %g2
	ldd	[%g2+%lo(.LC4)], %f8
	std	%f8, [%g1+%lo(TLimit)]
	sethi	%hi(.LC3), %g1
	ldd	[%g1+%lo(.LC3)], %f0
	sethi	%hi(.LC5), %g1
	ldd	[%g1+%lo(.LC5)], %f2
	sethi	%hi(.LC6), %g1
	ldd	[%g1+%lo(.LC6)], %f4
	sethi	%hi(.LC7), %g1
	ldd	[%g1+%lo(.LC7)], %f10
	sethi	%hi(.LC8), %g1
	ldd	[%g1+%lo(.LC8)], %f6
	sethi	%hi(.LC9), %g1
	sethi	%hi(two), %g3
	ldd	[%g1+%lo(.LC9)], %f12
	sethi	%hi(three), %g4
	sethi	%hi(four), %o1
	sethi	%hi(.LC10), %g1
	sethi	%hi(.LC11), %o2
	ldd	[%g1+%lo(.LC10)], %f14
	std	%f10, [%g3+%lo(two)]
	std	%f6, [%g4+%lo(three)]
	std	%f12, [%o1+%lo(four)]
	or	%o2, %lo(.LC11), %o0
	sethi	%hi(piref), %l0
	or	%i5, %lo(T), %i5
	std	%f2, [%l0+%lo(piref)]
	std	%f0, [%i5+8]
	sethi	%hi(one), %i1
	sethi	%hi(five), %i2
	std	%f4, [%i1+%lo(one)]
	std	%f14, [%i2+%lo(five)]
	sethi	%hi(scale), %i3
	call	ee_printf, 0
	 std	%f4, [%i3+%lo(scale)]
	sethi	%hi(.LC12), %o3
	call	ee_printf, 0
	 or	%o3, %lo(.LC12), %o0
	call	barebones_clock, 0
	 nop
	st	%o0, [%fp-64]
	sethi	%hi(TimeArray), %o4
	ld	[%fp-64], %f1
	or	%o4, %lo(TimeArray), %l7
	fitod	%f1, %f20
	cmp	%o0, 0
	bl	.L67
	 ldd	[%l7+16], %f16
.L2:
	sethi	%hi(.LC14), %i4
	ldd	[%i4+%lo(.LC14)], %f22
	fmuld	%f20, %f22, %f24
	fsubd	%f24, %f16, %f26
	std	%f24, [%l7+16]
	call	barebones_clock, 0
	 std	%f26, [%l7+8]
	ldd	[%l7+16], %f28
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f3
	bl	.L68
	 fitod	%f3, %f8
.L3:
	sethi	%hi(sa), %i2
	ldd	[%i4+%lo(.LC14)], %f0
	sethi	%hi(.LC0), %i3
	fmuld	%f8, %f0, %f2
	sethi	%hi(15360), %o5
	ldd	[%i3+%lo(.LC0)], %f8
	fsubd	%f2, %f28, %f4
	fmovs	%f8, %f30
	sethi	%hi(TLimit), %l6
	std	%f2, [%l7+16]
	std	%f4, [%l7+8]
	st	%g0, [%i2+%lo(sa)]
	st	%g0, [%i2+%lo(sa+4)]
	mov	15, %i0
	or	%o5, 265, %l1
	fmovs	%f9, %f31
	fmovs	%f30, %f14
	fmovs	%f9, %f15
	sethi	%hi(D3), %l3
	sethi	%hi(D2), %l4
	sethi	%hi(D1), %l5
	sethi	%hi(E2), %l2
	or	%l6, %lo(TLimit), %l6
.L4:
	ldd	[%l6], %f10
	fcmped	%f10, %f8
	nop
	fbule	.L8
	 nop
	ldd	[%i1+%lo(one)], %f12
	add	%l1, %l1, %l1
	st	%l1, [%fp-64]
	ld	[%fp-64], %f5
	fitod	%f5, %f6
	fdivd	%f12, %f6, %f30
	std	%f12, [%fp-112]
	call	barebones_clock, 0
	 std	%f30, [%fp-144]
	ldd	[%l7+16], %f18
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f7
	ldd	[%fp-112], %f12
	fitod	%f7, %f16
	bl	.L69
	 ldd	[%fp-144], %f30
.L5:
	ldd	[%i3+%lo(.LC0)], %f10
	ldd	[%i4+%lo(.LC14)], %f20
	sethi	%hi(E3), %o7
	fmuld	%f16, %f20, %f22
	ldd	[%l3+%lo(D3)], %f28
	fsubd	%f22, %f18, %f24
	ldd	[%l4+%lo(D2)], %f26
	std	%f22, [%l7+16]
	std	%f24, [%l7+8]
	ldd	[%l5+%lo(D1)], %f0
	ldd	[%o7+%lo(E3)], %f2
	ldd	[%l2+%lo(E2)], %f4
	mov	1, %g1
	fmovs	%f10, %f14
	fmovs	%f11, %f15
.L6:
	faddd	%f10, %f12, %f10
	fmuld	%f10, %f30, %f8
	fmuld	%f8, %f28, %f6
	fmuld	%f8, %f2, %f16
	faddd	%f6, %f26, %f18
	faddd	%f16, %f4, %f20
	fmuld	%f18, %f8, %f22
	fmuld	%f20, %f8, %f24
	add	%g1, 1, %g1
	faddd	%f22, %f0, %f6
	faddd	%f24, %f0, %f16
	cmp	%g1, %l1
	fmuld	%f16, %f8, %f8
	faddd	%f12, %f8, %f18
	fdivd	%f6, %f18, %f20
	bne	.L6
	 faddd	%f14, %f20, %f14
	std	%f14, [%fp-120]
	call	barebones_clock, 0
	 std	%f30, [%fp-144]
	ldd	[%l7+16], %f28
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f9
	ldd	[%fp-120], %f14
	fitod	%f9, %f10
	bl	.L70
	 ldd	[%fp-144], %f30
.L7:
	ldd	[%i4+%lo(.LC14)], %f26
	fmuld	%f10, %f26, %f0
	fsubd	%f0, %f28, %f8
	std	%f0, [%l7+16]
	std	%f8, [%l7+8]
	addcc	%i0, -1, %i0
	bne	.L4
	 std	%f8, [%i2+%lo(sa)]
	sethi	%hi(512000000), %l1
.L8:
	st	%l1, [%fp-64]
	sethi	%hi(.LC15), %g1
	ld	[%fp-64], %f11
	ldd	[%g1+%lo(.LC15)], %f4
	fitod	%f11, %f2
	sethi	%hi(scale), %g1
	fdivd	%f4, %f2, %f22
	std	%f22, [%i5+8]
	std	%f14, [%fp-120]
	std	%f30, [%fp-144]
	call	barebones_clock, 0
	 std	%f22, [%g1+%lo(scale)]
	ldd	[%l7+16], %f24
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f13
	ldd	[%fp-120], %f14
	fitod	%f13, %f16
	bl	.L71
	 ldd	[%fp-144], %f30
.L10:
	ldd	[%i4+%lo(.LC14)], %f8
	fmuld	%f16, %f8, %f18
	std	%f18, [%l7+16]
	fsubd	%f18, %f24, %f20
	std	%f20, [%l7+8]
	std	%f14, [%fp-120]
	call	barebones_clock, 0
	 std	%f30, [%fp-144]
	ldd	[%l7+16], %f28
	st	%o0, [%fp-64]
	ld	[%fp-64], %f15
	cmp	%o0, 0
	fitod	%f15, %f10
	ldd	[%fp-144], %f30
	bl	.L72
	 ldd	[%fp-120], %f14
.L11:
	ldd	[%i4+%lo(.LC14)], %f26
	fmuld	%f10, %f26, %f0
	fsubd	%f0, %f28, %f2
	std	%f0, [%l7+16]
	std	%f2, [%l7+8]
	ldd	[%i5+8], %f4
	ldd	[%i3+%lo(.LC0)], %f8
	fmuld	%f4, %f2, %f10
	fcmped	%f10, %f8
	nop
	fbl	.L12
	 sethi	%hi(nulltime), %i0
	std	%f10, [%i0+%lo(nulltime)]
.L13:
	ldd	[%i2+%lo(sa)], %f22
	ldd	[%l4+%lo(D2)], %f16
	fmuld	%f4, %f22, %f24
	sethi	%hi(E3), %o0
	fsubd	%f24, %f10, %f28
	std	%f28, [%fp-152]
	ldd	[%l5+%lo(D1)], %f6
	ldd	[%i1+%lo(one)], %f8
	faddd	%f6, %f16, %f20
	faddd	%f6, %f8, %f10
	ldd	[%l2+%lo(E2)], %f0
	ldd	[%o0+%lo(E3)], %f2
	faddd	%f10, %f0, %f4
	ldd	[%fp-152], %o0
	faddd	%f4, %f2, %f22
	std	%f28, [%i5+16]
	ldd	[%l3+%lo(D3)], %f12
	sethi	%hi(two), %g1
	faddd	%f20, %f12, %f26
	fdivd	%f26, %f22, %f16
	ldd	[%g1+%lo(two)], %f18
	faddd	%f6, %f16, %f6
	fmuld	%f18, %f14, %f14
	sethi	%hi(.LC16), %g1
	faddd	%f6, %f14, %f20
	fmuld	%f20, %f30, %f30
	fdivd	%f30, %f18, %f12
	fdivd	%f8, %f12, %f10
	fdtoi	%f10, %f17
	st	%f17, [%fp-64]
	ldd	[%g1+%lo(.LC16)], %f18
	ld	[%fp-64], %g3
	fdivd	%f28, %f18, %f28
	sethi	%hi(sb), %g1
	fdivd	%f8, %f28, %f8
	st	%f8, [%fp-64]
	std	%f8, [%fp-8]
	ld	[%fp-64], %o5
	std	%f10, [%g1+%lo(sb)]
	std	%f28, [%i5+24]
	sethi	%hi(39936), %g1
	or	%g1, 64, %g1
	smul	%g3, %g1, %g1
	st	%g1, [%fp-64]
	sethi	%hi(.LC17), %g1
	ld	[%fp-64], %f19
	ldd	[%g1+%lo(.LC17)], %f0
	fitod	%f19, %f26
	fsubd	%f10, %f0, %f2
	sethi	%hi(scale), %g2
	std	%f2, [%fp-152]
	ldd	[%g2+%lo(scale)], %f24
	sethi	%hi(sc), %g1
	fdivd	%f26, %f24, %f4
	fdtoi	%f4, %f21
	st	%f21, [%fp-64]
	ldd	[%fp-152], %g2
	std	%f2, [%g1+%lo(sc)]
	sethi	%hi(.LC18), %g4
	ld	[%fp-64], %l2
	std	%f8, [%i5+32]
	ld	[%fp-4], %g1
	mov	%o0, %o3
	mov	%o1, %o4
	std	%f12, [%i2+%lo(sa)]
	mov	%g2, %o1
	mov	%g3, %o2
	st	%g1, [%sp+92]
	call	ee_printf, 0
	 or	%g4, %lo(.LC18), %o0
	sethi	%hi(five), %o1
	ldd	[%i1+%lo(one)], %f14
	ldd	[%o1+%lo(five)], %f8
	fnegs	%f14, %f14
	fnegs	%f8, %f8
	std	%f14, [%i2+%lo(sa)]
	call	barebones_clock, 0
	 std	%f8, [%fp-96]
	ldd	[%l7+16], %f22
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f25
	ldd	[%fp-96], %f8
	bl	.L73
	 fitod	%f25, %f16
.L14:
	ldd	[%i4+%lo(.LC14)], %f6
	fmuld	%f16, %f6, %f20
	fsubd	%f20, %f22, %f30
	std	%f20, [%l7+16]
	cmp	%l2, 0
	ble	.L49
	 std	%f30, [%l7+8]
	ldd	[%i2+%lo(sa)], %f12
	add	%l2, 1, %o2
	mov	1, %g1
.L16:
	fnegs	%f8, %f10
	fsubd	%f12, %f8, %f12
	add	%g1, 1, %g1
	fmovs	%f9, %f11
	cmp	%g1, %o2
	bne	.L16
	 fmovs	%f10, %f8
	std	%f12, [%i2+%lo(sa)]
.L15:
	call	barebones_clock, 0
	 std	%f10, [%fp-104]
	ldd	[%l7+16], %f8
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f23
	ldd	[%fp-104], %f10
	bl	.L74
	 fitod	%f23, %f28
.L17:
	ldd	[%i4+%lo(.LC14)], %f26
	fmuld	%f28, %f26, %f0
	fsubd	%f0, %f8, %f2
	std	%f0, [%l7+16]
	std	%f2, [%l7+8]
	ldd	[%i5+8], %f4
	ldd	[%i3+%lo(.LC0)], %f14
	fmuld	%f2, %f4, %f22
	fcmped	%f22, %f14
	nop
	fbl,a	.L18
	 st	%g0, [%i5+40]
	std	%f22, [%i5+40]
.L19:
	ldd	[%i2+%lo(sa)], %f8
	st	%l2, [%fp-64]
	sethi	%hi(sc), %g1
	ld	[%fp-64], %f27
	fitod	%f27, %f24
	std	%f8, [%fp-96]
	std	%f10, [%fp-104]
	call	barebones_clock, 0
	 std	%f24, [%g1+%lo(sc)]
	ldd	[%l7+16], %f6
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f29
	ldd	[%fp-96], %f8
	fitod	%f29, %f20
	bl	.L75
	 ldd	[%fp-104], %f10
.L20:
	ldd	[%i4+%lo(.LC14)], %f30
	fmuld	%f20, %f30, %f12
	fsubd	%f12, %f6, %f18
	std	%f12, [%l7+16]
	cmp	%l2, 0
	ble	.L50
	 std	%f18, [%l7+8]
	sethi	%hi(two), %g1
	ldd	[%i3+%lo(.LC0)], %f20
	ldd	[%g1+%lo(two)], %f28
	fmovs	%f20, %f18
	ldd	[%i2+%lo(sa)], %f26
	add	%l2, 1, %o3
	mov	1, %g1
	fmovs	%f21, %f19
	fmovs	%f18, %f14
	fmovs	%f21, %f15
.L22:
	fnegs	%f10, %f12
	fmovs	%f11, %f13
	faddd	%f8, %f28, %f8
	fsubd	%f26, %f10, %f26
	fdivd	%f12, %f8, %f10
	fsubd	%f12, %f8, %f0
	faddd	%f18, %f10, %f18
	fmuld	%f12, %f8, %f2
	add	%g1, 1, %g1
	faddd	%f20, %f0, %f20
	fsubd	%f14, %f2, %f14
	fmovs	%f12, %f10
	cmp	%g1, %o3
	bne	.L22
	 fmovs	%f13, %f11
	std	%f26, [%i2+%lo(sa)]
.L21:
	std	%f14, [%fp-120]
	std	%f18, [%fp-128]
	call	barebones_clock, 0
	 std	%f20, [%fp-136]
	ldd	[%l7+16], %f4
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f31
	ldd	[%fp-120], %f14
	fitod	%f31, %f6
	ldd	[%fp-128], %f18
	bl	.L76
	 ldd	[%fp-136], %f20
.L23:
	ldd	[%i5+8], %f12
	ldd	[%i5+40], %f8
	ldd	[%i2+%lo(sa)], %f16
	ldd	[%i4+%lo(.LC14)], %f24
	fmuld	%f20, %f16, %f26
	fmuld	%f6, %f24, %f0
	sethi	%hi(sc), %g1
	fsubd	%f0, %f4, %f2
	ldd	[%g1+%lo(sc)], %f30
	fmuld	%f2, %f12, %f4
	fdivd	%f26, %f30, %f10
	fsubd	%f4, %f8, %f22
	fdtoi	%f10, %f7
	std	%f22, [%fp-152]
	st	%f7, [%fp-64]
	ldd	[%fp-152], %g2
	ld	[%fp-64], %l3
	sethi	%hi(five), %o4
	std	%f0, [%l7+16]
	std	%f2, [%l7+8]
	std	%f4, [%i5+48]
	ldd	[%o4+%lo(five)], %f28
	sethi	%hi(four), %g1
	fdivd	%f28, %f14, %f20
	ldd	[%g1+%lo(four)], %f6
	sethi	%hi(sb), %o5
	fmuld	%f18, %f6, %f18
	sethi	%hi(.LC19), %l4
	fdivd	%f18, %f28, %f30
	ldd	[%l4+%lo(.LC19)], %f12
	ldd	[%i1+%lo(one)], %f28
	fdivd	%f22, %f12, %f0
	fdivd	%f28, %f0, %f8
	std	%f8, [%fp-8]
	st	%f8, [%fp-64]
	faddd	%f30, %f20, %f24
	std	%f24, [%o5+%lo(sb)]
	ld	[%fp-64], %o5
	std	%f0, [%i5+56]
	std	%f8, [%i5+64]
	ldd	[%l0+%lo(piref)], %f16
	mov	%g2, %o3
	mov	%g3, %o4
	fmuld	%f14, %f14, %f26
	sethi	%hi(.LC20), %l5
	fmuld	%f26, %f14, %f14
	ldd	[%l5+%lo(.LC20)], %f2
	fdivd	%f2, %f14, %f4
	fsubd	%f24, %f4, %f8
	fsubd	%f8, %f16, %f10
	std	%f10, [%fp-152]
	ldd	[%fp-152], %g2
	ld	[%fp-4], %o7
	mov	%g2, %o1
	sethi	%hi(pierr), %o0
	sethi	%hi(.LC21), %g2
	mov	%g3, %o2
	std	%f10, [%o0+%lo(pierr)]
	std	%f30, [%i2+%lo(sa)]
	st	%o7, [%sp+92]
	or	%g2, %lo(.LC21), %o0
	sethi	%hi(sc), %l6
	sethi	%hi(piprg), %l1
	std	%f2, [%l6+%lo(sc)]
	call	ee_printf, 0
	 std	%f8, [%l1+%lo(piprg)]
	sethi	%hi(three), %g3
	ldd	[%l0+%lo(piref)], %f6
	ldd	[%g3+%lo(three)], %f22
	st	%l3, [%fp-64]
	ld	[%fp-64], %f1
	fitod	%f1, %f20
	fmuld	%f20, %f22, %f18
	fdivd	%f6, %f18, %f6
	std	%f20, [%fp-72]
	call	barebones_clock, 0
	 std	%f6, [%fp-88]
	ldd	[%l7+16], %f16
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f3
	ldd	[%fp-88], %f6
	bl	.L77
	 fitod	%f3, %f28
.L24:
	ldd	[%i4+%lo(.LC14)], %f24
	fmuld	%f28, %f24, %f12
	fsubd	%f12, %f16, %f0
	std	%f12, [%l7+16]
	cmp	%l3, 1
	ble	.L51
	 std	%f0, [%l7+8]
	sethi	%hi(A2), %g1
	ldd	[%i3+%lo(.LC0)], %f12
	sethi	%hi(A6), %l5
	sethi	%hi(A5), %l2
	sethi	%hi(A4), %l4
	sethi	%hi(A3), %l1
	sethi	%hi(A1), %l6
	st	%g1, [%fp-36]
	ldd	[%i1+%lo(one)], %f2
	ldd	[%l5+%lo(A6)], %f4
	ldd	[%l2+%lo(A5)], %f26
	ldd	[%l4+%lo(A4)], %f16
	ldd	[%l1+%lo(A3)], %f22
	ldd	[%g1+%lo(A2)], %f20
	ldd	[%l6+%lo(A1)], %f30
	mov	1, %o1
	fmovs	%f12, %f14
	fmovs	%f13, %f15
.L26:
	faddd	%f12, %f2, %f12
	fmuld	%f12, %f6, %f10
	fmuld	%f10, %f10, %f8
	fmuld	%f8, %f4, %f18
	fsubd	%f18, %f26, %f28
	fmuld	%f28, %f8, %f24
	faddd	%f24, %f16, %f0
	fmuld	%f0, %f8, %f18
	fsubd	%f18, %f22, %f28
	fmuld	%f28, %f8, %f24
	add	%o1, 1, %o1
	faddd	%f24, %f20, %f0
	cmp	%o1, %l3
	fmuld	%f0, %f8, %f18
	faddd	%f18, %f30, %f28
	fmuld	%f28, %f8, %f8
	faddd	%f8, %f2, %f24
	fmuld	%f24, %f10, %f10
	bne	.L26
	 faddd	%f14, %f10, %f14
.L25:
	std	%f6, [%fp-88]
	call	barebones_clock, 0
	 std	%f14, [%fp-120]
	ldd	[%l7+16], %f2
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f5
	ldd	[%fp-88], %f6
	fitod	%f5, %f4
	bl	.L78
	 ldd	[%fp-120], %f14
.L27:
	ldd	[%i5+8], %f20
	ldd	[%i4+%lo(.LC14)], %f26
	ldd	[%i0+%lo(nulltime)], %f30
	fmuld	%f4, %f26, %f18
	ldd	[%l0+%lo(piref)], %f28
	fsubd	%f18, %f2, %f22
	fmuld	%f22, %f20, %f24
	ldd	[%l5+%lo(A6)], %f10
	fsubd	%f24, %f30, %f2
	ldd	[%l2+%lo(A5)], %f26
	std	%f2, [%fp-152]
	ldd	[%l1+%lo(A3)], %f24
	sethi	%hi(three), %o3
	ldd	[%o3+%lo(three)], %f8
	fdivd	%f28, %f8, %f4
	ldd	[%l4+%lo(A4)], %f28
	fmuld	%f4, %f4, %f12
	fmuld	%f12, %f10, %f20
	fsubd	%f20, %f26, %f30
	ldd	[%fp-152], %o0
	fmuld	%f30, %f12, %f8
	std	%f18, [%l7+16]
	std	%f22, [%l7+8]
	std	%f2, [%i5+72]
	ld	[%fp-36], %o4
	faddd	%f8, %f28, %f10
	ldd	[%o4+%lo(A2)], %f26
	fmuld	%f10, %f12, %f28
	fsubd	%f28, %f24, %f30
	fmuld	%f30, %f12, %f24
	faddd	%f24, %f26, %f18
	ldd	[%i1+%lo(one)], %f0
	fmuld	%f18, %f12, %f22
	sethi	%hi(.LC22), %o5
	ldd	[%o5+%lo(.LC22)], %f10
	fdivd	%f2, %f10, %f2
	fdivd	%f0, %f2, %f18
	std	%f18, [%fp-8]
	st	%f18, [%fp-64]
	ldd	[%l6+%lo(A1)], %f20
	ld	[%fp-64], %o5
	sethi	%hi(sb), %g2
	std	%f2, [%i5+80]
	std	%f18, [%i5+88]
	faddd	%f22, %f20, %f8
	sethi	%hi(two), %g1
	fmuld	%f8, %f12, %f12
	ldd	[%g1+%lo(two)], %f16
	faddd	%f12, %f0, %f26
	fmuld	%f16, %f14, %f14
	fmuld	%f26, %f4, %f4
	sethi	%hi(.LC23), %o7
	faddd	%f4, %f14, %f0
	ldd	[%o7+%lo(.LC23)], %f20
	fmuld	%f0, %f6, %f6
	std	%f20, [%g2+%lo(sb)]
	fdivd	%f6, %f16, %f16
	fsubd	%f16, %f20, %f28
	std	%f28, [%fp-152]
	ldd	[%fp-152], %g2
	mov	%o0, %o3
	mov	%g3, %o2
	ld	[%fp-4], %o0
	sethi	%hi(sc), %g3
	sethi	%hi(.LC24), %g4
	mov	%o1, %o4
	std	%f16, [%i2+%lo(sa)]
	mov	%g2, %o1
	st	%o0, [%sp+92]
	std	%f28, [%g3+%lo(sc)]
	call	ee_printf, 0
	 or	%g4, %lo(.LC24), %o0
	ldd	[%l2+%lo(A5)], %f8
	ldd	[%l1+%lo(A3)], %f10
	fnegs	%f8, %f14
	fmovs	%f9, %f15
	fnegs	%f10, %f16
	fmovs	%f11, %f17
	sethi	%hi(three), %o1
	ldd	[%l0+%lo(piref)], %f24
	ldd	[%o1+%lo(three)], %f30
	ldd	[%fp-72], %f18
	fmuld	%f18, %f30, %f22
	fdivd	%f24, %f22, %f12
	std	%f16, [%l1+%lo(A3)]
	std	%f12, [%fp-112]
	call	barebones_clock, 0
	 std	%f14, [%l2+%lo(A5)]
	ldd	[%l7+16], %f26
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f9
	ldd	[%fp-112], %f12
	bl	.L79
	 fitod	%f9, %f8
.L28:
	ldd	[%i4+%lo(.LC14)], %f10
	fmuld	%f8, %f10, %f2
	fsubd	%f2, %f26, %f4
	std	%f2, [%l7+16]
	cmp	%l3, 1
	ble	.L52
	 std	%f4, [%l7+8]
	sethi	%hi(B6), %g1
	st	%g1, [%fp-60]
	sethi	%hi(B3), %g1
	st	%g1, [%fp-48]
	sethi	%hi(B6), %g1
	sethi	%hi(B5), %o0
	sethi	%hi(B4), %g2
	sethi	%hi(B2), %g3
	sethi	%hi(B1), %g4
	ldd	[%g1+%lo(B6)], %f0
	sethi	%hi(B5), %o1
	sethi	%hi(B4), %o2
	sethi	%hi(B3), %g1
	sethi	%hi(B2), %o3
	sethi	%hi(B1), %o4
	st	%o0, [%fp-56]
	st	%g2, [%fp-52]
	st	%g3, [%fp-44]
	st	%g4, [%fp-40]
	ldd	[%o1+%lo(B5)], %f6
	ldd	[%o2+%lo(B4)], %f30
	ldd	[%g1+%lo(B3)], %f20
	ldd	[%o3+%lo(B2)], %f24
	ldd	[%o4+%lo(B1)], %f16
	ldd	[%i1+%lo(one)], %f18
	mov	1, %o5
	ldd	[%i3+%lo(.LC0)], %f8
.L30:
	st	%o5, [%fp-64]
	ld	[%fp-64], %f11
	fitod	%f11, %f28
	fmuld	%f28, %f12, %f22
	fmuld	%f22, %f22, %f26
	fmuld	%f26, %f0, %f14
	faddd	%f14, %f6, %f10
	fmuld	%f10, %f26, %f2
	faddd	%f2, %f30, %f4
	add	%o5, 1, %o5
	fmuld	%f4, %f26, %f28
	cmp	%o5, %l3
	faddd	%f28, %f20, %f22
	fmuld	%f22, %f26, %f14
	faddd	%f14, %f24, %f10
	fmuld	%f10, %f26, %f2
	faddd	%f2, %f16, %f4
	fmuld	%f4, %f26, %f26
	faddd	%f26, %f8, %f8
	bne	.L30
	 faddd	%f8, %f18, %f8
.L29:
	std	%f12, [%fp-112]
	call	barebones_clock, 0
	 std	%f8, [%fp-96]
	ldd	[%l7+16], %f0
	st	%o0, [%fp-64]
	ld	[%fp-64], %f13
	cmp	%o0, 0
	fitod	%f13, %f30
	ldd	[%fp-96], %f8
	bl	.L80
	 ldd	[%fp-112], %f12
.L31:
	ldd	[%i5+8], %f18
	ldd	[%i0+%lo(nulltime)], %f28
	ldd	[%l0+%lo(piref)], %f16
	sethi	%hi(two), %g1
	ldd	[%i4+%lo(.LC14)], %f24
	sethi	%hi(three), %o0
	fmuld	%f30, %f24, %f24
	ldd	[%o0+%lo(three)], %f10
	fsubd	%f24, %f0, %f22
	fmuld	%f22, %f18, %f14
	ldd	[%g1+%lo(two)], %f6
	fsubd	%f14, %f28, %f0
	fdivd	%f16, %f10, %f18
	ld	[%fp-60], %g2
	fmuld	%f18, %f18, %f14
	ldd	[%g2+%lo(B6)], %f2
	ld	[%fp-56], %g1
	fmuld	%f14, %f2, %f26
	ldd	[%g1+%lo(B5)], %f4
	ld	[%fp-52], %g3
	faddd	%f26, %f4, %f16
	ldd	[%g3+%lo(B4)], %f28
	fmuld	%f16, %f14, %f10
	ld	[%fp-48], %g4
	faddd	%f10, %f28, %f26
	ldd	[%g4+%lo(B3)], %f30
	fmuld	%f26, %f14, %f28
	sethi	%hi(.LC4), %o2
	faddd	%f28, %f30, %f30
	ldd	[%o2+%lo(.LC4)], %f16
	fmuld	%f30, %f14, %f10
	fdivd	%f0, %f16, %f26
	ldd	[%i1+%lo(one)], %f20
	std	%f0, [%fp-152]
	fdivd	%f20, %f26, %f16
	ld	[%fp-44], %g1
	st	%f16, [%fp-64]
	std	%f16, [%fp-8]
	ldd	[%g1+%lo(B2)], %f4
	ld	[%fp-40], %o1
	faddd	%f10, %f4, %f4
	ldd	[%o1+%lo(B1)], %f2
	fmuld	%f4, %f14, %f28
	fmuld	%f6, %f8, %f30
	faddd	%f28, %f2, %f2
	ldd	[%l5+%lo(A6)], %f8
	fmuld	%f14, %f8, %f10
	ldd	[%fp-152], %g2
	ld	[%fp-64], %o5
	fmuld	%f2, %f14, %f28
	ldd	[%l2+%lo(A5)], %f4
	faddd	%f28, %f20, %f2
	faddd	%f10, %f4, %f8
	faddd	%f20, %f2, %f20
	fmuld	%f14, %f8, %f10
	std	%f24, [%l7+16]
	ldd	[%l1+%lo(A3)], %f8
	ld	[%fp-36], %g1
	faddd	%f20, %f30, %f30
	ldd	[%l4+%lo(A4)], %f28
	ldd	[%l6+%lo(A1)], %f20
	faddd	%f10, %f28, %f4
	fmuld	%f30, %f12, %f12
	ldd	[%g1+%lo(A2)], %f10
	fmuld	%f14, %f4, %f2
	std	%f22, [%l7+8]
	mov	%g2, %o3
	std	%f0, [%i5+96]
	std	%f26, [%i5+104]
	std	%f16, [%i5+112]
	mov	%g3, %o4
	ld	[%fp-4], %o0
	sethi	%hi(.LC25), %g2
	sethi	%hi(sb), %g3
	faddd	%f2, %f8, %f30
	fdivd	%f12, %f6, %f6
	fmuld	%f14, %f30, %f28
	sethi	%hi(A0), %o7
	faddd	%f28, %f10, %f12
	ldd	[%o7+%lo(A0)], %f24
	fmuld	%f14, %f12, %f4
	sethi	%hi(sc), %g4
	faddd	%f4, %f20, %f2
	st	%o0, [%sp+92]
	fmuld	%f14, %f2, %f14
	or	%g2, %lo(.LC25), %o0
	faddd	%f14, %f24, %f22
	fmuld	%f18, %f22, %f0
	fsubd	%f6, %f0, %f18
	std	%f0, [%g3+%lo(sb)]
	std	%f18, [%fp-152]
	ldd	[%fp-152], %g2
	std	%f6, [%i2+%lo(sa)]
	mov	%g2, %o1
	mov	%g3, %o2
	call	ee_printf, 0
	 std	%f18, [%g4+%lo(sc)]
	sethi	%hi(three), %o3
	ldd	[%l0+%lo(piref)], %f26
	ldd	[%o3+%lo(three)], %f16
	ldd	[%fp-72], %f6
	fmuld	%f6, %f16, %f8
	fdivd	%f26, %f8, %f10
	call	barebones_clock, 0
	 std	%f10, [%fp-16]
	ldd	[%l7+16], %f30
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f15
	bl	.L81
	 fitod	%f15, %f28
.L32:
	ldd	[%i4+%lo(.LC14)], %f12
	fmuld	%f28, %f12, %f4
	fsubd	%f4, %f30, %f2
	std	%f4, [%l7+16]
	cmp	%l3, 1
	ble	.L53
	 std	%f2, [%l7+8]
	ld	[%fp-36], %g1
	ldd	[%g1+%lo(A2)], %f18
	ld	[%fp-52], %g1
	ldd	[%g1+%lo(B4)], %f2
	ld	[%fp-44], %g1
	ld	[%fp-60], %o5
	ldd	[%g1+%lo(B2)], %f16
	ld	[%fp-56], %o1
	ld	[%fp-48], %o2
	ld	[%fp-40], %g1
	ldd	[%l5+%lo(A6)], %f28
	ldd	[%g1+%lo(B1)], %f8
	ldd	[%l2+%lo(A5)], %f26
	ldd	[%l4+%lo(A4)], %f24
	ldd	[%l1+%lo(A3)], %f22
	ldd	[%l6+%lo(A1)], %f30
	ldd	[%i1+%lo(one)], %f14
	ldd	[%o5+%lo(B6)], %f6
	ldd	[%o1+%lo(B5)], %f4
	ldd	[%o2+%lo(B3)], %f0
	std	%f16, [%fp-24]
	std	%f8, [%fp-32]
	mov	1, %o7
	ldd	[%i3+%lo(.LC0)], %f12
	std	%f18, [%fp-160]
.L34:
	st	%o7, [%fp-64]
	ldd	[%fp-16], %f20
	ld	[%fp-64], %f17
	fitod	%f17, %f10
	fmuld	%f10, %f20, %f10
	fmuld	%f10, %f10, %f8
	fmuld	%f8, %f28, %f16
	faddd	%f16, %f26, %f20
	fmuld	%f8, %f6, %f18
	fmuld	%f20, %f8, %f16
	faddd	%f18, %f4, %f18
	fmuld	%f18, %f8, %f20
	faddd	%f16, %f24, %f16
	faddd	%f20, %f2, %f18
	fmuld	%f16, %f8, %f20
	fmuld	%f18, %f8, %f18
	faddd	%f20, %f22, %f16
	faddd	%f18, %f0, %f20
	fmuld	%f20, %f8, %f18
	ldd	[%fp-160], %f20
	fmuld	%f16, %f8, %f16
	faddd	%f16, %f20, %f16
	ldd	[%fp-24], %f20
	fmuld	%f16, %f8, %f16
	faddd	%f18, %f20, %f18
	faddd	%f16, %f30, %f16
	fmuld	%f18, %f8, %f18
	fmuld	%f16, %f8, %f16
	ldd	[%fp-32], %f20
	faddd	%f18, %f20, %f18
	add	%o7, 1, %o7
	faddd	%f16, %f14, %f20
	fmuld	%f18, %f8, %f8
	fmuld	%f20, %f10, %f10
	faddd	%f8, %f14, %f18
	cmp	%o7, %l3
	fdivd	%f10, %f18, %f16
	bne	.L34
	 faddd	%f12, %f16, %f12
.L33:
	call	barebones_clock, 0
	 std	%f12, [%fp-112]
	ldd	[%l7+16], %f26
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f19
	ldd	[%fp-112], %f12
	bl	.L82
	 fitod	%f19, %f24
.L35:
	ldd	[%i0+%lo(nulltime)], %f6
	ldd	[%i5+8], %f30
	ldd	[%i4+%lo(.LC14)], %f22
	ldd	[%l0+%lo(piref)], %f8
	fmuld	%f24, %f22, %f0
	sethi	%hi(two), %g1
	fsubd	%f0, %f26, %f20
	ldd	[%l5+%lo(A6)], %f24
	fmuld	%f20, %f30, %f14
	ldd	[%l2+%lo(A5)], %f26
	fsubd	%f14, %f6, %f10
	ldd	[%l4+%lo(A4)], %f6
	ldd	[%g1+%lo(two)], %f2
	sethi	%hi(three), %g2
	ld	[%fp-60], %g1
	ldd	[%g2+%lo(three)], %f18
	fdivd	%f8, %f18, %f16
	ldd	[%l1+%lo(A3)], %f8
	fmuld	%f16, %f16, %f28
	fmuld	%f28, %f24, %f22
	faddd	%f22, %f26, %f30
	fmuld	%f30, %f28, %f14
	faddd	%f14, %f6, %f24
	ldd	[%g1+%lo(B6)], %f6
	fmuld	%f24, %f28, %f26
	ld	[%fp-56], %g4
	faddd	%f26, %f8, %f30
	ld	[%fp-36], %g3
	ldd	[%g4+%lo(B5)], %f26
	fmuld	%f30, %f28, %f14
	ldd	[%g3+%lo(A2)], %f18
	fmuld	%f28, %f6, %f8
	faddd	%f14, %f18, %f18
	faddd	%f8, %f26, %f6
	std	%f10, [%fp-152]
	ldd	[%i1+%lo(one)], %f4
	ldd	[%fp-152], %o0
	fmuld	%f18, %f28, %f24
	fmuld	%f6, %f28, %f30
	ld	[%fp-52], %o3
	ld	[%fp-44], %o4
	ldd	[%o3+%lo(B4)], %f8
	ldd	[%l6+%lo(A1)], %f22
	faddd	%f30, %f8, %f14
	faddd	%f24, %f22, %f22
	fmuld	%f14, %f28, %f6
	fmuld	%f22, %f28, %f26
	faddd	%f26, %f4, %f18
	fmuld	%f18, %f16, %f16
	ldd	[%o4+%lo(B2)], %f30
	ld	[%fp-48], %g1
	ld	[%fp-40], %o5
	ldd	[%g1+%lo(B3)], %f24
	ldd	[%o5+%lo(B1)], %f26
	faddd	%f6, %f24, %f22
	mov	%o1, %o4
	fmuld	%f22, %f28, %f8
	std	%f0, [%l7+16]
	faddd	%f8, %f30, %f14
	std	%f20, [%l7+8]
	fmuld	%f14, %f28, %f18
	std	%f10, [%i5+120]
	faddd	%f18, %f26, %f0
	sethi	%hi(.LC26), %o1
	fmuld	%f0, %f28, %f20
	faddd	%f4, %f20, %f28
	fdivd	%f16, %f28, %f6
	ldd	[%o1+%lo(.LC26)], %f16
	ldd	[%fp-16], %f30
	fdivd	%f10, %f16, %f10
	fdivd	%f4, %f10, %f16
	std	%f16, [%fp-8]
	st	%f16, [%fp-64]
	ld	[%fp-64], %o5
	std	%f10, [%i5+128]
	std	%f16, [%i5+136]
	fmuld	%f2, %f12, %f12
	sethi	%hi(.LC27), %o2
	faddd	%f6, %f12, %f24
	fmuld	%f24, %f30, %f22
	fdivd	%f22, %f2, %f4
	ldd	[%o2+%lo(.LC27)], %f2
	fsubd	%f4, %f2, %f26
	std	%f26, [%fp-152]
	ldd	[%fp-152], %g2
	mov	%o0, %o3
	ld	[%fp-4], %o7
	sethi	%hi(sb), %g1
	mov	%g2, %o1
	sethi	%hi(sc), %o0
	sethi	%hi(.LC28), %g2
	mov	%g3, %o2
	std	%f26, [%o0+%lo(sc)]
	std	%f4, [%i2+%lo(sa)]
	st	%o7, [%sp+92]
	std	%f2, [%g1+%lo(sb)]
	call	ee_printf, 0
	 or	%g2, %lo(.LC28), %o0
	sethi	%hi(four), %g3
	ldd	[%l0+%lo(piref)], %f8
	ldd	[%g3+%lo(four)], %f14
	ldd	[%fp-72], %f12
	fmuld	%f12, %f14, %f18
	fdivd	%f8, %f18, %f0
	call	barebones_clock, 0
	 std	%f0, [%fp-16]
	ldd	[%l7+16], %f20
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f25
	bl	.L83
	 fitod	%f25, %f6
.L36:
	ldd	[%i4+%lo(.LC14)], %f16
	fmuld	%f6, %f16, %f24
	fsubd	%f24, %f20, %f10
	std	%f24, [%l7+16]
	cmp	%l3, 1
	ble	.L54
	 std	%f10, [%l7+8]
	ld	[%fp-36], %g1
	ldd	[%g1+%lo(A2)], %f18
	ld	[%fp-52], %g1
	ldd	[%g1+%lo(B4)], %f2
	ld	[%fp-44], %g1
	ldd	[%g1+%lo(B2)], %f8
	ld	[%fp-40], %g1
	ldd	[%g1+%lo(B1)], %f12
	ld	[%fp-60], %o3
	ld	[%fp-56], %o4
	ld	[%fp-48], %o5
	std	%f12, [%fp-32]
	ldd	[%l5+%lo(A6)], %f28
	ldd	[%l2+%lo(A5)], %f26
	ldd	[%l4+%lo(A4)], %f24
	ldd	[%l1+%lo(A3)], %f22
	ldd	[%l6+%lo(A1)], %f30
	ldd	[%i1+%lo(one)], %f14
	ldd	[%o3+%lo(B6)], %f6
	ldd	[%o4+%lo(B5)], %f4
	ldd	[%o5+%lo(B3)], %f0
	std	%f8, [%fp-24]
	mov	1, %o1
	ldd	[%i3+%lo(.LC0)], %f12
	std	%f18, [%fp-160]
.L38:
	st	%o1, [%fp-64]
	ld	[%fp-64], %f21
	fitod	%f21, %f20
	ldd	[%fp-16], %f16
	fmuld	%f20, %f16, %f10
	fmuld	%f10, %f10, %f8
	fmuld	%f8, %f6, %f20
	fmuld	%f8, %f28, %f18
	faddd	%f20, %f4, %f16
	faddd	%f18, %f26, %f20
	fmuld	%f16, %f8, %f16
	fmuld	%f20, %f8, %f18
	faddd	%f16, %f2, %f20
	faddd	%f18, %f24, %f18
	fmuld	%f20, %f8, %f16
	fmuld	%f18, %f8, %f20
	faddd	%f20, %f22, %f18
	ldd	[%fp-24], %f20
	faddd	%f16, %f0, %f16
	fmuld	%f16, %f8, %f16
	faddd	%f16, %f20, %f16
	ldd	[%fp-160], %f20
	fmuld	%f18, %f8, %f18
	faddd	%f18, %f20, %f18
	ldd	[%fp-32], %f20
	fmuld	%f16, %f8, %f16
	fmuld	%f18, %f8, %f18
	faddd	%f16, %f20, %f16
	faddd	%f18, %f30, %f18
	fmuld	%f16, %f8, %f20
	add	%o1, 1, %o1
	fmuld	%f18, %f8, %f8
	faddd	%f20, %f14, %f16
	faddd	%f8, %f14, %f18
	cmp	%o1, %l3
	fmuld	%f18, %f10, %f10
	fmuld	%f16, %f10, %f20
	bne	.L38
	 faddd	%f12, %f20, %f12
.L37:
	call	barebones_clock, 0
	 std	%f12, [%fp-112]
	ldd	[%l7+16], %f26
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f23
	ldd	[%fp-112], %f12
	bl	.L84
	 fitod	%f23, %f30
.L39:
	ldd	[%i5+8], %f14
	ldd	[%i4+%lo(.LC14)], %f24
	ldd	[%i0+%lo(nulltime)], %f6
	ldd	[%l0+%lo(piref)], %f16
	fmuld	%f30, %f24, %f2
	ldd	[%l5+%lo(A6)], %f10
	fsubd	%f2, %f26, %f0
	ldd	[%l4+%lo(A4)], %f28
	fmuld	%f0, %f14, %f8
	ldd	[%l2+%lo(A5)], %f26
	fsubd	%f8, %f6, %f20
	sethi	%hi(two), %g1
	sethi	%hi(four), %o7
	ldd	[%o7+%lo(four)], %f18
	fdivd	%f16, %f18, %f24
	ldd	[%l1+%lo(A3)], %f16
	fmuld	%f24, %f24, %f14
	fmuld	%f14, %f10, %f30
	faddd	%f30, %f26, %f6
	ldd	[%g1+%lo(two)], %f22
	fmuld	%f6, %f14, %f8
	ld	[%fp-60], %g1
	faddd	%f8, %f28, %f10
	ldd	[%g1+%lo(B6)], %f28
	fmuld	%f10, %f14, %f26
	faddd	%f26, %f16, %f6
	fmuld	%f14, %f28, %f16
	fmuld	%f6, %f14, %f8
	ld	[%fp-36], %o0
	ldd	[%l6+%lo(A1)], %f30
	ldd	[%o0+%lo(A2)], %f18
	ld	[%fp-56], %g2
	faddd	%f8, %f18, %f18
	ldd	[%g2+%lo(B5)], %f26
	fmuld	%f18, %f14, %f10
	faddd	%f16, %f26, %f28
	faddd	%f10, %f30, %f16
	ldd	[%i1+%lo(one)], %f4
	fmuld	%f28, %f14, %f6
	fmuld	%f16, %f14, %f8
	ld	[%fp-44], %g4
	faddd	%f8, %f4, %f26
	ldd	[%g4+%lo(B2)], %f16
	ld	[%fp-52], %g3
	ld	[%fp-48], %g1
	ldd	[%g3+%lo(B4)], %f30
	ldd	[%g1+%lo(B3)], %f10
	faddd	%f6, %f30, %f18
	std	%f20, [%fp-152]
	fmuld	%f18, %f14, %f28
	fmuld	%f26, %f24, %f24
	faddd	%f28, %f10, %f30
	sethi	%hi(.LC26), %o4
	fmuld	%f30, %f14, %f8
	ldd	[%o4+%lo(.LC26)], %f18
	faddd	%f8, %f16, %f26
	fdivd	%f20, %f18, %f16
	fdivd	%f4, %f16, %f10
	st	%f10, [%fp-64]
	std	%f10, [%fp-8]
	ldd	[%fp-152], %g2
	ldd	[%fp-16], %f8
	ld	[%fp-40], %o3
	ld	[%fp-64], %o5
	ldd	[%o3+%lo(B1)], %f6
	std	%f2, [%l7+16]
	std	%f16, [%i5+152]
	std	%f0, [%l7+8]
	std	%f20, [%i5+144]
	std	%f10, [%i5+160]
	fmuld	%f26, %f14, %f28
	fmuld	%f22, %f12, %f12
	faddd	%f28, %f6, %f30
	mov	%g2, %o3
	fmuld	%f30, %f14, %f14
	mov	%g3, %o4
	faddd	%f4, %f14, %f4
	ld	[%fp-4], %o2
	fmuld	%f24, %f4, %f24
	sethi	%hi(sb), %g1
	faddd	%f24, %f12, %f6
	sethi	%hi(sc), %o7
	fmuld	%f6, %f8, %f18
	sethi	%hi(.LC29), %o1
	fdivd	%f18, %f22, %f22
	ldd	[%o1+%lo(.LC29)], %f2
	fsubd	%f22, %f2, %f0
	std	%f0, [%fp-152]
	ldd	[%fp-152], %g2
	std	%f22, [%i2+%lo(sa)]
	st	%o2, [%sp+92]
	std	%f2, [%g1+%lo(sb)]
	mov	%g2, %o1
	mov	%g3, %o2
	std	%f0, [%o7+%lo(sc)]
	sethi	%hi(.LC30), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC30), %o0
	ldd	[%i1+%lo(one)], %f10
	ldd	[%fp-72], %f26
	sethi	%hi(.LC31), %o5
	ldd	[%o5+%lo(.LC31)], %f20
	fdivd	%f20, %f26, %f18
	std	%f10, [%fp-104]
	std	%f18, [%fp-128]
	call	barebones_clock, 0
	 std	%f20, [%i2+%lo(sa)]
	ldd	[%l7+16], %f16
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f27
	ldd	[%fp-104], %f10
	fitod	%f27, %f30
	bl	.L85
	 ldd	[%fp-128], %f18
.L40:
	ldd	[%i4+%lo(.LC14)], %f12
	fmuld	%f30, %f12, %f14
	fsubd	%f14, %f16, %f4
	std	%f14, [%l7+16]
	cmp	%l3, 1
	ble	.L55
	 std	%f4, [%l7+8]
	mov	1, %g3
	ldd	[%i3+%lo(.LC0)], %f14
.L42:
	st	%g3, [%fp-64]
	ld	[%fp-64], %f29
	add	%g3, 1, %g3
	fitod	%f29, %f24
	cmp	%g3, %l3
	fmuld	%f24, %f18, %f6
	fmuld	%f6, %f6, %f22
	faddd	%f6, %f10, %f8
	faddd	%f22, %f10, %f2
	fdivd	%f10, %f8, %f0
	fdivd	%f6, %f2, %f20
	fsubd	%f14, %f0, %f26
	fmuld	%f6, %f22, %f16
	fsubd	%f26, %f20, %f28
	faddd	%f16, %f10, %f30
	fdivd	%f22, %f30, %f12
	bne	.L42
	 fsubd	%f28, %f12, %f14
.L41:
	std	%f10, [%fp-104]
	std	%f14, [%fp-120]
	call	barebones_clock, 0
	 std	%f18, [%fp-128]
	ldd	[%l7+16], %f4
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f31
	ldd	[%fp-104], %f10
	fitod	%f31, %f6
	ldd	[%fp-120], %f14
	bl	.L86
	 ldd	[%fp-128], %f18
.L43:
	ldd	[%i5+8], %f26
	ldd	[%i2+%lo(sa)], %f2
	ldd	[%i4+%lo(.LC14)], %f8
	fmuld	%f2, %f2, %f22
	fmuld	%f6, %f8, %f0
	faddd	%f22, %f10, %f12
	fsubd	%f0, %f4, %f20
	ldd	[%i0+%lo(nulltime)], %f16
	fmuld	%f20, %f26, %f28
	sethi	%hi(two), %g1
	fsubd	%f28, %f16, %f4
	std	%f4, [%fp-152]
	faddd	%f2, %f10, %f30
	ldd	[%fp-152], %o0
	fmuld	%f2, %f22, %f6
	std	%f0, [%l7+16]
	std	%f20, [%l7+8]
	std	%f4, [%i5+168]
	ldd	[%g1+%lo(two)], %f26
	fdivd	%f2, %f12, %f2
	sethi	%hi(.LC32), %g1
	fmuld	%f14, %f26, %f12
	ldd	[%g1+%lo(.LC32)], %f14
	fdivd	%f4, %f14, %f0
	std	%f0, [%i5+176]
	faddd	%f6, %f10, %f8
	sethi	%hi(.LC33), %g1
	fdivd	%f22, %f8, %f28
	ldd	[%i1+%lo(one)], %f22
	fdivd	%f22, %f0, %f22
	st	%f22, [%fp-64]
	std	%f22, [%fp-8]
	ld	[%fp-64], %o5
	ldd	[%g1+%lo(.LC33)], %f20
	std	%f22, [%i5+184]
	fdivd	%f10, %f30, %f24
	ld	[%fp-4], %g1
	fmuld	%f18, %f20, %f18
	st	%g1, [%sp+92]
	fnegs	%f10, %f10
	sethi	%hi(.LC34), %g1
	fsubd	%f10, %f24, %f10
	fsubd	%f10, %f2, %f16
	fsubd	%f16, %f28, %f4
	faddd	%f4, %f12, %f24
	fmuld	%f18, %f24, %f6
	fdtoi	%f6, %f1
	st	%f1, [%fp-64]
	ldd	[%g1+%lo(.LC34)], %f2
	ld	[%fp-64], %g1
	smul	%g1, -2000, %g1
	st	%g1, [%fp-64]
	faddd	%f6, %f2, %f26
	sethi	%hi(.LC35), %g4
	std	%f26, [%fp-152]
	std	%f6, [%i2+%lo(sa)]
	ldd	[%fp-152], %g2
	ld	[%fp-64], %f7
	sethi	%hi(sc), %g1
	fitod	%f7, %f8
	sethi	%hi(scale), %l3
	ldd	[%l3+%lo(scale)], %f30
	fdivd	%f8, %f30, %f28
	fdtoi	%f28, %f3
	st	%f3, [%fp-64]
	ld	[%fp-64], %o7
	mov	%o1, %o4
	mov	%o0, %o3
	std	%f26, [%g1+%lo(sc)]
	or	%g4, %lo(.LC35), %o0
	mov	%g2, %o1
	st	%o7, [%fp-76]
	call	ee_printf, 0
	 mov	%g3, %o2
	sethi	%hi(three), %g1
	ldd	[%l0+%lo(piref)], %f22
	ldd	[%g1+%lo(three)], %f30
	ld	[%fp-76], %o3
	st	%o3, [%fp-64]
	ld	[%fp-64], %f5
	fitod	%f5, %f12
	fmuld	%f12, %f30, %f14
	fdivd	%f22, %f14, %f0
	call	barebones_clock, 0
	 std	%f0, [%fp-16]
	ldd	[%l7+16], %f20
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f9
	ld	[%fp-76], %o4
	bl	.L87
	 fitod	%f9, %f10
.L44:
	ldd	[%i4+%lo(.LC14)], %f16
	fmuld	%f10, %f16, %f4
	fsubd	%f4, %f20, %f24
	std	%f4, [%l7+16]
	cmp	%o4, 1
	ble	.L56
	 std	%f24, [%l7+8]
	ld	[%fp-60], %g1
	ldd	[%g1+%lo(B6)], %f26
	ld	[%fp-52], %g1
	ldd	[%g1+%lo(B4)], %f22
	ld	[%fp-44], %g1
	ldd	[%g1+%lo(B2)], %f14
	ld	[%fp-36], %g1
	ldd	[%g1+%lo(A2)], %f6
	ld	[%fp-56], %o1
	ld	[%fp-48], %o2
	ld	[%fp-40], %o0
	std	%f6, [%fp-24]
	ldd	[%l6+%lo(A1)], %f8
	ldd	[%o1+%lo(B5)], %f24
	ldd	[%o2+%lo(B3)], %f20
	ldd	[%o0+%lo(B1)], %f28
	ldd	[%i1+%lo(one)], %f12
	ldd	[%l5+%lo(A6)], %f30
	ldd	[%l2+%lo(A5)], %f4
	ldd	[%l4+%lo(A4)], %f2
	ldd	[%l1+%lo(A3)], %f0
	std	%f8, [%fp-32]
	mov	1, %g1
	ldd	[%i3+%lo(.LC0)], %f6
	std	%f14, [%fp-72]
.L46:
	ldd	[%fp-16], %f18
	st	%g1, [%fp-64]
	ld	[%fp-64], %f11
	fitod	%f11, %f10
	fmuld	%f10, %f18, %f10
	fmuld	%f10, %f10, %f8
	fmuld	%f8, %f26, %f14
	faddd	%f14, %f24, %f18
	fmuld	%f8, %f30, %f16
	fmuld	%f18, %f8, %f14
	faddd	%f16, %f4, %f16
	fmuld	%f16, %f8, %f18
	faddd	%f14, %f22, %f14
	faddd	%f18, %f2, %f16
	fmuld	%f14, %f8, %f18
	fmuld	%f16, %f8, %f16
	faddd	%f18, %f20, %f14
	faddd	%f16, %f0, %f18
	fmuld	%f18, %f8, %f16
	ldd	[%fp-72], %f18
	fmuld	%f14, %f8, %f14
	faddd	%f14, %f18, %f14
	ldd	[%fp-24], %f18
	fmuld	%f14, %f8, %f14
	faddd	%f16, %f18, %f16
	faddd	%f14, %f28, %f14
	fmuld	%f16, %f8, %f16
	fmuld	%f14, %f8, %f14
	ldd	[%fp-32], %f18
	faddd	%f16, %f18, %f16
	fmuld	%f16, %f8, %f8
	add	%g1, 1, %g1
	faddd	%f14, %f12, %f18
	faddd	%f8, %f12, %f16
	fmuld	%f18, %f18, %f14
	cmp	%g1, %o4
	fmuld	%f14, %f10, %f10
	fmuld	%f10, %f16, %f8
	bne	.L46
	 faddd	%f6, %f8, %f6
.L45:
	std	%f6, [%fp-88]
	call	barebones_clock, 0
	 st	%o4, [%fp-76]
	ldd	[%l7+16], %f26
	st	%o0, [%fp-64]
	cmp	%o0, 0
	ld	[%fp-64], %f13
	ld	[%fp-76], %g2
	fitod	%f13, %f22
	bl	.L88
	 ldd	[%fp-88], %f6
.L47:
	ldd	[%i0+%lo(nulltime)], %f0
	ldd	[%i5+8], %f28
	ldd	[%i4+%lo(.LC14)], %f20
	ldd	[%l0+%lo(piref)], %f16
	fmuld	%f22, %f20, %f2
	ld	[%fp-60], %i3
	fsubd	%f2, %f26, %f18
	sethi	%hi(two), %g1
	fmuld	%f18, %f28, %f14
	ldd	[%i3+%lo(B6)], %f26
	fsubd	%f14, %f0, %f10
	sethi	%hi(three), %l0
	ldd	[%l0+%lo(three)], %f12
	fdivd	%f16, %f12, %f0
	fmuld	%f0, %f0, %f8
	fmuld	%f8, %f26, %f22
	ldd	[%g1+%lo(two)], %f4
	ld	[%fp-48], %o5
	ld	[%fp-56], %g1
	ldd	[%o5+%lo(B3)], %f16
	ldd	[%g1+%lo(B5)], %f24
	ld	[%fp-52], %i4
	faddd	%f22, %f24, %f28
	ldd	[%i4+%lo(B4)], %f20
	fmuld	%f28, %f8, %f14
	faddd	%f14, %f20, %f26
	fmuld	%f26, %f8, %f22
	std	%f10, [%fp-152]
	ld	[%fp-44], %g1
	ldd	[%l5+%lo(A6)], %f24
	faddd	%f22, %f16, %f28
	ldd	[%g1+%lo(B2)], %f12
	fmuld	%f8, %f24, %f16
	fmuld	%f28, %f8, %f14
	ldd	[%l2+%lo(A5)], %f22
	faddd	%f14, %f12, %f12
	faddd	%f16, %f22, %f26
	ld	[%fp-40], %g3
	ldd	[%fp-152], %o0
	ldd	[%g3+%lo(B1)], %f20
	std	%f2, [%l7+16]
	std	%f18, [%l7+8]
	std	%f10, [%i5+192]
	fmuld	%f12, %f8, %f24
	fmuld	%f26, %f8, %f28
	ldd	[%l4+%lo(A4)], %f16
	ldd	[%l1+%lo(A3)], %f26
	faddd	%f28, %f16, %f22
	faddd	%f24, %f20, %f20
	fmuld	%f22, %f8, %f12
	fmuld	%f20, %f8, %f14
	sethi	%hi(.LC36), %g1
	ldd	[%i1+%lo(one)], %f30
	faddd	%f12, %f26, %f28
	faddd	%f30, %f14, %f20
	ldd	[%g1+%lo(.LC36)], %f26
	ldd	[%l6+%lo(A1)], %f16
	fdivd	%f10, %f26, %f10
	fmuld	%f28, %f8, %f14
	ld	[%fp-36], %l5
	sethi	%hi(.LC37), %g1
	ldd	[%l5+%lo(A2)], %f24
	faddd	%f14, %f24, %f22
	fmuld	%f22, %f8, %f2
	faddd	%f2, %f16, %f18
	fmuld	%f18, %f8, %f8
	faddd	%f8, %f30, %f12
	fdivd	%f30, %f10, %f30
	st	%f30, [%fp-64]
	fmuld	%f4, %f6, %f6
	ld	[%fp-64], %o5
	std	%f30, [%fp-8]
	std	%f10, [%i5+200]
	std	%f30, [%i5+208]
	ldd	[%g1+%lo(.LC37)], %f30
	ld	[%fp-4], %g1
	fmuld	%f12, %f0, %f0
	ldd	[%fp-16], %f16
	fmuld	%f0, %f20, %f24
	st	%g1, [%sp+92]
	fmuld	%f20, %f24, %f20
	sethi	%hi(sb), %g1
	faddd	%f20, %f6, %f28
	fmuld	%f28, %f16, %f14
	fdivd	%f14, %f4, %f4
	fsubd	%f4, %f30, %f6
	std	%f4, [%i2+%lo(sa)]
	std	%f6, [%fp-152]
	ldd	[%fp-152], %i2
	mov	%o0, %o3
	mov	%o1, %o4
	st	%g2, [%fp-76]
	mov	%i3, %o2
	mov	%i2, %o1
	std	%f30, [%g1+%lo(sb)]
	sethi	%hi(sc), %l7
	sethi	%hi(.LC38), %i2
	std	%f6, [%l7+%lo(sc)]
	call	ee_printf, 0
	 or	%i2, %lo(.LC38), %o0
	sethi	%hi(.LC1), %g1
	ldd	[%i1+%lo(one)], %f2
	ldd	[%i5+48], %f10
	ldd	[%i5+40], %f12
	or	%g1, %lo(.LC1), %o0
	fsubd	%f10, %f12, %f20
	sethi	%hi(five), %i1
	sethi	%hi(.LC39), %g1
	ldd	[%i1+%lo(five)], %f26
	fmuld	%f20, %f26, %f14
	ldd	[%i5+72], %f8
	ldd	[%i5+96], %f0
	ldd	[%i5+16], %f28
	faddd	%f14, %f8, %f4
	faddd	%f8, %f28, %f16
	ldd	[%g1+%lo(.LC39)], %f14
	sethi	%hi(.LC40), %g1
	faddd	%f8, %f0, %f8
	ldd	[%i5+144], %f24
	ldd	[%i5+168], %f22
	faddd	%f16, %f0, %f30
	ldd	[%i5+120], %f6
	fdivd	%f4, %f14, %f16
	faddd	%f30, %f6, %f12
	ldd	[%g1+%lo(.LC40)], %f4
	faddd	%f12, %f24, %f20
	sethi	%hi(four), %l2
	sethi	%hi(.LC41), %g1
	ldd	[%l2+%lo(four)], %f10
	fmuld	%f22, %f10, %f26
	faddd	%f20, %f22, %f22
	faddd	%f20, %f26, %f0
	fdivd	%f2, %f16, %f6
	fdivd	%f0, %f4, %f30
	ldd	[%g1+%lo(.LC41)], %f12
	fdivd	%f2, %f30, %f10
	faddd	%f24, %f8, %f24
	sethi	%hi(.LC42), %g1
	ldd	[%i5+192], %f18
	ldd	[%g1+%lo(.LC42)], %f20
	faddd	%f22, %f18, %f28
	faddd	%f18, %f24, %f18
	fdivd	%f28, %f12, %f26
	fdivd	%f18, %f20, %f0
	fdivd	%f2, %f26, %f22
	fdivd	%f2, %f0, %f2
	std	%f16, [%i5+216]
	std	%f6, [%i5+224]
	std	%f30, [%i5+232]
	std	%f10, [%i5+240]
	std	%f26, [%i5+248]
	std	%f22, [%i5+256]
	std	%f0, [%i5+264]
	call	ee_printf, 0
	 std	%f2, [%i5+272]
	sethi	%hi(.LC43), %l1
	ld	[%fp-76], %l4
	or	%l1, %lo(.LC43), %o0
	call	ee_printf, 0
	 mov	%l4, %o1
	ld	[%i0+%lo(nulltime)], %o1
	ld	[%i0+%lo(nulltime+4)], %o2
	sethi	%hi(.LC44), %i0
	call	ee_printf, 0
	 or	%i0, %lo(.LC44), %o0
	ld	[%i5+224], %o1
	ld	[%i5+228], %o2
	sethi	%hi(.LC45), %l6
	call	ee_printf, 0
	 or	%l6, %lo(.LC45), %o0
	ld	[%i5+240], %o1
	ld	[%i5+244], %o2
	sethi	%hi(.LC46), %l3
	call	ee_printf, 0
	 or	%l3, %lo(.LC46), %o0
	sethi	%hi(.LC47), %g4
	ld	[%i5+256], %o1
	ld	[%i5+260], %o2
	call	ee_printf, 0
	 or	%g4, %lo(.LC47), %o0
	ld	[%i5+272], %o1
	ld	[%i5+276], %o2
	mov	0, %i0
	sethi	%hi(.LC48), %i5
	call	ee_printf, 0
	 or	%i5, %lo(.LC48), %o0
	jmp	%i7+8
	 restore
.L69:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f14
	b	.L5
	 faddd	%f16, %f14, %f16
.L70:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f12
	b	.L7
	 faddd	%f10, %f12, %f10
.L12:
	fmovs	%f8, %f10
	fmovs	%f9, %f11
	st	%g0, [%i0+%lo(nulltime)]
	b	.L13
	 st	%g0, [%i0+%lo(nulltime+4)]
.L18:
	b	.L19
	 st	%g0, [%i5+44]
.L71:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f6
	b	.L10
	 faddd	%f16, %f6, %f16
.L68:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f30
	b	.L3
	 faddd	%f8, %f30, %f8
.L67:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f18
	b	.L2
	 faddd	%f20, %f18, %f20
.L88:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f24
	b	.L47
	 faddd	%f22, %f24, %f22
.L87:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f18
	b	.L44
	 faddd	%f10, %f18, %f10
.L86:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f24
	b	.L43
	 faddd	%f6, %f24, %f6
.L85:
	sethi	%hi(.LC13), %g2
	ldd	[%g2+%lo(.LC13)], %f28
	b	.L40
	 faddd	%f30, %f28, %f30
.L84:
	sethi	%hi(.LC13), %o2
	ldd	[%o2+%lo(.LC13)], %f28
	b	.L39
	 faddd	%f30, %f28, %f30
.L83:
	sethi	%hi(.LC13), %g4
	ldd	[%g4+%lo(.LC13)], %f28
	b	.L36
	 faddd	%f6, %f28, %f6
.L72:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f12
	b	.L11
	 faddd	%f10, %f12, %f10
.L74:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f18
	b	.L17
	 faddd	%f28, %f18, %f28
.L73:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f24
	b	.L14
	 faddd	%f16, %f24, %f16
.L77:
	sethi	%hi(.LC13), %l2
	ldd	[%l2+%lo(.LC13)], %f30
	b	.L24
	 faddd	%f28, %f30, %f28
.L76:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f22
	b	.L23
	 faddd	%f6, %f22, %f6
.L75:
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f16
	b	.L20
	 faddd	%f20, %f16, %f20
.L82:
	sethi	%hi(.LC13), %o0
	ldd	[%o0+%lo(.LC13)], %f28
	b	.L35
	 faddd	%f24, %f28, %f24
.L81:
	sethi	%hi(.LC13), %o4
	ldd	[%o4+%lo(.LC13)], %f20
	b	.L32
	 faddd	%f28, %f20, %f28
.L80:
	sethi	%hi(.LC13), %o7
	ldd	[%o7+%lo(.LC13)], %f6
	b	.L31
	 faddd	%f30, %f6, %f30
.L79:
	sethi	%hi(.LC13), %o2
	ldd	[%o2+%lo(.LC13)], %f14
	b	.L28
	 faddd	%f8, %f14, %f8
.L78:
	sethi	%hi(.LC13), %o2
	ldd	[%o2+%lo(.LC13)], %f12
	b	.L27
	 faddd	%f4, %f12, %f4
.L52:
	sethi	%hi(B6), %g1
	sethi	%hi(B5), %o3
	st	%g1, [%fp-60]
	sethi	%hi(B4), %o4
	sethi	%hi(B3), %g1
	sethi	%hi(B2), %o5
	sethi	%hi(B1), %o7
	ldd	[%i3+%lo(.LC0)], %f8
	st	%o3, [%fp-56]
	st	%o4, [%fp-52]
	st	%g1, [%fp-48]
	st	%o5, [%fp-44]
	b	.L29
	 st	%o7, [%fp-40]
.L55:
	b	.L41
	 ldd	[%i3+%lo(.LC0)], %f14
.L56:
	b	.L45
	 ldd	[%i3+%lo(.LC0)], %f6
.L49:
	fmovs	%f8, %f10
	b	.L15
	 fmovs	%f9, %f11
.L54:
	b	.L37
	 ldd	[%i3+%lo(.LC0)], %f12
.L53:
	b	.L33
	 ldd	[%i3+%lo(.LC0)], %f12
.L50:
	ldd	[%i3+%lo(.LC0)], %f20
	fmovs	%f20, %f18
	fmovs	%f21, %f19
	fmovs	%f18, %f14
	b	.L21
	 fmovs	%f21, %f15
.L51:
	sethi	%hi(A2), %g4
	ldd	[%i3+%lo(.LC0)], %f14
	sethi	%hi(A6), %l5
	sethi	%hi(A5), %l2
	sethi	%hi(A4), %l4
	sethi	%hi(A3), %l1
	st	%g4, [%fp-36]
	b	.L25
	 sethi	%hi(A1), %l6
	.size	ajit_main, .-ajit_main
	.section	.rodata.cst8
	.align 8
.LC49:
	.long	1106247680
	.long	0
	.align 8
.LC50:
	.long	1053129102
	.long	3794832442
	.section	".text"
	.align 4
	.global dtime
	.type	dtime, #function
	.proc	04
dtime:
	save	%sp, -104, %sp
	call	barebones_clock, 0
	 nop
	st	%o0, [%fp-4]
	mov	%i0, %g1
	ld	[%fp-4], %f10
	ldd	[%i0+16], %f0
	cmp	%o0, 0
	bl	.L91
	 fitod	%f10, %f8
	sethi	%hi(.LC50), %g3
	ldd	[%g3+%lo(.LC50)], %f2
	fmuld	%f8, %f2, %f4
	fsubd	%f4, %f0, %f6
	std	%f4, [%g1+16]
	std	%f6, [%g1+8]
	jmp	%i7+8
	 restore %g0, 0, %o0
.L91:
	sethi	%hi(.LC49), %g2
	sethi	%hi(.LC50), %g3
	ldd	[%g2+%lo(.LC49)], %f12
	ldd	[%g3+%lo(.LC50)], %f2
	faddd	%f8, %f12, %f8
	fmuld	%f8, %f2, %f4
	fsubd	%f4, %f0, %f6
	std	%f4, [%g1+16]
	std	%f6, [%g1+8]
	jmp	%i7+8
	 restore %g0, 0, %o0
	.size	dtime, .-dtime
	.global E3
	.section	".data"
	.align 8
	.type	E3, #object
	.size	E3, 8
E3:
	.long	1050383821
	.long	1788578186
	.global E2
	.align 8
	.type	E2, #object
	.size	E2, 8
E2:
	.long	1061123344
	.long	1297423721
	.global D3
	.align 8
	.type	D3, #object
	.size	D3, 8
D3:
	.long	1052029018
	.long	267691816
	.global D2
	.align 8
	.type	D2, #object
	.size	D2, 8
D2:
	.long	1062171920
	.long	1297423721
	.global D1
	.align 8
	.type	D1, #object
	.size	D1, 8
D1:
	.long	1067743969
	.long	1125352308
	.global C8
	.align 8
	.type	C8, #object
	.size	C8, 8
C8:
	.long	1057266947
	.long	4261720527
	.global C7
	.align 8
	.type	C7, #object
	.size	C7, 8
C7:
	.long	1059504247
	.long	3356966714
	.global C6
	.align 8
	.type	C6, #object
	.size	C6, 8
C6:
	.long	1062671128
	.long	2128317445
	.global C5
	.align 8
	.type	C5, #object
	.size	C5, 8
C5:
	.long	1065422234
	.long	1255739916
	.global C4
	.align 8
	.type	C4, #object
	.size	C4, 8
C4:
	.long	1067799899
	.long	2121880904
	.global C3
	.align 8
	.type	C3, #object
	.size	C3, 8
C3:
	.long	1069897048
	.long	2085054741
	.global C2
	.align 8
	.type	C2, #object
	.size	C2, 8
C2:
	.long	1071644671
	.long	3425412280
	.global C1
	.align 8
	.type	C1, #object
	.size	C1, 8
C1:
	.long	1072693247
	.long	4265063394
	.global C0
	.align 8
	.type	C0, #object
	.size	C0, 8
C0:
	.long	1072693248
	.long	0
	.global B6
	.align 8
	.type	B6, #object
	.size	B6, 8
B6:
	.long	1042372530
	.long	1977554986
	.global B5
	.align 8
	.type	B5, #object
	.size	B5, 8
B5:
	.long	-1097696333
	.long	3565017998
	.global B4
	.align 8
	.type	B4, #object
	.size	B4, 8
B4:
	.long	1056571797
	.long	673459639
	.global B3
	.align 8
	.type	B3, #object
	.size	B3, 8
B3:
	.long	-1084833429
	.long	4293354774
	.global B2
	.align 8
	.type	B2, #object
	.size	B2, 8
B2:
	.long	1067799893
	.long	1428750884
	.global B1
	.align 8
	.type	B1, #object
	.size	B1, 8
B1:
	.long	-1075838977
	.long	4294934870
	.global B0
	.align 8
	.type	B0, #object
	.size	B0, 8
B0:
	.long	1072693248
	.long	0
	.global A6
	.align 8
	.type	A6, #object
	.size	A6, 8
A6:
	.long	1038519799
	.long	1378468262
	.global A5
	.align 8
	.type	A5, #object
	.size	A5, 8
A5:
	.long	1046145882
	.long	2365105190
	.global A4
	.align 8
	.type	A4, #object
	.size	A4, 8
A4:
	.long	1053236722
	.long	2225747302
	.global A3
	.align 8
	.type	A3, #object
	.size	A3, 8
A3:
	.long	1059717536
	.long	1068616305
	.global A2
	.align 8
	.type	A2, #object
	.size	A2, 8
A2:
	.long	1065423121
	.long	289073571
	.global A1
	.align 8
	.type	A1, #object
	.size	A1, 8
A1:
	.long	-1077586603
	.long	1431672581
	.global A0
	.align 8
	.type	A0, #object
	.size	A0, 8
A0:
	.long	1072693248
	.long	0
	.common	pierr,8,8
	.common	scale,8,8
	.common	piprg,8,8
	.common	piref,8,8
	.common	five,8,8
	.common	four,8,8
	.common	three,8,8
	.common	two,8,8
	.common	one,8,8
	.common	sd,8,8
	.common	sc,8,8
	.common	sb,8,8
	.common	sa,8,8
	.common	T,288,8
	.common	TLimit,8,8
	.common	TimeArray,24,8
	.common	nulltime,8,8
	.ident	"GCC: (Buildroot 2014.08-gfff9e93) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
