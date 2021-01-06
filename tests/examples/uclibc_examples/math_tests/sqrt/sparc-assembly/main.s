	.file	"main.c"
	.global X
	.section	".data"
	.align 8
	.type	X, #object
	.size	X, 8
X:
	.long	1074790400
	.long	0
	.common	b,4,4
	.section	".text"
	.align 4
	.global main
	.type	main, #function
	.proc	04
main:
	save	%sp, -112, %sp
	sethi	%hi(X), %g1
	or	%g1, %lo(X), %g1
	ldd	[%g1], %f8
	std	%f8, [%fp-8]
	ldd	[%fp-8], %o0
	call	sqrt, 0
	 nop
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	fdtoi	%f8, %f10
	st	%f10, [%fp-12]
	ld	[%fp-12], %g2
	sethi	%hi(b), %g1
	or	%g1, %lo(b), %g1
	st	%g2, [%g1]
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	main, .-main
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
