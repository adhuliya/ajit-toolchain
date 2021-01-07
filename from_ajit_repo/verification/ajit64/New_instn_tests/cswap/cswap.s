.global main
.text
main:
start:
	save %sp, -80, %sp

        set 0x3,%g2
        set 0xfffffffc,%g3   !double-word aligned for std
        and %fp, %g3,%fp	
        st %g2, [%fp + -4]   !Store values to be exchanged in memory
        mov %fp, %g2
        add %g2, -4, %g2

        mov 0x3, %g1
	mov 0x5, %g4
	mov 0x6, %g5

        cswap   [%g2 + %g1] 0x08, %g4
        cswap   [%g2 + 0x5]     , %g5
	ld [%g2], %g2
	restore


end: 	ta 0
