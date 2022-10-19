! A "safe" ISR, which can be guaranteed not to corrupt the user
! stack.
!
! Copies the entire state of the running thread into an isr
! buffer.
!
! Runs the interrupt handler on its own 4KB stack 
!
! Recovers the entire state of the running thread from
! the isr buffer.
!
! jmpl/rett to get out.
!
!
! Comments:  a bit excessive, but SAFE.
!
.section .data.traphandlers
.global generic_isr_save_buffer
.align 1024
generic_isr_save_buffer:
.skip 1024

.section .data.traphandlers
! 4KB for now, configurable later.
.global generic_isr_stack_buffer
.align 4096
generic_isr_stack_buffer:
.skip 4096

!
! There was an interrupt in window W, we move to trap window T
!
!  1. Save the wim psr y to generic_isr_save_buffer
!  2. Save all globals to generic_isr_save_buffer.
!  3. Save all window registers to generic_isr_save_buffer.
! 
!  This needs 3 + 8 + 128 = 139 words. give up 160 words 
!  or 1KB.
!
! Set window W as invalid.  Set the frame pointer of
! W to generic_isr_stack_buffer.
!
! Move to window T, sp = fp - 64.
! Call C interrupt handler from T.
!
! On return from interrupt handler.
! 1. recover all window registers
! 2. recover wim psr
! 3. recover globals.
! 4. jmpl/rett.
!
!
!  ASSUMPTIONS
!    psr, tbr are current.
!    l0 contains the PSR
!    l3 contains TBR
!
.section .text.traphandlers
.align 8
.global generic_vectored_isr
generic_vectored_isr:


! Save the running thread's state into the
! save buffer.
save_running_thread_state:

   ! l5 points to the stack buffer.
   set generic_isr_save_buffer, %l5

   ! save psr
   rd %psr, %l6
   st %l6, [%l5]

   !save wim
   rd %wim, %l6
   st %l6, [%l5 + 4]

   !save y
   rd %y, %l6
   st %l6, [%l5 + 8]

   ! save globals.
   st  %g1, [%l5 + 12]
   std %g2, [%l5 + 16]
   std %g4, [%l5 + 24]
   std %g6, [%l5 + 32]

   ! make wim 0 for now.
   mov %g0, %wim

   ! save the window registers...
   add %l5, 40,  %g1

   mov 8, %g2

! Save all the windows!
save_loop:
   std %l0, [%g1]
   std %l2, [%g1+8]
   std %l4, [%g1+16]
   std %l6, [%g1+24]
   std %i0, [%g1+32]
   std %i2, [%g1+40]
   std %i4, [%g1+48]
   std %i6, [%g1+56]
   subcc %g2, 1, %g2
   save  ! executed 8 times.. stay in window T
   bnz   save_loop
   add %g1, 64, %g1
   nop

   ! move to window W = T+1.
   restore

   ! set W as invalid
   mov 0x1, %l3
   mov %psr, %l4
   sll %l3, %l4, %l3
   mov %l3, %wim

   ! Give W a stack.
   set generic_isr_stack_buffer, %l3
   add %l3, 4096, %fp
   sub %fp, 64, %sp

   ! move to T, give it a minimal stack frame.
   save %sp, -64, %sp

   !
   !   enable traps, but set proc-ilvl=15
   !   so that non NMI interrupt will be blocked.
   !   This prevents a non NMI interrupt from interrupting
   !   the interrupt handler.
   !
   or %l0, 0x20, %l7       ! ET=1
   or %l7, 0xf00, %l7      ! [11:8] = 0xf
   wr %l7, %psr            ! write to PSR

   ! This is a  C routine with one argument
   ! namely, the TBR value.
   !
   ! It will run in window T-1....
   !
   ! And may trap...
   !    Thus, the ET=1 above.
   rd %tbr, %o0
   call ajit_generic_interrupt_handler
   nop

   !  back in T.


! Recove the interrupted thread's state and
! continue.
recover_and_leave:

   ! recover all the window registers.
   ! Use g1 as a temporary.
   set generic_isr_save_buffer, %g1
   
   ! g3 holds the save buffer base address
   mov %g1, %g3

   ! disable window overflow/underflow traps..
   mov %g0, %wim

   mov 8, %g2
   add %g1, 40, %g1

!  read back saved registers for 8 windows.
recover_loop:
   ldd [%g1], %l0
   ldd [%g1+8], %l2
   ldd [%g1+16], %l4
   ldd [%g1+24], %l6
   ldd [%g1+32], %i0
   ldd [%g1+40], %i2
   ldd [%g1+48], %i4
   ldd [%g1+56], %i6
   subcc %g2, 1, %g2
   save !  executed 8 times, 
   bnz  recover_loop
   add %g1, 64, %g1
   nop


   ! get back the psr, y, wim registers.
   ld [%g3], %l6
   mov %l6, %psr
   !restore y
   ld [%g3 + 8], %l6
   mov %l6, %y
   !restore wim
   ld [%g3 + 4], %l6
   mov %l6, %wim

   ! restore globals.
   mov %g3, %g1
   ldd [%g1 + 16], %g2
   ldd [%g1 + 24], %g4
   ldd [%g1 + 32], %g6
   ! g1 at the end..
   ld [%g1 + 12],  %g1


jmpl_and_return:

   !   go home.. guaranteed that the
   !   return window is valid 
   jmpl %r17, %r0
   rett %r18

   nop


