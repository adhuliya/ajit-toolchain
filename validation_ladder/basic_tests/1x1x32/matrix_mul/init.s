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
	set 0xfff02f00, %sp
	set 0xfff02f00, %fp

	!
	! set up virtual -> physical map.
	!  In this example, the same VA -> PA translation is used by all 
	!  threads.  The page table is set up by thread (0,0).
	!
	call page_table_setup 	
	nop

	call set_context_table_pointer
	nop
	
  	! enable mmu.. write 0x1 into mmu control register.
	set 0x1, %o0
	sta %o0, [%g0] 0x4    

	call enable_serial
	nop

	call main
	nop

HALT:
	ta 0
