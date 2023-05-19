	.file	"ajit_spi_flash.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.align 4
	.global ajit_spi_transfer_is_in_progress
	.type	ajit_spi_transfer_is_in_progress, #function
	.proc	016
ajit_spi_transfer_is_in_progress:
.LFB3:
	.file 1 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c"
	.loc 1 12 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 17 0
	sethi	%hi(-53248), %g1
	or	%g1, 776, %g1
#APP
! 17 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	lda [%g1] 32, %i5
	
! 0 "" 2
#NO_APP
	st	%i5, [%fp-4]
	.loc 1 19 0
	ld	[%fp-4], %g1
	and	%g1, 1, %g1
	.loc 1 20 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE3:
	.size	ajit_spi_transfer_is_in_progress, .-ajit_spi_transfer_is_in_progress
	.align 4
	.global ajit_spi_flash_send_byte
	.type	ajit_spi_flash_send_byte, #function
	.proc	020
ajit_spi_flash_send_byte:
.LFB4:
	.loc 1 27 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI1:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g3
	mov	%i1, %g2
	mov	%i2, %g1
	stb	%g3, [%fp+68]
	stb	%g2, [%fp+72]
	stb	%g1, [%fp+76]
	.loc 1 32 0
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g1
	sethi	%hi(-53248), %g2
	or	%g2, 768, %g2
#APP
! 32 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
	.loc 1 36 0
#NO_APP
	ldub	[%fp+76], %g1
	and	%g1, 0xff, %g1
	and	%g1, 1, %g1
	add	%g1, %g1, %g1
	or	%g1, 1, %g2
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	and	%g1, 7, %g1
	sll	%g1, 3, %g1
	or	%g2, %g1, %g1
	st	%g1, [%fp-4]
	.loc 1 40 0
	ld	[%fp-4], %g1
	sethi	%hi(-53248), %g2
	or	%g2, 776, %g2
#APP
! 40 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
	.loc 1 44 0
#NO_APP
	b	.L4
	 nop
.L5:
	.loc 1 47 0
	mov	64, %o0
	call	__ajit_sleep__, 0
	 nop
.L4:
	.loc 1 44 0 discriminator 1
	call	ajit_spi_transfer_is_in_progress, 0
	 nop
	mov	%o0, %g1
	cmp	%g1, 0
	bne	.L5
	 nop
	.loc 1 49 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE4:
	.size	ajit_spi_flash_send_byte, .-ajit_spi_flash_send_byte
	.align 4
	.global ajit_spi_flash_receive_byte
	.type	ajit_spi_flash_receive_byte, #function
	.proc	014
ajit_spi_flash_receive_byte:
.LFB5:
	.loc 1 52 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI2:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g2
	mov	%i1, %g1
	stb	%g2, [%fp+68]
	stb	%g1, [%fp+72]
	.loc 1 56 0
	mov	0, %g1
	sethi	%hi(-53248), %g2
	or	%g2, 768, %g2
#APP
! 56 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
	.loc 1 59 0
#NO_APP
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g1
	and	%g1, 1, %g1
	add	%g1, %g1, %g1
	or	%g1, 1, %g2
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	and	%g1, 7, %g1
	sll	%g1, 3, %g1
	or	%g2, %g1, %g1
	st	%g1, [%fp-4]
	.loc 1 64 0
	ld	[%fp-4], %g1
	sethi	%hi(-53248), %g2
	or	%g2, 776, %g2
#APP
! 64 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
#NO_APP
.L9:
.LBB2:
	.loc 1 73 0
	ld	[%fp-8], %g1
	sethi	%hi(-53248), %g2
	or	%g2, 776, %g2
#APP
! 73 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
	.loc 1 75 0
#NO_APP
	ld	[%fp-8], %g1
	and	%g1, 1, %g1
	cmp	%g1, 0
	be	.L12
	 nop
.L7:
	.loc 1 79 0
	mov	64, %o0
	call	__ajit_sleep__, 0
	 nop
.LBE2:
	.loc 1 80 0
	b	.L9
	 nop
.L12:
.LBB3:
	.loc 1 76 0
	nop
.L11:
.LBE3:
	.loc 1 86 0
	sethi	%hi(-53248), %g1
	or	%g1, 768, %g1
#APP
! 86 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	lda [%g1] 32, %i5
	
! 0 "" 2
#NO_APP
	stb	%i5, [%fp-9]
	.loc 1 88 0
	ldub	[%fp-9], %g1
	and	%g1, 0xff, %g1
	.loc 1 89 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE5:
	.size	ajit_spi_flash_receive_byte, .-ajit_spi_flash_receive_byte
	.align 4
	.global ajit_spi_flash_reset
	.type	ajit_spi_flash_reset, #function
	.proc	020
ajit_spi_flash_reset:
.LFB6:
	.loc 1 92 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI3:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 93 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	102, %o1
	mov	1, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 94 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE6:
	.size	ajit_spi_flash_reset, .-ajit_spi_flash_reset
	.align 4
	.global ajit_spi_flash_memory_reset
	.type	ajit_spi_flash_memory_reset, #function
	.proc	020
ajit_spi_flash_memory_reset:
.LFB7:
	.loc 1 97 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI4:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 98 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	153, %o1
	mov	1, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 99 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE7:
	.size	ajit_spi_flash_memory_reset, .-ajit_spi_flash_memory_reset
	.align 4
	.global ajit_spi_set_clock_frequency
	.type	ajit_spi_set_clock_frequency, #function
	.proc	020
ajit_spi_set_clock_frequency:
.LFB8:
	.loc 1 102 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI5:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 103 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	and	%g1, 15, %g1
	or	%g1, 16, %g1
	st	%g1, [%fp-4]
	.loc 1 107 0
	ld	[%fp-4], %g1
	sethi	%hi(-53248), %g2
	or	%g2, 780, %g2
#APP
! 107 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
	.loc 1 109 0
#NO_APP
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE8:
	.size	ajit_spi_set_clock_frequency, .-ajit_spi_set_clock_frequency
	.align 4
	.global ajit_spi_flash_is_busy
	.type	ajit_spi_flash_is_busy, #function
	.proc	016
ajit_spi_flash_is_busy:
.LFB9:
	.loc 1 112 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI6:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	.loc 1 113 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	5, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 114 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	1, %o1
	call	ajit_spi_flash_receive_byte, 0
	 nop
	mov	%o0, %g1
	and	%g1, 0xff, %g1
	st	%g1, [%fp-4]
	.loc 1 117 0
	ld	[%fp-4], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-4]
	.loc 1 119 0
	ld	[%fp-4], %g1
	.loc 1 120 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE9:
	.size	ajit_spi_flash_is_busy, .-ajit_spi_flash_is_busy
	.align 4
	.global ajit_spi_flash_generic_erase
	.type	ajit_spi_flash_generic_erase, #function
	.proc	020
ajit_spi_flash_generic_erase:
.LFB10:
	.loc 1 124 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI7:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g2
	mov	%i1, %g1
	st	%i2, [%fp+76]
	stb	%g2, [%fp+68]
	stb	%g1, [%fp+72]
	.loc 1 126 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	6, %o1
	mov	1, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 129 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g2
	ldub	[%fp+72], %g1
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 132 0
	ld	[%fp+76], %g1
	srl	%g1, 16, %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g2
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 133 0
	ld	[%fp+76], %g1
	srl	%g1, 8, %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g2
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 134 0
	ld	[%fp+76], %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g2
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	1, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 136 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	4, %o1
	mov	1, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 137 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE10:
	.size	ajit_spi_flash_generic_erase, .-ajit_spi_flash_generic_erase
	.align 4
	.global ajit_spi_flash_subsector_erase
	.type	ajit_spi_flash_subsector_erase, #function
	.proc	020
ajit_spi_flash_subsector_erase:
.LFB11:
	.loc 1 140 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI8:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	st	%i1, [%fp+72]
	stb	%g1, [%fp+68]
	.loc 1 141 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	32, %o1
	ld	[%fp+72], %o2
	call	ajit_spi_flash_generic_erase, 0
	 nop
	.loc 1 142 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE11:
	.size	ajit_spi_flash_subsector_erase, .-ajit_spi_flash_subsector_erase
	.align 4
	.global ajit_spi_flash_sector_erase
	.type	ajit_spi_flash_sector_erase, #function
	.proc	020
ajit_spi_flash_sector_erase:
.LFB12:
	.loc 1 144 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI9:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	st	%i1, [%fp+72]
	stb	%g1, [%fp+68]
	.loc 1 145 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	216, %o1
	ld	[%fp+72], %o2
	call	ajit_spi_flash_generic_erase, 0
	 nop
	.loc 1 146 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE12:
	.size	ajit_spi_flash_sector_erase, .-ajit_spi_flash_sector_erase
	.align 4
	.global ajit_spi_flash_bulk_erase
	.type	ajit_spi_flash_bulk_erase, #function
	.proc	020
ajit_spi_flash_bulk_erase:
.LFB13:
	.loc 1 149 0
	.cfi_startproc
	save	%sp, -96, %sp
.LCFI10:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	st	%i1, [%fp+72]
	stb	%g1, [%fp+68]
	.loc 1 150 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	199, %o1
	ld	[%fp+72], %o2
	call	ajit_spi_flash_generic_erase, 0
	 nop
	.loc 1 151 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE13:
	.size	ajit_spi_flash_bulk_erase, .-ajit_spi_flash_bulk_erase
	.align 4
	.global ajit_spi_flash_read
	.type	ajit_spi_flash_read, #function
	.proc	020
ajit_spi_flash_read:
.LFB14:
	.loc 1 154 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI11:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	stb	%g1, [%fp+68]
	.loc 1 156 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	3, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 159 0
	ld	[%fp+72], %g1
	srl	%g1, 16, %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g2
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 160 0
	ld	[%fp+72], %g1
	srl	%g1, 8, %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g2
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 161 0
	ld	[%fp+72], %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g2
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 164 0
	st	%g0, [%fp-4]
	b	.L23
	 nop
.L24:
.LBB4:
	.loc 1 166 0 discriminator 2
	ld	[%fp-4], %g2
	ld	[%fp+80], %g1
	add	%g1, -1, %g1
	xor	%g2, %g1, %g1
	subcc	%g0, %g1, %g0
	subx	%g0, -1, %g1
	stb	%g1, [%fp-5]
	.loc 1 167 0 discriminator 2
	ld	[%fp-4], %g1
	ld	[%fp+76], %g2
	add	%g2, %g1, %i5
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g2
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	call	ajit_spi_flash_receive_byte, 0
	 nop
	mov	%o0, %g1
	stb	%g1, [%i5]
.LBE4:
	.loc 1 164 0 discriminator 2
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L23:
	.loc 1 164 0 is_stmt 0 discriminator 1
	ld	[%fp-4], %g2
	ld	[%fp+80], %g1
	cmp	%g2, %g1
	blu	.L24
	 nop
	.loc 1 169 0 is_stmt 1
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE14:
	.size	ajit_spi_flash_read, .-ajit_spi_flash_read
	.align 4
	.global ajit_spi_flash_write
	.type	ajit_spi_flash_write, #function
	.proc	020
ajit_spi_flash_write:
.LFB15:
	.loc 1 172 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI12:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	stb	%g1, [%fp+68]
	.loc 1 174 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	6, %o1
	mov	1, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 177 0
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	2, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 180 0
	ld	[%fp+72], %g1
	srl	%g1, 16, %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g2
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 181 0
	ld	[%fp+72], %g1
	srl	%g1, 8, %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g2
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 182 0
	ld	[%fp+72], %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g2
	and	%g1, 0xff, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	mov	0, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 185 0
	st	%g0, [%fp-4]
	b	.L26
	 nop
.L27:
.LBB5:
	.loc 1 187 0 discriminator 2
	ld	[%fp-4], %g2
	ld	[%fp+80], %g1
	add	%g1, -1, %g1
	xor	%g2, %g1, %g1
	subcc	%g0, %g1, %g0
	subx	%g0, -1, %g1
	stb	%g1, [%fp-5]
	.loc 1 188 0 discriminator 2
	ld	[%fp-4], %g1
	ld	[%fp+76], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g1
	ldub	[%fp+68], %g2
	and	%g2, 0xff, %g3
	and	%g1, 0xff, %g2
	ldub	[%fp-5], %g1
	and	%g1, 0xff, %g1
	mov	%g3, %o0
	mov	%g2, %o1
	mov	%g1, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
.LBE5:
	.loc 1 185 0 discriminator 2
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L26:
	.loc 1 185 0 is_stmt 0 discriminator 1
	ld	[%fp-4], %g2
	ld	[%fp+80], %g1
	cmp	%g2, %g1
	blu	.L27
	 nop
	.loc 1 191 0 is_stmt 1
	ldub	[%fp+68], %g1
	and	%g1, 0xff, %g1
	mov	%g1, %o0
	mov	4, %o1
	mov	1, %o2
	call	ajit_spi_flash_send_byte, 0
	 nop
	.loc 1 192 0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE15:
	.size	ajit_spi_flash_write, .-ajit_spi_flash_write
.Letext0:
	.file 2 "/home/ajit4/ajit-toolchain/build/buildroot-2014.08/output/host/usr/lib/gcc/sparc-buildroot-linux-uclibc/4.7.4/include/stdint-gcc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x428
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF38
	.byte	0x1
	.uaword	.LASF39
	.uaword	.Ltext0
	.uaword	.Letext0
	.uaword	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF0
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.uaword	.LASF1
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.uaword	.LASF2
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.uaword	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.uaword	.LASF4
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF5
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF6
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
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
	.byte	0x1
	.byte	0x6
	.uaword	.LASF10
	.uleb128 0x4
	.uaword	.LASF11
	.byte	0x2
	.byte	0x2e
	.uaword	0x3d
	.uleb128 0x4
	.uaword	.LASF12
	.byte	0x2
	.byte	0x34
	.uaword	0x21
	.uleb128 0x5
	.byte	0x1
	.uaword	.LASF13
	.byte	0x1
	.byte	0xb
	.uaword	0x80
	.uaword	.LFB3
	.uaword	.LFE3
	.uaword	.LLST0
	.byte	0x1
	.uaword	0xb7
	.uleb128 0x6
	.uaword	.LASF18
	.byte	0x1
	.byte	0xd
	.uaword	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF14
	.byte	0x1
	.byte	0x1a
	.byte	0x1
	.uaword	.LFB4
	.uaword	.LFE4
	.uaword	.LLST1
	.byte	0x1
	.uaword	0x10d
	.uleb128 0x8
	.uaword	.LASF15
	.byte	0x1
	.byte	0x1a
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.uaword	.LASF16
	.byte	0x1
	.byte	0x1a
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x8
	.uaword	.LASF17
	.byte	0x1
	.byte	0x1a
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0x9
	.asciz	"cmd"
	.byte	0x1
	.byte	0x24
	.uaword	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0xa
	.byte	0x1
	.uaword	.LASF25
	.byte	0x1
	.byte	0x33
	.byte	0x1
	.uaword	0x75
	.uaword	.LFB5
	.uaword	.LFE5
	.uaword	.LLST2
	.byte	0x1
	.uaword	0x17a
	.uleb128 0x8
	.uaword	.LASF15
	.byte	0x1
	.byte	0x33
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.uaword	.LASF17
	.byte	0x1
	.byte	0x33
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x9
	.asciz	"cmd"
	.byte	0x1
	.byte	0x3b
	.uaword	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x6
	.uaword	.LASF19
	.byte	0x1
	.byte	0x52
	.uaword	0x75
	.byte	0x2
	.byte	0x91
	.sleb128 -9
	.uleb128 0xb
	.uaword	.Ldebug_ranges0+0
	.uleb128 0x6
	.uaword	.LASF18
	.byte	0x1
	.byte	0x45
	.uaword	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.byte	0
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF20
	.byte	0x1
	.byte	0x5b
	.byte	0x1
	.uaword	.LFB6
	.uaword	.LFE6
	.uaword	.LLST3
	.byte	0x1
	.uaword	0x1a4
	.uleb128 0x8
	.uaword	.LASF21
	.byte	0x1
	.byte	0x5b
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF22
	.byte	0x1
	.byte	0x60
	.byte	0x1
	.uaword	.LFB7
	.uaword	.LFE7
	.uaword	.LLST4
	.byte	0x1
	.uaword	0x1ce
	.uleb128 0x8
	.uaword	.LASF21
	.byte	0x1
	.byte	0x60
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.uaword	.LASF23
	.byte	0x1
	.byte	0x65
	.byte	0x1
	.uaword	.LFB8
	.uaword	.LFE8
	.uaword	.LLST5
	.byte	0x1
	.uaword	0x204
	.uleb128 0x8
	.uaword	.LASF24
	.byte	0x1
	.byte	0x65
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x9
	.asciz	"w"
	.byte	0x1
	.byte	0x67
	.uaword	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0xa
	.byte	0x1
	.uaword	.LASF26
	.byte	0x1
	.byte	0x6f
	.byte	0x1
	.uaword	0x80
	.uaword	.LFB9
	.uaword	.LFE9
	.uaword	.LLST6
	.byte	0x1
	.uaword	0x240
	.uleb128 0x8
	.uaword	.LASF15
	.byte	0x1
	.byte	0x6f
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x6
	.uaword	.LASF18
	.byte	0x1
	.byte	0x72
	.uaword	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF27
	.byte	0x1
	.byte	0x7b
	.byte	0x1
	.uaword	.LFB10
	.uaword	.LFE10
	.uaword	.LLST7
	.byte	0x1
	.uaword	0x288
	.uleb128 0x8
	.uaword	.LASF21
	.byte	0x1
	.byte	0x7b
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.uaword	.LASF28
	.byte	0x1
	.byte	0x7b
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x8
	.uaword	.LASF29
	.byte	0x1
	.byte	0x7b
	.uaword	0x80
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF30
	.byte	0x1
	.byte	0x8b
	.byte	0x1
	.uaword	.LFB11
	.uaword	.LFE11
	.uaword	.LLST8
	.byte	0x1
	.uaword	0x2c1
	.uleb128 0x8
	.uaword	.LASF21
	.byte	0x1
	.byte	0x8b
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.uaword	.LASF29
	.byte	0x1
	.byte	0x8b
	.uaword	0x80
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF31
	.byte	0x1
	.byte	0x8f
	.byte	0x1
	.uaword	.LFB12
	.uaword	.LFE12
	.uaword	.LLST9
	.byte	0x1
	.uaword	0x2fa
	.uleb128 0x8
	.uaword	.LASF21
	.byte	0x1
	.byte	0x8f
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.uaword	.LASF29
	.byte	0x1
	.byte	0x8f
	.uaword	0x80
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF32
	.byte	0x1
	.byte	0x94
	.byte	0x1
	.uaword	.LFB13
	.uaword	.LFE13
	.uaword	.LLST10
	.byte	0x1
	.uaword	0x333
	.uleb128 0x8
	.uaword	.LASF21
	.byte	0x1
	.byte	0x94
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.uaword	.LASF29
	.byte	0x1
	.byte	0x94
	.uaword	0x80
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.byte	0
	.uleb128 0x7
	.byte	0x1
	.uaword	.LASF33
	.byte	0x1
	.byte	0x99
	.byte	0x1
	.uaword	.LFB14
	.uaword	.LFE14
	.uaword	.LLST11
	.byte	0x1
	.uaword	0x3ae
	.uleb128 0x8
	.uaword	.LASF21
	.byte	0x1
	.byte	0x99
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.uaword	.LASF34
	.byte	0x1
	.byte	0x99
	.uaword	0x80
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x8
	.uaword	.LASF35
	.byte	0x1
	.byte	0x99
	.uaword	0x3ae
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0x8
	.uaword	.LASF36
	.byte	0x1
	.byte	0x99
	.uaword	0x80
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0x9
	.asciz	"I"
	.byte	0x1
	.byte	0xa3
	.uaword	0x28
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0xd
	.uaword	.LBB4
	.uaword	.LBE4
	.uleb128 0x6
	.uaword	.LASF37
	.byte	0x1
	.byte	0xa6
	.uaword	0x75
	.byte	0x2
	.byte	0x91
	.sleb128 -5
	.byte	0
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.uaword	0x75
	.uleb128 0xf
	.byte	0x1
	.uaword	.LASF40
	.byte	0x1
	.byte	0xab
	.byte	0x1
	.uaword	.LFB15
	.uaword	.LFE15
	.uaword	.LLST12
	.byte	0x1
	.uleb128 0x8
	.uaword	.LASF21
	.byte	0x1
	.byte	0xab
	.uaword	0x75
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x8
	.uaword	.LASF34
	.byte	0x1
	.byte	0xab
	.uaword	0x80
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x8
	.uaword	.LASF35
	.byte	0x1
	.byte	0xab
	.uaword	0x3ae
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0x8
	.uaword	.LASF36
	.byte	0x1
	.byte	0xab
	.uaword	0x80
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0x9
	.asciz	"I"
	.byte	0x1
	.byte	0xb8
	.uaword	0x28
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0xd
	.uaword	.LBB5
	.uaword	.LBE5
	.uleb128 0x6
	.uaword	.LASF37
	.byte	0x1
	.byte	0xbb
	.uaword	0x75
	.byte	0x2
	.byte	0x91
	.sleb128 -5
	.byte	0
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
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
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
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
	.uaword	.LFB3-.Ltext0
	.uaword	.LCFI0-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI0-.Ltext0
	.uaword	.LFE3-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST1:
	.uaword	.LFB4-.Ltext0
	.uaword	.LCFI1-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI1-.Ltext0
	.uaword	.LFE4-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST2:
	.uaword	.LFB5-.Ltext0
	.uaword	.LCFI2-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI2-.Ltext0
	.uaword	.LFE5-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST3:
	.uaword	.LFB6-.Ltext0
	.uaword	.LCFI3-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI3-.Ltext0
	.uaword	.LFE6-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST4:
	.uaword	.LFB7-.Ltext0
	.uaword	.LCFI4-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI4-.Ltext0
	.uaword	.LFE7-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST5:
	.uaword	.LFB8-.Ltext0
	.uaword	.LCFI5-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI5-.Ltext0
	.uaword	.LFE8-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST6:
	.uaword	.LFB9-.Ltext0
	.uaword	.LCFI6-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI6-.Ltext0
	.uaword	.LFE9-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST7:
	.uaword	.LFB10-.Ltext0
	.uaword	.LCFI7-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI7-.Ltext0
	.uaword	.LFE10-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST8:
	.uaword	.LFB11-.Ltext0
	.uaword	.LCFI8-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI8-.Ltext0
	.uaword	.LFE11-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST9:
	.uaword	.LFB12-.Ltext0
	.uaword	.LCFI9-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI9-.Ltext0
	.uaword	.LFE12-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST10:
	.uaword	.LFB13-.Ltext0
	.uaword	.LCFI10-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI10-.Ltext0
	.uaword	.LFE13-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST11:
	.uaword	.LFB14-.Ltext0
	.uaword	.LCFI11-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI11-.Ltext0
	.uaword	.LFE14-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST12:
	.uaword	.LFB15-.Ltext0
	.uaword	.LCFI12-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI12-.Ltext0
	.uaword	.LFE15-.Ltext0
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
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.uaword	.LBB2-.Ltext0
	.uaword	.LBE2-.Ltext0
	.uaword	.LBB3-.Ltext0
	.uaword	.LBE3-.Ltext0
	.uaword	0
	.uaword	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF2:
	.asciz	"long long int"
.LASF20:
	.asciz	"ajit_spi_flash_reset"
.LASF4:
	.asciz	"short unsigned int"
.LASF18:
	.asciz	"status"
.LASF32:
	.asciz	"ajit_spi_flash_bulk_erase"
.LASF6:
	.asciz	"signed char"
.LASF3:
	.asciz	"unsigned char"
.LASF22:
	.asciz	"ajit_spi_flash_memory_reset"
.LASF5:
	.asciz	"long unsigned int"
.LASF29:
	.asciz	"addr"
.LASF23:
	.asciz	"ajit_spi_set_clock_frequency"
.LASF15:
	.asciz	"dev_id"
.LASF30:
	.asciz	"ajit_spi_flash_subsector_erase"
.LASF40:
	.asciz	"ajit_spi_flash_write"
.LASF16:
	.asciz	"byte_to_send"
.LASF31:
	.asciz	"ajit_spi_flash_sector_erase"
.LASF0:
	.asciz	"unsigned int"
.LASF34:
	.asciz	"start_address"
.LASF8:
	.asciz	"long long unsigned int"
.LASF11:
	.asciz	"uint8_t"
.LASF39:
	.asciz	"/home/ajit4/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c"
.LASF14:
	.asciz	"ajit_spi_flash_send_byte"
.LASF37:
	.asciz	"desel_flag"
.LASF17:
	.asciz	"deselect_after_send"
.LASF21:
	.asciz	"device_id"
.LASF13:
	.asciz	"ajit_spi_transfer_is_in_progress"
.LASF9:
	.asciz	"sizetype"
.LASF27:
	.asciz	"ajit_spi_flash_generic_erase"
.LASF19:
	.asciz	"recv_byte"
.LASF10:
	.asciz	"char"
.LASF38:
	.asciz	"GNU C 4.7.4"
.LASF28:
	.asciz	"erase_type"
.LASF7:
	.asciz	"short int"
.LASF35:
	.asciz	"buffer"
.LASF26:
	.asciz	"ajit_spi_flash_is_busy"
.LASF36:
	.asciz	"n_bytes"
.LASF12:
	.asciz	"uint32_t"
.LASF1:
	.asciz	"long int"
.LASF33:
	.asciz	"ajit_spi_flash_read"
.LASF24:
	.asciz	"clk_divide_count"
.LASF25:
	.asciz	"ajit_spi_flash_receive_byte"
	.ident	"GCC: (Buildroot 2014.08-ga2bdb80-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
