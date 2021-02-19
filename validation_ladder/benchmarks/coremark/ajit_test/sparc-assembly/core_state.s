	.file	"core_state.c"
	.section	".text"
	.align 4
	.global core_init_state
	.type	core_init_state, #function
	.proc	020
core_init_state:
	save	%sp, -96, %sp
	mov	0, %g4
	add	%i0, -1, %o3
	mov	0, %i3
	mov	0, %i5
	mov	44, %o1
	sethi	%hi(intpat), %l2
	sethi	%hi(.L13), %o2
	sethi	%hi(errpat), %l1
	sethi	%hi(scipat), %l0
	sethi	%hi(floatpat), %o0
.L45:
	add	%i5, %i3, %o4
	add	%o4, 1, %o5
	cmp	%o3, %o5
	bleu	.L50
	 cmp	%i0, %i5
.L15:
	cmp	%i3, 0
	be,a	.L51
	 add	%i1, 1, %i1
	add	%i2, %i5, %i5
	add	%i5, 4, %g1
	cmp	%g4, %g1
	add	%g4, 4, %g1
	subx	%g0, -1, %g3
	cmp	%i5, %g1
	subx	%g0, -1, %g2
	srl	%i3, 2, %o7
	or	%g3, %g2, %g3
	sll	%o7, 2, %g1
	cmp	%i3, 3
	bgu	.L5
	 mov	1, %g2
	mov	0, %g2
.L5:
	or	%i5, %g4, %i4
	and	%i4, 3, %i4
	subcc	%g0, %i4, %g0
	and	%g3, %g2, %g2
	subx	%g0, -1, %g3
	andcc	%g2, %g3, %g0
	be	.L27
	 cmp	%g1, 0
	be	.L27
	 mov	0, %g2
	mov	0, %g3
.L6:
	ld	[%g4+%g2], %i4
	st	%i4, [%i5+%g2]
	add	%g3, 1, %g3
	cmp	%o7, %g3
	bgu	.L6
	 add	%g2, 4, %g2
	cmp	%i3, %g1
	be,a	.L52
	 stb	%o1, [%i2+%o4]
.L36:
	ldub	[%g4+%g1], %g2
.L53:
	stb	%g2, [%i5+%g1]
	add	%g1, 1, %g1
	cmp	%i3, %g1
	bgu,a	.L53
	 ldub	[%g4+%g1], %g2
	stb	%o1, [%i2+%o4]
.L52:
	mov	%o5, %i5
	add	%i1, 1, %i1
.L51:
	sll	%i1, 16, %g2
	sra	%g2, 16, %i1
	and	%i1, 7, %g1
	add	%g1, -3, %g1
	sll	%g1, 16, %g1
	srl	%g1, 16, %g1
	cmp	%g1, 4
	bleu,a	.L48
	 or	%o2, %lo(.L13), %g2
	or	%l2, %lo(intpat), %g1
	srl	%g2, 17, %g2
	mov	4, %i3
	and	%g2, 12, %g2
	add	%i5, %i3, %o4
	add	%o4, 1, %o5
	cmp	%o3, %o5
	bgu	.L15
	 ld	[%g1+%g2], %g4
	cmp	%i0, %i5
.L50:
	bleu	.L57
	 mov	%i5, %g3
	sub	%i0, %i5, %g4
	add	%i2, %i5, %i3
	sub	%g0, %i3, %g2
	and	%g2, 3, %g2
	cmp	%g2, %g4
	bgu	.L49
	 xnor	%g0, %i5, %g1
.L17:
	add	%i0, %g1, %g1
	add	%g1, 1, %g1
	cmp	%g1, 3
	bleu,a	.L18
	 mov	%g1, %g2
.L18:
	cmp	%g2, 0
	be,a	.L54
	 sub	%g4, %g2, %g4
	stb	%g0, [%i2+%i5]
.L55:
	add	%i5, 1, %i5
	sub	%i5, %g3, %g1
	cmp	%g2, %g1
	bgu,a	.L55
	 stb	%g0, [%i2+%i5]
	cmp	%g4, %g2
	be	.L57
	 sub	%g4, %g2, %g4
.L54:
	srl	%g4, 2, %g3
	sll	%g3, 2, %i4
	cmp	%i4, 0
	be,a	.L56
	 stb	%g0, [%i2+%i5]
	add	%i3, %g2, %g2
	mov	0, %g1
.L23:
	st	%g0, [%g2]
	add	%g1, 1, %g1
	cmp	%g1, %g3
	blu	.L23
	 add	%g2, 4, %g2
	cmp	%g4, %i4
	be	.L57
	 add	%i5, %i4, %i5
	stb	%g0, [%i2+%i5]
.L56:
	add	%i5, 1, %i5
	cmp	%i0, %i5
	bgu,a	.L56
	 stb	%g0, [%i2+%i5]
.L57:
	jmp	%i7+8
	 restore
.L48:
	sll	%g1, 2, %g1
	ld	[%g2+%g1], %g1
	jmp	%g1
	 nop
	.section	".rodata"
	.section	".text"
.L10:
	or	%o0, %lo(floatpat), %g2
	srl	%i1, 1, %g1
	mov	8, %i3
	and	%g1, 12, %g1
	b	.L45
	 ld	[%g2+%g1], %g4
.L11:
	or	%l0, %lo(scipat), %g2
	srl	%i1, 1, %g1
	mov	8, %i3
	and	%g1, 12, %g1
	b	.L45
	 ld	[%g2+%g1], %g4
.L12:
	or	%l1, %lo(errpat), %g2
	srl	%i1, 1, %g1
	mov	8, %i3
	and	%g1, 12, %g1
	b	.L45
	 ld	[%g2+%g1], %g4
.L49:
	b	.L17
	 mov	%g4, %g2
.L27:
	b	.L36
	 mov	0, %g1
	.align 4
	.subsection	-1
	.align 4
.L13:
	.word	.L10
	.word	.L10
	.word	.L11
	.word	.L11
	.word	.L12
	.previous
	.size	core_init_state, .-core_init_state
	.align 4
	.global core_state_transition
	.type	core_state_transition, #function
	.proc	012
core_state_transition:
	ld	[%o0], %o5
	ldub	[%o5], %g1
	andcc	%g1, 0xff, %g4
	be	.L94
	 mov	%o0, %o2
	cmp	%g4, 44
	be	.L114
	 add	%o5, 1, %g2
	mov	%o5, %g3
	mov	0, %o0
	sethi	%hi(.L71), %o3
.L102:
	or	%o3, %lo(.L71), %o4
	sll	%o0, 2, %o5
	ld	[%o4+%o5], %o5
	jmp	%o5
	 nop
	.section	".rodata"
	.section	".text"
.L64:
	add	%g1, -48, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 9
	bleu	.L72
	 mov	4, %o0
	cmp	%g4, 45
	be,a	.L120
	 ld	[%o1], %g1
	cmp	%g4, 43
	be,a	.L98
	 ld	[%o1], %g1
	cmp	%g4, 46
	be	.L72
	 mov	5, %o0
	ld	[%o1+4], %g1
	mov	1, %o0
	add	%g1, 1, %g1
	st	%g1, [%o1+4]
.L72:
	ld	[%o1], %g1
	add	%g1, 1, %g1
	st	%g1, [%o1]
.L63:
	ldub	[%g3+1], %g1
	andcc	%g1, 0xff, %g4
	be	.L59
	 mov	%g2, %o5
	cmp	%o0, 1
	be,a	.L121
	 mov	1, %o0
.L88:
	add	%g2, 1, %g2
	cmp	%g4, 44
	bne	.L102
	 add	%g3, 1, %g3
	add	%o5, 1, %o5
.L59:
	jmp	%o7+8
	 st	%o5, [%o2]
.L70:
	add	%g1, -48, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 9
	bgu,a	.L115
	 ld	[%o1+4], %g1
.L76:
	ldub	[%g3+1], %g1
.L122:
	andcc	%g1, 0xff, %g4
	bne	.L88
	 mov	%g2, %o5
	b,a	.L59
.L69:
	add	%g1, -48, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 9
	bgu	.L116
	 ld	[%o1+24], %g1
	mov	7, %o0
	add	%g1, 1, %g1
	b	.L76
	 st	%g1, [%o1+24]
.L68:
	and	%g1, 223, %g4
	cmp	%g4, 69
	bne	.L80
	 add	%g1, -48, %g1
	ld	[%o1+20], %g1
	mov	3, %o0
	add	%g1, 1, %g1
	b	.L76
	 st	%g1, [%o1+20]
.L67:
	cmp	%g4, 46
	be	.L117
	 add	%g1, -48, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 9
	bleu,a	.L122
	 ldub	[%g3+1], %g1
	ld	[%o1+16], %g1
	add	%g1, 1, %g1
	b	.L77
	 st	%g1, [%o1+16]
.L65:
	add	%g1, -48, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 9
	bgu	.L118
	 cmp	%g4, 46
	ld	[%o1+8], %g1
	mov	4, %o0
	add	%g1, 1, %g1
	b	.L76
	 st	%g1, [%o1+8]
.L66:
	cmp	%g4, 45
	be	.L99
	 ld	[%o1+12], %g1
	cmp	%g4, 43
	be	.L123
	 add	%g1, 1, %g1
	st	%g1, [%o1+12]
.L77:
	mov	%g2, %o5
	mov	1, %o0
.L121:
	jmp	%o7+8
	 st	%o5, [%o2]
.L99:
	add	%g1, 1, %g1
.L123:
	mov	6, %o0
	b	.L76
	 st	%g1, [%o1+12]
.L80:
	and	%g1, 0xff, %g1
	cmp	%g1, 9
	bleu,a	.L122
	 ldub	[%g3+1], %g1
	ld	[%o1+20], %g1
	add	%g1, 1, %g1
	b	.L77
	 st	%g1, [%o1+20]
.L118:
	be	.L119
	 ld	[%o1+8], %g1
	add	%g1, 1, %g1
	b	.L77
	 st	%g1, [%o1+8]
.L115:
	add	%g1, 1, %g1
	b	.L77
	 st	%g1, [%o1+4]
.L116:
	add	%g1, 1, %g1
	b	.L77
	 st	%g1, [%o1+24]
.L98:
.L120:
	mov	2, %o0
	add	%g1, 1, %g1
	b	.L63
	 st	%g1, [%o1]
.L117:
	ld	[%o1+16], %g1
	mov	5, %o0
	add	%g1, 1, %g1
	b	.L76
	 st	%g1, [%o1+16]
.L119:
	mov	5, %o0
	add	%g1, 1, %g1
	b	.L76
	 st	%g1, [%o1+8]
.L94:
	b	.L59
	 mov	0, %o0
.L114:
	mov	0, %o0
	b	.L59
	 add	%o5, 1, %o5
	.align 4
	.subsection	-1
	.align 4
.L71:
	.word	.L64
	.word	.L63
	.word	.L65
	.word	.L66
	.word	.L67
	.word	.L68
	.word	.L69
	.word	.L70
	.previous
	.size	core_state_transition, .-core_state_transition
	.align 4
	.global core_bench_state
	.type	core_bench_state, #function
	.proc	015
core_bench_state:
	save	%sp, -168, %sp
	st	%g0, [%fp-32]
	st	%g0, [%fp-28]
	st	%g0, [%fp-24]
	st	%g0, [%fp-20]
	st	%g0, [%fp-16]
	st	%g0, [%fp-12]
	st	%g0, [%fp-8]
	st	%g0, [%fp-4]
	st	%g0, [%fp-64]
	st	%g0, [%fp-60]
	st	%g0, [%fp-56]
	st	%g0, [%fp-52]
	st	%g0, [%fp-48]
	st	%g0, [%fp-44]
	st	%g0, [%fp-40]
	st	%g0, [%fp-36]
	ldub	[%i1], %g1
	cmp	%g1, 0
	be	.L125
	 mov	0, %g2
	st	%i1, [%fp-68]
	add	%fp, -68, %l0
	mov	%l0, %o0
.L152:
	call	core_state_transition, 0
	 add	%fp, -32, %o1
	sll	%o0, 2, %o0
	add	%fp, %o0, %g1
	ld	[%g1-64], %g2
	add	%g2, 1, %g2
	st	%g2, [%g1-64]
	ld	[%fp-68], %g1
	ldub	[%g1], %g1
	cmp	%g1, 0
	bne	.L152
	 mov	%l0, %o0
	ldub	[%i1], %g2
.L125:
	add	%i1, %i0, %i0
	cmp	%i1, %i0
	bgeu	.L153
	 andcc	%g2, 0xff, %g0
	st	%i1, [%fp-68]
	b	.L130
	 mov	%i1, %g1
.L150:
	ldub	[%g1], %g2
.L130:
	and	%g2, 0xff, %g3
	cmp	%g3, 44
	be	.L128
	 xor	%g2, %i2, %g2
	stb	%g2, [%g1]
	ld	[%fp-68], %g1
.L128:
	add	%g1, %i4, %g1
	cmp	%g1, %i0
	blu,a	.L150
	 st	%g1, [%fp-68]
	ldub	[%i1], %g2
	andcc	%g2, 0xff, %g0
.L153:
	be	.L154
	 cmp	%i1, %i0
	st	%i1, [%fp-68]
	add	%fp, -68, %l0
	mov	%l0, %o0
.L155:
	call	core_state_transition, 0
	 add	%fp, -32, %o1
	sll	%o0, 2, %o0
	add	%fp, %o0, %g1
	ld	[%g1-64], %g2
	add	%g2, 1, %g2
	st	%g2, [%g1-64]
	ld	[%fp-68], %g1
	ldub	[%g1], %g1
	cmp	%g1, 0
	bne	.L155
	 mov	%l0, %o0
	cmp	%i1, %i0
.L154:
	bgeu	.L151
	 st	%i1, [%fp-68]
.L143:
	ldub	[%i1], %g1
	and	%g1, 0xff, %g2
	cmp	%g2, 44
	be	.L135
	 xor	%g1, %i3, %g1
	stb	%g1, [%i1]
	ld	[%fp-68], %i1
.L135:
	add	%i1, %i4, %i1
	cmp	%i1, %i0
	blu	.L143
	 st	%i1, [%fp-68]
.L151:
	mov	%i5, %o1
	call	crcu32, 0
	 ld	[%fp-64], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-32], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-60], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-28], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-56], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-24], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-52], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-20], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-48], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-16], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-44], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-12], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-40], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-8], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-36], %o0
	mov	%o0, %o1
	call	crcu32, 0
	 ld	[%fp-4], %o0
	jmp	%i7+8
	 restore %g0, %o0, %o0
	.size	core_bench_state, .-core_bench_state
	.global errpat
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"T0.3e-1F"
	.align 8
.LC1:
	.asciz	"-T.T++Tq"
	.align 8
.LC2:
	.asciz	"1T3.4e4z"
	.align 8
.LC3:
	.asciz	"34.0e-T^"
	.section	".data"
	.align 4
	.type	errpat, #object
	.size	errpat, 16
errpat:
	.long	.LC0
	.long	.LC1
	.long	.LC2
	.long	.LC3
	.global scipat
	.section	.rodata.str1.8
	.align 8
.LC4:
	.asciz	"5.500e+3"
	.align 8
.LC5:
	.asciz	"-.123e-2"
	.align 8
.LC6:
	.asciz	"-87e+832"
	.align 8
.LC7:
	.asciz	"+0.6e-12"
	.section	".data"
	.align 4
	.type	scipat, #object
	.size	scipat, 16
scipat:
	.long	.LC4
	.long	.LC5
	.long	.LC6
	.long	.LC7
	.global floatpat
	.section	.rodata.str1.8
	.align 8
.LC8:
	.asciz	"35.54400"
	.align 8
.LC9:
	.asciz	".1234500"
	.align 8
.LC10:
	.asciz	"-110.700"
	.align 8
.LC11:
	.asciz	"+0.64400"
	.section	".data"
	.align 4
	.type	floatpat, #object
	.size	floatpat, 16
floatpat:
	.long	.LC8
	.long	.LC9
	.long	.LC10
	.long	.LC11
	.global intpat
	.section	.rodata.str1.8
	.align 8
.LC12:
	.asciz	"5012"
	.align 8
.LC13:
	.asciz	"1234"
	.align 8
.LC14:
	.asciz	"-874"
	.align 8
.LC15:
	.asciz	"+122"
	.section	".data"
	.align 4
	.type	intpat, #object
	.size	intpat, 16
intpat:
	.long	.LC12
	.long	.LC13
	.long	.LC14
	.long	.LC15
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
