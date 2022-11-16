	.file	"cortos_bget.c"
	.section	".text"
	.align 4
	.global __cortos_bpool
	.type	__cortos_bpool, #function
	.proc	020
__cortos_bpool:
	save	%sp, -96, %sp
	sethi	%hi(bgetLockAddr), %i5
	ld	[%i5+%lo(bgetLockAddr)], %g1
	cmp	%g1, 0
	bne	.L5
	 sethi	%hi(1073848320), %o0
	call	bpool, 0
	 sethi	%hi(4096), %o1
	sethi	%hi(allocatedLocksNc), %g1
	or	%g1, %lo(allocatedLocksNc), %g1
	mov	1, %g2
	stb	%g2, [%g1+2]
	sethi	%hi(1073844224), %g1
	or	%g1, 2, %g1
	st	%g1, [%i5+%lo(bgetLockAddr)]
.L5:
	jmp	%i7+8
	 restore
	.size	__cortos_bpool, .-__cortos_bpool
	.align 4
	.global cortos_bget
	.type	cortos_bget, #function
	.proc	0120
cortos_bget:
	save	%sp, -96, %sp
	sethi	%hi(bgetLockAddr), %i5
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i5+%lo(bgetLockAddr)], %o0
	call	bget, 0
	 mov	%i0, %o0
	mov	%o0, %i0
	call	cortos_lock_release, 0
	 ld	[%i5+%lo(bgetLockAddr)], %o0
	jmp	%i7+8
	 restore
	.size	cortos_bget, .-cortos_bget
	.align 4
	.global cortos_brel
	.type	cortos_brel, #function
	.proc	020
cortos_brel:
	save	%sp, -96, %sp
	sethi	%hi(bgetLockAddr), %i5
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i5+%lo(bgetLockAddr)], %o0
	call	brel, 0
	 mov	%i0, %o0
	ld	[%i5+%lo(bgetLockAddr)], %i0
	call	cortos_lock_release, 0
	 restore
	.size	cortos_brel, .-cortos_brel
	.align 4
	.global __cortos_bpool_ncram
	.type	__cortos_bpool_ncram, #function
	.proc	020
__cortos_bpool_ncram:
	save	%sp, -96, %sp
	sethi	%hi(bgetNcramLockAddr), %i5
	ld	[%i5+%lo(bgetNcramLockAddr)], %g1
	cmp	%g1, 0
	bne	.L11
	 mov	0, %o0
	call	bpool_ncram, 0
	 mov	-1, %o1
	sethi	%hi(allocatedLocksNc), %g1
	or	%g1, %lo(allocatedLocksNc), %g1
	mov	1, %g2
	stb	%g2, [%g1+3]
	sethi	%hi(1073844224), %g1
	or	%g1, 3, %g1
	st	%g1, [%i5+%lo(bgetNcramLockAddr)]
.L11:
	jmp	%i7+8
	 restore
	.size	__cortos_bpool_ncram, .-__cortos_bpool_ncram
	.align 4
	.global cortos_bget_ncram
	.type	cortos_bget_ncram, #function
	.proc	0120
cortos_bget_ncram:
	save	%sp, -96, %sp
	sethi	%hi(bgetNcramLockAddr), %i5
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i5+%lo(bgetNcramLockAddr)], %o0
	call	bget_ncram, 0
	 mov	%i0, %o0
	mov	%o0, %i0
	call	cortos_lock_release, 0
	 ld	[%i5+%lo(bgetNcramLockAddr)], %o0
	jmp	%i7+8
	 restore
	.size	cortos_bget_ncram, .-cortos_bget_ncram
	.align 4
	.global cortos_brel_ncram
	.type	cortos_brel_ncram, #function
	.proc	020
cortos_brel_ncram:
	save	%sp, -96, %sp
	sethi	%hi(bgetNcramLockAddr), %i5
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i5+%lo(bgetNcramLockAddr)], %o0
	call	brel_ncram, 0
	 mov	%i0, %o0
	ld	[%i5+%lo(bgetNcramLockAddr)], %i0
	call	cortos_lock_release, 0
	 restore
	.size	cortos_brel_ncram, .-cortos_brel_ncram
	.global bgetNcramLockAddr
	.section	".bss"
	.align 4
	.type	bgetNcramLockAddr, #object
	.size	bgetNcramLockAddr, 4
bgetNcramLockAddr:
	.skip	4
	.global bgetLockAddr
	.align 4
	.type	bgetLockAddr, #object
	.size	bgetLockAddr, 4
bgetLockAddr:
	.skip	4
	.ident	"GCC: (Buildroot 2014.08-g61fd03c-dirty) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
