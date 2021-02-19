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
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %o7
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
	addx	%g0, -1, %o5
	mov	0, %o2
	and	%o5, 240, %g2
	andcc	%i5, 2, %g0
	be	.L6
	 add	%g2, 48, %o5
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
	sub	%g0, %i0, %i4
	mov	%i3, %l1
	and	%i4, 3, %g2
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
	 mov	48, %i2
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
	sub	%g2, %i0, %i2
	cmp	%i5, %i2
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
	add	%i4, 1, %i2
	stb	%o5, [%g2+%g3]
.L129:
	add	%g3, 1, %g3
	sub	%i2, %g3, %i5
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
	sub	%g0, %i0, %g2
	and	%g2, 3, %i5
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
	ldub	[%g4+%g1], %i4
	stb	%i4, [%g2]
	add	%g1, -1, %g1
	add	%g1, 1, %i2
	cmp	%i2, 0
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
	sub	%g0, %i0, %i1
	and	%i1, 3, %g3
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
	sub	%g1, %i0, %i4
	cmp	%g3, %i4
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
	 sethi	%hi(538976256), %i4
	add	%i0, %g3, %g3
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
	mov	0, %i2
	add	%g4, 1, %i1
	mov	32, %i5
	stb	%i5, [%g1+%i2]
.L131:
	add	%i2, 1, %i2
	sub	%i1, %i2, %i4
	cmp	%i4, 0
	bg,a	.L131
	 stb	%i5, [%g1+%i2]
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
	mov	48, %g3
	stb	%g3, [%i0]
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
	mov	120, %g2
	stb	%i2, [%i0]
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
	or	%g2, 512, %g3
.L140:
#APP
! 624 "/home/madhav/AjitToolChain/tools/minimal_printf_timer/src/ee_printf.c" 1
	lda [%g3] 32, %g1
	
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
	ldub	[%i0], %o4
	add	%fp, -1024, %i3
	sll	%o4, 24, %g1
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
	ldub	[%i0+1], %o4
.L148:
	sll	%o4, 24, %g1
	cmp	%g1, 0
	be	.L146
	 add	%i0, 1, %i0
.L396:
	sra	%g1, 24, %g1
	cmp	%g1, 37
	bne,a	.L603
	 stb	%o4, [%i5]
	mov	0, %o5
	sethi	%hi(.L155), %i4
.L147:
	ldub	[%i0+1], %g1
	add	%g1, -32, %g3
	and	%g3, 0xff, %o0
	cmp	%o0, 16
	bleu	.L604
	 add	%i0, 1, %g2
.L149:
	add	%g1, -48, %o3
	and	%o3, 0xff, %o4
	cmp	%o4, 9
	bgu	.L157
	 sll	%g1, 24, %o7
	mov	0, %i4
.L158:
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	add	%i4, %i4, %l4
	sll	%i4, 3, %l5
	add	%g2, 1, %g2
	add	%l4, %l5, %l6
	add	%l6, %g1, %i0
	ldub	[%g2], %g1
	add	%g1, -48, %g3
	and	%g3, 0xff, %o0
	cmp	%o0, 9
	bleu	.L158
	 add	%i0, -48, %i4
.L594:
	sll	%g1, 24, %o7
	mov	%g2, %i0
	sra	%o7, 24, %g4
	cmp	%g4, 46
	be	.L605
	 mov	-1, %l3
.L161:
	and	%g1, -33, %o0
	sll	%o0, 24, %g4
	sra	%g4, 24, %o1
	cmp	%o1, 76
	bne	.L166
	 mov	-1, %o3
	sll	%g1, 24, %g3
	ldub	[%i0+1], %g1
	sra	%g3, 24, %o3
	add	%i0, 1, %i0
.L166:
	add	%g1, -65, %o2
	and	%o2, 0xff, %o4
	cmp	%o4, 55
	bleu	.L606
	 sll	%o4, 2, %o7
.L167:
	sll	%g1, 24, %i4
	sra	%i4, 24, %g2
	cmp	%g2, 37
	be,a	.L630
	 stb	%g1, [%i5]
	mov	37, %g1
	stb	%g1, [%i5]
	add	%i5, 1, %i5
	ldsb	[%i0], %g4
	cmp	%g4, 0
	be	.L146
	 ldub	[%i0], %g1
	stb	%g1, [%i5]
.L630:
	add	%i5, 1, %i5
	ldub	[%i0+1], %o4
	sll	%o4, 24, %g1
	cmp	%g1, 0
	bne	.L396
	 add	%i0, 1, %i0
.L146:
	stb	%g0, [%i5]
	ldub	[%fp-1024], %i0
	sll	%i0, 24, %i2
	cmp	%i2, 0
	be	.L682
	 mov	0, %i0
	sethi	%hi(-53248), %l0
	or	%l0, 512, %l1
.L584:
	call	__ajit_serial_putchar__, 0
	 sra	%i2, 24, %o0
	cmp	%o0, 0
	be	.L584
	 nop
.L496:
#APP
! 624 "/home/madhav/AjitToolChain/tools/minimal_printf_timer/src/ee_printf.c" 1
	lda [%l1] 32, %g1
	
! 0 "" 2
#NO_APP
	and	%g1, 9, %g1
	cmp	%g1, 9
	be	.L496
	 nop
	add	%i0, 1, %i0
	ldub	[%i3+%i0], %i1
	sll	%i1, 24, %i2
	cmp	%i2, 0
	bne	.L584
	 nop
.L682:
	jmp	%i7+8
	 restore
.L604:
	or	%i4, %lo(.L155), %g4
	sll	%o0, 2, %o1
	ld	[%g4+%o1], %o2
	jmp	%o2
	 nop
	.section	".rodata"
	.section	".text"
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
	sra	%o7, 24, %l3
	cmp	%l3, 42
	be	.L607
	 sra	%o7, 24, %g4
	mov	%g2, %i0
	mov	-1, %i4
	cmp	%g4, 46
	bne	.L161
	 mov	-1, %l3
.L605:
	ldub	[%i0+1], %g1
	add	%g1, -48, %o1
	and	%o1, 0xff, %o2
	cmp	%o2, 9
	bgu	.L162
	 add	%i0, 1, %o7
	mov	0, %l3
.L163:
	add	%l3, %l3, %g2
	sll	%g1, 24, %g1
	sll	%l3, 3, %l3
	sra	%g1, 24, %g1
	add	%g2, %l3, %l4
	add	%o7, 1, %o7
	add	%l4, %g1, %l5
	ldub	[%o7], %g1
	add	%g1, -48, %l6
	and	%l6, 0xff, %i0
	cmp	%i0, 9
	bleu	.L163
	 add	%l5, -48, %l3
.L164:
	b	.L161
	 mov	%o7, %i0
.L606:
	sethi	%hi(.L179), %g2
	or	%g2, %lo(.L179), %l4
	ld	[%l4+%o7], %l5
	jmp	%l5
	 nop
	.section	".rodata"
	.section	".text"
.L162:
	sll	%g1, 24, %o3
	sra	%o3, 24, %o4
	cmp	%o4, 42
	be	.L608
	 mov	0, %l3
	b	.L161
	 mov	%o7, %i0
.L168:
	or	%o5, 64, %o5
.L170:
	cmp	%o3, 108
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
	sdiv	%g3, 100, %o2
	smul	%o2, 100, %o7
	sub	%g3, %o7, %g3
	sra	%g3, 31, %o4
	wr	%o4, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %l6
	sethi	%hi(.LC0), %g1
	add	%l6, %l6, %o0
	or	%g1, %lo(.LC0), %g1
	sll	%l6, 3, %g4
	ldub	[%g1+%l6], %o1
	ldub	[%g1+%o2], %l5
	add	%o0, %g4, %l3
	stb	%l5, [%fp-1104]
	stb	%o1, [%fp-1103]
	mov	4, %l6
	sub	%g3, %l3, %g3
	mov	3, %o7
	mov	2, %o4
.L260:
	ldub	[%g1+%g3], %g1
	add	%fp, %o4, %l4
	stb	%g1, [%l4-1104]
	add	%fp, %o7, %l5
	mov	46, %g1
	stb	%g1, [%l5-1104]
	ldub	[%g2+1], %g3
	cmp	%g3, 0
	be	.L631
	 add	%fp, %l6, %g1
.L623:
	cmp	%g3, 99
	ble	.L611
	 cmp	%g3, 9
	sra	%g3, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 100, %o4
	add	%fp, %l6, %g4
	smul	%o4, 100, %o3
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldub	[%g1+%o4], %l4
	stb	%l4, [%g4-1104]
	sub	%g3, %o3, %g3
	add	%o7, 3, %l6
	sra	%g3, 31, %o3
	wr	%o3, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %o7
	ldub	[%g1+%o7], %o1
	add	%o7, %o7, %o2
	sll	%o7, 3, %o0
	stb	%o1, [%l5-1102]
	add	%o2, %o0, %l5
	sub	%g3, %l5, %g3
.L265:
	ldub	[%g1+%g3], %g1
	add	%fp, %l6, %l3
	stb	%g1, [%l3-1104]
	add	%l6, 1, %g4
	mov	46, %g1
	add	%fp, %g4, %l4
	stb	%g1, [%l4-1104]
	ldub	[%g2+2], %g3
	cmp	%g3, 0
	be	.L266
	 add	%g4, 1, %l6
.L624:
	cmp	%g3, 99
	ble	.L612
	 cmp	%g3, 9
	sra	%g3, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 100, %l5
	add	%fp, %l6, %l3
	smul	%l5, 100, %o3
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldub	[%g1+%l5], %o4
	stb	%o4, [%l3-1104]
	sub	%g3, %o3, %g3
	add	%g4, 3, %l6
	sra	%g3, 31, %o3
	wr	%o3, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %g4
	ldub	[%g1+%g4], %o7
	add	%g4, %g4, %o1
	sll	%g4, 3, %o2
	stb	%o7, [%l4-1102]
	add	%o1, %o2, %l4
	sub	%g3, %l4, %g3
.L270:
	add	%fp, %l6, %o0
	ldub	[%g1+%g3], %g1
	stb	%g1, [%o0-1104]
	add	%l6, 1, %l3
	mov	46, %g1
	add	%fp, %l3, %l6
	stb	%g1, [%l6-1104]
	ldub	[%g2+3], %g2
	cmp	%g2, 0
	be	.L271
	 add	%l3, 1, %o4
.L625:
	cmp	%g2, 99
	ble	.L613
	 cmp	%g2, 9
	sra	%g2, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g2, 100, %l4
	add	%fp, %o4, %g3
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldub	[%g1+%l4], %o0
	stb	%o0, [%g3-1104]
	smul	%l4, 100, %l5
	add	%l3, 3, %o4
	sub	%g2, %l5, %g2
	sra	%g2, 31, %o3
	wr	%o3, 0, %y
	nop
	nop
	nop
	sdiv	%g2, 10, %l3
	ldub	[%g1+%l3], %g4
	add	%l3, %l3, %o1
	sll	%l3, 3, %o3
	stb	%g4, [%l6-1102]
	add	%o1, %o3, %l6
	sub	%g2, %l6, %g2
.L275:
	add	%fp, %o4, %o7
	ldub	[%g1+%g2], %g1
	add	%o4, 1, %o2
	stb	%g1, [%o7-1104]
.L274:
	andcc	%o5, 16, %g0
	bne	.L632
	 orcc	%o2, 0, %o0
	cmp	%i4, %o2
	ble	.L425
	 add	%i4, -1, %g4
	sub	%i4, %o2, %i4
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
	mov	32, %o5
.L280:
	stb	%o5, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %o0
	cmp	%g3, %o0
	bgu	.L280
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L633
	 add	%i5, %i4, %i5
.L279:
	sub	%i4, %g3, %l5
	srl	%l5, 2, %o4
	sll	%o4, 2, %l3
	cmp	%l3, 0
	be	.L634
	 mov	0, %g2
	add	%i5, %g3, %o3
	mov	0, %o1
.L283:
	st	%l1, [%o3]
	add	%o1, 1, %o1
	cmp	%o1, %o4
	blu	.L283
	 add	%o3, 4, %o3
	add	%g1, %l3, %g1
	cmp	%l5, %l3
	be	.L281
	 sub	%g4, %l3, %g4
	mov	0, %g2
.L634:
	add	%g4, 1, %l6
	mov	32, %o7
	stb	%o7, [%g1+%g2]
.L635:
	add	%g2, 1, %g2
	sub	%l6, %g2, %l4
	cmp	%l4, %o2
	bg,a	.L635
	 stb	%o7, [%g1+%g2]
.L281:
	add	%i5, %i4, %i5
.L633:
	add	%o2, -1, %i4
.L276:
	orcc	%o2, 0, %o0
.L632:
	ble,a	.L286
	 mov	1, %o0
.L286:
	srl	%o0, 2, %o5
	andcc	%i5, 3, %g0
	bne	.L427
	 sll	%o5, 2, %g1
	cmp	%g1, 0
	be,a	.L636
	 mov	%i5, %l3
	mov	0, %o4
	mov	0, %g3
	add	%fp, -1104, %o1
.L288:
	ld	[%o1+%o4], %l5
	st	%l5, [%i5+%o4]
	add	%g3, 1, %g3
	cmp	%o5, %g3
	bgu	.L288
	 add	%o4, 4, %o4
	cmp	%o0, %g1
	be	.L289
	 add	%i5, %g1, %l3
.L287:
	sub	%l3, %g1, %o3
	ldub	[%o1+%g1], %g4
.L637:
	stb	%g4, [%o3+%g1]
	add	%g1, 1, %g1
	cmp	%o2, %g1
	bg,a	.L637
	 ldub	[%o1+%g1], %g4
.L289:
	add	%i5, %o0, %i5
	cmp	%i4, %o2
	ble	.L602
	 add	%i4, -1, %l3
	sub	%i4, %o2, %i4
	sub	%g0, %i5, %l6
	and	%l6, 3, %l4
	cmp	%l4, %i4
	bgu,a	.L292
	 mov	%i4, %l4
.L292:
	cmp	%i4, 3
	bleu,a	.L293
	 mov	%i4, %l4
.L293:
	cmp	%l4, 0
	be	.L294
	 mov	%i5, %g1
	mov	32, %o7
.L295:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g2
	cmp	%l4, %g2
	bgu	.L295
	 add	%l3, -1, %l3
	cmp	%i4, %l4
	be,a	.L638
	 add	%i5, %i4, %i5
.L294:
	sub	%i4, %l4, %o0
	srl	%o0, 2, %l5
	sll	%l5, 2, %o5
	cmp	%o5, 0
	be	.L639
	 mov	0, %g4
	add	%i5, %l4, %g3
	mov	0, %o4
.L298:
	st	%l1, [%g3]
	add	%o4, 1, %o4
	cmp	%o4, %l5
	blu	.L298
	 add	%g3, 4, %g3
	add	%g1, %o5, %g1
	cmp	%o0, %o5
	be	.L386
	 sub	%l3, %o5, %l3
	mov	0, %g4
.L639:
	add	%l3, 1, %o1
	mov	32, %o3
	stb	%o3, [%g1+%g4]
.L640:
	add	%g4, 1, %g4
	sub	%o1, %g4, %l6
	cmp	%o2, %l6
	bl,a	.L640
	 stb	%o3, [%g1+%g4]
.L386:
	add	%i5, %i4, %i5
.L602:
.L638:
	b	.L148
	 ldub	[%i0+1], %o4
.L169:
	or	%o5, 64, %o5
	mov	16, %o2
.L178:
	ld	[%l2], %o1
	mov	%i5, %o0
	mov	%l3, %o4
	call	number, 0
	 mov	%i4, %o3
	add	%l2, 4, %l2
	mov	%o0, %i5
	b	.L148
	 ldub	[%i0+1], %o4
.L176:
	ld	[%l2], %l6
	cmp	%l6, 0
	be	.L615
	 add	%l2, 4, %l2
.L201:
	ldsb	[%l6], %g1
	cmp	%g1, 0
	be	.L413
	 cmp	%l3, 0
	be	.L413
	 mov	%l6, %o0
	b	.L681
	 add	%o0, 1, %o0
.L203:
	be,a	.L202
	 sub	%o0, %l6, %l3
	add	%o0, 1, %o0
.L681:
	ldsb	[%o0], %g1
	cmp	%g1, 0
	bne	.L203
	 addcc	%l3, -1, %l3
	sub	%o0, %l6, %l3
.L202:
	andcc	%o5, 16, %g0
	bne	.L641
	 cmp	%l3, 0
	cmp	%i4, %l3
	ble	.L414
	 add	%i4, -1, %o5
	sub	%i4, %l3, %i4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L206
	 mov	%i4, %g4
	mov	%g1, %g4
.L206:
	cmp	%i4, 3
	bleu,a	.L207
	 mov	%i4, %g4
.L207:
	cmp	%g4, 0
	be	.L208
	 mov	%i5, %g1
	mov	32, %o1
.L209:
	stb	%o1, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g3
	cmp	%g4, %g3
	bgu	.L209
	 add	%o5, -1, %o5
	cmp	%i4, %g4
	be,a	.L642
	 add	%i5, %i4, %i5
.L208:
	sub	%i4, %g4, %o2
	srl	%o2, 2, %o4
	sll	%o4, 2, %o3
	cmp	%o3, 0
	be	.L643
	 mov	0, %o0
	add	%i5, %g4, %o7
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
	mov	0, %o0
.L643:
	add	%o5, 1, %l4
	mov	32, %l5
	stb	%l5, [%g1+%o0]
.L644:
	add	%o0, 1, %o0
	sub	%l4, %o0, %g4
	cmp	%l3, %g4
	bl,a	.L644
	 stb	%l5, [%g1+%o0]
.L210:
	add	%i5, %i4, %i5
.L642:
	add	%l3, -1, %i4
.L205:
	cmp	%l3, 0
.L641:
	ble	.L215
	 srl	%l3, 2, %g3
	add	%i5, 4, %g1
	cmp	%l6, %g1
	add	%l6, 4, %g1
	subx	%g0, -1, %o1
	cmp	%i5, %g1
	subx	%g0, -1, %g1
	or	%o1, %g1, %o4
	sll	%g3, 2, %o2
	cmp	%l3, 3
	bleu	.L616
	 mov	1, %g1
.L217:
	or	%i5, %l6, %o3
	and	%o3, 3, %g2
	subcc	%g0, %g2, %g0
	and	%o4, %g1, %g1
	subx	%g0, -1, %o7
	andcc	%g1, %o7, %g0
	be	.L416
	 cmp	%o2, 0
	be,a	.L645
	 mov	%i5, %l5
	mov	0, %g1
	mov	0, %l4
.L218:
	ld	[%l6+%g1], %o5
	st	%o5, [%i5+%g1]
	add	%l4, 1, %l4
	cmp	%g3, %l4
	bgu	.L218
	 add	%g1, 4, %g1
	mov	%o2, %g1
	add	%l6, %o2, %l6
	cmp	%l3, %o2
	be	.L219
	 add	%i5, %o2, %l5
.L216:
	sub	%g0, %g1, %o0
	add	%l6, %o0, %g4
	add	%l5, %o0, %o1
	ldub	[%g4+%g1], %g3
.L646:
	stb	%g3, [%o1+%g1]
	add	%g1, 1, %g1
	cmp	%l3, %g1
	bg,a	.L646
	 ldub	[%g4+%g1], %g3
.L219:
	add	%i5, %l3, %i5
.L215:
	cmp	%i4, %l3
	ble	.L602
	 add	%i4, -1, %o7
	sub	%i4, %l3, %i4
	sub	%g0, %i5, %l6
	and	%l6, 3, %o2
	cmp	%o2, %i4
	bgu,a	.L222
	 mov	%i4, %o2
.L222:
	cmp	%i4, 3
	bleu,a	.L223
	 mov	%i4, %o2
.L223:
	cmp	%o2, 0
	be	.L224
	 mov	%i5, %g1
	mov	32, %o4
.L225:
	stb	%o4, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %o3
	cmp	%o2, %o3
	bgu	.L225
	 add	%o7, -1, %o7
	cmp	%i4, %o2
	be,a	.L638
	 add	%i5, %i4, %i5
.L224:
	sub	%i4, %o2, %l4
	srl	%l4, 2, %o5
	sll	%o5, 2, %l5
	cmp	%l5, 0
	be	.L647
	 mov	0, %l6
	add	%i5, %o2, %o0
	mov	0, %g2
.L228:
	st	%l1, [%o0]
	add	%g2, 1, %g2
	cmp	%g2, %o5
	blu	.L228
	 add	%o0, 4, %o0
	add	%g1, %l5, %g1
	cmp	%l4, %l5
	be	.L386
	 sub	%o7, %l5, %o7
	mov	0, %l6
.L647:
	add	%o7, 1, %o1
	mov	32, %g3
	stb	%g3, [%g1+%l6]
.L648:
	add	%l6, 1, %l6
	sub	%o1, %l6, %g4
	cmp	%l3, %g4
	bl,a	.L648
	 stb	%g3, [%g1+%l6]
	b	.L602
	 add	%i5, %i4, %i5
.L175:
	cmp	%i4, -1
	be,a	.L618
	 or	%o5, 1, %o5
.L231:
	ld	[%l2], %o1
	mov	%i5, %o0
	mov	%l3, %o4
	mov	16, %o2
	call	number, 0
	 mov	%i4, %o3
	add	%l2, 4, %l2
	mov	%o0, %i5
	b	.L148
	 ldub	[%i0+1], %o4
.L174:
	b	.L178
	 mov	8, %o2
.L173:
	mov	%l2, %o1
	mov	8, %o2
	add	%fp, -1192, %o0
	call	memcpy, 0
	 st	%o5, [%fp-1212]
	ld	[%fp-1212], %o2
	add	%l2, 8, %l2
	andcc	%o2, 16, %g0
	be	.L596
	 ldd	[%fp-1192], %f8
	and	%o2, -2, %o2
.L596:
	or	%o2, 2, %l5
	and	%l5, 1, %g1
	subcc	%g0, %g1, %g0
	sethi	%hi(.LC3), %g1
	addx	%g0, -1, %o4
	ldd	[%g1+%lo(.LC3)], %f10
	and	%o4, 240, %o3
	fcmped	%f8, %f10
	nop
	fbl	.L619
	 add	%o3, 48, %l4
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
	add	%fp, -1104, %o5
	ldd	[%fp-1224], %o0
	mov	%l3, %o2
	add	%fp, -1200, %o3
	call	fcvtbuf, 0
	 add	%fp, -1196, %o4
	ld	[%fp-1196], %o5
	cmp	%o5, 0
	be	.L309
	 add	%fp, -1184, %g1
	mov	45, %g2
	add	%fp, -1183, %g1
	stb	%g2, [%fp-1184]
.L309:
	ldsb	[%o0], %o7
	cmp	%o7, 0
	bne	.L621
	 ldub	[%o0], %o5
	mov	48, %o0
	cmp	%l3, 0
	be	.L326
	 stb	%o0, [%g1]
	mov	46, %o1
	stb	%o1, [%g1+1]
	orcc	%l3, 0, %g4
	ble	.L622
	 add	%g1, 2, %g1
.L327:
	sub	%g0, %g1, %g3
	and	%g3, 3, %o2
	cmp	%g4, %o2
	bleu	.L328
	 mov	%g4, %o7
	mov	%o2, %o7
.L328:
	cmp	%g4, 3
	bleu,a	.L329
	 mov	%g4, %o7
.L329:
	mov	%g1, %g2
	cmp	%o7, 0
	be	.L330
	 mov	0, %g3
	mov	48, %o4
.L331:
	stb	%o4, [%g2]
	add	%g3, 1, %g3
	cmp	%o7, %g3
	bgu	.L331
	 add	%g2, 1, %g2
	cmp	%g4, %o7
	be,a	.L600
	 stb	%g0, [%g1+%g4]
.L330:
	sub	%g4, %o7, %o0
	srl	%o0, 2, %o3
	sll	%o3, 2, %o1
	cmp	%o1, 0
	be,a	.L649
	 mov	48, %o7
	add	%g1, %o7, %o2
	mov	0, %o5
.L334:
	st	%i2, [%o2]
	add	%o5, 1, %o5
	cmp	%o5, %o3
	blu	.L334
	 add	%o2, 4, %o2
	add	%g2, %o1, %g2
	cmp	%o0, %o1
	be	.L332
	 add	%g3, %o1, %g3
	mov	48, %o7
.L649:
	sub	%g2, %g3, %o4
	stb	%o7, [%o4+%g3]
.L650:
	add	%g3, 1, %g3
	cmp	%l3, %g3
	bg,a	.L650
	 stb	%o7, [%o4+%g3]
.L332:
	stb	%g0, [%g1+%g4]
.L600:
	ldub	[%fp-1184], %g1
.L629:
	sll	%g1, 24, %g1
	cmp	%g1, 0
	be,a	.L651
	 mov	0, %l3
.L341:
	add	%fp, -1184, %o0
.L677:
	add	%fp, -928, %o5
	b	.L353
	 mov	%o0, %o4
.L352:
	be	.L651
	 sub	%o4, %o0, %l3
.L353:
	add	%o4, 1, %o4
	ldsb	[%o4], %g1
	cmp	%g1, 0
	bne	.L352
	 cmp	%o4, %o5
	sub	%o4, %o0, %l3
.L351:
.L651:
	andcc	%l5, 17, %g0
	bne	.L354
	 sub	%i4, %l3, %i4
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
	mov	32, %o3
.L358:
	stb	%o3, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %o2
	cmp	%g3, %o2
	bgu	.L358
	 add	%g4, -1, %g4
	cmp	%i4, %g3
	be,a	.L652
	 add	%i5, %i4, %i5
.L357:
	sub	%i4, %g3, %o1
	srl	%o1, 2, %o7
	sll	%o7, 2, %o0
	cmp	%o0, 0
	be	.L653
	 mov	0, %o2
	add	%i5, %g3, %o5
	mov	0, %g2
.L361:
	st	%l1, [%o5]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L361
	 add	%o5, 4, %o5
	add	%g1, %o0, %g1
	cmp	%o1, %o0
	be	.L359
	 sub	%g4, %o0, %g4
	mov	0, %o2
.L653:
	add	%g4, 1, %o4
	mov	32, %o3
	stb	%o3, [%g1+%o2]
.L654:
	add	%o2, 1, %o2
	sub	%o4, %o2, %g3
	cmp	%g3, 0
	bg,a	.L654
	 stb	%o3, [%g1+%o2]
.L359:
	add	%i5, %i4, %i5
.L652:
	mov	-1, %i4
.L354:
	andcc	%l6, 0xff, %g0
	be	.L655
	 andcc	%l5, 16, %g0
	stb	%l6, [%i5]
	add	%i5, 1, %i5
.L655:
	bne	.L656
	 cmp	%l3, 0
	cmp	%i4, 0
	ble	.L440
	 add	%i4, -1, %g4
	sub	%g0, %i5, %l5
	and	%l5, 3, %l6
	cmp	%l6, %i4
	bgu,a	.L366
	 mov	%i4, %l6
.L366:
	cmp	%i4, 3
	bleu,a	.L367
	 mov	%i4, %l6
.L367:
	cmp	%l6, 0
	be	.L368
	 mov	%i5, %g1
.L369:
	stb	%l4, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %o1
	cmp	%l6, %o1
	bgu	.L369
	 add	%g4, -1, %g4
	cmp	%i4, %l6
	be,a	.L657
	 add	%i5, %i4, %i5
.L368:
	sub	%i4, %l6, %o4
	srl	%o4, 2, %o7
	sll	%o7, 2, %o3
	cmp	%o3, 0
	be,a	.L658
	 mov	0, %o7
	and	%l4, 0xff, %o5
	sll	%o5, 24, %o0
	sll	%o5, 16, %g2
	and	%o0, %l0, %o2
	sll	%o5, 8, %l5
	add	%i5, %l6, %g3
	or	%o2, %g2, %l6
	mov	0, %g2
	and	%l6, %i1, %o1
	or	%o1, %l5, %o0
	or	%o0, %o5, %o5
.L372:
	st	%o5, [%g3]
	add	%g2, 1, %g2
	cmp	%g2, %o7
	blu	.L372
	 add	%g3, 4, %g3
	add	%g1, %o3, %g1
	cmp	%o4, %o3
	be	.L370
	 sub	%g4, %o3, %g4
	mov	0, %o7
.L658:
	add	%g4, 1, %o4
	stb	%l4, [%g1+%o7]
.L659:
	add	%o7, 1, %o7
	sub	%o4, %o7, %o3
	cmp	%o3, 0
	bg,a	.L659
	 stb	%l4, [%g1+%o7]
.L370:
	add	%i5, %i4, %i5
.L657:
	mov	-1, %i4
.L365:
	cmp	%l3, 0
.L656:
	ble	.L660
	 cmp	%i4, 0
	and	%i5, 3, %g1
	subcc	%g0, %g1, %g0
	srl	%l3, 2, %l4
	subx	%g0, -1, %o2
	sll	%l4, 2, %g1
	cmp	%l3, 3
	bgu	.L377
	 mov	1, %l5
	mov	0, %l5
.L377:
	andcc	%o2, %l5, %g0
	be	.L442
	 cmp	%g1, 0
	be,a	.L661
	 mov	%i5, %o5
	mov	0, %o0
	mov	0, %o1
	add	%fp, -1184, %g4
.L378:
	ld	[%g4+%o0], %l6
	st	%l6, [%i5+%o0]
	add	%o1, 1, %o1
	cmp	%l4, %o1
	bgu	.L378
	 add	%o0, 4, %o0
	cmp	%l3, %g1
	be	.L379
	 add	%i5, %g1, %o5
.L376:
	sub	%o5, %g1, %g3
	ldub	[%g4+%g1], %g2
.L662:
	stb	%g2, [%g3+%g1]
	add	%g1, 1, %g1
	cmp	%l3, %g1
	bg,a	.L662
	 ldub	[%g4+%g1], %g2
.L379:
	add	%i5, %l3, %i5
	cmp	%i4, 0
.L660:
	ble	.L602
	 add	%i4, -1, %o0
	sub	%g0, %i5, %l3
	and	%l3, 3, %o3
	cmp	%o3, %i4
	bgu,a	.L382
	 mov	%i4, %o3
.L382:
	cmp	%i4, 3
	bleu,a	.L383
	 mov	%i4, %o3
.L383:
	cmp	%o3, 0
	be	.L384
	 mov	%i5, %g1
	mov	32, %o4
.L385:
	stb	%o4, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %o7
	cmp	%o3, %o7
	bgu	.L385
	 add	%o0, -1, %o0
	cmp	%i4, %o3
	be,a	.L638
	 add	%i5, %i4, %i5
.L384:
	sub	%i4, %o3, %l4
	srl	%l4, 2, %o2
	sll	%o2, 2, %l5
	cmp	%l5, 0
	be	.L663
	 mov	0, %g2
	add	%i5, %o3, %o1
	mov	0, %l6
.L388:
	st	%l1, [%o1]
	add	%l6, 1, %l6
	cmp	%l6, %o2
	blu	.L388
	 add	%o1, 4, %o1
	add	%g1, %l5, %g1
	cmp	%l4, %l5
	be	.L386
	 sub	%o0, %l5, %o0
	mov	0, %g2
.L663:
	add	%o0, 1, %o5
	mov	32, %g4
	stb	%g4, [%g1+%g2]
.L664:
	add	%g2, 1, %g2
	sub	%o5, %g2, %g3
	cmp	%g3, 0
	bg,a	.L664
	 stb	%g4, [%g1+%g2]
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
	bne,a	.L665
	 ld	[%l2], %g1
	add	%i4, -1, %i4
	orcc	%i4, 0, %o1
	ble	.L180
	 sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bleu	.L181
	 mov	%i4, %l3
	mov	%g1, %l3
.L181:
	cmp	%i4, 3
	bleu,a	.L182
	 mov	%i4, %l3
.L182:
	cmp	%l3, 0
	be	.L183
	 mov	%i5, %g1
	mov	32, %o4
.L184:
	stb	%o4, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %g3
	cmp	%l3, %g3
	bgu	.L184
	 add	%o1, -1, %o1
	cmp	%i4, %l3
	be,a	.L666
	 ld	[%l2], %o0
.L183:
	sub	%i4, %l3, %l4
	srl	%l4, 2, %o3
	sll	%o3, 2, %o7
	cmp	%o7, 0
	be	.L497
	 mov	32, %l6
	add	%i5, %l3, %l5
	mov	0, %o2
.L187:
	st	%l1, [%l5]
	add	%o2, 1, %o2
	cmp	%o2, %o3
	blu	.L187
	 add	%l5, 4, %l5
	add	%g1, %o7, %g1
	cmp	%l4, %o7
	be	.L185
	 sub	%o1, %o7, %o1
	mov	32, %l6
.L497:
	stb	%l6, [%g1]
	add	%o1, -1, %o1
	cmp	%o1, 0
	bg	.L497
	 add	%g1, 1, %g1
.L185:
	ld	[%l2], %o0
.L666:
	add	%i5, %i4, %g1
	stb	%o0, [%i5+%i4]
	add	%l2, 4, %l2
	add	%g1, 1, %i5
	b	.L148
	 ldub	[%i0+1], %o4
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
	add	%fp, %o7, %l5
	stb	%g1, [%l5-1104]
	ldub	[%g2+1], %g3
	cmp	%g3, 0
	bne	.L623
	 mov	2, %l6
	add	%fp, %l6, %g1
.L631:
	mov	48, %o4
	stb	%o4, [%g1-1104]
	add	%o7, 2, %g4
	mov	46, %g1
	add	%fp, %g4, %l4
	stb	%g1, [%l4-1104]
	ldub	[%g2+2], %g3
	cmp	%g3, 0
	bne	.L624
	 add	%g4, 1, %l6
.L266:
	add	%fp, %l6, %l5
	mov	48, %g1
	stb	%g1, [%l5-1104]
	add	%g4, 2, %l3
	mov	46, %g1
	add	%fp, %l3, %l6
	stb	%g1, [%l6-1104]
	ldub	[%g2+3], %g2
	cmp	%g2, 0
	bne	.L625
	 add	%l3, 1, %o4
.L271:
	add	%fp, %o4, %g1
	mov	48, %l4
	add	%l3, 2, %o2
	b	.L274
	 stb	%l4, [%g1-1104]
.L180:
	ld	[%l2], %g1
.L665:
	stb	%g1, [%i5]
	add	%i4, -1, %i4
	add	%i5, 1, %o4
	orcc	%i4, 0, %g2
	ble	.L422
	 add	%l2, 4, %l2
	sub	%g0, %o4, %l3
	and	%l3, 3, %l4
	cmp	%l4, %i4
	bgu,a	.L192
	 mov	%i4, %l4
.L192:
	cmp	%i4, 3
	bleu,a	.L193
	 mov	%i4, %l4
.L193:
	cmp	%l4, 0
	be	.L194
	 mov	%o4, %g1
	xnor	%g0, %i5, %o3
	mov	32, %o7
.L195:
	stb	%o7, [%g1]
	add	%g1, 1, %g1
	add	%g1, %o3, %o2
	cmp	%l4, %o2
	bgu	.L195
	 add	%g2, -1, %g2
	cmp	%i4, %l4
	be,a	.L667
	 add	%o4, %i4, %i5
.L194:
	sub	%i4, %l4, %l5
	srl	%l5, 2, %l6
	sll	%l6, 2, %o1
	cmp	%o1, 0
	be	.L200
	 add	%l4, 1, %o0
	mov	0, %o5
	add	%i5, %o0, %i5
.L198:
	st	%l1, [%i5]
	add	%o5, 1, %o5
	cmp	%o5, %l6
	blu	.L198
	 add	%i5, 4, %i5
	add	%g1, %o1, %g1
	cmp	%l5, %o1
	be	.L196
	 sub	%g2, %o1, %g2
.L200:
	mov	32, %g4
.L498:
	stb	%g4, [%g1]
	add	%g2, -1, %g2
	cmp	%g2, 0
	bg	.L498
	 add	%g1, 1, %g1
.L196:
	add	%o4, %i4, %i5
.L667:
	b	.L148
	 ldub	[%i0+1], %o4
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
	ldub	[%g2], %o2
	mov	58, %l4
	and	%o2, 0xff, %o7
	stb	%l4, [%fp-1102]
	srl	%o7, 4, %o0
	and	%o2, 15, %l5
	ldub	[%g1+%o0], %o4
	ldub	[%g1+%l5], %g3
	stb	%o4, [%fp-1104]
	stb	%g3, [%fp-1103]
	ldub	[%g2+1], %l3
	and	%l3, 0xff, %o1
	and	%l3, 15, %o3
	srl	%o1, 4, %g4
	stb	%l4, [%fp-1099]
	ldub	[%g1+%o3], %l6
	ldub	[%g1+%g4], %o2
	stb	%l6, [%fp-1100]
	stb	%o2, [%fp-1101]
	ldub	[%g2+2], %o7
	stb	%l4, [%fp-1096]
	and	%o7, 0xff, %o0
	and	%o7, 15, %l5
	srl	%o0, 4, %o4
	ldub	[%g1+%l5], %g3
	ldub	[%g1+%o4], %l3
	stb	%g3, [%fp-1097]
	stb	%l3, [%fp-1098]
	ldub	[%g2+3], %o1
	and	%o1, 0xff, %o3
	and	%o1, 15, %g4
	stb	%l4, [%fp-1093]
	ldub	[%g1+%g4], %o2
	srl	%o3, 4, %l6
	stb	%o2, [%fp-1094]
	ldub	[%g1+%l6], %o7
	stb	%o7, [%fp-1095]
	ldub	[%g2+4], %o0
	stb	%l4, [%fp-1090]
	and	%o0, 15, %l5
	and	%o0, 0xff, %l4
	ldub	[%g1+%l5], %l3
	srl	%l4, 4, %o4
	stb	%l3, [%fp-1091]
	ldub	[%g1+%o4], %g3
	stb	%g3, [%fp-1092]
	ldub	[%g2+5], %g2
	and	%g2, 0xff, %o1
	srl	%o1, 4, %o3
	ldub	[%g1+%o3], %g4
	stb	%g4, [%fp-1089]
	and	%g2, 15, %l6
	andcc	%o5, 16, %g0
	ldub	[%g1+%l6], %g1
	bne	.L234
	 stb	%g1, [%fp-1088]
	cmp	%i4, 17
	ble	.L419
	 add	%i4, -1, %g3
	add	%i4, -17, %i4
	sub	%g0, %i5, %g1
	and	%g1, 3, %g1
	cmp	%i4, %g1
	bgu	.L626
	 mov	%i4, %o2
.L235:
	cmp	%i4, 3
	bleu,a	.L236
	 mov	%i4, %o2
.L236:
	cmp	%o2, 0
	be	.L237
	 mov	%i5, %g1
	mov	32, %o5
.L238:
	stb	%o5, [%g1]
	add	%g1, 1, %g1
	sub	%g1, %i5, %o7
	cmp	%o2, %o7
	bgu	.L238
	 add	%g3, -1, %g3
	cmp	%i4, %o2
	be,a	.L668
	 add	%i5, %i4, %i5
.L237:
	sub	%i4, %o2, %o0
	srl	%o0, 2, %l4
	sll	%l4, 2, %l5
	cmp	%l5, 0
	be	.L669
	 mov	0, %g2
	add	%i5, %o2, %l3
	mov	0, %o4
.L241:
	st	%l1, [%l3]
	add	%o4, 1, %o4
	cmp	%o4, %l4
	blu	.L241
	 add	%l3, 4, %l3
	add	%g1, %l5, %g1
	cmp	%o0, %l5
	be	.L239
	 sub	%g3, %l5, %g3
	mov	0, %g2
.L669:
	add	%g3, 1, %o1
	mov	32, %o3
	stb	%o3, [%g1+%g2]
.L670:
	add	%g2, 1, %g2
	sub	%o1, %g2, %g4
	cmp	%g4, 17
	bg,a	.L670
	 stb	%o3, [%g1+%g2]
.L239:
	add	%i5, %i4, %i5
.L668:
	mov	16, %i4
.L234:
	andcc	%i5, 3, %g0
	bne	.L421
	 ld	[%fp-1104], %g1
	st	%g1, [%i5]
	ld	[%fp-1100], %g1
	st	%g1, [%i5+4]
	ld	[%fp-1096], %g1
	add	%i5, 16, %l6
	st	%g1, [%i5+8]
	mov	1, %o2
	ld	[%fp-1092], %g1
	mov	16, %o5
	st	%g1, [%i5+12]
.L244:
	mov	%o5, %g1
	add	%o5, %o2, %o7
	sub	%l6, %o5, %o0
	add	%fp, -1104, %l4
	ldub	[%l4+%g1], %l5
.L671:
	stb	%l5, [%o0+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %o7
	bne,a	.L671
	 ldub	[%l4+%g1], %l5
	add	%i5, 17, %o4
	cmp	%i4, 17
	ble	.L422
	 add	%i4, -1, %g3
	add	%i4, -17, %i4
	sub	%g0, %o4, %l3
	and	%l3, 3, %o1
	cmp	%o1, %i4
	bgu,a	.L247
	 mov	%i4, %o1
.L247:
	cmp	%i4, 3
	bleu,a	.L248
	 mov	%i4, %o1
.L248:
	cmp	%o1, 0
	be	.L249
	 mov	%o4, %g1
	mov	-17, %g2
	mov	32, %o3
	sub	%g2, %i5, %g4
.L250:
	stb	%o3, [%g1]
	add	%g1, 1, %g1
	add	%g1, %g4, %l6
	cmp	%o1, %l6
	bgu	.L250
	 add	%g3, -1, %g3
	cmp	%i4, %o1
	be,a	.L672
	 add	%o4, %i4, %i5
.L249:
	sub	%i4, %o1, %o2
	srl	%o2, 2, %o7
	sll	%o7, 2, %o5
	cmp	%o5, 0
	be	.L252
	 add	%o1, 17, %o0
	mov	0, %l4
	add	%i5, %o0, %i5
.L253:
	st	%l1, [%i5]
	add	%l4, 1, %l4
	cmp	%l4, %o7
	blu	.L253
	 add	%i5, 4, %i5
	add	%g1, %o5, %g1
	cmp	%o2, %o5
	be	.L251
	 sub	%g3, %o5, %g3
.L252:
	mov	0, %o1
	add	%g3, 1, %l5
	mov	32, %l3
	stb	%l3, [%g1+%o1]
.L673:
	add	%o1, 1, %o1
	sub	%l5, %o1, %o3
	cmp	%o3, 17
	bg,a	.L673
	 stb	%l3, [%g1+%o1]
.L251:
	add	%o4, %i4, %i5
.L672:
	b	.L148
	 ldub	[%i0+1], %o4
.L608:
	ld	[%l2], %l3
	add	%i0, 2, %o7
	add	%l2, 4, %l2
	cmp	%l3, 0
	bge	.L164
	 ldub	[%i0+2], %g1
	mov	0, %l3
	b	.L161
	 mov	%o7, %i0
.L612:
	bg,a	.L589
	 add	%fp, %l6, %l6
	sethi	%hi(.LC0), %g1
	b	.L270
	 or	%g1, %lo(.LC0), %g1
.L611:
	bg,a	.L587
	 add	%fp, %l6, %l6
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
	sll	%g4, 3, %o4
	sethi	%hi(.LC0), %g1
	add	%g4, %g4, %l3
	or	%g1, %lo(.LC0), %g1
	add	%l3, %o4, %o3
	ldub	[%g1+%g4], %l4
	sub	%g3, %o3, %g3
	stb	%l4, [%fp-1104]
	mov	3, %l6
	mov	2, %o7
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
	sdiv	%g3, 10, %o3
	sethi	%hi(.LC0), %g1
	add	%o3, %o3, %o1
	or	%g1, %lo(.LC0), %g1
	sll	%o3, 3, %o2
	ldub	[%g1+%o3], %o0
	add	%o1, %o2, %l3
	stb	%o0, [%l6-1104]
	sub	%g3, %l3, %g3
	b	.L265
	 add	%o7, 2, %l6
.L589:
	sra	%g3, 31, %g1
	wr	%g1, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 10, %o3
	sethi	%hi(.LC0), %g1
	add	%o3, %o3, %o7
	or	%g1, %lo(.LC0), %g1
	sll	%o3, 3, %o1
	ldub	[%g1+%o3], %o2
	add	%o7, %o1, %o0
	stb	%o2, [%l6-1104]
	sub	%g3, %o0, %g3
	b	.L270
	 add	%g4, 2, %l6
.L591:
	sra	%g2, 31, %o7
	wr	%o7, 0, %y
	nop
	nop
	nop
	sdiv	%g2, 10, %g4
	sethi	%hi(.LC0), %g1
	add	%g4, %g4, %o1
	or	%g1, %lo(.LC0), %g1
	sll	%g4, 3, %o3
	ldub	[%g1+%g4], %o7
	add	%o1, %o3, %o2
	stb	%o7, [%o4-1104]
	sub	%g2, %o2, %g2
	b	.L275
	 add	%l3, 2, %o4
.L424:
	mov	2, %l6
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
	 mov	%g1, %o2
.L621:
	ld	[%fp-1200], %o3
	mov	%o0, %o2
	cmp	%o3, 0
	bg	.L501
	 mov	46, %o1
	b	.L628
	 mov	48, %o7
.L324:
	stb	%o5, [%g1]
.L674:
	add	%o2, 1, %o2
	add	%g1, 1, %g1
	ldsb	[%o2], %g2
	cmp	%g2, 0
	be	.L323
	 ldub	[%o2], %o5
.L501:
	sub	%o2, %o0, %g4
	cmp	%o3, %g4
	bne,a	.L674
	 stb	%o5, [%g1]
	stb	%o1, [%g1]
	b	.L324
	 add	%g1, 1, %g1
.L628:
	mov	46, %o4
	stb	%o7, [%g1]
	stb	%o4, [%g1+1]
	subcc	%g0, %o3, %g2
	be	.L500
	 add	%g1, 2, %g1
	sub	%g0, %g1, %g3
	and	%g3, 3, %o3
	cmp	%o3, %g2
	bgu,a	.L313
	 mov	%g2, %o3
.L313:
	cmp	%g2, 3
	bleu,a	.L314
	 mov	%g2, %o3
.L314:
	mov	%g1, %g4
	cmp	%o3, 0
	be	.L315
	 mov	0, %o7
	mov	48, %o1
.L316:
	stb	%o1, [%g4]
	add	%o7, 1, %o7
	cmp	%o3, %o7
	bgu	.L316
	 add	%g4, 1, %g4
	cmp	%g2, %o3
	be,a	.L500
	 add	%g1, %g2, %g1
.L315:
	sub	%g2, %o3, %o2
	srl	%o2, 2, %o1
	sll	%o1, 2, %o4
	cmp	%o4, 0
	be,a	.L675
	 mov	48, %o2
	add	%g1, %o3, %g3
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
	mov	48, %o2
.L675:
	sub	%g4, %o7, %o1
	stb	%o2, [%o1+%o7]
.L676:
	add	%o7, 1, %o7
	cmp	%g2, %o7
	bg,a	.L676
	 stb	%o2, [%o1+%o7]
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
	 ldub	[%fp-1184], %l3
	cmp	%g1, 46
	be	.L341
	 and	%l3, -33, %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 69
	be	.L436
	 add	%fp, -1184, %o2
	b	.L343
	 add	%fp, -1183, %g1
.L344:
	cmp	%o0, 46
	be	.L677
	 add	%fp, -1184, %o0
	and	%o5, -33, %o4
	sll	%o4, 24, %o3
	sra	%o3, 24, %g3
	cmp	%g3, 69
	be	.L342
	 add	%g1, 1, %g1
.L343:
	ldsb	[%g1], %o0
	mov	%g1, %o2
	cmp	%o0, 0
	bne	.L344
	 ldub	[%g1], %o5
	stb	%g0, [%o2+1]
.L599:
	mov	46, %g1
.L679:
	b	.L600
	 stb	%g1, [%o2]
.L615:
	sethi	%hi(.LC2), %g1
	b	.L201
	 or	%g1, %lo(.LC2), %l6
.L425:
	b	.L276
	 mov	%g4, %i4
.L413:
	b	.L202
	 mov	0, %l3
.L438:
	b	.L354
	 mov	%g4, %i4
.L414:
	b	.L205
	 mov	%o5, %i4
.L422:
	mov	%o4, %i5
	b	.L148
	 ldub	[%i0+1], %o4
.L440:
	b	.L365
	 mov	%g4, %i4
.L419:
	b	.L234
	 mov	%g3, %i4
.L436:
.L342:
	add	%o2, 256, %g4
	b	.L347
	 mov	%o2, %g1
.L345:
	be,a	.L678
	 sub	%g1, %o2, %g1
.L347:
	add	%g1, 1, %g1
	ldsb	[%g1], %o1
	cmp	%o1, 0
	bne	.L345
	 cmp	%g1, %g4
	sub	%g1, %o2, %g1
.L678:
	cmp	%g1, 0
	ble,a	.L679
	 mov	46, %g1
.L499:
	ldub	[%o2+%g1], %o7
	add	%o2, %g1, %g2
	addcc	%g1, -1, %g1
	bne	.L499
	 stb	%o7, [%g2+1]
	mov	46, %g1
	b	.L600
	 stb	%g1, [%o2]
.L427:
	mov	%i5, %l3
.L636:
	mov	0, %g1
	b	.L287
	 add	%fp, -1104, %o1
.L421:
	mov	%i5, %l6
	mov	17, %o2
	b	.L244
	 mov	0, %o5
.L435:
	add	%fp, -1184, %o2
	b	.L599
	 stb	%g0, [%o2+1]
.L442:
	mov	%i5, %o5
.L661:
	mov	0, %g1
	b	.L376
	 add	%fp, -1184, %g4
.L416:
	mov	%i5, %l5
.L645:
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
	.ident	"GCC: (Buildroot 2014.08-gfff9e93) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
