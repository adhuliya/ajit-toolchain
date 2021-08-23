
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: threads_user_logic
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CORTOS_START_THREADS:

% for prog in confObj.programs:

{{prog.thread.genLabel(forSetup=False)}}:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set {{prog.thread.genIdHex()}}, %l2
  subcc %l1, %l2, %g0
  bnz {{confObj.genNextThreadLabel(prog.thread, forSetup=False)}}
  nop

% if prog.isThread00() and confObj.addBget:
  ! acquire memory for bget just once
  call __cortos_bpool
  nop
% end

!!!!!!! BLOCK START: Call_functions_sequentially.
% for calleeName in prog.initCallSeq:
  call {{calleeName}}
  nop
% end
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
{{prog.thread.genLabelForCortosLoop()}}:

% for calleeName in prog.loopCallSeq:
  call {{calleeName}}
  nop
% end

% if len(prog.loopCallSeq) > 0:
  ba {{prog.thread.genLabelForCortosLoop()}}
  nop
% end
!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop

% end

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : threads_user_logic
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
