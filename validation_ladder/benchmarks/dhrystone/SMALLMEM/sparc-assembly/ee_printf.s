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
	be	.L58
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
	bgu	.L59
	 and	%i5, 1, %g1
	subcc	%g0, %g1, %g0
	mov	0, %o2
	addx	%g0, -1, %o5
	andcc	%i5, 2, %g0
	and	%o5, 240, %o5
	be	.L6
	 add	%o5, 48, %o5
	cmp	%i1, 0
	bl	.L111
	 andcc	%i5, 4, %g0
	bne,a	.L112
	 add	%i3, -1, %i3
	andcc	%i5, 8, %g0
	be	.L120
	 andcc	%i5, 32, %o1
	add	%i3, -1, %i3
	mov	32, %o2
.L6:
	andcc	%i5, 32, %o1
.L120:
	be	.L121
	 cmp	%i1, 0
	cmp	%i2, 16
.L118:
	be	.L113
	 xor	%i2, 8, %g1
	subcc	%g0, %g1, %g0
	addx	%i3, -1, %i3
.L9:
	cmp	%i1, 0
.L121:
	bne	.L122
	 mov	0, %g1
	mov	48, %g1
.L119:
	add	%fp, -72, %g4
	stb	%g1, [%fp-72]
	mov	1, %g1
.L12:
	cmp	%g1, %i4
	bge	.L13
	 mov	%g1, %o4
	mov	%i4, %o4
.L13:
	andcc	%i5, 17, %g0
	bne	.L14
	 sub	%i3, %o4, %i3
	cmp	%i3, 0
	ble	.L64
	 add	%i3, -1, %o7
	sub	%g0, %i0, %g2
	mov	%i3, %l1
	and	%g2, 3, %g2
	cmp	%i3, %g2
	bleu	.L15
	 mov	%i3, %i4
	mov	%g2, %i4
.L15:
	cmp	%i3, 3
	bleu,a	.L16
	 mov	%i3, %i4
.L16:
	cmp	%i4, 0
	be	.L17
	 mov	%i0, %g2
	mov	32, %o3
.L18:
	stb	%o3, [%g2]
	add	%g2, 1, %g2
	sub	%g2, %i0, %g3
	cmp	%i4, %g3
	bgu	.L18
	 add	%o7, -1, %o7
	cmp	%i3, %i4
	be,a	.L123
	 mov	-1, %i3
.L17:
	sub	%i3, %i4, %i3
	srl	%i3, 2, %o3
	sll	%o3, 2, %l0
	cmp	%l0, 0
	be	.L20
	 add	%i0, %i4, %i4
	sethi	%hi(538976256), %o0
	mov	0, %g3
	or	%o0, 32, %o0
.L21:
	st	%o0, [%i4]
	add	%g3, 1, %g3
	cmp	%g3, %o3
	blu	.L21
	 add	%i4, 4, %i4
	add	%g2, %l0, %g2
	cmp	%i3, %l0
	be	.L19
	 sub	%o7, %l0, %o7
.L20:
	mov	0, %g3
	add	%o7, 1, %o7
	mov	32, %i3
	stb	%i3, [%g2+%g3]
.L124:
	add	%g3, 1, %g3
	sub	%o7, %g3, %i4
	cmp	%i4, 0
	bg,a	.L124
	 stb	%i3, [%g2+%g3]
.L19:
	mov	-1, %i3
.L123:
	add	%i0, %l1, %i0
.L14:
	andcc	%o2, 0xff, %g0
	be	.L125
	 cmp	%o1, 0
	stb	%o2, [%i0]
	add	%i0, 1, %i0
.L125:
	be	.L126
	 andcc	%i5, 16, %g0
	cmp	%i2, 8
	be	.L114
	 cmp	%i2, 16
	be,a	.L115
	 mov	48, %g2
.L25:
	andcc	%i5, 16, %g0
.L126:
	bne	.L127
	 cmp	%o4, %g1
	cmp	%i3, 0
	ble	.L66
	 add	%i3, -1, %i4
	sub	%g0, %i0, %i5
	and	%i5, 3, %i5
	cmp	%i5, %i3
	bgu,a	.L28
	 mov	%i3, %i5
.L28:
	cmp	%i3, 3
	bleu,a	.L29
	 mov	%i3, %i5
.L29:
	cmp	%i5, 0
	be	.L30
	 mov	%i0, %g2
.L31:
	stb	%o5, [%g2]
	add	%g2, 1, %g2
	sub	%g2, %i0, %g3
	cmp	%i5, %g3
	bgu	.L31
	 add	%i4, -1, %i4
	cmp	%i3, %i5
	be,a	.L128
	 add	%i0, %i3, %i0
.L30:
	sub	%i3, %i5, %o2
	srl	%o2, 2, %i2
	sll	%i2, 2, %o3
	cmp	%o3, 0
	be	.L33
	 add	%i0, %i5, %i5
	and	%o5, 0xff, %o7
	sll	%o7, 16, %g3
	sll	%o7, 24, %o0
	sll	%o7, 8, %o1
	or	%o0, %g3, %o0
	or	%o0, %o1, %o1
	mov	0, %g3
	or	%o1, %o7, %o7
.L34:
	st	%o7, [%i5]
	add	%g3, 1, %g3
	cmp	%g3, %i2
	blu	.L34
	 add	%i5, 4, %i5
	add	%g2, %o3, %g2
	cmp	%o2, %o3
	be	.L32
	 sub	%i4, %o3, %i4
.L33:
	mov	0, %g3
	add	%i4, 1, %i4
	stb	%o5, [%g2+%g3]
.L129:
	add	%g3, 1, %g3
	sub	%i4, %g3, %i5
	cmp	%i5, 0
	bg,a	.L129
	 stb	%o5, [%g2+%g3]
.L32:
	add	%i0, %i3, %i0
.L128:
	mov	-1, %i3
.L27:
	cmp	%o4, %g1
.L127:
	ble	.L37
	 add	%o4, -1, %i4
	sub	%o4, %g1, %o5
	sub	%g0, %i0, %i5
	and	%i5, 3, %i5
	cmp	%i5, %o5
	bgu,a	.L38
	 mov	%o5, %i5
.L38:
	cmp	%o5, 3
	bleu,a	.L39
	 mov	%o5, %i5
.L39:
	cmp	%i5, 0
	be	.L40
	 mov	%i0, %g2
	mov	48, %i2
.L41:
	stb	%i2, [%g2]
	add	%g2, 1, %g2
	sub	%g2, %i0, %g3
	cmp	%i5, %g3
	bgu	.L41
	 add	%i4, -1, %i4
	cmp	%o5, %i5
	be,a	.L37
	 add	%i0, %o5, %i0
.L40:
	sub	%o5, %i5, %o3
	srl	%o3, 2, %i2
	sll	%i2, 2, %o4
	cmp	%o4, 0
	be	.L43
	 add	%i0, %i5, %i5
	sethi	%hi(808464384), %o7
	mov	0, %g3
	or	%o7, 48, %o7
.L44:
	st	%o7, [%i5]
	add	%g3, 1, %g3
	cmp	%i2, %g3
	bgu	.L44
	 add	%i5, 4, %i5
	add	%g2, %o4, %g2
	cmp	%o3, %o4
	be	.L42
	 sub	%i4, %o4, %i4
.L43:
	mov	0, %g3
	add	%i4, 1, %i4
	mov	48, %i2
	stb	%i2, [%g2+%g3]
.L130:
	add	%g3, 1, %g3
	sub	%i4, %g3, %i5
	cmp	%g1, %i5
	bl,a	.L130
	 stb	%i2, [%g2+%g3]
.L42:
	add	%i0, %o5, %i0
.L37:
	mov	%i1, %g1
	mov	%i0, %g2
.L47:
	ldub	[%g4+%g1], %g3
	stb	%g3, [%g2]
	add	%g1, -1, %g1
	add	%g1, 1, %g3
	cmp	%g3, 0
	bg	.L47
	 add	%g2, 1, %g2
	xnor	%g0, %i1, %g1
	add	%i3, -1, %g4
	sra	%g1, 31, %g1
	cmp	%i3, 0
	and	%i1, %g1, %g1
	add	%g1, 1, %g1
	ble	.L132
	 add	%i0, %g1, %i0
	sub	%g0, %i0, %g3
	and	%g3, 3, %g3
	cmp	%g3, %i3
	bgu,a	.L49
	 mov	%i3, %g3
.L49:
	cmp	%i3, 3
	bleu,a	.L50
	 mov	%i3, %g3
.L50:
	cmp	%g3, 0
	be	.L51
	 mov	%i0, %g1
	mov	32, %i5
.L52:
	stb	%i5, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i0, %g2
	cmp	%g3, %g2
	bgu	.L52
	 add	%g4, -1, %g4
	cmp	%i3, %g3
	be	.L53
	 nop
.L51:
	sub	%i3, %g3, %i1
	srl	%i1, 2, %i5
	sll	%i5, 2, %i2
	cmp	%i2, 0
	be	.L54
	 add	%i0, %g3, %g3
	sethi	%hi(538976256), %i4
	mov	0, %g2
	or	%i4, 32, %i4
.L55:
	st	%i4, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %i5
	blu	.L55
	 add	%g3, 4, %g3
	add	%g1, %i2, %g1
	cmp	%i1, %i2
	be	.L53
	 sub	%g4, %i2, %g4
.L54:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %i5
	stb	%i5, [%g1+%g2]
.L131:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, 0
	bg,a	.L131
	 stb	%i5, [%g1+%g2]
.L53:
	jmp	%i7+8
	 restore %i0, %i3, %o0
.L58:
	b	.L2
	 or	%o7, %lo(.LC0), %o7
.L63:
	mov	0, %g1
.L122:
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
.L59:
	mov	0, %i0
.L132:
	jmp	%i7+8
	 restore
.L112:
	andcc	%i5, 32, %o1
	be	.L9
	 mov	43, %o2
	b	.L118
	 cmp	%i2, 16
.L114:
	mov	48, %g2
	stb	%g2, [%i0]
	b	.L25
	 add	%i0, 1, %i0
.L113:
	cmp	%i1, 0
	bne	.L63
	 add	%i3, -2, %i3
	b	.L119
	 mov	48, %g1
.L111:
	sub	%g0, %i1, %i1
	add	%i3, -1, %i3
	andcc	%i5, 32, %o1
	be	.L9
	 mov	45, %o2
	b	.L118
	 cmp	%i2, 16
.L115:
	stb	%g2, [%i0]
	mov	120, %g2
	stb	%g2, [%i0+1]
	b	.L25
	 add	%i0, 2, %i0
.L64:
	b	.L14
	 mov	%o7, %i3
.L66:
	b	.L27
	 mov	%i4, %i3
	.size	number, .-number
	.align 4
	.global memcpy
	.type	memcpy, #function
	.proc	020
memcpy:
	cmp	%o2, 0
	ble	.L149
	 add	%o1, 4, %g1
	cmp	%o0, %g1
	add	%o0, 4, %g1
	subx	%g0, -1, %g4
	cmp	%o1, %g1
	subx	%g0, -1, %g2
	srl	%o2, 2, %o5
	or	%g4, %g2, %g4
	sll	%o5, 2, %g1
	cmp	%o2, 3
	bleu	.L145
	 mov	1, %g2
.L136:
	or	%o1, %o0, %g3
	and	%g3, 3, %g3
	subcc	%g0, %g3, %g0
	and	%g4, %g2, %g2
	subx	%g0, -1, %g3
	andcc	%g2, %g3, %g0
	be	.L141
	 cmp	%g1, 0
	be	.L141
	 mov	0, %g2
	mov	0, %g3
.L137:
	ld	[%o1+%g2], %g4
	st	%g4, [%o0+%g2]
	add	%g3, 1, %g3
	cmp	%o5, %g3
	bgu	.L137
	 add	%g2, 4, %g2
	cmp	%o2, %g1
	be	.L148
	 nop
.L142:
	ldub	[%o1+%g1], %g2
.L147:
	stb	%g2, [%o0+%g1]
	add	%g1, 1, %g1
	cmp	%o2, %g1
	bg,a	.L147
	 ldub	[%o1+%g1], %g2
.L149:
	jmp	%o7+8
	 nop
.L145:
	b	.L136
	 mov	0, %g2
.L148:
	jmp	%o7+8
	 nop
.L141:
	b	.L142
	 mov	0, %g1
	.size	memcpy, .-memcpy
	.align 4
	.global uart_send_char
	.type	uart_send_char, #function
	.proc	020
uart_send_char:
	save	%sp, -96, %sp
.L151:
	call	__ajit_serial_putchar__, 0
	 mov	%i0, %o0
	cmp	%o0, 0
	be	.L151
	 sethi	%hi(-53248), %g2
	or	%g2, 512, %g2
.L157:
#APP
! 624 "/home/madhav/AjitToolChain/AjitPublicResources/tools/minimal_printf_timer/src/ee_printf.c" 1
	lda [%g2] 32, %g1
	
! 0 "" 2
#NO_APP
	and	%g1, 9, %g1
	cmp	%g1, 9
	be	.L157
	 nop
	jmp	%i7+8
	 restore
	.size	uart_send_char, .-uart_send_char
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
	.global ee_printf
	.type	ee_printf, #function
	.proc	04
ee_printf:
	save	%sp, -1320, %sp
	st	%i3, [%fp+80]
	st	%i5, [%fp+88]
	add	%fp, 72, %l2
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i4, [%fp+84]
	st	%l2, [%fp-1204]
	ldub	[%i0], %g2
	add	%fp, -1024, %i3
	sll	%g2, 24, %g1
	cmp	%g1, 0
	be	.L163
	 mov	%i3, %i5
	sethi	%hi(538976256), %l1
	sethi	%hi(-16712704), %l0
	sethi	%hi(-65536), %i1
	sethi	%hi(808464384), %i2
	or	%l1, 32, %l1
	or	%l0, 1023, %l0
	or	%i1, 255, %i1
	b	.L413
	 or	%i2, 48, %i2
.L620:
	add	%i5, 1, %i5
	ldub	[%i0+1], %g2
.L165:
	sll	%g2, 24, %g1
	cmp	%g1, 0
	be	.L163
	 add	%i0, 1, %i0
.L413:
	sra	%g1, 24, %g1
	cmp	%g1, 37
	bne,a	.L620
	 stb	%g2, [%i5]
	mov	0, %o5
	sethi	%hi(.L172), %i4
.L164:
	ldub	[%i0+1], %g1
	add	%g1, -32, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 16
	bleu	.L621
	 add	%i0, 1, %g2
.L166:
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bgu	.L174
	 sll	%g1, 24, %g3
	mov	0, %i4
.L175:
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
	bleu	.L175
	 add	%i4, -48, %i4
.L611:
	sll	%g1, 24, %g3
	mov	%g2, %i0
	sra	%g3, 24, %g3
	cmp	%g3, 46
	be	.L622
	 mov	-1, %l3
.L178:
	and	%g1, -33, %g2
	sll	%g2, 24, %g2
	sra	%g2, 24, %g2
	cmp	%g2, 76
	bne	.L183
	 mov	-1, %g3
	sll	%g1, 24, %g3
	ldub	[%i0+1], %g1
	sra	%g3, 24, %g3
	add	%i0, 1, %i0
.L183:
	add	%g1, -65, %g2
	and	%g2, 0xff, %g2
	cmp	%g2, 55
	bleu	.L623
	 sll	%g2, 2, %g2
.L184:
	sll	%g1, 24, %g2
	sra	%g2, 24, %g2
	cmp	%g2, 37
	be,a	.L647
	 stb	%g1, [%i5]
	mov	37, %g1
	stb	%g1, [%i5]
	add	%i5, 1, %i5
	ldsb	[%i0], %g2
	cmp	%g2, 0
	be	.L163
	 ldub	[%i0], %g1
	stb	%g1, [%i5]
.L647:
	add	%i5, 1, %i5
	ldub	[%i0+1], %g2
	sll	%g2, 24, %g1
	cmp	%g1, 0
	bne	.L413
	 add	%i0, 1, %i0
.L163:
	stb	%g0, [%i5]
	ldub	[%fp-1024], %i5
	sll	%i5, 24, %i5
	cmp	%i5, 0
	be	.L685
	 mov	0, %i0
	sethi	%hi(-53248), %i4
	or	%i4, 512, %i4
.L601:
	call	__ajit_serial_putchar__, 0
	 sra	%i5, 24, %o0
	cmp	%o0, 0
	be	.L601
	 nop
.L513:
#APP
! 624 "/home/madhav/AjitToolChain/AjitPublicResources/tools/minimal_printf_timer/src/ee_printf.c" 1
	lda [%i4] 32, %g1
	
! 0 "" 2
#NO_APP
	and	%g1, 9, %g1
	cmp	%g1, 9
	be	.L513
	 nop
	add	%i0, 1, %i0
	ldub	[%i3+%i0], %i5
	sll	%i5, 24, %i5
	cmp	%i5, 0
	bne	.L601
	 nop
.L685:
	jmp	%i7+8
	 restore
.L621:
	or	%i4, %lo(.L172), %g4
	sll	%g3, 2, %g3
	ld	[%g4+%g3], %g3
	jmp	%g3
	 nop
	.section	".rodata"
	.section	".text"
.L171:
	or	%o5, 1, %o5
	b	.L164
	 mov	%g2, %i0
.L170:
	or	%o5, 16, %o5
	b	.L164
	 mov	%g2, %i0
.L169:
	or	%o5, 4, %o5
	b	.L164
	 mov	%g2, %i0
.L168:
	or	%o5, 32, %o5
	b	.L164
	 mov	%g2, %i0
.L167:
	or	%o5, 8, %o5
	b	.L164
	 mov	%g2, %i0
.L174:
	sra	%g3, 24, %g4
	cmp	%g4, 42
	be	.L624
	 sra	%g3, 24, %g3
	mov	%g2, %i0
	mov	-1, %i4
	cmp	%g3, 46
	bne	.L178
	 mov	-1, %l3
.L622:
	ldub	[%i0+1], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bgu	.L179
	 add	%i0, 1, %g2
	mov	0, %l3
.L180:
	add	%l3, %l3, %g3
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	sll	%l3, 3, %l3
	add	%g2, 1, %g2
	add	%g3, %l3, %l3
	add	%l3, %g1, %l3
	ldub	[%g2], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bleu	.L180
	 add	%l3, -48, %l3
.L181:
	b	.L178
	 mov	%g2, %i0
.L623:
	sethi	%hi(.L196), %g4
	or	%g4, %lo(.L196), %g4
	ld	[%g4+%g2], %g2
	jmp	%g2
	 nop
	.section	".rodata"
	.section	".text"
.L179:
	sll	%g1, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 42
	be	.L625
	 mov	0, %l3
	b	.L178
	 mov	%g2, %i0
.L185:
	or	%o5, 64, %o5
.L187:
	cmp	%g3, 108
	be	.L626
	 ld	[%l2], %g2
	ldub	[%g2], %g3
	cmp	%g3, 0
	be	.L273
	 add	%l2, 4, %l2
	cmp	%g3, 99
	ble	.L627
	 cmp	%g3, 9
	sra	%g3, 31, %o3
	wr	%o3, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 100, %g4
	smul	%g4, 100, %o7
	sethi	%hi(.LC0), %g1
	sub	%g3, %o7, %g3
	or	%g1, %lo(.LC0), %g1
	ldub	[%g1+%g4], %o7
	sra	%g3, 31, %o4
	wr	%o4, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %g4
	stb	%o7, [%fp-1104]
	ldub	[%g1+%g4], %o4
	add	%g4, %g4, %o7
	sll	%g4, 3, %g4
	add	%o7, %g4, %o7
	stb	%o4, [%fp-1103]
	sub	%g3, %o7, %g3
	mov	4, %g4
	mov	3, %o7
	mov	2, %o4
.L277:
	ldub	[%g1+%g3], %g1
	add	%fp, %o4, %o4
	stb	%g1, [%o4-1104]
	add	%fp, %o7, %o4
	mov	46, %g1
	stb	%g1, [%o4-1104]
	ldub	[%g2+1], %g3
	cmp	%g3, 0
	be	.L648
	 add	%fp, %g4, %g1
.L640:
	cmp	%g3, 99
	ble	.L628
	 cmp	%g3, 9
	sra	%g3, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 100, %o3
	add	%fp, %g4, %g4
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldub	[%g1+%o3], %o2
	smul	%o3, 100, %o3
	stb	%o2, [%g4-1104]
	sub	%g3, %o3, %g3
	add	%o7, 3, %g4
	sra	%g3, 31, %o3
	wr	%o3, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %o7
	ldub	[%g1+%o7], %o2
	add	%o7, %o7, %o3
	stb	%o2, [%o4-1102]
	sll	%o7, 3, %o7
	add	%o3, %o7, %o7
	sub	%g3, %o7, %g3
.L282:
	add	%fp, %g4, %o7
	ldub	[%g1+%g3], %g1
	stb	%g1, [%o7-1104]
	add	%g4, 1, %g4
	mov	46, %g1
	add	%fp, %g4, %o4
	stb	%g1, [%o4-1104]
	ldub	[%g2+2], %g3
	cmp	%g3, 0
	be	.L283
	 add	%g4, 1, %o7
.L641:
	cmp	%g3, 99
	ble	.L629
	 cmp	%g3, 9
	sra	%g3, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 100, %o3
	add	%fp, %o7, %o7
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldub	[%g1+%o3], %o2
	smul	%o3, 100, %o3
	stb	%o2, [%o7-1104]
	sub	%g3, %o3, %g3
	add	%g4, 3, %o7
	sra	%g3, 31, %o3
	wr	%o3, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %g4
	ldub	[%g1+%g4], %o2
	add	%g4, %g4, %o3
	stb	%o2, [%o4-1102]
	sll	%g4, 3, %g4
	add	%o3, %g4, %g4
	sub	%g3, %g4, %g3
.L287:
	ldub	[%g1+%g3], %g1
	add	%fp, %o7, %g4
	stb	%g1, [%g4-1104]
	add	%o7, 1, %g3
	mov	46, %g1
	add	%fp, %g3, %g4
	stb	%g1, [%g4-1104]
	ldub	[%g2+3], %g2
	cmp	%g2, 0
	be	.L288
	 add	%g3, 1, %o4
.L642:
	cmp	%g2, 99
	ble	.L630
	 cmp	%g2, 9
	sra	%g2, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g2, 100, %o7
	add	%fp, %o4, %o4
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldub	[%g1+%o7], %o3
	smul	%o7, 100, %o7
	stb	%o3, [%o4-1104]
	sub	%g2, %o7, %g2
	add	%g3, 3, %o4
	sra	%g2, 31, %o3
	wr	%o3, 0, %y
	nop
	nop
	nop
	sdiv	%g2, 10, %g3
	ldub	[%g1+%g3], %o3
	add	%g3, %g3, %o7
	stb	%o3, [%g4-1102]
	sll	%g3, 3, %g3
	add	%o7, %g3, %g3
	sub	%g2, %g3, %g2
.L292:
	add	%fp, %o4, %g3
	ldub	[%g1+%g2], %g1
	add	%o4, 1, %o4
	stb	%g1, [%g3-1104]
.L291:
	andcc	%o5, 16, %g0
	bne	.L649
	 orcc	%o4, 0, %o3
	cmp	%i4, %o4
	ble	.L442
	 add	%i4, -1, %g4
	sub	%i4, %o4, %i4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L294
	 mov	%i4, %g3
	mov	%g1, %g3
.L294:
	cmp	%i4, 3
	bleu,a	.L295
	 mov	%i4, %g3
.L295:
	cmp	%g3, 0
	be	.L296
	 mov	%i5, %g1
	mov	32, %o7
.L297:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L297
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L650
	 add	%i5, %i4, %i5
.L296:
	sub	%i4, %g3, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L299
	 add	%i5, %g3, %g3
	mov	0, %g2
.L300:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L300
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L298
	 sub	%g4, %o5, %g4
.L299:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L651:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, %o4
	bg,a	.L651
	 stb	%o7, [%g1+%g2]
.L298:
	add	%i5, %i4, %i5
.L650:
	add	%o4, -1, %i4
.L293:
	orcc	%o4, 0, %o3
.L649:
	ble,a	.L303
	 mov	1, %o3
.L303:
	srl	%o3, 2, %o5
	andcc	%i5, 3, %g0
	bne	.L444
	 sll	%o5, 2, %g1
	cmp	%g1, 0
	be	.L444
	 mov	0, %g2
	mov	0, %g3
	add	%fp, -1104, %g4
.L305:
	ld	[%g4+%g2], %o7
	st	%o7, [%i5+%g2]
	add	%g3, 1, %g3
	cmp	%o5, %g3
	bgu	.L305
	 add	%g2, 4, %g2
	cmp	%o3, %g1
	be	.L306
	 add	%i5, %g1, %g3
.L304:
	sub	%g3, %g1, %g3
	ldub	[%g4+%g1], %g2
.L652:
	stb	%g2, [%g3+%g1]
	add	%g1, 1, %g1
	cmp	%o4, %g1
	bg,a	.L652
	 ldub	[%g4+%g1], %g2
.L306:
	add	%i5, %o3, %i5
	cmp	%i4, %o4
	ble	.L619
	 add	%i4, -1, %g4
	sub	%i4, %o4, %i4
	sub	%g0, %i5, %g3
	and	%g3, 3, %g3
	cmp	%g3, %i4
	bgu,a	.L309
	 mov	%i4, %g3
.L309:
	cmp	%i4, 3
	bleu,a	.L310
	 mov	%i4, %g3
.L310:
	cmp	%g3, 0
	be	.L311
	 mov	%i5, %g1
	mov	32, %o7
.L312:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L312
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L653
	 add	%i5, %i4, %i5
.L311:
	sub	%i4, %g3, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L314
	 add	%i5, %g3, %g3
	mov	0, %g2
.L315:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L315
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L403
	 sub	%g4, %o5, %g4
.L314:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L654:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%o4, %g3
	bl,a	.L654
	 stb	%o7, [%g1+%g2]
.L403:
	add	%i5, %i4, %i5
.L619:
.L653:
	b	.L165
	 ldub	[%i0+1], %g2
.L186:
	or	%o5, 64, %o5
	mov	16, %o2
.L195:
	ld	[%l2], %o1
	mov	%i5, %o0
	mov	%i4, %o3
	call	number, 0
	 mov	%l3, %o4
	add	%l2, 4, %l2
	mov	%o0, %i5
	b	.L165
	 ldub	[%i0+1], %g2
.L193:
	ld	[%l2], %g4
	cmp	%g4, 0
	be	.L632
	 add	%l2, 4, %l2
.L218:
	ldsb	[%g4], %g1
	cmp	%g1, 0
	be	.L430
	 cmp	%l3, 0
	be,a	.L219
	 mov	0, %g3
	b	.L221
	 mov	%g4, %g3
.L220:
	be,a	.L219
	 sub	%g3, %g4, %g3
.L221:
	add	%g3, 1, %g3
	ldsb	[%g3], %g1
	cmp	%g1, 0
	bne,a	.L220
	 addcc	%l3, -1, %l3
	sub	%g3, %g4, %g3
.L219:
	andcc	%o5, 16, %g0
	bne	.L655
	 cmp	%g3, 0
	cmp	%i4, %g3
	ble	.L431
	 add	%i4, -1, %o5
	sub	%i4, %g3, %i4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L223
	 mov	%i4, %o7
	mov	%g1, %o7
.L223:
	cmp	%i4, 3
	bleu,a	.L224
	 mov	%i4, %o7
.L224:
	cmp	%o7, 0
	be	.L225
	 mov	%i5, %g1
	mov	32, %o4
.L226:
	stb	%o4, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%o7, %g2
	bgu	.L226
	 add	%o5, -1, %o5
	cmp	%i4, %o7
	be,a	.L656
	 add	%i5, %i4, %i5
.L225:
	sub	%i4, %o7, %o2
	srl	%o2, 2, %o4
	sll	%o4, 2, %o3
	cmp	%o3, 0
	be	.L228
	 add	%i5, %o7, %o7
	mov	0, %g2
.L229:
	st	%l1, [%o7]
	add	%g2, 1, %g2
	cmp	%g2, %o4
	blu	.L229
	 add	%o7, 4, %o7
	add	%g1, %o3, %g1
	cmp	%o2, %o3
	be	.L227
	 sub	%o5, %o3, %o5
.L228:
	mov	0, %g2
	add	%o5, 1, %o5
	mov	32, %o4
	stb	%o4, [%g1+%g2]
.L657:
	add	%g2, 1, %g2
	sub	%o5, %g2, %o7
	cmp	%g3, %o7
	bl,a	.L657
	 stb	%o4, [%g1+%g2]
.L227:
	add	%i5, %i4, %i5
.L656:
	add	%g3, -1, %i4
.L222:
	cmp	%g3, 0
.L655:
	ble	.L232
	 srl	%g3, 2, %o5
	add	%i5, 4, %g1
	cmp	%g4, %g1
	add	%g4, 4, %g1
	subx	%g0, -1, %g2
	cmp	%i5, %g1
	subx	%g0, -1, %g1
	or	%g2, %g1, %g2
	sll	%o5, 2, %o4
	cmp	%g3, 3
	bleu	.L633
	 mov	1, %g1
.L234:
	or	%i5, %g4, %o7
	and	%o7, 3, %o7
	subcc	%g0, %o7, %g0
	and	%g2, %g1, %g1
	subx	%g0, -1, %g2
	andcc	%g1, %g2, %g0
	be	.L433
	 cmp	%o4, 0
	be	.L433
	 mov	0, %g2
	mov	0, %g1
.L235:
	ld	[%g4+%g1], %o7
	st	%o7, [%i5+%g1]
	add	%g2, 1, %g2
	cmp	%o5, %g2
	bgu	.L235
	 add	%g1, 4, %g1
	mov	%o4, %g1
	add	%g4, %o4, %g4
	cmp	%g3, %g1
	be	.L236
	 add	%i5, %o4, %o4
.L233:
	sub	%g0, %g1, %g2
	add	%g4, %g2, %o5
	add	%o4, %g2, %o7
.L658:
	ldub	[%o5+%g1], %o5
	stb	%o5, [%o7+%g1]
	add	%g1, 1, %g1
	cmp	%g3, %g1
	bg	.L658
	 add	%g4, %g2, %o5
.L236:
	add	%i5, %g3, %i5
.L232:
	cmp	%i4, %g3
	ble	.L619
	 add	%i4, -1, %o7
	sub	%i4, %g3, %i4
	sub	%g0, %i5, %g4
	and	%g4, 3, %g4
	cmp	%g4, %i4
	bgu,a	.L239
	 mov	%i4, %g4
.L239:
	cmp	%i4, 3
	bleu,a	.L240
	 mov	%i4, %g4
.L240:
	cmp	%g4, 0
	be	.L241
	 mov	%i5, %g1
	mov	32, %o5
.L242:
	stb	%o5, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g4, %g2
	bgu	.L242
	 add	%o7, -1, %o7
	cmp	%i4, %g4
	be,a	.L653
	 add	%i5, %i4, %i5
.L241:
	sub	%i4, %g4, %o3
	srl	%o3, 2, %o5
	sll	%o5, 2, %o4
	cmp	%o4, 0
	be	.L244
	 add	%i5, %g4, %g4
	mov	0, %g2
.L245:
	st	%l1, [%g4]
	add	%g2, 1, %g2
	cmp	%g2, %o5
	blu	.L245
	 add	%g4, 4, %g4
	add	%g1, %o4, %g1
	cmp	%o3, %o4
	be	.L403
	 sub	%o7, %o4, %o7
.L244:
	mov	0, %g2
	add	%o7, 1, %o7
	mov	32, %o5
	stb	%o5, [%g1+%g2]
.L659:
	add	%g2, 1, %g2
	sub	%o7, %g2, %g4
	cmp	%g3, %g4
	bl,a	.L659
	 stb	%o5, [%g1+%g2]
	b	.L619
	 add	%i5, %i4, %i5
.L192:
	cmp	%i4, -1
	be,a	.L635
	 or	%o5, 1, %o5
.L248:
	ld	[%l2], %o1
	mov	%i5, %o0
	mov	16, %o2
	mov	%i4, %o3
	call	number, 0
	 mov	%l3, %o4
	add	%l2, 4, %l2
	mov	%o0, %i5
	b	.L165
	 ldub	[%i0+1], %g2
.L191:
	b	.L195
	 mov	8, %o2
.L190:
	mov	%l2, %o1
	st	%o5, [%fp-1212]
	add	%fp, -1192, %o0
	call	memcpy, 0
	 mov	8, %o2
	ld	[%fp-1212], %o5
	add	%l2, 8, %l2
	andcc	%o5, 16, %g0
	be	.L613
	 ldd	[%fp-1192], %f8
	and	%o5, -2, %o5
.L613:
	or	%o5, 2, %l5
	and	%l5, 1, %g1
	subcc	%g0, %g1, %g0
	sethi	%hi(.LC3), %g1
	addx	%g0, -1, %l4
	ldd	[%g1+%lo(.LC3)], %f10
	and	%l4, 240, %l4
	fcmped	%f8, %f10
	nop
	fbl	.L636
	 add	%l4, 48, %l4
	andcc	%l5, 4, %g0
	be	.L324
	 andcc	%l5, 8, %g0
	add	%i4, -1, %i4
	mov	43, %l6
.L323:
	cmp	%l3, -1
	be,a	.L325
	 mov	6, %l3
.L325:
	std	%f8, [%fp-1224]
	mov	%l3, %o2
	ldd	[%fp-1224], %o0
	add	%fp, -1200, %o3
	add	%fp, -1196, %o4
	call	fcvtbuf, 0
	 add	%fp, -1104, %o5
	ld	[%fp-1196], %g2
	cmp	%g2, 0
	be	.L326
	 add	%fp, -1184, %g1
	mov	45, %g2
	add	%fp, -1183, %g1
	stb	%g2, [%fp-1184]
.L326:
	ldsb	[%o0], %g2
	cmp	%g2, 0
	bne	.L638
	 ldub	[%o0], %o5
	mov	48, %g2
	cmp	%l3, 0
	be	.L343
	 stb	%g2, [%g1]
	mov	46, %g2
	stb	%g2, [%g1+1]
	orcc	%l3, 0, %g4
	ble	.L639
	 add	%g1, 2, %g1
.L344:
	sub	%g0, %g1, %g2
	and	%g2, 3, %g2
	cmp	%g4, %g2
	bleu	.L345
	 mov	%g4, %o7
	mov	%g2, %o7
.L345:
	cmp	%g4, 3
	bleu,a	.L346
	 mov	%g4, %o7
.L346:
	mov	%g1, %g2
	cmp	%o7, 0
	be	.L347
	 mov	0, %g3
	mov	48, %o5
.L348:
	stb	%o5, [%g2]
	add	%g3, 1, %g3
	cmp	%o7, %g3
	bgu	.L348
	 add	%g2, 1, %g2
	cmp	%g4, %o7
	be,a	.L617
	 stb	%g0, [%g1+%g4]
.L347:
	sub	%g4, %o7, %o2
	srl	%o2, 2, %o3
	sll	%o3, 2, %o4
	cmp	%o4, 0
	be	.L350
	 add	%g1, %o7, %o7
	mov	0, %o5
.L351:
	st	%i2, [%o7]
	add	%o5, 1, %o5
	cmp	%o5, %o3
	blu	.L351
	 add	%o7, 4, %o7
	add	%g2, %o4, %g2
	cmp	%o2, %o4
	be	.L349
	 add	%g3, %o4, %g3
.L350:
	mov	48, %o7
	sub	%g2, %g3, %g2
	stb	%o7, [%g2+%g3]
.L660:
	add	%g3, 1, %g3
	cmp	%l3, %g3
	bg,a	.L660
	 stb	%o7, [%g2+%g3]
.L349:
	stb	%g0, [%g1+%g4]
.L617:
	ldub	[%fp-1184], %g1
.L646:
	sll	%g1, 24, %g1
	cmp	%g1, 0
	be,a	.L661
	 mov	0, %o4
.L358:
	add	%fp, -1184, %g4
.L681:
	add	%fp, -928, %g2
	b	.L370
	 mov	%g4, %o4
.L369:
	be,a	.L661
	 sub	%o4, %g4, %o4
.L370:
	add	%o4, 1, %o4
	ldsb	[%o4], %g1
	cmp	%g1, 0
	bne	.L369
	 cmp	%o4, %g2
	sub	%o4, %g4, %o4
.L368:
.L661:
	andcc	%l5, 17, %g0
	bne	.L371
	 sub	%i4, %o4, %i4
	cmp	%i4, 0
	ble	.L455
	 add	%i4, -1, %g4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L372
	 mov	%i4, %g3
	mov	%g1, %g3
.L372:
	cmp	%i4, 3
	bleu,a	.L373
	 mov	%i4, %g3
.L373:
	cmp	%g3, 0
	be	.L374
	 mov	%i5, %g1
	mov	32, %o7
.L375:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L375
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L662
	 add	%i5, %i4, %i5
.L374:
	sub	%i4, %g3, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L377
	 add	%i5, %g3, %g3
	mov	0, %g2
.L378:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L378
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L376
	 sub	%g4, %o5, %g4
.L377:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L663:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, 0
	bg,a	.L663
	 stb	%o7, [%g1+%g2]
.L376:
	add	%i5, %i4, %i5
.L662:
	mov	-1, %i4
.L371:
	andcc	%l6, 0xff, %g0
	be	.L664
	 andcc	%l5, 16, %g0
	stb	%l6, [%i5]
	add	%i5, 1, %i5
.L664:
	bne	.L665
	 cmp	%o4, 0
	cmp	%i4, 0
	ble	.L457
	 add	%i4, -1, %g4
	sub	%g0, %i5, %g3
	and	%g3, 3, %g3
	cmp	%g3, %i4
	bgu,a	.L383
	 mov	%i4, %g3
.L383:
	cmp	%i4, 3
	bleu,a	.L384
	 mov	%i4, %g3
.L384:
	cmp	%g3, 0
	be	.L385
	 mov	%i5, %g1
.L386:
	stb	%l4, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L386
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L666
	 add	%i5, %i4, %i5
.L385:
	sub	%i4, %g3, %o2
	srl	%o2, 2, %o7
	sll	%o7, 2, %o3
	cmp	%o3, 0
	be	.L388
	 add	%i5, %g3, %g3
	and	%l4, 0xff, %o5
	sll	%o5, 16, %g2
	sll	%o5, 24, %o0
	sll	%o5, 8, %o1
	and	%o0, %l0, %o0
	or	%o0, %g2, %o0
	mov	0, %g2
	and	%o0, %i1, %o0
	or	%o0, %o1, %o1
	or	%o1, %o5, %o5
.L389:
	st	%o5, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L389
	 add	%g3, 4, %g3
	add	%g1, %o3, %g1
	cmp	%o2, %o3
	be	.L387
	 sub	%g4, %o3, %g4
.L388:
	mov	0, %g2
	add	%g4, 1, %g4
	stb	%l4, [%g1+%g2]
.L667:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, 0
	bg,a	.L667
	 stb	%l4, [%g1+%g2]
.L387:
	add	%i5, %i4, %i5
.L666:
	mov	-1, %i4
.L382:
	cmp	%o4, 0
.L665:
	ble	.L668
	 cmp	%i4, 0
	and	%i5, 3, %g1
	subcc	%g0, %g1, %g0
	srl	%o4, 2, %o5
	subx	%g0, -1, %g3
	sll	%o5, 2, %g1
	cmp	%o4, 3
	bgu	.L394
	 mov	1, %g2
	mov	0, %g2
.L394:
	andcc	%g3, %g2, %g0
	be	.L459
	 cmp	%g1, 0
	be	.L459
	 mov	0, %g2
	mov	0, %g3
	add	%fp, -1184, %g4
.L395:
	ld	[%g4+%g2], %o7
	st	%o7, [%i5+%g2]
	add	%g3, 1, %g3
	cmp	%o5, %g3
	bgu	.L395
	 add	%g2, 4, %g2
	cmp	%o4, %g1
	be	.L396
	 add	%i5, %g1, %g3
.L393:
	sub	%g3, %g1, %g3
	ldub	[%g4+%g1], %g2
.L669:
	stb	%g2, [%g3+%g1]
	add	%g1, 1, %g1
	cmp	%o4, %g1
	bg,a	.L669
	 ldub	[%g4+%g1], %g2
.L396:
	add	%i5, %o4, %i5
	cmp	%i4, 0
.L668:
	ble	.L619
	 add	%i4, -1, %g4
	sub	%g0, %i5, %g3
	and	%g3, 3, %g3
	cmp	%g3, %i4
	bgu,a	.L399
	 mov	%i4, %g3
.L399:
	cmp	%i4, 3
	bleu,a	.L400
	 mov	%i4, %g3
.L400:
	cmp	%g3, 0
	be	.L401
	 mov	%i5, %g1
	mov	32, %o7
.L402:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L402
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L653
	 add	%i5, %i4, %i5
.L401:
	sub	%i4, %g3, %o4
	srl	%o4, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L404
	 add	%i5, %g3, %g3
	mov	0, %g2
.L405:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L405
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o4, %o5
	be	.L403
	 sub	%g4, %o5, %g4
.L404:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L670:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, 0
	bg,a	.L670
	 stb	%o7, [%g1+%g2]
	b	.L619
	 add	%i5, %i4, %i5
.L424:
	b	.L195
	 mov	16, %o2
.L194:
	b	.L195
	 mov	10, %o2
.L189:
	or	%o5, 2, %o5
	b	.L195
	 mov	10, %o2
.L188:
	andcc	%o5, 16, %g0
	bne,a	.L671
	 ld	[%l2], %g1
	add	%i4, -1, %i4
	orcc	%i4, 0, %g2
	ble	.L197
	 sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L198
	 mov	%i4, %g4
	mov	%g1, %g4
.L198:
	cmp	%i4, 3
	bleu,a	.L199
	 mov	%i4, %g4
.L199:
	cmp	%g4, 0
	be	.L200
	 mov	%i5, %g1
	mov	32, %o7
.L201:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g3
	cmp	%g4, %g3
	bgu	.L201
	 add	%g2, -1, %g2
	cmp	%i4, %g4
	be,a	.L672
	 ld	[%l2], %g2
.L200:
	sub	%i4, %g4, %o4
	srl	%o4, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L206
	 mov	0, %g3
	add	%i5, %g4, %g4
.L204:
	st	%l1, [%g4]
	add	%g3, 1, %g3
	cmp	%g3, %o7
	blu	.L204
	 add	%g4, 4, %g4
	add	%g1, %o5, %g1
	cmp	%o4, %o5
	be	.L202
	 sub	%g2, %o5, %g2
.L206:
	mov	32, %g3
.L514:
	stb	%g3, [%g1]
	add	%g2, -1, %g2
	cmp	%g2, 0
	bg	.L514
	 add	%g1, 1, %g1
.L202:
	ld	[%l2], %g2
.L672:
	add	%i5, %i4, %g1
	stb	%g2, [%i5+%i4]
	add	%l2, 4, %l2
	add	%g1, 1, %i5
	b	.L165
	 ldub	[%i0+1], %g2
.L624:
	ld	[%l2], %i4
	add	%i0, 2, %g2
	add	%l2, 4, %l2
	cmp	%i4, 0
	bge	.L611
	 ldub	[%i0+2], %g1
	sub	%g0, %i4, %i4
	b	.L611
	 or	%o5, 16, %o5
.L273:
	mov	48, %g1
	stb	%g1, [%fp-1104]
	mov	1, %o7
	mov	46, %g1
	add	%fp, %o7, %o4
	stb	%g1, [%o4-1104]
	ldub	[%g2+1], %g3
	cmp	%g3, 0
	bne	.L640
	 mov	2, %g4
	add	%fp, %g4, %g1
.L648:
	mov	48, %g3
	stb	%g3, [%g1-1104]
	add	%o7, 2, %g4
	mov	46, %g1
	add	%fp, %g4, %o4
	stb	%g1, [%o4-1104]
	ldub	[%g2+2], %g3
	cmp	%g3, 0
	bne	.L641
	 add	%g4, 1, %o7
.L283:
	mov	48, %g1
	add	%fp, %o7, %o7
	stb	%g1, [%o7-1104]
	add	%g4, 2, %g3
	mov	46, %g1
	add	%fp, %g3, %g4
	stb	%g1, [%g4-1104]
	ldub	[%g2+3], %g2
	cmp	%g2, 0
	bne	.L642
	 add	%g3, 1, %o4
.L288:
	add	%fp, %o4, %g1
	mov	48, %g2
	add	%g3, 2, %o4
	b	.L291
	 stb	%g2, [%g1-1104]
.L197:
	ld	[%l2], %g1
.L671:
	stb	%g1, [%i5]
	add	%i4, -1, %i4
	add	%i5, 1, %o4
	orcc	%i4, 0, %g2
	ble	.L439
	 add	%l2, 4, %l2
	sub	%g0, %o4, %g4
	and	%g4, 3, %g4
	cmp	%g4, %i4
	bgu,a	.L209
	 mov	%i4, %g4
.L209:
	cmp	%i4, 3
	bleu,a	.L210
	 mov	%i4, %g4
.L210:
	cmp	%g4, 0
	be	.L211
	 mov	%o4, %g1
	xnor	%g0, %i5, %o5
	mov	32, %o7
.L212:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	add	%g1, %o5, %g3
	cmp	%g4, %g3
	bgu	.L212
	 add	%g2, -1, %g2
	cmp	%i4, %g4
	be,a	.L673
	 add	%o4, %i4, %i5
.L211:
	sub	%i4, %g4, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L217
	 add	%g4, 1, %g4
	mov	0, %g3
	add	%i5, %g4, %i5
.L215:
	st	%l1, [%i5]
	add	%g3, 1, %g3
	cmp	%g3, %o7
	blu	.L215
	 add	%i5, 4, %i5
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L213
	 sub	%g2, %o5, %g2
.L217:
	mov	32, %g3
.L515:
	stb	%g3, [%g1]
	add	%g2, -1, %g2
	cmp	%g2, 0
	bg	.L515
	 add	%g1, 1, %g1
.L213:
	add	%o4, %i4, %i5
.L673:
	b	.L165
	 ldub	[%i0+1], %g2
.L633:
	b	.L234
	 mov	0, %g1
.L635:
	b	.L248
	 mov	8, %i4
.L626:
	andcc	%o5, 64, %g0
	be	.L435
	 add	%l2, 4, %l2
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %g1
.L250:
	ldub	[%g2], %g4
	and	%g4, 0xff, %o7
	and	%g4, 15, %g4
	ldub	[%g1+%g4], %g4
	mov	58, %g3
	stb	%g4, [%fp-1103]
	stb	%g3, [%fp-1102]
	srl	%o7, 4, %o7
	ldub	[%g1+%o7], %o7
	stb	%o7, [%fp-1104]
	ldub	[%g2+1], %g4
	and	%g4, 0xff, %o4
	and	%g4, 15, %g4
	srl	%o4, 4, %o4
	ldub	[%g1+%g4], %o7
	ldub	[%g1+%o4], %g4
	stb	%g3, [%fp-1099]
	stb	%o7, [%fp-1100]
	stb	%g4, [%fp-1101]
	ldub	[%g2+2], %g4
	and	%g4, 0xff, %o4
	and	%g4, 15, %g4
	srl	%o4, 4, %o4
	ldub	[%g1+%g4], %o7
	ldub	[%g1+%o4], %g4
	stb	%g3, [%fp-1096]
	stb	%o7, [%fp-1097]
	stb	%g4, [%fp-1098]
	ldub	[%g2+3], %g4
	and	%g4, 0xff, %o4
	and	%g4, 15, %g4
	srl	%o4, 4, %o4
	ldub	[%g1+%g4], %o7
	ldub	[%g1+%o4], %g4
	stb	%g3, [%fp-1093]
	stb	%o7, [%fp-1094]
	stb	%g4, [%fp-1095]
	ldub	[%g2+4], %g4
	stb	%g3, [%fp-1090]
	and	%g4, 0xff, %g3
	srl	%g3, 4, %g3
	ldub	[%g1+%g3], %g3
	and	%g4, 15, %g4
	stb	%g3, [%fp-1092]
	ldub	[%g1+%g4], %g4
	stb	%g4, [%fp-1091]
	ldub	[%g2+5], %g2
	and	%g2, 0xff, %g3
	srl	%g3, 4, %g3
	ldub	[%g1+%g3], %g3
	stb	%g3, [%fp-1089]
	and	%g2, 15, %g2
	andcc	%o5, 16, %g0
	ldub	[%g1+%g2], %g1
	bne	.L251
	 stb	%g1, [%fp-1088]
	cmp	%i4, 17
	ble	.L436
	 add	%i4, -1, %g4
	add	%i4, -17, %i4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bgu	.L643
	 mov	%i4, %g3
.L252:
	cmp	%i4, 3
	bleu,a	.L253
	 mov	%i4, %g3
.L253:
	cmp	%g3, 0
	be	.L254
	 mov	%i5, %g1
	mov	32, %o7
.L255:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L255
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L674
	 add	%i5, %i4, %i5
.L254:
	sub	%i4, %g3, %o4
	srl	%o4, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L257
	 add	%i5, %g3, %g3
	mov	0, %g2
.L258:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L258
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o4, %o5
	be	.L256
	 sub	%g4, %o5, %g4
.L257:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L675:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, 17
	bg,a	.L675
	 stb	%o7, [%g1+%g2]
.L256:
	add	%i5, %i4, %i5
.L674:
	mov	16, %i4
.L251:
	andcc	%i5, 3, %g0
	bne	.L438
	 ld	[%fp-1104], %g1
	st	%g1, [%i5]
	ld	[%fp-1100], %g1
	st	%g1, [%i5+4]
	ld	[%fp-1096], %g1
	add	%i5, 16, %g3
	st	%g1, [%i5+8]
	mov	1, %o7
	ld	[%fp-1092], %g1
	mov	16, %g2
	st	%g1, [%i5+12]
.L261:
	mov	%g2, %g1
	add	%g2, %o7, %o7
	sub	%g3, %g2, %g3
	add	%fp, -1104, %g4
	ldub	[%g4+%g1], %g2
.L676:
	stb	%g2, [%g3+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %o7
	bne,a	.L676
	 ldub	[%g4+%g1], %g2
	add	%i5, 17, %o4
	cmp	%i4, 17
	ble	.L439
	 add	%i4, -1, %g3
	add	%i4, -17, %i4
	sub	%g0, %o4, %g4
	and	%g4, 3, %g4
	cmp	%g4, %i4
	bgu,a	.L264
	 mov	%i4, %g4
.L264:
	cmp	%i4, 3
	bleu,a	.L265
	 mov	%i4, %g4
.L265:
	cmp	%g4, 0
	be	.L266
	 mov	%o4, %g1
	mov	-17, %o7
	mov	32, %o5
	sub	%o7, %i5, %o7
.L267:
	stb	%o5, [%g1]
	add	%g1, 1, %g1
	add	%g1, %o7, %g2
	cmp	%g4, %g2
	bgu	.L267
	 add	%g3, -1, %g3
	cmp	%i4, %g4
	be,a	.L677
	 add	%o4, %i4, %i5
.L266:
	sub	%i4, %g4, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L269
	 add	%g4, 17, %g4
	mov	0, %g2
	add	%i5, %g4, %i5
.L270:
	st	%l1, [%i5]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L270
	 add	%i5, 4, %i5
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L268
	 sub	%g3, %o5, %g3
.L269:
	mov	0, %g2
	add	%g3, 1, %g3
	mov	32, %i5
	stb	%i5, [%g1+%g2]
.L678:
	add	%g2, 1, %g2
	sub	%g3, %g2, %g4
	cmp	%g4, 17
	bg,a	.L678
	 stb	%i5, [%g1+%g2]
.L268:
	add	%o4, %i4, %i5
.L677:
	b	.L165
	 ldub	[%i0+1], %g2
.L625:
	ld	[%l2], %l3
	add	%i0, 2, %g2
	add	%l2, 4, %l2
	cmp	%l3, 0
	bge	.L181
	 ldub	[%i0+2], %g1
	mov	0, %l3
	b	.L178
	 mov	%g2, %i0
.L629:
	bg,a	.L606
	 add	%fp, %o7, %o7
	sethi	%hi(.LC0), %g1
	b	.L287
	 or	%g1, %lo(.LC0), %g1
.L628:
	bg,a	.L604
	 add	%fp, %g4, %g4
	sethi	%hi(.LC0), %g1
	b	.L282
	 or	%g1, %lo(.LC0), %g1
.L630:
	bg,a	.L608
	 add	%fp, %o4, %o4
	sethi	%hi(.LC0), %g1
	b	.L292
	 or	%g1, %lo(.LC0), %g1
.L627:
	ble,a	.L441
	 sethi	%hi(.LC0), %g1
	sra	%g3, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %g4
	sethi	%hi(.LC0), %g1
	sll	%g4, 3, %o4
	add	%g4, %g4, %o3
	or	%g1, %lo(.LC0), %g1
	ldub	[%g1+%g4], %o7
	add	%o3, %o4, %g4
	stb	%o7, [%fp-1104]
	sub	%g3, %g4, %g3
	mov	2, %o7
	mov	3, %g4
	b	.L277
	 mov	1, %o4
.L435:
	sethi	%hi(.LC0), %g1
	b	.L250
	 or	%g1, %lo(.LC0), %g1
.L324:
	be	.L323
	 mov	0, %l6
	add	%i4, -1, %i4
	b	.L323
	 mov	32, %l6
.L604:
	sra	%g3, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %o4
	sethi	%hi(.LC0), %g1
	add	%o4, %o4, %o1
	or	%g1, %lo(.LC0), %g1
	sll	%o4, 3, %o2
	ldub	[%g1+%o4], %o3
	add	%o1, %o2, %o4
	stb	%o3, [%g4-1104]
	sub	%g3, %o4, %g3
	b	.L282
	 add	%o7, 2, %g4
.L606:
	sra	%g3, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %o4
	sethi	%hi(.LC0), %g1
	add	%o4, %o4, %o1
	or	%g1, %lo(.LC0), %g1
	sll	%o4, 3, %o2
	ldub	[%g1+%o4], %o3
	add	%o1, %o2, %o4
	stb	%o3, [%o7-1104]
	sub	%g3, %o4, %g3
	b	.L287
	 add	%g4, 2, %o7
.L608:
	sra	%g2, 31, %o7
	wr	%o7, 0, %y
	nop
	nop
	nop
	sdiv	%g2, 10, %g4
	sethi	%hi(.LC0), %g1
	add	%g4, %g4, %o2
	or	%g1, %lo(.LC0), %g1
	sll	%g4, 3, %o3
	ldub	[%g1+%g4], %o7
	add	%o2, %o3, %g4
	stb	%o7, [%o4-1104]
	sub	%g2, %g4, %g2
	b	.L292
	 add	%g3, 2, %o4
.L441:
	mov	2, %g4
	mov	1, %o7
	mov	0, %o4
	b	.L277
	 or	%g1, %lo(.LC0), %g1
.L636:
	fnegs	%f8, %f8
	add	%i4, -1, %i4
	b	.L323
	 mov	45, %l6
.L643:
	b	.L252
	 mov	%g1, %g3
.L638:
	ld	[%fp-1200], %g3
	mov	%o0, %g2
	cmp	%g3, 0
	bg	.L518
	 mov	46, %o7
	b	.L645
	 mov	48, %g2
.L341:
	stb	%o5, [%g1]
.L679:
	add	%g2, 1, %g2
	add	%g1, 1, %g1
	ldsb	[%g2], %g4
	cmp	%g4, 0
	be	.L340
	 ldub	[%g2], %o5
.L518:
	sub	%g2, %o0, %g4
	cmp	%g3, %g4
	bne,a	.L679
	 stb	%o5, [%g1]
	stb	%o7, [%g1]
	b	.L341
	 add	%g1, 1, %g1
.L645:
	stb	%g2, [%g1]
	mov	46, %g2
	stb	%g2, [%g1+1]
	subcc	%g0, %g3, %g2
	be	.L517
	 add	%g1, 2, %g1
	sub	%g0, %g1, %g3
	and	%g3, 3, %g3
	cmp	%g3, %g2
	bgu,a	.L330
	 mov	%g2, %g3
.L330:
	cmp	%g2, 3
	bleu,a	.L331
	 mov	%g2, %g3
.L331:
	mov	%g1, %g4
	cmp	%g3, 0
	be	.L332
	 mov	0, %o7
	mov	48, %o4
.L333:
	stb	%o4, [%g4]
	add	%o7, 1, %o7
	cmp	%g3, %o7
	bgu	.L333
	 add	%g4, 1, %g4
	cmp	%g2, %g3
	be,a	.L517
	 add	%g1, %g2, %g1
.L332:
	sub	%g2, %g3, %o2
	srl	%o2, 2, %o1
	sll	%o1, 2, %o4
	cmp	%o4, 0
	be	.L335
	 add	%g1, %g3, %g3
	mov	0, %o3
.L336:
	st	%i2, [%g3]
	add	%o3, 1, %o3
	cmp	%o3, %o1
	blu	.L336
	 add	%g3, 4, %g3
	add	%g4, %o4, %g4
	cmp	%o2, %o4
	be	.L334
	 add	%o7, %o4, %o7
.L335:
	mov	48, %g3
	sub	%g4, %o7, %g4
	stb	%g3, [%g4+%o7]
.L680:
	add	%o7, 1, %o7
	cmp	%g2, %o7
	bg,a	.L680
	 stb	%g3, [%g4+%o7]
.L334:
	add	%g1, %g2, %g1
.L517:
	stb	%o5, [%g1]
	add	%o0, 1, %o0
	add	%g1, 1, %g1
	ldsb	[%o0], %g2
	cmp	%g2, 0
	bne	.L517
	 ldub	[%o0], %o5
.L340:
	andcc	%l5, 32, %g0
	be	.L617
	 stb	%g0, [%g1]
	cmp	%l3, 0
	bne	.L646
	 ldub	[%fp-1184], %g1
.L356:
	ldsb	[%fp-1184], %g1
	cmp	%g1, 0
	be	.L452
	 ldub	[%fp-1184], %g2
	cmp	%g1, 46
	be	.L358
	 and	%g2, -33, %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 69
	be	.L453
	 add	%fp, -1184, %g2
	b	.L360
	 add	%fp, -1183, %g1
.L361:
	cmp	%g3, 46
	be,a	.L681
	 add	%fp, -1184, %g4
	and	%g4, -33, %g3
	sll	%g3, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 69
	be	.L359
	 add	%g1, 1, %g1
.L360:
	ldsb	[%g1], %g3
	mov	%g1, %g2
	cmp	%g3, 0
	bne	.L361
	 ldub	[%g1], %g4
	stb	%g0, [%g2+1]
.L616:
	mov	46, %g1
.L683:
	b	.L617
	 stb	%g1, [%g2]
.L632:
	sethi	%hi(.LC2), %g4
	b	.L218
	 or	%g4, %lo(.LC2), %g4
.L442:
	b	.L293
	 mov	%g4, %i4
.L430:
	b	.L219
	 mov	0, %g3
.L455:
	b	.L371
	 mov	%g4, %i4
.L431:
	b	.L222
	 mov	%o5, %i4
.L439:
	mov	%o4, %i5
	b	.L165
	 ldub	[%i0+1], %g2
.L457:
	b	.L382
	 mov	%g4, %i4
.L436:
	b	.L251
	 mov	%g4, %i4
.L453:
.L359:
	add	%g2, 256, %g4
	b	.L364
	 mov	%g2, %g1
.L362:
	be,a	.L682
	 sub	%g1, %g2, %g1
.L364:
	add	%g1, 1, %g1
	ldsb	[%g1], %g3
	cmp	%g3, 0
	bne	.L362
	 cmp	%g1, %g4
	sub	%g1, %g2, %g1
.L682:
	cmp	%g1, 0
	ble,a	.L683
	 mov	46, %g1
.L516:
	ldub	[%g2+%g1], %g4
	add	%g2, %g1, %g3
	addcc	%g1, -1, %g1
	bne	.L516
	 stb	%g4, [%g3+1]
	mov	46, %g1
	b	.L617
	 stb	%g1, [%g2]
.L444:
	mov	%i5, %g3
	mov	0, %g1
	b	.L304
	 add	%fp, -1104, %g4
.L438:
	mov	%i5, %g3
	mov	17, %o7
	b	.L261
	 mov	0, %g2
.L452:
	add	%fp, -1184, %g2
	b	.L616
	 stb	%g0, [%g2+1]
.L459:
	mov	%i5, %g3
	mov	0, %g1
	b	.L393
	 add	%fp, -1184, %g4
.L433:
	mov	%i5, %o4
	b	.L233
	 mov	0, %g1
.L639:
	b	.L344
	 mov	1, %g4
.L343:
	andcc	%l5, 32, %g0
	bne	.L356
	 stb	%g0, [%g1+1]
	b	.L646
	 ldub	[%fp-1184], %g1
	.align 4
	.subsection	-1
	.align 4
.L196:
	.word	.L185
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L186
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L187
	.word	.L184
	.word	.L188
	.word	.L189
	.word	.L184
	.word	.L190
	.word	.L184
	.word	.L184
	.word	.L189
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L184
	.word	.L191
	.word	.L192
	.word	.L184
	.word	.L184
	.word	.L193
	.word	.L184
	.word	.L194
	.word	.L184
	.word	.L184
	.word	.L424
	.previous
	.subsection	-1
	.align 4
.L172:
	.word	.L167
	.word	.L166
	.word	.L166
	.word	.L168
	.word	.L166
	.word	.L166
	.word	.L166
	.word	.L166
	.word	.L166
	.word	.L166
	.word	.L166
	.word	.L169
	.word	.L166
	.word	.L170
	.word	.L166
	.word	.L166
	.word	.L171
	.previous
	.size	ee_printf, .-ee_printf
	.ident	"GCC: (Buildroot 2014.08-g9d8f423-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
