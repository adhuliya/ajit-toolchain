! Top level cortos loop file for each thread.
! This init file links with each program (i.e. each Ajit thread)



.section .text.ajitstart.cortosloop

.global AJIT_CORTOS_THREAD_LOOP


! start label of the cortos routine
! this starts at an an address decided by AjitCoRtos
AJIT_CORTOS_THREAD_LOOP:

  ! call next function to execute
  call ajit_entry_func_001
  nop

  ! call next function to execute
  call ajit_entry_func_010
  nop




  ! loop to the start
  ba AJIT_CORTOS_THREAD_LOOP
  nop


