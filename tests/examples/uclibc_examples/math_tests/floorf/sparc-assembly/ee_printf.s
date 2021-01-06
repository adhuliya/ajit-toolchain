	.file	"ee_printf.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.align 4
	.global memcpy
	.type	memcpy, #function
	.proc	0120
memcpy:
.LFB2:
	.file 1 "/usr/local/ajit_release/tools/minimal_printf_timer/src/ee_printf.c"
	.loc 1 50 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	.loc 1 52 0
	st	%g0, [%fp-4]
	b	.L2
	 nop
.L3:
	.loc 1 53 0 discriminator 2
	ld	[%fp-4], %g1
	ld	[%fp+68], %g2
	add	%g2, %g1, %g1
	ld	[%fp-4], %g2
	ld	[%fp+72], %g3
	add	%g3, %g2, %g2
	ldub	[%g2], %g2
	stb	%g2, [%g1]
	.loc 1 52 0 discriminator 2
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L2:
	.loc 1 52 0 is_stmt 0 discriminator 1
	ld	[%fp-4], %g2
	ld	[%fp+76], %g1
	cmp	%g2, %g1
	bl	.L3
	 nop
	.loc 1 54 0 is_stmt 1
	ld	[%fp+68], %g1
	.loc 1 55 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE2:
	.size	memcpy, .-memcpy
	.section	".rodata"
	.align 8
.LC0:
	.asciz	"0123456789abcdefghijklmnopqrstuvwxyz"
	.section	".data"
	.align 4
	.type	digits, #object
	.size	digits, 4
digits:
	.long	.LC0
	.section	".rodata"
	.align 8
.LC1:
	.asciz	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	.section	".data"
	.align 4
	.type	upper_digits, #object
	.size	upper_digits, 4
upper_digits:
	.long	.LC1
	.section	".text"
	.align 4
	.type	strnlen, #function
	.proc	016
strnlen:
.LFB3:
	.loc 1 63 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI1:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	.loc 1 65 0
	ld	[%fp+68], %g1
	st	%g1, [%fp-4]
	b	.L6
	 nop
.L8:
	.loc 1 65 0 is_stmt 0 discriminator 1
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L6:
	ld	[%fp-4], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 0
	be	.L7
	 nop
	.loc 1 65 0 discriminator 2
	ld	[%fp+72], %g1
	xor	%g1, 0, %g1
	subcc	%g0, %g1, %g0
	addx	%g0, 0, %g1
	ld	[%fp+72], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp+72]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L8
	 nop
.L7:
	.loc 1 66 0 is_stmt 1
	ld	[%fp-4], %g2
	ld	[%fp+68], %g1
	sub	%g2, %g1, %g1
	.loc 1 67 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE3:
	.size	strnlen, .-strnlen
	.align 4
	.type	skip_atoi, #function
	.proc	04
skip_atoi:
.LFB4:
	.loc 1 70 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI2:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	.loc 1 71 0
	st	%g0, [%fp-4]
	.loc 1 72 0
	b	.L11
	 nop
.L13:
	.loc 1 72 0 is_stmt 0 discriminator 1
	ld	[%fp-4], %g1
	add	%g1, %g1, %g1
	sll	%g1, 2, %g2
	add	%g1, %g2, %g3
	ld	[%fp+68], %g1
	ld	[%g1], %g1
	ldub	[%g1], %g2
	sll	%g2, 24, %g2
	sra	%g2, 24, %g2
	add	%g3, %g2, %g2
	add	%g2, -48, %g2
	st	%g2, [%fp-4]
	add	%g1, 1, %g2
	ld	[%fp+68], %g1
	st	%g2, [%g1]
.L11:
	ld	[%fp+68], %g1
	ld	[%g1], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 47
	ble	.L12
	 nop
	.loc 1 72 0 discriminator 2
	ld	[%fp+68], %g1
	ld	[%g1], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 57
	ble	.L13
	 nop
.L12:
	.loc 1 73 0 is_stmt 1
	ld	[%fp-4], %g1
	.loc 1 74 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE4:
	.size	skip_atoi, .-skip_atoi
	.align 4
	.type	number, #function
	.proc	0102
number:
.LFB5:
	.loc 1 77 0
	.cfi_startproc
	save	%sp, -176, %sp
.LCFI3:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%i5, [%fp+88]
	.loc 1 79 0
	sethi	%hi(digits), %g1
	or	%g1, %lo(digits), %g1
	ld	[%g1], %g1
	st	%g1, [%fp-8]
	.loc 1 82 0
	ld	[%fp+88], %g1
	and	%g1, 64, %g1
	cmp	%g1, 0
	be	.L16
	 nop
	.loc 1 82 0 is_stmt 0 discriminator 1
	sethi	%hi(upper_digits), %g1
	or	%g1, %lo(upper_digits), %g1
	ld	[%g1], %g1
	st	%g1, [%fp-8]
.L16:
	.loc 1 83 0 is_stmt 1
	ld	[%fp+88], %g1
	and	%g1, 16, %g1
	cmp	%g1, 0
	be	.L17
	 nop
	.loc 1 83 0 is_stmt 0 discriminator 1
	ld	[%fp+88], %g1
	and	%g1, -2, %g1
	st	%g1, [%fp+88]
.L17:
	.loc 1 84 0 is_stmt 1
	ld	[%fp+76], %g1
	cmp	%g1, 1
	ble	.L18
	 nop
	.loc 1 84 0 is_stmt 0 discriminator 2
	ld	[%fp+76], %g1
	cmp	%g1, 36
	ble	.L19
	 nop
.L18:
	.loc 1 84 0 discriminator 1
	mov	0, %g1
	b	.L49
	 nop
.L19:
	.loc 1 86 0 is_stmt 1
	ld	[%fp+88], %g1
	and	%g1, 1, %g1
	cmp	%g1, 0
	be	.L21
	 nop
	.loc 1 86 0 is_stmt 0 discriminator 1
	mov	48, %g1
	b	.L22
	 nop
.L21:
	.loc 1 86 0 discriminator 2
	mov	32, %g1
.L22:
	.loc 1 86 0 discriminator 3
	stb	%g1, [%fp-13]
	.loc 1 87 0 is_stmt 1 discriminator 3
	stb	%g0, [%fp-1]
	.loc 1 88 0 discriminator 3
	ld	[%fp+88], %g1
	and	%g1, 2, %g1
	cmp	%g1, 0
	be	.L23
	 nop
	.loc 1 90 0
	ld	[%fp+72], %g1
	cmp	%g1, 0
	bge	.L24
	 nop
	.loc 1 92 0
	mov	45, %g1
	stb	%g1, [%fp-1]
	.loc 1 93 0
	ld	[%fp+72], %g1
	sub	%g0, %g1, %g1
	st	%g1, [%fp+72]
	.loc 1 94 0
	ld	[%fp+80], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp+80]
	b	.L23
	 nop
.L24:
	.loc 1 96 0
	ld	[%fp+88], %g1
	and	%g1, 4, %g1
	cmp	%g1, 0
	be	.L25
	 nop
	.loc 1 98 0
	mov	43, %g1
	stb	%g1, [%fp-1]
	.loc 1 99 0
	ld	[%fp+80], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp+80]
	b	.L23
	 nop
.L25:
	.loc 1 101 0
	ld	[%fp+88], %g1
	and	%g1, 8, %g1
	cmp	%g1, 0
	be	.L23
	 nop
	.loc 1 103 0
	mov	32, %g1
	stb	%g1, [%fp-1]
	.loc 1 104 0
	ld	[%fp+80], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp+80]
.L23:
	.loc 1 108 0
	ld	[%fp+88], %g1
	and	%g1, 32, %g1
	cmp	%g1, 0
	be	.L26
	 nop
	.loc 1 110 0
	ld	[%fp+76], %g1
	cmp	%g1, 16
	bne	.L27
	 nop
	.loc 1 111 0
	ld	[%fp+80], %g1
	add	%g1, -2, %g1
	st	%g1, [%fp+80]
	b	.L26
	 nop
.L27:
	.loc 1 112 0
	ld	[%fp+76], %g1
	cmp	%g1, 8
	bne	.L26
	 nop
	.loc 1 113 0
	ld	[%fp+80], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp+80]
.L26:
	.loc 1 116 0
	st	%g0, [%fp-12]
	.loc 1 118 0
	ld	[%fp+72], %g1
	cmp	%g1, 0
	bne	.L30
	 nop
	.loc 1 119 0
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	mov	48, %g2
	stb	%g2, [%g1-80]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
	b	.L29
	 nop
.L31:
	.loc 1 124 0
	ld	[%fp+72], %g1
	ld	[%fp+76], %g2
	wr	%g0, 0, %y
	nop
	nop
	nop
	udiv	%g1, %g2, %g3
	smul	%g3, %g2, %g2
	sub	%g1, %g2, %g1
	ld	[%fp-8], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g2
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	stb	%g2, [%g1-80]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
	.loc 1 125 0
	ld	[%fp+72], %g3
	ld	[%fp+76], %g2
	wr	%g0, 0, %y
	nop
	nop
	nop
	udiv	%g3, %g2, %g1
	st	%g1, [%fp+72]
.L30:
	.loc 1 122 0 discriminator 1
	ld	[%fp+72], %g1
	cmp	%g1, 0
	bne	.L31
	 nop
.L29:
	.loc 1 129 0
	ld	[%fp-12], %g2
	ld	[%fp+84], %g1
	cmp	%g2, %g1
	ble	.L32
	 nop
	.loc 1 129 0 is_stmt 0 discriminator 1
	ld	[%fp-12], %g1
	st	%g1, [%fp+84]
.L32:
	.loc 1 130 0 is_stmt 1
	ld	[%fp+80], %g2
	ld	[%fp+84], %g1
	sub	%g2, %g1, %g1
	st	%g1, [%fp+80]
	.loc 1 131 0
	ld	[%fp+88], %g1
	and	%g1, 17, %g1
	cmp	%g1, 0
	bne	.L33
	 nop
	b	.L34
	 nop
.L35:
	.loc 1 131 0 is_stmt 0 discriminator 2
	ld	[%fp+68], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L34:
	.loc 1 131 0 discriminator 1
	ld	[%fp+80], %g1
	sra	%g1, 31, %g2
	ld	[%fp+80], %g1
	sub	%g2, %g1, %g1
	srl	%g1, 31, %g1
	ld	[%fp+80], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp+80]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L35
	 nop
.L33:
	.loc 1 132 0 is_stmt 1
	ldub	[%fp-1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 0
	be	.L36
	 nop
	.loc 1 132 0 is_stmt 0 discriminator 1
	ld	[%fp+68], %g1
	ldub	[%fp-1], %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L36:
	.loc 1 134 0 is_stmt 1
	ld	[%fp+88], %g1
	and	%g1, 32, %g1
	cmp	%g1, 0
	be	.L37
	 nop
	.loc 1 136 0
	ld	[%fp+76], %g1
	cmp	%g1, 8
	bne	.L38
	 nop
	.loc 1 137 0
	ld	[%fp+68], %g1
	mov	48, %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
	b	.L37
	 nop
.L38:
	.loc 1 138 0
	ld	[%fp+76], %g1
	cmp	%g1, 16
	bne	.L37
	 nop
	.loc 1 140 0
	ld	[%fp+68], %g1
	mov	48, %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
	.loc 1 141 0
	sethi	%hi(digits), %g1
	or	%g1, %lo(digits), %g1
	ld	[%g1], %g1
	ldub	[%g1+33], %g2
	ld	[%fp+68], %g1
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L37:
	.loc 1 145 0
	ld	[%fp+88], %g1
	and	%g1, 16, %g1
	cmp	%g1, 0
	bne	.L50
	 nop
	b	.L40
	 nop
.L41:
	.loc 1 145 0 is_stmt 0 discriminator 2
	ld	[%fp+68], %g1
	ldub	[%fp-13], %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L40:
	.loc 1 145 0 discriminator 1
	ld	[%fp+80], %g1
	sra	%g1, 31, %g2
	ld	[%fp+80], %g1
	sub	%g2, %g1, %g1
	srl	%g1, 31, %g1
	ld	[%fp+80], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp+80]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L41
	 nop
	.loc 1 146 0 is_stmt 1
	b	.L50
	 nop
.L44:
	.loc 1 146 0 is_stmt 0 discriminator 2
	ld	[%fp+68], %g1
	mov	48, %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
	b	.L42
	 nop
.L50:
	.loc 1 146 0
	nop
.L42:
	.loc 1 146 0 discriminator 1
	mov	1, %g1
	ld	[%fp+84], %g3
	ld	[%fp-12], %g2
	cmp	%g3, %g2
	bg	.L43
	 nop
	mov	0, %g1
.L43:
	ld	[%fp+84], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp+84]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L44
	 nop
	.loc 1 147 0 is_stmt 1
	b	.L45
	 nop
.L46:
	.loc 1 147 0 is_stmt 0 discriminator 2
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	ldub	[%g1-80], %g2
	ld	[%fp+68], %g1
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L45:
	.loc 1 147 0 discriminator 1
	ld	[%fp-12], %g1
	sra	%g1, 31, %g2
	ld	[%fp-12], %g1
	sub	%g2, %g1, %g1
	srl	%g1, 31, %g1
	ld	[%fp-12], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp-12]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L46
	 nop
	.loc 1 148 0 is_stmt 1
	b	.L47
	 nop
.L48:
	.loc 1 148 0 is_stmt 0 discriminator 2
	ld	[%fp+68], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L47:
	.loc 1 148 0 discriminator 1
	ld	[%fp+80], %g1
	sra	%g1, 31, %g2
	ld	[%fp+80], %g1
	sub	%g2, %g1, %g1
	srl	%g1, 31, %g1
	ld	[%fp+80], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp+80]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L48
	 nop
	.loc 1 150 0 is_stmt 1
	ld	[%fp+68], %g1
.L49:
	.loc 1 151 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE5:
	.size	number, .-number
	.align 4
	.type	eaddr, #function
	.proc	0102
eaddr:
.LFB6:
	.loc 1 154 0
	.cfi_startproc
	save	%sp, -136, %sp
.LCFI4:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	.loc 1 156 0
	sethi	%hi(digits), %g1
	or	%g1, %lo(digits), %g1
	ld	[%g1], %g1
	st	%g1, [%fp-4]
	.loc 1 159 0
	ld	[%fp+84], %g1
	and	%g1, 64, %g1
	cmp	%g1, 0
	be	.L52
	 nop
	.loc 1 159 0 is_stmt 0 discriminator 1
	sethi	%hi(upper_digits), %g1
	or	%g1, %lo(upper_digits), %g1
	ld	[%g1], %g1
	st	%g1, [%fp-4]
.L52:
	.loc 1 160 0 is_stmt 1
	st	%g0, [%fp-12]
	.loc 1 161 0
	st	%g0, [%fp-8]
	b	.L53
	 nop
.L55:
	.loc 1 163 0
	ld	[%fp-8], %g1
	cmp	%g1, 0
	be	.L54
	 nop
	.loc 1 163 0 is_stmt 0 discriminator 1
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	mov	58, %g2
	stb	%g2, [%g1-40]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
.L54:
	.loc 1 164 0 is_stmt 1
	ld	[%fp-8], %g1
	ld	[%fp+72], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g1
	and	%g1, 0xff, %g1
	srl	%g1, 4, %g1
	and	%g1, 0xff, %g1
	ld	[%fp-4], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g2
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	stb	%g2, [%g1-40]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
	.loc 1 165 0
	ld	[%fp-8], %g1
	ld	[%fp+72], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g1
	and	%g1, 0xff, %g1
	and	%g1, 15, %g1
	ld	[%fp-4], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g2
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	stb	%g2, [%g1-40]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
	.loc 1 161 0
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
.L53:
	.loc 1 161 0 is_stmt 0 discriminator 1
	ld	[%fp-8], %g1
	cmp	%g1, 5
	ble	.L55
	 nop
	.loc 1 168 0 is_stmt 1
	ld	[%fp+84], %g1
	and	%g1, 16, %g1
	cmp	%g1, 0
	bne	.L56
	 nop
	b	.L57
	 nop
.L59:
	.loc 1 168 0 is_stmt 0 discriminator 2
	ld	[%fp+68], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L57:
	.loc 1 168 0 discriminator 1
	mov	1, %g1
	ld	[%fp+76], %g3
	ld	[%fp-12], %g2
	cmp	%g3, %g2
	bg	.L58
	 nop
	mov	0, %g1
.L58:
	ld	[%fp+76], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp+76]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L59
	 nop
.L56:
	.loc 1 169 0 is_stmt 1
	st	%g0, [%fp-8]
	b	.L60
	 nop
.L61:
	.loc 1 169 0 is_stmt 0 discriminator 2
	ld	[%fp-8], %g1
	add	%fp, %g1, %g1
	ldub	[%g1-40], %g2
	ld	[%fp+68], %g1
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
.L60:
	.loc 1 169 0 discriminator 1
	ld	[%fp-8], %g2
	ld	[%fp-12], %g1
	cmp	%g2, %g1
	bl	.L61
	 nop
	.loc 1 170 0 is_stmt 1
	b	.L62
	 nop
.L64:
	.loc 1 170 0 is_stmt 0 discriminator 2
	ld	[%fp+68], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L62:
	.loc 1 170 0 discriminator 1
	mov	1, %g1
	ld	[%fp+76], %g3
	ld	[%fp-12], %g2
	cmp	%g3, %g2
	bg	.L63
	 nop
	mov	0, %g1
.L63:
	ld	[%fp+76], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp+76]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L64
	 nop
	.loc 1 172 0 is_stmt 1
	ld	[%fp+68], %g1
	.loc 1 173 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE6:
	.size	eaddr, .-eaddr
	.align 4
	.type	iaddr, #function
	.proc	0102
iaddr:
.LFB7:
	.loc 1 176 0
	.cfi_startproc
	save	%sp, -136, %sp
.LCFI5:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	.loc 1 180 0
	st	%g0, [%fp-12]
	.loc 1 181 0
	st	%g0, [%fp-4]
	b	.L67
	 nop
.L73:
	.loc 1 183 0
	ld	[%fp-4], %g1
	cmp	%g1, 0
	be	.L68
	 nop
	.loc 1 183 0 is_stmt 0 discriminator 1
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	mov	46, %g2
	stb	%g2, [%g1-40]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
.L68:
	.loc 1 184 0 is_stmt 1
	ld	[%fp-4], %g1
	ld	[%fp+72], %g2
	add	%g2, %g1, %g1
	ldub	[%g1], %g1
	and	%g1, 0xff, %g1
	st	%g1, [%fp-8]
	.loc 1 186 0
	ld	[%fp-8], %g1
	cmp	%g1, 0
	bne	.L69
	 nop
	.loc 1 187 0
	sethi	%hi(digits), %g1
	or	%g1, %lo(digits), %g1
	ld	[%g1], %g1
	ldub	[%g1], %g2
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	stb	%g2, [%g1-40]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
	b	.L70
	 nop
.L69:
	.loc 1 190 0
	ld	[%fp-8], %g1
	cmp	%g1, 99
	ble	.L71
	 nop
	.loc 1 192 0
	sethi	%hi(digits), %g1
	or	%g1, %lo(digits), %g1
	ld	[%g1], %g2
	ld	[%fp-8], %g1
	sra	%g1, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 100, %g1
	add	%g2, %g1, %g1
	ldub	[%g1], %g2
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	stb	%g2, [%g1-40]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
	.loc 1 193 0
	ld	[%fp-8], %g1
	sra	%g1, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 100, %g2
	smul	%g2, 100, %g2
	sub	%g1, %g2, %g1
	st	%g1, [%fp-8]
	.loc 1 194 0
	sethi	%hi(digits), %g1
	or	%g1, %lo(digits), %g1
	ld	[%g1], %g2
	ld	[%fp-8], %g1
	sra	%g1, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 10, %g1
	add	%g2, %g1, %g1
	ldub	[%g1], %g2
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	stb	%g2, [%g1-40]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
	.loc 1 195 0
	ld	[%fp-8], %g2
	sra	%g2, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g2, 10, %g1
	add	%g1, %g1, %g1
	sll	%g1, 2, %g3
	add	%g1, %g3, %g1
	sub	%g2, %g1, %g1
	st	%g1, [%fp-8]
	b	.L72
	 nop
.L71:
	.loc 1 197 0
	ld	[%fp-8], %g1
	cmp	%g1, 9
	ble	.L72
	 nop
	.loc 1 199 0
	sethi	%hi(digits), %g1
	or	%g1, %lo(digits), %g1
	ld	[%g1], %g2
	ld	[%fp-8], %g1
	sra	%g1, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 10, %g1
	add	%g2, %g1, %g1
	ldub	[%g1], %g2
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	stb	%g2, [%g1-40]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
	.loc 1 200 0
	ld	[%fp-8], %g2
	sra	%g2, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g2, 10, %g1
	add	%g1, %g1, %g1
	sll	%g1, 2, %g3
	add	%g1, %g3, %g1
	sub	%g2, %g1, %g1
	st	%g1, [%fp-8]
.L72:
	.loc 1 203 0
	sethi	%hi(digits), %g1
	or	%g1, %lo(digits), %g1
	ld	[%g1], %g2
	ld	[%fp-8], %g1
	add	%g2, %g1, %g1
	ldub	[%g1], %g2
	ld	[%fp-12], %g1
	add	%fp, %g1, %g1
	stb	%g2, [%g1-40]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
.L70:
	.loc 1 181 0
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L67:
	.loc 1 181 0 is_stmt 0 discriminator 1
	ld	[%fp-4], %g1
	cmp	%g1, 3
	ble	.L73
	 nop
	.loc 1 207 0 is_stmt 1
	ld	[%fp+84], %g1
	and	%g1, 16, %g1
	cmp	%g1, 0
	bne	.L74
	 nop
	b	.L75
	 nop
.L77:
	.loc 1 207 0 is_stmt 0 discriminator 2
	ld	[%fp+68], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L75:
	.loc 1 207 0 discriminator 1
	mov	1, %g1
	ld	[%fp+76], %g3
	ld	[%fp-12], %g2
	cmp	%g3, %g2
	bg	.L76
	 nop
	mov	0, %g1
.L76:
	ld	[%fp+76], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp+76]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L77
	 nop
.L74:
	.loc 1 208 0 is_stmt 1
	st	%g0, [%fp-4]
	b	.L78
	 nop
.L79:
	.loc 1 208 0 is_stmt 0 discriminator 2
	ld	[%fp-4], %g1
	add	%fp, %g1, %g1
	ldub	[%g1-40], %g2
	ld	[%fp+68], %g1
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L78:
	.loc 1 208 0 discriminator 1
	ld	[%fp-4], %g2
	ld	[%fp-12], %g1
	cmp	%g2, %g1
	bl	.L79
	 nop
	.loc 1 209 0 is_stmt 1
	b	.L80
	 nop
.L82:
	.loc 1 209 0 is_stmt 0 discriminator 2
	ld	[%fp+68], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp+68], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+68]
.L80:
	.loc 1 209 0 discriminator 1
	mov	1, %g1
	ld	[%fp+76], %g3
	ld	[%fp-12], %g2
	cmp	%g3, %g2
	bg	.L81
	 nop
	mov	0, %g1
.L81:
	ld	[%fp+76], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp+76]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L82
	 nop
	.loc 1 211 0 is_stmt 1
	ld	[%fp+68], %g1
	.loc 1 212 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE7:
	.size	iaddr, .-iaddr
	.section	".rodata"
	.align 8
.LC2:
	.asciz	"<NULL>"
	.section	".text"
	.align 4
	.type	ee_vsprintf, #function
	.proc	04
ee_vsprintf:
.LFB8:
	.loc 1 430 0
	.cfi_startproc
	save	%sp, -136, %sp
.LCFI6:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	.loc 1 443 0
	ld	[%fp+68], %g1
	st	%g1, [%fp-16]
	b	.L85
	 nop
.L140:
	.loc 1 445 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 37
	be	.L86
	 nop
	.loc 1 447 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g2
	ld	[%fp-16], %g1
	stb	%g2, [%g1]
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
	.loc 1 448 0
	b	.L87
	 nop
.L86:
	.loc 1 452 0
	st	%g0, [%fp-24]
.L88:
	.loc 1 454 0
	ld	[%fp+72], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+72]
	.loc 1 455 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	add	%g1, -32, %g1
	cmp	%g1, 16
	bgu	.L89
	 nop
	sll	%g1, 2, %g2
	sethi	%hi(.L95), %g1
	or	%g1, %lo(.L95), %g1
	ld	[%g2+%g1], %g1
	jmp	%g1
	 nop
	.section	".rodata"
	.section	".text"
.L93:
	.loc 1 457 0
	ld	[%fp-24], %g1
	or	%g1, 16, %g1
	st	%g1, [%fp-24]
	b	.L88
	 nop
.L92:
	.loc 1 458 0
	ld	[%fp-24], %g1
	or	%g1, 4, %g1
	st	%g1, [%fp-24]
	b	.L88
	 nop
.L90:
	.loc 1 459 0
	ld	[%fp-24], %g1
	or	%g1, 8, %g1
	st	%g1, [%fp-24]
	b	.L88
	 nop
.L91:
	.loc 1 460 0
	ld	[%fp-24], %g1
	or	%g1, 32, %g1
	st	%g1, [%fp-24]
	b	.L88
	 nop
.L94:
	.loc 1 461 0
	ld	[%fp-24], %g1
	or	%g1, 1, %g1
	st	%g1, [%fp-24]
	b	.L88
	 nop
.L89:
	.loc 1 465 0
	mov	-1, %g1
	st	%g1, [%fp-28]
	.loc 1 466 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 47
	ble	.L96
	 nop
	.loc 1 466 0 is_stmt 0 discriminator 1
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 57
	bg	.L96
	 nop
	.loc 1 467 0 is_stmt 1
	add	%fp, 72, %g1
	mov	%g1, %o0
	call	skip_atoi, 0
	 nop
	st	%o0, [%fp-28]
	b	.L97
	 nop
.L96:
	.loc 1 468 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 42
	bne	.L97
	 nop
	.loc 1 470 0
	ld	[%fp+72], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+72]
	.loc 1 471 0
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	st	%g1, [%fp-28]
	ld	[%fp+76], %g1
	add	%g1, 4, %g1
	st	%g1, [%fp+76]
	.loc 1 472 0
	ld	[%fp-28], %g1
	cmp	%g1, 0
	bge	.L97
	 nop
	.loc 1 474 0
	ld	[%fp-28], %g1
	sub	%g0, %g1, %g1
	st	%g1, [%fp-28]
	.loc 1 475 0
	ld	[%fp-24], %g1
	or	%g1, 16, %g1
	st	%g1, [%fp-24]
.L97:
	.loc 1 480 0
	mov	-1, %g1
	st	%g1, [%fp-32]
	.loc 1 481 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 46
	bne	.L98
	 nop
	.loc 1 483 0
	ld	[%fp+72], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+72]
	.loc 1 484 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 47
	ble	.L99
	 nop
	.loc 1 484 0 is_stmt 0 discriminator 1
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 57
	bg	.L99
	 nop
	.loc 1 485 0 is_stmt 1
	add	%fp, 72, %g1
	mov	%g1, %o0
	call	skip_atoi, 0
	 nop
	st	%o0, [%fp-32]
	b	.L100
	 nop
.L99:
	.loc 1 486 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 42
	bne	.L100
	 nop
	.loc 1 488 0
	ld	[%fp+72], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+72]
	.loc 1 489 0
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	st	%g1, [%fp-32]
	ld	[%fp+76], %g1
	add	%g1, 4, %g1
	st	%g1, [%fp+76]
.L100:
	.loc 1 491 0
	ld	[%fp-32], %g1
	cmp	%g1, 0
	bge	.L98
	 nop
	.loc 1 491 0 is_stmt 0 discriminator 1
	st	%g0, [%fp-32]
.L98:
	.loc 1 495 0 is_stmt 1
	mov	-1, %g1
	st	%g1, [%fp-36]
	.loc 1 496 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 108
	be	.L101
	 nop
	.loc 1 496 0 is_stmt 0 discriminator 1
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 76
	bne	.L102
	 nop
.L101:
	.loc 1 498 0 is_stmt 1
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	st	%g1, [%fp-36]
	.loc 1 499 0
	ld	[%fp+72], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+72]
.L102:
	.loc 1 503 0
	mov	10, %g1
	st	%g1, [%fp-12]
	.loc 1 505 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	add	%g1, -65, %g1
	cmp	%g1, 55
	bgu	.L103
	 nop
	sll	%g1, 2, %g2
	sethi	%hi(.L114), %g1
	or	%g1, %lo(.L114), %g1
	ld	[%g2+%g1], %g1
	jmp	%g1
	 nop
	.section	".rodata"
	.section	".text"
.L107:
	.loc 1 508 0
	ld	[%fp-24], %g1
	and	%g1, 16, %g1
	cmp	%g1, 0
	bne	.L115
	 nop
	b	.L116
	 nop
.L117:
	.loc 1 508 0 is_stmt 0 discriminator 2
	ld	[%fp-16], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
.L116:
	.loc 1 508 0 discriminator 1
	ld	[%fp-28], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp-28]
	ld	[%fp-28], %g1
	cmp	%g1, 0
	bg	.L117
	 nop
.L115:
	.loc 1 509 0 is_stmt 1
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	mov	%g1, %g2
	ld	[%fp-16], %g1
	stb	%g2, [%g1]
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
	ld	[%fp+76], %g1
	add	%g1, 4, %g1
	st	%g1, [%fp+76]
	.loc 1 510 0
	b	.L118
	 nop
.L119:
	.loc 1 510 0 is_stmt 0 discriminator 2
	ld	[%fp-16], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
.L118:
	.loc 1 510 0 discriminator 1
	ld	[%fp-28], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp-28]
	ld	[%fp-28], %g1
	cmp	%g1, 0
	bg	.L119
	 nop
	.loc 1 511 0 is_stmt 1
	b	.L87
	 nop
.L111:
	.loc 1 514 0
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	st	%g1, [%fp-20]
	ld	[%fp+76], %g1
	add	%g1, 4, %g1
	st	%g1, [%fp+76]
	.loc 1 515 0
	ld	[%fp-20], %g1
	cmp	%g1, 0
	bne	.L120
	 nop
	.loc 1 515 0 is_stmt 0 discriminator 1
	sethi	%hi(.LC2), %g1
	or	%g1, %lo(.LC2), %g1
	st	%g1, [%fp-20]
.L120:
	.loc 1 516 0 is_stmt 1
	ld	[%fp-32], %g1
	ld	[%fp-20], %o0
	mov	%g1, %o1
	call	strnlen, 0
	 nop
	mov	%o0, %g1
	st	%g1, [%fp-40]
	.loc 1 517 0
	ld	[%fp-24], %g1
	and	%g1, 16, %g1
	cmp	%g1, 0
	bne	.L121
	 nop
	b	.L122
	 nop
.L124:
	.loc 1 517 0 is_stmt 0 discriminator 2
	ld	[%fp-16], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
.L122:
	.loc 1 517 0 discriminator 1
	mov	1, %g1
	ld	[%fp-28], %g3
	ld	[%fp-40], %g2
	cmp	%g3, %g2
	bg	.L123
	 nop
	mov	0, %g1
.L123:
	ld	[%fp-28], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp-28]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L124
	 nop
.L121:
	.loc 1 518 0 is_stmt 1
	st	%g0, [%fp-8]
	b	.L125
	 nop
.L126:
	.loc 1 518 0 is_stmt 0 discriminator 2
	ld	[%fp-20], %g1
	ldub	[%g1], %g2
	ld	[%fp-16], %g1
	stb	%g2, [%g1]
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
	ld	[%fp-20], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
.L125:
	.loc 1 518 0 discriminator 1
	ld	[%fp-8], %g2
	ld	[%fp-40], %g1
	cmp	%g2, %g1
	bl	.L126
	 nop
	.loc 1 519 0 is_stmt 1
	b	.L127
	 nop
.L129:
	.loc 1 519 0 is_stmt 0 discriminator 2
	ld	[%fp-16], %g1
	mov	32, %g2
	stb	%g2, [%g1]
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
.L127:
	.loc 1 519 0 discriminator 1
	mov	1, %g1
	ld	[%fp-28], %g3
	ld	[%fp-40], %g2
	cmp	%g3, %g2
	bg	.L128
	 nop
	mov	0, %g1
.L128:
	ld	[%fp-28], %g2
	add	%g2, -1, %g2
	st	%g2, [%fp-28]
	and	%g1, 0xff, %g1
	cmp	%g1, 0
	bne	.L129
	 nop
	.loc 1 520 0 is_stmt 1
	b	.L87
	 nop
.L110:
	.loc 1 523 0
	ld	[%fp-28], %g1
	cmp	%g1, -1
	bne	.L130
	 nop
	.loc 1 525 0
	mov	8, %g1
	st	%g1, [%fp-28]
	.loc 1 526 0
	ld	[%fp-24], %g1
	or	%g1, 1, %g1
	st	%g1, [%fp-24]
.L130:
	.loc 1 528 0
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	ld	[%fp+76], %g2
	add	%g2, 4, %g2
	st	%g2, [%fp+76]
	ld	[%fp-16], %o0
	mov	%g1, %o1
	mov	16, %o2
	ld	[%fp-28], %o3
	ld	[%fp-32], %o4
	ld	[%fp-24], %o5
	call	number, 0
	 nop
	st	%o0, [%fp-16]
	.loc 1 529 0
	b	.L87
	 nop
.L104:
	.loc 1 532 0
	ld	[%fp-24], %g1
	or	%g1, 64, %g1
	st	%g1, [%fp-24]
.L106:
	.loc 1 535 0
	ld	[%fp-36], %g1
	cmp	%g1, 108
	bne	.L131
	 nop
	.loc 1 536 0
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	ld	[%fp+76], %g2
	add	%g2, 4, %g2
	st	%g2, [%fp+76]
	ld	[%fp-16], %o0
	mov	%g1, %o1
	ld	[%fp-28], %o2
	ld	[%fp-32], %o3
	ld	[%fp-24], %o4
	call	eaddr, 0
	 nop
	st	%o0, [%fp-16]
	.loc 1 539 0
	b	.L87
	 nop
.L131:
	.loc 1 538 0
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	ld	[%fp+76], %g2
	add	%g2, 4, %g2
	st	%g2, [%fp+76]
	ld	[%fp-16], %o0
	mov	%g1, %o1
	ld	[%fp-28], %o2
	ld	[%fp-32], %o3
	ld	[%fp-24], %o4
	call	iaddr, 0
	 nop
	st	%o0, [%fp-16]
	.loc 1 539 0
	b	.L87
	 nop
.L109:
	.loc 1 543 0
	mov	8, %g1
	st	%g1, [%fp-12]
	.loc 1 544 0
	b	.L133
	 nop
.L105:
	.loc 1 547 0
	ld	[%fp-24], %g1
	or	%g1, 64, %g1
	st	%g1, [%fp-24]
.L113:
	.loc 1 550 0
	mov	16, %g1
	st	%g1, [%fp-12]
	.loc 1 551 0
	b	.L133
	 nop
.L108:
	.loc 1 555 0
	ld	[%fp-24], %g1
	or	%g1, 2, %g1
	st	%g1, [%fp-24]
	.loc 1 558 0
	b	.L142
	 nop
.L103:
	.loc 1 569 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 37
	be	.L134
	 nop
	.loc 1 569 0 is_stmt 0 discriminator 1
	ld	[%fp-16], %g1
	mov	37, %g2
	stb	%g2, [%g1]
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
.L134:
	.loc 1 570 0 is_stmt 1
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 0
	be	.L135
	 nop
	.loc 1 571 0
	ld	[%fp+72], %g1
	ldub	[%g1], %g2
	ld	[%fp-16], %g1
	stb	%g2, [%g1]
	ld	[%fp-16], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-16]
	.loc 1 574 0
	b	.L87
	 nop
.L135:
	.loc 1 573 0
	ld	[%fp+72], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp+72]
	.loc 1 574 0
	b	.L87
	 nop
.L142:
	.loc 1 558 0
	nop
.L133:
	.loc 1 577 0
	ld	[%fp-36], %g1
	cmp	%g1, 108
	bne	.L137
	 nop
	.loc 1 578 0
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	st	%g1, [%fp-4]
	ld	[%fp+76], %g1
	add	%g1, 4, %g1
	st	%g1, [%fp+76]
	b	.L138
	 nop
.L137:
	.loc 1 579 0
	ld	[%fp-24], %g1
	and	%g1, 2, %g1
	cmp	%g1, 0
	be	.L139
	 nop
	.loc 1 580 0
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	st	%g1, [%fp-4]
	ld	[%fp+76], %g1
	add	%g1, 4, %g1
	st	%g1, [%fp+76]
	b	.L138
	 nop
.L139:
	.loc 1 582 0
	ld	[%fp+76], %g1
	ld	[%g1], %g1
	st	%g1, [%fp-4]
	ld	[%fp+76], %g1
	add	%g1, 4, %g1
	st	%g1, [%fp+76]
.L138:
	.loc 1 584 0
	ld	[%fp-4], %g1
	ld	[%fp-16], %o0
	mov	%g1, %o1
	ld	[%fp-12], %o2
	ld	[%fp-28], %o3
	ld	[%fp-32], %o4
	ld	[%fp-24], %o5
	call	number, 0
	 nop
	st	%o0, [%fp-16]
.L87:
	.loc 1 443 0
	ld	[%fp+72], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp+72]
.L85:
	.loc 1 443 0 is_stmt 0 discriminator 1
	ld	[%fp+72], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 0
	bne	.L140
	 nop
	.loc 1 587 0 is_stmt 1
	ld	[%fp-16], %g1
	stb	%g0, [%g1]
	.loc 1 588 0
	ld	[%fp-16], %g2
	ld	[%fp+68], %g1
	sub	%g2, %g1, %g1
	.loc 1 589 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.align 4
	.subsection	-1
	.align 4
.L114:
	.word	.L104
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L105
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L106
	.word	.L103
	.word	.L107
	.word	.L108
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L108
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L103
	.word	.L109
	.word	.L110
	.word	.L103
	.word	.L103
	.word	.L111
	.word	.L103
	.word	.L142
	.word	.L103
	.word	.L103
	.word	.L113
	.previous
	.subsection	-1
	.align 4
.L95:
	.word	.L90
	.word	.L89
	.word	.L89
	.word	.L91
	.word	.L89
	.word	.L89
	.word	.L89
	.word	.L89
	.word	.L89
	.word	.L89
	.word	.L89
	.word	.L92
	.word	.L89
	.word	.L93
	.word	.L89
	.word	.L89
	.word	.L94
	.previous
	.cfi_endproc
.LFE8:
	.size	ee_vsprintf, .-ee_vsprintf
	.align 4
	.global uart_send_char
	.type	uart_send_char, #function
	.proc	020
uart_send_char:
.LFB9:
	.loc 1 591 0
	.cfi_startproc
	save	%sp, -104, %sp
.LCFI7:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	mov	%i0, %g1
	stb	%g1, [%fp+68]
	b	.L146
	 nop
.L148:
	.loc 1 614 0
	nop
.L146:
.LBB2:
	.loc 1 611 0
	ldub	[%fp+68], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	mov	%g1, %o0
	call	__ajit_serial_putchar__, 0
	 nop
	st	%o0, [%fp-4]
	.loc 1 612 0
	ld	[%fp-4], %g1
	cmp	%g1, 0
	be	.L148
	 nop
	.loc 1 613 0
	nop
	b	.L145
	 nop
.L149:
.LBE2:
	.loc 1 625 0
	nop
.L145:
.LBB3:
	.loc 1 621 0
	st	%g0, [%fp-8]
	.loc 1 622 0
	sethi	%hi(-53248), %g1
	or	%g1, 512, %g1
#APP
! 622 "/usr/local/ajit_release/tools/minimal_printf_timer/src/ee_printf.c" 1
	lda [%g1] 32, %i5
	
! 0 "" 2
#NO_APP
	st	%i5, [%fp-8]
	.loc 1 623 0
	ld	[%fp-8], %g1
	and	%g1, 8, %g1
	cmp	%g1, 0
	be	.L143
	 nop
	.loc 1 623 0 is_stmt 0 discriminator 1
	ld	[%fp-8], %g1
	and	%g1, 1, %g1
	cmp	%g1, 0
	bne	.L149
	 nop
.L143:
.LBE3:
	.loc 1 628 0 is_stmt 1
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE9:
	.size	uart_send_char, .-uart_send_char
	.align 4
	.global ee_printf
	.type	ee_printf, #function
	.proc	04
ee_printf:
.LFB10:
	.loc 1 631 0
	.cfi_startproc
	save	%sp, -368, %sp
.LCFI8:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	.loc 1 636 0
	st	%i1, [%fp+72]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%i5, [%fp+88]
	.loc 1 631 0
	st	%i0, [%fp+68]
	.loc 1 634 0
	st	%g0, [%fp-8]
	.loc 1 636 0
	add	%fp, 72, %g1
	st	%g1, [%fp-268]
	.loc 1 637 0
	ld	[%fp-268], %g1
	add	%fp, -264, %g2
	mov	%g2, %o0
	ld	[%fp+68], %o1
	mov	%g1, %o2
	call	ee_vsprintf, 0
	 nop
	.loc 1 639 0
	add	%fp, -264, %g1
	st	%g1, [%fp-4]
	.loc 1 640 0
	b	.L151
	 nop
.L152:
	.loc 1 641 0
	ld	[%fp-4], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	mov	%g1, %o0
	call	uart_send_char, 0
	 nop
	.loc 1 642 0
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
	.loc 1 643 0
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L151:
	.loc 1 640 0 discriminator 1
	ld	[%fp-4], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 0
	bne	.L152
	 nop
	.loc 1 646 0
	ld	[%fp-8], %g1
	.loc 1 647 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE10:
	.size	ee_printf, .-ee_printf
.Letext0:
	.file 2 "/usr/local/ajit_release/cross-compiler/bin/../lib/gcc/sparc-buildroot-linux-uclibc/4.7.4/include/stdarg.h"
	.file 3 "/usr/local/ajit_release/cross-compiler/bin/../lib/gcc/sparc-buildroot-linux-uclibc/4.7.4/include/stddef.h"
	.file 4 "/home/codeman/.itsoflife/local/packages-live/sparc-glibc-2-21/install/include/stdint.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x59f
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF39
	.byte	0x1
	.uaword	.LASF40
	.uaword	.Ltext0
	.uaword	.Letext0
	.uaword	.Ldebug_line0
	.uleb128 0x2
	.uaword	.LASF0
	.byte	0x2
	.byte	0x28
	.uaword	0x2c
	.uleb128 0x3
	.byte	0x4
	.uaword	.LASF41
	.uleb128 0x2
	.uaword	.LASF1
	.byte	0x2
	.byte	0x66
	.uaword	0x21
	.uleb128 0x2
	.uaword	.LASF2
	.byte	0x3
	.byte	0xd7
	.uaword	0x48
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.uaword	.LASF3
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.asciz	"int"
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.uaword	.LASF4
	.uleb128 0x4
	.byte	0x2
	.byte	0x7
	.uaword	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.uaword	.LASF6
	.uleb128 0x4
	.byte	0x1
	.byte	0x6
	.uaword	.LASF7
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.uaword	.LASF8
	.uleb128 0x4
	.byte	0x8
	.byte	0x5
	.uaword	.LASF9
	.uleb128 0x4
	.byte	0x8
	.byte	0x7
	.uaword	.LASF10
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.uaword	.LASF11
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.uaword	.LASF12
	.uleb128 0x6
	.byte	0x4
	.uleb128 0x7
	.byte	0x4
	.uaword	0x9d
	.uleb128 0x4
	.byte	0x1
	.byte	0x6
	.uaword	.LASF13
	.uleb128 0x8
	.uaword	0x9d
	.uaword	0xb4
	.uleb128 0x9
	.uaword	0x8e
	.byte	0x17
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.uaword	0xba
	.uleb128 0xa
	.uleb128 0x2
	.uaword	.LASF14
	.byte	0x4
	.byte	0x33
	.uaword	0x48
	.uleb128 0xb
	.byte	0x1
	.uaword	.LASF35
	.byte	0x1
	.byte	0x31
	.byte	0x1
	.uaword	0x95
	.uaword	.LFB2
	.uaword	.LFE2
	.uaword	.LLST0
	.byte	0x1
	.uaword	0x11c
	.uleb128 0xc
	.uaword	.LASF15
	.byte	0x1
	.byte	0x31
	.uaword	0x95
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.asciz	"src"
	.byte	0x1
	.byte	0x31
	.uaword	0xb4
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0xd
	.asciz	"n"
	.byte	0x1
	.byte	0x31
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xe
	.asciz	"i"
	.byte	0x1
	.byte	0x33
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0xf
	.uaword	.LASF17
	.byte	0x1
	.byte	0x3e
	.byte	0x1
	.uaword	0x3d
	.uaword	.LFB3
	.uaword	.LFE3
	.uaword	.LLST1
	.byte	0x1
	.uaword	0x163
	.uleb128 0xd
	.asciz	"s"
	.byte	0x1
	.byte	0x3e
	.uaword	0x163
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xc
	.uaword	.LASF16
	.byte	0x1
	.byte	0x3e
	.uaword	0x3d
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0xe
	.asciz	"sc"
	.byte	0x1
	.byte	0x40
	.uaword	0x163
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.uaword	0x169
	.uleb128 0x10
	.uaword	0x9d
	.uleb128 0xf
	.uaword	.LASF18
	.byte	0x1
	.byte	0x45
	.byte	0x1
	.uaword	0x4f
	.uaword	.LFB4
	.uaword	.LFE4
	.uaword	.LLST2
	.byte	0x1
	.uaword	0x1a5
	.uleb128 0xd
	.asciz	"s"
	.byte	0x1
	.byte	0x45
	.uaword	0x1a5
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xe
	.asciz	"i"
	.byte	0x1
	.byte	0x47
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.uaword	0x163
	.uleb128 0xf
	.uaword	.LASF19
	.byte	0x1
	.byte	0x4c
	.byte	0x1
	.uaword	0x97
	.uaword	.LFB5
	.uaword	.LFE5
	.uaword	.LLST3
	.byte	0x1
	.uaword	0x266
	.uleb128 0xd
	.asciz	"str"
	.byte	0x1
	.byte	0x4c
	.uaword	0x97
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xd
	.asciz	"num"
	.byte	0x1
	.byte	0x4c
	.uaword	0x87
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0xc
	.uaword	.LASF20
	.byte	0x1
	.byte	0x4c
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xc
	.uaword	.LASF21
	.byte	0x1
	.byte	0x4c
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0xc
	.uaword	.LASF22
	.byte	0x1
	.byte	0x4c
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.uleb128 0xc
	.uaword	.LASF23
	.byte	0x1
	.byte	0x4c
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 88
	.uleb128 0xe
	.asciz	"c"
	.byte	0x1
	.byte	0x4e
	.uaword	0x9d
	.byte	0x2
	.byte	0x91
	.sleb128 -13
	.uleb128 0x11
	.uaword	.LASF24
	.byte	0x1
	.byte	0x4e
	.uaword	0x9d
	.byte	0x2
	.byte	0x91
	.sleb128 -1
	.uleb128 0xe
	.asciz	"tmp"
	.byte	0x1
	.byte	0x4e
	.uaword	0x266
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0xe
	.asciz	"dig"
	.byte	0x1
	.byte	0x4f
	.uaword	0x97
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xe
	.asciz	"i"
	.byte	0x1
	.byte	0x50
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x8
	.uaword	0x9d
	.uaword	0x276
	.uleb128 0x9
	.uaword	0x8e
	.byte	0x41
	.byte	0
	.uleb128 0xf
	.uaword	.LASF25
	.byte	0x1
	.byte	0x99
	.byte	0x1
	.uaword	0x97
	.uaword	.LFB6
	.uaword	.LFE6
	.uaword	.LLST4
	.byte	0x1
	.uaword	0x315
	.uleb128 0xd
	.asciz	"str"
	.byte	0x1
	.byte	0x99
	.uaword	0x97
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xc
	.uaword	.LASF26
	.byte	0x1
	.byte	0x99
	.uaword	0x315
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0xc
	.uaword	.LASF21
	.byte	0x1
	.byte	0x99
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xc
	.uaword	.LASF22
	.byte	0x1
	.byte	0x99
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0xc
	.uaword	.LASF23
	.byte	0x1
	.byte	0x99
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.uleb128 0xe
	.asciz	"tmp"
	.byte	0x1
	.byte	0x9b
	.uaword	0xa4
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xe
	.asciz	"dig"
	.byte	0x1
	.byte	0x9c
	.uaword	0x97
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0xe
	.asciz	"i"
	.byte	0x1
	.byte	0x9d
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xe
	.asciz	"len"
	.byte	0x1
	.byte	0x9d
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.uaword	0x56
	.uleb128 0xf
	.uaword	.LASF27
	.byte	0x1
	.byte	0xaf
	.byte	0x1
	.uaword	0x97
	.uaword	.LFB7
	.uaword	.LFE7
	.uaword	.LLST5
	.byte	0x1
	.uaword	0x3b8
	.uleb128 0xd
	.asciz	"str"
	.byte	0x1
	.byte	0xaf
	.uaword	0x97
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0xc
	.uaword	.LASF26
	.byte	0x1
	.byte	0xaf
	.uaword	0x315
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0xc
	.uaword	.LASF21
	.byte	0x1
	.byte	0xaf
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xc
	.uaword	.LASF22
	.byte	0x1
	.byte	0xaf
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0xc
	.uaword	.LASF23
	.byte	0x1
	.byte	0xaf
	.uaword	0x4f
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.uleb128 0xe
	.asciz	"tmp"
	.byte	0x1
	.byte	0xb1
	.uaword	0xa4
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xe
	.asciz	"i"
	.byte	0x1
	.byte	0xb2
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0xe
	.asciz	"n"
	.byte	0x1
	.byte	0xb2
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xe
	.asciz	"len"
	.byte	0x1
	.byte	0xb2
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x12
	.uaword	.LASF28
	.byte	0x1
	.uahalf	0x1ad
	.byte	0x1
	.uaword	0x4f
	.uaword	.LFB8
	.uaword	.LFE8
	.uaword	.LLST6
	.byte	0x1
	.uaword	0x4a5
	.uleb128 0x13
	.asciz	"buf"
	.byte	0x1
	.uahalf	0x1ad
	.uaword	0x97
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x13
	.asciz	"fmt"
	.byte	0x1
	.uahalf	0x1ad
	.uaword	0x163
	.byte	0x3
	.byte	0x91
	.sleb128 72
	.uleb128 0x14
	.uaword	.LASF29
	.byte	0x1
	.uahalf	0x1ad
	.uaword	0x32
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0x15
	.asciz	"len"
	.byte	0x1
	.uahalf	0x1af
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x15
	.asciz	"num"
	.byte	0x1
	.uahalf	0x1b0
	.uaword	0x64
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x15
	.asciz	"i"
	.byte	0x1
	.uahalf	0x1b1
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0x16
	.uaword	.LASF20
	.byte	0x1
	.uahalf	0x1b1
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x15
	.asciz	"str"
	.byte	0x1
	.uahalf	0x1b2
	.uaword	0x97
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x15
	.asciz	"s"
	.byte	0x1
	.uahalf	0x1b3
	.uaword	0x97
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x16
	.uaword	.LASF30
	.byte	0x1
	.uahalf	0x1b5
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x16
	.uaword	.LASF31
	.byte	0x1
	.uahalf	0x1b7
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x16
	.uaword	.LASF22
	.byte	0x1
	.uahalf	0x1b8
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x16
	.uaword	.LASF32
	.byte	0x1
	.uahalf	0x1b9
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x17
	.uaword	.LASF42
	.byte	0x1
	.uahalf	0x1c5
	.uaword	.L88
	.byte	0
	.uleb128 0x18
	.byte	0x1
	.uaword	.LASF43
	.byte	0x1
	.uahalf	0x24f
	.byte	0x1
	.uaword	.LFB9
	.uaword	.LFE9
	.uaword	.LLST7
	.byte	0x1
	.uaword	0x505
	.uleb128 0x13
	.asciz	"c"
	.byte	0x1
	.uahalf	0x24f
	.uaword	0x9d
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x19
	.uaword	.LBB2
	.uaword	.LBE2
	.uaword	0x4eb
	.uleb128 0x16
	.uaword	.LASF33
	.byte	0x1
	.uahalf	0x263
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x1a
	.uaword	.LBB3
	.uaword	.LBE3
	.uleb128 0x16
	.uaword	.LASF34
	.byte	0x1
	.uahalf	0x26d
	.uaword	0xbb
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.byte	0
	.byte	0
	.uleb128 0x1b
	.byte	0x1
	.uaword	.LASF36
	.byte	0x1
	.uahalf	0x276
	.byte	0x1
	.uaword	0x4f
	.uaword	.LFB10
	.uaword	.LFE10
	.uaword	.LLST8
	.byte	0x1
	.uaword	0x570
	.uleb128 0x13
	.asciz	"fmt"
	.byte	0x1
	.uahalf	0x276
	.uaword	0x163
	.byte	0x3
	.byte	0x91
	.sleb128 68
	.uleb128 0x1c
	.uleb128 0x15
	.asciz	"buf"
	.byte	0x1
	.uahalf	0x278
	.uaword	0x570
	.byte	0x3
	.byte	0x91
	.sleb128 -264
	.uleb128 0x15
	.asciz	"p"
	.byte	0x1
	.uahalf	0x278
	.uaword	0x97
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x16
	.uaword	.LASF29
	.byte	0x1
	.uahalf	0x279
	.uaword	0x32
	.byte	0x3
	.byte	0x91
	.sleb128 -268
	.uleb128 0x15
	.asciz	"n"
	.byte	0x1
	.uahalf	0x27a
	.uaword	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.byte	0
	.uleb128 0x8
	.uaword	0x9d
	.uaword	0x580
	.uleb128 0x9
	.uaword	0x8e
	.byte	0xff
	.byte	0
	.uleb128 0x11
	.uaword	.LASF37
	.byte	0x1
	.byte	0x3a
	.uaword	0x97
	.byte	0x5
	.byte	0x3
	.uaword	digits
	.uleb128 0x11
	.uaword	.LASF38
	.byte	0x1
	.byte	0x3b
	.uaword	0x97
	.byte	0x5
	.byte	0x3
	.uaword	upper_digits
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.uaword	.LFB2-.Ltext0
	.uaword	.LCFI0-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI0-.Ltext0
	.uaword	.LFE2-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST1:
	.uaword	.LFB3-.Ltext0
	.uaword	.LCFI1-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI1-.Ltext0
	.uaword	.LFE3-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST2:
	.uaword	.LFB4-.Ltext0
	.uaword	.LCFI2-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI2-.Ltext0
	.uaword	.LFE4-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST3:
	.uaword	.LFB5-.Ltext0
	.uaword	.LCFI3-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI3-.Ltext0
	.uaword	.LFE5-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST4:
	.uaword	.LFB6-.Ltext0
	.uaword	.LCFI4-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI4-.Ltext0
	.uaword	.LFE6-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST5:
	.uaword	.LFB7-.Ltext0
	.uaword	.LCFI5-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI5-.Ltext0
	.uaword	.LFE7-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST6:
	.uaword	.LFB8-.Ltext0
	.uaword	.LCFI6-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI6-.Ltext0
	.uaword	.LFE8-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST7:
	.uaword	.LFB9-.Ltext0
	.uaword	.LCFI7-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI7-.Ltext0
	.uaword	.LFE9-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST8:
	.uaword	.LFB10-.Ltext0
	.uaword	.LCFI8-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI8-.Ltext0
	.uaword	.LFE10-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
	.section	.debug_aranges,"",@progbits
	.uaword	0x1c
	.uahalf	0x2
	.uaword	.Ldebug_info0
	.byte	0x4
	.byte	0
	.uahalf	0
	.uahalf	0
	.uaword	.Ltext0
	.uaword	.Letext0-.Ltext0
	.uaword	0
	.uaword	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF33:
	.asciz	"success"
.LASF41:
	.asciz	"__builtin_va_list"
.LASF18:
	.asciz	"skip_atoi"
.LASF28:
	.asciz	"ee_vsprintf"
.LASF16:
	.asciz	"count"
.LASF5:
	.asciz	"short unsigned int"
.LASF43:
	.asciz	"uart_send_char"
.LASF34:
	.asciz	"ctrl_reg"
.LASF21:
	.asciz	"size"
.LASF6:
	.asciz	"long unsigned int"
.LASF26:
	.asciz	"addr"
.LASF2:
	.asciz	"size_t"
.LASF1:
	.asciz	"va_list"
.LASF27:
	.asciz	"iaddr"
.LASF4:
	.asciz	"unsigned char"
.LASF25:
	.asciz	"eaddr"
.LASF40:
	.asciz	"/usr/local/ajit_release/tools/minimal_printf_timer/src/ee_printf.c"
.LASF15:
	.asciz	"dest"
.LASF8:
	.asciz	"short int"
.LASF0:
	.asciz	"__gnuc_va_list"
.LASF20:
	.asciz	"base"
.LASF3:
	.asciz	"unsigned int"
.LASF30:
	.asciz	"flags"
.LASF32:
	.asciz	"qualifier"
.LASF10:
	.asciz	"long long unsigned int"
.LASF38:
	.asciz	"upper_digits"
.LASF42:
	.asciz	"repeat"
.LASF17:
	.asciz	"strnlen"
.LASF19:
	.asciz	"number"
.LASF12:
	.asciz	"sizetype"
.LASF9:
	.asciz	"long long int"
.LASF22:
	.asciz	"precision"
.LASF35:
	.asciz	"memcpy"
.LASF37:
	.asciz	"digits"
.LASF39:
	.asciz	"GNU C 4.7.4"
.LASF23:
	.asciz	"type"
.LASF31:
	.asciz	"field_width"
.LASF29:
	.asciz	"args"
.LASF14:
	.asciz	"uint32_t"
.LASF11:
	.asciz	"long int"
.LASF13:
	.asciz	"char"
.LASF7:
	.asciz	"signed char"
.LASF24:
	.asciz	"sign"
.LASF36:
	.asciz	"ee_printf"
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
