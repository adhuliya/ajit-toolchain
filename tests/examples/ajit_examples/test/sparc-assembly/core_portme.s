	.file	"core_portme.c"
	.section	".text"
	.align 4
	.global ajit_serial_init
	.type	ajit_serial_init, #function
	.proc	020
ajit_serial_init:
	mov	1, %o0
	mov	0, %o1
	mov	0, %o2
	or	%o7, %g0, %g1
	call	__ajit_serial_configure__, 0
	 or	%g1, %g0, %o7
	.size	ajit_serial_init, .-ajit_serial_init
	.align 4
	.global ajit_barebones_clock
	.type	ajit_barebones_clock, #function
	.proc	016
ajit_barebones_clock:
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
	.size	ajit_barebones_clock, .-ajit_barebones_clock
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
