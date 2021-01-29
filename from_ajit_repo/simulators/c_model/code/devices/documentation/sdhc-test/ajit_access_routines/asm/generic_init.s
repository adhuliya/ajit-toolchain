! A generic init routine.  Your stack position may vary.

.set INIT_STACK_POINTER, 0xee00ef00
.set INIT_FRAME_POINTER, 0xee00effc
.section .text.ajitstart
.global _start;
_start:
	set INIT_STACK_POINTER, %sp
	set INIT_FRAME_POINTER, %fp

	set 0x80, %l0		! window 7 is marked invalid...  we start at window 7
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

	!
	! go to window 6 and start from there.
	!
	save %sp, -96, %sp

	call main
	nop
	
        ! When main returns, trap and go to error.
	ta 0
	nop
