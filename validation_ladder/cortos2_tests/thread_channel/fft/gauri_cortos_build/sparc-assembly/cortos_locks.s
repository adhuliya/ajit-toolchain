	.file	"cortos_locks.c"
	.section	".text"
	.align 4
	.global cortos_init_locks
	.type	cortos_init_locks, #function
	.proc	020
cortos_init_locks:
	mov	1, %g2
	sethi	%hi(allocatedLocksNc), %g1
	stb	%g2, [%g1+%lo(allocatedLocksNc)]
	sethi	%hi(1073844224), %g2
	sethi	%hi(cortos_reservedLockAddr), %g1
	jmp	%o7+8
	 st	%g2, [%g1+%lo(cortos_reservedLockAddr)]
	.size	cortos_init_locks, .-cortos_init_locks
	.align 4
	.global cortos_reserveLock
	.type	cortos_reserveLock, #function
	.proc	0114
cortos_reserveLock:
	save	%sp, -96, %sp
	cmp	%i0, 0
	be,a	.L13
	 sethi	%hi(lockStartAddr), %g1
	sethi	%hi(lockStartAddrNc), %g1
	sethi	%hi(allocatedLocksNc), %i4
	ld	[%g1+%lo(lockStartAddrNc)], %i0
	or	%i4, %lo(allocatedLocksNc), %i4
.L8:
	sethi	%hi(cortos_reservedLockAddr), %i5
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i5+%lo(cortos_reservedLockAddr)], %o0
	mov	%i4, %g1
	b	.L7
	 mov	0, %g2
.L5:
	add	%g2, 1, %g2
	cmp	%g2, 256
	be	.L14
	 add	%g1, 1, %g1
.L7:
	ldsb	[%g1], %g3
	cmp	%g3, 0
	bne	.L5
	 mov	%g2, %i4
	mov	1, %g3
	ld	[%i5+%lo(cortos_reservedLockAddr)], %o0
	stb	%g3, [%g1]
	call	cortos_lock_release, 0
	 add	%i0, %i4, %i0
	jmp	%i7+8
	 restore
.L13:
	sethi	%hi(allocatedLocks), %i4
	ld	[%g1+%lo(lockStartAddr)], %i0
	b	.L8
	 or	%i4, %lo(allocatedLocks), %i4
.L14:
	mov	256, %i4
	ld	[%i5+%lo(cortos_reservedLockAddr)], %o0
	call	cortos_lock_release, 0
	 add	%i0, %i4, %i0
	jmp	%i7+8
	 restore
	.size	cortos_reserveLock, .-cortos_reserveLock
	.align 4
	.global cortos_freeLock
	.type	cortos_freeLock, #function
	.proc	020
cortos_freeLock:
	save	%sp, -96, %sp
	sethi	%hi(lockStartAddr), %i5
	ld	[%i5+%lo(lockStartAddr)], %g1
	cmp	%g1, %i0
	bgu	.L16
	 add	%g1, 256, %g1
	cmp	%i0, %g1
	blu	.L17
	 sethi	%hi(cortos_reservedLockAddr), %i4
.L16:
	sethi	%hi(cortos_reservedLockAddr), %i5
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i5+%lo(cortos_reservedLockAddr)], %o0
	sethi	%hi(lockStartAddrNc), %g1
	sethi	%hi(allocatedLocksNc), %g2
	ld	[%g1+%lo(lockStartAddrNc)], %g1
	or	%g2, %lo(allocatedLocksNc), %g2
	sub	%i0, %g1, %g1
	ld	[%i5+%lo(cortos_reservedLockAddr)], %i0
	stb	%g0, [%g2+%g1]
	call	cortos_lock_release, 0
	 restore
.L17:
	call	cortos_lock_acquire_buzy, 0
	 ld	[%i4+%lo(cortos_reservedLockAddr)], %o0
	ld	[%i5+%lo(lockStartAddr)], %g1
	sethi	%hi(allocatedLocks), %g2
	sub	%i0, %g1, %g1
	or	%g2, %lo(allocatedLocks), %g2
	ld	[%i4+%lo(cortos_reservedLockAddr)], %i0
	stb	%g0, [%g2+%g1]
	call	cortos_lock_release, 0
	 restore
	.size	cortos_freeLock, .-cortos_freeLock
	.common	cortos_reservedLockAddr,4,4
	.common	allocatedLocksNc,256,8
	.common	allocatedLocks,256,8
	.global lockStartAddrNc
	.section	".data"
	.align 4
	.type	lockStartAddrNc, #object
	.size	lockStartAddrNc, 4
lockStartAddrNc:
	.long	1073844224
	.global lockStartAddr
	.align 4
	.type	lockStartAddr, #object
	.size	lockStartAddr, 4
lockStartAddr:
	.long	1073840128
	.ident	"GCC: (Buildroot 2014.08) 4.7.4"
	.section	.note.GNU-stack,"",@progbits
