.section .text.ajitstart
.global _start;
_start:
	set 0xfff00f00, %sp
	set 0xfff00ff0, %fp

	set 0x1, %l0		! window 0 is marked invalid...  we start at window 7
	wr %l0, 0x0, %wim	!

	! trap table.
	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr

	! set up virtual -> physical map.
	call page_table_setup 	
	nop

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
