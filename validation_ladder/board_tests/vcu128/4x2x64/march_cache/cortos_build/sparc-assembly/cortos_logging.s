	.file	"cortos_logging.c"
	.section	".text"
	.align 4
	.global cortos_init_logging
	.type	cortos_init_logging, #function
	.proc	020
cortos_init_logging:
	mov	1, %g2
	sethi	%hi(allocatedLocksNc), %g1
	or	%g1, %lo(allocatedLocksNc), %g1
	stb	%g2, [%g1+4]
	sethi	%hi(94208), %g2
	sethi	%hi(loggingLockAddr), %g1
	or	%g2, 4, %g2
	jmp	%o7+8
	 st	%g2, [%g1+%lo(loggingLockAddr)]
	.size	cortos_init_logging, .-cortos_init_logging
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"CoRTOS:LOG: %s: (%d,%d): %s:%d, %s() [%llu]. "
	.align 8
.LC1:
	.asciz	"\n"
	.section	".text"
	.align 4
	.global __cortos_log_printf
	.type	__cortos_log_printf, #function
	.proc	04
__cortos_log_printf:
	save	%sp, -1152, %sp
	sethi	%hi(loggingLockAddr), %l0
	st	%i5, [%fp+88]
	call	cortos_lock_acquire_buzy, 0
	 ld	[%l0+%lo(loggingLockAddr)], %o0
	call	cortos_get_clock_time, 0
	 nop
#APP
! 34 "cortos_src/cortos_logging.c" 1
	  rd %asr29, %l1
  mov %l1, %g1

! 0 "" 2
#NO_APP
	std	%o0, [%fp-1040]
	and	%g1, 0xff, %o3
	srl	%g1, 8, %o2
	ld	[%fp-1040], %g1
	st	%g1, [%sp+96]
	ld	[%fp-1036], %g1
	mov	%i0, %o1
	st	%g1, [%sp+100]
	mov	%i1, %o4
	mov	%i3, %o5
	and	%o2, 0xff, %o2
	st	%i2, [%sp+92]
	sethi	%hi(.LC0), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC0), %o0
	add	%fp, 88, %o2
	mov	%o0, %i0
	st	%o2, [%fp-1028]
	add	%fp, -1024, %i5
	mov	%i4, %o1
	call	ee_vsprintf, 0
	 mov	%i5, %o0
	ldub	[%fp-1024], %g1
	sll	%g1, 24, %o0
	cmp	%o0, 0
	be,a	.L8
	 sethi	%hi(.LC1), %o0
	sub	%i5, %i0, %i5
.L4:
	call	uart_send_char, 0
	 sra	%o0, 24, %o0
	add	%i0, 1, %i0
	ldub	[%i5+%i0], %g1
	sll	%g1, 24, %o0
	cmp	%o0, 0
	bne	.L4
	 nop
	sethi	%hi(.LC1), %o0
.L8:
	call	ee_printf, 0
	 or	%o0, %lo(.LC1), %o0
	add	%o0, %i0, %i0
	call	cortos_lock_release, 0
	 ld	[%l0+%lo(loggingLockAddr)], %o0
	jmp	%i7+8
	 restore
	.size	__cortos_log_printf, .-__cortos_log_printf
	.global loggingLockAddr
	.section	".bss"
	.align 4
	.type	loggingLockAddr, #object
	.size	loggingLockAddr, 4
loggingLockAddr:
	.skip	4
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
