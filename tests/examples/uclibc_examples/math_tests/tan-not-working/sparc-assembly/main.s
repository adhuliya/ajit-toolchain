	.file	"main.c"
	.common	b,4,4
	.section	".rodata"
	.align 8
.LC0:
	.long	1073291771
	.long	1413754136
	.section	".text"
	.align 4
	.global main
	.type	main, #function
	.proc	020
main:
	save	%sp, -112, %sp
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldd	[%g1], %f8
	std	%f8, [%fp-8]
	ldd	[%fp-8], %o0
	call	tan, 0
	 nop
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	fdtoi	%f8, %f10
	st	%f10, [%fp-12]
	ld	[%fp-12], %g2
	sethi	%hi(b), %g1
	or	%g1, %lo(b), %g1
	st	%g2, [%g1]
	restore
	jmp	%o7+8
	 nop
	.size	main, .-main
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
