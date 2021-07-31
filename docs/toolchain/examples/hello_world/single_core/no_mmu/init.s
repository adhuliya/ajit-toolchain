.section .text.ajitstart
.global _start;
_start:
	set 0xffff2ffc, %sp
	set 0xffff2ffc, %fp

	! after reset is deasserted, we will be in window 7.  
	! we mark window 0 as invalid (for use by the trap handler).
	set 0x1, %l0		
	wr %l0, 0x0, %wim

	! trap table: by default, we provide window overflow
	! and underflow trap handlers.
	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr

	! enable traps.
	set 0x10E7, %l0	
	wr %l0, %psr

  	! mmu will stay disabled, but we set the default cacheable bit
	! in the mmu control register in order to mark every memory
	! access as potentially cacheable.
	set 0x100, %o0
	sta %o0, [%g0] 0x4      

	! all set up.  call main
	call main
	nop

	! on return from main, trap.. this will halt the
	! processor because the trap handler also traps.
	ta 0
