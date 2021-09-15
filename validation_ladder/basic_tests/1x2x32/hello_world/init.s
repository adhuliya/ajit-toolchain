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
	set 0xfff02f00, %sp
	set 0xfff02f00, %fp

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

	! Thread (0,0) enables the serial device
	call enable_serial
	nop

	! clear the mutex.. physically located at 0x4000d000
	!	This is to be marked non-cacheable...
	set 0x4000d000, %l0
	st %g0, [%l0]

	!  Thread (0,0) jumps to AFTER_PTABLE_SETUP.
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
	set 0xfff01f00, %sp
	set 0xfff01f00, %fp

	!  Thread (0,1) jumps to wait for mmu..
	ba WAIT_UNTIL_MMU_IS_ENABLED
	nop


AFTER_PTABLE_SETUP:


	!  thread (0,0) comes here and checks if PT_FLAG is set.
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

	! threads (0,1) will spin here until its mmu
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
	call main_00
	nop

	wr 0xa, %asr16

	ba HALT
	nop

CORE0_THREAD1: 

	set 0x50520001, %l2
	subcc %l1, %l2, %g0

	bnz  HALT
	nop

	call main_01
	nop

	wr 0xb, %asr17

	ba HALT
	nop

HALT:
	ta 0

.align 8
      PT_FLAG: .word 0x0
