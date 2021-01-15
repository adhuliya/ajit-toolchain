! loop prediction.

.global main
main:
_start:
	
	! initialize register values.. these will
	! be overwritten in the delay slots below.
	mov 0x0f, %g1
	mov 0x1, %g2
	mov 0x0, %g3

loopbegin:
	add %g2, %g3, %g3 ! g3 should reach 0x10.
	bne,a loopbegin
	subcc %g1,%g2, %g1

loopexit:
	ta 0 ! end of test

