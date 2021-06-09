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
	sethi	%hi(.LC1), %o7
	or	%o7, %lo(.LC1), %o7
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
	mov	0, %o4
	addx	%g0, -1, %o5
	andcc	%i5, 2, %g0
	and	%o5, 240, %o5
	be	.L6
	 add	%o5, 48, %o5
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
	 add	%i4, -1, %g2
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
	 mov	48, %g2
.L17:
	andcc	%i5, 16, %g0
.L69:
	bne	.L70
	 cmp	%g3, %g1
	cmp	%i4, 0
	ble	.L33
	 add	%i4, -1, %g2
	add	%i0, %i4, %i4
	stb	%o5, [%i0]
.L71:
	add	%i0, 1, %i0
	cmp	%i0, %i4
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
	ldub	[%g4+%g1], %g3
	stb	%g3, [%g2]
	add	%g1, -1, %g1
	add	%g1, 1, %g3
	cmp	%g3, 0
	bg	.L23
	 add	%g2, 1, %g2
	xnor	%g0, %i1, %g1
	cmp	%i4, 0
	sra	%g1, 31, %g1
	and	%i1, %g1, %g1
	add	%g1, 1, %g1
	ble	.L75
	 add	%i0, %g1, %i0
	add	%i0, %i4, %g2
	mov	32, %g1
	stb	%g1, [%i0]
.L73:
	add	%i0, 1, %i0
	cmp	%i0, %g2
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
	stb	%g2, [%i0]
	mov	120, %g2
	stb	%g2, [%i0+1]
	b	.L17
	 add	%i0, 2, %i0
.L32:
	b	.L14
	 mov	%g2, %i4
.L33:
	b	.L19
	 mov	%g2, %i4
	.size	number, .-number
	.align 4
	.global uart_send_char
	.type	uart_send_char, #function
	.proc	020
uart_send_char:
	save	%sp, -96, %sp
.L77:
	call	__ajit_serial_putchar__, 0
	 mov	%i0, %o0
	cmp	%o0, 0
	be	.L77
	 sethi	%hi(-53248), %g2
	or	%g2, 512, %g2
.L83:
#APP
! 624 "/home/madhav/AjitProject/Git/AjitRepoV2/tools/minimal_printf_timer/src/ee_printf.c" 1
	lda [%g2] 32, %g1
	
! 0 "" 2
#NO_APP
	and	%g1, 9, %g1
	cmp	%g1, 9
	be	.L83
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
	save	%sp, -1152, %sp
	st	%i5, [%fp+88]
	add	%fp, 72, %l5
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%l5, [%fp-1052]
	ldub	[%i0], %g2
	sll	%g2, 24, %g1
	cmp	%g1, 0
	be	.L166
	 add	%fp, -1024, %i5
	sethi	%hi(.L98), %l6
	mov	%i5, %o0
	mov	37, %l1
	sethi	%hi(.L121), %i4
	sethi	%hi(.LC0), %i3
	mov	48, %i1
	mov	46, %i2
	mov	32, %l4
	mov	1, %l0
	sethi	%hi(.LC1), %l2
	b	.L163
	 sethi	%hi(.LC2), %l3
.L211:
	add	%o0, 1, %o0
	ldub	[%i0+1], %g2
.L91:
	sll	%g2, 24, %g1
	cmp	%g1, 0
	be	.L89
	 add	%i0, 1, %i0
.L163:
	sra	%g1, 24, %g1
	cmp	%g1, 37
	bne,a	.L211
	 stb	%g2, [%o0]
	mov	0, %o5
.L90:
	ldub	[%i0+1], %g1
	add	%g1, -32, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 16
	bleu	.L212
	 add	%i0, 1, %g2
.L92:
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bgu	.L100
	 sll	%g1, 24, %g3
	mov	0, %o3
.L101:
	add	%o3, %o3, %g3
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	sll	%o3, 3, %o3
	add	%g2, 1, %g2
	add	%g3, %o3, %o3
	add	%o3, %g1, %o3
	ldub	[%g2], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bleu	.L101
	 add	%o3, -48, %o3
.L208:
	sll	%g1, 24, %g3
	mov	%g2, %i0
	sra	%g3, 24, %g3
	cmp	%g3, 46
	be	.L213
	 mov	-1, %o4
.L104:
	and	%g1, -33, %g2
	sll	%g2, 24, %g2
	sra	%g2, 24, %g2
	cmp	%g2, 76
	bne	.L109
	 mov	-1, %g3
	sll	%g1, 24, %g3
	ldub	[%i0+1], %g1
	sra	%g3, 24, %g3
	add	%i0, 1, %i0
.L109:
	add	%g1, -65, %g2
	and	%g2, 0xff, %g2
	cmp	%g2, 55
	bleu	.L214
	 or	%i4, %lo(.L121), %g4
.L110:
	sll	%g1, 24, %g2
	sra	%g2, 24, %g2
	cmp	%g2, 37
	be,a	.L225
	 stb	%g1, [%o0]
	stb	%l1, [%o0]
	add	%o0, 1, %o0
	ldsb	[%i0], %g2
	cmp	%g2, 0
	be	.L89
	 ldub	[%i0], %g1
	stb	%g1, [%o0]
.L225:
	add	%o0, 1, %o0
	ldub	[%i0+1], %g2
	sll	%g2, 24, %g1
	cmp	%g1, 0
	bne	.L163
	 add	%i0, 1, %i0
.L89:
	stb	%g0, [%o0]
	ldub	[%fp-1024], %o0
	sll	%o0, 24, %o0
	cmp	%o0, 0
	be	.L244
	 mov	0, %i0
.L165:
	call	uart_send_char, 0
	 sra	%o0, 24, %o0
	add	%i0, 1, %i0
	ldub	[%i5+%i0], %o0
	sll	%o0, 24, %o0
	cmp	%o0, 0
	bne	.L165
	 nop
.L244:
	jmp	%i7+8
	 restore
.L212:
	or	%l6, %lo(.L98), %g4
	sll	%g3, 2, %g3
	ld	[%g4+%g3], %g3
	jmp	%g3
	 nop
	.section	".rodata"
	.section	".text"
.L97:
	or	%o5, 1, %o5
	b	.L90
	 mov	%g2, %i0
.L96:
	or	%o5, 16, %o5
	b	.L90
	 mov	%g2, %i0
.L95:
	or	%o5, 4, %o5
	b	.L90
	 mov	%g2, %i0
.L94:
	or	%o5, 32, %o5
	b	.L90
	 mov	%g2, %i0
.L93:
	or	%o5, 8, %o5
	b	.L90
	 mov	%g2, %i0
.L214:
	sll	%g2, 2, %g2
	ld	[%g4+%g2], %g2
	jmp	%g2
	 nop
	.section	".rodata"
	.section	".text"
.L111:
	or	%o5, 64, %o5
.L113:
	cmp	%g3, 108
	be	.L215
	 mov	0, %g2
	ld	[%l5], %o7
	add	%l5, 4, %l5
	ldub	[%o7+%g2], %g1
	cmp	%g1, 0
	bne	.L148
	 mov	0, %g4
.L217:
	add	%fp, %g4, %g1
	stb	%i1, [%g1-1048]
	add	%g2, 1, %g2
	cmp	%g2, 4
	be	.L216
	 add	%g4, 1, %g4
.L152:
	add	%fp, %g4, %g1
	stb	%i2, [%g1-1048]
	ldub	[%o7+%g2], %g1
	cmp	%g1, 0
	be	.L217
	 add	%g4, 1, %g4
.L148:
	cmp	%g1, 99
	ble	.L150
	 cmp	%g1, 9
	sra	%g1, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 100, %o4
	or	%i3, %lo(.LC0), %g3
	smul	%o4, 100, %o1
	ldub	[%g3+%o4], %o4
	add	%fp, %g4, %o2
	sub	%g1, %o1, %g1
	stb	%o4, [%o2-1048]
	add	%g4, 2, %g4
	sra	%g1, 31, %o1
	wr	%o1, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 10, %o4
	ldub	[%g3+%o4], %l7
	add	%o4, %o4, %o1
	stb	%l7, [%o2-1047]
	sll	%o4, 3, %o4
	add	%o1, %o4, %o4
	sub	%g1, %o4, %g1
.L151:
	add	%fp, %g4, %o4
	ldub	[%g3+%g1], %g1
	stb	%g1, [%o4-1048]
	add	%g2, 1, %g2
	cmp	%g2, 4
	bne	.L152
	 add	%g4, 1, %g4
.L216:
	andcc	%o5, 16, %g0
	bne,a	.L226
	 mov	0, %g1
	cmp	%o3, %g4
	ble	.L180
	 add	%o3, -1, %g1
	sub	%o3, %g4, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L227:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L227
	 stb	%l4, [%o0]
	sub	%l0, %o3, %g1
	add	%o3, -2, %o3
	add	%g4, %g1, %g1
	add	%o3, %g1, %o3
.L153:
	mov	0, %g1
.L226:
	add	%fp, -1048, %g3
	ldub	[%g3+%g1], %g2
.L228:
	stb	%g2, [%o0+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %g4
	bne,a	.L228
	 ldub	[%g3+%g1], %g2
	cmp	%g1, %o3
	bge	.L210
	 add	%o0, %g1, %o0
	sub	%o3, %g1, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L229:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L229
	 stb	%l4, [%o0]
.L210:
	b	.L91
	 ldub	[%i0+1], %g2
.L100:
	sra	%g3, 24, %g4
	cmp	%g4, 42
	be	.L218
	 sra	%g3, 24, %g3
	mov	%g2, %i0
	mov	-1, %o3
	cmp	%g3, 46
	bne	.L104
	 mov	-1, %o4
.L213:
	ldub	[%i0+1], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bgu	.L105
	 add	%i0, 1, %g2
	mov	0, %o4
.L106:
	add	%o4, %o4, %g3
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	sll	%o4, 3, %o4
	add	%g2, 1, %g2
	add	%g3, %o4, %o4
	add	%o4, %g1, %o4
	ldub	[%g2], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bleu	.L106
	 add	%o4, -48, %o4
.L107:
	b	.L104
	 mov	%g2, %i0
.L105:
	sll	%g1, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 42
	be	.L219
	 mov	0, %o4
	b	.L104
	 mov	%g2, %i0
.L172:
	mov	16, %o2
.L120:
	call	number, 0
	 ld	[%l5], %o1
	add	%l5, 4, %l5
	b	.L91
	 ldub	[%i0+1], %g2
.L119:
	b	.L120
	 mov	10, %o2
.L118:
	ld	[%l5], %g4
	cmp	%g4, 0
	be	.L220
	 add	%l5, 4, %l5
.L127:
	ldsb	[%g4], %g1
	cmp	%g1, 0
	be	.L176
	 cmp	%o4, 0
	be	.L176
	 mov	%g4, %g1
	b	.L243
	 add	%g1, 1, %g1
.L129:
	be	.L128
	 sub	%g1, %g4, %g3
	add	%g1, 1, %g1
.L243:
	ldsb	[%g1], %g2
	cmp	%g2, 0
	bne,a	.L129
	 addcc	%o4, -1, %o4
	sub	%g1, %g4, %g3
.L128:
	andcc	%o5, 16, %g0
	bne	.L230
	 cmp	%g3, 0
	cmp	%o3, %g3
	ble	.L177
	 add	%o3, -1, %g1
	sub	%o3, %g3, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L231:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L231
	 stb	%l4, [%o0]
	sub	%l0, %o3, %g1
	add	%o3, -2, %o3
	add	%g1, %g3, %g1
	add	%o3, %g1, %o3
.L131:
	cmp	%g3, 0
.L230:
	ble	.L232
	 sub	%o3, %g3, %g1
	mov	0, %g1
	ldub	[%g4+%g1], %g2
.L233:
	stb	%g2, [%o0+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %g3
	bne,a	.L233
	 ldub	[%g4+%g1], %g2
	add	%o0, %g3, %o0
	sub	%o3, %g3, %g1
.L232:
	cmp	%o3, %g3
	ble	.L210
	 add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L234:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L234
	 stb	%l4, [%o0]
	b	.L91
	 ldub	[%i0+1], %g2
.L117:
	cmp	%o3, -1
	be,a	.L221
	 or	%o5, 1, %o5
.L137:
	ld	[%l5], %o1
	call	number, 0
	 mov	16, %o2
	add	%l5, 4, %l5
	b	.L91
	 ldub	[%i0+1], %g2
.L116:
	b	.L120
	 mov	8, %o2
.L115:
	or	%o5, 2, %o5
	b	.L120
	 mov	10, %o2
.L114:
	andcc	%o5, 16, %g0
	bne,a	.L235
	 ld	[%l5], %g1
	add	%o3, -1, %o3
	cmp	%o3, 0
	ble,a	.L122
	 ld	[%l5], %g1
	add	%o0, %o3, %g1
	stb	%l4, [%o0]
.L236:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L236
	 stb	%l4, [%o0]
	ld	[%l5], %g1
	add	%l5, 4, %l5
	stb	%g1, [%o0]
	add	%o0, 1, %o0
	b	.L91
	 ldub	[%i0+1], %g2
.L112:
	or	%o5, 64, %o5
	b	.L120
	 mov	16, %o2
.L218:
	ld	[%l5], %o3
	add	%i0, 2, %g2
	add	%l5, 4, %l5
	cmp	%o3, 0
	bge	.L208
	 ldub	[%i0+2], %g1
	sub	%g0, %o3, %o3
	b	.L208
	 or	%o5, 16, %o5
.L150:
	ble,a	.L151
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
	stb	%l7, [%o1-1048]
	add	%o2, %o4, %o4
	b	.L151
	 sub	%g1, %o4, %g1
.L215:
	ld	[%l5], %o4
	andcc	%o5, 64, %g0
	be	.L178
	 add	%l5, 4, %l5
	or	%l2, %lo(.LC1), %o7
.L139:
	mov	0, %g1
	ldub	[%o4+%g1], %g4
	and	%g4, 0xff, %l7
	and	%g4, 15, %g4
	mov	0, %g2
	ldub	[%o7+%g4], %o1
	add	%fp, %g2, %g3
	srl	%l7, 4, %l7
	stb	%o1, [%g3-1047]
	ldub	[%o7+%l7], %g4
	stb	%g4, [%g3-1048]
	add	%g1, 1, %g1
	mov	58, %o2
	cmp	%g1, 6
	be	.L223
	 add	%g2, 2, %g4
.L141:
	add	%fp, %g4, %g4
	stb	%o2, [%g4-1048]
	ldub	[%o4+%g1], %g4
	and	%g4, 0xff, %l7
	and	%g4, 15, %g4
	add	%g2, 3, %g2
	ldub	[%o7+%g4], %o1
	add	%fp, %g2, %g3
	srl	%l7, 4, %l7
	stb	%o1, [%g3-1047]
	ldub	[%o7+%l7], %g4
	stb	%g4, [%g3-1048]
	add	%g1, 1, %g1
	cmp	%g1, 6
	bne	.L141
	 add	%g2, 2, %g4
.L223:
	andcc	%o5, 16, %g0
	bne,a	.L237
	 mov	0, %g1
	cmp	%o3, %g4
	ble	.L179
	 add	%o3, -1, %g1
	sub	%o3, %g4, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L238:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L238
	 stb	%l4, [%o0]
	sub	%l0, %o3, %g1
	add	%o3, -2, %o3
	add	%g4, %g1, %g1
	add	%o3, %g1, %o3
.L142:
	mov	0, %g1
.L237:
	add	%fp, -1048, %g3
	ldub	[%g3+%g1], %g2
.L239:
	stb	%g2, [%o0+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %g4
	bne,a	.L239
	 ldub	[%g3+%g1], %g2
	cmp	%o3, %g1
	ble	.L210
	 add	%o0, %g1, %o0
	sub	%o3, %g1, %g1
	add	%o0, %g1, %g1
	stb	%l4, [%o0]
.L240:
	add	%o0, 1, %o0
	cmp	%o0, %g1
	bne,a	.L240
	 stb	%l4, [%o0]
	b	.L91
	 ldub	[%i0+1], %g2
.L122:
.L235:
	stb	%g1, [%o0]
	add	%o0, 1, %g3
	add	%l5, 4, %l5
	add	%o0, %o3, %o0
	cmp	%o3, 1
	ble	.L224
	 mov	%g3, %g1
	stb	%l4, [%g1]
.L241:
	add	%g1, 1, %g1
	cmp	%g1, %o0
	bne,a	.L241
	 stb	%l4, [%g1]
	add	%o3, -1, %o3
	ldub	[%i0+1], %g2
	b	.L91
	 add	%g3, %o3, %o0
.L221:
	b	.L137
	 mov	8, %o3
.L219:
	ld	[%l5], %o4
	add	%i0, 2, %g2
	add	%l5, 4, %l5
	cmp	%o4, 0
	bge	.L107
	 ldub	[%i0+2], %g1
	mov	0, %o4
	b	.L104
	 mov	%g2, %i0
.L166:
	b	.L89
	 mov	%i5, %o0
.L178:
	b	.L139
	 or	%i3, %lo(.LC0), %o7
.L220:
	b	.L127
	 or	%l3, %lo(.LC2), %g4
.L176:
	b	.L128
	 mov	0, %g3
.L180:
	b	.L153
	 mov	%g1, %o3
.L177:
	b	.L131
	 mov	%g1, %o3
.L179:
	b	.L142
	 mov	%g1, %o3
.L224:
	mov	%g3, %o0
	b	.L91
	 ldub	[%i0+1], %g2
	.align 4
	.subsection	-1
	.align 4
.L121:
	.word	.L111
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L112
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L113
	.word	.L110
	.word	.L114
	.word	.L115
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L115
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L110
	.word	.L116
	.word	.L117
	.word	.L110
	.word	.L110
	.word	.L118
	.word	.L110
	.word	.L119
	.word	.L110
	.word	.L110
	.word	.L172
	.previous
	.subsection	-1
	.align 4
.L98:
	.word	.L93
	.word	.L92
	.word	.L92
	.word	.L94
	.word	.L92
	.word	.L92
	.word	.L92
	.word	.L92
	.word	.L92
	.word	.L92
	.word	.L92
	.word	.L95
	.word	.L92
	.word	.L96
	.word	.L92
	.word	.L92
	.word	.L97
	.previous
	.size	ee_printf, .-ee_printf
	.ident	"GCC: (Buildroot 2014.08-gde406ae-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
