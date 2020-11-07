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
# For  SIMD 2  insns below,  we have  rs2 and  rd have  lowest  bit 0,
# i.e. they are even registers. The immediate mode of zbytedpos uses a
# value of 255 that fits into the 8 bits (0:7).
main:
	save	%sp, -120, %sp
        addbyter  %g2, %g1, %g4
        ordbyter  %g2, %g1, %g4
        anddbyter %g2, %g1, %g4
        xordbyter %g2, %g1, %g4
        zbytedpos %g2, %g1, %g4
        zbytedpos %g2, 255, %g4
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
