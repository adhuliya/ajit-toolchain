	.file	"cortos_util_ee_printf.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"0123456789abcdefghijklmnopqrstuvwxyz"
	.align 8
.LC1:
	.asciz	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	.global __umoddi3
	.global __udivdi3
	.section	".text"
	.align 4
	.type	number, #function
	.proc	0102
number:
	save	%sp, -168, %sp
	ld	[%fp+92], %l2
	mov	%i1, %l0
	andcc	%l2, 64, %g0
	be	.L28
	 mov	%i2, %l1
	sethi	%hi(.LC1), %l3
	or	%l3, %lo(.LC1), %l3
.L2:
	andcc	%l2, 16, %g0
	bne,a	.L3
	 and	%l2, -2, %l2
.L3:
	add	%i3, -2, %g1
	cmp	%g1, 34
	bgu	.L29
	 and	%l2, 1, %g1
	subcc	%g0, %g1, %g0
	mov	0, %l5
	addx	%g0, -1, %l4
	andcc	%l2, 2, %g0
	and	%l4, 240, %l4
	be	.L6
	 add	%l4, 48, %l4
	cmp	%l0, 0
	bge	.L7
	 andcc	%l2, 4, %g0
	subcc	%g0, %l1, %l1
	add	%i4, -1, %i4
	subx	%g0, %l0, %l0
	mov	45, %l5
.L6:
	andcc	%l2, 32, %l6
.L73:
	be	.L64
	 orcc	%l0, %l1, %g0
	cmp	%i3, 16
.L62:
	be	.L56
	 xor	%i3, 8, %g1
	subcc	%g0, %g1, %g0
	addx	%i4, -1, %i4
.L10:
	orcc	%l0, %l1, %g0
.L64:
	bne	.L65
	 mov	0, %i2
	mov	48, %g1
.L63:
	mov	0, %o7
	stb	%g1, [%fp-72]
	mov	1, %i2
	add	%fp, -72, %i1
.L13:
	cmp	%i2, %i5
	bge	.L15
	 mov	%i2, %g2
	mov	%i5, %g2
.L15:
	andcc	%l2, 17, %g0
	bne	.L16
	 sub	%i4, %g2, %g4
	cmp	%g4, 0
	ble	.L33
	 add	%g4, -1, %g1
	add	%i0, %g4, %g4
	mov	32, %g1
	stb	%g1, [%i0]
.L66:
	add	%i0, 1, %i0
	cmp	%i0, %g4
	bne,a	.L66
	 stb	%g1, [%i0]
	mov	-1, %g4
.L16:
	andcc	%l5, 0xff, %g0
	be	.L67
	 cmp	%l6, 0
	stb	%l5, [%i0]
	add	%i0, 1, %i0
.L67:
	be	.L68
	 andcc	%l2, 16, %g0
	cmp	%i3, 8
	be	.L57
	 cmp	%i3, 16
	be,a	.L58
	 mov	48, %g1
.L19:
	andcc	%l2, 16, %g0
.L68:
	bne	.L69
	 cmp	%g2, %i2
	cmp	%g4, 0
	ble	.L34
	 add	%g4, -1, %g1
	add	%i0, %g4, %g4
	stb	%l4, [%i0]
.L70:
	add	%i0, 1, %i0
	cmp	%i0, %g4
	bne,a	.L70
	 stb	%l4, [%i0]
	mov	-1, %g4
.L21:
	cmp	%g2, %i2
.L69:
	ble	.L23
	 sub	%g2, %i2, %g1
	mov	48, %g3
	add	%i0, %g1, %g1
	stb	%g3, [%i0]
.L71:
	add	%i0, 1, %i0
	cmp	%i0, %g1
	bne,a	.L71
	 stb	%g3, [%i0]
.L23:
	mov	%o7, %g1
	mov	%i0, %g2
.L25:
	ldub	[%i1+%g1], %g3
	stb	%g3, [%g2]
	add	%g1, -1, %g1
	add	%g1, 1, %g3
	cmp	%g3, 0
	bg	.L25
	 add	%g2, 1, %g2
	xnor	%g0, %o7, %g1
	cmp	%g4, 0
	sra	%g1, 31, %g1
	and	%o7, %g1, %g1
	add	%g1, 1, %g1
	ble	.L75
	 add	%i0, %g1, %i0
	add	%i0, %g4, %g2
	mov	32, %g1
	stb	%g1, [%i0]
.L72:
	add	%i0, 1, %i0
	cmp	%i0, %g2
	bne,a	.L72
	 stb	%g1, [%i0]
.L75:
	jmp	%i7+8
	 restore
.L28:
	sethi	%hi(.LC0), %l3
	b	.L2
	 or	%l3, %lo(.LC0), %l3
.L12:
	mov	0, %i2
.L65:
	add	%fp, -72, %i1
.L14:
	mov	%l0, %o0
	mov	%l1, %o1
	mov	0, %o2
	call	__umoddi3, 0
	 mov	%i3, %o3
	ldub	[%l3+%o1], %g1
	mov	%l0, %o0
	mov	%l1, %o1
	stb	%g1, [%i1+%i2]
	mov	0, %o2
	mov	%i3, %o3
	call	__udivdi3, 0
	 add	%i2, 1, %i2
	mov	%o0, %l0
	orcc	%l0, %o1, %g0
	bne	.L14
	 mov	%o1, %l1
	b	.L13
	 add	%i2, -1, %o7
.L29:
	mov	0, %i0
	jmp	%i7+8
	 restore
.L7:
	bne,a	.L59
	 add	%i4, -1, %i4
	andcc	%l2, 8, %g0
	be	.L73
	 andcc	%l2, 32, %l6
	add	%i4, -1, %i4
	b	.L73
	 mov	32, %l5
.L59:
	andcc	%l2, 32, %l6
	be	.L10
	 mov	43, %l5
	b	.L62
	 cmp	%i3, 16
.L57:
	mov	48, %g1
	stb	%g1, [%i0]
	b	.L19
	 add	%i0, 1, %i0
.L56:
	orcc	%l0, %l1, %g0
	bne	.L12
	 add	%i4, -2, %i4
	b	.L63
	 mov	48, %g1
.L58:
	stb	%g1, [%i0]
	mov	120, %g1
	stb	%g1, [%i0+1]
	b	.L19
	 add	%i0, 2, %i0
.L33:
	b	.L16
	 mov	%g1, %g4
.L34:
	b	.L21
	 mov	%g1, %g4
	.size	number, .-number
	.section	.rodata.str1.8
	.align 8
.LC2:
	.asciz	"<NULL>"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC3:
	.long	0
	.long	0
	.section	".text"
	.align 4
	.global ee_vsprintf
	.type	ee_vsprintf, #function
	.proc	04
ee_vsprintf:
	save	%sp, -304, %sp
	ldub	[%i1], %g2
	sll	%g2, 24, %g1
	cmp	%g1, 0
	be	.L203
	 mov	%i0, %i5
	sethi	%hi(.L86), %l3
	sethi	%hi(.L110), %i3
	sethi	%hi(.LC3), %l1
	add	%fp, -80, %l2
	add	%fp, 96, %l4
	b	.L200
	 sethi	%hi(.LC0), %l0
.L305:
	add	%i5, 1, %i5
	ldub	[%i1+1], %g2
.L79:
	sll	%g2, 24, %g1
	cmp	%g1, 0
	be	.L195
	 add	%i1, 1, %i1
.L200:
	sra	%g1, 24, %g1
	cmp	%g1, 37
	bne,a	.L305
	 stb	%g2, [%i5]
	mov	0, %l5
.L78:
	ldub	[%i1+1], %g1
	add	%g1, -32, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 16
	bleu	.L306
	 add	%i1, 1, %g2
.L80:
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bgu	.L88
	 sll	%g1, 24, %g3
	mov	0, %i4
.L89:
	add	%i4, %i4, %g3
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	sll	%i4, 3, %i4
	add	%g2, 1, %g2
	add	%g3, %i4, %i4
	add	%i4, %g1, %i4
	ldub	[%g2], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bleu	.L89
	 add	%i4, -48, %i4
.L296:
	sll	%g1, 24, %g3
	mov	%g2, %i1
	sra	%g3, 24, %g3
	cmp	%g3, 46
	be	.L307
	 mov	-1, %l6
.L92:
	and	%g1, -33, %g2
	sll	%g2, 24, %g2
	sra	%g2, 24, %g2
	cmp	%g2, 76
	bne,a	.L208
	 mov	-1, %g3
	ldub	[%i1+1], %g1
	and	%g1, -33, %g2
	sll	%g2, 24, %g2
	sra	%g2, 24, %g2
	cmp	%g2, 76
	bne	.L209
	 add	%i1, 1, %g3
	ldub	[%i1+2], %g1
	mov	108, %g3
	add	%i1, 2, %i1
	mov	108, %g4
.L97:
	add	%g1, -65, %g2
	and	%g2, 0xff, %g2
	cmp	%g2, 55
	bleu	.L308
	 or	%i3, %lo(.L110), %o7
.L98:
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 37
	be	.L194
	 mov	37, %g1
	stb	%g1, [%i5]
	add	%i5, 1, %i5
	ldsb	[%i1], %g2
	cmp	%g2, 0
	be	.L195
	 ldub	[%i1], %g1
.L194:
	stb	%g1, [%i5]
	add	%i5, 1, %i5
	ldub	[%i1+1], %g2
	sll	%g2, 24, %g1
	cmp	%g1, 0
	bne	.L200
	 add	%i1, 1, %i1
.L195:
	sub	%i5, %i0, %i0
.L77:
	stb	%g0, [%i5]
	jmp	%i7+8
	 restore
.L306:
	or	%l3, %lo(.L86), %g4
	sll	%g3, 2, %g3
	ld	[%g4+%g3], %g3
	jmp	%g3
	 nop
	.section	".rodata"
	.section	".text"
.L85:
	or	%l5, 1, %l5
	b	.L78
	 mov	%g2, %i1
.L84:
	or	%l5, 16, %l5
	b	.L78
	 mov	%g2, %i1
.L83:
	or	%l5, 4, %l5
	b	.L78
	 mov	%g2, %i1
.L82:
	or	%l5, 32, %l5
	b	.L78
	 mov	%g2, %i1
.L81:
	or	%l5, 8, %l5
	b	.L78
	 mov	%g2, %i1
.L308:
	sll	%g2, 2, %g2
	ld	[%o7+%g2], %g2
	jmp	%g2
	 nop
	.section	".rodata"
	.section	".text"
.L208:
	b	.L97
	 mov	0, %g4
.L88:
	sra	%g3, 24, %g4
	cmp	%g4, 42
	be	.L309
	 sra	%g3, 24, %g3
	mov	%g2, %i1
	mov	-1, %i4
	cmp	%g3, 46
	bne	.L92
	 mov	-1, %l6
.L307:
	ldub	[%i1+1], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bgu	.L93
	 add	%i1, 1, %g2
	mov	0, %l6
.L94:
	add	%l6, %l6, %g3
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	sll	%l6, 3, %l6
	add	%g2, 1, %g2
	add	%g3, %l6, %l6
	add	%l6, %g1, %l6
	ldub	[%g2], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bleu	.L94
	 add	%l6, -48, %l6
.L95:
	b	.L92
	 mov	%g2, %i1
.L93:
	sll	%g1, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 42
	be	.L310
	 mov	0, %l6
	b	.L92
	 mov	%g2, %i1
.L99:
	or	%l5, 64, %l5
.L101:
	cmp	%g3, 108
	be	.L311
	 mov	0, %g2
	ld	[%i2], %o7
	add	%i2, 4, %i2
	ldub	[%o7+%g2], %g1
	mov	0, %g3
	mov	48, %o3
	cmp	%g1, 0
	bne	.L137
	 mov	46, %o4
.L313:
	add	%fp, %g3, %g1
	stb	%o3, [%g1-80]
	add	%g2, 1, %g2
	cmp	%g2, 4
	be	.L312
	 add	%g3, 1, %g3
.L141:
	add	%fp, %g3, %g1
	stb	%o4, [%g1-80]
	ldub	[%o7+%g2], %g1
	cmp	%g1, 0
	be	.L313
	 add	%g3, 1, %g3
.L137:
	cmp	%g1, 99
	ble	.L139
	 cmp	%g1, 9
	sra	%g1, 31, %g4
	wr	%g4, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 100, %o5
	or	%l0, %lo(.LC0), %g4
	smul	%o5, 100, %o1
	ldub	[%g4+%o5], %o5
	add	%fp, %g3, %o2
	sub	%g1, %o1, %g1
	stb	%o5, [%o2-80]
	add	%g3, 2, %g3
	sra	%g1, 31, %o1
	wr	%o1, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 10, %o5
	ldub	[%g4+%o5], %o0
	add	%o5, %o5, %o1
	stb	%o0, [%o2-79]
	sll	%o5, 3, %o5
	add	%o1, %o5, %o5
	sub	%g1, %o5, %g1
.L140:
	add	%fp, %g3, %o5
	ldub	[%g4+%g1], %g1
	stb	%g1, [%o5-80]
	add	%g2, 1, %g2
	cmp	%g2, 4
	bne	.L141
	 add	%g3, 1, %g3
.L312:
	andcc	%l5, 16, %g0
	bne,a	.L144
	 mov	0, %g1
	cmp	%i4, %g3
	ble	.L218
	 add	%i4, -1, %g1
	sub	%i4, %g3, %g1
	mov	32, %g2
	add	%i5, %g1, %g1
	stb	%g2, [%i5]
.L328:
	add	%i5, 1, %i5
	cmp	%i5, %g1
	bne,a	.L328
	 stb	%g2, [%i5]
	add	%g3, -1, %i4
.L142:
	mov	0, %g1
.L144:
	ldub	[%l2+%g1], %g2
.L329:
	stb	%g2, [%i5+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %g3
	bne,a	.L329
	 ldub	[%l2+%g1], %g2
	cmp	%i4, %g1
	ble	.L304
	 add	%i5, %g1, %i5
	sub	%i4, %g1, %g1
	mov	32, %g2
	add	%i5, %g1, %g1
	stb	%g2, [%i5]
.L330:
	add	%i5, 1, %i5
	cmp	%i5, %g1
	bne,a	.L330
	 stb	%g2, [%i5]
.L304:
	b	.L79
	 ldub	[%i1+1], %g2
.L102:
	andcc	%l5, 16, %g0
	bne,a	.L331
	 ld	[%i2], %g1
	add	%i4, -1, %i4
	cmp	%i4, 0
	ble	.L111
	 mov	32, %g1
	add	%i5, %i4, %g2
	stb	%g1, [%i5]
.L332:
	add	%i5, 1, %i5
	cmp	%i5, %g2
	bne,a	.L332
	 stb	%g1, [%i5]
	ld	[%i2], %g1
	add	%i2, 4, %i2
	stb	%g1, [%i5]
	add	%i5, 1, %i5
	b	.L79
	 ldub	[%i1+1], %g2
.L100:
	or	%l5, 64, %l5
	mov	16, %o3
.L109:
	xor	%g3, 108, %g3
	subcc	%g0, %g3, %g0
	subx	%g0, -1, %g1
	cmp	%g4, 108
	be	.L333
	 andcc	%g1, 0xff, %g0
.L315:
	andcc	%g1, 0xff, %g0
	bne,a	.L314
	 ld	[%i2], %o2
	andcc	%l5, 2, %g0
.L334:
	be	.L199
	 ld	[%i2], %o2
	add	%i2, 4, %i2
	sra	%o2, 31, %o1
.L197:
	mov	%i5, %o0
	st	%l5, [%sp+92]
	mov	%i4, %o4
	call	number, 0
	 mov	%l6, %o5
	ldub	[%i1+1], %g2
	b	.L79
	 mov	%o0, %i5
.L210:
	xor	%g3, 108, %g3
	subcc	%g0, %g3, %g0
	subx	%g0, -1, %g1
	cmp	%g4, 108
	bne	.L315
	 mov	16, %o3
	andcc	%g1, 0xff, %g0
.L333:
	be	.L334
	 andcc	%l5, 2, %g0
	mov	%i2, %o1
	mov	8, %o2
	st	%o3, [%fp-192]
	call	memcpy, 0
	 add	%fp, -168, %o0
	add	%i2, 8, %i2
	ld	[%fp-168], %o1
	ld	[%fp-164], %o2
	b	.L197
	 ld	[%fp-192], %o3
.L108:
	b	.L109
	 mov	10, %o3
.L107:
	ld	[%i2], %g4
	cmp	%g4, 0
	be	.L316
	 add	%i2, 4, %i2
.L116:
	ldsb	[%g4], %g1
	cmp	%g1, 0
	be	.L214
	 cmp	%l6, 0
	be	.L214
	 mov	%g4, %g1
	b	.L357
	 add	%g1, 1, %g1
.L118:
	be	.L117
	 sub	%g1, %g4, %g3
	add	%g1, 1, %g1
.L357:
	ldsb	[%g1], %g2
	cmp	%g2, 0
	bne,a	.L118
	 addcc	%l6, -1, %l6
	sub	%g1, %g4, %g3
.L117:
	andcc	%l5, 16, %g0
	bne	.L335
	 cmp	%g3, 0
	cmp	%i4, %g3
	ble	.L215
	 add	%i4, -1, %g1
	sub	%i4, %g3, %g1
	mov	32, %g2
	add	%i5, %g1, %g1
	stb	%g2, [%i5]
.L336:
	add	%i5, 1, %i5
	cmp	%i5, %g1
	bne,a	.L336
	 stb	%g2, [%i5]
	add	%g3, -1, %i4
.L120:
	cmp	%g3, 0
.L335:
	ble	.L122
	 mov	0, %g1
	ldub	[%g4+%g1], %g2
.L337:
	stb	%g2, [%i5+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %g3
	bne,a	.L337
	 ldub	[%g4+%g1], %g2
	add	%i5, %g3, %i5
.L122:
	sub	%i4, %g3, %g1
	mov	32, %g2
	cmp	%i4, %g3
	ble	.L304
	 add	%i5, %g1, %g1
	stb	%g2, [%i5]
.L338:
	add	%i5, 1, %i5
	cmp	%i5, %g1
	bne,a	.L338
	 stb	%g2, [%i5]
	b	.L79
	 ldub	[%i1+1], %g2
.L106:
	cmp	%i4, -1
	be,a	.L317
	 or	%l5, 1, %l5
.L126:
	ld	[%i2], %o2
	mov	%i5, %o0
	st	%l5, [%sp+92]
	mov	0, %o1
	mov	16, %o3
	mov	%i4, %o4
	call	number, 0
	 mov	%l6, %o5
	add	%i2, 4, %i2
	mov	%o0, %i5
	b	.L79
	 ldub	[%i1+1], %g2
.L104:
	mov	%i2, %o1
	add	%fp, -176, %o0
	call	memcpy, 0
	 mov	8, %o2
	add	%i2, 8, %i2
	andcc	%l5, 16, %g0
	be	.L298
	 ldd	[%fp-176], %f8
	and	%l5, -2, %l5
.L298:
	or	%l5, 2, %l5
	ldd	[%l1+%lo(.LC3)], %f10
	and	%l5, 1, %g1
	fcmped	%f8, %f10
	subcc	%g0, %g1, %g0
	addx	%g0, -1, %l7
	and	%l7, 240, %l7
	nop
	fbl	.L318
	 add	%l7, 48, %l7
	andcc	%l5, 4, %g0
	bne,a	.L319
	 add	%i4, -1, %i4
	andcc	%l5, 8, %g0
	be	.L152
	 mov	0, %g1
	add	%i4, -1, %i4
	b	.L152
	 mov	32, %g1
.L103:
	or	%l5, 2, %l5
	b	.L109
	 mov	10, %o3
.L105:
	b	.L109
	 mov	8, %o3
.L309:
	ld	[%i2], %i4
	add	%i1, 2, %g2
	add	%i2, 4, %i2
	cmp	%i4, 0
	bge	.L296
	 ldub	[%i1+2], %g1
	sub	%g0, %i4, %i4
	b	.L296
	 or	%l5, 16, %l5
.L139:
	ble,a	.L140
	 or	%l0, %lo(.LC0), %g4
	sra	%g1, 31, %g4
	wr	%g4, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 10, %o5
	add	%fp, %g3, %o1
	add	%o5, %o5, %o2
	or	%l0, %lo(.LC0), %g4
	add	%g3, 1, %g3
	ldub	[%g4+%o5], %o0
	sll	%o5, 3, %o5
	stb	%o0, [%o1-80]
	add	%o2, %o5, %o5
	b	.L140
	 sub	%g1, %o5, %g1
.L199:
	mov	0, %o1
	b	.L197
	 add	%i2, 4, %i2
.L314:
	mov	0, %o1
	b	.L197
	 add	%i2, 4, %i2
.L111:
	ld	[%i2], %g1
.L331:
	stb	%g1, [%i5]
	add	%i5, 1, %g3
	add	%i2, 4, %i2
	add	%i5, %i4, %i5
	mov	%g3, %g1
	cmp	%i4, 1
	ble	.L321
	 mov	32, %g2
	stb	%g2, [%g1]
.L339:
	add	%g1, 1, %g1
	cmp	%g1, %i5
	bne,a	.L339
	 stb	%g2, [%g1]
	add	%i4, -1, %i5
	ldub	[%i1+1], %g2
	b	.L79
	 add	%g3, %i5, %i5
.L317:
	b	.L126
	 mov	8, %i4
.L311:
	ld	[%i2], %o3
	andcc	%l5, 64, %g0
	be	.L216
	 add	%i2, 4, %i2
	sethi	%hi(.LC1), %o7
	or	%o7, %lo(.LC1), %o7
.L128:
	mov	0, %g1
	ldub	[%o3+%g1], %g4
	and	%g4, 0xff, %o4
	and	%g4, 15, %g4
	mov	0, %g2
	ldub	[%o7+%g4], %o5
	add	%fp, %g2, %g3
	srl	%o4, 4, %o4
	stb	%o5, [%g3-79]
	ldub	[%o7+%o4], %g4
	stb	%g4, [%g3-80]
	add	%g1, 1, %g1
	mov	58, %o2
	cmp	%g1, 6
	be	.L322
	 add	%g2, 2, %g3
.L130:
	add	%fp, %g3, %g3
	stb	%o2, [%g3-80]
	ldub	[%o3+%g1], %g4
	and	%g4, 0xff, %o4
	and	%g4, 15, %g4
	add	%g2, 3, %g2
	ldub	[%o7+%g4], %o5
	add	%fp, %g2, %g3
	srl	%o4, 4, %o4
	stb	%o5, [%g3-79]
	ldub	[%o7+%o4], %g4
	stb	%g4, [%g3-80]
	add	%g1, 1, %g1
	cmp	%g1, 6
	bne	.L130
	 add	%g2, 2, %g3
.L322:
	andcc	%l5, 16, %g0
	bne,a	.L133
	 mov	0, %g1
	cmp	%i4, %g3
	ble	.L217
	 add	%i4, -1, %g1
	sub	%i4, %g3, %g1
	mov	32, %g2
	add	%i5, %g1, %g1
	stb	%g2, [%i5]
.L340:
	add	%i5, 1, %i5
	cmp	%i5, %g1
	bne,a	.L340
	 stb	%g2, [%i5]
	add	%g3, -1, %i4
.L131:
	mov	0, %g1
.L133:
	ldub	[%l2+%g1], %g2
.L341:
	stb	%g2, [%i5+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %g3
	bne,a	.L341
	 ldub	[%l2+%g1], %g2
	cmp	%i4, %g1
	ble	.L304
	 add	%i5, %g1, %i5
	sub	%i4, %g1, %g1
	mov	32, %g2
	add	%i5, %g1, %g1
	stb	%g2, [%i5]
.L342:
	add	%i5, 1, %i5
	cmp	%i5, %g1
	bne,a	.L342
	 stb	%g2, [%i5]
	b	.L79
	 ldub	[%i1+1], %g2
.L310:
	ld	[%i2], %l6
	add	%i1, 2, %g2
	add	%i2, 4, %i2
	cmp	%l6, 0
	bge	.L95
	 ldub	[%i1+2], %g1
	mov	0, %l6
	b	.L92
	 mov	%g2, %i1
.L203:
	b	.L77
	 mov	0, %i0
.L216:
	b	.L128
	 or	%l0, %lo(.LC0), %o7
.L318:
	fnegs	%f8, %f8
	add	%i4, -1, %i4
	mov	45, %g1
.L152:
	cmp	%l6, -1
	be,a	.L154
	 mov	6, %l6
.L154:
	std	%f8, [%fp-200]
	st	%g1, [%fp-188]
	ldd	[%fp-200], %o0
	mov	%l6, %o2
	add	%fp, -184, %o3
	add	%fp, -180, %o4
	call	fcvtbuf, 0
	 mov	%l2, %o5
	ld	[%fp-180], %g3
	add	%fp, -160, %g2
	cmp	%g3, 0
	be	.L155
	 ld	[%fp-188], %g1
	mov	45, %g3
	add	%fp, -159, %g2
	stb	%g3, [%fp-160]
.L155:
	ldsb	[%o0], %g3
	cmp	%g3, 0
	be	.L156
	 ldub	[%o0], %g4
	ld	[%fp-184], %o5
	mov	%o0, %g3
	cmp	%o5, 0
	bg	.L252
	 mov	46, %o4
	b	.L327
	 mov	48, %g3
.L162:
	stb	%g4, [%g2]
.L343:
	add	%g3, 1, %g3
	add	%g2, 1, %g2
	ldsb	[%g3], %o7
	cmp	%o7, 0
	be	.L161
	 ldub	[%g3], %g4
.L252:
	sub	%g3, %o0, %o7
	cmp	%o5, %o7
	bne,a	.L343
	 stb	%g4, [%g2]
	stb	%o4, [%g2]
	b	.L162
	 add	%g2, 1, %g2
.L319:
	b	.L152
	 mov	43, %g1
.L327:
	stb	%g3, [%g2]
	mov	46, %g3
	stb	%g3, [%g2+1]
	subcc	%g0, %o5, %o7
	be	.L251
	 add	%g2, 2, %g2
	add	%g2, %o7, %o7
	mov	48, %g3
	stb	%g3, [%g2]
.L344:
	add	%g2, 1, %g2
	cmp	%g2, %o7
	bne,a	.L344
	 stb	%g3, [%g2]
.L251:
	stb	%g4, [%g2]
	add	%o0, 1, %o0
	add	%g2, 1, %g2
	ldsb	[%o0], %g3
	cmp	%g3, 0
	bne	.L251
	 ldub	[%o0], %g4
.L161:
	andcc	%l5, 32, %g0
	be	.L302
	 stb	%g0, [%g2]
	cmp	%l6, 0
	be	.L345
	 ldsb	[%fp-160], %g3
.L302:
	ldub	[%fp-160], %g2
	sll	%g2, 24, %g3
	cmp	%g3, 0
	be,a	.L346
	 mov	0, %g4
	add	%fp, -160, %g3
.L202:
.L352:
	b	.L183
	 mov	%g3, %g4
.L182:
	be,a	.L346
	 sub	%l4, %g3, %g4
.L183:
	add	%g4, 1, %g4
	ldsb	[%g4], %o7
	cmp	%o7, 0
	bne	.L182
	 cmp	%g4, %l4
	sub	%g4, %g3, %g4
.L181:
.L346:
	andcc	%l5, 17, %g0
	bne	.L184
	 sub	%i4, %g4, %i4
	cmp	%i4, 0
	ble	.L226
	 add	%i4, -1, %g3
	add	%i5, %i4, %i4
	mov	32, %g3
	stb	%g3, [%i5]
.L347:
	add	%i5, 1, %i5
	cmp	%i5, %i4
	bne,a	.L347
	 stb	%g3, [%i5]
	mov	-1, %i4
.L184:
	andcc	%g1, 0xff, %g0
	be	.L348
	 andcc	%l5, 16, %g0
	stb	%g1, [%i5]
	add	%i5, 1, %i5
.L348:
	bne	.L349
	 cmp	%g4, 0
	cmp	%i4, 0
	ble	.L227
	 add	%i4, -1, %g1
	add	%i5, %i4, %i4
	stb	%l7, [%i5]
.L350:
	add	%i5, 1, %i5
	cmp	%i5, %i4
	bne,a	.L350
	 stb	%l7, [%i5]
	mov	-1, %i4
.L187:
	cmp	%g4, 0
.L349:
	ble	.L189
	 mov	0, %g1
	b	.L358
	 stb	%g2, [%i5+%g1]
.L326:
	ldub	[%g3+%g1], %g2
	stb	%g2, [%i5+%g1]
.L358:
	add	%g1, 1, %g1
	cmp	%g1, %g4
	bne	.L326
	 add	%fp, -160, %g3
	add	%i5, %g1, %i5
.L189:
	cmp	%i4, 0
	ble	.L304
	 mov	32, %g1
	add	%i5, %i4, %g2
	stb	%g1, [%i5]
.L351:
	add	%i5, 1, %i5
	cmp	%i5, %g2
	bne,a	.L351
	 stb	%g1, [%i5]
	b	.L79
	 ldub	[%i1+1], %g2
.L164:
	andcc	%l5, 32, %g0
	be	.L302
	 stb	%g0, [%g2+1]
	ldsb	[%fp-160], %g3
.L345:
	cmp	%g3, 0
	be	.L223
	 ldub	[%fp-160], %g2
	cmp	%g3, 46
	be	.L352
	 add	%fp, -160, %g3
	and	%g2, -33, %g3
	sll	%g3, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 69
	be	.L224
	 add	%fp, -160, %g3
	b	.L173
	 mov	%g3, %g4
.L174:
	cmp	%o7, 46
	be	.L202
	 and	%o5, -33, %o7
	sll	%o7, 24, %o7
	sra	%o7, 24, %o7
	cmp	%o7, 69
	be	.L353
	 add	%g4, 256, %o7
.L173:
	add	%g4, 1, %g4
	ldsb	[%g4], %o7
	cmp	%o7, 0
	bne	.L174
	 ldub	[%g4], %o5
	stb	%g0, [%g4+1]
.L301:
	mov	46, %g2
.L356:
	b	.L302
	 stb	%g2, [%g4]
.L316:
	sethi	%hi(.LC2), %g4
	b	.L116
	 or	%g4, %lo(.LC2), %g4
.L156:
	mov	48, %g3
	cmp	%l6, 0
	be	.L164
	 stb	%g3, [%g2]
	mov	46, %g4
	add	%g2, 2, %g3
	stb	%g4, [%g2+1]
	mov	0, %g2
	mov	48, %g4
	stb	%g4, [%g3+%g2]
.L354:
	add	%g2, 1, %g2
	cmp	%l6, %g2
	bg,a	.L354
	 stb	%g4, [%g3+%g2]
	cmp	%l6, 0
	ble,a	.L201
	 mov	1, %l6
.L201:
	b	.L302
	 stb	%g0, [%g3+%l6]
.L214:
	b	.L117
	 mov	0, %g3
.L218:
	b	.L142
	 mov	%g1, %i4
.L224:
	add	%fp, -160, %g4
	add	%g4, 256, %o7
.L353:
	b	.L177
	 mov	%g4, %g2
.L175:
	be,a	.L355
	 sub	%g2, %g4, %g2
.L177:
	add	%g2, 1, %g2
	ldsb	[%g2], %g3
	cmp	%g3, 0
	bne	.L175
	 cmp	%g2, %o7
	sub	%g2, %g4, %g2
.L355:
	cmp	%g2, 0
	ble,a	.L356
	 mov	46, %g2
.L250:
	ldub	[%g4+%g2], %o7
	add	%g4, %g2, %g3
	addcc	%g2, -1, %g2
	bne	.L250
	 stb	%o7, [%g3+1]
	mov	46, %g2
	b	.L302
	 stb	%g2, [%g4]
.L227:
	b	.L187
	 mov	%g1, %i4
.L226:
	b	.L184
	 mov	%g3, %i4
.L215:
	b	.L120
	 mov	%g1, %i4
.L217:
	b	.L131
	 mov	%g1, %i4
.L223:
	add	%fp, -160, %g4
	b	.L301
	 stb	%g0, [%g4+1]
.L321:
	mov	%g3, %i5
	b	.L79
	 ldub	[%i1+1], %g2
.L209:
	mov	%g3, %i1
	mov	0, %g4
	b	.L97
	 mov	108, %g3
	.align 4
	.subsection	-1
	.align 4
.L110:
	.word	.L99
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L100
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L101
	.word	.L98
	.word	.L102
	.word	.L103
	.word	.L98
	.word	.L104
	.word	.L98
	.word	.L98
	.word	.L103
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L98
	.word	.L105
	.word	.L106
	.word	.L98
	.word	.L98
	.word	.L107
	.word	.L98
	.word	.L108
	.word	.L98
	.word	.L98
	.word	.L210
	.previous
	.subsection	-1
	.align 4
.L86:
	.word	.L81
	.word	.L80
	.word	.L80
	.word	.L82
	.word	.L80
	.word	.L80
	.word	.L80
	.word	.L80
	.word	.L80
	.word	.L80
	.word	.L80
	.word	.L83
	.word	.L80
	.word	.L84
	.word	.L80
	.word	.L80
	.word	.L85
	.previous
	.size	ee_vsprintf, .-ee_vsprintf
	.align 4
	.global uart_send_char
	.type	uart_send_char, #function
	.proc	020
uart_send_char:
	save	%sp, -96, %sp
.L360:
	call	__ajit_serial_putchar_via_bypass__, 0
	 mov	%i0, %o0
	cmp	%o0, 0
	be	.L360
	 sethi	%hi(-53248), %g2
	or	%g2, 512, %g2
.L366:
#APP
! 645 "cortos_src/cortos_util_ee_printf.c" 1
	lda [%g2] 32, %g1
	
! 0 "" 2
#NO_APP
	and	%g1, 9, %g1
	cmp	%g1, 9
	be	.L366
	 nop
	jmp	%i7+8
	 restore
	.size	uart_send_char, .-uart_send_char
	.align 4
	.global ee_printf
	.type	ee_printf, #function
	.proc	04
ee_printf:
	save	%sp, -1128, %sp
	add	%fp, 72, %o2
	st	%i5, [%fp+88]
	mov	%i0, %o1
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%o2, [%fp-1028]
	add	%fp, -1024, %i5
	call	ee_vsprintf, 0
	 mov	%i5, %o0
	ldub	[%fp-1024], %o0
	sll	%o0, 24, %o0
	cmp	%o0, 0
	be	.L377
	 mov	0, %i0
.L373:
	call	uart_send_char, 0
	 sra	%o0, 24, %o0
	add	%i0, 1, %i0
	ldub	[%i5+%i0], %o0
	sll	%o0, 24, %o0
	cmp	%o0, 0
	bne	.L373
	 nop
.L377:
	jmp	%i7+8
	 restore
	.size	ee_printf, .-ee_printf
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
