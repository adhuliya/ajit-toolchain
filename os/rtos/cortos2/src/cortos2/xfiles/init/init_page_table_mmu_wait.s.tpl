!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: mmu_and_page_table_waits
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

AFTER_PTABLE_SETUP:
  !  threads (0,0), (1,0), ... come here, and check if PT_FLAG is set.
  set PT_FLAG, %l6
  ld [%l6], %l6
  ld [%l6], %l7

  mov 0x1, %i0
  subcc %i0, %l7,  %g0

  ! l7 = 1 after page tables have been setup.
  bnz AFTER_PTABLE_SETUP
  nop

  call set_context_table_pointer
  nop

  ! enable mmu.. write 0x1 into mmu control register.
  set 0x1, %o0
  sta %o0, [%g0] 0x4

  ! jump to run threads.
  ba CORTOS_START_THREADS
  nop

WAIT_UNTIL_MMU_IS_ENABLED:
  ! threads (0,1), (1,1), ... will spin here until their mmu
  ! is enabled.
  !
  ! MPD: this logic has been changed because of the multi-context munit
  !      In the multi-context munit, the MMU needs to be setup (context table pointer 
  !      and mmu_enable by each thread.   This logic will work for the single context
  !      case as well.
  ! spin until PT_FLAG becomes 1.
ODD_THREAD_WAIT_ON_PTABLE_SETUP:

  set PT_FLAG, %l6
  ld [%l6], %l6
  ld [%l6], %l7

  mov 0x1, %i0
  subcc %i0, %l7,  %g0

  ! l7 = 1 after page tables have been setup.
  bnz ODD_THREAD_WAIT_ON_PTABLE_SETUP
  nop

  ! set the context table pointer for the odd thread.
  call set_context_table_pointer
  nop

  ! Enable the MMU for odd threads.
  set 0x1, %o0
  sta %o0, [%g0] 0x4

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : mmu_and_page_table_waits
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
