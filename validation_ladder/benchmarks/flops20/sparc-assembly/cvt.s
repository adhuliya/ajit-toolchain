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
	ld	[%fp+92], %o5
	ldd	[%fp-8], %f10
	cmp	%i2, 0
	bl	.L3
	 mov	0, %o7
	cmp	%i2, 78
	ble	.L56
	 mov	78, %o7
.L3:
	sethi	%hi(.LC0), %g2
	ldd	[%g2+%lo(.LC0)], %f8
	fcmped	%f10, %f8
	nop
	fbl	.L4
	 mov	1, %g1
	st	%g0, [%i4]
.L5:
	fdtoi	%f10, %f0
	ldd	[%g2+%lo(.LC0)], %f12
	fitod	%f0, %f20
	fcmpd	%f20, %f12
	nop
	fbe	.L6
	 fsubd	%f10, %f20, %f10
	add	%i5, 80, %i1
	sethi	%hi(.LC1), %i0
	sethi	%hi(.LC2), %i2
	sethi	%hi(.LC0), %i4
	mov	%i1, %g1
	mov	0, %g4
	ldd	[%i0+%lo(.LC1)], %f14
	ldd	[%i2+%lo(.LC2)], %f18
	ldd	[%i4+%lo(.LC0)], %f4
.L7:
	fdivd	%f20, %f14, %f6
	fdtoi	%f6, %f1
	fitod	%f1, %f20
	fsubd	%f6, %f20, %f22
	faddd	%f22, %f18, %f24
	fmuld	%f24, %f14, %f12
	fdtoi	%f12, %f3
	st	%f3, [%fp-12]
	add	%g1, -1, %g1
	ld	[%fp-12], %g2
	add	%g2, 48, %g3
	stb	%g3, [%g1]
	fcmpd	%f20, %f4
	nop
	fbne	.L7
	 add	%g4, 1, %g4
	cmp	%i1, %g1
	bleu	.L8
	 mov	%i5, %g2
	add	%g1, 4, %i0
	cmp	%i5, %i0
	add	%i5, 4, %i2
	subx	%g0, -1, %i4
	cmp	%g1, %i2
	subx	%g0, -1, %g3
	sub	%i5, %g1, %o3
	or	%i4, %g3, %i4
	add	%o3, 80, %o3
	mov	%g1, %g2
	srl	%o3, 2, %i0
	mov	1, %g3
	cmp	%o3, 3
	bgu	.L10
	 sll	%i0, 2, %o4
	mov	0, %g3
.L10:
	or	%g1, %i5, %i2
	and	%i2, 3, %i2
	subcc	%g0, %i2, %g0
	and	%i4, %g3, %g3
	subx	%g0, -1, %i4
	andcc	%g3, %i4, %g0
	be	.L37
	 cmp	%o4, 0
	be	.L46
	 mov	%i5, %i2
	mov	0, %g3
	mov	0, %i4
.L11:
	ld	[%g1+%g3], %i2
	st	%i2, [%i5+%g3]
	add	%i4, 1, %i4
	cmp	%i0, %i4
	bgu	.L11
	 add	%g3, 4, %g3
	add	%i5, %o4, %i2
	cmp	%o3, %o4
	be	.L12
	 add	%g1, %o4, %g1
.L46:
	ldub	[%g1], %i0
	stb	%i0, [%i2]
	add	%g1, 1, %g1
	cmp	%i1, %g1
	bgu	.L46
	 add	%i2, 1, %i2
.L12:
	sub	%i1, %g2, %i1
	add	%i5, %i1, %g2
.L8:
	cmp	%o5, 0
	bne	.L17
	 add	%i5, %o7, %g1
	add	%g1, %g4, %g1
.L17:
	cmp	%g1, %i5
	blu	.L18
	 st	%g4, [%i3]
	cmp	%g2, %g1
	bgu	.L20
	 add	%i5, 80, %g4
	sethi	%hi(.LC1), %i4
	cmp	%g2, %g4
	bgeu	.L20
	 or	%i4, %lo(.LC1), %g3
	b	.L45
	 ldd	[%g3], %f26
.L57:
	cmp	%g2, %g4
	be	.L61
	 cmp	%g1, %g4
.L45:
	fmuld	%f10, %f26, %f28
	fdtoi	%f28, %f5
	fitod	%f5, %f30
	fdtoi	%f30, %f7
	st	%f7, [%fp-12]
	ld	[%fp-12], %i0
	add	%i0, 48, %i2
	stb	%i2, [%g2]
	add	%g2, 1, %g2
	cmp	%g1, %g2
	bgeu	.L57
	 fsubd	%f28, %f30, %f10
.L20:
	cmp	%g1, %g4
.L61:
	bgeu	.L58
	 mov	%g1, %g2
	ldub	[%g1], %i1
	add	%i1, 5, %g3
	stb	%g3, [%g1]
	mov	48, %g4
	cmp	%o5, 0
	be	.L53
	 mov	49, %i4
.L54:
	sll	%g3, 24, %i2
	sra	%i2, 24, %i1
	cmp	%i1, 57
	ble,a	.L26
	 mov	%g1, %g2
	cmp	%i5, %g2
.L62:
	blu	.L27
	 stb	%g4, [%g2]
	stb	%i4, [%g2]
	ld	[%i3], %g3
	add	%g3, 1, %i0
	st	%i0, [%i3]
	ldub	[%g2], %g3
	sll	%g3, 24, %i2
	sra	%i2, 24, %i1
	cmp	%i1, 57
	bg	.L62
	 cmp	%i5, %g2
	mov	%g1, %g2
.L26:
	stb	%g0, [%g2]
.L60:
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L6:
	fcmped	%f10, %f12
	nop
	fbule	.L52
	 nop
	sethi	%hi(.LC1), %g3
	sethi	%hi(.LC3), %g1
	ldd	[%g3+%lo(.LC1)], %f2
	ldd	[%g1+%lo(.LC3)], %f8
	fmuld	%f10, %f2, %f12
	mov	0, %g4
	ldd	[%g3+%lo(.LC1)], %f16
	fmovs	%f8, %f14
	fcmped	%f12, %f8
	nop
	fbl	.L16
	 fmovs	%f9, %f15
	b	.L8
	 mov	%i5, %g2
.L40:
	fmovs	%f8, %f12
	fmovs	%f9, %f13
.L16:
	fmuld	%f12, %f16, %f8
	fcmped	%f8, %f14
	nop
	fbl	.L40
	 add	%g4, -1, %g4
	mov	%i5, %g2
	fmovs	%f12, %f10
	b	.L8
	 fmovs	%f13, %f11
.L30:
	stb	%i4, [%g1]
	ld	[%i3], %i2
	add	%i2, 1, %i1
	cmp	%g2, %i5
	bleu	.L32
	 st	%i1, [%i3]
	stb	%g4, [%g2]
.L32:
	add	%g2, 1, %g2
	ldub	[%g1], %g3
.L53:
	sll	%g3, 24, %g3
	sra	%g3, 24, %i0
	cmp	%i0, 57
	ble,a	.L60
	 stb	%g0, [%g2]
.L33:
	cmp	%g1, %i5
	bleu	.L30
	 stb	%g4, [%g1]
	ldub	[%g1-1], %i0
	add	%i0, 1, %g3
	stb	%g3, [%g1-1]
	sll	%g3, 24, %g3
	sra	%g3, 24, %i0
	cmp	%i0, 57
	bg	.L33
	 add	%g1, -1, %g1
	b	.L60
	 stb	%g0, [%g2]
.L27:
	ldub	[%g2-1], %i2
	add	%i2, 1, %g3
	stb	%g3, [%g2-1]
	b	.L54
	 add	%g2, -1, %g2
.L18:
	stb	%g0, [%i5]
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L4:
	fnegs	%f10, %f10
	b	.L5
	 st	%g1, [%i4]
.L58:
	stb	%g0, [%i5+79]
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L56:
	b	.L3
	 mov	%i2, %o7
.L52:
	mov	%i5, %g2
	b	.L8
	 mov	0, %g4
.L37:
	b	.L46
	 mov	%i5, %i2
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
	.ident	"GCC: (Buildroot 2014.08-gfff9e93) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
