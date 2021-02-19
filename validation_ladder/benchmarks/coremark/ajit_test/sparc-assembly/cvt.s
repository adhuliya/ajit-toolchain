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
	ble	.L57
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
	fdtoi	%f10, %f8
	ldd	[%g2+%lo(.LC0)], %f12
	fitod	%f8, %f8
	fcmpd	%f8, %f12
	nop
	fbe	.L6
	 fsubd	%f10, %f8, %f10
	sethi	%hi(.LC2), %g2
	add	%i5, 80, %i1
	sethi	%hi(.LC1), %g3
	ldd	[%g2+%lo(.LC2)], %f18
	mov	%i1, %g1
	sethi	%hi(.LC0), %g2
	mov	0, %g4
	ldd	[%g3+%lo(.LC1)], %f14
	ldd	[%g2+%lo(.LC0)], %f16
.L7:
	fdivd	%f8, %f14, %f12
	fdtoi	%f12, %f8
	fitod	%f8, %f8
	fsubd	%f12, %f8, %f12
	faddd	%f12, %f18, %f12
	fmuld	%f12, %f14, %f12
	fdtoi	%f12, %f12
	st	%f12, [%fp-12]
	add	%g1, -1, %g1
	ld	[%fp-12], %g2
	add	%g2, 48, %g3
	stb	%g3, [%g1]
	fcmpd	%f8, %f16
	nop
	fbne	.L7
	 add	%g4, 1, %g4
	cmp	%i1, %g1
	bleu	.L8
	 mov	%i5, %g2
	add	%g1, 4, %g2
	cmp	%i5, %g2
	add	%i5, 4, %g2
	subx	%g0, -1, %i4
	cmp	%g1, %g2
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
	be	.L37
	 mov	0, %i4
	mov	0, %g3
.L11:
	ld	[%g1+%g3], %i2
	st	%i2, [%i5+%g3]
	add	%i4, 1, %i4
	cmp	%i0, %i4
	bgu	.L11
	 add	%g3, 4, %g3
	add	%i5, %o4, %g3
	cmp	%o3, %o4
	be	.L12
	 add	%g1, %o4, %g1
.L46:
	ldub	[%g1], %i4
	stb	%i4, [%g3]
	add	%g1, 1, %g1
	cmp	%i1, %g1
	bgu	.L46
	 add	%g3, 1, %g3
.L12:
	sub	%i1, %g2, %g2
	add	%i5, %g2, %g2
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
	sethi	%hi(.LC1), %g3
	cmp	%g2, %g4
	bgeu	.L20
	 or	%g3, %lo(.LC1), %g3
	b	.L45
	 ldd	[%g3], %f12
.L58:
	cmp	%g2, %g4
	be	.L63
	 cmp	%g1, %g4
.L45:
	fmuld	%f10, %f12, %f10
	fdtoi	%f10, %f8
	fitod	%f8, %f8
	fdtoi	%f8, %f14
	st	%f14, [%fp-12]
	ld	[%fp-12], %g3
	add	%g3, 48, %g3
	stb	%g3, [%g2]
	add	%g2, 1, %g2
	cmp	%g1, %g2
	bgeu	.L58
	 fsubd	%f10, %f8, %f10
.L20:
	cmp	%g1, %g4
.L63:
	bgeu	.L59
	 cmp	%o5, 0
	ldub	[%g1], %g3
	add	%g3, 5, %g3
	stb	%g3, [%g1]
	be	.L60
	 mov	%g1, %g2
	mov	48, %i4
	mov	49, %g4
.L54:
	sll	%g3, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 57
	ble,a	.L26
	 mov	%g1, %g2
	cmp	%i5, %g2
.L64:
	blu,a	.L27
	 ldub	[%g2-1], %g3
	stb	%g4, [%g2]
	ld	[%i3], %g3
	add	%g3, 1, %g3
	st	%g3, [%i3]
	ldub	[%g2], %g3
	sll	%g3, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 57
	bg	.L64
	 cmp	%i5, %g2
	mov	%g1, %g2
.L26:
	stb	%g0, [%g2]
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L6:
	fcmped	%f10, %f12
	nop
	fbule	.L52
	 nop
	sethi	%hi(.LC1), %g3
	sethi	%hi(.LC3), %g1
	ldd	[%g3+%lo(.LC1)], %f12
	ldd	[%g1+%lo(.LC3)], %f8
	fmuld	%f10, %f12, %f12
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
.L18:
	stb	%g0, [%i5]
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L4:
	fnegs	%f10, %f10
	b	.L5
	 st	%g1, [%i4]
.L59:
	stb	%g0, [%i5+79]
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L57:
	b	.L3
	 mov	%i2, %o7
.L60:
	mov	48, %g4
	mov	49, %i4
.L53:
	sll	%g3, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 57
	ble	.L26
	 cmp	%g1, %i5
	bleu,a	.L65
	 stb	%i4, [%g1]
	ldub	[%g1-1], %g3
.L66:
	stb	%g4, [%g1]
	add	%g3, 1, %g3
	stb	%g3, [%g1-1]
	sll	%g3, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 57
	ble	.L26
	 add	%g1, -1, %g1
	cmp	%g1, %i5
	bgu,a	.L66
	 ldub	[%g1-1], %g3
	stb	%i4, [%g1]
.L65:
	ld	[%i3], %g3
	add	%g3, 1, %g3
	cmp	%g2, %i5
	bleu	.L32
	 st	%g3, [%i3]
	stb	%g4, [%g2]
.L32:
	add	%g2, 1, %g2
	b	.L53
	 ldub	[%g1], %g3
.L52:
	mov	%i5, %g2
	b	.L8
	 mov	0, %g4
.L27:
	stb	%i4, [%g2]
	add	%g3, 1, %g3
	stb	%g3, [%g2-1]
	b	.L54
	 add	%g2, -1, %g2
.L37:
	b	.L46
	 mov	%i5, %g3
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
	fitod	%f8, %f8
	fsubd	%f0, %f8, %f0
	jmp	%o7+8
	 std	%f8, [%o2]
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
