	.file	"cvt.c"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	0
	.align 8
.LC1:
	.long	1076101120
	.long	0
	.align 8
.LC2:
	.long	1067366481
	.long	3951369912
	.align 8
.LC3:
	.long	1072693248
	.long	0
	.section	".text"
	.align 4
	.type	cvt, #function
	.proc	0102
cvt:
	save	%sp, -112, %sp
	std	%i0, [%fp-8]
	ld	[%fp+92], %o7
	ldd	[%fp-8], %f10
	cmp	%i2, 0
	bl	.L3
	 mov	0, %g2
	cmp	%i2, 78
	ble	.L44
	 mov	78, %g2
.L3:
	sethi	%hi(.LC0), %g1
	ldd	[%g1+%lo(.LC0)], %f8
	fcmped	%f10, %f8
	nop
	fbl	.L4
	 mov	1, %g3
	st	%g0, [%i4]
.L5:
	fdtoi	%f10, %f0
	ldd	[%g1+%lo(.LC0)], %f12
	fitod	%f0, %f20
	fcmpd	%f20, %f12
	nop
	fbe	.L6
	 fsubd	%f10, %f20, %f10
	sethi	%hi(.LC2), %g1
	add	%i5, 80, %o5
	sethi	%hi(.LC1), %g4
	ldd	[%g1+%lo(.LC2)], %f18
	mov	%o5, %i4
	sethi	%hi(.LC0), %g1
	mov	0, %g3
	ldd	[%g4+%lo(.LC1)], %f14
	ldd	[%g1+%lo(.LC0)], %f4
.L7:
	fdivd	%f20, %f14, %f6
	fdtoi	%f6, %f1
	fitod	%f1, %f20
	fsubd	%f6, %f20, %f22
	faddd	%f22, %f18, %f24
	fmuld	%f24, %f14, %f12
	fdtoi	%f12, %f3
	st	%f3, [%fp-12]
	add	%i4, -1, %i4
	ld	[%fp-12], %g1
	add	%g1, 48, %i0
	stb	%i0, [%i4]
	fcmpd	%f20, %f4
	nop
	fbne	.L7
	 add	%g3, 1, %g3
	cmp	%o5, %i4
	bleu	.L8
	 mov	%i5, %g1
	add	%i5, 79, %g1
	mov	%i4, %i1
	b	.L10
	 mov	%i5, %i2
.L9:
	ldub	[%i1+1], %i0
	add	%i1, 1, %i1
.L10:
	stb	%i0, [%i2]
	cmp	%i1, %g1
	bne	.L9
	 add	%i2, 1, %i2
	sub	%o5, %i4, %g1
	add	%i5, %g1, %g1
.L8:
	cmp	%o7, 0
	bne	.L14
	 add	%i5, %g2, %g2
	add	%g2, %g3, %g2
.L14:
	cmp	%g2, %i5
	blu	.L15
	 st	%g3, [%i3]
	cmp	%g1, %g2
	bgu	.L17
	 add	%i5, 80, %i1
	sethi	%hi(.LC1), %g3
	cmp	%g1, %i1
	bgeu	.L17
	 or	%g3, %lo(.LC1), %g4
	b	.L36
	 ldd	[%g4], %f26
.L45:
	cmp	%g1, %i1
	be	.L48
	 cmp	%g2, %i1
.L36:
	fmuld	%f10, %f26, %f28
	fdtoi	%f28, %f5
	fitod	%f5, %f30
	fdtoi	%f30, %f7
	st	%f7, [%fp-12]
	ld	[%fp-12], %i4
	add	%i4, 48, %i0
	stb	%i0, [%g1]
	add	%g1, 1, %g1
	cmp	%g2, %g1
	bgeu	.L45
	 fsubd	%f28, %f30, %f10
.L17:
	cmp	%g2, %i1
.L48:
	bgeu	.L46
	 mov	%g2, %g4
	ldub	[%g2], %i2
	add	%i2, 5, %i1
	mov	48, %g3
	mov	%i1, %g1
	stb	%i1, [%g2]
	mov	49, %i4
.L41:
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 57
	ble,a	.L49
	 stb	%g0, [%g4]
.L26:
	cmp	%g2, %i5
	bleu	.L22
	 stb	%g3, [%g2]
	ldub	[%g2-1], %g1
	add	%g1, 1, %g1
	stb	%g1, [%g2-1]
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 57
	bg	.L26
	 add	%g2, -1, %g2
	stb	%g0, [%g4]
.L49:
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L6:
	fcmped	%f10, %f12
	nop
	fbule	.L40
	 nop
	sethi	%hi(.LC1), %i2
	sethi	%hi(.LC3), %g1
	ldd	[%i2+%lo(.LC1)], %f2
	ldd	[%g1+%lo(.LC3)], %f8
	fmuld	%f10, %f2, %f12
	mov	0, %g3
	ldd	[%i2+%lo(.LC1)], %f16
	fmovs	%f8, %f14
	fcmped	%f12, %f8
	nop
	fbl	.L13
	 fmovs	%f9, %f15
	b	.L8
	 mov	%i5, %g1
.L32:
	fmovs	%f8, %f12
	fmovs	%f9, %f13
.L13:
	fmuld	%f12, %f16, %f8
	fcmped	%f8, %f14
	nop
	fbl	.L32
	 add	%g3, -1, %g3
	mov	%i5, %g1
	fmovs	%f12, %f10
	b	.L8
	 fmovs	%f13, %f11
.L22:
	stb	%i4, [%g2]
	ld	[%i3], %g1
	add	%g1, 1, %g1
	cmp	%o7, 0
	bne	.L42
	 st	%g1, [%i3]
	cmp	%g4, %i5
	bgu,a	.L25
	 stb	%g3, [%g4]
.L25:
	add	%g4, 1, %g4
.L42:
	b	.L41
	 ldub	[%g2], %g1
.L15:
	stb	%g0, [%i5]
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L4:
	fnegs	%f10, %f10
	b	.L5
	 st	%g3, [%i4]
.L46:
	stb	%g0, [%i5+79]
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L44:
	b	.L3
	 mov	%i2, %g2
.L40:
	mov	%i5, %g1
	b	.L8
	 mov	0, %g3
	.size	cvt, .-cvt
	.align 4
	.global __modf
	.type	__modf, #function
	.proc	07
__modf:
	add	%sp, -80, %sp
	std	%o0, [%sp+72]
	ldd	[%sp+72], %f0
	sub	%sp, -80, %sp
	fdtoi	%f0, %f8
	fitod	%f8, %f2
	fsubd	%f0, %f2, %f0
	jmp	%o7+8
	 std	%f2, [%o2]
	.size	__modf, .-__modf
	.align 4
	.global ecvt
	.type	ecvt, #function
	.proc	0102
ecvt:
	save	%sp, -104, %sp
	mov	1, %g1
	mov	%i0, %o0
	mov	%i1, %o1
	st	%g1, [%sp+92]
	mov	%i2, %o2
	mov	%i3, %o3
	mov	%i4, %o4
	sethi	%hi(CVTBUF), %o5
	call	cvt, 0
	 or	%o5, %lo(CVTBUF), %o5
	jmp	%i7+8
	 restore %g0, %o0, %o0
	.size	ecvt, .-ecvt
	.align 4
	.global ecvtbuf
	.type	ecvtbuf, #function
	.proc	0102
ecvtbuf:
	save	%sp, -104, %sp
	mov	1, %g1
	mov	%i0, %o0
	mov	%i1, %o1
	st	%g1, [%sp+92]
	mov	%i2, %o2
	mov	%i3, %o3
	mov	%i4, %o4
	call	cvt, 0
	 mov	%i5, %o5
	jmp	%i7+8
	 restore %g0, %o0, %o0
	.size	ecvtbuf, .-ecvtbuf
	.align 4
	.global fcvt
	.type	fcvt, #function
	.proc	0102
fcvt:
	save	%sp, -104, %sp
	sethi	%hi(CVTBUF), %o5
	st	%g0, [%sp+92]
	mov	%i0, %o0
	mov	%i1, %o1
	mov	%i2, %o2
	mov	%i3, %o3
	mov	%i4, %o4
	call	cvt, 0
	 or	%o5, %lo(CVTBUF), %o5
	jmp	%i7+8
	 restore %g0, %o0, %o0
	.size	fcvt, .-fcvt
	.align 4
	.global fcvtbuf
	.type	fcvtbuf, #function
	.proc	0102
fcvtbuf:
	save	%sp, -104, %sp
	st	%g0, [%sp+92]
	mov	%i0, %o0
	mov	%i1, %o1
	mov	%i2, %o2
	mov	%i3, %o3
	mov	%i4, %o4
	call	cvt, 0
	 mov	%i5, %o5
	jmp	%i7+8
	 restore %g0, %o0, %o0
	.size	fcvtbuf, .-fcvtbuf
	.local	CVTBUF
	.common	CVTBUF,80,8
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
