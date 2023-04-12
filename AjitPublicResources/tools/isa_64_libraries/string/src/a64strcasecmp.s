.section ".text"
.global a64strcasecmp
.type a64strcasecmp, #function
a64strcasecmp: 
	save %sp,-96,%sp
	mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%i0,%l0
	bne exit
	nop
begin64:mov 0x8, %l2
	mov 0x8, %l3
	set 0x20202020, %o0
	mov %o0,%o1
again64:ldd [%i0],%l0
	ldd [%i1],%l6
	ord %l0,%o0,%o2
	ord %l6,%o0,%o4
	subdcc %o2, %o4, %l4
	bne uneq
	zbytedpos %l0, 0xff, %l4
	cmp %l4, 0x0 
	be,a again64
	addd %l2,%i0,%i0
	mov 0, %i0
exit:	restore
	retl
	nop
uneq: 	srld %l0, 0x38, %o2
	srld %l6, 0x38, %o4
	btst 0xff, %o3
	or %o3,0x20,%o3
	or %o5,0x20,%o3
	be exit
	subcc %o3, %o5, %i0 
	bne exit
	srld %l0, 0x30, %o2
        srld %l6, 0x30, %o4
        btst 0xff, %o3
	or %o3,0x20,%o3
        or %o5,0x20,%o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
	srld %l0, 0x28, %o2
        srld %l6, 0x28, %o4
        btst 0xff, %o3
	or %o3,0x20,%o3
        or %o5,0x20,%o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
	srld %l0, 0x20, %o2
        srld %l6, 0x20, %o4
        btst 0xff, %o3
	or %o3,0x20,%o3
        or %o5,0x20,%o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
	srld %l0, 0x18, %o2
        srld %l6, 0x18, %o4
        btst 0xff, %o3
	or %o3,0x20,%o3
        or %o5,0x20,%o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
	srld %l0, 0x10, %o2
        srld %l6, 0x10, %o4
        btst 0xff, %o3
	or %o3,0x20,%o3
        or %o5,0x20,%o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
	srld %l0, 0x8, %o2
        srld %l6, 0x8, %o4
        btst 0xff, %o3
        or %o3,0x20,%o3
        or %o5,0x20,%o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
	nop
	btst 0xff, %l1
	or %l1,0x20,%l1
        or %l7,0x20,%l7
	be exit
	subcc %l1, %l7, %i0
	bne exit
	nop



	

