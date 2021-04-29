
.global main
main:
_start:
	set 0x100, %o0
	sta %o0, [%g0] 0x4      ! set the default cacheable bit in the mmu to 1. mmu stays disabled.

	! Initialize PSR, enable traps.
	! set PSR with ET=1 PS=1 S=1 and EF=1 all other fields=0
	set 0x10e0, %l0
	wr %l0, %psr

	!store base of trap table in TBR register
	set	trap_table_base, %l0
	wr	%l0, 0x0, %tbr
		

	set datablock, %o0

	mov 0x1, %g1
	mov 0x2, %g2
	mov 0x3, %g3
	mov 0x4, %g4
	mov 0x5, %g5
	mov 0x6, %g6
	mov 0x7, %g7

	! 8 iterations.
	mov 8, %o1

label1:

	st %g0, [%o0]
	st %g1, [%o0 + 4]
	st %g2, [%o0 + 8]
	st %g3, [%o0 + 12]
	st %g4, [%o0 + 16]
	st %g5, [%o0 + 20]
	st %g6, [%o0 + 24]
	st %g7, [%o0 + 28]

	ld [%o0 + 4],  %g1
	ld [%o0 + 8],  %g2
	ld [%o0 + 12], %g3
	ld [%o0 + 16], %g4
	ld [%o0 + 20], %g5
	ld [%o0 + 24], %g6
	ld [%o0 + 28], %g7

	std %g0, [%o0]
	std %g2, [%o0 + 8]
	std %g4, [%o0 + 16]
	std %g6, [%o0 + 24]

	ldd [%o0],      %g0
	ldd [%o0 + 8],  %g2
	ldd [%o0 + 16], %g4
	ldd [%o0 + 24],  %g6

	ld [%o0],  %f0
	ld [%o0 + 4],  %f1
	ld [%o0 + 8],  %f2
	ld [%o0 + 12], %f3
	ld [%o0 + 16], %f4
	ld [%o0 + 20], %f5
	ld [%o0 + 24], %f6
	ld [%o0 + 28], %f7

	st %f0, [%o0]
	st %f1, [%o0 + 4]
	st %f2, [%o0 + 8]
	st %f3, [%o0 + 12]
	st %f4, [%o0 + 16]
	st %f5, [%o0 + 20]
	st %f6, [%o0 + 24]
	st %f7, [%o0 + 28]

	ldd [%o0],      %f0
	ldd [%o0 + 8],  %f2
	ldd [%o0 + 16], %f4
	ldd [%o0 + 24], %f6

	std %f0, [%o0]
	std %f2, [%o0 + 8]
	std %f4, [%o0 + 16]
	std %f6, [%o0 + 24]

	subcc %o1, 0x1, %o1	
	bnz label1
	nop

	ta 0	

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	.align 64
datablock:
	.skip  64

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	!====================================
	! TRAP TABLE
	!====================================
	!NOTE: the trap table has to be aligned on 2^12 = 4096 bytes
	!because wr tbr instruction copies bits 
	!31:12 of the result only into tbr register
	
	.align 4096

trap_table_base:
	! The trap handler for each trap does the following:
	!	- store the trap number in g1
	!	- do a restore operation so that we  
	!	  go back to the original window 
	!	- ta 0 (cause a trap in trap to go into ERROR mode)

hardware_trap_table_base:

HW_trap_0x00: mov 0x00, %g1; restore; ta 0; nop
HW_trap_0x01: mov 0x01, %g1; restore; ta 0; nop
HW_trap_0x02: mov 0x02, %g1; restore; ta 0; nop
HW_trap_0x03: mov 0x03, %g1; restore; ta 0; nop
HW_trap_0x04: mov 0x04, %g1; restore; ta 0; nop
HW_trap_0x05: mov 0x05, %g1; restore; ta 0; nop
HW_trap_0x06: mov 0x06, %g1; restore; ta 0; nop
HW_trap_0x07: mov 0x07, %g1; restore; ta 0; nop
HW_trap_0x08: inc %g2; ta 0; nop; nop      !FP exception

software_trap_table_base:
SW_trap_0x80: mov 0x80, %g1; restore; ta 0; nop
SW_trap_0x81: mov 0x81, %g1; restore; ta 0; nop
