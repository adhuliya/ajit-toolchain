
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: common_init_footer
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CORTOS_HALT_ERROR:
  ! Write some value into asr16 to close.
  ! 0x1 is halt due to error while initialization in this script.
  wr 0x1, %asr16
  ta 0

CORTOS_HALT_OKAY:
  ! Write some value into asr16 to close.
  ! 0x0 is an expected/normal halt.
  wr 0x0, %asr16
  ta 0

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : common_init_footer
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
