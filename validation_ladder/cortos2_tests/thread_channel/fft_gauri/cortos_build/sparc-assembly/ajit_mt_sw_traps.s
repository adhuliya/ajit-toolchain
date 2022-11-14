	.file	"ajit_mt_sw_traps.c"
	.section	".text"
	.align 4
	.global ajit_initialize_sw_trap_handlers_to_null
	.type	ajit_initialize_sw_trap_handlers_to_null, #function
	.proc	020
ajit_initialize_sw_trap_handlers_to_null:
	sethi	%hi(ajit_global_sw_trap_handlers), %g1
	or	%g1, %lo(ajit_global_sw_trap_handlers), %g1
	add	%g1, 64, %g2
	st	%g0, [%g1]
.L5:
	add	%g1, 4, %g1
	cmp	%g1, %g2
	bne,a	.L5
	 st	%g0, [%g1]
	jmp	%o7+8
	 nop
	.size	ajit_initialize_sw_trap_handlers_to_null, .-ajit_initialize_sw_trap_handlers_to_null
	.align 4
	.global ajit_set_sw_trap_handler
	.type	ajit_set_sw_trap_handler, #function
	.proc	020
ajit_set_sw_trap_handler:
	cmp	%o0, 15
	bgu	.L8
	 sll	%o0, 2, %o0
	sethi	%hi(ajit_global_sw_trap_handlers), %g1
	or	%g1, %lo(ajit_global_sw_trap_handlers), %g1
	st	%o1, [%g1+%o0]
.L8:
	jmp	%o7+8
	 nop
	.size	ajit_set_sw_trap_handler, .-ajit_set_sw_trap_handler
	.align 4
	.global ajit_generic_sw_trap_handler
	.type	ajit_generic_sw_trap_handler, #function
	.proc	020
ajit_generic_sw_trap_handler:
	save	%sp, -96, %sp
	srl	%i0, 4, %i0
	and	%i0, 255, %g1
	add	%g1, -128, %g1
	cmp	%g1, 15
	bgu	.L10
	 sll	%g1, 2, %g1
	sethi	%hi(ajit_global_sw_trap_handlers), %g2
	or	%g2, %lo(ajit_global_sw_trap_handlers), %g2
	ld	[%g2+%g1], %g1
	cmp	%g1, 0
	be	.L10
	 mov	%i1, %o0
	mov	%i2, %o1
	call	%g1, 0
	 mov	%i3, %o2
	jmp	%i7+8
	 restore
.L10:
#APP
! 45 "/home/ajit/ajit-toolchain/AjitPublicResources/tools/ajit_access_routines_mt/src/ajit_mt_sw_traps.c" 1
	ta 0;
! 0 "" 2
#NO_APP
	jmp	%i7+8
	 restore
	.size	ajit_generic_sw_trap_handler, .-ajit_generic_sw_trap_handler
	.common	ajit_global_sw_trap_handlers,64,4
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
