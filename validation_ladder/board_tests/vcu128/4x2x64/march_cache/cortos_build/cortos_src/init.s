

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: common_init_header
!   Code executed across all threads.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

.section .data
.align 8
  MEM_START_ADDR: .word 0x0
  PT_FLAG: .word 0xffff2c00
  INIT_BY_00_DONE: .word 0xffff2c04

!
! Ajit startup initialization code.
!
.section .text.ajitstart

.global _start;
_start:
  ! current value of window is 0

  ! clear all stack pointers in all windows
  call clear_stack_pointers
  nop

CORTOS_SET_PSR:
  ! enable traps, set current window=0
  set 0x10E0, %l0  ! 0x1060 for user mode (see p28 in sparcv8.pdf)
  wr %l0, %psr

COROTS_WIMSET:
  set 0x1, %l0   ! window 0 is marked invalid. We start at window 0.
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


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: threads_setup
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CORTOS_SETUP_THREADS:
!!!!!  setting up stacks in each thread....


SETUP_THREAD_0_0:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set 0x50520000, %l2
  subcc %l1, %l2, %g0
  bnz SETUP_THREAD_0_1
  nop


  !!!!!!!!!!!!!!!!!!!   START: thread (0,0) setup section !!!!!!!!!!!!!!!!!!
  set 0x114fa0, %sp  ! set stack address
  clr %fp

  ! zero initialization of memory regions and flags
  set INIT_BY_00_DONE, %g2
  ld [%g2], %g2
  mov 0x0, %g3
  st %g3, [%g2]  ! set to zero

  set PT_FLAG, %g2
  ld [%g2], %g2
  mov 0x0, %g3
  st %g3, [%g2]  ! set to zero

  call __cortos_init_region_to_zero
  nop

  !
  ! set up virtual -> physical map.
  !  In this example, the same VA -> PA translation is used by all
  !  threads.  The page table is set up by thread (0,0).
  !
  call page_table_setup
  nop

  !
  !  set *PT_FLAG = 1.   This indicates that the page table has been written.
  !
  set PT_FLAG, %l6
  ld [%l6], %l6
  mov 1, %l7
  st %l7, [%l6]

  ! block start: setup the mmu
  call set_context_table_pointer
  nop

  ! enable mmu.. write 0x1 into mmu control register.
  set 0x1, %o0
  sta %o0, [%g0] 0x4
  ! block end  : setup the mmu

  call cortos_init_locks
  nop

  ! acquire memory for bget just once
  call __cortos_bpool
  nop
  ! acquire memory for bget ncram just once
  call __cortos_bpool_ncram
  nop

  ! initialize traps and interrupts
  call cortos_init_hw_traps
  nop
  call cortos_init_sw_traps
  nop

  call __cortos_enable_serial
  nop

  ! ! initialize the queue headers
  ! call cortos_init_queue_headers
  ! nop

  ! enable printing (cortos_printf)
  call cortos_init_printing
  nop

  ! enable cortos logging
  call cortos_init_logging
  nop

  ! initialization provided by user (executes on thread 0,0)
  ! no startup/init function provided by user.

  ! indicate that the system initialization is done!!!
  set INIT_BY_00_DONE, %g2
  ld [%g2], %g2
  mov 0x1, %g3
  st %g3, [%g2]  ! set to one

  ! Read CORE,THREAD IDs into %l1 (required for 0,0 here, as l1 gets corrupted)
  rd %asr29, %l1

  !  Thread (0,0) jumps to start running user code.
  ba CORTOS_START_THREADS
  nop
  ! ba AFTER_PTABLE_SETUP
  ! nop
  !!!!!!!!!!!!!!!!!!!   END  : thread (0,0) setup section !!!!!!!!!!!!!!!!!!





SETUP_THREAD_0_1:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set 0x50520001, %l2
  subcc %l1, %l2, %g0
  bnz SETUP_THREAD_1_0
  nop




  !!!!!!!!!!!!   START: thread (0,1) setup section !!!!!!!
  set 0x117fa0, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_by_00
  nop

  !  Thread (0,1) jumps to wait for mmu..
  ba WAIT_UNTIL_MMU_IS_ENABLED
  nop
  !!!!!!!!!!!!   END  : thread (0,1) setup section !!!!!!!



SETUP_THREAD_1_0:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set 0x50520100, %l2
  subcc %l1, %l2, %g0
  bnz SETUP_THREAD_1_1
  nop



  !!!!!!!!!!!!   START: thread (1,0) setup section !!!!!!!
  set 0x11afa0, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_by_00
  nop

  !  Thread (1,0) jumps to AFTER_PTABLE_SETUP.
  ba AFTER_PTABLE_SETUP
  nop
  !!!!!!!!!!!!   END  : thread (1,0) setup section !!!!!!!




SETUP_THREAD_1_1:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set 0x50520101, %l2
  subcc %l1, %l2, %g0
  bnz SETUP_THREAD_2_0
  nop




  !!!!!!!!!!!!   START: thread (1,1) setup section !!!!!!!
  set 0x11dfa0, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_by_00
  nop

  !  Thread (1,1) jumps to wait for mmu..
  ba WAIT_UNTIL_MMU_IS_ENABLED
  nop
  !!!!!!!!!!!!   END  : thread (1,1) setup section !!!!!!!



SETUP_THREAD_2_0:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set 0x50520200, %l2
  subcc %l1, %l2, %g0
  bnz SETUP_THREAD_2_1
  nop



  !!!!!!!!!!!!   START: thread (2,0) setup section !!!!!!!
  set 0x120fa0, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_by_00
  nop

  !  Thread (2,0) jumps to AFTER_PTABLE_SETUP.
  ba AFTER_PTABLE_SETUP
  nop
  !!!!!!!!!!!!   END  : thread (2,0) setup section !!!!!!!




SETUP_THREAD_2_1:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set 0x50520201, %l2
  subcc %l1, %l2, %g0
  bnz SETUP_THREAD_3_0
  nop




  !!!!!!!!!!!!   START: thread (2,1) setup section !!!!!!!
  set 0x123fa0, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_by_00
  nop

  !  Thread (2,1) jumps to wait for mmu..
  ba WAIT_UNTIL_MMU_IS_ENABLED
  nop
  !!!!!!!!!!!!   END  : thread (2,1) setup section !!!!!!!



SETUP_THREAD_3_0:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set 0x50520300, %l2
  subcc %l1, %l2, %g0
  bnz SETUP_THREAD_3_1
  nop



  !!!!!!!!!!!!   START: thread (3,0) setup section !!!!!!!
  set 0x126fa0, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_by_00
  nop

  !  Thread (3,0) jumps to AFTER_PTABLE_SETUP.
  ba AFTER_PTABLE_SETUP
  nop
  !!!!!!!!!!!!   END  : thread (3,0) setup section !!!!!!!




SETUP_THREAD_3_1:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set 0x50520301, %l2
  subcc %l1, %l2, %g0
  bnz CORTOS_HALT_ERROR
  nop




  !!!!!!!!!!!!   START: thread (3,1) setup section !!!!!!!
  set 0x129fa0, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_by_00
  nop

  !  Thread (3,1) jumps to wait for mmu..
  ba WAIT_UNTIL_MMU_IS_ENABLED
  nop
  !!!!!!!!!!!!   END  : thread (3,1) setup section !!!!!!!



!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : threads_setup
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


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
  ! read mmu control register.
  set 0x1, %o0
  lda [%g0] 0x4, %o0
  andcc %o0, 0x1, %o0

  ! spin as long as mmu_control = 0.
  bz WAIT_UNTIL_MMU_IS_ENABLED
  nop

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : mmu_and_page_table_waits
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: threads_user_logic
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CORTOS_START_THREADS:


EXECUTE_THREAD_0_0:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set 0x50520000, %l2
  subcc %l1, %l2, %g0
  bnz EXECUTE_THREAD_0_1
  nop

!!!!!!! BLOCK START: Call_functions_sequentially.
  call main_00
  nop
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
START_THREAD_0_0_LOOP:


!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop


EXECUTE_THREAD_0_1:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set 0x50520001, %l2
  subcc %l1, %l2, %g0
  bnz EXECUTE_THREAD_1_0
  nop

!!!!!!! BLOCK START: Call_functions_sequentially.
  call main_01
  nop
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
START_THREAD_0_1_LOOP:


!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop


EXECUTE_THREAD_1_0:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set 0x50520100, %l2
  subcc %l1, %l2, %g0
  bnz EXECUTE_THREAD_1_1
  nop

!!!!!!! BLOCK START: Call_functions_sequentially.
  call main_10
  nop
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
START_THREAD_1_0_LOOP:


!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop


EXECUTE_THREAD_1_1:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set 0x50520101, %l2
  subcc %l1, %l2, %g0
  bnz EXECUTE_THREAD_2_0
  nop

!!!!!!! BLOCK START: Call_functions_sequentially.
  call main_11
  nop
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
START_THREAD_1_1_LOOP:


!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop


EXECUTE_THREAD_2_0:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set 0x50520200, %l2
  subcc %l1, %l2, %g0
  bnz EXECUTE_THREAD_2_1
  nop

!!!!!!! BLOCK START: Call_functions_sequentially.
  call main_20
  nop
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
START_THREAD_2_0_LOOP:


!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop


EXECUTE_THREAD_2_1:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set 0x50520201, %l2
  subcc %l1, %l2, %g0
  bnz EXECUTE_THREAD_3_0
  nop

!!!!!!! BLOCK START: Call_functions_sequentially.
  call main_21
  nop
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
START_THREAD_2_1_LOOP:


!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop


EXECUTE_THREAD_3_0:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set 0x50520300, %l2
  subcc %l1, %l2, %g0
  bnz EXECUTE_THREAD_3_1
  nop

!!!!!!! BLOCK START: Call_functions_sequentially.
  call main_30
  nop
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
START_THREAD_3_0_LOOP:


!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop


EXECUTE_THREAD_3_1:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set 0x50520301, %l2
  subcc %l1, %l2, %g0
  bnz CORTOS_HALT_ERROR
  nop

!!!!!!! BLOCK START: Call_functions_sequentially.
  call main_31
  nop
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
START_THREAD_3_1_LOOP:


!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : threads_user_logic
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


!
! A utility which initializes all stack pointers to 0.
!
.global __cortos_clear_stack_pointers
__cortos_clear_stack_pointers:
	mov %g0, %wim

	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
 	save
	mov %g0, %sp
	save

	retl
	nop


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: init_allocated_memory_to_zero
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! This routine initializes a pre-determined region(s) of memory to zero.
! This routine works before the MMU is set.

.global __cortos_init_region_to_zero

! initialize a set of regions to zeros
! Only for thread 0,0
__cortos_init_region_to_zero:

  ! BLOCK START: zero_init zero_region_BssSection
  ! set the base address
  sethi %hi(0x11000), %l0
  or %l0, %lo(0x11000), %l0

  ! set the first illegal address
  sethi %hi(0x16000), %l2
  or %l2, %lo(0x16000), %l2
  sub %l2, 0x4, %l2         ! address of last valid word location

! loop to store zeros byte by byte
_cortos_zero_init_area_BssSection:
  stb %g0, [%l0]             ! zero stored here
  subcc %l0, %l2, %g0
  bne _cortos_zero_init_area_BssSection
  add %l0, 0x1, %l0         ! get address of next byte
  ! BLOCK END  : zero_init zero_region_BssSection

  ! BLOCK START: zero_init zero_region_CacheableLocks
  ! set the base address
  sethi %hi(0x16000), %l0
  or %l0, %lo(0x16000), %l0

  ! set the first illegal address
  sethi %hi(0x17000), %l2
  or %l2, %lo(0x17000), %l2
  sub %l2, 0x4, %l2         ! address of last valid word location

! loop to store zeros byte by byte
_cortos_zero_init_area_CacheableLocks:
  stb %g0, [%l0]             ! zero stored here
  subcc %l0, %l2, %g0
  bne _cortos_zero_init_area_CacheableLocks
  add %l0, 0x1, %l0         ! get address of next byte
  ! BLOCK END  : zero_init zero_region_CacheableLocks

  ! BLOCK START: zero_init zero_region_NonCacheableLocks
  ! set the base address
  sethi %hi(0x17000), %l0
  or %l0, %lo(0x17000), %l0

  ! set the first illegal address
  sethi %hi(0x18000), %l2
  or %l2, %lo(0x18000), %l2
  sub %l2, 0x4, %l2         ! address of last valid word location

! loop to store zeros byte by byte
_cortos_zero_init_area_NonCacheableLocks:
  stb %g0, [%l0]             ! zero stored here
  subcc %l0, %l2, %g0
  bne _cortos_zero_init_area_NonCacheableLocks
  add %l0, 0x1, %l0         ! get address of next byte
  ! BLOCK END  : zero_init zero_region_NonCacheableLocks


  ! restore                   ! func suffix
  jmp %o7+8                 ! func suffix
  nop                       ! func suffix

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : init_allocated_memory_to_zero
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: wait_for_init
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
.global __cortos_wait_for_init_by_00
__cortos_wait_for_init_by_00:

  set INIT_BY_00_DONE, %l6
  ld [%l6], %l6
_CORTOS_WAIT_FOR_INIT_BY_00:
  ld [%l6], %l7
  mov 0x1, %i0
  subcc %i0, %l7, %g0
  ! l7 = 1 after page tables have been setup.
  bnz _CORTOS_WAIT_FOR_INIT_BY_00
  nop

  ! restore                   ! func suffix
  jmp %o7+8                 ! func suffix
  nop                       ! func suffix

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : wait_for_init
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


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

