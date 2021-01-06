	.file	"dhry_2.c"
	.section	".text"
	.align 4
	.global Proc_6
	.type	Proc_6, #function
	.proc	020
Proc_6:
	save	%sp, -96, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	ld	[%fp+72], %g1
	ld	[%fp+68], %g2
	st	%g2, [%g1]
	ld	[%fp+68], %o0
	call	Func_3, 0
	 nop
	mov	%o0, %g1
	cmp	%g1, 0
	bne	.L2
	 nop
	ld	[%fp+72], %g1
	mov	3, %g2
	st	%g2, [%g1]
.L2:
	ld	[%fp+68], %g1
	cmp	%g1, 4
	bgu	.L1
	 nop
	ld	[%fp+68], %g1
	sll	%g1, 2, %g2
	sethi	%hi(.L9), %g1
	or	%g1, %lo(.L9), %g1
	ld	[%g2+%g1], %g1
	jmp	%g1
	 nop
	.section	".rodata"
	.section	".text"
.L4:
	ld	[%fp+72], %g1
	st	%g0, [%g1]
	b	.L1
	 nop
.L5:
	sethi	%hi(Int_Glob), %g1
	or	%g1, %lo(Int_Glob), %g1
	ld	[%g1], %g1
	cmp	%g1, 100
	ble	.L10
	 nop
	ld	[%fp+72], %g1
	st	%g0, [%g1]
	b	.L1
	 nop
.L10:
	ld	[%fp+72], %g1
	mov	3, %g2
	st	%g2, [%g1]
	b	.L1
	 nop
.L6:
	ld	[%fp+72], %g1
	mov	1, %g2
	st	%g2, [%g1]
	b	.L1
	 nop
.L8:
	ld	[%fp+72], %g1
	mov	2, %g2
	st	%g2, [%g1]
	nop
	b	.L1
	 nop
.L12:
	nop
.L1:
	restore
	jmp	%o7+8
	 nop
	.align 4
	.subsection	-1
	.align 4
.L9:
	.word	.L4
	.word	.L5
	.word	.L6
	.word	.L12
	.word	.L8
	.previous
	.size	Proc_6, .-Proc_6
	.align 4
	.global Proc_7
	.type	Proc_7, #function
	.proc	020
Proc_7:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	ld	[%fp+68], %g1
	add	%g1, 2, %g1
	st	%g1, [%fp-4]
	ld	[%fp+72], %g2
	ld	[%fp-4], %g1
	add	%g2, %g1, %g2
	ld	[%fp+76], %g1
	st	%g2, [%g1]
	restore
	jmp	%o7+8
	 nop
	.size	Proc_7, .-Proc_7
	.align 4
	.global Proc_8
	.type	Proc_8, #function
	.proc	020
Proc_8:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	ld	[%fp+76], %g1
	add	%g1, 5, %g1
	st	%g1, [%fp-8]
	ld	[%fp-8], %g1
	sll	%g1, 2, %g1
	ld	[%fp+68], %g2
	add	%g2, %g1, %g1
	ld	[%fp+80], %g2
	st	%g2, [%g1]
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	sll	%g1, 2, %g1
	ld	[%fp+68], %g2
	add	%g2, %g1, %g1
	ld	[%fp-8], %g2
	sll	%g2, 2, %g2
	ld	[%fp+68], %g3
	add	%g3, %g2, %g2
	ld	[%g2], %g2
	st	%g2, [%g1]
	ld	[%fp-8], %g1
	add	%g1, 30, %g1
	sll	%g1, 2, %g1
	ld	[%fp+68], %g2
	add	%g2, %g1, %g1
	ld	[%fp-8], %g2
	st	%g2, [%g1]
	ld	[%fp-8], %g1
	st	%g1, [%fp-4]
	b	.L15
	 nop
.L16:
	ld	[%fp-8], %g1
	smul	%g1, 200, %g1
	ld	[%fp+72], %g2
	add	%g2, %g1, %g2
	ld	[%fp-4], %g1
	sll	%g1, 2, %g1
	ld	[%fp-8], %g3
	st	%g3, [%g2+%g1]
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L15:
	ld	[%fp-8], %g1
	add	%g1, 1, %g2
	ld	[%fp-4], %g1
	cmp	%g2, %g1
	bge	.L16
	 nop
	ld	[%fp-8], %g1
	smul	%g1, 200, %g1
	ld	[%fp+72], %g2
	add	%g2, %g1, %g2
	ld	[%fp-8], %g1
	add	%g1, -1, %g1
	ld	[%fp-8], %g3
	smul	%g3, 200, %g3
	ld	[%fp+72], %g4
	add	%g4, %g3, %g4
	ld	[%fp-8], %g3
	add	%g3, -1, %g3
	sll	%g3, 2, %g3
	ld	[%g4+%g3], %g3
	add	%g3, 1, %g3
	sll	%g1, 2, %g1
	st	%g3, [%g2+%g1]
	ld	[%fp-8], %g1
	smul	%g1, 200, %g1
	add	%g1, 4000, %g1
	ld	[%fp+72], %g2
	add	%g2, %g1, %g2
	ld	[%fp-8], %g1
	sll	%g1, 2, %g1
	ld	[%fp+68], %g3
	add	%g3, %g1, %g1
	ld	[%g1], %g3
	ld	[%fp-8], %g1
	sll	%g1, 2, %g1
	st	%g3, [%g2+%g1]
	sethi	%hi(Int_Glob), %g1
	or	%g1, %lo(Int_Glob), %g1
	mov	5, %g2
	st	%g2, [%g1]
	restore
	jmp	%o7+8
	 nop
	.size	Proc_8, .-Proc_8
	.align 4
	.global Func_1
	.type	Func_1, #function
	.proc	012
Func_1:
	save	%sp, -104, %sp
	mov	%i0, %g2
	mov	%i1, %g1
	stb	%g2, [%fp+68]
	stb	%g1, [%fp+72]
	ldub	[%fp+68], %g1
	stb	%g1, [%fp-1]
	ldub	[%fp-1], %g1
	stb	%g1, [%fp-2]
	ldub	[%fp-2], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g2
	ldub	[%fp+72], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g2, %g1
	be	.L18
	 nop
	mov	0, %g1
	b	.L19
	 nop
.L18:
	sethi	%hi(Ch_1_Glob), %g1
	or	%g1, %lo(Ch_1_Glob), %g1
	ldub	[%fp-1], %g2
	stb	%g2, [%g1]
	mov	1, %g1
.L19:
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	Func_1, .-Func_1
	.align 4
	.global Func_2
	.type	Func_2, #function
	.proc	04
Func_2:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	mov	2, %g1
	st	%g1, [%fp-4]
	b	.L21
	 nop
.L22:
	ld	[%fp-4], %g1
	ld	[%fp+68], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g2
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	ld	[%fp+72], %g3
	add	%g3, %g1, %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	mov	%g2, %o0
	mov	%g1, %o1
	call	Func_1, 0
	 nop
	mov	%o0, %g1
	cmp	%g1, 0
	bne	.L21
	 nop
	mov	65, %g1
	stb	%g1, [%fp-5]
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L21:
	ld	[%fp-4], %g1
	cmp	%g1, 2
	ble	.L22
	 nop
	ldub	[%fp-5], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 86
	ble	.L23
	 nop
	ldub	[%fp-5], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 89
	bg	.L23
	 nop
	mov	7, %g1
	st	%g1, [%fp-4]
.L23:
	ldub	[%fp-5], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 82
	bne	.L24
	 nop
	mov	1, %g1
	b	.L25
	 nop
.L24:
	ld	[%fp+68], %o0
	ld	[%fp+72], %o1
	call	__strcmp, 0
	 nop
	mov	%o0, %g1
	cmp	%g1, 0
	ble	.L26
	 nop
	ld	[%fp-4], %g1
	add	%g1, 7, %g1
	st	%g1, [%fp-4]
	sethi	%hi(Int_Glob), %g1
	or	%g1, %lo(Int_Glob), %g1
	ld	[%fp-4], %g2
	st	%g2, [%g1]
	mov	1, %g1
	b	.L25
	 nop
.L26:
	mov	0, %g1
.L25:
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	Func_2, .-Func_2
	.align 4
	.global Func_3
	.type	Func_3, #function
	.proc	04
Func_3:
	save	%sp, -104, %sp
	st	%i0, [%fp+68]
	ld	[%fp+68], %g1
	st	%g1, [%fp-4]
	ld	[%fp-4], %g1
	cmp	%g1, 2
	bne	.L28
	 nop
	mov	1, %g1
	b	.L29
	 nop
.L28:
	mov	0, %g1
.L29:
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.size	Func_3, .-Func_3
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
