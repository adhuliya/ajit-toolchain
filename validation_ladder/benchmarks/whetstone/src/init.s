.section .text.ajitstart
.global _start;
_start:
	! stack..
	set 0x40080000, %sp
        set 0x40080000, %fp

	set 0x1, %l0		! window 1 is marked invalid...  we start at window 7
	wr %l0, 0x0, %wim	!

	! trap table.
	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr

	! enable traps.
	set 0x10E7, %l0	
	wr %l0, %psr

  	! set cacheable bit in mmu
	set 0x100, %o0
	sta %o0, [%g0] 0x4    

	call main
	nop

	ta 0
