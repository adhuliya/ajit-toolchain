.section .text.ajitstart
.global _start;
_start:
	call clear_stack_pointers

	! set the stack in window 7
	set -256, %sp

	set 0x1, %l0		!  we start at window 7, mark it invalid
	sll %l0, 7, %l0
	wr %l0, 0x0, %wim	

	! trap table.
	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr

	! set up virtual -> physical map.
	call page_table_setup 	
	nop

	! setup context table pointer
	call set_context_table_pointer
	nop

	! enable traps.
	set 0x10E7, %l0	
	wr %l0, %psr

  	! enable mmu.
	set 0x1, %o0
	sta %o0, [%g0] 0x4    

	call main
	nop

	ta 0
