.section .text.ajitstart
_start_00:
mov 0x1, %g1
mov 0x2, %g2
add %g1, %g2, %g3
ta 0

_start_01:
mov 0x3, %g1
mov 0x4, %g2
add %g1, %g2, %g3
ta 0
