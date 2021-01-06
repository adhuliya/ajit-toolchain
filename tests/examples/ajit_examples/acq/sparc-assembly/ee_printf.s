	.file	"ee_printf.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"0123456789abcdefghijklmnopqrstuvwxyz"
	.align 8
.LC1:
	.asciz	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	.section	".text"
	.align 4
	.type	number, #function
	.proc	0102
number:
	save	%sp, -168, %sp
	andcc	%i5, 64, %g0
	be	.L26
	 sethi	%hi(.LC0), %o7
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %o7
.L2:
	andcc	%i5, 16, %g0
	bne,a	.L3
	 and	%i5, -2, %i5
.L3:
	add	%i2, -2, %g1
	cmp	%g1, 34
	bgu	.L27
	 and	%i5, 1, %g1
	subcc	%g0, %g1, %g0
	addx	%g0, -1, %o5
	mov	0, %o4
	and	%o5, 240, %g2
	andcc	%i5, 2, %g0
	be	.L6
	 add	%g2, 48, %o5
	cmp	%i1, 0
	bl	.L55
	 andcc	%i5, 4, %g0
	bne,a	.L56
	 add	%i3, -1, %i3
	andcc	%i5, 8, %g0
	be	.L64
	 andcc	%i5, 32, %o3
	add	%i3, -1, %i3
	mov	32, %o4
.L6:
	andcc	%i5, 32, %o3
.L64:
	be	.L65
	 cmp	%i1, 0
	cmp	%i2, 16
.L62:
	be	.L57
	 xor	%i2, 8, %g1
	subcc	%g0, %g1, %g0
	addx	%i3, -1, %i3
.L9:
	cmp	%i1, 0
.L65:
	bne	.L66
	 mov	0, %g1
	mov	48, %g1
.L63:
	add	%fp, -72, %g4
	stb	%g1, [%fp-72]
	mov	1, %g1
.L12:
	cmp	%g1, %i4
	bge	.L13
	 mov	%g1, %g3
	mov	%i4, %g3
.L13:
	andcc	%i5, 17, %g0
	bne	.L14
	 sub	%i3, %g3, %i4
	cmp	%i4, 0
	ble	.L32
	 add	%i4, -1, %i3
	add	%i0, %i4, %i4
	mov	32, %g2
	stb	%g2, [%i0]
.L67:
	add	%i0, 1, %i0
	cmp	%i0, %i4
	bne,a	.L67
	 stb	%g2, [%i0]
	mov	-1, %i4
.L14:
	andcc	%o4, 0xff, %g0
	be	.L68
	 cmp	%o3, 0
	stb	%o4, [%i0]
	add	%i0, 1, %i0
.L68:
	be	.L69
	 andcc	%i5, 16, %g0
	cmp	%i2, 8
	be	.L58
	 cmp	%i2, 16
	be,a	.L59
	 mov	48, %i2
.L17:
	andcc	%i5, 16, %g0
.L69:
	bne	.L70
	 cmp	%g3, %g1
	cmp	%i4, 0
	ble	.L33
	 add	%i4, -1, %i5
	add	%i0, %i4, %i2
	stb	%o5, [%i0]
.L71:
	add	%i0, 1, %i0
	cmp	%i0, %i2
	bne,a	.L71
	 stb	%o5, [%i0]
	mov	-1, %i4
.L19:
	cmp	%g3, %g1
.L70:
	ble	.L21
	 sub	%g3, %g1, %g1
	mov	48, %g3
	add	%i0, %g1, %g1
	stb	%g3, [%i0]
.L72:
	add	%i0, 1, %i0
	cmp	%i0, %g1
	bne,a	.L72
	 stb	%g3, [%i0]
.L21:
	mov	%i1, %g1
	mov	%i0, %g2
.L23:
	ldub	[%g4+%g1], %i3
	stb	%i3, [%g2]
	add	%g1, -1, %g1
	add	%g1, 1, %i5
	cmp	%i5, 0
	bg	.L23
	 add	%g2, 1, %g2
	xnor	%g0, %i1, %g1
	cmp	%i4, 0
	sra	%g1, 31, %g1
	and	%i1, %g1, %g1
	add	%g1, 1, %g1
	ble	.L75
	 add	%i0, %g1, %i0
	add	%i0, %i4, %g4
	mov	32, %g1
	stb	%g1, [%i0]
.L73:
	add	%i0, 1, %i0
	cmp	%i0, %g4
	bne,a	.L73
	 stb	%g1, [%i0]
.L75:
	jmp	%i7+8
	 restore
.L26:
	b	.L2
	 or	%o7, %lo(.LC0), %o7
.L31:
	mov	0, %g1
.L66:
	add	%fp, -72, %g4
.L11:
	wr	%g0, 0, %y
	nop
	nop
	nop
	udiv	%i1, %i2, %g2
	smul	%g2, %i2, %g3
	sub	%i1, %g3, %i1
	ldub	[%o7+%i1], %g3
	stb	%g3, [%g4+%g1]
	mov	%g2, %i1
	cmp	%g2, 0
	bne	.L11
	 add	%g1, 1, %g1
	b	.L12
	 add	%g1, -1, %i1
.L27:
	mov	0, %i0
	jmp	%i7+8
	 restore
.L56:
	andcc	%i5, 32, %o3
	be	.L9
	 mov	43, %o4
	b	.L62
	 cmp	%i2, 16
.L58:
	mov	48, %g2
	stb	%g2, [%i0]
	b	.L17
	 add	%i0, 1, %i0
.L57:
	cmp	%i1, 0
	bne	.L31
	 add	%i3, -2, %i3
	b	.L63
	 mov	48, %g1
.L55:
	sub	%g0, %i1, %i1
	add	%i3, -1, %i3
	andcc	%i5, 32, %o3
	be	.L9
	 mov	45, %o4
	b	.L62
	 cmp	%i2, 16
.L59:
	mov	120, %i3
	stb	%i2, [%i0]
	stb	%i3, [%i0+1]
	b	.L17
	 add	%i0, 2, %i0
.L32:
	b	.L14
	 mov	%i3, %i4
.L33:
	b	.L19
	 mov	%i5, %i4
	.size	number, .-number
	.align 4
	.global memcpy
	.type	memcpy, #function
	.proc	0120
memcpy:
	cmp	%o2, 0
	ble	.L84
	 mov	0, %g1
	ldub	[%o1+%g1], %g2
.L83:
	stb	%g2, [%o0+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %o2
	bne,a	.L83
	 ldub	[%o1+%g1], %g2
.L84:
	jmp	%o7+8
	 nop
	.size	memcpy, .-memcpy
	.align 4
	.global uart_send_char
	.type	uart_send_char, #function
	.proc	020
uart_send_char:
	save	%sp, -96, %sp
.L86:
	call	__ajit_serial_putchar__, 0
	 mov	%i0, %o0
	cmp	%o0, 0
	be	.L86
	 nop
	jmp	%i7+8
	 restore
	.size	uart_send_char, .-uart_send_char
	.section	.rodata.str1.8
	.align 8
.LC2:
	.asciz	"<NULL>"
	.section	".text"
	.align 4
	.global ee_printf
	.type	ee_printf, #function
	.proc	04
ee_printf:
	save	%sp, -384, %sp
	st	%i5, [%fp+88]
	add	%fp, 72, %l5
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%l5, [%fp-284]
	ldub	[%i0], %g2
	sll	%g2, 24, %g1
	cmp	%g1, 0
	be	.L169
	 add	%fp, -256, %i5
	sethi	%hi(.L101), %l6
	mov	%i5, %o0
	mov	37, %l1
	sethi	%hi(.L124), %i4
	sethi	%hi(.LC0), %i3
	mov	48, %i1
	mov	46, %i2
	mov	32, %l4
	mov	1, %l0
	sethi	%hi(.LC1), %l2
	b	.L166
	 sethi	%hi(.LC2), %l3
.L214:
	add	%o0, 1, %o0
	ldub	[%i0+1], %g2
.L94:
	sll	%g2, 24, %g1
	cmp	%g1, 0
	be	.L92
	 add	%i0, 1, %i0
.L166:
	sra	%g1, 24, %g1
	cmp	%g1, 37
	bne,a	.L214
	 stb	%g2, [%o0]
	mov	0, %o5
.L93:
	ldub	[%i0+1], %g1
	add	%g1, -32, %g3
	and	%g3, 0xff, %o1
	cmp	%o1, 16
	bleu	.L215
	 add	%i0, 1, %g2
.L95:
	add	%g1, -48, %o4
	and	%o4, 0xff, %o7
	cmp	%o7, 9
	bgu	.L103
	 sll	%g1, 24, %l7
	mov	0, %o3
.L104:
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	add	%o3, %o3, %i0
	sll	%o3, 3, %o1
	add	%g2, 1, %g2
	add	%i0, %o1, %g4
	add	%g4, %g1, %o2
	ldub	[%g2], %g1
	add	%g1, -48, %o4
	and	%o4, 0xff, %o7
	cmp	%o7, 9
	bleu	.L104
	 add	%o2, -48, %o3
.L211:
	sll	%g1, 24, %l7
	mov	%g2, %i0
	sra	%l7, 24, %l7
	cmp	%l7, 46
	be	.L216
	 mov	-1, %o4
.L107:
	and	%g1, -33, %g4
	sll	%g4, 24, %o2
	sra	%o2, 24, %g2
	cmp	%g2, 76
	bne	.L112
	 mov	-1, %l7
	sll	%g1, 24, %o7
	ldub	[%i0+1], %g1
	sra	%o7, 24, %l7
	add	%i0, 1, %i0
.L112:
	add	%g1, -65, %g3
	and	%g3, 0xff, %o1
	cmp	%o1, 55
	bleu	.L217
	 or	%i4, %lo(.L124), %g4
.L113:
	sll	%g1, 24, %o5
	sra	%o5, 24, %o1
	cmp	%o1, 37
	be,a	.L228
	 stb	%g1, [%o0]
	stb	%l1, [%o0]
	add	%o0, 1, %o0
	ldsb	[%i0], %g4
	cmp	%g4, 0
	be	.L92
	 ldub	[%i0], %g1
	stb	%g1, [%o0]
.L228:
	add	%o0, 1, %o0
	ldub	[%i0+1], %g2
	sll	%g2, 24, %g1
	cmp	%g1, 0
	bne	.L166
	 add	%i0, 1, %i0
.L92:
	stb	%g0, [%o0]
	ldub	[%fp-256], %i0
	sll	%i0, 24, %l5
	cmp	%l5, 0
	be	.L247
	 mov	0, %i0
.L168:
	call	uart_send_char, 0
	 sra	%l5, 24, %o0
	add	%i0, 1, %i0
	ldub	[%i5+%i0], %o0
	sll	%o0, 24, %l5
	cmp	%l5, 0
	bne	.L168
	 nop
.L247:
	jmp	%i7+8
	 restore
.L215:
	or	%l6, %lo(.L101), %g4
	sll	%o1, 2, %o2
	ld	[%g4+%o2], %o3
	jmp	%o3
	 nop
	.section	".rodata"
	.section	".text"
.L100:
	or	%o5, 1, %o5
	b	.L93
	 mov	%g2, %i0
.L99:
	or	%o5, 16, %o5
	b	.L93
	 mov	%g2, %i0
.L98:
	or	%o5, 4, %o5
	b	.L93
	 mov	%g2, %i0
.L97:
	or	%o5, 32, %o5
	b	.L93
	 mov	%g2, %i0
.L96:
	or	%o5, 8, %o5
	b	.L93
	 mov	%g2, %i0
.L217:
	sll	%o1, 2, %o2
	ld	[%g4+%o2], %g2
	jmp	%g2
	 nop
	.section	".rodata"
	.section	".text"
.L114:
	or	%o5, 64, %o5
.L116:
	cmp	%l7, 108
	be	.L218
	 mov	0, %g2
	ld	[%l5], %o7
	add	%l5, 4, %l5
	ldub	[%o7+%g2], %g1
	cmp	%g1, 0
	bne	.L151
	 mov	0, %g4
.L220:
	add	%fp, %g4, %g1
	stb	%i1, [%g1-280]
	add	%g2, 1, %g2
	cmp	%g2, 4
	be	.L219
	 add	%g4, 1, %g4
.L155:
	add	%fp, %g4, %g1
	stb	%i2, [%g1-280]
	ldub	[%o7+%g2], %g1
	cmp	%g1, 0
	be	.L220
	 add	%g4, 1, %g4
.L151:
	cmp	%g1, 99
	ble	.L153
	 cmp	%g1, 9
	sra	%g1, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 100, %l7
	add	%fp, %g4, %o2
	smul	%l7, 100, %o1
	or	%i3, %lo(.LC0), %g3
	ldub	[%g3+%l7], %o4
	sub	%g1, %o1, %g1
	stb	%o4, [%o2-280]
	add	%g4, 2, %g4
	sra	%g1, 31, %o1
	wr	%o1, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 10, %o4
	ldub	[%g3+%o4], %l7
	add	%o4, %o4, %o1
	stb	%l7, [%o2-279]
	sll	%o4, 3, %o4
	add	%o1, %o4, %o2
	sub	%g1, %o2, %g1
.L154:
	add	%fp, %g4, %l7
	ldub	[%g3+%g1], %g1
	stb	%g1, [%l7-280]
	add	%g2, 1, %g2
	cmp	%g2, 4
	bne	.L155
	 add	%g4, 1, %g4
.L219:
	andcc	%o5, 16, %g0
	bne,a	.L229
	 mov	0, %g1
	cmp	%o3, %g4
	ble	.L183
	 add	%o3, -1, %g1
	sub	%o3, %g4, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L230:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L230
	 stb	%l4, [%o0]
	sub	%l0, %o3, %g1
	add	%o3, -2, %o7
	add	%g4, %g1, %g1
	add	%o7, %g1, %o3
.L156:
	mov	0, %g1
.L229:
	add	%fp, -280, %o5
	ldub	[%o5+%g1], %g3
.L231:
	stb	%g3, [%o0+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %g4
	bne,a	.L231
	 ldub	[%o5+%g1], %g3
	cmp	%g1, %o3
	bge	.L213
	 add	%o0, %g1, %o0
	sub	%o3, %g1, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L232:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L232
	 stb	%l4, [%o0]
.L213:
	b	.L94
	 ldub	[%i0+1], %g2
.L103:
	sra	%l7, 24, %g3
	cmp	%g3, 42
	be	.L221
	 sra	%l7, 24, %l7
	mov	%g2, %i0
	mov	-1, %o3
	cmp	%l7, 46
	bne	.L107
	 mov	-1, %o4
.L216:
	ldub	[%i0+1], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %o1
	cmp	%o1, 9
	bgu	.L108
	 add	%i0, 1, %g2
	mov	0, %o4
.L109:
	add	%o4, %o4, %i0
	sll	%g1, 24, %g1
	sll	%o4, 3, %o4
	sra	%g1, 24, %g1
	add	%i0, %o4, %o7
	add	%g2, 1, %g2
	add	%o7, %g1, %l7
	ldub	[%g2], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %o1
	cmp	%o1, 9
	bleu	.L109
	 add	%l7, -48, %o4
.L110:
	b	.L107
	 mov	%g2, %i0
.L108:
	sll	%g1, 24, %g4
	sra	%g4, 24, %o2
	cmp	%o2, 42
	be	.L222
	 mov	0, %o4
	b	.L107
	 mov	%g2, %i0
.L175:
	mov	16, %o2
.L123:
	call	number, 0
	 ld	[%l5], %o1
	add	%l5, 4, %l5
	b	.L94
	 ldub	[%i0+1], %g2
.L122:
	b	.L123
	 mov	10, %o2
.L121:
	ld	[%l5], %o7
	cmp	%o7, 0
	be	.L223
	 add	%l5, 4, %l5
.L130:
	ldsb	[%o7], %g1
	cmp	%g1, 0
	be	.L179
	 cmp	%o4, 0
	be	.L179
	 mov	%o7, %g1
	b	.L246
	 add	%g1, 1, %g1
.L132:
	be,a	.L131
	 sub	%g1, %o7, %o4
	add	%g1, 1, %g1
.L246:
	ldsb	[%g1], %l7
	cmp	%l7, 0
	bne	.L132
	 addcc	%o4, -1, %o4
	sub	%g1, %o7, %o4
.L131:
	andcc	%o5, 16, %g0
	bne	.L233
	 cmp	%o4, 0
	cmp	%o3, %o4
	ble	.L180
	 add	%o3, -1, %g1
	sub	%o3, %o4, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L234:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L234
	 stb	%l4, [%o0]
	sub	%l0, %o3, %g1
	add	%o3, -2, %o5
	add	%g1, %o4, %g1
	add	%o5, %g1, %o3
.L134:
	cmp	%o4, 0
.L233:
	ble	.L235
	 sub	%o3, %o4, %g1
	mov	0, %g1
	ldub	[%o7+%g1], %g3
.L236:
	stb	%g3, [%o0+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %o4
	bne,a	.L236
	 ldub	[%o7+%g1], %g3
	add	%o0, %o4, %o0
	sub	%o3, %o4, %g1
.L235:
	cmp	%o3, %o4
	ble	.L213
	 add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L237:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L237
	 stb	%l4, [%o0]
	b	.L94
	 ldub	[%i0+1], %g2
.L120:
	cmp	%o3, -1
	be,a	.L224
	 or	%o5, 1, %o5
.L140:
	ld	[%l5], %o1
	call	number, 0
	 mov	16, %o2
	add	%l5, 4, %l5
	b	.L94
	 ldub	[%i0+1], %g2
.L119:
	b	.L123
	 mov	8, %o2
.L118:
	or	%o5, 2, %o5
	b	.L123
	 mov	10, %o2
.L117:
	andcc	%o5, 16, %g0
	bne,a	.L238
	 ld	[%l5], %g1
	add	%o3, -1, %o3
	cmp	%o3, 0
	ble,a	.L125
	 ld	[%l5], %g1
	add	%o0, %o3, %g1
	stb	%l4, [%o0]
.L239:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L239
	 stb	%l4, [%o0]
	ld	[%l5], %g1
	add	%l5, 4, %l5
	stb	%g1, [%o0]
	add	%o0, 1, %o0
	b	.L94
	 ldub	[%i0+1], %g2
.L115:
	or	%o5, 64, %o5
	b	.L123
	 mov	16, %o2
.L221:
	ld	[%l5], %o3
	add	%i0, 2, %g2
	add	%l5, 4, %l5
	cmp	%o3, 0
	bge	.L211
	 ldub	[%i0+2], %g1
	sub	%g0, %o3, %o3
	b	.L211
	 or	%o5, 16, %o5
.L153:
	ble,a	.L154
	 or	%i3, %lo(.LC0), %g3
	sra	%g1, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 10, %o4
	add	%fp, %g4, %o1
	add	%o4, %o4, %o2
	or	%i3, %lo(.LC0), %g3
	add	%g4, 1, %g4
	ldub	[%g3+%o4], %l7
	sll	%o4, 3, %o4
	stb	%l7, [%o1-280]
	add	%o2, %o4, %o1
	b	.L154
	 sub	%g1, %o1, %g1
.L218:
	ld	[%l5], %o4
	andcc	%o5, 64, %g0
	be	.L181
	 add	%l5, 4, %l5
	or	%l2, %lo(.LC1), %o7
.L142:
	mov	0, %g1
	ldub	[%o4+%g1], %o1
	and	%o1, 15, %g4
	mov	0, %g2
	and	%o1, 0xff, %l7
	add	%fp, %g2, %g3
	srl	%l7, 4, %l7
	ldub	[%o7+%g4], %o1
	ldub	[%o7+%l7], %g4
	stb	%o1, [%g3-279]
	stb	%g4, [%g3-280]
	add	%g1, 1, %g1
	mov	58, %o2
	cmp	%g1, 6
	be	.L226
	 add	%g2, 2, %l7
.L144:
	ldub	[%o4+%g1], %o1
	add	%fp, %l7, %g3
	and	%o1, 15, %g4
	stb	%o2, [%g3-280]
	add	%g2, 3, %g2
	and	%o1, 0xff, %l7
	add	%fp, %g2, %g3
	srl	%l7, 4, %l7
	ldub	[%o7+%g4], %o1
	ldub	[%o7+%l7], %g4
	stb	%o1, [%g3-279]
	stb	%g4, [%g3-280]
	add	%g1, 1, %g1
	cmp	%g1, 6
	bne	.L144
	 add	%g2, 2, %l7
.L226:
	andcc	%o5, 16, %g0
	bne,a	.L240
	 mov	0, %g1
	cmp	%o3, %l7
	ble	.L182
	 add	%o3, -1, %g1
	sub	%o3, %l7, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L241:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L241
	 stb	%l4, [%o0]
	sub	%l0, %o3, %g1
	add	%o3, -2, %o3
	add	%l7, %g1, %g1
	add	%o3, %g1, %o3
.L145:
	mov	0, %g1
.L240:
	add	%fp, -280, %o4
	ldub	[%o4+%g1], %o2
.L242:
	stb	%o2, [%o0+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %l7
	bne,a	.L242
	 ldub	[%o4+%g1], %o2
	cmp	%o3, %g1
	ble	.L213
	 add	%o0, %g1, %o0
	sub	%o3, %g1, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L243:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L243
	 stb	%l4, [%o0]
	b	.L94
	 ldub	[%i0+1], %g2
.L125:
.L238:
	stb	%g1, [%o0]
	add	%o0, 1, %o1
	add	%l5, 4, %l5
	add	%o0, %o3, %o0
	cmp	%o3, 1
	ble	.L227
	 mov	%o1, %g1
	stb	%l4, [%g1]
.L244:
	add	%g1, 1, %g1
	cmp	%g1, %o0
	bne,a	.L244
	 stb	%l4, [%g1]
	add	%o3, -1, %o3
	ldub	[%i0+1], %g2
	b	.L94
	 add	%o1, %o3, %o0
.L224:
	b	.L140
	 mov	8, %o3
.L222:
	ld	[%l5], %o4
	add	%i0, 2, %g2
	add	%l5, 4, %l5
	cmp	%o4, 0
	bge	.L110
	 ldub	[%i0+2], %g1
	mov	0, %o4
	b	.L107
	 mov	%g2, %i0
.L169:
	b	.L92
	 mov	%i5, %o0
.L181:
	b	.L142
	 or	%i3, %lo(.LC0), %o7
.L223:
	b	.L130
	 or	%l3, %lo(.LC2), %o7
.L179:
	b	.L131
	 mov	0, %o4
.L183:
	b	.L156
	 mov	%g1, %o3
.L180:
	b	.L134
	 mov	%g1, %o3
.L182:
	b	.L145
	 mov	%g1, %o3
.L227:
	mov	%o1, %o0
	b	.L94
	 ldub	[%i0+1], %g2
	.align 4
	.subsection	-1
	.align 4
.L124:
	.word	.L114
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L115
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L116
	.word	.L113
	.word	.L117
	.word	.L118
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L118
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L113
	.word	.L119
	.word	.L120
	.word	.L113
	.word	.L113
	.word	.L121
	.word	.L113
	.word	.L122
	.word	.L113
	.word	.L113
	.word	.L175
	.previous
	.subsection	-1
	.align 4
.L101:
	.word	.L96
	.word	.L95
	.word	.L95
	.word	.L97
	.word	.L95
	.word	.L95
	.word	.L95
	.word	.L95
	.word	.L95
	.word	.L95
	.word	.L95
	.word	.L98
	.word	.L95
	.word	.L99
	.word	.L95
	.word	.L95
	.word	.L100
	.previous
	.size	ee_printf, .-ee_printf
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
