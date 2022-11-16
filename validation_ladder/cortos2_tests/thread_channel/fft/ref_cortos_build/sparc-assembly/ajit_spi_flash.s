	.file	"ajit_spi_flash.c"
	.section	".text"
	.align 4
	.global ajit_spi_transfer_is_in_progress
	.type	ajit_spi_transfer_is_in_progress, #function
	.proc	016
ajit_spi_transfer_is_in_progress:
	sethi	%hi(-53248), %g1
	or	%g1, 776, %g1
	ld	[%g1], %o0
	jmp	%o7+8
	 and	%o0, 1, %o0
	.size	ajit_spi_transfer_is_in_progress, .-ajit_spi_transfer_is_in_progress
	.align 4
	.global ajit_spi_flash_send_byte
	.type	ajit_spi_flash_send_byte, #function
	.proc	020
ajit_spi_flash_send_byte:
	save	%sp, -96, %sp
	sethi	%hi(-53248), %g1
	or	%g1, 776, %g2
	or	%g1, 768, %g1
	st	%i1, [%g1]
	and	%i0, 7, %i0
	and	%i2, 1, %i2
	sll	%i0, 3, %g3
	add	%i2, %i2, %i2
	or	%g3, 1, %g3
	mov	%g2, %i5
	or	%g3, %i2, %i2
	st	%i2, [%g2]
.L3:
	call	__ajit_sleep__, 0
	 mov	64, %o0
	ld	[%i5], %g1
	andcc	%g1, 1, %g0
	bne	.L3
	 nop
	jmp	%i7+8
	 restore
	.size	ajit_spi_flash_send_byte, .-ajit_spi_flash_send_byte
	.align 4
	.global ajit_spi_flash_receive_byte
	.type	ajit_spi_flash_receive_byte, #function
	.proc	014
ajit_spi_flash_receive_byte:
	save	%sp, -96, %sp
	sethi	%hi(-53248), %g1
	or	%g1, 776, %g2
	or	%g1, 768, %g1
	st	%g0, [%g1]
	and	%i0, 7, %i0
	and	%i1, 1, %i1
	sll	%i0, 3, %g3
	add	%i1, %i1, %i1
	or	%g3, 1, %g3
	mov	%g2, %i5
	or	%g3, %i1, %g3
	st	%g3, [%g2]
.L7:
	call	__ajit_sleep__, 0
	 mov	64, %o0
	ld	[%i5], %g1
	andcc	%g1, 1, %g0
	bne	.L7
	 sethi	%hi(-53248), %g1
	or	%g1, 768, %g1
	ldub	[%g1+3], %i0
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
	jmp	%o7+8
	 st	%o0, [%g1]
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
	be	.L23
	 mov	0, %i5
.L21:
	xor	%i4, %i1, %g1
	subcc	%g0, %g1, %g0
	mov	%i0, %o0
	call	ajit_spi_flash_receive_byte, 0
	 subx	%g0, -1, %o1
	stb	%o0, [%i2+%i4]
	add	%i5, 1, %i5
	cmp	%i5, %i3
	bne	.L21
	 mov	%i5, %i4
.L23:
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
	be	.L27
	 mov	0, %i5
.L28:
	xor	%g1, %i4, %g2
	subcc	%g0, %g2, %g0
	ldub	[%i2+%g1], %o1
	subx	%g0, -1, %o2
	call	ajit_spi_flash_send_byte, 0
	 mov	%i0, %o0
	add	%i5, 1, %i5
	cmp	%i5, %i3
	bne	.L28
	 mov	%i5, %g1
.L27:
	mov	4, %i1
	call	ajit_spi_flash_send_byte, 0
	 restore %g0, 1, %o2
	.size	ajit_spi_flash_write, .-ajit_spi_flash_write
	.ident	"GCC: (Buildroot 2014.08-g61fd03c-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
