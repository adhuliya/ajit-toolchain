.section .text.ajitstart
.global main
main:
_start:
	set 0x100, %o0
	sta %o0, [%g0] 0x4      ! set the default cacheable bit in the mmu to 1. mmu stays disabled.

	set 0xfff00000, %sp
	set 0xfff00000, %fp

	set 0x1, %l0		! window 0 is marked invalid...  we start at window 7
	wr %l0, 0x0, %wim	!

	set 0x10E7, %l0		! enable traps.
	wr %l0, %psr

	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr

	call ajit_main
	nop
