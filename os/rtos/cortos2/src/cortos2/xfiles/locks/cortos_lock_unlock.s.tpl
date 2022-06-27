! see the reference file `cortos/res/lock_unlock.s`

! Usage Note:
! cortos_lock_acquire_buzy(<index: an-integer-index>);
!   CRITICAL_SECTION_CODE...
! cortos_lock_release(<index: an-integer-index>);
! ----or-------or--------
! status = cortos_lock_acquire(<index: an-integer-index>);
! if (status == 1) {
!   CRITICAL_SECTION_CODE...
!   cortos_lock_release(<index: an-integer-index>);
! }

.global cortos_lock_acquire_buzy
.global cortos_lock_acquire
.global cortos_lock_release

! FUNCTION
cortos_lock_acquire_buzy:
  ! i0 contains the address to the correct locking variable
  save  %sp, -96, %sp       ! func prefix

wait_for_lock:
  ldub [%i0], %l1
  tst %l1
  bne wait_for_lock
  nop
try_to_lock:
  ldstub [%i0], %l1
  tst %l1
  be out
  nop
  ba,a wait_for_lock
out:
  or %g0, 0x1, %i0          ! return 1 on success

  restore                   ! func suffix
  jmp %o7+8                 ! func suffix
  nop                       ! func suffix


! FUNCTION
cortos_lock_acquire:
  ! Try to acquire the given lock id.
  ! if lock couldn't be acquired, it returns 0 (else 1)
  ! i0 contains an index to the correct locking variable
  save  %sp, -96, %sp       ! func prefix

try_to_lock_once:
  ldstub [%i0], %l1
  tst %l1
  be lock_acquired
  nop
  ba,a lock_not_acquired

lock_acquired:
  ba exit_cortos_lock_acquire
  or %g0, 0x1, %i0          ! return 1 on success

lock_not_acquired:
  or %g0, %g0, %i0          ! return 0 on failure

exit_cortos_lock_acquire:
  restore                   ! func suffix
  jmp %o7+8                 ! func suffix
  nop                       ! func suffix


! FUNCTION
cortos_lock_release:
  ! Release the given lock.
  ! i0 contains an index to the correct locking variable
  save  %sp, -96, %sp       ! func prefix

  stbar
  stub %g0, [%i0]

  restore                   ! func suffix
  jmp %o7+8                 ! func suffix
  nop                       ! func suffix

