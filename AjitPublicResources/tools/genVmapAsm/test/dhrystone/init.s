.global _start
_start:
	mov %g0, %sp
	call page_table_setup
	nop
	set 0x1, %o0
	sta %o0, [%g0] 0x4      ! enable mmu.
	call ajit_main
	nop
