	.file	"PVT.c"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	0
	.section	.text.NavComputeDOP.constprop.1,"ax",@progbits
	.align 4
	.type	NavComputeDOP.constprop.1, #function
	.proc	020
NavComputeDOP.constprop.1:
	save	%sp, -152, %sp
	sethi	%hi(.LC1), %i5
	mov	0, %g1
	mov	1, %g2
	cmp	%g1, 0
	be	.L11
	 ldd	[%i5+%lo(.LC1)], %f8
	cmp	%g1, 1
.L14:
	be	.L12
	 cmp	%g1, 2
	bne	.L6
	 cmp	%g1, 3
	ldd	[%i0+80], %f10
	add	%g1, 1, %g1
	faddd	%f8, %f10, %f8
	add	%g2, 1, %g2
.L13:
	cmp	%g1, 0
	bne	.L14
	 cmp	%g1, 1
.L11:
	ldd	[%i0], %f10
	b	.L4
	 faddd	%f8, %f10, %f8
.L12:
	ldd	[%i0+40], %f10
	faddd	%f8, %f10, %f8
.L4:
	cmp	%g2, 4
.L15:
	be	.L8
	 add	%g1, 1, %g1
	b	.L13
	 add	%g2, 1, %g2
.L6:
	bne	.L15
	 cmp	%g2, 4
	ldd	[%i0+120], %f10
	faddd	%f8, %f10, %f8
.L8:
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f8, [%fp-16]
	ldd	[%i0], %f10
	ldd	[%fp-8], %f14
	ldd	[%i5+%lo(.LC1)], %f8
	ldd	[%i0+40], %f12
	faddd	%f10, %f8, %f16
	ldd	[%i0+80], %f10
	faddd	%f16, %f12, %f12
	faddd	%f12, %f10, %f10
	std	%f14, [%fp-48]
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	std	%f10, [%fp-16]
	call	sqrt_ajit_asm_double, 0
	 std	%f8, [%fp-24]
	ldd	[%fp-8], %f12
	ldd	[%i0], %f16
	ldd	[%i0+40], %f10
	ldd	[%fp-24], %f8
	faddd	%f16, %f8, %f8
	faddd	%f8, %f10, %f10
	std	%f12, [%fp-40]
	std	%f10, [%fp-16]
	add	%fp, -16, %o0
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	ldd	[%fp-8], %f16
	ldd	[%i0+80], %f8
	std	%f16, [%fp-56]
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f8, [%fp-16]
	ldd	[%fp-8], %f10
	ldd	[%i0+120], %f8
	std	%f10, [%fp-32]
	std	%f8, [%fp-16]
	add	%fp, -16, %o0
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	ldd	[%fp-48], %f14
	ldd	[%fp-40], %f12
	ldd	[%fp-56], %f16
	ldd	[%fp-32], %f10
	sethi	%hi(NavprocData), %g1
	ldd	[%fp-8], %f8
	or	%g1, %lo(NavprocData), %g1
	std	%f14, [%g1+752]
	std	%f12, [%g1+760]
	std	%f16, [%g1+768]
	std	%f10, [%g1+776]
	std	%f8, [%g1+784]
	jmp	%i7+8
	 restore
	.size	NavComputeDOP.constprop.1, .-NavComputeDOP.constprop.1
	.section	.text.__enable_serial,"ax",@progbits
	.align 4
	.global __enable_serial
	.type	__enable_serial, #function
	.proc	04
__enable_serial:
	save	%sp, -96, %sp
	mov	0, %i0
	call	__ajit_write_serial_control_register__, 0
	 mov	3, %o0
	jmp	%i7+8
	 restore
	.size	__enable_serial, .-__enable_serial
	.section	.rodata.cst8
	.align 8
.LC2:
	.long	-1065402368
	.long	0
	.section	.text.Verify_NavIC_PVT_Data,"ax",@progbits
	.align 4
	.global Verify_NavIC_PVT_Data
	.type	Verify_NavIC_PVT_Data, #function
	.proc	04
Verify_NavIC_PVT_Data:
	save	%sp, -144, %sp
	mov	-1, %g1
	st	%g1, [%fp-48]
	st	%g1, [%fp-44]
	st	%g1, [%fp-40]
	st	%g1, [%fp-36]
	st	%g1, [%fp-32]
	st	%g1, [%fp-28]
	sethi	%hi(NavSubFrame1Data), %g3
	sethi	%hi(.LC2), %g1
	or	%g3, %lo(NavSubFrame1Data), %g2
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g2+8], %f10
	ldd	[%g3+%lo(NavSubFrame1Data)], %f12
	fcmpd	%f10, %f8
	nop
	fbe	.L18
	 mov	0, %g4
	fcmpd	%f12, %f8
	nop
	fbe	.L225
	 mov	1, %g4
.L18:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g2+16], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L256
	 ldd	[%g2+24], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L256:
	fcmpd	%f8, %f10
	nop
	fbne	.L257
	 ldd	[%g2+32], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L257:
	fcmpd	%f8, %f10
	nop
	fbne	.L258
	 ldd	[%g2+40], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L258:
	fcmpd	%f8, %f10
	nop
	fbne	.L259
	 ldd	[%g2+48], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L259:
	fcmpd	%f8, %f10
	nop
	fbne	.L260
	 ldd	[%g2+56], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L260:
	fcmpd	%f8, %f10
	nop
	fbne	.L261
	 ldd	[%g2+64], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L261:
	fcmpd	%f8, %f10
	nop
	fbne	.L262
	 ldd	[%g2+72], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L262:
	fcmpd	%f8, %f10
	nop
	fbne	.L263
	 ldd	[%g2+80], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L263:
	fcmpd	%f8, %f10
	nop
	fbne	.L264
	 ldd	[%g2+88], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L264:
	fcmpd	%f8, %f10
	nop
	fbne	.L265
	 ldd	[%g2+96], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L265:
	fcmpd	%f8, %f10
	nop
	fbne	.L266
	 ldd	[%g2+104], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L266:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L31
	 mov	0, %g4
.L31:
	ld	[%g2+112], %g3
	xor	%g3, 1, %g3
	ld	[%g2+128], %f8
	subcc	%g0, %g3, %g0
	ld	[%g2+116], %g3
	xor	%g3, 1, %g3
	subx	%g0, 0, %i5
	fitod	%f8, %f10
	and	%g4, %i5, %g4
	subcc	%g0, %g3, %g0
	ldd	[%g1+%lo(.LC2)], %f8
	subx	%g0, 0, %g3
	fcmpd	%f10, %f8
	nop
	fbne	.L34
	 and	%g4, %g3, %g4
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f8
.L34:
	ld	[%g2+132], %f12
	fitod	%f12, %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L35
	 mov	0, %g4
.L35:
	sethi	%hi(NavSubFrame2Data), %g3
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g3+%lo(NavSubFrame2Data)], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L267
	 or	%g3, %lo(NavSubFrame2Data), %g3
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L267:
	ldd	[%g3+8], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L268
	 ldd	[%g3+16], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L268:
	fcmpd	%f8, %f10
	nop
	fbne	.L269
	 ldd	[%g3+24], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L269:
	fcmpd	%f8, %f10
	nop
	fbne	.L270
	 ldd	[%g3+32], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L270:
	fcmpd	%f8, %f10
	nop
	fbne	.L271
	 ldd	[%g3+40], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L271:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L41
	 mov	0, %g4
.L41:
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g3+48], %f10
	fcmpd	%f10, %f8
	nop
	fbe	.L359
	 mov	0, %o4
	ldd	[%g3+56], %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L272
	 ldd	[%g2+152], %f10
	cmp	%g4, 1
	bne,a	.L272
	 ldd	[%g2+152], %f10
	st	%g0, [%fp-48]
	mov	1, %o4
	ldd	[%g1+%lo(.LC2)], %f8
.L359:
	ldd	[%g2+152], %f10
.L272:
	ldd	[%g2+144], %f12
	fcmpd	%f10, %f8
	nop
	fbe	.L43
	 mov	0, %g4
	fcmpd	%f12, %f8
	nop
	fbe	.L226
	 mov	1, %g4
.L43:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g2+160], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L273
	 ldd	[%g2+168], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L273:
	fcmpd	%f8, %f10
	nop
	fbne	.L274
	 ldd	[%g2+176], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L274:
	fcmpd	%f8, %f10
	nop
	fbne	.L275
	 ldd	[%g2+184], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L275:
	fcmpd	%f8, %f10
	nop
	fbne	.L276
	 ldd	[%g2+192], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L276:
	fcmpd	%f8, %f10
	nop
	fbne	.L277
	 ldd	[%g2+200], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L277:
	fcmpd	%f8, %f10
	nop
	fbne	.L278
	 ldd	[%g2+208], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L278:
	fcmpd	%f8, %f10
	nop
	fbne	.L279
	 ldd	[%g2+216], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L279:
	fcmpd	%f8, %f10
	nop
	fbne	.L280
	 ldd	[%g2+224], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L280:
	fcmpd	%f8, %f10
	nop
	fbne	.L281
	 ldd	[%g2+232], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L281:
	fcmpd	%f8, %f10
	nop
	fbne	.L282
	 ldd	[%g2+240], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L282:
	fcmpd	%f8, %f10
	nop
	fbne	.L283
	 ldd	[%g2+248], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L283:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L56
	 mov	0, %g4
.L56:
	ld	[%g2+256], %i5
	xor	%i5, 1, %i5
	ld	[%g2+272], %f8
	subcc	%g0, %i5, %g0
	ld	[%g2+260], %i5
	xor	%i5, 1, %i5
	subx	%g0, 0, %i4
	fitod	%f8, %f10
	and	%g4, %i4, %g4
	subcc	%g0, %i5, %g0
	ldd	[%g1+%lo(.LC2)], %f8
	subx	%g0, 0, %i5
	fcmpd	%f10, %f8
	nop
	fbne	.L59
	 and	%g4, %i5, %g4
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f8
.L59:
	ld	[%g2+276], %f12
	fitod	%f12, %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L60
	 mov	0, %g4
.L60:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g3+80], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L284
	 ldd	[%g3+88], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L284:
	fcmpd	%f8, %f10
	nop
	fbne	.L285
	 ldd	[%g3+96], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L285:
	fcmpd	%f8, %f10
	nop
	fbne	.L286
	 ldd	[%g3+104], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L286:
	fcmpd	%f8, %f10
	nop
	fbne	.L287
	 ldd	[%g3+112], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L287:
	fcmpd	%f8, %f10
	nop
	fbne	.L288
	 ldd	[%g3+120], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L288:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L66
	 mov	0, %g4
.L66:
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g3+128], %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L289
	 ldd	[%g2+296], %f10
	ldd	[%g3+136], %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L289
	 ldd	[%g2+296], %f10
	cmp	%g4, 1
	bne,a	.L289
	 ldd	[%g2+296], %f10
	st	%g4, [%fp-44]
	add	%o4, 1, %o4
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g2+296], %f10
.L289:
	ldd	[%g2+288], %f12
	fcmpd	%f10, %f8
	nop
	fbe	.L68
	 mov	0, %g4
	fcmpd	%f12, %f8
	nop
	fbe	.L227
	 mov	1, %g4
.L68:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g2+304], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L290
	 ldd	[%g2+312], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L290:
	fcmpd	%f8, %f10
	nop
	fbne	.L291
	 ldd	[%g2+320], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L291:
	fcmpd	%f8, %f10
	nop
	fbne	.L292
	 ldd	[%g2+328], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L292:
	fcmpd	%f8, %f10
	nop
	fbne	.L293
	 ldd	[%g2+336], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L293:
	fcmpd	%f8, %f10
	nop
	fbne	.L294
	 ldd	[%g2+344], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L294:
	fcmpd	%f8, %f10
	nop
	fbne	.L295
	 ldd	[%g2+352], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L295:
	fcmpd	%f8, %f10
	nop
	fbne	.L296
	 ldd	[%g2+360], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L296:
	fcmpd	%f8, %f10
	nop
	fbne	.L297
	 ldd	[%g2+368], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L297:
	fcmpd	%f8, %f10
	nop
	fbne	.L298
	 ldd	[%g2+376], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L298:
	fcmpd	%f8, %f10
	nop
	fbne	.L299
	 ldd	[%g2+384], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L299:
	fcmpd	%f8, %f10
	nop
	fbne	.L300
	 ldd	[%g2+392], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L300:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L81
	 mov	0, %g4
.L81:
	ld	[%g2+400], %i5
	xor	%i5, 1, %i5
	ld	[%g2+416], %f8
	subcc	%g0, %i5, %g0
	ld	[%g2+404], %i5
	xor	%i5, 1, %i5
	subx	%g0, 0, %i4
	fitod	%f8, %f10
	and	%g4, %i4, %g4
	subcc	%g0, %i5, %g0
	ldd	[%g1+%lo(.LC2)], %f8
	subx	%g0, 0, %i5
	fcmpd	%f10, %f8
	nop
	fbne	.L84
	 and	%g4, %i5, %g4
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f8
.L84:
	ld	[%g2+420], %f12
	fitod	%f12, %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L85
	 mov	0, %g4
.L85:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g3+160], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L301
	 ldd	[%g3+168], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L301:
	fcmpd	%f8, %f10
	nop
	fbne	.L302
	 ldd	[%g3+176], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L302:
	fcmpd	%f8, %f10
	nop
	fbne	.L303
	 ldd	[%g3+184], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L303:
	fcmpd	%f8, %f10
	nop
	fbne	.L304
	 ldd	[%g3+192], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L304:
	fcmpd	%f8, %f10
	nop
	fbne	.L305
	 ldd	[%g3+200], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L305:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L91
	 mov	0, %g4
.L91:
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g3+208], %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L306
	 ldd	[%g2+440], %f10
	ldd	[%g3+216], %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L306
	 ldd	[%g2+440], %f10
	cmp	%g4, 1
	bne,a	.L306
	 ldd	[%g2+440], %f10
	mov	2, %g4
	add	%o4, 1, %o4
	st	%g4, [%fp-40]
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g2+440], %f10
.L306:
	ldd	[%g2+432], %f12
	fcmpd	%f10, %f8
	nop
	fbe	.L93
	 mov	0, %g4
	fcmpd	%f12, %f8
	nop
	fbe	.L228
	 mov	1, %g4
.L93:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g2+448], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L307
	 ldd	[%g2+456], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L307:
	fcmpd	%f8, %f10
	nop
	fbne	.L308
	 ldd	[%g2+464], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L308:
	fcmpd	%f8, %f10
	nop
	fbne	.L309
	 ldd	[%g2+472], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L309:
	fcmpd	%f8, %f10
	nop
	fbne	.L310
	 ldd	[%g2+480], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L310:
	fcmpd	%f8, %f10
	nop
	fbne	.L311
	 ldd	[%g2+488], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L311:
	fcmpd	%f8, %f10
	nop
	fbne	.L312
	 ldd	[%g2+496], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L312:
	fcmpd	%f8, %f10
	nop
	fbne	.L313
	 ldd	[%g2+504], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L313:
	fcmpd	%f8, %f10
	nop
	fbne	.L314
	 ldd	[%g2+512], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L314:
	fcmpd	%f8, %f10
	nop
	fbne	.L315
	 ldd	[%g2+520], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L315:
	fcmpd	%f8, %f10
	nop
	fbne	.L316
	 ldd	[%g2+528], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L316:
	fcmpd	%f8, %f10
	nop
	fbne	.L317
	 ldd	[%g2+536], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L317:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L106
	 mov	0, %g4
.L106:
	ld	[%g2+544], %i5
	xor	%i5, 1, %i5
	ld	[%g2+560], %f8
	subcc	%g0, %i5, %g0
	ld	[%g2+548], %i5
	xor	%i5, 1, %i5
	subx	%g0, 0, %i4
	fitod	%f8, %f10
	and	%g4, %i4, %g4
	subcc	%g0, %i5, %g0
	ldd	[%g1+%lo(.LC2)], %f8
	subx	%g0, 0, %i5
	fcmpd	%f10, %f8
	nop
	fbne	.L109
	 and	%g4, %i5, %g4
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f8
.L109:
	ld	[%g2+564], %f12
	fitod	%f12, %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L110
	 mov	0, %g4
.L110:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g3+240], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L318
	 ldd	[%g3+248], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L318:
	fcmpd	%f8, %f10
	nop
	fbne	.L319
	 ldd	[%g3+256], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L319:
	fcmpd	%f8, %f10
	nop
	fbne	.L320
	 ldd	[%g3+264], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L320:
	fcmpd	%f8, %f10
	nop
	fbne	.L321
	 ldd	[%g3+272], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L321:
	fcmpd	%f8, %f10
	nop
	fbne	.L322
	 ldd	[%g3+280], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L322:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L116
	 mov	0, %g4
.L116:
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g3+288], %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L323
	 ldd	[%g2+584], %f10
	ldd	[%g3+296], %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L323
	 ldd	[%g2+584], %f10
	cmp	%g4, 1
	bne,a	.L323
	 ldd	[%g2+584], %f10
	mov	3, %g4
	add	%o4, 1, %o4
	st	%g4, [%fp-36]
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g2+584], %f10
.L323:
	ldd	[%g2+576], %f12
	fcmpd	%f10, %f8
	nop
	fbe	.L118
	 mov	0, %g4
	fcmpd	%f12, %f8
	nop
	fbe	.L229
	 mov	1, %g4
.L118:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g2+592], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L324
	 ldd	[%g2+600], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L324:
	fcmpd	%f8, %f10
	nop
	fbne	.L325
	 ldd	[%g2+608], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L325:
	fcmpd	%f8, %f10
	nop
	fbne	.L326
	 ldd	[%g2+616], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L326:
	fcmpd	%f8, %f10
	nop
	fbne	.L327
	 ldd	[%g2+624], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L327:
	fcmpd	%f8, %f10
	nop
	fbne	.L328
	 ldd	[%g2+632], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L328:
	fcmpd	%f8, %f10
	nop
	fbne	.L329
	 ldd	[%g2+640], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L329:
	fcmpd	%f8, %f10
	nop
	fbne	.L330
	 ldd	[%g2+648], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L330:
	fcmpd	%f8, %f10
	nop
	fbne	.L331
	 ldd	[%g2+656], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L331:
	fcmpd	%f8, %f10
	nop
	fbne	.L332
	 ldd	[%g2+664], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L332:
	fcmpd	%f8, %f10
	nop
	fbne	.L333
	 ldd	[%g2+672], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L333:
	fcmpd	%f8, %f10
	nop
	fbne	.L334
	 ldd	[%g2+680], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L334:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L131
	 mov	0, %g4
.L131:
	ld	[%g2+688], %i5
	xor	%i5, 1, %i5
	ld	[%g2+704], %f8
	subcc	%g0, %i5, %g0
	ld	[%g2+692], %i5
	xor	%i5, 1, %i5
	subx	%g0, 0, %i4
	fitod	%f8, %f10
	and	%g4, %i4, %g4
	subcc	%g0, %i5, %g0
	ldd	[%g1+%lo(.LC2)], %f8
	subx	%g0, 0, %i5
	fcmpd	%f10, %f8
	nop
	fbne	.L134
	 and	%g4, %i5, %g4
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f8
.L134:
	ld	[%g2+708], %f12
	fitod	%f12, %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L135
	 mov	0, %g4
.L135:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g3+320], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L335
	 ldd	[%g3+328], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L335:
	fcmpd	%f8, %f10
	nop
	fbne	.L336
	 ldd	[%g3+336], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L336:
	fcmpd	%f8, %f10
	nop
	fbne	.L337
	 ldd	[%g3+344], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L337:
	fcmpd	%f8, %f10
	nop
	fbne	.L338
	 ldd	[%g3+352], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L338:
	fcmpd	%f8, %f10
	nop
	fbne	.L339
	 ldd	[%g3+360], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L339:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L141
	 mov	0, %g4
.L141:
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g3+368], %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L340
	 ldd	[%g2+728], %f10
	ldd	[%g3+376], %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L340
	 ldd	[%g2+728], %f10
	cmp	%g4, 1
	bne,a	.L340
	 ldd	[%g2+728], %f10
	mov	4, %g4
	add	%o4, 1, %o4
	st	%g4, [%fp-32]
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g2+728], %f10
.L340:
	ldd	[%g2+720], %f12
	fcmpd	%f10, %f8
	nop
	fbe	.L143
	 mov	0, %g4
	fcmpd	%f12, %f8
	nop
	fbe	.L230
	 mov	1, %g4
.L143:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g2+736], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L341
	 ldd	[%g2+744], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L341:
	fcmpd	%f8, %f10
	nop
	fbne	.L342
	 ldd	[%g2+752], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L342:
	fcmpd	%f8, %f10
	nop
	fbne	.L343
	 ldd	[%g2+760], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L343:
	fcmpd	%f8, %f10
	nop
	fbne	.L344
	 ldd	[%g2+768], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L344:
	fcmpd	%f8, %f10
	nop
	fbne	.L345
	 ldd	[%g2+776], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L345:
	fcmpd	%f8, %f10
	nop
	fbne	.L346
	 ldd	[%g2+784], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L346:
	fcmpd	%f8, %f10
	nop
	fbne	.L347
	 ldd	[%g2+792], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L347:
	fcmpd	%f8, %f10
	nop
	fbne	.L348
	 ldd	[%g2+800], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L348:
	fcmpd	%f8, %f10
	nop
	fbne	.L349
	 ldd	[%g2+808], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L349:
	fcmpd	%f8, %f10
	nop
	fbne	.L350
	 ldd	[%g2+816], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L350:
	fcmpd	%f8, %f10
	nop
	fbne	.L351
	 ldd	[%g2+824], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L351:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L156
	 mov	0, %g4
.L156:
	ld	[%g2+832], %i5
	xor	%i5, 1, %i5
	ld	[%g2+848], %f8
	subcc	%g0, %i5, %g0
	ld	[%g2+836], %i5
	xor	%i5, 1, %i5
	subx	%g0, 0, %i4
	fitod	%f8, %f10
	and	%g4, %i4, %g4
	subcc	%g0, %i5, %g0
	ldd	[%g1+%lo(.LC2)], %f8
	subx	%g0, 0, %i5
	fcmpd	%f10, %f8
	nop
	fbne	.L159
	 and	%g4, %i5, %g4
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f8
.L159:
	ld	[%g2+852], %f10
	fitod	%f10, %f10
	fcmpd	%f10, %f8
	nop
	fbe,a	.L160
	 mov	0, %g4
.L160:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g3+400], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L352
	 ldd	[%g3+408], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L352:
	fcmpd	%f8, %f10
	nop
	fbne	.L353
	 ldd	[%g3+416], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L353:
	fcmpd	%f8, %f10
	nop
	fbne	.L354
	 ldd	[%g3+424], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L354:
	fcmpd	%f8, %f10
	nop
	fbne	.L355
	 ldd	[%g3+432], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L355:
	fcmpd	%f8, %f10
	nop
	fbne	.L356
	 ldd	[%g3+440], %f8
	mov	0, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L356:
	fcmpd	%f8, %f10
	nop
	fbe,a	.L166
	 mov	0, %g4
.L166:
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g3+448], %f10
	fcmpd	%f10, %f8
	nop
	fbne,a	.L231
	 ldd	[%g3+456], %f10
	cmp	%o4, 0
.L358:
	be,a	.L169
	 sethi	%hi(NavprocData+184), %g1
.L168:
	add	%i0, %i0, %i1
	sll	%o4, 2, %o4
	add	%i1, %i0, %i1
	mov	0, %g3
	mov	0, %i0
	add	%fp, -48, %o5
	sethi	%hi(Raw_PR_Delay), %o7
	add	%i1, %i1, %i1
	sethi	%hi(NavObsDat), %i2
	ld	[%o5+%g3], %g2
.L357:
	or	%o7, %lo(Raw_PR_Delay), %i3
	add	%i1, %g2, %g4
	or	%i2, %lo(NavObsDat), %i4
	sll	%g2, 3, %i5
	cmp	%g2, -1
	be	.L170
	 sll	%g4, 3, %g4
	ldd	[%i3+%g4], %f8
	ldd	[%g1+%lo(.LC2)], %f10
	fcmpd	%f8, %f10
	nop
	fbe	.L170
	 std	%f8, [%i4+%i5]
	sll	%i0, 2, %g4
	add	%i0, 1, %i0
	add	%fp, %g4, %g4
	st	%g2, [%g4-24]
.L170:
	add	%g3, 4, %g3
	cmp	%g3, %o4
	bne,a	.L357
	 ld	[%o5+%g3], %g2
	sethi	%hi(NavprocData), %g3
	or	%g3, %lo(NavprocData), %g3
	cmp	%i0, 0
	be	.L361
	 st	%i0, [%g3+184]
	sethi	%hi(NavUTCCorr), %g4
	ldd	[%g1+%lo(.LC2)], %f8
	or	%g4, %lo(NavUTCCorr), %g2
	ldd	[%g2+8], %f10
	fcmpd	%f10, %f8
	nop
	fbe	.L174
	 mov	1, %i5
	ldd	[%g4+%lo(NavUTCCorr)], %f10
	fcmpd	%f10, %f8
	nop
	fbne,a	.L174
	 mov	0, %i5
.L174:
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g2+16], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L232
	 mov	1, %g4
	ldd	[%g2+24], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L233
	 mov	1, %i5
.L179:
	ldd	[%g2+32], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L234
	 mov	1, %g4
.L181:
	ldd	[%g2+40], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L235
	 mov	1, %i5
.L183:
	ldd	[%g2+48], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L236
	 mov	1, %g4
.L185:
	ldd	[%g2+56], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L237
	 mov	1, %i5
.L187:
	ldd	[%g2+64], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L238
	 mov	1, %g4
.L189:
	ldd	[%g2+72], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L239
	 mov	1, %i5
.L191:
	ldd	[%g2+80], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L240
	 mov	1, %g4
.L193:
	ldd	[%g2+88], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L241
	 mov	1, %i5
.L195:
	ldd	[%g2+96], %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L242
	 mov	1, %g4
.L197:
	ldd	[%g1+%lo(.LC2)], %f8
	ldd	[%g2+104], %f10
	fcmpd	%f10, %f8
	nop
	fbe	.L198
	 ld	[%g3+152], %i3
	cmp	%g4, 1
.L245:
	be	.L199
	 sll	%i0, 2, %i4
	mov	0, %g1
	add	%fp, -24, %g2
.L200:
	add	%g3, %g1, %g4
	ld	[%g2+%g1], %i5
	add	%g1, 4, %g1
	cmp	%g1, %i4
	bne	.L200
	 st	%i5, [%g4+188]
	st	%i3, [%g3+152]
.L361:
	jmp	%i7+8
	 restore
.L169:
	st	%g0, [%g1+%lo(NavprocData+184)]
	jmp	%i7+8
	 restore %g0, 0, %o0
.L231:
	fcmpd	%f10, %f8
	nop
	fbe	.L358
	 cmp	%o4, 0
	cmp	%g4, 1
	bne	.L358
	 cmp	%o4, 0
	mov	5, %g2
	add	%o4, 1, %o4
	b	.L168
	 st	%g2, [%fp-28]
.L242:
	ldd	[%g1+%lo(.LC2)], %f8
.L246:
	ldd	[%g2+104], %f10
	mov	%i5, %g4
	fcmpd	%f10, %f8
	nop
	fbe	.L198
	 ld	[%g3+152], %i3
	b	.L245
	 cmp	%g4, 1
.L241:
	mov	%g4, %i5
	ldd	[%g1+%lo(.LC2)], %f10
.L247:
	ldd	[%g2+96], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L197
	 mov	1, %g4
	b	.L246
	 ldd	[%g1+%lo(.LC2)], %f8
.L240:
	mov	%i5, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L248:
	ldd	[%g2+88], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L195
	 mov	1, %i5
	b	.L247
	 mov	%g4, %i5
.L239:
	mov	%g4, %i5
	ldd	[%g1+%lo(.LC2)], %f10
.L249:
	ldd	[%g2+80], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L193
	 mov	1, %g4
	b	.L248
	 mov	%i5, %g4
.L238:
	mov	%i5, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L250:
	ldd	[%g2+72], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L191
	 mov	1, %i5
	b	.L249
	 mov	%g4, %i5
.L237:
	mov	%g4, %i5
	ldd	[%g1+%lo(.LC2)], %f10
.L251:
	ldd	[%g2+64], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L189
	 mov	1, %g4
	b	.L250
	 mov	%i5, %g4
.L236:
	mov	%i5, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L252:
	ldd	[%g2+56], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L187
	 mov	1, %i5
	b	.L251
	 mov	%g4, %i5
.L235:
	mov	%g4, %i5
	ldd	[%g1+%lo(.LC2)], %f10
.L253:
	ldd	[%g2+48], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L185
	 mov	1, %g4
	b	.L252
	 mov	%i5, %g4
.L234:
	mov	%i5, %g4
	ldd	[%g1+%lo(.LC2)], %f10
.L254:
	ldd	[%g2+40], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L183
	 mov	1, %i5
	b	.L253
	 mov	%g4, %i5
.L233:
	mov	%g4, %i5
	ldd	[%g1+%lo(.LC2)], %f10
.L255:
	ldd	[%g2+32], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L181
	 mov	1, %g4
	b	.L254
	 mov	%i5, %g4
.L232:
	mov	%i5, %g4
	ldd	[%g1+%lo(.LC2)], %f10
	ldd	[%g2+24], %f8
	fcmpd	%f8, %f10
	nop
	fbe	.L179
	 mov	1, %i5
	b	.L255
	 mov	%g4, %i5
.L198:
	sll	%i0, 2, %i4
	mov	0, %g1
	add	%fp, -24, %g2
.L203:
	add	%g3, %g1, %g4
	ld	[%g2+%g1], %i5
	add	%g1, 4, %g1
	cmp	%g1, %i4
	bne	.L203
	 st	%i5, [%g4+188]
	mov	1, %i3
.L244:
	st	%i3, [%g3+152]
	jmp	%i7+8
	 restore
.L228:
	b	.L93
	 mov	0, %g4
.L230:
	b	.L143
	 mov	0, %g4
.L229:
	b	.L118
	 mov	0, %g4
.L227:
	b	.L68
	 mov	0, %g4
.L226:
	b	.L43
	 mov	0, %g4
.L225:
	b	.L18
	 mov	0, %g4
.L199:
	sll	%i0, 2, %g4
	mov	0, %g1
	add	%fp, -24, %g2
.L202:
	add	%g3, %g1, %i5
	ld	[%g2+%g1], %i4
	add	%g1, 4, %g1
	cmp	%g1, %g4
	bne	.L202
	 st	%i4, [%i5+188]
	b	.L244
	 mov	1, %i3
	.size	Verify_NavIC_PVT_Data, .-Verify_NavIC_PVT_Data
	.section	.rodata.cst8
	.align 8
.LC3:
	.long	-1065402368
	.long	0
	.section	.text.NavIC_Init_Processed_Data,"ax",@progbits
	.align 4
	.global NavIC_Init_Processed_Data
	.type	NavIC_Init_Processed_Data, #function
	.proc	020
NavIC_Init_Processed_Data:
	sethi	%hi(.LC3), %o5
	mov	-500, %g2
	ldd	[%o5+%lo(.LC3)], %f8
	sethi	%hi(NavObsDat), %g4
	sethi	%hi(NavprocData), %g1
	or	%g4, %lo(NavObsDat), %g3
	or	%g1, %lo(NavprocData), %g1
	std	%f8, [%g3+8]
	std	%f8, [%g3+16]
	std	%f8, [%g3+24]
	std	%f8, [%g3+32]
	std	%f8, [%g3+40]
	st	%g2, [%g1+156]
	st	%g2, [%g1+160]
	st	%g2, [%g1+164]
	st	%g2, [%g1+168]
	st	%g2, [%g1+172]
	st	%g2, [%g1+176]
	mov	1, %o5
	std	%f8, [%g1+8]
	st	%o5, [%g1+152]
	std	%f8, [%g4+%lo(NavObsDat)]
	std	%f8, [%g1+56]
	std	%f8, [%g1+16]
	std	%f8, [%g1+64]
	std	%f8, [%g1+24]
	std	%f8, [%g1+72]
	std	%f8, [%g1+32]
	std	%f8, [%g1+80]
	std	%f8, [%g1+40]
	std	%f8, [%g1+88]
	std	%f8, [%g1+48]
	std	%f8, [%g1+96]
	std	%f8, [%g1+960]
	std	%f8, [%g1+968]
	std	%f8, [%g1+976]
	std	%f8, [%g1+984]
	std	%f8, [%g1+992]
	std	%f8, [%g1+1000]
	std	%f8, [%g1+1008]
	st	%g2, [%g1+180]
	mov	-50, %g3
	std	%f8, [%g1+216]
	std	%g2, [%g1+184]
	st	%g3, [%g1+192]
	st	%g3, [%g1+196]
	st	%g3, [%g1+200]
	st	%g3, [%g1+204]
	st	%g3, [%g1+208]
	std	%f8, [%g1+224]
	std	%f8, [%g1+232]
	std	%f8, [%g1+240]
	std	%f8, [%g1+248]
	std	%f8, [%g1+256]
	std	%f8, [%g1+264]
	std	%f8, [%g1+272]
	std	%f8, [%g1+280]
	std	%f8, [%g1+288]
	std	%f8, [%g1+296]
	std	%f8, [%g1+304]
	std	%f8, [%g1+312]
	std	%f8, [%g1+320]
	std	%f8, [%g1+328]
	std	%f8, [%g1+336]
	std	%f8, [%g1+344]
	std	%f8, [%g1+352]
	std	%f8, [%g1+360]
	std	%f8, [%g1+368]
	std	%f8, [%g1+376]
	std	%f8, [%g1+384]
	std	%f8, [%g1+392]
	std	%f8, [%g1+400]
	std	%f8, [%g1+408]
	std	%f8, [%g1+416]
	std	%f8, [%g1+424]
	std	%f8, [%g1+432]
	mov	78, %g2
	std	%f8, [%g1+440]
	std	%f8, [%g1+448]
	std	%f8, [%g1+456]
	std	%f8, [%g1+464]
	std	%f8, [%g1+472]
	std	%f8, [%g1+480]
	std	%f8, [%g1+488]
	std	%f8, [%g1+496]
	std	%f8, [%g1+504]
	std	%f8, [%g1+512]
	std	%f8, [%g1+520]
	std	%f8, [%g1+528]
	std	%f8, [%g1+536]
	std	%f8, [%g1+544]
	std	%f8, [%g1+552]
	std	%f8, [%g1+560]
	std	%f8, [%g1+568]
	std	%f8, [%g1+576]
	std	%f8, [%g1+584]
	std	%f8, [%g1+592]
	std	%f8, [%g1+600]
	std	%f8, [%g1+648]
	std	%f8, [%g1+608]
	std	%f8, [%g1+656]
	std	%f8, [%g1+616]
	std	%f8, [%g1+664]
	std	%f8, [%g1+624]
	std	%f8, [%g1+672]
	std	%f8, [%g1+632]
	std	%f8, [%g1+680]
	std	%f8, [%g1+640]
	std	%f8, [%g1+688]
	std	%f8, [%g1+696]
	std	%f8, [%g1+704]
	stb	%g2, [%g1+744]
	std	%f8, [%g1+712]
	mov	69, %g2
	std	%f8, [%g1+792]
	std	%f8, [%g1+800]
	std	%f8, [%g1+808]
	std	%f8, [%g1+816]
	std	%f8, [%g1+824]
	std	%f8, [%g1+832]
	std	%f8, [%g1+720]
	std	%f8, [%g1+728]
	std	%f8, [%g1+736]
	stb	%g2, [%g1+745]
	std	%f8, [%g1+936]
	std	%f8, [%g1+944]
	std	%f8, [%g1+952]
	std	%f8, [%g1+752]
	std	%f8, [%g1+760]
	std	%f8, [%g1+768]
	std	%f8, [%g1+776]
	std	%f8, [%g1+784]
	std	%f8, [%g1+840]
	std	%f8, [%g1+888]
	std	%f8, [%g1+848]
	std	%f8, [%g1+896]
	std	%f8, [%g1+856]
	std	%f8, [%g1+904]
	std	%f8, [%g1+864]
	std	%f8, [%g1+912]
	std	%f8, [%g1+872]
	std	%f8, [%g1+920]
	std	%f8, [%g1+880]
	jmp	%o7+8
	 std	%f8, [%g1+928]
	.size	NavIC_Init_Processed_Data, .-NavIC_Init_Processed_Data
	.section	.rodata.cst8
	.align 8
.LC4:
	.long	-1065402368
	.long	0
	.align 8
.LC5:
	.long	1073741824
	.long	0
	.section	.text.NavIC_Compute_Sat_Rx_Range,"ax",@progbits
	.align 4
	.global NavIC_Compute_Sat_Rx_Range
	.type	NavIC_Compute_Sat_Rx_Range, #function
	.proc	020
NavIC_Compute_Sat_Rx_Range:
	save	%sp, -168, %sp
	sethi	%hi(NavprocData), %i5
	add	%i0, %i0, %g2
	or	%i5, %lo(NavprocData), %i5
	add	%g2, %i0, %g2
	sethi	%hi(.LC4), %i4
	sll	%g2, 3, %g3
	ldd	[%i4+%lo(.LC4)], %f8
	add	%i5, %g3, %g3
	mov	1, %g1
	ldd	[%g3+224], %f18
	fcmpd	%f18, %f8
	nop
	fbe	.L364
	 ldd	[%g3+216], %f20
	fcmpd	%f20, %f8
	nop
	fbne,a	.L364
	 mov	0, %g1
.L364:
	sll	%g2, 3, %g2
	ldd	[%i4+%lo(.LC4)], %f8
	add	%i5, %g2, %g2
	ldd	[%g2+232], %f12
	fcmpd	%f12, %f8
	nop
	fbne	.L378
	 ldd	[%i5+696], %f16
	mov	1, %g1
	ldd	[%i4+%lo(.LC4)], %f8
.L378:
	fcmpd	%f16, %f8
	nop
	fbne	.L379
	 ldd	[%i5+704], %f14
	mov	1, %g1
	ldd	[%i4+%lo(.LC4)], %f8
.L379:
	fcmpd	%f14, %f8
	nop
	fbne,a	.L377
	 ldd	[%i5+712], %f10
.L368:
	ldd	[%i4+%lo(.LC4)], %f8
.L380:
	add	%i0, 111, %g1
	add	%i0, 105, %i0
	sll	%g1, 3, %g1
	sll	%i0, 3, %i0
	std	%f8, [%i5+%g1]
	std	%f8, [%i5+%i0]
	jmp	%i7+8
	 restore
.L377:
	fcmpd	%f10, %f8
	nop
	fbe,a	.L380
	 ldd	[%i4+%lo(.LC4)], %f8
	cmp	%g1, 1
	be	.L368
	 sethi	%hi(.LC5), %i3
	fsubd	%f20, %f16, %f22
	std	%f8, [%fp-24]
	std	%f22, [%fp-72]
	std	%f10, [%fp-32]
	std	%f12, [%fp-40]
	ldd	[%fp-72], %o0
	ldd	[%i3+%lo(.LC5)], %o2
	std	%f14, [%fp-48]
	call	pow, 0
	 std	%f18, [%fp-64]
	ldd	[%fp-48], %f14
	ldd	[%fp-64], %f18
	fmovs	%f0, %f16
	fsubd	%f18, %f14, %f20
	fmovs	%f1, %f17
	std	%f20, [%fp-72]
	ldd	[%i3+%lo(.LC5)], %o2
	ldd	[%fp-72], %o0
	call	pow, 0
	 std	%f16, [%fp-56]
	ldd	[%fp-32], %f10
	ldd	[%fp-40], %f12
	ldd	[%fp-56], %f16
	fsubd	%f12, %f10, %f22
	faddd	%f16, %f0, %f16
	std	%f22, [%fp-72]
	ldd	[%i3+%lo(.LC5)], %o2
	ldd	[%fp-72], %o0
	call	pow, 0
	 std	%f16, [%fp-56]
	ldd	[%fp-56], %f16
	faddd	%f16, %f0, %f0
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-16]
	ldd	[%fp-8], %f10
	add	%i0, 105, %g1
	sll	%g1, 3, %g1
	std	%f10, [%i5+%g1]
	ldd	[%fp-24], %f8
	add	%i0, 75, %g1
	sll	%g1, 3, %g1
	ldd	[%i5+%g1], %f12
	fcmpd	%f12, %f8
	nop
	fbne,a	.L371
	 faddd	%f10, %f12, %f10
.L371:
	add	%i0, 81, %g1
	ldd	[%i4+%lo(.LC4)], %f12
	sll	%g1, 3, %g1
	ldd	[%i5+%g1], %f8
	fcmpd	%f8, %f12
	nop
	fbne,a	.L372
	 faddd	%f10, %f8, %f10
.L372:
	add	%i0, 111, %i0
	sll	%i0, 3, %i0
	std	%f10, [%i5+%i0]
	jmp	%i7+8
	 restore
	.size	NavIC_Compute_Sat_Rx_Range, .-NavIC_Compute_Sat_Rx_Range
	.section	.rodata.cst8
	.align 8
.LC6:
	.long	1076101120
	.long	0
	.align 8
.LC7:
	.long	1076625408
	.long	0
	.align 8
.LC8:
	.long	1074783062
	.long	2531625523
	.align 8
.LC9:
	.long	-1071382528
	.long	0
	.align 8
.LC10:
	.long	-1072577169
	.long	1563991519
	.align 8
.LC11:
	.long	-1071513600
	.long	0
	.align 8
.LC12:
	.long	1091728640
	.long	0
	.align 8
.LC13:
	.long	1092777216
	.long	0
	.align 8
.LC14:
	.long	-1055755008
	.long	0
	.align 8
.LC15:
	.long	1073741824
	.long	0
	.align 8
.LC16:
	.long	1044740494
	.long	3794832442
	.section	.text.NavIC_TOWC_Correction,"ax",@progbits
	.align 4
	.global NavIC_TOWC_Correction
	.type	NavIC_TOWC_Correction, #function
	.proc	020
NavIC_TOWC_Correction:
	save	%sp, -200, %sp
	sethi	%hi(.LC7), %g1
	sethi	%hi(.LC6), %i5
	ldd	[%g1+%lo(.LC7)], %o2
	call	pow, 0
	 ldd	[%i5+%lo(.LC6)], %o0
	sethi	%hi(.LC9), %g1
	ldd	[%g1+%lo(.LC9)], %o2
	sethi	%hi(.LC8), %g1
	ldd	[%g1+%lo(.LC8)], %f8
	fmuld	%f0, %f8, %f0
	ldd	[%i5+%lo(.LC6)], %o0
	call	pow, 0
	 std	%f0, [%fp-24]
	sethi	%hi(.LC11), %g1
	ldd	[%g1+%lo(.LC11)], %o2
	sethi	%hi(.LC10), %g1
	ldd	[%g1+%lo(.LC10)], %f8
	fmuld	%f0, %f8, %f0
	ldd	[%i5+%lo(.LC6)], %o0
	call	pow, 0
	 std	%f0, [%fp-56]
	sll	%i0, 4, %i5
	std	%i2, [%fp-96]
	st	%i1, [%fp-100]
	ldd	[%fp-96], %f10
	ld	[%fp-100], %f12
	fmuld	%f0, %f10, %f0
	fitod	%f12, %f8
	sethi	%hi(NavSubFrame2Data), %i3
	fsubd	%f8, %f0, %f14
	or	%i3, %lo(NavSubFrame2Data), %i3
	sll	%i0, 6, %i4
	std	%f14, [%fp-40]
	add	%i5, %i4, %i4
	add	%i3, %i4, %g1
	ldd	[%g1+8], %f8
	sethi	%hi(.LC12), %g1
	fsubd	%f14, %f8, %f8
	ldd	[%g1+%lo(.LC12)], %f10
	fcmped	%f8, %f10
	nop
	fbul	.L390
	 nop
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f10
	fsubd	%f8, %f10, %f8
.L384:
	add	%i3, %i4, %g1
	sethi	%hi(.LC15), %l1
	ldd	[%g1+24], %o0
	ldd	[%l1+%lo(.LC15)], %o2
	call	pow, 0
	 std	%f8, [%fp-64]
	ldd	[%fp-24], %f12
	fdivd	%f12, %f0, %f10
	std	%f0, [%fp-48]
	std	%f10, [%fp-16]
	add	%fp, -16, %o0
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	ldd	[%fp-8], %f10
	ldd	[%fp-48], %f12
	fdivd	%f10, %f12, %f14
	sll	%i0, 7, %i1
	sethi	%hi(NavSubFrame1Data), %l0
	add	%i5, %i1, %i1
	or	%l0, %lo(NavSubFrame1Data), %l0
	ldd	[%i3+%i4], %f10
	add	%l0, %i1, %g1
	ldd	[%fp-64], %f8
	ldd	[%g1+40], %f12
	sethi	%hi(.LC16), %i2
	faddd	%f14, %f12, %f12
	or	%i2, %lo(.LC16), %i2
	fmuld	%f12, %f8, %f8
	faddd	%f8, %f10, %f14
	std	%f14, [%fp-32]
	std	%f14, [%fp-24]
	add	%i3, %i4, %i5
.L391:
	ldd	[%i5+16], %f8
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f8, [%fp-64]
	ldd	[%fp-64], %f8
	ldd	[%fp-24], %f10
	fmuld	%f8, %f0, %f0
	ldd	[%fp-32], %f8
	faddd	%f0, %f8, %f0
	fsubd	%f0, %f10, %f10
	std	%f0, [%fp-24]
	std	%f10, [%fp-96]
	call	fabs, 0
	 ldd	[%fp-96], %o0
	ldd	[%i2], %f8
	fcmped	%f0, %f8
	nop
	fbg,a	.L391
	 add	%i3, %i4, %i5
	ldd	[%i5+16], %f10
	ldd	[%fp-56], %f12
	ldd	[%fp-48], %f14
	fmuld	%f12, %f10, %f10
	fmuld	%f10, %f14, %f10
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f10, [%fp-72]
	add	%l0, %i1, %i5
	ldd	[%fp-40], %f12
	ldd	[%i5+8], %f14
	ldd	[%i5+24], %f8
	ldd	[%fp-72], %f10
	fsubd	%f12, %f8, %f8
	fmuld	%f10, %f0, %f10
	fmuld	%f8, %f14, %f12
	ldd	[%l0+%i1], %f16
	ldd	[%i5+16], %f14
	faddd	%f12, %f16, %f12
	std	%f8, [%fp-96]
	std	%f10, [%fp-72]
	std	%f12, [%fp-80]
	std	%f14, [%fp-88]
	ldd	[%fp-96], %o0
	call	pow, 0
	 ldd	[%l1+%lo(.LC15)], %o2
	ldd	[%fp-88], %f14
	ldd	[%fp-80], %f12
	fmuld	%f14, %f0, %f0
	ldd	[%fp-72], %f10
	add	%i0, 1, %i0
	ldd	[%i5+32], %f8
	sll	%i0, 3, %i0
	faddd	%f12, %f0, %f12
	ldd	[%fp-40], %f14
	faddd	%f12, %f10, %f10
	sethi	%hi(NavprocData), %g1
	fsubd	%f10, %f8, %f10
	or	%g1, %lo(NavprocData), %g1
	fsubd	%f14, %f10, %f10
	std	%f10, [%g1+%i0]
	jmp	%i7+8
	 restore
.L390:
	sethi	%hi(.LC14), %g1
	ldd	[%g1+%lo(.LC14)], %f10
	fcmped	%f8, %f10
	nop
	fbug	.L384
	 nop
	sethi	%hi(.LC13), %g1
	ldd	[%g1+%lo(.LC13)], %f10
	b	.L384
	 faddd	%f8, %f10, %f8
	.size	NavIC_TOWC_Correction, .-NavIC_TOWC_Correction
	.section	.rodata.cst8
	.align 8
.LC17:
	.long	1076101120
	.long	0
	.align 8
.LC18:
	.long	1076625408
	.long	0
	.align 8
.LC19:
	.long	1074783062
	.long	2531625523
	.align 8
.LC20:
	.long	-1071382528
	.long	0
	.align 8
.LC21:
	.long	-1072577169
	.long	1563991519
	.align 8
.LC22:
	.long	-1071513600
	.long	0
	.align 8
.LC23:
	.long	1091728640
	.long	0
	.align 8
.LC24:
	.long	1092777216
	.long	0
	.align 8
.LC25:
	.long	-1055755008
	.long	0
	.align 8
.LC26:
	.long	1073741824
	.long	0
	.align 8
.LC27:
	.long	1044740494
	.long	3794832442
	.section	.text.NavIC_Cor1_ObsPRange,"ax",@progbits
	.align 4
	.global NavIC_Cor1_ObsPRange
	.type	NavIC_Cor1_ObsPRange, #function
	.proc	020
NavIC_Cor1_ObsPRange:
	save	%sp, -208, %sp
	sethi	%hi(.LC18), %g1
	sethi	%hi(.LC17), %i5
	ldd	[%g1+%lo(.LC18)], %o2
	call	pow, 0
	 ldd	[%i5+%lo(.LC17)], %o0
	sethi	%hi(.LC20), %g1
	ldd	[%g1+%lo(.LC20)], %o2
	sethi	%hi(.LC19), %g1
	ldd	[%g1+%lo(.LC19)], %f8
	fmuld	%f0, %f8, %f0
	ldd	[%i5+%lo(.LC17)], %o0
	call	pow, 0
	 std	%f0, [%fp-24]
	sethi	%hi(.LC22), %g1
	ldd	[%g1+%lo(.LC22)], %o2
	sethi	%hi(.LC21), %g1
	ldd	[%g1+%lo(.LC21)], %f8
	fmuld	%f0, %f8, %f0
	ldd	[%i5+%lo(.LC17)], %o0
	call	pow, 0
	 std	%f0, [%fp-64]
	sll	%i0, 4, %i5
	std	%i2, [%fp-104]
	st	%i1, [%fp-108]
	ldd	[%fp-104], %f10
	ld	[%fp-108], %f12
	fmuld	%f0, %f10, %f0
	fitod	%f12, %f8
	sethi	%hi(NavSubFrame2Data), %i3
	fsubd	%f8, %f0, %f14
	or	%i3, %lo(NavSubFrame2Data), %i3
	sll	%i0, 6, %i4
	std	%f0, [%fp-48]
	add	%i5, %i4, %i4
	std	%f14, [%fp-56]
	add	%i3, %i4, %g1
	ldd	[%g1+8], %f8
	sethi	%hi(.LC23), %g1
	fsubd	%f14, %f8, %f8
	ldd	[%g1+%lo(.LC23)], %f10
	fcmped	%f8, %f10
	nop
	fbul	.L401
	 nop
	sethi	%hi(.LC24), %g1
	ldd	[%g1+%lo(.LC24)], %f10
	fsubd	%f8, %f10, %f8
.L395:
	add	%i3, %i4, %g1
	sethi	%hi(.LC26), %l1
	ldd	[%g1+24], %o0
	ldd	[%l1+%lo(.LC26)], %o2
	call	pow, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-24], %f12
	fdivd	%f12, %f0, %f10
	std	%f0, [%fp-40]
	std	%f10, [%fp-16]
	add	%fp, -16, %o0
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	ldd	[%fp-8], %f10
	ldd	[%fp-40], %f12
	fdivd	%f10, %f12, %f14
	sll	%i0, 7, %i1
	sethi	%hi(NavSubFrame1Data), %l0
	add	%i5, %i1, %i1
	or	%l0, %lo(NavSubFrame1Data), %l0
	ldd	[%i3+%i4], %f10
	add	%l0, %i1, %g1
	ldd	[%fp-72], %f8
	ldd	[%g1+40], %f12
	sethi	%hi(.LC27), %i2
	faddd	%f14, %f12, %f12
	or	%i2, %lo(.LC27), %i2
	fmuld	%f12, %f8, %f8
	faddd	%f8, %f10, %f14
	std	%f14, [%fp-32]
	std	%f14, [%fp-24]
	add	%i3, %i4, %i5
.L402:
	ldd	[%i5+16], %f8
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-72], %f8
	ldd	[%fp-24], %f10
	fmuld	%f8, %f0, %f0
	ldd	[%fp-32], %f8
	faddd	%f0, %f8, %f0
	fsubd	%f0, %f10, %f10
	std	%f0, [%fp-24]
	std	%f10, [%fp-104]
	call	fabs, 0
	 ldd	[%fp-104], %o0
	ldd	[%i2], %f8
	fcmped	%f0, %f8
	nop
	fbg,a	.L402
	 add	%i3, %i4, %i5
	ldd	[%i5+16], %f10
	ldd	[%fp-64], %f12
	ldd	[%fp-40], %f14
	fmuld	%f12, %f10, %f10
	fmuld	%f10, %f14, %f10
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f10, [%fp-80]
	add	%l0, %i1, %i5
	ldd	[%fp-56], %f12
	ldd	[%i5+8], %f14
	ldd	[%i5+24], %f8
	ldd	[%fp-80], %f10
	fsubd	%f12, %f8, %f8
	fmuld	%f10, %f0, %f10
	fmuld	%f8, %f14, %f12
	ldd	[%l0+%i1], %f16
	ldd	[%i5+16], %f14
	faddd	%f12, %f16, %f12
	std	%f8, [%fp-104]
	std	%f10, [%fp-80]
	std	%f12, [%fp-88]
	std	%f14, [%fp-96]
	ldd	[%fp-104], %o0
	call	pow, 0
	 ldd	[%l1+%lo(.LC26)], %o2
	ldd	[%fp-96], %f14
	ldd	[%fp-88], %f12
	fmuld	%f14, %f0, %f0
	ldd	[%fp-80], %f10
	add	%i0, 13, %i0
	ldd	[%i5+32], %f8
	sll	%i0, 3, %i0
	faddd	%f12, %f0, %f12
	ldd	[%fp-48], %f14
	faddd	%f12, %f10, %f10
	sethi	%hi(NavprocData), %g1
	fsubd	%f10, %f8, %f10
	or	%g1, %lo(NavprocData), %g1
	faddd	%f14, %f10, %f10
	std	%f10, [%g1+%i0]
	jmp	%i7+8
	 restore
.L401:
	sethi	%hi(.LC25), %g1
	ldd	[%g1+%lo(.LC25)], %f10
	fcmped	%f8, %f10
	nop
	fbug	.L395
	 nop
	sethi	%hi(.LC24), %g1
	ldd	[%g1+%lo(.LC24)], %f10
	b	.L395
	 faddd	%f8, %f10, %f8
	.size	NavIC_Cor1_ObsPRange, .-NavIC_Cor1_ObsPRange
	.section	.rodata.cst8
	.align 8
.LC28:
	.long	-1065402368
	.long	0
	.section	.text.NavIC_Cor_ObsPRange,"ax",@progbits
	.align 4
	.global NavIC_Cor_ObsPRange
	.type	NavIC_Cor_ObsPRange, #function
	.proc	020
NavIC_Cor_ObsPRange:
	add	%o0, 13, %g3
	sethi	%hi(NavprocData), %g1
	sll	%g3, 3, %g3
	or	%g1, %lo(NavprocData), %g1
	add	%o0, 75, %g4
	sethi	%hi(.LC28), %g2
	sll	%g4, 3, %g4
	ldd	[%g2+%lo(.LC28)], %f12
	ldd	[%g1+%g4], %f10
	fcmpd	%f10, %f12
	nop
	fbe	.L404
	 ldd	[%g1+%g3], %f8
	faddd	%f8, %f10, %f8
	ldd	[%g2+%lo(.LC28)], %f12
.L404:
	add	%o0, 81, %g3
	sll	%g3, 3, %g2
	ldd	[%g1+%g2], %f10
	fcmpd	%f10, %f12
	nop
	fbne,a	.L405
	 faddd	%f8, %f10, %f8
.L405:
	add	%o0, 7, %o0
	sll	%o0, 3, %o0
	jmp	%o7+8
	 std	%f8, [%g1+%o0]
	.size	NavIC_Cor_ObsPRange, .-NavIC_Cor_ObsPRange
	.section	.rodata.cst8
	.align 8
.LC29:
	.long	1076101120
	.long	0
	.align 8
.LC30:
	.long	1076625408
	.long	0
	.align 8
.LC31:
	.long	1074783062
	.long	2531625523
	.align 8
.LC32:
	.long	-1072431104
	.long	0
	.align 8
.LC33:
	.long	1075653408
	.long	1000798353
	.align 8
.LC34:
	.long	-1071513600
	.long	0
	.align 8
.LC35:
	.long	1091728640
	.long	0
	.align 8
.LC36:
	.long	1092777216
	.long	0
	.align 8
.LC37:
	.long	-1055755008
	.long	0
	.align 8
.LC38:
	.long	1073741824
	.long	0
	.align 8
.LC39:
	.long	1044740494
	.long	3794832442
	.align 8
.LC40:
	.long	1072693248
	.long	0
	.section	.text.NavComputeSatPos,"ax",@progbits
	.align 4
	.global NavComputeSatPos
	.type	NavComputeSatPos, #function
	.proc	020
NavComputeSatPos:
	save	%sp, -216, %sp
	sethi	%hi(.LC30), %g1
	sethi	%hi(.LC29), %i5
	ldd	[%g1+%lo(.LC30)], %o2
	call	pow, 0
	 ldd	[%i5+%lo(.LC29)], %o0
	sethi	%hi(.LC32), %g1
	ldd	[%g1+%lo(.LC32)], %o2
	sethi	%hi(.LC31), %g1
	ldd	[%g1+%lo(.LC31)], %f8
	fmuld	%f0, %f8, %f0
	ldd	[%i5+%lo(.LC29)], %o0
	call	pow, 0
	 std	%f0, [%fp-24]
	sethi	%hi(.LC34), %g1
	ldd	[%g1+%lo(.LC34)], %o2
	sethi	%hi(.LC33), %g1
	ldd	[%g1+%lo(.LC33)], %f8
	fmuld	%f0, %f8, %f0
	ldd	[%i5+%lo(.LC29)], %o0
	call	pow, 0
	 std	%f0, [%fp-56]
	sll	%i1, 4, %i5
	st	%i3, [%fp-112]
	st	%i4, [%fp-108]
	st	%i2, [%fp-116]
	sethi	%hi(NavSubFrame2Data), %i3
	ld	[%fp-116], %f8
	or	%i3, %lo(NavSubFrame2Data), %i3
	fitod	%f8, %f10
	sll	%i1, 6, %i4
	add	%i5, %i4, %i4
	add	%i3, %i4, %g1
	ldd	[%fp-112], %f12
	ldd	[%g1+8], %f14
	fmuld	%f0, %f12, %f0
	sethi	%hi(.LC35), %g1
	fsubd	%f10, %f0, %f8
	ldd	[%g1+%lo(.LC35)], %f10
	fsubd	%f8, %f14, %f8
	fcmped	%f8, %f10
	nop
	fbul	.L415
	 nop
	sethi	%hi(.LC36), %g1
	ldd	[%g1+%lo(.LC36)], %f10
	fsubd	%f8, %f10, %f8
.L409:
	add	%i3, %i4, %g1
	sethi	%hi(.LC38), %l1
	ldd	[%g1+24], %o0
	ldd	[%l1+%lo(.LC38)], %o2
	call	pow, 0
	 std	%f8, [%fp-64]
	ldd	[%fp-24], %f12
	fdivd	%f12, %f0, %f10
	std	%f0, [%fp-40]
	std	%f10, [%fp-16]
	add	%fp, -16, %o0
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	ldd	[%fp-8], %f10
	sll	%i1, 7, %i0
	sethi	%hi(NavSubFrame1Data), %l0
	add	%i5, %i0, %i0
	or	%l0, %lo(NavSubFrame1Data), %l0
	ldd	[%fp-40], %f18
	add	%l0, %i0, %g1
	fdivd	%f10, %f18, %f14
	ldd	[%g1+40], %f12
	faddd	%f14, %f12, %f12
	ldd	[%i3+%i4], %f10
	ldd	[%fp-64], %f8
	sethi	%hi(.LC39), %i2
	fmuld	%f12, %f8, %f8
	or	%i2, %lo(.LC39), %i2
	faddd	%f8, %f10, %f12
	std	%f12, [%fp-32]
	std	%f12, [%fp-24]
	add	%i3, %i4, %i5
.L416:
	ldd	[%i5+16], %f8
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f8, [%fp-64]
	ldd	[%fp-64], %f8
	ldd	[%fp-32], %f14
	fmuld	%f8, %f0, %f0
	ldd	[%fp-24], %f18
	faddd	%f0, %f14, %f0
	fsubd	%f0, %f18, %f18
	std	%f0, [%fp-24]
	std	%f18, [%fp-112]
	call	fabs, 0
	 ldd	[%fp-112], %o0
	ldd	[%i2], %f8
	fcmped	%f0, %f8
	nop
	fbg,a	.L416
	 add	%i3, %i4, %i5
	ldd	[%l1+%lo(.LC38)], %o2
	call	pow, 0
	 ldd	[%i5+16], %o0
	sethi	%hi(.LC40), %g1
	ldd	[%g1+%lo(.LC40)], %f8
	fsubd	%f8, %f0, %f0
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-16]
	call	sin, 0
	 ldd	[%fp-24], %o0
	ldd	[%i5+16], %f12
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f8
	ldd	[%fp-24], %o0
	std	%f8, [%fp-64]
	call	cos, 0
	 std	%f12, [%fp-80]
	ldd	[%fp-80], %f12
	sethi	%hi(.LC40), %g1
	ldd	[%fp-64], %f8
	ldd	[%g1+%lo(.LC40)], %f10
	fmuld	%f12, %f0, %f0
	fsubd	%f10, %f0, %f12
	fdivd	%f8, %f12, %f12
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f12, [%fp-80]
	ldd	[%i5+16], %f8
	fsubd	%f0, %f8, %f10
	ldd	[%fp-24], %o0
	std	%f8, [%fp-64]
	call	cos, 0
	 std	%f10, [%fp-72]
	ldd	[%fp-80], %f12
	sethi	%hi(.LC40), %g1
	std	%f12, [%fp-112]
	ldd	[%fp-64], %f8
	ldd	[%g1+%lo(.LC40)], %f12
	ldd	[%fp-72], %f10
	fmuld	%f8, %f0, %f0
	fsubd	%f12, %f0, %f8
	fdivd	%f10, %f8, %f12
	ldd	[%fp-112], %o0
	std	%f12, [%fp-112]
	call	atan2, 0
	 ldd	[%fp-112], %o2
	add	%l0, %i0, %i4
	ldd	[%i5+40], %f8
	ldd	[%i4+64], %f10
	faddd	%f0, %f8, %f8
	faddd	%f8, %f8, %f14
	std	%f8, [%fp-64]
	std	%f14, [%fp-32]
	std	%f10, [%fp-72]
	call	sin, 0
	 ldd	[%fp-32], %o0
	ldd	[%i4+56], %f18
	ldd	[%fp-72], %f10
	fmuld	%f10, %f0, %f10
	ldd	[%fp-32], %o0
	std	%f10, [%fp-72]
	call	cos, 0
	 std	%f18, [%fp-104]
	ldd	[%fp-104], %f18
	ldd	[%i4+96], %f14
	ldd	[%fp-72], %f10
	fmuld	%f18, %f0, %f0
	faddd	%f10, %f0, %f18
	ldd	[%fp-32], %o0
	std	%f18, [%fp-104]
	call	sin, 0
	 std	%f14, [%fp-88]
	ldd	[%i4+88], %f12
	ldd	[%fp-88], %f14
	fmuld	%f14, %f0, %f14
	ldd	[%fp-32], %o0
	std	%f12, [%fp-80]
	call	cos, 0
	 std	%f14, [%fp-88]
	ldd	[%fp-80], %f12
	ldd	[%i4+80], %f10
	ldd	[%fp-88], %f14
	fmuld	%f12, %f0, %f0
	faddd	%f14, %f0, %f12
	ldd	[%fp-32], %o0
	std	%f12, [%fp-80]
	call	sin, 0
	 std	%f10, [%fp-72]
	ldd	[%i4+72], %f14
	ldd	[%fp-72], %f10
	fmuld	%f10, %f0, %f10
	ldd	[%fp-32], %o0
	std	%f10, [%fp-72]
	call	cos, 0
	 std	%f14, [%fp-88]
	ldd	[%fp-88], %f14
	ldd	[%i5+16], %f16
	ldd	[%fp-72], %f10
	fmuld	%f14, %f0, %f0
	faddd	%f10, %f0, %f14
	ldd	[%fp-24], %o0
	std	%f14, [%fp-88]
	call	cos, 0
	 std	%f16, [%fp-96]
	ldd	[%i5+56], %f10
	ldd	[%fp-104], %f18
	ldd	[%fp-96], %f16
	ldd	[%fp-88], %f14
	faddd	%f14, %f10, %f14
	ldd	[%fp-40], %f10
	sethi	%hi(.LC40), %g1
	ldd	[%fp-64], %f8
	ldd	[%fp-80], %f12
	faddd	%f8, %f18, %f8
	fmuld	%f16, %f0, %f0
	ldd	[%g1+%lo(.LC40)], %f18
	fsubd	%f18, %f0, %f16
	fmuld	%f16, %f10, %f16
	ldd	[%i5+8], %f10
	faddd	%f16, %f12, %f18
	add	%i1, 1, %i3
	ldd	[%i4+104], %f16
	sll	%i3, 3, %i3
	std	%f8, [%fp-112]
	sethi	%hi(NavprocData), %i4
	or	%i4, %lo(NavprocData), %i4
	ldd	[%i4+%i3], %f12
	fsubd	%f12, %f10, %f12
	fmuld	%f12, %f16, %f12
	faddd	%f14, %f12, %f10
	std	%f18, [%fp-24]
	std	%f10, [%fp-32]
	ldd	[%fp-112], %o0
	call	cos, 0
	 std	%f8, [%fp-64]
	ldd	[%fp-64], %f8
	ldd	[%fp-24], %f12
	fmuld	%f0, %f12, %f0
	std	%f8, [%fp-112]
	std	%f0, [%fp-48]
	call	sin, 0
	 ldd	[%fp-112], %o0
	ldd	[%fp-24], %f14
	ldd	[%i5+32], %f12
	ldd	[%i4+%i3], %f8
	ldd	[%fp-56], %f18
	fmuld	%f0, %f14, %f0
	ldd	[%i5+8], %f10
	ldd	[%i5+48], %f14
	fsubd	%f8, %f10, %f10
	fmuld	%f18, %f8, %f8
	fmuld	%f10, %f14, %f10
	faddd	%f10, %f12, %f10
	fsubd	%f10, %f8, %f12
	std	%f0, [%fp-40]
	std	%f12, [%fp-24]
	call	cos, 0
	 ldd	[%fp-24], %o0
	ldd	[%fp-48], %f14
	fmuld	%f0, %f14, %f8
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f8, [%fp-64]
	ldd	[%fp-40], %f18
	fmuld	%f0, %f18, %f10
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f10, [%fp-72]
	ldd	[%fp-72], %f10
	ldd	[%fp-64], %f8
	fmuld	%f10, %f0, %f0
	fsubd	%f8, %f0, %f10
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f10, [%fp-72]
	ldd	[%fp-48], %f8
	fmuld	%f0, %f8, %f12
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f12, [%fp-80]
	ldd	[%fp-40], %f14
	fmuld	%f0, %f14, %f8
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f8, [%fp-64]
	ldd	[%fp-64], %f8
	ldd	[%fp-80], %f12
	fmuld	%f8, %f0, %f0
	faddd	%f12, %f0, %f8
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f8, [%fp-64]
	ldd	[%fp-72], %f10
	ldd	[%fp-64], %f8
	add	%i1, %i1, %g1
	ldd	[%fp-40], %f18
	add	%g1, %i1, %i1
	fmuld	%f0, %f18, %f0
	sll	%i1, 3, %i1
	add	%i4, %i1, %i4
	std	%f10, [%i4+216]
	std	%f8, [%i4+224]
	std	%f0, [%i4+232]
	jmp	%i7+8
	 restore
.L415:
	sethi	%hi(.LC37), %g1
	ldd	[%g1+%lo(.LC37)], %f10
	fcmped	%f8, %f10
	nop
	fbug	.L409
	 nop
	sethi	%hi(.LC36), %g1
	ldd	[%g1+%lo(.LC36)], %f10
	b	.L409
	 faddd	%f8, %f10, %f8
	.size	NavComputeSatPos, .-NavComputeSatPos
	.section	.text.CompTranspose,"ax",@progbits
	.align 4
	.global CompTranspose
	.type	CompTranspose, #function
	.proc	020
CompTranspose:
	save	%sp, -96, %sp
	cmp	%i0, 0
	ble	.L424
	 sll	%i0, 3, %i5
	sll	%i1, 3, %o7
	mov	0, %i4
.L419:
	cmp	%i1, 0
	ble,a	.L423
	 add	%i4, 1, %i4
	mov	%i3, %g3
	mov	%i2, %g2
	mov	0, %g1
	sll	%i4, 3, %g4
.L420:
	ldd	[%g2], %f8
	std	%f8, [%g3+%g4]
	add	%g1, 1, %g1
	add	%g2, 8, %g2
	cmp	%g1, %i1
	bne	.L420
	 add	%g3, %i5, %g3
	add	%i4, 1, %i4
.L423:
	cmp	%i4, %i0
	bne	.L419
	 add	%i2, %o7, %i2
.L424:
	jmp	%i7+8
	 restore
	.size	CompTranspose, .-CompTranspose
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC42:
	.asciz	"\nMatrices with entered orders can't be multiplied with each other.\n"
	.section	.rodata.cst8
	.align 8
.LC41:
	.long	0
	.long	0
	.section	.text.MatMultiplication,"ax",@progbits
	.align 4
	.global MatMultiplication
	.type	MatMultiplication, #function
	.proc	020
MatMultiplication:
	save	%sp, -96, %sp
	cmp	%i1, %i2
	bne	.L426
	 ld	[%fp+92], %o2
	cmp	%i0, 0
	ble	.L442
	 sll	%i3, 3, %i2
	sll	%i1, 3, %o0
	mov	%i4, %o5
	mov	0, %o3
	sethi	%hi(.LC41), %o1
.L432:
	cmp	%i3, 0
	ble,a	.L440
	 add	%o3, 1, %o3
	mov	%o2, %o7
	mov	0, %i4
	or	%o1, %lo(.LC41), %o4
.L434:
	cmp	%i1, 0
	ble	.L435
	 mov	%i5, %g3
	mov	%o5, %g2
	ldd	[%o4], %f8
	mov	0, %g1
	sll	%i4, 3, %g4
.L429:
	ldd	[%g2], %f12
	ldd	[%g3+%g4], %f10
	add	%g1, 1, %g1
	fmuld	%f12, %f10, %f10
	add	%g2, 8, %g2
	faddd	%f8, %f10, %f8
	cmp	%g1, %i1
	bne	.L429
	 add	%g3, %i2, %g3
	std	%f8, [%o7]
	add	%i4, 1, %i4
	cmp	%i4, %i3
	bne	.L434
	 add	%o7, 8, %o7
	add	%o3, 1, %o3
.L440:
	add	%o2, %i2, %o2
	cmp	%o3, %i0
	bne	.L432
	 add	%o5, %o0, %o5
.L442:
	jmp	%i7+8
	 restore
.L435:
	ldd	[%o4], %f8
	std	%f8, [%o7]
	add	%i4, 1, %i4
	cmp	%i4, %i3
	bne	.L434
	 add	%o7, 8, %o7
	b	.L440
	 add	%o3, 1, %o3
.L426:
	sethi	%hi(.LC42), %i0
	call	ee_printf, 0
	 restore %i0, %lo(.LC42), %o0
	.size	MatMultiplication, .-MatMultiplication
	.section	.rodata.cst8
	.align 8
.LC43:
	.long	0
	.long	0
	.section	.text.FindDeterminant,"ax",@progbits
	.align 4
	.global FindDeterminant
	.type	FindDeterminant, #function
	.proc	07
FindDeterminant:
	save	%sp, -392, %sp
	cmp	%i0, 2
	be	.L444
	 cmp	%i0, 0
	ble	.L453
	 add	%fp, -160, %l0
	add	%i0, -1, %l1
	mov	%l0, %l3
	mov	0, %i5
	mov	1, %l2
.L446:
	mov	%i1, %i2
	mov	0, %i4
	mov	0, %g3
	mov	0, %g4
.L449:
	subcc	%g0, %i4, %g0
	mov	%i2, %g2
	mov	0, %g1
	addx	%g0, 0, %o7
.L448:
	cmp	%g1, %i5
	be,a	.L464
	 add	%g1, 1, %g1
	sll	%g4, 2, %i3
	cmp	%o7, 0
	add	%i3, %g3, %i3
	sll	%i3, 3, %i3
	be	.L447
	 add	%fp, %i3, %i3
	ldd	[%g2], %f8
	add	%g3, 1, %g3
	cmp	%l1, %g3
	bg	.L447
	 std	%f8, [%i3-288]
	add	%g4, 1, %g4
	mov	0, %g3
.L447:
	add	%g1, 1, %g1
.L464:
	cmp	%g1, %i0
	bne	.L448
	 add	%g2, 8, %g2
	add	%i4, 1, %i4
	cmp	%i4, %i0
	bne	.L449
	 add	%i2, 32, %i2
	mov	%l2, %i5
	mov	1, %i4
	add	%l2, 1, %l2
	mov	0, %g1
.L450:
	add	%g1, 1, %g1
	cmp	%l2, %g1
	bne	.L450
	 sub	%g0, %i4, %i4
	mov	%l1, %o0
	call	FindDeterminant, 0
	 add	%fp, -288, %o1
	st	%i4, [%fp-292]
	ld	[%fp-292], %f10
	fitod	%f10, %f8
	fmuld	%f8, %f0, %f0
	std	%f0, [%l3]
	cmp	%i5, %i0
	bne	.L446
	 add	%l3, 8, %l3
	sethi	%hi(.LC43), %g2
	sll	%i5, 3, %i5
	mov	0, %g1
	ldd	[%g2+%lo(.LC43)], %f0
.L452:
	ldd	[%i1+%g1], %f10
	ldd	[%l0+%g1], %f8
	add	%g1, 8, %g1
	fmuld	%f10, %f8, %f8
	cmp	%g1, %i5
	bne	.L452
	 faddd	%f0, %f8, %f0
	jmp	%i7+8
	 restore
.L444:
	ldd	[%i1], %f10
	ldd	[%i1+40], %f8
	ldd	[%i1+8], %f12
	fmuld	%f10, %f8, %f8
	ldd	[%i1+32], %f10
	fmuld	%f12, %f10, %f12
	fsubd	%f8, %f12, %f0
	jmp	%i7+8
	 restore
.L453:
	sethi	%hi(.LC43), %g1
	ldd	[%g1+%lo(.LC43)], %f0
	jmp	%i7+8
	 restore
	.size	FindDeterminant, .-FindDeterminant
	.section	.rodata.cst8
	.align 8
.LC44:
	.long	0
	.long	0
	.align 8
.LC45:
	.long	-1074790400
	.long	0
	.section	.text.FindCoFactor.constprop.3,"ax",@progbits
	.align 4
	.type	FindCoFactor.constprop.3, #function
	.proc	020
FindCoFactor.constprop.3:
	save	%sp, -536, %sp
	mov	0, %l1
	st	%i1, [%fp-424]
.L466:
	subcc	%g0, %l1, %g0
	xor	%l1, 1, %g1
	addx	%g0, 0, %l5
	subcc	%g0, %g1, %g0
	xor	%l1, 2, %g1
	addx	%g0, 0, %l4
	subcc	%g0, %g1, %g0
	xor	%l1, 3, %g1
	addx	%g0, 0, %l3
	mov	0, %l0
	subcc	%g0, %g1, %g0
	stb	%g0, [%fp-417]
	mov	0, %g1
	addx	%g0, 0, %l2
.L498:
	xor	%l0, 1, %g2
	subcc	%g0, %g2, %g0
	addx	%g0, 0, %o0
	cmp	%o0, 0
	be	.L623
	 xor	%l0, 2, %g2
	cmp	%l5, 0
	be	.L624
	 subcc	%g0, %g2, %g0
	sll	%g1, 3, %g2
	ldd	[%i0+8], %f8
	add	%fp, %g2, %g2
	add	%g1, 1, %g1
	std	%f8, [%g2-416]
	xor	%l0, 2, %g2
.L623:
	subcc	%g0, %g2, %g0
.L624:
	addx	%g0, 0, %o1
	cmp	%o1, 0
	be	.L625
	 mov	12, %l6
	cmp	%l5, 0
	be	.L626
	 mov	11, %o3
	sll	%g1, 3, %g2
	ldd	[%i0+16], %f8
	add	%fp, %g2, %g2
	cmp	%g1, 1
	bg	.L507
	 std	%f8, [%g2-416]
	add	%g1, 1, %g1
	mov	12, %l6
.L625:
	mov	11, %o3
.L626:
	mov	10, %o4
	mov	9, %o5
	mov	8, %o7
	mov	7, %i1
	mov	6, %i2
	mov	5, %i3
	mov	4, %i4
	mov	3, %i5
	mov	2, %g4
	mov	1, %g3
	mov	0, %g2
.L482:
	xor	%l0, 3, %o2
	subcc	%g0, %o2, %g0
	addx	%g0, 0, %o2
	cmp	%o2, 0
	be	.L627
	 ldub	[%fp-417], %l7
	cmp	%l5, 0
	be,a	.L628
	 andcc	%l7, 0xff, %l6
	sll	%g2, 2, %l7
	ldd	[%i0+24], %f8
	add	%l7, %g1, %l7
	sll	%l7, 3, %l7
	add	%fp, %l7, %l7
	cmp	%g1, 1
	bg	.L508
	 std	%f8, [%l7-416]
	add	%g1, 1, %g1
.L483:
	ldub	[%fp-417], %l7
.L627:
	andcc	%l7, 0xff, %l6
.L628:
	be	.L629
	 cmp	%o0, 0
	cmp	%l4, 0
	be	.L629
	 cmp	%o0, 0
	sll	%g2, 2, %l7
	ldd	[%i0+32], %f8
	add	%l7, %g1, %l7
	sll	%l7, 3, %l7
	add	%fp, %l7, %l7
	cmp	%g1, 1
	bg	.L509
	 std	%f8, [%l7-416]
	add	%g1, 1, %g1
.L484:
	cmp	%o0, 0
.L629:
	be	.L630
	 cmp	%o1, 0
	cmp	%l4, 0
	be	.L630
	 cmp	%o1, 0
	sll	%g2, 2, %o3
	ldd	[%i0+40], %f8
	add	%o3, %g1, %o3
	sll	%o3, 3, %o3
	add	%fp, %o3, %o3
	cmp	%g1, 1
	bg	.L510
	 std	%f8, [%o3-416]
	add	%g1, 1, %g1
.L485:
	cmp	%o1, 0
.L630:
	be	.L631
	 cmp	%o2, 0
	cmp	%l4, 0
	be	.L631
	 cmp	%o2, 0
	sll	%g2, 2, %o4
	ldd	[%i0+48], %f8
	add	%o4, %g1, %o4
	sll	%o4, 3, %o4
	add	%fp, %o4, %o4
	cmp	%g1, 1
	bg	.L511
	 std	%f8, [%o4-416]
	add	%g1, 1, %g1
.L486:
	cmp	%o2, 0
.L631:
	be	.L632
	 cmp	%l6, 0
	cmp	%l4, 0
	be	.L632
	 cmp	%l6, 0
	sll	%g2, 2, %o5
	ldd	[%i0+56], %f8
	add	%o5, %g1, %o5
	sll	%o5, 3, %o5
	add	%fp, %o5, %o5
	cmp	%g1, 1
	bg	.L512
	 std	%f8, [%o5-416]
	add	%g1, 1, %g1
.L487:
	cmp	%l6, 0
.L632:
	be	.L633
	 cmp	%o0, 0
	cmp	%l3, 0
	be	.L633
	 cmp	%o0, 0
	sll	%g2, 2, %o7
	ldd	[%i0+64], %f8
	add	%o7, %g1, %o7
	sll	%o7, 3, %o7
	add	%fp, %o7, %o7
	cmp	%g1, 1
	bg	.L513
	 std	%f8, [%o7-416]
	add	%g1, 1, %g1
.L488:
	cmp	%o0, 0
.L633:
	be	.L634
	 cmp	%o1, 0
	cmp	%l3, 0
	be	.L634
	 cmp	%o1, 0
	sll	%g2, 2, %i1
	ldd	[%i0+72], %f8
	add	%i1, %g1, %i1
	sll	%i1, 3, %i1
	add	%fp, %i1, %i1
	cmp	%g1, 1
	bg	.L514
	 std	%f8, [%i1-416]
	add	%g1, 1, %g1
.L489:
	cmp	%o1, 0
.L634:
	be	.L635
	 cmp	%o2, 0
	cmp	%l3, 0
	be	.L635
	 cmp	%o2, 0
	sll	%g2, 2, %i2
	ldd	[%i0+80], %f8
	add	%i2, %g1, %i2
	sll	%i2, 3, %i2
	add	%fp, %i2, %i2
	cmp	%g1, 1
	bg	.L515
	 std	%f8, [%i2-416]
	add	%g1, 1, %g1
.L490:
	cmp	%o2, 0
.L635:
	be	.L636
	 cmp	%l6, 0
	cmp	%l3, 0
	be	.L636
	 cmp	%l6, 0
	sll	%g2, 2, %i3
	ldd	[%i0+88], %f8
	add	%i3, %g1, %i3
	sll	%i3, 3, %i3
	add	%fp, %i3, %i3
	cmp	%g1, 1
	bg	.L516
	 std	%f8, [%i3-416]
	add	%g1, 1, %g1
.L491:
	cmp	%l6, 0
.L636:
	be	.L637
	 cmp	%o0, 0
	cmp	%l2, 0
	be	.L637
	 cmp	%o0, 0
	sll	%g2, 2, %i4
	ldd	[%i0+96], %f8
	add	%i4, %g1, %i4
	sll	%i4, 3, %i4
	add	%fp, %i4, %i4
	cmp	%g1, 1
	bg	.L517
	 std	%f8, [%i4-416]
	add	%g1, 1, %g1
.L492:
	cmp	%o0, 0
.L637:
	be	.L638
	 cmp	%o1, 0
	cmp	%l2, 0
	be	.L638
	 cmp	%o1, 0
	sll	%g2, 2, %i5
	ldd	[%i0+104], %f8
	add	%i5, %g1, %i5
	sll	%i5, 3, %i5
	add	%fp, %i5, %i5
	cmp	%g1, 1
	bg	.L518
	 std	%f8, [%i5-416]
	add	%g1, 1, %g1
.L493:
	cmp	%o1, 0
.L638:
	be	.L639
	 cmp	%o2, 0
	cmp	%l2, 0
	be	.L639
	 cmp	%o2, 0
	sll	%g2, 2, %g4
	ldd	[%i0+112], %f8
	add	%g4, %g1, %g4
	sll	%g4, 3, %g4
	add	%fp, %g4, %g4
	cmp	%g1, 1
	bg	.L519
	 std	%f8, [%g4-416]
	add	%g1, 1, %g1
.L494:
	cmp	%o2, 0
.L639:
	be	.L640
	 add	%l0, %l1, %o2
	cmp	%l2, 0
	be,a	.L641
	 sethi	%hi(.LC45), %g1
	sll	%g2, 2, %g2
	ldd	[%i0+120], %f8
	add	%g2, %g1, %g1
	sll	%g1, 3, %g1
	add	%fp, %g1, %g1
	std	%f8, [%g1-416]
	add	%l0, %l1, %o2
.L640:
	sethi	%hi(.LC45), %g1
.L641:
	st	%o2, [%fp-428]
	or	%g1, %lo(.LC45), %g1
	ld	[%fp-428], %f9
	fitod	%f9, %f8
	ldd	[%g1], %o0
	std	%f8, [%fp-440]
	call	pow, 0
	 ldd	[%fp-440], %o2
	ldd	[%fp-384], %f22
	ldd	[%fp-376], %f10
	ldd	[%fp-368], %f8
	ldd	[%fp-352], %f20
	ldd	[%fp-344], %f18
	ldd	[%fp-336], %f16
	mov	1, %g3
	mov	0, %g4
.L496:
	cmp	%g4, 0
	be,a	.L469
	 std	%f10, [%fp-288]
	cmp	%g4, 1
	bne	.L621
	 std	%f22, [%fp-288]
	std	%f8, [%fp-280]
	mov	1, %g1
.L501:
	mov	0, %g2
.L472:
	cmp	%g4, 0
	bne	.L500
	 sll	%g1, 2, %i5
	add	%i5, %g2, %i5
.L642:
	sll	%i5, 3, %i5
	add	%fp, %i5, %i5
	cmp	%g2, 1
	bne	.L504
	 std	%f18, [%i5-288]
	add	%g1, 1, %g1
	cmp	%g4, 2
	bne	.L622
	 mov	0, %g2
.L478:
	mov	0, %g1
	mov	1, %g2
.L467:
	add	%g1, 1, %g1
	cmp	%g1, %g3
	ble	.L467
	 sub	%g0, %g2, %g2
	ldd	[%fp-248], %f12
	ldd	[%fp-288], %f14
	st	%g2, [%fp-428]
	fmuld	%f14, %f12, %f26
	ld	[%fp-428], %f12
	ldd	[%fp-280], %f14
	sll	%g4, 3, %g1
	fitod	%f12, %f24
	add	%fp, -160, %g2
	ldd	[%fp-256], %f12
	fmuld	%f14, %f12, %f12
	fsubd	%f26, %f12, %f12
	fmuld	%f12, %f24, %f12
	fmovs	%f12, %f14
	fmovs	%f13, %f15
	std	%f14, [%g2+%g1]
	add	%g4, 1, %g4
	cmp	%g4, 3
	bne	.L496
	 add	%g3, 1, %g3
	ldd	[%fp-416], %f10
	ldd	[%fp-160], %f8
	fmuld	%f10, %f8, %f8
	sethi	%hi(.LC44), %l7
	ldd	[%fp-408], %f10
	or	%l7, %lo(.LC44), %l7
	ldd	[%l7], %f12
	faddd	%f8, %f12, %f12
	ldd	[%fp-152], %f8
	fmuld	%f10, %f8, %f8
	ldd	[%fp-400], %f10
	faddd	%f12, %f8, %f12
	ldd	[%fp-144], %f8
	fmuld	%f10, %f8, %f8
	faddd	%f12, %f8, %f8
	sll	%l0, 3, %g1
	fmuld	%f0, %f8, %f0
	ld	[%fp-424], %g2
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	add	%l0, 1, %l0
	cmp	%l0, 4
	be	.L479
	 std	%f8, [%g2+%g1]
	cmp	%l5, 0
	be	.L480
	 mov	0, %g1
	ldd	[%i0], %f8
	mov	1, %g1
	std	%f8, [%fp-416]
.L480:
	mov	1, %l7
	b	.L498
	 stb	%l7, [%fp-417]
.L621:
	cmp	%g4, 2
	bne	.L520
	 std	%f10, [%fp-280]
	mov	0, %g2
	mov	1, %g1
.L500:
	sll	%g1, 2, %i5
	add	%i5, %g2, %i4
	sll	%i4, 3, %i4
	add	%fp, %i4, %i4
	cmp	%g2, 1
	bne	.L503
	 std	%f20, [%i4-288]
	add	%g1, 1, %g1
	mov	0, %g2
	sll	%g1, 2, %i5
.L474:
	cmp	%g4, 1
	bne,a	.L642
	 add	%i5, %g2, %i5
.L475:
	add	%i5, %g2, %g1
	sll	%g1, 3, %g1
	add	%fp, %g1, %g1
	b	.L478
	 std	%f16, [%g1-288]
.L469:
	mov	1, %i5
	mov	0, %g2
	mov	1, %g1
.L499:
	sll	%g2, 2, %i4
	add	%i4, %i5, %i4
	sll	%i4, 3, %i4
	add	%fp, %i4, %i4
	cmp	%i5, 1
	be	.L501
	 std	%f8, [%i4-288]
	mov	%g2, %g1
	b	.L472
	 mov	1, %g2
.L504:
	cmp	%g4, 2
	be	.L478
	 mov	1, %g2
.L622:
	b	.L475
	 sll	%g1, 2, %i5
.L503:
	b	.L474
	 mov	1, %g2
.L519:
	mov	%g3, %g2
	b	.L494
	 mov	0, %g1
.L479:
	add	%g2, 32, %g1
	add	%l1, 1, %l1
	cmp	%l1, 4
	bne	.L466
	 st	%g1, [%fp-424]
	jmp	%i7+8
	 restore
.L520:
	mov	0, %i5
	mov	1, %g2
	b	.L499
	 mov	2, %g1
.L515:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	mov	%i5, %g4
	mov	%i4, %i5
	b	.L490
	 mov	%i3, %i4
.L516:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	mov	%i5, %g4
	b	.L491
	 mov	%i4, %i5
.L517:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	b	.L492
	 mov	%i5, %g4
.L518:
	mov	%g3, %g2
	mov	0, %g1
	b	.L493
	 mov	%g4, %g3
.L507:
	mov	13, %l6
	mov	12, %o3
	mov	11, %o4
	mov	10, %o5
	mov	9, %o7
	mov	8, %i1
	mov	7, %i2
	mov	6, %i3
	mov	5, %i4
	mov	4, %i5
	mov	3, %g4
	mov	2, %g3
	mov	0, %g1
	b	.L482
	 mov	1, %g2
.L508:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	mov	%i5, %g4
	mov	%i4, %i5
	mov	%i3, %i4
	mov	%i2, %i3
	mov	%i1, %i2
	mov	%o7, %i1
	mov	%o5, %o7
	mov	%o4, %o5
	mov	%o3, %o4
	b	.L483
	 mov	%l6, %o3
.L509:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	mov	%i5, %g4
	mov	%i4, %i5
	mov	%i3, %i4
	mov	%i2, %i3
	mov	%i1, %i2
	mov	%o7, %i1
	mov	%o5, %o7
	mov	%o4, %o5
	b	.L484
	 mov	%o3, %o4
.L510:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	mov	%i5, %g4
	mov	%i4, %i5
	mov	%i3, %i4
	mov	%i2, %i3
	mov	%i1, %i2
	mov	%o7, %i1
	mov	%o5, %o7
	b	.L485
	 mov	%o4, %o5
.L511:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	mov	%i5, %g4
	mov	%i4, %i5
	mov	%i3, %i4
	mov	%i2, %i3
	mov	%i1, %i2
	mov	%o7, %i1
	b	.L486
	 mov	%o5, %o7
.L512:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	mov	%i5, %g4
	mov	%i4, %i5
	mov	%i3, %i4
	mov	%i2, %i3
	mov	%i1, %i2
	b	.L487
	 mov	%o7, %i1
.L513:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	mov	%i5, %g4
	mov	%i4, %i5
	mov	%i3, %i4
	mov	%i2, %i3
	b	.L488
	 mov	%i1, %i2
.L514:
	mov	%g3, %g2
	mov	0, %g1
	mov	%g4, %g3
	mov	%i5, %g4
	mov	%i4, %i5
	mov	%i3, %i4
	b	.L489
	 mov	%i2, %i3
	.size	FindCoFactor.constprop.3, .-FindCoFactor.constprop.3
	.section	.rodata.cst8
	.align 8
.LC46:
	.long	0
	.long	0
	.section	.text.FindDeterminant.constprop.5,"ax",@progbits
	.align 4
	.type	FindDeterminant.constprop.5, #function
	.proc	07
FindDeterminant.constprop.5:
	save	%sp, -736, %sp
	sethi	%hi(.LC46), %l2
	mov	1, %l0
	mov	0, %i1
	add	%fp, -160, %i2
	or	%l2, %lo(.LC46), %l2
	add	%fp, -320, %l1
.L644:
	cmp	%i1, 0
	be,a	.L660
	 ldd	[%i0+40], %f10
	ldd	[%i0+32], %f8
	cmp	%i1, 1
	bne	.L732
	 std	%f8, [%fp-576]
	ldd	[%i0+48], %f8
	std	%f8, [%fp-568]
.L690:
	mov	2, %g4
	mov	0, %g1
	mov	3, %g3
.L691:
	sll	%g1, 2, %g2
	ldd	[%i0+56], %f8
	add	%g2, %g4, %g4
	sll	%g4, 3, %g4
	add	%fp, %g4, %g4
	std	%f8, [%g4-576]
	cmp	%g3, 2
	ble	.L665
	 add	%g3, 1, %i5
.L664:
	add	%g1, 1, %g1
	mov	1, %i5
	mov	0, %g3
	sll	%g1, 2, %g2
.L665:
	cmp	%i1, 0
	bne,a	.L740
	 add	%g2, %g3, %g3
.L666:
	add	%g2, %g3, %g3
	ldd	[%i0+72], %f8
	sll	%g3, 3, %g3
	add	%fp, %g3, %g3
	std	%f8, [%g3-576]
	cmp	%i5, 3
	bne	.L671
	 add	%i5, 1, %g4
	add	%g1, 1, %g1
	mov	1, %g4
	mov	0, %i5
	sll	%g1, 2, %g2
.L671:
	cmp	%i1, 2
	bne,a	.L741
	 add	%g2, %i5, %g3
.L672:
	add	%g2, %i5, %g3
	ldd	[%i0+88], %f8
	sll	%g3, 3, %g3
	add	%fp, %g3, %g3
	std	%f8, [%g3-576]
	cmp	%g4, 2
	ble	.L677
	 add	%g4, 1, %g3
	add	%g1, 1, %g1
	mov	1, %g3
	mov	0, %g4
	sll	%g1, 2, %g2
.L677:
	cmp	%i1, 0
	bne,a	.L742
	 add	%g2, %g4, %g4
.L678:
	add	%g2, %g4, %g4
	ldd	[%i0+104], %f8
	sll	%g4, 3, %g4
	add	%fp, %g4, %g4
	cmp	%g3, 3
	bne	.L682
	 std	%f8, [%g4-576]
	add	%g1, 1, %g1
	mov	0, %g3
	sll	%g1, 2, %g2
.L682:
	cmp	%i1, 2
	bne	.L681
	 add	%g3, 1, %i5
.L683:
	add	%g2, %g3, %g1
	ldd	[%i0+120], %f8
	sll	%g1, 3, %g1
	add	%fp, %g1, %g1
	std	%f8, [%g1-576]
	mov	0, %g1
.L744:
	mov	1, %g2
.L645:
	add	%g1, 1, %g1
	cmp	%g1, %l0
	ble	.L645
	 sub	%g0, %g2, %g2
	st	%g2, [%fp-636]
	ld	[%fp-636], %f9
	fitod	%f9, %f8
	ldd	[%fp-544], %f12
	std	%f8, [%fp-632]
	ldd	[%fp-536], %f8
	std	%f12, [%fp-600]
	std	%f8, [%fp-584]
	ldd	[%fp-528], %f12
	ldd	[%fp-512], %f8
	std	%f12, [%fp-592]
	std	%f8, [%fp-608]
	ldd	[%fp-504], %f12
	ldd	[%fp-496], %f8
	std	%f12, [%fp-616]
	std	%f8, [%fp-624]
	mov	1, %i4
	mov	0, %i3
.L646:
	cmp	%i3, 0
	be	.L649
	 ldd	[%fp-584], %f8
	ldd	[%fp-600], %f12
	cmp	%i3, 1
	bne	.L734
	 std	%f12, [%fp-448]
	ldd	[%fp-592], %f8
	mov	1, %g2
	std	%f8, [%fp-440]
.L689:
	mov	0, %g1
.L652:
	cmp	%i3, 0
	bne	.L688
	 sll	%g2, 2, %g3
	add	%g3, %g1, %g3
.L743:
	ldd	[%fp-616], %f8
	sll	%g3, 3, %g3
	add	%fp, %g3, %g3
	cmp	%g1, 1
	bne	.L695
	 std	%f8, [%g3-448]
	add	%g2, 1, %g2
	cmp	%i3, 2
	bne	.L735
	 mov	0, %g1
.L658:
	mov	0, %g1
	mov	1, %i5
.L647:
	add	%g1, 1, %g1
	cmp	%g1, %i4
	ble	.L647
	 sub	%g0, %i5, %i5
	mov	2, %o0
	call	FindDeterminant, 0
	 add	%fp, -448, %o1
	st	%i5, [%fp-636]
	sll	%i3, 3, %g1
	ld	[%fp-636], %f10
	fitod	%f10, %f8
	fmuld	%f8, %f0, %f0
	std	%f0, [%i2+%g1]
	add	%i3, 1, %i3
	cmp	%i3, 3
	bne	.L646
	 add	%i4, 1, %i4
	ldd	[%fp-576], %f12
	ldd	[%fp-160], %f10
	fmuld	%f12, %f10, %f10
	ldd	[%fp-568], %f12
	ldd	[%l2], %f8
	faddd	%f10, %f8, %f14
	ldd	[%fp-152], %f10
	fmuld	%f12, %f10, %f10
	ldd	[%fp-560], %f12
	sll	%i1, 3, %g1
	faddd	%f14, %f10, %f14
	ldd	[%fp-144], %f10
	fmuld	%f12, %f10, %f10
	ldd	[%fp-632], %f12
	faddd	%f14, %f10, %f10
	fmuld	%f10, %f12, %f10
	std	%f10, [%l1+%g1]
	add	%i1, 1, %i1
	cmp	%i1, 4
	bne	.L644
	 add	%l0, 1, %l0
	ldd	[%i0], %f14
	ldd	[%fp-320], %f10
	fmuld	%f14, %f10, %f10
	faddd	%f10, %f8, %f8
	ldd	[%i0+8], %f12
	ldd	[%fp-312], %f10
	ldd	[%i0+16], %f14
	fmuld	%f12, %f10, %f10
	faddd	%f8, %f10, %f10
	ldd	[%fp-304], %f8
	fmuld	%f14, %f8, %f8
	ldd	[%i0+24], %f12
	faddd	%f8, %f10, %f10
	ldd	[%fp-296], %f8
	fmuld	%f12, %f8, %f8
	faddd	%f8, %f10, %f0
	jmp	%i7+8
	 restore
.L734:
	ldd	[%fp-584], %f12
	cmp	%i3, 2
	bne	.L696
	 std	%f12, [%fp-440]
	mov	0, %g1
	mov	1, %g2
.L688:
	sll	%g2, 2, %g3
	ldd	[%fp-608], %f12
	add	%g3, %g1, %g4
	sll	%g4, 3, %g4
	add	%fp, %g4, %g4
	cmp	%g1, 1
	bne	.L694
	 std	%f12, [%g4-448]
	add	%g2, 1, %g2
	mov	0, %g1
	sll	%g2, 2, %g3
.L654:
	cmp	%i3, 1
	bne,a	.L743
	 add	%g3, %g1, %g3
.L655:
	add	%g3, %g1, %g1
	ldd	[%fp-624], %f12
	sll	%g1, 3, %g1
	add	%fp, %g1, %g1
	b	.L658
	 std	%f12, [%g1-448]
.L649:
	mov	1, %g3
	std	%f8, [%fp-448]
	mov	0, %g1
	mov	1, %g2
.L687:
	sll	%g1, 2, %g4
	ldd	[%fp-592], %f8
	add	%g4, %g3, %g4
	sll	%g4, 3, %g4
	add	%fp, %g4, %g4
	cmp	%g3, 1
	be	.L689
	 std	%f8, [%g4-448]
	mov	%g1, %g2
	b	.L652
	 mov	1, %g1
.L695:
	cmp	%i3, 2
	be	.L658
	 mov	1, %g1
.L735:
	b	.L655
	 sll	%g2, 2, %g3
.L694:
	b	.L654
	 mov	1, %g1
.L739:
	ldd	[%i0+48], %f8
	cmp	%i1, 3
	bne	.L697
	 std	%f8, [%fp-560]
	mov	1, %i5
	mov	0, %g3
	mov	1, %g1
	mov	4, %g2
	add	%g2, %g3, %g3
.L740:
	ldd	[%i0+64], %f8
	sll	%g3, 3, %g3
	add	%fp, %g3, %g3
	std	%f8, [%g3-576]
	cmp	%i5, 2
	ble	.L668
	 add	%i5, 1, %g4
	add	%g1, 1, %g1
	mov	1, %g4
	mov	0, %i5
	sll	%g1, 2, %g2
.L668:
	cmp	%i1, 1
	bne,a	.L736
	 mov	%i5, %g3
	add	%g2, %i5, %g3
.L741:
	ldd	[%i0+80], %f8
	sll	%g3, 3, %g3
	add	%fp, %g3, %g3
	std	%f8, [%g3-576]
	cmp	%g4, 2
	ble	.L674
	 add	%g4, 1, %g3
	add	%g1, 1, %g1
	mov	1, %g3
	mov	0, %g4
	sll	%g1, 2, %g2
.L674:
	cmp	%i1, 3
	bne,a	.L737
	 mov	%g4, %i5
	add	%g2, %g4, %g4
.L742:
	ldd	[%i0+96], %f8
	sll	%g4, 3, %g4
	add	%fp, %g4, %g4
	std	%f8, [%g4-576]
	cmp	%g3, 3
	bne	.L680
	 add	%g3, 1, %i5
	add	%g1, 1, %g1
	mov	1, %i5
	mov	0, %g3
	sll	%g1, 2, %g2
.L680:
	cmp	%i1, 1
	bne	.L738
	 mov	%g3, %g4
.L681:
	add	%g2, %g3, %g2
	ldd	[%i0+112], %f8
	sll	%g2, 3, %g2
	add	%fp, %g2, %g2
	cmp	%i5, 3
	bne	.L684
	 std	%f8, [%g2-576]
	add	%g1, 1, %g1
	mov	0, %i5
.L684:
	cmp	%i1, 3
	be,a	.L744
	 mov	0, %g1
	mov	%i5, %g3
	b	.L683
	 sll	%g1, 2, %g2
.L660:
	ldd	[%i0+48], %f8
	std	%f10, [%fp-576]
	b	.L690
	 std	%f8, [%fp-568]
.L736:
	b	.L666
	 mov	%g4, %i5
.L732:
	ldd	[%i0+40], %f8
	cmp	%i1, 2
	bne	.L739
	 std	%f8, [%fp-568]
	ldd	[%i0+56], %f8
	mov	0, %g1
	b	.L664
	 std	%f8, [%fp-560]
.L737:
	b	.L672
	 mov	%g3, %g4
.L738:
	b	.L678
	 mov	%i5, %g3
.L697:
	mov	0, %g4
	mov	1, %g1
	b	.L691
	 mov	1, %g3
.L696:
	mov	0, %g3
	mov	1, %g1
	b	.L687
	 mov	2, %g2
	.size	FindDeterminant.constprop.5, .-FindDeterminant.constprop.5
	.section	.rodata.str1.8
	.align 8
.LC51:
	.asciz	"\nInverse of Entered Matrix is not possible\n"
	.section	.rodata.cst8
	.align 8
.LC47:
	.long	0
	.long	0
	.align 8
.LC48:
	.long	1073741824
	.long	0
	.align 8
.LC49:
	.long	1102175864
	.long	1241513984
	.align 8
.LC50:
	.long	1134423871
	.long	1614070530
	.align 8
.LC52:
	.long	1077149696
	.long	0
	.align 8
.LC53:
	.long	1080459264
	.long	0
	.align 8
.LC54:
	.long	1074340347
	.long	1413752350
	.align 8
.LC55:
	.long	1064007514
	.long	2230575400
	.align 8
.LC56:
	.long	1051772663
	.long	2696277389
	.align 8
.LC57:
	.long	1078765020
	.long	442747372
	.align 8
.LC58:
	.long	1072693248
	.long	0
	.align 8
.LC59:
	.long	1096307878
	.long	1073741824
	.section	.text.NavComputeUserPosSixSat,"ax",@progbits
	.align 4
	.global NavComputeUserPosSixSat
	.type	NavComputeUserPosSixSat, #function
	.proc	020
NavComputeUserPosSixSat:
	save	%sp, -1176, %sp
	sethi	%hi(.LC47), %l1
	sethi	%hi(.LC48), %i1
	ldd	[%l1+%lo(.LC47)], %f8
	sethi	%hi(NavprocData), %i5
	fmovs	%f8, %f10
	or	%i5, %lo(NavprocData), %i5
	fmovs	%f9, %f11
	fmovs	%f10, %f12
	fmovs	%f9, %f13
	fmovs	%f10, %f14
	fmovs	%f9, %f15
	sethi	%hi(.LC49), %i2
	sethi	%hi(.LC50), %l4
	sethi	%hi(.LC52), %l3
	mov	10, %i0
	std	%f8, [%fp-864]
	std	%f10, [%fp-752]
	std	%f12, [%fp-744]
	std	%f14, [%fp-736]
	or	%i1, %lo(.LC48), %i3
	or	%i2, %lo(.LC49), %i2
	or	%l1, %lo(.LC47), %l1
	or	%l4, %lo(.LC50), %l4
	or	%l3, %lo(.LC52), %l3
	add	%i5, 188, %l0
.L754:
	ld	[%i5+184], %g1
	cmp	%g1, 0
	ble	.L756
	 mov	0, %i4
	mov	%l0, %l6
	mov	%l0, %l2
	add	%fp, -672, %l7
.L747:
	ld	[%l2], %g1
	ldd	[%fp-736], %f16
	add	%g1, %g1, %g3
	add	%g3, %g1, %g1
	sll	%g1, 3, %l5
	add	%i5, %l5, %l5
	ldd	[%l5+216], %f8
	fsubd	%f16, %f8, %f16
	ldd	[%i3], %o2
	std	%f16, [%fp-1064]
	call	pow, 0
	 ldd	[%fp-1064], %o0
	ldd	[%l5+224], %f10
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%fp-744], %f18
	fsubd	%f18, %f10, %f18
	ldd	[%i3], %o2
	std	%f18, [%fp-1064]
	std	%f8, [%fp-1048]
	call	pow, 0
	 ldd	[%fp-1064], %o0
	ldd	[%l5+232], %f10
	ldd	[%fp-1048], %f8
	ldd	[%fp-752], %f20
	faddd	%f8, %f0, %f8
	fsubd	%f20, %f10, %f20
	ldd	[%i3], %o2
	std	%f20, [%fp-1064]
	std	%f8, [%fp-1048]
	call	pow, 0
	 ldd	[%fp-1064], %o0
	ldd	[%fp-1048], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -688, %o0
	add	%fp, -680, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-688]
	sll	%i4, 3, %g1
	ldd	[%i2], %f10
	ldd	[%fp-864], %f22
	ldd	[%fp-680], %f8
	fmuld	%f22, %f10, %f10
	faddd	%f10, %f8, %f8
	std	%f8, [%l7+%g1]
	add	%i4, 1, %i4
	ld	[%i5+184], %g4
	cmp	%g4, %i4
	bg	.L747
	 add	%l2, 4, %l2
	cmp	%g4, 0
	ble	.L756
	 add	%fp, -192, %g2
	sll	%g4, 2, %o7
	mov	0, %g1
	ldd	[%fp-736], %f16
	ldd	[%fp-744], %f18
	ldd	[%fp-752], %f20
.L748:
	add	%g1, %g1, %i4
	add	%i5, %g1, %g3
	ldd	[%l7+%i4], %f8
	ld	[%g3+188], %g3
	fsubd	%f8, %f10, %f8
	add	%g3, %g3, %i4
	add	%i4, %g3, %g3
	sll	%g3, 3, %g3
	add	%i5, %g3, %g3
	ldd	[%g3+224], %f12
	fsubd	%f18, %f12, %f12
	fdivd	%f12, %f8, %f12
	ldd	[%g3+216], %f14
	std	%f12, [%g2+8]
	fsubd	%f16, %f14, %f14
	ldd	[%g3+232], %f12
	fdivd	%f14, %f8, %f14
	fsubd	%f20, %f12, %f12
	std	%f14, [%g2]
	fdivd	%f12, %f8, %f8
	std	%f8, [%g2+16]
	add	%g1, 4, %g1
	cmp	%g1, %o7
	bne	.L748
	 add	%g2, 32, %g2
	sll	%g4, 3, %g4
	mov	0, %g1
	add	%fp, -624, %g3
	ldd	[%i2], %f12
.L749:
	ld	[%l6], %g2
	ldd	[%l7+%g1], %f8
	add	%g2, 13, %g2
	sll	%g2, 3, %g2
	ldd	[%i5+%g2], %f10
	fmuld	%f10, %f12, %f10
	fsubd	%f10, %f8, %f8
	std	%f8, [%g3+%g1]
	add	%g1, 8, %g1
	cmp	%g1, %g4
	bne	.L749
	 add	%l6, 4, %l6
.L756:
	ldd	[%fp-192], %f26
	ldd	[%fp-184], %f28
	ldd	[%fp-176], %f12
	ldd	[%fp-160], %f14
	ldd	[%fp-152], %f16
	ldd	[%fp-144], %f18
	ldd	[%fp-128], %f20
	ldd	[%fp-120], %f22
	std	%f26, [%fp-792]
	std	%f28, [%fp-808]
	ldd	[%fp-112], %f26
	ldd	[%fp-96], %f28
	std	%f12, [%fp-800]
	std	%f14, [%fp-728]
	ldd	[%fp-88], %f12
	ldd	[%fp-80], %f14
	std	%f16, [%fp-784]
	std	%f18, [%fp-768]
	ldd	[%fp-64], %f16
	ldd	[%fp-56], %f18
	std	%f20, [%fp-760]
	std	%f22, [%fp-720]
	ldd	[%fp-48], %f20
	std	%f26, [%fp-696]
	std	%f28, [%fp-712]
	std	%f12, [%fp-776]
	std	%f14, [%fp-704]
	std	%f16, [%fp-816]
	std	%f18, [%fp-824]
	std	%f20, [%fp-832]
	ldd	[%i2], %f8
	ldd	[%l1], %f10
	ldd	[%fp-32], %f22
	std	%f22, [%fp-840]
	ldd	[%fp-792], %f14
	ldd	[%fp-728], %f16
	fmuld	%f14, %f8, %f12
	fmuld	%f16, %f8, %f14
	ldd	[%fp-24], %f26
	ldd	[%fp-16], %f28
	faddd	%f12, %f10, %f12
	ldd	[%fp-760], %f18
	ldd	[%fp-712], %f20
	fmuld	%f18, %f8, %f16
	faddd	%f12, %f14, %f12
	fmuld	%f20, %f8, %f14
	std	%f26, [%fp-848]
	std	%f28, [%fp-856]
	ldd	[%fp-816], %f22
	ldd	[%fp-840], %f26
	ldd	[%fp-808], %f28
	faddd	%f12, %f16, %f12
	fmuld	%f28, %f8, %f18
	fmuld	%f22, %f8, %f16
	faddd	%f12, %f14, %f12
	fmuld	%f26, %f8, %f14
	faddd	%f12, %f16, %f12
	faddd	%f12, %f14, %f16
	faddd	%f18, %f10, %f14
	ldd	[%fp-784], %f18
	ldd	[%fp-720], %f20
	fmuld	%f18, %f8, %f12
	fmuld	%f20, %f8, %f18
	ldd	[%fp-776], %f22
	ldd	[%fp-824], %f26
	faddd	%f14, %f12, %f12
	fmuld	%f22, %f8, %f14
	faddd	%f12, %f18, %f12
	fmuld	%f26, %f8, %f18
	ldd	[%fp-848], %f28
	faddd	%f12, %f14, %f12
	fmuld	%f28, %f8, %f14
	faddd	%f12, %f18, %f12
	ldd	[%fp-800], %f18
	fmuld	%f18, %f8, %f20
	faddd	%f12, %f14, %f18
	faddd	%f20, %f10, %f14
	ldd	[%fp-768], %f20
	ldd	[%fp-832], %f28
	fmuld	%f20, %f8, %f12
	ldd	[%fp-696], %f22
	ldd	[%fp-704], %f26
	fmuld	%f22, %f8, %f20
	faddd	%f14, %f12, %f12
	ldd	[%fp-856], %f22
	fmuld	%f26, %f8, %f14
	faddd	%f12, %f20, %f12
	ldd	[%fp-792], %f26
	fmuld	%f28, %f8, %f20
	faddd	%f12, %f14, %f12
	fmovs	%f26, %f28
	fmovs	%f27, %f29
	fmuld	%f22, %f8, %f14
	std	%f16, [%fp-552]
	faddd	%f12, %f20, %f8
	ldd	[%fp-760], %f22
	fmuld	%f26, %f28, %f12
	std	%f16, [%fp-480]
	ldd	[%fp-712], %f28
	ldd	[%fp-728], %f16
	faddd	%f12, %f10, %f12
	fmovs	%f16, %f20
	fmovs	%f17, %f21
	fmovs	%f22, %f26
	fmovs	%f23, %f27
	faddd	%f8, %f14, %f14
	std	%f18, [%fp-520]
	fmuld	%f16, %f20, %f8
	std	%f14, [%fp-488]
	fmuld	%f22, %f26, %f16
	fmovs	%f28, %f20
	ldd	[%fp-816], %f22
	fmovs	%f29, %f21
	fmovs	%f22, %f26
	fmovs	%f23, %f27
	faddd	%f12, %f8, %f8
	fmuld	%f28, %f20, %f12
	ldd	[%fp-840], %f28
	faddd	%f8, %f16, %f8
	fmovs	%f28, %f20
	fmuld	%f22, %f26, %f16
	fmovs	%f29, %f21
	ldd	[%fp-808], %f22
	ldd	[%fp-792], %f26
	faddd	%f8, %f12, %f8
	fmuld	%f28, %f20, %f12
	faddd	%f8, %f16, %f8
	faddd	%f8, %f12, %f8
	std	%f8, [%fp-576]
	ldd	[%fp-784], %f28
	fmuld	%f22, %f26, %f16
	ldd	[%fp-728], %f12
	faddd	%f16, %f10, %f16
	fmuld	%f28, %f12, %f8
	ldd	[%fp-720], %f20
	ldd	[%fp-760], %f22
	ldd	[%fp-712], %f26
	ldd	[%fp-776], %f28
	fmuld	%f20, %f22, %f12
	faddd	%f16, %f8, %f8
	ldd	[%fp-816], %f20
	fmuld	%f26, %f28, %f16
	ldd	[%fp-824], %f22
	ldd	[%fp-840], %f26
	ldd	[%fp-848], %f28
	faddd	%f8, %f12, %f8
	fmuld	%f20, %f22, %f12
	faddd	%f8, %f16, %f8
	ldd	[%fp-800], %f20
	fmuld	%f26, %f28, %f16
	ldd	[%fp-792], %f22
	ldd	[%fp-768], %f26
	ldd	[%fp-728], %f28
	faddd	%f8, %f12, %f8
	faddd	%f8, %f16, %f8
	fmuld	%f20, %f22, %f12
	std	%f8, [%fp-568]
	faddd	%f12, %f10, %f12
	ldd	[%fp-696], %f20
	ldd	[%fp-760], %f22
	std	%f8, [%fp-544]
	fmuld	%f26, %f28, %f8
	ldd	[%fp-704], %f26
	ldd	[%fp-712], %f28
	fmuld	%f20, %f22, %f16
	faddd	%f12, %f8, %f8
	ldd	[%fp-832], %f22
	fmuld	%f26, %f28, %f12
	ldd	[%fp-816], %f20
	ldd	[%fp-856], %f28
	ldd	[%fp-840], %f26
	faddd	%f8, %f16, %f8
	fmuld	%f20, %f22, %f16
	faddd	%f8, %f12, %f8
	ldd	[%fp-808], %f20
	fmuld	%f26, %f28, %f12
	fmovs	%f20, %f22
	ldd	[%fp-784], %f26
	fmovs	%f21, %f23
	fmovs	%f26, %f28
	fmovs	%f27, %f29
	faddd	%f8, %f16, %f8
	faddd	%f8, %f12, %f8
	fmuld	%f20, %f22, %f16
	std	%f8, [%fp-560]
	ldd	[%fp-720], %f20
	faddd	%f16, %f10, %f16
	fmovs	%f20, %f22
	fmovs	%f21, %f23
	std	%f8, [%fp-512]
	fmuld	%f26, %f28, %f8
	ldd	[%fp-776], %f26
	fmovs	%f26, %f28
	fmovs	%f27, %f29
	fmuld	%f20, %f22, %f12
	faddd	%f16, %f8, %f8
	ldd	[%fp-824], %f20
	fmuld	%f26, %f28, %f16
	fmovs	%f20, %f22
	ldd	[%fp-848], %f26
	fmovs	%f21, %f23
	fmovs	%f26, %f28
	fmovs	%f27, %f29
	faddd	%f8, %f12, %f8
	fmuld	%f20, %f22, %f12
	faddd	%f8, %f16, %f8
	ldd	[%fp-800], %f20
	fmuld	%f26, %f28, %f16
	ldd	[%fp-808], %f22
	faddd	%f8, %f12, %f8
	faddd	%f8, %f16, %f8
	std	%f8, [%fp-536]
	ldd	[%fp-768], %f26
	ldd	[%fp-784], %f28
	fmuld	%f20, %f22, %f12
	fmuld	%f26, %f28, %f8
	faddd	%f12, %f10, %f12
	ldd	[%fp-696], %f20
	ldd	[%fp-720], %f22
	ldd	[%fp-704], %f26
	fmuld	%f20, %f22, %f16
	ldd	[%fp-776], %f28
	ldd	[%fp-832], %f22
	faddd	%f12, %f8, %f8
	ldd	[%fp-824], %f20
	fmuld	%f26, %f28, %f12
	faddd	%f8, %f16, %f8
	ldd	[%fp-856], %f28
	fmuld	%f20, %f22, %f16
	ldd	[%fp-848], %f26
	ldd	[%fp-800], %f20
	faddd	%f8, %f12, %f8
	fmovs	%f20, %f22
	fmuld	%f26, %f28, %f12
	fmovs	%f21, %f23
	ldd	[%fp-768], %f26
	faddd	%f8, %f16, %f8
	fmovs	%f26, %f28
	fmuld	%f20, %f22, %f16
	faddd	%f8, %f12, %f8
	faddd	%f16, %f10, %f16
	fmovs	%f27, %f29
	ldd	[%fp-696], %f20
	std	%f8, [%fp-528]
	fmovs	%f20, %f22
	fmovs	%f21, %f23
	std	%f8, [%fp-504]
	fmuld	%f20, %f22, %f12
	fmuld	%f26, %f28, %f8
	ldd	[%fp-704], %f26
	faddd	%f16, %f8, %f8
	fmovs	%f26, %f28
	fmovs	%f27, %f29
	fmuld	%f26, %f28, %f16
	ldd	[%fp-832], %f20
	ldd	[%fp-856], %f26
	faddd	%f8, %f12, %f8
	fmovs	%f20, %f22
	fmovs	%f21, %f23
	faddd	%f8, %f16, %f8
	fmuld	%f20, %f22, %f12
	fmovs	%f26, %f28
	fmovs	%f27, %f29
	faddd	%f8, %f12, %f8
	fmuld	%f26, %f28, %f16
	faddd	%f8, %f16, %f8
	std	%f8, [%fp-496]
	ldd	[%l4], %f8
	std	%f10, [%fp-1056]
	std	%f18, [%fp-472]
	add	%fp, -576, %o0
	std	%f14, [%fp-464]
	call	FindDeterminant.constprop.5, 0
	 std	%f8, [%fp-456]
	ldd	[%fp-1056], %f10
	fcmpd	%f0, %f10
	nop
	fbne	.L750
	 std	%f0, [%fp-1040]
	sethi	%hi(.LC51), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC51), %o0
	ldd	[%fp-1040], %f0
.L753:
	ldd	[%fp-248], %f14
	fdivd	%f14, %f0, %f20
	ldd	[%fp-240], %f14
	fdivd	%f14, %f0, %f30
	ldd	[%fp-232], %f14
	fdivd	%f14, %f0, %f2
	ldd	[%fp-224], %f14
	ldd	[%i2], %f26
	fdivd	%f14, %f0, %f28
	fmuld	%f28, %f26, %f14
	std	%f14, [%fp-872]
	ldd	[%fp-216], %f14
	std	%f28, [%fp-424]
	fdivd	%f14, %f0, %f28
	fmuld	%f28, %f26, %f14
	std	%f14, [%fp-880]
	ldd	[%fp-208], %f14
	std	%f28, [%fp-392]
	fdivd	%f14, %f0, %f28
	fmuld	%f28, %f26, %f14
	ldd	[%fp-272], %f10
	std	%f28, [%fp-360]
	std	%f14, [%fp-888]
	ldd	[%fp-200], %f14
	fdivd	%f14, %f0, %f28
	fdivd	%f10, %f0, %f24
	fmuld	%f28, %f26, %f14
	ldd	[%fp-264], %f10
	ldd	[%fp-288], %f12
	std	%f28, [%fp-328]
	fdivd	%f12, %f0, %f12
	ldd	[%fp-792], %f28
	ldd	[%fp-808], %f26
	fmuld	%f26, %f12, %f26
	fdivd	%f10, %f0, %f4
	std	%f26, [%fp-912]
	ldd	[%fp-312], %f16
	ldd	[%fp-304], %f22
	fdivd	%f16, %f0, %f16
	fdivd	%f22, %f0, %f22
	ldd	[%fp-296], %f6
	ldd	[%fp-280], %f18
	fdivd	%f6, %f0, %f6
	fdivd	%f18, %f0, %f18
	ldd	[%fp-256], %f10
	std	%f14, [%fp-896]
	fdivd	%f10, %f0, %f10
	ldd	[%fp-320], %f14
	fdivd	%f14, %f0, %f14
	ldd	[%fp-800], %f0
	fmuld	%f28, %f14, %f26
	fmuld	%f0, %f10, %f0
	ldd	[%fp-728], %f28
	std	%f0, [%fp-904]
	fmuld	%f28, %f14, %f0
	ldd	[%fp-912], %f28
	ldd	[%l1], %f8
	faddd	%f26, %f8, %f26
	faddd	%f26, %f28, %f26
	faddd	%f0, %f8, %f28
	std	%f28, [%fp-912]
	ldd	[%fp-784], %f28
	ldd	[%fp-904], %f0
	faddd	%f26, %f0, %f0
	fmuld	%f28, %f12, %f26
	ldd	[%fp-912], %f28
	std	%f0, [%fp-904]
	faddd	%f28, %f26, %f26
	ldd	[%fp-768], %f0
	ldd	[%fp-760], %f28
	fmuld	%f0, %f10, %f0
	std	%f0, [%fp-920]
	fmuld	%f28, %f14, %f0
	ldd	[%fp-920], %f28
	faddd	%f26, %f28, %f28
	faddd	%f0, %f8, %f26
	std	%f28, [%fp-912]
	ldd	[%fp-696], %f0
	ldd	[%fp-720], %f28
	fmuld	%f0, %f10, %f0
	std	%f26, [%fp-920]
	std	%f0, [%fp-928]
	fmuld	%f28, %f12, %f26
	ldd	[%fp-712], %f0
	ldd	[%fp-920], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f14, %f28
	ldd	[%fp-928], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-920]
	ldd	[%fp-776], %f28
	ldd	[%fp-704], %f0
	fmuld	%f0, %f10, %f0
	std	%f26, [%fp-928]
	std	%f0, [%fp-936]
	fmuld	%f28, %f12, %f26
	ldd	[%fp-816], %f0
	ldd	[%fp-928], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f14, %f28
	ldd	[%fp-936], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-928]
	ldd	[%fp-824], %f28
	ldd	[%fp-832], %f0
	fmuld	%f0, %f10, %f0
	std	%f26, [%fp-936]
	std	%f0, [%fp-944]
	fmuld	%f28, %f12, %f26
	ldd	[%fp-840], %f0
	ldd	[%fp-936], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f14, %f28
	ldd	[%fp-944], %f0
	faddd	%f26, %f0, %f0
	std	%f0, [%fp-936]
	faddd	%f28, %f8, %f26
	std	%f26, [%fp-944]
	ldd	[%fp-848], %f28
	ldd	[%fp-856], %f0
	fmuld	%f0, %f10, %f0
	fmuld	%f28, %f12, %f26
	std	%f0, [%fp-952]
	ldd	[%fp-944], %f28
	ldd	[%fp-792], %f0
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f16, %f28
	ldd	[%fp-952], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-944]
	ldd	[%fp-808], %f28
	ldd	[%fp-800], %f0
	fmuld	%f0, %f20, %f0
	std	%f26, [%fp-952]
	std	%f0, [%fp-960]
	fmuld	%f28, %f18, %f26
	ldd	[%fp-728], %f0
	ldd	[%fp-952], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f16, %f28
	ldd	[%fp-960], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-952]
	ldd	[%fp-784], %f28
	ldd	[%fp-768], %f0
	fmuld	%f0, %f20, %f0
	std	%f26, [%fp-960]
	std	%f0, [%fp-968]
	fmuld	%f28, %f18, %f26
	ldd	[%fp-760], %f0
	ldd	[%fp-960], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f16, %f28
	ldd	[%fp-968], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-960]
	ldd	[%fp-720], %f28
	ldd	[%fp-696], %f0
	fmuld	%f0, %f20, %f0
	std	%f26, [%fp-968]
	std	%f0, [%fp-976]
	fmuld	%f28, %f18, %f26
	ldd	[%fp-712], %f0
	ldd	[%fp-968], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f16, %f28
	ldd	[%fp-976], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-968]
	ldd	[%fp-776], %f28
	std	%f26, [%fp-976]
	ldd	[%fp-704], %f0
	fmuld	%f0, %f20, %f0
	fmuld	%f28, %f18, %f26
	std	%f0, [%fp-984]
	ldd	[%fp-976], %f28
	ldd	[%fp-816], %f0
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f16, %f28
	ldd	[%fp-984], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-976]
	ldd	[%fp-824], %f28
	ldd	[%fp-832], %f0
	fmuld	%f0, %f20, %f0
	std	%f26, [%fp-984]
	std	%f0, [%fp-992]
	fmuld	%f28, %f18, %f26
	ldd	[%fp-840], %f0
	ldd	[%fp-984], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f16, %f28
	ldd	[%fp-992], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-984]
	ldd	[%fp-848], %f28
	ldd	[%fp-856], %f0
	fmuld	%f0, %f20, %f0
	std	%f26, [%fp-992]
	std	%f0, [%fp-1000]
	fmuld	%f28, %f18, %f26
	ldd	[%fp-792], %f0
	ldd	[%fp-992], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f22, %f28
	ldd	[%fp-1000], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-992]
	ldd	[%fp-808], %f28
	ldd	[%fp-800], %f0
	fmuld	%f0, %f30, %f0
	std	%f26, [%fp-1000]
	std	%f0, [%fp-1008]
	fmuld	%f28, %f24, %f26
	ldd	[%fp-728], %f0
	ldd	[%fp-1000], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f22, %f28
	ldd	[%fp-1008], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-1000]
	ldd	[%fp-784], %f28
	ldd	[%fp-768], %f0
	fmuld	%f0, %f30, %f0
	std	%f26, [%fp-1008]
	std	%f0, [%fp-1016]
	fmuld	%f28, %f24, %f26
	ldd	[%fp-760], %f0
	ldd	[%fp-1008], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f22, %f28
	ldd	[%fp-1016], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-1008]
	ldd	[%fp-720], %f28
	ldd	[%fp-696], %f0
	fmuld	%f0, %f30, %f0
	std	%f26, [%fp-1016]
	std	%f0, [%fp-1024]
	fmuld	%f28, %f24, %f26
	ldd	[%fp-712], %f0
	ldd	[%fp-1016], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f22, %f28
	ldd	[%fp-1024], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-1016]
	ldd	[%fp-776], %f28
	ldd	[%fp-704], %f0
	fmuld	%f0, %f30, %f0
	std	%f26, [%fp-1024]
	std	%f0, [%fp-1032]
	fmuld	%f28, %f24, %f26
	ldd	[%fp-816], %f0
	ldd	[%fp-1024], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f22, %f28
	ldd	[%fp-1032], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-1024]
	ldd	[%fp-824], %f28
	ldd	[%fp-832], %f0
	fmuld	%f0, %f30, %f0
	std	%f26, [%fp-1032]
	std	%f0, [%fp-1072]
	fmuld	%f28, %f24, %f26
	ldd	[%fp-840], %f0
	ldd	[%fp-1032], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f22, %f28
	ldd	[%fp-1072], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-1032]
	ldd	[%fp-848], %f28
	ldd	[%fp-856], %f0
	fmuld	%f0, %f30, %f0
	std	%f26, [%fp-1072]
	std	%f0, [%fp-1080]
	fmuld	%f28, %f24, %f26
	ldd	[%fp-792], %f0
	ldd	[%fp-1072], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f6, %f28
	ldd	[%fp-1080], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-792]
	ldd	[%fp-808], %f28
	std	%f26, [%fp-1072]
	ldd	[%fp-800], %f0
	fmuld	%f0, %f2, %f0
	fmuld	%f28, %f4, %f26
	std	%f0, [%fp-800]
	ldd	[%fp-728], %f0
	ldd	[%fp-1072], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f6, %f28
	ldd	[%fp-800], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-728]
	ldd	[%fp-784], %f28
	ldd	[%fp-768], %f0
	fmuld	%f0, %f2, %f0
	std	%f26, [%fp-800]
	std	%f0, [%fp-768]
	fmuld	%f28, %f4, %f26
	ldd	[%fp-760], %f0
	ldd	[%fp-800], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f6, %f28
	ldd	[%fp-768], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-760]
	ldd	[%fp-720], %f28
	ldd	[%fp-696], %f0
	fmuld	%f0, %f2, %f0
	std	%f26, [%fp-768]
	std	%f0, [%fp-696]
	fmuld	%f28, %f4, %f26
	ldd	[%fp-712], %f0
	ldd	[%fp-768], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f6, %f28
	ldd	[%fp-696], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-712]
	ldd	[%fp-776], %f28
	ldd	[%fp-704], %f0
	fmuld	%f0, %f2, %f0
	std	%f26, [%fp-696]
	std	%f0, [%fp-704]
	fmuld	%f28, %f4, %f26
	ldd	[%fp-816], %f0
	ldd	[%fp-696], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f6, %f28
	ldd	[%fp-704], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-720]
	ldd	[%fp-824], %f28
	ldd	[%fp-832], %f0
	fmuld	%f0, %f2, %f0
	std	%f26, [%fp-696]
	std	%f0, [%fp-704]
	fmuld	%f28, %f4, %f26
	ldd	[%fp-840], %f0
	ldd	[%fp-696], %f28
	faddd	%f28, %f26, %f26
	fmuld	%f0, %f6, %f28
	ldd	[%fp-704], %f0
	faddd	%f26, %f0, %f0
	faddd	%f28, %f8, %f26
	std	%f0, [%fp-768]
	std	%f26, [%fp-696]
	ldd	[%fp-848], %f28
	ldd	[%fp-856], %f0
	fmuld	%f28, %f4, %f26
	fmuld	%f0, %f2, %f0
	ldd	[%fp-696], %f28
	std	%f0, [%fp-704]
	faddd	%f28, %f26, %f28
	ldd	[%fp-904], %f0
	ldd	[%fp-872], %f26
	std	%f28, [%fp-696]
	faddd	%f0, %f26, %f28
	ldd	[%fp-704], %f26
	ldd	[%fp-696], %f0
	faddd	%f0, %f26, %f0
	std	%f0, [%fp-776]
	ldd	[%fp-624], %f0
	ldd	[%fp-872], %f26
	fmuld	%f28, %f0, %f28
	ldd	[%fp-912], %f0
	faddd	%f26, %f0, %f26
	ldd	[%fp-616], %f0
	std	%f26, [%fp-704]
	faddd	%f28, %f8, %f26
	ldd	[%fp-704], %f28
	fmuld	%f28, %f0, %f28
	std	%f26, [%fp-696]
	std	%f28, [%fp-704]
	ldd	[%fp-872], %f26
	ldd	[%fp-920], %f28
	faddd	%f26, %f28, %f0
	ldd	[%fp-704], %f28
	ldd	[%fp-696], %f26
	faddd	%f26, %f28, %f26
	std	%f26, [%fp-696]
	ldd	[%fp-608], %f26
	ldd	[%fp-872], %f28
	fmuld	%f0, %f26, %f0
	ldd	[%fp-928], %f26
	faddd	%f28, %f26, %f28
	ldd	[%fp-600], %f26
	std	%f28, [%fp-704]
	ldd	[%fp-696], %f28
	faddd	%f28, %f0, %f28
	ldd	[%fp-704], %f0
	std	%f28, [%fp-696]
	fmuld	%f0, %f26, %f0
	ldd	[%fp-872], %f28
	ldd	[%fp-936], %f26
	std	%f0, [%fp-704]
	faddd	%f28, %f26, %f0
	ldd	[%fp-704], %f26
	ldd	[%fp-696], %f28
	faddd	%f28, %f26, %f28
	std	%f28, [%fp-696]
	ldd	[%fp-592], %f28
	ldd	[%fp-872], %f26
	fmuld	%f0, %f28, %f0
	ldd	[%fp-944], %f28
	faddd	%f26, %f28, %f26
	std	%f26, [%fp-704]
	ldd	[%fp-696], %f26
	ldd	[%fp-704], %f28
	faddd	%f26, %f0, %f26
	ldd	[%fp-584], %f0
	fmuld	%f28, %f0, %f28
	std	%f26, [%fp-696]
	std	%f28, [%fp-704]
	ldd	[%fp-952], %f26
	ldd	[%fp-880], %f28
	faddd	%f26, %f28, %f0
	ldd	[%fp-696], %f26
	ldd	[%fp-704], %f28
	faddd	%f26, %f28, %f26
	std	%f26, [%fp-704]
	ldd	[%fp-624], %f26
	ldd	[%fp-880], %f28
	fmuld	%f0, %f26, %f0
	ldd	[%fp-960], %f26
	faddd	%f28, %f26, %f28
	ldd	[%fp-616], %f26
	std	%f28, [%fp-784]
	faddd	%f0, %f8, %f28
	ldd	[%fp-784], %f0
	std	%f28, [%fp-696]
	fmuld	%f0, %f26, %f28
	ldd	[%fp-968], %f26
	ldd	[%fp-880], %f0
	faddd	%f0, %f26, %f0
	std	%f0, [%fp-784]
	ldd	[%fp-696], %f0
	ldd	[%fp-784], %f26
	faddd	%f0, %f28, %f0
	ldd	[%fp-608], %f28
	std	%f0, [%fp-696]
	fmuld	%f26, %f28, %f0
	ldd	[%fp-976], %f28
	ldd	[%fp-880], %f26
	faddd	%f26, %f28, %f26
	std	%f26, [%fp-784]
	ldd	[%fp-696], %f26
	faddd	%f26, %f0, %f26
	ldd	[%fp-784], %f28
	std	%f26, [%fp-696]
	ldd	[%fp-600], %f26
	fmuld	%f28, %f26, %f0
	ldd	[%fp-984], %f26
	ldd	[%fp-880], %f28
	faddd	%f28, %f26, %f28
	std	%f28, [%fp-784]
	ldd	[%fp-696], %f28
	faddd	%f28, %f0, %f28
	ldd	[%fp-784], %f26
	std	%f28, [%fp-696]
	ldd	[%fp-592], %f28
	fmuld	%f26, %f28, %f0
	ldd	[%fp-992], %f28
	ldd	[%fp-880], %f26
	faddd	%f26, %f28, %f26
	std	%f26, [%fp-800]
	ldd	[%fp-696], %f26
	ldd	[%fp-800], %f28
	faddd	%f26, %f0, %f26
	ldd	[%fp-584], %f0
	fmuld	%f28, %f0, %f28
	std	%f26, [%fp-784]
	std	%f28, [%fp-808]
	ldd	[%fp-1000], %f26
	ldd	[%fp-888], %f28
	faddd	%f26, %f28, %f26
	std	%f26, [%fp-696]
	ldd	[%fp-1008], %f26
	faddd	%f28, %f26, %f0
	ldd	[%fp-696], %f28
	ldd	[%fp-624], %f26
	fmuld	%f28, %f26, %f28
	std	%f28, [%fp-696]
	ldd	[%fp-616], %f28
	fmuld	%f0, %f28, %f28
	ldd	[%fp-696], %f0
	std	%f28, [%fp-800]
	ldd	[%fp-888], %f26
	faddd	%f0, %f8, %f28
	ldd	[%fp-1016], %f0
	faddd	%f26, %f0, %f26
	std	%f26, [%fp-696]
	ldd	[%fp-800], %f26
	faddd	%f28, %f26, %f26
	ldd	[%fp-696], %f28
	std	%f26, [%fp-800]
	ldd	[%fp-608], %f26
	fmuld	%f28, %f26, %f0
	ldd	[%fp-1024], %f26
	ldd	[%fp-888], %f28
	faddd	%f28, %f26, %f28
	std	%f28, [%fp-696]
	ldd	[%fp-800], %f28
	faddd	%f28, %f0, %f28
	std	%f28, [%fp-800]
	ldd	[%fp-696], %f26
	ldd	[%fp-600], %f28
	fmuld	%f26, %f28, %f0
	ldd	[%fp-1032], %f28
	ldd	[%fp-888], %f26
	faddd	%f26, %f28, %f26
	std	%f26, [%fp-696]
	ldd	[%fp-800], %f26
	faddd	%f26, %f0, %f26
	ldd	[%fp-696], %f28
	std	%f26, [%fp-800]
	ldd	[%fp-592], %f26
	fmuld	%f28, %f26, %f0
	ldd	[%fp-792], %f26
	ldd	[%fp-888], %f28
	faddd	%f28, %f26, %f28
	std	%f28, [%fp-696]
	ldd	[%fp-800], %f28
	faddd	%f28, %f0, %f28
	ldd	[%fp-696], %f26
	std	%f28, [%fp-792]
	ldd	[%fp-584], %f28
	fmuld	%f26, %f28, %f0
	ldd	[%fp-728], %f26
	ldd	[%fp-896], %f28
	faddd	%f26, %f28, %f26
	std	%f26, [%fp-728]
	ldd	[%fp-792], %f26
	faddd	%f26, %f0, %f26
	ldd	[%fp-728], %f28
	ldd	[%fp-624], %f0
	std	%f26, [%fp-696]
	fmuld	%f28, %f0, %f28
	ldd	[%fp-896], %f26
	std	%f28, [%fp-728]
	ldd	[%fp-760], %f28
	faddd	%f26, %f28, %f0
	ldd	[%fp-728], %f26
	faddd	%f26, %f8, %f26
	ldd	[%fp-616], %f28
	std	%f26, [%fp-728]
	ldd	[%fp-896], %f8
	ldd	[%fp-712], %f26
	fmuld	%f0, %f28, %f0
	faddd	%f8, %f26, %f28
	ldd	[%fp-608], %f26
	ldd	[%fp-728], %f8
	faddd	%f8, %f0, %f8
	fmuld	%f28, %f26, %f28
	std	%f8, [%fp-712]
	ldd	[%fp-720], %f26
	ldd	[%fp-896], %f8
	faddd	%f8, %f26, %f0
	ldd	[%fp-712], %f8
	faddd	%f8, %f28, %f8
	std	%f8, [%fp-712]
	ldd	[%fp-600], %f26
	ldd	[%fp-896], %f8
	fmuld	%f0, %f26, %f0
	ldd	[%fp-768], %f26
	faddd	%f8, %f26, %f28
	ldd	[%fp-712], %f8
	ldd	[%fp-592], %f26
	faddd	%f8, %f0, %f8
	fmuld	%f28, %f26, %f28
	std	%f8, [%fp-712]
	ldd	[%fp-776], %f26
	ldd	[%fp-896], %f8
	std	%f12, [%fp-440]
	faddd	%f8, %f26, %f0
	ldd	[%fp-808], %f12
	ldd	[%fp-712], %f26
	std	%f10, [%fp-432]
	faddd	%f26, %f28, %f8
	ldd	[%fp-784], %f10
	ldd	[%fp-584], %f28
	faddd	%f10, %f12, %f10
	fmuld	%f0, %f28, %f0
	faddd	%f8, %f0, %f8
	std	%f14, [%fp-448]
	std	%f8, [%fp-1048]
	std	%f16, [%fp-416]
	std	%f18, [%fp-408]
	std	%f20, [%fp-400]
	std	%f22, [%fp-384]
	std	%f24, [%fp-376]
	std	%f30, [%fp-368]
	std	%f6, [%fp-352]
	std	%f4, [%fp-344]
	std	%f2, [%fp-336]
	std	%f10, [%fp-712]
	ldd	[%i3], %o2
	call	pow, 0
	 ldd	[%fp-704], %o0
	fmovs	%f0, %f10
	fmovs	%f1, %f11
	ldd	[%fp-712], %o0
	ldd	[%i3], %o2
	call	pow, 0
	 std	%f10, [%fp-1056]
	ldd	[%fp-1056], %f10
	faddd	%f10, %f0, %f10
	ldd	[%fp-696], %o0
	ldd	[%i3], %o2
	call	pow, 0
	 std	%f10, [%fp-1056]
	ldd	[%fp-1056], %f10
	faddd	%f10, %f0, %f0
	add	%fp, -688, %o0
	add	%fp, -680, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-688]
	ldd	[%l3], %f12
	ldd	[%fp-680], %f10
	fcmped	%f10, %f12
	nop
	fbule	.L752
	 ldd	[%fp-1048], %f8
	ldd	[%fp-736], %f14
	ldd	[%fp-744], %f18
	ldd	[%fp-752], %f22
	ldd	[%fp-864], %f28
	ldd	[%fp-704], %f16
	ldd	[%fp-712], %f20
	faddd	%f14, %f16, %f14
	faddd	%f18, %f20, %f18
	ldd	[%fp-696], %f26
	faddd	%f28, %f8, %f28
	faddd	%f22, %f26, %f22
	std	%f14, [%fp-736]
	std	%f18, [%fp-744]
	std	%f22, [%fp-752]
	add	%i0, -1, %i0
	andcc	%i0, 0xff, %g0
	bne	.L754
	 std	%f28, [%fp-864]
.L752:
	sethi	%hi(zftemp), %g1
	ldd	[%fp-864], %f8
	ldd	[%i1+%lo(.LC48)], %o2
	std	%f8, [%g1+%lo(zftemp)]
	call	pow, 0
	 ldd	[%fp-736], %o0
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%fp-744], %o0
	ldd	[%i1+%lo(.LC48)], %o2
	call	pow, 0
	 std	%f8, [%fp-1048]
	ldd	[%fp-1048], %f8
	faddd	%f8, %f0, %f8
	ldd	[%fp-752], %o0
	ldd	[%i1+%lo(.LC48)], %o2
	call	pow, 0
	 std	%f8, [%fp-1048]
	ldd	[%fp-1048], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -688, %o0
	add	%fp, -680, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-688]
	ldd	[%fp-680], %f10
	ldd	[%i1+%lo(.LC48)], %o2
	std	%f10, [%fp-696]
	call	pow, 0
	 ldd	[%fp-736], %o0
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%fp-744], %o0
	ldd	[%i1+%lo(.LC48)], %o2
	call	pow, 0
	 std	%f8, [%fp-1048]
	ldd	[%fp-1048], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -688, %o0
	add	%fp, -680, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-688]
	ldd	[%fp-752], %o0
	call	atan2, 0
	 ldd	[%fp-680], %o2
	ldd	[%fp-744], %o0
	std	%f0, [%fp-712]
	ldd	[%fp-736], %o2
	call	atan2, 0
	 std	%f0, [%fp-704]
	sethi	%hi(.LC53), %g1
	sethi	%hi(.LC56), %i3
	ldd	[%g1+%lo(.LC53)], %f8
	or	%i3, %lo(.LC56), %i3
	fmuld	%f0, %f8, %f0
	sethi	%hi(.LC54), %g1
	ldd	[%g1+%lo(.LC54)], %f10
	fdivd	%f0, %f10, %f12
	std	%f12, [%fp-720]
	ldd	[%fp-704], %f14
.L762:
	fmovs	%f14, %f16
	fmovs	%f15, %f17
	faddd	%f14, %f16, %f14
	std	%f14, [%fp-1064]
	call	sin, 0
	 ldd	[%fp-1064], %o0
	sethi	%hi(.LC55), %g1
	ldd	[%fp-712], %f10
	ldd	[%g1+%lo(.LC55)], %f18
	ldd	[%fp-704], %f12
	fmuld	%f0, %f18, %f0
	faddd	%f0, %f10, %f8
	fsubd	%f12, %f8, %f12
	std	%f8, [%fp-704]
	std	%f12, [%fp-1064]
	call	fabs, 0
	 ldd	[%fp-1064], %o0
	ldd	[%i3], %f8
	fcmped	%f0, %f8
	nop
	fbg	.L762
	 ldd	[%fp-704], %f14
	call	sin, 0
	 ldd	[%fp-704], %o0
	ldd	[%i1+%lo(.LC48)], %o2
	std	%f0, [%fp-1064]
	call	pow, 0
	 ldd	[%fp-1064], %o0
	sethi	%hi(.LC55), %g1
	ldd	[%g1+%lo(.LC55)], %f14
	sethi	%hi(.LC57), %g1
	ldd	[%fp-704], %f8
	ldd	[%g1+%lo(.LC57)], %f10
	sethi	%hi(.LC58), %g1
	fmuld	%f0, %f14, %f0
	fmuld	%f8, %f10, %f10
	ldd	[%g1+%lo(.LC58)], %f12
	ldd	[%fp-736], %f14
	fsubd	%f12, %f0, %f12
	sethi	%hi(.LC59), %g1
	ldd	[%fp-744], %f16
	ldd	[%g1+%lo(.LC59)], %f8
	ldd	[%fp-696], %f18
	fmuld	%f12, %f8, %f8
	ldd	[%fp-752], %f20
	fsubd	%f18, %f8, %f8
	ldd	[%fp-720], %f22
	add	%fp, -448, %o0
	std	%f14, [%i5+696]
	std	%f16, [%i5+704]
	std	%f20, [%i5+712]
	std	%f22, [%i5+720]
	std	%f10, [%i5+728]
	call	NavComputeDOP.constprop.1, 0
	 std	%f8, [%i5+736]
	jmp	%i7+8
	 restore
.L750:
	add	%fp, -576, %o0
	call	FindCoFactor.constprop.3, 0
	 add	%fp, -320, %o1
	b	.L753
	 ldd	[%fp-1040], %f0
	.size	NavComputeUserPosSixSat, .-NavComputeUserPosSixSat
	.section	.rodata.cst8
	.align 8
.LC60:
	.long	0
	.long	0
	.align 8
.LC61:
	.long	1073741824
	.long	0
	.align 8
.LC62:
	.long	1077149696
	.long	0
	.align 8
.LC63:
	.long	1080459264
	.long	0
	.align 8
.LC64:
	.long	1074340347
	.long	1413752350
	.align 8
.LC65:
	.long	1064007514
	.long	2230575400
	.align 8
.LC66:
	.long	1051772663
	.long	2696277389
	.align 8
.LC67:
	.long	1078765020
	.long	442747372
	.align 8
.LC68:
	.long	1072693248
	.long	0
	.align 8
.LC69:
	.long	1096307878
	.long	1073741824
	.section	.text.NavComputeUserPosFourSat,"ax",@progbits
	.align 4
	.global NavComputeUserPosFourSat
	.type	NavComputeUserPosFourSat, #function
	.proc	020
NavComputeUserPosFourSat:
	save	%sp, -552, %sp
	sethi	%hi(.LC60), %i3
	sethi	%hi(.LC61), %i2
	sethi	%hi(NavprocData), %i4
	sethi	%hi(.LC62), %l3
	sethi	%hi(.LC42), %l1
	sethi	%hi(.LC51), %l2
	or	%i3, %lo(.LC60), %i1
	mov	10, %i0
	or	%i4, %lo(NavprocData), %i4
	or	%i2, %lo(.LC61), %i5
	or	%l3, %lo(.LC62), %l3
	or	%l1, %lo(.LC42), %l1
	or	%l2, %lo(.LC51), %l2
	ld	[%i4+188], %g1
.L772:
	add	%g1, %g1, %g2
	add	%g2, %g1, %g1
	sll	%g1, 3, %l0
	sethi	%hi(.LC60), %g1
	add	%i4, %l0, %l0
	ldd	[%g1+%lo(.LC60)], %f10
	ldd	[%l0+216], %f8
	fsubd	%f10, %f8, %f10
	ldd	[%i5], %o2
	std	%f10, [%fp-456]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%l0+224], %f10
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	sethi	%hi(.LC60), %g1
	ldd	[%g1+%lo(.LC60)], %f12
	fsubd	%f12, %f10, %f12
	ldd	[%i5], %o2
	std	%f12, [%fp-456]
	std	%f8, [%fp-448]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%l0+232], %f10
	sethi	%hi(.LC60), %g1
	ldd	[%fp-448], %f8
	ldd	[%g1+%lo(.LC60)], %f12
	faddd	%f8, %f0, %f8
	fsubd	%f12, %f10, %f12
	ldd	[%i5], %o2
	std	%f12, [%fp-456]
	std	%f8, [%fp-448]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%fp-448], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -400, %o0
	add	%fp, -392, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-400]
	ld	[%i4+192], %g1
	add	%g1, %g1, %g2
	add	%g2, %g1, %g1
	sll	%g1, 3, %l0
	sethi	%hi(.LC60), %g1
	add	%i4, %l0, %l0
	ldd	[%g1+%lo(.LC60)], %f10
	ldd	[%l0+216], %f8
	fsubd	%f10, %f8, %f10
	ldd	[%i5], %o2
	std	%f10, [%fp-456]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%l0+224], %f10
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	sethi	%hi(.LC60), %g1
	ldd	[%g1+%lo(.LC60)], %f12
	fsubd	%f12, %f10, %f12
	ldd	[%i5], %o2
	std	%f12, [%fp-456]
	std	%f8, [%fp-448]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%l0+232], %f10
	sethi	%hi(.LC60), %g1
	ldd	[%fp-448], %f8
	ldd	[%g1+%lo(.LC60)], %f12
	faddd	%f8, %f0, %f8
	fsubd	%f12, %f10, %f12
	ldd	[%i5], %o2
	std	%f12, [%fp-456]
	std	%f8, [%fp-448]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%fp-448], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -400, %o0
	add	%fp, -392, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-400]
	ld	[%i4+196], %g1
	add	%g1, %g1, %g2
	add	%g2, %g1, %g1
	sll	%g1, 3, %l0
	sethi	%hi(.LC60), %g1
	add	%i4, %l0, %l0
	ldd	[%g1+%lo(.LC60)], %f10
	ldd	[%l0+216], %f8
	fsubd	%f10, %f8, %f10
	ldd	[%i5], %o2
	std	%f10, [%fp-456]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%l0+224], %f10
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	sethi	%hi(.LC60), %g1
	ldd	[%g1+%lo(.LC60)], %f12
	fsubd	%f12, %f10, %f12
	ldd	[%i5], %o2
	std	%f12, [%fp-456]
	std	%f8, [%fp-448]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%l0+232], %f10
	sethi	%hi(.LC60), %g1
	ldd	[%fp-448], %f8
	ldd	[%g1+%lo(.LC60)], %f12
	faddd	%f8, %f0, %f8
	fsubd	%f12, %f10, %f12
	ldd	[%i5], %o2
	std	%f12, [%fp-456]
	std	%f8, [%fp-448]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%fp-448], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -400, %o0
	add	%fp, -392, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-400]
	ld	[%i4+200], %g1
	add	%g1, %g1, %g2
	add	%g2, %g1, %g1
	sll	%g1, 3, %l0
	sethi	%hi(.LC60), %g1
	add	%i4, %l0, %l0
	ldd	[%g1+%lo(.LC60)], %f10
	ldd	[%l0+216], %f8
	fsubd	%f10, %f8, %f10
	ldd	[%i5], %o2
	std	%f10, [%fp-456]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%l0+224], %f10
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	sethi	%hi(.LC60), %g1
	ldd	[%g1+%lo(.LC60)], %f12
	fsubd	%f12, %f10, %f12
	ldd	[%i5], %o2
	std	%f12, [%fp-456]
	std	%f8, [%fp-448]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%l0+232], %f10
	sethi	%hi(.LC60), %g1
	ldd	[%fp-448], %f8
	ldd	[%g1+%lo(.LC60)], %f12
	faddd	%f8, %f0, %f8
	fsubd	%f12, %f10, %f12
	ldd	[%i5], %o2
	std	%f12, [%fp-456]
	std	%f8, [%fp-448]
	call	pow, 0
	 ldd	[%fp-456], %o0
	ldd	[%fp-448], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -392, %o1
	std	%f0, [%fp-400]
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -400, %o0
	call	ee_printf, 0
	 mov	%l1, %o0
	call	FindDeterminant.constprop.5, 0
	 add	%fp, -384, %o0
	sethi	%hi(.LC60), %g1
	ldd	[%g1+%lo(.LC60)], %f8
	fcmpd	%f0, %f8
	nop
	fbne	.L764
	 std	%f0, [%fp-440]
	call	ee_printf, 0
	 mov	%l2, %o0
	ldd	[%fp-440], %f0
.L767:
	ldd	[%fp-120], %f8
	fdivd	%f8, %f0, %f18
	ldd	[%fp-88], %f8
	fdivd	%f8, %f0, %f20
	ldd	[%fp-56], %f8
	fdivd	%f8, %f0, %f22
	ldd	[%fp-24], %f8
	fdivd	%f8, %f0, %f24
	ldd	[%fp-112], %f8
	fdivd	%f8, %f0, %f26
	ldd	[%fp-80], %f8
	fdivd	%f8, %f0, %f28
	ldd	[%fp-48], %f8
	fdivd	%f8, %f0, %f30
	ldd	[%fp-16], %f8
	fdivd	%f8, %f0, %f6
	ldd	[%fp-104], %f8
	fdivd	%f8, %f0, %f4
	ldd	[%fp-72], %f8
	fdivd	%f8, %f0, %f2
	ldd	[%fp-40], %f8
	fdivd	%f8, %f0, %f8
	ldd	[%fp-96], %f12
	ldd	[%fp-128], %f14
	fdivd	%f12, %f0, %f12
	fdivd	%f14, %f0, %f14
	ldd	[%fp-64], %f10
	ldd	[%fp-32], %f16
	fdivd	%f10, %f0, %f10
	fdivd	%f16, %f0, %f16
	std	%f8, [%fp-144]
	ldd	[%fp-8], %f8
	fdivd	%f8, %f0, %f8
	std	%f10, [%fp-240]
	std	%f14, [%fp-256]
	std	%f12, [%fp-248]
	std	%f16, [%fp-232]
	std	%f18, [%fp-224]
	std	%f20, [%fp-216]
	std	%f22, [%fp-208]
	std	%f24, [%fp-200]
	std	%f26, [%fp-192]
	std	%f28, [%fp-184]
	std	%f30, [%fp-176]
	std	%f6, [%fp-168]
	std	%f4, [%fp-160]
	std	%f2, [%fp-152]
	std	%f8, [%fp-136]
	call	ee_printf, 0
	 mov	%l1, %o0
	ldd	[%i1], %o0
	call	pow, 0
	 ldd	[%i5], %o2
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%i1], %o0
	ldd	[%i5], %o2
	call	pow, 0
	 std	%f8, [%fp-448]
	ldd	[%fp-448], %f8
	faddd	%f8, %f0, %f8
	ldd	[%i1], %o0
	ldd	[%i5], %o2
	call	pow, 0
	 std	%f8, [%fp-448]
	ldd	[%fp-448], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -400, %o0
	add	%fp, -392, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-400]
	ldd	[%l3], %f10
	ldd	[%fp-392], %f8
	fcmped	%f8, %f10
	nop
	fbule	.L769
	 nop
	add	%i0, -1, %i0
	andcc	%i0, 0xff, %g0
	bne,a	.L772
	 ld	[%i4+188], %g1
.L769:
	sethi	%hi(zftemp), %g1
	ldd	[%i3+%lo(.LC60)], %o0
	st	%g0, [%g1+%lo(zftemp)]
	st	%g0, [%g1+%lo(zftemp+4)]
	call	pow, 0
	 ldd	[%i2+%lo(.LC61)], %o2
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%i3+%lo(.LC60)], %o0
	ldd	[%i2+%lo(.LC61)], %o2
	call	pow, 0
	 std	%f8, [%fp-448]
	ldd	[%fp-448], %f8
	faddd	%f8, %f0, %f8
	ldd	[%i3+%lo(.LC60)], %o0
	ldd	[%i2+%lo(.LC61)], %o2
	call	pow, 0
	 std	%f8, [%fp-448]
	ldd	[%fp-448], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -400, %o0
	add	%fp, -392, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-400]
	ldd	[%fp-392], %f10
	ldd	[%i3+%lo(.LC60)], %o0
	std	%f10, [%fp-424]
	call	pow, 0
	 ldd	[%i2+%lo(.LC61)], %o2
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%i3+%lo(.LC60)], %o0
	ldd	[%i2+%lo(.LC61)], %o2
	call	pow, 0
	 std	%f8, [%fp-448]
	ldd	[%fp-448], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -400, %o0
	add	%fp, -392, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-400]
	ldd	[%i3+%lo(.LC60)], %o0
	call	atan2, 0
	 ldd	[%fp-392], %o2
	ldd	[%i3+%lo(.LC60)], %o0
	std	%f0, [%fp-416]
	mov	%o0, %o2
	mov	%o1, %o3
	call	atan2, 0
	 std	%f0, [%fp-408]
	sethi	%hi(.LC63), %g1
	sethi	%hi(.LC66), %i3
	ldd	[%g1+%lo(.LC63)], %f8
	or	%i3, %lo(.LC66), %i3
	fmuld	%f0, %f8, %f0
	sethi	%hi(.LC64), %g1
	ldd	[%g1+%lo(.LC64)], %f10
	fdivd	%f0, %f10, %f12
	std	%f12, [%fp-432]
	ldd	[%fp-408], %f8
.L773:
	fmovs	%f8, %f10
	fmovs	%f9, %f11
	faddd	%f8, %f10, %f8
	std	%f8, [%fp-456]
	call	sin, 0
	 ldd	[%fp-456], %o0
	sethi	%hi(.LC65), %g1
	ldd	[%g1+%lo(.LC65)], %f12
	ldd	[%fp-416], %f10
	fmuld	%f0, %f12, %f0
	ldd	[%fp-408], %f12
	faddd	%f0, %f10, %f8
	fsubd	%f12, %f8, %f12
	std	%f8, [%fp-408]
	std	%f12, [%fp-456]
	call	fabs, 0
	 ldd	[%fp-456], %o0
	ldd	[%i3], %f8
	fcmped	%f0, %f8
	nop
	fbg	.L773
	 ldd	[%fp-408], %f8
	call	sin, 0
	 ldd	[%fp-408], %o0
	ldd	[%i2+%lo(.LC61)], %o2
	std	%f0, [%fp-456]
	call	pow, 0
	 ldd	[%fp-456], %o0
	sethi	%hi(.LC65), %g1
	ldd	[%g1+%lo(.LC65)], %f8
	sethi	%hi(.LC67), %g1
	fmuld	%f0, %f8, %f0
	ldd	[%g1+%lo(.LC67)], %f10
	ldd	[%fp-408], %f8
	sethi	%hi(.LC68), %g1
	ldd	[%g1+%lo(.LC68)], %f12
	fsubd	%f12, %f0, %f12
	fmuld	%f8, %f10, %f10
	sethi	%hi(.LC69), %g1
	ldd	[%g1+%lo(.LC69)], %f8
	fmuld	%f12, %f8, %f8
	ldd	[%fp-424], %f12
	fsubd	%f12, %f8, %f8
	ldd	[%fp-432], %f12
	add	%fp, -256, %o0
	st	%g0, [%i4+696]
	st	%g0, [%i4+700]
	st	%g0, [%i4+704]
	st	%g0, [%i4+708]
	st	%g0, [%i4+712]
	st	%g0, [%i4+716]
	std	%f12, [%i4+720]
	std	%f10, [%i4+728]
	call	NavComputeDOP.constprop.1, 0
	 std	%f8, [%i4+736]
	jmp	%i7+8
	 restore
.L764:
	add	%fp, -384, %o0
	call	FindCoFactor.constprop.3, 0
	 add	%fp, -128, %o1
	b	.L767
	 ldd	[%fp-440], %f0
	.size	NavComputeUserPosFourSat, .-NavComputeUserPosFourSat
	.section	.rodata.cst8
	.align 8
.LC70:
	.long	-1074790400
	.long	0
	.section	.text.FindCoFactor,"ax",@progbits
	.align 4
	.global FindCoFactor
	.type	FindCoFactor, #function
	.proc	020
FindCoFactor:
	save	%sp, -248, %sp
	cmp	%i0, 0
	ble	.L794
	 sethi	%hi(.LC70), %i3
	sll	%i0, 3, %l3
	add	%i0, -1, %l0
	mov	0, %l2
	or	%i3, %lo(.LC70), %i3
	add	%i0, -2, %l1
.L776:
	mov	%i2, %l4
	mov	0, %i5
.L783:
	mov	%i1, %o4
	mov	0, %o5
	mov	0, %g3
	mov	0, %g4
.L782:
	xor	%o5, %l2, %g1
	mov	%o4, %g2
	subcc	%g0, %g1, %g0
	mov	0, %g1
	b	.L779
	 addx	%g0, 0, %o7
.L792:
	add	%g3, 1, %g3
.L777:
	add	%g1, 1, %g1
.L793:
	cmp	%g1, %i0
	be	.L791
	 add	%g2, 8, %g2
.L779:
	cmp	%g1, %i5
	be,a	.L793
	 add	%g1, 1, %g1
	sll	%g4, 2, %i4
	cmp	%o7, 0
	add	%i4, %g3, %i4
	sll	%i4, 3, %i4
	be	.L777
	 add	%fp, %i4, %i4
	ldd	[%g2], %f8
	cmp	%l1, %g3
	bg	.L792
	 std	%f8, [%i4-128]
	add	%g1, 1, %g1
	add	%g4, 1, %g4
	mov	0, %g3
	cmp	%g1, %i0
	bne	.L779
	 add	%g2, 8, %g2
.L791:
	add	%o5, 1, %o5
	cmp	%o5, %i0
	bne	.L782
	 add	%o4, %l3, %o4
	add	%i5, %l2, %o2
	st	%o2, [%fp-148]
	ld	[%fp-148], %f9
	fitod	%f9, %f8
	ldd	[%i3], %o0
	std	%f8, [%fp-144]
	call	pow, 0
	 ldd	[%fp-144], %o2
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	mov	%l0, %o0
	std	%f8, [%fp-136]
	call	FindDeterminant, 0
	 add	%fp, -128, %o1
	ldd	[%fp-136], %f8
	fmuld	%f8, %f0, %f0
	std	%f0, [%l4]
	add	%i5, 1, %i5
	cmp	%i5, %i0
	bne	.L783
	 add	%l4, 8, %l4
	add	%l2, 1, %l2
	cmp	%l2, %i0
	bne	.L776
	 add	%i2, %l3, %i2
.L794:
	jmp	%i7+8
	 restore
	.size	FindCoFactor, .-FindCoFactor
	.section	.rodata.cst8
	.align 8
.LC71:
	.long	0
	.long	0
	.align 8
.LC72:
	.long	-1074790400
	.long	0
	.section	.text.FindMatrixInverse,"ax",@progbits
	.align 4
	.global FindMatrixInverse
	.type	FindMatrixInverse, #function
	.proc	020
FindMatrixInverse:
	save	%sp, -384, %sp
	mov	%i0, %o0
	call	FindDeterminant, 0
	 mov	%i1, %o1
	sethi	%hi(.LC71), %g1
	ldd	[%g1+%lo(.LC71)], %f8
	fcmpd	%f0, %f8
	nop
	fbe	.L796
	 std	%f0, [%fp-264]
	cmp	%i0, 0
	ble	.L836
	 sethi	%hi(.LC72), %l0
	sll	%i0, 3, %l5
	add	%i0, -1, %l1
	add	%fp, -256, %l2
	mov	0, %l4
	or	%l0, %lo(.LC72), %l0
	add	%fp, -128, %i3
	add	%i0, -2, %l3
.L805:
	mov	%l2, %l6
	mov	0, %i5
.L814:
	mov	%i1, %o4
	mov	0, %o5
	mov	0, %g3
	mov	0, %g4
.L804:
	xor	%l4, %o5, %g1
	mov	%o4, %g2
	subcc	%g0, %g1, %g0
	mov	0, %g1
	b	.L801
	 addx	%g0, 0, %o7
.L830:
	add	%g3, 1, %g3
.L799:
	add	%g1, 1, %g1
.L832:
	cmp	%g1, %i0
	be	.L829
	 add	%g2, 8, %g2
.L801:
	cmp	%g1, %i5
	be,a	.L832
	 add	%g1, 1, %g1
	sll	%g4, 2, %i4
	cmp	%o7, 0
	add	%i4, %g3, %i4
	sll	%i4, 3, %i4
	be	.L799
	 add	%fp, %i4, %i4
	ldd	[%g2], %f8
	cmp	%l3, %g3
	bg	.L830
	 std	%f8, [%i4-128]
	add	%g1, 1, %g1
	add	%g4, 1, %g4
	mov	0, %g3
	cmp	%g1, %i0
	bne	.L801
	 add	%g2, 8, %g2
.L829:
	add	%o5, 1, %o5
	cmp	%o5, %i0
	bne	.L804
	 add	%o4, %l5, %o4
	add	%i5, %l4, %o2
	st	%o2, [%fp-284]
	ld	[%fp-284], %f9
	fitod	%f9, %f8
	ldd	[%l0], %o0
	std	%f8, [%fp-280]
	call	pow, 0
	 ldd	[%fp-280], %o2
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	mov	%l1, %o0
	std	%f8, [%fp-272]
	call	FindDeterminant, 0
	 mov	%i3, %o1
	ldd	[%fp-272], %f8
	fmuld	%f8, %f0, %f0
	std	%f0, [%l6]
	add	%i5, 1, %i5
	cmp	%i5, %i0
	bne	.L814
	 add	%l6, 8, %l6
	add	%l4, 1, %l4
	cmp	%l4, %i0
	bne	.L805
	 add	%l2, %l5, %l2
	cmp	%i0, 0
	ble	.L836
	 sll	%i0, 3, %g4
.L834:
	add	%fp, -256, %o7
	mov	0, %i4
	add	%fp, -128, %i3
.L809:
	mov	%i3, %i1
	mov	%i3, %g3
	mov	%o7, %g2
	mov	0, %g1
	sll	%i4, 3, %i5
.L808:
	ldd	[%g2], %f8
	std	%f8, [%g3+%i5]
	add	%g1, 1, %g1
	add	%g2, 8, %g2
	cmp	%g1, %i0
	bne	.L808
	 add	%g3, %g4, %g3
	add	%i4, 1, %i4
	cmp	%i4, %g1
	bne	.L809
	 add	%o7, %g4, %o7
	sll	%i4, 5, %i4
	add	%i4, %i3, %i3
.L812:
	mov	0, %g1
	ldd	[%fp-264], %f10
	ldd	[%i1+%g1], %f8
.L833:
	fdivd	%f8, %f10, %f8
	std	%f8, [%i2+%g1]
	add	%g1, 8, %g1
	cmp	%g4, %g1
	bne,a	.L833
	 ldd	[%i1+%g1], %f8
	add	%i1, 32, %i1
	cmp	%i1, %i3
	bne	.L812
	 add	%i2, %g4, %i2
.L836:
	jmp	%i7+8
	 restore
.L796:
	sethi	%hi(.LC51), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC51), %o0
	cmp	%i0, 0
	bg	.L834
	 sll	%i0, 3, %g4
	jmp	%i7+8
	 restore
	.size	FindMatrixInverse, .-FindMatrixInverse
	.section	.rodata.cst8
	.align 8
.LC73:
	.long	0
	.long	0
	.section	.text.NavComputeDOP,"ax",@progbits
	.align 4
	.global NavComputeDOP
	.type	NavComputeDOP, #function
	.proc	020
NavComputeDOP:
	save	%sp, -144, %sp
	cmp	%i0, 0
	ble	.L850
	 sethi	%hi(.LC73), %i4
	mov	%i1, %g3
	mov	0, %g2
	ldd	[%i4+%lo(.LC73)], %f8
.L839:
	mov	0, %g1
	cmp	%g2, %g1
.L859:
	be,a	.L856
	 ldd	[%g3], %f10
.L840:
	add	%g1, 1, %g1
	cmp	%g1, %i0
	bne	.L859
	 cmp	%g2, %g1
	add	%g2, 1, %g2
	cmp	%g2, %i0
	bne	.L839
	 add	%g3, 40, %g3
.L838:
	std	%f8, [%fp-16]
	add	%fp, -16, %o0
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	ldd	[%fp-8], %f8
	add	%i0, -1, %i5
	cmp	%i5, 0
	ble	.L851
	 std	%f8, [%fp-24]
	mov	%i1, %g3
	mov	0, %g2
	ldd	[%i4+%lo(.LC73)], %f8
.L843:
	mov	0, %g1
	cmp	%g2, %g1
.L860:
	be,a	.L857
	 ldd	[%g3], %f10
.L844:
	add	%g1, 1, %g1
	cmp	%g1, %i5
	bne	.L860
	 cmp	%g2, %g1
	add	%g2, 1, %g2
	cmp	%g2, %i5
	bne	.L843
	 add	%g3, 40, %g3
.L842:
	std	%f8, [%fp-16]
	add	%fp, -16, %o0
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	add	%i0, -2, %i0
	cmp	%i0, 0
	ble	.L852
	 ldd	[%fp-8], %f12
	mov	%i1, %g3
	mov	0, %g2
	ldd	[%i4+%lo(.LC73)], %f8
.L847:
	mov	0, %g1
	cmp	%g2, %g1
.L861:
	be,a	.L858
	 ldd	[%g3], %f10
.L848:
	add	%g1, 1, %g1
	cmp	%g1, %i0
	bne	.L861
	 cmp	%g2, %g1
	add	%g2, 1, %g2
	cmp	%g2, %i0
	bne	.L847
	 add	%g3, 40, %g3
.L846:
	std	%f12, [%fp-40]
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f8, [%fp-16]
	ldd	[%fp-8], %f14
	sll	%i0, 5, %g1
	sll	%i0, 3, %i0
	add	%i1, %i0, %i0
	ldd	[%i0+%g1], %f8
	add	%fp, -16, %o0
	std	%f14, [%fp-48]
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f8, [%fp-16]
	sll	%i5, 5, %g1
	ldd	[%fp-8], %f10
	sll	%i5, 3, %i5
	add	%i1, %i5, %i1
	ldd	[%i1+%g1], %f8
	add	%fp, -16, %o0
	std	%f8, [%fp-16]
	std	%f10, [%fp-32]
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	ldd	[%fp-24], %f8
	ldd	[%fp-40], %f12
	ldd	[%fp-48], %f14
	ldd	[%fp-32], %f10
	sethi	%hi(NavprocData), %g1
	or	%g1, %lo(NavprocData), %g1
	std	%f8, [%g1+752]
	std	%f12, [%g1+760]
	ldd	[%fp-8], %f8
	std	%f14, [%g1+768]
	std	%f10, [%g1+776]
	std	%f8, [%g1+784]
	jmp	%i7+8
	 restore
.L858:
	b	.L848
	 faddd	%f8, %f10, %f8
.L857:
	b	.L844
	 faddd	%f8, %f10, %f8
.L856:
	b	.L840
	 faddd	%f8, %f10, %f8
.L850:
	b	.L838
	 ldd	[%i4+%lo(.LC73)], %f8
.L851:
	b	.L842
	 ldd	[%i4+%lo(.LC73)], %f8
.L852:
	b	.L846
	 ldd	[%i4+%lo(.LC73)], %f8
	.size	NavComputeDOP, .-NavComputeDOP
	.section	.rodata.cst8
	.align 8
.LC74:
	.long	-1065402368
	.long	0
	.align 8
.LC75:
	.long	1073741824
	.long	0
	.align 8
.LC76:
	.long	1066524486
	.long	2723321923
	.align 8
.LC77:
	.long	1072693248
	.long	0
	.align 8
.LC78:
	.long	1080459264
	.long	0
	.align 8
.LC79:
	.long	1074340347
	.long	1413752350
	.align 8
.LC80:
	.long	0
	.long	0
	.align 8
.LC81:
	.long	1081507840
	.long	0
	.section	.text.NavComputeSatAzEl,"ax",@progbits
	.align 4
	.global NavComputeSatAzEl
	.type	NavComputeSatAzEl, #function
	.proc	020
NavComputeSatAzEl:
	save	%sp, -208, %sp
	sethi	%hi(NavprocData), %i5
	add	%i0, %i0, %g3
	or	%i5, %lo(NavprocData), %i5
	add	%g3, %i0, %g3
	sethi	%hi(.LC74), %g1
	sll	%g3, 3, %g4
	ldd	[%g1+%lo(.LC74)], %f8
	add	%i5, %g4, %g4
	mov	1, %g2
	ldd	[%g4+224], %f18
	fcmpd	%f18, %f8
	nop
	fbe	.L863
	 ldd	[%g4+216], %f22
	fcmpd	%f22, %f8
	nop
	fbne,a	.L863
	 mov	0, %g2
.L863:
	sll	%g3, 3, %g3
	ldd	[%g1+%lo(.LC74)], %f8
	add	%i5, %g3, %g3
	ldd	[%g3+232], %f12
	fcmpd	%f12, %f8
	nop
	fbne	.L887
	 ldd	[%i5+696], %f20
	mov	1, %g2
	ldd	[%g1+%lo(.LC74)], %f8
.L887:
	fcmpd	%f20, %f8
	nop
	fbne	.L888
	 ldd	[%i5+704], %f14
	mov	1, %g2
	ldd	[%g1+%lo(.LC74)], %f8
.L888:
	fcmpd	%f14, %f8
	nop
	fbne	.L889
	 ldd	[%i5+712], %f10
	mov	1, %g2
	ldd	[%g1+%lo(.LC74)], %f8
.L889:
	fcmpd	%f10, %f8
	nop
	fbne	.L890
	 ldd	[%i5+720], %f16
	mov	1, %g2
	ldd	[%g1+%lo(.LC74)], %f8
.L890:
	fcmpd	%f16, %f8
	nop
	fbne,a	.L885
	 ldd	[%i5+728], %f16
	ldd	[%g1+%lo(.LC74)], %f8
.L891:
	sll	%i0, 4, %g1
	add	%i5, %g1, %g1
	std	%f8, [%g1+360]
	add	%i0, 23, %i0
	sll	%i0, 4, %i0
	std	%f8, [%i5+%i0]
	jmp	%i7+8
	 restore
.L885:
	fcmpd	%f16, %f8
	nop
	fbe	.L891
	 ldd	[%g1+%lo(.LC74)], %f8
	cmp	%g2, 1
	be	.L891
	 sethi	%hi(.LC75), %i4
	fsubd	%f22, %f20, %f8
	std	%f8, [%fp-40]
	std	%f10, [%fp-80]
	std	%f12, [%fp-88]
	ldd	[%i4+%lo(.LC75)], %o2
	ldd	[%fp-40], %o0
	std	%f14, [%fp-96]
	call	pow, 0
	 std	%f18, [%fp-104]
	ldd	[%fp-104], %f18
	ldd	[%fp-96], %f14
	fmovs	%f0, %f8
	fsubd	%f18, %f14, %f16
	fmovs	%f1, %f9
	std	%f16, [%fp-48]
	ldd	[%i4+%lo(.LC75)], %o2
	ldd	[%fp-48], %o0
	call	pow, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-88], %f12
	ldd	[%fp-80], %f10
	ldd	[%fp-72], %f8
	fsubd	%f12, %f10, %f10
	faddd	%f8, %f0, %f8
	ldd	[%i4+%lo(.LC75)], %o2
	std	%f10, [%fp-112]
	std	%f10, [%fp-80]
	ldd	[%fp-112], %o0
	call	pow, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-72], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-16]
	ldd	[%i5+728], %f14
	ldd	[%fp-8], %f8
	sethi	%hi(zftemp), %g1
	ldd	[%i5+720], %f12
	std	%f8, [%g1+%lo(zftemp)]
	sethi	%hi(.LC76), %g1
	ldd	[%g1+%lo(.LC76)], %f8
	fmuld	%f14, %f8, %f16
	fmuld	%f12, %f8, %f14
	std	%f16, [%fp-32]
	std	%f14, [%fp-24]
	call	sin, 0
	 ldd	[%fp-32], %o0
	fmovs	%f0, %f12
	fmovs	%f1, %f13
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f12, [%fp-88]
	ldd	[%fp-88], %f12
	ldd	[%fp-40], %f16
	fmuld	%f12, %f0, %f0
	fmuld	%f16, %f0, %f12
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f12, [%fp-88]
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-72], %f8
	ldd	[%fp-48], %f14
	ldd	[%fp-88], %f12
	fmuld	%f8, %f0, %f0
	fmuld	%f14, %f0, %f8
	faddd	%f12, %f8, %f8
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-80], %f10
	ldd	[%fp-72], %f8
	fmuld	%f10, %f0, %f0
	fsubd	%f8, %f0, %f16
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f16, [%fp-56]
	ldd	[%fp-40], %f12
	fnegs	%f0, %f0
	fmuld	%f12, %f0, %f8
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-48], %f14
	ldd	[%fp-72], %f8
	fmuld	%f14, %f0, %f0
	faddd	%f8, %f0, %f16
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f16, [%fp-64]
	fmovs	%f0, %f12
	fmovs	%f1, %f13
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f12, [%fp-88]
	ldd	[%fp-88], %f12
	ldd	[%fp-40], %f8
	fmuld	%f12, %f0, %f0
	fmuld	%f8, %f0, %f12
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f12, [%fp-88]
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-72], %f8
	ldd	[%fp-48], %f14
	ldd	[%fp-88], %f12
	fmuld	%f8, %f0, %f0
	fmuld	%f14, %f0, %f8
	faddd	%f12, %f8, %f8
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-80], %f10
	ldd	[%fp-72], %f8
	fmuld	%f10, %f0, %f0
	faddd	%f8, %f0, %f16
	ldd	[%i4+%lo(.LC75)], %o2
	std	%f16, [%fp-24]
	call	pow, 0
	 ldd	[%fp-56], %o0
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%fp-64], %o0
	ldd	[%i4+%lo(.LC75)], %o2
	call	pow, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-72], %f8
	faddd	%f8, %f0, %f8
	ldd	[%fp-24], %o0
	ldd	[%i4+%lo(.LC75)], %o2
	call	pow, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-72], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-16]
	ldd	[%fp-24], %f10
	ldd	[%fp-8], %f8
	fdivd	%f10, %f8, %f8
	ldd	[%i4+%lo(.LC75)], %o2
	std	%f8, [%fp-112]
	std	%f8, [%fp-72]
	call	pow, 0
	 ldd	[%fp-112], %o0
	sethi	%hi(.LC77), %g1
	ldd	[%g1+%lo(.LC77)], %f10
	fsubd	%f10, %f0, %f0
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-16]
	ldd	[%fp-72], %f8
	ldd	[%fp-8], %o2
	std	%f8, [%fp-112]
	call	atan2, 0
	 ldd	[%fp-112], %o0
	sethi	%hi(.LC78), %g1
	ldd	[%fp-56], %f12
	fnegs	%f12, %f12
	ldd	[%g1+%lo(.LC78)], %f8
	std	%f12, [%fp-112]
	sethi	%hi(.LC79), %g1
	fmuld	%f0, %f8, %f0
	ldd	[%g1+%lo(.LC79)], %f10
	fdivd	%f0, %f10, %f12
	std	%f8, [%fp-72]
	std	%f10, [%fp-80]
	std	%f12, [%fp-88]
	ldd	[%fp-64], %o0
	call	atan2, 0
	 ldd	[%fp-112], %o2
	ldd	[%fp-72], %f8
	ldd	[%fp-80], %f10
	sethi	%hi(.LC80), %g1
	fmuld	%f0, %f8, %f0
	fdivd	%f0, %f10, %f8
	ldd	[%g1+%lo(.LC80)], %f10
	ldd	[%fp-88], %f12
	fcmped	%f8, %f10
	sethi	%hi(.LC81), %g1
	nop
	fbl	.L886
	 ldd	[%g1+%lo(.LC81)], %f10
	fcmped	%f8, %f10
	nop
	fbg,a	.L874
	 fsubd	%f8, %f10, %f8
.L874:
	sll	%i0, 4, %g1
	add	%i5, %g1, %g1
	std	%f8, [%g1+360]
	add	%i0, 23, %i0
	sll	%i0, 4, %i0
	std	%f12, [%i5+%i0]
	jmp	%i7+8
	 restore
.L886:
	sll	%i0, 4, %g1
	faddd	%f8, %f10, %f8
	add	%i5, %g1, %g1
	std	%f8, [%g1+360]
	add	%i0, 23, %i0
	sll	%i0, 4, %i0
	std	%f12, [%i5+%i0]
	jmp	%i7+8
	 restore
	.size	NavComputeSatAzEl, .-NavComputeSatAzEl
	.section	.rodata.cst8
	.align 8
.LC82:
	.long	1083157504
	.long	0
	.align 8
.LC83:
	.long	0
	.long	0
	.align 8
.LC84:
	.long	1083153920
	.long	0
	.align 8
.LC85:
	.long	-1075838976
	.long	0
	.align 8
.LC86:
	.long	1081260646
	.long	1717986918
	.align 8
.LC87:
	.long	1076690944
	.long	0
	.align 8
.LC88:
	.long	1081113190
	.long	1717986918
	.align 8
.LC89:
	.long	1077563228
	.long	687194767
	.align 8
.LC90:
	.long	1074470584
	.long	1374389535
	.align 8
.LC91:
	.long	1074819235
	.long	3607772529
	.align 8
.LC92:
	.long	1075393331
	.long	858993459
	.align 8
.LC93:
	.long	1074929336
	.long	1374389535
	.align 8
.LC94:
	.long	1071896330
	.long	1030792151
	.align 8
.LC95:
	.long	1074145525
	.long	3264175145
	.align 8
.LC96:
	.long	1070805811
	.long	858993459
	.align 8
.LC97:
	.long	1073269964
	.long	3435973837
	.align 8
.LC98:
	.long	1079164928
	.long	0
	.align 8
.LC99:
	.long	1076756480
	.long	0
	.align 8
.LC100:
	.long	1077805056
	.long	0
	.align 8
.LC101:
	.long	1070596096
	.long	0
	.align 8
.LC102:
	.long	-1076887552
	.long	0
	.align 8
.LC103:
	.long	1078362112
	.long	0
	.align 8
.LC104:
	.long	-1078355559
	.long	2576980378
	.align 8
.LC105:
	.long	1083165184
	.long	0
	.align 8
.LC106:
	.long	1069128089
	.long	2576980378
	.align 8
.LC107:
	.long	1074659328
	.long	0
	.align 8
.LC108:
	.long	1078853632
	.long	0
	.align 8
.LC109:
	.long	-1076817647
	.long	292335953
	.align 8
.LC110:
	.long	1083162112
	.long	0
	.align 8
.LC111:
	.long	1067509088
	.long	1099511628
	.align 8
.LC112:
	.long	1073872896
	.long	0
	.align 8
.LC113:
	.long	1068848469
	.long	1407636567
	.align 8
.LC114:
	.long	1068842876
	.long	3985729651
	.align 8
.LC115:
	.long	1073479680
	.long	0
	.align 8
.LC116:
	.long	1075388923
	.long	1413752350
	.align 8
.LC117:
	.long	1081529344
	.long	0
	.align 8
.LC118:
	.long	1076101120
	.long	0
	.align 8
.LC119:
	.long	-1072168960
	.long	0
	.align 8
.LC120:
	.long	1087750434
	.long	2024750662
	.align 8
.LC121:
	.long	1076072808
	.long	1924145349
	.align 8
.LC122:
	.long	-1076398217
	.long	2010322871
	.align 8
.LC123:
	.long	1071476899
	.long	3607772529
	.align 8
.LC124:
	.long	-1075349641
	.long	2001315672
	.align 8
.LC125:
	.long	1081238118
	.long	1717986918
	.align 8
.LC126:
	.long	1070663204
	.long	3710851744
	.align 8
.LC127:
	.long	1075576832
	.long	0
	.align 8
.LC128:
	.long	1081193062
	.long	1717986918
	.align 8
.LC129:
	.long	1076232192
	.long	0
	.align 8
.LC130:
	.long	-1075699166
	.long	575664706
	.align 8
.LC131:
	.long	1081148006
	.long	1717986918
	.align 8
.LC132:
	.long	-1076672245
	.long	2593882070
	.align 8
.LC133:
	.long	-1075471276
	.long	2791589654
	.align 8
.LC134:
	.long	1077267005
	.long	1889785610
	.align 8
.LC135:
	.long	-1076571582
	.long	3865192390
	.align 8
.LC136:
	.long	1076318699
	.long	2233382994
	.align 8
.LC137:
	.long	-1077491532
	.long	962072674
	.align 8
.LC138:
	.long	1075519160
	.long	1374389535
	.align 8
.LC139:
	.long	1068847910
	.long	398572965
	.align 8
.LC140:
	.long	-1081011951
	.long	382407945
	.align 8
.LC141:
	.long	-1081016425
	.long	611603343
	.align 8
.LC142:
	.long	-1080030484
	.long	822408309
	.align 8
.LC143:
	.long	1075327795
	.long	858993459
	.align 8
.LC144:
	.long	1061063214
	.long	3263900267
	.align 8
.LC145:
	.long	-1081478917
	.long	1142773012
	.align 8
.LC146:
	.long	1075204587
	.long	2233382994
	.align 8
.LC147:
	.long	1067497679
	.long	3217445901
	.align 8
.LC148:
	.long	1070889697
	.long	1202590843
	.align 8
.LC149:
	.long	-1079158069
	.long	1818840722
	.align 8
.LC150:
	.long	1075154780
	.long	687194767
	.align 8
.LC151:
	.long	1066003836
	.long	1874667325
	.align 8
.LC152:
	.long	1072294789
	.long	515396076
	.align 8
.LC153:
	.long	1075314688
	.long	0
	.align 8
.LC154:
	.long	1067053307
	.long	854542636
	.align 8
.LC155:
	.long	1066829611
	.long	34359738
	.align 8
.LC156:
	.long	1076948063
	.long	2461509666
	.align 8
.LC157:
	.long	1074344755
	.long	858993459
	.align 8
.LC158:
	.long	1065466965
	.long	2252624447
	.align 8
.LC159:
	.long	1070931640
	.long	1374389535
	.align 8
.LC160:
	.long	-1070529730
	.long	527787572
	.align 8
.LC161:
	.long	1081085952
	.long	0
	.align 8
.LC162:
	.long	1066605467
	.long	1727607645
	.align 8
.LC163:
	.long	1076128994
	.long	2773562062
	.align 8
.LC164:
	.long	1073542594
	.long	2405181686
	.align 8
.LC165:
	.long	1067321518
	.long	4213878313
	.align 8
.LC166:
	.long	1072147988
	.long	2061584302
	.align 8
.LC167:
	.long	1072693248
	.long	0
	.align 8
.LC168:
	.long	1081209053
	.long	790273982
	.align 8
.LC169:
	.long	1090176362
	.long	206158430
	.align 8
.LC170:
	.long	1076075777
	.long	982688517
	.align 8
.LC171:
	.long	1063281766
	.long	2984624314
	.align 8
.LC172:
	.long	1072694296
	.long	2473901162
	.section	.text.NavComputeTroposphericDelay,"ax",@progbits
	.align 4
	.global NavComputeTroposphericDelay
	.type	NavComputeTroposphericDelay, #function
	.proc	07
NavComputeTroposphericDelay:
	save	%sp, -224, %sp
	sethi	%hi(NavprocData), %l0
	add	%i0, 23, %g1
	or	%l0, %lo(NavprocData), %l0
	sll	%g1, 4, %g1
	ldd	[%l0+736], %f14
	ldd	[%l0+%g1], %f12
	std	%f14, [%fp-48]
	std	%f12, [%fp-32]
	ldd	[%l0+728], %f8
	ldd	[%l0+968], %f10
	sethi	%hi(.LC98), %i5
	ldd	[%i5+%lo(.LC98)], %f12
	fcmped	%f8, %f12
	nop
	fbge	.L958
	 fdtoi	%f10, %f16
	sethi	%hi(.LC82), %g1
	ldd	[%g1+%lo(.LC82)], %f10
	sethi	%hi(.LC83), %g1
	ldd	[%g1+%lo(.LC83)], %f12
.L893:
	sethi	%hi(.LC99), %i1
	ldd	[%i1+%lo(.LC99)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L894
	 sethi	%hi(.LC100), %i2
	ldd	[%i2+%lo(.LC100)], %f18
	fcmped	%f8, %f18
	nop
	fble	.L1003
	 sethi	%hi(.LC101), %g1
.L894:
	ldd	[%i2+%lo(.LC100)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L897
	 sethi	%hi(.LC103), %i3
	ldd	[%i3+%lo(.LC103)], %f18
	fcmped	%f8, %f18
	nop
	fble	.L1004
	 sethi	%hi(.LC104), %g1
.L897:
	ldd	[%i3+%lo(.LC103)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L900
	 sethi	%hi(.LC108), %i4
	ldd	[%i4+%lo(.LC108)], %f18
	fcmped	%f8, %f18
	nop
	fble	.L1005
	 sethi	%hi(.LC109), %g1
.L900:
	ldd	[%i4+%lo(.LC108)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L903
	 nop
	ldd	[%i5+%lo(.LC98)], %f18
	fcmped	%f8, %f18
	nop
	fble	.L1006
	 sethi	%hi(.LC113), %g1
.L903:
	st	%f16, [%fp-116]
	ld	[%fp-116], %g1
	add	%g1, -28, %g1
	st	%g1, [%fp-116]
	sethi	%hi(.LC116), %g1
	ldd	[%g1+%lo(.LC116)], %f14
	ld	[%fp-116], %f16
	sethi	%hi(.LC117), %g1
	fitod	%f16, %f16
	fmuld	%f16, %f14, %f16
	ldd	[%g1+%lo(.LC117)], %f14
	fdivd	%f16, %f14, %f18
	std	%f8, [%fp-72]
	std	%f18, [%fp-24]
	std	%f10, [%fp-80]
	std	%f12, [%fp-88]
	call	cos, 0
	 ldd	[%fp-24], %o0
	fmovs	%f0, %f14
	fmovs	%f1, %f15
	sethi	%hi(.LC118), %l1
	std	%f14, [%fp-96]
	sethi	%hi(.LC119), %l3
	ldd	[%l1+%lo(.LC118)], %o0
	call	pow, 0
	 ldd	[%l3+%lo(.LC119)], %o2
	sethi	%hi(.LC121), %l2
	ldd	[%fp-88], %f12
	ldd	[%fp-96], %f14
	ldd	[%fp-80], %f10
	fmuld	%f14, %f12, %f12
	ldd	[%l2+%lo(.LC121)], %f16
	fsubd	%f10, %f12, %f10
	sethi	%hi(.LC120), %g1
	ldd	[%g1+%lo(.LC120)], %f18
	fmuld	%f10, %f18, %f10
	fmuld	%f10, %f0, %f0
	fdivd	%f0, %f16, %f20
	std	%f20, [%fp-56]
	ldd	[%i5+%lo(.LC98)], %f18
	ldd	[%fp-72], %f8
	fcmped	%f8, %f18
	nop
	fbge	.L959
	 sethi	%hi(.LC87), %g1
	sethi	%hi(.LC83), %g1
	ldd	[%g1+%lo(.LC83)], %f12
	sethi	%hi(.LC86), %g1
	ldd	[%g1+%lo(.LC86)], %f10
.L906:
	ldd	[%i1+%lo(.LC99)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L907
	 nop
	ldd	[%i2+%lo(.LC100)], %f16
	fcmped	%f8, %f16
	nop
	fble	.L1007
	 sethi	%hi(.LC122), %g1
.L907:
	ldd	[%i2+%lo(.LC100)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L910
	 nop
	ldd	[%i3+%lo(.LC103)], %f16
	fcmped	%f8, %f16
	nop
	fble	.L1008
	 sethi	%hi(.LC124), %g1
.L910:
	ldd	[%i3+%lo(.LC103)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L913
	 nop
	ldd	[%i4+%lo(.LC108)], %f16
	fcmped	%f8, %f16
	nop
	fble	.L1009
	 sethi	%hi(.LC124), %g1
.L913:
	ldd	[%i4+%lo(.LC108)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L916
	 nop
	ldd	[%i5+%lo(.LC98)], %f16
	fcmped	%f8, %f16
	nop
	fble	.L1010
	 sethi	%hi(.LC130), %g1
.L916:
	std	%f8, [%fp-72]
	std	%f10, [%fp-80]
	std	%f12, [%fp-88]
	call	cos, 0
	 ldd	[%fp-24], %o0
	ldd	[%fp-88], %f12
	ldd	[%fp-80], %f10
	fmuld	%f0, %f12, %f0
	fsubd	%f10, %f0, %f12
	std	%f12, [%fp-40]
	ldd	[%i5+%lo(.LC98)], %f14
	ldd	[%fp-72], %f8
	fcmped	%f8, %f14
	nop
	fbge	.L960
	 sethi	%hi(.LC90), %g1
	sethi	%hi(.LC83), %g1
	ldd	[%g1+%lo(.LC83)], %f12
	sethi	%hi(.LC89), %g1
	ldd	[%g1+%lo(.LC89)], %f10
.L919:
	ldd	[%i1+%lo(.LC99)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L920
	 nop
	ldd	[%i2+%lo(.LC100)], %f16
	fcmped	%f8, %f16
	nop
	fble	.L1011
	 sethi	%hi(.LC132), %g1
.L920:
	ldd	[%i2+%lo(.LC100)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L923
	 nop
	ldd	[%i3+%lo(.LC103)], %f16
	fcmped	%f8, %f16
	nop
	fble	.L1012
	 sethi	%hi(.LC133), %g1
.L923:
	ldd	[%i3+%lo(.LC103)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L926
	 nop
	ldd	[%i4+%lo(.LC108)], %f16
	fcmped	%f8, %f16
	nop
	fble	.L1013
	 sethi	%hi(.LC135), %g1
.L926:
	ldd	[%i4+%lo(.LC108)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L929
	 nop
	ldd	[%i5+%lo(.LC98)], %f16
	fcmped	%f8, %f16
	nop
	fble	.L1014
	 sethi	%hi(.LC137), %g1
.L929:
	std	%f8, [%fp-72]
	std	%f10, [%fp-80]
	std	%f12, [%fp-88]
	call	cos, 0
	 ldd	[%fp-24], %o0
	ldd	[%i5+%lo(.LC98)], %f14
	ldd	[%fp-88], %f12
	ldd	[%fp-72], %f8
	fmuld	%f0, %f12, %f0
	fcmped	%f8, %f14
	ldd	[%fp-80], %f10
	fsubd	%f10, %f0, %f14
	nop
	fbge	.L961
	 std	%f14, [%fp-64]
	sethi	%hi(.LC92), %g1
	ldd	[%g1+%lo(.LC92)], %f16
	sethi	%hi(.LC83), %g1
	ldd	[%g1+%lo(.LC83)], %f10
.L932:
	ldd	[%i1+%lo(.LC99)], %f12
	fcmped	%f8, %f12
	nop
	fbule	.L933
	 nop
	ldd	[%i2+%lo(.LC100)], %f14
	fcmped	%f8, %f14
	nop
	fble	.L1015
	 sethi	%hi(.LC140), %g1
.L933:
	ldd	[%i2+%lo(.LC100)], %f12
	fcmped	%f8, %f12
	nop
	fbule	.L936
	 nop
	ldd	[%i3+%lo(.LC103)], %f14
	fcmped	%f8, %f14
	nop
	fble	.L1016
	 sethi	%hi(.LC142), %g1
.L936:
	ldd	[%i3+%lo(.LC103)], %f12
	fcmped	%f8, %f12
	nop
	fbule	.L939
	 nop
	ldd	[%i4+%lo(.LC108)], %f14
	fcmped	%f8, %f14
	nop
	fble	.L1017
	 sethi	%hi(.LC145), %g1
.L939:
	ldd	[%i4+%lo(.LC108)], %f12
	fcmped	%f8, %f12
	nop
	fbule	.L942
	 nop
	ldd	[%i5+%lo(.LC98)], %f14
	fcmped	%f8, %f14
	nop
	fble	.L1018
	 sethi	%hi(.LC149), %g1
.L942:
	std	%f8, [%fp-72]
	std	%f10, [%fp-80]
	std	%f16, [%fp-104]
	call	cos, 0
	 ldd	[%fp-24], %o0
	ldd	[%fp-104], %f16
	ldd	[%l1+%lo(.LC118)], %f12
	ldd	[%fp-80], %f10
	sethi	%hi(.LC153), %g1
	fsubd	%f16, %f10, %f10
	ldd	[%g1+%lo(.LC153)], %f16
	fmuld	%f10, %f12, %f10
	fmuld	%f0, %f16, %f0
	ldd	[%i5+%lo(.LC98)], %f12
	ldd	[%fp-72], %f8
	fcmped	%f8, %f12
	nop
	fbge	.L962
	 fsubd	%f10, %f0, %f16
	sethi	%hi(.LC83), %g1
	ldd	[%g1+%lo(.LC83)], %f10
	sethi	%hi(.LC95), %g1
	ldd	[%g1+%lo(.LC95)], %f12
.L945:
	ldd	[%i1+%lo(.LC99)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L946
	 nop
	ldd	[%i2+%lo(.LC100)], %f18
	fcmped	%f8, %f18
	nop
	fble	.L1019
	 sethi	%hi(.LC154), %g1
.L946:
	ldd	[%i2+%lo(.LC100)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L949
	 nop
	ldd	[%i3+%lo(.LC103)], %f18
	fcmped	%f8, %f18
	nop
	fble	.L1020
	 sethi	%hi(.LC156), %g1
.L949:
	ldd	[%i3+%lo(.LC103)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L952
	 nop
	ldd	[%i4+%lo(.LC108)], %f18
	fcmped	%f8, %f18
	nop
	fble	.L1021
	 sethi	%hi(.LC160), %g1
.L952:
	ldd	[%i4+%lo(.LC108)], %f14
	fcmped	%f8, %f14
	nop
	fbule	.L955
	 nop
	ldd	[%i5+%lo(.LC98)], %f18
	fcmped	%f8, %f18
	nop
	fbug	.L955
	 nop
	sethi	%hi(.LC163), %g1
	ldd	[%g1+%lo(.LC163)], %f12
	sethi	%hi(.LC165), %g1
	ldd	[%g1+%lo(.LC165)], %f10
	fsubd	%f8, %f14, %f8
	sethi	%hi(.LC164), %g1
	fmuld	%f8, %f12, %f12
	fmuld	%f8, %f10, %f8
	ldd	[%g1+%lo(.LC164)], %f10
	sethi	%hi(.LC166), %g1
	faddd	%f12, %f10, %f12
	ldd	[%g1+%lo(.LC166)], %f10
	fsubd	%f10, %f8, %f10
.L955:
	fsubd	%f12, %f10, %f10
	std	%f16, [%fp-104]
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f10, [%fp-80]
	ldd	[%fp-80], %f10
	fmuld	%f10, %f0, %f10
	ldd	[%l1+%lo(.LC118)], %o0
	ldd	[%l3+%lo(.LC119)], %o2
	call	pow, 0
	 std	%f10, [%fp-80]
	ldd	[%fp-40], %f8
	sethi	%hi(.LC167), %g1
	ldd	[%fp-104], %f16
	ldd	[%fp-48], %f20
	fmuld	%f16, %f20, %f18
	fsubd	%f8, %f18, %f12
	ldd	[%g1+%lo(.LC167)], %f8
	sethi	%hi(.LC168), %g1
	ldd	[%fp-80], %f10
	fdivd	%f18, %f12, %f12
	faddd	%f10, %f8, %f10
	fsubd	%f8, %f12, %f12
	ldd	[%g1+%lo(.LC168)], %f8
	sethi	%hi(.LC169), %g1
	fmuld	%f16, %f8, %f8
	ldd	[%g1+%lo(.LC169)], %f16
	ldd	[%l2+%lo(.LC121)], %f14
	fmuld	%f0, %f16, %f0
	fmuld	%f10, %f14, %f14
	ldd	[%fp-40], %f16
	fmuld	%f8, %f16, %f18
	fsubd	%f14, %f18, %f14
	std	%f12, [%fp-128]
	sethi	%hi(.LC170), %g1
	ldd	[%fp-64], %f20
	fmuld	%f0, %f20, %f16
	fdivd	%f16, %f14, %f16
	ldd	[%g1+%lo(.LC170)], %f14
	fdivd	%f14, %f8, %f18
	ldd	[%fp-128], %o0
	std	%f16, [%fp-104]
	std	%f18, [%fp-128]
	std	%f8, [%fp-72]
	ldd	[%fp-128], %o2
	std	%f10, [%fp-80]
	std	%f12, [%fp-88]
	call	pow, 0
	 std	%f14, [%fp-96]
	ldd	[%fp-80], %f10
	ldd	[%fp-88], %f12
	ldd	[%fp-56], %f20
	std	%f12, [%fp-128]
	fmuld	%f0, %f20, %f18
	ldd	[%fp-72], %f8
	ldd	[%fp-96], %f14
	fmuld	%f10, %f14, %f14
	fdivd	%f14, %f8, %f10
	std	%f18, [%fp-112]
	ldd	[%fp-128], %o0
	std	%f10, [%fp-128]
	call	pow, 0
	 ldd	[%fp-128], %o2
	ldd	[%fp-104], %f16
	fmuld	%f0, %f16, %f16
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f16, [%fp-104]
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f8, [%fp-72]
	ldd	[%fp-72], %f8
	sethi	%hi(.LC171), %g1
	fmuld	%f8, %f0, %f0
	ldd	[%g1+%lo(.LC171)], %f10
	faddd	%f0, %f10, %f8
	add	%fp, -16, %o0
	std	%f8, [%fp-16]
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	sethi	%hi(.LC172), %g1
	ldd	[%g1+%lo(.LC172)], %f0
	ldd	[%fp-104], %f16
	ldd	[%fp-112], %f18
	ldd	[%fp-8], %f8
	faddd	%f18, %f16, %f16
	fdivd	%f0, %f8, %f8
	add	%i0, 81, %i0
	fmuld	%f16, %f8, %f0
	sll	%i0, 3, %i0
	std	%f0, [%l0+%i0]
	jmp	%i7+8
	 restore
.L962:
	sethi	%hi(.LC96), %g1
	ldd	[%g1+%lo(.LC96)], %f10
	sethi	%hi(.LC97), %g1
	b	.L945
	 ldd	[%g1+%lo(.LC97)], %f12
.L961:
	sethi	%hi(.LC93), %g1
	ldd	[%g1+%lo(.LC93)], %f16
	sethi	%hi(.LC94), %g1
	b	.L932
	 ldd	[%g1+%lo(.LC94)], %f10
.L960:
	ldd	[%g1+%lo(.LC90)], %f12
	sethi	%hi(.LC91), %g1
	b	.L919
	 ldd	[%g1+%lo(.LC91)], %f10
.L959:
	ldd	[%g1+%lo(.LC87)], %f12
	sethi	%hi(.LC88), %g1
	b	.L906
	 ldd	[%g1+%lo(.LC88)], %f10
.L958:
	sethi	%hi(.LC84), %g1
	ldd	[%g1+%lo(.LC84)], %f10
	sethi	%hi(.LC85), %g1
	b	.L893
	 ldd	[%g1+%lo(.LC85)], %f12
.L1021:
	ldd	[%g1+%lo(.LC160)], %f12
	sethi	%hi(.LC162), %g1
	ldd	[%g1+%lo(.LC162)], %f10
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC161), %g1
	fmuld	%f14, %f12, %f12
	fmuld	%f14, %f10, %f14
	ldd	[%g1+%lo(.LC161)], %f10
	sethi	%hi(.LC123), %g1
	faddd	%f12, %f10, %f12
	ldd	[%g1+%lo(.LC123)], %f18
	b	.L952
	 faddd	%f14, %f18, %f10
.L1020:
	ldd	[%g1+%lo(.LC156)], %f12
	sethi	%hi(.LC158), %g1
	ldd	[%g1+%lo(.LC158)], %f10
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC157), %g1
	fmuld	%f14, %f12, %f12
	fmuld	%f14, %f10, %f14
	ldd	[%g1+%lo(.LC157)], %f10
	sethi	%hi(.LC159), %g1
	faddd	%f12, %f10, %f12
	ldd	[%g1+%lo(.LC159)], %f18
	b	.L949
	 faddd	%f14, %f18, %f10
.L1019:
	ldd	[%g1+%lo(.LC154)], %f12
	sethi	%hi(.LC95), %g1
	ldd	[%g1+%lo(.LC95)], %f10
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC155), %g1
	fmuld	%f14, %f12, %f12
	faddd	%f12, %f10, %f12
	ldd	[%g1+%lo(.LC155)], %f10
	b	.L946
	 fmuld	%f14, %f10, %f10
.L1018:
	ldd	[%g1+%lo(.LC149)], %f16
	sethi	%hi(.LC151), %g1
	ldd	[%g1+%lo(.LC151)], %f10
	fsubd	%f8, %f12, %f12
	sethi	%hi(.LC150), %g1
	fmuld	%f12, %f16, %f16
	fmuld	%f12, %f10, %f12
	ldd	[%g1+%lo(.LC150)], %f10
	sethi	%hi(.LC152), %g1
	faddd	%f16, %f10, %f16
	ldd	[%g1+%lo(.LC152)], %f10
	b	.L942
	 fsubd	%f10, %f12, %f10
.L1017:
	ldd	[%g1+%lo(.LC145)], %f16
	sethi	%hi(.LC147), %g1
	ldd	[%g1+%lo(.LC147)], %f10
	fsubd	%f8, %f12, %f12
	sethi	%hi(.LC146), %g1
	fmuld	%f12, %f16, %f16
	fmuld	%f12, %f10, %f12
	ldd	[%g1+%lo(.LC146)], %f10
	sethi	%hi(.LC148), %g1
	faddd	%f16, %f10, %f16
	ldd	[%g1+%lo(.LC148)], %f14
	b	.L939
	 faddd	%f12, %f14, %f10
.L1016:
	ldd	[%g1+%lo(.LC142)], %f16
	sethi	%hi(.LC144), %g1
	ldd	[%g1+%lo(.LC144)], %f10
	fsubd	%f8, %f12, %f12
	sethi	%hi(.LC143), %g1
	fmuld	%f12, %f16, %f16
	fmuld	%f12, %f10, %f12
	ldd	[%g1+%lo(.LC143)], %f10
	sethi	%hi(.LC101), %g1
	faddd	%f16, %f10, %f16
	ldd	[%g1+%lo(.LC101)], %f14
	b	.L936
	 faddd	%f12, %f14, %f10
.L1015:
	ldd	[%g1+%lo(.LC140)], %f16
	sethi	%hi(.LC92), %g1
	ldd	[%g1+%lo(.LC92)], %f10
	fsubd	%f8, %f12, %f12
	sethi	%hi(.LC141), %g1
	fmuld	%f12, %f16, %f16
	faddd	%f16, %f10, %f16
	ldd	[%g1+%lo(.LC141)], %f10
	b	.L933
	 fmuld	%f12, %f10, %f10
.L1014:
	ldd	[%g1+%lo(.LC137)], %f10
	sethi	%hi(.LC139), %g1
	ldd	[%g1+%lo(.LC139)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC138), %g1
	fmuld	%f14, %f10, %f10
	fmuld	%f14, %f12, %f14
	ldd	[%g1+%lo(.LC138)], %f12
	sethi	%hi(.LC115), %g1
	faddd	%f10, %f12, %f10
	ldd	[%g1+%lo(.LC115)], %f16
	b	.L929
	 fsubd	%f14, %f16, %f12
.L1013:
	ldd	[%g1+%lo(.LC135)], %f10
	sethi	%hi(.LC111), %g1
	ldd	[%g1+%lo(.LC111)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC136), %g1
	fmuld	%f14, %f10, %f10
	fmuld	%f14, %f12, %f14
	ldd	[%g1+%lo(.LC136)], %f12
	sethi	%hi(.LC112), %g1
	faddd	%f10, %f12, %f10
	ldd	[%g1+%lo(.LC112)], %f16
	b	.L926
	 fsubd	%f14, %f16, %f12
.L1012:
	ldd	[%g1+%lo(.LC133)], %f10
	sethi	%hi(.LC106), %g1
	ldd	[%g1+%lo(.LC106)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC134), %g1
	fmuld	%f14, %f10, %f10
	fmuld	%f14, %f12, %f14
	ldd	[%g1+%lo(.LC134)], %f12
	sethi	%hi(.LC107), %g1
	faddd	%f10, %f12, %f10
	ldd	[%g1+%lo(.LC107)], %f16
	b	.L923
	 fsubd	%f14, %f16, %f12
.L1011:
	ldd	[%g1+%lo(.LC132)], %f10
	sethi	%hi(.LC89), %g1
	ldd	[%g1+%lo(.LC89)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC102), %g1
	fmuld	%f14, %f10, %f10
	faddd	%f10, %f12, %f10
	ldd	[%g1+%lo(.LC102)], %f12
	b	.L920
	 fmuld	%f14, %f12, %f12
.L1010:
	ldd	[%g1+%lo(.LC130)], %f10
	sethi	%hi(.LC131), %g1
	ldd	[%g1+%lo(.LC131)], %f16
	fsubd	%f8, %f14, %f14
	ldd	[%i1+%lo(.LC99)], %f12
	fmuld	%f14, %f10, %f10
	sethi	%hi(.LC111), %g1
	faddd	%f10, %f16, %f10
	ldd	[%g1+%lo(.LC111)], %f16
	fmuld	%f14, %f16, %f14
	b	.L916
	 fsubd	%f12, %f14, %f12
.L1009:
	ldd	[%g1+%lo(.LC124)], %f10
	sethi	%hi(.LC126), %g1
	ldd	[%g1+%lo(.LC126)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC128), %g1
	fmuld	%f14, %f10, %f10
	fmuld	%f14, %f12, %f14
	ldd	[%g1+%lo(.LC128)], %f12
	sethi	%hi(.LC129), %g1
	faddd	%f10, %f12, %f10
	ldd	[%g1+%lo(.LC129)], %f16
	b	.L913
	 faddd	%f14, %f16, %f12
.L1008:
	ldd	[%g1+%lo(.LC124)], %f10
	sethi	%hi(.LC126), %g1
	ldd	[%g1+%lo(.LC126)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC125), %g1
	fmuld	%f14, %f10, %f10
	fmuld	%f14, %f12, %f14
	ldd	[%g1+%lo(.LC125)], %f12
	sethi	%hi(.LC127), %g1
	faddd	%f10, %f12, %f10
	ldd	[%g1+%lo(.LC127)], %f16
	b	.L910
	 faddd	%f14, %f16, %f12
.L1007:
	ldd	[%g1+%lo(.LC122)], %f10
	sethi	%hi(.LC86), %g1
	ldd	[%g1+%lo(.LC86)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC123), %g1
	fmuld	%f14, %f10, %f10
	faddd	%f10, %f12, %f10
	ldd	[%g1+%lo(.LC123)], %f12
	b	.L907
	 fmuld	%f14, %f12, %f12
.L1006:
	ldd	[%g1+%lo(.LC113)], %f18
	sethi	%hi(.LC114), %g1
	ldd	[%g1+%lo(.LC114)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC84), %g1
	fmuld	%f14, %f18, %f18
	fmuld	%f14, %f12, %f14
	ldd	[%g1+%lo(.LC84)], %f12
	sethi	%hi(.LC115), %g1
	faddd	%f18, %f12, %f10
	ldd	[%g1+%lo(.LC115)], %f18
	b	.L903
	 fsubd	%f14, %f18, %f12
.L1005:
	ldd	[%g1+%lo(.LC109)], %f18
	sethi	%hi(.LC111), %g1
	ldd	[%g1+%lo(.LC111)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC110), %g1
	fmuld	%f14, %f18, %f18
	fmuld	%f14, %f12, %f14
	ldd	[%g1+%lo(.LC110)], %f12
	sethi	%hi(.LC112), %g1
	faddd	%f18, %f12, %f10
	ldd	[%g1+%lo(.LC112)], %f18
	b	.L900
	 fsubd	%f14, %f18, %f12
.L1004:
	ldd	[%g1+%lo(.LC104)], %f18
	sethi	%hi(.LC106), %g1
	ldd	[%g1+%lo(.LC106)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC105), %g1
	fmuld	%f14, %f18, %f18
	fmuld	%f14, %f12, %f14
	ldd	[%g1+%lo(.LC105)], %f12
	sethi	%hi(.LC107), %g1
	faddd	%f18, %f12, %f10
	ldd	[%g1+%lo(.LC107)], %f18
	b	.L897
	 fsubd	%f14, %f18, %f12
.L1003:
	ldd	[%g1+%lo(.LC101)], %f18
	sethi	%hi(.LC82), %g1
	ldd	[%g1+%lo(.LC82)], %f12
	fsubd	%f8, %f14, %f14
	sethi	%hi(.LC102), %g1
	fmuld	%f14, %f18, %f18
	faddd	%f18, %f12, %f10
	ldd	[%g1+%lo(.LC102)], %f12
	b	.L894
	 fmuld	%f14, %f12, %f12
	.size	NavComputeTroposphericDelay, .-NavComputeTroposphericDelay
	.section	.rodata.cst8
	.align 8
.LC173:
	.long	1071292350
	.long	1992864825
	.align 8
.LC174:
	.long	-1076191298
	.long	1992864825
	.align 8
.LC175:
	.long	1089573888
	.long	0
	.align 8
.LC176:
	.long	0
	.long	0
	.align 8
.LC177:
	.long	-1065402368
	.long	0
	.align 8
.LC178:
	.long	1066524486
	.long	2723321923
	.align 8
.LC179:
	.long	1080459264
	.long	0
	.align 8
.LC180:
	.long	1069295861
	.long	3264175145
	.align 8
.LC181:
	.long	1066143422
	.long	3752083430
	.align 8
.LC182:
	.long	1066829611
	.long	34359738
	.align 8
.LC183:
	.long	1074340347
	.long	1413752350
	.align 8
.LC184:
	.long	1073340219
	.long	1683627180
	.align 8
.LC185:
	.long	1068524109
	.long	3539053052
	.align 8
.LC186:
	.long	1088755712
	.long	0
	.align 8
.LC187:
	.long	1089804288
	.long	0
	.align 8
.LC188:
	.long	1073741824
	.long	0
	.align 8
.LC189:
	.long	1074266112
	.long	0
	.align 8
.LC190:
	.long	1071707586
	.long	2405181686
	.align 8
.LC191:
	.long	1076887552
	.long	0
	.align 8
.LC192:
	.long	1072693248
	.long	0
	.align 8
.LC193:
	.long	1088986112
	.long	0
	.align 8
.LC194:
	.long	1075388923
	.long	1413752350
	.align 8
.LC195:
	.long	1073290936
	.long	1374389535
	.align 8
.LC196:
	.long	1076101120
	.long	0
	.align 8
.LC197:
	.long	-1071513600
	.long	0
	.align 8
.LC198:
	.long	1074790400
	.long	0
	.align 8
.LC199:
	.long	1075052544
	.long	0
	.align 8
.LC200:
	.long	1071644672
	.long	0
	.align 8
.LC201:
	.long	1077411840
	.long	0
	.align 8
.LC202:
	.long	1102175864
	.long	1241513984
	.section	.text.NavComputeIonosphericDelay,"ax",@progbits
	.align 4
	.global NavComputeIonosphericDelay
	.type	NavComputeIonosphericDelay, #function
	.proc	020
NavComputeIonosphericDelay:
	save	%sp, -232, %sp
	sethi	%hi(NavprocData), %i5
	or	%i5, %lo(NavprocData), %i5
	ldd	[%i5+720], %f12
	std	%f12, [%fp-8]
	sethi	%hi(.LC177), %g1
	ldd	[%i5+728], %f8
	ldd	[%g1+%lo(.LC177)], %f10
	fcmpd	%f8, %f10
	nop
	fbe	.L1023
	 mov	1, %g3
	fcmpd	%f12, %f10
	nop
	fbne,a	.L1023
	 mov	0, %g3
.L1023:
	sll	%i0, 4, %g2
	ldd	[%g1+%lo(.LC177)], %f10
	add	%i5, %g2, %g2
	ldd	[%g2+360], %f18
	fcmpd	%f18, %f10
	nop
	fbne	.L1070
	 add	%i0, 23, %g2
	mov	1, %g3
	ldd	[%g1+%lo(.LC177)], %f10
.L1070:
	sll	%g2, 4, %g2
	ldd	[%i5+%g2], %f16
	fcmpd	%f16, %f10
	nop
	fbne	.L1071
	 sethi	%hi(NavIonoCorrction), %g2
	mov	1, %g3
	ldd	[%g1+%lo(.LC177)], %f10
.L1071:
	ldd	[%g2+%lo(NavIonoCorrction)], %f14
	fcmpd	%f14, %f10
	nop
	fbne	.L1027
	 std	%f14, [%fp-32]
	mov	1, %g3
	ldd	[%g1+%lo(.LC177)], %f10
.L1027:
	or	%g2, %lo(NavIonoCorrction), %g2
	ldd	[%g2+8], %f20
	fcmpd	%f20, %f10
	nop
	fbne	.L1028
	 std	%f20, [%fp-40]
	mov	1, %g3
	ldd	[%g1+%lo(.LC177)], %f10
.L1028:
	ldd	[%g2+16], %f22
	fcmpd	%f22, %f10
	nop
	fbne	.L1029
	 std	%f22, [%fp-48]
	mov	1, %g3
.L1029:
	ldd	[%g2+24], %f10
	std	%f10, [%fp-56]
	ldd	[%g1+%lo(.LC177)], %f10
	ldd	[%fp-56], %f12
	fcmpd	%f12, %f10
	nop
	fbne	.L1072
	 ldd	[%g2+32], %f12
	mov	1, %g3
	ldd	[%g1+%lo(.LC177)], %f10
.L1072:
	fcmpd	%f12, %f10
	nop
	fbne	.L1073
	 ldd	[%g2+40], %f14
	mov	1, %g3
	ldd	[%g1+%lo(.LC177)], %f10
.L1073:
	fcmpd	%f14, %f10
	nop
	fbne	.L1074
	 ldd	[%g2+48], %f20
	mov	1, %g3
	ldd	[%g1+%lo(.LC177)], %f10
.L1074:
	fcmpd	%f20, %f10
	nop
	fbne	.L1065
	 std	%f20, [%fp-16]
.L1033:
	add	%i0, 75, %i0
	ldd	[%g1+%lo(.LC177)], %f8
	sll	%i0, 3, %i0
	std	%f8, [%i5+%i0]
	jmp	%i7+8
	 restore
.L1065:
	ldd	[%g2+56], %f22
	fcmpd	%f22, %f10
	nop
	fbe	.L1033
	 std	%f22, [%fp-24]
	cmp	%g3, 1
	be	.L1033
	 sethi	%hi(.LC179), %i4
	sethi	%hi(.LC178), %g1
	ldd	[%g1+%lo(.LC178)], %f20
	fmuld	%f18, %f20, %f18
	ldd	[%i4+%lo(.LC179)], %f10
	sethi	%hi(.LC180), %g1
	fdivd	%f16, %f10, %f20
	std	%f20, [%fp-64]
	ldd	[%g1+%lo(.LC180)], %f20
	ldd	[%fp-64], %f22
	sethi	%hi(.LC181), %g1
	ldd	[%g1+%lo(.LC181)], %f16
	faddd	%f22, %f20, %f20
	sethi	%hi(.LC182), %g1
	fdivd	%f16, %f20, %f20
	ldd	[%g1+%lo(.LC182)], %f16
	fsubd	%f20, %f16, %f22
	std	%f18, [%fp-128]
	std	%f8, [%fp-80]
	std	%f10, [%fp-88]
	std	%f12, [%fp-96]
	std	%f14, [%fp-104]
	std	%f18, [%fp-120]
	ldd	[%fp-128], %o0
	call	cos, 0
	 std	%f22, [%fp-72]
	ldd	[%fp-88], %f10
	ldd	[%fp-80], %f8
	fdivd	%f8, %f10, %f8
	ldd	[%fp-72], %f10
	sethi	%hi(.LC173), %g1
	fmuld	%f0, %f10, %f0
	ldd	[%fp-96], %f12
	faddd	%f8, %f0, %f8
	ldd	[%g1+%lo(.LC173)], %f10
	ldd	[%fp-104], %f14
	fcmped	%f8, %f10
	nop
	fbule	.L1066
	 ldd	[%fp-120], %f18
	fmovs	%f10, %f8
.L1075:
	fmovs	%f11, %f9
	std	%f12, [%fp-96]
.L1068:
	std	%f14, [%fp-104]
	std	%f18, [%fp-128]
	std	%f8, [%fp-80]
	call	sin, 0
	 ldd	[%fp-128], %o0
	ldd	[%fp-80], %f8
	ldd	[%fp-72], %f18
	sethi	%hi(.LC183), %g1
	fmuld	%f0, %f18, %f16
	ldd	[%g1+%lo(.LC183)], %f10
	fmuld	%f8, %f10, %f20
	std	%f10, [%fp-88]
	std	%f20, [%fp-128]
	std	%f16, [%fp-112]
	call	cos, 0
	 ldd	[%fp-128], %o0
	ldd	[%fp-112], %f16
	ldd	[%fp-8], %f22
	ldd	[%i4+%lo(.LC179)], %f18
	fdivd	%f22, %f18, %f18
	sethi	%hi(.LC184), %g1
	ldd	[%fp-88], %f10
	fdivd	%f16, %f0, %f0
	faddd	%f18, %f0, %f16
	ldd	[%g1+%lo(.LC184)], %f18
	fsubd	%f16, %f18, %f18
	fmuld	%f18, %f10, %f20
	std	%f16, [%fp-112]
	std	%f20, [%fp-128]
	call	cos, 0
	 ldd	[%fp-128], %o0
	ldd	[%fp-80], %f8
	sethi	%hi(.LC185), %g2
	ldd	[%g2+%lo(.LC185)], %f18
	sethi	%hi(.LC186), %g2
	fmuld	%f0, %f18, %f0
	faddd	%f0, %f8, %f22
	ldd	[%g2+%lo(.LC186)], %f8
	sethi	%hi(.LC187), %g1
	std	%f22, [%fp-8]
	ldd	[%g1+%lo(.LC187)], %f10
	ldd	[%fp-112], %f16
	st	%i1, [%fp-132]
	fmuld	%f16, %f8, %f16
	ld	[%fp-132], %f23
	fitod	%f23, %f8
	faddd	%f16, %f8, %f18
	std	%f10, [%fp-88]
	std	%f18, [%fp-128]
	ldd	[%g1+%lo(.LC187)], %o2
	call	fmod, 0
	 ldd	[%fp-128], %o0
	ldd	[%fp-88], %f10
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%fp-96], %f12
	fcmped	%f8, %f10
	nop
	fbule	.L1062
	 ldd	[%fp-104], %f14
	fsubd	%f8, %f10, %f8
	sethi	%hi(.LC176), %i2
.L1039:
	ldd	[%fp-8], %f20
.L1069:
	fmuld	%f14, %f20, %f14
	faddd	%f12, %f14, %f12
	std	%f8, [%fp-80]
	ldd	[%fp-8], %o0
	std	%f12, [%fp-96]
	sethi	%hi(.LC188), %i3
	call	pow, 0
	 ldd	[%i3+%lo(.LC188)], %o2
	ldd	[%fp-96], %f12
	ldd	[%fp-16], %f22
	fmuld	%f22, %f0, %f0
	faddd	%f12, %f0, %f12
	sethi	%hi(.LC189), %i4
	std	%f12, [%fp-96]
	ldd	[%fp-8], %o0
	call	pow, 0
	 ldd	[%i4+%lo(.LC189)], %o2
	ldd	[%fp-24], %f10
	sethi	%hi(.LC175), %g1
	fmuld	%f10, %f0, %f0
	ldd	[%fp-96], %f12
	ldd	[%g1+%lo(.LC175)], %f10
	faddd	%f12, %f0, %f12
	fcmped	%f12, %f10
	nop
	fbuge	.L1041
	 ldd	[%fp-80], %f8
	fmovs	%f10, %f12
	fmovs	%f11, %f13
.L1041:
	sethi	%hi(.LC190), %g1
	ldd	[%fp-64], %f14
	ldd	[%g1+%lo(.LC190)], %f10
	fsubd	%f10, %f14, %f14
	ldd	[%i4+%lo(.LC189)], %o2
	std	%f14, [%fp-128]
	std	%f8, [%fp-80]
	ldd	[%fp-128], %o0
	call	pow, 0
	 std	%f12, [%fp-96]
	sethi	%hi(.LC191), %g1
	sethi	%hi(.LC192), %i1
	ldd	[%g1+%lo(.LC191)], %f16
	ldd	[%i1+%lo(.LC192)], %f14
	sethi	%hi(.LC193), %g1
	ldd	[%g1+%lo(.LC193)], %f18
	ldd	[%i2+%lo(.LC176)], %f10
	sethi	%hi(.LC194), %g1
	ldd	[%fp-96], %f12
	fmuld	%f0, %f16, %f0
	ldd	[%fp-80], %f8
	faddd	%f0, %f14, %f16
	fsubd	%f8, %f18, %f8
	ldd	[%g1+%lo(.LC194)], %f14
	fmuld	%f8, %f14, %f8
	fdivd	%f8, %f12, %f18
	std	%f16, [%fp-24]
	std	%f18, [%fp-16]
	std	%f10, [%fp-88]
	ldd	[%i2+%lo(.LC176)], %o2
	call	pow, 0
	 ldd	[%fp-8], %o0
	ldd	[%fp-8], %o0
	call	pow, 0
	 ldd	[%i1+%lo(.LC192)], %o2
	ldd	[%fp-8], %o0
	call	pow, 0
	 ldd	[%i3+%lo(.LC188)], %o2
	ldd	[%fp-8], %o0
	call	pow, 0
	 ldd	[%i4+%lo(.LC189)], %o2
	ldd	[%fp-40], %f20
	ldd	[%fp-8], %f22
	ldd	[%fp-32], %f12
	fmuld	%f20, %f22, %f8
	faddd	%f12, %f8, %f8
	ldd	[%fp-8], %o0
	ldd	[%i3+%lo(.LC188)], %o2
	call	pow, 0
	 std	%f8, [%fp-80]
	ldd	[%fp-80], %f8
	ldd	[%fp-48], %f14
	fmuld	%f14, %f0, %f0
	faddd	%f8, %f0, %f8
	ldd	[%fp-8], %o0
	std	%f8, [%fp-80]
	call	pow, 0
	 ldd	[%i4+%lo(.LC189)], %o2
	ldd	[%fp-56], %f16
	ldd	[%fp-80], %f8
	fmuld	%f16, %f0, %f0
	faddd	%f8, %f0, %f18
	std	%f18, [%fp-8]
	ldd	[%fp-88], %f10
	fcmped	%f18, %f10
	nop
	fbl	.L1067
	 ldd	[%i2+%lo(.LC176)], %f20
.L1042:
	call	fabs, 0
	 ldd	[%fp-16], %o0
	sethi	%hi(.LC195), %g1
	ldd	[%g1+%lo(.LC195)], %f8
	sethi	%hi(.LC196), %g1
	fcmped	%f0, %f8
	ldd	[%g1+%lo(.LC196)], %o0
	sethi	%hi(.LC197), %g1
	nop
	fbuge	.L1063
	 ldd	[%g1+%lo(.LC197)], %o2
	call	pow, 0
	 add	%i0, 75, %i0
	fmovs	%f0, %f8
	fmovs	%f1, %f9
	ldd	[%fp-16], %o0
	std	%f8, [%fp-80]
	call	pow, 0
	 ldd	[%i3+%lo(.LC188)], %o2
	sethi	%hi(.LC198), %g1
	fmovs	%f0, %f10
	fmovs	%f1, %f11
	ldd	[%g1+%lo(.LC198)], %o2
	std	%f10, [%fp-88]
	call	pow, 0
	 ldd	[%fp-16], %o0
	sethi	%hi(.LC199), %g1
	ldd	[%g1+%lo(.LC199)], %f12
	ldd	[%fp-80], %f8
	sethi	%hi(.LC200), %g1
	fmuld	%f8, %f12, %f8
	ldd	[%g1+%lo(.LC200)], %f12
	ldd	[%fp-88], %f10
	fmuld	%f10, %f12, %f10
	ldd	[%i1+%lo(.LC192)], %f12
	sethi	%hi(.LC201), %g1
	fsubd	%f12, %f10, %f10
	ldd	[%fp-8], %f22
	ldd	[%g1+%lo(.LC201)], %f12
	fdivd	%f0, %f12, %f0
	faddd	%f10, %f0, %f10
	fmuld	%f10, %f22, %f10
	faddd	%f8, %f10, %f8
	ldd	[%fp-24], %f10
	fmuld	%f8, %f10, %f0
	sll	%i0, 3, %i0
	sethi	%hi(.LC202), %g1
	ldd	[%g1+%lo(.LC202)], %f10
	fmuld	%f0, %f10, %f8
	std	%f8, [%i5+%i0]
	jmp	%i7+8
	 restore
.L1066:
	sethi	%hi(.LC174), %g1
	ldd	[%g1+%lo(.LC174)], %f10
	fcmped	%f8, %f10
	nop
	fbl,a	.L1075
	 fmovs	%f10, %f8
	b	.L1068
	 std	%f12, [%fp-96]
.L1062:
	sethi	%hi(.LC176), %i2
	ldd	[%i2+%lo(.LC176)], %f16
	fcmped	%f8, %f16
	nop
	fbl,a	.L1039
	 faddd	%f8, %f10, %f8
	b	.L1069
	 ldd	[%fp-8], %f20
.L1063:
	call	pow, 0
	 add	%i0, 75, %i0
	sethi	%hi(.LC199), %g1
	ldd	[%fp-24], %f12
	ldd	[%g1+%lo(.LC199)], %f8
	fmuld	%f12, %f8, %f8
	fmuld	%f8, %f0, %f0
	sll	%i0, 3, %i0
	sethi	%hi(.LC202), %g1
	ldd	[%g1+%lo(.LC202)], %f10
	fmuld	%f0, %f10, %f8
	std	%f8, [%i5+%i0]
	jmp	%i7+8
	 restore
.L1067:
	b	.L1042
	 std	%f20, [%fp-8]
	.size	NavComputeIonosphericDelay, .-NavComputeIonosphericDelay
	.section	.rodata.cst8
	.align 8
.LC203:
	.long	1076101120
	.long	0
	.align 8
.LC204:
	.long	1076625408
	.long	0
	.align 8
.LC205:
	.long	1074783062
	.long	2531625523
	.align 8
.LC206:
	.long	-1072431104
	.long	0
	.align 8
.LC207:
	.long	1075653408
	.long	1000798353
	.align 8
.LC208:
	.long	1091728640
	.long	0
	.align 8
.LC209:
	.long	1092777216
	.long	0
	.align 8
.LC210:
	.long	-1055755008
	.long	0
	.align 8
.LC211:
	.long	1073741824
	.long	0
	.align 8
.LC212:
	.long	1044740494
	.long	3794832442
	.align 8
.LC213:
	.long	1072693248
	.long	0
	.section	.text.NavComputeSatVelocity,"ax",@progbits
	.align 4
	.global NavComputeSatVelocity
	.type	NavComputeSatVelocity, #function
	.proc	020
NavComputeSatVelocity:
	save	%sp, -248, %sp
	sethi	%hi(.LC204), %g1
	sethi	%hi(.LC203), %i5
	ldd	[%g1+%lo(.LC204)], %o2
	call	pow, 0
	 ldd	[%i5+%lo(.LC203)], %o0
	sethi	%hi(.LC206), %g1
	ldd	[%g1+%lo(.LC206)], %o2
	sethi	%hi(.LC205), %g1
	ldd	[%g1+%lo(.LC205)], %f8
	fmuld	%f0, %f8, %f0
	ldd	[%i5+%lo(.LC203)], %o0
	call	pow, 0
	 std	%f0, [%fp-24]
	st	%i0, [%fp-140]
	ld	[%fp-140], %f10
	add	%i1, 13, %g1
	fitod	%f10, %f8
	sll	%g1, 3, %g1
	sethi	%hi(NavprocData), %l0
	or	%l0, %lo(NavprocData), %l0
	ldd	[%l0+%g1], %f10
	sethi	%hi(.LC207), %g2
	fsubd	%f8, %f10, %f8
	ldd	[%g2+%lo(.LC207)], %f10
	sethi	%hi(NavSubFrame2Data), %i2
	fmuld	%f0, %f10, %f0
	or	%i2, %lo(NavSubFrame2Data), %i2
	sll	%i1, 4, %i5
	sll	%i1, 6, %i3
	std	%f0, [%fp-72]
	add	%i5, %i3, %i3
	add	%i2, %i3, %g1
	ldd	[%g1+8], %f10
	sethi	%hi(.LC208), %g1
	fsubd	%f8, %f10, %f8
	ldd	[%g1+%lo(.LC208)], %f10
	fcmped	%f8, %f10
	nop
	fbul	.L1085
	 nop
	sethi	%hi(.LC209), %g1
	ldd	[%g1+%lo(.LC209)], %f10
	fsubd	%f8, %f10, %f8
.L1079:
	add	%i2, %i3, %g1
	sethi	%hi(.LC211), %l2
	ldd	[%g1+24], %o0
	ldd	[%l2+%lo(.LC211)], %o2
	call	pow, 0
	 std	%f8, [%fp-96]
	ldd	[%fp-24], %f12
	fdivd	%f12, %f0, %f10
	std	%f0, [%fp-40]
	std	%f10, [%fp-16]
	add	%fp, -16, %o0
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -8, %o1
	ldd	[%fp-8], %f10
	sll	%i1, 7, %i4
	sethi	%hi(NavSubFrame1Data), %l1
	add	%i5, %i4, %i4
	or	%l1, %lo(NavSubFrame1Data), %l1
	add	%l1, %i4, %g1
	ldd	[%g1+40], %f12
	ldd	[%fp-40], %f16
	ldd	[%fp-96], %f8
	fdivd	%f10, %f16, %f14
	sethi	%hi(.LC212), %i0
	faddd	%f14, %f12, %f20
	ldd	[%i2+%i3], %f10
	fmuld	%f20, %f8, %f8
	std	%f20, [%fp-48]
	faddd	%f8, %f10, %f12
	or	%i0, %lo(.LC212), %i0
	std	%f12, [%fp-32]
	std	%f12, [%fp-24]
	add	%i2, %i3, %i5
.L1086:
	ldd	[%i5+16], %f8
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f8, [%fp-96]
	ldd	[%fp-96], %f8
	ldd	[%fp-32], %f14
	fmuld	%f8, %f0, %f0
	ldd	[%fp-24], %f16
	faddd	%f0, %f14, %f0
	fsubd	%f0, %f16, %f16
	std	%f0, [%fp-24]
	std	%f16, [%fp-152]
	call	fabs, 0
	 ldd	[%fp-152], %o0
	ldd	[%i0], %f8
	fcmped	%f0, %f8
	nop
	fbg,a	.L1086
	 add	%i2, %i3, %i5
	ldd	[%i5+16], %f10
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-104], %f10
	ldd	[%fp-48], %f8
	sethi	%hi(.LC213), %g1
	fmuld	%f10, %f0, %f0
	ldd	[%g1+%lo(.LC213)], %f20
	fsubd	%f20, %f0, %f10
	fdivd	%f8, %f10, %f10
	ldd	[%l2+%lo(.LC211)], %o2
	ldd	[%i5+16], %o0
	call	pow, 0
	 std	%f10, [%fp-104]
	sethi	%hi(.LC213), %g1
	ldd	[%g1+%lo(.LC213)], %f12
	fsubd	%f12, %f0, %f0
	add	%fp, -16, %o0
	add	%fp, -8, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-16]
	call	sin, 0
	 ldd	[%fp-24], %o0
	ldd	[%i5+16], %f14
	ldd	[%fp-8], %f8
	fmuld	%f0, %f8, %f8
	ldd	[%fp-24], %o0
	std	%f8, [%fp-96]
	call	cos, 0
	 std	%f14, [%fp-120]
	ldd	[%fp-120], %f14
	sethi	%hi(.LC213), %g1
	ldd	[%fp-96], %f8
	ldd	[%g1+%lo(.LC213)], %f12
	fmuld	%f14, %f0, %f0
	fsubd	%f12, %f0, %f14
	fdivd	%f8, %f14, %f14
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f14, [%fp-120]
	ldd	[%i5+16], %f8
	fsubd	%f0, %f8, %f12
	ldd	[%fp-24], %o0
	std	%f8, [%fp-96]
	call	cos, 0
	 std	%f12, [%fp-112]
	ldd	[%fp-120], %f14
	sethi	%hi(.LC213), %g1
	std	%f14, [%fp-152]
	ldd	[%fp-96], %f8
	ldd	[%g1+%lo(.LC213)], %f14
	ldd	[%fp-112], %f12
	fmuld	%f8, %f0, %f0
	fsubd	%f14, %f0, %f8
	fdivd	%f12, %f8, %f14
	ldd	[%fp-152], %o0
	std	%f14, [%fp-152]
	call	atan2, 0
	 ldd	[%fp-152], %o2
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f0, [%fp-32]
	ldd	[%i5+16], %f8
	ldd	[%fp-104], %f10
	fmuld	%f0, %f10, %f10
	ldd	[%fp-32], %o0
	std	%f8, [%fp-96]
	call	cos, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-96], %f8
	sethi	%hi(.LC213), %g1
	ldd	[%fp-104], %f10
	ldd	[%g1+%lo(.LC213)], %f16
	fmuld	%f8, %f0, %f0
	faddd	%f0, %f16, %f8
	fmuld	%f10, %f8, %f8
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f8, [%fp-96]
	ldd	[%i5+16], %f12
	fmovs	%f0, %f10
	fmovs	%f1, %f11
	ldd	[%fp-24], %o0
	std	%f10, [%fp-104]
	call	cos, 0
	 std	%f12, [%fp-112]
	ldd	[%fp-112], %f12
	sethi	%hi(.LC213), %g1
	ldd	[%fp-104], %f10
	ldd	[%g1+%lo(.LC213)], %f14
	fmuld	%f12, %f0, %f0
	fsubd	%f14, %f0, %f12
	fmuld	%f10, %f12, %f10
	add	%l1, %i4, %i4
	ldd	[%fp-32], %f14
	ldd	[%i5+40], %f18
	ldd	[%fp-96], %f8
	faddd	%f14, %f18, %f18
	fdivd	%f8, %f10, %f20
	faddd	%f18, %f18, %f16
	ldd	[%i4+64], %f10
	std	%f16, [%fp-32]
	std	%f18, [%fp-136]
	std	%f20, [%fp-56]
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f10, [%fp-104]
	ldd	[%i4+56], %f8
	ldd	[%fp-104], %f10
	fmuld	%f10, %f0, %f10
	ldd	[%fp-32], %o0
	std	%f8, [%fp-96]
	call	cos, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-96], %f8
	ldd	[%i4+96], %f14
	ldd	[%fp-104], %f10
	fmuld	%f8, %f0, %f0
	faddd	%f10, %f0, %f8
	ldd	[%fp-32], %o0
	std	%f8, [%fp-96]
	call	sin, 0
	 std	%f14, [%fp-120]
	ldd	[%i4+88], %f10
	ldd	[%fp-120], %f14
	fmuld	%f14, %f0, %f14
	ldd	[%fp-32], %o0
	std	%f10, [%fp-104]
	call	cos, 0
	 std	%f14, [%fp-120]
	ldd	[%fp-104], %f10
	ldd	[%i4+80], %f12
	ldd	[%fp-120], %f14
	fmuld	%f10, %f0, %f0
	faddd	%f14, %f0, %f10
	ldd	[%fp-32], %o0
	std	%f10, [%fp-104]
	call	sin, 0
	 std	%f12, [%fp-112]
	ldd	[%i4+72], %f14
	ldd	[%fp-112], %f12
	fmuld	%f12, %f0, %f12
	ldd	[%fp-32], %o0
	std	%f12, [%fp-112]
	call	cos, 0
	 std	%f14, [%fp-120]
	ldd	[%fp-120], %f14
	ldd	[%i5+16], %f16
	ldd	[%fp-112], %f12
	fmuld	%f14, %f0, %f0
	faddd	%f12, %f0, %f14
	ldd	[%fp-24], %o0
	std	%f14, [%fp-120]
	call	cos, 0
	 std	%f16, [%fp-128]
	ldd	[%i5+56], %f12
	sethi	%hi(.LC213), %g1
	ldd	[%fp-128], %f16
	ldd	[%g1+%lo(.LC213)], %f20
	ldd	[%fp-120], %f14
	fmuld	%f16, %f0, %f0
	fsubd	%f20, %f0, %f16
	faddd	%f14, %f12, %f20
	ldd	[%fp-40], %f12
	ldd	[%fp-104], %f10
	fmuld	%f16, %f12, %f16
	faddd	%f16, %f10, %f12
	ldd	[%fp-40], %f16
	std	%f12, [%fp-64]
	ldd	[%i4+104], %f12
	ldd	[%i5+8], %f14
	ldd	[%i5+16], %f10
	add	%i1, 1, %i3
	fmuld	%f16, %f10, %f10
	sll	%i3, 3, %i3
	ldd	[%l0+%i3], %f16
	fsubd	%f16, %f14, %f16
	fmuld	%f16, %f12, %f16
	faddd	%f20, %f16, %f12
	ldd	[%fp-24], %o0
	std	%f12, [%fp-32]
	call	sin, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-104], %f10
	ldd	[%fp-48], %f16
	ldd	[%i5+16], %f14
	fmuld	%f10, %f0, %f0
	fmuld	%f0, %f16, %f10
	ldd	[%fp-24], %o0
	std	%f10, [%fp-104]
	call	cos, 0
	 std	%f14, [%fp-120]
	ldd	[%fp-120], %f14
	sethi	%hi(.LC213), %g1
	ldd	[%fp-96], %f8
	fmuld	%f14, %f0, %f0
	ldd	[%g1+%lo(.LC213)], %f14
	ldd	[%fp-136], %f18
	ldd	[%fp-104], %f10
	faddd	%f18, %f8, %f20
	fsubd	%f14, %f0, %f12
	faddd	%f20, %f20, %f8
	fdivd	%f10, %f12, %f12
	ldd	[%i4+88], %f14
	std	%f20, [%fp-24]
	std	%f8, [%fp-40]
	std	%f12, [%fp-112]
	ldd	[%fp-40], %o0
	call	sin, 0
	 std	%f14, [%fp-120]
	ldd	[%i4+96], %f8
	ldd	[%fp-120], %f14
	fmuld	%f14, %f0, %f14
	ldd	[%fp-40], %o0
	std	%f8, [%fp-96]
	call	cos, 0
	 std	%f14, [%fp-120]
	ldd	[%fp-96], %f8
	ldd	[%fp-120], %f14
	ldd	[%fp-112], %f12
	ldd	[%i4+56], %f10
	fmuld	%f8, %f0, %f0
	fsubd	%f14, %f0, %f8
	ldd	[%fp-56], %f14
	faddd	%f8, %f8, %f8
	fmuld	%f8, %f14, %f8
	fsubd	%f12, %f8, %f16
	ldd	[%fp-40], %o0
	std	%f16, [%fp-48]
	call	sin, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-104], %f10
	fmuld	%f10, %f0, %f8
	ldd	[%i4+64], %f10
	ldd	[%fp-40], %o0
	std	%f8, [%fp-96]
	call	cos, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-96], %f8
	ldd	[%fp-104], %f10
	ldd	[%i4+104], %f12
	ldd	[%fp-56], %f20
	fmuld	%f10, %f0, %f0
	fsubd	%f8, %f0, %f10
	ldd	[%i4+72], %f8
	faddd	%f10, %f10, %f10
	fmuld	%f10, %f20, %f10
	fsubd	%f20, %f10, %f14
	std	%f12, [%fp-112]
	std	%f14, [%fp-80]
	ldd	[%fp-40], %o0
	call	sin, 0
	 std	%f8, [%fp-96]
	ldd	[%fp-96], %f8
	fmuld	%f8, %f0, %f10
	ldd	[%i4+80], %f8
	ldd	[%fp-40], %o0
	std	%f8, [%fp-96]
	call	cos, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-96], %f8
	ldd	[%fp-56], %f16
	ldd	[%fp-112], %f12
	ldd	[%fp-104], %f10
	fmuld	%f8, %f0, %f0
	fsubd	%f10, %f0, %f8
	faddd	%f8, %f8, %f8
	fmuld	%f8, %f16, %f8
	fsubd	%f12, %f8, %f20
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f20, [%fp-56]
	ldd	[%fp-64], %f10
	fmuld	%f0, %f10, %f8
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f8, [%fp-96]
	ldd	[%fp-64], %f12
	fmuld	%f0, %f12, %f0
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f0, [%fp-40]
	ldd	[%fp-48], %f14
	fmuld	%f0, %f14, %f10
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-80], %f20
	ldd	[%fp-104], %f10
	ldd	[%fp-64], %f16
	fmuld	%f0, %f16, %f0
	fmuld	%f0, %f20, %f12
	fsubd	%f10, %f12, %f14
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f14, [%fp-88]
	ldd	[%fp-48], %f16
	fmuld	%f0, %f16, %f14
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f14, [%fp-120]
	ldd	[%i5+48], %f12
	ldd	[%fp-72], %f20
	fsubd	%f12, %f20, %f20
	ldd	[%fp-64], %f16
	std	%f20, [%fp-48]
	ldd	[%fp-80], %f20
	ldd	[%l0+%i3], %f10
	fmuld	%f0, %f16, %f0
	ldd	[%fp-120], %f14
	fmuld	%f0, %f20, %f18
	ldd	[%i5+8], %f16
	faddd	%f14, %f18, %f20
	fsubd	%f10, %f16, %f16
	ldd	[%i5+32], %f14
	std	%f20, [%fp-64]
	fmuld	%f12, %f16, %f12
	ldd	[%fp-72], %f16
	faddd	%f12, %f14, %f12
	fmuld	%f16, %f10, %f10
	fsubd	%f12, %f10, %f20
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f20, [%fp-24]
	ldd	[%fp-88], %f16
	ldd	[%fp-40], %f10
	ldd	[%fp-48], %f14
	fmuld	%f0, %f10, %f0
	fmuld	%f0, %f14, %f12
	fsubd	%f16, %f12, %f12
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f12, [%fp-112]
	ldd	[%fp-112], %f12
	fmuld	%f12, %f0, %f12
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f12, [%fp-112]
	ldd	[%fp-96], %f8
	ldd	[%fp-48], %f20
	ldd	[%fp-64], %f10
	fmuld	%f8, %f20, %f8
	fmuld	%f0, %f10, %f0
	faddd	%f8, %f0, %f14
	std	%f8, [%fp-96]
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f14, [%fp-120]
	ldd	[%fp-56], %f20
	ldd	[%fp-40], %f16
	ldd	[%fp-120], %f14
	fmuld	%f0, %f16, %f0
	fmuld	%f0, %f20, %f10
	fsubd	%f14, %f10, %f10
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-104], %f10
	ldd	[%fp-112], %f12
	fmuld	%f10, %f0, %f0
	fsubd	%f12, %f0, %f10
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f10, [%fp-104]
	ldd	[%fp-40], %f12
	ldd	[%fp-48], %f14
	ldd	[%fp-88], %f16
	fmuld	%f0, %f12, %f0
	fmuld	%f0, %f14, %f12
	fsubd	%f16, %f12, %f12
	ldd	[%fp-24], %o0
	call	sin, 0
	 std	%f12, [%fp-112]
	ldd	[%fp-112], %f12
	fmuld	%f12, %f0, %f12
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f12, [%fp-112]
	ldd	[%fp-64], %f20
	ldd	[%fp-96], %f8
	fmuld	%f0, %f20, %f0
	faddd	%f8, %f0, %f8
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f8, [%fp-96]
	ldd	[%fp-40], %f14
	ldd	[%fp-56], %f16
	ldd	[%fp-96], %f8
	fmuld	%f0, %f14, %f0
	fmuld	%f0, %f16, %f14
	fsubd	%f8, %f14, %f8
	ldd	[%fp-24], %o0
	call	cos, 0
	 std	%f8, [%fp-96]
	ldd	[%fp-96], %f8
	ldd	[%fp-112], %f12
	fmuld	%f8, %f0, %f0
	faddd	%f12, %f0, %f8
	ldd	[%fp-32], %o0
	call	sin, 0
	 std	%f8, [%fp-96]
	ldd	[%fp-64], %f20
	fmuld	%f0, %f20, %f12
	ldd	[%fp-32], %o0
	call	cos, 0
	 std	%f12, [%fp-112]
	ldd	[%fp-40], %f14
	ldd	[%fp-112], %f12
	ldd	[%fp-104], %f10
	ldd	[%fp-96], %f8
	add	%i1, %i1, %g1
	fmuld	%f0, %f14, %f0
	add	%g1, %i1, %i1
	ldd	[%fp-56], %f16
	sll	%i1, 3, %i1
	fmuld	%f0, %f16, %f14
	add	%l0, %i1, %l0
	faddd	%f12, %f14, %f12
	std	%f10, [%l0+456]
	std	%f8, [%l0+464]
	std	%f12, [%l0+472]
	jmp	%i7+8
	 restore
.L1085:
	sethi	%hi(.LC210), %g1
	ldd	[%g1+%lo(.LC210)], %f10
	fcmped	%f8, %f10
	nop
	fbug	.L1079
	 nop
	sethi	%hi(.LC209), %g1
	ldd	[%g1+%lo(.LC209)], %f10
	b	.L1079
	 faddd	%f8, %f10, %f8
	.size	NavComputeSatVelocity, .-NavComputeSatVelocity
	.section	".rodata"
	.align 2
.LC0:
	.half	0
	.half	31
	.half	59
	.half	90
	.half	120
	.half	151
	.half	181
	.half	212
	.half	243
	.half	273
	.half	304
	.half	334
	.half	365
	.section	.rodata.cst8
	.align 8
.LC214:
	.long	0
	.long	0
	.align 8
.LC215:
	.long	-1065402368
	.long	0
	.align 8
.LC216:
	.long	1072693248
	.long	0
	.align 8
.LC217:
	.long	1092777216
	.long	0
	.align 8
.LC218:
	.long	1073741824
	.long	0
	.align 8
.LC219:
	.long	1089804288
	.long	0
	.align 8
.LC220:
	.long	1088755712
	.long	0
	.align 8
.LC221:
	.long	1085022208
	.long	0
	.align 8
.LC222:
	.long	1078853632
	.long	0
	.section	.text.NavFindUTCTime,"ax",@progbits
	.align 4
	.global NavFindUTCTime
	.type	NavFindUTCTime, #function
	.proc	020
NavFindUTCTime:
	save	%sp, -168, %sp
	sethi	%hi(.LC0), %o1
	add	%fp, -28, %o0
	or	%o1, %lo(.LC0), %o1
	call	memcpy, 0
	 mov	26, %o2
	sethi	%hi(NavprocData), %i1
	or	%i1, %lo(NavprocData), %i1
	ld	[%i1+152], %g1
	cmp	%g1, 1
	be	.L1197
	 nop
	ld	[%i1+184], %i4
	cmp	%i4, 0
	ble	.L1198
	 sethi	%hi(NavSubFrame1Data), %i3
	ld	[%i1+188], %g1
	sll	%g1, 4, %g2
	or	%i3, %lo(NavSubFrame1Data), %i3
	sll	%g1, 7, %g1
	add	%g2, %g1, %g1
	add	%i3, %g1, %g1
	ld	[%g1+132], %i5
	st	%i5, [%fp-60]
	sethi	%hi(.LC215), %i2
	ld	[%fp-60], %f12
	ldd	[%i2+%lo(.LC215)], %f10
	fitod	%f12, %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L1089
	 add	%i1, 192, %g2
	b	.L1090
	 mov	0, %g1
.L1091:
	sll	%g3, 4, %g4
	sll	%g3, 7, %g3
	add	%g4, %g3, %g3
	add	%i3, %g3, %g3
	ld	[%g3+132], %i5
	st	%i5, [%fp-60]
	ldd	[%i2+%lo(.LC215)], %f10
	ld	[%fp-60], %f13
	fitod	%f13, %f8
	fcmpd	%f8, %f10
	nop
	fbne	.L1089
	 add	%g2, 4, %g2
.L1090:
	add	%g1, 1, %g1
	cmp	%g1, %i4
	bne,a	.L1091
	 ld	[%g2], %g3
.L1198:
	jmp	%i7+8
	 restore
.L1089:
	sethi	%hi(NavUTCCorr), %g1
	sethi	%hi(86016), %i2
	or	%g1, %lo(NavUTCCorr), %i4
	or	%i2, 384, %i2
	ldd	[%i4+48], %f16
	ldd	[%i4+56], %f12
	sra	%i0, 31, %g2
	wr	%g2, 0, %y
	nop
	nop
	nop
	sdiv	%i0, %i2, %i2
	st	%i2, [%fp-60]
	sethi	%hi(.LC214), %i3
	ld	[%fp-60], %f18
	ldd	[%i3+%lo(.LC214)], %f14
	fcmped	%f16, %f8
	faddd	%f12, %f14, %f14
	nop
	fbug	.L1093
	 fitod	%f18, %f10
	fcmped	%f14, %f10
	nop
	fbg	.L1092
	 sethi	%hi(.LC216), %g2
	ldd	[%g2+%lo(.LC216)], %f18
	faddd	%f12, %f18, %f18
	fcmped	%f10, %f18
	nop
	fbule	.L1093
	 nop
.L1092:
	st	%i0, [%fp-60]
	ld	[%fp-60], %f12
	fitod	%f12, %f10
	ldd	[%i4+40], %f12
	ldd	[%i4+32], %f14
	fsubd	%f8, %f12, %f8
	fsubd	%f10, %f14, %f18
	ldd	[%i4+24], %f12
.L1172:
	ldd	[%g1+%lo(NavUTCCorr)], %f16
	sethi	%hi(.LC218), %g1
	ldd	[%g1+%lo(.LC218)], %o2
	sethi	%hi(.LC217), %g1
	ldd	[%g1+%lo(.LC217)], %f20
	fmuld	%f8, %f20, %f8
	faddd	%f18, %f8, %f8
	ldd	[%i4+8], %f14
	faddd	%f12, %f16, %f16
	fmuld	%f8, %f14, %f14
	ldd	[%i4+16], %f12
	std	%f8, [%fp-72]
	faddd	%f16, %f14, %f8
	ldd	[%fp-72], %o0
	std	%f8, [%fp-40]
	std	%f10, [%fp-48]
	call	pow, 0
	 std	%f12, [%fp-56]
	ldd	[%fp-56], %f12
	sethi	%hi(.LC219), %g1
	fmuld	%f12, %f0, %f0
	ldd	[%fp-40], %f8
	ldd	[%fp-48], %f10
	faddd	%f8, %f0, %f8
	fsubd	%f10, %f8, %f14
	ldd	[%g1+%lo(.LC219)], %o2
	std	%f14, [%fp-72]
	call	fmod, 0
	 ldd	[%fp-72], %o0
	fmovs	%f0, %f8
	fmovs	%f1, %f9
.L1095:
	sethi	%hi(.LC221), %g1
	ldd	[%g1+%lo(.LC221)], %f10
	fdivd	%f8, %f10, %f10
	fdtoi	%f10, %f15
	std	%f8, [%fp-72]
	ldd	[%g1+%lo(.LC221)], %o2
	st	%f15, [%fp-60]
	ldd	[%fp-72], %o0
	std	%f8, [%fp-40]
	call	fmod, 0
	 ld	[%fp-60], %i4
	ldd	[%fp-40], %f8
	sethi	%hi(.LC222), %g1
	std	%f8, [%fp-72]
	ldd	[%g1+%lo(.LC222)], %f8
	fdivd	%f0, %f8, %f0
	fdtoi	%f0, %f18
	ldd	[%g1+%lo(.LC222)], %o2
	st	%f18, [%fp-60]
	ldd	[%fp-72], %o0
	call	fmod, 0
	 ld	[%fp-60], %i0
	sll	%i5, 3, %g2
	fdtoi	%f0, %f0
	sub	%g2, %i5, %i5
	st	%f0, [%fp-60]
	sra	%i5, 31, %o5
	wr	%o5, 0, %y
	nop
	nop
	nop
	sdiv	%i5, 1460, %o7
	sra	%i5, 31, %g3
	wr	%g3, 0, %y
	nop
	nop
	nop
	sdiv	%i5, -1460, %g2
	lduh	[%fp-28], %g1
	add	%g2, %i5, %g3
	smul	%o7, 366, %o7
	sra	%g3, 31, %o5
	wr	%o5, 0, %y
	nop
	nop
	nop
	sdiv	%g3, 365, %g3
	ld	[%fp-60], %g4
	add	%g3, -1, %o5
	add	%g2, %o5, %g2
	smul	%g2, 365, %g2
	add	%g2, 132, %g2
	add	%g2, %o7, %g2
	sub	%i5, %g2, %i5
	cmp	%i5, %g1
	bl	.L1102
	 add	%g3, 1999, %g3
	lduh	[%fp-26], %g2
	cmp	%g2, %i5
	bg,a	.L1103
	 mov	1, %g2
	mov	%g2, %g1
	lduh	[%fp-24], %g2
.L1187:
	cmp	%i5, %g2
	bl,a	.L1103
	 mov	2, %g2
	mov	%g2, %g1
	lduh	[%fp-22], %g2
.L1188:
	cmp	%i5, %g2
	bl,a	.L1175
	 mov	3, %g2
	mov	%g2, %g1
	lduh	[%fp-20], %g2
.L1189:
	cmp	%i5, %g2
	bl,a	.L1103
	 mov	4, %g2
	mov	%g2, %g1
	lduh	[%fp-18], %g2
.L1190:
	cmp	%i5, %g2
	bl,a	.L1103
	 mov	5, %g2
	mov	%g2, %g1
	lduh	[%fp-16], %g2
.L1191:
	cmp	%i5, %g2
	bl,a	.L1103
	 mov	6, %g2
	mov	%g2, %g1
	lduh	[%fp-14], %g2
.L1192:
	cmp	%i5, %g2
	bl,a	.L1103
	 mov	7, %g2
	mov	%g2, %g1
	lduh	[%fp-12], %g2
.L1193:
	cmp	%i5, %g2
	bl,a	.L1103
	 mov	8, %g2
	mov	%g2, %g1
	lduh	[%fp-10], %g2
.L1194:
	cmp	%i5, %g2
	bl,a	.L1103
	 mov	9, %g2
	mov	%g2, %g1
	lduh	[%fp-8], %g2
.L1195:
	cmp	%i5, %g2
	bl,a	.L1103
	 mov	10, %g2
	mov	%g2, %g1
	lduh	[%fp-6], %g2
.L1196:
	cmp	%i5, %g2
	bl,a	.L1103
	 mov	11, %g2
	mov	%g2, %g1
	lduh	[%fp-4], %o7
.L1186:
	cmp	%i5, %o7
	bl	.L1184
	 mov	%o7, %g2
.L1125:
	sll	%g2, 16, %g1
	ldd	[%i3+%lo(.LC214)], %f20
	srl	%g1, 16, %g1
.L1126:
	st	%i5, [%fp-60]
	ld	[%fp-60], %f9
	st	%g3, [%fp-60]
	sub	%i5, %g1, %g1
	ld	[%fp-60], %f12
	add	%g1, %i2, %g1
	st	%g1, [%fp-60]
	and	%i4, 0xff, %i4
	ld	[%fp-60], %f13
	st	%i4, [%fp-60]
	and	%i0, 0xff, %i0
	ld	[%fp-60], %f8
	st	%i0, [%fp-60]
	fitod	%f13, %f18
	fitod	%f9, %f16
	ld	[%fp-60], %f9
	std	%f18, [%i1+960]
	and	%g4, 0xff, %g4
	st	%g4, [%fp-60]
	fitod	%f12, %f14
	ld	[%fp-60], %f18
	fitod	%f8, %f12
	fitod	%f9, %f10
	std	%f16, [%i1+968]
	fitod	%f18, %f8
	std	%f20, [%i1+976]
	std	%f14, [%i1+984]
	std	%f12, [%i1+992]
	std	%f10, [%i1+1000]
	std	%f8, [%i1+1008]
.L1197:
	jmp	%i7+8
	 restore
.L1093:
	fcmped	%f14, %f10
	nop
	fbuge	.L1096
	 nop
	sethi	%hi(.LC216), %g2
	ldd	[%g2+%lo(.LC216)], %f18
	faddd	%f12, %f18, %f18
	fcmped	%f18, %f10
	nop
	fbg,a	.L1185
	 sethi	%hi(.LC219), %g1
.L1096:
	fcmped	%f16, %f8
	nop
	fbuge	.L1160
	 nop
	fcmped	%f14, %f10
	nop
	fbg	.L1100
	 sethi	%hi(.LC216), %g2
	ldd	[%g2+%lo(.LC216)], %f14
	faddd	%f12, %f14, %f12
	fcmped	%f12, %f10
	nop
	fbuge	.L1160
	 nop
.L1100:
	st	%i0, [%fp-60]
	ld	[%fp-60], %f12
	fitod	%f12, %f10
	ldd	[%i4+40], %f12
	ldd	[%i4+32], %f14
	fsubd	%f8, %f12, %f8
	fsubd	%f10, %f14, %f18
	b	.L1172
	 ldd	[%i4+64], %f12
.L1160:
	b	.L1095
	 ldd	[%i3+%lo(.LC214)], %f8
.L1102:
	lduh	[%fp-26], %g1
	cmp	%i5, %g1
	bge	.L1187
	 lduh	[%fp-24], %g2
	lduh	[%fp-24], %g1
	cmp	%i5, %g1
	bge	.L1188
	 lduh	[%fp-22], %g2
	lduh	[%fp-22], %g1
	cmp	%i5, %g1
	bge	.L1189
	 lduh	[%fp-20], %g2
	lduh	[%fp-20], %g1
	cmp	%i5, %g1
	bge	.L1190
	 lduh	[%fp-18], %g2
	lduh	[%fp-18], %g1
	cmp	%i5, %g1
	bge	.L1191
	 lduh	[%fp-16], %g2
	lduh	[%fp-16], %g1
	cmp	%i5, %g1
	bge	.L1192
	 lduh	[%fp-14], %g2
	lduh	[%fp-14], %g1
	cmp	%i5, %g1
	bge	.L1193
	 lduh	[%fp-12], %g2
	lduh	[%fp-12], %g1
	cmp	%i5, %g1
	bge	.L1194
	 lduh	[%fp-10], %g2
	lduh	[%fp-10], %g1
	cmp	%i5, %g1
	bge	.L1195
	 lduh	[%fp-8], %g2
	lduh	[%fp-8], %g1
	cmp	%i5, %g1
	bge,a	.L1196
	 lduh	[%fp-6], %g2
	lduh	[%fp-6], %g1
	cmp	%i5, %g1
	bl	.L1125
	 lduh	[%fp-4], %g2
	b	.L1186
	 lduh	[%fp-4], %o7
.L1185:
	st	%i0, [%fp-60]
	ld	[%fp-60], %f15
	ldd	[%g1+%lo(.LC219)], %f10
	fitod	%f15, %f12
	ldd	[%g1+%lo(.LC219)], %o2
	sethi	%hi(.LC220), %g1
	ldd	[%g1+%lo(.LC220)], %f8
	fsubd	%f12, %f8, %f14
	std	%f8, [%fp-40]
	std	%f14, [%fp-72]
	std	%f10, [%fp-48]
	call	fmod, 0
	 ldd	[%fp-72], %o0
	ldd	[%fp-40], %f8
	ldd	[%i4+64], %f14
	ldd	[%i4+24], %f12
	faddd	%f0, %f8, %f0
	ldd	[%fp-48], %f10
	std	%f0, [%fp-72]
	faddd	%f14, %f10, %f10
	fsubd	%f10, %f12, %f8
	ldd	[%fp-72], %o0
	std	%f8, [%fp-72]
	call	fmod, 0
	 ldd	[%fp-72], %o2
	fmovs	%f0, %f8
	b	.L1095
	 fmovs	%f1, %f9
.L1175:
.L1103:
	st	%g2, [%fp-60]
	ld	[%fp-60], %f8
	b	.L1126
	 fitod	%f8, %f20
.L1184:
	b	.L1103
	 mov	12, %g2
	.size	NavFindUTCTime, .-NavFindUTCTime
	.section	.text.calc_checksum,"ax",@progbits
	.align 4
	.global calc_checksum
	.type	calc_checksum, #function
	.proc	014
calc_checksum:
	ldsb	[%o0+1], %g2
	add	%o0, 1, %g1
	ldub	[%o0+1], %g3
	cmp	%g2, 0
	bne	.L1214
	 mov	0, %o0
	jmp	%o7+8
	 and	%o0, 0xff, %o0
.L1215:
	xor	%g3, %o0, %o0
	ldsb	[%g1], %g2
	cmp	%g2, 0
	be	.L1200
	 ldub	[%g1], %g3
.L1214:
	cmp	%g2, 42
	bne,a	.L1215
	 add	%g1, 1, %g1
.L1200:
	and	%o0, 0xff, %o0
	jmp	%o7+8
	 nop
	.size	calc_checksum, .-calc_checksum
	.section	.rodata.cst8
	.align 8
.LC223:
	.long	1073741824
	.long	0
	.align 8
.LC224:
	.long	0
	.long	0
	.align 8
.LC225:
	.long	1102175864
	.long	1241513984
	.align 8
.LC226:
	.long	1134423871
	.long	1614070530
	.section	.text.NavComputeUserVelocitySixSat,"ax",@progbits
	.align 4
	.global NavComputeUserVelocitySixSat
	.type	NavComputeUserVelocitySixSat, #function
	.proc	020
NavComputeUserVelocitySixSat:
	save	%sp, -816, %sp
	sethi	%hi(NavprocData), %i5
	or	%i5, %lo(NavprocData), %i5
	ldd	[%i5+216], %f8
	ldd	[%i5+696], %f10
	fsubd	%f10, %f8, %f0
	sethi	%hi(.LC223), %i4
	std	%f0, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	call	pow, 0
	 ldd	[%fp-704], %o0
	ldd	[%i5+704], %f12
	ldd	[%i5+224], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f2
	fmovs	%f1, %f9
	std	%f2, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%i5+712], %f12
	ldd	[%i5+232], %f10
	ldd	[%fp-696], %f8
	fsubd	%f12, %f10, %f4
	faddd	%f8, %f0, %f8
	std	%f4, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%fp-696], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -512, %o0
	add	%fp, -504, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-512]
	ldd	[%fp-504], %f12
	ldd	[%i5+240], %f8
	ldd	[%i5+696], %f10
	std	%f12, [%fp-496]
	fsubd	%f10, %f8, %f12
	ldd	[%i4+%lo(.LC223)], %o2
	std	%f12, [%fp-704]
	call	pow, 0
	 ldd	[%fp-704], %o0
	ldd	[%i5+704], %f12
	ldd	[%i5+248], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f14
	fmovs	%f1, %f9
	std	%f14, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%i5+712], %f12
	ldd	[%i5+256], %f10
	ldd	[%fp-696], %f8
	fsubd	%f12, %f10, %f16
	faddd	%f8, %f0, %f8
	std	%f16, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%fp-696], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -512, %o0
	add	%fp, -504, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-512]
	ldd	[%i5+264], %f8
	ldd	[%i5+696], %f10
	ldd	[%fp-504], %f12
	fsubd	%f10, %f8, %f18
	ldd	[%i4+%lo(.LC223)], %o2
	std	%f18, [%fp-704]
	std	%f12, [%fp-488]
	call	pow, 0
	 ldd	[%fp-704], %o0
	ldd	[%i5+704], %f12
	ldd	[%i5+272], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f20
	fmovs	%f1, %f9
	std	%f20, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%i5+712], %f12
	ldd	[%i5+280], %f10
	ldd	[%fp-696], %f8
	fsubd	%f12, %f10, %f24
	faddd	%f8, %f0, %f8
	std	%f24, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%fp-696], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -512, %o0
	add	%fp, -504, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-512]
	ldd	[%i5+288], %f8
	ldd	[%i5+696], %f10
	ldd	[%fp-504], %f12
	fsubd	%f10, %f8, %f26
	ldd	[%i4+%lo(.LC223)], %o2
	std	%f26, [%fp-704]
	std	%f12, [%fp-480]
	call	pow, 0
	 ldd	[%fp-704], %o0
	ldd	[%i5+704], %f12
	ldd	[%i5+296], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f30
	fmovs	%f1, %f9
	std	%f30, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%i5+712], %f12
	ldd	[%i5+304], %f10
	ldd	[%fp-696], %f8
	faddd	%f8, %f0, %f8
	fsubd	%f12, %f10, %f0
	ldd	[%i4+%lo(.LC223)], %o2
	std	%f0, [%fp-704]
	std	%f8, [%fp-696]
	call	pow, 0
	 ldd	[%fp-704], %o0
	ldd	[%fp-696], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -512, %o0
	add	%fp, -504, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-512]
	ldd	[%i5+312], %f8
	ldd	[%i5+696], %f10
	ldd	[%fp-504], %f12
	fsubd	%f10, %f8, %f2
	ldd	[%i4+%lo(.LC223)], %o2
	std	%f2, [%fp-704]
	std	%f12, [%fp-472]
	call	pow, 0
	 ldd	[%fp-704], %o0
	ldd	[%i5+704], %f12
	ldd	[%i5+320], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f4
	fmovs	%f1, %f9
	std	%f4, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%i5+712], %f12
	ldd	[%i5+328], %f10
	ldd	[%fp-696], %f8
	fsubd	%f12, %f10, %f14
	faddd	%f8, %f0, %f8
	std	%f14, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%fp-696], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -512, %o0
	add	%fp, -504, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-512]
	ldd	[%i5+336], %f8
	ldd	[%i5+696], %f10
	ldd	[%fp-504], %f12
	fsubd	%f10, %f8, %f16
	ldd	[%i4+%lo(.LC223)], %o2
	std	%f16, [%fp-704]
	std	%f12, [%fp-464]
	call	pow, 0
	 ldd	[%fp-704], %o0
	ldd	[%i5+704], %f12
	ldd	[%i5+344], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f18
	fmovs	%f1, %f9
	std	%f18, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%i5+712], %f12
	ldd	[%i5+352], %f10
	ldd	[%fp-696], %f8
	fsubd	%f12, %f10, %f20
	faddd	%f8, %f0, %f8
	std	%f20, [%fp-704]
	ldd	[%i4+%lo(.LC223)], %o2
	ldd	[%fp-704], %o0
	call	pow, 0
	 std	%f8, [%fp-696]
	ldd	[%fp-696], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -512, %o0
	add	%fp, -504, %o1
	call	sqrt_ajit_asm_double, 0
	 std	%f0, [%fp-512]
	ldd	[%fp-496], %f16
	ldd	[%i5+216], %f12
	ldd	[%i5+224], %f14
	ldd	[%i5+696], %f4
	ldd	[%i5+704], %f10
	ldd	[%i5+712], %f8
	fsubd	%f4, %f12, %f18
	ldd	[%i5+240], %f20
	fdivd	%f18, %f16, %f18
	fsubd	%f10, %f14, %f12
	ldd	[%i5+232], %f14
	fdivd	%f12, %f16, %f12
	fsubd	%f8, %f14, %f2
	fdivd	%f2, %f16, %f26
	ldd	[%i5+248], %f16
	fsubd	%f10, %f16, %f16
	ldd	[%fp-488], %f22
	fsubd	%f4, %f20, %f14
	fdivd	%f16, %f22, %f20
	ldd	[%i5+264], %f16
	fsubd	%f4, %f16, %f16
	ldd	[%fp-480], %f24
	fdivd	%f14, %f22, %f14
	ldd	[%i5+256], %f0
	ldd	[%i5+288], %f28
	fsubd	%f8, %f0, %f0
	fsubd	%f4, %f28, %f28
	fdivd	%f0, %f22, %f30
	fdivd	%f16, %f24, %f22
	ldd	[%i5+280], %f16
	fsubd	%f8, %f16, %f16
	ldd	[%fp-472], %f6
	fdivd	%f16, %f24, %f0
	std	%f26, [%fp-712]
	ldd	[%i5+296], %f16
	ldd	[%i5+272], %f26
	fsubd	%f10, %f16, %f16
	fsubd	%f10, %f26, %f26
	fdivd	%f26, %f24, %f26
	fdivd	%f28, %f6, %f24
	ldd	[%i5+304], %f28
	fsubd	%f8, %f28, %f28
	fdivd	%f28, %f6, %f2
	std	%f30, [%fp-720]
	std	%f2, [%fp-560]
	fdivd	%f16, %f6, %f30
	ldd	[%i5+328], %f2
	ldd	[%i5+312], %f16
	fsubd	%f8, %f2, %f2
	fsubd	%f4, %f16, %f28
	std	%f0, [%fp-552]
	ldd	[%fp-464], %f16
	ldd	[%i5+336], %f0
	fsubd	%f4, %f0, %f0
	fdivd	%f2, %f16, %f4
	ldd	[%fp-504], %f2
	fdivd	%f28, %f16, %f28
	ldd	[%i5+320], %f6
	fsubd	%f10, %f6, %f6
	fdivd	%f6, %f16, %f6
	fdivd	%f0, %f2, %f16
	ldd	[%i5+344], %f2
	ldd	[%i5+352], %f0
	fsubd	%f8, %f0, %f8
	std	%f4, [%fp-536]
	fsubd	%f10, %f2, %f4
	ldd	[%fp-504], %f10
	fmuld	%f14, %f14, %f2
	fdivd	%f8, %f10, %f0
	fmuld	%f22, %f22, %f8
	std	%f0, [%fp-544]
	std	%f2, [%fp-568]
	std	%f8, [%fp-576]
	fmuld	%f28, %f28, %f2
	fmuld	%f16, %f16, %f8
	std	%f2, [%fp-592]
	std	%f8, [%fp-600]
	fmuld	%f20, %f14, %f2
	fmuld	%f26, %f22, %f8
	fdivd	%f4, %f10, %f4
	std	%f2, [%fp-608]
	std	%f8, [%fp-616]
	fmuld	%f28, %f6, %f2
	fmuld	%f4, %f16, %f8
	std	%f2, [%fp-632]
	std	%f8, [%fp-640]
	ldd	[%fp-720], %f2
	ldd	[%fp-552], %f8
	fmuld	%f2, %f14, %f2
	fmuld	%f8, %f22, %f8
	fmuld	%f18, %f18, %f0
	fmuld	%f24, %f24, %f10
	std	%f2, [%fp-656]
	std	%f8, [%fp-664]
	ldd	[%fp-536], %f2
	ldd	[%fp-544], %f8
	fmuld	%f2, %f28, %f2
	fmuld	%f8, %f16, %f8
	std	%f10, [%fp-584]
	std	%f2, [%fp-680]
	fmuld	%f12, %f18, %f10
	std	%f8, [%fp-688]
	std	%f10, [%fp-528]
	sethi	%hi(.LC224), %g1
	ldd	[%g1+%lo(.LC224)], %f8
	faddd	%f0, %f8, %f2
	ldd	[%fp-528], %f0
	faddd	%f0, %f8, %f0
	fmuld	%f30, %f24, %f10
	std	%f0, [%fp-528]
	ldd	[%fp-568], %f0
	faddd	%f2, %f0, %f2
	std	%f10, [%fp-624]
	std	%f2, [%fp-520]
	ldd	[%fp-608], %f0
	ldd	[%fp-528], %f2
	ldd	[%fp-712], %f10
	faddd	%f2, %f0, %f2
	fmuld	%f10, %f18, %f10
	ldd	[%fp-576], %f0
	std	%f10, [%fp-648]
	std	%f2, [%fp-528]
	ldd	[%fp-560], %f10
	ldd	[%fp-520], %f2
	fmuld	%f10, %f24, %f10
	faddd	%f2, %f0, %f2
	std	%f10, [%fp-672]
	sethi	%hi(.LC225), %g1
	ldd	[%g1+%lo(.LC225)], %f10
	std	%f2, [%fp-520]
	ldd	[%fp-528], %f2
	ldd	[%fp-616], %f0
	faddd	%f2, %f0, %f2
	ldd	[%fp-584], %f0
	std	%f2, [%fp-528]
	ldd	[%fp-520], %f2
	faddd	%f2, %f0, %f2
	ldd	[%fp-624], %f0
	std	%f2, [%fp-520]
	ldd	[%fp-528], %f2
	faddd	%f2, %f0, %f2
	ldd	[%fp-592], %f0
	std	%f2, [%fp-528]
	ldd	[%fp-520], %f2
	faddd	%f2, %f0, %f2
	ldd	[%fp-632], %f0
	std	%f2, [%fp-520]
	ldd	[%fp-528], %f2
	faddd	%f2, %f0, %f2
	ldd	[%fp-600], %f0
	std	%f2, [%fp-528]
	ldd	[%fp-520], %f2
	faddd	%f2, %f0, %f2
	ldd	[%fp-640], %f0
	std	%f2, [%fp-448]
	ldd	[%fp-528], %f2
	faddd	%f2, %f0, %f2
	std	%f2, [%fp-416]
	std	%f2, [%fp-440]
	ldd	[%fp-648], %f2
	faddd	%f2, %f8, %f2
	fmuld	%f18, %f10, %f18
	ldd	[%fp-656], %f0
	faddd	%f2, %f0, %f0
	faddd	%f18, %f8, %f2
	std	%f2, [%fp-528]
	ldd	[%fp-664], %f2
	faddd	%f0, %f2, %f18
	ldd	[%fp-672], %f0
	ldd	[%fp-528], %f2
	fmuld	%f28, %f10, %f28
	fmuld	%f16, %f10, %f16
	faddd	%f18, %f0, %f18
	ldd	[%fp-680], %f0
	faddd	%f18, %f0, %f18
	fmuld	%f24, %f10, %f24
	fmuld	%f22, %f10, %f0
	fmuld	%f14, %f10, %f14
	faddd	%f2, %f14, %f14
	ldd	[%fp-688], %f2
	faddd	%f14, %f0, %f14
	faddd	%f18, %f2, %f22
	faddd	%f14, %f24, %f14
	fmuld	%f26, %f26, %f18
	faddd	%f14, %f28, %f14
	faddd	%f14, %f16, %f28
	fmuld	%f20, %f20, %f16
	fmuld	%f12, %f12, %f14
	faddd	%f14, %f8, %f14
	faddd	%f14, %f16, %f14
	fmuld	%f30, %f30, %f16
	faddd	%f14, %f18, %f14
	fmuld	%f6, %f6, %f18
	ldd	[%fp-712], %f24
	std	%f22, [%fp-432]
	std	%f28, [%fp-424]
	faddd	%f14, %f16, %f14
	fmuld	%f4, %f4, %f16
	faddd	%f14, %f18, %f14
	fmuld	%f24, %f12, %f18
	faddd	%f14, %f16, %f0
	faddd	%f18, %f8, %f16
	std	%f0, [%fp-408]
	ldd	[%fp-720], %f2
	ldd	[%fp-552], %f24
	fmuld	%f24, %f26, %f18
	fmuld	%f20, %f2, %f14
	fmuld	%f26, %f10, %f26
	ldd	[%fp-560], %f0
	fmuld	%f20, %f10, %f20
	faddd	%f16, %f14, %f14
	ldd	[%fp-536], %f2
	fmuld	%f0, %f30, %f16
	faddd	%f14, %f18, %f14
	fmuld	%f30, %f10, %f30
	fmuld	%f2, %f6, %f18
	faddd	%f14, %f16, %f14
	faddd	%f14, %f18, %f14
	ldd	[%fp-544], %f16
	fmuld	%f12, %f10, %f12
	fmuld	%f16, %f4, %f24
	faddd	%f12, %f8, %f12
	faddd	%f14, %f24, %f24
	fmuld	%f4, %f10, %f4
	faddd	%f12, %f20, %f12
	ldd	[%fp-712], %f20
	faddd	%f12, %f26, %f12
	fmovs	%f20, %f26
	fmovs	%f21, %f27
	faddd	%f12, %f30, %f12
	ldd	[%fp-720], %f30
	fmovs	%f30, %f0
	fmovs	%f31, %f1
	fmuld	%f30, %f0, %f14
	fmuld	%f20, %f26, %f18
	ldd	[%fp-552], %f2
	ldd	[%fp-560], %f20
	ldd	[%fp-536], %f30
	fmuld	%f6, %f10, %f6
	faddd	%f18, %f8, %f18
	fmovs	%f20, %f26
	fmovs	%f21, %f27
	fmovs	%f30, %f0
	fmovs	%f31, %f1
	faddd	%f12, %f6, %f12
	faddd	%f18, %f14, %f18
	faddd	%f12, %f4, %f12
	fmuld	%f20, %f26, %f14
	fmovs	%f2, %f4
	fmovs	%f3, %f5
	fmuld	%f2, %f4, %f16
	faddd	%f18, %f16, %f18
	faddd	%f18, %f14, %f18
	ldd	[%fp-544], %f2
	fmuld	%f30, %f0, %f16
	ldd	[%fp-720], %f20
	faddd	%f18, %f16, %f16
	fmuld	%f20, %f10, %f0
	ldd	[%fp-712], %f18
	fmovs	%f2, %f4
	fmovs	%f3, %f5
	ldd	[%fp-552], %f26
	fmuld	%f2, %f4, %f14
	ldd	[%fp-560], %f30
	fmuld	%f18, %f10, %f2
	faddd	%f16, %f14, %f14
	faddd	%f2, %f8, %f2
	fmuld	%f26, %f10, %f16
	faddd	%f2, %f0, %f2
	fmuld	%f30, %f10, %f18
	faddd	%f2, %f16, %f16
	ldd	[%fp-536], %f0
	faddd	%f16, %f18, %f16
	fmuld	%f0, %f10, %f20
	fmuld	%f4, %f10, %f10
	faddd	%f16, %f20, %f16
	faddd	%f16, %f10, %f10
	sethi	%hi(.LC226), %g1
	std	%f10, [%fp-360]
	std	%f10, [%fp-336]
	ldd	[%g1+%lo(.LC226)], %f10
	std	%f8, [%fp-696]
	std	%f24, [%fp-400]
	std	%f12, [%fp-392]
	std	%f22, [%fp-384]
	std	%f24, [%fp-376]
	std	%f14, [%fp-368]
	std	%f28, [%fp-352]
	std	%f12, [%fp-344]
	add	%fp, -448, %o0
	call	FindDeterminant.constprop.5, 0
	 std	%f10, [%fp-328]
	ldd	[%fp-696], %f8
	fcmpd	%f0, %f8
	nop
	fbne,a	.L1218
	 add	%fp, -448, %o0
	sethi	%hi(.LC51), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC51), %o0
	jmp	%i7+8
	 restore
.L1218:
	call	FindCoFactor.constprop.3, 0
	 add	%fp, -320, %o1
	jmp	%i7+8
	 restore
	.size	NavComputeUserVelocitySixSat, .-NavComputeUserVelocitySixSat
	.section	.rodata.str1.8
	.align 8
.LC227:
	.asciz	"\n J= %d"
	.section	.rodata.cst8
	.align 8
.LC228:
	.long	1073741824
	.long	0
	.align 8
.LC229:
	.long	0
	.long	0
	.section	.text.NavComputeUserVelocityFourSat,"ax",@progbits
	.align 4
	.global NavComputeUserVelocityFourSat
	.type	NavComputeUserVelocityFourSat, #function
	.proc	020
NavComputeUserVelocityFourSat:
	save	%sp, -512, %sp
	sethi	%hi(.LC227), %i3
	sethi	%hi(NavprocData), %i5
	or	%i3, %lo(.LC227), %o0
	or	%i5, %lo(NavprocData), %i5
	ld	[%i5+188], %i2
	call	ee_printf, 0
	 mov	%i2, %o1
	add	%i2, %i2, %g1
	ldd	[%i5+696], %f10
	add	%g1, %i2, %i2
	sll	%i2, 3, %i2
	add	%i5, %i2, %i2
	ldd	[%i2+216], %f8
	fsubd	%f10, %f8, %f12
	sethi	%hi(.LC228), %i4
	std	%f12, [%fp-416]
	ldd	[%i4+%lo(.LC228)], %o2
	call	pow, 0
	 ldd	[%fp-416], %o0
	ldd	[%i5+704], %f12
	ldd	[%i2+224], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f14
	fmovs	%f1, %f9
	std	%f14, [%fp-416]
	ldd	[%i4+%lo(.LC228)], %o2
	ldd	[%fp-416], %o0
	call	pow, 0
	 std	%f8, [%fp-408]
	ldd	[%i5+712], %f10
	ldd	[%i2+232], %f12
	ldd	[%fp-408], %f8
	fsubd	%f10, %f12, %f14
	faddd	%f8, %f0, %f8
	std	%f14, [%fp-416]
	ldd	[%i4+%lo(.LC228)], %o2
	ldd	[%fp-416], %o0
	call	pow, 0
	 std	%f8, [%fp-408]
	ldd	[%fp-408], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -400, %o0
	std	%f0, [%fp-400]
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -392, %o1
	or	%i3, %lo(.LC227), %o0
	ld	[%i5+192], %i2
	call	ee_printf, 0
	 mov	%i2, %o1
	add	%i2, %i2, %g1
	ldd	[%i5+696], %f10
	add	%g1, %i2, %i2
	sll	%i2, 3, %i2
	add	%i5, %i2, %i2
	ldd	[%i2+216], %f8
	fsubd	%f10, %f8, %f12
	ldd	[%i4+%lo(.LC228)], %o2
	std	%f12, [%fp-416]
	call	pow, 0
	 ldd	[%fp-416], %o0
	ldd	[%i5+704], %f12
	ldd	[%i2+224], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f14
	fmovs	%f1, %f9
	std	%f14, [%fp-416]
	ldd	[%i4+%lo(.LC228)], %o2
	ldd	[%fp-416], %o0
	call	pow, 0
	 std	%f8, [%fp-408]
	ldd	[%i5+712], %f10
	ldd	[%i2+232], %f12
	ldd	[%fp-408], %f8
	fsubd	%f10, %f12, %f14
	faddd	%f8, %f0, %f8
	std	%f14, [%fp-416]
	ldd	[%i4+%lo(.LC228)], %o2
	ldd	[%fp-416], %o0
	call	pow, 0
	 std	%f8, [%fp-408]
	ldd	[%fp-408], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -400, %o0
	std	%f0, [%fp-400]
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -392, %o1
	or	%i3, %lo(.LC227), %o0
	ld	[%i5+196], %i2
	call	ee_printf, 0
	 mov	%i2, %o1
	add	%i2, %i2, %g1
	ldd	[%i5+696], %f10
	add	%g1, %i2, %i2
	sll	%i2, 3, %i2
	add	%i5, %i2, %i2
	ldd	[%i2+216], %f8
	fsubd	%f10, %f8, %f12
	ldd	[%i4+%lo(.LC228)], %o2
	std	%f12, [%fp-416]
	call	pow, 0
	 ldd	[%fp-416], %o0
	ldd	[%i5+704], %f12
	ldd	[%i2+224], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f14
	fmovs	%f1, %f9
	std	%f14, [%fp-416]
	ldd	[%i4+%lo(.LC228)], %o2
	ldd	[%fp-416], %o0
	call	pow, 0
	 std	%f8, [%fp-408]
	ldd	[%i5+712], %f10
	ldd	[%i2+232], %f12
	ldd	[%fp-408], %f8
	fsubd	%f10, %f12, %f14
	faddd	%f8, %f0, %f8
	std	%f14, [%fp-416]
	ldd	[%i4+%lo(.LC228)], %o2
	ldd	[%fp-416], %o0
	call	pow, 0
	 std	%f8, [%fp-408]
	ldd	[%fp-408], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -400, %o0
	std	%f0, [%fp-400]
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -392, %o1
	or	%i3, %lo(.LC227), %o0
	ld	[%i5+200], %i3
	call	ee_printf, 0
	 mov	%i3, %o1
	add	%i3, %i3, %g1
	ldd	[%i5+696], %f10
	add	%g1, %i3, %i3
	sll	%i3, 3, %i3
	add	%i5, %i3, %i3
	ldd	[%i3+216], %f8
	fsubd	%f10, %f8, %f12
	ldd	[%i4+%lo(.LC228)], %o2
	std	%f12, [%fp-416]
	call	pow, 0
	 ldd	[%fp-416], %o0
	ldd	[%i5+704], %f12
	ldd	[%i3+224], %f10
	fmovs	%f0, %f8
	fsubd	%f12, %f10, %f14
	fmovs	%f1, %f9
	std	%f14, [%fp-416]
	ldd	[%i4+%lo(.LC228)], %o2
	ldd	[%fp-416], %o0
	call	pow, 0
	 std	%f8, [%fp-408]
	ldd	[%i5+712], %f12
	ldd	[%i3+232], %f10
	ldd	[%fp-408], %f8
	fsubd	%f12, %f10, %f14
	faddd	%f8, %f0, %f8
	std	%f14, [%fp-416]
	ldd	[%i4+%lo(.LC228)], %o2
	ldd	[%fp-416], %o0
	call	pow, 0
	 std	%f8, [%fp-408]
	ldd	[%fp-408], %f8
	faddd	%f8, %f0, %f0
	add	%fp, -392, %o1
	std	%f0, [%fp-400]
	call	sqrt_ajit_asm_double, 0
	 add	%fp, -400, %o0
	sethi	%hi(.LC42), %i5
	call	ee_printf, 0
	 or	%i5, %lo(.LC42), %o0
	call	FindDeterminant.constprop.5, 0
	 add	%fp, -384, %o0
	sethi	%hi(.LC229), %g1
	ldd	[%g1+%lo(.LC229)], %f8
	fcmpd	%f0, %f8
	nop
	fbne,a	.L1221
	 add	%fp, -384, %o0
	sethi	%hi(.LC51), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC51), %o0
	call	ee_printf, 0
	 or	%i5, %lo(.LC42), %o0
	jmp	%i7+8
	 restore
.L1221:
	call	FindCoFactor.constprop.3, 0
	 add	%fp, -256, %o1
	call	ee_printf, 0
	 or	%i5, %lo(.LC42), %o0
	jmp	%i7+8
	 restore
	.size	NavComputeUserVelocityFourSat, .-NavComputeUserVelocityFourSat
	.section	.rodata.cst8
	.align 8
.LC230:
	.long	-1065402368
	.long	0
	.section	.text.ProcessNavIC_PVTData_Main,"ax",@progbits
	.align 4
	.global ProcessNavIC_PVTData_Main
	.type	ProcessNavIC_PVTData_Main, #function
	.proc	020
ProcessNavIC_PVTData_Main:
	save	%sp, -104, %sp
	sethi	%hi(NavprocData), %i5
	mov	%i0, %o0
	call	Verify_NavIC_PVT_Data, 0
	 or	%i5, %lo(NavprocData), %i5
	cmp	%o0, 0
	ble	.L1225
	 st	%o0, [%i5+184]
	sethi	%hi(Raw_PR_Delay), %g1
	or	%g1, %lo(Raw_PR_Delay), %g1
	add	%i0, %i0, %g2
	sethi	%hi(NavObsDat), %i4
	add	%g2, %i0, %g2
	sll	%o0, 3, %o0
	sll	%g2, 4, %g2
	or	%i4, %lo(NavObsDat), %i4
	add	%g2, %g1, %g2
	mov	0, %g1
	ldd	[%g2+%g1], %f8
.L1271:
	std	%f8, [%i4+%g1]
	add	%g1, 8, %g1
	cmp	%g1, %o0
	bne,a	.L1271
	 ldd	[%g2+%g1], %f8
	sethi	%hi(NavprocData+188), %i3
	mov	0, %i0
	or	%i3, %lo(NavprocData+188), %i3
	mov	%i3, %i2
.L1227:
	ld	[%i2], %o0
	sll	%o0, 3, %g1
	mov	%i1, %o1
	call	NavIC_TOWC_Correction, 0
	 ldd	[%i4+%g1], %o2
	add	%i0, 1, %i0
	ld	[%i5+184], %g1
	cmp	%g1, %i0
	bg	.L1227
	 add	%i2, 4, %i2
	cmp	%g1, 0
	ble	.L1225
	 mov	0, %i2
.L1253:
	ld	[%i3], %o0
	sll	%o0, 3, %g1
	mov	%i1, %o1
	call	NavIC_Cor1_ObsPRange, 0
	 ldd	[%i4+%g1], %o2
	add	%i2, 1, %i2
	ld	[%i5+184], %g1
	cmp	%g1, %i2
	bg	.L1253
	 add	%i3, 4, %i3
.L1225:
	call	NavFindUTCTime, 0
	 mov	%i1, %o0
	ld	[%i5+184], %g1
	cmp	%g1, 3
	ble	.L1274
	 add	%i5, 188, %i2
	sethi	%hi(NavObsDat), %i4
	mov	%i2, %i0
	mov	0, %i3
	or	%i4, %lo(NavObsDat), %i4
.L1231:
	ld	[%i0], %o1
	sll	%o1, 3, %g1
	add	%i4, %g1, %g2
	mov	%i3, %o0
	mov	%i1, %o2
	ld	[%g2], %o3
	call	NavComputeSatPos, 0
	 ld	[%g2+4], %o4
	add	%i3, 1, %i3
	ld	[%i5+184], %g1
	cmp	%g1, %i3
	bg	.L1231
	 add	%i0, 4, %i0
	cmp	%g1, 5
	bg	.L1264
	 cmp	%g1, 3
	bg	.L1265
	 nop
	mov	%i2, %i3
.L1269:
	cmp	%g1, 0
	ble	.L1244
	 mov	0, %i4
.L1252:
	call	NavComputeSatAzEl, 0
	 ld	[%i3], %o0
	add	%i4, 1, %i4
	ld	[%i5+184], %g1
	cmp	%g1, %i4
	bg	.L1252
	 add	%i3, 4, %i3
	cmp	%g1, 0
	ble	.L1272
	 cmp	%g1, 3
	add	%i5, 8, %i0
	mov	%i2, %i3
	mov	0, %i4
.L1236:
	ldd	[%i0], %f8
	fdtoi	%f8, %f10
	ld	[%i3], %o0
	st	%f10, [%fp-4]
	call	NavComputeIonosphericDelay, 0
	 ld	[%fp-4], %o1
	add	%i4, 1, %i4
	ld	[%i5+184], %g1
	add	%i3, 4, %i3
	cmp	%g1, %i4
	bg	.L1236
	 add	%i0, 8, %i0
	cmp	%g1, 0
	ble	.L1272
	 cmp	%g1, 3
	mov	%i2, %i3
	mov	0, %i4
.L1238:
	call	NavComputeTroposphericDelay, 0
	 ld	[%i3], %o0
	add	%i4, 1, %i4
	ld	[%i5+184], %g1
	cmp	%g1, %i4
	bg	.L1238
	 add	%i3, 4, %i3
	cmp	%g1, 0
	ble	.L1244
	 sethi	%hi(.LC230), %g2
	sll	%g1, 2, %g1
	mov	%i5, %g3
	or	%g2, %lo(.LC230), %g2
	add	%i5, %g1, %g1
	ldd	[%g2], %f14
	fmovs	%f14, %f12
	fmovs	%f15, %f13
.L1242:
	ld	[%g3+188], %g2
	add	%g2, 7, %g4
	add	%g2, 13, %i3
	add	%g2, 75, %i4
	sll	%i3, 3, %i3
	sll	%i4, 3, %i4
	sll	%g4, 3, %g4
	ldd	[%i5+%i4], %f10
	fcmpd	%f10, %f14
	nop
	fbe	.L1240
	 ldd	[%i5+%i3], %f8
	faddd	%f8, %f10, %f8
.L1240:
	add	%g2, 81, %g2
	sll	%g2, 3, %g2
	ldd	[%i5+%g2], %f10
	fcmpd	%f10, %f12
	nop
	fbne,a	.L1241
	 faddd	%f8, %f10, %f8
.L1241:
	add	%g3, 4, %g3
	cmp	%g3, %g1
	bne	.L1242
	 std	%f8, [%i5+%g4]
	mov	0, %i4
.L1243:
	ld	[%i2], %o1
	call	NavComputeSatVelocity, 0
	 mov	%i1, %o0
	add	%i4, 1, %i4
	ld	[%i5+184], %g1
	cmp	%g1, %i4
	bg	.L1243
	 add	%i2, 4, %i2
	cmp	%g1, 5
	bg	.L1266
	 nop
.L1244:
	cmp	%g1, 3
.L1272:
	bg	.L1267
	 nop
	mov	0, %i4
.L1270:
	cmp	%g1, 0
	ble	.L1273
	 nop
.L1251:
	call	NavIC_Compute_Sat_Rx_Range, 0
	 mov	%i4, %o0
	add	%i4, 1, %i4
	ld	[%i5+184], %g1
	cmp	%g1, %i4
	bg	.L1251
	 nop
.L1274:
	jmp	%i7+8
	 restore
.L1264:
	call	NavComputeUserPosSixSat, 0
	 mov	%i2, %i3
	b	.L1269
	 ld	[%i5+184], %g1
.L1266:
	call	NavComputeUserVelocitySixSat, 0
	 mov	0, %i4
	b	.L1270
	 ld	[%i5+184], %g1
.L1265:
	call	NavComputeUserPosFourSat, 0
	 mov	%i2, %i3
	b	.L1269
	 ld	[%i5+184], %g1
.L1267:
	call	NavComputeUserVelocityFourSat, 0
	 mov	0, %i4
	b	.L1270
	 ld	[%i5+184], %g1
.L1273:
	jmp	%i7+8
	 restore
	.size	ProcessNavIC_PVTData_Main, .-ProcessNavIC_PVTData_Main
	.section	.rodata.str1.8
	.align 8
.LC231:
	.asciz	"================Satellite Position====================\n"
	.align 8
.LC232:
	.asciz	"\n\n================User Position====================\n"
	.align 8
.LC233:
	.asciz	"\nUserpos[%d]=%0.10f\n"
	.align 8
.LC234:
	.asciz	"\n\nUserPosition_Lat= %0.10f\n"
	.align 8
.LC235:
	.asciz	"\nUserPosition_Long= %0.10f\n"
	.align 8
.LC236:
	.asciz	"\nUserPosition_Ht= %0.10f\n"
	.align 8
.LC237:
	.asciz	"\n\n================SatAzEl Cooridinates====================\n\n"
	.align 8
.LC238:
	.asciz	"\nSatPos[%d][%d]=%0.10f\n"
	.align 8
.LC239:
	.asciz	"\n"
	.align 8
.LC240:
	.asciz	"\n\n================Satellite Velocity====================\n"
	.align 8
.LC241:
	.asciz	"SatPosAz[%d][0]=%0.10f\t\n"
	.align 8
.LC242:
	.asciz	"SatPosEl[%d][1]=%0.10f\n"
	.align 8
.LC243:
	.asciz	"\n\n======================DOP================================\n"
	.align 8
.LC244:
	.asciz	"\nGDOP=%0.10f\n"
	.align 8
.LC245:
	.asciz	"\tPDOP=%0.10f\n"
	.align 8
.LC246:
	.asciz	"\tHDOP=%0.10f\n"
	.align 8
.LC247:
	.asciz	"\tVDOP=%0.10f\n"
	.align 8
.LC248:
	.asciz	"\tTDOP=%0.10f\n"
	.align 8
.LC249:
	.asciz	"\n\n======================Ionospheric Delay================================\n"
	.align 8
.LC250:
	.asciz	"\nSatIonosphericCorr=%0.10f\n"
	.align 8
.LC251:
	.asciz	"\n\n======================FINDUTC================================\n"
	.align 8
.LC252:
	.asciz	"\nCurDay = %0.10f\tCurMonth = %0.10f\tUTC_Yr = %0.10f\n"
	.align 8
.LC253:
	.asciz	"\nUTC_Hrs = %0.10f\tUTC_Mins = %0.10f\tUTC_Sec = %0.10f\tremday = %0.10f\n"
	.align 8
.LC254:
	.asciz	"SatVel[%d][%d]=%0.10f\t\n"
	.section	.text.Print_Process_Data,"ax",@progbits
	.align 4
	.global Print_Process_Data
	.type	Print_Process_Data, #function
	.proc	020
Print_Process_Data:
	save	%sp, -112, %sp
	sethi	%hi(.LC231), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC231), %o0
	sethi	%hi(NavprocData), %i5
	or	%i5, %lo(NavprocData), %i5
	ld	[%i5+184], %g1
	cmp	%g1, 0
	ble	.L1280
	 mov	0, %i4
	sethi	%hi(.LC239), %i0
	sethi	%hi(.LC238), %i2
	add	%i5, 188, %i1
	or	%i2, %lo(.LC238), %i2
	or	%i0, %lo(.LC239), %i0
.L1279:
	ld	[%i1], %g1
	mov	%i4, %o1
	add	%g1, %g1, %i3
	mov	0, %o2
	add	%i3, %g1, %i3
	mov	%i2, %o0
	sll	%i3, 3, %i3
	add	%i5, %i3, %i3
	ld	[%i3+216], %o3
	call	ee_printf, 0
	 ld	[%i3+220], %o4
	mov	%i4, %o1
	mov	1, %o2
	ld	[%i3+224], %o3
	ld	[%i3+228], %o4
	call	ee_printf, 0
	 mov	%i2, %o0
	mov	%i4, %o1
	mov	2, %o2
	ld	[%i3+232], %o3
	ld	[%i3+236], %o4
	call	ee_printf, 0
	 mov	%i2, %o0
	call	ee_printf, 0
	 mov	%i0, %o0
	add	%i4, 1, %i4
	ld	[%i5+184], %g1
	cmp	%g1, %i4
	bg	.L1279
	 add	%i1, 4, %i1
.L1280:
	sethi	%hi(.LC232), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC232), %o0
	sethi	%hi(.LC233), %i4
	mov	0, %o1
	ldd	[%i5+696], %o2
	call	ee_printf, 0
	 or	%i4, %lo(.LC233), %o0
	mov	1, %o1
	ldd	[%i5+704], %o2
	call	ee_printf, 0
	 or	%i4, %lo(.LC233), %o0
	ldd	[%i5+712], %o2
	mov	2, %o1
	call	ee_printf, 0
	 or	%i4, %lo(.LC233), %o0
	ld	[%i5+728], %o1
	ld	[%i5+732], %o2
	sethi	%hi(.LC234), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC234), %o0
	ld	[%i5+720], %o1
	ld	[%i5+724], %o2
	sethi	%hi(.LC235), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC235), %o0
	ld	[%i5+736], %o1
	ld	[%i5+740], %o2
	sethi	%hi(.LC236), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC236), %o0
	sethi	%hi(.LC237), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC237), %o0
	ld	[%i5+184], %g1
	cmp	%g1, 0
	ble	.L1289
	 sethi	%hi(.LC240), %o0
	sethi	%hi(.LC241), %i0
	sethi	%hi(.LC242), %i1
	add	%i5, 188, %i3
	mov	0, %i4
	or	%i0, %lo(.LC241), %i0
	or	%i1, %lo(.LC242), %i1
.L1283:
	ld	[%i3], %i2
	sll	%i2, 4, %g1
	add	%i5, %g1, %g1
	mov	%i4, %o1
	ldd	[%g1+360], %o2
	call	ee_printf, 0
	 mov	%i0, %o0
	mov	%i4, %o1
	add	%i2, 23, %i2
	mov	%i1, %o0
	sll	%i2, 4, %i2
	call	ee_printf, 0
	 ldd	[%i5+%i2], %o2
	add	%i4, 1, %i4
	ld	[%i5+184], %g1
	cmp	%g1, %i4
	bg	.L1283
	 add	%i3, 4, %i3
	sethi	%hi(.LC240), %o0
.L1289:
	call	ee_printf, 0
	 or	%o0, %lo(.LC240), %o0
	ld	[%i5+184], %g1
	cmp	%g1, 0
	ble,a	.L1290
	 sethi	%hi(.LC243), %o0
	sethi	%hi(.LC239), %i0
	sethi	%hi(.LC254), %i2
	add	%i5, 188, %i1
	mov	0, %i4
	or	%i2, %lo(.LC254), %i2
	or	%i0, %lo(.LC239), %i0
.L1284:
	ld	[%i1], %g1
	mov	%i4, %o1
	add	%g1, %g1, %i3
	mov	0, %o2
	add	%i3, %g1, %i3
	mov	%i2, %o0
	sll	%i3, 3, %i3
	add	%i5, %i3, %i3
	ld	[%i3+456], %o3
	call	ee_printf, 0
	 ld	[%i3+460], %o4
	mov	%i4, %o1
	mov	1, %o2
	ld	[%i3+464], %o3
	ld	[%i3+468], %o4
	call	ee_printf, 0
	 mov	%i2, %o0
	mov	%i4, %o1
	mov	2, %o2
	ld	[%i3+472], %o3
	ld	[%i3+476], %o4
	call	ee_printf, 0
	 mov	%i2, %o0
	call	ee_printf, 0
	 mov	%i0, %o0
	add	%i4, 1, %i4
	ld	[%i5+184], %g1
	cmp	%g1, %i4
	bg	.L1284
	 add	%i1, 4, %i1
	sethi	%hi(.LC243), %o0
.L1290:
	call	ee_printf, 0
	 or	%o0, %lo(.LC243), %o0
	ld	[%i5+752], %o1
	ld	[%i5+756], %o2
	sethi	%hi(.LC244), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC244), %o0
	ld	[%i5+760], %o1
	ld	[%i5+764], %o2
	sethi	%hi(.LC245), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC245), %o0
	ld	[%i5+768], %o1
	ld	[%i5+772], %o2
	sethi	%hi(.LC246), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC246), %o0
	ld	[%i5+776], %o1
	ld	[%i5+780], %o2
	sethi	%hi(.LC247), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC247), %o0
	ld	[%i5+784], %o1
	ld	[%i5+788], %o2
	sethi	%hi(.LC248), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC248), %o0
	sethi	%hi(.LC249), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC249), %o0
	ld	[%i5+184], %g1
	add	%g1, 75, %g1
	sll	%g1, 3, %g1
	add	%i5, %g1, %g2
	sethi	%hi(.LC250), %o0
	ld	[%g2], %o1
	ld	[%g2+4], %o2
	call	ee_printf, 0
	 or	%o0, %lo(.LC250), %o0
	sethi	%hi(.LC251), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC251), %o0
	ld	[%i5+988], %g1
	ld	[%i5+984], %o5
	ld	[%i5+960], %o1
	ld	[%i5+964], %o2
	ld	[%i5+976], %o3
	ld	[%i5+980], %o4
	sethi	%hi(.LC252), %o0
	st	%g1, [%sp+92]
	call	ee_printf, 0
	 or	%o0, %lo(.LC252), %o0
	ld	[%i5+968], %g3
	ld	[%i5+972], %g2
	ld	[%i5+1012], %g1
	ld	[%i5+1008], %o5
	sethi	%hi(.LC253), %o0
	st	%g3, [%sp+96]
	st	%g2, [%sp+100]
	st	%g1, [%sp+92]
	or	%o0, %lo(.LC253), %o0
	ld	[%i5+992], %o1
	ld	[%i5+996], %o2
	ld	[%i5+1000], %o3
	call	ee_printf, 0
	 ld	[%i5+1004], %o4
	jmp	%i7+8
	 restore
	.size	Print_Process_Data, .-Print_Process_Data
	.section	.rodata.str1.8
	.align 8
.LC255:
	.asciz	"t0=%d, %d\n"
	.align 8
.LC256:
	.asciz	"t1=%d, %d\n"
	.align 8
.LC257:
	.asciz	"t2=%d, %d\n"
	.align 8
.LC258:
	.asciz	"t3=%d, %d\n"
	.align 8
.LC259:
	.asciz	"t4=%d, %d\n"
	.section	.text.startup.main,"ax",@progbits
	.align 4
	.global main
	.type	main, #function
	.proc	020
main:
	save	%sp, -96, %sp
	call	__enable_serial, 0
	 sethi	%hi(.LC259), %i0
	call	__ajit_get_clock_time, 0
	 or	%i0, %lo(.LC259), %i0
	mov	%o1, %o2
	mov	%o0, %o1
	mov	%o2, %o4
	mov	%o1, %o3
	sethi	%hi(.LC255), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC255), %o0
	call	NavIC_Init_Processed_Data, 0
	 nop
	call	__ajit_get_clock_time, 0
	 nop
	mov	%o1, %o2
	mov	%o0, %o1
	mov	%o2, %o4
	mov	%o1, %o3
	sethi	%hi(.LC256), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC256), %o0
	call	ReadandExtractData, 0
	 nop
	call	__ajit_get_clock_time, 0
	 mov	%o0, %i5
	mov	%o1, %o2
	mov	%o0, %o1
	mov	%o2, %o4
	mov	%o1, %o3
	sethi	%hi(.LC257), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC257), %o0
	mov	0, %o0
	call	ProcessNavIC_PVTData_Main, 0
	 mov	%i5, %o1
	call	__ajit_get_clock_time, 0
	 nop
	mov	%o1, %o2
	mov	%o0, %o1
	mov	%o2, %o4
	mov	%o1, %o3
	sethi	%hi(.LC258), %o0
	call	ee_printf, 0
	 or	%o0, %lo(.LC258), %o0
	call	Print_Process_Data, 0
	 nop
	call	__ajit_get_clock_time, 0
	 nop
	mov	%o0, %i1
	mov	%o1, %i2
	mov	%i1, %i3
	call	ee_printf, 0
	 restore %g0, %o1, %o4
	.size	main, .-main
	.global Raw_PR_Delay
	.section	".data"
	.align 8
	.type	Raw_PR_Delay, #object
	.size	Raw_PR_Delay, 384
Raw_PR_Delay:
	.long	1100783921
	.long	1409286144
	.long	1100797011
	.long	67108864
	.long	1100871585
	.long	1207959552
	.long	1100820485
	.long	3221225472
	.long	1100880892
	.long	2415919104
	.long	1100918483
	.long	4093640704
	.long	1100783951
	.long	1006632960
	.long	1100797009
	.long	1409286144
	.long	1100871641
	.long	3221225472
	.long	1100820502
	.long	3623878656
	.long	1100880895
	.long	3288334336
	.long	1100918484
	.long	2147483648
	.long	1100783981
	.long	1811939328
	.long	1100797007
	.long	3623878656
	.long	1100871698
	.long	1946157056
	.long	1100820520
	.long	738197504
	.long	1100880899
	.long	536870912
	.long	1100918485
	.long	1140850688
	.long	1100784011
	.long	2080374784
	.long	1100797006
	.long	671088640
	.long	1100871754
	.long	4160749568
	.long	1100820537
	.long	1409286144
	.long	1100880902
	.long	1409286144
	.long	1100918485
	.long	3422552064
	.long	1100784041
	.long	3355443200
	.long	1100797004
	.long	2617245696
	.long	1100871811
	.long	2751463424
	.long	1100820554
	.long	2952790016
	.long	1100880905
	.long	2818572288
	.long	1100918486
	.long	2080374784
	.long	1100784072
	.long	67108864
	.long	1100797002
	.long	3959422976
	.long	1100871868
	.long	872415232
	.long	1100820571
	.long	4160749568
	.long	1100880908
	.long	3758096384
	.long	1100918487
	.long	201326592
	.long	1100784102
	.long	2415919104
	.long	1100797001
	.long	2013265920
	.long	1100871924
	.long	4227858432
	.long	1100820589
	.long	2147483648
	.long	1100880912
	.long	1342177280
	.long	1100918487
	.long	3422552064
	.long	1100784132
	.long	3758096384
	.long	1100796999
	.long	2885681152
	.long	1100871981
	.long	2080374784
	.long	1100820606
	.long	3288334336
	.long	1100880915
	.long	1946157056
	.long	1100918488
	.long	1073741824
	.common	ztemp,4,4
	.common	zftemp,8,8
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
