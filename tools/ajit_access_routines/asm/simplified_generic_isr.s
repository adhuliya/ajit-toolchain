! a generic isr model for the case when an interrupt handler
! does a lot of user-level work.

!
! When you get here, you are in the trap window T
! which may or may not be a valid window.  Our first
! job is to make T a valid window, by executing a
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
.set   ISR_STACK_BASE, 0xffffcf00
.global generic_isr_ibuffer
.align 8
generic_isr_ibuffer:
.skip 256
generic_isr_intr_active:
.skip 8, 0x0
.global generic_isr
generic_isr:

   !
   ! Step 0
   !    Save the PSR
   set generic_isr_ibuffer, %l6
   mov %psr, %l7
   st %l7, [%l6]          ! Save PSR

   !
   ! No interrupt nesting.
   !    If interrupt-flag is set, then go to error.
   !    mode.
   set generic_isr_intr_active, %l6
   ld [%l6], %l7
   cmp %l7, %g0
   be normal_exec
   nop

   ! go into error mode..
   ta 0

normal_exec:

   ! Set the interrupt flag.
   set generic_isr_intr_active, %l6
   mov 0x1, %l7
   st %l7, [%l6]

   !
   ! Step 1
   !    First disable the interrupt controller.
   !
   sethi  %hi(0xffff3000), %l7
   sta %g0, [%l7] 0x20  ! disable irc



   !
   ! Step 2
   !   Store globals, ins and stack pointer in isr buffer.
   !   Will be recovered later.
   !
   set generic_isr_ibuffer, %l6
   st  %g1, [%l6 + 4]
   std %g2, [%l6 + 8]
   std %g4, [%l6 + 16]
   std %g6, [%l6 + 24]
   std %i0, [%l6 + 32]
   std %i2, [%l6 + 40]
   std %i4, [%l6 + 48]
   std %i6, [%l6 + 56]
   st  %sp, [%l6 + 64]
   st  %l1, [%l6 + 68]
   st  %l2, [%l6 + 72]
   mov %y, %l7
   st  %l7,  [%l6 + 76]
   std %f0, [%l6 + 80]
   std %f2, [%l6 + 88]
   std %f4, [%l6 + 96]
   std %f6, [%l6 + 104]
   std %f8, [%l6 + 112]
   std %f10, [%l6 + 120]
   std %f12, [%l6 + 128]
   std %f14, [%l6 + 136]
   std %f16, [%l6 + 144]
   std %f18, [%l6 + 152]
   std %f20, [%l6 + 160]
   std %f22, [%l6 + 168]
   std %f24, [%l6 + 176]
   std %f26, [%l6 + 184]
   std %f28, [%l6 + 192]
   std %f30, [%l6 + 200]
   st %fsr, [%l6 + 204]


   ! Step 3
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
   ! give T a stack pointer for later overflow saves.
   !
   sub %fp, 96, %sp

   ! Step 4
   !   enable traps, but set proc-ilvl=15
   !   so that non NMI interrupt will be blocked.
   !    This prevents a non NMI interrupt from interrupting
   !    the interrupt handler.
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
   ! window T+1 is invalid.. it used the ISR stack
   ! to save registers.  Recover them.
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
   !   recover psr, globals.
   !
   set generic_isr_ibuffer, %l6

   ! Step 6
   !   get back the psr and global registers, also i, sp.
   ld [%l6],  %l7  
   wr %l7, %psr
   ld [%l6 + 4],  %g1
   ldd [%l6 + 8], %g2
   ldd [%l6 + 16],%g4
   ldd [%l6 + 24],%g6
   ldd [%l6 + 32],%i0
   ldd [%l6 + 40],%i2
   ldd [%l6 + 48],%i4
   ldd [%l6 + 56],%i6
   ld  [%l6 + 64],%sp
   ld  [%l6 + 68],%l1
   ld  [%l6 + 72],%l2
   ld  [%l6 + 76], %l7
   mov %l7, %y
   ldd [%l6 + 80], %f0
   ldd [%l6 + 88], %f2
   ldd [%l6 + 96], %f4
   ldd [%l6 + 104], %f6
   ldd [%l6 + 112], %f8
   ldd [%l6 + 120], %f10
   ldd [%l6 + 128], %f12
   ldd [%l6 + 136], %f14
   ldd [%l6 + 144], %f16
   ldd [%l6 + 152], %f18
   ldd [%l6 + 160], %f20
   ldd [%l6 + 168], %f22
   ldd [%l6 + 176], %f24
   ldd [%l6 + 184], %f26
   ldd [%l6 + 192], %f28
   ldd [%l6 + 200], %f30
   ld  [%l6 + 204], %fsr


   !
   ! Step 7
   !   re-enable the interrupt controller.
   !   
   sethi  %hi(0xffff3000), %l6
   mov 0x1, %l0 
   sta %l0, [%l6] 0x20  ! enable irc

   ! mark the interrupt as ok
   set generic_isr_intr_active, %l6
   mov 0x0, %l7
   st %l7, [%l6]

jmpl_and_return:

   ! Step 8 
   !   go home.. guaranteed that the
   !   return window is valid 
   jmpl %r17, %r0
   rett %r18

   nop
