! an example to show how branch prediction gets lucky.
! In each case the branch prediction is correct, so
! the stream goes on and on till the trap exception.

.global main
main:
_start:
	
	! initialize register values.. these will
	! be overwritten in the delay slots below.
	mov 0x3, %o0
	mov 0x4, %o1
	mov 0x5, %o2

	ba label1	! conditional branch that is taken
	mov 0xF00, %o0	! delay slot instruction is always executed 
label1:
	ba label2
	mov 0xF01, %o1	! delay slot instruction is always executed 
label2:
	ba label3
	mov 0xF02, %o2	! delay slot instruction is always executed 
label3:
	ta 0 ! end of test

