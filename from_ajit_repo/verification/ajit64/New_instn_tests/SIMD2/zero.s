
.text
.global main

main:
start: 
	mov 0x1,%g2              !input in 64 bit register
	set 0x01010101,%g3
	mov 0xfb,%g4             !mask
	zbytedpos %g2,%g4,%g6    !g6 = 0xe0

	zbytedpos %g2, 0xf1,%g7  !g7 = 0xe0


end:    ta 0
