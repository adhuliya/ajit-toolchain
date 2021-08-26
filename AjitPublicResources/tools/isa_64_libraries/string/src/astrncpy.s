.section ".text"
.global _a64_strncpy
.type _a64_strncpy, #function
_a64_strncpy: 

	mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%o0,%l2
	be begin64
	nop
	ba back

begin64:mov 0x4, %l2
	mov 0x4, %l3
again64:ld [%o1], %l0
	deccc 4, %o2
        ble null
        mov %l0, %l5
        not %l5,%l6
        set 0x01010101,%l4
        sub %l5,%l4,%l5
        set 0x80808080,%l4
        and %l6,%l4,%l6
        and %l5,%l6,%l4
	cmp %l4, 0x0
	bne null
	nop 
	st %l0, [%o0]
	addd %l2,%o0,%o0
	ba begin64
	nop


null:	inc 4, %o2
	mov 0x1, %l2
	mov 0x1,%l3
back:	ldub [%o1], %l0
	stb %l0,[%o0]
	addd %l2,%o0,%o0
	deccc %o2
	be exit
	cmp %l0,0x0
	bne back

back1:	mov 0x0, %l5
	stb %l5,[%o0]
	addd %l2,%o0,%o0
	deccc %o2
	bne back1

exit:	retl
	nop
