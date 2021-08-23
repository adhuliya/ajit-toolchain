
! Allocates a memory area and initializes it to zero.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: allocate_memory_for_queue_lockvars_etc
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

% r = confObj.reservedMem

.align 8
CORTOS_INIT_TO_ZERO_START:

.align 8
CORTOS_RESERVED_SPACE: .skip {{r.cortosReserved.sizeInBytes}} ! size in multiples of 8

.align 8
CORTOS_INT_ARRAY_BASE: .skip {{r.cortosSharedIntVars.sizeInBytes}} ! size in multiples of 8

.align 8
CORTOS_RES_LOCK_VARS_BASE: .skip {{r.cortosLockVars.sizeInBytes}} ! size in multiples of 8

.align 8
CORTOS_LOCK_VARS_BASE: .skip {{r.cortosLockVars.sizeInBytes}} ! size in multiples of 8

.align 8
CORTOS_QUEUE_LOCK_VARS_BASE: .skip {{r.cortosQueueLockVars.sizeInBytes}} ! size in multiples of 8

.align 8
CORTOS_QUEUE_HEADERS_BASE: .skip {{r.cortosQueueHeaders.sizeInBytes}} ! size in multiples of 8

.align 8
CORTOS_QUEUES_BASE: .skip {{r.cortosQueues.sizeInBytes}} ! size in multiples of 8

.align 8
CORTOS_INIT_TO_ZERO_END:

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : allocate_memory_for_queue_lockvars_etc
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



% if confObj.addBget:
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: cortos_bget_memory_area
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

.align 8
CORTOS_BGET_MEM_BASE: .skip {{r.cortosBgetMemory.sizeInBytes}} ! size in multiples of 8

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: cortos_bget_memory_area
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
% end



!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK START: init_allocated_memory_to_zero
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

! initialize the region above to zeros
! Only for thread 0,0 enters here.
INIT_CORTOS_ALLOCATE_AREA_TO_ZERO:

! (0,0)=0x50520000, (0,1)=0x50520001, (1,0)=0x50520100, (1,1)=0x50520101, ...
set 0x50520000, %l2
subcc %l1, %l2, %g0
bnz CORTOS_SETUP_THREADS
nop

  ! set the base address
  sethi %hi(CORTOS_INIT_TO_ZERO_START}), %l0
  or %l0, %lo(CORTOS_INIT_TO_ZERO_START), %l0

  ! set the first illegal address
  sethi %hi(CORTOS_INIT_TO_ZERO_END), %l2
  or %l2, %lo(CORTOS_INIT_TO_ZERO_END), %l2
  sub %l2, 0x4, %l2         ! address of last valid word location

! loop to store zeros word by word (assumes size is at least 4 bytes)
zero_init_cortos_allocate_area:
  st %g0, [%l0]             ! zero stored here
  subcc %l0, %l2, %g0
  bne zero_init_cortos_allocate_area
  add %l0, 0x4, %l0         ! get address of next word

! if here, then the region is initialized to zeros

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! BLOCK END  : init_allocated_memory_to_zero
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


