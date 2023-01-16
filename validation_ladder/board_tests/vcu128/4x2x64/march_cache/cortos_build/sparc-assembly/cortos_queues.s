	.file	"cortos_queues.c"
	.section	".text"
	.align 4
	.global cortos_reserveQueue
	.type	cortos_reserveQueue, #function
	.proc	0110
cortos_reserveQueue:
	save	%sp, -96, %sp
	smul	%i1, %i0, %o0
	cmp	%i2, 0
	be	.L2
	 add	%o0, 48, %o0
	call	cortos_bget_ncram, 0
	 nop
	mov	%o0, %i4
.L3:
	cmp	%i4, 0
	be	.L5
	 mov	16, %g2
	and	%i4, 15, %g1
	sub	%g2, %g1, %g1
	mov	1, %o0
	add	%i4, %g1, %i5
	st	%g0, [%i4+%g1]
	st	%g0, [%i5+4]
	st	%g0, [%i5+8]
	st	%i0, [%i5+16]
	call	cortos_reserveLock, 0
	 st	%i1, [%i5+12]
	st	%i4, [%i5+24]
	st	%o0, [%i5+20]
	st	%g0, [%i5+28]
.L4:
	jmp	%i7+8
	 restore %g0, %i5, %o0
.L2:
	call	cortos_bget, 0
	 nop
	b	.L3
	 mov	%o0, %i4
.L5:
	b	.L4
	 mov	0, %i5
	.size	cortos_reserveQueue, .-cortos_reserveQueue
	.align 4
	.global cortos_freeQueue
	.type	cortos_freeQueue, #function
	.proc	020
cortos_freeQueue:
	save	%sp, -96, %sp
	call	cortos_freeLock, 0
	 ld	[%i0+20], %o0
	call	cortos_IsNcRamAddr, 0
	 mov	%i0, %o0
	andcc	%o0, 0xff, %g0
	bne	.L9
	 ld	[%i0+24], %i0
	call	cortos_brel, 0
	 restore
.L9:
	call	cortos_brel_ncram, 0
	 restore
	.size	cortos_freeQueue, .-cortos_freeQueue
	.align 4
	.global cortos_writeMessages
	.type	cortos_writeMessages, #function
	.proc	016
cortos_writeMessages:
	save	%sp, -96, %sp
	ld	[%i0+28], %g1
	andcc	%g1, 1, %g0
	be	.L29
	 nop
	ld	[%i0], %g1
	cmp	%g1, 0
	bne	.L20
	 mov	0, %i5
.L12:
	ld	[%i0+8], %i4
	ld	[%i0+12], %o7
	ld	[%i0+16], %g3
	cmp	%i2, 0
	be	.L14
	 add	%i0, 32, %o5
	cmp	%o7, %i5
	bleu	.L21
	 mov	%i2, %i3
.L18:
	smul	%i4, %g3, %g4
	mov	0, %g1
	cmp	%g3, 0
	be	.L17
	 add	%o5, %g4, %g4
	ldub	[%i1+%g1], %g2
.L31:
	stb	%g2, [%g4+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %g3
	bne,a	.L31
	 ldub	[%i1+%g1], %g2
.L17:
	add	%i4, 1, %i4
	add	%i5, 1, %i5
	wr	%g0, 0, %y
	nop
	nop
	nop
	udiv	%i4, %o7, %g1
	addcc	%i3, -1, %i3
	smul	%g1, %o7, %g1
	be	.L14
	 sub	%i4, %g1, %i4
	ld	[%i0+12], %g1
	cmp	%g1, %i5
	bgu	.L18
	 add	%i1, %g3, %i1
	sub	%i2, %i3, %i2
.L14:
	st	%i4, [%i0+8]
	st	%i5, [%i0]
	ld	[%i0+28], %g1
	andcc	%g1, 1, %g0
	be,a	.L30
	 ld	[%i0+20], %o0
	jmp	%i7+8
	 restore %g0, %i2, %o0
.L20:
	mov	0, %i2
	jmp	%i7+8
	 restore %g0, %i2, %o0
.L29:
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i0+20], %o0
	b	.L12
	 ld	[%i0], %i5
.L30:
	call	cortos_lock_release, 0
	 mov	%i2, %i0
	jmp	%i7+8
	 restore
.L21:
	b	.L14
	 mov	0, %i2
	.size	cortos_writeMessages, .-cortos_writeMessages
	.align 4
	.global cortos_readMessages
	.type	cortos_readMessages, #function
	.proc	016
cortos_readMessages:
	save	%sp, -96, %sp
	ld	[%i0+28], %g1
	andcc	%g1, 1, %g0
	be	.L59
	 nop
	ld	[%i0], %i5
	cmp	%i5, 0
	be	.L35
	 mov	0, %i3
.L34:
	ld	[%i0+4], %i4
	ld	[%i0+12], %o7
	ld	[%i0+16], %g3
	cmp	%i5, 0
	be	.L44
	 add	%i0, 32, %o5
	cmp	%i2, 0
	be	.L36
	 mov	0, %i3
	mov	%i2, %i3
	smul	%i4, %g3, %g4
.L62:
	mov	0, %g1
	cmp	%g3, 0
	be	.L41
	 add	%o5, %g4, %g4
	ldub	[%g4+%g1], %g2
.L61:
	stb	%g2, [%i1+%g1]
	add	%g1, 1, %g1
	cmp	%g1, %g3
	bne,a	.L61
	 ldub	[%g4+%g1], %g2
.L41:
	add	%i4, 1, %i4
	add	%i3, -1, %i3
	wr	%g0, 0, %y
	nop
	nop
	nop
	udiv	%i4, %o7, %g1
	add	%i1, %g3, %i1
	smul	%g1, %o7, %g1
	addcc	%i5, -1, %i5
	be	.L40
	 sub	%i4, %g1, %i4
	cmp	%i3, 0
	bne,a	.L62
	 smul	%i4, %g3, %g4
.L40:
	sub	%i2, %i3, %i3
.L36:
	st	%i4, [%i0+4]
	st	%i5, [%i0]
	ld	[%i0+28], %g1
	andcc	%g1, 1, %g0
	be,a	.L60
	 ld	[%i0+20], %o0
.L35:
	jmp	%i7+8
	 restore %g0, %i3, %o0
.L59:
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i0+20], %o0
	b	.L34
	 ld	[%i0], %i5
.L60:
	call	cortos_lock_release, 0
	 mov	%i3, %i0
	jmp	%i7+8
	 restore
.L44:
	b	.L36
	 mov	0, %i3
	.size	cortos_readMessages, .-cortos_readMessages
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
