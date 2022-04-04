
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

% if confObj.software.bget.enable:
  ! acquire memory for bget just once
  call __cortos_bpool
  nop
% end
% if confObj.hardware.memory.ncram.sizeInBytes:
  ! acquire memory for bget ncram just once
  call __cortos_bpool_ncram
  nop
% end

  ! initialize traps and interrupts
  call cortos_init_hw_traps
  nop
  call cortos_init_sw_traps
  nop

% if confObj.software.build.enableSerial and (not confObj.software.build.enableSerialInt):
  call __cortos_enable_serial
  nop
% end
% if confObj.software.build.enableSerialInt:
  call __cortos_enable_serial_interrupt
  nop
% end

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
% if confObj.software.startup.startupFuncName:
  call {{ confObj.software.startup.startupFuncName }}
  nop
% else:
  ! no startup/init function provided by user.
% end

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

% end

% if progThread.coreThread.tid == 0 and not progThread.isThread00():

  !!!!!!!!!!!!   START: thread ({{ progThread.coreThread.cid }},0) setup section !!!!!!!
  set {{ hex(progThread.getStackStartAddr()) }}, %sp  ! set stack address
  clr %fp

  call __cortos_wait_for_init_by_00
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

  call __cortos_wait_for_init_by_00
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

