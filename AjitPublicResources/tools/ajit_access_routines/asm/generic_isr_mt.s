! an improved generic isr model for the case when an interrupt handler
! does a lot of user-level work.

!
! When you get here, you are in the trap window T
! which may or may not be an available window.  Our first
! job is to make T an available window, by executing a
! restore/save combination.  Save the globals. 
! And then work from T. Need to be careful while 
! RETT-ing by making window T+1 valid before RETT.
!
!
! Assumptions:  
!     a valid window will not have a valid stack pointer.
!     an invalid window will have a valid stack pointer.
!

.section .text.traphandlers
.global generic_isr_mt
generic_isr_mt:
   !
   ! Step 1
   !    First disable the interrupt controller.
   !
   rd %asr29, %l6
   and %l6, 0xff, %l7 ! thread id
   srl %l6, 8, %l6
   and %l6, 0xff, %l6  ! core id
   sll %l6, 0x1,  %l6  ! (2 * core_id)
   add %l6, %l7,  %l6  ! (2 * core_id) + thread_id
   sll %l6, 0x2,  %l6  ! 4 *( (2*core_id) + thread_id)
   sethi  %hi(0xffff3000), %l7
   add  %l6, %l7, %l7
   sta %g0, [%l7] 0x20  ! disable irc

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   ! Now check if T is available.. and give it a hefty stack.
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !  ensure that you have a stack
   !  to work with.   Make this
   !  window a valid window to do
   !  serious work in.

   ! Check if this window is valid.
   mov %wim, %l6
   mov %psr, %l7
   srl %l6, %l7, %l6 
   cmp %l6, 0x1

   ! invalid? 
   be  handle_invalid_T
   nop

   ba continue_with_valid_T
   nop

! invalid window, make it valid
! by making T-1 invalid.
handle_invalid_T:

   ! move to T-1
   save    

   !
   !  save registers in T-1 to stack.
   !
   std %l0, [%sp +  0]
   std %l2, [%sp +  8]
   std %l4, [%sp + 16]
   std %l6, [%sp + 24]
   std %i0, [%sp + 32]
   std %i2, [%sp + 40]
   std %i4, [%sp + 48]
   std %i6, [%sp + 56]

   /* rotate WIM one bit right, we have 8 windows */
   mov %wim,%l3
   sll %l3,7,%l4
   srl %l3,1,%l3
   or  %l3,%l4,%l3
   and %l3,0xff,%l3

   ! WIM says T-1 is invalid.
   mov %l3, %wim

   ! back in T.
   restore

continue_with_valid_T:
   
   !
   ! give T a stack pointer
   !
   sub %fp, 320, %sp

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


   ! save state in stack of window T.
   !  Note: do not use %sp to %sp  + 64
   ! Step 0
   !    Save the PSR
   mov %psr, %l7
   st %l7, [%sp + 64]          ! Save PSR


   !
   ! Step 2
   !   Store globals, ins and stack pointer in stack of T.
   !   Will be recovered later.
   !
   st  %g1, [%sp + 68]
   std %g2, [%sp + 72]
   std %g4, [%sp + 80]
   std %g6, [%sp + 88]
   std %i0, [%sp + 96]
   std %i2, [%sp + 104]
   std %i4, [%sp + 112]
   std %i6, [%sp + 120]
   st  %sp, [%sp + 128]
   st  %l1, [%sp + 132]
   st  %l2, [%sp + 136]

   ! y carries state.
   mov %y, %l7
   st  %l7,  [%sp + 140]

   ! floating point state.
   std %f0, [%sp + 144]
   std %f2, [%sp + 152]
   std %f4, [%sp + 160]
   std %f6, [%sp + 168]
   std %f8, [%sp + 176]
   std %f10, [%sp + 184]
   std %f12, [%sp + 192]
   std %f14, [%sp + 200]
   std %f16, [%sp + 208]
   std %f18, [%sp + 216]
   std %f20, [%sp + 224]
   std %f22, [%sp + 232]
   std %f24, [%sp + 240]
   std %f26, [%sp + 248]
   std %f28, [%sp + 256]
   std %f30, [%sp + 264]
   st %fsr, [%sp +  272]

   !   enable traps, but set proc-ilvl=15
   !   so that non NMI interrupt will be blocked.
   !   This prevents a non NMI interrupt from interrupting
   !   the interrupt handler.
   mov %psr, %l7
   or %l7,0x20, %l7       ! ET=1
   or %l7, 0xf00, %l7     ! [11:8] = 0xf
   wr %l7, %psr           ! write to PSR

   ! Step 6
   !  call the interrupt handler.. free to
   !  do whatever it wants... return should
   !  bring it home to this window..
   call generic_interrupt_handler
   nop

   !
   ! You have come back from the actual handler..
   !

   ! Step 5
   ! Important: ensure that you
   ! have a valid window to rett
   ! into. rett into an invalid window
   ! will put the processor in error mode.
   ! 
   ! Check if window T+1 is valid...
   ! 
   mov %wim, %l6
   mov %psr, %l7
   and %l7, 7, %l7  !CWP mod 8
   add %l7, 1, %l7  ! add 1
   and %l7, 7, %l7
   srl %l6, %l7, %l6 
   cmp %l6, 0x1
   
   ! l6 holds wim
   mov %wim, %l6

   bne recover_and_leave
   nop

free_window_for_rett:

   !
   ! window T+1 is invalid..  recover its registers.
   !  and make T+2 invalid.
   !
   mov 0, %wim
   restore   !in window T+1.

   !
   ! recover registers in T+1
   !
   ldd [%sp +  0], %l0
   ldd [%sp +  8], %l2
   ldd [%sp + 16], %l4
   ldd [%sp + 24], %l6
   ldd [%sp + 32], %i0
   ldd [%sp + 40], %i2
   ldd [%sp + 48], %i4
   ldd [%sp + 56], %i6

   save  ! back to T

   ! wim should be rotated left.
   mov %l6,%l3
   srl %l3,7,%l4
   sll %l3,1,%l3
   or  %l3,%l4,%l3
   and %l3,0xff,%l3

   ! wim says T+1 is valid.
   mov %l3, %wim

recover_and_leave:

   !
   !   recover psr, globals and other state saved in
   !   T's stack frame.
   !

   ! Step 6
   !   get back the psr and global registers, also i, sp.
   ld [%sp + 64],  %l7  
   wr %l7, %psr
   ld [%sp + 68],  %g1
   ldd [%sp + 72], %g2
   ldd [%sp + 80], %g4
   ldd [%sp + 88], %g6
   ldd [%sp + 96], %i0
   ldd [%sp + 104],%i2
   ldd [%sp + 112],%i4
   ldd [%sp + 120],%i6
   ld  [%sp + 132],%l1
   ld  [%sp + 136],%l2
   ld  [%sp + 140], %l7
   mov %l7, %y
   ldd [%sp + 144], %f0
   ldd [%sp + 152], %f2
   ldd [%sp + 160], %f4
   ldd [%sp + 168], %f6
   ldd [%sp + 176], %f8
   ldd [%sp + 184], %f10
   ldd [%sp + 192], %f12
   ldd [%sp + 200], %f14
   ldd [%sp + 208], %f16
   ldd [%sp + 216], %f18
   ldd [%sp + 224], %f20
   ldd [%sp + 232], %f22
   ldd [%sp + 240], %f24
   ldd [%sp + 248], %f26
   ldd [%sp + 256], %f28
   ldd [%sp + 264], %f30
   ld  [%sp + 272], %fsr

   ld  [%sp + 128],%sp

jmpl_and_return:

   ! Step 8 
   !   go home.. guaranteed that the
   !   return window is valid 
   jmpl %r17, %r0
   rett %r18

   nop
