.section ".text"
.global a64strcmp
.type a64strcmp, #function
a64strcmp:
	save %sp,-96,%sp
	mov 0x7,%l2
	mov 0x7,%l3
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
        subdcc %l0, %l6, %l4
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
	subcc %l4, %l5, %l6
	bne,a exit
	mov %l6,%i0
	anddcc %l4,%o2,%o4
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
	subdcc %l0,%l6,%l4
	be,a exit
	mov %g0,%i0
	b uneq
        nop



!!!!!!!!!!!!word aligned!!!!!!!!!!!
wordal: 
	ld [%i1],%l6
	subcc %l0,%l6,%l4
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
	subdcc %o4, %l6, %l4
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
	srld %l0,0x30,%l4
	lduh [%i1],%l6
	subcc %l5,%l6,%l4
	bne,a uneq
	sll %l6,0x10,%l6		!!!shift so that halfword at top of l6
	add %i1,2,%i1        
	andcc %i1,7,%l4       		!!!it is dword aligned?
	be hwrddag
	srld %l0,0x10,%l4
        ld [%i1],%l6
        subcc %l5,%l6,%l4
        bne uneq
	add %i1,4,%i1
hwrdag:	
	slld %l0,0x30,%o4		!!!shift for saving unstored halfword
	ldd [%i0],%l0			!!! load next dword
	ldd [%i1],%l6
        srld %l0,0x10,%o2               !!! shift and or to create dword for store      
        ord %o2,%o4,%o4
	subdcc %o4,%l6,%l4
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
	subdcc %o4,%l6,%l4
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
	srld %l0,0x38,%l4
	ldub [%i1],%l6
	subcc %l5,%l6,%l4
	bne,a exit 			!!this byte is unequal
	mov %l4,%i0
	add %i1,1,%i1
	andcc %i1,7,%l4
        be dword1       		!!!dword after first byte
	srld %l0,0x28,%l4
	lduh [%i1],%l6
	andcc %l5,%l7,%l5
	subcc %l5,%l6,%l4
        bne,a uneq
        sll %l6,0x10,%l6                !!!shift so that halfword at top of l6
	add %i1,2,%i1
	andcc %i1,7,%l4
        be dword3      			!!!dword after third byte     
	srld %l0,0x18,%l4
        lduh [%i1],%l6
	andcc %l5,%l7,%l5
        subcc %l5,%l6,%l4
        bne,a uneq
	sll %l6,0x10,%l6                !!!shift so that halfword at top of l6
        add %i1,2,%i1
        andcc %i1,7,%l4
	be dword5      			!!!dword after fifth byte
        srld %l0,0x8,%l4
        lduh [%i1],%l6
	andcc %l5,%l7,%l5
        subcc %l5,%l6,%l4
        bne,a uneq
        sll %l6,0x10,%l6                !!!shift so that halfword at top of l6
        add %i1,2,%i1

dword7:					!!!dowrd after 7th byte
	slld %l0,0x38,%o4		!!!save the single byte from previous dword
        ldd [%i0],%l0
	ldd [%i1],%l6
        srld %l0,0x8,%o2		!!!shift by 1 byte as we need 7 bytes
        ord %o2,%o4,%o4
	subdcc %o4,%l6,%l4
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
        subdcc %o4,%l6,%l4
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
        subdcc %o4,%l6,%l4
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
        subdcc %o4,%l6,%l4
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
        be exit
        subcc %o3, %o5, %i0
        bne exit
        srld %l0, 0x30, %o2
        srld %l6, 0x30, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
        srld %l0, 0x28, %o2
        srld %l6, 0x28, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
        srld %l0, 0x20, %o2
        srld %l6, 0x20, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
        srld %l0, 0x18, %o2
        srld %l6, 0x18, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
        srld %l0, 0x10, %o2
        srld %l6, 0x10, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
        srld %l0, 0x8, %o2
        srld %l6, 0x8, %o4
        btst 0xff, %o3
        be exit
        subcc %o3, %o5, %i0
        bne exit
        btst 0xff, %l1
        be exit
        subcc %l1, %l7, %i0
        bne exit 
	nop
exit: 
	restore 
	retl
	nop
