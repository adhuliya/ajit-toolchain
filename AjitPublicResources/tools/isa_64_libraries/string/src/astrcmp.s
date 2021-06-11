.section ".text"
.global _a64_strcmp
.type _a64_strcmp, #function
_a64_strcmp: 

	mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%o0,%l0
	be begin64
	nop
	ba load8
	nop

begin64:mov 0x4, %l2
	mov 0x4, %l3
again64:ld [%o0],%l0
	ld [%o1],%l6
	mov %l0, %l5
        not %l5,%l7
        set 0x01010101,%l4
        sub %l5,%l4,%l5
        set 0x80808080,%l4
        and %l7,%l4,%l7
        and %l5,%l7,%l4

	cmp %l4, 0x0
	bne load8
	nop 
	mov %l6, %l5
        not %l5,%l7
        set 0x01010101,%l4
        sub %l5,%l4,%l5
        set 0x80808080,%l4
        and %l7,%l4,%l7
        and %l5,%l7,%l4

        cmp %l4, 0x0
        bne load8
        nop
	xor %l0,%l6,%l4
	bne load8
	nop
	addd %l2,%o0,%o0
	ba again64
	nop

load8:	mov 0x1,%l2
	mov 0x1,%l3
back:	ldub [%o0],%l0
	ldub [%o1],%l6
	cmp %l0, 0x0
	be nz8
	cmp %l6, 0x0
	be nz8
	nop	
	cmp %l0,%l6
	bne nz8
	nop
	addd %l2,%o0,%o0
	ba back


nz8:	sub %l0,%l6, %l4
	mov %l4,%o0

exit:	retl
	nop
