	.file	"mem.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"Fact: %u\n"
	.section	".text"
	.align 4
	.global mem_march
	.type	mem_march, #function
	.proc	020
mem_march:
	cmp	%o0, 0
	ble	.L4
	 add	%o0, 1, %o0
	mov	1, %o1
	mov	1, %g1
	smul	%o1, %g1, %o1
.L7:
	add	%g1, 1, %g1
	cmp	%g1, %o0
	bne,a	.L7
	 smul	%o1, %g1, %o1
.L2:
	sethi	%hi(.LC0), %g2
	or	%g2, %lo(.LC0), %o0
	or	%o7, %g0, %g1
	call	ee_printf, 0
	 or	%g1, %g0, %o7
.L4:
	b	.L2
	 mov	1, %o1
	.size	mem_march, .-mem_march
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
