.section .text.ajitstart
_start:
  ! initial values
  ! g1 >= g2.
  mov 0x9, %g1
  mov 0x2, %g2

  ! g1 = g1 - g2
  subcc %g1, %g2, %g1

loopbegin:
 
  bz done
  nop

  ! ensure that g1 >= g2.
  subcc %g1, %g2, %g0
  bge,a   loopbegin
  subcc %g1, %g2, %g1    ! delay slot
			 ! annulled if branch
			 ! not taken.
  
  ! swap g1, g2
  mov %g1, %g3
  mov %g2, %g1
  mov %g3, %g2

  ba loopbegin
  subcc %g1, %g2, %g1     ! delay slot

done:
   ! result is in g2
 
   ta 0


