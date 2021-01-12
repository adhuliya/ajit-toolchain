.global main
main:
_start:
	mov %g0, %sp
	set 0x100, %o0
	sta %o0, [%g0] 0x4      ! set the default cacheable bit in the mmu to 1. mmu stays disabled.
	call ajit_main
	nop
