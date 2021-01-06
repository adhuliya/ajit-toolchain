	.file	"main.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"March-time (ticks)=%u\n"
	.align 8
.LC1:
	.asciz	"ERROR\n"
	.align 8
.LC2:
	.asciz	"OK\n"
	.section	.text.startup,"ax",@progbits
	.align 4
	.global main
	.type	main, #function
	.proc	04
main:
	save	%sp, -96, %sp
	call	ajit_serial_init, 0
	 nop
	call	ajit_barebones_clock, 0
	 nop
	mov	%o0, %i3
	call	mem_march, 0
	 mov	4, %o0
	mov	%o1, %i5
	call	ajit_barebones_clock, 0
	 mov	%o0, %i4
	sub	%o0, %i3, %o1
	sethi	%hi(.LC0), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC0), %o0
	orcc	%i4, %i5, %g0
	bne	.L6
	 sethi	%hi(.LC2), %g2
	call	ee_printf, 0
	 or	%g2, %lo(.LC2), %o0
.L4:
	jmp	%i7+8
	 restore %g0, 0, %o0
.L6:
	sethi	%hi(.LC1), %g1
	call	ee_printf, 0
	 or	%g1, %lo(.LC1), %o0
	b,a	.L4
	.size	main, .-main
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
