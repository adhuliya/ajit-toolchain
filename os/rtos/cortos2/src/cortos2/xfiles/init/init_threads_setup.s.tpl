
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: threads_setup
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CORTOS_SETUP_THREADS:
!!!!!  setting up stacks in each thread....

% for progThread in confObj.software.program.programThreads:

{{ progThread.coreThread.genLabel(forSetup=True) }}:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set {{ progThread.coreThread.genIdHex() }}, %l2
  subcc %l1, %l2, %g0
  bnz {{ confObj.hardware.cpu.genNextThreadLabel(progThread.coreThread, forSetup=True) }}
  nop

% if progThread.isThread00():

  !!!!!!!!!!!!!!!!!!!   START: thread (0,0) setup section !!!!!!!!!!!!!!!!!!
  set {{ hex(progThread.getStackStartAddr()) }}, %sp  ! set stack address
  clr %fp

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

% if confObj.software.build.enableSerial:
  call __cortos_enable_serial
  nop
% end

  !  Thread (0,0) jumps to AFTER_PTABLE_SETUP.
  ba AFTER_PTABLE_SETUP
  nop
  !!!!!!!!!!!!!!!!!!!   END  : thread (0,0) setup section !!!!!!!!!!!!!!!!!!

% end

% if progThread.coreThread.tid == 0 and not progThread.isThread00():

  !!!!!!!!!!!!   START: thread ({{ progThread.coreThread.cid }},0) setup section !!!!!!!
  set {{ hex(progThread.getStackStartAddr()) }}, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_1
  nop

  !  Thread ({{ progThread.coreThread.cid }},0) jumps to AFTER_PTABLE_SETUP.
  ba AFTER_PTABLE_SETUP
  nop
  !!!!!!!!!!!!   END  : thread ({{ progThread.coreThread.cid }},0) setup section !!!!!!!

% end

% if progThread.coreThread.tid == 1:

  !!!!!!!!!!!!   START: thread ({{ progThread.coreThread.cid }},1) setup section !!!!!!!
  set {{ hex(progThread.getStackStartAddr()) }}, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_1
  nop

  !  Thread ({{ progThread.coreThread.cid }},1) jumps to wait for mmu..
  ba WAIT_UNTIL_MMU_IS_ENABLED
  nop
  !!!!!!!!!!!!   END  : thread ({{ progThread.coreThread.cid }},1) setup section !!!!!!!

% end

% end

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : threads_setup
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

