! a generic isr model for the case when an interrupt handler
! does a lot of user-level work.

!
! When you get here, you are in the trap window T
!
.section .text.traphandlers
.global generic_isr_ibuffer
.align 128
generic_isr_ibuffer:
.skip 128
.global generic_isr
generic_isr:
   !
   ! Step 1: save state.
   !
   ! Special attention to o1, which will
   ! be used as a temporary.  Save it in asr1.
   wr %o1, %asr1

   ! Use generic_isr_buffer to store all registers
   ! and PSR.
   !
   ! TODO: should save FPU registers also.
   !
   set generic_isr_ibuffer, %o1
   st  %g1, [%o1 + 4]
   std %g2, [%o1 + 8]
   std %g4, [%o1 + 16]
   std %g6, [%o1 + 24]
   std %i0, [%o1 + 32]
   std %i2, [%o1 + 40]
   std %i4, [%o1 + 48]
   std %i6, [%o1 + 56]
   std %l0, [%o1 + 64]
   std %l2, [%o1 + 72]
   std %l4, [%o1 + 80]
   std %l6, [%o1 + 88]
   !
   ! save o0 and o1..
   ! o1 is in asr1
   mov %o0, %l0
   rd %asr1, %l1
   std %l0, [%o1 + 96]
   ! save remaining o regs.
   std %o2, [%o1 + 104]
   std %o4, [%o1 + 112]
   std %o6, [%o1 + 120]


   !
   ! Step 2
   !    Save the PSR into the buffer.
   !
   set generic_isr_ibuffer, %o1
   mov %psr, %o2
   st %o2, [%o1]
    	


   !
   ! Step 3
   !    First disable the interrupt controller.
   !
   sethi  %hi(0xffff3000), %o1
   sta %g0, [%o1] 0x20  ! disable irc


   !
   ! enable traps, but set proc-ilvl=15
   ! so that non NMI interrupt will be blocked.
   !    This prevents a non NMI interrupt from interrupting
   !    the interrupt handler.
   or %o2,0x20, %o2       ! ET=1
   or %o2, 0xf00, %o2     ! [11:8] = 0xf
   wr %o2, %psr           ! write to PSR

   ! Step 4
   !  ensure that you have a stack
   !  to work with.  Also makes this
   !  window a valid window to do
   !  serious work in.
   restore
   save %sp, -96, %sp

   ! Now you are back in window T, but
   ! with a stack.  This stack is necessary
   ! for WOF/WUF traps that can be triggered by
   ! the high-level ISR.


   ! Step 5
   !    call the interrupt handler.. free to
   !    do whatever it wants..
   call generic_interrupt_handler
   nop


   ! Step 6
   !
   ! Important: ensure that you
   ! have a valid window to rett
   ! into. rett into an invalid window
   ! will put the processor in error mode.
   !
   ! This restore may itself cause an 
   ! exception, which will be handled.
   restore
   save 

   ! Step 7
   !   back from complex code..
   !   recover globals.
   !
   set generic_isr_ibuffer, %o1

   ! get back the psr and registers.
   ld [%o1],  %o2;  wr %o2, %psr
   ld [%o1 + 4],  %g1
   ldd [%o1 + 8], %g2
   ldd [%o1 + 16],%g4
   ldd [%o1 + 24],%g6
   ldd [%o1 + 32], %i0
   ldd [%o1 + 40], %i2
   ldd [%o1 + 48], %i4
   ldd [%o1 + 56], %i6
   ldd [%o1 + 64], %l0
   ldd [%o1 + 72], %l2
   ldd [%o1 + 80], %l4
   ldd [%o1 + 88], %l6
   ! o2,o3 will hold  o0, o1
   ldd [%o1 + 96], %o2
   ! keep retrieved o0, o1 in asr1,2.
   wr %o2, %asr1
   wr %o3, %asr2
   ! retrieve o2 to o7
   ldd [%o1 + 104], %o2
   ldd [%o1 + 112], %o4
   ldd [%o1 + 120], %o6


   ! Step 9
   !  re-enable the interrupt controller.
   sethi  %hi(0xffff3000), %o1
   mov 0x1, %o0 
   sta %o0, [%o1] 0x20  ! enable irc

   ! get back o0,o1
   rd %asr1, %o0
   rd %asr2, %o1

   ! Step 10
   !   go home.. guaranteed that the
   !   return window is valid (see Step 7 above)
   jmpl %r17, %r0
   rett %r18

   nop
