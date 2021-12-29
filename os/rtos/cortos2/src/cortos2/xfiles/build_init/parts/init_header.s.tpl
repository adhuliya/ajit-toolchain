!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: common_init_header
!   Code executed across all threads.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

.section .bss
.align 8
  MEM_START_ADDR: .word {{ hex(confObj.hardware.memory.ram.physicalStartAddr) }}
  PT_FLAG: .word {{ hex(confObj.hardware.devices["ScratchArea"].memoryRegion.physicalStartAddr) }}
  INIT_TO_ZERO_DONE: .word {{ hex(confObj.hardware.devices["ScratchArea"].memoryRegion.physicalStartAddr + 4) }}

!
! Ajit startup initialization code.
!
.section .text.ajitstart

.global _start;
_start:

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

  ! trap table.
  set	trap_table_base, %l0
  wr	%l0, 0x0, %tbr



!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : common_init_header
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
