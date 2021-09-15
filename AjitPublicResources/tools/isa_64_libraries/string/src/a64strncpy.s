.section ".text"
.global a64strncpy
.type a64strncpy, #function
a64strncpy:
	mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%o0,%l2
	bne b5

begin64:mov 0x8, %l2
	mov 0x8, %l3 
	mov %o0, %i0
again64:subcc %o2, 0x8, %o2
	ldd [%o1], %l0
	bl ncheck
	addd %l2,%o0,%o0
	zbytedpos %l0, 0xff, %l4
	cmp %l4, 0x0
	be,a again64
	std %l0, [%o0 + -8]
zcheck: mov 0x0, %g1
        mov 0x0, %g0
        std %g0, [%o0 + -8]
	srld %l0, 0x38, %l4
	btst 0xff, %l5
	be b8
        srld %l0, 0x30, %l4
        btst 0xff, %l5
        be b7
	srld %l0, 0x38, %l4
        srld %l0, 0x28, %l4
        btst 0xff, %l5
        be b6
	srld %l0, 0x38, %l4
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
	srld %l0, 0x18, %l4
        srld %l0, 0x8, %l4
        btst 0xff, %l5
        be b2
	btst 0xff, %l1
	be b1
	nop
	
b8:	add %o1, 1, %o1
	b strz
	clrb [%o0 + -8]
b7:	add %o1, 2, %o1
	b strz
b6:	sth  %l5, [%o0 + -8]
	add %o1, 3, %o1
	b strz
	clrb [%o0 + -6]
b4:	add %o1, 5, %o1
	b strz
	clrb [%o0 + -4]
b3:	add %o1, 6, %o1
	b strz
b2:	sth %l5, [%o0 + -4]
	add %o1, 7, %o1
	b strz
	clrb [%o0 + -2]
b1: 	add %o1, 8, %o1
	b strz
	st %l1,[%o0 + -4]
b5:	b strz
	add %o1, 4, %o1
strz:	subcc %o2, 0x8, %o2
	add %o0, 0x8, %o0
        bge,a strz
        std %g0, [%o0]   
ncheck: add %o2, 0x8, %o2
	b comp
	nop
back:	add %o2, -1, %o2
      	stb %g2, [ %o0 + -8 ]
     	cmp %g0, %g2
     	inc %o0
      	addx %g0, %o1, %o1
comp:	cmp %o2, 0
    	bne,a back
     	ldub [%o1 + -8], %g2
      	retl
	mov %i0,%o0
      	




