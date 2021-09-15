.section ".text"
.global a64strcmp
.type a64strcmp, #function
a64strcmp: 

	mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%o0,%l0
	bne exit
	nop
begin64:mov 0x8, %l2
	mov 0x8, %l3
again64:ldd [%o0],%l0
	ldd [%o1],%l6
	subdcc %l0, %l6, %l4
	bne uneq
	zbytedpos %l0, 0xff, %l4
	cmp %l4, 0x0 
	be,a again64
	addd %l2,%o0,%o0
	mov 0, %o0
exit:	retl
	nop
uneq: 	srld %l0, 0x38, %o2
        srld %l6, 0x38, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %o0 
        bne exit
	srld %l0, 0x30, %o2
	srld %l6, 0x30, %o4
	btst 0xff, %o3
	be exit
	subcc %o3, %o5, %o0 
	bne exit
	srld %l0, 0x28, %o2
        srld %l6, 0x28, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %o0
        bne exit
	srld %l0, 0x20, %o2
        srld %l6, 0x20, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %o0
        bne exit
	srld %l0, 0x18, %o2
        srld %l6, 0x18, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %o0
        bne exit
	srld %l0, 0x10, %o2
        srld %l6, 0x10, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %o0
        bne exit
	srld %l0, 0x8, %o2
        srld %l6, 0x8, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %o0
        bne exit
	btst 0xff, %l1
	be exit
	subcc %l1, %l7, %o0
	bne exit
	nop



	

