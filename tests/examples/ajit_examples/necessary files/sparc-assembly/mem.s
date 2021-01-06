	.file	"mem.c"
	.section	".text"
	.align 4
	.global mem_march
	.type	mem_march, #function
	.proc	017
mem_march:
	save	%sp, -96, %sp
	mov	0, %i4
	cmp	%i0, 0
	ble	.L10
	 mov	0, %i5
	sethi	%hi(mem_array), %o7
	mov	0, %o4
	or	%o7, %lo(mem_array), %o7
	mov	0, %o5
	mov	0, %i4
	mov	0, %i5
	add	%o7, 64, %i1
.L2:
	mov	%o7, %g4
	mov	%o7, %g1
	mov	%o4, %g2
	mov	%o5, %g3
.L4:
	std	%g2, [%g1]
	addcc	%g3, 1, %o3
	add	%g1, 8, %g1
	addx	%g2, 0, %o2
	mov	%o3, %g3
	cmp	%g1, %i1
	bne	.L4
	 mov	%o2, %g2
	mov	%o4, %g1
	mov	%o5, %g3
.L5:
	ldd	[%g4], %i2
	xor	%g3, %i3, %i3
	addcc	%g3, 1, %g3
	xor	%g1, %i2, %i2
	addx	%g1, 0, %g2
	add	%g4, 8, %g4
	mov	%g2, %g1
	or	%i4, %i2, %i4
	cmp	%g4, %i1
	bne	.L5
	 or	%i5, %i3, %i5
	addcc	%o5, 1, %g4
	addx	%o4, 0, %i2
	mov	%g4, %o5
	cmp	%i0, %g4
	bg	.L2
	 mov	%i2, %o4
.L10:
	mov	%i4, %i0
	jmp	%i7+8
	 restore %g0, %i5, %o1
	.size	mem_march, .-mem_march
	.common	mem_array,64,8
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
