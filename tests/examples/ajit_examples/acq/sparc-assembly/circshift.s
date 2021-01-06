	.file	"circshift.c"
	.section	".text"
	.align 4
	.global circshift
	.type	circshift, #function
	.proc	020
circshift:
	sethi	%hi(-25600), %g1
	or	%g1, 976, %g1
	sethi	%hi(24576), %g2
	add	%sp, %g1, %sp
	or	%g2, 48, %g3
	sll	%o1, 2, %g1
	add	%g3, %sp, %g4
	sethi	%hi(-24576), %o3
	sethi	%hi(5120), %o5
	or	%o3, 24, %o3
	sethi	%hi(23552), %g2
	add	%g4, %o3, %o4
	or	%o5, 1017, %g3
	add	%o4, %g1, %g4
	or	%g2, 1000, %g2
	b	.L4
	 mov	0, %g1
.L10:
	ld	[%o0+%g1], %o4
	st	%o4, [%o5+%o3]
	add	%g1, 4, %g1
	cmp	%g1, %g2
	be	.L9
	 add	%o1, 1, %o1
.L4:
	cmp	%o1, %g3
	bg	.L10
	 add	%g4, %g1, %o5
	ld	[%o0+%g1], %o4
	st	%o4, [%g4+%g1]
	add	%g1, 4, %g1
	cmp	%g1, %g2
	bne	.L4
	 add	%o1, 1, %o1
.L9:
	sethi	%hi(23552), %o3
	mov	0, %g1
	or	%o3, 1000, %g4
	add	%sp, 72, %g3
	ld	[%g1+%g3], %g2
.L11:
	st	%g2, [%o0+%g1]
	add	%g1, 4, %g1
	cmp	%g1, %g4
	bne,a	.L11
	 ld	[%g1+%g3], %g2
	sethi	%hi(-25600), %g1
	or	%g1, 976, %g1
	jmp	%o7+8
	 sub	%sp, %g1, %sp
	.size	circshift, .-circshift
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
