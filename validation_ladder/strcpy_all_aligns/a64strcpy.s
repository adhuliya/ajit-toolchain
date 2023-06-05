.section ".text"
.global a64strcpy
.type a64strcpy, #function
a64strcpy:
	save %sp,-96,%sp
	mov 0x7,%l2
	mov 0x7,%l3
	anddcc %l2,%i0,%l2
	be begin64
	mov %i0,%o0
	cmp %l3,0x0  			!! check if source is unaligned
	bne beginas			!! go to start of aligning source
	nop
	b destuna			!! else source is aligned dest is not  
	nop

begin64:				!! if both source and dest are dword aligned, do some basic intializations
	mov 0x8, %l2
	mov 0x8, %l3
again64:				!!! main loop that does copying and checks for end of string
	ldd [%i1], %l0
	addd %l2,%i0,%i0
	zbytedpos %l0, 0xff, %l4	!!checks for zero byte
	cmp %l4, 0x0
	be,a again64
	std %l0, [%i0 + -8]
	b zcheck
	nop

beginas:				!!! if source not aligned, align it to dword
	mov 0x1, %l2
        mov 0x1, %l3
aligns:					!!! align source to dowrd
	ldub [%i1], %l5	
	addd %i0,%l2,%i0
	cmp %l5, 0
	be,a b5				!!! If null byte found store it and exit
	clrb [%i0 + -1]    	
	andcc %i1,7,%l6  		!!!check if source is aligned
	bne aligns
	stub %l5,[%i0 + -1]
	andcc %i0, 7, %l6 		!!!is destination aligned to dword?
	be begin64
	
destuna:				!!!we have aligned source to dword now for other cases of dest
					!!!check dest alignment -- compare with 1 (byte), 2 (hword), 4(word)
	mov 0x8, %l2
        mov 0x8, %l3
	ldd [%i1],%l0 			!!!load, add to i1
	zbytedpos %l0, 0xff, %l4	!!!check for null byte
        cmp %l4, 0x0
        bne,a zcheck			!!if found go to check zero
	add %i0,8,%i0			!! only if null byte is found
	add %i1,8,%i1			!!! add as one dword loaded
	andcc %i0,3,%l4
	be wordal        		!!!dest is word aligned	
	cmp %l4, 2
	be hwrdal		 	!!!dest is hword aligned	
	nop
	b byteal
	nop
	!!else byte aligned


!!!!!!!!!!!!word aligned!!!!!!!!!!!
wordal: 
	st %l0,[%i0]
	add %i0,4,%i0
wrdlag:	
	slld %l0,0x20,%l6          	!!!shift to get lower word of previous dword into l6
	ldd [%i1],%l0
	addd %l2,%i0,%i0
	zbytedpos %l0, 0xff, %l4	!!!check for zero
	mov %l0,%l7		   	!!!shift the next word in l7 
        cmp %l4, 0x0
        be,a wrdlag
	std %l6,[%i0 + -8]		!!! if no null byte store dowrd and loop 
	st %l6,[%i0 + -8]		!!! else store word of previous dword and go for zero check
        b zcheck
	add %i0,4,%i0

!!!!!!!!!!!!!!!!!!ha1fword alignments !!!!!!!!!!!!
hwrdal: 
	srld %l0,0x30,%l4
	sth %l5,[%i0]         		!!!store first hword
	add %i0,2,%i0        
	andcc %i0,7,%l4       		!!!it is dword aligned?
	be hwrddag
	srld %l0,0x10,%l4
	st  %l5,[%i0]	      		!!!else store another word
	add %i0,4,%i0
hwrdag:	
	slld %l0,0x30,%l6		!!!shift for saving unstored halfword
	ldd [%i1],%l0			!!! load next dword
        addd %l2,%i0,%i0
        zbytedpos %l0, 0xff, %l4	!!! check for null byte
	srld %l0,0x10,%o2		!!! shift and or to create dword for store	
	ord %o2,%l6,%l6
        cmp %l4, 0x0
	be,a hwrdag
	std %l6,[%i0 + -8]		!!! if no null byte store dowrd
 	srl %l6,0x10,%l6		!!! else store remaining of the halfword of previous dword
	sth %l6,[%i0 + -8]			
	b zcheck
	add %i0,2,%i0
	

hwrddag:
	slld %l0,0x10,%l6		!!! shift to save three halfwords
        ldd [%i1],%l0			
        addd %l2,%i0,%i0
        zbytedpos %l0, 0xff, %l4	!!! check for zero
        srld %l0,0x30,%o2		!!! shift to create dword
	ord %o2,%l6,%l6
        cmp %l4, 0x0
        be,a hwrddag
        std %l6,[%i0 + -8]		!!! if no null byte store dword	
	srld %l6,0x30,%l4		!!! else store the three halfwords from previous dword
	sth %l5,[%i0 + -8]
	srld %l6,0x20,%l4
	sth %l5,[%i0 + -6]
	srld %l6,0x10,%l4
	sth %l5,[%i0 + -4]
	b zcheck 
	add %i0,6,%i0


!!!!!!!!!!!!!!!!!!byte alignments!!!!!!!!!!!!!


byteal: 
	srld %l0,0x38,%l4		!!!store bytes till dword boundary for destination
	stb %l5,[%i0]
	add %i0,1,%i0
	andcc %i0,7,%l4
        be dword1       		!!!dword after first byte
	srld %l0,0x28,%l4
	sth %l5, [%i0]
	add %i0,2,%i0
	andcc %i0,7,%l4
        be dword3      			!!!dword after third byte     
	srld %l0,0x18,%l4
        sth %l5, [%i0]
        add %i0,2,%i0
        andcc %i0,7,%l4
	be dword5      			!!!dword after fifth byte
        srld %l0,0x8,%l4
        sth %l5, [%i0]
        add %i0,2,%i0

dword7:					!!!dowrd after 7th byte
	slld %l0,0x38,%l6		!!!save the single byte from previous dword
        ldd [%i1],%l0
        addd %l2,%i0,%i0		
        zbytedpos %l0, 0xff, %l4	!!!check for zero
        srld %l0,0x8,%o2		!!!shift by 1 byte as we need 7 bytes
        ord %o2,%l6,%l6
        cmp %l4, 0x0
        be,a dword7
        std %l6,[%i0 + -8]		!!!if no null byte store the dword
	srl %l6,0x18,%l6		!!!else store the remaining byte from previous dword and go to check zero
	stb %l6,[%i0 + -8]
	b zcheck
        add %i0,1,%i0

dword5:
        slld %l0,0x28,%l6		!!!save remaining bytes of dword
        ldd [%i1],%l0			!!!load a new dword
        addd %l2,%i0,%i0
        zbytedpos %l0, 0xff, %l4	!!!check for zero
        srld %l0,0x18,%o2		!!! perform shift and or to create the dword to be stored
        ord %o2,%l6,%l6
        cmp %l4, 0x0
        be,a dword5
        std %l6,[%i0 + -8]		!!!if no null byte store the dword
	srl %l6,0x10,%l7		!!else store the remaining byte from previous dword and go to check zero
	sth %l7,[%i0 + -8]
	srl %l6,0x8,%l6
	stb %l6,[%i0 + -6]
        b zcheck
        add %i0,3,%i0

dword3:
        slld %l0,0x18,%l6		!!!save remaining bytes of dword
        ldd [%i1],%l0			
        addd %l2,%i0,%i0
        zbytedpos %l0, 0xff, %l4	!!!check for zero
    	srld %l0,0x28,%o2		!!! perform shift and or to create the dword to be stored
        ord %o2,%l6,%l6
        cmp %l4, 0x0
        be,a dword3
        std %l6,[%i0 + -8]		!!!if no null byte store the dword
	st %l6,[%i0 + -8]		!!else store the remaining byte from previous dword and go
	srl %l7,0x18,%l7
	stb %l7,[%i0 + -4]
        b zcheck
        add %i0,5,%i0

	
dword1:
        slld %l0,0x8,%l6		!!!save remaining bytes of dword
        ldd [%i1],%l0
        addd %l2,%i0,%i0
        zbytedpos %l0, 0xff, %l4	!!!check for zero
        srld %l0,0x38,%o2		!!! perform shift and or to create the dword to be stored
        ord %o2,%l6,%l6
        cmp %l4, 0x0
        be,a dword1
        std %l6,[%i0 + -8]		!!!if no null byte store the dword
        st %l6, [%i0 + -8]		!!else store the remaining byte from previous dword and go
	srl %l7,0x10,%l5
	sth %l5,[%i0 + -4]
	srl %l7,0x8,%l7
	stb %l7,[%i0 + -2]
        b zcheck
        add %i0,7,%i0



!!!!!!!!!!!null byte check at end!!!!!!!

zcheck: 				!!check where the zero byte is in the dword
	srld %l0, 0x38, %l4		!!shift required byte
        btst 0xff, %l5			!!and to check for zero
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
	srl %l0,0x18,%l2	     	!!!if null byte not at b6, store a word
	stb %l2, [%i0 + -8]	 
        srl %l0,0x10,%l2
        stb %l2, [%i0 + -7]
        srl %l0,0x8,%l2
        stb %l2, [%i0 + -6]
        stb %l0, [%i0 + -5]
        be b5
        !st %l0, [%i0 + -8]           !!!change this for byte aligned
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
        btst 0xff, %l5
        be b1
        nop

b8:     clrb [%i0 + -8]			!!!makes stores according to null byte postion
        mov %o0,%i0
        restore
        retl
        nop
b7:    	srl  %l5, 0x8,%l7
        stb  %l7, [%i0 + -8]
        stb  %l5, [%i0 + -7]
        mov %o0,%i0
        restore
        retl
        nop
b6:     srl  %l5, 0x8,%l7
	stb  %l7, [%i0 + -8]
	stb  %l5, [%i0 + -7]
        clrb [%i0 + -6]
        mov %o0,%i0
        restore
        retl
        nop
b4:     clrb [%i0 + -4]
        mov %o0,%i0
        restore
        retl
        nop
b3:     srl  %l5, 0x8,%l7
        stb  %l7, [%i0 + -4]
        stb  %l5, [%i0 + -3]
        mov %o0,%i0
        restore
        retl
        nop
b2:     srl  %l5, 0x8,%l7
        stb  %l7, [%i0 + -4]
        stb  %l5, [%i0 + -3]
        clrb [%i0 + -2]
        mov %o0,%i0
        restore
        retl
        nop
b1:     srl %l0,0x18,%l2
        stb %l2, [%i0 + -4]
        srl %l0,0x10,%l2
        stb %l2, [%i0 + -3]
        srl %l0,0x8,%l2
        stb %l2, [%i0 + -2]
        stb %l0, [%i0 + -1]
        mov %o0,%i0
        restore
        retl
	nop
b5:	mov %o0,%i0
        restore
	retl
	nop


