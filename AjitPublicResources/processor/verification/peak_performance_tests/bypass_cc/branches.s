.global main
main:
_start:
	set 0x100, %o0
	sta %o0, [%g0] 0x4      ! set the default cacheable bit in the mmu to 1. mmu stays disabled.


	! result
	mov 0, %o1

	! 8 iterations.
	mov 8, %o0

	mov 0x1, %g1
	mov 0x2, %g2
	mov 0x3, %g3
	mov 0x4, %g4
	mov 0x5, %g5
	mov 0x6, %g6
	mov 0x7, %g7

label1:
	subcc %g1, 0x1, %g0	
	bz,a l0
	add %o1, 1, %o1
l0:
	subcc %g2, 0x2, %g0	
	bz,a l1
	add %o1, 1, %o1
l1:
	subcc %g3, 0x3, %g0	
	bz,a l2
	add %o1, 1, %o1
l2:
	subcc %g4, 0x4, %g0	
	bz,a l3
	add %o1, 1, %o1
l3:
	subcc %g5, 0x5, %g0	
	bz,a l4
	add %o1, 1, %o1
l4:
	subcc %g6, 0x6, %g0	
	bz,a l5
	add %o1, 1, %o1
l5:
	subcc %g7, 0x7, %g0	
	bz,a l6
	add %o1, 1, %o1

l6:
	subcc %o0, 1, %o0
	bnz label1
	nop
		
	ta 0
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	!====================================
	! TRAP TABLE
	!====================================
	!NOTE: the trap table has to be aligned on 2^12 = 4096 bytes
	!because wr tbr instruction copies bits 
	!31:12 of the result only into tbr register
	
