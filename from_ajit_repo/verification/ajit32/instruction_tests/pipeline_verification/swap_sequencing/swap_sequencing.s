! Swap followed by load from same address.


.global main
main:
_start:
	mov 0x0, %l1
	mov 0x0, %l2
	mov 0x0, %l3
	mov 0x0, %l4
	mov 0x0, %l5

loopbegin:
	set MEMBUF, %g1

	ld [%g1],   %i1
	swap [%g1], %l1
	ld [%g1],   %o1
	add %g1, 4, %g1

	ld [%g1],   %i2
	swap [%g1], %l2
	ld [%g1],   %o2
	add %g1, 4, %g1

	ld [%g1],   %i3
	swap [%g1], %l3
	ld [%g1],   %o3
	add %g1, 4, %g1

	ld [%g1],   %i4
	swap [%g1], %l4
	ld [%g1],   %o4
	add %g1, 4, %g1

	ld [%g1],   %i5
	swap [%g1], %l5
	ld [%g1],   %o5

	ta 0			! end of test
	nop
	nop
	

.align 8
.global MEMBUF
MEMBUF:
.word 0x1
.word 0x2
.word 0x3
.word 0x4
.word 0x5


