.section ".text"
.global a64strncpy
.type a64strncpy, #function
a64strncpy:
	save %sp,-96,%sp
	mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%i0,%l2
	bne b5

begin64:mov 0x8, %l2
	mov 0x8, %l3 
	mov %i0, %o0
again64:subcc %i2, 0x8, %i2
	ldd [%i1], %l0
	bl ncheck
	addd %l2,%i0,%i0
	zbytedpos %l0, 0xff, %l4
	cmp %l4, 0x0
	be,a again64
	std %l0, [%i0 + -8]
zcheck: mov 0x0, %g1
        mov 0x0, %g0
        std %g0, [%i0 + -8]
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
	st %l0, [%i0 + -8]
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
	
b8:	add %i1, 1, %i1
	b strz
	clrb [%i0 + -8]
b7:	add %i1, 2, %i1
	b strz
b6:	sth  %l5, [%i0 + -8]
	add %i1, 3, %i1
	b strz
	clrb [%i0 + -6]
b4:	add %i1, 5, %i1
	b strz
	clrb [%i0 + -4]
b3:	add %i1, 6, %i1
	b strz
b2:	sth %l5, [%i0 + -4]
	add %i1, 7, %i1
	b strz
	clrb [%i0 + -2]
b1: 	add %i1, 8, %i1
	b strz
	st %l1,[%i0 + -4]
b5:	b strz
	add %i1, 4, %i1
strz:	subcc %i2, 0x8, %i2
	add %i0, 0x8, %i0
        bge,a strz
        std %g0, [%i0]   
ncheck: add %i2, 0x8, %i2
	b comp
	nop
back:	add %i2, -1, %i2
      	stb %g2, [ %i0 + -8 ]
     	cmp %g0, %g2
     	inc %i0
      	addx %g0, %i1, %i1
comp:	cmp %i2, 0
    	bne,a back
     	ldub [%i1 + -8], %g2
	mov %o0,%i0
        restore
	retl
	nop
      	




