	.file	"fact.c"
	.global .umul
	.section	".text"
	.align 4
	.global factorial
	.type	factorial, #function
	.proc	04
factorial:
	save	%sp, -96, %sp
	addd    %g1, %g2, %g1 /* Safe: g1 is overwritten below, and g1, g2 are read */
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
	cmp	%g1, 0
	be	.L2
	 nop
	ld	[%fp+68], %g1
	add	%g1, -1, %g1
	mov	%g1, %o0
	call	factorial, 0
	 nop
	mov	%o0, %g1
	mov	%g1, %o0
	ld	[%fp+68], %o1
	call	.umul, 0
	 nop
	mov	%o0, %g1
	b	.L3
	 nop
.L2:
	mov	1, %g1
.L3:
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	factorial, .-factorial
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
