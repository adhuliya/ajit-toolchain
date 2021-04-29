	.file	"core_util.c"
	.section	".text"
	.align 4
	.global get_seed_32
	.type	get_seed_32, #function
	.proc	04
get_seed_32:
	cmp	%o0, 5
	bleu,a	.L11
	 sll	%o0, 2, %o0
.L9:
	jmp	%o7+8
	 mov	0, %o0
.L11:
	sethi	%hi(.L8), %g1
	or	%g1, %lo(.L8), %g1
	ld	[%g1+%o0], %g1
	jmp	%g1
	 nop
	.section	".rodata"
	.section	".text"
.L7:
	sethi	%hi(seed5_volatile), %g1
	ld	[%g1+%lo(seed5_volatile)], %o0
	jmp	%o7+8
	 nop
.L3:
	sethi	%hi(seed1_volatile), %g1
	ld	[%g1+%lo(seed1_volatile)], %o0
	jmp	%o7+8
	 nop
.L4:
	sethi	%hi(seed2_volatile), %g1
	ld	[%g1+%lo(seed2_volatile)], %o0
	jmp	%o7+8
	 nop
.L5:
	sethi	%hi(seed3_volatile), %g1
	ld	[%g1+%lo(seed3_volatile)], %o0
	jmp	%o7+8
	 nop
.L6:
	sethi	%hi(seed4_volatile), %g1
	ld	[%g1+%lo(seed4_volatile)], %o0
	jmp	%o7+8
	 nop
	.align 4
	.subsection	-1
	.align 4
.L8:
	.word	.L9
	.word	.L3
	.word	.L4
	.word	.L5
	.word	.L6
	.word	.L7
	.previous
	.size	get_seed_32, .-get_seed_32
	.align 4
	.global crcu8
	.type	crcu8, #function
	.proc	015
crcu8:
	xor	%o0, %o1, %g3
	sethi	%hi(16384), %o5
	sethi	%hi(32768), %g4
	or	%o5, 2, %o5
	srl	%o0, 1, %g2
	xor	%o1, %o5, %o5
	srl	%o1, 1, %g1
	srl	%o5, 1, %o5
	andcc	%g3, 1, %g0
	bne	.L29
	 or	%o5, %g4, %g4
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	bne	.L30
	 or	%g3, %o5, %g3
.L16:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	bne	.L31
	 or	%g3, %o5, %g3
.L18:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	bne	.L32
	 or	%g3, %o5, %g3
.L20:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	bne	.L33
	 or	%g3, %o5, %g3
.L22:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	bne	.L34
	 or	%g3, %o5, %g3
.L24:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	andcc	%g4, 1, %g0
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	bne	.L35
	 or	%g3, %o5, %g3
.L26:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	sll	%g1, 16, %g1
	srl	%g2, 1, %o5
	sethi	%hi(32768), %g3
	srl	%g1, 16, %g2
	srl	%g1, 17, %g1
	and	%g2, 1, %o4
	xor	%g2, %g4, %g2
	cmp	%o4, %o5
	srl	%g2, 1, %g4
	bne	.L36
	 or	%g4, %g3, %g3
.L28:
	sll	%g1, 16, %o0
	jmp	%o7+8
	 srl	%o0, 16, %o0
.L29:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g4, %g1
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	be	.L16
	 or	%g3, %o5, %g3
.L30:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g3, %g1
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	be	.L18
	 or	%g3, %o5, %g3
.L31:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g3, %g1
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	be	.L20
	 or	%g3, %o5, %g3
.L32:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g3, %g1
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	be	.L22
	 or	%g3, %o5, %g3
.L33:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g3, %g1
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	srl	%g2, 1, %g2
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	andcc	%g4, 1, %g0
	be	.L24
	 or	%g3, %o5, %g3
.L34:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g3, %g1
	sll	%g1, 16, %g1
	srl	%g1, 16, %g3
	srl	%g1, 17, %g1
	xor	%g2, %g3, %g4
	xor	%g3, %o5, %g3
	andcc	%g4, 1, %g0
	srl	%g3, 1, %g3
	sethi	%hi(32768), %o5
	be	.L26
	 or	%g3, %o5, %g3
.L35:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	mov	%g3, %g1
	srl	%g2, 1, %o5
	sll	%g1, 16, %g1
	sethi	%hi(32768), %g3
	srl	%g1, 16, %g2
	srl	%g1, 17, %g1
	and	%g2, 1, %o4
	xor	%g2, %g4, %g2
	cmp	%o4, %o5
	srl	%g2, 1, %g4
	be	.L28
	 or	%g4, %g3, %g3
.L36:
	mov	%g3, %g1
	sll	%g1, 16, %o0
	jmp	%o7+8
	 srl	%o0, 16, %o0
	.size	crcu8, .-crcu8
	.align 4
	.global crcu16
	.type	crcu16, #function
	.proc	015
crcu16:
	sethi	%hi(32768), %g2
	xor	%o0, %o1, %g1
	and	%o0, 0xff, %g4
	sethi	%hi(16384), %o5
	srl	%g4, 1, %g4
	or	%o5, 2, %o5
	mov	%g4, %g3
	xor	%o1, %o5, %o5
	andcc	%g1, 1, %g0
	srl	%o5, 1, %o5
	or	%o5, %g2, %o5
	bne	.L70
	 srl	%o1, 1, %g2
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L71
	 or	%g1, %o5, %g1
.L41:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L72
	 or	%g1, %o5, %g1
.L43:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L73
	 or	%g1, %o5, %g1
.L45:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L74
	 or	%g1, %o5, %g1
.L47:
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	bne	.L75
	 or	%g1, %g4, %g1
.L49:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	bne	.L76
	 or	%g1, %g4, %g1
.L51:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	sll	%g2, 16, %g2
	sethi	%hi(16384), %o5
	srl	%g2, 16, %g1
	or	%o5, 2, %o5
	and	%g1, 1, %g4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	bne	.L77
	 or	%g1, %g3, %g1
.L53:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	srl	%o0, 8, %o0
	srl	%g2, 16, %g1
	srl	%o0, 1, %g4
	srl	%g2, 17, %g2
	xor	%o0, %g1, %o0
	mov	%g4, %g3
	xor	%g1, %o5, %g1
	andcc	%o0, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	bne	.L78
	 or	%g1, %o5, %g1
.L55:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L79
	 or	%g1, %o5, %g1
.L57:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L80
	 or	%g1, %o5, %g1
.L59:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L81
	 or	%g1, %o5, %g1
.L61:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L82
	 or	%g1, %o5, %g1
.L63:
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	bne	.L83
	 or	%g1, %g4, %g1
.L65:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	bne	.L84
	 or	%g1, %g4, %g1
.L67:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	sll	%g2, 16, %g2
	sethi	%hi(16384), %o5
	srl	%g2, 16, %g1
	or	%o5, 2, %o5
	and	%g1, 1, %g4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	bne	.L85
	 or	%g1, %g3, %g1
.L69:
	sll	%g2, 16, %o0
	jmp	%o7+8
	 srl	%o0, 16, %o0
.L70:
	mov	%o5, %g2
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L41
	 or	%g1, %o5, %g1
.L71:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g4, 0xff, %g4
	sll	%g2, 16, %g2
	srl	%g4, 1, %g4
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L43
	 or	%g1, %o5, %g1
.L72:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g3, 0xff, %g3
	sll	%g2, 16, %g2
	srl	%g3, 1, %g3
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g4, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L45
	 or	%g1, %o5, %g1
.L73:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g4, 0xff, %g4
	sll	%g2, 16, %g2
	srl	%g4, 1, %g4
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L47
	 or	%g1, %o5, %g1
.L74:
	mov	%g1, %g2
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	be	.L49
	 or	%g1, %g4, %g1
.L75:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	mov	%g1, %g2
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	be	.L51
	 or	%g1, %g4, %g1
.L76:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	mov	%g1, %g2
	sethi	%hi(16384), %o5
	sll	%g2, 16, %g2
	or	%o5, 2, %o5
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	and	%g1, 1, %g4
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	be	.L53
	 or	%g1, %g3, %g1
.L77:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	srl	%o0, 8, %o0
	sll	%g2, 16, %g2
	srl	%o0, 1, %g4
	srl	%g2, 16, %g1
	mov	%g4, %g3
	xor	%o0, %g1, %o0
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	andcc	%o0, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	be	.L55
	 or	%g1, %o5, %g1
.L78:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g3, 0xff, %g3
	sll	%g2, 16, %g2
	srl	%g3, 1, %g3
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g4, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L57
	 or	%g1, %o5, %g1
.L79:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g4, 0xff, %g4
	sll	%g2, 16, %g2
	srl	%g4, 1, %g4
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L59
	 or	%g1, %o5, %g1
.L80:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g3, 0xff, %g3
	sll	%g2, 16, %g2
	srl	%g3, 1, %g3
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g4, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L61
	 or	%g1, %o5, %g1
.L81:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g4, 0xff, %g4
	sll	%g2, 16, %g2
	srl	%g4, 1, %g4
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L63
	 or	%g1, %o5, %g1
.L82:
	mov	%g1, %g2
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	be	.L65
	 or	%g1, %g4, %g1
.L83:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	mov	%g1, %g2
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	be	.L67
	 or	%g1, %g4, %g1
.L84:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	mov	%g1, %g2
	sethi	%hi(16384), %o5
	sll	%g2, 16, %g2
	or	%o5, 2, %o5
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	and	%g1, 1, %g4
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	be	.L69
	 or	%g1, %g3, %g1
.L85:
	mov	%g1, %g2
	sll	%g2, 16, %o0
	jmp	%o7+8
	 srl	%o0, 16, %o0
	.size	crcu16, .-crcu16
	.align 4
	.global crcu32
	.type	crcu32, #function
	.proc	015
crcu32:
	sethi	%hi(32768), %g2
	xor	%o0, %o1, %g1
	and	%o0, 0xff, %g4
	sethi	%hi(16384), %o5
	srl	%g4, 1, %g4
	or	%o5, 2, %o5
	mov	%g4, %g3
	xor	%o1, %o5, %o5
	andcc	%g1, 1, %g0
	srl	%o5, 1, %o5
	or	%o5, %g2, %o5
	bne	.L151
	 srl	%o1, 1, %g2
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L152
	 or	%g1, %o5, %g1
.L90:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L153
	 or	%g1, %o5, %g1
.L92:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L154
	 or	%g1, %o5, %g1
.L94:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L155
	 or	%g1, %o5, %g1
.L96:
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	bne	.L156
	 or	%g1, %g4, %g1
.L98:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	bne	.L157
	 or	%g1, %g4, %g1
.L100:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	sll	%g2, 16, %g2
	sethi	%hi(16384), %o5
	srl	%g2, 16, %g1
	or	%o5, 2, %o5
	and	%g1, 1, %g4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	bne	.L158
	 or	%g1, %g3, %g1
.L102:
	sethi	%hi(16384), %g3
	or	%g3, 2, %g3
	sll	%g2, 16, %g2
	sll	%o0, 16, %g4
	srl	%g2, 16, %g1
	srl	%g4, 24, %g4
	sethi	%hi(32768), %o4
	xor	%g4, %g1, %o5
	srl	%g2, 17, %g2
	xor	%g1, %g3, %g1
	srl	%g4, 1, %g4
	srl	%g1, 1, %g1
	mov	%g4, %g3
	andcc	%o5, 1, %g0
	bne	.L159
	 or	%g1, %o4, %g1
.L104:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L160
	 or	%g1, %o5, %g1
.L106:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L161
	 or	%g1, %o5, %g1
.L108:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L162
	 or	%g1, %o5, %g1
.L110:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L163
	 or	%g1, %o5, %g1
.L112:
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	bne	.L164
	 or	%g1, %g4, %g1
.L114:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	bne	.L165
	 or	%g1, %g4, %g1
.L116:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	sll	%g2, 16, %g2
	sethi	%hi(16384), %o5
	srl	%g2, 16, %g1
	or	%o5, 2, %o5
	and	%g1, 1, %g4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	bne	.L166
	 or	%g1, %g3, %g1
.L118:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	srl	%o0, 16, %o0
	srl	%g2, 16, %g1
	and	%o0, 0xff, %g4
	xor	%o0, %g1, %o4
	srl	%g4, 1, %g4
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	srl	%g2, 17, %g2
	andcc	%o4, 1, %g0
	bne	.L167
	 or	%g1, %o5, %g1
.L120:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L168
	 or	%g1, %o5, %g1
.L122:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L169
	 or	%g1, %o5, %g1
.L124:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L170
	 or	%g1, %o5, %g1
.L126:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L171
	 or	%g1, %o5, %g1
.L128:
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	bne	.L172
	 or	%g1, %g4, %g1
.L130:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	bne	.L173
	 or	%g1, %g4, %g1
.L132:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	sll	%g2, 16, %g2
	sethi	%hi(16384), %o5
	srl	%g2, 16, %g1
	or	%o5, 2, %o5
	and	%g1, 1, %g4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	bne	.L174
	 or	%g1, %g3, %g1
.L134:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	srl	%o0, 8, %o0
	srl	%g2, 16, %g1
	srl	%o0, 1, %g4
	srl	%g2, 17, %g2
	xor	%o0, %g1, %o0
	mov	%g4, %g3
	xor	%g1, %o5, %g1
	andcc	%o0, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	bne	.L175
	 or	%g1, %o5, %g1
.L136:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L176
	 or	%g1, %o5, %g1
.L138:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L177
	 or	%g1, %o5, %g1
.L140:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L178
	 or	%g1, %o5, %g1
.L142:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L179
	 or	%g1, %o5, %g1
.L144:
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	bne	.L180
	 or	%g1, %g4, %g1
.L146:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	bne	.L181
	 or	%g1, %g4, %g1
.L148:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	sll	%g2, 16, %g2
	sethi	%hi(16384), %o5
	srl	%g2, 16, %g1
	or	%o5, 2, %o5
	and	%g1, 1, %g4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	bne	.L182
	 or	%g1, %g3, %g1
	sll	%g2, 16, %o0
	jmp	%o7+8
	 srl	%o0, 16, %o0
.L151:
	mov	%o5, %g2
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L90
	 or	%g1, %o5, %g1
.L152:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g4, 0xff, %g4
	sll	%g2, 16, %g2
	srl	%g4, 1, %g4
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L92
	 or	%g1, %o5, %g1
.L153:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g3, 0xff, %g3
	sll	%g2, 16, %g2
	srl	%g3, 1, %g3
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g4, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L94
	 or	%g1, %o5, %g1
.L154:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g4, 0xff, %g4
	sll	%g2, 16, %g2
	srl	%g4, 1, %g4
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L96
	 or	%g1, %o5, %g1
.L155:
	mov	%g1, %g2
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	be	.L98
	 or	%g1, %g4, %g1
.L156:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	mov	%g1, %g2
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	be	.L100
	 or	%g1, %g4, %g1
.L157:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	mov	%g1, %g2
	sethi	%hi(16384), %o5
	sll	%g2, 16, %g2
	or	%o5, 2, %o5
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	and	%g1, 1, %g4
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	be	.L102
	 or	%g1, %g3, %g1
.L158:
	b	.L102
	 mov	%g1, %g2
.L182:
	mov	%g1, %g2
	sll	%g2, 16, %o0
	jmp	%o7+8
	 srl	%o0, 16, %o0
.L181:
	b	.L148
	 mov	%g1, %g2
.L180:
	b	.L146
	 mov	%g1, %g2
.L179:
	b	.L144
	 mov	%g1, %g2
.L178:
	b	.L142
	 mov	%g1, %g2
.L177:
	b	.L140
	 mov	%g1, %g2
.L176:
	b	.L138
	 mov	%g1, %g2
.L175:
	b	.L136
	 mov	%g1, %g2
.L174:
	b	.L134
	 mov	%g1, %g2
.L173:
	b	.L132
	 mov	%g1, %g2
.L172:
	b	.L130
	 mov	%g1, %g2
.L171:
	b	.L128
	 mov	%g1, %g2
.L170:
	b	.L126
	 mov	%g1, %g2
.L169:
	b	.L124
	 mov	%g1, %g2
.L168:
	b	.L122
	 mov	%g1, %g2
.L167:
	b	.L120
	 mov	%g1, %g2
.L166:
	b	.L118
	 mov	%g1, %g2
.L165:
	b	.L116
	 mov	%g1, %g2
.L164:
	b	.L114
	 mov	%g1, %g2
.L163:
	b	.L112
	 mov	%g1, %g2
.L162:
	b	.L110
	 mov	%g1, %g2
.L161:
	b	.L108
	 mov	%g1, %g2
.L160:
	b	.L106
	 mov	%g1, %g2
.L159:
	b	.L104
	 mov	%g1, %g2
	.size	crcu32, .-crcu32
	.align 4
	.global crc16
	.type	crc16, #function
	.proc	015
crc16:
	sethi	%hi(32768), %g2
	xor	%o0, %o1, %g1
	and	%o0, 0xff, %g4
	sethi	%hi(16384), %o5
	srl	%g4, 1, %g4
	or	%o5, 2, %o5
	mov	%g4, %g3
	xor	%o1, %o5, %o5
	andcc	%g1, 1, %g0
	srl	%o5, 1, %o5
	or	%o5, %g2, %o5
	bne	.L216
	 srl	%o1, 1, %g2
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L217
	 or	%g1, %o5, %g1
.L187:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L218
	 or	%g1, %o5, %g1
.L189:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L219
	 or	%g1, %o5, %g1
.L191:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L220
	 or	%g1, %o5, %g1
.L193:
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	bne	.L221
	 or	%g1, %g4, %g1
.L195:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	bne	.L222
	 or	%g1, %g4, %g1
.L197:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	sll	%g2, 16, %g2
	sethi	%hi(16384), %o5
	srl	%g2, 16, %g1
	or	%o5, 2, %o5
	and	%g1, 1, %g4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	bne	.L223
	 or	%g1, %g3, %g1
.L199:
	sethi	%hi(16384), %g3
	or	%g3, 2, %g3
	sll	%g2, 16, %g2
	sll	%o0, 16, %o0
	srl	%g2, 16, %g1
	srl	%o0, 24, %o0
	sethi	%hi(32768), %o5
	xor	%o0, %g1, %g4
	srl	%g2, 17, %g2
	xor	%g1, %g3, %g1
	srl	%o0, 1, %o0
	srl	%g1, 1, %g1
	mov	%o0, %g3
	andcc	%g4, 1, %g0
	bne	.L224
	 or	%g1, %o5, %g1
.L201:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%o0, %g1, %o0
	mov	%g3, %g4
	xor	%g1, %o5, %g1
	srl	%g2, 17, %g2
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o0, 1, %g0
	bne	.L225
	 or	%g1, %o5, %g1
.L203:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L226
	 or	%g1, %o5, %g1
.L205:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L227
	 or	%g1, %o5, %g1
.L207:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g4, 0xff, %g4
	srl	%g2, 16, %g1
	srl	%g4, 1, %g4
	xor	%g3, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	bne	.L228
	 or	%g1, %o5, %g1
.L209:
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	bne	.L229
	 or	%g1, %g4, %g1
.L211:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	bne	.L230
	 or	%g1, %g4, %g1
.L213:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	sll	%g2, 16, %g2
	sethi	%hi(16384), %o5
	srl	%g2, 16, %g1
	or	%o5, 2, %o5
	and	%g1, 1, %g4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	bne	.L231
	 or	%g1, %g3, %g1
	sll	%g2, 16, %o0
	jmp	%o7+8
	 srl	%o0, 16, %o0
.L216:
	mov	%o5, %g2
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	sll	%g2, 16, %g2
	and	%g3, 0xff, %g3
	srl	%g2, 16, %g1
	srl	%g3, 1, %g3
	xor	%g4, %g1, %o4
	srl	%g2, 17, %g2
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L187
	 or	%g1, %o5, %g1
.L217:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g4, 0xff, %g4
	sll	%g2, 16, %g2
	srl	%g4, 1, %g4
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L189
	 or	%g1, %o5, %g1
.L218:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g3, 0xff, %g3
	sll	%g2, 16, %g2
	srl	%g3, 1, %g3
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g4, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g3, %g4
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L191
	 or	%g1, %o5, %g1
.L219:
	sethi	%hi(16384), %o5
	or	%o5, 2, %o5
	mov	%g1, %g2
	and	%g4, 0xff, %g4
	sll	%g2, 16, %g2
	srl	%g4, 1, %g4
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %o4
	xor	%g1, %o5, %g1
	mov	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %o5
	andcc	%o4, 1, %g0
	be	.L193
	 or	%g1, %o5, %g1
.L220:
	mov	%g1, %g2
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	xor	%g4, %g1, %g4
	and	%g3, 0xff, %g3
	sethi	%hi(16384), %o4
	srl	%g3, 1, %g3
	or	%o4, 2, %o4
	andcc	%g4, 1, %g0
	xor	%g1, %o4, %g1
	sethi	%hi(32768), %g4
	srl	%g1, 1, %g1
	mov	%g3, %o5
	srl	%g2, 17, %g2
	be	.L195
	 or	%g1, %g4, %g1
.L221:
	sethi	%hi(16384), %g4
	or	%g4, 2, %g4
	mov	%g1, %g2
	sll	%g2, 16, %g2
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	xor	%g3, %g1, %g3
	xor	%g1, %g4, %g1
	andcc	%g3, 1, %g0
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g4
	be	.L197
	 or	%g1, %g4, %g1
.L222:
	and	%o5, 0xff, %g3
	srl	%g3, 1, %g3
	mov	%g1, %g2
	sethi	%hi(16384), %o5
	sll	%g2, 16, %g2
	or	%o5, 2, %o5
	srl	%g2, 16, %g1
	srl	%g2, 17, %g2
	and	%g1, 1, %g4
	xor	%g1, %o5, %g1
	cmp	%g4, %g3
	srl	%g1, 1, %g1
	sethi	%hi(32768), %g3
	be	.L199
	 or	%g1, %g3, %g1
.L223:
	b	.L199
	 mov	%g1, %g2
.L231:
	mov	%g1, %g2
	sll	%g2, 16, %o0
	jmp	%o7+8
	 srl	%o0, 16, %o0
.L230:
	b	.L213
	 mov	%g1, %g2
.L229:
	b	.L211
	 mov	%g1, %g2
.L228:
	b	.L209
	 mov	%g1, %g2
.L227:
	b	.L207
	 mov	%g1, %g2
.L226:
	b	.L205
	 mov	%g1, %g2
.L225:
	b	.L203
	 mov	%g1, %g2
.L224:
	b	.L201
	 mov	%g1, %g2
	.size	crc16, .-crc16
	.align 4
	.global check_data_types
	.type	check_data_types, #function
	.proc	014
check_data_types:
	jmp	%o7+8
	 mov	0, %o0
	.size	check_data_types, .-check_data_types
	.ident	"GCC: (Buildroot 2014.08-g9aeb387) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
