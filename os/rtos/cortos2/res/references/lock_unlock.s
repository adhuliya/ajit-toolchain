! Spin Lock Logic using ldstub

! Page 271 of the SparcV8 Manual (Figure J-2, Section J.4)
! A spin lock is a lock for which the “lock held” condition is handled by busy wait-
! ing. Figure J-2 shows how spin locks can be implemented using LDSTUB. A
! nonzero value for the lock represents the locked condition, while a value of
! zero means that the lock is free. Note that the code busy waits by doing loads to
! avoid generating expensive stores to a potentially shared location. The STBAR
! in UnLock ensures that pending user stores are completed before the store that
! frees the lock.

LockWithLDSTUB:
retry:
  ldstub [{{lock}}], %l0
  tst %l0
  be out
  nop
loop:
  ldub [{{lock}}], %l0
  tst %l0
  bne loop
  nop
  ba,a retry
out:
  nop


UnLockWithLDSTUB: (lock)
 stbar
 stub %g0, [{{lock}}]
