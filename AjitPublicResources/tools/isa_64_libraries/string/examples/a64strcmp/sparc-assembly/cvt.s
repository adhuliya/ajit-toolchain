	.file	"cvt.c"
	.section	".text"
.Ltext0:
	.cfi_sections	.debug_frame
	.local	CVTBUF
	.common	CVTBUF,80,8
	.align 4
	.global __modf
	.type	__modf, #function
	.proc	07
__modf:
.LFB0:
	.file 1 "/home/ajit4/ajit-toolchain/AjitPublicResources/tools/minimal_printf_timer/src/cvt.c"
	.loc 1 6 0
	.cfi_startproc
	save	%sp, -128, %sp
.LCFI0:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	std	%i0, [%fp-24]
	st	%i2, [%fp+76]
	.loc 1 7 0
	ldd	[%fp-24], %f8
	fdtoi	%f8, %f10
	st	%f10, [%fp-28]
	ld	[%fp-28], %g1
	st	%g1, [%fp-4]
	.loc 1 9 0
	ld	[%fp-4], %g1
	st	%g1, [%fp-28]
	ld	[%fp-28], %f10
	fitod	%f10, %f8
	ld	[%fp+76], %g1
	std	%f8, [%g1]
	.loc 1 10 0
	ld	[%fp+76], %g1
	ldd	[%g1], %f8
	ldd	[%fp-24], %f10
	fsubd	%f10, %f8, %f8
	std	%f8, [%fp-16]
	.loc 1 12 0
	ldd	[%fp-16], %f8
	.loc 1 13 0
	fmovs	%f8, %f0
	fmovs	%f9, %f1
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE0:
	.size	__modf, .-__modf
	.section	".rodata"
	.align 8
.LC0:
	.long	0
	.long	0
	.align 8
.LC1:
	.long	1076101120
	.long	0
	.align 8
.LC2:
	.long	1067366481
	.long	3951369912
	.align 8
.LC3:
	.long	1072693248
	.long	0
	.section	".text"
	.align 4
	.type	cvt, #function
	.proc	0102
cvt:
.LFB1:
	.loc 1 16 0
	.cfi_startproc
	save	%sp, -152, %sp
.LCFI1:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	std	%i0, [%fp-40]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%i5, [%fp+88]
	.loc 1 21 0
	ld	[%fp+76], %g1
	cmp	%g1, 0
	bge	.L4
	 nop
	.loc 1 21 0 is_stmt 0 discriminator 1
	st	%g0, [%fp+76]
.L4:
	.loc 1 22 0 is_stmt 1
	ld	[%fp+76], %g1
	cmp	%g1, 78
	ble	.L5
	 nop
	.loc 1 22 0 is_stmt 0 discriminator 1
	mov	78, %g1
	st	%g1, [%fp+76]
.L5:
	.loc 1 23 0 is_stmt 1
	st	%g0, [%fp-4]
	.loc 1 24 0
	ld	[%fp+84], %g1
	st	%g0, [%g1]
	.loc 1 25 0
	ld	[%fp+88], %g1
	st	%g1, [%fp-8]
	.loc 1 26 0
	ldd	[%fp-40], %f10
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldd	[%g1], %f8
	fcmped	%f10, %f8
	nop
	fbuge	.L6
	 nop
.L29:
	.loc 1 28 0
	ld	[%fp+84], %g1
	mov	1, %g2
	st	%g2, [%g1]
	.loc 1 29 0
	ldd	[%fp-40], %f8
	fnegs	%f8, %f8
	std	%f8, [%fp-40]
.L6:
	.loc 1 31 0
	add	%fp, -24, %g1
	ldd	[%fp-40], %o0
	mov	%g1, %o2
	call	__modf, 0
	 nop
	std	%f0, [%fp-40]
	.loc 1 32 0
	ld	[%fp+88], %g1
	add	%g1, 80, %g1
	st	%g1, [%fp-12]
	.loc 1 34 0
	ldd	[%fp-24], %f10
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldd	[%g1], %f8
	fcmpd	%f10, %f8
	nop
	fbe	.L8
	 nop
	.loc 1 36 0
	ld	[%fp+88], %g1
	add	%g1, 80, %g1
	st	%g1, [%fp-12]
	.loc 1 37 0
	b	.L9
	 nop
.L10:
	.loc 1 39 0
	ldd	[%fp-24], %f10
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %g1
	ldd	[%g1], %f8
	fdivd	%f10, %f8, %f8
	add	%fp, -24, %g1
	std	%f8, [%fp-48]
	ldd	[%fp-48], %o0
	mov	%g1, %o2
	call	__modf, 0
	 nop
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	std	%f8, [%fp-32]
	.loc 1 40 0
	ld	[%fp-12], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp-12]
	ldd	[%fp-32], %f10
	sethi	%hi(.LC2), %g1
	or	%g1, %lo(.LC2), %g1
	ldd	[%g1], %f8
	faddd	%f10, %f8, %f10
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %g1
	ldd	[%g1], %f8
	fmuld	%f10, %f8, %f8
	fdtoi	%f8, %f10
	st	%f10, [%fp-52]
	ld	[%fp-52], %g1
	add	%g1, 48, %g1
	mov	%g1, %g2
	ld	[%fp-12], %g1
	stb	%g2, [%g1]
	.loc 1 41 0
	ld	[%fp-4], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-4]
.L9:
	.loc 1 37 0 discriminator 1
	ldd	[%fp-24], %f10
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldd	[%g1], %f8
	fcmpd	%f10, %f8
	nop
	fbne	.L10
	 nop
	.loc 1 43 0
	b	.L11
	 nop
.L12:
	.loc 1 43 0 is_stmt 0 discriminator 2
	ld	[%fp-12], %g1
	ldub	[%g1], %g2
	ld	[%fp-8], %g1
	stb	%g2, [%g1]
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
	ld	[%fp-12], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-12]
.L11:
	.loc 1 43 0 discriminator 1
	ld	[%fp+88], %g1
	add	%g1, 80, %g2
	ld	[%fp-12], %g1
	cmp	%g2, %g1
	bgu	.L12
	 nop
	.loc 1 43 0
	b	.L13
	 nop
.L8:
	.loc 1 45 0 is_stmt 1
	ldd	[%fp-40], %f10
	sethi	%hi(.LC0), %g1
	or	%g1, %lo(.LC0), %g1
	ldd	[%g1], %f8
	fcmped	%f10, %f8
	nop
	fbg	.L30
	 nop
	b	.L13
	 nop
.L16:
	.loc 1 49 0
	ldd	[%fp-32], %f8
	std	%f8, [%fp-40]
	.loc 1 50 0
	ld	[%fp-4], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp-4]
	b	.L15
	 nop
.L30:
	.loc 1 47 0
	nop
.L15:
	.loc 1 47 0 is_stmt 0 discriminator 1
	ldd	[%fp-40], %f10
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %g1
	ldd	[%g1], %f8
	fmuld	%f10, %f8, %f8
	std	%f8, [%fp-32]
	ldd	[%fp-32], %f10
	sethi	%hi(.LC3), %g1
	or	%g1, %lo(.LC3), %g1
	ldd	[%g1], %f8
	fcmped	%f10, %f8
	nop
	fbl	.L16
	 nop
.L13:
	.loc 1 53 0 is_stmt 1
	ld	[%fp+76], %g1
	ld	[%fp+88], %g2
	add	%g2, %g1, %g1
	st	%g1, [%fp-12]
	.loc 1 54 0
	ld	[%fp+92], %g1
	cmp	%g1, 0
	bne	.L17
	 nop
	.loc 1 54 0 is_stmt 0 discriminator 1
	ld	[%fp-4], %g1
	ld	[%fp-12], %g2
	add	%g2, %g1, %g1
	st	%g1, [%fp-12]
.L17:
	.loc 1 55 0 is_stmt 1
	ld	[%fp+80], %g1
	ld	[%fp-4], %g2
	st	%g2, [%g1]
	.loc 1 56 0
	ld	[%fp-12], %g2
	ld	[%fp+88], %g1
	cmp	%g2, %g1
	bgeu	.L20
	 nop
	.loc 1 58 0
	ld	[%fp+88], %g1
	stb	%g0, [%g1]
	.loc 1 59 0
	ld	[%fp+88], %g1
	b	.L28
	 nop
.L22:
	.loc 1 63 0
	ldd	[%fp-40], %f10
	sethi	%hi(.LC1), %g1
	or	%g1, %lo(.LC1), %g1
	ldd	[%g1], %f8
	fmuld	%f10, %f8, %f8
	std	%f8, [%fp-40]
	.loc 1 64 0
	add	%fp, -32, %g1
	ldd	[%fp-40], %o0
	mov	%g1, %o2
	call	__modf, 0
	 nop
	std	%f0, [%fp-40]
	.loc 1 65 0
	ldd	[%fp-32], %f8
	fdtoi	%f8, %f10
	st	%f10, [%fp-52]
	ld	[%fp-52], %g1
	add	%g1, 48, %g1
	mov	%g1, %g2
	ld	[%fp-8], %g1
	stb	%g2, [%g1]
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
.L20:
	.loc 1 61 0 discriminator 1
	ld	[%fp-8], %g2
	ld	[%fp-12], %g1
	cmp	%g2, %g1
	bgu	.L21
	 nop
	.loc 1 61 0 is_stmt 0 discriminator 2
	ld	[%fp+88], %g1
	add	%g1, 80, %g2
	ld	[%fp-8], %g1
	cmp	%g2, %g1
	bgu	.L22
	 nop
.L21:
	.loc 1 67 0 is_stmt 1
	ld	[%fp+88], %g1
	add	%g1, 80, %g2
	ld	[%fp-12], %g1
	cmp	%g2, %g1
	bgu	.L23
	 nop
	.loc 1 69 0
	ld	[%fp+88], %g1
	add	%g1, 79, %g1
	stb	%g0, [%g1]
	.loc 1 70 0
	ld	[%fp+88], %g1
	b	.L28
	 nop
.L23:
	.loc 1 72 0
	ld	[%fp-12], %g1
	st	%g1, [%fp-8]
	.loc 1 73 0
	ld	[%fp-12], %g1
	ldub	[%g1], %g1
	add	%g1, 5, %g1
	mov	%g1, %g2
	ld	[%fp-12], %g1
	stb	%g2, [%g1]
	.loc 1 74 0
	b	.L24
	 nop
.L27:
	.loc 1 76 0
	ld	[%fp-12], %g1
	mov	48, %g2
	stb	%g2, [%g1]
	.loc 1 77 0
	ld	[%fp-12], %g2
	ld	[%fp+88], %g1
	cmp	%g2, %g1
	bleu	.L25
	 nop
	.loc 1 78 0
	ld	[%fp-12], %g1
	add	%g1, -1, %g1
	st	%g1, [%fp-12]
	ld	[%fp-12], %g1
	ldub	[%g1], %g1
	add	%g1, 1, %g1
	mov	%g1, %g2
	ld	[%fp-12], %g1
	stb	%g2, [%g1]
	b	.L24
	 nop
.L25:
	.loc 1 81 0
	ld	[%fp-12], %g1
	mov	49, %g2
	stb	%g2, [%g1]
	.loc 1 82 0
	ld	[%fp+80], %g1
	ld	[%g1], %g1
	add	%g1, 1, %g2
	ld	[%fp+80], %g1
	st	%g2, [%g1]
	.loc 1 83 0
	ld	[%fp+92], %g1
	cmp	%g1, 0
	bne	.L24
	 nop
	.loc 1 85 0
	ld	[%fp-8], %g2
	ld	[%fp+88], %g1
	cmp	%g2, %g1
	bleu	.L26
	 nop
	.loc 1 85 0 is_stmt 0 discriminator 1
	ld	[%fp-8], %g1
	mov	48, %g2
	stb	%g2, [%g1]
.L26:
	.loc 1 86 0 is_stmt 1
	ld	[%fp-8], %g1
	add	%g1, 1, %g1
	st	%g1, [%fp-8]
.L24:
	.loc 1 74 0 discriminator 1
	ld	[%fp-12], %g1
	ldub	[%g1], %g1
	sll	%g1, 24, %g1
	sra	%g1, 24, %g1
	cmp	%g1, 57
	bg	.L27
	 nop
	.loc 1 90 0
	ld	[%fp-8], %g1
	stb	%g0, [%g1]
	.loc 1 91 0
	ld	[%fp+88], %g1
.L28:
	.loc 1 92 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE1:
	.size	cvt, .-cvt
	.align 4
	.global ecvt
	.type	ecvt, #function
	.proc	0102
ecvt:
.LFB2:
	.loc 1 95 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI2:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	std	%i0, [%fp-8]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	.loc 1 96 0
	mov	1, %g1
	st	%g1, [%sp+92]
	ldd	[%fp-8], %o0
	ld	[%fp+76], %o2
	ld	[%fp+80], %o3
	ld	[%fp+84], %o4
	sethi	%hi(CVTBUF), %g1
	or	%g1, %lo(CVTBUF), %o5
	call	cvt, 0
	 nop
	mov	%o0, %g1
	.loc 1 97 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE2:
	.size	ecvt, .-ecvt
	.align 4
	.global ecvtbuf
	.type	ecvtbuf, #function
	.proc	0102
ecvtbuf:
.LFB3:
	.loc 1 100 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI3:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	std	%i0, [%fp-8]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%i5, [%fp+88]
	.loc 1 101 0
	mov	1, %g1
	st	%g1, [%sp+92]
	ldd	[%fp-8], %o0
	ld	[%fp+76], %o2
	ld	[%fp+80], %o3
	ld	[%fp+84], %o4
	ld	[%fp+88], %o5
	call	cvt, 0
	 nop
	mov	%o0, %g1
	.loc 1 102 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE3:
	.size	ecvtbuf, .-ecvtbuf
	.align 4
	.global fcvt
	.type	fcvt, #function
	.proc	0102
fcvt:
.LFB4:
	.loc 1 105 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI4:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	std	%i0, [%fp-8]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	.loc 1 106 0
	st	%g0, [%sp+92]
	ldd	[%fp-8], %o0
	ld	[%fp+76], %o2
	ld	[%fp+80], %o3
	ld	[%fp+84], %o4
	sethi	%hi(CVTBUF), %g1
	or	%g1, %lo(CVTBUF), %o5
	call	cvt, 0
	 nop
	mov	%o0, %g1
	.loc 1 107 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE4:
	.size	fcvt, .-fcvt
	.align 4
	.global fcvtbuf
	.type	fcvtbuf, #function
	.proc	0102
fcvtbuf:
.LFB5:
	.loc 1 110 0
	.cfi_startproc
	save	%sp, -112, %sp
.LCFI5:
	.cfi_window_save
	.cfi_register 15, 31
	.cfi_def_cfa_register 30
	std	%i0, [%fp-8]
	st	%i2, [%fp+76]
	st	%i3, [%fp+80]
	st	%i4, [%fp+84]
	st	%i5, [%fp+88]
	.loc 1 111 0
	st	%g0, [%sp+92]
	ldd	[%fp-8], %o0
	ld	[%fp+76], %o2
	ld	[%fp+80], %o3
	ld	[%fp+84], %o4
	ld	[%fp+88], %o5
	call	cvt, 0
	 nop
	mov	%o0, %g1
	.loc 1 112 0
	mov	%g1, %i0
	restore
	jmp	%o7+8
	 nop
	.cfi_endproc
.LFE5:
	.size	fcvtbuf, .-fcvtbuf
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x32f
	.uahalf	0x2
	.uaword	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.uaword	.LASF21
	.byte	0x1
	.uaword	.LASF22
	.uaword	.Ltext0
	.uaword	.Letext0
	.uaword	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF0
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.uaword	.LASF1
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.uaword	.LASF2
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.uaword	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.uaword	.LASF4
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.uaword	.LASF6
	.uleb128 0x4
	.byte	0x1
	.uaword	.LASF14
	.byte	0x1
	.byte	0x5
	.byte	0x1
	.uaword	0xad
	.uaword	.LFB0
	.uaword	.LFE0
	.uaword	.LLST0
	.byte	0x1
	.uaword	0xad
	.uleb128 0x5
	.asciz	"X"
	.byte	0x1
	.byte	0x5
	.uaword	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x5
	.asciz	"itr"
	.byte	0x1
	.byte	0x5
	.uaword	0xb4
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0x6
	.asciz	"I"
	.byte	0x1
	.byte	0x7
	.uaword	0x2f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x7
	.uaword	.LASF7
	.byte	0x1
	.byte	0xa
	.uaword	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.uaword	.LASF8
	.uleb128 0x8
	.byte	0x4
	.uaword	0xad
	.uleb128 0x9
	.asciz	"cvt"
	.byte	0x1
	.byte	0xf
	.byte	0x1
	.uaword	0x171
	.uaword	.LFB1
	.uaword	.LFE1
	.uaword	.LLST1
	.byte	0x1
	.uaword	0x171
	.uleb128 0x5
	.asciz	"arg"
	.byte	0x1
	.byte	0xf
	.uaword	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xa
	.uaword	.LASF9
	.byte	0x1
	.byte	0xf
	.uaword	0x2f
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xa
	.uaword	.LASF10
	.byte	0x1
	.byte	0xf
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0xa
	.uaword	.LASF11
	.byte	0x1
	.byte	0xf
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.uleb128 0x5
	.asciz	"buf"
	.byte	0x1
	.byte	0xf
	.uaword	0x171
	.byte	0x3
	.byte	0x91
	.sleb128 88
	.uleb128 0xa
	.uaword	.LASF12
	.byte	0x1
	.byte	0xf
	.uaword	0x2f
	.byte	0x3
	.byte	0x91
	.sleb128 92
	.uleb128 0x6
	.asciz	"r2"
	.byte	0x1
	.byte	0x11
	.uaword	0x2f
	.byte	0x2
	.byte	0x91
	.sleb128 -4
	.uleb128 0x6
	.asciz	"fi"
	.byte	0x1
	.byte	0x12
	.uaword	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x6
	.asciz	"fj"
	.byte	0x1
	.byte	0x12
	.uaword	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x6
	.asciz	"p"
	.byte	0x1
	.byte	0x13
	.uaword	0x171
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0x6
	.asciz	"p1"
	.byte	0x1
	.byte	0x13
	.uaword	0x171
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x8
	.byte	0x4
	.uaword	0x177
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.uaword	.LASF13
	.uleb128 0x8
	.byte	0x4
	.uaword	0x2f
	.uleb128 0xb
	.byte	0x1
	.uaword	.LASF15
	.byte	0x1
	.byte	0x5e
	.byte	0x1
	.uaword	0x171
	.uaword	.LFB2
	.uaword	.LFE2
	.uaword	.LLST2
	.byte	0x1
	.uaword	0x1de
	.uleb128 0x5
	.asciz	"arg"
	.byte	0x1
	.byte	0x5e
	.uaword	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xa
	.uaword	.LASF9
	.byte	0x1
	.byte	0x5e
	.uaword	0x2f
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xa
	.uaword	.LASF10
	.byte	0x1
	.byte	0x5e
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0xa
	.uaword	.LASF11
	.byte	0x1
	.byte	0x5e
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.byte	0
	.uleb128 0xb
	.byte	0x1
	.uaword	.LASF16
	.byte	0x1
	.byte	0x63
	.byte	0x1
	.uaword	0x171
	.uaword	.LFB3
	.uaword	.LFE3
	.uaword	.LLST3
	.byte	0x1
	.uaword	0x247
	.uleb128 0x5
	.asciz	"arg"
	.byte	0x1
	.byte	0x63
	.uaword	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xa
	.uaword	.LASF9
	.byte	0x1
	.byte	0x63
	.uaword	0x2f
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xa
	.uaword	.LASF10
	.byte	0x1
	.byte	0x63
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0xa
	.uaword	.LASF11
	.byte	0x1
	.byte	0x63
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.uleb128 0x5
	.asciz	"buf"
	.byte	0x1
	.byte	0x63
	.uaword	0x171
	.byte	0x3
	.byte	0x91
	.sleb128 88
	.byte	0
	.uleb128 0xb
	.byte	0x1
	.uaword	.LASF17
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.uaword	0x171
	.uaword	.LFB4
	.uaword	.LFE4
	.uaword	.LLST4
	.byte	0x1
	.uaword	0x2a1
	.uleb128 0x5
	.asciz	"arg"
	.byte	0x1
	.byte	0x68
	.uaword	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xa
	.uaword	.LASF9
	.byte	0x1
	.byte	0x68
	.uaword	0x2f
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xa
	.uaword	.LASF10
	.byte	0x1
	.byte	0x68
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0xa
	.uaword	.LASF11
	.byte	0x1
	.byte	0x68
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.byte	0
	.uleb128 0xb
	.byte	0x1
	.uaword	.LASF18
	.byte	0x1
	.byte	0x6d
	.byte	0x1
	.uaword	0x171
	.uaword	.LFB5
	.uaword	.LFE5
	.uaword	.LLST5
	.byte	0x1
	.uaword	0x30a
	.uleb128 0x5
	.asciz	"arg"
	.byte	0x1
	.byte	0x6d
	.uaword	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -8
	.uleb128 0xa
	.uaword	.LASF9
	.byte	0x1
	.byte	0x6d
	.uaword	0x2f
	.byte	0x3
	.byte	0x91
	.sleb128 76
	.uleb128 0xa
	.uaword	.LASF10
	.byte	0x1
	.byte	0x6d
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 80
	.uleb128 0xa
	.uaword	.LASF11
	.byte	0x1
	.byte	0x6d
	.uaword	0x17e
	.byte	0x3
	.byte	0x91
	.sleb128 84
	.uleb128 0x5
	.asciz	"buf"
	.byte	0x1
	.byte	0x6d
	.uaword	0x171
	.byte	0x3
	.byte	0x91
	.sleb128 88
	.byte	0
	.uleb128 0xc
	.uaword	0x177
	.uaword	0x31a
	.uleb128 0xd
	.uaword	0x31a
	.byte	0x4f
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.uaword	.LASF19
	.uleb128 0x7
	.uaword	.LASF20
	.byte	0x1
	.byte	0x3
	.uaword	0x30a
	.byte	0x5
	.byte	0x3
	.uaword	CVTBUF
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
	.uleb128 0x3
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
	.uleb128 0x4
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
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.uaword	.LFB0-.Ltext0
	.uaword	.LCFI0-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI0-.Ltext0
	.uaword	.LFE0-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST1:
	.uaword	.LFB1-.Ltext0
	.uaword	.LCFI1-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI1-.Ltext0
	.uaword	.LFE1-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST2:
	.uaword	.LFB2-.Ltext0
	.uaword	.LCFI2-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI2-.Ltext0
	.uaword	.LFE2-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST3:
	.uaword	.LFB3-.Ltext0
	.uaword	.LCFI3-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI3-.Ltext0
	.uaword	.LFE3-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST4:
	.uaword	.LFB4-.Ltext0
	.uaword	.LCFI4-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI4-.Ltext0
	.uaword	.LFE4-.Ltext0
	.uahalf	0x2
	.byte	0x8e
	.sleb128 0
	.uaword	0
	.uaword	0
.LLST5:
	.uaword	.LFB5-.Ltext0
	.uaword	.LCFI5-.Ltext0
	.uahalf	0x2
	.byte	0x7e
	.sleb128 0
	.uaword	.LCFI5-.Ltext0
	.uaword	.LFE5-.Ltext0
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
.LASF10:
	.asciz	"decpt"
.LASF20:
	.asciz	"CVTBUF"
.LASF7:
	.asciz	"ret_val"
.LASF3:
	.asciz	"unsigned char"
.LASF16:
	.asciz	"ecvtbuf"
.LASF11:
	.asciz	"sign"
.LASF4:
	.asciz	"short unsigned int"
.LASF15:
	.asciz	"ecvt"
.LASF18:
	.asciz	"fcvtbuf"
.LASF8:
	.asciz	"double"
.LASF9:
	.asciz	"ndigits"
.LASF14:
	.asciz	"__modf"
.LASF22:
	.asciz	"/home/ajit4/ajit-toolchain/AjitPublicResources/tools/minimal_printf_timer/src/cvt.c"
.LASF5:
	.asciz	"unsigned int"
.LASF6:
	.asciz	"long long unsigned int"
.LASF12:
	.asciz	"eflag"
.LASF19:
	.asciz	"sizetype"
.LASF2:
	.asciz	"long long int"
.LASF13:
	.asciz	"char"
.LASF17:
	.asciz	"fcvt"
.LASF21:
	.asciz	"GNU C 4.7.4"
.LASF1:
	.asciz	"short int"
.LASF0:
	.asciz	"signed char"
	.ident	"GCC: (Buildroot 2014.08-ga2bdb80-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
