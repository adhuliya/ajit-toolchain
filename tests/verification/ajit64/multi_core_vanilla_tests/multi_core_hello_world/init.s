!
! The test uses ASR's to distinguish between the
! cores.
!
.global main;
main:
_start:
	! enable traps, set current window=0
	set 0x10E0, %l0	
	wr %l0, %psr


	set PT_FLAG, %l6
	mov 0, %l7
	st %l7, [%l6]

	! initialize some ASR's
	wr 0x1, %asr16
	wr 0x2, %asr17
	wr 0x3, %asr18
	wr 0x4, %asr19

WIMSET:
	set 0x2, %l0		! window 1 is marked invalid...  we start at window 0
	wr %l0, 0x0, %wim	!

	! trap table.
	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr

STACKSETUP:

	! set up stack pointers.
	mov 0x0, %l2
	rd %asr29, %l1
	subcc %l1, %l2, %g0

	bnz SP1
	nop

	! for core 0
	set 0, %sp
	clr %fp

	! set up virtual -> physical map.
	! This will be executed by each core.
	! a waste but does not seem to affect
	! the correctness since we do not expect
	! to have any page faults....
	call page_table_setup 	
	nop

	set PT_FLAG, %l6
	mov 1, %l7
	st %l7, [%l6]

	ba AFTER_PTABLE_SETUP
	nop
SP1:
	mov 0x1, %l2
	subcc %l1, %l2, %g0

	bnz SP2
	nop

	! for core 1
	set -4096, %sp
	clr %fp

	ba AFTER_PTABLE_SETUP
	nop

SP2:
	mov 0x2, %l2
	subcc %l1, %l2, %g0

	bnz SP3
	nop

	! for core 2
	set -8192, %sp
	clr %fp

	ba AFTER_PTABLE_SETUP
	nop

SP3:
	mov 0x3, %l2
	subcc %l1, %l2, %g0

	bnz AFTER_PTABLE_SETUP
	nop

	! for core 3
	set -12288, %sp
	clr %fp


AFTER_PTABLE_SETUP:

	set PT_FLAG, %l6
	ld [%l6], %l7 

	mov 0x1, %i0
	subcc %i0, %l7,  %g0

	! l7 = 1 after page tables have been setup.
	bnz AFTER_PTABLE_SETUP
	nop

	call set_context_table_pointer
	nop


  	! enable mmu.
	set 0x1, %o0
	sta %o0, [%g0] 0x4    

	rd %asr29, %l1
	mov 0x0, %l2
	subcc %l1, %l2, %g0

	bnz CORE1
	nop

	call main_0
	nop

	wr 0xa, %asr16

	ba HALT
	nop

CORE1: 

	mov 0x1, %l2
	subcc %l1, %l2, %g0

	bnz  CORE2
	nop

	call main_1
	nop

	wr 0xb, %asr17

	ba HALT
	nop

CORE2:
	mov 0x2, %l2
	subcc %l1, %l2, %g0

	bnz  CORE3
	nop

	call main_2
	nop

	wr 0xc, %asr18

	ba HALT
	nop

CORE3:
	mov 0x3, %l2
	subcc %l1, %l2, %g0

	bnz  HALT
	nop

	call main_3
	nop

	wr 0xd, %asr19

HALT:

	ta 0

.align 8
      PT_FLAG: .word 0x0
