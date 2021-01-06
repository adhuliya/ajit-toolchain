	.file	"ee_printf.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.asciz	"0123456789abcdefghijklmnopqrstuvwxyz"
	.align 8
.LC1:
	.asciz	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	.section	.text.number,"ax",@progbits
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
	.section	.text.uart_send_char,"ax",@progbits
	.align 4
	.global uart_send_char
	.type	uart_send_char, #function
	.proc	020
uart_send_char:
	save	%sp, -96, %sp
.L134:
	call	__ajit_serial_putchar__, 0
	 mov	%i0, %o0
	cmp	%o0, 0
	be	.L134
	 sethi	%hi(-53248), %g2
	or	%g2, 512, %g2
.L140:
#APP
! 624 "/usr/local/ajit_release/tools/minimal_printf_timer/src/ee_printf.c" 1
	lda [%g2] 32, %g1
	
! 0 "" 2
#NO_APP
	and	%g1, 9, %g1
	cmp	%g1, 9
	be	.L140
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
	.section	.text.ee_printf,"ax",@progbits
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
	be	.L146
	 mov	%i3, %i5
	sethi	%hi(538976256), %l1
	sethi	%hi(-16712704), %l0
	sethi	%hi(-65536), %i1
	sethi	%hi(808464384), %i2
	or	%l1, 32, %l1
	or	%l0, 1023, %l0
	or	%i1, 255, %i1
	b	.L396
	 or	%i2, 48, %i2
.L603:
	add	%i5, 1, %i5
	ldub	[%i0+1], %g2
.L148:
	sll	%g2, 24, %g1
	cmp	%g1, 0
	be	.L146
	 add	%i0, 1, %i0
.L396:
	sra	%g1, 24, %g1
	cmp	%g1, 37
	bne,a	.L603
	 stb	%g2, [%i5]
	mov	0, %o5
	sethi	%hi(.L155), %i4
.L147:
	ldub	[%i0+1], %g1
	add	%g1, -32, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 16
	bleu	.L604
	 add	%i0, 1, %g2
.L149:
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bgu	.L157
	 sll	%g1, 24, %g3
	mov	0, %i4
.L158:
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
	bleu	.L158
	 add	%i4, -48, %i4
.L594:
	sll	%g1, 24, %g3
	mov	%g2, %i0
	sra	%g3, 24, %g3
	cmp	%g3, 46
	be	.L605
	 mov	-1, %l3
.L161:
	and	%g1, -33, %g2
	sll	%g2, 24, %g2
	sra	%g2, 24, %g2
	cmp	%g2, 76
	bne	.L166
	 mov	-1, %g3
	sll	%g1, 24, %g3
	ldub	[%i0+1], %g1
	sra	%g3, 24, %g3
	add	%i0, 1, %i0
.L166:
	add	%g1, -65, %g2
	and	%g2, 0xff, %g2
	cmp	%g2, 55
	bleu	.L606
	 sll	%g2, 2, %g2
.L167:
	sll	%g1, 24, %g2
	sra	%g2, 24, %g2
	cmp	%g2, 37
	be,a	.L630
	 stb	%g1, [%i5]
	mov	37, %g1
	stb	%g1, [%i5]
	add	%i5, 1, %i5
	ldsb	[%i0], %g2
	cmp	%g2, 0
	be	.L146
	 ldub	[%i0], %g1
	stb	%g1, [%i5]
.L630:
	add	%i5, 1, %i5
	ldub	[%i0+1], %g2
	sll	%g2, 24, %g1
	cmp	%g1, 0
	bne	.L396
	 add	%i0, 1, %i0
.L146:
	stb	%g0, [%i5]
	ldub	[%fp-1024], %i5
	sll	%i5, 24, %i5
	cmp	%i5, 0
	be	.L668
	 mov	0, %i0
	sethi	%hi(-53248), %i4
	or	%i4, 512, %i4
.L584:
	call	__ajit_serial_putchar__, 0
	 sra	%i5, 24, %o0
	cmp	%o0, 0
	be	.L584
	 nop
.L496:
#APP
! 624 "/usr/local/ajit_release/tools/minimal_printf_timer/src/ee_printf.c" 1
	lda [%i4] 32, %g1
	
! 0 "" 2
#NO_APP
	and	%g1, 9, %g1
	cmp	%g1, 9
	be	.L496
	 nop
	add	%i0, 1, %i0
	ldub	[%i3+%i0], %i5
	sll	%i5, 24, %i5
	cmp	%i5, 0
	bne	.L584
	 nop
.L668:
	jmp	%i7+8
	 restore
.L604:
	or	%i4, %lo(.L155), %g4
	sll	%g3, 2, %g3
	ld	[%g4+%g3], %g3
	jmp	%g3
	 nop
	.section	".rodata"
	.section	.text.ee_printf
.L154:
	or	%o5, 1, %o5
	b	.L147
	 mov	%g2, %i0
.L153:
	or	%o5, 16, %o5
	b	.L147
	 mov	%g2, %i0
.L152:
	or	%o5, 4, %o5
	b	.L147
	 mov	%g2, %i0
.L151:
	or	%o5, 32, %o5
	b	.L147
	 mov	%g2, %i0
.L150:
	or	%o5, 8, %o5
	b	.L147
	 mov	%g2, %i0
.L157:
	sra	%g3, 24, %g4
	cmp	%g4, 42
	be	.L607
	 sra	%g3, 24, %g3
	mov	%g2, %i0
	mov	-1, %i4
	cmp	%g3, 46
	bne	.L161
	 mov	-1, %l3
.L605:
	ldub	[%i0+1], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 9
	bgu	.L162
	 add	%i0, 1, %g2
	mov	0, %l3
.L163:
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
	bleu	.L163
	 add	%l3, -48, %l3
.L164:
	b	.L161
	 mov	%g2, %i0
.L606:
	sethi	%hi(.L179), %g4
	or	%g4, %lo(.L179), %g4
	ld	[%g4+%g2], %g2
	jmp	%g2
	 nop
	.section	".rodata"
	.section	.text.ee_printf
.L162:
	sll	%g1, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 42
	be	.L608
	 mov	0, %l3
	b	.L161
	 mov	%g2, %i0
.L168:
	or	%o5, 64, %o5
.L170:
	cmp	%g3, 108
	be	.L609
	 ld	[%l2], %g2
	ldub	[%g2], %g3
	cmp	%g3, 0
	be	.L256
	 add	%l2, 4, %l2
	cmp	%g3, 99
	ble	.L610
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
.L260:
	ldub	[%g1+%g3], %g1
	add	%fp, %o4, %o4
	stb	%g1, [%o4-1104]
	add	%fp, %o7, %o4
	mov	46, %g1
	stb	%g1, [%o4-1104]
	ldub	[%g2+1], %g3
	cmp	%g3, 0
	be	.L631
	 add	%fp, %g4, %g1
.L623:
	cmp	%g3, 99
	ble	.L611
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
.L265:
	add	%fp, %g4, %o7
	ldub	[%g1+%g3], %g1
	stb	%g1, [%o7-1104]
	add	%g4, 1, %g4
	mov	46, %g1
	add	%fp, %g4, %o4
	stb	%g1, [%o4-1104]
	ldub	[%g2+2], %g3
	cmp	%g3, 0
	be	.L266
	 add	%g4, 1, %o7
.L624:
	cmp	%g3, 99
	ble	.L612
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
.L270:
	ldub	[%g1+%g3], %g1
	add	%fp, %o7, %g4
	stb	%g1, [%g4-1104]
	add	%o7, 1, %g3
	mov	46, %g1
	add	%fp, %g3, %g4
	stb	%g1, [%g4-1104]
	ldub	[%g2+3], %g2
	cmp	%g2, 0
	be	.L271
	 add	%g3, 1, %o4
.L625:
	cmp	%g2, 99
	ble	.L613
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
.L275:
	add	%fp, %o4, %g3
	ldub	[%g1+%g2], %g1
	add	%o4, 1, %o4
	stb	%g1, [%g3-1104]
.L274:
	andcc	%o5, 16, %g0
	bne	.L632
	 orcc	%o4, 0, %o3
	cmp	%i4, %o4
	ble	.L425
	 add	%i4, -1, %g4
	sub	%i4, %o4, %i4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L277
	 mov	%i4, %g3
	mov	%g1, %g3
.L277:
	cmp	%i4, 3
	bleu,a	.L278
	 mov	%i4, %g3
.L278:
	cmp	%g3, 0
	be	.L279
	 mov	%i5, %g1
	mov	32, %o7
.L280:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L280
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L633
	 add	%i5, %i4, %i5
.L279:
	sub	%i4, %g3, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L282
	 add	%i5, %g3, %g3
	mov	0, %g2
.L283:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L283
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L281
	 sub	%g4, %o5, %g4
.L282:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L634:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, %o4
	bg,a	.L634
	 stb	%o7, [%g1+%g2]
.L281:
	add	%i5, %i4, %i5
.L633:
	add	%o4, -1, %i4
.L276:
	orcc	%o4, 0, %o3
.L632:
	ble,a	.L286
	 mov	1, %o3
.L286:
	srl	%o3, 2, %o5
	andcc	%i5, 3, %g0
	bne	.L427
	 sll	%o5, 2, %g1
	cmp	%g1, 0
	be	.L427
	 mov	0, %g2
	mov	0, %g3
	add	%fp, -1104, %g4
.L288:
	ld	[%g4+%g2], %o7
	st	%o7, [%i5+%g2]
	add	%g3, 1, %g3
	cmp	%o5, %g3
	bgu	.L288
	 add	%g2, 4, %g2
	cmp	%o3, %g1
	be	.L289
	 add	%i5, %g1, %g3
.L287:
	sub	%g3, %g1, %g3
	ldub	[%g4+%g1], %g2
.L635:
	stb	%g2, [%g3+%g1]
	add	%g1, 1, %g1
	cmp	%o4, %g1
	bg,a	.L635
	 ldub	[%g4+%g1], %g2
.L289:
	add	%i5, %o3, %i5
	cmp	%i4, %o4
	ble	.L602
	 add	%i4, -1, %g4
	sub	%i4, %o4, %i4
	sub	%g0, %i5, %g3
	and	%g3, 3, %g3
	cmp	%g3, %i4
	bgu,a	.L292
	 mov	%i4, %g3
.L292:
	cmp	%i4, 3
	bleu,a	.L293
	 mov	%i4, %g3
.L293:
	cmp	%g3, 0
	be	.L294
	 mov	%i5, %g1
	mov	32, %o7
.L295:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L295
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L636
	 add	%i5, %i4, %i5
.L294:
	sub	%i4, %g3, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L297
	 add	%i5, %g3, %g3
	mov	0, %g2
.L298:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L298
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L386
	 sub	%g4, %o5, %g4
.L297:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L637:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%o4, %g3
	bl,a	.L637
	 stb	%o7, [%g1+%g2]
.L386:
	add	%i5, %i4, %i5
.L602:
.L636:
	b	.L148
	 ldub	[%i0+1], %g2
.L169:
	or	%o5, 64, %o5
	mov	16, %o2
.L178:
	ld	[%l2], %o1
	mov	%i5, %o0
	mov	%i4, %o3
	call	number, 0
	 mov	%l3, %o4
	add	%l2, 4, %l2
	mov	%o0, %i5
	b	.L148
	 ldub	[%i0+1], %g2
.L176:
	ld	[%l2], %g4
	cmp	%g4, 0
	be	.L615
	 add	%l2, 4, %l2
.L201:
	ldsb	[%g4], %g1
	cmp	%g1, 0
	be	.L413
	 cmp	%l3, 0
	be,a	.L202
	 mov	0, %g3
	b	.L204
	 mov	%g4, %g3
.L203:
	be,a	.L202
	 sub	%g3, %g4, %g3
.L204:
	add	%g3, 1, %g3
	ldsb	[%g3], %g1
	cmp	%g1, 0
	bne,a	.L203
	 addcc	%l3, -1, %l3
	sub	%g3, %g4, %g3
.L202:
	andcc	%o5, 16, %g0
	bne	.L638
	 cmp	%g3, 0
	cmp	%i4, %g3
	ble	.L414
	 add	%i4, -1, %o5
	sub	%i4, %g3, %i4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L206
	 mov	%i4, %o7
	mov	%g1, %o7
.L206:
	cmp	%i4, 3
	bleu,a	.L207
	 mov	%i4, %o7
.L207:
	cmp	%o7, 0
	be	.L208
	 mov	%i5, %g1
	mov	32, %o4
.L209:
	stb	%o4, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%o7, %g2
	bgu	.L209
	 add	%o5, -1, %o5
	cmp	%i4, %o7
	be,a	.L639
	 add	%i5, %i4, %i5
.L208:
	sub	%i4, %o7, %o2
	srl	%o2, 2, %o4
	sll	%o4, 2, %o3
	cmp	%o3, 0
	be	.L211
	 add	%i5, %o7, %o7
	mov	0, %g2
.L212:
	st	%l1, [%o7]
	add	%g2, 1, %g2
	cmp	%g2, %o4
	blu	.L212
	 add	%o7, 4, %o7
	add	%g1, %o3, %g1
	cmp	%o2, %o3
	be	.L210
	 sub	%o5, %o3, %o5
.L211:
	mov	0, %g2
	add	%o5, 1, %o5
	mov	32, %o4
	stb	%o4, [%g1+%g2]
.L640:
	add	%g2, 1, %g2
	sub	%o5, %g2, %o7
	cmp	%g3, %o7
	bl,a	.L640
	 stb	%o4, [%g1+%g2]
.L210:
	add	%i5, %i4, %i5
.L639:
	add	%g3, -1, %i4
.L205:
	cmp	%g3, 0
.L638:
	ble	.L215
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
	bleu	.L616
	 mov	1, %g1
.L217:
	or	%i5, %g4, %o7
	and	%o7, 3, %o7
	subcc	%g0, %o7, %g0
	and	%g2, %g1, %g1
	subx	%g0, -1, %g2
	andcc	%g1, %g2, %g0
	be	.L416
	 cmp	%o4, 0
	be	.L416
	 mov	0, %g2
	mov	0, %g1
.L218:
	ld	[%g4+%g1], %o7
	st	%o7, [%i5+%g1]
	add	%g2, 1, %g2
	cmp	%o5, %g2
	bgu	.L218
	 add	%g1, 4, %g1
	mov	%o4, %g1
	add	%g4, %o4, %g4
	cmp	%g3, %g1
	be	.L219
	 add	%i5, %o4, %o4
.L216:
	sub	%g0, %g1, %g2
	add	%g4, %g2, %o5
	add	%o4, %g2, %o7
.L641:
	ldub	[%o5+%g1], %o5
	stb	%o5, [%o7+%g1]
	add	%g1, 1, %g1
	cmp	%g3, %g1
	bg	.L641
	 add	%g4, %g2, %o5
.L219:
	add	%i5, %g3, %i5
.L215:
	cmp	%i4, %g3
	ble	.L602
	 add	%i4, -1, %o7
	sub	%i4, %g3, %i4
	sub	%g0, %i5, %g4
	and	%g4, 3, %g4
	cmp	%g4, %i4
	bgu,a	.L222
	 mov	%i4, %g4
.L222:
	cmp	%i4, 3
	bleu,a	.L223
	 mov	%i4, %g4
.L223:
	cmp	%g4, 0
	be	.L224
	 mov	%i5, %g1
	mov	32, %o5
.L225:
	stb	%o5, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g4, %g2
	bgu	.L225
	 add	%o7, -1, %o7
	cmp	%i4, %g4
	be,a	.L636
	 add	%i5, %i4, %i5
.L224:
	sub	%i4, %g4, %o3
	srl	%o3, 2, %o5
	sll	%o5, 2, %o4
	cmp	%o4, 0
	be	.L227
	 add	%i5, %g4, %g4
	mov	0, %g2
.L228:
	st	%l1, [%g4]
	add	%g2, 1, %g2
	cmp	%g2, %o5
	blu	.L228
	 add	%g4, 4, %g4
	add	%g1, %o4, %g1
	cmp	%o3, %o4
	be	.L386
	 sub	%o7, %o4, %o7
.L227:
	mov	0, %g2
	add	%o7, 1, %o7
	mov	32, %o5
	stb	%o5, [%g1+%g2]
.L642:
	add	%g2, 1, %g2
	sub	%o7, %g2, %g4
	cmp	%g3, %g4
	bl,a	.L642
	 stb	%o5, [%g1+%g2]
	b	.L602
	 add	%i5, %i4, %i5
.L175:
	cmp	%i4, -1
	be,a	.L618
	 or	%o5, 1, %o5
.L231:
	ld	[%l2], %o1
	mov	%i5, %o0
	mov	16, %o2
	mov	%i4, %o3
	call	number, 0
	 mov	%l3, %o4
	add	%l2, 4, %l2
	mov	%o0, %i5
	b	.L148
	 ldub	[%i0+1], %g2
.L174:
	b	.L178
	 mov	8, %o2
.L173:
	mov	%l2, %o1
	st	%o5, [%fp-1212]
	add	%fp, -1192, %o0
	call	memcpy, 0
	 mov	8, %o2
	ld	[%fp-1212], %o5
	add	%l2, 8, %l2
	andcc	%o5, 16, %g0
	be	.L596
	 ldd	[%fp-1192], %f8
	and	%o5, -2, %o5
.L596:
	or	%o5, 2, %l5
	and	%l5, 1, %g1
	subcc	%g0, %g1, %g0
	sethi	%hi(.LC3), %g1
	addx	%g0, -1, %l4
	ldd	[%g1+%lo(.LC3)], %f10
	and	%l4, 240, %l4
	fcmped	%f8, %f10
	nop
	fbl	.L619
	 add	%l4, 48, %l4
	andcc	%l5, 4, %g0
	be	.L307
	 andcc	%l5, 8, %g0
	add	%i4, -1, %i4
	mov	43, %l6
.L306:
	cmp	%l3, -1
	be,a	.L308
	 mov	6, %l3
.L308:
	std	%f8, [%fp-1224]
	mov	%l3, %o2
	ldd	[%fp-1224], %o0
	add	%fp, -1200, %o3
	add	%fp, -1196, %o4
	call	fcvtbuf, 0
	 add	%fp, -1104, %o5
	ld	[%fp-1196], %g2
	cmp	%g2, 0
	be	.L309
	 add	%fp, -1184, %g1
	mov	45, %g2
	add	%fp, -1183, %g1
	stb	%g2, [%fp-1184]
.L309:
	ldsb	[%o0], %g2
	cmp	%g2, 0
	bne	.L621
	 ldub	[%o0], %o5
	mov	48, %g2
	cmp	%l3, 0
	be	.L326
	 stb	%g2, [%g1]
	mov	46, %g2
	stb	%g2, [%g1+1]
	orcc	%l3, 0, %g4
	ble	.L622
	 add	%g1, 2, %g1
.L327:
	sub	%g0, %g1, %g2
	and	%g2, 3, %g2
	cmp	%g4, %g2
	bleu	.L328
	 mov	%g4, %o7
	mov	%g2, %o7
.L328:
	cmp	%g4, 3
	bleu,a	.L329
	 mov	%g4, %o7
.L329:
	mov	%g1, %g2
	cmp	%o7, 0
	be	.L330
	 mov	0, %g3
	mov	48, %o5
.L331:
	stb	%o5, [%g2]
	add	%g3, 1, %g3
	cmp	%o7, %g3
	bgu	.L331
	 add	%g2, 1, %g2
	cmp	%g4, %o7
	be,a	.L600
	 stb	%g0, [%g1+%g4]
.L330:
	sub	%g4, %o7, %o2
	srl	%o2, 2, %o3
	sll	%o3, 2, %o4
	cmp	%o4, 0
	be	.L333
	 add	%g1, %o7, %o7
	mov	0, %o5
.L334:
	st	%i2, [%o7]
	add	%o5, 1, %o5
	cmp	%o5, %o3
	blu	.L334
	 add	%o7, 4, %o7
	add	%g2, %o4, %g2
	cmp	%o2, %o4
	be	.L332
	 add	%g3, %o4, %g3
.L333:
	mov	48, %o7
	sub	%g2, %g3, %g2
	stb	%o7, [%g2+%g3]
.L643:
	add	%g3, 1, %g3
	cmp	%l3, %g3
	bg,a	.L643
	 stb	%o7, [%g2+%g3]
.L332:
	stb	%g0, [%g1+%g4]
.L600:
	ldub	[%fp-1184], %g1
.L629:
	sll	%g1, 24, %g1
	cmp	%g1, 0
	be,a	.L644
	 mov	0, %o4
.L341:
	add	%fp, -1184, %g4
.L664:
	add	%fp, -928, %g2
	b	.L353
	 mov	%g4, %o4
.L352:
	be,a	.L644
	 sub	%o4, %g4, %o4
.L353:
	add	%o4, 1, %o4
	ldsb	[%o4], %g1
	cmp	%g1, 0
	bne	.L352
	 cmp	%o4, %g2
	sub	%o4, %g4, %o4
.L351:
.L644:
	andcc	%l5, 17, %g0
	bne	.L354
	 sub	%i4, %o4, %i4
	cmp	%i4, 0
	ble	.L438
	 add	%i4, -1, %g4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L355
	 mov	%i4, %g3
	mov	%g1, %g3
.L355:
	cmp	%i4, 3
	bleu,a	.L356
	 mov	%i4, %g3
.L356:
	cmp	%g3, 0
	be	.L357
	 mov	%i5, %g1
	mov	32, %o7
.L358:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L358
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L645
	 add	%i5, %i4, %i5
.L357:
	sub	%i4, %g3, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L360
	 add	%i5, %g3, %g3
	mov	0, %g2
.L361:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L361
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L359
	 sub	%g4, %o5, %g4
.L360:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L646:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, 0
	bg,a	.L646
	 stb	%o7, [%g1+%g2]
.L359:
	add	%i5, %i4, %i5
.L645:
	mov	-1, %i4
.L354:
	andcc	%l6, 0xff, %g0
	be	.L647
	 andcc	%l5, 16, %g0
	stb	%l6, [%i5]
	add	%i5, 1, %i5
.L647:
	bne	.L648
	 cmp	%o4, 0
	cmp	%i4, 0
	ble	.L440
	 add	%i4, -1, %g4
	sub	%g0, %i5, %g3
	and	%g3, 3, %g3
	cmp	%g3, %i4
	bgu,a	.L366
	 mov	%i4, %g3
.L366:
	cmp	%i4, 3
	bleu,a	.L367
	 mov	%i4, %g3
.L367:
	cmp	%g3, 0
	be	.L368
	 mov	%i5, %g1
.L369:
	stb	%l4, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L369
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L649
	 add	%i5, %i4, %i5
.L368:
	sub	%i4, %g3, %o2
	srl	%o2, 2, %o7
	sll	%o7, 2, %o3
	cmp	%o3, 0
	be	.L371
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
.L372:
	st	%o5, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L372
	 add	%g3, 4, %g3
	add	%g1, %o3, %g1
	cmp	%o2, %o3
	be	.L370
	 sub	%g4, %o3, %g4
.L371:
	mov	0, %g2
	add	%g4, 1, %g4
	stb	%l4, [%g1+%g2]
.L650:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, 0
	bg,a	.L650
	 stb	%l4, [%g1+%g2]
.L370:
	add	%i5, %i4, %i5
.L649:
	mov	-1, %i4
.L365:
	cmp	%o4, 0
.L648:
	ble	.L651
	 cmp	%i4, 0
	and	%i5, 3, %g1
	subcc	%g0, %g1, %g0
	srl	%o4, 2, %o5
	subx	%g0, -1, %g3
	sll	%o5, 2, %g1
	cmp	%o4, 3
	bgu	.L377
	 mov	1, %g2
	mov	0, %g2
.L377:
	andcc	%g3, %g2, %g0
	be	.L442
	 cmp	%g1, 0
	be	.L442
	 mov	0, %g2
	mov	0, %g3
	add	%fp, -1184, %g4
.L378:
	ld	[%g4+%g2], %o7
	st	%o7, [%i5+%g2]
	add	%g3, 1, %g3
	cmp	%o5, %g3
	bgu	.L378
	 add	%g2, 4, %g2
	cmp	%o4, %g1
	be	.L379
	 add	%i5, %g1, %g3
.L376:
	sub	%g3, %g1, %g3
	ldub	[%g4+%g1], %g2
.L652:
	stb	%g2, [%g3+%g1]
	add	%g1, 1, %g1
	cmp	%o4, %g1
	bg,a	.L652
	 ldub	[%g4+%g1], %g2
.L379:
	add	%i5, %o4, %i5
	cmp	%i4, 0
.L651:
	ble	.L602
	 add	%i4, -1, %g4
	sub	%g0, %i5, %g3
	and	%g3, 3, %g3
	cmp	%g3, %i4
	bgu,a	.L382
	 mov	%i4, %g3
.L382:
	cmp	%i4, 3
	bleu,a	.L383
	 mov	%i4, %g3
.L383:
	cmp	%g3, 0
	be	.L384
	 mov	%i5, %g1
	mov	32, %o7
.L385:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L385
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L636
	 add	%i5, %i4, %i5
.L384:
	sub	%i4, %g3, %o4
	srl	%o4, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L387
	 add	%i5, %g3, %g3
	mov	0, %g2
.L388:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L388
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o4, %o5
	be	.L386
	 sub	%g4, %o5, %g4
.L387:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L653:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, 0
	bg,a	.L653
	 stb	%o7, [%g1+%g2]
	b	.L602
	 add	%i5, %i4, %i5
.L407:
	b	.L178
	 mov	16, %o2
.L177:
	b	.L178
	 mov	10, %o2
.L172:
	or	%o5, 2, %o5
	b	.L178
	 mov	10, %o2
.L171:
	andcc	%o5, 16, %g0
	bne,a	.L654
	 ld	[%l2], %g1
	add	%i4, -1, %i4
	orcc	%i4, 0, %g2
	ble	.L180
	 sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L181
	 mov	%i4, %g4
	mov	%g1, %g4
.L181:
	cmp	%i4, 3
	bleu,a	.L182
	 mov	%i4, %g4
.L182:
	cmp	%g4, 0
	be	.L183
	 mov	%i5, %g1
	mov	32, %o7
.L184:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g3
	cmp	%g4, %g3
	bgu	.L184
	 add	%g2, -1, %g2
	cmp	%i4, %g4
	be,a	.L655
	 ld	[%l2], %g2
.L183:
	sub	%i4, %g4, %o4
	srl	%o4, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L189
	 mov	0, %g3
	add	%i5, %g4, %g4
.L187:
	st	%l1, [%g4]
	add	%g3, 1, %g3
	cmp	%g3, %o7
	blu	.L187
	 add	%g4, 4, %g4
	add	%g1, %o5, %g1
	cmp	%o4, %o5
	be	.L185
	 sub	%g2, %o5, %g2
.L189:
	mov	32, %g3
.L497:
	stb	%g3, [%g1]
	add	%g2, -1, %g2
	cmp	%g2, 0
	bg	.L497
	 add	%g1, 1, %g1
.L185:
	ld	[%l2], %g2
.L655:
	add	%i5, %i4, %g1
	stb	%g2, [%i5+%i4]
	add	%l2, 4, %l2
	add	%g1, 1, %i5
	b	.L148
	 ldub	[%i0+1], %g2
.L607:
	ld	[%l2], %i4
	add	%i0, 2, %g2
	add	%l2, 4, %l2
	cmp	%i4, 0
	bge	.L594
	 ldub	[%i0+2], %g1
	sub	%g0, %i4, %i4
	b	.L594
	 or	%o5, 16, %o5
.L256:
	mov	48, %g1
	stb	%g1, [%fp-1104]
	mov	1, %o7
	mov	46, %g1
	add	%fp, %o7, %o4
	stb	%g1, [%o4-1104]
	ldub	[%g2+1], %g3
	cmp	%g3, 0
	bne	.L623
	 mov	2, %g4
	add	%fp, %g4, %g1
.L631:
	mov	48, %g3
	stb	%g3, [%g1-1104]
	add	%o7, 2, %g4
	mov	46, %g1
	add	%fp, %g4, %o4
	stb	%g1, [%o4-1104]
	ldub	[%g2+2], %g3
	cmp	%g3, 0
	bne	.L624
	 add	%g4, 1, %o7
.L266:
	mov	48, %g1
	add	%fp, %o7, %o7
	stb	%g1, [%o7-1104]
	add	%g4, 2, %g3
	mov	46, %g1
	add	%fp, %g3, %g4
	stb	%g1, [%g4-1104]
	ldub	[%g2+3], %g2
	cmp	%g2, 0
	bne	.L625
	 add	%g3, 1, %o4
.L271:
	add	%fp, %o4, %g1
	mov	48, %g2
	add	%g3, 2, %o4
	b	.L274
	 stb	%g2, [%g1-1104]
.L180:
	ld	[%l2], %g1
.L654:
	stb	%g1, [%i5]
	add	%i4, -1, %i4
	add	%i5, 1, %o4
	orcc	%i4, 0, %g2
	ble	.L422
	 add	%l2, 4, %l2
	sub	%g0, %o4, %g4
	and	%g4, 3, %g4
	cmp	%g4, %i4
	bgu,a	.L192
	 mov	%i4, %g4
.L192:
	cmp	%i4, 3
	bleu,a	.L193
	 mov	%i4, %g4
.L193:
	cmp	%g4, 0
	be	.L194
	 mov	%o4, %g1
	xnor	%g0, %i5, %o5
	mov	32, %o7
.L195:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	add	%g1, %o5, %g3
	cmp	%g4, %g3
	bgu	.L195
	 add	%g2, -1, %g2
	cmp	%i4, %g4
	be,a	.L656
	 add	%o4, %i4, %i5
.L194:
	sub	%i4, %g4, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L200
	 add	%g4, 1, %g4
	mov	0, %g3
	add	%i5, %g4, %i5
.L198:
	st	%l1, [%i5]
	add	%g3, 1, %g3
	cmp	%g3, %o7
	blu	.L198
	 add	%i5, 4, %i5
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L196
	 sub	%g2, %o5, %g2
.L200:
	mov	32, %g3
.L498:
	stb	%g3, [%g1]
	add	%g2, -1, %g2
	cmp	%g2, 0
	bg	.L498
	 add	%g1, 1, %g1
.L196:
	add	%o4, %i4, %i5
.L656:
	b	.L148
	 ldub	[%i0+1], %g2
.L616:
	b	.L217
	 mov	0, %g1
.L618:
	b	.L231
	 mov	8, %i4
.L609:
	andcc	%o5, 64, %g0
	be	.L418
	 add	%l2, 4, %l2
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %g1
.L233:
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
	bne	.L234
	 stb	%g1, [%fp-1088]
	cmp	%i4, 17
	ble	.L419
	 add	%i4, -1, %g4
	add	%i4, -17, %i4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bgu	.L626
	 mov	%i4, %g3
.L235:
	cmp	%i4, 3
	bleu,a	.L236
	 mov	%i4, %g3
.L236:
	cmp	%g3, 0
	be	.L237
	 mov	%i5, %g1
	mov	32, %o7
.L238:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%g3, %g2
	bgu	.L238
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L657
	 add	%i5, %i4, %i5
.L237:
	sub	%i4, %g3, %o4
	srl	%o4, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L240
	 add	%i5, %g3, %g3
	mov	0, %g2
.L241:
	st	%l1, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L241
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o4, %o5
	be	.L239
	 sub	%g4, %o5, %g4
.L240:
	mov	0, %g2
	add	%g4, 1, %g4
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L658:
	add	%g2, 1, %g2
	sub	%g4, %g2, %g3
	cmp	%g3, 17
	bg,a	.L658
	 stb	%o7, [%g1+%g2]
.L239:
	add	%i5, %i4, %i5
.L657:
	mov	16, %i4
.L234:
	andcc	%i5, 3, %g0
	bne	.L421
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
.L244:
	mov	%g2, %g1
	add	%g2, %o7, %o7
	sub	%g3, %g2, %g3
	add	%fp, -1104, %g4
	ldub	[%g4+%g1], %g2
.L659:
	stb	%g2, [%g3+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %o7
	bne,a	.L659
	 ldub	[%g4+%g1], %g2
	add	%i5, 17, %o4
	cmp	%i4, 17
	ble	.L422
	 add	%i4, -1, %g3
	add	%i4, -17, %i4
	sub	%g0, %o4, %g4
	and	%g4, 3, %g4
	cmp	%g4, %i4
	bgu,a	.L247
	 mov	%i4, %g4
.L247:
	cmp	%i4, 3
	bleu,a	.L248
	 mov	%i4, %g4
.L248:
	cmp	%g4, 0
	be	.L249
	 mov	%o4, %g1
	mov	-17, %o7
	mov	32, %o5
	sub	%o7, %i5, %o7
.L250:
	stb	%o5, [%g1]
	add	%g1, 1, %g1
	add	%g1, %o7, %g2
	cmp	%g4, %g2
	bgu	.L250
	 add	%g3, -1, %g3
	cmp	%i4, %g4
	be,a	.L660
	 add	%o4, %i4, %i5
.L249:
	sub	%i4, %g4, %o3
	srl	%o3, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L252
	 add	%g4, 17, %g4
	mov	0, %g2
	add	%i5, %g4, %i5
.L253:
	st	%l1, [%i5]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L253
	 add	%i5, 4, %i5
	add	%g1, %o5, %g1
	cmp	%o3, %o5
	be	.L251
	 sub	%g3, %o5, %g3
.L252:
	mov	0, %g2
	add	%g3, 1, %g3
	mov	32, %i5
	stb	%i5, [%g1+%g2]
.L661:
	add	%g2, 1, %g2
	sub	%g3, %g2, %g4
	cmp	%g4, 17
	bg,a	.L661
	 stb	%i5, [%g1+%g2]
.L251:
	add	%o4, %i4, %i5
.L660:
	b	.L148
	 ldub	[%i0+1], %g2
.L608:
	ld	[%l2], %l3
	add	%i0, 2, %g2
	add	%l2, 4, %l2
	cmp	%l3, 0
	bge	.L164
	 ldub	[%i0+2], %g1
	mov	0, %l3
	b	.L161
	 mov	%g2, %i0
.L612:
	bg,a	.L589
	 add	%fp, %o7, %o7
	sethi	%hi(.LC0), %g1
	b	.L270
	 or	%g1, %lo(.LC0), %g1
.L611:
	bg,a	.L587
	 add	%fp, %g4, %g4
	sethi	%hi(.LC0), %g1
	b	.L265
	 or	%g1, %lo(.LC0), %g1
.L613:
	bg,a	.L591
	 add	%fp, %o4, %o4
	sethi	%hi(.LC0), %g1
	b	.L275
	 or	%g1, %lo(.LC0), %g1
.L610:
	ble,a	.L424
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
	b	.L260
	 mov	1, %o4
.L418:
	sethi	%hi(.LC0), %g1
	b	.L233
	 or	%g1, %lo(.LC0), %g1
.L307:
	be	.L306
	 mov	0, %l6
	add	%i4, -1, %i4
	b	.L306
	 mov	32, %l6
.L587:
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
	b	.L265
	 add	%o7, 2, %g4
.L589:
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
	b	.L270
	 add	%g4, 2, %o7
.L591:
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
	b	.L275
	 add	%g3, 2, %o4
.L424:
	mov	2, %g4
	mov	1, %o7
	mov	0, %o4
	b	.L260
	 or	%g1, %lo(.LC0), %g1
.L619:
	fnegs	%f8, %f8
	add	%i4, -1, %i4
	b	.L306
	 mov	45, %l6
.L626:
	b	.L235
	 mov	%g1, %g3
.L621:
	ld	[%fp-1200], %g3
	mov	%o0, %g2
	cmp	%g3, 0
	bg	.L501
	 mov	46, %o7
	b	.L628
	 mov	48, %g2
.L324:
	stb	%o5, [%g1]
.L662:
	add	%g2, 1, %g2
	add	%g1, 1, %g1
	ldsb	[%g2], %g4
	cmp	%g4, 0
	be	.L323
	 ldub	[%g2], %o5
.L501:
	sub	%g2, %o0, %g4
	cmp	%g3, %g4
	bne,a	.L662
	 stb	%o5, [%g1]
	stb	%o7, [%g1]
	b	.L324
	 add	%g1, 1, %g1
.L628:
	stb	%g2, [%g1]
	mov	46, %g2
	stb	%g2, [%g1+1]
	subcc	%g0, %g3, %g2
	be	.L500
	 add	%g1, 2, %g1
	sub	%g0, %g1, %g3
	and	%g3, 3, %g3
	cmp	%g3, %g2
	bgu,a	.L313
	 mov	%g2, %g3
.L313:
	cmp	%g2, 3
	bleu,a	.L314
	 mov	%g2, %g3
.L314:
	mov	%g1, %g4
	cmp	%g3, 0
	be	.L315
	 mov	0, %o7
	mov	48, %o4
.L316:
	stb	%o4, [%g4]
	add	%o7, 1, %o7
	cmp	%g3, %o7
	bgu	.L316
	 add	%g4, 1, %g4
	cmp	%g2, %g3
	be,a	.L500
	 add	%g1, %g2, %g1
.L315:
	sub	%g2, %g3, %o2
	srl	%o2, 2, %o1
	sll	%o1, 2, %o4
	cmp	%o4, 0
	be	.L318
	 add	%g1, %g3, %g3
	mov	0, %o3
.L319:
	st	%i2, [%g3]
	add	%o3, 1, %o3
	cmp	%o3, %o1
	blu	.L319
	 add	%g3, 4, %g3
	add	%g4, %o4, %g4
	cmp	%o2, %o4
	be	.L317
	 add	%o7, %o4, %o7
.L318:
	mov	48, %g3
	sub	%g4, %o7, %g4
	stb	%g3, [%g4+%o7]
.L663:
	add	%o7, 1, %o7
	cmp	%g2, %o7
	bg,a	.L663
	 stb	%g3, [%g4+%o7]
.L317:
	add	%g1, %g2, %g1
.L500:
	stb	%o5, [%g1]
	add	%o0, 1, %o0
	add	%g1, 1, %g1
	ldsb	[%o0], %g2
	cmp	%g2, 0
	bne	.L500
	 ldub	[%o0], %o5
.L323:
	andcc	%l5, 32, %g0
	be	.L600
	 stb	%g0, [%g1]
	cmp	%l3, 0
	bne	.L629
	 ldub	[%fp-1184], %g1
.L339:
	ldsb	[%fp-1184], %g1
	cmp	%g1, 0
	be	.L435
	 ldub	[%fp-1184], %g2
	cmp	%g1, 46
	be	.L341
	 and	%g2, -33, %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 69
	be	.L436
	 add	%fp, -1184, %g2
	b	.L343
	 add	%fp, -1183, %g1
.L344:
	cmp	%g3, 46
	be,a	.L664
	 add	%fp, -1184, %g4
	and	%g4, -33, %g3
	sll	%g3, 24, %g3
	sra	%g3, 24, %g3
	cmp	%g3, 69
	be	.L342
	 add	%g1, 1, %g1
.L343:
	ldsb	[%g1], %g3
	mov	%g1, %g2
	cmp	%g3, 0
	bne	.L344
	 ldub	[%g1], %g4
	stb	%g0, [%g2+1]
.L599:
	mov	46, %g1
.L666:
	b	.L600
	 stb	%g1, [%g2]
.L615:
	sethi	%hi(.LC2), %g4
	b	.L201
	 or	%g4, %lo(.LC2), %g4
.L425:
	b	.L276
	 mov	%g4, %i4
.L413:
	b	.L202
	 mov	0, %g3
.L438:
	b	.L354
	 mov	%g4, %i4
.L414:
	b	.L205
	 mov	%o5, %i4
.L422:
	mov	%o4, %i5
	b	.L148
	 ldub	[%i0+1], %g2
.L440:
	b	.L365
	 mov	%g4, %i4
.L419:
	b	.L234
	 mov	%g4, %i4
.L436:
.L342:
	add	%g2, 256, %g4
	b	.L347
	 mov	%g2, %g1
.L345:
	be,a	.L665
	 sub	%g1, %g2, %g1
.L347:
	add	%g1, 1, %g1
	ldsb	[%g1], %g3
	cmp	%g3, 0
	bne	.L345
	 cmp	%g1, %g4
	sub	%g1, %g2, %g1
.L665:
	cmp	%g1, 0
	ble,a	.L666
	 mov	46, %g1
.L499:
	ldub	[%g2+%g1], %g4
	add	%g2, %g1, %g3
	addcc	%g1, -1, %g1
	bne	.L499
	 stb	%g4, [%g3+1]
	mov	46, %g1
	b	.L600
	 stb	%g1, [%g2]
.L427:
	mov	%i5, %g3
	mov	0, %g1
	b	.L287
	 add	%fp, -1104, %g4
.L421:
	mov	%i5, %g3
	mov	17, %o7
	b	.L244
	 mov	0, %g2
.L435:
	add	%fp, -1184, %g2
	b	.L599
	 stb	%g0, [%g2+1]
.L442:
	mov	%i5, %g3
	mov	0, %g1
	b	.L376
	 add	%fp, -1184, %g4
.L416:
	mov	%i5, %o4
	b	.L216
	 mov	0, %g1
.L622:
	b	.L327
	 mov	1, %g4
.L326:
	andcc	%l5, 32, %g0
	bne	.L339
	 stb	%g0, [%g1+1]
	b	.L629
	 ldub	[%fp-1184], %g1
	.align 4
	.subsection	-1
	.align 4
.L179:
	.word	.L168
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L169
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L170
	.word	.L167
	.word	.L171
	.word	.L172
	.word	.L167
	.word	.L173
	.word	.L167
	.word	.L167
	.word	.L172
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L167
	.word	.L174
	.word	.L175
	.word	.L167
	.word	.L167
	.word	.L176
	.word	.L167
	.word	.L177
	.word	.L167
	.word	.L167
	.word	.L407
	.previous
	.subsection	-1
	.align 4
.L155:
	.word	.L150
	.word	.L149
	.word	.L149
	.word	.L151
	.word	.L149
	.word	.L149
	.word	.L149
	.word	.L149
	.word	.L149
	.word	.L149
	.word	.L149
	.word	.L152
	.word	.L149
	.word	.L153
	.word	.L149
	.word	.L149
	.word	.L154
	.previous
	.size	ee_printf, .-ee_printf
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
