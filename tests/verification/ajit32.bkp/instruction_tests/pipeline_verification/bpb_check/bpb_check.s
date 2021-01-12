! loop prediction.
! See if 8 slots in bpb_8 are working correctly.
!

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

	ba label1
	nop
        nop

label1:
	ba label2
	nop
	nop

label2:
	ba label3
	nop
        nop

label3:
	ba label4
	nop
        nop

label4:
	ba label5
	nop
        nop

label5:
	ba label6
	nop
        nop

label6:
	ba label7
	nop
        nop

label7:
	bne,a loopbegin
	subcc %g1,%g2, %g1

loopexit:
	ta 0 ! end of test

