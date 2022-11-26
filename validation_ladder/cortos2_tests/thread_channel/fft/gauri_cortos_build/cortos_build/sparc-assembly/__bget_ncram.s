	.file	"__bget_ncram.c"
	.section	".text"
	.align 4
	.global bget_ncram
	.type	bget_ncram, #function
	.proc	0120
bget_ncram:
	sra	%o0, 31, %g1
	srl	%g1, 28, %g1
	add	%o0, %g1, %g2
	and	%g2, 15, %g2
	sub	%g2, %g1, %g1
	add	%g1, %o0, %o0
	cmp	%o0, 15
	bleu	.L9
	 mov	24, %g3
	add	%o0, 15, %g4
	and	%g4, -16, %g4
	add	%g4, 8, %g4
	mov	%g4, %g3
.L2:
	sethi	%hi(freelist_ncram), %g2
	or	%g2, %lo(freelist_ncram), %g2
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
	cmp	%g2, 24
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
	 mov	24, %g4
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
	.size	bget_ncram, .-bget_ncram
	.align 4
	.global bpool_ncram
	.type	bpool_ncram, #function
	.proc	020
bpool_ncram:
	sethi	%hi(freelist_ncram), %g1
	or	%g1, %lo(freelist_ncram), %g1
	ld	[%g1+12], %g2
	st	%g1, [%o0+8]
	st	%g2, [%o0+12]
	st	%o0, [%g1+12]
	st	%g0, [%o0]
	ld	[%o0+12], %g1
	and	%o1, -16, %o1
	st	%o0, [%g1+8]
	add	%o1, -8, %o1
	st	%o1, [%o0+4]
	add	%o0, %o1, %g1
	sethi	%hi(-2147483648), %g2
	st	%o1, [%o0+%o1]
	jmp	%o7+8
	 st	%g2, [%g1+4]
	.size	bpool_ncram, .-bpool_ncram
	.align 4
	.global brel_ncram
	.type	brel_ncram, #function
	.proc	020
brel_ncram:
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
	sethi	%hi(freelist_ncram), %g3
	or	%g3, %lo(freelist_ncram), %g3
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
	.size	brel_ncram, .-brel_ncram
	.section	".data"
	.align 4
	.type	freelist_ncram, #object
	.size	freelist_ncram, 16
freelist_ncram:
	.long	0
	.long	0
	.long	freelist_ncram
	.long	freelist_ncram
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
