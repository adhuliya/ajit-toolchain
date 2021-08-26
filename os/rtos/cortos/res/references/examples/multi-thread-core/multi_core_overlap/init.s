!
! The test uses ASR's to distinguish between the
! cores.
!
! A stack-frame is assigned to each core by initializing
! stack-pointers in each core.
!
! Core-0 is used to set up the page tables.
!
! The context-table-pointer is updated by each
! core into its mmu.
!
! Core-i jumps to main_i (i=0,1,2,3)
!
_start:
!---------------------  Core-0,1,2,3 region --------------------------------
	! enable traps, set current window=0
	set 0x10E0, %l0	
	wr %l0, %psr



WIMSET:
	set 0x2, %l0		! window 1 is marked invalid... 
	wr %l0, 0x0, %wim	!

	! trap table.
	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr

STACKSETUP:

	! set up stack pointers.
	set 0x50520000, %l2
	rd %asr29, %l1
	subcc %l1, %l2, %g0

	bnz SP1
	nop

!---------------------  Core-0 region --------------------------------
	! for core 0
	set 0x50520000, %sp
	clr %fp

	!
	! set up virtual -> physical map.
	! This will be executed only by core-0
	!
	call page_table_setup 	
	nop

	set PT_FLAG, %l6
	mov 1, %l7
	sta %l7, [%l6] 0x20

	ba AFTER_PTABLE_SETUP
	nop
!---------------------  Core-1,2,3 region --------------------------------
SP1:
	set 0x50520100, %l2
	subcc %l1, %l2, %g0

	bnz SP2
	nop

!---------------------  Core-1 region --------------------------------
	! for core 1
	set -4096, %sp
	clr %fp

	ba AFTER_PTABLE_SETUP
	nop

!---------------------  Core-2,3 region --------------------------------
SP2:
	set 0x50520200, %l2
	subcc %l1, %l2, %g0

	bnz SP3
	nop

!---------------------  Core-2 region --------------------------------
	! for core 2
	set -8192, %sp
	clr %fp

	ba AFTER_PTABLE_SETUP
	nop

SP3:
!---------------------  Core-3 region --------------------------------
	set 0x50520300, %l2
	subcc %l1, %l2, %g0

	bnz AFTER_PTABLE_SETUP
	nop

!---------------------  Core-3 region --------------------------------
	! for core 3
	set -12288, %sp
	clr %fp


!---------------------  Core-0,1,2,3 region --------------------------------
AFTER_PTABLE_SETUP:

	set PT_FLAG, %l6
	lda [%l6] 0x20, %l7 

	mov 0x1, %i0
	subcc %i0, %l7,  %g0

	! l7 = 1 after page tables have been setup.
	!  Spin until page table setup has been completed
	!  by Core-0
	bnz AFTER_PTABLE_SETUP
	nop

	call set_context_table_pointer
	nop


  	! enable mmu.
	set 0x1, %o0
	sta %o0, [%g0] 0x4    

	rd %asr29, %l1
	set 0x50520000, %l2
	subcc %l1, %l2, %g0

	bnz CORE1
	nop

!---------------------  Core-0 region --------------------------------
	call main_0
	nop

	call print_vals
	nop

	ba HALT
	nop

!---------------------  Core-1,2,3 region --------------------------------
CORE1: 

	set 0x50520100, %l2
	subcc %l1, %l2, %g0

	bnz  CORE2
	nop

!---------------------  Core-1 region --------------------------------

	call main_1
	nop


!---------------------  Core-1,2,3 region --------------------------------
CORE2:
	set 0x50520200, %l2
	subcc %l1, %l2, %g0

	bnz  CORE3
	nop

!---------------------  Core-2 region --------------------------------
	call main_2
	nop


CORE3:
!---------------------  Core-1,2,3 region --------------------------------
	set 0x50520300, %l2
	subcc %l1, %l2, %g0

	bnz  HALT
	nop

!---------------------  Core-3 region --------------------------------
	call main_3
	nop

	wr 0xd, %asr19
	ba HALT
	nop

.align 8
      PT_FLAG: .word 0x0


HALT:

!---------------------  Core-0,1,2,3 region --------------------------------
	ta 0

