.section ".text"
.global a64strcasecmp
.type a64strcasecmp, #function
a64strcasecmp:
	save %sp,-96,%sp
	mov 0x7,%l2
	mov 0x7,%l3
	set 0x20202020, %o0
	mov %o0,%o1
	anddcc %l2,%i0,%l2
	be begin64
	cmp %l2,0x0  			!! check if i0 is unaligned
	bne beginas			!! go to start of aligning source
	nop
	b destuna			!! else source is aligned dest is not  
	nop

begin64:				!! if both source and dest are dword aligned, do some basic intializations
	mov 0x8, %l2
	mov 0x8, %l3
again64:				!!! main loop that does copying and checks for end of string
	ldd [%i0],%l0
        ldd [%i1],%l6
	ord %l0,%o0,%o2
        ord %l6,%o0,%o4
        subdcc %o2, %o4, %l4
        bne uneq
        zbytedpos %l0, 0xff, %l4
        cmp %l4, 0x0
        be,a again64
        addd %l2,%i0,%i0
	b exit
	mov %g0,%i0

beginas:				!!! if source not aligned, align it to dword
	mov 0x1, %l2
        mov 0x1, %l3
	mov 0xff,%o2
	mov 0xff,%o3
aligns:	
	ldub [%i0],%l4				!!! align source to dowrd
	ldub [%i1], %l5
	ord %l4,%o0,%o4
	subdcc %o4, %o5, %l6
	bne,a exit
	mov %l6,%i0
	anddcc %l4,%o2,%o4		!!check for null byte
	be,a exit
	mov %g0,%i0
	addd %i0,%l2,%i0
	andcc %i0,7,%l6  		!!!check if source is aligned
	bne aligns	
	andcc %i1, 7, %l6 		!!!is destination aligned to dword?
	be begin64
	
destuna:				!!!we have aligned source to dword now for other cases of dest
					!!!check dest alignment -- compare with 1 (byte), 2 (hword), 4(word)
	mov %g0,%g1
	mov 0x8, %l2
        mov 0x8, %l3
	ldd [%i0],%l0 			!!!load, add to i0
	ord %l0,%o0,%i2
	zbytedpos %l0, 0xff, %l4	!!!check for null byte
        cmp %l4, 0x0
        bne loadi	
	add %i0,8,%i0			!!if found go to check zero
	andcc %i1,3,%l4
	be wordal       		!!! other sting is word aligned	
	cmp %l4, 2
	be hwrdal		 	!!! other string is hword aligned	
	nop
	b byteal
	nop
	!!else byte aligned

loadi:	
					!!load 8 i0 in l6-l7 create a dword to compare with zeros of i1
	mov %g0,%l4
	ldub [%i1],%l5
	slld %l4,0x38,%l6
	mov %g0,%l4
	ldub [%i1],%l5
        slld %l4,0x30,%o2
	ord  %l6,%o2,%l6
	mov %g0,%l4
	ldub [%i1],%l5
        slld %l4,0x28,%o2
	ord  %l6,%o2,%l6
        mov %g0,%l4
	ldub [%i1],%l5
        slld %l4,0x20,%o2
	ord  %l6,%o2,%l6
        mov %g0,%l4
	ldub [%i1],%l5
        slld %l4,0x18,%o2
	ord  %l6,%o2,%l6
        mov %g0,%l4
	ldub [%i1],%l5
        slld %l4,0x10,%o2
	ord  %l6,%o2,%l6
        mov %g0,%l4
	ldub [%i1],%l5
        slld %l4,0x8,%o2
	ord  %l6,%o2,%l6
        mov %g0,%l4
	ldub [%i1],%l5
       	ord  %l6,%o2,%l6
 	ord %l0,%o0,%o2
        ord %l6,%o0,%o4	
	subdcc %o2,%o4,%l4
	be,a exit
	mov %g0,%i0
	b uneq
        nop



!!!!!!!!!!!!word aligned!!!!!!!!!!!
wordal: 
	ld [%i1],%l6
	or %l6,%o0,%i4
	subcc %i2,%i4,%l4
	bne uneq
	zbytedpos %l0, 0xf, %l4	
	cmp %l4,0x0
	bne,a exit
	mov 0,%i0
	add %i1,4,%i1
wrdlag:	
	slld %l0,0x20,%o4         	!!!shift to get lower word of previous doubleword into l6
	ldd [%i0],%l0
	ldd [%i1],%l6
	mov %l0,%o5
	ord %o4,%o0,%i2
        ord %l6,%o0,%i4
	subdcc %i2, %i4, %l4
	bne,a uneq
	ord %g0,%o4,%l0			!!!mov o4 to l0 for unequal checks
	zbytedpos %l6, 0xff, %l4	!!!check for zero 
        cmp %l4, 0x0
        be,a wrdlag
	addd %l2,%i0,%i0
	b exit
	mov 0,%i0
		
!!!!!!!!!!!!!!!!!!ha1fword alignments !!!!!!!!!!!!
hwrdal: 
	set 0xffff ,%l7
	srld %i2,0x30,%l4
	lduh [%i1],%l6
	or %l6,%o0,%i5
	and %i5,%l7,%i5
	subcc %l5,%i5,%l4
	bne,a uneq
	sll %l6,0x10,%l6		!!!shift so that halfword at top of l6
	add %i1,2,%i1        
	andcc %i1,7,%l4       		!!!it is dword aligned?
	be hwrddag
	srld %i2,0x10,%l4
        ld [%i1],%l6
	or %l6,%o0,%i5
        subcc %l5,%i5,%l4
        bne,a uneq
	sll %l6,0x10,%l6
	add %i1,4,%i1
hwrdag:	
	slld %l0,0x30,%o4		!!!shift for saving unstored halfword
	ldd [%i0],%l0			!!! load next dword
	ldd [%i1],%l6
        srld %l0,0x10,%o2               !!! shift and or to create dword for store      
        ord %o2,%o4,%o4
	ord %o4,%o0,%i2
        ord %l6,%o0,%i4
        subdcc %i2, %i4, %l4
	bne,a uneq
	ord %g0,%o4,%l0
        zbytedpos %l6, 0xff, %l4	!!! check for null byte
        cmp %l4, 0x0
	be,a hwrdag
	addd %l2,%i0,%i0
	b exit
	mov %g0,%i0
 
hwrddag:
	slld %l0,0x10,%o4		!!! shift to save three halfwords
        ldd [%i0],%l0	
	ldd [%i1],%l6		
        srld %l0,0x30,%o2		!!! shift to create doubleword
	ord %o2,%o4,%o4
	ord %o4,%o0,%i2
        ord %l6,%o0,%i4
        subdcc %i2, %i4, %l4
        bne,a uneq
	ord %g0,%o4,%l0
        zbytedpos %l0, 0xff, %l4	!!! check for zero
        cmp %l4, 0x0
        be,a hwrddag
        addd %l2,%i0,%i0
	b exit
        mov %g0,%i0


!!!!!!!!!!!!!!!!!!byte alignments!!!!!!!!!!!!!


byteal:	
	set 0xffff ,%l7 
	srld %i2,0x38,%l4
	ldub [%i1],%l6
	or %l6,%o0,%i5
	and %i5,0xff,%i5		!!!make sure only last byte has required string
	subcc %l5,%i5,%l4
	bne,a exit 			!!this byte is unequal
	mov %l4,%i0
	add %i1,1,%i1
	andcc %i1,7,%l4
        be dword1       		!!!dword after first byte
	srld %i2,0x28,%l4
	lduh [%i1],%l6
	or %l6,%o0,%i5
        and %i5,%l7,%i5
	andcc %l5,%l7,%l5
	subcc %l5,%i5,%l4
        bne,a uneq
        sll %l6,0x10,%l6                !!!shift so that halfword at top of l6
	add %i1,2,%i1
	andcc %i1,7,%l4
        be dword3      			!!!dword after third byte     
	srld %i2,0x18,%l4
        lduh [%i1],%l6
	andcc %l5,%l7,%l5
	or %l6,%o0,%i5
        and %i5,%l7,%i5
        subcc %l5,%i5,%l4
        bne,a uneq
	sll %l6,0x10,%l6                !!!shift so that halfword at top of l6
        add %i1,2,%i1
        andcc %i1,7,%l4
	be dword5      			!!!dword after fifth byte
        srld %i2,0x8,%l4
        lduh [%i1],%l6
	andcc %l5,%l7,%l5
	or %l6,%o0,%i5
        and %i5,%l7,%i5
        subcc %l5,%i5,%l4
        bne,a uneq
        sll %l6,0x10,%l6                !!!shift so that halfword at top of l6
        add %i1,2,%i1

dword7:					!!!dowrd after 7th byte
	slld %l0,0x38,%o4		!!!save the single byte from previous dword
        ldd [%i0],%l0
	ldd [%i1],%l6
        srld %l0,0x8,%o2		!!!shift by 1 byte as we need 7 bytes
        ord %o2,%o4,%o4
	ord %o4,%o0,%i2
        ord %l6,%o0,%i4
        subdcc %i2, %i4, %l4
	bne,a uneq
	ord %g0,%o4,%l0
        zbytedpos %l0, 0xff, %l4	!!!check for zero
        cmp %l4, 0x0
        be,a dword7
        addd %l2,%i0,%i0		
        b exit
        mov %g0,%i0


dword5:
        slld %l0,0x28,%o4
        ldd [%i0],%l0
	ldd [%i1],%l6 
        srld %l0,0x18,%o2
        ord %o2,%o4,%o4
	ord %o4,%o0,%i2
        ord %l6,%o0,%i4
        subdcc %i2, %i4, %l4
        bne,a uneq
        ord %g0,%o4,%l0
        zbytedpos %l0, 0xff, %l4
        cmp %l4, 0x0
        be,a dword5
        addd %l2,%i0,%i0
        b exit
        mov %g0,%i0

dword3:
        slld %l0,0x18,%o4
        ldd [%i0],%l0
	ldd [%i1],%l6
    	srld %l0,0x28,%o2
        ord %o2,%o4,%o4
	ord %o4,%o0,%i2
        ord %l6,%o0,%i4
        subdcc %i2, %i4, %l4
        bne,a uneq
        ord %g0,%o4,%l0
        zbytedpos %l0, 0xff, %l4
        cmp %l4, 0x0
        be,a dword3
        addd %l2,%i0,%i0
        b exit
        mov %g0,%i0

	
dword1:
        slld %l0,0x8,%o4
        ldd [%i0],%l0
	ldd [%i1],%l6
        srld %l0,0x38,%o2
        ord %o2,%o4,%o4
	ord %o4,%o0,%i2
        ord %l6,%o0,%i4
        subdcc %i2, %i4, %l4
        bne,a uneq
        ord %g0,%o4,%l0
        zbytedpos %l0, 0xff, %l4
        cmp %l4, 0x0
        be,a dword1
        addd %l2,%i0,%i0
        b exit
        mov %g0,%i0

!!!!!!!!!!unequal byte check at for last doubleword!!!!!!!
uneq:   
	srld %l0, 0x38, %o2
        srld %l6, 0x38, %o4
        btst 0xff, %o3
        or %o3,%o0,%o3
        or %o5,%o0,%o5
        be zero
        subcc %o3, %o5, %i0
        bne checkz
        srld %l0, 0x30, %o2
        srld %l6, 0x30, %o4
        btst 0xff, %o3
        or %o3,%o0,%o3
        or %o5,%o0,%o5
        be zero
        subcc %o3, %o5, %i0
        bne checkz
        srld %l0, 0x28, %o2
        srld %l6, 0x28, %o4
        btst 0xff, %o3
        or %o3,%o0,%o3
        or %o5,%o0,%o5
        be zero
        subcc %o3, %o5, %i0
        bne checkz
        srld %l0, 0x20, %o2
        srld %l6, 0x20, %o4
        btst 0xff, %o3
        or %o3,%o0,%o3
        or %o5,%o0,%o5
        be zero
        subcc %o3, %o5, %i0
        bne checkz
        srld %l0, 0x18, %o2
        srld %l6, 0x18, %o4
        btst 0xff, %o3
        or %o3,%o0,%o3
        or %o5,%o0,%o5
        be zero
        subcc %o3, %o5, %i0
        bne checkz
        srld %l0, 0x10, %o2
        srld %l6, 0x10, %o4
        btst 0xff, %o3
        or %o3,%o0,%o3
        or %o5,%o0,%o5
        be zero
        subcc %o3, %o5, %i0
        bne checkz
        srld %l0, 0x8, %o2
        srld %l6, 0x8, %o4
        btst 0xff, %o3
        or %o3,%o0,%o3
        or %o5,%o0,%o5
        be zero
        subcc %o3, %o5, %i0
        bne checkz
	ord %l0, %g0, %o2
        ord %l6, %g0, %o4
	btst 0xff, %o3
        or %o3,%o0,%o3
        or %o5,%o0,%o5
        be zero
        subcc %o3, %o5, %i0
        bne checkz
        nop

checkz:					!!!checks for zero byte in other string
	and %o5,0xff,%o4
        cmp %o4,0x20
	bne exit
	add %i0,0x20,%i0
	b exit
	nop
	


zero:					!!!if null byte found, make last byte zero
	be exit
	set 0xffffff00,%o4
	and %o3,%o4,%o3
	sub %o3,%o5,%i0
exit: 
	restore 
	retl
	nop
