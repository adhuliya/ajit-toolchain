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
!
!  psr, tbr are as received in the trap table.
!  traps are disabled.
!
!  Note: T is is trap handler window and may be invalid!
!
!  l0 contains PSR
!  l3 contains TBR
.section .text.traphandlers
.global generic_vectored_isr
generic_vectored_isr:
   !
   ! check if T is valid.
   !
   rd %wim, %l4
   srl %l4, %l0, %l4
   cmp %l4, 0x1

   bne continue_with_valid_T
   nop

handle_invalid_T:

   ! T is invalid.. go to T-1 and
   ! make it valid.
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
   mov %sp, %l7

   !
   ! give T a stack pointer
   !
   sub %fp, 320, %sp

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   ! save state in stack of window T.
   ! Step 0
   !    Save the PSR (for the flags!)
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !
   !   Store globals ins and psr in stack of T.
   !   Will be recovered later.
   !
   st  %l0, [%sp]            ! Save PSR
   st  %g1, [%sp + 4]
   std %g2, [%sp + 8]
   std %g4, [%sp + 16]
   std %g6, [%sp + 24]
   std %i0, [%sp + 32]
   std %i2, [%sp + 40]
   std %i4, [%sp + 48]
   std %i6, [%sp + 56]
   ! for rett
   st  %l1, [%sp + 64]
   st  %l2, [%sp + 68]
   ! old stack pointer
   st %l7, [%sp + 72]
   ! y carries state.
   mov %y, %l7
   st  %l7,  [%sp + 76]

   ! floating point state is not saved here,
   ! but should be managed in the C handler.

   ! increase the stack further.. 
   ! for window overflow traps..
   sub %sp, 96, %sp

   !
   !   enable traps, but set proc-ilvl=15
   !   so that non NMI interrupt will be blocked.
   !   This prevents a non NMI interrupt from interrupting
   !   the interrupt handler.
   !
   or %l0, 0x20, %l7       ! ET=1
   or %l7, 0xf00, %l7     ! [11:8] = 0xf
   wr %l7, %psr           ! write to PSR

   ! Step 6
   !  call the interrupt handler.. free to
   !  do whatever it wants... return should
   !  bring it home to this window..
   rd %tbr, %o0
   ! This is a  C routine with one argument
   ! namely, the TBR value.
   !
   ! It will run in window T-1....
   !    which may be invalid.. 
   !    Thus, the ET=1 above.
   !
   ! 
   call ajit_generic_interrupt_handler
   nop

   !
   ! You have come back from the actual handler..
   ! Interrupts are still disabled...
   !

   ! Step 5: make window T+1 available for RETT!
   restore
   save

recover_and_leave:
   !
   !   recover psr, globals and other state saved in
   !   T's stack frame.
   !
   add %sp, 96, %sp

   ! Step 6
   !   get back the psr and global registers,in regs,y
   ld [%sp],  %l7  
   wr %l7, %psr
   ld  [%sp + 4],  %g1
   ldd [%sp + 8],  %g2
   ldd [%sp + 16], %g4
   ldd [%sp + 24], %g6
   ldd [%sp + 32], %i0
   ldd [%sp + 40], %i2
   ldd [%sp + 48], %i4
   ldd [%sp + 56], %i6
   ld  [%sp + 64], %l1
   ld  [%sp + 68], %l2
   ld  [%sp + 72], %l6
   ld  [%sp + 76], %l7

   mov %l6, %sp
   mov %l7, %y

jmpl_and_return:

   ! Step 8 
   !   go home.. guaranteed that the
   !   return window is valid 
   jmpl %r17, %r0
   rett %r18

   nop
