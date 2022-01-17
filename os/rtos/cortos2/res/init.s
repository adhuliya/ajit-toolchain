!
! The test uses ASR's to distinguish between the
! cores.
!
.global main;
main:
_start:
	!!!!!!!!!!!!!!! code executed across all threads !!!!!!!!!!!!!!!!111

	! enable traps, set current window=0
	set 0x10E0, %l0
	wr %l0, %psr

	! Read CORE,THREAD IDs into %l1.
	! format of asr29
	!    0x50 0x52 core-id thread-id
	rd %asr29, %l1

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
	!!!!!  setting up stacks in each thread....

	set 0x50520000, %l2
	subcc %l1, %l2, %g0

	bnz SP1
	nop

	!!!!!!!!!!!!!!!!!!!   Start: thread (0,0) section !!!!!!!!!!!!!!!!!!!!!!!!
	set 0x0, %sp
	clr %fp

	!
	! set up virtual -> physical map.
	!  In this example, the same VA -> PA translation is used by all
	!  threads.  The page table is set up by thread (0,0).
	!
	call page_table_setup
	nop

	!
	!  set PT_FLAG = 1.   This indicates that the page table has been written.
	!
	set PT_FLAG, %l6
	mov 1, %l7
	st %l7, [%l6]

	!  Thread (0,0) jumps to AFTER_PTABLE_SETUP.
	ba AFTER_PTABLE_SETUP
	nop
SP1:
	! hand off to thread (0,1)
	set 0x50520001, %l2
	subcc %l1, %l2, %g0

	bnz SP2
	nop

	!!!!!!!!!!!!!!!!!!!   Start: thread (0,1) section !!!!!!!!!!!!!!!!!!!!!!!!
	set -4096, %sp
	clr %fp

	!  Thread (0,1) jumps to wait for mmu..
	ba WAIT_UNTIL_MMU_IS_ENABLED
	nop

SP2:
	! hand off to thread (0,1)
	set 0x50520100, %l2
	subcc %l1, %l2, %g0

	bnz SP3
	nop

	!!!!!!!!!!!!!!!!!!!   Start: thread (1,0) section !!!!!!!!!!!!!!!!!!!!!!!!
	set -8192, %sp
	clr %fp

	!  Thread (1,0) jumps to AFTER_PTABLE_SETUP.
	ba AFTER_PTABLE_SETUP
	nop

SP3:
	! hand off to thread (1,1)
	set 0x50520101, %l2
	subcc %l1, %l2, %g0


	!
	! if this is not thread 1,1 we have a problem.
	!
	bnz HALT
	nop

	!!!!!!!!!!!!!!!!!!!   Start: thread (1,1) section !!!!!!!!!!!!!!!!!!!!!!!!
	set -12288, %sp
	clr %fp

	ba WAIT_UNTIL_MMU_IS_ENABLED
	nop


AFTER_PTABLE_SETUP:

	!  threads (0,0) and (0,1) come here, and check if PT_FLAG is set.
	set PT_FLAG, %l6
	ld [%l6], %l7

	mov 0x1, %i0
	subcc %i0, %l7,  %g0

	! l7 = 1 after page tables have been setup.
	bnz AFTER_PTABLE_SETUP
	nop

	call set_context_table_pointer
	nop

  	! enable mmu.. write 0x1 into mmu control register.
	set 0x1, %o0
	sta %o0, [%g0] 0x4

	! jump to run threads.
	ba RUN_THREADS
	nop

WAIT_UNTIL_MMU_IS_ENABLED:

	! threads (0,1) and (1,1) will spin here until their mmu
	! is enabled.

	! read mmu control register.
	set 0x1, %o0
	lda [%g0] 0x4, %o0
	andcc %o0, 0x1, %o0

	! spin as long as mmu_control = 0.
	bz WAIT_UNTIL_MMU_IS_ENABLED
	nop

RUN_THREADS:
	!
	! Time to run the routines.
	!

	set 0x50520000, %l2
	rd %asr29, %l1
	subcc %l1, %l2, %g0

	bnz CORE0_THREAD1
	nop

	! Thread 0,0 runs main_0
	call main_0
	nop

	wr 0xa, %asr16

	ba HALT
	nop

CORE0_THREAD1:

	set 0x50520001, %l2
	subcc %l1, %l2, %g0

	! Thread 0,1 runs main_1
	bnz  CORE1_THREAD0
	nop

	call main_1
	nop

	wr 0xb, %asr17

	ba HALT
	nop

CORE1_THREAD0:
	set 0x50520100, %l2
	subcc %l1, %l2, %g0

	! Thread 1,0 runs main_2
	bnz  CORE1_THREAD1
	nop

	call main_2
	nop

	wr 0xc, %asr18

	ba HALT
	nop

CORE1_THREAD1:
	set 0x50520101, %l2
	subcc %l1, %l2, %g0

	bnz  HALT
	nop

	! Thread 1,1 runs main_3
	call main_3
	nop

	wr 0xd, %asr19

HALT:
	! write some value into asr19 to close.
	wr 0xd, %asr15
	ta 0

.align 8
      PT_FLAG: .word 0x0
