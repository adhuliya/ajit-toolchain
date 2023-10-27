! An improved generic isr model for the case when an interrupt handler
! does a lot of user-level work.
!
!MPD notes
! This seems to work fine, and it uses the same stack as the
! interrupted stack.  However, some code seems to break with
! this interrupt handler.  I have no explanation as yet,
! but we have implemented an ISR which saves the
! entire register context and uses a different stack
! to run the interrupt handling code.

!
! There was an interrupt in window W, we move to trap window T
! Trap window T is either valid or invalid..  If it is valid,
! then we can give it a stack..  
!
! If T is invalid, then we make it valid as follows:
!    make T-1 invalid by saving its registers to stack.
!         and adjusting wim
!    make T valid
! endif 
!    Give T a stack relative to that in W.
!    save T state into this stack. 
!    deepen the stack in T.
!    call the ajit generic interrupt handler from T.
!    on return, make window T+1 available to 
!           rett into.. using a restore/save combination.
!    recover the critical information stored on stack in T
!    jmpl/rett into T+1 and go on.
!
!  ASSUMPTIONS
!    l0 contains PSR
!    l3 contains TBR
!
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

   ! window T-1 will be made invalid...
   mov %wim,%l3
   sll %l3,7,%l4
   srl %l3,1,%l3
   or  %l3,%l4,%l3
   and %l3,0xff,%l3

   ! wim = 0.
   mov %g0,%wim

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

   ! back in T.
   restore

   ! WIM says T-1 is invalid, but T is valid.
   mov %l3, %wim


continue_with_valid_T:

   ! Give window T a stack..
   ! Note: the stack pointer in W is not touched.
   sub %fp, 96, %sp


   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   ! save state in stack of window T.
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !
   !   Store globals ins psr l1 l2 in stack of T.
   !   Will be recovered later.
   !
   st  %l0, [%sp]            ! Save PSR
   st  %g1, [%sp + 4]
   std %g2, [%sp + 8]
   std %g4, [%sp + 16]
   std %g6, [%sp + 24]
   ! for rett
   st  %l1, [%sp + 32]
   st  %l2, [%sp + 36]
   ! y carries state.
   mov %y, %l7
   st  %l7,  [%sp + 40]

   ! floating point state is not saved here,
   ! but should be managed in the C handler.

   ! increase the stack further.. 
   ! for window overflow traps..
   sub %sp, 96, %sp


   ! check if the interrupt is not maskable.
   ! if it is not maskable, we will enable traps
   ! with processor irl 15.  The handler can then
   ! generate a trap.
   !
   ! If the interrupt is non-maskable (NMI), then the NMI handler
   ! runs with interrupts disabled.   
   !
   ! note: tbr is read into o0 to be passed to interrupt handler.
   !
   rd %tbr, %o0
   srl %o0, 4, %l3
   and %l3, 0xf, %l3
   subcc %l3, 0xf, %l3
   bz continue_after_enabling_traps_or_nmi
   nop

   !
   !   enable traps, but set proc-ilvl=15
   !   so that non NMI interrupt will be blocked.
   !
   or %l0, 0x20, %l7       ! ET=1
   or %l7, 0xf00, %l7      ! [11:8] = 0xf
   wr %l7, %psr            ! write to PSR

continue_after_enabling_traps_or_nmi:

   ! Step 6
   !  Note that tbr is in o0 here.
   !  call the interrupt handler.. free to
   !  do whatever it wants... return should
   !  bring it home to this window..
   !


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
   ! non NMI interrupts are still blocked.

prepare_window_for_rett:

   ! Traps are enabled...  
   !  make window T+1 available for RETT!
   restore

   ! back in T.
   save

recover_and_leave:
   !
   !   recover psr, globals and other state saved in
   !   T's stack frame.
   !
   add %sp, 96, %sp

   !   get back the psr and global registers,in regs,y

   ! get back psr.
   ld [%sp],  %l7  
   wr %l7, %psr
   ld  [%sp + 4],  %g1
   ldd [%sp + 8],  %g2
   ldd [%sp + 16], %g4
   ldd [%sp + 24], %g6
   ld  [%sp + 32], %l1
   ld  [%sp + 36], %l2
   ld  [%sp + 40], %l7

   ! recover y.
   mov %l7, %y


jmpl_and_return:

   !   go home.. guaranteed that the
   !   return window is valid 
   jmpl %r17, %r0
   rett %r18

   nop
