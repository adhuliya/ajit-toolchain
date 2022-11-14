
.global cortos_trap

! invoke a software trap : i0 has the exit code
cortos_trap:
  save  %sp, -96, %sp       ! func prefix

  ta %i0                    ! trap with the given code

  restore                   ! func suffix
  jmp %o7+8                 ! func suffix
  nop                       ! func suffix
