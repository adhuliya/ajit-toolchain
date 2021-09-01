.section ".text"
.global a64strcpy
.type a64strcpy, #function
a64strcpy:
	mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%o0,%l2
	bne b5

begin64:mov 0x8, %l2
	mov 0x8, %l3
	mov %o0,%i0
again64:ldd [%o1], %l0
	addd %l2,%o0,%o0
	zbytedpos %l0, 0xff, %l4
	cmp %l4, 0x0
	be,a again64
	std %l0, [%o0 + -8]
zcheck: srld %l0, 0x38, %l4
        btst 0xff, %l5
        be b8
        srld %l0, 0x30, %l4
        btst 0xff, %l5
        be b7
        nop
        srld %l0, 0x28, %l4
        btst 0xff, %l5
        be b6
        srld %l0, 0x30, %l4
        srld %l0, 0x20, %l4
        btst 0xff, %l5
        be b5
        st %l0, [%o0 + -8]
        srld %l0, 0x18, %l4
        btst 0xff, %l5
        be b4
        srld %l0, 0x10, %l4
        btst 0xff, %l5
        be b3
        nop
        srld %l0, 0x8, %l4
        btst 0xff, %l5
        be b2
        srld %l0,0x10,%l4
        btst 0xff, %l1
        be b1
        nop

b8:     clrb [%o0 + -8]
        retl
        mov %i0,%o0
b7:     sth  %l5, [%o0 + -8]
        retl
        mov %i0,%o0
b6:     sth  %l5, [%o0 + -8]
        clrb [%o0 + -6]
        retl
        mov %i0,%o0
b4:     clrb [%o0 + -4]
        retl
        mov %i0,%o0
b3:     sth %l5, [%o0 + -4]
        retl
        mov %i0,%o0
b2:     sth %l5, [%o0 + -4]
        clrb [%o0 + -2]
        retl
        mov %i0,%o0
b1:     st %l1,[%o0 + -4]
        retl
	mov %i0,%o0
b5:	retl
	mov %i0,%o0


