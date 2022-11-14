	.file	"additional_serial.c"
	.section	".text"
	.align 4
	.global __ajit_write_serial_1_control_register_via_bypass__
	.type	__ajit_write_serial_1_control_register_via_bypass__, #function
	.proc	020
__ajit_write_serial_1_control_register_via_bypass__:
	sethi	%hi(-53248), %g1
	or	%g1, 576, %g1
#APP
! 8 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	sta %o0, [%g1] 32
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	__ajit_write_serial_1_control_register_via_bypass__, .-__ajit_write_serial_1_control_register_via_bypass__
	.align 4
	.global __ajit_read_serial_1_control_register_via_bypass__
	.type	__ajit_read_serial_1_control_register_via_bypass__, #function
	.proc	016
__ajit_read_serial_1_control_register_via_bypass__:
	sethi	%hi(-53248), %o0
	or	%o0, 576, %o0
#APP
! 14 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lda [%o0] 32, %o0
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	__ajit_read_serial_1_control_register_via_bypass__, .-__ajit_read_serial_1_control_register_via_bypass__
	.align 4
	.global __ajit_write_serial_1_tx_register_via_bypass__
	.type	__ajit_write_serial_1_tx_register_via_bypass__, #function
	.proc	020
__ajit_write_serial_1_tx_register_via_bypass__:
	sethi	%hi(-53248), %g1
	or	%g1, 580, %g1
#APP
! 20 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	stuba %o0, [%g1] 32
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	__ajit_write_serial_1_tx_register_via_bypass__, .-__ajit_write_serial_1_tx_register_via_bypass__
	.align 4
	.global __ajit_read_serial_1_tx_register_via_bypass__
	.type	__ajit_read_serial_1_tx_register_via_bypass__, #function
	.proc	014
__ajit_read_serial_1_tx_register_via_bypass__:
	sethi	%hi(-53248), %o0
	or	%o0, 580, %o0
#APP
! 25 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lduba [%o0] 32, %o0
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 and	%o0, 0xff, %o0
	.size	__ajit_read_serial_1_tx_register_via_bypass__, .-__ajit_read_serial_1_tx_register_via_bypass__
	.align 4
	.global __ajit_read_serial_1_rx_register_via_bypass__
	.type	__ajit_read_serial_1_rx_register_via_bypass__, #function
	.proc	014
__ajit_read_serial_1_rx_register_via_bypass__:
	sethi	%hi(-53248), %o0
	or	%o0, 584, %o0
#APP
! 31 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lduba [%o0] 32, %o0
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 and	%o0, 0xff, %o0
	.size	__ajit_read_serial_1_rx_register_via_bypass__, .-__ajit_read_serial_1_rx_register_via_bypass__
	.align 4
	.global __ajit_serial_1_putchar_via_bypass__
	.type	__ajit_serial_1_putchar_via_bypass__, #function
	.proc	04
__ajit_serial_1_putchar_via_bypass__:
	mov	%o0, %o2
	mov	1, %o1
	mov	0, %o0
	or	%o7, %g0, %g1
	call	__ajit_serial_putchar_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_putchar_via_bypass__, .-__ajit_serial_1_putchar_via_bypass__
	.align 4
	.global __ajit_serial_1_getchar_via_bypass__
	.type	__ajit_serial_1_getchar_via_bypass__, #function
	.proc	04
__ajit_serial_1_getchar_via_bypass__:
	save	%sp, -104, %sp
	mov	1, %o1
	add	%fp, -1, %o2
	call	__ajit_serial_getchar_inner__, 0
	 mov	0, %o0
	ldsb	[%fp-1], %i0
	jmp	%i7+8
	 restore
	.size	__ajit_serial_1_getchar_via_bypass__, .-__ajit_serial_1_getchar_via_bypass__
	.align 4
	.global __ajit_serial_1_puts_via_bypass__
	.type	__ajit_serial_1_puts_via_bypass__, #function
	.proc	020
__ajit_serial_1_puts_via_bypass__:
	mov	%o0, %o2
	mov	%o1, %o3
	mov	0, %o0
	mov	1, %o1
	or	%o7, %g0, %g1
	call	__ajit_serial_puts_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_puts_via_bypass__, .-__ajit_serial_1_puts_via_bypass__
	.align 4
	.global __ajit_serial_1_gets_via_bypass__
	.type	__ajit_serial_1_gets_via_bypass__, #function
	.proc	020
__ajit_serial_1_gets_via_bypass__:
	mov	%o0, %o2
	mov	%o1, %o3
	mov	0, %o0
	mov	1, %o1
	or	%o7, %g0, %g1
	call	__ajit_serial_gets_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_gets_via_bypass__, .-__ajit_serial_1_gets_via_bypass__
	.align 4
	.global __ajit_serial_1_configure_via_bypass__
	.type	__ajit_serial_1_configure_via_bypass__, #function
	.proc	020
__ajit_serial_1_configure_via_bypass__:
	mov	%o0, %g1
	mov	%o1, %o3
	mov	%o2, %o4
	mov	0, %o0
	mov	1, %o1
	mov	%g1, %o2
	or	%o7, %g0, %g1
	call	__ajit_serial_configure_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_configure_via_bypass__, .-__ajit_serial_1_configure_via_bypass__
	.align 4
	.global __ajit_read_serial_1_baud_limit_register_via_bypass__
	.type	__ajit_read_serial_1_baud_limit_register_via_bypass__, #function
	.proc	016
__ajit_read_serial_1_baud_limit_register_via_bypass__:
	sethi	%hi(-53248), %o0
	or	%o0, 588, %o0
#APP
! 67 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lda [%o0] 32, %o0
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	__ajit_read_serial_1_baud_limit_register_via_bypass__, .-__ajit_read_serial_1_baud_limit_register_via_bypass__
	.align 4
	.global __ajit_write_serial_1_baud_limit_register_via_bypass__
	.type	__ajit_write_serial_1_baud_limit_register_via_bypass__, #function
	.proc	020
__ajit_write_serial_1_baud_limit_register_via_bypass__:
	sethi	%hi(-53248), %g1
	or	%g1, 588, %g1
#APP
! 73 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	sta %o0, [%g1] 32
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	__ajit_write_serial_1_baud_limit_register_via_bypass__, .-__ajit_write_serial_1_baud_limit_register_via_bypass__
	.align 4
	.global __ajit_read_serial_1_baud_frequency_register_via_bypass__
	.type	__ajit_read_serial_1_baud_frequency_register_via_bypass__, #function
	.proc	016
__ajit_read_serial_1_baud_frequency_register_via_bypass__:
	sethi	%hi(-53248), %o0
	or	%o0, 592, %o0
#APP
! 79 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lda [%o0] 32, %o0
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	__ajit_read_serial_1_baud_frequency_register_via_bypass__, .-__ajit_read_serial_1_baud_frequency_register_via_bypass__
	.align 4
	.global __ajit_write_serial_1_baud_frequency_register_via_bypass__
	.type	__ajit_write_serial_1_baud_frequency_register_via_bypass__, #function
	.proc	020
__ajit_write_serial_1_baud_frequency_register_via_bypass__:
	sethi	%hi(-53248), %g1
	or	%g1, 592, %g1
#APP
! 85 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	sta %o0, [%g1] 32
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	__ajit_write_serial_1_baud_frequency_register_via_bypass__, .-__ajit_write_serial_1_baud_frequency_register_via_bypass__
	.align 4
	.global __ajit_serial_1_set_baudrate_via_bypass__
	.type	__ajit_serial_1_set_baudrate_via_bypass__, #function
	.proc	020
__ajit_serial_1_set_baudrate_via_bypass__:
	mov	%o0, %o2
	mov	%o1, %o3
	mov	1, %o0
	mov	1, %o1
	or	%o7, %g0, %g1
	call	__ajit_serial_set_baudrate_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_set_baudrate_via_bypass__, .-__ajit_serial_1_set_baudrate_via_bypass__
	.align 4
	.global __ajit_serial_1_set_uart_reset_via_bypass__
	.type	__ajit_serial_1_set_uart_reset_via_bypass__, #function
	.proc	020
__ajit_serial_1_set_uart_reset_via_bypass__:
	mov	%o0, %o2
	mov	1, %o1
	mov	1, %o0
	or	%o7, %g0, %g1
	call	__ajit_serial_set_uart_reset_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_set_uart_reset_via_bypass__, .-__ajit_serial_1_set_uart_reset_via_bypass__
	.align 4
	.global __ajit_write_serial_1_control_register_via_vmap__
	.type	__ajit_write_serial_1_control_register_via_vmap__, #function
	.proc	020
__ajit_write_serial_1_control_register_via_vmap__:
	sethi	%hi(-53248), %g1
	or	%g1, 576, %g1
	jmp	%o7+8
	 st	%o0, [%g1]
	.size	__ajit_write_serial_1_control_register_via_vmap__, .-__ajit_write_serial_1_control_register_via_vmap__
	.align 4
	.global __ajit_read_serial_1_control_register_via_vmap__
	.type	__ajit_read_serial_1_control_register_via_vmap__, #function
	.proc	016
__ajit_read_serial_1_control_register_via_vmap__:
	sethi	%hi(-53248), %g1
	or	%g1, 576, %g1
	jmp	%o7+8
	 ldub	[%g1], %o0
	.size	__ajit_read_serial_1_control_register_via_vmap__, .-__ajit_read_serial_1_control_register_via_vmap__
	.align 4
	.global __ajit_write_serial_1_tx_register_via_vmap__
	.type	__ajit_write_serial_1_tx_register_via_vmap__, #function
	.proc	020
__ajit_write_serial_1_tx_register_via_vmap__:
	sethi	%hi(-53248), %g1
	or	%g1, 580, %g1
	jmp	%o7+8
	 stb	%o0, [%g1]
	.size	__ajit_write_serial_1_tx_register_via_vmap__, .-__ajit_write_serial_1_tx_register_via_vmap__
	.align 4
	.global __ajit_read_serial_1_tx_register_via_vmap__
	.type	__ajit_read_serial_1_tx_register_via_vmap__, #function
	.proc	014
__ajit_read_serial_1_tx_register_via_vmap__:
	sethi	%hi(-53248), %g1
	or	%g1, 580, %g1
	jmp	%o7+8
	 ldub	[%g1], %o0
	.size	__ajit_read_serial_1_tx_register_via_vmap__, .-__ajit_read_serial_1_tx_register_via_vmap__
	.align 4
	.global __ajit_read_serial_1_rx_register_via_vmap__
	.type	__ajit_read_serial_1_rx_register_via_vmap__, #function
	.proc	014
__ajit_read_serial_1_rx_register_via_vmap__:
	sethi	%hi(-53248), %g1
	or	%g1, 584, %g1
	jmp	%o7+8
	 ldub	[%g1], %o0
	.size	__ajit_read_serial_1_rx_register_via_vmap__, .-__ajit_read_serial_1_rx_register_via_vmap__
	.align 4
	.global __ajit_serial_1_putchar_via_vmap__
	.type	__ajit_serial_1_putchar_via_vmap__, #function
	.proc	04
__ajit_serial_1_putchar_via_vmap__:
	mov	%o0, %o2
	mov	1, %o1
	mov	1, %o0
	or	%o7, %g0, %g1
	call	__ajit_serial_putchar_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_putchar_via_vmap__, .-__ajit_serial_1_putchar_via_vmap__
	.align 4
	.global __ajit_serial_1_getchar_via_vmap__
	.type	__ajit_serial_1_getchar_via_vmap__, #function
	.proc	04
__ajit_serial_1_getchar_via_vmap__:
	save	%sp, -104, %sp
	mov	1, %o1
	add	%fp, -1, %o2
	call	__ajit_serial_getchar_inner__, 0
	 mov	1, %o0
	ldsb	[%fp-1], %i0
	jmp	%i7+8
	 restore
	.size	__ajit_serial_1_getchar_via_vmap__, .-__ajit_serial_1_getchar_via_vmap__
	.align 4
	.global __ajit_serial_1_puts_via_vmap__
	.type	__ajit_serial_1_puts_via_vmap__, #function
	.proc	020
__ajit_serial_1_puts_via_vmap__:
	mov	%o0, %o2
	mov	%o1, %o3
	mov	1, %o0
	mov	1, %o1
	or	%o7, %g0, %g1
	call	__ajit_serial_puts_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_puts_via_vmap__, .-__ajit_serial_1_puts_via_vmap__
	.align 4
	.global __ajit_serial_1_gets_via_vmap__
	.type	__ajit_serial_1_gets_via_vmap__, #function
	.proc	020
__ajit_serial_1_gets_via_vmap__:
	mov	%o0, %o2
	mov	%o1, %o3
	mov	1, %o0
	mov	1, %o1
	or	%o7, %g0, %g1
	call	__ajit_serial_gets_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_gets_via_vmap__, .-__ajit_serial_1_gets_via_vmap__
	.align 4
	.global __ajit_serial_1_configure_via_vmap__
	.type	__ajit_serial_1_configure_via_vmap__, #function
	.proc	020
__ajit_serial_1_configure_via_vmap__:
	mov	%o0, %g1
	mov	%o1, %o3
	mov	%o2, %o4
	mov	1, %o0
	mov	1, %o1
	mov	%g1, %o2
	or	%o7, %g0, %g1
	call	__ajit_serial_configure_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_configure_via_vmap__, .-__ajit_serial_1_configure_via_vmap__
	.align 4
	.global __ajit_read_serial_1_baud_limit_register_via_vmap__
	.type	__ajit_read_serial_1_baud_limit_register_via_vmap__, #function
	.proc	016
__ajit_read_serial_1_baud_limit_register_via_vmap__:
	sethi	%hi(-53248), %g1
	or	%g1, 588, %g1
	jmp	%o7+8
	 ld	[%g1], %o0
	.size	__ajit_read_serial_1_baud_limit_register_via_vmap__, .-__ajit_read_serial_1_baud_limit_register_via_vmap__
	.align 4
	.global __ajit_write_serial_1_baud_limit_register_via_vmap__
	.type	__ajit_write_serial_1_baud_limit_register_via_vmap__, #function
	.proc	020
__ajit_write_serial_1_baud_limit_register_via_vmap__:
	sethi	%hi(-53248), %g1
	or	%g1, 588, %g1
	jmp	%o7+8
	 st	%o0, [%g1]
	.size	__ajit_write_serial_1_baud_limit_register_via_vmap__, .-__ajit_write_serial_1_baud_limit_register_via_vmap__
	.align 4
	.global __ajit_read_serial_1_baud_frequency_register_via_vmap__
	.type	__ajit_read_serial_1_baud_frequency_register_via_vmap__, #function
	.proc	016
__ajit_read_serial_1_baud_frequency_register_via_vmap__:
	sethi	%hi(-53248), %g1
	or	%g1, 592, %g1
	jmp	%o7+8
	 ld	[%g1], %o0
	.size	__ajit_read_serial_1_baud_frequency_register_via_vmap__, .-__ajit_read_serial_1_baud_frequency_register_via_vmap__
	.align 4
	.global __ajit_write_serial_1_baud_frequency_register_via_vmap__
	.type	__ajit_write_serial_1_baud_frequency_register_via_vmap__, #function
	.proc	020
__ajit_write_serial_1_baud_frequency_register_via_vmap__:
	sethi	%hi(-53248), %g1
	or	%g1, 592, %g1
	jmp	%o7+8
	 st	%o0, [%g1]
	.size	__ajit_write_serial_1_baud_frequency_register_via_vmap__, .-__ajit_write_serial_1_baud_frequency_register_via_vmap__
	.align 4
	.global __ajit_serial_1_set_baudrate_via_vmap__
	.type	__ajit_serial_1_set_baudrate_via_vmap__, #function
	.proc	020
__ajit_serial_1_set_baudrate_via_vmap__:
	mov	%o0, %o2
	mov	%o1, %o3
	mov	1, %o0
	mov	1, %o1
	or	%o7, %g0, %g1
	call	__ajit_serial_set_baudrate_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_set_baudrate_via_vmap__, .-__ajit_serial_1_set_baudrate_via_vmap__
	.align 4
	.global __ajit_serial_1_set_uart_reset_via_vmap__
	.type	__ajit_serial_1_set_uart_reset_via_vmap__, #function
	.proc	020
__ajit_serial_1_set_uart_reset_via_vmap__:
	mov	%o0, %o2
	mov	1, %o1
	mov	1, %o0
	or	%o7, %g0, %g1
	call	__ajit_serial_set_uart_reset_inner__, 0
	 or	%g1, %g0, %o7
	.size	__ajit_serial_1_set_uart_reset_via_vmap__, .-__ajit_serial_1_set_uart_reset_via_vmap__
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
