	.file	"helpers.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"\nHiFromAjit\n\n"
	.section	".text"
	.align 4
	.global ajit_init
	.type	ajit_init, #function
	.proc	020
ajit_init:
	save	%sp, -96, %sp
	mov	1, %o0
	mov	0, %o1
	mov	0, %o2
	sethi	%hi(.LC0), %i0
	call	__ajit_serial_configure__, 0
	 mov	13, %i1
	call	__ajit_serial_puts__, 0
	 restore %i0, %lo(.LC0), %o0
	.size	ajit_init, .-ajit_init
	.align 4
	.global barebones_clock
	.type	barebones_clock, #function
	.proc	016
barebones_clock:
	save	%sp, -96, %sp
	call	__ajit_read_cycle_count_register_high__, 0
	 nop
	call	__ajit_read_cycle_count_register_low__, 0
	 mov	%o0, %i0
	sll	%i0, 24, %g1
	srl	%o0, 8, %o0
	or	%o0, %g1, %i0
	jmp	%i7+8
	 restore
	.size	barebones_clock, .-barebones_clock
	.ident	"GCC: (Buildroot 2014.08-gfff9e93) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
