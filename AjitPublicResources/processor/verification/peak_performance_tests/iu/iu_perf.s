
.global main
main:
_start:
	set 0x100, %o0
	sta %o0, [%g0] 0x4      ! set the default cacheable bit in the mmu to 1. mmu stays disabled.


	! 8 iterations.
	mov 8, %o0

label1:
	mov 0x1, %g1
	mov 0x2, %g2
	mov 0x3, %g3
	mov 0x4, %g4
	mov 0x5, %g5
	mov 0x6, %g6
	mov 0x7, %g7

	add %g1, %g2, %g2 !g2 = 3
	add %g2, %g3, %g3 !g3 = 6
	add %g3, %g4, %g4 !g4 = 10
	add %g4, %g5, %g5 !g5 = 15
	add %g5, %g6, %g6 !g6 = 21
	add %g6, %g7, %g7 !g7 = 28

	umul %g7, %g1, %g1 !g1 = 28
	umul %g1, %g2, %g2 !g2 = 84
	umul %g2, %g3, %g3 !g3 = 504
	umul %g3, %g4, %g4 !g4 = 5040
	umul %g4, %g5, %g5 !g5 = 75600
	umul %g5, %g6, %g6 !g6 = 1587600
	umul %g6, %g7, %g7 !g7 = 44452800 = 0x2a64bc0
	

	subcc %o0, 0x1, %o0	
	bnz label1
	nop

	ta 0	

