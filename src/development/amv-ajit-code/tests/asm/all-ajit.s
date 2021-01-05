	.file	"cons-car-cdr.c"
	.global head
	.section	".bss"
	.align 4
	.type	head, #object
	.size	head, 4
head:
	.skip	4
	.global counter
	.align 4
	.type	counter, #object
	.size	counter, 4
counter:
	.skip	4
	.global lst_len
	.align 4
	.type	lst_len, #object
	.size	lst_len, 4
lst_len:
	.skip	4
	.section	".rodata"
	.align 8
.LC0:
	.asciz	"List as %d members.\n"
	.align 8
.LC1:
	.asciz	"Element %02d : %d\n"
	.section	".text"
	.align 4
	.global main
	.type	main, #function
	.proc	04
main:
	save	%sp, -120, %sp
	addd	%g2, %g4, %g2
	adddcc	%g2, %g4, %g2
	subd	%g2, %g4, %g2
	subdcc	%g2, %g4, %g2
	udivd	%g2, %g4, %g2
	addd    %g1, %g2, %g1
	adddcc  %g1, %g2, %g1
	subd    %g1, %g2, %g1
	subdcc  %g1, %g2, %g1
        slld    %g1, 24, %g2
        srld    %g1, 24, %g2
        srad    %g1, 24, %g2
        slld    %g1, %g3, %g2
        srld    %g1, %g3, %g2
        srad    %g1, %g3, %g2
	addd    %g1, %g2, %g1
	adddcc  %g1, %g2, %g1
	subd    %g1, %g2, %g1
	subdcc  %g1, %g2, %g1
	ord     %g1, %g2, %g1
	ordcc   %g1, %g2, %g1
	ordn    %g1, %g2, %g1
	ordncc  %g1, %g2, %g1
	xordcc  %g1, %g2, %g1
	xnord   %g1, %g2, %g1
	xnordcc %g1, %g2, %g1
	andd    %g1, %g2, %g1
	anddcc  %g1, %g2, %g1
	anddn   %g1, %g2, %g1
	anddncc %g1, %g2, %g1
# Following shift operations use register indirect and direct operands
#slld    %g2, %g2, %g1
#slld    %g1,  32, %g1
#srld    %g2, %g2, %g1
#srld    %g1,  32, %g1
#srad    %g2, %g2, %g1
#srad    %g1,  32, %g1
	slld    %g2, %g4, %l2
	slld    %g2,   2, %l2
	srld    %g2, %g4, %g6
	srld    %g2,   2, %g6
	srad    %g2, %g4, %l0
	srad    %g2,   2, %l0
	addd    %g1, %g2, %g1
	adddcc  %g1, %g2, %g1
	subd    %g1, %g2, %g1
	subdcc  %g1, %g2, %g1
	## umuldaj %g1, %g2, %g0       ## "umuld" from other architectures discarded as per instruction from Prof. Desai.
	## umuldajcc %g1, %g2, %g0
	## smuldaj %g1, %g2, %g0
	## smuldajcc %g1, %g2, %g0
	smul    %g1, %g2, %g0
	smuld   %g1, %g2, %g0
	umul    %g1, %g2, %g0
	umuld   %g1, %g2, %g0
	umuldcc %g1, %g2, %g0
	smuld   %g1, %g2, %g0
	smuldcc %g1, %g2, %g0
	udivd   %g1, %g2, %g1
	udivd   %g1, %g2, %g2
	udivd   %g1, %g2, %g3
	udivd   %g1, %g2, %g4
	udivd   %g1, %g2, %g5
	udivd   %g1, %g2, %g6
	sdivd   %g1, %g2, %g1
	udivdcc %g1, %g2, %g6
	sdivdcc %g1, %g2, %g1
        ## vfadd   %f2, %f4, %f6
        ## vfsub   %f2, %f4, %f6
        ## vfmul   %f2, %f4, %f6
        ## vfdiv   %f2, %f4, %f6
        ## vfsqrt  %f2, %f4, %f6
        vfadd16   %f2, %f4, %f6
        vfsub16   %f2, %f4, %f6
        vfmul16   %f2, %f4, %f6
        vfadd32   %f2, %f4, %f6
        vfsub32   %f2, %f4, %f6
        vfmul32   %f2, %f4, %f6
        ## vfdiv   %f2, %f4, %f6
        ## vfsqrt  %f2, %f4, %f6
        faddreduce16 %f2, %f4
        fstoh        %f1, %f3
        fhtos        %f1, %f3
	adddcc  %g1, %g2, %g1
	subd    %g1, %g2, %g1
	subdcc  %g1, %g2, %g1
        adddreduce8  %g2, %g1, %g4
        ordreduce8   %g2, %g1, %g4
        anddreduce8  %g2, %g1, %g4
        xordreduce8  %g2, %g1, %g4
        zbytedpos    %g2, %g1, %g4
        zbytedpos    %g2, 255, %g4
        adddreduce16 %g2, %g1, %g4
        ordreduce16  %g2, %g1, %g4
        anddreduce16 %g2, %g1, %g4
        xordreduce16 %g2, %g1, %g4
	adddcc  %g1, %g2, %g1
	subd    %g1, %g2, %g1
	subdcc  %g1, %g2, %g1
	vaddd16 %g1, %g2, %g1
	vsubd16 %g1, %g2, %g1
	vumuld16 %g1, %g2, %g1
	vsmuld16 %g1, %g2, %g1
	adddcc  %g1, %g2, %g1
	subd    %g1, %g2, %g1
	subdcc  %g1, %g2, %g1
	vaddd16 %g2, %g4, %g6
        vsubd16 %g2, %g4, %g6
        vumuld16 %g2, %g4, %g6
        vsmuld16 %g2, %g4, %g6
	vaddd32 %g1, %g2, %g1
	vsubd32 %g1, %g2, %g1
	vumuld32 %g1, %g2, %g1
	vsmuld32 %g1, %g2, %g1
	adddcc  %g1, %g2, %g1
	subd    %g1, %g2, %g1
	subdcc  %g1, %g2, %g1
	vaddd32 %g2, %g4, %g6
        vsubd32 %g2, %g4, %g6
        vumuld32 %g2, %g4, %g6
        vsmuld32 %g2, %g4, %g6
	vaddd8  %g1, %g2, %g1
	vsubd8  %g1, %g2, %g1
	vumuld8  %g1, %g2, %g1
	vsmuld8  %g1, %g2, %g1
	adddcc  %g1, %g2, %g1
	subd    %g1, %g2, %g1
	subdcc  %g1, %g2, %g1
	vaddd8 %g2, %g4, %g6
        vsubd8 %g2, %g4, %g6
        vumuld8 %g2, %g4, %g6
        vsmuld8 %g2, %g4, %g6
# For the CSWAP  family of insns below we  have register indirect with
# even registers  for rs1 and rd,  and direct with  even registers for
# rs1 and rd; 0x1FFF = 13 bit immediate.
        cswap   [%g2 + %g1   ] 0x08, %g4
        cswap   [%g2 + 0x0fff]     , %g4
        cswapa  [%g2 + %g1   ] 0x0A, %g4
        cswapa  [%g2 + 0x0fff]     , %g4
	cswap   [%fp + -8]         , %g4
	adddcc  %g1, %g2, %g1
	subd    %g1, %g2, %g1
	subdcc  %g1, %g2, %g1
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%g0, [%fp-4]
	mov	1, %g1
	st	%g1, [%fp-8]
	st	%g0, [%fp-12]
	ld	[%fp+68], %g1
	cmp	%g1, 1
	ble	.L2
	 nop
	b	.L3
	 nop
.L4:
	ld	[%fp-8], %g1
	sll	%g1, 2, %g1
	ld	[%fp+72], %g2
	add	%g2, %g1, %g1
	ld	[%g1], %g1
	mov	%g1, %o0
	call	atoi, 0
	 nop
	st	%o0, [%fp-16]
	sethi	%hi(head), %g1
	or	%g1, %lo(head), %g1
	ld	[%g1], %g1
	ld	[%fp-16], %o0
	mov	%g1, %o1
	call	cons, 0
	 nop
	mov	%o0, %g2
	sethi	%hi(head), %g1
	or	%g1, %lo(head), %g1
	st	%g2, [%g1]
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
.L3:
	ld	[%fp-8], %g2
	ld	[%fp+68], %g1
	cmp	%g2, %g1
	bl	.L4
	 nop
	sethi	%hi(head), %g1
	or	%g1, %lo(head), %g1
	ld	[%g1], %g1
	mov	%g1, %o0
	call	llrec, 0
	 nop
	mov	%o0, %g2
	sethi	%hi(lst_len), %g1
	or	%g1, %lo(lst_len), %g1
	st	%g2, [%g1]
	sethi	%hi(lst_len), %g1
	or	%g1, %lo(lst_len), %g1
	ld	[%g1], %g1
	sethi	%hi(.LC0), %g2
	or	%g2, %lo(.LC0), %o0
	mov	%g1, %o1
	call	printf, 0
	 nop
	sethi	%hi(head), %g1
	or	%g1, %lo(head), %g1
	ld	[%g1], %g1
	st	%g1, [%fp-12]
	b	.L5
	 nop
.L7:
	ld	[%fp-12], %o0
	call	car, 0
	 nop
	st	%o0, [%fp-20]
	sethi	%hi(counter), %g1
	or	%g1, %lo(counter), %g1
	ld	[%g1], %g1
	add	%g1, 1, %g1
	sethi	%hi(.LC1), %g2
	or	%g2, %lo(.LC1), %o0
	mov	%g1, %o1
	ld	[%fp-20], %o2
	call	printf, 0
	 nop
	ld	[%fp-12], %o0
	call	cdr, 0
	 nop
	st	%o0, [%fp-12]
	sethi	%hi(counter), %g1
	or	%g1, %lo(counter), %g1
	ld	[%g1], %g1
	add	%g1, 1, %g2
	sethi	%hi(counter), %g1
	or	%g1, %lo(counter), %g1
	st	%g2, [%g1]
.L5:
	ld	[%fp-12], %g1
	cmp	%g1, 0
	be	.L6
	 nop
	sethi	%hi(counter), %g1
	or	%g1, %lo(counter), %g1
	ld	[%g1], %g2
	sethi	%hi(lst_len), %g1
	or	%g1, %lo(lst_len), %g1
	ld	[%g1], %g1
	cmp	%g2, %g1
	bl	.L7
	 nop
	b	.L6
	 nop
.L2:
	mov	-1, %g1
	st	%g1, [%fp-4]
.L6:
	ld	[%fp-4], %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	main, .-main
	.align 4
	.global cons
	.type	cons, #function
	.proc	0110
cons:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%g0, [%fp-4]
	mov	1, %o0
	mov	8, %o1
	call	calloc, 0
	 nop
	mov	%o0, %g1
	st	%g1, [%fp-4]
	ld	[%fp-4], %g1
	cmp	%g1, 0
	be	.L10
	 nop
	ld	[%fp-4], %g1
	ld	[%fp+68], %g2
	st	%g2, [%g1]
	ld	[%fp-4], %g1
	ld	[%fp+72], %g2
	st	%g2, [%g1+4]
	b	.L11
	 nop
.L10:
	st	%g0, [%fp-4]
.L11:
	ld	[%fp-4], %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	cons, .-cons
	.align 4
	.global car
	.type	car, #function
	.proc	04
car:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
	cmp	%g1, 0
	be	.L14
	 nop
	ld	[%fp+68], %g1
	ld	[%g1], %g1
	b	.L15
	 nop
.L14:
	mov	-1, %g1
.L15:
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	car, .-car
	.align 4
	.global cdr
	.type	cdr, #function
	.proc	0110
cdr:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
	cmp	%g1, 0
	be	.L18
	 nop
	ld	[%fp+68], %g1
	ld	[%g1+4], %g1
	b	.L19
	 nop
.L18:
	mov	0, %g1
.L19:
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	cdr, .-cdr
	.align 4
	.global ll
	.type	ll, #function
	.proc	04
ll:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
	st	%g1, [%fp-4]
	st	%g0, [%fp-8]
	b	.L22
	 nop
.L23:
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
	ld	[%fp-4], %o0
	call	cdr, 0
	 nop
	st	%o0, [%fp-4]
.L22:
	ld	[%fp-4], %g1
	cmp	%g1, 0
	bne	.L23
	 nop
	ld	[%fp-8], %g1
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	ll, .-ll
	.align 4
	.global llrec
	.type	llrec, #function
	.proc	04
llrec:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
	st	%g1, [%fp-4]
	ld	[%fp-4], %g1
	cmp	%g1, 0
	bne	.L26
	 nop
	mov	0, %g1
	b	.L27
	 nop
.L26:
	ld	[%fp-4], %o0
	call	cdr, 0
	 nop
	mov	%o0, %g1
	mov	%g1, %o0
	call	llrec, 0
	 nop
	mov	%o0, %g1
	add	%g1, 1, %g1
.L27:
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	llrec, .-llrec
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
