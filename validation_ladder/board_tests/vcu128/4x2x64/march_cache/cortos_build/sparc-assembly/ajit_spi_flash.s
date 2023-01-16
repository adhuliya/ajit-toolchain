	.file	"ajit_spi_flash.c"
	.section	".text"
	.align 4
	.global ajit_spi_transfer_is_in_progress
	.type	ajit_spi_transfer_is_in_progress, #function
	.proc	016
ajit_spi_transfer_is_in_progress:
	sethi	%hi(-53248), %o0
	or	%o0, 776, %o0
#APP
! 17 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	lda [%o0] 32, %o0
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 and	%o0, 1, %o0
	.size	ajit_spi_transfer_is_in_progress, .-ajit_spi_transfer_is_in_progress
	.align 4
	.global ajit_spi_flash_send_byte
	.type	ajit_spi_flash_send_byte, #function
	.proc	020
ajit_spi_flash_send_byte:
	save	%sp, -96, %sp
	sethi	%hi(-53248), %i5
	or	%i5, 768, %g1
#APP
! 32 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %i1, [%g1] 32
	
! 0 "" 2
#NO_APP
	and	%i0, 7, %i0
	and	%i2, 1, %i2
	sll	%i0, 3, %i0
	add	%i2, %i2, %i2
	or	%i0, 1, %i0
	or	%i5, 776, %i5
	or	%i0, %i2, %i2
#APP
! 40 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %i2, [%i5] 32
	
! 0 "" 2
! 17 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	lda [%i5] 32, %g1
	
! 0 "" 2
#NO_APP
	andcc	%g1, 1, %g0
	be	.L8
	 nop
.L5:
	call	__ajit_sleep__, 0
	 mov	64, %o0
#APP
! 17 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	lda [%i5] 32, %g1
	
! 0 "" 2
#NO_APP
	andcc	%g1, 1, %g0
	bne	.L5
	 nop
.L8:
	jmp	%i7+8
	 restore
	.size	ajit_spi_flash_send_byte, .-ajit_spi_flash_send_byte
	.align 4
	.global ajit_spi_flash_receive_byte
	.type	ajit_spi_flash_receive_byte, #function
	.proc	014
ajit_spi_flash_receive_byte:
	save	%sp, -96, %sp
	sethi	%hi(-53248), %i5
	mov	0, %g1
	or	%i5, 768, %g2
#APP
! 56 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %g1, [%g2] 32
	
! 0 "" 2
#NO_APP
	and	%i0, 7, %i0
	and	%i1, 1, %i1
	sll	%i0, 3, %i0
	add	%i1, %i1, %i1
	or	%i0, 1, %i0
	or	%i5, 776, %i5
	or	%i0, %i1, %i1
#APP
! 64 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %i1, [%i5] 32
	
! 0 "" 2
! 73 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %g1, [%i5] 32
	
! 0 "" 2
#NO_APP
	cmp	%g1, 0
	be	.L10
	 nop
.L12:
	call	__ajit_sleep__, 0
	 mov	64, %o0
	mov	0, %g1
#APP
! 73 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %g1, [%i5] 32
	
! 0 "" 2
#NO_APP
	b,a	.L12
.L10:
#APP
! 86 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	lda [%g2] 32, %i0
	
! 0 "" 2
#NO_APP
	and	%i0, 0xff, %i0
	jmp	%i7+8
	 restore
	.size	ajit_spi_flash_receive_byte, .-ajit_spi_flash_receive_byte
	.align 4
	.global ajit_spi_flash_reset
	.type	ajit_spi_flash_reset, #function
	.proc	020
ajit_spi_flash_reset:
	mov	102, %o1
	mov	1, %o2
	or	%o7, %g0, %g1
	call	ajit_spi_flash_send_byte, 0
	 or	%g1, %g0, %o7
	.size	ajit_spi_flash_reset, .-ajit_spi_flash_reset
	.align 4
	.global ajit_spi_flash_memory_reset
	.type	ajit_spi_flash_memory_reset, #function
	.proc	020
ajit_spi_flash_memory_reset:
	mov	153, %o1
	mov	1, %o2
	or	%o7, %g0, %g1
	call	ajit_spi_flash_send_byte, 0
	 or	%g1, %g0, %o7
	.size	ajit_spi_flash_memory_reset, .-ajit_spi_flash_memory_reset
	.align 4
	.global ajit_spi_set_clock_frequency
	.type	ajit_spi_set_clock_frequency, #function
	.proc	020
ajit_spi_set_clock_frequency:
	and	%o0, 15, %o0
	sethi	%hi(-53248), %g1
	or	%o0, 16, %o0
	or	%g1, 780, %g1
#APP
! 107 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_spi_flash.c" 1
	sta %o0, [%g1] 32
	
! 0 "" 2
#NO_APP
	jmp	%o7+8
	 nop
	.size	ajit_spi_set_clock_frequency, .-ajit_spi_set_clock_frequency
	.align 4
	.global ajit_spi_flash_is_busy
	.type	ajit_spi_flash_is_busy, #function
	.proc	016
ajit_spi_flash_is_busy:
	save	%sp, -96, %sp
	mov	0, %o2
	mov	%i0, %o0
	call	ajit_spi_flash_send_byte, 0
	 mov	5, %o1
	mov	%i0, %o0
	call	ajit_spi_flash_receive_byte, 0
	 mov	1, %o1
	and	%o0, 1, %i0
	jmp	%i7+8
	 restore
	.size	ajit_spi_flash_is_busy, .-ajit_spi_flash_is_busy
	.align 4
	.global ajit_spi_flash_generic_erase
	.type	ajit_spi_flash_generic_erase, #function
	.proc	020
ajit_spi_flash_generic_erase:
	save	%sp, -96, %sp
	mov	1, %o2
	mov	%i0, %o0
	call	ajit_spi_flash_send_byte, 0
	 mov	6, %o1
	mov	%i1, %o1
	mov	%i0, %o0
	call	ajit_spi_flash_send_byte, 0
	 mov	0, %o2
	mov	%i0, %o0
	mov	0, %o2
	srl	%i2, 16, %o1
	call	ajit_spi_flash_send_byte, 0
	 and	%o1, 0xff, %o1
	mov	0, %o2
	srl	%i2, 8, %o1
	mov	%i0, %o0
	call	ajit_spi_flash_send_byte, 0
	 and	%o1, 0xff, %o1
	and	%i2, 0xff, %o1
	mov	%i0, %o0
	mov	1, %o2
	call	ajit_spi_flash_send_byte, 0
	 mov	4, %i1
	call	ajit_spi_flash_send_byte, 0
	 restore %g0, 1, %o2
	.size	ajit_spi_flash_generic_erase, .-ajit_spi_flash_generic_erase
	.align 4
	.global ajit_spi_flash_subsector_erase
	.type	ajit_spi_flash_subsector_erase, #function
	.proc	020
ajit_spi_flash_subsector_erase:
	mov	%o1, %o2
	mov	32, %o1
	or	%o7, %g0, %g1
	call	ajit_spi_flash_generic_erase, 0
	 or	%g1, %g0, %o7
	.size	ajit_spi_flash_subsector_erase, .-ajit_spi_flash_subsector_erase
	.align 4
	.global ajit_spi_flash_sector_erase
	.type	ajit_spi_flash_sector_erase, #function
	.proc	020
ajit_spi_flash_sector_erase:
	mov	%o1, %o2
	mov	216, %o1
	or	%o7, %g0, %g1
	call	ajit_spi_flash_generic_erase, 0
	 or	%g1, %g0, %o7
	.size	ajit_spi_flash_sector_erase, .-ajit_spi_flash_sector_erase
	.align 4
	.global ajit_spi_flash_bulk_erase
	.type	ajit_spi_flash_bulk_erase, #function
	.proc	020
ajit_spi_flash_bulk_erase:
	mov	%o1, %o2
	mov	199, %o1
	or	%o7, %g0, %g1
	call	ajit_spi_flash_generic_erase, 0
	 or	%g1, %g0, %o7
	.size	ajit_spi_flash_bulk_erase, .-ajit_spi_flash_bulk_erase
	.align 4
	.global ajit_spi_flash_read
	.type	ajit_spi_flash_read, #function
	.proc	020
ajit_spi_flash_read:
	save	%sp, -96, %sp
	mov	3, %o1
	mov	%i0, %o0
	call	ajit_spi_flash_send_byte, 0
	 mov	0, %o2
	mov	%i0, %o0
	mov	0, %o2
	srl	%i1, 16, %o1
	call	ajit_spi_flash_send_byte, 0
	 and	%o1, 0xff, %o1
	mov	0, %o2
	srl	%i1, 8, %o1
	mov	%i0, %o0
	call	ajit_spi_flash_send_byte, 0
	 and	%o1, 0xff, %o1
	and	%i1, 0xff, %o1
	mov	%i0, %o0
	call	ajit_spi_flash_send_byte, 0
	 mov	0, %o2
	add	%i3, -1, %i1
	mov	0, %i4
	cmp	%i3, 0
	be	.L27
	 mov	0, %i5
.L25:
	xor	%i4, %i1, %g1
	subcc	%g0, %g1, %g0
	mov	%i0, %o0
	call	ajit_spi_flash_receive_byte, 0
	 subx	%g0, -1, %o1
	stb	%o0, [%i2+%i4]
	add	%i5, 1, %i5
	cmp	%i5, %i3
	bne	.L25
	 mov	%i5, %i4
.L27:
	jmp	%i7+8
	 restore
	.size	ajit_spi_flash_read, .-ajit_spi_flash_read
	.align 4
	.global ajit_spi_flash_write
	.type	ajit_spi_flash_write, #function
	.proc	020
ajit_spi_flash_write:
	save	%sp, -96, %sp
	mov	6, %o1
	mov	1, %o2
	call	ajit_spi_flash_send_byte, 0
	 mov	%i0, %o0
	mov	%i0, %o0
	mov	2, %o1
	call	ajit_spi_flash_send_byte, 0
	 mov	0, %o2
	mov	%i0, %o0
	mov	0, %o2
	srl	%i1, 16, %o1
	call	ajit_spi_flash_send_byte, 0
	 and	%o1, 0xff, %o1
	mov	0, %o2
	mov	%i0, %o0
	srl	%i1, 8, %o1
	call	ajit_spi_flash_send_byte, 0
	 and	%o1, 0xff, %o1
	mov	%i0, %o0
	and	%i1, 0xff, %o1
	call	ajit_spi_flash_send_byte, 0
	 mov	0, %o2
	add	%i3, -1, %i4
	mov	0, %g1
	cmp	%i3, 0
	be	.L31
	 mov	0, %i5
.L32:
	xor	%g1, %i4, %g2
	subcc	%g0, %g2, %g0
	ldub	[%i2+%g1], %o1
	subx	%g0, -1, %o2
	call	ajit_spi_flash_send_byte, 0
	 mov	%i0, %o0
	add	%i5, 1, %i5
	cmp	%i5, %i3
	bne	.L32
	 mov	%i5, %g1
.L31:
	mov	4, %i1
	call	ajit_spi_flash_send_byte, 0
	 restore %g0, 1, %o2
	.size	ajit_spi_flash_write, .-ajit_spi_flash_write
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
