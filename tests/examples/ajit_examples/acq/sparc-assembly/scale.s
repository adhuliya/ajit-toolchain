	.file	"scale.c"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	1075388923
	.long	1413754136
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC1:
	.long	0
	.align 4
.LC2:
	.long	1048576000
	.align 4
.LC3:
	.long	1061158912
	.section	".text"
	.align 4
	.global mycos
	.type	mycos, #function
	.proc	04
mycos:
	add	%sp, -80, %sp
	sethi	%hi(.LC0), %g1
	st	%o0, [%sp+76]
	ld	[%sp+76], %f8
	ldd	[%g1+%lo(.LC0)], %f0
	fstod	%f8, %f10
	sethi	%hi(.LC1), %g1
	fdivd	%f10, %f0, %f8
	ld	[%g1+%lo(.LC1)], %f4
	fdtos	%f8, %f1
	fstoi	%f1, %f9
	fitos	%f9, %f2
	fsubs	%f1, %f2, %f3
	fcmpes	%f3, %f4
	nop
	fbule	.L2
	 sethi	%hi(.LC2), %g1
	ld	[%g1+%lo(.LC2)], %f5
	fcmpes	%f3, %f5
	nop
	fbl	.L4
	 mov	1, %o0
.L2:
	ld	[%g1+%lo(.LC2)], %f6
	fcmpes	%f3, %f6
	nop
	fbg	.L13
	 sethi	%hi(.LC3), %g1
.L11:
	mov	1, %o0
.L4:
	jmp	%o7+8
	 sub	%sp, -80, %sp
.L13:
	ld	[%g1+%lo(.LC3)], %f7
	fcmpes	%f3, %f7
	nop
	fbuge	.L11
	 nop
	b	.L4
	 mov	-1, %o0
	.size	mycos, .-mycos
	.section	.rodata.cst8
	.align 8
.LC4:
	.long	1075388923
	.long	1413754136
	.section	.rodata.cst4
	.align 4
.LC5:
	.long	0
	.align 4
.LC6:
	.long	1048576000
	.align 4
.LC7:
	.long	1061158912
	.section	".text"
	.align 4
	.global scale
	.type	scale, #function
	.proc	020
scale:
	add	%o0, %o1, %o1
	add	%sp, -80, %sp
	st	%o1, [%sp+76]
	ld	[%sp+76], %f10
	sethi	%hi(.LC4), %g2
	fitod	%f10, %f12
	ldd	[%g2+%lo(.LC4)], %f8
	sethi	%hi(.LC6), %g4
	sethi	%hi(.LC5), %g3
	sethi	%hi(23552), %o5
	fmuld	%f12, %f8, %f0
	mov	0, %g1
	or	%g4, %lo(.LC6), %o0
	fmovs	%f8, %f10
	fmovs	%f9, %f11
	ld	[%g3+%lo(.LC5)], %f14
	sethi	%hi(.LC7), %o4
	or	%o5, 1000, %o1
	ld	[%o2+%g1], %f8
.L28:
	fstod	%f8, %f2
	fmuld	%f2, %f0, %f8
	fdtos	%f8, %f3
	fstod	%f3, %f4
	fdivd	%f4, %f10, %f8
	fdtos	%f8, %f5
	fstoi	%f5, %f9
	fitos	%f9, %f6
	fsubs	%f5, %f6, %f7
	fcmpes	%f7, %f14
	nop
	fbule	.L15
	 nop
	ld	[%o0], %f13
	fcmpes	%f7, %f13
	nop
	fbl	.L17
	 mov	1, %g2
.L15:
	ld	[%o0], %f15
	fcmpes	%f7, %f15
	nop
	fbule	.L26
	 nop
	ld	[%o4+%lo(.LC7)], %f16
	fcmpes	%f7, %f16
	nop
	fbuge	.L26
	 mov	-1, %g2
.L17:
	ld	[%o3+%g1], %g4
	smul	%g4, %g2, %g3
	st	%g3, [%o3+%g1]
	add	%g1, 4, %g1
	cmp	%g1, %o1
	bne,a	.L28
	 ld	[%o2+%g1], %f8
.L27:
	jmp	%o7+8
	 sub	%sp, -80, %sp
.L26:
	ld	[%o3+%g1], %g4
	mov	1, %g2
	smul	%g4, %g2, %g3
	st	%g3, [%o3+%g1]
	add	%g1, 4, %g1
	cmp	%g1, %o1
	bne,a	.L28
	 ld	[%o2+%g1], %f8
	b,a	.L27
	.size	scale, .-scale
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
