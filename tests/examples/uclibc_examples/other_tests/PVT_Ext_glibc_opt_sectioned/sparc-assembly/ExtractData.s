	.file	"ExtractData.c"
	.section	.text.NavIdentifyFrameID,"ax",@progbits
	.align 4
	.global NavIdentifyFrameID
	.type	NavIdentifyFrameID, #function
	.proc	014
NavIdentifyFrameID:
	ld	[%o0+12], %o0
	and	%o0, 24, %o0
	jmp	%o7+8
	 srl	%o0, 3, %o0
	.size	NavIdentifyFrameID, .-NavIdentifyFrameID
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	-1065402368
	.long	0
	.section	.text.InitNavFrameOneParameters,"ax",@progbits
	.align 4
	.global InitNavFrameOneParameters
	.type	InitNavFrameOneParameters, #function
	.proc	020
InitNavFrameOneParameters:
	sll	%o0, 4, %g1
	sll	%o0, 7, %o0
	add	%g1, %o0, %o0
	sethi	%hi(.LC0), %g1
	mov	-500, %g2
	ldd	[%g1+%lo(.LC0)], %f8
	sethi	%hi(NavSubFrame1Data), %g3
	or	%g3, %lo(NavSubFrame1Data), %g3
	add	%g3, %o0, %g1
	std	%f8, [%g3+%o0]
	st	%g2, [%g1+132]
	std	%f8, [%g1+8]
	std	%f8, [%g1+16]
	st	%g2, [%g1+128]
	std	%f8, [%g1+24]
	std	%f8, [%g1+32]
	std	%f8, [%g1+40]
	std	%f8, [%g1+48]
	std	%f8, [%g1+56]
	std	%f8, [%g1+64]
	std	%f8, [%g1+72]
	std	%f8, [%g1+80]
	std	%f8, [%g1+88]
	std	%f8, [%g1+96]
	std	%f8, [%g1+104]
	jmp	%o7+8
	 st	%g2, [%g1+136]
	.size	InitNavFrameOneParameters, .-InitNavFrameOneParameters
	.section	.rodata.cst8
	.align 8
.LC1:
	.long	-1065402368
	.long	0
	.section	.text.InitNavFrameTwoParameters,"ax",@progbits
	.align 4
	.global InitNavFrameTwoParameters
	.type	InitNavFrameTwoParameters, #function
	.proc	020
InitNavFrameTwoParameters:
	sll	%o0, 4, %g1
	sethi	%hi(.LC1), %g3
	sethi	%hi(NavSubFrame2Data), %g2
	ldd	[%g3+%lo(.LC1)], %f8
	or	%g2, %lo(NavSubFrame2Data), %g2
	sll	%o0, 6, %o0
	mov	-500, %g3
	add	%g1, %o0, %o0
	add	%g2, %o0, %g1
	std	%f8, [%g2+%o0]
	st	%g3, [%g1+64]
	std	%f8, [%g1+8]
	std	%f8, [%g1+16]
	std	%f8, [%g1+24]
	std	%f8, [%g1+32]
	std	%f8, [%g1+40]
	std	%f8, [%g1+48]
	jmp	%o7+8
	 std	%f8, [%g1+56]
	.size	InitNavFrameTwoParameters, .-InitNavFrameTwoParameters
	.section	.text.InitNavFrameThreeAndFourParameters,"ax",@progbits
	.align 4
	.global InitNavFrameThreeAndFourParameters
	.type	InitNavFrameThreeAndFourParameters, #function
	.proc	020
InitNavFrameThreeAndFourParameters:
	sll	%o0, 2, %g2
	mov	-500, %g1
	sethi	%hi(NavSubFrame3_4Data), %g3
	sll	%o0, 5, %o0
	or	%g3, %lo(NavSubFrame3_4Data), %g3
	sub	%o0, %g2, %o0
	add	%g3, %o0, %g2
	st	%g1, [%g3+%o0]
	st	%g1, [%g2+4]
	st	%g1, [%g2+8]
	st	%g1, [%g2+12]
	st	%g1, [%g2+16]
	st	%g1, [%g2+20]
	jmp	%o7+8
	 sth	%g1, [%g2+24]
	.size	InitNavFrameThreeAndFourParameters, .-InitNavFrameThreeAndFourParameters
	.section	.rodata.cst8
	.align 8
.LC2:
	.long	-1065402368
	.long	0
	.section	.text.InitNavMessageNineParameters,"ax",@progbits
	.align 4
	.global InitNavMessageNineParameters
	.type	InitNavMessageNineParameters, #function
	.proc	020
InitNavMessageNineParameters:
	sethi	%hi(NavUTCCorr), %g2
	sethi	%hi(.LC2), %g3
	or	%g2, %lo(NavUTCCorr), %g1
	ldd	[%g3+%lo(.LC2)], %f8
	std	%f8, [%g2+%lo(NavUTCCorr)]
	std	%f8, [%g1+8]
	mov	-500, %g2
	std	%f8, [%g1+16]
	std	%f8, [%g1+24]
	std	%f8, [%g1+32]
	std	%f8, [%g1+40]
	std	%f8, [%g1+48]
	std	%f8, [%g1+56]
	std	%f8, [%g1+64]
	std	%f8, [%g1+72]
	std	%f8, [%g1+80]
	std	%f8, [%g1+88]
	std	%f8, [%g1+96]
	std	%f8, [%g1+104]
	jmp	%o7+8
	 st	%g2, [%g1+112]
	.size	InitNavMessageNineParameters, .-InitNavMessageNineParameters
	.section	.rodata.cst8
	.align 8
.LC3:
	.long	-1065402368
	.long	0
	.section	.text.InitNavMessageElevenParameters,"ax",@progbits
	.align 4
	.global InitNavMessageElevenParameters
	.type	InitNavMessageElevenParameters, #function
	.proc	020
InitNavMessageElevenParameters:
	sethi	%hi(NavIonoCorrction), %g2
	sethi	%hi(.LC3), %g3
	or	%g2, %lo(NavIonoCorrction), %g1
	ldd	[%g3+%lo(.LC3)], %f8
	std	%f8, [%g2+%lo(NavIonoCorrction)]
	std	%f8, [%g1+8]
	std	%f8, [%g1+16]
	std	%f8, [%g1+24]
	std	%f8, [%g1+32]
	std	%f8, [%g1+40]
	std	%f8, [%g1+48]
	jmp	%o7+8
	 std	%f8, [%g1+56]
	.size	InitNavMessageElevenParameters, .-InitNavMessageElevenParameters
	.section	.rodata.cst8
	.align 8
.LC5:
	.long	1073741824
	.long	0
	.align 8
.LC6:
	.long	1074340347
	.long	1413752350
	.align 8
.LC7:
	.long	1076887552
	.long	0
	.section	.text.NavExtractDataFrameOne,"ax",@progbits
	.align 4
	.global NavExtractDataFrameOne
	.type	NavExtractDataFrameOne, #function
	.proc	020
NavExtractDataFrameOne:
	save	%sp, -120, %sp
	sethi	%hi(temp_frame1), %i1
	or	%i1, %lo(temp_frame1), %i5
	st	%g0, [%i1+%lo(temp_frame1)]
	st	%g0, [%i5+132]
	st	%g0, [%i5+128]
	st	%g0, [%i5+136]
	st	%g0, [%i1+%lo(temp_frame1+4)]
	st	%g0, [%i5+8]
	st	%g0, [%i5+12]
	st	%g0, [%i5+16]
	st	%g0, [%i5+20]
	st	%g0, [%i5+24]
	st	%g0, [%i5+28]
	st	%g0, [%i5+32]
	st	%g0, [%i5+36]
	st	%g0, [%i5+40]
	st	%g0, [%i5+44]
	st	%g0, [%i5+48]
	st	%g0, [%i5+52]
	st	%g0, [%i5+56]
	st	%g0, [%i5+60]
	st	%g0, [%i5+64]
	st	%g0, [%i5+68]
	st	%g0, [%i5+72]
	st	%g0, [%i5+76]
	st	%g0, [%i5+80]
	st	%g0, [%i5+84]
	st	%g0, [%i5+88]
	st	%g0, [%i5+92]
	st	%g0, [%i5+96]
	st	%g0, [%i5+100]
	st	%g0, [%i5+104]
	st	%g0, [%i5+108]
	st	%g0, [%i5+124]
	ld	[%i0+128], %g1
	st	%g0, [%i5+112]
	sra	%g1, 31, %g2
	wr	%g2, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 6, %g1
	st	%g0, [%i5+116]
	st	%g1, [%i0+128]
	sethi	%hi(.LC5), %l0
	mov	0, %i3
	mov	1, %i2
	and	%i3, 0xff, %g1
	cmp	%g1, 3
	bleu	.L90
	 or	%l0, %lo(.LC5), %i4
	add	%i3, -4, %g2
.L140:
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L91
	 cmp	%g1, 12
	be	.L92
	 mov	13, %o2
	ldd	[%i5+104], %f10
	ld	[%i0+120], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+120], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+104]
	sra	%g1, 1, %g1
	st	%g1, [%i0+120]
.L10:
	and	%i2, 0xff, %g1
	cmp	%g1, 14
	be,a	.L139
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L141:
	add	%i2, 1, %i2
.L137:
	and	%i3, 0xff, %g1
	cmp	%g1, 3
	bgu	.L140
	 add	%i3, -4, %g2
.L90:
	ld	[%i0+128], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+128], %g1
	ldd	[%i5+104], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+104]
	sra	%g1, 1, %g1
	st	%g1, [%i0+128]
	and	%i2, 0xff, %g1
	cmp	%g1, 14
	bne,a	.L141
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L139:
	ldd	[%l0+%lo(.LC5)], %o0
	mov	-43, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	sethi	%hi(.LC6), %i2
	fmuld	%f0, %f8, %f0
	ldd	[%i2+%lo(.LC6)], %f10
	mov	0, %i3
	fmuld	%f0, %f10, %f8
	b	.L17
	 std	%f8, [%i5+104]
.L14:
	bne	.L94
	 mov	14, %o2
	ldd	[%i5+96], %f10
	ld	[%i0+112], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+112], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+96]
	sra	%g1, 1, %g1
	st	%g1, [%i0+112]
.L15:
	add	%i3, 1, %i3
	cmp	%i3, 15
	be,a	.L142
	 std	%f8, [%fp-8]
.L17:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L14
	 cmp	%g1, 14
	ld	[%i0+120], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+120], %g1
	ldd	[%i5+96], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+96]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 15
	bne	.L17
	 st	%g1, [%i0+120]
	std	%f8, [%fp-8]
.L142:
	ldd	[%l0+%lo(.LC5)], %o0
	mov	-4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i3
	fmuld	%f0, %f8, %f0
	b	.L21
	 std	%f0, [%i5+96]
.L18:
	bne	.L96
	 mov	14, %o2
	ldd	[%i5+88], %f10
	ld	[%i0+108], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+108], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+88]
	sra	%g1, 1, %g1
	st	%g1, [%i0+108]
.L19:
	add	%i3, 1, %i3
	cmp	%i3, 15
	be,a	.L143
	 std	%f8, [%fp-8]
.L21:
	and	%i3, 0xff, %g1
	cmp	%g1, 6
	bgu	.L18
	 cmp	%g1, 14
	ld	[%i0+112], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+112], %g1
	ldd	[%i5+88], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+88]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 15
	bne	.L21
	 st	%g1, [%i0+112]
	std	%f8, [%fp-8]
.L143:
	ldd	[%l0+%lo(.LC5)], %o0
	mov	-4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i3
	fmuld	%f0, %f8, %f0
	b	.L25
	 std	%f0, [%i5+88]
.L22:
	bne	.L98
	 mov	14, %o2
	ldd	[%i5+80], %f10
	ld	[%i0+100], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+100], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+80]
	sra	%g1, 1, %g1
	st	%g1, [%i0+100]
.L23:
	add	%i3, 1, %i3
	cmp	%i3, 15
	be,a	.L144
	 std	%f8, [%fp-8]
.L25:
	and	%i3, 0xff, %g1
	cmp	%g1, 7
	bgu	.L22
	 cmp	%g1, 14
	ld	[%i0+104], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+104], %g1
	ldd	[%i5+80], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+80]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 15
	bne	.L25
	 st	%g1, [%i0+104]
	std	%f8, [%fp-8]
.L144:
	ldd	[%l0+%lo(.LC5)], %o0
	mov	-28, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+80]
	mov	0, %i3
	andcc	%i3, 0xff, %g1
	be	.L100
	 mov	1, %l1
	add	%i3, -1, %g2
.L145:
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L101
	 cmp	%g1, 14
	bne	.L102
	 mov	14, %o2
	ldd	[%i5+72], %f10
	ld	[%i0+92], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+92], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+72]
	sra	%g1, 1, %g1
	st	%g1, [%i0+92]
.L30:
	and	%l1, 0xff, %g1
	cmp	%g1, 15
	be	.L103
	 add	%l1, 1, %l1
	add	%i3, 1, %i3
.L104:
	andcc	%i3, 0xff, %g1
	bne	.L145
	 add	%i3, -1, %g2
.L100:
	ld	[%i0+100], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	0, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+100], %g1
	ldd	[%i5+72], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+72]
	st	%g1, [%i0+100]
	add	%i3, 1, %i3
	b	.L104
	 add	%l1, 1, %l1
.L94:
	ld	[%i0+116], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+116], %g1
	ldd	[%i5+96], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+96]
	sra	%g1, 1, %g1
	b	.L15
	 st	%g1, [%i0+116]
.L91:
	ld	[%i0+124], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+124], %g1
	ldd	[%i5+104], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+104]
	sra	%g1, 1, %g1
	b	.L10
	 st	%g1, [%i0+124]
.L96:
	ld	[%i0+108], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+108], %g1
	ldd	[%i5+88], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+88]
	sra	%g1, 1, %g1
	b	.L19
	 st	%g1, [%i0+108]
.L98:
	ld	[%i0+100], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+100], %g1
	ldd	[%i5+80], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+80]
	sra	%g1, 1, %g1
	b	.L23
	 st	%g1, [%i0+100]
.L103:
	std	%f8, [%fp-8]
	ldd	[%l0+%lo(.LC5)], %o0
	mov	-28, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i3
	fmuld	%f0, %f8, %f0
	b	.L36
	 std	%f0, [%i5+72]
.L34:
	bne	.L105
	 mov	14, %o2
	ldd	[%i5+64], %f10
	ld	[%i0+84], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+84], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+64]
	sra	%g1, 1, %g1
	st	%g1, [%i0+84]
.L33:
	add	%i3, 1, %i3
	cmp	%i3, 15
	be,a	.L146
	 std	%f8, [%fp-8]
.L36:
	and	%i3, 0xff, %g1
	cmp	%g1, 1
	bleu	.L107
	 add	%i3, -2, %g2
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bgu	.L34
	 cmp	%g1, 14
	ld	[%i0+88], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+88], %g1
	ldd	[%i5+64], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+64]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 15
	bne	.L36
	 st	%g1, [%i0+88]
	std	%f8, [%fp-8]
.L146:
	ldd	[%l0+%lo(.LC5)], %o0
	mov	-28, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i3
	fmuld	%f0, %f8, %f0
	b	.L41
	 std	%f0, [%i5+64]
.L37:
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L108
	 cmp	%g1, 14
	bne	.L109
	 mov	14, %o2
	ldd	[%i5+56], %f10
	ld	[%i0+76], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+76], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	st	%g1, [%i0+76]
.L38:
	add	%i3, 1, %i3
	cmp	%i3, 15
	be	.L147
	 ldd	[%l0+%lo(.LC5)], %o0
.L41:
	and	%i3, 0xff, %g1
	cmp	%g1, 2
	bgu	.L37
	 add	%i3, -3, %g2
	ld	[%i0+84], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+84], %g1
	ldd	[%i5+56], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 15
	bne	.L41
	 st	%g1, [%i0+84]
	ldd	[%l0+%lo(.LC5)], %o0
.L147:
	mov	-28, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ld	[%i0+76], %g1
	and	%g1, 1, %g1
	st	%g1, [%i5+112]
	ld	[%i0+76], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+76]
	and	%g1, 1, %g1
	st	%g1, [%i5+116]
	ld	[%i0+68], %g3
	and	%g3, 1, %g3
	st	%g3, [%fp-20]
	ldd	[%fp-8], %f8
	ld	[%fp-20], %f14
	ld	[%i0+76], %g1
	fitod	%f14, %f10
	srl	%g1, 31, %g2
	fmuld	%f0, %f8, %f0
	add	%g2, %g1, %g1
	std	%f0, [%i5+56]
	sra	%g1, 1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	mov	0, %o2
	mov	0, %o3
	st	%g1, [%i0+76]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+68], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+48], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %l1
	faddd	%f0, %f8, %f8
	add	%l1, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %l1
	mov	1, %o2
	mov	0, %o3
	std	%f8, [%i5+48]
	call	xx__pow_opt, 0
	 st	%l1, [%i0+68]
	ld	[%i0+68], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %i3
	and	%l1, 1, %l1
	add	%i3, %g1, %g1
	st	%l1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i3
	ldd	[%l0+%lo(.LC5)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%i3, [%i0+68]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ld	[%i0+68], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %l1
	and	%i3, 1, %i3
	add	%l1, %g1, %g1
	st	%i3, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l1
	ldd	[%l0+%lo(.LC5)], %o0
	mov	3, %o2
	mov	0, %o3
	st	%l1, [%i0+68]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ld	[%i0+68], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %i3
	and	%l1, 1, %l1
	add	%i3, %g1, %g1
	st	%l1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i3
	ldd	[%l0+%lo(.LC5)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%i3, [%i0+68]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ld	[%i0+68], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %l1
	and	%i3, 1, %i3
	add	%l1, %g1, %g1
	st	%i3, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l1
	ldd	[%l0+%lo(.LC5)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%l1, [%i0+68]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ld	[%i0+68], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %i3
	and	%l1, 1, %l1
	add	%i3, %g1, %g1
	st	%l1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i3
	ldd	[%l0+%lo(.LC5)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%i3, [%i0+68]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ld	[%i0+68], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %l1
	and	%i3, 1, %i3
	add	%l1, %g1, %g1
	st	%i3, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l1
	std	%f8, [%i5+48]
	st	%l1, [%i0+68]
	ldd	[%l0+%lo(.LC5)], %o0
	mov	7, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%i5+48], %f8
	and	%l1, 1, %l1
	st	%l1, [%fp-20]
	ld	[%i0+68], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %g2
	fitod	%f12, %f10
	add	%g2, %g1, %g1
	fmuld	%f10, %f0, %f0
	sra	%g1, 1, %g1
	faddd	%f0, %f8, %f8
	mov	0, %i3
	st	%g1, [%i0+68]
	b	.L46
	 std	%f8, [%i5+48]
.L42:
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L111
	 cmp	%g1, 21
	bne	.L112
	 mov	21, %o2
	ldd	[%i5+40], %f10
	ld	[%i0+56], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+56], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	st	%g1, [%i0+56]
.L43:
	add	%i3, 1, %i3
	cmp	%i3, 22
	be	.L148
	 ldd	[%l0+%lo(.LC5)], %o0
.L46:
	and	%i3, 0xff, %g1
	cmp	%g1, 7
	bgu	.L42
	 add	%i3, -8, %g2
	ld	[%i0+64], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+64], %g1
	ldd	[%i5+40], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 22
	bne	.L46
	 st	%g1, [%i0+64]
	ldd	[%l0+%lo(.LC5)], %o0
.L148:
	mov	-41, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ldd	[%fp-8], %f8
	ldd	[%i2+%lo(.LC6)], %f10
	ld	[%i0+56], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	fmuld	%f0, %f8, %f0
	ld	[%fp-20], %f14
	fmuld	%f0, %f10, %f8
	fitod	%f14, %f10
	std	%f8, [%i5+40]
	ldd	[%l0+%lo(.LC5)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+56], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+32], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i3
	faddd	%f0, %f8, %f8
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	1, %o2
	mov	0, %o3
	std	%f8, [%i5+32]
	call	xx__pow_opt, 0
	 st	%i3, [%i0+56]
	ldd	[%i5+32], %f8
	ld	[%i0+52], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i3, 1, %i3
	ld	[%fp-20], %f12
	st	%i3, [%fp-20]
	ld	[%i0+56], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %g3
	fitod	%f12, %f10
	add	%g3, %g1, %g1
	fitod	%f14, %f12
	sra	%g1, 1, %g1
	fmuld	%f12, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+32]
	ldd	[%l0+%lo(.LC5)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%g1, [%i0+56]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+52], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+32], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i3
	faddd	%f0, %f8, %f8
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	3, %o2
	mov	0, %o3
	std	%f8, [%i5+32]
	call	xx__pow_opt, 0
	 st	%i3, [%i0+52]
	ld	[%i0+52], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i2
	and	%i3, 1, %i3
	add	%i2, %g1, %g1
	st	%i3, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i2
	ldd	[%l0+%lo(.LC5)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%i2, [%i0+52]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+52], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i3
	and	%i2, 1, %i2
	add	%i3, %g1, %g1
	st	%i2, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i3
	ldd	[%l0+%lo(.LC5)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%i3, [%i0+52]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+52], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i2
	and	%i3, 1, %i3
	add	%i2, %g1, %g1
	st	%i3, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i2
	ldd	[%l0+%lo(.LC5)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%i2, [%i0+52]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ldd	[%i5+32], %f8
	and	%i2, 1, %i2
	st	%i2, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f10
	ld	[%i0+52], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i3
	faddd	%f0, %f8, %f10
	add	%i3, %g1, %g1
	std	%f10, [%i5+32]
	sra	%g1, 1, %i3
	ldd	[%l0+%lo(.LC5)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%i3, [%i0+52]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ld	[%i0+52], %g1
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f8, %f0, %f0
	add	%g2, %g1, %g1
	fsubd	%f10, %f0, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+32]
	std	%f8, [%fp-8]
	ldd	[%l0+%lo(.LC5)], %o0
	st	%g1, [%i0+52]
	mov	-31, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i3
	fmuld	%f8, %f0, %f0
	b	.L50
	 std	%f0, [%i5+32]
.L49:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+44], %g1
	ldd	[%i5+24], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	st	%g1, [%i0+44]
.L48:
	add	%i3, 1, %i3
	cmp	%i3, 16
	be,a	.L149
	 ld	[%i0+44], %g1
.L50:
	and	%i3, 0xff, %g1
	cmp	%g1, 1
	bleu	.L115
	 add	%i3, -2, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bgu,a	.L49
	 ld	[%i0+44], %g1
	ld	[%i0+48], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+48], %g1
	ldd	[%i5+24], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 16
	bne	.L50
	 st	%g1, [%i0+48]
	ld	[%i0+44], %g1
.L149:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	sethi	%hi(.LC7), %g1
	ld	[%fp-20], %f14
	ldd	[%g1+%lo(.LC7)], %f12
	fitod	%f14, %f10
	fmuld	%f8, %f12, %f8
	std	%f8, [%i5+24]
	ldd	[%l0+%lo(.LC5)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	ld	[%i5+128], %f10
	fitod	%f10, %f8
	faddd	%f0, %f8, %f10
	fdtoi	%f10, %f10
	st	%f10, [%i5+128]
	ld	[%i0+44], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i3, [%i0+44]
	ld	[%i5+128], %f12
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f12, %f8
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+128]
	ld	[%i0+44], %g1
	ld	[%i0+40], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f10
	fitod	%f10, %f8
	ldd	[%l0+%lo(.LC5)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%g1, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ldd	[%fp-8], %f8
	ld	[%i5+128], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+128]
	ld	[%i0+40], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	3, %o2
	st	%i3, [%i0+40]
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i5+128], %f14
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f14, %f8
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+128]
	ld	[%i0+40], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+40]
	mov	0, %i3
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bleu	.L116
	 mov	1, %i2
	cmp	%g1, 6
.L151:
	be	.L117
	 mov	7, %o2
	ldd	[%i5+16], %f10
	ld	[%i0+36], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+36], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+16]
	sra	%g1, 1, %g1
	st	%g1, [%i0+36]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	be,a	.L150
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L152:
	add	%i2, 1, %i2
.L138:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L151
	 cmp	%g1, 6
.L116:
	ld	[%i0+40], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+40], %g1
	ldd	[%i5+16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+16]
	sra	%g1, 1, %g1
	st	%g1, [%i0+40]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	bne	.L152
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L150:
	ldd	[%l0+%lo(.LC5)], %o0
	mov	-55, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+16]
	mov	0, %i3
	mov	1, %l2
	and	%i3, 0xff, %i2
	cmp	%i2, 5
	bleu	.L119
	 mov	%i3, %l1
.L57:
	add	%l1, -6, %l1
	and	%l1, 0xff, %l1
	cmp	%l1, 7
	bleu,a	.L153
	 ld	[%i0+32], %g1
.L58:
	cmp	%i2, 14
	be	.L121
	 cmp	%i2, 15
	be,a	.L122
	 ldd	[%i5+8], %f10
.L59:
	and	%l2, 0xff, %g1
	cmp	%g1, 16
	be	.L123
	 add	%l2, 1, %l2
	add	%i3, 1, %i3
.L124:
	and	%i3, 0xff, %i2
	cmp	%i2, 5
	bgu	.L57
	 mov	%i3, %l1
.L119:
	ld	[%i0+36], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	mov	%i2, %o2
	std	%f10, [%fp-16]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+36], %g1
	ldd	[%i5+8], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+8]
	add	%l1, -6, %l1
	and	%l1, 0xff, %l1
	cmp	%l1, 7
	bgu	.L58
	 st	%g1, [%i0+36]
	ld	[%i0+32], %g1
.L153:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+32], %g1
	ldd	[%i5+8], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+8]
	b	.L59
	 st	%g1, [%i0+32]
.L101:
	ld	[%i0+96], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+96], %g1
	ldd	[%i5+72], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+72]
	sra	%g1, 1, %g1
	b	.L30
	 st	%g1, [%i0+96]
.L105:
	ld	[%i0+84], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+84], %g1
	ldd	[%i5+64], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+64]
	sra	%g1, 1, %g1
	b	.L33
	 st	%g1, [%i0+84]
.L102:
	ld	[%i0+92], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+92], %g1
	ldd	[%i5+72], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+72]
	sra	%g1, 1, %g1
	b	.L30
	 st	%g1, [%i0+92]
.L107:
	ld	[%i0+92], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+92], %g1
	ldd	[%i5+64], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+64]
	sra	%g1, 1, %g1
	b	.L33
	 st	%g1, [%i0+92]
.L108:
	ld	[%i0+80], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+80], %g1
	ldd	[%i5+56], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	b	.L38
	 st	%g1, [%i0+80]
.L109:
	ld	[%i0+76], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+76], %g1
	ldd	[%i5+56], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	b	.L38
	 st	%g1, [%i0+76]
.L111:
	ld	[%i0+60], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+60], %g1
	ldd	[%i5+40], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	b	.L43
	 st	%g1, [%i0+60]
.L112:
	ld	[%i0+56], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+56], %g1
	ldd	[%i5+40], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	b	.L43
	 st	%g1, [%i0+56]
.L115:
	ld	[%i0+52], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+52], %g1
	ldd	[%i5+24], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	b	.L48
	 st	%g1, [%i0+52]
.L121:
	ld	[%i0+28], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	14, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+28], %g1
	ldd	[%i5+8], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+8]
	st	%g1, [%i0+28]
	add	%i3, 1, %i3
	b	.L124
	 add	%l2, 1, %l2
.L122:
	ld	[%i0+28], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%l0+%lo(.LC5)], %o0
	mov	15, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+28], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	st	%g1, [%i0+28]
.L62:
	std	%f8, [%fp-8]
	ldd	[%l0+%lo(.LC5)], %o0
	mov	-43, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i3
	fmuld	%f8, %f0, %f0
	b	.L68
	 std	%f0, [%i5+8]
.L63:
	add	%i2, -6, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu,a	.L154
	 ld	[%i0+24], %g1
	add	%i2, -14, %i2
.L155:
	and	%i2, 0xff, %i2
	cmp	%i2, 6
	bleu	.L126
	 cmp	%l1, 21
	be	.L127
	 ldd	[%i1+%lo(temp_frame1)], %f10
.L65:
	add	%i3, 1, %i3
	cmp	%i3, 22
	be	.L67
	 ldd	[%i1+%lo(temp_frame1)], %f8
.L68:
	and	%i3, 0xff, %l1
	cmp	%l1, 5
	bgu	.L63
	 mov	%i3, %i2
	ld	[%i0+28], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	mov	%i3, %o2
	std	%f10, [%fp-16]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+28], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	st	%g1, [%i0+28]
	add	%i2, -6, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bgu,a	.L155
	 add	%i2, -14, %i2
	ld	[%i0+24], %g1
.L154:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+24], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	b	.L65
	 st	%g1, [%i0+24]
.L126:
	ld	[%i0+20], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+20], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	b	.L65
	 st	%g1, [%i0+20]
.L127:
	ld	[%i0+20], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%l0+%lo(.LC5)], %o0
	mov	21, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+20], %g1
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	ldd	[%fp-16], %f10
	add	%g2, %g1, %g1
	fsubd	%f10, %f0, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i1+%lo(temp_frame1)]
	st	%g1, [%i0+20]
.L67:
	ldd	[%l0+%lo(.LC5)], %o0
	mov	-31, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ldd	[%fp-8], %f8
	ld	[%i0+16], %g1
	fmuld	%f0, %f8, %f0
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%l0+%lo(.LC5)], %o0
	mov	0, %o2
	mov	0, %o3
	std	%f10, [%fp-16]
	call	xx__pow_opt, 0
	 std	%f0, [%i1+%lo(temp_frame1)]
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	ld	[%i5+132], %f10
	fitod	%f10, %f8
	faddd	%f0, %f8, %f10
	fdtoi	%f10, %f10
	st	%f10, [%i5+132]
	ld	[%i0+16], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i3, [%i0+16]
	ld	[%i5+132], %f12
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f12, %f8
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+132]
	ld	[%i0+16], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i3, [%i0+16]
	ld	[%i5+132], %f10
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f10, %f8
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+132]
	ld	[%i0+16], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i3, [%i0+16]
	ld	[%i5+132], %f14
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f14, %f8
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+132]
	ld	[%i0+16], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	4, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i3, [%i0+16]
	ld	[%i5+132], %f14
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f14, %f8
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+132]
	ld	[%i0+16], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	5, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i3, [%i0+16]
	ld	[%i5+132], %f14
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f14, %f8
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+132]
	ld	[%i0+16], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	6, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i3, [%i0+16]
	ld	[%i5+132], %f14
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f14, %f8
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+132]
	ld	[%i0+16], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	7, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i3, [%i0+16]
	ld	[%i5+132], %f14
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f14, %f8
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+132]
	ld	[%i0+16], %g1
	ld	[%i0+12], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f14
	fitod	%f14, %f8
	ldd	[%l0+%lo(.LC5)], %o0
	mov	8, %o2
	mov	0, %o3
	st	%g1, [%i0+16]
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ldd	[%fp-8], %f8
	fmuld	%f8, %f0, %f0
	ld	[%i5+132], %f8
	fitod	%f8, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+132]
	ld	[%i0+12], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%l0+%lo(.LC5)], %o0
	sra	%g1, 1, %i3
	mov	9, %o2
	st	%i3, [%i0+12]
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i5+132], %f10
	and	%i3, 1, %i3
	st	%i3, [%fp-20]
	fitod	%f10, %f8
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+132]
	ld	[%i0+12], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+12]
	mov	0, %g3
	and	%g3, 0xff, %g2
	cmp	%g2, 2
	bgu	.L70
	 mov	1, %g4
	srl	%g1, 31, %g2
.L156:
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+12]
	and	%g4, 0xff, %g2
.L157:
	cmp	%g2, 6
	be	.L129
	 add	%g3, 1, %g3
	add	%g4, 1, %g4
.L132:
	and	%g3, 0xff, %g2
	cmp	%g2, 2
	bleu,a	.L156
	 srl	%g1, 31, %g2
.L70:
	cmp	%g2, 3
	be	.L131
	 cmp	%g2, 4
	bne	.L157
	 and	%g4, 0xff, %g2
	and	%g1, 1, %g1
	st	%g1, [%i5+124]
.L88:
	ld	[%i0+12], %g1
	add	%g3, 1, %g3
	srl	%g1, 31, %g2
	add	%g4, 1, %g4
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L132
	 st	%g1, [%i0+12]
.L129:
	mov	0, %i3
	mov	1, %i2
	and	%i3, 0xff, %o2
	andcc	%i3, 0xff, %g0
	be	.L133
	 mov	0, %o3
.L76:
	add	%i3, -1, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu,a	.L134
	 ld	[%i0+8], %g1
	ld	[%i0+4], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f8
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ldd	[%fp-8], %f8
	fmuld	%f8, %f0, %f0
	ld	[%i5+136], %f8
	fitod	%f8, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+136]
	ld	[%i0+4], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+4]
.L79:
	and	%i2, 0xff, %g1
	cmp	%g1, 17
	be	.L158
	 add	%i3, 1, %i3
	add	%i2, 1, %i2
.L136:
	and	%i3, 0xff, %o2
	andcc	%i3, 0xff, %g0
	bne	.L76
	 mov	0, %o3
.L133:
	ld	[%i0+12], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 mov	0, %o2
	ldd	[%fp-8], %f8
	fmuld	%f8, %f0, %f0
	ld	[%i5+136], %f8
	fitod	%f8, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+136]
	add	%i3, 1, %i3
	ld	[%i0+12], %g1
	add	%i2, 1, %i2
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L136
	 st	%g1, [%i0+12]
.L158:
	jmp	%i7+8
	 restore
.L134:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i5+136], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+136]
	ld	[%i0+8], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L79
	 st	%g1, [%i0+8]
.L92:
	ld	[%i0+120], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	12, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+120], %g1
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+104]
	st	%g1, [%i0+120]
	add	%i3, 1, %i3
	b	.L137
	 add	%i2, 1, %i2
.L131:
	and	%g1, 1, %g1
	b	.L88
	 st	%g1, [%i5+120]
.L117:
	ld	[%i0+36], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	6, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+36], %g1
	ldd	[%i5+16], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+16]
	st	%g1, [%i0+36]
	add	%i3, 1, %i3
	b	.L138
	 add	%i2, 1, %i2
.L123:
	b	.L62
	 ldd	[%i5+8], %f8
	.size	NavExtractDataFrameOne, .-NavExtractDataFrameOne
	.section	.rodata.cst8
	.align 8
.LC8:
	.long	0
	.long	0
	.align 8
.LC9:
	.long	1073741824
	.long	0
	.align 8
.LC10:
	.long	1074340347
	.long	1413752350
	.align 8
.LC11:
	.long	1076887552
	.long	0
	.section	.text.NavExtractDataFrameTwo,"ax",@progbits
	.align 4
	.global NavExtractDataFrameTwo
	.type	NavExtractDataFrameTwo, #function
	.proc	020
NavExtractDataFrameTwo:
	save	%sp, -120, %sp
	ld	[%i0+128], %g1
	sra	%g1, 31, %g2
	wr	%g2, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 6, %g1
	sethi	%hi(temp_frame2), %l0
	sethi	%hi(.LC9), %i1
	or	%l0, %lo(temp_frame2), %i5
	st	%g1, [%i0+128]
	st	%g0, [%i5+64]
	sethi	%hi(.LC8), %g1
	st	%g0, [%l0+%lo(temp_frame2)]
	st	%g0, [%l0+%lo(temp_frame2+4)]
	st	%g0, [%i5+8]
	st	%g0, [%i5+12]
	st	%g0, [%i5+16]
	st	%g0, [%i5+20]
	st	%g0, [%i5+24]
	st	%g0, [%i5+28]
	st	%g0, [%i5+32]
	st	%g0, [%i5+36]
	st	%g0, [%i5+40]
	st	%g0, [%i5+44]
	st	%g0, [%i5+48]
	st	%g0, [%i5+52]
	st	%g0, [%i5+56]
	st	%g0, [%i5+60]
	st	%g0, [%i5+68]
	mov	0, %i3
	ldd	[%g1+%lo(.LC8)], %f8
	b	.L166
	 or	%i1, %lo(.LC9), %i4
.L160:
	add	%i3, -4, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 7
	bleu	.L230
	 add	%g1, -12, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 7
	bleu	.L231
	 add	%g1, -20, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu	.L232
	 cmp	%g2, 31
	ld	[%i0+112], %g1
	ldd	[%i4], %o0
	bne	.L233
	 and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	std	%f8, [%fp-8]
	std	%f10, [%fp-16]
	mov	31, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+112], %g1
	ldd	[%fp-16], %f10
	ldd	[%fp-8], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f8, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	st	%g1, [%i0+112]
.L161:
	add	%i3, 1, %i3
	cmp	%i3, 32
	be,a	.L280
	 std	%f8, [%fp-8]
.L166:
	and	%i3, 0xff, %g2
	cmp	%g2, 3
	bgu	.L160
	 mov	%i3, %g1
	ld	[%i0+128], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+128], %g1
	ldd	[%i5+56], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 32
	bne	.L166
	 st	%g1, [%i0+128]
	std	%f8, [%fp-8]
.L280:
	ldd	[%i1+%lo(.LC9)], %o0
	mov	-31, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	sethi	%hi(.LC10), %l1
	fmuld	%f0, %f8, %f0
	ldd	[%l1+%lo(.LC10)], %f10
	fmuld	%f0, %f10, %f8
	std	%f8, [%i5+56]
	mov	0, %i3
	mov	1, %i2
	and	%i3, 0xff, %g2
	cmp	%g2, 3
	bleu	.L235
	 mov	%i3, %g1
.L168:
	add	%i3, -4, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 7
	bleu	.L236
	 add	%g1, -12, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu	.L237
	 cmp	%g2, 20
	be	.L238
	 mov	21, %o2
	ldd	[%i5+48], %f10
	ld	[%i0+100], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+100], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+48]
	sra	%g1, 1, %g1
	st	%g1, [%i0+100]
.L169:
	and	%i2, 0xff, %g1
	cmp	%g1, 22
	be,a	.L281
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L282:
	add	%i2, 1, %i2
.L274:
	and	%i3, 0xff, %g2
	cmp	%g2, 3
	bgu	.L168
	 mov	%i3, %g1
.L235:
	ld	[%i0+112], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%g2, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+112], %g1
	ldd	[%i5+48], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+48]
	sra	%g1, 1, %g1
	st	%g1, [%i0+112]
	and	%i2, 0xff, %g1
	cmp	%g1, 22
	bne	.L282
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L281:
	ldd	[%i1+%lo(.LC9)], %o0
	mov	-41, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ldd	[%l1+%lo(.LC10)], %f10
	fmuld	%f0, %f8, %f0
	fmuld	%f0, %f10, %f8
	std	%f8, [%i5+48]
	mov	0, %i3
	mov	1, %i2
	and	%i3, 0xff, %g2
	cmp	%g2, 5
	bleu	.L240
	 mov	%i3, %g1
.L175:
	add	%i3, -6, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 7
	bleu	.L241
	 add	%g1, -14, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 7
	bleu	.L242
	 add	%g1, -22, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu	.L243
	 cmp	%g2, 30
	be	.L244
	 mov	31, %o2
	ldd	[%i5+40], %f10
	ld	[%i0+84], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+84], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	st	%g1, [%i0+84]
.L176:
	and	%i2, 0xff, %g1
	cmp	%g1, 32
	be,a	.L283
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L284:
	add	%i2, 1, %i2
.L272:
	and	%i3, 0xff, %g2
	cmp	%g2, 5
	bgu	.L175
	 mov	%i3, %g1
.L240:
	ld	[%i0+100], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%g2, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+100], %g1
	ldd	[%i5+40], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	st	%g1, [%i0+100]
	and	%i2, 0xff, %g1
	cmp	%g1, 32
	bne	.L284
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L283:
	ldd	[%i1+%lo(.LC9)], %o0
	mov	-31, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ldd	[%l1+%lo(.LC10)], %f10
	fmuld	%f0, %f8, %f0
	fmuld	%f0, %f10, %f8
	std	%f8, [%i5+40]
	mov	0, %i3
	mov	1, %i2
	and	%i3, 0xff, %g2
	cmp	%g2, 5
	bleu	.L246
	 mov	%i3, %g1
.L183:
	add	%i3, -6, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 7
	bleu	.L247
	 add	%g1, -14, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 7
	bleu	.L248
	 add	%g1, -22, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu	.L249
	 cmp	%g2, 30
	be	.L250
	 mov	31, %o2
	ldd	[%i5+32], %f10
	ld	[%i0+68], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+68], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+32]
	sra	%g1, 1, %g1
	st	%g1, [%i0+68]
.L184:
	and	%i2, 0xff, %g1
	cmp	%g1, 32
	be,a	.L285
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L286:
	add	%i2, 1, %i2
.L273:
	and	%i3, 0xff, %g2
	cmp	%g2, 5
	bgu	.L183
	 mov	%i3, %g1
.L246:
	ld	[%i0+84], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%g2, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+84], %g1
	ldd	[%i5+32], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+32]
	sra	%g1, 1, %g1
	st	%g1, [%i0+84]
	and	%i2, 0xff, %g1
	cmp	%g1, 32
	bne,a	.L286
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L285:
	ldd	[%i1+%lo(.LC9)], %o0
	mov	-31, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ldd	[%l1+%lo(.LC10)], %f10
	fmuld	%f0, %f8, %f0
	mov	0, %i3
	fmuld	%f0, %f10, %f10
	b	.L195
	 std	%f10, [%i5+32]
.L190:
	add	%i3, -6, %g2
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L252
	 add	%g1, -14, %g2
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L253
	 add	%g1, -22, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu	.L254
	 mov	%i3, %o2
	ld	[%i0+52], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+52], %g1
	ldd	[%i5+24], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	st	%g1, [%i0+52]
.L191:
	add	%i3, 1, %i3
	cmp	%i3, 32
	be,a	.L287
	 std	%f8, [%fp-8]
.L195:
	and	%i3, 0xff, %g2
	cmp	%g2, 5
	bgu	.L190
	 mov	%i3, %g1
	ld	[%i0+68], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+68], %g1
	ldd	[%i5+24], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 32
	bne	.L195
	 st	%g1, [%i0+68]
	std	%f8, [%fp-8]
.L287:
	ldd	[%i1+%lo(.LC9)], %o0
	mov	-19, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i3
	fmuld	%f0, %f8, %f0
	b	.L201
	 std	%f0, [%i5+24]
.L196:
	add	%i3, -6, %g2
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L256
	 add	%g1, -14, %g2
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L257
	 add	%g1, -22, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu	.L258
	 mov	%i3, %o2
	ld	[%i0+36], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+36], %g1
	ldd	[%i5+16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+16]
	sra	%g1, 1, %g1
	st	%g1, [%i0+36]
.L197:
	add	%i3, 1, %i3
	cmp	%i3, 32
	be,a	.L288
	 std	%f8, [%fp-8]
.L201:
	and	%i3, 0xff, %g2
	cmp	%g2, 5
	bgu	.L196
	 mov	%i3, %g1
	ld	[%i0+52], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+52], %g1
	ldd	[%i5+16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+16]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 32
	bne	.L201
	 st	%g1, [%i0+52]
	std	%f8, [%fp-8]
.L288:
	ldd	[%i1+%lo(.LC9)], %o0
	mov	-33, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i3
	fmuld	%f0, %f8, %f0
	b	.L205
	 std	%f0, [%i5+16]
.L202:
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu	.L260
	 mov	%i3, %o2
	ld	[%i0+28], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+28], %g1
	ldd	[%i5+8], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	st	%g1, [%i0+28]
.L203:
	add	%i3, 1, %i3
	cmp	%i3, 16
	be	.L289
	 sethi	%hi(.LC11), %g1
.L205:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L202
	 add	%i3, -6, %g1
	ld	[%i0+36], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+36], %g1
	ldd	[%i5+8], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	add	%i3, 1, %i3
	cmp	%i3, 16
	bne	.L205
	 st	%g1, [%i0+36]
	sethi	%hi(.LC11), %g1
.L289:
	ldd	[%g1+%lo(.LC11)], %f10
	fmuld	%f8, %f10, %f8
	std	%f8, [%i5+8]
	mov	0, %i3
	mov	1, %i2
	and	%i3, 0xff, %g2
	cmp	%g2, 5
	bleu	.L262
	 mov	%i3, %g1
.L207:
	add	%i3, -6, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 7
	bleu	.L263
	 add	%g1, -14, %g3
	and	%g3, 0xff, %g3
	cmp	%g3, 7
	bleu	.L264
	 add	%g1, -22, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu	.L265
	 cmp	%g2, 30
	be	.L266
	 mov	31, %o2
	ldd	[%i5], %f10
	ld	[%i0+12], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+12], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5]
	sra	%g1, 1, %g1
	st	%g1, [%i0+12]
.L208:
	and	%i2, 0xff, %g1
	cmp	%g1, 32
	be,a	.L290
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L291:
	add	%i2, 1, %i2
.L279:
	and	%i3, 0xff, %g2
	cmp	%g2, 5
	bgu	.L207
	 mov	%i3, %g1
.L262:
	ld	[%i0+28], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%g2, %o2
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+28], %g1
	ldd	[%i5], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5]
	sra	%g1, 1, %g1
	st	%g1, [%i0+28]
	and	%i2, 0xff, %g1
	cmp	%g1, 32
	bne,a	.L291
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L290:
	ldd	[%i1+%lo(.LC9)], %o0
	mov	-31, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%l1+%lo(.LC10)], %f10
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	fmuld	%f0, %f10, %f10
	std	%f10, [%l0+%lo(temp_frame2)]
	mov	0, %g2
	and	%g2, 0xff, %g1
	cmp	%g1, 2
	bgu	.L215
	 mov	1, %g3
	ld	[%i0+12], %g1
.L292:
	srl	%g1, 31, %g4
	add	%g4, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+12]
	and	%g3, 0xff, %g1
.L293:
	cmp	%g1, 6
	be	.L268
	 add	%g2, 1, %g2
	add	%g3, 1, %g3
.L271:
	and	%g2, 0xff, %g1
	cmp	%g1, 2
	bleu,a	.L292
	 ld	[%i0+12], %g1
.L215:
	cmp	%g1, 3
	be	.L270
	 cmp	%g1, 4
	bne	.L293
	 and	%g3, 0xff, %g1
	ld	[%i0+12], %g1
	and	%g1, 1, %g1
	st	%g1, [%i5+68]
.L229:
	ld	[%i0+12], %g1
	add	%g2, 1, %g2
	srl	%g1, 31, %g4
	add	%g3, 1, %g3
	add	%g4, %g1, %g1
	sra	%g1, 1, %g1
	b	.L271
	 st	%g1, [%i0+12]
.L230:
	ld	[%i0+124], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+124], %g1
	ldd	[%i5+56], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	b	.L161
	 st	%g1, [%i0+124]
.L231:
	ld	[%i0+120], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+120], %g1
	ldd	[%i5+56], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	b	.L161
	 st	%g1, [%i0+120]
.L232:
	ld	[%i0+116], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+116], %g1
	ldd	[%i5+56], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	b	.L161
	 st	%g1, [%i0+116]
.L233:
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i3, %o2
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+112], %g1
	ldd	[%i5+56], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	b	.L161
	 st	%g1, [%i0+112]
.L247:
	ld	[%i0+80], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+80], %g1
	ldd	[%i5+32], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+32]
	sra	%g1, 1, %g1
	b	.L184
	 st	%g1, [%i0+80]
.L252:
	ld	[%i0+64], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+64], %g1
	ldd	[%i5+24], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	b	.L191
	 st	%g1, [%i0+64]
.L241:
	ld	[%i0+96], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+96], %g1
	ldd	[%i5+40], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	b	.L176
	 st	%g1, [%i0+96]
.L253:
	ld	[%i0+60], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+60], %g1
	ldd	[%i5+24], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	b	.L191
	 st	%g1, [%i0+60]
.L242:
	ld	[%i0+92], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+92], %g1
	ldd	[%i5+40], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	b	.L176
	 st	%g1, [%i0+92]
.L248:
	ld	[%i0+76], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+76], %g1
	ldd	[%i5+32], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+32]
	sra	%g1, 1, %g1
	b	.L184
	 st	%g1, [%i0+76]
.L236:
	ld	[%i0+108], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+108], %g1
	ldd	[%i5+48], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+48]
	sra	%g1, 1, %g1
	b	.L169
	 st	%g1, [%i0+108]
.L249:
	ld	[%i0+72], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+72], %g1
	ldd	[%i5+32], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+32]
	sra	%g1, 1, %g1
	b	.L184
	 st	%g1, [%i0+72]
.L254:
	ld	[%i0+56], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+56], %g1
	ldd	[%i5+24], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	b	.L191
	 st	%g1, [%i0+56]
.L243:
	ld	[%i0+88], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+88], %g1
	ldd	[%i5+40], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	b	.L176
	 st	%g1, [%i0+88]
.L237:
	ld	[%i0+104], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+104], %g1
	ldd	[%i5+48], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+48]
	sra	%g1, 1, %g1
	b	.L169
	 st	%g1, [%i0+104]
.L244:
	ld	[%i0+84], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	30, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+84], %g1
	ldd	[%i5+40], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+40]
	st	%g1, [%i0+84]
	add	%i3, 1, %i3
	b	.L272
	 add	%i2, 1, %i2
.L250:
	ld	[%i0+68], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	30, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+68], %g1
	ldd	[%i5+32], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+32]
	st	%g1, [%i0+68]
	add	%i3, 1, %i3
	b	.L273
	 add	%i2, 1, %i2
.L238:
	ld	[%i0+100], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	20, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+100], %g1
	ldd	[%i5+48], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+48]
	st	%g1, [%i0+100]
	add	%i3, 1, %i3
	b	.L274
	 add	%i2, 1, %i2
.L256:
	ld	[%i0+48], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+48], %g1
	ldd	[%i5+16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+16]
	sra	%g1, 1, %g1
	b	.L197
	 st	%g1, [%i0+48]
.L257:
	ld	[%i0+44], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	mov	%i3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+44], %g1
	ldd	[%i5+16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+16]
	sra	%g1, 1, %g1
	b	.L197
	 st	%g1, [%i0+44]
.L258:
	ld	[%i0+40], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+40], %g1
	ldd	[%i5+16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+16]
	sra	%g1, 1, %g1
	b	.L197
	 st	%g1, [%i0+40]
.L260:
	ld	[%i0+32], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+32], %g1
	ldd	[%i5+8], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	b	.L203
	 st	%g1, [%i0+32]
.L268:
	mov	0, %i3
	mov	1, %i2
	and	%i3, 0xff, %o2
	andcc	%i3, 0xff, %g0
	be	.L275
	 mov	0, %o3
.L221:
	add	%i3, -1, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu,a	.L276
	 ld	[%i0+8], %g1
	ld	[%i0+4], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f8
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ldd	[%fp-8], %f8
	ld	[%i5+64], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+64]
	ld	[%i0+4], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+4]
.L224:
	and	%i2, 0xff, %g1
	cmp	%g1, 17
	be	.L294
	 add	%i3, 1, %i3
	add	%i2, 1, %i2
.L278:
	and	%i3, 0xff, %o2
	andcc	%i3, 0xff, %g0
	bne	.L221
	 mov	0, %o3
.L275:
	ld	[%i0+12], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 mov	0, %o2
	ldd	[%fp-8], %f8
	ld	[%i5+64], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+64]
	add	%i3, 1, %i3
	ld	[%i0+12], %g1
	add	%i2, 1, %i2
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L278
	 st	%g1, [%i0+12]
.L294:
	jmp	%i7+8
	 restore
.L263:
	ld	[%i0+24], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+24], %g1
	ldd	[%i5], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5]
	sra	%g1, 1, %g1
	b	.L208
	 st	%g1, [%i0+24]
.L264:
	ld	[%i0+20], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+20], %g1
	ldd	[%i5], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5]
	sra	%g1, 1, %g1
	b	.L208
	 st	%g1, [%i0+20]
.L276:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i5+64], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+64]
	ld	[%i0+8], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L224
	 st	%g1, [%i0+8]
.L265:
	ld	[%i0+16], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+16], %g1
	ldd	[%i5], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5]
	sra	%g1, 1, %g1
	b	.L208
	 st	%g1, [%i0+16]
.L266:
	ld	[%i0+12], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	30, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+12], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	st	%g1, [%i0+12]
	add	%i3, 1, %i3
	b	.L279
	 add	%i2, 1, %i2
.L270:
	ld	[%i0+12], %g1
	and	%g1, 1, %g1
	b	.L229
	 st	%g1, [%i5+72]
	.size	NavExtractDataFrameTwo, .-NavExtractDataFrameTwo
	.section	.rodata.cst8
	.align 8
.LC13:
	.long	1073741824
	.long	0
	.align 8
.LC14:
	.long	1106247680
	.long	0
	.align 8
.LC15:
	.long	1105199104
	.long	0
	.align 8
.LC16:
	.long	1076887552
	.long	0
	.section	.text.NavExtractMsgNine,"ax",@progbits
	.align 4
	.global NavExtractMsgNine
	.type	NavExtractMsgNine, #function
	.proc	020
NavExtractMsgNine:
	save	%sp, -120, %sp
	sethi	%hi(temp_UTCCorr), %g1
	or	%g1, %lo(temp_UTCCorr), %i5
	st	%g0, [%i5+112]
	st	%g0, [%i5+96]
	ld	[%i0+96], %g2
	st	%g0, [%i5+100]
	st	%g0, [%i5+104]
	st	%g0, [%i5+108]
	st	%g0, [%i5+92]
	sethi	%hi(.LC13), %i3
	sra	%g2, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%g2, 5, %g2
	sethi	%hi(.LC15), %l0
	st	%g0, [%g1+%lo(temp_UTCCorr)]
	st	%g0, [%g1+%lo(temp_UTCCorr+4)]
	st	%g0, [%i5+8]
	st	%g0, [%i5+12]
	st	%g0, [%i5+16]
	st	%g0, [%i5+20]
	st	%g0, [%i5+24]
	st	%g0, [%i5+28]
	st	%g0, [%i5+32]
	st	%g0, [%i5+36]
	st	%g0, [%i5+40]
	st	%g0, [%i5+44]
	st	%g0, [%i5+48]
	st	%g0, [%i5+52]
	st	%g0, [%i5+56]
	st	%g0, [%i5+60]
	st	%g0, [%i5+64]
	st	%g0, [%i5+68]
	st	%g0, [%i5+72]
	st	%g0, [%i5+76]
	st	%g0, [%i5+80]
	st	%g0, [%i5+84]
	st	%g0, [%i5+88]
	st	%g2, [%i0+96]
	mov	1, %i1
	mov	0, %i4
	or	%i3, %lo(.LC13), %i2
	or	%l0, %lo(.LC15), %l0
	sethi	%hi(-2147483648), %l1
	sethi	%hi(.LC14), %l2
.L296:
	andcc	%i4, 0xff, %g0
	be	.L328
	 and	%i4, 0xff, %o2
	ld	[%i0+92], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i5+112], %f10
	fmuld	%f8, %f0, %f0
	ld	[%i5+112], %g1
	cmp	%g1, 0
	bl	.L329
	 fitod	%f10, %f8
	faddd	%f0, %f8, %f8
	ldd	[%l0], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L345
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
.L344:
	st	%f8, [%i5+112]
.L304:
	ld	[%i0+92], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	and	%i1, 0xff, %g2
	cmp	%g2, 3
	bne	.L301
	 st	%g1, [%i0+92]
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+92], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+92], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+92], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+92], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	4, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+92], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	5, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+92], %g1
	ld	[%i0+88], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	ldd	[%i3+%lo(.LC13)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%g1, [%i0+92]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+88], %g1
	and	%g1, 1, %g3
	srl	%g1, 31, %g2
	st	%g3, [%fp-20]
	add	%g2, %g1, %g1
	ld	[%fp-20], %f10
	sra	%g1, 1, %g1
	fitod	%f10, %f10
	ldd	[%i3+%lo(.LC13)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%g1, [%i0+92]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+88], %g1
	and	%g1, 1, %g3
	srl	%g1, 31, %g2
	st	%g3, [%fp-20]
	add	%g2, %g1, %g1
	ld	[%fp-20], %f10
	sra	%g1, 1, %g1
	fitod	%f10, %f10
	ldd	[%i3+%lo(.LC13)], %o0
	mov	8, %o2
	mov	0, %o3
	st	%g1, [%i0+92]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+88], %g1
	srl	%g1, 31, %g2
	and	%g1, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f10
	fitod	%f10, %f10
	st	%g1, [%i0+92]
	std	%f10, [%fp-16]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	9, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+88], %g1
	mov	0, %i4
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L308
	 st	%g1, [%i0+92]
.L305:
	add	%i4, -4, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu,a	.L330
	 ld	[%i0+84], %g1
	ld	[%i0+80], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	ldd	[%i2], %o0
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+96], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f0
	std	%f0, [%i5+96]
	ld	[%i0+80], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+80]
.L306:
	add	%i4, 1, %i4
	cmp	%i4, 16
	be,a	.L346
	 ld	[%i0+80], %g1
.L308:
	and	%i4, 0xff, %g1
	mov	%i4, %o2
	cmp	%g1, 3
	bgu	.L305
	 mov	0, %o3
	ld	[%i0+88], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i2], %o0
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+96], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f0
	std	%f0, [%i5+96]
	ld	[%i0+88], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	add	%i4, 1, %i4
	cmp	%i4, 16
	bne	.L308
	 st	%g1, [%i0+88]
	ld	[%i0+80], %g1
.L346:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	sethi	%hi(.LC16), %i1
	ld	[%fp-20], %f16
	ldd	[%i1+%lo(.LC16)], %f8
	fitod	%f16, %f10
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+96]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+88], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+80], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+88]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+80]
	ldd	[%i5+88], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+80], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+88]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+80]
	ldd	[%i5+88], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+80], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+88]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+80]
	ldd	[%i5+88], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+88]
	ld	[%i0+80], %g1
	ld	[%i0+76], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i3+%lo(.LC13)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%g1, [%i0+80]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%fp-16], %f10
	ldd	[%i5+88], %f8
	fmuld	%f10, %f0, %f0
	ld	[%i0+76], %g1
	faddd	%f0, %f8, %f8
	srl	%g1, 31, %i4
	std	%f8, [%i5+88]
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC13)], %o0
	sra	%g1, 1, %i4
	mov	5, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+88], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f10
	ld	[%i0+76], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f10
	add	%i4, %g1, %g1
	std	%f10, [%i5+88]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%i4, [%i0+76]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%fp-16], %f10
	ld	[%i0+76], %g1
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+88]
	sra	%g1, 1, %g1
	ldd	[%i3+%lo(.LC13)], %o0
	mov	-68, %o2
	mov	0, %o3
	st	%g1, [%i0+76]
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ld	[%i0+76], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ldd	[%fp-8], %f8
	ld	[%fp-20], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	std	%f0, [%i5+88]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+80], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+76], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+76], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+76], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+76], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	4, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	ld	[%i0+76], %g1
	ld	[%i0+72], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	ldd	[%i3+%lo(.LC13)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%g1, [%i0+76]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+80], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+72], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	6, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	7, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	8, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	9, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	10, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	11, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f10
	ld	[%i0+72], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f10
	add	%i4, %g1, %g1
	std	%f10, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	12, %o2
	mov	0, %o3
	st	%i4, [%i0+72]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ld	[%i0+72], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+80]
	sra	%g1, 1, %g1
	std	%f8, [%fp-8]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	-51, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%g1, [%i0+72]
	ldd	[%fp-8], %f8
	mov	0, %i4
	fmuld	%f8, %f0, %f0
	b	.L312
	 std	%f0, [%i5+80]
.L309:
	cmp	%g1, 15
	bne	.L332
	 ld	[%i0+64], %g1
	ldd	[%i5+72], %f10
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 ldd	[%i2], %o0
	ldd	[%fp-8], %f8
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	fsubd	%f10, %f0, %f8
.L327:
	std	%f8, [%i5+72]
	ld	[%i0+64], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	add	%i4, 1, %i4
	cmp	%i4, 16
	be	.L333
	 st	%g1, [%i0+64]
.L312:
	and	%i4, 0xff, %g1
	mov	15, %o2
	cmp	%g1, 7
	bgu	.L309
	 mov	0, %o3
	ld	[%i0+68], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i4, %o2
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 ldd	[%i2], %o0
	ldd	[%fp-8], %f8
	ldd	[%i5+72], %f10
	fmuld	%f8, %f0, %f0
	faddd	%f0, %f10, %f8
	std	%f8, [%i5+72]
	ld	[%i0+68], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	add	%i4, 1, %i4
	cmp	%i4, 16
	bne	.L312
	 st	%g1, [%i0+68]
.L333:
	ldd	[%i3+%lo(.LC13)], %o0
	mov	-35, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ld	[%i0+60], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ldd	[%fp-8], %f8
	ld	[%fp-20], %f16
	fmuld	%f0, %f8, %f0
	fitod	%f16, %f10
	std	%f0, [%i5+72]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+64], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+60], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	4, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	5, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	6, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f10
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ld	[%i0+60], %g1
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f10, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%i4, [%i0+60]
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ldd	[%fp-8], %f8
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	fsubd	%f8, %f0, %f8
	std	%f8, [%i5+64]
	ld	[%i0+60], %g1
	ld	[%i0+56], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	st	%g1, [%i0+60]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+56], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+56], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+56]
	ldd	[%i5+56], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+56], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+56]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+56]
	ldd	[%i5+56], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+56], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+56]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+56]
	ldd	[%i5+56], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+56], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %l0
	fitod	%f16, %f10
	add	%l0, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+56]
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%l0, [%i0+56]
	ld	[%i0+56], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	1, %o2
	mov	0, %o3
	st	%i4, [%i0+56]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ld	[%i0+56], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%l0, [%i0+56]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ld	[%i0+56], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	3, %o2
	mov	0, %o3
	st	%i4, [%i0+56]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ldd	[%i5+48], %f8
	ld	[%i0+52], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f12
	st	%i4, [%fp-20]
	ld	[%i0+56], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %g3
	fitod	%f12, %f10
	add	%g3, %g1, %g1
	fitod	%f14, %f12
	sra	%g1, 1, %g1
	fmuld	%f12, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%g1, [%i0+56]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+48], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+52], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	5, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	6, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	7, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	8, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	9, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %l0
	fitod	%f12, %f10
	add	%l0, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%l0, [%i0+52]
	ld	[%i0+52], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	1, %o2
	mov	0, %o3
	st	%i4, [%i0+52]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ldd	[%i5+40], %f8
	ld	[%i0+48], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ld	[%fp-20], %f14
	ld	[%i0+52], %g1
	fitod	%f14, %f12
	srl	%g1, 31, %g3
	fmuld	%f12, %f0, %f0
	add	%g3, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+40]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%g1, [%i0+52]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+48], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+40], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC13)], %o0
	sra	%g1, 1, %i4
	mov	3, %o2
	mov	0, %o3
	std	%f8, [%i5+40]
	call	xx__pow_opt, 0
	 st	%i4, [%i0+48]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%l0, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%i4, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%l0, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%i4, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	8, %o2
	mov	0, %o3
	st	%l0, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	9, %o2
	mov	0, %o3
	st	%i4, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ldd	[%i5+40], %f8
	ld	[%i0+44], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ld	[%fp-20], %f14
	ld	[%i0+48], %g1
	fitod	%f14, %f12
	srl	%g1, 31, %g3
	fmuld	%f12, %f0, %f0
	add	%g3, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+40]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	st	%g1, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+44], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+32], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC13)], %o0
	sra	%g1, 1, %i4
	mov	1, %o2
	mov	0, %o3
	std	%f8, [%i5+32]
	call	xx__pow_opt, 0
	 st	%i4, [%i0+44]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%l0, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	3, %o2
	mov	0, %o3
	st	%i4, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%l0, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%i4, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%l0, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%i4, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ldd	[%i5+32], %f8
	ld	[%i0+40], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ld	[%fp-20], %f14
	ld	[%i0+44], %g1
	fitod	%f14, %f12
	srl	%g1, 31, %g3
	fmuld	%f12, %f0, %f0
	add	%g3, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+32]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	8, %o2
	mov	0, %o3
	st	%g1, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+40], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+32], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC13)], %o0
	sra	%g1, 1, %i4
	mov	9, %o2
	mov	0, %o3
	std	%f8, [%i5+32]
	call	xx__pow_opt, 0
	 st	%i4, [%i0+40]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	10, %o2
	mov	0, %o3
	st	%l0, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	11, %o2
	mov	0, %o3
	st	%i4, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	12, %o2
	mov	0, %o3
	st	%l0, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	13, %o2
	mov	0, %o3
	st	%i4, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC13)], %o0
	mov	14, %o2
	mov	0, %o3
	st	%l0, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	15, %o2
	mov	0, %o3
	st	%i4, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	srl	%g1, 31, %g2
	ldd	[%i5+32], %f8
	add	%g2, %g1, %g1
	ld	[%i0+36], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ldd	[%i1+%lo(.LC16)], %f12
	ld	[%fp-20], %f16
	sra	%g1, 1, %g1
	fitod	%f16, %f14
	fmuld	%f14, %f0, %f0
	faddd	%f0, %f8, %f8
	fmuld	%f8, %f12, %f12
	std	%f12, [%i5+32]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	st	%g1, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+36], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+24], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC13)], %o0
	sra	%g1, 1, %i4
	mov	1, %o2
	mov	0, %o3
	std	%f8, [%i5+24]
	call	xx__pow_opt, 0
	 st	%i4, [%i0+36]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%i1, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+24]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i4
	and	%i1, 1, %i1
	add	%i4, %g1, %g1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	3, %o2
	mov	0, %o3
	st	%i4, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+24]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	ldd	[%i3+%lo(.LC13)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%i1, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+24]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i4
	and	%i1, 1, %i1
	add	%i4, %g1, %g1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%i4, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+24]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	std	%f8, [%i5+24]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	6, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i1, [%i0+36]
	ldd	[%i5+24], %f10
	and	%i1, 1, %i1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ld	[%i0+36], %g1
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f10, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%i4, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ld	[%i0+32], %g3
	and	%g3, 1, %g3
	st	%g3, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ld	[%fp-20], %f14
	ld	[%i0+36], %g1
	fitod	%f14, %f12
	srl	%g1, 31, %g2
	fmuld	%f12, %f0, %f0
	add	%g2, %g1, %g1
	ldd	[%fp-8], %f8
	sra	%g1, 1, %g1
	fsubd	%f8, %f0, %f8
	std	%f8, [%i5+24]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	0, %o2
	mov	0, %o3
	st	%g1, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+32], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+16], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i1
	faddd	%f0, %f8, %f8
	add	%i1, %g1, %g1
	ldd	[%i3+%lo(.LC13)], %o0
	sra	%g1, 1, %i1
	mov	1, %o2
	mov	0, %o3
	std	%f8, [%i5+16]
	call	xx__pow_opt, 0
	 st	%i1, [%i0+32]
	ld	[%i0+32], %g1
	ldd	[%i5+16], %f8
	srl	%g1, 31, %i4
	and	%i1, 1, %i1
	add	%i4, %g1, %g1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%i4, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+16]
	ld	[%i0+32], %g1
	ldd	[%i5+16], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	ldd	[%i3+%lo(.LC13)], %o0
	mov	3, %o2
	mov	0, %o3
	st	%i1, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+16]
	ld	[%i0+32], %g1
	ldd	[%i5+16], %f8
	srl	%g1, 31, %i4
	and	%i1, 1, %i1
	add	%i4, %g1, %g1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%i4, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+16]
	ld	[%i0+32], %g1
	ldd	[%i5+16], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	ldd	[%i3+%lo(.LC13)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%i1, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+16]
	ldd	[%i5+16], %f8
	and	%i1, 1, %i1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f10
	ld	[%i0+32], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f10
	add	%i4, %g1, %g1
	std	%f10, [%i5+16]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC13)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%i4, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ld	[%i0+32], %g1
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f8, %f0, %f0
	add	%g2, %g1, %g1
	fsubd	%f10, %f0, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+16]
	st	%g1, [%i0+32]
	std	%f8, [%fp-8]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	-68, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f8, %f0, %f0
	std	%f0, [%i5+16]
	mov	0, %i4
	andcc	%i4, 0xff, %g1
	be	.L334
	 mov	1, %i1
	add	%i4, -1, %g2
.L347:
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L335
	 cmp	%g1, 12
	bne	.L336
	 ld	[%i0+24], %g1
	ldd	[%i5+8], %f10
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i2], %o0
	mov	12, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+24], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	st	%g1, [%i0+24]
.L317:
	and	%i1, 0xff, %g1
	cmp	%g1, 13
	be	.L337
	 add	%i1, 1, %i1
	add	%i4, 1, %i4
.L338:
	andcc	%i4, 0xff, %g1
	bne	.L347
	 add	%i4, -1, %g2
.L334:
	ld	[%i0+32], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i2], %o0
	std	%f10, [%fp-16]
	mov	0, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+32], %g1
	ldd	[%i5+8], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+8]
	st	%g1, [%i0+32]
	add	%i4, 1, %i4
	b	.L338
	 add	%i1, 1, %i1
.L328:
	ld	[%i0+96], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	mov	0, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i5+112], %f10
	fmuld	%f8, %f0, %f0
	ld	[%i5+112], %g1
	cmp	%g1, 0
	bl	.L339
	 fitod	%f10, %f8
.L298:
	faddd	%f0, %f8, %f8
	ldd	[%l0], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L299
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+112]
.L300:
	ld	[%i0+96], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+96]
.L301:
	add	%i4, 1, %i4
	b	.L296
	 add	%i1, 1, %i1
.L299:
	fdtoi	%f8, %f8
	st	%f8, [%fp-20]
	ld	[%fp-20], %g2
	xor	%g2, %l1, %g1
	b	.L300
	 st	%g1, [%i5+112]
.L303:
.L345:
	fdtoi	%f8, %f8
	st	%f8, [%fp-20]
	ld	[%fp-20], %g2
	xor	%g2, %l1, %g1
	b	.L304
	 st	%g1, [%i5+112]
.L330:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i2], %o0
	std	%f10, [%fp-16]
	mov	%i4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%i5+96], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f0
	std	%f0, [%i5+96]
	ld	[%i0+84], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L306
	 st	%g1, [%i0+84]
.L332:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	mov	%i4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ldd	[%i5+72], %f10
	fmuld	%f8, %f0, %f0
	b	.L327
	 faddd	%f0, %f10, %f8
.L337:
	std	%f8, [%fp-8]
	ldd	[%i3+%lo(.LC13)], %o0
	mov	-51, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i4
	fmuld	%f0, %f8, %f0
	b	.L323
	 std	%f0, [%i5+8]
.L319:
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L340
	 cmp	%g1, 15
	bne	.L341
	 mov	15, %o2
	ldd	[%i5], %f8
	ld	[%i0+16], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	std	%f8, [%fp-8]
	std	%f10, [%fp-16]
	ldd	[%i2], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+16], %g1
	ldd	[%fp-16], %f10
	ldd	[%fp-8], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f8, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5]
	sra	%g1, 1, %g1
	st	%g1, [%i0+16]
.L320:
	add	%i4, 1, %i4
	cmp	%i4, 16
	be	.L348
	 nop
.L323:
	and	%i4, 0xff, %g1
	cmp	%g1, 3
	bgu	.L319
	 add	%i4, -4, %g2
	ld	[%i0+24], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	mov	%i4, %o2
	std	%f10, [%fp-16]
	ldd	[%i2], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+24], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	add	%i4, 1, %i4
	cmp	%i4, 16
	bne	.L323
	 st	%g1, [%i0+24]
.L348:
	jmp	%i7+8
	 restore
.L340:
	ld	[%i0+20], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	ldd	[%i2], %o0
	std	%f10, [%fp-16]
	mov	%i4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+20], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	b	.L320
	 st	%g1, [%i0+20]
.L335:
	ld	[%i0+28], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	and	%i4, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+28], %g1
	ldd	[%i5+8], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	b	.L317
	 st	%g1, [%i0+28]
.L341:
	ld	[%i0+16], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	ldd	[%i2], %o0
	std	%f10, [%fp-16]
	mov	%i4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+16], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	b	.L320
	 st	%g1, [%i0+16]
.L336:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	and	%i4, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+24], %g1
	ldd	[%i5+8], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	b	.L317
	 st	%g1, [%i0+24]
.L329:
	ldd	[%l2+%lo(.LC14)], %f10
	faddd	%f8, %f10, %f8
	ldd	[%l0], %f10
	faddd	%f0, %f8, %f8
	fcmped	%f8, %f10
	nop
	fbge,a	.L303
	 fsubd	%f8, %f10, %f8
	b	.L344
	 fdtoi	%f8, %f8
.L339:
	ldd	[%l2+%lo(.LC14)], %f10
	b	.L298
	 faddd	%f8, %f10, %f8
	.size	NavExtractMsgNine, .-NavExtractMsgNine
	.section	.rodata.cst8
	.align 8
.LC17:
	.long	1073741824
	.long	0
	.section	.text.NavExtractMsgEleven,"ax",@progbits
	.align 4
	.global NavExtractMsgEleven
	.type	NavExtractMsgEleven, #function
	.proc	020
NavExtractMsgEleven:
	save	%sp, -120, %sp
	ld	[%i0+116], %g1
	sra	%g1, 31, %g2
	and	%g2, 3, %g2
	add	%g2, %g1, %g1
	sra	%g1, 2, %g1
	st	%g1, [%i0+116]
	sethi	%hi(.LC17), %i1
	mov	0, %i3
	sethi	%hi(temp_Iono_Corr), %i5
	and	%i3, 0xff, %g1
	mov	1, %i2
	or	%i1, %lo(.LC17), %i4
	cmp	%g1, 5
	bleu	.L390
	 or	%i5, %lo(temp_Iono_Corr), %i5
	cmp	%g1, 6
.L423:
	be	.L391
	 mov	7, %o2
	ldd	[%i5+56], %f10
	ld	[%i0+112], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+112], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	st	%g1, [%i0+112]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	be,a	.L422
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L424:
	add	%i2, 1, %i2
.L415:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L423
	 cmp	%g1, 6
.L390:
	ld	[%i0+116], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+116], %g1
	ldd	[%i5+56], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %g1
	st	%g1, [%i0+116]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	bne	.L424
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L422:
	ldd	[%i1+%lo(.LC17)], %o0
	mov	16, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+56]
	mov	0, %i3
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bleu	.L393
	 mov	1, %i2
	cmp	%g1, 6
.L426:
	be	.L394
	 mov	7, %o2
	ldd	[%i5+48], %f10
	ld	[%i0+108], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+108], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+48]
	sra	%g1, 1, %g1
	st	%g1, [%i0+108]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	be,a	.L425
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L427:
	add	%i2, 1, %i2
.L414:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L426
	 cmp	%g1, 6
.L393:
	ld	[%i0+112], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+112], %g1
	ldd	[%i5+48], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+48]
	sra	%g1, 1, %g1
	st	%g1, [%i0+112]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	bne	.L427
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L425:
	ldd	[%i1+%lo(.LC17)], %o0
	mov	16, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+48]
	mov	0, %i3
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bleu	.L396
	 mov	1, %i2
	cmp	%g1, 6
.L429:
	be	.L397
	 mov	7, %o2
	ldd	[%i5+40], %f10
	ld	[%i0+104], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+104], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	st	%g1, [%i0+104]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	be,a	.L428
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L430:
	add	%i2, 1, %i2
.L417:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L429
	 cmp	%g1, 6
.L396:
	ld	[%i0+108], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+108], %g1
	ldd	[%i5+40], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+40]
	sra	%g1, 1, %g1
	st	%g1, [%i0+108]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	bne	.L430
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L428:
	ldd	[%i1+%lo(.LC17)], %o0
	mov	14, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+40]
	mov	0, %i3
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bleu	.L399
	 mov	1, %i2
	cmp	%g1, 6
.L432:
	be	.L400
	 mov	7, %o2
	ldd	[%i5+32], %f10
	ld	[%i0+100], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+100], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+32]
	sra	%g1, 1, %g1
	st	%g1, [%i0+100]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	be,a	.L431
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L433:
	add	%i2, 1, %i2
.L416:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L432
	 cmp	%g1, 6
.L399:
	ld	[%i0+104], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+104], %g1
	ldd	[%i5+32], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+32]
	sra	%g1, 1, %g1
	st	%g1, [%i0+104]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	bne	.L433
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L431:
	ldd	[%i1+%lo(.LC17)], %o0
	mov	11, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+32]
	mov	0, %i3
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bleu	.L402
	 mov	1, %i2
	cmp	%g1, 6
.L435:
	be	.L403
	 ld	[%i0+96], %g1
	ldd	[%i5+24], %f10
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	mov	7, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+96], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	st	%g1, [%i0+96]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	be,a	.L434
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L436:
	add	%i2, 1, %i2
.L419:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L435
	 cmp	%g1, 6
.L402:
	ld	[%i0+100], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+100], %g1
	ldd	[%i5+24], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %g1
	st	%g1, [%i0+100]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	bne	.L436
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L434:
	ldd	[%i1+%lo(.LC17)], %o0
	mov	-24, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+24]
	mov	0, %i3
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bleu	.L405
	 mov	1, %i2
	cmp	%g1, 6
.L438:
	be	.L406
	 ld	[%i0+92], %g1
	ldd	[%i5+16], %f10
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	mov	7, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+92], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+16]
	sra	%g1, 1, %g1
	st	%g1, [%i0+92]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	be,a	.L437
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L439:
	add	%i2, 1, %i2
.L418:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L438
	 cmp	%g1, 6
.L405:
	ld	[%i0+96], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+96], %g1
	ldd	[%i5+16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+16]
	sra	%g1, 1, %g1
	st	%g1, [%i0+96]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	bne	.L439
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L437:
	ldd	[%i1+%lo(.LC17)], %o0
	mov	-24, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+16]
	mov	0, %i3
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bleu	.L408
	 mov	1, %i2
	cmp	%g1, 6
.L441:
	be	.L409
	 ld	[%i0+88], %g1
	ldd	[%i5+8], %f10
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i4], %o0
	mov	7, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+88], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	st	%g1, [%i0+88]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	be,a	.L440
	 std	%f8, [%fp-8]
	add	%i3, 1, %i3
.L442:
	add	%i2, 1, %i2
.L421:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L441
	 cmp	%g1, 6
.L408:
	ld	[%i0+92], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i4], %o0
	std	%f8, [%fp-8]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+92], %g1
	ldd	[%i5+8], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	st	%g1, [%i0+92]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	bne	.L442
	 add	%i3, 1, %i3
	std	%f8, [%fp-8]
.L440:
	ldd	[%i1+%lo(.LC17)], %o0
	mov	-27, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+8]
	mov	0, %i3
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bleu	.L411
	 mov	1, %i2
	cmp	%g1, 6
.L443:
	be	.L412
	 ld	[%i0+84], %g1
	ldd	[%i5], %f8
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	std	%f8, [%fp-8]
	std	%f10, [%fp-16]
	ldd	[%i4], %o0
	mov	7, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+84], %g1
	ldd	[%fp-16], %f10
	ldd	[%fp-8], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f8, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5]
	sra	%g1, 1, %g1
	st	%g1, [%i0+84]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	be	.L445
	 add	%i3, 1, %i3
.L444:
	add	%i2, 1, %i2
.L420:
	and	%i3, 0xff, %g1
	cmp	%g1, 5
	bgu	.L443
	 cmp	%g1, 6
.L411:
	ld	[%i0+88], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	and	%i3, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+88], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	st	%g1, [%i0+88]
	and	%i2, 0xff, %g1
	cmp	%g1, 8
	bne	.L444
	 add	%i3, 1, %i3
.L445:
	jmp	%i7+8
	 restore
.L394:
	ld	[%i0+108], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	6, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+108], %g1
	ldd	[%i5+48], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+48]
	st	%g1, [%i0+108]
	add	%i3, 1, %i3
	b	.L414
	 add	%i2, 1, %i2
.L391:
	ld	[%i0+112], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	6, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+112], %g1
	ldd	[%i5+56], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+56]
	st	%g1, [%i0+112]
	add	%i3, 1, %i3
	b	.L415
	 add	%i2, 1, %i2
.L400:
	ld	[%i0+100], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	6, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+100], %g1
	ldd	[%i5+32], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+32]
	st	%g1, [%i0+100]
	add	%i3, 1, %i3
	b	.L416
	 add	%i2, 1, %i2
.L397:
	ld	[%i0+104], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	6, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+104], %g1
	ldd	[%i5+40], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+40]
	st	%g1, [%i0+104]
	add	%i3, 1, %i3
	b	.L417
	 add	%i2, 1, %i2
.L406:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	6, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+92], %g1
	ldd	[%i5+16], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+16]
	st	%g1, [%i0+92]
	add	%i3, 1, %i3
	b	.L418
	 add	%i2, 1, %i2
.L403:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	6, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+96], %g1
	ldd	[%i5+24], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+24]
	st	%g1, [%i0+96]
	add	%i3, 1, %i3
	b	.L419
	 add	%i2, 1, %i2
.L412:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	6, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+84], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	st	%g1, [%i0+84]
	add	%i3, 1, %i3
	b	.L420
	 add	%i2, 1, %i2
.L409:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i4], %o0
	std	%f10, [%fp-16]
	mov	6, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+88], %g1
	ldd	[%i5+8], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+8]
	st	%g1, [%i0+88]
	add	%i3, 1, %i3
	b	.L421
	 add	%i2, 1, %i2
	.size	NavExtractMsgEleven, .-NavExtractMsgEleven
	.section	.rodata.cst8
	.align 8
.LC19:
	.long	1073741824
	.long	0
	.align 8
.LC20:
	.long	1106247680
	.long	0
	.align 8
.LC21:
	.long	1105199104
	.long	0
	.align 8
.LC22:
	.long	1076887552
	.long	0
	.section	.text.NavExtractMsgTwentySix,"ax",@progbits
	.align 4
	.global NavExtractMsgTwentySix
	.type	NavExtractMsgTwentySix, #function
	.proc	020
NavExtractMsgTwentySix:
	save	%sp, -120, %sp
	sethi	%hi(temp_UTCCorr), %i5
	or	%i5, %lo(temp_UTCCorr), %i5
	st	%g0, [%i5+112]
	st	%g0, [%i5+96]
	ld	[%i0+96], %g1
	st	%g0, [%i5+100]
	st	%g0, [%i5+104]
	st	%g0, [%i5+108]
	st	%g0, [%i5+92]
	sethi	%hi(.LC19), %i3
	sra	%g1, 31, %g2
	wr	%g2, 0, %y
	nop
	nop
	nop
	sdiv	%g1, 5, %g1
	sethi	%hi(.LC21), %l0
	st	%g0, [%i5+8]
	st	%g0, [%i5+12]
	st	%g0, [%i5+16]
	st	%g0, [%i5+20]
	st	%g0, [%i5+24]
	st	%g0, [%i5+28]
	st	%g0, [%i5+32]
	st	%g0, [%i5+36]
	st	%g0, [%i5+40]
	st	%g0, [%i5+44]
	st	%g0, [%i5+48]
	st	%g0, [%i5+52]
	st	%g0, [%i5+56]
	st	%g0, [%i5+60]
	st	%g0, [%i5+64]
	st	%g0, [%i5+68]
	st	%g0, [%i5+72]
	st	%g0, [%i5+76]
	st	%g0, [%i5+80]
	st	%g0, [%i5+84]
	st	%g0, [%i5+88]
	st	%g1, [%i0+96]
	mov	1, %i1
	mov	0, %i4
	or	%i3, %lo(.LC19), %i2
	or	%l0, %lo(.LC21), %l0
	sethi	%hi(-2147483648), %l1
	sethi	%hi(.LC20), %l2
.L447:
	andcc	%i4, 0xff, %g0
	be	.L479
	 and	%i4, 0xff, %o2
	ld	[%i0+92], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i5+112], %f10
	fmuld	%f8, %f0, %f0
	ld	[%i5+112], %g1
	cmp	%g1, 0
	bl	.L480
	 fitod	%f10, %f8
	faddd	%f0, %f8, %f8
	ldd	[%l0], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L496
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
.L495:
	st	%f8, [%i5+112]
.L455:
	ld	[%i0+92], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	and	%i1, 0xff, %g2
	cmp	%g2, 3
	bne	.L452
	 st	%g1, [%i0+92]
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+92], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+92], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+92], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+92], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	4, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+92], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	5, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+92]
	ldd	[%i5+104], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+92], %g1
	ld	[%i0+88], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	ldd	[%i3+%lo(.LC19)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%g1, [%i0+92]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+88], %g1
	and	%g1, 1, %g3
	srl	%g1, 31, %g2
	st	%g3, [%fp-20]
	add	%g2, %g1, %g1
	ld	[%fp-20], %f10
	sra	%g1, 1, %g1
	fitod	%f10, %f10
	ldd	[%i3+%lo(.LC19)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%g1, [%i0+92]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+88], %g1
	and	%g1, 1, %g3
	srl	%g1, 31, %g2
	st	%g3, [%fp-20]
	add	%g2, %g1, %g1
	ld	[%fp-20], %f10
	sra	%g1, 1, %g1
	fitod	%f10, %f10
	ldd	[%i3+%lo(.LC19)], %o0
	mov	8, %o2
	mov	0, %o3
	st	%g1, [%i0+92]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+88], %g1
	srl	%g1, 31, %g2
	and	%g1, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f10
	fitod	%f10, %f10
	st	%g1, [%i0+92]
	std	%f10, [%fp-16]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	9, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%i5+104], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+104]
	ld	[%i0+88], %g1
	mov	0, %i4
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L459
	 st	%g1, [%i0+92]
.L456:
	add	%i4, -4, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu,a	.L481
	 ld	[%i0+84], %g1
	ld	[%i0+80], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	ldd	[%i2], %o0
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+96], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f0
	std	%f0, [%i5+96]
	ld	[%i0+80], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+80]
.L457:
	add	%i4, 1, %i4
	cmp	%i4, 16
	be,a	.L497
	 ld	[%i0+80], %g1
.L459:
	and	%i4, 0xff, %g1
	mov	%i4, %o2
	cmp	%g1, 3
	bgu	.L456
	 mov	0, %o3
	ld	[%i0+88], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i2], %o0
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+96], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f0
	std	%f0, [%i5+96]
	ld	[%i0+88], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	add	%i4, 1, %i4
	cmp	%i4, 16
	bne	.L459
	 st	%g1, [%i0+88]
	ld	[%i0+80], %g1
.L497:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	sethi	%hi(.LC22), %i1
	ld	[%fp-20], %f16
	ldd	[%i1+%lo(.LC22)], %f8
	fitod	%f16, %f10
	fmuld	%f0, %f8, %f0
	std	%f0, [%i5+96]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+88], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+80], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+88]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+80]
	ldd	[%i5+88], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+80], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+88]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+80]
	ldd	[%i5+88], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+80], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+88]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+80]
	ldd	[%i5+88], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+88]
	ld	[%i0+80], %g1
	ld	[%i0+76], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i3+%lo(.LC19)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%g1, [%i0+80]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%fp-16], %f10
	ldd	[%i5+88], %f8
	fmuld	%f10, %f0, %f0
	ld	[%i0+76], %g1
	faddd	%f0, %f8, %f8
	srl	%g1, 31, %i4
	std	%f8, [%i5+88]
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC19)], %o0
	sra	%g1, 1, %i4
	mov	5, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+88], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f10
	ld	[%i0+76], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f10
	add	%i4, %g1, %g1
	std	%f10, [%i5+88]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%i4, [%i0+76]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%fp-16], %f10
	ld	[%i0+76], %g1
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+88]
	sra	%g1, 1, %g1
	ldd	[%i3+%lo(.LC19)], %o0
	mov	-68, %o2
	mov	0, %o3
	st	%g1, [%i0+76]
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ld	[%i0+76], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ldd	[%fp-8], %f8
	ld	[%fp-20], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	std	%f0, [%i5+88]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+80], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+76], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+76], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+76], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+76], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	4, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+76]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	ld	[%i0+76], %g1
	ld	[%i0+72], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	ldd	[%i3+%lo(.LC19)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%g1, [%i0+76]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+80], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+72], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	6, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	7, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	8, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	9, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	10, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+72], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	11, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+72]
	ldd	[%i5+80], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f10
	ld	[%i0+72], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f10
	add	%i4, %g1, %g1
	std	%f10, [%i5+80]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	12, %o2
	mov	0, %o3
	st	%i4, [%i0+72]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ld	[%i0+72], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+80]
	sra	%g1, 1, %g1
	std	%f8, [%fp-8]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	-51, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%g1, [%i0+72]
	ldd	[%fp-8], %f8
	mov	0, %i4
	fmuld	%f8, %f0, %f0
	b	.L463
	 std	%f0, [%i5+80]
.L460:
	cmp	%g1, 15
	bne	.L483
	 ld	[%i0+64], %g1
	ldd	[%i5+72], %f10
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 ldd	[%i2], %o0
	ldd	[%fp-8], %f8
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	fsubd	%f10, %f0, %f8
.L478:
	std	%f8, [%i5+72]
	ld	[%i0+64], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	add	%i4, 1, %i4
	cmp	%i4, 16
	be	.L484
	 st	%g1, [%i0+64]
.L463:
	and	%i4, 0xff, %g1
	mov	15, %o2
	cmp	%g1, 7
	bgu	.L460
	 mov	0, %o3
	ld	[%i0+68], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	mov	%i4, %o2
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 ldd	[%i2], %o0
	ldd	[%fp-8], %f8
	ldd	[%i5+72], %f10
	fmuld	%f8, %f0, %f0
	faddd	%f0, %f10, %f8
	std	%f8, [%i5+72]
	ld	[%i0+68], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	add	%i4, 1, %i4
	cmp	%i4, 16
	bne	.L463
	 st	%g1, [%i0+68]
.L484:
	ldd	[%i3+%lo(.LC19)], %o0
	mov	-35, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ld	[%i0+60], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ldd	[%fp-8], %f8
	ld	[%fp-20], %f16
	fmuld	%f0, %f8, %f0
	fitod	%f16, %f10
	std	%f0, [%i5+72]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+64], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+60], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	4, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	5, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+60], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	6, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+60]
	ldd	[%i5+64], %f10
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ld	[%i0+60], %g1
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f10, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+64]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%i4, [%i0+60]
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ldd	[%fp-8], %f8
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	fsubd	%f8, %f0, %f8
	std	%f8, [%i5+64]
	ld	[%i0+60], %g1
	ld	[%i0+56], %g3
	srl	%g1, 31, %g2
	and	%g3, 1, %g3
	add	%g2, %g1, %g1
	st	%g3, [%fp-20]
	sra	%g1, 1, %g1
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	st	%g1, [%i0+60]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+56], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+56], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+56]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+56]
	ldd	[%i5+56], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+56], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+56]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+56]
	ldd	[%i5+56], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+56], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+56]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	3, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+56]
	ldd	[%i5+56], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+56], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %l0
	fitod	%f16, %f10
	add	%l0, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+56]
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%l0, [%i0+56]
	ld	[%i0+56], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	1, %o2
	mov	0, %o3
	st	%i4, [%i0+56]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ld	[%i0+56], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%l0, [%i0+56]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ld	[%i0+56], %g1
	ldd	[%i5+48], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	3, %o2
	mov	0, %o3
	st	%i4, [%i0+56]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+48]
	ldd	[%i5+48], %f8
	ld	[%i0+52], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f12
	st	%i4, [%fp-20]
	ld	[%i0+56], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %g3
	fitod	%f12, %f10
	add	%g3, %g1, %g1
	fitod	%f14, %f12
	sra	%g1, 1, %g1
	fmuld	%f12, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%g1, [%i0+56]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ldd	[%i5+48], %f8
	ldd	[%fp-16], %f10
	ld	[%i0+52], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	5, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	6, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %i4
	fitod	%f12, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	7, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f14
	srl	%g1, 31, %i4
	fitod	%f14, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	8, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f16
	srl	%g1, 31, %i4
	fitod	%f16, %f10
	add	%i4, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	9, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i4, [%i0+52]
	ldd	[%i5+48], %f8
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%i0+52], %g1
	ld	[%fp-20], %f12
	srl	%g1, 31, %l0
	fitod	%f12, %f10
	add	%l0, %g1, %g1
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	std	%f8, [%i5+48]
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%l0, [%i0+52]
	ld	[%i0+52], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	1, %o2
	mov	0, %o3
	st	%i4, [%i0+52]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ldd	[%i5+40], %f8
	ld	[%i0+48], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ld	[%fp-20], %f14
	ld	[%i0+52], %g1
	fitod	%f14, %f12
	srl	%g1, 31, %g3
	fmuld	%f12, %f0, %f0
	add	%g3, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+40]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%g1, [%i0+52]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+48], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+40], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC19)], %o0
	sra	%g1, 1, %i4
	mov	3, %o2
	mov	0, %o3
	std	%f8, [%i5+40]
	call	xx__pow_opt, 0
	 st	%i4, [%i0+48]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%l0, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%i4, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%l0, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%i4, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	8, %o2
	mov	0, %o3
	st	%l0, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ld	[%i0+48], %g1
	ldd	[%i5+40], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	9, %o2
	mov	0, %o3
	st	%i4, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+40]
	ldd	[%i5+40], %f8
	ld	[%i0+44], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ld	[%fp-20], %f14
	ld	[%i0+48], %g1
	fitod	%f14, %f12
	srl	%g1, 31, %g3
	fmuld	%f12, %f0, %f0
	add	%g3, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+40]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	st	%g1, [%i0+48]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+44], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+32], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC19)], %o0
	sra	%g1, 1, %i4
	mov	1, %o2
	mov	0, %o3
	std	%f8, [%i5+32]
	call	xx__pow_opt, 0
	 st	%i4, [%i0+44]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%l0, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	3, %o2
	mov	0, %o3
	st	%i4, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%l0, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%i4, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%l0, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+44], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%i4, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ldd	[%i5+32], %f8
	ld	[%i0+40], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ld	[%fp-20], %f14
	ld	[%i0+44], %g1
	fitod	%f14, %f12
	srl	%g1, 31, %g3
	fmuld	%f12, %f0, %f0
	add	%g3, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+32]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	8, %o2
	mov	0, %o3
	st	%g1, [%i0+44]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+40], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+32], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC19)], %o0
	sra	%g1, 1, %i4
	mov	9, %o2
	mov	0, %o3
	std	%f8, [%i5+32]
	call	xx__pow_opt, 0
	 st	%i4, [%i0+40]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	10, %o2
	mov	0, %o3
	st	%l0, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	11, %o2
	mov	0, %o3
	st	%i4, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	12, %o2
	mov	0, %o3
	st	%l0, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	13, %o2
	mov	0, %o3
	st	%i4, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %l0
	and	%i4, 1, %i4
	add	%l0, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %l0
	ldd	[%i3+%lo(.LC19)], %o0
	mov	14, %o2
	mov	0, %o3
	st	%l0, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	ldd	[%i5+32], %f8
	srl	%g1, 31, %i4
	and	%l0, 1, %l0
	add	%i4, %g1, %g1
	st	%l0, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	15, %o2
	mov	0, %o3
	st	%i4, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+32]
	ld	[%i0+40], %g1
	srl	%g1, 31, %g2
	ldd	[%i5+32], %f8
	add	%g2, %g1, %g1
	ld	[%i0+36], %g2
	and	%g2, 1, %g2
	st	%g2, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ldd	[%i1+%lo(.LC22)], %f12
	ld	[%fp-20], %f16
	sra	%g1, 1, %g1
	fitod	%f16, %f14
	fmuld	%f14, %f0, %f0
	faddd	%f0, %f8, %f8
	fmuld	%f8, %f12, %f12
	std	%f12, [%i5+32]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	st	%g1, [%i0+40]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+36], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+24], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f8
	add	%i4, %g1, %g1
	ldd	[%i3+%lo(.LC19)], %o0
	sra	%g1, 1, %i4
	mov	1, %o2
	mov	0, %o3
	std	%f8, [%i5+24]
	call	xx__pow_opt, 0
	 st	%i4, [%i0+36]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%i1, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+24]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i4
	and	%i1, 1, %i1
	add	%i4, %g1, %g1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	3, %o2
	mov	0, %o3
	st	%i4, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+24]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	ldd	[%i3+%lo(.LC19)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%i1, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+24]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i4
	and	%i1, 1, %i1
	add	%i4, %g1, %g1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%i4, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+24]
	ld	[%i0+36], %g1
	ldd	[%i5+24], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	std	%f8, [%i5+24]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	6, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 st	%i1, [%i0+36]
	ldd	[%i5+24], %f10
	and	%i1, 1, %i1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ld	[%i0+36], %g1
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f10, %f8
	add	%i4, %g1, %g1
	std	%f8, [%i5+24]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	7, %o2
	mov	0, %o3
	st	%i4, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ld	[%i0+32], %g3
	and	%g3, 1, %g3
	st	%g3, [%fp-20]
	and	%i4, 1, %i4
	ld	[%fp-20], %f16
	st	%i4, [%fp-20]
	fitod	%f16, %f10
	ld	[%fp-20], %f14
	ld	[%i0+36], %g1
	fitod	%f14, %f12
	srl	%g1, 31, %g2
	fmuld	%f12, %f0, %f0
	add	%g2, %g1, %g1
	ldd	[%fp-8], %f8
	sra	%g1, 1, %g1
	fsubd	%f8, %f0, %f8
	std	%f8, [%i5+24]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	0, %o2
	mov	0, %o3
	st	%g1, [%i0+36]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	ld	[%i0+32], %g1
	ldd	[%fp-16], %f10
	ldd	[%i5+16], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i1
	faddd	%f0, %f8, %f8
	add	%i1, %g1, %g1
	ldd	[%i3+%lo(.LC19)], %o0
	sra	%g1, 1, %i1
	mov	1, %o2
	mov	0, %o3
	std	%f8, [%i5+16]
	call	xx__pow_opt, 0
	 st	%i1, [%i0+32]
	ld	[%i0+32], %g1
	ldd	[%i5+16], %f8
	srl	%g1, 31, %i4
	and	%i1, 1, %i1
	add	%i4, %g1, %g1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	2, %o2
	mov	0, %o3
	st	%i4, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+16]
	ld	[%i0+32], %g1
	ldd	[%i5+16], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	ldd	[%i3+%lo(.LC19)], %o0
	mov	3, %o2
	mov	0, %o3
	st	%i1, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+16]
	ld	[%i0+32], %g1
	ldd	[%i5+16], %f8
	srl	%g1, 31, %i4
	and	%i1, 1, %i1
	add	%i4, %g1, %g1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	4, %o2
	mov	0, %o3
	st	%i4, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+16]
	ld	[%i0+32], %g1
	ldd	[%i5+16], %f8
	srl	%g1, 31, %i1
	and	%i4, 1, %i4
	add	%i1, %g1, %g1
	st	%i4, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %i1
	ldd	[%i3+%lo(.LC19)], %o0
	mov	5, %o2
	mov	0, %o3
	st	%i1, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f8, [%i5+16]
	ldd	[%i5+16], %f8
	and	%i1, 1, %i1
	st	%i1, [%fp-20]
	ld	[%fp-20], %f10
	fitod	%f10, %f10
	ld	[%i0+32], %g1
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %i4
	faddd	%f0, %f8, %f10
	add	%i4, %g1, %g1
	std	%f10, [%i5+16]
	sra	%g1, 1, %i4
	ldd	[%i3+%lo(.LC19)], %o0
	mov	6, %o2
	mov	0, %o3
	st	%i4, [%i0+32]
	call	xx__pow_opt, 0
	 std	%f10, [%fp-16]
	and	%i4, 1, %i4
	st	%i4, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ld	[%i0+32], %g1
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f8, %f0, %f0
	add	%g2, %g1, %g1
	fsubd	%f10, %f0, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+16]
	st	%g1, [%i0+32]
	std	%f8, [%fp-8]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	-68, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	fmuld	%f8, %f0, %f0
	std	%f0, [%i5+16]
	mov	0, %i4
	andcc	%i4, 0xff, %g1
	be	.L485
	 mov	1, %i1
	add	%i4, -1, %g2
.L498:
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L486
	 cmp	%g1, 12
	bne	.L487
	 ld	[%i0+24], %g1
	ldd	[%i5+8], %f10
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	std	%f10, [%fp-16]
	std	%f8, [%fp-8]
	ldd	[%i2], %o0
	mov	12, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+24], %g1
	ldd	[%fp-16], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f10, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	st	%g1, [%i0+24]
.L468:
	and	%i1, 0xff, %g1
	cmp	%g1, 13
	be	.L488
	 add	%i1, 1, %i1
	add	%i4, 1, %i4
.L489:
	andcc	%i4, 0xff, %g1
	bne	.L498
	 add	%i4, -1, %g2
.L485:
	ld	[%i0+32], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f10
	ldd	[%i2], %o0
	std	%f10, [%fp-16]
	mov	0, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+32], %g1
	ldd	[%i5+8], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5+8]
	st	%g1, [%i0+32]
	add	%i4, 1, %i4
	b	.L489
	 add	%i1, 1, %i1
.L479:
	ld	[%i0+96], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	mov	0, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i5+112], %f10
	fmuld	%f8, %f0, %f0
	ld	[%i5+112], %g1
	cmp	%g1, 0
	bl	.L490
	 fitod	%f10, %f8
.L449:
	faddd	%f0, %f8, %f8
	ldd	[%l0], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L450
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i5+112]
.L451:
	ld	[%i0+96], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+96]
.L452:
	add	%i4, 1, %i4
	b	.L447
	 add	%i1, 1, %i1
.L450:
	fdtoi	%f8, %f8
	st	%f8, [%fp-20]
	ld	[%fp-20], %g2
	xor	%g2, %l1, %g1
	b	.L451
	 st	%g1, [%i5+112]
.L454:
.L496:
	fdtoi	%f8, %f8
	st	%f8, [%fp-20]
	ld	[%fp-20], %g2
	xor	%g2, %l1, %g1
	b	.L455
	 st	%g1, [%i5+112]
.L481:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	ldd	[%i2], %o0
	std	%f10, [%fp-16]
	mov	%i4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%i5+96], %f8
	ldd	[%fp-16], %f10
	fmuld	%f10, %f0, %f0
	faddd	%f0, %f8, %f0
	std	%f0, [%i5+96]
	ld	[%i0+84], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L457
	 st	%g1, [%i0+84]
.L483:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	mov	%i4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ldd	[%i5+72], %f10
	fmuld	%f8, %f0, %f0
	b	.L478
	 faddd	%f0, %f10, %f8
.L488:
	std	%f8, [%fp-8]
	ldd	[%i3+%lo(.LC19)], %o0
	mov	-51, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	mov	0, %i4
	fmuld	%f0, %f8, %f0
	b	.L474
	 std	%f0, [%i5+8]
.L470:
	and	%g2, 0xff, %g2
	cmp	%g2, 7
	bleu	.L491
	 cmp	%g1, 15
	bne	.L492
	 mov	15, %o2
	ldd	[%i5], %f8
	ld	[%i0+16], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	std	%f8, [%fp-8]
	std	%f10, [%fp-16]
	ldd	[%i2], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+16], %g1
	ldd	[%fp-16], %f10
	ldd	[%fp-8], %f8
	fmuld	%f10, %f0, %f0
	srl	%g1, 31, %g2
	fsubd	%f8, %f0, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5]
	sra	%g1, 1, %g1
	st	%g1, [%i0+16]
.L471:
	add	%i4, 1, %i4
	cmp	%i4, 16
	be	.L499
	 nop
.L474:
	and	%i4, 0xff, %g1
	cmp	%g1, 3
	bgu	.L470
	 add	%i4, -4, %g2
	ld	[%i0+24], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f12
	fitod	%f12, %f10
	mov	%i4, %o2
	std	%f10, [%fp-16]
	ldd	[%i2], %o0
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+24], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	add	%i4, 1, %i4
	cmp	%i4, 16
	bne	.L474
	 st	%g1, [%i0+24]
.L499:
	jmp	%i7+8
	 restore
.L491:
	ld	[%i0+20], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f14
	fitod	%f14, %f10
	ldd	[%i2], %o0
	std	%f10, [%fp-16]
	mov	%i4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+20], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	b	.L471
	 st	%g1, [%i0+20]
.L486:
	ld	[%i0+28], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	and	%i4, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+28], %g1
	ldd	[%i5+8], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	b	.L468
	 st	%g1, [%i0+28]
.L492:
	ld	[%i0+16], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f16
	fitod	%f16, %f10
	ldd	[%i2], %o0
	std	%f10, [%fp-16]
	mov	%i4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i0+16], %g1
	ldd	[%i5], %f8
	ldd	[%fp-16], %f10
	srl	%g1, 31, %g2
	fmuld	%f10, %f0, %f0
	add	%g2, %g1, %g1
	faddd	%f0, %f8, %f8
	sra	%g1, 1, %g1
	std	%f8, [%i5]
	b	.L471
	 st	%g1, [%i0+16]
.L487:
	and	%g1, 1, %g1
	st	%g1, [%fp-20]
	ld	[%fp-20], %f8
	fitod	%f8, %f8
	ldd	[%i2], %o0
	std	%f8, [%fp-8]
	and	%i4, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i0+24], %g1
	ldd	[%i5+8], %f10
	fmuld	%f8, %f0, %f0
	srl	%g1, 31, %g2
	faddd	%f0, %f10, %f8
	add	%g2, %g1, %g1
	std	%f8, [%i5+8]
	sra	%g1, 1, %g1
	b	.L468
	 st	%g1, [%i0+24]
.L480:
	ldd	[%l2+%lo(.LC20)], %f10
	faddd	%f8, %f10, %f8
	ldd	[%l0], %f10
	faddd	%f0, %f8, %f8
	fcmped	%f8, %f10
	nop
	fbge,a	.L454
	 fsubd	%f8, %f10, %f8
	b	.L495
	 fdtoi	%f8, %f8
.L490:
	ldd	[%l2+%lo(.LC20)], %f10
	b	.L449
	 faddd	%f8, %f10, %f8
	.size	NavExtractMsgTwentySix, .-NavExtractMsgTwentySix
	.section	.rodata.cst8
	.align 8
.LC23:
	.long	1073741824
	.long	0
	.align 8
.LC24:
	.long	1106247680
	.long	0
	.align 8
.LC25:
	.long	1105199104
	.long	0
	.section	.text.NavExtractDataFrameThreeFour,"ax",@progbits
	.align 4
	.global NavExtractDataFrameThreeFour
	.type	NavExtractDataFrameThreeFour, #function
	.proc	020
NavExtractDataFrameThreeFour:
	save	%sp, -112, %sp
	ld	[%i0+128], %g1
	sra	%g1, 31, %i5
	and	%i5, 3, %i5
	add	%i5, %g1, %g1
	sethi	%hi(temp_frame3_4), %i3
	sra	%g1, 2, %i5
	or	%i3, %lo(temp_frame3_4), %i4
	st	%i5, [%i0+128]
	st	%g0, [%i3+%lo(temp_frame3_4)]
	st	%g0, [%i4+4]
	st	%g0, [%i4+16]
	st	%g0, [%i4+8]
	st	%g0, [%i4+12]
	sethi	%hi(.LC23), %i2
	mov	0, %o2
	ldd	[%i2+%lo(.LC23)], %o0
	mov	0, %o3
	call	xx__pow_opt, 0
	 and	%i5, 1, %i5
	st	%i5, [%fp-12]
	ld	[%i3+%lo(temp_frame3_4)], %f12
	ld	[%fp-12], %f8
	ld	[%i3+%lo(temp_frame3_4)], %g2
	fitod	%f8, %f8
	mov	%i3, %g1
	fitod	%f12, %f10
	cmp	%g2, 0
	bl	.L556
	 fmuld	%f8, %f0, %f0
.L501:
	faddd	%f0, %f10, %f8
	sethi	%hi(.LC25), %i5
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L502
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+%lo(temp_frame3_4)]
.L503:
	ld	[%i0+128], %g1
	srl	%g1, 31, %l0
	add	%l0, %g1, %g1
	ldd	[%i2+%lo(.LC23)], %o0
	sra	%g1, 1, %l0
	mov	1, %o2
	st	%l0, [%i0+128]
	mov	0, %o3
	call	xx__pow_opt, 0
	 and	%l0, 1, %l0
	st	%l0, [%fp-12]
	ld	[%i3+%lo(temp_frame3_4)], %f12
	ld	[%fp-12], %f8
	ld	[%i3+%lo(temp_frame3_4)], %g2
	fitod	%f8, %f8
	sethi	%hi(temp_frame3_4), %g1
	fitod	%f12, %f10
	cmp	%g2, 0
	bl	.L557
	 fmuld	%f8, %f0, %f0
.L504:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L505
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+%lo(temp_frame3_4)]
.L506:
	ld	[%i0+128], %g1
	srl	%g1, 31, %l0
	add	%l0, %g1, %g1
	ldd	[%i2+%lo(.LC23)], %o0
	sra	%g1, 1, %l0
	mov	2, %o2
	st	%l0, [%i0+128]
	mov	0, %o3
	call	xx__pow_opt, 0
	 and	%l0, 1, %l0
	st	%l0, [%fp-12]
	ld	[%i3+%lo(temp_frame3_4)], %f12
	ld	[%fp-12], %f8
	ld	[%i3+%lo(temp_frame3_4)], %g2
	fitod	%f8, %f8
	sethi	%hi(temp_frame3_4), %g1
	fitod	%f12, %f10
	cmp	%g2, 0
	bl	.L558
	 fmuld	%f8, %f0, %f0
.L507:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L508
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+%lo(temp_frame3_4)]
.L509:
	ld	[%i0+128], %g1
	srl	%g1, 31, %l0
	add	%l0, %g1, %g1
	ldd	[%i2+%lo(.LC23)], %o0
	sra	%g1, 1, %l0
	mov	3, %o2
	st	%l0, [%i0+128]
	mov	0, %o3
	call	xx__pow_opt, 0
	 and	%l0, 1, %l0
	st	%l0, [%fp-12]
	ld	[%i3+%lo(temp_frame3_4)], %f12
	ld	[%fp-12], %f8
	ld	[%i3+%lo(temp_frame3_4)], %g2
	fitod	%f8, %f8
	sethi	%hi(temp_frame3_4), %g1
	fitod	%f12, %f10
	cmp	%g2, 0
	bl	.L559
	 fmuld	%f8, %f0, %f0
.L510:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L511
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+%lo(temp_frame3_4)]
.L512:
	ld	[%i0+128], %g1
	srl	%g1, 31, %l0
	add	%l0, %g1, %g1
	ldd	[%i2+%lo(.LC23)], %o0
	sra	%g1, 1, %l0
	mov	4, %o2
	st	%l0, [%i0+128]
	mov	0, %o3
	call	xx__pow_opt, 0
	 and	%l0, 1, %l0
	st	%l0, [%fp-12]
	ld	[%i3+%lo(temp_frame3_4)], %f12
	ld	[%fp-12], %f8
	ld	[%i3+%lo(temp_frame3_4)], %g2
	fitod	%f8, %f8
	sethi	%hi(temp_frame3_4), %g1
	fitod	%f12, %f10
	cmp	%g2, 0
	bl	.L560
	 fmuld	%f8, %f0, %f0
.L513:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L514
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+%lo(temp_frame3_4)]
.L515:
	ld	[%i0+128], %g1
	srl	%g1, 31, %l0
	add	%l0, %g1, %g1
	ldd	[%i2+%lo(.LC23)], %o0
	sra	%g1, 1, %l0
	mov	5, %o2
	st	%l0, [%i0+128]
	mov	0, %o3
	call	xx__pow_opt, 0
	 and	%l0, 1, %l0
	st	%l0, [%fp-12]
	ld	[%i3+%lo(temp_frame3_4)], %g1
	ld	[%fp-12], %f8
	st	%g1, [%fp-12]
	fitod	%f8, %f8
	ld	[%fp-12], %f12
	sethi	%hi(temp_frame3_4), %g2
	fitod	%f12, %f10
	cmp	%g1, 0
	bl	.L561
	 fmuld	%f8, %f0, %f0
.L516:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L517
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g2+%lo(temp_frame3_4)]
.L518:
	ld	[%i0+128], %g2
	ld	[%i0+16], %g1
	srl	%g2, 31, %g3
	sra	%g1, 31, %i3
	add	%g3, %g2, %g2
	and	%i3, 15, %i3
	sra	%g2, 1, %g2
	add	%i3, %g1, %g1
	st	%g2, [%i0+128]
	sra	%g1, 4, %i3
	ldd	[%i2+%lo(.LC23)], %o0
	mov	0, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 mov	%i3, %l0
	and	%i3, 1, %i3
	st	%i3, [%fp-12]
	mov	%i4, %g1
	ld	[%fp-12], %f8
	ld	[%i4+4], %f12
	fitod	%f8, %f8
	ld	[%i4+4], %g2
	fitod	%f12, %f10
	cmp	%g2, 0
	bl	.L562
	 fmuld	%f8, %f0, %f0
.L519:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L520
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+4]
.L521:
	and	%l0, 0xff, %l0
	ldd	[%i2+%lo(.LC23)], %o0
	srl	%l0, 1, %l0
	mov	1, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 mov	%l0, %i3
	and	%l0, 1, %l0
	st	%l0, [%fp-12]
	mov	%i4, %g1
	ld	[%fp-12], %f8
	ld	[%i4+4], %f12
	fitod	%f8, %f8
	ld	[%i4+4], %g2
	fitod	%f12, %f10
	cmp	%g2, 0
	bl	.L563
	 fmuld	%f8, %f0, %f0
.L522:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L523
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+4]
.L524:
	and	%i3, 0xff, %i3
	ldd	[%i2+%lo(.LC23)], %o0
	srl	%i3, 1, %i3
	mov	2, %o2
	mov	0, %o3
	call	xx__pow_opt, 0
	 mov	%i3, %l0
	and	%i3, 1, %i3
	st	%i3, [%fp-12]
	mov	%i4, %g1
	ld	[%fp-12], %f8
	ld	[%i4+4], %f12
	fitod	%f8, %f8
	ld	[%i4+4], %g2
	fitod	%f12, %f10
	cmp	%g2, 0
	bl	.L564
	 fmuld	%f8, %f0, %f0
.L525:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L526
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+4]
.L527:
	ldd	[%i2+%lo(.LC23)], %o0
	mov	3, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ld	[%i4+4], %f8
	srl	%l0, 1, %l0
	and	%l0, 1, %l0
	st	%l0, [%fp-12]
	fitod	%f8, %f10
	ld	[%fp-12], %f12
	ld	[%i4+4], %g2
	fitod	%f12, %f8
	mov	%i4, %g1
	cmp	%g2, 0
	bl	.L565
	 fmuld	%f8, %f0, %f0
.L528:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L529
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+4]
.L530:
	ld	[%i0+12], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-12]
	ld	[%fp-12], %f8
	fitod	%f8, %f8
	ldd	[%i2+%lo(.LC23)], %o0
	std	%f8, [%fp-8]
	mov	4, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i4+4], %f10
	fmuld	%f8, %f0, %f0
	ld	[%i4+4], %g2
	mov	%i4, %g1
	cmp	%g2, 0
	bl	.L566
	 fitod	%f10, %f8
.L531:
	faddd	%f0, %f8, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L532
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+4]
.L533:
	ld	[%i0+12], %g1
	srl	%g1, 31, %i3
	add	%i3, %g1, %g1
	ldd	[%i2+%lo(.LC23)], %o0
	sra	%g1, 1, %i3
	mov	5, %o2
	st	%i3, [%i0+12]
	mov	0, %o3
	call	xx__pow_opt, 0
	 and	%i3, 1, %i3
	st	%i3, [%fp-12]
	mov	%i4, %g1
	ld	[%fp-12], %f8
	ld	[%i4+4], %f12
	fitod	%f8, %f8
	ld	[%i4+4], %g2
	fitod	%f12, %f10
	cmp	%g2, 0
	bl	.L567
	 fmuld	%f8, %f0, %f0
.L534:
	faddd	%f0, %f10, %f8
	ldd	[%i5+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbge,a	.L535
	 fsubd	%f8, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%g1+4]
.L536:
	ld	[%i0+12], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+12]
	mov	0, %g3
	ld	[%i4+8], %i5
	and	%g3, 0xff, %g2
	cmp	%g2, 2
	bgu	.L538
	 mov	1, %g4
	srl	%g1, 31, %g2
.L578:
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+12]
	and	%g4, 0xff, %g2
.L579:
	cmp	%g2, 6
	be	.L568
	 add	%g3, 1, %g3
	add	%g4, 1, %g4
.L571:
	and	%g3, 0xff, %g2
	cmp	%g2, 2
	bleu,a	.L578
	 srl	%g1, 31, %g2
.L538:
	cmp	%g2, 3
	be	.L570
	 cmp	%g2, 4
	bne	.L579
	 and	%g4, 0xff, %g2
	srl	%g1, 31, %g2
	and	%g1, 1, %i5
	add	%g3, 1, %g3
	add	%g2, %g1, %g1
	add	%g4, 1, %g4
	sra	%g1, 1, %g1
	b	.L571
	 st	%g1, [%i0+12]
.L568:
	st	%i5, [%i4+8]
	sethi	%hi(.LC23), %l0
	mov	0, %i5
	mov	1, %i3
	or	%l0, %lo(.LC23), %l0
	and	%i5, 0xff, %o2
	andcc	%i5, 0xff, %g0
	be	.L572
	 mov	0, %o3
.L544:
	add	%i5, -1, %g1
	and	%g1, 0xff, %g1
	cmp	%g1, 7
	bleu,a	.L573
	 ld	[%i0+8], %g1
	ld	[%i0+4], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-12]
	ld	[%fp-12], %f10
	fitod	%f10, %f8
	ldd	[%l0], %o0
	call	xx__pow_opt, 0
	 std	%f8, [%fp-8]
	ldd	[%fp-8], %f8
	ld	[%i4+16], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i4+16]
	ld	[%i0+4], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	st	%g1, [%i0+4]
.L547:
	and	%i3, 0xff, %g1
	cmp	%g1, 17
	be	.L574
	 add	%i5, 1, %i5
	add	%i3, 1, %i3
.L575:
	and	%i5, 0xff, %o2
	andcc	%i5, 0xff, %g0
	bne	.L544
	 mov	0, %o3
.L572:
	ld	[%i0+12], %g1
	and	%g1, 1, %g1
	st	%g1, [%fp-12]
	ld	[%fp-12], %f10
	fitod	%f10, %f8
	ldd	[%l0], %o0
	std	%f8, [%fp-8]
	call	xx__pow_opt, 0
	 mov	0, %o2
	ldd	[%fp-8], %f8
	ld	[%i4+16], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i4+16]
	add	%i5, 1, %i5
	ld	[%i0+12], %g1
	add	%i3, 1, %i3
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L575
	 st	%g1, [%i0+12]
.L574:
	ld	[%i4+8], %g3
	cmp	%g3, 1
	be	.L581
	 sll	%i1, 2, %g1
	sethi	%hi(temp_frame3_4), %i5
	ld	[%i4+4], %g2
	ld	[%i5+%lo(temp_frame3_4)], %o5
	sethi	%hi(NavSubFrame3_4Data), %g4
	sll	%i1, 5, %i1
	or	%g4, %lo(NavSubFrame3_4Data), %g4
	sub	%i1, %g1, %i1
	ld	[%i4+16], %o7
	add	%g4, %i1, %g1
	ld	[%i4+12], %i3
	ld	[%i4+20], %i5
	st	%o5, [%g4+%i1]
	st	%g2, [%g1+4]
	st	%o7, [%g1+16]
	st	%g3, [%g1+8]
	st	%i3, [%g1+12]
	cmp	%g2, 11
	be	.L550
	 st	%i5, [%g1+20]
	cmp	%g2, 26
	be	.L551
	 cmp	%g2, 9
	be	.L576
	 nop
.L581:
	jmp	%i7+8
	 restore
.L573:
	and	%g1, 1, %g1
	st	%g1, [%fp-12]
	ld	[%fp-12], %f10
	fitod	%f10, %f8
	ldd	[%l0], %o0
	std	%f8, [%fp-8]
	and	%i5, 0xff, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	ld	[%i4+16], %f12
	fmuld	%f8, %f0, %f0
	fitod	%f12, %f10
	faddd	%f0, %f10, %f8
	fdtoi	%f8, %f8
	st	%f8, [%i4+16]
	ld	[%i0+8], %g1
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L547
	 st	%g1, [%i0+8]
.L570:
	and	%g1, 1, %g1
	st	%g1, [%i4+12]
	add	%g3, 1, %g3
	ld	[%i0+12], %g1
	add	%g4, 1, %g4
	srl	%g1, 31, %g2
	add	%g2, %g1, %g1
	sra	%g1, 1, %g1
	b	.L571
	 st	%g1, [%i0+12]
.L532:
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	sethi	%hi(-2147483648), %g3
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L533
	 st	%g2, [%g1+4]
.L529:
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	sethi	%hi(-2147483648), %g3
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L530
	 st	%g2, [%g1+4]
.L526:
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	sethi	%hi(-2147483648), %g3
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L527
	 st	%g2, [%g1+4]
.L523:
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	sethi	%hi(-2147483648), %g3
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L524
	 st	%g2, [%g1+4]
.L502:
	sethi	%hi(-2147483648), %g3
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L503
	 st	%g2, [%g1+%lo(temp_frame3_4)]
.L535:
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	sethi	%hi(-2147483648), %g3
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L536
	 st	%g2, [%g1+4]
.L508:
	sethi	%hi(-2147483648), %g3
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L509
	 st	%g2, [%g1+%lo(temp_frame3_4)]
.L505:
	sethi	%hi(-2147483648), %g3
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L506
	 st	%g2, [%g1+%lo(temp_frame3_4)]
.L520:
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	sethi	%hi(-2147483648), %g3
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L521
	 st	%g2, [%g1+4]
.L517:
	sethi	%hi(-2147483648), %g3
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g1
	b	.L518
	 st	%g1, [%g2+%lo(temp_frame3_4)]
.L514:
	sethi	%hi(-2147483648), %g3
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L515
	 st	%g2, [%g1+%lo(temp_frame3_4)]
.L511:
	sethi	%hi(-2147483648), %g3
	fdtoi	%f8, %f8
	st	%f8, [%fp-12]
	ld	[%fp-12], %g4
	xor	%g4, %g3, %g2
	b	.L512
	 st	%g2, [%g1+%lo(temp_frame3_4)]
.L551:
	call	NavExtractMsgTwentySix, 0
	 mov	%i0, %o0
	sethi	%hi(temp_UTCCorr), %i4
.L577:
	ldd	[%i4+%lo(temp_UTCCorr)], %f8
	ldd	[%i2+%lo(.LC23)], %o0
	std	%f8, [%fp-8]
	mov	-35, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	or	%i4, %lo(temp_UTCCorr), %i5
	fmuld	%f8, %f0, %f0
	sethi	%hi(NavUTCCorr), %g2
	ldd	[%i5+8], %f16
	or	%g2, %lo(NavUTCCorr), %g1
	ldd	[%i5+16], %f14
	ldd	[%i5+24], %f12
	ldd	[%i5+32], %f10
	ldd	[%i5+40], %f8
	ldd	[%i5+48], %f18
	ldd	[%i5+56], %f20
	ldd	[%i5+64], %f22
	ldd	[%i5+72], %f24
	ldd	[%i5+80], %f26
	ldd	[%i5+88], %f28
	ldd	[%i5+96], %f30
	ldd	[%i5+104], %f6
	ld	[%i5+112], %g3
	std	%f0, [%i4+%lo(temp_UTCCorr)]
	std	%f0, [%g2+%lo(NavUTCCorr)]
	std	%f16, [%g1+8]
	std	%f14, [%g1+16]
	std	%f12, [%g1+24]
	std	%f10, [%g1+32]
	std	%f8, [%g1+40]
	std	%f18, [%g1+48]
	std	%f20, [%g1+56]
	std	%f22, [%g1+64]
	std	%f24, [%g1+72]
	std	%f26, [%g1+80]
	std	%f28, [%g1+88]
	std	%f30, [%g1+96]
	std	%f6, [%g1+104]
	st	%g3, [%g1+112]
	jmp	%i7+8
	 restore
.L576:
	call	NavExtractMsgNine, 0
	 mov	%i0, %o0
	b	.L577
	 sethi	%hi(temp_UTCCorr), %i4
.L567:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L534
	 faddd	%f10, %f12, %f10
.L566:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f10
	b	.L531
	 faddd	%f8, %f10, %f8
.L565:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L528
	 faddd	%f10, %f12, %f10
.L564:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L525
	 faddd	%f10, %f12, %f10
.L563:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L522
	 faddd	%f10, %f12, %f10
.L562:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L519
	 faddd	%f10, %f12, %f10
.L561:
	sethi	%hi(.LC24), %g1
	ldd	[%g1+%lo(.LC24)], %f12
	b	.L516
	 faddd	%f10, %f12, %f10
.L560:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L513
	 faddd	%f10, %f12, %f10
.L559:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L510
	 faddd	%f10, %f12, %f10
.L558:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L507
	 faddd	%f10, %f12, %f10
.L557:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L504
	 faddd	%f10, %f12, %f10
.L556:
	sethi	%hi(.LC24), %g2
	ldd	[%g2+%lo(.LC24)], %f12
	b	.L501
	 faddd	%f10, %f12, %f10
.L550:
	call	NavExtractMsgEleven, 0
	 mov	%i0, %o0
	sethi	%hi(temp_Iono_Corr), %i4
	ldd	[%i4+%lo(temp_Iono_Corr)], %f8
	ldd	[%i2+%lo(.LC23)], %o0
	std	%f8, [%fp-8]
	mov	-30, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	or	%i4, %lo(temp_Iono_Corr), %i5
	fmuld	%f8, %f0, %f0
	sethi	%hi(NavIonoCorrction), %g2
	ldd	[%i5+8], %f16
	or	%g2, %lo(NavIonoCorrction), %g1
	ldd	[%i5+16], %f14
	ldd	[%i5+24], %f12
	ldd	[%i5+32], %f10
	ldd	[%i5+40], %f8
	ldd	[%i5+48], %f18
	ldd	[%i5+56], %f20
	std	%f0, [%i4+%lo(temp_Iono_Corr)]
	std	%f0, [%g2+%lo(NavIonoCorrction)]
	std	%f16, [%g1+8]
	std	%f14, [%g1+16]
	std	%f12, [%g1+24]
	std	%f10, [%g1+32]
	std	%f8, [%g1+40]
	std	%f18, [%g1+48]
	std	%f20, [%g1+56]
	jmp	%i7+8
	 restore
	.size	NavExtractDataFrameThreeFour, .-NavExtractDataFrameThreeFour
	.section	.text.VerifyCopyFrameOneData,"ax",@progbits
	.align 4
	.global VerifyCopyFrameOneData
	.type	VerifyCopyFrameOneData, #function
	.proc	020
VerifyCopyFrameOneData:
	sethi	%hi(temp_frame1), %g2
	or	%g2, %lo(temp_frame1), %g1
	ld	[%g1+124], %g3
	cmp	%g3, 1
	be	.L601
	 nop
	ld	[%g1+128], %g3
	cmp	%g3, 14
	bg	.L598
	 sethi	%hi(DataBufFrqBand), %g4
	ld	[%g4+%lo(DataBufFrqBand)], %g4
	cmp	%g4, 1
	be	.L599
	 cmp	%g4, 0
	bne,a	.L600
	 ld	[%g1+112], %o5
	ld	[%g1+116], %g4
	cmp	%g4, 1
	be	.L601
	 nop
	ld	[%g1+112], %o5
.L586:
	ld	[%g1+132], %o3
	ldd	[%g1+8], %f26
	ldd	[%g1+16], %f24
	ldd	[%g1+24], %f22
	ldd	[%g1+32], %f20
	ldd	[%g1+40], %f18
	ldd	[%g1+48], %f16
	ldd	[%g1+56], %f14
	ldd	[%g1+64], %f12
	ldd	[%g1+72], %f10
	ldd	[%g1+80], %f8
	ldd	[%g1+88], %f30
	ldd	[%g1+96], %f6
	ldd	[%g1+104], %f4
	ld	[%g1+136], %o4
	sll	%o0, 4, %g1
	ldd	[%g2+%lo(temp_frame1)], %f28
	sll	%o0, 7, %o0
	sethi	%hi(NavSubFrame1Data), %g2
	add	%g1, %o0, %o0
	or	%g2, %lo(NavSubFrame1Data), %g2
	add	%g2, %o0, %g1
	std	%f28, [%g2+%o0]
	st	%o3, [%g1+132]
	std	%f26, [%g1+8]
	std	%f24, [%g1+16]
	st	%g3, [%g1+128]
	std	%f22, [%g1+24]
	std	%f20, [%g1+32]
	std	%f18, [%g1+40]
	std	%f16, [%g1+48]
	std	%f14, [%g1+56]
	std	%f12, [%g1+64]
	std	%f10, [%g1+72]
	std	%f8, [%g1+80]
	std	%f30, [%g1+88]
	std	%f6, [%g1+96]
	std	%f4, [%g1+104]
	st	%o4, [%g1+136]
	st	%o5, [%g1+112]
	st	%g4, [%g1+116]
.L601:
	jmp	%o7+8
	 nop
.L598:
	sll	%o0, 4, %g1
	sll	%o0, 7, %o0
	add	%g1, %o0, %o0
	sethi	%hi(NavSubFrame1Data), %g1
	or	%g1, %lo(NavSubFrame1Data), %g1
	add	%g1, %o0, %o0
	mov	-500, %g1
	jmp	%o7+8
	 st	%g1, [%o0+128]
.L599:
	ld	[%g1+112], %o5
	cmp	%o5, 1
	be	.L601
	 nop
	b	.L586
	 ld	[%g1+116], %g4
.L600:
	b	.L586
	 ld	[%g1+116], %g4
	.size	VerifyCopyFrameOneData, .-VerifyCopyFrameOneData
	.section	.text.NavExtractDataFrameMain,"ax",@progbits
	.align 4
	.global NavExtractDataFrameMain
	.type	NavExtractDataFrameMain, #function
	.proc	020
NavExtractDataFrameMain:
	save	%sp, -96, %sp
	ld	[%i0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L606
	 mov	%i0, %o0
	cmp	%g1, 3
	be	.L606
	 cmp	%g1, 1
	be	.L604
	 nop
	call	NavExtractDataFrameOne, 0
	 mov	%i1, %i0
	call	VerifyCopyFrameOneData, 0
	 restore
.L604:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L612
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f20
	ldd	[%g1+16], %f16
	ldd	[%g1+24], %f14
	ldd	[%g1+32], %f12
	ldd	[%g1+40], %f10
	ldd	[%g1+48], %f8
	ldd	[%g1+56], %f18
	sll	%i1, 4, %i4
	sethi	%hi(NavSubFrame2Data), %g4
	sll	%i1, 6, %i5
	or	%g4, %lo(NavSubFrame2Data), %g4
	add	%i4, %i5, %i5
	sethi	%hi(temp), %g1
	add	%g4, %i5, %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g4+%i5]
	std	%f20, [%g2+8]
	std	%f16, [%g2+16]
	std	%f14, [%g2+24]
	std	%f12, [%g2+32]
	std	%f10, [%g2+40]
	std	%f8, [%g2+48]
	std	%f18, [%g2+56]
	st	%g3, [%g2+64]
.L612:
	jmp	%i7+8
	 restore
.L606:
	call	NavExtractDataFrameThreeFour, 0
	 restore
	.size	NavExtractDataFrameMain, .-NavExtractDataFrameMain
	.section	.text.ReadandExtractData,"ax",@progbits
	.align 4
	.global ReadandExtractData
	.type	ReadandExtractData, #function
	.proc	04
ReadandExtractData:
	save	%sp, -96, %sp
	sethi	%hi(IntNavframeData01), %o0
	or	%o0, %lo(IntNavframeData01), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L617
	 cmp	%g1, 3
	be	.L617
	 cmp	%g1, 1
	be	.L615
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	0, %o0
.L618:
	sethi	%hi(IntNavframeData02), %o0
.L829:
	or	%o0, %lo(IntNavframeData02), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L622
	 cmp	%g1, 3
.L831:
	be	.L622
	 cmp	%g1, 1
	be	.L620
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	0, %o0
.L623:
	sethi	%hi(IntNavframeData03), %o0
	or	%o0, %lo(IntNavframeData03), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L627
	 cmp	%g1, 3
.L832:
	be	.L627
	 cmp	%g1, 1
	be	.L625
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	0, %o0
.L628:
	sethi	%hi(IntNavframeData04), %o0
	or	%o0, %lo(IntNavframeData04), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L632
	 cmp	%g1, 3
.L833:
	be	.L632
	 cmp	%g1, 1
	be	.L630
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	0, %o0
.L633:
	sethi	%hi(IntNavframeData11), %o0
	or	%o0, %lo(IntNavframeData11), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L637
	 cmp	%g1, 3
.L834:
	be	.L637
	 cmp	%g1, 1
	be	.L635
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	1, %o0
.L638:
	sethi	%hi(IntNavframeData12), %o0
	or	%o0, %lo(IntNavframeData12), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L642
	 cmp	%g1, 3
.L835:
	be	.L642
	 cmp	%g1, 1
	be	.L640
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	1, %o0
.L643:
	sethi	%hi(IntNavframeData13), %o0
	or	%o0, %lo(IntNavframeData13), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L647
	 cmp	%g1, 3
.L836:
	be	.L647
	 cmp	%g1, 1
	be	.L645
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	1, %o0
.L648:
	sethi	%hi(IntNavframeData14), %o0
	or	%o0, %lo(IntNavframeData14), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L652
	 cmp	%g1, 3
.L837:
	be	.L652
	 cmp	%g1, 1
	be	.L650
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	1, %o0
.L653:
	sethi	%hi(IntNavframeData21), %o0
	or	%o0, %lo(IntNavframeData21), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L657
	 cmp	%g1, 3
.L838:
	be	.L657
	 cmp	%g1, 1
	be	.L655
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	2, %o0
.L658:
	sethi	%hi(IntNavframeData22), %o0
	or	%o0, %lo(IntNavframeData22), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L662
	 cmp	%g1, 3
.L839:
	be	.L662
	 cmp	%g1, 1
	be	.L660
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	2, %o0
.L663:
	sethi	%hi(IntNavframeData23), %o0
	or	%o0, %lo(IntNavframeData23), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L667
	 cmp	%g1, 3
.L840:
	be	.L667
	 cmp	%g1, 1
	be	.L665
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	2, %o0
.L668:
	sethi	%hi(IntNavframeData24), %o0
	or	%o0, %lo(IntNavframeData24), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L672
	 cmp	%g1, 3
.L841:
	be	.L672
	 cmp	%g1, 1
	be	.L670
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	2, %o0
.L673:
	sethi	%hi(IntNavframeData31), %o0
	or	%o0, %lo(IntNavframeData31), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L677
	 cmp	%g1, 3
.L842:
	be	.L677
	 cmp	%g1, 1
	be	.L675
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	3, %o0
.L678:
	sethi	%hi(IntNavframeData32), %o0
	or	%o0, %lo(IntNavframeData32), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L682
	 cmp	%g1, 3
.L843:
	be	.L682
	 cmp	%g1, 1
	be	.L680
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	3, %o0
.L683:
	sethi	%hi(IntNavframeData33), %o0
	or	%o0, %lo(IntNavframeData33), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L687
	 cmp	%g1, 3
.L844:
	be	.L687
	 cmp	%g1, 1
	be	.L685
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	3, %o0
.L688:
	sethi	%hi(IntNavframeData34), %o0
	or	%o0, %lo(IntNavframeData34), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L692
	 cmp	%g1, 3
.L845:
	be	.L692
	 cmp	%g1, 1
	be	.L690
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	3, %o0
.L693:
	sethi	%hi(IntNavframeData41), %o0
	or	%o0, %lo(IntNavframeData41), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L697
	 cmp	%g1, 3
.L846:
	be	.L697
	 cmp	%g1, 1
	be	.L695
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	4, %o0
.L698:
	sethi	%hi(IntNavframeData42), %o0
	or	%o0, %lo(IntNavframeData42), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L702
	 cmp	%g1, 3
.L847:
	be	.L702
	 cmp	%g1, 1
	be	.L700
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	4, %o0
.L703:
	sethi	%hi(IntNavframeData43), %o0
	or	%o0, %lo(IntNavframeData43), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L707
	 cmp	%g1, 3
.L848:
	be	.L707
	 cmp	%g1, 1
	be	.L705
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	4, %o0
.L708:
	sethi	%hi(IntNavframeData44), %o0
	or	%o0, %lo(IntNavframeData44), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L712
	 cmp	%g1, 3
.L849:
	be	.L712
	 cmp	%g1, 1
	be	.L710
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	4, %o0
.L713:
	sethi	%hi(IntNavframeData51), %o0
	or	%o0, %lo(IntNavframeData51), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L717
	 cmp	%g1, 3
.L850:
	be	.L717
	 cmp	%g1, 1
	be	.L715
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	5, %o0
	sethi	%hi(IntNavframeData52), %o0
.L857:
	or	%o0, %lo(IntNavframeData52), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L722
	 cmp	%g1, 3
.L851:
	be	.L722
	 cmp	%g1, 1
	be	.L720
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	5, %o0
	sethi	%hi(IntNavframeData53), %o0
.L856:
	or	%o0, %lo(IntNavframeData53), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be	.L727
	 cmp	%g1, 3
.L852:
	be	.L727
	 cmp	%g1, 1
	be	.L725
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	5, %o0
	sethi	%hi(IntNavframeData54), %o0
.L855:
	or	%o0, %lo(IntNavframeData54), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	be,a	.L830
	 mov	5, %o1
	cmp	%g1, 3
.L853:
	be	.L732
	 cmp	%g1, 1
	be	.L730
	 nop
	call	NavExtractDataFrameOne, 0
	 nop
	call	VerifyCopyFrameOneData, 0
	 mov	5, %o0
	sethi	%hi(96256), %i0
.L854:
	or	%i0, 1004, %i0
	jmp	%i7+8
	 restore
.L615:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g3
	or	%g3, %lo(temp_frame2), %g1
	ld	[%g1+68], %g2
	cmp	%g2, 1
	be	.L618
	 sethi	%hi(NavSubFrame2Data), %i5
	ld	[%g1+64], %g4
	ldd	[%g1+8], %f14
	or	%i5, %lo(NavSubFrame2Data), %g2
	ldd	[%g1+16], %f12
	ldd	[%g1+24], %f10
	ldd	[%g1+32], %f8
	ldd	[%g1+40], %f18
	ldd	[%g1+48], %f20
	ldd	[%g1+56], %f22
	ldd	[%g3+%lo(temp_frame2)], %f16
	sethi	%hi(temp), %g1
	std	%f16, [%i5+%lo(NavSubFrame2Data)]
	st	%g4, [%g1+%lo(temp)]
	std	%f14, [%g2+8]
	std	%f12, [%g2+16]
	std	%f10, [%g2+24]
	std	%f8, [%g2+32]
	std	%f18, [%g2+40]
	std	%f20, [%g2+48]
	std	%f22, [%g2+56]
	st	%g4, [%g2+64]
	sethi	%hi(IntNavframeData02), %o0
	or	%o0, %lo(IntNavframeData02), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L831
	 cmp	%g1, 3
.L622:
	call	NavExtractDataFrameThreeFour, 0
	 mov	0, %o1
	sethi	%hi(IntNavframeData03), %o0
	or	%o0, %lo(IntNavframeData03), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L832
	 cmp	%g1, 3
.L627:
	call	NavExtractDataFrameThreeFour, 0
	 mov	0, %o1
	sethi	%hi(IntNavframeData04), %o0
	or	%o0, %lo(IntNavframeData04), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L833
	 cmp	%g1, 3
.L632:
	call	NavExtractDataFrameThreeFour, 0
	 mov	0, %o1
	sethi	%hi(IntNavframeData11), %o0
	or	%o0, %lo(IntNavframeData11), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L834
	 cmp	%g1, 3
.L637:
	call	NavExtractDataFrameThreeFour, 0
	 mov	1, %o1
	sethi	%hi(IntNavframeData12), %o0
	or	%o0, %lo(IntNavframeData12), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L835
	 cmp	%g1, 3
.L642:
	call	NavExtractDataFrameThreeFour, 0
	 mov	1, %o1
	sethi	%hi(IntNavframeData13), %o0
	or	%o0, %lo(IntNavframeData13), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L836
	 cmp	%g1, 3
.L647:
	call	NavExtractDataFrameThreeFour, 0
	 mov	1, %o1
	sethi	%hi(IntNavframeData14), %o0
	or	%o0, %lo(IntNavframeData14), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L837
	 cmp	%g1, 3
.L652:
	call	NavExtractDataFrameThreeFour, 0
	 mov	1, %o1
	sethi	%hi(IntNavframeData21), %o0
	or	%o0, %lo(IntNavframeData21), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L838
	 cmp	%g1, 3
.L657:
	call	NavExtractDataFrameThreeFour, 0
	 mov	2, %o1
	sethi	%hi(IntNavframeData22), %o0
	or	%o0, %lo(IntNavframeData22), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L839
	 cmp	%g1, 3
.L662:
	call	NavExtractDataFrameThreeFour, 0
	 mov	2, %o1
	sethi	%hi(IntNavframeData23), %o0
	or	%o0, %lo(IntNavframeData23), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L840
	 cmp	%g1, 3
.L667:
	call	NavExtractDataFrameThreeFour, 0
	 mov	2, %o1
	sethi	%hi(IntNavframeData24), %o0
	or	%o0, %lo(IntNavframeData24), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L841
	 cmp	%g1, 3
.L672:
	call	NavExtractDataFrameThreeFour, 0
	 mov	2, %o1
	sethi	%hi(IntNavframeData31), %o0
	or	%o0, %lo(IntNavframeData31), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L842
	 cmp	%g1, 3
.L677:
	call	NavExtractDataFrameThreeFour, 0
	 mov	3, %o1
	sethi	%hi(IntNavframeData32), %o0
	or	%o0, %lo(IntNavframeData32), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L843
	 cmp	%g1, 3
.L682:
	call	NavExtractDataFrameThreeFour, 0
	 mov	3, %o1
	sethi	%hi(IntNavframeData33), %o0
	or	%o0, %lo(IntNavframeData33), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L844
	 cmp	%g1, 3
.L687:
	call	NavExtractDataFrameThreeFour, 0
	 mov	3, %o1
	sethi	%hi(IntNavframeData34), %o0
	or	%o0, %lo(IntNavframeData34), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L845
	 cmp	%g1, 3
.L692:
	call	NavExtractDataFrameThreeFour, 0
	 mov	3, %o1
	sethi	%hi(IntNavframeData41), %o0
	or	%o0, %lo(IntNavframeData41), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L846
	 cmp	%g1, 3
.L697:
	call	NavExtractDataFrameThreeFour, 0
	 mov	4, %o1
	sethi	%hi(IntNavframeData42), %o0
	or	%o0, %lo(IntNavframeData42), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L847
	 cmp	%g1, 3
.L702:
	call	NavExtractDataFrameThreeFour, 0
	 mov	4, %o1
	sethi	%hi(IntNavframeData43), %o0
	or	%o0, %lo(IntNavframeData43), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L848
	 cmp	%g1, 3
.L707:
	call	NavExtractDataFrameThreeFour, 0
	 mov	4, %o1
	sethi	%hi(IntNavframeData44), %o0
	or	%o0, %lo(IntNavframeData44), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L849
	 cmp	%g1, 3
.L712:
	call	NavExtractDataFrameThreeFour, 0
	 mov	4, %o1
	sethi	%hi(IntNavframeData51), %o0
	or	%o0, %lo(IntNavframeData51), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L850
	 cmp	%g1, 3
.L717:
	call	NavExtractDataFrameThreeFour, 0
	 mov	5, %o1
	sethi	%hi(IntNavframeData52), %o0
	or	%o0, %lo(IntNavframeData52), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L851
	 cmp	%g1, 3
.L722:
	call	NavExtractDataFrameThreeFour, 0
	 mov	5, %o1
	sethi	%hi(IntNavframeData53), %o0
	or	%o0, %lo(IntNavframeData53), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L852
	 cmp	%g1, 3
.L727:
	call	NavExtractDataFrameThreeFour, 0
	 mov	5, %o1
	sethi	%hi(IntNavframeData54), %o0
	or	%o0, %lo(IntNavframeData54), %o0
	ld	[%o0+12], %g1
	and	%g1, 24, %g1
	srl	%g1, 3, %g1
	cmp	%g1, 2
	bne	.L853
	 cmp	%g1, 3
.L732:
	mov	5, %o1
.L830:
	call	NavExtractDataFrameThreeFour, 0
	 sethi	%hi(96256), %i0
	or	%i0, 1004, %i0
	jmp	%i7+8
	 restore
.L617:
	call	NavExtractDataFrameThreeFour, 0
	 mov	0, %o1
	b	.L829
	 sethi	%hi(IntNavframeData02), %o0
.L620:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g3
	or	%g3, %lo(temp_frame2), %g1
	ld	[%g1+68], %g2
	cmp	%g2, 1
	be	.L623
	 sethi	%hi(NavSubFrame2Data), %i5
	ld	[%g1+64], %g4
	ldd	[%g1+8], %f14
	or	%i5, %lo(NavSubFrame2Data), %g2
	ldd	[%g1+16], %f12
	ldd	[%g1+24], %f10
	ldd	[%g1+32], %f8
	ldd	[%g1+40], %f18
	ldd	[%g1+48], %f20
	ldd	[%g1+56], %f22
	ldd	[%g3+%lo(temp_frame2)], %f16
	sethi	%hi(temp), %g1
	std	%f16, [%i5+%lo(NavSubFrame2Data)]
	st	%g4, [%g1+%lo(temp)]
	std	%f14, [%g2+8]
	std	%f12, [%g2+16]
	std	%f10, [%g2+24]
	std	%f8, [%g2+32]
	std	%f18, [%g2+40]
	std	%f20, [%g2+48]
	std	%f22, [%g2+56]
	b	.L623
	 st	%g4, [%g2+64]
.L630:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g3
	or	%g3, %lo(temp_frame2), %g1
	ld	[%g1+68], %g2
	cmp	%g2, 1
	be	.L633
	 sethi	%hi(NavSubFrame2Data), %i5
	ld	[%g1+64], %g4
	ldd	[%g1+8], %f14
	or	%i5, %lo(NavSubFrame2Data), %g2
	ldd	[%g1+16], %f12
	ldd	[%g1+24], %f10
	ldd	[%g1+32], %f8
	ldd	[%g1+40], %f18
	ldd	[%g1+48], %f20
	ldd	[%g1+56], %f22
	ldd	[%g3+%lo(temp_frame2)], %f16
	sethi	%hi(temp), %g1
	std	%f16, [%i5+%lo(NavSubFrame2Data)]
	st	%g4, [%g1+%lo(temp)]
	std	%f14, [%g2+8]
	std	%f12, [%g2+16]
	std	%f10, [%g2+24]
	std	%f8, [%g2+32]
	std	%f18, [%g2+40]
	std	%f20, [%g2+48]
	std	%f22, [%g2+56]
	b	.L633
	 st	%g4, [%g2+64]
.L625:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g3
	or	%g3, %lo(temp_frame2), %g1
	ld	[%g1+68], %g2
	cmp	%g2, 1
	be	.L628
	 sethi	%hi(NavSubFrame2Data), %i5
	ld	[%g1+64], %g4
	ldd	[%g1+8], %f14
	or	%i5, %lo(NavSubFrame2Data), %g2
	ldd	[%g1+16], %f12
	ldd	[%g1+24], %f10
	ldd	[%g1+32], %f8
	ldd	[%g1+40], %f18
	ldd	[%g1+48], %f20
	ldd	[%g1+56], %f22
	ldd	[%g3+%lo(temp_frame2)], %f16
	sethi	%hi(temp), %g1
	std	%f16, [%i5+%lo(NavSubFrame2Data)]
	st	%g4, [%g1+%lo(temp)]
	std	%f14, [%g2+8]
	std	%f12, [%g2+16]
	std	%f10, [%g2+24]
	std	%f8, [%g2+32]
	std	%f18, [%g2+40]
	std	%f20, [%g2+48]
	std	%f22, [%g2+56]
	b	.L628
	 st	%g4, [%g2+64]
.L650:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L653
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+80]
	std	%f16, [%g2+88]
	std	%f14, [%g2+96]
	std	%f12, [%g2+104]
	std	%f10, [%g2+112]
	std	%f8, [%g2+120]
	std	%f18, [%g2+128]
	std	%f20, [%g2+136]
	b	.L653
	 st	%g3, [%g2+144]
.L645:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L648
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+80]
	std	%f16, [%g2+88]
	std	%f14, [%g2+96]
	std	%f12, [%g2+104]
	std	%f10, [%g2+112]
	std	%f8, [%g2+120]
	std	%f18, [%g2+128]
	std	%f20, [%g2+136]
	b	.L648
	 st	%g3, [%g2+144]
.L640:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L643
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+80]
	std	%f16, [%g2+88]
	std	%f14, [%g2+96]
	std	%f12, [%g2+104]
	std	%f10, [%g2+112]
	std	%f8, [%g2+120]
	std	%f18, [%g2+128]
	std	%f20, [%g2+136]
	b	.L643
	 st	%g3, [%g2+144]
.L635:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L638
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+80]
	std	%f16, [%g2+88]
	std	%f14, [%g2+96]
	std	%f12, [%g2+104]
	std	%f10, [%g2+112]
	std	%f8, [%g2+120]
	std	%f18, [%g2+128]
	std	%f20, [%g2+136]
	b	.L638
	 st	%g3, [%g2+144]
.L730:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L854
	 sethi	%hi(96256), %i0
	ld	[%g1+64], %g3
	ldd	[%g2+%lo(temp_frame2)], %f22
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+400]
	std	%f16, [%g2+408]
	std	%f14, [%g2+416]
	std	%f12, [%g2+424]
	std	%f10, [%g2+432]
	std	%f8, [%g2+440]
	std	%f18, [%g2+448]
	std	%f20, [%g2+456]
	st	%g3, [%g2+464]
	or	%i0, 1004, %i0
	jmp	%i7+8
	 restore
.L725:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L855
	 sethi	%hi(IntNavframeData54), %o0
	ld	[%g1+64], %g3
	ldd	[%g2+%lo(temp_frame2)], %f22
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+400]
	std	%f16, [%g2+408]
	std	%f14, [%g2+416]
	std	%f12, [%g2+424]
	std	%f10, [%g2+432]
	std	%f8, [%g2+440]
	std	%f18, [%g2+448]
	std	%f20, [%g2+456]
	b	.L855
	 st	%g3, [%g2+464]
.L720:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L856
	 sethi	%hi(IntNavframeData53), %o0
	ld	[%g1+64], %g3
	ldd	[%g2+%lo(temp_frame2)], %f22
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+400]
	std	%f16, [%g2+408]
	std	%f14, [%g2+416]
	std	%f12, [%g2+424]
	std	%f10, [%g2+432]
	std	%f8, [%g2+440]
	std	%f18, [%g2+448]
	std	%f20, [%g2+456]
	b	.L856
	 st	%g3, [%g2+464]
.L715:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L857
	 sethi	%hi(IntNavframeData52), %o0
	ld	[%g1+64], %g3
	ldd	[%g2+%lo(temp_frame2)], %f22
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+400]
	std	%f16, [%g2+408]
	std	%f14, [%g2+416]
	std	%f12, [%g2+424]
	std	%f10, [%g2+432]
	std	%f8, [%g2+440]
	std	%f18, [%g2+448]
	std	%f20, [%g2+456]
	b	.L857
	 st	%g3, [%g2+464]
.L710:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L713
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+320]
	std	%f16, [%g2+328]
	std	%f14, [%g2+336]
	std	%f12, [%g2+344]
	std	%f10, [%g2+352]
	std	%f8, [%g2+360]
	std	%f18, [%g2+368]
	std	%f20, [%g2+376]
	b	.L713
	 st	%g3, [%g2+384]
.L705:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L708
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+320]
	std	%f16, [%g2+328]
	std	%f14, [%g2+336]
	std	%f12, [%g2+344]
	std	%f10, [%g2+352]
	std	%f8, [%g2+360]
	std	%f18, [%g2+368]
	std	%f20, [%g2+376]
	b	.L708
	 st	%g3, [%g2+384]
.L700:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L703
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+320]
	std	%f16, [%g2+328]
	std	%f14, [%g2+336]
	std	%f12, [%g2+344]
	std	%f10, [%g2+352]
	std	%f8, [%g2+360]
	std	%f18, [%g2+368]
	std	%f20, [%g2+376]
	b	.L703
	 st	%g3, [%g2+384]
.L695:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L698
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+320]
	std	%f16, [%g2+328]
	std	%f14, [%g2+336]
	std	%f12, [%g2+344]
	std	%f10, [%g2+352]
	std	%f8, [%g2+360]
	std	%f18, [%g2+368]
	std	%f20, [%g2+376]
	b	.L698
	 st	%g3, [%g2+384]
.L690:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L693
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+240]
	std	%f16, [%g2+248]
	std	%f14, [%g2+256]
	std	%f12, [%g2+264]
	std	%f10, [%g2+272]
	std	%f8, [%g2+280]
	std	%f18, [%g2+288]
	std	%f20, [%g2+296]
	b	.L693
	 st	%g3, [%g2+304]
.L685:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L688
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+240]
	std	%f16, [%g2+248]
	std	%f14, [%g2+256]
	std	%f12, [%g2+264]
	std	%f10, [%g2+272]
	std	%f8, [%g2+280]
	std	%f18, [%g2+288]
	std	%f20, [%g2+296]
	b	.L688
	 st	%g3, [%g2+304]
.L680:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L683
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+240]
	std	%f16, [%g2+248]
	std	%f14, [%g2+256]
	std	%f12, [%g2+264]
	std	%f10, [%g2+272]
	std	%f8, [%g2+280]
	std	%f18, [%g2+288]
	std	%f20, [%g2+296]
	b	.L683
	 st	%g3, [%g2+304]
.L675:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L678
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+240]
	std	%f16, [%g2+248]
	std	%f14, [%g2+256]
	std	%f12, [%g2+264]
	std	%f10, [%g2+272]
	std	%f8, [%g2+280]
	std	%f18, [%g2+288]
	std	%f20, [%g2+296]
	b	.L678
	 st	%g3, [%g2+304]
.L670:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L673
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+160]
	std	%f16, [%g2+168]
	std	%f14, [%g2+176]
	std	%f12, [%g2+184]
	std	%f10, [%g2+192]
	std	%f8, [%g2+200]
	std	%f18, [%g2+208]
	std	%f20, [%g2+216]
	b	.L673
	 st	%g3, [%g2+224]
.L665:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L668
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+160]
	std	%f16, [%g2+168]
	std	%f14, [%g2+176]
	std	%f12, [%g2+184]
	std	%f10, [%g2+192]
	std	%f8, [%g2+200]
	std	%f18, [%g2+208]
	std	%f20, [%g2+216]
	b	.L668
	 st	%g3, [%g2+224]
.L660:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L663
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+160]
	std	%f16, [%g2+168]
	std	%f14, [%g2+176]
	std	%f12, [%g2+184]
	std	%f10, [%g2+192]
	std	%f8, [%g2+200]
	std	%f18, [%g2+208]
	std	%f20, [%g2+216]
	b	.L663
	 st	%g3, [%g2+224]
.L655:
	call	NavExtractDataFrameTwo, 0
	 nop
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L658
	 ldd	[%g2+%lo(temp_frame2)], %f22
	ld	[%g1+64], %g3
	ldd	[%g1+8], %f16
	ldd	[%g1+16], %f14
	ldd	[%g1+24], %f12
	ldd	[%g1+32], %f10
	ldd	[%g1+40], %f8
	ldd	[%g1+48], %f18
	ldd	[%g1+56], %f20
	sethi	%hi(NavSubFrame2Data), %g2
	sethi	%hi(temp), %g1
	or	%g2, %lo(NavSubFrame2Data), %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g2+160]
	std	%f16, [%g2+168]
	std	%f14, [%g2+176]
	std	%f12, [%g2+184]
	std	%f10, [%g2+192]
	std	%f8, [%g2+200]
	std	%f18, [%g2+208]
	std	%f20, [%g2+216]
	b	.L658
	 st	%g3, [%g2+224]
	.size	ReadandExtractData, .-ReadandExtractData
	.section	.text.VerifyCopyFrameTwoData,"ax",@progbits
	.align 4
	.global VerifyCopyFrameTwoData
	.type	VerifyCopyFrameTwoData, #function
	.proc	020
VerifyCopyFrameTwoData:
	sethi	%hi(temp_frame2), %g2
	or	%g2, %lo(temp_frame2), %g1
	ld	[%g1+68], %g3
	cmp	%g3, 1
	be	.L863
	 sll	%o0, 4, %o5
	ld	[%g1+64], %g3
	ldd	[%g2+%lo(temp_frame2)], %f22
	ldd	[%g1+8], %f20
	ldd	[%g1+16], %f16
	ldd	[%g1+24], %f14
	ldd	[%g1+32], %f12
	ldd	[%g1+40], %f10
	ldd	[%g1+48], %f8
	ldd	[%g1+56], %f18
	sethi	%hi(NavSubFrame2Data), %g4
	sll	%o0, 6, %o0
	or	%g4, %lo(NavSubFrame2Data), %g4
	add	%o5, %o0, %o0
	sethi	%hi(temp), %g1
	add	%g4, %o0, %g2
	st	%g3, [%g1+%lo(temp)]
	std	%f22, [%g4+%o0]
	std	%f20, [%g2+8]
	std	%f16, [%g2+16]
	std	%f14, [%g2+24]
	std	%f12, [%g2+32]
	std	%f10, [%g2+40]
	std	%f8, [%g2+48]
	std	%f18, [%g2+56]
	st	%g3, [%g2+64]
.L863:
	jmp	%o7+8
	 nop
	.size	VerifyCopyFrameTwoData, .-VerifyCopyFrameTwoData
	.section	.text.VerifyCopyFrameThreeFourData,"ax",@progbits
	.align 4
	.global VerifyCopyFrameThreeFourData
	.type	VerifyCopyFrameThreeFourData, #function
	.proc	020
VerifyCopyFrameThreeFourData:
	sethi	%hi(temp_frame3_4), %g1
	sll	%o0, 2, %g4
	or	%g1, %lo(temp_frame3_4), %g2
	ld	[%g1+%lo(temp_frame3_4)], %o2
	ld	[%g2+4], %o3
	ld	[%g2+16], %o4
	ld	[%g2+8], %o5
	sethi	%hi(NavSubFrame3_4Data), %g3
	sll	%o0, 5, %o0
	or	%g3, %lo(NavSubFrame3_4Data), %g3
	sub	%o0, %g4, %o0
	ld	[%g2+12], %g4
	add	%g3, %o0, %g1
	ld	[%g2+20], %g2
	st	%o2, [%g3+%o0]
	st	%o3, [%g1+4]
	st	%o4, [%g1+16]
	st	%o5, [%g1+8]
	st	%g4, [%g1+12]
	jmp	%o7+8
	 st	%g2, [%g1+20]
	.size	VerifyCopyFrameThreeFourData, .-VerifyCopyFrameThreeFourData
	.section	.rodata.cst8
	.align 8
.LC26:
	.long	1073741824
	.long	0
	.section	.text.VerifyCopyMesssgeNine,"ax",@progbits
	.align 4
	.global VerifyCopyMesssgeNine
	.type	VerifyCopyMesssgeNine, #function
	.proc	020
VerifyCopyMesssgeNine:
	save	%sp, -104, %sp
	sethi	%hi(temp_UTCCorr), %i4
	sethi	%hi(.LC26), %g1
	ldd	[%i4+%lo(temp_UTCCorr)], %f8
	ldd	[%g1+%lo(.LC26)], %o0
	std	%f8, [%fp-8]
	mov	-35, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	or	%i4, %lo(temp_UTCCorr), %i5
	fmuld	%f8, %f0, %f0
	sethi	%hi(NavUTCCorr), %g2
	ldd	[%i5+8], %f16
	or	%g2, %lo(NavUTCCorr), %g1
	ldd	[%i5+16], %f14
	ldd	[%i5+24], %f12
	ldd	[%i5+32], %f10
	ldd	[%i5+40], %f8
	ldd	[%i5+48], %f18
	ldd	[%i5+56], %f20
	ldd	[%i5+64], %f22
	ldd	[%i5+72], %f24
	ldd	[%i5+80], %f26
	ldd	[%i5+88], %f28
	ldd	[%i5+96], %f30
	ldd	[%i5+104], %f6
	ld	[%i5+112], %g3
	std	%f0, [%i4+%lo(temp_UTCCorr)]
	std	%f0, [%g2+%lo(NavUTCCorr)]
	std	%f16, [%g1+8]
	std	%f14, [%g1+16]
	std	%f12, [%g1+24]
	std	%f10, [%g1+32]
	std	%f8, [%g1+40]
	std	%f18, [%g1+48]
	std	%f20, [%g1+56]
	std	%f22, [%g1+64]
	std	%f24, [%g1+72]
	std	%f26, [%g1+80]
	std	%f28, [%g1+88]
	std	%f30, [%g1+96]
	std	%f6, [%g1+104]
	st	%g3, [%g1+112]
	jmp	%i7+8
	 restore
	.size	VerifyCopyMesssgeNine, .-VerifyCopyMesssgeNine
	.section	.rodata.cst8
	.align 8
.LC27:
	.long	1073741824
	.long	0
	.section	.text.VerifyCopyMessageEleven,"ax",@progbits
	.align 4
	.global VerifyCopyMessageEleven
	.type	VerifyCopyMessageEleven, #function
	.proc	020
VerifyCopyMessageEleven:
	save	%sp, -104, %sp
	sethi	%hi(temp_Iono_Corr), %i4
	sethi	%hi(.LC27), %g1
	ldd	[%i4+%lo(temp_Iono_Corr)], %f8
	ldd	[%g1+%lo(.LC27)], %o0
	std	%f8, [%fp-8]
	mov	-30, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	or	%i4, %lo(temp_Iono_Corr), %i5
	fmuld	%f8, %f0, %f0
	sethi	%hi(NavIonoCorrction), %g2
	ldd	[%i5+8], %f16
	or	%g2, %lo(NavIonoCorrction), %g1
	ldd	[%i5+16], %f14
	ldd	[%i5+24], %f12
	ldd	[%i5+32], %f10
	ldd	[%i5+40], %f8
	ldd	[%i5+48], %f18
	ldd	[%i5+56], %f20
	std	%f0, [%i4+%lo(temp_Iono_Corr)]
	std	%f0, [%g2+%lo(NavIonoCorrction)]
	std	%f16, [%g1+8]
	std	%f14, [%g1+16]
	std	%f12, [%g1+24]
	std	%f10, [%g1+32]
	std	%f8, [%g1+40]
	std	%f18, [%g1+48]
	std	%f20, [%g1+56]
	jmp	%i7+8
	 restore
	.size	VerifyCopyMessageEleven, .-VerifyCopyMessageEleven
	.section	.rodata.cst8
	.align 8
.LC28:
	.long	1073741824
	.long	0
	.section	.text.VerifyCopyFrameMessageTwentySix,"ax",@progbits
	.align 4
	.global VerifyCopyFrameMessageTwentySix
	.type	VerifyCopyFrameMessageTwentySix, #function
	.proc	020
VerifyCopyFrameMessageTwentySix:
	save	%sp, -104, %sp
	sethi	%hi(temp_UTCCorr), %i4
	sethi	%hi(.LC28), %g1
	ldd	[%i4+%lo(temp_UTCCorr)], %f8
	ldd	[%g1+%lo(.LC28)], %o0
	std	%f8, [%fp-8]
	mov	-35, %o2
	call	xx__pow_opt, 0
	 mov	0, %o3
	ldd	[%fp-8], %f8
	or	%i4, %lo(temp_UTCCorr), %i5
	fmuld	%f8, %f0, %f0
	sethi	%hi(NavUTCCorr), %g2
	ldd	[%i5+8], %f16
	or	%g2, %lo(NavUTCCorr), %g1
	ldd	[%i5+16], %f14
	ldd	[%i5+24], %f12
	ldd	[%i5+32], %f10
	ldd	[%i5+40], %f8
	ldd	[%i5+48], %f18
	ldd	[%i5+56], %f20
	ldd	[%i5+64], %f22
	ldd	[%i5+72], %f24
	ldd	[%i5+80], %f26
	ldd	[%i5+88], %f28
	ldd	[%i5+96], %f30
	ldd	[%i5+104], %f6
	ld	[%i5+112], %g3
	std	%f0, [%i4+%lo(temp_UTCCorr)]
	std	%f0, [%g2+%lo(NavUTCCorr)]
	std	%f16, [%g1+8]
	std	%f14, [%g1+16]
	std	%f12, [%g1+24]
	std	%f10, [%g1+32]
	std	%f8, [%g1+40]
	std	%f18, [%g1+48]
	std	%f20, [%g1+56]
	std	%f22, [%g1+64]
	std	%f24, [%g1+72]
	std	%f26, [%g1+80]
	std	%f28, [%g1+88]
	std	%f30, [%g1+96]
	std	%f6, [%g1+104]
	st	%g3, [%g1+112]
	jmp	%i7+8
	 restore
	.size	VerifyCopyFrameMessageTwentySix, .-VerifyCopyFrameMessageTwentySix
	.global IntNavframeData54
	.section	".data"
	.align 4
	.type	IntNavframeData54, #object
	.size	IntNavframeData54, 148
IntNavframeData54:
	.long	139
	.long	15
	.long	212
	.long	24
	.long	177
	.long	81
	.long	129
	.long	219
	.long	252
	.long	249
	.long	210
	.long	41
	.long	252
	.long	159
	.long	43
	.long	95
	.long	246
	.long	252
	.long	66
	.long	253
	.long	130
	.long	232
	.long	112
	.long	81
	.long	250
	.long	8
	.long	204
	.long	45
	.long	254
	.long	4
	.long	0
	.long	0
	.long	30
	.long	87
	.long	173
	.long	172
	.long	0
	.global IntNavframeData53
	.align 4
	.type	IntNavframeData53, #object
	.size	IntNavframeData53, 148
IntNavframeData53:
	.long	139
	.long	15
	.long	211
	.long	144
	.long	80
	.long	25
	.long	116
	.long	29
	.long	161
	.long	45
	.long	7
	.long	232
	.long	71
	.long	66
	.long	63
	.long	255
	.long	255
	.long	254
	.long	128
	.long	52
	.long	5
	.long	160
	.long	29
	.long	3
	.long	232
	.long	35
	.long	64
	.long	154
	.long	6
	.long	208
	.long	32
	.long	0
	.long	30
	.long	45
	.long	111
	.long	140
	.long	16
	.global IntNavframeData52
	.align 4
	.type	IntNavframeData52, #object
	.size	IntNavframeData52, 148
IntNavframeData52:
	.long	139
	.long	15
	.long	211
	.long	8
	.long	24
	.long	185
	.long	86
	.long	180
	.long	91
	.long	104
	.long	0
	.long	128
	.long	74
	.long	23
	.long	43
	.long	171
	.long	13
	.long	98
	.long	229
	.long	81
	.long	220
	.long	74
	.long	203
	.long	1
	.long	85
	.long	47
	.long	255
	.long	160
	.long	96
	.long	54
	.long	81
	.long	200
	.long	98
	.long	56
	.long	175
	.long	32
	.long	0
	.global IntNavframeData51
	.align 4
	.type	IntNavframeData51, #object
	.size	IntNavframeData51, 148
IntNavframeData51:
	.long	139
	.long	15
	.long	210
	.long	131
	.long	125
	.long	78
	.long	204
	.long	84
	.long	9
	.long	148
	.long	0
	.long	5
	.long	182
	.long	191
	.long	64
	.long	8
	.long	76
	.long	1
	.long	255
	.long	194
	.long	248
	.long	123
	.long	98
	.long	64
	.long	7
	.long	0
	.long	47
	.long	67
	.long	72
	.long	174
	.long	127
	.long	245
	.long	82
	.long	231
	.long	248
	.long	240
	.long	0
	.global IntNavframeData44
	.align 4
	.type	IntNavframeData44, #object
	.size	IntNavframeData44, 148
IntNavframeData44:
	.long	139
	.long	15
	.long	212
	.long	24
	.long	80
	.long	24
	.long	112
	.long	149
	.long	133
	.long	44
	.long	43
	.long	105
	.long	115
	.long	76
	.long	56
	.long	46
	.long	193
	.long	125
	.long	140
	.long	236
	.long	107
	.long	99
	.long	171
	.long	32
	.long	225
	.long	31
	.long	9
	.long	120
	.long	77
	.long	210
	.long	112
	.long	0
	.long	25
	.long	120
	.long	63
	.long	224
	.long	0
	.global IntNavframeData43
	.align 4
	.type	IntNavframeData43, #object
	.size	IntNavframeData43, 148
IntNavframeData43:
	.long	139
	.long	15
	.long	211
	.long	144
	.long	80
	.long	24
	.long	52
	.long	129
	.long	132
	.long	60
	.long	36
	.long	97
	.long	55
	.long	10
	.long	56
	.long	86
	.long	194
	.long	230
	.long	153
	.long	180
	.long	211
	.long	166
	.long	236
	.long	26
	.long	224
	.long	231
	.long	7
	.long	182
	.long	65
	.long	178
	.long	48
	.long	0
	.long	24
	.long	66
	.long	89
	.long	8
	.long	0
	.global IntNavframeData42
	.align 4
	.type	IntNavframeData42, #object
	.size	IntNavframeData42, 148
IntNavframeData42:
	.long	139
	.long	15
	.long	211
	.long	11
	.long	187
	.long	212
	.long	246
	.long	80
	.long	91
	.long	104
	.long	4
	.long	54
	.long	68
	.long	215
	.long	43
	.long	174
	.long	68
	.long	94
	.long	225
	.long	232
	.long	61
	.long	166
	.long	22
	.long	225
	.long	180
	.long	219
	.long	255
	.long	224
	.long	48
	.long	53
	.long	118
	.long	60
	.long	2
	.long	167
	.long	229
	.long	116
	.long	0
	.global IntNavframeData41
	.align 4
	.type	IntNavframeData41, #object
	.size	IntNavframeData41, 148
IntNavframeData41:
	.long	139
	.long	15
	.long	210
	.long	131
	.long	125
	.long	1
	.long	62
	.long	215
	.long	247
	.long	8
	.long	0
	.long	5
	.long	182
	.long	191
	.long	0
	.long	4
	.long	176
	.long	1
	.long	255
	.long	194
	.long	122
	.long	59
	.long	208
	.long	0
	.long	28
	.long	255
	.long	198
	.long	61
	.long	90
	.long	142
	.long	95
	.long	251
	.long	176
	.long	152
	.long	235
	.long	28
	.long	16
	.global IntNavframeData34
	.align 4
	.type	IntNavframeData34, #object
	.size	IntNavframeData34, 148
IntNavframeData34:
	.long	139
	.long	15
	.long	212
	.long	24
	.long	177
	.long	81
	.long	129
	.long	219
	.long	252
	.long	249
	.long	210
	.long	41
	.long	252
	.long	159
	.long	43
	.long	95
	.long	246
	.long	252
	.long	66
	.long	253
	.long	130
	.long	232
	.long	112
	.long	81
	.long	250
	.long	8
	.long	204
	.long	45
	.long	254
	.long	4
	.long	0
	.long	0
	.long	20
	.long	124
	.long	249
	.long	152
	.long	0
	.global IntNavframeData33
	.align 4
	.type	IntNavframeData33, #object
	.size	IntNavframeData33, 148
IntNavframeData33:
	.long	139
	.long	15
	.long	211
	.long	144
	.long	80
	.long	25
	.long	116
	.long	29
	.long	161
	.long	45
	.long	7
	.long	232
	.long	71
	.long	66
	.long	63
	.long	255
	.long	255
	.long	254
	.long	128
	.long	52
	.long	5
	.long	160
	.long	29
	.long	3
	.long	232
	.long	35
	.long	64
	.long	154
	.long	6
	.long	208
	.long	32
	.long	0
	.long	20
	.long	6
	.long	59
	.long	184
	.long	0
	.global IntNavframeData32
	.align 4
	.type	IntNavframeData32, #object
	.size	IntNavframeData32, 148
IntNavframeData32:
	.long	139
	.long	15
	.long	211
	.long	10
	.long	145
	.long	14
	.long	197
	.long	200
	.long	94
	.long	92
	.long	3
	.long	165
	.long	193
	.long	155
	.long	43
	.long	166
	.long	51
	.long	129
	.long	51
	.long	181
	.long	217
	.long	137
	.long	245
	.long	12
	.long	31
	.long	219
	.long	255
	.long	52
	.long	81
	.long	66
	.long	180
	.long	154
	.long	34
	.long	66
	.long	89
	.long	224
	.long	0
	.global IntNavframeData31
	.align 4
	.type	IntNavframeData31, #object
	.size	IntNavframeData31, 148
IntNavframeData31:
	.long	139
	.long	15
	.long	210
	.long	131
	.long	125
	.long	116
	.long	54
	.long	112
	.long	6
	.long	8
	.long	0
	.long	69
	.long	229
	.long	255
	.long	192
	.long	13
	.long	127
	.long	172
	.long	248
	.long	15
	.long	194
	.long	27
	.long	168
	.long	191
	.long	234
	.long	128
	.long	17
	.long	73
	.long	199
	.long	241
	.long	80
	.long	2
	.long	128
	.long	149
	.long	224
	.long	56
	.long	0
	.global IntNavframeData24
	.align 4
	.type	IntNavframeData24, #object
	.size	IntNavframeData24, 148
IntNavframeData24:
	.long	139
	.long	15
	.long	212
	.long	24
	.long	177
	.long	81
	.long	129
	.long	219
	.long	252
	.long	249
	.long	210
	.long	41
	.long	252
	.long	159
	.long	43
	.long	95
	.long	246
	.long	252
	.long	66
	.long	253
	.long	130
	.long	232
	.long	112
	.long	81
	.long	250
	.long	8
	.long	204
	.long	45
	.long	254
	.long	4
	.long	0
	.long	0
	.long	18
	.long	101
	.long	202
	.long	116
	.long	0
	.global IntNavframeData23
	.align 4
	.type	IntNavframeData23, #object
	.size	IntNavframeData23, 148
IntNavframeData23:
	.long	139
	.long	15
	.long	211
	.long	144
	.long	80
	.long	25
	.long	116
	.long	29
	.long	161
	.long	45
	.long	7
	.long	232
	.long	71
	.long	66
	.long	63
	.long	255
	.long	255
	.long	254
	.long	128
	.long	52
	.long	5
	.long	160
	.long	29
	.long	3
	.long	232
	.long	35
	.long	64
	.long	154
	.long	6
	.long	208
	.long	32
	.long	0
	.long	18
	.long	31
	.long	8
	.long	84
	.long	16
	.global IntNavframeData22
	.align 4
	.type	IntNavframeData22, #object
	.size	IntNavframeData22, 148
IntNavframeData22:
	.long	139
	.long	15
	.long	211
	.long	8
	.long	91
	.long	48
	.long	161
	.long	152
	.long	91
	.long	104
	.long	4
	.long	48
	.long	239
	.long	255
	.long	43
	.long	174
	.long	126
	.long	215
	.long	51
	.long	43
	.long	77
	.long	146
	.long	8
	.long	33
	.long	170
	.long	19
	.long	255
	.long	76
	.long	33
	.long	79
	.long	235
	.long	50
	.long	35
	.long	36
	.long	181
	.long	252
	.long	16
	.global IntNavframeData21
	.align 4
	.type	IntNavframeData21, #object
	.size	IntNavframeData21, 148
IntNavframeData21:
	.long	139
	.long	15
	.long	210
	.long	131
	.long	125
	.long	15
	.long	193
	.long	192
	.long	1
	.long	172
	.long	0
	.long	5
	.long	182
	.long	191
	.long	64
	.long	11
	.long	65
	.long	1
	.long	255
	.long	207
	.long	241
	.long	185
	.long	220
	.long	255
	.long	229
	.long	128
	.long	1
	.long	99
	.long	226
	.long	0
	.long	95
	.long	230
	.long	225
	.long	41
	.long	48
	.long	60
	.long	0
	.global IntNavframeData14
	.align 4
	.type	IntNavframeData14, #object
	.size	IntNavframeData14, 148
IntNavframeData14:
	.long	139
	.long	15
	.long	212
	.long	24
	.long	5
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	15
	.long	169
	.long	22
	.long	28
	.long	16
	.global IntNavframeData13
	.align 4
	.type	IntNavframeData13, #object
	.size	IntNavframeData13, 148
IntNavframeData13:
	.long	139
	.long	15
	.long	211
	.long	144
	.long	5
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	12
	.long	55
	.long	190
	.long	120
	.long	0
	.global IntNavframeData12
	.align 4
	.type	IntNavframeData12, #object
	.size	IntNavframeData12, 148
IntNavframeData12:
	.long	139
	.long	15
	.long	211
	.long	10
	.long	170
	.long	193
	.long	231
	.long	104
	.long	94
	.long	92
	.long	4
	.long	47
	.long	13
	.long	67
	.long	43
	.long	172
	.long	166
	.long	54
	.long	188
	.long	165
	.long	190
	.long	48
	.long	1
	.long	55
	.long	47
	.long	27
	.long	255
	.long	166
	.long	64
	.long	40
	.long	62
	.long	101
	.long	146
	.long	183
	.long	169
	.long	76
	.long	0
	.global IntNavframeData11
	.align 4
	.type	IntNavframeData11, #object
	.size	IntNavframeData11, 148
IntNavframeData11:
	.long	139
	.long	15
	.long	210
	.long	131
	.long	125
	.long	155
	.long	124
	.long	180
	.long	2
	.long	16
	.long	2
	.long	133
	.long	229
	.long	255
	.long	64
	.long	8
	.long	2
	.long	172
	.long	248
	.long	3
	.long	143
	.long	126
	.long	206
	.long	64
	.long	38
	.long	0
	.long	21
	.long	16
	.long	222
	.long	209
	.long	107
	.long	243
	.long	83
	.long	160
	.long	58
	.long	200
	.long	0
	.global IntNavframeData04
	.align 4
	.type	IntNavframeData04, #object
	.size	IntNavframeData04, 148
IntNavframeData04:
	.long	139
	.long	15
	.long	212
	.long	24
	.long	125
	.long	244
	.long	72
	.long	204
	.long	84
	.long	96
	.long	83
	.long	254
	.long	44
	.long	0
	.long	67
	.long	43
	.long	170
	.long	195
	.long	50
	.long	151
	.long	182
	.long	15
	.long	209
	.long	219
	.long	92
	.long	245
	.long	137
	.long	137
	.long	127
	.long	160
	.long	128
	.long	0
	.long	10
	.long	49
	.long	84
	.long	192
	.long	0
	.global IntNavframeData03
	.align 4
	.type	IntNavframeData03, #object
	.size	IntNavframeData03, 148
IntNavframeData03:
	.long	139
	.long	15
	.long	211
	.long	144
	.long	117
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	85
	.long	11
	.long	222
	.long	240
	.long	92
	.long	0
	.global IntNavframeData02
	.align 4
	.type	IntNavframeData02, #object
	.size	IntNavframeData02, 148
IntNavframeData02:
	.long	139
	.long	15
	.long	211
	.long	11
	.long	179
	.long	166
	.long	86
	.long	236
	.long	91
	.long	104
	.long	4
	.long	133
	.long	1
	.long	127
	.long	43
	.long	170
	.long	153
	.long	239
	.long	50
	.long	195
	.long	68
	.long	198
	.long	14
	.long	137
	.long	3
	.long	99
	.long	255
	.long	90
	.long	209
	.long	79
	.long	249
	.long	125
	.long	114
	.long	1
	.long	166
	.long	136
	.long	0
	.global IntNavframeData01
	.align 4
	.type	IntNavframeData01, #object
	.size	IntNavframeData01, 148
IntNavframeData01:
	.long	139
	.long	15
	.long	210
	.long	131
	.long	125
	.long	98
	.long	73
	.long	59
	.long	252
	.long	180
	.long	0
	.long	69
	.long	182
	.long	191
	.long	0
	.long	11
	.long	15
	.long	1
	.long	255
	.long	207
	.long	217
	.long	122
	.long	219
	.long	192
	.long	1
	.long	0
	.long	27
	.long	85
	.long	147
	.long	247
	.long	247
	.long	241
	.long	209
	.long	187
	.long	114
	.long	76
	.long	0
	.global DataBufFrqBand
	.section	".bss"
	.align 4
	.type	DataBufFrqBand, #object
	.size	DataBufFrqBand, 4
DataBufFrqBand:
	.skip	4
	.common	NavNMEAdata,192,8
	.common	temp,16,8
	.common	NavprocData1,6336,8
	.common	NavprocData,1056,8
	.common	temp_NavObsDat,144,8
	.common	NavObsDat,144,8
	.common	temp_Iono_Corr,64,8
	.common	NavIonoCorrction,64,8
	.common	temp_UTCCorr,120,8
	.common	NavUTCCorr,120,8
	.common	temp_frame3_4,28,4
	.common	NavSubFrame3_4Data,168,4
	.common	temp_frame2,80,8
	.common	NavSubFrame2Data,480,8
	.common	temp_frame1,144,8
	.common	NavSubFrame1Data,864,8
	.ident	"GCC: (Buildroot 2014.08-ga33456e-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
