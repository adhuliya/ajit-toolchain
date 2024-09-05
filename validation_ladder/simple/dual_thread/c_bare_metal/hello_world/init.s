.section .text.ajitstart
.global _start;
_start:
	! stack and frame pointers at high memory.
	set 0x40020000, %fp        
	sub %fp, 64, %sp

	set 0x1, %l0		! window 0 is marked invalid.
	wr %l0, 0x0, %wim	!

	set 0x10E7, %l0		! enable traps.
	wr %l0, %psr

	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr

	call main
	nop

	ta 0
