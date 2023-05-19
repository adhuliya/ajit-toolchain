	.file	"additional_serial.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.align 4
	.global __ajit_write_serial_1_control_register_via_bypass__
	.type	__ajit_write_serial_1_control_register_via_bypass__, #function
	.proc	020
__ajit_write_serial_1_control_register_via_bypass__:
.LFB0:
	.file 1 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c"
	.loc 1 7 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 8 0
	ld	[%fp+68], %g1
	sethi	%hi(-53248), %g2
	or	%g2, 576, %g2
#APP
! 8 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
	.loc 1 9 0
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE0:
	.size	__ajit_write_serial_1_control_register_via_bypass__, .-__ajit_write_serial_1_control_register_via_bypass__
	.align 4
	.global __ajit_read_serial_1_control_register_via_bypass__
	.type	__ajit_read_serial_1_control_register_via_bypass__, #function
	.proc	016
__ajit_read_serial_1_control_register_via_bypass__:
.LFB1:
	.loc 1 12 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI1:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 14 0
	sethi	%hi(-53248), %g1
	or	%g1, 576, %g1
#APP
! 14 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lda [%g1] 32, %i5
	
! 0 "" 2
#NO_APP
	st	%i5, [%fp-4]
	.loc 1 15 0
	ld	[%fp-4], %g1
	.loc 1 16 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE1:
	.size	__ajit_read_serial_1_control_register_via_bypass__, .-__ajit_read_serial_1_control_register_via_bypass__
	.align 4
	.global __ajit_write_serial_1_tx_register_via_bypass__
	.type	__ajit_write_serial_1_tx_register_via_bypass__, #function
	.proc	020
__ajit_write_serial_1_tx_register_via_bypass__:
.LFB2:
	.loc 1 19 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI2:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 20 0
	ldub	[%fp+68], %g1
	sethi	%hi(-53248), %g2
	or	%g2, 580, %g2
#APP
! 20 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	stuba %g1, [%g2] 32
	
! 0 "" 2
	.loc 1 21 0
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE2:
	.size	__ajit_write_serial_1_tx_register_via_bypass__, .-__ajit_write_serial_1_tx_register_via_bypass__
	.align 4
	.global __ajit_read_serial_1_tx_register_via_bypass__
	.type	__ajit_read_serial_1_tx_register_via_bypass__, #function
	.proc	014
__ajit_read_serial_1_tx_register_via_bypass__:
.LFB3:
	.loc 1 23 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI3:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 25 0
	sethi	%hi(-53248), %g1
	or	%g1, 580, %g1
#APP
! 25 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lduba [%g1] 32, %i5
	
! 0 "" 2
#NO_APP
	stb	%i5, [%fp-1]
	.loc 1 26 0
	ldub	[%fp-1], %g1
	and	%g1, 0xff, %g1
	.loc 1 27 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE3:
	.size	__ajit_read_serial_1_tx_register_via_bypass__, .-__ajit_read_serial_1_tx_register_via_bypass__
	.align 4
	.global __ajit_read_serial_1_rx_register_via_bypass__
	.type	__ajit_read_serial_1_rx_register_via_bypass__, #function
	.proc	014
__ajit_read_serial_1_rx_register_via_bypass__:
.LFB4:
	.loc 1 29 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI4:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 31 0
	sethi	%hi(-53248), %g1
	or	%g1, 584, %g1
#APP
! 31 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lduba [%g1] 32, %i5
	
! 0 "" 2
#NO_APP
	stb	%i5, [%fp-1]
	.loc 1 32 0
	ldub	[%fp-1], %g1
	and	%g1, 0xff, %g1
	.loc 1 33 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE4:
	.size	__ajit_read_serial_1_rx_register_via_bypass__, .-__ajit_read_serial_1_rx_register_via_bypass__
	.align 4
	.global __ajit_serial_1_putchar_via_bypass__
	.type	__ajit_serial_1_putchar_via_bypass__, #function
	.proc	04
__ajit_serial_1_putchar_via_bypass__:
.LFB5:
	.loc 1 37 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI5:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 38 0
	ldub	[%fp+68], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	mov	0, %o0
	mov	1, %o1
	mov	%g1, %o2
	call	__ajit_serial_putchar_inner__, 0
	 nop
	mov	%o0, %g1
	.loc 1 39 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE5:
	.size	__ajit_serial_1_putchar_via_bypass__, .-__ajit_serial_1_putchar_via_bypass__
	.align 4
	.global __ajit_serial_1_getchar_via_bypass__
	.type	__ajit_serial_1_getchar_via_bypass__, #function
	.proc	04
__ajit_serial_1_getchar_via_bypass__:
.LFB6:
	.loc 1 42 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI6:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 46 0
	add	%fp, -1, %g1
	mov	0, %o0
	mov	1, %o1
	mov	%g1, %o2
	call	__ajit_serial_getchar_inner__, 0
	 nop
	.loc 1 48 0
	ldub	[%fp-1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	.loc 1 49 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE6:
	.size	__ajit_serial_1_getchar_via_bypass__, .-__ajit_serial_1_getchar_via_bypass__
	.align 4
	.global __ajit_serial_1_puts_via_bypass__
	.type	__ajit_serial_1_puts_via_bypass__, #function
	.proc	020
__ajit_serial_1_puts_via_bypass__:
.LFB7:
	.loc 1 52 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI7:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	.loc 1 53 0
	mov	0, %o0
	mov	1, %o1
	ld	[%fp+68], %o2
	ld	[%fp+72], %o3
	call	__ajit_serial_puts_inner__, 0
	 nop
	nop
	.loc 1 54 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE7:
	.size	__ajit_serial_1_puts_via_bypass__, .-__ajit_serial_1_puts_via_bypass__
	.align 4
	.global __ajit_serial_1_gets_via_bypass__
	.type	__ajit_serial_1_gets_via_bypass__, #function
	.proc	020
__ajit_serial_1_gets_via_bypass__:
.LFB8:
	.loc 1 56 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI8:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	.loc 1 57 0
	mov	0, %o0
	mov	1, %o1
	ld	[%fp+68], %o2
	ld	[%fp+72], %o3
	call	__ajit_serial_gets_inner__, 0
	 nop
	.loc 1 58 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE8:
	.size	__ajit_serial_1_gets_via_bypass__, .-__ajit_serial_1_gets_via_bypass__
	.align 4
	.global __ajit_serial_1_configure_via_bypass__
	.type	__ajit_serial_1_configure_via_bypass__, #function
	.proc	020
__ajit_serial_1_configure_via_bypass__:
.LFB9:
	.loc 1 61 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI9:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g3
	mov	%i1, %g2
	mov	%i2, %g1
	stb	%g3, [%fp+68]
	stb	%g2, [%fp+72]
	stb	%g1, [%fp+76]
	.loc 1 62 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g3
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g2
	ldub	[%fp+76], %g1
	and	%g1, 0xff, %g1
	mov	0, %o0
	mov	1, %o1
	mov	%g3, %o2
	mov	%g2, %o3
	mov	%g1, %o4
	call	__ajit_serial_configure_inner__, 0
	 nop
	.loc 1 63 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE9:
	.size	__ajit_serial_1_configure_via_bypass__, .-__ajit_serial_1_configure_via_bypass__
	.align 4
	.global __ajit_read_serial_1_baud_limit_register_via_bypass__
	.type	__ajit_read_serial_1_baud_limit_register_via_bypass__, #function
	.proc	016
__ajit_read_serial_1_baud_limit_register_via_bypass__:
.LFB10:
	.loc 1 65 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI10:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 67 0
	sethi	%hi(-53248), %g1
	or	%g1, 588, %g1
#APP
! 67 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lda [%g1] 32, %i5
	
! 0 "" 2
#NO_APP
	st	%i5, [%fp-4]
	.loc 1 68 0
	ld	[%fp-4], %g1
	.loc 1 69 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE10:
	.size	__ajit_read_serial_1_baud_limit_register_via_bypass__, .-__ajit_read_serial_1_baud_limit_register_via_bypass__
	.align 4
	.global __ajit_write_serial_1_baud_limit_register_via_bypass__
	.type	__ajit_write_serial_1_baud_limit_register_via_bypass__, #function
	.proc	020
__ajit_write_serial_1_baud_limit_register_via_bypass__:
.LFB11:
	.loc 1 72 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI11:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 73 0
	ld	[%fp+68], %g1
	sethi	%hi(-53248), %g2
	or	%g2, 588, %g2
#APP
! 73 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
	.loc 1 74 0
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE11:
	.size	__ajit_write_serial_1_baud_limit_register_via_bypass__, .-__ajit_write_serial_1_baud_limit_register_via_bypass__
	.align 4
	.global __ajit_read_serial_1_baud_frequency_register_via_bypass__
	.type	__ajit_read_serial_1_baud_frequency_register_via_bypass__, #function
	.proc	016
__ajit_read_serial_1_baud_frequency_register_via_bypass__:
.LFB12:
	.loc 1 77 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI12:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 79 0
	sethi	%hi(-53248), %g1
	or	%g1, 592, %g1
#APP
! 79 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	lda [%g1] 32, %i5
	
! 0 "" 2
#NO_APP
	st	%i5, [%fp-4]
	.loc 1 80 0
	ld	[%fp-4], %g1
	.loc 1 81 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE12:
	.size	__ajit_read_serial_1_baud_frequency_register_via_bypass__, .-__ajit_read_serial_1_baud_frequency_register_via_bypass__
	.align 4
	.global __ajit_write_serial_1_baud_frequency_register_via_bypass__
	.type	__ajit_write_serial_1_baud_frequency_register_via_bypass__, #function
	.proc	020
__ajit_write_serial_1_baud_frequency_register_via_bypass__:
.LFB13:
	.loc 1 84 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI13:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 85 0
	ld	[%fp+68], %g1
	sethi	%hi(-53248), %g2
	or	%g2, 592, %g2
#APP
! 85 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
	.loc 1 86 0
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE13:
	.size	__ajit_write_serial_1_baud_frequency_register_via_bypass__, .-__ajit_write_serial_1_baud_frequency_register_via_bypass__
	.align 4
	.global __ajit_serial_1_set_baudrate_via_bypass__
	.type	__ajit_serial_1_set_baudrate_via_bypass__, #function
	.proc	020
__ajit_serial_1_set_baudrate_via_bypass__:
.LFB14:
	.loc 1 90 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI14:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	.loc 1 91 0
	mov	1, %o0
	mov	1, %o1
	ld	[%fp+68], %o2
	ld	[%fp+72], %o3
	call	__ajit_serial_set_baudrate_inner__, 0
	 nop
	.loc 1 92 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE14:
	.size	__ajit_serial_1_set_baudrate_via_bypass__, .-__ajit_serial_1_set_baudrate_via_bypass__
	.align 4
	.global __ajit_serial_1_set_uart_reset_via_bypass__
	.type	__ajit_serial_1_set_uart_reset_via_bypass__, #function
	.proc	020
__ajit_serial_1_set_uart_reset_via_bypass__:
.LFB15:
	.loc 1 95 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI15:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 96 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	1, %o0
	mov	1, %o1
	mov	%g1, %o2
	call	__ajit_serial_set_uart_reset_inner__, 0
	 nop
	.loc 1 97 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE15:
	.size	__ajit_serial_1_set_uart_reset_via_bypass__, .-__ajit_serial_1_set_uart_reset_via_bypass__
	.align 4
	.global __ajit_write_serial_1_control_register_via_vmap__
	.type	__ajit_write_serial_1_control_register_via_vmap__, #function
	.proc	020
__ajit_write_serial_1_control_register_via_vmap__:
.LFB16:
	.loc 1 101 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI16:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 102 0
	sethi	%hi(-53248), %g1
	or	%g1, 576, %g1
	ld	[%fp+68], %g2
	st	%g2, [%g1]
	.loc 1 103 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE16:
	.size	__ajit_write_serial_1_control_register_via_vmap__, .-__ajit_write_serial_1_control_register_via_vmap__
	.align 4
	.global __ajit_read_serial_1_control_register_via_vmap__
	.type	__ajit_read_serial_1_control_register_via_vmap__, #function
	.proc	016
__ajit_read_serial_1_control_register_via_vmap__:
.LFB17:
	.loc 1 106 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI17:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 107 0
	sethi	%hi(-53248), %g1
	or	%g1, 576, %g1
	ldub	[%g1], %g1
	and	%g1, 0xff, %g1
	st	%g1, [%fp-4]
	.loc 1 108 0
	ld	[%fp-4], %g1
	.loc 1 109 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE17:
	.size	__ajit_read_serial_1_control_register_via_vmap__, .-__ajit_read_serial_1_control_register_via_vmap__
	.align 4
	.global __ajit_write_serial_1_tx_register_via_vmap__
	.type	__ajit_write_serial_1_tx_register_via_vmap__, #function
	.proc	020
__ajit_write_serial_1_tx_register_via_vmap__:
.LFB18:
	.loc 1 112 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI18:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 113 0
	sethi	%hi(-53248), %g1
	or	%g1, 580, %g1
	ldub	[%fp+68], %g2
	stb	%g2, [%g1]
	.loc 1 114 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE18:
	.size	__ajit_write_serial_1_tx_register_via_vmap__, .-__ajit_write_serial_1_tx_register_via_vmap__
	.align 4
	.global __ajit_read_serial_1_tx_register_via_vmap__
	.type	__ajit_read_serial_1_tx_register_via_vmap__, #function
	.proc	014
__ajit_read_serial_1_tx_register_via_vmap__:
.LFB19:
	.loc 1 116 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI19:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 117 0
	sethi	%hi(-53248), %g1
	or	%g1, 580, %g1
	ldub	[%g1], %g1
	stb	%g1, [%fp-1]
	.loc 1 118 0
	ldub	[%fp-1], %g1
	and	%g1, 0xff, %g1
	.loc 1 119 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE19:
	.size	__ajit_read_serial_1_tx_register_via_vmap__, .-__ajit_read_serial_1_tx_register_via_vmap__
	.align 4
	.global __ajit_read_serial_1_rx_register_via_vmap__
	.type	__ajit_read_serial_1_rx_register_via_vmap__, #function
	.proc	014
__ajit_read_serial_1_rx_register_via_vmap__:
.LFB20:
	.loc 1 121 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI20:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 122 0
	sethi	%hi(-53248), %g1
	or	%g1, 584, %g1
	ldub	[%g1], %g1
	stb	%g1, [%fp-1]
	.loc 1 123 0
	ldub	[%fp-1], %g1
	and	%g1, 0xff, %g1
	.loc 1 124 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE20:
	.size	__ajit_read_serial_1_rx_register_via_vmap__, .-__ajit_read_serial_1_rx_register_via_vmap__
	.align 4
	.global __ajit_serial_1_putchar_via_vmap__
	.type	__ajit_serial_1_putchar_via_vmap__, #function
	.proc	04
__ajit_serial_1_putchar_via_vmap__:
.LFB21:
	.loc 1 128 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI21:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 129 0
	ldub	[%fp+68], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	mov	1, %o0
	mov	1, %o1
	mov	%g1, %o2
	call	__ajit_serial_putchar_inner__, 0
	 nop
	mov	%o0, %g1
	.loc 1 130 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE21:
	.size	__ajit_serial_1_putchar_via_vmap__, .-__ajit_serial_1_putchar_via_vmap__
	.align 4
	.global __ajit_serial_1_getchar_via_vmap__
	.type	__ajit_serial_1_getchar_via_vmap__, #function
	.proc	04
__ajit_serial_1_getchar_via_vmap__:
.LFB22:
	.loc 1 133 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI22:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 137 0
	add	%fp, -1, %g1
	mov	1, %o0
	mov	1, %o1
	mov	%g1, %o2
	call	__ajit_serial_getchar_inner__, 0
	 nop
	.loc 1 139 0
	ldub	[%fp-1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	.loc 1 140 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE22:
	.size	__ajit_serial_1_getchar_via_vmap__, .-__ajit_serial_1_getchar_via_vmap__
	.align 4
	.global __ajit_serial_1_puts_via_vmap__
	.type	__ajit_serial_1_puts_via_vmap__, #function
	.proc	020
__ajit_serial_1_puts_via_vmap__:
.LFB23:
	.loc 1 143 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI23:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	.loc 1 144 0
	mov	1, %o0
	mov	1, %o1
	ld	[%fp+68], %o2
	ld	[%fp+72], %o3
	call	__ajit_serial_puts_inner__, 0
	 nop
	nop
	.loc 1 145 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE23:
	.size	__ajit_serial_1_puts_via_vmap__, .-__ajit_serial_1_puts_via_vmap__
	.align 4
	.global __ajit_serial_1_gets_via_vmap__
	.type	__ajit_serial_1_gets_via_vmap__, #function
	.proc	020
__ajit_serial_1_gets_via_vmap__:
.LFB24:
	.loc 1 147 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI24:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	.loc 1 148 0
	mov	1, %o0
	mov	1, %o1
	ld	[%fp+68], %o2
	ld	[%fp+72], %o3
	call	__ajit_serial_gets_inner__, 0
	 nop
	.loc 1 149 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE24:
	.size	__ajit_serial_1_gets_via_vmap__, .-__ajit_serial_1_gets_via_vmap__
	.align 4
	.global __ajit_serial_1_configure_via_vmap__
	.type	__ajit_serial_1_configure_via_vmap__, #function
	.proc	020
__ajit_serial_1_configure_via_vmap__:
.LFB25:
	.loc 1 152 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI25:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g3
	mov	%i1, %g2
	mov	%i2, %g1
	stb	%g3, [%fp+68]
	stb	%g2, [%fp+72]
	stb	%g1, [%fp+76]
	.loc 1 153 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g3
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g2
	ldub	[%fp+76], %g1
	and	%g1, 0xff, %g1
	mov	1, %o0
	mov	1, %o1
	mov	%g3, %o2
	mov	%g2, %o3
	mov	%g1, %o4
	call	__ajit_serial_configure_inner__, 0
	 nop
	.loc 1 154 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE25:
	.size	__ajit_serial_1_configure_via_vmap__, .-__ajit_serial_1_configure_via_vmap__
	.align 4
	.global __ajit_read_serial_1_baud_limit_register_via_vmap__
	.type	__ajit_read_serial_1_baud_limit_register_via_vmap__, #function
	.proc	016
__ajit_read_serial_1_baud_limit_register_via_vmap__:
.LFB26:
	.loc 1 156 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI26:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 157 0
	sethi	%hi(-53248), %g1
	or	%g1, 588, %g1
	ld	[%g1], %g1
	st	%g1, [%fp-4]
	.loc 1 158 0
	ld	[%fp-4], %g1
	.loc 1 159 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE26:
	.size	__ajit_read_serial_1_baud_limit_register_via_vmap__, .-__ajit_read_serial_1_baud_limit_register_via_vmap__
	.align 4
	.global __ajit_write_serial_1_baud_limit_register_via_vmap__
	.type	__ajit_write_serial_1_baud_limit_register_via_vmap__, #function
	.proc	020
__ajit_write_serial_1_baud_limit_register_via_vmap__:
.LFB27:
	.loc 1 162 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI27:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 163 0
	sethi	%hi(-53248), %g1
	or	%g1, 588, %g1
	ld	[%fp+68], %g2
	st	%g2, [%g1]
	.loc 1 164 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE27:
	.size	__ajit_write_serial_1_baud_limit_register_via_vmap__, .-__ajit_write_serial_1_baud_limit_register_via_vmap__
	.align 4
	.global __ajit_read_serial_1_baud_frequency_register_via_vmap__
	.type	__ajit_read_serial_1_baud_frequency_register_via_vmap__, #function
	.proc	016
__ajit_read_serial_1_baud_frequency_register_via_vmap__:
.LFB28:
	.loc 1 167 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI28:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 168 0
	sethi	%hi(-53248), %g1
	or	%g1, 592, %g1
	ld	[%g1], %g1
	st	%g1, [%fp-4]
	.loc 1 169 0
	ld	[%fp-4], %g1
	.loc 1 170 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE28:
	.size	__ajit_read_serial_1_baud_frequency_register_via_vmap__, .-__ajit_read_serial_1_baud_frequency_register_via_vmap__
	.align 4
	.global __ajit_write_serial_1_baud_frequency_register_via_vmap__
	.type	__ajit_write_serial_1_baud_frequency_register_via_vmap__, #function
	.proc	020
__ajit_write_serial_1_baud_frequency_register_via_vmap__:
.LFB29:
	.loc 1 173 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI29:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 174 0
	sethi	%hi(-53248), %g1
	or	%g1, 592, %g1
	ld	[%fp+68], %g2
	st	%g2, [%g1]
	.loc 1 175 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE29:
	.size	__ajit_write_serial_1_baud_frequency_register_via_vmap__, .-__ajit_write_serial_1_baud_frequency_register_via_vmap__
	.align 4
	.global __ajit_serial_1_set_baudrate_via_vmap__
	.type	__ajit_serial_1_set_baudrate_via_vmap__, #function
	.proc	020
__ajit_serial_1_set_baudrate_via_vmap__:
.LFB30:
	.loc 1 179 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI30:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	.loc 1 180 0
	mov	1, %o0
	mov	1, %o1
	ld	[%fp+68], %o2
	ld	[%fp+72], %o3
	call	__ajit_serial_set_baudrate_inner__, 0
	 nop
	.loc 1 181 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE30:
	.size	__ajit_serial_1_set_baudrate_via_vmap__, .-__ajit_serial_1_set_baudrate_via_vmap__
	.align 4
	.global __ajit_serial_1_set_uart_reset_via_vmap__
	.type	__ajit_serial_1_set_uart_reset_via_vmap__, #function
	.proc	020
__ajit_serial_1_set_uart_reset_via_vmap__:
.LFB31:
	.loc 1 184 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI31:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 185 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	1, %o0
	mov	1, %o1
	mov	%g1, %o2
	call	__ajit_serial_set_uart_reset_inner__, 0
	 nop
	.loc 1 186 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE31:
	.size	__ajit_serial_1_set_uart_reset_via_vmap__, .-__ajit_serial_1_set_uart_reset_via_vmap__
.Letext0:
	.file 2 "/home/ajit4/ajit-toolchain/build/buildroot-2014.08/output/host/usr/lib/gcc/sparc-buildroot-linux-uclibc/4.7.4/include/stdint-gcc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x670
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF53
	.byte	0x1
	.uaword	.LASF54
	.uaword	.Ltext0
	.uaword	.Letext0
	.uaword	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF0
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.uaword	.LASF1
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.uaword	.LASF2
	.uleb128 0x4
	.uaword	.LASF5
	.byte	0x2
	.byte	0x2e
	.uaword	0x48
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.uaword	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.uaword	.LASF4
	.uleb128 0x4
	.uaword	.LASF6
	.byte	0x2
	.byte	0x34
	.uaword	0x61
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.uaword	.LASF8
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF9
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.uaword	.LASF10
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF11
	.uleb128 0x5
	.byte	0x4
	.uaword	0x8a
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF12
	.uleb128 0x6
	.byte	0x1
	.uaword	.LASF13
	.byte	0x1
	.byte	0x6
	.byte	0x1
	.uaword	.LFB0
	.uaword	.LFE0
	.uaword	.LLST0
	.byte	0x1
	.uaword	0xbb
	.uleb128 0x7
	.asciz	"val"
	.byte	0x1
	.byte	0x6
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF14
	.byte	0x1
	.byte	0xb
	.uaword	0x56
	.uaword	.LFB1
	.uaword	.LFE1
	.uaword	.LLST1
	.byte	0x1
	.uaword	0xe7
	.uleb128 0x9
	.asciz	"val"
	.byte	0x1
	.byte	0xd
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.uaword	.LASF15
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.uaword	.LFB2
	.uaword	.LFE2
	.uaword	.LLST2
	.byte	0x1
	.uaword	0x111
	.uleb128 0x7
	.asciz	"val"
	.byte	0x1
	.byte	0x12
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF16
	.byte	0x1
	.byte	0x16
	.uaword	0x3d
	.uaword	.LFB3
	.uaword	.LFE3
	.uaword	.LLST3
	.byte	0x1
	.uaword	0x13d
	.uleb128 0x9
	.asciz	"val"
	.byte	0x1
	.byte	0x18
	.uaword	0x3d
	.byte	0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF17
	.byte	0x1
	.byte	0x1c
	.uaword	0x3d
	.uaword	.LFB4
	.uaword	.LFE4
	.uaword	.LLST4
	.byte	0x1
	.uaword	0x169
	.uleb128 0x9
	.asciz	"val"
	.byte	0x1
	.byte	0x1e
	.uaword	0x3d
	.byte	0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0xa
	.byte	0x1
	.uaword	.LASF41
	.byte	0x1
	.byte	0x24
	.byte	0x1
	.uaword	0x2f
	.uaword	.LFB5
	.uaword	.LFE5
	.uaword	.LLST5
	.byte	0x1
	.uaword	0x195
	.uleb128 0x7
	.asciz	"c"
	.byte	0x1
	.byte	0x24
	.uaword	0x8a
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0xb
	.byte	0x1
	.uaword	.LASF18
	.byte	0x1
	.byte	0x29
	.uaword	0x2f
	.uaword	.LFB6
	.uaword	.LFE6
	.uaword	.LLST6
	.byte	0x1
	.uaword	0x1bf
	.uleb128 0x9
	.asciz	"c"
	.byte	0x1
	.byte	0x2c
	.uaword	0x8a
	.byte	0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF19
	.byte	0x1
	.byte	0x33
	.byte	0x1
	.uaword	.LFB7
	.uaword	.LFE7
	.uaword	.LLST7
	.byte	0x1
	.uaword	0x1f6
	.uleb128 0x7
	.asciz	"s"
	.byte	0x1
	.byte	0x33
	.uaword	0x84
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.uaword	.LASF20
	.byte	0x1
	.byte	0x33
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF21
	.byte	0x1
	.byte	0x37
	.byte	0x1
	.uaword	.LFB8
	.uaword	.LFE8
	.uaword	.LLST8
	.byte	0x1
	.uaword	0x22d
	.uleb128 0x7
	.asciz	"s"
	.byte	0x1
	.byte	0x37
	.uaword	0x84
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.uaword	.LASF20
	.byte	0x1
	.byte	0x37
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF22
	.byte	0x1
	.byte	0x3c
	.byte	0x1
	.uaword	.LFB9
	.uaword	.LFE9
	.uaword	.LLST9
	.byte	0x1
	.uaword	0x275
	.uleb128 0xd
	.uaword	.LASF23
	.byte	0x1
	.byte	0x3c
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.uaword	.LASF24
	.byte	0x1
	.byte	0x3c
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0xd
	.uaword	.LASF25
	.byte	0x1
	.byte	0x3c
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF26
	.byte	0x1
	.byte	0x40
	.uaword	0x56
	.uaword	.LFB10
	.uaword	.LFE10
	.uaword	.LLST10
	.byte	0x1
	.uaword	0x2a1
	.uleb128 0x9
	.asciz	"val"
	.byte	0x1
	.byte	0x42
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.uaword	.LASF27
	.byte	0x1
	.byte	0x47
	.byte	0x1
	.uaword	.LFB11
	.uaword	.LFE11
	.uaword	.LLST11
	.byte	0x1
	.uaword	0x2cb
	.uleb128 0x7
	.asciz	"bcv"
	.byte	0x1
	.byte	0x47
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF28
	.byte	0x1
	.byte	0x4c
	.uaword	0x56
	.uaword	.LFB12
	.uaword	.LFE12
	.uaword	.LLST12
	.byte	0x1
	.uaword	0x2f7
	.uleb128 0x9
	.asciz	"val"
	.byte	0x1
	.byte	0x4e
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.uaword	.LASF29
	.byte	0x1
	.byte	0x53
	.byte	0x1
	.uaword	.LFB13
	.uaword	.LFE13
	.uaword	.LLST13
	.byte	0x1
	.uaword	0x321
	.uleb128 0x7
	.asciz	"bcv"
	.byte	0x1
	.byte	0x53
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF30
	.byte	0x1
	.byte	0x59
	.byte	0x1
	.uaword	.LFB14
	.uaword	.LFE14
	.uaword	.LLST14
	.byte	0x1
	.uaword	0x35a
	.uleb128 0xd
	.uaword	.LASF31
	.byte	0x1
	.byte	0x59
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.uaword	.LASF32
	.byte	0x1
	.byte	0x59
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF33
	.byte	0x1
	.byte	0x5e
	.byte	0x1
	.uaword	.LFB15
	.uaword	.LFE15
	.uaword	.LLST15
	.byte	0x1
	.uaword	0x384
	.uleb128 0xd
	.uaword	.LASF34
	.byte	0x1
	.byte	0x5e
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.uaword	.LASF35
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.uaword	.LFB16
	.uaword	.LFE16
	.uaword	.LLST16
	.byte	0x1
	.uaword	0x3ae
	.uleb128 0x7
	.asciz	"val"
	.byte	0x1
	.byte	0x64
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF36
	.byte	0x1
	.byte	0x69
	.uaword	0x56
	.uaword	.LFB17
	.uaword	.LFE17
	.uaword	.LLST17
	.byte	0x1
	.uaword	0x3da
	.uleb128 0xe
	.uaword	.LASF37
	.byte	0x1
	.byte	0x6b
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.uaword	.LASF38
	.byte	0x1
	.byte	0x6f
	.byte	0x1
	.uaword	.LFB18
	.uaword	.LFE18
	.uaword	.LLST18
	.byte	0x1
	.uaword	0x404
	.uleb128 0x7
	.asciz	"val"
	.byte	0x1
	.byte	0x6f
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF39
	.byte	0x1
	.byte	0x73
	.uaword	0x3d
	.uaword	.LFB19
	.uaword	.LFE19
	.uaword	.LLST19
	.byte	0x1
	.uaword	0x430
	.uleb128 0xe
	.uaword	.LASF37
	.byte	0x1
	.byte	0x75
	.uaword	0x3d
	.byte	0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF40
	.byte	0x1
	.byte	0x78
	.uaword	0x3d
	.uaword	.LFB20
	.uaword	.LFE20
	.uaword	.LLST20
	.byte	0x1
	.uaword	0x45c
	.uleb128 0xe
	.uaword	.LASF37
	.byte	0x1
	.byte	0x7a
	.uaword	0x3d
	.byte	0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0xa
	.byte	0x1
	.uaword	.LASF42
	.byte	0x1
	.byte	0x7f
	.byte	0x1
	.uaword	0x2f
	.uaword	.LFB21
	.uaword	.LFE21
	.uaword	.LLST21
	.byte	0x1
	.uaword	0x488
	.uleb128 0x7
	.asciz	"c"
	.byte	0x1
	.byte	0x7f
	.uaword	0x8a
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0xb
	.byte	0x1
	.uaword	.LASF43
	.byte	0x1
	.byte	0x84
	.uaword	0x2f
	.uaword	.LFB22
	.uaword	.LFE22
	.uaword	.LLST22
	.byte	0x1
	.uaword	0x4b2
	.uleb128 0x9
	.asciz	"c"
	.byte	0x1
	.byte	0x87
	.uaword	0x8a
	.byte	0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF44
	.byte	0x1
	.byte	0x8e
	.byte	0x1
	.uaword	.LFB23
	.uaword	.LFE23
	.uaword	.LLST23
	.byte	0x1
	.uaword	0x4e9
	.uleb128 0x7
	.asciz	"s"
	.byte	0x1
	.byte	0x8e
	.uaword	0x84
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.uaword	.LASF20
	.byte	0x1
	.byte	0x8e
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF45
	.byte	0x1
	.byte	0x92
	.byte	0x1
	.uaword	.LFB24
	.uaword	.LFE24
	.uaword	.LLST24
	.byte	0x1
	.uaword	0x520
	.uleb128 0x7
	.asciz	"s"
	.byte	0x1
	.byte	0x92
	.uaword	0x84
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.uaword	.LASF20
	.byte	0x1
	.byte	0x92
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF46
	.byte	0x1
	.byte	0x97
	.byte	0x1
	.uaword	.LFB25
	.uaword	.LFE25
	.uaword	.LLST25
	.byte	0x1
	.uaword	0x568
	.uleb128 0xd
	.uaword	.LASF23
	.byte	0x1
	.byte	0x97
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.uaword	.LASF24
	.byte	0x1
	.byte	0x97
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0xd
	.uaword	.LASF25
	.byte	0x1
	.byte	0x97
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF47
	.byte	0x1
	.byte	0x9b
	.uaword	0x56
	.uaword	.LFB26
	.uaword	.LFE26
	.uaword	.LLST26
	.byte	0x1
	.uaword	0x594
	.uleb128 0xe
	.uaword	.LASF48
	.byte	0x1
	.byte	0x9d
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.uaword	.LASF49
	.byte	0x1
	.byte	0xa1
	.byte	0x1
	.uaword	.LFB27
	.uaword	.LFE27
	.uaword	.LLST27
	.byte	0x1
	.uaword	0x5be
	.uleb128 0x7
	.asciz	"bcv"
	.byte	0x1
	.byte	0xa1
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.uaword	.LASF50
	.byte	0x1
	.byte	0xa6
	.uaword	0x56
	.uaword	.LFB28
	.uaword	.LFE28
	.uaword	.LLST28
	.byte	0x1
	.uaword	0x5ea
	.uleb128 0xe
	.uaword	.LASF48
	.byte	0x1
	.byte	0xa8
	.uaword	0x56
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x6
	.byte	0x1
	.uaword	.LASF51
	.byte	0x1
	.byte	0xac
	.byte	0x1
	.uaword	.LFB29
	.uaword	.LFE29
	.uaword	.LLST29
	.byte	0x1
	.uaword	0x614
	.uleb128 0x7
	.asciz	"bcv"
	.byte	0x1
	.byte	0xac
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF52
	.byte	0x1
	.byte	0xb2
	.byte	0x1
	.uaword	.LFB30
	.uaword	.LFE30
	.uaword	.LLST30
	.byte	0x1
	.uaword	0x64d
	.uleb128 0xd
	.uaword	.LASF31
	.byte	0x1
	.byte	0xb2
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.uaword	.LASF32
	.byte	0x1
	.byte	0xb2
	.uaword	0x56
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0xf
	.byte	0x1
	.uaword	.LASF55
	.byte	0x1
	.byte	0xb7
	.byte	0x1
	.uaword	.LFB31
	.uaword	.LFE31
	.uaword	.LLST31
	.byte	0x1
	.uleb128 0xd
	.uaword	.LASF34
	.byte	0x1
	.byte	0xb7
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.uaword	.LFB0-.Ltext0
	.uaword	.LCFI0-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI0-.Ltext0
	.uaword	.LFE0-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST1:
	.uaword	.LFB1-.Ltext0
	.uaword	.LCFI1-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI1-.Ltext0
	.uaword	.LFE1-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST2:
	.uaword	.LFB2-.Ltext0
	.uaword	.LCFI2-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI2-.Ltext0
	.uaword	.LFE2-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST3:
	.uaword	.LFB3-.Ltext0
	.uaword	.LCFI3-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI3-.Ltext0
	.uaword	.LFE3-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST4:
	.uaword	.LFB4-.Ltext0
	.uaword	.LCFI4-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI4-.Ltext0
	.uaword	.LFE4-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST5:
	.uaword	.LFB5-.Ltext0
	.uaword	.LCFI5-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI5-.Ltext0
	.uaword	.LFE5-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST6:
	.uaword	.LFB6-.Ltext0
	.uaword	.LCFI6-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI6-.Ltext0
	.uaword	.LFE6-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST7:
	.uaword	.LFB7-.Ltext0
	.uaword	.LCFI7-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI7-.Ltext0
	.uaword	.LFE7-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST8:
	.uaword	.LFB8-.Ltext0
	.uaword	.LCFI8-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI8-.Ltext0
	.uaword	.LFE8-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST9:
	.uaword	.LFB9-.Ltext0
	.uaword	.LCFI9-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI9-.Ltext0
	.uaword	.LFE9-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST10:
	.uaword	.LFB10-.Ltext0
	.uaword	.LCFI10-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI10-.Ltext0
	.uaword	.LFE10-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST11:
	.uaword	.LFB11-.Ltext0
	.uaword	.LCFI11-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI11-.Ltext0
	.uaword	.LFE11-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST12:
	.uaword	.LFB12-.Ltext0
	.uaword	.LCFI12-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI12-.Ltext0
	.uaword	.LFE12-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST13:
	.uaword	.LFB13-.Ltext0
	.uaword	.LCFI13-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI13-.Ltext0
	.uaword	.LFE13-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST14:
	.uaword	.LFB14-.Ltext0
	.uaword	.LCFI14-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI14-.Ltext0
	.uaword	.LFE14-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST15:
	.uaword	.LFB15-.Ltext0
	.uaword	.LCFI15-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI15-.Ltext0
	.uaword	.LFE15-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST16:
	.uaword	.LFB16-.Ltext0
	.uaword	.LCFI16-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI16-.Ltext0
	.uaword	.LFE16-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST17:
	.uaword	.LFB17-.Ltext0
	.uaword	.LCFI17-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI17-.Ltext0
	.uaword	.LFE17-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST18:
	.uaword	.LFB18-.Ltext0
	.uaword	.LCFI18-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI18-.Ltext0
	.uaword	.LFE18-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST19:
	.uaword	.LFB19-.Ltext0
	.uaword	.LCFI19-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI19-.Ltext0
	.uaword	.LFE19-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST20:
	.uaword	.LFB20-.Ltext0
	.uaword	.LCFI20-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI20-.Ltext0
	.uaword	.LFE20-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST21:
	.uaword	.LFB21-.Ltext0
	.uaword	.LCFI21-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI21-.Ltext0
	.uaword	.LFE21-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST22:
	.uaword	.LFB22-.Ltext0
	.uaword	.LCFI22-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI22-.Ltext0
	.uaword	.LFE22-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST23:
	.uaword	.LFB23-.Ltext0
	.uaword	.LCFI23-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI23-.Ltext0
	.uaword	.LFE23-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST24:
	.uaword	.LFB24-.Ltext0
	.uaword	.LCFI24-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI24-.Ltext0
	.uaword	.LFE24-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST25:
	.uaword	.LFB25-.Ltext0
	.uaword	.LCFI25-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI25-.Ltext0
	.uaword	.LFE25-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST26:
	.uaword	.LFB26-.Ltext0
	.uaword	.LCFI26-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI26-.Ltext0
	.uaword	.LFE26-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST27:
	.uaword	.LFB27-.Ltext0
	.uaword	.LCFI27-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI27-.Ltext0
	.uaword	.LFE27-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST28:
	.uaword	.LFB28-.Ltext0
	.uaword	.LCFI28-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI28-.Ltext0
	.uaword	.LFE28-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST29:
	.uaword	.LFB29-.Ltext0
	.uaword	.LCFI29-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI29-.Ltext0
	.uaword	.LFE29-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST30:
	.uaword	.LFB30-.Ltext0
	.uaword	.LCFI30-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI30-.Ltext0
	.uaword	.LFE30-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST31:
	.uaword	.LFB31-.Ltext0
	.uaword	.LCFI31-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI31-.Ltext0
	.uaword	.LFE31-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
	.section	.debug_aranges,"",@progbits
	.uaword	0x1c
	.uahalf	0x2
	.uaword	.Ldebug_info0
	.byte	0x4
	.byte	0
	.uahalf	0
	.uahalf	0
	.uaword	.Ltext0
	.uaword	.Letext0-.Ltext0
	.uaword	0
	.uaword	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF49:
	.asciz	"__ajit_write_serial_1_baud_limit_register_via_vmap__"
.LASF36:
	.asciz	"__ajit_read_serial_1_control_register_via_vmap__"
.LASF39:
	.asciz	"__ajit_read_serial_1_tx_register_via_vmap__"
.LASF25:
	.asciz	"enable_intr"
.LASF33:
	.asciz	"__ajit_serial_1_set_uart_reset_via_bypass__"
.LASF38:
	.asciz	"__ajit_write_serial_1_tx_register_via_vmap__"
.LASF19:
	.asciz	"__ajit_serial_1_puts_via_bypass__"
.LASF27:
	.asciz	"__ajit_write_serial_1_baud_limit_register_via_bypass__"
.LASF34:
	.asciz	"reset_value"
.LASF30:
	.asciz	"__ajit_serial_1_set_baudrate_via_bypass__"
.LASF12:
	.asciz	"char"
.LASF35:
	.asciz	"__ajit_write_serial_1_control_register_via_vmap__"
.LASF16:
	.asciz	"__ajit_read_serial_1_tx_register_via_bypass__"
.LASF31:
	.asciz	"baud_rate"
.LASF21:
	.asciz	"__ajit_serial_1_gets_via_bypass__"
.LASF48:
	.asciz	"retval"
.LASF46:
	.asciz	"__ajit_serial_1_configure_via_vmap__"
.LASF9:
	.asciz	"long unsigned int"
.LASF4:
	.asciz	"short unsigned int"
.LASF44:
	.asciz	"__ajit_serial_1_puts_via_vmap__"
.LASF13:
	.asciz	"__ajit_write_serial_1_control_register_via_bypass__"
.LASF54:
	.asciz	"/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/additional_serial.c"
.LASF14:
	.asciz	"__ajit_read_serial_1_control_register_via_bypass__"
.LASF17:
	.asciz	"__ajit_read_serial_1_rx_register_via_bypass__"
.LASF55:
	.asciz	"__ajit_serial_1_set_uart_reset_via_vmap__"
.LASF3:
	.asciz	"unsigned char"
.LASF43:
	.asciz	"__ajit_serial_1_getchar_via_vmap__"
.LASF52:
	.asciz	"__ajit_serial_1_set_baudrate_via_vmap__"
.LASF37:
	.asciz	"ret_val"
.LASF24:
	.asciz	"enable_rx"
.LASF50:
	.asciz	"__ajit_read_serial_1_baud_frequency_register_via_vmap__"
.LASF41:
	.asciz	"__ajit_serial_1_putchar_via_bypass__"
.LASF7:
	.asciz	"unsigned int"
.LASF23:
	.asciz	"enable_tx"
.LASF8:
	.asciz	"long long unsigned int"
.LASF5:
	.asciz	"uint8_t"
.LASF51:
	.asciz	"__ajit_write_serial_1_baud_frequency_register_via_vmap__"
.LASF47:
	.asciz	"__ajit_read_serial_1_baud_limit_register_via_vmap__"
.LASF11:
	.asciz	"sizetype"
.LASF22:
	.asciz	"__ajit_serial_1_configure_via_bypass__"
.LASF2:
	.asciz	"long long int"
.LASF26:
	.asciz	"__ajit_read_serial_1_baud_limit_register_via_bypass__"
.LASF40:
	.asciz	"__ajit_read_serial_1_rx_register_via_vmap__"
.LASF29:
	.asciz	"__ajit_write_serial_1_baud_frequency_register_via_bypass__"
.LASF53:
	.asciz	"GNU C 4.7.4"
.LASF1:
	.asciz	"short int"
.LASF45:
	.asciz	"__ajit_serial_1_gets_via_vmap__"
.LASF32:
	.asciz	"clock_frequency"
.LASF28:
	.asciz	"__ajit_read_serial_1_baud_frequency_register_via_bypass__"
.LASF10:
	.asciz	"long int"
.LASF42:
	.asciz	"__ajit_serial_1_putchar_via_vmap__"
.LASF20:
	.asciz	"length"
.LASF0:
	.asciz	"signed char"
.LASF6:
	.asciz	"uint32_t"
.LASF18:
	.asciz	"__ajit_serial_1_getchar_via_bypass__"
.LASF15:
	.asciz	"__ajit_write_serial_1_tx_register_via_bypass__"
	.ident	"GCC: (Buildroot 2014.08-ga2bdb80-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
