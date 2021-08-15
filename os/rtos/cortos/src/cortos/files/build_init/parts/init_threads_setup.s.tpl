
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: threads_setup
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CORTOS_SETUP_THREADS:
!!!!!  setting up stacks in each thread....

% for prog in confObj.programs:

{{prog.thread.genLabel(forSetup=True)}}:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
  set {{prog.thread.genIdHex()}}, %l2
  subcc %l1, %l2, %g0
  bnz {{confObj.genNextThreadLabel(prog.thread, forSetup=True)}}
  nop

% if prog.isThread00():

  !!!!!!!!!!!!!!!!!!!   START: thread (0,0) setup section !!!!!!!!!!!!!!!!!!
  set {{hex(prog.stackStartAddr)}}, %sp  ! set stack address
  clr %fp

  !
  ! set up virtual -> physical map.
  !  In this example, the same VA -> PA translation is used by all
  !  threads.  The page table is set up by thread (0,0).
  !
  call page_table_setup
  nop

  !
  !  set PT_FLAG = 1.   This indicates that the page table has been written.
  !
  set PT_FLAG, %l6
  mov 1, %l7
  st %l7, [%l6]

% if confObj.enableSerial:
  call cortos_enable_serial
  nop
% end

  !  Thread (0,0) jumps to AFTER_PTABLE_SETUP.
  ba AFTER_PTABLE_SETUP
  nop
  !!!!!!!!!!!!!!!!!!!   END  : thread (0,0) setup section !!!!!!!!!!!!!!!!!!

% end

% if prog.thread.tid == 0 and not prog.isThread00():

  !!!!!!!!!!!!   START: thread ({{prog.thread.cid}},0) setup section !!!!!!!
  set {{hex(prog.stackStartAddr)}}, %sp  ! set stack address
  clr %fp

  !  Thread ({{prog.thread.cid}},0) jumps to AFTER_PTABLE_SETUP.
  ba AFTER_PTABLE_SETUP
  nop
  !!!!!!!!!!!!   END  : thread ({{prog.thread.cid}},0) setup section !!!!!!!

% end

% if prog.thread.tid == 1:

  !!!!!!!!!!!!   START: thread ({{prog.thread.cid}},1) setup section !!!!!!!
  set {{hex(prog.stackStartAddr)}}, %sp  ! set stack address
  clr %fp

  !  Thread ({{prog.thread.cid}},1) jumps to wait for mmu..
  ba WAIT_UNTIL_MMU_IS_ENABLED
  nop
  !!!!!!!!!!!!   END  : thread ({{prog.thread.cid}},1) setup section !!!!!!!

% end

% end

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : threads_setup
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

