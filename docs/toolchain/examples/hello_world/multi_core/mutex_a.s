
.global acquire_lock
acquire_lock :
	set LOCK_FLAG, %o0
	mov 0x1, %o1
	! Atomic read of LOCK_FLAG,
	!  with LOCK_FLAG being swapped with 0x1
	swapa [%o0] 0x20, %o1
	tst %o1
	! If read-value of LOCK_FLAG is 0,
	!   then lock has been acquired.
	be lock_acquired
	nop
spin_on_lock:
	! lock not acquired.. spin until
	! LOCK_FLAG becomes 0..	
	lda [%o0] 0x20, %o1
	tst %o1
	bne spin_on_lock
	nop
	ba,a acquire_lock
lock_acquired:
	retl
	nop

.global release_lock
release_lock:
	set LOCK_FLAG, %o0
	sta %g0, [%o0] 0x20
	retl
	nop

! initialized to 0
.align 4
      PT_FLAG: .word 0x0
.align 4
      LOCK_FLAG: .word 0x0
