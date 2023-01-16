	.file	"cortos_devices.c"
	.section	".text"
	.align 4
	.global __cortos_enable_serial
	.type	__cortos_enable_serial, #function
	.proc	020
__cortos_enable_serial:
	mov	3, %o0
	or	%o7, %g0, %g1
	call	__ajit_write_serial_control_register_via_bypass__, 0
	 or	%g1, %g0, %o7
	.size	__cortos_enable_serial, .-__cortos_enable_serial
	.align 4
	.global __cortos_enable_serial_interrupt
	.type	__cortos_enable_serial_interrupt, #function
	.proc	020
__cortos_enable_serial_interrupt:
	mov	7, %o0
	or	%o7, %g0, %g1
	call	__ajit_write_serial_control_register_via_bypass__, 0
	 or	%g1, %g0, %o7
	.size	__cortos_enable_serial_interrupt, .-__cortos_enable_serial_interrupt
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
