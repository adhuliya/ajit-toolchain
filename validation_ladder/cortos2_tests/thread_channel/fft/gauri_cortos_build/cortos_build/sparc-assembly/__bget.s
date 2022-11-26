	.file	"__bget.c"
	.section	".text"
	.align 4
	.global bget
	.type	bget, #function
	.proc	0120
bget:
	cmp	%o0, 7
	bleu	.L9
	 mov	16, %g3
	add	%o0, 7, %g4
	and	%g4, -8, %g4
	add	%g4, 8, %g4
	mov	%g4, %g3
.L2:
	sethi	%hi(freelist), %g2
	or	%g2, %lo(freelist), %g2
	ld	[%g2+8], %o0
	cmp	%o0, %g2
	bne,a	.L16
	 ld	[%o0+4], %g1
	jmp	%o7+8
	 mov	0, %o0
.L11:
	cmp	%o0, %g2
	be	.L10
	 nop
	ld	[%o0+4], %g1
.L16:
	cmp	%g1, %g3
	bl,a	.L11
	 ld	[%o0+8], %o0
	sub	%g1, %g3, %g2
	cmp	%g2, 16
	bleu,a	.L7
	 ld	[%o0+8], %g3
	st	%g2, [%o0+4]
	st	%g2, [%o0+%g2]
	sub	%g0, %g3, %g3
	add	%o0, %g2, %o0
	st	%g0, [%o0+%g4]
	st	%g3, [%o0+4]
	jmp	%o7+8
	 add	%o0, 8, %o0
.L10:
	jmp	%o7+8
	 mov	0, %o0
.L9:
	b	.L2
	 mov	16, %g4
.L7:
	ld	[%o0+12], %g2
	st	%g3, [%g2+8]
	ld	[%o0+8], %g3
	st	%g2, [%g3+12]
	st	%g0, [%o0+%g1]
	sub	%g0, %g1, %g2
	st	%g2, [%o0+4]
	add	%o0, 8, %o0
	jmp	%o7+8
	 nop
	.size	bget, .-bget
	.align 4
	.global bpool
	.type	bpool, #function
	.proc	020
bpool:
	sethi	%hi(freelist), %g1
	or	%g1, %lo(freelist), %g1
	ld	[%g1+12], %g2
	st	%g1, [%o0+8]
	st	%g2, [%o0+12]
	st	%o0, [%g1+12]
	st	%g0, [%o0]
	ld	[%o0+12], %g1
	and	%o1, -8, %o1
	st	%o0, [%g1+8]
	add	%o1, -8, %o1
	st	%o1, [%o0+4]
	add	%o0, %o1, %g1
	sethi	%hi(-2147483648), %g2
	st	%o1, [%o0+%o1]
	jmp	%o7+8
	 st	%g2, [%g1+4]
	.size	bpool, .-bpool
	.align 4
	.global brel
	.type	brel, #function
	.proc	020
brel:
	ld	[%o0-8], %g1
	cmp	%g1, 0
	be	.L19
	 add	%o0, -8, %g2
	sub	%g2, %g1, %g2
	ld	[%o0-4], %g1
	ld	[%g2+4], %g3
	sub	%g3, %g1, %g1
	st	%g1, [%g2+4]
.L20:
	add	%g2, %g1, %g3
	ld	[%g3+4], %g4
	cmp	%g4, 0
	ble	.L21
	 nop
	ld	[%g3+12], %o5
	add	%g1, %g4, %g1
	ld	[%g3+8], %o4
	st	%g1, [%g2+4]
	st	%o4, [%o5+8]
	ld	[%g3+8], %g4
	add	%g2, %g1, %g3
	st	%o5, [%g4+12]
.L21:
	jmp	%o7+8
	 st	%g1, [%g3]
.L19:
	sethi	%hi(freelist), %g3
	or	%g3, %lo(freelist), %g3
	ld	[%g3+12], %g1
	st	%g3, [%o0]
	st	%g1, [%o0+4]
	st	%g2, [%g3+12]
	ld	[%o0-4], %g1
	ld	[%o0+4], %g3
	sub	%g0, %g1, %g1
	st	%g2, [%g3+8]
	b	.L20
	 st	%g1, [%o0-4]
	.size	brel, .-brel
	.section	".data"
	.align 4
	.type	freelist, #object
	.size	freelist, 16
freelist:
	.long	0
	.long	0
	.long	freelist
	.long	freelist
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
