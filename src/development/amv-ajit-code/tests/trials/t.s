	.file	"test.c"
	.section	".rodata"
	.align 8
.LC0:
	.asciz	"x1 = 0x%08X.\n"
	.align 8
.LC1:
	.asciz	"x2 = 0x%08X.\n"
	.align 8
.LC2:
	.asciz	"x3 = 0x%08X.\n"
	.align 8
.LC3:
	.asciz	"x4 = 0x%08X.\n"
	.align 8
.LC4:
	.asciz	"x5 = 0x%08X.\n"
	.align 8
.LC5:
	.asciz	"j  = 0x%08X.\n"
	.section	".text"
	.align 4
	.global main
	.type	main, #function
	.proc	04
main:
	save	%sp, -128, %sp
	addd    %g1, %g2, %g1 /* Safe */
	mov	170, %g1
	st	%g1, [%fp-12]
	mov	3, %g1
	st	%g1, [%fp-16]
	mov	204, %g1
	st	%g1, [%fp-20]
	ld	[%fp-12], %g2
	ld	[%fp-16], %g1
	sra	%g2, %g1, %g1
	st	%g1, [%fp-24]
	ld	[%fp-24], %g2
	ld	[%fp-20], %g1
	and	%g2, %g1, %g1
	st	%g1, [%fp-28]
	st	%g0, [%fp-4]
	st	%g0, [%fp-8]
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %o0
	ld	[%fp-12], %o1
	call	printf, 0
	 nop
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %o0
	ld	[%fp-16], %o1
	call	printf, 0
	 nop
	sethi	%hi(.LC2), %g1
	or	%g1, %lo(.LC2), %o0
	ld	[%fp-20], %o1
	call	printf, 0
	 nop
	sethi	%hi(.LC3), %g1
	or	%g1, %lo(.LC3), %o0
	ld	[%fp-24], %o1
	call	printf, 0
	 nop
	sethi	%hi(.LC4), %g1
	or	%g1, %lo(.LC4), %o0
	ld	[%fp-28], %o1
	call	printf, 0
	 nop
	ld	[%fp-12], %g1
	st	%g1, [%fp-8]
	sethi	%hi(.LC5), %g1
	or	%g1, %lo(.LC5), %o0
	ld	[%fp-8], %o1
	call	printf, 0
	 nop
	ld	[%fp-16], %g1
	st	%g1, [%fp-4]
	b	.L2
	 nop
.L3:
	ld	[%fp-8], %g1
	sra	%g1, 1, %g1
	st	%g1, [%fp-8]
	sethi	%hi(.LC5), %g1
	or	%g1, %lo(.LC5), %o0
	ld	[%fp-8], %o1
	call	printf, 0
	 nop
	ld	[%fp-4], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp-4]
.L2:
	ld	[%fp-4], %g1
	cmp	%g1, 0
	bg	.L3
	 nop
	mov	0, %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	main, .-main
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
