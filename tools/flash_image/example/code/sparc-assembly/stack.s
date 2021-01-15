	.file	"stack.c"
	.section	".text"
	.align 4
	.global initStack
	.type	initStack, #function
	.proc	020
initStack:
	mov	-1, %g1
	jmp	%o7+8
	 st	%g1, [%o0+40]
	.size	initStack, .-initStack
	.align 4
	.global isEmpty
	.type	isEmpty, #function
	.proc	04
isEmpty:
	ld	[%o0+40], %g1
	xnor	%g0, %g1, %g1
	subcc	%g0, %g1, %g0
	jmp	%o7+8
	 subx	%g0, -1, %o0
	.size	isEmpty, .-isEmpty
	.align 4
	.global isFull
	.type	isFull, #function
	.proc	04
isFull:
	ld	[%o0+40], %g1
	xor	%g1, 9, %g1
	subcc	%g0, %g1, %g0
	jmp	%o7+8
	 subx	%g0, -1, %o0
	.size	isFull, .-isFull
	.align 4
	.global peek
	.type	peek, #function
	.proc	04
peek:
	jmp	%o7+8
	 ld	[%o0+40], %o0
	.size	peek, .-peek
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"Could not retrieve data, Stack is empty.\n"
	.section	".text"
	.align 4
	.global pop
	.type	pop, #function
	.proc	04
pop:
	save	%sp, -96, %sp
	ld	[%i0+40], %g2
	cmp	%g2, -1
	be	.L6
	 mov	%i0, %g1
	sll	%g2, 2, %g3
	add	%g2, -1, %g2
	ld	[%i0+%g3], %i0
	st	%g2, [%g1+40]
	jmp	%i7+8
	 restore
.L6:
	sethi	%hi(.LC0), %o0
	mov	-1, %i0
	call	ee_printf, 0
	 or	%o0, %lo(.LC0), %o0
	jmp	%i7+8
	 restore
	.size	pop, .-pop
	.section	.rodata.str1.8
	.align 8
.LC1:
	.asciz	"Could not insert data, Stack is full.\n"
	.section	".text"
	.align 4
	.global push
	.type	push, #function
	.proc	020
push:
	ld	[%o0+40], %g1
	cmp	%g1, 9
	be	.L12
	 add	%g1, 1, %g1
	sll	%g1, 2, %g2
	st	%g1, [%o0+40]
	jmp	%o7+8
	 st	%o1, [%o0+%g2]
.L12:
	sethi	%hi(.LC1), %o0
	or	%o0, %lo(.LC1), %o0
	or	%o7, %g0, %g1
	call	ee_printf, 0
	 or	%g1, %g0, %o7
	.size	push, .-push
	.section	.rodata.str1.8
	.align 8
.LC2:
	.asciz	"Stack is empty\n"
	.align 8
.LC3:
	.asciz	"\n The status of the stack is \n"
	.align 8
.LC4:
	.asciz	"\n"
	.align 8
.LC5:
	.asciz	"%d\n"
	.section	".text"
	.align 4
	.global display
	.type	display, #function
	.proc	020
display:
	save	%sp, -96, %sp
	ld	[%i0+40], %g1
	cmp	%g1, -1
	be	.L23
	 sethi	%hi(.LC3), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC3), %o0
	sethi	%hi(.LC5), %i4
	ld	[%i0+40], %i5
	or	%i4, %lo(.LC5), %i4
	sll	%i5, 2, %g1
	cmp	%i5, 0
	bl	.L20
	 add	%i0, %g1, %i0
.L21:
	ld	[%i0], %o1
	call	ee_printf, 0
	 mov	%i4, %o0
	add	%i5, -1, %i5
	cmp	%i5, -1
	bne	.L21
	 add	%i0, -4, %i0
.L20:
	sethi	%hi(.LC4), %i0
	call	ee_printf, 0
	 restore %i0, %lo(.LC4), %o0
.L23:
	sethi	%hi(.LC2), %i0
	call	ee_printf, 0
	 restore %i0, %lo(.LC2), %o0
	.size	display, .-display
	.ident	"GCC: (Buildroot 2014.08-gde406ae-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
