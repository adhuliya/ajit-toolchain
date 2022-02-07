
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

% for zeroRegion in confObj.memoryLayout.zeroRegionSeq:
  ! BLOCK START: zero_init zero_region_{{zeroRegion.name}}
  ! set the base address
  sethi %hi({{ hex(zeroRegion.getFirstByteAddr(False)) }}), %l0
  or %l0, %lo({{ hex(zeroRegion.getFirstByteAddr(False)) }}), %l0

  ! set the first illegal address
  sethi %hi({{ hex(zeroRegion.getLastByteAddr(False)+1) }}), %l2
  or %l2, %lo({{ hex(zeroRegion.getLastByteAddr(False)+1) }}), %l2
  sub %l2, 0x4, %l2         ! address of last valid word location

! loop to store zeros byte by byte
_cortos_zero_init_area_{{zeroRegion.name}}:
  stb %g0, [%l0]             ! zero stored here
  subcc %l0, %l2, %g0
  bne _cortos_zero_init_area_{{zeroRegion.name}}
  add %l0, 0x1, %l0         ! get address of next byte
  ! BLOCK END  : zero_init zero_region_{{zeroRegion.name}}

% end

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
