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
  ! current value of window is 7

  ! clear all stack pointers in all windows
  call clear_stack_pointers
  nop

CORTOS_SET_PSR:
  ! enable traps, set current window=7
  set 0x10E0, %l0  ! 0x1067 for user mode (see p28 in sparcv8.pdf)
  wr %l0, %psr

COROTS_WIMSET:
  set 0x2, %l0   ! window 1 is marked invalid. We start at window 0.
  ! sll %l0, 7, %l0
  wr %l0, 0x0, %wim

  ! trap table.
  set	trap_table_base, %l0
  wr	%l0, 0x0, %tbr

CORTOS_READ_CORE_THREAD_ID:
  ! Read CORE,THREAD IDs into %l1.
  ! format of asr29
  !    0x50 0x52 core-id thread-id
  rd %asr29, %l1


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : common_init_header
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
