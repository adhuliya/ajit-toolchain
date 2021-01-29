!
! A utility package consisting of mutex routines.
! Two versions are provided.  One with SWAP and
! one with ldstub.
!

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!  SWAP version				          !!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
! has one argument assumed to be in %i0,
! which specifies the address of the mutex
! variable to be used. 
!
.global acquire_mutex_using_swap
acquire_mutex_using_swap :
	save %sp, -96, %sp
	mov 0x1, %l5 
	!  LOCK_FLAG is swapped with 0x1
	swap [%i0], %l5
	tst %l5
	! If read-value of LOCK_FLAG is 0,
	!   then lock has been acquired.
	be swap_lock_acquired
	nop
spin_on_swap_lock:
	! lock not acquired.. spin until
	! LOCK_FLAG becomes 0..	
	ld [%i0], %l5
	tst %l5
	bne spin_on_swap_lock
	nop
	ba,a acquire_mutex_using_swap
	nop
swap_lock_acquired:
	retl
	restore
!
! single argument: %i0 contains the address
! of the mutex variable to be cleared.
!
.global release_mutex_using_swap
release_mutex_using_swap:
	save %sp, -96, %sp
	st %g0, [%i0]
	retl
	restore

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!  LDSTUB version				          !!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
.global acquire_mutex_using_ldstub
!
! has one argument assumed to be in %i0,
! which specifies the address of the mutex
! variable to be used. 
!
acquire_mutex_using_ldstub :
	save %sp, -96, %sp
	mov 0x1, %o1
	ldstub [%i0], %o1
	tst %o1
	! If read-value of LOCK_FLAG is 0,
	!   then lock has been acquired.
	be ldstub_mutex_acquired
	nop
spin_on_ldstub_mutex:
	! lock not acquired.. spin until
	! LOCK_FLAG becomes 0..	
	ldub [%i0], %o1
	tst %o1
	bne spin_on_ldstub_mutex
	nop
	! Someone has released the lock
	! Try to acquire it!
	ba,a acquire_mutex_using_ldstub
ldstub_mutex_acquired:
	retl
	restore
!
! has one argument assumed to be in %i0,
! which specifies the address of the mutex
! variable to be used. 
!
.global release_mutex_using_ldstub
release_mutex_using_ldstub:
	save %sp, -96, %sp
	stub %g0, [%i0]
	retl
	restore
