	.file	"math_func.c"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	0
	.section	.text.xx__fabs,"ax",@progbits
	.align 4
	.global xx__fabs
	.type	xx__fabs, #function
	.proc	07
xx__fabs:
	add	%sp, -80, %sp
	std	%o0, [%sp+72]
	sethi	%hi(.LC0), %g1
	ldd	[%sp+72], %f0
	ldd	[%g1+%lo(.LC0)], %f8
	fcmped	%f0, %f8
	nop
	fbule,a	.L2
	 fsubd	%f8, %f0, %f0
.L2:
	jmp	%o7+8
	 sub	%sp, -80, %sp
	.size	xx__fabs, .-xx__fabs
	.section	.rodata.cst8
	.align 8
.LC1:
	.long	0
	.long	0
	.section	.text.xx__fmod,"ax",@progbits
	.align 4
	.global xx__fmod
	.type	xx__fmod, #function
	.proc	07
xx__fmod:
	add	%sp, -80, %sp
	std	%o0, [%sp+72]
	ldd	[%sp+72], %f0
	std	%o2, [%sp+72]
	sethi	%hi(.LC1), %g1
	ldd	[%sp+72], %f8
	ldd	[%g1+%lo(.LC1)], %f10
	fmovs	%f0, %f12
	fcmped	%f0, %f10
	nop
	fbule	.L11
	 fmovs	%f1, %f13
	ldd	[%g1+%lo(.LC1)], %f14
	fmovs	%f8, %f10
	fcmped	%f8, %f14
	nop
	fbule	.L12
	 fmovs	%f9, %f11
.L7:
	fcmped	%f12, %f10
	nop
	fbl	.L8
	 nop
	fdivd	%f0, %f8, %f10
	fdtoi	%f10, %f10
	fitod	%f10, %f10
	fmuld	%f10, %f8, %f8
	fsubd	%f0, %f8, %f0
.L8:
	jmp	%o7+8
	 sub	%sp, -80, %sp
.L11:
	fsubd	%f10, %f0, %f12
	ldd	[%g1+%lo(.LC1)], %f14
	fmovs	%f8, %f10
	fcmped	%f8, %f14
	nop
	fbg	.L7
	 fmovs	%f9, %f11
.L12:
	b	.L7
	 fsubd	%f14, %f8, %f10
	.size	xx__fmod, .-xx__fmod
	.section	.rodata.cst8
	.align 8
.LC2:
	.long	1072693248
	.long	0
	.align 8
.LC3:
	.long	0
	.long	0
	.section	.text.xx__pow,"ax",@progbits
	.align 4
	.global xx__pow
	.type	xx__pow, #function
	.proc	07
xx__pow:
	add	%sp, -80, %sp
	std	%o0, [%sp+72]
	sethi	%hi(.LC3), %g1
	ldd	[%sp+72], %f8
	ldd	[%g1+%lo(.LC3)], %f10
	fmovs	%f10, %f0
	fcmpd	%f8, %f10
	nop
	fbe	.L14
	 fmovs	%f11, %f1
	sethi	%hi(.LC2), %g2
	cmp	%o2, 0
	be	.L14
	 ldd	[%g2+%lo(.LC2)], %f0
	cmp	%o2, 0
	bl	.L24
	 mov	0, %g1
.L20:
	add	%g1, 1, %g1
	cmp	%o2, %g1
	bg	.L20
	 fmuld	%f0, %f8, %f0
.L14:
	jmp	%o7+8
	 sub	%sp, -80, %sp
.L24:
	sub	%g0, %o2, %o2
	fmovs	%f0, %f10
	fmovs	%f1, %f11
.L16:
	add	%g1, 1, %g1
	cmp	%o2, %g1
	bg	.L16
	 fmuld	%f10, %f8, %f10
	ldd	[%g2+%lo(.LC2)], %f0
	sub	%sp, -80, %sp
	jmp	%o7+8
	 fdivd	%f0, %f10, %f0
	.size	xx__pow, .-xx__pow
	.section	.rodata.cst8
	.align 8
.LC4:
	.long	1072693248
	.long	0
	.section	.text.xx__pow_opt,"ax",@progbits
	.align 4
	.global xx__pow_opt
	.type	xx__pow_opt, #function
	.proc	07
xx__pow_opt:
	save	%sp, -136, %sp
	std	%i0, [%fp-40]
	cmp	%i2, 0
	bl	.L62
	 ldd	[%fp-40], %f8
	sethi	%hi(.LC4), %g1
	cmp	%i2, 0
	be	.L78
	 ldd	[%g1+%lo(.LC4)], %f0
	cmp	%i2, 1
	be	.L48
	 cmp	%i2, 2
	be	.L63
	 cmp	%i2, 3
	be	.L64
	 cmp	%i2, 4
	be	.L65
	 sra	%i2, 2, %g1
	cmp	%g1, 0
	bl	.L66
	 and	%i2, 3, %i2
.L31:
	sethi	%hi(.LC4), %g2
	cmp	%g1, 0
	be	.L33
	 ldd	[%g2+%lo(.LC4)], %f0
	cmp	%g1, 1
	be	.L67
	 cmp	%g1, 2
	be	.L68
	 cmp	%g1, 3
	be	.L69
	 cmp	%g1, 4
	fmovs	%f8, %f12
	be	.L70
	 fmovs	%f9, %f13
.L32:
	sra	%g1, 2, %o2
	cmp	%o2, 0
	bl	.L71
	 and	%g1, 3, %i5
	sethi	%hi(.LC4), %g1
	cmp	%o2, 0
	be	.L39
	 ldd	[%g1+%lo(.LC4)], %f10
	cmp	%o2, 1
	be	.L72
	 cmp	%o2, 2
	be	.L73
	 cmp	%o2, 3
	be	.L74
	 cmp	%o2, 4
	fmovs	%f12, %f14
	bne	.L38
	 fmovs	%f13, %f15
	fmuld	%f12, %f12, %f10
	fmuld	%f10, %f10, %f10
	fmuld	%f10, %f10, %f10
	fmuld	%f10, %f10, %f10
.L39:
	cmp	%i5, 0
	bne,a	.L44
	 std	%f12, [%fp-40]
	fmuld	%f10, %f10, %f0
	fmuld	%f0, %f0, %f0
.L33:
	cmp	%i2, 0
	be	.L78
	 cmp	%i2, 1
	be	.L45
	 cmp	%i2, 2
	be,a	.L45
	 fmuld	%f8, %f8, %f8
	fmuld	%f8, %f8, %f10
	fmuld	%f8, %f10, %f8
.L45:
	fmuld	%f8, %f0, %f0
.L78:
	jmp	%i7+8
	 restore
.L48:
	fmovs	%f8, %f0
	fmovs	%f9, %f1
	jmp	%i7+8
	 restore
.L62:
	sethi	%hi(.LC4), %g1
	sub	%g0, %i2, %i2
	ldd	[%g1+%lo(.LC4)], %f10
	sra	%i2, 2, %g1
	fdivd	%f10, %f8, %f8
	cmp	%g1, 0
	bge	.L31
	 and	%i2, 3, %i2
.L66:
	sethi	%hi(.LC4), %g2
	sub	%g0, %g1, %g1
	ldd	[%g2+%lo(.LC4)], %f12
	b	.L32
	 fdivd	%f12, %f8, %f12
.L44:
	std	%f8, [%fp-8]
	std	%f10, [%fp-16]
	ldd	[%fp-40], %o0
	mov	%i5, %o2
	call	xx__pow_opt, 0
	 add	%i3, 2, %o3
	ldd	[%fp-16], %f10
	ldd	[%fp-8], %f8
	fmuld	%f0, %f10, %f0
	fmuld	%f0, %f0, %f0
	b	.L33
	 fmuld	%f0, %f0, %f0
.L63:
	fmuld	%f8, %f8, %f0
	jmp	%i7+8
	 restore
.L64:
	fmuld	%f8, %f8, %f0
	fmuld	%f0, %f8, %f0
	jmp	%i7+8
	 restore
.L71:
	sethi	%hi(.LC4), %g1
	sub	%g0, %o2, %o2
	ldd	[%g1+%lo(.LC4)], %f14
	fdivd	%f14, %f12, %f14
.L38:
	std	%f14, [%fp-40]
	and	%o2, 3, %i1
	std	%f8, [%fp-8]
	std	%f12, [%fp-24]
	std	%f14, [%fp-32]
	add	%i3, 3, %i4
	ldd	[%fp-40], %o0
	sra	%o2, 2, %o2
	call	xx__pow_opt, 0
	 mov	%i4, %o3
	cmp	%i1, 0
	fmuld	%f0, %f0, %f0
	ldd	[%fp-8], %f8
	fmuld	%f0, %f0, %f10
	ldd	[%fp-24], %f12
	be	.L76
	 ldd	[%fp-32], %f14
	std	%f14, [%fp-40]
	std	%f8, [%fp-8]
	std	%f10, [%fp-16]
	std	%f12, [%fp-24]
	ldd	[%fp-40], %o0
	mov	%i1, %o2
	call	xx__pow_opt, 0
	 mov	%i4, %o3
	ldd	[%fp-16], %f10
	ldd	[%fp-24], %f12
	fmuld	%f10, %f0, %f0
	ldd	[%fp-8], %f8
	fmuld	%f0, %f0, %f10
	b	.L39
	 fmuld	%f10, %f10, %f10
.L65:
	fmuld	%f8, %f8, %f0
	fmuld	%f0, %f0, %f0
	jmp	%i7+8
	 restore
.L76:
	fmuld	%f10, %f10, %f10
	b	.L39
	 fmuld	%f10, %f10, %f10
.L67:
	fmuld	%f8, %f8, %f0
	b	.L33
	 fmuld	%f0, %f0, %f0
.L74:
	fmuld	%f12, %f12, %f10
	fmuld	%f12, %f10, %f10
	fmuld	%f10, %f10, %f10
	b	.L39
	 fmuld	%f10, %f10, %f10
.L68:
	fmuld	%f8, %f8, %f0
	fmuld	%f0, %f0, %f0
	b	.L33
	 fmuld	%f0, %f0, %f0
.L69:
	fmuld	%f8, %f8, %f0
	fmuld	%f8, %f0, %f0
	fmuld	%f0, %f0, %f0
	b	.L33
	 fmuld	%f0, %f0, %f0
.L70:
	fmuld	%f8, %f8, %f0
	fmuld	%f0, %f0, %f0
	fmuld	%f0, %f0, %f0
	b	.L33
	 fmuld	%f0, %f0, %f0
.L72:
	fmuld	%f12, %f12, %f10
	b	.L39
	 fmuld	%f10, %f10, %f10
.L73:
	fmuld	%f12, %f12, %f10
	fmuld	%f10, %f10, %f10
	b	.L39
	 fmuld	%f10, %f10, %f10
	.size	xx__pow_opt, .-xx__pow_opt
	.section	.rodata.cst8
	.align 8
.LC5:
	.long	1072693248
	.long	0
	.section	.text.xx__fact,"ax",@progbits
	.align 4
	.global xx__fact
	.type	xx__fact, #function
	.proc	07
xx__fact:
	add	%sp, -88, %sp
	std	%o0, [%sp+80]
	sethi	%hi(.LC5), %g2
	ldd	[%sp+80], %f10
	ldd	[%g2+%lo(.LC5)], %f12
	mov	1, %g1
	fmovs	%f12, %f8
	fmovs	%f13, %f9
	fmovs	%f8, %f0
	fcmped	%f10, %f12
	nop
	fbul	.L86
	 fmovs	%f13, %f1
	add	%g1, 1, %g1
.L87:
	st	%g1, [%sp+76]
	fmuld	%f0, %f8, %f0
	ld	[%sp+76], %f12
	fitod	%f12, %f8
	fcmped	%f8, %f10
	nop
	fble	.L87
	 add	%g1, 1, %g1
.L80:
	jmp	%o7+8
	 sub	%sp, -88, %sp
.L86:
	b	.L80
	 fmovs	%f12, %f0
	.size	xx__fact, .-xx__fact
	.section	.rodata.cst8
	.align 8
.LC6:
	.long	0
	.long	0
	.align 8
.LC7:
	.long	1072693248
	.long	0
	.align 8
.LC8:
	.long	1048238066
	.long	2596056904
	.section	.text.xx__cos_base,"ax",@progbits
	.align 4
	.global xx__cos_base
	.type	xx__cos_base, #function
	.proc	07
xx__cos_base:
	add	%sp, -88, %sp
	sethi	%hi(.LC7), %g3
	sethi	%hi(.LC6), %g2
	std	%o0, [%sp+80]
	ldd	[%sp+80], %f8
	ldd	[%g2+%lo(.LC6)], %f0
	fmovs	%f8, %f10
	fmovs	%f9, %f11
	mov	0, %g1
	fmuld	%f8, %f10, %f16
	mov	0, %g2
	ldd	[%g3+%lo(.LC7)], %f8
	sethi	%hi(.LC8), %g3
	fmovs	%f8, %f14
	fmovs	%f9, %f15
	b	.L91
	 ldd	[%g3+%lo(.LC8)], %f12
.L94:
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fsubd	%f0, %f8, %f0
	ld	[%sp+76], %f10
	fmuld	%f8, %f16, %f8
	fitod	%f10, %f10
	fdivd	%f14, %f10, %f10
	fmuld	%f8, %f10, %f8
	fcmped	%f8, %f12
	nop
	fbule	.L93
	 xor	%g2, 1, %g2
.L91:
	cmp	%g2, 0
	bne	.L94
	 add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	faddd	%f0, %f8, %f0
	ld	[%sp+76], %f10
	fmuld	%f8, %f16, %f8
	fitod	%f10, %f10
	fdivd	%f14, %f10, %f10
	fmuld	%f8, %f10, %f8
	fcmped	%f8, %f12
	nop
	fbg	.L91
	 xor	%g2, 1, %g2
.L93:
	jmp	%o7+8
	 sub	%sp, -88, %sp
	.size	xx__cos_base, .-xx__cos_base
	.section	.rodata.cst8
	.align 8
.LC9:
	.long	0
	.long	0
	.align 8
.LC10:
	.long	1048238066
	.long	2596056904
	.align 8
.LC11:
	.long	1072693248
	.long	0
	.section	.text.xx__sin_base,"ax",@progbits
	.align 4
	.global xx__sin_base
	.type	xx__sin_base, #function
	.proc	07
xx__sin_base:
	add	%sp, -88, %sp
	std	%o0, [%sp+80]
	sethi	%hi(.LC10), %g3
	ldd	[%sp+80], %f8
	ldd	[%g3+%lo(.LC10)], %f10
	fcmped	%f8, %f10
	nop
	fbule	.L104
	 fmuld	%f8, %f8, %f12
	sethi	%hi(.LC9), %g2
	sethi	%hi(.LC11), %g4
	ldd	[%g2+%lo(.LC9)], %f0
	mov	1, %g1
	mov	0, %g2
	ldd	[%g4+%lo(.LC11)], %f16
	fmovs	%f10, %f14
	b	.L100
	 fmovs	%f11, %f15
.L105:
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fsubd	%f0, %f8, %f0
	ld	[%sp+76], %f10
	fmuld	%f8, %f12, %f8
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f8, %f10, %f8
	fcmped	%f8, %f14
	nop
	fbule	.L96
	 xor	%g2, 1, %g2
.L100:
	cmp	%g2, 0
	bne	.L105
	 add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	faddd	%f0, %f8, %f0
	ld	[%sp+76], %f10
	fmuld	%f8, %f12, %f8
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f8, %f10, %f8
	fcmped	%f8, %f14
	nop
	fbg	.L100
	 xor	%g2, 1, %g2
.L96:
	jmp	%o7+8
	 sub	%sp, -88, %sp
.L104:
	sethi	%hi(.LC9), %g1
	b	.L96
	 ldd	[%g1+%lo(.LC9)], %f0
	.size	xx__sin_base, .-xx__sin_base
	.section	.rodata.cst8
	.align 8
.LC12:
	.long	1072693248
	.long	0
	.align 8
.LC13:
	.long	0
	.long	0
	.align 8
.LC14:
	.long	-2147483648
	.long	0
	.align 8
.LC15:
	.long	1075388923
	.long	1413752350
	.align 8
.LC16:
	.long	1074340347
	.long	1413752350
	.align 8
.LC17:
	.long	1073291771
	.long	1413750098
	.align 8
.LC18:
	.long	1072243195
	.long	1413750098
	.align 8
.LC19:
	.long	1048238066
	.long	2596056904
	.section	.text.xx__cos,"ax",@progbits
	.align 4
	.global xx__cos
	.type	xx__cos, #function
	.proc	07
xx__cos:
	add	%sp, -88, %sp
	std	%o0, [%sp+80]
	sethi	%hi(.LC13), %g2
	ldd	[%sp+80], %f8
	ldd	[%g2+%lo(.LC13)], %f10
	fcmped	%f8, %f10
	nop
	fbl,a	.L107
	 fnegs	%f8, %f8
.L107:
	sethi	%hi(.LC15), %g1
	ldd	[%g1+%lo(.LC15)], %f10
	fcmped	%f8, %f10
	nop
	fbul	.L109
	 nop
	fsubd	%f8, %f10, %f8
	fcmped	%f8, %f10
	nop
	fbg,a	.L195
	 fdivd	%f8, %f10, %f12
.L109:
	sethi	%hi(.LC16), %g1
	ldd	[%g1+%lo(.LC16)], %f10
	fcmped	%f8, %f10
	nop
	fbul	.L182
	 nop
	fsubd	%f8, %f10, %f8
	sethi	%hi(.LC17), %g1
	ldd	[%g1+%lo(.LC17)], %f10
	fcmped	%f8, %f10
	nop
	fbge	.L196
	 mov	1, %g3
.L183:
	sethi	%hi(.LC18), %g1
	ldd	[%g1+%lo(.LC18)], %f12
	fcmped	%f8, %f12
	nop
	fbule	.L190
	 nop
	cmp	%g3, 0
	be	.L197
	 fsubd	%f10, %f8, %f8
	sethi	%hi(.LC19), %g3
	ldd	[%g3+%lo(.LC19)], %f10
	fcmped	%f8, %f10
	nop
	fbule	.L189
	 fmuld	%f8, %f8, %f12
	sethi	%hi(.LC12), %g4
	ldd	[%g2+%lo(.LC13)], %f0
	mov	1, %g1
	mov	0, %g2
	ldd	[%g4+%lo(.LC12)], %f16
	fmovs	%f10, %f14
	b	.L129
	 fmovs	%f11, %f15
.L198:
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fsubd	%f0, %f8, %f0
	ld	[%sp+76], %f10
	fmuld	%f12, %f8, %f8
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f10, %f8, %f8
	fcmped	%f8, %f14
	nop
	fbule	.L193
	 xor	%g2, 1, %g2
.L129:
	cmp	%g2, 0
	bne	.L198
	 add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	faddd	%f0, %f8, %f0
	ld	[%sp+76], %f10
	fmuld	%f12, %f8, %f8
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f10, %f8, %f8
	fcmped	%f8, %f14
	nop
	fbg	.L129
	 xor	%g2, 1, %g2
.L193:
	fnegs	%f0, %f0
.L185:
	jmp	%o7+8
	 sub	%sp, -88, %sp
.L182:
	sethi	%hi(.LC17), %g1
	ldd	[%g1+%lo(.LC17)], %f10
	fcmped	%f8, %f10
	nop
	fbul	.L183
	 mov	0, %g3
.L196:
	fsubd	%f8, %f10, %f8
	sethi	%hi(.LC18), %g1
	ldd	[%g1+%lo(.LC18)], %f12
	fcmped	%f8, %f12
	nop
	fbule	.L199
	 nop
	cmp	%g3, 0
	be	.L200
	 fsubd	%f10, %f8, %f8
	sethi	%hi(.LC12), %g4
	sethi	%hi(.LC19), %g3
	ldd	[%g4+%lo(.LC12)], %f10
	ldd	[%g2+%lo(.LC13)], %f0
	fmuld	%f8, %f8, %f8
	mov	0, %g1
	mov	0, %g2
	fmovs	%f10, %f16
	fmovs	%f11, %f17
	b	.L120
	 ldd	[%g3+%lo(.LC19)], %f14
.L201:
.L119:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g3, %g1, %g3
	st	%g3, [%sp+76]
	fmuld	%f8, %f10, %f10
	ld	[%sp+76], %f12
	fitod	%f12, %f12
	fdivd	%f16, %f12, %f12
	fmuld	%f12, %f10, %f10
	fcmped	%f10, %f14
	nop
	fbule	.L185
	 xor	%g2, 1, %g2
.L120:
	cmp	%g2, 0
	bne,a	.L201
	 fsubd	%f0, %f10, %f0
	b	.L119
	 faddd	%f0, %f10, %f0
.L199:
	cmp	%g3, 0
	fmuld	%f8, %f8, %f12
	sethi	%hi(.LC19), %g3
	ldd	[%g3+%lo(.LC19)], %f10
	be	.L135
	 fcmped	%f8, %f10
	nop
	fbule	.L188
	 nop
	sethi	%hi(.LC12), %g4
	ldd	[%g2+%lo(.LC13)], %f0
	mov	1, %g1
	mov	0, %g2
	ldd	[%g4+%lo(.LC12)], %f16
	fmovs	%f10, %f14
	b	.L140
	 fmovs	%f11, %f15
.L202:
.L139:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f12, %f8, %f8
	ld	[%sp+76], %f10
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f10, %f8, %f8
	fcmped	%f8, %f14
	nop
	fbule	.L185
	 xor	%g2, 1, %g2
.L140:
	cmp	%g2, 0
	bne,a	.L202
	 fsubd	%f0, %f8, %f0
	b	.L139
	 faddd	%f0, %f8, %f0
.L195:
	fdtoi	%f12, %f12
	fitod	%f12, %f12
	fmuld	%f12, %f10, %f10
	b	.L109
	 fsubd	%f8, %f10, %f8
.L190:
	sethi	%hi(.LC12), %g4
	cmp	%g3, 0
	ldd	[%g4+%lo(.LC12)], %f10
	sethi	%hi(.LC19), %g3
	ldd	[%g2+%lo(.LC13)], %f0
	fmuld	%f8, %f8, %f8
	mov	0, %g1
	mov	0, %g2
	fmovs	%f10, %f16
	fmovs	%f11, %f17
	be	.L152
	 ldd	[%g3+%lo(.LC19)], %f14
	cmp	%g2, 0
	be,a	.L148
	 faddd	%f0, %f10, %f0
	fsubd	%f0, %f10, %f0
.L148:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f8, %f10, %f10
	ld	[%sp+76], %f12
	fitod	%f12, %f12
	fdivd	%f16, %f12, %f12
	fmuld	%f12, %f10, %f10
	fcmped	%f10, %f14
	nop
	fbule	.L193
	 xor	%g2, 1, %g2
	cmp	%g2, 0
	bne,a	.L148
	 fsubd	%f0, %f10, %f0
	b	.L148
	 faddd	%f0, %f10, %f0
.L204:
.L151:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f8, %f10, %f10
	ld	[%sp+76], %f12
	fitod	%f12, %f12
	fdivd	%f16, %f12, %f12
	fmuld	%f12, %f10, %f10
	fcmped	%f10, %f14
	nop
	fbule	.L185
	 xor	%g2, 1, %g2
.L152:
	cmp	%g2, 0
	bne,a	.L204
	 fsubd	%f0, %f10, %f0
	b	.L151
	 faddd	%f0, %f10, %f0
.L200:
	sethi	%hi(.LC12), %g4
	sethi	%hi(.LC19), %g3
	ldd	[%g4+%lo(.LC12)], %f10
	ldd	[%g2+%lo(.LC13)], %f0
	fmuld	%f8, %f8, %f8
	mov	0, %g1
	mov	0, %g2
	fmovs	%f10, %f16
	fmovs	%f11, %f17
	b	.L124
	 ldd	[%g3+%lo(.LC19)], %f14
.L205:
.L123:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g3, %g1, %g3
	st	%g3, [%sp+76]
	fmuld	%f8, %f10, %f10
	ld	[%sp+76], %f12
	fitod	%f12, %f12
	fdivd	%f16, %f12, %f12
	fmuld	%f12, %f10, %f10
	fcmped	%f10, %f14
	nop
	fbule	.L193
	 xor	%g2, 1, %g2
.L124:
	cmp	%g2, 0
	bne,a	.L205
	 fsubd	%f0, %f10, %f0
	b	.L123
	 faddd	%f0, %f10, %f0
.L135:
	nop
	fbule	.L189
	 nop
	sethi	%hi(.LC12), %g4
	ldd	[%g2+%lo(.LC13)], %f0
	mov	1, %g1
	mov	0, %g2
	ldd	[%g4+%lo(.LC12)], %f16
	fmovs	%f10, %f14
	b	.L145
	 fmovs	%f11, %f15
.L206:
.L144:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f12, %f8, %f8
	ld	[%sp+76], %f10
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f10, %f8, %f8
	fcmped	%f8, %f14
	nop
	fbule	.L193
	 xor	%g2, 1, %g2
.L145:
	cmp	%g2, 0
	bne,a	.L206
	 fsubd	%f0, %f8, %f0
	b	.L144
	 faddd	%f0, %f8, %f0
.L189:
	sethi	%hi(.LC14), %g1
	b	.L185
	 ldd	[%g1+%lo(.LC14)], %f0
.L188:
	b	.L185
	 ldd	[%g2+%lo(.LC13)], %f0
.L197:
	sethi	%hi(.LC19), %g3
	ldd	[%g3+%lo(.LC19)], %f10
	fcmped	%f8, %f10
	nop
	fbule	.L188
	 fmuld	%f8, %f8, %f12
	sethi	%hi(.LC12), %g4
	ldd	[%g2+%lo(.LC13)], %f0
	mov	1, %g1
	mov	0, %g2
	ldd	[%g4+%lo(.LC12)], %f16
	fmovs	%f10, %f14
	b	.L134
	 fmovs	%f11, %f15
.L207:
.L133:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f12, %f8, %f8
	ld	[%sp+76], %f10
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f10, %f8, %f8
	fcmped	%f8, %f14
	nop
	fbule	.L185
	 xor	%g2, 1, %g2
.L134:
	cmp	%g2, 0
	bne,a	.L207
	 fsubd	%f0, %f8, %f0
	b	.L133
	 faddd	%f0, %f8, %f0
	.size	xx__cos, .-xx__cos
	.section	.rodata.cst8
	.align 8
.LC20:
	.long	0
	.long	0
	.align 8
.LC21:
	.long	-2147483648
	.long	0
	.align 8
.LC22:
	.long	1072693248
	.long	0
	.align 8
.LC23:
	.long	1075388923
	.long	1413752350
	.align 8
.LC24:
	.long	1074340347
	.long	1413752350
	.align 8
.LC25:
	.long	1073291771
	.long	1413750098
	.align 8
.LC26:
	.long	1072243195
	.long	1413750098
	.align 8
.LC27:
	.long	1048238066
	.long	2596056904
	.section	.text.xx__sin,"ax",@progbits
	.align 4
	.global xx__sin
	.type	xx__sin, #function
	.proc	07
xx__sin:
	add	%sp, -88, %sp
	std	%o0, [%sp+80]
	sethi	%hi(.LC20), %g2
	ldd	[%sp+80], %f8
	ldd	[%g2+%lo(.LC20)], %f10
	fcmped	%f8, %f10
	nop
	fbl,a	.L302
	 fnegs	%f8, %f8
	mov	0, %g4
.L209:
	sethi	%hi(.LC23), %g1
	ldd	[%g1+%lo(.LC23)], %f10
	fcmped	%f8, %f10
	nop
	fbul	.L211
	 nop
	fsubd	%f8, %f10, %f8
	fcmped	%f8, %f10
	nop
	fbg,a	.L303
	 fdivd	%f8, %f10, %f12
.L211:
	sethi	%hi(.LC24), %g1
	ldd	[%g1+%lo(.LC24)], %f10
	fcmped	%f8, %f10
	nop
	fbul	.L290
	 nop
	fsubd	%f8, %f10, %f8
	sethi	%hi(.LC25), %g1
	ldd	[%g1+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge	.L304
	 mov	1, %g3
.L291:
	sethi	%hi(.LC26), %g1
	ldd	[%g1+%lo(.LC26)], %f12
	fcmped	%f8, %f12
	nop
	fbule	.L305
	 nop
	cmp	%g3, 0
	be	.L306
	 fsubd	%f10, %f8, %f8
	sethi	%hi(.LC22), %o5
	sethi	%hi(.LC27), %g3
	ldd	[%o5+%lo(.LC22)], %f10
	ldd	[%g2+%lo(.LC20)], %f0
	fmuld	%f8, %f8, %f8
	mov	0, %g1
	mov	0, %g2
	fmovs	%f10, %f16
	fmovs	%f11, %f17
	b	.L233
	 ldd	[%g3+%lo(.LC27)], %f14
.L307:
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fsubd	%f0, %f10, %f0
	ld	[%sp+76], %f12
	fmuld	%f8, %f10, %f10
	fitod	%f12, %f12
	fdivd	%f16, %f12, %f12
	fmuld	%f12, %f10, %f10
	fcmped	%f10, %f14
	nop
	fbule	.L301
	 xor	%g2, 1, %g2
.L233:
	cmp	%g2, 0
	bne	.L307
	 add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	faddd	%f0, %f10, %f0
	ld	[%sp+76], %f12
	fmuld	%f8, %f10, %f10
	fitod	%f12, %f12
	fdivd	%f16, %f12, %f12
	fmuld	%f12, %f10, %f10
	fcmped	%f10, %f14
	nop
	fbg	.L233
	 xor	%g2, 1, %g2
.L301:
	fnegs	%f0, %f0
.L225:
	cmp	%g4, 0
	bne,a	.L278
	 fnegs	%f0, %f0
.L278:
	jmp	%o7+8
	 sub	%sp, -88, %sp
.L290:
	sethi	%hi(.LC25), %g1
	ldd	[%g1+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbul	.L291
	 mov	0, %g3
.L304:
	fsubd	%f8, %f10, %f8
	sethi	%hi(.LC26), %g1
	ldd	[%g1+%lo(.LC26)], %f12
	fcmped	%f8, %f12
	nop
	fbule	.L308
	 nop
	cmp	%g3, 0
	be	.L309
	 fsubd	%f10, %f8, %f8
	sethi	%hi(.LC27), %g3
	ldd	[%g3+%lo(.LC27)], %f10
	fcmped	%f8, %f10
	nop
	fbule	.L295
	 fmuld	%f8, %f8, %f12
	sethi	%hi(.LC22), %o5
	ldd	[%g2+%lo(.LC20)], %f0
	mov	1, %g1
	mov	0, %g2
	ldd	[%o5+%lo(.LC22)], %f16
	fmovs	%f10, %f14
	b	.L224
	 fmovs	%f11, %f15
.L310:
.L223:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g3, %g1, %g3
	st	%g3, [%sp+76]
	fmuld	%f12, %f8, %f8
	ld	[%sp+76], %f10
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f10, %f8, %f8
	fcmped	%f8, %f14
	nop
	fbule	.L301
	 xor	%g2, 1, %g2
.L224:
	cmp	%g2, 0
	bne,a	.L310
	 fsubd	%f0, %f8, %f0
	b	.L223
	 faddd	%f0, %f8, %f0
.L308:
	sethi	%hi(.LC22), %o5
	cmp	%g3, 0
	ldd	[%o5+%lo(.LC22)], %f10
	sethi	%hi(.LC27), %g3
	ldd	[%g2+%lo(.LC20)], %f0
	fmuld	%f8, %f8, %f8
	mov	0, %g1
	mov	0, %g2
	fmovs	%f10, %f16
	fmovs	%f11, %f17
	be	.L243
	 ldd	[%g3+%lo(.LC27)], %f14
	cmp	%g2, 0
	be,a	.L239
	 faddd	%f0, %f10, %f0
	fsubd	%f0, %f10, %f0
.L239:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f8, %f10, %f10
	ld	[%sp+76], %f12
	fitod	%f12, %f12
	fdivd	%f16, %f12, %f12
	fmuld	%f12, %f10, %f10
	fcmped	%f10, %f14
	nop
	fbule	.L301
	 xor	%g2, 1, %g2
	cmp	%g2, 0
	bne,a	.L239
	 fsubd	%f0, %f10, %f0
	b	.L239
	 faddd	%f0, %f10, %f0
.L312:
.L242:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f8, %f10, %f10
	ld	[%sp+76], %f12
	fitod	%f12, %f12
	fdivd	%f16, %f12, %f12
	fmuld	%f12, %f10, %f10
	fcmped	%f10, %f14
	nop
	fbule	.L225
	 xor	%g2, 1, %g2
.L243:
	cmp	%g2, 0
	bne,a	.L312
	 fsubd	%f0, %f10, %f0
	b	.L242
	 faddd	%f0, %f10, %f0
.L303:
	fdtoi	%f12, %f12
	fitod	%f12, %f12
	fmuld	%f12, %f10, %f10
	b	.L211
	 fsubd	%f8, %f10, %f8
.L302:
	b	.L209
	 mov	1, %g4
.L305:
	cmp	%g3, 0
	fmuld	%f8, %f8, %f12
	sethi	%hi(.LC27), %g3
	ldd	[%g3+%lo(.LC27)], %f10
	be	.L244
	 fcmped	%f8, %f10
	nop
	fbule	.L295
	 nop
	sethi	%hi(.LC22), %o5
	ldd	[%g2+%lo(.LC20)], %f0
	mov	1, %g1
	mov	0, %g2
	ldd	[%o5+%lo(.LC22)], %f16
	fmovs	%f10, %f14
	b	.L249
	 fmovs	%f11, %f15
.L313:
.L248:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f12, %f8, %f8
	ld	[%sp+76], %f10
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f10, %f8, %f8
	fcmped	%f8, %f14
	nop
	fbule	.L301
	 xor	%g2, 1, %g2
.L249:
	cmp	%g2, 0
	bne,a	.L313
	 fsubd	%f0, %f8, %f0
	b	.L248
	 faddd	%f0, %f8, %f0
.L244:
	nop
	fbule	.L296
	 nop
	sethi	%hi(.LC22), %o5
	ldd	[%g2+%lo(.LC20)], %f0
	mov	1, %g1
	mov	0, %g2
	ldd	[%o5+%lo(.LC22)], %f16
	fmovs	%f10, %f14
	b	.L254
	 fmovs	%f11, %f15
.L314:
.L253:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f12, %f8, %f8
	ld	[%sp+76], %f10
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f10, %f8, %f8
	fcmped	%f8, %f14
	nop
	fbule	.L225
	 xor	%g2, 1, %g2
.L254:
	cmp	%g2, 0
	bne,a	.L314
	 fsubd	%f0, %f8, %f0
	b	.L253
	 faddd	%f0, %f8, %f0
.L309:
	sethi	%hi(.LC27), %g3
	ldd	[%g3+%lo(.LC27)], %f10
	fcmped	%f8, %f10
	nop
	fbule	.L296
	 fmuld	%f8, %f8, %f12
	sethi	%hi(.LC22), %o5
	ldd	[%g2+%lo(.LC20)], %f0
	mov	1, %g1
	mov	0, %g2
	ldd	[%o5+%lo(.LC22)], %f16
	fmovs	%f10, %f14
	b	.L230
	 fmovs	%f11, %f15
.L315:
.L229:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g3, %g1, %g3
	st	%g3, [%sp+76]
	fmuld	%f12, %f8, %f8
	ld	[%sp+76], %f10
	fitod	%f10, %f10
	fdivd	%f16, %f10, %f10
	fmuld	%f10, %f8, %f8
	fcmped	%f8, %f14
	nop
	fbule	.L225
	 xor	%g2, 1, %g2
.L230:
	cmp	%g2, 0
	bne,a	.L315
	 fsubd	%f0, %f8, %f0
	b	.L229
	 faddd	%f0, %f8, %f0
.L296:
	b	.L225
	 ldd	[%g2+%lo(.LC20)], %f0
.L295:
	sethi	%hi(.LC21), %g1
	b	.L225
	 ldd	[%g1+%lo(.LC21)], %f0
.L306:
	sethi	%hi(.LC22), %o5
	sethi	%hi(.LC27), %g3
	ldd	[%o5+%lo(.LC22)], %f10
	ldd	[%g2+%lo(.LC20)], %f0
	fmuld	%f8, %f8, %f8
	mov	0, %g1
	mov	0, %g2
	fmovs	%f10, %f16
	fmovs	%f11, %f17
	b	.L236
	 ldd	[%g3+%lo(.LC27)], %f14
.L316:
.L235:
	add	%g1, 1, %g3
	add	%g1, 2, %g1
	smul	%g1, %g3, %g3
	st	%g3, [%sp+76]
	fmuld	%f8, %f10, %f10
	ld	[%sp+76], %f12
	fitod	%f12, %f12
	fdivd	%f16, %f12, %f12
	fmuld	%f12, %f10, %f10
	fcmped	%f10, %f14
	nop
	fbule	.L225
	 xor	%g2, 1, %g2
.L236:
	cmp	%g2, 0
	bne,a	.L316
	 fsubd	%f0, %f10, %f0
	b	.L235
	 faddd	%f0, %f10, %f0
	.size	xx__sin, .-xx__sin
	.section	.text.xx__tan,"ax",@progbits
	.align 4
	.global xx__tan
	.type	xx__tan, #function
	.proc	07
xx__tan:
	save	%sp, -120, %sp
	std	%i0, [%fp-24]
	ldd	[%fp-24], %f8
	mov	%i0, %o0
	mov	%i1, %o1
	call	xx__sin, 0
	 std	%f8, [%fp-8]
	ldd	[%fp-8], %f8
	fmovs	%f0, %f10
	fmovs	%f1, %f11
	std	%f8, [%fp-24]
	std	%f10, [%fp-16]
	call	xx__cos, 0
	 ldd	[%fp-24], %o0
	ldd	[%fp-16], %f10
	fdivd	%f10, %f0, %f0
	jmp	%i7+8
	 restore
	.size	xx__tan, .-xx__tan
	.section	.rodata.cst8
	.align 8
.LC28:
	.long	1071194619
	.long	1293080650
	.align 8
.LC29:
	.long	1072654970
	.long	538105389
	.align 8
.LC30:
	.long	1073085883
	.long	3813548329
	.align 8
.LC31:
	.long	1073165107
	.long	858993459
	.align 8
.LC32:
	.long	1073201807
	.long	1546188227
	.align 8
.LC33:
	.long	1073233264
	.long	2748779069
	.align 8
.LC34:
	.long	1073254236
	.long	687194767
	.align 8
.LC35:
	.long	1073264721
	.long	3951369912
	.align 8
.LC36:
	.long	1073272586
	.long	1030792151
	.align 8
.LC37:
	.long	1073275941
	.long	2934321657
	.align 8
.LC38:
	.long	0
	.long	0
	.align 8
.LC39:
	.long	1073290936
	.long	1374389535
	.align 8
.LC40:
	.long	1072243195
	.long	1413750098
	.align 8
.LC41:
	.long	-1075240453
	.long	1413750098
	.align 8
.LC42:
	.long	1071644672
	.long	0
	.align 8
.LC43:
	.long	1072693248
	.long	0
	.align 8
.LC44:
	.long	-1074790400
	.long	0
	.align 8
.LC45:
	.long	1071741774
	.long	1425516825
	.align 8
.LC46:
	.long	1073277732
	.long	2796058069
	.align 8
.LC47:
	.long	1074003968
	.long	0
	.align 8
.LC48:
	.long	1075576832
	.long	0
	.align 8
.LC49:
	.long	1076101120
	.long	0
	.align 8
.LC50:
	.long	1076625408
	.long	0
	.align 8
.LC51:
	.long	1076953088
	.long	0
	.align 8
.LC52:
	.long	1077411840
	.long	0
	.align 8
.LC53:
	.long	1077936128
	.long	0
	.align 8
.LC54:
	.long	1078460416
	.long	0
	.align 8
.LC55:
	.long	1079033856
	.long	0
	.align 8
.LC56:
	.long	1079443456
	.long	0
	.align 8
.LC57:
	.long	1074340347
	.long	1413752350
	.section	.text.tan_inverse,"ax",@progbits
	.align 4
	.global tan_inverse
	.type	tan_inverse, #function
	.proc	07
tan_inverse:
	save	%sp, -144, %sp
	std	%i0, [%fp-48]
	ldd	[%fp-48], %f14
	std	%i2, [%fp-48]
	sethi	%hi(.LC38), %i5
	ldd	[%fp-48], %f10
	ldd	[%i5+%lo(.LC38)], %f12
	fdivd	%f14, %f10, %f8
	fmovs	%f12, %f0
	fcmpd	%f8, %f12
	nop
	fbe	.L391
	 fmovs	%f13, %f1
	sethi	%hi(.LC43), %g1
	sethi	%hi(.LC40), %g2
	ldd	[%g1+%lo(.LC43)], %f16
	fcmpd	%f8, %f16
	nop
	fbe	.L391
	 ldd	[%g2+%lo(.LC40)], %f0
	sethi	%hi(.LC41), %g2
	ldd	[%g2+%lo(.LC41)], %f0
	sethi	%hi(.LC44), %g2
	ldd	[%g2+%lo(.LC44)], %f16
	fcmpd	%f8, %f16
	nop
	fbe	.L391
	 sethi	%hi(.LC42), %g2
	ldd	[%g2+%lo(.LC42)], %f0
	sethi	%hi(.LC45), %g2
	ldd	[%g2+%lo(.LC45)], %f16
	fcmpd	%f8, %f16
	nop
	fbe	.L391
	 sethi	%hi(.LC46), %g2
	ldd	[%g2+%lo(.LC46)], %f16
	fcmpd	%f8, %f16
	nop
	fbe	.L391
	 ldd	[%g1+%lo(.LC43)], %f0
	fcmped	%f8, %f12
	nop
	fbule	.L387
	 nop
	ldd	[%g1+%lo(.LC43)], %f12
.L389:
	fcmped	%f8, %f12
	nop
	fbl,a	.L358
	 sethi	%hi(.LC28), %g1
.L321:
	ldd	[%g1+%lo(.LC43)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L324
	 sethi	%hi(.LC47), %g1
	ldd	[%g1+%lo(.LC47)], %f16
	sethi	%hi(.LC29), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC29)], %f12
.L324:
	ldd	[%g1+%lo(.LC47)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L326
	 sethi	%hi(.LC48), %g1
	ldd	[%g1+%lo(.LC48)], %f16
	sethi	%hi(.LC30), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC30)], %f12
.L326:
	ldd	[%g1+%lo(.LC48)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L328
	 sethi	%hi(.LC49), %g1
	ldd	[%g1+%lo(.LC49)], %f16
	sethi	%hi(.LC31), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC31)], %f12
.L328:
	ldd	[%g1+%lo(.LC49)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L330
	 sethi	%hi(.LC50), %g1
	ldd	[%g1+%lo(.LC50)], %f16
	sethi	%hi(.LC32), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC32)], %f12
.L330:
	ldd	[%g1+%lo(.LC50)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L332
	 sethi	%hi(.LC51), %g1
	ldd	[%g1+%lo(.LC51)], %f16
	sethi	%hi(.LC32), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC32)], %f12
.L332:
	ldd	[%g1+%lo(.LC51)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L334
	 sethi	%hi(.LC52), %g1
	ldd	[%g1+%lo(.LC52)], %f16
	sethi	%hi(.LC33), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC33)], %f12
.L334:
	ldd	[%g1+%lo(.LC52)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L336
	 sethi	%hi(.LC53), %g1
	ldd	[%g1+%lo(.LC53)], %f16
	sethi	%hi(.LC34), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC34)], %f12
.L336:
	ldd	[%g1+%lo(.LC53)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L338
	 sethi	%hi(.LC54), %g1
	ldd	[%g1+%lo(.LC54)], %f16
	sethi	%hi(.LC35), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC35)], %f12
.L338:
	ldd	[%g1+%lo(.LC54)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L340
	 sethi	%hi(.LC55), %g1
	ldd	[%g1+%lo(.LC55)], %f16
	sethi	%hi(.LC36), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC36)], %f12
.L340:
	ldd	[%g1+%lo(.LC55)], %f12
	fcmped	%f8, %f12
	nop
	fbul	.L342
	 sethi	%hi(.LC56), %g1
	ldd	[%g1+%lo(.LC56)], %f16
	sethi	%hi(.LC37), %g2
	fcmped	%f8, %f16
	nop
	fbl	.L323
	 ldd	[%g2+%lo(.LC37)], %f12
.L342:
	ldd	[%g1+%lo(.LC56)], %f12
	sethi	%hi(.LC39), %g1
	fcmped	%f8, %f12
	nop
	fbge	.L323
	 ldd	[%g1+%lo(.LC39)], %f12
	ldd	[%i5+%lo(.LC38)], %f12
.L323:
	std	%f10, [%fp-16]
	std	%f14, [%fp-32]
	std	%f12, [%fp-48]
	std	%f8, [%fp-8]
	ldd	[%fp-48], %o0
	call	xx__sin, 0
	 std	%f12, [%fp-24]
	ldd	[%fp-24], %f12
	fmovs	%f0, %f16
	fmovs	%f1, %f17
	std	%f12, [%fp-48]
	std	%f16, [%fp-40]
	call	xx__cos, 0
	 ldd	[%fp-48], %o0
	ldd	[%fp-8], %f8
	ldd	[%fp-40], %f16
	ldd	[%fp-24], %f12
	fdivd	%f16, %f0, %f16
	fmuld	%f0, %f0, %f0
	fsubd	%f16, %f8, %f16
	fmuld	%f16, %f0, %f0
	fsubd	%f12, %f0, %f12
	std	%f12, [%fp-48]
	std	%f12, [%fp-24]
	call	xx__sin, 0
	 ldd	[%fp-48], %o0
	ldd	[%fp-24], %f12
	fmovs	%f0, %f16
	fmovs	%f1, %f17
	std	%f12, [%fp-48]
	std	%f16, [%fp-40]
	call	xx__cos, 0
	 ldd	[%fp-48], %o0
	ldd	[%fp-8], %f8
	ldd	[%fp-40], %f16
	ldd	[%fp-24], %f12
	fdivd	%f16, %f0, %f16
	fmuld	%f0, %f0, %f0
	fsubd	%f16, %f8, %f16
	fmuld	%f16, %f0, %f0
	fsubd	%f12, %f0, %f12
	std	%f12, [%fp-48]
	std	%f12, [%fp-24]
	call	xx__sin, 0
	 ldd	[%fp-48], %o0
	ldd	[%fp-24], %f12
	fmovs	%f0, %f16
	fmovs	%f1, %f17
	std	%f12, [%fp-48]
	std	%f16, [%fp-40]
	call	xx__cos, 0
	 ldd	[%fp-48], %o0
	ldd	[%i5+%lo(.LC38)], %f18
	ldd	[%fp-40], %f16
	ldd	[%fp-8], %f8
	fdivd	%f16, %f0, %f16
	ldd	[%fp-16], %f10
	fmuld	%f0, %f0, %f0
	fsubd	%f16, %f8, %f8
	ldd	[%fp-24], %f12
	fmuld	%f8, %f0, %f0
	fcmped	%f10, %f18
	fsubd	%f12, %f0, %f0
	nop
	fbl	.L388
	 ldd	[%fp-32], %f14
.L344:
	ldd	[%i5+%lo(.LC38)], %f8
	fcmped	%f10, %f8
	nop
	fbule	.L347
	 nop
	fcmped	%f14, %f8
	nop
	fble,a	.L391
	 fnegs	%f0, %f0
.L347:
	ldd	[%i5+%lo(.LC38)], %f8
	fcmped	%f10, %f8
	nop
	fbuge	.L390
	 nop
	fcmped	%f14, %f8
	nop
	fbug	.L390
	 nop
	sethi	%hi(.LC57), %g1
	ldd	[%g1+%lo(.LC57)], %f8
	fsubd	%f8, %f0, %f0
	fnegs	%f0, %f0
.L391:
	jmp	%i7+8
	 restore
.L358:
	b	.L323
	 ldd	[%g1+%lo(.LC28)], %f12
.L388:
	fcmped	%f14, %f18
	nop
	fbul	.L344
	 nop
	sethi	%hi(.LC57), %g1
	ldd	[%g1+%lo(.LC57)], %f8
	fsubd	%f8, %f0, %f0
.L390:
	jmp	%i7+8
	 restore
.L387:
	fsubd	%f12, %f8, %f8
	fcmped	%f8, %f12
	nop
	fbul	.L321
	 nop
	b	.L389
	 ldd	[%g1+%lo(.LC43)], %f12
	.size	tan_inverse, .-tan_inverse
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
