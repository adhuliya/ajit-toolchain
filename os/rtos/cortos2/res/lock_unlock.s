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