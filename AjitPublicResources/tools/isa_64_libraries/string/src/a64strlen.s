.section ".text"
.global a64strlen
.type a64strlen, #function
a64strlen:
	save %sp,-96,%sp
	mov 0x7,%l2
	andcc %l2,%i0,%l2			!!!check for alignements
	mov %g0,%i1	
	be begin64


aligns:						!!!align the string address to a dowrd boundary
	ldub [%i0],%l0
	inc %i0
	cmp %l0,0x0
	be b8
	andcc %i0,0x7,%l4
	bne aligns
	inc %i1

begin64:mov 0x8, %l2

again64:ldd [%i0], %l0				!!! load stting and check for zero
	add %l2,%i0,%i0
	zbytedpos %l0, 0xf, %l4
	cmp %l4, 0x0
	be,a again64
	add %i1,8,%i1				!!! if no null byte increment length counter and repeat
		
zcheck: srld %l0, 0x38, %l4			!!!checks where null byte is by shifting and testing each byte
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

b8:     mov %i1,%i0
        restore
        retl
        nop
b7:     add %i1,1,%i1
        mov %i1,%i0
        restore
        retl
        nop
b6:     add %i1,2,%i1
        mov %i1,%i0
        restore
        retl
        nop
b4:     add %i1,4,%i1
        mov %i1,%i0
        restore
        retl
        nop
b3:     add %i1,5,%i1
        mov %i1,%i0
        restore
        retl
        nop
b2:     add %i1,6,%i1
        mov %i1,%i0
        restore
        retl
        nop
b1:     add %i1,7,%i1
        mov %i1,%i0
        restore
        retl
        nop
b5:     add %i1,3,%i1
        mov %i1,%i0
        restore
        retl
        nop
