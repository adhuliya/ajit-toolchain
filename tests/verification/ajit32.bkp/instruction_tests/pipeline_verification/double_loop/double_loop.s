! loop prediction.

.global main
main:
_start:
	
	! initialize register values.. these will
	! be overwritten in the delay slots below.
	mov 0xf, %g1
	mov 0x4, %g5
	mov 0x1, %g2
	mov 0x0, %g3
	mov 0x0, %g4
	

loopbegin:
	add %g2, %g3, %g3 ! g3 should reach 0xe1.
	subcc %g0, %g0, %g0 
	bz loopcontinue1
	nop
	nop
loopcontinue1:
	subcc %g1,%g2, %g1
	bne loopbegin     ! should loop 15 times.
	nop
	add %g2, %g4, %g4 ! g4 should reach 0xe.
	subcc %g0, %g0, %g0 
	bz loopcontinue2
	nop
	nop
loopcontinue2:
	subcc %g5, %g2, %g5
	bne,a loopbegin
	mov 0xf, %g1	  ! annulled when exiting loop.
	

loopexit:
	ta 0 ! end of test

