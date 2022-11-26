	.file	"ajit_mt_irc.c"
	.section	".text"
	.align 4
	.global ajit_initialize_interrupt_handlers_to_null
	.type	ajit_initialize_interrupt_handlers_to_null, #function
	.proc	020
ajit_initialize_interrupt_handlers_to_null:
	sethi	%hi(ajit_global_interrupt_handlers), %g1
	or	%g1, %lo(ajit_global_interrupt_handlers), %g1
	add	%g1, 64, %g2
	st	%g0, [%g1]
.L5:
	add	%g1, 4, %g1
	cmp	%g1, %g2
	bne,a	.L5
	 st	%g0, [%g1]
	jmp	%o7+8
	 nop
	.size	ajit_initialize_interrupt_handlers_to_null, .-ajit_initialize_interrupt_handlers_to_null
	.align 4
	.global ajit_set_interrupt_handler
	.type	ajit_set_interrupt_handler, #function
	.proc	020
ajit_set_interrupt_handler:
	cmp	%o0, 15
	bgu	.L8
	 sll	%o0, 2, %o0
	sethi	%hi(ajit_global_interrupt_handlers), %g1
	or	%g1, %lo(ajit_global_interrupt_handlers), %g1
	st	%o1, [%g1+%o0]
.L8:
	jmp	%o7+8
	 nop
	.size	ajit_set_interrupt_handler, .-ajit_set_interrupt_handler
	.align 4
	.global ajit_generic_interrupt_handler
	.type	ajit_generic_interrupt_handler, #function
	.proc	020
ajit_generic_interrupt_handler:
	save	%sp, -104, %sp
	add	%fp, -2, %o0
	call	ajit_get_core_and_thread_id, 0
	 add	%fp, -1, %o1
	ldub	[%fp-2], %g2
	add	%g2, %g2, %g2
	sethi	%hi(-53248), %i5
	ldub	[%fp-1], %g1
	add	%g1, %g2, %g1
	sll	%g1, 2, %g1
	ld	[%g1+%i5], %g2
	and	%g2, -2, %g2
	srl	%i0, 4, %i0
	and	%i0, 255, %i0
	add	%i0, -17, %g3
	cmp	%g3, 14
	bgu	.L10
	 st	%g2, [%g1+%i5]
	add	%i0, -16, %i0
	sethi	%hi(ajit_global_interrupt_handlers), %g3
	sll	%i0, 2, %i0
	or	%g3, %lo(ajit_global_interrupt_handlers), %g3
	ld	[%g3+%i0], %g3
	cmp	%g3, 0
	be	.L15
	 or	%g2, 1, %g2
	call	%g3, 0
	 nop
	ldub	[%fp-2], %g2
	add	%g2, %g2, %g2
	ldub	[%fp-1], %g1
	add	%g1, %g2, %g1
	sll	%g1, 2, %g1
	ld	[%g1+%i5], %g2
	or	%g2, 1, %g2
	st	%g2, [%g1+%i5]
	jmp	%i7+8
	 restore
.L10:
	or	%g2, 1, %g2
.L15:
	st	%g2, [%g1+%i5]
#APP
! 51 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_mt_irc.c" 1
	ta 0;
! 0 "" 2
#NO_APP
	jmp	%i7+8
	 restore
	.size	ajit_generic_interrupt_handler, .-ajit_generic_interrupt_handler
	.align 4
	.global readInterruptControlRegister
	.type	readInterruptControlRegister, #function
	.proc	016
readInterruptControlRegister:
	add	%o0, %o0, %o0
	sethi	%hi(-53248), %g1
	add	%o0, %o1, %o1
	sll	%o1, 2, %o0
	jmp	%o7+8
	 ld	[%o0+%g1], %o0
	.size	readInterruptControlRegister, .-readInterruptControlRegister
	.align 4
	.global writeInterruptControlRegister
	.type	writeInterruptControlRegister, #function
	.proc	020
writeInterruptControlRegister:
	add	%o0, %o0, %o0
	sethi	%hi(-53248), %g1
	add	%o0, %o1, %o1
	sll	%o1, 2, %o0
	jmp	%o7+8
	 st	%o2, [%o0+%g1]
	.size	writeInterruptControlRegister, .-writeInterruptControlRegister
	.align 4
	.global enableInterruptController
	.type	enableInterruptController, #function
	.proc	020
enableInterruptController:
	sethi	%hi(-53248), %g1
	add	%o0, %o0, %o0
	add	%o1, %o0, %o1
	sll	%o1, 2, %o1
	ld	[%o1+%g1], %g2
	or	%g2, 1, %g2
	jmp	%o7+8
	 st	%g2, [%o1+%g1]
	.size	enableInterruptController, .-enableInterruptController
	.align 4
	.global disableInterruptController
	.type	disableInterruptController, #function
	.proc	020
disableInterruptController:
	sethi	%hi(-53248), %g1
	add	%o0, %o0, %o0
	add	%o1, %o0, %o1
	sll	%o1, 2, %o1
	ld	[%o1+%g1], %g2
	and	%g2, -2, %g2
	jmp	%o7+8
	 st	%g2, [%o1+%g1]
	.size	disableInterruptController, .-disableInterruptController
	.align 4
	.global enableInterrupt
	.type	enableInterrupt, #function
	.proc	020
enableInterrupt:
	mov	1, %g2
	sethi	%hi(-53248), %g1
	add	%o0, %o0, %o0
	sll	%g2, %o2, %o2
	add	%o1, %o0, %o1
	sll	%o1, 2, %o1
	ld	[%o1+%g1], %g3
	or	%g3, %o2, %g2
	jmp	%o7+8
	 st	%g2, [%o1+%g1]
	.size	enableInterrupt, .-enableInterrupt
	.align 4
	.global enableAllInterrupts
	.type	enableAllInterrupts, #function
	.proc	020
enableAllInterrupts:
	sethi	%hi(-53248), %g1
	add	%o0, %o0, %o0
	sethi	%hi(64512), %g2
	add	%o1, %o0, %o1
	or	%g2, 1022, %g2
	sll	%o1, 2, %o1
	ld	[%o1+%g1], %g3
	or	%g3, %g2, %g2
	jmp	%o7+8
	 st	%g2, [%o1+%g1]
	.size	enableAllInterrupts, .-enableAllInterrupts
	.align 4
	.global enableInterruptControllerAndAllInterrupts
	.type	enableInterruptControllerAndAllInterrupts, #function
	.proc	020
enableInterruptControllerAndAllInterrupts:
	add	%o0, %o0, %o0
	sethi	%hi(64512), %g2
	add	%o0, %o1, %o1
	or	%g2, 1023, %g2
	sll	%o1, 2, %o0
	sethi	%hi(-53248), %g1
	jmp	%o7+8
	 st	%g2, [%o0+%g1]
	.size	enableInterruptControllerAndAllInterrupts, .-enableInterruptControllerAndAllInterrupts
	.align 4
	.global setInterruptMask
	.type	setInterruptMask, #function
	.proc	020
setInterruptMask:
	sethi	%hi(-53248), %g1
	add	%o0, %o0, %o0
	add	%o1, %o0, %o1
	sll	%o1, 2, %o1
	ld	[%o1+%g1], %g3
	sethi	%hi(-65536), %g2
	or	%g2, 1, %g2
	and	%g3, %g2, %g2
	sethi	%hi(64512), %g3
	or	%g3, 1022, %g3
	and	%o2, %g3, %o2
	or	%g2, %o2, %g2
	jmp	%o7+8
	 st	%g2, [%o1+%g1]
	.size	setInterruptMask, .-setInterruptMask
	.align 4
	.global disableInterrupt
	.type	disableInterrupt, #function
	.proc	020
disableInterrupt:
	mov	1, %g2
	sethi	%hi(-53248), %g1
	add	%o0, %o0, %o0
	sll	%g2, %o2, %o2
	add	%o1, %o0, %o1
	sll	%o1, 2, %o1
	ld	[%o1+%g1], %g3
	andn	%g3, %o2, %g2
	jmp	%o7+8
	 st	%g2, [%o1+%g1]
	.size	disableInterrupt, .-disableInterrupt
	.common	ajit_global_interrupt_handlers,64,4
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
