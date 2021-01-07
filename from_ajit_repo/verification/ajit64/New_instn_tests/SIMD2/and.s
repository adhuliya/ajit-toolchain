
.text
.global main

main:
start:
    	set 0xffffffff,%g3	 !input to 64 bit register
        set 0Xfffffff0,%g2
        mov 0Xff,%g4             !mask
	mov 0xf, %g5

       
	anddreduce8 %g2,%g4,%g6   !g6 = e
        anddreduce16 %g2,%g5,%g7   !g6 = e




end:	ta 0
