.section .text.ajitstart
.global _start;
_start:
	! current value of window is 7


	!
	! clear all stack pointers in all windows.
	!
	!    NEW FOR CORTOS
	call clear_stack_pointers
	nop

	! give window 7 a stack..
	!    NEW FOR CORTOS
	set 0xfff00f00, %sp

	!    NEW FOR CORTOS
	set 0x1, %l0		! window 7 is marked invalid...  we start at window 7
	sll %l0, 7, %l0         !
	wr %l0, 0x0, %wim	!

	!
	! trap table.
	!
	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr

	!
	! set up virtual -> physical map.
	!
	call page_table_setup 	
	nop

	call set_context_table_pointer 	
	nop

  	! enable mmu.
	set 0x1, %o0
	sta %o0, [%g0] 0x4    

	!
	! enable traps, go to user mode.
	!    NEW FOR CORTOS
	!
	set 0x1067, %l0	
	wr %l0, %psr


	! thread specific main
	call main
	nop

	ta 0
