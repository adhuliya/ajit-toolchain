.section .text.traphandlers
!
! A collection of assembly routines which have simple implementations of
! privileged instructions: 
!
! Currently implemented:
!    uint32_t ajit_sys_read_asr (uint32_t asr_id);
!
! 
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! ta 16
!  sys_call:  uint32_t ajit_sys_read_asr(uint32_t asr_id);
!    
!  provides access to ASR registers (read-only) via software trap 17
!
!  When you get here, you are in trap window T.
!  The trap occurred in window T+1.  Register o0
!  in T+1 contained the index of the ASR register.
!  Return value is kept in o0 of T+1.
!
.align 8
.global generic_read_asr
generic_read_asr:

	! go back to window T+1
	restore

	! index is in %o0
	subcc %o0, 31, %g0
	bz   read_31
	nop

	subcc %o0, 30, %g0
	bz   read_30
	nop

	subcc %o0, 29, %g0
	bz   read_29
	nop

	subcc %o0, 28, %g0
	bz   read_28
	nop

	subcc %o0, 27, %g0
	bz   read_27
	nop

	subcc %o0, 26, %g0
	bz   read_26
	nop

	subcc %o0, 25, %g0
	bz   read_25
	nop

	subcc %o0, 24, %g0
	bz   read_24
	nop

	subcc %o0, 23, %g0
	bz   read_23
	nop

	subcc %o0, 22, %g0
	bz   read_22
	nop

	subcc %o0, 21, %g0
	bz   read_21
	nop

	subcc %o0, 20, %g0
	bz   read_20
	nop

	subcc %o0, 19, %g0
	bz   read_19
	nop

	subcc %o0, 18, %g0
	bz   read_18
	nop

	subcc %o0, 17, %g0
	bz   read_17
	nop

	subcc %o0, 16, %g0
	bz   read_16
	nop

	subcc %o0, 15, %g0
	bz   read_15
	nop

	subcc %o0, 14, %g0
	bz   read_14
	nop

	subcc %o0, 13, %g0
	bz   read_13
	nop

	subcc %o0, 12, %g0
	bz   read_12
	nop

	subcc %o0, 11, %g0
	bz   read_11
	nop

	subcc %o0, 10, %g0
	bz   read_10
	nop

	subcc %o0, 9, %g0
	bz   read_9
	nop

	subcc %o0, 8, %g0
	bz   read_8
	nop

	subcc %o0, 7, %g0
	bz   read_7
	nop

	subcc %o0, 6, %g0
	bz   read_6
	nop

	subcc %o0, 5, %g0
	bz   read_5
	nop

	subcc %o0, 4, %g0
	bz   read_4
	nop

	subcc %o0, 3, %g0
	bz   read_3
	nop

	subcc %o0, 2, %g0
	bz   read_2
	nop

	subcc %o0, 1, %g0
	bz   read_1
	nop

	subcc %o0, 0, %g0
	bz   read_0
	nop

	mov %g0, %o0
	ba  ret_block
	nop

read_31: rd %asr31, %o0; ba ret_block; nop;
read_30: rd %asr30, %o0; ba ret_block; nop;
read_29: rd %asr29, %o0; ba ret_block; nop;
read_28: rd %asr28, %o0; ba ret_block; nop;
read_27: rd %asr27, %o0; ba ret_block; nop;
read_26: rd %asr26, %o0; ba ret_block; nop;
read_25: rd %asr25, %o0; ba ret_block; nop;
read_24: rd %asr24, %o0; ba ret_block; nop;
read_23: rd %asr23, %o0; ba ret_block; nop;
read_22: rd %asr22, %o0; ba ret_block; nop;
read_21: rd %asr21, %o0; ba ret_block; nop;
read_20: rd %asr20, %o0; ba ret_block; nop;
read_19: rd %asr19, %o0; ba ret_block; nop;
read_18: rd %asr18, %o0; ba ret_block; nop;
read_17: rd %asr17, %o0; ba ret_block; nop;
read_16: rd %asr16, %o0; ba ret_block; nop;
read_15: rd %asr15, %o0; ba ret_block; nop;
read_14: rd %asr14, %o0; ba ret_block; nop;
read_13: rd %asr13, %o0; ba ret_block; nop;
read_12: rd %asr12, %o0; ba ret_block; nop;
read_11: rd %asr11, %o0; ba ret_block; nop;
read_10: rd %asr10, %o0; ba ret_block; nop;
read_9: rd %asr9, %o0; ba ret_block; nop;
read_8: rd %asr8, %o0; ba ret_block; nop;
read_7: rd %asr7, %o0; ba ret_block; nop;
read_6: rd %asr6, %o0; ba ret_block; nop;
read_5: rd %asr5, %o0; ba ret_block; nop;
read_4: rd %asr4, %o0; ba ret_block; nop;
read_3: rd %asr3, %o0; ba ret_block; nop;
read_2: rd %asr2, %o0; ba ret_block; nop;
read_1: rd %asr1, %o0; ba ret_block; nop;
read_0: rd %asr0, %o0; ba ret_block; nop;


ret_block:
	! get back to window T.
	save

   	!   go home.. to the next instruction.
   	jmpl %r18, %r0
   	rett %r18 + 4

	nop

.align 8
.global ajit_sys_read_asr

! single argument, in register o0
! result will be placed in o0
ajit_sys_read_asr:
	! in window W of caller...  this is a leaf routine.
	ta 16
	! trap handler works in window T = W - 1.
	! and puts the result in register %o0 of window W.
	nop
	! return from leaf.. no restore.
	retl
	nop

!  finished sys_call:  uint32_t ajit_sys_read_asr(uint32_t asr_id);


.align 8
.global ajit_sys_go_to_supervisor_mode
! register o0 contains enable-traps flag.
ajit_sys_go_to_supervisor_mode:
	!
	ta 17
	nop
	
	retl 
	nop

.align 8
.global generic_sys_go_to_supervisor
! i0 contains  enable-traps flag.
generic_sys_go_to_supervisor:

	mov %psr, %l5

	! enable traps
	sll %i0, 5, %i0
	or  %i0, 0x80, %i0
	or  %l5, %i0, %l5
	mov %l5, %psr

	! jump to the next instruction
	! and continue.
	!
	! Note: no return from trap !
	!
	jmp %l2
	restore

	
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
