.global main
.text
main:
start:
	save %sp, -80, %sp

        set 0x3,%g2
	mov 0xfffffffc,%g3
	and %fp, %g3,%fp
        st %g2, [%fp + -4]   !Store values to be exchanged in memory
        mov %fp, %g2
        add %g2, -4, %g2

        mov 0x3, %g1
	mov 0x5, %g4

        cswapa   [%g2 + %g1] 0x0A, %g4
	ld [%g2], %g2
	


end: 	ta 0
