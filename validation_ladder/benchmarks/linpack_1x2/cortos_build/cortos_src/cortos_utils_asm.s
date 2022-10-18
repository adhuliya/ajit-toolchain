

.global cortos_exit

! exit routine : i0 has the exit code
cortos_exit:
  save  %sp, -96, %sp       ! func prefix
  wr %i0, %asr16            ! put the exit code in asr16
  ta 0                      ! exit by trapping
