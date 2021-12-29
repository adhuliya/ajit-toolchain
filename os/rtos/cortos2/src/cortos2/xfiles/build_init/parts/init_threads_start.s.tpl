
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: threads_user_logic
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

CORTOS_START_THREADS:

% for progThread in confObj.software.program.programThreads:

{{progThread.coreThread.genLabel(forSetup=False)}}:

  ! (0,0)=0x50520000, (0,1)=0x50520001, (1,1)=0x50520101, ...
  set {{progThread.coreThread.genIdHex()}}, %l2
  subcc %l1, %l2, %g0
  bnz {{confObj.hardware.cpu.genNextThreadLabel(progThread.coreThread, forSetup=False)}}
  nop

% if progThread.isThread00() and confObj.software.bget.enable:
  ! acquire memory for bget just once
  call __cortos_bpool
  nop
% end

!!!!!!! BLOCK START: Call_functions_sequentially.
% for calleeName in progThread.initCallSeq:
  call {{calleeName}}
  nop
% end
!!!!!!! BLOCK END  : Call_functions_sequentially.


!!!!!!! BLOCK START: Call_functions_in_a_loop.
{{progThread.coreThread.genLabelForCortosLoop()}}:

% for calleeName in progThread.loopCallSeq:
  call {{calleeName}}
  nop
% end

% if len(progThread.loopCallSeq) > 0:
  ba {{progThread.coreThread.genLabelForCortosLoop()}}
  nop
% end
!!!!!!! BLOCK END  : Call_functions_in_a_loop.

  ba CORTOS_HALT_OKAY  ! in case of cortos loop, this is unreachable
  nop

% end

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : threads_user_logic
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
