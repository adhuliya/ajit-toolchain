.global main
main:
_start:
	! stack and frame pointer placed just below IO mem. aligned to 256
	set 0xfff00000, %sp
	set 0xfff00000, %fp
	
	! mmu control register format
	!   [8]                    [7:1]               [0]
        !   default-cacheable bit, unused,		mmu-enable
	!
	set 0x100, %o0
	sta %o0, [%g0] 0x4      ! set the default cacheable bit in the mmu to 1. mmu stays disabled.

	! no arguments..
	call ajit_main
	nop

	!
	ta 0
