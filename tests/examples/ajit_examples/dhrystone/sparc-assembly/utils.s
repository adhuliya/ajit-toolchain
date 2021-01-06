	.file	"utils.c"
	.section	".text"
	.align 4
	.global __memcpy
	.type	__memcpy, #function
	.proc	0120
__memcpy:
	save	%sp, -128, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%g0, [%fp-4]
	st	%g0, [%fp-8]
	ld	[%fp+68], %g1
	st	%g1, [%fp-20]
	ld	[%fp+72], %g1
	st	%g1, [%fp-24]
	ld	[%fp-24], %g1
	ldd	[%g1], %g2
	std	%g2, [%fp-16]
.L2:
	ld	[%fp-4], %g1
	sll	%g1, 3, %g1
	ld	[%fp-20], %g2
	add	%g2, %g1, %g1
	ldd	[%fp-16], %g2
	std	%g2, [%g1]
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
	ld	[%fp-8], %g1
	add	%g1, 8, %g1
	st	%g1, [%fp-8]
	ld	[%fp-4], %g1
	sll	%g1, 3, %g1
	ld	[%fp-24], %g2
	add	%g2, %g1, %g1
	ldd	[%g1], %g2
	std	%g2, [%fp-16]
	ld	[%fp-8], %g2
	ld	[%fp+76], %g1
	cmp	%g2, %g1
	blu	.L2
	 nop
	ld	[%fp-8], %g2
	ld	[%fp+76], %g1
	cmp	%g2, %g1
	bgeu	.L3
	 nop
	ld	[%fp+68], %g1
	st	%g1, [%fp-28]
	ld	[%fp+72], %g1
	st	%g1, [%fp-32]
.L4:
	ld	[%fp-8], %g1
	ld	[%fp-28], %g2
	add	%g2, %g1, %g1
	ld	[%fp-8], %g2
	ld	[%fp-32], %g3
	add	%g3, %g2, %g2
	ldub	[%g2], %g2
	stb	%g2, [%g1]
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
	ld	[%fp-8], %g2
	ld	[%fp+76], %g1
	cmp	%g2, %g1
	blu	.L4
	 nop
.L3:
	ld	[%fp+68], %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	__memcpy, .-__memcpy
	.align 4
	.global __strcpy
	.type	__strcpy, #function
	.proc	0102
__strcpy:
	save	%sp, -120, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%g0, [%fp-4]
	ld	[%fp+68], %g1
	st	%g1, [%fp-12]
	ld	[%fp+72], %g1
	st	%g1, [%fp-16]
	ld	[%fp-16], %g1
	ld	[%g1], %g1
	st	%g1, [%fp-8]
	st	%g0, [%fp-20]
.L7:
	ld	[%fp-8], %g2
	sethi	%hi(-16843776), %g1
	or	%g1, 767, %g1
	add	%g2, %g1, %g2
	ld	[%fp-8], %g1
	xnor	%g0, %g1, %g1
	and	%g2, %g1, %g2
	sethi	%hi(-2139062272), %g1
	or	%g1, 128, %g1
	and	%g2, %g1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-4], %g1
	sll	%g1, 2, %g1
	ld	[%fp-12], %g2
	add	%g2, %g1, %g1
	ld	[%fp-8], %g2
	st	%g2, [%g1]
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
	ld	[%fp-4], %g1
	sll	%g1, 2, %g1
	ld	[%fp-16], %g2
	add	%g2, %g1, %g1
	ld	[%g1], %g1
	st	%g1, [%fp-8]
	ld	[%fp-20], %g1
	cmp	%g1, 0
	be	.L7
	 nop
	ld	[%fp+68], %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	__strcpy, .-__strcpy
	.align 4
	.global __strcmp
	.type	__strcmp, #function
	.proc	04
__strcmp:
	save	%sp, -120, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	mov	0, %i5
	st	%g0, [%fp-4]
	ld	[%fp+68], %g1
	st	%g1, [%fp-12]
	ld	[%fp+72], %g1
	st	%g1, [%fp-16]
	st	%g0, [%fp-8]
.L11:
	ld	[%fp-4], %g1
	sll	%g1, 2, %g1
	ld	[%fp-12], %g2
	add	%g2, %g1, %g1
	ld	[%g1], %g1
	st	%g1, [%fp-20]
	ld	[%fp-4], %g1
	sll	%g1, 2, %g1
	ld	[%fp-16], %g2
	add	%g2, %g1, %g1
	ld	[%g1], %g1
	st	%g1, [%fp-24]
	ld	[%fp-20], %g2
	ld	[%fp-24], %g1
	sub	%g2, %g1, %g1
	mov	%g1, %i5
	ld	[%fp-20], %g2
	sethi	%hi(-16843776), %g1
	or	%g1, 767, %g1
	add	%g2, %g1, %g2
	ld	[%fp-20], %g1
	xnor	%g0, %g1, %g1
	and	%g2, %g1, %g2
	sethi	%hi(-2139062272), %g1
	or	%g1, 128, %g1
	and	%g2, %g1, %g2
	mov	%i5, %g1
	or	%g2, %g1, %g1
	cmp	%g1, 0
	be	.L10
	 nop
	mov	1, %g1
	st	%g1, [%fp-8]
.L10:
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
	ld	[%fp-8], %g1
	cmp	%g1, 0
	be	.L11
	 nop
	mov	%i5, %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	__strcmp, .-__strcmp
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
