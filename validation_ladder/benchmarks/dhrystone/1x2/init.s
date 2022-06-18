.section .text.ajitstart
!
! The test uses ASR's to distinguish between the
!
.global _start;
_start:

	!!!!!!!!!!!!!!! code executed across all threads !!!!!!!!!!!!!!!!111
	! enable traps, set current window=0
	set 0x10E0, %l0	
	wr %l0, %psr

	! Read CORE,THREAD IDs into %l1.
	! format of asr29
	!    0x50 0x52 core-id thread-id
	rd %asr29, %l1

WIMSET:
	set 0x1, %l0		! window 0 is marked invalid...  we start at window 0
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
	set 0x40062f00, %sp
	set 0x40062f00, %fp

	! Thread (0,0) enables the serial device
	call enable_serial
	nop

	ba AFTER_PTABLE_SETUP
	nop
SP1:
	! All threads except (0,0) reach here..

	! hand off to thread (0,1) 
	set 0x50520001, %l2
	subcc %l1, %l2, %g0

	bnz HALT
	nop

	!!!!!!!!!!!!!!!!!!!   Start: thread (0,1) section !!!!!!!!!!!!!!!!!!!!!!!!
	set 0x40082f00, %sp
	set 0x40082f00, %fp

	!  Thread (0,1) jumps to wait for mmu..
	ba WAIT_UNTIL_MMU_IS_ENABLED
	nop


AFTER_PTABLE_SETUP:

  	! enable mmu.. write 0x100 into mmu control register.
	set 0x100, %o0
	sta %o0, [%g0] 0x4    

	! jump to run threads.
	ba RUN_THREADS
	nop

WAIT_UNTIL_MMU_IS_ENABLED:

	! threads (0,1) will spin here until its mmu
	! is enabled.

	! read mmu control register.
	set 0x1, %o0
	lda [%g0] 0x4, %o0 
	andcc %o0, 0x100, %o0

	! spin as long as mmu_control = 0.
	bz WAIT_UNTIL_MMU_IS_ENABLED
	nop

RUN_THREADS:
	! clear mutex variable
	set 0x40070000, %l2
	mov 0x0, %l2

	!
	! Time to run the routines.
	!

	set 0x50520000, %l2
	rd %asr29, %l1
	subcc %l1, %l2, %g0

	bnz CORE0_THREAD1
	nop

	! Thread 0,0 runs main_0
	call 0x40020000
	nop

	ba HALT
	nop

CORE0_THREAD1: 

	set 0x50520001, %l2
	subcc %l1, %l2, %g0

	bnz  HALT
	nop

	call 0x40040000
	nop

	ba HALT
	nop

HALT:
	ta 0

