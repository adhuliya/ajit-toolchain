	.file	"cortos_utils.c"
	.section	".text"
	.align 4
	.global cortos_init_printing
	.type	cortos_init_printing, #function
	.proc	020
cortos_init_printing:
	mov	1, %g2
	sethi	%hi(allocatedLocksNc), %g1
	or	%g1, %lo(allocatedLocksNc), %g1
	stb	%g2, [%g1+5]
	sethi	%hi(1073844224), %g2
	sethi	%hi(printingLockAddr), %g1
	or	%g2, 5, %g2
	jmp	%o7+8
	 st	%g2, [%g1+%lo(printingLockAddr)]
	.size	cortos_init_printing, .-cortos_init_printing
	.align 4
	.global cortos_get_clock_time
	.type	cortos_get_clock_time, #function
	.proc	017
cortos_get_clock_time:
	or	%o7, %g0, %g1
	call	__ajit_get_clock_time, 0
	 or	%g1, %g0, %o7
	.size	cortos_get_clock_time, .-cortos_get_clock_time
	.align 4
	.global cortos_sleep
	.type	cortos_sleep, #function
	.proc	020
cortos_sleep:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %o0
	call	__ajit_sleep__, 0
	 nop
	restore
	jmp	%o7+8
	 nop
	.size	cortos_sleep, .-cortos_sleep
	.align 4
	.global cortos_get_thread_id
	.type	cortos_get_thread_id, #function
	.proc	02
cortos_get_thread_id:
	save	%sp, -96, %sp
#APP
! 36 "cortos_src/cortos_utils.c" 1
	  rd %asr29, %l1
  mov %l1, %g1

! 0 "" 2
#NO_APP
	srl	%g1, 7, %i0
	and	%i0, 510, %i0
	add	%i0, %g1, %g1
	sll	%g1, 24, %i0
	sra	%i0, 24, %i0
	jmp	%i7+8
	 restore
	.size	cortos_get_thread_id, .-cortos_get_thread_id
	.align 4
	.global cortos_IsNcRamAddr
	.type	cortos_IsNcRamAddr, #function
	.proc	014
cortos_IsNcRamAddr:
	jmp	%o7+8
	 mov	0, %o0
	.size	cortos_IsNcRamAddr, .-cortos_IsNcRamAddr
	.align 4
	.global cortos_printf
	.type	cortos_printf, #function
	.proc	04
cortos_printf:
	save	%sp, -1128, %sp
	st	%i4, [%fp+84]
	st	%i5, [%fp+88]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	sethi	%hi(printingLockAddr), %i4
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i4+%lo(printingLockAddr)], %o0
	add	%fp, 72, %o2
	mov	%i0, %o1
	add	%fp, -1024, %i5
	st	%o2, [%fp-1028]
	call	ee_vsprintf, 0
	 mov	%i5, %o0
	ldub	[%fp-1024], %o0
	sll	%o0, 24, %o0
	cmp	%o0, 0
	be	.L7
	 mov	0, %i0
.L8:
	call	uart_send_char, 0
	 sra	%o0, 24, %o0
	add	%i0, 1, %i0
	ldub	[%i5+%i0], %o0
	sll	%o0, 24, %o0
	cmp	%o0, 0
	bne	.L8
	 nop
.L7:
	call	cortos_lock_release, 0
	 ld	[%i4+%lo(printingLockAddr)], %o0
	jmp	%i7+8
	 restore
	.size	cortos_printf, .-cortos_printf
	.global printingLockAddr
	.section	".bss"
	.align 4
	.type	printingLockAddr, #object
	.size	printingLockAddr, 4
printingLockAddr:
	.skip	4
	.ident	"GCC: (Buildroot 2014.08-g61fd03c-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
