! initializes an array of words to zero
! INPUT: baseAddr and sizeInWords

  ! set the base address
  sethi %hi({{baseAddr}}), %l0
  or %g0, %lo({{baseAddr}}), %l0

  ! number of words (32 bit) to initialize to zero
  sethi %hi({{sizeInWords}}), %l1
  or %g0, %lo({{sizeInWords}}), %l1

! loop to store zeros
{{loopLabel}}:
  st %g0, [%l0]             ! zero stored here
  subcc %l1, 0x1, %l1
  bne {{loopLabel}}
  add %l0, 0x4, %l0         ! get address of next word

! if here, then the array is initialized to zeros
