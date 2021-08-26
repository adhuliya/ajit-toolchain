!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: common_init_header
!   Code executed across all threads, but
!   only linked to the source of thread (0,0)
!   NOTE: The size of this header is manually computed
!         and stored in consts.INIT_HEADER_SIZE vairable.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

!
! Ajit startup initialization code.
!
.section .text.ajitstart
.global _start;
_start: ! always starts at 0x00000000
  ! enable traps, set current window=0
  set 0x10E0, %l0
  wr %l0, %psr

  ! Read CORE,THREAD IDs into %l1.
  ! format of asr29
  !    0x50 0x52 core-id thread-id
  rd %asr29, %l1

  ! initialize some ASR's (AD: Is this optional?)
  wr 0x1, %asr16
  wr 0x2, %asr17
  wr 0x3, %asr18
  wr 0x4, %asr19

WIMSET:
  set 0x2, %l0		! window 1 is marked invalid...  we start at window 0
  wr %l0, 0x0, %wim	!

  ! trap table. (AD: is this common to all threads? or only to thread0?)
  set	trap_table_base, %l0
  wr	%l0, 0x0, %tbr

  ! jump to skip data area ahead
  call INIT_CORTOS_ALLOCATE_AREA_TO_ZERO
  nop

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : common_init_header
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
