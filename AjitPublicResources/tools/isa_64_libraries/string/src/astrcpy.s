.section ".text"
.global _a64_strcpy
.type _a64_strcpy, #function
_a64_strcpy:mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%o0,%l2
	be begin64
	nop
	ba load8
	nop

begin64:mov 0x8, %l2
	mov 0x8, %l3
again64:ldd [%o1], %l0
	zbytedpos %l0, 0xff, %l4
	cmp %l4, 0x0
	bne check
	nop 
	std %l0, [%o0]
	addd %l2,%o0,%o0
	ba again64
	nop

check:	cmp %l4,0x8
        bg load8
	nop

	ld [%o1],%l0
	st %l0,[%o0]
	add 0x4,%o0,%o0
	add 0x4,%o1,%o1
	cmp %l4,0x10
	be exit

load8:	mov 0x1,%l2
	mov 0x1,%l3
back:	ldub [%o1],%l0
	stb %l0,[%o0]
	addd %l2,%o0,%o0
	cmp %l0,0x0
	bne back
	nop

exit:	retl
	nop
