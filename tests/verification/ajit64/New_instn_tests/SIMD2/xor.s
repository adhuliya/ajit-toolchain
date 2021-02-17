
.text
.global main

main:
start: 
	mov 0x1,%g2             !Input number in register pair
	set 0x08050401,%g3
	mov 0x1b,%g4            !mask
	mov 0xb, %g5
	xordreduce8 %g2,%g4,%g6   !g6 = e
        xordreduce16 %g2,%g5,%g7   !g6 = e





end:	ta 0
