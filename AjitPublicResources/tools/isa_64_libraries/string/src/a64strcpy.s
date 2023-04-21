.section ".text"
.global a64strcpy
.type a64strcpy, #function
a64strcpy:
	save %sp,-96,%sp
	mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%i0,%l2
	bne b5

begin64:mov 0x8, %l2
	mov 0x8, %l3
	mov %i0,%o0
again64:ldd [%i1], %l0
	addd %l2,%i0,%i0
	zbytedpos %l0, 0xff, %l4
	cmp %l4, 0x0
	be,a again64
	std %l0, [%i0 + -8]
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
        st %l0, [%i0 + -8]
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

b8:     clrb [%i0 + -8]
        mov %o0,%i0
        restore
        retl
        nop
b7:     sth  %l5, [%i0 + -8]
        mov %o0,%i0
        restore
        retl
        nop
b6:     sth  %l5, [%i0 + -8]
        clrb [%i0 + -6]
        mov %o0,%i0
        restore
        retl
        nop
b4:     clrb [%i0 + -4]
        mov %o0,%i0
        restore
        retl
        nop
b3:     sth %l5, [%i0 + -4]
        mov %o0,%i0
        restore
        retl
        nop
b2:     sth %l5, [%i0 + -4]
        clrb [%i0 + -2]
        mov %o0,%i0
        restore
        retl
        nop
b1:     st %l1,[%i0 + -4]
        mov %o0,%i0
        restore
        retl
	nop
b5:	mov %o0,%i0
        restore
	retl
	nop


